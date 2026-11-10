#include "hack.h"
#include <stddef.h>
#include <limits.h>

#define EXP_LAYOUT(name, value) { #name, value }
#define EXP_HERO(field) EXP_LAYOUT(hero_##field, offsetof(struct you, field)), EXP_LAYOUT(hero_##field##_size, sizeof(((struct you *) 0)->field))
#define EXP_ADVANCE(field) EXP_LAYOUT(advance_##field, offsetof(struct RoleAdvance, field))
static const struct {
    const char *name;
    size_t value;
} exper_layout[] = {
    EXP_LAYOUT(pointerSize, sizeof(void *)), EXP_LAYOUT(intSize, sizeof(int)),
    EXP_LAYOUT(longSize, sizeof(long)), EXP_LAYOUT(charSize, sizeof(char)),
    EXP_LAYOUT(charSigned, (char) -1 < 0), EXP_LAYOUT(CHAR_BIT, CHAR_BIT),
    EXP_LAYOUT(booleanSize, sizeof(boolean)), EXP_LAYOUT(booleanSigned, (boolean) -1 < 0),
    EXP_HERO(ulevel), EXP_HERO(ulevelmax), EXP_HERO(ulevelpeak),
    EXP_HERO(uhp), EXP_HERO(uhpmax), EXP_HERO(uhppeak),
    EXP_HERO(uen), EXP_HERO(uenmax), EXP_HERO(uenpeak),
    EXP_HERO(mh), EXP_HERO(mhmax), EXP_HERO(umonnum), EXP_HERO(umonster),
    EXP_HERO(uexp), EXP_HERO(urexp),
    EXP_LAYOUT(hero_uhpinc, offsetof(struct you, uhpinc)),
    EXP_LAYOUT(hero_ueninc, offsetof(struct you, ueninc)),
    EXP_LAYOUT(incrementSize, sizeof(((struct you *) 0)->uhpinc[0])),
    EXP_LAYOUT(incrementCount, sizeof(((struct you *) 0)->uhpinc) / sizeof(((struct you *) 0)->uhpinc[0])),
    EXP_LAYOUT(heroProps, offsetof(struct you, uprops)),
    EXP_LAYOUT(propSize, sizeof(struct prop)),
    EXP_LAYOUT(propIntrinsic, offsetof(struct prop, intrinsic)),
    EXP_LAYOUT(propExtrinsic, offsetof(struct prop, extrinsic)),
    EXP_LAYOUT(propValueSize, sizeof(((struct prop *) 0)->intrinsic)),
    EXP_LAYOUT(roleMonster, offsetof(__typeof__(gu), urole.mnum)),
    EXP_LAYOUT(roleMonsterSize, sizeof gu.urole.mnum),
    EXP_LAYOUT(roleXlev, offsetof(__typeof__(gu), urole.xlev)),
    EXP_LAYOUT(roleXlevSize, sizeof gu.urole.xlev),
    EXP_LAYOUT(roleEnergy, offsetof(__typeof__(gu), urole.enadv)),
    EXP_LAYOUT(raceEnergy, offsetof(__typeof__(gu), urace.enadv)),
    EXP_LAYOUT(advanceFieldSize, sizeof(((struct RoleAdvance *) 0)->infix)),
    EXP_ADVANCE(infix), EXP_ADVANCE(inrnd), EXP_ADVANCE(lofix),
    EXP_ADVANCE(lornd), EXP_ADVANCE(hifix), EXP_ADVANCE(hirnd),
    EXP_LAYOUT(youmonst, offsetof(__typeof__(gy), youmonst)),
    EXP_LAYOUT(monsterSize, sizeof(struct monst)),
    EXP_LAYOUT(monsterData, offsetof(struct monst, data)),
    EXP_LAYOUT(monsterDataSize, sizeof(((struct monst *) 0)->data)),
    EXP_LAYOUT(monsterLevel, offsetof(struct monst, m_lev)),
    EXP_LAYOUT(monsterLevelSize, sizeof(((struct monst *) 0)->m_lev)),
    EXP_LAYOUT(permonstSize, sizeof(struct permonst)),
    EXP_LAYOUT(permonstMove, offsetof(struct permonst, mmove)),
    EXP_LAYOUT(permonstMoveSize, sizeof(((struct permonst *) 0)->mmove)),
    EXP_LAYOUT(permonstLetter, offsetof(struct permonst, mlet)),
    EXP_LAYOUT(permonstLetterSize, sizeof(((struct permonst *) 0)->mlet)),
    EXP_LAYOUT(permonstFlags1, offsetof(struct permonst, mflags1)),
    EXP_LAYOUT(permonstFlags2, offsetof(struct permonst, mflags2)),
    EXP_LAYOUT(permonstFlagsSize, sizeof(((struct permonst *) 0)->mflags1)),
    EXP_LAYOUT(permonstAttacks, offsetof(struct permonst, mattk)),
    EXP_LAYOUT(attackSize, sizeof(struct attack)),
    EXP_LAYOUT(attackType, offsetof(struct attack, aatyp)),
    EXP_LAYOUT(attackDamageType, offsetof(struct attack, adtyp)),
    EXP_LAYOUT(attackDice, offsetof(struct attack, damn)),
    EXP_LAYOUT(attackSides, offsetof(struct attack, damd)),
    EXP_LAYOUT(attackFieldSize, sizeof(((struct attack *) 0)->aatyp)),
    EXP_LAYOUT(flagShowexp, offsetof(__typeof__(flags), showexp)),
    EXP_LAYOUT(flagShowscore, offsetof(__typeof__(flags), showscore)),
    EXP_LAYOUT(flagBeginner, offsetof(__typeof__(flags), beginner)),
    EXP_LAYOUT(flagFieldSize, sizeof flags.showexp),
    EXP_LAYOUT(displayBotl, offsetof(struct display_hints, botl)),
    EXP_LAYOUT(displayBotlSize, sizeof disp.botl),
    EXP_LAYOUT(killerFormat, offsetof(__typeof__(svk), killer.format)),
    EXP_LAYOUT(killerFormatSize, sizeof svk.killer.format),
    EXP_LAYOUT(killerName, offsetof(__typeof__(svk), killer.name)),
    EXP_LAYOUT(killerNameSize, sizeof svk.killer.name),
#ifdef NDEBUG
    EXP_LAYOUT(ASSERT_ENABLED, 0),
#else
    EXP_LAYOUT(ASSERT_ENABLED, 1),
#endif
#ifdef MAIL_STRUCTURES
    EXP_LAYOUT(MAIL_STRUCTURES, 1),
#else
    EXP_LAYOUT(MAIL_STRUCTURES, 0),
#endif
#ifdef SCORE_ON_BOTL
    EXP_LAYOUT(SCORE_ON_BOTL, 1),
#else
    EXP_LAYOUT(SCORE_ON_BOTL, 0),
#endif
    EXP_LAYOUT(LONG_MAX, LONG_MAX), EXP_LAYOUT(LARGEST_INT, LARGEST_INT),
    EXP_LAYOUT(MAGICAL_BREATHING, MAGICAL_BREATHING), EXP_LAYOUT(M1_AMPHIBIOUS, M1_AMPHIBIOUS),
    EXP_LAYOUT(M2_NASTY, M2_NASTY), EXP_LAYOUT(NUMMONS, NUMMONS),
    EXP_LAYOUT(MAXULEV, MAXULEV), EXP_LAYOUT(NATTK, NATTK), EXP_LAYOUT(NORMAL_SPEED, NORMAL_SPEED),
    EXP_LAYOUT(AT_BUTT, AT_BUTT), EXP_LAYOUT(AT_WEAP, AT_WEAP), EXP_LAYOUT(AT_MAGC, AT_MAGC),
    EXP_LAYOUT(AD_PHYS, AD_PHYS), EXP_LAYOUT(AD_BLND, AD_BLND), EXP_LAYOUT(AD_DRLI, AD_DRLI),
    EXP_LAYOUT(AD_STON, AD_STON), EXP_LAYOUT(AD_SLIM, AD_SLIM), EXP_LAYOUT(AD_WRAP, AD_WRAP),
    EXP_LAYOUT(S_EEL, S_EEL), EXP_LAYOUT(A_WIS, A_WIS), EXP_LAYOUT(DIED, DIED),
    EXP_LAYOUT(KILLED_BY, KILLED_BY), EXP_LAYOUT(LL_MINORAC, LL_MINORAC),
    EXP_LAYOUT(PM_CLERIC, PM_CLERIC), EXP_LAYOUT(PM_WIZARD, PM_WIZARD),
    EXP_LAYOUT(PM_HEALER, PM_HEALER), EXP_LAYOUT(PM_KNIGHT, PM_KNIGHT),
    EXP_LAYOUT(PM_BARBARIAN, PM_BARBARIAN), EXP_LAYOUT(PM_VALKYRIE, PM_VALKYRIE),
#ifdef MAIL_STRUCTURES
    EXP_LAYOUT(PM_MAIL_DAEMON, PM_MAIL_DAEMON),
#endif
};
#undef EXP_LAYOUT
#undef EXP_HERO
#undef EXP_ADVANCE

size_t probe_context_size(void) { return sizeof(struct you); }
int probe_layout_count(void) { return sizeof exper_layout / sizeof exper_layout[0]; }
const char *probe_layout_name(int index) { return exper_layout[index].name; }
size_t probe_layout_value(int index) { return exper_layout[index].value; }
