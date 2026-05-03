// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/lib/inc/pll.h"
#include "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h"

void mock_timer_update_arr(uint32_t newARR)
{ (void)newARR; }

static inline float32_t sine_sample(uint32_t i, float32_t f, float32_t fs)
{
    return 1.0f * sinf((2.0f * (float32_t)
                           3.14159265358979323846
                           ) * f * (float32_t)i / fs);
}

static inline void three_phase_samples(uint32_t i, float32_t f, float32_t fs,
                                        float32_t *va, float32_t *vb, float32_t *vc)
{
    float32_t phi = (2.0f * (float32_t)
                   3.14159265358979323846
                   ) * f * (float32_t)i / fs;
    *va = 1.0f * sinf(phi);
    *vb = 1.0f * sinf(phi - (2.0f * (float32_t)
                                3.14159265358979323846
                                ) / 3.0f);
    *vc = 1.0f * sinf(phi - 2.0f * (2.0f * (float32_t)
                                       3.14159265358979323846
                                       ) / 3.0f);
}

void setUp(void)
{}
void tearDown(void)
{}

void test_pll_init_1p_sets_theta_to_270(void)
{
    struct pll_s pll;
    memset(&pll, 0xAB, sizeof(pll));
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((270.0f)), (UNITY_FLOAT)((pll.theta)), (
   ((void *)0)
   ), (UNITY_UINT)(72));
}

void test_pll_init_1p_sets_delta_theta(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    float32_t expected = 50.0f / 6400.0f * 360.0f;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((pll.delta_theta)), (
   ((void *)0)
   ), (UNITY_UINT)(81));
}

void test_pll_init_1p_stores_fs_and_f0(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((6400.0f)), (UNITY_FLOAT)((pll.fs)), (
   ((void *)0)
   ), (UNITY_UINT)(88));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.01f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((pll.f0)), (
   ((void *)0)
   ), (UNITY_UINT)(89));
}

void test_pll_init_1p_SOGI_cleared(void)
{
    struct pll_s pll;
    memset(&pll, 0xAB, sizeof(pll));
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((pll.SOGI.alpha)), (
   ((void *)0)
   ), (UNITY_UINT)(97));
    UnityAssertFloatsWithin((UNITY_FLOAT)((1e-6f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((pll.SOGI.beta)), (
   ((void *)0)
   ), (UNITY_UINT)(98));
}

void test_pll_init_3p_sets_theta_to_270(void)
{
    struct pll_s pll;
    memset(&pll, 0xAB, sizeof(pll));
    pll_init_3p(&pll, 50.0f, 6400.0f);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((270.0f)), (UNITY_FLOAT)((pll.theta)), (
   ((void *)0)
   ), (UNITY_UINT)(106));
}

void test_pll_init_3p_sets_delta_theta(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);
    float32_t expected = 360.0f * 50.0f / 6400.0f;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((pll.delta_theta)), (
   ((void *)0)
   ), (UNITY_UINT)(114));
}

void test_pll_is_locked_returns_0_before_lock(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_UINT32);
}

void test_pll_is_locked_returns_1_when_counter_at_threshold(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    pll.locked = (128 * 2);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(134), UNITY_DISPLAY_STYLE_UINT32);
}

void test_pll_is_locked_returns_0_when_counter_below_threshold(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);
    pll.locked = (128 * 2) - 1;
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (
   ((void *)0)
   ), (UNITY_UINT)(142), UNITY_DISPLAY_STYLE_UINT32);
}

void test_pll_update_1p_theta_stays_in_0_to_360(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t samples = (uint32_t)(10.0f * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        float32_t vin = sine_sample(i, 50.0f, 6400.0f);
        pll_update_1p(&pll, vin);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((("theta out of [0, 360)"))), (UNITY_UINT)((159))); } } while (0)

    }
}

void test_pll_update_3p_theta_stays_in_0_to_360(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t samples = (uint32_t)(10.0f * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        float32_t va, vb, vc;
        three_phase_samples(i, 50.0f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
        do { if ((pll.theta >= 0.0f && pll.theta < 360.0f))
{ } else { UnityFail( ((("theta out of [0, 360)"))), (UNITY_UINT)((174))); } } while (0)

    }
}

void test_pll_update_1p_frequency_estimate_within_2Hz(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t samples = (uint32_t)(200 * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        pll_update_1p(&pll, sine_sample(i, 50.0f, 6400.0f));
    }

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(194));
}

void test_pll_update_3p_frequency_estimate_within_2Hz(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t samples = (uint32_t)(200 * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < samples; i++)
{
        float32_t va, vb, vc;
        three_phase_samples(i, 50.0f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
    }

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(209));
}

void test_pll_update_1p_locks_within_max_cycles(void)
{
    struct pll_s pll;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t total_samples = (uint32_t)(200 * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < total_samples; i++)
{
        pll_update_1p(&pll, sine_sample(i, 50.0f, 6400.0f));
    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (("PLL did not lock within MAX_LOCK_CYCLES grid cycles")), (UNITY_UINT)(226), UNITY_DISPLAY_STYLE_UINT32)
}

void test_pll_update_3p_locks_within_max_cycles(void)
{
    struct pll_s pll;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t total_samples = (uint32_t)(200 * 6400.0f / 50.0f);
    for (uint32_t i = 0; i < total_samples; i++)
{
        float32_t va, vb, vc;
        three_phase_samples(i, 50.0f, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((pll_is_locked(&pll))), (("3P PLL did not lock within MAX_LOCK_CYCLES grid cycles")), (UNITY_UINT)(242), UNITY_DISPLAY_STYLE_UINT32)
}

void test_pll_update_1p_tracks_49Hz(void)
{
    struct pll_s pll;
    float32_t true_freq = 49.0f;
    pll_init_1p(&pll, 50.0f, 6400.0f, 100000000UL);

    uint32_t samples = (uint32_t)(200 * 6400.0f / true_freq);
    for (uint32_t i = 0; i < samples; i++)
{
        pll_update_1p(&pll, sine_sample(i, true_freq, 6400.0f));
    }

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((true_freq)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(262));
}

void test_pll_update_3p_tracks_51Hz(void)
{
    struct pll_s pll;
    float32_t true_freq = 51.0f;
    pll_init_3p(&pll, 50.0f, 6400.0f);

    uint32_t samples = (uint32_t)(200 * 6400.0f / true_freq);
    for (uint32_t i = 0; i < samples; i++)
{
        float32_t va, vb, vc;
        three_phase_samples(i, true_freq, 6400.0f, &va, &vb, &vc);
        pll_update_3p(&pll, va, vb, vc);
    }

    UnityAssertFloatsWithin((UNITY_FLOAT)((2.0f)), (UNITY_FLOAT)((true_freq)), (UNITY_FLOAT)((pll.fre)), (
   ((void *)0)
   ), (UNITY_UINT)(278));
}