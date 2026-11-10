#include "config.h"
#include "isaac64.h"
#include <stddef.h>
#include <stdlib.h>

size_t probe_context_size(void) { return sizeof(isaac64_ctx); }
size_t probe_offset_n(void) { return offsetof(isaac64_ctx, n); }
size_t probe_offset_r(void) { return offsetof(isaac64_ctx, r); }
size_t probe_offset_m(void) { return offsetof(isaac64_ctx, m); }
size_t probe_offset_a(void) { return offsetof(isaac64_ctx, a); }
size_t probe_offset_b(void) { return offsetof(isaac64_ctx, b); }
size_t probe_offset_c(void) { return offsetof(isaac64_ctx, c); }
void probe_init(isaac64_ctx *ctx, const unsigned char *seed, int size) { isaac64_init(ctx, seed, size); }
void probe_reseed(isaac64_ctx *ctx, const unsigned char *seed, int size) { isaac64_reseed(ctx, seed, size); }
uint64_t probe_next(isaac64_ctx *ctx) { return isaac64_next_uint64(ctx); }
uint64_t probe_bounded(isaac64_ctx *ctx, uint64_t n) { return isaac64_next_uint(ctx, n); }
