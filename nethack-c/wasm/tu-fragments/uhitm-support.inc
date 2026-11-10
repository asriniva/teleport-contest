/* UHITM typed header/field/storage/callback/varargs transport; no combat policy. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
static unsigned char teleport_uhitm_persistent_bytes[267];void*teleport_uhitm_persistent(int i){return teleport_uhitm_persistent_bytes+(i==0?0:i==1?1:257); }
const void*teleport_uhitm_global(int i){switch(i){case 0:return(const void*)&gy;case 1:return(const void*)&gv;case 2:return(const void*)&gm;case 3:return(const void*)&u;case 4:return(const void*)&svc;case 5:return(const void*)&gb;case 6:return(const void*)&c_common_strings;case 7:return(const void*)&svl;case 8:return(const void*)&flags;case 9:return(const void*)&go;case 10:return(const void*)&gu;case 11:return(const void*)&uarm;case 12:return(const void*)&uwep;case 13:return(const void*)&uarms;case 14:return(const void*)&uball;case 15:return(const void*)&mons;case 16:return(const void*)&svr;case 17:return(const void*)&gn;case 18:return(const void*)&uarmg;case 19:return(const void*)&objects;case 20:return(const void*)&xdir;case 21:return(const void*)&ydir;case 22:return(const void*)&uswapwep;case 23:return(const void*)&gt;case 24:return(const void*)&svm;case 25:return(const void*)&genders;case 26:return(const void*)&gi;case 27:return(const void*)&gs;case 28:return(const void*)&uarmh;case 29:return(const void*)&svd;case 30:return(const void*)&svk;case 31:return(const void*)&uright;case 32:return(const void*)&uleft;case 33:return(const void*)&uamul;case 34:return(const void*)&ublindf;case 35:return(const void*)&disp;case 36:return(const void*)&uarmu;case 37:return(const void*)&uarmc;case 38:return(const void*)&uarmf;case 39:return(const void*)&sysopt;case 40:return(const void*)&windowprocs;case 41:return(const void*)&gc;case 42:return(const void*)&ga;case 43:return(const void*)&defsyms;case 44:return(const void*)&c_color_names;case 45:return(const void*)&WIN_MESSAGE;default:return 0;}}
int teleport_uhitm_bit(int kind,const void*p){switch(kind){case 0:return((const struct monst*)p)->mcan;case 1:return((const struct monst*)p)->mundetected;case 2:return((const struct monst*)p)->mflee;case 3:return((const struct monst*)p)->msleeping;case 4:return((const struct monst*)p)->mpeaceful;case 5:return((const struct monst*)p)->mcanmove;case 6:return((const struct monst*)p)->mavenge;case 7:return((const struct monst*)p)->mfrozen;case 8:return((const struct monst*)p)->mstun;case 9:return((const struct monst*)p)->wormno;case 10:return((const struct monst*)p)->isshk;case 11:return((const struct monst*)p)->mconf;case 12:return((const struct monst*)p)->mcansee;case 13:return((const struct monst*)p)->ispriest;case 14:return((const struct monst*)p)->mblinded;case 15:return((const struct monst*)p)->mspeed;case 16:return((const struct monst*)p)->isminion;case 17:return((const struct monst*)p)->female;case 18:return((const struct monst*)p)->minvis;case 19:return((const struct you*)p)->uswallow;case 20:return((const struct you*)p)->uinwater;case 21:return((const struct you*)p)->mfemale;case 22:return((const struct rm*)p)->lit;case 23:return((const struct obj*)p)->oeroded;case 24:return((const struct obj*)p)->oeroded2;case 25:return((const struct obj*)p)->lamplit;case 26:return((const struct obj*)p)->otrapped;case 27:return((const struct obj*)p)->dknown;case 28:return((const struct obj*)p)->known;case 29:return((const struct obj*)p)->bknown;case 30:return((const struct obj*)p)->blessed;case 31:return((const struct obj*)p)->cursed;case 32:return((const struct obj*)p)->greased;case 33:return((const struct objclass*)p)->oc_big;case 34:return((const struct objclass*)p)->oc_material;case 35:return((const struct objclass*)p)->oc_name_known;case 36:return((const struct objclass*)p)->oc_dir;default:abort();}}
void teleport_uhitm_set_bit(int kind,void*p,unsigned n){switch(kind){case 0:((struct monst*)p)->mcan=n;return;case 1:((struct monst*)p)->mundetected=n;return;case 2:((struct monst*)p)->mflee=n;return;case 3:((struct monst*)p)->msleeping=n;return;case 4:((struct monst*)p)->mpeaceful=n;return;case 5:((struct monst*)p)->mcanmove=n;return;case 6:((struct monst*)p)->mavenge=n;return;case 7:((struct monst*)p)->mfrozen=n;return;case 8:((struct monst*)p)->mstun=n;return;case 9:((struct monst*)p)->wormno=n;return;case 10:((struct monst*)p)->isshk=n;return;case 11:((struct monst*)p)->mconf=n;return;case 12:((struct monst*)p)->mcansee=n;return;case 13:((struct monst*)p)->ispriest=n;return;case 14:((struct monst*)p)->mblinded=n;return;case 15:((struct monst*)p)->mspeed=n;return;case 16:((struct monst*)p)->isminion=n;return;case 17:((struct monst*)p)->female=n;return;case 18:((struct monst*)p)->minvis=n;return;case 19:((struct you*)p)->uswallow=n;return;case 20:((struct you*)p)->uinwater=n;return;case 21:((struct you*)p)->mfemale=n;return;case 22:((struct rm*)p)->lit=n;return;case 23:((struct obj*)p)->oeroded=n;return;case 24:((struct obj*)p)->oeroded2=n;return;case 25:((struct obj*)p)->lamplit=n;return;case 26:((struct obj*)p)->otrapped=n;return;case 27:((struct obj*)p)->dknown=n;return;case 28:((struct obj*)p)->known=n;return;case 29:((struct obj*)p)->bknown=n;return;case 30:((struct obj*)p)->blessed=n;return;case 31:((struct obj*)p)->cursed=n;return;case 32:((struct obj*)p)->greased=n;return;case 33:((struct objclass*)p)->oc_big=n;return;case 34:((struct objclass*)p)->oc_material=n;return;case 35:((struct objclass*)p)->oc_name_known=n;return;case 36:((struct objclass*)p)->oc_dir=n;return;default:abort();}}
void teleport_uhitm_rng_source(int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("uhitm.c",line,fn);}
int teleport_uhitm_rn2(int n){return(rn2)(n);}int teleport_uhitm_rnd(int n){return(rnd)(n);}int teleport_uhitm_d(int n,int s){return(d)(n,s);}int teleport_uhitm_rnl(int n){return(rnl)(n);}
void*teleport_uhitm_callback(int i){switch(i){case 0:return(void*)Finish_digestion;case 1:return(void*)rn2_on_display_rng;case 2:return(void*)xname;default:return 0;}}
void teleport_uhitm_window_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
void teleport_uhitm_window_nh_delay_output(){nh_delay_output();}
int teleport_uhitm_v_0(char *restrict a0,const char *restrict a1,int a2){return sprintf(a0,a1,a2);}
int teleport_uhitm_v_1(char *restrict a0,const char *restrict a1,const char * a2,const char * a3,const char * a4){return sprintf(a0,a1,a2,a3,a4);}
int teleport_uhitm_v_2(char *restrict a0,const char *restrict a1,const char * a2){return sprintf(a0,a1,a2);}
int teleport_uhitm_v_3(char *restrict a0,const char *restrict a1,const char * a2,const char * a3){return sprintf(a0,a1,a2,a3);}
void teleport_uhitm_v_5(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char * a5,const char * a6,const char * a7){nh_snprintf(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_uhitm_v_6(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char * a5){nh_snprintf(a0,a1,a2,a3,a4,a5);}
void teleport_uhitm_v_8(const char * a0){panic(a0);}
void teleport_uhitm_v_10(const char * a0,const char * a1){pline(a0,a1);}
void teleport_uhitm_v_11(const char * a0,const char * a1,const char * a2,const char * a3){pline(a0,a1,a2,a3);}
void teleport_uhitm_v_12(const char * a0){pline(a0);}
void teleport_uhitm_v_13(const char * a0,const char * a1,const char * a2){pline(a0,a1,a2);}
void teleport_uhitm_v_14(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4){pline(a0,a1,a2,a3,a4);}
void teleport_uhitm_v_15(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4,const char * a5){pline(a0,a1,a2,a3,a4,a5);}
void teleport_uhitm_v_16(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4,const char * a5,const char * a6){pline(a0,a1,a2,a3,a4,a5,a6);}
void teleport_uhitm_v_17(const char * a0,const char * a1,const char * a2,int a3){pline(a0,a1,a2,a3);}
void teleport_uhitm_v_19(struct monst * a0,const char * a1,const char * a2){pline_mon(a0,a1,a2);}
void teleport_uhitm_v_20(struct monst * a0,const char * a1,const char * a2,const char * a3){pline_mon(a0,a1,a2,a3);}
void teleport_uhitm_v_21(struct monst * a0,const char * a1,const char * a2,const char * a3,const char * a4){pline_mon(a0,a1,a2,a3,a4);}
void teleport_uhitm_v_23(const char * a0,const char * a1,const char * a2){urgent_pline(a0,a1,a2);}
void teleport_uhitm_v_24(const char * a0,const char * a1){urgent_pline(a0,a1);}
void teleport_uhitm_v_25(const char * a0){urgent_pline(a0);}
void teleport_uhitm_v_27(const char * a0){You(a0);}
void teleport_uhitm_v_28(const char * a0,const char * a1){You(a0,a1);}
void teleport_uhitm_v_29(const char * a0,const char * a1,const char * a2,const char * a3){You(a0,a1,a2,a3);}
void teleport_uhitm_v_30(const char * a0,const char * a1,const char * a2){You(a0,a1,a2);}
void teleport_uhitm_v_31(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4){You(a0,a1,a2,a3,a4);}
void teleport_uhitm_v_33(const char * a0){Your(a0);}
void teleport_uhitm_v_34(const char * a0,const char * a1){Your(a0,a1);}
void teleport_uhitm_v_35(const char * a0,const char * a1,const char * a2){Your(a0,a1,a2);}
void teleport_uhitm_v_36(const char * a0,const char * a1,const char * a2,const char * a3){Your(a0,a1,a2,a3);}
void teleport_uhitm_v_38(const char * a0){You_feel(a0);}
void teleport_uhitm_v_39(const char * a0,const char * a1,const char * a2){You_feel(a0,a1,a2);}
void teleport_uhitm_v_40(const char * a0,const char * a1){You_feel(a0,a1);}
void teleport_uhitm_v_42(const char * a0){You_hear(a0);}
void teleport_uhitm_v_43(const char * a0,const char * a1){You_hear(a0,a1);}
void teleport_uhitm_v_45(const char * a0,const char * a1,const char * a2){pline_The(a0,a1,a2);}
void teleport_uhitm_v_46(const char * a0,const char * a1){pline_The(a0,a1);}
void teleport_uhitm_v_47(const char * a0){pline_The(a0);}
void teleport_uhitm_v_49(const char * a0){verbalize(a0);}
void teleport_uhitm_v_51(long a0,const char * a1,const char * a2){livelog_printf(a0,a1,a2);}
void teleport_uhitm_v_53(const char * a0,int a1,int a2,int a3){impossible(a0,a1,a2,a3);}
void teleport_uhitm_v_54(const char * a0){impossible(a0);}
void teleport_uhitm_v_55(const char * a0,int a1){impossible(a0,a1);}
static char teleport_uhitm_literals[9293];void*teleport_uhitm_literal_storage(void){return teleport_uhitm_literals;}size_t teleport_uhitm_literal_capacity(void){return sizeof teleport_uhitm_literals;}
