#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include <emscripten.h>
__typeof__(gs) gs; __typeof__(gp) gp; __typeof__(gv) gv; __typeof__(gy) gy;
__typeof__(gm) gm; __typeof__(gg) gg; __typeof__(ge) ge; __typeof__(svm) svm; __typeof__(a11y) a11y;
__typeof__(flags) flags; __typeof__(iflags) iflags; struct sinfo program_state;
struct sysopt_s sysopt; struct you u; __typeof__(windowprocs) windowprocs;
winid WIN_MESSAGE=7;
const char ynchars[]="yn";
static struct monst target;
static int options[24],reentry;
static char trace_storage[524288],snapshot[65536],input[8192],argument[8192];
static void append(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(trace_storage+strlen(trace_storage),sizeof trace_storage-strlen(trace_storage),f,ap);va_end(ap);}
static void put(int win,int attr,const char *line){append("put:%d:%d:%s;",win,attr,line);if(options[5]&&!reentry){reentry=1;pline("nested %d",71);reentry=0;}if(options[6]){options[6]=0;emscripten_resize_heap(emscripten_get_heap_size()+16777216);append("grow;");}}
static void raw(const char *line){append("raw:%s;",line);}
static void display(int win,boolean block){append("display:%d:%d;",win,block);}
EM_JS(void,teleport_pline_probe_throw,(int kind),{throw new Error('PLINE fixture exit '+kind);});
void panic(const char*f,...){char buffer[256];va_list ap;va_start(ap,f);vsnprintf(buffer,sizeof buffer,f,ap);va_end(ap);append("panic:%s;",buffer);teleport_pline_probe_throw(2);__builtin_unreachable();}
void nh_terminate(int status){append("terminate:%d;",status);teleport_pline_probe_throw(1);__builtin_unreachable();}
void paniclog(const char *reason,const char *line){append("paniclog:%s:%s;",reason,line);}
void dirtocoord(coord *cc,int dir){cc->x=dir%3-1;cc->y=dir/3-1;append("dir:%d;",dir);}
boolean unconscious(void){append("unconscious;");return options[8];}
boolean is_fainted(void){append("fainted;");return options[9];}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
char *coord_desc(coordxy x,coordxy y,char *buf,char mode){snprintf(buf,QBUFSZ,"at%d,%d:%c",x,y,mode);append("coord:%d:%d:%d;",x,y,mode);return buf;}
int msgtype_type(const char *line,boolean no_repeat){append("type:%d:%s;",no_repeat,line);return options[0];}
void vision_recalc(int control){append("vision:%d;",control);gv.vision_full_recalc=0;if(options[4]&&!reentry){reentry=1;pline("vision message");reentry=0;}}
void flush_screen(int cursor){append("flush:%d;",cursor);}
void livelog_add(long flags,const char *line){append("live:%ld:%s;",flags,line);}
long *alloc(unsigned int size){append("alloc:%u;",size);return malloc(size);}
char *dupstr(const char *line){size_t size=strlen(line)+1;char *p=malloc(size);append("dup:%zu;",size);memcpy(p,line,size);return p;}
#undef free
extern void free(void *);
void teleport_probe_free(void *value){append("free;");free(value);}
#define free teleport_probe_free
char yn_function(const char *query,const char *choices,char deflt,boolean history){append("yn:%s:%s:%c:%d;",query,choices,deflt,history);return options[3]?'y':'n';}
boolean submit_web_report(int cos,const char *subject,const char *why){append("report:%d:%s:%s;",cos,subject,why);return TRUE;}
pid_t teleport_probe_fork(void){append("fork;");return options[1];}
pid_t teleport_probe_waitpid(pid_t pid,int *status,int flags){append("wait:%d:%d;",pid,flags);*status=options[2];return pid;}
gid_t teleport_probe_getgid(void){append("getgid;");return 23;}
uid_t teleport_probe_getuid(void){append("getuid;");return 29;}
int teleport_probe_setgid(gid_t id){append("setgid:%u;",id);return 0;}
int teleport_probe_setuid(uid_t id){append("setuid:%u;",id);return 0;}
int teleport_probe_execv(const char *path,char *const *args){append("exec:%s:%s:%s:%d;",path,args[0],args[1],args[2]==NULL);return -1;}
void teleport_probe_perror(const char *text){append("perror:%s;",text?text:"<null>");}
int teleport_probe_fprintf(FILE *stream,const char *fmt,...){char buf[256];va_list ap;va_start(ap,fmt);vsnprintf(buf,sizeof buf,fmt,ap);va_end(ap);append("stderr:%s;",buf);return strlen(buf);}
/* Source header macro helper: kept identical to original strNsubst service. */
int strNsubst(char *buf,const char *old,const char *replacement,int n){char *p=buf;size_t a=strlen(old),b=strlen(replacement);if(a!=1||b!=1||n!=0)abort();while(*p){if(*p==*old)*p=*replacement;p++;}return 0;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/pline.c"
#else
extern void teleport_pline_test_putmesg(const char *);
extern char *teleport_pline_test_You_buf(int);
extern void teleport_pline_test_execplinehandler(const char *);
#endif
#include "tu-pline-layout.h"
#include "../nethack-c/wasm/tu-fragments/pline-support.c"
void probe_reset(void){memset(&gs,0,sizeof gs);memset(&gp,0,sizeof gp);memset(&gv,0,sizeof gv);memset(&gy,0,sizeof gy);memset(&gg,0,sizeof gg);memset(&ge,0,sizeof ge);memset(&svm,0,sizeof svm);memset(&a11y,0,sizeof a11y);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(&sysopt,0,sizeof sysopt);memset(&u,0,sizeof u);memset(options,0,sizeof options);options[1]=41;trace_storage[0]=0;u.ux=10;u.uy=11;target.mx=15;target.my=9;flags.acoustics=1;iflags.window_inited=1;iflags.getpos_coords=GPCOORDS_NONE;windowprocs.win_putstr=put;windowprocs.win_raw_print=raw;windowprocs.win_display_nhwindow=display;windowprocs.wincap2=WC2_URGENT_MESG|WC2_SUPPRESS_HIST;}
void probe_caps(uint64_t value){windowprocs.wincap2=value;}
void probe_clear(void){trace_storage[0]=0;}
void probe_option(int key,int value){if(key>=0&&key<SIZE(options))options[key]=value;}
void probe_field(int key,int value){switch(key){case 0:iflags.window_inited=value;break;case 1:iflags.debug_prevent_pline=value;break;case 2:program_state.done_hup=value;break;case 3:program_state.wizkit_wishing=value;break;case 4:a11y.accessiblemsg=value;break;case 5:a11y.msg_loc.x=value;break;case 6:a11y.msg_loc.y=value;break;case 7:gv.vision_full_recalc=value;break;case 8:flags.acoustics=value;break;case 9:gm.multi=value;break;case 10:u.uinwater=value;break;case 11:u.uprops[BLINDED].intrinsic=value;break;case 12:u.uprops[DEAF].intrinsic=value;break;case 13:program_state.beyond_savefile_load=value;break;case 14:program_state.something_worth_saving=value;break;case 15:program_state.in_sanity_check=value;break;case 16:iflags.debug_fuzzer=value;break;case 17:iflags.last_msg=value;break;case 18:sysopt.msghandler=value?"/fixture/handler":NULL;break;case 19:sysopt.support=value?"fixture support":NULL;break;case 20:sysopt.crashreporturl=value?"https://fixture.invalid":NULL;break;}}
char *probe_input(void){return input;}
char *probe_argument(void){return argument;}
const char *probe_trace(void){return trace_storage;}
const char *probe_snapshot(void){char *p=snapshot;int i;struct gamelog_line *g;p+=sprintf(p,"flags=%u;idx=%u;prev=%s;loc=%d,%d;you=%d:%s;early=%d;last=%d;impossible=%d;",gp.pline_flags,gs.saved_pline_index,gp.prevmsg,a11y.msg_loc.x,a11y.msg_loc.y,gy.you_buf_siz,gy.you_buf?gy.you_buf:"<null>",ge.early_raw_messages,iflags.last_msg,program_state.in_impossible);for(i=0;i<DUMPLOG_MSG_COUNT;i++)if(gs.saved_plines[i])p+=sprintf(p,"m%d=%s;",i,gs.saved_plines[i]);for(g=gg.gamelog;g;g=g->next)p+=sprintf(p,"g=%ld/%ld:%s;",g->flags,g->turn,g->text);return snapshot;}
void probe_message(int function,int pattern){
#define SEND(fn) do {switch(pattern){case 0:fn(input);break;case 1:fn("%s",input);break;case 2:fn("text=%s int=%d long=%ld float=%.4g hex=%#x ptr=%p %%",input,-71,9007199254740997L,1.2345,0xabc,(void*)0x1234);break;case 3:fn("%.4s/%*.*d",input,8,3,-12);break;default:abort();}}while(0)
 switch(function){case 0:SEND(pline);break;case 1:SEND(You);break;case 2:SEND(Your);break;case 3:SEND(You_feel);break;case 4:SEND(You_cant);break;case 5:SEND(pline_The);break;case 6:SEND(There);break;case 7:SEND(You_hear);break;case 8:SEND(You_see);break;case 9:SEND(verbalize);break;case 10:SEND(raw_printf);break;case 11:SEND(impossible);break;case 12:SEND(Norep);break;case 13:SEND(urgent_pline);break;case 14:pline_dir(options[10],"%s",input);break;case 15:pline_xy(options[10],options[11],"%s",input);break;case 16:pline_mon(options[10]?&gy.youmonst:&target,"%s",input);break;case 17:custompline(options[10],"%s",input);break;case 18:livelog_printf(9007199254740997L,"%s\t%ld",input,-9007199254740997L);break;case 19:nhassert_failed(input,argument,options[10]);break;default:abort();}
#undef SEND
}
void probe_direct(int action){switch(action){case 0:dumplogmsg(input);break;case 1:dumplogfreemessages();break;case 2:free_youbuf();break;case 3:gamelog_add(-9007199254740997L,9007199254740999L,input);break;case 4:
#ifdef TELEPORT_REFERENCE_TU
putmesg(input);
#else
teleport_pline_test_putmesg(input);
#endif
break;case 5:
#ifdef TELEPORT_REFERENCE_TU
(void)You_buf(options[10]);
#else
(void)teleport_pline_test_You_buf(options[10]);
#endif
break;case 6:
#ifdef TELEPORT_REFERENCE_TU
execplinehandler(input);
#else
teleport_pline_test_execplinehandler(input);
#endif
break;case 7:set_msg_dir(options[10]);break;case 8:set_msg_xy(options[10],options[11]);break;default:abort();}}
size_t probe_context_size(void){return 5*BUFSZ;}
size_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return SIZE(pline_layout);}
const char *probe_layout_name(int i){return pline_layout[i].name;}
size_t probe_layout_value(int i){return pline_layout[i].value;}
