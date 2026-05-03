// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/lib/inc/meter_register.h"

typedef void* TaskHandle_t;
typedef unsigned int UBaseType_t;

static uint16_t _stub_regs[0x0060];

void mb_set_float(uint16_t addr, float32_t val)
{
    uint32_t bits;
    memcpy(&bits, &val, 4);
    _stub_regs[addr] = (uint16_t)(bits >> 16);
    _stub_regs[addr + 1] = (uint16_t)(bits & 0xFFFF);
}

float32_t mb_get_float(uint16_t addr)
{
    uint32_t bits = ((uint32_t)_stub_regs[addr] << 16) |
                     (uint32_t)_stub_regs[addr + 1];
    float32_t val;
    memcpy(&val, &bits, 4);
    return val;
}

struct mb_data_store *mb_get_data_store(void)
{ return
                                                      ((void *)0)
 }
void mb_set_coil(uint16_t a,
                            _Bool
                                 v)
{ (void)a; (void)v; }

_Bool
    mb_get_coil(uint16_t a)
{ (void)a; return 0; }
void mb_set_discrete_input(uint16_t a,
                                      _Bool
                                           v){ (void)a; (void)v; }

_Bool
    mb_get_discrete_input(uint16_t a)
{ (void)a; return 0; }
void mb_set_input_reg(uint16_t a, uint16_t v)
{ (void)a; (void)v; }
uint16_t mb_get_input_reg(uint16_t a)
{ (void)a; return 0; }
void mb_set_holding_reg(uint16_t a, uint16_t v){ (void)a; (void)v; }
uint16_t mb_get_holding_reg(uint16_t a)
{ (void)a; return 0; }

static struct meter_data_s make_data(void)
{
    struct meter_data_s m;
    memset(&m, 0, sizeof(m));
    m.frequency = 50.0f;
    m.energy_hWh = 1000;
    m.energy_Ws = 360000.0;

    for (int i = 0; i < 3U; i++)
{
        m.phase_data[i].rms_voltage = 230.0f + i * 1.0f;
        m.phase_data[i].rms_current = 10.0f + i * 0.5f;
        m.phase_data[i].act_pwr = 2000.0f + i * 100.0f;
        m.phase_data[i].react_pwr = 500.0f + i * 50.0f;
        m.phase_data[i].app_pwr = 2100.0f + i * 100.0f;
        m.phase_data[i].pf = 0.95f - i * 0.01f;
        m.phase_data[i].thd.voltage = 3.0f + i * 0.5f;
        m.phase_data[i].thd.current = 5.0f + i * 1.0f;
    }
    m.vol_line.ab = 400.0f;
    m.vol_line.bc = 401.0f;
    m.vol_line.ca = 402.0f;
    return m;
}

void setUp(void)
{
    memset(_stub_regs, 0, sizeof(_stub_regs));
}

void tearDown(void)
{}

void test_mreg_get_data_returns_non_null(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    do { if ((((meter_get_data())) !=
   ((void *)0)
   ))
{ } else { UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)(((140)))); } } while (0);
}

void test_mreg_get_data_matches_last_written(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    const struct meter_data_s *out = meter_get_data();
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.frequency)), (UNITY_FLOAT)((out->frequency)), (
   ((void *)0)
   ), (UNITY_UINT)(148));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].rms_voltage)), (UNITY_FLOAT)((out->phase_data[0].rms_voltage)), (
   ((void *)0)
   ), (UNITY_UINT)(149))
}

void test_mreg_voltage_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].rms_voltage)), (UNITY_FLOAT)((mb_get_float(0x0000))), (
   ((void *)0)
   ), (UNITY_UINT)(161));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].rms_voltage)), (UNITY_FLOAT)((mb_get_float(0x0002))), (
   ((void *)0)
   ), (UNITY_UINT)(162));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].rms_voltage)), (UNITY_FLOAT)((mb_get_float(0x0004))), (
   ((void *)0)
   ), (UNITY_UINT)(163));
}

void test_mreg_voltage_line_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ab)), (UNITY_FLOAT)((mb_get_float(0x0006))), (
   ((void *)0)
   ), (UNITY_UINT)(170));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.bc)), (UNITY_FLOAT)((mb_get_float(0x0008))), (
   ((void *)0)
   ), (UNITY_UINT)(171));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ca)), (UNITY_FLOAT)((mb_get_float(0x000A))), (
   ((void *)0)
   ), (UNITY_UINT)(172));
}

void test_mreg_current_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].rms_current)), (UNITY_FLOAT)((mb_get_float(0x000C))), (
   ((void *)0)
   ), (UNITY_UINT)(183));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].rms_current)), (UNITY_FLOAT)((mb_get_float(0x000E))), (
   ((void *)0)
   ), (UNITY_UINT)(184));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].rms_current)), (UNITY_FLOAT)((mb_get_float(0x0010))), (
   ((void *)0)
   ), (UNITY_UINT)(185));
}

void test_mreg_neutral_current_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected_in = m.phase_data[0].rms_current
                          + m.phase_data[1].rms_current
                          + m.phase_data[2].rms_current;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected_in)), (UNITY_FLOAT)((mb_get_float(0x0012))), (
   ((void *)0)
   ), (UNITY_UINT)(195));
}

void test_mreg_active_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].act_pwr)), (UNITY_FLOAT)((mb_get_float(0x0014))), (
   ((void *)0)
   ), (UNITY_UINT)(206));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].act_pwr)), (UNITY_FLOAT)((mb_get_float(0x0016))), (
   ((void *)0)
   ), (UNITY_UINT)(207));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].act_pwr)), (UNITY_FLOAT)((mb_get_float(0x0018))), (
   ((void *)0)
   ), (UNITY_UINT)(208));
}

void test_mreg_active_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].act_pwr
                       + m.phase_data[1].act_pwr
                       + m.phase_data[2].act_pwr;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x001A))), (
   ((void *)0)
   ), (UNITY_UINT)(218));
}

void test_mreg_reactive_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].react_pwr)), (UNITY_FLOAT)((mb_get_float(0x001C))), (
   ((void *)0)
   ), (UNITY_UINT)(229));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].react_pwr)), (UNITY_FLOAT)((mb_get_float(0x001E))), (
   ((void *)0)
   ), (UNITY_UINT)(230));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].react_pwr)), (UNITY_FLOAT)((mb_get_float(0x0020))), (
   ((void *)0)
   ), (UNITY_UINT)(231));
}

void test_mreg_reactive_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].react_pwr
                       + m.phase_data[1].react_pwr
                       + m.phase_data[2].react_pwr;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x0022))), (
   ((void *)0)
   ), (UNITY_UINT)(241));
}

void test_mreg_apparent_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].app_pwr)), (UNITY_FLOAT)((mb_get_float(0x0024))), (
   ((void *)0)
   ), (UNITY_UINT)(252));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].app_pwr)), (UNITY_FLOAT)((mb_get_float(0x0026))), (
   ((void *)0)
   ), (UNITY_UINT)(253));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].app_pwr)), (UNITY_FLOAT)((mb_get_float(0x0028))), (
   ((void *)0)
   ), (UNITY_UINT)(254));
}

void test_mreg_apparent_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].app_pwr
                       + m.phase_data[1].app_pwr
                       + m.phase_data[2].app_pwr;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x002A))), (
   ((void *)0)
   ), (UNITY_UINT)(264));
}

void test_mreg_power_factor_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].pf)), (UNITY_FLOAT)((mb_get_float(0x002C))), (
   ((void *)0)
   ), (UNITY_UINT)(275));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].pf)), (UNITY_FLOAT)((mb_get_float(0x002E))), (
   ((void *)0)
   ), (UNITY_UINT)(276));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].pf)), (UNITY_FLOAT)((mb_get_float(0x0030))), (
   ((void *)0)
   ), (UNITY_UINT)(277));
}

void test_mreg_power_factor_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].pf
                       + m.phase_data[1].pf
                       + m.phase_data[2].pf;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x0032))), (
   ((void *)0)
   ), (UNITY_UINT)(287));
}

void test_mreg_frequency_register(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
   ((void *)0)
   ), (UNITY_UINT)(298));
}

void test_mreg_frequency_boundary_45Hz(void)
{
    struct meter_data_s m = make_data();
    m.frequency = 45.0f;
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((45.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
   ((void *)0)
   ), (UNITY_UINT)(306));
}

void test_mreg_frequency_boundary_65Hz(void)
{
    struct meter_data_s m = make_data();
    m.frequency = 65.0f;
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((65.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
   ((void *)0)
   ), (UNITY_UINT)(314));
}

void test_mreg_energy_export_kwh_conversion(void)
{
    struct meter_data_s m = make_data();
    m.energy_hWh = 1000;
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((100.0f)), (UNITY_FLOAT)((mb_get_float(0x0038))), (
   ((void *)0)
   ), (UNITY_UINT)(326));
}

void test_mreg_energy_import_is_zero(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mb_get_float(0x0036))), (
   ((void *)0)
   ), (UNITY_UINT)(333));
}

void test_mreg_energy_reactive_not_implemented(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mb_get_float(0x003C))), (
   ((void *)0)
   ), (UNITY_UINT)(340));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mb_get_float(0x003A))), (
   ((void *)0)
   ), (UNITY_UINT)(341));
}

void test_mreg_thd_voltage_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].thd.voltage)), (UNITY_FLOAT)((mb_get_float(0x003E))), (
   ((void *)0)
   ), (UNITY_UINT)(352));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].thd.voltage)), (UNITY_FLOAT)((mb_get_float(0x0040))), (
   ((void *)0)
   ), (UNITY_UINT)(353));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].thd.voltage)), (UNITY_FLOAT)((mb_get_float(0x0042))), (
   ((void *)0)
   ), (UNITY_UINT)(354));
}

void test_mreg_thd_current_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].thd.current)), (UNITY_FLOAT)((mb_get_float(0x0044))), (
   ((void *)0)
   ), (UNITY_UINT)(361));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].thd.current)), (UNITY_FLOAT)((mb_get_float(0x0046))), (
   ((void *)0)
   ), (UNITY_UINT)(362));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].thd.current)), (UNITY_FLOAT)((mb_get_float(0x0048))), (
   ((void *)0)
   ), (UNITY_UINT)(363));
}

void test_mreg_snapshot_all_fields_preserved(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    const struct meter_data_s *snap = meter_get_data();

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.frequency)), (UNITY_FLOAT)((snap->frequency)), (
   ((void *)0)
   ), (UNITY_UINT)(376));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ab)), (UNITY_FLOAT)((snap->vol_line.ab)), (
   ((void *)0)
   ), (UNITY_UINT)(377));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.bc)), (UNITY_FLOAT)((snap->vol_line.bc)), (
   ((void *)0)
   ), (UNITY_UINT)(378));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ca)), (UNITY_FLOAT)((snap->vol_line.ca)), (
   ((void *)0)
   ), (UNITY_UINT)(379));
    UnityAssertEqualNumber((UNITY_INT)((m.energy_hWh)), (UNITY_INT)((snap->energy_hWh)), (
   ((void *)0)
   ), (UNITY_UINT)(380), UNITY_DISPLAY_STYLE_INT64);

    for (int i = 0; i < 3U; i++)
{
        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].rms_voltage)), (UNITY_FLOAT)((snap->phase_data[i].rms_voltage)), (
       ((void *)0)
       ), (UNITY_UINT)(383))

        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].rms_current)), (UNITY_FLOAT)((snap->phase_data[i].rms_current)), (
       ((void *)0)
       ), (UNITY_UINT)(385))

        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].act_pwr)), (UNITY_FLOAT)((snap->phase_data[i].act_pwr)), (
       ((void *)0)
       ), (UNITY_UINT)(387))

        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].pf)), (UNITY_FLOAT)((snap->phase_data[i].pf)), (
       ((void *)0)
       ), (UNITY_UINT)(389))

        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].thd.voltage)), (UNITY_FLOAT)((snap->phase_data[i].thd.voltage)), (
       ((void *)0)
       ), (UNITY_UINT)(391))

    }
}

void test_mreg_overwrite_updates_registers(void)
{
    struct meter_data_s m1 = make_data();
    struct meter_data_s m2 = make_data();
    m2.frequency = 60.0f;
    m2.phase_data[0].rms_voltage = 240.0f;

    meter_update_registers(&m1);
    meter_update_registers(&m2);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((60.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
   ((void *)0)
   ), (UNITY_UINT)(410));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((240.0f)), (UNITY_FLOAT)((mb_get_float(0x0000))), (
   ((void *)0)
   ), (UNITY_UINT)(411));
}

void test_mreg_overwrite_updates_snapshot(void)
{
    struct meter_data_s m1 = make_data();
    struct meter_data_s m2 = make_data();
    m2.frequency = 60.0f;

    meter_update_registers(&m1);
    meter_update_registers(&m2);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((60.0f)), (UNITY_FLOAT)((meter_get_data()->frequency)), (
   ((void *)0)
   ), (UNITY_UINT)(423));
}