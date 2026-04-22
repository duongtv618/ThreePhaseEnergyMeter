#ifndef CALIB_H
#define CALIB_H

#include "share_types.h"
#include "modbus_rtu.h"

/*
 * calib.h — per-channel calibration module
 *
 * Model per channel:
 *   y = gain * x + offset        (voltage / current amplitude)
 *   y_corrected = rotate(y, phase_deg)   (phase angle trim, degrees)
 *
 * Channels (all independent):
 *   Va, Vb, Vc  — phase voltages
 *   Ia, Ib, Ic  — phase currents
 *
 * P, Q, S, PF are derived from calibrated V and I — no separate calib needed.
 *
 * Storage:
 *   • Modbus holding registers  0x0100 – 0x017F  (FC03 read, FC10 write)
 *   • STM32F411 internal Flash  sector 7 (0x0806 0000, 128 kB)
 *     Written by calib_save(), loaded by calib_load() at startup.
 *
 * Modbus register map (float32, big-endian word order, 2 regs each):
 * 
  float32_t v_coef;
  float32_t i_coef;
  float32_t i_phase_shift;  // in degree, for current phase shift compensation
  float32_t v_offset;
  float32_t i_offset;

  volline_t vll;
 *
 *  Addr   Parameter
 *  ─────────────────────────────────────────
 *  0x0100  Va gain
 *  0x0102  Ia gain
 *  0x0104  Ia phase_deg
 *  0x0106  Va offset
 *  0x0108  Va offset
 *  0x010A  Vb gain
 *  0x010C  Ib gain
 *  0x010E  Ib phase_deg
 *  0x0110  Vb offset
 *  0x0112  Ib offset
 *  0x0114  Ia offset
 *  0x0116  Ia phase_deg
 *  0x0118  Ib gain
 *  0x011A  Ib offset
 *  0x011C  Ib phase_deg
 *  0x011E  Ic gain
 *  0x0120  Ic offset
 *  0x0122  Ic phase_deg
 *  ─────────────────────────────────────────
 *  0x0124  CMD: write 1.0 → save to Flash
 *  0x0126  CMD: write 1.0 → reset to defaults
 *  ─────────────────────────────────────────
 *  Total: 0x0128 - 0x0100 = 40 registers
 */

/* ── Flash storage ──────────────────────────────────────────
 * STM32F411 Flash sector 7: 0x08060000, size 128 kB.
 * Adjust if your linker script reserves a different sector.    */
#define CALIB_FLASH_ADDR    0x08060000UL
#define CALIB_FLASH_SECTOR  FLASH_SECTOR_7
#define CALIB_MAGIC         0xCA11B00CUL   /* sanity check word */
 
/* ── Modbus register base ──────────────────────────────────── */
#define CALIB_REG_BASE      0x0100
#define CALIB_REG_CMD_SAVE  0x0124
#define CALIB_REG_CMD_RESET 0x0126
#define CALIB_REG_COUNT     40             /* registers reserved for calib */

struct calib_starting_current_voltage {
  float32_t start_current;
  float32_t start_voltage;
};

const struct calib_starting_current_voltage calib_get_threshold(void);
const struct dsp_coef_s calib_get_dsp_coef(void);
void calib_save(void);
void calib_reset(void);
void calib_init(void);
void calib_poll(void);

#endif /* CALIB_H */