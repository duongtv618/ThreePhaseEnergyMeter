// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "build_x86/vendor/unity/src/unity.h"
#include "User/safety/inc/ram_pat_ck.h"

static uint32_t test_ram;
static struct ram_pat_ck_ctx ctx;

void setUp(void)
{
    test_ram = 0;
}

void tearDown(void)
{
}

void test_ram_pat_ck_check_pattern_match(void)
{
    ram_pat_ck_init(&ctx, &test_ram, 0xA5A5A5A5);
    int32_t result = ram_pat_ck_check(&ctx);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((0)), (UNITY_INT)(UNITY_INT32)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_INT32);
}

void test_ram_pat_ck_check_pattern_mismatch(void)
{
    ram_pat_ck_init(&ctx, &test_ram, 0xDEADBEEF);
    test_ram = 0x12345678;
    int32_t result = ram_pat_ck_check(&ctx);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((-1)), (UNITY_INT)(UNITY_INT32)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT32);
}