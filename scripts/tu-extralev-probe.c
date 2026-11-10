#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-extralev-layout.h"

__typeof__(gr) gr;
__typeof__(gs) gs;
__typeof__(svn) svn;
__typeof__(svr) svr;
__typeof__(svl) svl;
static uint32_t random_state;
static int random_values[512], random_length, random_index, log_enabled = 1, fail_monster, object_count, rename_replaces;
static struct monst ghost, renamed_ghost;
static struct obj fixture_objects[16];
static char trace[262144], caller[128];
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...)
{
    va_list args; va_start(args, format); vsnprintf(trace + strlen(trace), sizeof trace - strlen(trace), format, args); va_end(args);
}
void impossible(const char *format, ...)
{
    char message[BUFSZ]; va_list args; va_start(args, format); vsnprintf(message, sizeof message, format, args); va_end(args); append("impossible:%s;", message);
}
boolean rng_log_enabled(void) { return log_enabled; }
void rng_log_set_caller(const char *file, int line, const char *function)
{
    const char *base = strrchr(file, '/'); snprintf(caller, sizeof caller, "%s:%d:%s", base ? base + 1 : file, line, function);
}
static int draw(const char *name, int bound)
{
    int result;
    if (bound <= 0) abort();
    if (random_index < random_length) result = random_values[random_index] % bound;
    else { random_state = random_state * 1664525U + 1013904223U; result = (int) ((random_state >> 8) % (unsigned) bound); }
    random_index++; append("%s:%d:%d@%s;", name, bound, result, caller); return result;
}
int (rn2)(int bound) { return draw("rn2", bound); }
int (rnd)(int bound) { return draw("rnd", bound) + 1; }
void add_room(coordxy lx, coordxy ly, coordxy hx, coordxy hy, boolean lit, schar type, boolean special)
{
    int x, y;
    struct mkroom *room = &svr.rooms[svn.nroom];
    append("room:%d:%d:%d:%d:%d:%d:%d:%d;", svn.nroom, lx, ly, hx, hy, lit, type, special);
    memset(room, 0, sizeof *room); room->lx = lx; room->ly = ly; room->hx = hx; room->hy = hy; room->rlit = lit; room->rtype = type;
    for (x = lx - 1; x <= hx + 1; x++) for (y = ly - 1; y <= hy + 1; y++) {
        if (x < 0 || x >= COLNO || y < 0 || y >= ROWNO) abort();
        levl[x][y].typ = x == lx - 1 || x == hx + 1 ? VWALL : y == ly - 1 || y == hy + 1 ? HWALL : ROOM;
        levl[x][y].lit = lit;
    }
    svn.nroom++;
}
void dodoor(coordxy x, coordxy y, struct mkroom *room)
{
    append("door:%d:%d:%d;", x, y, (int) (room - svr.rooms)); levl[x][y].typ = DOOR; levl[x][y].doormask = D_CLOSED;
}
int somex(struct mkroom *room) { append("somex:%d;", (int) (room - svr.rooms)); return room->lx; }
int somey(struct mkroom *room) { append("somey:%d;", (int) (room - svr.rooms)); return room->ly; }
struct monst *makemon(struct permonst *data, coordxy x, coordxy y, mmflags_nht flags)
{
    append("make:%d:%d:%d:%lu;", monsndx(data), x, y, (unsigned long) flags);
    if (fail_monster) return NULL;
    memset(&ghost, 0, sizeof ghost); ghost.data = data; ghost.mx = x; ghost.my = y; return &ghost;
}
const char *roguename(void) { append("name;"); return "Fixture Rogue"; }
struct monst *christen_monst(struct monst *monster, const char *name)
{
    append("christen:%s:sleep=%d;", name, monster->msleeping);
    if (rename_replaces) { renamed_ghost = *monster; return &renamed_ghost; }
    return monster;
}
struct obj *mksobj_at(int type, coordxy x, coordxy y, boolean initialize, boolean artifact)
{
    struct obj *object;
    append("object:%d:%d:%d:%d:%d;", type, x, y, initialize, artifact);
    if (object_count >= SIZE(fixture_objects)) abort();
    object = &fixture_objects[object_count++]; memset(object, 0, sizeof *object);
    object->otyp = type; object->quan = 9007199254740993L; object->owt = 0x12345678U; object->spe = -5; return object;
}
int weight(struct obj *object) { append("weight:%d:%ld;", object->otyp, object->quan); return 0x12345678 + (int) object->quan * 11; }
void curse(struct obj *object) { append("curse:%d;", object->otyp); object->cursed = 1; }

#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/extralev.c"
#else
extern void teleport_extralev_test_join(coordxy, coordxy, coordxy, coordxy, int);
extern void teleport_extralev_test_corridor(coordxy, coordxy, int);
extern void teleport_extralev_test_walk(coordxy, coordxy);
#endif
void probe_reset(unsigned seed)
{
    monst_globals_init(); memset(&gr, 0, sizeof gr); memset(&gs, 0, sizeof gs); memset(&svn, 0, sizeof svn);
    memset(&svr, 0, sizeof svr); memset(&svl, 0, sizeof svl); memset(&ghost, 0, sizeof ghost); memset(&renamed_ghost, 0, sizeof renamed_ghost);
    memset(fixture_objects, 0, sizeof fixture_objects); object_count = 0; fail_monster = 0; rename_replaces = 0; log_enabled = 1;
    random_state = seed; random_length = random_index = 0; trace[0] = caller[0] = '\0';
}
void probe_clear(void) { trace[0] = '\0'; }
const char *probe_trace(void) { return trace; }
int *probe_rng_pointer(void) { return random_values; }
void probe_rng_length(int count) { random_length = count; random_index = 0; }
int probe_rng_count(void) { return random_index; }
unsigned probe_rng_state(void) { return random_state; }
void probe_options(int fail, int rename, int logging) { fail_monster = fail; rename_replaces = rename; log_enabled = logging; }
void probe_make(void) { makeroguerooms(); }
void probe_corr(int x, int y) { corr(x, y); }
void probe_join(int x1, int y1, int x2, int y2, int horizontal)
{
#ifdef TELEPORT_REFERENCE_TU
    roguejoin(x1, y1, x2, y2, horizontal);
#else
    teleport_extralev_test_join(x1, y1, x2, y2, horizontal);
#endif
}
void probe_corridor(int x, int y, int direction)
{
#ifdef TELEPORT_REFERENCE_TU
    roguecorr(x, y, direction);
#else
    teleport_extralev_test_corridor(x, y, direction);
#endif
}
void probe_walk(int x, int y)
{
#ifdef TELEPORT_REFERENCE_TU
    miniwalk(x, y);
#else
    teleport_extralev_test_walk(x, y);
#endif
}
void probe_ghost(void) { makerogueghost(); }
void *probe_grid_pointer(void) { return gr.r; }
void *probe_terrain_pointer(void) { return levl; }
void *probe_rooms_pointer(void) { return svr.rooms; }
void *probe_smeq_pointer(void) { return gs.smeq; }
int probe_nroom(void) { return svn.nroom; }
void probe_nroom_set(int count) { svn.nroom = count; }
void probe_cell(int x, int y, int real, int lx, int ly, int dx, int dy, int number, int doors)
{
    gr.r[x][y].real = real; gr.r[x][y].rlx = lx; gr.r[x][y].rly = ly; gr.r[x][y].dx = dx; gr.r[x][y].dy = dy; gr.r[x][y].nroom = number; gr.r[x][y].doortable = doors;
}
void probe_room(int index, int lx, int ly, int hx, int hy) { svn.nroom = index; add_room(lx, ly, hx, hy, 0, OROOM, FALSE); }
int probe_typ(int x, int y) { return levl[x][y].typ; }
int probe_door(int x, int y) { return levl[x][y].doormask; }
void probe_typ_set(int x, int y, int type) { levl[x][y].typ = type; }
int probe_ghost_sleep(void) { return ghost.msleeping; }
int probe_renamed_sleep(void) { return renamed_ghost.msleeping; }
int probe_object_count(void) { return object_count; }
int probe_object_type(int index) { return fixture_objects[index].otyp; }
long probe_object_quantity(int index) { return fixture_objects[index].quan; }
unsigned probe_object_weight(int index) { return fixture_objects[index].owt; }
int probe_object_spe(int index) { return fixture_objects[index].spe; }
int probe_object_cursed(int index) { return fixture_objects[index].cursed; }
int probe_object_known(int index) { return fixture_objects[index].known; }
int probe_object_proof(int index) { return fixture_objects[index].oerodeproof; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
