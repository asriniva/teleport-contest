#define RNGLOG_IN_RND_C
#include "hack.h"
#include "isaac64.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>

struct you u;
__typeof__(has_strong_rngseed) has_strong_rngseed;
static unsigned long seed_value, seed_step;
static int seed_calls, panic_guard;
static char diagnostic[512], panic_message[512];
static jmp_buf panic_jump;
unsigned long sys_random_seed(void)
{
    unsigned long result = seed_value;
    seed_value += seed_step; seed_calls++; return result;
}
void panic(const char *format, ...)
{
    va_list args;
    va_start(args, format); vsnprintf(panic_message, sizeof panic_message, format, args); va_end(args);
    if (!panic_guard) abort();
    longjmp(panic_jump, 1);
}
void impossible(const char *format, ...)
{
    va_list args;
    va_start(args, format); vsnprintf(diagnostic, sizeof diagnostic, format, args); va_end(args);
}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/rnd.c"
#endif
#include "tu-rnd-layout.h"

static int bad_rng(int value) { return value; }
static int (*select_rng(int which))(int)
{
    return which == 0 ? (rn2) : which == 1 ? rn2_on_display_rng : bad_rng;
}
#define GUARD panic_message[0] = '\0'; panic_guard = 1; if (setjmp(panic_jump)) { panic_guard = 0; return -1; }
void probe_seed(unsigned long value, unsigned long step) { seed_value = value; seed_step = step; seed_calls = 0; }
int probe_seed_calls(void) { return seed_calls; }
unsigned long probe_seed_value(void) { return seed_value; }
int probe_init(unsigned long seed, int which)
{
    GUARD
    init_isaac64(seed, select_rng(which)); panic_guard = 0; return 0;
}
int probe_init_random(int which)
{
    GUARD
    init_random(select_rng(which)); panic_guard = 0; return 0;
}
int probe_reseed(int which, int strong)
{
    has_strong_rngseed = strong;
    GUARD
    reseed_random(select_rng(which)); panic_guard = 0; return 0;
}
void probe_hero(int luck, int more, int level) { u.uluck = luck; u.moreluck = more; u.ulevel = level; }
int probe_rn2(int x) { diagnostic[0] = '\0'; return (rn2)(x); }
int probe_display(int x) { diagnostic[0] = '\0'; return rn2_on_display_rng(x); }
int probe_rnd(int x) { diagnostic[0] = '\0'; return (rnd)(x); }
int probe_rnd_display(int x) { diagnostic[0] = '\0'; return rnd_on_display_rng(x); }
int probe_rnl(int x) { diagnostic[0] = '\0'; return (rnl)(x); }
int probe_dice(int n, int x) { diagnostic[0] = '\0'; return (d)(n, x); }
int probe_rne(int x) { diagnostic[0] = '\0'; return (rne)(x); }
int probe_rnz(int x) { diagnostic[0] = '\0'; return (rnz)(x); }
void probe_shuffle(int *values, int count) { shuffle_int_array(values, count); }
void probe_log_init(void) { rng_log_init(); }
int probe_enabled(void) { return rng_log_enabled(); }
int probe_count(void) { return rng_log_get_call_count(); }
void probe_caller(const char *file, int line, const char *function) { rng_log_set_caller(file, line, function); }
int probe_env(const char *name, const char *value) { return value ? setenv(name, value, 1) : unsetenv(name); }
const char *probe_diagnostic(void) { return diagnostic; }
const char *probe_panic_message(void) { return panic_message; }
void *probe_state(int which) {
#ifdef TELEPORT_REFERENCE_TU
    return &rnglist[which].rng_state;
#else
    return NULL;
#endif
}
int probe_state_init(int which) {
#ifdef TELEPORT_REFERENCE_TU
    return rnglist[which].init;
#else
    return 0;
#endif
}
FILE *probe_log_pointer(void) {
#ifdef TELEPORT_REFERENCE_TU
    return rng_logfile;
#else
    return NULL;
#endif
}
int probe_log_disp(void) {
#ifdef TELEPORT_REFERENCE_TU
    return rng_log_disp;
#else
    return 0;
#endif
}
const char *probe_caller_file(void) {
#ifdef TELEPORT_REFERENCE_TU
    return rng_caller_file;
#else
    return NULL;
#endif
}
int probe_caller_line(void) {
#ifdef TELEPORT_REFERENCE_TU
    return rng_caller_line;
#else
    return 0;
#endif
}
const char *probe_caller_function(void) {
#ifdef TELEPORT_REFERENCE_TU
    return rng_caller_func;
#else
    return NULL;
#endif
}
int probe_flush(FILE *file) { return fflush(file); }
int probe_close(FILE *file) { return fclose(file); }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
