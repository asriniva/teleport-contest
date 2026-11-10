/* Include from tu-support.c: REPORT typed ABI/dependency calls only. */
#include "hack.h"
#include "nhmd4.h"
#include "report.storage.h"
static struct teleport_report_storage teleport_report_storage;
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

void *teleport_report_global(int field) {
    switch (field) {
    case 0: return &gc.crash_urlmax;
    case 1: return &gc.crash_name;
    case 2: return &gc.crash_email;
    case 3: return &sysopt.crashreporturl;
    case 4: return &gs.saved_pline_index;
    case 5: return gs.saved_plines;
    case 6: return teleport_report_storage.bid;
    case 7: return teleport_report_storage.url;
    default: return NULL;
    }
}
int *teleport_report_errno(void) { return &errno; }
void *teleport_report_environ(void) { extern char **environ; return environ; }
void *teleport_report_handler(void) { return (void *) panictrace_handler; }
int teleport_report_open(const char *path, int flags, int mode) { return open(path, flags, mode); }
int teleport_report_execve(const char *file, char *const *argv, char *const *env) { return execve(file, argv, env); }
int teleport_report_waitpid(int pid, int *status, int options) { return waitpid(pid, status, options); }
void *teleport_report_signal(int sig, void *handler) { return (void *) signal(sig, (void (*)(int)) handler); }
void teleport_report_raw_print(const char *text) { raw_print(text); }
void teleport_report_pline(const char *format, const char *text) { pline(format, text); }
int teleport_report_format(char *out, int kind, int number, const char *a, const char *b) {
    switch (kind) {
    case 0: return sprintf(out, "%%%02X", number);
    case 1: return sprintf(out, "?cos=%d&v=1", number);
    case 2: return sprintf(out, "%.40s report for NetHack %.40s", a, b);
    case 3: return sprintf(out, "%d", number);
    case 4: return sprintf(out, "Can't start " CRASHREPORT ": %.*s", number, a);
    default: abort();
    }
}

long teleport_report_readlink(const char *path, char *out, size_t size) { return (long) readlink(path, out, size); }
long teleport_report_read(int fd, void *out, size_t size) { return (long) read(fd, out, size); }
long teleport_report_write(int fd, const void *input, size_t size) { return (long) write(fd, input, size); }
int teleport_report_close(int fd) { return close(fd); }
int teleport_report_fork(void) { return fork(); }
void teleport_report_exit(int status) { exit(status); }
