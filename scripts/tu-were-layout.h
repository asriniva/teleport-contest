#include "hack.h"
#include <stddef.h>
#include <limits.h>

#define WERE_LAYOUT(name, value) { #name, value }
#define WERE_MON_FIELD(field) WERE_LAYOUT(mon_##field, offsetof(struct monst, field)), WERE_LAYOUT(mon_##field##_size, sizeof(((struct monst *) 0)->field))
#define WERE_HERO_FIELD(field) WERE_LAYOUT(hero_##field, offsetof(struct you, field)), WERE_LAYOUT(hero_##field##_size, sizeof(((struct you *) 0)->field))
static const struct {
    const char *name;
    size_t value;
} were_layout[] = {
    WERE_LAYOUT(pointerSize, sizeof(void *)), WERE_LAYOUT(intSize, sizeof(int)),
    WERE_LAYOUT(longSize, sizeof(long)),
    WERE_LAYOUT(booleanSize, sizeof(boolean)), WERE_LAYOUT(booleanSigned, (boolean) -1 < 0), WERE_LAYOUT(CHAR_BIT, CHAR_BIT),
    WERE_LAYOUT(permonstSize, sizeof(struct permonst)),
    WERE_LAYOUT(permonstNames, offsetof(struct permonst, pmnames)),
    WERE_LAYOUT(permonstIndex, offsetof(struct permonst, pmidx)),
    WERE_LAYOUT(permonstIndexSize, sizeof(((struct permonst *) 0)->pmidx)),
    WERE_LAYOUT(permonstFlags2, offsetof(struct permonst, mflags2)),
    WERE_LAYOUT(permonstFlags2Size, sizeof(((struct permonst *) 0)->mflags2)),
    WERE_LAYOUT(monsterSize, sizeof(struct monst)),
    WERE_MON_FIELD(data), WERE_MON_FIELD(mx), WERE_MON_FIELD(my),
    WERE_MON_FIELD(mux), WERE_MON_FIELD(muy), WERE_MON_FIELD(mhp), WERE_MON_FIELD(mhpmax),
    WERE_HERO_FIELD(ux), WERE_HERO_FIELD(uy), WERE_HERO_FIELD(umonnum),
    WERE_HERO_FIELD(ulycn), WERE_HERO_FIELD(mtimedone),
    WERE_LAYOUT(heroProps, offsetof(struct you, uprops)),
    WERE_LAYOUT(propSize, sizeof(struct prop)),
    WERE_LAYOUT(propIntrinsic, offsetof(struct prop, intrinsic)),
    WERE_LAYOUT(propExtrinsic, offsetof(struct prop, extrinsic)),
    WERE_LAYOUT(propValueSize, sizeof(((struct prop *) 0)->intrinsic)),
    WERE_LAYOUT(flagsMoonphase, offsetof(__typeof__(flags), moonphase)),
    WERE_LAYOUT(flagsMoonphaseSize, sizeof flags.moonphase),
    WERE_LAYOUT(flagsParanoia, offsetof(__typeof__(flags), paranoia_bits)),
    WERE_LAYOUT(flagsParanoiaSize, sizeof flags.paranoia_bits),
    WERE_LAYOUT(wereChanges, offsetof(__typeof__(gw), were_changes)),
    WERE_LAYOUT(wereChangesSize, sizeof gw.were_changes),
    WERE_LAYOUT(contextMonMoving, offsetof(__typeof__(svc), context.mon_moving)),
    WERE_LAYOUT(contextMonMovingSize, sizeof svc.context.mon_moving),
    WERE_LAYOUT(youmonst, offsetof(__typeof__(gy), youmonst)),
    WERE_LAYOUT(multi, offsetof(__typeof__(gm), multi)),
    WERE_LAYOUT(multiSize, sizeof gm.multi),
    WERE_LAYOUT(NUMMONS, NUMMONS), WERE_LAYOUT(NUM_MGENDERS, NUM_MGENDERS),
    WERE_LAYOUT(M2_WERE, M2_WERE), WERE_LAYOUT(M2_HUMAN, M2_HUMAN),
    WERE_LAYOUT(NEUTRAL, NEUTRAL), WERE_LAYOUT(LOW_PM, LOW_PM), WERE_LAYOUT(NON_PM, NON_PM),
    WERE_LAYOUT(FULL_MOON, FULL_MOON), WERE_LAYOUT(QBUFSZ, QBUFSZ),
    WERE_LAYOUT(NO_MM_FLAGS, NO_MM_FLAGS),
    WERE_LAYOUT(STUNNED, STUNNED), WERE_LAYOUT(HALLUC, HALLUC),
    WERE_LAYOUT(HALLUC_RES, HALLUC_RES), WERE_LAYOUT(DEAF, DEAF),
    WERE_LAYOUT(PROT_FROM_SHAPE_CHANGERS, PROT_FROM_SHAPE_CHANGERS),
    WERE_LAYOUT(POLYMORPH_CONTROL, POLYMORPH_CONTROL), WERE_LAYOUT(UNCHANGING, UNCHANGING),
    WERE_LAYOUT(PARANOID_WERECHANGE, PARANOID_WERECHANGE),
    WERE_LAYOUT(PM_WEREWOLF, PM_WEREWOLF), WERE_LAYOUT(PM_HUMAN_WEREWOLF, PM_HUMAN_WEREWOLF),
    WERE_LAYOUT(PM_WEREJACKAL, PM_WEREJACKAL), WERE_LAYOUT(PM_HUMAN_WEREJACKAL, PM_HUMAN_WEREJACKAL),
    WERE_LAYOUT(PM_WERERAT, PM_WERERAT), WERE_LAYOUT(PM_HUMAN_WERERAT, PM_HUMAN_WERERAT),
    WERE_LAYOUT(PM_SEWER_RAT, PM_SEWER_RAT), WERE_LAYOUT(PM_GIANT_RAT, PM_GIANT_RAT),
    WERE_LAYOUT(PM_RABID_RAT, PM_RABID_RAT), WERE_LAYOUT(PM_JACKAL, PM_JACKAL),
    WERE_LAYOUT(PM_FOX, PM_FOX), WERE_LAYOUT(PM_COYOTE, PM_COYOTE),
    WERE_LAYOUT(PM_WOLF, PM_WOLF), WERE_LAYOUT(PM_WARG, PM_WARG),
    WERE_LAYOUT(PM_WINTER_WOLF, PM_WINTER_WOLF), WERE_LAYOUT(PM_WINTER_WOLF_CUB, PM_WINTER_WOLF_CUB),
};
#undef WERE_LAYOUT
#undef WERE_MON_FIELD
#undef WERE_HERO_FIELD

size_t probe_context_size(void) { return sizeof(struct monst); }
int probe_layout_count(void) { return sizeof were_layout / sizeof were_layout[0]; }
const char *probe_layout_name(int index) { return were_layout[index].name; }
size_t probe_layout_value(int index) { return were_layout[index].value; }
