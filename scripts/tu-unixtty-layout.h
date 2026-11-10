#include "hack.h"
#include <termios.h>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>

#if !defined(POSIX_TYPES) || defined(BSD) || defined(AUX) || defined(LINUX) || defined(__linux__)
#error "Review unixtty JS implementation for changed platform terminal configuration"
#endif

#define UNIXTTY_LAYOUT(name, value) { #name, value }
static const struct {
    const char *name;
    size_t value;
} unixtty_layout[] = {
    UNIXTTY_LAYOUT(termioSize, sizeof(struct termios)),
    UNIXTTY_LAYOUT(c_iflag, offsetof(struct termios, c_iflag)),
    UNIXTTY_LAYOUT(c_oflag, offsetof(struct termios, c_oflag)),
    UNIXTTY_LAYOUT(c_cflag, offsetof(struct termios, c_cflag)),
    UNIXTTY_LAYOUT(c_lflag, offsetof(struct termios, c_lflag)),
    UNIXTTY_LAYOUT(c_cc, offsetof(struct termios, c_cc)),
    UNIXTTY_LAYOUT(ccCount, sizeof(((struct termios *) 0)->c_cc) / sizeof(cc_t)),
    UNIXTTY_LAYOUT(ccSize, sizeof(cc_t)),
    UNIXTTY_LAYOUT(tcflagSize, sizeof(tcflag_t)),
    UNIXTTY_LAYOUT(speedSize, sizeof(speed_t)),
    UNIXTTY_LAYOUT(pointerSize, sizeof(void *)),
    UNIXTTY_LAYOUT(intSize, sizeof(int)),
    UNIXTTY_LAYOUT(charSize, sizeof(char)),
    UNIXTTY_LAYOUT(charSigned, (char) -1 < 0),
    UNIXTTY_LAYOUT(CHAR_BIT, CHAR_BIT),
    UNIXTTY_LAYOUT(POSIX_TYPES, 1),
    UNIXTTY_LAYOUT(USG, 1),
    UNIXTTY_LAYOUT(BSD, 0), UNIXTTY_LAYOUT(AUX, 0), UNIXTTY_LAYOUT(LINUX, 0),
    UNIXTTY_LAYOUT(B0, B0), UNIXTTY_LAYOUT(B50, B50), UNIXTTY_LAYOUT(B75, B75),
    UNIXTTY_LAYOUT(B110, B110), UNIXTTY_LAYOUT(B134, B134), UNIXTTY_LAYOUT(B150, B150),
    UNIXTTY_LAYOUT(B200, B200), UNIXTTY_LAYOUT(B300, B300), UNIXTTY_LAYOUT(B600, B600),
    UNIXTTY_LAYOUT(B1200, B1200), UNIXTTY_LAYOUT(B1800, B1800), UNIXTTY_LAYOUT(B2400, B2400),
    UNIXTTY_LAYOUT(B4800, B4800), UNIXTTY_LAYOUT(B9600, B9600),
    UNIXTTY_LAYOUT(B19200, B19200), UNIXTTY_LAYOUT(B38400, B38400),
    UNIXTTY_LAYOUT(ECHO, ECHO), UNIXTTY_LAYOUT(ICANON, ICANON),
    UNIXTTY_LAYOUT(CBRKMASK, ICANON),
#ifdef TAB3
    UNIXTTY_LAYOUT(EXTABS, TAB3),
#else
    UNIXTTY_LAYOUT(EXTABS, 0),
#endif
    UNIXTTY_LAYOUT(STRIPHI, ISTRIP), UNIXTTY_LAYOUT(ISTRIP, ISTRIP),
    UNIXTTY_LAYOUT(CS7, CS7), UNIXTTY_LAYOUT(TCSADRAIN, TCSADRAIN),
    UNIXTTY_LAYOUT(_PC_VDISABLE, _PC_VDISABLE),
    UNIXTTY_LAYOUT(VERASE, VERASE), UNIXTTY_LAYOUT(VKILL, VKILL),
    UNIXTTY_LAYOUT(VINTR, VINTR), UNIXTTY_LAYOUT(VMIN, VMIN), UNIXTTY_LAYOUT(VTIME, VTIME),
#ifdef VSUSP
    UNIXTTY_LAYOUT(HAS_VSUSP, 1), UNIXTTY_LAYOUT(VSUSP, VSUSP),
#else
    UNIXTTY_LAYOUT(HAS_VSUSP, 0), UNIXTTY_LAYOUT(VSUSP, 0),
#endif
#ifdef VSWTCH
    UNIXTTY_LAYOUT(HAS_VSWTCH, 1), UNIXTTY_LAYOUT(VSWTCH, VSWTCH),
#else
    UNIXTTY_LAYOUT(HAS_VSWTCH, 0), UNIXTTY_LAYOUT(VSWTCH, 0),
#endif
#ifdef VDSUSP
    UNIXTTY_LAYOUT(HAS_VDSUSP, 1), UNIXTTY_LAYOUT(VDSUSP, VDSUSP),
#else
    UNIXTTY_LAYOUT(HAS_VDSUSP, 0), UNIXTTY_LAYOUT(VDSUSP, 0),
#endif
#ifdef VREPRINT
    UNIXTTY_LAYOUT(HAS_VREPRINT, 1), UNIXTTY_LAYOUT(VREPRINT, VREPRINT),
#else
    UNIXTTY_LAYOUT(HAS_VREPRINT, 0), UNIXTTY_LAYOUT(VREPRINT, 0),
#endif
#ifdef VDISCARD
    UNIXTTY_LAYOUT(HAS_VDISCARD, 1), UNIXTTY_LAYOUT(VDISCARD, VDISCARD),
#else
    UNIXTTY_LAYOUT(HAS_VDISCARD, 0), UNIXTTY_LAYOUT(VDISCARD, 0),
#endif
#ifdef VWERASE
    UNIXTTY_LAYOUT(HAS_VWERASE, 1), UNIXTTY_LAYOUT(VWERASE, VWERASE),
#else
    UNIXTTY_LAYOUT(HAS_VWERASE, 0), UNIXTTY_LAYOUT(VWERASE, 0),
#endif
#ifdef VLNEXT
    UNIXTTY_LAYOUT(HAS_VLNEXT, 1), UNIXTTY_LAYOUT(VLNEXT, VLNEXT),
#else
    UNIXTTY_LAYOUT(HAS_VLNEXT, 0), UNIXTTY_LAYOUT(VLNEXT, 0),
#endif
#ifdef POSIX_JOB_CONTROL
    UNIXTTY_LAYOUT(POSIX_JOB_CONTROL, 1),
#else
    UNIXTTY_LAYOUT(POSIX_JOB_CONTROL, 0),
#endif
#ifdef TTY_GRAPHICS
    UNIXTTY_LAYOUT(TTY_GRAPHICS, 1),
#else
    UNIXTTY_LAYOUT(TTY_GRAPHICS, 0),
#endif
#ifdef ENHANCED_SYMBOLS
    UNIXTTY_LAYOUT(ENHANCED_SYMBOLS, 1),
#else
    UNIXTTY_LAYOUT(ENHANCED_SYMBOLS, 0),
#endif
    UNIXTTY_LAYOUT(wp_tty, wp_tty), UNIXTTY_LAYOUT(EXIT_FAILURE, EXIT_FAILURE),
};
#undef UNIXTTY_LAYOUT

size_t probe_context_size(void) { return sizeof(struct termios); }
int probe_layout_count(void) { return sizeof unixtty_layout / sizeof unixtty_layout[0]; }
const char *probe_layout_name(int index) { return unixtty_layout[index].name; }
size_t probe_layout_value(int index) { return unixtty_layout[index].value; }
