#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
struct you u;
__typeof__(svl) svl;
__typeof__(gm) gm;
__typeof__(svm) svm;
__typeof__(svc) svc;
__typeof__(gf) gf;
__typeof__(gs) gs;
__typeof__(gy) gy;
__typeof__(flags) flags;
__typeof__(gu) gu;
__typeof__(svd) svd;
__typeof__(gv) gv;
struct obj *uamul,*uwep;
const struct c_color_names c_color_names={.c_black="black"};
static struct monst monsters[512];
static struct obj pool[64];
static struct mextra extras[8];
static struct emin minions[8];
static stairway stairs[8];
static struct trap traps[8];
static seenV vision[ROWNO][COLNO],*vision_rows[ROWNO];
static int opts[40],rolls[8192],nroll,rollidx,nextmon,nextobj,makecalls;
static unsigned seed;
static char tracebuf[4194304],statebuf[1048576],caller[128];
static coord spot;
static void *growth;
static int mid(struct monst *m){return m?(int)(m-monsters):-1;}
static int oid(struct obj *o){return o?(int)(o-pool):-1;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*3];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(You_feel) MSG(verbalize) MSG(impossible)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *f,int line,const char *fn){const char *b=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(rollidx<nroll)v=rolls[rollidx]%(unsigned)n;else{seed=seed*1664525U+1013904223U;v=(seed>>8)%(unsigned)n;}rollidx++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("nested-aggravate:%d;",has_aggravatables(&monsters[0]));}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}if(stage==1&&opts[34]){opts[34]=0;append("nested-nasty-begin;");int n=nasty(NULL);append("nested-nasty-end:%d;",n);}}
aligntyp mon_aligntyp(struct monst *m){append("alignment:%d;",mid(m));return m->isminion?EMIN(m)->min_align:m->data->maligntyp==A_NONE?A_NONE:sgn(m->data->maligntyp);}
boolean on_level(d_level *a,d_level *b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean builds_up(d_level *d){append("builds:%d:%d;",d->dnum,d->dlevel);return opts[10];}
boolean In_hell(d_level *d){append("hell:%d:%d;",d->dnum,d->dlevel);return d->dnum==7;}
boolean In_W_tower(coordxy x,coordxy y,d_level *d){append("tower:%d:%d:%d;",x,y,d->dnum);return opts[7]==2||(opts[7]==1&&x>=30);}
boolean inhistemple(struct monst *m){append("temple:%d;",mid(m));return opts[8];}
int inhishop(struct monst *m){append("shop:%d;",mid(m));return opts[9];}
boolean noteleport_level(struct monst *m){append("noport:%d;",mid(m));return opts[6];}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
boolean monnear(struct monst *m,coordxy x,coordxy y){append("near:%d:%d:%d;",mid(m),x,y);return dist2(m->mx,m->my,x,y)<=2;}
void rloc_to(struct monst *m,coordxy x,coordxy y){append("rloc-to:%d:%d:%d;",mid(m),x,y);if(m->mx>0&&m->mx<COLNO&&m->my>=0&&m->my<ROWNO&&svl.level.monsters[m->mx][m->my]==m)svl.level.monsters[m->mx][m->my]=NULL;m->mx=x;m->my=y;svl.level.monsters[x][y]=m;callback(2);}
boolean rloc(struct monst *m,unsigned f){append("rloc:%d:%u;",mid(m),f);rloc_to(m,35,10);return TRUE;}
int mnearto(struct monst *m,coordxy x,coordxy y,boolean moveother,unsigned flags){append("mnearto:%d:%d:%d:%d:%u;",mid(m),x,y,moveother,flags);if(opts[5])rloc_to(m,x,y);return opts[5];}
void mnexto(struct monst *m,unsigned f){append("mnexto:%d:%u;",mid(m),f);rloc_to(m,u.ux+1,u.uy);}
int healmon(struct monst *m,int n,int over){append("heal:%d:%d:%d;",mid(m),n,over);m->mhp+=n;if(m->mhp>m->mhpmax)m->mhp=m->mhpmax;callback(3);return n;}
void expels(struct monst *m,struct permonst *p,boolean b){append("expel:%d:%d:%d;",mid(m),monsndx(p),b);u.uswallow=0;u.ustuck=NULL;}
char *Monnam(struct monst *m){static char b[8][BUFSZ];static unsigned i;char *s=b[i++%8];snprintf(s,BUFSZ,"monster%d",mid(m));return s;}
char *doname(struct obj *o){static char b[8][BUFSZ];static unsigned i;char *s=b[i++%8];snprintf(s,BUFSZ,"object%d",oid(o));return s;}
char *distant_name(struct obj *o,char *(*f)(struct obj*)){append("distant:%d;",oid(o));return f(o);}
char *Tobjnam(struct obj *o,const char *verb){static char b[BUFSZ];snprintf(b,sizeof b,"Object%d %s",oid(o),verb);return b;}
void obj_extract_self(struct obj *o){struct obj **p=&fobj;append("extract:%d;",oid(o));while(*p){if(*p==o){*p=o->nobj;break;}p=&(*p)->nobj;}o->nobj=NULL;o->where=OBJ_FREE;callback(4);}
int mpickobj(struct monst *m,struct obj *o){append("pickup:%d:%d;",mid(m),oid(o));o->nobj=m->minvent;m->minvent=o;o->where=OBJ_MINVENT;o->ocarry=m;callback(5);return 0;}
struct obj *mksobj(int typ,boolean init,boolean art){struct obj *o=&pool[nextobj++];append("object:%d:%d:%d:%d;",nextobj-1,typ,init,art);memset(o,0,sizeof *o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;return o;}
int add_to_minv(struct monst *m,struct obj *o){return mpickobj(m,o);}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
static struct monst *make_one(struct permonst *p,coordxy x,coordxy y){struct monst *m;if(nextmon>=512)abort();m=&monsters[nextmon++];memset(m,0,sizeof *m);m->data=p;m->m_id=100+mid(m);m->mx=x;m->my=y;m->mux=u.ux;m->muy=u.uy;m->mhp=m->mhpmax=30;m->mcanmove=1;m->mpeaceful=1;m->mstrategy=~0UL;m->iswiz=p==&mons[PM_WIZARD_OF_YENDOR];if(m->iswiz)svc.context.no_of_wizards++;m->nmon=fmon;fmon=m;return m;}
struct monst *makemon(struct permonst *p,coordxy x,coordxy y,mmflags_nht f){struct monst *m;int i;makecalls++;append("make:%d:%d:%d:%lu;",p?monsndx(p):-1,x,y,(unsigned long)f);if(opts[1]==1||(opts[1]==2&&p)||(opts[1]==3&&!p)||makecalls<=opts[27])return NULL;m=make_one(p?p:&mons[opts[2]],x,y);for(i=0;i<opts[3];i++)make_one(&mons[PM_HUMAN],x,y);callback(1);return m;}
void set_malign(struct monst *m){append("malign:%d;",mid(m));}
int monster_census(boolean b){int n=0;struct monst *m;for(m=fmon;m;m=m->nmon)if(!DEADMONSTER(m))n++;append("census:%d:%d;",b,n);return n;}
int msummon(struct monst *m){int i;append("summon:%d;",mid(m));for(i=0;i<opts[16];i++)make_one(&mons[PM_HORNED_DEVIL],u.ux,u.uy);callback(6);return opts[16];}
int big_to_little(int pm){append("smaller:%d;",pm);if(opts[21]>=0)return opts[21];if(pm==PM_ARCH_LICH)return PM_MASTER_LICH;if(pm==PM_MASTER_MIND_FLAYER)return PM_MIND_FLAYER;return pm;}
boolean attacktype(struct permonst *p,int at){int i;append("attack:%d:%d;",monsndx(p),at);if(opts[15]>=0)return opts[15];for(i=0;i<NATTK;i++)if(p->mattk[i].aatyp==at)return TRUE;return FALSE;}
boolean enexto(coord *c,coordxy x,coordxy y,struct permonst *p){append("next:%d:%d:%d;",x,y,monsndx(p));c->x=x+1;c->y=y+1;callback(7);return opts[4];}
struct monst *unmakemon(struct monst *m,mmflags_nht f){struct monst **p=&fmon;append("unmake:%d:%lu;",mid(m),(unsigned long)f);while(*p&&*p!=m)p=&(*p)->nmon;if(*p)*p=m->nmon;m->mhp=0;return NULL;}
void mon_catchup_elapsed_time(struct monst *m,long n){append("catchup:%d:%ld;",mid(m),n);if(opts[13]){m->msleeping=0;m->mfrozen=0;m->mcanmove=1;}callback(8);}
void mon_arrive(struct monst *m,int how){append("arrive:%d:%d:remaining=%d;",mid(m),how,mid(gm.migrating_mons));if(opts[12])m->mx=0;else{m->mx=20;m->my=10;m->nmon=fmon;fmon=m;}if(opts[14]){monsters[7].nmon=gm.migrating_mons;gm.migrating_mons=&monsters[7];}callback(9);}
const char *hcolor(const char *s){append("color:%s;",s);return s;}
void rndcurse(void){append("curse;");callback(10);}
void com_pager(const char *s){append("pager:%s;",s);callback(11);}
void wake_nearto(coordxy x,coordxy y,int d){append("wake:%d:%d:%d;",x,y,d);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/wizard.c"
#else
extern short teleport_wizard_test_which(int);
extern boolean teleport_wizard_test_has(struct monst*,short),teleport_wizard_test_you(int);
extern struct monst *teleport_wizard_test_other(struct monst*,short);
extern struct obj *teleport_wizard_test_ground(short);
extern unsigned long teleport_wizard_test_target(int,struct monst*),teleport_wizard_test_strategy(struct monst*);
#define which_arti teleport_wizard_test_which
#define mon_has_arti teleport_wizard_test_has
#define other_mon_has_arti teleport_wizard_test_other
#define on_ground teleport_wizard_test_ground
#define you_have teleport_wizard_test_you
#define target_on teleport_wizard_test_target
#define strategy teleport_wizard_test_strategy
#endif
#include "tu-wizard-layout.h"
void probe_reset(unsigned s){int i,x,y;if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&gm,0,sizeof gm);memset(&svm,0,sizeof svm);memset(&svc,0,sizeof svc);memset(&gf,0,sizeof gf);memset(&gs,0,sizeof gs);memset(&gy,0,sizeof gy);memset(&flags,0,sizeof flags);memset(&gu,0,sizeof gu);memset(&svd,0,sizeof svd);memset(&gv,0,sizeof gv);memset(monsters,0,sizeof monsters);memset(pool,0,sizeof pool);memset(extras,0,sizeof extras);memset(minions,0,sizeof minions);memset(stairs,0,sizeof stairs);memset(traps,0,sizeof traps);memset(opts,0,sizeof opts);uamul=uwep=NULL;objects_globals_init();monst_globals_init();u.ux=u.uy=10;u.ulevel=9;u.uhp=20;u.uz.dnum=1;u.uz.dlevel=2;astral_level.dnum=8;astral_level.dlevel=9;rogue_level.dnum=6;rogue_level.dlevel=7;sanctum_level.dnum=7;sanctum_level.dlevel=8;gy.youmonst.data=&mons[PM_HUMAN];for(i=0;i<8;i++){monsters[i].data=&mons[PM_WIZARD_OF_YENDOR];monsters[i].m_id=100+i;monsters[i].mhp=monsters[i].mhpmax=30;monsters[i].mx=20+i;monsters[i].my=10;monsters[i].mux=10;monsters[i].muy=10;monsters[i].mcanmove=1;monsters[i].iswiz=1;}for(i=0;i<64;i++){pool[i].otyp=ROCK;pool[i].quan=1;pool[i].where=OBJ_FREE;}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)vision[y][x]=COULD_SEE|IN_SIGHT;for(y=0;y<ROWNO;y++)vision_rows[y]=vision[y];gv.viz_array=vision_rows;opts[0]=opts[4]=opts[5]=1;opts[2]=PM_HUMAN;opts[15]=opts[21]=-1;opts[16]=2;nextmon=8;nextobj=16;rollidx=nroll=makecalls=0;seed=s;svm.moves=100;spot.x=spot.y=-99;tracebuf[0]=statebuf[0]=caller[0]=0;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;}
int *probe_rng_pointer(void){return rolls;}
void probe_rng_length(int n){nroll=n;rollidx=0;}
int probe_rng_count(void){return rollidx;}
unsigned probe_rng_state(void){return seed;}
void probe_object(int i,int k,long v){struct obj *o=&pool[i];switch(k){case 0:o->otyp=v;o->oclass=objects[v].oc_class;break;case 1:o->oartifact=v;break;case 2:o->ox=v;break;case 3:o->oy=v;break;case 4:o->nobj=v<0?NULL:&pool[v];break;case 5:fobj=v?o:NULL;break;case 6:uamul=v?o:NULL;break;case 7:uwep=v?o:NULL;break;case 8:monsters[v].minvent=o;break;case 9:o->where=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.uhave.amulet=v;break;case 3:u.uhave.bell=v;break;case 4:u.uhave.menorah=v;break;case 5:u.uhave.book=v;break;case 6:u.uhave.questart=v;break;case 7:u.uevent.invoked=v;break;case 8:u.uevent.udemigod=v;break;case 9:u.uswallow=v;break;case 10:u.ustuck=v<0?NULL:&monsters[v];break;case 11:u.uhp=v;break;case 12:u.ulevel=v;break;case 13:svc.context.no_of_wizards=v;break;case 14:svc.context.made_amulet=v;break;case 15:svm.moves=v;break;case 16:u.uz.dnum=v;break;case 17:u.uz.dlevel=v;break;case 18:u.uroleplay.deaf=v;break;case 19:traps[0].ttyp=v;break;case 20:traps[0].tx=v;break;case 21:traps[0].ty=v;break;case 22:gf.ftrap=v?&traps[0]:NULL;break;case 23:traps[0].ntrap=v?&traps[1]:NULL;traps[1].ttyp=MAGIC_PORTAL;traps[1].tx=32;traps[1].ty=10;break;case 24:u.udg_cnt=v;break;case 25:memset(vision,v?IN_SIGHT:0,sizeof vision);break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_monster_field(int i,int k,unsigned long v){struct monst *m=&monsters[i];switch(k){case 0:m->data=&mons[v];break;case 1:m->mhp=v;break;case 2:m->mhpmax=v;break;case 3:m->mx=v;break;case 4:m->my=v;break;case 5:m->mstrategy=v;break;case 6:m->minvent=(long)v<0?NULL:&pool[v];break;case 7:m->nmon=(long)v<0?NULL:&monsters[v];break;case 8:fmon=v?m:NULL;break;case 9:gm.migrating_mons=v?m:NULL;break;case 10:m->iswiz=v;break;case 11:m->isshk=v;break;case 12:m->ispriest=v;break;case 13:m->msleeping=v;break;case 14:m->mcanmove=v;break;case 15:m->mfrozen=v;break;case 16:m->mpeaceful=v;break;case 17:m->mflee=v;break;case 18:m->mtame=v;break;case 19:m->mlstmv=v;break;case 20:m->mgoal.x=v;break;case 21:m->mgoal.y=v;break;case 22:m->mux=v;break;case 23:m->muy=v;break;case 24:m->isminion=v;m->mextra=&extras[i];extras[i].emin=&minions[i];minions[i].min_align=A_LAWFUL;break;case 25:minions[i].renegade=v;break;case 26:svl.level.monsters[m->mx][m->my]=v?m:NULL;break;}}
void probe_stair(int i,int sx,int sy,int up,int ladder,int dnum,int next){stairway *s=&stairs[i];s->sx=sx;s->sy=sy;s->up=up;s->isladder=ladder;s->tolev.dnum=dnum;s->next=next<0?NULL:&stairs[next];if(i==0)gs.stairs=s;}
void probe_vital(int pm,int flags){svm.mvitals[pm].mvflags=flags;}
long probe_action(int op,int i,int a,int b,int c){struct monst *m=i<0?NULL:&monsters[i];switch(op){case 0:amulet();return 0;case 1:return mon_has_amulet(m);case 2:return mon_has_special(m);case 3:return which_arti(a);case 4:return mon_has_arti(m,a);case 5:return mid(other_mon_has_arti(m,a));case 6:return oid(on_ground(a));case 7:return you_have(a);case 8:return target_on(a,m);case 9:return strategy(m);case 10:choose_stairs(&spot.x,&spot.y,a);return 0;case 11:return tactics(m);case 12:return has_aggravatables(m);case 13:aggravate();return 0;case 14:clonewiz();return 0;case 15:return pick_nasty(a);case 16:return nasty(m);case 17:resurrect();return 0;case 18:intervene();return 0;case 19:wizdeadorgone();return 0;case 20:cuss(m);return 0;}return -999;}
void *probe_pointer(int k,int i){switch(k){case 0:return &pool[i];case 1:return &monsters[i];case 2:return &mons[i];case 3:return &u;case 4:return &spot;case 5:return &stairs[i];case 6:return &traps[i];case 7:return &gm.migrating_mons;case 8:return &fmon;case 9:return &svm.mvitals[i];}return NULL;}
const void *probe_table_pointer(int table){
#ifdef TELEPORT_REFERENCE_TU
switch(table){case 0:return nasties;case 1:return wizapp;case 2:return random_insult;case 3:return random_malediction;}
#endif
return NULL;}
int probe_table_count(int table){
#ifdef TELEPORT_REFERENCE_TU
switch(table){case 0:return SIZE(nasties);case 1:return SIZE(wizapp);case 2:return SIZE(random_insult);case 3:return SIZE(random_malediction);}
#endif
return 0;}
const char *probe_snapshot(void){int i;char *p=statebuf;p+=sprintf(p,"hero:%d:%d:%d:%u:%u:%u:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld:%d:%d;heads:%d:%d:%d;spot:%d:%d;",u.ux,u.uy,u.uhp,u.udg_cnt,svc.context.no_of_wizards,svc.context.made_amulet,u.uhave.amulet,u.uhave.bell,u.uhave.menorah,u.uhave.book,u.uhave.questart,u.uevent.invoked,u.uevent.udemigod,u.uswallow,mid(u.ustuck),svm.moves,nextmon,makecalls,mid(fmon),mid(gm.migrating_mons),oid(fobj),spot.x,spot.y);for(i=1;i<=LAST_PROP;i++)p+=sprintf(p,"p%d:%ld:%ld:%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);for(i=0;i<nextmon;i++){struct monst *m=&monsters[i];p+=sprintf(p,"m%d:%d:%u:%d:%d:%d:%d:%lu:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%u;",i,monsndx(m->data),m->m_id,m->mx,m->my,m->mhp,m->mhpmax,m->mstrategy,m->mgoal.x,m->mgoal.y,oid(m->minvent),mid(m->nmon),m->iswiz,m->isshk,m->ispriest,m->msleeping,m->mcanmove,m->mfrozen,m->mpeaceful,m->mtame,m->mlstmv,m->mflee,m->mavenge,m->mrevived,m->mspec_used,m->mux,m->muy,m->m_ap_type,m->mappearance);}for(i=0;i<nextobj;i++){struct obj *o=&pool[i];p+=sprintf(p,"o%d:%d:%d:%d:%d:%d:%d:%d;",i,o->otyp,o->oartifact,o->ox,o->oy,o->where,oid(o->nobj),o->where==OBJ_MINVENT?mid(o->ocarry):-1);}return statebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
