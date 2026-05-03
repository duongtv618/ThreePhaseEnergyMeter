#include "deadline_monitor.h"

#include <string.h>

// #include "FreeRTOS.h"
// #include "task.h"

#define MAX_TASKS 16

uint32_t dm_cycles_to_us(uint32_t cycles) {
#if defined(ARM_MATH_HOST) && ARM_MATH_HOST
    (void)cycles;
    return 0U;
#else
    extern uint32_t SystemCoreClock;
    if (SystemCoreClock == 0U) {
        return 0U;
    }
    return (uint32_t)(((uint64_t)cycles * 1000000ULL) / (uint64_t)SystemCoreClock);
#endif
}

static struct {
    struct task_health_status *status[MAX_TASKS];
    uint8_t count; // Count of registered tasks
} dm_ctx;

void dm_init(void) {
    memset(&dm_ctx, 0, sizeof(dm_ctx));
}

enum dm_error_code dm_register(struct task_health_status *status, uint32_t deadline_us) {
    if (status == NULL) {
        return DM_ERR_INVALID;
    }
    if (dm_ctx.count >= MAX_TASKS) {
        return DM_ERR_FAILED;
    }
    dm_ctx.status[dm_ctx.count] = status;
    dm_ctx.count++;
    status->exe_time_us = 0;
    status->exe_deadline_us = deadline_us;
    return DM_ERR_NONE;
}

void dm_report(struct task_health_status *status, uint32_t exe_time_us) {
    if (status == NULL) {
        return;
    }
    status->exe_time_us = exe_time_us;
}

enum dm_error_code dm_is_healthy(struct task_health_status *status) {
    if (status == NULL) {
        return DM_ERR_INVALID;
    }
    if (status->exe_time_us <= status->exe_deadline_us) {
        status->healthy = 1;
        return DM_ERR_PASSED;
    } else {
        status->healthy = 0;
        status->dm_missed++;
        return DM_ERR_FAILED;
    }
}

enum dm_error_code dm_is_system_healthy(struct task_health_status *status) {
    if (status == NULL) {
        return DM_ERR_INVALID;
    }
    for (uint8_t i = 0; i < dm_ctx.count; i++) {
        if (dm_ctx.status[i] && dm_ctx.status[i]->healthy == 0) {
            return DM_ERR_FAILED;
        }
    }
    return DM_ERR_PASSED;
}

uint8_t dm_get_missed_count(struct task_health_status *status) {
    if (status == NULL) {
        return 0;
    }
    return status->dm_missed;
}