/* Controlled UNIXMAIN foreign world; actual algorithms only in source reference or JS. */
#include "hack.h"
#include "tu-unixmain-layout.h"
#include <stdarg.h>
#include <errno.h>
#include <emscripten.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(gh) gh;
__typeof__(svh) svh;
__typeof__(program_state) program_state;
__typeof__(ARGV0) ARGV0;
__typeof__(u) u;
__typeof__(windowprocs) windowprocs;
__typeof__(gp) gp;
__typeof__(svp) svp;
__typeof__(flags) flags;
__typeof__(gl) gl;
__typeof__(gs) gs;
__typeof__(iflags) iflags;
__typeof__(ge) ge;
__typeof__(sysopt) sysopt;
__typeof__(has_strong_rngseed) has_strong_rngseed;
__typeof__(svn) svn;

const char ynchars[]="yn";
static char text[64][1024],scratch[1024],tracebuf[262144],snapshotbuf[16384];static char*argv0[64],*argv1[64];static int argn[2],pos,reentered,restore_count,selection_count,action_count;static long opts[256];static struct nh_file savefile;static struct sigaction actions[8];static int signums[8];
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);if(pos>=sizeof tracebuf-8192)abort();}
EM_JS(void,fixture_throw,(void),{throw Error('UNIXMAIN controlled callback');});
static void callback(void){if(opts[30]){opts[30]=0;emscripten_resize_heap(emscripten_get_heap_size()+8388608);}if(opts[31]){opts[31]=0;fixture_throw();}if(opts[32]&&!reentered){reentered=1;char b[16]="native";append_slash(b);logmsg("reentry:%s;",b);reentered=0;}}
static void vlog(const char*name,const char*f,va_list ap){logmsg("%s:",name);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);logmsg(";");callback();}
static void logargv(int n,char**v){logmsg("argv:%d:",n);for(int i=0;i<n;i++)logmsg("[%s]",v[i]?v[i]:"NULL");logmsg(";");}
static void init_windows(int*argc,char**argv){logmsg("initwin;");logargv(*argc,argv);if(opts[10])*argc=opts[10];callback();}
static void display(const char*s,boolean n){logmsg("display:%s/%d;",s,n);callback();}
static void raw(const char*s){logmsg("raw:%s;",s);callback();}
static void syncwin(void){logmsg("sync;");callback();}
static void selection(void){selection_count++;logmsg("selection:%d;",selection_count);if(opts[11]&&selection_count==1){strcpy(svp.plname,text[10]);iflags.renameinprogress=opts[12];}else if(opts[12])iflags.renameinprogress=0;callback();}
void (*teleport_native_signal(int sig,void(*fn)(int)))(int){logmsg("signal:%d/%d;",sig,fn==SIG_IGN?1:fn==done1?2:fn==hangup?3:fn==SIG_DFL?0:4);callback();return fn;}
int sigaction(int sig,const struct sigaction*restrict a,struct sigaction*restrict old){if(action_count>=8)abort();signums[action_count]=sig;memcpy(&actions[action_count++],a,sizeof *a);logmsg("sigaction:%d/%d;",sig,a->sa_handler==hangup?3:a->sa_handler==done1?2:a->sa_handler==SIG_IGN?1:a->sa_handler==SIG_DFL?0:4);callback();return opts[60];}

void You(const char*f,...){va_list ap;va_start(ap,f);vlog("You",f,ap);va_end(ap);}
void config_error_add(const char*f,...){va_list ap;va_start(ap,f);vlog("config_error_add",f,ap);va_end(ap);}
void error(const char*f,...){va_list ap;va_start(ap,f);vlog("error",f,ap);va_end(ap);fixture_throw();__builtin_unreachable();}
void pline(const char*f,...){va_list ap;va_start(ap,f);vlog("pline",f,ap);va_end(ap);}
void early_init(int a0,char ** a1){logmsg("early_init;");logargv(a0,a1);callback();}
void rng_log_init(void){logmsg("rng_log_init;");callback();}
pid_t getpid(void){logmsg("getpid:%ld;",opts[70]);return opts[70];}
void choose_windows(const char * a0){logmsg("choose:%s;",a0);callback();}
char * nh_getenv(const char * a0){logmsg("env:%s;",a0);callback();return getenv(a0);}
void early_options(int * a0,char *** a1,char ** a2){logmsg("early_options:%d/%s;",*a0,*a2?*a2:"NULL");if(opts[1]){*a0=argn[1];*a1=argv1;*a2=text[11];}callback();}
void initoptions(void){logmsg("initoptions;");callback();}
void panictrace_setsignals(boolean a0){logmsg("panictrace:%d;",a0);callback();}
void hangup(int a0){logmsg("hangup:%d;",a0);callback();}
void getmailstatus(void){logmsg("mail; ");callback();}
void set_playmode(void){logmsg("playmode;");callback();}
void plnamesuffix(void){logmsg("suffix:%s/%d;",svp.plname,gp.plnamelen);if(opts[2])strcpy(svp.plname,text[12]);callback();}
void vision_init(void){logmsg("vision;");callback();}
void init_sound_disp_gamewindows(void){logmsg("soundwindows;");callback();}
void getlock(void){logmsg("lock:%s/%d;",svp.plname,gl.locknum);callback();}
NHFILE * restore_saved_game(void){logmsg("restore:%d:%s;",++restore_count,svp.plname);callback();return restore_count<=opts[3]?&savefile:0;}
const char * fqname(const char * a0,int a1,int a2){logmsg("fqname:%s/%d/%d;",a0,a1,a2);callback();return text[13];}
void done1(int a0){logmsg("done1:%d;",a0);callback();}
int dorecover(NHFILE * a0){logmsg("recover:%d;",a0==&savefile);callback();return opts[4];}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){logmsg("yn:%s/%s/%d/%d;",a0,a1?a1:"NULL",a2,a3);callback();return opts[5]?opts[5]:a2;}
int delete_savefile(void){logmsg("delete_save;");callback();return 0;}
void nh_compress(const char * a0){logmsg("compress:%s;",a0);callback();}
void delete_levelfile(int a0){logmsg("delete_level:%d;",a0);callback();}
int check_panic_save(void){logmsg("check_panic;");callback();return opts[6];}
void ask_about_panic_save(void){logmsg("ask_panic;");callback();}
void newgame(void){logmsg("newgame;");callback();}
void moveloop(boolean a0){logmsg("moveloop:%d;",a0);callback();}
void config_error_init(boolean a0,const char * a1,boolean a2){logmsg("config_init:%d/%s/%d;",a0,a1,a2);callback();}
int load_symset(const char * a0,int a1){logmsg("symbols:%s/%d;",a0,a1);callback();return opts[61];}
void switch_symbols(int a0){logmsg("switch_symbols:%d;",a0);callback();}
int str2role(const char * a0){logmsg("role:%s;",a0);callback();return opts[72];}
int str2race(const char * a0){logmsg("race:%s;",a0);callback();return opts[73];}
int config_error_done(void){logmsg("config_done;");callback();return 0;}
void check_recordfile(const char * a0){logmsg("record:%s;",a0?a0:"NULL");callback();}
char * build_english_list(char * a0){logmsg("english:%s;",a0);callback();return strdup(a0);}
void paniclog(const char * a0,const char * a1){logmsg("paniclog:%s/%s;",a0,a1);callback();}
time_t getnow(void){logmsg("getnow:%ld;",opts[71]);callback();return opts[71];}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/sys/unix/unixmain.c"
#define TELEPORT_UNIXMAIN_VALIDATE_ORIGINAL 1
void teleport_unixmain_process_options(int a0,char ** a1){process_options(a0,a1);}
void teleport_unixmain_wd_message(void){wd_message();}
struct passwd * teleport_unixmain_get_unix_pw(void){return get_unix_pw();}
#else
extern int main(int,char**);
extern int main(int a0,char ** a1);
extern void teleport_unixmain_process_options(int a0,char ** a1);
extern void chdirx(const char * a0,boolean a1);
extern boolean whoami(void);
extern void sethanguphandler(void (*a0)(int));
extern boolean authorize_wizard_mode(void);
extern boolean authorize_explore_mode(void);
extern void teleport_unixmain_wd_message(void);
extern void append_slash(char * a0);
extern boolean check_user_string(const char * a0);
extern struct passwd * teleport_unixmain_get_unix_pw(void);
extern char * get_login_name(void);
extern unsigned long sys_random_seed(void);
extern void get_nhuuid(void);
extern void free_nhuuid(void);
#endif
#include "../nethack-c/wasm/tu-fragments/unixmain-support.c"
long probe_call(int which,long*args){switch(which){
case 0:return(long)main((int)args[0],(char **)args[1]);
case 1:teleport_unixmain_process_options((int)args[0],(char **)args[1]);return 0;
case 2:chdirx((const char *)args[0],(boolean)args[1]);return 0;
case 3:return(long)whoami();
case 4:sethanguphandler((void (*)(int))args[0]);return 0;
case 5:return(long)authorize_wizard_mode();
case 6:return(long)authorize_explore_mode();
case 7:teleport_unixmain_wd_message();return 0;
case 8:append_slash((char *)args[0]);return 0;
case 9:return(long)check_user_string((const char *)args[0]);
case 10:return(long)teleport_unixmain_get_unix_pw();
case 11:return(long)get_login_name();
case 12:return(long)sys_random_seed();
case 13:get_nhuuid();return 0;
case 14:free_nhuuid();return 0;
default:abort();}}

void probe_reset(void){
memset(&gh,0,sizeof gh);memset(&svh,0,sizeof svh);memset(&program_state,0,sizeof program_state);memset(&ARGV0,0,sizeof ARGV0);memset(&u,0,sizeof u);windowprocs=(struct window_procs){0};memset(&gp,0,sizeof gp);memset(&svp,0,sizeof svp);memset(&flags,0,sizeof flags);memset(&gl,0,sizeof gl);memset(&gs,0,sizeof gs);memset(&iflags,0,sizeof iflags);memset(&ge,0,sizeof ge);memset(&sysopt,0,sizeof sysopt);memset(&has_strong_rngseed,0,sizeof has_strong_rngseed);memset(&svn,0,sizeof svn);
memset(text,0,sizeof text);memset(argv0,0,sizeof argv0);memset(argv1,0,sizeof argv1);memset(opts,0,sizeof opts);memset(actions,0,sizeof actions);memset(signums,0,sizeof signums);pos=reentered=restore_count=selection_count=action_count=0;tracebuf[0]=0;argn[0]=argn[1]=1;strcpy(text[0],"nethack");argv0[0]=text[0];argv1[0]=text[0];strcpy(text[10],"Renamed");strcpy(text[11],"/nethack/alt");strcpy(text[12],"Tester");strcpy(text[13],"/nethack/save/test.sav");strcpy(gs.SAVEF,"save/test.sav");opts[70]=42;opts[71]=9007199254740993L;opts[72]=7;opts[73]=3;sysopt.maxplayers=9;windowprocs.name="controlled";windowprocs.win_init_nhwindows=init_windows;windowprocs.win_display_file=display;windowprocs.win_raw_print=raw;windowprocs.win_mark_synch=syncwin;windowprocs.win_player_selection=selection;
}
void probe_option(int i,long v){opts[i]=v;}void probe_clear(void){pos=0;tracebuf[0]=0;}
char*probe_buffer(int i){return text[i];}char**probe_argv(int which){return which?argv1:argv0;}void probe_arg(int which,int index,int buf){(which?argv1:argv0)[index]=buf<0?0:text[buf];if(index>=argn[which])argn[which]=index+1;}
long probe_global(int i){return(long)teleport_unixmain_global(i);}uint64_t probe_layout(int i){return teleport_unixmain_layout(i);}uint64_t probe_read(int k,void*p,int f){return teleport_unixmain_read(k,p,f);}void probe_write(int k,void*p,int f,uint64_t v){teleport_unixmain_write(k,p,f,v);}void*probe_address(int k,void*p,int f){return teleport_unixmain_address(k,p,f);}
const char*probe_trace(void){return tracebuf;}long probe_stack(void){return emscripten_stack_get_current();}void*probe_action(int i){return &actions[i];}int probe_actions(void){return action_count;}
int probe_handler(void(*h)(int)){return h==SIG_DFL?0:h==SIG_IGN?1:h==done1?2:h==hangup?3:-1;}
long probe_function(int i){return i?(long)hangup:(long)done1;}int probe_errno(void){return errno;}
const char*probe_snapshot(void){snprintf(snapshotbuf,sizeof snapshotbuf,"flags:%d/%d/%d/%d/%d;name:%s/%d;state:%d/%d/%d;error:%d/%d/%d;pid:%d;strong:%d;hname:%s;argv0:%s;restore:%d;selection:%d;actions:%d;",flags.debug,flags.explore,flags.initrole,flags.initrace,flags.randomall,svp.plname,gp.plnamelen,program_state.early_options,program_state.preserve_locks,program_state.in_self_recover,iflags.wiz_error_flag,iflags.explore_error_flag,iflags.deferred_X,svh.hackpid,has_strong_rngseed,gh.hname?gh.hname:"NULL",ARGV0?ARGV0:"NULL",restore_count,selection_count,action_count);return snapshotbuf;}

