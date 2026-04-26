#include "comm.h"
#include "app_cfg.h"
#include <string.h>

#include "FreeRTOS.h"
#include "share_data.h"
#include "share_types.h"
#include "task.h"
#include "uart_dma.h"
#include "modbus_rtu.h"

#define RMS_VOL_MSG "RMS Voltage:\t"
#define RMS_CUR_MSG "RMS Current:\t"
#define ACTIVE_POWR_MSG "Active power:\t"
#define APP_PWR_MSG "Apparent power:\t"
#define FRE_MSG "Frequency:\t"
#define PF_MSG "Power Factor:\t"
#define ENERGY "Energy (hWh):\t"
#define THD_VOLTAGE_MSG "THD voltage:\t"
#define THD_CURRENT_MSG "THD current:\t"

#define WRITE_TAB uart_dma_write((uint8_t*)"\t", 1)

#define CRNL "\r\n"
#define CLEAR_TER "\033[2J\033[H"

/** Comm task struct */
static struct _commTask_s {
  StaticTask_t taskBuffer;
  StackType_t taskStack[APP_DEFAULT_TASK_STACK_SIZE];
  TaskHandle_t taskHandle;
} commTaskData;

/** Not running message */
// const static char* meterNotRunningMsg = "Meter not running\r\n";

static void comm_task(void* params);
static char* itoa(int32_t value, char* str, int32_t base);
static char* ftoa(float32_t value, char* str, int digit);
#ifdef USE_UART_LOG
static void sendData(void);
#endif

/**
 * @brief Comm task
 *
 * @param params Unuse
 */
static void comm_task(void* params) {
  struct meter_data_s meter_data;
  while (1) {
    // Periodically update UART DMA ring buffer
    // uart_dma_update();
    // if (shdat_get_meter_current_state() >= METER_STATE_RUNNING_3PHASE) {
    //   sendData();
    // } else {
    //   uart_dma_write((uint8_t*)meterNotRunningMsg, strlen(meterNotRunningMsg));
    // }

    // vTaskDelayUntil(&lastWakeTime,
    //                 pdMS_TO_TICKS(1000));  // Adjust delay as needed

    xTaskNotifyWait(0, 0x00, NULL, portMAX_DELAY);
    meter_data = shdat_get_meter_data();
    meter_update_registers(&meter_data);
    mb_poll();
    calib_poll();
  }
}

/** Initialize task */
void comm_init(void) {
  // uart_dma_init();  // Init debug port
  commTaskData.taskHandle =
      xTaskCreateStatic(comm_task,                    // Task function
                        "CommTask",                   // Name of the task
                        APP_DEFAULT_TASK_STACK_SIZE,  // Stack size (in words)
                        NULL,                         // Task parameters
                        tskIDLE_PRIORITY + 1,         // Priority
                        commTaskData.taskStack,       // Stack buffer
                        &commTaskData.taskBuffer  // Task control block buffer
      );
  mb_init(commTaskData.taskHandle);
}

static char* ftoa(float32_t value, char* str, int digit) {
  char* ptr = str;
  char* ptr1;
  int32_t int_part, remain;

  if (value == NAN) {
    *str = '\0';
    return str;
  }

  if (value == INFINITY) {
    strcpy(str, "Inf");
    return str;
  }

  int_part = (int32_t)value;

  ptr = itoa(int_part, str, 10);  // Convert to string
  ptr1 = ptr;
  ptr += strlen(ptr);  // ptr is in last position now
  *ptr++ = '.';

  value -= (float32_t)int_part;

  if (value < 0.0f) {
    value = -1.0f * value;
  }

  value *= (powf(10.0f, (float32_t)digit));
  remain = (int32_t)value;
  itoa(remain, ptr, 10);
  return ptr1;
}

/** Support funtcion interget to ascii */
static char* itoa(int32_t value, char* str, int32_t base) {
  char *ptr = str, *ptr1 = str, tmp_char;
  int tmp_value;

  if (base < 2 || base > 36) {
    *str = '\0';
    return str;
  }

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[35 + (tmp_value - value * base)];
  } while (value);

  if (tmp_value < 0) {
    *ptr++ = '-';
  }
  *ptr-- = '\0';

  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return str;
}

#ifdef USE_UART_LOG
static void sendData(void) {
  static char msg[64];
  struct meter_data_s meter_data;
  meter_data = shdat_get_meter_data();
  // Example: Send a message every 500ms

  uart_dma_write((uint8_t*)CLEAR_TER, strlen(CLEAR_TER));

  uart_dma_write((uint8_t*)RMS_VOL_MSG, strlen(RMS_VOL_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[0].rms_voltage, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[1].rms_voltage, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[2].rms_voltage, msg, 3),
                 strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)RMS_CUR_MSG, strlen(RMS_CUR_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[0].rms_current, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[1].rms_current, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[2].rms_current, msg, 3),
                 strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)ACTIVE_POWR_MSG, strlen(ACTIVE_POWR_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[0].act_pwr, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[1].act_pwr, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[2].act_pwr, msg, 3),
                 strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)APP_PWR_MSG, strlen(APP_PWR_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[0].app_pwr, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[1].app_pwr, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[2].app_pwr, msg, 3),
                 strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)FRE_MSG, strlen(FRE_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.frequency, msg, 3), strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)PF_MSG, strlen(PF_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[0].pf, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[1].pf, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[2].pf, msg, 3),
                 strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)THD_VOLTAGE_MSG, strlen(THD_VOLTAGE_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[0].thd.voltage, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[1].thd.voltage, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[2].thd.voltage, msg, 3),
                 strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)THD_CURRENT_MSG, strlen(THD_CURRENT_MSG));
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[0].thd.current, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[1].thd.current, msg, 3),
                 strlen(msg));
  WRITE_TAB;
  WRITE_TAB;
  uart_dma_write((uint8_t*)ftoa(meter_data.phase_data[2].thd.current, msg, 3),
                 strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));

  uart_dma_write((uint8_t*)ENERGY, strlen(ENERGY));
  uart_dma_write((uint8_t*)itoa(meter_data.energy_hWh, msg, 10), strlen(msg));
  uart_dma_write((uint8_t*)CRNL, strlen(CRNL));
}
#endif