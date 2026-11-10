/* INSIGHT native ABI only: zero storage, packed fields and existing calls. */
#include "hack.h"
#include <stdlib.h>
#include <stdint.h>
extern const char *const hu_stat[];extern const char *const enc_stat[];extern const char *const attrname[];
extern const char *const vanqorders[NUM_VANQ_ORDER_MODES][3];
#ifndef TELEPORT_REFERENCE_INSIGHT
const char *const vanqorders[NUM_VANQ_ORDER_MODES][3]={{0}};
#endif
static char insight_sizebuf[40],insight_piousbuf[32],insight_punctclasses[7];
void *teleport_insight_storage(int i){switch(i){case 0:return(void*)vanqorders;case 1:return insight_sizebuf;case 2:return insight_piousbuf;case 3:return insight_punctclasses;default:return 0;}}
const void *teleport_insight_global(int i){switch(i){case 0:return &ge;case 1:return &flags;case 2:return &u;case 3:return &svd;case 4:return &gi;case 5:return &objects;case 6:return &urealtime;case 7:return &svp;case 8:return &gu;case 9:return &gy;case 10:return &genders;case 11:return &mons;case 12:return &svm;case 13:return &iflags;case 14:return &ga;case 15:return &uleft;case 16:return &uright;case 17:return &uarmg;case 18:return &uwep;case 19:return &uarmh;case 20:return &svk;case 21:return &uball;case 22:return &hu_stat;case 23:return &enc_stat;case 24:return &uarm;case 25:return &uarmu;case 26:return &uarmc;case 27:return &uarms;case 28:return &uarmf;case 29:return &uswapwep;case 30:return &svc;case 31:return &c_common_strings;case 32:return &uamul;case 33:return &ublindf;case 34:return &svs;case 35:return &gf;case 36:return &svl;case 37:return &program_state;case 38:return &obj_descr;case 39:return &gg;case 40:return &cg;case 41:return &nul_glyphinfo;case 42:return &ynaqchars;case 43:return &ynqchars;case 44:return &def_monsyms;case 45:return &gb;case 46:return &attrname;default:return 0;}}
unsigned teleport_insight_get_bit(const void*p,int i){switch(i){case 0:return((const struct you*)p)->uinwater;case 1:return((const struct you*)p)->mfemale;case 2:return((const struct you*)p)->uhandedness;case 3:return((const struct you*)p)->uundetected;case 4:return((const struct you*)p)->uburied;case 5:return((const struct you*)p)->usick_type;case 6:return((const struct you*)p)->uswallow;case 7:return((const struct you*)p)->uedibility;case 8:return((const struct monst*)p)->isminion;case 9:return((const struct monst*)p)->mpeaceful;case 10:return((const struct monst*)p)->mundetected;case 11:return((const struct monst*)p)->mcan;case 12:return((const struct monst*)p)->mconf;case 13:return((const struct monst*)p)->mblinded;case 14:return((const struct monst*)p)->mcansee;case 15:return((const struct monst*)p)->mstun;case 16:return((const struct monst*)p)->msleeping;case 17:return((const struct monst*)p)->mfrozen;case 18:return((const struct monst*)p)->mcanmove;case 19:return((const struct monst*)p)->mflee;case 20:return((const struct monst*)p)->mtrapped;case 21:return((const struct monst*)p)->mspeed;case 22:return((const struct monst*)p)->minvis;case 23:return((const struct monst*)p)->mleashed;case 24:return((const struct trap*)p)->ttyp;case 25:return((const struct obj*)p)->dknown;case 26:return((const struct obj*)p)->cursed;case 27:return((const struct objclass*)p)->oc_name_known;case 28:return((const struct objclass*)p)->oc_material;case 29:return((const struct u_event*)p)->uhand_of_elbereth;case 30:return((const struct u_event*)p)->ascended;case 31:return((const struct u_have*)p)->bell;case 32:return((const struct u_have*)p)->menorah;case 33:return((const struct u_have*)p)->book;case 34:return((const struct u_have*)p)->amulet;default:return 0;}}
void teleport_insight_set_bit(void*p,int i,unsigned v){switch(i){case 0:((struct you*)p)->uinwater=v;break;case 1:((struct you*)p)->mfemale=v;break;case 2:((struct you*)p)->uhandedness=v;break;case 3:((struct you*)p)->uundetected=v;break;case 4:((struct you*)p)->uburied=v;break;case 5:((struct you*)p)->usick_type=v;break;case 6:((struct you*)p)->uswallow=v;break;case 7:((struct you*)p)->uedibility=v;break;case 8:((struct monst*)p)->isminion=v;break;case 9:((struct monst*)p)->mpeaceful=v;break;case 10:((struct monst*)p)->mundetected=v;break;case 11:((struct monst*)p)->mcan=v;break;case 12:((struct monst*)p)->mconf=v;break;case 13:((struct monst*)p)->mblinded=v;break;case 14:((struct monst*)p)->mcansee=v;break;case 15:((struct monst*)p)->mstun=v;break;case 16:((struct monst*)p)->msleeping=v;break;case 17:((struct monst*)p)->mfrozen=v;break;case 18:((struct monst*)p)->mcanmove=v;break;case 19:((struct monst*)p)->mflee=v;break;case 20:((struct monst*)p)->mtrapped=v;break;case 21:((struct monst*)p)->mspeed=v;break;case 22:((struct monst*)p)->minvis=v;break;case 23:((struct monst*)p)->mleashed=v;break;case 24:((struct trap*)p)->ttyp=v;break;case 25:((struct obj*)p)->dknown=v;break;case 26:((struct obj*)p)->cursed=v;break;case 27:((struct objclass*)p)->oc_name_known=v;break;case 28:((struct objclass*)p)->oc_material=v;break;case 29:((struct u_event*)p)->uhand_of_elbereth=v;break;case 30:((struct u_event*)p)->ascended=v;break;case 31:((struct u_have*)p)->bell=v;break;case 32:((struct u_have*)p)->menorah=v;break;case 33:((struct u_have*)p)->book=v;break;case 34:((struct u_have*)p)->amulet=v;break;}}
static char insight_literals[TELEPORT_INSIGHT_LITERAL_CAPACITY+sizeof "%s"+sizeof "s"];
void *teleport_insight_literal_storage(void){return insight_literals;}
size_t teleport_insight_literal_capacity(void){return sizeof insight_literals;}
void teleport_insight_free(void*p){free(p);}
winid teleport_insight_create(int type){return create_nhwindow(type);}
void teleport_insight_start(winid w,unsigned long f){start_menu(w,f);}
void teleport_insight_end(winid w,const char*s){end_menu(w,s);}
void teleport_insight_destroy(winid w){destroy_nhwindow(w);}
void teleport_insight_display(winid w,boolean b){display_nhwindow(w,b);}
void teleport_insight_putstr(winid w,int a,const char*s){putstr(w,a,s);}
void teleport_insight_putmixed(winid w,int a,const char*s){putmixed(w,a,s);}
void teleport_insight_raw_print(const char*s){raw_print(s);}
void teleport_insight_assertion(int i){(void)i;__assert_fail(TELEPORT_INSIGHT_ASSERT_CONDITION,"insight.c",TELEPORT_INSIGHT_ASSERT_LINE,TELEPORT_INSIGHT_ASSERT_FUNCTION);}
extern int teleport_insight_callback_vanqsort_cmp(const void*,const void*);
static int insight_comparator(const void*a,const void*b){return teleport_insight_callback_vanqsort_cmp(a,b);}
void teleport_insight_qsort(void*p,size_t n,size_t z){qsort(p,n,z,insight_comparator);}
void teleport_insight_livelog_p(long f,const char*fmt,const char*a){livelog_printf(f,fmt,a);}
void teleport_insight_livelog_pp(long f,const char*fmt,const char*a,const char*b){livelog_printf(f,fmt,a,b);}
void teleport_insight_livelog_pi(long f,const char*fmt,const char*a,int b){livelog_printf(f,fmt,a,b);}
void teleport_insight_pline_none(const char *fmt){pline(fmt);}
void teleport_insight_pline_i(const char *fmt,int a0){pline(fmt,a0);}
void teleport_insight_pline_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){pline(fmt,a0,a1,a2,a3);}
void teleport_insight_pline_iip(const char *fmt,int a0,int a1,const char *a2){pline(fmt,a0,a1,a2);}
void teleport_insight_pline_ip(const char *fmt,int a0,const char *a1){pline(fmt,a0,a1);}
void teleport_insight_pline_ipi(const char *fmt,int a0,const char *a1,int a2){pline(fmt,a0,a1,a2);}
void teleport_insight_pline_ipp(const char *fmt,int a0,const char *a1,const char *a2){pline(fmt,a0,a1,a2);}
void teleport_insight_pline_l(const char *fmt,long a0){pline(fmt,a0);}
void teleport_insight_pline_li(const char *fmt,long a0,int a1){pline(fmt,a0,a1);}
void teleport_insight_pline_lp(const char *fmt,long a0,const char *a1){pline(fmt,a0,a1);}
void teleport_insight_pline_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){pline(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_pline_p(const char *fmt,const char *a0){pline(fmt,a0);}
void teleport_insight_pline_pi(const char *fmt,const char *a0,int a1){pline(fmt,a0,a1);}
void teleport_insight_pline_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){pline(fmt,a0,a1,a2,a3);}
void teleport_insight_pline_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){pline(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_pline_plp(const char *fmt,const char *a0,long a1,const char *a2){pline(fmt,a0,a1,a2);}
void teleport_insight_pline_pp(const char *fmt,const char *a0,const char *a1){pline(fmt,a0,a1);}
void teleport_insight_pline_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){pline(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_pline_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){pline(fmt,a0,a1,a2);}
void teleport_insight_pline_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){pline(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_pline_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){pline(fmt,a0,a1,a2,a3);}
void teleport_insight_pline_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){pline(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_pline_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){pline(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_pline_u(const char *fmt,unsigned a0){pline(fmt,a0);}
void teleport_insight_Norep_none(const char *fmt){Norep(fmt);}
void teleport_insight_Norep_i(const char *fmt,int a0){Norep(fmt,a0);}
void teleport_insight_Norep_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){Norep(fmt,a0,a1,a2,a3);}
void teleport_insight_Norep_iip(const char *fmt,int a0,int a1,const char *a2){Norep(fmt,a0,a1,a2);}
void teleport_insight_Norep_ip(const char *fmt,int a0,const char *a1){Norep(fmt,a0,a1);}
void teleport_insight_Norep_ipi(const char *fmt,int a0,const char *a1,int a2){Norep(fmt,a0,a1,a2);}
void teleport_insight_Norep_ipp(const char *fmt,int a0,const char *a1,const char *a2){Norep(fmt,a0,a1,a2);}
void teleport_insight_Norep_l(const char *fmt,long a0){Norep(fmt,a0);}
void teleport_insight_Norep_li(const char *fmt,long a0,int a1){Norep(fmt,a0,a1);}
void teleport_insight_Norep_lp(const char *fmt,long a0,const char *a1){Norep(fmt,a0,a1);}
void teleport_insight_Norep_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){Norep(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_Norep_p(const char *fmt,const char *a0){Norep(fmt,a0);}
void teleport_insight_Norep_pi(const char *fmt,const char *a0,int a1){Norep(fmt,a0,a1);}
void teleport_insight_Norep_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){Norep(fmt,a0,a1,a2,a3);}
void teleport_insight_Norep_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){Norep(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_Norep_plp(const char *fmt,const char *a0,long a1,const char *a2){Norep(fmt,a0,a1,a2);}
void teleport_insight_Norep_pp(const char *fmt,const char *a0,const char *a1){Norep(fmt,a0,a1);}
void teleport_insight_Norep_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){Norep(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_Norep_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){Norep(fmt,a0,a1,a2);}
void teleport_insight_Norep_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){Norep(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_Norep_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){Norep(fmt,a0,a1,a2,a3);}
void teleport_insight_Norep_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){Norep(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_Norep_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){Norep(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_Norep_u(const char *fmt,unsigned a0){Norep(fmt,a0);}
void teleport_insight_You_none(const char *fmt){You(fmt);}
void teleport_insight_You_i(const char *fmt,int a0){You(fmt,a0);}
void teleport_insight_You_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){You(fmt,a0,a1,a2,a3);}
void teleport_insight_You_iip(const char *fmt,int a0,int a1,const char *a2){You(fmt,a0,a1,a2);}
void teleport_insight_You_ip(const char *fmt,int a0,const char *a1){You(fmt,a0,a1);}
void teleport_insight_You_ipi(const char *fmt,int a0,const char *a1,int a2){You(fmt,a0,a1,a2);}
void teleport_insight_You_ipp(const char *fmt,int a0,const char *a1,const char *a2){You(fmt,a0,a1,a2);}
void teleport_insight_You_l(const char *fmt,long a0){You(fmt,a0);}
void teleport_insight_You_li(const char *fmt,long a0,int a1){You(fmt,a0,a1);}
void teleport_insight_You_lp(const char *fmt,long a0,const char *a1){You(fmt,a0,a1);}
void teleport_insight_You_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){You(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_p(const char *fmt,const char *a0){You(fmt,a0);}
void teleport_insight_You_pi(const char *fmt,const char *a0,int a1){You(fmt,a0,a1);}
void teleport_insight_You_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){You(fmt,a0,a1,a2,a3);}
void teleport_insight_You_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){You(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_plp(const char *fmt,const char *a0,long a1,const char *a2){You(fmt,a0,a1,a2);}
void teleport_insight_You_pp(const char *fmt,const char *a0,const char *a1){You(fmt,a0,a1);}
void teleport_insight_You_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){You(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_You_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You(fmt,a0,a1,a2);}
void teleport_insight_You_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){You(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_You_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){You(fmt,a0,a1,a2,a3);}
void teleport_insight_You_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){You(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_You_u(const char *fmt,unsigned a0){You(fmt,a0);}
void teleport_insight_Your_none(const char *fmt){Your(fmt);}
void teleport_insight_Your_i(const char *fmt,int a0){Your(fmt,a0);}
void teleport_insight_Your_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){Your(fmt,a0,a1,a2,a3);}
void teleport_insight_Your_iip(const char *fmt,int a0,int a1,const char *a2){Your(fmt,a0,a1,a2);}
void teleport_insight_Your_ip(const char *fmt,int a0,const char *a1){Your(fmt,a0,a1);}
void teleport_insight_Your_ipi(const char *fmt,int a0,const char *a1,int a2){Your(fmt,a0,a1,a2);}
void teleport_insight_Your_ipp(const char *fmt,int a0,const char *a1,const char *a2){Your(fmt,a0,a1,a2);}
void teleport_insight_Your_l(const char *fmt,long a0){Your(fmt,a0);}
void teleport_insight_Your_li(const char *fmt,long a0,int a1){Your(fmt,a0,a1);}
void teleport_insight_Your_lp(const char *fmt,long a0,const char *a1){Your(fmt,a0,a1);}
void teleport_insight_Your_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){Your(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_Your_p(const char *fmt,const char *a0){Your(fmt,a0);}
void teleport_insight_Your_pi(const char *fmt,const char *a0,int a1){Your(fmt,a0,a1);}
void teleport_insight_Your_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){Your(fmt,a0,a1,a2,a3);}
void teleport_insight_Your_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){Your(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_Your_plp(const char *fmt,const char *a0,long a1,const char *a2){Your(fmt,a0,a1,a2);}
void teleport_insight_Your_pp(const char *fmt,const char *a0,const char *a1){Your(fmt,a0,a1);}
void teleport_insight_Your_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){Your(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_Your_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){Your(fmt,a0,a1,a2);}
void teleport_insight_Your_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){Your(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_Your_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){Your(fmt,a0,a1,a2,a3);}
void teleport_insight_Your_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){Your(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_Your_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){Your(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_Your_u(const char *fmt,unsigned a0){Your(fmt,a0);}
void teleport_insight_You_feel_none(const char *fmt){You_feel(fmt);}
void teleport_insight_You_feel_i(const char *fmt,int a0){You_feel(fmt,a0);}
void teleport_insight_You_feel_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){You_feel(fmt,a0,a1,a2,a3);}
void teleport_insight_You_feel_iip(const char *fmt,int a0,int a1,const char *a2){You_feel(fmt,a0,a1,a2);}
void teleport_insight_You_feel_ip(const char *fmt,int a0,const char *a1){You_feel(fmt,a0,a1);}
void teleport_insight_You_feel_ipi(const char *fmt,int a0,const char *a1,int a2){You_feel(fmt,a0,a1,a2);}
void teleport_insight_You_feel_ipp(const char *fmt,int a0,const char *a1,const char *a2){You_feel(fmt,a0,a1,a2);}
void teleport_insight_You_feel_l(const char *fmt,long a0){You_feel(fmt,a0);}
void teleport_insight_You_feel_li(const char *fmt,long a0,int a1){You_feel(fmt,a0,a1);}
void teleport_insight_You_feel_lp(const char *fmt,long a0,const char *a1){You_feel(fmt,a0,a1);}
void teleport_insight_You_feel_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){You_feel(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_feel_p(const char *fmt,const char *a0){You_feel(fmt,a0);}
void teleport_insight_You_feel_pi(const char *fmt,const char *a0,int a1){You_feel(fmt,a0,a1);}
void teleport_insight_You_feel_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){You_feel(fmt,a0,a1,a2,a3);}
void teleport_insight_You_feel_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){You_feel(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_feel_plp(const char *fmt,const char *a0,long a1,const char *a2){You_feel(fmt,a0,a1,a2);}
void teleport_insight_You_feel_pp(const char *fmt,const char *a0,const char *a1){You_feel(fmt,a0,a1);}
void teleport_insight_You_feel_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){You_feel(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_You_feel_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You_feel(fmt,a0,a1,a2);}
void teleport_insight_You_feel_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){You_feel(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_You_feel_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){You_feel(fmt,a0,a1,a2,a3);}
void teleport_insight_You_feel_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You_feel(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_feel_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){You_feel(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_You_feel_u(const char *fmt,unsigned a0){You_feel(fmt,a0);}
void teleport_insight_You_hear_none(const char *fmt){You_hear(fmt);}
void teleport_insight_You_hear_i(const char *fmt,int a0){You_hear(fmt,a0);}
void teleport_insight_You_hear_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){You_hear(fmt,a0,a1,a2,a3);}
void teleport_insight_You_hear_iip(const char *fmt,int a0,int a1,const char *a2){You_hear(fmt,a0,a1,a2);}
void teleport_insight_You_hear_ip(const char *fmt,int a0,const char *a1){You_hear(fmt,a0,a1);}
void teleport_insight_You_hear_ipi(const char *fmt,int a0,const char *a1,int a2){You_hear(fmt,a0,a1,a2);}
void teleport_insight_You_hear_ipp(const char *fmt,int a0,const char *a1,const char *a2){You_hear(fmt,a0,a1,a2);}
void teleport_insight_You_hear_l(const char *fmt,long a0){You_hear(fmt,a0);}
void teleport_insight_You_hear_li(const char *fmt,long a0,int a1){You_hear(fmt,a0,a1);}
void teleport_insight_You_hear_lp(const char *fmt,long a0,const char *a1){You_hear(fmt,a0,a1);}
void teleport_insight_You_hear_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){You_hear(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_hear_p(const char *fmt,const char *a0){You_hear(fmt,a0);}
void teleport_insight_You_hear_pi(const char *fmt,const char *a0,int a1){You_hear(fmt,a0,a1);}
void teleport_insight_You_hear_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){You_hear(fmt,a0,a1,a2,a3);}
void teleport_insight_You_hear_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){You_hear(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_hear_plp(const char *fmt,const char *a0,long a1,const char *a2){You_hear(fmt,a0,a1,a2);}
void teleport_insight_You_hear_pp(const char *fmt,const char *a0,const char *a1){You_hear(fmt,a0,a1);}
void teleport_insight_You_hear_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){You_hear(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_You_hear_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You_hear(fmt,a0,a1,a2);}
void teleport_insight_You_hear_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){You_hear(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_You_hear_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){You_hear(fmt,a0,a1,a2,a3);}
void teleport_insight_You_hear_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You_hear(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_hear_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){You_hear(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_You_hear_u(const char *fmt,unsigned a0){You_hear(fmt,a0);}
void teleport_insight_You_see_none(const char *fmt){You_see(fmt);}
void teleport_insight_You_see_i(const char *fmt,int a0){You_see(fmt,a0);}
void teleport_insight_You_see_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){You_see(fmt,a0,a1,a2,a3);}
void teleport_insight_You_see_iip(const char *fmt,int a0,int a1,const char *a2){You_see(fmt,a0,a1,a2);}
void teleport_insight_You_see_ip(const char *fmt,int a0,const char *a1){You_see(fmt,a0,a1);}
void teleport_insight_You_see_ipi(const char *fmt,int a0,const char *a1,int a2){You_see(fmt,a0,a1,a2);}
void teleport_insight_You_see_ipp(const char *fmt,int a0,const char *a1,const char *a2){You_see(fmt,a0,a1,a2);}
void teleport_insight_You_see_l(const char *fmt,long a0){You_see(fmt,a0);}
void teleport_insight_You_see_li(const char *fmt,long a0,int a1){You_see(fmt,a0,a1);}
void teleport_insight_You_see_lp(const char *fmt,long a0,const char *a1){You_see(fmt,a0,a1);}
void teleport_insight_You_see_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){You_see(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_see_p(const char *fmt,const char *a0){You_see(fmt,a0);}
void teleport_insight_You_see_pi(const char *fmt,const char *a0,int a1){You_see(fmt,a0,a1);}
void teleport_insight_You_see_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){You_see(fmt,a0,a1,a2,a3);}
void teleport_insight_You_see_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){You_see(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_see_plp(const char *fmt,const char *a0,long a1,const char *a2){You_see(fmt,a0,a1,a2);}
void teleport_insight_You_see_pp(const char *fmt,const char *a0,const char *a1){You_see(fmt,a0,a1);}
void teleport_insight_You_see_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){You_see(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_You_see_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){You_see(fmt,a0,a1,a2);}
void teleport_insight_You_see_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){You_see(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_You_see_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){You_see(fmt,a0,a1,a2,a3);}
void teleport_insight_You_see_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){You_see(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_You_see_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){You_see(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_You_see_u(const char *fmt,unsigned a0){You_see(fmt,a0);}
void teleport_insight_urgent_pline_none(const char *fmt){urgent_pline(fmt);}
void teleport_insight_urgent_pline_i(const char *fmt,int a0){urgent_pline(fmt,a0);}
void teleport_insight_urgent_pline_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){urgent_pline(fmt,a0,a1,a2,a3);}
void teleport_insight_urgent_pline_iip(const char *fmt,int a0,int a1,const char *a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_insight_urgent_pline_ip(const char *fmt,int a0,const char *a1){urgent_pline(fmt,a0,a1);}
void teleport_insight_urgent_pline_ipi(const char *fmt,int a0,const char *a1,int a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_insight_urgent_pline_ipp(const char *fmt,int a0,const char *a1,const char *a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_insight_urgent_pline_l(const char *fmt,long a0){urgent_pline(fmt,a0);}
void teleport_insight_urgent_pline_li(const char *fmt,long a0,int a1){urgent_pline(fmt,a0,a1);}
void teleport_insight_urgent_pline_lp(const char *fmt,long a0,const char *a1){urgent_pline(fmt,a0,a1);}
void teleport_insight_urgent_pline_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){urgent_pline(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_urgent_pline_p(const char *fmt,const char *a0){urgent_pline(fmt,a0);}
void teleport_insight_urgent_pline_pi(const char *fmt,const char *a0,int a1){urgent_pline(fmt,a0,a1);}
void teleport_insight_urgent_pline_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){urgent_pline(fmt,a0,a1,a2,a3);}
void teleport_insight_urgent_pline_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){urgent_pline(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_urgent_pline_plp(const char *fmt,const char *a0,long a1,const char *a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_insight_urgent_pline_pp(const char *fmt,const char *a0,const char *a1){urgent_pline(fmt,a0,a1);}
void teleport_insight_urgent_pline_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){urgent_pline(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_urgent_pline_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){urgent_pline(fmt,a0,a1,a2);}
void teleport_insight_urgent_pline_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){urgent_pline(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_urgent_pline_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){urgent_pline(fmt,a0,a1,a2,a3);}
void teleport_insight_urgent_pline_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){urgent_pline(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_urgent_pline_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){urgent_pline(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_urgent_pline_u(const char *fmt,unsigned a0){urgent_pline(fmt,a0);}
void teleport_insight_verbalize_none(const char *fmt){verbalize(fmt);}
void teleport_insight_verbalize_i(const char *fmt,int a0){verbalize(fmt,a0);}
void teleport_insight_verbalize_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){verbalize(fmt,a0,a1,a2,a3);}
void teleport_insight_verbalize_iip(const char *fmt,int a0,int a1,const char *a2){verbalize(fmt,a0,a1,a2);}
void teleport_insight_verbalize_ip(const char *fmt,int a0,const char *a1){verbalize(fmt,a0,a1);}
void teleport_insight_verbalize_ipi(const char *fmt,int a0,const char *a1,int a2){verbalize(fmt,a0,a1,a2);}
void teleport_insight_verbalize_ipp(const char *fmt,int a0,const char *a1,const char *a2){verbalize(fmt,a0,a1,a2);}
void teleport_insight_verbalize_l(const char *fmt,long a0){verbalize(fmt,a0);}
void teleport_insight_verbalize_li(const char *fmt,long a0,int a1){verbalize(fmt,a0,a1);}
void teleport_insight_verbalize_lp(const char *fmt,long a0,const char *a1){verbalize(fmt,a0,a1);}
void teleport_insight_verbalize_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){verbalize(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_verbalize_p(const char *fmt,const char *a0){verbalize(fmt,a0);}
void teleport_insight_verbalize_pi(const char *fmt,const char *a0,int a1){verbalize(fmt,a0,a1);}
void teleport_insight_verbalize_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){verbalize(fmt,a0,a1,a2,a3);}
void teleport_insight_verbalize_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){verbalize(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_verbalize_plp(const char *fmt,const char *a0,long a1,const char *a2){verbalize(fmt,a0,a1,a2);}
void teleport_insight_verbalize_pp(const char *fmt,const char *a0,const char *a1){verbalize(fmt,a0,a1);}
void teleport_insight_verbalize_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){verbalize(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_verbalize_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){verbalize(fmt,a0,a1,a2);}
void teleport_insight_verbalize_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){verbalize(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_verbalize_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){verbalize(fmt,a0,a1,a2,a3);}
void teleport_insight_verbalize_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){verbalize(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_verbalize_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){verbalize(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_verbalize_u(const char *fmt,unsigned a0){verbalize(fmt,a0);}
void teleport_insight_impossible_none(const char *fmt){impossible(fmt);}
void teleport_insight_impossible_i(const char *fmt,int a0){impossible(fmt,a0);}
void teleport_insight_impossible_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){impossible(fmt,a0,a1,a2,a3);}
void teleport_insight_impossible_iip(const char *fmt,int a0,int a1,const char *a2){impossible(fmt,a0,a1,a2);}
void teleport_insight_impossible_ip(const char *fmt,int a0,const char *a1){impossible(fmt,a0,a1);}
void teleport_insight_impossible_ipi(const char *fmt,int a0,const char *a1,int a2){impossible(fmt,a0,a1,a2);}
void teleport_insight_impossible_ipp(const char *fmt,int a0,const char *a1,const char *a2){impossible(fmt,a0,a1,a2);}
void teleport_insight_impossible_l(const char *fmt,long a0){impossible(fmt,a0);}
void teleport_insight_impossible_li(const char *fmt,long a0,int a1){impossible(fmt,a0,a1);}
void teleport_insight_impossible_lp(const char *fmt,long a0,const char *a1){impossible(fmt,a0,a1);}
void teleport_insight_impossible_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){impossible(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_impossible_p(const char *fmt,const char *a0){impossible(fmt,a0);}
void teleport_insight_impossible_pi(const char *fmt,const char *a0,int a1){impossible(fmt,a0,a1);}
void teleport_insight_impossible_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){impossible(fmt,a0,a1,a2,a3);}
void teleport_insight_impossible_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){impossible(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_impossible_plp(const char *fmt,const char *a0,long a1,const char *a2){impossible(fmt,a0,a1,a2);}
void teleport_insight_impossible_pp(const char *fmt,const char *a0,const char *a1){impossible(fmt,a0,a1);}
void teleport_insight_impossible_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){impossible(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_impossible_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){impossible(fmt,a0,a1,a2);}
void teleport_insight_impossible_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){impossible(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_impossible_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){impossible(fmt,a0,a1,a2,a3);}
void teleport_insight_impossible_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){impossible(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_impossible_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){impossible(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_impossible_u(const char *fmt,unsigned a0){impossible(fmt,a0);}
void teleport_insight_panic_none(const char *fmt){panic(fmt);}
void teleport_insight_panic_i(const char *fmt,int a0){panic(fmt,a0);}
void teleport_insight_panic_iiip(const char *fmt,int a0,int a1,int a2,const char *a3){panic(fmt,a0,a1,a2,a3);}
void teleport_insight_panic_iip(const char *fmt,int a0,int a1,const char *a2){panic(fmt,a0,a1,a2);}
void teleport_insight_panic_ip(const char *fmt,int a0,const char *a1){panic(fmt,a0,a1);}
void teleport_insight_panic_ipi(const char *fmt,int a0,const char *a1,int a2){panic(fmt,a0,a1,a2);}
void teleport_insight_panic_ipp(const char *fmt,int a0,const char *a1,const char *a2){panic(fmt,a0,a1,a2);}
void teleport_insight_panic_l(const char *fmt,long a0){panic(fmt,a0);}
void teleport_insight_panic_li(const char *fmt,long a0,int a1){panic(fmt,a0,a1);}
void teleport_insight_panic_lp(const char *fmt,long a0,const char *a1){panic(fmt,a0,a1);}
void teleport_insight_panic_lpppi(const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){panic(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_panic_p(const char *fmt,const char *a0){panic(fmt,a0);}
void teleport_insight_panic_pi(const char *fmt,const char *a0,int a1){panic(fmt,a0,a1);}
void teleport_insight_panic_pipp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3){panic(fmt,a0,a1,a2,a3);}
void teleport_insight_panic_pippp(const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){panic(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_panic_plp(const char *fmt,const char *a0,long a1,const char *a2){panic(fmt,a0,a1,a2);}
void teleport_insight_panic_pp(const char *fmt,const char *a0,const char *a1){panic(fmt,a0,a1);}
void teleport_insight_panic_ppiiiip(const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){panic(fmt,a0,a1,a2,a3,a4,a5,a6);}
void teleport_insight_panic_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){panic(fmt,a0,a1,a2);}
void teleport_insight_panic_pppiiiip(const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){panic(fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_insight_panic_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){panic(fmt,a0,a1,a2,a3);}
void teleport_insight_panic_ppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){panic(fmt,a0,a1,a2,a3,a4);}
void teleport_insight_panic_pppppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){panic(fmt,a0,a1,a2,a3,a4,a5);}
void teleport_insight_panic_u(const char *fmt,unsigned a0){panic(fmt,a0);}
int teleport_insight_Sprintf_none(char *out,const char *fmt){return sprintf(out,fmt);}
int teleport_insight_Sprintf_i(char *out,const char *fmt,int a0){return sprintf(out,fmt,a0);}
int teleport_insight_Sprintf_iiip(char *out,const char *fmt,int a0,int a1,int a2,const char *a3){return sprintf(out,fmt,a0,a1,a2,a3);}
int teleport_insight_Sprintf_iip(char *out,const char *fmt,int a0,int a1,const char *a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_insight_Sprintf_ip(char *out,const char *fmt,int a0,const char *a1){return sprintf(out,fmt,a0,a1);}
int teleport_insight_Sprintf_ipi(char *out,const char *fmt,int a0,const char *a1,int a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_insight_Sprintf_ipp(char *out,const char *fmt,int a0,const char *a1,const char *a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_insight_Sprintf_l(char *out,const char *fmt,long a0){return sprintf(out,fmt,a0);}
int teleport_insight_Sprintf_li(char *out,const char *fmt,long a0,int a1){return sprintf(out,fmt,a0,a1);}
int teleport_insight_Sprintf_lp(char *out,const char *fmt,long a0,const char *a1){return sprintf(out,fmt,a0,a1);}
int teleport_insight_Sprintf_lpppi(char *out,const char *fmt,long a0,const char *a1,const char *a2,const char *a3,int a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_insight_Sprintf_p(char *out,const char *fmt,const char *a0){return sprintf(out,fmt,a0);}
int teleport_insight_Sprintf_pi(char *out,const char *fmt,const char *a0,int a1){return sprintf(out,fmt,a0,a1);}
int teleport_insight_Sprintf_pipp(char *out,const char *fmt,const char *a0,int a1,const char *a2,const char *a3){return sprintf(out,fmt,a0,a1,a2,a3);}
int teleport_insight_Sprintf_pippp(char *out,const char *fmt,const char *a0,int a1,const char *a2,const char *a3,const char *a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_insight_Sprintf_plp(char *out,const char *fmt,const char *a0,long a1,const char *a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_insight_Sprintf_pp(char *out,const char *fmt,const char *a0,const char *a1){return sprintf(out,fmt,a0,a1);}
int teleport_insight_Sprintf_ppiiiip(char *out,const char *fmt,const char *a0,const char *a1,int a2,int a3,int a4,int a5,const char *a6){return sprintf(out,fmt,a0,a1,a2,a3,a4,a5,a6);}
int teleport_insight_Sprintf_ppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2){return sprintf(out,fmt,a0,a1,a2);}
int teleport_insight_Sprintf_pppiiiip(char *out,const char *fmt,const char *a0,const char *a1,const char *a2,int a3,int a4,int a5,int a6,const char *a7){return sprintf(out,fmt,a0,a1,a2,a3,a4,a5,a6,a7);}
int teleport_insight_Sprintf_pppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){return sprintf(out,fmt,a0,a1,a2,a3);}
int teleport_insight_Sprintf_ppppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_insight_Sprintf_pppppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3,const char *a4,const char *a5){return sprintf(out,fmt,a0,a1,a2,a3,a4,a5);}
int teleport_insight_Sprintf_u(char *out,const char *fmt,unsigned a0){return sprintf(out,fmt,a0);}
void teleport_insight_snprintf_p(int site,char*out,size_t n,const char*fmt,const char*a0){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0);}
void teleport_insight_snprintf_pp(int site,char*out,size_t n,const char*fmt,const char*a0,const char*a1){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1);}
void teleport_insight_snprintf_ppp(int site,char*out,size_t n,const char*fmt,const char*a0,const char*a1,const char*a2){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1,a2);}
void teleport_insight_snprintf_pppp(int site,char*out,size_t n,const char*fmt,const char*a0,const char*a1,const char*a2,const char*a3){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1,a2,a3);}
void teleport_insight_snprintf_lp(int site,char*out,size_t n,const char*fmt,long a0,const char*a1){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1);}
void teleport_insight_snprintf_ip(int site,char*out,size_t n,const char*fmt,int a0,const char*a1){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1);}
void teleport_insight_snprintf_ipi(int site,char*out,size_t n,const char*fmt,int a0,const char*a1,int a2){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1,a2);}
void teleport_insight_snprintf_ippp(int site,char*out,size_t n,const char*fmt,int a0,const char*a1,const char*a2,const char*a3){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1,a2,a3);}
void teleport_insight_snprintf_ipp(int site,char*out,size_t n,const char*fmt,int a0,const char*a1,const char*a2){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1,a2);}
void teleport_insight_snprintf_pip(int site,char*out,size_t n,const char*fmt,const char*a0,int a1,const char*a2){static const int source_lines[]=TELEPORT_INSIGHT_SNPRINTF_LINES;static const char*const funcs[]=TELEPORT_INSIGHT_SNPRINTF_FUNCTIONS;nh_snprintf(funcs[site],source_lines[site],out,n,fmt,a0,a1,a2);}
