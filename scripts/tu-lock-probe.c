#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
struct you u;
struct obj *uwep;
const struct c_common_strings c_common_strings={.c_Something="Something"};
__typeof__(gx) gx;
__typeof__(go) go;
__typeof__(gi) gi;
__typeof__(gy) gy;
__typeof__(svl) svl;
__typeof__(svm) svm;
__typeof__(flags) flags;
__typeof__(gv) gv;
__typeof__(cg) cg={.zeroobj={0}};
__typeof__(gu) gu;
__typeof__(svc) svc;
__typeof__(svd) svd;
__typeof__(gm) gm;
static struct obj pool[24];
static struct monst monster;
static struct trap trap;
static int opts[40],rolls[4096],nroll,rollidx,deleted[24],used[24];
static unsigned seed;
static char tracebuf[2097152],statebuf[131072],caller[128],output[BUFSZ];
static seenV vision[ROWNO][COLNO],*vision_rows[ROWNO];
static coord result;
static void *growth;
static int oid(struct obj *o){return o?(o>=pool&&o<pool+24?(int)(o-pool):99):-1;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*3];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(Your) MSG(You_cant) MSG(There) MSG(You_hear) MSG(pline_The) MSG(verbalize) MSG(impossible)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *f,int line,const char *fn){const char *b=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(rollidx<nroll)v=rolls[rollidx]%(unsigned)n;else{seed=seed*1664525U+1013904223U;v=(seed>>8)%(unsigned)n;}rollidx++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnl)(int n){int v=draw(n);append("rnl:%d:%d@%s;",n,v,caller);return v;}
static void callback(int stage){coordxy x,y;if(opts[30]==stage){opts[30]=0;int p=picking_lock(&x,&y);append("nested-pick:%d:%d:%d;",p,x,y);}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}}
static int other_occupation(void){append("other-occupation;");return 73;}
#ifdef TELEPORT_REFERENCE_TU
static int picklock(void),forcelock(void);
static int occupation_id(int(*fn)(void)){return !fn?-1:fn==picklock?0:fn==forcelock?1:99;}
#else
extern uintptr_t teleport_lock_callback_pointer(int);
static int occupation_id(int(*fn)(void)){return !fn?-1:(uintptr_t)fn==teleport_lock_callback_pointer(0)?0:(uintptr_t)fn==teleport_lock_callback_pointer(1)?1:99;}
#endif
void set_occupation(int(*f)(void),const char *s,cmdcount_nht n){append("occupation:%d:%s:%ld;",occupation_id(f),s,n);go.occupation=f;callback(1);}
void stop_occupation(void){append("stop; ");go.occupation=NULL;callback(1);}
void exercise(int a,boolean b){append("exercise:%d:%d;",a,b);}
schar acurr(int a){append("acurr:%d;",a);return opts[1];}
schar acurrstr(void){append("strength;");return opts[1];}
char yn_function(const char *q,const char *choices,char def,boolean hist){int c=opts[2];append("yn:%s:%s:%d:%d:%d;",q,choices,def,hist,c);callback(2);return c;}
const char ynchars[]="yn",ynqchars[]="ynq";
int get_adjacent_loc(const char *a,const char *b,coordxy x,coordxy y,coord *c){append("adjacent:%s:%s:%d:%d;",a?a:"NULL",b?b:"NULL",x,y);c->x=opts[3];c->y=opts[4];callback(3);return opts[5];}
int getdir(const char *s){append("getdir:%s;",s?s:"NULL");return opts[5];}
boolean can_reach_floor(boolean b){append("reach:%d;",b);return opts[6];}
void cant_reach_floor(coordxy x,coordxy y,boolean a,boolean b,boolean c){append("cant-reach:%d:%d:%d:%d:%d;",x,y,a,b,c);}
const char *hliquid(const char *s){append("liquid:%s;",s);return s;}
boolean on_level(d_level *a,d_level *b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean is_pool(coordxy x,coordxy y){append("pool:%d:%d;",x,y);return opts[7];}
boolean is_lava(coordxy x,coordxy y){append("lava:%d:%d;",x,y);return opts[8];}
int is_drawbridge_wall(coordxy x,coordxy y){append("drawbridge:%d:%d;",x,y);return opts[9];}
boolean is_db_wall(coordxy x,coordxy y){append("dbwall:%d:%d;",x,y);return opts[10];}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
boolean unconscious(void){append("unconscious; ");return opts[25];}
boolean is_fainted(void){append("fainted; ");return opts[26];}
int container_at(coordxy x,coordxy y,boolean b){append("container:%d:%d:%d;",x,y,b);return opts[11];}
int doloot(void){append("loot;");return 37;}
int dokick(void){append("kick;");return 38;}
void cmdq_add_ec(int q,int(*f)(void)){append("queue:%d:%d;",q,f==dokick);}
void cmdq_add_dir(int q,schar x,schar y,schar z){append("direction:%d:%d:%d:%d;",q,x,y,z);}
boolean is_magic_key(struct monst *m,struct obj *o){append("magic:%d;",oid(o));return o&&o->oartifact==ART_MASTER_KEY_OF_THIEVERY&&!o->cursed;}
boolean is_quest_artifact(struct obj *o){append("own-quest:%d;",oid(o));return o->oartifact==opts[12];}
int touch_artifact(struct obj *o,struct monst *m){append("touch:%d;",oid(o));callback(4);return opts[13];}
int could_untrap(boolean a,boolean b){append("could-untrap:%d:%d;",a,b);return opts[14];}
int untrap(boolean a,coordxy x,coordxy y,struct obj *o){append("untrap:%d:%d:%d:%d;",a,x,y,oid(o));return 1;}
boolean chest_trap(struct obj *o,int p,boolean b){append("chest-trap:%d:%d:%d;",oid(o),p,b);callback(5);return TRUE;}
void b_trapped(const char *s,int p){append("btrapped:%s:%d;",s,p);callback(5);}
int update_mapseen_for(coordxy x,coordxy y){int old=svl.lastseentyp[x][y];append("mapseen:%d:%d;",x,y);svl.lastseentyp[x][y]=opts[15];return old;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);levl[x][y].glyph+=opts[16];callback(6);}
void feel_location(coordxy x,coordxy y){append("feel:%d:%d;",x,y);newsym(x,y);}
void feel_newsym(coordxy x,coordxy y){append("feel-new:%d:%d;",x,y);newsym(x,y);}
void block_point(int x,int y){append("block:%d:%d;",x,y);}
void unblock_point(int x,int y){append("unblock:%d:%d;",x,y);}
void recalc_block_point(coordxy x,coordxy y){append("reblock:%d:%d;",x,y);}
boolean closed_door(coordxy x,coordxy y){return IS_DOOR(levl[x][y].typ)&&(levl[x][y].doormask&(D_CLOSED|D_LOCKED));}
struct trap *t_at(coordxy x,coordxy y){append("trap-at:%d:%d;",x,y);return opts[24]?&trap:NULL;}
void set_msg_xy(coordxy x,coordxy y){append("message-xy:%d:%d;",x,y);}
void vision_recalc(int n){append("vision:%d;",n);gv.vision_full_recalc=0;}
void wake_nearto(coordxy x,coordxy y,int n){append("wake-at:%d:%d:%d;",x,y,n);}
void wake_nearby(boolean b){append("wake:%d;",b);}
char *in_rooms(coordxy x,coordxy y,int t){static char b[2];append("rooms:%d:%d:%d;",x,y,t);b[0]=opts[17];b[1]=0;callback(7);return b;}
void add_damage(coordxy x,coordxy y,long n){append("damage:%d:%d:%ld;",x,y,n);}
boolean costly_spot(coordxy x,coordxy y){append("costly:%d:%d;",x,y);return opts[18];}
struct monst *shop_keeper(char c){append("keeper:%d;",c);return opts[19]?&monster:NULL;}
void costly_alteration(struct obj *o,int t){append("alter:%d:%d:contents=%d;",oid(o),t,oid(o->cobj));callback(8);}
long stolen_value(struct obj *o,coordxy x,coordxy y,boolean p,boolean b){append("stolen:%d:%d:%d:%d:%d;",oid(o),x,y,p,b);return opts[20];}
const char *currency(long n){append("currency:%ld;",n);return "gold pieces";}
void obj_extract_self(struct obj *o){int i;struct obj **p;append("extract:%d;",oid(o));for(i=0;i<24;i++){p=&pool[i].cobj;while(*p){if(*p==o){*p=o->nobj;goto out;}p=&(*p)->nobj;}}out:o->nobj=NULL;o->where=OBJ_FREE;}
void obfree(struct obj *o,struct obj *merge){append("obfree:%d:%d;",oid(o),oid(merge));deleted[oid(o)]=1;maybe_reset_pick(o);callback(9);}
void delobj(struct obj *o){append("delete:%d;",oid(o));obfree(o,NULL);}
void useup(struct obj *o){append("useup:%d;",oid(o));used[oid(o)]++;if(--o->quan<=0){if(uwep==o)uwep=NULL;obfree(o,NULL);}}
void place_object(struct obj *o,coordxy x,coordxy y){append("place:%d:%d:%d;",oid(o),x,y);o->where=OBJ_FLOOR;o->ox=x;o->oy=y;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;}
void stackobj(struct obj *o){append("stack:%d;",oid(o));}
void start_corpse_timeout(struct obj *o){append("corpse-time:%d:%ld;",oid(o),o->age);}
boolean obj_resists(struct obj *o,int a,int b){append("resists:%d:%d:%d;",oid(o),a,b);return opts[21];}
int canseemon(struct monst *m){append("cansee-mon;");return opts[22];}
int sensemon(struct monst *m){append("sense-mon;");return opts[23];}
void map_invisible(coordxy x,coordxy y){append("invisible:%d:%d;",x,y);}
void stumble_onto_mimic(struct monst *m){append("mimic;");}
void maybe_absorb_item(struct monst *m,struct obj *o,int a,int b){append("absorb:%d:%d:%d;",oid(o),a,b);}
boolean mb_trapped(struct monst *m,boolean b){append("monster-trap:%d;",b);return TRUE;}
char *mon_nam(struct monst *m){return "fixture monster";}
char *Some_Monnam(struct monst *m){static char b[BUFSZ];strcpy(b,"Fixture monster");return b;}
const char *bottlename(void){return "bottle";}
void potionbreathe(struct obj *o){append("breathe:%d;",oid(o));}
char *xname(struct obj *o){static char b[8][BUFSZ];static unsigned idx;char *s=b[(idx++)%8];snprintf(s,BUFSZ,"object%d-type%d",oid(o),o->otyp);return s;}
char *doname(struct obj *o){return xname(o);}
char *yname(struct obj *o){return xname(o);}
char *ysimple_name(struct obj *o){return xname(o);}
char *ansimpleoname(struct obj *o){return xname(o);}
char *simple_typename(int t){static char b[BUFSZ];snprintf(b,sizeof b,"type%d",t);return b;}
const char *singular(struct obj *o,char *(*f)(struct obj*)){append("singular:%d:%ld:%ld;",oid(o),HBlinded,BBlinded);return f(o);}
char *safe_qbuf(char *b,const char *pre,const char *suf,struct obj *o,char *(*a)(struct obj*),char *(*z)(struct obj*),const char *last){append("safe:%d;",oid(o));snprintf(b,QBUFSZ,"%s%s%s",pre?pre:"",a(o),suf?suf:"");return b;}
char *the(const char *s){static char b[BUFSZ*2];snprintf(b,sizeof b,"the %s",s);return b;}
char *an(const char *s){static char b[BUFSZ*2];snprintf(b,sizeof b,"a %s",s);return b;}
char *An(const char *s){static char b[BUFSZ*2];snprintf(b,sizeof b,"A %s",s);return b;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/lock.c"
#else
extern const char *teleport_lock_test_action(void);
extern int teleport_lock_test_pick(void),teleport_lock_test_force(void);
extern boolean teleport_lock_test_obstructed(coordxy,coordxy,boolean);
extern void teleport_lock_test_shatter(struct obj*);
#define lock_action teleport_lock_test_action
#define picklock teleport_lock_test_pick
#define forcelock teleport_lock_test_force
#define obstructed teleport_lock_test_obstructed
#define chest_shatter_msg teleport_lock_test_shatter
#endif
#include "tu-lock-layout.h"
void probe_reset(unsigned s){int i,x,y;if(growth)free(growth);growth=NULL;uwep=NULL;memset(&u,0,sizeof u);memset(&gx,0,sizeof gx);memset(&go,0,sizeof go);memset(&gi,0,sizeof gi);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&svm,0,sizeof svm);memset(&flags,0,sizeof flags);memset(&gv,0,sizeof gv);memset(&gu,0,sizeof gu);memset(&svc,0,sizeof svc);memset(&svd,0,sizeof svd);memset(&gm,0,sizeof gm);memset(pool,0,sizeof pool);memset(&monster,0,sizeof monster);memset(opts,0,sizeof opts);memset(deleted,0,sizeof deleted);memset(used,0,sizeof used);objects_globals_init();monst_globals_init();for(i=0;i<24;i++){pool[i].otyp=CHEST;pool[i].oclass=TOOL_CLASS;pool[i].quan=1;pool[i].where=OBJ_FLOOR;pool[i].ox=pool[i].oy=10;}u.ux=u.uy=10;u.dx=1;u.uz.dnum=1;rogue_level.dnum=4;gy.youmonst.data=&mons[PM_HUMAN];monster.data=&mons[PM_SMALL_MIMIC];monster.mx=11;monster.my=10;monster.mhp=20;monster.mpeaceful=1;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;vision[y][x]=IN_SIGHT|COULD_SEE;}for(y=0;y<ROWNO;y++)vision_rows[y]=vision[y];gv.viz_array=vision_rows;levl[11][10].typ=DOOR;levl[11][10].doormask=D_LOCKED;opts[0]=1;opts[1]=12;opts[2]='y';opts[3]=11;opts[4]=10;opts[5]=opts[6]=opts[13]=opts[22]=1;opts[9]=-1;seed=s;rollidx=nroll=0;tracebuf[0]=statebuf[0]=output[0]=caller[0]=0;result.x=result.y=-99;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;}
int *probe_rng_pointer(void){return rolls;}
void probe_rng_length(int n){nroll=n;rollidx=0;}
int probe_rng_count(void){return rollidx;}
unsigned probe_rng_state(void){return seed;}
void probe_object(int i,int k,long v){struct obj *o=&pool[i];switch(k){case 0:o->otyp=v;o->oclass=objects[v].oc_class;break;case 1:o->where=v;break;case 2:o->ox=v;break;case 3:o->oy=v;break;case 4:o->olocked=v;break;case 5:o->obroken=v;break;case 6:o->lknown=v;break;case 7:o->otrapped=v;break;case 8:o->tknown=v;break;case 9:o->cursed=v;break;case 10:o->oartifact=v;break;case 11:o->quan=v;break;case 12:o->spe=v;break;case 13:o->nobj=v<0?NULL:&pool[v];break;case 14:o->nexthere=v<0?NULL:&pool[v];break;case 15:o->cobj=v<0?NULL:&pool[v];break;case 16:gi.invent=v?o:NULL;break;case 17:svl.level.objects[o->ox][o->oy]=v?o:NULL;break;case 18:uwep=v?o:NULL;break;case 19:o->age=v;break;case 20:o->dknown=v;break;case 21:o->oclass=v;break;case 22:o->oeroded=v;break;case 23:o->oeroded2=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.dx=v;break;case 3:u.dy=v;break;case 4:u.dz=v;break;case 5:u.uswallow=v;u.ustuck=v?&monster:NULL;break;case 6:u.utrap=v;break;case 7:u.utraptype=v;break;case 8:gy.youmonst.data=&mons[v];break;case 9:gu.urole.mnum=v;break;case 10:flags.autounlock=v;break;case 11:flags.verbose=v;break;case 12:u.uroleplay.deaf=v;break;case 13:u.usteed=v?&monster:NULL;break;case 14:u.ushops[0]=v;break;case 15:svm.moves=v;break;case 16:gv.vision_full_recalc=v;break;case 17:u.uz.dnum=v;break;case 18:rogue_level.dnum=v;break;case 19:gm.multi=v;break;case 20:u.uinwater=v;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_terrain(int x,int y,int type,int mask){levl[x][y].typ=type;levl[x][y].doormask=mask;}
void probe_monster_field(int k,int v){switch(k){case 0:svl.level.monsters[11][10]=v?&monster:NULL;break;case 1:monster.m_ap_type=v;break;case 2:monster.mappearance=v;break;case 3:monster.isshk=v;break;case 4:monster.mpeaceful=v;break;case 5:monster.mx=v;break;case 6:monster.my=v;break;case 7:monster.data=&mons[v];break;}}
void probe_xlock(int k,int v){switch(k){case 0:gx.xlock.box=v<0?NULL:&pool[v];break;case 1:gx.xlock.door=v?&levl[11][10]:NULL;break;case 2:gx.xlock.usedtime=v;break;case 3:gx.xlock.chance=v;break;case 4:gx.xlock.picktyp=v;break;case 5:gx.xlock.magic_key=v;break;}}
void probe_occupation(int which){if(which<0)go.occupation=NULL;else if(which==99)go.occupation=other_occupation;else{
#ifdef TELEPORT_REFERENCE_TU
 go.occupation=which?forcelock:picklock;
#else
 go.occupation=(int(*)(void))teleport_lock_callback_pointer(which);
#endif
}}
long probe_action(int op,int a,int b,int c,int d){switch(op){case 0:return picking_lock(&result.x,&result.y);case 1:return picking_at(a,b);case 2:strcpy(output,lock_action());return 0;case 3:return picklock();case 4:breakchestlock(&pool[a],b);return 0;case 5:return forcelock();case 6:reset_pick();return 0;case 7:maybe_reset_pick(a<0?NULL:&pool[a]);return 0;case 8:return oid(autokey(a));case 9:return pick_lock(a<0?NULL:&pool[a],b,c,d<0?NULL:&pool[d]);case 10:return u_have_forceable_weapon();case 11:return doforce();case 12:return stumble_on_door_mimic(a,b);case 13:return doopen();case 14:return doopen_indir(a,b);case 15:return obstructed(a,b,c);case 16:return doclose();case 17:return boxlock(&pool[a],&pool[b]);case 18:return doorlock(&pool[a],b,c);case 19:chest_shatter_msg(&pool[a]);return 0;case 20:return go.occupation?go.occupation():-1;}return -999;}
void *probe_pointer(int kind,int i){switch(kind){case 0:return &pool[i];case 1:return &gx.xlock;case 2:return &levl[11][10];case 3:return &u;case 4:return &monster;case 5:return output;case 6:return &result;case 7:return (void*)lock_action();case 8:return &gy.youmonst;}return NULL;}
const char *probe_snapshot(void){int i;char *p=statebuf;p+=sprintf(p,"lock:%d:%d:%d:%d:%d:%d;occ:%d;hero:%d:%d:%d:%d:%d:%d:%ld:%ld;coord:%d:%d;output:%s;",oid(gx.xlock.box),gx.xlock.door?1:0,gx.xlock.usedtime,gx.xlock.chance,gx.xlock.picktyp,gx.xlock.magic_key,occupation_id(go.occupation),u.ux,u.uy,u.dx,u.dy,u.dz,svc.context.move,HBlinded,BBlinded,result.x,result.y,output);for(i=0;i<24;i++){struct obj *o=&pool[i];p+=sprintf(p,"o%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld:%ld:%d:%d:%d:%d:%d;",i,o->otyp,o->where,o->ox,o->oy,o->olocked,o->obroken,o->lknown,o->otrapped,o->tknown,o->cursed,o->quan,o->age,oid(o->cobj),oid(o->nobj),oid(o->nexthere),deleted[i],used[i]);}p+=sprintf(p,"heads:%d:%d:%d;",oid(gi.invent),oid(uwep),oid(svl.level.objects[10][10]));for(i=0;i<COLNO*ROWNO;i++){struct rm *r=&levl[i/ROWNO][i%ROWNO];p+=sprintf(p,"%d,%d,%d;",r->typ,r->doormask,r->glyph);}return statebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
