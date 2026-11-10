/* MAKEMON native field/header/data/callback/varargs transport. No generation policy. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
const void*teleport_makemon_global(int i){switch(i){case 0:return (const void*)&svd;case 1:return (const void*)&u;case 2:return (const void*)&mons;case 3:return (const void*)&objects;case 4:return (const void*)&gi;case 5:return (const void*)&gu;case 6:return (const void*)&svl;case 7:return (const void*)&svm;case 8:return (const void*)&svc;case 9:return (const void*)&flags;case 10:return (const void*)&iflags;case 11:return (const void*)&gv;case 12:return (const void*)&gs;case 13:return (const void*)&cg;case 14:return (const void*)&svq;case 15:return (const void*)&uwep;case 16:return (const void*)&gm;case 17:return (const void*)&go;case 18:return (const void*)&def_monsyms;case 19:return (const void*)&windowprocs;case 20:return (const void*)&monsdump;case 21:return (const void*)&genders;case 22:return (const void*)&svr;case 23:return (const void*)&c_common_strings;default:return 0;}}
int teleport_makemon_bit(int kind,const void*p){switch(kind){case 0:return((const struct you*)p)->uinwater;case 1:return((const struct monst*)p)->mpeaceful;case 2:return((const struct monst*)p)->mavenge;case 3:return((const struct monst*)p)->isminion;case 4:return((const struct monst*)p)->mundetected;case 5:return((const struct monst*)p)->mtrapped;case 6:return((const struct monst*)p)->mcloned;case 7:return((const struct monst*)p)->mleashed;case 8:return((const struct monst*)p)->isshk;case 9:return((const struct monst*)p)->isgd;case 10:return((const struct monst*)p)->ispriest;case 11:return((const struct monst*)p)->msleeping;case 12:return((const struct monst*)p)->female;case 13:return((const struct monst*)p)->mwandexp;case 14:return((const struct monst*)p)->mcansee;case 15:return((const struct monst*)p)->mcanmove;case 16:return((const struct monst*)p)->mgenmklev;case 17:return((const struct monst*)p)->perminvis;case 18:return((const struct monst*)p)->minvis;case 19:return((const struct monst*)p)->iswiz;case 20:return((const struct monst*)p)->wormno;case 21:return((const struct obj*)p)->otrapped;case 22:return((const struct obj*)p)->oerodeproof;case 23:return((const struct obj*)p)->oeroded;case 24:return((const struct obj*)p)->oeroded2;case 25:return((const struct obj*)p)->blessed;case 26:return((const struct obj*)p)->cursed;case 27:return((const struct obj*)p)->lamplit;case 28:return((const struct obj*)p)->cknown;case 29:return((const struct obj*)p)->dknown;case 30:return((const struct objclass*)p)->oc_name_known;case 31:return((const struct rm*)p)->lit;case 32:return((const struct rm*)p)->roomno;case 33:return((const struct levelflags*)p)->rndmongen;case 34:return((const struct levelflags*)p)->is_maze_lev;case 35:return((const struct q_score*)p)->ldrgend;case 36:return((const struct q_score*)p)->nemgend;case 37:return((const struct u_have*)p)->amulet;case 38:return((const d_flags*)p)->align;default:abort();}}
void teleport_makemon_set_bit(int kind,void*p,unsigned n){switch(kind){case 0:((struct you*)p)->uinwater=n;return;case 1:((struct monst*)p)->mpeaceful=n;return;case 2:((struct monst*)p)->mavenge=n;return;case 3:((struct monst*)p)->isminion=n;return;case 4:((struct monst*)p)->mundetected=n;return;case 5:((struct monst*)p)->mtrapped=n;return;case 6:((struct monst*)p)->mcloned=n;return;case 7:((struct monst*)p)->mleashed=n;return;case 8:((struct monst*)p)->isshk=n;return;case 9:((struct monst*)p)->isgd=n;return;case 10:((struct monst*)p)->ispriest=n;return;case 11:((struct monst*)p)->msleeping=n;return;case 12:((struct monst*)p)->female=n;return;case 13:((struct monst*)p)->mwandexp=n;return;case 14:((struct monst*)p)->mcansee=n;return;case 15:((struct monst*)p)->mcanmove=n;return;case 16:((struct monst*)p)->mgenmklev=n;return;case 17:((struct monst*)p)->perminvis=n;return;case 18:((struct monst*)p)->minvis=n;return;case 19:((struct monst*)p)->iswiz=n;return;case 20:((struct monst*)p)->wormno=n;return;case 21:((struct obj*)p)->otrapped=n;return;case 22:((struct obj*)p)->oerodeproof=n;return;case 23:((struct obj*)p)->oeroded=n;return;case 24:((struct obj*)p)->oeroded2=n;return;case 25:((struct obj*)p)->blessed=n;return;case 26:((struct obj*)p)->cursed=n;return;case 27:((struct obj*)p)->lamplit=n;return;case 28:((struct obj*)p)->cknown=n;return;case 29:((struct obj*)p)->dknown=n;return;case 30:((struct objclass*)p)->oc_name_known=n;return;case 31:((struct rm*)p)->lit=n;return;case 32:((struct rm*)p)->roomno=n;return;case 33:((struct levelflags*)p)->rndmongen=n;return;case 34:((struct levelflags*)p)->is_maze_lev=n;return;case 35:((struct q_score*)p)->ldrgend=n;return;case 36:((struct q_score*)p)->nemgend=n;return;case 37:((struct u_have*)p)->amulet=n;return;case 38:((d_flags*)p)->align=n;return;default:abort();}}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_makemon_mongen_order mongen_order
#define teleport_makemon_mclass_maxf mclass_maxf
#define teleport_makemon_zeromextra zeromextra
#define teleport_makemon_mongen_order_init mongen_order_init
/* function-local align_shift statics have no direct foreign address */
#else
static int teleport_makemon_mongen_order[NUMMONS];
static xint8 teleport_makemon_mclass_maxf[MAXMCLASSES];
static const struct mextra teleport_makemon_zeromextra=DUMMY;
static boolean teleport_makemon_mongen_order_init=FALSE;
#endif
static long teleport_makemon_oldmoves=0L;
static s_level*teleport_makemon_lev;
const void*teleport_makemon_data(int i){switch(i){
case 0:return teleport_makemon_mongen_order;case 1:return teleport_makemon_mclass_maxf;case 2:return &teleport_makemon_zeromextra;
case 3:return &teleport_makemon_mongen_order_init;case 4:return &teleport_makemon_oldmoves;case 5:return &teleport_makemon_lev;default:return 0;}}
void teleport_makemon_rng_source(int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("makemon.c",line,fn);}
int teleport_makemon_rn2(int n){return(rn2)(n);}int teleport_makemon_rnd(int n){return(rnd)(n);}int teleport_makemon_d(int n,int s){return(d)(n,s);}
void teleport_makemon_assert(const char*expr,const char*file,int line,const char*fn){__assert_fail(expr,file,line,fn);}
void teleport_makemon_raw_print(const char*s){raw_print(s);}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_makemon_private_cmp cmp_init_mongen_order
#else
extern int teleport_makemon_private_cmp(const void*,const void*);
#endif
static int teleport_makemon_cmp(const void*a,const void*b){return teleport_makemon_private_cmp(a,b);}
void teleport_makemon_qsort(void*p,size_t n,size_t width){qsort(p,n,width,teleport_makemon_cmp);}
int teleport_makemon_v_0(char *restrict a0,const char *restrict a1,const char* a2,const char* a3){return sprintf(a0,a1,a2,a3);}
void teleport_makemon_v_2(const char * a0,int a1,char * a2,size_t a3,const char * a4,const char* a5,const char* a6){nh_snprintf(a0,a1,a2,a3,a4,a5,a6);}
void teleport_makemon_v_4(const char * a0,const char* a1,const char* a2,const char* a3,const char* a4,int a5){Norep(a0,a1,a2,a3,a4,a5);}
void teleport_makemon_v_6(const char * a0,const char* a1){pline(a0,a1);}
void teleport_makemon_v_7(const char * a0){pline(a0);}
void teleport_makemon_v_8(const char * a0,int a1){pline(a0,a1);}
void teleport_makemon_v_9(const char * a0,const char* a1,const char* a2,const char* a3,const char* a4){pline(a0,a1,a2,a3,a4);}
void teleport_makemon_v_11(struct monst * a0,const char * a1,const char* a2,const char* a3,const char* a4){pline_mon(a0,a1,a2,a3,a4);}
void teleport_makemon_v_13(const char * a0){raw_printf(a0);}
void teleport_makemon_v_14(const char * a0,int a1,const char* a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,const char* a10){raw_printf(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}
void teleport_makemon_v_16(const char * a0,int a1){impossible(a0,a1);}
void teleport_makemon_v_17(const char * a0,int a1,int a2){impossible(a0,a1,a2);}
void teleport_makemon_v_18(const char * a0){impossible(a0);}
static char teleport_makemon_literals[1092];void*teleport_makemon_literal_storage(void){return teleport_makemon_literals;}size_t teleport_makemon_literal_capacity(void){return sizeof teleport_makemon_literals;}
