#include "uart_dma.h"

#include <string.h>

#include "main.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_usart.h"

/* UART DMA Ring Buffer Configuration */
#define UART_DMA_RX_BUFFER_SIZE 512
#define UART_DMA_TX_BUFFER_SIZE 512
#define UART_NUM_BUFFERS 2

typedef struct {
  uint8_t buffer[UART_NUM_BUFFERS][UART_DMA_RX_BUFFER_SIZE];
  uint16_t head;
  uint16_t tail;
  uint16_t size;
} uart_ring_buffer_t;

typedef struct {
  uint8_t buffer[UART_DMA_TX_BUFFER_SIZE];
  uint16_t head;
  uint16_t tail;
  uint16_t size;
} uart_tx_ring_buffer_t;

static volatile uart_ring_buffer_t uart_rx_ring = {0};
static volatile uart_tx_ring_buffer_t uart_tx_ring = {0};
static volatile uint8_t current_dma_buffer = 0;
static volatile uint8_t tx_busy = 0;

/** Start UART DMA transmission */
static void uart_dma_start_tx(void) {
  if (uart_tx_ring.head == uart_tx_ring.tail) {
    return;  // No data to send
  }

  /** Length to send */
  uint16_t transfer_len;
  if (uart_tx_ring.head > uart_tx_ring.tail) {
    transfer_len = uart_tx_ring.head - uart_tx_ring.tail;
  } else {
    transfer_len = UART_DMA_TX_BUFFER_SIZE - uart_tx_ring.tail;
  }

  tx_busy = 1;
  /** Setup DMA */
  LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
  // LL_DMA_ClearFlag_TC6(DMA1);
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6,
                          (uint32_t)&uart_tx_ring.buffer[uart_tx_ring.tail]);
  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_6,
                          LL_USART_DMA_GetRegAddr(USART2));
  LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, transfer_len);

  /** New tails */
  uart_tx_ring.tail =
      (uart_tx_ring.tail + transfer_len) % UART_DMA_TX_BUFFER_SIZE;

  LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_6);
  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);
  LL_USART_EnableDMAReq_TX(USART2);
}

/**
 * @brief Initialize UART2 with DMA for NUCLEOF411RE
 * USART2: TX=PA2, RX=PA3, Baud=115200
 */
void uart_dma_init(void) {
  LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
  LL_DMA_ClearFlag_TC6(DMA1);

  /* Set DMA addresses for RX */
  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_5,
                          (uint32_t)uart_rx_ring.buffer[0]);
  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_5,
                          LL_USART_DMA_GetRegAddr(USART2));
  LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_5, UART_DMA_RX_BUFFER_SIZE);

  /* Enable USART2 DMA RX request */
  LL_USART_EnableDMAReq_RX(USART2);

  /* Enable DMA stream and USART */
  LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
  LL_USART_Enable(USART2);

  /* Initialize ring buffers */
  uart_rx_ring.head = 0;
  uart_rx_ring.tail = 0;
  uart_rx_ring.size = 0;
  current_dma_buffer = 0;

  uart_tx_ring.head = 0;
  uart_tx_ring.tail = 0;
  uart_tx_ring.size = 0;
  tx_busy = 0;
}

/**
 * @brief Get number of bytes available in ring buffer
 */
uint16_t uart_dma_available(void) { return uart_rx_ring.size; }

/**
 * @brief Read one byte from ring buffer
 */
uint8_t uart_dma_read_byte(void) {
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
uint16_t uart_dma_read(uint8_t* data, uint16_t len) {
  uint16_t bytes_read = 0;

  while (bytes_read < len && uart_rx_ring.size > 0) {
    data[bytes_read++] = uart_dma_read_byte();
  }

  return bytes_read;
}

/**
 * @brief Write one byte via UART (DMA-driven)
 */
void uart_dma_write_byte(uint8_t byte) {
  if (uart_tx_ring.size >= UART_DMA_TX_BUFFER_SIZE) {
    return;
  }

  uart_tx_ring.buffer[uart_tx_ring.head] = byte;
  uart_tx_ring.head = (uart_tx_ring.head + 1) % UART_DMA_TX_BUFFER_SIZE;
  uart_tx_ring.size++;

  if (!tx_busy) {
    uart_dma_start_tx();
  }
}

/**
 * @brief Write multiple bytes via UART (DMA-driven)
 */
void uart_dma_write(const uint8_t* data, uint16_t len) {
  /** Put data to ring buffer */
  for (uint16_t i = 0; i < len; i++) {
    uint16_t next_head = (uart_tx_ring.head + 1) % UART_DMA_TX_BUFFER_SIZE;
    if (next_head != uart_tx_ring.tail) {
      uart_tx_ring.buffer[uart_tx_ring.head] = data[i];
      uart_tx_ring.head = next_head;
    } else {
      break;
    }
  }

  /** If DMA is not busy, start transmission */
  if (!tx_busy && (uart_tx_ring.head != uart_tx_ring.tail)) {
    uart_dma_start_tx();
  }
}

void uart_dma_write_block(const uint8_t* data, uint16_t len) {
  /** Put data to ring buffer */
  for (uint16_t i = 0; i < len; i++) {
    uint16_t next_head = (uart_tx_ring.head + 1) % UART_DMA_TX_BUFFER_SIZE;
    /** Wait until there is space in the buffer */
    while (next_head == uart_tx_ring.tail);
    uart_tx_ring.buffer[uart_tx_ring.head] = data[i];
    uart_tx_ring.head = next_head;
  }

  /** If DMA is not busy, start transmission */
  if (!tx_busy && (uart_tx_ring.head != uart_tx_ring.tail)) {
    uart_dma_start_tx();
  }
}

/**
 * @brief Update ring buffer based on DMA counter
 * Call this periodically or in interrupt handler
 */
void uart_dma_update(void) {
  uint16_t dma_remaining = LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
  uint16_t dma_pos = UART_DMA_RX_BUFFER_SIZE - dma_remaining;

  if (dma_pos != uart_rx_ring.head) {
    if (dma_pos > uart_rx_ring.head) {
      uart_rx_ring.size += (dma_pos - uart_rx_ring.head);
    } else {
      uart_rx_ring.size +=
          (UART_DMA_RX_BUFFER_SIZE - uart_rx_ring.head) + dma_pos;
    }
    uart_rx_ring.head = dma_pos;
  }
}

/**
 * @brief Flush ring buffer
 */
void uart_dma_flush(void) {
  LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
  LL_USART_DisableDMAReq_TX(USART2);

  uart_rx_ring.head = 0;
  uart_rx_ring.tail = 0;
  uart_rx_ring.size = 0;
  current_dma_buffer = 0;

  uart_tx_ring.head = 0;
  uart_tx_ring.tail = 0;
  uart_tx_ring.size = 0;
  tx_busy = 0;
}

/**
 * @brief DMA1 Stream6 Interrupt Handler for USART2 TX
 */
void stream6ISR(void) {
  if (LL_DMA_IsActiveFlag_TC6(DMA1)) {
    LL_DMA_ClearFlag_TC6(DMA1);
    // LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);

    if (uart_tx_ring.head != uart_tx_ring.tail) {
      // Vẫn còn dữ liệu trong hàng đợi, tiếp tục gửi
      uart_dma_start_tx();
    } else {
      // Hết dữ liệu, giải phóng cờ bận
      tx_busy = 0;
    }
  }
}
