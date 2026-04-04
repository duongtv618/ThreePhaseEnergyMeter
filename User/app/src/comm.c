#include "comm.h"

#include "app_cfg.h"

#include "FreeRTOS.h"
#include "task.h"

#include "uart_dma.h"

static struct _commTask_s
{
    StaticTask_t taskBuffer;
    StackType_t taskStack[APP_DEFAULT_TASK_STACK_SIZE];
    TaskHandle_t taskHandle;
} commTaskData;

static void comm_task(void *params);

static void comm_task(void *params)
{
    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1)
    {
        // Periodically update UART DMA ring buffer
        uart_dma_update();
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(500)); // Adjust delay as needed
    }
}

void comm_init(void)
{
    // Initialize communication interfaces (e.g., UART, I2C, SPI)
    // For example, initialize UART with DMA for efficient communication
    uart_dma_init();
    commTaskData.taskHandle = xTaskCreateStatic(
        comm_task,                   // Task function
        "CommTask",                  // Name of the task
        APP_DEFAULT_TASK_STACK_SIZE, // Stack size (in words)
        NULL,                        // Task parameters
        tskIDLE_PRIORITY + 1,        // Priority
        commTaskData.taskStack,      // Stack buffer
        &commTaskData.taskBuffer     // Task control block buffer
    );
}