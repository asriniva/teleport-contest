#include "hack.h"
#include "wintty.h"
#include "func_tab.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-getline-layout.h"
__typeof__(iflags) iflags;
__typeof__(gi) gi;
__typeof__(gt) gt;
__typeof__(windowprocs) windowprocs;
struct sinfo program_state;
winid WIN_MESSAGE;
struct WinDesc *wins[MAXWIN];
struct DisplayDesc *ttyDisplay;
extern char erase_char, kill_char;
#ifndef TELEPORT_REFERENCE_TU
extern char morc;
#endif
static struct WinDesc message_window;
static struct DisplayDesc display;
static int input[20000], input_length, input_index, interrupt_at, menu_result;
static char output[BUFSZ + 32], screen[4096], probe_trace_storage[8 * 1024 * 1024];
static int screen_cursor;
static int matches[16];
static struct ext_func_tab entries[7];
static const char *const command_names[]={"adjust","annotate","apply","cast","conduct","pray","foo"};
void panic(const char *format, ...) { abort(); }
static void append(const char *format, ...) {va_list ap;va_start(ap,format);vsnprintf(probe_trace_storage+strlen(probe_trace_storage),sizeof probe_trace_storage-strlen(probe_trace_storage),format,ap);va_end(ap);}
int teleport_probe_fflush(FILE *stream){append("flush:%d;",stream==stdout);return 0;}
static void paint(const char *s){while(*s){unsigned char c=*s++;if(c=='\b'){if(screen_cursor)screen_cursor--;}else if(c=='\r')screen_cursor=0;else{if(screen_cursor >= sizeof screen-1)abort();screen[screen_cursor++]=c;}}}
static void fixture_clear_screen(void){memset(screen,0,sizeof screen);screen_cursor=0;}
static int next_input(const char *kind){int c;if(input_index>=input_length)abort();c=input[input_index++];if(interrupt_at==input_index)display.intr++;append("%s:%d:%d:%d;",kind,c,display.inread,display.toplin);return c;}
char pgetchar(void){return (char)next_input("pget");}
int tty_nhgetch(void){return next_input("get");}
void term_curs_set(int mode){append("cursor:%d;",mode);}
void more(void){append("more;");}
void addtopl(const char *s){append("add:%s;",s);paint(s);}
void putsyms(const char *s){append("put:%s;",s);paint(s);}
void tty_nhbell(void){append("bell;");}
void tty_clear_nhwindow(winid id){append("ttyclear:%d;",id);fixture_clear_screen();}
static void capture_clear(winid id){append("clear:%d;",id);fixture_clear_screen();}
int tty_doprev_message(void){append("prev:%d;",display.inread);return 0;}
void custompline(unsigned flags,const char *format,...){char b[BUFSZ];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("prompt:%u:%s;",flags,b);paint(b);}
void pline(const char *format,...){char b[BUFSZ];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("pline:%s;",b);}
void dumplogmsg(const char *s){append("dump:%s;",s);}
int extcmd_via_menu(void){append("menu;");return menu_result;}
char extcmd_initiator(void){append("initiator;");return '#';}
int extcmds_match(const char *base,int flags,int **out){int i,n=0;append("match:%d:%s;",flags,base);for(i=0;i<7;i++){if(!(flags&ECM_IGNOREAC)&&!(entries[i].flags&AUTOCOMPLETE))continue;if(flags&ECM_EXACTMATCH?strcmp(base,command_names[i])==0:strncmp(base,command_names[i],strlen(base))==0)matches[n++]=i;}*out=matches;return n;}
struct ext_func_tab *extcmds_getentry(int n){append("entry:%d;",n);if(n<0||n>=7)abort();return &entries[n];}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/win/tty/getline.c"
#else
extern void teleport_getline_test_hooked(const char *,char *,int);
extern boolean teleport_getline_test_ext_hook(char *);
#endif
void probe_reset(void){int i;memset(&iflags,0,sizeof iflags);memset(&gi,0,sizeof gi);memset(&gt,0,sizeof gt);memset(&program_state,0,sizeof program_state);memset((void *)&windowprocs,0,sizeof windowprocs);memset(&display,0,sizeof display);memset(&message_window,0,sizeof message_window);memset(wins,0,sizeof wins);WIN_MESSAGE=3;wins[WIN_MESSAGE]=&message_window;ttyDisplay=&display;windowprocs.win_clear_nhwindow=capture_clear;display.cols=COLNO;display.rows=ROWNO;display.dismiss_more=' ';message_window.maxrow=7;message_window.maxcol=91;iflags.cbreak=1;erase_char=8;kill_char=21;morc=0;input_length=input_index=0;interrupt_at=-1;menu_result=4;fixture_clear_screen();memset(output,0xa5,sizeof output);output[0]=0;probe_trace_storage[0]=0;memset(entries,0,sizeof entries);for(i=0;i<7;i++){entries[i].ef_txt=command_names[i];entries[i].flags=i==6?0:AUTOCOMPLETE;}}
void probe_clear(void){probe_trace_storage[0]=0;}
const char *probe_trace(void){return probe_trace_storage;}
int *probe_input_pointer(void){return input;}
void probe_input_length(int n){input_length=n;input_index=0;}
void probe_option(int n,int value){switch(n){case 0:iflags.prevmsg_window=value;break;case 1:iflags.cbreak=value;break;case 2:iflags.extmenu=value;break;case 3:gi.in_doagain=value;break;case 4:display.toplin=value;break;case 5:message_window.flags=value;break;case 6:display.intr=value;break;case 7:interrupt_at=value;break;case 8:erase_char=value;break;case 9:kill_char=value;break;case 10:display.dismiss_more=value;break;case 11:ttyDisplay=value?&display:NULL;break;case 12:program_state.done_hup=value;break;case 13:menu_result=value;break;case 14:display.inread=value;break;}}
void *probe_snapshot_pointer(int n){switch(n){case 0:return &display;case 1:return &message_window;case 2:return gt.toplines;case 3:return screen;default:return output;}}
size_t probe_snapshot_size(int n){switch(n){case 0:return sizeof display;case 1:return sizeof message_window;case 2:return sizeof gt.toplines;case 3:return sizeof screen;default:return sizeof output;}}
int probe_scalar(int n){switch(n){case 0:return input_index;case 1:return iflags.term_gone;case 2:return morc;case 3:return screen_cursor;case 4:return ttyDisplay!=NULL;default:return program_state.done_hup;}}
void probe_default(const char *s){strcpy(output,s);}
void probe_line(const char *query){tty_getlin(query,output);}
void probe_hooked(const char *query,int hook){
#ifdef TELEPORT_REFERENCE_TU
hooked_tty_getlin(query,output,hook?ext_cmd_getlin_hook:NULL);
#else
teleport_getline_test_hooked(query,output,hook);
#endif
}
int probe_hook(void){
#ifdef TELEPORT_REFERENCE_TU
return ext_cmd_getlin_hook(output);
#else
return teleport_getline_test_ext_hook(output);
#endif
}
int probe_ext(void){return tty_get_ext_cmd();}
void probe_wait(const char *allowed){xwaitforspace(allowed);}
int probe_history(void){
#ifdef TELEPORT_REFERENCE_TU
return suppress_history;
#else
return -1;
#endif
}
size_t probe_stack(void){return emscripten_stack_get_current();}
