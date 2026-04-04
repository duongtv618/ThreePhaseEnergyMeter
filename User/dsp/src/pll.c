#include "pll.h"
#include "app_cfg.h"
#include "arm_math.h"

#define Kp 50.0f
#define Ki 3000.0f

#define OMEGA_MIN (2.0f * PI * 45.0f)
#define OMEGA_MAX (2.0f * PI * 65.0f)

static inline void SOGI_Update(PLL_t *pll, float vin, float Ts);
static float32_t clamp(float32_t value, float min, float max);

static float32_t clamp(float32_t value, float min, float max)
{
    if (value > max)
        return max;
    else if (value < min)
        return min;
    return value;
}

static inline void SOGI_Update(PLL_t *pll, float vin, float Ts)
{
    float e = vin - pll->alpha;

    pll->alpha += Ts * (pll->omega * e - pll->omega * pll->beta);
    pll->beta += Ts * (pll->omega * pll->alpha);
}

void PLL_Init(PLL_t *pll)
{
    pll->theta = 0.0f;
    pll->omega = 2.0f * PI * METER_MAIN_FREQUENCY; // Initial frequency, can be tuned
    pll->integrator = 0.0f;
    pll->alpha = 0.0f;
    pll->beta = 0.0f;
}

void PLL_UpdateSinglePhase(PLL_t *pll, float vin, float Ts)
{
    // ===== SOGI =====
    SOGI_Update(pll, vin, Ts);

    // ===== sin/cos từ CMSIS =====
    float32_t sin_t, cos_t;
    arm_sin_cos_f32(pll->theta, &sin_t, &cos_t);

    // ===== Park transform =====
    float32_t d, q;
    arm_park_f32(pll->alpha, pll->beta, &d, &q, sin_t, cos_t);

    // ===== PI controller =====
    pll->integrator += Ki * q * Ts;
    pll->omega += (Kp * q + pll->integrator) * Ts;

    // ===== clamp =====
    if (pll->omega > OMEGA_MAX)
        pll->omega = OMEGA_MAX;
    else if (pll->omega < OMEGA_MIN)
        pll->omega = OMEGA_MIN;

    // ===== theta =====
    pll->theta += pll->omega * Ts;

    if (pll->theta > 2.0f * PI)
        pll->theta -= 2.0f * PI;
}

void PLL_UpdateThreePhase(PLL_t *pll, float vin_a, float vin_b, float vin_c, float Ts)
{
    float32_t alpha, beta;

    // ===== Clarke =====
    arm_clarke_f32(vin_a, vin_b, &alpha, &beta);

    pll->alpha = alpha;
    pll->beta = beta;

    // ===== sin/cos =====
    float32_t sin_t, cos_t;
    arm_sin_cos_f32(pll->theta, &sin_t, &cos_t);

    // ===== Park =====
    float32_t d, q;
    arm_park_f32(alpha, beta, &d, &q, sin_t, cos_t);

    // ===== PI =====
    pll->integrator += Ki * q * Ts;
    pll->omega += (Kp * q + pll->integrator) * Ts;

    // ===== Clamp =====
    pll->omega = clamp(pll->omega, OMEGA_MIN, OMEGA_MAX);

    // ===== Theta =====
    pll->theta += pll->omega * Ts;

    if (pll->theta > 2.0f * PI)
        pll->theta -= 2.0f * PI;
}