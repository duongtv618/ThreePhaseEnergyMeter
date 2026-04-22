#include "calib.h"

#include "app_cfg.h"

#ifndef DSP_USE_FLOAT
#define DEFAULT_VOLTAGE_RMS 220
#define DEFAULT_CURRENT_RMS 5
#define MAX_VOLTAGE_RMS 250
#define MAX_CURRENT_RMS 6
#define SQRT2_SCALED 1414
#define ADC_RESOLUTION 4096  // Assuming 12-bit ADC
#define MAX_VOLTAGE_RMS_SCALED_MV (MAX_VOLTAGE_RMS * 1000)  // mV
#define MAX_CURRENT_RMS_SCALED_MA (MAX_CURRENT_RMS * 1000)  // mA
#define PEAK_VOLTAGE_SCALED_MV \
  (MAX_VOLTAGE_RMS_SCALED_MV * SQRT2_SCALED)  // Peak voltage in mV
#define PEAK_CURRENT_SCALED_MA \
  (MAX_CURRENT_RMS_SCALED_MA * SQRT2_SCALED)  // Peak current in mA
#define DEFAULT_COEF_VOLTAGE                        \
  (PEAK_VOLTAGE_SCALED_MV / (ADC_RESOLUTION << 3) / \
   1000)  // Coefficient to convert ADC value to mV, considering the shift left
          // by 4 in adc_sample.c
#define DEFAULT_COEF_CURRENT                        \
  (PEAK_CURRENT_SCALED_MA / (ADC_RESOLUTION << 3) / \
   1000)  // Coefficient to convert ADC value to mA, considering the shift left
          // by 4 in adc_sample.c

#define DEFAULT_CURRENT_PHASE_SHIFT_DEGREE 0.0f
#define DEFAULT_ADC_OFFSET_VALUE 2048
#else
#define DEFAULT_VOLTAGE_RMS 220.0f
#define DEFAULT_CURRENT_RMS 5.0f
#define MAX_VOLTAGE_RMS 250.0f
#define MAX_CURRENT_RMS 6.0f
#define SQRT2_SCALED 1.4142135623731f
#define ADC_RESOLUTION 4095.0f  // Assuming 12-bit ADC
#define MAX_VOLTAGE_RMS_SCALED_MV (MAX_VOLTAGE_RMS * 1000.0f)  // mV
#define MAX_CURRENT_RMS_SCALED_MA (MAX_CURRENT_RMS * 1000.0f)  // mA
#define PEAK_VOLTAGE_SCALED_MV \
  (MAX_VOLTAGE_RMS_SCALED_MV * SQRT2_SCALED)  // Peak voltage in mV
#define PEAK_CURRENT_SCALED_MA \
  (MAX_CURRENT_RMS_SCALED_MA * SQRT2_SCALED)  // Peak current in mA
#define DEFAULT_COEF_VOLTAGE (MAX_VOLTAGE_RMS * SQRT2_SCALED)
#define DEFAULT_COEF_CURRENT (MAX_CURRENT_RMS * SQRT2_SCALED)

#define START_VOLTAGE 85.0f
#define START_CURRENT 0.015f

#define DEFAULT_CURRENT_PHASE_SHIFT_DEGREE 0.0f
#define DEFAULT_ADC_OFFSET_VALUE 2048.0f
#endif

const struct calib_starting_current_voltage cg_start_current_voltage = {
    .start_current = START_CURRENT, .start_voltage = START_VOLTAGE};

static const struct dsp_coef_s default_dsp_coef = {
    .phase_coef = {{.v_coef = DEFAULT_COEF_VOLTAGE,
                   .i_coef = DEFAULT_COEF_CURRENT,
                   .i_phase_shift = DEFAULT_CURRENT_PHASE_SHIFT_DEGREE,
                   .v_offset = DEFAULT_ADC_OFFSET_VALUE,
                   .i_offset = DEFAULT_ADC_OFFSET_VALUE},
                  {.v_coef = DEFAULT_COEF_VOLTAGE,
                   .i_coef = DEFAULT_COEF_CURRENT,
                   .i_phase_shift = DEFAULT_CURRENT_PHASE_SHIFT_DEGREE,
                   .v_offset = DEFAULT_ADC_OFFSET_VALUE,
                   .i_offset = DEFAULT_ADC_OFFSET_VALUE},
                  {.v_coef = DEFAULT_COEF_VOLTAGE,
                   .i_coef = DEFAULT_COEF_CURRENT,
                   .i_phase_shift = DEFAULT_CURRENT_PHASE_SHIFT_DEGREE,
                   .v_offset = DEFAULT_ADC_OFFSET_VALUE,
                   .i_offset = DEFAULT_ADC_OFFSET_VALUE}},
      .vll = {.ab = DEFAULT_COEF_VOLTAGE,
              .bc = DEFAULT_COEF_VOLTAGE,
              .ca = DEFAULT_COEF_VOLTAGE}};

const struct dsp_coef_s calib_get_dsp_coef(void) { return default_dsp_coef; }

const struct calib_starting_current_voltage calib_get_threshold(void) {
  return cg_start_current_voltage;
}