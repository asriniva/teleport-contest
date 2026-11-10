#include "hack.h"
#include <stddef.h>
#include <limits.h>

#define MP_LAYOUT(name, value) { #name, value }
#define MP_MON(field) MP_LAYOUT(mon_##field, offsetof(struct monst, field)), MP_LAYOUT(mon_##field##_size, sizeof(((struct monst *) 0)->field))
#define MP_OBJ(field) MP_LAYOUT(obj_##field, offsetof(struct obj, field)), MP_LAYOUT(obj_##field##_size, sizeof(((struct obj *) 0)->field))
static const struct {
    const char *name;
    size_t value;
} mplayer_layout[] = {
    MP_LAYOUT(pointerSize, sizeof(void *)), MP_LAYOUT(intSize, sizeof(int)),
    MP_LAYOUT(longSize, sizeof(long)), MP_LAYOUT(shortSize, sizeof(short)),
    MP_LAYOUT(charSize, sizeof(char)), MP_LAYOUT(charSigned, (char) -1 < 0),
    MP_LAYOUT(CHAR_BIT, CHAR_BIT), MP_LAYOUT(booleanSize, sizeof(boolean)),
    MP_LAYOUT(booleanSigned, (boolean) -1 < 0),
    MP_LAYOUT(coordxySize, sizeof(coordxy)), MP_LAYOUT(coordxySigned, (coordxy) -1 < 0),
    MP_LAYOUT(monsterSize, sizeof(struct monst)),
    MP_MON(nmon), MP_MON(data), MP_MON(mextra), MP_MON(m_lev), MP_MON(mhp), MP_MON(mhpmax),
    MP_LAYOUT(givenName, offsetof(struct mextra, mgivenname)),
    MP_LAYOUT(permonstSize, sizeof(struct permonst)),
    MP_LAYOUT(permonstIndex, offsetof(struct permonst, pmidx)),
    MP_LAYOUT(permonstIndexSize, sizeof(((struct permonst *) 0)->pmidx)),
    MP_LAYOUT(permonstFlags2, offsetof(struct permonst, mflags2)),
    MP_LAYOUT(permonstFlags2Size, sizeof(((struct permonst *) 0)->mflags2)),
    MP_LAYOUT(objectSize, sizeof(struct obj)),
    MP_OBJ(otyp), MP_OBJ(oartifact), MP_OBJ(oclass), MP_OBJ(quan), MP_OBJ(owt), MP_OBJ(spe),
    MP_LAYOUT(objectClassSize, sizeof(struct objclass)),
    MP_LAYOUT(objectSkill, offsetof(struct objclass, oc_skill)),
    MP_LAYOUT(objectSkillSize, sizeof(((struct objclass *) 0)->oc_skill)),
    MP_LAYOUT(monlist, offsetof(__typeof__(svl), level.monlist)),
    MP_LAYOUT(monsters, offsetof(__typeof__(svl), level.monsters)),
    MP_LAYOUT(heroLevel, offsetof(struct you, uz)),
    MP_LAYOUT(levelSize, sizeof(d_level)),
    MP_LAYOUT(levelDnum, offsetof(d_level, dnum)), MP_LAYOUT(levelDlevel, offsetof(d_level, dlevel)),
    MP_LAYOUT(levelFieldSize, sizeof(((d_level *) 0)->dnum)),
    MP_LAYOUT(roleMonster, offsetof(__typeof__(gu), urole.mnum)),
    MP_LAYOUT(roleMonsterSize, sizeof gu.urole.mnum),
    MP_LAYOUT(zeroMonster, offsetof(__typeof__(cg), zeromonst)),
    MP_LAYOUT(astralLevel, offsetof(__typeof__(svd), dungeon_topology.d_astral_level)),
    MP_LAYOUT(NUMMONS, NUMMONS), MP_LAYOUT(NUM_OBJECTS, NUM_OBJECTS),
    MP_LAYOUT(M2_FEMALE, M2_FEMALE), MP_LAYOUT(WEAPON_CLASS, WEAPON_CLASS), MP_LAYOUT(P_SPEAR, P_SPEAR),
    MP_LAYOUT(ART_MAGICBANE, ART_MAGICBANE), MP_LAYOUT(ATHAME, ATHAME), MP_LAYOUT(A_NONE, A_NONE),
    MP_LAYOUT(BATTLE_AXE, BATTLE_AXE), MP_LAYOUT(BLACK_DRAGON_SCALE_MAIL, BLACK_DRAGON_SCALE_MAIL),
    MP_LAYOUT(BULLWHIP, BULLWHIP), MP_LAYOUT(CHAIN_MAIL, CHAIN_MAIL),
    MP_LAYOUT(CLOAK_OF_DISPLACEMENT, CLOAK_OF_DISPLACEMENT), MP_LAYOUT(CLOAK_OF_MAGIC_RESISTANCE, CLOAK_OF_MAGIC_RESISTANCE),
    MP_LAYOUT(CLUB, CLUB), MP_LAYOUT(COLNO, COLNO), MP_LAYOUT(DILITHIUM_CRYSTAL, DILITHIUM_CRYSTAL),
    MP_LAYOUT(ELVEN_DAGGER, ELVEN_DAGGER), MP_LAYOUT(ELVEN_LEATHER_HELM, ELVEN_LEATHER_HELM),
    MP_LAYOUT(ELVEN_SHIELD, ELVEN_SHIELD), MP_LAYOUT(FAKE_AMULET_OF_YENDOR, FAKE_AMULET_OF_YENDOR),
    MP_LAYOUT(GAUNTLETS_OF_DEXTERITY, GAUNTLETS_OF_DEXTERITY), MP_LAYOUT(GAUNTLETS_OF_POWER, GAUNTLETS_OF_POWER),
    MP_LAYOUT(GRAY_DRAGON_SCALE_MAIL, GRAY_DRAGON_SCALE_MAIL), MP_LAYOUT(HELM_OF_BRILLIANCE, HELM_OF_BRILLIANCE),
    MP_LAYOUT(HELM_OF_TELEPATHY, HELM_OF_TELEPATHY), MP_LAYOUT(JADE, JADE), MP_LAYOUT(KATANA, KATANA),
    MP_LAYOUT(LEATHER_GLOVES, LEATHER_GLOVES), MP_LAYOUT(LEVITATION_BOOTS, LEVITATION_BOOTS),
    MP_LAYOUT(LOADSTONE, LOADSTONE), MP_LAYOUT(LONG_SWORD, LONG_SWORD), MP_LAYOUT(LOW_BOOTS, LOW_BOOTS),
    MP_LAYOUT(LUCKSTONE, LUCKSTONE), MP_LAYOUT(MACE, MACE), MP_LAYOUT(MM_NOMSG, MM_NOMSG),
    MP_LAYOUT(NO_MM_FLAGS, NO_MM_FLAGS), MP_LAYOUT(OILSKIN_CLOAK, OILSKIN_CLOAK),
    MP_LAYOUT(ORCISH_DAGGER, ORCISH_DAGGER), MP_LAYOUT(PLATE_MAIL, PLATE_MAIL), MP_LAYOUT(PL_NSIZ, PL_NSIZ),
    MP_LAYOUT(PM_ARCHEOLOGIST, PM_ARCHEOLOGIST), MP_LAYOUT(PM_BARBARIAN, PM_BARBARIAN),
    MP_LAYOUT(PM_CAVE_DWELLER, PM_CAVE_DWELLER), MP_LAYOUT(PM_CLERIC, PM_CLERIC),
    MP_LAYOUT(PM_HEALER, PM_HEALER), MP_LAYOUT(PM_KNIGHT, PM_KNIGHT), MP_LAYOUT(PM_MONK, PM_MONK),
    MP_LAYOUT(PM_RANGER, PM_RANGER), MP_LAYOUT(PM_ROGUE, PM_ROGUE), MP_LAYOUT(PM_SAMURAI, PM_SAMURAI),
    MP_LAYOUT(PM_TOURIST, PM_TOURIST), MP_LAYOUT(PM_VALKYRIE, PM_VALKYRIE), MP_LAYOUT(PM_WIZARD, PM_WIZARD),
    MP_LAYOUT(QUARTERSTAFF, QUARTERSTAFF), MP_LAYOUT(RANDOM_CLASS, RANDOM_CLASS),
    MP_LAYOUT(RLOC_ERR, RLOC_ERR), MP_LAYOUT(RLOC_NOMSG, RLOC_NOMSG), MP_LAYOUT(ROBE, ROBE),
    MP_LAYOUT(ROWNO, ROWNO), MP_LAYOUT(SCALPEL, SCALPEL), MP_LAYOUT(SHIELD_OF_REFLECTION, SHIELD_OF_REFLECTION),
    MP_LAYOUT(SHORT_SWORD, SHORT_SWORD), MP_LAYOUT(SHURIKEN, SHURIKEN),
    MP_LAYOUT(SILVER_DRAGON_SCALE_MAIL, SILVER_DRAGON_SCALE_MAIL), MP_LAYOUT(SPEAR, SPEAR),
    MP_LAYOUT(STRANGE_OBJECT, STRANGE_OBJECT), MP_LAYOUT(TWO_HANDED_SWORD, TWO_HANDED_SWORD),
    MP_LAYOUT(UNICORN_HORN, UNICORN_HORN), MP_LAYOUT(WAR_HAMMER, WAR_HAMMER),
    MP_LAYOUT(YELLOW_DRAGON_SCALE_MAIL, YELLOW_DRAGON_SCALE_MAIL),
};
#undef MP_LAYOUT
#undef MP_MON
#undef MP_OBJ

size_t probe_context_size(void) { return sizeof(struct monst); }
int probe_layout_count(void) { return sizeof mplayer_layout / sizeof mplayer_layout[0]; }
const char *probe_layout_name(int index) { return mplayer_layout[index].name; }
size_t probe_layout_value(int index) { return mplayer_layout[index].value; }
