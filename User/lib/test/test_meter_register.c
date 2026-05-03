/**
 * @file test_meter_register.c
 * @brief Unit tests for meter_register.c
 *
 * Strategy:
 *   - Stub mb_set_float / mb_get_float with a local uint16_t array
 *   - Stub all hardware/FreeRTOS headers via defines before any include
 *   - Test meter_update_registers() mapping and meter_get_data() snapshot
 *
 * Coverage:
 *  A. meter_get_data        — returns pointer to last snapshot
 *  B. Voltage registers     — VA/VB/VC/VAB/VBC/VCA
 *  C. Current registers     — IA/IB/IC/IN (neutral = sum)
 *  D. Active power          — PA/PB/PC/P_TOTAL
 *  E. Reactive power        — QA/QB/QC/Q_TOTAL
 *  F. Apparent power        — SA/SB/SC/S_TOTAL
 *  G. Power factor          — PFA/PFB/PFC/PF_TOTAL
 *  H. Frequency
 *  I. Energy                — kWh export (hWh/10), import=0
 *  J. THD                   — voltage and current per phase
 *  K. Snapshot integrity    — meter_get_data matches written data
 *  L. Overwrite             — second call overwrites first
 */

/* ------------------------------------------------------------------ */
/*  Stub out hardware dependencies BEFORE any project header           */
/* ------------------------------------------------------------------ */

/* Prevent modbus_rtu.h hardware includes from being processed */
#define STM32F4XX_LL_USART_H
#define STM32F4XX_LL_DMA_H
#define STM32F4XX_LL_BUS_H
#define STM32F4XX_LL_GPIO_H
#define FREERTOS_H
#define TASK_H

/* FreeRTOS types needed by modbus_rtu.h */
typedef void* TaskHandle_t;
typedef unsigned int UBaseType_t;

/* stm32 LL peripheral stubs */
#define USART2          ((void*)0)
#define LL_DMA_STREAM_5 5
#define LL_DMA_STREAM_6 6
#define LL_DMA_CHANNEL_4 4
#define DMA1            ((void*)0)
#define USART2_IRQn     0
#define DMA1_Stream5_IRQn 0
#define DMA1_Stream6_IRQn 0

#include "unity.h"
#include "meter_register.h"   /* pulls in share_types.h */
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ */
/*  Stub register store                                                 */
/* ------------------------------------------------------------------ */
#define STUB_REG_COUNT  0x0060   /* larger than METER_REG_COUNT=0x4A  */
static uint16_t _stub_regs[STUB_REG_COUNT];

/* Implement mb_set_float / mb_get_float as big-endian word encoding */
void mb_set_float(uint16_t addr, float32_t val)
{
    uint32_t bits;
    memcpy(&bits, &val, 4);
    _stub_regs[addr]     = (uint16_t)(bits >> 16);   /* high word */
    _stub_regs[addr + 1] = (uint16_t)(bits & 0xFFFF);/* low  word */
}

float32_t mb_get_float(uint16_t addr)
{
    uint32_t bits = ((uint32_t)_stub_regs[addr] << 16) |
                     (uint32_t)_stub_regs[addr + 1];
    float32_t val;
    memcpy(&val, &bits, 4);
    return val;
}

/* Stub remaining mb_* functions (not called by meter_register.c) */
struct mb_data_store *mb_get_data_store(void) { return NULL; }
void mb_set_coil(uint16_t a, bool v)          { (void)a; (void)v; }
bool mb_get_coil(uint16_t a)                  { (void)a; return 0; }
void mb_set_discrete_input(uint16_t a, bool v){ (void)a; (void)v; }
bool mb_get_discrete_input(uint16_t a)        { (void)a; return 0; }
void mb_set_input_reg(uint16_t a, uint16_t v) { (void)a; (void)v; }
uint16_t mb_get_input_reg(uint16_t a)         { (void)a; return 0; }
void mb_set_holding_reg(uint16_t a, uint16_t v){ (void)a; (void)v; }
uint16_t mb_get_holding_reg(uint16_t a)        { (void)a; return 0; }

/* ------------------------------------------------------------------ */
/*  Test data helpers                                                   */
/* ------------------------------------------------------------------ */
#define TOL 0.001f

static struct meter_data_s make_data(void)
{
    struct meter_data_s m;
    memset(&m, 0, sizeof(m));
    m.frequency   = 50.0f;
    m.energy_hWh  = 1000;      /* 1000 hWh = 100 kWh */
    m.energy_Ws   = 360000.0;

    for (int i = 0; i < METER_PHASE_COUNT; i++) {
        m.phase_data[i].rms_voltage = 230.0f + i * 1.0f;
        m.phase_data[i].rms_current = 10.0f  + i * 0.5f;
        m.phase_data[i].act_pwr     = 2000.0f + i * 100.0f;
        m.phase_data[i].react_pwr   = 500.0f  + i * 50.0f;
        m.phase_data[i].app_pwr     = 2100.0f + i * 100.0f;
        m.phase_data[i].pf          = 0.95f   - i * 0.01f;
        m.phase_data[i].thd.voltage = 3.0f    + i * 0.5f;
        m.phase_data[i].thd.current = 5.0f    + i * 1.0f;
    }
    m.vol_line.ab = 400.0f;
    m.vol_line.bc = 401.0f;
    m.vol_line.ca = 402.0f;
    return m;
}

/* ------------------------------------------------------------------ */
/*  setUp / tearDown                                                    */
/* ------------------------------------------------------------------ */
void setUp(void)
{
    memset(_stub_regs, 0, sizeof(_stub_regs));
}

void tearDown(void) {}

/* ================================================================== */
/*  A. meter_get_data                                                  */
/* ================================================================== */

void test_mreg_get_data_returns_non_null(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_NOT_NULL(meter_get_data());
}

void test_mreg_get_data_matches_last_written(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    const struct meter_data_s *out = meter_get_data();
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.frequency, out->frequency);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].rms_voltage,
                             out->phase_data[0].rms_voltage);
}

/* ================================================================== */
/*  B. Voltage registers                                               */
/* ================================================================== */

void test_mreg_voltage_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].rms_voltage, mb_get_float(REG_VA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].rms_voltage, mb_get_float(REG_VB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].rms_voltage, mb_get_float(REG_VC));
}

void test_mreg_voltage_line_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.vol_line.ab, mb_get_float(REG_VAB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.vol_line.bc, mb_get_float(REG_VBC));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.vol_line.ca, mb_get_float(REG_VCA));
}

/* ================================================================== */
/*  C. Current registers                                               */
/* ================================================================== */

void test_mreg_current_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].rms_current, mb_get_float(REG_IA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].rms_current, mb_get_float(REG_IB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].rms_current, mb_get_float(REG_IC));
}

void test_mreg_neutral_current_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected_in = m.phase_data[0].rms_current
                          + m.phase_data[1].rms_current
                          + m.phase_data[2].rms_current;
    TEST_ASSERT_FLOAT_WITHIN(TOL, expected_in, mb_get_float(REG_IN));
}

/* ================================================================== */
/*  D. Active power                                                    */
/* ================================================================== */

void test_mreg_active_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].act_pwr, mb_get_float(REG_PA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].act_pwr, mb_get_float(REG_PB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].act_pwr, mb_get_float(REG_PC));
}

void test_mreg_active_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].act_pwr
                       + m.phase_data[1].act_pwr
                       + m.phase_data[2].act_pwr;
    TEST_ASSERT_FLOAT_WITHIN(TOL, expected, mb_get_float(REG_P_TOTAL));
}

/* ================================================================== */
/*  E. Reactive power                                                  */
/* ================================================================== */

void test_mreg_reactive_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].react_pwr, mb_get_float(REG_QA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].react_pwr, mb_get_float(REG_QB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].react_pwr, mb_get_float(REG_QC));
}

void test_mreg_reactive_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].react_pwr
                       + m.phase_data[1].react_pwr
                       + m.phase_data[2].react_pwr;
    TEST_ASSERT_FLOAT_WITHIN(TOL, expected, mb_get_float(REG_Q_TOTAL));
}

/* ================================================================== */
/*  F. Apparent power                                                  */
/* ================================================================== */

void test_mreg_apparent_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].app_pwr, mb_get_float(REG_SA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].app_pwr, mb_get_float(REG_SB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].app_pwr, mb_get_float(REG_SC));
}

void test_mreg_apparent_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].app_pwr
                       + m.phase_data[1].app_pwr
                       + m.phase_data[2].app_pwr;
    TEST_ASSERT_FLOAT_WITHIN(TOL, expected, mb_get_float(REG_S_TOTAL));
}

/* ================================================================== */
/*  G. Power factor                                                    */
/* ================================================================== */

void test_mreg_power_factor_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].pf, mb_get_float(REG_PFA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].pf, mb_get_float(REG_PFB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].pf, mb_get_float(REG_PFC));
}

void test_mreg_power_factor_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].pf
                       + m.phase_data[1].pf
                       + m.phase_data[2].pf;
    TEST_ASSERT_FLOAT_WITHIN(TOL, expected, mb_get_float(REG_PF_TOTAL));
}

/* ================================================================== */
/*  H. Frequency                                                       */
/* ================================================================== */

void test_mreg_frequency_register(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 50.0f, mb_get_float(REG_FREQ));
}

void test_mreg_frequency_boundary_45Hz(void)
{
    struct meter_data_s m = make_data();
    m.frequency = 45.0f;
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 45.0f, mb_get_float(REG_FREQ));
}

void test_mreg_frequency_boundary_65Hz(void)
{
    struct meter_data_s m = make_data();
    m.frequency = 65.0f;
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 65.0f, mb_get_float(REG_FREQ));
}

/* ================================================================== */
/*  I. Energy                                                          */
/* ================================================================== */

void test_mreg_energy_export_kwh_conversion(void)
{
    struct meter_data_s m = make_data();
    m.energy_hWh = 1000;   /* 1000 hWh = 100.0 kWh */
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 100.0f, mb_get_float(REG_KWH_EXP));
}

void test_mreg_energy_import_is_zero(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 0.0f, mb_get_float(REG_KWH_IMP));
}

void test_mreg_energy_reactive_not_implemented(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 0.0f, mb_get_float(REG_KVARH_EXP));
    TEST_ASSERT_FLOAT_WITHIN(TOL, 0.0f, mb_get_float(REG_KVARH_IMP));
}

/* ================================================================== */
/*  J. THD                                                             */
/* ================================================================== */

void test_mreg_thd_voltage_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].thd.voltage, mb_get_float(REG_THD_VA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].thd.voltage, mb_get_float(REG_THD_VB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].thd.voltage, mb_get_float(REG_THD_VC));
}

void test_mreg_thd_current_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[0].thd.current, mb_get_float(REG_THD_IA));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[1].thd.current, mb_get_float(REG_THD_IB));
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[2].thd.current, mb_get_float(REG_THD_IC));
}

/* ================================================================== */
/*  K. Snapshot integrity                                              */
/* ================================================================== */

void test_mreg_snapshot_all_fields_preserved(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    const struct meter_data_s *snap = meter_get_data();

    TEST_ASSERT_FLOAT_WITHIN(TOL, m.frequency,       snap->frequency);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.vol_line.ab,     snap->vol_line.ab);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.vol_line.bc,     snap->vol_line.bc);
    TEST_ASSERT_FLOAT_WITHIN(TOL, m.vol_line.ca,     snap->vol_line.ca);
    TEST_ASSERT_EQUAL_INT64(m.energy_hWh,            snap->energy_hWh);

    for (int i = 0; i < METER_PHASE_COUNT; i++) {
        TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[i].rms_voltage,
                                 snap->phase_data[i].rms_voltage);
        TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[i].rms_current,
                                 snap->phase_data[i].rms_current);
        TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[i].act_pwr,
                                 snap->phase_data[i].act_pwr);
        TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[i].pf,
                                 snap->phase_data[i].pf);
        TEST_ASSERT_FLOAT_WITHIN(TOL, m.phase_data[i].thd.voltage,
                                 snap->phase_data[i].thd.voltage);
    }
}

/* ================================================================== */
/*  L. Overwrite                                                       */
/* ================================================================== */

void test_mreg_overwrite_updates_registers(void)
{
    struct meter_data_s m1 = make_data();
    struct meter_data_s m2 = make_data();
    m2.frequency = 60.0f;
    m2.phase_data[0].rms_voltage = 240.0f;

    meter_update_registers(&m1);
    meter_update_registers(&m2);

    TEST_ASSERT_FLOAT_WITHIN(TOL, 60.0f,  mb_get_float(REG_FREQ));
    TEST_ASSERT_FLOAT_WITHIN(TOL, 240.0f, mb_get_float(REG_VA));
}

void test_mreg_overwrite_updates_snapshot(void)
{
    struct meter_data_s m1 = make_data();
    struct meter_data_s m2 = make_data();
    m2.frequency = 60.0f;

    meter_update_registers(&m1);
    meter_update_registers(&m2);

    TEST_ASSERT_FLOAT_WITHIN(TOL, 60.0f, meter_get_data()->frequency);
}