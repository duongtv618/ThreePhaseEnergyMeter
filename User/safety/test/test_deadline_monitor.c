#include "unity.h"
#include "deadline_monitor.h"
#include <stdint.h>

struct task_health_status test_status;

void setUp(void) {
    dm_init();
}

void tearDown(void) {
    // Nothing to clean up
}

void test_dm_init(void) {
    dm_init();
    // Add assertions to check the initial state of the deadline monitor
}

void test_dm_register(void) {
    enum dm_error_code result = dm_register(&test_status, 1000);
    TEST_ASSERT_EQUAL(DM_ERR_NONE, result);
}

void test_dm_report(void) {
    dm_register(&test_status, 1000);
    dm_report(&test_status, 500);
    TEST_ASSERT_EQUAL(500, test_status.exe_time_us);
}

void test_dm_is_healthy(void) {
    dm_register(&test_status, 1000);
    dm_report(&test_status, 500);
    enum dm_error_code result = dm_is_healthy(&test_status);
    TEST_ASSERT_EQUAL(DM_ERR_PASSED, result);
    dm_report(&test_status, 1500);
    result = dm_is_healthy(&test_status);
    TEST_ASSERT_EQUAL(DM_ERR_FAILED, result);
    TEST_ASSERT_EQUAL(1, test_status.dm_missed);
}
        