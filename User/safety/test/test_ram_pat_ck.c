#include "unity.h"
#include "ram_pat_ck.h"
#include <stdint.h>

static uint32_t test_ram;
static struct ram_pat_ck_ctx ctx;

void setUp(void) {
    test_ram = 0;
}

void tearDown(void) {
    // Nothing to clean up
}

void test_ram_pat_ck_check_pattern_match(void) {
    ram_pat_ck_init(&ctx, &test_ram, 0xA5A5A5A5);
    int32_t result = ram_pat_ck_check(&ctx);
    TEST_ASSERT_EQUAL_INT32(0, result);
}

void test_ram_pat_ck_check_pattern_mismatch(void) {
    ram_pat_ck_init(&ctx, &test_ram, 0xDEADBEEF);
    test_ram = 0x12345678; // Corrupt the pattern
    int32_t result = ram_pat_ck_check(&ctx);
    TEST_ASSERT_EQUAL_INT32(-1, result);
}
