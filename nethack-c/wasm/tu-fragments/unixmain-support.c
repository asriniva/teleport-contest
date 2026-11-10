/* UNIXMAIN typed field/header/dependency/zero storage only. */
#include "../../../scripts/tu-unixmain-layout.h"
#include "unixmain-types.h"
#include <stdlib.h>
#pragma push_macro("sa_handler")
#undef sa_handler
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(size_t)==8,"Review UNIXMAIN LP64");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0&&sizeof(int8)==1&&(int8)-1<0&&sizeof(coordxy)==2&&(char)-1<0,"Review UNIXMAIN scalar widths");
void*teleport_unixmain_global(int index){switch(index){
case 0:return(void*)&gh;
case 1:return(void*)&svh;
case 2:return(void*)&program_state;
case 3:return(void*)&ARGV0;
case 4:return(void*)&u;
case 5:return(void*)&windowprocs;
case 6:return(void*)&gp;
case 7:return(void*)&svp;
case 8:return(void*)&flags;
case 9:return(void*)&gl;
case 10:return(void*)&gs;
case 11:return(void*)&iflags;
case 12:return(void*)&ge;
case 13:return(void*)&ynchars;
case 14:return(void*)&sysopt;
case 15:return(void*)&has_strong_rngseed;
case 16:return(void*)&svn;
default:abort();}}
uint64_t teleport_unixmain_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(__typeof__(((struct sigaction*)0)->__sa_handler)));
case 6:return(uint64_t)(sizeof(struct flag));
case 7:return(uint64_t)(sizeof(struct instance_flags));
case 8:return(uint64_t)(sizeof(struct instance_globals_e));
case 9:return(uint64_t)(sizeof(struct instance_globals_h));
case 10:return(uint64_t)(sizeof(struct instance_globals_l));
case 11:return(uint64_t)(sizeof(struct instance_globals_p));
case 12:return(uint64_t)(sizeof(struct instance_globals_s));
case 13:return(uint64_t)(sizeof(struct instance_globals_saved_h));
case 14:return(uint64_t)(sizeof(struct instance_globals_saved_n));
case 15:return(uint64_t)(sizeof(struct instance_globals_saved_p));
case 16:return(uint64_t)(sizeof(struct passwd));
case 17:return(uint64_t)(sizeof(struct sigaction));
case 18:return(uint64_t)(sizeof(struct sinfo));
case 19:return(uint64_t)(sizeof(struct sysopt_s));
case 20:return(uint64_t)(sizeof(struct window_procs));
case 21:return(uint64_t)(sizeof(struct you));
case 22:return(uint64_t)(PRIMARYSET);
case 23:return(uint64_t)(ROGUESET);
default:abort();}}
uint64_t teleport_unixmain_read(int kind,void*at,int field){switch(kind){
case 0:{__typeof__(((struct sigaction*)0)->__sa_handler)*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sa_handler);
default:abort();}}
case 1:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
case 1:return(uint64_t)(uintptr_t)(p->explore);
case 2:return(uint64_t)(uintptr_t)(p->initrole);
case 3:return(uint64_t)(uintptr_t)(p->initrace);
case 4:return(uint64_t)(uintptr_t)(p->randomall);
default:abort();}}
case 2:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->defer_plname);
case 1:return(uint64_t)(uintptr_t)(p->deferred_X);
case 2:return(uint64_t)(uintptr_t)(p->news);
case 3:return(uint64_t)(uintptr_t)(p->renameinprogress);
case 4:return(uint64_t)(uintptr_t)(p->wiz_error_flag);
case 5:return(uint64_t)(uintptr_t)(p->explore_error_flag);
default:abort();}}
case 3:{struct instance_globals_e*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->early_raw_messages);
default:abort();}}
case 4:{struct instance_globals_h*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hname);
default:abort();}}
case 5:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->locknum);
case 1:return(uint64_t)(uintptr_t)(p->loglua);
default:abort();}}
case 6:{struct instance_globals_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->plnamelen);
default:abort();}}
case 7:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->SAVEF);
default:abort();}}
case 8:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hackpid);
default:abort();}}
case 9:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->nhuuid);
default:abort();}}
case 10:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 11:{struct passwd*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->pw_name);
case 1:return(uint64_t)(uintptr_t)(p->pw_passwd);
case 2:return(uint64_t)(uintptr_t)(p->pw_uid);
case 3:return(uint64_t)(uintptr_t)(p->pw_gid);
case 4:return(uint64_t)(uintptr_t)(p->pw_gecos);
case 5:return(uint64_t)(uintptr_t)(p->pw_dir);
case 6:return(uint64_t)(uintptr_t)(p->pw_shell);
default:abort();}}
case 12:{struct sigaction*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->__sa_handler);
default:abort();}}
case 13:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->preserve_locks);
case 1:return(uint64_t)(uintptr_t)(p->in_self_recover);
case 2:return(uint64_t)(uintptr_t)(p->early_options);
default:abort();}}
case 14:{struct sysopt_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->wizards);
case 1:return(uint64_t)(uintptr_t)(p->explorers);
case 2:return(uint64_t)(uintptr_t)(p->maxplayers);
case 3:return(uint64_t)(uintptr_t)(p->check_plname);
default:abort();}}
case 15:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_init_nhwindows);
case 1:return(uint64_t)(uintptr_t)(p->win_player_selection);
case 2:return(uint64_t)(uintptr_t)(p->win_display_file);
case 3:return(uint64_t)(uintptr_t)(p->win_mark_synch);
case 4:return(uint64_t)(uintptr_t)(p->win_raw_print);
default:abort();}}
case 16:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->uhp);
default:abort();}}
default:abort();}}
void teleport_unixmain_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{__typeof__(((struct sigaction*)0)->__sa_handler)*p=at;switch(field){
case 0:p->sa_handler=(__typeof__(p->sa_handler))value;return;
default:abort();}}
case 1:{struct flag*p=at;switch(field){
case 0:p->debug=(__typeof__(p->debug))value;return;
case 1:p->explore=(__typeof__(p->explore))value;return;
case 2:p->initrole=(__typeof__(p->initrole))value;return;
case 3:p->initrace=(__typeof__(p->initrace))value;return;
case 4:p->randomall=(__typeof__(p->randomall))value;return;
default:abort();}}
case 2:{struct instance_flags*p=at;switch(field){
case 0:p->defer_plname=(__typeof__(p->defer_plname))value;return;
case 1:p->deferred_X=(__typeof__(p->deferred_X))value;return;
case 2:p->news=(__typeof__(p->news))value;return;
case 3:p->renameinprogress=(__typeof__(p->renameinprogress))value;return;
case 4:p->wiz_error_flag=(__typeof__(p->wiz_error_flag))value;return;
case 5:p->explore_error_flag=(__typeof__(p->explore_error_flag))value;return;
default:abort();}}
case 3:{struct instance_globals_e*p=at;switch(field){
case 0:p->early_raw_messages=(__typeof__(p->early_raw_messages))value;return;
default:abort();}}
case 4:{struct instance_globals_h*p=at;switch(field){
case 0:p->hname=(__typeof__(p->hname))value;return;
default:abort();}}
case 5:{struct instance_globals_l*p=at;switch(field){
case 0:p->locknum=(__typeof__(p->locknum))value;return;
case 1:p->loglua=(__typeof__(p->loglua))value;return;
default:abort();}}
case 6:{struct instance_globals_p*p=at;switch(field){
case 0:p->plnamelen=(__typeof__(p->plnamelen))value;return;
default:abort();}}
case 7:{struct instance_globals_s*p=at;switch(field){
default:abort();}}
case 8:{struct instance_globals_saved_h*p=at;switch(field){
case 0:p->hackpid=(__typeof__(p->hackpid))value;return;
default:abort();}}
case 9:{struct instance_globals_saved_n*p=at;switch(field){
default:abort();}}
case 10:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 11:{struct passwd*p=at;switch(field){
case 0:p->pw_name=(__typeof__(p->pw_name))value;return;
case 1:p->pw_passwd=(__typeof__(p->pw_passwd))value;return;
case 2:p->pw_uid=(__typeof__(p->pw_uid))value;return;
case 3:p->pw_gid=(__typeof__(p->pw_gid))value;return;
case 4:p->pw_gecos=(__typeof__(p->pw_gecos))value;return;
case 5:p->pw_dir=(__typeof__(p->pw_dir))value;return;
case 6:p->pw_shell=(__typeof__(p->pw_shell))value;return;
default:abort();}}
case 12:{struct sigaction*p=at;switch(field){
default:abort();}}
case 13:{struct sinfo*p=at;switch(field){
case 0:p->preserve_locks=(__typeof__(p->preserve_locks))value;return;
case 1:p->in_self_recover=(__typeof__(p->in_self_recover))value;return;
case 2:p->early_options=(__typeof__(p->early_options))value;return;
default:abort();}}
case 14:{struct sysopt_s*p=at;switch(field){
case 0:p->wizards=(__typeof__(p->wizards))value;return;
case 1:p->explorers=(__typeof__(p->explorers))value;return;
case 2:p->maxplayers=(__typeof__(p->maxplayers))value;return;
case 3:p->check_plname=(__typeof__(p->check_plname))value;return;
default:abort();}}
case 15:{struct window_procs*p=at;switch(field){
case 0:p->win_init_nhwindows=(__typeof__(p->win_init_nhwindows))value;return;
case 1:p->win_player_selection=(__typeof__(p->win_player_selection))value;return;
case 2:p->win_display_file=(__typeof__(p->win_display_file))value;return;
case 3:p->win_mark_synch=(__typeof__(p->win_mark_synch))value;return;
case 4:p->win_raw_print=(__typeof__(p->win_raw_print))value;return;
default:abort();}}
case 16:{struct you*p=at;switch(field){
case 0:p->uhp=(__typeof__(p->uhp))value;return;
default:abort();}}
default:abort();}}
void* teleport_unixmain_address(int kind,void*at,int field){switch(kind){
case 0:{__typeof__(((struct sigaction*)0)->__sa_handler)*p=at;switch(field){
case 0:return(void*)&p->sa_handler;
default:abort();}}
case 1:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
case 1:return(void*)&p->explore;
case 2:return(void*)&p->initrole;
case 3:return(void*)&p->initrace;
case 4:return(void*)&p->randomall;
default:abort();}}
case 2:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->defer_plname;
case 1:return(void*)&p->deferred_X;
case 2:return(void*)&p->news;
case 3:return(void*)&p->renameinprogress;
case 4:return(void*)&p->wiz_error_flag;
case 5:return(void*)&p->explore_error_flag;
default:abort();}}
case 3:{struct instance_globals_e*p=at;switch(field){
case 0:return(void*)&p->early_raw_messages;
default:abort();}}
case 4:{struct instance_globals_h*p=at;switch(field){
case 0:return(void*)&p->hname;
default:abort();}}
case 5:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->locknum;
case 1:return(void*)&p->loglua;
default:abort();}}
case 6:{struct instance_globals_p*p=at;switch(field){
case 0:return(void*)&p->plnamelen;
default:abort();}}
case 7:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->SAVEF;
default:abort();}}
case 8:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return(void*)&p->hackpid;
default:abort();}}
case 9:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(void*)&p->nhuuid;
default:abort();}}
case 10:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(void*)&p->plname;
default:abort();}}
case 11:{struct passwd*p=at;switch(field){
case 0:return(void*)&p->pw_name;
case 1:return(void*)&p->pw_passwd;
case 2:return(void*)&p->pw_uid;
case 3:return(void*)&p->pw_gid;
case 4:return(void*)&p->pw_gecos;
case 5:return(void*)&p->pw_dir;
case 6:return(void*)&p->pw_shell;
default:abort();}}
case 12:{struct sigaction*p=at;switch(field){
case 0:return(void*)&p->__sa_handler;
default:abort();}}
case 13:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->preserve_locks;
case 1:return(void*)&p->in_self_recover;
case 2:return(void*)&p->early_options;
default:abort();}}
case 14:{struct sysopt_s*p=at;switch(field){
case 0:return(void*)&p->wizards;
case 1:return(void*)&p->explorers;
case 2:return(void*)&p->maxplayers;
case 3:return(void*)&p->check_plname;
default:abort();}}
case 15:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_init_nhwindows;
case 1:return(void*)&p->win_player_selection;
case 2:return(void*)&p->win_display_file;
case 3:return(void*)&p->win_mark_synch;
case 4:return(void*)&p->win_raw_print;
default:abort();}}
case 16:{struct you*p=at;switch(field){
case 0:return(void*)&p->uhp;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_unixmain_var0(char * a0){(pline)(a0);}
void teleport_unixmain_var1(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_unixmain_var2(char * a0){(config_error_add)(a0);}
void teleport_unixmain_var3(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_unixmain_var4(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_unixmain_var5(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_unixmain_var6(char * a0,char * a1,char * a2,char * a3){(config_error_add)(a0,a1,a2,a3);}
void teleport_unixmain_var7(char * a0,char * a1){(error)(a0,a1);}
void teleport_unixmain_var8(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_unixmain_var9(char * a0){(You)(a0);}
void teleport_unixmain_var10(char * a0){(pline)(a0);}
void teleport_unixmain_var11(char * a0){(You)(a0);}
void teleport_unixmain_var12(char * a0){(You)(a0);}
void teleport_unixmain_cb0(void (*fn)(int *, char **),int * a0,char ** a1){fn(a0,a1);}
void teleport_unixmain_cb1(void (*fn)(const char *, boolean),const char * a0,boolean a1){fn(a0,a1);}
void teleport_unixmain_cb2(void (*fn)(const char *),const char * a0){fn(a0);}
void teleport_unixmain_cb3(void (*fn)(void)){fn();}
void teleport_unixmain_cb4(void (*fn)(void)){fn();}
#pragma clang diagnostic pop
static char unixmain_literals[672];
char*teleport_unixmain_literal_storage(void){return unixmain_literals;}
size_t teleport_unixmain_literal_capacity(void){return sizeof unixmain_literals;}
static struct passwd unixmain_backing_0;
static struct passwd * unixmain_backing_1;
static char unixmain_backing_2[256];
void*teleport_unixmain_storage(int i){switch(i){
case 0:return &unixmain_backing_0;
case 1:return &unixmain_backing_1;
case 2:return &unixmain_backing_2;
default:abort();}}
int teleport_unixmain_header_isspace(int v){return __isspace(v);}
void*teleport_unixmain_function(int i){switch(i){
case 0:return(void*)done1;
case 1:return(void*)hangup;
default:abort();}}
#ifdef TELEPORT_UNIXMAIN_VALIDATE_ORIGINAL
#endif
#pragma pop_macro("sa_handler")
