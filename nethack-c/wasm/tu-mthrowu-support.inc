/* Native fields and typed actual dependencies only; all projectile/combat policy is JavaScript. */
#include "hack.h"
void *teleport_mthrowu_global(int i){switch(i){case 0:return &u;case 1:return &gy;case 2:return &gm;case 3:return &gt;case 4:return &gb;case 5:return &gn;case 6:return &gv;case 7:return &gi;case 8:return &gu;case 9:return &svc;case 10:return &svm;case 11:return &flags;case 12:return &iflags;case 13:return &svl;case 14:return &go;case 15:return mons;case 16:return objects;case 17:return (void*)genders;}return 0;}
unsigned teleport_mthrowu_object_bit(struct obj*o,int i){switch(i){case 0:return o->cursed;case 1:return o->greased;case 2:return o->known;case 3:return o->opoisoned;case 4:return o->otrapped;case 5:return o->dknown;}return 0;}
void teleport_mthrowu_set_object_bit(struct obj*o,int i,unsigned v){switch(i){case 0:o->cursed=v;break;case 1:o->greased=v;break;case 2:o->known=v;break;case 3:o->opoisoned=v;break;case 4:o->otrapped=v;break;case 5:o->dknown=v;break;}}
unsigned teleport_mthrowu_monster_bit(struct monst*m,int i){switch(i){case 0:return m->isminion;case 1:return m->mblinded;case 2:return m->mcan;case 3:return m->mcansee;case 4:return m->mconf;case 5:return m->mflee;case 6:return m->msleeping;case 7:return m->mstun;}return 0;}
void teleport_mthrowu_set_monster_bit(struct monst*m,int i,unsigned v){switch(i){case 0:m->isminion=v;break;case 1:m->mblinded=v;break;case 2:m->mcan=v;break;case 3:m->mcansee=v;break;case 4:m->mconf=v;break;case 5:m->mflee=v;break;case 6:m->msleeping=v;break;case 7:m->mstun=v;break;}}
unsigned teleport_mthrowu_hero_bit(int i){switch(i){case 0:return u.uundetected;case 1:return u.uroleplay.deaf;case 2:return u.uinwater;}return 0;}
unsigned teleport_mthrowu_class_bit(struct objclass*c,int i){return c->oc_material;}
unsigned teleport_mthrowu_return_bit(const struct throw_and_return_weapon*p){return p->tethered;}
void *teleport_mthrowu_string_alloc(size_t n){return malloc(n);}
void teleport_mthrowu_delay(void){nh_delay_output();}
boolean teleport_mthrowu_invoke(uintptr_t token,coordxy x,coordxy y){return ((boolean(*)(coordxy,coordxy))token)(x,y);}
const char *teleport_mthrowu_singular(struct obj*o,int which){return singular(o,which?mshot_xname:xname);}
char *teleport_mthrowu_distant(struct obj*o,int which){return distant_name(o,which?mshot_xname:xname);}
int teleport_mthrowu_rng(int kind,int n,const char*name,int line){if(rng_log_enabled())rng_log_set_caller("mthrowu.c",line,name);return kind?(rnd)(n):(rn2)(n);}
void teleport_mthrowu_format_ip(char*out,const char*fmt,int n,const char*p){Sprintf(out,fmt,n,p);}
void teleport_mthrowu_format_p(char*out,const char*fmt,const char*p){Sprintf(out,fmt,p);}
void teleport_mthrowu_snprintf(char*out,size_t n,const char*fmt,const char*p){nh_snprintf("u_catch_thrown_obj",544,out,n,fmt,p);}
void teleport_mthrowu_message(int kind,struct monst*m,const char*fmt,const char*a,const char*b,const char*c,const char*d,const char*e){switch(kind){case 0:pline(fmt,a,b,c,d,e);break;case 1:pline_The(fmt,a,b,c,d,e);break;case 2:You(fmt,a,b,c,d,e);break;case 3:Your(fmt,a,b,c,d,e);break;case 4:You_hear(fmt,a,b,c,d,e);break;case 5:pline_mon(m,fmt,a,b,c,d,e);break;}}
void teleport_mthrowu_your1(const char*s){Your1(s);}
void teleport_mthrowu_impossible(const char*fmt,int n){impossible(fmt,n);}
void teleport_mthrowu_panic(const char*s){panic("%s",s);}
const char *teleport_mthrowu_common(int i){return i==0?something:i==1?Something:vision_clears;}

unsigned teleport_mthrowu_terrain_bit(struct rm*p){return p->wall_info;}
