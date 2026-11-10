#include "hack.h"
#include "nhmd4.h"
#include <stddef.h>
#include <stdlib.h>

size_t probe_context_size(void) { return sizeof(NHMD4_CTX); }
size_t probe_offset_lo(void) { return offsetof(NHMD4_CTX, lo); }
size_t probe_offset_hi(void) { return offsetof(NHMD4_CTX, hi); }
size_t probe_offset_a(void) { return offsetof(NHMD4_CTX, a); }
size_t probe_offset_b(void) { return offsetof(NHMD4_CTX, b); }
size_t probe_offset_c(void) { return offsetof(NHMD4_CTX, c); }
size_t probe_offset_d(void) { return offsetof(NHMD4_CTX, d); }
size_t probe_offset_buffer(void) { return offsetof(NHMD4_CTX, buffer); }
size_t probe_offset_block(void) { return offsetof(NHMD4_CTX, block); }
void probe_init(NHMD4_CTX *ctx) { nhmd4_init(ctx); }
void probe_update(NHMD4_CTX *ctx, const unsigned char *data, size_t size) { nhmd4_update(ctx, data, size); }
void probe_final(NHMD4_CTX *ctx, unsigned char *result) { nhmd4_final(ctx, result); }
