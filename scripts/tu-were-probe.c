#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-were-layout.h"

struct you u;
__typeof__(flags) flags;
__typeof__(gw) gw;
__typeof__(gy) gy;
__typeof__(gm) gm;
__typeof__(svc) svc;
static struct monst main_mon, summoned[16];
static int options[16], random_values[512], random_length, random_index, make_count, summoned_count;
static int visible;
static char trace[32768], genbuf[BUFSZ], article[BUFSZ], caller[128];
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...)
{
    va_list args; va_start(args, format); vsnprintf(trace + strlen(trace), sizeof trace - strlen(trace), format, args); va_end(args);
}
static void text_message(const char *kind, const char *format, va_list args)
{
    char buffer[BUFSZ]; vsnprintf(buffer, sizeof buffer, format, args); append("%s:%s;", kind, buffer);
}
void impossible(const char *format, ...) { va_list args; va_start(args, format); text_message("impossible", format, args); va_end(args); }
void pline(const char *format, ...) { va_list args; va_start(args, format); text_message("pline", format, args); va_end(args); }
void You_hear(const char *format, ...) { va_list args; va_start(args, format); text_message("hear", format, args); va_end(args); }
void You_feel(const char *format, ...) { va_list args; va_start(args, format); text_message("feel", format, args); va_end(args); }
boolean rng_log_enabled(void) { return options[11] != 0; }
void rng_log_set_caller(const char *file, int line, const char *function)
{
    const char *base = strrchr(file, '/'); snprintf(caller, sizeof caller, "%s:%d:%s", base ? base + 1 : file, line, function);
}
static int draw(const char *name, int bound)
{
    int value;
    if (bound <= 0) abort();
    value = random_length ? random_values[random_index++ % random_length] % bound : 0;
    append("%s:%d:%d@%s;", name, bound, value, caller); return value;
}
int (rn2)(int bound) { return draw("rn2", bound); }
int (rnd)(int bound) { return draw("rnd", bound) + 1; }
int night(void) { append("night;"); return options[0]; }
int canseemon(struct monst *mon) { int value = mon == &main_mon ? options[1] : options[9]; append("see:%d:%d;", monsndx(mon->data), value); return value; }
void wake_nearto(coordxy x, coordxy y, int radius) { append("wake:%d:%d:%d;", x, y, radius); }
char *Monnam(struct monst *mon) { append("Monnam:%d;", monsndx(mon->data)); return "The creature"; }
void set_mon_data(struct monst *mon, struct permonst *data) { append("data:%d;", monsndx(data)); mon->data = data; }
int healmon(struct monst *mon, int amount, int maximum)
{
    append("heal:%d:%d;", amount, maximum); mon->mhp += amount; return amount;
}
void newsym(coordxy x, coordxy y) { append("newsym:%d:%d;", x, y); }
void mon_break_armor(struct monst *mon, boolean polyspot) { append("armor:%d:%d;", monsndx(mon->data), polyspot); }
void possibly_unwield(struct monst *mon, boolean polyspot) { append("unwield:%d:%d;", monsndx(mon->data), polyspot); }
boolean onscary(coordxy x, coordxy y, struct monst *mon) { append("scary:%d:%d;", x, y); return options[2]; }
boolean monnear(struct monst *mon, coordxy x, coordxy y) { append("near:%d:%d;", x, y); return options[3]; }
void monflee(struct monst *mon, int duration, boolean first, boolean message) { append("flee:%d:%d:%d;", duration, first, message); mon->mflee = 1; }
struct monst *makemon(struct permonst *data, coordxy x, coordxy y, mmflags_nht mmflags)
{
    struct monst *mon;
    make_count++; append("make:%d:%d:%d:%lu;", monsndx(data), x, y, (unsigned long) mmflags);
    if (options[8] && make_count % options[8] == 0) return NULL;
    if (summoned_count >= SIZE(summoned)) abort();
    mon = &summoned[summoned_count++]; memset(mon, 0, sizeof *mon); mon->data = data; mon->mx = x; mon->my = y; return mon;
}
boolean tamedog(struct monst *mon, struct obj *object, boolean tame)
{
    append("tame:%d:%d:%d;", monsndx(mon->data), object != NULL, tame); mon->mtame = 1; return TRUE;
}
char *an(const char *name) { append("an:%s;", name); snprintf(article, sizeof article, "a %s", name); return article; }
boolean paranoid_query(boolean paranoid, const char *query) { append("query:%d:%s;", paranoid, query); return options[5]; }
int monster_nearby(void) { append("nearby;"); return options[4]; }
int polymon(int pm) { append("poly:%d;", pm); u.umonnum = pm; gy.youmonst.data = &mons[pm]; return 1; }
void rehumanize(void) { append("humanize;"); u.umonnum = u.umonster; gy.youmonst.data = &mons[u.umonster]; }
void set_uasmon(void) { append("uasmon:%d;", u.ulycn); }
boolean unconscious(void) { append("unconscious;"); return options[6]; }
boolean is_fainted(void) { append("fainted;"); return options[7]; }

void probe_reset(void)
{
    monst_globals_init();
    memset(&u, 0, sizeof u); memset(&flags, 0, sizeof flags); memset(&gw, 0, sizeof gw);
    memset(&gy, 0, sizeof gy); memset(&gm, 0, sizeof gm); memset(&svc, 0, sizeof svc);
    memset(&main_mon, 0, sizeof main_mon); memset(summoned, 0, sizeof summoned); memset(options, 0, sizeof options);
    main_mon.data = &mons[PM_HUMAN_WEREWOLF]; main_mon.mcanmove = 1; main_mon.mx = 12; main_mon.my = 13; main_mon.mux = 14; main_mon.muy = 15;
    main_mon.mhp = 50; main_mon.mhpmax = 100;
    u.ux = 20; u.uy = 21; u.umonster = u.umonnum = PM_HUMAN; u.ulycn = PM_WEREWOLF; gy.youmonst.data = &mons[PM_HUMAN];
    options[11] = 1;
    random_length = random_index = make_count = summoned_count = 0; trace[0] = caller[0] = '\0'; strcpy(genbuf, "UNCHANGED");
}
void probe_clear(void) { trace[0] = '\0'; }
const char *probe_trace(void) { return trace; }
int *probe_rng_pointer(void) { return random_values; }
void probe_rng_length(int length) { random_length = length; random_index = 0; }
int probe_rng_count(void) { return random_index; }
void probe_option(int index, int value) { options[index] = value; }
void probe_properties(unsigned mask)
{
    HProtection_from_shape_changers = !!(mask & 1); EProtection_from_shape_changers = !!(mask & 2);
    HDeaf = !!(mask & 4); EDeaf = !!(mask & 8); u.uroleplay.deaf = !!(mask & 16);
    HHallucination = !!(mask & 32); HHalluc_resistance = !!(mask & 64); EHalluc_resistance = !!(mask & 128);
    HPolymorph_control = !!(mask & 256); EPolymorph_control = !!(mask & 512);
    HStun = !!(mask & 1024); HUnchanging = !!(mask & 2048); EUnchanging = !!(mask & 4096);
}
void probe_mon(int pm, int hp, int maximum, int asleep, int movable, int frozen, int peaceful, int female)
{
    main_mon.data = &mons[pm]; main_mon.mhp = hp; main_mon.mhpmax = maximum;
    main_mon.msleeping = asleep; main_mon.mcanmove = movable; main_mon.mfrozen = frozen;
    main_mon.mpeaceful = peaceful; main_mon.female = female; main_mon.mflee = 0;
}
void probe_hero(int current, int lycanthrope, int timeout, int multi, int moving, int paranoia, int moon)
{
    u.umonnum = current; u.ulycn = lycanthrope; u.mtimedone = timeout; gy.youmonst.data = &mons[current];
    gm.multi = multi; svc.context.mon_moving = moving; flags.paranoia_bits = paranoia ? PARANOID_WERECHANGE : 0; flags.moonphase = moon;
}
int probe_counter(int pm) { return counter_were(pm); }
int probe_beastie(int pm) { return were_beastie(pm); }
void probe_change(void) { were_change(&main_mon); }
void probe_new(void) { new_were(&main_mon); }
int probe_summon(int pm, int yours, int buffer) { return were_summon(&mons[pm], yours, &visible, buffer ? genbuf : NULL); }
void probe_you(void) { you_were(); }
void probe_unwere(int purify) { you_unwere(purify); }
void probe_lycanthrope(int which) { set_ulycn(which); }
long probe_changes(void) { return gw.were_changes; }
void probe_set_changes(long value) { gw.were_changes = value; }
int probe_mon_pm(void) { return monsndx(main_mon.data); }
int probe_mon_hp(void) { return main_mon.mhp; }
int probe_mon_sleep(void) { return main_mon.msleeping; }
int probe_mon_move(void) { return main_mon.mcanmove; }
int probe_mon_frozen(void) { return main_mon.mfrozen; }
int probe_mon_flee(void) { return main_mon.mflee; }
int probe_current(void) { return u.umonnum; }
int probe_lycan(void) { return u.ulycn; }
int probe_timeout(void) { return u.mtimedone; }
int probe_visible(void) { return visible; }
const char *probe_genbuf(void) { return genbuf; }
int probe_summoned_count(void) { return summoned_count; }
int probe_summoned_pm(int index) { return monsndx(summoned[index].data); }
int probe_summoned_tame(int index) { return summoned[index].mtame; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
