#include "hack.h"
#include <stddef.h>
#include <limits.h>

#define WRITE_LAYOUT(name, value) { #name, value }
#define WRITE_OBJ(field) WRITE_LAYOUT(obj_##field, offsetof(struct obj, field)), WRITE_LAYOUT(obj_##field##_size, sizeof(((struct obj *) 0)->field))
#define WRITE_CLASS(field) WRITE_LAYOUT(class_##field, offsetof(struct objclass, field)), WRITE_LAYOUT(class_##field##_size, sizeof(((struct objclass *) 0)->field))
static const struct {
    const char *name;
    size_t value;
} write_layout[] = {
    WRITE_LAYOUT(pointerSize, sizeof(void *)), WRITE_LAYOUT(intSize, sizeof(int)),
    WRITE_LAYOUT(longSize, sizeof(long)), WRITE_LAYOUT(charSize, sizeof(char)),
    WRITE_LAYOUT(charSigned, (char) -1 < 0), WRITE_LAYOUT(CHAR_BIT, CHAR_BIT),
    WRITE_LAYOUT(booleanSize, sizeof(boolean)), WRITE_LAYOUT(booleanSigned, (boolean) -1 < 0),
    WRITE_LAYOUT(objectSize, sizeof(struct obj)), WRITE_OBJ(otyp), WRITE_OBJ(oclass), WRITE_OBJ(spe),
    WRITE_LAYOUT(objectClassSize, sizeof(struct objclass)),
    WRITE_CLASS(oc_name_idx), WRITE_CLASS(oc_descr_idx), WRITE_CLASS(oc_uname), WRITE_CLASS(oc_level),
    WRITE_LAYOUT(descriptorSize, sizeof(struct objdescr)),
    WRITE_LAYOUT(descriptorName, offsetof(struct objdescr, oc_name)),
    WRITE_LAYOUT(descriptorDescription, offsetof(struct objdescr, oc_descr)),
    WRITE_LAYOUT(bases, offsetof(__typeof__(svb), bases)), WRITE_LAYOUT(baseSize, sizeof svb.bases[0]),
    WRITE_LAYOUT(baseCount, sizeof svb.bases / sizeof svb.bases[0]),
    WRITE_LAYOUT(heroLevel, offsetof(struct you, ulevel)), WRITE_LAYOUT(heroLevelSize, sizeof u.ulevel),
    WRITE_LAYOUT(literate, offsetof(struct you, uconduct.literate)), WRITE_LAYOUT(literateSize, sizeof u.uconduct.literate),
    WRITE_LAYOUT(heroProps, offsetof(struct you, uprops)), WRITE_LAYOUT(propSize, sizeof(struct prop)),
    WRITE_LAYOUT(propIntrinsic, offsetof(struct prop, intrinsic)), WRITE_LAYOUT(propExtrinsic, offsetof(struct prop, extrinsic)),
    WRITE_LAYOUT(propBlocked, offsetof(struct prop, blocked)), WRITE_LAYOUT(propValueSize, sizeof(((struct prop *) 0)->intrinsic)),
    WRITE_LAYOUT(roleMonster, offsetof(__typeof__(gu), urole.mnum)), WRITE_LAYOUT(roleMonsterSize, sizeof gu.urole.mnum),
    WRITE_LAYOUT(youmonst, offsetof(__typeof__(gy), youmonst)), WRITE_LAYOUT(monsterData, offsetof(struct monst, data)),
    WRITE_LAYOUT(permonstFlags1, offsetof(struct permonst, mflags1)), WRITE_LAYOUT(permonstFlagsSize, sizeof(((struct permonst *) 0)->mflags1)),
    WRITE_LAYOUT(playerName, offsetof(__typeof__(svp), plname)), WRITE_LAYOUT(playerNameSize, sizeof svp.plname),
    WRITE_LAYOUT(NUM_OBJECTS, NUM_OBJECTS), WRITE_LAYOUT(MAXOCLASSES, MAXOCLASSES),
    WRITE_LAYOUT(TOOL_CLASS, TOOL_CLASS), WRITE_LAYOUT(SPE_FORCE_BOLT, SPE_FORCE_BOLT),
    WRITE_LAYOUT(PM_ARCHEOLOGIST, PM_ARCHEOLOGIST),
    WRITE_LAYOUT(M1_NOHANDS, M1_NOHANDS), WRITE_LAYOUT(BLINDED, BLINDED), WRITE_LAYOUT(GLIB, GLIB),
    WRITE_LAYOUT(HALLUC, HALLUC), WRITE_LAYOUT(HALLUC_RES, HALLUC_RES),
    WRITE_LAYOUT(spe_Unknown, spe_Unknown), WRITE_LAYOUT(spe_Fresh, spe_Fresh), WRITE_LAYOUT(spe_GoingStale, spe_GoingStale),
#ifdef MAIL_STRUCTURES
    WRITE_LAYOUT(MAIL_STRUCTURES, 1),
#else
    WRITE_LAYOUT(MAIL_STRUCTURES, 0),
#endif
    WRITE_LAYOUT(A_WIS, A_WIS),
    WRITE_LAYOUT(BUFSZ, BUFSZ),
    WRITE_LAYOUT(ECMD_CANCEL, ECMD_CANCEL),
    WRITE_LAYOUT(ECMD_OK, ECMD_OK),
    WRITE_LAYOUT(ECMD_TIME, ECMD_TIME),
    WRITE_LAYOUT(GETOBJ_DOWNPLAY, GETOBJ_DOWNPLAY),
    WRITE_LAYOUT(GETOBJ_EXCLUDE, GETOBJ_EXCLUDE),
    WRITE_LAYOUT(GETOBJ_NOFLAGS, GETOBJ_NOFLAGS),
    WRITE_LAYOUT(GETOBJ_SUGGEST, GETOBJ_SUGGEST),
    WRITE_LAYOUT(LL_CONDUCT, LL_CONDUCT),
    WRITE_LAYOUT(MAXULEV, MAXULEV),
    WRITE_LAYOUT(PM_WIZARD, PM_WIZARD),
    WRITE_LAYOUT(QBUFSZ, QBUFSZ),
    WRITE_LAYOUT(SCROLL_CLASS, SCROLL_CLASS),
    WRITE_LAYOUT(SCR_AMNESIA, SCR_AMNESIA),
    WRITE_LAYOUT(SCR_BLANK_PAPER, SCR_BLANK_PAPER),
    WRITE_LAYOUT(SCR_CHARGING, SCR_CHARGING),
    WRITE_LAYOUT(SCR_CONFUSE_MONSTER, SCR_CONFUSE_MONSTER),
    WRITE_LAYOUT(SCR_CREATE_MONSTER, SCR_CREATE_MONSTER),
    WRITE_LAYOUT(SCR_DESTROY_ARMOR, SCR_DESTROY_ARMOR),
    WRITE_LAYOUT(SCR_EARTH, SCR_EARTH),
    WRITE_LAYOUT(SCR_ENCHANT_ARMOR, SCR_ENCHANT_ARMOR),
    WRITE_LAYOUT(SCR_ENCHANT_WEAPON, SCR_ENCHANT_WEAPON),
    WRITE_LAYOUT(SCR_FIRE, SCR_FIRE),
    WRITE_LAYOUT(SCR_FOOD_DETECTION, SCR_FOOD_DETECTION),
    WRITE_LAYOUT(SCR_GENOCIDE, SCR_GENOCIDE),
    WRITE_LAYOUT(SCR_GOLD_DETECTION, SCR_GOLD_DETECTION),
    WRITE_LAYOUT(SCR_IDENTIFY, SCR_IDENTIFY),
    WRITE_LAYOUT(SCR_LIGHT, SCR_LIGHT),
    WRITE_LAYOUT(SCR_MAGIC_MAPPING, SCR_MAGIC_MAPPING),
#ifdef MAIL_STRUCTURES
    WRITE_LAYOUT(SCR_MAIL, SCR_MAIL),
#endif
    WRITE_LAYOUT(SCR_PUNISHMENT, SCR_PUNISHMENT),
    WRITE_LAYOUT(SCR_REMOVE_CURSE, SCR_REMOVE_CURSE),
    WRITE_LAYOUT(SCR_SCARE_MONSTER, SCR_SCARE_MONSTER),
    WRITE_LAYOUT(SCR_STINKING_CLOUD, SCR_STINKING_CLOUD),
    WRITE_LAYOUT(SCR_TAMING, SCR_TAMING),
    WRITE_LAYOUT(SCR_TELEPORTATION, SCR_TELEPORTATION),
    WRITE_LAYOUT(SPBOOK_CLASS, SPBOOK_CLASS),
    WRITE_LAYOUT(SPE_BLANK_PAPER, SPE_BLANK_PAPER),
    WRITE_LAYOUT(SPE_BOOK_OF_THE_DEAD, SPE_BOOK_OF_THE_DEAD),
    WRITE_LAYOUT(SPE_NOVEL, SPE_NOVEL),
};
#undef WRITE_LAYOUT
#undef WRITE_OBJ
#undef WRITE_CLASS

size_t probe_context_size(void) { return sizeof(struct obj); }
int probe_layout_count(void) { return sizeof write_layout / sizeof write_layout[0]; }
const char *probe_layout_name(int index) { return write_layout[index].name; }
size_t probe_layout_value(int index) { return write_layout[index].value; }
