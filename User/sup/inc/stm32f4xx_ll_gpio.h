#ifndef STM32F4XX_LL_GPIO_H
#define STM32F4XX_LL_GPIO_H
#include <stdint.h>
#define LL_GPIO_MODE_ALTERNATE  0
#define LL_GPIO_SPEED_FREQ_HIGH 0
#define LL_GPIO_OUTPUT_PUSHPULL 0
#define LL_GPIO_PULL_UP         0
#define LL_GPIO_AF_7            7
typedef struct {
    uint32_t Pin,Mode,Speed,OutputType,Pull,Alternate;
} LL_GPIO_InitTypeDef;
#define LL_GPIO_Init(p,c)       do{}while(0)
/* NVIC stubs */
#define NVIC_SetPriority(irq,p) do{}while(0)
#define NVIC_EnableIRQ(irq)     do{}while(0)
typedef int IRQn_Type;
#endif /* STM32F4XX_LL_GPIO_H */
