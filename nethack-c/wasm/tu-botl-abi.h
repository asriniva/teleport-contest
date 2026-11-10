#ifndef TELEPORT_BOTL_ABI_H
#define TELEPORT_BOTL_ABI_H
#include "hack.h"
#include <stddef.h>
struct teleport_botl_fieldid_t {
    const char *fieldname;
    enum statusfields fldid;
};
struct teleport_botl__status_hilite_line_str {
    int id;
    int fld;
    struct hilite_s *hl;
    unsigned long mask;
    char str[BUFSZ];
    struct teleport_botl__status_hilite_line_str *next;
};
struct teleport_botl__cond_map {
    unsigned long bm;
    unsigned int clratr;
};
extern const char *const enc_stat[6];
extern const char *terrain_descr[47];
extern const char *const hu_stat[];
#ifdef TELEPORT_BOTL_ORIGINAL_DECLARED
_Static_assert(sizeof(struct teleport_botl_fieldid_t)==sizeof(struct fieldid_t),"BOTL fieldid size");
_Static_assert(offsetof(struct teleport_botl_fieldid_t,fldid)==offsetof(struct fieldid_t,fldid),"BOTL fieldid member");
_Static_assert(sizeof(struct teleport_botl__status_hilite_line_str)==sizeof(struct _status_hilite_line_str),"BOTL private line size");
_Static_assert(offsetof(struct teleport_botl__status_hilite_line_str,next)==offsetof(struct _status_hilite_line_str,next),"BOTL private line link");
#endif
#endif
