#include "hack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

__typeof__(gs) gs;
__typeof__(svd) svd;
struct you u;
static char trace[1024];
static int single_dnum = 3;
static char description[BUFSZ];

/* Controlled external dungeon dependencies, identical in both probe builds.
 * The production game continues to use its real dungeon and placement code. */
void assign_level(d_level *to, d_level *from) { *to = *from; }
boolean on_level(d_level *a, d_level *b) { return a->dnum == b->dnum && a->dlevel == b->dlevel; }
schar depth(d_level *lev) { return (schar) (lev->dlevel + 10 * lev->dnum); }
xint16 dunlev(d_level *lev) { return lev->dlevel; }
boolean single_level_branch(d_level *lev) { return lev->dnum == single_dnum; }
void u_on_newpos(coordxy x, coordxy y)
{
    snprintf(trace + strlen(trace), sizeof trace - strlen(trace), "pos:%d,%d;", x, y);
    u.ux = x; u.uy = y;
}
void u_on_rndspot(int flag)
{
    snprintf(trace + strlen(trace), sizeof trace - strlen(trace), "random:%d;", flag);
}
void panic(const char *format, ...) { abort(); }

size_t probe_context_size(void) { return sizeof(stairway); }
#define OFFSET(field) size_t probe_offset_##field(void) { return offsetof(stairway, field); }
OFFSET(sx) OFFSET(sy) OFFSET(tolev) OFFSET(up) OFFSET(isladder) OFFSET(u_traversed) OFFSET(next)
size_t probe_offset_dnum(void) { return offsetof(d_level, dnum); }
size_t probe_offset_dlevel(void) { return offsetof(d_level, dlevel); }
size_t probe_offset_uz(void) { return offsetof(struct you, uz); }
int probe_coordxy_size(void) { return sizeof(coordxy); }
int probe_bool_size(void) { return sizeof(boolean); }
int probe_bool_signed(void) { return (boolean) -1 < 0; }
int probe_level_size(void) { return sizeof(d_level); }
int probe_level_field_size(void) { return sizeof(((d_level *) 0)->dnum); }

void probe_init(void)
{
    stairway_free_all();
    memset(&u, 0, sizeof u);
    memset(&svd, 0, sizeof svd);
    trace[0] = description[0] = '\0';
    quest_dnum = 2;
    earth_level.dnum = air_level.dnum = fire_level.dnum = water_level.dnum = 4;
    earth_level.dlevel = 1; air_level.dlevel = 2;
    fire_level.dlevel = 3; water_level.dlevel = 4;
    strcpy(svd.dungeons[0].dname, "The Main Dungeon");
    strcpy(svd.dungeons[1].dname, "The Gnomish Mines");
    strcpy(svd.dungeons[2].dname, "The Quest");
    strcpy(svd.dungeons[3].dname, "Fort Ludios");
    strcpy(svd.dungeons[4].dname, "The End Game");
}
void probe_hero(int dnum, int dlevel, int amulet)
{
    u.uz.dnum = dnum; u.uz.dlevel = dlevel; u.uhave.amulet = !!amulet;
    trace[0] = '\0';
}
void probe_add(int x, int y, int up, int ladder, int dnum, int dlevel)
{
    d_level dest = { dnum, dlevel };
    stairway_add(x, y, up, ladder, &dest);
}
stairway *probe_head(void) { return gs.stairs; }
void probe_free(void) { stairway_free_all(); }
stairway *probe_at(int x, int y) { return stairway_at(x, y); }
stairway *probe_find(int dnum, int dlevel)
{
    d_level level = { dnum, dlevel }; return stairway_find(&level);
}
stairway *probe_find_from(int dnum, int dlevel, int ladder)
{
    d_level level = { dnum, dlevel }; return stairway_find_from(&level, ladder);
}
stairway *probe_find_dir(int up) { return stairway_find_dir(up); }
stairway *probe_find_type_dir(int ladder, int up) { return stairway_find_type_dir(ladder, up); }
stairway *probe_find_special_dir(int up) { return stairway_find_special_dir(up); }
void probe_special(int flag) { u_on_sstairs(flag); }
void probe_up(void) { u_on_upstairs(); }
void probe_down(void) { u_on_dnstairs(); }
int probe_on(int x, int y) { return On_stairs(x, y); }
int probe_ladder(int x, int y) { return On_ladder(x, y); }
int probe_on_up(int x, int y) { return On_stairs_up(x, y); }
int probe_on_down(int x, int y) { return On_stairs_dn(x, y); }
int probe_known(stairway *stairs) { return known_branch_stairs(stairs); }
char *probe_describe(stairway *stairs, int singular) { return stairs_description(stairs, description, singular); }
char *probe_description_buffer(void) { return description; }
char *probe_trace(void) { return trace; }
