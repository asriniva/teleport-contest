/* Controlled world boundaries, actual catalogues and native allocation. */
#include "hack.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-dog-layout.h"
__typeof__(svm) svm;__typeof__(gu) gu;__typeof__(gp) gp;__typeof__(svc) svc;__typeof__(gd) gd;__typeof__(gc) gc;__typeof__(gh) gh;__typeof__(gb) gb;__typeof__(gn) gn;__typeof__(gm) gm;__typeof__(gf) gf;__typeof__(svu) svu;__typeof__(svr) svr;__typeof__(svq) svq;__typeof__(gy) gy;__typeof__(svd) svd;__typeof__(svl) svl;__typeof__(gv) gv;
struct you u;struct flag flags;struct instance_flags iflags;__typeof__(program_state) program_state;
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0}};
static struct monst monsters[64];static struct obj items[64];static stairway stairs;static struct trap fixture_trap;static struct eshk shops[64];static struct epri priests[64];static struct egd guards[64];static struct mextra extensions[64];
static int opts[64],rolls[512],roll_count,roll_idx,created,freed;static unsigned random_state;static char tracebuf[262144],caller[128];static seenV viewspace[ROWNO][COLNO];static seenV*viewrows[ROWNO];static void*growth;static anything anybuf;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
static int mid(struct monst*m){return m?(int)(m-monsters):-1;}static int oid(struct obj*o){return o?(int)(o-items):-1;}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);vfprintf(stderr,fmt,ap);va_end(ap);abort();}
void impossible(const char*fmt,...){char b[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
static void message(const char*kind,const char*fmt,va_list ap){char b[BUFSZ];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",kind,b);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);message("pline",fmt,ap);va_end(ap);}
void pline_mon(struct monst*m,const char*fmt,...){va_list ap;va_start(ap,fmt);message("mon",fmt,ap);va_end(ap);}
void You(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You",fmt,ap);va_end(ap);}
void There(const char*fmt,...){va_list ap;va_start(ap,fmt);message("There",fmt,ap);va_end(ap);}
void pline_The(const char*fmt,...){va_list ap;va_start(ap,fmt);message("The",fmt,ap);va_end(ap);}
void livelog_printf(long category,const char*fmt,...){va_list ap;va_start(ap,fmt);message("livelog",fmt,ap);va_end(ap);}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*file,int line,const char*fn){const char*b=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:file,line,fn);}
static int draw(int n){int v;if(n<=0)return 0;if(roll_idx<roll_count)v=(unsigned)rolls[roll_idx]%(unsigned)n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}roll_idx++;append("rng:%d:%d@%s;",n,v,caller);return v;}
int (rn2)(int n){return draw(n);}int (rnd)(int n){return draw(n)+1;}
static int free_count;
#ifdef free
#undef free
#endif
extern void free(void*);
void teleport_probe_free(void*p){if(p)free_count++;free(p);}
#define free teleport_probe_free
struct mextra*newmextra(void){struct mextra*e=(struct mextra*)alloc(sizeof *e);memset(e,0,sizeof *e);append("newmextra;");return e;}
void set_malign(struct monst*m){append("malign:%d:%d:%d;",mid(m),m->mtame,m->mpeaceful);}
struct monst*makemon(struct permonst*p,coordxy x,coordxy y,mmflags_nht mm){struct monst*m;append("make:%d:%d:%d:%u;",p?(int)(p-mons):-1,x,y,mm);if(opts[0])return NULL;if(opts[29]&&!growth)growth=malloc(32*1024*1024);m=&monsters[32+created++];m->data=p;m->mx=x;m->my=y;m->mhp=m->mhpmax=20;m->m_id=100+mid(m);m->mcanmove=m->mcansee=1;if(mm&MM_EDOG)newedog(m);return m;}
struct monst*christen_monst(struct monst*m,const char*s){append("name:%d:%s;",mid(m),s);return m;}
void iter_mons(void(*fn)(struct monst*)){struct monst*m;append("iterate;");for(m=fmon;m;m=m->nmon)fn(m);for(m=gm.migrating_mons;m;m=m->nmon)fn(m);for(m=gm.mydogs;m;m=m->nmon)fn(m);}
int probe_count(int);
void relmon(struct monst*m,struct monst**to){struct monst**p;append("relmon:%d;",mid(m));for(p=&fmon;*p;p=&(*p)->nmon)if(*p==m){*p=m->nmon;break;}m->nmon=*to;*to=m;if(opts[30]){opts[30]=0;append("borrow:%d;",probe_count(7));mon_catchup_elapsed_time(m,1);}if(opts[31]){opts[31]=0;mon_arrive(&monsters[1],2);append("nestedborrow:%d;",probe_count(7));}}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
int healmon(struct monst*m,int amount,int extra){append("heal:%d:%d:%d;",mid(m),amount,extra);m->mhp=min(m->mhpmax,m->mhp+amount);return amount;}
void place_monster(struct monst*m,coordxy x,coordxy y){append("place:%d:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;levl[x][y].typ=ROOM;svl.level.monsters[x][y]=m;}
void place_object(struct obj*o,coordxy x,coordxy y){append("placeobj:%d:%d:%d;",oid(o),x,y);o->ox=x;o->oy=y;o->where=OBJ_FLOOR;}
boolean rloc(struct monst*m,unsigned flags_){append("rloc:%d:%u;",mid(m),flags_);if(opts[1])return FALSE;m->mx=8;m->my=8;return TRUE;}
void rloc_to(struct monst*m,coordxy x,coordxy y){append("rloc_to:%d:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;}
int mnearto(struct monst*m,coordxy x,coordxy y,boolean moveother,unsigned flags_){append("near:%d:%d:%d:%d:%u;",mid(m),x,y,moveother,flags_);if(opts[1])return 0;m->mx=x;m->my=y;return 1;}
void mnexto(struct monst*m,unsigned flags_){append("next:%d:%u;",mid(m),flags_);m->mx=u.ux+1;m->my=u.uy;}
void mon_track_clear(struct monst*m){memset(m->mtrack,0,sizeof m->mtrack);append("trackclear:%d;",mid(m));}
anything*monst_to_any(struct monst*m){anybuf.a_monst=m;return &anybuf;}
char*in_rooms(coordxy x,coordxy y,int type){static char r[2];r[0]=opts[2]?ROOMOFFSET:0;r[1]=0;append("inrooms:%d:%d:%d;",x,y,type);return r;}
stairway*stairway_find(d_level*l){append("stair:%d:%d;",l->dnum,l->dlevel);return opts[3]?NULL:&stairs;}
stairway*stairway_find_dir(boolean up){append("stairdir:%d;",up);return opts[3]?NULL:&stairs;}
stairway*stairway_find_from(d_level*l,boolean ladder){append("stairfrom:%d:%d:%d;",l->dnum,l->dlevel,ladder);return opts[3]?NULL:&stairs;}
struct permonst*rndmonst_adj(int low,int high){append("randommon:%d:%d;",low,high);return opts[4]?NULL:&mons[PM_DOG];}
schar acurr(int attr){append("attribute:%d;",attr);return opts[5];}
boolean Resists_Elem(struct monst*m,int prop){append("resists:%d:%d;",mid(m),prop);return !!(opts[6]&(1<<prop));}
int mbirth_limit(int pm){append("limit:%d;",pm);return opts[7]?opts[7]:MAXMONNO;}
int spell_skilltype(int spell){append("skill:%d;",spell);return 1;}
int night(void){append("night;");return opts[8];}
long peek_at_iced_corpse_age(struct obj*o){append("age:%d;",oid(o));return o->age;}
boolean is_quest_artifact(struct obj*o){return o->oartifact!=0;}
boolean obj_resists(struct obj*o,int a,int b){append("objres:%d:%d:%d;",oid(o),a,b);return opts[9];}
int mon_has_amulet(struct monst*m){append("amulet:%d;",mid(m));return opts[10];}
boolean mon_hates_silver(struct monst*m){append("silver:%d;",mid(m));return opts[11];}
int dog_eat(struct monst*m,struct obj*o,coordxy x,coordxy y,boolean devour){append("eat:%d:%d:%d:%d:%d;",mid(m),oid(o),x,y,devour);return opts[12];}
void finish_meating(struct monst*m){append("finish:%d;",mid(m));m->meating=0;}
void m_unleash(struct monst*m,boolean feedback){append("unleash:%d:%d;",mid(m),feedback);m->mleashed=0;}
void discard_minvent(struct monst*m,boolean all){append("discard:%d:%d;",mid(m),all);m->minvent=NULL;}
void dealloc_monst(struct monst*m){append("dealloc:%d;",mid(m));m->mhp=0;freed++;}
void obfree(struct obj*o,struct obj*merge){append("obfree:%d:%d;",oid(o),oid(merge));o->where=OBJ_DELETED;freed++;}
void free_emin(struct monst*m){append("freeemin:%d;",mid(m));}
void deliver_obj_to_mon(struct monst*m,int n,unsigned long flags_){append("deliver:%d:%d:%lu;",mid(m),n,flags_);}
int minliquid(struct monst*m){append("liquid:%d;",mid(m));return opts[13];}
int mintrap(struct monst*m,unsigned flags_){append("trap:%d:%u;",mid(m),flags_);m->mtrapped=opts[14];return 0;}
int get_wormno(void){append("wormno;");return opts[15];}int count_wsegs(struct monst*m){append("segments:%d;",mid(m));return opts[16];}
void wormgone(struct monst*m){append("wormgone:%d;",mid(m));m->wormno=0;}void initworm(struct monst*m,int n){append("initworm:%d:%d;",mid(m),n);}
int canseemon(struct monst*m){append("canseemon:%d;",mid(m));return opts[17];}int sensemon(struct monst*m){append("sensemon:%d;",mid(m));return opts[18];}
boolean attacktype(struct permonst*p,int type){append("attack:%d:%d;",(int)(p-mons),type);return opts[19];}
boolean same_race(struct permonst*a,struct permonst*b){append("race:%d:%d;",(int)(a-mons),(int)(b-mons));return a->mlet==b->mlet;}
boolean sticks(struct permonst*p){append("sticks:%d;",(int)(p-mons));return opts[20];}
boolean In_W_tower(coordxy x,coordxy y,d_level*l){append("tower:%d:%d:%d:%d;",x,y,l->dnum,l->dlevel);return opts[21];}
boolean builds_up(d_level*l){append("buildsup:%d:%d;",l->dnum,l->dlevel);return opts[22];}
xint16 ledger_no(d_level*l){return l->dnum*100+l->dlevel;}xint16 ledger_to_dnum(xint16 n){return n/100;}xint16 ledger_to_dlev(xint16 n){return n%100;}schar depth(d_level*l){return l->dlevel;}
boolean levl_follower(struct monst*m){append("follower:%d;",mid(m));return opts[23];}boolean monnear(struct monst*m,coordxy x,coordxy y){append("monnear:%d:%d:%d;",mid(m),x,y);return opts[24];}
boolean somexy(struct mkroom*r,coord*c){append("somexy;");c->x=9;c->y=7;return !opts[25];}
struct obj*carrying(int type){append("carry:%d;",type);return opts[26]?&items[0]:NULL;}
const char*mon_pmname(struct monst*m){return m->data->pmnames[NEUTRAL];}
char*Monnam(struct monst*m){static char buf[BUFSZ];snprintf(buf,sizeof buf,"Monster%d",mid(m));return buf;}
char*xname(struct obj*o){static char buf[BUFSZ];snprintf(buf,sizeof buf,"Item%d",oid(o));return buf;}
char*Tobjnam(struct obj*o,const char*verb){static char buf[BUFSZ];snprintf(buf,sizeof buf,"Item%d %s",oid(o),verb);return buf;}
char*an(const char*s){static char buf[BUFSZ];snprintf(buf,sizeof buf,"a %s",s);return buf;}char*the(const char*s){static char buf[BUFSZ];snprintf(buf,sizeof buf,"the %s",s);return buf;}const char*body_part(int n){return "eye";}
int pm_to_cham(int pm){return opts[27]?pm:NON_PM;}boolean dmgtype(struct permonst*p,int type){return opts[28];}
void del_light_source(int a0,union any * a1){append("del_light_source;");}
void dismount_steed(int a0){append("dismount_steed;");}
void expels(struct monst * a0,struct permonst * a1,boolean a2){append("expels;");}
struct monst * find_pmmonst(int a0){append("find_pmmonst;");return NULL;}
void growl(struct monst * a0){append("growl;");}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool;");return 0;}
void m_into_limbo(struct monst * a0){append("m_into_limbo;");}
void make_happy_shk(struct monst * a0,boolean a1){append("make_happy_shk;");}
void make_happy_shoppers(boolean a0){append("make_happy_shoppers;");}
void mdrop_special_objs(struct monst * a0){append("mdrop_special_objs;");}
int mon_wield_item(struct monst * a0){append("mon_wield_item;");return 0;}
void newsym(coordxy a0,coordxy a1){append("newsym;");}
void picked_container(struct obj * a0){append("picked_container;");}
void put_saddle_on_mon(struct obj * a0,struct monst * a1){append("put_saddle_on_mon;");}
void redraw_worm(struct monst * a0){append("redraw_worm;");}
void restore_cham(struct monst * a0){append("restore_cham;");}
void see_monster_closeup(struct monst * a0,boolean a1){append("see_monster_closeup;");}
void set_residency(struct monst * a0,boolean a1){append("set_residency;");}
void unstuck(struct monst * a0){append("unstuck;");}
void vision_recalc(int a0){append("vision_recalc;");}
void wake_nearto(coordxy a0,coordxy a1,int a2){append("wake_nearto;");}
void yelp(struct monst * a0){append("yelp;");}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/dog.c"
#define PRIVATE(n) n
#else
extern int teleport_dog_test_pet_type(void),teleport_dog_test_mon_leave(struct monst*);
extern struct permonst*teleport_dog_test_pick_familiar_pm(struct obj*,boolean);
extern void teleport_dog_test_set_mon_lastmove(struct monst*);
extern boolean teleport_dog_test_keep_mon_accessible(struct monst*);
extern struct monst*teleport_dog_test_failed(void);
#define PRIVATE(n) teleport_dog_test_##n
#endif
void probe_reset(unsigned seed){int i;if(growth){free(growth);growth=NULL;}for(i=0;i<SIZE(monsters);i++)if(monsters[i].mextra&&EDOG(&monsters[i])){free(EDOG(&monsters[i]));EDOG(&monsters[i])=NULL;}for(i=0;i<SIZE(monsters);i++)if(monsters[i].mextra&&monsters[i].mextra!=&extensions[i])free(monsters[i].mextra);objects_globals_init();monst_globals_init();memset(&u,0,sizeof u);memset(&svm,0,sizeof svm);memset(&gu,0,sizeof gu);memset(&gp,0,sizeof gp);memset(&svc,0,sizeof svc);memset(&gd,0,sizeof gd);memset(&gc,0,sizeof gc);memset(&gh,0,sizeof gh);memset(&gb,0,sizeof gb);memset(&gn,0,sizeof gn);memset(&gm,0,sizeof gm);memset(&gf,0,sizeof gf);memset(&svu,0,sizeof svu);memset(&svr,0,sizeof svr);memset(&svq,0,sizeof svq);memset(&gy,0,sizeof gy);memset(&svd,0,sizeof svd);memset(&svl,0,sizeof svl);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(monsters,0,sizeof monsters);memset(items,0,sizeof items);memset(extensions,0,sizeof extensions);memset(shops,0,sizeof shops);memset(priests,0,sizeof priests);memset(guards,0,sizeof guards);memset(opts,0,sizeof opts);u.ux=10;u.uy=8;u.uz.dnum=1;u.uz.dlevel=4;u.uz0=u.uz;u.umonnum=u.umonster=PM_HUMAN;svm.moves=1000;gu.urole.petnum=NON_PM;gu.urole.mnum=PM_CAVE_DWELLER;svc.context.startingpet_typ=NON_PM;opts[5]=12;for(i=0;i<SIZE(monsters);i++){monsters[i].data=&mons[PM_DOG];monsters[i].m_id=100+i;monsters[i].mhp=10;monsters[i].mhpmax=20;monsters[i].mcanmove=monsters[i].mcansee=1;monsters[i].mx=6+i%10;monsters[i].my=5;}for(i=0;i<SIZE(items);i++){items[i].quan=1;items[i].otyp=TRIPE_RATION;items[i].oclass=FOOD_CLASS;items[i].corpsenm=PM_DOG;items[i].where=OBJ_INVENT;}for(i=0;i<ROWNO;i++){memset(viewspace[i],IN_SIGHT,sizeof viewspace[i]);viewrows[i]=viewspace[i];}gv.viz_array=viewrows;gy.youmonst.data=&mons[PM_HUMAN];stairs.sx=12;stairs.sy=9;fixture_trap.tx=14;fixture_trap.ty=10;fixture_trap.ttyp=MAGIC_PORTAL;astral_level.dnum=3;astral_level.dlevel=1;svu.updest.lx=2;svu.updest.hx=6;svu.updest.ly=3;svu.updest.hy=7;u.weapon_skills[1].skill=2;losedogs();created=freed=free_count=roll_count=roll_idx=0;random_state=seed;tracebuf[0]=caller[0]=0;}
void probe_option(int i,int v){opts[i]=v;}
void probe_moves(long v){svm.moves=v;}
void probe_mon(int i,int key,long v){struct monst*m=&monsters[i];switch(key){case 0:m->data=&mons[v];break;case 1:m->mtame=v;break;case 2:m->mpeaceful=v;break;case 3:m->mhp=v;break;case 4:m->mhpmax=v;break;case 5:m->mfrozen=v;break;case 6:m->mblinded=v;break;case 7:m->mfleetim=v;break;case 8:m->mtrapped=v;break;case 9:m->mconf=v;break;case 10:m->mstun=v;break;case 11:m->meating=v;break;case 12:m->mspec_used=v;break;case 13:m->mleashed=v;break;case 14:m->isminion=v;break;case 15:m->msleeping=v;break;case 16:m->mcanmove=v;break;case 17:m->mcansee=v;break;case 18:m->iswiz=v;break;case 19:m->isshk=v;break;case 20:m->ispriest=v;break;case 21:m->isgd=v;break;case 22:m->wormno=v;break;case 23:m->mstrategy=v;break;case 24:m->mlstmv=v;break;case 25:m->mstate=v;break;case 26:m->migflags=v;break;case 27:m->mux=v;break;case 28:m->muy=v;break;case 29:m->mx=v;break;case 30:m->my=v;break;case 31:m->mtrack[0].x=v;break;case 32:m->mtrack[0].y=v;break;case 33:m->mtrack[1].x=v;break;case 34:m->mtrack[1].y=v;break;case 35:m->mtrack[2].x=v;break;case 40:m->m_id=v;break;default:m->mtrack[2].y=v;}}
long probe_mon_value(int i,int k){struct monst*m=&monsters[i];switch(k){case 0:return m->data?(long)(m->data-mons):-1;case 1:return m->mtame;case 2:return m->mpeaceful;case 3:return m->mhp;case 4:return m->mhpmax;case 5:return m->mfrozen;case 6:return m->mblinded;case 7:return m->mfleetim;case 8:return m->mtrapped;case 9:return m->mconf;case 10:return m->mstun;case 11:return m->meating;case 12:return m->mspec_used;case 13:return m->mleashed;case 14:return m->isminion;case 15:return m->msleeping;case 16:return m->mcanmove;case 17:return m->mcansee;case 18:return m->iswiz;case 19:return m->isshk;case 20:return m->ispriest;case 21:return m->isgd;case 22:return m->wormno;case 23:return m->mstrategy;case 24:return m->mlstmv;case 25:return m->mstate;case 26:return m->migflags;case 27:return m->mux;case 28:return m->muy;case 29:return m->mx;case 30:return m->my;case 31:return m->mtrack[0].x;case 32:return m->mtrack[0].y;case 33:return m->mtrack[1].x;case 34:return m->mtrack[1].y;case 35:return m->mtrack[2].x;case 36:return m->mtrack[2].y;case 37:return mid(m->nmon);case 38:return oid(m->minvent);case 40:return m->m_id;default:return m->weapon_check;}}
void probe_object(int i,int type,int corpse,int blessed,int cursed){items[i].otyp=type;items[i].oclass=objects[type].oc_class;items[i].corpsenm=corpse;items[i].blessed=blessed;items[i].cursed=cursed;}
void probe_objfield(int i,int key,long v){struct obj*o=&items[i];switch(key){case 0:o->opoisoned=v;break;case 1:o->oerodeproof=v;break;case 2:o->oartifact=v;break;case 3:o->age=v;break;case 4:o->spe=v;break;case 5:o->nobj=v<0?NULL:&items[v];break;case 6:o->no_charge=v;break;case 7:o->cobj=v<0?NULL:&items[v];break;case 8:o->ox=v;break;case 9:o->oy=v;break;default:o->owornmask=v;}}
long probe_obj_value(int i,int k){struct obj*o=&items[i];switch(k){case 0:return o->otyp;case 1:return o->oclass;case 2:return o->corpsenm;case 3:return o->blessed;case 4:return o->cursed;case 5:return o->opoisoned;case 6:return o->no_charge;case 7:return o->oerodeproof;case 8:return o->where;case 9:return o->owornmask;case 10:return o->ox;case 11:return o->oy;case 12:return oid(o->nobj);case 13:return oid(o->cobj);case 14:return o->age;default:return o->spe;}}
void probe_edog(int i,int key,long v){struct monst*m=&monsters[i];if(!m->mextra||!EDOG(m))newedog(m);switch(key){case 0:EDOG(m)->hungrytime=v;break;case 1:EDOG(m)->mhpmax_penalty=v;break;case 2:EDOG(m)->abuse=v;break;case 3:EDOG(m)->killed_by_u=v;break;case 4:EDOG(m)->apport=v;break;default:EDOG(m)->revivals=v;}}
void probe_extension(int i,int dismiss){struct monst*m=&monsters[i];m->mextra=&extensions[i];m->mextra->eshk=&shops[i];m->mextra->epri=&priests[i];m->mextra->egd=&guards[i];shops[i].dismiss_kops=dismiss;shops[i].shoplevel=u.uz;priests[i].shrlevel=u.uz;guards[i].gdlevel=u.uz;}
void probe_level(int i,int dnum,int dlev){if(i==0){u.uz.dnum=dnum;u.uz.dlevel=dlev;}else if(i==1){astral_level.dnum=dnum;astral_level.dlevel=dlev;}else{qstart_level.dnum=dnum;qstart_level.dlevel=dlev;}}
void probe_hero(int key,long v){switch(key){case 0:gu.urole.petnum=v;break;case 1:gp.preferred_pet=v;break;case 2:gu.urole.mnum=v;break;case 3:flags.female=v;break;case 4:program_state.in_moveloop=v;break;case 5:u.uconduct.pets=v;break;case 6:u.uroleplay.pauper=v;break;case 7:u.usteed=v<0?NULL:&monsters[v];break;case 8:u.ustuck=v<0?NULL:&monsters[v];break;case 9:u.uswallow=v;break;case 10:u.umonnum=v;break;case 11:u.uhave.amulet=v;break;case 12:flags.moonphase=v;break;case 13:HAggravate_monster=v;break;case 14:HConflict=v;break;case 15:HHallucination=v;break;case 16:svq.quest_status.leader_m_id=v;break;case 17:iflags.debug_fuzzer=v;break;default:u.uevent.qexpelled=v;}}
void probe_chain(int kind,int index,int next){struct monst*m=index<0?NULL:&monsters[index];if(m)m->nmon=next<0?NULL:&monsters[next];switch(kind){case 0:fmon=m;break;case 1:gm.mydogs=m;break;case 2:gm.migrating_mons=m;break;case 3:gm.migrating_objs=index<0?NULL:&items[index];break;case 4:monsters[index].minvent=next<0?NULL:&items[next];break;default:gf.ftrap=&fixture_trap;}}
void probe_vital(int pm,int flags_){svm.mvitals[pm].mvflags=flags_;}
int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){roll_count=n;}int probe_rng_count(void){return roll_idx;}unsigned probe_rng_state(void){return random_state;}
const char*probe_trace(void){return tracebuf;}void probe_clear_trace(void){tracebuf[0]=caller[0]=0;}
void*probe_pointer(int kind,int i){if(kind==0)return &monsters[i];if(kind==1)return &items[i];if(kind==2)return monsters[i].mextra?EDOG(&monsters[i]):NULL;return &u;}
int probe_count(int k){switch(k){case 0:return created;case 1:return freed;case 2:return free_count;case 3:return mid(fmon);case 4:return mid(gm.mydogs);case 5:return mid(gm.migrating_mons);case 6:return oid(gm.migrating_objs);default:
#ifdef TELEPORT_REFERENCE_TU
return mid(failed_arrivals);
#else
return mid(teleport_dog_test_failed());
#endif
}}
long probe_hero_value(int k){switch(k){case 0:return u.uconduct.pets;case 1:return svc.context.startingpet_typ;case 2:return svc.context.startingpet_mid;case 3:return gp.petname_used;default:return gn.notonhead;}}
long probe_action(int op,int a,int b,long c){struct monst*m=a<0?NULL:&monsters[a],*res;struct permonst*pm;struct obj*o=b<0?NULL:&items[b];coord dest={8,9};switch(op){case 0:newedog(m);return 0;case 1:free_edog(m);return 0;case 2:initedog(m,b);return 0;case 3:return PRIVATE(pet_type)();case 4:pm=PRIVATE(pick_familiar_pm)(b<0?NULL:&items[b],c);return pm?(long)(pm-mons):-1;case 5:res=make_familiar(b<0?NULL:&items[b],8,9,c);return mid(res);case 6:return mid(makedog());case 7:PRIVATE(set_mon_lastmove)(m);return 0;case 8:update_mlstmv();return 0;case 9:losedogs();return 0;case 10:mon_arrive(m,b);return 0;case 11:mon_catchup_elapsed_time(m,c);return 0;case 12:return PRIVATE(mon_leave)(m);case 13:return PRIVATE(keep_mon_accessible)(m);case 14:keepdogs(a);return 0;case 15:migrate_to_level(m,b,c,c<0?NULL:&dest);return 0;case 16:discard_migrations();return 0;case 17:return dogfood(m,o);case 18:return tamedog(m,o,c);case 19:wary_dog(m,b);return 0;default:abuse_dog(m);return 0;}}
size_t probe_stack(void){return emscripten_stack_get_current();}
