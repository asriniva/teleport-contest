#ifndef TELEPORT_OPTIONS_ABI_H
#define TELEPORT_OPTIONS_ABI_H
#include "hack.h"
struct teleport_options_paranoia_opts {
int flagmask;
const char * argname;
int argMinLen;
const char * synonym;
int synMinLen;
const char * explain;
};
struct teleport_options_objsymopt {
int num;
const char * nam;
const char * descr;
};
struct teleport_options_menu_cmd_t {
const char * name;
char cmd;
const char * desc;
};
struct teleport_options_options_msgtype_name {
const char * name;
xint8 msgtyp;
const char * descr;
};
struct teleport_options_menuscrollinfo {
char cmdkey;
uchar maskindx;
};
struct teleport_options_xtra_cntrls {
const char * key;
const char * desc;
};
struct teleport_options_action {
char letr;
const char * desc;
};
#ifndef TELEPORT_OPTIONS_ORIGINAL_INCLUDED
enum window_option_types {MESSAGE_OPTION=1,STATUS_OPTION,MAP_OPTION,MENU_OPTION,TEXT_OPTION};
enum optn_result {optn_silenterr=-1,optn_err=0,optn_ok};
enum requests {do_nothing,do_init,do_set,do_handler,get_val,get_cnf_val};
enum {MAX_ROLEOPT=4};
#endif
extern int wcolors_opt[4];
extern int options_set_window_colors_flag;
extern const char *const known_handling[];
extern const char *const known_restrictions[];
extern const struct symparse loadsyms[];
#endif
