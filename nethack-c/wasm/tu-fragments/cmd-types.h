#ifndef TELEPORT_CMD_TYPES_H
#define TELEPORT_CMD_TYPES_H
#include "hack.h"
#include "func_tab.h"
#ifdef TELEPORT_CMD_REFERENCE_TYPES
typedef __typeof_unqual__(misc_keys[0]) cmd_misc_key;
#else
typedef struct {
    int nhkf;
    const char *desc;
    boolean numpad;
} cmd_misc_key;
#endif
#ifdef TELEPORT_CMD_REFERENCE_TYPES
typedef __typeof_unqual__(spkeys_binds[0]) cmd_spkey_bind;
#else
typedef struct {
    int nhkf;
    uchar key;
    const char *name;
} cmd_spkey_bind;
#endif
#ifndef TELEPORT_CMD_REFERENCE_TYPES
enum menucmd {
    MCMD_NOTHING = 0,
    MCMD_OPEN_DOOR,
    MCMD_LOCK_DOOR,
    MCMD_UNTRAP_DOOR,
    MCMD_KICK_DOOR,
    MCMD_CLOSE_DOOR,
    MCMD_SEARCH,
    MCMD_LOOK_TRAP,
    MCMD_UNTRAP_TRAP,
    MCMD_MOVE_DIR,
    MCMD_RIDE,
    MCMD_REMOVE_SADDLE,
    MCMD_APPLY_SADDLE,
    MCMD_TALK,
    MCMD_NAME,

    MCMD_QUAFF,
    MCMD_DIP,
    MCMD_SIT,
    MCMD_UP,
    MCMD_DOWN,
    MCMD_DISMOUNT,
    MCMD_MONABILITY,
    MCMD_PICKUP,
    MCMD_LOOT,
    MCMD_TIP,
    MCMD_EAT,
    MCMD_DROP,
    MCMD_REST,
    MCMD_LOOK_HERE,
    MCMD_LOOK_AT,
    MCMD_ATTACK_NEXT2U,
    MCMD_UNTRAP_HERE,
    MCMD_OFFER,
    MCMD_INVENTORY,
    MCMD_CAST_SPELL,

    MCMD_THROW_OBJ,
    MCMD_TRAVEL,
};
#endif
extern const char unavailcmd[26];
extern const char*levltyp[39];
extern struct ext_func_tab extcmdlist[171];
#endif
