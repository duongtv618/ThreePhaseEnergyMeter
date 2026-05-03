#ifndef STM32F4XX_LL_DMA_H
#define STM32F4XX_LL_DMA_H
#include <stdint.h>
typedef struct { volatile uint32_t dummy; } DMA_TypeDef;
static DMA_TypeDef _stub_dma1 = {0};
#define DMA1                                (&_stub_dma1)
#define DMA1_Stream5_IRQn                   0
#define DMA1_Stream6_IRQn                   0
#define LL_DMA_STREAM_5                     5
#define LL_DMA_STREAM_6                     6
#define LL_DMA_CHANNEL_4                    4
#define LL_DMA_DIRECTION_PERIPH_TO_MEMORY   0
#define LL_DMA_DIRECTION_MEMORY_TO_PERIPH   1
#define LL_DMA_PRIORITY_LOW                 0
#define LL_DMA_MODE_CIRCULAR                0
#define LL_DMA_MODE_NORMAL                  1
#define LL_DMA_PERIPH_NOINCREMENT           0
#define LL_DMA_MEMORY_INCREMENT             1
#define LL_DMA_PDATAALIGN_BYTE              0
#define LL_DMA_MDATAALIGN_BYTE              0
#define LL_DMA_DisableStream(d,s)           do{}while(0)
#define LL_DMA_IsEnabledStream(d,s)         (0)
#define LL_DMA_EnableStream(d,s)            do{}while(0)
#define LL_DMA_SetChannelSelection(d,s,c)   do{}while(0)
#define LL_DMA_SetDataTransferDirection(d,s,v) do{}while(0)
#define LL_DMA_SetStreamPriorityLevel(d,s,v)   do{}while(0)
#define LL_DMA_SetMode(d,s,v)               do{}while(0)
#define LL_DMA_SetPeriphIncMode(d,s,v)      do{}while(0)
#define LL_DMA_SetMemoryIncMode(d,s,v)      do{}while(0)
#define LL_DMA_SetPeriphSize(d,s,v)         do{}while(0)
#define LL_DMA_SetMemorySize(d,s,v)         do{}while(0)
#define LL_DMA_DisableFifoMode(d,s)         do{}while(0)
#define LL_DMA_SetPeriphAddress(d,s,v)      do{}while(0)
#define LL_DMA_SetMemoryAddress(d,s,v)      do{}while(0)
#define LL_DMA_SetDataLength(d,s,v)         do{}while(0)
#define LL_DMA_GetDataLength(d,s)           (0U)
#define LL_DMA_EnableIT_TC(d,s)             do{}while(0)
#define LL_DMA_IsActiveFlag_TC5(d)          (0)
#define LL_DMA_IsActiveFlag_TC6(d)          (0)
#define LL_DMA_IsActiveFlag_TE5(d)          (0)
#define LL_DMA_IsActiveFlag_TE6(d)          (0)
#define LL_DMA_ClearFlag_TC5(d)             do{}while(0)
#define LL_DMA_ClearFlag_TC6(d)             do{}while(0)
#define LL_DMA_ClearFlag_TE5(d)             do{}while(0)
#define LL_DMA_ClearFlag_TE6(d)             do{}while(0)
#endif /* STM32F4XX_LL_DMA_H */
