#include "led_blink.h"

#include "FreeRTOS.h"
#include "app_cfg.h"
#include "deadline_monitor.h"
#include "main.h"
#include "stm32f4xx.h"
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

static struct task_health_status led_blink_task_health;

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
  (void)dm_register(&led_blink_task_health, DM_DEADLINE_LED_BLINK_TASK_US);
}

static void blink_led_task(void* pvParameters) {
  while (1) {
    /* Toggle LED */
    if (xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) != pdPASS) continue;
    uint32_t start_cycles = DWT->CYCCNT;
    LL_GPIO_SetOutputPin(GPIOA, GPIO_PIN_5);
    vTaskDelay(pdMS_TO_TICKS(LED_BLINK_TIME_MS));
    LL_GPIO_ResetOutputPin(GPIOA, GPIO_PIN_5);
    dm_report(&led_blink_task_health, dm_cycles_to_us(DWT->CYCCNT - start_cycles));
    (void)dm_is_healthy(&led_blink_task_health);
  }
}
