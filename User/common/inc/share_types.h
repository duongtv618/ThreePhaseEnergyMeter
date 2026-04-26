#ifndef SHARE_TYPES_H
#define SHARE_TYPES_H

#include "app_cfg.h"
#include "arm_math.h"

#ifndef DSP_USE_FLOAT
typedef struct {
  float32_t rmsVoltage;
  float32_t rmsCurrent;
  float32_t activePower;
  float32_t reactivePower;
  float32_t apparentPower;
  float32_t powerFactor;
  struct THD_s {
    float32_t voltage;
    float32_t current;
  } thd;

} phaseMeterData_t;

typedef struct {
  phaseMeterData_t phaseData[METER_PHASE_COUNT];
  float32_t frequency;  // in Hz
  float32_t energyWs;   // in watt-seconds, can be converted to kWh later
} meterData_t;

typedef struct dspPhaseCoef_s {
  float32_t vCoef;
  float32_t iCoef;
  float32_t iPhaseShift;  // in degree, for current phase shift compensation
  float32_t vOffset;
  float32_t iOffset;
} dspPhaseCoef_t;

#else
struct THD_s {
  float32_t voltage;
  float32_t current;
};

struct phase_angle_s {
  float32_t voltage;
  float32_t current;
};

struct phase_data_s {
  float32_t rms_voltage;
  float32_t rms_current;;
  float32_t act_pwr;
  float32_t react_pwr;
  float32_t app_pwr;
  float32_t pf;
  struct THD_s thd;
  struct phase_angle_s angle;
};

struct vol_line_s {
  float32_t ab;
  float32_t bc;
  float32_t ca;
};

struct vol_line_coef_s {
  float32_t ab_gain;
  float32_t bc_gain;
  float32_t ca_gain;
  float32_t ab_offset;
  float32_t bc_offset;
  float32_t ca_offset;
};

struct meter_data_s {
  struct phase_data_s phase_data[METER_PHASE_COUNT];
  struct vol_line_s vol_line;
  float32_t frequency;  // in Hz
  float64_t energy_Ws;   // in watt-seconds, can be converted to kWh later
  int64_t energy_hWh;    // kilo watt hour
};

struct dsp_phase_coef_s {
  float32_t v_coef;
  float32_t i_coef;
  float32_t i_phase_shift;  // in degree, for current phase shift compensation
  float32_t v_offset;
  float32_t i_offset;
};
#endif

struct dsp_coef_s {
  struct dsp_phase_coef_s phase_coef[METER_PHASE_COUNT];
  struct vol_line_coef_s vll;
};

enum meter_state_e {
  METER_STATE_ERROR = -2,
  METER_STATE_WARNING = -1,
  METER_STATE_START = 0,
  METER_STATE_WAIT_FOR_STARTING_CURRENT,
  METER_STATE_WAIT_FOR_PLL_LOCK,
  METER_STATE_RUNNING_3PHASE,
  METER_STATE_RUNNING_PHASE_A,
  METER_STATE_RUNNING_PHASE_B,
  METER_STATE_RUNNING_PHASE_C,
};

#endif /* SHARE_TYPES_H */