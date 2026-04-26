/**
 * @file    modbus_rtu.c
 * @brief   Modbus RTU Slave — STM32F411, USART2 + DMA1, LL Layer
 *
 * Architecture
 * ─────────────
 *  • LL initialises USART2 and DMA1 Stream5/6 directly (no HAL handle).
 *  • DMA RX Circular feeds raw bytes into dma_rx_buf[].
 *  • USART2 IDLE-line interrupt fires at end of frame:
 *      – reads NDTR to compute received byte count
 *      – snapshots dma_rx_buf[] into rx_buf[]
 *      – sets frame_ready flag for mb_poll()
 *  • mb_poll() validates CRC, dispatches FC, builds reply.
 *  • DMA TX sends reply; TC interrupt switches back to RX mode.
 *
 * CubeMX / project requirements
 * ──────────────────────────────
 *  • Add USE_FULL_LL_DRIVER to preprocessor defines.
 *  • Do NOT generate USART2 or DMA init code — mb_init() handles it.
 *  • Enable in NVIC: USART2, DMA1_Stream5, DMA1_Stream6 (priority 5).
 */

#include "modbus_rtu.h"

#include <string.h>

/* ============================================================
 *  Private types
 * ============================================================ */
enum mb_state {
  mb_state_idle = 0,
  mb_state_rx,
  mb_state_frame_ready,
  mb_state_tx,
};

/* ============================================================
 *  Private state
 * ============================================================ */
static volatile enum mb_state state = mb_state_idle;
static volatile bool frame_ready = false;
static volatile uint16_t rx_len = 0;

static uint8_t dma_rx_buf[MODBUS_RX_BUF_SIZE]; /* DMA circular buffer */
static uint8_t rx_buf[MODBUS_RX_BUF_SIZE];     /* frame snapshot      */
static uint8_t tx_buf[MODBUS_TX_BUF_SIZE];     /* reply buffer        */

static struct mb_data_store data_store;

static TaskHandle_t handle;

/* ============================================================
 *  CRC-16/Modbus lookup table
 * ============================================================ */
static const uint16_t crc_lut[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241, 0xC601,
    0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440, 0xCC01, 0x0CC0,
    0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40, 0x0A00, 0xCAC1, 0xCB81,
    0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841, 0xD801, 0x18C0, 0x1980, 0xD941,
    0x1B00, 0xDBC1, 0xDA81, 0x1A40, 0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01,
    0x1DC0, 0x1C80, 0xDC41, 0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0,
    0x1680, 0xD641, 0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081,
    0x1040, 0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441, 0x3C00,
    0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41, 0xFA01, 0x3AC0,
    0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840, 0x2800, 0xE8C1, 0xE981,
    0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41, 0xEE01, 0x2EC0, 0x2F80, 0xEF41,
    0x2D00, 0xEDC1, 0xEC81, 0x2C40, 0xE401, 0x24C0, 0x2580, 0xE541, 0x2700,
    0xE7C1, 0xE681, 0x2640, 0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0,
    0x2080, 0xE041, 0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281,
    0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41, 0xAA01,
    0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840, 0x7800, 0xB8C1,
    0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41, 0xBE01, 0x7EC0, 0x7F80,
    0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40, 0xB401, 0x74C0, 0x7580, 0xB541,
    0x7700, 0xB7C1, 0xB681, 0x7640, 0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101,
    0x71C0, 0x7080, 0xB041, 0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0,
    0x5280, 0x9241, 0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481,
    0x5440, 0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841, 0x8801,
    0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40, 0x4E00, 0x8EC1,
    0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41, 0x4400, 0x84C1, 0x8581,
    0x4540, 0x8701, 0x47C0, 0x4680, 0x8641, 0x8201, 0x42C0, 0x4380, 0x8341,
    0x4100, 0x81C1, 0x8081, 0x4040,
};

static uint16_t calc_crc16(const uint8_t* buf, uint16_t len) {
  uint16_t crc = 0xFFFF;

  while (len--) crc = (crc >> 8) ^ crc_lut[(crc ^ *buf++) & 0xFF];

  return crc;
}

/* ============================================================
 *  LL hardware initialisation
 * ============================================================ */
static void gpio_init(void) {
  /* PA2 = USART2_TX, PA3 = USART2_RX — AF7 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

  LL_GPIO_InitTypeDef gpio_cfg = {0};

  gpio_cfg.Pin = LL_GPIO_PIN_2 | LL_GPIO_PIN_3;
  gpio_cfg.Mode = LL_GPIO_MODE_ALTERNATE;
  gpio_cfg.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  gpio_cfg.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  gpio_cfg.Pull = LL_GPIO_PULL_UP;
  gpio_cfg.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &gpio_cfg);
}

static void dma_init(void) {
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* ── RX: DMA1 Stream5 Ch4, Periph→Mem, Circular ─────── */
  LL_DMA_DisableStream(MODBUS_DMA, MODBUS_DMA_RX_STREAM);
  while (LL_DMA_IsEnabledStream(MODBUS_DMA, MODBUS_DMA_RX_STREAM));

  LL_DMA_SetChannelSelection(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                             MODBUS_DMA_CHANNEL);
  LL_DMA_SetDataTransferDirection(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                                  LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  LL_DMA_SetStreamPriorityLevel(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                                LL_DMA_PRIORITY_LOW);
  LL_DMA_SetMode(MODBUS_DMA, MODBUS_DMA_RX_STREAM, LL_DMA_MODE_CIRCULAR);
  LL_DMA_SetPeriphIncMode(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                          LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemoryIncMode(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                          LL_DMA_MEMORY_INCREMENT);
  LL_DMA_SetPeriphSize(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                       LL_DMA_PDATAALIGN_BYTE);
  LL_DMA_SetMemorySize(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                       LL_DMA_MDATAALIGN_BYTE);
  LL_DMA_DisableFifoMode(MODBUS_DMA, MODBUS_DMA_RX_STREAM);
  LL_DMA_SetPeriphAddress(MODBUS_DMA, MODBUS_DMA_RX_STREAM,
                          LL_USART_DMA_GetRegAddr(MODBUS_USARTx));
  LL_DMA_SetMemoryAddress(MODBUS_DMA, MODBUS_DMA_RX_STREAM, (uint32_t)dma_rx_buf);
  LL_DMA_SetDataLength(MODBUS_DMA, MODBUS_DMA_RX_STREAM, MODBUS_RX_BUF_SIZE);
  // LL_DMA_EnableIT_TC(MODBUS_DMA, MODBUS_DMA_RX_STREAM);

  /* ── TX: DMA1 Stream6 Ch4, Mem→Periph, Normal ───────── */
  LL_DMA_DisableStream(MODBUS_DMA, MODBUS_DMA_TX_STREAM);
  while (LL_DMA_IsEnabledStream(MODBUS_DMA, MODBUS_DMA_TX_STREAM));

  LL_DMA_SetChannelSelection(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                             MODBUS_DMA_CHANNEL);
  LL_DMA_SetDataTransferDirection(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                                  LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
  LL_DMA_SetStreamPriorityLevel(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                                LL_DMA_PRIORITY_LOW);
  LL_DMA_SetMode(MODBUS_DMA, MODBUS_DMA_TX_STREAM, LL_DMA_MODE_NORMAL);
  LL_DMA_SetPeriphIncMode(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                          LL_DMA_PERIPH_NOINCREMENT);
  LL_DMA_SetMemoryIncMode(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                          LL_DMA_MEMORY_INCREMENT);
  LL_DMA_SetPeriphSize(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                       LL_DMA_PDATAALIGN_BYTE);
  LL_DMA_SetMemorySize(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                       LL_DMA_MDATAALIGN_BYTE);
  LL_DMA_DisableFifoMode(MODBUS_DMA, MODBUS_DMA_TX_STREAM);
  LL_DMA_SetPeriphAddress(MODBUS_DMA, MODBUS_DMA_TX_STREAM,
                          LL_USART_DMA_GetRegAddr(MODBUS_USARTx));
  LL_DMA_EnableIT_TC(MODBUS_DMA, MODBUS_DMA_TX_STREAM);

  NVIC_SetPriority(MODBUS_DMA_RX_IRQn, 5);
  NVIC_EnableIRQ(MODBUS_DMA_RX_IRQn);
  NVIC_SetPriority(MODBUS_DMA_TX_IRQn, 5);
  NVIC_EnableIRQ(MODBUS_DMA_TX_IRQn);
}

static void usart_init(void) {
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

  LL_USART_InitTypeDef usart_cfg = {0};

  usart_cfg.BaudRate = MODBUS_BAUD_RATE;
  usart_cfg.DataWidth = LL_USART_DATAWIDTH_8B;
  usart_cfg.StopBits = LL_USART_STOPBITS_1;
  usart_cfg.Parity = LL_USART_PARITY_NONE;
  usart_cfg.TransferDirection = LL_USART_DIRECTION_TX_RX;
  usart_cfg.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  usart_cfg.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(MODBUS_USARTx, &usart_cfg);
  LL_USART_ConfigAsyncMode(MODBUS_USARTx);

  LL_USART_EnableDMAReq_RX(MODBUS_USARTx);
  LL_USART_EnableDMAReq_TX(MODBUS_USARTx);

  /* IDLE line interrupt — detects inter-frame silence */
  LL_USART_ClearFlag_IDLE(MODBUS_USARTx);
  LL_USART_EnableIT_IDLE(MODBUS_USARTx);

  NVIC_SetPriority(MODBUS_UART_IRQn, 5);
  NVIC_EnableIRQ(MODBUS_UART_IRQn);

  LL_USART_Enable(MODBUS_USARTx);
}

static void start_rx_dma(void) {
  LL_DMA_DisableStream(MODBUS_DMA, MODBUS_DMA_RX_STREAM);
  while (LL_DMA_IsEnabledStream(MODBUS_DMA, MODBUS_DMA_RX_STREAM));
  LL_DMA_SetMemoryAddress(MODBUS_DMA, MODBUS_DMA_RX_STREAM, (uint32_t)dma_rx_buf);
  LL_DMA_SetDataLength(MODBUS_DMA, MODBUS_DMA_RX_STREAM, MODBUS_RX_BUF_SIZE);
  LL_DMA_EnableStream(MODBUS_DMA, MODBUS_DMA_RX_STREAM);
}

static void start_tx_dma(uint16_t len) {
  LL_DMA_DisableStream(MODBUS_DMA, MODBUS_DMA_TX_STREAM);
  while (LL_DMA_IsEnabledStream(MODBUS_DMA, MODBUS_DMA_TX_STREAM));
  LL_DMA_SetMemoryAddress(MODBUS_DMA, MODBUS_DMA_TX_STREAM, (uint32_t)tx_buf);
  LL_DMA_SetDataLength(MODBUS_DMA, MODBUS_DMA_TX_STREAM, len);
  LL_DMA_EnableStream(MODBUS_DMA, MODBUS_DMA_TX_STREAM);
}

/* ============================================================
 *  RS-485 direction control — override __weak if needed
 * ============================================================ */
__attribute__((weak)) void mb_enable_tx(void) {
  /* e.g. LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4); */
}

__attribute__((weak)) void mb_enable_rx(void) {
  /* e.g. LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4); */
}

/* ============================================================
 *  Bit-level helpers for coils / discrete inputs
 * ============================================================ */
static inline void set_bit_val(uint8_t* arr, uint16_t idx, bool val) {
  if (val)
    arr[idx >> 3] |= (1u << (idx & 7));
  else
    arr[idx >> 3] &= ~(1u << (idx & 7));
}

static inline bool get_bit_val(const uint8_t* arr, uint16_t idx) {
  return (arr[idx >> 3] >> (idx & 7)) & 1u;
}

/* ============================================================
 *  Exception response builder
 * ============================================================ */
static uint16_t build_exception(uint8_t fc, uint8_t ex_code) {
  uint16_t crc;

  tx_buf[0] = MODBUS_SLAVE_ADDR;
  tx_buf[1] = fc | 0x80;
  tx_buf[2] = ex_code;
  crc = calc_crc16(tx_buf, 3);
  tx_buf[3] = (uint8_t)(crc);
  tx_buf[4] = (uint8_t)(crc >> 8);

  return 5;
}

/* ============================================================
 *  Function code handlers
 *  Each returns the reply length (bytes) or 0 on silent discard.
 * ============================================================ */

/* FC 01 — Read Coils */
static uint16_t handle_fc01(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t count = (uint16_t)(req[4] << 8) | req[5];
  uint8_t nb, i;
  uint16_t crc;

  if (count < 1 || count > 2000)
    return build_exception(FC_READ_COILS, MB_EX_ILLEGAL_DATA_VALUE);
  if ((addr + count) > MODBUS_COIL_COUNT)
    return build_exception(FC_READ_COILS, MB_EX_ILLEGAL_DATA_ADDR);

  nb = (uint8_t)((count + 7) / 8);
  tx_buf[0] = MODBUS_SLAVE_ADDR;
  tx_buf[1] = FC_READ_COILS;
  tx_buf[2] = nb;
  memset(&tx_buf[3], 0, nb);

  for (i = 0; i < count; i++)
    if (get_bit_val(data_store.coils, addr + i))
      tx_buf[3 + (i >> 3)] |= (1u << (i & 7));

  crc = calc_crc16(tx_buf, 3 + nb);
  tx_buf[3 + nb] = (uint8_t)(crc);
  tx_buf[4 + nb] = (uint8_t)(crc >> 8);

  return (uint16_t)(5 + nb);
}

/* FC 02 — Read Discrete Inputs */
static uint16_t handle_fc02(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t count = (uint16_t)(req[4] << 8) | req[5];
  uint8_t nb, i;
  uint16_t crc;

  if (count < 1 || count > 2000)
    return build_exception(FC_READ_DISCRETE_INPUTS, MB_EX_ILLEGAL_DATA_VALUE);
  if ((addr + count) > MODBUS_DISCRETE_COUNT)
    return build_exception(FC_READ_DISCRETE_INPUTS, MB_EX_ILLEGAL_DATA_ADDR);

  nb = (uint8_t)((count + 7) / 8);
  tx_buf[0] = MODBUS_SLAVE_ADDR;
  tx_buf[1] = FC_READ_DISCRETE_INPUTS;
  tx_buf[2] = nb;
  memset(&tx_buf[3], 0, nb);

  for (i = 0; i < count; i++)
    if (get_bit_val(data_store.discrete_inputs, addr + i))
      tx_buf[3 + (i >> 3)] |= (1u << (i & 7));

  crc = calc_crc16(tx_buf, 3 + nb);
  tx_buf[3 + nb] = (uint8_t)(crc);
  tx_buf[4 + nb] = (uint8_t)(crc >> 8);

  return (uint16_t)(5 + nb);
}

/* FC 03 — Read Holding Registers */
static uint16_t handle_fc03(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t count = (uint16_t)(req[4] << 8) | req[5];
  uint16_t i, len, crc;

  if (count < 1 || count > 125)
    return build_exception(FC_READ_HOLDING_REGS, MB_EX_ILLEGAL_DATA_VALUE);
  if ((addr + count) > MODBUS_HOLDING_REG_COUNT)
    return build_exception(FC_READ_HOLDING_REGS, MB_EX_ILLEGAL_DATA_ADDR);

  tx_buf[0] = MODBUS_SLAVE_ADDR;
  tx_buf[1] = FC_READ_HOLDING_REGS;
  tx_buf[2] = (uint8_t)(count * 2);

  for (i = 0; i < count; i++) {
    tx_buf[3 + i * 2] = (uint8_t)(data_store.holding_regs[addr + i] >> 8);
    tx_buf[3 + i * 2 + 1] = (uint8_t)(data_store.holding_regs[addr + i]);
  }

  len = (uint16_t)(3 + count * 2);
  crc = calc_crc16(tx_buf, len);
  tx_buf[len] = (uint8_t)(crc);
  tx_buf[len + 1] = (uint8_t)(crc >> 8);

  return len + 2;
}

/* FC 04 — Read Input Registers */
static uint16_t handle_fc04(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t count = (uint16_t)(req[4] << 8) | req[5];
  uint16_t i, len, crc;

  if (count < 1 || count > 125)
    return build_exception(FC_READ_INPUT_REGS, MB_EX_ILLEGAL_DATA_VALUE);
  if ((addr + count) > MODBUS_INPUT_REG_COUNT)
    return build_exception(FC_READ_INPUT_REGS, MB_EX_ILLEGAL_DATA_ADDR);

  tx_buf[0] = MODBUS_SLAVE_ADDR;
  tx_buf[1] = FC_READ_INPUT_REGS;
  tx_buf[2] = (uint8_t)(count * 2);

  for (i = 0; i < count; i++) {
    tx_buf[3 + i * 2] = (uint8_t)(data_store.input_regs[addr + i] >> 8);
    tx_buf[3 + i * 2 + 1] = (uint8_t)(data_store.input_regs[addr + i]);
  }

  len = (uint16_t)(3 + count * 2);
  crc = calc_crc16(tx_buf, len);
  tx_buf[len] = (uint8_t)(crc);
  tx_buf[len + 1] = (uint8_t)(crc >> 8);

  return len + 2;
}

/* FC 05 — Write Single Coil */
static uint16_t handle_fc05(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t value = (uint16_t)(req[4] << 8) | req[5];
  uint16_t crc;

  if (value != 0x0000 && value != 0xFF00)
    return build_exception(FC_WRITE_SINGLE_COIL, MB_EX_ILLEGAL_DATA_VALUE);
  if (addr >= MODBUS_COIL_COUNT)
    return build_exception(FC_WRITE_SINGLE_COIL, MB_EX_ILLEGAL_DATA_ADDR);

  set_bit_val(data_store.coils, addr, value == 0xFF00);
  memcpy(tx_buf, req, 6);
  crc = calc_crc16(tx_buf, 6);
  tx_buf[6] = (uint8_t)(crc);
  tx_buf[7] = (uint8_t)(crc >> 8);

  return 8;
}

/* FC 06 — Write Single Register */
static uint16_t handle_fc06(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t value = (uint16_t)(req[4] << 8) | req[5];
  uint16_t crc;

  if (addr >= MODBUS_HOLDING_REG_COUNT)
    return build_exception(FC_WRITE_SINGLE_REG, MB_EX_ILLEGAL_DATA_ADDR);

  data_store.holding_regs[addr] = value;
  memcpy(tx_buf, req, 6);
  crc = calc_crc16(tx_buf, 6);
  tx_buf[6] = (uint8_t)(crc);
  tx_buf[7] = (uint8_t)(crc >> 8);

  return 8;
}

/* FC 0F — Write Multiple Coils */
static uint16_t handle_fc0f(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t count = (uint16_t)(req[4] << 8) | req[5];
  uint8_t nb = req[6];
  uint16_t i, crc;

  if (count < 1 || count > 1968)
    return build_exception(FC_WRITE_MULTIPLE_COILS, MB_EX_ILLEGAL_DATA_VALUE);
  if ((addr + count) > MODBUS_COIL_COUNT)
    return build_exception(FC_WRITE_MULTIPLE_COILS, MB_EX_ILLEGAL_DATA_ADDR);
  if (nb != (uint8_t)((count + 7) / 8))
    return build_exception(FC_WRITE_MULTIPLE_COILS, MB_EX_ILLEGAL_DATA_VALUE);

  for (i = 0; i < count; i++)
    set_bit_val(data_store.coils, addr + i,
                (req[7 + (i >> 3)] >> (i & 7)) & 1u);

  tx_buf[0] = MODBUS_SLAVE_ADDR;
  tx_buf[1] = FC_WRITE_MULTIPLE_COILS;
  tx_buf[2] = req[2];
  tx_buf[3] = req[3];
  tx_buf[4] = req[4];
  tx_buf[5] = req[5];
  crc = calc_crc16(tx_buf, 6);
  tx_buf[6] = (uint8_t)(crc);
  tx_buf[7] = (uint8_t)(crc >> 8);

  return 8;
}

/* FC 10 — Write Multiple Registers */
static uint16_t handle_fc10(const uint8_t* req) {
  uint16_t addr = (uint16_t)(req[2] << 8) | req[3];
  uint16_t count = (uint16_t)(req[4] << 8) | req[5];
  uint8_t nb = req[6];
  uint16_t i, crc;

  if (count < 1 || count > 123)
    return build_exception(FC_WRITE_MULTIPLE_REGS, MB_EX_ILLEGAL_DATA_VALUE);
  if ((addr + count) > MODBUS_HOLDING_REG_COUNT)
    return build_exception(FC_WRITE_MULTIPLE_REGS, MB_EX_ILLEGAL_DATA_ADDR);
  if (nb != (uint8_t)(count * 2))
    return build_exception(FC_WRITE_MULTIPLE_REGS, MB_EX_ILLEGAL_DATA_VALUE);

  for (i = 0; i < count; i++)
    data_store.holding_regs[addr + i] =
        (uint16_t)(req[7 + i * 2] << 8) | req[7 + i * 2 + 1];

  tx_buf[0] = MODBUS_SLAVE_ADDR;
  tx_buf[1] = FC_WRITE_MULTIPLE_REGS;
  tx_buf[2] = req[2];
  tx_buf[3] = req[3];
  tx_buf[4] = req[4];
  tx_buf[5] = req[5];
  crc = calc_crc16(tx_buf, 6);
  tx_buf[6] = (uint8_t)(crc);
  tx_buf[7] = (uint8_t)(crc >> 8);

  return 8;
}

/* ============================================================
 *  Frame dispatcher
 * ============================================================ */
static void process_frame(void) {
  const uint8_t* req = rx_buf;
  uint16_t len = rx_len;
  uint16_t crc_recv, crc_calc;
  uint8_t fc;
  uint16_t reply_len = 0;

  if (len < 4) return;

  crc_recv = (uint16_t)(req[len - 1] << 8) | req[len - 2];
  crc_calc = calc_crc16(req, len - 2);
  if (crc_recv != crc_calc) return;

  if (req[0] != MODBUS_SLAVE_ADDR) return;

  fc = req[1];

  switch (fc) {
    case FC_READ_COILS:
      reply_len = handle_fc01(req);
      break;
    case FC_READ_DISCRETE_INPUTS:
      reply_len = handle_fc02(req);
      break;
    case FC_READ_HOLDING_REGS:
      reply_len = handle_fc03(req);
      break;
    case FC_READ_INPUT_REGS:
      reply_len = handle_fc04(req);
      break;
    case FC_WRITE_SINGLE_COIL:
      reply_len = handle_fc05(req);
      break;
    case FC_WRITE_SINGLE_REG:
      reply_len = handle_fc06(req);
      break;
    case FC_WRITE_MULTIPLE_COILS:
      reply_len = handle_fc0f(req);
      break;
    case FC_WRITE_MULTIPLE_REGS:
      reply_len = handle_fc10(req);
      break;
    default:
      reply_len = build_exception(fc, MB_EX_ILLEGAL_FUNCTION);
      break;
  }

  if (reply_len > 0) {
    state = mb_state_tx;
    mb_enable_tx();
    start_tx_dma(reply_len);
  }
}

/* ============================================================
 *  Public API
 * ============================================================ */
enum mb_status mb_init(TaskHandle_t task_handle) {
  handle = task_handle;
  memset(&data_store, 0, sizeof(data_store));
  state = mb_state_idle;
  frame_ready = false;

  gpio_init();
  dma_init();
  usart_init();

  mb_enable_rx();
  start_rx_dma();

  return mb_ok;
}

void mb_poll(void) {
  if (!frame_ready) return;

  frame_ready = false;
  process_frame();
}

struct mb_data_store* mb_get_data_store(void) { return &data_store; }

/* Coils */
void mb_set_coil(uint16_t addr, bool val) {
  if (addr < MODBUS_COIL_COUNT) set_bit_val(data_store.coils, addr, val);
}

bool mb_get_coil(uint16_t addr) {
  return addr < MODBUS_COIL_COUNT ? get_bit_val(data_store.coils, addr) : false;
}

/* Discrete inputs */
void mb_set_discrete_input(uint16_t addr, bool val) {
  if (addr < MODBUS_DISCRETE_COUNT)
    set_bit_val(data_store.discrete_inputs, addr, val);
}

bool mb_get_discrete_input(uint16_t addr) {
  return addr < MODBUS_DISCRETE_COUNT
             ? get_bit_val(data_store.discrete_inputs, addr)
             : false;
}

/* Input registers */
void mb_set_input_reg(uint16_t addr, uint16_t val) {
  if (addr < MODBUS_INPUT_REG_COUNT) data_store.input_regs[addr] = val;
}

uint16_t mb_get_input_reg(uint16_t addr) {
  return addr < MODBUS_INPUT_REG_COUNT ? data_store.input_regs[addr] : 0;
}

/* Holding registers */
void mb_set_holding_reg(uint16_t addr, uint16_t val) {
  if (addr < MODBUS_HOLDING_REG_COUNT) data_store.holding_regs[addr] = val;
}

uint16_t mb_get_holding_reg(uint16_t addr) {
  return addr < MODBUS_HOLDING_REG_COUNT ? data_store.holding_regs[addr] : 0;
}


void mb_set_float(uint16_t addr, float32_t val) {
	uint32_t raw;
	uint16_t hi, lo;

	/* Type-pun float → u32 without UB */
	memcpy(&raw, &val, sizeof(raw));

	hi = (uint16_t)(raw >> 16);
	lo = (uint16_t)(raw & 0xFFFFu);

	/*
	 * Use mb_set_holding_reg() so values flow through the
	 * existing Modbus input-register store.
	 * Swap to mb_set_input_reg() if you want these read-only
	 * (FC04 only) and reserve holding regs for setpoints.
	 */
	mb_set_holding_reg(addr,     hi);
	mb_set_holding_reg(addr + 1, lo);
}

float32_t mb_get_float(uint16_t addr) {
	uint32_t raw;
	uint16_t hi, lo;

	hi = mb_get_holding_reg(addr);
	lo = mb_get_holding_reg(addr + 1);

	/* Type-pun u32 → float without UB */
	memcpy(&raw, &hi, sizeof(hi));
	raw <<= 16;
	memcpy(&raw, &lo, sizeof(lo));

	return *(float32_t *)&raw;
}

/* ============================================================
 *  IRQ handlers
 * ============================================================ */

/**
 * mb_usart_irq_handler - USART2 IDLE-line interrupt
 *
 * Captures the received byte count from the DMA counter,
 * snapshots the buffer, resets DMA, and signals mb_poll().
 * Call from USART2_IRQHandler() in stm32f4xx_it.c.
 */
void mb_usart_irq_handler(void) {
  uint16_t ndtr, received;

  if (!LL_USART_IsActiveFlag_IDLE(MODBUS_USARTx)) return;

  LL_USART_ClearFlag_IDLE(MODBUS_USARTx);

  if (state == mb_state_tx) /* ignore RS-485 echo */
    return;

  ndtr = (uint16_t)LL_DMA_GetDataLength(MODBUS_DMA, MODBUS_DMA_RX_STREAM);
  received = (uint16_t)(MODBUS_RX_BUF_SIZE - ndtr);

  if (received == 0) return;

  rx_len = received;
  memcpy(rx_buf, dma_rx_buf, received);

  start_rx_dma();

  state = mb_state_frame_ready;
  frame_ready = true;
  
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xTaskNotifyFromISR(handle, 0, eSetBits, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/**
 * mb_dma_rx_irq_handler - DMA1 Stream5 transfer complete / error
 *
 * Handles the unlikely case where the circular buffer fills completely.
 * Call from DMA1_Stream5_IRQHandler() in stm32f4xx_it.c.
 */
void mb_dma_rx_irq_handler(void) {
  if (LL_DMA_IsActiveFlag_TC5(MODBUS_DMA)) {
    LL_DMA_ClearFlag_TC5(MODBUS_DMA);
    start_rx_dma(); /* buffer overflow — reset and discard */
  }
  if (LL_DMA_IsActiveFlag_TE5(MODBUS_DMA)) {
    LL_DMA_ClearFlag_TE5(MODBUS_DMA);
    start_rx_dma();
  }
}

/**
 * mb_dma_tx_irq_handler - DMA1 Stream6 transfer complete / error
 *
 * Waits for the shift register to drain, de-asserts DE, then
 * restarts RX DMA.
 * Call from DMA1_Stream6_IRQHandler() in stm32f4xx_it.c.
 */
void mb_dma_tx_irq_handler(void) {
  if (LL_DMA_IsActiveFlag_TC6(MODBUS_DMA)) {
    LL_DMA_ClearFlag_TC6(MODBUS_DMA);

    /* Wait for last byte to leave the shift register */
    while (!LL_USART_IsActiveFlag_TC(MODBUS_USARTx));
    LL_USART_ClearFlag_TC(MODBUS_USARTx);

    mb_enable_rx();
    state = mb_state_idle;
    start_rx_dma();
  }
  if (LL_DMA_IsActiveFlag_TE6(MODBUS_DMA)) {
    LL_DMA_ClearFlag_TE6(MODBUS_DMA);
    mb_enable_rx();
    state = mb_state_idle;
  }
}