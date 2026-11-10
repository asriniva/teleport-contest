#define NEED_VARARGS
#include "hack.h"
#include <termios.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <emscripten/stack.h>

__typeof__(iflags) iflags;
__typeof__(windowprocs) windowprocs;
short ospeed;
extern struct termios inittyb, curttyb;
extern char erase_char, intr_char, kill_char;
static struct termios fixture_input, fixture_output;
static int get_status, set_status, nested_exit, exit_guard, exit_status;
static speed_t fixture_speed;
static long disabled_character;
static char probe_trace_storage[32768];
static jmp_buf exit_jump;
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...)
{
    va_list args;
    va_start(args, format); vsnprintf(probe_trace_storage + strlen(probe_trace_storage), sizeof probe_trace_storage - strlen(probe_trace_storage), format, args); va_end(args);
}
int teleport_probe_tcgetattr(int fd, struct termios *value)
{
    append("get:%d:%s;", fd, value == &inittyb ? "init" : "other");
    if (get_status >= 0) memcpy(value, &fixture_input, sizeof *value);
    return get_status;
}
int teleport_probe_tcsetattr(int fd, int action, const struct termios *value)
{
    append("set:%d:%d:%s;", fd, action, value == &inittyb ? "init" : value == &curttyb ? "cur" : "other");
    memcpy(&fixture_output, value, sizeof *value); return set_status;
}
speed_t teleport_probe_cfgetospeed(const struct termios *value)
{
    append("speed:%s;", value == &inittyb ? "init" : "other"); return fixture_speed;
}
long teleport_probe_fpathconf(int fd, int name)
{
    append("disable:%d:%d;", fd, name); return disabled_character;
}
void teleport_probe_perror(const char *name) { append("perror:%s;", name); }
int teleport_probe_vprintf(const char *format, va_list args)
{
    char output[BUFSZ];
    int count = vsnprintf(output, sizeof output, format, args);
    append("vprintf:%s;", output); return count;
}
int teleport_probe_putchar(int character) { append("putchar:%d;", character); return character; }
void teleport_probe_exit(int code)
{
    append("exit:%d;", code); exit_status = code;
    if (!exit_guard) abort(); longjmp(exit_jump, 1);
}
void getioctls(void) { append("getioctls;"); }
void setioctls(void) { append("setioctls;"); }
void term_start_screen(void) { append("start;"); }
void term_end_screen(void) { append("end;"); }
static void capture_raw(const char *message) { append("raw:%s;", message); }
static void capture_exit(const char *message)
{
    append("window-exit:%s;", message ? message : "<null>");
    if (nested_exit) settty(NULL);
}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/sys/share/unixtty.c"
#endif
#include "tu-unixtty-layout.h"

void probe_options(int get, int set, unsigned int speed, long disabled, int tty, int nested)
{
    get_status = get; set_status = set; fixture_speed = speed;
    disabled_character = disabled; nested_exit = nested;
    windowprocs.wp_id = tty ? wp_tty : wp_shim;
    windowprocs.win_raw_print = capture_raw;
    windowprocs.win_exit_nhwindows = capture_exit;
    probe_trace_storage[0] = '\0'; exit_status = -1;
}
void probe_clear_trace(void) { probe_trace_storage[0] = '\0'; }
const char *probe_trace(void) { return probe_trace_storage; }
void *probe_input_pointer(void) { return &fixture_input; }
void *probe_output_pointer(void) { return &fixture_output; }
void *probe_init_pointer(void) { return &inittyb; }
void *probe_cur_pointer(void) { return &curttyb; }
int probe_ospeed(void) { return ospeed; }
int probe_erase(void) { return erase_char; }
int probe_intr(void) { return intr_char; }
int probe_kill(void) { return kill_char; }
void probe_chars(int erase, int intr, int kill) { erase_char = erase; intr_char = intr; kill_char = kill; }
int probe_echo(void) { return iflags.echo; }
int probe_cbreak(void) { return iflags.cbreak; }
int probe_window(void) { return iflags.window_inited; }
void probe_iflags(int echo, int cbreak, int window) { iflags.echo = echo; iflags.cbreak = cbreak; iflags.window_inited = window; }
int probe_needed(void) {
#ifdef TELEPORT_REFERENCE_TU
    return settty_needed;
#else
    return 0;
#endif
}
void probe_set_needed(int value) {
#ifdef TELEPORT_REFERENCE_TU
    settty_needed = value;
#endif
}
int probe_env(const char *name, const char *value) { return value ? setenv(name, value, 1) : unsetenv(name); }
void probe_get(void) { gettty(); }
void probe_set(const char *text) { settty(text); }
void probe_fast(void) { setftty(); }
void probe_on(void) { intron(); }
void probe_off(void) { introff(); }
void probe_fixup(void) { tty_utf8graphics_fixup(); }
int probe_error(int variant)
{
    exit_guard = 1;
    if (setjmp(exit_jump)) { exit_guard = 0; return -1; }
    switch (variant) {
    case 0: error("fatal plain");
    case 1: error("typed %d %ld %.2f %s %%", -7, (long) -9007199254740993L, 3.25, "message");
    case 2: error("chars %c %u %x", 'Q', 4294967295U, 0xabcdefU);
    default: error("empty:%s", "");
    }
}
int probe_exit_status(void) { return exit_status; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
