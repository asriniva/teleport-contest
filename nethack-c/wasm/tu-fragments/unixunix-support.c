/* UNIXUNIX ABI/header/native dependency transport and zero backing only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(size_t)==8,"UNIXUNIX memory64 LP64 ABI");
_Static_assert(sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"UNIXUNIX signed native scalar ABI");
void*teleport_unixunix_global(int index){switch(index){
case 0:return(void*)&program_state;
case 1:return(void*)&gl;
case 2:return(void*)&windowprocs;
case 3:return(void*)&svp;
case 4:return(void*)&iflags;
case 5:return(void*)&ynchars;
case 6:return(void*)&stdout;
case 7:return(void*)&svh;
case 8:return(void*)&sysopt;
case 9:return(void*)&flags;
default:abort();}}
uint64_t teleport_unixunix_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(struct flag));
case 6:return(uint64_t)(sizeof(struct instance_flags));
case 7:return(uint64_t)(sizeof(struct instance_globals_l));
case 8:return(uint64_t)(sizeof(struct instance_globals_saved_h));
case 9:return(uint64_t)(sizeof(struct instance_globals_saved_p));
case 10:return(uint64_t)(sizeof(struct sinfo));
case 11:return(uint64_t)(sizeof(struct stat));
case 12:return(uint64_t)(sizeof(struct sysopt_s));
case 13:return(uint64_t)(sizeof(struct timespec));
case 14:return(uint64_t)(sizeof(struct window_procs));
default:abort();}}
uint64_t teleport_unixunix_read(int kind,void*at,int field){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
default:abort();}}
case 1:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->window_inited);
default:abort();}}
case 2:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->locknum);
case 1:return(uint64_t)(uintptr_t)(&p->lock);
default:abort();}}
case 3:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hackpid);
default:abort();}}
case 4:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 5:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->preserve_locks);
default:abort();}}
case 6:{struct stat*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->st_dev);
case 1:return(uint64_t)(uintptr_t)(p->st_mode);
case 2:return(uint64_t)(uintptr_t)(p->st_nlink);
case 3:return(uint64_t)(uintptr_t)(p->st_uid);
case 4:return(uint64_t)(uintptr_t)(p->st_gid);
case 5:return(uint64_t)(uintptr_t)(p->st_rdev);
case 6:return(uint64_t)(uintptr_t)(p->st_size);
case 7:return(uint64_t)(uintptr_t)(p->st_blksize);
case 8:return(uint64_t)(uintptr_t)(p->st_blocks);
case 9:return(uint64_t)(uintptr_t)(&p->st_atim);
case 10:return(uint64_t)(uintptr_t)(&p->st_mtim);
case 11:return(uint64_t)(uintptr_t)(&p->st_ctim);
case 12:return(uint64_t)(uintptr_t)(p->st_ino);
default:abort();}}
case 7:{struct sysopt_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->shellers);
default:abort();}}
case 8:{struct timespec*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tv_sec);
case 1:return(uint64_t)(uintptr_t)(p->tv_nsec);
default:abort();}}
case 9:{volatile struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->win_exit_nhwindows);
case 2:return(uint64_t)(uintptr_t)(p->win_suspend_nhwindows);
case 3:return(uint64_t)(uintptr_t)(p->win_resume_nhwindows);
case 4:return(uint64_t)(uintptr_t)(p->win_wait_synch);
case 5:return(uint64_t)(uintptr_t)(p->win_raw_print);
default:abort();}}
default:abort();}}
void teleport_unixunix_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:p->debug=(__typeof__(p->debug))value;return;
default:abort();}}
case 1:{struct instance_flags*p=at;switch(field){
case 0:p->window_inited=(__typeof__(p->window_inited))value;return;
default:abort();}}
case 2:{struct instance_globals_l*p=at;switch(field){
case 0:p->locknum=(__typeof__(p->locknum))value;return;
default:abort();}}
case 3:{struct instance_globals_saved_h*p=at;switch(field){
case 0:p->hackpid=(__typeof__(p->hackpid))value;return;
default:abort();}}
case 4:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 5:{struct sinfo*p=at;switch(field){
case 0:p->preserve_locks=(__typeof__(p->preserve_locks))value;return;
default:abort();}}
case 6:{struct stat*p=at;switch(field){
case 0:p->st_dev=(__typeof__(p->st_dev))value;return;
case 1:p->st_mode=(__typeof__(p->st_mode))value;return;
case 2:p->st_nlink=(__typeof__(p->st_nlink))value;return;
case 3:p->st_uid=(__typeof__(p->st_uid))value;return;
case 4:p->st_gid=(__typeof__(p->st_gid))value;return;
case 5:p->st_rdev=(__typeof__(p->st_rdev))value;return;
case 6:p->st_size=(__typeof__(p->st_size))value;return;
case 7:p->st_blksize=(__typeof__(p->st_blksize))value;return;
case 8:p->st_blocks=(__typeof__(p->st_blocks))value;return;
case 12:p->st_ino=(__typeof__(p->st_ino))value;return;
default:abort();}}
case 7:{struct sysopt_s*p=at;switch(field){
case 0:p->shellers=(__typeof__(p->shellers))value;return;
default:abort();}}
case 8:{struct timespec*p=at;switch(field){
case 0:p->tv_sec=(__typeof__(p->tv_sec))value;return;
case 1:p->tv_nsec=(__typeof__(p->tv_nsec))value;return;
default:abort();}}
case 9:{volatile struct window_procs*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->win_exit_nhwindows=(__typeof__(p->win_exit_nhwindows))value;return;
case 2:p->win_suspend_nhwindows=(__typeof__(p->win_suspend_nhwindows))value;return;
case 3:p->win_resume_nhwindows=(__typeof__(p->win_resume_nhwindows))value;return;
case 4:p->win_wait_synch=(__typeof__(p->win_wait_synch))value;return;
case 5:p->win_raw_print=(__typeof__(p->win_raw_print))value;return;
default:abort();}}
default:abort();}}
void* teleport_unixunix_address(int kind,void*at,int field){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
default:abort();}}
case 1:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->window_inited;
default:abort();}}
case 2:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->locknum;
case 1:return(void*)&p->lock;
default:abort();}}
case 3:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return(void*)&p->hackpid;
default:abort();}}
case 4:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(void*)&p->plname;
default:abort();}}
case 5:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->preserve_locks;
default:abort();}}
case 6:{struct stat*p=at;switch(field){
case 0:return(void*)&p->st_dev;
case 1:return(void*)&p->st_mode;
case 2:return(void*)&p->st_nlink;
case 3:return(void*)&p->st_uid;
case 4:return(void*)&p->st_gid;
case 5:return(void*)&p->st_rdev;
case 6:return(void*)&p->st_size;
case 7:return(void*)&p->st_blksize;
case 8:return(void*)&p->st_blocks;
case 9:return(void*)&p->st_atim;
case 10:return(void*)&p->st_mtim;
case 11:return(void*)&p->st_ctim;
case 12:return(void*)&p->st_ino;
default:abort();}}
case 7:{struct sysopt_s*p=at;switch(field){
case 0:return(void*)&p->shellers;
default:abort();}}
case 8:{struct timespec*p=at;switch(field){
case 0:return(void*)&p->tv_sec;
case 1:return(void*)&p->tv_nsec;
default:abort();}}
case 9:{volatile struct window_procs*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->win_exit_nhwindows;
case 2:return(void*)&p->win_suspend_nhwindows;
case 3:return(void*)&p->win_resume_nhwindows;
case 4:return(void*)&p->win_wait_synch;
case 5:return(void*)&p->win_raw_print;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_unixunix_var0(char * a0){(error)(a0);}
void teleport_unixunix_var1(char * a0,char * a1){(error)(a0,a1);}
int teleport_unixunix_var2(char * a0,char * a1,unsigned int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_unixunix_var3(char * a0,int a1){return (open)(a0,a1);}
void teleport_unixunix_var4(char * a0,char * a1){(error)(a0,a1);}
void teleport_unixunix_var5(char * a0){(error)(a0);}
int teleport_unixunix_var6(char * a0,int a1){return (open)(a0,a1);}
void teleport_unixunix_var7(char * a0,char * a1){(error)(a0,a1);}
void teleport_unixunix_var8(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_unixunix_var9(char * a0){(error)(a0);}
void teleport_unixunix_var10(char * a0,char * a1){(error)(a0,a1);}
void teleport_unixunix_var11(char * a0,char * a1){(error)(a0,a1);}
void teleport_unixunix_var12(char * a0,char * a1){(error)(a0,a1);}
void teleport_unixunix_var13(char * a0,char * a1){(error)(a0,a1);}
void teleport_unixunix_var14(char * a0){(pline)(a0);}
void teleport_unixunix_var15(char * a0){(pline)(a0);}
void teleport_unixunix_var16(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_unixunix_var17(char * a0){(Norep)(a0);}
int teleport_unixunix_var18(char * a0,char * a1,char * a2){return (execl)(a0,a1,a2);}
int teleport_unixunix_var19(char * a0,char * a1,char * a2){return (execl)(a0,a1,a2);}
void teleport_unixunix_var20(char * a0){(pline)(a0);}
void teleport_unixunix_indirect0(void (* fn)(void)){fn();}
void teleport_unixunix_indirect1(void (* fn)(const char *),char * a0){fn(a0);}
void teleport_unixunix_indirect2(void (* fn)(const char *),char * a0){fn(a0);}
void teleport_unixunix_indirect3(void (* fn)(const char *),char * a0){fn(a0);}
void teleport_unixunix_indirect4(void (* fn)(const char *),char * a0){fn(a0);}
void teleport_unixunix_indirect5(void (* fn)(void)){fn();}
void teleport_unixunix_indirect6(void (* fn)(void)){fn();}
uintptr_t teleport_unixunix_owned_pointer(int i){switch(i){
default:abort();}}
uintptr_t teleport_unixunix_native_pointer(int i){switch(i){
case 0:return(uintptr_t)(done1);
default:abort();}}
#pragma clang diagnostic pop
static char unixunix_literals[542];
char*teleport_unixunix_literal_storage(void){return unixunix_literals;}
size_t teleport_unixunix_literal_capacity(void){return sizeof unixunix_literals;}
static struct stat unixunix_backing_0;
static char unixunix_backing_1[72];
static char unixunix_backing_2[26];
void*teleport_unixunix_storage(int i){switch(i){
case 0:return(void*)&unixunix_backing_0;
case 1:return(void*)&unixunix_backing_1;
case 2:return(void*)&unixunix_backing_2;
default:abort();}}
uintptr_t teleport_unixunix_dep_signal(int sig,void(*handler)(int)){return(uintptr_t)(teleport_native_signal)(sig,handler);}
