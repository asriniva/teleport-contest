#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
struct you u;
__typeof__(gy) gy;
__typeof__(svl) svl;
__typeof__(gu) gu;
__typeof__(gi) gi;
__typeof__(gv) gv;
__typeof__(disp) disp;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
struct obj *uwep,*uarm,*uarmg,*uarmf,*uball;
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind."};
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
static struct monst monsters[8];
static struct mextra extras[8];
static struct obj pool[16];
static struct trap traps[COLNO][ROWNO];
static int opts[40],rolls[4096],nroll,rollidx,nextobj,enexto_calls;
static unsigned seed;
static char tracebuf[2097152],statebuf[131072],caller[128];
static coord spot;
static seenV vision[ROWNO][COLNO],*vision_rows[ROWNO];
static void *growth;
static int mid(struct monst *m){return m?(m==&gy.youmonst?-2:(int)(m-monsters)):-1;}
static int oid(struct obj *o){return o?(int)(o-pool):-1;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*3];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(Your) MSG(You_cant) MSG(impossible)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *f,int line,const char *fn){const char *b=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(rollidx<nroll)v=rolls[rollidx]%(unsigned)n;else{seed=seed*1664525U+1013904223U;v=(seed>>8)%(unsigned)n;}rollidx++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("nested-ride:%d;",can_ride(&monsters[0]));}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}if(opts[32]==stage){opts[32]=0;monsters[0].mhp=0;append("callback-death;");}}
boolean debugcore(const char *f,boolean b){const char *s=strrchr(f,'/');append("debugcore:%s:%d;",s?s+1:f,b);return opts[33];}
boolean has_ceiling(d_level *d){append("ceiling:%d:%d;",d->dnum,d->dlevel);return opts[29];}
boolean is_art(struct obj *o,int a){append("artifact:%d:%d;",oid(o),a);return o&&o->oartifact==a;}
boolean poly_when_stoned(struct permonst *p){append("stone-poly:%d;",monsndx(p));return opts[28];}
boolean u_handsy(void){append("hands;");return opts[1];}
int getdir(const char *q){append("getdir:%s;",q?q:"NULL");return opts[2];}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
schar acurr(int a){append("attribute:%d;",a);return a==A_CHA?opts[4]:opts[3];}
int canseemon(struct monst *m){append("cansee:%d;",mid(m));return opts[5];}
int sensemon(struct monst *m){append("sense:%d;",mid(m));return opts[6];}
char yn_function(const char *q,const char *choices,char def,boolean h){append("yn:%s:%s:%d:%d:%d;",q,choices,def,h,opts[7]);callback(1);return opts[7];}
const char ynchars[]="yn";
struct obj *which_armor(struct monst *m,long mask){struct obj *o;append("armor:%d:%ld;",mid(m),mask);for(o=m->minvent;o;o=o->nobj)if(o->owornmask&mask)return o;return NULL;}
int Mgender(struct monst *m){append("gender:%d;",mid(m));return m->female?FEMALE:MALE;}
const char *pmname(struct permonst *p,int g){return p->pmnames[g] ? p->pmnames[g]:p->pmnames[NEUTRAL];}
int pronoun_gender(struct monst *m,unsigned f){append("pronoun:%d:%u;",mid(m),f);return opts[8]?3:m->female?1:0;}
static char *mname(struct monst *m){static char b[8][BUFSZ];static unsigned i;char *s=b[i++%8];snprintf(s,BUFSZ,"monster%d",mid(m));return s;}
char *mon_nam(struct monst *m){return mname(m);}
char *Monnam(struct monst *m){return mname(m);}
char *YMonnam(struct monst *m){return mname(m);}
char *y_monnam(struct monst *m){return mname(m);}
char *a_monnam(struct monst *m){return mname(m);}
char *minimal_monnam(struct monst *m,boolean b){return mname(m);}
char *x_monnam(struct monst *m,int article,const char *adj,int suppress,boolean b){static char s[BUFSZ];append("xname:%d:%d:%s:%d:%d;",mid(m),article,adj?adj:"NULL",suppress,b);snprintf(s,sizeof s,"your monster%d",mid(m));return s;}
char *monverbself(struct monst *m,char *s,const char *verb,const char *other){append("verbself:%d:%s:%s:%s;",mid(m),s,verb,other?other:"NULL");strcat(s," rouses itself");return s;}
char *an(const char *s){static char b[BUFSZ*2];snprintf(b,sizeof b,"a %s",s);return b;}
void exercise(int a,boolean b){append("exercise:%d:%d;",a,b);}
boolean objdescr_is(struct obj *o,const char *s){append("description:%d:%s;",oid(o),s);return opts[9];}
void remove_worn_item(struct obj *o,boolean b){append("unwear:%d:%d;",oid(o),b);o->owornmask=0;}
void freeinv(struct obj *o){struct obj **p=&gi.invent;append("freeinv:%d;",oid(o));while(*p){if(*p==o){*p=o->nobj;break;}p=&(*p)->nobj;}o->nobj=NULL;o->where=OBJ_FREE;callback(2);}
struct obj *mksobj(int typ,boolean init,boolean art){struct obj *o;append("makeobj:%d:%d:%d;",typ,init,art);o=&pool[nextobj++];memset(o,0,sizeof *o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;callback(3);return o;}
void fully_identify_obj(struct obj *o){append("identify:%d;",oid(o));o->known=o->dknown=o->bknown=1;}
int mpickobj(struct monst *m,struct obj *o){append("pickup:%d:%d;",mid(m),oid(o));o->nobj=m->minvent;m->minvent=o;o->where=OBJ_MINVENT;o->ocarry=m;callback(4);return 0;}
void update_mon_extrinsics(struct monst *m,struct obj *o,boolean a,boolean b){append("extrinsics:%d:%d:%d:%d;",mid(m),oid(o),a,b);callback(5);}
void instapetrify(const char *s){append("petrify:%s;",s);}
int polymon(int p){append("polymon:%d;",p);if(opts[11])gy.youmonst.data=&mons[p];return opts[11];}
void legs_in_no_shape(const char *s,boolean b){append("legs:%s:%d;",s,b);}
void heal_legs(int n){append("heal-legs:%d:%d;",n,mid(u.usteed));HWounded_legs=EWounded_legs=0;}
int near_capacity(void){append("capacity;");return opts[12];}
boolean test_move(coordxy x,coordxy y,coordxy dx,coordxy dy,int mode){append("move-test:%d:%d:%d:%d:%d;",x,y,dx,dy,mode);callback(6);return opts[13];}
struct trap *t_at(coordxy x,coordxy y){append("trap:%d:%d;",x,y);return traps[x][y].ttyp?&traps[x][y]:NULL;}
const char *trapname(int t,boolean b){append("trapname:%d:%d;",t,b);return "trap";}
void m_unleash(struct monst *m,boolean b){append("unleash:%d:%d;",mid(m),b);m->mleashed=0;}
const char *hliquid(const char *s){return s;}
const char *body_part(int p){return "leg";}
void losehp(int n,const char *s,schar how){append("damage:%d:%s:%d;",n,s,how);u.uhp-=n;}
void set_wounded_legs(long sides,int t){append("wound:%ld:%d;",sides,t);HWounded_legs=t;EWounded_legs=sides;}
void use_skill(int p,int n){append("skill:%d:%d;",p,n);u.weapon_skills[p].advance+=n;}
void finish_meating(struct monst *m){append("finish-meal:%d;",mid(m));m->meating=0;}
void steed_vs_stealth(void){append("stealth:%d:%d:%d;",mid(u.usteed),!!Flying,!!Levitation);if(u.usteed&&!Flying)BStealth|=FROMOUTSIDE;else BStealth&=~FROMOUTSIDE;callback(7);}
void teleds(coordxy x,coordxy y,int f){append("teleds:%d:%d:%d:%d:%d;",x,y,f,mid(u.usteed),gi.in_steed_dismounting);u.ux=x;u.uy=y;u.utrap=0;if(u.usteed){u.usteed->mx=x;u.usteed->my=y;}callback(8);}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
const char *u_locomotion(const char *s){append("locomotion:%s:%d:%d:%d;",s,mid(u.usteed),!!Flying,!!Levitation);callback(9);return s;}
boolean accessible(coordxy x,coordxy y){append("accessible:%d:%d;",x,y);return opts[14]&&levl[x][y].typ==ROOM;}
struct obj *sobj_at(int t,coordxy x,coordxy y){append("sobj:%d:%d:%d;",t,x,y);return opts[15]?&pool[15]:NULL;}
boolean enexto(coord *c,coordxy x,coordxy y,struct permonst *p){boolean yes=enexto_calls++>=opts[17]&&opts[16];append("enexto:%d:%d:%d:%d;",x,y,monsndx(p),yes);if(yes){c->x=opts[18];c->y=opts[19];}callback(10);return yes;}
int xytodir(int x,int y){static const int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,-1,-1,-1,0,1,1,1};int i;for(i=0;i<8;i++)if(dx[i]==x&&dy[i]==y)return i;return DIR_ERR;}
void dirtocoord(coord *c,int i){static const int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,-1,-1,-1,0,1,1,1};c->x=dx[i];c->y=dy[i];}
const char *directionname(int d){static const char *names[]={"W","NW","N","NE","E","SE","S","SW"};return d>=0&&d<8?names[d]:"bad";}
boolean is_pool(coordxy x,coordxy y){append("pool:%d:%d;",x,y);return opts[20];}
boolean is_lava(coordxy x,coordxy y){append("lava:%d:%d;",x,y);return opts[21];}
const char *surface(coordxy x,coordxy y){return "water";}
void killed(struct monst *m){append("killed:%d;",mid(m));m->mhp=0;svl.level.monsters[m->mx][m->my]=NULL;callback(11);}
void monkilled(struct monst *m,const char *s,int how){append("monkilled:%d:%s:%d;",mid(m),s,how);m->mhp=0;svl.level.monsters[m->mx][m->my]=NULL;callback(11);}
void adjalign(int n){append("align:%d;",n);u.ualign.record+=n;}
void rloc_to(struct monst *m,coordxy x,coordxy y){append("rloc-to:%d:%d:%d;",mid(m),x,y);svl.level.monsters[m->mx][m->my]=NULL;place_monster(m,x,y);}
boolean rloc(struct monst *m,unsigned f){append("rloc:%d:%u;",mid(m),f);rloc_to(m,30,10);return TRUE;}
void sokoban_guilt(void){append("guilt;");}
int mintrap(struct monst *m,unsigned f){append("mintrap:%d:%u;",mid(m),f);callback(12);return 0;}
int float_down(long a,long b){append("float-down:%ld:%ld:%d:%d;",a,b,mid(u.usteed),gi.in_steed_dismounting);callback(13);return 1;}
void encumber_msg(void){append("encumber;");}
int describe_level(char *b,int which){append("describe:%d;",which);strcpy(b,"fixture-level");return 1;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/steed.c"
#else
extern boolean teleport_steed_test_landing(coord*,int,int);
extern void teleport_steed_test_wake(struct monst*);
extern const char *teleport_steed_storage(void);
#define landing_spot teleport_steed_test_landing
#define maybewakesteed teleport_steed_test_wake
#endif
#include "tu-steed-layout.h"
void probe_reset(unsigned s){int i,x,y;if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&gu,0,sizeof gu);memset(&gi,0,sizeof gi);memset(&gv,0,sizeof gv);memset(&disp,0,sizeof disp);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(monsters,0,sizeof monsters);memset(extras,0,sizeof extras);memset(pool,0,sizeof pool);memset(traps,0,sizeof traps);memset(opts,0,sizeof opts);uwep=uarm=uarmg=uarmf=uball=NULL;objects_globals_init();monst_globals_init();u.ux=u.uy=10;u.dx=1;u.ulevel=20;u.uhp=100;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];for(i=0;i<8;i++){monsters[i].data=&mons[PM_PONY];monsters[i].m_id=100+i;monsters[i].mx=11+i;monsters[i].my=10;monsters[i].mhp=monsters[i].mhpmax=20;monsters[i].mtame=10;monsters[i].mcanmove=1;}for(i=0;i<16;i++){pool[i].otyp=SADDLE;pool[i].oclass=TOOL_CLASS;pool[i].quan=1;pool[i].where=OBJ_FREE;}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;vision[y][x]=COULD_SEE|IN_SIGHT;}for(y=0;y<ROWNO;y++)vision_rows[y]=vision[y];gv.viz_array=vision_rows;svl.level.monsters[11][10]=&monsters[0];opts[0]=opts[1]=opts[2]=opts[5]=opts[13]=opts[14]=opts[16]=1;opts[3]=12;opts[4]=11;opts[7]='y';opts[18]=12;opts[19]=10;seed=s;rollidx=nroll=enexto_calls=0;nextobj=8;tracebuf[0]=statebuf[0]=caller[0]=0;spot.x=spot.y=-99;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;}
int *probe_rng_pointer(void){return rolls;}
void probe_rng_length(int n){nroll=n;rollidx=0;}
int probe_rng_count(void){return rollidx;}
unsigned probe_rng_state(void){return seed;}
void probe_object(int i,int k,long v){struct obj *o=&pool[i];switch(k){case 0:o->otyp=v;o->oclass=objects[v].oc_class;break;case 1:o->cursed=v;break;case 2:o->greased=v;break;case 3:o->bknown=v;break;case 4:o->oeroded=v;break;case 5:o->oeroded2=v;break;case 6:o->owornmask=v;break;case 7:o->quan=v;break;case 8:o->nobj=v<0?NULL:&pool[v];break;case 9:gi.invent=v?o:NULL;break;case 10:o->where=v;break;case 11:uwep=v?o:NULL;break;case 12:uarm=v?o:NULL;break;case 13:uarmg=v?o:NULL;break;case 14:uarmf=v?o:NULL;break;case 15:uball=v?o:NULL;break;}}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.dx=v;break;case 3:u.dy=v;break;case 4:u.uswallow=v;break;case 5:u.uinwater=v;break;case 6:u.usteed=v<0?NULL:&monsters[v];break;case 7:u.ustuck=v<0?NULL:&monsters[v];break;case 8:u.utrap=v;break;case 9:u.utraptype=v;break;case 10:u.ulevel=v;break;case 11:gy.youmonst.data=&mons[v];u.umonnum=v;break;case 12:u.umonster=v;break;case 13:gu.urole.mnum=v;break;case 14:flags.debug=v;break;case 15:u.weapon_skills[P_RIDING].skill=v;break;case 16:u.urideturns=v;break;case 17:u.ugallop=v;break;case 18:gu.unweapon=v;break;case 19:gi.in_steed_dismounting=v;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_monster_field(int i,int k,long v){struct monst *m=&monsters[i];switch(k){case 0:m->data=&mons[v];break;case 1:m->m_id=v;break;case 2:m->mhp=v;break;case 3:m->m_lev=v;break;case 4:m->mtame=v;break;case 5:m->isminion=v;break;case 6:m->isshk=v;break;case 7:m->ispriest=v;break;case 8:m->isgd=v;break;case 9:m->iswiz=v;break;case 10:m->mundetected=v;break;case 11:m->mtrapped=v;break;case 12:m->mleashed=v;break;case 13:m->mcanmove=v;break;case 14:m->mfrozen=v;break;case 15:m->msleeping=v;break;case 16:m->misc_worn_check=v;break;case 17:m->minvent=v<0?NULL:&pool[v];break;case 18:m->m_ap_type=v;break;case 19:m->female=v;break;case 20:m->mx=v;break;case 21:m->my=v;break;case 22:m->meating=v;break;case 23:m->mstate=v;break;case 24:m->mextra=v?&extras[i]:NULL;extras[i].mgivenname=v?"Dobbin":NULL;break;case 25:svl.level.monsters[m->mx][m->my]=v?m:NULL;break;}}
void probe_terrain(int x,int y,int typ,int trap,int seen){levl[x][y].typ=typ;traps[x][y].ttyp=trap;traps[x][y].tseen=seen;}
long probe_action(int op,int i,int a,int b,int c){struct monst *m=i<0?NULL:&monsters[i];switch(op){case 0:rider_cant_reach();return 0;case 1:return can_saddle(m);case 2:return use_saddle(&pool[i]);case 3:put_saddle_on_mon(a<0?NULL:&pool[a],m);return 0;case 4:return can_ride(m);case 5:return doride();case 6:return mount_steed(m,a);case 7:exercise_steed();return 0;case 8:kick_steed();return 0;case 9:return landing_spot(&spot,a,b);case 10:dismount_steed(a);return 0;case 11:maybewakesteed(m);return 0;case 12:poly_steed(m,&mons[a]);return 0;case 13:return stucksteed(a);case 14:place_monster(m,a,b);return 0;}return -999;}
void *probe_pointer(int k,int i){switch(k){case 0:return &pool[i];case 1:return &monsters[i];case 2:return &u;case 3:return &gy.youmonst;case 4:return &spot;case 5:return &monsters[i].data;case 6:return &mons[i];case 7:return &svl.level.monsters[0][0];case 8:return &u.weapon_skills[P_RIDING];case 9:
#ifdef TELEPORT_REFERENCE_TU
return (void*)steeds;
#else
return (void*)teleport_steed_storage();
#endif
}return NULL;}
const char *probe_snapshot(void){int i;char *p=statebuf;p+=sprintf(p,"hero:%d:%d:%d:%d:%d:%d:%d:%u:%d:%d:%d:%d:%ld:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d;",u.ux,u.uy,u.dx,u.dy,mid(u.usteed),mid(u.ustuck),u.uswallow,u.utrap,u.utraptype,u.ulevel,u.uhp,u.urideturns,u.ugallop,(long)u.ualign.record,u.weapon_skills[P_RIDING].skill,u.weapon_skills[P_RIDING].advance,gu.unweapon,gi.in_steed_dismounting,disp.botl,gv.vision_full_recalc,spot.x,spot.y,u.uinwater);for(i=1;i<=LAST_PROP;i++)p+=sprintf(p,"p%d:%ld:%ld:%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);for(i=0;i<8;i++){struct monst *m=&monsters[i];p+=sprintf(p,"m%d:%d:%u:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld:%ld:%d:%d:%d:%d:%d;",i,monsndx(m->data),m->m_id,m->mx,m->my,m->mhp,m->mtame,m->mcanmove,m->mfrozen,m->msleeping,m->mtrapped,m->mleashed,m->misc_worn_check,m->mstate,oid(m->minvent),m->meating,m->isminion,m->female,has_mgivenname(m)?1:0);}for(i=0;i<16;i++){struct obj *o=&pool[i];p+=sprintf(p,"o%d:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d;",i,o->otyp,o->owornmask,o->leashmon,o->where,o->cursed,o->greased,o->known,o->dknown,o->bknown,oid(o->nobj),o->where==OBJ_MINVENT?mid(o->ocarry):-1);}p+=sprintf(p,"equipment:%d:%d:%d:%d:%d:%d;",oid(gi.invent),oid(uwep),oid(uarm),oid(uarmg),oid(uarmf),oid(uball));for(i=0;i<COLNO*ROWNO;i++)p+=sprintf(p,"%d,",mid(svl.level.monsters[i/ROWNO][i%ROWNO]));return statebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
