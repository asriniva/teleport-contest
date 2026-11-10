/* Unchanged original TERMCAP versus JS policy in a controlled C foreign world.
 * This fixture does not change selected capture/encoding/input or emulate a
 * terminal. Actual configured libtinfo supplies the first-pass dependency.
 * Source and transport/capture/native-host/full-game claims stay separate.
 */
#include "hack.h"
#include "wintty.h"
#include "tcap.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
extern boolean HE_resets_AS;
extern void (*decgraphics_mode_callback)(void);
extern void (*utf8graphics_mode_callback)(void);
__typeof__(flags) flags;
__typeof__(gt) gt;
__typeof__(gs) gs;
__typeof__(gc) gc;
__typeof__(HE_resets_AS) HE_resets_AS;
__typeof__(decgraphics_mode_callback) decgraphics_mode_callback;
__typeof__(utf8graphics_mode_callback) utf8graphics_mode_callback;
__typeof__(ttyDisplay) ttyDisplay;
__typeof__(BASE_WINDOW) BASE_WINDOW;
__typeof__(iflags) iflags;

static struct DisplayDesc display;
static int ints[8],options[16],error_code,tracepos,allocated,reentered;
static char inputs[4][8192],tracebuf[1048576];
static uintptr_t last_output_pointer;
static jmp_buf escapes[16];static int escape_depth;static void*growth;
static struct {uintptr_t pointer;size_t bytes;int live;} allocations[4096];
static struct {int kind,key,value;char text[512];} overrides[128];static int override_count;
static void append(const char*format,...){if(tracepos>sizeof tracebuf-20000)abort();va_list ap;va_start(ap,format);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,format,ap);va_end(ap);}
static void hex(const char*value){if(!value){append("null");return;}for(const unsigned char*p=(const unsigned char*)value;*p;p++)append("%02x",*p);}
static void checkpoint(void){if(options[0]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}if(options[1]&&!reentered){reentered=1;append("reenter:%d;",term_attr_fixup(HL_ULINE|HL_BLINK|HL_DIM));}}
static int key(const char*id){return((unsigned char)id[0]<<8)|(unsigned char)id[1];}
static int override(int kind,const char*id){for(int i=0;i<override_count;i++)if(overrides[i].kind==kind&&overrides[i].key==key(id))return i;return-1;}
char*__real_getenv(const char*);
char*__wrap_getenv(const char*name){char*v=__real_getenv(name);append("getenv:%s:",name);hex(v);append(";");return v;}
int __real_putchar(int);
int __wrap_putchar(int c){append("putchar:%d;",c);checkpoint();return __real_putchar(c);}
int __real_fflush(FILE*);
int __wrap_fflush(FILE*f){append("fflush:%d;",!f?0:f==stdout?1:2);checkpoint();return __real_fflush(f);}
void __real_free(void*);
void __wrap_free(void*p){int found=0;for(int i=allocated-1;i>=0;i--)if(allocations[i].pointer==(uintptr_t)p&&allocations[i].live){found=i+1;allocations[i].live=0;break;}append("free:%d;",found);__real_free(p);}
int __real_tgetent(char*,const char*);
int __wrap_tgetent(char*b,const char*name){append("tgetent:");hex(name);append(";");int i=override(3,"en");return i>=0?overrides[i].value:__real_tgetent(b,name);}
int __real_tgetnum(const char*);
int __wrap_tgetnum(const char*id){int i=override(1,id),v=i>=0?overrides[i].value:__real_tgetnum(id);append("tgetnum:%s:%d;",id,v);return v;}
int __real_tgetflag(const char*);
int __wrap_tgetflag(const char*id){int i=override(2,id),v=i>=0?overrides[i].value:__real_tgetflag(id);append("tgetflag:%s:%d;",id,v);return v;}
char*__real_tgetstr(const char*,char**);
char*__wrap_tgetstr(const char*id,char**area){int i=override(0,id);char*v;if(i<0)v=__real_tgetstr(id,area);else if(!overrides[i].value)v=0;else if(area&&*area){v=*area;strcpy(v,overrides[i].text);*area+=strlen(v)+1;}else v=overrides[i].text;append("tgetstr:%s:%d:",id,area!=0);hex(v);append(";");return v;}
int __real_tputs(const char*,int,int(*)(int));
int __wrap_tputs(const char*value,int affected,int(*callback)(int)){last_output_pointer=(uintptr_t)value;append("tputs:%d:%d:",affected,callback==xputc);hex(value);append(";");return __real_tputs(value,affected,callback);}
long*alloc(unsigned int bytes){void*p=malloc(bytes?bytes:1);if(!p||allocated>=4096)abort();allocations[allocated].pointer=(uintptr_t)p;allocations[allocated].bytes=bytes;allocations[allocated].live=1;allocated++;append("alloc:%u:%d;",bytes,allocated);return p;}
char*dupstr(const char*text){size_t n=strlen(text)+1;char*p=(char*)(alloc)((unsigned)n);memcpy(p,text,n);append("dup:");hex(text);append(";");return p;}
boolean digit(char c){return c>='0'&&c<='9';}
void error(const char*format,...){char message[2048];va_list ap;va_start(ap,format);vsnprintf(message,sizeof message,format,ap);va_end(ap);append("error:");hex(message);append(";");error_code=1;if(!escape_depth)abort();longjmp(escapes[escape_depth-1],1);}
void nh_snprintf(const char*function,int line,char*buffer,size_t bytes,const char*format,...){append("snprintf:%s:%d:%lu;",function,line,(unsigned long)bytes);va_list ap;va_start(ap,format);vsnprintf(buffer,bytes,format,ap);va_end(ap);checkpoint();}
void setclipped(void){append("setclipped;");}
void tty_raw_print(const char*text){append("raw:");hex(text);append(";");}
void tty_wait_synch(void){append("wait;");}
void tty_utf8graphics_fixup(void){append("utf8fixup;");checkpoint();}
void tty_curs(winid window,int x,int y){append("curs:%d:%d:%d;",window,x,y);if(ttyDisplay){ttyDisplay->curx=x-1;ttyDisplay->cury=y;}}
void erase_tty_screen(void){append("erase;");}
void teleport_capture(const char*screen,int x,int y,int animation){append("capture:%d:%d:%d:",x,y,animation);hex(screen);append(";");checkpoint();}
#ifndef HYBRID_TERMCAP
#define TELEPORT_REFERENCE_TU 1
#include "../.cache/wasm64-build/tree/win/tty/termcap.c"
#else
extern void term_startup(int *,int *);
extern void term_shutdown(void);
extern void tty_number_pad(int);
extern void teleport_termcap_test_tty_decgraphics_termcap_fixup(void);
extern void term_start_screen(void);
extern void term_end_screen(void);
extern void nocmov(int,int);
extern void cmov(int,int);
extern int xputc(int);
extern int teleport_termcap_test_nomux_markers_enabled(void);
extern void teleport_termcap_test_nomux_emit_marker(const char *);
extern void nomux_capture_write_screen(void);
extern void nomux_capture_write_input_boundary(void);
extern void nomux_clear_screen(void);
extern void nomux_clear_to_eol(int,int);
extern void nomux_putch(int);
extern void nomux_set_attr(int);
extern void nomux_end_attr(void);
extern void nomux_set_fg(int);
extern void nomux_end_fg(void);
extern int teleport_termcap_test_nomux_sgr_fg(int);
extern char * nomux_capture_screen(void);
extern void nomux_enter_raw_mode(void);
extern void teleport_termcap_test_nomux_raw_putch(int);
extern void nomux_raw_emit(const char *,int);
extern void nomux_raw_emit_eol(void);
extern void nomux_get_cursor(int *,int *);
extern void xputs(const char *);
extern void cl_end(void);
extern void term_clear_screen(void);
extern void home(void);
extern void standoutbeg(void);
extern void standoutend(void);
extern void backsp(void);
extern void tty_nhbell(void);
extern void graph_on(void);
extern void graph_off(void);
extern void tty_delay_output(void);
extern void cl_eos(void);
extern void teleport_termcap_test_init_hilite(void);
extern void teleport_termcap_test_kill_hilite(void);
extern char * teleport_termcap_test_s_atr2str(int);
extern char * teleport_termcap_test_e_atr2str(int);
extern int term_attr_fixup(int);
extern void term_start_attr(int);
extern void term_end_attr(int);
extern void term_start_raw_bold(void);
extern void term_end_raw_bold(void);
extern void term_end_color(void);
extern void term_start_color(int);
extern void term_start_bgcolor(int);
extern void term_curs_set(int);
extern void teleport_termcap_test_emit24bit(long);
extern void teleport_termcap_test_emit256(int);
extern void term_start_extracolor(uint32,uint16);
extern void term_end_extracolor(void);
#endif
#include "../nethack-c/wasm/tu-fragments/termcap-support.c"
#include "tu-termcap-layout.h"
#ifdef HYBRID_TERMCAP
#define tty_decgraphics_termcap_fixup teleport_termcap_test_tty_decgraphics_termcap_fixup
#endif
#ifdef HYBRID_TERMCAP
#define nomux_markers_enabled teleport_termcap_test_nomux_markers_enabled
#endif
#ifdef HYBRID_TERMCAP
#define nomux_emit_marker teleport_termcap_test_nomux_emit_marker
#endif
#ifdef HYBRID_TERMCAP
#define nomux_sgr_fg teleport_termcap_test_nomux_sgr_fg
#endif
#ifdef HYBRID_TERMCAP
#define nomux_raw_putch teleport_termcap_test_nomux_raw_putch
#endif
#ifdef HYBRID_TERMCAP
#define init_hilite teleport_termcap_test_init_hilite
#endif
#ifdef HYBRID_TERMCAP
#define kill_hilite teleport_termcap_test_kill_hilite
#endif
#ifdef HYBRID_TERMCAP
#define s_atr2str teleport_termcap_test_s_atr2str
#endif
#ifdef HYBRID_TERMCAP
#define e_atr2str teleport_termcap_test_e_atr2str
#endif
#ifdef HYBRID_TERMCAP
#define emit24bit teleport_termcap_test_emit24bit
#endif
#ifdef HYBRID_TERMCAP
#define emit256 teleport_termcap_test_emit256
#endif
static const size_t global_sizes[]={sizeof(signed char[512]),sizeof(struct flag),sizeof(signed char),sizeof(void *),sizeof(void *),sizeof(struct instance_globals_t),sizeof(struct tc_lcl_data),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(int),sizeof(signed char[1]),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(signed char),sizeof(void *),sizeof(signed char[16]),sizeof(signed char[16]),sizeof(struct instance_globals_s),sizeof(struct instance_globals_c),sizeof(signed char),sizeof(void *),sizeof(void *),sizeof(void *),sizeof(int),sizeof(void *),sizeof(int),sizeof(int),sizeof(nomux_cell[24][80]),sizeof(unsigned char),sizeof(unsigned char),sizeof(unsigned char),sizeof(struct instance_flags),sizeof(signed char[6144]),sizeof(int),sizeof(int),sizeof(int),sizeof(short),sizeof(short[15]),sizeof(void *[16]),sizeof(signed char[1]),sizeof(TELEPORT_TERMCAP_TI_MAP_TYPE[6]),sizeof(signed char[1])};

uint64_t probe_canonical(uint64_t p){if(!p)return 0;for(int i=0;i<sizeof global_sizes/sizeof global_sizes[0];i++){uintptr_t start=(uintptr_t)teleport_termcap_global(i);if(p>=start&&p<start+global_sizes[i])return(uint64_t)(i+1)*100000+(p-start);}if(p==(uintptr_t)stdout)return 90000000;for(int i=0;i<4;i++)if(p>=(uintptr_t)inputs[i]&&p<(uintptr_t)(inputs[i]+sizeof inputs[i]))return 80000000+i*10000+(p-(uintptr_t)inputs[i]);if(p>=(uintptr_t)&display&&p<(uintptr_t)(&display+1))return 81000000+p-(uintptr_t)&display;for(int i=allocated-1;i>=0;i--)if(allocations[i].live&&p>=allocations[i].pointer&&p<allocations[i].pointer+allocations[i].bytes)return 100000000+(uint64_t)(i+1)*100000+p-allocations[i].pointer;return UINT64_MAX;}
void probe_reset(void){tracepos=0;tracebuf[0]=0;error_code=0;reentered=0;memset(options,0,sizeof options);memset(ints,0x56,sizeof ints);override_count=0;flags.null=flags.silent=0;gt.tc_gbl_data.tc_CO=80;gt.tc_gbl_data.tc_LI=24;gc.currentgraphics=0;gc.Cmd.num_pad=0;gs.symset[0].handling=H_UNK;gs.symset[1].handling=H_UNK;iflags.wc2_darkgray=0;iflags.debug_fuzzer=0;HE_resets_AS=0;ttyDisplay=&display;display.curx=0;display.cury=0;BASE_WINDOW=1;}
void probe_clear_trace(void){tracepos=0;tracebuf[0]=0;error_code=0;reentered=0;}
void probe_option(int index,int value){if(index<0||index>=16)abort();options[index]=value;}
void probe_override(int kind,int id,int value){if(override_count>=128)abort();int i=override_count++;overrides[i].kind=kind;overrides[i].key=id;overrides[i].value=value;if(strlen(inputs[1])>=sizeof overrides[i].text)abort();strcpy(overrides[i].text,inputs[1]);}
uint64_t probe_pointer(int kind,int index){switch(kind){case 0:return(uintptr_t)inputs[index];case 1:return(uintptr_t)&ints[index];case 2:return(uintptr_t)&display;case 3:return(uintptr_t)stdout;default:abort();}}
const char*probe_trace(void){return tracebuf;}
int probe_error(void){return error_code;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
uintptr_t probe_last_output_pointer(void){return last_output_pointer;}
int probe_layout_count(void){return sizeof termcap_layout/sizeof termcap_layout[0];}
const char*probe_layout_name(int i){return termcap_layout[i].name;}
uint64_t probe_layout_value(int i){return termcap_layout[i].value;}
uintptr_t probe_callback_pointer(int i){return i==0?(uintptr_t)xputc:i==1?(uintptr_t)decgraphics_mode_callback:(uintptr_t)utf8graphics_mode_callback;}
int probe_invoke_callback(int i,int c){if(i==0)return xputc(c);void(*fn)(void)=i==1?decgraphics_mode_callback:utf8graphics_mode_callback;if(!fn)abort();fn();return 0;}
int probe_constant(int i){static const int values[]={H_UNK,H_DEC,H_UTF8,CLR_MAX,NO_COLOR,HL_BOLD,HL_ULINE,HL_BLINK,HL_DIM};return values[i];}
uint64_t probe_call_term_startup(uint64_t a0,uint64_t a1){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_startup((int *)(uintptr_t)a0,(int *)(uintptr_t)a1);}escape_depth--;return result;}
uint64_t probe_call_term_shutdown(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_shutdown();}escape_depth--;return result;}
uint64_t probe_call_tty_number_pad(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){tty_number_pad((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_tty_decgraphics_termcap_fixup(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){tty_decgraphics_termcap_fixup();}escape_depth--;return result;}
uint64_t probe_call_term_start_screen(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_start_screen();}escape_depth--;return result;}
uint64_t probe_call_term_end_screen(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_end_screen();}escape_depth--;return result;}
uint64_t probe_call_nocmov(uint64_t a0,uint64_t a1){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nocmov((int)(uintptr_t)a0,(int)(uintptr_t)a1);}escape_depth--;return result;}
uint64_t probe_call_cmov(uint64_t a0,uint64_t a1){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){cmov((int)(uintptr_t)a0,(int)(uintptr_t)a1);}escape_depth--;return result;}
uint64_t probe_call_xputc(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){result=(uint64_t)(intptr_t)(xputc((int)(uintptr_t)a0));}escape_depth--;return result;}
uint64_t probe_call_nomux_markers_enabled(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){result=(uint64_t)(intptr_t)(nomux_markers_enabled());}escape_depth--;return result;}
uint64_t probe_call_nomux_emit_marker(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_emit_marker((const char *)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_nomux_capture_write_screen(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_capture_write_screen();}escape_depth--;return result;}
uint64_t probe_call_nomux_capture_write_input_boundary(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_capture_write_input_boundary();}escape_depth--;return result;}
uint64_t probe_call_nomux_clear_screen(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_clear_screen();}escape_depth--;return result;}
uint64_t probe_call_nomux_clear_to_eol(uint64_t a0,uint64_t a1){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_clear_to_eol((int)(uintptr_t)a0,(int)(uintptr_t)a1);}escape_depth--;return result;}
uint64_t probe_call_nomux_putch(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_putch((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_nomux_set_attr(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_set_attr((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_nomux_end_attr(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_end_attr();}escape_depth--;return result;}
uint64_t probe_call_nomux_set_fg(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_set_fg((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_nomux_end_fg(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_end_fg();}escape_depth--;return result;}
uint64_t probe_call_nomux_sgr_fg(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){result=(uint64_t)(intptr_t)(nomux_sgr_fg((int)(uintptr_t)a0));}escape_depth--;return result;}
uint64_t probe_call_nomux_capture_screen(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){result=(uint64_t)(intptr_t)(nomux_capture_screen());}escape_depth--;return result;}
uint64_t probe_call_nomux_enter_raw_mode(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_enter_raw_mode();}escape_depth--;return result;}
uint64_t probe_call_nomux_raw_putch(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_raw_putch((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_nomux_raw_emit(uint64_t a0,uint64_t a1){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_raw_emit((const char *)(uintptr_t)a0,(int)(uintptr_t)a1);}escape_depth--;return result;}
uint64_t probe_call_nomux_raw_emit_eol(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_raw_emit_eol();}escape_depth--;return result;}
uint64_t probe_call_nomux_get_cursor(uint64_t a0,uint64_t a1){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){nomux_get_cursor((int *)(uintptr_t)a0,(int *)(uintptr_t)a1);}escape_depth--;return result;}
uint64_t probe_call_xputs(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){xputs((const char *)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_cl_end(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){cl_end();}escape_depth--;return result;}
uint64_t probe_call_term_clear_screen(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_clear_screen();}escape_depth--;return result;}
uint64_t probe_call_home(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){home();}escape_depth--;return result;}
uint64_t probe_call_standoutbeg(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){standoutbeg();}escape_depth--;return result;}
uint64_t probe_call_standoutend(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){standoutend();}escape_depth--;return result;}
uint64_t probe_call_backsp(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){backsp();}escape_depth--;return result;}
uint64_t probe_call_tty_nhbell(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){tty_nhbell();}escape_depth--;return result;}
uint64_t probe_call_graph_on(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){graph_on();}escape_depth--;return result;}
uint64_t probe_call_graph_off(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){graph_off();}escape_depth--;return result;}
uint64_t probe_call_tty_delay_output(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){tty_delay_output();}escape_depth--;return result;}
uint64_t probe_call_cl_eos(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){cl_eos();}escape_depth--;return result;}
uint64_t probe_call_init_hilite(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){init_hilite();}escape_depth--;return result;}
uint64_t probe_call_kill_hilite(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){kill_hilite();}escape_depth--;return result;}
uint64_t probe_call_s_atr2str(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){result=(uint64_t)(intptr_t)(s_atr2str((int)(uintptr_t)a0));}escape_depth--;return result;}
uint64_t probe_call_e_atr2str(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){result=(uint64_t)(intptr_t)(e_atr2str((int)(uintptr_t)a0));}escape_depth--;return result;}
uint64_t probe_call_term_attr_fixup(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){result=(uint64_t)(intptr_t)(term_attr_fixup((int)(uintptr_t)a0));}escape_depth--;return result;}
uint64_t probe_call_term_start_attr(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_start_attr((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_term_end_attr(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_end_attr((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_term_start_raw_bold(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_start_raw_bold();}escape_depth--;return result;}
uint64_t probe_call_term_end_raw_bold(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_end_raw_bold();}escape_depth--;return result;}
uint64_t probe_call_term_end_color(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_end_color();}escape_depth--;return result;}
uint64_t probe_call_term_start_color(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_start_color((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_term_start_bgcolor(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_start_bgcolor((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_term_curs_set(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_curs_set((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_emit24bit(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){emit24bit((long)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_emit256(uint64_t a0){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){emit256((int)(uintptr_t)a0);}escape_depth--;return result;}
uint64_t probe_call_term_start_extracolor(uint64_t a0,uint64_t a1){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_start_extracolor((uint32)(uintptr_t)a0,(uint16)(uintptr_t)a1);}escape_depth--;return result;}
uint64_t probe_call_term_end_extracolor(void){uint64_t result=0;if(escape_depth>=16)abort();if(setjmp(escapes[escape_depth++])==0){term_end_extracolor();}escape_depth--;return result;}
