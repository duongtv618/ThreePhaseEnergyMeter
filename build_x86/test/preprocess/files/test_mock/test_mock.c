// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "User/mock/inc/mock_hw_stub.h"
#include "build_x86/vendor/unity/src/unity.h"
#include "User/mock/inc/mock.h"
#include "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h"

void setUp(void)
{}
void tearDown(void)
{}
void test_mock_sin_gen_output_within_adc_range(void)
{
    uint16_t buf[128U];
    memset(buf, 0xFF, sizeof(buf));

    mock_sin_gen(buf, 128U, 1, 50.0f, 6400.0f, 0.0f);

    for (uint32_t i = 0; i < 128U; i++)
{
        do { if ((buf[i] <= (uint16_t)4096.0f))
{ } else { UnityFail( ((("Sample above ADC_MAX"))), (UNITY_UINT)((69))); } } while (0)

    }
}

void test_mock_sin_gen_dc_offset_near_midpoint(void)
{
    uint16_t buf[128U];
    mock_sin_gen(buf, 128U, 1, 50.0f, 6400.0f, 0.0f);

    float32_t sum = 0.0f;
    for (uint32_t i = 0; i < 128U; i++) sum += buf[i];
    float32_t mean = sum / (float32_t)128U;

    UnityAssertFloatsWithin((UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((2048.0f)), (UNITY_FLOAT)((mean)), (
   ((void *)0)
   ), (UNITY_UINT)(87));
}

void test_mock_sin_gen_jump_space_skips_indices(void)
{
    uint16_t buf[128U * 2];
    memset(buf, 0xAB, sizeof(buf));

    mock_sin_gen(buf, 128U * 2, 2, 50.0f, 6400.0f, 0.0f);

    for (uint32_t i = 1; i < 128U * 2; i += 2)
{
        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xABAB)), (UNITY_INT)(UNITY_INT16)((buf[i])), (("Odd index should not be written")), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_HEX16)

    }
}

void test_mock_sin_gen_phase_shift_180_inverts_wave(void)
{
    uint16_t buf0[128U], buf180[128U];
    mock_sin_gen(buf0, 128U, 1, 50.0f, 6400.0f, 0.0f);
    mock_sin_gen(buf180, 128U, 1, 50.0f, 6400.0f, 180.0f);

    for (uint32_t i = 0; i < 128U; i++)
{
        int32_t sum = (int32_t)buf0[i] + (int32_t)buf180[i];
        UnityAssertNumbersWithin((UNITY_UINT32)((20)), (UNITY_INT)(UNITY_INT32) (((int32_t)(2.0f * 2048.0f))), (UNITY_INT)(UNITY_INT32) ((sum)), (("180 shift should mirror around midpoint")), (UNITY_UINT)(118), UNITY_DISPLAY_STYLE_INT32)

    }
}

void test_mock_sin_gen_peak_amplitude_correct(void)
{
    uint16_t buf[128U];
    mock_sin_gen(buf, 128U, 1, 50.0f, 6400.0f, 0.0f);

    uint16_t peak = 0;
    for (uint32_t i = 0; i < 128U; i++)
        if (buf[i] > peak) peak = buf[i];

    float32_t expected_peak = 2048.0f + 2048.0f * 0.88f;

    UnityAssertFloatsWithin((UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((expected_peak)), (UNITY_FLOAT)(((float32_t)peak)), (
   ((void *)0)
   ), (UNITY_UINT)(137));
}

void test_mock_sin_gen_trough_amplitude_correct(void)
{
    uint16_t buf[128U];
    mock_sin_gen(buf, 128U, 1, 50.0f, 6400.0f, 0.0f);

    uint16_t trough = 0xFFFF;
    for (uint32_t i = 0; i < 128U; i++)
        if (buf[i] < trough) trough = buf[i];

    float32_t expected_trough = 2048.0f - 2048.0f * 0.88f;
    UnityAssertFloatsWithin((UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((expected_trough)), (UNITY_FLOAT)(((float32_t)trough)), (
   ((void *)0)
   ), (UNITY_UINT)(153));
}

void test_mock_sin_gen_different_frequencies_differ(void)
{
    uint16_t buf50[128U], buf60[128U];
    mock_sin_gen(buf50, 128U, 1, 50.0f, 6400.0f, 0.0f);
    mock_sin_gen(buf60, 128U, 1, 60.0f, 6400.0f, 0.0f);

    uint32_t diff_count = 0;
    for (uint32_t i = 0; i < 128U; i++)
        if (buf50[i] != buf60[i]) diff_count++;

    do { if ((diff_count > 128U / 2))
{ } else { UnityFail( ((("50Hz and 60Hz buffers should differ significantly"))), (UNITY_UINT)((169))); } } while (0)
}
void test_mock_3p_all_samples_within_adc_range(void)
{
    uint32_t n_samples = 128U;
    uint16_t buf[128U * (3U * 2U)];
    memset(buf, 0, sizeof(buf));

    mock_sin_gen_ui_3_p(buf, 128U * (3U * 2U), 50.0f, 6400.0f, (-5.0f));

    for (uint32_t i = 0; i < 128U * (3U * 2U); i++)
{
        do { if ((buf[i] <= (uint16_t)4096.0f))
{ } else { UnityFail( ((("3p sample above ADC_MAX"))), (UNITY_UINT)((190))); } } while (0)

    }
}

void test_mock_3p_dc_offset_all_channels(void)
{
    uint16_t buf[128U * (3U * 2U)];
    mock_sin_gen_ui_3_p(buf, 128U * (3U * 2U), 50.0f, 6400.0f, 0.0f);

    for (uint32_t ch = 0; ch < (3U * 2U); ch++)
{
        float32_t sum = 0.0f;
        for (uint32_t s = 0; s < 128U; s++)
            sum += buf[s * (3U * 2U) + ch];
        float32_t mean = sum / (float32_t)128U;
        UnityAssertFloatsWithin((UNITY_FLOAT)((100.0f)), (UNITY_FLOAT)((2048.0f)), (UNITY_FLOAT)((mean)), (("Channel DC offset too far from midpoint")), (UNITY_UINT)(209))

    }
}

void test_mock_3p_voltage_phases_120_apart(void)
{
    uint16_t buf[128U * (3U * 2U)];

    mock_sin_gen_ui_3_p(buf, 128U * (3U * 2U), 50.0f, 6400.0f, 0.0f);

    uint32_t peak_idx[3] = {0, 0, 0};
    uint16_t peak_val[3] = {0, 0, 0};
    uint32_t ch_map[3] = {0, 2, 4};

    for (uint32_t ph = 0; ph < 3; ph++)
{
        for (uint32_t s = 0; s < 128U; s++)
{
            uint16_t v = buf[s * (3U * 2U) + ch_map[ph]];
            if (v > peak_val[ph])
{ peak_val[ph] = v; peak_idx[ph] = s; }
        }
    }

    uint32_t spacing_ab = (peak_idx[1] + 128U - peak_idx[0]) % 128U;
    uint32_t spacing_bc = (peak_idx[2] + 128U - peak_idx[1]) % 128U;

    UnityAssertNumbersWithin((UNITY_UINT32)((5)), (UNITY_INT)(UNITY_UINT)(UNITY_UINT32)((128U / 3)), (UNITY_INT)(UNITY_UINT)(UNITY_UINT32)((spacing_ab)), (("Va-Vb phase spacing not ~120")), (UNITY_UINT)(240), UNITY_DISPLAY_STYLE_UINT32)

    UnityAssertNumbersWithin((UNITY_UINT32)((5)), (UNITY_INT)(UNITY_UINT)(UNITY_UINT32)((128U / 3)), (UNITY_INT)(UNITY_UINT)(UNITY_UINT32)((spacing_bc)), (("Vb-Vc phase spacing not ~120")), (UNITY_UINT)(242), UNITY_DISPLAY_STYLE_UINT32)
}

void test_mock_3p_current_phase_shift_applied(void)
{
    uint16_t buf_0[128U * (3U * 2U)];
    uint16_t buf_shift[128U * (3U * 2U)];

    mock_sin_gen_ui_3_p(buf_0, 128U * (3U * 2U), 50.0f, 6400.0f, 0.0f);
    mock_sin_gen_ui_3_p(buf_shift, 128U * (3U * 2U), 50.0f, 6400.0f, (-5.0f));

    uint32_t ia_diff = 0;
    for (uint32_t s = 0; s < 128U; s++)
        if (buf_0[s * (3U * 2U) + 1] != buf_shift[s * (3U * 2U) + 1]) ia_diff++;

    do { if ((ia_diff > 0))
{ } else { UnityFail( ((("Current channel did not change with i_phase_shift"))), (UNITY_UINT)((265))); } } while (0)
}

void test_mock_3p_zero_length_no_crash(void)
{
    uint16_t buf[10];
    memset(buf, 0xAB, sizeof(buf));
    mock_sin_gen_ui_3_p(buf, 0, 50.0f, 6400.0f, 0.0f);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xABAB)), (UNITY_INT)(UNITY_INT16)((buf[0])), (
   ((void *)0)
   ), (UNITY_UINT)(278), UNITY_DISPLAY_STYLE_HEX16);
}
void test_mock_DMA_init_registers_buffer(void)
{
    uint16_t buf_a[128U * (3U * 2U)];
    uint16_t buf_b[128U * (3U * 2U)];
    memset(buf_a, 0xAA, sizeof(buf_a));
    memset(buf_b, 0xBB, sizeof(buf_b));

    mock_DMA_init(buf_a, 128U * (3U * 2U), 1, 1);

    mock_sin_gen_ui_3_p(buf_a, 128U * (3U * 2U), 50.0f, 6400.0f, 0.0f);

    uint32_t changed = 0;
    for (uint32_t i = 0; i < 128U * (3U * 2U); i++)
        if (buf_a[i] != 0xAAAA) changed++;
    do { if ((changed > 0))
{ } else { UnityFail( ((("buf_a should have been written"))), (UNITY_UINT)((306))); } } while (0);

    for (uint32_t i = 0; i < 128U * (3U * 2U); i++)
        UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xBBBB)), (UNITY_INT)(UNITY_INT16)((buf_b[i])), (
       ((void *)0)
       ), (UNITY_UINT)(310), UNITY_DISPLAY_STYLE_HEX16);
}
void test_mock_timer_update_arr_no_crash(void)
{
    uint32_t arr_50hz = 100000000UL / (uint32_t)6400.0f;
    mock_timer_update_arr(arr_50hz);

    uint16_t buf[128U * (3U * 2U)];
    mock_sin_gen_ui_3_p(buf, 128U * (3U * 2U), 50.0f, 6400.0f, 0.0f);

    for (uint32_t i = 0; i < 128U * (3U * 2U); i++)
        do { if ((buf[i] <= (uint16_t)4096.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((334))); } } while (0);
}

void test_mock_timer_update_arr_changes_internal_fs(void)
{
    uint32_t arr_45 = 100000000UL / (128 * 45);
    uint32_t arr_65 = 100000000UL / (128 * 65);

    mock_timer_update_arr(arr_45);
    mock_timer_update_arr(arr_65);

    uint16_t buf[128U * (3U * 2U)];
    mock_sin_gen_ui_3_p(buf, 128U * (3U * 2U), 50.0f, 6400.0f, 0.0f);
    for (uint32_t i = 0; i < 128U * (3U * 2U); i++)
        do { if ((buf[i] <= (uint16_t)4096.0f))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((350))); } } while (0);
}

void test_mock_change_frequency_no_crash(void)
{
    mock_change_frequency(45.0f, 0.1f);
    mock_change_frequency(65.0f, 0.5f);
    mock_change_frequency(50.0f, 1.0f);

    longjmp(Unity.AbortFrame, 1);
}

void test_mock_change_frequency_zero_step(void)
{
    mock_change_frequency(50.0f, 0.0f);
    longjmp(Unity.AbortFrame, 1);
}