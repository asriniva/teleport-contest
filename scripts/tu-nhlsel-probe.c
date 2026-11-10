/* Controlled world fixture; actual Lua/selection/mapfragment/nhlua helpers link. */
#include "hack.h"
#include "sp_lev.h"
#include <stdarg.h>
#include <stdint.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(cg) cg={0};__typeof__(gc) gc;__typeof__(gx) gx;__typeof__(gy) gy;__typeof__(svn) svn;__typeof__(svr) svr;__typeof__(svl) svl;__typeof__(gl) gl;
static struct sp_coder coder;
static lua_State *state;
static unsigned random_state;
static int random_index,options[8];
static char trace_storage[262144],snapshot_storage[262144],input_storage[32768],caller[128];
static void *grown;
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace_storage+strlen(trace_storage),sizeof trace_storage-strlen(trace_storage),fmt,ap);va_end(ap);}
static void snap(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(snapshot_storage+strlen(snapshot_storage),sizeof snapshot_storage-strlen(snapshot_storage),fmt,ap);va_end(ap);}
void panic(const char *fmt,...){abort();}
void impossible(const char *fmt,...){char b[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void newsym_force(coordxy x,coordxy y){append("newsym:%d,%d;",x,y);}
void livelog_printf(long t,const char *fmt,...){append("livelog:%lld;",(long long)t);}
boolean rng_log_enabled(void){return TRUE;}
void rng_log_set_caller(const char *file,int line,const char *name){const char *s=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",s?s+1:file,line,name);}
int (rn2)(int n){int out;if(n<=0)abort();random_state=random_state*1664525U+1013904223U;out=(random_state>>8)%(unsigned)n;random_index++;append("rn2:%d=%d@%s;",n,out,caller);return out;}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
void __wrap_get_location_coord(coordxy *x,coordxy *y,int mode,struct mkroom *room,long packed){append("location:%d,%d:%d:%d:%lld;",*x,*y,mode,room?room->lx:-999,(long long)packed);if(packed&SP_COORD_IS_RANDOM){*x=3;*y=4;}else{*x=packed&255;*y=(packed>>16)&255;}if(room){*x+=room->lx;*y+=room->ly;}else{*x+=gx.xstart;*y+=gy.ystart;}}
int __wrap_nhl_pcall_handle(lua_State *L,int nargs,int results,const char *name,NHL_pcall_action action){int out;append("pcall:%d,%d:%s:%d;",nargs,results,name,action);if(options[1]&&!grown){grown=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!grown)abort();append("heap-grown;");}out=lua_pcall(L,nargs,results,0);if(out){append("callback-error:%s;",lua_tostring(L,-1));lua_pop(L,1);}return out;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/nhlsel.c"
#define NHLSEL_VALIDATE_REFERENCE 1
#else
extern struct selectionvar *teleport_nhlsel_test_l_selection_push_new(lua_State *);
extern boolean teleport_nhlsel_test_params_sel_2coords(lua_State *,struct selectionvar **,coordxy *,coordxy *,coordxy *,coordxy *);
#endif
#include "tu-nhlsel-layout.h"
static void *last_freed;
void __real_free(void *);
char *__real_dupstr(const char *);
void __wrap_free(void *p){last_freed=p;if(options[7]){struct selectionvar *a=luaL_testudata(state,1,"selection"),*b=luaL_testudata(state,2,"selection");append("free:argalias%d:map1%d:map2%d;",a&&a==b,a&&a->map==p,b&&b->map==p);}__real_free(p);}
char *__wrap_dupstr(const char *p){if(options[7]){struct selectionvar *a=luaL_testudata(state,1,"selection"),*b=luaL_testudata(state,2,"selection");append("dupstr:argalias%d:map1%d:map2%d:after-free%d;",a&&a==b,a&&a->map==p,b&&b->map==p,p==last_freed);}return __real_dupstr(p);}
static void dump_value(int i){int t=lua_type(state,i),j;const char *s;struct selectionvar *sel;snap("type:%d:",t);switch(t){case LUA_TNUMBER:if(lua_isinteger(state,i))snap("i%lld;",(long long)lua_tointeger(state,i));else snap("f%a;",lua_tonumber(state,i));break;case LUA_TBOOLEAN:snap("%d;",lua_toboolean(state,i));break;case LUA_TSTRING:s=lua_tostring(state,i);snap("%zu:",strlen(s));for(j=0;s[j];j++)snap("%02x",(unsigned char)s[j]);snap(";");break;case LUA_TUSERDATA:sel=luaL_testudata(state,i,"selection");if(sel){snap("sel:%d,%d,%d:%d,%d,%d,%d:map%d:",sel->wid,sel->hei,sel->bounds_dirty,sel->bounds.lx,sel->bounds.ly,sel->bounds.hx,sel->bounds.hy,sel->map!=NULL);if(sel->map)for(j=0;j<sel->wid*sel->hei+1;j++)snap("%02x",(unsigned char)sel->map[j]);snap(";");}break;case LUA_TTABLE:{static const char *keys[]={"x","y","lx","ly","hx","hy","n","text",NULL};for(j=0;keys[j];j++){lua_getfield(state,i,keys[j]);if(!lua_isnil(state,-1)){snap("%s=",keys[j]);dump_value(lua_gettop(state));}lua_pop(state,1);}snap(";");break;}default:snap(";");}}
void probe_reset(unsigned seed){int x,y;if(state){lua_close(state);state=NULL;}if(grown)free(grown);grown=NULL;memset(&gc,0,sizeof gc);memset(&gx,0,sizeof gx);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&svn,0,sizeof svn);memset(&svr,0,sizeof svr);memset(&coder,0,sizeof coder);memset(options,0,sizeof options);random_state=seed;random_index=0;trace_storage[0]=caller[0]=snapshot_storage[0]=input_storage[0]=0;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)levl[x][y].typ=(x>1&&x<14&&y<10)?ROOM:STONE;state=luaL_newstate();if(!state)abort();luaL_openlibs(state);l_selection_register(state);}
char *probe_input(void){return input_storage;}
void probe_clear_trace(void){trace_storage[0]=0;}
const char *probe_trace(void){return trace_storage;}
const char *probe_snapshot(void){int i;snapshot_storage[0]=0;snap("rng:%u:%d;top:%d;",random_state,random_index,lua_gettop(state));for(i=1;i<=lua_gettop(state);i++)dump_value(i);return snapshot_storage;}
int probe_run(void){int result;lua_settop(state,0);result=luaL_loadstring(state,input_storage);if(!result)result=lua_pcall(state,0,LUA_MULTRET,0);return result;}
void probe_option(int n,int value){options[n]=value;}
void probe_origin(int x,int y,int which){gx.xstart=x;gy.ystart=y;gc.coder=which?&coder:NULL;coder.croom=which==2?&svr.rooms[0]:NULL;coder.n_subroom=which==2?1:0;coder.tmproomlist[0]=coder.croom;}
void probe_room(int n,int lx,int ly,int hx,int hy){svr.rooms[n].lx=lx;svr.rooms[n].ly=ly;svr.rooms[n].hx=hx;svr.rooms[n].hy=hy;if(n>=svn.nroom)svn.nroom=n+1;}
void probe_cell(int x,int y,int typ,int lit){levl[x][y].typ=typ;levl[x][y].lit=lit;}
int probe_alias(int n){int out;lua_getglobal(state,"selection");if(n==0){lua_getfield(state,-1,"area");lua_getfield(state,-2,"fillrect");out=lua_tocfunction(state,-1)==lua_tocfunction(state,-2);}else{luaL_getmetatable(state,"selection");lua_getfield(state,-1,"__add");lua_getfield(state,-2,"__bor");out=lua_tocfunction(state,-1)==lua_tocfunction(state,-2);}lua_settop(state,0);return out;}
int probe_helper(int which){coordxy x1=-111,y1=-112,x2=-113,y2=-114;struct selectionvar *sel=NULL;boolean out;if(which==2)return l_selection_check(state,1)!=NULL;if(which==3){sel=l_selection_check(state,1);l_selection_push_copy(state,sel);return 1;}if(which==0){
#ifdef TELEPORT_REFERENCE_TU
sel=l_selection_push_new(state);
#else
sel=teleport_nhlsel_test_l_selection_push_new(state);
#endif
return sel!=NULL;}
#ifdef TELEPORT_REFERENCE_TU
out=params_sel_2coords(state,&sel,&x1,&y1,&x2,&y2);
#else
out=teleport_nhlsel_test_params_sel_2coords(state,&sel,&x1,&y1,&x2,&y2);
#endif
append("params:%d:%d,%d,%d,%d:%d;",out,x1,y1,x2,y2,sel!=NULL);return out;}
uintptr_t probe_state(void){return (uintptr_t)state;}
size_t probe_stack(void){return emscripten_stack_get_current();}
