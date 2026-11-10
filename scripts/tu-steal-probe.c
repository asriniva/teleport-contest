#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
struct you u;
__typeof__(gy) gy;
__typeof__(gi) gi;
__typeof__(gs) gs;
__typeof__(ga) ga;
__typeof__(gn) gn;
__typeof__(gm) gm;
__typeof__(go) go;
__typeof__(gt) gt;
__typeof__(gk) gk;
__typeof__(svl) svl;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(disp) disp;
__typeof__(gv) gv;
static seenV vision[ROWNO][COLNO];
static seenV *visionrows[ROWNO];
struct obj *uarm,*uarmc,*uarmh,*uarms,*uarmg,*uarmf,*uarmu,*uskin,*uamul,*uleft,*uright,*ublindf,*uwep,*uswapwep,*uquiver,*uchain,*uball;
static struct obj objs[32];
static struct monst monsters[4];
static struct obj *floorhead;
static int opts[32],random_values[256],random_length,random_index;
static unsigned random_state;
static char tracebuf[262144],snapshotbuf[16384],caller[128],output[BUFSZ+32],reason[128],description[BUFSZ];
static void *growth;
static int oid(struct obj *o){return o?(int)(o-objs)+1:0;}
static int mid(struct monst *m){return m==&gy.youmonst?99:m?(int)(m-monsters)+1:0;}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),format,ap);va_end(ap);}
void panic(const char *format,...){abort();}
void impossible(const char *format,...){char b[BUFSZ];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("impossible:%s;",b);}
static void message(const char *kind,const char *format,va_list ap){char b[BUFSZ*2];vsnprintf(b,sizeof b,format,ap);append("%s:%s;",kind,b);iflags.last_msg=0;}
#define MSG(fn) void fn(const char *f,...){va_list a;va_start(a,f);message(#fn,f,a);va_end(a);}
MSG(pline) MSG(urgent_pline) MSG(You) MSG(Your)
void pline_mon(struct monst *m,const char *f,...){va_list a;append("message-mon:%d;",mid(m));va_start(a,f);message("pline_mon",f,a);va_end(a);}
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file,int line,const char *func){const char *p=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:file,line,func);}
int (rn2)(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){return (rn2)(n)+1;}
int Mgender(struct monst *m){append("gender:%d;",mid(m));return m->female?FEMALE:MALE;}
#ifndef PMNAME_MACROS
const char *pmname(struct permonst *p,int g){return (g==MALE||g==FEMALE)&&p->pmnames[g]?p->pmnames[g]:p->pmnames[NEUTRAL];}
#endif
char *Monnam(struct monst *m){return (char *)(m->data->pmnames[NEUTRAL]?m->data->pmnames[NEUTRAL]:"Monster");}
char *Some_Monnam(struct monst *m){return canseemon(m)?Monnam(m):(char *)(is_animal(m->data)?"Something":"Someone");}
char *Adjmonnam(struct monst *m,const char *a){static char b[BUFSZ];snprintf(b,sizeof b,"%s %s",a,Monnam(m));return b;}
char *y_monnam(struct monst *m){return Monnam(m);}
char *doname(struct obj *o){static char b[4][BUFSZ];static int i;char *p=b[(i++)%4];if(description[0])snprintf(p,BUFSZ,"%s",description);else snprintf(p,BUFSZ,"a fixture item %d%s",oid(o),o->owornmask?" (being worn)":"");return p;}
char *yname(struct obj *o){return doname(o);}
char *simpleonames(struct obj *o){append("simple:%d;",oid(o));return doname(o);}
const char *armor_simple_name(struct obj *o){return "fixture armor";}
char *Tobjnam(struct obj *o,const char *v){static char b[BUFSZ];snprintf(b,sizeof b,"%s %s",doname(o),v);return b;}
char *distant_name(struct obj *o,char *(*fn)(struct obj *)){append("distant:%d;",oid(o));return fn(o);}
char *otense(struct obj *o,const char *v){return o->quan>1?(char *)v:(char *)"is";}
const char *body_part(int p){append("body:%d;",p);return p==FOOT?"rear foot":"hand";}
const char *mbodypart(struct monst *m,int p){append("mbody:%d:%d;",mid(m),p);return "rear hoof";}
char *makeplural(const char *s){static char b[BUFSZ];snprintf(b,sizeof b,"%ss",s);return b;}
int canseemon(struct monst *m){append("visible:%d;",mid(m));return opts[1];}
int sensemon(struct monst *m){append("sense:%d;",mid(m));return opts[2];}
boolean monnear(struct monst *m,coordxy x,coordxy y){append("near:%d:%d:%d;",mid(m),x,y);return opts[4];}
boolean tele_restrict(struct monst *m){append("restrict:%d;",mid(m));return opts[5];}
boolean rloc(struct monst *m,unsigned f){append("rloc:%d:%u;",mid(m),f);m->mx=31;m->my=17;return TRUE;}
boolean rloco(struct obj *o){append("rloco:%d;",oid(o));o->where=OBJ_FLOOR;return TRUE;}
void monflee(struct monst *m,int n,boolean a,boolean b){append("flee:%d:%d:%d:%d;",mid(m),n,a,b);m->mflee=1;}
void newsym_force(coordxy x,coordxy y){append("newsym-force:%d:%d;",x,y);}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
boolean debugcore(const char *file,boolean wild){const char *p=strrchr(file,'/');append("debug:%s:%d;",p?p+1:file,wild);return opts[31];}
struct obj *g_at(coordxy x,coordxy y){append("floor:%d:%d;",x,y);return floorhead;}
static void unlink_obj(struct obj **head,struct obj *o){while(*head&&*head!=o)head=&(*head)->nobj;if(*head){*head=o->nobj;o->nobj=NULL;}}
void obj_extract_self(struct obj *o){int i;append("extract:%d;",oid(o));unlink_obj(&gi.invent,o);for(i=0;i<4;i++)unlink_obj(&monsters[i].minvent,o);if(floorhead==o)floorhead=o->nexthere;else{struct obj *p=floorhead;while(p&&p->nexthere!=o)p=p->nexthere;if(p)p->nexthere=o->nexthere;}o->nexthere=NULL;o->where=OBJ_FREE;}
void freeinv(struct obj *o){append("freeinv:%d;",oid(o));unlink_obj(&gi.invent,o);o->where=OBJ_FREE;}
static void callback_effect(void){if(opts[29]){opts[29]=0;append("nested:%d;",unresponsive());}if(opts[30]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grow;");}}
int add_to_minv(struct monst *m,struct obj *o){append("minv:%d:%d;",mid(m),oid(o));callback_effect();if(opts[6]&&m->minvent){m->minvent->quan+=o->quan;o->where=OBJ_DELETED;return 1;}o->nobj=m->minvent;m->minvent=o;o->where=OBJ_MINVENT;o->ocarry=m;return 0;}
long money_cnt(struct obj *o){long n=0;for(;o;o=o->nobj)if(o->oclass==COIN_CLASS)n+=o->quan;append("money:%ld;",n);return n;}
struct obj *splitobj(struct obj *o,long n){struct obj *p=&objs[31];append("split:%d:%ld;",oid(o),n);*p=*o;p->o_id=132;p->quan=n;o->quan-=n;p->nobj=o->nobj;o->nobj=p;return p;}
int inv_cnt(boolean gold){int n=0;struct obj *o;for(o=gi.invent;o;o=o->nobj)if(gold||o->oclass!=COIN_CLASS)n++;append("count:%d:%d;",gold,n);return n;}
boolean unconscious(void){append("unconscious;");return opts[7];}
boolean is_fainted(void){append("fainted;");return opts[8];}
boolean donning(struct obj *o){append("donning:%d;",oid(o));return opts[9];}
boolean doffing(struct obj *o){append("doffing:%d;",oid(o));return opts[10];}
int stop_donning(struct obj *o){append("stop-don:%d;",oid(o));return opts[11];}
void cancel_don(void){append("cancel-don;");}
void stop_occupation(void){append("stop-occupation;");go.occupation=NULL;}
boolean maybe_finished_meal(boolean b){append("meal:%d;",b);return FALSE;}
void nomul(int n){append("nomul:%d;",n);gm.multi=n;}
static void clear_worn(struct obj *o){struct obj **slots[]={&uarm,&uarmc,&uarmh,&uarms,&uarmg,&uarmf,&uarmu,&uskin,&uamul,&uleft,&uright,&ublindf,&uwep,&uswapwep,&uquiver};int i;if(o){append("off:%d:%u;",oid(o),o->in_use);o->owornmask=0;for(i=0;i<SIZE(slots);i++)if(*slots[i]==o)*slots[i]=NULL;}}
void setnotworn(struct obj *o){append("notworn:%d;",oid(o));clear_worn(o);}
void setworn(struct obj *o,long mask){int i;append("setworn:%d:%ld;",oid(o),mask);for(i=0;i<32;i++)if(objs[i].owornmask&mask)clear_worn(&objs[i]);}
#define PROBE_OFF(fn,slot) int fn(void){clear_worn(slot);return 0;}
PROBE_OFF(Armor_off,uarm) PROBE_OFF(Cloak_off,uarmc) PROBE_OFF(Boots_off,uarmf) PROBE_OFF(Gloves_off,uarmg) PROBE_OFF(Helmet_off,uarmh) PROBE_OFF(Shield_off,uarms) PROBE_OFF(Shirt_off,uarmu)
void Amulet_off(void){clear_worn(uamul);}
void Ring_gone(struct obj *o){clear_worn(o);}
void Blindf_off(struct obj *o){clear_worn(o);}
void uwepgone(void){clear_worn(uwep);}
void uswapwepgone(void){clear_worn(uswapwep);u.twoweap=0;}
void uqwepgone(void){clear_worn(uquiver);}
void unpunish(void){append("unpunish;");if(uchain){uchain->where=OBJ_DELETED;uchain->owornmask=0;}if(uball)uball->owornmask&=~W_BALL;uchain=uball=NULL;}
void skinback(boolean b){append("skin:%d;",b);uarm=uskin;uskin=NULL;}
boolean openholdingtrap(struct monst *m,boolean *b){append("open-trap:%d;",mid(m));*b=TRUE;u.utrap=0;return TRUE;}
int welded(struct obj *o){append("welded:%d;",oid(o));return opts[12];}
int can_carry(struct monst *m,struct obj *o){append("carry:%d:%d;",mid(m),oid(o));return opts[13];}
void o_unleash(struct obj *o){append("unleash:%d;",oid(o));o->leashmon=0;}
struct monst *shop_keeper(char c){append("shop:%d;",c);return &monsters[3];}
struct monst *find_objowner(struct obj *o,coordxy x,coordxy y){append("owner:%d:%d:%d;",oid(o),x,y);return &monsters[3];}
void subfrombill(struct obj *o,struct monst *m){append("bill:%d:%d;",oid(o),mid(m));o->unpaid=0;}
int count_unpaid(struct obj *o){append("count-unpaid:%d;",oid(o));return opts[14];}
void unknow_object(struct obj *o){append("unknown:%d;",oid(o));o->known=o->dknown=0;}
boolean obj_sheds_light(struct obj *o){append("light:%d;",oid(o));return opts[15];}
void carry_obj_effects(struct obj *o){append("effects:%d;",oid(o));}
void snuff_light_source(coordxy x,coordxy y){append("snuff:%d:%d;",x,y);}
void encumber_msg(void){append("encumber;");}
void minstapetrify(struct monst *m,boolean b){append("petrify:%d:%d;",mid(m),b);m->mhp=0;}
boolean is_quest_artifact(struct obj *o){append("quest-artifact:%d;",oid(o));return o->oartifact==1;}
boolean obj_resists(struct obj *o,int ordinary,int art){append("resist:%d:%d:%d;",oid(o),ordinary,art);return opts[16]||o->otyp==AMULET_OF_YENDOR;}
int touch_artifact(struct obj *o,struct monst *m){append("touch:%d:%d;",oid(o),mid(m));return opts[17];}
void extract_from_minvent(struct monst *m,struct obj *o,boolean a,boolean b){append("extract-minv:%d:%d:%d:%d;",mid(m),oid(o),a,b);unlink_obj(&m->minvent,o);o->where=OBJ_FREE;o->owornmask=0;}
boolean costly_spot(coordxy x,coordxy y){append("costly:%d:%d;",x,y);return opts[18];}
char *in_rooms(coordxy x,coordxy y,int type){append("rooms:%d:%d:%d;",x,y,type);return "\x11";}
boolean flooreffects(struct obj *o,coordxy x,coordxy y,const char *v){append("floor-effects:%d:%d:%d:%s;",oid(o),x,y,v);if(opts[19])o->where=OBJ_DELETED;return opts[19];}
void place_object(struct obj *o,coordxy x,coordxy y){append("place:%d:%d:%d;",oid(o),x,y);o->where=OBJ_FLOOR;o->ox=x;o->oy=y;o->nexthere=floorhead;floorhead=o;}
void stackobj(struct obj *o){append("stack:%d;",oid(o));}
void update_mon_extrinsics(struct monst *m,struct obj *o,boolean a,boolean b){append("extrinsics:%d:%d:%d:%d;",mid(m),oid(o),a,b);}
void obfree(struct obj *o,struct obj *other){append("obfree:%d:%d;",oid(o),oid(other));o->where=OBJ_DELETED;}
struct obj *droppables(struct monst *m){struct obj *o;append("droppable:%d;",mid(m));for(o=m->minvent;o;o=o->nobj)if(!o->owornmask)return o;return NULL;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/steal.c"
#else
extern int teleport_steal_test_stealarm(void);
extern int teleport_steal_test_unstolenarm(void);
extern void teleport_steal_test_worn(struct monst *,struct obj *);
#endif
#include "tu-steal-layout.h"
#ifndef TELEPORT_REFERENCE_TU
extern int teleport_steal_after_stealarm(void),teleport_steal_after_unstolenarm(void);
#endif
static int afterid(void){if(!ga.afternmv)return 0;
#ifdef TELEPORT_REFERENCE_TU
return ga.afternmv==stealarm?1:ga.afternmv==unstolenarm?2:99;
#else
return ga.afternmv==teleport_steal_after_stealarm?1:ga.afternmv==teleport_steal_after_unstolenarm?2:99;
#endif
}
boolean attacktype(struct permonst *p,int t){append("attack:%d:%d;",p->pmidx,t);return opts[20];}
boolean dmgtype(struct permonst *p,int t){append("damage:%d:%d;",p->pmidx,t);return opts[21];}
static int fixture_occupation(void){return 0;}
static int unrelated_after(void){append("unrelated-after;");return 73;}
void probe_reset(unsigned seed){int i;if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&gs,0,sizeof gs);memset(&ga,0,sizeof ga);memset(&gn,0,sizeof gn);memset(&gm,0,sizeof gm);memset(&go,0,sizeof go);memset(&gt,0,sizeof gt);memset(&gk,0,sizeof gk);memset(&svl,0,sizeof svl);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(objs,0,sizeof objs);memset(monsters,0,sizeof monsters);memset(opts,0,sizeof opts);for(i=0;i<22;i++)opts[i]=1;opts[2]=opts[5]=opts[6]=opts[7]=opts[8]=opts[9]=opts[10]=opts[11]=opts[12]=opts[14]=opts[15]=opts[16]=opts[18]=opts[19]=opts[20]=0;monst_globals_init();objects_globals_init();for(i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=i;objects[i].oc_descr_idx=i;}u.ux=10;u.uy=10;gy.youmonst.data=&mons[PM_HUMAN];uarm=uarmc=uarmh=uarms=uarmg=uarmf=uarmu=uskin=uamul=uleft=uright=ublindf=uwep=uswapwep=uquiver=uchain=uball=NULL;for(i=0;i<4;i++){monsters[i].m_id=200+i;monsters[i].data=&mons[PM_WOOD_NYMPH];monsters[i].mx=11;monsters[i].my=10;monsters[i].mhp=monsters[i].mhpmax=20;if(i<3)monsters[i].nmon=&monsters[i+1];}fmon=monsters;for(i=0;i<ROWNO;i++)visionrows[i]=vision[i];gv.viz_array=visionrows;memset(vision,IN_SIGHT,sizeof vision);floorhead=NULL;random_length=random_index=0;random_state=seed;tracebuf[0]=caller[0]=reason[0]=description[0]=0;memset(output,0xa5,sizeof output);flags.verbose=1;u.ushops[0]='Q';}
const char *probe_trace(void){return tracebuf;}
void probe_option(int i,int n){opts[i]=n;if(i==3)memset(vision,n?IN_SIGHT:0,sizeof vision);}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
static struct obj *obj(int i){return i<0?NULL:&objs[i];}
void probe_obj(int i,int type,long quantity,int where){struct obj *o=obj(i);memset(o,0,sizeof *o);o->o_id=100+i;o->otyp=type;o->oclass=objects[type].oc_class;o->quan=quantity;o->where=where;o->known=o->dknown=1;o->corpsenm=PM_COCKATRICE;}
void probe_next(int a,int b,int floor){if(floor)objs[a].nexthere=obj(b);else objs[a].nobj=obj(b);}
void probe_inventory(int i){gi.invent=obj(i);}
void probe_floor(int i){floorhead=obj(i);}
void probe_minvent(int m,int i){monsters[m].minvent=obj(i);if(i>=0)objs[i].ocarry=&monsters[m];}
void probe_equipment(int n,int i){struct obj **slots[]={&uskin,&uarm,&uarmc,&uarmf,&uarmg,&uarmh,&uarms,&uarmu,&uwep,&uswapwep,&uquiver,&uball,&uchain,&uleft,&uright,&uamul,&ublindf};*slots[n]=obj(i);}
void probe_obit(int i,int bit,long value){struct obj *o=&objs[i];switch(bit){case 0:o->unpaid=value;break;case 1:o->cursed=value;break;case 2:o->in_use=value;break;case 3:o->no_charge=value;break;case 4:o->how_lost=value;break;case 5:o->known=value;break;case 6:o->dknown=value;break;case 7:o->owornmask=value;break;case 8:o->oartifact=value;break;case 9:o->leashmon=value;break;case 10:o->corpsenm=value;break;case 11:o->cobj=obj(value);break;case 12:o->where=value;break;case 13:o->otyp=value;break;case 14:o->oclass=value;break;case 15:o->o_id=value;break;}}
void probe_mbit(int m,int bit,long value){struct monst *p=&monsters[m];switch(bit){case 0:p->female=value;break;case 1:p->mavenge=value;break;case 2:p->iswiz=value;break;case 3:p->isgd=value;break;case 4:p->mtame=value;break;case 5:p->mhp=value;break;case 6:p->misc_worn_check=value;break;case 7:p->mx=value;break;case 8:p->my=value;break;case 9:p->m_id=value;break;}}
void probe_mon(int m,int pm){monsters[m].data=&mons[pm];}
void probe_monnext(int a,int b){monsters[a].nmon=b<0?NULL:&monsters[b];}
void probe_hero(int key,long value){switch(key){case 0:gm.multi=value;break;case 1:gs.stealoid=value;break;case 2:gs.stealmid=value;break;case 3:u.twoweap=value;break;case 4:u.uhave.amulet=value;break;case 5:u.uhave.bell=value;break;case 6:u.uhave.book=value;break;case 7:u.uhave.menorah=value;break;case 8:flags.female=value;break;case 9:gt.thrownobj=obj(value);break;case 10:gk.kickedobj=obj(value);break;case 11:u.ustuck=value<0?NULL:&monsters[value];break;case 12:u.usteed=value<0?NULL:&monsters[value];break;case 13:go.occupation=value?fixture_occupation:NULL;break;case 14:u.utrap=value;break;case 15:u.utraptype=value;break;case 16:gy.youmonst.data=&mons[value];break;case 17:iflags.last_msg=value;break;case 18:levl[11][10].roomno=value;break;case 19:flags.verbose=value;break;case 20:ga.afternmv=value?unrelated_after:NULL;break;case 21:u.uswallow=value;break;}}
void probe_prop(int p,int field,long value){if(field==0)u.uprops[p].intrinsic=value;else if(field==1)u.uprops[p].extrinsic=value;else u.uprops[p].blocked=value;}
void probe_reason(const char *s){if(s){snprintf(reason,sizeof reason,"%s",s);gm.multi_reason=reason;}else gm.multi_reason=NULL;}
void probe_description(const char *s){snprintf(description,sizeof description,"%s",s?s:"");}
long probe_action(int op,int m,int o,long a,long b){struct monst *p=&monsters[m];struct obj *q=obj(o);switch(op){case 0:return somegold(a);case 1:return oid(findgold(q));case 2:stealgold(p);break;case 3:thiefdead();break;case 4:return unresponsive();case 5:remove_worn_item(q,a);break;case 6:return steal(p,a?output:NULL);case 7:return mpickobj(p,q);case 8:stealamulet(p);break;case 9:maybe_absorb_item(p,q,a,b);break;case 10:mdrop_obj(p,q,a);break;case 11:mdrop_special_objs(p);break;case 12:relobj(p,a,b);break;case 13:
#ifdef TELEPORT_REFERENCE_TU
return stealarm();
#else
return teleport_steal_test_stealarm();
#endif
case 14:
#ifdef TELEPORT_REFERENCE_TU
return unstolenarm();
#else
return teleport_steal_test_unstolenarm();
#endif
case 15:
#ifdef TELEPORT_REFERENCE_TU
worn_item_removal(p,q);
#else
teleport_steal_test_worn(p,q);
#endif
break;}return 0;}
int probe_afternmv(int invoke){if(invoke)return ga.afternmv?ga.afternmv():-77;return afterid();}
void *probe_object_pointer(int n){return obj(n);}
void *probe_mon_pointer(int n){return &monsters[n];}
const char *probe_output(void){return output;}
size_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){int i;char *p=snapshotbuf;struct obj **slots[]={&uskin,&uarm,&uarmc,&uarmf,&uarmg,&uarmh,&uarms,&uarmu,&uwep,&uswapwep,&uquiver,&uball,&uchain,&uleft,&uright,&uamul,&ublindf};p+=sprintf(p,"hero:%ld:%u:%u:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%s:%s;",gm.multi,gs.stealoid,gs.stealmid,afterid(),gn.nomovemsg!=NULL,disp.botl,iflags.last_msg,oid(gi.invent),oid(floorhead),oid(gt.thrownobj),oid(gk.kickedobj),u.twoweap,u.utrap,go.occupation!=NULL,gm.multi_reason?gm.multi_reason:"NULL",gn.nomovemsg?gn.nomovemsg:"NULL");for(i=0;i<SIZE(slots);i++)p+=sprintf(p,"e%d:%d;",i,oid(*slots[i]));for(i=0;i<32;i++){struct obj *o=&objs[i];p+=sprintf(p,"o%d:%d:%d:%d:%u:%d:%ld:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%u;",i,oid(o->nobj),o->where==OBJ_FLOOR?oid(o->nexthere):o->where==OBJ_MINVENT?-mid(o->ocarry):0,oid(o->cobj),o->o_id,o->otyp,o->quan,o->owornmask,o->where,o->oclass,o->unpaid,o->cursed,o->in_use,o->no_charge,o->how_lost,o->known,o->dknown,o->oartifact,o->leashmon);}for(i=0;i<4;i++){struct monst *m=&monsters[i];p+=sprintf(p,"m%d:%d:%d:%d:%u:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld;",i,mid(m->nmon),oid(m->minvent),m->data->pmidx,m->m_id,m->mx,m->my,m->mhp,m->female,m->mavenge,m->iswiz,m->isgd,m->mtame,m->mflee,m->misc_worn_check);}return snapshotbuf;}
