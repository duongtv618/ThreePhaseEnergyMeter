#include "uart_dma.h"
#include "main.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_rcc.h"
#include <string.h>

/* UART DMA Ring Buffer Configuration */
#define UART_DMA_RX_BUFFER_SIZE 256
#define UART_NUM_BUFFERS 2

typedef struct {
    uint8_t buffer[UART_NUM_BUFFERS][UART_DMA_RX_BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t size;
} uart_ring_buffer_t;

static uart_ring_buffer_t uart_rx_ring = {0};
static uint8_t current_dma_buffer = 0;

static volatile uint8_t tx_busy = 0;

/**
 * @brief Initialize UART2 with DMA for NUCLEOF411RE
 * USART2: TX=PA2, RX=PA3, Baud=115200
 */
void uart_dma_init(void)
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

    /**USART2 GPIO Configuration
    PA2   ------> USART2_TX
    PA3   ------> USART2_RX
    */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2 | LL_GPIO_PIN_3;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 DMA Init */

    /* USART2_RX Init */
    LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_5, LL_DMA_CHANNEL_4);
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_5, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
    LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_5, LL_DMA_PRIORITY_HIGH);
    LL_DMA_SetMode(DMA1, LL_DMA_STREAM_5, LL_DMA_MODE_CIRCULAR);
    LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_STREAM_5, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_5, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_5, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_5, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_DisableFifoMode(DMA1, LL_DMA_STREAM_5);

    /* USART2_TX Init */
    LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_6, LL_DMA_CHANNEL_4);
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_STREAM_6, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_6, LL_DMA_PRIORITY_LOW);
    LL_DMA_SetMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MODE_NORMAL);
    LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_STREAM_6, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(DMA1, LL_DMA_STREAM_6, LL_DMA_PDATAALIGN_BYTE);
    LL_DMA_SetMemorySize(DMA1, LL_DMA_STREAM_6, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_DisableFifoMode(DMA1, LL_DMA_STREAM_6);

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    USART_InitStruct.BaudRate = 115200;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(USART2, &USART_InitStruct);
    LL_USART_ConfigAsyncMode(USART2);

    /* Set DMA addresses for RX */
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_5, (uint32_t)uart_rx_ring.buffer[0]);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_5, LL_USART_DMA_GetRegAddr(USART2));
    LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_5, UART_DMA_RX_BUFFER_SIZE);

    /* Enable DMA circular mode */
    LL_DMA_SetMode(DMA1, LL_DMA_STREAM_5, LL_DMA_MODE_CIRCULAR);

    /* Enable USART2 DMA RX request */
    LL_USART_EnableDMAReq_RX(USART2);

    /* Enable DMA stream and USART */
    LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
    LL_USART_Enable(USART2);

    /* Enable NVIC for DMA TX */
    NVIC_SetPriority(DMA1_Stream6_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Stream6_IRQn);

    /* Initialize ring buffer */
    uart_rx_ring.head = 0;
    uart_rx_ring.tail = 0;
    uart_rx_ring.size = 0;
    current_dma_buffer = 0;

    /* Initialize TX busy flag */
    tx_busy = 0;
}

/**
 * @brief Get number of bytes available in ring buffer
 */
uint16_t uart_dma_available(void)
{
    return uart_rx_ring.size;
}

/**
 * @brief Read one byte from ring buffer
 */
uint8_t uart_dma_read_byte(void)
{
    if (uart_rx_ring.size == 0) {
        return 0;
    }

    uint8_t data = uart_rx_ring.buffer[current_dma_buffer][uart_rx_ring.tail];
    uart_rx_ring.tail++;

    if (uart_rx_ring.tail >= UART_DMA_RX_BUFFER_SIZE) {
        uart_rx_ring.tail = 0;
        current_dma_buffer = (current_dma_buffer + 1) % UART_NUM_BUFFERS;
    }

    uart_rx_ring.size--;
    return data;
}

/**
 * @brief Read multiple bytes from ring buffer
 */
uint16_t uart_dma_read(uint8_t *data, uint16_t len)
{
    uint16_t bytes_read = 0;

    while (bytes_read < len && uart_rx_ring.size > 0) {
        data[bytes_read++] = uart_dma_read_byte();
    }

    return bytes_read;
}

/**
 * @brief Write one byte via UART (DMA-driven)
 */
void uart_dma_write_byte(uint8_t byte)
{
    if (!tx_busy) {
        tx_busy = 1;
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)&byte);
        LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_6, LL_USART_DMA_GetRegAddr(USART2));
        LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, 1);
        LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_6);
        LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);
        LL_USART_EnableDMAReq_TX(USART2);
    }
    // If busy, do nothing (non-blocking)
}

/**
 * @brief Write multiple bytes via UART (DMA-driven)
 */
void uart_dma_write(const uint8_t *data, uint16_t len)
{
    if (!tx_busy) {
        tx_busy = 1;
        LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)data);
        LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_6, LL_USART_DMA_GetRegAddr(USART2));
        LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, len);
        LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_6);
        LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);
        LL_USART_EnableDMAReq_TX(USART2);
    }
    // If busy, do nothing (non-blocking)
}

/**
 * @brief Update ring buffer based on DMA counter
 * Call this periodically or in interrupt handler
 */
void uart_dma_update(void)
{
    uint16_t dma_remaining = LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
    uint16_t dma_pos = UART_DMA_RX_BUFFER_SIZE - dma_remaining;

    if (dma_pos != uart_rx_ring.head) {
        if (dma_pos > uart_rx_ring.head) {
            uart_rx_ring.size += (dma_pos - uart_rx_ring.head);
        } else {
            uart_rx_ring.size += (UART_DMA_RX_BUFFER_SIZE - uart_rx_ring.head) + dma_pos;
        }
        uart_rx_ring.head = dma_pos;
    }
}

/**
 * @brief Flush ring buffer
 */
void uart_dma_flush(void)
{
    uart_rx_ring.head = 0;
    uart_rx_ring.tail = 0;
    uart_rx_ring.size = 0;
    current_dma_buffer = 0;
}

/**
 * @brief DMA1 Stream6 Interrupt Handler for USART2 TX
 */
void DMA1_Stream6_IRQHandler(void)
{
    if (LL_DMA_IsActiveFlag_TC6(DMA1)) {
        LL_DMA_ClearFlag_TC6(DMA1);
        LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
        LL_USART_DisableDMAReq_TX(USART2);
        tx_busy = 0;
    }
}
