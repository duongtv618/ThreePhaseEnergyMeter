#include <string.h>
#include "maf.h"

#include <stdint.h>

void maf_init(struct maf_s* maf) {
  memset(maf->samples, 0, sizeof(maf->samples));
  maf->sample_count = 0;
  maf->sum = 0.0f;
}

float32_t maf_update(struct maf_s* maf, float32_t sample) {
    maf->sum -= maf->samples[maf->sample_count];
    maf->samples[maf->sample_count] = sample;
    maf->sum += sample;
    maf->sample_count++;
    if (maf->sample_count >= MAF_MAX_SAMPLES) maf->sample_count = 0;
    return maf->sum / MAF_MAX_SAMPLES;
}