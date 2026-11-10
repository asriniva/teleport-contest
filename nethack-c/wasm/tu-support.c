/* Temporary ABI support only; no translated NetHack algorithm lives here. */
#define NEED_VARARGS
#include "hack.h"
#include "tu-source-locations.h"
#include "tu-support.h"

/* Clang implements the variadic ABI, rather than JS constructing a va_list.
 * This is the single panic invocation from the original strutil.c. */
void teleport_strutil_panic(const char *file, int line)
{
    panic("%s:%d string too long", file, line);
}

void teleport_rect_panic(void)
{
    panic("Could not alloc rect");
}

void teleport_rect_impossible(void)
{
    impossible("n_rects may be too small.");
}

int teleport_rect_rn2(int n)
{
    if (rng_log_enabled())
        rng_log_set_caller(TELEPORT_RECT_RNG_FILE, TELEPORT_RECT_RNG_LINE,
                           TELEPORT_RECT_RNG_FUNCTION);
    return (rn2)(n);
}

static struct teleport_track_state track_state;
void *teleport_track_state_pointer(void) { return &track_state; }
struct you *teleport_track_u(void) { return &u; }
struct obj *teleport_track_uleft(void) { return uleft; }
struct obj *teleport_track_uright(void) { return uright; }
int teleport_track_update_file(NHFILE *nhfp) { return update_file(nhfp); }
int teleport_track_release_data(NHFILE *nhfp) { return release_data(nhfp); }
void teleport_track_panic(void) { panic("rest_track: impossible pt counts"); }

/* libc ABI and stable output storage only; calendar algorithms live in JS. */
time_t teleport_calendar_time(void)
{
    time_t datetime = 0;
    (void) time(&datetime);
    return datetime;
}
struct tm *teleport_calendar_localtime(time_t date) { return localtime(&date); }
char *teleport_calendar_datestr(void) { static char datestr[15]; return datestr; }
void teleport_calendar_format(char *buf, size_t size, long year,
                              int month, int day, int hour, int minute, int second)
{
    nh_snprintf(TELEPORT_CALENDAR_FORMAT_FUNCTION, TELEPORT_CALENDAR_FORMAT_LINE,
                buf, size, "%04ld%02d%02d%02d%02d%02d", year, month, day, hour, minute, second);
}

/* Field/global accessors and variadic ABI bridges for stairs.js. */
stairway **teleport_stairs_head_pointer(void) { return &gs.stairs; }
int teleport_stairs_amulet(void) { return u.uhave.amulet; }
int teleport_stairs_quest(void) { return quest_dnum; }
d_level *teleport_stairs_special_level(int which)
{
    switch (which) {
    case 0: return &earth_level;
    case 1: return &air_level;
    case 2: return &fire_level;
    case 3: return &water_level;
    default: return NULL;
    }
}
char *teleport_stairs_dname(int index) { return svd.dungeons[index].dname; }
void teleport_stairs_format_strings(char *out, const char *format,
                                    const char *a, const char *b,
                                    const char *c, const char *d)
{
    Sprintf(out, format, a, b, c, d);
}
void teleport_stairs_format_int(char *out, const char *format, int value)
{
    Sprintf(out, format, value);
}

/* Shared option storage and global/diagnostic ABI access only; logic is JS. */
#ifndef TELEPORT_REFERENCE_SYS
struct sysopt_s sysopt;
#endif
void *teleport_sys_pointer(void) { return &sysopt; }
void *teleport_sys_gc_pointer(void) { return &gc; }
void teleport_sys_panic(void)
{
    panic("config error: PERS_IS_UID must be either 0 or 1");
}

/* Tombstone global/variadic/window ABI only; layout decisions are JS. */
void *teleport_rip_head_pointer(void) { return &gr.rip; }
char *teleport_rip_name(void) { return svp.plname; }
long teleport_rip_money(void) { return gd.done_money; }
void teleport_rip_putstr(winid window, int attr, const char *text)
{
    putstr(window, attr, text);
}
void teleport_rip_dump(winid window, int attr, const char *text, int forward)
{
#ifdef DUMPLOG
    dump_forward_putstr(window, attr, text, forward);
#else
    (void) window; (void) attr; (void) text; (void) forward;
#endif
}
void teleport_rip_format_name(char *out, int length, const char *name)
{
    Sprintf(out, "%.*s", length, name);
}
void teleport_rip_format_cash(char *out, long cash) { Sprintf(out, "%ld Au", cash); }
void teleport_rip_format_year(char *out, int year) { Sprintf(out, "%4d", year); }

/* Zero-only version metadata storage; date.js supplies initial values. */
#ifndef TELEPORT_REFERENCE_DATE
struct nomakedefs_s nomakedefs;
#endif
void *teleport_date_pointer(void) { return &nomakedefs; }
void teleport_date_format(char *out, size_t size, const char *text)
{
    nh_snprintf("populate_nomakedefs", TELEPORT_DATE_FORMAT_LINE,
                out, size, "%s", text);
}

/* Native allocator/diagnostic/format ABI; allocation policy lives in JS. */
void *teleport_alloc_malloc(unsigned size) { return malloc(size); }
void *teleport_alloc_realloc(void *pointer, unsigned size) { return realloc(pointer, size); }
static char teleport_alloc_buffers[4][32];
void *teleport_alloc_ptrbuf(void) { return teleport_alloc_buffers; }
void teleport_alloc_format(char *out, void *pointer)
{
#ifdef HAS_PTR_FMT
    Sprintf(out, "%p", pointer);
#else
    Sprintf(out, "%06lx", (unsigned long) pointer);
#endif
}
void teleport_alloc_panic_alloc(unsigned size)
{
    panic("Memory allocation failure; cannot get %u bytes", size);
}
void teleport_alloc_panic_realloc(unsigned size)
{
    panic("Memory allocation failure; cannot extend to %u bytes", size);
}
void teleport_alloc_panic_dupstr(void) { panic("dupstr: string length overflow"); }
void teleport_alloc_panic_overflow(const char *file, int line)
{
    panic("Overflow at %s:%d", file, line);
}

/* Global addresses only; UTF-8/glyph/list algorithms live in JS. */
#ifdef ENHANCED_SYMBOLS
extern glyph_map glyphmap[MAX_GLYPH];
extern const glyph_info nul_glyphinfo;
void *teleport_utf8_glyphmap(void) { return glyphmap; }
void *teleport_utf8_gbuf(void) { return &gg.gbuf[0][0]; }
void *teleport_utf8_showsyms(void) { return gs.showsyms; }
void *teleport_utf8_customizations(void) { return &gs.sym_customizations[0][0]; }
int teleport_utf8_currentgraphics(void) { return gc.currentgraphics; }
const char *teleport_utf8_hexdd(void) { return hexdd; }
const void *teleport_utf8_nul_glyphinfo(void) { return &nul_glyphinfo; }
#endif

/* Zero-only ABI storage; drawing.js is the authoritative initializer. */
extern const uchar def_r_oc_syms[MAXOCLASSES];
#ifndef TELEPORT_REFERENCE_DRAWING
const struct class_sym def_oc_syms[MAXOCLASSES] = {{0}};
const struct class_sym def_monsyms[MAXMCLASSES] = {{0}};
const struct symdef def_warnsyms[WARNCOUNT] = {{0}};
const struct symdef defsyms[MAXPCHARS + 1] = {{0}};
const uchar def_r_oc_syms[MAXOCLASSES] = {0};
#endif
const void *teleport_drawing_objects(void) { return def_oc_syms; }
const void *teleport_drawing_monsters(void) { return def_monsyms; }
const void *teleport_drawing_warnings(void) { return def_warnsyms; }
const void *teleport_drawing_symbols(void) { return defsyms; }
const void *teleport_drawing_rogue(void) { return def_r_oc_syms; }

/* Engine identifier storage only; POSIX wrapper logic and text live in JS. */
#ifndef TELEPORT_REFERENCE_POSIXREGEX
const char regex_id[11] = {0};
#else
extern const char regex_id[];
#endif
const void *teleport_posixregex_identifier(void) { return regex_id; }

/* RNG/global and variadic stdio ABI only; RNG/logger decisions are JS. */
void *teleport_rnd_core_function(void) { return (void *) rn2; }
void *teleport_rnd_display_function(void) { return (void *) rn2_on_display_rng; }
int teleport_rnd_luck(void) { return Luck; }
int teleport_rnd_level(void) { return u.ulevel; }
int teleport_rnd_strong_seed(void) { return has_strong_rngseed; }
void teleport_rnd_panic(void) { panic("Bad rng function passed to init_isaac64()."); }
void teleport_rnd_impossible_one(const char *format, int value) { impossible(format, value); }
void teleport_rnd_impossible_two(const char *format, int a, int b) { impossible(format, a, b); }
void teleport_rnd_snprintf_one(char *out, size_t size, const char *format, int value)
{
    snprintf(out, size, format, value);
}
void teleport_rnd_snprintf_two(char *out, size_t size, const char *format, int a, int b)
{
    snprintf(out, size, format, a, b);
}
void teleport_rnd_print_full(FILE *file, const char *format, int count,
                            const char *function, const char *args, int result,
                            const char *caller, const char *source, int line)
{
    fprintf(file, format, count, function, args, result, caller, source, line);
}
void teleport_rnd_print_file(FILE *file, const char *format, int count,
                            const char *function, const char *args, int result,
                            const char *source, int line)
{
    fprintf(file, format, count, function, args, result, source, line);
}
void teleport_rnd_print_plain(FILE *file, const char *format, int count,
                             const char *function, const char *args, int result)
{
    fprintf(file, format, count, function, args, result);
}
void teleport_rnd_print_display(FILE *file, const char *format, int count, int x, int result)
{
    fprintf(file, format, count, x, result);
}
void teleport_rnd_print_caller(FILE *file, const char *format,
                              const char *caller, const char *source, int line)
{
    fprintf(file, format, caller, source, line);
}
void teleport_rnd_print_source(FILE *file, const char *format, const char *source, int line)
{
    fprintf(file, format, source, line);
}

/* Shared terminal storage and native ABI only; ioctl.c decisions are JS. */
#include <termios.h>
#include <signal.h>
#include <stdint.h>
#ifndef TELEPORT_REFERENCE_IOCTL
struct termios termio;
#else
extern struct termios termio;
#endif
void *teleport_ioctl_termio(void) { return &termio; }
FILE *teleport_ioctl_stdin(void) { return stdin; }
char *teleport_ioctl_shellers(void) { return sysopt.shellers; }
int teleport_ioctl_fileno(FILE *stream) { return fileno(stream); }
int teleport_ioctl_getattr(int fd, void *state) { return tcgetattr(fd, state); }
int teleport_ioctl_setattr(int fd, int action, const void *state) { return tcsetattr(fd, action, state); }
uintptr_t teleport_ioctl_signal(int sig, uintptr_t handler)
{
    return (uintptr_t) signal(sig, (void (*)(int)) handler);
}
int teleport_ioctl_kill(int pid, int sig) { return kill(pid, sig); }
void teleport_ioctl_suspend(const char *message) { suspend_nhwindows(message); }
void teleport_ioctl_resume(void) { resume_nhwindows(); }
void teleport_ioctl_norep(const char *message) { Norep("%s", message); }
void teleport_ioctl_pline(const char *message) { pline("%s", message); }

/* Terminal storage and call ABI only; all unixtty policy lives in JavaScript. */
#ifndef TELEPORT_REFERENCE_UNIXTTY
struct termios inittyb, curttyb;
char erase_char, intr_char, kill_char;
#else
extern struct termios inittyb, curttyb;
extern char erase_char, intr_char, kill_char;
#endif
extern short ospeed;
void *teleport_unixtty_initial(void) { return &inittyb; }
void *teleport_unixtty_current(void) { return &curttyb; }
int teleport_unixtty_scalar(int index)
{
    switch (index) {
    case 0: return ospeed;
    case 1: return erase_char;
    case 2: return kill_char;
    default: return intr_char;
    }
}
void teleport_unixtty_set_scalar(int index, int value)
{
    switch (index) {
    case 0: ospeed = value; break;
    case 1: erase_char = value; break;
    case 2: kill_char = value; break;
    default: intr_char = value; break;
    }
}
int teleport_unixtty_iflag(int index)
{
    switch (index) {
    case 0: return iflags.echo;
    case 1: return iflags.cbreak;
    default: return iflags.window_inited;
    }
}
void teleport_unixtty_set_iflag(int index, int value)
{
    switch (index) {
    case 0: iflags.echo = value; break;
    case 1: iflags.cbreak = value; break;
    default: iflags.window_inited = value; break;
    }
}
int teleport_unixtty_window(void) { return windowprocs.wp_id; }
unsigned int teleport_unixtty_speed(const void *state) { return cfgetospeed(state); }
long teleport_unixtty_fpathconf(int fd, int name) { return fpathconf(fd, name); }
void teleport_unixtty_perror(const char *message) { perror(message); }
_Static_assert(__builtin_types_compatible_p(va_list, void *), "Review changed unixtty va_list ABI");
int teleport_unixtty_vprintf(const char *format, va_list arguments) { return vprintf(format, arguments); }
int teleport_unixtty_putchar(int value) { return putchar(value); }
void teleport_unixtty_exit(int value) { exit(value); }
void teleport_unixtty_raw_print(const char *message) { raw_print(message); }
void teleport_unixtty_exit_windows(const char *message) { exit_nhwindows(message); }

/* Shared were.c storage, bitfield ABI and original variadic call shapes only. */
void *teleport_were_global(int index)
{
    switch (index) {
    case 0: return mons;
    case 1: return &u;
    case 2: return &flags;
    case 3: return &gw;
    case 4: return &svc;
    case 5: return &gy;
    default: return &gm;
    }
}
int teleport_were_monster_bit(struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->msleeping;
    case 1: return mon->mfrozen;
    case 2: return mon->mcanmove;
    default: return mon->mpeaceful;
    }
}
void teleport_were_set_monster_bit(struct monst *mon, int index, int value)
{
    switch (index) {
    case 0: mon->msleeping = value; break;
    case 1: mon->mfrozen = value; break;
    case 2: mon->mcanmove = value; break;
    default: mon->mpeaceful = value; break;
    }
}
int teleport_were_roleplay_deaf(void) { return u.uroleplay.deaf; }
static const char *const teleport_were_callers[] = {
    "were_change", "new_were", "were_summon", "you_unwere"
};
int teleport_were_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("were.c", line, teleport_were_callers[caller]);
    return (rn2)(bound);
}
int teleport_were_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("were.c", line, teleport_were_callers[caller]);
    return (rnd)(bound);
}
void teleport_were_impossible(const char *format, const char *name) { impossible(format, name); }
void teleport_were_pline(const char *format, const char *a, const char *b) { pline(format, a, b); }
void teleport_were_hear(const char *format, const char *name) { You_hear(format, name); }
void teleport_were_feel(const char *format) { You_feel("%s", format); }
void teleport_were_sprintf(char *output, const char *format, const char *name) { Sprintf(output, format, name); }

/* Rogue level shared storage, bitfield and diagnostic ABI only. */
void *teleport_extralev_global(int index)
{
    switch (index) {
    case 0: return &gr;
    case 1: return &svn;
    case 2: return &gs;
    case 3: return &svr;
    case 4: return &svl;
    default: return mons;
    }
}
int teleport_extralev_object_bit(struct obj *object, int index)
{
    return index == 0 ? object->oerodeproof : object->known;
}
void teleport_extralev_set_object_bit(struct obj *object, int index, int value)
{
    if (index == 0) object->oerodeproof = value;
    else object->known = value;
}
int teleport_extralev_door_mask(struct rm *location) { return location->doormask; }
void teleport_extralev_set_door_mask(struct rm *location, int value) { location->doormask = value; }
static const char *const teleport_extralev_callers[] = {
    "roguejoin", "roguecorr", "miniwalk", "makeroguerooms", "corr", "makerogueghost"
};
int teleport_extralev_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("extralev.c", line, teleport_extralev_callers[caller]);
    return (rn2)(bound);
}
int teleport_extralev_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("extralev.c", line, teleport_extralev_callers[caller]);
    return (rnd)(bound);
}
void teleport_extralev_impossible_one(const char *format, int value) { impossible(format, value); }
void teleport_extralev_impossible_two(const char *format, int x, int y) { impossible(format, x, y); }

/* Player-monster shared storage, bitfields and native call metadata only. */
void *teleport_mplayer_global(int index)
{
    switch (index) {
    case 0: return mons;
    case 1: return objects;
    case 2: return &svl;
    case 3: return &u;
    case 4: return &gu;
    case 5: return (void *) &cg;
    default: return &svd;
    }
}
int teleport_mplayer_monster_bit(struct monst *mon, int index)
{
    return index == 0 ? mon->female : mon->mpeaceful;
}
void teleport_mplayer_set_monster_bit(struct monst *mon, int index, int value)
{
    if (index == 0) mon->female = value;
    else mon->mpeaceful = value;
}
int teleport_mplayer_object_bit(struct obj *object, int index)
{
    switch (index) {
    case 0: return object->oeroded;
    case 1: return object->oeroded2;
    case 2: return object->greased;
    default: return object->oerodeproof;
    }
}
void teleport_mplayer_set_object_bit(struct obj *object, int index, int value)
{
    switch (index) {
    case 0: object->oeroded = value; break;
    case 1: object->oeroded2 = value; break;
    case 2: object->greased = value; break;
    default: object->oerodeproof = value; break;
    }
}
int teleport_mplayer_class_bit(struct objclass *type) { return type->oc_merge; }
#ifdef TELEPORT_MPLAYER_LITERAL_CAPACITY
static char teleport_mplayer_literals[TELEPORT_MPLAYER_LITERAL_CAPACITY];
void *teleport_mplayer_literal_storage(void) { return teleport_mplayer_literals; }
size_t teleport_mplayer_literal_capacity(void) { return sizeof teleport_mplayer_literals; }
#endif
static const char *const teleport_mplayer_callers[] = {
    "dev_name", "get_mplname", "mk_mplayer_armor", "mk_mplayer", "create_mplayers", "mplayer_talk"
};
int teleport_mplayer_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("mplayer.c", line, teleport_mplayer_callers[caller]);
    return (rn2)(bound);
}
int teleport_mplayer_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("mplayer.c", line, teleport_mplayer_callers[caller]);
    return (rnd)(bound);
}
int teleport_mplayer_dice(int count, int sides, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("mplayer.c", line, teleport_mplayer_callers[caller]);
    return (d)(count, sides);
}
void teleport_mplayer_impossible(const char *message) { impossible("%s", message); }
void teleport_mplayer_verbalize(const char *format, const char *message) { verbalize(format, message); }

/* Experience shared addresses, monster bits, printf and assert ABI only. */
void *teleport_exper_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gu;
    case 2: return &gy;
    case 3: return &flags;
    case 4: return &disp;
    case 5: return &svk;
    default: return mons;
    }
}
int teleport_exper_monster_bit(struct monst *mon, int index)
{
    return index == 0 ? mon->mrevived : mon->mcloned;
}
void teleport_exper_set_monster_bit(struct monst *mon, int index, int value)
{
    if (index == 0) mon->mrevived = value;
    else mon->mcloned = value;
}
static const char *const teleport_exper_callers[] = { "newpw", "rndexp" };
int teleport_exper_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("exper.c", line, teleport_exper_callers[caller]);
    return (rn2)(bound);
}
int teleport_exper_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("exper.c", line, teleport_exper_callers[caller]);
    return (rnd)(bound);
}
void teleport_exper_pline(const char *format, const char *prefix, int level) { pline(format, prefix, level); }
void teleport_exper_feel(const char *message) { You_feel("%s", message); }
void teleport_exper_log_plain(long category, const char *message) { livelog_printf(category, "%s", message); }
void teleport_exper_log_int(long category, const char *format, int value) { livelog_printf(category, format, value); }
void teleport_exper_log_prefix(long category, const char *format, const char *prefix, int value) { livelog_printf(category, format, prefix, value); }
#ifdef TELEPORT_EXPER_ASSERT_LINE
void teleport_exper_assert_fail(void)
{
    __assert_fail(TELEPORT_EXPER_ASSERT_CONDITION, "exper.c", TELEPORT_EXPER_ASSERT_LINE, "losexp");
}
#endif

/* Cave map shared storage/bitfield ABI only; generation decisions are JS. */
void *teleport_mkmap_global(int index)
{
    switch (index) {
    case 0: return &svl;
    case 1: return &gn;
    case 2: return &gm;
    case 3: return &svn;
    case 4: return &svr;
    case 5: return &gs;
    default: return &u;
    }
}
int teleport_mkmap_terrain_bit(struct rm *location, int index)
{
    switch (index) {
    case 0: return location->roomno;
    case 1: return location->lit;
    case 2: return location->edge;
    default: return location->icedpool;
    }
}
void teleport_mkmap_set_terrain_bit(struct rm *location, int index, int value)
{
    switch (index) {
    case 0: location->roomno = value; break;
    case 1: location->lit = value; break;
    case 2: location->edge = value; break;
    default: location->icedpool = value; break;
    }
}
int teleport_mkmap_level_bit(int index)
{
    return index == 0 ? svl.level.flags.is_maze_lev : svl.level.flags.is_cavernous_lev;
}
void teleport_mkmap_set_level_bit(int index, int value)
{
    if (index == 0) svl.level.flags.is_maze_lev = value;
    else svl.level.flags.is_cavernous_lev = value;
}
static const char *const teleport_mkmap_callers[] = { "init_fill", "join_map", "litstate_rnd" };
int teleport_mkmap_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("mkmap.c", line, teleport_mkmap_callers[caller]);
    return (rn2)(bound);
}
int teleport_mkmap_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled())
        rng_log_set_caller("mkmap.c", line, teleport_mkmap_callers[caller]);
    return (rnd)(bound);
}
void teleport_mkmap_impossible(const char *message) { impossible("%s", message); }

/* TTY getline storage/pointers and variadic/window/stdout ABI only. */
struct WinDesc;
struct DisplayDesc;
extern struct WinDesc *wins[];
extern struct DisplayDesc *ttyDisplay;
#ifndef TELEPORT_REFERENCE_GETLINE
char morc = 0;
#else
extern char morc;
#endif
void *teleport_getline_global(int index)
{
    switch (index) {
    case 0: return wins;
    case 1: return &ttyDisplay;
    case 2: return &iflags;
    case 3: return &gt;
    case 4: return &gi;
    default: return &program_state;
    }
}
int teleport_getline_window_message(void) { return WIN_MESSAGE; }
int teleport_getline_scalar(int index)
{
    switch (index) {
    case 0: return morc;
    case 1: return erase_char;
    default: return kill_char;
    }
}
void teleport_getline_set_scalar(int index, int value)
{
    switch (index) {
    case 0: morc = value; break;
    case 1: erase_char = value; break;
    default: kill_char = value; break;
    }
}
FILE *teleport_getline_stdout(void) { return stdout; }
int teleport_getline_fflush(FILE *stream) { return fflush(stream); }
void teleport_getline_clear_window(winid window) { clear_nhwindow(window); }
void teleport_getline_custompline(unsigned flags, const char *format, const char *query) { custompline(flags, format, query); }
void teleport_getline_pline(const char *format, const char *prefix, const char *command) { pline(format, prefix, command); }
#ifdef TELEPORT_GETLINE_LITERAL_CAPACITY
static char teleport_getline_literals[TELEPORT_GETLINE_LITERAL_CAPACITY];
void *teleport_getline_literal_storage(void) { return teleport_getline_literals; }
size_t teleport_getline_literal_capacity(void) { return sizeof teleport_getline_literals; }
#endif

/* Marker-writing address/bitfield, native callback and formatting ABI only. */
void *teleport_write_global(int index)
{
    switch (index) {
    case 0: return objects;
    case 1: return (void *) obj_descr;
    case 2: return &svb;
    case 3: return &u;
    case 4: return &gu;
    case 5: return &gy;
    default: return &svp;
    }
}
int teleport_write_object_bit(struct obj *object, int index)
{
    switch (index) {
    case 0: return object->dknown;
    case 1: return object->bknown;
    case 2: return object->blessed;
    default: return object->cursed;
    }
}
void teleport_write_set_object_bit(struct obj *object, int index, int value)
{
    switch (index) {
    case 0: object->dknown = value; break;
    case 1: object->bknown = value; break;
    case 2: object->blessed = value; break;
    default: object->cursed = value; break;
    }
}
int teleport_write_class_bit(struct objclass *object, int index)
{
    return index == 0 ? object->oc_name_known : object->oc_encountered;
}
extern int teleport_write_callback(struct obj *);
static int teleport_write_selection(struct obj *object)
{
    return teleport_write_callback(object);
}
struct obj *teleport_write_getobj(const char *verb, unsigned flags)
{
    return getobj(verb, teleport_write_selection, flags);
}
void teleport_write_getlin(const char *query, char *out) { getlin(query, out); }
void teleport_write_message(int kind, const char *format, const char *a, const char *b)
{
    switch (kind) {
    case 0: pline(format, a, b); break;
    case 1: You(format, a, b); break;
    case 2: Your(format, a, b); break;
    case 3: You_cant(format, a, b); break;
    case 4: There(format, a, b); break;
    case 5: pline_The(format, a, b); break;
    default: impossible(format, a, b); break;
    }
}
void teleport_write_sprintf(char *out, const char *format, const char *a, const char *b)
{
    Sprintf(out, format, a, b);
}
void teleport_write_livelog(long category, const char *format, const char *value)
{
    livelog_printf(category, format, value);
}
int teleport_write_rn2(int bound, int line)
{
    if (rng_log_enabled()) rng_log_set_caller("write.c", line, "dowrite");
    return (rn2)(bound);
}
int teleport_write_rnl(int bound, int line)
{
    if (rng_log_enabled()) rng_log_set_caller("write.c", line, "dowrite");
    return (rnl)(bound);
}
#ifdef TELEPORT_WRITE_LITERAL_CAPACITY
static char teleport_write_literals[TELEPORT_WRITE_LITERAL_CAPACITY];
void *teleport_write_literal_storage(void) { return teleport_write_literals; }
size_t teleport_write_literal_capacity(void) { return sizeof teleport_write_literals; }
#endif

/* Metadata private addressable storage and fixed native formatting ABI only. */
static char teleport_mdlib_optbuf[COLBUFSZ];
static struct version_info teleport_mdlib_version;
static char teleport_mdlib_compat[BUFSZ];
void *teleport_mdlib_storage(int index)
{
    switch (index) {
    case 0: return teleport_mdlib_optbuf;
    case 1: return &teleport_mdlib_version;
    default: return teleport_mdlib_compat;
    }
}
void teleport_mdlib_format_string(char *out, const char *format, const char *value)
{
    Sprintf(out, format, value);
}
void teleport_mdlib_format_int(char *out, const char *format, int value)
{
    Sprintf(out, format, value);
}
void teleport_mdlib_format_three(char *out, const char *format, int a, int b, int c)
{
    Sprintf(out, format, a, b, c);
}
void teleport_mdlib_format_version(char *out, const char *format, int a,
                                  const char *b, int c, const char *d, int e)
{
    Sprintf(out, format, a, b, c, d, e);
}
void teleport_mdlib_format_heading(char *out, const char *format, const char *a,
                                  int b, int c, int d, const char *e)
{
    Sprintf(out, format, a, b, c, d, e);
}
void teleport_mdlib_snprintf(int kind, char *out, size_t size, const char *format,
                            const char *a, const char *b, const char *c,
                            const char *d, const char *e, const char *f)
{
    nh_snprintf(kind == 0 ? "version_id_string" : "bannerc_string",
                kind == 0 ? TELEPORT_MDLIB_VERSION_LINE : TELEPORT_MDLIB_BANNER_LINE,
                out, size, format, a, b, c, d, e, f);
}
#ifdef TELEPORT_MDLIB_LITERAL_CAPACITY
/* Two copies allow a configured string both alone and in a literal prefix. */
static char teleport_mdlib_literals[TELEPORT_MDLIB_LITERAL_CAPACITY
    + 2 * (sizeof(PORT_ID) + sizeof(DEFAULT_WINDOW_SYS))
#ifdef DEV_RANDOM
    + 2 * sizeof(DEV_RANDOM)
#endif
];
void *teleport_mdlib_literal_storage(void) { return teleport_mdlib_literals; }
size_t teleport_mdlib_literal_capacity(void) { return sizeof teleport_mdlib_literals; }
#endif

/* Quest shared storage, native bitfields and fixed formatting ABI only. */
void *teleport_quest_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &svq;
    case 2: return &svd;
    case 3: return &svc;
    case 4: return &flags;
    case 5: return &gi;
    case 6: return &gf;
    default: return mons;
    }
}
int teleport_quest_bit(int index)
{
    switch (index) {
    case 0: return svq.quest_status.first_start;
    case 1: return svq.quest_status.not_ready;
    case 2: return svq.quest_status.killed_nemesis;
    case 3: return svq.quest_status.first_locate;
    case 4: return svq.quest_status.made_goal;
    case 5: return svq.quest_status.killed_leader;
    case 6: return svq.quest_status.touched_artifact;
    case 7: return svq.quest_status.got_quest;
    case 8: return svq.quest_status.got_thanks;
    case 9: return svq.quest_status.pissed_off;
    case 10: return svq.quest_status.met_nemesis;
    case 11: return svq.quest_status.cheater;
    case 12: return svq.quest_status.met_leader;
    default: return svq.quest_status.in_battle;
    }
}
void teleport_quest_set_bit(int index, int value)
{
    switch (index) {
    case 0: svq.quest_status.first_start = value; break;
    case 1: svq.quest_status.not_ready = value; break;
    case 2: svq.quest_status.killed_nemesis = value; break;
    case 3: svq.quest_status.first_locate = value; break;
    case 4: svq.quest_status.made_goal = value; break;
    case 5: svq.quest_status.killed_leader = value; break;
    case 6: svq.quest_status.touched_artifact = value; break;
    case 7: svq.quest_status.got_quest = value; break;
    case 8: svq.quest_status.got_thanks = value; break;
    case 9: svq.quest_status.pissed_off = value; break;
    case 10: svq.quest_status.met_nemesis = value; break;
    case 11: svq.quest_status.cheater = value; break;
    case 12: svq.quest_status.met_leader = value; break;
    default: svq.quest_status.in_battle = value; break;
    }
}
int teleport_quest_hero_bit(int index)
{
    switch (index) {
    case 0: return u.uevent.qcompleted;
    case 1: return u.uevent.qexpelled;
    case 2: return u.uhave.amulet;
    case 3: return u.uhave.questart;
    default: return u.uroleplay.deaf;
    }
}
void teleport_quest_set_hero_bit(int index, int value)
{
    switch (index) {
    case 0: u.uevent.qcompleted = value; break;
    case 1: u.uevent.qexpelled = value; break;
    case 2: u.uhave.amulet = value; break;
    case 3: u.uhave.questart = value; break;
    default: u.uroleplay.deaf = value; break;
    }
}
int teleport_quest_monster_bit(struct monst *monster, int index)
{
    switch (index) {
    case 0: return monster->mpeaceful;
    case 1: return monster->msleeping;
    case 2: return monster->mfrozen;
    default: return monster->mcanmove;
    }
}
void teleport_quest_set_monster_bit(struct monst *monster, int index, int value)
{
    switch (index) {
    case 0: monster->mpeaceful = value; break;
    case 1: monster->msleeping = value; break;
    case 2: monster->mfrozen = value; break;
    default: monster->mcanmove = value; break;
    }
}
int teleport_quest_trap_type(struct trap *trap) { return trap->ttyp; }
void teleport_quest_message(int kind, const char *format, const char *a, const char *b)
{
    switch (kind) {
    case 0: pline(format, a, b); break;
    case 1: You(format, a, b); break;
    case 2: verbalize(format, a, b); break;
    default: impossible(format, a, b); break;
    }
}
void teleport_quest_you_ints(const char *format, int a, int b) { You(format, a, b); }
void teleport_quest_livelog(long category, const char *format, const char *name)
{
    livelog_printf(category, format, name);
}
int teleport_quest_rn2(int bound, int line)
{
    if (rng_log_enabled()) rng_log_set_caller("quest.c", line, "nemesis_speaks");
    return (rn2)(bound);
}
#ifdef TELEPORT_QUEST_LITERAL_CAPACITY
static char teleport_quest_literals[TELEPORT_QUEST_LITERAL_CAPACITY];
void *teleport_quest_literal_storage(void) { return teleport_quest_literals; }
size_t teleport_quest_literal_capacity(void) { return sizeof teleport_quest_literals; }
#endif

/* Minion shared storage, packed fields, native scanning and message ABI only. */
void *teleport_minion_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &gi;
    case 3: return &gm;
    case 4: return &svm;
    case 5: return &svd;
    case 6: return &flags;
    case 7: return &disp;
    case 8: return &svl;
    default: return mons;
    }
}
struct obj *teleport_minion_uwep(void) { return uwep; }
int teleport_minion_roleplay_deaf(void) { return u.uroleplay.deaf; }
int teleport_minion_monster_bit(struct monst *monster, int index)
{
    switch (index) {
    case 0: return monster->isgd;
    case 1: return monster->ispriest;
    case 2: return monster->isminion;
    case 3: return monster->mpeaceful;
    case 4: return monster->minvis;
    default: return monster->perminvis;
    }
}
void teleport_minion_set_monster_bit(struct monst *monster, int index, int value)
{
    switch (index) {
    case 0: monster->isgd = value; break;
    case 1: monster->ispriest = value; break;
    case 2: monster->isminion = value; break;
    case 3: monster->mpeaceful = value; break;
    case 4: monster->minvis = value; break;
    default: monster->perminvis = value; break;
    }
}
int teleport_minion_sscanf(const char *buffer, const char *format, long *value)
{
    return sscanf(buffer, format, value);
}
void teleport_minion_message(int kind, const char *format,
                            const char *a, const char *b, const char *c)
{
    switch (kind) {
    case 0: pline(format, a, b, c); break;
    case 1: pline_The(format, a, b, c); break;
    case 2: You(format, a, b, c); break;
    case 3: You_feel(format, a, b, c); break;
    case 4: verbalize(format, a, b, c); break;
    case 5: impossible(format, a, b, c); break;
    default: panic(format, a, b, c); break;
    }
}
void teleport_minion_money_message(int kind, const char *format,
                                  const char *name, long value, const char *units)
{
    if (kind == 0) pline(format, name, value, units);
    else You(format, name, value, units);
}
void teleport_minion_livelog(long category, const char *format,
                            const char *name, long value, const char *units)
{
    livelog_printf(category, format, name, value, units);
}
static const char *const teleport_minion_callers[] = {
    "msummon", "summon_minion", "demon_talk", "dprince", "dlord",
    "lose_guardian_angel", "gain_guardian_angel"
};
int teleport_minion_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("minion.c", line, teleport_minion_callers[caller]);
    return (rn2)(bound);
}
int teleport_minion_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("minion.c", line, teleport_minion_callers[caller]);
    return (rnd)(bound);
}
int teleport_minion_d(int number, int sides, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("minion.c", line, teleport_minion_callers[caller]);
    return (d)(number, sides);
}
#ifdef TELEPORT_MINION_LITERAL_CAPACITY
static char teleport_minion_literals[TELEPORT_MINION_LITERAL_CAPACITY];
void *teleport_minion_literal_storage(void) { return teleport_minion_literals; }
size_t teleport_minion_literal_capacity(void) { return sizeof teleport_minion_literals; }
#endif

/* Item action ABI only: shared storage, native function identities and calls. */
const void *teleport_iactions_global(int index)
{
    switch (index) {
    case 0: return objects;
    case 1: return &u;
    case 2: return &gy;
    case 3: return &svl;
    default: return &cg;
    }
}
struct obj *teleport_iactions_equipment(int index)
{
    switch (index) {
    case 0: return uwep;
    case 1: return uswapwep;
    case 2: return uquiver;
    case 3: return uamul;
    case 4: return uleft;
    case 5: return uright;
    case 6: return ublindf;
    default: return uarms;
    }
}
int teleport_iactions_object_bit(struct obj *obj, int index)
{
    switch (index) {
    case 0: return obj->lamplit;
    case 1: return obj->dknown;
    case 2: return obj->unpaid;
    case 3: return obj->cknown;
    default: return obj->known;
    }
}
int teleport_iactions_class_bit(struct objclass *oc, int index)
{
    switch (index) {
    case 0: return oc->oc_name_known;
    case 1: return oc->oc_tough;
    case 2: return oc->oc_unique;
    default: return oc->oc_bimanual;
    }
}
int teleport_iactions_hero_bit(int index)
{
    return index == 0 ? u.uswallow : u.twoweap;
}
const glyph_info *teleport_iactions_nul_glyphinfo(void) { return &nul_glyphinfo; }
static int (*const teleport_iactions_commands[])(void) = {
    dowield, remarm_swapwep, dowieldquiver, donull, doapply, dip_into,
    docallcmd, dodrop, do_reqmenu, doeat, doengrave, dofire, doorganize,
    adjust_split, dosacrifice, dopay, dodrink, doread, dorub, dothrow,
    ia_dotakeoff, dotip, doinvoke, dowear, doswapweapon, dotwoweapon,
    dozap, dowhatis
};
uintptr_t teleport_iactions_command(int index)
{
    return (uintptr_t) teleport_iactions_commands[index];
}
void teleport_iactions_cmdq_add_ec(int queue, uintptr_t command)
{
    cmdq_add_ec(queue, (int (*)(void)) command);
}
void teleport_iactions_free(void *ptr) { free(ptr); }
winid teleport_iactions_create_window(int type) { return create_nhwindow(type); }
void teleport_iactions_start_menu(winid win, unsigned long behavior)
{
    start_menu(win, behavior);
}
void teleport_iactions_end_menu(winid win, const char *prompt) { end_menu(win, prompt); }
void teleport_iactions_destroy_window(winid win) { destroy_nhwindow(win); }
void teleport_iactions_format_strings(char *out, const char *format,
                                     const char *a, const char *b, const char *c)
{
    Sprintf(out, format, a, b, c);
}
void teleport_iactions_format_unwield(char *out, const char *format,
                                     const char *a, int b, const char *c,
                                     const char *d, const char *e)
{
    Sprintf(out, format, a, b, c, d, e);
}
void teleport_iactions_impossible(const char *format, int act) { impossible(format, act); }
#ifndef NDEBUG
void teleport_iactions_assert_fail(void)
{
    __assert_fail(TELEPORT_IACTIONS_ASSERT_CONDITION, "iactions.c",
                  TELEPORT_IACTIONS_ASSERT_LINE, "itemactions");
}
#endif
#ifdef TELEPORT_IACTIONS_LITERAL_CAPACITY
static char teleport_iactions_literals[TELEPORT_IACTIONS_LITERAL_CAPACITY];
void *teleport_iactions_literal_storage(void) { return teleport_iactions_literals; }
size_t teleport_iactions_literal_capacity(void) { return sizeof teleport_iactions_literals; }
#endif

/* Selection ABI only: live globals, packed terrain and native callbacks. */
const void *teleport_selvar_global(int index)
{
    switch (index) {
    case 0: return &cg;
    case 1: return &svl;
    case 2: return &gc;
    default: return &svr;
    }
}
int teleport_selvar_terrain_bit(coordxy x, coordxy y, int index)
{
    switch (index) {
    case 0: return levl[x][y].lit;
    case 1: return levl[x][y].edge;
    default: return levl[x][y].roomno;
    }
}
int teleport_selvar_flood_check(uintptr_t callback, coordxy x, coordxy y)
{
    return ((int (*)(coordxy, coordxy)) callback)(x, y);
}
void teleport_selvar_iterate(uintptr_t callback, coordxy x, coordxy y, void *arg)
{
    ((void (*)(coordxy, coordxy, void *)) callback)(x, y, arg);
}
void teleport_selvar_free(void *ptr) { free(ptr); }
static const char *const teleport_selvar_callers[] = {
    "selection_filter_percent", "selection_filter_mapchar", "selection_rndcoord",
    "selection_do_gradient", "selection_do_randline"
};
int teleport_selvar_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("selvar.c", line, teleport_selvar_callers[caller]);
    return (rn2)(bound);
}
void teleport_selvar_panic(const char *message) { panic("%s", message); }
void teleport_selvar_impossible(const char *message) { impossible("%s", message); }
void teleport_selvar_format(char *out, const char *format, const char *shape, int dx, int dy)
{
    Sprintf(out, format, shape, dx, dy);
}
#ifdef TELEPORT_SELVAR_LITERAL_CAPACITY
static char teleport_selvar_literals[TELEPORT_SELVAR_LITERAL_CAPACITY];
void *teleport_selvar_literal_storage(void) { return teleport_selvar_literals; }
size_t teleport_selvar_literal_capacity(void) { return sizeof teleport_selvar_literals; }
#endif

/* Theft ABI only: native storage views, packed fields and callback identity. */
void *teleport_steal_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &gi;
    case 3: return &gm;
    case 4: return &ga;
    case 5: return &gn;
    case 6: return &gs;
    case 7: return &gt;
    case 8: return &gk;
    case 9: return &go;
    case 10: return &flags;
    case 11: return &iflags;
    case 12: return &disp;
    case 13: return &svl;
    case 14: return mons;
    case 15: return objects;
    default: return &gv;
    }
}
struct obj *teleport_steal_equipment(int index)
{
    switch (index) {
    case 0: return uskin;
    case 1: return uarm;
    case 2: return uarmc;
    case 3: return uarmf;
    case 4: return uarmg;
    case 5: return uarmh;
    case 6: return uarms;
    case 7: return uarmu;
    case 8: return uwep;
    case 9: return uswapwep;
    case 10: return uquiver;
    case 11: return uball;
    case 12: return uchain;
    case 13: return uleft;
    default: return uright;
    }
}
int teleport_steal_object_bit(struct obj *obj, int index)
{
    switch (index) {
    case 0: return obj->unpaid;
    case 1: return obj->cursed;
    case 2: return obj->in_use;
    case 3: return obj->no_charge;
    default: return obj->how_lost;
    }
}
void teleport_steal_set_object_bit(struct obj *obj, int index, int value)
{
    switch (index) {
    case 0: obj->unpaid = value; break;
    case 1: obj->cursed = value; break;
    case 2: obj->in_use = value; break;
    case 3: obj->no_charge = value; break;
    default: obj->how_lost = value; break;
    }
}
int teleport_steal_monster_bit(struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->female;
    case 1: return mon->mavenge;
    case 2: return mon->iswiz;
    default: return mon->isgd;
    }
}
void teleport_steal_set_monster_bit(struct monst *mon, int index, int value)
{
    if (index == 1) mon->mavenge = value;
}
int teleport_steal_hero_bit(int index)
{
    switch (index) {
    case 0: return u.uswallow;
    case 1: return u.twoweap;
    case 2: return u.uhave.amulet;
    case 3: return u.uhave.bell;
    case 4: return u.uhave.book;
    case 5: return u.uhave.menorah;
    default: return u.uhandedness;
    }
}
int teleport_steal_class_bit(struct objclass *oc, int index)
{
    (void) index;
    return oc->oc_bimanual;
}
int teleport_steal_roomno(coordxy x, coordxy y) { return levl[x][y].roomno; }
extern int teleport_steal_callback_stealarm(void);
extern int teleport_steal_callback_unstolenarm(void);
int teleport_steal_after_stealarm(void) { return teleport_steal_callback_stealarm(); }
int teleport_steal_after_unstolenarm(void) { return teleport_steal_callback_unstolenarm(); }
uintptr_t teleport_steal_callback_pointer(int index)
{
    return (uintptr_t) (index == 0 ? teleport_steal_after_stealarm : teleport_steal_after_unstolenarm);
}
char *teleport_steal_distant_name(struct obj *obj) { return distant_name(obj, doname); }
static const char *const teleport_steal_callers[] = { "somegold", "stealgold", "steal", "stealamulet" };
int teleport_steal_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("steal.c", line, teleport_steal_callers[caller]);
    return (rn2)(bound);
}
int teleport_steal_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("steal.c", line, teleport_steal_callers[caller]);
    return (rnd)(bound);
}
void teleport_steal_message(int kind, const char *format, const char *a,
                            const char *b, const char *c, const char *d)
{
    switch (kind) {
    case 0: pline(format, a, b, c, d); break;
    case 1: urgent_pline(format, a, b, c, d); break;
    case 2: You(format, a, b, c, d); break;
    case 3: Your(format, a, b, c, d); break;
    default: impossible(format, a, b, c, d); break;
    }
}
void teleport_steal_impossible_int(const char *format, int value) { impossible(format, value); }
void teleport_steal_mon_message(struct monst *mon, const char *format, const char *a, const char *b)
{
    pline_mon(mon, format, a, b);
}
#ifndef NDEBUG
void teleport_steal_assert_fail(void)
{
    __assert_fail(TELEPORT_STEAL_ASSERT_CONDITION, "steal.c", TELEPORT_STEAL_ASSERT_LINE, "steal");
}
#endif
#ifdef TELEPORT_STEAL_LITERAL_CAPACITY
static char teleport_steal_literals[TELEPORT_STEAL_LITERAL_CAPACITY];
void *teleport_steal_literal_storage(void) { return teleport_steal_literals; }
size_t teleport_steal_literal_capacity(void) { return sizeof teleport_steal_literals; }
#endif

/* Sitting ABI only: native state views, packed fields, prompts and varargs. */
const void *teleport_sit_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &gi;
    case 3: return &flags;
    case 4: return &iflags;
    case 5: return &disp;
    case 6: return &svl;
    case 7: return &svd;
    case 8: return &cg;
    case 9: return &gv;
    case 10: return mons;
    case 11: return objects;
    case 12: return defsyms;
    default: return genders;
    }
}
struct obj *teleport_sit_equipment(int index)
{
    switch (index) {
    case 0: return uwep;
    case 1: return uarm;
    default: return uarmf;
    }
}
int teleport_sit_hero_bit(int index)
{
    switch (index) {
    case 0: return u.uhave.amulet;
    case 1: return u.uundetected;
    case 2: return u.uswallow;
    case 3: return u.uevent.uhand_of_elbereth;
    case 4: return u.uinwater;
    default: return u.uroleplay.deaf;
    }
}
void teleport_sit_set_hero_bit(int index, int value)
{
    if (index == 1) u.uundetected = value;
}
int teleport_sit_object_bit(struct obj *obj, int index)
{
    switch (index) {
    case 0: return obj->greased;
    case 1: return obj->blessed;
    case 2: return obj->known;
    case 3: return obj->cursed;
    default: return obj->bknown;
    }
}
void teleport_sit_set_object_bit(struct obj *obj, int index, int value)
{
    switch (index) {
    case 0: obj->greased = value; break;
    case 1: obj->blessed = value; break;
    case 2: obj->known = value; break;
    case 3: obj->cursed = value; break;
    default: obj->bknown = value; break;
    }
}
int teleport_sit_class_bit(struct objclass *oc, int index)
{
    (void) index;
    return oc->oc_material;
}
int teleport_sit_terrain_flags(coordxy x, coordxy y) { return levl[x][y].flags; }
void teleport_sit_set_terrain_flags(coordxy x, coordxy y, int value) { levl[x][y].flags = value; }
int teleport_sit_level_bit(int index) { (void) index; return svl.level.flags.nommap; }
int teleport_sit_trap_type(struct trap *trap) { return trap->ttyp; }
const char *teleport_sit_common_string(int index) { return index == 0 ? Never_mind : NH_BLACK; }
void teleport_sit_getlin(const char *query, char *out) { getlin(query, out); }
char teleport_sit_y_n(const char *query) { return y_n(query); }
static const char *const teleport_sit_callers[] = {
    "throne_sit_effect", "special_throne_effect", "dosit", "rndcurse", "attrcurse"
};
int teleport_sit_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("sit.c", line, teleport_sit_callers[caller]);
    return (rn2)(bound);
}
int teleport_sit_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("sit.c", line, teleport_sit_callers[caller]);
    return (rnd)(bound);
}
int teleport_sit_d(int number, int sides, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("sit.c", line, teleport_sit_callers[caller]);
    return (d)(number, sides);
}
void teleport_sit_message(int kind, const char *format, const char *a, const char *b)
{
    switch (kind) {
    case 0: pline(format, a, b); break;
    case 1: pline_The(format, a, b); break;
    case 2: You(format, a, b); break;
    case 3: Your(format, a, b); break;
    case 4: You_feel(format, a, b); break;
    case 5: verbalize(format, a, b); break;
    case 6: You_cant(format, a, b); break;
    case 7: There(format, a, b); break;
    default: impossible(format, a, b); break;
    }
}
#ifdef TELEPORT_SIT_LITERAL_CAPACITY
static char teleport_sit_literals[TELEPORT_SIT_LITERAL_CAPACITY];
void *teleport_sit_literal_storage(void) { return teleport_sit_literals; }
size_t teleport_sit_literal_capacity(void) { return sizeof teleport_sit_literals; }
#endif

/* Fountain ABI only: native globals, packed fields and callback adapters. */
const void *teleport_fountain_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &gi;
    case 3: return &svm;
    case 4: return &svl;
    case 5: return &gu;
    case 6: return &disp;
    case 7: return &flags;
    case 8: return mons;
    case 9: return objects;
    case 10: return obj_descr;
    case 11: return &gv;
    default: return genders;
    }
}
struct obj *teleport_fountain_equipment(int index) { (void) index; return uarmg; }
const struct obj *teleport_fountain_hands(void) { return &hands_obj; }
int teleport_fountain_object_bit(struct obj *obj, int index)
{
    switch (index) {
    case 0: return obj->cursed;
    case 1: return obj->blessed;
    case 2: return obj->oerodeproof;
    case 3: return obj->oeroded;
    case 4: return obj->oeroded2;
    default: return obj->dknown;
    }
}
void teleport_fountain_set_object_bit(struct obj *obj, int index, int value)
{
    switch (index) {
    case 0: obj->cursed = value; break;
    case 1: obj->blessed = value; break;
    case 2: obj->oerodeproof = value; break;
    case 3: obj->oeroded = value; break;
    case 4: obj->oeroded2 = value; break;
    default: obj->dknown = value; break;
    }
}
int teleport_fountain_monster_bit(struct monst *mon, int index)
{
    return index == 0 ? mon->msleeping : mon->mpeaceful;
}
void teleport_fountain_set_monster_bit(struct monst *mon, int index, int value)
{
    if (index == 0) mon->msleeping = value;
    else mon->mpeaceful = value;
}
int teleport_fountain_terrain_bit(coordxy x, coordxy y, int index)
{
    return index == 0 ? levl[x][y].looted : levl[x][y].blessedftn;
}
void teleport_fountain_set_terrain_bit(coordxy x, coordxy y, int index, int value)
{
    if (index == 0) levl[x][y].looted = value;
    else levl[x][y].blessedftn = value;
}
int teleport_fountain_terrain_flags(coordxy x, coordxy y) { return levl[x][y].flags; }
void teleport_fountain_set_terrain_flags(coordxy x, coordxy y, int value) { levl[x][y].flags = value; }
int teleport_fountain_hero_bit(int index) { (void) index; return u.uroleplay.deaf; }
const char *teleport_fountain_common_string(int index)
{
    return index == 0 ? something : nothing_seems_to_happen;
}
extern void teleport_fountain_callback_gush(coordxy, coordxy, void *);
extern boolean teleport_fountain_callback_watch(struct monst *);
void teleport_fountain_gush_callback(coordxy x, coordxy y, void *poolcnt)
{
    teleport_fountain_callback_gush(x, y, poolcnt);
}
boolean teleport_fountain_watch_callback(struct monst *mon)
{
    return teleport_fountain_callback_watch(mon);
}
void teleport_fountain_clear_area(coordxy x, coordxy y, int range, void *poolcnt)
{
    do_clear_area(x, y, range, teleport_fountain_gush_callback, poolcnt);
}
struct monst *teleport_fountain_get_iter_mons(void)
{
    return get_iter_mons(teleport_fountain_watch_callback);
}
winid teleport_fountain_win_message(void) { return WIN_MESSAGE; }
void teleport_fountain_display_window(winid win, boolean blocking) { display_nhwindow(win, blocking); }
char teleport_fountain_y_n(const char *query) { return y_n(query); }
static const char *const teleport_fountain_callers[] = {
    "dowatersnakes", "dowaterdemon", "dowaternymph", "gush", "dofindgem",
    "dryup", "drinkfountain", "dipfountain", "drinksink", "dipsink"
};
int teleport_fountain_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("fountain.c", line, teleport_fountain_callers[caller]);
    return (rn2)(bound);
}
int teleport_fountain_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("fountain.c", line, teleport_fountain_callers[caller]);
    return (rnd)(bound);
}
void teleport_fountain_message(int kind, const char *format, const char *a,
                               const char *b, const char *c, const char *d)
{
    switch (kind) {
    case 0: pline(format, a, b, c, d); break;
    case 1: pline_The(format, a, b, c, d); break;
    case 2: You(format, a, b, c, d); break;
    case 3: Your(format, a, b, c, d); break;
    case 4: You_feel(format, a, b, c, d); break;
    case 5: You_hear(format, a, b, c, d); break;
    case 6: verbalize(format, a, b, c, d); break;
    default: You_see(format, a, b, c, d); break;
    }
}
void teleport_fountain_format(char *out, const char *format, const char *value)
{
    Sprintf(out, format, value);
}
void teleport_fountain_livelog(long category, const char *format,
                              const char *a, const char *b, const char *c)
{
    livelog_printf(category, format, a, b, c);
}
#ifdef TELEPORT_FOUNTAIN_LITERAL_CAPACITY
static char teleport_fountain_literals[TELEPORT_FOUNTAIN_LITERAL_CAPACITY];
void *teleport_fountain_literal_storage(void) { return teleport_fountain_literals; }
size_t teleport_fountain_literal_capacity(void) { return sizeof teleport_fountain_literals; }
#endif

/* Object catalogue ABI only. Authoritative initializer rows live in JS. */
#ifndef TELEPORT_REFERENCE_OBJECTS
struct objdescr obj_descr[NUM_OBJECTS + 1];
struct objclass objects[NUM_OBJECTS + 1];
#endif
static struct objdescr teleport_objects_descr_init[NUM_OBJECTS + 1];
static struct objclass teleport_objects_init[NUM_OBJECTS + 1];
void *teleport_objects_storage(int index)
{
    switch (index) {
    case 0: return obj_descr;
    case 1: return objects;
    case 2: return teleport_objects_descr_init;
    default: return teleport_objects_init;
    }
}
void teleport_objects_set_bit(struct objclass *row, int index, unsigned value)
{
    switch (index) {
    case 0: row->oc_name_known = value; break;
    case 1: row->oc_merge = value; break;
    case 2: row->oc_uses_known = value; break;
    case 3: row->oc_encountered = value; break;
    case 4: row->oc_magic = value; break;
    case 5: row->oc_charged = value; break;
    case 6: row->oc_unique = value; break;
    case 7: row->oc_nowish = value; break;
    case 8: row->oc_big = value; break;
    case 9: row->oc_tough = value; break;
    case 10: row->oc_spare1 = value; break;
    case 11: row->oc_dir = value; break;
    default: row->oc_material = value; break;
    }
}
#ifdef TELEPORT_OBJECTS_LITERAL_CAPACITY
static char teleport_objects_literals[TELEPORT_OBJECTS_LITERAL_CAPACITY];
void *teleport_objects_literal_storage(void) { return teleport_objects_literals; }
size_t teleport_objects_literal_capacity(void) { return sizeof teleport_objects_literals; }
#endif

/* Monster catalogue ABI only. All initializer data is supplied by JS. */
extern const struct attack c_sa_yes[NATTK], c_sa_no[NATTK];
#ifndef TELEPORT_REFERENCE_MONST
struct permonst mons[NUMMONS + 1];
const struct attack c_sa_yes[NATTK] = { { 0 } };
const struct attack c_sa_no[NATTK] = { { 0 } };
#endif
static struct permonst teleport_monst_init[NUMMONS + 1];
const void *teleport_monst_storage(int index)
{
    switch (index) {
    case 0: return mons;
    case 1: return teleport_monst_init;
    case 2: return c_sa_yes;
    default: return c_sa_no;
    }
}
#ifdef TELEPORT_MONST_LITERAL_CAPACITY
static char teleport_monst_literals[TELEPORT_MONST_LITERAL_CAPACITY];
void *teleport_monst_literal_storage(void) { return teleport_monst_literals; }
size_t teleport_monst_literal_capacity(void) { return sizeof teleport_monst_literals; }
#endif

/* Shop-name ABI only. Tables, naming, allocation and stocking logic are JS. */
extern const struct shclass shtypes[];
#ifdef TELEPORT_SHKNAM_ROW_COUNT
#ifndef TELEPORT_REFERENCE_SHKNAM
const struct shclass shtypes[TELEPORT_SHKNAM_ROW_COUNT] = { { 0 } };
#endif
static const char *teleport_shknam_names[TELEPORT_SHKNAM_NAME_POINTER_COUNT];
const void *teleport_shknam_storage(int index)
{
    return index == 0 ? (const void *) shtypes : (const void *) teleport_shknam_names;
}
#endif
const void *teleport_shknam_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &svb;
    case 2: return &svc;
    case 3: return &svl;
    case 4: return &svd;
    case 5: return &svr;
    case 6: return mons;
    case 7: return objects;
    case 8: return obj_descr;
    case 9: return &program_state;
    case 10: return &gd;
    default: return &flags;
    }
}
time_t teleport_shknam_birthday(void) { return ubirthday; }
int teleport_shknam_object_class_bit(const struct objclass *obj, int index)
{
    (void) index;
    return obj->oc_material;
}
int teleport_shknam_monster_bit(const struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->female;
    case 1: return mon->isshk;
    case 2: return mon->mpeaceful;
    default: return mon->msleeping;
    }
}
void teleport_shknam_set_monster_bit(struct monst *mon, int index, unsigned value)
{
    switch (index) {
    case 0: mon->female = value; break;
    case 1: mon->isshk = value; break;
    case 2: mon->mpeaceful = value; break;
    default: mon->msleeping = value; break;
    }
}
int teleport_shknam_terrain_bit(coordxy x, coordxy y, int index)
{
    switch (index) {
    case 0: return levl[x][y].edge;
    case 1: return levl[x][y].roomno;
    default: return levl[x][y].doormask;
    }
}
void teleport_shknam_set_terrain_bit(coordxy x, coordxy y, int index, unsigned value)
{
    switch (index) {
    case 0: levl[x][y].edge = value; break;
    case 1: levl[x][y].roomno = value; break;
    default: levl[x][y].doormask = value; break;
    }
}
int teleport_shknam_level_bit(int index) { (void) index; return svl.level.flags.has_shop; }
void teleport_shknam_set_level_bit(int index, unsigned value)
{
    (void) index;
    svl.level.flags.has_shop = value;
}
int teleport_shknam_special_town(const s_level *level) { return level->flags.town; }
int teleport_shknam_context_bit(int index) { (void) index; return svc.context.tribute.bookstock; }
void teleport_shknam_set_context_bit(int index, unsigned value)
{
    (void) index;
    svc.context.tribute.bookstock = value;
}
void teleport_shknam_free(void *ptr) { free(ptr); }
static const char *const teleport_shknam_callers[] = {
    "shkveg", "mkshobj_at", "nameshk", "shkinit", "stock_room", "get_shop_item", "shkname"
};
int teleport_shknam_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("shknam.c", line, teleport_shknam_callers[caller]);
    return (rn2)(bound);
}
int teleport_shknam_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("shknam.c", line, teleport_shknam_callers[caller]);
    return (rnd)(bound);
}
#ifdef TELEPORT_SHKNAM_ASSERT_LINE_0
void teleport_shknam_assert(int index)
{
    if (index == 0)
        __assert_fail(TELEPORT_SHKNAM_ASSERT_CONDITION_0, "shknam.c", TELEPORT_SHKNAM_ASSERT_LINE_0, "nameshk");
    else
        __assert_fail(TELEPORT_SHKNAM_ASSERT_CONDITION_1, "shknam.c", TELEPORT_SHKNAM_ASSERT_LINE_1, "nameshk");
}
#endif
void teleport_shknam_panic(const char *format, const char *name, int a, int b)
{
    panic(format, name, a, b);
}
void teleport_shknam_panic_ints(const char *format, int a, int b) { panic(format, a, b); }
void teleport_shknam_impossible(const char *format, const char *name) { impossible(format, name); }
void teleport_shknam_pline(const char *format, int a, int b, int c, int d) { pline(format, a, b, c, d); }
void teleport_shknam_format(char *out, const char *format) { Sprintf(out, format); }
void teleport_shknam_display_window(winid win, boolean blocking) { display_nhwindow(win, blocking); }
winid teleport_shknam_win_message(void) { return WIN_MESSAGE; }
#ifdef TELEPORT_SHKNAM_LITERAL_CAPACITY
static char teleport_shknam_literals[TELEPORT_SHKNAM_LITERAL_CAPACITY];
void *teleport_shknam_literal_storage(void) { return teleport_shknam_literals; }
size_t teleport_shknam_literal_capacity(void) { return sizeof teleport_shknam_literals; }
#endif

/* Rumors ABI only: real stdio, native dependencies and typed calls. */
const void *teleport_rumors_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gi;
    case 2: return &gt;
    case 3: return &gf;
    case 4: return &svo;
    case 5: return &go;
    case 6: return &gm;
    case 7: return &disp;
    case 8: return &program_state;
    case 9: return &iflags;
    case 10: return mons;
    default: return &flags;
    }
}
int teleport_rumors_hero_bit(int index) { return index == 0 ? u.uevent.major_oracle : u.uevent.minor_oracle; }
void teleport_rumors_set_hero_bit(int index, unsigned value)
{
    if (index == 0) u.uevent.major_oracle = value;
    else u.uevent.minor_oracle = value;
}
int teleport_rumors_monster_bit(const struct monst *mon, int index) { (void) index; return mon->mpeaceful; }
extern const char bogon_codes[];
const char *teleport_rumors_bogon_codes(void) { return bogon_codes; }
FILE *teleport_rumors_open(const char *name, const char *mode) { return fopen(name, mode); }
int teleport_rumors_close(FILE *fp) { return fclose(fp); }
int teleport_rumors_seek(FILE *fp, long offset, int whence) { return fseek(fp, offset, whence); }
long teleport_rumors_tell(FILE *fp) { return ftell(fp); }
char *teleport_rumors_gets(char *buf, int size, FILE *fp) { return fgets(buf, size, fp); }
void teleport_rumors_free(void *ptr) { free(ptr); }
uintptr_t teleport_rumors_rng_pointer(void) { return (uintptr_t) (rn2); }
int teleport_rumors_call_rng(uintptr_t rng, int bound) { return ((int (*)(int)) rng)(bound); }
static const char *const teleport_rumors_callers[] = { "getrumor", "outrumor", "outoracle" };
int teleport_rumors_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("rumors.c", line, teleport_rumors_callers[caller]);
    return (rn2)(bound);
}
int teleport_rumors_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("rumors.c", line, teleport_rumors_callers[caller]);
    return (rnd)(bound);
}
#ifdef TELEPORT_RUMORS_ASSERT_LINE
void teleport_rumors_assert(void)
{
    __assert_fail(TELEPORT_RUMORS_ASSERT_CONDITION, "rumors.c", TELEPORT_RUMORS_ASSERT_LINE, "CapitalMon");
}
void teleport_rumors_nhassert(void)
{
    nhassert_failed(TELEPORT_RUMORS_NHASSERT_CONDITION, "rumors.c", TELEPORT_RUMORS_NHASSERT_LINE);
}
#endif
int teleport_rumors_scan_header(const char *line, const char *format, int *a, long *b,
                                unsigned long *c, int *d, long *e, unsigned long *f,
                                unsigned long *g)
{
    return sscanf(line, format, a, b, c, d, e, f, g);
}
int teleport_rumors_scan_int(const char *line, const char *format, int *out) { return sscanf(line, format, out); }
int teleport_rumors_scan_ulong(const char *line, const char *format, unsigned long *out) { return sscanf(line, format, out); }
void teleport_rumors_format_longs(char *out, const char *fmt, long a, unsigned long b,
                                 long c, unsigned long d, long e, unsigned long f)
{ Sprintf(out, fmt, a, b, c, d, e, f); }
void teleport_rumors_format_long_string(char *out, const char *fmt, long value, const char *name) { Sprintf(out, fmt, value, name); }
void teleport_rumors_format_int_string(char *out, const char *fmt, int value, const char *name) { Sprintf(out, fmt, value, name); }
void teleport_rumors_format_strings(char *out, const char *fmt, const char *a, const char *b) { Sprintf(out, fmt, a, b); }
void teleport_rumors_message(int kind, const char *fmt, const char *a, const char *b)
{
    switch (kind) {
    case 0: pline(fmt, a, b); break;
    case 1: You(fmt, a, b); break;
    case 2: There(fmt, a, b); break;
    case 3: verbalize(fmt, a, b); break;
    default: impossible(fmt, a, b); break;
    }
}
winid teleport_rumors_create_window(int type) { return create_nhwindow(type); }
void teleport_rumors_display_window(winid win, boolean blocking) { display_nhwindow(win, blocking); }
void teleport_rumors_destroy_window(winid win) { destroy_nhwindow(win); }
void teleport_rumors_putstr(winid win, int attr, const char *text) { putstr(win, attr, text); }
winid teleport_rumors_win_message(void) { return WIN_MESSAGE; }
char teleport_rumors_ynq(const char *query) { return ynq(query); }
char teleport_rumors_y_n(const char *query) { return y_n(query); }
boolean teleport_rumors_explicitdebug(const char *name) { return explicitdebug(name); }
void teleport_rumors_sfo_unsigned(NHFILE *fp, unsigned *value, const char *tag) { Sfo_unsigned(fp, value, tag); }
void teleport_rumors_sfo_ulong(NHFILE *fp, unsigned long *value, const char *tag) { Sfo_ulong(fp, value, tag); }
void teleport_rumors_sfi_unsigned(NHFILE *fp, unsigned *value, const char *tag) { Sfi_unsigned(fp, value, tag); }
void teleport_rumors_sfi_ulong(NHFILE *fp, unsigned long *value, const char *tag) { Sfi_ulong(fp, value, tag); }
#ifdef TELEPORT_RUMORS_LITERAL_CAPACITY
static char teleport_rumors_literals[TELEPORT_RUMORS_LITERAL_CAPACITY
    + sizeof RUMORFILE + sizeof ENGRAVEFILE + sizeof EPITAPHFILE
    + sizeof BOGUSMONFILE + sizeof ORACLEFILE + sizeof "%s"];
void *teleport_rumors_literal_storage(void) { return teleport_rumors_literals; }
size_t teleport_rumors_literal_capacity(void) { return sizeof teleport_rumors_literals; }
#endif

/* Music ABI only: storage, packed fields and native dependency calls. */
static char teleport_music_song[2];
void *teleport_music_storage(int index) { (void) index; return teleport_music_song; }
const void *teleport_music_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &svl;
    case 3: return &svc;
    case 4: return &svt;
    case 5: return &gc;
    case 6: return &disp;
    case 7: return &svd;
    case 8: return &gu;
    case 9: return &gv;
    case 10: return &flags;
    case 11: return genders;
    case 12: return objects;
    default: return mons;
    }
}
int teleport_music_hero_bit(int index)
{
    switch (index) {
    case 0: return u.uswallow;
    case 1: return u.uinwater;
    case 2: return u.uroleplay.deaf;
    default: return u.uevent.uheard_tune;
    }
}
void teleport_music_set_hero_bit(int index, unsigned value)
{
    switch (index) {
    case 0: u.uswallow = value; break;
    case 1: u.uinwater = value; break;
    case 2: u.uroleplay.deaf = value; break;
    default: u.uevent.uheard_tune = value; break;
    }
}
int teleport_music_monster_bit(const struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->msleeping;
    case 1: return mon->mcanmove;
    case 2: return mon->mfrozen;
    case 3: return mon->mpeaceful;
    case 4: return mon->mavenge;
    case 5: return mon->mundetected;
    case 6: return mon->mtrapped;
    default: return mon->isshk;
    }
}
void teleport_music_set_monster_bit(struct monst *mon, int index, unsigned value)
{
    switch (index) {
    case 0: mon->msleeping = value; break;
    case 1: mon->mcanmove = value; break;
    case 2: mon->mfrozen = value; break;
    case 3: mon->mpeaceful = value; break;
    case 4: mon->mavenge = value; break;
    case 5: mon->mundetected = value; break;
    case 6: mon->mtrapped = value; break;
    default: mon->isshk = value; break;
    }
}
int teleport_music_object_class_bit(const struct objclass *obj, int index) { (void) index; return obj->oc_magic; }
int teleport_music_terrain_bit(coordxy x, coordxy y, int index) { (void) index; return levl[x][y].doormask; }
void teleport_music_set_terrain_bit(coordxy x, coordxy y, int index, unsigned value)
{ (void) index; levl[x][y].doormask = value; }
int teleport_music_trap_bit(const struct trap *trap, int index) { return index == 0 ? trap->tseen : trap->ttyp; }
void teleport_music_set_trap_bit(struct trap *trap, int index, unsigned value) { (void) index; trap->tseen = value; }
const char *teleport_music_givenname(const struct monst *mon) { return mon->mextra ? MGIVENNAME(mon) : NULL; }
const char *teleport_music_never_mind(void) { return Never_mind; }
static const char *const teleport_music_callers[] = {
    "put_monsters_to_sleep", "do_pit", "do_earthquake", "do_improvisation", "improvised_notes"
};
int teleport_music_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("music.c", line, teleport_music_callers[caller]);
    return (rn2)(bound);
}
int teleport_music_rnd(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("music.c", line, teleport_music_callers[caller]);
    return (rnd)(bound);
}
int teleport_music_rnl(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("music.c", line, teleport_music_callers[caller]);
    return (rnl)(bound);
}
int teleport_music_d(int n, int x, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("music.c", line, teleport_music_callers[caller]);
    return (d)(n, x);
}
void teleport_music_message(int kind, const char *format, const char *a, const char *b, const char *c)
{
    switch (kind) {
    case 0: pline(format, a, b, c); break;
    case 1: You(format, a, b, c); break;
    case 2: Your(format, a, b, c); break;
    case 3: You_hear(format, a, b, c); break;
    case 4: You_feel(format, a, b, c); break;
    case 5: You_cant(format, a, b, c); break;
    case 6: pline_The(format, a, b, c); break;
    default: Norep(format, a, b, c); break;
    }
}
void teleport_music_hear_numbers(const char *format, int a, const char *b, int c, const char *d)
{ You_hear(format, a, b, c, d); }
void teleport_music_impossible(const char *format, int value) { impossible(format, value); }
void teleport_music_format(char *out, const char *format, const char *value) { Sprintf(out, format, value); }
void teleport_music_getlin(const char *query, char *out) { getlin(query, out); }
char teleport_music_ynq(const char *query) { return ynq(query); }
#ifdef TELEPORT_MUSIC_LITERAL_CAPACITY
static char teleport_music_literals[TELEPORT_MUSIC_LITERAL_CAPACITY + sizeof "%s" + sizeof "s"];
void *teleport_music_literal_storage(void) { return teleport_music_literals; }
size_t teleport_music_literal_capacity(void) { return sizeof teleport_music_literals; }
#endif

/* Version ABI only: zero storage, native dependencies and typed varargs. */
struct critical_sizes_with_names { uchar ucsize; const char *nm; };
#ifdef TELEPORT_VERSION_CRITICAL_COUNT
#ifndef TELEPORT_REFERENCE_VERSION
struct critical_sizes_with_names critical_sizes[TELEPORT_VERSION_CRITICAL_COUNT];
uchar cscbuf[TELEPORT_VERSION_CRITICAL_COUNT];
#else
extern struct critical_sizes_with_names critical_sizes[];
extern uchar cscbuf[];
#endif
struct teleport_version_rt_opt { const char *token, *value; };
static struct teleport_version_rt_opt teleport_version_rt_opts[TELEPORT_VERSION_RTOPTS_COUNT];
void *teleport_version_storage(int index)
{
    switch (index) {
    case 0: return critical_sizes;
    case 1: return cscbuf;
    default: return teleport_version_rt_opts;
    }
}
#endif
const void *teleport_version_global(int index)
{
    switch (index) {
    case 0: return &nomakedefs;
    case 1: return &flags;
    case 2: return &iflags;
    case 3: return &gh;
    case 4: return &gl;
    default: return &gc;
    }
}
extern const char regex_id[];
const char *teleport_version_regex_id(void) { return regex_id; }
winid teleport_version_win_message(void) { return WIN_MESSAGE; }
winid teleport_version_create_window(int type) { return create_nhwindow(type); }
void teleport_version_putstr(winid win, int attr, const char *text) { putstr(win, attr, text); }
void teleport_version_display_window(winid win, boolean blocking) { display_nhwindow(win, blocking); }
void teleport_version_destroy_window(winid win) { destroy_nhwindow(win); }
void teleport_version_wait_synch(void) { wait_synch(); }
void teleport_version_raw_print(const char *text) { raw_print(text); }
void teleport_version_pline(const char *fmt, const char *value) { pline(fmt, value); }
void teleport_version_format(char *out, const char *fmt, const char *value) { Sprintf(out, fmt, value); }
void teleport_version_raw_string(const char *fmt, const char *value) { raw_printf(fmt, value); }
void teleport_version_raw_int_string(const char *fmt, int value, const char *name) { raw_printf(fmt, value, name); }
void teleport_version_raw_counts(const char *fmt, int value, int count) { raw_printf(fmt, value, count); }
const char *teleport_version_datamodel(int format) { return datamodel(format); }
void teleport_version_pastebuf(char *buf) { port_insert_pastebuf(buf); }
#ifdef TELEPORT_VERSION_SNPRINTF_LINES
static const int teleport_version_snprintf_lines[] = TELEPORT_VERSION_SNPRINTF_LINES;
static const char *const teleport_version_snprintf_functions[] = TELEPORT_VERSION_SNPRINTF_FUNCTIONS;
void teleport_version_snprintf_strings(int site, char *out, size_t size, const char *fmt, const char *a, const char *b)
{
    nh_snprintf(teleport_version_snprintf_functions[site], teleport_version_snprintf_lines[site], out, size, fmt, a, b);
}
void teleport_version_snprintf_longs(int site, char *out, size_t size, const char *fmt, const char *name,
                                    unsigned long a, unsigned long b, unsigned long c)
{
    nh_snprintf(teleport_version_snprintf_functions[site], teleport_version_snprintf_lines[site], out, size, fmt, name, a, b, c);
}
#endif
void teleport_version_sfo_char(NHFILE *fp, char *value, const char *tag, int count) { Sfo_char(fp, value, tag, count); }
void teleport_version_sfi_char(NHFILE *fp, char *value, const char *tag, int count) { Sfi_char(fp, value, tag, count); }
void teleport_version_sfo_uchar(NHFILE *fp, uchar *value, const char *tag) { Sfo_uchar(fp, value, tag); }
void teleport_version_sfi_uchar(NHFILE *fp, uchar *value, const char *tag) { Sfi_uchar(fp, value, tag); }
void teleport_version_sfo_info(NHFILE *fp, struct version_info *value, const char *tag) { Sfo_version_info(fp, value, tag); }
void teleport_version_sfi_info(NHFILE *fp, struct version_info *value, const char *tag) { Sfi_version_info(fp, value, tag); }
#ifdef TELEPORT_VERSION_LITERAL_CAPACITY
static char teleport_version_literals[TELEPORT_VERSION_LITERAL_CAPACITY
    + sizeof COPYRIGHT_BANNER_A + sizeof COPYRIGHT_BANNER_B + sizeof COPYRIGHT_BANNER_D
    + sizeof OPTIONS_USED];
void *teleport_version_literal_storage(void) { return teleport_version_literals; }
size_t teleport_version_literal_capacity(void) { return sizeof teleport_version_literals; }
#endif

/* Color/attribute ABI only: zero storage and typed native dependencies. */
#ifdef TELEPORT_COLORATT_TABLE_COUNT
#ifndef TELEPORT_REFERENCE_COLORATT
const struct nethack_color colortable[TELEPORT_COLORATT_TABLE_COUNT] = { { 0 } };
#endif
struct teleport_coloratt_named { const char *name; int value; };
struct teleport_coloratt_rgb256 { int index; uint32 value; };
static struct teleport_coloratt_named teleport_coloratt_names[TELEPORT_COLORATT_COLORNAME_COUNT];
static struct teleport_coloratt_named teleport_coloratt_attrs[TELEPORT_COLORATT_ATTRNAME_COUNT];
static struct teleport_coloratt_rgb256 teleport_coloratt_palette[TELEPORT_COLORATT_PALETTE_COUNT];
static char teleport_coloratt_buf[BUFSZ], teleport_coloratt_hex[sizeof "#rrggbb"];
const void *teleport_coloratt_storage(int index)
{
    switch (index) {
    case 0: return colortable;
    case 1: return teleport_coloratt_names;
    case 2: return teleport_coloratt_attrs;
    case 3: return teleport_coloratt_palette;
    case 4: return teleport_coloratt_buf;
    default: return teleport_coloratt_hex;
    }
}
#endif
const void *teleport_coloratt_global(int index)
{
    switch (index) {
    case 0: return &cg;
    case 1: return &gm;
    case 2: return &gc;
    case 3: return &gs;
    default: return &iflags;
    }
}
const char *teleport_coloratt_regex_id(void) { return regex_id; }
const char *teleport_coloratt_hexdd(void) { return hexdd; }
const glyph_info *teleport_coloratt_nul_glyphinfo(void) { return &nul_glyphinfo; }
void teleport_coloratt_free(void *ptr) { free(ptr); }
int teleport_coloratt_isspace(int c) { return isspace(c); }
winid teleport_coloratt_create_window(int type) { return create_nhwindow(type); }
void teleport_coloratt_start_menu(winid win, unsigned long behavior) { start_menu(win, behavior); }
void teleport_coloratt_end_menu(winid win, const char *prompt) { end_menu(win, prompt); }
void teleport_coloratt_destroy_window(winid win) { destroy_nhwindow(win); }
void teleport_coloratt_format(char *out, const char *format, const char *a, const char *b) { Sprintf(out, format, a, b); }
void teleport_coloratt_config_error(const char *format, const char *a, const char *b) { config_error_add(format, a, b); }
int teleport_coloratt_scan(const char *text, const char *format, unsigned *r, unsigned *g, unsigned *b, char *extra)
{ return sscanf(text, format, r, g, b, extra); }
#ifdef TELEPORT_COLORATT_SNPRINTF_LINES
static const int teleport_coloratt_snprintf_lines[] = TELEPORT_COLORATT_SNPRINTF_LINES;
static const char *const teleport_coloratt_snprintf_functions[] = TELEPORT_COLORATT_SNPRINTF_FUNCTIONS;
void teleport_coloratt_snprintf_rgb(int site, char *out, size_t size, const char *format, unsigned r, unsigned g, unsigned b)
{ nh_snprintf(teleport_coloratt_snprintf_functions[site], teleport_coloratt_snprintf_lines[site], out, size, format, r, g, b); }
void teleport_coloratt_snprintf_string(int site, char *out, size_t size, const char *format, const char *value)
{ nh_snprintf(teleport_coloratt_snprintf_functions[site], teleport_coloratt_snprintf_lines[site], out, size, format, value); }
#endif
#ifdef TELEPORT_COLORATT_ASSERT_LINE
void teleport_coloratt_assert(void)
{ __assert_fail(TELEPORT_COLORATT_ASSERT_CONDITION, "coloratt.c", TELEPORT_COLORATT_ASSERT_LINE, "wc_color_name"); }
#endif
#ifdef TELEPORT_COLORATT_LITERAL_CAPACITY
static char teleport_coloratt_literals[TELEPORT_COLORATT_LITERAL_CAPACITY];
void *teleport_coloratt_literal_storage(void) { return teleport_coloratt_literals; }
size_t teleport_coloratt_literal_capacity(void) { return sizeof teleport_coloratt_literals; }
#endif

/* Priest ABI only: packed fields and native dependencies, never decisions. */
const void *teleport_priest_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &svl;
    case 2: return &svr;
    case 3: return &svm;
    case 4: return &svd;
    case 5: return &gi;
    case 6: return &flags;
    case 7: return &program_state;
    case 8: return &gm;
    case 9: return &gn;
    case 10: return &gc;
    case 11: return &gb;
    case 12: return &gt;
    case 13: return mons;
    case 14: return genders;
    case 15: return &gv;
    case 16: return xdir;
    default: return ydir;
    }
}
int teleport_priest_monster_bit(const struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->isshk;
    case 1: return mon->ispriest;
    case 2: return mon->isminion;
    case 3: return mon->mconf;
    case 4: return mon->mpeaceful;
    case 5: return mon->msleeping;
    case 6: return mon->mcanmove;
    case 7: return mon->mfrozen;
    case 8: return mon->mcansee;
    case 9: return mon->mflee;
    case 10: return mon->female;
    default: return mon->minvis;
    }
}
void teleport_priest_set_monster_bit(struct monst *mon, int index, unsigned value)
{
    switch (index) {
    case 0: mon->isshk = value; break;
    case 1: mon->ispriest = value; break;
    case 2: mon->isminion = value; break;
    case 3: mon->mconf = value; break;
    case 4: mon->mpeaceful = value; break;
    case 5: mon->msleeping = value; break;
    case 6: mon->mcanmove = value; break;
    case 7: mon->mfrozen = value; break;
    case 8: mon->mcansee = value; break;
    case 9: mon->mflee = value; break;
    case 10: mon->female = value; break;
    default: mon->minvis = value; break;
    }
}
int teleport_priest_roleplay_deaf(void) { return u.uroleplay.deaf; }
int teleport_priest_underwater(void) { return u.uinwater; }
int teleport_priest_terrain_bit(coordxy x, coordxy y, int index) { (void) index; return levl[x][y].altarmask; }
void teleport_priest_free(void *ptr) { free(ptr); }
static const char *const teleport_priest_callers[] = {
    "move_special", "pri_move", "priestini", "intemple", "priest_talk", "ghod_hitsu"
};
int teleport_priest_rn2(int bound, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("priest.c", line, teleport_priest_callers[caller]);
    return (rn2)(bound);
}
int teleport_priest_d(int n, int x, int line, int caller)
{
    if (rng_log_enabled()) rng_log_set_caller("priest.c", line, teleport_priest_callers[caller]);
    return (d)(n, x);
}
#ifdef TELEPORT_PRIEST_ASSERT_LINE
void teleport_priest_assert(void)
{ __assert_fail(TELEPORT_PRIEST_ASSERT_CONDITION, "priest.c", TELEPORT_PRIEST_ASSERT_LINE, "angry_priest"); }
#endif
void teleport_priest_format_string(char *out, const char *fmt, const char *value) { Sprintf(out, fmt, value); }
void teleport_priest_format_money(char *out, const char *fmt, long a, long b) { Sprintf(out, fmt, a, b); }
void teleport_priest_message(int kind, const char *fmt, const char *a, const char *b, const char *c)
{
    switch (kind) {
    case 0: pline(fmt, a, b, c); break;
    case 1: You(fmt, a, b, c); break;
    case 2: Your(fmt, a, b, c); break;
    case 3: You_feel(fmt, a, b, c); break;
    case 4: verbalize(fmt, a, b, c); break;
    default: impossible(fmt, a, b, c); break;
    }
}
void teleport_priest_message_money(const char *fmt, const char *name, long money) { pline(fmt, name, money); }
void teleport_priest_message_char(const char *fmt, const char *text, int ch) { pline(fmt, text, ch); }
void teleport_priest_livelog(long category, const char *fmt, const char *value) { livelog_printf(category, fmt, value); }
#ifdef TELEPORT_PRIEST_LITERAL_CAPACITY
static char teleport_priest_literals[TELEPORT_PRIEST_LITERAL_CAPACITY + sizeof "%s"];
void *teleport_priest_literal_storage(void) { return teleport_priest_literals; }
size_t teleport_priest_literal_capacity(void) { return sizeof teleport_priest_literals; }
#endif

/* Light ABI only: live packed fields, serialization and native calls. */
extern const coordxy circle_data[], circle_start[];
const void *teleport_light_global(int index)
{
    switch (index) {
    case 0: return &gl;
    case 1: return &gv;
    case 2: return &u;
    case 3: return &cg;
    case 4: return &gy;
    case 5: return &svl;
    case 6: return &gm;
    case 7: return &gb;
    case 8: return &gi;
    case 9: return circle_data;
    default: return circle_start;
    }
}
struct obj *teleport_light_uskin(void) { return uskin; }
int teleport_light_object_bit(const struct obj *obj, int index)
{ return index == 0 ? obj->lamplit : index == 1 ? obj->blessed : obj->cursed; }
void teleport_light_set_object_bit(struct obj *obj, int index, unsigned value)
{
    switch (index) {
    case 0: obj->lamplit = value; break;
    case 1: obj->blessed = value; break;
    default: obj->cursed = value; break;
    }
}
int teleport_light_monster_bit(const struct monst *mon, int index)
{ return index == 0 ? mon->isgd : mon->mtemplit; }
void teleport_light_set_monster_bit(struct monst *mon, int index, unsigned value)
{ if (index == 0) mon->isgd = value; else mon->mtemplit = value; }
int teleport_light_terrain_bit(coordxy x, coordxy y, int index)
{ (void) index; return levl[x][y].lit; }
void teleport_light_free(void *ptr) { free(ptr); }
void teleport_light_delay(void) { nh_delay_output(); }
winid teleport_light_create_window(int type) { return create_nhwindow(type); }
void teleport_light_putstr(winid win, int attr, const char *text) { putstr(win, attr, text); }
void teleport_light_display_window(winid win, boolean blocking) { display_nhwindow(win, blocking); }
void teleport_light_destroy_window(winid win) { destroy_nhwindow(win); }
void teleport_light_sfo_int(NHFILE *fp, int *value, const char *tag) { Sfo_int(fp, value, tag); }
void teleport_light_sfi_int(NHFILE *fp, int *value, const char *tag) { Sfi_int(fp, value, tag); }
void teleport_light_sfo_ls(NHFILE *fp, light_source *value, const char *tag) { Sfo_ls_t(fp, value, tag); }
void teleport_light_sfi_ls(NHFILE *fp, light_source *value, const char *tag) { Sfi_ls_t(fp, value, tag); }
#ifdef TELEPORT_LIGHT_ASSERT_LINES
static const int teleport_light_assert_lines[] = TELEPORT_LIGHT_ASSERT_LINES;
static const char *const teleport_light_assert_conditions[] = TELEPORT_LIGHT_ASSERT_CONDITIONS;
static const char *const teleport_light_assert_functions[] = TELEPORT_LIGHT_ASSERT_FUNCTIONS;
void teleport_light_assert(int index)
{ __assert_fail(teleport_light_assert_conditions[index], "light.c", teleport_light_assert_lines[index], teleport_light_assert_functions[index]); }
#endif
void teleport_light_panic_ints(const char *fmt, int a, int b, int c) { panic(fmt, a, b, c); }
void teleport_light_panic_uint(const char *fmt, unsigned value) { panic(fmt, value); }
void teleport_light_panic_char_uint(const char *fmt, int ch, unsigned value) { panic(fmt, ch, value); }
void teleport_light_impossible_ints(const char *fmt, int a, int b) { impossible(fmt, a, b); }
void teleport_light_impossible_int_string(const char *fmt, int value, const char *text) { impossible(fmt, value, text); }
void teleport_light_impossible_strings(const char *fmt, const char *a, const char *b, const char *c, const char *d) { impossible(fmt, a, b, c, d); }
void teleport_light_impossible_uint(const char *fmt, unsigned value) { impossible(fmt, value); }
void teleport_light_impossible_string_uint(const char *fmt, const char *text, unsigned value) { impossible(fmt, text, value); }
void teleport_light_format_long(char *out, const char *fmt, long size) { Sprintf(out, fmt, size); }
void teleport_light_format_xy(char *out, const char *fmt, int x, int y) { Sprintf(out, fmt, x, y); }
void teleport_light_format_source(char *out, const char *fmt, int x, int y, int range, int flags, const char *type, const char *id)
{ Sprintf(out, fmt, x, y, range, flags, type, id); }
#ifdef TELEPORT_LIGHT_LITERAL_CAPACITY
static char teleport_light_literals[TELEPORT_LIGHT_LITERAL_CAPACITY];
void *teleport_light_literal_storage(void) { return teleport_light_literals; }
size_t teleport_light_literal_capacity(void) { return sizeof teleport_light_literals; }
#endif

/* LOCK: typed native ABI only; original lock algorithms live in JS. */
const void *teleport_lock_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gx;
    case 2: return &go;
    case 3: return &gi;
    case 4: return &gy;
    case 5: return &svl;
    case 6: return &svm;
    case 7: return &flags;
    case 8: return &gv;
    case 9: return &cg;
    case 10: return objects;
    case 11: return mons;
    case 12: return &gu;
    case 13: return &svc;
    case 14: return &gm;
    case 15: return &svd;
    default: return 0;
    }
}
struct obj *teleport_lock_equipment(void) { return uwep; }
int teleport_lock_roleplay_deaf(void) { return u.uroleplay.deaf; }
int teleport_lock_hero_bit(int index) { return index == 0 ? u.uswallow : u.uinwater; }
int teleport_lock_object_bit(const struct obj *obj, int index)
{
    switch (index) {
    case 0: return obj->cursed;
    case 1: return obj->olocked;
    case 2: return obj->obroken;
    case 3: return obj->lknown;
    case 4: return obj->otrapped;
    case 5: return obj->tknown;
    case 6: return obj->dknown;
    case 7: return obj->oeroded;
    case 8: return obj->oeroded2;
    default: return 0;
    }
}
void teleport_lock_set_object_bit(struct obj *obj, int index, unsigned value)
{
    switch (index) {
    case 0: obj->cursed = value; break;
    case 1: obj->olocked = value; break;
    case 2: obj->obroken = value; break;
    case 3: obj->lknown = value; break;
    case 4: obj->otrapped = value; break;
    case 5: obj->tknown = value; break;
    case 6: obj->dknown = value; break;
    case 7: obj->oeroded = value; break;
    case 8: obj->oeroded2 = value; break;
    }
}
int teleport_lock_monster_bit(const struct monst *mon, int index) { return index == 0 ? mon->mpeaceful : mon->isshk; }
int teleport_lock_object_class_bit(const struct objclass *obj, int index) { (void) index; return obj->oc_material; }
int teleport_lock_terrain_bit(coordxy x, coordxy y, int index) { (void) index; return levl[x][y].doormask; }
void teleport_lock_set_terrain_bit(coordxy x, coordxy y, int index, unsigned value) { (void) index; levl[x][y].doormask = value; }
int teleport_lock_context_bit(int index) { (void) index; return svc.context.move; }
void teleport_lock_set_context_bit(int index, int value) { (void) index; svc.context.move = (boolean) value; }
extern int teleport_lock_callback_pick(void);
extern int teleport_lock_callback_force(void);
int teleport_lock_pick_callback(void) { return teleport_lock_callback_pick(); }
int teleport_lock_force_callback(void) { return teleport_lock_callback_force(); }
uintptr_t teleport_lock_callback_pointer(int index)
{ return (uintptr_t) (index == 0 ? teleport_lock_pick_callback : teleport_lock_force_callback); }
uintptr_t teleport_lock_get_occupation(void) { return (uintptr_t) go.occupation; }
void teleport_lock_set_occupation_pointer(uintptr_t value) { go.occupation = (int (*)(void)) value; }
void teleport_lock_set_occupation(uintptr_t callback, const char *action, cmdcount_nht count)
{ set_occupation((int (*)(void)) callback, action, count); }
uintptr_t teleport_lock_command_pointer(void) { return (uintptr_t) dokick; }
void teleport_lock_cmdq_add_ec(int queue, uintptr_t command) { cmdq_add_ec(queue, (int (*)(void)) command); }
char *teleport_lock_safe_qbuf(char *buf, const char *prefix, const char *suffix, struct obj *obj, int pair, const char *last)
{ return safe_qbuf(buf, prefix, suffix, obj, pair == 0 ? yname : doname, pair == 0 ? ysimple_name : ansimpleoname, last); }
const char *teleport_lock_singular(struct obj *obj) { return singular(obj, xname); }
const char *teleport_lock_common_string(int index) { (void) index; return Something; }
char teleport_lock_y_n(const char *query) { return y_n(query); }
char teleport_lock_ynq(const char *query) { return ynq(query); }
static const char *const teleport_lock_callers[] = { "picklock", "breakchestlock", "forcelock", "doopen_indir", "doclose" };
int teleport_lock_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("lock.c", line, teleport_lock_callers[caller]); return (rn2)(bound); }
int teleport_lock_rnl(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("lock.c", line, teleport_lock_callers[caller]); return (rnl)(bound); }
void teleport_lock_pline(const char *fmt, const char *a, const char *b, const char *c) { pline(fmt, a, b, c); }
void teleport_lock_You(const char *fmt, const char *a, const char *b, const char *c) { You(fmt, a, b, c); }
void teleport_lock_You_cant(const char *fmt, const char *a, const char *b, const char *c) { You_cant(fmt, a, b, c); }
void teleport_lock_You_hear(const char *fmt, const char *a, const char *b, const char *c) { You_hear(fmt, a, b, c); }
void teleport_lock_There(const char *fmt, const char *a, const char *b, const char *c) { There(fmt, a, b, c); }
void teleport_lock_pline_The(const char *fmt, const char *a, const char *b, const char *c) { pline_The(fmt, a, b, c); }
void teleport_lock_verbalize(const char *fmt, const char *a, const char *b, const char *c) { verbalize(fmt, a, b, c); }
void teleport_lock_you_money(const char *fmt, long amount, const char *unit) { You(fmt, amount, unit); }
void teleport_lock_impossible(const char *fmt, int value) { impossible(fmt, value); }
void teleport_lock_format(char *out, const char *fmt, const char *a, const char *b, const char *c) { Sprintf(out, fmt, a, b, c); }
#ifdef TELEPORT_LOCK_LITERAL_CAPACITY
static char teleport_lock_literals[TELEPORT_LOCK_LITERAL_CAPACITY + sizeof "%s"];
void *teleport_lock_literal_storage(void) { return teleport_lock_literals; }
size_t teleport_lock_literal_capacity(void) { return sizeof teleport_lock_literals; }
#endif

/* STEED: native layout and dependency ABI only; riding policy remains JS. */
const void *teleport_steed_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &svl;
    case 3: return &gu;
    case 4: return &gi;
    case 5: return &gv;
    case 6: return &disp;
    case 7: return &flags;
    case 8: return mons;
    case 9: return objects;
    case 10: return genders;
    case 11: return &iflags;
    default: return 0;
    }
}
struct obj *teleport_steed_equipment(int index)
{
    switch (index) {
    case 0: return uwep;
    case 1: return uarm;
    case 2: return uarmg;
    case 3: return uarmf;
    case 4: return uball;
    default: return 0;
    }
}
int teleport_steed_hero_bit(int index) { return index == 0 ? u.uswallow : u.uinwater; }
int teleport_steed_roleplay_deaf(void) { return u.uroleplay.deaf; }
int teleport_steed_monster_bit(const struct monst *value, int index)
{
    switch(index) {
    case 0: return value->isminion;
    case 1: return value->isshk;
    case 2: return value->ispriest;
    case 3: return value->isgd;
    case 4: return value->iswiz;
    case 5: return value->mundetected;
    case 6: return value->mtrapped;
    case 7: return value->mleashed;
    case 8: return value->mcanmove;
    case 9: return value->mfrozen;
    case 10: return value->msleeping;
    default: return 0;
    }
}
void teleport_steed_set_monster_bit(struct monst *value, int index, unsigned bits)
{
    switch(index) {
    case 0: value->isminion = bits; break;
    case 1: value->isshk = bits; break;
    case 2: value->ispriest = bits; break;
    case 3: value->isgd = bits; break;
    case 4: value->iswiz = bits; break;
    case 5: value->mundetected = bits; break;
    case 6: value->mtrapped = bits; break;
    case 7: value->mleashed = bits; break;
    case 8: value->mcanmove = bits; break;
    case 9: value->mfrozen = bits; break;
    case 10: value->msleeping = bits; break;
    }
}
int teleport_steed_object_bit(const struct obj *value, int index)
{
    switch(index) {
    case 0: return value->cursed;
    case 1: return value->greased;
    case 2: return value->bknown;
    case 3: return value->oeroded;
    case 4: return value->oeroded2;
    default: return 0;
    }
}
void teleport_steed_set_object_bit(struct obj *value, int index, unsigned bits)
{
    switch(index) {
    case 0: value->cursed = bits; break;
    case 1: value->greased = bits; break;
    case 2: value->bknown = bits; break;
    case 3: value->oeroded = bits; break;
    case 4: value->oeroded2 = bits; break;
    }
}
int teleport_steed_class_bit(const struct objclass *value, int index) { (void) index; return value->oc_material; }
int teleport_steed_trap_bit(const struct trap *value, int index) { return index == 0 ? value->ttyp : value->tseen; }
int teleport_steed_has_mgivenname(const struct monst *value) { return has_mgivenname(value) != 0; }
static char teleport_steed_classifiers[7];
void *teleport_steed_storage(void) { return teleport_steed_classifiers; }
const char *teleport_steed_common_string(int index) { (void) index; return Never_mind; }
char teleport_steed_y_n(const char *query) { return y_n(query); }
static const char *const teleport_steed_callers[] = { "use_saddle", "mount_steed", "kick_steed", "landing_spot", "dismount_steed", "maybewakesteed" };
int teleport_steed_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("steed.c", line, teleport_steed_callers[caller]); return (rn2)(bound); }
int teleport_steed_rnd(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("steed.c", line, teleport_steed_callers[caller]); return (rnd)(bound); }
void teleport_steed_pline(const char *fmt, const char *a, const char *b, const char *c) { pline(fmt, a, b, c); }
void teleport_steed_You(const char *fmt, const char *a, const char *b, const char *c) { You(fmt, a, b, c); }
void teleport_steed_You_cant(const char *fmt, const char *a, const char *b, const char *c) { You_cant(fmt, a, b, c); }
void teleport_steed_Your(const char *fmt, const char *a, const char *b, const char *c) { Your(fmt, a, b, c); }
void teleport_steed_impossible0(const char *fmt) { impossible(fmt); }
void teleport_steed_impossible_position(const char *fmt, const char *name, int x, int y, unsigned long state, const char *level)
{ impossible(fmt, name, x, y, state, level); }
void teleport_steed_impossible_state(const char *fmt, const char *name, unsigned long state, const char *level)
{ impossible(fmt, name, state, level); }
void teleport_steed_impossible_overlap(const char *fmt, const char *name, const char *other, int x, int y, unsigned long state1, unsigned long state2, const char *level)
{ impossible(fmt, name, other, x, y, state1, state2, level); }
void teleport_steed_panic(const char *fmt) { panic(fmt); }
void teleport_steed_format(char *out, const char *fmt, const char *value) { Sprintf(out, fmt, value); }
#ifdef TELEPORT_STEED_LITERAL_CAPACITY
static char teleport_steed_literals[TELEPORT_STEED_LITERAL_CAPACITY + sizeof "%s"];
void *teleport_steed_literal_storage(void) { return teleport_steed_literals; }
size_t teleport_steed_literal_capacity(void) { return sizeof teleport_steed_literals; }
#endif

/* WIZARD: typed layout/dependency ABI only; all strategy algorithms are JS. */
const void *teleport_wizard_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &svl;
    case 2: return &gm;
    case 3: return &svm;
    case 4: return &svc;
    case 5: return &gf;
    case 6: return &gs;
    case 7: return &gy;
    case 8: return &flags;
    case 9: return mons;
    case 10: return &gu;
    case 11: return &svd;
    case 12: return def_monsyms;
    case 13: return &gv;
    default: return 0;
    }
}
struct obj *teleport_wizard_equipment(int index) { return index == 0 ? uamul : uwep; }
int teleport_wizard_roleplay_deaf(void) { return u.uroleplay.deaf; }
int teleport_wizard_hero_bit(int index)
{
    switch(index) {
    case 0: return u.uhave.amulet;
    case 1: return u.uhave.bell;
    case 2: return u.uhave.menorah;
    case 3: return u.uhave.book;
    case 4: return u.uhave.questart;
    case 5: return u.uevent.invoked;
    case 6: return u.uevent.udemigod;
    case 7: return u.uswallow;
    default: return 0;
    }
}
void teleport_wizard_set_hero_bit(int index, unsigned value)
{
    switch(index) {
    case 0: u.uhave.amulet = value; break;
    case 1: u.uhave.bell = value; break;
    case 2: u.uhave.menorah = value; break;
    case 3: u.uhave.book = value; break;
    case 4: u.uhave.questart = value; break;
    case 5: u.uevent.invoked = value; break;
    case 6: u.uevent.udemigod = value; break;
    case 7: u.uswallow = value; break;
    }
}
int teleport_wizard_monster_bit(const struct monst *mon, int index)
{
    switch(index) {
    case 0: return mon->iswiz;
    case 1: return mon->isshk;
    case 2: return mon->ispriest;
    case 3: return mon->msleeping;
    case 4: return mon->mcanmove;
    case 5: return mon->mfrozen;
    case 6: return mon->mpeaceful;
    case 7: return mon->mflee;
    case 8: return mon->mavenge;
    case 9: return mon->mrevived;
    case 10: return mon->isminion;
    default: return 0;
    }
}
void teleport_wizard_set_monster_bit(struct monst *mon, int index, unsigned value)
{
    switch(index) {
    case 0: mon->iswiz = value; break;
    case 1: mon->isshk = value; break;
    case 2: mon->ispriest = value; break;
    case 3: mon->msleeping = value; break;
    case 4: mon->mcanmove = value; break;
    case 5: mon->mfrozen = value; break;
    case 6: mon->mpeaceful = value; break;
    case 7: mon->mflee = value; break;
    case 8: mon->mavenge = value; break;
    case 9: mon->mrevived = value; break;
    case 10: mon->isminion = value; break;
    }
}
int teleport_wizard_trap_type(const struct trap *trap) { return trap->ttyp; }
char *teleport_wizard_distant_name(struct obj *obj) { return distant_name(obj, doname); }
const char *teleport_wizard_common_string(int index) { (void) index; return NH_BLACK; }
static const char *const teleport_wizard_callers[] = { "amulet", "tactics", "aggravate", "clonewiz", "pick_nasty", "nasty", "resurrect", "intervene", "wizdeadorgone", "cuss" };
int teleport_wizard_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("wizard.c", line, teleport_wizard_callers[caller]); return (rn2)(bound); }
int teleport_wizard_rnd(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("wizard.c", line, teleport_wizard_callers[caller]); return (rnd)(bound); }
void teleport_wizard_pline(const char *fmt, const char *a, const char *b) { pline(fmt, a, b); }
void teleport_wizard_You(const char *fmt, const char *a, const char *b) { You(fmt, a, b); }
void teleport_wizard_You_feel(const char *fmt, const char *a, const char *b) { You_feel(fmt, a, b); }
void teleport_wizard_verbalize(const char *fmt, const char *a, const char *b) { verbalize(fmt, a, b); }
#ifdef TELEPORT_WIZARD_LITERAL_CAPACITY
static char teleport_wizard_literals[TELEPORT_WIZARD_LITERAL_CAPACITY];
void *teleport_wizard_literal_storage(void) { return teleport_wizard_literals; }
size_t teleport_wizard_literal_capacity(void) { return sizeof teleport_wizard_literals; }
#endif

/* WORM: native layout and dependency ABI only; worm policy/state remain JS. */
const void *teleport_worm_global(int index)
{
    switch (index) {
    case 0: return &svl;
    case 1: return &svm;
    case 2: return &svc;
    case 3: return &u;
    case 4: return &gv;
    case 5: return mons;
    default: return 0;
    }
}
int teleport_worm_monster_bit(const struct monst *mon, int index)
{ return index == 0 ? mon->wormno : index == 1 ? mon->mcloned : mon->female; }
void teleport_worm_set_monster_bit(struct monst *mon, int index, unsigned value)
{ if (index == 0) mon->wormno = value; else if (index == 1) mon->mcloned = value; else mon->female = value; }
void teleport_worm_free(void *value) { free(value); }
void teleport_worm_sfo_int(NHFILE *fp, int *value, const char *tag) { Sfo_int(fp, value, tag); }
void teleport_worm_sfo_coordxy(NHFILE *fp, coordxy *value, const char *tag) { Sfo_coordxy(fp, value, tag); }
void teleport_worm_sfo_long(NHFILE *fp, long *value, const char *tag) { Sfo_long(fp, value, tag); }
void teleport_worm_sfi_int(NHFILE *fp, int *value, const char *tag) { Sfi_int(fp, value, tag); }
void teleport_worm_sfi_coordxy(NHFILE *fp, coordxy *value, const char *tag) { Sfi_coordxy(fp, value, tag); }
void teleport_worm_sfi_long(NHFILE *fp, long *value, const char *tag) { Sfi_long(fp, value, tag); }
static const char *const teleport_worm_callers[] = { "worm_move", "worm_nomove", "cutworm" };
int teleport_worm_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("worm.c", line, teleport_worm_callers[caller]); return (rn2)(bound); }
int teleport_worm_rnd(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("worm.c", line, teleport_worm_callers[caller]); return (rnd)(bound); }
int teleport_worm_d(int dice, int sides, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("worm.c", line, teleport_worm_callers[caller]); return (d)(dice, sides); }
void teleport_worm_impossible_ints(const char *fmt, int a, int b, int c, int d) { impossible(fmt, a, b, c, d); }
void teleport_worm_impossible_strings(const char *fmt, const char *a, const char *b) { impossible(fmt, a, b); }
void teleport_worm_pline(const char *fmt, const char *value) { pline(fmt, value); }
void teleport_worm_you(const char *fmt, const char *value) { You(fmt, value); }
#ifdef TELEPORT_WORM_LITERAL_CAPACITY
static char teleport_worm_literals[TELEPORT_WORM_LITERAL_CAPACITY];
void *teleport_worm_literal_storage(void) { return teleport_worm_literals; }
size_t teleport_worm_literal_capacity(void) { return sizeof teleport_worm_literals; }
#endif

/* O_INIT: native layout/dependency ABI only; discovery algorithms remain JS. */
const void *teleport_o_init_global(int index)
{
    switch (index) {
    case 0: return objects;
    case 1: return obj_descr;
    case 2: return &svb;
    case 3: return &svd;
    case 4: return &go;
    case 5: return &iflags;
    case 6: return &flags;
    case 7: return &program_state;
    case 8: return &u;
    case 9: return &cg;
    case 10: return &gu;
    case 11: return &svc;
    case 12: return def_oc_syms;
    default: return 0;
    }
}
int teleport_o_init_class_bit(const struct objclass *value, int index)
{
    switch (index) {
    case 0: return value->oc_name_known;
    case 1: return value->oc_encountered;
    case 2: return value->oc_tough;
    case 3: return value->oc_material;
    case 4: return value->oc_unique;
    case 5: return value->oc_magic;
    case 6: return value->oc_uses_known;
    case 7: return value->oc_dir;
    default: return 0;
    }
}
void teleport_o_init_set_class_bit(struct objclass *value, int index, unsigned bits)
{
    switch (index) {
    case 0: value->oc_name_known = bits; break;
    case 1: value->oc_encountered = bits; break;
    case 2: value->oc_tough = bits; break;
    case 3: value->oc_material = bits; break;
    case 4: value->oc_unique = bits; break;
    case 5: value->oc_magic = bits; break;
    case 6: value->oc_uses_known = bits; break;
    case 7: value->oc_dir = bits; break;
    }
}
int teleport_o_init_object_bit(const struct obj *value, int index)
{
    switch (index) {
    case 0: return value->dknown;
    case 1: return value->known;
    default: return 0;
    }
}
void teleport_o_init_set_object_bit(struct obj *value, int index, unsigned bits)
{
    switch (index) {
    case 0: value->dknown = bits; break;
    case 1: value->known = bits; break;
    }
}
extern int teleport_o_init_compare(const void *, const void *);
int teleport_o_init_comparator(const void *a, const void *b) { return teleport_o_init_compare(a, b); }
uintptr_t teleport_o_init_comparator_pointer(void) { return (uintptr_t) teleport_o_init_comparator; }
void teleport_o_init_qsort(void *base, size_t count, size_t size)
{ qsort(base, count, size, teleport_o_init_comparator); }
void teleport_o_init_free(void *value) { free(value); }
void teleport_o_init_wait(void) { wait_synch(); }
winid teleport_o_init_create_window(int type) { return create_nhwindow(type); }
void teleport_o_init_clear_window(winid win) { clear_nhwindow(win); }
void teleport_o_init_start_menu(winid win, unsigned long flags) { start_menu(win, flags); }
void teleport_o_init_end_menu(winid win, const char *prompt) { end_menu(win, prompt); }
void teleport_o_init_display_window(winid win, boolean blocking) { display_nhwindow(win, blocking); }
void teleport_o_init_destroy_window(winid win) { destroy_nhwindow(win); }
void teleport_o_init_putstr(winid win, int attr, const char *value) { putstr(win, attr, value); }
winid teleport_o_init_win_message(void) { return WIN_MESSAGE; }
const glyph_info *teleport_o_init_nul_glyph(void) { return &nul_glyphinfo; }
char teleport_o_init_y_n(const char *query) { return y_n(query); }
void teleport_o_init_sfo_int(NHFILE *fp, int *value, const char *tag) { Sfo_int(fp, value, tag); }
void teleport_o_init_sfo_short(NHFILE *fp, short *value, const char *tag) { Sfo_short(fp, value, tag); }
void teleport_o_init_sfo_objclass(NHFILE *fp, struct objclass *value, const char *tag) { Sfo_objclass(fp, value, tag); }
void teleport_o_init_sfo_unsigned(NHFILE *fp, unsigned *value, const char *tag) { Sfo_unsigned(fp, value, tag); }
void teleport_o_init_sfo_char(NHFILE *fp, char *value, const char *tag, int count) { Sfo_char(fp, value, tag, count); }
void teleport_o_init_sfi_int(NHFILE *fp, int *value, const char *tag) { Sfi_int(fp, value, tag); }
void teleport_o_init_sfi_short(NHFILE *fp, short *value, const char *tag) { Sfi_short(fp, value, tag); }
void teleport_o_init_sfi_objclass(NHFILE *fp, struct objclass *value, const char *tag) { Sfi_objclass(fp, value, tag); }
void teleport_o_init_sfi_unsigned(NHFILE *fp, unsigned *value, const char *tag) { Sfi_unsigned(fp, value, tag); }
void teleport_o_init_sfi_char(NHFILE *fp, char *value, const char *tag, int count) { Sfi_char(fp, value, tag, count); }
static const char *const teleport_o_init_callers[] = { "randomize_gem_colors", "shuffle", "init_objects" };
int teleport_o_init_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("o_init.c", line, teleport_o_init_callers[caller]); return (rn2)(bound); }
void teleport_o_init_raw_printf(const char *fmt, int a, int b, int c) { raw_printf(fmt, a, b, c); }
void teleport_o_init_panic(const char *fmt, int a, int b) { panic(fmt, a, b); }
void teleport_o_init_impossible0(const char *fmt) { impossible(fmt); }
void teleport_o_init_impossible_string(const char *fmt, const char *value) { impossible(fmt, value); }
void teleport_o_init_impossible_name(const char *fmt, int index, const char *name, const char *known, const char *prefix) { impossible(fmt, index, name, known, prefix); }
void teleport_o_init_impossible_probability(const char *fmt, const char *sign, int sum, int oclass) { impossible(fmt, sign, sum, oclass); }
void teleport_o_init_you(const char *fmt, const char *value) { You(fmt, value); }
void teleport_o_init_pline(const char *fmt) { pline(fmt); }
void teleport_o_init_format_ints(char *out, const char *fmt, int a, int b, int c) { Sprintf(out, fmt, a, b, c); }
void teleport_o_init_format_strings(char *out, const char *fmt, const char *a, const char *b) { Sprintf(out, fmt, a, b); }
void teleport_o_init_format_string_chars(char *out, const char *fmt, const char *value, int a, int b, int c) { Sprintf(out, fmt, value, a, b, c); }
#ifdef TELEPORT_O_INIT_STRLEN_LINE
unsigned teleport_o_init_strlen(const char *value)
{ return Strlen_(value, TELEPORT_O_INIT_STRLEN_FUNCTION, TELEPORT_O_INIT_STRLEN_LINE); }
#endif
#ifdef TELEPORT_O_INIT_ASSERT_LINE
void teleport_o_init_assert(void)
{ __assert_fail(TELEPORT_O_INIT_ASSERT_CONDITION, "o_init.c", TELEPORT_O_INIT_ASSERT_LINE, TELEPORT_O_INIT_ASSERT_FUNCTION); }
#endif
#ifdef TELEPORT_O_INIT_LITERAL_CAPACITY
static char teleport_o_init_literals[TELEPORT_O_INIT_LITERAL_CAPACITY];
void *teleport_o_init_literal_storage(void) { return teleport_o_init_literals; }
size_t teleport_o_init_literal_capacity(void) { return sizeof teleport_o_init_literals; }
#endif

/* BALL: typed native layout/dependency ABI only; ball policy/state remain JS. */
const void *teleport_ball_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &svl;
    case 2: return &svd;
    case 3: return &gi;
    case 4: return &flags;
    case 5: return &gv;
    default: return 0;
    }
}
struct obj *teleport_ball_equipment(int index)
{
    switch (index) {
    case 0: return uball;
    case 1: return uchain;
    case 2: return uwep;
    case 3: return uswapwep;
    case 4: return uquiver;
    case 5: return uarmh;
    default: return 0;
    }
}
int teleport_ball_hero_bit(int index) { (void) index; return u.uswallow; }
int teleport_ball_terrain_bit(coordxy x, coordxy y, int index) { (void) index; return levl[x][y].doormask; }
int teleport_ball_trap_bit(const struct trap *trap, int index) { return index == 0 ? trap->ttyp : trap->tseen; }
void teleport_ball_set_trap_bit(struct trap *trap, int index, unsigned value)
{ if (index == 0) trap->ttyp = value; else trap->tseen = value; }
static const char *const teleport_ball_callers[] = { "ballfall", "unplacebc_and_covet_placebc", "drag_ball", "drop_ball", "litter", "drag_down" };
int teleport_ball_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("ball.c", line, teleport_ball_callers[caller]); return (rn2)(bound); }
int teleport_ball_rnd(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("ball.c", line, teleport_ball_callers[caller]); return (rnd)(bound); }
void teleport_ball_pline(const char *fmt, const char *a, const char *b, const char *c) { pline(fmt, a, b, c); }
void teleport_ball_pline_The(const char *fmt, const char *a, const char *b, const char *c) { pline_The(fmt, a, b, c); }
void teleport_ball_You(const char *fmt, const char *a, const char *b, const char *c) { You(fmt, a, b, c); }
void teleport_ball_You_feel(const char *fmt, const char *a, const char *b, const char *c) { You_feel(fmt, a, b, c); }
void teleport_ball_Your(const char *fmt, const char *a, const char *b, const char *c) { Your(fmt, a, b, c); }
void teleport_ball_impossible0(const char *fmt) { impossible(fmt); }
void teleport_ball_impossible_strings(const char *fmt, const char *a, const char *b, const char *c) { impossible(fmt, a, b, c); }
void teleport_ball_impossible_worn(const char *fmt, int type, const char *name, int where, unsigned long worn) { impossible(fmt, type, name, where, worn); }
void teleport_ball_impossible_coords(const char *fmt, int a, int b, int c, int d, int e, int f) { impossible(fmt, a, b, c, d, e, f); }
void teleport_ball_format(char *out, const char *fmt, const char *value) { Sprintf(out, fmt, value); }
#ifdef TELEPORT_BALL_LITERAL_CAPACITY
static char teleport_ball_literals[TELEPORT_BALL_LITERAL_CAPACITY];
void *teleport_ball_literal_storage(void) { return teleport_ball_literals; }
size_t teleport_ball_literal_capacity(void) { return sizeof teleport_ball_literals; }
#endif

/* MCASTU: native field/typed-call ABI; all spell data and policy remain JS. */
const void *teleport_mcastu_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &svm;
    case 3: return &svc;
    case 4: return &svk;
    case 5: return &gi;
    case 6: return &gm;
    case 7: return &gn;
    case 8: return &gb;
    case 9: return &gt;
    case 10: return &gv;
    case 11: return &mons;
    case 12: return &genders;
    case 13: return &iflags;
    default: return 0;
    }
}
int teleport_mcastu_monster_bit(const struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->mcan;
    case 1: return mon->mconf;
    case 2: return mon->iswiz;
    case 3: return mon->minvis;
    case 4: return mon->invis_blkd;
    case 5: return mon->msleeping;
    case 6: return mon->mpeaceful;
    case 7: return mon->permspeed;
    default: return 0;
    }
}
void teleport_mcastu_set_monster_bit(struct monst *mon, int index, unsigned value)
{
    switch (index) {
    case 0: mon->mcan = value; break;
    case 1: mon->mconf = value; break;
    case 2: mon->iswiz = value; break;
    case 3: mon->minvis = value; break;
    case 4: mon->invis_blkd = value; break;
    case 5: mon->msleeping = value; break;
    case 6: mon->mpeaceful = value; break;
    case 7: mon->permspeed = value; break;
    }
}
int teleport_mcastu_hero_bit(int index) { (void) index; return u.uundetected; }
int teleport_mcastu_roleplay_deaf(void) { return u.uroleplay.deaf; }
const char *teleport_mcastu_common_string(int index) { (void) index; return vision_clears; }
static const char *const teleport_mcastu_callers[] = {
    "cursetxt", "choose_monster_spell", "castmu", "m_cure_self",
    "touch_of_death", "mcast_death_touch", "mcast_weaken_you", "mcast_stun_you",
    "mcast_geyser", "mcast_fire_pillar", "mcast_lightning", "mcast_insects",
    "spell_would_be_useless", "buzzmu"
};
int teleport_mcastu_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("mcastu.c", line, teleport_mcastu_callers[caller]); return (rn2)(bound); }
int teleport_mcastu_rnd(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("mcastu.c", line, teleport_mcastu_callers[caller]); return (rnd)(bound); }
int teleport_mcastu_d(int n, int x, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("mcastu.c", line, teleport_mcastu_callers[caller]); return (d)(n, x); }
void teleport_mcastu_pline(const char *fmt, const char *a, const char *b) { pline(fmt, a, b); }
void teleport_mcastu_pline_The(const char *fmt, const char *a, const char *b) { pline_The(fmt, a, b); }
void teleport_mcastu_You(const char *fmt, const char *a, const char *b) { You(fmt, a, b); }
void teleport_mcastu_You_feel(const char *fmt, const char *a, const char *b) { You_feel(fmt, a, b); }
void teleport_mcastu_Your(const char *fmt, const char *a, const char *b) { Your(fmt, a, b); }
void teleport_mcastu_You_hear(const char *fmt, const char *a, const char *b) { You_hear(fmt, a, b); }
void teleport_mcastu_verbalize(const char *fmt, const char *a, const char *b) { verbalize(fmt, a, b); }
void teleport_mcastu_Norep(const char *fmt, const char *a, const char *b) { Norep(fmt, a, b); }
void teleport_mcastu_pline_mon(struct monst *mon, const char *fmt, const char *a, const char *b) { pline_mon(mon, fmt, a, b); }
void teleport_mcastu_debug_pline(const char *fmt, const char *name, int level, int spell) { pline(fmt, name, level, spell); }
void teleport_mcastu_impossible_ints(const char *fmt, int a, int b) { impossible(fmt, a, b); }
void teleport_mcastu_impossible_name(const char *fmt, const char *name, int adtyp) { impossible(fmt, name, adtyp); }
void teleport_mcastu_format(char *out, const char *fmt, const char *a, const char *b) { Sprintf(out, fmt, a, b); }
#ifdef TELEPORT_MCASTU_LITERAL_CAPACITY
static char teleport_mcastu_literals[TELEPORT_MCASTU_LITERAL_CAPACITY + sizeof "%s" + sizeof "s"];
void *teleport_mcastu_literal_storage(void) { return teleport_mcastu_literals; }
size_t teleport_mcastu_literal_capacity(void) { return sizeof teleport_mcastu_literals; }
#endif

/* DBRIDGE: native storage/field/typed-call ABI; drawbridge policy remains JS. */
const void *teleport_dbridge_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &go;
    case 2: return &gy;
    case 3: return &svl;
    case 4: return &svd;
    case 5: return &svk;
    case 6: return &svc;
    case 7: return &gm;
    case 8: return &gv;
    case 9: return &iflags;
    case 10: return &mons;
    case 11: return &genders;
    default: return 0;
    }
}
int teleport_dbridge_monster_bit(const struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->wormno;
    case 1: return mon->msleeping;
    case 2: return mon->mcanmove;
    case 3: return mon->mconf;
    case 4: return mon->mstun;
    default: return 0;
    }
}
int teleport_dbridge_hero_bit(int index) { (void) index; return u.uinwater; }
int teleport_dbridge_roleplay_deaf(void) { return u.uroleplay.deaf; }
int teleport_dbridge_hero_event(int index) { return index == 0 ? u.uevent.uopened_dbridge : u.uevent.uheard_tune; }
void teleport_dbridge_set_hero_event(int index, unsigned value)
{ if (index == 0) u.uevent.uopened_dbridge = value; else u.uevent.uheard_tune = value; }
int teleport_dbridge_terrain_bit(coordxy x, coordxy y, int index)
{
    switch (index) {
    case 0: return levl[x][y].drawbridgemask;
    case 1: return levl[x][y].doormask;
    case 2: return levl[x][y].wall_info;
    case 3: return levl[x][y].horizontal;
    case 4: return levl[x][y].icedpool;
    default: return 0;
    }
}
void teleport_dbridge_set_terrain_bit(coordxy x, coordxy y, int index, unsigned value)
{
    switch (index) {
    case 0: levl[x][y].drawbridgemask = value; break;
    case 1: levl[x][y].doormask = value; break;
    case 2: levl[x][y].wall_info = value; break;
    case 3: levl[x][y].horizontal = value; break;
    case 4: levl[x][y].icedpool = value; break;
    }
}
static char teleport_dbridge_phrase[80];
char *teleport_dbridge_phrase_buffer(void) { return teleport_dbridge_phrase; }
static const char *const teleport_dbridge_callers[] = { "e_missed", "e_jumps", "destroy_drawbridge" };
int teleport_dbridge_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("dbridge.c", line, teleport_dbridge_callers[caller]); return (rn2)(bound); }
int teleport_dbridge_rnd(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("dbridge.c", line, teleport_dbridge_callers[caller]); return (rnd)(bound); }
void teleport_dbridge_pline(const char *fmt, const char *a, const char *b) { pline(fmt, a, b); }
void teleport_dbridge_pline_The(const char *fmt, const char *a, const char *b) { pline_The(fmt, a, b); }
void teleport_dbridge_You(const char *fmt, const char *a, const char *b) { You(fmt, a, b); }
void teleport_dbridge_You_see(const char *fmt, const char *a, const char *b) { You_see(fmt, a, b); }
void teleport_dbridge_You_hear(const char *fmt, const char *a, const char *b) { You_hear(fmt, a, b); }
void teleport_dbridge_pline_int(const char *fmt, int value) { pline(fmt, value); }
void teleport_dbridge_pline_name_int(const char *fmt, const char *name, int value) { pline(fmt, name, value); }
void teleport_dbridge_impossible(const char *fmt) { impossible(fmt); }
#ifdef TELEPORT_DBRIDGE_LITERAL_CAPACITY
static char teleport_dbridge_literals[TELEPORT_DBRIDGE_LITERAL_CAPACITY];
void *teleport_dbridge_literal_storage(void) { return teleport_dbridge_literals; }
size_t teleport_dbridge_literal_capacity(void) { return sizeof teleport_dbridge_literals; }
#endif

/* MONDATA: typed native field/dependency ABI; all monster data policy remains JS. */
const void *teleport_mondata_global(int index)
{
    switch (index) {
    case 0: return &u;
    case 1: return &gy;
    case 2: return &svm;
    case 3: return &gi;
    case 4: return &cg;
    case 5: return &gm;
    case 6: return &svl;
    case 7: return &gv;
    case 8: return &gu;
    case 9: return &mons;
    case 10: return &objects;
    case 11: return &def_monsyms;
    default: return 0;
    }
}
struct obj *teleport_mondata_equipment(int index)
{
    switch (index) {
    case 0: return uwep;
    case 1: return uarm;
    case 2: return ublindf;
    default: return 0;
    }
}
int teleport_mondata_monster_bit(const struct monst *mon, int index)
{
    switch (index) {
    case 0: return mon->mblinded;
    case 1: return mon->mcansee;
    case 2: return mon->msleeping;
    case 3: return mon->mcan;
    case 4: return mon->female;
    case 5: return mon->iswiz;
    case 6: return mon->mflee;
    default: return 0;
    }
}
int teleport_mondata_hero_bit(int index)
{
    switch (index) {
    case 0: return u.twoweap;
    case 1: return u.uswallow;
    case 2: return u.uhave.amulet;
    case 3: return u.uinwater;
    default: return 0;
    }
}
int teleport_mondata_terrain_bit(coordxy x, coordxy y, int index) { (void) index; return levl[x][y].lit; }
int teleport_mondata_trap_bit(const struct trap *trap, int index) { (void) index; return trap->ttyp; }
static const char *const teleport_mondata_callers[] = { "pronoun_gender", "resist_conflict", "get_atkdam_type" };
int teleport_mondata_rn2(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("mondata.c", line, teleport_mondata_callers[caller]); return (rn2)(bound); }
int teleport_mondata_rnd(int bound, int line, int caller)
{ if (rng_log_enabled()) rng_log_set_caller("mondata.c", line, teleport_mondata_callers[caller]); return (rnd)(bound); }
void teleport_mondata_impossible(const char *fmt, int value) { impossible(fmt, value); }
#ifdef TELEPORT_MONDATA_LITERAL_CAPACITY
static char teleport_mondata_literals[TELEPORT_MONDATA_LITERAL_CAPACITY];
void *teleport_mondata_literal_storage(void) { return teleport_mondata_literals; }
size_t teleport_mondata_literal_capacity(void) { return sizeof teleport_mondata_literals; }
#endif

/* HACKLIB: zero storage and typed libc/callback ABI; utilities remain JS. */
static char teleport_hacklib_suffix[BUFSZ];
static char teleport_hacklib_ing[BUFSZ];
static char teleport_hacklib_visctrl[5][5];
static char teleport_hacklib_sitoa[13];
void *teleport_hacklib_storage(int index)
{
    switch (index) {
    case 0: return teleport_hacklib_suffix;
    case 1: return teleport_hacklib_ing;
    case 2: return teleport_hacklib_visctrl;
    case 3: return teleport_hacklib_sitoa;
    default: return 0;
    }
}
extern int teleport_hacklib_compare(const void *, const void *);
int teleport_hacklib_comparator(const void *a, const void *b)
{ return teleport_hacklib_compare(a, b); }
uintptr_t teleport_hacklib_callback_pointer(void)
{ return (uintptr_t) teleport_hacklib_comparator; }
int teleport_hacklib_call_comparator(uintptr_t token, const void *a, const void *b)
{ return ((int (QSORTCALLBACK *)(const void *, const void *)) token)(a, b); }
void teleport_hacklib_qsort(void *base, size_t count, size_t size)
{ (qsort)(base, count, size, teleport_hacklib_comparator); }
void *teleport_hacklib_malloc(size_t size) { return malloc(size); }
void teleport_hacklib_free(void *value) { free(value); }
void *teleport_hacklib_memcpy(void *dst, const void *src, size_t size)
{ return memcpy(dst, src, size); }
int teleport_hacklib_vsnprintf(char *out, size_t size, const char *fmt, va_list args)
{ return vsnprintf(out, size, fmt, args); }
void teleport_hacklib_format(char *out, const char *fmt, int value)
{ Sprintf(out, fmt, value); }
int teleport_hacklib_isupper(int value) { return isupper(value); }
int teleport_hacklib_tolower(int value) { return tolower(value); }
ssize_t teleport_hacklib_read(int fd, void *buf, size_t count)
{ return read(fd, buf, count); }
ssize_t teleport_hacklib_write(int fd, const void *buf, size_t count)
{ return write(fd, buf, count); }
#ifdef TELEPORT_HACKLIB_LITERAL_CAPACITY
static char teleport_hacklib_literals[TELEPORT_HACKLIB_LITERAL_CAPACITY];
void *teleport_hacklib_literal_storage(void) { return teleport_hacklib_literals; }
size_t teleport_hacklib_literal_capacity(void) { return sizeof teleport_hacklib_literals; }
#endif
