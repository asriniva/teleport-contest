/* UNIXMAIN compiler header types only; no source data/policy. */
#ifndef TELEPORT_UNIXMAIN_TYPES_H
#define TELEPORT_UNIXMAIN_TYPES_H
#include <pwd.h>
#include <signal.h>
_Static_assert(sizeof(struct passwd)==48&&sizeof(struct sigaction)==152,"Review UNIXMAIN account/signal ABI");
#endif
