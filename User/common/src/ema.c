#include "ema.h"

float32_t ema_get(float32_t in, float32_t last, float32_t alpha) {
    return alpha * in + (1.0f - alpha) * last;
}