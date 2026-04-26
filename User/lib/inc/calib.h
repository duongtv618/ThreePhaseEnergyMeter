#ifndef CALIB_H
#define CALIB_H

#include "share_types.h"

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

  struct vol_line_coef_s vll;
 *
 *  Addr   Parameter
 *  ─────────────────────────────────────────
 *  0x0100  Va gain
 *  0x0102  Ia gain
 *  0x0104  Ia phase_deg
 *  0x0106  Va offset
 *  0x0108  Ia offset
 *  0x010A  Vb gain
 *  0x010C  Ib gain
 *  0x010E  Ib phase_deg
 *  0x0110  Vb offset
 *  0x0112  Ib offset
 *  0x0114  Vc gain
 *  0x0116  Ic gain
 *  0x0118  Ic phase_deg
 *  0x011A  Vc offset
 *  0x011C  Ic offset
 *  0x011E  Vll gain
 *  0x0120  Vll offset
 *  0x0122  reserved for future use
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

#define CALIB_REG_START      0x0100
#define CALIB_REG_VGAIN     CALIB_REG_START
#define CALIB_REG_IGAIN     0x0102
#define CALIB_REG_IAPHASE    0x0104
#define CALIB_REG_VAOFFSET   0x0106
#define CALIB_REG_IAOFFSET   0x0108
#define CALIB_REG_VBGAIN    0x010A
#define CALIB_REG_IBGAIN    0x010C
#define CALIB_REG_IBPHASE    0x010E
#define CALIB_REG_VBOFFSET  0x0110
#define CALIB_REG_IBOFFSET  0x0112
#define CALIB_REG_VCGAIN  0x0114
#define CALIB_REG_ICGAIN  0x0116
#define CALIB_REG_ICPHASE  0x0118
#define CALIB_REG_VCOFFSET  0x011A
#define CALIB_REG_ICOFFSET  0x011C

#define CALIB_REG_VLL_START 0x011E  /* Vll gain starts here, 2 regs each for gain and offset */
#define CALIB_REG_VLL_AB_GAIN  CALIB_REG_VLL_START
#define CALIB_REG_VLL_BC_GAIN  0x0120
#define CALIB_REG_VLL_CA_GAIN  0x0122
#define CALIB_REG_VLL_AB_OFFSET 0x0124
#define CALIB_REG_VLL_BC_OFFSET 0x0126
#define CALIB_REG_VLL_CA_OFFSET 0x0128
#define CALIB_REG_VLL_STOP CALIB_REG_VLL_CA_OFFSET

#define CALIB_REG_BASE      0x0100
#define CALIB_REG_VLL_BASE  CALIB_REG_VLL_AB_GAIN
#define CALIB_REG_CMD_SAVE  (CALIB_REG_VLL_STOP + 2)
#define CALIB_REG_CMD_RESET (CALIB_REG_CMD_SAVE + 2)
#define CALIB_REG_COUNT     ((CALIB_REG_CMD_RESET) + 2)

/**
 * @brief Structure to hold starting current and voltage thresholds
 * 
 */
struct calib_starting_current_voltage {
  float32_t start_current;/* Starting current threshold */
  float32_t start_voltage;/* Starting voltage threshold */
};

/**
 * @brief Flash image structure for storing calibration data persistently
 * 
 */
struct calib_flash_image {
	uint32_t magic;
	struct dsp_coef_s  coef;
  struct calib_starting_current_voltage start_ui;
};


/**
 * @brief Structure to hold calibration data
 * 
 */
struct calib_data_s {
  struct dsp_coef_s dsp_coef;/* Calibration data */
};

const struct calib_starting_current_voltage calib_get_threshold(void);
const struct dsp_coef_s calib_get_dsp_coef(void);
void calib_save(void);
void calib_reset(void);
void calib_init(void);
void calib_poll(void);

/* ── Public API ─────────────────────────────────────────────── */
 
/**
 * calib_init - load dsp_coef_s from Flash (or defaults if Flash blank/invalid).
 *              Pushes all values into Modbus holding registers.
 *              Call once after mb_init().
 */
void calib_init(void);
 
/**
 * calib_poll - service Modbus-written coefficient registers.
 *              Pulls any PC-written values into the live dsp_coef_s,
 *              then handles CMD_SAVE / CMD_RESET.
 *              Call every cycle alongside mb_poll().
 */
void calib_poll(void);
 
/**
 * calib_get_coef - return const pointer to the live dsp_coef_s.
 *                  Pass directly to your DSP measurement functions.
 */
const struct dsp_coef_s *calib_get_coef(void);
 
/**
 * calib_apply_v - apply phase voltage calibration inline.
 * @ph  : phase index (0=A, 1=B, 2=C)
 * @raw : raw ADC-derived instantaneous or RMS voltage
 * Return: calibrated value
 */
static inline float32_t calib_apply_v(int ph, float32_t raw)
{
	extern struct dsp_coef_s calib_live_coef;
	const struct dsp_phase_coef_s *c = &calib_live_coef.phase_coef[ph];
	return c->v_coef * raw + c->v_offset;
}
 
/**
 * calib_apply_i - apply phase current calibration inline.
 * @ph  : phase index (0=A, 1=B, 2=C)
 * @raw : raw ADC-derived instantaneous or RMS current
 * Return: calibrated value (amplitude correction only;
 *         phase shift is applied by calib_apply_i_phase when
 *         the quadrature component is available)
 */
static inline float32_t calib_apply_i(int ph, float32_t raw)
{
	extern struct dsp_coef_s calib_live_coef;
	const struct dsp_phase_coef_s *c = &calib_live_coef.phase_coef[ph];
	return c->i_coef * raw + c->i_offset;
}
 
/**
 * calib_apply_i_phase - apply current phase-shift correction.
 *
 * For instantaneous DSP (Clarke transform input):
 *   i_corrected = i_inphase * cos(θ) + i_quad * sin(θ)
 *
 * @ph     : phase index
 * @i_d    : in-phase current sample  (already amplitude-calibrated)
 * @i_q    : 90° quadrature sample    (e.g. from Hilbert or prev sample)
 * Return  : phase-corrected current sample
 */
float32_t calib_apply_i_phase(int ph, float32_t i_d, float32_t i_q);
 
/**
 * calib_apply_vll - apply line-to-line voltage calibration.
 * @line : 0=Vab, 1=Vbc, 2=Vca
 * @raw  : raw line-to-line voltage
 */
float32_t calib_apply_vll(int line, float32_t raw);
 
/**
 * calib_save  - erase Flash sector 7 and write current dsp_coef_s.
 * calib_reset - reload factory defaults into live coef and registers.
 */
void calib_save(void);
void calib_reset(void);

#endif /* CALIB_H */