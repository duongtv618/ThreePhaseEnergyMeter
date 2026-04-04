#ifndef PLL_H
#define PLL_H

#include "arm_math.h"

typedef struct
{
    float32_t theta;
    float32_t omega;
    float32_t integrator;

    float32_t alpha;
    float32_t beta;

} PLL_t;

typedef PLL_t PLL3_t;

void PLL_Init(PLL_t *pll);
void PLL_UpdateSinglePhase(PLL_t *pll, float vin, float Ts);
void PLL_UpdateThreePhase(PLL_t *pll, float vin_a, float vin_b, float vin_c, float Ts);

#endif /* PLL_H */