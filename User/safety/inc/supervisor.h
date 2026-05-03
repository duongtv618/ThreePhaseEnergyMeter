/**
 * @file supervisor.h
 * @brief Periodically evaluate deadline-monitor task health and kick IWDG when healthy
 * @version 0.1
 * @date 2026-05-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <stdint.h>

#include "deadline_monitor.h"

/**
 * @brief One-time setup (reserved for future use)
 */
void supervisor_init(void);

/**
 * @brief Check all registered task_health_status entries; reload IWDG if the system is healthy
 *
 * @return 1 if every registered task has healthy==1 and the IWDG was reloaded, 0 otherwise
 */
uint8_t supervisor_service(void);

#endif /* SUPERVISOR_H */
