#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <emscripten/stack.h>
#include "tu-exper-layout.h"

struct you u;
__typeof__(gu) gu;
__typeof__(gy) gy;
__typeof__(flags) flags;
__typeof__(disp) disp;
__typeof__(svk) svk;
static struct monst victim;
static struct permonst victim_data, player_data;
static int options[16], random_values[512], random_length, random_index, achievements, recorded[256], assert_guard;
static uint32_t random_state;
static char trace[131072], caller[128], assertion[512];
static jmp_buf assert_jump;
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...)
{
    va_list args; va_start(args, format); vsnprintf(trace + strlen(trace), sizeof trace - strlen(trace), format, args); va_end(args);
}
void pline(const char *format, ...) { char buf[BUFSZ]; va_list args; va_start(args, format); vsnprintf(buf, sizeof buf, format, args); va_end(args); append("pline:%s;", buf); }
void You_feel(const char *format, ...) { char buf[BUFSZ]; va_list args; va_start(args, format); vsnprintf(buf, sizeof buf, format, args); va_end(args); append("feel:%s;", buf); }
void livelog_printf(long category, const char *format, ...) { char buf[BUFSZ]; va_list args; va_start(args, format); vsnprintf(buf, sizeof buf, format, args); va_end(args); append("log:%ld:%s;", category, buf); }
void teleport_probe_assert_fail(const char *expression, const char *file, int line, const char *function)
{
    const char *base = strrchr(file, '/'); snprintf(assertion, sizeof assertion, "%s@%s:%d:%s", expression, base ? base + 1 : file, line, function);
    if (!assert_guard) abort(); longjmp(assert_jump, 1);
}
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
schar acurr(int which) { append("attribute:%d;", which); return options[1]; }
int find_mac(struct monst *mon) { append("ac;"); return options[0]; }
boolean exp_percent_changing(void) { append("percent;"); return options[3]; }
boolean resists_drli(struct monst *mon) { append("resist;"); return options[6]; }
const char *Goodbye(void) { append("goodbye;"); return "Goodbye"; }
void adjabil(int from, int to) { append("abilities:%d:%d;", from, to); if (options[7]) u.ulevel = options[7]; }
void done(int how) { append("done:%d;", how); if (options[11] == 1) u.ulevel = 2; else if (options[11] == 2) pluslvl(FALSE); }
int minuhpmax(int minimum) { append("minimum:%d;", minimum); return options[2]; }
void setuhpmax(int maximum, boolean human)
{
    append("maxhp:%d:%d;", maximum, human);
    if (!human && Upolyd) { u.mhmax = maximum; if (u.mh > maximum) u.mh = maximum; }
    else { u.uhpmax = maximum; if (u.uhp > maximum) u.uhp = maximum; }
}
int monhp_per_lvl(struct monst *mon) { append("monhp;"); return options[5]; }
void rehumanize(void) { append("humanize;"); u.umonnum = u.umonster; gy.youmonst.data = &mons[PM_HUMAN]; }
int newhp(void) { append("newhp;"); return options[4]; }
int xlev_to_rank(int level) { append("rank:%d;", level); return level / 3; }
int count_achievements(void) { append("achievements:%d;", achievements); return achievements; }
schar achieve_rank(int rank) { append("achievement-rank:%d;", rank); return rank + 42; }
void record_achievement(schar achievement) { append("record:%d;", achievement); if (options[8] && !recorded[(unsigned char) achievement]) { recorded[(unsigned char) achievement] = 1; achievements++; } }
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/exper.c"
#else
extern int teleport_exper_test_enermod(int);
#endif
void probe_reset(unsigned seed)
{
    monst_globals_init(); memset(&u, 0, sizeof u); memset(&gu, 0, sizeof gu); memset(&gy, 0, sizeof gy); memset(&flags, 0, sizeof flags);
    memset(&disp, 0, sizeof disp); memset(&svk, 0, sizeof svk); memset(&victim, 0, sizeof victim); memset(options, 0, sizeof options); memset(recorded, 0, sizeof recorded);
    memcpy(&victim_data, &mons[PM_HUMAN], sizeof victim_data); memcpy(&player_data, &mons[PM_HUMAN], sizeof player_data);
    memset(victim_data.mattk, 0, sizeof victim_data.mattk); victim_data.mmove = NORMAL_SPEED; victim.data = &victim_data; victim.m_lev = 5;
    u.umonster = u.umonnum = PM_HUMAN; gy.youmonst.data = &mons[PM_HUMAN]; u.ulevel = u.ulevelmax = u.ulevelpeak = 1;
    u.uhp = 50; u.uhpmax = 100; u.uen = 20; u.uenmax = u.uenpeak = 30; u.mh = 15; u.mhmax = 20;
    gu.urole.mnum = PM_ARCHEOLOGIST; gu.urole.xlev = 10; gu.urole.enadv.lofix = gu.urace.enadv.lofix = 1; gu.urole.enadv.lornd = gu.urace.enadv.lornd = 3;
    gu.urole.enadv.hifix = gu.urace.enadv.hifix = 2; gu.urole.enadv.hirnd = gu.urace.enadv.hirnd = 4;
    options[0] = 5; options[1] = 18; options[2] = 10; options[4] = 8; options[5] = 3; options[8] = options[10] = 1; flags.beginner = 1;
    random_state = seed; random_length = random_index = achievements = 0; trace[0] = caller[0] = assertion[0] = '\0';
}
void probe_clear(void) { trace[0] = '\0'; assertion[0] = '\0'; }
const char *probe_trace(void) { return trace; }
const char *probe_assertion(void) { return assertion; }
int *probe_rng_pointer(void) { return random_values; }
void probe_rng_length(int length) { random_length = length; random_index = 0; }
int probe_rng_count(void) { return random_index; }
unsigned probe_rng_state(void) { return random_state; }
void probe_option(int index, int value) { options[index] = value; }
size_t probe_snapshot_size(int which) { switch (which) { case 0: return sizeof u; case 1: return sizeof gu; case 2: return sizeof flags; case 3: return sizeof disp; case 4: return sizeof svk; } return 0; }
void *probe_snapshot_pointer(int which) { switch (which) { case 0: return &u; case 1: return &gu; case 2: return &flags; case 3: return &disp; case 4: return &svk; } return NULL; }
void probe_role(int role, int xlev, int race, int infix, int inrnd, int lofix, int lornd, int hifix, int hirnd)
{
    struct RoleAdvance *advance = race ? &gu.urace.enadv : &gu.urole.enadv;
    gu.urole.mnum = role; gu.urole.xlev = xlev;
    advance->infix = infix; advance->inrnd = inrnd; advance->lofix = lofix; advance->lornd = lornd; advance->hifix = hifix; advance->hirnd = hirnd;
}
void probe_hero(int level, int maximum, int peak, long experience, long score, int poly)
{
    u.ulevel = level; u.ulevelmax = maximum; u.ulevelpeak = peak; u.uexp = experience; u.urexp = score;
    u.umonnum = poly ? PM_DOG : PM_HUMAN; gy.youmonst.data = &mons[PM_HUMAN];
}
void probe_health(int hp, int hpmax, int energy, int energymax, int energypeak, int monsterhp, int monstermax)
{
    u.uhp = hp; u.uhpmax = hpmax; u.uen = energy; u.uenmax = energymax; u.uenpeak = energypeak; u.mh = monsterhp; u.mhmax = monstermax;
}
void probe_increments(int index, int hp, int energy) { u.uhpinc[index] = hp; u.ueninc[index] = energy; }
void probe_flags(int showexp, int showscore, int beginner, int bottom) { flags.showexp = showexp;
#ifdef SCORE_ON_BOTL
    flags.showscore = showscore;
#endif
    flags.beginner = beginner; disp.botl = bottom;
}
void probe_amphibious(int mask) { HMagical_breathing = !!(mask & 1); EMagical_breathing = !!(mask & 2); player_data.mflags1 = mask & 4 ? M1_AMPHIBIOUS : 0; gy.youmonst.data = &player_data; }
void probe_victim(int level, int speed, int symbol, int nasty, int revived, int cloned, int mail)
{
    victim.m_lev = level; victim_data.mmove = speed; victim_data.mlet = symbol; victim_data.mflags2 = nasty ? M2_NASTY : 0; victim.mrevived = revived; victim.mcloned = cloned;
#ifdef MAIL_STRUCTURES
    victim.data = mail ? &mons[PM_MAIL_DAEMON] : &victim_data;
#else
    victim.data = &victim_data;
#endif
}
void probe_attack(int index, int attack, int damage, int number, int sides) { victim_data.mattk[index].aatyp = attack; victim_data.mattk[index].adtyp = damage; victim_data.mattk[index].damn = number; victim_data.mattk[index].damd = sides; }
long probe_threshold(int level) { return newuexp(level); }
int probe_energy_modifier(int energy) {
#ifdef TELEPORT_REFERENCE_TU
    return enermod(energy);
#else
    return teleport_exper_test_enermod(energy);
#endif
}
int probe_power(void) { return newpw(); }
int probe_experience(int kills) { return experience(&victim, kills); }
void probe_more(int experience, int score) { more_experienced(experience, score); }
int probe_lose(const char *drainer, int alias)
{
    assert_guard = 1; if (setjmp(assert_jump)) { assert_guard = 0; return -1; }
    losexp(alias ? svk.killer.name : drainer); assert_guard = 0; return 0;
}
void probe_killer(const char *name) { snprintf(svk.killer.name, sizeof svk.killer.name, "%s", name); }
void probe_new_level(void) { newexplevel(); }
void probe_plus(int increment) { pluslvl(increment); }
long probe_random_experience(int gaining) { return rndexp(gaining); }
int probe_achievements(void) { return achievements; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
