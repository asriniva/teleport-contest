#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
struct you u;
__typeof__(gy) gy;
__typeof__(gi) gi;
__typeof__(gu) gu;
__typeof__(svm) svm;
__typeof__(svl) svl;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(disp) disp;
__typeof__(gv) gv;
__typeof__(windowprocs) windowprocs;
winid WIN_MESSAGE=3;
struct obj *uarmg;
struct obj hands_obj;
const char ynchars[]="yn";
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
const struct c_common_strings c_common_strings={.c_something="something",.c_nothing_seems_to_happen="Nothing seems to happen."};
static seenV vision[ROWNO][COLNO],*visionrows[ROWNO];
static struct obj objs[24];
static struct monst monsters[8];
static struct trap fixture_trap;
static int opts[32],random_values[512],random_length,random_index,created,area_count,area_x[64],area_y[64],pool_count;
static unsigned random_state;
static char tracebuf[524288],statebuf[32768],caller[128];
static void *growth;
static int oid(struct obj *o){return o==&hands_obj?99:o?(int)(o-objs)+1:0;}
static int mid(struct monst *m){return m?(int)(m-monsters)+1:0;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(Your) MSG(You_feel) MSG(You_hear) MSG(You_see) MSG(pline_The) MSG(verbalize) MSG(impossible)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file,int line,const char *fn){const char *p=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:file,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
static void callback_effect(void){if(opts[28]){opts[28]=0;append("nested-wash:%d;",wash_hands());}if(opts[29]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew;");}}
const char *surface(coordxy x,coordxy y){append("surface:%d:%d;",x,y);return "floor";}
char *makeplural(const char *s){static char b[BUFSZ];snprintf(b,sizeof b,"%ss",s);return b;}
char *rndmonnam(char *s){append("rndmonnam:%d;",s!=NULL);return "purple hippo";}
struct monst *makemon(struct permonst *p,coordxy x,coordxy y,mmflags_nht f){struct monst *m;append("make:%d:%d:%d:%lu;",p->pmidx,x,y,(unsigned long)f);if(opts[1])return NULL;if(created>=8)abort();m=&monsters[created++];m->data=p;m->mx=x;m->my=y;m->mhp=20;m->msleeping=1;return m;}
struct trap *t_at(coordxy x,coordxy y){append("trap:%d:%d;",x,y);return opts[2]?&fixture_trap:NULL;}
int mintrap(struct monst *m,unsigned f){append("mintrap:%d:%u;",mid(m),f);return 0;}
char *a_monnam(struct monst *m){return "a fixture monster";}
char *Amonnam(struct monst *m){return "A fixture monster";}
int pronoun_gender(struct monst *m,unsigned f){append("pronoun:%d:%u;",mid(m),f);return opts[3];}
xint16 level_difficulty(void){append("difficulty;");return opts[4];}
void mongrantswish(struct monst **m){append("grant:%d;",mid(*m));(*m)->mhp=0;*m=NULL;}
void do_clear_area(coordxy x,coordxy y,int range,void(*fn)(coordxy,coordxy,void*),genericptr_t arg){int i;append("area:%d:%d:%d:%d:%d;",x,y,range,fn!=NULL,*(int *)arg);for(i=0;i<area_count;i++){append("before:%d;",*(int *)arg);fn(area_x[i],area_y[i],arg);append("after:%d;",*(int *)arg);}pool_count=*(int *)arg;}
struct obj *sobj_at(int type,coordxy x,coordxy y){append("sobj:%d:%d:%d;",type,x,y);return opts[5]?&objs[0]:NULL;}
boolean nexttodoor(int x,int y){append("door:%d:%d;",x,y);return opts[6];}
boolean delfloortrap(struct trap *t){append("deltrap:%d;",t->ttyp);if(!opts[7])return FALSE;opts[2]=0;return TRUE;}
boolean set_levltyp(coordxy x,coordxy y,schar type){int old=levl[x][y].typ;append("terrain:%d:%d:%d;",x,y,type);if(old==FOUNTAIN)svl.level.flags.nfountains--;if(old==SINK)svl.level.flags.nsinks--;if(type==FOUNTAIN)svl.level.flags.nfountains++;if(type==SINK)svl.level.flags.nsinks++;levl[x][y].typ=type;return TRUE;}
void del_engr_at(coordxy x,coordxy y){append("engraving:%d:%d;",x,y);}
void water_damage_chain(struct obj *o,boolean f){append("water-chain:%d:%d;",oid(o),f);callback_effect();}
int minliquid(struct monst *m){append("liquid:%d;",mid(m));m->mhp--;return 0;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
int rnd_class(int first,int last){append("class:%d:%d;",first,last);return first+opts[8];}
struct obj *mksobj_at(int type,coordxy x,coordxy y,boolean init,boolean art){struct obj *o=&objs[22];append("mksobj-at:%d:%d:%d:%d:%d;",type,x,y,init,art);o->otyp=type;o->oclass=objects[type].oc_class;o->quan=1;o->where=OBJ_FLOOR;return o;}
void exercise(int a,boolean b){append("exercise:%d:%d;",a,b);}
const char *mbodypart(struct monst *m,int p){append("body:%d:%d;",mid(m),p);return p==HEAD?"head":"arm";}
boolean in_town(coordxy x,coordxy y){append("town:%d:%d;",x,y);return opts[9];}
struct monst *get_iter_mons(boolean(*fn)(struct monst *)){int i;append("iterate-watch;");for(i=0;i<8;i++)if(monsters[i].data&&fn(&monsters[i]))return &monsters[i];return NULL;}
char yn_function(const char *q,const char *choices,char def,boolean save){append("yn:%s:%s:%d:%d;",q,choices,def,save);return opts[10];}
int glyph_at(coordxy x,coordxy y){append("glyph:%d:%d;",x,y);return opts[11]?cmap_c_to_glyph(S_cloud):NO_GLYPH;}
int glyph_to_cmap(int glyph){append("cmap:%d;",glyph);return S_cloud;}
boolean angry_guards(boolean b){append("angry:%d;",b);return TRUE;}
boolean adjattrib(int a,int n,int msg){append("attribute:%d:%d:%d;",a,n,msg);if(opts[12])return FALSE;u.acurr.a[a]+=n;return TRUE;}
static void display_window(winid w,boolean block){append("display:%d:%d;",w,block);}
void newuhs(boolean b){append("hunger-state:%d;",b);}
void enlightenment(int flags,int final){append("enlighten:%d:%d;",flags,final);}
void morehungry(int n){append("hungry:%d;",n);u.uhunger-=n;}
void vomit(void){append("vomit;");}
char *fruitname(boolean juice){append("fruit:%d;",juice);return "slime mold";}
void losehp(int n,const char *why,schar how){append("losehp:%d:%s:%d;",n,why,how);u.uhp-=n;}
void poison_strdmg(int str,int hp,const char *why,schar how){append("poison:%d:%d:%s:%d;",str,hp,why,how);u.uhp-=hp;}
void curse(struct obj *o){append("curse:%d;",oid(o));o->cursed=1;callback_effect();}
void uncurse(struct obj *o){append("uncurse:%d;",oid(o));o->cursed=0;}
void bless(struct obj *o){append("bless:%d;",oid(o));o->blessed=1;o->cursed=0;}
void update_inventory(void){append("inventory;");}
int monster_detect(struct obj *o,int n){append("detect:%d:%d;",oid(o),n);return opts[13];}
const char *hliquid(const char *s){return s;}
void monflee(struct monst *m,int n,boolean a,boolean b){append("flee:%d:%d:%d:%d;",mid(m),n,a,b);m->mflee=1;}
boolean exist_artifact(int type,const char *name){append("exists:%d:%s;",type,name);return opts[14];}
const char *artiname(int n){append("artifact-name:%d;",n);return "Excalibur";}
struct obj *oname(struct obj *o,const char *name,unsigned f){append("oname:%d:%s:%u;",oid(o),name,f);if(opts[15]){objs[23]=*o;if(gi.invent==o)gi.invent=&objs[23];o=&objs[23];}o->oartifact=ART_EXCALIBUR;return o;}
void discover_artifact(xint16 n){append("discover:%d;",n);}
void livelog_printf(long mask,const char *f,...){char b[BUFSZ];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append("log:%ld:%s;",mask,b);}
const char *body_part(int p){append("hero-body:%d;",p);return p==FACE?"face":p==HAND?"hand":"arm";}
long money_cnt(struct obj *o){long n=0;for(;o;o=o->nobj)if(o->oclass==COIN_CLASS)n+=o->quan*objects[o->otyp].oc_cost;append("money:%ld;",n);return n;}
long somegold(long n){append("somegold:%ld;",n);return opts[16];}
void delobj(struct obj *o){struct obj **p=&gi.invent;append("delete:%d;",oid(o));while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;o->nobj=NULL;o->where=OBJ_DELETED;}
xint16 dunlev(d_level *l){append("dunlev:%d:%d;",l->dnum,l->dlevel);return l->dlevel;}
xint16 dunlevs_in_dungeon(d_level *l){append("dunlevs:%d;",l->dnum);return 20;}
struct obj *mkgold(long n,coordxy x,coordxy y){append("gold:%ld:%d:%d;",n,x,y);objs[22].quan=n;objs[22].otyp=GOLD_PIECE;objs[22].where=OBJ_FLOOR;return &objs[22];}
void make_glib(int n){append("glib:%d;",n);Glib=n;}
const char *fingers_or_gloves(boolean b){append("fingers:%d;",b);return "fingers";}
int water_damage(struct obj *o,const char *why,boolean f){append("water:%d:%s:%d;",oid(o),why?why:"NULL",f);return opts[17];}
void monstseesu(unsigned long flags){append("sees:%lu;",flags);}
void monstunseesu(unsigned long flags){append("unsees:%lu;",flags);}
struct obj *mkobj(int cls,boolean art){struct obj *o=&objs[21];append("mkobj:%d:%d;",cls,art);memset(o,0,sizeof *o);o->otyp=opts[18]-->0?POT_WATER:POT_HEALING;o->oclass=cls;o->quan=1;o->dknown=1;return o;}
void obfree(struct obj *o,struct obj *other){append("free:%d:%d;",oid(o),oid(other));o->where=OBJ_DELETED;}
const char *hcolor(const char *s){append("color:%s;",s);return s;}
void observe_object(struct obj *o){append("observe:%d;",oid(o));}
int dopotion(struct obj *o){append("potion:%d:%ld:%d:%d:%d;",oid(o),o->quan,o->cursed,o->blessed,o->fromsink);o->quan--;return 1;}
struct obj *mkobj_at(char cls,coordxy x,coordxy y,boolean init){append("mkobj-at:%d:%d:%d:%d;",cls,x,y,init);objs[22].oclass=cls;objs[22].where=OBJ_FLOOR;return &objs[22];}
void more_experienced(int xp,int score){append("experience:%d:%d;",xp,score);u.uexp+=xp;}
void newexplevel(void){append("newlevel;");}
schar acurr(int attr){append("acurr:%d;",attr);return u.acurr.a[attr];}
void polyself(int f){append("poly:%d;",f);}
NhRegion *create_gas_cloud(coordxy x,coordxy y,int radius,int duration){append("cloud:%d:%d:%d:%d;",x,y,radius,duration);return NULL;}
int canseemon(struct monst *m){append("see:%d;",mid(m));return opts[19];}
int sensemon(struct monst *m){append("sense:%d;",mid(m));return 0;}
char *xname(struct obj *o){static char b[BUFSZ];snprintf(b,sizeof b,"fixture item %d",oid(o));return b;}
char *the(const char *s){static char b[BUFSZ];snprintf(b,sizeof b,"the %s",s);return b;}
void polymorph_sink(void){append("poly-sink;");}
void potionbreathe(struct obj *o){append("breathe:%d;",oid(o));}
void trycall(struct obj *o){append("trycall:%d;",oid(o));}
void useup(struct obj *o){append("useup:%d;",oid(o));if(--o->quan==0)delobj(o);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/fountain.c"
#else
extern void teleport_fountain_test_snakes(void),teleport_fountain_test_demon(void),teleport_fountain_test_nymph(void),teleport_fountain_test_gush(coordxy,coordxy,void*),teleport_fountain_test_gem(void);
extern boolean teleport_fountain_test_watch(struct monst*);
#endif
#include "tu-fountain-layout.h"
void probe_reset(unsigned seed){int i;if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&gu,0,sizeof gu);memset(&svm,0,sizeof svm);memset(&svl,0,sizeof svl);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(objs,0,sizeof objs);memset(monsters,0,sizeof monsters);memset(&fixture_trap,0,sizeof fixture_trap);memset(&hands_obj,0,sizeof hands_obj);memset(opts,0,sizeof opts);opts[0]=opts[7]=opts[19]=1;opts[10]='y';opts[16]=100;monst_globals_init();objects_globals_init();for(i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=i;objects[i].oc_descr_idx=i;}u.ux=10;u.uy=10;u.uz.dlevel=5;u.ulevel=10;u.uhp=100;u.uhunger=500;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];gu.urole.mnum=PM_KNIGHT;for(i=0;i<A_MAX;i++){u.acurr.a[i]=10;u.amax.a[i]=14;}for(i=0;i<ROWNO;i++)visionrows[i]=vision[i];gv.viz_array=visionrows;memset(vision,IN_SIGHT|COULD_SEE,sizeof vision);windowprocs.win_display_nhwindow=display_window;for(i=0;i<8;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].mhp=20;monsters[i].mx=11;monsters[i].my=11;monsters[i].mpeaceful=1;if(i<7)monsters[i].nmon=&monsters[i+1];}fmon=monsters;uarmg=NULL;random_length=random_index=0;random_state=seed;created=area_count=pool_count=0;tracebuf[0]=caller[0]=0;levl[10][10].typ=FOUNTAIN;levl[10][10].flags=0;svl.level.flags.nfountains=1;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int i,int value){opts[i]=value;if(i==22)memset(vision,value?(IN_SIGHT|COULD_SEE):0,sizeof vision);}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
static struct obj *object(int i){return i<0?&hands_obj:&objs[i];}
void probe_obj(int i,int type,long q,int where){struct obj *o=&objs[i];memset(o,0,sizeof *o);o->o_id=100+i;o->otyp=type;o->oclass=objects[type].oc_class;o->quan=q;o->where=where;o->dknown=1;}
void probe_next(int a,int b){objs[a].nobj=b<0?NULL:&objs[b];}
void probe_inventory(int n){gi.invent=n<0?NULL:&objs[n];}
void probe_obit(int i,int bit,long value){struct obj *o=object(i);switch(bit){case 0:o->cursed=value;break;case 1:o->blessed=value;break;case 2:o->oerodeproof=value;break;case 3:o->oeroded=value;break;case 4:o->oeroded2=value;break;case 5:o->dknown=value;break;case 6:o->oartifact=value;break;case 7:o->spe=value;break;case 8:o->where=value;break;case 9:uarmg=value?o:NULL;break;case 10:svl.level.objects[12][12]=value?o:NULL;break;}}
void probe_hero(int field,long value){switch(field){case 0:u.utrap=value;break;case 1:u.utraptype=value;break;case 2:u.uluck=value;break;case 3:u.ulevel=value;break;case 4:u.ualign.type=value;break;case 5:gu.urole.mnum=value;break;case 6:flags.female=value;break;case 7:wizard=value;break;case 8:u.uroleplay.deaf=value;break;case 9:u.uhunger=value;break;case 10:u.uz.dlevel=value;break;case 11:u.acurr.a[A_CON]=value;break;}}
void probe_prop(int p,int field,long value){if(field==0)u.uprops[p].intrinsic=value;else if(field==1)u.uprops[p].extrinsic=value;else u.uprops[p].blocked=value;}
void probe_terrain(int x,int y,int type,int flags,int blessed){int old=levl[x][y].typ;if(old==FOUNTAIN)svl.level.flags.nfountains--;if(old==SINK)svl.level.flags.nsinks--;levl[x][y].typ=type;levl[x][y].flags=flags;levl[x][y].blessedftn=blessed;if(type==FOUNTAIN)svl.level.flags.nfountains++;if(type==SINK)svl.level.flags.nsinks++;}
void probe_trap(int type){fixture_trap.ttyp=type;opts[2]=type!=0;}
void probe_mon(int n,int species){monsters[n].data=&mons[species];}
void probe_mbit(int n,int bit,int value){switch(bit){case 0:monsters[n].msleeping=value;break;case 1:monsters[n].mpeaceful=value;break;case 2:monsters[n].mhp=value;break;case 3:svl.level.monsters[12][12]=value?&monsters[n]:NULL;break;}}
void probe_vital(int n,int flags){svm.mvitals[n].mvflags=flags;}
void probe_area(int n,int x,int y){if(n<0){area_count=0;return;}area_x[n]=x;area_y[n]=y;if(area_count<=n)area_count=n+1;}
int probe_counter(void){return pool_count;}
int probe_action(int op,int a,int b,int c){switch(op){case 0:floating_above(a==0?"fountain":a==1?"sink":"pool");break;case 1:
#ifdef TELEPORT_REFERENCE_TU
dowatersnakes();
#else
teleport_fountain_test_snakes();
#endif
break;case 2:
#ifdef TELEPORT_REFERENCE_TU
dowaterdemon();
#else
teleport_fountain_test_demon();
#endif
break;case 3:
#ifdef TELEPORT_REFERENCE_TU
dowaternymph();
#else
teleport_fountain_test_nymph();
#endif
break;case 4:dogushforth(a);break;case 5:
#ifdef TELEPORT_REFERENCE_TU
gush(a,b,&pool_count);
#else
teleport_fountain_test_gush(a,b,&pool_count);
#endif
break;case 6:
#ifdef TELEPORT_REFERENCE_TU
dofindgem();
#else
teleport_fountain_test_gem();
#endif
break;case 7:
#ifdef TELEPORT_REFERENCE_TU
return watchman_warn_fountain(&monsters[a]);
#else
return teleport_fountain_test_watch(&monsters[a]);
#endif
case 8:dryup(a,b,c);break;case 9:drinkfountain();break;case 10:dipfountain(object(a));break;case 11:return wash_hands();case 12:breaksink(a,b);break;case 13:drinksink();break;case 14:dipsink(object(a));break;case 15:sink_backs_up(a,b);break;}return 0;}
void *probe_object_pointer(int n){return object(n);}
void *probe_hero_pointer(void){return &u;}
size_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){int i,x,y;char *p=statebuf;p+=sprintf(p,"hero:%d:%d:%d:%d:%d:%d:%d:%d:%ld:%d:%d:%d:%d;",u.ux,u.uy,u.ulevel,u.uluck,u.ualign.type,u.uhunger,u.uhp,u.utrap,u.uexp,u.utraptype,disp.botl,oid(gi.invent),oid(uarmg));p+=sprintf(p,"attributes:");for(i=0;i<A_MAX;i++)p+=sprintf(p,"%d,%d/",u.acurr.a[i],u.amax.a[i]);for(i=0;i<=LAST_PROP;i++)p+=sprintf(p,";p%d:%ld:%ld:%ld",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);for(i=0;i<24;i++){struct obj *o=&objs[i];p+=sprintf(p,";o%d:%d:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",i,oid(o->nobj),o->otyp,o->quan,o->where,o->oclass,o->cursed,o->blessed,o->oerodeproof,o->oeroded,o->oeroded2,o->dknown,o->oartifact,o->spe);}for(i=0;i<8;i++)p+=sprintf(p,";m%d:%d:%d:%d:%d:%d",i,monsters[i].data?monsters[i].data->pmidx:-1,monsters[i].mhp,monsters[i].msleeping,monsters[i].mpeaceful,monsters[i].mflee);p+=sprintf(p,";level:%d:%d:%d;map:",svl.level.flags.nfountains,svl.level.flags.nsinks,pool_count);for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)if(levl[x][y].typ||levl[x][y].flags||levl[x][y].blessedftn||svl.level.objects[x][y]||svl.level.monsters[x][y])p+=sprintf(p,"%d,%d,%d,%d,%d,%d,%d,%d/",x,y,levl[x][y].typ,levl[x][y].flags,levl[x][y].looted,levl[x][y].blessedftn,oid(svl.level.objects[x][y]),mid(svl.level.monsters[x][y]));return statebuf;}
