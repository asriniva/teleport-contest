#include "hack.h"
#include <termios.h>
#include <signal.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-ioctl-layout.h"

extern struct termios termio;
__typeof__(windowprocs) windowprocs;
__typeof__(gt) gt;
static struct termios fixture_input, fixture_output;
static int get_status, set_status, kill_status;
static boolean authorized;
static uintptr_t current_handler;
static char trace[8192];
static int window_status=-1,window_rows,window_columns;
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...)
{
    va_list args;
    va_start(args, format); vsnprintf(trace + strlen(trace), sizeof(trace) - strlen(trace), format, args); va_end(args);
}
#if defined(__EMSCRIPTEN__) && !defined(TELEPORT_NATIVE_PLATFORM_ABI)
typedef int fixture_ioctl_request;
#else
typedef unsigned long fixture_ioctl_request;
#endif
int teleport_probe_ioctl(int fd,fixture_ioctl_request request,...)
{
    if(window_status==-1)return -1;
    va_list args;va_start(args,request);struct winsize *out=va_arg(args,struct winsize*);va_end(args);
    memset(out,0,sizeof *out);out->ws_row=window_rows;out->ws_col=window_columns;
    append("window:%d:%lu;",fd,(unsigned long)request);return window_status;
}
void probe_window_options(int status,int rows,int columns)
{
    window_status=status;window_rows=rows;window_columns=columns;LI=12;CO=34;trace[0]=0;
}
int probe_dimensions(int column){return column?CO:LI;}
/* Only isolated probe builds redirect these C platform calls. They observe
 * requests without touching the host terminal, signals or process group. */
int teleport_probe_tcgetattr(int fd, struct termios *value)
{
    append("get:%d;", fd);
    if (!get_status) memcpy(value, &fixture_input, sizeof *value);
    return get_status;
}
int teleport_probe_tcsetattr(int fd, int action, const struct termios *value)
{
    append("set:%d:%d;", fd, action);
    memcpy(&fixture_output, value, sizeof *value); return set_status;
}
void (*teleport_probe_signal(int number, void (*handler)(int)))(int)
{
    uintptr_t previous = current_handler;
    append("signal:%d:%" PRIuPTR ";", number, (uintptr_t) handler);
    current_handler = (uintptr_t) handler;
    return (void (*)(int)) previous;
}
int teleport_probe_kill(pid_t pid, int number)
{
    append("kill:%d:%d;", (int) pid, number); return kill_status;
}
boolean check_user_string(const char *users)
{
    append("check:%s;", users); return authorized;
}
static void capture_suspend(const char *message) { append("suspend:%s;", message ? message : "<null>"); }
static void capture_resume(void) { append("resume;"); }
static void message(const char *kind, const char *format, va_list args)
{
    char buffer[BUFSZ];
    vsnprintf(buffer, sizeof buffer, format, args); append("%s:%s;", kind, buffer);
}
void Norep(const char *format, ...)
{
    va_list args; va_start(args, format); message("Norep", format, args); va_end(args);
}
void pline(const char *format, ...)
{
    va_list args; va_start(args, format); message("pline", format, args); va_end(args);
}
void probe_options(int get, int set, int kill_result, int auth, uintptr_t handler)
{
    get_status = get; set_status = set; kill_status = kill_result; authorized = auth;
    current_handler = handler; trace[0] = '\0';
    windowprocs.win_suspend_nhwindows = capture_suspend;
    windowprocs.win_resume_nhwindows = capture_resume;
}
void probe_shellers(const char *value) { sysopt.shellers = (char *) value; }
void *probe_termio_pointer(void) { return &termio; }
void *probe_input_pointer(void) { return &fixture_input; }
void *probe_output_pointer(void) { return &fixture_output; }
const char *probe_trace(void) { return trace; }
uintptr_t probe_handler(void) { return current_handler; }
void probe_get(void) { getioctls(); }
void probe_set(void) { setioctls(); }
void probe_windows(void) { getwindowsz(); }
int probe_suspend(void) { return dosuspend(); }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
