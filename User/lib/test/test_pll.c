/**
 * @file test_pll.c
 * @brief Unit tests for PLL (Phase Lock Loop) - DSP_USE_FLOAT
 *
 * Test strategy:
 *  - Init tests   : verify struct fields after pll_init_*
 *  - Convergence  : feed perfect sine → PLL must lock within finite cycles
 *  - Theta wrap   : theta always stays in [0, 360)
 *  - Frequency est: estimated fre must be within ±2 Hz of true frequency
 *  - Lock flag    : pll_is_locked() returns 1 after lock, 0 before
 *  - 3-phase      : balanced 3-phase input, same convergence expectation
 */

#include "unity.h"
#include "pll.h"
#include "arm_math.h"
#include <math.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/*  Constants                                                           */
/* ------------------------------------------------------------------ */
#define FS              6400.0f   /* sampling frequency (Hz) */
#define F0              50.0f     /* nominal grid frequency  */
#define TIMER_CLOCK     100000000UL
#define AMPLITUDE       1.0f      /* normalised to [-1, 1]   */
#define TWO_PI          (2.0f * (float32_t)M_PI)

/* LOCK_SQUENCE from pll.c = METER_SAMPLES_PER_CYCLE * 2 = 256        */
#define LOCK_SEQUENCE   (128 * 2)

/* Maximum cycles allowed before we expect lock                        */
#define MAX_LOCK_CYCLES 200   /* 200 grid cycles = 4 s at 50 Hz       */

/* ------------------------------------------------------------------ */
/*  Helpers                                                             */
/* ------------------------------------------------------------------ */

void mock_timer_update_arr(uint32_t newARR) { (void)newARR; }

/** Generate normalised single-phase sine sample at index i */
static inline float32_t sine_sample(uint32_t i, float32_t f, float32_t fs)
{
    return AMPLITUDE * sinf(TWO_PI * f * (float32_t)i / fs);
}

/** Generate balanced 3-phase samples at index i */
static inline void three_phase_samples(uint32_t i, float32_t f, float32_t fs,
                                        float32_t *va, float32_t *vb, float32_t *vc)
{
    float32_t phi = TWO_PI * f * (float32_t)i / fs;
    *va = AMPLITUDE * sinf(phi);
    *vb = AMPLITUDE * sinf(phi - TWO_PI / 3.0f);
    *vc = AMPLITUDE * sinf(phi - 2.0f * TWO_PI / 3.0f);
}

/* ------------------------------------------------------------------ */
/*  setUp / tearDown                                                    */
/* ------------------------------------------------------------------ */
void setUp(void)  {}
void tearDown(void) {}

/* ================================================================== */
/*  GROUP 1 – Initialisation                                           */
/* ================================================================== */

void test_pll_init_1p_sets_theta_to_270(void)
{
    struct pll_s pll;
    memset(&pll, 0xAB, sizeof(pll));   /* fill with garbage first */
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 270.0f, pll.theta);
}

void test_pll_init_1p_sets_delta_theta(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    /* delta_theta = f0 / fs * 360 */
    float32_t expected = F0 / FS * 360.0f;
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected, pll.delta_theta);
}

void test_pll_init_1p_stores_fs_and_f0(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, FS, pll.fs);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, F0, pll.f0);
}

void test_pll_init_1p_SOGI_cleared(void)
{
    struct pll_s pll;
    memset(&pll, 0xAB, sizeof(pll));
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, pll.SOGI.alpha);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, pll.SOGI.beta);
}

void test_pll_init_3p_sets_theta_to_270(void)
{
    struct pll_s pll;
    memset(&pll, 0xAB, sizeof(pll));
    pll_init_3p(&pll, F0, FS);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 270.0f, pll.theta);
}

void test_pll_init_3p_sets_delta_theta(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);
    float32_t expected = 360.0f * F0 / FS;
    TEST_ASSERT_FLOAT_WITHIN(0.001f, expected, pll.delta_theta);
}

/* ================================================================== */
/*  GROUP 2 – pll_is_locked logic                                      */
/* ================================================================== */

void test_pll_is_locked_returns_0_before_lock(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    /* Fresh init → locked counter = 0, threshold not reached */
    TEST_ASSERT_EQUAL_UINT32(0, pll_is_locked(&pll));
}

void test_pll_is_locked_returns_1_when_counter_at_threshold(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    pll.locked = LOCK_SEQUENCE;   /* force counter to threshold */
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));
}

void test_pll_is_locked_returns_0_when_counter_below_threshold(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    pll.locked = LOCK_SEQUENCE - 1;
    TEST_ASSERT_EQUAL_UINT32(0, pll_is_locked(&pll));
}

/* ================================================================== */
/*  GROUP 3 – Theta bounds                                             */
/* ================================================================== */

void test_pll_update_1p_theta_stays_in_0_to_360(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    /* Run for 10 full cycles */
    uint32_t samples = (uint32_t)(10.0f * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        float32_t vin = sine_sample(i, F0, FS);
        pll_update_1p(&pll, vin);
        TEST_ASSERT_TRUE_MESSAGE(pll.theta >= 0.0f && pll.theta < 360.0f,
                                 "theta out of [0, 360)");
    }
}

void test_pll_update_3p_theta_stays_in_0_to_360(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    uint32_t samples = (uint32_t)(10.0f * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        float32_t va, vb, vc;
        three_phase_samples(i, F0, FS, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
        TEST_ASSERT_TRUE_MESSAGE(pll.theta >= 0.0f && pll.theta < 360.0f,
                                 "theta out of [0, 360)");
    }
}

/* ================================================================== */
/*  GROUP 4 – Frequency estimation                                     */
/* ================================================================== */

void test_pll_update_1p_frequency_estimate_within_2Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    /* Warm up for MAX_LOCK_CYCLES grid cycles */
    uint32_t samples = (uint32_t)(MAX_LOCK_CYCLES * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        pll_update_1p(&pll, sine_sample(i, F0, FS));
    }

    TEST_ASSERT_FLOAT_WITHIN(2.0f, F0, pll.fre);
}

void test_pll_update_3p_frequency_estimate_within_2Hz(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    uint32_t samples = (uint32_t)(MAX_LOCK_CYCLES * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        float32_t va, vb, vc;
        three_phase_samples(i, F0, FS, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
    }

    TEST_ASSERT_FLOAT_WITHIN(2.0f, F0, pll.fre);
}

/* ================================================================== */
/*  GROUP 5 – Lock convergence                                         */
/* ================================================================== */

void test_pll_update_1p_locks_within_max_cycles(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    uint32_t total_samples = (uint32_t)(MAX_LOCK_CYCLES * FS / F0);
    for (uint32_t i = 0; i < total_samples; i++) {
        pll_update_1p(&pll, sine_sample(i, F0, FS));
    }

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, pll_is_locked(&pll),
        "PLL did not lock within MAX_LOCK_CYCLES grid cycles");
}

void test_pll_update_3p_locks_within_max_cycles(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    uint32_t total_samples = (uint32_t)(MAX_LOCK_CYCLES * FS / F0);
    for (uint32_t i = 0; i < total_samples; i++) {
        float32_t va, vb, vc;
        three_phase_samples(i, F0, FS, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
    }

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, pll_is_locked(&pll),
        "3P PLL did not lock within MAX_LOCK_CYCLES grid cycles");
}

/* ================================================================== */
/*  GROUP 6 – Off-nominal frequency tracking                          */
/* ================================================================== */

void test_pll_update_1p_tracks_49Hz(void)
{
    struct pll_s pll;
    float32_t true_freq = 49.0f;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);  /* init at 50 Hz nominal */

    uint32_t samples = (uint32_t)(MAX_LOCK_CYCLES * FS / true_freq);
    for (uint32_t i = 0; i < samples; i++) {
        pll_update_1p(&pll, sine_sample(i, true_freq, FS));
    }

    /* Frequency estimate should converge to 49 Hz within ±2 Hz */
    TEST_ASSERT_FLOAT_WITHIN(2.0f, true_freq, pll.fre);
}

void test_pll_update_3p_tracks_51Hz(void)
{
    struct pll_s pll;
    float32_t true_freq = 51.0f;
    pll_init_3p(&pll, F0, FS);

    uint32_t samples = (uint32_t)(MAX_LOCK_CYCLES * FS / true_freq);
    for (uint32_t i = 0; i < samples; i++) {
        float32_t va, vb, vc;
        three_phase_samples(i, true_freq, FS, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
    }

    TEST_ASSERT_FLOAT_WITHIN(2.0f, true_freq, pll.fre);
}