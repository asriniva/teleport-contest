/* DOKICK: typed native fields, original dependencies and callback ABI only. */
#include "hack.h"
const void *teleport_dokick_global(int i){switch(i){case 0:return &u;case 1:return &gy;case 2:return &svc;case 3:return &gb;case 4:return &gm;case 5:return &gk;case 6:return &gn;case 7:return &gg;case 8:return &gi;case 9:return &svm;case 10:return &svl;case 11:return &svd;case 12:return &svk;case 13:return &flags;case 14:return &iflags;case 15:return &gu;case 16:return mons;case 17:return objects;case 18:return genders;case 19:return &svp;case 20:return &gv;default:return 0;}}
void *teleport_dokick_equipment(int i){return i==0?uarm:i==1?uarmf:i==2?uball:uchain;}
unsigned teleport_dokick_monster_bit(struct monst *p,int i){switch(i){case 0:return p->isshk;case 1:return p->ispriest;case 2:return p->isgd;case 3:return p->mcanmove;case 4:return p->msleeping;case 5:return p->mpeaceful;case 6:return p->mflee;case 7:return p->mundetected;case 8:return p->mcansee;case 9:return p->mtrapped;case 10:return p->mstun;case 11:return p->mconf;default:return 0;}}
void teleport_dokick_set_monster_bit(struct monst *p,int i,unsigned v){switch(i){case 0:p->isshk=v;break;case 1:p->ispriest=v;break;case 2:p->isgd=v;break;case 3:p->mcanmove=v;break;case 4:p->msleeping=v;break;case 5:p->mpeaceful=v;break;case 6:p->mflee=v;break;case 7:p->mundetected=v;break;case 8:p->mcansee=v;break;case 9:p->mtrapped=v;break;case 10:p->mstun=v;break;case 11:p->mconf=v;break;}}
unsigned teleport_dokick_object_bit(struct obj *p,int i){switch(i){case 0:return p->unpaid;case 1:return p->no_charge;case 2:return p->cknown;case 3:return p->greased;case 4:return p->lknown;case 5:return p->olocked;case 6:return p->otrapped;case 7:return p->blessed;case 8:return p->cursed;default:return 0;}}
void teleport_dokick_set_object_bit(struct obj *p,int i,unsigned v){switch(i){case 0:p->unpaid=v;break;case 1:p->no_charge=v;break;case 2:p->cknown=v;break;case 3:p->greased=v;break;case 4:p->lknown=v;break;case 5:p->olocked=v;break;case 6:p->otrapped=v;break;case 7:p->blessed=v;break;case 8:p->cursed=v;break;}}
unsigned teleport_dokick_terrain_bit(struct rm *p,int i){switch(i){case 0:return p->disturbed;case 1:return p->doormask;case 2:return p->emptygrave;case 3:return p->looted;case 4:return p->ladder;default:return 0;}}
void teleport_dokick_set_terrain_bit(struct rm *p,int i,unsigned v){switch(i){case 0:p->disturbed=v;break;case 1:p->doormask=v;break;case 2:p->emptygrave=v;break;case 3:p->looted=v;break;case 4:p->ladder=v;break;}}
unsigned teleport_dokick_trap_bit(struct trap *p,int i){switch(i){case 0:return p->ttyp;case 1:return p->tseen;default:return 0;}}
void teleport_dokick_set_trap_bit(struct trap *p,int i,unsigned v){switch(i){case 0:p->ttyp=v;break;case 1:p->tseen=v;break;}}
unsigned teleport_dokick_class_bit(struct objclass *p,int i){return i?p->oc_material:p->oc_bulky;}
unsigned teleport_dokick_hero_bit(int i){return i==0?u.uinwater:i==1?u.uswallow:u.uroleplay.deaf;}
const char *teleport_dokick_common_string(int i){switch(i){case 0:return NH_BLACK;case 1:return Something;case 2:return something;case 3:return nothing_happens;default:return ynchars;}}
int teleport_dokick_win_message(void){return WIN_MESSAGE;}
static char teleport_dokick_literals[TELEPORT_DOKICK_LITERAL_CAPACITY+sizeof "%s"];
void *teleport_dokick_literal_storage(void){return teleport_dokick_literals;}
size_t teleport_dokick_literal_capacity(void){return sizeof teleport_dokick_literals;}
extern boolean teleport_dokick_callback_watchman_thief_arrest(struct monst *);
extern boolean teleport_dokick_callback_watchman_door_damage(struct monst *,coordxy,coordxy);
static boolean teleport_dokick_watch_thief(struct monst *m){return teleport_dokick_callback_watchman_thief_arrest(m);}
static boolean teleport_dokick_watch_door(struct monst *m,coordxy x,coordxy y){return teleport_dokick_callback_watchman_door_damage(m,x,y);}
struct monst *teleport_dokick_iterator(void){return get_iter_mons(teleport_dokick_watch_thief);}
struct monst *teleport_dokick_iterator_xy(coordxy x,coordxy y){return get_iter_mons_xy(teleport_dokick_watch_door,x,y);}
const char *teleport_dokick_singular(struct obj *o){return singular(o,doname);}
char *teleport_dokick_distant_name(struct obj *o){return distant_name(o,xname);}
struct monst *teleport_dokick_bhit(int dx,int dy,int range,int type,struct obj **o){return bhit(dx,dy,range,(enum bhit_call_types)type,NULL,NULL,o);}
void teleport_dokick_display(winid win,boolean blocking){display_nhwindow(win,blocking);}
int teleport_dokick_rng(int n,int line,const char *fn){if(rng_log_enabled())rng_log_set_caller("dokick.c",line,fn);return (rn2)(n);}
int teleport_dokick_rnd(int n,int line,const char *fn){if(rng_log_enabled())rng_log_set_caller("dokick.c",line,fn);return (rnd)(n);}
int teleport_dokick_rnl(int n,int line,const char *fn){if(rng_log_enabled())rng_log_set_caller("dokick.c",line,fn);return (rnl)(n);}
void teleport_dokick_pline_none(const char *fmt){pline(fmt);}
void teleport_dokick_pline_lp(const char *fmt,long a0,const char *a1){pline(fmt,a0,a1);}
void teleport_dokick_pline_p(const char *fmt,const char *a0){pline(fmt,a0);}
void teleport_dokick_pline_pp(const char *fmt,const char *a0,const char *a1){pline(fmt,a0,a1);}
void teleport_dokick_pline_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){pline(fmt,a0,a1,a2);}
void teleport_dokick_pline_pppp(const char *fmt,const char *a0,const char *a1,const char *a2,const char *a3){pline(fmt,a0,a1,a2,a3);}
void teleport_dokick_pline_The_none(const char *fmt){pline_The(fmt);}
void teleport_dokick_pline_The_p(const char *fmt,const char *a0){pline_The(fmt,a0);}
void teleport_dokick_pline_The_pp(const char *fmt,const char *a0,const char *a1){pline_The(fmt,a0,a1);}
void teleport_dokick_pline_The_ppp(const char *fmt,const char *a0,const char *a1,const char *a2){pline_The(fmt,a0,a1,a2);}
void teleport_dokick_Norep_p(const char *fmt,const char *a0){Norep(fmt,a0);}
void teleport_dokick_You_none(const char *fmt){You(fmt);}
void teleport_dokick_You_lp(const char *fmt,long a0,const char *a1){You(fmt,a0,a1);}
void teleport_dokick_You_p(const char *fmt,const char *a0){You(fmt,a0);}
void teleport_dokick_You_plp(const char *fmt,const char *a0,long a1,const char *a2){You(fmt,a0,a1,a2);}
void teleport_dokick_You_pp(const char *fmt,const char *a0,const char *a1){You(fmt,a0,a1);}
void teleport_dokick_Your_none(const char *fmt){Your(fmt);}
void teleport_dokick_Your_pp(const char *fmt,const char *a0,const char *a1){Your(fmt,a0,a1);}
void teleport_dokick_You_hear_none(const char *fmt){You_hear(fmt);}
void teleport_dokick_You_hear_p(const char *fmt,const char *a0){You_hear(fmt,a0);}
void teleport_dokick_You_cant_p(const char *fmt,const char *a0){You_cant(fmt,a0);}
void teleport_dokick_You_cant_pp(const char *fmt,const char *a0,const char *a1){You_cant(fmt,a0,a1);}
void teleport_dokick_There_p(const char *fmt,const char *a0){There(fmt,a0);}
void teleport_dokick_verbalize_none(const char *fmt){verbalize(fmt);}
void teleport_dokick_verbalize_p(const char *fmt,const char *a0){verbalize(fmt,a0);}
void teleport_dokick_mon_yells_none(struct monst *out,const char *fmt){mon_yells(out,fmt);}
int teleport_dokick_Sprintf_none(char *out,const char *fmt){return sprintf(out,fmt);}
int teleport_dokick_Sprintf_p(char *out,const char *fmt,const char *a0){return sprintf(out,fmt,a0);}
int teleport_dokick_Sprintf_pp(char *out,const char *fmt,const char *a0,const char *a1){return sprintf(out,fmt,a0,a1);}
int teleport_dokick_Sprintf_ppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2){return sprintf(out,fmt,a0,a1,a2);}
