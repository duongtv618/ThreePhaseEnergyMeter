#ifndef RAM_PAT_CK_H
#define RAM_PAT_CK_H

#include "share_types.h"

struct ram_pat_ck_ctx {
    uint32_t pattern;
    uint32_t *addr;
};

/**
 * @brief Initialize the RAM pattern check context
 * 
 * @param ctx points to the RAM pattern check context to be initialized
 * @param addr points to the RAM address where the pattern will be written and checked
 * @param pattern the pattern to be checked
 */
void ram_pat_ck_init(struct ram_pat_ck_ctx *ctx, uint32_t *addr, uint32_t pattern);

/**
 * @brief Check the RAM pattern
 * 
 * @param ctx points to the RAM pattern check context
 * @return int32_t 0 if the pattern matches, -1 otherwise
 */
int32_t ram_pat_ck_check(struct ram_pat_ck_ctx *ctx);

#endif // RAM_PAT_CK_H