/**
 * @file test_ema_maf_shdat.c
 * @brief Unit tests for ema.c, maf.c, share_data.c
 *
 * A. ema_get        — exponential moving average
 * B. maf_init/update — moving average filter
 * C. shdat_*        — shared data double-buffer + EMA smoothing
 */

#include "unity.h"
#include "ema.h"
#include "maf.h"
#include "share_data.h"
#include "share_types.h"
#include <string.h>
#include <math.h>

/* ------------------------------------------------------------------ */
/*  Helpers                                                             */
/* ------------------------------------------------------------------ */
#define EMA_ALPHA       0.2f
#define MAF_SIZE        MAF_MAX_SAMPLES   /* 128 */
#define TOL             1e-4f

static struct meter_data_s make_meter_data(float32_t freq, float32_t rmsV,
                                            float32_t rmsI, float32_t actP)
{
    struct meter_data_s d;
    memset(&d, 0, sizeof(d));
    d.frequency = freq;
    for (int i = 0; i < METER_PHASE_COUNT; i++) {
        d.phase_data[i].rms_voltage = rmsV;
        d.phase_data[i].rms_current = rmsI;
        d.phase_data[i].act_pwr     = actP;
        d.phase_data[i].app_pwr     = rmsV * rmsI;
        d.phase_data[i].pf          = (rmsV * rmsI > 0.0f) ?
                                       actP / (rmsV * rmsI) : 0.0f;
    }
    d.vol_line.ab = rmsV * 1.732f;
    d.vol_line.bc = rmsV * 1.732f;
    d.vol_line.ca = rmsV * 1.732f;
    return d;
}

/* ------------------------------------------------------------------ */
/*  setUp / tearDown                                                    */
/* ------------------------------------------------------------------ */
void setUp(void)  {}
void tearDown(void) {}

/* ================================================================== */
/*  A. ema_get                                                         */
/* ================================================================== */

/**
 * Formula: out = alpha*in + (1-alpha)*last
 */
void test_ema_basic_formula(void)
{
    float32_t result = ema_get(10.0f, 0.0f, 0.5f);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 5.0f, result);
}

void test_ema_alpha_1_returns_input(void)
{
    /* alpha=1 → output = input */
    TEST_ASSERT_FLOAT_WITHIN(TOL, 42.0f, ema_get(42.0f, 999.0f, 1.0f));
}

void test_ema_alpha_0_returns_last(void)
{
    /* alpha=0 → output = last */
    TEST_ASSERT_FLOAT_WITHIN(TOL, 999.0f, ema_get(42.0f, 999.0f, 0.0f));
}

void test_ema_converges_to_constant_input(void)
{
    /* Feed constant 100.0f — EMA must converge within N steps */
    float32_t val = 0.0f;
    for (int i = 0; i < 200; i++)
        val = ema_get(100.0f, val, EMA_ALPHA);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, val);
}

void test_ema_step_response_monotonic(void)
{
    /* Step from 0 to 1: EMA should increase monotonically */
    float32_t val = 0.0f, prev = 0.0f;
    for (int i = 0; i < 50; i++) {
        val = ema_get(1.0f, val, EMA_ALPHA);
        TEST_ASSERT_TRUE_MESSAGE(val >= prev, "EMA not monotonically increasing");
        prev = val;
    }
}

void test_ema_negative_input(void)
{
    float32_t result = ema_get(-10.0f, 0.0f, 0.5f);
    TEST_ASSERT_FLOAT_WITHIN(TOL, -5.0f, result);
}

void test_ema_zero_input_zero_last(void)
{
    TEST_ASSERT_FLOAT_WITHIN(TOL, 0.0f, ema_get(0.0f, 0.0f, EMA_ALPHA));
}

/* ================================================================== */
/*  B. maf_init / maf_update                                           */
/* ================================================================== */

void test_maf_init_clears_state(void)
{
    struct maf_s maf;
    /* Fill with garbage */
    memset(&maf, 0xFF, sizeof(maf));
    maf_init(&maf);
    TEST_ASSERT_EQUAL_UINT32(0, maf.sample_count);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 0.0f, maf.sum);
}

void test_maf_single_sample_returns_itself_divided_by_size(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = maf_update(&maf, (float32_t)MAF_SIZE);
    /* sum = MAF_SIZE, output = sum / MAF_SIZE = 1.0 */
    TEST_ASSERT_FLOAT_WITHIN(TOL, 1.0f, result);
}

void test_maf_converges_to_constant(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = 0.0f;
    /* Feed MAF_SIZE identical samples → output = that value */
    for (int i = 0; i < MAF_SIZE; i++)
        result = maf_update(&maf, 10.0f);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 10.0f, result);
}

void test_maf_output_is_running_average(void)
{
    struct maf_s maf;
    maf_init(&maf);
    /* Fill with 1.0, then push one 0.0 → average drops by 1/MAF_SIZE */
    for (int i = 0; i < MAF_SIZE; i++)
        maf_update(&maf, 1.0f);
    float32_t result = maf_update(&maf, 0.0f);
    float32_t expected = (float32_t)(MAF_SIZE - 1) / (float32_t)MAF_SIZE;
    TEST_ASSERT_FLOAT_WITHIN(TOL, expected, result);
}

void test_maf_circular_buffer_wraps(void)
{
    struct maf_s maf;
    maf_init(&maf);
    /* Push MAF_SIZE+1 samples — oldest should be evicted */
    for (int i = 0; i < MAF_SIZE; i++)
        maf_update(&maf, 1.0f);
    /* Now push MAF_SIZE samples of 2.0 — output should converge to 2.0 */
    float32_t result = 0.0f;
    for (int i = 0; i < MAF_SIZE; i++)
        result = maf_update(&maf, 2.0f);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 2.0f, result);
}

void test_maf_sample_count_wraps_at_max(void)
{
    struct maf_s maf;
    maf_init(&maf);
    for (int i = 0; i < MAF_SIZE; i++)
        maf_update(&maf, 1.0f);
    /* After MAF_SIZE updates, sample_count should wrap to 0 */
    TEST_ASSERT_EQUAL_UINT32(0, maf.sample_count);
}

void test_maf_zero_input_returns_zero(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = 0.0f;
    for (int i = 0; i < MAF_SIZE; i++)
        result = maf_update(&maf, 0.0f);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 0.0f, result);
}

void test_maf_negative_samples(void)
{
    struct maf_s maf;
    maf_init(&maf);
    float32_t result = 0.0f;
    for (int i = 0; i < MAF_SIZE; i++)
        result = maf_update(&maf, -5.0f);
    TEST_ASSERT_FLOAT_WITHIN(TOL, -5.0f, result);
}

/* ================================================================== */
/*  C. share_data                                                       */
/* ================================================================== */

/* Helper: reset share_data to known state */
static void shdat_reset(void)
{
    /* Write zeros twice to initialize both buffers */
    struct meter_data_s zero;
    memset(&zero, 0, sizeof(zero));
    shdat_wrt_meter_data(&zero);
    shdat_wrt_meter_data(&zero);
    shdat_set_meter_state(METER_STATE_START);
}

void test_shdat_initial_state_is_start(void)
{
    shdat_reset();
    TEST_ASSERT_EQUAL_INT(METER_STATE_START, shdat_get_meter_current_state());
}

void test_shdat_set_and_get_state(void)
{
    shdat_set_meter_state(METER_STATE_RUNNING_3PHASE);
    TEST_ASSERT_EQUAL_INT(METER_STATE_RUNNING_3PHASE,
                          shdat_get_meter_current_state());
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
    for (int i = 0; i < 9; i++) {
        shdat_set_meter_state(states[i]);
        TEST_ASSERT_EQUAL_INT(states[i], shdat_get_meter_current_state());
    }
}

void test_shdat_wrt_and_get_frequency(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);
    /* Write many times so EMA converges */
    for (int i = 0; i < 50; i++)
        shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 50.0f, out.frequency);
}

void test_shdat_wrt_and_get_rms_voltage(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);
    for (int i = 0; i < 50; i++)
        shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    for (int ph = 0; ph < METER_PHASE_COUNT; ph++)
        TEST_ASSERT_FLOAT_WITHIN(1.0f, 230.0f, out.phase_data[ph].rms_voltage);
}

void test_shdat_wrt_and_get_active_power(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);
    for (int i = 0; i < 50; i++)
        shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    for (int ph = 0; ph < METER_PHASE_COUNT; ph++)
        TEST_ASSERT_FLOAT_WITHIN(10.0f, 2000.0f, out.phase_data[ph].act_pwr);
}

/**
 * Double-buffer swap: get after write returns the written data (after EMA)
 */
void test_shdat_double_buffer_swap(void)
{
    shdat_reset();
    struct meter_data_s d1 = make_meter_data(50.0f, 100.0f, 1.0f, 80.0f);
    struct meter_data_s d2 = make_meter_data(60.0f, 200.0f, 2.0f, 160.0f);

    /* Write d1 many times to converge */
    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d1);
    struct meter_data_s out1 = shdat_get_meter_data();

    /* Switch to d2 and converge */
    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d2);
    struct meter_data_s out2 = shdat_get_meter_data();

    /* out2 frequency should be closer to 60 than out1 */
    TEST_ASSERT_TRUE(fabsf(out2.frequency - 60.0f) <
                     fabsf(out1.frequency - 60.0f));
}

/**
 * EMA smoothing: single step write should NOT jump immediately to new value
 */
void test_shdat_ema_smoothing_single_step(void)
{
    shdat_reset();

    /* Converge to 50Hz */
    struct meter_data_s d50 = make_meter_data(50.0f, 100.0f, 1.0f, 80.0f);
    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d50);

    /* Single write at 100Hz */
    struct meter_data_s d100 = make_meter_data(100.0f, 100.0f, 1.0f, 80.0f);
    shdat_wrt_meter_data(&d100);

    struct meter_data_s out = shdat_get_meter_data();
    /* EMA with alpha=0.2: out ≈ 0.2*100 + 0.8*50 = 60Hz, not 100Hz */
    TEST_ASSERT_TRUE_MESSAGE(out.frequency < 100.0f,
                             "EMA should dampen step change");
    TEST_ASSERT_TRUE_MESSAGE(out.frequency > 50.0f,
                             "EMA output should be above previous value");
}

/**
 * Energy fields pass through without EMA
 */
void test_shdat_energy_passthrough(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 100.0f, 1.0f, 80.0f);
    d.energy_hWh = 12345;
    d.energy_Ws  = 9999.0;
    shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    TEST_ASSERT_EQUAL_INT64(12345, out.energy_hWh);
    TEST_ASSERT_FLOAT_WITHIN(TOL, 9999.0f, (float32_t)out.energy_Ws);
}

/**
 * Vol line fields are EMA smoothed
 */
void test_shdat_vol_line_ema_smoothed(void)
{
    shdat_reset();
    struct meter_data_s d = make_meter_data(50.0f, 230.0f, 10.0f, 2000.0f);
    for (int i = 0; i < 50; i++) shdat_wrt_meter_data(&d);
    struct meter_data_s out = shdat_get_meter_data();
    float32_t expected = 230.0f * 1.732f;
    TEST_ASSERT_FLOAT_WITHIN(1.0f, expected, out.vol_line.ab);
    TEST_ASSERT_FLOAT_WITHIN(1.0f, expected, out.vol_line.bc);
    TEST_ASSERT_FLOAT_WITHIN(1.0f, expected, out.vol_line.ca);
}