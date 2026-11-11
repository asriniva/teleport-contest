/* WINTTY typed native ABI only. Window/terminal/menu/status policy is JS. */
#include "hack.h"
#include "wintty.h"
#include "tcap.h"
extern const char *status_fieldfmt[MAXBLSTATS];
extern char *status_vals[MAXBLSTATS];
extern boolean status_activefields[MAXBLSTATS];
extern void cmov(int,int),nocmov(int,int);
#include <stdint.h>
#include <stdlib.h>
extern void *teleport_wintty_data_storage(int);
static char wintty_askname_text[14],wintty_compressed[BUFSZ];
void *teleport_wintty_storage(int i){return teleport_wintty_data_storage(i);}
void *teleport_wintty_static_storage(int i){return i==0?wintty_askname_text:i==1?wintty_compressed:0;}
static char wintty_literals[TELEPORT_WINTTY_LITERAL_CAPACITY];
void *teleport_wintty_literal_storage(void){return wintty_literals;}
size_t teleport_wintty_literal_capacity(void){return sizeof wintty_literals;}
extern void teleport_wintty_callback_winch_handler(int);
static void teleport_wintty_winch_trampoline(int sig){teleport_wintty_callback_winch_handler(sig);}
uintptr_t teleport_wintty_signal(int sig,uintptr_t fn){return(uintptr_t)signal(sig,(void(*)(int))fn);}
uintptr_t teleport_wintty_callback_pointer(int i){switch(i){case 0:return(uintptr_t)teleport_wintty_winch_trampoline;case 1:return(uintptr_t)tty_init_nhwindows;case 2:return(uintptr_t)tty_player_selection;case 3:return(uintptr_t)tty_askname;case 4:return(uintptr_t)tty_get_nh_event;case 5:return(uintptr_t)tty_exit_nhwindows;case 6:return(uintptr_t)tty_suspend_nhwindows;case 7:return(uintptr_t)tty_resume_nhwindows;case 8:return(uintptr_t)tty_create_nhwindow;case 9:return(uintptr_t)tty_clear_nhwindow;case 10:return(uintptr_t)tty_display_nhwindow;case 11:return(uintptr_t)tty_destroy_nhwindow;case 12:return(uintptr_t)tty_curs;case 13:return(uintptr_t)tty_putstr;case 14:return(uintptr_t)tty_putmixed;case 15:return(uintptr_t)tty_display_file;case 16:return(uintptr_t)tty_start_menu;case 17:return(uintptr_t)tty_add_menu;case 18:return(uintptr_t)tty_end_menu;case 19:return(uintptr_t)tty_select_menu;case 20:return(uintptr_t)tty_message_menu;case 21:return(uintptr_t)tty_mark_synch;case 22:return(uintptr_t)tty_wait_synch;case 23:return(uintptr_t)tty_cliparound;case 24:return(uintptr_t)tty_print_glyph;case 25:return(uintptr_t)tty_raw_print;case 26:return(uintptr_t)tty_raw_print_bold;case 27:return(uintptr_t)tty_nhgetch;case 28:return(uintptr_t)tty_nh_poskey;case 29:return(uintptr_t)tty_nhbell;case 30:return(uintptr_t)tty_doprev_message;case 31:return(uintptr_t)tty_yn_function;case 32:return(uintptr_t)tty_getlin;case 33:return(uintptr_t)tty_get_ext_cmd;case 34:return(uintptr_t)tty_number_pad;case 35:return(uintptr_t)tty_delay_output;case 36:return(uintptr_t)genl_outrip;case 37:return(uintptr_t)tty_preference_update;case 38:return(uintptr_t)tty_getmsghistory;case 39:return(uintptr_t)tty_putmsghistory;case 40:return(uintptr_t)tty_status_init;case 41:return(uintptr_t)genl_status_finish;case 42:return(uintptr_t)tty_status_enablefield;case 43:return(uintptr_t)tty_status_update;case 44:return(uintptr_t)genl_can_suspend_yes;case 45:return(uintptr_t)tty_update_inventory;case 46:return(uintptr_t)tty_ctrl_nhwindow;default:return 0;}}
const void *teleport_wintty_global(int i){switch(i){case 0:return &program_state;case 1:return &gt;case 2:return teleport_wintty_data_storage(17);case 3:return teleport_wintty_data_storage(3);case 4:return teleport_wintty_data_storage(2);case 5:return teleport_wintty_data_storage(1);case 6:return &iflags;case 7:return &WIN_MAP;case 8:return &gg;case 9:return &u;case 10:return &WIN_STATUS;case 11:return &WIN_MESSAGE;case 12:return teleport_wintty_data_storage(8);case 13:return teleport_wintty_data_storage(9);case 14:return teleport_wintty_data_storage(11);case 15:return &stdout;case 16:return teleport_wintty_data_storage(5);case 17:return teleport_wintty_data_storage(0);case 18:return &svp;case 19:return &morc;case 20:return &flags;case 21:return &WIN_INVEN;case 22:return teleport_wintty_data_storage(6);case 23:return teleport_wintty_data_storage(4);case 24:return &disp;case 25:return teleport_wintty_data_storage(7);case 26:return &gm;case 27:return teleport_wintty_data_storage(16);case 28:return &quitchars;case 29:return &gs;case 30:return &gc;case 31:return &tc_lcl_data;case 32:return &cg;case 33:return &nul_glyphinfo;case 34:return teleport_wintty_data_storage(18);case 35:return teleport_wintty_data_storage(13);case 36:return teleport_wintty_data_storage(14);case 37:return teleport_wintty_data_storage(10);case 38:return teleport_wintty_data_storage(12);case 39:return teleport_wintty_data_storage(15);case 40:return &stdin;case 41:return &windowprocs;case 42:return teleport_wintty_data_storage(27);case 43:return teleport_wintty_data_storage(25);case 44:return teleport_wintty_data_storage(26);case 45:return teleport_wintty_data_storage(21);case 46:return teleport_wintty_data_storage(20);case 47:return teleport_wintty_data_storage(22);case 48:return teleport_wintty_data_storage(23);case 49:return &status_activefields;case 50:return teleport_wintty_data_storage(34);case 51:return teleport_wintty_data_storage(19);case 52:return &status_fieldfmt;case 53:return &status_vals;case 54:return teleport_wintty_data_storage(33);case 55:return teleport_wintty_data_storage(32);case 56:return teleport_wintty_data_storage(31);case 57:return teleport_wintty_data_storage(30);case 58:return teleport_wintty_data_storage(29);case 59:return teleport_wintty_data_storage(35);case 60:return &conditions;case 61:return teleport_wintty_data_storage(24);case 62:return &cond_idx;case 63:return teleport_wintty_data_storage(28);default:return 0;}}
unsigned teleport_wintty_get_bit(const void*p,int i){switch(i){default:return 0;}}
void teleport_wintty_set_bit(void*p,int i,unsigned v){switch(i){}}
void teleport_wintty_dep_clearlocks(){clearlocks();}
void teleport_wintty_dep_nh_terminate(int a0){nh_terminate(a0);}
void teleport_wintty_dep_getwindowsz(){getwindowsz();}
void teleport_wintty_dep_term_clear_screen(){term_clear_screen();}
void teleport_wintty_dep_docrt_flags(int a0){docrt_flags(a0);}
void teleport_wintty_dep_bot(){bot();}
void teleport_wintty_dep_addtopl(const char * a0){addtopl(a0);}
void teleport_wintty_dep_genl_status_finish(){genl_status_finish();}
void teleport_wintty_dep_status_initialize(boolean a0){status_initialize(a0);}
void teleport_wintty_dep_setbuf(FILE *restrict a0,char *restrict a1){setbuf(a0,a1);}
void teleport_wintty_dep_gettty(){gettty();}
void teleport_wintty_dep_term_startup(int * a0,int * a1){term_startup(a0,a1);}
void teleport_wintty_dep_setftty(){setftty();}
void teleport_wintty_dep_term_curs_set(int a0){term_curs_set(a0);}
long * teleport_wintty_dep_alloc(unsigned int a0){return alloc(a0);}
const char * teleport_wintty_dep_copyright_banner_line(int a0){return copyright_banner_line(a0);}
void teleport_wintty_dep_set_wc2_option_mod_status(unsigned long a0,int a1){set_wc2_option_mod_status(a0,a1);}
int teleport_wintty_dep_strcmp(const char * a0,const char * a1){return strcmp(a0,a1);}
void teleport_wintty_dep_genl_preference_update(const char * a0){genl_preference_update(a0);}
int teleport_wintty_dep_genl_player_setup(int a0){return genl_player_setup(a0);}
int teleport_wintty_dep_restore_menu(winid a0){return restore_menu(a0);}
void teleport_wintty_dep_cl_end(){cl_end();}
int teleport_wintty_dep_putchar(int a0){return putchar(a0);}
void teleport_wintty_dep_nomux_putch(int a0){nomux_putch(a0);}
void teleport_wintty_dep_xputs(const char * a0){xputs(a0);}
void teleport_wintty_dep_standoutbeg(){standoutbeg();}
void teleport_wintty_dep_standoutend(){standoutend();}
void teleport_wintty_dep_xwaitforspace(const char * a0){xwaitforspace(a0);}
void teleport_wintty_dep_settty(const char * a0){settty(a0);}
void teleport_wintty_dep_docrt(){docrt();}
void teleport_wintty_dep_free_pickinv_cache(){free_pickinv_cache();}
void teleport_wintty_dep_free(void * a0){free(a0);}
void teleport_wintty_dep_term_shutdown(){term_shutdown();}
void teleport_wintty_fmt_panic_none(const char * a0){panic(a0);}
void teleport_wintty_fmt_panic_i(const char * a0,int a1){panic(a0,a1);}
void teleport_wintty_fmt_panic_ip(const char * a0,int a1,const char* a2){panic(a0,a1,a2);}
void teleport_wintty_dep_cl_eos(){cl_eos();}
void teleport_wintty_dep_flush_screen(int a0){flush_screen(a0);}
void teleport_wintty_dep_home(){home();}
unsigned long teleport_wintty_dep_strlen(const char * a0){return strlen(a0);}
void teleport_wintty_dep_term_start_attr(int a0){term_start_attr(a0);}
void teleport_wintty_dep_term_start_color(int a0){term_start_color(a0);}
void teleport_wintty_dep_term_end_color(){term_end_color();}
void teleport_wintty_dep_term_end_attr(int a0){term_end_attr(a0);}
boolean teleport_wintty_dep_menuitem_invert_test(int a0,unsigned int a1,boolean a2){return menuitem_invert_test(a0,a1,a2);}
char * teleport_wintty_dep_strchr(const char * a0,int a1){return strchr(a0,a1);}
char * teleport_wintty_dep_strcat(char * a0,const char * a1){return strcat(a0,a1);}
int teleport_wintty_fmt_sprintf_i(char *restrict a0,const char *restrict a1,int a2){return sprintf(a0,a1,a2);}
int teleport_wintty_fmt_sprintf_ii(char *restrict a0,const char *restrict a1,int a2,int a3){return sprintf(a0,a1,a2,a3);}
int teleport_wintty_fmt_sprintf_ll(char *restrict a0,const char *restrict a1,long a2,long a3){return sprintf(a0,a1,a2,a3);}
int teleport_wintty_fmt_sprintf_p(char *restrict a0,const char *restrict a1,const char* a2){return sprintf(a0,a1,a2);}
char * teleport_wintty_dep_strcpy(char * a0,const char * a1){return strcpy(a0,a1);}
char teleport_wintty_dep_map_menu_cmd(char a0){return map_menu_cmd(a0);}
void teleport_wintty_dep_tty_nhbell(){tty_nhbell();}
void teleport_wintty_dep_tty_getlin(const char * a0,char * a1){tty_getlin(a0,a1);}
boolean teleport_wintty_dep_pmatchi(const char * a0,const char * a1){return pmatchi(a0,a1);}
void teleport_wintty_dep_more(){more();}
void teleport_wintty_dep_nhassert_failed(const char * a0,const char * a1,int a2){nhassert_failed(a0,a1,a2);}
int teleport_wintty_dep_fflush(FILE * a0){return fflush(a0);}
boolean teleport_wintty_dep_debugcore(const char * a0,boolean a1){return debugcore(a0,a1);}
void teleport_wintty_fmt_pline_ipii(const char * a0,int a1,const char* a2,int a3,int a4){pline(a0,a1,a2,a3,a4);}
void teleport_wintty_fmt_pline_p(const char * a0,const char* a1){pline(a0,a1);}
void teleport_wintty_dep_cmov(int a0,int a1){cmov(a0,a1);}
void teleport_wintty_dep_nocmov(int a0,int a1){nocmov(a0,a1);}
void teleport_wintty_dep_update_topl(const char * a0){update_topl(a0);}
void teleport_wintty_dep_remember_topl(){remember_topl();}
void teleport_wintty_dep_show_topl(const char * a0){show_topl(a0);}
FILE * teleport_wintty_dep_fopen(const char * a0,const char * a1){return fopen(a0,a1);}
void teleport_wintty_dep_perror(const char * a0){perror(a0);}
char * teleport_wintty_dep_fgets(char *restrict a0,int a1,FILE *restrict a2){return fgets(a0,a1,a2);}
char * teleport_wintty_dep_tabexpand(char * a0){return tabexpand(a0);}
int teleport_wintty_dep_fclose(FILE * a0){return fclose(a0);}
void teleport_wintty_fmt_impossible_i(const char * a0,int a1){impossible(a0,a1);}
void teleport_wintty_fmt_impossible_p(const char * a0,const char* a1){impossible(a0,a1);}
char * teleport_wintty_dep_strncpy(char * a0,const char * a1,unsigned long a2){return strncpy(a0,a1,a2);}
char * teleport_wintty_dep_dupstr(const char * a0){return dupstr(a0);}
int teleport_wintty_dep_tty_doprev_message(){return tty_doprev_message();}
void teleport_wintty_dep_row_refresh(coordxy a0,coordxy a1,coordxy a2){row_refresh(a0,a1,a2);}
void teleport_wintty_dep_graph_off(){graph_off();}
void teleport_wintty_dep_graph_on(){graph_on();}
void teleport_wintty_dep_redraw_map(boolean a0){redraw_map(a0);}
void teleport_wintty_dep_backsp(){backsp();}
void teleport_wintty_dep_term_start_extracolor(uint32 a0,uint16 a1){term_start_extracolor(a0,a1);}
void teleport_wintty_dep_term_start_bgcolor(int a0){term_start_bgcolor(a0);}
void teleport_wintty_dep_term_end_extracolor(){term_end_extracolor();}
int teleport_wintty_dep_puts(const char * a0){return puts(a0);}
void teleport_wintty_dep_nomux_raw_emit(const char * a0,int a1){nomux_raw_emit(a0,a1);}
void teleport_wintty_dep_term_start_raw_bold(){term_start_raw_bold();}
int teleport_wintty_dep_fputs(const char *restrict a0,FILE *restrict a1){return fputs(a0,a1);}
void teleport_wintty_dep_term_end_raw_bold(){term_end_raw_bold();}
void teleport_wintty_dep_nomux_capture_write_input_boundary(){nomux_capture_write_input_boundary();}
char teleport_wintty_dep_randomkey(){return randomkey();}
int teleport_wintty_dep_teleport_getch(){return teleport_getch();}
int teleport_wintty_dep_fileno(FILE * a0){return fileno(a0);}
ssize_t teleport_wintty_dep_read(int a0,void * a1,size_t a2){return read(a0,a1,a2);}
char * teleport_wintty_dep_mixed_to_utf8(char * a0,size_t a1,const char * a2,int * a3){return mixed_to_utf8(a0,a1,a2,a3);}
char * teleport_wintty_dep_decode_mixed(char * a0,const char * a1){return decode_mixed(a0,a1);}
void teleport_wintty_dep_genl_status_init(){genl_status_init();}
void teleport_wintty_dep_genl_status_enablefield(int a0,const char * a1,const char * a2,boolean a3){genl_status_enablefield(a0,a1,a2,a3);}
int teleport_wintty_dep_term_attr_fixup(int a0){return term_attr_fixup(a0);}
boolean teleport_wintty_dep_critically_low_hp(boolean a0){return critically_low_hp(a0);}
char * teleport_wintty_dep_eos(char * a0){return eos(a0);}
int teleport_wintty_dep_stat_cap_indx(){return stat_cap_indx();}
void teleport_wintty_dep_paniclog(const char * a0,const char * a1){paniclog(a0,a1);}
void teleport_wintty_dep_repad_with_dashes(char * a0){repad_with_dashes(a0);}
