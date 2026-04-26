

/**
 * calib.c — calibration module built around dsp_coef_s
 *
 * Modbus layout (FC03 read-back / FC10 write from PC):
 *   Phase block  : 0x0100 – 0x011D  (3 phases × 5 floats × 2 regs)
 *   VLL block    : 0x011E – 0x0129  (3 lines  × 2 floats × 2 regs)
 *   CMD save     : 0x012A
 *   CMD reset    : 0x012C
 *
 * Flash layout at CALIB_FLASH_ADDR:
 *   calib_flash_image { u32 magic; struct dsp_coef_s coef; }
 * 
 */

#include "calib.h"
#include "app_cfg.h"
#include "modbus_rtu.h"

#ifndef DSP_USE_FLOAT
#define DEFAULT_VOLTAGE_RMS 220
#define DEFAULT_CURRENT_RMS 5
#define MAX_VOLTAGE_RMS 250
#define MAX_CURRENT_RMS 6
#define SQRT2_SCALED 1414
#define ADC_RESOLUTION 4096  // Assuming 12-bit ADC
#define MAX_VOLTAGE_RMS_SCALED_MV (MAX_VOLTAGE_RMS * 1000)  // mV
#define MAX_CURRENT_RMS_SCALED_MA (MAX_CURRENT_RMS * 1000)  // mA
#define PEAK_VOLTAGE_SCALED_MV \
  (MAX_VOLTAGE_RMS_SCALED_MV * SQRT2_SCALED)  // Peak voltage in mV
#define PEAK_CURRENT_SCALED_MA \
  (MAX_CURRENT_RMS_SCALED_MA * SQRT2_SCALED)  // Peak current in mA
#define DEFAULT_COEF_VOLTAGE                        \
  (PEAK_VOLTAGE_SCALED_MV / (ADC_RESOLUTION << 3) / \
   1000)  // Coefficient to convert ADC value to mV, considering the shift left
          // by 4 in adc_sample.c
#define DEFAULT_COEF_CURRENT                        \
  (PEAK_CURRENT_SCALED_MA / (ADC_RESOLUTION << 3) / \
   1000)  // Coefficient to convert ADC value to mA, considering the shift left
          // by 4 in adc_sample.c

#define DEFAULT_CURRENT_PHASE_SHIFT_DEGREE 0.0f
#define DEFAULT_ADC_OFFSET_VALUE 2048
#else
#define DEFAULT_VOLTAGE_RMS 220.0f
#define DEFAULT_CURRENT_RMS 5.0f
#define MAX_VOLTAGE_RMS 250.0f
#define MAX_CURRENT_RMS 6.0f
#define SQRT2_SCALED 1.4142135623731f
#define ADC_RESOLUTION 4095.0f  // Assuming 12-bit ADC
#define MAX_VOLTAGE_RMS_SCALED_MV (MAX_VOLTAGE_RMS * 1000.0f)  // mV
#define MAX_CURRENT_RMS_SCALED_MA (MAX_CURRENT_RMS * 1000.0f)  // mA
#define PEAK_VOLTAGE_SCALED_MV \
  (MAX_VOLTAGE_RMS_SCALED_MV * SQRT2_SCALED)  // Peak voltage in mV
#define PEAK_CURRENT_SCALED_MA \
  (MAX_CURRENT_RMS_SCALED_MA * SQRT2_SCALED)  // Peak current in mA
#define DEFAULT_COEF_VOLTAGE (MAX_VOLTAGE_RMS * SQRT2_SCALED)
#define DEFAULT_COEF_CURRENT (MAX_CURRENT_RMS * SQRT2_SCALED)

#define START_VOLTAGE 85.0f
#define START_CURRENT 0.015f

#define DEFAULT_CURRENT_PHASE_SHIFT_DEGREE 0.0f
#define DEFAULT_ADC_OFFSET_VALUE 2048.0f
#endif

const struct calib_starting_current_voltage cg_start_current_voltage = {
    .start_current = START_CURRENT, .start_voltage = START_VOLTAGE};

static const struct dsp_coef_s default_dsp_coef = {
    .phase_coef = {{.v_coef = DEFAULT_COEF_VOLTAGE,
                   .i_coef = DEFAULT_COEF_CURRENT,
                   .i_phase_shift = DEFAULT_CURRENT_PHASE_SHIFT_DEGREE,
                   .v_offset = DEFAULT_ADC_OFFSET_VALUE,
                   .i_offset = DEFAULT_ADC_OFFSET_VALUE},
                  {.v_coef = DEFAULT_COEF_VOLTAGE,
                   .i_coef = DEFAULT_COEF_CURRENT,
                   .i_phase_shift = DEFAULT_CURRENT_PHASE_SHIFT_DEGREE,
                   .v_offset = DEFAULT_ADC_OFFSET_VALUE,
                   .i_offset = DEFAULT_ADC_OFFSET_VALUE},
                  {.v_coef = DEFAULT_COEF_VOLTAGE,
                   .i_coef = DEFAULT_COEF_CURRENT,
                   .i_phase_shift = DEFAULT_CURRENT_PHASE_SHIFT_DEGREE,
                   .v_offset = DEFAULT_ADC_OFFSET_VALUE,
                   .i_offset = DEFAULT_ADC_OFFSET_VALUE}},
      .vll = {.ab_gain = DEFAULT_COEF_VOLTAGE,
              .bc_gain = DEFAULT_COEF_VOLTAGE,
              .ca_gain = DEFAULT_COEF_VOLTAGE,
			  .ab_offset = DEFAULT_ADC_OFFSET_VALUE,
			  .bc_offset = DEFAULT_ADC_OFFSET_VALUE,
			  .ca_offset = DEFAULT_ADC_OFFSET_VALUE}};

/* ── Live coefficient store (exported for inline functions) ─── */
struct dsp_coef_s calib_live_coef;


const struct dsp_coef_s calib_get_dsp_coef(void) { return calib_live_coef; }

const struct calib_starting_current_voltage calib_get_threshold(void) {
  return cg_start_current_voltage;
}
/* ============================================================
 *  Modbus register helpers
 * ============================================================ */
static inline void reg_set_f32(uint16_t addr, float32_t val)
{
	mb_set_float(addr, val);
}

static inline float32_t reg_get_f32(uint16_t addr)
{
	return mb_get_float(addr);
}

/* ── push: calib_live_coef → Modbus registers ────────────────── */
static void push_to_regs(void)
{
	uint16_t addr = CALIB_REG_BASE;
	int ph;

	for (ph = 0; ph < METER_PHASE_COUNT; ph++) {
		const struct dsp_phase_coef_s *c = &calib_live_coef.phase_coef[ph];
		reg_set_f32(addr,     c->v_coef);
		reg_set_f32(addr + 2, c->i_coef);
		reg_set_f32(addr + 4, c->i_phase_shift);
		reg_set_f32(addr + 6, c->v_offset);
		reg_set_f32(addr + 8, c->i_offset);
		addr += 10;   /* 5 floats × 2 regs */
	}

	/* vll block starts at CALIB_REG_VLL_BASE = 0x011E */
	addr = CALIB_REG_VLL_BASE;
	reg_set_f32(addr,      calib_live_coef.vll.ab_gain);
	reg_set_f32(addr +  2, calib_live_coef.vll.ab_offset);
	reg_set_f32(addr +  4, calib_live_coef.vll.bc_gain);
	reg_set_f32(addr +  6, calib_live_coef.vll.bc_offset);
	reg_set_f32(addr +  8, calib_live_coef.vll.ca_gain);
	reg_set_f32(addr + 10, calib_live_coef.vll.ca_offset);

	/* clear CMD registers */
	reg_set_f32(CALIB_REG_CMD_SAVE,  0.0f);
	reg_set_f32(CALIB_REG_CMD_RESET, 0.0f);
}

/* ── pull: Modbus registers → calib_live_coef ────────────────── */
static void pull_from_regs(void)
{
	uint16_t addr = CALIB_REG_BASE;
	int ph;

	for (ph = 0; ph < METER_PHASE_COUNT; ph++) {
		struct dsp_phase_coef_s *c = &calib_live_coef.phase_coef[ph];
		c->v_coef         = reg_get_f32(addr);
		c->i_coef         = reg_get_f32(addr + 2);
		c->i_phase_shift  = reg_get_f32(addr + 4);
		c->v_offset       = reg_get_f32(addr + 6);
		c->i_offset       = reg_get_f32(addr + 8);
		addr += 10;
	}

	addr = CALIB_REG_VLL_BASE;
	calib_live_coef.vll.ab_gain    = reg_get_f32(addr);
	calib_live_coef.vll.ab_offset  = reg_get_f32(addr +  2);
	calib_live_coef.vll.bc_gain    = reg_get_f32(addr +  4);
	calib_live_coef.vll.bc_offset  = reg_get_f32(addr +  6);
	calib_live_coef.vll.ca_gain    = reg_get_f32(addr +  8);
	calib_live_coef.vll.ca_offset  = reg_get_f32(addr + 10);
}

/* ============================================================
 *  Flash save / load
 * ============================================================ */
void calib_save(void)
{
	// struct calib_flash_image img;
	// const uint32_t *src;
	// uint32_t addr, words, i, error;
	// FLASH_EraseInitTypeDef erase = {
	// 	.TypeErase    = FLASH_TYPEERASE_SECTORS,
	// 	.Sector       = CALIB_FLASH_SECTOR,
	// 	.NbSectors    = 1,
	// 	.VoltageRange = FLASH_VOLTAGE_RANGE_3,
	// };

	// img.magic = CALIB_MAGIC;
	// memcpy(&img.coef, &calib_live_coef, sizeof(img.coef));

	// src   = (const uint32_t *)&img;
	// addr  = CALIB_FLASH_ADDR;
	// words = (sizeof(img) + 3u) / 4u;

	// HAL_FLASH_Unlock();

	// if (HAL_FLASHEx_Erase(&erase, &error) != HAL_OK)
	// 	goto done;

	// for (i = 0; i < words; i++) {
	// 	if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,
	// 			      addr + i * 4u, src[i]) != HAL_OK)
	// 		break;
	// }

// done:
	// HAL_FLASH_Lock();
	reg_set_f32(CALIB_REG_CMD_SAVE, 0.0f);   /* auto-clear CMD */
}

static void load_from_flash(void)
{
	const struct calib_flash_image *img =
		(const struct calib_flash_image *)CALIB_FLASH_ADDR;

	if (img->magic == CALIB_MAGIC)
		memcpy(&calib_live_coef, &img->coef, sizeof(calib_live_coef));
	else
		memcpy(&calib_live_coef, &default_dsp_coef,  sizeof(calib_live_coef));
}

/* ============================================================
 *  Reset to factory defaults
 * ============================================================ */
void calib_reset(void)
{
	// FLASH_EraseInitTypeDef erase = {
	// 	.TypeErase    = FLASH_TYPEERASE_SECTORS,
	// 	.Sector       = CALIB_FLASH_SECTOR,
	// 	.NbSectors    = 1,
	// 	.VoltageRange = FLASH_VOLTAGE_RANGE_3,
	// };
	// uint32_t error;

	memcpy(&calib_live_coef, &default_dsp_coef, sizeof(calib_live_coef));
	push_to_regs();

	/* Erase Flash so next boot also gets defaults */
	// HAL_FLASH_Unlock();
	// HAL_FLASHEx_Erase(&erase, &error);
	// HAL_FLASH_Lock();

	reg_set_f32(CALIB_REG_CMD_RESET, 0.0f);
}

/* ============================================================
 *  Public API
 * ============================================================ */
void calib_init(void)
{
	load_from_flash();
	push_to_regs();
}

void calib_poll(void)
{
	float32_t cmd_save, cmd_reset;

	/* Always sync registers → live coef so PC edits take effect */
	pull_from_regs();

	cmd_save  = reg_get_f32(CALIB_REG_CMD_SAVE);
	cmd_reset = reg_get_f32(CALIB_REG_CMD_RESET);

	if (cmd_save  >= 1.0f)
		calib_save();

	if (cmd_reset >= 1.0f)
		calib_reset();
}

const struct dsp_coef_s *calib_get_coef(void)
{
	return &calib_live_coef;
}

/* ============================================================
 *  Phase-shift correction
 *
 *  i_corrected = i_d * cos(θ) + i_q * sin(θ)
 *
 *  where:
 *    i_d = in-phase current sample (amplitude-calibrated)
 *    i_q = 90° quadrature sample
 *    θ   = i_phase_shift in radians
 *
 *  For small angles (|θ| < 5°), sin(θ) ≈ θ and cos(θ) ≈ 1,
 *  reducing to:  i_corrected ≈ i_d + i_q * θ_rad
 * ============================================================ */
float32_t calib_apply_i_phase(int ph, float32_t i_d, float32_t i_q)
{
	float32_t theta_rad, cos_t, sin_t;

	if (ph < 0 || ph >= METER_PHASE_COUNT)
		return i_d;

	theta_rad = calib_live_coef.phase_coef[ph].i_phase_shift
	            * (3.14159265f / 180.0f);

	if (theta_rad == 0.0f)
		return i_d;

	cos_t = cosf(theta_rad);
	sin_t = sinf(theta_rad);

	return i_d * cos_t + i_q * sin_t;
}

/* ============================================================
 *  Line-to-line voltage calibration
 *  line: 0=Vab, 1=Vbc, 2=Vca
 * ============================================================ */
float32_t calib_apply_vll(int line, float32_t raw)
{
	const struct vol_line_coef_s *vll = &calib_live_coef.vll;

	switch (line) {
	case 0: return vll->ab_gain * raw + vll->ab_offset;
	case 1: return vll->bc_gain * raw + vll->bc_offset;
	case 2: return vll->ca_gain * raw + vll->ca_offset;
	default: return raw;
	}
}