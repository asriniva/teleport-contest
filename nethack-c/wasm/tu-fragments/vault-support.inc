/* Typed fields/header macros, printf and original RNG source attribution only. */
#include "hack.h"
const void*teleport_vault_global(int i){switch(i){case 0:return &u;case 1:return &fmon;case 2:return &gm.migrating_mons;case 3:return &levl[0][0];case 4:return &svl.level.monsters[0][0];case 5:return &svr.rooms[0];case 6:return &gv.viz_array;case 7:return &gv.vision_full_recalc;case 8:return &program_state.stopprint;case 9:return &svc.context.polearm.hitmon;case 10:return &gy.youmonst;case 11:return &gi.invent;case 12:return &gm.multi;case 13:return svm.mvitals;case 14:return svp.plname;case 15:return mons;case 16:return &uball;case 17:return &flags.female;default:return 0;}}
int teleport_vault_monster_bit(struct monst*m,int i){switch(i){case 0:return m->isgd;case 1:return m->mpeaceful;case 2:return m->mcansee;default:return 0;}}
void teleport_vault_set_monster_bit(struct monst*m,int i,unsigned v){switch(i){case 0:m->isgd=v;break;case 1:m->mpeaceful=v;break;case 2:m->mcansee=v;break;}}
int teleport_vault_egd_bit(struct egd*e,int i){return i?e->witness:e->gddone;}
void teleport_vault_set_egd_bit(struct egd*e,int i,unsigned v){if(i)e->witness=v;else e->gddone=v;}
int teleport_vault_object_cknown(struct obj*o){return o->cknown;}
int teleport_vault_object_class(int type){return objects[type].oc_class;}
int teleport_vault_hero_bit(int i){return i?u.uundetected:u.uswallow;}
int teleport_vault_flag(int i){switch(i){case 0:return !!Upolyd;case 1:return !!Blind;case 2:return !!Deaf;case 3:return !!Strangled;default:return 0;}}
int teleport_vault_terrain_bit(coordxy x,coordxy y,int i){switch(i){case 0:return levl[x][y].flags;case 1:return levl[x][y].lit;case 2:return levl[x][y].waslit;case 3:return levl[x][y].wall_info;case 4:return levl[x][y].doormask;default:return 0;}}
void teleport_vault_set_terrain_bit(coordxy x,coordxy y,int i,unsigned v){switch(i){case 0:levl[x][y].flags=v;break;case 1:levl[x][y].lit=v;break;case 2:levl[x][y].waslit=v;break;case 3:levl[x][y].wall_info=v;break;case 4:levl[x][y].doormask=v;break;}}
const char*teleport_vault_pronoun(struct monst*m,int i){return i?noit_mhis(m):mhe(m);}
static const char*const teleport_vault_callers[]={"invault","move_gold","gd_move","paygd"};
int teleport_vault_rn2(int n,int line,int caller){if(rng_log_enabled())rng_log_set_caller("vault.c",line,teleport_vault_callers[caller]);return(rn2)(n);}
void teleport_vault_message(int kind,const char*f,const char*a,const char*b,const char*c){switch(kind){case 0:pline(f,a,b,c);break;case 1:pline_The(f,a,b,c);break;case 2:You(f,a,b,c);break;case 3:You_hear(f,a,b,c);break;case 4:You_see(f,a,b,c);break;case 5:verbalize(f,a,b,c);break;}}
void teleport_vault_Your_gold(const char*f,long amount,const char*unit){Your(f,amount,unit);}
char*teleport_vault_sprintf(char*out,const char*f,const char*a,const char*b){Sprintf(out,f,a,b);return out;}
void teleport_vault_impossible(const char*f){impossible(f,(char*)0);}
void teleport_vault_panic(const char*f){panic(f,(char*)0);}
void teleport_vault_debug1(const char*f,const char*a){if(debugcore("vault.c",TRUE)){int saved=iflags.last_msg;pline(f,a);iflags.last_msg=saved;}}
void teleport_vault_debug2(const char*f,const char*a,const char*b){if(debugcore("vault.c",TRUE)){int saved=iflags.last_msg;pline(f,a,b);iflags.last_msg=saved;}}
static char teleport_vault_literals[1934];void*teleport_vault_literal_storage(void){return teleport_vault_literals;}size_t teleport_vault_literal_capacity(void){return sizeof teleport_vault_literals;}

int teleport_vault_m_canseeu(struct monst*m){return !!m_canseeu(m);}
void teleport_vault_free(void*p){free(p);}
