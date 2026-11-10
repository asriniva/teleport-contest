#include "hack.h"
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

/* Isolate fatal process exit for the unit probe only. Production still calls
 * NetHack's actual panic. Capture the same formatted message on both paths. */
static jmp_buf probe_jump;
static char probe_panic_message[256];
void panic(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vsnprintf(probe_panic_message, sizeof probe_panic_message, format, ap);
    va_end(ap);
    longjmp(probe_jump, 1);
}

size_t probe_context_size(void) { return sizeof(strbuf_t); }
size_t probe_offset_len(void) { return offsetof(strbuf_t, len); }
size_t probe_offset_str(void) { return offsetof(strbuf_t, str); }
size_t probe_offset_buf(void) { return offsetof(strbuf_t, buf); }
size_t probe_buffer_size(void) { return sizeof(((strbuf_t *) 0)->buf); }
int probe_largest_int(void) { return LARGEST_INT; }
void probe_init(strbuf_t *strbuf) { strbuf_init(strbuf); }
void probe_append(strbuf_t *strbuf, const char *str) { strbuf_append(strbuf, str); }
void probe_reserve(strbuf_t *strbuf, int len) { strbuf_reserve(strbuf, len); }
void probe_empty(strbuf_t *strbuf) { strbuf_empty(strbuf); }
void probe_crlf(strbuf_t *strbuf) { strbuf_nl_to_crlf(strbuf); }
int probe_match(const char *pattern, const char *text, int ci) { return ci ? pmatchi(pattern, text) : pmatch(pattern, text); }
int probe_guarded_strlen(const char *str)
{
    probe_panic_message[0] = '\0';
    if (setjmp(probe_jump)) return -1;
    return (int) Strlen_(str, "source-path.c", 777);
}
const char *probe_message(void) { return probe_panic_message; }
