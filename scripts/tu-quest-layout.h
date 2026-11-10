#include "hack.h"
#include "quest.h"
#include <stddef.h>
#include <limits.h>

#define QUEST_LAYOUT(name, value) { #name, value }
#define QUEST_MON(field) QUEST_LAYOUT(mon_##field, offsetof(struct monst, field)), QUEST_LAYOUT(mon_##field##_size, sizeof(((struct monst *) 0)->field))
static const struct { const char *name; size_t value; } quest_layout[] = {
    QUEST_LAYOUT(pointerSize, sizeof(void *)), QUEST_LAYOUT(intSize, sizeof(int)),
    QUEST_LAYOUT(longSize, sizeof(long)), QUEST_LAYOUT(charSize, sizeof(char)),
    QUEST_LAYOUT(charSigned, (char) -1 < 0), QUEST_LAYOUT(CHAR_BIT, CHAR_BIT),
    QUEST_LAYOUT(booleanSize, sizeof(boolean)), QUEST_LAYOUT(booleanSigned, (boolean) -1 < 0),
    QUEST_LAYOUT(coordxySize, sizeof(coordxy)), QUEST_LAYOUT(coordxySigned, (coordxy) -1 < 0),
    QUEST_LAYOUT(heroUx, offsetof(struct you, ux)), QUEST_LAYOUT(heroUy, offsetof(struct you, uy)),
    QUEST_LAYOUT(heroLevel, offsetof(struct you, ulevel)), QUEST_LAYOUT(heroLevelSize, sizeof u.ulevel),
    QUEST_LAYOUT(heroUz, offsetof(struct you, uz)), QUEST_LAYOUT(heroUz0, offsetof(struct you, uz0)),
    QUEST_LAYOUT(heroAlignType, offsetof(struct you, ualign.type)), QUEST_LAYOUT(heroAlignTypeSize, sizeof u.ualign.type),
    QUEST_LAYOUT(heroAlignRecord, offsetof(struct you, ualign.record)), QUEST_LAYOUT(heroAlignRecordSize, sizeof u.ualign.record),
    QUEST_LAYOUT(heroAlignBase, offsetof(struct you, ualignbase)), QUEST_LAYOUT(heroAlignBaseSize, sizeof u.ualignbase[0]),
    QUEST_LAYOUT(heroAlignBaseCount, sizeof u.ualignbase / sizeof u.ualignbase[0]),
    QUEST_LAYOUT(heroProps, offsetof(struct you, uprops)), QUEST_LAYOUT(propSize, sizeof(struct prop)),
    QUEST_LAYOUT(propIntrinsic, offsetof(struct prop, intrinsic)), QUEST_LAYOUT(propExtrinsic, offsetof(struct prop, extrinsic)),
    QUEST_LAYOUT(propValueSize, sizeof(((struct prop *) 0)->intrinsic)), QUEST_LAYOUT(DEAF, DEAF),
    QUEST_LAYOUT(leaderId, offsetof(__typeof__(svq), quest_status.leader_m_id)),
    QUEST_LAYOUT(leaderIdSize, sizeof svq.quest_status.leader_m_id),
    QUEST_LAYOUT(questDungeon, offsetof(__typeof__(svd), dungeon_topology.d_quest_dnum)),
    QUEST_LAYOUT(questDungeonSize, sizeof quest_dnum),
    QUEST_LAYOUT(startLevel, offsetof(__typeof__(svd), dungeon_topology.d_qstart_level)),
    QUEST_LAYOUT(locateLevel, offsetof(__typeof__(svd), dungeon_topology.d_qlocate_level)),
    QUEST_LAYOUT(nemesisLevel, offsetof(__typeof__(svd), dungeon_topology.d_nemesis_level)),
    QUEST_LAYOUT(levelSize, sizeof(d_level)), QUEST_LAYOUT(levelDnum, offsetof(d_level, dnum)),
    QUEST_LAYOUT(levelDlevel, offsetof(d_level, dlevel)), QUEST_LAYOUT(levelFieldSize, sizeof(((d_level *) 0)->dnum)),
    QUEST_LAYOUT(monMoving, offsetof(__typeof__(svc), context.mon_moving)), QUEST_LAYOUT(monMovingSize, sizeof svc.context.mon_moving),
    QUEST_LAYOUT(debug, offsetof(__typeof__(flags), debug)), QUEST_LAYOUT(debugSize, sizeof flags.debug),
    QUEST_LAYOUT(inventory, offsetof(__typeof__(gi), invent)), QUEST_LAYOUT(traps, offsetof(__typeof__(gf), ftrap)),
    QUEST_LAYOUT(monsterSize, sizeof(struct monst)), QUEST_MON(data), QUEST_MON(m_id), QUEST_MON(mstrategy),
    QUEST_LAYOUT(permonstSize, sizeof(struct permonst)), QUEST_LAYOUT(monsterSound, offsetof(struct permonst, msound)),
    QUEST_LAYOUT(monsterSoundSize, sizeof(((struct permonst *) 0)->msound)), QUEST_LAYOUT(NUMMONS, NUMMONS),
    QUEST_LAYOUT(MS_LEADER, MS_LEADER),
    QUEST_LAYOUT(objectSize, sizeof(struct obj)), QUEST_LAYOUT(objectNext, offsetof(struct obj, nobj)),
    QUEST_LAYOUT(objectType, offsetof(struct obj, otyp)), QUEST_LAYOUT(objectTypeSize, sizeof(((struct obj *) 0)->otyp)),
    QUEST_LAYOUT(trapSize, sizeof(struct trap)), QUEST_LAYOUT(trapNext, offsetof(struct trap, ntrap)),
    QUEST_LAYOUT(branchSize, sizeof(branch)), QUEST_LAYOUT(branchEnd1, offsetof(branch, end1)), QUEST_LAYOUT(branchEnd2, offsetof(branch, end2)),
    QUEST_LAYOUT(AMULET_OF_YENDOR, AMULET_OF_YENDOR),
    QUEST_LAYOUT(A_CURRENT, A_CURRENT),
    QUEST_LAYOUT(A_ORIGINAL, A_ORIGINAL),
    QUEST_LAYOUT(A_WIS, A_WIS),
    QUEST_LAYOUT(BELL_OF_OPENING, BELL_OF_OPENING),
    QUEST_LAYOUT(FAKE_AMULET_OF_YENDOR, FAKE_AMULET_OF_YENDOR),
    QUEST_LAYOUT(LL_ACHIEVE, LL_ACHIEVE),
    QUEST_LAYOUT(MAGIC_PORTAL, MAGIC_PORTAL),
    QUEST_LAYOUT(MIN_QUEST_ALIGN, MIN_QUEST_ALIGN),
    QUEST_LAYOUT(MIN_QUEST_LEVEL, MIN_QUEST_LEVEL),
    QUEST_LAYOUT(MS_DJINNI, MS_DJINNI),
    QUEST_LAYOUT(MS_GUARDIAN, MS_GUARDIAN),
    QUEST_LAYOUT(MS_NEMESIS, MS_NEMESIS),
    QUEST_LAYOUT(OBJ_BURIED, OBJ_BURIED),
    QUEST_LAYOUT(OBJ_FLOOR, OBJ_FLOOR),
    QUEST_LAYOUT(OBJ_MINVENT, OBJ_MINVENT),
    QUEST_LAYOUT(PM_PRISONER, PM_PRISONER),
    QUEST_LAYOUT(STRAT_WAITMASK, STRAT_WAITMASK),
    QUEST_LAYOUT(UTOTYPE_NONE, UTOTYPE_NONE),
    QUEST_LAYOUT(UTOTYPE_PORTAL, UTOTYPE_PORTAL),
    QUEST_LAYOUT(UTOTYPE_RMPORTAL, UTOTYPE_RMPORTAL),
};
#undef QUEST_LAYOUT
#undef QUEST_MON
size_t probe_context_size(void) { return sizeof(struct q_score); }
int probe_layout_count(void) { return sizeof quest_layout / sizeof quest_layout[0]; }
const char *probe_layout_name(int index) { return quest_layout[index].name; }
size_t probe_layout_value(int index) { return quest_layout[index].value; }
