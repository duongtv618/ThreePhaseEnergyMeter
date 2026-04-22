#ifndef DSP_H
#define DSP_H

#include "arm_math.h"
#include "pll.h"
#include "share_types.h"

#ifdef DSP_USE_Q31

void dsp_process_phase(struct phase_data_s* meterData,
                     q31_t volBuffer[METER_SAMPLES_PER_CYCLE],
                     q31_t curBuffer[METER_SAMPLES_PER_CYCLE],
                     struct dsp_phase_coef_s coef);

void dspProcessFre(PLL3_t* pll, q31_t freBuffer[METER_SAMPLES_PER_CYCLE][3],
                   uint16_t periodMs);
#endif

#ifdef DSP_USE_FLOAT
void dsp_process_phase(struct phase_data_s* meterData, float32_t* volBuffer,
                     float32_t* curBuffer, struct dsp_phase_coef_s coef);

void dsp_process_vol_line(struct meter_data_s *mdat, struct dsp_coef_s* coef, float32_t* v_va, float32_t* v_vb, float32_t* v_vc, uint32_t v_len);

void dsp_process_fre_3_phase(struct pll_s* pll, struct meter_data_s* meterDat,
                             float32_t* bufVola, float32_t* bufVolB,
                             float32_t* bufVolC, uint16_t len);
void dsp_process_fre_1_phase(struct pll_s* pll, struct meter_data_s* meterDat, float32_t* buf,
                              uint16_t len);


void dsp_process_thd(struct phase_data_s* phaseDat, float32_t* data_buf,
                   float32_t* fft_buf, float32_t* mag_buf, uint16_t buf_len, float32_t* angle, float32_t* result);
#endif

#endif /* DSP_H */