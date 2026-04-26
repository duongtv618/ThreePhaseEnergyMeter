#ifndef PLL_H
#define PLL_H

#include "app_cfg.h"
#include "maf.h"
#include "arm_math.h"
#ifdef DSP_USE_Q31
struct pll_s {
  arm_pid_instance_q31 pi_instance;
  q31_t theta;
  q31_t frequency;
  q31_t nominal_dt;
  uint32_t fs;
};
#elifdef DSP_USE_FLOAT
struct pll_s{
  /** ARM PID instance for PID */
  arm_pid_instance_f32 pi_instance;

  /** SOGI struct */
  struct SOGI_s {
    float32_t alpha;
    float32_t beta;
    float32_t omega;
    float32_t ts;
  } SOGI;

  /** Timer struct */
  struct {
    uint32_t clock;
  } timer;

  /** Theta angel in degree */
  float32_t theta;
  /** Delta theta per sample */
  float32_t delta_theta;
  /** Norminal frequency */
  float32_t f0;
  /** Sampling frequency */
  float32_t fs;
  /** Current frequency */
  float32_t fre;
  /** Lock status */
  uint16_t locked;
  /** MAF for frequency */
  struct maf_s q_maf;
};
#endif

#ifdef DSP_USE_Q31
void pll_init_3p(struct pll_s* pll, float32_t nominal_f, uint32_t fs);
void pll_update_1p(struct pll_s* pll, q31_t vin, uint16_t Ts);
void pll_update_3p(struct pll_s* pll, q31_t vin_a, q31_t vin_b, q31_t vin_c,
                          uint16_t Ts);
#elifdef DSP_USE_FLOAT
void pll_init_3p(struct pll_s* pll, float32_t nominal_f, float32_t fs);
void pll_init_1p(struct pll_s* pll, float32_t f0, float32_t fs, uint32_t timerClock);
void pll_update_fs(struct pll_s* pll);
void pll_update_1p(struct pll_s* pll, float32_t vin);
void pll_update_3p(struct pll_s* pll, float32_t va, float32_t vb, float32_t vc);
uint32_t pll_is_locked(struct pll_s* pll);
#endif

#endif /* PLL_H */