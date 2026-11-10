#include "hack.h"
#include "sp_lev.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-mkmap-layout.h"
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(svn) svn;
__typeof__(svr) svr;
__typeof__(gs) gs;
__typeof__(svl) svl;
struct you u;
static struct mkroom fixture_subrooms[MAXNROFROOMS + 1];
static unsigned random_state;
static int random_values[2048], random_length, random_index, logging, failed_location, fixture_depth, buffer_live;
static char trace[262144], caller[128];
void panic(const char *format, ...) { abort(); }
int isok(coordxy x, coordxy y) { return x >= 1 && x <= COLNO - 1 && y >= 0 && y <= ROWNO - 1; }
static void append(const char *format, ...) { va_list ap; va_start(ap, format); vsnprintf(trace + strlen(trace), sizeof trace - strlen(trace), format, ap); va_end(ap); }
void impossible(const char *format, ...) { char b[BUFSZ]; va_list ap; va_start(ap, format); vsnprintf(b, sizeof b, format, ap); va_end(ap); append("impossible:%s;", b); }
boolean rng_log_enabled(void) { return logging; }
void rng_log_set_caller(const char *file, int line, const char *function) { const char *base = strrchr(file, '/'); snprintf(caller, sizeof caller, "%s:%d:%s", base ? base + 1 : file, line, function); }
static int draw(const char *kind, int bound) { int value; if (bound <= 0) abort(); if (random_index < random_length) value = random_values[random_index] % bound; else { random_state = random_state * 1664525U + 1013904223U; value = (random_state >> 8) % (unsigned) bound; } random_index++; append("%s:%d:%d@%s;", kind, bound, value, caller); return value; }
int (rn2)(int n) { return draw("rn2", n); }
int (rnd)(int n) { return draw("rnd", n) + 1; }
schar depth(d_level *level) { append("depth:%d:%d;", level->dnum, level->dlevel); return fixture_depth; }
void add_room(coordxy lx, coordxy ly, coordxy hx, coordxy hy, boolean lit, schar type, boolean special) { struct mkroom *r = &svr.rooms[svn.nroom]; append("room:%d:%d:%d:%d:%d:%d:%d:%d;", svn.nroom, lx, ly, hx, hy, lit, type, special); memset(r, 0, sizeof *r); r->lx=lx; r->ly=ly; r->hx=hx; r->hy=hy; r->rlit=lit; r->rtype=type; svn.nroom++; svr.rooms[svn.nroom].hx=-1; }
boolean somexy(struct mkroom *r, coord *c) { append("somexy:%d;", (int)(r-svr.rooms)); c->x=r->lx; c->y=r->hy; return failed_location ? FALSE : TRUE; }
boolean dig_corridor(coord *a, coord *b, int *count, boolean nox, schar fg, schar bg) { int x=a->x,y=a->y; append("dig:%d:%d:%d:%d:%d:%d:%d:%d;",a->x,a->y,b->x,b->y,count!=NULL,nox,fg,bg); while(x!=b->x) {levl[x][y].typ=fg; x+=x<b->x?1:-1;} while(y!=b->y) {levl[x][y].typ=fg; y+=y<b->y?1:-1;} levl[x][y].typ=fg; return TRUE; }
void wallify_map(coordxy lx,coordxy ly,coordxy hx,coordxy hy) { append("wall:%d:%d:%d:%d;",lx,ly,hx,hy); /* Controlled native dependency; preserve non-type bits. */ levl[lx][ly].typ=HWALL; }
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/mkmap.c"
#define PRIVATE(name) name
#else
extern void mkmap(lev_init *);
extern void teleport_mkmap_test_init_map(schar), teleport_mkmap_test_init_fill(schar,schar), teleport_mkmap_test_pass_one(schar,schar), teleport_mkmap_test_pass_two(schar,schar), teleport_mkmap_test_pass_three(schar,schar), teleport_mkmap_test_join_map_cleanup(void), teleport_mkmap_test_join_map(schar,schar), teleport_mkmap_test_finish_map(schar,schar,boolean,boolean,boolean), teleport_mkmap_test_remove_room(unsigned);
extern schar teleport_mkmap_test_get_map(coordxy,coordxy,schar);
#define PRIVATE(name) teleport_mkmap_test_##name
#endif
void probe_reset(unsigned seed) { if(buffer_live) free(gn.new_locations); memset(&gm,0,sizeof gm); memset(&gn,0,sizeof gn); memset(&svn,0,sizeof svn); memset(&svr,0,sizeof svr); memset(&gs,0,sizeof gs); memset(&svl,0,sizeof svl); memset(&u,0,sizeof u); memset(fixture_subrooms,0,sizeof fixture_subrooms); gs.subrooms=fixture_subrooms; memset(levl,0,sizeof svl.level.locations); random_state=seed; random_length=random_index=0; logging=1; failed_location=0; fixture_depth=1; trace[0]=caller[0]=0; gn.new_locations=(char *)alloc((COLNO-1)*(ROWNO-1)); memset(gn.new_locations,0xa5,(COLNO-1)*(ROWNO-1)); buffer_live=1; }
void probe_options(int log,int fail,int dep) { logging=log; failed_location=fail; fixture_depth=dep; }
void probe_clear(void) { trace[0]=0; }
const char *probe_trace(void) { return trace; }
int *probe_rng_pointer(void) { return random_values; }
void probe_rng_length(int n) { random_length=n; random_index=0; }
int probe_rng_count(void) { return random_index; }
unsigned probe_rng_state(void) { return random_state; }
void *probe_snapshot_pointer(int n) { switch(n) {case 0:return levl;case 1:return svr.rooms;case 2:return gs.subrooms;case 3:return buffer_live?gn.new_locations:NULL;default:return &svl.level.flags;} }
size_t probe_snapshot_size(int n) { switch(n) {case 0:return sizeof svl.level.locations;case 1:return sizeof svr.rooms;case 2:return sizeof fixture_subrooms;case 3:return buffer_live?(COLNO-1)*(ROWNO-1):0;default:return sizeof svl.level.flags;} }
int probe_scalar(int n) { switch(n) {case 0:return svn.nroom;case 1:return gn.nsubroom;case 2:return gn.n_loc_filled;case 3:return gm.min_rx;case 4:return gm.min_ry;case 5:return gm.max_rx;default:return gm.max_ry;} }
void probe_cell(int x,int y,int typ,int room,int lit,int edge,int flags) { levl[x][y].typ=typ;levl[x][y].roomno=room;levl[x][y].lit=lit;levl[x][y].edge=edge;levl[x][y].flags=flags; }
int probe_cell_field(int x,int y,int field) { switch(field){case 0:return levl[x][y].typ;case 1:return levl[x][y].roomno;case 2:return levl[x][y].lit;case 3:return levl[x][y].edge;default:return levl[x][y].flags;} }
void probe_room(int n,int lx,int ly,int hx,int hy,int irregular) { struct mkroom *r=&svr.rooms[n]; /* Only bounds and scalar fields are read by these tests; pointer-like sentinel bytes are never dereferenced. */ memset(r,17+n,sizeof *r);r->nsubrooms=0;r->lx=lx;r->ly=ly;r->hx=hx;r->hy=hy;r->irregular=irregular;r->doorct=n+3;r->fdoor=n+5;r->rtype=n+1;r->orig_rtype=n+2;r->rlit=n&1; if(svn.nroom<=n)svn.nroom=n+1; }
void probe_counts(int rooms,int subrooms) { svn.nroom=rooms;gn.nsubroom=subrooms; }
void probe_bounds(int x,int y) {gm.min_rx=gm.max_rx=x;gm.min_ry=gm.max_ry=y;gn.n_loc_filled=0;}
void probe_init(int bg) { PRIVATE(init_map)(bg); }
void probe_fill(int bg,int fg) { PRIVATE(init_fill)(bg,fg); }
int probe_get(int x,int y,int bg) {return PRIVATE(get_map)(x,y,bg);}
void probe_pass(int n,int bg,int fg) {if(n==1)PRIVATE(pass_one)(bg,fg);else if(n==2)PRIVATE(pass_two)(bg,fg);else PRIVATE(pass_three)(bg,fg);}
void probe_flood(int x,int y,int room,int lit,int any) {flood_fill_rm(x,y,room,lit,any);}
void probe_cleanup(void) {PRIVATE(join_map_cleanup)();}
void probe_join(int bg,int fg) {PRIVATE(join_map)(bg,fg);}
void probe_finish(int fg,int bg,int lit,int wall,int ice) {PRIVATE(finish_map)(fg,bg,lit,wall,ice);}
void probe_remove(unsigned n) {PRIVATE(remove_room)(n);}
void probe_remove_region(int lx,int ly,int hx,int hy) {remove_rooms(lx,ly,hx,hy);}
int probe_lit(int n) {return litstate_rnd(n);}
void probe_make(int bg,int fg,int smooth,int join,int lit,int wall,int ice) { lev_init init; memset(&init,0,sizeof init);init.bg=bg;init.fg=fg;init.smoothed=smooth;init.joined=join;init.lit=lit;init.walled=wall;init.icedpools=ice; if(buffer_live)free(gn.new_locations);buffer_live=0;mkmap(&init); }
size_t probe_stack(void) {return emscripten_stack_get_current();}
