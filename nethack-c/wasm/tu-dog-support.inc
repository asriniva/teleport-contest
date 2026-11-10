/* DOG ABI only: native storage/packed fields/typed calls; all pet policy is JS. */
extern void teleport_dog_callback_lastmove(struct monst*);
static void teleport_dog_lastmove_trampoline(struct monst*m){teleport_dog_callback_lastmove(m);}
void teleport_dog_iter(void){iter_mons(teleport_dog_lastmove_trampoline);}
void*teleport_dog_global(int i){switch(i){
case 0:return &u;
case 1:return &svm;
case 2:return &gu;
case 3:return &gp;
case 4:return &svc;
case 5:return &gd;
case 6:return &gc;
case 7:return &gh;
case 8:return &gb;
case 9:return &gn;
case 10:return &gm;
case 11:return &gf;
case 12:return &svu;
case 13:return &svr;
case 14:return &svq;
case 15:return &gy;
case 16:return &svd;
case 17:return &svl;
case 18:return &flags;
case 19:return &iflags;
case 20:return &program_state;
case 21:return (void*)genders;
case 22:return (void*)mons;
case 23:return (void*)objects;
case 24:return &gv;
default:return NULL;}}
unsigned teleport_dog_monster_bit(struct monst*p,int i){switch(i){case 0:return p->female;case 1:return p->isgd;case 2:return p->isminion;case 3:return p->ispriest;case 4:return p->isshk;case 5:return p->iswiz;case 6:return p->mavenge;case 7:return p->mblinded;case 8:return p->mcanmove;case 9:return p->mconf;case 10:return p->mflee;case 11:return p->mfleetim;case 12:return p->mfrozen;case 13:return p->mleashed;case 14:return p->mpeaceful;case 15:return p->msleeping;case 16:return p->mstun;case 17:return p->mtrapped;case 18:return p->wormno;case 19:return p->mcansee;default:return 0;}}
void teleport_dog_set_monster_bit(struct monst*p,int i,unsigned v){switch(i){case 0:p->female=v;break;case 1:p->isgd=v;break;case 2:p->isminion=v;break;case 3:p->ispriest=v;break;case 4:p->isshk=v;break;case 5:p->iswiz=v;break;case 6:p->mavenge=v;break;case 7:p->mblinded=v;break;case 8:p->mcanmove=v;break;case 9:p->mconf=v;break;case 10:p->mflee=v;break;case 11:p->mfleetim=v;break;case 12:p->mfrozen=v;break;case 13:p->mleashed=v;break;case 14:p->mpeaceful=v;break;case 15:p->msleeping=v;break;case 16:p->mstun=v;break;case 17:p->mtrapped=v;break;case 18:p->wormno=v;break;case 19:p->mcansee=v;break;default:break;}}
unsigned teleport_dog_object_bit(struct obj*p,int i){switch(i){case 0:return p->blessed;case 1:return p->cursed;case 2:return p->no_charge;case 3:return p->oerodeproof;case 4:return p->opoisoned;default:return 0;}}
void teleport_dog_set_object_bit(struct obj*p,int i,unsigned v){switch(i){case 0:p->blessed=v;break;case 1:p->cursed=v;break;case 2:p->no_charge=v;break;case 3:p->oerodeproof=v;break;case 4:p->opoisoned=v;break;default:break;}}
unsigned teleport_dog_hero_bit(int i){switch(i){case 0:return u.uroleplay.pauper;case 1:return u.uhave.amulet;case 2:return u.uevent.qexpelled;default:return u.uswallow;}}
unsigned teleport_dog_edog_bit(struct edog*p,int i){return p->killed_by_u;}
void teleport_dog_set_edog_bit(struct edog*p,int i,unsigned v){p->killed_by_u=v;}
unsigned teleport_dog_eshk_bit(struct eshk*p,int i){return p->dismiss_kops;}
void teleport_dog_set_eshk_bit(struct eshk*p,int i,unsigned v){p->dismiss_kops=v;}
unsigned teleport_dog_class_bit(int n,int i){return objects[n].oc_material;}
unsigned teleport_dog_trap_bit(struct trap*p,int i){return p->ttyp;}
int teleport_dog_rn2(int n,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("dog.c",line,fn);return (rn2)(n);}
int teleport_dog_rnd(int n,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("dog.c",line,fn);return (rnd)(n);}
void teleport_dog_assert(int condition){if(!condition)__assert_fail("ismnum(mndx)","dog.c",111,"pick_familiar_pm");}
void teleport_dog_message(int kind,struct monst*m,const char*fmt,const char*a,const char*b,const char*c){switch(kind){case 0:pline(fmt,a,b,c);break;case 1:pline_mon(m,fmt,a,b,c);break;case 2:pline_The(fmt,a,b,c);break;case 3:There(fmt,a,b,c);break;case 4:You(fmt,a,b,c);break;case 5:impossible(fmt,a,b,c);break;default:panic(fmt,a,b,c);}}
void teleport_dog_livelog(long cat,const char*fmt,const char*a,const char*b){livelog_printf(cat,fmt,a,b);}
void teleport_dog_free(void*p){free(p);}
static char teleport_dog_literals[TELEPORT_DOG_LITERAL_CAPACITY];
void*teleport_dog_literal_storage(void){return teleport_dog_literals;}
size_t teleport_dog_literal_capacity(void){return sizeof teleport_dog_literals;}
