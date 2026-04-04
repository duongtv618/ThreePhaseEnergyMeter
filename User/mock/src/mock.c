/**
 * @file mock.c
 * @author your name (you@domain.com)
 * @brief Mock signal generation functions, simulate ADC data for testing DSP processing code without real ADC hardware.
 * @version 0.1
 * @date 2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "mock.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

static struct mock_dma_s
{
    mockSigCallback_t htCallback;
    mockSigCallback_t tcCallback;
    uint32_t signalPeriod;

    uint16_t *bufPointer;
    uint32_t length;
    enum
    {
        HT = 0u,
        TC = 1u
    } nextInt;
} mockDMAConfig;

static void _mockTask(void *pvParameters);
static StackType_t mock_task_stack[APP_DEFAULT_TASK_STACK_SIZE];
static StaticTask_t mock_task_buffer;

/**
 * @brief Generates mock sine wave data for ADC simulation
 *
 * @param buffer Destination buffer to store the generated sine wave data
 * @param length Length of the buffer (number of samples)
 * @param jumpSpace Space between samples in the buffer
 * @param period Period of the sine wave
 * @param phaseShift Phase shift of the sine wave in degrees
 */
void mockSinGen(uint16_t *buffer, uint32_t length, uint8_t jumpSpace, uint32_t period, float32_t phaseShift)
{
    for (uint32_t i = 0, pos = 0; i < length; i += jumpSpace, pos++)
    {
        float32_t bufferValue;
        /** ADC range is from 0 to 4095 so middle point is 2047 */
        #ifdef USE_HARMONIC_NOISE
        bufferValue = (2047u * arm_sin_f32(2.0f * PI * (float)pos / (float)period + phaseShift * PI / 180.0f) + 2047U) +
                    (2047u * HARMONIC_AMP_PERCENT / 100.0f * arm_sin_f32(2.0f * PI * HARMONIC_ * (float)pos / (float)period + phaseShift * PI / 180.0f));
        #else
        bufferValue = (2047u * arm_sin_f32(2.0f * PI * (float)pos / (float)period + phaseShift * PI / 180.0f) + 2047U);
        #endif
        #if USE_RANDOM_NOISE
        /** Add some random noise to the signal, noise range is from -2 to 2 */
        bufferValue = bufferValue - 2 + ((DWT->CYCCNT) % 4);
        #endif
        /** Truncate to 12-bit */
        buffer[i] = bufferValue > 4095.0f ? 4095u : bufferValue < 0.0f ? 0u : (uint16_t)bufferValue;
    }
}

/**
 * @brief Init FreeRTOS task for generating mock signal data, and the callback will
 * be called after each period of signal generation, so that we can update the
 * signal data for testing DSP processing code without real ADC data.
 *
 * @param periodMs Period in milliseconds
 * @param callback Callback function to be called after each period of signal generation, can be NULL if not needed
 */
void mockSignalGenInit(uint32_t periodMs, mockSigCallback_t htCallback, mockSigCallback_t tcCallback)
{
    if (htCallback)
    {
        mockDMAConfig.htCallback = htCallback;
    }

    if (tcCallback)
    {
        mockDMAConfig.tcCallback = tcCallback;
    }

    mockDMAConfig.signalPeriod = periodMs;

    xTaskCreateStatic(
        _mockTask,
        "MockSignalGen",
        APP_DEFAULT_TASK_STACK_SIZE,
        NULL,
        APP_DEFAULT_TASK_PRIORITY,
        mock_task_stack,
        &mock_task_buffer);
}

/**
 * @brief Mock task, call callback after period of time, and then delay until next period
 * Should be used for generating mock signal data, and the callback should be used for
 * updating the signal data, so that we can test the DSP processing code without real ADC data.
 *
 * @param pvParameters Unused parameter for task, can be NULL
 */
static void _mockTask(void *pvParameters)
{
    TickType_t lastWakeTime = xTaskGetTickCount();
    /** Voltage phase a */
    mockSinGen(mockDMAConfig.bufPointer,
               METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE,
               METER_SIGNAL_COUNT * METER_PHASE_COUNT,
               METER_SAMPLES_PER_CYCLE,
               0.0f);
    /** Current phase a */
    mockSinGen(mockDMAConfig.bufPointer + 1,
               METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE,
               METER_SIGNAL_COUNT * METER_PHASE_COUNT,
               METER_SAMPLES_PER_CYCLE,
               0.0f);

    /** Voltage phase b */
    mockSinGen(mockDMAConfig.bufPointer + 2,
               METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE,
               METER_SIGNAL_COUNT * METER_PHASE_COUNT,
               METER_SAMPLES_PER_CYCLE,
               120.0f);
    /** Current phase b */
    mockSinGen(mockDMAConfig.bufPointer + 3,
               METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE,
               METER_SIGNAL_COUNT * METER_PHASE_COUNT,
               METER_SAMPLES_PER_CYCLE,
               120.0f);

    /** Voltage phase c */
    mockSinGen(mockDMAConfig.bufPointer + 4,
               METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE,
               METER_SIGNAL_COUNT * METER_PHASE_COUNT,
               METER_SAMPLES_PER_CYCLE,
               240.0f);
    /** Current phase c */
    mockSinGen(mockDMAConfig.bufPointer + 5,
               METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE,
               METER_SIGNAL_COUNT * METER_PHASE_COUNT,
               METER_SAMPLES_PER_CYCLE,
               240.0f);
    while (1)
    {
        switch (mockDMAConfig.nextInt)
        {
        case HT:
        {
            if (mockDMAConfig.htCallback)
                mockDMAConfig.htCallback();
            mockDMAConfig.nextInt = TC;
        }
        break;

        case TC:
        {
            if (mockDMAConfig.tcCallback)
                mockDMAConfig.tcCallback();
            mockDMAConfig.nextInt = HT;
        }
        break;

        default:
            break;
        }

        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(mockDMAConfig.signalPeriod));
    }
}

void mockDMAInit(uint16_t *bufPointer, uint32_t length, uint8_t halfCpltInt, uint8_t cpltInt)
{
    (void)halfCpltInt;
    (void)cpltInt;
    mockDMAConfig.bufPointer = bufPointer;
    mockDMAConfig.length = length;
}