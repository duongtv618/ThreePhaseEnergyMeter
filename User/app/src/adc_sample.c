/**
 * @file adc_sample.c
 * @author your name (you@domain.com)
 * @brief ADC sampling and processing task implementation
 * @note Use q15_t for more accurate calculations in DSP processing, especially
 * for power calculations, to avoid issues with floating-point precision and
 * negative values under square root. Energy calculation can be done in
 * float32_t, but we need to be careful with the precision and accumulation
 * error, so we can use a separate variable to accumulate energy in float32_t
 * and only convert to uint64_t when updating the meter_data structure.
 * @version 0.1
 * @date 2026-04-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "adc_sample.h"

#include "FreeRTOS.h"
#include "app_cfg.h"
#include "arm_math.h"
#include "calib.h"
#include "deadline_monitor.h"
#include "dsp.h"
#include "led_blink.h"
#include "main.h"
#include "mock.h"
#include "pll.h"
#include "share_data.h"
#include "share_types.h"
#include "task.h"
#include "uart_dma.h"

#define pulse_trigger() led_trigger()

#define ABS(x) (x < 0.0f ? (x * -1.0f) : x)

#define HT_CALLBACK_VAL 0u
#define TC_CALLBACK_VAL 1u

#ifdef DSP_USE_Q31
#define BIT_SHIFT_SCALE_Q31 19
#endif

#define ADC_TIMER_CLOCK 100000000

#define PHASE_A_POS 0u
#define PHASE_B_POS 1u
#define PHASE_C_POS 2u
#define VOLTAGE_POS 0u
#define CURRENT_POS 1u

#define WS_TO_HWH 36000.0

#ifndef MOCK_H
// #define ADC_MIDDLE_POINT 2048
#else
// #define ADC_MIDDLE_POINT MOCK_ADC_MIDDLE_POINT
#define ADC_MIDDLE_POINT 0.0f
#define ADC_EXPECT_MAX_PEAK 2048.0f
#endif

enum phase_on_e { OFF = 0, ON = 1 };

const char* phase_lost_msg = "Phase lost \r\n";
const char* warning_msg = "Phase counter not normally\r\nPhase counter: ";

static struct adc_task_s {
  StackType_t stack[APP_DEFAULT_TASK_STACK_SIZE];
  StaticTask_t buffer;
  TaskHandle_t handle;
} adc_task;

static struct task_health_status adc_task_health;

static struct meter_data_s meter_data = {
    .energy_hWh = 0.0f,
    .energy_Ws = 0.0f,
};

struct fft_buffer_s {
  float32_t data_buf[FFT_BUF_SIZE];
  float32_t fft_buf[FFT_BUF_SIZE];
  float32_t mag_buf[FFT_BUF_SIZE / 2];
};

static struct thd_buf_s {
  struct fft_buffer_s voltage;
  struct fft_buffer_s current;
  uint16_t counter;
} thd_buf[METER_PHASE_COUNT];

/** Normaly voltage and current value will be subtracted with middle point, but
 * we still need to store the raw ADC value for later processing, so we can just
 * store the raw value in adc_buffer and do the subtraction in processing stage.
 * 2 is for half and full conversion, because we use DMA in circular mode, so we
 * need to store both half and full conversion data. Layout in memmory is like
 * this: Ua Ia Ub Ib Uc Ic Ua Ia Ub Ib Uc Ic ... for each cycle, and we have
 * METER_SAMPLES_PER_CYCLE samples for each phase.
 */
static uint16_t adc_buffer[METER_SAMPLES_PER_CYCLE * 2u][METER_PHASE_COUNT]
                          [METER_SIGNAL_COUNT];

#ifdef DSP_USE_FLOAT
static struct dsp_dat_buf_s {
  float32_t vol_buf[METER_PHASE_COUNT][METER_SAMPLES_PER_CYCLE];
  float32_t cur_buf[METER_PHASE_COUNT][METER_SAMPLES_PER_CYCLE];
  struct pll_s pll_1p;
  struct pll_s pll_3p;
} dsp_dat_buf;
#endif

static enum phase_on_e on_phase[3] = {OFF, OFF, OFF};
static uint32_t process_time = 0u;
static struct dsp_coef_s dsp_coef;

static void energy_accum(struct meter_data_s* dat, enum phase_on_e phase_a,
                         enum phase_on_e phase_b, enum phase_on_e phase_c);

void adc_sample_ready(void);
void adc_sample_task(void* pvParameters);
void adc_half_conv_cplt_callback(void);
void adc_full_conv_cplt_callback(void);
void adc_DMA_init(void);

void adc_sample_init(void) {
  /** Create task */
  adc_task.handle = xTaskCreateStatic(
      adc_sample_task, "ADCSample", APP_DEFAULT_TASK_STACK_SIZE, NULL,
      APP_DEFAULT_TASK_PRIORITY, adc_task.stack, &adc_task.buffer);
  (void)dm_register(&adc_task_health, DM_DEADLINE_ADC_SAMPLE_TASK_US);
}

void adc_sample_task(void* pvParameters) {
  /* ADC initialization code goes here */
  adc_DMA_init();
  struct calib_starting_current_voltage threshhold = calib_get_threshold();
  calib_init();
  pll_init_1p(&dsp_dat_buf.pll_1p, (float32_t)METER_MAIN_FREQUENCY,
              (float32_t)METER_MAIN_FREQUENCY * METER_SAMPLES_PER_CYCLE,
              ADC_TIMER_CLOCK);

  pll_init_3p(&dsp_dat_buf.pll_3p, METER_MAIN_FREQUENCY,
              METER_SAMPLES_PER_CYCLE * METER_MAIN_FREQUENCY);

  /** If we want to use mock data, we can init the mock signal generator here */
#ifdef DATA_USE_MOCK_DATA
  mock_sin_gen_init((float32_t)METER_START_FREQUENCY,
                    (float32_t)METER_MAIN_FREQUENCY * METER_SAMPLES_PER_CYCLE,
                    adc_half_conv_cplt_callback, adc_full_conv_cplt_callback);
#endif

  while (1) {
    dsp_coef = calib_get_dsp_coef();

    uint32_t noti_val;
    uint16_t (*adc_buf_ptr)[METER_PHASE_COUNT][METER_SIGNAL_COUNT];
    xTaskNotifyWait(1, 1, &noti_val,
                    portMAX_DELAY);  // Wait for HT or TC notification

    if (noti_val == HT_CALLBACK_VAL) {
      adc_buf_ptr = &adc_buffer[0];
    } else if (noti_val == TC_CALLBACK_VAL) {
      adc_buf_ptr = &adc_buffer[METER_SAMPLES_PER_CYCLE];
    } else {
      while (1);  // Err here
    }

    uint32_t start_cycles = DWT->CYCCNT;

#ifdef DSP_USE_FLOAT
    /** Take processible data from adc buffer */
    for (size_t i = 0; i < METER_SAMPLES_PER_CYCLE; i++) {
      for (size_t j = 0; j < METER_PHASE_COUNT; j++) {
        dsp_dat_buf.vol_buf[j][i] = (float32_t)adc_buf_ptr[i][j][VOLTAGE_POS] -
                                    (float32_t)dsp_coef.phase_coef[j].v_offset;
        dsp_dat_buf.cur_buf[j][i] = (float32_t)adc_buf_ptr[i][j][CURRENT_POS] -
                                    (float32_t)dsp_coef.phase_coef[j].i_offset;
      }
    }
    /** Convert adc value to [-1:1] */
    const float32_t to_per_unit = 1.0f / ADC_EXPECT_MAX_PEAK;

    /** To per unit */
    for (size_t i = 0; i < METER_PHASE_COUNT; i++) {
      arm_scale_f32(&dsp_dat_buf.vol_buf[i][0], to_per_unit,
                    &dsp_dat_buf.vol_buf[i][0], METER_SAMPLES_PER_CYCLE);
      arm_scale_f32(&dsp_dat_buf.cur_buf[i][0], to_per_unit,
                    &dsp_dat_buf.cur_buf[i][0], METER_SAMPLES_PER_CYCLE);
    }

    for (size_t i = 0; i < METER_PHASE_COUNT; i++) {
      if (thd_buf[i].counter < FFT_BUF_SIZE) {
        for (size_t j = 0; j < METER_SAMPLES_PER_CYCLE; j++) {
          thd_buf[i].voltage.data_buf[thd_buf[i].counter] =
              dsp_dat_buf.vol_buf[i][j];
          thd_buf[i].current.data_buf[thd_buf[i].counter++] =
              dsp_dat_buf.cur_buf[i][j];
        }
      } else {
        thd_buf[i].counter = 0;

        dsp_process_thd(&meter_data.phase_data[i], thd_buf[i].voltage.data_buf,
                        thd_buf[i].voltage.fft_buf, thd_buf[i].voltage.mag_buf,
                        FFT_BUF_SIZE, &meter_data.phase_data[i].angle.voltage,
                        &meter_data.phase_data[i].thd.voltage);
        dsp_process_thd(&meter_data.phase_data[i], thd_buf[i].current.data_buf,
                        thd_buf[i].current.fft_buf, thd_buf[i].current.mag_buf,
                        FFT_BUF_SIZE, &meter_data.phase_data[i].angle.current,
                        &meter_data.phase_data[i].thd.current);
      }
    }

    /** Calculate phase */
    for (size_t i = 0; i < METER_PHASE_COUNT; i++) {
      dsp_process_phase(&meter_data.phase_data[i], &dsp_dat_buf.vol_buf[i][0],
                        &dsp_dat_buf.cur_buf[i][0], dsp_coef.phase_coef[i]);
    }

    dsp_process_vol_line(
        &meter_data, &dsp_coef, &dsp_dat_buf.vol_buf[PHASE_A_POS][0],
        &dsp_dat_buf.vol_buf[PHASE_B_POS][0],
        &dsp_dat_buf.vol_buf[PHASE_C_POS][0], METER_SAMPLES_PER_CYCLE);

    /** Phase lock loop works good, but there is still 0.017 diff from origin
     * frequency, cause of 12bit ADC resolution */
    // dspProcessFreSinglePhase(&dsp_dat_buf.pll1P, &meter_data,
    //                          &dsp_dat_buf.vol_buf[PHASE_A_POS][0],
    //                          METER_SAMPLES_PER_CYCLE);

    /** 3 phase pll works good, err at 60hz:0.007 max, after change frequency
     * from 60hz to 50hz, err is 0.001, so we can use this method */
    dsp_process_fre_3_phase(
        &dsp_dat_buf.pll_3p, &meter_data, &dsp_dat_buf.vol_buf[0][0],
        &dsp_dat_buf.vol_buf[1][0], &dsp_dat_buf.vol_buf[2][0],
        METER_SAMPLES_PER_CYCLE);
#endif
    if (pll_is_locked(&dsp_dat_buf.pll_3p) == 0) {
      shdat_set_meter_state(METER_STATE_WAIT_FOR_PLL_LOCK);
    }

    uint8_t on_phase_counter = 0;
    /** Check running condition, which phase is on */
    for (size_t i = 0; i < METER_PHASE_COUNT; i++) {
      if ((meter_data.phase_data[i].rms_voltage > threshhold.start_voltage) &&
          (meter_data.phase_data[i].rms_current > threshhold.start_current)) {
        /** Phase i is ON */
        on_phase[i] = ON;
        on_phase_counter++;
      }
    }

    switch (on_phase_counter) {
      case METER_PHASE_COUNT:
        /** All phase are on */
        if (shdat_get_meter_current_state() ==
            METER_STATE_WAIT_FOR_STARTING_CURRENT)
          shdat_set_meter_state(METER_STATE_WAIT_FOR_PLL_LOCK);
        break;

      case METER_PHASE_COUNT - 1u:
        /** Phase lost error */
        uart_dma_write((uint8_t*)phase_lost_msg, strlen(phase_lost_msg));
        shdat_set_meter_state(METER_STATE_ERROR);
      case METER_PHASE_COUNT - 2u:
        /** 1 phase is ON */
        if (shdat_get_meter_current_state() ==
            METER_STATE_WAIT_FOR_STARTING_CURRENT)
          shdat_set_meter_state(METER_STATE_WAIT_FOR_PLL_LOCK);
        break;
      case METER_PHASE_COUNT - 3u:
        /** No phase satisfy condition */
        shdat_set_meter_state(METER_STATE_WAIT_FOR_STARTING_CURRENT);
        break;
      default:
        /** Warning */
        uart_dma_write((uint8_t*)warning_msg, strlen(warning_msg));
        shdat_set_meter_state(METER_STATE_WARNING);
        break;
    }

    /** Check state */
    switch (shdat_get_meter_current_state()) {
      case METER_STATE_START:
        /** if power on is good */
        shdat_set_meter_state(METER_STATE_WAIT_FOR_STARTING_CURRENT);
        break;

      case METER_STATE_WAIT_FOR_STARTING_CURRENT:
        break;

      case METER_STATE_WAIT_FOR_PLL_LOCK: {
        static uint8_t locked_counter = 0;
        if (pll_is_locked(&dsp_dat_buf.pll_3p)) {
          if (locked_counter > 2) {
            locked_counter = 0;
            if ((on_phase[PHASE_A_POS] == ON) &&
                (on_phase[PHASE_B_POS] == ON) &&
                (on_phase[PHASE_C_POS] == ON)) {
              shdat_set_meter_state(METER_STATE_RUNNING_3PHASE);
            } else if (on_phase[PHASE_A_POS] == ON) {
              shdat_set_meter_state(METER_STATE_RUNNING_PHASE_A);
            } else if (on_phase[PHASE_B_POS] == ON) {
              shdat_set_meter_state(METER_STATE_RUNNING_PHASE_B);
            } else {
              shdat_set_meter_state(METER_STATE_RUNNING_PHASE_C);
            }
          } else {
            locked_counter++;
          }
        }
      } break;

        // Only accumulate energy when meter is running
      case METER_STATE_RUNNING_PHASE_A:
        energy_accum(&meter_data, ON, OFF, OFF);
        shdat_wrt_meter_data(&meter_data);
        break;
      case METER_STATE_RUNNING_PHASE_B:
        energy_accum(&meter_data, OFF, ON, OFF);
        shdat_wrt_meter_data(&meter_data);
        break;
      case METER_STATE_RUNNING_PHASE_C:
        energy_accum(&meter_data, OFF, OFF, ON);
        shdat_wrt_meter_data(&meter_data);
        break;
      case METER_STATE_RUNNING_3PHASE: {
        static enum {
          FRE_50HZ,
          FRE_CHANGE_UP,
          FRE_CHANGE_DOWN,
          FRE_60HZ,
        } cur_fre = (METER_START_FREQUENCY == 60U) ? FRE_60HZ : FRE_50HZ;

        switch (cur_fre) {
          case FRE_50HZ:
            cur_fre = FRE_CHANGE_UP;
            mock_change_frequency(60.0f, 0.001f);
            break;

          case FRE_CHANGE_UP:
            if (ABS(dsp_dat_buf.pll_3p.fre - 60.0f) < 0.01f) {
              cur_fre = FRE_60HZ;
            }
            break;

          case FRE_CHANGE_DOWN:
            if (ABS(dsp_dat_buf.pll_3p.fre - 50.0f) < 0.01f) {
              cur_fre = FRE_50HZ;
            }
            break;

          case FRE_60HZ:
            cur_fre = FRE_CHANGE_DOWN;
            mock_change_frequency(50.0f, 0.001f);
            break;
          default:
            break;
        }

        energy_accum(&meter_data, ON, ON, ON);
        shdat_wrt_meter_data(&meter_data);
      } break;
      case METER_STATE_WARNING:
        break;
      case METER_STATE_ERROR:
        break;
      default:
        break;
    }
    //<1ms for 3 phase with full data, so fast =))
    process_time = DWT->CYCCNT - start_cycles;
    dm_report(&adc_task_health, dm_cycles_to_us(process_time));
    (void)dm_is_healthy(&adc_task_health);
  }
}
/**
 * @brief ADC half conversion complete callback
 * @note Notify adc task
 *
 */
void adc_half_conv_cplt_callback(void) {
#ifdef DATA_USE_MOCK_DATA
  xTaskNotify(adc_task.handle, HT_CALLBACK_VAL, eSetBits);
#else
  BaseType_t xWake;
  xTaskNotifyFromISR(adc_task.handle, 0, eNoAction, &xWake);
  portYIELD_FROM_ISR(xWake);
#endif
}

/**
 * @brief ADC half conversion complete callback
 * @note Notify adc task
 *
 */
void adc_full_conv_cplt_callback(void) {
#ifdef DATA_USE_MOCK_DATA
  xTaskNotify(adc_task.handle, TC_CALLBACK_VAL, eSetBits);
#else
  BaseType_t xWake;
  xTaskNotifyFromISR(adc_task.handle, 0, eNoAction, &xWake);
  portYIELD_FROM_ISR(xWake);
#endif
}

/**
 * @brief ADC DMA init
 *
 */
void adc_DMA_init(void) {
/** MX set DMA and ADC, we need to set memory address for DMA transfer */
#ifndef DATA_USE_MOCK_DATA
  LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_0, (uint32_t)adc_buffer);
  LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_0, (uint32_t)&ADC1->DR);
  LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_0,
                       METER_PHASE_COUNT * 4U * METER_SAMPLES_PER_CYCLE);
  LL_DMA_EnableIT_HT(DMA2, LL_DMA_STREAM_0);
  LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_0);
  LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
#endif
#ifdef DATA_USE_MOCK_DATA
  /** If we use mock data, we can just generate mock data in the task, so we
   * don't need to set up DMA for ADC. */
  mock_DMA_init(
      (uint16_t*)adc_buffer,
      METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE * 2u, 1,
      1);
#endif
}

/** Accumulate energy */
static void energy_accum(struct meter_data_s* meter_dat, enum phase_on_e phaseA,
                         enum phase_on_e phaseB, enum phase_on_e phaseC) {
  if (phaseA == ON) {
    meter_dat->energy_Ws +=
        meter_dat->phase_data[PHASE_A_POS].act_pwr / meter_dat->frequency;
  }
  if (phaseB == ON) {
    meter_dat->energy_Ws +=
        meter_dat->phase_data[PHASE_B_POS].act_pwr / meter_dat->frequency;
  }
  if (phaseC == ON) {
    meter_dat->energy_Ws +=
        meter_dat->phase_data[PHASE_C_POS].act_pwr / meter_dat->frequency;
  }

  int32_t int_part = (int32_t)(meter_dat->energy_Ws / WS_TO_HWH);
  if (int_part) {
    /** Accum ws, in_part now contain amount hWh, use int because WS and hWh can
     * be negative */
    meter_dat->energy_Ws -= (float64_t)int_part * WS_TO_HWH;

    meter_dat->energy_hWh += int_part;

    if (int_part < 0) int_part = -int_part;  // ABS int_part

    for (size_t i = 0; i < int_part; i++) {
      pulse_trigger(); /** Trigger pulse output pin */
    }
  }
}