/* Private TOPL differential. No original TOPL bodies in hybrid. */
#define NEED_VARARGS
#include "hack.h"
#include "tcap.h"
#include "wintty.h"
#include <stdint.h>
#include <stdarg.h>
#include <setjmp.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(wins) wins;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(iflags) iflags;
__typeof__(ttyDisplay) ttyDisplay;
__typeof__(windowprocs) windowprocs;
__typeof__(gt) gt;
__typeof__(morc) morc;
__typeof__(program_state) program_state;
__typeof__(BASE_WINDOW) BASE_WINDOW;
__typeof__(flags) flags;
__typeof__(yn_number) yn_number;
char erase_char;
__typeof__(gs) gs;
char defmorestr[]="--More--";const char quitchars[]=" \r\n\033";
static volatile struct window_procs callback_procs;static struct WinDesc message_window,base_window;static struct DisplayDesc display_state;
static char*history[8];static short datlens[8];static int opts[128],callback_depth,retargeted,inputlen,inputpos;static unsigned char inputbuf[4096];
static char tracebuf[2097152],statebuf[32768],resultbuf[4096];static unsigned char output[32768];static int outputlen;
static jmp_buf fixture_jump;static void*growth,*last_pointer;
struct allocation {void*p;unsigned size;int live;};static struct allocation allocations[1024];static int nalloc;
static void callback(void);
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static int id(const void*p){if(!p)return-1;uintptr_t a=(uintptr_t)p;for(int i=nalloc-1;i>=0;i--){uintptr_t b=(uintptr_t)allocations[i].p;if(allocations[i].live&&a>=b&&a<b+allocations[i].size)return 10000+i*1024+(int)(a-b);}if(a>=(uintptr_t)gt.toplines&&a<(uintptr_t)(gt.toplines+TBUFSZ))return 2000+(int)(a-(uintptr_t)gt.toplines);return 999;}
long*alloc(unsigned n){if(nalloc>=1024)longjmp(fixture_jump,1);void*p=malloc(n);if(!p)longjmp(fixture_jump,1);allocations[nalloc]=(struct allocation){p,n,1};logmsg("alloc:%u:%d;",n,nalloc++);return p;}
void __real_free(void*);void __wrap_free(void*p){logmsg("free:%d;",id(p));for(int i=nalloc-1;i>=0;i--)if(allocations[i].p==p&&allocations[i].live){allocations[i].live=0;break;}__real_free(p);}
int putchar(int c){logmsg("out:%d@%d,%d;",c,ttyDisplay->curx,ttyDisplay->cury);if(outputlen<32768)output[outputlen++]=(unsigned char)c;else longjmp(fixture_jump,1);callback();return(unsigned char)c;}
void nomux_putch(int c){logmsg("shadow:%d@%d,%d;",c,ttyDisplay->curx,ttyDisplay->cury);if(opts[95])longjmp(fixture_jump,1);callback();}
void home(void){logmsg("home;");ttyDisplay->curx=ttyDisplay->cury=0;callback();}
void cl_end(void){logmsg("clend;");callback();}void backsp(void){logmsg("backsp;");callback();}
void standoutbeg(void){logmsg("standout+;");}void standoutend(void){logmsg("standout-;");}void end_glyphout(void){logmsg("glyphend;");}
void g_putch(int c){logmsg("glyph:%d;",c);callback();}
void tty_curs(winid w,int x,int y){logmsg("curs:%d:%d:%d;",w,x,y);ttyDisplay->curx=x-1;ttyDisplay->cury=y;callback();}
void tty_clear_nhwindow(winid w){logmsg("clear:%d;",w);wins[w]->curx=wins[w]->cury=0;ttyDisplay->curx=ttyDisplay->cury=0;callback();}
void docorner(int x,int y,int between){logmsg("corner:%d:%d:%d;",x,y,between);ttyDisplay->curx=ttyDisplay->cury=0;callback();}
void tty_nhbell(void){logmsg("bell;");callback();}
void dumplogmsg(const char*s){logmsg("dump:%s;",s);callback();}
char readchar(void){if(inputpos>=inputlen){logmsg("INPUT_EXHAUSTED;");longjmp(fixture_jump,1);}char c=(char)inputbuf[inputpos++];logmsg("read:%d;",(int)c);callback();return c;}
void xwaitforspace(const char*s){logmsg("wait:%d,%d;",(int)s[0],(int)s[1]);morc=readchar();}
boolean digit(char c){return c>='0'&&c<='9';}char lowc(char c){return(c>='A'&&c<='Z')?c+32:c;}
char*eos(char*s){return s+strlen(s);}char*key2txt(uchar c,char*out){sprintf(out,"key%u",c);logmsg("key:%u;",c);return out;}
void panic(const char*f,...){va_list ap;va_start(ap,f);logmsg("panic:");vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");longjmp(fixture_jump,1);}
void nhassert_failed(const char*e,const char*f,int line){logmsg("assert:%s:%s:%d;",e,f,line);longjmp(fixture_jump,1);}
void custompline(unsigned flags_,const char*f,...){char b[4096];va_list ap;va_start(ap,f);vsnprintf(b,sizeof b,f,ap);va_end(ap);logmsg("pline:%u:%s;",flags_,b);if(opts[16])update_topl(b);callback();}
static winid window_create(int type){logmsg("create:%d;",type);callback();return 2;}
static void window_putstr_alt(winid w,int attr,const char*s){logmsg("put-alt:%d:%d:%s;",w,attr,s?s:"(null)");callback();}
static void window_putstr(winid w,int attr,const char*s){logmsg("put:%d:%d:%s;",w,attr,s?s:"(null)");if(opts[91]){windowprocs.win_putstr=window_putstr_alt;retargeted=1;}callback();}
static void window_display(winid w,boolean block){logmsg("display:%d:%d;",w,block);callback();}
static void window_destroy(winid w){logmsg("destroy:%d;",w);callback();}
#ifdef TELEPORT_REFERENCE_TU
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/win/tty/topl.c"
#else
extern void teleport_topl_test_redotoplin(const char *);
#define redotoplin teleport_topl_test_redotoplin
extern void teleport_topl_test_topl_putsym(char);
#define topl_putsym teleport_topl_test_topl_putsym
extern void teleport_topl_test_removetopl(int);
#define removetopl teleport_topl_test_removetopl
extern void teleport_topl_test_msghistory_snapshot(boolean);
#define msghistory_snapshot teleport_topl_test_msghistory_snapshot
extern void teleport_topl_test_free_msghistory_snapshot(boolean);
#define free_msghistory_snapshot teleport_topl_test_free_msghistory_snapshot
#endif
#include "../nethack-c/wasm/tu-fragments/topl-support.inc"
#include "tu-topl-layout.h"
static void callback(void){if(opts[93])longjmp(fixture_jump,1);if(opts[90]&&!callback_depth){opts[90]=0;callback_depth++;logmsg("reentry;");remember_topl();if(opts[92]&&!growth){growth=malloc(40000000);logmsg("growth:%d;",growth!=0);}if(opts[94]){gt.tc_gbl_data.tc_CO=40;message_window.flags|=WIN_NOSTOP;logmsg("alias-write;");}callback_depth--;}}
void probe_clear(void){tracebuf[0]=0;resultbuf[0]=0;outputlen=0;}
void probe_reset(void){

#ifdef TELEPORT_PRODUCTION_PROJECTION
 while(tty_getmsghistory(FALSE)){}
#else
 free_msghistory_snapshot(FALSE);
#endif
 for(int i=0;i<8;i++)if(history[i]){free(history[i]);history[i]=0;}if(growth){free(growth);growth=0;}nalloc=0;callback_depth=0;retargeted=0;last_pointer=0;inputlen=inputpos=0;memset(opts,0,sizeof opts);memset(&message_window,0,sizeof message_window);memset(&base_window,0,sizeof base_window);memset(&display_state,0,sizeof display_state);memset(datlens,0,sizeof datlens);probe_clear();
 WIN_MESSAGE=1;BASE_WINDOW=0;wins[0]=&base_window;wins[1]=&message_window;ttyDisplay=&display_state;message_window.rows=3;message_window.cols=80;message_window.data=history;message_window.datlen=datlens;base_window.rows=24;base_window.cols=80;gt.toplines[0]=0;gt.tc_gbl_data.tc_CO=80;gt.tc_gbl_data.tc_LI=24;display_state.rows=24;display_state.cols=80;program_state.in_checkpoint=0;flags.standout=0;iflags.prevmsg_window='s';iflags.debug_fuzzer=0;gs.saved_pline_index=77;yn_number=0;morc=0;erase_char=127;
 windowprocs.win_create_nhwindow=window_create;windowprocs.win_putstr=window_putstr;windowprocs.win_display_nhwindow=window_display;windowprocs.win_destroy_nhwindow=window_destroy;callback_procs.win_doprev_message=tty_doprev_message;callback_procs.win_yn_function=tty_yn_function;callback_procs.win_getmsghistory=tty_getmsghistory;callback_procs.win_putmsghistory=tty_putmsghistory;
 for(int i=0;i<3;i++){history[i]=(char*)alloc(16);history[i][0]=0;datlens[i]=16;}
}
void probe_input(const char*s,int length){if(length<0||length>4096)abort();memcpy(inputbuf,s,length);inputlen=length;inputpos=0;}
void probe_option(int i,int value){opts[i]=value;}
void probe_scene(int which,long a,long b){switch(which){case 0:ttyDisplay->toplin=a;break;case 1:message_window.flags=a;break;case 2:message_window.curx=a;message_window.cury=b;ttyDisplay->curx=a;ttyDisplay->cury=b;break;case 3:gt.tc_gbl_data.tc_CO=a;break;case 4:iflags.prevmsg_window=a;ttyDisplay->inread=b;break;case 5:program_state.in_checkpoint=a;break;case 6:flags.standout=a;break;case 7:ttyDisplay->topl_utf8=a;ttyDisplay->mixed=b;break;case 8:iflags.debug_fuzzer=a;ttyDisplay->inmore=b;break;case 9:message_window.maxrow=a;message_window.maxcol=b;break;case 10:gs.saved_pline_index=a;break;case 11:ttyDisplay->intr=a;break;case 12:WIN_MESSAGE=a;break;case 13:if(a<1||a>8)abort();message_window.rows=a;break;case 14:wins[1]=a?&message_window:0;break;}}
void probe_topline(const char*s){strncpy(gt.toplines,s,TBUFSZ-1);gt.toplines[TBUFSZ-1]=0;}
void probe_history(int i,const char*s){unsigned n=(unsigned)strlen(s)+1;if(n>65535)abort();if(history[i])free(history[i]);history[i]=(char*)alloc(n);strcpy(history[i],s);datlens[i]=n;}
int probe_layout_count(void){return SIZE(topl_layout);}const char*probe_layout_name(int i){return topl_layout[i].name;}long long probe_layout_value(int i){return topl_layout[i].value;}
size_t probe_stack(void){return emscripten_stack_get_current();}const char*probe_trace(void){return tracebuf;}const char*probe_result(void){return resultbuf;}
void*probe_pointer(int i){switch(i){case 0:return &message_window;case 1:return ttyDisplay;case 2:return gt.toplines;case 3:return last_pointer;case 4:return history;case 5:return datlens;default:return 0;}}
int probe_window_identity(void){return windowprocs.win_putstr==(retargeted?window_putstr_alt:window_putstr);}
const char*probe_snapshot(void){char*p=statebuf;p+=sprintf(p,"msg:%s;cw:%d,%ld,%ld,%ld,%ld,%ld;display:%d,%d,%d,%d,%d,%d,%d,%d,%d;global:%ld,%d,%u,%d,%d;ret:%d:%s;out:",gt.toplines,message_window.flags,message_window.curx,message_window.cury,message_window.maxrow,message_window.maxcol,message_window.rows,ttyDisplay->curx,ttyDisplay->cury,ttyDisplay->toplin,ttyDisplay->inmore,ttyDisplay->inread,ttyDisplay->intr,ttyDisplay->dismiss_more,ttyDisplay->topl_utf8,ttyDisplay->mixed,yn_number,(int)morc,gs.saved_pline_index,inputpos,retargeted,id(last_pointer),resultbuf);for(int i=0;i<outputlen;i++)p+=sprintf(p,"%02x",output[i]);for(int i=0;i<8;i++)p+=sprintf(p,";h:%d,%d,%s",id(history[i]),datlens[i],history[i]?history[i]:"(null)");return statebuf;}
long long probe_action(int op,const char*s,const char*resp,int def){long long result=0;if(setjmp(fixture_jump))return-999;switch(op){
case 0:result=tty_doprev_message();break;
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 1:redotoplin(s);break;
#endif
case 2:show_topl(s);break;
case 3:remember_topl();break;
case 4:addtopl(s);break;
case 5:more();break;
case 6:update_topl(s);break;
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 7:topl_putsym(def);break;
#endif
case 8:putsyms(s);break;
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 9:removetopl(def);break;
#endif
case 10:result=tty_yn_function(s,resp,def);break;
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 11:msghistory_snapshot(def);break;
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 12:free_msghistory_snapshot(def);break;
#endif
case 13:last_pointer=tty_getmsghistory(def);if(last_pointer)snprintf(resultbuf,sizeof resultbuf,"%s",(char*)last_pointer);else resultbuf[0]=0;result=id(last_pointer);break;
case 14:tty_putmsghistory(s,def);break;
default:abort();}return result;}
void probe_view_write(int op,int v){switch(op){case 0:message_window.curx=v;break;case 1:display_state.curx=v;break;case 2:gt.toplines[0]=(char)v;break;case 3:history[1][0]=(char)v;break;default:abort();}}
void probe_mutate_retained(int c){if(last_pointer){int found=0;for(int i=0;i<nalloc;i++)if(allocations[i].live&&allocations[i].p==last_pointer)found=1;if(!found)abort();((char*)last_pointer)[0]=(char)c;}}
int probe_callback_identity(int i){switch(i){case 0:return callback_procs.win_doprev_message==tty_doprev_message;case 1:return callback_procs.win_yn_function==tty_yn_function;case 2:return callback_procs.win_getmsghistory==tty_getmsghistory;case 3:return callback_procs.win_putmsghistory==tty_putmsghistory;default:abort();}}
long long probe_callback_action(int i,const char*s,const char*resp,int def){if(setjmp(fixture_jump))return-999;switch(i){case 0:return callback_procs.win_doprev_message();case 1:return callback_procs.win_yn_function(s,resp,(char)def);case 2:last_pointer=callback_procs.win_getmsghistory(def);if(last_pointer)snprintf(resultbuf,sizeof resultbuf,"%s",(char*)last_pointer);else resultbuf[0]=0;return id(last_pointer);case 3:callback_procs.win_putmsghistory(s,def);return 0;default:abort();}}
