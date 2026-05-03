// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/common/inc/ema.h"
#include "User/common/inc/maf.h"
#include "User/common/inc/share_data.h"
#include "User/common/inc/share_types.h"

static struct meter_data_s make_meter_data(float32_t freq, float32_t rmsV,
                                            float32_t rmsI, float32_t actP)
{
    struct meter_data_s d;
    memset(&d, 0, sizeof(d));
    d.frequency = freq;
    for (int i = 0; i < 3U; i++)
{
        d.phase_data[i].rms_voltage = rmsV;
        d.phase_data[i].rms_current = rmsI;
        d.phase_data[i].act_pwr = actP;
        d.phase_data[i].app_pwr = rmsV * rmsI;
        d.phase_data[i].pf = (rmsV * rmsI > 0.0f) ?
                                       actP / (rmsV * rmsI) : 0.0f;
    }
    d.vol_line.ab = rmsV * 1.732f;
    d.vol_line.bc = rmsV * 1.732f;
    d.vol_line.ca = rmsV * 1.732f;
    return d;
}

void setUp(void)
{}
void tearDown(void)
{}
void test_ema_basic_formula(void)
{
    float32_t result = ema_get(10.0f, 0.0f, 0.5f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((5.0f)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(61));
}

void test_ema_alpha_1_returns_input(void)
{
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((42.0f)), (UNITY_FLOAT)((ema_get(42.0f, 999.0f, 1.0f))), (
   ((void *)0)
   ), (UNITY_UINT)(67));
}

void test_ema_alpha_0_returns_last(void)
{
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((999.0f)), (UNITY_FLOAT)((ema_get(42.0f, 999.0f, 0.0f))), (
   ((void *)0)
   ), (UNITY_UINT)(73));
}

void test_ema_converges_to_constant_input(void)
{
    float32_t val = 0.0f;
    for (int i = 0; i < 200; i++)
        val = ema_get(100.0f, val, 0.2f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((100.0f)), (UNITY_FLOAT)((val)), (
   ((void *)0)
   ), (UNITY_UINT)(82));
}

void test_ema_step_response_monotonic(void)
{
    float32_t val = 0.0f, prev = 0.0f;
    for (int i = 0; i < 50; i++)
{
        val = ema_get(1.0f, val, 0.2f);
        do { if ((val >= prev))
{ } else { UnityFail( ((("EMA not monotonically increasing"))), (UNITY_UINT)((91))); } } while (0);
        prev = val;
    }
}

void test_ema_negative_input(void)
{
    float32_t result = ema_get(-10.0f, 0.0f, 0.5f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((-5.0f)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(99));
}

void test_ema_zero_input_zero_last(void)
{
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((ema_get(0.0f, 0.0f, 0.2f))), (
   ((void *)0)
   ), (UNITY_UINT)(104));
}

void test_maf_init_clears_state(void)
{
    struct maf_s maf;

    memset(&maf, 0xFF, sizeof(maf));
    maf_init(&maf);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((maf.sample_count)), (
   ((void *)0)
   ), (UNITY_UINT)(117), UNITY_DISPLAY_STYLE_UINT32);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((maf.sum)), (
   ((void *)0)
   ), (UNITY_UINT)(118));
}

void test_maf_single_sample_returns_itself_divided_by_size(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = maf_update(&maf, (float32_t)128);

    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(127));
}

void test_maf_converges_to_constant(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = 0.0f;

    for (int i = 0; i < 128; i++)
        result = maf_update(&maf, 10.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((10.0f)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(138));
}

void test_maf_output_is_running_average(void)
{
    struct maf_s maf;
    maf_init(&maf);

    for (int i = 0; i < 128; i++)
        maf_update(&maf, 1.0f);
    float32_t result = maf_update(&maf, 0.0f);
    float32_t expected = (float32_t)(128 - 1) / (float32_t)128;
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(150));
}

void test_maf_circular_buffer_wraps(void)
{
    struct maf_s maf;
    maf_init(&maf);

    for (int i = 0; i < 128; i++)
        maf_update(&maf, 1.0f);

    float32_t result = 0.0f;
    for (int i = 0; i < 128; i++)
        result = maf_update(&maf, 2.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(164));
}

void test_maf_sample_count_wraps_at_max(void)
{
    struct maf_s maf;
    maf_init(&maf);
    for (int i = 0; i < 128; i++)
        maf_update(&maf, 1.0f);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((maf.sample_count)), (
   ((void *)0)
   ), (UNITY_UINT)(174), UNITY_DISPLAY_STYLE_UINT32);
}

void test_maf_zero_input_returns_zero(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = 0.0f;
    for (int i = 0; i < 128; i++)
        result = maf_update(&maf, 0.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(184));
}

void test_maf_negative_samples(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = 0.0f;
    for (int i = 0; i < 128; i++)
        result = maf_update(&maf, -5.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((-5.0f)), (UNITY_FLOAT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(194));
}

static void shdat_reset(void)
{
    struct meter_data_s zero;
    memset(&zero, 0, sizeof(zero));
    shdat_wrt_meter_data(&zero);
    shdat_wrt_meter_data(&zero);
    shdat_set_meter_state(METER_STATE_START);
}

void test_shdat_initial_state_is_start(void)
{
    shdat_reset();
    UnityAssertEqualNumber((UNITY_INT)((METER_STATE_START)), (UNITY_INT)((shdat_get_meter_current_state())), (
   ((void *)0)
   ), (UNITY_UINT)(215), UNITY_DISPLAY_STYLE_INT);
}

void test_shdat_set_and_get_state(void)
{
    shdat_set_meter_state(METER_STATE_RUNNING_3PHASE);
    UnityAssertEqualNumber((UNITY_INT)((METER_STATE_RUNNING_3PHASE)), (UNITY_INT)((shdat_get_meter_current_state())), (
   ((void *)0)
   ), (UNITY_UINT)(221), UNITY_DISPLAY_STYLE_INT)

    shdat_set_meter_state(METER_STATE_START);
}

void test_shdat_all_states_settable(void)
{
    enum meter_state_e states[] = {
        METER_STATE_ERROR,
        METER_STATE_WARNING,
        METER_STATE_START,
        METER_STATE_WAIT_FOR_STARTING_CURRENT,
        METER_STATE_WAIT_FOR_PLL_LOCK,
        METER_STATE_RUNNING_3PHASE,
        METER_STATE_RUNNING_PHASE_A,
        METER_STATE_RUNNING_PHASE_B,
        METER_STATE_RUNNING_PHASE_C,
    };
    for (int i = 0; i < 9; i++)
{
        shdat_set_meter_state(states[i]);
        UnityAssertEqualNumber((UNITY_INT)((states[i])), (UNITY_INT)((shdat_get_meter_current_state())), (
       ((void *)0)
       ), (UNITY_UINT)(241), UNITY_DISPLAY_STYLE_INT);
    }
}

void test_shdat_wrt_and_get_frequency(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);

    for (int i = 0; i < 50; i++)
        shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.1f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((out.frequency)), (
   ((void *)0)
   ), (UNITY_UINT)(253));
}

void test_shdat_wrt_and_get_rms_voltage(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);
    for (int i = 0; i < 50; i++)
        shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    for (int ph = 0; ph < 3U; ph++)
        UnityAssertFloatsWithin((UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((230.0f)), (UNITY_FLOAT)((out.phase_data[ph].rms_voltage)), (
       ((void *)0)
       ), (UNITY_UINT)(264));
}

void test_shdat_wrt_and_get_active_power(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);
    for (int i = 0; i < 50; i++)
        shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    for (int ph = 0; ph < 3U; ph++)
        UnityAssertFloatsWithin((UNITY_FLOAT)((10.0f)), (UNITY_FLOAT)((2000.0f)), (UNITY_FLOAT)((out.phase_data[ph].act_pwr)), (
       ((void *)0)
       ), (UNITY_UINT)(275));
}

void test_shdat_double_buffer_swap(void)
{
    shdat_reset();
    struct meter_data_s d1 = make_meter_data(50.0f, 100.0f, 1.0f, 80.0f);
    struct meter_data_s d2 = make_meter_data(60.0f, 200.0f, 2.0f, 160.0f);

    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d1);
    struct meter_data_s out1 = shdat_get_meter_data();

    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d2);
    struct meter_data_s out2 = shdat_get_meter_data();

    do { if ((fabsf(out2.frequency - 60.0f) < fabsf(out1.frequency - 60.0f)))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((296))); } } while (0)
}

void test_shdat_ema_smoothing_single_step(void)
{
    shdat_reset();

    struct meter_data_s d50 = make_meter_data(50.0f, 100.0f, 1.0f, 80.0f);
    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d50);

    struct meter_data_s d100 = make_meter_data(100.0f, 100.0f, 1.0f, 80.0f);
    shdat_wrt_meter_data(&d100);

    struct meter_data_s out = shdat_get_meter_data();

    do { if ((out.frequency < 100.0f))
{ } else { UnityFail( ((("EMA should dampen step change"))), (UNITY_UINT)((317))); } } while (0)

    do { if ((out.frequency > 50.0f))
{ } else { UnityFail( ((("EMA output should be above previous value"))), (UNITY_UINT)((319))); } } while (0)
}

void test_shdat_energy_passthrough(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 100.0f, 1.0f, 80.0f);
    d.energy_hWh = 12345;
    d.energy_Ws = 9999.0;
    shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    UnityAssertEqualNumber((UNITY_INT)((12345)), (UNITY_INT)((out.energy_hWh)), (
   ((void *)0)
   ), (UNITY_UINT)(334), UNITY_DISPLAY_STYLE_INT64);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-4f)), (UNITY_FLOAT)((9999.0f)), (UNITY_FLOAT)(((float32_t)out.energy_Ws)), (
   ((void *)0)
   ), (UNITY_UINT)(335));
}

void test_shdat_vol_line_ema_smoothed(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);
    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    float32_t expected = 230.0f * 1.732f;
    UnityAssertFloatsWithin((UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((out.vol_line.ab)), (
   ((void *)0)
   ), (UNITY_UINT)(348));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((out.vol_line.bc)), (
   ((void *)0)
   ), (UNITY_UINT)(349));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((out.vol_line.ca)), (
   ((void *)0)
   ), (UNITY_UINT)(350));
}