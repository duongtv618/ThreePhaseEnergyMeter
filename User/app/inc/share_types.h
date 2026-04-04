#ifndef SHARE_TYPES_H
#define SHARE_TYPES_H

#include "app_cfg.h"
#include "arm_math.h"

typedef struct
{
    float32_t rmsVoltage;
    float32_t rmsCurrent;
    float32_t activePower;
    float32_t reactivePower;
    float32_t apparentPower;
    float32_t powerFactor;
    struct THD_s
    {
        float32_t voltage;
        float32_t current;
    } thd;
    
} phaseMeterData_t;

typedef struct
{
    phaseMeterData_t phaseData[METER_PHASE_COUNT];
    float32_t frequency;
} meterData_t;

#endif /* SHARE_TYPES_H */