/**
 * @file deadline_monitor.h
 * @author your name (you@domain.com)
 * @brief Monitor task execution times against deadlines and track health status
 * @version 0.1
 * @date 2026-05-01
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef DEADLINE_MONITOR_H
#define DEADLINE_MONITOR_H

#include "share_types.h"
#include "app_cfg.h"

/**
 * @brief Error codes for the deadline monitor
 * 
 */
enum dm_error_code {
    DM_ERR_NONE = 0,
    DM_ERR_PASSED = 1,
    DM_ERR_FAILED = 2,
    DM_ERR_INVALID = 3,
};

/**
 * @brief Structure to hold the health status of a task
 * 
 */
struct task_health_status {
    uint32_t exe_time_us; // Execution time in microseconds
    uint32_t exe_deadline_us; // Deadline in microseconds
    uint8_t healthy; // 1 if healthy, 0 if not
    uint8_t dm_missed; // Count of missed deadlines
};

/**
 * @brief Initialize the deadline monitor context
 * 
 */
void dm_init(void);

/**
 * @brief Convert Cortex-M DWT cycle delta (when CYCCNT wraps on uint32_t subtraction)
 *        to microseconds using SystemCoreClock. Host/unit-test builds return 0.
 */
uint32_t dm_cycles_to_us(uint32_t cycles);

/**
 * @brief Register a task with the deadline monitor
 * 
 * @param status points to the task health status structure to be registered
 * @param deadline_us is the execution deadline in microseconds for the task
 * @return enum dm_error_code is DM_ERR_NONE if registration is successful, DM_ERR_INVALID if the status pointer is NULL, or DM_ERR_FAILED if the maximum number of tasks has been reached
 */
enum dm_error_code dm_register(struct task_health_status *status, uint32_t deadline_us);

/**
 * @brief Report the execution time of a task
 * 
 * @param status points to the task health status structure
 * @param exe_time_us is the actual execution time in microseconds
 */
void dm_report(struct task_health_status *status, uint32_t exe_time_us);

/**
 * @brief Check if a task is healthy based on its execution time and deadline
 * 
 * @param status points to the task health status structure
 * @return enum dm_error_code is DM_ERR_PASSED if the task is healthy, DM_ERR_FAILED if not
 */
enum dm_error_code dm_is_healthy(struct task_health_status *status);

/**
 * @brief Check if the system is healthy based on the health status of all registered tasks
 * 
 * @param status points to the task health status structure
 * @return enum dm_error_code is DM_ERR_PASSED if the system is healthy, DM_ERR_FAILED if not
 */
enum dm_error_code dm_is_system_healthy(struct task_health_status *status);

/**
 * @brief Get the count of missed deadlines for a specific task
 * 
 * @param status points to the task health status structure
 * @return uint8_t is the count of missed deadlines for the task
 */
uint8_t dm_get_missed_count(struct task_health_status *status);

#endif // DEADLINE_MONITOR_H