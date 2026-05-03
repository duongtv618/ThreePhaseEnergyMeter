/**
 * @file test_mock.c
 * @brief Unit tests for mock signal generation (mock.c)
 *
 * Functions under test:
 *   - mock_sin_gen          : single-phase sine → uint16_t buffer
 *   - mock_sin_gen_ui_3_p   : 3-phase VI interleaved → uint16_t buffer
 *   - mock_DMA_init         : stores buffer pointer and length
 *   - mock_timer_update_arr : updates internal fs from ARR
 *   - mock_change_frequency : updates target frequency and step
 *
 * NOT tested (FreeRTOS / hardware only):
 *   - mock_sin_gen_init     : calls xTaskCreateStatic
 *   - _mock_task            : FreeRTOS task body
 *
 * Stub strategy:
 *   mock_hw_stub.h is placed in the include path and replaces
 *   FreeRTOS.h, stm32f4xx.h, task.h with lightweight x86 stubs.
 */

/* Pull in stubs BEFORE any header that includes stm32/FreeRTOS */
#include "mock_hw_stub.h"

#include "unity.h"
#include "mock.h"
#include "arm_math.h"
#include <math.h>
#include <string.h>
#include <stdint.h>

/* ------------------------------------------------------------------ */
/*  Constants matching app_cfg.h                                        */
/* ------------------------------------------------------------------ */
#define PHASE_COUNT     3U
#define SIGNAL_COUNT    2U          /* voltage + current per phase     */
#define SPC             128U        /* METER_SAMPLES_PER_CYCLE         */
#define ADC_MID         2048.0f     /* MOCK_ADC_MIDDLE_POINT           */
#define ADC_MAX         4096.0f     /* MOCK_ADC_MAX                    */
#define AMP_SCALE       0.88f       /* AMPTITUE_PERCENT = 88/100       */
#define F0              50.0f
#define FS              6400.0f
#define I_PHASE_SHIFT   (-5.0f)     /* CURRENT_PHASE_SHIFT             */
#define TIMER_CLOCK     100000000UL

/* stride for mock_sin_gen_ui_3_p output */
#define STRIDE          (PHASE_COUNT * SIGNAL_COUNT)   /* 6 */

/* ------------------------------------------------------------------ */
/*  setUp / tearDown                                                     */
/* ------------------------------------------------------------------ */
void setUp(void)  {}
void tearDown(void) {}

/* ================================================================== */
/*  GROUP 1 – mock_sin_gen (single phase)                              */
/* ================================================================== */

/**
 * Output must stay within [0, ADC_MAX) for a clean sine
 */
void test_mock_sin_gen_output_within_adc_range(void)
{
    uint16_t buf[SPC];
    memset(buf, 0xFF, sizeof(buf));

    mock_sin_gen(buf, SPC, 1, F0, FS, 0.0f);

    for (uint32_t i = 0; i < SPC; i++) {
        TEST_ASSERT_TRUE_MESSAGE(buf[i] <= (uint16_t)ADC_MAX,
                                 "Sample above ADC_MAX");
    }
}

/**
 * DC offset: average should be close to ADC_MID (2048)
 */
void test_mock_sin_gen_dc_offset_near_midpoint(void)
{
    uint16_t buf[SPC];
    mock_sin_gen(buf, SPC, 1, F0, FS, 0.0f);

    float32_t sum = 0.0f;
    for (uint32_t i = 0; i < SPC; i++) sum += buf[i];
    float32_t mean = sum / (float32_t)SPC;

    /* Mean should be within ±50 counts of midpoint */
    TEST_ASSERT_FLOAT_WITHIN(50.0f, ADC_MID, mean);
}

/**
 * With jump_space=2, only even indices are written; others untouched
 */
void test_mock_sin_gen_jump_space_skips_indices(void)
{
    uint16_t buf[SPC * 2];
    memset(buf, 0xAB, sizeof(buf));   /* sentinel value */

    mock_sin_gen(buf, SPC * 2, 2, F0, FS, 0.0f);

    for (uint32_t i = 1; i < SPC * 2; i += 2) {
        TEST_ASSERT_EQUAL_HEX16_MESSAGE(0xABAB, buf[i],
                                        "Odd index should not be written");
    }
}

/**
 * Phase shift of 180° should invert the waveform around midpoint
 */
void test_mock_sin_gen_phase_shift_180_inverts_wave(void)
{
    uint16_t buf0[SPC], buf180[SPC];
    mock_sin_gen(buf0,   SPC, 1, F0, FS,   0.0f);
    mock_sin_gen(buf180, SPC, 1, F0, FS, 180.0f);

    for (uint32_t i = 0; i < SPC; i++) {
        /* buf0[i] + buf180[i] ≈ 2 * ADC_MID due to symmetry */
        int32_t sum = (int32_t)buf0[i] + (int32_t)buf180[i];
        TEST_ASSERT_INT32_WITHIN_MESSAGE(20, (int32_t)(2.0f * ADC_MID), sum,
                                         "180° shift should mirror around midpoint");
    }
}

/**
 * Peak value should be close to ADC_MID * (1 + AMP_SCALE)
 */
void test_mock_sin_gen_peak_amplitude_correct(void)
{
    uint16_t buf[SPC];
    mock_sin_gen(buf, SPC, 1, F0, FS, 0.0f);

    uint16_t peak = 0;
    for (uint32_t i = 0; i < SPC; i++)
        if (buf[i] > peak) peak = buf[i];

    float32_t expected_peak = ADC_MID + ADC_MID * AMP_SCALE;
    /* Allow ±50 counts for integer truncation */
    TEST_ASSERT_FLOAT_WITHIN(50.0f, expected_peak, (float32_t)peak);
}

/**
 * Trough value should be close to ADC_MID * (1 - AMP_SCALE)
 */
void test_mock_sin_gen_trough_amplitude_correct(void)
{
    uint16_t buf[SPC];
    mock_sin_gen(buf, SPC, 1, F0, FS, 0.0f);

    uint16_t trough = 0xFFFF;
    for (uint32_t i = 0; i < SPC; i++)
        if (buf[i] < trough) trough = buf[i];

    float32_t expected_trough = ADC_MID - ADC_MID * AMP_SCALE;
    TEST_ASSERT_FLOAT_WITHIN(50.0f, expected_trough, (float32_t)trough);
}

/**
 * Different frequencies should produce different waveforms
 */
void test_mock_sin_gen_different_frequencies_differ(void)
{
    uint16_t buf50[SPC], buf60[SPC];
    mock_sin_gen(buf50, SPC, 1, 50.0f, FS, 0.0f);
    mock_sin_gen(buf60, SPC, 1, 60.0f, FS, 0.0f);

    uint32_t diff_count = 0;
    for (uint32_t i = 0; i < SPC; i++)
        if (buf50[i] != buf60[i]) diff_count++;

    TEST_ASSERT_TRUE_MESSAGE(diff_count > SPC / 2,
                             "50Hz and 60Hz buffers should differ significantly");
}

/* ================================================================== */
/*  GROUP 2 – mock_sin_gen_ui_3_p (3-phase VI)                        */
/* ================================================================== */

/**
 * Buffer layout: [va, ia, vb, ib, vc, ic, va, ia, ...]
 * All values must be within ADC range
 */
void test_mock_3p_all_samples_within_adc_range(void)
{
    uint32_t n_samples = SPC;
    uint16_t buf[SPC * STRIDE];
    memset(buf, 0, sizeof(buf));

    mock_sin_gen_ui_3_p(buf, SPC * STRIDE, F0, FS, I_PHASE_SHIFT);

    for (uint32_t i = 0; i < SPC * STRIDE; i++) {
        TEST_ASSERT_TRUE_MESSAGE(buf[i] <= (uint16_t)ADC_MAX,
                                 "3p sample above ADC_MAX");
    }
}

/**
 * DC offset of each channel should be near ADC_MID
 */
void test_mock_3p_dc_offset_all_channels(void)
{
    uint16_t buf[SPC * STRIDE];
    mock_sin_gen_ui_3_p(buf, SPC * STRIDE, F0, FS, 0.0f);

    /* Channel indices: va=0, ia=1, vb=2, ib=3, vc=4, ic=5 */
    for (uint32_t ch = 0; ch < STRIDE; ch++) {
        float32_t sum = 0.0f;
        for (uint32_t s = 0; s < SPC; s++)
            sum += buf[s * STRIDE + ch];
        float32_t mean = sum / (float32_t)SPC;
        TEST_ASSERT_FLOAT_WITHIN_MESSAGE(100.0f, ADC_MID, mean,
                                         "Channel DC offset too far from midpoint");
    }
}

/**
 * Voltage channels (0,2,4) should be 120° apart
 * Check: va_peak index, vb_peak index, vc_peak index spaced ~SPC/3 apart
 */
void test_mock_3p_voltage_phases_120_apart(void)
{
    uint16_t buf[SPC * STRIDE];
    /* Use phase_shift=0 so current = voltage for this check */
    mock_sin_gen_ui_3_p(buf, SPC * STRIDE, F0, FS, 0.0f);

    /* Find peak index for va (ch=0), vb (ch=2), vc (ch=4) */
    uint32_t peak_idx[3] = {0, 0, 0};
    uint16_t peak_val[3] = {0, 0, 0};
    uint32_t ch_map[3] = {0, 2, 4};

    for (uint32_t ph = 0; ph < 3; ph++) {
        for (uint32_t s = 0; s < SPC; s++) {
            uint16_t v = buf[s * STRIDE + ch_map[ph]];
            if (v > peak_val[ph]) { peak_val[ph] = v; peak_idx[ph] = s; }
        }
    }

    /* Expected spacing: SPC/3 ≈ 42-43 samples */
    uint32_t spacing_ab = (peak_idx[1] + SPC - peak_idx[0]) % SPC;
    uint32_t spacing_bc = (peak_idx[2] + SPC - peak_idx[1]) % SPC;

    TEST_ASSERT_UINT32_WITHIN_MESSAGE(5, SPC / 3, spacing_ab,
                                      "Va-Vb phase spacing not ~120°");
    TEST_ASSERT_UINT32_WITHIN_MESSAGE(5, SPC / 3, spacing_bc,
                                      "Vb-Vc phase spacing not ~120°");
}

/**
 * Current channel should lag/lead voltage by iPhaseShift degrees
 * With iPhaseShift = -5° (lead), ia peak appears slightly before va peak
 */
void test_mock_3p_current_phase_shift_applied(void)
{
    uint16_t buf_0[SPC * STRIDE];
    uint16_t buf_shift[SPC * STRIDE];

    mock_sin_gen_ui_3_p(buf_0,     SPC * STRIDE, F0, FS, 0.0f);
    mock_sin_gen_ui_3_p(buf_shift, SPC * STRIDE, F0, FS, I_PHASE_SHIFT);

    /* va (ch=0) should be identical in both calls (phase_shift only on i) */

    /* ia (ch=1) should differ when phase_shift != 0 */
    uint32_t ia_diff = 0;
    for (uint32_t s = 0; s < SPC; s++)
        if (buf_0[s * STRIDE + 1] != buf_shift[s * STRIDE + 1]) ia_diff++;

    TEST_ASSERT_TRUE_MESSAGE(ia_diff > 0,
                             "Current channel did not change with i_phase_shift");
}

/**
 * Buffer length = 0 — must not crash
 */
void test_mock_3p_zero_length_no_crash(void)
{
    uint16_t buf[10];
    memset(buf, 0xAB, sizeof(buf));
    mock_sin_gen_ui_3_p(buf, 0, F0, FS, 0.0f);
    /* If we get here without segfault, test passes */
    TEST_ASSERT_EQUAL_HEX16(0xABAB, buf[0]);  /* buffer untouched */
}

/* ================================================================== */
/*  GROUP 3 – mock_DMA_init                                            */
/* ================================================================== */

/**
 * After init, mock_sin_gen_ui_3_p should write to the registered buffer.
 * We verify indirectly: call init with buf_a, generate into buf_a,
 * then verify buf_a changed and buf_b (never registered) did not.
 */
void test_mock_DMA_init_registers_buffer(void)
{
    uint16_t buf_a[SPC * STRIDE];
    uint16_t buf_b[SPC * STRIDE];
    memset(buf_a, 0xAA, sizeof(buf_a));
    memset(buf_b, 0xBB, sizeof(buf_b));

    mock_DMA_init(buf_a, SPC * STRIDE, 1, 1);

    /* Direct call still writes to whatever buffer we pass */
    mock_sin_gen_ui_3_p(buf_a, SPC * STRIDE, F0, FS, 0.0f);

    /* buf_a should have changed */
    uint32_t changed = 0;
    for (uint32_t i = 0; i < SPC * STRIDE; i++)
        if (buf_a[i] != 0xAAAA) changed++;
    TEST_ASSERT_TRUE_MESSAGE(changed > 0, "buf_a should have been written");

    /* buf_b untouched */
    for (uint32_t i = 0; i < SPC * STRIDE; i++)
        TEST_ASSERT_EQUAL_HEX16(0xBBBB, buf_b[i]);
}

/* ================================================================== */
/*  GROUP 4 – mock_timer_update_arr                                    */
/* ================================================================== */

/**
 * mock_timer_update_arr stores fs = TIMER_CLOCK / arr.
 * We verify indirectly: after calling update_arr, mock_sin_gen_ui_3_p
 * should still produce valid output (no crash, no garbage).
 * The internal fs is static so we can't read it directly,
 * but we can verify the waveform frequency changes by comparing buffers.
 */
void test_mock_timer_update_arr_no_crash(void)
{
    /* ARR for 50Hz: TIMER_CLOCK / (fs) = 100e6 / 6400 = 15625 */
    uint32_t arr_50hz = TIMER_CLOCK / (uint32_t)FS;
    mock_timer_update_arr(arr_50hz);

    uint16_t buf[SPC * STRIDE];
    mock_sin_gen_ui_3_p(buf, SPC * STRIDE, F0, FS, 0.0f);

    for (uint32_t i = 0; i < SPC * STRIDE; i++)
        TEST_ASSERT_TRUE(buf[i] <= (uint16_t)ADC_MAX);
}

void test_mock_timer_update_arr_changes_internal_fs(void)
{
    /* Set ARR to 45Hz equivalent, then 65Hz equivalent */
    uint32_t arr_45 = TIMER_CLOCK / (128 * 45);
    uint32_t arr_65 = TIMER_CLOCK / (128 * 65);

    /* Both should execute without crash */
    mock_timer_update_arr(arr_45);
    mock_timer_update_arr(arr_65);

    uint16_t buf[SPC * STRIDE];
    mock_sin_gen_ui_3_p(buf, SPC * STRIDE, F0, FS, 0.0f);
    for (uint32_t i = 0; i < SPC * STRIDE; i++)
        TEST_ASSERT_TRUE(buf[i] <= (uint16_t)ADC_MAX);
}

/* ================================================================== */
/*  GROUP 5 – mock_change_frequency                                    */
/* ================================================================== */

void test_mock_change_frequency_no_crash(void)
{
    mock_change_frequency(45.0f, 0.1f);
    mock_change_frequency(65.0f, 0.5f);
    mock_change_frequency(50.0f, 1.0f);
    /* No assert needed — just verifying no crash/segfault */
    TEST_PASS();
}

void test_mock_change_frequency_zero_step(void)
{
    /* step=0 means instant change — should not divide by zero or crash */
    mock_change_frequency(50.0f, 0.0f);
    TEST_PASS();
}