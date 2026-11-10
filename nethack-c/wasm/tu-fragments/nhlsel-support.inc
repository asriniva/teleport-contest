/* Typed ABI/header/dependency calls only; original NHLSEL bodies/data stay JS. */
#include "hack.h"
#include "sp_lev.h"
#include <stdint.h>
static char teleport_nhlsel_literals[653];
static luaL_Reg teleport_nhlsel_methods[25],teleport_nhlsel_meta[9];
static const char *teleport_nhlsel_growdirs[7],*teleport_nhlsel_gradtypes[3];
char *teleport_nhlsel_literal_storage(void){return teleport_nhlsel_literals;}
size_t teleport_nhlsel_literal_capacity(void){return sizeof teleport_nhlsel_literals;}
void *teleport_nhlsel_global(int n){switch(n){case 0:return (void*)&cg.zeroNhRect;case 1:return &gc.coder;case 2:return &gx.xstart;case 3:return &gy.ystart;case 4:return &svn.nroom;case 5:return svr.rooms;default:return &levl[0][0];}}
void *teleport_nhlsel_table(int n){return n==0?(void*)teleport_nhlsel_methods:n==1?(void*)teleport_nhlsel_meta:n==2?(void*)teleport_nhlsel_growdirs:(void*)teleport_nhlsel_gradtypes;}
void teleport_nhlsel_rect_bounds(const NhRect *a,const NhRect *b,NhRect *out){rect_bounds(*a,*b,out);}
int teleport_nhlsel_gc(lua_State *L,int what,int data){return lua_gc(L,what,data);}
void teleport_nhlsel_free(void *p){free(p);}
extern int teleport_nhlsel_l_selection_gc(lua_State *);
extern int teleport_nhlsel_l_selection_new(lua_State *);
extern int teleport_nhlsel_l_selection_clone(lua_State *);
extern int teleport_nhlsel_l_selection_setpoint(lua_State *);
extern int teleport_nhlsel_l_selection_numpoints(lua_State *);
extern int teleport_nhlsel_l_selection_getpoint(lua_State *);
extern int teleport_nhlsel_l_selection_not(lua_State *);
extern int teleport_nhlsel_l_selection_and(lua_State *);
extern int teleport_nhlsel_l_selection_or(lua_State *);
extern int teleport_nhlsel_l_selection_xor(lua_State *);
extern int teleport_nhlsel_l_selection_sub(lua_State *);
extern int teleport_nhlsel_l_selection_filter_percent(lua_State *);
extern int teleport_nhlsel_l_selection_rndcoord(lua_State *);
extern int teleport_nhlsel_l_selection_room(lua_State *);
extern int teleport_nhlsel_l_selection_getbounds(lua_State *);
extern int teleport_nhlsel_l_selection_line(lua_State *);
extern int teleport_nhlsel_l_selection_rect(lua_State *);
extern int teleport_nhlsel_l_selection_fillrect(lua_State *);
extern int teleport_nhlsel_l_selection_randline(lua_State *);
extern int teleport_nhlsel_l_selection_grow(lua_State *);
extern int teleport_nhlsel_l_selection_filter_mapchar(lua_State *);
extern int teleport_nhlsel_l_selection_match(lua_State *);
extern int teleport_nhlsel_l_selection_flood(lua_State *);
extern int teleport_nhlsel_l_selection_circle(lua_State *);
extern int teleport_nhlsel_l_selection_ellipse(lua_State *);
extern int teleport_nhlsel_l_selection_gradient(lua_State *);
extern int teleport_nhlsel_l_selection_iterate(lua_State *);
extern int teleport_nhlsel_l_selection_size_description(lua_State *);
uintptr_t teleport_nhlsel_callback(int n){switch(n){case 0:return (uintptr_t)teleport_nhlsel_l_selection_gc;case 1:return (uintptr_t)teleport_nhlsel_l_selection_new;case 2:return (uintptr_t)teleport_nhlsel_l_selection_clone;case 3:return (uintptr_t)teleport_nhlsel_l_selection_setpoint;case 4:return (uintptr_t)teleport_nhlsel_l_selection_numpoints;case 5:return (uintptr_t)teleport_nhlsel_l_selection_getpoint;case 6:return (uintptr_t)teleport_nhlsel_l_selection_not;case 7:return (uintptr_t)teleport_nhlsel_l_selection_and;case 8:return (uintptr_t)teleport_nhlsel_l_selection_or;case 9:return (uintptr_t)teleport_nhlsel_l_selection_xor;case 10:return (uintptr_t)teleport_nhlsel_l_selection_sub;case 11:return (uintptr_t)teleport_nhlsel_l_selection_filter_percent;case 12:return (uintptr_t)teleport_nhlsel_l_selection_rndcoord;case 13:return (uintptr_t)teleport_nhlsel_l_selection_room;case 14:return (uintptr_t)teleport_nhlsel_l_selection_getbounds;case 15:return (uintptr_t)teleport_nhlsel_l_selection_line;case 16:return (uintptr_t)teleport_nhlsel_l_selection_rect;case 17:return (uintptr_t)teleport_nhlsel_l_selection_fillrect;case 18:return (uintptr_t)teleport_nhlsel_l_selection_randline;case 19:return (uintptr_t)teleport_nhlsel_l_selection_grow;case 20:return (uintptr_t)teleport_nhlsel_l_selection_filter_mapchar;case 21:return (uintptr_t)teleport_nhlsel_l_selection_match;case 22:return (uintptr_t)teleport_nhlsel_l_selection_flood;case 23:return (uintptr_t)teleport_nhlsel_l_selection_circle;case 24:return (uintptr_t)teleport_nhlsel_l_selection_ellipse;case 25:return (uintptr_t)teleport_nhlsel_l_selection_gradient;case 26:return (uintptr_t)teleport_nhlsel_l_selection_iterate;case 27:return (uintptr_t)teleport_nhlsel_l_selection_size_description;default:return 0;}}
void teleport_nhlsel_location(coordxy *x,coordxy *y,int mode,struct mkroom *room,long packed){get_location_coord(x,y,mode,room,packed);}
int teleport_nhlsel_pcall(lua_State *L,int nargs,int results,const char *name,NHL_pcall_action action){return nhl_pcall_handle(L,nargs,results,name,action);}
char *teleport_nhlsel_duplicate(const char *p){return dupstr(p);}
