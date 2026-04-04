#include "adc_sample.h"
#include "app_cfg.h"
#include "share_types.h"
#include "arm_math.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "dsp.h"
#include "mock.h"
#include "pll.h"

static struct adcTask_s
{
    StackType_t stack[APP_DEFAULT_TASK_STACK_SIZE];
    StaticTask_t buffer;
    TaskHandle_t handle;
} adcTask;

meterData_t meterData;

/** Normaly voltage and current value will be subtracted with middle point, but we still
 * need to store the raw ADC value for later processing, so we can just store the raw value
 *  in adc_buffer and do the subtraction in processing stage. 2 is for half and full conversion,
 * because we use DMA in circular mode, so we need to store both half and full conversion data.
 * Layout in memmory is like this: Ua Ia Ub Ib Uc Ic Ua Ia Ub Ib Uc Ic ... for each cycle, and
 * we have METER_SAMPLES_PER_CYCLE samples for each phase.
 */
static uint16_t adc_buffer[METER_SAMPLES_PER_CYCLE][METER_PHASE_COUNT][METER_SIGNAL_COUNT];
static float32_t adc_buffer_f32[METER_SAMPLES_PER_CYCLE][METER_PHASE_COUNT][METER_SIGNAL_COUNT];
static float32_t volBuffer[METER_SAMPLES_PER_CYCLE];
static float32_t curBuffer[METER_SAMPLES_PER_CYCLE];
static uint32_t processingTime;

static float32_t freBuffer[METER_SAMPLES_PER_CYCLE];

void adcSampleReady(void);
void adcSampleTask(void *pvParameters);
void adcHalfConvCpltCallback(void);
void adcConvCpltCallback(void);
void adcDMAInit(void);


void adcSampleInit(void)
{
    /** Create task */
    adcTask.handle = xTaskCreateStatic(adcSampleTask,
                      "ADCSample",
                      APP_DEFAULT_TASK_STACK_SIZE,
                      NULL,
                      APP_DEFAULT_TASK_PRIORITY,
                      adcTask.stack,
                      &adcTask.buffer);
}

void adcSampleTask(void *pvParameters)
{
    /* ADC initialization code goes here */
    adcDMAInit();
    /** If we want to use mock data, we can init the mock signal generator here */
#ifdef DATA_USE_MOCK_DATA
    mockSignalGenInit(1000u / METER_MAIN_FREQUENCY, adcHalfConvCpltCallback, adcConvCpltCallback);
#endif
    while (1)
    {
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);//Wait for HT or TC notification

        uint32_t startTime = DWT->CYCCNT;//For time calculation

        /** Convert ADC values to floating-point */
        for (int i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            for (int j = 0; j < METER_PHASE_COUNT; j++)
            {
                for (int k = 0; k < METER_SIGNAL_COUNT; k++)
                {
                    adc_buffer_f32[i][j][k] = (float32_t)((int16_t)adc_buffer[i][j][k] - 2047); // Subtract middle point to get signed value
                }
            }
        }

        /** Take voltage phase a from adc buffer */
        for (int i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            volBuffer[i] = adc_buffer_f32[i][0][0];
        }

        /** Take current phase a from adc buffer */
        for (int i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            curBuffer[i] = adc_buffer_f32[i][0][1];
        }

        dspProcess(&meterData.phaseData[0], volBuffer, curBuffer);


        /** Take voltage phase b from adc buffer */
        for (int i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            volBuffer[i] = adc_buffer_f32[i][1][0];
        }

        /** Take current phase b from adc buffer */
        for (int i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            curBuffer[i] = adc_buffer_f32[i][1][1];
        }

        dspProcess(&meterData.phaseData[1], volBuffer, curBuffer);
        /** Take voltage phase c from adc buffer */
        for (int i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            volBuffer[i] = adc_buffer_f32[i][2][0];
        }       
        /** Take current phase c from adc buffer */
        for (int i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            curBuffer[i] = adc_buffer_f32[i][2][1];
        }

        dspProcess(&meterData.phaseData[2], volBuffer, curBuffer);

        PLL3_t frePll;
        PLL_Init(&frePll);

        float32_t va, vb, vc;
        /** Frequency calculation (if needed) */
        for (size_t i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            va = adc_buffer_f32[i][0][0] / 2047.0f;
            vb = adc_buffer_f32[i][1][0] / 2047.0f;
            vc = adc_buffer_f32[i][2][0] / 2047.0f;

            PLL_UpdateThreePhase(&frePll, va, vb, vc, 1.0f / METER_SAMPLES_PER_CYCLE / METER_MAIN_FREQUENCY);
            freBuffer[i] = frePll.omega / (2.0f * PI);
        }
        
        float32_t freAvr = 0.0f;
        for (size_t i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
        {
            freAvr += freBuffer[i];
        }
        freAvr /= METER_SAMPLES_PER_CYCLE;

        meterData.frequency = freAvr;

        processingTime = DWT->CYCCNT - startTime;//<1ms for 3 phase with full data, so fast =))
    }
}

/**
 * @brief ADC half conversion complete callback
 * @note Notify adc task
 * 
 */
void adcHalfConvCpltCallback(void)
{
    #ifdef DATA_USE_MOCK_DATA
    xTaskNotify(adcTask.handle, 0, eNoAction);
    #else
    BaseType_t xWake;
    xTaskNotifyFromISR(adcTask.handle, 0, eNoAction, &xWake);
    portYIELD_FROM_ISR(xWake);
    #endif
}

/**
 * @brief ADC half conversion complete callback
 * @note Notify adc task
 * 
 */
void adcConvCpltCallback(void)
{
    #ifdef DATA_USE_MOCK_DATA
    xTaskNotify(adcTask.handle, 0, eNoAction);
    #else
    BaseType_t xWake;
    xTaskNotifyFromISR(adcTask.handle, 0, eNoAction, &xWake);
    portYIELD_FROM_ISR(xWake);
    #endif
}

/**
 * @brief ADC DMA init
 * 
 */
void adcDMAInit(void)
{
    /** MX set DMA and ADC, we need to set memory address for DMA transfer */
    #ifndef DATA_USE_MOCK_DATA
    LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_0, (uint32_t)adc_buffer);
    LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_0, (uint32_t)&ADC1->DR);
    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_0, METER_PHASE_COUNT * 4U * METER_SAMPLES_PER_CYCLE);
    LL_DMA_EnableIT_HT(DMA2, LL_DMA_STREAM_0);
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_0);
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
    #endif
    #ifdef DATA_USE_MOCK_DATA
    /** If we use mock data, we can just generate mock data in the task, so we don't need to set up DMA for ADC. */
    mockDMAInit((uint16_t *)adc_buffer, METER_PHASE_COUNT * METER_SIGNAL_COUNT * METER_SAMPLES_PER_CYCLE, 1, 1);
    #endif
}