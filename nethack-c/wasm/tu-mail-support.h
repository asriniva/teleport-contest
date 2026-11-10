#ifndef TELEPORT_MAIL_SUPPORT_H
#define TELEPORT_MAIL_SUPPORT_H
#include "hack.h"
#include "mail.h"
#include <sys/stat.h>
#include <pwd.h>
/* Original file-local configured path macros, shared by ABI metadata only. */
#if !defined(MAILPATH) && defined(AMS) /* Just a placeholder for AMS */
#define MAILPATH "/dev/null"
#endif
#if !defined(MAILPATH) && (defined(LINUX) || defined(__osf__))
#define MAILPATH "/var/spool/mail/"
#endif
#if !defined(MAILPATH) && defined(__FreeBSD__)
#define MAILPATH "/var/mail/"
#endif
#if !defined(MAILPATH) && (defined(BSD) || defined(ULTRIX))
#define MAILPATH "/usr/spool/mail/"
#endif
#if !defined(MAILPATH) && (defined(SYSV) || defined(HPUX))
#define MAILPATH "/usr/mail/"
#endif

#endif
