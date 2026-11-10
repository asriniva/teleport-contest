/* Test-only Node-API access to native C probes; no NetHack algorithm here. */
#include <node_api.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#undef malloc
#undef realloc
#undef calloc
#undef free
extern void free(void*);
extern void *malloc(size_t);
extern void *realloc(void *,size_t);
extern void *calloc(size_t,size_t);
static unsigned long native_allocations;
static unsigned long native_stack_checks;
static unsigned long native_stack_failures;
static inline uintptr_t native_stack_pointer(void) {
#if defined(__aarch64__) || defined(__arm64__)
    uintptr_t p; __asm__ volatile("mov %0, sp" : "=r"(p)); return p;
#elif defined(__x86_64__)
    uintptr_t p; __asm__ volatile("mov %%rsp, %0" : "=r"(p)); return p;
#else
#error Native stack checks need an implementation for this architecture
#endif
}
static void native_check_stack(uintptr_t before) { native_stack_checks++; if(native_stack_pointer()!=before) native_stack_failures++; }

static unsigned long long native_requested;
void *teleport_native_malloc(size_t n){native_allocations++;native_requested+=n;return malloc(n);}
void *teleport_native_realloc(void *p,size_t n){native_allocations++;native_requested+=n;return realloc(p,n);}
void *teleport_native_calloc(size_t n,size_t size){native_allocations++;native_requested+=n*size;return calloc(n,size);}
static uint64_t native_integer(napi_env env,napi_value v){
    napi_valuetype type;napi_typeof(env,v,&type);
    if(type==napi_bigint){uint64_t n;bool lossless;napi_get_value_bigint_uint64(env,v,&n,&lossless);return n;}
    double n=0;napi_get_value_double(env,v,&n);return (uint64_t)(int64_t)n;
}
static napi_value native_void(napi_env env){napi_value v;napi_get_undefined(env,&v);return v;}
static napi_value native_number(napi_env env,double n){napi_value v;napi_create_double(env,n,&v);return v;}
static napi_value native_unsigned(napi_env env,uint64_t n){napi_value v;napi_create_bigint_uint64(env,n,&v);return v;}
static napi_value native_signed(napi_env env,int64_t n){napi_value v;napi_create_bigint_int64(env,n,&v);return v;}
static napi_value native_read(napi_env env,napi_callback_info info){
    napi_value a[2],v;size_t argc=2;napi_get_cb_info(env,info,&argc,a,NULL,NULL);
    void *p=(void*)(uintptr_t)native_integer(env,a[0]);size_t n=native_integer(env,a[1]);
    if(n&&!p){napi_throw_range_error(env,NULL,"Cannot read native NULL");return NULL;}napi_create_buffer_copy(env,n,p,NULL,&v);return v;
}
static napi_value native_write(napi_env env,napi_callback_info info){
    napi_value a[2];size_t argc=2,n;void *data;napi_get_cb_info(env,info,&argc,a,NULL,NULL);
    napi_get_buffer_info(env,a[1],&data,&n);memcpy((void*)(uintptr_t)native_integer(env,a[0]),data,n);return native_void(env);
}
static napi_value native_cstring(napi_env env,napi_callback_info info){
    napi_value a[1],v;size_t argc=1;napi_get_cb_info(env,info,&argc,a,NULL,NULL);
    const char *p=(const char*)(uintptr_t)native_integer(env,a[0]);
    napi_create_buffer_copy(env,strlen(p)+1,p,NULL,&v);return v;
}
static napi_value native_stack_status(napi_env env,napi_callback_info info){return native_signed(env,native_stack_failures?-(int64_t)native_stack_failures:(int64_t)native_stack_checks);}
static napi_value native_metrics(napi_env env,napi_callback_info info){return native_unsigned(env,native_requested);}

static int64_t native_clock_epoch;
#if ORACLE_CALENDAR
time_t teleport_native_time(time_t *out){time_t value=(time_t)native_clock_epoch;if(out)*out=value;return value;}
#endif
static napi_value native_set_clock(napi_env env,napi_callback_info info){napi_value a[1];size_t argc=1;napi_get_cb_info(env,info,&argc,a,NULL,NULL);native_clock_epoch=(int64_t)native_integer(env,a[0]);return native_void(env);}

#undef fopen
extern FILE *fopen(const char*,const char*);
static char native_fs_root[4096];
FILE *teleport_native_fopen(const char *path,const char *mode){char full[8192];snprintf(full,sizeof full,"%s/%s",native_fs_root,path[0]=='/'?path+1:path);return fopen(full,mode);}
static napi_value native_set_root(napi_env env,napi_callback_info info){napi_value a[1];size_t argc=1,len;napi_get_cb_info(env,info,&argc,a,NULL,NULL);napi_get_value_string_utf8(env,a[0],native_fs_root,sizeof native_fs_root,&len);return native_void(env);}

