#ifndef MOCK_H
#define MOCK_H

#include "app_cfg.h"
#include "arm_math.h"

// #define USE_RANDOM_NOISE 1u
// #define USE_HARMONIC_NOISE 1u
#ifdef USE_HARMONIC_NOISE
#define HARMONIC_ 2u
#define HARMONIC_AMP_PERCENT 10
#endif

typedef void (*mockSigCallback_t)(void);

void mockDMAInit(uint16_t *bufPointer, uint32_t length, uint8_t halfCpltInt, uint8_t cpltInt);
void mockSinGen(uint16_t *buffer, uint32_t length, uint8_t jumpSpace, uint32_t period, float32_t phaseShift);
void mockSignalGenInit(uint32_t periodMs, mockSigCallback_t htCallback, mockSigCallback_t tcCallback);

#endif // MOCK_H