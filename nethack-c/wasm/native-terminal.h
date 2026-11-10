/* Native macOS terminal ABI for the JS game. Transport converts to SDK ABI. */
#pragma once
#ifdef __EMSCRIPTEN__
#define TELEPORT_NATIVE_PLATFORM_ABI 1
#pragma push_macro("tcgetattr")
#undef tcgetattr
#pragma push_macro("tcsetattr")
#undef tcsetattr
#pragma push_macro("cfgetospeed")
#undef cfgetospeed
#pragma push_macro("signal")
#undef signal
#pragma push_macro("kill")
#undef kill
#pragma push_macro("fpathconf")
#undef fpathconf
#pragma push_macro("ioctl")
#undef ioctl
#include <stdint.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <regex.h>
#pragma pop_macro("tcgetattr")
#pragma pop_macro("tcsetattr")
#pragma pop_macro("cfgetospeed")
#pragma pop_macro("signal")
#pragma pop_macro("kill")
#pragma pop_macro("fpathconf")
#pragma pop_macro("ioctl")
#define termios teleport_native_termios
#define tcflag_t uint64_t
#define speed_t uint64_t
#define cc_t uint8_t
#undef NCCS
#define NCCS 20
struct termios {tcflag_t c_iflag,c_oflag,c_cflag,c_lflag;cc_t c_cc[NCCS];speed_t c_ispeed,c_ospeed;};
#undef B0
#define B0 0
#undef B50
#define B50 50
#undef B75
#define B75 75
#undef B110
#define B110 110
#undef B134
#define B134 134
#undef B150
#define B150 150
#undef B200
#define B200 200
#undef B300
#define B300 300
#undef B600
#define B600 600
#undef B1200
#define B1200 1200
#undef B1800
#define B1800 1800
#undef B2400
#define B2400 2400
#undef B4800
#define B4800 4800
#undef B9600
#define B9600 9600
#undef B19200
#define B19200 19200
#undef B38400
#define B38400 38400
#undef ECHO
#define ECHO 8
#undef ICANON
#define ICANON 256
#undef ISTRIP
#define ISTRIP 32
#undef CS7
#define CS7 512
#undef TCSADRAIN
#define TCSADRAIN 1
#undef _PC_VDISABLE
#define _PC_VDISABLE 9
#undef VERASE
#define VERASE 3
#undef VKILL
#define VKILL 5
#undef VINTR
#define VINTR 8
#undef VMIN
#define VMIN 16
#undef VTIME
#define VTIME 17
#undef VSUSP
#define VSUSP 10
#undef VSWTCH
#undef VDSUSP
#define VDSUSP 11
#undef VREPRINT
#define VREPRINT 6
#undef VDISCARD
#define VDISCARD 15
#undef VWERASE
#define VWERASE 4
#undef VLNEXT
#define VLNEXT 14
#undef IGNBRK
#define IGNBRK 1
#undef BRKINT
#define BRKINT 2
#undef IGNPAR
#define IGNPAR 4
#undef PARMRK
#define PARMRK 8
#undef INPCK
#define INPCK 16
#undef ISTRIP
#define ISTRIP 32
#undef INLCR
#define INLCR 64
#undef IGNCR
#define IGNCR 128
#undef ICRNL
#define ICRNL 256
#undef IXON
#define IXON 512
#undef IXOFF
#define IXOFF 1024
#undef IXANY
#define IXANY 2048
#undef IMAXBEL
#define IMAXBEL 8192
#undef IUTF8
#define IUTF8 16384
#undef OPOST
#define OPOST 1
#undef ONLCR
#define ONLCR 2
#undef OCRNL
#define OCRNL 16
#undef ONOCR
#define ONOCR 32
#undef ONLRET
#define ONLRET 64
#undef OFILL
#define OFILL 128
#undef OFDEL
#define OFDEL 131072
#undef TABDLY
#define TABDLY 3076
#undef TAB0
#define TAB0 0
#undef TAB1
#define TAB1 1024
#undef TAB2
#define TAB2 2048
#undef TAB3
#define TAB3 4
#undef CLOCAL
#define CLOCAL 32768
#undef CREAD
#define CREAD 2048
#undef CSTOPB
#define CSTOPB 1024
#undef HUPCL
#define HUPCL 16384
#undef PARENB
#define PARENB 4096
#undef PARODD
#define PARODD 8192
#undef CSIZE
#define CSIZE 768
#undef CS5
#define CS5 0
#undef CS6
#define CS6 256
#undef CS7
#define CS7 512
#undef CS8
#define CS8 768
#undef CRTSCTS
#define CRTSCTS 196608
#undef CCTS_OFLOW
#define CCTS_OFLOW 65536
#undef CRTS_IFLOW
#define CRTS_IFLOW 131072
#undef CDSR_OFLOW
#define CDSR_OFLOW 524288
#undef CDTR_IFLOW
#define CDTR_IFLOW 262144
#undef CCAR_OFLOW
#define CCAR_OFLOW 1048576
#undef ECHO
#define ECHO 8
#undef ECHOE
#define ECHOE 2
#undef ECHOK
#define ECHOK 4
#undef ECHONL
#define ECHONL 16
#undef ICANON
#define ICANON 256
#undef ISIG
#define ISIG 128
#undef IEXTEN
#define IEXTEN 1024
#undef TOSTOP
#define TOSTOP 4194304
#undef NOFLSH
#define NOFLSH 2147483648
#undef ECHOKE
#define ECHOKE 1
#undef ECHOCTL
#define ECHOCTL 64
#undef PENDIN
#define PENDIN 536870912
#undef FLUSHO
#define FLUSHO 8388608
#undef EXTPROC
#define EXTPROC 2048
#undef VEOF
#define VEOF 0
#undef VEOL
#define VEOL 1
#undef VEOL2
#define VEOL2 2
#undef VERASE
#define VERASE 3
#undef VWERASE
#define VWERASE 4
#undef VKILL
#define VKILL 5
#undef VREPRINT
#define VREPRINT 6
#undef VINTR
#define VINTR 8
#undef VQUIT
#define VQUIT 9
#undef VSUSP
#define VSUSP 10
#undef VDSUSP
#define VDSUSP 11
#undef VSTART
#define VSTART 12
#undef VSTOP
#define VSTOP 13
#undef VLNEXT
#define VLNEXT 14
#undef VDISCARD
#define VDISCARD 15
#undef VMIN
#define VMIN 16
#undef VTIME
#define VTIME 17
#undef VSTATUS
#define VSTATUS 18
#undef TAB3
#define TAB3 4
#undef SIGHUP
#define SIGHUP 1
#undef SIGINT
#define SIGINT 2
#undef SIGQUIT
#define SIGQUIT 3
#undef SIGILL
#define SIGILL 4
#undef SIGTRAP
#define SIGTRAP 5
#undef SIGABRT
#define SIGABRT 6
#undef SIGEMT
#define SIGEMT 7
#undef SIGFPE
#define SIGFPE 8
#undef SIGKILL
#define SIGKILL 9
#undef SIGBUS
#define SIGBUS 10
#undef SIGSEGV
#define SIGSEGV 11
#undef SIGSYS
#define SIGSYS 12
#undef SIGPIPE
#define SIGPIPE 13
#undef SIGALRM
#define SIGALRM 14
#undef SIGTERM
#define SIGTERM 15
#undef SIGURG
#define SIGURG 16
#undef SIGSTOP
#define SIGSTOP 17
#undef SIGTSTP
#define SIGTSTP 18
#undef SIGCONT
#define SIGCONT 19
#undef SIGCHLD
#define SIGCHLD 20
#undef SIGTTIN
#define SIGTTIN 21
#undef SIGTTOU
#define SIGTTOU 22
#undef SIGIO
#define SIGIO 23
#undef SIGXCPU
#define SIGXCPU 24
#undef SIGXFSZ
#define SIGXFSZ 25
#undef SIGVTALRM
#define SIGVTALRM 26
#undef SIGPROF
#define SIGPROF 27
#undef SIGWINCH
#define SIGWINCH 28
#undef SIGINFO
#define SIGINFO 29
#undef SIGUSR1
#define SIGUSR1 30
#undef SIGUSR2
#define SIGUSR2 31
#undef SIG_IGN
#define SIG_IGN ((void (*)(int))1)
#undef TIOCGWINSZ
#define TIOCGWINSZ 0x40087468UL
#ifndef tcgetattr
#define tcgetattr teleport_native_tcgetattr
#endif
#ifndef tcsetattr
#define tcsetattr teleport_native_tcsetattr
#endif
#ifndef cfgetospeed
#define cfgetospeed teleport_native_cfgetospeed
#endif
#ifndef signal
#define signal teleport_native_signal
#endif
#ifndef kill
#define kill teleport_native_kill
#endif
#ifndef fpathconf
#define fpathconf teleport_native_fpathconf
#endif
#ifndef ioctl
#define ioctl teleport_native_ioctl
#endif
int tcgetattr(int,struct termios*);
int tcsetattr(int,int,const struct termios*);
speed_t cfgetospeed(const struct termios*);
void (*signal(int,void (*)(int)))(int);
int kill(pid_t,int);
long fpathconf(int,int);
int ioctl(int,unsigned long,...);
/* Opaque native regex storage is owned by the JS native ERE service. */
typedef struct {int re_magic;size_t re_nsub;const char *re_endp;void *re_g;} teleport_native_regex_t;
#define regex_t teleport_native_regex_t
#undef REG_NOSUB
#define REG_NOSUB 4
#undef REG_NEWLINE
#define REG_NEWLINE 8
#define regcomp teleport_native_regcomp
#define regexec teleport_native_regexec
#define regerror teleport_native_regerror
#define regfree teleport_native_regfree
int regcomp(regex_t*,const char*,int);
int regexec(const regex_t*,const char*,size_t,regmatch_t*,int);
size_t regerror(int,const regex_t*,char*,size_t);
void regfree(regex_t*);
#endif
