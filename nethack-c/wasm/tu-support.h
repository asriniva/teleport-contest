#ifndef TELEPORT_TU_SUPPORT_H
#define TELEPORT_TU_SUPPORT_H
#include "hack.h"
#include "tu-source-locations.h"

/* Addressable storage for JS track.c while C callers and save APIs still use
 * int/coord addresses. Storage only: the algorithm lives in the JS TU. */
struct teleport_track_state {
    int utcnt, utpnt;
    coord utrack[TELEPORT_TRACK_UTSZ];
};
extern void *teleport_track_state_pointer(void);
#endif
