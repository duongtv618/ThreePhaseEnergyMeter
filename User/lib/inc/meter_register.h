#ifndef METER_REGISTERS_H
#define METER_REGISTERS_H

/*
 * meter_registers.h — 3-phase power meter Modbus register map
 *
 * Encoding: IEEE 754 float32, big-endian word order
 *           Each parameter occupies 2 consecutive holding registers.
 *           Register address = base address shown below.
 *           High word at addr N, low word at addr N+1.
 *
 * Master read example (FC03):
 *   Read 2 regs at 0x0000 → Va_rms [V]
 *   Read 2 regs at 0x0002 → Vb_rms [V]
 *   ...
 *
 * Total holding registers used: METER_REG_COUNT (see below)
 */

#include "share_types.h"
#include <stdint.h>

/* ============================================================
 *  Register base addresses  (each entry = 2 x u16 registers)
 * ============================================================
 *
 *  ┌────────────────────────────────┬──────┬───────┬────────┐
 *  │ Parameter                      │ Addr │ Unit  │ Range  │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Voltage --                  │      │       │        │
 *  │ Va RMS                         │ 0x00 │ V     │ 0–250  │
 *  │ Vb RMS                         │ 0x02 │ V     │ 0-250  │
 *  │ Vc RMS                         │ 0x04 │ V     │ 0–250  │
 *  │ Vab line-to-line               │ 0x06 │ V     │ 0–250  │
 *  │ Vbc line-to-line               │ 0x08 │ V     │ 0–250  │
 *  │ Vca line-to-line               │ 0x0A │ V     │ 0–250  │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Current --                  │      │       │        │
 *  │ Ia RMS                         │ 0x0C │ A     │ 0–9999 │
 *  │ Ib RMS                         │ 0x0E │ A     │ 0–9999 │
 *  │ Ic RMS                         │ 0x10 │ A     │ 0–9999 │
 *  │ In (neutral)                   │ 0x12 │ A     │ 0–9999 │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Active Power --             │      │       │        │
 *  │ Pa                             │ 0x14 │ W     │ ±9999k │
 *  │ Pb                             │ 0x16 │ W     │ ±9999k │
 *  │ Pc                             │ 0x18 │ W     │ ±9999k │
 *  │ P_total                        │ 0x1A │ W     │ ±9999k │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Reactive Power --           │      │       │        │
 *  │ Qa                             │ 0x1C │ VAr   │ ±9999k │
 *  │ Qb                             │ 0x1E │ VAr   │ ±9999k │
 *  │ Qc                             │ 0x20 │ VAr   │ ±9999k │
 *  │ Q_total                        │ 0x22 │ VAr   │ ±9999k │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Apparent Power --           │      │       │        │
 *  │ Sa                             │ 0x24 │ VA    │ 0–9999k│
 *  │ Sb                             │ 0x26 │ VA    │ 0–9999k│
 *  │ Sc                             │ 0x28 │ VA    │ 0–9999k│
 *  │ S_total                        │ 0x2A │ VA    │ 0–9999k│
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Power Factor --             │      │       │        │
 *  │ PFa                            │ 0x2C │ —     │ -1..+1 │
 *  │ PFb                            │ 0x2E │ —     │ -1..+1 │
 *  │ PFc                            │ 0x30 │ —     │ -1..+1 │
 *  │ PF_total                       │ 0x32 │ —     │ -1..+1 │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Frequency --                │      │       │        │
 *  │ Frequency                      │ 0x34 │ Hz    │ 45–65  │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- Energy --                   │      │       │        │
 *  │ Import active   (kWh)          │ 0x36 │ kWh   │ 0–1e9  │
 *  │ Export active   (kWh)          │ 0x38 │ kWh   │ 0–1e9  │
 *  │ Import reactive (kVarh)        │ 0x3A │ kVarh │ 0–1e9  │
 *  │ Export reactive (kVarh)        │ 0x3C │ kVarh │ 0–1e9  │
 *  ├────────────────────────────────┼──────┼───────┼────────┤
 *  │ -- THD (Total Harmonic Dist.) -│      │       │        │
 *  │ THD_Va                         │ 0x3E │ %     │ 0–100  │
 *  │ THD_Vb                         │ 0x40 │ %     │ 0–100  │
 *  │ THD_Vc                         │ 0x42 │ %     │ 0–100  │
 *  │ THD_Ia                         │ 0x44 │ %     │ 0–100  │
 *  │ THD_Ib                         │ 0x46 │ %     │ 0–100  │
 *  │ THD_Ic                         │ 0x48 │ %     │ 0–100  │
 *  └────────────────────────────────┴──────┴───────┴────────┘
 */

/* Voltage */
#define REG_VA          0x0000
#define REG_VB          0x0002
#define REG_VC          0x0004
#define REG_VAB         0x0006
#define REG_VBC         0x0008
#define REG_VCA         0x000A

/* Current */
#define REG_IA          0x000C
#define REG_IB          0x000E
#define REG_IC          0x0010
#define REG_IN          0x0012

/* Active power */
#define REG_PA          0x0014
#define REG_PB          0x0016
#define REG_PC          0x0018
#define REG_P_TOTAL     0x001A

/* Reactive power */
#define REG_QA          0x001C
#define REG_QB          0x001E
#define REG_QC          0x0020
#define REG_Q_TOTAL     0x0022

/* Apparent power */
#define REG_SA          0x0024
#define REG_SB          0x0026
#define REG_SC          0x0028
#define REG_S_TOTAL     0x002A

/* Power factor */
#define REG_PFA         0x002C
#define REG_PFB         0x002E
#define REG_PFC         0x0030
#define REG_PF_TOTAL    0x0032

/* Frequency */
#define REG_FREQ        0x0034

/* Energy */
#define REG_KWH_IMP     0x0036
#define REG_KWH_EXP     0x0038
#define REG_KVARH_IMP   0x003A
#define REG_KVARH_EXP   0x003C

/* THD */
#define REG_THD_VA      0x003E
#define REG_THD_VB      0x0040
#define REG_THD_VC      0x0042
#define REG_THD_IA      0x0044
#define REG_THD_IB      0x0046
#define REG_THD_IC      0x0048

/* Total register count (last addr + 2) */
#define METER_REG_COUNT  0x004A   /* = 74 registers */

/* ============================================================
 *  Public API
 * ============================================================ */

/**
 * meter_update_registers - push meter_data values into Modbus
 *                          holding registers (input registers).
 * @m: pointer to freshly calculated meter_data
 *
 * Call this after every ADC measurement cycle, before mb_poll().
 * Thread-safe: writes are 16-bit aligned on Cortex-M, no lock needed
 * for individual register reads from the Modbus side.
 */
void meter_update_registers(const struct meter_data_s *m);

/**
 * meter_get_data - return pointer to the last written meter_data
 *                 (read-only snapshot, updated by meter_update_registers)
 */
const struct meter_data_s *meter_get_data(void);

#endif /* METER_REGISTERS_H */