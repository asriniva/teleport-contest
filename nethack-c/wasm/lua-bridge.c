/* Lua 5.4 C ABI transport for the experimental JavaScript Lua runtime.
 * The configured Lua headers and NetHack binding functions are unchanged.
 * This file contains no interpreter, collector or standard-library algorithm.
 * Lua errors cross a native callback boundary using C setjmp/longjmp; ordinary
 * JS exceptions are never used to skip arbitrary native callback frames. */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lobject.h" /* configured userdata/string layout, never algorithms */
#include "lstate.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

extern uint64_t teleport_lua_dispatch(lua_State *, const char *, uint64_t,
                                     uint64_t, uint64_t, uint64_t, uint64_t);
extern int teleport_lua_failed(lua_State *);
extern void teleport_lua_unprotected(lua_State *);
struct callback_frame { jmp_buf jump; lua_State *state; struct callback_frame *previous; };
static struct callback_frame *callbacks;

static uint64_t dispatch(lua_State *L, const char *operation, uint64_t a,
                         uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t result = teleport_lua_dispatch(L, operation, a, b, c, d, e);
    if (teleport_lua_failed(L)) {
        struct callback_frame *frame;
        for (frame = callbacks; frame; frame = frame->previous)
            if (frame->state == L) longjmp(frame->jump, 1);
        teleport_lua_unprotected(L);
        abort(); /* A panic callback is not permitted to return. */
    }
    return result;
}
#define P(value) ((uint64_t)(uintptr_t)(value))
#define D0(L,n) dispatch(L,n,0,0,0,0,0)
#define D1(L,n,a) dispatch(L,n,P(a),0,0,0,0)
#define D2(L,n,a,b) dispatch(L,n,P(a),P(b),0,0,0)
#define D3(L,n,a,b,c) dispatch(L,n,P(a),P(b),P(c),0,0)
#define D4(L,n,a,b,c,d) dispatch(L,n,P(a),P(b),P(c),P(d),0)
#define D5(L,n,a,b,c,d,e) dispatch(L,n,P(a),P(b),P(c),P(d),P(e))
static uint64_t number_bits(lua_Number n) { union { lua_Number n; uint64_t u; } v = { .n=n }; return v.u; }
static lua_Number bits_number(uint64_t u) { union { lua_Number n; uint64_t u; } v = { .u=u }; return v.n; }

/* Scalar host inputs only; Lua's entropy summation/pivot policy stays in JS. */
EMSCRIPTEN_KEEPALIVE int64_t teleport_lua_sort_clock(void) { return (int64_t)clock(); }
EMSCRIPTEN_KEEPALIVE int64_t teleport_lua_sort_time(void) { return (int64_t)time(NULL); }
EMSCRIPTEN_KEEPALIVE int64_t teleport_lua_os_clock_rate(void) { return CLOCKS_PER_SEC; }
EMSCRIPTEN_KEEPALIVE double teleport_lua_os_difftime(int64_t a,int64_t b) { return difftime((time_t)a,(time_t)b); }
EMSCRIPTEN_KEEPALIVE int teleport_lua_os_calendar(int64_t value,int utc,struct tm *result)
{ time_t stamp=(time_t)value; return (utc?gmtime_r(&stamp,result):localtime_r(&stamp,result))!=NULL; }
EMSCRIPTEN_KEEPALIVE int64_t teleport_lua_os_mktime(struct tm *value) { return (int64_t)mktime(value); }
EMSCRIPTEN_KEEPALIVE size_t teleport_lua_os_strftime(char *out,size_t size,const char *format,const struct tm *value)
{ return strftime(out,size,format,value); }
EMSCRIPTEN_KEEPALIVE int teleport_lua_os_remove(const char *path) { errno=0;return remove(path); }
EMSCRIPTEN_KEEPALIVE int teleport_lua_os_rename(const char *from,const char *to) { errno=0;return rename(from,to); }
EMSCRIPTEN_KEEPALIVE int teleport_lua_os_errno(void) { return errno; }
EMSCRIPTEN_KEEPALIVE const char *teleport_lua_os_error_message(int error) { return strerror(error); }
EMSCRIPTEN_KEEPALIVE size_t teleport_lua_os_tm_layout(int field)
{
    static const size_t offsets[]={sizeof(struct tm),offsetof(struct tm,tm_sec),offsetof(struct tm,tm_min),
        offsetof(struct tm,tm_hour),offsetof(struct tm,tm_mday),offsetof(struct tm,tm_mon),offsetof(struct tm,tm_year),
        offsetof(struct tm,tm_wday),offsetof(struct tm,tm_yday),offsetof(struct tm,tm_isdst)};
    return field>=0 && field<(int)(sizeof offsets/sizeof offsets[0])?offsets[field]:0;
}

EMSCRIPTEN_KEEPALIVE int teleport_lua_callback(lua_CFunction fn, lua_State *L)
{
    struct callback_frame frame;
    int result;
    frame.state = L; frame.previous = callbacks; callbacks = &frame;
    if (setjmp(frame.jump)) result = -1;
    else result = fn(L);
    callbacks = frame.previous;
    return result;
}

/* Query the configured C layout instead of hard-coding wasm64 struct offsets
 * in the JS adapter. i_ci is an opaque descriptor token outside compiled Lua. */
EMSCRIPTEN_KEEPALIVE size_t teleport_lua_debug_layout(int field)
{
    static const size_t offsets[] = {
        sizeof(lua_Debug), offsetof(lua_Debug,event), offsetof(lua_Debug,name),
        offsetof(lua_Debug,namewhat), offsetof(lua_Debug,what), offsetof(lua_Debug,source),
        offsetof(lua_Debug,srclen), offsetof(lua_Debug,currentline), offsetof(lua_Debug,linedefined),
        offsetof(lua_Debug,lastlinedefined), offsetof(lua_Debug,nups), offsetof(lua_Debug,nparams),
        offsetof(lua_Debug,isvararg), offsetof(lua_Debug,istailcall), offsetof(lua_Debug,ftransfer),
        offsetof(lua_Debug,ntransfer), offsetof(lua_Debug,short_src), offsetof(lua_Debug,i_ci), LUA_IDSIZE
    };
    return field >= 0 && field < (int)(sizeof offsets/sizeof offsets[0]) ? offsets[field] : 0;
}
EMSCRIPTEN_KEEPALIVE size_t teleport_lua_string_header(void)
{ return offsetof(TString,contents); }
EMSCRIPTEN_KEEPALIVE size_t teleport_lua_userdata_header(int values)
{ return values >= 0 && values <= 65535 ? udatamemoffset(values) : 0; }
EMSCRIPTEN_KEEPALIVE size_t teleport_lua_memory_layout(int field)
{
    static const size_t sizes[] = { sizeof(Table),sizeof(Node),sizeof(TValue),
        offsetof(TString,contents),sizeof(Proto),offsetof(LClosure,upvals),
        offsetof(CClosure,upvalue),sizeof(UpVal),sizeof(lua_State),sizeof(global_State),
        sizeof(CallInfo),udatamemoffset(0),udatamemoffset(1)-sizeof(UValue) };
    return field >= 0 && field < (int)(sizeof sizes/sizeof sizes[0]) ? sizes[field] : 0;
}
EMSCRIPTEN_KEEPALIVE int teleport_lua_hook(lua_Hook fn, lua_State *L,lua_Debug *ar)
{
    struct callback_frame frame; int result;
    frame.state=L; frame.previous=callbacks; callbacks=&frame;
    if(setjmp(frame.jump)) result=-1; else { fn(L,ar); result=0; }
    callbacks=frame.previous; return result;
}

lua_State *lua_newstate(lua_Alloc f, void *ud) { return (lua_State *)(uintptr_t)D2(NULL,"lua_newstate",f,ud); }
lua_State *luaL_newstate(void) { return (lua_State *)(uintptr_t)D0(NULL,"luaL_newstate"); }
void lua_close(lua_State *L) { D0(L,"lua_close"); }
int lua_gettop(lua_State *L) { return D0(L,"lua_gettop"); }
int lua_absindex(lua_State *L,int i) { return D1(L,"lua_absindex",i); }
void lua_settop(lua_State *L,int i) { D1(L,"lua_settop",i); }
int lua_checkstack(lua_State *L,int n) { return D1(L,"lua_checkstack",n); }
void lua_pushvalue(lua_State *L,int i) { D1(L,"lua_pushvalue",i); }
void lua_copy(lua_State *L,int f,int t) { D2(L,"lua_copy",f,t); }
void lua_rotate(lua_State *L,int i,int n) { D2(L,"lua_rotate",i,n); }
void lua_pushnil(lua_State *L) { D0(L,"lua_pushnil"); }
void lua_pushboolean(lua_State *L,int v) { D1(L,"lua_pushboolean",v); }
void lua_pushinteger(lua_State *L,lua_Integer v) { D1(L,"lua_pushinteger",v); }
void lua_pushnumber(lua_State *L,lua_Number v) { D1(L,"lua_pushnumber",number_bits(v)); }
void lua_pushlightuserdata(lua_State *L,void *v) { D1(L,"lua_pushlightuserdata",v); }
const char *lua_pushstring(lua_State *L,const char *v) { return (const char *)(uintptr_t)D1(L,"lua_pushstring",v); }
const char *lua_pushlstring(lua_State *L,const char *v,size_t n) { return (const char *)(uintptr_t)D2(L,"lua_pushlstring",v,n); }
void lua_pushcclosure(lua_State *L,lua_CFunction f,int n) { D2(L,"lua_pushcclosure",f,n); }
int lua_type(lua_State *L,int i) { return D1(L,"lua_type",i); }
const char *lua_typename(lua_State *L,int t) { return (const char *)(uintptr_t)D1(L,"lua_typename",t); }
int lua_isnumber(lua_State *L,int i) { return D1(L,"lua_isnumber",i); }
int lua_isstring(lua_State *L,int i) { return D1(L,"lua_isstring",i); }
int lua_isinteger(lua_State *L,int i) { return D1(L,"lua_isinteger",i); }
int lua_iscfunction(lua_State *L,int i) { return D1(L,"lua_iscfunction",i); }
int lua_isuserdata(lua_State *L,int i) { int type=lua_type(L,i); return type==LUA_TUSERDATA || type==LUA_TLIGHTUSERDATA; }
int lua_rawequal(lua_State *L,int a,int b) { return D2(L,"lua_rawequal",a,b); }
int lua_toboolean(lua_State *L,int i) { return D1(L,"lua_toboolean",i); }
lua_Integer lua_tointegerx(lua_State *L,int i,int *valid) { return (lua_Integer)D2(L,"lua_tointegerx",i,valid); }
lua_Number lua_tonumberx(lua_State *L,int i,int *valid) { return bits_number(D2(L,"lua_tonumberx",i,valid)); }
const char *lua_tolstring(lua_State *L,int i,size_t *n) { return (const char *)(uintptr_t)D2(L,"lua_tolstring",i,n); }
void *lua_touserdata(lua_State *L,int i) { return (void *)(uintptr_t)D1(L,"lua_touserdata",i); }
const void *lua_topointer(lua_State *L,int i) { return (void *)(uintptr_t)D1(L,"lua_topointer",i); }
void lua_createtable(lua_State *L,int a,int h) { D2(L,"lua_createtable",a,h); }
int lua_getglobal(lua_State *L,const char *k) { return D1(L,"lua_getglobal",k); }
void lua_setglobal(lua_State *L,const char *k) { D1(L,"lua_setglobal",k); }
int lua_getfield(lua_State *L,int i,const char *k) { return D2(L,"lua_getfield",i,k); }
void lua_setfield(lua_State *L,int i,const char *k) { D2(L,"lua_setfield",i,k); }
int lua_geti(lua_State *L,int i,lua_Integer k) { return D2(L,"lua_geti",i,k); }
void lua_seti(lua_State *L,int i,lua_Integer k) { D2(L,"lua_seti",i,k); }
int lua_gettable(lua_State *L,int i) { return D1(L,"lua_gettable",i); }
void lua_settable(lua_State *L,int i) { D1(L,"lua_settable",i); }
int lua_rawget(lua_State *L,int i) { return D1(L,"lua_rawget",i); }
void lua_rawset(lua_State *L,int i) { D1(L,"lua_rawset",i); }
int lua_rawgeti(lua_State *L,int i,lua_Integer k) { return D2(L,"lua_rawgeti",i,k); }
void lua_rawseti(lua_State *L,int i,lua_Integer k) { D2(L,"lua_rawseti",i,k); }
int lua_next(lua_State *L,int i) { return D1(L,"lua_next",i); }
void lua_len(lua_State *L,int i) { D1(L,"lua_len",i); }
lua_Unsigned lua_rawlen(lua_State *L,int i) { return D1(L,"lua_rawlen",i); }
int lua_getmetatable(lua_State *L,int i) { return D1(L,"lua_getmetatable",i); }
int lua_setmetatable(lua_State *L,int i) { return D1(L,"lua_setmetatable",i); }
void *lua_newuserdatauv(lua_State *L,size_t n,int u) { return (void *)(uintptr_t)D2(L,"lua_newuserdatauv",n,u); }
void lua_callk(lua_State *L,int n,int r,lua_KContext c,lua_KFunction k) { D4(L,"lua_callk",n,r,c,k); }
int lua_pcallk(lua_State *L,int n,int r,int e,lua_KContext c,lua_KFunction k) { return D5(L,"lua_pcallk",n,r,e,c,k); }
int lua_error(lua_State *L) { return D0(L,"lua_error"); }
lua_Integer luaL_checkinteger(lua_State *L,int i) { return (lua_Integer)D1(L,"luaL_checkinteger",i); }
lua_Integer luaL_optinteger(lua_State *L,int i,lua_Integer d) { return (lua_Integer)D2(L,"luaL_optinteger",i,d); }
const char *luaL_checklstring(lua_State *L,int i,size_t *n) { return (const char *)(uintptr_t)D2(L,"luaL_checklstring",i,n); }
const char *luaL_optlstring(lua_State *L,int i,const char *d,size_t *n) { return (const char *)(uintptr_t)D3(L,"luaL_optlstring",i,d,n); }
int luaL_checkoption(lua_State *L,int i,const char *d,const char *const opts[]) { return D3(L,"luaL_checkoption",i,d,opts); }
void luaL_checktype(lua_State *L,int i,int t) { D2(L,"luaL_checktype",i,t); }
void *luaL_checkudata(lua_State *L,int i,const char *n) { return (void *)(uintptr_t)D2(L,"luaL_checkudata",i,n); }
int luaL_newmetatable(lua_State *L,const char *n) { return D1(L,"luaL_newmetatable",n); }
void luaL_setfuncs(lua_State *L,const luaL_Reg *r,int n) { D2(L,"luaL_setfuncs",r,n); }
void luaL_requiref(lua_State *L,const char *n,lua_CFunction f,int g) { D3(L,"luaL_requiref",n,f,g); }
void luaL_checkversion_(lua_State *L,lua_Number v,size_t size) { D2(L,"luaL_checkversion_",number_bits(v),size); }
int luaL_loadbufferx(lua_State *L,const char *b,size_t n,const char *name,const char *mode) { return D4(L,"luaL_loadbufferx",b,n,name,mode); }
int luaL_loadstring(lua_State *L,const char *s) { return D1(L,"luaL_loadstring",s); }
lua_Alloc lua_getallocf(lua_State *L,void **ud) { return (lua_Alloc)(uintptr_t)D1(L,"lua_getallocf",ud); }
lua_CFunction lua_atpanic(lua_State *L,lua_CFunction f) { return (lua_CFunction)(uintptr_t)D1(L,"lua_atpanic",f); }
void lua_setwarnf(lua_State *L,lua_WarnFunction f,void *ud) { D2(L,"lua_setwarnf",f,ud); }
void lua_warning(lua_State *L,const char *message,int continued) { D2(L,"lua_warning",message,continued); }
void lua_sethook(lua_State *L,lua_Hook f,int mask,int count) { D3(L,"lua_sethook",f,mask,count); }
int lua_getstack(lua_State *L,int level,lua_Debug *ar) { return D2(L,"lua_getstack",level,ar); }
int lua_getinfo(lua_State *L,const char *what,lua_Debug *ar) { return D2(L,"lua_getinfo",what,ar); }
void luaL_traceback(lua_State *L,lua_State *from,const char *msg,int level) { D3(L,"luaL_traceback",from,msg,level); }
int lua_gc(lua_State *L,int what,...) {
    va_list args; int a=0,b=0,c=0;
    va_start(args,what);
    if (what==LUA_GCSTEP || what==LUA_GCSETPAUSE || what==LUA_GCSETSTEPMUL) a=va_arg(args,int);
    else if (what==LUA_GCGEN) { a=va_arg(args,int); b=va_arg(args,int); }
    else if (what==LUA_GCINC) { a=va_arg(args,int); b=va_arg(args,int); c=va_arg(args,int); }
    va_end(args); return D4(L,"lua_gc",what,a,b,c);
}
int luaopen_base(lua_State *L) { return D0(L,"luaopen_base"); }
int luaopen_coroutine(lua_State *L) { return D0(L,"luaopen_coroutine"); }
int luaopen_table(lua_State *L) { return D0(L,"luaopen_table"); }
int luaopen_string(lua_State *L) { return D0(L,"luaopen_string"); }
int luaopen_math(lua_State *L) { return D0(L,"luaopen_math"); }
int luaopen_utf8(lua_State *L) { return D0(L,"luaopen_utf8"); }
int luaopen_os(lua_State *L) { return D0(L,"luaopen_os"); }
int luaopen_debug(lua_State *L) { return D0(L,"luaopen_debug"); }
void luaL_openlibs(lua_State *L) { D0(L,"luaL_openlibs"); }
