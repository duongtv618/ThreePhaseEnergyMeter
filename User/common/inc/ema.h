#ifndef EMA_H
#define EMA_H

#include "share_types.h"
#include "arm_math.h"

float32_t ema_get(float32_t in, float32_t last, float32_t alpha);

#endif