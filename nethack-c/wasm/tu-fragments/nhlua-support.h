#ifndef TELEPORT_NHLUA_SUPPORT_H
#define TELEPORT_NHLUA_SUPPORT_H
#include "hack.h"
#include <stdint.h>
#include <setjmp.h>
typedef struct nhl_user_data {
    lua_State *L;       /* because the allocator needs it */
    uint32_t flags;     /* from nhl_sandbox_info */

    uint32_t memlimit;

    uint32_t steps;     /* current counter */
    uint32_t osteps;    /* original steps value */
    uint32_t perpcall;  /* per pcall steps value */

    /* stats */
    uint32_t statctr;   /* stats step reload count */
    int sid;            /* id number (per state) */
    const char *name;   /* for stats logging (per pcall) */

#ifdef NHL_SANDBOX
    jmp_buf jb;
#endif
} nhl_user_data;
enum ewhen {NEVER, IFFLAG, EOT};
struct e {enum ewhen when;const char *fnname;};
struct teleport_nhlua_anonymous_2057_14 {const char * name;int64_t value;};
struct teleport_nhlua_anonymous_2120_18 {const char * name;void * ptr;int type;};
struct teleport_nhlua_anonymous_342_14 {signed char ch;signed char typ;};
#endif
