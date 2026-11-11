#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#ifndef MIXED_RANDOM
#ifndef RANDOM_ORIGINAL_SOURCE
#error "explicit original RANDOM source path required"
#endif
#include RANDOM_ORIGINAL_SOURCE
#else
extern void utility_js_srandom(unsigned);
extern char *utility_js_initstate(unsigned,char*,int);
extern char *utility_js_setstate(char*);
extern long utility_js_random(void);
extern int utility_js_scalar(int);
extern uintptr_t utility_js_pointer(int);
void srandom(unsigned x){utility_js_srandom(x);}
char *initstate(unsigned seed,char *arg_state,int n){return utility_js_initstate(seed,arg_state,n);}
char *setstate(char *arg_state){return utility_js_setstate(arg_state);}
long random(void){return utility_js_random();}
static long utility_randtbl[32];
#endif
int utility_long_size(void){return sizeof(long);}
int utility_degree(int type){static const int values[]={0,7,15,31,63};return values[type];}
void *utility_storage(void){
#ifndef MIXED_RANDOM
return randtbl;
#else
return utility_randtbl;
#endif
}
int probe_scalar(int i){
#ifndef MIXED_RANDOM
return i==0?rand_type:i==1?rand_deg:rand_sep;
#else
return utility_js_scalar(i);
#endif
}
uintptr_t probe_pointer(int i){
#ifndef MIXED_RANDOM
return(uintptr_t)(i==0?state:i==1?fptr:i==2?rptr:end_ptr);
#else
return utility_js_pointer(i);
#endif
}
static int diag_count;static char diagnostic[256];
void impossible(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(diagnostic,sizeof diagnostic,format,ap);va_end(ap);diag_count++;}
void utility_impossible(const char *format,int n){impossible(format,n);}
int probe_diag_count(void){return diag_count;}
const char *probe_diagnostic(void){return diagnostic;}
