#ifndef TELEPORT_SP_LEV_TYPES_H
#define TELEPORT_SP_LEV_TYPES_H
#include "hack.h"
#include "sp_lev.h"
#ifdef TELEPORT_SP_LEV_REFERENCE_TYPES
typedef __typeof_unqual__(room_types[0]) sp_lev_room_type;
#else
typedef struct {
    const char *name;
    int type;
} sp_lev_room_type;
#endif
#ifdef TELEPORT_SP_LEV_REFERENCE_TYPES
typedef __typeof_unqual__(trap_types[0]) sp_lev_trap_type;
#else
typedef struct {
    const char *name;
    int type;
} sp_lev_trap_type;
#endif
typedef struct sp_lev_objclasspfx {
            const char *prefix;
            char class;
        } sp_lev_objclasspfx;
typedef __typeof__(((corridor*)0)->src) sp_lev_corridor_end;
typedef __typeof__(((lev_region*)0)->inarea) sp_lev_lregion_inarea;
typedef __typeof__(((lev_region*)0)->delarea) sp_lev_lregion_delarea;
#endif
