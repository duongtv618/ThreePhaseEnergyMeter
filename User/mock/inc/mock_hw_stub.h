#ifndef MOCK_HW_STUB_H
#define MOCK_HW_STUB_H

#include <stdint.h>
#include <stddef.h>

/* DWT stub */
typedef struct { uint32_t CYCCNT; } DWT_Type;
static DWT_Type _stub_DWT = {0};
#define DWT (&_stub_DWT)

/* FreeRTOS stubs */
typedef uint32_t TickType_t;
typedef uint32_t UBaseType_t;
typedef struct { uint32_t dummy; } StaticTask_t;
typedef uint32_t StackType_t;

#define pdMS_TO_TICKS(ms)      (ms)
#define xTaskGetTickCount()    (0U)
#define vTaskDelayUntil(a,b)   do{(void)(a);(void)(b);}while(0)

static inline void* xTaskCreateStatic(void(*f)(void*),const char* n,
    uint32_t s,void* p,uint32_t prio,StackType_t* st,StaticTask_t* buf)
{ (void)f;(void)n;(void)s;(void)p;(void)prio;(void)st;(void)buf; return NULL; }

#endif /* MOCK_HW_STUB_H */
