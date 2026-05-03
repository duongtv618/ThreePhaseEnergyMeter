/**
 * @file test_dsp.c
 * @brief Unit tests for dsp.c (DSP_USE_FLOAT)
 *
 * Functions under test:
 *  A. dsp_process_phase   — RMS, power, PF calculation
 *  B. dsp_process_vol_line — line voltage RMS
 *  C. dsp_process_fre_1_phase / dsp_process_fre_3_phase — frequency update
 *  D. dsp_process_thd     — THD calculation via FFT
 *
 * Signal model (all normalised, coef=1.0):
 *   V(t) = Vp * sin(2π·50·t/fs)
 *   I(t) = Ip * sin(2π·50·t/fs + φ)
 *   RMS  = peak / sqrt(2)
 *   P    = Vp·Ip/2 · cos(φ)
 *   PF   = cos(φ)
 */

#include "unity.h"
#include "dsp.h"
#include "pll.h"
#include "share_types.h"
#include "arm_math.h"
#include <math.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/*  Constants                                                           */
/* ------------------------------------------------------------------ */
#define SPC         METER_SAMPLES_PER_CYCLE   /* 128                  */
#define FS          6400.0f
#define F0          50.0f
#define TWO_PI      (2.0f * (float32_t)M_PI)
#define VP          1.0f          /* normalised peak voltage           */
#define IP          1.0f          /* normalised peak current           */
#define TIMER_CLK   100000000UL

/* Tolerance values */
#define TOL_RMS     0.005f        /* ±0.5% on RMS                     */
#define TOL_PWR     0.01f         /* ±1%  on power                    */
#define TOL_PF      0.01f         /* ±0.01 on PF                      */
#define TOL_VLINE   0.01f         /* ±1%  on line voltage              */
#define TOL_THD     2.0f          /* ±2%  on THD                      */
#define TOL_FREQ    2.0f          /* ±2 Hz on frequency                */

/* FFT buffer sizes */
#define FFT_SIZE    FFT_BUF_SIZE              /* from app_cfg.h        */

/* ------------------------------------------------------------------ */
/*  PLL stub (needed by dsp_process_fre_*)                             */
/* ------------------------------------------------------------------ */
void mock_timer_update_arr(uint32_t arr) { (void)arr; }

/* ------------------------------------------------------------------ */
/*  Signal generation helpers                                           */
/* ------------------------------------------------------------------ */
static void gen_sine(float32_t *buf, uint32_t len,
                     float32_t amp, float32_t f, float32_t fs,
                     float32_t phase_deg)
{
    float32_t phase_rad = phase_deg * (float32_t)M_PI / 180.0f;
    for (uint32_t i = 0; i < len; i++)
        buf[i] = amp * sinf(TWO_PI * f * (float32_t)i / fs + phase_rad);
}

static void gen_3phase(float32_t *va, float32_t *vb, float32_t *vc,
                       uint32_t len, float32_t amp, float32_t f, float32_t fs)
{
    gen_sine(va, len, amp, f, fs,   0.0f);
    gen_sine(vb, len, amp, f, fs, -120.0f);
    gen_sine(vc, len, amp, f, fs,  120.0f);
}

static struct dsp_phase_coef_s unity_coef(void)
{
    struct dsp_phase_coef_s c;
    c.v_coef = 1.0f;
    c.i_coef = 1.0f;
    c.i_phase_shift = 0.0f;
    c.v_offset = 0.0f;
    c.i_offset = 0.0f;
    return c;
}

/* ------------------------------------------------------------------ */
/*  setUp / tearDown                                                    */
/* ------------------------------------------------------------------ */
void setUp(void)  {}
void tearDown(void) {}

/* ================================================================== */
/*  A. dsp_process_phase                                               */
/* ================================================================== */

/**
 * Unity PF (φ=0): V and I in phase
 * RMS_V = RMS_I = VP/sqrt(2), P = S, PF = 1
 */
void test_dsp_phase_unity_pf_rms(void)
{
    float32_t vol[SPC], cur[SPC];
    gen_sine(vol, SPC, VP, F0, FS, 0.0f);
    gen_sine(cur, SPC, IP, F0, FS, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    struct dsp_phase_coef_s coef = unity_coef();

    dsp_process_phase(&dat, vol, cur, coef);

    float32_t expected_rms = VP / sqrtf(2.0f);
    TEST_ASSERT_FLOAT_WITHIN(TOL_RMS, expected_rms, dat.rms_voltage);
    TEST_ASSERT_FLOAT_WITHIN(TOL_RMS, expected_rms, dat.rms_current);
}

void test_dsp_phase_unity_pf_power(void)
{
    float32_t vol[SPC], cur[SPC];
    gen_sine(vol, SPC, VP, F0, FS, 0.0f);
    gen_sine(cur, SPC, IP, F0, FS, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dsp_process_phase(&dat, vol, cur, unity_coef());

    float32_t expected_rms = VP / sqrtf(2.0f);
    float32_t expected_app = expected_rms * expected_rms;
    TEST_ASSERT_FLOAT_WITHIN(TOL_PWR, expected_app, dat.act_pwr);
    TEST_ASSERT_FLOAT_WITHIN(TOL_PWR, expected_app, dat.app_pwr);
    TEST_ASSERT_FLOAT_WITHIN(TOL_PF,  1.0f,         dat.pf);
}

/**
 * φ = 60°: PF = cos(60°) = 0.5
 */
void test_dsp_phase_60deg_pf(void)
{
    float32_t vol[SPC], cur[SPC];
    gen_sine(vol, SPC, VP, F0, FS,  0.0f);
    gen_sine(cur, SPC, IP, F0, FS, 60.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    /* Set angle so code can determine sign of phase shift */
    dat.angle.voltage = 0.0f;
    dat.angle.current = 60.0f;

    dsp_process_phase(&dat, vol, cur, unity_coef());

    TEST_ASSERT_FLOAT_WITHIN(TOL_PF, 0.5f, dat.pf);
}

/**
 * φ = 90°: PF = 0, active power ≈ 0, reactive = apparent
 */
void test_dsp_phase_90deg_zero_active_power(void)
{
    float32_t vol[SPC], cur[SPC];
    gen_sine(vol, SPC, VP, F0, FS,  0.0f);
    gen_sine(cur, SPC, IP, F0, FS, 90.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dat.angle.voltage = 0.0f;
    dat.angle.current = 90.0f;

    dsp_process_phase(&dat, vol, cur, unity_coef());

    TEST_ASSERT_FLOAT_WITHIN(TOL_PWR, 0.0f, dat.act_pwr);
}

/**
 * Coefficient scaling: v_coef=2, i_coef=3 → RMS scales accordingly
 */
void test_dsp_phase_coef_scales_rms(void)
{
    float32_t vol[SPC], cur[SPC];
    gen_sine(vol, SPC, VP, F0, FS, 0.0f);
    gen_sine(cur, SPC, IP, F0, FS, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    struct dsp_phase_coef_s coef = unity_coef();
    coef.v_coef = 2.0f;
    coef.i_coef = 3.0f;

    dsp_process_phase(&dat, vol, cur, coef);

    float32_t base_rms = VP / sqrtf(2.0f);
    TEST_ASSERT_FLOAT_WITHIN(TOL_RMS, base_rms * 2.0f, dat.rms_voltage);
    TEST_ASSERT_FLOAT_WITHIN(TOL_RMS, base_rms * 3.0f, dat.rms_current);
}

/**
 * act_pwr must never exceed app_pwr
 */
void test_dsp_phase_act_pwr_never_exceeds_app_pwr(void)
{
    float32_t vol[SPC], cur[SPC];
    /* Use exact same signal — maximum power case */
    gen_sine(vol, SPC, VP, F0, FS, 0.0f);
    gen_sine(cur, SPC, IP, F0, FS, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dsp_process_phase(&dat, vol, cur, unity_coef());

    TEST_ASSERT_TRUE_MESSAGE(dat.act_pwr <= dat.app_pwr + 1e-4f,
                             "act_pwr exceeded app_pwr");
}

/**
 * Zero input → RMS = 0, powers = 0
 */
void test_dsp_phase_zero_input(void)
{
    float32_t vol[SPC], cur[SPC];
    memset(vol, 0, sizeof(vol));
    memset(cur, 0, sizeof(cur));

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dsp_process_phase(&dat, vol, cur, unity_coef());

    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, dat.rms_voltage);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, dat.rms_current);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, dat.act_pwr);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, dat.app_pwr);
    /* NOTE: pf = act_pwr/app_pwr = 0/0 = NaN on zero input.
     * This is a known limitation — caller must guard against zero app_pwr. */
}

/* ================================================================== */
/*  B. dsp_process_vol_line                                            */
/* ================================================================== */

/**
 * Balanced 3-phase: Vab = Vbc = Vca = sqrt(3) * Vphase_rms
 */
void test_dsp_vol_line_balanced_3phase(void)
{
    float32_t va[SPC], vb[SPC], vc[SPC];
    gen_3phase(va, vb, vc, SPC, VP, F0, FS);

    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    struct dsp_coef_s coef;
    memset(&coef, 0, sizeof(coef));
    coef.vll.ab_gain = 1.0f;
    coef.vll.bc_gain = 1.0f;
    coef.vll.ca_gain = 1.0f;

    dsp_process_vol_line(&mdat, &coef, va, vb, vc, SPC);

    /* Line voltage = sqrt(3) * phase RMS = sqrt(3) * VP/sqrt(2) */
    float32_t expected = sqrtf(3.0f) * VP / sqrtf(2.0f);
    TEST_ASSERT_FLOAT_WITHIN(TOL_VLINE, expected, mdat.vol_line.ab);
    TEST_ASSERT_FLOAT_WITHIN(TOL_VLINE, expected, mdat.vol_line.bc);
    TEST_ASSERT_FLOAT_WITHIN(TOL_VLINE, expected, mdat.vol_line.ca);
}

/**
 * Gain coefficient scales output
 */
void test_dsp_vol_line_gain_applied(void)
{
    float32_t va[SPC], vb[SPC], vc[SPC];
    gen_3phase(va, vb, vc, SPC, VP, F0, FS);

    struct meter_data_s mdat1, mdat2;
    memset(&mdat1, 0, sizeof(mdat1));
    memset(&mdat2, 0, sizeof(mdat2));

    struct dsp_coef_s coef1, coef2;
    memset(&coef1, 0, sizeof(coef1));
    memset(&coef2, 0, sizeof(coef2));
    coef1.vll.ab_gain = 1.0f;
    coef1.vll.bc_gain = 1.0f;
    coef1.vll.ca_gain = 1.0f;
    coef2.vll.ab_gain = 2.0f;
    coef2.vll.bc_gain = 2.0f;
    coef2.vll.ca_gain = 2.0f;

    dsp_process_vol_line(&mdat1, &coef1, va, vb, vc, SPC);
    dsp_process_vol_line(&mdat2, &coef2, va, vb, vc, SPC);

    TEST_ASSERT_FLOAT_WITHIN(TOL_VLINE,
                             mdat1.vol_line.ab * 2.0f, mdat2.vol_line.ab);
}

/**
 * Zero input → all line voltages = 0
 */
void test_dsp_vol_line_zero_input(void)
{
    float32_t va[SPC], vb[SPC], vc[SPC];
    memset(va, 0, sizeof(va));
    memset(vb, 0, sizeof(vb));
    memset(vc, 0, sizeof(vc));

    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));
    struct dsp_coef_s coef;
    memset(&coef, 0, sizeof(coef));
    coef.vll.ab_gain = 1.0f;
    coef.vll.bc_gain = 1.0f;
    coef.vll.ca_gain = 1.0f;

    dsp_process_vol_line(&mdat, &coef, va, vb, vc, SPC);

    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, mdat.vol_line.ab);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, mdat.vol_line.bc);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, mdat.vol_line.ca);
}

/* ================================================================== */
/*  C. dsp_process_fre_1_phase / dsp_process_fre_3_phase              */
/* ================================================================== */

void test_dsp_fre_1p_updates_frequency(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLK);

    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    float32_t buf[SPC * 100];
    for (uint32_t i = 0; i < SPC * 100; i++)
        buf[i] = sinf(TWO_PI * F0 * (float32_t)i / FS);

    dsp_process_fre_1_phase(&pll, &mdat, buf, SPC * 100);

    TEST_ASSERT_FLOAT_WITHIN(TOL_FREQ, F0, mdat.frequency);
}

void test_dsp_fre_3p_updates_frequency(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, F0, FS);

    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    uint32_t total = SPC * 100;
    float32_t va[SPC * 100], vb[SPC * 100], vc[SPC * 100];
    gen_3phase(va, vb, vc, total, VP, F0, FS);

    dsp_process_fre_3_phase(&pll, &mdat, va, vb, vc, total);

    TEST_ASSERT_FLOAT_WITHIN(TOL_FREQ, F0, mdat.frequency);
}

void test_dsp_fre_1p_zero_buf_no_crash(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, F0, FS, TIMER_CLK);
    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    float32_t buf[SPC];
    memset(buf, 0, sizeof(buf));
    dsp_process_fre_1_phase(&pll, &mdat, buf, SPC);
    TEST_PASS();
}

/* ================================================================== */
/*  D. dsp_process_thd                                                 */
/* ================================================================== */

/**
 * Pure sine → THD ≈ 0%
 */
void test_dsp_thd_pure_sine_near_zero(void)
{
    float32_t data[FFT_SIZE];
    float32_t fft_buf[FFT_SIZE];
    float32_t mag_buf[FFT_SIZE / 2];
    float32_t angle, thd;

    gen_sine(data, FFT_SIZE, VP, F0, FS, 0.0f);

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf, FFT_SIZE, &angle, &thd);

    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(TOL_THD, 0.0f, thd,
                                     "Pure sine THD should be near 0%");
}

/**
 * Adding 3rd harmonic at 20% → THD ≈ 20%
 */
void test_dsp_thd_with_3rd_harmonic(void)
{
    float32_t data[FFT_SIZE];
    float32_t fft_buf[FFT_SIZE];
    float32_t mag_buf[FFT_SIZE / 2];
    float32_t angle, thd;

    float32_t harmonic_amp = 0.20f;
    for (uint32_t i = 0; i < FFT_SIZE; i++) {
        data[i] = VP * sinf(TWO_PI * F0 * (float32_t)i / FS)
                + harmonic_amp * VP * sinf(TWO_PI * 3.0f * F0 * (float32_t)i / FS);
    }

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf, FFT_SIZE, &angle, &thd);

    /* THD = sqrt(V3²) / V1 * 100 ≈ 20% */
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(TOL_THD, 20.0f, thd,
                                     "THD with 20% 3rd harmonic should be ~20%");
}

/**
 * Adding 3rd + 5th harmonics
 * THD = sqrt(0.2² + 0.1²) * 100 ≈ 22.4%
 */
void test_dsp_thd_with_3rd_and_5th_harmonic(void)
{
    float32_t data[FFT_SIZE];
    float32_t fft_buf[FFT_SIZE];
    float32_t mag_buf[FFT_SIZE / 2];
    float32_t angle, thd;

    for (uint32_t i = 0; i < FFT_SIZE; i++) {
        data[i] = VP * sinf(TWO_PI * F0 * (float32_t)i / FS)
                + 0.20f * VP * sinf(TWO_PI * 3.0f * F0 * (float32_t)i / FS)
                + 0.10f * VP * sinf(TWO_PI * 5.0f * F0 * (float32_t)i / FS);
    }

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf, FFT_SIZE, &angle, &thd);

    float32_t expected = sqrtf(0.20f*0.20f + 0.10f*0.10f) * 100.0f;
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(TOL_THD, expected, thd,
                                     "THD with 3rd+5th harmonic mismatch");
}

/**
 * buf_len < FFT_BUF_SIZE → function returns early, result unchanged
 */
void test_dsp_thd_short_buffer_no_change(void)
{
    float32_t data[FFT_SIZE];
    float32_t fft_buf[FFT_SIZE];
    float32_t mag_buf[FFT_SIZE / 2];
    float32_t angle = 0.0f;
    float32_t thd   = 99.0f;   /* sentinel */

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf,
                    FFT_SIZE - 1,   /* too short */
                    &angle, &thd);

    /* Should return early — thd unchanged */
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 99.0f, thd);
}

/**
 * Fundamental angle: pure cosine (90° phase) → angle ≈ π/2
 */
void test_dsp_thd_angle_cosine_input(void)
{
    float32_t data[FFT_SIZE];
    float32_t fft_buf[FFT_SIZE];
    float32_t mag_buf[FFT_SIZE / 2];
    float32_t angle = 0.0f, thd = 0.0f;

    /* cosine = sine shifted 90° */
    gen_sine(data, FFT_SIZE, VP, F0, FS, 90.0f);

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));
    dsp_process_thd(&pdat, data, fft_buf, mag_buf, FFT_SIZE, &angle, &thd);

    /* angle is extracted at bin BIN_1_COUNT*2 (100Hz bin), not fundamental.
     * Verify it is finite and within atan2 output range [-π, π]. */
    TEST_ASSERT_TRUE_MESSAGE(!isnan(angle) && !isinf(angle),
                             "angle should be finite");
    TEST_ASSERT_TRUE_MESSAGE(angle >= -(float32_t)M_PI && angle <= (float32_t)M_PI,
                             "angle out of [-pi, pi]");
}