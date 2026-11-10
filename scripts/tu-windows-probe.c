/* Controlled foreign window/stdio/queue dependencies; original WINDOWS is
 * compiled only for reference. No OS terminal messages are sent. */
#include "hack.h"
#include "wintty.h"
#include "tu-windows-layout.h"
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <emscripten.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef free
extern void free(void*);
__typeof__(iflags)iflags;__typeof__(flags)flags;__typeof__(program_state)program_state;
__typeof__(gb)gb;__typeof__(go)go;__typeof__(gl)gl;__typeof__(gm)gm;__typeof__(gs)gs;__typeof__(svc)svc;__typeof__(cg)cg;__typeof__(gw)gw;__typeof__(gg)gg;
winid WIN_STATUS;
const char hexdd[33]="00112233445566778899aAbBcCdDeEfF";
const glyph_info nul_glyphinfo = {
    NO_GLYPH, ' ', NO_COLOR,
        {  /* glyph_map */
            MG_UNEXPL,
            { NO_COLOR, SYM_UNEXPLORED + SYM_OFF_X },
              0,
              0U, 0U
#ifdef ENHANCED_SYMBOLS
               , 0
#endif
        }
};
static char input[8192],output[32768],query[8192],selection[8192],filetext[32768],tracebuf[2097152],snapshotbuf[2097152],encoded[128];
static long callback_sp;
static int pos,opts[24],allocs,frees,callback_depth,filepos,fileopen;static unsigned filetoken;static void*growth;
static menu_item*last_pick;static struct _cmd_queue*queue[256];static int queued,qhead;
struct allocation{void*p;unsigned n;int live;};static struct allocation allocation[2048];
static int identity(void*p){int i;for(i=allocs-1;i>=0;i--)if(allocation[i].live&&allocation[i].p==p)return i+1;return 0;}
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);}
static void callback(void);
EM_JS(void,fixture_throw,(int why),{throw new Error('WINDOWS fixture exit '+why);});
long*alloc(unsigned n){void*p=malloc(n);if(!p||allocs>=SIZE(allocation))abort();allocation[allocs++]=(struct allocation){p,n,1};if(opts[0])logmsg("alloc:%u;",n);callback();return p;}
void teleport_probe_free(void*p){if(p){int i=identity(p);if(!i)abort();allocation[i-1].live=0;frees++;if(opts[0])logmsg("free:%d;",i);free(p);}}
#define free teleport_probe_free
void panic(const char*f,...){va_list ap;va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);fixture_throw(1);__builtin_unreachable();}
void impossible(const char*f,...){(void)f;fixture_throw(2);}
void nh_terminate(int status){logmsg("terminate:%d;",status);fixture_throw(10+status);__builtin_unreachable();}
boolean debugcore(const char*file,boolean wild){logmsg("debug:%s:%d;",file,wild);return opts[7];}
void pline(const char*f,...){va_list ap;logmsg("pline:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");iflags.last_msg=17;callback();}
void raw_printf(const char*f,...){va_list ap;logmsg("raw:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void config_error_add(const char*f,...){va_list ap;logmsg("config:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
int teleport_probe_puts(const char*s){logmsg("puts:%s;",s);callback();return 0;}
FILE*teleport_probe_fopen(const char*name,const char*mode){logmsg("open:%s:%s;",name,mode);filepos=0;fileopen=!opts[8];return fileopen?(FILE*)&filetoken:0;}
char*teleport_probe_fgets(char*s,int n,FILE*fp){int i=0;(void)fp;if(!filetext[filepos])return 0;while(i<n-1&&filetext[filepos]){char c=filetext[filepos++];s[i++]=c;if(c=='\n')break;}s[i]=0;return s;}
int teleport_probe_fclose(FILE*fp){(void)fp;logmsg("close;");fileopen=0;return 0;}
int teleport_probe_fputs(const char*s,FILE*fp){(void)fp;logmsg("write:%s;",s);callback();return opts[9]?-1:0;}
int teleport_probe_fprintf(FILE*fp,const char*f,...){va_list ap;int n;(void)fp;logmsg("fprintf:");va_start(ap,f);n=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);pos+=n;logmsg(";");callback();return n;}
struct _cmd_queue*cmdq_pop(void){return qhead<queued?queue[qhead++]:0;}
boolean regex_match(const char*s,struct nhregex*pattern){logmsg("regex:%s:%d;",s,(int)(intptr_t)pattern);return opts[10]==(int)(intptr_t)pattern;}
void map_glyphinfo(coordxy x,coordxy y,int glyph,unsigned mgflags,glyph_info*gip){(void)x;(void)y;*gip=nul_glyphinfo;gip->glyph=glyph;gip->ttychar=(glyph%94)+33;gip->gm.sym.symidx=(glyph<0?0:glyph)%MAXPCHARS;gip->gm.customcolor=(uint32)glyph*17U;gip->framecolor=(uint32)mgflags;callback();}
void backend_win_init_nhwindows(int * a0,char ** a1){logmsg("win_init_nhwindows;");callback();}
void backend_win_player_selection(void){logmsg("win_player_selection;");callback();}
void backend_win_askname(void){logmsg("win_askname;");callback();}
void backend_win_get_nh_event(void){logmsg("win_get_nh_event;");callback();}
void backend_win_exit_nhwindows(const char * a0){logmsg("win_exit_nhwindows:%s;",a0?a0:"(null)");callback();}
void backend_win_suspend_nhwindows(const char * a0){logmsg("win_suspend_nhwindows;");callback();}
void backend_win_resume_nhwindows(void){logmsg("win_resume_nhwindows;");callback();}
winid backend_win_create_nhwindow(int a0){logmsg("create:%d;",a0);callback();return 17;}
void backend_win_clear_nhwindow(winid a0){logmsg("win_clear_nhwindow;");callback();}
void backend_win_display_nhwindow(winid a0,boolean a1){logmsg("display:%d:%d;",a0,a1);callback();}
void backend_win_destroy_nhwindow(winid a0){logmsg("win_destroy_nhwindow;");callback();}
void backend_win_curs(winid a0,int a1,int a2){logmsg("curs:%d:%d:%d;",a0,a1,a2);callback();}
void backend_win_putstr(winid a0,int a1,const char * a2){logmsg("win_putstr:%d:%d:%s;",a0,a1,a2);callback();}
void backend_win_putmixed(winid a0,int a1,const char * a2){logmsg("win_putmixed:%d:%d:%s;",a0,a1,a2);callback();}
void backend_win_display_file(const char * a0,boolean a1){logmsg("win_display_file;");callback();}
void backend_win_start_menu(winid a0,unsigned long a1){logmsg("start:%d:%lu;",a0,a1);callback();}
void backend_win_add_menu(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){if(opts[12]){long sp=emscripten_stack_get_current();if(!callback_sp)callback_sp=sp;logmsg("callback-sp:%ld;",sp-callback_sp);}logmsg("add:%d:%d:%d:%d:%d:%d:%d:%s:%u;",a0,a1?a1->glyph:-999,a2?a2->a_int:0,a3,a4,a5,a6,a7,a8);callback();}
void backend_win_end_menu(winid a0,const char * a1){logmsg("end:%d:%s;",a0,a1?a1:"(null)");callback();}
int backend_win_select_menu(winid a0,int a1,struct mi ** a2){int i,n=opts[1];logmsg("select:%d:%d:%d;",a0,a1,gb.bot_disabled);*a2=0;if(n>0){*a2=(menu_item*)alloc(n*sizeof **a2);last_pick=*a2;for(i=0;i<n;i++){(*a2)[i].item.a_int=selection[i]?selection[i]:'a'+i;(*a2)[i].count=9007199254740997L+i;(*a2)[i].itemflags=0x80000000U+i;}}callback();return opts[1];}
char backend_win_message_menu(char a0,int a1,const char * a2){logmsg("message:%d:%d:%s;",a0,a1,a2);callback();return 7;}
void backend_win_mark_synch(void){logmsg("win_mark_synch;");callback();}
void backend_win_wait_synch(void){logmsg("win_wait_synch;");callback();}
void backend_win_cliparound(int a0,int a1){logmsg("win_cliparound;");callback();}
void backend_win_print_glyph(winid a0,coordxy a1,coordxy a2,const glyph_info * a3,const glyph_info * a4){logmsg("glyph:%d:%d:%d:%d:%d;",a0,a1,a2,a3?a3->glyph:-999,a4?a4->glyph:-999);callback();}
void backend_win_raw_print(const char * a0){logmsg("win_raw_print:%s;",a0?a0:"(null)");callback();}
void backend_win_raw_print_bold(const char * a0){logmsg("win_raw_print_bold:%s;",a0?a0:"(null)");callback();}
int backend_win_nhgetch(void){logmsg("win_nhgetch;");callback();return 7;}
int backend_win_nh_poskey(coordxy * a0,coordxy * a1,int * a2){logmsg("win_nh_poskey;");callback();return 7;}
void backend_win_nhbell(void){logmsg("win_nhbell;");callback();}
int backend_win_doprev_message(void){logmsg("win_doprev_message;");callback();return 7;}
char backend_win_yn_function(const char * a0,const char * a1,char a2){logmsg("win_yn_function;");callback();return 7;}
void backend_win_getlin(const char * a0,char * a1){logmsg("getlin:%s:%d:%d;",a0,gb.bot_disabled,program_state.in_getlin);strcpy(a1,input);callback();}
int backend_win_get_ext_cmd(void){logmsg("win_get_ext_cmd;");callback();return 7;}
void backend_win_number_pad(int a0){logmsg("win_number_pad;");callback();}
void backend_win_delay_output(void){logmsg("win_delay_output;");callback();}
void backend_win_outrip(winid a0,int a1,time_t a2){logmsg("outrip:%d:%d:%lld;",a0,a1,a2);callback();}
void backend_win_preference_update(const char * a0){logmsg("win_preference_update;");callback();}
char * backend_win_getmsghistory(boolean a0){logmsg("win_getmsghistory;");callback();return query;}
void backend_win_putmsghistory(const char * a0,boolean a1){logmsg("win_putmsghistory;");callback();}
void backend_win_status_init(void){logmsg("win_status_init;");callback();}
void backend_win_status_finish(void){logmsg("win_status_finish;");callback();}
void backend_win_status_enablefield(int a0,const char * a1,const char * a2,boolean a3){logmsg("win_status_enablefield;");callback();}
void backend_win_status_update(int a0,genericptr_t a1,int a2,int a3,int a4,unsigned long * a5){logmsg("status:%d:%d:%d:%d:%lu;",a0,a2,a3,a4,a5?*a5:0);callback();}
boolean backend_win_can_suspend(void){logmsg("win_can_suspend;");callback();return 7;}
void backend_win_update_inventory(int a0){logmsg("win_update_inventory;");callback();}
win_request_info * backend_win_ctrl_nhwindow(winid a0,int a1,win_request_info * a2){logmsg("ctrl:%d:%d:%ld:%d:%d;",a0,a1,a2?a2->tocore.tocore_flags:0,a2?a2->fromcore.menu_promptstyle.color:0,a2?a2->fromcore.menu_promptstyle.attr:0);callback();return a2;}
struct window_procs tty_procs={.name="tty",.wp_id=wp_tty,.wincap=WC_COLOR,.wincap2=WC2_FLUSH_STATUS,
.win_init_nhwindows=backend_win_init_nhwindows,
.win_player_selection=backend_win_player_selection,
.win_askname=backend_win_askname,
.win_get_nh_event=backend_win_get_nh_event,
.win_exit_nhwindows=backend_win_exit_nhwindows,
.win_suspend_nhwindows=backend_win_suspend_nhwindows,
.win_resume_nhwindows=backend_win_resume_nhwindows,
.win_create_nhwindow=backend_win_create_nhwindow,
.win_clear_nhwindow=backend_win_clear_nhwindow,
.win_display_nhwindow=backend_win_display_nhwindow,
.win_destroy_nhwindow=backend_win_destroy_nhwindow,
.win_curs=backend_win_curs,
.win_putstr=backend_win_putstr,
.win_putmixed=backend_win_putmixed,
.win_display_file=backend_win_display_file,
.win_start_menu=backend_win_start_menu,
.win_add_menu=backend_win_add_menu,
.win_end_menu=backend_win_end_menu,
.win_select_menu=backend_win_select_menu,
.win_message_menu=backend_win_message_menu,
.win_mark_synch=backend_win_mark_synch,
.win_wait_synch=backend_win_wait_synch,
.win_cliparound=backend_win_cliparound,
.win_print_glyph=backend_win_print_glyph,
.win_raw_print=backend_win_raw_print,
.win_raw_print_bold=backend_win_raw_print_bold,
.win_nhgetch=backend_win_nhgetch,
.win_nh_poskey=backend_win_nh_poskey,
.win_nhbell=backend_win_nhbell,
.win_doprev_message=backend_win_doprev_message,
.win_yn_function=backend_win_yn_function,
.win_getlin=backend_win_getlin,
.win_get_ext_cmd=backend_win_get_ext_cmd,
.win_number_pad=backend_win_number_pad,
.win_delay_output=backend_win_delay_output,
.win_outrip=backend_win_outrip,
.win_preference_update=backend_win_preference_update,
.win_getmsghistory=backend_win_getmsghistory,
.win_putmsghistory=backend_win_putmsghistory,
.win_status_init=backend_win_status_init,
.win_status_finish=backend_win_status_finish,
.win_status_enablefield=backend_win_status_enablefield,
.win_status_update=backend_win_status_update,
.win_can_suspend=backend_win_can_suspend,
.win_update_inventory=backend_win_update_inventory,
.win_ctrl_nhwindow=backend_win_ctrl_nhwindow};
void win_tty_init(int mode){logmsg("ttyinit:%d;",mode);callback();}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/windows.c"
#define TELEPORT_WINDOWS_VALIDATE_SOURCE 1
#else
extern void teleport_windows_callback_def_raw_print(const char *);
#define def_raw_print teleport_windows_callback_def_raw_print
extern void teleport_windows_callback_def_wait_synch(void);
#define def_wait_synch teleport_windows_callback_def_wait_synch
extern struct win_choices * teleport_windows_callback_win_choices_find(const char *);
#define win_choices_find teleport_windows_callback_win_choices_find
extern void teleport_windows_callback_hup_exit_nhwindows(const char *);
#define hup_exit_nhwindows teleport_windows_callback_hup_exit_nhwindows
extern int teleport_windows_callback_hup_nhgetch(void);
#define hup_nhgetch teleport_windows_callback_hup_nhgetch
extern char teleport_windows_callback_hup_yn_function(const char *,const char *,char);
#define hup_yn_function teleport_windows_callback_hup_yn_function
extern int teleport_windows_callback_hup_nh_poskey(coordxy *,coordxy *,int *);
#define hup_nh_poskey teleport_windows_callback_hup_nh_poskey
extern void teleport_windows_callback_hup_getlin(const char *,char *);
#define hup_getlin teleport_windows_callback_hup_getlin
extern void teleport_windows_callback_hup_init_nhwindows(int *,char **);
#define hup_init_nhwindows teleport_windows_callback_hup_init_nhwindows
extern winid teleport_windows_callback_hup_create_nhwindow(int);
#define hup_create_nhwindow teleport_windows_callback_hup_create_nhwindow
extern int teleport_windows_callback_hup_select_menu(winid,int,struct mi **);
#define hup_select_menu teleport_windows_callback_hup_select_menu
extern void teleport_windows_callback_hup_add_menu(winid,const glyph_info *,const anything *,char,char,int,int,const char *,unsigned int);
#define hup_add_menu teleport_windows_callback_hup_add_menu
extern void teleport_windows_callback_hup_end_menu(winid,const char *);
#define hup_end_menu teleport_windows_callback_hup_end_menu
extern void teleport_windows_callback_hup_putstr(winid,int,const char *);
#define hup_putstr teleport_windows_callback_hup_putstr
extern void teleport_windows_callback_hup_print_glyph(winid,coordxy,coordxy,const glyph_info *,const glyph_info *);
#define hup_print_glyph teleport_windows_callback_hup_print_glyph
extern void teleport_windows_callback_hup_outrip(winid,int,time_t);
#define hup_outrip teleport_windows_callback_hup_outrip
extern void teleport_windows_callback_hup_curs(winid,int,int);
#define hup_curs teleport_windows_callback_hup_curs
extern void teleport_windows_callback_hup_display_nhwindow(winid,boolean);
#define hup_display_nhwindow teleport_windows_callback_hup_display_nhwindow
extern void teleport_windows_callback_hup_display_file(const char *,boolean);
#define hup_display_file teleport_windows_callback_hup_display_file
extern void teleport_windows_callback_hup_cliparound(int,int);
#define hup_cliparound teleport_windows_callback_hup_cliparound
extern void teleport_windows_callback_hup_status_update(int,genericptr_t,int,int,int,unsigned long *);
#define hup_status_update teleport_windows_callback_hup_status_update
extern int teleport_windows_callback_hup_int_ndecl(void);
#define hup_int_ndecl teleport_windows_callback_hup_int_ndecl
extern void teleport_windows_callback_hup_void_ndecl(void);
#define hup_void_ndecl teleport_windows_callback_hup_void_ndecl
extern void teleport_windows_callback_hup_void_fdecl_int(int);
#define hup_void_fdecl_int teleport_windows_callback_hup_void_fdecl_int
extern void teleport_windows_callback_hup_void_fdecl_winid(winid);
#define hup_void_fdecl_winid teleport_windows_callback_hup_void_fdecl_winid
extern void teleport_windows_callback_hup_void_fdecl_winid_ulong(winid,unsigned long);
#define hup_void_fdecl_winid_ulong teleport_windows_callback_hup_void_fdecl_winid_ulong
extern void teleport_windows_callback_hup_void_fdecl_constchar_p(const char *);
#define hup_void_fdecl_constchar_p teleport_windows_callback_hup_void_fdecl_constchar_p
extern win_request_info * teleport_windows_callback_hup_ctrl_nhwindow(winid,int,win_request_info *);
#define hup_ctrl_nhwindow teleport_windows_callback_hup_ctrl_nhwindow
extern void teleport_windows_callback_dump_putstr(winid,int,const char *);
#define dump_putstr teleport_windows_callback_dump_putstr
extern winid teleport_windows_callback_dump_create_nhwindow(int);
#define dump_create_nhwindow teleport_windows_callback_dump_create_nhwindow
extern void teleport_windows_callback_dump_clear_nhwindow(winid);
#define dump_clear_nhwindow teleport_windows_callback_dump_clear_nhwindow
extern void teleport_windows_callback_dump_display_nhwindow(winid,boolean);
#define dump_display_nhwindow teleport_windows_callback_dump_display_nhwindow
extern void teleport_windows_callback_dump_destroy_nhwindow(winid);
#define dump_destroy_nhwindow teleport_windows_callback_dump_destroy_nhwindow
extern void teleport_windows_callback_dump_start_menu(winid,unsigned long);
#define dump_start_menu teleport_windows_callback_dump_start_menu
extern void teleport_windows_callback_dump_add_menu(winid,const glyph_info *,const anything *,char,char,int,int,const char *,unsigned int);
#define dump_add_menu teleport_windows_callback_dump_add_menu
extern void teleport_windows_callback_dump_end_menu(winid,const char *);
#define dump_end_menu teleport_windows_callback_dump_end_menu
extern int teleport_windows_callback_dump_select_menu(winid,int,menu_item **);
#define dump_select_menu teleport_windows_callback_dump_select_menu
extern boolean teleport_windows_callback_get_menu_coloring(const char *,int *,int *);
#define get_menu_coloring teleport_windows_callback_get_menu_coloring
extern void teleport_windows_initialize(void);
#endif
#include "../nethack-c/wasm/tu-fragments/windows-support.c"
static void callback(void){if(opts[3]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}if(opts[4]&&!callback_depth){opts[4]=0;callback_depth++;logmsg("reentry:%d;",genl_can_suspend_yes());callback_depth--;}if(opts[5])fixture_throw(5);}
extern void teleport_windows_consumer_copy(win_request_info*);
extern long teleport_windows_consumer_status(int,int);
void probe_initialize(void){
#ifndef TELEPORT_REFERENCE_TU
teleport_windows_initialize();
#endif
}
void probe_clear(void){pos=0;tracebuf[0]=0;}
void probe_reset(void){int i;for(i=0;i<allocs;i++)if(allocation[i].live){
#undef free
free(allocation[i].p);
#define free teleport_probe_free
}if(growth){
#undef free
free(growth);
#define free teleport_probe_free
growth=0;}memset(allocation,0,sizeof allocation);allocs=frees=0;last_pick=0;memset(opts,0,sizeof opts);queued=qhead=0;callback_sp=0;memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(&gb,0,sizeof gb);memset(&go,0,sizeof go);memset(&gl,0,sizeof gl);memset(&gm,0,sizeof gm);memset(&svc,0,sizeof svc);memset(&gw,0,sizeof gw);memset((void*)&windowprocs,0,sizeof windowprocs);memset(status_vals,0,sizeof status_vals);memset(status_fieldfmt,0,sizeof status_fieldfmt);memset(status_fieldnm,0,sizeof status_fieldnm);memset(status_activefields,0,sizeof status_activefields);input[0]=output[0]=query[0]=selection[0]=filetext[0]=encoded[0]=0;teleport_windows_private_set(0,0);teleport_windows_private_set(1,0);for(i=0;i<MAXPCHARS;i++)gs.showsyms[i]='!'+i%90;tty_procs.wincap=WC_COLOR;tty_procs.wincap2=WC2_FLUSH_STATUS;for(i=0;i<CLR_MAX;i++)tty_procs.has_color[i]=i&1;probe_clear();}
char*probe_buffer(int i){switch(i){case 0:return input;case 1:return output;case 2:return query;case 3:return selection;case 4:return filetext;case 5:return encoded;}return 0;}
void probe_option(int i,int v){opts[i]=v;}
long probe_field(int i,long v){switch(i){case 100:tty_procs.wincap=(unsigned long)v;return tty_procs.wincap;case 101:tty_procs.wincap2=(unsigned long)v;return tty_procs.wincap2;default:teleport_windows_set_global(i,v);return teleport_windows_global(i);}}
void probe_queue(int typ,int key){struct _cmd_queue*q=(struct _cmd_queue*)alloc(sizeof *q);memset(q,0,sizeof *q);q->typ=typ;q->key=key;queue[queued++]=q;}
void probe_menucolor(int i,int clr,int attr){static struct menucoloring colors[4];colors[i].match=(struct nhregex*)(intptr_t)(i+1);colors[i].color=clr;colors[i].attr=attr;colors[i].next=i?0:&colors[1];gm.menu_colorings=&colors[0];}
long probe_storage(int n,int field,long value){void*p=teleport_windows_storage(n);teleport_windows_set(n==4?5:0,field,p,0,value);return teleport_windows_get(n==4?5:0,field,p,0);}
long probe_consumer(int kind,int i){win_request_info wri;teleport_windows_consumer_copy(&wri);if(kind==0)return wri.tocore.tocore_flags;if(kind==1)return wri.fromcore.menu_promptstyle.color;if(kind==2)return wri.fromcore.menu_promptstyle.attr;return teleport_windows_consumer_status(kind-3,i);}
void probe_dump(int on){teleport_windows_private_set(1,on?(long)(intptr_t)&filetoken:0);memcpy(teleport_windows_storage(3),(void*)&windowprocs,sizeof windowprocs);}
static glyph_info glyph;static anything any;static color_attr style;static long condition;static int extra;static menu_item*pick;
long probe_call(int action,int a,int b,long wide){switch(action){
case 0:return genl_can_suspend_no();case 1:return genl_can_suspend_yes();case 2:def_raw_print(input);break;case 3:def_wait_synch();break;
case 4:return check_tty_wincap((unsigned long)wide);case 5:return check_tty_wincap2((unsigned long)wide);case 6:return win_choices_find(input)==teleport_windows_storage(1);case 7:choose_windows(input);break;case 8:return genl_message_menu(a,b,input);case 9:genl_preference_update(input);break;case 10:return genl_getmsghistory(a)!=0;case 11:genl_putmsghistory(input,a);break;
case 12:nhwindows_hangup();break;case 13:hup_exit_nhwindows(input);break;case 14:return hup_nhgetch();case 15:return hup_yn_function(input,query,a);case 16:return hup_nh_poskey(0,0,0);case 17:hup_getlin(input,output);break;case 18:hup_init_nhwindows(0,0);break;case 19:return hup_create_nhwindow(a);case 20:return hup_select_menu(a,b,&pick);case 21:hup_add_menu(a,&glyph,&any,13,17,2,3,input,(unsigned)wide);break;case 22:hup_end_menu(a,input);break;case 23:hup_putstr(a,b,input);break;case 24:hup_print_glyph(a,b,b,&glyph,&glyph);break;case 25:hup_outrip(a,b,wide);break;case 26:hup_curs(a,b,12);break;case 27:hup_display_nhwindow(a,b);break;case 28:hup_display_file(input,a);break;case 29:hup_cliparound(a,b);break;case 30:hup_status_update(a,&condition,b,15,3,(unsigned long*)&wide);break;case 31:return hup_int_ndecl();case 32:hup_void_ndecl();break;case 33:hup_void_fdecl_int(a);break;case 34:hup_void_fdecl_winid(a);break;case 35:hup_void_fdecl_winid_ulong(a,(unsigned long)wide);break;case 36:hup_void_fdecl_constchar_p(input);break;case 37:return hup_ctrl_nhwindow(a,b,0)!=0;
case 38:genl_status_init();break;case 39:genl_status_finish();break;case 40:genl_status_enablefield(a,query,opts[11]==0?"%s":opts[11]==1?"[%s]":opts[11]==2?"%10s":opts[11]==3?"":0,b);break;case 41:condition=wide;genl_status_update(a,a==BL_CONDITION?(void*)&condition:(void*)input,0,0,0,0);break;
case 42:dump_open_log(wide);break;case 43:dump_close_log();break;case 44:dump_forward_putstr(a,b,input,(int)wide);break;case 45:dump_putstr(a,b,input);break;case 46:return dump_create_nhwindow(a);case 47:dump_clear_nhwindow(a);break;case 48:dump_display_nhwindow(a,b);break;case 49:dump_destroy_nhwindow(a);break;case 50:dump_start_menu(a,(unsigned long)wide);break;case 51:glyph.glyph=b;dump_add_menu(a,&glyph,&any,13,17,2,3,input,(unsigned)wide);break;case 52:dump_end_menu(a,b?input:0);break;case 53:return dump_select_menu(a,b,&pick);case 54:dump_redirect(a);break;
case 55:return has_color(a);case 56:return glyph2ttychar(a);case 57:return glyph2symidx(a);case 58:strcpy(encoded,encglyph(a));break;case 59:extra=(int)wide;{int n=decode_glyph(input,&extra);sprintf(output,"%d",extra);return n;}case 60:decode_mixed(output,a?input:0);break;case 61:genl_putmixed(a,b,input);break;case 62:genl_display_file(input,a);break;case 63:return menuitem_invert_test(a,(unsigned)wide,b);case 64:{const char*p=mixed_to_glyphinfo(a?input:0,b?&glyph:0);strcpy(output,p);return p>=input&&p<=input+sizeof input?p-input:-1;}case 65:return choose_classes_menu(query,a,b,input,selection);case 66:style.color=a;style.attr=b;adjust_menu_promptstyle(17,&style);break;case 67:any.a_int=b;add_menu(17,&glyph,&any,13,17,a,b,wide?input:0,(unsigned)wide);break;case 68:add_menu_heading(a,input);break;case 69:add_menu_str(a,input);break;case 70:{int clr=a,attr=b,n=get_menu_coloring(input,&clr,&attr);sprintf(output,"%d/%d",clr,attr);return n;}case 71:return select_menu(a,b,&pick);case 72:getlin(query,output);break;
}return 0;}
void probe_null_status_format(int i){status_fieldfmt[i]=0;}
int probe_enc_alias(int a,int b){char*p=encglyph(a);char*q=encglyph(b);strcpy(encoded,p);return p==q;}
char*probe_trace(void){return tracebuf;}
char*probe_snapshot(void){char*p=snapshotbuf;int i;
#define APP(...) p+=sprintf(p,__VA_ARGS__)
APP("alloc:%d/%d;queue:%d/%d;global:",allocs,frees,qhead,queued);for(i=0;i<SIZE(teleport_windows_layout);i++){}for(i=0;i<18;i++)if(i!=13&&i!=14)APP("%ld,",teleport_windows_global(i));APP("wp:%s/%d/%lu/%lu;",windowprocs.name?windowprocs.name:"",windowprocs.wp_id,windowprocs.wincap,windowprocs.wincap2);for(i=0;i<CLR_MAX;i++)APP("%d,",windowprocs.has_color[i]);APP("lastchoice:%d;",gl.last_winchoice==teleport_windows_storage(1));APP("private:%d/%d;",!!teleport_windows_private_get(0),!!teleport_windows_private_get(1));APP("status:");for(i=0;i<MAXBLSTATS;i++)APP("%d/%s/%s/%d:%s;",status_activefields[i],status_fieldnm[i]?status_fieldnm[i]:"",status_fieldfmt[i]?status_fieldfmt[i]:"",identity(status_vals[i]),status_vals[i]?status_vals[i]:"");APP("glyph:%d/%d/%u/%d/%u;pick:%d;",glyph.glyph,glyph.ttychar,glyph.framecolor,glyph.gm.sym.symidx,glyph.gm.customcolor,identity(pick));if(pick&&identity(pick))APP("%d/%ld/%u;",pick[0].item.a_int,pick[0].count,pick[0].itemflags);APP("wri:%ld/%d/%d;",zerowri.tocore.tocore_flags,zerowri.fromcore.menu_promptstyle.color,zerowri.fromcore.menu_promptstyle.attr);return snapshotbuf;
#undef APP
}
long probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return SIZE(teleport_windows_layout);}const char*probe_layout_name(int i){return teleport_windows_layout[i].name;}long probe_layout_value(int i){return teleport_windows_layout[i].value;}
long probe_callback_id(int field){void*p=(void*)(intptr_t)teleport_windows_get(0,field,(void*)&windowprocs,0);int i;if(!p)return -1;for(i=0;i<73;i++)if(p==teleport_windows_function_address(i))return i;switch(field){
case 5:return p==(void*)backend_win_init_nhwindows?100:999;
case 6:return p==(void*)backend_win_player_selection?101:999;
case 7:return p==(void*)backend_win_askname?102:999;
case 8:return p==(void*)backend_win_get_nh_event?103:999;
case 9:return p==(void*)backend_win_exit_nhwindows?104:999;
case 10:return p==(void*)backend_win_suspend_nhwindows?105:999;
case 11:return p==(void*)backend_win_resume_nhwindows?106:999;
case 12:return p==(void*)backend_win_create_nhwindow?107:999;
case 13:return p==(void*)backend_win_clear_nhwindow?108:999;
case 14:return p==(void*)backend_win_display_nhwindow?109:999;
case 15:return p==(void*)backend_win_destroy_nhwindow?110:999;
case 16:return p==(void*)backend_win_curs?111:999;
case 17:return p==(void*)backend_win_putstr?112:999;
case 18:return p==(void*)backend_win_putmixed?113:999;
case 19:return p==(void*)backend_win_display_file?114:999;
case 20:return p==(void*)backend_win_start_menu?115:999;
case 21:return p==(void*)backend_win_add_menu?116:999;
case 22:return p==(void*)backend_win_end_menu?117:999;
case 23:return p==(void*)backend_win_select_menu?118:999;
case 24:return p==(void*)backend_win_message_menu?119:999;
case 25:return p==(void*)backend_win_mark_synch?120:999;
case 26:return p==(void*)backend_win_wait_synch?121:999;
case 27:return p==(void*)backend_win_cliparound?122:999;
case 28:return p==(void*)backend_win_print_glyph?123:999;
case 29:return p==(void*)backend_win_raw_print?124:999;
case 30:return p==(void*)backend_win_raw_print_bold?125:999;
case 31:return p==(void*)backend_win_nhgetch?126:999;
case 32:return p==(void*)backend_win_nh_poskey?127:999;
case 33:return p==(void*)backend_win_nhbell?128:999;
case 34:return p==(void*)backend_win_doprev_message?129:999;
case 35:return p==(void*)backend_win_yn_function?130:999;
case 36:return p==(void*)backend_win_getlin?131:999;
case 37:return p==(void*)backend_win_get_ext_cmd?132:999;
case 38:return p==(void*)backend_win_number_pad?133:999;
case 39:return p==(void*)backend_win_delay_output?134:999;
case 40:return p==(void*)backend_win_outrip?135:999;
case 41:return p==(void*)backend_win_preference_update?136:999;
case 42:return p==(void*)backend_win_getmsghistory?137:999;
case 43:return p==(void*)backend_win_putmsghistory?138:999;
case 44:return p==(void*)backend_win_status_init?139:999;
case 45:return p==(void*)backend_win_status_finish?140:999;
case 46:return p==(void*)backend_win_status_enablefield?141:999;
case 47:return p==(void*)backend_win_status_update?142:999;
case 48:return p==(void*)backend_win_can_suspend?143:999;
case 49:return p==(void*)backend_win_update_inventory?144:999;
case 50:return p==(void*)backend_win_ctrl_nhwindow?145:999;
}return 999;}
