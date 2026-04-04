#ifndef DSP_H
#define DSP_H

#include "share_types.h"

void dspProcess(phaseMeterData_t *meterData, float32_t volBuffer[METER_SAMPLES_PER_CYCLE], float32_t curBuffer[METER_SAMPLES_PER_CYCLE]);

#endif /* DSP_H */