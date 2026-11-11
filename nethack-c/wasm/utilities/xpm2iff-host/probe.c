/* Private direct callers/storage witnesses. Original reference policy unchanged. */
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>
#include <emscripten/emscripten.h>
#define main utility_main
#ifdef HYBRID_XPM2IFF
#include "generated/mixed.c"
#else
#include "source/xpm2iff_host.c"
#endif
#undef main
#include "generated/literal-data.h"
static int allocation_attempts, refuse_allocation=-1;
void *__real_malloc(size_t);
void *__real_calloc(size_t,size_t);
void *__wrap_malloc(size_t n){if(allocation_attempts++==refuse_allocation){errno=ENOMEM;return NULL;}return __real_malloc(n);}
void *__wrap_calloc(size_t a,size_t b){if(allocation_attempts++==refuse_allocation){errno=ENOMEM;return NULL;}return __real_calloc(a,b);}
EMSCRIPTEN_KEEPALIVE void probe_fail(int n){allocation_attempts=0;refuse_allocation=n;}
EMSCRIPTEN_KEEPALIVE int probe_attempts(void){return allocation_attempts;}
EMSCRIPTEN_KEEPALIVE int probe_run(int argc,char **argv){return utility_main(argc,argv);}
EMSCRIPTEN_KEEPALIVE uintptr_t probe_call(int fn,uintptr_t a,uintptr_t b,uint32_t c){
 switch(fn){
 case 0:return (uintptr_t)xpmgetline();
 case 1:return (uintptr_t)fopen_xpm_file((const char *)a);
 case 2:conv_image((int)a);return 0;
 case 3:wr32((uint32_t)a);return 0;
 case 4:write_chunk((const char *)a,(const void *)b,c);return 0;
 case 5:return (uintptr_t)utility_main((int)a,(char **)b);
 default:return UINTPTR_MAX;
 }
}
EMSCRIPTEN_KEEPALIVE uintptr_t probe_global(int n){
 switch(n){case 0:return (uintptr_t)&XpmScreen;case 1:return (uintptr_t)ttable;case 2:return (uintptr_t)&xpmfh;case 3:return (uintptr_t)xbuf;case 4:return (uintptr_t)&planes;case 5:return (uintptr_t)&iff_out;default:return 0;}
}
EMSCRIPTEN_KEEPALIVE uint64_t probe_layout(int n){
 switch(n){case 0:return sizeof(void *);case 1:return sizeof(XpmScreen);case 2:return sizeof(ttable[0]);case 3:return offsetof(__typeof__(XpmScreen),Width);case 4:return offsetof(__typeof__(XpmScreen),Height);case 5:return offsetof(__typeof__(XpmScreen),Colors);case 6:return offsetof(__typeof__(XpmScreen),BytesPerRow);case 7:return offsetof(__typeof__(ttable[0]),flag);case 8:return offsetof(__typeof__(ttable[0]),r);case 9:return offsetof(__typeof__(ttable[0]),g);case 10:return offsetof(__typeof__(ttable[0]),b);case 11:return offsetof(__typeof__(ttable[0]),slot);case 12:return CHAR_MIN;case 13:return sizeof(uint32_t);case 14:return sizeof(int);default:return UINT64_MAX;}
}
EMSCRIPTEN_KEEPALIVE const char *probe_literal(int n){return utility_literals[n];}
EMSCRIPTEN_KEEPALIVE int probe_input(const char *fn){xpmfh=fopen(fn,"r");return !!xpmfh;}
EMSCRIPTEN_KEEPALIVE int probe_output(const char *fn){iff_out=fopen(fn,"wb");return !!iff_out;}
EMSCRIPTEN_KEEPALIVE int probe_close(int output){return fclose(output?iff_out:xpmfh);}

EMSCRIPTEN_KEEPALIVE void probe_capture(void){freopen("/stdout","wb",stdout);freopen("/stderr","wb",stderr);}
EMSCRIPTEN_KEEPALIVE int probe_flush(void){return fflush(NULL);}
