// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/lib/inc/dsp.h"
#include "User/lib/inc/pll.h"
#include "User/common/inc/share_types.h"
#include "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h"

void mock_timer_update_arr(uint32_t arr)
{ (void)arr; }

static void gen_sine(float32_t *buf, uint32_t len,
                     float32_t amp, float32_t f, float32_t fs,
                     float32_t phase_deg)
{
    float32_t phase_rad = phase_deg * (float32_t)
                                                3.14159265358979323846
                                                     / 180.0f;
    for (uint32_t i = 0; i < len; i++)
        buf[i] = amp * sinf((2.0f * (float32_t)
                           3.14159265358979323846
                           ) * f * (float32_t)i / fs + phase_rad);
}

static void gen_3phase(float32_t *va, float32_t *vb, float32_t *vc,
                       uint32_t len, float32_t amp, float32_t f, float32_t fs)
{
    gen_sine(va, len, amp, f, fs, 0.0f);
    gen_sine(vb, len, amp, f, fs, -120.0f);
    gen_sine(vc, len, amp, f, fs, 120.0f);
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

void setUp(void)
{}
void tearDown(void)
{}
void test_dsp_phase_unity_pf_rms(void)
{
    float32_t vol[128U], cur[128U];
    gen_sine(vol, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);
    gen_sine(cur, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    struct dsp_phase_coef_s coef = unity_coef();

    dsp_process_phase(&dat, vol, cur, coef);

    float32_t expected_rms = 1.0f / sqrtf(2.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.005f)), (UNITY_FLOAT)((expected_rms)), (UNITY_FLOAT)((dat.rms_voltage)), (
   ((void *)0)
   ), (UNITY_UINT)(112));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.005f)), (UNITY_FLOAT)((expected_rms)), (UNITY_FLOAT)((dat.rms_current)), (
   ((void *)0)
   ), (UNITY_UINT)(113));
}

void test_dsp_phase_unity_pf_power(void)
{
    float32_t vol[128U], cur[128U];
    gen_sine(vol, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);
    gen_sine(cur, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dsp_process_phase(&dat, vol, cur, unity_coef());

    float32_t expected_rms = 1.0f / sqrtf(2.0f);
    float32_t expected_app = expected_rms * expected_rms;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((expected_app)), (UNITY_FLOAT)((dat.act_pwr)), (
   ((void *)0)
   ), (UNITY_UINT)(128));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((expected_app)), (UNITY_FLOAT)((dat.app_pwr)), (
   ((void *)0)
   ), (UNITY_UINT)(129));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((dat.pf)), (
   ((void *)0)
   ), (UNITY_UINT)(130));
}

void test_dsp_phase_60deg_pf(void)
{
    float32_t vol[128U], cur[128U];
    gen_sine(vol, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);
    gen_sine(cur, 128U, 1.0f, 50.0f, 6400.0f, 60.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));

    dat.angle.voltage = 0.0f;
    dat.angle.current = 60.0f;

    dsp_process_phase(&dat, vol, cur, unity_coef());

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((0.5f)), (UNITY_FLOAT)((dat.pf)), (
   ((void *)0)
   ), (UNITY_UINT)(150));
}

void test_dsp_phase_90deg_zero_active_power(void)
{
    float32_t vol[128U], cur[128U];
    gen_sine(vol, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);
    gen_sine(cur, 128U, 1.0f, 50.0f, 6400.0f, 90.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dat.angle.voltage = 0.0f;
    dat.angle.current = 90.0f;

    dsp_process_phase(&dat, vol, cur, unity_coef());

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((dat.act_pwr)), (
   ((void *)0)
   ), (UNITY_UINT)(169));
}

void test_dsp_phase_coef_scales_rms(void)
{
    float32_t vol[128U], cur[128U];
    gen_sine(vol, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);
    gen_sine(cur, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    struct dsp_phase_coef_s coef = unity_coef();
    coef.v_coef = 2.0f;
    coef.i_coef = 3.0f;

    dsp_process_phase(&dat, vol, cur, coef);

    float32_t base_rms = 1.0f / sqrtf(2.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.005f)), (UNITY_FLOAT)((base_rms * 2.0f)), (UNITY_FLOAT)((dat.rms_voltage)), (
   ((void *)0)
   ), (UNITY_UINT)(190));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.005f)), (UNITY_FLOAT)((base_rms * 3.0f)), (UNITY_FLOAT)((dat.rms_current)), (
   ((void *)0)
   ), (UNITY_UINT)(191));
}

void test_dsp_phase_act_pwr_never_exceeds_app_pwr(void)
{
    float32_t vol[128U], cur[128U];

    gen_sine(vol, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);
    gen_sine(cur, 128U, 1.0f, 50.0f, 6400.0f, 0.0f);

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dsp_process_phase(&dat, vol, cur, unity_coef());

    do { if ((dat.act_pwr <= dat.app_pwr + 1e-4f))
{ } else { UnityFail( ((("act_pwr exceeded app_pwr"))), (UNITY_UINT)((208))); } } while (0)
}

void test_dsp_phase_zero_input(void)
{
    float32_t vol[128U], cur[128U];
    memset(vol, 0, sizeof(vol));
    memset(cur, 0, sizeof(cur));

    struct phase_data_s dat;
    memset(&dat, 0, sizeof(dat));
    dsp_process_phase(&dat, vol, cur, unity_coef());

    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((dat.rms_voltage)), (
   ((void *)0)
   ), (UNITY_UINT)(225));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((dat.rms_current)), (
   ((void *)0)
   ), (UNITY_UINT)(226));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((dat.act_pwr)), (
   ((void *)0)
   ), (UNITY_UINT)(227));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((dat.app_pwr)), (
   ((void *)0)
   ), (UNITY_UINT)(228));
}
void test_dsp_vol_line_balanced_3phase(void)
{
    float32_t va[128U], vb[128U], vc[128U];
    gen_3phase(va, vb, vc, 128U, 1.0f, 50.0f, 6400.0f);

    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    struct dsp_coef_s coef;
    memset(&coef, 0, sizeof(coef));
    coef.vll.ab_gain = 1.0f;
    coef.vll.bc_gain = 1.0f;
    coef.vll.ca_gain = 1.0f;

    dsp_process_vol_line(&mdat, &coef, va, vb, vc, 128U);

    float32_t expected = sqrtf(3.0f) * 1.0f / sqrtf(2.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mdat.vol_line.ab)), (
   ((void *)0)
   ), (UNITY_UINT)(258));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mdat.vol_line.bc)), (
   ((void *)0)
   ), (UNITY_UINT)(259));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mdat.vol_line.ca)), (
   ((void *)0)
   ), (UNITY_UINT)(260));
}

void test_dsp_vol_line_gain_applied(void)
{
    float32_t va[128U], vb[128U], vc[128U];
    gen_3phase(va, vb, vc, 128U, 1.0f, 50.0f, 6400.0f);

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

    dsp_process_vol_line(&mdat1, &coef1, va, vb, vc, 128U);
    dsp_process_vol_line(&mdat2, &coef2, va, vb, vc, 128U);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((mdat1.vol_line.ab * 2.0f)), (UNITY_FLOAT)((mdat2.vol_line.ab)), (
   ((void *)0)
   ), (UNITY_UINT)(288))
}

void test_dsp_vol_line_zero_input(void)
{
    float32_t va[128U], vb[128U], vc[128U];
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

    dsp_process_vol_line(&mdat, &coef, va, vb, vc, 128U);

    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mdat.vol_line.ab)), (
   ((void *)0)
   ), (UNITY_UINT)(312));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mdat.vol_line.bc)), (
   ((void *)0)
   ), (UNITY_UINT)(313));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mdat.vol_line.ca)), (
   ((void *)0)
   ), (UNITY_UINT)(314));
}

void test_dsp_fre_1p_updates_frequency(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    float32_t buf[128U * 100];
    for (uint32_t i = 0; i < 128U * 100; i++)
        buf[i] = sinf((2.0f * (float32_t)
                     3.14159265358979323846
                     ) * 50.0f * (float32_t)i / 6400.0f);

    dsp_process_fre_1_phase(&pll, &mdat, buf, 128U * 100);

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((mdat.frequency)), (
   ((void *)0)
   ), (UNITY_UINT)(335));
}

void test_dsp_fre_3p_updates_frequency(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    uint32_t total = 128U * 100;
    float32_t va[128U * 100], vb[128U * 100], vc[128U * 100];
    gen_3phase(va, vb, vc, total, 1.0f, 50.0f, 6400.0f);

    dsp_process_fre_3_phase(&pll, &mdat, va, vb, vc, total);

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((mdat.frequency)), (
   ((void *)0)
   ), (UNITY_UINT)(352));
}

void test_dsp_fre_1p_zero_buf_no_crash(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    struct meter_data_s mdat;
    memset(&mdat, 0, sizeof(mdat));

    float32_t buf[128U];
    memset(buf, 0, sizeof(buf));
    dsp_process_fre_1_phase(&pll, &mdat, buf, 128U);
    longjmp(Unity.AbortFrame, 1);
}
void test_dsp_thd_pure_sine_near_zero(void)
{
    float32_t data[(128U * 8)];
    float32_t fft_buf[(128U * 8)];
    float32_t mag_buf[(128U * 8) / 2];
    float32_t angle, thd;

    gen_sine(data, (128U * 8), 1.0f, 50.0f, 6400.0f, 0.0f);

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf, (128U * 8), &angle, &thd);

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((thd)), (("Pure sine THD should be near 0%")), (UNITY_UINT)(389))
}

void test_dsp_thd_with_3rd_harmonic(void)
{
    float32_t data[(128U * 8)];
    float32_t fft_buf[(128U * 8)];
    float32_t mag_buf[(128U * 8) / 2];
    float32_t angle, thd;

    float32_t harmonic_amp = 0.20f;
    for (uint32_t i = 0; i < (128U * 8); i++)
{
        data[i] = 1.0f * sinf((2.0f * (float32_t)
                           3.14159265358979323846
                           ) * 50.0f * (float32_t)i / 6400.0f)
                + harmonic_amp * 1.0f * sinf((2.0f * (float32_t)
                                          3.14159265358979323846
                                          ) * 3.0f * 50.0f * (float32_t)i / 6400.0f);
    }

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf, (128U * 8), &angle, &thd);

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((20.0f)), (UNITY_FLOAT)((thd)), (("THD with 20% 3rd harmonic should be ~20%")), (UNITY_UINT)(415))
}

void test_dsp_thd_with_3rd_and_5th_harmonic(void)
{
    float32_t data[(128U * 8)];
    float32_t fft_buf[(128U * 8)];
    float32_t mag_buf[(128U * 8) / 2];
    float32_t angle, thd;

    for (uint32_t i = 0; i < (128U * 8); i++)
{
        data[i] = 1.0f * sinf((2.0f * (float32_t)
                           3.14159265358979323846
                           ) * 50.0f * (float32_t)i / 6400.0f)
                + 0.20f * 1.0f * sinf((2.0f * (float32_t)
                                   3.14159265358979323846
                                   ) * 3.0f * 50.0f * (float32_t)i / 6400.0f)
                + 0.10f * 1.0f * sinf((2.0f * (float32_t)
                                   3.14159265358979323846
                                   ) * 5.0f * 50.0f * (float32_t)i / 6400.0f);
    }

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf, (128U * 8), &angle, &thd);

    float32_t expected = sqrtf(0.20f*0.20f + 0.10f*0.10f) * 100.0f;
    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((thd)), (("THD with 3rd+5th harmonic mismatch")), (UNITY_UINT)(442))
}

void test_dsp_thd_short_buffer_no_change(void)
{
    float32_t data[(128U * 8)];
    float32_t fft_buf[(128U * 8)];
    float32_t mag_buf[(128U * 8) / 2];
    float32_t angle = 0.0f;
    float32_t thd = 99.0f;

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));

    dsp_process_thd(&pdat, data, fft_buf, mag_buf,
                    (128U * 8) - 1,
                    &angle, &thd);

    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((99.0f)), (UNITY_FLOAT)((thd)), (
   ((void *)0)
   ), (UNITY_UINT)(465));
}

void test_dsp_thd_angle_cosine_input(void)
{
    float32_t data[(128U * 8)];
    float32_t fft_buf[(128U * 8)];
    float32_t mag_buf[(128U * 8) / 2];
    float32_t angle = 0.0f, thd = 0.0f;

    gen_sine(data, (128U * 8), 1.0f, 50.0f, 6400.0f, 90.0f);

    struct phase_data_s pdat;
    memset(&pdat, 0, sizeof(pdat));
    dsp_process_thd(&pdat, data, fft_buf, mag_buf, (128U * 8), &angle, &thd);

    do { if ((!
   __builtin_isnan (
   angle
   )
   && !
   __builtin_isinf_sign (
   angle
   )
   ))
{ } else { UnityFail( ((("angle should be finite"))), (UNITY_UINT)((487))); } } while (0)

    do { if ((angle >= -(float32_t)
   3.14159265358979323846
   && angle <= (float32_t)
   3.14159265358979323846
   ))
{ } else { UnityFail( ((("angle out of [-pi, pi]"))), (UNITY_UINT)((489))); } } while (0)
}