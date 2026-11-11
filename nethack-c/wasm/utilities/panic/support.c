#define NEED_VARARGS
#include "config.h"
#include <stdint.h>
#include <stdarg.h>
#ifdef REFERENCE_PANIC
#ifndef UTILITY_PANIC_REFERENCE_SOURCE
#error "Explicit absolute original utility reference source required"
#endif
#include UTILITY_PANIC_REFERENCE_SOURCE
#else
extern void utility_panic_js(const char*,va_list);
void panic(const char *str,...){va_list ap;va_start(ap,str);utility_panic_js(str,ap);va_end(ap);}
#endif
void utility_panic_fixture(int mode,const char*text,long wide,double value){switch(mode){case 0:panic("%s",text);break;case 1:panic("number=%d long=%ld double=%.3f char=%c string=%s\n",-17,wide,value,65,text);break;case 2:panic("literal %% noargs");break;case 3:panic("%*.*s:%ld",12,3,text,wide);break;default:abort();}}
FILE*utility_panic_stderr(void){return stderr;}
int utility_panic_fputs(const char*s,FILE*f){return fputs(s,f);}
int utility_panic_vfprintf(FILE*f,const char*s,va_list ap){return vfprintf(f,s,ap);}
int utility_panic_fflush(FILE*f){return fflush(f);}
void utility_panic_va_end(va_list ap){va_end(ap);}
void utility_panic_abort(void){abort();}
void utility_panic_exit(int n){exit(n);}
#ifdef REFERENCE_PANIC
uintptr_t utility_panic_state_address(void){return(uintptr_t)&panicking;}
#else
uintptr_t utility_panic_state_address(void){return 0;}
#endif
