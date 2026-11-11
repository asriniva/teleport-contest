/* Original BOTL owner, with observation-only helpers in its own translation unit. */
#include "botl.c"
#define TELEPORT_BOTL_ORIGINAL_DECLARED
#include "tu-botl-abi.h"
const void *probe_status_storage(int i){switch(i){case 0:return initblstats;case 1:return conditions;case 2:return condtests;case 3:return cond_idx;case 4:return enc_stat;case 5:return terrain_descr;case 6:return &gb;case 7:return &iflags;case 8:return &gu;case 9:return &disp;case 10:return &WIN_MESSAGE;case 11:return &WIN_STATUS;case 12:return &WIN_MAP;case 13:return &WIN_INVEN;}return NULL;}
unsigned long probe_status_size(int i){const unsigned long sizes[]={sizeof initblstats,sizeof conditions,sizeof condtests,sizeof cond_idx,sizeof enc_stat,sizeof terrain_descr,sizeof gb,sizeof iflags,sizeof gu,sizeof disp,sizeof WIN_MESSAGE,sizeof WIN_STATUS,sizeof WIN_MAP,sizeof WIN_INVEN};return sizes[i];}
uintptr_t probe_status_callback(int i){return i?(uintptr_t)menualpha_cmp:(uintptr_t)cond_cmp;}
