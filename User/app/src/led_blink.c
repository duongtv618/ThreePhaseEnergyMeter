#include "led_blink.h"
#include "app_cfg.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

#define BLINK_TASK_STACK_SIZE APP_DEFAULT_TASK_STACK_SIZE
#define BLINK_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define BLINK_TASK_INTERVAL_MS 500

/* Global Variables */

static struct blinkTask_s
{
    StaticTask_t taskBuffer;
    StackType_t taskStack[BLINK_TASK_STACK_SIZE];
    TaskHandle_t taskHandle;
} blinkLEDTaskData;


static void blink_led_task(void *pvParameters);

/* Blink LED Task */
void ledBlinkInit(void) {
    blinkLEDTaskData.taskHandle = xTaskCreateStatic(blink_led_task,
                      "BlinkLED",
                      BLINK_TASK_STACK_SIZE,
                      NULL,
                      BLINK_TASK_PRIORITY,
                      blinkLEDTaskData.taskStack,
                      &blinkLEDTaskData.taskBuffer);
}

static void blink_led_task(void *pvParameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1) {
        /* Toggle LED */
        LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(BLINK_TASK_INTERVAL_MS));
    }
}