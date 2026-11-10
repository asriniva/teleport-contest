/* Typed ABI/header/dependency access and mutable zero-only source storage.
 * All WINDOWS algorithms, tables and source initializers are JS. */
#include "../../../scripts/tu-windows-layout.h"
#include <stdint.h>
#include "windows-source-data.h"
#include <stdio.h>
#include <string.h>
#include "dlb.h"
extern const char*status_fieldnm[MAXBLSTATS];extern const char*status_fieldfmt[MAXBLSTATS];
extern char*status_vals[MAXBLSTATS];extern boolean status_activefields[MAXBLSTATS];
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
 typedef struct win_choices teleport_windows_actual_choice;
 _Static_assert(sizeof(struct win_choices)==sizeof(struct teleport_windows_choice),"source win_choices size changed");
 _Static_assert(offsetof(struct win_choices,procs)==offsetof(struct teleport_windows_choice,procs),"source choice procs offset changed");
 _Static_assert(offsetof(struct win_choices,ini_routine)==offsetof(struct teleport_windows_choice,ini_routine),"source choice callback offset changed");
 _Static_assert(SIZE(winchoices)==2,"source winchoices count changed");
 _Static_assert(sizeof status_vals/sizeof status_vals[0]==MAXBLSTATS,"source status table count changed");
#else
 typedef struct teleport_windows_choice teleport_windows_actual_choice;
 #ifndef TELEPORT_REFERENCE_TU
 volatile struct window_procs windowprocs;
 const char*status_fieldnm[MAXBLSTATS];const char*status_fieldfmt[MAXBLSTATS];
 char*status_vals[MAXBLSTATS];boolean status_activefields[MAXBLSTATS];
 win_request_info zerowri;
 #endif
 static struct teleport_windows_choice teleport_windows_choices[2];
 static struct window_procs teleport_windows_hup,teleport_windows_backup;
 static void*teleport_windows_private[2];
#endif
static char teleport_windows_encbuf[20];
extern struct window_procs tty_procs;
extern void win_tty_init(int);
void*teleport_windows_storage(int which){switch(which){
case 0:return(void*)&windowprocs;
case 1:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
 return winchoices;
#else
 return teleport_windows_choices;
#endif
case 2:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
 return &hup_procs;
#else
 return &teleport_windows_hup;
#endif
case 3:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
 return &dumplog_windowprocs_backup;
#else
 return &teleport_windows_backup;
#endif
case 4:return &zerowri;case 5:return teleport_windows_encbuf;case 6:return status_fieldnm;case 7:return status_fieldfmt;case 8:return status_vals;case 9:return status_activefields;
case 10:return &tty_procs;case 11:return(void*)&nul_glyphinfo;case 12:return(void*)&cg.zeroany;case 13:return(void*)def_monsyms;case 14:return(void*)def_oc_syms;case 15:return(void*)hexdd;case 16:return stdout;case 17:return(void*)win_tty_init;case 18:return gs.showsyms;
}return 0;}
long teleport_windows_private_get(int i){
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
 return(long)(intptr_t)(i?(void*)dumplog_file:(void*)previnterface_exit_nhwindows);
#else
 return(long)(intptr_t)teleport_windows_private[i];
#endif
}
void teleport_windows_private_set(int i,long v){
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
 if(i)dumplog_file=(FILE*)(intptr_t)v;else previnterface_exit_nhwindows=(void(*)(const char*))(intptr_t)v;
#else
 teleport_windows_private[i]=(void*)(intptr_t)v;
#endif
}
long teleport_windows_get(int kind,int field,void*p,int index){switch(kind){
case 0:{struct window_procs*v=p;switch(field){
case 0:return(long)(intptr_t)v->name;
case 1:return(long)v->wp_id;
case 2:return(long)v->wincap;
case 3:return(long)v->wincap2;
case 4:return(long)v->has_color[index];
case 5:return(long)(intptr_t)v->win_init_nhwindows;
case 6:return(long)(intptr_t)v->win_player_selection;
case 7:return(long)(intptr_t)v->win_askname;
case 8:return(long)(intptr_t)v->win_get_nh_event;
case 9:return(long)(intptr_t)v->win_exit_nhwindows;
case 10:return(long)(intptr_t)v->win_suspend_nhwindows;
case 11:return(long)(intptr_t)v->win_resume_nhwindows;
case 12:return(long)(intptr_t)v->win_create_nhwindow;
case 13:return(long)(intptr_t)v->win_clear_nhwindow;
case 14:return(long)(intptr_t)v->win_display_nhwindow;
case 15:return(long)(intptr_t)v->win_destroy_nhwindow;
case 16:return(long)(intptr_t)v->win_curs;
case 17:return(long)(intptr_t)v->win_putstr;
case 18:return(long)(intptr_t)v->win_putmixed;
case 19:return(long)(intptr_t)v->win_display_file;
case 20:return(long)(intptr_t)v->win_start_menu;
case 21:return(long)(intptr_t)v->win_add_menu;
case 22:return(long)(intptr_t)v->win_end_menu;
case 23:return(long)(intptr_t)v->win_select_menu;
case 24:return(long)(intptr_t)v->win_message_menu;
case 25:return(long)(intptr_t)v->win_mark_synch;
case 26:return(long)(intptr_t)v->win_wait_synch;
case 27:return(long)(intptr_t)v->win_cliparound;
case 28:return(long)(intptr_t)v->win_print_glyph;
case 29:return(long)(intptr_t)v->win_raw_print;
case 30:return(long)(intptr_t)v->win_raw_print_bold;
case 31:return(long)(intptr_t)v->win_nhgetch;
case 32:return(long)(intptr_t)v->win_nh_poskey;
case 33:return(long)(intptr_t)v->win_nhbell;
case 34:return(long)(intptr_t)v->win_doprev_message;
case 35:return(long)(intptr_t)v->win_yn_function;
case 36:return(long)(intptr_t)v->win_getlin;
case 37:return(long)(intptr_t)v->win_get_ext_cmd;
case 38:return(long)(intptr_t)v->win_number_pad;
case 39:return(long)(intptr_t)v->win_delay_output;
case 40:return(long)(intptr_t)v->win_outrip;
case 41:return(long)(intptr_t)v->win_preference_update;
case 42:return(long)(intptr_t)v->win_getmsghistory;
case 43:return(long)(intptr_t)v->win_putmsghistory;
case 44:return(long)(intptr_t)v->win_status_init;
case 45:return(long)(intptr_t)v->win_status_finish;
case 46:return(long)(intptr_t)v->win_status_enablefield;
case 47:return(long)(intptr_t)v->win_status_update;
case 48:return(long)(intptr_t)v->win_can_suspend;
case 49:return(long)(intptr_t)v->win_update_inventory;
case 50:return(long)(intptr_t)v->win_ctrl_nhwindow;
}}break;
case 1:{teleport_windows_actual_choice*v=p;switch(field){
case 0:return(long)(intptr_t)v->procs;
case 1:return(long)(intptr_t)v->ini_routine;
}}break;
case 2:{glyph_info*v=p;switch(field){
case 0:return(long)v->glyph;
case 1:return(long)v->ttychar;
case 2:return(long)v->framecolor;
case 3:return(long)v->gm.glyphflags;
case 4:return(long)v->gm.sym.color;
case 5:return(long)v->gm.sym.symidx;
case 6:return(long)v->gm.customcolor;
case 7:return(long)v->gm.color256idx;
case 8:return(long)v->gm.tileidx;
case 9:return(long)(intptr_t)v->gm.u;
}}break;
case 3:{anything*v=p;switch(field){
case 0:return(long)v->a_int;
}}break;
case 4:{menu_item*v=p;switch(field){
case 0:return(long)v->item.a_int;
case 1:return(long)v->count;
case 2:return(long)v->itemflags;
}}break;
case 5:{win_request_info*v=p;switch(field){
case 0:return(long)v->tocore.tocore_flags;
case 1:return(long)v->tocore.active;
case 2:return(long)v->tocore.use_update_inventory;
case 3:return(long)v->tocore.maxslot;
case 4:return(long)v->tocore.needrows;
case 5:return(long)v->tocore.needcols;
case 6:return(long)v->tocore.haverows;
case 7:return(long)v->tocore.havecols;
case 8:return(long)v->fromcore.core_request;
case 9:return(long)v->fromcore.invmode;
case 10:return(long)v->fromcore.menu_promptstyle.color;
case 11:return(long)v->fromcore.menu_promptstyle.attr;
}}break;
case 6:{color_attr*v=p;switch(field){
case 0:return(long)v->color;
case 1:return(long)v->attr;
}}break;
case 7:{struct _cmd_queue*v=p;switch(field){
case 0:return(long)v->typ;
case 1:return(long)v->key;
}}break;
case 8:{struct menucoloring*v=p;switch(field){
case 0:return(long)(intptr_t)v->match;
case 1:return(long)v->color;
case 2:return(long)v->attr;
case 3:return(long)(intptr_t)v->next;
}}break;
case 9:{const struct class_sym*v=p;switch(field){
case 0:return(long)v->sym;
case 1:return(long)(intptr_t)v->name;
case 2:return(long)(intptr_t)v->explain;
}}break;
}return 0;}
void teleport_windows_set(int kind,int field,void*p,int index,long value){switch(kind){
case 0:{struct window_procs*v=p;switch(field){
case 0:v->name=(__typeof__(v->name))(intptr_t)value;return;
case 1:v->wp_id=(__typeof__(v->wp_id))value;return;
case 2:v->wincap=(__typeof__(v->wincap))value;return;
case 3:v->wincap2=(__typeof__(v->wincap2))value;return;
case 4:v->has_color[index]=(__typeof__(v->has_color[index]))value;return;
case 5:v->win_init_nhwindows=(__typeof__(v->win_init_nhwindows))(intptr_t)value;return;
case 6:v->win_player_selection=(__typeof__(v->win_player_selection))(intptr_t)value;return;
case 7:v->win_askname=(__typeof__(v->win_askname))(intptr_t)value;return;
case 8:v->win_get_nh_event=(__typeof__(v->win_get_nh_event))(intptr_t)value;return;
case 9:v->win_exit_nhwindows=(__typeof__(v->win_exit_nhwindows))(intptr_t)value;return;
case 10:v->win_suspend_nhwindows=(__typeof__(v->win_suspend_nhwindows))(intptr_t)value;return;
case 11:v->win_resume_nhwindows=(__typeof__(v->win_resume_nhwindows))(intptr_t)value;return;
case 12:v->win_create_nhwindow=(__typeof__(v->win_create_nhwindow))(intptr_t)value;return;
case 13:v->win_clear_nhwindow=(__typeof__(v->win_clear_nhwindow))(intptr_t)value;return;
case 14:v->win_display_nhwindow=(__typeof__(v->win_display_nhwindow))(intptr_t)value;return;
case 15:v->win_destroy_nhwindow=(__typeof__(v->win_destroy_nhwindow))(intptr_t)value;return;
case 16:v->win_curs=(__typeof__(v->win_curs))(intptr_t)value;return;
case 17:v->win_putstr=(__typeof__(v->win_putstr))(intptr_t)value;return;
case 18:v->win_putmixed=(__typeof__(v->win_putmixed))(intptr_t)value;return;
case 19:v->win_display_file=(__typeof__(v->win_display_file))(intptr_t)value;return;
case 20:v->win_start_menu=(__typeof__(v->win_start_menu))(intptr_t)value;return;
case 21:v->win_add_menu=(__typeof__(v->win_add_menu))(intptr_t)value;return;
case 22:v->win_end_menu=(__typeof__(v->win_end_menu))(intptr_t)value;return;
case 23:v->win_select_menu=(__typeof__(v->win_select_menu))(intptr_t)value;return;
case 24:v->win_message_menu=(__typeof__(v->win_message_menu))(intptr_t)value;return;
case 25:v->win_mark_synch=(__typeof__(v->win_mark_synch))(intptr_t)value;return;
case 26:v->win_wait_synch=(__typeof__(v->win_wait_synch))(intptr_t)value;return;
case 27:v->win_cliparound=(__typeof__(v->win_cliparound))(intptr_t)value;return;
case 28:v->win_print_glyph=(__typeof__(v->win_print_glyph))(intptr_t)value;return;
case 29:v->win_raw_print=(__typeof__(v->win_raw_print))(intptr_t)value;return;
case 30:v->win_raw_print_bold=(__typeof__(v->win_raw_print_bold))(intptr_t)value;return;
case 31:v->win_nhgetch=(__typeof__(v->win_nhgetch))(intptr_t)value;return;
case 32:v->win_nh_poskey=(__typeof__(v->win_nh_poskey))(intptr_t)value;return;
case 33:v->win_nhbell=(__typeof__(v->win_nhbell))(intptr_t)value;return;
case 34:v->win_doprev_message=(__typeof__(v->win_doprev_message))(intptr_t)value;return;
case 35:v->win_yn_function=(__typeof__(v->win_yn_function))(intptr_t)value;return;
case 36:v->win_getlin=(__typeof__(v->win_getlin))(intptr_t)value;return;
case 37:v->win_get_ext_cmd=(__typeof__(v->win_get_ext_cmd))(intptr_t)value;return;
case 38:v->win_number_pad=(__typeof__(v->win_number_pad))(intptr_t)value;return;
case 39:v->win_delay_output=(__typeof__(v->win_delay_output))(intptr_t)value;return;
case 40:v->win_outrip=(__typeof__(v->win_outrip))(intptr_t)value;return;
case 41:v->win_preference_update=(__typeof__(v->win_preference_update))(intptr_t)value;return;
case 42:v->win_getmsghistory=(__typeof__(v->win_getmsghistory))(intptr_t)value;return;
case 43:v->win_putmsghistory=(__typeof__(v->win_putmsghistory))(intptr_t)value;return;
case 44:v->win_status_init=(__typeof__(v->win_status_init))(intptr_t)value;return;
case 45:v->win_status_finish=(__typeof__(v->win_status_finish))(intptr_t)value;return;
case 46:v->win_status_enablefield=(__typeof__(v->win_status_enablefield))(intptr_t)value;return;
case 47:v->win_status_update=(__typeof__(v->win_status_update))(intptr_t)value;return;
case 48:v->win_can_suspend=(__typeof__(v->win_can_suspend))(intptr_t)value;return;
case 49:v->win_update_inventory=(__typeof__(v->win_update_inventory))(intptr_t)value;return;
case 50:v->win_ctrl_nhwindow=(__typeof__(v->win_ctrl_nhwindow))(intptr_t)value;return;
}}break;
case 1:{teleport_windows_actual_choice*v=p;switch(field){
case 0:v->procs=(__typeof__(v->procs))(intptr_t)value;return;
case 1:v->ini_routine=(__typeof__(v->ini_routine))(intptr_t)value;return;
}}break;
case 2:{glyph_info*v=p;switch(field){
case 0:v->glyph=(__typeof__(v->glyph))value;return;
case 1:v->ttychar=(__typeof__(v->ttychar))value;return;
case 2:v->framecolor=(__typeof__(v->framecolor))value;return;
case 3:v->gm.glyphflags=(__typeof__(v->gm.glyphflags))value;return;
case 4:v->gm.sym.color=(__typeof__(v->gm.sym.color))value;return;
case 5:v->gm.sym.symidx=(__typeof__(v->gm.sym.symidx))value;return;
case 6:v->gm.customcolor=(__typeof__(v->gm.customcolor))value;return;
case 7:v->gm.color256idx=(__typeof__(v->gm.color256idx))value;return;
case 8:v->gm.tileidx=(__typeof__(v->gm.tileidx))value;return;
case 9:v->gm.u=(__typeof__(v->gm.u))(intptr_t)value;return;
}}break;
case 3:{anything*v=p;switch(field){
case 0:v->a_int=(__typeof__(v->a_int))value;return;
}}break;
case 4:{menu_item*v=p;switch(field){
case 0:v->item.a_int=(__typeof__(v->item.a_int))value;return;
case 1:v->count=(__typeof__(v->count))value;return;
case 2:v->itemflags=(__typeof__(v->itemflags))value;return;
}}break;
case 5:{win_request_info*v=p;switch(field){
case 0:v->tocore.tocore_flags=(__typeof__(v->tocore.tocore_flags))value;return;
case 1:v->tocore.active=(__typeof__(v->tocore.active))value;return;
case 2:v->tocore.use_update_inventory=(__typeof__(v->tocore.use_update_inventory))value;return;
case 3:v->tocore.maxslot=(__typeof__(v->tocore.maxslot))value;return;
case 4:v->tocore.needrows=(__typeof__(v->tocore.needrows))value;return;
case 5:v->tocore.needcols=(__typeof__(v->tocore.needcols))value;return;
case 6:v->tocore.haverows=(__typeof__(v->tocore.haverows))value;return;
case 7:v->tocore.havecols=(__typeof__(v->tocore.havecols))value;return;
case 8:v->fromcore.core_request=(__typeof__(v->fromcore.core_request))value;return;
case 9:v->fromcore.invmode=(__typeof__(v->fromcore.invmode))value;return;
case 10:v->fromcore.menu_promptstyle.color=(__typeof__(v->fromcore.menu_promptstyle.color))value;return;
case 11:v->fromcore.menu_promptstyle.attr=(__typeof__(v->fromcore.menu_promptstyle.attr))value;return;
}}break;
case 6:{color_attr*v=p;switch(field){
case 0:v->color=(__typeof__(v->color))value;return;
case 1:v->attr=(__typeof__(v->attr))value;return;
}}break;
case 7:{struct _cmd_queue*v=p;switch(field){
case 0:v->typ=(__typeof__(v->typ))value;return;
case 1:v->key=(__typeof__(v->key))value;return;
}}break;
case 8:{struct menucoloring*v=p;switch(field){
case 0:v->match=(__typeof__(v->match))(intptr_t)value;return;
case 1:v->color=(__typeof__(v->color))value;return;
case 2:v->attr=(__typeof__(v->attr))value;return;
case 3:v->next=(__typeof__(v->next))(intptr_t)value;return;
}}break;
}}
long teleport_windows_global(int i){switch(i){
case 0:return(long)iflags.raw_printed;
case 1:return(long)iflags.altmeta;
case 2:return(long)iflags.window_inited;
case 3:return(long)iflags.in_dumplog;
case 4:return(long)iflags.use_color;
case 5:return(long)iflags.use_menu_color;
case 6:return(long)iflags.menu_headings.attr;
case 7:return(long)iflags.menu_headings.color;
case 8:return(long)program_state.gameover;
case 9:return(long)program_state.in_getlin;
case 10:return(long)gb.bot_disabled;
case 11:return(long)go.opt_need_promptstyle;
case 12:return(long)flags.pickup;
case 13:return(long)(intptr_t)gl.last_winchoice;
case 14:return(long)(intptr_t)gm.menu_colorings;
case 15:return(long)svc.context.rndencode;
case 16:return(long)WIN_STATUS;
case 17:return(long)iflags.menuinvertmode;
}return 0;}
void teleport_windows_set_global(int i,long v){switch(i){
case 0:iflags.raw_printed=(__typeof__(iflags.raw_printed))v;return;
case 1:iflags.altmeta=(__typeof__(iflags.altmeta))v;return;
case 2:iflags.window_inited=(__typeof__(iflags.window_inited))v;return;
case 3:iflags.in_dumplog=(__typeof__(iflags.in_dumplog))v;return;
case 4:iflags.use_color=(__typeof__(iflags.use_color))v;return;
case 5:iflags.use_menu_color=(__typeof__(iflags.use_menu_color))v;return;
case 6:iflags.menu_headings.attr=(__typeof__(iflags.menu_headings.attr))v;return;
case 7:iflags.menu_headings.color=(__typeof__(iflags.menu_headings.color))v;return;
case 8:program_state.gameover=(__typeof__(program_state.gameover))v;return;
case 9:program_state.in_getlin=(__typeof__(program_state.in_getlin))v;return;
case 10:gb.bot_disabled=(__typeof__(gb.bot_disabled))v;return;
case 11:go.opt_need_promptstyle=(__typeof__(go.opt_need_promptstyle))v;return;
case 12:flags.pickup=(__typeof__(flags.pickup))v;return;
case 13:gl.last_winchoice=(__typeof__(gl.last_winchoice))(intptr_t)v;return;
case 14:gm.menu_colorings=(__typeof__(gm.menu_colorings))(intptr_t)v;return;
case 15:svc.context.rndencode=(__typeof__(svc.context.rndencode))v;return;
case 16:WIN_STATUS=(__typeof__(WIN_STATUS))v;return;
case 17:iflags.menuinvertmode=(__typeof__(iflags.menuinvertmode))v;return;
}}
void teleport_windows_call_win_init_nhwindows(int * a0, char ** a1){(*windowprocs.win_init_nhwindows)(a0,a1);}
void teleport_windows_call_win_player_selection(){(*windowprocs.win_player_selection)();}
void teleport_windows_call_win_askname(){(*windowprocs.win_askname)();}
void teleport_windows_call_win_get_nh_event(){(*windowprocs.win_get_nh_event)();}
void teleport_windows_call_win_exit_nhwindows(const char * a0){(*windowprocs.win_exit_nhwindows)(a0);}
void teleport_windows_call_win_suspend_nhwindows(const char * a0){(*windowprocs.win_suspend_nhwindows)(a0);}
void teleport_windows_call_win_resume_nhwindows(){(*windowprocs.win_resume_nhwindows)();}
winid teleport_windows_call_win_create_nhwindow(int a0){return (*windowprocs.win_create_nhwindow)(a0);}
void teleport_windows_call_win_clear_nhwindow(winid a0){(*windowprocs.win_clear_nhwindow)(a0);}
void teleport_windows_call_win_display_nhwindow(winid a0, boolean a1){(*windowprocs.win_display_nhwindow)(a0,a1);}
void teleport_windows_call_win_destroy_nhwindow(winid a0){(*windowprocs.win_destroy_nhwindow)(a0);}
void teleport_windows_call_win_curs(winid a0, int a1, int a2){(*windowprocs.win_curs)(a0,a1,a2);}
void teleport_windows_call_win_putstr(winid a0, int a1, const char * a2){(*windowprocs.win_putstr)(a0,a1,a2);}
void teleport_windows_call_win_putmixed(winid a0, int a1, const char * a2){(*windowprocs.win_putmixed)(a0,a1,a2);}
void teleport_windows_call_win_display_file(const char * a0, boolean a1){(*windowprocs.win_display_file)(a0,a1);}
void teleport_windows_call_win_start_menu(winid a0, unsigned long a1){(*windowprocs.win_start_menu)(a0,a1);}
void teleport_windows_call_win_add_menu(winid a0, const glyph_info * a1, const union any * a2, char a3, char a4, int a5, int a6, const char * a7, unsigned int a8){(*windowprocs.win_add_menu)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
void teleport_windows_call_win_end_menu(winid a0, const char * a1){(*windowprocs.win_end_menu)(a0,a1);}
int teleport_windows_call_win_select_menu(winid a0, int a1, struct mi ** a2){return (*windowprocs.win_select_menu)(a0,a1,a2);}
char teleport_windows_call_win_message_menu(char a0, int a1, const char * a2){return (*windowprocs.win_message_menu)(a0,a1,a2);}
void teleport_windows_call_win_mark_synch(){(*windowprocs.win_mark_synch)();}
void teleport_windows_call_win_wait_synch(){(*windowprocs.win_wait_synch)();}
void teleport_windows_call_win_cliparound(int a0, int a1){(*windowprocs.win_cliparound)(a0,a1);}
void teleport_windows_call_win_print_glyph(winid a0, coordxy a1, coordxy a2, const glyph_info * a3, const glyph_info * a4){(*windowprocs.win_print_glyph)(a0,a1,a2,a3,a4);}
void teleport_windows_call_win_raw_print(const char * a0){(*windowprocs.win_raw_print)(a0);}
void teleport_windows_call_win_raw_print_bold(const char * a0){(*windowprocs.win_raw_print_bold)(a0);}
int teleport_windows_call_win_nhgetch(){return (*windowprocs.win_nhgetch)();}
int teleport_windows_call_win_nh_poskey(coordxy * a0, coordxy * a1, int * a2){return (*windowprocs.win_nh_poskey)(a0,a1,a2);}
void teleport_windows_call_win_nhbell(){(*windowprocs.win_nhbell)();}
int teleport_windows_call_win_doprev_message(){return (*windowprocs.win_doprev_message)();}
char teleport_windows_call_win_yn_function(const char * a0, const char * a1, char a2){return (*windowprocs.win_yn_function)(a0,a1,a2);}
void teleport_windows_call_win_getlin(const char * a0, char * a1){(*windowprocs.win_getlin)(a0,a1);}
int teleport_windows_call_win_get_ext_cmd(){return (*windowprocs.win_get_ext_cmd)();}
void teleport_windows_call_win_number_pad(int a0){(*windowprocs.win_number_pad)(a0);}
void teleport_windows_call_win_delay_output(){(*windowprocs.win_delay_output)();}
void teleport_windows_call_win_outrip(winid a0, int a1, time_t a2){(*windowprocs.win_outrip)(a0,a1,a2);}
void teleport_windows_call_win_preference_update(const char * a0){(*windowprocs.win_preference_update)(a0);}
char * teleport_windows_call_win_getmsghistory(boolean a0){return (*windowprocs.win_getmsghistory)(a0);}
void teleport_windows_call_win_putmsghistory(const char * a0, boolean a1){(*windowprocs.win_putmsghistory)(a0,a1);}
void teleport_windows_call_win_status_init(){(*windowprocs.win_status_init)();}
void teleport_windows_call_win_status_finish(){(*windowprocs.win_status_finish)();}
void teleport_windows_call_win_status_enablefield(int a0, const char * a1, const char * a2, boolean a3){(*windowprocs.win_status_enablefield)(a0,a1,a2,a3);}
void teleport_windows_call_win_status_update(int a0, genericptr_t a1, int a2, int a3, int a4, unsigned long * a5){(*windowprocs.win_status_update)(a0,a1,a2,a3,a4,a5);}
boolean teleport_windows_call_win_can_suspend(){return (*windowprocs.win_can_suspend)();}
void teleport_windows_call_win_update_inventory(int a0){(*windowprocs.win_update_inventory)(a0);}
win_request_info * teleport_windows_call_win_ctrl_nhwindow(winid a0, int a1, win_request_info * a2){return (*windowprocs.win_ctrl_nhwindow)(a0,a1,a2);}
void teleport_windows_call_init(void*p,int n){((void(*)(int))p)(n);}
void teleport_windows_call_exit(void*p,const char*s){((void(*)(const char*))p)(s);}
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_def_raw_print(const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_def_wait_synch(void);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern struct win_choices * teleport_windows_callback_win_choices_find(const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_exit_nhwindows(const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern int teleport_windows_callback_hup_nhgetch(void);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern char teleport_windows_callback_hup_yn_function(const char *,const char *,char);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern int teleport_windows_callback_hup_nh_poskey(coordxy *,coordxy *,int *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_getlin(const char *,char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_init_nhwindows(int *,char **);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern winid teleport_windows_callback_hup_create_nhwindow(int);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern int teleport_windows_callback_hup_select_menu(winid,int,struct mi **);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_add_menu(winid,const glyph_info *,const anything *,char,char,int,int,const char *,unsigned int);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_end_menu(winid,const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_putstr(winid,int,const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_print_glyph(winid,coordxy,coordxy,const glyph_info *,const glyph_info *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_outrip(winid,int,time_t);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_curs(winid,int,int);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_display_nhwindow(winid,boolean);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_display_file(const char *,boolean);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_cliparound(int,int);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_status_update(int,genericptr_t,int,int,int,unsigned long *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern int teleport_windows_callback_hup_int_ndecl(void);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_void_ndecl(void);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_void_fdecl_int(int);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_void_fdecl_winid(winid);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_void_fdecl_winid_ulong(winid,unsigned long);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_hup_void_fdecl_constchar_p(const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern win_request_info * teleport_windows_callback_hup_ctrl_nhwindow(winid,int,win_request_info *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_dump_putstr(winid,int,const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern winid teleport_windows_callback_dump_create_nhwindow(int);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_dump_clear_nhwindow(winid);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_dump_display_nhwindow(winid,boolean);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_dump_destroy_nhwindow(winid);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_dump_start_menu(winid,unsigned long);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_dump_add_menu(winid,const glyph_info *,const anything *,char,char,int,int,const char *,unsigned int);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern void teleport_windows_callback_dump_end_menu(winid,const char *);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern int teleport_windows_callback_dump_select_menu(winid,int,menu_item **);
#endif
#ifndef TELEPORT_WINDOWS_VALIDATE_SOURCE
extern boolean teleport_windows_callback_get_menu_coloring(const char *,int *,int *);
#endif
void*teleport_windows_function_address(int n){switch(n){
case 0:
return(void*)genl_can_suspend_no;
case 1:
return(void*)genl_can_suspend_yes;
case 2:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)def_raw_print;
#else
return(void*)teleport_windows_callback_def_raw_print;
#endif
case 3:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)def_wait_synch;
#else
return(void*)teleport_windows_callback_def_wait_synch;
#endif
case 4:
return(void*)check_tty_wincap;
case 5:
return(void*)check_tty_wincap2;
case 6:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)win_choices_find;
#else
return(void*)teleport_windows_callback_win_choices_find;
#endif
case 7:
return(void*)choose_windows;
case 8:
return(void*)genl_message_menu;
case 9:
return(void*)genl_preference_update;
case 10:
return(void*)genl_getmsghistory;
case 11:
return(void*)genl_putmsghistory;
case 12:
return(void*)nhwindows_hangup;
case 13:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_exit_nhwindows;
#else
return(void*)teleport_windows_callback_hup_exit_nhwindows;
#endif
case 14:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_nhgetch;
#else
return(void*)teleport_windows_callback_hup_nhgetch;
#endif
case 15:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_yn_function;
#else
return(void*)teleport_windows_callback_hup_yn_function;
#endif
case 16:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_nh_poskey;
#else
return(void*)teleport_windows_callback_hup_nh_poskey;
#endif
case 17:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_getlin;
#else
return(void*)teleport_windows_callback_hup_getlin;
#endif
case 18:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_init_nhwindows;
#else
return(void*)teleport_windows_callback_hup_init_nhwindows;
#endif
case 19:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_create_nhwindow;
#else
return(void*)teleport_windows_callback_hup_create_nhwindow;
#endif
case 20:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_select_menu;
#else
return(void*)teleport_windows_callback_hup_select_menu;
#endif
case 21:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_add_menu;
#else
return(void*)teleport_windows_callback_hup_add_menu;
#endif
case 22:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_end_menu;
#else
return(void*)teleport_windows_callback_hup_end_menu;
#endif
case 23:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_putstr;
#else
return(void*)teleport_windows_callback_hup_putstr;
#endif
case 24:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_print_glyph;
#else
return(void*)teleport_windows_callback_hup_print_glyph;
#endif
case 25:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_outrip;
#else
return(void*)teleport_windows_callback_hup_outrip;
#endif
case 26:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_curs;
#else
return(void*)teleport_windows_callback_hup_curs;
#endif
case 27:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_display_nhwindow;
#else
return(void*)teleport_windows_callback_hup_display_nhwindow;
#endif
case 28:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_display_file;
#else
return(void*)teleport_windows_callback_hup_display_file;
#endif
case 29:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_cliparound;
#else
return(void*)teleport_windows_callback_hup_cliparound;
#endif
case 30:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_status_update;
#else
return(void*)teleport_windows_callback_hup_status_update;
#endif
case 31:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_int_ndecl;
#else
return(void*)teleport_windows_callback_hup_int_ndecl;
#endif
case 32:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_void_ndecl;
#else
return(void*)teleport_windows_callback_hup_void_ndecl;
#endif
case 33:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_void_fdecl_int;
#else
return(void*)teleport_windows_callback_hup_void_fdecl_int;
#endif
case 34:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_void_fdecl_winid;
#else
return(void*)teleport_windows_callback_hup_void_fdecl_winid;
#endif
case 35:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_void_fdecl_winid_ulong;
#else
return(void*)teleport_windows_callback_hup_void_fdecl_winid_ulong;
#endif
case 36:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_void_fdecl_constchar_p;
#else
return(void*)teleport_windows_callback_hup_void_fdecl_constchar_p;
#endif
case 37:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)hup_ctrl_nhwindow;
#else
return(void*)teleport_windows_callback_hup_ctrl_nhwindow;
#endif
case 38:
return(void*)genl_status_init;
case 39:
return(void*)genl_status_finish;
case 40:
return(void*)genl_status_enablefield;
case 41:
return(void*)genl_status_update;
case 42:
return(void*)dump_open_log;
case 43:
return(void*)dump_close_log;
case 44:
return(void*)dump_forward_putstr;
case 45:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_putstr;
#else
return(void*)teleport_windows_callback_dump_putstr;
#endif
case 46:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_create_nhwindow;
#else
return(void*)teleport_windows_callback_dump_create_nhwindow;
#endif
case 47:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_clear_nhwindow;
#else
return(void*)teleport_windows_callback_dump_clear_nhwindow;
#endif
case 48:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_display_nhwindow;
#else
return(void*)teleport_windows_callback_dump_display_nhwindow;
#endif
case 49:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_destroy_nhwindow;
#else
return(void*)teleport_windows_callback_dump_destroy_nhwindow;
#endif
case 50:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_start_menu;
#else
return(void*)teleport_windows_callback_dump_start_menu;
#endif
case 51:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_add_menu;
#else
return(void*)teleport_windows_callback_dump_add_menu;
#endif
case 52:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_end_menu;
#else
return(void*)teleport_windows_callback_dump_end_menu;
#endif
case 53:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)dump_select_menu;
#else
return(void*)teleport_windows_callback_dump_select_menu;
#endif
case 54:
return(void*)dump_redirect;
case 55:
return(void*)has_color;
case 56:
return(void*)glyph2ttychar;
case 57:
return(void*)glyph2symidx;
case 58:
return(void*)encglyph;
case 59:
return(void*)decode_glyph;
case 60:
return(void*)decode_mixed;
case 61:
return(void*)genl_putmixed;
case 62:
return(void*)genl_display_file;
case 63:
return(void*)menuitem_invert_test;
case 64:
return(void*)mixed_to_glyphinfo;
case 65:
return(void*)choose_classes_menu;
case 66:
return(void*)adjust_menu_promptstyle;
case 67:
return(void*)add_menu;
case 68:
return(void*)add_menu_heading;
case 69:
return(void*)add_menu_str;
case 70:
#ifdef TELEPORT_WINDOWS_VALIDATE_SOURCE
return(void*)get_menu_coloring;
#else
return(void*)teleport_windows_callback_get_menu_coloring;
#endif
case 71:
return(void*)select_menu;
case 72:
return(void*)getlin;
}return 0;}
long * teleport_windows_dep_alloc(unsigned int a0){return alloc(a0);}
struct _cmd_queue * teleport_windows_dep_cmdq_pop(void){return cmdq_pop();}
int teleport_windows_dep_def_char_to_monclass(char a0){return def_char_to_monclass(a0);}
int teleport_windows_dep_def_char_to_objclass(char a0){return def_char_to_objclass(a0);}
int teleport_windows_dep_dlb_fclose(FILE * a0){return dlb_fclose(a0);}
char * teleport_windows_dep_dlb_fgets(char *restrict a0,int a1,FILE *restrict a2){return dlb_fgets(a0,a1,a2);}
FILE * teleport_windows_dep_dlb_fopen(const char *restrict a0,const char *restrict a1){return dlb_fopen(a0,a1);}
char * teleport_windows_dep_eos(char * a0){return eos(a0);}
int teleport_windows_dep_fclose(FILE * a0){return fclose(a0);}
int teleport_windows_dep_fputs(const char *restrict a0,FILE *restrict a1){return fputs(a0,a1);}
void teleport_windows_dep_free(void * a0){free(a0);}
void teleport_windows_dep_map_glyphinfo(coordxy a0,coordxy a1,int a2,unsigned int a3,glyph_info * a4){map_glyphinfo(a0,a1,a2,a3,a4);}
char * teleport_windows_dep_mungspaces(char * a0){return mungspaces(a0);}
void teleport_windows_dep_nh_terminate(int a0){nh_terminate(a0);}
int teleport_windows_dep_puts(const char * a0){return puts(a0);}
boolean teleport_windows_dep_regex_match(const char * a0,struct nhregex * a1){return regex_match(a0,a1);}
char * teleport_windows_dep_strchr(const char * a0,int a1){return strchr(a0,a1);}
int teleport_windows_dep_strcmp(const char * a0,const char * a1){return strcmp(a0,a1);}
char * teleport_windows_dep_strcpy(char *restrict a0,const char *restrict a1){return strcpy(a0,a1);}
unsigned long teleport_windows_dep_strlen(const char * a0){return strlen(a0);}
char * teleport_windows_dep_strncpy(char *restrict a0,const char *restrict a1,size_t a2){return strncpy(a0,a1,a2);}
char * teleport_windows_dep_strstr(const char * a0,const char * a1){return strstr(a0,a1);}
int teleport_windows_strcmpi(const char*a,const char*b){return strcmpi(a,b);}
int teleport_windows_format_strings(char*out,const char*f,const char*a,const char*b){return sprintf(out,f,a,b);}
int teleport_windows_format_char(char*out,const char*f,int ch,const char*s){return sprintf(out,f,ch,s);}
int teleport_windows_format_encode(char*out,const char*f,unsigned a,unsigned b){return sprintf(out,f,a,b);}
int teleport_windows_fprintf_string(FILE*fp,const char*f,const char*s){return fprintf(fp,f,s);}
int teleport_windows_fprintf_char(FILE*fp,const char*f,int c,const char*s){return fprintf(fp,f,c,s);}
void teleport_windows_pline(const char*f,const char*a,const char*b){pline(f,a,b);}
void teleport_windows_config_error(const char*f,const char*a,const char*b){config_error_add(f,a,b);}
void teleport_windows_raw_printf(const char*f){raw_printf(f);}
void teleport_windows_panic(const char*f,int n){panic(f,n);}
#ifndef WINDOWS_SOURCE_FILE
#error WINDOWS_SOURCE_FILE must name the actual compiled reference windows.c
#endif
void teleport_windows_debug0(const char*s){do{if(debugcore(WINDOWS_SOURCE_FILE,TRUE)){int save_plnmsg=iflags.last_msg;pline(s);iflags.last_msg=save_plnmsg;}}while(0);}
void*teleport_windows_copy(void*out,const void*in,size_t n){return memcpy(out,in,n);}
void teleport_windows_copy_procs(volatile struct window_procs*out,const volatile struct window_procs*in){*out=*in;}
static char teleport_windows_literals[662];
void*teleport_windows_literal_storage(void){return teleport_windows_literals;}
size_t teleport_windows_literal_capacity(void){return sizeof teleport_windows_literals;}
