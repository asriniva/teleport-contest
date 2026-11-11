#include "config.h"
#include "dlb.h"
#include "hacklib.h"
#include <fcntl.h>
#include <stdint.h>
#include <stddef.h>
#ifndef O_BINARY
#define O_BINARY 0
#endif
_Static_assert(sizeof(long)==8 && sizeof(void*)==8 && sizeof(int)==4,"utility memory64 widths");
#ifdef REFERENCE_DLB_MAIN
#define main utility_main
#ifndef UTILITY_DLB_MAIN_REFERENCE_SOURCE
#error "Explicit absolute original utility reference source required"
#endif
#include UTILITY_DLB_MAIN_REFERENCE_SOURCE
#undef main
#else
extern void dlb_main_js_usage(void);
extern void dlb_main_js_verbose_help(void);
extern void dlb_main_js_Write(int,char*,long);
extern FILE *dlb_main_js_fopen_datafile(const char*,const char*,int);
extern int dlb_main_js_main(int,char**);
extern void dlb_main_js_grow_ld(libdir**,int*,int);
extern void dlb_main_js_write_dlb_directory(int,int,libdir*,long,long,long);
extern void dlb_main_js_xexit(int);
static void usage(void){dlb_main_js_usage();}
static void verbose_help(void){dlb_main_js_verbose_help();}
static void Write(int out,char*buf,long len){dlb_main_js_Write(out,buf,len);}
FILE*fopen_datafile(const char*filename,const char*mode,int prefix){return dlb_main_js_fopen_datafile(filename,mode,prefix);}
int utility_main(int argc,char**argv){return dlb_main_js_main(argc,argv);}
static void grow_ld(libdir**ld_p,int*ldlimit_p,int alloc_incr){dlb_main_js_grow_ld(ld_p,ldlimit_p,alloc_incr);}
static void write_dlb_directory(int out,int nfiles,libdir*ld,long slen,long dir_size,long flen){dlb_main_js_write_dlb_directory(out,nfiles,ld,slen,dir_size,flen);}
static void xexit(int retcd){dlb_main_js_xexit(retcd);}
#endif
static libdir utility_zero;
uintptr_t utility_layout(int i){switch(i){case 0:return sizeof(library);case 1:return sizeof(libdir);case 2:return BUFSIZ;case 3:return FCMASK;case 4:return O_RDONLY;case 5:return O_WRONLY;case 6:return O_TRUNC;case 7:return O_CREAT;case 8:return O_RDWR;case 9:return O_BINARY;case 10:return SEEK_SET;case 11:return SEEK_END;case 12:return sizeof(void*);case 13:return(uintptr_t)&utility_zero;case 14:return(uintptr_t)DLBFILE;default:abort();}}
uintptr_t utility_offset(int type,int field){if(type==0){switch(field){case 0:return offsetof(library,fdata);case 1:return offsetof(library,fmark);case 2:return offsetof(library,dir);case 3:return offsetof(library,sspace);case 4:return offsetof(library,nentries);case 5:return offsetof(library,rev);case 6:return offsetof(library,strsize);}}else{switch(field){case 0:return offsetof(libdir,fname);case 1:return offsetof(libdir,foffset);case 2:return offsetof(libdir,fsize);case 3:return offsetof(libdir,handling);}}abort();}
void utility_private(int which,long a,long b,long c,long d,long e,long f){switch(which){case 0:usage();break;case 1:verbose_help();break;case 2:Write((int)a,(char*)b,c);break;case 3:grow_ld((libdir**)a,(int*)b,(int)c);break;case 4:write_dlb_directory((int)a,(int)b,(libdir*)c,d,e,f);break;case 5:xexit((int)a);break;default:abort();}}
int utility_open(const char*p,int flags,int mode){return open(p,flags,mode);}
ssize_t utility_read(int fd,void*p,size_t n){return read(fd,p,n);}
ssize_t utility_write(int fd,const void*p,size_t n){return write(fd,p,n);}
void utility_printf_s(const char*f,const char*a){printf(f,a);}
void utility_printf_sll(const char*f,const char*a,long b,long c){printf(f,a,b,c);}
void utility_printf_lll(const char*f,long a,long b,long c){printf(f,a,b,c);}
void utility_sprintf_header(char*out,const char*f,long a,long b,long c,long d,long e){sprintf(out,f,a,b,c,d,e);}
void utility_sprintf_entry(char*out,const char*f,int a,const char*b,long c){sprintf(out,f,a,b,c);}
FILE*utility_fopen(const char*a,const char*b){return fopen(a,b);}
char*utility_fgets(char*a,int n,FILE*f){return fgets(a,n,f);}
size_t utility_fread(void*a,size_t b,size_t c,FILE*f){return fread(a,b,c,f);}
int utility_fseek(FILE*f,long n,int whence){return fseek(f,n,whence);}
int utility_fclose(FILE*f){return fclose(f);}
void utility_exit(int n){exit(n);}
static unsigned long utility_allocations,utility_frees;
extern void *__real_malloc(size_t);
extern void __real_free(void*);
void *__wrap_malloc(size_t n){void*p=__real_malloc(n);if(p)++utility_allocations;return p;}
void __wrap_free(void*p){if(p)++utility_frees;__real_free(p);}
void utility_free(void*p){free(p);}
unsigned long utility_stats(int which){return which?utility_frees:utility_allocations;}
void*utility_malloc(size_t n){return __real_malloc(n);}
