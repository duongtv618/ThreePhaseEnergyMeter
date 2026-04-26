#include "led_blink.h"

#include "FreeRTOS.h"
#include "app_cfg.h"
#include "main.h"
#include "task.h"

#define LED_BLINK_TIME_MS 50

#define BLINK_TASK_STACK_SIZE APP_DEFAULT_TASK_STACK_SIZE
#define BLINK_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

/* Global Variables */

static struct {
  StaticTask_t buffer;
  StackType_t stack[BLINK_TASK_STACK_SIZE];
  TaskHandle_t handle;
} blinkLEDTaskData;

static void blink_led_task(void* pvParameters);

void led_trigger(void) {
  xTaskNotifyGive(blinkLEDTaskData.handle);
}

/* Blink LED Task */
void led_blink_init(void) {
  blinkLEDTaskData.handle =
      xTaskCreateStatic(blink_led_task, "BlinkLED", BLINK_TASK_STACK_SIZE, NULL,
                        BLINK_TASK_PRIORITY, blinkLEDTaskData.stack,
                        &blinkLEDTaskData.buffer);
}

static void blink_led_task(void* pvParameters) {
  while (1) {
    /* Toggle LED */
    if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) != pdPASS) continue; 
    LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_5);
    vTaskDelay(pdMS_TO_TICKS(LED_BLINK_TIME_MS));
    LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_5);
  }
}