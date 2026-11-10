/* Configured NHLUA original-C/JS oracle with controlled foreign game effects. */
#include "hack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
static int reentered;extern void probe_js_reentry(void);static char tracebuf[1048576];static size_t tracepos;static int options[128];static void *growth;
static void append(const char *fmt,...) __attribute__((format(printf,1,2)));
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);if(n<0||tracepos+n>=sizeof tracebuf)abort();tracepos+=n;}
static void message(const char *kind,const char *fmt,va_list ap){char buf[8192];vsnprintf(buf,sizeof buf,fmt,ap);append("%s:%s;",kind,buf);}
extern void probe_js_fatal(const char *);
static void fatal(const char*fmt,va_list ap){char b[8192];vsnprintf(b,sizeof b,fmt,ap);append("panic:%s;",b);probe_js_fatal(b);abort();}
__typeof__(gl) gl;
char emptystr[1];
__typeof__(svl) svl;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(windowprocs) windowprocs;
__typeof__(cg) cg;
__typeof__(nul_glyphinfo) nul_glyphinfo;
__typeof__(svm) svm;
__typeof__(flags) flags;
__typeof__(svn) svn;
__typeof__(svd) svd;
__typeof__(mons) mons={[0]={.pmnames={"fixture male","fixture female","fixture neutral"}}};
__typeof__(obj_descr) obj_descr={[0]={.oc_name="fixture object"}};
__typeof__(objects) objects={[0]={.oc_class=1}};
__typeof__(def_oc_syms) def_oc_syms={[1]={.sym=41}};
__typeof__(gs) gs;
__typeof__(gm) gm;
__typeof__(iflags) iflags;
__typeof__(gi) gi;
const char *const nhcb_name[NUM_NHCB]={"cmd_before","level_enter","level_leave","end_turn"};
int nhcb_counts[NUM_NHCB];
__typeof__(u) u;
__typeof__(gg) gg;
__typeof__(svs) svs;
__typeof__(gu) gu;
static menu_item fixture_picks[3];static struct obj fixture_obj,fixture_inventory[3];static struct monst fixture_monsters[3];static stairway fixture_stairs[2];static struct trap fixture_trap;static struct stairway fixture_stair;static anything fixture_any;
static unsigned fixture_saved_length;static char fixture_saved[65536];
static int fixture_allocations;
static int fixture_seed=1;
static int fixture_rand(int n){fixture_seed=(unsigned)fixture_seed*1664525U+1013904223U;return n>0?(unsigned)fixture_seed%n:0;}
int (FITSint_)(long long a0,const char * a1,int a2){
return (int)a0;
}
boolean (Invocation_lev)(d_level * a0){
append("Invocation_lev;");
return options[7];
}
unsigned int (Strlen_)(const char * a0,const char * a1,int a2){
return (int)strlen(a0);
}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){
append("add_menu:%d:%d:%d:%d:%d:%d:%s:%u;",a0,a2->a_char,a3,a4,a5,a6,a7,a8);
}
void (add_menu_str)(winid a0,const char * a1){
append("add_menu_str:%d:%s;",a0,a1);if(options[21]&&!reentered){reentered=1;probe_js_reentry();}if(options[20]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();append("growth;");}
}
struct obj * (addinv_nomerge)(struct obj * a0){
append("addinv_nomerge:%u;",a0->o_id);a0->nobj=gi.invent;gi.invent=a0;a0->where=OBJ_INVENT;return a0;
}
long * (alloc)(unsigned int a0){
return (long*)malloc(a0);
}
char * (an)(const char * a0){
append("an:%s;",a0);return (char*)a0;
}
char * (cmd_from_ecname)(const char * a0){
append("cmd_from_ecname:%s;",a0);return (char*)a0;
}
void (cmdq_add_key)(int a0,char a1){
append("cmdq_add_key;");
}
void (cvt_to_abscoord)(coordxy * a0,coordxy * a1){
append("cvt:%d:%d;",*a0,*a1);*a0+=options[1];*a1+=options[2];
}
boolean (debugcore)(const char * a0,boolean a1){
append("debugcore:%s:%d;",a0,a1);return options[9];
}
void (deltrap)(struct trap * a0){
append("deltrap;");
}
schar (depth)(d_level * a0){
append("depth;");
return options[7];
}
char * (dupstr)(const char * a0){
size_t n=strlen(a0)+1;char*out=malloc(n);memcpy(out,a0,n);return out;
}
char * (eos)(char * a0){
return a0+strlen(a0);
}
void (extract_nobj)(struct obj * a0,struct obj ** a1){
append("extract_nobj:%u;",a0->o_id);if(*a1!=a0)abort();*a1=a0->nobj;a0->nobj=NULL;a0->where=OBJ_FREE;
}
void (flip_level)(int a0,boolean a1){
append("flip_level;");
}
void (freeinv)(struct obj * a0){
append("freeinv:%u;",a0->o_id);if(gi.invent!=a0)abort();gi.invent=a0->nobj;a0->nobj=NULL;a0->where=OBJ_FREE;
}
boolean (get_coord)(lua_State * a0,int a1,lua_Integer * a2,lua_Integer * a3){
append("get_coord;");*a2=3;*a3=4;return !options[8];
}
char * (get_option_value)(const char * a0,boolean a1){
return "fixture value";
}
const char * (get_trapname_bytype)(int a0){
return "fixture trap";
}
void (getlin)(const char * a0,char * a1){
append("getlin:%s;",a0);strcpy(a1,"fixture input");
}
void (impossible)(const char * a0,...){
va_list ap;va_start(ap,a0);message("impossible",a0,ap);va_end(ap);
}
char * (ing_suffix)(const char * a0){
append("ing_suffix:%s;",a0);return (char*)a0;
}
void (init_uhunger)(void){
append("init_uhunger;");
}
int (isok)(coordxy a0,coordxy a1){
return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;
}
int (l_get_config_errors)(lua_State * a0){
append("l_get_config_errors;");
return options[7];
}
int (l_obj_register)(lua_State * a0){
append("l_obj_register;");
return options[7];
}
void (l_register_des)(lua_State * a0){
append("l_register_des;");
}
int (l_selection_register)(lua_State * a0){
append("l_selection_register;");
return options[7];
}
xint16 (level_difficulty)(void){
append("level_difficulty;");
return options[7];
}
const char * (levltyp_to_name)(int a0){
return "fixture terrain";
}
void (livelog_printf)(long a0,const char * a1,...){
va_list ap;va_start(ap,a1);message("livelog_printf",a1,ap);va_end(ap);
}
anything * (long_to_any)(long a0){
fixture_any.a_long=a0;return &fixture_any;
}
char * (makeplural)(const char * a0){
append("makeplural:%s;",a0);return (char*)a0;
}
char * (makesingular)(const char * a0){
append("makesingular:%s;",a0);return (char*)a0;
}
void (mongone)(struct monst * a0){
append("mongone:%u;",a0->m_id);if(fmon==a0)fmon=a0->nmon;
}
void (moveloop_core)(void){
append("moveloop_core;");
}
int (name_to_mon)(const char * a0,int * a1){
return options[6];
}
char * (nh_getenv)(const char * a0){
return getenv(a0);
}
void (nh_snprintf)(const char * func,int line,char * str,size_t size,const char * fmt,...){
va_list ap;va_start(ap,fmt);int n=vsnprintf(str,size,fmt,ap);va_end(ap);
}
int (nhl_abs_coord)(lua_State * a0){
append("nhl_abs_coord;");
return options[7];
}
int (nhl_obj_u_giveobj)(lua_State * a0){
append("nhl_obj_u_giveobj;");
return options[7];
}
void (nhl_push_obj)(lua_State * a0,struct obj * a1){
append("nhl_push_obj;");
}
void (obfree)(struct obj * a0,struct obj * a1){
append("obfree:%u;",a0->o_id);
}
void (panic)(const char * a0,...){
va_list ap;va_start(ap,a0);fatal(a0,ap);va_end(ap);
__builtin_unreachable();
}
void (paniclog)(const char * a0,const char * a1){
append("paniclog:%s:%s;",a0,a1);
}
boolean (parse_conf_str)(const char * str,boolean (*proc)(char *)){
append("parse_conf_str;");
return options[7];
}
boolean (parse_config_line)(char * a0){
append("parse_config_line;");
return options[7];
}
void (pline)(const char * a0,...){
va_list ap;va_start(ap,a0);message("pline",a0,ap);va_end(ap);
}
long * (re_alloc)(long * a0,unsigned int a1){
fixture_allocations++;if(options[30]&&fixture_allocations==options[30]){append("re_alloc_panic:%d:%u;",fixture_allocations,a1);panic("controlled re_alloc OOM");}return (long*)realloc(a0,a1);
}
int (rn2)(int a0){
int n=fixture_rand(a0);append("rn2:%d:%d;",a0,n);return n;
}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){
append("rng:%s:%d:%s;",a0,a1,a2);
}
char * (s_suffix)(const char * a0){
append("s_suffix:%s;",a0);return (char*)a0;
}
int (select_menu)(winid a0,int a1,menu_item ** a2){
append("select_menu:%d:%d;",a0,a1);fixture_picks[0].item.a_char=97;fixture_picks[1].item.a_char=98;*a2=fixture_picks;return options[10];
}
void (setnotworn)(struct obj * a0){
append("setnotworn:%u:%ld;",a0->o_id,a0->owornmask);a0->owornmask=0;
}
void (setworn)(struct obj * a0,long a1){
append("setworn:%u:%ld;",a0->o_id,a1);a0->owornmask=a1;
}
void (sfi_char)(NHFILE * a0,char * a1,const char * a2,int a3){
if(a3>sizeof fixture_saved)abort();memcpy(a1,fixture_saved,a3);append("sfi_char:%s:%d:%s;",a2,a3,a1);
}
void (sfi_unsigned)(NHFILE * a0,unsigned int * a1,const char * a2){
*a1=fixture_saved_length;append("sfi_unsigned:%s:%u;",a2,fixture_saved_length);
}
void (sfo_char)(NHFILE * a0,char * a1,const char * a2,int a3){
if(a3>sizeof fixture_saved)abort();memcpy(fixture_saved,a1,a3);append("sfo_char:%s:%d:%s;",a2,a3,a1);
}
void (sfo_unsigned)(NHFILE * a0,unsigned int * a1,const char * a2){
fixture_saved_length=*a1;append("sfo_unsigned:%s:%u;",a2,fixture_saved_length);
}
void (spot_stop_timers)(coordxy a0,coordxy a1,short a2){
append("spot_stop_timers;");
}
long (spot_time_expires)(coordxy a0,coordxy a1,short a2){
append("spot_time_expires;");
return options[7];
}
boolean (start_timer)(long a0,short a1,short a2,union any * a3){
append("start_timer;");
return options[7];
}
int (strncmpi)(const char * a0,const char * a1,int a2){
return strncasecmp(a0,a1,a2);
}
struct trap * (t_at)(coordxy a0,coordxy a1){
return options[5]?&fixture_trap:NULL;
}
void (update_inventory)(void){
append("update_inventory;");
}
void (useupall)(struct obj * a0){
append("useupall:%u;",a0->o_id);if(gi.invent!=a0)abort();gi.invent=a0->nobj;a0->nobj=NULL;a0->where=OBJ_FREE;
}
void (verbalize)(const char * a0,...){
va_list ap;va_start(ap,a0);message("verbalize",a0,ap);va_end(ap);
}
static winid fixture_create(int n){append("create:%d;",n);return 12;}
static void fixture_destroy(winid w){append("destroy:%d;",w);}
static void fixture_display(winid w,boolean b){append("display:%d:%d;",w,b);}
static void fixture_start(winid w,unsigned long b){append("start:%d:%lu;",w,b);}
static void fixture_end(winid w,const char*s){append("end:%d:%s;",w,s?s:"(null)");}
static void fixture_put(winid w,int attr,const char*s){append("put:%d:%d:%s;",w,attr,s);}
#ifdef HYBRID_NHLUA
#include "../nethack-c/wasm/tu-fragments/nhlua-support.c"
#else
#include "../.cache/wasm64-build/tree/src/nhlua.c"
#endif
typedef nhl_user_data probe_nud;
#ifdef HYBRID_NHLUA
#define SOURCE_CB(name) teleport_nhlua_entry_ ## name
#else
#define SOURCE_CB(name) name
#endif
uintptr_t probe_callback_pointer(int kind){switch(kind){case 0:return (uintptr_t)SOURCE_CB(nhl_level_difficulty);case 1:return (uintptr_t)SOURCE_CB(nhl_alloc);case 2:return (uintptr_t)SOURCE_CB(nhl_hookfn);case 3:return (uintptr_t)SOURCE_CB(nhl_warn);case 4:return (uintptr_t)SOURCE_CB(nhl_panic);default:abort();}}
#undef SOURCE_CB
void *probe_data(int index){switch(index){
case 0:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(0);
#else
return (void*)&nhcore_call_names;
#endif
case 1:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(1);
#else
return (void*)&nhcore_call_available;
#endif
case 2:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(2);
#else
return (void*)&luapat;
#endif
case 3:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(3);
#else
return (void*)&char2typ;
#endif
case 4:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(4);
#else
return (void*)&nhl_functions;
#endif
case 5:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(5);
#else
return (void*)&nhl_consts;
#endif
case 6:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(6);
#else
return (void*)&nhl_u_functions;
#endif
case 7:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(7);
#else
return (void*)&ct_base_base;
#endif
case 8:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(8);
#else
return (void*)&ct_base_error;
#endif
case 9:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(9);
#else
return (void*)&ct_base_meta;
#endif
case 10:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(10);
#else
return (void*)&ct_base_iffy;
#endif
case 11:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(11);
#else
return (void*)&ct_base_unsafe;
#endif
case 12:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(12);
#else
return (void*)&ct_debug_debug;
#endif
case 13:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(13);
#else
return (void*)&ct_debug_safe;
#endif
case 14:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(14);
#else
return (void*)&ct_os_time;
#endif
case 15:
#ifdef HYBRID_NHLUA
return teleport_nhlua_storage(15);
#else
return (void*)&ct_os_files;
#endif
default:abort();}}
const char*probe_function_name(uintptr_t pointer){if(!pointer)return NULL;
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&l_get_config_errors)return "l_get_config_errors";
#else
if(pointer==(uintptr_t)&l_get_config_errors)return "l_get_config_errors";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_base)return "luaopen_base";
#else
if(pointer==(uintptr_t)&luaopen_base)return "luaopen_base";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_coroutine)return "luaopen_coroutine";
#else
if(pointer==(uintptr_t)&luaopen_coroutine)return "luaopen_coroutine";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_debug)return "luaopen_debug";
#else
if(pointer==(uintptr_t)&luaopen_debug)return "luaopen_debug";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_math)return "luaopen_math";
#else
if(pointer==(uintptr_t)&luaopen_math)return "luaopen_math";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_os)return "luaopen_os";
#else
if(pointer==(uintptr_t)&luaopen_os)return "luaopen_os";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_string)return "luaopen_string";
#else
if(pointer==(uintptr_t)&luaopen_string)return "luaopen_string";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_table)return "luaopen_table";
#else
if(pointer==(uintptr_t)&luaopen_table)return "luaopen_table";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&luaopen_utf8)return "luaopen_utf8";
#else
if(pointer==(uintptr_t)&luaopen_utf8)return "luaopen_utf8";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&nhl_abs_coord)return "nhl_abs_coord";
#else
if(pointer==(uintptr_t)&nhl_abs_coord)return "nhl_abs_coord";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_alloc)return "nhl_alloc";
#else
if(pointer==(uintptr_t)&nhl_alloc)return "nhl_alloc";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_an)return "nhl_an";
#else
if(pointer==(uintptr_t)&nhl_an)return "nhl_an";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_callback)return "nhl_callback";
#else
if(pointer==(uintptr_t)&nhl_callback)return "nhl_callback";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_debug_flags)return "nhl_debug_flags";
#else
if(pointer==(uintptr_t)&nhl_debug_flags)return "nhl_debug_flags";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_deltrap)return "nhl_deltrap";
#else
if(pointer==(uintptr_t)&nhl_deltrap)return "nhl_deltrap";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_dnum_name)return "nhl_dnum_name";
#else
if(pointer==(uintptr_t)&nhl_dnum_name)return "nhl_dnum_name";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_doturn)return "nhl_doturn";
#else
if(pointer==(uintptr_t)&nhl_doturn)return "nhl_doturn";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_flip_level)return "nhl_flip_level";
#else
if(pointer==(uintptr_t)&nhl_flip_level)return "nhl_flip_level";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_gamestate)return "nhl_gamestate";
#else
if(pointer==(uintptr_t)&nhl_gamestate)return "nhl_gamestate";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_get_cmd_key)return "nhl_get_cmd_key";
#else
if(pointer==(uintptr_t)&nhl_get_cmd_key)return "nhl_get_cmd_key";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_get_config)return "nhl_get_config";
#else
if(pointer==(uintptr_t)&nhl_get_config)return "nhl_get_config";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_get_debug_themerm_name)return "nhl_get_debug_themerm_name";
#else
if(pointer==(uintptr_t)&nhl_get_debug_themerm_name)return "nhl_get_debug_themerm_name";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_getlin)return "nhl_getlin";
#else
if(pointer==(uintptr_t)&nhl_getlin)return "nhl_getlin";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_getmap)return "nhl_getmap";
#else
if(pointer==(uintptr_t)&nhl_getmap)return "nhl_getmap";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_gettrap)return "nhl_gettrap";
#else
if(pointer==(uintptr_t)&nhl_gettrap)return "nhl_gettrap";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_hookfn)return "nhl_hookfn";
#else
if(pointer==(uintptr_t)&nhl_hookfn)return "nhl_hookfn";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_impossible)return "nhl_impossible";
#else
if(pointer==(uintptr_t)&nhl_impossible)return "nhl_impossible";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_ing_suffix)return "nhl_ing_suffix";
#else
if(pointer==(uintptr_t)&nhl_ing_suffix)return "nhl_ing_suffix";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_int_to_obj_name)return "nhl_int_to_obj_name";
#else
if(pointer==(uintptr_t)&nhl_int_to_obj_name)return "nhl_int_to_obj_name";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_int_to_pm_name)return "nhl_int_to_pm_name";
#else
if(pointer==(uintptr_t)&nhl_int_to_pm_name)return "nhl_int_to_pm_name";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_is_genocided)return "nhl_is_genocided";
#else
if(pointer==(uintptr_t)&nhl_is_genocided)return "nhl_is_genocided";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_level_difficulty)return "nhl_level_difficulty";
#else
if(pointer==(uintptr_t)&nhl_level_difficulty)return "nhl_level_difficulty";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_makeplural)return "nhl_makeplural";
#else
if(pointer==(uintptr_t)&nhl_makeplural)return "nhl_makeplural";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_makesingular)return "nhl_makesingular";
#else
if(pointer==(uintptr_t)&nhl_makesingular)return "nhl_makesingular";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_menu)return "nhl_menu";
#else
if(pointer==(uintptr_t)&nhl_menu)return "nhl_menu";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_meta_u_index)return "nhl_meta_u_index";
#else
if(pointer==(uintptr_t)&nhl_meta_u_index)return "nhl_meta_u_index";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_meta_u_newindex)return "nhl_meta_u_newindex";
#else
if(pointer==(uintptr_t)&nhl_meta_u_newindex)return "nhl_meta_u_newindex";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_panic)return "nhl_panic";
#else
if(pointer==(uintptr_t)&nhl_panic)return "nhl_panic";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_parse_config)return "nhl_parse_config";
#else
if(pointer==(uintptr_t)&nhl_parse_config)return "nhl_parse_config";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_pline)return "nhl_pline";
#else
if(pointer==(uintptr_t)&nhl_pline)return "nhl_pline";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_pushkey)return "nhl_pushkey";
#else
if(pointer==(uintptr_t)&nhl_pushkey)return "nhl_pushkey";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_random)return "nhl_random";
#else
if(pointer==(uintptr_t)&nhl_random)return "nhl_random";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_rn2)return "nhl_rn2";
#else
if(pointer==(uintptr_t)&nhl_rn2)return "nhl_rn2";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_s_suffix)return "nhl_s_suffix";
#else
if(pointer==(uintptr_t)&nhl_s_suffix)return "nhl_s_suffix";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_stairways)return "nhl_stairways";
#else
if(pointer==(uintptr_t)&nhl_stairways)return "nhl_stairways";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_test)return "nhl_test";
#else
if(pointer==(uintptr_t)&nhl_test)return "nhl_test";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_text)return "nhl_text";
#else
if(pointer==(uintptr_t)&nhl_text)return "nhl_text";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_timer_has_at)return "nhl_timer_has_at";
#else
if(pointer==(uintptr_t)&nhl_timer_has_at)return "nhl_timer_has_at";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_timer_peek_at)return "nhl_timer_peek_at";
#else
if(pointer==(uintptr_t)&nhl_timer_peek_at)return "nhl_timer_peek_at";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_timer_start_at)return "nhl_timer_start_at";
#else
if(pointer==(uintptr_t)&nhl_timer_start_at)return "nhl_timer_start_at";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_timer_stop_at)return "nhl_timer_stop_at";
#else
if(pointer==(uintptr_t)&nhl_timer_stop_at)return "nhl_timer_stop_at";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_u_clear_inventory)return "nhl_u_clear_inventory";
#else
if(pointer==(uintptr_t)&nhl_u_clear_inventory)return "nhl_u_clear_inventory";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_u_giveobj)return "nhl_u_giveobj";
#else
if(pointer==(uintptr_t)&nhl_u_giveobj)return "nhl_u_giveobj";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_variable)return "nhl_variable";
#else
if(pointer==(uintptr_t)&nhl_variable)return "nhl_variable";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_verbalize)return "nhl_verbalize";
#else
if(pointer==(uintptr_t)&nhl_verbalize)return "nhl_verbalize";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_nhl_warn)return "nhl_warn";
#else
if(pointer==(uintptr_t)&nhl_warn)return "nhl_warn";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&parse_config_line)return "parse_config_line";
#else
if(pointer==(uintptr_t)&parse_config_line)return "parse_config_line";
#endif
#ifdef HYBRID_NHLUA
if(pointer==(uintptr_t)&teleport_nhlua_entry_traceback_handler)return "traceback_handler";
#else
if(pointer==(uintptr_t)&traceback_handler)return "traceback_handler";
#endif
abort();}
#ifdef HYBRID_NHLUA
void probe_call_l_nhcore_init(void){teleport_nhlua_entry_l_nhcore_init();}
#else
void probe_call_l_nhcore_init(void){l_nhcore_init();}
#endif
#ifdef HYBRID_NHLUA
void probe_call_l_nhcore_done(void){teleport_nhlua_entry_l_nhcore_done();}
#else
void probe_call_l_nhcore_done(void){l_nhcore_done();}
#endif
#ifdef HYBRID_NHLUA
void probe_call_l_nhcore_call(int callidx){teleport_nhlua_entry_l_nhcore_call(callidx);}
#else
void probe_call_l_nhcore_call(int callidx){l_nhcore_call(callidx);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_error(lua_State * L,const char * msg){teleport_nhlua_entry_nhl_error(L,msg);}
#else
void probe_call_nhl_error(lua_State * L,const char * msg){nhl_error(L,msg);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_lcheck_param_table(lua_State * L){teleport_nhlua_entry_lcheck_param_table(L);}
#else
void probe_call_lcheck_param_table(lua_State * L){lcheck_param_table(L);}
#endif
#ifdef HYBRID_NHLUA
schar probe_call_get_table_mapchr(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_mapchr(L,name);}
#else
schar probe_call_get_table_mapchr(lua_State * L,const char * name){return get_table_mapchr(L,name);}
#endif
#ifdef HYBRID_NHLUA
schar probe_call_get_table_mapchr_opt(lua_State * L,const char * name,schar defval){return teleport_nhlua_entry_get_table_mapchr_opt(L,name,defval);}
#else
schar probe_call_get_table_mapchr_opt(lua_State * L,const char * name,schar defval){return get_table_mapchr_opt(L,name,defval);}
#endif
#ifdef HYBRID_NHLUA
short probe_call_nhl_get_timertype(lua_State * L,int idx){return teleport_nhlua_entry_nhl_get_timertype(L,idx);}
#else
short probe_call_nhl_get_timertype(lua_State * L,int idx){return nhl_get_timertype(L,idx);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_add_table_entry_int(lua_State * L,const char * name,lua_Integer value){teleport_nhlua_entry_nhl_add_table_entry_int(L,name,value);}
#else
void probe_call_nhl_add_table_entry_int(lua_State * L,const char * name,lua_Integer value){nhl_add_table_entry_int(L,name,value);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_add_table_entry_char(lua_State * L,const char * name,char value){teleport_nhlua_entry_nhl_add_table_entry_char(L,name,value);}
#else
void probe_call_nhl_add_table_entry_char(lua_State * L,const char * name,char value){nhl_add_table_entry_char(L,name,value);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_add_table_entry_str(lua_State * L,const char * name,const char * value){teleport_nhlua_entry_nhl_add_table_entry_str(L,name,value);}
#else
void probe_call_nhl_add_table_entry_str(lua_State * L,const char * name,const char * value){nhl_add_table_entry_str(L,name,value);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_add_table_entry_bool(lua_State * L,const char * name,boolean value){teleport_nhlua_entry_nhl_add_table_entry_bool(L,name,value);}
#else
void probe_call_nhl_add_table_entry_bool(lua_State * L,const char * name,boolean value){nhl_add_table_entry_bool(L,name,value);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_add_table_entry_region(lua_State * L,const char * name,coordxy x1,coordxy y1,coordxy x2,coordxy y2){teleport_nhlua_entry_nhl_add_table_entry_region(L,name,x1,y1,x2,y2);}
#else
void probe_call_nhl_add_table_entry_region(lua_State * L,const char * name,coordxy x1,coordxy y1,coordxy x2,coordxy y2){nhl_add_table_entry_region(L,name,x1,y1,x2,y2);}
#endif
#ifdef HYBRID_NHLUA
schar probe_call_splev_chr2typ(char c){return teleport_nhlua_entry_splev_chr2typ(c);}
#else
schar probe_call_splev_chr2typ(char c){return splev_chr2typ(c);}
#endif
#ifdef HYBRID_NHLUA
schar probe_call_check_mapchr(const char * s){return teleport_nhlua_entry_check_mapchr(s);}
#else
schar probe_call_check_mapchr(const char * s){return check_mapchr(s);}
#endif
#ifdef HYBRID_NHLUA
char probe_call_splev_typ2chr(schar typ){return teleport_nhlua_entry_splev_typ2chr(typ);}
#else
char probe_call_splev_typ2chr(schar typ){return splev_typ2chr(typ);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_gettrap(lua_State * L){return teleport_nhlua_entry_nhl_gettrap(L);}
#else
int probe_call_nhl_gettrap(lua_State * L){return nhl_gettrap(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_deltrap(lua_State * L){return teleport_nhlua_entry_nhl_deltrap(L);}
#else
int probe_call_nhl_deltrap(lua_State * L){return nhl_deltrap(L);}
#endif
#ifdef HYBRID_NHLUA
boolean probe_call_nhl_get_xy_params(lua_State * L,lua_Integer * x,lua_Integer * y){return teleport_nhlua_entry_nhl_get_xy_params(L,x,y);}
#else
boolean probe_call_nhl_get_xy_params(lua_State * L,lua_Integer * x,lua_Integer * y){return nhl_get_xy_params(L,x,y);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_getmap(lua_State * L){return teleport_nhlua_entry_nhl_getmap(L);}
#else
int probe_call_nhl_getmap(lua_State * L){return nhl_getmap(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_impossible(lua_State * L){return teleport_nhlua_entry_nhl_impossible(L);}
#else
int probe_call_nhl_impossible(lua_State * L){return nhl_impossible(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_pline(lua_State * L){return teleport_nhlua_entry_nhl_pline(L);}
#else
int probe_call_nhl_pline(lua_State * L){return nhl_pline(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_verbalize(lua_State * L){return teleport_nhlua_entry_nhl_verbalize(L);}
#else
int probe_call_nhl_verbalize(lua_State * L){return nhl_verbalize(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_parse_config(lua_State * L){return teleport_nhlua_entry_nhl_parse_config(L);}
#else
int probe_call_nhl_parse_config(lua_State * L){return nhl_parse_config(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_get_config(lua_State * L){return teleport_nhlua_entry_nhl_get_config(L);}
#else
int probe_call_nhl_get_config(lua_State * L){return nhl_get_config(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_getlin(lua_State * L){return teleport_nhlua_entry_nhl_getlin(L);}
#else
int probe_call_nhl_getlin(lua_State * L){return nhl_getlin(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_menu(lua_State * L){return teleport_nhlua_entry_nhl_menu(L);}
#else
int probe_call_nhl_menu(lua_State * L){return nhl_menu(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_text(lua_State * L){return teleport_nhlua_entry_nhl_text(L);}
#else
int probe_call_nhl_text(lua_State * L){return nhl_text(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_makeplural(lua_State * L){return teleport_nhlua_entry_nhl_makeplural(L);}
#else
int probe_call_nhl_makeplural(lua_State * L){return nhl_makeplural(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_makesingular(lua_State * L){return teleport_nhlua_entry_nhl_makesingular(L);}
#else
int probe_call_nhl_makesingular(lua_State * L){return nhl_makesingular(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_s_suffix(lua_State * L){return teleport_nhlua_entry_nhl_s_suffix(L);}
#else
int probe_call_nhl_s_suffix(lua_State * L){return nhl_s_suffix(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_ing_suffix(lua_State * L){return teleport_nhlua_entry_nhl_ing_suffix(L);}
#else
int probe_call_nhl_ing_suffix(lua_State * L){return nhl_ing_suffix(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_an(lua_State * L){return teleport_nhlua_entry_nhl_an(L);}
#else
int probe_call_nhl_an(lua_State * L){return nhl_an(L);}
#endif
#ifdef HYBRID_NHLUA
boolean probe_call_nhl_lua_rnglog_ctx_enabled(void){return teleport_nhlua_entry_nhl_lua_rnglog_ctx_enabled();}
#else
boolean probe_call_nhl_lua_rnglog_ctx_enabled(void){return nhl_lua_rnglog_ctx_enabled();}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_rnglog_set_lua_caller(lua_State * L,const char * fallback){teleport_nhlua_entry_nhl_rnglog_set_lua_caller(L,fallback);}
#else
void probe_call_nhl_rnglog_set_lua_caller(lua_State * L,const char * fallback){nhl_rnglog_set_lua_caller(L,fallback);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_rn2(lua_State * L){return teleport_nhlua_entry_nhl_rn2(L);}
#else
int probe_call_nhl_rn2(lua_State * L){return nhl_rn2(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_random(lua_State * L){return teleport_nhlua_entry_nhl_random(L);}
#else
int probe_call_nhl_random(lua_State * L){return nhl_random(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_level_difficulty(lua_State * L){return teleport_nhlua_entry_nhl_level_difficulty(L);}
#else
int probe_call_nhl_level_difficulty(lua_State * L){return nhl_level_difficulty(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_is_genocided(lua_State * L){return teleport_nhlua_entry_nhl_is_genocided(L);}
#else
int probe_call_nhl_is_genocided(lua_State * L){return nhl_is_genocided(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_get_debug_themerm_name(lua_State * L){return teleport_nhlua_entry_nhl_get_debug_themerm_name(L);}
#else
int probe_call_nhl_get_debug_themerm_name(lua_State * L){return nhl_get_debug_themerm_name(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_get_table_int(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_int(L,name);}
#else
int probe_call_get_table_int(lua_State * L,const char * name){return get_table_int(L,name);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_get_table_int_opt(lua_State * L,const char * name,int defval){return teleport_nhlua_entry_get_table_int_opt(L,name,defval);}
#else
int probe_call_get_table_int_opt(lua_State * L,const char * name,int defval){return get_table_int_opt(L,name,defval);}
#endif
#ifdef HYBRID_NHLUA
char * probe_call_get_table_str(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_str(L,name);}
#else
char * probe_call_get_table_str(lua_State * L,const char * name){return get_table_str(L,name);}
#endif
#ifdef HYBRID_NHLUA
char * probe_call_get_table_str_opt(lua_State * L,const char * name,char * defval){return teleport_nhlua_entry_get_table_str_opt(L,name,defval);}
#else
char * probe_call_get_table_str_opt(lua_State * L,const char * name,char * defval){return get_table_str_opt(L,name,defval);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_get_table_boolean(lua_State * L,const char * name){return teleport_nhlua_entry_get_table_boolean(L,name);}
#else
int probe_call_get_table_boolean(lua_State * L,const char * name){return get_table_boolean(L,name);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_get_table_boolean_opt(lua_State * L,const char * name,int defval){return teleport_nhlua_entry_get_table_boolean_opt(L,name,defval);}
#else
int probe_call_get_table_boolean_opt(lua_State * L,const char * name,int defval){return get_table_boolean_opt(L,name,defval);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_get_table_option(lua_State * L,const char * name,const char * defval,const char *const * opts){return teleport_nhlua_entry_get_table_option(L,name,defval,opts);}
#else
int probe_call_get_table_option(lua_State * L,const char * name,const char * defval,const char *const * opts){return get_table_option(L,name,defval,opts);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_dnum_name(lua_State * L){return teleport_nhlua_entry_nhl_dnum_name(L);}
#else
int probe_call_nhl_dnum_name(lua_State * L){return nhl_dnum_name(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_int_to_pm_name(lua_State * L){return teleport_nhlua_entry_nhl_int_to_pm_name(L);}
#else
int probe_call_nhl_int_to_pm_name(lua_State * L){return nhl_int_to_pm_name(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_int_to_obj_name(lua_State * L){return teleport_nhlua_entry_nhl_int_to_obj_name(L);}
#else
int probe_call_nhl_int_to_obj_name(lua_State * L){return nhl_int_to_obj_name(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_variable(lua_State * L){return teleport_nhlua_entry_nhl_variable(L);}
#else
int probe_call_nhl_variable(lua_State * L){return nhl_variable(L);}
#endif
#ifdef HYBRID_NHLUA
char * probe_call_get_nh_lua_variables(void){return teleport_nhlua_entry_get_nh_lua_variables();}
#else
char * probe_call_get_nh_lua_variables(void){return get_nh_lua_variables();}
#endif
#ifdef HYBRID_NHLUA
void probe_call_save_luadata(NHFILE * nhfp){teleport_nhlua_entry_save_luadata(nhfp);}
#else
void probe_call_save_luadata(NHFILE * nhfp){save_luadata(nhfp);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_restore_luadata(NHFILE * nhfp){teleport_nhlua_entry_restore_luadata(nhfp);}
#else
void probe_call_restore_luadata(NHFILE * nhfp){restore_luadata(nhfp);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_stairways(lua_State * L){return teleport_nhlua_entry_nhl_stairways(L);}
#else
int probe_call_nhl_stairways(lua_State * L){return nhl_stairways(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_test(lua_State * L){return teleport_nhlua_entry_nhl_test(L);}
#else
int probe_call_nhl_test(lua_State * L){return nhl_test(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_pushkey(lua_State * L){return teleport_nhlua_entry_nhl_pushkey(L);}
#else
int probe_call_nhl_pushkey(lua_State * L){return nhl_pushkey(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_doturn(lua_State * L){return teleport_nhlua_entry_nhl_doturn(L);}
#else
int probe_call_nhl_doturn(lua_State * L){return nhl_doturn(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_debug_flags(lua_State * L){return teleport_nhlua_entry_nhl_debug_flags(L);}
#else
int probe_call_nhl_debug_flags(lua_State * L){return nhl_debug_flags(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_flip_level(lua_State * L){return teleport_nhlua_entry_nhl_flip_level(L);}
#else
int probe_call_nhl_flip_level(lua_State * L){return nhl_flip_level(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_timer_has_at(lua_State * L){return teleport_nhlua_entry_nhl_timer_has_at(L);}
#else
int probe_call_nhl_timer_has_at(lua_State * L){return nhl_timer_has_at(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_timer_peek_at(lua_State * L){return teleport_nhlua_entry_nhl_timer_peek_at(L);}
#else
int probe_call_nhl_timer_peek_at(lua_State * L){return nhl_timer_peek_at(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_timer_stop_at(lua_State * L){return teleport_nhlua_entry_nhl_timer_stop_at(L);}
#else
int probe_call_nhl_timer_stop_at(lua_State * L){return nhl_timer_stop_at(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_timer_start_at(lua_State * L){return teleport_nhlua_entry_nhl_timer_start_at(L);}
#else
int probe_call_nhl_timer_start_at(lua_State * L){return nhl_timer_start_at(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_get_cmd_key(lua_State * L){return teleport_nhlua_entry_nhl_get_cmd_key(L);}
#else
int probe_call_nhl_get_cmd_key(lua_State * L){return nhl_get_cmd_key(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_callback(lua_State * L){return teleport_nhlua_entry_nhl_callback(L);}
#else
int probe_call_nhl_callback(lua_State * L){return nhl_callback(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_gamestate(lua_State * L){return teleport_nhlua_entry_nhl_gamestate(L);}
#else
int probe_call_nhl_gamestate(lua_State * L){return nhl_gamestate(L);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_free_tutorial(void){teleport_nhlua_entry_free_tutorial();}
#else
void probe_call_free_tutorial(void){free_tutorial();}
#endif
#ifdef HYBRID_NHLUA
void probe_call_tutorial(boolean entering){teleport_nhlua_entry_tutorial(entering);}
#else
void probe_call_tutorial(boolean entering){tutorial(entering);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_init_nhc_data(lua_State * L){teleport_nhlua_entry_init_nhc_data(L);}
#else
void probe_call_init_nhc_data(lua_State * L){init_nhc_data(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_push_anything(lua_State * L,int anytype,void * src){return teleport_nhlua_entry_nhl_push_anything(L,anytype,src);}
#else
int probe_call_nhl_push_anything(lua_State * L,int anytype,void * src){return nhl_push_anything(L,anytype,src);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_meta_u_index(lua_State * L){return teleport_nhlua_entry_nhl_meta_u_index(L);}
#else
int probe_call_nhl_meta_u_index(lua_State * L){return nhl_meta_u_index(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_meta_u_newindex(lua_State * L){return teleport_nhlua_entry_nhl_meta_u_newindex(L);}
#else
int probe_call_nhl_meta_u_newindex(lua_State * L){return nhl_meta_u_newindex(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_u_clear_inventory(lua_State * L){return teleport_nhlua_entry_nhl_u_clear_inventory(L);}
#else
int probe_call_nhl_u_clear_inventory(lua_State * L){return nhl_u_clear_inventory(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_u_giveobj(lua_State * L){return teleport_nhlua_entry_nhl_u_giveobj(L);}
#else
int probe_call_nhl_u_giveobj(lua_State * L){return nhl_u_giveobj(L);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_init_u_data(lua_State * L){teleport_nhlua_entry_init_u_data(L);}
#else
void probe_call_init_u_data(lua_State * L){init_u_data(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_traceback_handler(lua_State * L){return teleport_nhlua_entry_traceback_handler(L);}
#else
int probe_call_traceback_handler(lua_State * L){return traceback_handler(L);}
#endif
#ifdef HYBRID_NHLUA
uint32_t probe_call_nhl_getmeminuse(lua_State * L){return teleport_nhlua_entry_nhl_getmeminuse(L);}
#else
uint32_t probe_call_nhl_getmeminuse(lua_State * L){return nhl_getmeminuse(L);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_pcall(lua_State * L,int nargs,int nresults,const char * name){return teleport_nhlua_entry_nhl_pcall(L,nargs,nresults,name);}
#else
int probe_call_nhl_pcall(lua_State * L,int nargs,int nresults,const char * name){return nhl_pcall(L,nargs,nresults,name);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_pcall_handle(lua_State * L,int nargs,int nresults,const char * name,NHL_pcall_action npa){return teleport_nhlua_entry_nhl_pcall_handle(L,nargs,nresults,name,npa);}
#else
int probe_call_nhl_pcall_handle(lua_State * L,int nargs,int nresults,const char * name,NHL_pcall_action npa){return nhl_pcall_handle(L,nargs,nresults,name,npa);}
#endif
#ifdef HYBRID_NHLUA
boolean probe_call_nhl_loadlua(lua_State * L,const char * fname){return teleport_nhlua_entry_nhl_loadlua(L,fname);}
#else
boolean probe_call_nhl_loadlua(lua_State * L,const char * fname){return nhl_loadlua(L,fname);}
#endif
#ifdef HYBRID_NHLUA
lua_State * probe_call_nhl_init(nhl_sandbox_info * sbi){return teleport_nhlua_entry_nhl_init(sbi);}
#else
lua_State * probe_call_nhl_init(nhl_sandbox_info * sbi){return nhl_init(sbi);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_done(lua_State * L){teleport_nhlua_entry_nhl_done(L);}
#else
void probe_call_nhl_done(lua_State * L){nhl_done(L);}
#endif
#ifdef HYBRID_NHLUA
boolean probe_call_load_lua(const char * name,nhl_sandbox_info * sbi){return teleport_nhlua_entry_load_lua(name,sbi);}
#else
boolean probe_call_load_lua(const char * name,nhl_sandbox_info * sbi){return load_lua(name,sbi);}
#endif
#ifdef HYBRID_NHLUA
const char * probe_call_get_lua_version(void){return teleport_nhlua_entry_get_lua_version();}
#else
const char * probe_call_get_lua_version(void){return get_lua_version();}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_clearfromtable(lua_State * L,int flag,int tndx,struct e * todo){teleport_nhlua_entry_nhl_clearfromtable(L,flag,tndx,todo);}
#else
void probe_call_nhl_clearfromtable(lua_State * L,int flag,int tndx,struct e * todo){nhl_clearfromtable(L,flag,tndx,todo);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_end_luapat(void){teleport_nhlua_entry_end_luapat();}
#else
void probe_call_end_luapat(void){end_luapat();}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_pushhooked_open_table(lua_State * L){teleport_nhlua_entry_nhl_pushhooked_open_table(L);}
#else
void probe_call_nhl_pushhooked_open_table(lua_State * L){nhl_pushhooked_open_table(L);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhlL_openlibs(lua_State * L,uint32_t lflags){teleport_nhlua_entry_nhlL_openlibs(L,lflags);}
#else
void probe_call_nhlL_openlibs(lua_State * L,uint32_t lflags){nhlL_openlibs(L,lflags);}
#endif
#ifdef HYBRID_NHLUA
void * probe_call_nhl_alloc(void * ud,void * ptr,size_t osize,size_t nsize){return teleport_nhlua_entry_nhl_alloc(ud,ptr,osize,nsize);}
#else
void * probe_call_nhl_alloc(void * ud,void * ptr,size_t osize,size_t nsize){return nhl_alloc(ud,ptr,osize,nsize);}
#endif
#ifdef HYBRID_NHLUA
int probe_call_nhl_panic(lua_State * L){return teleport_nhlua_entry_nhl_panic(L);}
#else
int probe_call_nhl_panic(lua_State * L){return nhl_panic(L);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_warn(void * userdata,const char * msg_fragment,int to_be_continued){teleport_nhlua_entry_nhl_warn(userdata,msg_fragment,to_be_continued);}
#else
void probe_call_nhl_warn(void * userdata,const char * msg_fragment,int to_be_continued){nhl_warn(userdata,msg_fragment,to_be_continued);}
#endif
#ifdef HYBRID_NHLUA
void probe_call_nhl_hookfn(lua_State * L,lua_Debug * ar){teleport_nhlua_entry_nhl_hookfn(L,ar);}
#else
void probe_call_nhl_hookfn(lua_State * L,lua_Debug * ar){nhl_hookfn(L,ar);}
#endif
#ifdef HYBRID_NHLUA
lua_State * probe_call_nhlL_newstate(nhl_sandbox_info * sbi,const char * name){return teleport_nhlua_entry_nhlL_newstate(sbi,name);}
#else
lua_State * probe_call_nhlL_newstate(nhl_sandbox_info * sbi,const char * name){return nhlL_newstate(sbi,name);}
#endif
const char *probe_trace(void){return tracebuf;}
void probe_clear_trace(void){tracebuf[0]=0;tracepos=0;}
void probe_option(int i,int value){options[i]=value;if(i==21)reentered=0;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
void *probe_alloc(size_t n){return calloc(1,n);}
void probe_free(void*p){free(p);}
lua_State *probe_lua(void){return luaL_newstate();}
int probe_lua_load(lua_State *L,const char*s){return luaL_loadbuffer(L,s,strlen(s),"=(nhlua-fixture)");}
int probe_lua_run(lua_State *L,int n){return lua_pcall(L,n,LUA_MULTRET,0);}
const char *probe_lua_text(lua_State*L,int i){return lua_tostring(L,i);}
lua_Integer probe_lua_integer(lua_State*L,int i){return lua_tointeger(L,i);}
int probe_lua_type(lua_State*L,int i){return lua_type(L,i);}
int probe_lua_top(lua_State*L){return lua_gettop(L);}
void probe_lua_settop(lua_State*L,int n){lua_settop(L,n);}
void probe_lua_string(lua_State*L,const char*s){lua_pushstring(L,s);}
void probe_lua_integer_push(lua_State*L,lua_Integer n){lua_pushinteger(L,n);}
void probe_lua_boolean(lua_State*L,int n){lua_pushboolean(L,n);}
void probe_lua_table(lua_State*L){lua_newtable(L);}
void probe_lua_field(lua_State*L,int i,const char*s){lua_getfield(L,i,s);}
void probe_lua_global(lua_State*L,const char*s){lua_getglobal(L,s);}
void probe_lua_close(lua_State*L){lua_close(L);}
void probe_setup(void){setenv("NETHACK_LUA_RNGLOG_CTX","1",1);windowprocs.win_create_nhwindow=fixture_create;windowprocs.win_destroy_nhwindow=fixture_destroy;windowprocs.win_display_nhwindow=fixture_display;windowprocs.win_start_menu=fixture_start;windowprocs.win_end_menu=fixture_end;windowprocs.win_putstr=fixture_put;u.ux=0x3215;u.uy=0x1243;u.dx=-257;u.dy=183;u.dz=-2;u.tx=0x1457;u.ty=0x2468;u.ulevel=17;u.ulevelmax=19;u.uhunger=701;u.nv_range=11;u.xray_range=13;u.umonster=23;u.umonnum=29;u.mh=31;u.mhmax=37;u.mtimedone=41;u.uz.dnum=0x1243;u.uz.dlevel=0x2345;u.uluck=-7;u.uhp=43;u.uhpmax=47;u.uen=53;u.uenmax=59;u.uhave.amulet=1;svm.moves=987;strcpy(svd.dungeons[0].dname,"Fixture Dungeon");svn.n_dgns=1;gu.urole.name.m="FixtureRole";}
void probe_core(lua_State*L){gl.luacore=L;}
lua_State*probe_core_state(void){return gl.luacore;}
int probe_lua_boolean_value(lua_State*L,int i){return lua_toboolean(L,i);}
double probe_lua_number(lua_State*L,int i){return lua_tonumber(L,i);}
int probe_lua_isinteger(lua_State*L,int i){return lua_isinteger(L,i);}
void probe_loglua(int n){gl.loglua=n;}
void*probe_userdata(lua_State*L){void*ud;lua_getallocf(L,&ud);return ud;}
void probe_nudfield(lua_State*L,int key,uint32_t value){probe_nud*ud;lua_getallocf(L,(void**)&ud);switch(key){case 0:ud->statctr=value;break;case 1:ud->steps=value;break;case 2:ud->osteps=value;break;case 3:ud->perpcall=value;break;case 4:ud->memlimit=value;break;default:abort();}}
void probe_chains(int kind){if(kind==0){for(int i=0;i<3;i++){fixture_inventory[i].o_id=100+i;fixture_inventory[i].quan=i+1;fixture_inventory[i].where=OBJ_INVENT;fixture_inventory[i].owornmask=i==0?W_ARM:0;fixture_inventory[i].nobj=i<2?&fixture_inventory[i+1]:NULL;}gi.invent=fixture_inventory;}else if(kind==1){for(int i=0;i<3;i++){fixture_monsters[i].m_id=200+i;fixture_monsters[i].mhp=i==1?0:7;fixture_monsters[i].nmon=i<2?&fixture_monsters[i+1]:NULL;}fmon=fixture_monsters;}else{for(int i=0;i<2;i++){fixture_stairs[i].sx=13+i;fixture_stairs[i].sy=14+i;fixture_stairs[i].up=i;fixture_stairs[i].isladder=!i;fixture_stairs[i].tolev.dnum=i+2;fixture_stairs[i].tolev.dlevel=i+3;fixture_stairs[i].next=i==0?&fixture_stairs[1]:NULL;}gs.stairs=fixture_stairs;}}
const char*probe_snapshot(void){static char out[2048];char*at=out;at+=sprintf(at,"u:%d:%d:%d:%d:%d:%ld;store:%d;invent:",u.ux,u.uy,u.uz.dnum,u.uz.dlevel,u.uhunger,svm.moves,gg.gmst_stored);for(struct obj*o=gi.invent;o;o=o->nobj)at+=sprintf(at,"%u:%d:%ld,",o->o_id,o->where,o->owornmask);at+=sprintf(at,";saved:");for(struct obj*o=gg.gmst_invent;o;o=o->nobj)at+=sprintf(at,"%u:%d:%ld,",o->o_id,o->where,o->owornmask);return out;}
void probe_mutate(void){u.ux=41;u.uy=17;u.uz.dnum=7;u.uz.dlevel=9;u.uhunger=123;svm.moves=4321;}
void probe_world(int type,int flags,int traptype){svl.level.locations[3][4].typ=type;svl.level.locations[3][4].flags=flags;fixture_trap.ttyp=traptype;fixture_trap.tx=3;fixture_trap.ty=4;fixture_trap.tseen=1;fixture_trap.madeby_u=1;fixture_trap.once=1;fixture_trap.launch.x=17;fixture_trap.launch.y=18;fixture_trap.launch2.x=19;fixture_trap.launch2.y=20;}
void probe_grow(void){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();}
