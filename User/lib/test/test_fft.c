#include "unity.h"
#include "arm_math.h"
#include <math.h>

#define FFT_SIZE 1024
#define SAMPLING_FREQ 1000.0f
#define TARGET_FREQ 50.0f // Giả sử đo dòng điện 50Hz

static arm_rfft_fast_instance_f32 fft_handler;
static float32_t input_buffer[FFT_SIZE];
static float32_t output_buffer[FFT_SIZE];
static float32_t magnitude_buffer[FFT_SIZE / 2];

void setUp(void) {
    // Khởi tạo instance FFT
    arm_status status = arm_rfft_fast_init_f32(&fft_handler, FFT_SIZE);
    TEST_ASSERT_EQUAL(ARM_MATH_SUCCESS, status);
}

void tearDown(void) {
}

void test_fft_should_detect_correct_frequency(void) {
    // 1. Tạo tín hiệu Sine 50Hz
    for (int i = 0; i < FFT_SIZE; i++) {
        input_buffer[i] = sinf(2.0f * PI * TARGET_FREQ * (float32_t)i / SAMPLING_FREQ);
    }

    // 2. Thực hiện Real FFT
    // Lưu ý: Output của RFFT có định dạng phức (complex), kích thước vẫn là FFT_SIZE
    arm_rfft_fast_f32(&fft_handler, input_buffer, output_buffer, 0);

    // 3. Tính toán biên độ (Magnitude)
    // arm_cmplx_mag_f32 tính căn bậc hai tổng bình phương phần thực và ảo
    arm_cmplx_mag_f32(output_buffer, magnitude_buffer, FFT_SIZE / 2);

    // 4. Tìm vị trí đỉnh (Peak)
    float32_t max_val;
    uint32_t max_index;
    arm_max_f32(magnitude_buffer, FFT_SIZE / 2, &max_val, &max_index);

    // 5. Kiểm tra tần số tìm được
    // Tần số (Hz) = index * (Sampling_Rate / FFT_Size)
    float32_t detected_freq = (float32_t)max_index * (SAMPLING_FREQ / FFT_SIZE);

    // Kiểm tra sai số trong khoảng 1Hz (do độ phân giải của FFT là 1000/1024 ≈ 0.97Hz)
    TEST_ASSERT_FLOAT_WITHIN(1.0f, TARGET_FREQ, detected_freq);
}