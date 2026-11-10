/* Controlled native filesystem/process/window/signal fixture; not host support. */
#include "hack.h"
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
__typeof__(program_state) program_state;
__typeof__(gl) gl;
__typeof__(windowprocs) windowprocs;
__typeof__(svp) svp;
__typeof__(iflags) iflags;
const char ynchars[3]="yn";
__typeof__(svh) svh;
__typeof__(sysopt) sysopt;
__typeof__(flags) flags;
#ifdef HYBRID_UNIXUNIX
extern int teleport_unixunix_veryold(int fd);
extern int teleport_unixunix_eraseoldlocks(void);
extern void getlock(void);
extern void ask_about_panic_save(void);
extern void regularize(char * s);
extern int dosh(void);
extern int child(int wt);
extern boolean file_exists(const char * path);
#else
static int veryold(int);
static int eraseoldlocks(void);
#define teleport_unixunix_veryold veryold
#define teleport_unixunix_eraseoldlocks eraseoldlocks
#endif

static char tracebuf[4194304];static size_t traceused;static int options[128],outcome;static int64_t now=1000000;static jmp_buf jumpframe;
static char env_shell[128]="/fixture/shell",env_home[128]="/fixture/home",markers[16]="1",fullpath[256],authorized[128]="fixture",name[32]="hero",fixture_tty_name[16]="tty";
static int answers[256],nanswer,ianswer,characters[1024],nchar,ichar;
_Alignas(16)static unsigned char scratch[4096];
struct fixture_file{char path[256];unsigned char bytes[256];size_t len;struct stat st;int exists;};
static struct fixture_file files[600];static int nfile;struct fixture_fd{int used,file;size_t pos;};static struct fixture_fd fds[700];static int nextfd=3;
static void(*handlers[64])(int);static unsigned char statevents[128][104];static int nevents;static int recursion;
static void logfmt(const char*f,...){va_list ap;va_start(ap,f);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,f,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=n;}
static int lookup(const char*p){for(int i=0;i<nfile;i++)if(!strcmp(files[i].path,p))return i;return-1;}
static int fileadd(const char*p,int exists){int i=lookup(p);if(i<0){if(nfile==600)abort();i=nfile++;strncpy(files[i].path,p,255);}files[i].exists=exists;return i;}
static int fdopenfixture(int i){if(nextfd==700)abort();int fd=nextfd++;fds[fd]=(struct fixture_fd){1,i,0};return fd;}
static void handlerlog(void(*fn)(int)){if(!fn)logfmt("DEFAULT");else if(fn==SIG_IGN)logfmt("IGNORE");else if(fn==done1)logfmt("done1");else logfmt("UNKNOWN:%llu",(unsigned long long)(uintptr_t)fn);}
static void win_wait(void){logfmt("window.wait\n");if(options[70]&&!recursion){recursion=1;regularize((char*)scratch);recursion=0;}}
static void win_exit(const char*s){logfmt("window.exit(%s)\n",s?s:"NULL");}
static void win_raw(const char*s){logfmt("window.raw(%s)\n",s?s:"NULL");}
static void win_suspend(const char*s){logfmt("window.suspend(%s)\n",s?s:"NULL");}
static void win_resume(void){logfmt("window.resume\n");}
int (fstat)(int fd,struct stat*out){logfmt("fstat(%d,OUTstat104)\n",fd);if(options[1]||fd<0||fd>=nextfd||!fds[fd].used){errno=EBADF;return-1;}memcpy(out,&files[fds[fd].file].st,104);if(nevents==128)abort();memcpy(statevents[nevents++],out,104);if(options[71]&&!recursion){recursion=1;(teleport_unixunix_veryold)(options[71]);recursion=0;}return 0;}
time_t(time)(time_t*out){logfmt("time(%s)=%lld\n",out?"OUTtime8":"NULL",(long long)now);if(out)*out=now;return now;}
ssize_t(read)(int fd,void*out,size_t n){logfmt("read(%d,OUTbytes,%llu)\n",fd,(unsigned long long)n);if(options[2]||fd<0||fd>=nextfd||!fds[fd].used){errno=EIO;return-1;}struct fixture_fd*d=&fds[fd];struct fixture_file*f=&files[d->file];size_t count=n;if(count>f->len-d->pos)count=f->len-d->pos;if(options[3]&&count>(unsigned)options[3])count=options[3];memcpy(out,f->bytes+d->pos,count);d->pos+=count;logfmt("readbytes:");for(size_t i=0;i<count;i++)logfmt("%02x",((unsigned char*)out)[i]);logfmt("\n");return count;}
void set_levelfile_name(char*p,int n){char*q=strrchr(p,'.');if(q)*q=0;size_t len=strlen(p);snprintf(p+len,46-len,".%d",n);logfmt("levelname(%d)=%s\n",n,p);}
int(unlink)(const char*p){logfmt("unlink(%s)\n",p);int i=lookup(p);if(options[4]||i<0||!files[i].exists){errno=ENOENT;return-1;}files[i].exists=0;return 0;}
const char*fqname(const char*p,int prefix,int which){snprintf(fullpath,sizeof fullpath,"/%d/%s",prefix,p);logfmt("fqname(%s,%d,%d)=%s\n",p,prefix,which,fullpath);return fullpath;}
int(isatty)(int fd){logfmt("isatty(%d)=%d\n",fd,!options[5]);return!options[5];}
char*(getenv)(const char*p){logfmt("getenv(%s)\n",p);if(!strcmp(p,"NOMUX_MARKERS"))return options[6]?markers:0;if(!strcmp(p,"SHELL"))return options[7]?0:env_shell;if(!strcmp(p,"HOME"))return options[8]?0:env_home;return 0;}
void(error)(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("error:%s\n",b);longjmp(jumpframe,1);}
boolean lock_file(const char*p,int prefix,int retry){logfmt("lock(%s,%d,%d)=%d\n",p,prefix,retry,!options[9]);return!options[9];}
uid_t(getuid)(void){logfmt("getuid=%u\n",(unsigned)options[10]);return(unsigned)options[10];}
int(open)(const char*p,int flags,...){logfmt("open(%s,%d)\n",p,flags);int i=lookup(p);if(options[11]){errno=options[11];return-1;}if(i<0||!files[i].exists){errno=ENOENT;return-1;}return fdopenfixture(i);}
void(perror)(const char*p){logfmt("perror(%s,errno=%d)\n",p,errno);}
void unlock_file(const char*p){logfmt("unlock(%s)\n",p);}
int(close)(int fd){logfmt("close(%d)\n",fd);if(fd<0||fd>=nextfd||!fds[fd].used){errno=EBADF;return-1;}fds[fd].used=0;if(options[12]){errno=EIO;return-1;}return 0;}
char yn_function(const char*q,const char*choices,char def,boolean hist){logfmt("yn(%s,%s,%d,%d)\n",q,choices,(int)def,(int)hist);return ianswer<nanswer?answers[ianswer++]:def;}
int(fflush)(FILE*f){logfmt("fflush(%s)\n",f==stdout?"stdout":f?"OTHER":"NULL");return 0;}
int(getchar)(void){int c=ichar<nchar?characters[ichar++]:EOF;logfmt("getchar=%d\n",c);return c;}
int(putchar)(int c){logfmt("putchar=%d\n",c);return c;}
int(creat)(const char*p,mode_t mode){logfmt("creat(%s,%u)\n",p,(unsigned)mode);if(options[13]){errno=EACCES;return-1;}int i=fileadd(p,1);files[i].len=0;files[i].st.st_mode=S_IFREG|mode;files[i].st.st_mtim.tv_sec=now;files[i].st.st_mtim.tv_nsec=0;files[i].st.st_size=0;return fdopenfixture(i);}
ssize_t(write)(int fd,const void*p,size_t n){logfmt("write(%d,%llu):",fd,(unsigned long long)n);for(size_t i=0;i<n;i++)logfmt("%02x",((const unsigned char*)p)[i]);logfmt("\n");if(options[14]){errno=EIO;return-1;}if(fd<0||fd>=nextfd||!fds[fd].used){errno=EBADF;return-1;}struct fixture_file*f=&files[fds[fd].file];size_t count=options[15]?(unsigned)options[15]:n;if(count>n||count>sizeof f->bytes)abort();memcpy(f->bytes,p,count);f->len=count;f->st.st_size=count;return count;}
char lowc(char c){return c>='A'&&c<='Z'?c-'A'+'a':c;}
void delete_levelfile(int n){logfmt("deletelevel(%d)\n",n);}
void nh_terminate(int status){logfmt("terminate(%d)\n",status);longjmp(jumpframe,2);}
boolean check_user_string(const char*p){logfmt("authorize(%s)\n",p);return!options[16];}
int(execl)(const char*path,const char*arg0,...){va_list ap;va_start(ap,arg0);char*end=va_arg(ap,char*);va_end(ap);if(end)abort();logfmt("execl(%s,%s,NULL)\n",path,arg0);errno=ENOENT;return-1;}
void(exit)(int status){logfmt("exit(%d)\n",status);longjmp(jumpframe,3);}
pid_t(fork)(void){logfmt("fork=%d\n",options[17]);return options[17];}
int(setgid)(gid_t id){logfmt("setgid(%u)\n",(unsigned)id);return options[18];}
gid_t(getgid)(void){logfmt("getgid=%u\n",(unsigned)options[19]);return(unsigned)options[19];}
int(setuid)(uid_t id){logfmt("setuid(%u)\n",(unsigned)id);return options[20];}
int(chdir)(const char*p){logfmt("chdir(%s)\n",p?p:"NULL");if(!p){errno=EFAULT;return-1;}return options[21];}
void(*teleport_native_signal(int sig,void(*handler)(int)))(int){if(sig<0||sig>=64)abort();logfmt("signal(%d,",sig);handlerlog(handler);logfmt(")\n");void(*old)(int)=handlers[sig];handlers[sig]=handler;return old;}
pid_t(wait)(int*p){logfmt("wait(%s)\n",p?"OUTint4":"NULL");if(p)*p=options[22];return options[23];}
void done1(int n){logfmt("done1(%d)\n",n);options[90]++;}
int(stat)(const char*p,struct stat*out){logfmt("stat(%s,OUTstat104)\n",p);int i=lookup(p);if(options[24]||i<0||!files[i].exists){errno=ENOENT;return-1;}memcpy(out,&files[i].st,104);if(nevents==128)abort();memcpy(statevents[nevents++],out,104);return 0;}

void raw_printf(const char*fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("raw_printf:%s\n",b);}
void pline(const char*fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline:%s\n",b);}
void Norep(const char*fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("Norep:%s\n",b);}
#ifndef HYBRID_UNIXUNIX
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/sys/unix/unixunix.c"
#endif

void*probe_sourcebuf(void){
#ifdef HYBRID_UNIXUNIX
extern void*teleport_unixunix_storage(int);return teleport_unixunix_storage(0);
#else
return &buf;
#endif
}
__attribute__((noinline))static void zero_stack(void){volatile char x[65536];for(int i=0;i<sizeof x;i++)x[i]=0;}
int64_t probe_action(int fn,int64_t a,int64_t b){zero_stack();outcome=0;int jumped=setjmp(jumpframe);if(jumped){outcome=jumped;return-999;}switch(fn){

case 0:return(int64_t)(teleport_unixunix_veryold)((int)a);
case 1:return(int64_t)(teleport_unixunix_eraseoldlocks)();
case 2:(getlock)();return 0;
case 3:(ask_about_panic_save)();return 0;
case 4:(regularize)((char *)a);return 0;
case 5:return(int64_t)(dosh)();
case 6:return(int64_t)(child)((int)a);
case 7:return(int64_t)(file_exists)((const char *)a);
default:abort();}}

const char*probe_trace(void){return tracebuf;}void probe_clear(void){traceused=0;tracebuf[0]=0;}int probe_outcome(void){return outcome;}int probe_errno(void){return errno;}void probe_option(int i,int n){options[i]=n;}int probe_option_get(int i){return options[i];}void probe_now(int64_t n){now=n;}void probe_answer(int c){if(nanswer==256)abort();answers[nanswer++]=c;}void probe_char(int c){if(nchar==1024)abort();characters[nchar++]=c;}
int probe_file(const char*p,int exists,int64_t stamp,int bytes){int i=fileadd(p,exists);memset(&files[i].st,0xA5,104);files[i].st.st_dev=1;files[i].st.st_mode=S_IFREG|0660;files[i].st.st_nlink=1;files[i].st.st_uid=123;files[i].st.st_gid=456;files[i].st.st_rdev=0;files[i].st.st_size=bytes;files[i].st.st_blksize=4096;files[i].st.st_blocks=1;files[i].st.st_atim.tv_sec=stamp;files[i].st.st_atim.tv_nsec=123;files[i].st.st_mtim.tv_sec=stamp;files[i].st.st_mtim.tv_nsec=456;files[i].st.st_ctim.tv_sec=stamp;files[i].st.st_ctim.tv_nsec=789;files[i].st.st_ino=42;files[i].len=bytes;for(int j=0;j<bytes;j++)files[i].bytes[j]=j+1;return i;}
int probe_open(int i){return fdopenfixture(i);}int probe_file_count(void){return nfile;}int probe_fd_count(void){return nextfd;}int probe_fd_open(int i){return fds[i].used;}int probe_event_count(void){return nevents;}int probe_handler(int sig){return handlers[sig]==0?0:handlers[sig]==SIG_IGN?1:handlers[sig]==done1?2:3;}uintptr_t probe_done_id(void){return(uintptr_t)done1;}uintptr_t probe_handler_raw(int sig){return(uintptr_t)handlers[sig];}void probe_signal_run(int sig,int n){if(handlers[sig]!=done1)abort();handlers[sig](n);}void*probe_growth(void){return malloc(50000000);}
void probe_reset(void){if((uintptr_t)done1<=1)abort();memset(options,0,sizeof options);memset(files,0,sizeof files);memset(fds,0,sizeof fds);memset(handlers,0,sizeof handlers);memset(statevents,0,sizeof statevents);memset(scratch,0,sizeof scratch);nfile=nanswer=ianswer=nchar=ichar=nevents=recursion=outcome=0;nextfd=3;now=1000000;

memset((void*)&program_state,0,sizeof program_state);
memset((void*)&gl,0,sizeof gl);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&svp,0,sizeof svp);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&svh,0,sizeof svh);
memset((void*)&sysopt,0,sizeof sysopt);
memset((void*)&flags,0,sizeof flags);

strcpy(gl.lock,"fixture");strcpy(svp.plname,"hero");svh.hackpid=0x12345678;sysopt.shellers=authorized;windowprocs.name=fixture_tty_name;windowprocs.win_wait_synch=win_wait;windowprocs.win_exit_nhwindows=win_exit;windowprocs.win_raw_print=win_raw;windowprocs.win_suspend_nhwindows=win_suspend;windowprocs.win_resume_nhwindows=win_resume;errno=0;regularize((char*)scratch);memset(probe_sourcebuf(),0,104);probe_clear();}
void*probe_pointer(int i){switch(i){

case 0:return &scratch;
case 1:return &env_shell;
case 2:return &env_home;
case 3:return &markers;
case 4:return &fullpath;
case 5:return &authorized;
case 6:return &name;
case 7:return &fixture_tty_name;
case 8:return &files;
case 9:return &fds;
case 10:return &statevents;
default:abort();}}
size_t probe_region_size(int i){switch(i){
case 0:return sizeof scratch;
case 1:return sizeof env_shell;
case 2:return sizeof env_home;
case 3:return sizeof markers;
case 4:return sizeof fullpath;
case 5:return sizeof authorized;
case 6:return sizeof name;
case 7:return sizeof fixture_tty_name;
case 8:return sizeof files;
case 9:return sizeof fds;
case 10:return sizeof statevents;
default:abort();}}
size_t probe_global_size(int i){switch(i){
case 0:return sizeof program_state;
case 1:return sizeof gl;
case 2:return sizeof windowprocs;
case 3:return sizeof svp;
case 4:return sizeof iflags;
case 5:return sizeof ynchars;
case 6:return sizeof stdout;
case 7:return sizeof svh;
case 8:return sizeof sysopt;
case 9:return sizeof flags;
default:abort();}}
