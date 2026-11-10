/* MHITM: native layout, field access, attribution and typed varargs only. */
#include "hack.h"
const void *teleport_mhitm_global(int index) {
 switch(index){case 0:return &u;case 1:return &gf;case 2:return &svm;case 3:return &gn;case 4:return &gv;case 5:return &gb;case 6:return &gs;case 7:return &gl;case 8:return &iflags;case 9:return &flags;case 10:return &gy;case 11:return &gm;case 12:return &gz;case 13:return mons;case 14:return objects;case 15:return &svl;case 16:return genders;default:return 0;}
}
unsigned teleport_mhitm_monster_bit(struct monst *m,int index) {
 switch(index){case 0:return m->mcan;case 1:return m->mconf;case 2:return m->mundetected;case 3:return m->msleeping;case 4:return m->mcanmove;case 5:return m->wormno;case 6:return m->mcansee;case 7:return m->minvis;case 8:return m->mleashed;case 9:return m->mstun;case 10:return m->mfrozen;default:return m->mtrapped;}
}
void teleport_mhitm_set_monster_bit(struct monst *m,int index,unsigned value) {
 switch(index){case 0:m->mcan=value;break;case 1:m->mconf=value;break;case 2:m->mundetected=value;break;case 3:m->msleeping=value;break;case 4:m->mcanmove=value;break;case 5:m->wormno=value;break;case 6:m->mcansee=value;break;case 7:m->minvis=value;break;case 8:m->mleashed=value;break;case 9:m->mstun=value;break;case 10:m->mfrozen=value;break;default:m->mtrapped=value;break;}
}
unsigned teleport_mhitm_hero_bit(int index){return index?u.uroleplay.deaf:u.uswallow;}
unsigned teleport_mhitm_class_material(struct objclass *cls){return cls->oc_material;}
unsigned teleport_mhitm_arboreal(void){return svl.level.flags.arboreal;}
const char *teleport_mhitm_common_string(int index){return index?nothing_happens:something;}
int teleport_mhitm_rng(int bound,int dice,int dice_call,int line,const char *caller){if(rng_log_enabled())rng_log_set_caller("mhitm.c",line,caller);return dice_call?(d)(dice,bound):(rn2)(bound);}
int teleport_mhitm_rnd(int bound,int line,const char *caller){if(rng_log_enabled())rng_log_set_caller("mhitm.c",line,caller);return (rnd)(bound);}
void teleport_mhitm_pline(const char *fmt,const char *a,const char *b,const char *c,const char *e,const char *f,const char *g){pline(fmt,a,b,c,e,f,g);}
void teleport_mhitm_pline_mon(struct monst *mon,const char *fmt,const char *a,const char *b){pline_mon(mon,fmt,a,b);}
void teleport_mhitm_You(const char *fmt,const char *a,const char *b){You(fmt,a,b);}
void teleport_mhitm_You_hear(const char *fmt,const char *a,const char *b){You_hear(fmt,a,b);}
void teleport_mhitm_You_feel(const char *fmt,const char *a){You_feel(fmt,a);}
void teleport_mhitm_Your(const char *fmt){Your(fmt);}
int teleport_mhitm_sprintf(char *out,const char *fmt,const char *a,const char *b){return sprintf(out,fmt,a,b);}
void teleport_mhitm_snprintf(char *out,size_t size,const char *fmt,const char *a,const char *b,int site){static const int lines[]=TELEPORT_MHITM_SNPRINTF_LINES;nh_snprintf("hitmm",lines[site],out,size,fmt,a,b);}
static char teleport_mhitm_literals[TELEPORT_MHITM_LITERAL_CAPACITY+sizeof "%s"];
void *teleport_mhitm_literal_storage(void){return teleport_mhitm_literals;}
size_t teleport_mhitm_literal_capacity(void){return sizeof teleport_mhitm_literals;}
