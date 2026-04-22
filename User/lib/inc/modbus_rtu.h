#ifndef MODBUS_RTU_H
#define MODBUS_RTU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "meter_register.h"

/* LL layer — no HAL handle needed */
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include <stdbool.h>

/* Linux kernel-style fixed-width type aliases */
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;

/* ============================================================
 *  MODBUS RTU MODULE — STM32F411 / USART2 + DMA (LL Layer)
 *  Supports: Slave mode
 *  Function codes: 0x01 0x02 0x03 0x04 0x05 0x06 0x0F 0x10
 * ============================================================ */

/* ---------- Hardware mapping --------------------------------
 *  USART2 TX → PA2   (AF7)
 *  USART2 RX → PA3   (AF7)
 *  DMA1 Stream5 Ch4  → USART2_RX  (Circular)
 *  DMA1 Stream6 Ch4  → USART2_TX  (Normal)
 * ---------------------------------------------------------- */
#define MODBUS_USARTx               USART2
#define MODBUS_UART_IRQn            USART2_IRQn

#define MODBUS_DMA                  DMA1
#define MODBUS_DMA_RX_STREAM        LL_DMA_STREAM_5
#define MODBUS_DMA_TX_STREAM        LL_DMA_STREAM_6
#define MODBUS_DMA_CHANNEL          LL_DMA_CHANNEL_4
#define MODBUS_DMA_RX_IRQn          DMA1_Stream5_IRQn
#define MODBUS_DMA_TX_IRQn          DMA1_Stream6_IRQn

/* ---------- Slave configuration ---------------------------- */
#define MODBUS_SLAVE_ADDR           1           /* 1–247 */
#define MODBUS_BAUD_RATE            115200UL
#define MODBUS_APB1_FREQ_HZ         42000000UL  /* STM32F411 @ 100 MHz: APB1 = 42 MHz */

#define MODBUS_RX_BUF_SIZE          2048
#define MODBUS_TX_BUF_SIZE          512

/* Register counts — adjust to application */
#define MODBUS_COIL_COUNT           64
#define MODBUS_DISCRETE_COUNT       64
#define MODBUS_INPUT_REG_COUNT      32
#define MODBUS_HOLDING_REG_COUNT    128

/* T3.5 inter-frame silence (µs) */
#if (MODBUS_BAUD_RATE <= 19200UL)
  #define MODBUS_T35_US             1750u
#else
  #define MODBUS_T35_US             ((3500000UL / MODBUS_BAUD_RATE) + 1u)
#endif

/* ---------- Function Codes --------------------------------- */
#define FC_READ_COILS               0x01
#define FC_READ_DISCRETE_INPUTS     0x02
#define FC_READ_HOLDING_REGS        0x03
#define FC_READ_INPUT_REGS          0x04
#define FC_WRITE_SINGLE_COIL        0x05
#define FC_WRITE_SINGLE_REG         0x06
#define FC_WRITE_MULTIPLE_COILS     0x0F
#define FC_WRITE_MULTIPLE_REGS      0x10

/* ---------- Exception Codes -------------------------------- */
#define MB_EX_NONE                  0x00
#define MB_EX_ILLEGAL_FUNCTION      0x01
#define MB_EX_ILLEGAL_DATA_ADDR     0x02
#define MB_EX_ILLEGAL_DATA_VALUE    0x03
#define MB_EX_DEVICE_FAILURE        0x04

/* ---------- Public Types ----------------------------------- */

/* Linux kernel style: no typedef on enum/struct */
enum mb_status {
	mb_ok = 0,
	mb_err_init,
	mb_err_crc,
	mb_err_addr,
	mb_err_frame,
};

struct mb_data_store {
	u8  coils[MODBUS_COIL_COUNT / 8 + 1];
	u8  discrete_inputs[MODBUS_DISCRETE_COUNT / 8 + 1];
	u16 input_regs[MODBUS_INPUT_REG_COUNT];
	u16 holding_regs[MODBUS_HOLDING_REG_COUNT];
};

/* ---------- Public API ------------------------------------- */

/**
 * mb_init - initialise Modbus RTU slave
 *
 * Self-configures USART2 and DMA1 via LL — do NOT call
 * MX_USART2_UART_Init() or MX_DMA_Init() from CubeMX.
 * Requires GPIOA clock already enabled.
 *
 * Return: mb_ok on success, mb_err_init on failure.
 */
enum mb_status mb_init(TaskHandle_t task_handle);

/**
 * mb_poll - process one pending Modbus frame
 *
 * Call as often as possible from the main loop or an RTOS task.
 * Validates CRC, dispatches the function code, and sends the reply.
 */
void mb_poll(void);

/**
 * mb_get_data_store - return pointer to the live register store
 *
 * The application may read/write registers directly through this
 * pointer between calls to mb_poll().
 */
struct mb_data_store *mb_get_data_store(void);

/* Register accessor helpers */
void mb_set_coil(u16 addr, bool val);
bool mb_get_coil(u16 addr);

void mb_set_discrete_input(u16 addr, bool val);
bool mb_get_discrete_input(u16 addr);

void mb_set_input_reg(u16 addr, u16 val);
u16  mb_get_input_reg(u16 addr);

void mb_set_holding_reg(u16 addr, u16 val);
u16  mb_get_holding_reg(u16 addr);

/* ---------- IRQ handlers — place in stm32f4xx_it.c ----------
 *
 *  void USART2_IRQHandler(void)       { mb_usart_irq_handler();   }
 *  void DMA1_Stream5_IRQHandler(void) { mb_dma_rx_irq_handler();  }
 *  void DMA1_Stream6_IRQHandler(void) { mb_dma_tx_irq_handler();  }
 */
void mb_usart_irq_handler(void);
void mb_dma_rx_irq_handler(void);
void mb_dma_tx_irq_handler(void);

/* RS-485 DE/RE direction — override __weak if using RS-485 transceiver */
void mb_enable_tx(void);
void mb_enable_rx(void);

#ifdef __cplusplus
}
#endif
#endif /* MODBUS_RTU_H */