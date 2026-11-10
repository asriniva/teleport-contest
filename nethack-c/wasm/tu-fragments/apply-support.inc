/* APPLY typed header/field/storage/callback/varargs transport; no scroll policy. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
const void*teleport_apply_global(int i){switch(i){case 0:return(const void*)&u;case 1:return(const void*)&c_common_strings;case 2:return(const void*)&uwep;case 3:return(const void*)&ublindf;case 4:return(const void*)&uarmg;case 5:return(const void*)&mons;case 6:return(const void*)&genders;case 7:return(const void*)&go;case 8:return(const void*)&svl;case 9:return(const void*)&gu;case 10:return(const void*)&gy;case 11:return(const void*)&gh;case 12:return(const void*)&svc;case 13:return(const void*)&gb;case 14:return(const void*)&gn;case 15:return(const void*)&svd;case 16:return(const void*)&objects;case 17:return(const void*)&defsyms;case 18:return(const void*)&flags;case 19:return(const void*)&svm;case 20:return(const void*)&iflags;case 21:return(const void*)&gi;case 22:return(const void*)&gm;case 23:return(const void*)&gs;case 24:return(const void*)&uchain;case 25:return(const void*)&ynchars;case 26:return(const void*)&gv;case 27:return(const void*)&gj;case 28:return(const void*)&disp;case 29:return(const void*)&hands_obj;case 30:return(const void*)&c_obj_colors;case 31:return(const void*)&gt;case 32:return(const void*)&gp;case 33:return(const void*)&windowprocs;case 34:return(const void*)&cg;case 35:return(const void*)&nul_glyphinfo;case 36:return(const void*)&gc;case 37:return(const void*)&xdir;case 38:return(const void*)&ydir;case 39:return(const void*)&c_color_names;default:return 0;}}
int teleport_apply_bit(int kind,const void*p){switch(kind){case 0:return((const struct you*)p)->uinwater;case 1:return((const struct you*)p)->uswallow;case 2:return((const struct you*)p)->mfemale;case 3:return((const struct obj*)p)->cursed;case 4:return((const struct obj*)p)->dknown;case 5:return((const struct obj*)p)->blessed;case 6:return((const struct obj*)p)->known;case 7:return((const struct obj*)p)->lamplit;case 8:return((const struct obj*)p)->unpaid;case 9:return((const struct obj*)p)->nomerge;case 10:return((const struct obj*)p)->no_charge;case 11:return((const struct obj*)p)->greased;case 12:return((const struct obj*)p)->bknown;case 13:return((const struct monst*)p)->mundetected;case 14:return((const struct monst*)p)->mtrapped;case 15:return((const struct monst*)p)->mleashed;case 16:return((const struct monst*)p)->msleeping;case 17:return((const struct monst*)p)->mcan;case 18:return((const struct monst*)p)->minvis;case 19:return((const struct monst*)p)->mcansee;case 20:return((const struct monst*)p)->mfrozen;case 21:return((const struct monst*)p)->mconf;case 22:return((const struct monst*)p)->wormno;case 23:return((const struct monst*)p)->mpeaceful;case 24:return((const struct trap*)p)->ttyp;case 25:return((const struct trap*)p)->madeby_u;case 26:return((const struct objclass*)p)->oc_name_known;case 27:return((const struct objclass*)p)->oc_material;case 28:return((const struct objclass*)p)->oc_big;case 29:return((const struct objclass*)p)->oc_magic;case 30:return((const struct rm*)p)->flags;case 31:return((const struct rm*)p)->horizontal;case 32:return((const struct rm*)p)->candig;case 33:return((const struct levelflags*)p)->arboreal;default:abort();}}
void teleport_apply_set_bit(int kind,void*p,unsigned n){switch(kind){case 0:((struct you*)p)->uinwater=n;return;case 1:((struct you*)p)->uswallow=n;return;case 2:((struct you*)p)->mfemale=n;return;case 3:((struct obj*)p)->cursed=n;return;case 4:((struct obj*)p)->dknown=n;return;case 5:((struct obj*)p)->blessed=n;return;case 6:((struct obj*)p)->known=n;return;case 7:((struct obj*)p)->lamplit=n;return;case 8:((struct obj*)p)->unpaid=n;return;case 9:((struct obj*)p)->nomerge=n;return;case 10:((struct obj*)p)->no_charge=n;return;case 11:((struct obj*)p)->greased=n;return;case 12:((struct obj*)p)->bknown=n;return;case 13:((struct monst*)p)->mundetected=n;return;case 14:((struct monst*)p)->mtrapped=n;return;case 15:((struct monst*)p)->mleashed=n;return;case 16:((struct monst*)p)->msleeping=n;return;case 17:((struct monst*)p)->mcan=n;return;case 18:((struct monst*)p)->minvis=n;return;case 19:((struct monst*)p)->mcansee=n;return;case 20:((struct monst*)p)->mfrozen=n;return;case 21:((struct monst*)p)->mconf=n;return;case 22:((struct monst*)p)->wormno=n;return;case 23:((struct monst*)p)->mpeaceful=n;return;case 24:((struct trap*)p)->ttyp=n;return;case 25:((struct trap*)p)->madeby_u=n;return;case 26:((struct objclass*)p)->oc_name_known=n;return;case 27:((struct objclass*)p)->oc_material=n;return;case 28:((struct objclass*)p)->oc_big=n;return;case 29:((struct objclass*)p)->oc_magic=n;return;case 30:((struct rm*)p)->flags=n;return;case 31:((struct rm*)p)->horizontal=n;return;case 32:((struct rm*)p)->candig=n;return;case 33:((struct levelflags*)p)->arboreal=n;return;default:abort();}}
void teleport_apply_rng_source(int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("apply.c",line,fn);}
int teleport_apply_rn2(int n){return(rn2)(n);}int teleport_apply_rnd(int n){return(rnd)(n);}int teleport_apply_d(int n,int s){return(d)(n,s);}int teleport_apply_rnl(int n){return(rnl)(n);}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_apply_ok apply_ok
#else
extern int teleport_apply_callback_apply_ok(struct obj *);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_can_grapple_location can_grapple_location
#else
extern boolean teleport_apply_callback_can_grapple_location(coordxy,coordxy);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_check_jump check_jump
#else
extern boolean teleport_apply_callback_check_jump(void *,coordxy,coordxy);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_display_grapple_positions display_grapple_positions
#else
extern void teleport_apply_callback_display_grapple_positions(boolean);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_display_jump_positions display_jump_positions
#else
extern void teleport_apply_callback_display_jump_positions(boolean);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_display_polearm_positions display_polearm_positions
#else
extern void teleport_apply_callback_display_polearm_positions(boolean);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_get_valid_jump_position get_valid_jump_position
#else
extern boolean teleport_apply_callback_get_valid_jump_position(coordxy,coordxy);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_get_valid_polearm_position get_valid_polearm_position
#else
extern boolean teleport_apply_callback_get_valid_polearm_position(coordxy,coordxy);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_grease_ok grease_ok
#else
extern int teleport_apply_callback_grease_ok(struct obj *);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_jelly_ok jelly_ok
#else
extern int teleport_apply_callback_jelly_ok(struct obj *);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_mleashed_next2u mleashed_next2u
#else
extern boolean teleport_apply_callback_mleashed_next2u(struct monst *);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_rub_ok rub_ok
#else
extern int teleport_apply_callback_rub_ok(struct obj *);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_set_trap set_trap
#else
extern int teleport_apply_callback_set_trap(void);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_apply_callback_touchstone_ok touchstone_ok
#else
extern int teleport_apply_callback_touchstone_ok(struct obj *);
#endif
void*teleport_apply_callback(int i){switch(i){case 0:return(void*)any_obj_ok;case 1:return(void*)teleport_apply_callback_apply_ok;case 2:return(void*)bhito;case 3:return(void*)teleport_apply_callback_can_grapple_location;case 4:return(void*)teleport_apply_callback_check_jump;case 5:return(void*)teleport_apply_callback_display_grapple_positions;case 6:return(void*)teleport_apply_callback_display_jump_positions;case 7:return(void*)teleport_apply_callback_display_polearm_positions;case 8:return(void*)doapply;case 9:return(void*)dorub;case 10:return(void*)teleport_apply_callback_get_valid_jump_position;case 11:return(void*)teleport_apply_callback_get_valid_polearm_position;case 12:return(void*)teleport_apply_callback_grease_ok;case 13:return(void*)hurtle_jump;case 14:return(void*)teleport_apply_callback_jelly_ok;case 15:return(void*)teleport_apply_callback_mleashed_next2u;case 16:return(void*)teleport_apply_callback_rub_ok;case 17:return(void*)teleport_apply_callback_set_trap;case 18:return(void*)thesimpleoname;case 19:return(void*)teleport_apply_callback_touchstone_ok;case 20:return(void*)xname;case 21:return(void*)yname;case 22:return(void*)ysimple_name;default:return 0;}}
winid teleport_apply_window_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_apply_window_start_menu(winid a0,unsigned long a1){start_menu(a0,a1);}
void teleport_apply_window_end_menu(winid a0,const char * a1){end_menu(a0,a1);}
void teleport_apply_window_destroy_nhwindow(winid a0){destroy_nhwindow(a0);}
int teleport_apply_v_0(char *restrict a0,const char *restrict a1,const char * a2){return sprintf(a0,a1,a2);}
int teleport_apply_v_1(char *restrict a0,const char *restrict a1,const char * a2,const char * a3){return sprintf(a0,a1,a2,a3);}
void teleport_apply_v_3(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char * a5,const char * a6){nh_snprintf(a0,a1,a2,a3,a4,a5,a6);}
void teleport_apply_v_5(const char * a0){pline(a0);}
void teleport_apply_v_6(const char * a0,const char * a1){pline(a0,a1);}
void teleport_apply_v_7(const char * a0,const char * a1,const char * a2){pline(a0,a1,a2);}
void teleport_apply_v_8(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4){pline(a0,a1,a2,a3,a4);}
void teleport_apply_v_9(const char * a0,const char * a1,const char * a2,const char * a3){pline(a0,a1,a2,a3);}
void teleport_apply_v_10(const char * a0,const char * a1,const char * a2,const char * a3,int a4){pline(a0,a1,a2,a3,a4);}
void teleport_apply_v_12(struct monst * a0,const char * a1,const char * a2,const char * a3,const char * a4){pline_mon(a0,a1,a2,a3,a4);}
void teleport_apply_v_13(struct monst * a0,const char * a1,const char * a2,const char * a3){pline_mon(a0,a1,a2,a3);}
void teleport_apply_v_15(const char * a0,const char * a1,const char * a2){You(a0,a1,a2);}
void teleport_apply_v_16(const char * a0,const char * a1){You(a0,a1);}
void teleport_apply_v_17(const char * a0){You(a0);}
void teleport_apply_v_18(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4){You(a0,a1,a2,a3,a4);}
void teleport_apply_v_19(const char * a0,long a1,const char * a2,const char * a3,const char * a4){You(a0,a1,a2,a3,a4);}
void teleport_apply_v_20(const char * a0,const char * a1,const char * a2,const char * a3){You(a0,a1,a2,a3);}
void teleport_apply_v_22(const char * a0,const char * a1,const char * a2){Your(a0,a1,a2);}
void teleport_apply_v_23(const char * a0,const char * a1){Your(a0,a1);}
void teleport_apply_v_24(const char * a0){Your(a0);}
void teleport_apply_v_26(const char * a0,const char * a1){You_feel(a0,a1);}
void teleport_apply_v_27(const char * a0){You_feel(a0);}
void teleport_apply_v_28(const char * a0,const char * a1,const char * a2){You_feel(a0,a1,a2);}
void teleport_apply_v_30(const char * a0){You_cant(a0);}
void teleport_apply_v_31(const char * a0,const char * a1){You_cant(a0,a1);}
void teleport_apply_v_32(const char * a0,const char * a1,const char * a2){You_cant(a0,a1,a2);}
void teleport_apply_v_34(const char * a0,const char * a1){You_hear(a0,a1);}
void teleport_apply_v_35(const char * a0){You_hear(a0);}
void teleport_apply_v_37(const char * a0,const char * a1,const char * a2,const char * a3){You_see(a0,a1,a2,a3);}
void teleport_apply_v_38(const char * a0,const char * a1,const char * a2){You_see(a0,a1,a2);}
void teleport_apply_v_39(const char * a0,const char * a1,const char * a2,const char * a3,const char * a4){You_see(a0,a1,a2,a3,a4);}
void teleport_apply_v_40(const char * a0,const char * a1){You_see(a0,a1);}
void teleport_apply_v_42(const char * a0,const char * a1){pline_The(a0,a1);}
void teleport_apply_v_43(const char * a0){pline_The(a0);}
void teleport_apply_v_44(const char * a0,const char * a1,const char * a2,const char * a3){pline_The(a0,a1,a2,a3);}
void teleport_apply_v_45(const char * a0,const char * a1,const char * a2){pline_The(a0,a1,a2);}
void teleport_apply_v_47(const char * a0,const char * a1){There(a0,a1);}
void teleport_apply_v_48(const char * a0){There(a0);}
void teleport_apply_v_49(const char * a0,const char * a1,int a2,const char * a3,const char * a4){There(a0,a1,a2,a3,a4);}
void teleport_apply_v_51(const char * a0,const char * a1,const char * a2,const char * a3){verbalize(a0,a1,a2,a3);}
void teleport_apply_v_52(const char * a0,const char * a1,const char * a2){verbalize(a0,a1,a2);}
void teleport_apply_v_53(const char * a0){verbalize(a0);}
void teleport_apply_v_55(const char * a0){impossible(a0);}
void teleport_apply_v_56(const char * a0,int a1){impossible(a0,a1);}
static char teleport_apply_literals[11516];void*teleport_apply_literal_storage(void){return teleport_apply_literals;}size_t teleport_apply_literal_capacity(void){return sizeof teleport_apply_literals;}
