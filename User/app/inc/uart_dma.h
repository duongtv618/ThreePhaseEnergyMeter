#ifndef UART_DMA_H
#define UART_DMA_H

#include <stdint.h>

void uart_dma_init(void);
uint16_t uart_dma_available(void);
uint8_t uart_dma_read_byte(void);
uint16_t uart_dma_read(uint8_t *data, uint16_t len);
void uart_dma_write_byte(uint8_t byte);
void uart_dma_write(const uint8_t *data, uint16_t len);
void uart_dma_update(void);
void uart_dma_flush(void);

#endif /* UART_DMA_H */