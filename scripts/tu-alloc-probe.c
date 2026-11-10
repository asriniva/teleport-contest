#include "hack.h"
#include "nhlua.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>

#undef malloc
#undef realloc
extern void *malloc(size_t);
extern void *realloc(void *, size_t);
static int probe_active, fail_malloc, fail_realloc, malloc_calls, realloc_calls;
static size_t requested;
static void *result;
static int signed_result;
static unsigned unsigned_result;
static char panic_message[512];
static jmp_buf panic_jump;

/* Test-only compile-time redirection observes C allocation requests during
 * the current probe operation. Module setup and test allocations continue
 * to use the actual libc allocator; the game build has no redirection. */
void *teleport_probe_malloc(size_t size)
{
    if (probe_active) {
        malloc_calls++; requested = size;
        if (fail_malloc) { fail_malloc = 0; return NULL; }
    }
    return malloc(size);
}
void *teleport_probe_realloc(void *pointer, size_t size)
{
    if (probe_active) {
        realloc_calls++; requested = size;
        if (fail_realloc) { fail_realloc = 0; return NULL; }
    }
    return realloc(pointer, size);
}
void panic(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(panic_message, sizeof panic_message, format, args);
    va_end(args);
    if (!probe_active) abort();
    longjmp(panic_jump, 1);
}
static void begin(int fail_m, int fail_r)
{
    result = NULL; signed_result = 0; unsigned_result = 0;
    panic_message[0] = '\0'; malloc_calls = realloc_calls = 0;
    requested = 0; fail_malloc = fail_m; fail_realloc = fail_r; probe_active = 1;
}
#define GUARD if (setjmp(panic_jump)) { probe_active = 0; return -1; }
size_t probe_context_size(void) { return sizeof(long); }
int probe_long_size(void) { return sizeof(long); }
int probe_int_size(void) { return sizeof(int); }
int probe_lua_integer_size(void) { return sizeof(LUA_INTEGER); }
int probe_ull_size(void) { return sizeof(unsigned long long); }
int probe_ptrbuf_count(void) { return 4; }
int probe_ptrbuf_size(void) { return 32; }
int probe_has_ptr_fmt(void) {
#ifdef HAS_PTR_FMT
    return 1;
#else
    return 0;
#endif
}
int probe_monitor_heap(void) {
#ifdef MONITOR_HEAP
    return 1;
#else
    return 0;
#endif
}
int probe_alloc(unsigned length, int fail)
{
    begin(fail, 0); GUARD
    result = alloc(length); probe_active = 0; return 0;
}
int probe_realloc(void *pointer, unsigned length, int fail)
{
    begin(0, fail); GUARD
    result = re_alloc((long *) pointer, length); probe_active = 0; return 0;
}
int probe_dup(const char *string, int fail)
{
    begin(fail, 0); GUARD
    result = dupstr(string); probe_active = 0; return 0;
}
int probe_signed(LUA_INTEGER value, const char *file, int line)
{
    begin(0, 0); GUARD
    signed_result = FITSint_(value, file, line); probe_active = 0; return 0;
}
int probe_unsigned(unsigned long long value, const char *file, int line)
{
    begin(0, 0); GUARD
    unsigned_result = FITSuint_(value, file, line); probe_active = 0; return 0;
}
char *probe_format(void *pointer) { return fmt_ptr(pointer); }
void *probe_result(void) { return result; }
int probe_signed_result(void) { return signed_result; }
unsigned probe_unsigned_result(void) { return unsigned_result; }
int probe_malloc_calls(void) { return malloc_calls; }
int probe_realloc_calls(void) { return realloc_calls; }
size_t probe_requested(void) { return requested; }
const char *probe_panic_message(void) { return panic_message; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
