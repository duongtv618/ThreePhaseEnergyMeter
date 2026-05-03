#include "dsp.h"

#include "app_cfg.h"

#include "arm_math.h"
#include "pll.h"

#define SCALE_FACTOR 1000

#ifdef DSP_USE_Q31

/**
 * @brief Process the meter data using DSP algorithms
 *
 * @param meterData Pointer to the meter data structure to be filled
 * @param vol_buf Pointer to the voltage buffer
 * @param cur_buf Pointer to the current buffer
 * @param coef Pointer to the DSP coefficients
 */
void dspProcessPhase(phasestruct meter_data_s* meterData,
                     q31_t vol_buf[METER_SAMPLES_PER_CYCLE],
                     q31_t cur_buf[METER_SAMPLES_PER_CYCLE],
                     dspPhaseCoef_t coef) {
  q31_t rmsVoltage, rmsCurrent;
  q31_t activePower;
  arm_rms_q31(vol_buf, METER_SAMPLES_PER_CYCLE, &rmsVoltage);
  arm_rms_q31(cur_buf, METER_SAMPLES_PER_CYCLE, &rmsCurrent);
  arm_mult_q31(vol_buf, cur_buf, mulBuffer, METER_SAMPLES_PER_CYCLE);
  arm_mean_q31(mulBuffer, METER_SAMPLES_PER_CYCLE, &activePower);

  /** q15_t range from -32768 - 32767 */
  /** rms will be peak * sqrt(2) -> rmsVoltage in mV will calculate by:
   * 1. Multi with peak voltage data in mV
   * 2. Divide for 32767
   */
  meterData->rmsVoltage =
      ((int64_t)rmsVoltage * 325269) >> 29;  // Apply voltage coefficient
  meterData->rmsCurrent =
      ((int64_t)rmsCurrent * 8485) >> 29;  // Apply current coefficient
  meterData->activePower = (((int64_t)activePower * 8485 * 325269) >> 29);
  meterData->apparentPower = meterData->rmsVoltage * meterData->rmsCurrent;
  if (meterData->activePower > meterData->apparentPower) {
    meterData->activePower = meterData->apparentPower;
  }
  meterData->powerFactor =
      meterData->activePower * 1000 /
      meterData->apparentPower;  // PF scale 1000, with q15 multi, it will never
                                 // be 1, only can be 999
}

void dspProcessFre(struct pll_s* pll,
                   q31_t freBuffer[METER_SAMPLES_PER_CYCLE][3],
                   uint16_t periodMs) {
  for (size_t i = 0; i < METER_SAMPLES_PER_CYCLE; i++) {
    pll_update_3p(pll, freBuffer[i][0], freBuffer[i][1], freBuffer[i][2], 50);
  }
}
#endif

#ifdef DSP_USE_FLOAT
static float32_t get_group_mag(float32_t* mag, uint16_t center_bin);
/**
 * @brief DSP phase calculation
 *
 * @param meterData Meter data instance
 * @param vol_buf Voltage's buffer
 * @param cur_buf Current's buffer
 * @param coef Coeffection
 */
void dsp_process_phase(struct phase_data_s* phase_dat, float32_t* vol_buf,
                       float32_t* cur_buf, struct dsp_phase_coef_s phase_coef) {
  float32_t rmsV, rmsI, actPwr;
  float32_t ui_diff_angel;

  arm_rms_f32(vol_buf, METER_SAMPLES_PER_CYCLE, &rmsV);
  arm_rms_f32(cur_buf, METER_SAMPLES_PER_CYCLE, &rmsI);
  arm_dot_prod_f32(vol_buf, cur_buf, METER_SAMPLES_PER_CYCLE, &actPwr);
  actPwr /= (float32_t)METER_SAMPLES_PER_CYCLE;

  phase_dat->app_pwr = rmsV * rmsI;
  phase_dat->rms_current = rmsI;
  phase_dat->rms_voltage = rmsV;
  if (actPwr > phase_dat->app_pwr) {
    phase_dat->act_pwr = phase_dat->app_pwr;
    phase_dat->react_pwr = 0.0f;
  } else {
    phase_dat->act_pwr = actPwr;

    arm_sqrt_f32(phase_dat->app_pwr * phase_dat->app_pwr - actPwr * actPwr,
                 &phase_dat->react_pwr);
  }

  phase_dat->pf = (phase_dat->app_pwr > 1e-9f) ? (phase_dat->act_pwr / phase_dat->app_pwr) : 0.0f;
  float32_t phi = acosf(phase_dat->pf);
  phi = phi * 180.0f / PI;
  ui_diff_angel = phase_dat->angle.current - phase_dat->angle.voltage;
  if (ui_diff_angel > 0.0f) {
    phi += phase_coef.i_phase_shift;
  } else if (ui_diff_angel < 0.0f) {
    phi -= phase_coef.i_phase_shift;
  }
  phase_dat->pf = arm_cos_f32(phi * PI / 180.0f);
  phase_dat->act_pwr = phase_dat->app_pwr * phase_dat->pf;

  phase_dat->act_pwr *= phase_coef.i_coef * phase_coef.v_coef;
  phase_dat->app_pwr *= phase_coef.i_coef * phase_coef.v_coef;
  phase_dat->rms_current *= phase_coef.i_coef;
  phase_dat->rms_voltage *= phase_coef.v_coef;
  phase_dat->react_pwr *= phase_coef.i_coef * phase_coef.v_coef;
}

/**
 * @brief DSP voltage line calculation
 * 
 * @param mdat points to meter data
 * @param v_va points to voltage a buffer
 * @param v_vb points to voltage b buffer
 * @param v_vc poitns to voltage c buffer
 * @param v_len is vector length
 */
void dsp_process_vol_line(struct meter_data_s *mdat, struct dsp_coef_s* coef, float32_t* v_va, float32_t* v_vb, float32_t* v_vc, uint32_t v_len) {
  float32_t vab = 0.0f;
  float32_t vbc = 0.0f;
  float32_t vca = 0.0f;
  float32_t vsub;
  for (size_t i = 0; i < v_len; i++) {
    vsub = v_va[i] - v_vb[i];
    vab += vsub * vsub;
    vsub = v_vb[i] - v_vc[i];
    vbc += vsub * vsub;
    vsub = v_vc[i] - v_va[i];
    vca += vsub * vsub;
  }
  vab /= v_len;
  vbc /= v_len;
  vca /= v_len;

  arm_sqrt_f32(vab, &mdat->vol_line.ab);
  arm_sqrt_f32(vbc, &mdat->vol_line.bc);
  arm_sqrt_f32(vca, &mdat->vol_line.ca);

  mdat->vol_line.ab *= coef->vll.ab_gain;
  mdat->vol_line.bc *= coef->vll.bc_gain;
  mdat->vol_line.ca *= coef->vll.ca_gain;
}

/**
 * @brief DSP frequency block update single phase
 *
 * @param pll Phase lock loop instance
 * @param meterDat struct meter_data_s instance
 * @param buf Buffer
 * @param len Buffer length
 */
void dsp_process_fre_1_phase(struct pll_s* pll, struct meter_data_s* meterDat,
                             float32_t* buf, uint16_t len) {
  for (size_t i = 0; i < len; i++) {
    pll_update_1p(pll, buf[i]);
  }
  if (pll_is_locked(pll)) pll_update_fs(pll);
  meterDat->frequency = pll->fre;
}

/**
 * @brief DSP frequency block update
 * @note buffer must be in this format va[0], vb[0], vc[0], va[1], vb[1], vc[1]
 * @param pll Phase lock loop instance
 * @param meterDat struct meter_data_s instance
 * @param buf Buffer
 * @param len Buffer length
 */
void dsp_process_fre_3_phase(struct pll_s* pll, struct meter_data_s* meterDat,
                             float32_t* bufVola, float32_t* bufVolB,
                             float32_t* bufVolC, uint16_t len) {

  /** Update phase lock loop */
  for (size_t i = 0; i < len; i++) {
    pll_update_3p(pll, bufVola[i], bufVolB[i], bufVolC[i]);
  }
  /** Update frequency */
  if (pll_is_locked(pll)) pll_update_fs(pll);
  meterDat->frequency = pll->fre;
}

void dsp_process_thd(struct phase_data_s* phase_data, float32_t* data_buf,
                     float32_t* fft_buf, float32_t* mag_buf, uint16_t buf_len,
                     float32_t* angle, float32_t* result) {
  if (buf_len < FFT_BUF_SIZE) {
    return;
  }

  arm_rfft_fast_instance_f32 instance;
  #if (FFT_BUF_SIZE == 2048)
  arm_rfft_fast_init_2048_f32(&instance);
  #elif (FFT_BUF_SIZE == 1024)
  arm_rfft_fast_init_1024_f32(&instance);
  #endif

  /** Forward FFT */
  arm_rfft_fast_f32(&instance, data_buf, fft_buf, 0);

  /** Calculate angle */
  *angle = atan2f(fft_buf[BIN_1_COUNT * 2 + 1], fft_buf[BIN_1_COUNT * 2 + 0]);

  /** Calculate magnitude */
  arm_cmplx_mag_f32(fft_buf + 2, mag_buf, FFT_BUF_SIZE / 2 - 1);

  float32_t v1 = get_group_mag(mag_buf, BIN_1_COUNT - 1);

  /** Calculate harmonics */
  float32_t sum_h_sq = 0.0f;
  for (size_t i = 2; i < (FFT_BUF_SIZE / 2 - 1) / BIN_1_COUNT; i++) {
    /** Get magnitude of harmonic,  mag start from bin 16, bin 0 is not
     * calculated */
    float32_t vh = get_group_mag(mag_buf, BIN_1_COUNT * i - 1);
    sum_h_sq += (vh * vh);
  }

  float32_t thd;
  arm_sqrt_f32(sum_h_sq, &thd);
  *result = thd * 100.0f / v1;
}

/**
 * @brief Calculate magnitude of group
 *
 * @param mag points to the magnitude buffer
 * @param center_bin is the center bin of the group
 * @return float32_t
 */
static float32_t get_group_mag(float32_t* mag, uint16_t center_bin) {
  float32_t left = mag[center_bin - 1];
  float32_t right = mag[center_bin + 1];
  float32_t center = mag[center_bin];

  float32_t ret;

  arm_sqrt_f32(left * left + center * center + right * right, &ret);
  return ret;
}
#endif