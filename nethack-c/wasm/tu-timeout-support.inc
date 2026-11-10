/* TIMEOUT typed fields, actual native dependencies, format ABI and opaque callbacks. */
#include "hack.h"
#include <stdlib.h>
const void *teleport_timeout_global(int i){switch(i){case 0:return &u;case 1:return &gy;case 2:return &gm;case 3:return &gn;case 4:return &svk;case 5:return &svm;case 6:return &svq;case 7:return &svc;case 8:return &svl;case 9:return &svt;case 10:return &gt;case 11:return &gb;case 12:return &cg;case 13:return &gi;case 14:return &flags;case 15:return &iflags;case 16:return &disp;case 17:return mons;case 18:return &gv;case 19:return &gu;case 20:return &svd;case 21:return genders;default:return 0;}}
void *teleport_timeout_equipment(int i){switch(i){case 0:return uwep;case 1:return uswapwep;case 2:return uarmh;case 3:return uarmf;case 4:return uamul;default:return 0;}}
unsigned teleport_timeout_monster_bit(struct monst *p,int i){switch(i){case 0:return p->wormno;default:return 0;}}
void teleport_timeout_set_monster_bit(struct monst *p,int i,unsigned v){switch(i){case 0:p->wormno=v;break;}}
unsigned teleport_timeout_object_bit(struct obj *p,int i){switch(i){case 0:return p->dknown;case 1:return p->lamplit;case 2:return p->cursed;case 3:return p->odiluted;default:return 0;}}
void teleport_timeout_set_object_bit(struct obj *p,int i,unsigned v){switch(i){case 0:p->dknown=v;break;case 1:p->lamplit=v;break;case 2:p->cursed=v;break;case 3:p->odiluted=v;break;}}
unsigned teleport_timeout_terrain_bit(struct rm *p,int i){switch(i){case 0:return p->drawbridgemask;default:return 0;}}
unsigned teleport_timeout_hero_bit(int i){switch(i){case 0:return u.uhave.amulet;case 1:return u.uinvulnerable;case 2:return u.uburied;case 3:return u.usick_type;case 4:return u.uroleplay.deaf;default:return 0;}}
void teleport_timeout_set_hero_bit(int i,unsigned v){switch(i){case 0:u.uhave.amulet=v;break;case 1:u.uinvulnerable=v;break;case 2:u.uburied=v;break;case 3:u.usick_type=v;break;case 4:u.uroleplay.deaf=v;break;}}
unsigned teleport_timeout_flag_bit(int i){switch(i){case 0:return svq.quest_status.killed_leader;case 1:return svl.level.flags.stormy;default:return 0;}}
unsigned teleport_timeout_timer_bit(timer_element*p){return p->needs_fixup;}
void teleport_timeout_set_timer_bit(timer_element*p,unsigned v){p->needs_fixup=v;}
const char *teleport_timeout_common_string(int i){switch(i){case 0:return You_can_move_again;case 1:return something;case 2:return NH_BLUE;case 3:return NH_GOLDEN;default:return NH_GREEN;}}
static char teleport_timeout_literals[TELEPORT_TIMEOUT_LITERAL_CAPACITY+sizeof "%s"];
void *teleport_timeout_literal_storage(void){return teleport_timeout_literals;}
size_t teleport_timeout_literal_capacity(void){return sizeof teleport_timeout_literals;}
void teleport_timeout_free(void*p){free(p);}
uintptr_t teleport_timeout_callback_pointer(int i){switch(i){case 0:return(uintptr_t)rot_organic;case 1:return(uintptr_t)rot_corpse;case 2:return(uintptr_t)revive_mon;case 3:return(uintptr_t)zombify_mon;case 4:return(uintptr_t)fig_transform;case 5:return(uintptr_t)shrink_glob;case 6:return(uintptr_t)melt_ice_away;default:return 0;}}
void teleport_timeout_invoke(uintptr_t fn,anything*arg,long when){((timeout_proc)fn)(arg,when);}
void teleport_timeout_rng_caller(int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("timeout.c",line,fn);}
int teleport_timeout_rng(int n,int line,const char*fn,int already){if(!already&&rng_log_enabled())rng_log_set_caller("timeout.c",line,fn);return(rn2)(n);}
int teleport_timeout_rnd(int n,int line,const char*fn,int already){if(!already&&rng_log_enabled())rng_log_set_caller("timeout.c",line,fn);return(rnd)(n);}
int teleport_timeout_dice(int n,int x,int line,const char*fn,int already){if(!already&&rng_log_enabled())rng_log_set_caller("timeout.c",line,fn);return(d)(n,x);}
winid teleport_timeout_create(int type){return create_nhwindow(type);}
void teleport_timeout_destroy(winid w){destroy_nhwindow(w);}
void teleport_timeout_display(winid w,boolean b){display_nhwindow(w,b);}
void teleport_timeout_sfo_fe(NHFILE*n,timer_element*t,const char*k){Sfo_fe(n,t,k);}
void teleport_timeout_sfi_fe(NHFILE*n,timer_element*t,const char*k){Sfi_fe(n,t,k);}
void teleport_timeout_putstr(winid w,int a,const char*t){putstr(w,a,t);}
void teleport_timeout_sfo_int(NHFILE*n,int*p,const char*k){Sfo_int(n,p,k);}
void teleport_timeout_sfi_int(NHFILE*n,int*p,const char*k){Sfi_int(n,p,k);}
void teleport_timeout_sfo_ulong(NHFILE*n,unsigned long*p,const char*k){Sfo_ulong(n,p,k);}
void teleport_timeout_sfi_ulong(NHFILE*n,unsigned long*p,const char*k){Sfi_ulong(n,p,k);}
void teleport_timeout_assertion(int i){static const unsigned assert_lines[]=TELEPORT_TIMEOUT_ASSERT_LINES;static const char*const conditions[]=TELEPORT_TIMEOUT_ASSERT_CONDITIONS;static const char*const functions[]=TELEPORT_TIMEOUT_ASSERT_FUNCTIONS;__assert_fail(conditions[i],"timeout.c",assert_lines[i],functions[i]);}
void teleport_timeout_pline_none(const char *fmt){pline(fmt);}
void teleport_timeout_pline_U(const char *fmt,unsigned long a0){pline(fmt,a0);}
void teleport_timeout_pline_Ui(const char *fmt,unsigned long a0,int a1){pline(fmt,a0,a1);}
void teleport_timeout_pline_Uii(const char *fmt,unsigned long a0,int a1,int a2){pline(fmt,a0,a1,a2);}
void teleport_timeout_pline_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){pline(fmt,a0,a1,a2,a3);}
void teleport_timeout_pline_i(const char *fmt,int a0){pline(fmt,a0);}
void teleport_timeout_pline_ipl(const char *fmt,int a0,const char *a1,long a2){pline(fmt,a0,a1,a2);}
void teleport_timeout_pline_l(const char *fmt,long a0){pline(fmt,a0);}
void teleport_timeout_pline_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_pline_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_pline_lp(const char *fmt,long a0,const char *a1){pline(fmt,a0,a1);}
void teleport_timeout_pline_p(const char *fmt,const char *a0){pline(fmt,a0);}
void teleport_timeout_pline_pU(const char *fmt,const char *a0,unsigned long a1){pline(fmt,a0,a1);}
void teleport_timeout_pline_pi(const char *fmt,const char *a0,int a1){pline(fmt,a0,a1);}
void teleport_timeout_pline_piU(const char *fmt,const char *a0,int a1,unsigned long a2){pline(fmt,a0,a1,a2);}
void teleport_timeout_pline_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_pline_pp(const char *fmt,const char *a0,const char *a1){pline(fmt,a0,a1);}
void teleport_timeout_pline_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){pline(fmt,a0,a1,a2);}
void teleport_timeout_pline_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_pline_u(const char *fmt,unsigned a0){pline(fmt,a0);}
void teleport_timeout_Norep_none(const char *fmt){Norep(fmt);}
void teleport_timeout_Norep_U(const char *fmt,unsigned long a0){Norep(fmt,a0);}
void teleport_timeout_Norep_Ui(const char *fmt,unsigned long a0,int a1){Norep(fmt,a0,a1);}
void teleport_timeout_Norep_Uii(const char *fmt,unsigned long a0,int a1,int a2){Norep(fmt,a0,a1,a2);}
void teleport_timeout_Norep_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){Norep(fmt,a0,a1,a2,a3);}
void teleport_timeout_Norep_i(const char *fmt,int a0){Norep(fmt,a0);}
void teleport_timeout_Norep_ipl(const char *fmt,int a0,const char *a1,long a2){Norep(fmt,a0,a1,a2);}
void teleport_timeout_Norep_l(const char *fmt,long a0){Norep(fmt,a0);}
void teleport_timeout_Norep_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){Norep(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Norep_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){Norep(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Norep_lp(const char *fmt,long a0,const char *a1){Norep(fmt,a0,a1);}
void teleport_timeout_Norep_p(const char *fmt,const char *a0){Norep(fmt,a0);}
void teleport_timeout_Norep_pU(const char *fmt,const char *a0,unsigned long a1){Norep(fmt,a0,a1);}
void teleport_timeout_Norep_pi(const char *fmt,const char *a0,int a1){Norep(fmt,a0,a1);}
void teleport_timeout_Norep_piU(const char *fmt,const char *a0,int a1,unsigned long a2){Norep(fmt,a0,a1,a2);}
void teleport_timeout_Norep_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){Norep(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Norep_pp(const char *fmt,const char *a0,const char *a1){Norep(fmt,a0,a1);}
void teleport_timeout_Norep_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){Norep(fmt,a0,a1,a2);}
void teleport_timeout_Norep_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){Norep(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Norep_u(const char *fmt,unsigned a0){Norep(fmt,a0);}
void teleport_timeout_You_none(const char *fmt){You(fmt);}
void teleport_timeout_You_U(const char *fmt,unsigned long a0){You(fmt,a0);}
void teleport_timeout_You_Ui(const char *fmt,unsigned long a0,int a1){You(fmt,a0,a1);}
void teleport_timeout_You_Uii(const char *fmt,unsigned long a0,int a1,int a2){You(fmt,a0,a1,a2);}
void teleport_timeout_You_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){You(fmt,a0,a1,a2,a3);}
void teleport_timeout_You_i(const char *fmt,int a0){You(fmt,a0);}
void teleport_timeout_You_ipl(const char *fmt,int a0,const char *a1,long a2){You(fmt,a0,a1,a2);}
void teleport_timeout_You_l(const char *fmt,long a0){You(fmt,a0);}
void teleport_timeout_You_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){You(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){You(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_lp(const char *fmt,long a0,const char *a1){You(fmt,a0,a1);}
void teleport_timeout_You_p(const char *fmt,const char *a0){You(fmt,a0);}
void teleport_timeout_You_pU(const char *fmt,const char *a0,unsigned long a1){You(fmt,a0,a1);}
void teleport_timeout_You_pi(const char *fmt,const char *a0,int a1){You(fmt,a0,a1);}
void teleport_timeout_You_piU(const char *fmt,const char *a0,int a1,unsigned long a2){You(fmt,a0,a1,a2);}
void teleport_timeout_You_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){You(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_pp(const char *fmt,const char *a0,const char *a1){You(fmt,a0,a1);}
void teleport_timeout_You_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You(fmt,a0,a1,a2);}
void teleport_timeout_You_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_u(const char *fmt,unsigned a0){You(fmt,a0);}
void teleport_timeout_Your_none(const char *fmt){Your(fmt);}
void teleport_timeout_Your_U(const char *fmt,unsigned long a0){Your(fmt,a0);}
void teleport_timeout_Your_Ui(const char *fmt,unsigned long a0,int a1){Your(fmt,a0,a1);}
void teleport_timeout_Your_Uii(const char *fmt,unsigned long a0,int a1,int a2){Your(fmt,a0,a1,a2);}
void teleport_timeout_Your_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){Your(fmt,a0,a1,a2,a3);}
void teleport_timeout_Your_i(const char *fmt,int a0){Your(fmt,a0);}
void teleport_timeout_Your_ipl(const char *fmt,int a0,const char *a1,long a2){Your(fmt,a0,a1,a2);}
void teleport_timeout_Your_l(const char *fmt,long a0){Your(fmt,a0);}
void teleport_timeout_Your_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){Your(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Your_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){Your(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Your_lp(const char *fmt,long a0,const char *a1){Your(fmt,a0,a1);}
void teleport_timeout_Your_p(const char *fmt,const char *a0){Your(fmt,a0);}
void teleport_timeout_Your_pU(const char *fmt,const char *a0,unsigned long a1){Your(fmt,a0,a1);}
void teleport_timeout_Your_pi(const char *fmt,const char *a0,int a1){Your(fmt,a0,a1);}
void teleport_timeout_Your_piU(const char *fmt,const char *a0,int a1,unsigned long a2){Your(fmt,a0,a1,a2);}
void teleport_timeout_Your_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){Your(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Your_pp(const char *fmt,const char *a0,const char *a1){Your(fmt,a0,a1);}
void teleport_timeout_Your_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){Your(fmt,a0,a1,a2);}
void teleport_timeout_Your_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){Your(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_Your_u(const char *fmt,unsigned a0){Your(fmt,a0);}
void teleport_timeout_You_feel_none(const char *fmt){You_feel(fmt);}
void teleport_timeout_You_feel_U(const char *fmt,unsigned long a0){You_feel(fmt,a0);}
void teleport_timeout_You_feel_Ui(const char *fmt,unsigned long a0,int a1){You_feel(fmt,a0,a1);}
void teleport_timeout_You_feel_Uii(const char *fmt,unsigned long a0,int a1,int a2){You_feel(fmt,a0,a1,a2);}
void teleport_timeout_You_feel_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){You_feel(fmt,a0,a1,a2,a3);}
void teleport_timeout_You_feel_i(const char *fmt,int a0){You_feel(fmt,a0);}
void teleport_timeout_You_feel_ipl(const char *fmt,int a0,const char *a1,long a2){You_feel(fmt,a0,a1,a2);}
void teleport_timeout_You_feel_l(const char *fmt,long a0){You_feel(fmt,a0);}
void teleport_timeout_You_feel_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){You_feel(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_feel_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){You_feel(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_feel_lp(const char *fmt,long a0,const char *a1){You_feel(fmt,a0,a1);}
void teleport_timeout_You_feel_p(const char *fmt,const char *a0){You_feel(fmt,a0);}
void teleport_timeout_You_feel_pU(const char *fmt,const char *a0,unsigned long a1){You_feel(fmt,a0,a1);}
void teleport_timeout_You_feel_pi(const char *fmt,const char *a0,int a1){You_feel(fmt,a0,a1);}
void teleport_timeout_You_feel_piU(const char *fmt,const char *a0,int a1,unsigned long a2){You_feel(fmt,a0,a1,a2);}
void teleport_timeout_You_feel_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){You_feel(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_feel_pp(const char *fmt,const char *a0,const char *a1){You_feel(fmt,a0,a1);}
void teleport_timeout_You_feel_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You_feel(fmt,a0,a1,a2);}
void teleport_timeout_You_feel_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You_feel(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_feel_u(const char *fmt,unsigned a0){You_feel(fmt,a0);}
void teleport_timeout_You_hear_none(const char *fmt){You_hear(fmt);}
void teleport_timeout_You_hear_U(const char *fmt,unsigned long a0){You_hear(fmt,a0);}
void teleport_timeout_You_hear_Ui(const char *fmt,unsigned long a0,int a1){You_hear(fmt,a0,a1);}
void teleport_timeout_You_hear_Uii(const char *fmt,unsigned long a0,int a1,int a2){You_hear(fmt,a0,a1,a2);}
void teleport_timeout_You_hear_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){You_hear(fmt,a0,a1,a2,a3);}
void teleport_timeout_You_hear_i(const char *fmt,int a0){You_hear(fmt,a0);}
void teleport_timeout_You_hear_ipl(const char *fmt,int a0,const char *a1,long a2){You_hear(fmt,a0,a1,a2);}
void teleport_timeout_You_hear_l(const char *fmt,long a0){You_hear(fmt,a0);}
void teleport_timeout_You_hear_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){You_hear(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_hear_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){You_hear(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_hear_lp(const char *fmt,long a0,const char *a1){You_hear(fmt,a0,a1);}
void teleport_timeout_You_hear_p(const char *fmt,const char *a0){You_hear(fmt,a0);}
void teleport_timeout_You_hear_pU(const char *fmt,const char *a0,unsigned long a1){You_hear(fmt,a0,a1);}
void teleport_timeout_You_hear_pi(const char *fmt,const char *a0,int a1){You_hear(fmt,a0,a1);}
void teleport_timeout_You_hear_piU(const char *fmt,const char *a0,int a1,unsigned long a2){You_hear(fmt,a0,a1,a2);}
void teleport_timeout_You_hear_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){You_hear(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_hear_pp(const char *fmt,const char *a0,const char *a1){You_hear(fmt,a0,a1);}
void teleport_timeout_You_hear_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You_hear(fmt,a0,a1,a2);}
void teleport_timeout_You_hear_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You_hear(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_hear_u(const char *fmt,unsigned a0){You_hear(fmt,a0);}
void teleport_timeout_You_see_none(const char *fmt){You_see(fmt);}
void teleport_timeout_You_see_U(const char *fmt,unsigned long a0){You_see(fmt,a0);}
void teleport_timeout_You_see_Ui(const char *fmt,unsigned long a0,int a1){You_see(fmt,a0,a1);}
void teleport_timeout_You_see_Uii(const char *fmt,unsigned long a0,int a1,int a2){You_see(fmt,a0,a1,a2);}
void teleport_timeout_You_see_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){You_see(fmt,a0,a1,a2,a3);}
void teleport_timeout_You_see_i(const char *fmt,int a0){You_see(fmt,a0);}
void teleport_timeout_You_see_ipl(const char *fmt,int a0,const char *a1,long a2){You_see(fmt,a0,a1,a2);}
void teleport_timeout_You_see_l(const char *fmt,long a0){You_see(fmt,a0);}
void teleport_timeout_You_see_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){You_see(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_see_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){You_see(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_see_lp(const char *fmt,long a0,const char *a1){You_see(fmt,a0,a1);}
void teleport_timeout_You_see_p(const char *fmt,const char *a0){You_see(fmt,a0);}
void teleport_timeout_You_see_pU(const char *fmt,const char *a0,unsigned long a1){You_see(fmt,a0,a1);}
void teleport_timeout_You_see_pi(const char *fmt,const char *a0,int a1){You_see(fmt,a0,a1);}
void teleport_timeout_You_see_piU(const char *fmt,const char *a0,int a1,unsigned long a2){You_see(fmt,a0,a1,a2);}
void teleport_timeout_You_see_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){You_see(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_see_pp(const char *fmt,const char *a0,const char *a1){You_see(fmt,a0,a1);}
void teleport_timeout_You_see_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You_see(fmt,a0,a1,a2);}
void teleport_timeout_You_see_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You_see(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_You_see_u(const char *fmt,unsigned a0){You_see(fmt,a0);}
void teleport_timeout_urgent_pline_none(const char *fmt){urgent_pline(fmt);}
void teleport_timeout_urgent_pline_U(const char *fmt,unsigned long a0){urgent_pline(fmt,a0);}
void teleport_timeout_urgent_pline_Ui(const char *fmt,unsigned long a0,int a1){urgent_pline(fmt,a0,a1);}
void teleport_timeout_urgent_pline_Uii(const char *fmt,unsigned long a0,int a1,int a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_timeout_urgent_pline_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){urgent_pline(fmt,a0,a1,a2,a3);}
void teleport_timeout_urgent_pline_i(const char *fmt,int a0){urgent_pline(fmt,a0);}
void teleport_timeout_urgent_pline_ipl(const char *fmt,int a0,const char *a1,long a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_timeout_urgent_pline_l(const char *fmt,long a0){urgent_pline(fmt,a0);}
void teleport_timeout_urgent_pline_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){urgent_pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_urgent_pline_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){urgent_pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_urgent_pline_lp(const char *fmt,long a0,const char *a1){urgent_pline(fmt,a0,a1);}
void teleport_timeout_urgent_pline_p(const char *fmt,const char *a0){urgent_pline(fmt,a0);}
void teleport_timeout_urgent_pline_pU(const char *fmt,const char *a0,unsigned long a1){urgent_pline(fmt,a0,a1);}
void teleport_timeout_urgent_pline_pi(const char *fmt,const char *a0,int a1){urgent_pline(fmt,a0,a1);}
void teleport_timeout_urgent_pline_piU(const char *fmt,const char *a0,int a1,unsigned long a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_timeout_urgent_pline_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){urgent_pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_urgent_pline_pp(const char *fmt,const char *a0,const char *a1){urgent_pline(fmt,a0,a1);}
void teleport_timeout_urgent_pline_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_timeout_urgent_pline_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){urgent_pline(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_urgent_pline_u(const char *fmt,unsigned a0){urgent_pline(fmt,a0);}
void teleport_timeout_verbalize_none(const char *fmt){verbalize(fmt);}
void teleport_timeout_verbalize_U(const char *fmt,unsigned long a0){verbalize(fmt,a0);}
void teleport_timeout_verbalize_Ui(const char *fmt,unsigned long a0,int a1){verbalize(fmt,a0,a1);}
void teleport_timeout_verbalize_Uii(const char *fmt,unsigned long a0,int a1,int a2){verbalize(fmt,a0,a1,a2);}
void teleport_timeout_verbalize_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){verbalize(fmt,a0,a1,a2,a3);}
void teleport_timeout_verbalize_i(const char *fmt,int a0){verbalize(fmt,a0);}
void teleport_timeout_verbalize_ipl(const char *fmt,int a0,const char *a1,long a2){verbalize(fmt,a0,a1,a2);}
void teleport_timeout_verbalize_l(const char *fmt,long a0){verbalize(fmt,a0);}
void teleport_timeout_verbalize_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){verbalize(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_verbalize_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){verbalize(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_verbalize_lp(const char *fmt,long a0,const char *a1){verbalize(fmt,a0,a1);}
void teleport_timeout_verbalize_p(const char *fmt,const char *a0){verbalize(fmt,a0);}
void teleport_timeout_verbalize_pU(const char *fmt,const char *a0,unsigned long a1){verbalize(fmt,a0,a1);}
void teleport_timeout_verbalize_pi(const char *fmt,const char *a0,int a1){verbalize(fmt,a0,a1);}
void teleport_timeout_verbalize_piU(const char *fmt,const char *a0,int a1,unsigned long a2){verbalize(fmt,a0,a1,a2);}
void teleport_timeout_verbalize_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){verbalize(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_verbalize_pp(const char *fmt,const char *a0,const char *a1){verbalize(fmt,a0,a1);}
void teleport_timeout_verbalize_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){verbalize(fmt,a0,a1,a2);}
void teleport_timeout_verbalize_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){verbalize(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_verbalize_u(const char *fmt,unsigned a0){verbalize(fmt,a0);}
void teleport_timeout_impossible_none(const char *fmt){impossible(fmt);}
void teleport_timeout_impossible_U(const char *fmt,unsigned long a0){impossible(fmt,a0);}
void teleport_timeout_impossible_Ui(const char *fmt,unsigned long a0,int a1){impossible(fmt,a0,a1);}
void teleport_timeout_impossible_Uii(const char *fmt,unsigned long a0,int a1,int a2){impossible(fmt,a0,a1,a2);}
void teleport_timeout_impossible_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){impossible(fmt,a0,a1,a2,a3);}
void teleport_timeout_impossible_i(const char *fmt,int a0){impossible(fmt,a0);}
void teleport_timeout_impossible_ipl(const char *fmt,int a0,const char *a1,long a2){impossible(fmt,a0,a1,a2);}
void teleport_timeout_impossible_l(const char *fmt,long a0){impossible(fmt,a0);}
void teleport_timeout_impossible_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){impossible(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_impossible_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){impossible(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_impossible_lp(const char *fmt,long a0,const char *a1){impossible(fmt,a0,a1);}
void teleport_timeout_impossible_p(const char *fmt,const char *a0){impossible(fmt,a0);}
void teleport_timeout_impossible_pU(const char *fmt,const char *a0,unsigned long a1){impossible(fmt,a0,a1);}
void teleport_timeout_impossible_pi(const char *fmt,const char *a0,int a1){impossible(fmt,a0,a1);}
void teleport_timeout_impossible_piU(const char *fmt,const char *a0,int a1,unsigned long a2){impossible(fmt,a0,a1,a2);}
void teleport_timeout_impossible_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){impossible(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_impossible_pp(const char *fmt,const char *a0,const char *a1){impossible(fmt,a0,a1);}
void teleport_timeout_impossible_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){impossible(fmt,a0,a1,a2);}
void teleport_timeout_impossible_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){impossible(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_impossible_u(const char *fmt,unsigned a0){impossible(fmt,a0);}
void teleport_timeout_panic_none(const char *fmt){panic(fmt);}
void teleport_timeout_panic_U(const char *fmt,unsigned long a0){panic(fmt,a0);}
void teleport_timeout_panic_Ui(const char *fmt,unsigned long a0,int a1){panic(fmt,a0,a1);}
void teleport_timeout_panic_Uii(const char *fmt,unsigned long a0,int a1,int a2){panic(fmt,a0,a1,a2);}
void teleport_timeout_panic_Uiii(const char *fmt,unsigned long a0,int a1,int a2,int a3){panic(fmt,a0,a1,a2,a3);}
void teleport_timeout_panic_i(const char *fmt,int a0){panic(fmt,a0);}
void teleport_timeout_panic_ipl(const char *fmt,int a0,const char *a1,long a2){panic(fmt,a0,a1,a2);}
void teleport_timeout_panic_l(const char *fmt,long a0){panic(fmt,a0);}
void teleport_timeout_panic_llpip(const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){panic(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_panic_llppp(const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){panic(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_panic_lp(const char *fmt,long a0,const char *a1){panic(fmt,a0,a1);}
void teleport_timeout_panic_p(const char *fmt,const char *a0){panic(fmt,a0);}
void teleport_timeout_panic_pU(const char *fmt,const char *a0,unsigned long a1){panic(fmt,a0,a1);}
void teleport_timeout_panic_pi(const char *fmt,const char *a0,int a1){panic(fmt,a0,a1);}
void teleport_timeout_panic_piU(const char *fmt,const char *a0,int a1,unsigned long a2){panic(fmt,a0,a1,a2);}
void teleport_timeout_panic_piiiU(const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){panic(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_panic_pp(const char *fmt,const char *a0,const char *a1){panic(fmt,a0,a1);}
void teleport_timeout_panic_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){panic(fmt,a0,a1,a2);}
void teleport_timeout_panic_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){panic(fmt,a0,a1,a2,a3,a4);}
void teleport_timeout_panic_u(const char *fmt,unsigned a0){panic(fmt,a0);}
int teleport_timeout_Sprintf_none(char *out,const char *fmt){return sprintf(out,fmt);}
int teleport_timeout_Sprintf_U(char *out,const char *fmt,unsigned long a0){return sprintf(out,fmt,a0);}
int teleport_timeout_Sprintf_Ui(char *out,const char *fmt,unsigned long a0,int a1){return sprintf(out,fmt,a0,a1);}
int teleport_timeout_Sprintf_Uii(char *out,const char *fmt,unsigned long a0,int a1,int a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_timeout_Sprintf_Uiii(char *out,const char *fmt,unsigned long a0,int a1,int a2,int a3){return sprintf(out,fmt,a0,a1,a2,a3);}
int teleport_timeout_Sprintf_i(char *out,const char *fmt,int a0){return sprintf(out,fmt,a0);}
int teleport_timeout_Sprintf_ipl(char *out,const char *fmt,int a0,const char *a1,long a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_timeout_Sprintf_l(char *out,const char *fmt,long a0){return sprintf(out,fmt,a0);}
int teleport_timeout_Sprintf_llpip(char *out,const char *fmt,long a0,long a1,const char *a2,int a3,const char *a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_timeout_Sprintf_llppp(char *out,const char *fmt,long a0,long a1,const char *a2,const char *a3,const char *a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_timeout_Sprintf_lp(char *out,const char *fmt,long a0,const char *a1){return sprintf(out,fmt,a0,a1);}
int teleport_timeout_Sprintf_p(char *out,const char *fmt,const char *a0){return sprintf(out,fmt,a0);}
int teleport_timeout_Sprintf_pU(char *out,const char *fmt,const char *a0,unsigned long a1){return sprintf(out,fmt,a0,a1);}
int teleport_timeout_Sprintf_pi(char *out,const char *fmt,const char *a0,int a1){return sprintf(out,fmt,a0,a1);}
int teleport_timeout_Sprintf_piU(char *out,const char *fmt,const char *a0,int a1,unsigned long a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_timeout_Sprintf_piiiU(char *out,const char *fmt,const char *a0,int a1,int a2,int a3,unsigned long a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_timeout_Sprintf_pp(char *out,const char *fmt,const char *a0,const char *a1){return sprintf(out,fmt,a0,a1);}
int teleport_timeout_Sprintf_ppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_timeout_Sprintf_ppppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_timeout_Sprintf_u(char *out,const char *fmt,unsigned a0){return sprintf(out,fmt,a0);}
