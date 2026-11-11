/* Fixed-signature libc ABI transports only. No XPM/IFF conversion policy. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <emscripten/emscripten.h>
EMSCRIPTEN_KEEPALIVE FILE *t_fopen(const char *fn,const char *mode){return fopen(fn,mode);}
EMSCRIPTEN_KEEPALIVE int t_fclose(FILE *f){return fclose(f);}
EMSCRIPTEN_KEEPALIVE char *t_fgets(char *p,int n,FILE *f){return fgets(p,n,f);}
EMSCRIPTEN_KEEPALIVE int t_fputc(int c,FILE *f){return fputc(c,f);}
EMSCRIPTEN_KEEPALIVE size_t t_fwrite(const void *p,size_t s,size_t n,FILE *f){return fwrite(p,s,n,f);}
EMSCRIPTEN_KEEPALIVE int t_scan_dimensions(const char *p,const char *fmt,int *a,int *b,int *c,int *d){return sscanf(p,fmt,a,b,c,d);}
/* int* arguments preserve the original source's inherited %x mismatch. */
EMSCRIPTEN_KEEPALIVE int t_scan_color(const char *p,const char *fmt,char *a,int *b,int *c,int *d){return sscanf(p,fmt,a,b,c,d);}
EMSCRIPTEN_KEEPALIVE int t_fprintf_p(FILE *f,const char *fmt,const char *p){return fprintf(f,fmt,p);}
EMSCRIPTEN_KEEPALIVE int t_fprintf_ii(FILE *f,const char *fmt,int a,int b){return fprintf(f,fmt,a,b);}
EMSCRIPTEN_KEEPALIVE int t_printf5(const char *fmt,int a,int b,int c,int d,unsigned e){return printf(fmt,a,b,c,d,e);}
EMSCRIPTEN_KEEPALIVE int t_isspace(int c){return isspace(c);}
EMSCRIPTEN_KEEPALIVE FILE *t_stderr(void){return stderr;}
EMSCRIPTEN_KEEPALIVE void *t_malloc(size_t n){return malloc(n);}
EMSCRIPTEN_KEEPALIVE void *t_calloc(size_t a,size_t b){return calloc(a,b);}
EMSCRIPTEN_KEEPALIVE void t_free(void *p){free(p);}
EMSCRIPTEN_KEEPALIVE void *t_memset(void *p,int c,size_t n){return memset(p,c,n);}
EMSCRIPTEN_KEEPALIVE void t_perror(const char *s){perror(s);}
