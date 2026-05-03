/**
 * @file mock.c
 * @author your name (you@domain.com)
 * @brief Mock signal generation functions, simulate ADC data for testing DSP
 * processing code without real ADC hardware.
 * @version 0.1
 * @date 2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "mock.h"
/* ---- x86 test build: swap hardware headers for stubs ---- */
#ifdef ARM_MATH_HOST
  #include "mock_hw_stub.h"
#else
  #include "FreeRTOS.h"
  #include "stm32f4xx.h"
  #include "task.h"
#endif

#define DEFAULT_TIMER_CLOCK 100000000

static struct mock_dma_s {
  void(*  htCallback)();
  void(*  tcCallback)();
  uint32_t signalPeriod;

  uint16_t* buf_pointer;
  uint16_t* start_ptr;
  uint32_t length;
  enum { HT = 0u, TC = 1u } next_int;
} mock_DMA_cfg;

static struct mock_sin_s {
  float32_t f0;
  float32_t fs;
  float32_t f0_target;
  float32_t step;
} mock_sin;

static void _mock_task(void* pvParameters);
static StackType_t mock_task_stack[APP_DEFAULT_TASK_STACK_SIZE];
static StaticTask_t mock_task_buffer;
static void clamp(float32_t* x, float32_t ceil, float32_t floor);
static int32_t get_noise_val(void);
static float32_t harmonic_noise(float32_t n, float32_t omega);


static float32_t harmonic_noise(float32_t n, float32_t omega) {
  float32_t ret;
  #ifdef USE_HARMONIC_NOISE
  ret = HARMONIC_AMP * MOCK_ADC_MIDDLE_POINT * arm_sin_f32(2.0f * PI * n * omega);
  #else
  ret = 0.0f;
  #endif
  return ret;
}

static int32_t get_noise_val(void) {
#if USE_RANDOM_NOISE
  return (2 - (int32_t)(DWT->CYCCNT % 4));
#else
  return 0;
#endif
}

static void clamp(float32_t* x, float32_t ceil, float32_t floor) {
  if (*x < ceil) *x = ceil;
  if (*x > floor) *x = floor;
}

/**
 * @brief Generates mock sine wave data for ADC simulation
 *
 * @param buffer Destination buffer to store the generated sine wave data
 * @param length Length of the buffer (number of samples)
 * @param jump_space Space between samples in the buffer
 * @param f0 Frequency of the sine wave
 * @param fs Sampling frequency
 * @param phase_shift Phase shift of the sine wave in degrees
 */
void mock_sin_gen(uint16_t* buffer, uint32_t length, uint8_t jump_space,
                float32_t f0, float32_t fs, float32_t phase_shift) {
  float32_t ts_delta = f0 / fs;
  float32_t ts = 0.0f;
  float32_t buf_val;
  for (uint32_t i = 0, pos = 0; i < length; i += jump_space, pos++) {
/** ADC range is from 0 to 4095 so middle point is 2047 */
    buf_val = (MOCK_ADC_MIDDLE_POINT * AMPTITUE_PERCENT *
                       arm_sin_f32(2.0f * PI * ts + phase_shift * PI / 180.0f) +
                   MOCK_ADC_MIDDLE_POINT);
    ts += ts_delta;
    /** Truncate to 12-bit */
    clamp(&buf_val, 0.0f, (float32_t)MOCK_ADC_MAX);
    buffer[i] = (uint16_t)buf_val;
  }
}

/**
 * @brief Generate sine wave buffer
 * @note Output will be va,ia,vb,ib,vc,ic
 * @param buf is buffer
 * @param bufLen is the length of buffer
 * @param f0 is grid frequenncy
 * @param fs is sampling frequency
 * @param iPhaseShift is current phase shift
 */
void mock_sin_gen_ui_3_p(uint16_t* buf, uint32_t len, float32_t f0,
                            float32_t fs, float32_t i_phase_shift) {
  static float32_t omega = 0.0f;
  float32_t delta_omega = f0 * 2.0f * PI / fs;
  uint32_t couter = len / METER_PHASE_COUNT / METER_SIGNAL_COUNT;
  float32_t va, ia, vb, ib, vc, ic;
  for (size_t i = 0; i < couter; i++) {
    va = (MOCK_ADC_MIDDLE_POINT * AMPTITUE_PERCENT *
                   arm_sin_f32(omega + 0.0f * PI / 180.0f) +
               MOCK_ADC_MIDDLE_POINT) + harmonic_noise(HARMONIC_, omega)
                + get_noise_val() + harmonic_noise(HARMONIC_ * 3.0f, omega);
    ia = (MOCK_ADC_MIDDLE_POINT * AMPTITUE_PERCENT *
                   arm_sin_f32(omega + i_phase_shift * PI / 180.0f) +
               MOCK_ADC_MIDDLE_POINT) + harmonic_noise(HARMONIC_, omega)
                + get_noise_val() + harmonic_noise(HARMONIC_ * 3.0f, omega);
    vb = (MOCK_ADC_MIDDLE_POINT * AMPTITUE_PERCENT *
                   arm_sin_f32(omega - 120.0f * PI / 180.0f) +
               MOCK_ADC_MIDDLE_POINT) + harmonic_noise(HARMONIC_, omega)
               + (float32_t)get_noise_val() + harmonic_noise(HARMONIC_ * 3.0f, omega);
    ib = (MOCK_ADC_MIDDLE_POINT * AMPTITUE_PERCENT *
                   arm_sin_f32(omega - (120.0f - i_phase_shift) * PI / 180.0f) +
               MOCK_ADC_MIDDLE_POINT) + harmonic_noise(HARMONIC_, omega)
               + (float32_t)get_noise_val() + harmonic_noise(HARMONIC_ * 3.0f, omega);
    vc = (MOCK_ADC_MIDDLE_POINT * AMPTITUE_PERCENT *
                   arm_sin_f32(omega + 120.0f * PI / 180.0f) +
               MOCK_ADC_MIDDLE_POINT) + harmonic_noise(HARMONIC_, omega) +
              (float32_t)get_noise_val() + harmonic_noise(HARMONIC_ * 3.0f, omega);
    ic = (MOCK_ADC_MIDDLE_POINT * AMPTITUE_PERCENT *
                   arm_sin_f32(omega + (120.0f + i_phase_shift) * PI / 180.0f) +
               MOCK_ADC_MIDDLE_POINT) + harmonic_noise(HARMONIC_, omega) +
              (float32_t)get_noise_val() + harmonic_noise(HARMONIC_ * 3.0f, omega);
    omega += delta_omega;
    if (omega > PI) omega -= (2.0f * PI);

    /** Truncate to 12-bit */
    clamp(&va, 0.0f, (float32_t)MOCK_ADC_MAX);
    clamp(&vb, 0.0f, (float32_t)MOCK_ADC_MAX);
    clamp(&vc, 0.0f, (float32_t)MOCK_ADC_MAX);
    clamp(&ia, 0.0f, (float32_t)MOCK_ADC_MAX);
    clamp(&ib, 0.0f, (float32_t)MOCK_ADC_MAX);
    clamp(&ic, 0.0f, (float32_t)MOCK_ADC_MAX);

    buf[i * METER_PHASE_COUNT * METER_SIGNAL_COUNT + 0] = (uint16_t)va;
    buf[i * METER_PHASE_COUNT * METER_SIGNAL_COUNT + 1] = (uint16_t)ia;
    buf[i * METER_PHASE_COUNT * METER_SIGNAL_COUNT + 2] = (uint16_t)vb;
    buf[i * METER_PHASE_COUNT * METER_SIGNAL_COUNT + 3] = (uint16_t)ib;
    buf[i * METER_PHASE_COUNT * METER_SIGNAL_COUNT + 4] = (uint16_t)vc;
    buf[i * METER_PHASE_COUNT * METER_SIGNAL_COUNT + 5] = (uint16_t)ic;
  }
}

/**
 * @brief Init FreeRTOS task for generating mock signal data, and the callback
 * will be called after each period of signal generation, so that we can update
 * the signal data for testing DSP processing code without real ADC data.
 *
 * @param periodMs Period in milliseconds
 * @param callback Callback function to be called after each period of signal
 * generation, can be NULL if not needed
 */
void mock_sin_gen_init(float32_t f0, float32_t fs, void (*htCallback)(),
                       void (* tcCallback)()) {
  if (htCallback) {
    mock_DMA_cfg.htCallback = htCallback;
  }

  if (tcCallback) {
    mock_DMA_cfg.tcCallback = tcCallback;
  }

  mock_sin.f0 = f0;
  mock_sin.fs = fs;
  mock_sin.f0_target = f0;
  mock_sin.step = 0.0f;

  mock_DMA_cfg.signalPeriod = (uint32_t)(1000.0f / f0);

  xTaskCreateStatic(_mock_task, "MockSignalGen", APP_DEFAULT_TASK_STACK_SIZE,
                    NULL, APP_DEFAULT_TASK_PRIORITY, mock_task_stack,
                    &mock_task_buffer);
}

/**
 * @brief Mock task, call callback after period of time, and then delay until
 * next period Should be used for generating mock signal data, and the callback
 * should be used for updating the signal data, so that we can test the DSP
 * processing code without real ADC data.
 *
 * @param pvParameters Unused parameter for task, can be NULL
 */
static void _mock_task(void* pvParameters) {
  TickType_t lastWakeTime = xTaskGetTickCount();
  while (1) {
    if (mock_sin.f0 > mock_sin.f0_target) {
      mock_sin.f0 -= mock_sin.step;
    } else if (mock_sin.f0 < mock_sin.f0_target) {
      mock_sin.f0 += mock_sin.step;
    } else {
    }

    switch (mock_DMA_cfg.next_int) {
      case HT: {
        mock_DMA_cfg.start_ptr = mock_DMA_cfg.buf_pointer;
        mock_sin_gen_ui_3_p(mock_DMA_cfg.start_ptr, mock_DMA_cfg.length / 2,
                               mock_sin.f0, mock_sin.fs, 0.0f);
        if (mock_DMA_cfg.htCallback) mock_DMA_cfg.htCallback();
        mock_DMA_cfg.next_int = TC;
      } break;

      case TC: {
        mock_DMA_cfg.start_ptr =
        mock_DMA_cfg.buf_pointer + mock_DMA_cfg.length / 2;
        mock_sin_gen_ui_3_p(mock_DMA_cfg.start_ptr, mock_DMA_cfg.length / 2,
                               mock_sin.f0, mock_sin.fs, 0.0f);
        if (mock_DMA_cfg.tcCallback) mock_DMA_cfg.tcCallback();
        mock_DMA_cfg.next_int = HT;
      } break;

      default:
        break;
    }

    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(mock_DMA_cfg.signalPeriod));
  }
}

void mock_DMA_init(uint16_t* buf_pointer, uint32_t length, uint8_t halfCpltInt,
                 uint8_t cpltInt) {
  (void)halfCpltInt;
  (void)cpltInt;
  mock_DMA_cfg.buf_pointer = buf_pointer;
  mock_DMA_cfg.length = length;
}

void mock_timer_update_arr(uint32_t arr) {
  mock_sin.fs = (float32_t)DEFAULT_TIMER_CLOCK / (float32_t)arr;
}

void mock_change_frequency(float32_t targetF, float32_t step) {
  mock_sin.f0_target = targetF;
  mock_sin.step = step;
  mock_DMA_cfg.signalPeriod = (uint32_t)1000.0f / targetF;
}