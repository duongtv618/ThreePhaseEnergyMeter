#include "ram_pat_ck.h"

void ram_pat_ck_init(struct ram_pat_ck_ctx *ctx, uint32_t *addr, uint32_t pattern) {
    ctx->pattern = pattern;
    ctx->addr = addr;
    *ctx->addr = pattern; // Write the pattern to the specified address
}

int32_t ram_pat_ck_check(struct ram_pat_ck_ctx *ctx) {
    if (*ctx->addr != ctx->pattern) {
        return -1; // Pattern mismatch, RAM check failed
    }
    return 0; // RAM check passed
}