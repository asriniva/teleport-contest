#include "hack.h"
#include "isaac64.h"
#include <stddef.h>
#include <stdio.h>

#ifndef USE_ISAAC64
#error "The rnd JS implementation requires USE_ISAAC64"
#endif

static const struct {
    const char *name;
    size_t value;
} rnd_layout[] = {
    { "ULONG_SIZE", sizeof(unsigned long) },
    { "intSize", sizeof(int) },
    { "pointerSize", sizeof(void *) },
    { "USE_ISAAC64", 1 },
#if NH_DEVEL_STATUS != NH_STATUS_RELEASED
    { "DEVELOPMENT", 1 },
#else
    { "DEVELOPMENT", 0 },
#endif
    { "_IOLBF", _IOLBF },
    { "CORE", 0 },
    { "DISP", 1 },
    { "ISAAC64_SZ", ISAAC64_SZ },
    { "n", offsetof(isaac64_ctx, n) },
    { "r", offsetof(isaac64_ctx, r) },
    { "m", offsetof(isaac64_ctx, m) },
    { "a", offsetof(isaac64_ctx, a) },
    { "b", offsetof(isaac64_ctx, b) },
    { "c", offsetof(isaac64_ctx, c) },
};

size_t probe_context_size(void) { return sizeof(isaac64_ctx); }
int probe_layout_count(void) { return sizeof rnd_layout / sizeof rnd_layout[0]; }
const char *probe_layout_name(int index) { return rnd_layout[index].name; }
size_t probe_layout_value(int index) { return rnd_layout[index].value; }
