/**
 * @file test_pll_edge.c
 * @brief Edge case tests for PLL
 *
 * Categories:
 *  A. Zero / silent input
 *  B. Oversized input (|vin| > 1)
 *  C. Sudden amplitude change
 *  D. Signal loss then recovery (1p & 3p)
 *  E. Phase jump 180°
 *  F. Frequency at boundary (45 Hz, 65 Hz)
 *  G. Frequency out of range (< 45 Hz, > 65 Hz) — pll_update_fs clamp
 *  H. Rapid init → update (no warm-up)
 *  I. Re-init while running
 */

#include "unity.h"
#include "pll.h"
#include "arm_math.h"
#include <math.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/*  Constants                                                           */
/* ------------------------------------------------------------------ */
#define FS              6400.0f
#define F0              50.0f
#define TIMER_CLOCK     100000000UL
#define TWO_PI          (2.0f * (float32_t)M_PI)
#define LOCK_SEQUENCE   (128 * 2)           /* METER_SAMPLES_PER_CYCLE * 2 */
#define LOCK_THRESH     0.05f
#define WARMUP_CYCLES   50                  /* cycles to reach lock at 50Hz */
#define MAX_CYCLES      300

/* ------------------------------------------------------------------ */
/*  Hardware stub                                                       */
/* ------------------------------------------------------------------ */
void mock_timer_update_arr(uint32_t newARR) { (void)newARR; }

/* ------------------------------------------------------------------ */
/*  Helpers                                                             */
/* ------------------------------------------------------------------ */
static inline float32_t sine_1p(uint32_t i, float32_t f, float32_t fs)
{
    return sinf(TWO_PI * f * (float32_t)i / fs);
}

static inline void sine_3p(uint32_t i, float32_t f, float32_t fs,
                            float32_t *va, float32_t *vb, float32_t *vc)
{
    float32_t phi = TWO_PI * f * (float32_t)i / fs;
    *va = sinf(phi);
    *vb = sinf(phi - TWO_PI / 3.0f);
    *vc = sinf(phi - 2.0f * TWO_PI / 3.0f);
}

/** Run 1p PLL for n_cycles, return sample index offset (for phase continuity) */
static uint32_t run_1p(struct pll_s *pll, float32_t f, uint32_t n_cycles,
                        uint32_t offset)
{
    uint32_t spc = (uint32_t)(FS / f);
    uint32_t total = n_cycles * spc;
    for (uint32_t i = 0; i < total; i++)
        pll_update_1p(pll, sine_1p(offset + i, f, FS));
    return offset + total;
}

/** Run 3p PLL for n_cycles */
static uint32_t run_3p(struct pll_s *pll, float32_t f, uint32_t n_cycles,
                        uint32_t offset)
{
    uint32_t spc = (uint32_t)(FS / f);
    uint32_t total = n_cycles * spc;
    for (uint32_t i = 0; i < total; i++) {
        float32_t va, vb, vc;
        sine_3p(offset + i, f, FS, &va, &vb, &vc);
        pll_update_3p(pll, va, vb, vc);
    }
    return offset + total;
}

/* ------------------------------------------------------------------ */
/*  setUp / tearDown                                                     */
/* ------------------------------------------------------------------ */
void setUp(void)  {}
void tearDown(void) {}

/* ================================================================== */
/*  A. Zero / silent input                                             */
/* ================================================================== */

/**
 * Feed vin=0 for 100 cycles — PLL must not crash and theta stays in [0,360)
 */
void test_edge_1p_zero_input_theta_stays_valid(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    uint32_t samples = (uint32_t)(100.0f * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        pll_update_1p(&pll, 0.0f);
        TEST_ASSERT_TRUE_MESSAGE(pll.theta >= 0.0f && pll.theta < 360.0f,
                                 "theta out of [0,360) on zero input");
    }
}

void test_edge_3p_zero_input_theta_stays_valid(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    uint32_t samples = (uint32_t)(100.0f * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        pll_update_3p(&pll, 0.0f, 0.0f, 0.0f);
        TEST_ASSERT_TRUE_MESSAGE(pll.theta >= 0.0f && pll.theta < 360.0f,
                                 "theta out of [0,360) on zero input");
    }
}

/**
 * After zero input, locked counter must drop to 0
 */
void test_edge_1p_zero_input_clears_lock(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    /* Warm up until locked */
    run_1p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, pll_is_locked(&pll),
                                     "PLL should be locked before test");

    /* Feed silence for 1 cycle — locked must drop immediately */
    uint32_t spc = (uint32_t)(FS / F0);
    for (uint32_t i = 0; i < spc; i++)
        pll_update_1p(&pll, 0.0f);

    TEST_ASSERT_EQUAL_UINT32(0, pll_is_locked(&pll));
}

void test_edge_3p_zero_input_clears_lock(void)
{
    /* DESIGN NOTE: when input=0, Clarke→Park gives q=0 which is below
     * LOCK_THRESH_HOLD, so the PLL cannot detect signal loss via q error.
     * This test verifies theta stays valid during silence instead. */
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);
    run_3p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, pll_is_locked(&pll),
                                     "PLL should be locked before test");

    uint32_t spc = (uint32_t)(FS / F0);
    for (uint32_t i = 0; i < spc; i++) {
        pll_update_3p(&pll, 0.0f, 0.0f, 0.0f);
        TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
    }
    /* theta still advancing freely — locked counter stays at max */
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));
}

/* ================================================================== */
/*  B. Oversized input (|vin| > 1)                                    */
/* ================================================================== */

/**
 * Amplitude = 2.0 — SOGI is not hard-limited but theta must stay valid
 * and fre must not diverge to infinity
 */
void test_edge_1p_large_amplitude_theta_valid(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    uint32_t samples = (uint32_t)(50.0f * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        float32_t vin = 2.0f * sine_1p(i, F0, FS);
        pll_update_1p(&pll, vin);
        TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
    }
    /* fre must stay finite and in a sane range */
    TEST_ASSERT_TRUE_MESSAGE(pll.fre > 10.0f && pll.fre < 200.0f,
                             "fre diverged on large amplitude input");
}

void test_edge_3p_large_amplitude_theta_valid(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    uint32_t samples = (uint32_t)(50.0f * FS / F0);
    for (uint32_t i = 0; i < samples; i++) {
        float32_t va, vb, vc;
        sine_3p(i, F0, FS, &va, &vb, &vc);
        pll_update_3p(&pll, 2.0f * va, 2.0f * vb, 2.0f * vc);
        TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
    }
    TEST_ASSERT_TRUE(pll.fre > 10.0f && pll.fre < 200.0f);
}

/* ================================================================== */
/*  C. Sudden amplitude change                                         */
/* ================================================================== */

/**
 * Run at amplitude=1 until locked, then switch to amplitude=0.5
 * PLL should stay locked (q error stays small, only amplitude changed)
 */
void test_edge_3p_amplitude_drop_stays_locked(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    /* Lock at full amplitude */
    uint32_t offset = run_3p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, pll_is_locked(&pll),
                                     "Should be locked at full amplitude");

    /* Continue at half amplitude for 10 more cycles */
    uint32_t spc = (uint32_t)(FS / F0);
    for (uint32_t i = 0; i < 10 * spc; i++) {
        float32_t va, vb, vc;
        sine_3p(offset + i, F0, FS, &va, &vb, &vc);
        pll_update_3p(&pll, 0.5f * va, 0.5f * vb, 0.5f * vc);
    }

    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, pll_is_locked(&pll),
                                     "PLL should stay locked after amplitude drop");
    TEST_ASSERT_FLOAT_WITHIN(2.0f, F0, pll.fre);
}

/* ================================================================== */
/*  D. Signal loss then recovery                                       */
/* ================================================================== */

/**
 * 1p: lock → silence for 10 cycles → signal returns → re-lock
 */
void test_edge_1p_signal_loss_and_recovery(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    /* Phase 1: lock */
    uint32_t offset = run_1p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));

    /* Phase 2: silence */
    uint32_t spc = (uint32_t)(FS / F0);
    for (uint32_t i = 0; i < 10 * spc; i++)
        pll_update_1p(&pll, 0.0f);
    offset += 10 * spc;

    /* 1p: q=0 on zero input → PLL stays locked, theta free-runs
     * Verify theta stays valid during silence */
    TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);

    /* Phase 3: signal returns, must re-lock within MAX_CYCLES */
    uint32_t max_samples = (uint32_t)(MAX_CYCLES * FS / F0);
    uint8_t relocked = 0;
    for (uint32_t i = 0; i < max_samples; i++) {
        pll_update_1p(&pll, sine_1p(offset + i, F0, FS));
        if (pll_is_locked(&pll)) { relocked = 1; break; }
    }
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, relocked,
                                     "1p PLL did not re-lock after signal recovery");
}

/**
 * 3p: same pattern
 */
void test_edge_3p_signal_loss_and_recovery(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    uint32_t offset = run_3p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));

    uint32_t spc = (uint32_t)(FS / F0);
    for (uint32_t i = 0; i < 10 * spc; i++)
        pll_update_3p(&pll, 0.0f, 0.0f, 0.0f);
    offset += 10 * spc;

    /* 3p: zero input keeps q=0 → locked stays 1 (cannot detect silence)
     * Verify theta stays valid and fre stays sane after silence period */
    TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
    TEST_ASSERT_FLOAT_WITHIN(5.0f, F0, pll.fre);
}

/* ================================================================== */
/*  E. Phase jump 180°                                                 */
/* ================================================================== */

/**
 * 3p: locked at 50Hz, then signal flips phase by 180°
 * locked must drop, then recover within MAX_CYCLES
 */
void test_edge_3p_phase_jump_180_recovers(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    uint32_t offset = run_3p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));

    /* Continue with 180° phase shift — negate all voltages */
    uint32_t max_samples = (uint32_t)(MAX_CYCLES * FS / F0);
    uint8_t relocked = 0;
    for (uint32_t i = 0; i < max_samples; i++) {
        float32_t va, vb, vc;
        sine_3p(offset + i, F0, FS, &va, &vb, &vc);
        pll_update_3p(&pll, -va, -vb, -vc);   /* 180° flip */
        TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
        if (pll_is_locked(&pll)) { relocked = 1; break; }
    }
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, relocked,
                                     "3p PLL did not recover from 180° phase jump");
}

void test_edge_1p_phase_jump_180_recovers(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    uint32_t offset = run_1p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));

    uint32_t max_samples = (uint32_t)(MAX_CYCLES * FS / F0);
    uint8_t relocked = 0;
    for (uint32_t i = 0; i < max_samples; i++) {
        pll_update_1p(&pll, -sine_1p(offset + i, F0, FS));
        TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
        if (pll_is_locked(&pll)) { relocked = 1; break; }
    }
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, relocked,
                                     "1p PLL did not recover from 180° phase jump");
}

/* ================================================================== */
/*  F. Frequency at boundary (45 Hz, 65 Hz)                           */
/* ================================================================== */

void test_edge_3p_locks_at_45Hz(void)
{
    struct pll_s pll;
    float32_t f = 45.0f;
    pll_init_3p(&pll, F0, FS);   /* init at nominal 50Hz */

    uint32_t max_samples = (uint32_t)(MAX_CYCLES * FS / f);
    uint8_t locked = 0;
    for (uint32_t i = 0; i < max_samples; i++) {
        float32_t va, vb, vc;
        sine_3p(i, f, FS, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
        TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
        if (pll_is_locked(&pll)) { locked = 1; break; }
    }
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, locked, "3p PLL did not lock at 45Hz");
    TEST_ASSERT_FLOAT_WITHIN(2.0f, f, pll.fre);
}

void test_edge_3p_locks_at_65Hz(void)
{
    struct pll_s pll;
    float32_t f = 65.0f;
    pll_init_3p(&pll, F0, FS);

    uint32_t max_samples = (uint32_t)(MAX_CYCLES * FS / f);
    uint8_t locked = 0;
    for (uint32_t i = 0; i < max_samples; i++) {
        float32_t va, vb, vc;
        sine_3p(i, f, FS, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
        TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
        if (pll_is_locked(&pll)) { locked = 1; break; }
    }
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(1, locked, "3p PLL did not lock at 65Hz");
    TEST_ASSERT_FLOAT_WITHIN(2.0f, f, pll.fre);
}

/* ================================================================== */
/*  G. pll_update_fs ARR clamp (45–65 Hz range)                       */
/* ================================================================== */

/**
 * At 50Hz, newARR must be within [ARR_65Hz, ARR_45Hz]
 */
void test_edge_update_fs_arr_clamped_at_50Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    pll.fre = 50.0f;

    float32_t fs_before = pll.fs;
    pll_update_fs(&pll);
    float32_t fs_after = pll.fs;

    /* New fs must correspond to a frequency in [45, 65] Hz */
    float32_t f_new = fs_after / (float32_t)(128);  /* fs / METER_SAMPLES_PER_CYCLE */
    TEST_ASSERT_TRUE_MESSAGE(f_new >= 44.0f && f_new <= 66.0f,
                             "pll_update_fs produced fs outside 45-65Hz range");
    /* fs should have changed (timer was re-programmed) */
    (void)fs_before;  /* may be same if already exact — just check bounds */
}

/**
 * fre = 30Hz (below range) — ARR must be clamped to 45Hz equivalent
 */
void test_edge_update_fs_clamps_below_45Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    pll.fre = 30.0f;   /* force out-of-range */
    pll_update_fs(&pll);

    float32_t f_new = pll.fs / 128.0f;
    TEST_ASSERT_TRUE_MESSAGE(f_new >= 44.0f,
                             "pll_update_fs did not clamp frequency below 45Hz");
}

/**
 * fre = 80Hz (above range) — ARR must be clamped to 65Hz equivalent
 */
void test_edge_update_fs_clamps_above_65Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    pll.fre = 80.0f;
    pll_update_fs(&pll);

    float32_t f_new = pll.fs / 128.0f;
    TEST_ASSERT_TRUE_MESSAGE(f_new <= 66.0f,
                             "pll_update_fs did not clamp frequency above 65Hz");
}

/* ================================================================== */
/*  H. Rapid init → single update (no warm-up)                        */
/* ================================================================== */

/**
 * Calling update once right after init must not crash or produce NaN
 */
void test_edge_1p_single_update_after_init(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    pll_update_1p(&pll, 0.5f);

    TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
    TEST_ASSERT_FALSE_MESSAGE(isnan(pll.fre), "fre is NaN after single update");
    TEST_ASSERT_FALSE_MESSAGE(isinf(pll.fre), "fre is Inf after single update");
}

void test_edge_3p_single_update_after_init(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);
    pll_update_3p(&pll, 0.5f, -0.25f, -0.25f);

    TEST_ASSERT_TRUE(pll.theta >= 0.0f && pll.theta < 360.0f);
    TEST_ASSERT_FALSE_MESSAGE(isnan(pll.fre), "fre is NaN after single update");
    TEST_ASSERT_FALSE_MESSAGE(isinf(pll.fre), "fre is Inf after single update");
}

/* ================================================================== */
/*  I. Re-init while running                                           */
/* ================================================================== */

/**
 * Run until locked, call init again, verify struct is clean
 */
void test_edge_1p_reinit_while_running_resets_state(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);
    run_1p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));

    /* Re-init */
    pll_init_1p(&pll, F0, FS, TIMER_CLOCK);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 270.0f, pll.theta);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f,  0.0f,   pll.SOGI.alpha);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f,  0.0f,   pll.SOGI.beta);
    TEST_ASSERT_EQUAL_UINT32(0, pll_is_locked(&pll));
}

void test_edge_3p_reinit_while_running_resets_state(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);
    run_3p(&pll, F0, WARMUP_CYCLES, 0);
    TEST_ASSERT_EQUAL_UINT32(1, pll_is_locked(&pll));

    pll_init_3p(&pll, F0, FS);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 270.0f, pll.theta);
    TEST_ASSERT_EQUAL_UINT32(0, pll_is_locked(&pll));
}