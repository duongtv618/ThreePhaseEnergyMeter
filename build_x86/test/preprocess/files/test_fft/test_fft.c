// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h"

static arm_rfft_fast_instance_f32 fft_handler;
static float32_t input_buffer[1024];
static float32_t output_buffer[1024];
static float32_t magnitude_buffer[1024 / 2];

void setUp(void)
{
    arm_status status = arm_rfft_fast_init_f32(&fft_handler, 1024);
    UnityAssertEqualNumber((UNITY_INT)((ARM_MATH_SUCCESS)), (UNITY_INT)((status)), (
   ((void *)0)
   ), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_INT);
}

void tearDown(void)
{
}

void test_fft_should_detect_correct_frequency(void)
{
    for (int i = 0; i < 1024; i++)
{
        input_buffer[i] = sinf(2.0f * 3.14159265358979f * 50.0f * (float32_t)i / 1000.0f);
    }

    arm_rfft_fast_f32(&fft_handler, input_buffer, output_buffer, 0);

    arm_cmplx_mag_f32(output_buffer, magnitude_buffer, 1024 / 2);

    float32_t max_val;
    uint32_t max_index;
    arm_max_f32(magnitude_buffer, 1024 / 2, &max_val, &max_index);

    float32_t detected_freq = (float32_t)max_index * (1000.0f / 1024);

    UnityAssertFloatsWithin((UNITY_FLOAT)((1.0f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((detected_freq)), (
   ((void *)0)
   ), (UNITY_UINT)(47));
}