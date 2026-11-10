#include "hack.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
int get_rect_ind(NhRect *);

/* Deterministic dependency for the isolated unit probe, not the game RNG. */
static uint32_t probe_rng_state;
static int probe_rng_calls, probe_rng_last_bound, probe_diagnostics;
static char probe_caller[128], probe_diagnostic[128];
boolean rng_log_enabled(void) { return TRUE; }
void rng_log_set_caller(const char *file, int line, const char *func)
{
    const char *base = strrchr(file, '/');
    snprintf(probe_caller, sizeof probe_caller, "%s:%d:%s", base ? base + 1 : file, line, func);
}
int (rn2)(int n)
{
    if (n <= 0) abort();
    probe_rng_last_bound = n;
    probe_rng_calls++;
    probe_rng_state = probe_rng_state * 1664525U + 1013904223U;
    return (int) (probe_rng_state % (unsigned) n);
}
void panic(const char *format, ...) { abort(); }
void impossible(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(probe_diagnostic, sizeof probe_diagnostic, format, args);
    va_end(args);
    probe_diagnostics++;
}

/* Including the original TU lets the oracle expose its private static state
 * without modifying that source. Hybrid state is inspected through its ABI
 * runtime instead; no extra algorithm is supplied to the hybrid probe. */
#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/rect.c"
#endif

size_t probe_context_size(void) { return sizeof(NhRect); }
size_t probe_offset_lx(void) { return offsetof(NhRect, lx); }
size_t probe_offset_ly(void) { return offsetof(NhRect, ly); }
size_t probe_offset_hx(void) { return offsetof(NhRect, hx); }
size_t probe_offset_hy(void) { return offsetof(NhRect, hy); }
int probe_coord_size(void) { return sizeof(coordxy); }
int probe_colno(void) { return COLNO; }
int probe_rowno(void) { return ROWNO; }
void probe_init(void) { init_rect(); }
void probe_free(void) { free_rect(); }
int probe_index(NhRect *r) { return get_rect_ind(r); }
NhRect *probe_get(NhRect *r) { return get_rect(r); }
NhRect *probe_random(void) { return rnd_rect(); }
void probe_bounds(NhRect *a, NhRect *b, NhRect *out) { rect_bounds(*a, *b, out); }
void probe_remove(NhRect *r) { remove_rect(r); }
void probe_add(NhRect *r) { add_rect(r); }
void probe_split(NhRect *a, NhRect *b) { split_rects(a, b); }
void probe_seed(unsigned int seed)
{
    probe_rng_state = seed;
    probe_rng_calls = probe_rng_last_bound = probe_diagnostics = 0;
    probe_caller[0] = probe_diagnostic[0] = '\0';
}
int probe_rng_count(void) { return probe_rng_calls; }
int probe_rng_bound(void) { return probe_rng_last_bound; }
const char *probe_rng_caller(void) { return probe_caller; }
int probe_diagnostic_count(void) { return probe_diagnostics; }
const char *probe_diagnostic_message(void) { return probe_diagnostic; }
int probe_count(void) {
#ifdef TELEPORT_REFERENCE_TU
    return rect_cnt;
#else
    return -1;
#endif
}
int probe_capacity(void) {
#ifdef TELEPORT_REFERENCE_TU
    return n_rects;
#else
    return -1;
#endif
}
NhRect *probe_data(void) {
#ifdef TELEPORT_REFERENCE_TU
    return rect;
#else
    return NULL;
#endif
}
