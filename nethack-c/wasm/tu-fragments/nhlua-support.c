/* NHLUA native ABI only: typed calls, addresses, storage, callbacks and jump lifetime. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include "nhlua-support.h"
#include "nhlua-source-data.h"
_Static_assert(sizeof(nhl_user_data)==TELEPORT_NHLUA_USERDATA_SIZE,"NHLUA userdata layout");
_Static_assert(sizeof(lua_Debug)==TELEPORT_NHLUA_LUA_DEBUG_SIZE,"NHLUA debug layout");
_Static_assert(NHL_SB_STEPSIZE==TELEPORT_NHLUA_CONFIGURED_STEP_SIZE,"NHLUA configured opcode stride");
static const char * teleport_nhlua_storage_0[7];
static boolean teleport_nhlua_storage_1[7];
static lua_State * teleport_nhlua_storage_2;
static struct teleport_nhlua_anonymous_342_14 teleport_nhlua_storage_3[35];
static struct luaL_Reg teleport_nhlua_storage_4[41];
static struct teleport_nhlua_anonymous_2057_14 teleport_nhlua_storage_5[9];
static struct luaL_Reg teleport_nhlua_storage_6[3];
static struct e teleport_nhlua_storage_7[10];
static struct e teleport_nhlua_storage_8[5];
static struct e teleport_nhlua_storage_9[7];
static struct e teleport_nhlua_storage_10[2];
static struct e teleport_nhlua_storage_11[4];
static struct e teleport_nhlua_storage_12[17];
static struct e teleport_nhlua_storage_13[2];
static struct e teleport_nhlua_storage_14[5];
static struct e teleport_nhlua_storage_15[8];
static const char * teleport_nhlua_storage_16[10];
static const char * teleport_nhlua_storage_17[3];
static int teleport_nhlua_storage_18;
static char teleport_nhlua_storage_19[256];
static char teleport_nhlua_storage_20[256];
static char teleport_nhlua_storage_21[256];
static char teleport_nhlua_storage_22[256];
static char teleport_nhlua_storage_23[256];
static char teleport_nhlua_storage_24[256];
static const char * teleport_nhlua_storage_25[5];
static struct teleport_nhlua_anonymous_2120_18 teleport_nhlua_storage_26[24];
void *teleport_nhlua_storage(int index){switch(index){
case 0:return &teleport_nhlua_storage_0;
case 1:return &teleport_nhlua_storage_1;
case 2:return &teleport_nhlua_storage_2;
case 3:return &teleport_nhlua_storage_3;
case 4:return &teleport_nhlua_storage_4;
case 5:return &teleport_nhlua_storage_5;
case 6:return &teleport_nhlua_storage_6;
case 7:return &teleport_nhlua_storage_7;
case 8:return &teleport_nhlua_storage_8;
case 9:return &teleport_nhlua_storage_9;
case 10:return &teleport_nhlua_storage_10;
case 11:return &teleport_nhlua_storage_11;
case 12:return &teleport_nhlua_storage_12;
case 13:return &teleport_nhlua_storage_13;
case 14:return &teleport_nhlua_storage_14;
case 15:return &teleport_nhlua_storage_15;
case 16:return &teleport_nhlua_storage_16;
case 17:return &teleport_nhlua_storage_17;
case 18:return &teleport_nhlua_storage_18;
case 19:return &teleport_nhlua_storage_19;
case 20:return &teleport_nhlua_storage_20;
case 21:return &teleport_nhlua_storage_21;
case 22:return &teleport_nhlua_storage_22;
case 23:return &teleport_nhlua_storage_23;
case 24:return &teleport_nhlua_storage_24;
case 25:return &teleport_nhlua_storage_25;
case 26:return &teleport_nhlua_storage_26;
default:abort();}}
void *teleport_nhlua_global(int index){switch(index){
case 0:return (void*)&gl;
case 1:return (void*)&emptystr;
case 2:return (void*)&svl;
case 3:return (void*)&WIN_MESSAGE;
case 4:return (void*)&windowprocs;
case 5:return (void*)&cg;
case 6:return (void*)&nul_glyphinfo;
case 7:return (void*)&svm;
case 8:return (void*)&flags;
case 9:return (void*)&svn;
case 10:return (void*)&svd;
case 11:return (void*)&mons;
case 12:return (void*)&obj_descr;
case 13:return (void*)&objects;
case 14:return (void*)&def_oc_syms;
case 15:return (void*)&gs;
case 16:return (void*)&gm;
case 17:return (void*)&iflags;
case 18:return (void*)&gi;
case 19:return (void*)&nhcb_name;
case 20:return (void*)&nhcb_counts;
case 21:return (void*)&u;
case 22:return (void*)&gg;
case 23:return (void*)&svs;
case 24:return (void*)&gu;
default:abort();}}
_Static_assert(sizeof(((struct RoleName*)0)->m)==8,"NHLUA pointer RoleName.m");
_Static_assert(sizeof(((struct teleport_nhlua_anonymous_2057_14*)0)->name)==8,"NHLUA pointer anonymous_2057_14.name");
_Static_assert(sizeof(((struct teleport_nhlua_anonymous_2057_14*)0)->value)==8 && (((__typeof__(((struct teleport_nhlua_anonymous_2057_14*)0)->value))-1<0)==1),"NHLUA field anonymous_2057_14.value width/sign");
_Static_assert(sizeof(((struct teleport_nhlua_anonymous_2120_18*)0)->name)==8,"NHLUA pointer anonymous_2120_18.name");
_Static_assert(sizeof(((struct teleport_nhlua_anonymous_2120_18*)0)->ptr)==8,"NHLUA pointer anonymous_2120_18.ptr");
_Static_assert(sizeof(((struct teleport_nhlua_anonymous_2120_18*)0)->type)==4 && (((__typeof__(((struct teleport_nhlua_anonymous_2120_18*)0)->type))-1<0)==1),"NHLUA field anonymous_2120_18.type width/sign");
_Static_assert(sizeof(((struct teleport_nhlua_anonymous_342_14*)0)->ch)==1 && (((__typeof__(((struct teleport_nhlua_anonymous_342_14*)0)->ch))-1<0)==1),"NHLUA field anonymous_342_14.ch width/sign");
_Static_assert(sizeof(((struct teleport_nhlua_anonymous_342_14*)0)->typ)==1 && (((__typeof__(((struct teleport_nhlua_anonymous_342_14*)0)->typ))-1<0)==1),"NHLUA field anonymous_342_14.typ width/sign");
_Static_assert(sizeof(((union any*)0)->a_char)==1 && (((__typeof__(((union any*)0)->a_char))-1<0)==1),"NHLUA field any.a_char width/sign");
_Static_assert(sizeof(((union any*)0)->a_int)==4 && (((__typeof__(((union any*)0)->a_int))-1<0)==1),"NHLUA field any.a_int width/sign");
_Static_assert(sizeof(((union any*)0)->a_schar)==1 && (((__typeof__(((union any*)0)->a_schar))-1<0)==1),"NHLUA field any.a_schar width/sign");
_Static_assert(sizeof(((union any*)0)->a_uchar)==1 && (((__typeof__(((union any*)0)->a_uchar))-1<0)==0),"NHLUA field any.a_uchar width/sign");
_Static_assert(sizeof(((struct class_sym*)0)->sym)==1 && (((__typeof__(((struct class_sym*)0)->sym))-1<0)==1),"NHLUA field class_sym.sym width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"NHLUA field d_level.dlevel width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"NHLUA field d_level.dnum width/sign");
_Static_assert(sizeof(((struct e*)0)->fnname)==8,"NHLUA pointer e.fnname");
_Static_assert(sizeof(((struct e*)0)->when)==4 && (((__typeof__(((struct e*)0)->when))-1<0)==0),"NHLUA field e.when width/sign");
_Static_assert(sizeof(((struct flag*)0)->debug)==1 && (((__typeof__(((struct flag*)0)->debug))-1<0)==1),"NHLUA field flag.debug width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_hunger)==1 && (((__typeof__(((struct instance_flags*)0)->debug_hunger))-1<0)==1),"NHLUA field instance_flags.debug_hunger width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_mongen)==1 && (((__typeof__(((struct instance_flags*)0)->debug_mongen))-1<0)==1),"NHLUA field instance_flags.debug_mongen width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_overwrite_stairs)==1 && (((__typeof__(((struct instance_flags*)0)->debug_overwrite_stairs))-1<0)==1),"NHLUA field instance_flags.debug_overwrite_stairs width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_prevent_pline)==1 && (((__typeof__(((struct instance_flags*)0)->debug_prevent_pline))-1<0)==1),"NHLUA field instance_flags.debug_prevent_pline width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->in_lua)==1 && (((__typeof__(((struct instance_flags*)0)->in_lua))-1<0)==1),"NHLUA field instance_flags.in_lua width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4 && (((__typeof__(((struct instance_flags*)0)->last_msg))-1<0)==1),"NHLUA field instance_flags.last_msg width/sign");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gmst_disco)==8,"NHLUA pointer instance_globals_g.gmst_disco");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gmst_invent)==8,"NHLUA pointer instance_globals_g.gmst_invent");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gmst_moves)==8 && (((__typeof__(((struct instance_globals_g*)0)->gmst_moves))-1<0)==1),"NHLUA field instance_globals_g.gmst_moves width/sign");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gmst_mvitals)==8,"NHLUA pointer instance_globals_g.gmst_mvitals");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gmst_stored)==1 && (((__typeof__(((struct instance_globals_g*)0)->gmst_stored))-1<0)==1),"NHLUA field instance_globals_g.gmst_stored width/sign");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gmst_ubak)==8,"NHLUA pointer instance_globals_g.gmst_ubak");
_Static_assert(sizeof(((struct instance_globals_i*)0)->in_mklev)==1 && (((__typeof__(((struct instance_globals_i*)0)->in_mklev))-1<0)==1),"NHLUA field instance_globals_i.in_mklev width/sign");
_Static_assert(sizeof(((struct instance_globals_i*)0)->invent)==8,"NHLUA pointer instance_globals_i.invent");
_Static_assert(sizeof(((struct instance_globals_l*)0)->lastinvnr)==4 && (((__typeof__(((struct instance_globals_l*)0)->lastinvnr))-1<0)==1),"NHLUA field instance_globals_l.lastinvnr width/sign");
_Static_assert(sizeof(((struct instance_globals_l*)0)->loglua)==4 && (((__typeof__(((struct instance_globals_l*)0)->loglua))-1<0)==1),"NHLUA field instance_globals_l.loglua width/sign");
_Static_assert(sizeof(((struct instance_globals_l*)0)->lua_sid)==4 && (((__typeof__(((struct instance_globals_l*)0)->lua_sid))-1<0)==1),"NHLUA field instance_globals_l.lua_sid width/sign");
_Static_assert(sizeof(((struct instance_globals_l*)0)->luacore)==8,"NHLUA pointer instance_globals_l.luacore");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8 && (((__typeof__(((struct instance_globals_m*)0)->multi))-1<0)==1),"NHLUA field instance_globals_m.multi width/sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->stairs)==8,"NHLUA pointer instance_globals_s.stairs");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8 && (((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1<0)==1),"NHLUA field instance_globals_saved_m.moves width/sign");
_Static_assert(sizeof(((struct instance_globals_saved_n*)0)->n_dgns)==4 && (((__typeof__(((struct instance_globals_saved_n*)0)->n_dgns))-1<0)==1),"NHLUA field instance_globals_saved_n.n_dgns width/sign");
_Static_assert(sizeof(((struct lua_Debug*)0)->currentline)==4 && (((__typeof__(((struct lua_Debug*)0)->currentline))-1<0)==1),"NHLUA field lua_Debug.currentline width/sign");
_Static_assert(sizeof(((struct lua_Debug*)0)->name)==8,"NHLUA pointer lua_Debug.name");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"NHLUA field monst.mhp width/sign");
_Static_assert(sizeof(((struct monst*)0)->nmon)==8,"NHLUA pointer monst.nmon");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1 && (((__typeof__(((struct mvitals*)0)->mvflags))-1<0)==0),"NHLUA field mvitals.mvflags width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2 && (((__typeof__(((struct nhcoord*)0)->x))-1<0)==1),"NHLUA field nhcoord.x width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2 && (((__typeof__(((struct nhcoord*)0)->y))-1<0)==1),"NHLUA field nhcoord.y width/sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->flags)==4 && (((__typeof__(((struct nhl_sandbox_info*)0)->flags))-1<0)==0),"NHLUA field nhl_sandbox_info.flags width/sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->memlimit)==4 && (((__typeof__(((struct nhl_sandbox_info*)0)->memlimit))-1<0)==0),"NHLUA field nhl_sandbox_info.memlimit width/sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->perpcall)==4 && (((__typeof__(((struct nhl_sandbox_info*)0)->perpcall))-1<0)==0),"NHLUA field nhl_sandbox_info.perpcall width/sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->steps)==4 && (((__typeof__(((struct nhl_sandbox_info*)0)->steps))-1<0)==0),"NHLUA field nhl_sandbox_info.steps width/sign");
_Static_assert(sizeof(((struct nhl_user_data*)0)->L)==8,"NHLUA pointer nhl_user_data.L");
_Static_assert(sizeof(((struct nhl_user_data*)0)->flags)==4 && (((__typeof__(((struct nhl_user_data*)0)->flags))-1<0)==0),"NHLUA field nhl_user_data.flags width/sign");
_Static_assert(sizeof(((struct nhl_user_data*)0)->memlimit)==4 && (((__typeof__(((struct nhl_user_data*)0)->memlimit))-1<0)==0),"NHLUA field nhl_user_data.memlimit width/sign");
_Static_assert(sizeof(((struct nhl_user_data*)0)->name)==8,"NHLUA pointer nhl_user_data.name");
_Static_assert(sizeof(((struct nhl_user_data*)0)->osteps)==4 && (((__typeof__(((struct nhl_user_data*)0)->osteps))-1<0)==0),"NHLUA field nhl_user_data.osteps width/sign");
_Static_assert(sizeof(((struct nhl_user_data*)0)->perpcall)==4 && (((__typeof__(((struct nhl_user_data*)0)->perpcall))-1<0)==0),"NHLUA field nhl_user_data.perpcall width/sign");
_Static_assert(sizeof(((struct nhl_user_data*)0)->sid)==4 && (((__typeof__(((struct nhl_user_data*)0)->sid))-1<0)==1),"NHLUA field nhl_user_data.sid width/sign");
_Static_assert(sizeof(((struct nhl_user_data*)0)->statctr)==4 && (((__typeof__(((struct nhl_user_data*)0)->statctr))-1<0)==0),"NHLUA field nhl_user_data.statctr width/sign");
_Static_assert(sizeof(((struct nhl_user_data*)0)->steps)==4 && (((__typeof__(((struct nhl_user_data*)0)->steps))-1<0)==0),"NHLUA field nhl_user_data.steps width/sign");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"NHLUA pointer obj.nobj");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8 && (((__typeof__(((struct obj*)0)->owornmask))-1<0)==1),"NHLUA field obj.owornmask width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_class)==1 && (((__typeof__(((struct objclass*)0)->oc_class))-1<0)==1),"NHLUA field objclass.oc_class width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2 && (((__typeof__(((struct objclass*)0)->oc_name_idx))-1<0)==1),"NHLUA field objclass.oc_name_idx width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_uname)==8,"NHLUA pointer objclass.oc_uname");
_Static_assert(sizeof(((struct objdescr*)0)->oc_name)==8,"NHLUA pointer objdescr.oc_name");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4 && (((__typeof__(((struct rm*)0)->glyph))-1<0)==1),"NHLUA field rm.glyph width/sign");
_Static_assert(sizeof(((struct rm*)0)->seenv)==1 && (((__typeof__(((struct rm*)0)->seenv))-1<0)==0),"NHLUA field rm.seenv width/sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"NHLUA field rm.typ width/sign");
_Static_assert(sizeof(((struct stairway*)0)->isladder)==1 && (((__typeof__(((struct stairway*)0)->isladder))-1<0)==1),"NHLUA field stairway.isladder width/sign");
_Static_assert(sizeof(((struct stairway*)0)->next)==8,"NHLUA pointer stairway.next");
_Static_assert(sizeof(((struct stairway*)0)->sx)==2 && (((__typeof__(((struct stairway*)0)->sx))-1<0)==1),"NHLUA field stairway.sx width/sign");
_Static_assert(sizeof(((struct stairway*)0)->sy)==2 && (((__typeof__(((struct stairway*)0)->sy))-1<0)==1),"NHLUA field stairway.sy width/sign");
_Static_assert(sizeof(((struct stairway*)0)->up)==1 && (((__typeof__(((struct stairway*)0)->up))-1<0)==1),"NHLUA field stairway.up width/sign");
_Static_assert(sizeof(((struct trap*)0)->tx)==2 && (((__typeof__(((struct trap*)0)->tx))-1<0)==1),"NHLUA field trap.tx width/sign");
_Static_assert(sizeof(((struct trap*)0)->ty)==2 && (((__typeof__(((struct trap*)0)->ty))-1<0)==1),"NHLUA field trap.ty width/sign");
_Static_assert(sizeof(((union vlaunchinfo*)0)->v_conjoined)==1 && (((__typeof__(((union vlaunchinfo*)0)->v_conjoined))-1<0)==0),"NHLUA field vlaunchinfo.v_conjoined width/sign");
_Static_assert(sizeof(((union vlaunchinfo*)0)->v_tnote)==2 && (((__typeof__(((union vlaunchinfo*)0)->v_tnote))-1<0)==1),"NHLUA field vlaunchinfo.v_tnote width/sign");
_Static_assert(sizeof(((struct window_procs*)0)->win_create_nhwindow)==8,"NHLUA pointer window_procs.win_create_nhwindow");
_Static_assert(sizeof(((struct window_procs*)0)->win_destroy_nhwindow)==8,"NHLUA pointer window_procs.win_destroy_nhwindow");
_Static_assert(sizeof(((struct window_procs*)0)->win_display_nhwindow)==8,"NHLUA pointer window_procs.win_display_nhwindow");
_Static_assert(sizeof(((struct window_procs*)0)->win_end_menu)==8,"NHLUA pointer window_procs.win_end_menu");
_Static_assert(sizeof(((struct window_procs*)0)->win_start_menu)==8,"NHLUA pointer window_procs.win_start_menu");
_Static_assert(sizeof(((struct you*)0)->dx)==4 && (((__typeof__(((struct you*)0)->dx))-1<0)==1),"NHLUA field you.dx width/sign");
_Static_assert(sizeof(((struct you*)0)->dy)==4 && (((__typeof__(((struct you*)0)->dy))-1<0)==1),"NHLUA field you.dy width/sign");
_Static_assert(sizeof(((struct you*)0)->dz)==4 && (((__typeof__(((struct you*)0)->dz))-1<0)==1),"NHLUA field you.dz width/sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4 && (((__typeof__(((struct you*)0)->mh))-1<0)==1),"NHLUA field you.mh width/sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4 && (((__typeof__(((struct you*)0)->mhmax))-1<0)==1),"NHLUA field you.mhmax width/sign");
_Static_assert(sizeof(((struct you*)0)->mtimedone)==4 && (((__typeof__(((struct you*)0)->mtimedone))-1<0)==1),"NHLUA field you.mtimedone width/sign");
_Static_assert(sizeof(((struct you*)0)->nv_range)==4 && (((__typeof__(((struct you*)0)->nv_range))-1<0)==1),"NHLUA field you.nv_range width/sign");
_Static_assert(sizeof(((struct you*)0)->tx)==2 && (((__typeof__(((struct you*)0)->tx))-1<0)==1),"NHLUA field you.tx width/sign");
_Static_assert(sizeof(((struct you*)0)->ty)==2 && (((__typeof__(((struct you*)0)->ty))-1<0)==1),"NHLUA field you.ty width/sign");
_Static_assert(sizeof(((struct you*)0)->uen)==4 && (((__typeof__(((struct you*)0)->uen))-1<0)==1),"NHLUA field you.uen width/sign");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4 && (((__typeof__(((struct you*)0)->uenmax))-1<0)==1),"NHLUA field you.uenmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4 && (((__typeof__(((struct you*)0)->uhp))-1<0)==1),"NHLUA field you.uhp width/sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4 && (((__typeof__(((struct you*)0)->uhpmax))-1<0)==1),"NHLUA field you.uhpmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4 && (((__typeof__(((struct you*)0)->uhunger))-1<0)==1),"NHLUA field you.uhunger width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4 && (((__typeof__(((struct you*)0)->ulevel))-1<0)==1),"NHLUA field you.ulevel width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevelmax)==4 && (((__typeof__(((struct you*)0)->ulevelmax))-1<0)==1),"NHLUA field you.ulevelmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uluck)==1 && (((__typeof__(((struct you*)0)->uluck))-1<0)==1),"NHLUA field you.uluck width/sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"NHLUA field you.umonnum width/sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"NHLUA field you.umonster width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"NHLUA field you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"NHLUA field you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->xray_range)==4 && (((__typeof__(((struct you*)0)->xray_range))-1<0)==1),"NHLUA field you.xray_range width/sign");
extern void teleport_nhlua_js_l_nhcore_init(void);
void teleport_nhlua_entry_l_nhcore_init(void){teleport_nhlua_js_l_nhcore_init();}
void l_nhcore_init(void){teleport_nhlua_entry_l_nhcore_init();}
extern void teleport_nhlua_js_l_nhcore_done(void);
void teleport_nhlua_entry_l_nhcore_done(void){teleport_nhlua_js_l_nhcore_done();}
void l_nhcore_done(void){teleport_nhlua_entry_l_nhcore_done();}
extern void teleport_nhlua_js_l_nhcore_call(int callidx);
void teleport_nhlua_entry_l_nhcore_call(int callidx){teleport_nhlua_js_l_nhcore_call(callidx);}
void l_nhcore_call(int callidx){teleport_nhlua_entry_l_nhcore_call(callidx);}
extern void teleport_nhlua_js_nhl_error(lua_State * L,const char * msg);
void teleport_nhlua_entry_nhl_error(lua_State * L,const char * msg){teleport_nhlua_js_nhl_error(L,msg);}
void nhl_error(lua_State * L,const char * msg){teleport_nhlua_entry_nhl_error(L,msg);__builtin_unreachable();}
extern void teleport_nhlua_js_lcheck_param_table(lua_State * L);
void teleport_nhlua_entry_lcheck_param_table(lua_State * L){teleport_nhlua_js_lcheck_param_table(L);}
void lcheck_param_table(lua_State * L){teleport_nhlua_entry_lcheck_param_table(L);}
extern schar teleport_nhlua_js_get_table_mapchr(lua_State * L,const char * name);
schar teleport_nhlua_entry_get_table_mapchr(lua_State * L,const char * name){return teleport_nhlua_js_get_table_mapchr(L,name);}
schar get_table_mapchr(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_mapchr(L,name);}
extern schar teleport_nhlua_js_get_table_mapchr_opt(lua_State * L,const char * name,schar defval);
schar teleport_nhlua_entry_get_table_mapchr_opt(lua_State * L,const char * name,schar defval){return teleport_nhlua_js_get_table_mapchr_opt(L,name,defval);}
schar get_table_mapchr_opt(lua_State * L,const char * name,schar defval){return teleport_nhlua_entry_get_table_mapchr_opt(L,name,defval);}
extern short teleport_nhlua_js_nhl_get_timertype(lua_State * L,int idx);
short teleport_nhlua_entry_nhl_get_timertype(lua_State * L,int idx){return teleport_nhlua_js_nhl_get_timertype(L,idx);}
short nhl_get_timertype(lua_State * L,int idx){return teleport_nhlua_entry_nhl_get_timertype(L,idx);}
extern void teleport_nhlua_js_nhl_add_table_entry_int(lua_State * L,const char * name,lua_Integer value);
void teleport_nhlua_entry_nhl_add_table_entry_int(lua_State * L,const char * name,lua_Integer value){teleport_nhlua_js_nhl_add_table_entry_int(L,name,value);}
void nhl_add_table_entry_int(lua_State * L,const char * name,lua_Integer value){teleport_nhlua_entry_nhl_add_table_entry_int(L,name,value);}
extern void teleport_nhlua_js_nhl_add_table_entry_char(lua_State * L,const char * name,char value);
void teleport_nhlua_entry_nhl_add_table_entry_char(lua_State * L,const char * name,char value){teleport_nhlua_js_nhl_add_table_entry_char(L,name,value);}
void nhl_add_table_entry_char(lua_State * L,const char * name,char value){teleport_nhlua_entry_nhl_add_table_entry_char(L,name,value);}
extern void teleport_nhlua_js_nhl_add_table_entry_str(lua_State * L,const char * name,const char * value);
void teleport_nhlua_entry_nhl_add_table_entry_str(lua_State * L,const char * name,const char * value){teleport_nhlua_js_nhl_add_table_entry_str(L,name,value);}
void nhl_add_table_entry_str(lua_State * L,const char * name,const char * value){teleport_nhlua_entry_nhl_add_table_entry_str(L,name,value);}
extern void teleport_nhlua_js_nhl_add_table_entry_bool(lua_State * L,const char * name,boolean value);
void teleport_nhlua_entry_nhl_add_table_entry_bool(lua_State * L,const char * name,boolean value){teleport_nhlua_js_nhl_add_table_entry_bool(L,name,value);}
void nhl_add_table_entry_bool(lua_State * L,const char * name,boolean value){teleport_nhlua_entry_nhl_add_table_entry_bool(L,name,value);}
extern void teleport_nhlua_js_nhl_add_table_entry_region(lua_State * L,const char * name,coordxy x1,coordxy y1,coordxy x2,coordxy y2);
void teleport_nhlua_entry_nhl_add_table_entry_region(lua_State * L,const char * name,coordxy x1,coordxy y1,coordxy x2,coordxy y2){teleport_nhlua_js_nhl_add_table_entry_region(L,name,x1,y1,x2,y2);}
void nhl_add_table_entry_region(lua_State * L,const char * name,coordxy x1,coordxy y1,coordxy x2,coordxy y2){teleport_nhlua_entry_nhl_add_table_entry_region(L,name,x1,y1,x2,y2);}
extern schar teleport_nhlua_js_splev_chr2typ(char c);
schar teleport_nhlua_entry_splev_chr2typ(char c){return teleport_nhlua_js_splev_chr2typ(c);}
schar splev_chr2typ(char c){return teleport_nhlua_entry_splev_chr2typ(c);}
extern schar teleport_nhlua_js_check_mapchr(const char * s);
schar teleport_nhlua_entry_check_mapchr(const char * s){return teleport_nhlua_js_check_mapchr(s);}
schar check_mapchr(const char * s){return teleport_nhlua_entry_check_mapchr(s);}
extern char teleport_nhlua_js_splev_typ2chr(schar typ);
char teleport_nhlua_entry_splev_typ2chr(schar typ){return teleport_nhlua_js_splev_typ2chr(typ);}
extern int teleport_nhlua_js_nhl_gettrap(lua_State * L);
int teleport_nhlua_entry_nhl_gettrap(lua_State * L){return teleport_nhlua_js_nhl_gettrap(L);}
extern int teleport_nhlua_js_nhl_deltrap(lua_State * L);
int teleport_nhlua_entry_nhl_deltrap(lua_State * L){return teleport_nhlua_js_nhl_deltrap(L);}
extern boolean teleport_nhlua_js_nhl_get_xy_params(lua_State * L,lua_Integer * x,lua_Integer * y);
boolean teleport_nhlua_entry_nhl_get_xy_params(lua_State * L,lua_Integer * x,lua_Integer * y){return teleport_nhlua_js_nhl_get_xy_params(L,x,y);}
boolean nhl_get_xy_params(lua_State * L,lua_Integer * x,lua_Integer * y){return teleport_nhlua_entry_nhl_get_xy_params(L,x,y);}
extern int teleport_nhlua_js_nhl_getmap(lua_State * L);
int teleport_nhlua_entry_nhl_getmap(lua_State * L){return teleport_nhlua_js_nhl_getmap(L);}
extern int teleport_nhlua_js_nhl_impossible(lua_State * L);
int teleport_nhlua_entry_nhl_impossible(lua_State * L){return teleport_nhlua_js_nhl_impossible(L);}
extern int teleport_nhlua_js_nhl_pline(lua_State * L);
int teleport_nhlua_entry_nhl_pline(lua_State * L){return teleport_nhlua_js_nhl_pline(L);}
extern int teleport_nhlua_js_nhl_verbalize(lua_State * L);
int teleport_nhlua_entry_nhl_verbalize(lua_State * L){return teleport_nhlua_js_nhl_verbalize(L);}
extern int teleport_nhlua_js_nhl_parse_config(lua_State * L);
int teleport_nhlua_entry_nhl_parse_config(lua_State * L){return teleport_nhlua_js_nhl_parse_config(L);}
extern int teleport_nhlua_js_nhl_get_config(lua_State * L);
int teleport_nhlua_entry_nhl_get_config(lua_State * L){return teleport_nhlua_js_nhl_get_config(L);}
extern int teleport_nhlua_js_nhl_getlin(lua_State * L);
int teleport_nhlua_entry_nhl_getlin(lua_State * L){return teleport_nhlua_js_nhl_getlin(L);}
extern int teleport_nhlua_js_nhl_menu(lua_State * L);
int teleport_nhlua_entry_nhl_menu(lua_State * L){return teleport_nhlua_js_nhl_menu(L);}
extern int teleport_nhlua_js_nhl_text(lua_State * L);
int teleport_nhlua_entry_nhl_text(lua_State * L){return teleport_nhlua_js_nhl_text(L);}
extern int teleport_nhlua_js_nhl_makeplural(lua_State * L);
int teleport_nhlua_entry_nhl_makeplural(lua_State * L){return teleport_nhlua_js_nhl_makeplural(L);}
extern int teleport_nhlua_js_nhl_makesingular(lua_State * L);
int teleport_nhlua_entry_nhl_makesingular(lua_State * L){return teleport_nhlua_js_nhl_makesingular(L);}
extern int teleport_nhlua_js_nhl_s_suffix(lua_State * L);
int teleport_nhlua_entry_nhl_s_suffix(lua_State * L){return teleport_nhlua_js_nhl_s_suffix(L);}
extern int teleport_nhlua_js_nhl_ing_suffix(lua_State * L);
int teleport_nhlua_entry_nhl_ing_suffix(lua_State * L){return teleport_nhlua_js_nhl_ing_suffix(L);}
extern int teleport_nhlua_js_nhl_an(lua_State * L);
int teleport_nhlua_entry_nhl_an(lua_State * L){return teleport_nhlua_js_nhl_an(L);}
extern boolean teleport_nhlua_js_nhl_lua_rnglog_ctx_enabled(void);
boolean teleport_nhlua_entry_nhl_lua_rnglog_ctx_enabled(void){return teleport_nhlua_js_nhl_lua_rnglog_ctx_enabled();}
extern void teleport_nhlua_js_nhl_rnglog_set_lua_caller(lua_State * L,const char * fallback);
void teleport_nhlua_entry_nhl_rnglog_set_lua_caller(lua_State * L,const char * fallback){teleport_nhlua_js_nhl_rnglog_set_lua_caller(L,fallback);}
extern int teleport_nhlua_js_nhl_rn2(lua_State * L);
int teleport_nhlua_entry_nhl_rn2(lua_State * L){return teleport_nhlua_js_nhl_rn2(L);}
extern int teleport_nhlua_js_nhl_random(lua_State * L);
int teleport_nhlua_entry_nhl_random(lua_State * L){return teleport_nhlua_js_nhl_random(L);}
extern int teleport_nhlua_js_nhl_level_difficulty(lua_State * L);
int teleport_nhlua_entry_nhl_level_difficulty(lua_State * L){return teleport_nhlua_js_nhl_level_difficulty(L);}
extern int teleport_nhlua_js_nhl_is_genocided(lua_State * L);
int teleport_nhlua_entry_nhl_is_genocided(lua_State * L){return teleport_nhlua_js_nhl_is_genocided(L);}
extern int teleport_nhlua_js_nhl_get_debug_themerm_name(lua_State * L);
int teleport_nhlua_entry_nhl_get_debug_themerm_name(lua_State * L){return teleport_nhlua_js_nhl_get_debug_themerm_name(L);}
extern int teleport_nhlua_js_get_table_int(lua_State * L,const char * name);
int teleport_nhlua_entry_get_table_int(lua_State * L,const char * name){return teleport_nhlua_js_get_table_int(L,name);}
int get_table_int(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_int(L,name);}
extern int teleport_nhlua_js_get_table_int_opt(lua_State * L,const char * name,int defval);
int teleport_nhlua_entry_get_table_int_opt(lua_State * L,const char * name,int defval){return teleport_nhlua_js_get_table_int_opt(L,name,defval);}
int get_table_int_opt(lua_State * L,const char * name,int defval){return teleport_nhlua_entry_get_table_int_opt(L,name,defval);}
extern char * teleport_nhlua_js_get_table_str(lua_State * L,const char * name);
char * teleport_nhlua_entry_get_table_str(lua_State * L,const char * name){return teleport_nhlua_js_get_table_str(L,name);}
char * get_table_str(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_str(L,name);}
extern char * teleport_nhlua_js_get_table_str_opt(lua_State * L,const char * name,char * defval);
char * teleport_nhlua_entry_get_table_str_opt(lua_State * L,const char * name,char * defval){return teleport_nhlua_js_get_table_str_opt(L,name,defval);}
char * get_table_str_opt(lua_State * L,const char * name,char * defval){return teleport_nhlua_entry_get_table_str_opt(L,name,defval);}
extern int teleport_nhlua_js_get_table_boolean(lua_State * L,const char * name);
int teleport_nhlua_entry_get_table_boolean(lua_State * L,const char * name){return teleport_nhlua_js_get_table_boolean(L,name);}
int get_table_boolean(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_boolean(L,name);}
extern int teleport_nhlua_js_get_table_boolean_opt(lua_State * L,const char * name,int defval);
int teleport_nhlua_entry_get_table_boolean_opt(lua_State * L,const char * name,int defval){return teleport_nhlua_js_get_table_boolean_opt(L,name,defval);}
int get_table_boolean_opt(lua_State * L,const char * name,int defval){return teleport_nhlua_entry_get_table_boolean_opt(L,name,defval);}
extern int teleport_nhlua_js_get_table_option(lua_State * L,const char * name,const char * defval,const char *const * opts);
int teleport_nhlua_entry_get_table_option(lua_State * L,const char * name,const char * defval,const char *const * opts){return teleport_nhlua_js_get_table_option(L,name,defval,opts);}
int get_table_option(lua_State * L,const char * name,const char * defval,const char *const * opts){return teleport_nhlua_entry_get_table_option(L,name,defval,opts);}
extern int teleport_nhlua_js_nhl_dnum_name(lua_State * L);
int teleport_nhlua_entry_nhl_dnum_name(lua_State * L){return teleport_nhlua_js_nhl_dnum_name(L);}
extern int teleport_nhlua_js_nhl_int_to_pm_name(lua_State * L);
int teleport_nhlua_entry_nhl_int_to_pm_name(lua_State * L){return teleport_nhlua_js_nhl_int_to_pm_name(L);}
extern int teleport_nhlua_js_nhl_int_to_obj_name(lua_State * L);
int teleport_nhlua_entry_nhl_int_to_obj_name(lua_State * L){return teleport_nhlua_js_nhl_int_to_obj_name(L);}
extern int teleport_nhlua_js_nhl_variable(lua_State * L);
int teleport_nhlua_entry_nhl_variable(lua_State * L){return teleport_nhlua_js_nhl_variable(L);}
extern char * teleport_nhlua_js_get_nh_lua_variables(void);
char * teleport_nhlua_entry_get_nh_lua_variables(void){return teleport_nhlua_js_get_nh_lua_variables();}
char * get_nh_lua_variables(void){return teleport_nhlua_entry_get_nh_lua_variables();}
extern void teleport_nhlua_js_save_luadata(NHFILE * nhfp);
void teleport_nhlua_entry_save_luadata(NHFILE * nhfp){teleport_nhlua_js_save_luadata(nhfp);}
void save_luadata(NHFILE * nhfp){teleport_nhlua_entry_save_luadata(nhfp);}
extern void teleport_nhlua_js_restore_luadata(NHFILE * nhfp);
void teleport_nhlua_entry_restore_luadata(NHFILE * nhfp){teleport_nhlua_js_restore_luadata(nhfp);}
void restore_luadata(NHFILE * nhfp){teleport_nhlua_entry_restore_luadata(nhfp);}
extern int teleport_nhlua_js_nhl_stairways(lua_State * L);
int teleport_nhlua_entry_nhl_stairways(lua_State * L){return teleport_nhlua_js_nhl_stairways(L);}
extern int teleport_nhlua_js_nhl_test(lua_State * L);
int teleport_nhlua_entry_nhl_test(lua_State * L){return teleport_nhlua_js_nhl_test(L);}
extern int teleport_nhlua_js_nhl_pushkey(lua_State * L);
int teleport_nhlua_entry_nhl_pushkey(lua_State * L){return teleport_nhlua_js_nhl_pushkey(L);}
extern int teleport_nhlua_js_nhl_doturn(lua_State * L);
int teleport_nhlua_entry_nhl_doturn(lua_State * L){return teleport_nhlua_js_nhl_doturn(L);}
extern int teleport_nhlua_js_nhl_debug_flags(lua_State * L);
int teleport_nhlua_entry_nhl_debug_flags(lua_State * L){return teleport_nhlua_js_nhl_debug_flags(L);}
extern int teleport_nhlua_js_nhl_flip_level(lua_State * L);
int teleport_nhlua_entry_nhl_flip_level(lua_State * L){return teleport_nhlua_js_nhl_flip_level(L);}
extern int teleport_nhlua_js_nhl_timer_has_at(lua_State * L);
int teleport_nhlua_entry_nhl_timer_has_at(lua_State * L){return teleport_nhlua_js_nhl_timer_has_at(L);}
extern int teleport_nhlua_js_nhl_timer_peek_at(lua_State * L);
int teleport_nhlua_entry_nhl_timer_peek_at(lua_State * L){return teleport_nhlua_js_nhl_timer_peek_at(L);}
extern int teleport_nhlua_js_nhl_timer_stop_at(lua_State * L);
int teleport_nhlua_entry_nhl_timer_stop_at(lua_State * L){return teleport_nhlua_js_nhl_timer_stop_at(L);}
extern int teleport_nhlua_js_nhl_timer_start_at(lua_State * L);
int teleport_nhlua_entry_nhl_timer_start_at(lua_State * L){return teleport_nhlua_js_nhl_timer_start_at(L);}
extern int teleport_nhlua_js_nhl_get_cmd_key(lua_State * L);
int teleport_nhlua_entry_nhl_get_cmd_key(lua_State * L){return teleport_nhlua_js_nhl_get_cmd_key(L);}
extern int teleport_nhlua_js_nhl_callback(lua_State * L);
int teleport_nhlua_entry_nhl_callback(lua_State * L){return teleport_nhlua_js_nhl_callback(L);}
extern int teleport_nhlua_js_nhl_gamestate(lua_State * L);
int teleport_nhlua_entry_nhl_gamestate(lua_State * L){return teleport_nhlua_js_nhl_gamestate(L);}
extern void teleport_nhlua_js_free_tutorial(void);
void teleport_nhlua_entry_free_tutorial(void){teleport_nhlua_js_free_tutorial();}
void free_tutorial(void){teleport_nhlua_entry_free_tutorial();}
extern void teleport_nhlua_js_tutorial(boolean entering);
void teleport_nhlua_entry_tutorial(boolean entering){teleport_nhlua_js_tutorial(entering);}
void tutorial(boolean entering){teleport_nhlua_entry_tutorial(entering);}
extern void teleport_nhlua_js_init_nhc_data(lua_State * L);
void teleport_nhlua_entry_init_nhc_data(lua_State * L){teleport_nhlua_js_init_nhc_data(L);}
extern int teleport_nhlua_js_nhl_push_anything(lua_State * L,int anytype,void * src);
int teleport_nhlua_entry_nhl_push_anything(lua_State * L,int anytype,void * src){return teleport_nhlua_js_nhl_push_anything(L,anytype,src);}
extern int teleport_nhlua_js_nhl_meta_u_index(lua_State * L);
int teleport_nhlua_entry_nhl_meta_u_index(lua_State * L){return teleport_nhlua_js_nhl_meta_u_index(L);}
extern int teleport_nhlua_js_nhl_meta_u_newindex(lua_State * L);
int teleport_nhlua_entry_nhl_meta_u_newindex(lua_State * L){return teleport_nhlua_js_nhl_meta_u_newindex(L);}
extern int teleport_nhlua_js_nhl_u_clear_inventory(lua_State * L);
int teleport_nhlua_entry_nhl_u_clear_inventory(lua_State * L){return teleport_nhlua_js_nhl_u_clear_inventory(L);}
extern int teleport_nhlua_js_nhl_u_giveobj(lua_State * L);
int teleport_nhlua_entry_nhl_u_giveobj(lua_State * L){return teleport_nhlua_js_nhl_u_giveobj(L);}
extern void teleport_nhlua_js_init_u_data(lua_State * L);
void teleport_nhlua_entry_init_u_data(lua_State * L){teleport_nhlua_js_init_u_data(L);}
extern int teleport_nhlua_js_traceback_handler(lua_State * L);
int teleport_nhlua_entry_traceback_handler(lua_State * L){return teleport_nhlua_js_traceback_handler(L);}
extern uint32_t teleport_nhlua_js_nhl_getmeminuse(lua_State * L);
uint32_t teleport_nhlua_entry_nhl_getmeminuse(lua_State * L){return teleport_nhlua_js_nhl_getmeminuse(L);}
extern int teleport_nhlua_js_nhl_pcall(lua_State * L,int nargs,int nresults,const char * name);
int teleport_nhlua_entry_nhl_pcall(lua_State * L,int nargs,int nresults,const char * name){return teleport_nhlua_js_nhl_pcall(L,nargs,nresults,name);}
int nhl_pcall(lua_State * L,int nargs,int nresults,const char * name){return teleport_nhlua_entry_nhl_pcall(L,nargs,nresults,name);}
extern int teleport_nhlua_js_nhl_pcall_handle(lua_State * L,int nargs,int nresults,const char * name,NHL_pcall_action npa);
int teleport_nhlua_entry_nhl_pcall_handle(lua_State * L,int nargs,int nresults,const char * name,NHL_pcall_action npa){return teleport_nhlua_js_nhl_pcall_handle(L,nargs,nresults,name,npa);}
int nhl_pcall_handle(lua_State * L,int nargs,int nresults,const char * name,NHL_pcall_action npa){return teleport_nhlua_entry_nhl_pcall_handle(L,nargs,nresults,name,npa);}
extern boolean teleport_nhlua_js_nhl_loadlua(lua_State * L,const char * fname);
boolean teleport_nhlua_entry_nhl_loadlua(lua_State * L,const char * fname){return teleport_nhlua_js_nhl_loadlua(L,fname);}
boolean nhl_loadlua(lua_State * L,const char * fname){return teleport_nhlua_entry_nhl_loadlua(L,fname);}
extern lua_State * teleport_nhlua_js_nhl_init(nhl_sandbox_info * sbi);
lua_State * teleport_nhlua_entry_nhl_init(nhl_sandbox_info * sbi){return teleport_nhlua_js_nhl_init(sbi);}
lua_State * nhl_init(nhl_sandbox_info * sbi){return teleport_nhlua_entry_nhl_init(sbi);}
extern void teleport_nhlua_js_nhl_done(lua_State * L);
void teleport_nhlua_entry_nhl_done(lua_State * L){teleport_nhlua_js_nhl_done(L);}
void nhl_done(lua_State * L){teleport_nhlua_entry_nhl_done(L);}
extern boolean teleport_nhlua_js_load_lua(const char * name,nhl_sandbox_info * sbi);
boolean teleport_nhlua_entry_load_lua(const char * name,nhl_sandbox_info * sbi){return teleport_nhlua_js_load_lua(name,sbi);}
boolean load_lua(const char * name,nhl_sandbox_info * sbi){return teleport_nhlua_entry_load_lua(name,sbi);}
extern const char * teleport_nhlua_js_get_lua_version(void);
const char * teleport_nhlua_entry_get_lua_version(void){return teleport_nhlua_js_get_lua_version();}
const char * get_lua_version(void){return teleport_nhlua_entry_get_lua_version();}
extern void teleport_nhlua_js_nhl_clearfromtable(lua_State * L,int flag,int tndx,struct e * todo);
void teleport_nhlua_entry_nhl_clearfromtable(lua_State * L,int flag,int tndx,struct e * todo){teleport_nhlua_js_nhl_clearfromtable(L,flag,tndx,todo);}
extern void teleport_nhlua_js_end_luapat(void);
void teleport_nhlua_entry_end_luapat(void){teleport_nhlua_js_end_luapat();}
extern void teleport_nhlua_js_nhl_pushhooked_open_table(lua_State * L);
void teleport_nhlua_entry_nhl_pushhooked_open_table(lua_State * L){teleport_nhlua_js_nhl_pushhooked_open_table(L);}
void nhl_pushhooked_open_table(lua_State * L){teleport_nhlua_entry_nhl_pushhooked_open_table(L);}
extern void teleport_nhlua_js_nhlL_openlibs(lua_State * L,uint32_t lflags);
void teleport_nhlua_entry_nhlL_openlibs(lua_State * L,uint32_t lflags){teleport_nhlua_js_nhlL_openlibs(L,lflags);}
extern void * teleport_nhlua_js_nhl_alloc(void * ud,void * ptr,size_t osize,size_t nsize);
void * teleport_nhlua_entry_nhl_alloc(void * ud,void * ptr,size_t osize,size_t nsize){return teleport_nhlua_js_nhl_alloc(ud,ptr,osize,nsize);}
extern int teleport_nhlua_js_nhl_panic(lua_State * L);
int teleport_nhlua_entry_nhl_panic(lua_State * L){return teleport_nhlua_js_nhl_panic(L);}
extern void teleport_nhlua_js_nhl_warn(void * userdata,const char * msg_fragment,int to_be_continued);
void teleport_nhlua_entry_nhl_warn(void * userdata,const char * msg_fragment,int to_be_continued){teleport_nhlua_js_nhl_warn(userdata,msg_fragment,to_be_continued);}
extern void teleport_nhlua_js_nhl_hookfn(lua_State * L,lua_Debug * ar);
void teleport_nhlua_entry_nhl_hookfn(lua_State * L,lua_Debug * ar){teleport_nhlua_js_nhl_hookfn(L,ar);}
extern lua_State * teleport_nhlua_js_nhlL_newstate(nhl_sandbox_info * sbi,const char * name);
lua_State * teleport_nhlua_entry_nhlL_newstate(nhl_sandbox_info * sbi,const char * name){return teleport_nhlua_js_nhlL_newstate(sbi,name);}
uintptr_t teleport_nhlua_function_pointer(int index){switch(index){
case 0:return (uintptr_t)&l_get_config_errors;
case 1:return (uintptr_t)&luaopen_base;
case 2:return (uintptr_t)&luaopen_coroutine;
case 3:return (uintptr_t)&luaopen_debug;
case 4:return (uintptr_t)&luaopen_math;
case 5:return (uintptr_t)&luaopen_os;
case 6:return (uintptr_t)&luaopen_string;
case 7:return (uintptr_t)&luaopen_table;
case 8:return (uintptr_t)&luaopen_utf8;
case 9:return (uintptr_t)&nhl_abs_coord;
case 10:return (uintptr_t)&teleport_nhlua_entry_nhl_alloc;
case 11:return (uintptr_t)&teleport_nhlua_entry_nhl_an;
case 12:return (uintptr_t)&teleport_nhlua_entry_nhl_callback;
case 13:return (uintptr_t)&teleport_nhlua_entry_nhl_debug_flags;
case 14:return (uintptr_t)&teleport_nhlua_entry_nhl_deltrap;
case 15:return (uintptr_t)&teleport_nhlua_entry_nhl_dnum_name;
case 16:return (uintptr_t)&teleport_nhlua_entry_nhl_doturn;
case 17:return (uintptr_t)&teleport_nhlua_entry_nhl_flip_level;
case 18:return (uintptr_t)&teleport_nhlua_entry_nhl_gamestate;
case 19:return (uintptr_t)&teleport_nhlua_entry_nhl_get_cmd_key;
case 20:return (uintptr_t)&teleport_nhlua_entry_nhl_get_config;
case 21:return (uintptr_t)&teleport_nhlua_entry_nhl_get_debug_themerm_name;
case 22:return (uintptr_t)&teleport_nhlua_entry_nhl_getlin;
case 23:return (uintptr_t)&teleport_nhlua_entry_nhl_getmap;
case 24:return (uintptr_t)&teleport_nhlua_entry_nhl_gettrap;
case 25:return (uintptr_t)&teleport_nhlua_entry_nhl_hookfn;
case 26:return (uintptr_t)&teleport_nhlua_entry_nhl_impossible;
case 27:return (uintptr_t)&teleport_nhlua_entry_nhl_ing_suffix;
case 28:return (uintptr_t)&teleport_nhlua_entry_nhl_int_to_obj_name;
case 29:return (uintptr_t)&teleport_nhlua_entry_nhl_int_to_pm_name;
case 30:return (uintptr_t)&teleport_nhlua_entry_nhl_is_genocided;
case 31:return (uintptr_t)&teleport_nhlua_entry_nhl_level_difficulty;
case 32:return (uintptr_t)&teleport_nhlua_entry_nhl_makeplural;
case 33:return (uintptr_t)&teleport_nhlua_entry_nhl_makesingular;
case 34:return (uintptr_t)&teleport_nhlua_entry_nhl_menu;
case 35:return (uintptr_t)&teleport_nhlua_entry_nhl_meta_u_index;
case 36:return (uintptr_t)&teleport_nhlua_entry_nhl_meta_u_newindex;
case 37:return (uintptr_t)&teleport_nhlua_entry_nhl_panic;
case 38:return (uintptr_t)&teleport_nhlua_entry_nhl_parse_config;
case 39:return (uintptr_t)&teleport_nhlua_entry_nhl_pline;
case 40:return (uintptr_t)&teleport_nhlua_entry_nhl_pushkey;
case 41:return (uintptr_t)&teleport_nhlua_entry_nhl_random;
case 42:return (uintptr_t)&teleport_nhlua_entry_nhl_rn2;
case 43:return (uintptr_t)&teleport_nhlua_entry_nhl_s_suffix;
case 44:return (uintptr_t)&teleport_nhlua_entry_nhl_stairways;
case 45:return (uintptr_t)&teleport_nhlua_entry_nhl_test;
case 46:return (uintptr_t)&teleport_nhlua_entry_nhl_text;
case 47:return (uintptr_t)&teleport_nhlua_entry_nhl_timer_has_at;
case 48:return (uintptr_t)&teleport_nhlua_entry_nhl_timer_peek_at;
case 49:return (uintptr_t)&teleport_nhlua_entry_nhl_timer_start_at;
case 50:return (uintptr_t)&teleport_nhlua_entry_nhl_timer_stop_at;
case 51:return (uintptr_t)&teleport_nhlua_entry_nhl_u_clear_inventory;
case 52:return (uintptr_t)&teleport_nhlua_entry_nhl_u_giveobj;
case 53:return (uintptr_t)&teleport_nhlua_entry_nhl_variable;
case 54:return (uintptr_t)&teleport_nhlua_entry_nhl_verbalize;
case 55:return (uintptr_t)&teleport_nhlua_entry_nhl_warn;
case 56:return (uintptr_t)&parse_config_line;
case 57:return (uintptr_t)&teleport_nhlua_entry_traceback_handler;
default:abort();}}
extern int teleport_nhlua_resume(uint64_t token,int resumed);
int teleport_nhlua_jump_scope(void *buffer,uint64_t token){if(setjmp(*(jmp_buf*)buffer))return teleport_nhlua_resume(token,1);return teleport_nhlua_resume(token,0);}
void teleport_nhlua_jump(void *buffer,int status){longjmp(*(jmp_buf*)buffer,status);}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
void teleport_nhlua_api_0(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_1(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_2(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_3(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_4(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_5(uint64_t a0,int a1,uint64_t a2){return (lua_getstack)((lua_State *)(uintptr_t)a0,(int)a1,(lua_Debug *)(uintptr_t)a2);}
int teleport_nhlua_api_6(uint64_t a0,uint64_t a1,uint64_t a2){return (lua_getinfo)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(lua_Debug *)(uintptr_t)a2);}
int teleport_nhlua_api_7(uint64_t a0,uint64_t a1,uint64_t a2,int a3){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3);}
uint64_t teleport_nhlua_api_8(uint64_t a0){return (uint64_t)(uintptr_t)(eos)((char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_9(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_10(uint64_t a0,uint64_t a1,int a2,uint64_t a3){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_11(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_12(uint64_t a0){return (lua_error)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_13(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_14(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_15(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_16(uint64_t a0,int a1,int a2){(luaL_checktype)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_17(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_18(uint64_t a0){(free)((void *)(uintptr_t)a0);}
int teleport_nhlua_api_19(uint64_t a0,int a1,uint64_t a2,uint64_t a3){return (luaL_checkoption)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(const char *const *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_20(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_21(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_22(uint64_t a0,int a1){(lua_rawset)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_23(uint64_t a0,uint64_t a1,int a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_nhlua_api_24(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_25(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_26(uint64_t a0,int a1){(lua_rawset)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_27(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_28(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_29(uint64_t a0,int a1){(lua_rawset)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_30(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_31(uint64_t a0,int a1){(lua_pushboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_32(uint64_t a0,int a1){(lua_rawset)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_33(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_34(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_35(uint64_t a0,int a1){(lua_rawset)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_36(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
void teleport_nhlua_api_37(uint64_t a0,uint64_t a1){(cvt_to_abscoord)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
int teleport_nhlua_api_38(int a0,int a1){return (isok)((short)a0,(short)a1);}
uint64_t teleport_nhlua_api_39(int a0,int a1){return (uint64_t)(uintptr_t)(t_at)((short)a0,(short)a1);}
void teleport_nhlua_api_40(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
uint64_t teleport_nhlua_api_41(int a0){return (uint64_t)(uintptr_t)(get_trapname_bytype)((int)a0);}
void teleport_nhlua_api_42(uint64_t a0,uint64_t a1){(cvt_to_abscoord)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
int teleport_nhlua_api_43(int a0,int a1){return (isok)((short)a0,(short)a1);}
uint64_t teleport_nhlua_api_44(int a0,int a1){return (uint64_t)(uintptr_t)(t_at)((short)a0,(short)a1);}
void teleport_nhlua_api_45(uint64_t a0){(deltrap)((struct trap *)(uintptr_t)a0);}
int teleport_nhlua_api_46(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int64_t teleport_nhlua_api_47(uint64_t a0,int a1,uint64_t a2){return (lua_tointegerx)((lua_State *)(uintptr_t)a0,(int)a1,(int *)(uintptr_t)a2);}
int64_t teleport_nhlua_api_48(uint64_t a0,int a1,uint64_t a2){return (lua_tointegerx)((lua_State *)(uintptr_t)a0,(int)a1,(int *)(uintptr_t)a2);}
int teleport_nhlua_api_49(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_50(uint64_t a0,int a1,uint64_t a2,uint64_t a3){return (get_coord)((lua_State *)(uintptr_t)a0,(int)a1,(lua_Integer *)(uintptr_t)a2,(lua_Integer *)(uintptr_t)a3);}
void teleport_nhlua_api_51(uint64_t a0,uint64_t a1){(cvt_to_abscoord)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
int teleport_nhlua_api_52(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_nhlua_api_53(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
uint64_t teleport_nhlua_api_54(int a0){return (uint64_t)(uintptr_t)(levltyp_to_name)((int)a0);}
int teleport_nhlua_api_55(uint64_t a0,uint64_t a1,int a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_nhlua_api_56(int a0,int a1){return (uint64_t)(uintptr_t)(t_at)((short)a0,(short)a1);}
uint64_t teleport_nhlua_api_57(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_58(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_59(uint64_t a0,int a1){(lua_settable)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_60(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_61(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_62(uint64_t a0,uint64_t a1){(impossible)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_63(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_64(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_65(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_66(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_67(uint64_t target,int a0,int a1){((void (*)(winid, boolean))(uintptr_t)target)((int)a0,(signed char)a1);}
int teleport_nhlua_api_68(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_69(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_70(uint64_t a0,uint64_t a1){(verbalize)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_71(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_72(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_73(uint64_t a0,uint64_t a1){return (parse_conf_str)((const char *)(uintptr_t)a0,(boolean (*)(char *))(uintptr_t)a1);}
int teleport_nhlua_api_74(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_75(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_76(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(get_option_value)((const char *)(uintptr_t)a0,(signed char)a1);}
uint64_t teleport_nhlua_api_77(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_78(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_79(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_80(uint64_t a0,uint64_t a1){(getlin)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_81(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_82(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_83(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_84(uint64_t a0,int a1){return (lua_isstring)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_85(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_86(uint64_t a0,int a1){return (lua_isstring)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_87(uint64_t a0,int a1,uint64_t a2,uint64_t a3){return (luaL_checkoption)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(const char *const *)(uintptr_t)a3);}
void teleport_nhlua_api_88(uint64_t a0,int a1,int a2){(luaL_checktype)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
int teleport_nhlua_api_89(uint64_t target,int a0){return ((winid (*)(int))(uintptr_t)target)((int)a0);}
void teleport_nhlua_api_90(uint64_t target,int a0,uint64_t a1){((void (*)(winid, unsigned long))(uintptr_t)target)((int)a0,(unsigned long)a1);}
void teleport_nhlua_api_91(uint64_t a0){(lua_pushnil)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_92(uint64_t a0,int a1){return (lua_next)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_93(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_94(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_95(uint64_t a0,int a1){return (lua_gettable)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_96(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_97(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_98(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_99(uint64_t a0,int a1){return (lua_gettable)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_100(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_101(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_102(uint64_t a0,int a1){return (lua_isstring)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_103(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_104(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_105(int a0,uint64_t a1,uint64_t a2,int a3,int a4,int a5,int a6,uint64_t a7,unsigned a8){(add_menu)((int)a0,(const glyph_info *)(uintptr_t)a1,(const union any *)(uintptr_t)a2,(char)a3,(char)a4,(int)a5,(int)a6,(const char *)(uintptr_t)a7,(unsigned int)a8);}
void teleport_nhlua_api_106(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_107(uint64_t target,int a0,uint64_t a1){((void (*)(winid, const char *))(uintptr_t)target)((int)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_108(int a0,int a1,uint64_t a2){return (select_menu)((int)a0,(int)a1,(menu_item **)(uintptr_t)a2);}
void teleport_nhlua_api_109(uint64_t target,int a0){((void (*)(winid))(uintptr_t)target)((int)a0);}
uint64_t teleport_nhlua_api_110(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_111(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_112(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_113(uint64_t target,int a0){return ((winid (*)(int))(uintptr_t)target)((int)a0);}
void teleport_nhlua_api_114(uint64_t target,int a0,uint64_t a1){((void (*)(winid, unsigned long))(uintptr_t)target)((int)a0,(unsigned long)a1);}
int teleport_nhlua_api_115(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_116(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_117(uint64_t a0){return (uint64_t)(uintptr_t)(dupstr)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_118(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_119(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(strchr)((const char *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_120(int a0,uint64_t a1){(add_menu_str)((int)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_121(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_122(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_123(uint64_t target,int a0,uint64_t a1){((void (*)(winid, const char *))(uintptr_t)target)((int)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_124(int a0,int a1,uint64_t a2){return (select_menu)((int)a0,(int)a1,(menu_item **)(uintptr_t)a2);}
void teleport_nhlua_api_125(uint64_t target,int a0){((void (*)(winid))(uintptr_t)target)((int)a0);}
int teleport_nhlua_api_126(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_127(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_128(uint64_t a0){return (uint64_t)(uintptr_t)(makeplural)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_129(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_130(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_131(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_132(uint64_t a0){return (uint64_t)(uintptr_t)(makesingular)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_133(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_134(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_135(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_136(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_137(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_138(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_139(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_140(uint64_t a0){return (uint64_t)(uintptr_t)(ing_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_141(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_142(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_143(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_144(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_145(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_146(uint64_t a0){return (uint64_t)(uintptr_t)(getenv)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_147(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_148(uint64_t a0){return (uint64_t)(uintptr_t)(getenv)((const char *)(uintptr_t)a0);}
void teleport_nhlua_api_149(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(char *)(uintptr_t)a5);}
void teleport_nhlua_api_150(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(char *)(uintptr_t)a5);}
void teleport_nhlua_api_151(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(char *)(uintptr_t)a5);}
int teleport_nhlua_api_152(uint64_t a0,int a1,uint64_t a2){return (lua_getstack)((lua_State *)(uintptr_t)a0,(int)a1,(lua_Debug *)(uintptr_t)a2);}
int teleport_nhlua_api_153(uint64_t a0,uint64_t a1,uint64_t a2){return (lua_getinfo)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(lua_Debug *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_154(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_155(uint64_t a0,uint64_t a1,uint64_t a2){return (strncmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2);}
void teleport_nhlua_api_156(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,int a5,uint64_t a6){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(int)a5,(const char *)(uintptr_t)a6);}
void teleport_nhlua_api_157(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(const char *)(uintptr_t)a5);}
int teleport_nhlua_api_158(uint64_t a0,int a1,uint64_t a2){return (lua_getstack)((lua_State *)(uintptr_t)a0,(int)a1,(lua_Debug *)(uintptr_t)a2);}
int teleport_nhlua_api_159(uint64_t a0,uint64_t a1,uint64_t a2){return (lua_getinfo)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(lua_Debug *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_160(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_161(uint64_t a0,uint64_t a1,uint64_t a2){return (strncmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2);}
void teleport_nhlua_api_162(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,int a5,uint64_t a6){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(int)a5,(const char *)(uintptr_t)a6);}
void teleport_nhlua_api_163(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(const char *)(uintptr_t)a5);}
void teleport_nhlua_api_164(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,int a7,uint64_t a8){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(const char *)(uintptr_t)a5,(char *)(uintptr_t)a6,(int)a7,(const char *)(uintptr_t)a8);}
void teleport_nhlua_api_165(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_166(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int64_t teleport_nhlua_api_167(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_168(int a0){return (rn2)((int)a0);}
void teleport_nhlua_api_169(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int teleport_nhlua_api_170(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int64_t teleport_nhlua_api_171(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_172(int a0){return (rn2)((int)a0);}
void teleport_nhlua_api_173(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int64_t teleport_nhlua_api_174(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
int64_t teleport_nhlua_api_175(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_176(int a0){return (rn2)((int)a0);}
void teleport_nhlua_api_177(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int teleport_nhlua_api_178(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_179(void){return (level_difficulty)();}
void teleport_nhlua_api_180(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int teleport_nhlua_api_181(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_182(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_183(uint64_t a0,uint64_t a1){return (name_to_mon)((const char *)(uintptr_t)a0,(int *)(uintptr_t)a1);}
void teleport_nhlua_api_184(uint64_t a0,int a1){(lua_pushboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_185(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_186(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_187(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_188(uint64_t a0){return (uint64_t)(uintptr_t)(getenv)((const char *)(uintptr_t)a0);}
void teleport_nhlua_api_189(uint64_t a0){(lua_pushnil)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_190(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_191(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int64_t teleport_nhlua_api_192(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_193(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_194(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_195(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
int64_t teleport_nhlua_api_196(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_197(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_198(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_199(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_200(uint64_t a0){return (uint64_t)(uintptr_t)(dupstr)((const char *)(uintptr_t)a0);}
void teleport_nhlua_api_201(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_202(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_203(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_204(uint64_t a0,int a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t)(luaL_optlstring)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(size_t *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_205(uint64_t a0,int a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t)(luaL_optlstring)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(size_t *)(uintptr_t)a3);}
void teleport_nhlua_api_206(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_207(uint64_t a0){return (uint64_t)(uintptr_t)(dupstr)((const char *)(uintptr_t)a0);}
void teleport_nhlua_api_208(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_209(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_210(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_211(uint64_t a0,int a1,uint64_t a2,uint64_t a3){return (luaL_checkoption)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(const char *const *)(uintptr_t)a3);}
int teleport_nhlua_api_212(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
int64_t teleport_nhlua_api_213(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_214(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_215(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_216(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_217(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_218(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_219(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_220(uint64_t a0,int a1,uint64_t a2,uint64_t a3){return (luaL_checkoption)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(const char *const *)(uintptr_t)a3);}
void teleport_nhlua_api_221(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_222(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int64_t teleport_nhlua_api_223(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_224(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_225(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_226(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int64_t teleport_nhlua_api_227(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_228(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_229(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_230(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int64_t teleport_nhlua_api_231(uint64_t a0,int a1){return (luaL_checkinteger)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_232(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_233(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_234(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_235(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_236(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_237(uint64_t a0){(panic)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_238(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_239(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_240(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_241(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_242(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_243(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_244(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_245(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_246(uint64_t a0){(lua_pushnil)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_247(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_248(uint64_t a0,int a1){(lua_pushboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
int64_t teleport_nhlua_api_249(uint64_t a0,int a1,uint64_t a2){return (lua_tointegerx)((lua_State *)(uintptr_t)a0,(int)a1,(int *)(uintptr_t)a2);}
void teleport_nhlua_api_250(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int teleport_nhlua_api_251(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_252(uint64_t a0,int a1){(lua_pushvalue)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_253(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_254(uint64_t a0,uint64_t a1){return (luaL_loadstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_255(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_256(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_257(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_258(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_259(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_260(uint64_t a0){(lua_pushnil)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_261(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_262(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_263(uint64_t a0,int a1){(lua_pushboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_264(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int64_t teleport_nhlua_api_265(uint64_t a0,int a1,uint64_t a2){return (lua_tointegerx)((lua_State *)(uintptr_t)a0,(int)a1,(int *)(uintptr_t)a2);}
void teleport_nhlua_api_266(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_267(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_268(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_269(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_270(uint64_t a0,int a1){(lua_pushvalue)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_271(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_272(uint64_t a0,uint64_t a1){return (luaL_loadstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_273(uint64_t a0){(panic)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_274(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_275(uint64_t a0,int a1){return (lua_type)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_276(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_277(uint64_t a0){return (uint64_t)(uintptr_t)(dupstr)((const char *)(uintptr_t)a0);}
void teleport_nhlua_api_278(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_279(uint64_t a0){return (uint64_t)(uintptr_t)(dupstr)((const char *)(uintptr_t)a0);}
unsigned teleport_nhlua_api_280(uint64_t a0,uint64_t a1,int a2){return (Strlen_)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
void teleport_nhlua_api_281(uint64_t a0,uint64_t a1,uint64_t a2){(sfo_unsigned)((NHFILE *)(uintptr_t)a0,(unsigned int *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_282(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(sfo_char)((NHFILE *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3);}
void teleport_nhlua_api_283(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_284(uint64_t a0,uint64_t a1,uint64_t a2){(sfi_unsigned)((NHFILE *)(uintptr_t)a0,(unsigned int *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_285(unsigned a0){return (uint64_t)(uintptr_t)(alloc)((unsigned int)a0);}
void teleport_nhlua_api_286(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(sfi_char)((NHFILE *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3);}
int teleport_nhlua_api_287(uint64_t a0,uint64_t a1){return (luaL_loadstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_288(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_289(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_290(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_291(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_292(uint64_t a0,int a1){(lua_settable)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_293(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_294(uint64_t a0,int a1,int a2){(luaL_checktype)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_295(uint64_t a0,int a1,int a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(int)a1,(int)a2,(char *)(uintptr_t)a3);}
void teleport_nhlua_api_296(uint64_t a0){(free)((void *)(uintptr_t)a0);}
int teleport_nhlua_api_297(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_298(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_299(int a0,int a1){(cmdq_add_key)((int)a0,(char)a1);}
int teleport_nhlua_api_300(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_301(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_302(void){(moveloop_core)();}
void teleport_nhlua_api_303(uint64_t a0){(mongone)((struct monst *)(uintptr_t)a0);}
int teleport_nhlua_api_304(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int64_t teleport_nhlua_api_305(uint64_t a0,int a1,uint64_t a2){return (lua_tointegerx)((lua_State *)(uintptr_t)a0,(int)a1,(int *)(uintptr_t)a2);}
void teleport_nhlua_api_306(int a0,int a1){(flip_level)((int)a0,(signed char)a1);}
void teleport_nhlua_api_307(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_308(uint64_t a0,uint64_t a1){(cvt_to_abscoord)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
int teleport_nhlua_api_309(int a0,int a1){return (isok)((short)a0,(short)a1);}
int64_t teleport_nhlua_api_310(int a0,int a1,int a2){return (spot_time_expires)((short)a0,(short)a1,(short)a2);}
void teleport_nhlua_api_311(uint64_t a0,int a1){(lua_pushboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_312(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_313(uint64_t a0,uint64_t a1){(cvt_to_abscoord)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
int teleport_nhlua_api_314(int a0,int a1){return (isok)((short)a0,(short)a1);}
int64_t teleport_nhlua_api_315(int a0,int a1,int a2){return (spot_time_expires)((short)a0,(short)a1,(short)a2);}
void teleport_nhlua_api_316(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_317(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_318(uint64_t a0,uint64_t a1){(cvt_to_abscoord)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
int teleport_nhlua_api_319(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_nhlua_api_320(int a0,int a1,int a2){(spot_stop_timers)((short)a0,(short)a1,(short)a2);}
int64_t teleport_nhlua_api_321(uint64_t a0,int a1,uint64_t a2){return (lua_tointegerx)((lua_State *)(uintptr_t)a0,(int)a1,(int *)(uintptr_t)a2);}
void teleport_nhlua_api_322(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_323(uint64_t a0,uint64_t a1){(cvt_to_abscoord)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
int teleport_nhlua_api_324(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_nhlua_api_325(int a0,int a1,int a2){(spot_stop_timers)((short)a0,(short)a1,(short)a2);}
uint64_t teleport_nhlua_api_326(int64_t a0){return (uint64_t)(uintptr_t)(long_to_any)((long)a0);}
int teleport_nhlua_api_327(int64_t a0,int a1,int a2,uint64_t a3){return (start_timer)((long)a0,(short)a1,(short)a2,(anything *)(uintptr_t)a3);}
int teleport_nhlua_api_328(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_329(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_330(uint64_t a0){return (uint64_t)(uintptr_t)(cmd_from_ecname)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_331(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_332(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_333(uint64_t a0){(panic)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_334(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_335(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_336(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_337(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_338(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_339(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_340(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_341(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_342(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_343(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_344(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_345(uint64_t a0,int a1){return (lua_toboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_346(uint64_t a0,int a1){return (debugcore)((const char *)(uintptr_t)a0,(signed char)a1);}
void teleport_nhlua_api_347(uint64_t a0,int a1,int a2,int a3,int a4){(pline)((const char *)(uintptr_t)a0,(int)a1,(int)a2,(int)a3,(int)a4);}
void teleport_nhlua_api_348(uint64_t a0,int64_t a1){(pline)((const char *)(uintptr_t)a0,(long)a1);}
void teleport_nhlua_api_349(uint64_t a0){(useupall)((struct obj *)(uintptr_t)a0);}
void teleport_nhlua_api_350(uint64_t a0,uint64_t a1){(extract_nobj)((struct obj *)(uintptr_t)a0,(struct obj **)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_351(uint64_t a0){return (uint64_t)(uintptr_t)(addinv_nomerge)((struct obj *)(uintptr_t)a0);}
void teleport_nhlua_api_352(uint64_t a0,int64_t a1){(setworn)((struct obj *)(uintptr_t)a0,(long)a1);}
void teleport_nhlua_api_353(uint64_t a0,uint64_t a1,int a2,uint64_t a3){(__assert_fail)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_354(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
void teleport_nhlua_api_355(uint64_t a0,uint64_t a1,int a2,uint64_t a3){(__assert_fail)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_356(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
void teleport_nhlua_api_357(uint64_t a0,uint64_t a1,int a2,uint64_t a3){(__assert_fail)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_358(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
void teleport_nhlua_api_359(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_360(void){(init_uhunger)();}
uint64_t teleport_nhlua_api_361(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
void teleport_nhlua_api_362(uint64_t a0){(setnotworn)((struct obj *)(uintptr_t)a0);}
void teleport_nhlua_api_363(uint64_t a0){(freeinv)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_364(unsigned a0){return (uint64_t)(uintptr_t)(alloc)((unsigned int)a0);}
uint64_t teleport_nhlua_api_365(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
uint64_t teleport_nhlua_api_366(unsigned a0){return (uint64_t)(uintptr_t)(alloc)((unsigned int)a0);}
uint64_t teleport_nhlua_api_367(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
uint64_t teleport_nhlua_api_368(unsigned a0){return (uint64_t)(uintptr_t)(alloc)((unsigned int)a0);}
uint64_t teleport_nhlua_api_369(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
uint64_t teleport_nhlua_api_370(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(memcpy)((void *)(uintptr_t)a0,(const void *)(uintptr_t)a1,(unsigned long)a2);}
uint64_t teleport_nhlua_api_371(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(memset)((void *)(uintptr_t)a0,(int)a1,(unsigned long)a2);}
void teleport_nhlua_api_372(uint64_t a0,uint64_t a1,uint64_t a2){(impossible)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_nhlua_api_373(void){(update_inventory)();}
void teleport_nhlua_api_374(uint64_t a0,uint64_t a1){(extract_nobj)((struct obj *)(uintptr_t)a0,(struct obj **)(uintptr_t)a1);}
void teleport_nhlua_api_375(uint64_t a0,uint64_t a1){(obfree)((struct obj *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
void teleport_nhlua_api_376(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_377(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_378(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_379(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
uint64_t teleport_nhlua_api_380(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_381(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_382(uint64_t a0,int a1){(lua_rawset)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_383(uint64_t a0,uint64_t a1){(lua_setglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_384(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_385(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_386(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
uint64_t teleport_nhlua_api_387(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(luaL_checklstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
int teleport_nhlua_api_388(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_389(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_390(uint64_t a0,uint64_t a1){(nhl_push_obj)((lua_State *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
int teleport_nhlua_api_391(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_392(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_pushstring)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_393(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_394(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int teleport_nhlua_api_395(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_396(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int teleport_nhlua_api_397(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_398(uint64_t a0){return (depth)((d_level *)(uintptr_t)a0);}
void teleport_nhlua_api_399(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
int teleport_nhlua_api_400(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_401(uint64_t a0){return (Invocation_lev)((d_level *)(uintptr_t)a0);}
void teleport_nhlua_api_402(uint64_t a0,int a1){(lua_pushboolean)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_403(uint64_t a0){(useupall)((struct obj *)(uintptr_t)a0);}
int teleport_nhlua_api_404(uint64_t a0){return (nhl_obj_u_giveobj)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_405(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_406(uint64_t a0,uint64_t a1,int a2){(luaL_setfuncs)((lua_State *)(uintptr_t)a0,(const struct luaL_Reg *)(uintptr_t)a1,(int)a2);}
void teleport_nhlua_api_407(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_408(uint64_t a0,uint64_t a1,int a2){(lua_pushcclosure)((lua_State *)(uintptr_t)a0,(int (*)(lua_State *))(uintptr_t)a1,(int)a2);}
void teleport_nhlua_api_409(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_410(uint64_t a0,uint64_t a1,int a2){(lua_pushcclosure)((lua_State *)(uintptr_t)a0,(int (*)(lua_State *))(uintptr_t)a1,(int)a2);}
void teleport_nhlua_api_411(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_412(uint64_t a0,int a1){return (lua_setmetatable)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_413(uint64_t a0,uint64_t a1){(lua_setglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_414(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_415(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_traceback)((lua_State *)(uintptr_t)a0,(lua_State *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3);}
int teleport_nhlua_api_416(uint64_t a0,int a1){return (lua_gc)((lua_State *)(uintptr_t)a0,(int)a1);}
int teleport_nhlua_api_417(uint64_t a0,int a1){return (lua_gc)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_418(uint64_t a0,uint64_t a1,int a2){(lua_pushcclosure)((lua_State *)(uintptr_t)a0,(int (*)(lua_State *))(uintptr_t)a1,(int)a2);}
void teleport_nhlua_api_419(uint64_t a0,int a1,int a2){(lua_rotate)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
uint64_t teleport_nhlua_api_420(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_getallocf)((lua_State *)(uintptr_t)a0,(void **)(uintptr_t)a1);}
void teleport_nhlua_api_421(uint64_t a0,int a1,uint64_t a2){(panic)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_nhlua_api_422(uint64_t a0,int a1,int a2,int a3,int64_t a4,uint64_t a5){return (lua_pcallk)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2,(int)a3,(long)a4,(int (*)(lua_State *, int, lua_KContext))(uintptr_t)a5);}
void teleport_nhlua_api_423(uint64_t a0,int a1,int a2){(lua_rotate)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_424(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_425(int64_t a0,uint64_t a1,int a2,uint64_t a3,int64_t a4){(livelog_printf)((long)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3,(long)a4);}
void teleport_nhlua_api_426(int64_t a0,uint64_t a1,int a2,uint64_t a3,uint64_t a4){(livelog_printf)((long)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3,(unsigned long)a4);}
uint64_t teleport_nhlua_api_427(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_getallocf)((lua_State *)(uintptr_t)a0,(void **)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_428(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_429(uint64_t a0,int a1,uint64_t a2,uint64_t a3){(panic)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_430(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_431(uint64_t a0,int a1,uint64_t a2,uint64_t a3){(impossible)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_nhlua_api_432(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
unsigned teleport_nhlua_api_433(uint64_t a0,uint64_t a1,int a2){return (Strlen_)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_nhlua_api_434(unsigned a0){return (uint64_t)(uintptr_t)(alloc)((unsigned int)a0);}
int teleport_nhlua_api_435(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_436(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(fopen)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_437(uint64_t a0,uint64_t a1){(impossible)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_nhlua_api_438(uint64_t a0,int64_t a1,int a2){return (fseek)((FILE *)(uintptr_t)a0,(long)a1,(int)a2);}
int64_t teleport_nhlua_api_439(uint64_t a0){return (ftell)((FILE *)(uintptr_t)a0);}
int teleport_nhlua_api_440(uint64_t a0,int64_t a1,int a2){return (fseek)((FILE *)(uintptr_t)a0,(long)a1,(int)a2);}
int teleport_nhlua_api_441(int64_t a0,uint64_t a1,int a2){return (FITSint_)((long long)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_nhlua_api_442(unsigned a0){return (uint64_t)(uintptr_t)(alloc)((unsigned int)a0);}
uint64_t teleport_nhlua_api_443(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (fread)((void *)(uintptr_t)a0,(unsigned long)a1,(unsigned long)a2,(FILE *)(uintptr_t)a3);}
uint64_t teleport_nhlua_api_444(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(strchr)((const char *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_445(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_446(uint64_t a0){return (uint64_t)(uintptr_t)(eos)((char *)(uintptr_t)a0);}
void teleport_nhlua_api_447(uint64_t a0,uint64_t a1){(impossible)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_nhlua_api_448(uint64_t a0){return (fclose)((FILE *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_449(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_450(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){return (luaL_loadbufferx)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2,(const char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
uint64_t teleport_nhlua_api_451(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_452(uint64_t a0,uint64_t a1,uint64_t a2){(impossible)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_453(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_454(uint64_t a0){(free)((void *)(uintptr_t)a0);}
void teleport_nhlua_api_455(uint64_t a0,int a1,int a2){(panic)((const char *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_456(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_457(uint64_t a0,uint64_t a1,int a2){(luaL_setfuncs)((lua_State *)(uintptr_t)a0,(const struct luaL_Reg *)(uintptr_t)a1,(int)a2);}
void teleport_nhlua_api_458(uint64_t a0,uint64_t a1){(lua_setglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_459(uint64_t a0){return (l_selection_register)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_460(uint64_t a0){(l_register_des)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_461(uint64_t a0){return (l_obj_register)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_462(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_463(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_464(uint64_t a0,uint64_t a1){(lua_setglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_465(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_getallocf)((lua_State *)(uintptr_t)a0,(void **)(uintptr_t)a1);}
void teleport_nhlua_api_466(int64_t a0,uint64_t a1,int a2,uint64_t a3,int64_t a4){(livelog_printf)((long)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3,(long)a4);}
void teleport_nhlua_api_467(int64_t a0,uint64_t a1,int a2,uint64_t a3,uint64_t a4){(livelog_printf)((long)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3,(unsigned long)a4);}
void teleport_nhlua_api_468(uint64_t a0){(lua_close)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_469(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_470(uint64_t a0,int a1){return (lua_isstring)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_471(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_472(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_473(uint64_t a0,uint64_t a1){return (lua_getglobal)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_nhlua_api_474(uint64_t a0,int a1){return (lua_isstring)((lua_State *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_nhlua_api_475(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
uint64_t teleport_nhlua_api_476(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
int teleport_nhlua_api_477(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_nhlua_api_478(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_479(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_nhlua_api_480(uint64_t a0){(lua_pushnil)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_481(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_482(uint64_t a0){(lua_close)((lua_State *)(uintptr_t)a0);}
int teleport_nhlua_api_483(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_484(uint64_t a0,int a1,int a2){(lua_createtable)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_nhlua_api_485(uint64_t a0,int a1){(lua_pushvalue)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_486(uint64_t a0,int a1,uint64_t a2){(lua_setfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_487(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
int teleport_nhlua_api_488(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_489(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_490(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
void teleport_nhlua_api_491(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_492(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
void teleport_nhlua_api_493(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_494(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
int teleport_nhlua_api_495(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_496(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_497(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
void teleport_nhlua_api_498(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_499(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
uint64_t teleport_nhlua_api_500(uint64_t a0){return (uint64_t)(uintptr_t)(nh_getenv)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_501(uint64_t a0,uint64_t a1,int a2){return (strtoul)((const char *)(uintptr_t)a0,(char **)(uintptr_t)a1,(int)a2);}
int teleport_nhlua_api_502(uint64_t a0,int a1,uint64_t a2){return (lua_getfield)((lua_State *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
void teleport_nhlua_api_503(uint64_t a0,int64_t a1){(lua_pushinteger)((lua_State *)(uintptr_t)a0,(long long)a1);}
void teleport_nhlua_api_504(uint64_t a0,int a1,int a2,int64_t a3,uint64_t a4){(lua_callk)((lua_State *)(uintptr_t)a0,(int)a1,(int)a2,(long)a3,(int (*)(lua_State *, int, lua_KContext))(uintptr_t)a4);}
void teleport_nhlua_api_505(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_506(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
void teleport_nhlua_api_507(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_508(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(luaL_requiref)((lua_State *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int (*)(lua_State *))(uintptr_t)a2,(int)a3);}
int teleport_nhlua_api_509(uint64_t a0){return (lua_gettop)((lua_State *)(uintptr_t)a0);}
void teleport_nhlua_api_510(uint64_t a0,int a1){(lua_settop)((lua_State *)(uintptr_t)a0,(int)a1);}
void teleport_nhlua_api_511(uint64_t a0){(free)((void *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_512(uint64_t a0,unsigned a1){return (uint64_t)(uintptr_t)(re_alloc)((long *)(uintptr_t)a0,(unsigned int)a1);}
uint64_t teleport_nhlua_api_513(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(lua_tolstring)((lua_State *)(uintptr_t)a0,(int)a1,(size_t *)(uintptr_t)a2);}
void teleport_nhlua_api_514(uint64_t a0,uint64_t a1){(panic)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_515(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_516(uint64_t a0){return (strlen)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_517(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(strncat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2);}
void teleport_nhlua_api_518(uint64_t a0,uint64_t a1){(paniclog)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_519(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_getallocf)((lua_State *)(uintptr_t)a0,(void **)(uintptr_t)a1);}
uint64_t teleport_nhlua_api_520(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_newstate)((void *(*)(void *, void *, size_t, size_t))(uintptr_t)a0,(void *)(uintptr_t)a1);}
void teleport_nhlua_api_521(uint64_t a0){(panic)((const char *)(uintptr_t)a0);}
uint64_t teleport_nhlua_api_522(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(lua_atpanic)((lua_State *)(uintptr_t)a0,(int (*)(lua_State *))(uintptr_t)a1);}
void teleport_nhlua_api_523(uint64_t a0,uint64_t a1,uint64_t a2){(lua_setwarnf)((lua_State *)(uintptr_t)a0,(void (*)(void *, const char *, int))(uintptr_t)a1,(void *)(uintptr_t)a2);}
void teleport_nhlua_api_524(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
void teleport_nhlua_api_525(uint64_t a0,uint64_t a1,int a2,int a3){(lua_sethook)((lua_State *)(uintptr_t)a0,(void (*)(lua_State *, lua_Debug *))(uintptr_t)a1,(int)a2,(int)a3);}
#pragma clang diagnostic pop
static char teleport_nhlua_literals[TELEPORT_NHLUA_NATIVE_LITERAL_CAPACITY];
char *teleport_nhlua_literal_storage(void){return teleport_nhlua_literals;}
size_t teleport_nhlua_literal_capacity(void){return sizeof teleport_nhlua_literals;}
#include "tu-nhlua-layout.h"
size_t teleport_nhlua_layout_count(void){return sizeof teleport_nhlua_layout/sizeof *teleport_nhlua_layout;}
const char *teleport_nhlua_layout_name(size_t i){return teleport_nhlua_layout[i].name;}
uint64_t teleport_nhlua_layout_value(size_t i){return teleport_nhlua_layout[i].value;}
