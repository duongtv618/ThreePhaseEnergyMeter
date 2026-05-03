// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/lib/inc/pll.h"
#include "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h"

void mock_timer_update_arr(uint32_t newARR)
{ (void)newARR; }

static inline float32_t sine_1p(uint32_t i, float32_t f, float32_t fs)
{
    return sinf((2.0f * (float32_t)
               3.14159265358979323846
               ) * f * (float32_t)i / fs);
}

static inline void sine_3p(uint32_t i, float32_t f, float32_t fs,
                            float32_t *va, float32_t *vb, float32_t *vc)
{
    float32_t phi = (2.0f * (float32_t)
                   3.14159265358979323846
                   ) * f * (float32_t)i / fs;
    *va = sinf(phi);
    *vb = sinf(phi - (2.0f * (float32_t)
                    3.14159265358979323846
                    ) / 3.0f);
    *vc = sinf(phi - 2.0f * (2.0f * (float32_t)
                           3.14159265358979323846
                           ) / 3.0f);
}

static uint32_t run_1p(struct pll_s *pll, float32_t f, uint32_t n_cycles,
                        uint32_t offset)
{
    uint32_t spc = (uint32_t)(6400.0f / f);
    uint32_t total = n_cycles * spc;
    for (uint32_t i = 0; i < total; i++)
        pll_update_1p(pll, sine_1p(offset + i, f, 6400.0f));
    return offset + total;
}

static uint32_t run_3p(struct pll_s *pll, float32_t f, uint32_t n_cycles,
                        uint32_t offset)
{
    uint32_t spc = (uint32_t)(6400.0f / f);
    uint32_t total = n_cycles * spc;
    for (uint32_t i = 0; i < total; i++)
{
        float32_t va, vb, vc;
        sine_3p(offset + i, f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(pll, va, vb, vc);
    }
    return offset + total;
}

void setUp(void)
{}
void tearDown(void)
{}
void test_edge_1p_zero_input_theta_stays_valid(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t samples = (uint32_t)(100.0f * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        pll_update_1p(&pll, 0.0f);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((("theta out of [0,360) on zero input"))), (UNITY_UINT)((103))); } } while (0)

    }
}

void test_edge_3p_zero_input_theta_stays_valid(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t samples = (uint32_t)(100.0f * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        pll_update_3p(&pll, 0.0f, 0.0f, 0.0f);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((("theta out of [0,360) on zero input"))), (UNITY_UINT)((116))); } } while (0)

    }
}

void test_edge_1p_zero_input_clears_lock(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    run_1p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (("PLL should be locked before test")), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_UINT32)

    uint32_t spc = (uint32_t)(6400.0f / 50.0f);
    for (uint32_t i = 0; i < spc; i++)
        pll_update_1p(&pll, 0.0f);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(139), UNITY_DISPLAY_STYLE_UINT32);
}

void test_edge_3p_zero_input_clears_lock(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);
    run_3p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (("PLL should be locked before test")), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_UINT32)

    uint32_t spc = (uint32_t)(6400.0f / 50.0f);
    for (uint32_t i = 0; i < spc; i++)
{
        pll_update_3p(&pll, 0.0f, 0.0f, 0.0f);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((156))); } } while (0);
    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(159), UNITY_DISPLAY_STYLE_UINT32);
}
void test_edge_1p_large_amplitude_theta_valid(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t samples = (uint32_t)(50.0f * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        float32_t vin = 2.0f * sine_1p(i, 50.0f, 6400.0f);
        pll_update_1p(&pll, vin);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((179))); } } while (0);
    }

    do { if ((pll.fre > 10.0f && pll.fre < 200.0f))
{ } else { UnityFail( ((("fre diverged on large amplitude input"))), (UNITY_UINT)((182))); } } while (0)
}

void test_edge_3p_large_amplitude_theta_valid(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t samples = (uint32_t)(50.0f * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        float32_t va, vb, vc;
        sine_3p(i, 50.0f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, 2.0f * va, 2.0f * vb, 2.0f * vc);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((196))); } } while (0);
    }
    do { if ((pll.fre > 10.0f && pll.fre < 200.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((198))); } } while (0);
}
void test_edge_3p_amplitude_drop_stays_locked(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t offset = run_3p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (("Should be locked at full amplitude")), (UNITY_UINT)(216), UNITY_DISPLAY_STYLE_UINT32)

    uint32_t spc = (uint32_t)(6400.0f / 50.0f);
    for (uint32_t i = 0; i < 10 * spc; i++)
{
        float32_t va, vb, vc;
        sine_3p(offset + i, 50.0f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, 0.5f * va, 0.5f * vb, 0.5f * vc);
    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (("PLL should stay locked after amplitude drop")), (UNITY_UINT)(227), UNITY_DISPLAY_STYLE_UINT32)

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(229));
}
void test_edge_1p_signal_loss_and_recovery(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t offset = run_1p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(246), UNITY_DISPLAY_STYLE_UINT32);

    uint32_t spc = (uint32_t)(6400.0f / 50.0f);
    for (uint32_t i = 0; i < 10 * spc; i++)
        pll_update_1p(&pll, 0.0f);
    offset += 10 * spc;

    do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((256))); } } while (0);

    uint32_t max_samples = (uint32_t)(300 * 6400.0f / 50.0f);
    uint8_t relocked = 0;
    for (uint32_t i = 0; i < max_samples; i++)
{
        pll_update_1p(&pll, sine_1p(offset + i, 50.0f, 6400.0f));
        if (pll_is_locked(&pll))
{ relocked = 1; break; }
    }
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((relocked)), (("1p PLL did not re-lock after signal recovery")), (UNITY_UINT)(265), UNITY_DISPLAY_STYLE_UINT32)
}

void test_edge_3p_signal_loss_and_recovery(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t offset = run_3p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(278), UNITY_DISPLAY_STYLE_UINT32);

    uint32_t spc = (uint32_t)(6400.0f / 50.0f);
    for (uint32_t i = 0; i < 10 * spc; i++)
        pll_update_3p(&pll, 0.0f, 0.0f, 0.0f);
    offset += 10 * spc;

    do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((287))); } } while (0);
    UnityAssertFloatsWithin((UNITY_FLOAT)((5.0f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(288));
}
void test_edge_3p_phase_jump_180_recovers(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t offset = run_3p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(305), UNITY_DISPLAY_STYLE_UINT32);

    uint32_t max_samples = (uint32_t)(300 * 6400.0f / 50.0f);
    uint8_t relocked = 0;
    for (uint32_t i = 0; i < max_samples; i++)
{
        float32_t va, vb, vc;
        sine_3p(offset + i, 50.0f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, -va, -vb, -vc);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((314))); } } while (0);
        if (pll_is_locked(&pll))
{ relocked = 1; break; }
    }
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((relocked)), (("3p PLL did not recover from 180 phase jump")), (UNITY_UINT)(317), UNITY_DISPLAY_STYLE_UINT32)
}

void test_edge_1p_phase_jump_180_recovers(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t offset = run_1p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(327), UNITY_DISPLAY_STYLE_UINT32);

    uint32_t max_samples = (uint32_t)(300 * 6400.0f / 50.0f);
    uint8_t relocked = 0;
    for (uint32_t i = 0; i < max_samples; i++)
{
        pll_update_1p(&pll, -sine_1p(offset + i, 50.0f, 6400.0f));
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((333))); } } while (0);
        if (pll_is_locked(&pll))
{ relocked = 1; break; }
    }
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((relocked)), (("1p PLL did not recover from 180 phase jump")), (UNITY_UINT)(336), UNITY_DISPLAY_STYLE_UINT32)
}

void test_edge_3p_locks_at_45Hz(void)
{
    struct pll_s pll;
    float32_t f = 45.0f;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t max_samples = (uint32_t)(300 * 6400.0f / f);
    uint8_t locked = 0;
    for (uint32_t i = 0; i < max_samples; i++)
{
        float32_t va, vb, vc;
        sine_3p(i, f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((356))); } } while (0);
        if (pll_is_locked(&pll))
{ locked = 1; break; }
    }
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((locked)), (("3p PLL did not lock at 45Hz")), (UNITY_UINT)(359), UNITY_DISPLAY_STYLE_UINT32);
    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((f)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(360));
}

void test_edge_3p_locks_at_65Hz(void)
{
    struct pll_s pll;
    float32_t f = 65.0f;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t max_samples = (uint32_t)(300 * 6400.0f / f);
    uint8_t locked = 0;
    for (uint32_t i = 0; i < max_samples; i++)
{
        float32_t va, vb, vc;
        sine_3p(i, f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((375))); } } while (0);
        if (pll_is_locked(&pll))
{ locked = 1; break; }
    }
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((locked)), (("3p PLL did not lock at 65Hz")), (UNITY_UINT)(378), UNITY_DISPLAY_STYLE_UINT32);
    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((f)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(379));
}
void test_edge_update_fs_arr_clamped_at_50Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    pll.fre = 50.0f;

    float32_t fs_before = pll.fs;
    pll_update_fs(&pll);
    float32_t fs_after = pll.fs;

    float32_t f_new = fs_after / (float32_t)(128);
    do { if ((f_new >= 44.0f && f_new <= 66.0f))
{ } else { UnityFail( ((("pll_update_fs produced fs outside 45-65Hz range"))), (UNITY_UINT)((401))); } } while (0)

    (void)fs_before;
}

void test_edge_update_fs_clamps_below_45Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    pll.fre = 30.0f;
    pll_update_fs(&pll);

    float32_t f_new = pll.fs / 128.0f;
    do { if ((f_new >= 44.0f))
{ } else { UnityFail( ((("pll_update_fs did not clamp frequency below 45Hz"))), (UNITY_UINT)((418))); } } while (0)
}

void test_edge_update_fs_clamps_above_65Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    pll.fre = 80.0f;
    pll_update_fs(&pll);

    float32_t f_new = pll.fs / 128.0f;
    do { if ((f_new <= 66.0f))
{ } else { UnityFail( ((("pll_update_fs did not clamp frequency above 65Hz"))), (UNITY_UINT)((433))); } } while (0)
}
void test_edge_1p_single_update_after_init(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    pll_update_1p(&pll, 0.5f);

    do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((450))); } } while (0);
    do { if (!(
   __builtin_isnan (
   pll.fre
   )
   ))
{ } else { UnityFail( ((("fre is NaN after single update"))), (UNITY_UINT)((451))); } } while (0);
    do { if (!(
   __builtin_isinf_sign (
   pll.fre
   )
   ))
{ } else { UnityFail( ((("fre is Inf after single update"))), (UNITY_UINT)((452))); } } while (0);
}

void test_edge_3p_single_update_after_init(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);
    pll_update_3p(&pll, 0.5f, -0.25f, -0.25f);

    do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((461))); } } while (0);
    do { if (!(
   __builtin_isnan (
   pll.fre
   )
   ))
{ } else { UnityFail( ((("fre is NaN after single update"))), (UNITY_UINT)((462))); } } while (0);
    do { if (!(
   __builtin_isinf_sign (
   pll.fre
   )
   ))
{ } else { UnityFail( ((("fre is Inf after single update"))), (UNITY_UINT)((463))); } } while (0);
}
void test_edge_1p_reinit_while_running_resets_state(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    run_1p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(478), UNITY_DISPLAY_STYLE_UINT32);

    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((270.0f)), (UNITY_FLOAT)((pll.theta)), (
   ((void *)0)
   ), (UNITY_UINT)(483));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((pll.SOGI.alpha)), (
   ((void *)0)
   ), (UNITY_UINT)(484));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((pll.SOGI.beta)), (
   ((void *)0)
   ), (UNITY_UINT)(485));
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(486), UNITY_DISPLAY_STYLE_UINT32);
}

void test_edge_3p_reinit_while_running_resets_state(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);
    run_3p(&pll, 50.0f, 50, 0);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(494), UNITY_DISPLAY_STYLE_UINT32);

    pll_init_3p(&pll, 50.0f, 6400.0f);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((270.0f)), (UNITY_FLOAT)((pll.theta)), (
   ((void *)0)
   ), (UNITY_UINT)(498));
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(499), UNITY_DISPLAY_STYLE_UINT32);
}