/* Actual WINTTY C versus JS with real prepared termcap/ncurses6.5.
 * Foreign game/terminal-mode dependencies are explicit controlled fixtures.
 * No terminal emulation or replacement escape policy is implemented here. */
#include "hack.h"
#include "wintty.h"
#include "tcap.h"
#include <stdint.h>
#include <stdarg.h>
#include <setjmp.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-wintty-layout.h"
extern void *teleport_wintty_data_storage(int);
extern char erase_char;
__typeof__(program_state) program_state;
__typeof__(gt) gt;
__typeof__(iflags) iflags;
__typeof__(WIN_MAP) WIN_MAP;
__typeof__(gg) gg;
__typeof__(u) u;
__typeof__(WIN_STATUS) WIN_STATUS;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(svp) svp;
__typeof__(morc) morc;
__typeof__(flags) flags;
__typeof__(WIN_INVEN) WIN_INVEN;
__typeof__(disp) disp;
__typeof__(gm) gm;
__typeof__(gs) gs;
__typeof__(gc) gc;
__typeof__(windowprocs) windowprocs;
__typeof__(status_activefields) status_activefields;
__typeof__(status_fieldfmt) status_fieldfmt;
__typeof__(status_vals) status_vals;
__typeof__(yn_number) yn_number;
__typeof__(erase_char) erase_char;
const struct const_globals cg={0};const glyph_info nul_glyphinfo={0};
const char quitchars[]=" \r\n\033";
int cond_idx[CONDITION_COUNT];
void(*decgraphics_mode_callback)(void),(*utf8graphics_mode_callback)(void);
char erase_char=8;
static char input[4096],buffers[8][8192],tracebuf[1048576],snap[1048576];static unsigned inputpos;static int opts[1024],integers[16],escape_code;static uintptr_t returned;static jmp_buf escape;static void*growth;static int nested;
static void append(const char*format,...){va_list ap;va_start(ap,format);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),format,ap);va_end(ap);}
static void hex(const char*s){if(!s){append("null");return;}for(const unsigned char*p=(const unsigned char*)s;*p;p++)append("%02x",*p);}
static void checkpoint(int stage){if(opts[1000]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("growth;");}if(opts[1001]==stage&&!nested){nested=1;tty_mark_synch();append("nested;");}}
const struct conditions_t conditions[] = {
    /* ranking, mask, identifier, txt1, txt2, txt3 */
    { 20, BL_MASK_BAREH,     bl_bareh,     { "Bare",     "Bar",   "Bh"  } },
    { 10, BL_MASK_BLIND,     bl_blind,     { "Blind",    "Blnd",  "Bl"  } },
    { 20, BL_MASK_BUSY,      bl_busy,      { "Busy",     "Bsy",   "By"  } },
    { 10, BL_MASK_CONF,      bl_conf,      { "Conf",     "Cnf",   "Cf"  } },
    { 10, BL_MASK_DEAF,      bl_deaf,      { "Deaf",     "Def",   "Df"  } },
    { 15, BL_MASK_ELF_IRON,  bl_elf_iron,  { "Iron",     "Irn",   "Fe"  } },
    { 10, BL_MASK_FLY,       bl_fly,       { "Fly",      "Fly",   "Fl"  } },
    {  6, BL_MASK_FOODPOIS,  bl_foodpois,  { "FoodPois", "Fpois", "Poi" } },
    { 20, BL_MASK_GLOWHANDS, bl_glowhands, { "Glow",     "Glo",   "Gl"  } },
    {  2, BL_MASK_GRAB,      bl_grab,      { "Grab",     "Grb",   "Gr"  } },
    { 10, BL_MASK_HALLU,     bl_hallu,     { "Hallu",    "Hal",   "Hl"  } },
    { 20, BL_MASK_HELD,      bl_held,      { "Held",     "Hld",   "Hd"  } },
    { 20, BL_MASK_ICY,       bl_icy,       { "Icy",      "Icy",   "Ic"  } },
    {  8, BL_MASK_INLAVA,    bl_inlava,    { "InLava",   "Lav",   "La"  } },
    { 10, BL_MASK_LEV,       bl_lev,       { "Lev",      "Lev",   "Lv"  } },
    { 20, BL_MASK_PARLYZ,    bl_parlyz,    { "Parlyz",   "Para",  "Par" } },
    { 10, BL_MASK_RIDE,      bl_ride,      { "Ride",     "Rid",   "Rd"  } },
    { 20, BL_MASK_SLEEPING,  bl_sleeping,  { "Zzz",      "Zzz",   "Zz"  } },
    {  6, BL_MASK_SLIME,     bl_slime,     { "Slime",    "Slim",  "Slm" } },
    { 20, BL_MASK_SLIPPERY,  bl_slippery,  { "Slip",     "Slp",   "Sl"  } },
    {  6, BL_MASK_STONE,     bl_stone,     { "Stone",    "Ston",  "Sto" } },
    {  4, BL_MASK_STRNGL,    bl_strngl,    { "Strngl",   "Stngl", "Str" } },
    { 10, BL_MASK_STUN,      bl_stun,      { "Stun",     "Stun",  "St"  } },
    { 15, BL_MASK_SUBMERGED, bl_submerged, { "Submrg",   "Subm",  "Sm"  } },
    {  6, BL_MASK_TERMILL,   bl_termill,   { "TermIll",  "Ill",   "Ill" } },
    { 20, BL_MASK_TETHERED,  bl_tethered,  { "Teth",     "Tth",   "Te"  } },
    { 20, BL_MASK_TRAPPED,   bl_trapped,   { "Trap",     "Trp",   "Tr"  } },
    { 20, BL_MASK_UNCONSC,   bl_unconsc,   { "Out",      "Out",   "KO"  } },
    { 20, BL_MASK_WOUNDEDL,  bl_woundedl,  { "WLegs",    "Leg",   "Lg"  } },
    { 20, BL_MASK_HOLDING,   bl_holding,   { "UHold",    "UHld",  "UHd" } },
};
static void(*handler)(int);
void(*teleport_native_signal(int sig,void(*fn)(int)))(int){void(*old)(int)=handler;handler=fn;append("signal:%d:%d;",sig,fn!=0);return old;}
void teleport_capture(const char*s,int x,int y,int animation){append("capture:%d:%d:%d:",x,y,animation);hex(s);append(";");checkpoint(2);}
void nh_terminate(int status){append("terminate:%d;",status);escape_code=1;longjmp(escape,1);}
void panic(const char*format,...){char b[4096];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("panic:%s;",b);escape_code=2;longjmp(escape,1);}
void error(const char*format,...){char b[4096];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("error:%s;",b);escape_code=4;longjmp(escape,1);}
void nhassert_failed(const char*condition,const char*file,int line){append("assert:%s:%s:%d;",condition,file,line);escape_code=3;longjmp(escape,1);}
static struct {void*p;unsigned size;int live;} allocations[32768];static unsigned allocated;
unsigned probe_alloc_count(void) { return allocated; }
void *probe_alloc_base(unsigned id) {
    return id && id <= allocated ? allocations[id - 1].p : 0;
}
unsigned probe_alloc_size(unsigned id) {
    return id && id <= allocated ? allocations[id - 1].size : 0;
}
int probe_alloc_live(unsigned id) {
    return id && id <= allocated ? allocations[id - 1].live : 0;
}
long*__real_alloc(unsigned);
long*__wrap_alloc(unsigned n){long*p=__real_alloc(n);if(allocated>=32768)abort();allocations[allocated].p=p;allocations[allocated].size=n;allocations[allocated].live=1;allocated++;memset(p,0xa5,n);append("alloc:%u:%u;",allocated,n);checkpoint(6);return p;}
void __real_free(void*);
void __wrap_free(void*p){unsigned id=0;for(unsigned i=allocated;i>0;i--)if(allocations[i-1].p==p&&allocations[i-1].live){id=i;allocations[i-1].live=0;break;}append("free:%u;",id);__real_free(p);}
int __real_putchar(int);int __wrap_putchar(int c){checkpoint(5);return __real_putchar(c);}
int __real_puts(const char*);int __wrap_puts(const char*s){return __real_puts(s);}
int __real_fputs(const char*,FILE*);int __wrap_fputs(const char*s,FILE*f){return __real_fputs(s,f);}
int __real_fflush(FILE*);int __wrap_fflush(FILE*f){append("fflush:%d;",!f?0:f==stdout?1:2);return __real_fflush(f);}
void __real_setbuf(FILE*,char*);void __wrap_setbuf(FILE*f,char*p){append("setbuf:%d:%d;",f==stdout,p==teleport_wintty_data_storage(5));__real_setbuf(f,p);}
ssize_t __real_read(int,void*,size_t);ssize_t __wrap_read(int fd,void*p,size_t n){ssize_t got=__real_read(fd,p,n);append("read:%d:%lu:%ld;",fd,(unsigned long)n,(long)got);return got;}
void clearlocks(){append("clearlocks;");}
void getwindowsz(){append("getwindowsz;");if(opts[1]){LI=opts[1];CO=opts[2];}}
void docrt_flags(int a0){append("docrt_flags;");}
void bot(){append("bot;");}
void genl_status_finish(){append("genl_status_finish;");}
void status_initialize(boolean a0){append("status_initialize;");}
void gettty(){append("gettty;");iflags.echo=1;iflags.cbreak=1;}
void setftty(){append("setftty;");term_start_screen();}
const char * copyright_banner_line(int a0){return a0==1?"WINTTY fixture":a0==2?"Original terminal chain":"";}
void set_wc2_option_mod_status(unsigned long a0,int a1){append("set_wc2_option_mod_status;");}
void genl_preference_update(const char * a0){append("pref:%s;",a0);}
int genl_player_setup(int a0){return opts[6];}
int restore_menu(winid a0){return opts[7];}
void xwaitforspace(const char * a0){append("wait:");hex(a0);append(";");morc=input[inputpos]?(char)input[inputpos++]:27;checkpoint(3);}
void settty(const char * a0){append("settty:%s;",a0?a0:"");term_end_screen();}
void docrt(){append("docrt;");}
void free_pickinv_cache(){append("free_pickinv_cache;");}
void flush_screen(int a0){append("flush_screen;");}
boolean menuitem_invert_test(int a0,unsigned int a1,boolean a2){return 1;}
char map_menu_cmd(char a0){return a0;}
void tty_getlin(const char * a0,char * a1){append("getlin:%s;",a0);strcpy(a1,input+inputpos);inputpos=strlen(input);}
boolean debugcore(const char * a0,boolean a1){append("debug:%s:%d;",a0,a1);return opts[3];}
void pline(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline:%s;",b);checkpoint(4);}
void impossible(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("impossible:%s;",b);checkpoint(4);}
void row_refresh(coordxy a0,coordxy a1,coordxy a2){append("row_refresh:%d:%d:%d;",a0,a1,a2);}
void redraw_map(boolean a0){append("redraw_map;");}
char randomkey(){return (char)opts[9];}
int teleport_getch(){append("getch;");checkpoint(1);return input[inputpos]?(unsigned char)input[inputpos++]:-1;}
char * mixed_to_utf8(char * a0,size_t a1,const char * a2,int * a3){strcpy(a0,a2);*a3=opts[8];return a0;}
char * decode_mixed(char * a0,const char * a1){strcpy(a0,a1);return a0;}
void genl_status_init(){append("genl_status_init;");if(WIN_STATUS==WIN_ERR)WIN_STATUS=tty_create_nhwindow(NHW_STATUS);}
void genl_status_enablefield(int a0,const char * a1,const char * a2,boolean a3){append("enable:%d:%d;",a0,a3);status_fieldfmt[a0]=dupstr(a2);status_activefields[a0]=a3;if(!status_vals[a0])status_vals[a0]=calloc(1,BUFSZ);}
boolean critically_low_hp(boolean a0){return opts[4];}
int stat_cap_indx(){return opts[5];}
void paniclog(const char * a0,const char * a1){append("paniclog;");}
void repad_with_dashes(char * a0){append("repad;");}
int tty_get_ext_cmd(){append("tty_get_ext_cmd;");return (int)opts[66];}
void genl_outrip(winid a0,int a1,time_t a2){append("genl_outrip;");}
boolean genl_can_suspend_yes(){return 1;}
void tty_utf8graphics_fixup(){append("tty_utf8graphics_fixup;");}
void custompline(unsigned int a0,const char * a1,...){append("custompline;");}
char readchar(){append("readchar;");return (char)opts[71];}
char * key2txt(uchar a0,char * a1){append("key2txt;");return "key2txt";}
void dumplogmsg(const char * a0){append("dumplogmsg;");}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/win/tty/wintty.c"
void *teleport_wintty_reference_storage(int i){switch(i){case 0:return(void*)&tty_procs;case 1:return(void*)&BASE_WINDOW;case 2:return(void*)&wins;case 3:return(void*)&ttyDisplay;case 4:return(void*)&erasing_tty_screen;case 5:return(void*)&obuf;case 6:return(void*)&winpanicstr;case 7:return(void*)&defmorestr;case 8:return(void*)&clipping;case 9:return(void*)&clipx;case 10:return(void*)&clipxmax;case 11:return(void*)&clipy;case 12:return(void*)&clipymax;case 13:return(void*)&GFlag;case 14:return(void*)&HE_resets_AS;case 15:return(void*)&calling_from_update_inventory;case 16:return(void*)&default_menu_cmds;case 17:return(void*)&resize_mesg;case 18:return(void*)&tty_menu_promptstyle;case 19:return(void*)&tty_colormasks;case 20:return(void*)&tty_condition_bits;case 21:return(void*)&tty_status;case 22:return(void*)&hpbar_percent;case 23:return(void*)&hpbar_crit_hp;case 24:return(void*)&encvals;case 25:return(void*)&twolineorder;case 26:return(void*)&threelineorder;case 27:return(void*)&fieldorder;case 28:return(void*)&finalx;case 29:return(void*)&windowdata_init;case 30:return(void*)&cond_shrinklvl;case 31:return(void*)&enclev;case 32:return(void*)&enc_shrinklvl;case 33:return(void*)&dlvl_shrinklvl;case 34:return(void*)&truncation_expected;case 35:return(void*)&do_field_opt;default:return 0;}}
#else
extern void teleport_wintty_test_bail(const char *);
#define bail teleport_wintty_test_bail
extern void teleport_wintty_test_winch_handler(int);
#define winch_handler teleport_wintty_test_winch_handler
extern void teleport_wintty_test_resize_tty();
#define resize_tty teleport_wintty_test_resize_tty
extern void teleport_wintty_test_newclipping(coordxy,coordxy);
#define newclipping teleport_wintty_test_newclipping
extern void teleport_wintty_test_new_status_window();
#define new_status_window teleport_wintty_test_new_status_window
extern void teleport_wintty_test_getret();
#define getret teleport_wintty_test_getret
extern void teleport_wintty_test_erase_menu_or_text(winid,struct WinDesc *,boolean);
#define erase_menu_or_text teleport_wintty_test_erase_menu_or_text
extern void teleport_wintty_test_free_window_info(struct WinDesc *,boolean);
#define free_window_info teleport_wintty_test_free_window_info
extern boolean teleport_wintty_test_toggle_menu_curr(winid,tty_menu_item *,int,boolean,boolean,long);
#define toggle_menu_curr teleport_wintty_test_toggle_menu_curr
extern void teleport_wintty_test_dmore(struct WinDesc *,const char *);
#define dmore teleport_wintty_test_dmore
extern void teleport_wintty_test_set_item_state(winid,int,tty_menu_item *);
#define set_item_state teleport_wintty_test_set_item_state
extern void teleport_wintty_test_set_all_on_page(winid,tty_menu_item *,tty_menu_item *);
#define set_all_on_page teleport_wintty_test_set_all_on_page
extern void teleport_wintty_test_unset_all_on_page(winid,tty_menu_item *,tty_menu_item *);
#define unset_all_on_page teleport_wintty_test_unset_all_on_page
extern void teleport_wintty_test_invert_all_on_page(winid,tty_menu_item *,tty_menu_item *,char,long);
#define invert_all_on_page teleport_wintty_test_invert_all_on_page
extern void teleport_wintty_test_invert_all(winid,tty_menu_item *,tty_menu_item *,char,long);
#define invert_all teleport_wintty_test_invert_all
extern void teleport_wintty_test_toggle_menu_attr(boolean,int,int);
#define toggle_menu_attr teleport_wintty_test_toggle_menu_attr
extern void teleport_wintty_test_process_menu_window(winid,struct WinDesc *);
#define process_menu_window teleport_wintty_test_process_menu_window
extern void teleport_wintty_test_process_text_window(winid,struct WinDesc *);
#define process_text_window teleport_wintty_test_process_text_window
extern const char * teleport_wintty_test_compress_str(const char *);
#define compress_str teleport_wintty_test_compress_str
extern tty_menu_item * teleport_wintty_test_reverse(tty_menu_item *);
#define reverse teleport_wintty_test_reverse
extern int teleport_wintty_test_make_things_fit(boolean);
#define make_things_fit teleport_wintty_test_make_things_fit
extern boolean teleport_wintty_test_check_fields(boolean,int *);
#define check_fields teleport_wintty_test_check_fields
extern void teleport_wintty_test_tty_putstatusfield(const char *,int,int);
#define tty_putstatusfield teleport_wintty_test_tty_putstatusfield
extern void teleport_wintty_test_set_condition_length();
#define set_condition_length teleport_wintty_test_set_condition_length
extern void teleport_wintty_test_shrink_enc(int);
#define shrink_enc teleport_wintty_test_shrink_enc
extern void teleport_wintty_test_shrink_dlvl(int);
#define shrink_dlvl teleport_wintty_test_shrink_dlvl
extern boolean teleport_wintty_test_check_windowdata();
#define check_windowdata teleport_wintty_test_check_windowdata
extern int teleport_wintty_test_condcolor(long,unsigned long *);
#define condcolor teleport_wintty_test_condcolor
extern int teleport_wintty_test_condattr(long,unsigned long *);
#define condattr teleport_wintty_test_condattr
extern void teleport_wintty_test_render_status();
#define render_status teleport_wintty_test_render_status
#endif
int probe_callback_kind(uintptr_t fn){
#ifdef TELEPORT_REFERENCE_TU
if(fn==(uintptr_t)winch_handler)return 0;
#else
extern uintptr_t teleport_wintty_callback_pointer(int);
if(fn==teleport_wintty_callback_pointer(0))return 0;
#endif
if(fn==(uintptr_t)tty_init_nhwindows)return 1;if(fn==(uintptr_t)tty_player_selection)return 2;if(fn==(uintptr_t)tty_askname)return 3;if(fn==(uintptr_t)tty_get_nh_event)return 4;if(fn==(uintptr_t)tty_exit_nhwindows)return 5;if(fn==(uintptr_t)tty_suspend_nhwindows)return 6;if(fn==(uintptr_t)tty_resume_nhwindows)return 7;if(fn==(uintptr_t)tty_create_nhwindow)return 8;if(fn==(uintptr_t)tty_clear_nhwindow)return 9;if(fn==(uintptr_t)tty_display_nhwindow)return 10;if(fn==(uintptr_t)tty_destroy_nhwindow)return 11;if(fn==(uintptr_t)tty_curs)return 12;if(fn==(uintptr_t)tty_putstr)return 13;if(fn==(uintptr_t)tty_putmixed)return 14;if(fn==(uintptr_t)tty_display_file)return 15;if(fn==(uintptr_t)tty_start_menu)return 16;if(fn==(uintptr_t)tty_add_menu)return 17;if(fn==(uintptr_t)tty_end_menu)return 18;if(fn==(uintptr_t)tty_select_menu)return 19;if(fn==(uintptr_t)tty_message_menu)return 20;if(fn==(uintptr_t)tty_mark_synch)return 21;if(fn==(uintptr_t)tty_wait_synch)return 22;if(fn==(uintptr_t)tty_cliparound)return 23;if(fn==(uintptr_t)tty_print_glyph)return 24;if(fn==(uintptr_t)tty_raw_print)return 25;if(fn==(uintptr_t)tty_raw_print_bold)return 26;if(fn==(uintptr_t)tty_nhgetch)return 27;if(fn==(uintptr_t)tty_nh_poskey)return 28;if(fn==(uintptr_t)tty_nhbell)return 29;if(fn==(uintptr_t)tty_doprev_message)return 30;if(fn==(uintptr_t)tty_yn_function)return 31;if(fn==(uintptr_t)tty_getlin)return 32;if(fn==(uintptr_t)tty_get_ext_cmd)return 33;if(fn==(uintptr_t)tty_number_pad)return 34;if(fn==(uintptr_t)tty_delay_output)return 35;if(fn==(uintptr_t)genl_outrip)return 36;if(fn==(uintptr_t)tty_preference_update)return 37;if(fn==(uintptr_t)tty_getmsghistory)return 38;if(fn==(uintptr_t)tty_putmsghistory)return 39;if(fn==(uintptr_t)tty_status_init)return 40;if(fn==(uintptr_t)genl_status_finish)return 41;if(fn==(uintptr_t)tty_status_enablefield)return 42;if(fn==(uintptr_t)tty_status_update)return 43;if(fn==(uintptr_t)genl_can_suspend_yes)return 44;if(fn==(uintptr_t)tty_update_inventory)return 45;if(fn==(uintptr_t)tty_ctrl_nhwindow)return 46;return-1;}
unsigned probe_layout_count(void){return SIZE(wintty_layout);}const char*probe_layout_name(unsigned i){return wintty_layout[i].name;}size_t probe_layout_value(unsigned i){return wintty_layout[i].value;}
size_t probe_stack(void){return emscripten_stack_get_current();}const char*probe_trace(void){return tracebuf;}int probe_error(void){return escape_code;}uintptr_t probe_return(void){return returned;}void*probe_buffer(int i){return buffers[i];}void*probe_ints(void){return integers;}void*probe_window(int i){return wins[i];}void*probe_display(void){return ttyDisplay;}void*probe_storage(int i){return teleport_wintty_data_storage(i);}void*probe_shadow(void){return nomux_buf;}
const char *probe_name(void){return svp.plname;}
void probe_input(const char*s){strcpy(input,s);inputpos=0;}void probe_option(int i,int value){opts[i]=value;}void probe_clear(void){tracebuf[0]=0;returned=0;escape_code=0;nested=0;}
void probe_signal(int sig){if(handler)handler(sig);}
int probe_pointer_kind(uintptr_t p){if(!p)return-1;for(int i=0;i<MAXWIN;i++)if((uintptr_t)wins[i]==p)return i;if(p==(uintptr_t)ttyDisplay)return 100;return-2;}
const char*probe_snapshot(void){snprintf(snap,sizeof snap,"base:%d;wins:%d:%d:%d:%d;flags:%d:%d:%d:%d;state:%d:%d;",BASE_WINDOW,WIN_MAP,WIN_MESSAGE,WIN_STATUS,WIN_INVEN,iflags.window_inited,iflags.term_gone,iflags.raw_printed,iflags.wc2_statuslines,program_state.getting_char,program_state.resize_pending);if(ttyDisplay)snprintf(snap+strlen(snap),sizeof snap-strlen(snap),"display:%d:%d:%d:%d:%u:%u:%u:%d:%d:%d:%d:%d:%d:%d:%d;",ttyDisplay->rows,ttyDisplay->cols,ttyDisplay->curx,ttyDisplay->cury,ttyDisplay->color,ttyDisplay->colorflags,ttyDisplay->framecolor,ttyDisplay->attrs,ttyDisplay->toplin,ttyDisplay->rawprint,ttyDisplay->inmore,ttyDisplay->inread,ttyDisplay->intr,ttyDisplay->topl_utf8,ttyDisplay->mixed);for(int i=0;i<MAXWIN;i++)if(wins[i]){struct WinDesc*p=wins[i];snprintf(snap+strlen(snap),sizeof snap-strlen(snap),"w%d:%d:%d:%d:%d:%d:%ld:%ld:%ld:%ld:%ld:%ld:%lu:%ld:%ld:%ld:%d:%d;",i,p->type,p->flags,p->active,p->offx,p->offy,p->rows,p->cols,p->curx,p->cury,p->maxrow,p->maxcol,p->mbehavior,p->plist_size,p->npages,p->nitems,p->how,p->menu_ch);for(tty_menu_item*m=p->mlist;m;m=m->next)snprintf(snap+strlen(snap),sizeof snap-strlen(snap),"mi:%lu:%ld:%d:%d:%d:%u:%d:%d:%s;",m->identifier.a_ulong,m->count,m->attr,m->color,m->selected,m->itemflags,m->selector,m->gselector,m->str);}return snap;}
void probe_set(int field,long value){switch(field){case 0:program_state.done_hup=value;break;case 1:iflags.debug_fuzzer=value;break;case 2:iflags.window_inited=value;break;case 3:program_state.getting_char=value;break;case 4:program_state.resize_pending=value;break;case 5:iflags.wc_color=value;break;case 6:flags.standout=value;break;case 7:iflags.cbreak=value;break;case 8:morc=value;break;case 9:iflags.term_gone=value;break;case 10:iflags.wc_eight_bit_input=value;break;case 11:iflags.wc2_statuslines=value;break;case 12:WIN_MAP=value;break;case 13:WIN_MESSAGE=value;break;case 14:WIN_STATUS=value;break;case 15:WIN_INVEN=value;break;}}
void probe_reset(void){memset(opts,0,sizeof opts);memset(buffers,0,sizeof buffers);memset(integers,0,sizeof integers);memset(&program_state,0,sizeof program_state);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&u,0,sizeof u);memset(&gm,0,sizeof gm);memset(&gt,0,sizeof gt);memset(&gc,0,sizeof gc);memset(&gs,0,sizeof gs);memset(&gg,0,sizeof gg);if(growth){free(growth);growth=0;}handler=0;input[0]=0;inputpos=0;WIN_MAP=WIN_MESSAGE=WIN_STATUS=WIN_INVEN=WIN_ERR;BASE_WINDOW=WIN_ERR;ttyDisplay=0;memset(wins,0,sizeof wins);iflags.msg_history=20;iflags.wc2_statuslines=2;CO=80;LI=24;for(int i=0;i<CONDITION_COUNT;i++)cond_idx[i]=i;probe_clear();}
void probe_invoke(int action,uintptr_t a0,uintptr_t a1,uintptr_t a2,uintptr_t a3,uintptr_t a4,uintptr_t a5,uintptr_t a6,uintptr_t a7,uintptr_t a8){probe_clear();if(setjmp(escape))return;switch(action){
case 0:bail((const char *)a0);break;
case 1:winch_handler((int)a0);break;
case 2:resize_tty();break;
case 3:newclipping((coordxy)a0,(coordxy)a1);break;
case 4:new_status_window();break;
case 5:tty_init_nhwindows((int *)a0,(char **)a1);break;
case 6:tty_preference_update((const char *)a0);break;
case 7:tty_player_selection();break;
case 8:tty_askname();break;
case 9:tty_get_nh_event();break;
case 10:getret();break;
case 11:tty_suspend_nhwindows((const char *)a0);break;
case 12:tty_resume_nhwindows();break;
case 13:tty_exit_nhwindows((const char *)a0);break;
case 14:returned=(uintptr_t)(tty_create_nhwindow((int)a0));break;
case 15:erase_menu_or_text((winid)a0,(struct WinDesc *)a1,(boolean)a2);break;
case 16:free_window_info((struct WinDesc *)a0,(boolean)a1);break;
case 17:tty_clear_nhwindow((winid)a0);break;
case 18:returned=(uintptr_t)(toggle_menu_curr((winid)a0,(tty_menu_item *)a1,(int)a2,(boolean)a3,(boolean)a4,(long)a5));break;
case 19:dmore((struct WinDesc *)a0,(const char *)a1);break;
case 20:set_item_state((winid)a0,(int)a1,(tty_menu_item *)a2);break;
case 21:set_all_on_page((winid)a0,(tty_menu_item *)a1,(tty_menu_item *)a2);break;
case 22:unset_all_on_page((winid)a0,(tty_menu_item *)a1,(tty_menu_item *)a2);break;
case 23:invert_all_on_page((winid)a0,(tty_menu_item *)a1,(tty_menu_item *)a2,(char)a3,(long)a4);break;
case 24:invert_all((winid)a0,(tty_menu_item *)a1,(tty_menu_item *)a2,(char)a3,(long)a4);break;
case 25:toggle_menu_attr((boolean)a0,(int)a1,(int)a2);break;
case 26:process_menu_window((winid)a0,(struct WinDesc *)a1);break;
case 27:process_text_window((winid)a0,(struct WinDesc *)a1);break;
case 28:tty_display_nhwindow((winid)a0,(boolean)a1);break;
case 29:tty_dismiss_nhwindow((winid)a0);break;
case 30:tty_destroy_nhwindow((winid)a0);break;
case 31:erase_tty_screen();break;
case 32:tty_curs((winid)a0,(int)a1,(int)a2);break;
case 33:returned=(uintptr_t)(compress_str((const char *)a0));break;
case 34:tty_putstr((winid)a0,(int)a1,(const char *)a2);break;
case 35:tty_display_file((const char *)a0,(boolean)a1);break;
case 36:tty_start_menu((winid)a0,(unsigned long)a1);break;
case 37:tty_add_menu((winid)a0,(const glyph_info *)a1,(const anything *)a2,(char)a3,(char)a4,(int)a5,(int)a6,(const char *)a7,(unsigned int)a8);break;
case 38:returned=(uintptr_t)(reverse((tty_menu_item *)a0));break;
case 39:tty_end_menu((winid)a0,(const char *)a1);break;
case 40:returned=(uintptr_t)(tty_select_menu((winid)a0,(int)a1,(menu_item **)a2));break;
case 41:returned=(uintptr_t)(tty_message_menu((char)a0,(int)a1,(const char *)a2));break;
case 42:returned=(uintptr_t)(tty_ctrl_nhwindow((winid)a0,(int)a1,(win_request_info *)a2));break;
case 43:tty_update_inventory((int)a0);break;
case 44:tty_mark_synch();break;
case 45:tty_wait_synch();break;
case 46:docorner((int)a0,(int)a1,(int)a2);break;
case 47:end_glyphout();break;
case 48:g_putch((int)a0);break;
case 49:g_pututf8((uint8 *)a0);break;
case 50:setclipped();break;
case 51:tty_cliparound((int)a0,(int)a1);break;
case 52:tty_print_glyph((winid)a0,(coordxy)a1,(coordxy)a2,(const glyph_info *)a3,(const glyph_info *)a4);break;
case 53:tty_raw_print((const char *)a0);break;
case 54:tty_raw_print_bold((const char *)a0);break;
case 55:returned=(uintptr_t)(tty_nhgetch());break;
case 56:returned=(uintptr_t)(tty_nh_poskey((coordxy *)a0,(coordxy *)a1,(int *)a2));break;
case 57:win_tty_init((int)a0);break;
case 58:tty_putmixed((winid)a0,(int)a1,(const char *)a2);break;
case 59:tty_status_init();break;
case 60:tty_status_enablefield((int)a0,(const char *)a1,(const char *)a2,(boolean)a3);break;
case 61:tty_status_update((int)a0,(genericptr_t)a1,(int)a2,(int)a3,(int)a4,(unsigned long *)a5);break;
case 62:returned=(uintptr_t)(make_things_fit((boolean)a0));break;
case 63:returned=(uintptr_t)(check_fields((boolean)a0,(int *)a1));break;
case 64:tty_putstatusfield((const char *)a0,(int)a1,(int)a2);break;
case 65:set_condition_length();break;
case 66:shrink_enc((int)a0);break;
case 67:shrink_dlvl((int)a0);break;
case 68:returned=(uintptr_t)(check_windowdata());break;
case 69:returned=(uintptr_t)(condcolor((long)a0,(unsigned long *)a1));break;
case 70:returned=(uintptr_t)(condattr((long)a0,(unsigned long *)a1));break;
case 71:render_status();break;
}}
void probe_release(void*p){free(p); }
void*probe_menu_item(int id,int index){tty_menu_item*p=wins[id]->mlist;while(index-->0&&p)p=p->next;return p;}
void probe_window_set(int id,int field,long v){struct WinDesc*p=wins[id];switch(field){case 0:p->active=v;break;case 1:p->curx=v;break;case 2:p->cury=v;break;case 3:p->flags=v;break;case 4:p->mbehavior=v;break;case 5:p->how=v;break;}}
const char*probe_data(int id,int row){return wins[id]->data[row];}
const char*probe_status_value(int i){return status_vals[i];}
static glyph_info glyphs[2];static struct unicode_representation unicode;
void*probe_glyph(int i,int ch,int color,unsigned special,uint32 rgb,uint16 idx,const char*utf8){glyphs[i]=nul_glyphinfo;glyphs[i].ttychar=ch;glyphs[i].framecolor=NO_COLOR;glyphs[i].gm.sym.color=color;glyphs[i].gm.glyphflags=special;glyphs[i].gm.customcolor=rgb;glyphs[i].gm.color256idx=idx;unicode.utf8str=(uint8*)utf8;glyphs[i].gm.u=utf8?&unicode:0;return &glyphs[i];}
void probe_graphics(int handling,unsigned colorcount,int inverse,int pets,int piles,int hitbar){gs.symset[gc.currentgraphics].handling=handling;iflags.colorcount=colorcount;iflags.wc_inverse=inverse;iflags.wc_hilite_pet=pets;iflags.hilite_pile=piles;iflags.wc2_hitpointbar=hitbar;iflags.wc2_petattr=ATR_BOLD;}
