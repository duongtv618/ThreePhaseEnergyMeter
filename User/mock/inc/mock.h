#ifndef MOCK_H
#define MOCK_H

#include "app_cfg.h"
#include "arm_math.h"

#define USE_RANDOM_NOISE 1u
#define USE_HARMONIC_NOISE 1u
#define HARMONIC_ 3.0f
#define HARMONIC_AMP 0.2f

#define AMPTITUE_SCALE 88.0f
#define AMPTITUE_PERCENT (AMPTITUE_SCALE / 100.0f)
#define MOCK_ADC_MIDDLE_POINT 2048.0f
#define MOCK_ADC_MAX (MOCK_ADC_MIDDLE_POINT * 2.0f)

#define CURRENT_PHASE_SHIFT (-5.0f)//Lead

void mock_DMA_init(uint16_t* bufPointer, uint32_t length, uint8_t halfCpltInt,
                 uint8_t cpltInt);
void mock_sin_gen(uint16_t* buffer, uint32_t length, uint8_t jumpSpace,
                float32_t f0, float32_t fs, float32_t phaseShift);
void mock_sin_gen_ui_3_p(uint16_t* buf, uint32_t bufLen, float32_t f0,
                            float32_t fs, float32_t iPhaseShift);
void mock_sin_gen_init(float32_t f0, float32_t fs, void (*htCallback)(),
                       void (* tcCallback)());
void mock_timer_update_arr(uint32_t arr);
void mock_change_frequency(float32_t targetF, float32_t step);

#endif  // MOCK_H