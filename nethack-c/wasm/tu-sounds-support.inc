/* SOUNDS ABI only: native storage, packed fields, callbacks, original typed calls. */
#ifndef TELEPORT_REFERENCE_SOUNDS
struct sound_procs soundprocs;
#endif
static struct sound_procs teleport_sounds_source;
void*teleport_sounds_storage(int i){return &teleport_sounds_source;}
void*teleport_sounds_global(int i){switch(i){
case 0:return &u;
case 1:return &svl;
case 2:return &svr;
case 3:return &svc;
case 4:return &svq;
case 5:return &gu;
case 6:return &gy;
case 7:return &gi;
case 8:return &ga;
case 9:return &gc;
case 10:return &gn;
case 11:return &gm;
case 12:return &flags;
case 13:return &iflags;
case 14:return (void*)mons;
case 15:return (void*)objects;
case 16:return (void*)genders;
case 17:return &svd;
case 18:return &svm;
case 19:return &gv;
case 20:return &soundprocs;
case 21:return &sysopt;
default:return NULL;}}
void*teleport_sounds_equipment(int i){switch(i){case 0:return uwep;case 1:return uarm;case 2:return uarmc;case 3:return uarmh;case 4:return uarms;case 5:return uarmg;case 6:return uarmf;case 7:return uarmu;default:return NULL;}}
unsigned teleport_sounds_monster_bit(struct monst*p,int i){switch(i){case 0:return p->female;case 1:return p->isminion;case 2:return p->ispriest;case 3:return p->isshk;case 4:return p->mcan;case 5:return p->mcansee;case 6:return p->mcanmove;case 7:return p->mconf;case 8:return p->mflee;case 9:return p->mpeaceful;case 10:return p->msleeping;case 11:return p->mstun;case 12:return p->mtrapped;case 13:return p->mundetected;default:return 0;}}
void teleport_sounds_set_monster_bit(struct monst*p,int i,unsigned v){switch(i){case 0:p->female=v;break;case 1:p->isminion=v;break;case 2:p->ispriest=v;break;case 3:p->isshk=v;break;case 4:p->mcan=v;break;case 5:p->mcansee=v;break;case 6:p->mcanmove=v;break;case 7:p->mconf=v;break;case 8:p->mflee=v;break;case 9:p->mpeaceful=v;break;case 10:p->msleeping=v;break;case 11:p->mstun=v;break;case 12:p->mtrapped=v;break;case 13:p->mundetected=v;break;default:break;}}
unsigned teleport_sounds_object_bit(struct obj*p,int i){switch(i){case 0:return p->cursed;case 1:return p->bknown;default:return 0;}}
void teleport_sounds_set_object_bit(struct obj*p,int i,unsigned v){switch(i){case 0:p->cursed=v;break;case 1:p->bknown=v;break;default:break;}}
unsigned teleport_sounds_hero_bit(int i){switch(i){case 0:return u.uswallow;case 1:return u.uinwater;default:return u.uroleplay.deaf;}}
unsigned teleport_sounds_level_bit(int i){switch(i){case 0:return svl.level.flags.nfountains;case 1:return svl.level.flags.nsinks;case 2:return svl.level.flags.has_court;case 3:return svl.level.flags.has_swamp;case 4:return svl.level.flags.has_vault;case 5:return svl.level.flags.has_beehive;case 6:return svl.level.flags.has_morgue;case 7:return svl.level.flags.has_barracks;case 8:return svl.level.flags.has_zoo;case 9:return svl.level.flags.has_shop;case 10:return svl.level.flags.has_temple;default:return 0;}}
void teleport_sounds_set_level_bit(int i,unsigned v){switch(i){case 0:svl.level.flags.nfountains=v;break;case 1:svl.level.flags.nsinks=v;break;case 2:svl.level.flags.has_court=v;break;case 3:svl.level.flags.has_swamp=v;break;case 4:svl.level.flags.has_vault=v;break;case 5:svl.level.flags.has_beehive=v;break;case 6:svl.level.flags.has_morgue=v;break;case 7:svl.level.flags.has_barracks=v;break;case 8:svl.level.flags.has_zoo=v;break;case 9:svl.level.flags.has_shop=v;break;case 10:svl.level.flags.has_temple=v;break;default:break;}}
unsigned teleport_sounds_context_bit(int i){return svc.context.tribute.Deathnotice;}
void teleport_sounds_set_context_bit(int i,unsigned v){svc.context.tribute.Deathnotice=v;}
unsigned teleport_sounds_terrain_bit(int x,int y,int i){return levl[x][y].roomno;}
unsigned teleport_sounds_trap_bit(struct trap*t,int i){return t->tseen;}
void teleport_sounds_set_trap_bit(struct trap*t,int i,unsigned v){t->tseen=v;}
extern boolean teleport_sounds_callback_throne_mon_sound(struct monst*);
static boolean teleport_sounds_cb_0(struct monst*m){return teleport_sounds_callback_throne_mon_sound(m);}
extern boolean teleport_sounds_callback_beehive_mon_sound(struct monst*);
static boolean teleport_sounds_cb_1(struct monst*m){return teleport_sounds_callback_beehive_mon_sound(m);}
extern boolean teleport_sounds_callback_morgue_mon_sound(struct monst*);
static boolean teleport_sounds_cb_2(struct monst*m){return teleport_sounds_callback_morgue_mon_sound(m);}
extern boolean teleport_sounds_callback_zoo_mon_sound(struct monst*);
static boolean teleport_sounds_cb_3(struct monst*m){return teleport_sounds_callback_zoo_mon_sound(m);}
extern boolean teleport_sounds_callback_temple_priest_sound(struct monst*);
static boolean teleport_sounds_cb_4(struct monst*m){return teleport_sounds_callback_temple_priest_sound(m);}
extern boolean teleport_sounds_callback_oracle_sound(struct monst*);
static boolean teleport_sounds_cb_5(struct monst*m){return teleport_sounds_callback_oracle_sound(m);}
struct monst*teleport_sounds_get_iter(int i){switch(i){case 0:return get_iter_mons(teleport_sounds_cb_0);case 1:return get_iter_mons(teleport_sounds_cb_1);case 2:return get_iter_mons(teleport_sounds_cb_2);case 3:return get_iter_mons(teleport_sounds_cb_3);case 4:return get_iter_mons(teleport_sounds_cb_4);case 5:return get_iter_mons(teleport_sounds_cb_5);default:return NULL;}}
void teleport_sounds_call_init(uint64_t token){((void(*)(void))(uintptr_t)token)();}
void teleport_sounds_call_exit(uint64_t token,const char*s){((void(*)(const char*))(uintptr_t)token)(s);}
int teleport_sounds_rn2(int n,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("sounds.c",line,fn);return (rn2)(n);}
void teleport_sounds_message(int kind,const char*fmt,const char*a,const char*b,const char*c,const char*d){switch(kind){case 0:pline(fmt,a,b,c,d);break;case 1:You(fmt,a,b,c,d);break;case 2:You_hear(fmt,a,b,c,d);break;case 3:Your(fmt,a,b,c,d);break;case 4:You_cant(fmt,a,b,c,d);break;case 5:verbalize(fmt,a,b,c,d);break;default:pline_The(fmt,a,b,c,d);}}
void teleport_sounds_panic(const char*fmt,int value){panic(fmt,value);}
void teleport_sounds_sprintf(char*out,const char*fmt,const char*a,const char*b){Sprintf(out,fmt,a,b);}
void teleport_sounds_snprintf(int site,char*out,size_t size,const char*fmt,const char*a,const char*b){nh_snprintf("base_soundname_to_filename",site?2146:2144,out,size,fmt,a,b);}
const char*teleport_sounds_common_string(int i){return nothing_happens;}
static char teleport_sounds_literals[TELEPORT_SOUNDS_LITERAL_CAPACITY + sizeof "%s"];
void*teleport_sounds_literal_storage(void){return teleport_sounds_literals;}
size_t teleport_sounds_literal_capacity(void){return sizeof teleport_sounds_literals;}
