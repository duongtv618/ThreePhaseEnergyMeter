#ifndef FREERTOS_H
#define FREERTOS_H
#include <stdint.h>
typedef void*    TaskHandle_t;
typedef uint32_t UBaseType_t;
typedef uint32_t TickType_t;
typedef int      BaseType_t;
#define pdFALSE  0
#define pdTRUE   1
#define eSetBits 0
#define portYIELD_FROM_ISR(x)       do{}while(0)
#define xTaskNotifyFromISR(t,v,a,p) do{}while(0)
#endif /* FREERTOS_H */
