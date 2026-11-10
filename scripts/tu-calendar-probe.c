#include "hack.h"
#include <stddef.h>
#include <stdlib.h>
#include <emscripten/stack.h>

/* Fatal allocation failure is outside this isolated probe's tested inputs. */
void panic(const char *format, ...) { abort(); }

size_t probe_context_size(void) { return sizeof(struct tm); }
size_t probe_offset_tm_year(void) { return offsetof(struct tm, tm_year); }
size_t probe_offset_tm_mon(void) { return offsetof(struct tm, tm_mon); }
size_t probe_offset_tm_mday(void) { return offsetof(struct tm, tm_mday); }
size_t probe_offset_tm_hour(void) { return offsetof(struct tm, tm_hour); }
size_t probe_offset_tm_min(void) { return offsetof(struct tm, tm_min); }
size_t probe_offset_tm_sec(void) { return offsetof(struct tm, tm_sec); }
size_t probe_offset_tm_wday(void) { return offsetof(struct tm, tm_wday); }
size_t probe_offset_tm_yday(void) { return offsetof(struct tm, tm_yday); }
int probe_int_size(void) { return sizeof(int); }
int probe_long_size(void) { return sizeof(long); }
int probe_time_size(void) { return sizeof(time_t); }
size_t probe_stack(void) { return (size_t) emscripten_stack_get_current(); }
time_t probe_now(void) { return getnow(); }
int probe_year(void) { return getyear(); }
long probe_date(time_t date) { return yyyymmdd(date); }
long probe_time(time_t date) { return hhmmss(date); }
char *probe_format(time_t date) { return yyyymmddhhmmss(date); }
time_t probe_parse(char *text) { return time_from_yyyymmddhhmmss(text); }
int probe_moon(void) { return phase_of_the_moon(); }
int probe_friday(void) { return friday_13th(); }
int probe_night(void) { return night(); }
int probe_midnight(void) { return midnight(); }
int probe_set_env(const char *name, const char *value)
{
    return value ? setenv(name, value, 1) : unsetenv(name);
}
