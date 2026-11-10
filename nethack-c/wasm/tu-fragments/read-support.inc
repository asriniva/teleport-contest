/* READ typed header/field/storage/callback/varargs transport; no scroll policy. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#if !defined(TELEPORT_REFERENCE_TU) && !defined(TELEPORT_READ_LITMON_DEFINED)
#define TELEPORT_READ_LITMON_DEFINED
struct litmon {struct monst *mon;struct litmon *nxt;};
#endif
const void*teleport_read_global(int i){switch(i){case 0:return(const void*)&objects;case 1:return(const void*)&ubirthday;case 2:return(const void*)&gk;case 3:return(const void*)&flags;case 4:return(const void*)&u;case 5:return(const void*)&uarm;case 6:return(const void*)&uarmu;case 7:return(const void*)&gu;case 8:return(const void*)&mons;case 9:return(const void*)&c_common_strings;case 10:return(const void*)&ynchars;case 11:return(const void*)&gy;case 12:return(const void*)&c_color_names;case 13:return(const void*)&uleft;case 14:return(const void*)&uright;case 15:return(const void*)&uball;case 16:return(const void*)&svl;case 17:return(const void*)&gm;case 18:return(const void*)&gv;case 19:return(const void*)&svd;case 20:return(const void*)&uarmc;case 21:return(const void*)&uarmh;case 22:return(const void*)&uarms;case 23:return(const void*)&uarmg;case 24:return(const void*)&uarmf;case 25:return(const void*)&gi;case 26:return(const void*)&uswapwep;case 27:return(const void*)&uquiver;case 28:return(const void*)&uwep;case 29:return(const void*)&svm;case 30:return(const void*)&disp;case 31:return(const void*)&svp;case 32:return(const void*)&iflags;case 33:return(const void*)&a11y;case 34:return(const void*)&genders;case 35:return(const void*)&uchain;case 36:return(const void*)&svr;case 37:return(const void*)&def_monsyms;case 38:return(const void*)&svk;default:return 0;}}
int teleport_read_bit(int kind,const void*p){switch(kind){case 0:return((const struct objclass*)p)->oc_name_known;case 1:return((const struct objclass*)p)->oc_charged;case 2:return((const struct objclass*)p)->oc_dir;case 3:return((const struct objclass*)p)->oc_magic;case 4:return((const struct objclass*)p)->oc_merge;case 5:return((const struct obj*)p)->oeroded;case 6:return((const struct obj*)p)->oeroded2;case 7:return((const struct obj*)p)->pickup_prev;case 8:return((const struct obj*)p)->unpaid;case 9:return((const struct obj*)p)->dknown;case 10:return((const struct obj*)p)->in_use;case 11:return((const struct obj*)p)->cursed;case 12:return((const struct obj*)p)->blessed;case 13:return((const struct obj*)p)->recharged;case 14:return((const struct obj*)p)->lamplit;case 15:return((const struct obj*)p)->oerodeproof;case 16:return((const struct obj*)p)->rknown;case 17:return((const struct obj*)p)->known;case 18:return((const struct obj*)p)->bknown;case 19:return((const struct you*)p)->uswallow;case 20:return((const struct you*)p)->uinwater;case 21:return((const struct you*)p)->mfemale;case 22:return((const struct monst*)p)->meverseen;case 23:return((const struct monst*)p)->mpeaceful;case 24:return((const struct monst*)p)->isshk;case 25:return((const struct monst*)p)->mflee;case 26:return((const struct monst*)p)->mfrozen;case 27:return((const struct monst*)p)->msleeping;case 28:return((const struct monst*)p)->mcanmove;case 29:return((const struct monst*)p)->mcan;case 30:return((const struct monst*)p)->minvis;case 31:return((const struct monst*)p)->mundetected;case 32:return((const struct rm*)p)->lit;case 33:return((const struct rm*)p)->roomno;case 34:return((const struct levelflags*)p)->nommap;default:abort();}}
void teleport_read_set_bit(int kind,void*p,unsigned n){switch(kind){case 0:((struct objclass*)p)->oc_name_known=n;return;case 1:((struct objclass*)p)->oc_charged=n;return;case 2:((struct objclass*)p)->oc_dir=n;return;case 3:((struct objclass*)p)->oc_magic=n;return;case 4:((struct objclass*)p)->oc_merge=n;return;case 5:((struct obj*)p)->oeroded=n;return;case 6:((struct obj*)p)->oeroded2=n;return;case 7:((struct obj*)p)->pickup_prev=n;return;case 8:((struct obj*)p)->unpaid=n;return;case 9:((struct obj*)p)->dknown=n;return;case 10:((struct obj*)p)->in_use=n;return;case 11:((struct obj*)p)->cursed=n;return;case 12:((struct obj*)p)->blessed=n;return;case 13:((struct obj*)p)->recharged=n;return;case 14:((struct obj*)p)->lamplit=n;return;case 15:((struct obj*)p)->oerodeproof=n;return;case 16:((struct obj*)p)->rknown=n;return;case 17:((struct obj*)p)->known=n;return;case 18:((struct obj*)p)->bknown=n;return;case 19:((struct you*)p)->uswallow=n;return;case 20:((struct you*)p)->uinwater=n;return;case 21:((struct you*)p)->mfemale=n;return;case 22:((struct monst*)p)->meverseen=n;return;case 23:((struct monst*)p)->mpeaceful=n;return;case 24:((struct monst*)p)->isshk=n;return;case 25:((struct monst*)p)->mflee=n;return;case 26:((struct monst*)p)->mfrozen=n;return;case 27:((struct monst*)p)->msleeping=n;return;case 28:((struct monst*)p)->mcanmove=n;return;case 29:((struct monst*)p)->mcan=n;return;case 30:((struct monst*)p)->minvis=n;return;case 31:((struct monst*)p)->mundetected=n;return;case 32:((struct rm*)p)->lit=n;return;case 33:((struct rm*)p)->roomno=n;return;case 34:((struct levelflags*)p)->nommap=n;return;default:abort();}}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_read_gremlins gremlins
#else
static struct litmon *teleport_read_gremlins;
#endif
void*teleport_read_data(int i){return i==0?&teleport_read_gremlins:0;}
void teleport_read_rng_source(int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("read.c",line,fn);}
int teleport_read_rn2(int n){return(rn2)(n);}int teleport_read_rnd(int n){return(rnd)(n);}int teleport_read_d(int n,int s){return(d)(n,s);}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_read_callback_can_center_cloud can_center_cloud
#else
extern boolean teleport_read_callback_can_center_cloud(coordxy,coordxy);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_read_callback_display_stinking_cloud_positions display_stinking_cloud_positions
#else
extern void teleport_read_callback_display_stinking_cloud_positions(boolean);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_read_callback_read_ok read_ok
#else
extern int teleport_read_callback_read_ok(struct obj *);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_read_callback_set_lit set_lit
#else
extern void teleport_read_callback_set_lit(coordxy,coordxy,genericptr_t);
#endif
void*teleport_read_callback(int i){switch(i){case 0:return(void*)any_worn_armor_ok;case 1:return(void*)teleport_read_callback_can_center_cloud;case 2:return(void*)charge_ok;case 3:return(void*)teleport_read_callback_display_stinking_cloud_positions;case 4:return(void*)teleport_read_callback_read_ok;case 5:return(void*)teleport_read_callback_set_lit;case 6:return(void*)xname;default:return 0;}}
int teleport_read_v_0(char *restrict a0,const char *restrict a1,const char * a2,const char * a3){return sprintf(a0,a1,a2,a3);}
int teleport_read_v_1(char *restrict a0,const char *restrict a1,const char * a2){return sprintf(a0,a1,a2);}
void teleport_read_v_3(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char * a5){nh_snprintf(a0,a1,a2,a3,a4,a5);}
void teleport_read_v_5(const char * a0,const char * a1,const char * a2,const char * a3){pline(a0,a1,a2,a3);}
void teleport_read_v_6(const char * a0,const char * a1,const char * a2){pline(a0,a1,a2);}
void teleport_read_v_7(const char * a0){pline(a0);}
void teleport_read_v_8(const char * a0,const char * a1){pline(a0,a1);}
void teleport_read_v_9(const char * a0,int a1,int a2,long a3,int a4,int a5,int a6,const char * a7){pline(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_read_v_10(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4){pline(a0,a1,a2,a3,a4);}
void teleport_read_v_11(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4,const char * a5){pline(a0,a1,a2,a3,a4,a5);}
void teleport_read_v_12(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4,const char * a5,const char * a6){pline(a0,a1,a2,a3,a4,a5,a6);}
void teleport_read_v_13(const char * a0,int a1,const char * a2){pline(a0,a1,a2);}
void teleport_read_v_15(const char * a0,const char * a1,const char * a2){pline_The(a0,a1,a2);}
void teleport_read_v_16(const char * a0){pline_The(a0);}
void teleport_read_v_17(const char * a0,const char * a1){pline_The(a0,a1);}
void teleport_read_v_19(const char * a0){urgent_pline(a0);}
void teleport_read_v_21(const char * a0){You(a0);}
void teleport_read_v_22(const char * a0,const char * a1){You(a0,a1);}
void teleport_read_v_23(const char * a0,const char * a1,const char * a2){You(a0,a1,a2);}
void teleport_read_v_25(const char * a0){Your(a0);}
void teleport_read_v_26(const char * a0,const char * a1,const char * a2,const char * a3){Your(a0,a1,a2,a3);}
void teleport_read_v_27(const char * a0,const char * a1,const char * a2){Your(a0,a1,a2);}
void teleport_read_v_28(const char * a0,const char * a1){Your(a0,a1);}
void teleport_read_v_30(const char * a0){You_feel(a0);}
void teleport_read_v_31(const char * a0,const char * a1){You_feel(a0,a1);}
void teleport_read_v_33(const char * a0){You_cant(a0);}
void teleport_read_v_34(const char * a0,const char * a1){You_cant(a0,a1);}
void teleport_read_v_36(const char * a0,const char * a1,const char * a2){You_hear(a0,a1,a2);}
void teleport_read_v_37(const char * a0){You_hear(a0);}
void teleport_read_v_38(const char * a0,const char * a1,const char * a2,const char * a3){You_hear(a0,a1,a2,a3);}
void teleport_read_v_40(const char * a0){verbalize(a0);}
void teleport_read_v_42(const char * a0){impossible(a0);}
void teleport_read_v_43(const char * a0,int a1){impossible(a0,a1);}
void teleport_read_v_45(long a0,const char * a1){livelog_printf(a0,a1);}
void teleport_read_v_46(long a0,const char * a1,const char * a2){livelog_printf(a0,a1,a2);}
void teleport_read_v_47(long a0,const char * a1,const char * a2,int a3){livelog_printf(a0,a1,a2,a3);}
void teleport_read_v_48(long a0,const char * a1,int a2){livelog_printf(a0,a1,a2);}
void teleport_read_v_49(long a0,const char * a1,const char * a2,const char * a3){livelog_printf(a0,a1,a2,a3);}
static char teleport_read_literals[10328];void*teleport_read_literal_storage(void){return teleport_read_literals;}size_t teleport_read_literal_capacity(void){return sizeof teleport_read_literals;}
