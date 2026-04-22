#include "led_blink.h"

#include "FreeRTOS.h"
#include "app_cfg.h"
#include "main.h"
#include "task.h"

#define BLINK_TASK_STACK_SIZE APP_DEFAULT_TASK_STACK_SIZE
#define BLINK_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define BLINK_TASK_INTERVAL_MS 500

/* Global Variables */

static struct {
  StaticTask_t buffer;
  StackType_t stack[BLINK_TASK_STACK_SIZE];
  TaskHandle_t handle;
} blinkLEDTaskData;

static void blink_led_task(void* pvParameters);

/* Blink LED Task */
void led_blink_init(void) {
  blinkLEDTaskData.handle =
      xTaskCreateStatic(blink_led_task, "BlinkLED", BLINK_TASK_STACK_SIZE, NULL,
                        BLINK_TASK_PRIORITY, blinkLEDTaskData.stack,
                        &blinkLEDTaskData.buffer);
}

static void blink_led_task(void* pvParameters) {
  TickType_t last_wake_time = xTaskGetTickCount();
  while (1) {
    /* Toggle LED */
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(BLINK_TASK_INTERVAL_MS));
  }
}