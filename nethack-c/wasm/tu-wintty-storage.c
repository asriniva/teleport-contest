/* Zero-only WINTTY backing. JS owns all configured initializers. */
#include "hack.h"
#include "wintty.h"
#include "tcap.h"
#include <stdint.h>
#ifndef TELEPORT_REFERENCE_WINTTY
struct window_procs tty_procs;
winid BASE_WINDOW;
struct WinDesc * wins[20];
struct DisplayDesc * ttyDisplay;
static volatile int teleport_wintty_data_erasing_tty_screen;
static char teleport_wintty_data_obuf[1024];
static const char teleport_wintty_data_winpanicstr[22];
char defmorestr[9];
static boolean teleport_wintty_data_clipping;
static int teleport_wintty_data_clipx;
static int teleport_wintty_data_clipxmax;
static int teleport_wintty_data_clipy;
static int teleport_wintty_data_clipymax;
boolean GFlag;
boolean HE_resets_AS;
static boolean teleport_wintty_data_calling_from_update_inventory;
static const char teleport_wintty_data_default_menu_cmds[12];
static volatile int teleport_wintty_data_resize_mesg;
static color_attr teleport_wintty_data_tty_menu_promptstyle;
static unsigned long * teleport_wintty_data_tty_colormasks;
static long teleport_wintty_data_tty_condition_bits;
static struct tty_status_fields teleport_wintty_data_tty_status[2][27];
static int teleport_wintty_data_hpbar_percent;
static int teleport_wintty_data_hpbar_crit_hp;
static const char *const teleport_wintty_data_encvals[3][6];
static const enum statusfields teleport_wintty_data_twolineorder[3][19];
static const enum statusfields teleport_wintty_data_threelineorder[3][19];
static const enum statusfields (*teleport_wintty_data_fieldorder)[19];
static int teleport_wintty_data_finalx[3][2];
static boolean teleport_wintty_data_windowdata_init;
static int teleport_wintty_data_cond_shrinklvl;
static int teleport_wintty_data_enclev;
static int teleport_wintty_data_enc_shrinklvl;
static int teleport_wintty_data_dlvl_shrinklvl;
static boolean teleport_wintty_data_truncation_expected;
static int teleport_wintty_data_do_field_opt;
void *teleport_wintty_data_storage(int i){switch(i){case 0:return(void*)&tty_procs;case 1:return(void*)&BASE_WINDOW;case 2:return(void*)&wins;case 3:return(void*)&ttyDisplay;case 4:return(void*)&teleport_wintty_data_erasing_tty_screen;case 5:return(void*)&teleport_wintty_data_obuf;case 6:return(void*)&teleport_wintty_data_winpanicstr;case 7:return(void*)&defmorestr;case 8:return(void*)&teleport_wintty_data_clipping;case 9:return(void*)&teleport_wintty_data_clipx;case 10:return(void*)&teleport_wintty_data_clipxmax;case 11:return(void*)&teleport_wintty_data_clipy;case 12:return(void*)&teleport_wintty_data_clipymax;case 13:return(void*)&GFlag;case 14:return(void*)&HE_resets_AS;case 15:return(void*)&teleport_wintty_data_calling_from_update_inventory;case 16:return(void*)&teleport_wintty_data_default_menu_cmds;case 17:return(void*)&teleport_wintty_data_resize_mesg;case 18:return(void*)&teleport_wintty_data_tty_menu_promptstyle;case 19:return(void*)&teleport_wintty_data_tty_colormasks;case 20:return(void*)&teleport_wintty_data_tty_condition_bits;case 21:return(void*)&teleport_wintty_data_tty_status;case 22:return(void*)&teleport_wintty_data_hpbar_percent;case 23:return(void*)&teleport_wintty_data_hpbar_crit_hp;case 24:return(void*)&teleport_wintty_data_encvals;case 25:return(void*)&teleport_wintty_data_twolineorder;case 26:return(void*)&teleport_wintty_data_threelineorder;case 27:return(void*)&teleport_wintty_data_fieldorder;case 28:return(void*)&teleport_wintty_data_finalx;case 29:return(void*)&teleport_wintty_data_windowdata_init;case 30:return(void*)&teleport_wintty_data_cond_shrinklvl;case 31:return(void*)&teleport_wintty_data_enclev;case 32:return(void*)&teleport_wintty_data_enc_shrinklvl;case 33:return(void*)&teleport_wintty_data_dlvl_shrinklvl;case 34:return(void*)&teleport_wintty_data_truncation_expected;case 35:return(void*)&teleport_wintty_data_do_field_opt;default:return 0;}}
#else
extern void *teleport_wintty_reference_storage(int);
void *teleport_wintty_data_storage(int i){return teleport_wintty_reference_storage(i); }
#endif
