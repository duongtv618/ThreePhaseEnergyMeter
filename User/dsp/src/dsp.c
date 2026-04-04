#include "dsp.h"
#include "arm_math.h"
#include "pll.h"


float32_t mulBuffer[METER_SAMPLES_PER_CYCLE];
float32_t fftInput[METER_SAMPLES_PER_CYCLE];
float32_t fftOutput[METER_SAMPLES_PER_CYCLE];
float32_t freBuffer[METER_SAMPLES_PER_CYCLE];

arm_rfft_fast_instance_f32 S;
PLL_t pll;

void dspProcess(phaseMeterData_t *meterData, float32_t volBuffer[METER_SAMPLES_PER_CYCLE], float32_t curBuffer[METER_SAMPLES_PER_CYCLE])
{
    /* DSP processing code goes here */
    /* For example, you can calculate RMS voltage and current, active power, reactive power, etc. */
    arm_rms_f32(volBuffer, METER_SAMPLES_PER_CYCLE, &meterData->rmsVoltage);
    arm_rms_f32(curBuffer, METER_SAMPLES_PER_CYCLE, &meterData->rmsCurrent);
    arm_mult_f32(volBuffer, curBuffer, mulBuffer, METER_SAMPLES_PER_CYCLE);    // mulBuffer now holds the instantaneous power
    arm_mean_f32(mulBuffer, METER_SAMPLES_PER_CYCLE, &meterData->activePower); // active power is the average of instantaneous power over a cycle

    /** THD */
    static uint8_t isFFTInit = 0;
    if (isFFTInit == 0)
    {
        arm_rfft_128_fast_init_f32(&S);
        isFFTInit = 1;
    }

    // Process voltage THD
    arm_copy_f32(volBuffer, fftInput, METER_SAMPLES_PER_CYCLE);
    arm_rfft_fast_f32(&S, fftInput, fftOutput, 0);
    float32_t fundamentalVoltage = sqrtf(powf(fftOutput[2], 2) + powf(fftOutput[3], 2)); // Fundamental component is the second bin, first is dc offset
    float32_t harmonicSumVoltage = 0.0f;
    for (int i = 4; i < METER_SAMPLES_PER_CYCLE; i += 2) // Start from the second bin, and skip every other bin since it's complex
    {
        harmonicSumVoltage += sqrtf(powf(fftOutput[i], 2) + powf(fftOutput[i + 1], 2)); // Sum of harmonics
    }
    meterData->thd.voltage = harmonicSumVoltage / fundamentalVoltage * 100.0f; // THD in percentage

    // Process current THD
    arm_copy_f32(curBuffer, fftInput, METER_SAMPLES_PER_CYCLE);
    arm_rfft_fast_f32(&S, fftInput, fftOutput, 0);
    float32_t fundamentalCurrent = sqrtf(powf(fftOutput[2], 2) + powf(fftOutput[3], 2)); // Fundamental component is the second bin, first is dc offset
    float32_t harmonicSumCurrent = 0.0f;
    for (int i = 4; i < METER_SAMPLES_PER_CYCLE; i += 2) // Start from the second bin, and skip every other bin since it's complex
    {
        harmonicSumCurrent += sqrtf(powf(fftOutput[i], 2) + powf(fftOutput[i + 1], 2)); // Sum of harmonics
    }
    meterData->thd.current = harmonicSumCurrent / fundamentalCurrent * 100.0f; // THD in percentage

    static uint8_t frePllInit = 0;

    if (frePllInit == 0)
    {
        PLL_Init(&pll);
        frePllInit = 1;
    }
    
    // for (size_t i = 0; i < METER_SAMPLES_PER_CYCLE; i++)
    // {
    //     //ADC normalize from [-2047;2047] to [-1;1]
    //     volBuffer[i] = volBuffer[i] / 2047.0f;

    //     PLL_UpdateSinglePhase(&pll, volBuffer[i], 1.0f / METER_SAMPLES_PER_CYCLE / METER_MAIN_FREQUENCY);
    //     freBuffer[i] = pll.omega / (2.0f * PI);
    // }
    

    // For reactive power, you can use the quadrature component of the current, which can be obtained by applying a Hilbert transform to the current signal. However, for simplicity, we will just calculate the reactive power as the difference between apparent power and active power.
    meterData->apparentPower = meterData->rmsVoltage * meterData->rmsCurrent;
    meterData->reactivePower = sqrtf(powf(meterData->apparentPower, 2) - powf(meterData->activePower, 2));
    meterData->powerFactor = meterData->activePower / meterData->apparentPower;
}