#ifndef MAF_H
#define MAF_H

#include "arm_math.h"

#define MAF_MAX_SAMPLES 128

struct maf_s {
  float32_t samples[MAF_MAX_SAMPLES];
  uint32_t sample_count;
  float32_t sum;
};

void maf_init(struct maf_s* maf);
float32_t maf_update(struct maf_s* maf, float32_t sample);

#endif