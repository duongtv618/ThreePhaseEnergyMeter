// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/safety/inc/deadline_monitor.h"

struct task_health_status test_status;

void setUp(void)
{
    dm_init();
}

void tearDown(void)
{
}

void test_dm_init(void)
{
    dm_init();
}

void test_dm_register(void)
{
    enum dm_error_code result = dm_register(&test_status, 1000);
    UnityAssertEqualNumber((UNITY_INT)((DM_ERR_NONE)), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);
}

void test_dm_report(void)
{
    dm_register(&test_status, 1000);
    dm_report(&test_status, 500);
    UnityAssertEqualNumber((UNITY_INT)((500)), (UNITY_INT)((test_status.exe_time_us)), (
   ((void *)0)
   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);
}

void test_dm_is_healthy(void)
{
    dm_register(&test_status, 1000);
    dm_report(&test_status, 500);
    enum dm_error_code result = dm_is_healthy(&test_status);
    UnityAssertEqualNumber((UNITY_INT)((DM_ERR_PASSED)), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);
    dm_report(&test_status, 1500);
    result = dm_is_healthy(&test_status);
    UnityAssertEqualNumber((UNITY_INT)((DM_ERR_FAILED)), (UNITY_INT)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);
    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((test_status.dm_missed)), (
   ((void *)0)
   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);
}