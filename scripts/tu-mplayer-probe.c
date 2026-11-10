#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-mplayer-layout.h"

struct you u;
__typeof__(svl) svl;
__typeof__(svd) svd;
__typeof__(gu) gu;
const struct const_globals cg = { .zeromonst = { .mhp = 1234567, .mhpmax = 7654321, .mux = 17, .muy = 18, .m_id = 0x12345678, .female = 1, .msleeping = 1, .mfrozen = 7, .mcanmove = 0 } };
static struct monst monsters[128];
static struct mextra extras[128];
static char names[128][PL_NSIZ], name_result[PL_NSIZ], rank_result[64];
static struct permonst copied_data;
static struct obj fixture_objects[1024];
static int monster_count, object_count, random_values[1024], random_length, random_index, good_calls, options[16], fake_copy_valid;
static uint32_t random_state;
static char trace[1048576], caller[128];
static struct monst *last_result;
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...)
{
    va_list args; va_start(args, format); vsnprintf(trace + strlen(trace), sizeof trace - strlen(trace), format, args); va_end(args);
}
void impossible(const char *format, ...) { char buf[BUFSZ]; va_list args; va_start(args, format); vsnprintf(buf, sizeof buf, format, args); va_end(args); append("impossible:%s;", buf); }
void verbalize(const char *format, ...) { char buf[BUFSZ]; va_list args; va_start(args, format); vsnprintf(buf, sizeof buf, format, args); va_end(args); append("say:%s;", buf); }
boolean rng_log_enabled(void) { return options[10]; }
void rng_log_set_caller(const char *file, int line, const char *function)
{
    const char *base = strrchr(file, '/'); snprintf(caller, sizeof caller, "%s:%d:%s", base ? base + 1 : file, line, function);
}
static int draw(const char *kind, int bound)
{
    int result;
    if (bound <= 0) abort();
    if (random_index < random_length) result = random_values[random_index] % bound;
    else { random_state = random_state * 1664525U + 1013904223U; result = (int) ((random_state >> 8) % (unsigned) bound); }
    random_index++; append("%s:%d:%d@%s;", kind, bound, result, caller); return result;
}
int (rn2)(int bound) { return draw("rn2", bound); }
int (rnd)(int bound) { return draw("rnd", bound) + 1; }
int (d)(int number, int sides) { int result = draw("dice", sides * number) + number; append("diceargs:%d:%d;", number, sides); return result; }
static int mon_index(struct monst *mon) { return mon >= monsters && mon < monsters + SIZE(monsters) ? (int) (mon - monsters) : -1; }
static int object_index(struct obj *object) { return (int) (object - fixture_objects); }
const char *rank_of(int level, short pm, boolean female) { append("rank:%d:%d:%d;", level, pm, female); snprintf(rank_result, sizeof rank_result, "Rank%d", level); return rank_result; }
boolean rloc(struct monst *mon, unsigned flags)
{
    int x, y; append("rloc:%d:%u;", mon_index(mon), flags);
    for (x = 0; x < COLNO; x++) for (y = 0; y < ROWNO; y++) if (svl.level.monsters[x][y] == mon) svl.level.monsters[x][y] = NULL;
    return TRUE;
}
struct monst *makemon(struct permonst *data, coordxy x, coordxy y, mmflags_nht flags)
{
    struct monst *mon;
    append("make:%d:%d:%d:%lu;", monsndx(data), x, y, (unsigned long) flags);
    if (options[0]) return NULL;
    if (monster_count >= SIZE(monsters)) abort();
    mon = &monsters[monster_count++]; memset(mon, 0, sizeof *mon); mon->data = data; mon->mx = x; mon->my = y; mon->mpeaceful = 1;
    mon->nmon = fmon; fmon = mon; svl.level.monsters[x][y] = mon; return mon;
}
struct monst *christen_monst(struct monst *mon, const char *name)
{
    int index = mon_index(mon);
    append("name:%d:%s;", index, name);
    if (options[6]) {
        struct monst *replacement = &monsters[monster_count++]; int old = index;
        *replacement = *mon; index = mon_index(replacement);
        if (fmon == mon) fmon = replacement;
        svl.level.monsters[mon->mx][mon->my] = replacement; mon = replacement;
        append("renamed:%d:%d;", old, index);
    }
    snprintf(names[index], sizeof names[index], "%s", name); extras[index].mgivenname = names[index]; mon->mextra = &extras[index]; return mon;
}
static struct obj *object(int type)
{
    struct obj *value;
    if (object_count >= SIZE(fixture_objects)) abort();
    value = &fixture_objects[object_count++]; memset(value, 0, sizeof *value); value->otyp = type;
    value->oclass = objects[type].oc_class; value->quan = 1; value->spe = -5; value->oeroded = value->oeroded2 = 3; value->owt = 77; return value;
}
struct obj *mksobj(int type, boolean init, boolean art) { append("object:%d:%d:%d;", type, init, art); return object(type); }
struct obj *mkobj(int oclass, boolean art) { append("random-object:%d:%d;", oclass, art); return object(DAGGER); }
int mpickobj(struct monst *mon, struct obj *value) { append("pick:%d:%d;", mon_index(mon), object_index(value)); value->ocarry = mon; return 0; }
struct obj *mongets(struct monst *mon, int type) { struct obj *value = object(type); append("gets:%d:%d;", mon_index(mon), type); value->ocarry = mon; return value; }
void set_malign(struct monst *mon) { append("malign:%d:%d;", mon_index(mon), mon->mpeaceful); mon->malign = -7; }
int rnd_class(int low, int high) { int result = low + options[2] % (high - low + 1); append("class:%d:%d:%d;", low, high, result); return result; }
void curse(struct obj *value) { append("curse:%d;", object_index(value)); value->cursed = 1; value->blessed = 0; }
void bless(struct obj *value) { append("bless:%d;", object_index(value)); value->blessed = 1; value->cursed = 0; }
struct obj *mk_artifact(struct obj *value, aligntyp alignment, uchar mode, boolean outside)
{
    append("artifact:%d:%d:%u:%d;", object_index(value), alignment, mode, outside);
    if (options[3]) {
        struct obj *replacement = object(value->otyp); *replacement = *value; value = replacement;
        value->oartifact = options[3] == 2 ? ART_MAGICBANE : ART_EXCALIBUR;
    }
    return value;
}
boolean is_art(struct obj *value, int which) { append("is-art:%d:%d;", object_index(value), which); return value && value->oartifact == which; }
boolean monmightthrowwep(struct obj *value) { append("throw:%d;", object_index(value)); return options[4]; }
int weight(struct obj *value) { append("weight:%d:%ld;", object_index(value), value->quan); return (int) (100 + value->quan * 3); }
void m_dowear(struct monst *mon, boolean creating) { append("wear:%d:%d;", mon_index(mon), creating); }
void mkmonmoney(struct monst *mon, long amount) { append("money:%d:%ld;", mon_index(mon), amount); }
int rnd_offensive_item(struct monst *mon) { append("offense:%d;", mon_index(mon)); return POT_BOOZE; }
int rnd_defensive_item(struct monst *mon) { append("defense:%d;", mon_index(mon)); return POT_WATER; }
int rnd_misc_item(struct monst *mon) { append("misc:%d;", mon_index(mon)); return SCROLL_CLASS == 0 ? DAGGER : SCR_IDENTIFY; }
void set_mon_data(struct monst *mon, struct permonst *data)
{
    struct monst copy = *mon; copy.data = cg.zeromonst.data;
    fake_copy_valid = !memcmp(&copy, &cg.zeromonst, sizeof copy);
    append("data:%d:copy=%d;", monsndx(data), fake_copy_valid); mon->data = data;
}
boolean goodpos(coordxy x, coordxy y, struct monst *mon, mmflags_nht flags)
{
    good_calls++; append("good:%d:%d:%d:%lu;", x, y, monsndx(mon->data), (unsigned long) flags);
    return options[5] >= 0 && good_calls > options[5];
}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/mplayer.c"
#else
extern const char *teleport_mplayer_test_dev_name(void);
extern void teleport_mplayer_test_name(struct monst *, char *);
extern void teleport_mplayer_test_armor(struct monst *, short);
#endif
void probe_reset(unsigned seed)
{
    monst_globals_init(); objects_globals_init(); memset(&u, 0, sizeof u); memset(&svl, 0, sizeof svl); memset(&svd, 0, sizeof svd); memset(&gu, 0, sizeof gu);
    memset(monsters, 0, sizeof monsters); memset(extras, 0, sizeof extras); memset(names, 0, sizeof names); memset(fixture_objects, 0, sizeof fixture_objects); memset(options, 0, sizeof options);
    monster_count = object_count = random_length = random_index = good_calls = fake_copy_valid = 0; random_state = seed; options[4] = options[10] = 1;
    trace[0] = caller[0] = name_result[0] = '\0'; last_result = NULL; astral_level.dnum = 99; gu.urole.mnum = PM_ARCHEOLOGIST;
}
void probe_clear(void) { trace[0] = '\0'; }
const char *probe_trace(void) { return trace; }
int *probe_rng_pointer(void) { return random_values; }
void probe_rng_length(int length) { random_length = length; random_index = 0; }
int probe_rng_count(void) { return random_index; }
unsigned probe_rng_state(void) { return random_state; }
void probe_option(int index, int value) { options[index] = value; if (index == 1) u.uz.dnum = value ? 99 : 0; }
void probe_existing(int pm, const char *name, int named)
{
    struct monst *mon = &monsters[monster_count++]; int index = mon_index(mon);
    memset(mon, 0, sizeof *mon); mon->data = &mons[pm]; mon->nmon = fmon; fmon = mon;
    if (named) { snprintf(names[index], sizeof names[index], "%s", name); extras[index].mgivenname = names[index]; mon->mextra = &extras[index]; }
}
void probe_occupied(int x, int y) { if (!monster_count) probe_existing(PM_GHOST, "", 0); svl.level.monsters[x][y] = &monsters[0]; }
const char *probe_dev(void) {
#ifdef TELEPORT_REFERENCE_TU
    return dev_name();
#else
    return teleport_mplayer_test_dev_name();
#endif
}
void probe_name(int pm, int level)
{
    struct monst *mon = &monsters[monster_count++]; memset(mon, 0, sizeof *mon); mon->data = &mons[pm]; mon->m_lev = level;
#ifdef TELEPORT_REFERENCE_TU
    get_mplname(mon, name_result);
#else
    teleport_mplayer_test_name(mon, name_result);
#endif
    last_result = mon;
}
void probe_armor(short type) {
    if (!monster_count) probe_existing(PM_ARCHEOLOGIST, "", 0);
#ifdef TELEPORT_REFERENCE_TU
    mk_mplayer_armor(&monsters[0], type);
#else
    teleport_mplayer_test_armor(&monsters[0], type);
#endif
}
void probe_make(int pm, int x, int y, int special) { last_result = mk_mplayer(&mons[pm], x, y, special); }
void probe_create(int number, int special) { create_mplayers(number, special); }
void probe_role(int pm) { gu.urole.mnum = pm; }
void probe_talk(int index, int peaceful, int copy_data)
{
    struct monst *mon = &monsters[index]; mon->mpeaceful = peaceful;
    if (copy_data) { memcpy(&copied_data, mon->data, sizeof copied_data); mon->data = &copied_data; }
    mplayer_talk(mon);
}
int probe_result(void) { return last_result ? mon_index(last_result) : -1; }
const char *probe_name_result(void) { return name_result; }
int probe_monster_count(void) { return monster_count; }
int probe_mon_pm(int i) { return monsndx(monsters[i].data); }
int probe_mon_female(int i) { return monsters[i].female; }
int probe_mon_peaceful(int i) { return monsters[i].mpeaceful; }
int probe_mon_level(int i) { return monsters[i].m_lev; }
int probe_mon_hp(int i) { return monsters[i].mhp; }
int probe_mon_hpmax(int i) { return monsters[i].mhpmax; }
int probe_mon_malign(int i) { return monsters[i].malign; }
const char *probe_mon_name(int i) { return has_mgivenname(&monsters[i]) ? MGIVENNAME(&monsters[i]) : NULL; }
int probe_object_count(void) { return object_count; }
int probe_object_field(int i, int field) {
    struct obj *value = &fixture_objects[i];
    switch (field) {
    case 0: return value->otyp; case 1: return value->spe; case 2: return value->oeroded; case 3: return value->oeroded2;
    case 4: return value->oerodeproof; case 5: return value->greased; case 6: return value->cursed; case 7: return value->blessed;
    case 8: return value->oartifact; case 9: return value->owt; case 10: return value->ocarry ? mon_index(value->ocarry) : -1;
    } return 0;
}
long probe_object_quantity(int i) { return fixture_objects[i].quan; }
int probe_good_calls(void) { return good_calls; }
int probe_fake_copy(void) { return fake_copy_valid; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
