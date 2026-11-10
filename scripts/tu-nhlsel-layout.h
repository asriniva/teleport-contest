/* Actual compiler data only; no NHLSEL implementation. */
#ifndef TELEPORT_NHLSEL_LAYOUT_H
#define TELEPORT_NHLSEL_LAYOUT_H
#include "hack.h"
#include "sp_lev.h"
#include <stddef.h>
struct nhlsel_meta{const char *name;long long value;};
static const struct nhlsel_meta nhlsel_layout[]={
{"BUFSZ",(long long)(BUFSZ)},
{"COLNO",(long long)(COLNO)},
{"ROWNO",(long long)(ROWNO)},
{"LUA_TUSERDATA",(long long)(LUA_TUSERDATA)},
{"LUA_TNUMBER",(long long)(LUA_TNUMBER)},
{"LUA_TTABLE",(long long)(LUA_TTABLE)},
{"LUA_TFUNCTION",(long long)(LUA_TFUNCTION)},
{"LUA_GCCOLLECT",(long long)(LUA_GCCOLLECT)},
{"LUA_REGISTRYINDEX",(long long)(LUA_REGISTRYINDEX)},
{"LUA_VERSION_NUM",(long long)(LUA_VERSION_NUM)},
{"LUAL_NUMSIZES",(long long)(LUAL_NUMSIZES)},
{"ANY_LOC",(long long)(ANY_LOC)},
{"INVALID_TYPE",(long long)(INVALID_TYPE)},
{"SP_COORD_IS_RANDOM",(long long)(SP_COORD_IS_RANDOM)},
{"W_ANY",(long long)(W_ANY)},
{"W_RANDOM",(long long)(W_RANDOM)},
{"W_NORTH",(long long)(W_NORTH)},
{"W_WEST",(long long)(W_WEST)},
{"W_EAST",(long long)(W_EAST)},
{"W_SOUTH",(long long)(W_SOUTH)},
{"SEL_GRADIENT_RADIAL",(long long)(SEL_GRADIENT_RADIAL)},
{"SEL_GRADIENT_SQUARE",(long long)(SEL_GRADIENT_SQUARE)},
{"NHLpa_impossible",(long long)(NHLpa_impossible)},
{"TRUE",(long long)(TRUE)},
{"FALSE",(long long)(FALSE)},
{"pointerSize",(long long)(sizeof(void*))},
{"longSize",(long long)(sizeof(long))},
{"intSize",(long long)(sizeof(int))},
{"coordSize",(long long)(sizeof(coordxy))},
{"booleanSize",(long long)(sizeof(boolean))},
{"charSigned",(long long)((char)-1<0)},
{"luaIntegerSize",(long long)(sizeof(lua_Integer))},
{"luaNumberSize",(long long)(sizeof(lua_Number))},
{"selectionSize",(long long)(sizeof(struct selectionvar))},
{"rectSize",(long long)(sizeof(NhRect))},
{"roomSize",(long long)(sizeof(struct mkroom))},
{"rmSize",(long long)(sizeof(struct rm))},
{"luaRegSize",(long long)(sizeof(luaL_Reg))},
{"luaReg_name",(long long)(offsetof(luaL_Reg,name))},
{"luaReg_func",(long long)(offsetof(luaL_Reg,func))},
{"xstartSize",(long long)(sizeof gx.xstart)},
{"ystartSize",(long long)(sizeof gy.ystart)},
{"nroomSize",(long long)(sizeof svn.nroom)},
{"coder_croom",(long long)(offsetof(struct sp_coder,croom))},
{"selection_wid",(long long)(offsetof(struct selectionvar,wid))},
{"selection_wid_size",(long long)(sizeof(((struct selectionvar*)0)->wid))},
{"selection_hei",(long long)(offsetof(struct selectionvar,hei))},
{"selection_hei_size",(long long)(sizeof(((struct selectionvar*)0)->hei))},
{"selection_bounds_dirty",(long long)(offsetof(struct selectionvar,bounds_dirty))},
{"selection_bounds_dirty_size",(long long)(sizeof(((struct selectionvar*)0)->bounds_dirty))},
{"selection_bounds",(long long)(offsetof(struct selectionvar,bounds))},
{"selection_bounds_size",(long long)(sizeof(((struct selectionvar*)0)->bounds))},
{"selection_map",(long long)(offsetof(struct selectionvar,map))},
{"selection_map_size",(long long)(sizeof(((struct selectionvar*)0)->map))},
{"rect_lx",(long long)(offsetof(NhRect,lx))},
{"rect_lx_size",(long long)(sizeof(((NhRect*)0)->lx))},
{"rect_ly",(long long)(offsetof(NhRect,ly))},
{"rect_ly_size",(long long)(sizeof(((NhRect*)0)->ly))},
{"rect_hx",(long long)(offsetof(NhRect,hx))},
{"rect_hx_size",(long long)(sizeof(((NhRect*)0)->hx))},
{"rect_hy",(long long)(offsetof(NhRect,hy))},
{"rect_hy_size",(long long)(sizeof(((NhRect*)0)->hy))},
{"room_lx",(long long)(offsetof(struct mkroom,lx))},
{"room_lx_size",(long long)(sizeof(((struct mkroom*)0)->lx))},
{"room_ly",(long long)(offsetof(struct mkroom,ly))},
{"room_ly_size",(long long)(sizeof(((struct mkroom*)0)->ly))},
{"rm_typ",(long long)(offsetof(struct rm,typ))},
{"rm_typ_size",(long long)(sizeof(((struct rm*)0)->typ))},
};
#ifdef NHLSEL_VALIDATE_REFERENCE
_Static_assert(SIZE(l_selection_methods)==25,"Configured original method rows changed");
_Static_assert(SIZE(l_selection_meta)==9,"Configured original metatable rows changed");
#endif
int probe_layout_count(void){return SIZE(nhlsel_layout);}
const char *probe_layout_name(int i){return nhlsel_layout[i].name;}
long long probe_layout_value(int i){return nhlsel_layout[i].value;}
#endif
