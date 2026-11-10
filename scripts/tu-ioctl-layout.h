#include "hack.h"
#include <termios.h>
#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/ioctl.h>

/* Match the POSIX ioctl.c header-selection branch before testing TIOCGWINSZ. */
#if defined(POSIX_TYPES)
#if defined(BSD) || defined(_AIX32) || defined(__linux__)
#if defined(_AIX32) && !defined(_ALL_SOURCE)
#define _ALL_SOURCE
#endif
#include <sys/ioctl.h>
#endif
#endif
#if defined(AMIX) || defined(__APPLE__)
#include <sys/ioctl.h>
#endif

#if !defined(POSIX_TYPES) || defined(BSD_JOB_CONTROL) || defined(_BULL_SOURCE)
#error "Review the ioctl JS port for a changed terminal API configuration"
#endif
#if !defined(SUSPEND) || !defined(SYSCF) || defined(NO_SIGNAL) || defined(AUX)
#error "Review the ioctl JS port for a changed suspend configuration"
#endif

static const struct {
    const char *name;
    size_t value;
} ioctl_layout[] = {
    { "termioSize", sizeof(struct termios) },
    { "pointerSize", sizeof(void *) },
    { "intSize", sizeof(int) },
    { "TCSADRAIN", TCSADRAIN },
    { "SIGTSTP", SIGTSTP },
    { "POSIX_TYPES", 1 },
    { "SUSPEND", 1 },
    { "SYSCF", 1 },
    { "TIOCGWINSZ", TIOCGWINSZ },
    { "winsizeSize", sizeof(struct winsize) },
    { "winsizeRow", offsetof(struct winsize,ws_row) },
    { "winsizeColumn", offsetof(struct winsize,ws_col) },
#if defined(TIOCGWINSZ) && !defined(AVOID_WIN_IOCTL)
    { "USE_WIN_IOCTL", 1 },
#else
    { "USE_WIN_IOCTL", 0 },
#endif
};

size_t probe_context_size(void) { return sizeof(struct termios); }
int probe_layout_count(void) { return sizeof ioctl_layout / sizeof ioctl_layout[0]; }
const char *probe_layout_name(int index) { return ioctl_layout[index].name; }
size_t probe_layout_value(int index) { return ioctl_layout[index].value; }
uintptr_t probe_sig_default(void) { return (uintptr_t) SIG_DFL; }
uintptr_t probe_sig_ignore(void) { return (uintptr_t) SIG_IGN; }
uintptr_t probe_sig_error(void) { return (uintptr_t) SIG_ERR; }
