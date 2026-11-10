/* Controlled native world boundaries; every worn algorithm stays in the TU. */
#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef free
extern void free(void *);
struct you u;
__typeof__(gy) gy; __typeof__(gi) gi; __typeof__(gu) gu;
__typeof__(gm) gm; __typeof__(gb) gb; __typeof__(go) go;
__typeof__(svc) svc; __typeof__(svl) svl; __typeof__(gv) gv;
__typeof__(flags) flags; __typeof__(iflags) iflags; __typeof__(disp) disp;
struct obj *uarm,*uarmc,*uarmh,*uarms,*uarmg,*uarmf,*uarmu,*uleft,*uright;
struct obj *uwep,*uswapwep,*uquiver,*uamul,*ublindf,*uball,*uchain,*uskin;
const struct c_color_names c_color_names={.c_black="black"};
const struct c_common_strings c_common_strings={.c_Something="Something"};
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
static struct obj **slots[]={&uarm,&uarmc,&uarmh,&uarms,&uarmg,&uarmf,&uarmu,&uleft,&uright,&uwep,&uswapwep,&uquiver,&uamul,&ublindf,&uball,&uchain,&uskin};
static struct obj *pool[32],*retired[32];
static struct monst monsters[8];
static Loot loot[16];
static seenV vision[ROWNO][COLNO],*vision_rows[ROWNO];
static int opts[48],rolls[256],nr,ri,frees;
static unsigned seed;
static char tracebuf[262144],statebuf[262144],caller[128];
static void *growth;
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
static int oid(const struct obj *o){if(!o)return -1;for(int i=0;i<32;i++)if(o==pool[i]||o==retired[i])return i;return 99;}
static int mid(const struct monst *m){if(!m)return -1;if(m==&gy.youmonst)return 8;for(int i=0;i<8;i++)if(m==&monsters[i])return i;return 99;}
static struct obj *object_at(int i){return i<0?NULL:i>=32?retired[i-32]:pool[i];}
static struct monst *monster_at(int i){return i<0?NULL:i==8?&gy.youmonst:&monsters[i];}
static void callback(int stage){
    if(opts[30]==stage){opts[30]=0;recalc_telepat_range();append("nested:%d;",u.unblind_telepat_range);}
    if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}
    if(opts[32]==stage){opts[32]=0;*slots[opts[33]]=object_at(opts[34]);append("replace:%d:%d;",opts[33],opts[34]);}
}
void panic(const char *fmt,...){abort();}
#define MESSAGE(fn) void fn(const char *fmt,...){char b[BUFSZ*4];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#fn ":%s;",b);}
MESSAGE(impossible) MESSAGE(pline) MESSAGE(You) MESSAGE(You_hear)
void pline_mon(struct monst *m,const char *fmt,...){char b[BUFSZ*4];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline-mon:%d:%s;",mid(m),b);}
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file,int line,const char *fn){const char *p=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:file,line,fn);}
int (rnl)(int n){if(n<=0)abort();seed=seed*1664525U+1013904223U;int r=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;append("rnl:%d:%d@%s;",n,r,caller);return r;}
void teleport_probe_free(void *p){if(!p)return;for(int i=0;i<32;i++)if(p==pool[i]){append("free:%d;",i);retired[i]=pool[i];pool[i]=NULL;frees++;break;}free(p);}
void set_twoweap(boolean on){append("twoweap:%d;",on);u.twoweap=on;}
void cancel_doff(struct obj *o,long mask){append("cancel:%d:%lu;",oid(o),(unsigned long)mask);callback(1);}
unsigned long cvt_prop_to_mseenres(uchar p){append("seen-prop:%d;",p);return p?0x1000UL+(unsigned)p:0;}
void monstunseesu(unsigned long mask){append("unsee:%lu;",mask);callback(4);}
void set_artifact_intrinsic(struct obj *o,boolean on,long mask){append("artifact:%d:%d:%lu;",oid(o),on,(unsigned long)mask);callback(2);}
void update_inventory(void){append("inventory;");callback(3);}
boolean is_art(struct obj *o,int artifact){append("is-art:%d:%d;",oid(o),artifact);return o&&o->oartifact==artifact;}
int canseemon(struct monst *m){append("visible:%d:%d;",mid(m),opts[1]);callback(13);return opts[1];}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);callback(6);}
void see_wsegs(struct monst *m){append("segments:%d;",mid(m));}
void learnwand(struct obj *o){append("learn:%d;",oid(o));callback(5);}
void check_gear_next_turn(struct monst *m){append("gear:%d;",mid(m));}
void obj_no_longer_held(struct obj *o){append("unheld:%d;",oid(o));}
void mwepgone(struct monst *m){append("weapon-gone:%d;",mid(m));m->mw=NULL;m->weapon_check=NEED_WEAPON;}
const struct permonst *raceptr(struct monst *m){append("race:%d;",mid(m));return m==&gy.youmonst?&mons[u.umonnum]:m->data;}
boolean artifact_light(struct obj *o){append("light:%d:%lu;",oid(o),(unsigned long)o->owornmask);return opts[3]&&o->oartifact;}
void begin_burn(struct obj *o,boolean timer){append("begin:%d:%d;",oid(o),timer);o->lamplit=1;callback(10);}
void end_burn(struct obj *o,boolean timer){append("end:%d:%d;",oid(o),timer);o->lamplit=0;callback(10);}
void vision_recalc(int why){append("vision:%d;",why);callback(12);}
void curse(struct obj *o){append("curse:%d;",oid(o));o->cursed=1;o->blessed=0;}
void discover_object(int typ,boolean mark,boolean credit,boolean disclose){append("known:%d:%d:%d:%d;",typ,mark,credit,disclose);if(mark)objects[typ].oc_name_known=1;}
boolean can_saddle(struct monst *m){append("saddle:%d;",mid(m));return opts[4];}
boolean can_ride(struct monst *m){append("ride:%d;",mid(m));return opts[5];}
void dismount_steed(int reason){append("dismount:%d:%d;",reason,mid(u.usteed));u.usteed=NULL;callback(11);}
void instapetrify(const char *why){append("petrify:%s;",why);}
const char *surface(coordxy x,coordxy y){append("surface:%d:%d;",x,y);return "floor";}
char *Monnam(struct monst *m){append("Monnam:%d;",mid(m));return "Creature";}
char *mon_nam(struct monst *m){append("mon-name:%d;",mid(m));return "the creature";}
int Mgender(struct monst *m){append("gender:%d;",mid(m));return m->female?FEMALE:MALE;}
int pronoun_gender(struct monst *m,unsigned flagsarg){append("pronoun:%d:%u;",mid(m),flagsarg);return opts[6];}
const char *pmname(struct permonst *pm,int gender){append("pmname:%d:%d;",pm->pmidx,gender);return pm->pmnames[gender]?pm->pmnames[gender]:pm->pmnames[NEUTRAL];}
const char *mon_pmname(struct monst *m){return pmname(m->data,m->female?FEMALE:MALE);}
static char names[16][BUFSZ];static unsigned name_index;
char *doname(struct obj *o){char *b=names[name_index++%16];append("doname:%d;",oid(o));snprintf(b,BUFSZ,"a %s",OBJ_NAME(objects[o->otyp])?OBJ_NAME(objects[o->otyp]):"object");return b;}
char *simpleonames(struct obj *o){append("simple:%d;",oid(o));return "helmet";}
char *Yname2(struct obj *o){append("Yname:%d;",oid(o));return "The armor";}
char *otense(struct obj *o,const char *verb){append("tense:%d:%s;",oid(o),verb);return (char*)verb;}
const char *cloak_simple_name(struct obj *o){append("cloak:%d;",oid(o));return "cloak";}
const char *arti_light_description(struct obj *o){append("light-desc:%d;",oid(o));return "brightly";}
const char *hcolor(const char *color){append("hcolor:%s;",color);return color;}
char *an(const char *s){char *b=names[name_index++%16];append("an:%s;",s);snprintf(b,BUFSZ,"a %s",s);return b;}
char *distant_name(struct obj *o,char *(*fn)(struct obj*)){append("distant:%d:%d;",oid(o),fn==doname);return fn(o);}
void obj_extract_self(struct obj *o){
    struct obj **head=NULL;append("extract:%d:%d;",oid(o),o->where);
    if(o->where==OBJ_MINVENT)head=&o->ocarry->minvent;else if(o->where==OBJ_INVENT)head=&gi.invent;else if(o->where==OBJ_FLOOR)head=&fobj;
    if(head){while(*head&&*head!=o)head=&(*head)->nobj;if(*head)*head=o->nobj;}
    o->nobj=NULL;o->where=OBJ_FREE;o->ocarry=NULL;callback(7);
}
void place_object(struct obj *o,coordxy x,coordxy y){append("place:%d:%d:%d;",oid(o),x,y);o->where=OBJ_FLOOR;o->ox=x;o->oy=y;o->nobj=fobj;fobj=o;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;callback(8);}
void m_useup(struct monst *m,struct obj *o){append("useup:%d:%d;",mid(m),oid(o));callback(9);if(o->quan>1){o->quan--;return;}extract_from_minvent(m,o,TRUE,FALSE);teleport_probe_free(o);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/worn.c"
#undef free
#else
extern void teleport_worn_test_lose(struct monst*,struct obj*,boolean),teleport_worn_test_clear(struct obj*),teleport_worn_test_type(struct monst*,long,boolean,boolean);
extern int teleport_worn_test_pref(struct monst*,struct obj*);
#define m_lose_armor teleport_worn_test_lose
#define clear_bypass teleport_worn_test_clear
#define m_dowear_type teleport_worn_test_type
#define extra_pref teleport_worn_test_pref
#endif
#include "tu-worn-layout.h"
void probe_reset(unsigned initial){
    for(int i=0;i<32;i++){free(pool[i]);pool[i]=NULL;retired[i]=NULL;}for(int i=0;i<8;i++)free(monsters[i].mextra);free(growth);growth=NULL;
    memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&gu,0,sizeof gu);memset(&gm,0,sizeof gm);memset(&gb,0,sizeof gb);memset(&go,0,sizeof go);memset(&svc,0,sizeof svc);memset(&svl,0,sizeof svl);memset(&gv,0,sizeof gv);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(monsters,0,sizeof monsters);memset(loot,0,sizeof loot);memset(opts,0,sizeof opts);
    for(int y=0;y<ROWNO;y++)vision_rows[y]=vision[y];gv.viz_array=vision_rows;memset(vision,IN_SIGHT,sizeof vision);
    objects_globals_init();monst_globals_init();for(int i=0;i<32;i++){pool[i]=calloc(1,sizeof *pool[i]);if(!pool[i])abort();pool[i]->o_id=i+1;pool[i]->otyp=HELMET;pool[i]->oclass=ARMOR_CLASS;pool[i]->quan=1;}
    for(int i=0;i<8;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].m_id=100+i;monsters[i].mx=10+i;monsters[i].my=10;monsters[i].mhp=monsters[i].mhpmax=30;monsters[i].mcanmove=1;}
    gy.youmonst.data=&mons[PM_HUMAN];u.umonnum=u.umonster=PM_HUMAN;u.ux=u.uy=10;gu.urole.mnum=PM_ARCHEOLOGIST;
    for(int i=0;i<SIZE(slots);i++)*slots[i]=NULL;opts[0]=opts[1]=opts[4]=opts[5]=1;flags.verbose=1;seed=initial;nr=ri=frees=0;name_index=0;tracebuf[0]=caller[0]=statebuf[0]=0;
}
void probe_option(int k,int value){opts[k]=value;if(k==7)memset(vision,value?IN_SIGHT:0,sizeof vision);}
int *probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nr=n;ri=0;}int probe_rng_count(void){return ri;}unsigned probe_rng_state(void){return seed;}
void probe_object(int i,int field,long v){struct obj *o=pool[i];switch(field){case 0:o->otyp=v;o->oclass=objects[v].oc_class;break;case 1:o->owornmask=v;break;case 2:o->spe=v;break;case 3:o->quan=v;break;case 4:o->nobj=object_at(v);break;case 5:o->cobj=object_at(v);break;case 6:o->bypass=v;break;case 7:o->cursed=v;break;case 8:o->oartifact=v;break;case 9:o->lamplit=v;break;case 10:o->oeroded=v;break;case 11:o->oeroded2=v;break;case 12:o->where=v;break;case 13:o->ocarry=monster_at(v);break;case 14:o->nexthere=object_at(v);break;case 15:o->oclass=v;break;}}
void probe_set_monster(int i,int field,long v){struct monst *m=monster_at(i);switch(field){case 0:m->data=&mons[v];if(i==8)u.umonnum=v;break;case 1:m->minvent=object_at(v);break;case 2:m->misc_worn_check=v;break;case 3:m->mw=object_at(v);break;case 4:m->nmon=monster_at(v);break;case 5:m->mhp=v;break;case 6:m->permspeed=v;break;case 7:m->mspeed=v;break;case 8:m->minvis=v;break;case 9:m->perminvis=v;break;case 10:m->invis_blkd=v;break;case 11:m->wormno=v;break;case 12:m->msleeping=v;break;case 13:m->mcanmove=v;break;case 14:m->mfrozen=v;break;case 15:m->ispriest=v;break;case 16:m->isminion=v;break;case 17:m->female=v;break;case 18:if(!m->mextra)m->mextra=calloc(1,sizeof *m->mextra);MCORPSENM(m)=v;break;case 19:m->mhpmax=v;break;}}
void probe_hero(int field,long v){switch(field){case 0:gu.urole.mnum=v;break;case 1:u.twoweap=v;break;case 2:u.uroleplay.nudist=v;break;case 3:gi.in_mklev=v;break;case 4:flags.verbose=v;break;case 5:flags.weaponstatus=v;break;case 6:flags.armorstatus=v;break;case 7:u.usteed=monster_at(v);break;case 8:u.umonnum=v;break;case 9:u.umonster=v;break;case 10:gu.urole.spelarmr=v;break;case 11:svc.context.bypasses=v;break;case 12:iflags.tux_penalty=v;break;case 13:disp.botl=v;break;case 14:u.uluck=v;break;}}
void probe_prop(int p,int field,long v){if(field==0)u.uprops[p].intrinsic=v;else if(field==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_class(int typ,int field,int v){switch(field){case 0:objects[typ].oc_oprop=v;break;case 1:objects[typ].a_ac=v;break;case 2:objects[typ].oc_delay=v;break;case 3:objects[typ].oc_material=v;break;case 4:objects[typ].oc_subtyp=v;break;}}
void probe_equip(int slot,int i){*slots[slot]=object_at(i);}
void probe_link(int kind,int i){switch(kind){case 0:gi.invent=object_at(i);break;case 1:fobj=object_at(i);break;case 2:gm.migrating_objs=object_at(i);break;case 3:svl.level.buriedobjlist=object_at(i);break;case 4:gb.billobjs=object_at(i);break;case 5:go.objs_deleted=object_at(i);break;case 6:fmon=monster_at(i);break;case 7:gm.migrating_mons=monster_at(i);break;case 8:gm.mydogs=monster_at(i);break;}}
void probe_loot(int at,int i){loot[at].obj=object_at(i);}
long probe_action(int op,int i,int a,int b,long mask){struct obj *o=object_at(i);struct monst *m=i<=8?monster_at(i):NULL;switch(op){case 0:recalc_telepat_range();break;case 1:setworn(o,mask);break;case 2:setnotworn(o);break;case 3:allunworn();break;case 4:return oid(wearmask_to_obj(mask));case 5:return wornmask_to_armcat(mask);case 6:return armcat_to_wornmask(a);case 7:return wearslot(o);case 8:check_wornmask_slots();break;case 9:mon_set_minvis(m,a);break;case 10:mon_adjust_speed(m,a,object_at(b));break;case 11:update_mon_extrinsics(m,object_at(a),b,mask);break;case 12:return find_mac(m);case 13:m_dowear(m,a);break;case 14:m_dowear_type(m,mask,a,b);break;case 15:return oid(which_armor(m,mask));case 16:m_lose_armor(m,object_at(a),b);break;case 17:clear_bypass(o);break;case 18:clear_bypasses();break;case 19:bypass_obj(o);break;case 20:bypass_objlist(o,a);break;case 21:return oid(nxt_unbypassed_obj(o));case 22:return oid(nxt_unbypassed_loot(loot,o));case 23:mon_break_armor(m,a);break;case 24:return extra_pref(m,object_at(a));case 25:return racial_exception(m,object_at(a));case 26:extract_from_minvent(m,object_at(a),b,mask);break;}return 0;}
void *probe_pointer(int kind,int i){switch(kind){case 0:return object_at(i);case 1:return monster_at(i);case 2:return slots[i];case 3:return &objects[i];case 4:return &mons[i];case 5:return loot;case 6:return u.uprops;case 7:return &u;case 8:return &svc.context;case 9:return svl.level.objects;}return NULL;}
const char *probe_trace(void){return tracebuf;}int probe_free_count(void){return frees;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_worn_table_count(void){
#ifdef TELEPORT_REFERENCE_TU
return SIZE(worn);
#else
return 0;
#endif
}
unsigned long probe_worn_mask(int i){
#ifdef TELEPORT_REFERENCE_TU
return worn[i].w_mask;
#else
return 0;
#endif
}
const char *probe_worn_what(int i){
#ifdef TELEPORT_REFERENCE_TU
return worn[i].w_what;
#else
return NULL;
#endif
}
void *probe_worn_cell(int i){
#ifdef TELEPORT_REFERENCE_TU
return worn[i].w_obj;
#else
return NULL;
#endif
}
const char *probe_snapshot(void){char *p=statebuf;
    p+=sprintf(p,"hero:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;equip:",u.unblind_telepat_range,u.twoweap,u.uroleplay.nudist,gi.in_mklev,flags.verbose,iflags.tux_penalty,disp.botl,svc.context.bypasses,mid(u.usteed),u.umonnum,gu.urole.mnum);
    for(int i=0;i<SIZE(slots);i++)p+=sprintf(p,"%d,",oid(*slots[i]));
    p+=sprintf(p,";heads:%d:%d:%d:%d:%d:%d:%d:%d:%d;free:%d;props:",oid(gi.invent),oid(fobj),oid(gm.migrating_objs),oid(svl.level.buriedobjlist),oid(gb.billobjs),oid(go.objs_deleted),mid(fmon),mid(gm.migrating_mons),mid(gm.mydogs),frees);
    for(size_t j=0;j<sizeof u.uprops;j++)p+=sprintf(p,"%02x",((unsigned char*)u.uprops)[j]);
    for(int i=0;i<32;i++){struct obj *o=pool[i];if(!o){p+=sprintf(p,";o%d:freed",i);continue;}p+=sprintf(p,";o%d:%d:%lu:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",i,o->otyp,(unsigned long)o->owornmask,o->spe,o->quan,o->where,oid(o->nobj),oid(o->cobj),oid(o->nexthere),mid(o->ocarry),o->bypass,o->cursed,o->lamplit,o->oeroded,o->oeroded2,o->oartifact);}
    for(int i=0;i<8;i++){struct monst *m=&monsters[i];p+=sprintf(p,";m%d:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",i,m->data->pmidx,m->misc_worn_check,oid(m->minvent),oid(m->mw),mid(m->nmon),m->mhp,m->permspeed,m->mspeed,m->minvis,m->perminvis,m->invis_blkd,m->wormno,m->msleeping,m->mcanmove,m->mfrozen,m->ispriest,m->isminion,m->female,m->mextra?MCORPSENM(m):-99);}
    p+=sprintf(p,";vision:");for(size_t i=0;i<sizeof vision;i++)p+=sprintf(p,"%02x",((unsigned char*)vision)[i]);
    p+=sprintf(p,";loot:");for(int i=0;i<16;i++)p+=sprintf(p,"%d,",oid(loot[i].obj));p+=sprintf(p,";grid:");for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)if(svl.level.objects[x][y])p+=sprintf(p,"%d,%d,%d/",x,y,oid(svl.level.objects[x][y]));return statebuf;
}
