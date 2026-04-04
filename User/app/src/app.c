#include "app.h"
#include "stm32f4xx.h"
#include "led_blink.h"
#include "adc_sample.h"
#include "comm.h"

static void DWTInit(void);

static void DWTInit(void)
{
    /* Enable DWT and CYCCNT */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // Enable trace and debug
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; // Enable cycle counter
}

/**
 * @brief Initialize the application
 */
void app_init(void) {
    DWTInit();
    ledBlinkInit();
    adcSampleInit();
    comm_init();
}