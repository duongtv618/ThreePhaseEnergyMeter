#include "app.h"

#include "FreeRTOS.h"
#include "adc_sample.h"
#include "comm.h"
#include "led_blink.h"
#include "stm32f4xx.h"
#include "task.h"

static void DWT_init(void);

static void DWT_init(void) {
  /* Enable DWT and CYCCNT */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // Enable trace and debug
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;             // Enable cycle counter
}

/**
 * @brief Initialize the application
 */
void app_init(void) {
  DWT_init();
  led_blink_init();
  adc_sample_init();
  comm_init();
}

void app_start(void) { vTaskStartScheduler(); }