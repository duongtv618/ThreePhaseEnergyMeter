#ifndef STM32F4XX_LL_USART_H
#define STM32F4XX_LL_USART_H
#include <stdint.h>
#include <stdbool.h>
typedef struct { volatile uint32_t DR; volatile uint32_t SR; } USART_TypeDef;
static USART_TypeDef _stub_usart2 = {0};
#define USART2 (&_stub_usart2)
#define USART2_IRQn 0
#define LL_USART_DMA_GetRegAddr(x)          (0U)
#define LL_USART_EnableDMAReq_RX(x)         do{}while(0)
#define LL_USART_EnableDMAReq_TX(x)         do{}while(0)
#define LL_USART_ClearFlag_IDLE(x)          do{}while(0)
#define LL_USART_EnableIT_IDLE(x)           do{}while(0)
#define LL_USART_Enable(x)                  do{}while(0)
#define LL_USART_IsActiveFlag_IDLE(x)       (0)
#define LL_USART_IsActiveFlag_TC(x)         (1)
#define LL_USART_ClearFlag_TC(x)            do{}while(0)
#define LL_USART_DATAWIDTH_8B               0
#define LL_USART_STOPBITS_1                 0
#define LL_USART_PARITY_NONE                0
#define LL_USART_DIRECTION_TX_RX            0
#define LL_USART_HWCONTROL_NONE             0
#define LL_USART_OVERSAMPLING_16            0
typedef struct {
    uint32_t BaudRate; uint32_t DataWidth; uint32_t StopBits;
    uint32_t Parity;   uint32_t TransferDirection;
    uint32_t HardwareFlowControl; uint32_t OverSampling;
} LL_USART_InitTypeDef;
#define LL_USART_Init(u, c)                 do{}while(0)
#define LL_USART_ConfigAsyncMode(x)         do{}while(0)
#define GPIOA                               ((void*)0)
#define LL_GPIO_PIN_2                       0
#define LL_GPIO_PIN_3                       0
#define LL_GPIO_PIN_4                       0
#endif /* STM32F4XX_LL_USART_H */
