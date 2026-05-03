#include "pll.h"

#include "app_cfg.h"
#include "arm_math.h"
#include "mock.h"
#include "serial_plot.h"

#define TWO_PI_Q31 2147483647
#define RAD_TO_DEG(x) (x * 180.0f / PI)
#define DEG_ROUND 360.0f

#define CALCULATE_KP 177.6f
#define CALCULATE_KI 15775.0f

#define TUNED_KP CALCULATE_KP
#define TUNED_KI CALCULATE_KI

#define TUNED_SOGI_K 0.8f

#define LOCK_THRESH_HOLD 0.05f
#define LOCK_SQUENCE (METER_SAMPLES_PER_CYCLE * 2)
// #define LOCK_SQUENCE 16

#define LPF_10HZ_ALPHA 0.009722f

#define ABS(x) (x < 0.0f ? (x * -1.0f) : x)

// struct dsogi_s {
//   float32_t b0, b2, a1, a2;
//   float32_t x1, x2, y1, y2;
//   float32_t q1, q2;
//   float32_t out_alpha, out_beta;
// };

static const float32_t OMEGA_STEP = 2.0f * PI / 128.0f;

static void pll_timer_update_arr(uint32_t newARR);
// static uint32_t PLL_TimerGetARR(void);

#ifdef DSP_USE_FLOAT
// static inline void DSOGI_update(struct dsogi_s* s, float32_t input);
static inline void SOGI_Update(struct pll_s* pll, float32_t vin, float32_t Ts);
// static void SOGI_Update_Coeffs(struct dsogi_s* s, float32_t omega_pll,
// float32_t fs);

/**
 * @brief SOGI update
 * @note SOGI stand for Second order generalized integrator
 * @param pll Phase lock loop instance
 * @param vin Voltage in [-1;1]
 * @param Ts T sample
 */
static inline void SOGI_Update(struct pll_s* pll, float32_t vin, float32_t Ts) {
  float32_t e = vin - pll->SOGI.alpha;  // Get error first
  e *= TUNED_SOGI_K;
  float32_t last_alpha = pll->SOGI.alpha;

  /** Why omega step is constant?
   * Cause I want the number of sample per sine cycle is constant
   * The SOGI output will be more stable -> frequency more stable
   */
  pll->SOGI.alpha += (e - pll->SOGI.beta) * OMEGA_STEP;  // Then cal v alpha
  pll->SOGI.beta += OMEGA_STEP * last_alpha;             // Then v beta
}

// static inline void DSOGI_update(struct dsogi_s* s, float32_t input) {
//   float32_t v_alpha = s->b0*input + s->b2*s->x2 - s->a1*s->y1 - s->a2*s->y2;
//   float32_t x = (s->b0 / 1.41421356f) * (s->b0 / 1.41421356f / 2.0f);
//   float32_t v_beta = (s->b0 * 0.5f * x) * (input + 2.0f * s->x1 + s->x2) -
//   s->a1 * s->q1 - s->a2 * s->q2;

//   s->x2 = s->x1;
//     s->x1 = input;

//     s->y2 = s->y1;
//     s->y1 = v_alpha;

//     s->q2 = s->q1;
//     s->q1 = v_beta;
//     s->out_alpha = v_alpha;
//     s->out_beta = v_beta;
// }

// static void SOGI_Update_Coeffs(struct dsogi_s* s, float32_t omega_pll,
// float32_t fs) {
//     float32_t Ts = 1.0f / fs;
//     float32_t k = 1.41421356f;
//     float32_t x = omega_pll * Ts;
//     float32_t x2 = x * x;
//     float32_t kx = k * x;

//     float32_t A = 4.0f + 2.0f * kx + x2;

//     s->b0 = (2.0f * kx) / A;
//     s->b2 = -(s->b0);
//     s->a1 = (2.0f * x2 - 8.0f) / A;
//     s->a2 = (4.0f - 2.0f * kx + x2) / A;
// }

/**
 * @brief
 *
 * @param in
 * @return float32_t
 */
static inline float32_t clamp(float32_t in) {
  while (in >= DEG_ROUND) in -= DEG_ROUND;
  while (in < 0.0f) in += DEG_ROUND;
  return in;
}
#endif

/**
 * @brief Set timer auto reload value
 *
 * @param newARR New auto reload value
 */
static void pll_timer_update_arr(uint32_t newARR) {
/** Update timer code goes here */
#ifdef USE_MOCK
  mock_timer_update_arr(newARR);
#endif
}

/**
 * @brief Return current timer auto reload value
 *
 * @return uint32_t Reload value
 */
// static uint32_t PLL_TimerGetARR(void) {
//   const uint32_t DEFAULT_TIMER_VAL = 123456;
//   return DEFAULT_TIMER_VAL;
// }

#ifdef DSP_USE_Q31
void PLL_Init(PLL3_t* pll, float32_t nominal_f, uint32_t fs) {
  pll->fs = fs;
  pll->theta = 0;

  // 1. Cấu hình bộ lọc vòng lặp (PI Controller)
  // Các hệ số này cần tuned tùy theo độ nhiễu của lưới
  pll->pi_instance.Kp = 0x00020000;  // Thử nghiệm giá trị nhỏ trước
  pll->pi_instance.Ki = 0x00005000;
  pll->pi_instance.Kd = 0;
  arm_pid_init_q31(&pll->pi_instance, 1);  // Reset bộ tích phân

  // 2. Tính toán bước nhảy góc mặc định (delta theta)
  // nominal_dt = (f * 2*PI / fs) -> quy đổi sang Q31
  pll->nominal_dt = (q31_t)((nominal_f / (float32_t)fs) * 2147483648.0f);
}

void PLL_UpdateSinglePhase(PLL_t* pll, q31_t vin, uint16_t Ts) {
  // // ===== SOGI =====
  // SOGI_Update(pll, vin, Ts);

  // // ===== sin/cos từ CMSIS =====
  // q31_t sin_t, cos_t;
  // arm_sin_cos_q31(pll->theta, &sin_t, &cos_t);

  // // ===== Park transform =====
  // q31_t d, q;
  // // arm_park_q31(pll->alpha, pll->beta, &d, &q, sin_t, cos_t);
  // curQ = q;

  // q31_t err = -q;

  // // q63_t i_next = (q63_t)pll->integrator + (((q63_t)err * Ki_pll) >> 31);
  // // pll->integrator = (q31_t)__SSAT(i_next, 31); // Saturation bảo vệ

  // // q31_t delta_omega = (q31_t)(((q63_t)err * Kp_pll) >> 31) +
  // pll->integrator;

  // // uint32_t current_step = OMEGA_NOMINAL_STEP + (uint32_t)delta_omega;

  // // pll->theta += current_step;

  // // 6. Tính toán tần số thực tế (Có thể đưa ra ngoài Task chậm hơn)
  // // f = (Step * Fs) / 2^32
  // // if ((pll->theta % 128) == 0) { // Giảm tải: tính tần số mỗi 128 mẫu
  //     // measured_freq = ((float32_t)current_step * 6400.0f) / 4294967296.0f;
  // }
}

void PLL_UpdateThreePhase(PLL_t* pll, q31_t va, q31_t vb, q31_t vc,
                          uint16_t Ts) {
  q31_t valpha, vbeta, vd, vq;
  q31_t s, c;

  // Bước 1: Clarke (3 pha -> 2 pha tĩnh)
  arm_clarke_q31(va, vb, &valpha, &vbeta);

  // Bước 2: Lấy Sin/Cos của góc theta hiện tại
  arm_sin_cos_q31(pll->theta, &s, &c);

  // Bước 3: Park (2 pha tĩnh -> 2 pha quay)
  arm_park_q31(valpha, vbeta, &vd, &vq, s, c);

  // Bước 4: Loop Filter (PI)
  // Mục tiêu: điều chỉnh delta_f sao cho vq -> 0
  // vq là sai số (error), đầu ra là độ lệch tần số (delta_f)
  // q31_t delta_f = arm_pid_q31(&pll->pi_instance, vq);
  q31_t delta_f = 0;

  // Bước 5: VCO (Tích phân góc)
  // Tần số thực tế = Tần số định mức + delta_f
  q31_t current_dt = pll->nominal_dt + delta_f;
  pll->theta += current_dt;  // Tự động tràn trong Q31 tương ứng 0 -> 2pi

  // Bước 6: Tính toán tần số thực tế (Hz) để hiển thị nếu cần
  // f = (current_dt / 2^31) * fs
  pll->frequency = current_dt;

  // return pll->theta;
}

#elifdef DSP_USE_FLOAT
void pll_init_3p(struct pll_s* pll, float32_t nominal_f, float32_t fs) {
  pll->fs = fs;
  pll->theta = 270.0f;
  pll->f0 = nominal_f;
  pll->fre = nominal_f;

  pll->pi_instance.Kp = TUNED_KP;
  pll->pi_instance.Ki = TUNED_KI / fs;
  pll->pi_instance.Kd = 0.0f;
  pll->locked = 0;
  arm_pid_init_f32(&pll->pi_instance, 1);

  pll->timer.clock = 100000000;

  pll->delta_theta = (360.0f * nominal_f) / fs;
}

/**
 * @brief Initialize phase lock loop instance for 1 phase input
 *
 * @param pll Phase lock loop instance
 * @param f0 Grid frequency (expectation)
 * @param fs Sampling frequency (Real)
 * @param timerClock ADC driving TIMER CLOCK in HZ
 */
void pll_init_1p(struct pll_s* pll, float32_t f0, float32_t fs,
                 uint32_t timerClock) {
  pll->delta_theta = f0 / fs * 360.0f;
  pll->fs = fs;
  pll->f0 = f0;
  pll->fre = f0;
  pll->theta = 270.0f;
  pll->SOGI.alpha = 0.0f;
  pll->SOGI.beta = 0.0f;
  pll->SOGI.omega = 2.0f * PI * f0;
  pll->SOGI.ts = 1.0f / fs;

  pll->locked = 0;

  pll->timer.clock = timerClock;

  pll->pi_instance.Kp = TUNED_KP;
  pll->pi_instance.Ki = TUNED_KI / fs;
  pll->pi_instance.Kd = 0.0f;
  arm_pid_init_f32(&pll->pi_instance, 1);
}

/**
 * @brief Update new sampling frequency
 *
 * @param pll Phase lock loop instance
 */
void pll_update_fs(struct pll_s* pll) {
  /** F grid = pll->fre */
  float32_t target_Ts = 1.0f / pll->fre / METER_SAMPLES_PER_CYCLE;

  /** Set Timer ARR */
  uint32_t newARR, lockBeneath, lockAbove;
  newARR = (float32_t)pll->timer.clock * target_Ts;
  if (newARR) newARR--;
  /**Lock timer ARR value in range from 45 - 65Hz */
  lockBeneath = pll->timer.clock * (1.0f / 45.0f / METER_SAMPLES_PER_CYCLE);
  lockAbove = pll->timer.clock * (1.0f / 65.0f / METER_SAMPLES_PER_CYCLE);
  if (newARR < lockAbove) newARR = lockBeneath;
  if (newARR > lockBeneath) newARR = lockAbove;
  pll_timer_update_arr(newARR);

  /** Update new fs */
  float32_t newFs;
  newFs = (float32_t)pll->timer.clock / (float32_t)(newARR + 1);
  pll->fs = newFs;

  /** Then SOGI */
  pll->delta_theta = pll->fre / newFs * 360.0f;
  pll->f0 = pll->fre;
}

/**
 * @brief Plase lock loop update singele phase
 *
 * @param pll Phase lock loop instance
 * @param vin Voltage in [-1;1]
 */
void pll_update_1p(struct pll_s* pll, float32_t vin) {
  float32_t sin, cos, d, q, delta_omega;

  SOGI_Update(pll, vin, pll->SOGI.ts);  // Update SOGI first

  arm_sin_cos_f32(pll->theta, &sin, &cos);  // Calculate sin code
  arm_park_f32(pll->SOGI.alpha, pll->SOGI.beta, &d, &q, sin,
               cos);  // Park transform to get d,q
  delta_omega = arm_pid_f32(&pll->pi_instance, q);
  delta_omega /= pll->fs;  // Convert to deg per sample
  delta_omega = RAD_TO_DEG(delta_omega);
  pll->theta += (pll->delta_theta + delta_omega);

  if (ABS(q) < LOCK_THRESH_HOLD)
    pll->locked = pll->locked < LOCK_SQUENCE ? pll->locked + 1 : pll->locked;
  else
    pll->locked = 0;

  pll->theta = clamp(pll->theta);  // Clamp to range [0. 360];

  float32_t freq = (pll->delta_theta + delta_omega) * pll->fs / DEG_ROUND;
  pll->fre = (0.99f * pll->fre) + (0.01f * freq);
}

/**
 * @brief Update phase lock loop with 3 phase input
 * @note Voltage value in range [-1,1]
 *
 * @param pll Phase lock loop instance
 * @param va Voltage A
 * @param vb Voltage B
 * @param vc Voltage C
 */
void pll_update_3p(struct pll_s* pll, float32_t va, float32_t vb,
                   float32_t vc) {
  float32_t alpha, beta, d, q, sin, cos, delta;

  /** Find normal point for phase balance */
  float32_t van, vbn, vcom;
  vcom = (va + vb + vc) / 3.0f;
  van = va - vcom;
  vbn = vb - vcom;

  /** Put balance input to clarke transform */
  arm_clarke_f32(van, vbn, &alpha, &beta);
  /** Sin cos calculation */
  arm_sin_cos_f32(pll->theta, &sin, &cos);  // Theta in degree
  /** After park transform we got d, q */
  arm_park_f32(alpha, beta, &d, &q, sin, cos);
  /** put q to maf for high order harmonic filter */
  // q = maf_update(&pll->q_maf, q);
  /** delta after pid, in deg per second */
  delta = arm_pid_f32(&pll->pi_instance, q);
  // struct serial_plot_point_s point = {"q"};
  // serial_plot_write_point(point, q);
  // delta = RAD_TO_DEG(delta);
  /** Convert to deg per sample */
  delta /= pll->fs;
  delta = RAD_TO_DEG(delta);
  pll->theta += (pll->delta_theta + delta);

  if (fabsf(q) < LOCK_THRESH_HOLD)
    pll->locked = pll->locked < LOCK_SQUENCE ? pll->locked + 1 : pll->locked;
  // pll->locked = 1;
  else
    pll->locked = 0;

  /** Clamp to range [0;360] */
  pll->theta = clamp(pll->theta);

  /** Current estimated frequency */
  float32_t freq = (pll->delta_theta + delta) * pll->fs / DEG_ROUND;
  /** Add to LPF for smooth freqency output, fc = 10Hz */
  // pll->fre = (0.99f * pll->fre) + (0.01f * freq);
  pll->fre = freq;
}

/**
 * @brief Check if phase lock loop is locked
 *
 * @param pll PLL_t instance
 * @return uint32_t
 * 1 if the PLL is locked
 * 0 if the PLL is not locked
 */
uint32_t pll_is_locked(struct pll_s* pll) {
  return (pll->locked >= LOCK_SQUENCE);
}
#endif