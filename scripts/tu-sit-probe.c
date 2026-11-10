#include "hack.h"
#include "artifact.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
struct you u;
__typeof__(gy) gy;
__typeof__(gi) gi;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(disp) disp;
__typeof__(svl) svl;
__typeof__(svd) svd;
__typeof__(cg) cg={0};
__typeof__(gv) gv;
struct obj *uwep,*uarm,*uarmf;
const char ynchars[]="yn";
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind."};
const struct c_color_names c_color_names={.c_black="black"};
static seenV vision[ROWNO][COLNO],*visionrows[ROWNO];
static struct obj objs[16];
static struct monst steed,holder;
static struct trap fixture_trap;
static int opts[32],random_values[512],random_length,random_index;
static unsigned random_state;
static char tracebuf[262144],statebuf[32768],caller[128],inputbuf[BUFSZ];
static void *growth;
static int oid(struct obj *o){return o?(int)(o-objs)+1:0;}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),format,ap);va_end(ap);}
void panic(const char *format,...){abort();}
void impossible(const char *format,...){char b[BUFSZ];va_list a;va_start(a,format);vsnprintf(b,sizeof b,format,a);va_end(a);append("impossible:%s;",b);}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(Your) MSG(You_feel) MSG(There) MSG(You_cant) MSG(pline_The) MSG(verbalize)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file,int line,const char *func){const char *p=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:file,line,func);}
static int draw(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
int (d)(int n,int x){int i,v=n;for(i=0;i<n;i++)v+=draw(x);append("d:%d:%d:%d@%s;",n,x,v,caller);return v;}
static void callback_effect(void){if(opts[20]){opts[20]=0;append("nested-begin;");take_gold();append("nested-end;");}if(opts[21]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew;");}}
void remove_worn_item(struct obj *o,boolean b){append("remove:%d:%d;",oid(o),b);o->owornmask=0;}
void delobj(struct obj *o){struct obj **p=&gi.invent;append("delete:%d;",oid(o));while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;o->nobj=NULL;o->where=OBJ_DELETED;}
boolean In_V_tower(d_level *l){append("tower:%d:%d;",l->dnum,l->dlevel);return opts[1];}
void getlin(const char *prompt,char *out){append("getlin:%s;",prompt);strcpy(out,inputbuf);}
char yn_function(const char *q,const char *choices,char def,boolean save){append("yn:%s:%s:%d:%d;",q,choices,def,save);return opts[2];}
boolean adjattrib(int a,int n,int msg){append("attribute:%d:%d:%d;",a,n,msg);u.acurr.a[a]+=n;return TRUE;}
void losehp(int n,const char *why,schar how){append("losehp:%d:%s:%d;",n,why,how);if(Upolyd)u.mh-=n;else u.uhp-=n;}
void exercise(int a,boolean inc){append("exercise:%d:%d;",a,inc);}
void make_blinded(long n,boolean msg){append("blind:%ld:%d;",n,msg);HBlinded=(HBlinded&~TIMEOUT)|(n&TIMEOUT);}
void make_sick(long n,const char *why,boolean talk,int type){append("sick:%ld:%s:%d:%d;",n,why?why:"NULL",talk,type);Sick=(Sick&~TIMEOUT)|(n&TIMEOUT);}
void heal_legs(int n){append("legs:%d;",n);}
void change_luck(schar n){append("luck:%d;",n);u.uluck+=n;}
void makewish(void){append("wish;");callback_effect();}
struct permonst *courtmon(void){append("court;");return &mons[PM_HUMAN];}
struct monst *makemon(struct permonst *p,coordxy x,coordxy y,mmflags_nht f){append("make:%d:%d:%d:%lu;",p->pmidx,x,y,(unsigned long)f);return &holder;}
void do_genocide(int n){append("genocide:%d;",n);}
void make_confused(long n,boolean msg){append("confused:%ld:%d;",n,msg);HConfusion=(HConfusion&~TIMEOUT)|(n&TIMEOUT);}
void do_mapping(void){append("mapping;");}
const char *body_part(int p){append("body:%d;",p);return p==EYE?"eye":p==FOOT?"foot":"head";}
char *makeplural(const char *s){static char b[BUFSZ];snprintf(b,sizeof b,"%ss",s);return b;}
char *vtense(const char *s,const char *v){static char b[BUFSZ];snprintf(b,sizeof b,"%ss",v);return b;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
void newsym_force(coordxy x,coordxy y){append("newsym-force:%d:%d;",x,y);}
void aggravate(void){append("aggravate;");}
void tele(void){append("tele;");u.ux=20;u.uy=12;}
void identify_pack(int n,boolean b){append("identify:%d:%d;",n,b);}
void map_background(coordxy x,coordxy y,int b){append("background:%d:%d:%d;",x,y,b);}
void losexp(const char *why){append("losexp:%s;",why);u.ulevel--;}
void make_glib(int n){append("glib:%d;",n);Glib=n;}
void update_inventory(void){append("inventory;");}
void find_hell(d_level *l){append("hell;");l->dnum=2;l->dlevel=1;}
void schedule_goto(d_level *l,int type,const char *a,const char *b){append("goto:%d:%d:%d:%s:%s;",l->dnum,l->dlevel,type,a?a:"NULL",b?b:"NULL");}
int msummon(struct monst *m){append("summon:%d;",m!=NULL);return 1;}
int seffects(struct obj *o){size_t i;append("spell:%d:%d:%d:%ld:",o->otyp,o->oclass,o->blessed,HConfusion);for(i=0;i<sizeof *o;i++)append("%02x",((unsigned char *)o)[i]);append(";");callback_effect();HConfusion=12345;return 1;}
void polyself(int f){append("poly:%d;",f);}
struct obj *mksobj(int type,boolean init,boolean art){append("mksobj:%d:%d:%d;",type,init,art);memset(&objs[15],0,sizeof objs[15]);objs[15].otyp=type;objs[15].oclass=objects[type].oc_class;return &objs[15];}
int weight(struct obj *o){append("weight:%d:%ld;",oid(o),o->quan);return 17;}
void set_corpsenm(struct obj *o,int n){append("species:%d:%d;",oid(o),n);o->corpsenm=n;}
int egg_type_from_parent(int n,boolean f){append("egg-type:%d:%d;",n,f);return opts[3]<0?n:opts[3];}
void observe_object(struct obj *o){append("observe:%d;",oid(o));}
void dropy(struct obj *o){append("drop:%d;",oid(o));o->where=OBJ_FLOOR;}
void stackobj(struct obj *o){append("stack:%d;",oid(o));}
void morehungry(int n){append("hungry:%d;",n);u.uhunger-=n;}
struct trap *t_at(coordxy x,coordxy y){append("trap-at:%d:%d;",x,y);return opts[4]?&fixture_trap:NULL;}
boolean sticks(struct permonst *p){append("sticks:%d;",p->pmidx);return opts[14];}
boolean can_reach_floor(boolean b){append("reach:%d;",b);return opts[5];}
boolean is_pool(coordxy x,coordxy y){append("pool:%d:%d;",x,y);return levl[x][y].typ==POOL||levl[x][y].typ==MOAT||levl[x][y].typ==WATER;}
boolean is_lava(coordxy x,coordxy y){append("lava:%d:%d;",x,y);return levl[x][y].typ==LAVAPOOL;}
boolean is_ice(coordxy x,coordxy y){append("ice:%d:%d;",x,y);return levl[x][y].typ==ICE;}
boolean uteetering_at_seen_pit(struct trap *t){append("teeter:%d;",t!=NULL);return opts[6];}
boolean uescaped_shaft(struct trap *t){append("shaft:%d;",t!=NULL);return opts[7];}
boolean on_level(d_level *a,d_level *b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
char *mon_nam(struct monst *m){return "fixture monster";}
char *Monnam(struct monst *m){return "Fixture monster";}
int pronoun_gender(struct monst *m,unsigned flags){append("pronoun:%u;",flags);return opts[8];}
char *xname(struct obj *o){static char b[BUFSZ];snprintf(b,sizeof b,"fixture item %d",oid(o));return b;}
char *the(const char *s){static char b[BUFSZ];snprintf(b,sizeof b,"the %s",s);return b;}
long money_cnt(struct obj *o){long n=0;for(;o;o=o->nobj)if(o->oclass==COIN_CLASS)n+=o->quan;append("money:%ld;",n);return n;}
void useupf(struct obj *o,long n){append("useup:%d:%ld;",oid(o),n);o->where=OBJ_DELETED;}
struct monst *split_mon(struct monst *m,struct monst *other){append("split:%d:%d;",m==&gy.youmonst,other!=NULL);return opts[9]?&holder:NULL;}
void dryup(coordxy x,coordxy y,boolean b){append("dry:%d:%d:%d;",x,y,b);levl[x][y].typ=ROOM;}
int water_damage(struct obj *o,const char *why,boolean f){append("water-damage:%d:%s:%d;",oid(o),why,f);return 1;}
void altar_wrath(coordxy x,coordxy y){append("wrath:%d:%d;",x,y);}
void burn_away_slime(void){append("burn-slime;");Slimed=0;}
void dotrap(struct trap *t,unsigned f){append("dotrap:%d:%u;",t->ttyp,f);}
const char *surface(coordxy x,coordxy y){append("surface:%d:%d;",x,y);return "floor";}
const char *hliquid(const char *s){return s;}
boolean is_art(struct obj *o,int n){append("wield-art:%d;",n);return opts[10];}
void shieldeff(coordxy x,coordxy y){append("shield:%d:%d;",x,y);}
boolean spec_ability(struct obj *o,unsigned long n){append("ability:%d:%lu;",oid(o),n);return opts[11];}
char *Tobjnam(struct obj *o,const char *verb){static char b[BUFSZ];snprintf(b,sizeof b,"Item%d %s",oid(o),verb);return b;}
void unbless(struct obj *o){append("unbless:%d;",oid(o));o->blessed=0;}
void curse(struct obj *o){append("curse:%d;",oid(o));o->cursed=1;}
struct obj *which_armor(struct monst *m,long mask){append("armor:%ld;",mask);return opts[12]?&objs[14]:NULL;}
char *Yobjnam2(struct obj *o,const char *verb){return Tobjnam(o,verb);}
const char *hcolor(const char *s){append("color:%s;",s);return s;}
void see_monsters(void){append("see-monsters;");}
void set_mimic_blocking(void){append("mimic-block;");}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/sit.c"
#else
extern void teleport_sit_test_throne(void),teleport_sit_test_special(int);
extern int teleport_sit_test_egg(void);
#endif
#include "tu-sit-layout.h"
void probe_reset(unsigned seed){int i;if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&svl,0,sizeof svl);memset(&svd,0,sizeof svd);memset(objs,0,sizeof objs);memset(&steed,0,sizeof steed);memset(&holder,0,sizeof holder);memset(&fixture_trap,0,sizeof fixture_trap);memset(opts,0,sizeof opts);opts[0]=opts[5]=1;opts[2]='n';opts[3]=-1;monst_globals_init();objects_globals_init();for(i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=i;objects[i].oc_descr_idx=i;}u.ux=10;u.uy=10;u.uz.dnum=0;u.uz.dlevel=1;water_level.dnum=9;water_level.dlevel=9;svd.dungeons[2].num_dunlevs=20;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];steed.data=holder.data=&mons[PM_HUMAN];u.uhp=30;u.uhpmax=40;u.uhppeak=40;u.mh=20;u.mhmax=30;u.ulevel=u.ulevelmax=10;u.uhunger=500;for(i=0;i<A_MAX;i++)u.acurr.a[i]=10;for(i=0;i<ROWNO;i++)visionrows[i]=vision[i];gv.viz_array=visionrows;memset(vision,IN_SIGHT,sizeof vision);uwep=uarm=uarmf=NULL;random_length=random_index=0;random_state=seed;tracebuf[0]=caller[0]=inputbuf[0]=0;levl[10][10].typ=ROOM;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int i,int value){opts[i]=value;if(i==13)memset(vision,value?IN_SIGHT:0,sizeof vision);}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_obj(int i,int type,long quantity,int where){struct obj *o=&objs[i];memset(o,0,sizeof *o);o->o_id=100+i;o->otyp=type;o->oclass=objects[type].oc_class;o->quan=quantity;o->where=where;o->corpsenm=PM_GREEN_SLIME;}
void probe_next(int a,int b){objs[a].nobj=b<0?NULL:&objs[b];}
void probe_inventory(int n){gi.invent=n<0?NULL:&objs[n];}
void probe_obit(int i,int field,long value){struct obj *o=&objs[i];switch(field){case 0:o->greased=value;break;case 1:o->blessed=value;break;case 2:o->known=value;break;case 3:o->cursed=value;break;case 4:o->bknown=value;break;case 5:o->oartifact=value;break;case 6:o->corpsenm=value;break;case 7:o->owornmask=value;break;case 8:o->where=value;break;case 9:uwep=value?o:NULL;break;case 10:uarm=value?o:NULL;break;case 11:uarmf=value?o:NULL;break;case 12:svl.level.objects[u.ux][u.uy]=value?o:NULL;break;}}
void probe_hero(int field,long value){switch(field){case 0:flags.female=value;break;case 1:wizard=value;break;case 2:iflags.debug_fuzzer=value;break;case 4:u.uhunger=value;break;case 5:u.ulevel=value;break;case 6:u.ulevelmax=value;break;case 7:u.uluck=value;break;case 8:u.moreluck=value;break;case 9:u.uhp=value;break;case 10:u.uhpmax=value;break;case 11:u.uhppeak=value;break;case 12:u.mh=value;break;case 13:u.mhmax=value;break;case 14:u.ucreamed=value;break;case 15:u.uundetected=value;break;case 16:u.usteed=value?&steed:NULL;break;case 17:u.ustuck=value?&holder:NULL;break;case 18:u.uswallow=value;break;case 19:u.uinwater=value;break;case 20:u.utrap=value;break;case 21:u.utraptype=value;break;case 22:u.uhave.amulet=value;break;case 23:u.uevent.uhand_of_elbereth=value;break;case 24:svl.level.flags.nommap=value;break;case 25:water_level.dnum=value?u.uz.dnum:9;water_level.dlevel=value?u.uz.dlevel:9;break;case 26:holder.data=&mons[value];break;case 27:u.uhunger=objects[EGG].oc_nutrition+value;break;case 28:u.uroleplay.deaf=value;break;}}
void probe_prop(int p,int field,long value){if(field==0)u.uprops[p].intrinsic=value;else if(field==1)u.uprops[p].extrinsic=value;else u.uprops[p].blocked=value;}
void probe_terrain(int x,int y,int type,int flags){levl[x][y].typ=type;levl[x][y].flags=flags;}
void probe_trap(int type){fixture_trap.ttyp=type;fixture_trap.tx=u.ux;fixture_trap.ty=u.uy;opts[4]=type!=0;}
void probe_species(int pm,int polymorphed){gy.youmonst.data=&mons[pm];u.umonnum=pm;u.umonster=polymorphed?PM_HUMAN:pm;}
void probe_input(const char *s){snprintf(inputbuf,sizeof inputbuf,"%s",s);}
int probe_action(int op,int effect){switch(op){case 0:take_gold();return 0;case 1:return dosit();case 2:rndcurse();return 0;case 3:return attrcurse();case 4:
#ifdef TELEPORT_REFERENCE_TU
throne_sit_effect();
#else
teleport_sit_test_throne();
#endif
return 0;case 5:
#ifdef TELEPORT_REFERENCE_TU
special_throne_effect(effect);
#else
teleport_sit_test_special(effect);
#endif
return 0;default:
#ifdef TELEPORT_REFERENCE_TU
return lay_an_egg();
#else
return teleport_sit_test_egg();
#endif
}}
void *probe_object_pointer(int n){return &objs[n];}
void *probe_hero_pointer(void){return &u;}
size_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){char *p=statebuf;int i,x,y;p+=sprintf(p,"hero:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d;",u.ux,u.uy,u.umonnum,u.umonster,u.ulevel,u.ulevelmax,u.uhp,u.uhpmax,u.uhppeak,u.mh,u.mhmax,u.uhunger,HConfusion,u.uluck,u.moreluck,u.ucreamed,u.uundetected,u.utrap,u.utraptype,disp.botl,oid(gi.invent),svl.level.flags.nommap);p+=sprintf(p,"attributes:");for(i=0;i<A_MAX;i++)p+=sprintf(p,"%d,",u.acurr.a[i]);for(i=0;i<=LAST_PROP;i++)p+=sprintf(p,";p%d:%ld:%ld:%ld",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);for(i=0;i<16;i++){struct obj *o=&objs[i];p+=sprintf(p,";o%d:%d:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld",i,oid(o->nobj),o->otyp,o->quan,o->where,o->oclass,o->spe,o->owt,o->corpsenm,o->greased,o->blessed,o->known,o->cursed,o->bknown,o->owornmask);}p+=sprintf(p,";equipment:%d:%d:%d;map:",oid(uwep),oid(uarm),oid(uarmf));for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)if(levl[x][y].typ||levl[x][y].flags||svl.level.objects[x][y])p+=sprintf(p,"%d,%d,%d,%d,%d/",x,y,levl[x][y].typ,levl[x][y].flags,oid(svl.level.objects[x][y]));return statebuf;}
