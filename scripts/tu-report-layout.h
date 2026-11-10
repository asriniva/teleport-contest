#include "hack.h"
#include "nhmd4.h"
#include "../nethack-c/wasm/tu-fragments/report.storage.h"
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <stddef.h>
struct report_layout_entry { const char *name; size_t value; };
#define REPORT_LAYOUT(name, value) { #name, value }
static const struct report_layout_entry report_layout[] = {
    REPORT_LAYOUT(bidSize, sizeof(((struct teleport_report_storage *)0)->bid)),
    REPORT_LAYOUT(pointerSize, sizeof(void *)), REPORT_LAYOUT(intSize, sizeof(int)),
    REPORT_LAYOUT(charSize, sizeof(char)), REPORT_LAYOUT(charSigned, (char)-1 < 0),
    REPORT_LAYOUT(md4Size, sizeof(NHMD4_CTX)),
    REPORT_LAYOUT(NHMD4_DIGEST_LENGTH, NHMD4_DIGEST_LENGTH), REPORT_LAYOUT(NHMD4_RESULTLEN, NHMD4_RESULTLEN),
    REPORT_LAYOUT(PATH_MAX, PATH_MAX), REPORT_LAYOUT(MAX_URL, sizeof(((struct teleport_report_storage *)0)->url)),
    REPORT_LAYOUT(DUMPLOG_MSG_COUNT, DUMPLOG_MSG_COUNT), REPORT_LAYOUT(O_RDONLY, O_RDONLY),
    REPORT_LAYOUT(START_ERROR_SIZE, sizeof "Can't start " CRASHREPORT ": "),
    REPORT_LAYOUT(ECMD_OK, ECMD_OK),
#ifdef CRASHREPORT
    REPORT_LAYOUT(CRASHREPORT, 1),
#else
    REPORT_LAYOUT(CRASHREPORT, 0),
#endif
#ifdef PANICTRACE
    REPORT_LAYOUT(PANICTRACE, 1),
#else
    REPORT_LAYOUT(PANICTRACE, 0),
#endif
#ifdef DUMPLOG_CORE
    REPORT_LAYOUT(DUMPLOG_CORE, 1),
#else
    REPORT_LAYOUT(DUMPLOG_CORE, 0),
#endif
#ifdef PANICTRACE_LIBC
    REPORT_LAYOUT(PANICTRACE_LIBC, 1),
#else
    REPORT_LAYOUT(PANICTRACE_LIBC, 0),
#endif
#ifdef PANICTRACE_GDB
    REPORT_LAYOUT(PANICTRACE_GDB, 1),
#else
    REPORT_LAYOUT(PANICTRACE_GDB, 0),
#endif
#ifdef WIN32
    REPORT_LAYOUT(WIN32, 1),
#else
    REPORT_LAYOUT(WIN32, 0),
#endif
#ifdef NO_SIGNAL
    REPORT_LAYOUT(NO_SIGNAL, 1),
#else
    REPORT_LAYOUT(NO_SIGNAL, 0),
#endif
#ifdef CRASHREPORT_EXEC_NOSTDERR
    REPORT_LAYOUT(CRASHREPORT_EXEC_NOSTDERR, 1),
#else
    REPORT_LAYOUT(CRASHREPORT_EXEC_NOSTDERR, 0),
#endif
#ifdef SIGILL
    REPORT_LAYOUT(SIGILL, SIGILL),
#endif
#ifdef SIGTRAP
    REPORT_LAYOUT(SIGTRAP, SIGTRAP),
#endif
#ifdef SIGIOT
    REPORT_LAYOUT(SIGIOT, SIGIOT),
#endif
#ifdef SIGBUS
    REPORT_LAYOUT(SIGBUS, SIGBUS),
#endif
#ifdef SIGFPE
    REPORT_LAYOUT(SIGFPE, SIGFPE),
#endif
#ifdef SIGSEGV
    REPORT_LAYOUT(SIGSEGV, SIGSEGV),
#endif
#ifdef SIGSTKFLT
    REPORT_LAYOUT(SIGSTKFLT, SIGSTKFLT),
#endif
#ifdef SIGSYS
    REPORT_LAYOUT(SIGSYS, SIGSYS),
#endif
#ifdef SIGEMT
    REPORT_LAYOUT(SIGEMT, SIGEMT),
#endif
};
#undef REPORT_LAYOUT
