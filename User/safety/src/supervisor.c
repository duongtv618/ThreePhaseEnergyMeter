#include "supervisor.h"

#include "stm32f4xx_ll_iwdg.h"
#include "stm32f411xe.h"

/* dm_is_system_healthy() requires a non-NULL pointer but does not use the object */
static struct task_health_status sv_dm_arg_dummy;

void supervisor_init(void) {
}

uint8_t supervisor_service(void) {
    if (dm_is_system_healthy(&sv_dm_arg_dummy) != DM_ERR_PASSED) {
        return 0;
    }
    LL_IWDG_ReloadCounter(IWDG);
    return 1;
}
