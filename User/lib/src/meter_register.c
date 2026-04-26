/**
 * meter_registers.c — map 3-phase meter values → Modbus holding registers
 *
 * Float32 encoding (big-endian word order, per common meter convention):
 *   register[N]   = high 16 bits of IEEE 754 float
 *   register[N+1] = low  16 bits of IEEE 754 float
 *
 * This matches the byte order used by most DIN-rail energy meters
 * (Eastron SDM, Schneider iEM, ABB B-series, etc.).
 *
 * If your master expects little-endian word order, swap the
 * write_f32() lines: write low word first, high word second.
 */

#include "meter_register.h"
#include "modbus_rtu.h"
#include <string.h>

/* ============================================================
 *  Internal snapshot
 * ============================================================ */
static struct meter_data_s last_meter;

/* ============================================================
 *  Float → two u16 registers (big-endian word order)
 * ============================================================ */
static inline void write_f32(uint16_t reg_addr, float32_t val)
{
	mb_set_float(reg_addr, val);
}

/* ============================================================
 *  Public API
 * ============================================================ */
void meter_update_registers(const struct meter_data_s *m)
{
	/* snapshot for meter_get_data() */
	memcpy(&last_meter, m, sizeof(last_meter));

	/* ── Voltage ─────────────────────────────────────────── */
	write_f32(REG_VA,  m->phase_data[0].rms_voltage);
	write_f32(REG_VB,  m->phase_data[1].rms_voltage);
	write_f32(REG_VC,  m->phase_data[2].rms_voltage);
	write_f32(REG_VAB, m->vol_line.ab);
	write_f32(REG_VBC, m->vol_line.bc);
	write_f32(REG_VCA, m->vol_line.ca);

	/* ── Current ─────────────────────────────────────────── */
	write_f32(REG_IA, m->phase_data[0].rms_current);
	write_f32(REG_IB, m->phase_data[1].rms_current);
	write_f32(REG_IC, m->phase_data[2].rms_current);
	write_f32(REG_IN, m->phase_data[0].rms_current + m->phase_data[1].rms_current + m->phase_data[2].rms_current);

	/* ── Active power ────────────────────────────────────── */
	write_f32(REG_PA,      m->phase_data[0].act_pwr);
	write_f32(REG_PB,      m->phase_data[1].act_pwr);
	write_f32(REG_PC,      m->phase_data[2].act_pwr);
	write_f32(REG_P_TOTAL, m->phase_data[0].act_pwr + m->phase_data[1].act_pwr + m->phase_data[2].act_pwr);

	/* ── Reactive power ──────────────────────────────────── */
	write_f32(REG_QA,      m->phase_data[0].react_pwr);
	write_f32(REG_QB,      m->phase_data[1].react_pwr);
	write_f32(REG_QC,      m->phase_data[2].react_pwr);
	write_f32(REG_Q_TOTAL, m->phase_data[0].react_pwr + m->phase_data[1].react_pwr + m->phase_data[2].react_pwr);

	/* ── Apparent power ──────────────────────────────────── */
	write_f32(REG_SA,      m->phase_data[0].app_pwr);
	write_f32(REG_SB,      m->phase_data[1].app_pwr);
	write_f32(REG_SC,      m->phase_data[2].app_pwr);
	write_f32(REG_S_TOTAL, m->phase_data[0].app_pwr + m->phase_data[1].app_pwr + m->phase_data[2].app_pwr);

	/* ── Power factor ────────────────────────────────────── */
	write_f32(REG_PFA,      m->phase_data[0].pf);
	write_f32(REG_PFB,      m->phase_data[1].pf);
	write_f32(REG_PFC,      m->phase_data[2].pf);
	write_f32(REG_PF_TOTAL, m->phase_data[0].pf + m->phase_data[1].pf + m->phase_data[2].pf);

	/* ── Frequency ───────────────────────────────────────── */
	write_f32(REG_FREQ, m->frequency);

	/* ── Energy ──────────────────────────────────────────── */
	write_f32(REG_KWH_EXP,   m->energy_hWh/10.0f);  /* convert hWh → kWh */
	write_f32(REG_KWH_IMP,   0.0f);  /* not implemented */
	write_f32(REG_KVARH_EXP, 0.0f);  /* not implemented */
	write_f32(REG_KVARH_IMP, 0.0f);  /* not implemented */

	/* ── THD ─────────────────────────────────────────────── */
	write_f32(REG_THD_VA, m->phase_data[0].thd.voltage);
	write_f32(REG_THD_VB, m->phase_data[1].thd.voltage);
	write_f32(REG_THD_VC, m->phase_data[2].thd.voltage);
	write_f32(REG_THD_IA, m->phase_data[0].thd.current);
	write_f32(REG_THD_IB, m->phase_data[1].thd.current);
	write_f32(REG_THD_IC, m->phase_data[2].thd.current);
}

const struct meter_data_s *meter_get_data(void)
{
	return &last_meter;
}