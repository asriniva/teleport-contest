#define RECOVER_C
#include "config.h"
#include "hacklib.h"
#include "artifact.h"
#include "rect.h"
#include "dungeon.h"
#include "hack.h"
#include <fcntl.h>
#include <stdint.h>
#ifdef REFERENCE_RECOVER
#define main teleport_recover_main
#ifndef UTILITY_RECOVER_REFERENCE_SOURCE
#error "Explicit absolute original utility reference source required"
#endif
#include UTILITY_RECOVER_REFERENCE_SOURCE
#undef main
#else
char savename[SAVESIZE];
static char lock[256];
extern int recover_js_main(int,char**);
extern void recover_js_set_levelfile_name(int);
extern int recover_js_open_levelfile(int);
extern int recover_js_create_savefile(void);
extern int recover_js_restore_savefile(char*);
int teleport_recover_main(int argc,char**argv){return recover_js_main(argc,argv);}
void set_levelfile_name(int lev){recover_js_set_levelfile_name(lev);}
int open_levelfile(int lev){return recover_js_open_levelfile(lev);}
int create_savefile(void){return recover_js_create_savefile();}
int restore_savefile(char*basename){return recover_js_restore_savefile(basename);}
#endif
extern uchar cscbuf[];
uintptr_t recover_layout(int i){switch(i){case 0:return(uintptr_t)savename;case 1:return(uintptr_t)lock;case 2:return(uintptr_t)cscbuf;case 3:return SAVESIZE;case 4:return PL_NSIZ_PLUS;case 5:return sizeof(struct version_info);case 6:return sizeof(int);case 7:return O_RDONLY;case 8:return FCMASK;case 9:return sizeof(char*);case 10:return(uintptr_t)HACKDIR;default:abort();}}
int recover_open(const char*p,int flags,int mode){return open(p,flags,mode);}
int recover_creat(const char*p,int mode){return creat(p,mode);}
ssize_t recover_read(int fd,void*p,size_t n){return read(fd,p,n);}
ssize_t recover_write(int fd,const void*p,size_t n){return write(fd,p,n);}
void recover_fprintf(const char*f,const char*a,const char*b,const char*c,const char*d){fprintf(stderr,f,a,b,c,d);}
void recover_sprintf(char*out,const char*f,int n){sprintf(out,f,n);}
void recover_exit(int n){exit(n);}
void recover_assert(int truth){assert(truth);}
