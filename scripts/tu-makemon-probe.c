/* Private MAKEMON original C/imported JS comparison; foreign dungeon/world seams controlled. */
#define NEED_VARARGS
#include "hack.h"
#include <stdarg.h>
#include <stdint.h>
#include <setjmp.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(svd) svd;
__typeof__(u) u;
__typeof__(gi) gi;
__typeof__(gu) gu;
__typeof__(svl) svl;
__typeof__(svm) svm;
__typeof__(svc) svc;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(gv) gv;
__typeof__(gs) gs;
__typeof__(cg) cg;
__typeof__(svq) svq;
__typeof__(uwep) uwep;
__typeof__(gm) gm;
__typeof__(go) go;
__typeof__(windowprocs) windowprocs;
__typeof__(svr) svr;
const struct c_common_strings c_common_strings =
    { "Nothing happens.",
      "Nothing seems to happen.",
      "That's enough tries!",
      "That is a silly thing to %s.",
      "shudder for a moment.",
      "something",
      "Something",
      "You can move again.",
      "Never mind.",
      "vision quickly clears.",
      { "the", "your" },
      { "mon", "you" }
};
const struct class_sym def_monsyms[MAXMCLASSES] = {
    { '\0', "", "" },
#define MONSYMS_DRAWING
#include "defsym.h"
#undef MONSYMS_DRAWING
};
const struct Gender genders[] = {
    { "male", "he", "him", "his", "Mal", ROLE_MALE },
    { "female", "she", "her", "her", "Fem", ROLE_FEMALE },
    { "neuter", "it", "it", "its", "Ntr", ROLE_NEUTER },
    /* used by pronoun_gender() when hallucinating */
    { "group", "they", "them", "their", "Grp", 0 },
};
struct enum_dump monsdump[NUMMONS];
static char tracebuf[2097152],snapshotbuf[2097152],namesbuf[NUMMONS][24],textbuf[32][256],origin[120];
static struct monst monpool[128];static struct obj objpool[256];static struct mextra mextrapool[128];static struct emin eminpool[128];static struct edog edogpool[128];static struct epri epripool[128];static anything anypool[8];static struct s_level special;
static int opts[128],monnext,objnext,serial,alloccount,freecount,callbackdepth;static unsigned rngstate;static jmp_buf fixture_jump;static void*growth;
static void logmsg(const char*f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
static int id(const void*p){if(!p)return -1;if((uintptr_t)p>=(uintptr_t)monpool&&(uintptr_t)p<(uintptr_t)(monpool+128))return 10000+(int)((uintptr_t)p-(uintptr_t)monpool);if((uintptr_t)p>=(uintptr_t)objpool&&(uintptr_t)p<(uintptr_t)(objpool+256))return 100000+(int)((uintptr_t)p-(uintptr_t)objpool);if((uintptr_t)p>=(uintptr_t)mons&&(uintptr_t)p<(uintptr_t)(mons+NUMMONS+1))return 1000000+(int)((uintptr_t)p-(uintptr_t)mons);return 999;}
static void callback(void);
static char*named(const char*s){static int i;char*p=textbuf[i++%32];snprintf(p,256,"%s",s);return p;}
void panic(const char*f,...){logmsg("panic:%s;",f);longjmp(fixture_jump,1);}
long*alloc(unsigned n){alloccount++;logmsg("alloc:%u;",n);void*p=malloc(n);if(!p)longjmp(fixture_jump,1);return p;}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*f,int line,const char*fn){snprintf(origin,sizeof origin,"%s:%d:%s",f,line,fn);}
int(rn2)(int n){if(n<=0){logmsg("BADRNG:%d;",n);longjmp(fixture_jump,1);}rngstate=rngstate*1664525u+1013904223u;int r=(rngstate>>8)%n;logmsg("rng:%d:%d@%s;",n,r,origin);return r;}
int(rnd)(int n){return(rn2)(n)+1;}int(d)(int n,int s){int total=0;for(int i=0;i<n;i++)total+=(rn2)(s)+1;return total;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
struct obj*mksobj(int typ,boolean init,boolean arti){struct obj*o=&objpool[objnext++%256];memset(o,0,sizeof *o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;o->spe=opts[2];logmsg("mksobj:%d:%d:%d;",typ,init,arti);callback();return o;}
struct obj*mkobj(int cls,boolean arti){int typ=opts[3]?opts[3]:DAGGER;logmsg("mkobj:%d:%d;",cls,arti);return mksobj(typ,TRUE,arti);}
struct obj*mkobj_at(char cls,coordxy x,coordxy y,boolean arti){logmsg("mkobjat:%d:%d:%d;",cls,x,y);return mkobj(cls,arti);}
int add_to_minv(struct monst*m,struct obj*o){logmsg("add:%d:%d;",id(m),id(o));if(opts[4])return 1;o->nobj=m->minvent;m->minvent=o;return 0;}int mpickobj(struct monst*m,struct obj*o){return add_to_minv(m,o);}
struct obj*add_to_container(struct obj*a,struct obj*b){logmsg("container:%d:%d;",id(a),id(b));b->nobj=a->cobj;a->cobj=b;return b;}
void obfree(struct obj*o,struct obj*merge){logmsg("obfree:%d:%d;",id(o),id(merge));}
void set_mon_data(struct monst*m,struct permonst*p){logmsg("setdata:%d:%d;",id(m),id(p));m->data=p;}
void place_monster(struct monst*m,coordxy x,coordxy y){m->mx=x;m->my=y;logmsg("place:%d:%d:%d;",id(m),x,y);svl.level.monsters[x][y]=m;callback();}
aligntyp mon_aligntyp(struct monst*m){return m->data->maligntyp;}
boolean goodpos(coordxy x,coordxy y,struct monst*m,mmflags_nht f){logmsg("good:%d:%d:%d:%d:%u;",x,y,id(m),m&&m->data?m->data->pmidx:-1,f);return opts[5]?x==opts[5]&&y==opts[6]:isok(x,y);}
boolean enexto_core(coord*c,coordxy x,coordxy y,struct permonst*p,mmflags_nht f){logmsg("enext:%d:%d:%d:%u;",x,y,id(p),f);if(opts[7])return FALSE;c->x=x<COLNO-2?x+1:1;c->y=y;return TRUE;}
boolean enexto_gpflags(coord*c,coordxy x,coordxy y,struct permonst*p,mmflags_nht f){return enexto_core(c,x,y,p,f);}boolean enexto(coord*c,coordxy x,coordxy y,struct permonst*p){return enexto_core(c,x,y,p,0);}
unsigned next_ident(void){return ++serial;}
void newemin(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->emin=&eminpool[(m->m_id)%128];logmsg("emin:%d;",id(m));}void newedog(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->edog=&edogpool[(m->m_id)%128];logmsg("edog:%d;",id(m));}void newepri(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->epri=&epripool[(m->m_id)%128];logmsg("epri:%d;",id(m));}
struct monst*christen_monst(struct monst*m,const char*s){if(!m->mextra)m->mextra=newmextra();m->mextra->mgivenname=(char*)s;logmsg("name:%d:%s;",id(m),s);return m;}boolean tamedog(struct monst*m,struct obj*o,boolean b){logmsg("tame:%d;",id(m));newedog(m);m->mtame=10;return TRUE;}
s_level*Is_special(d_level*l){logmsg("special:%d:%d;",l->dnum,l->dlevel);return opts[8]?&special:0;}struct permonst*qt_montype(void){return opts[9]?&mons[opts[9]]:0;}
anything*monst_to_any(struct monst*m){anypool[0].a_monst=m;return &anypool[0];}anything*obj_to_any(struct obj*o){anypool[1].a_obj=o;return &anypool[1];}
const char*pmname(struct permonst*p,int g){snprintf(textbuf[0],256,"creature%d%c",p->pmidx,g?'F':'M');return textbuf[0];}int pronoun_gender(struct monst*m,unsigned f){return m->female;}int pm_to_cham(int n){return opts[10]?opts[10]:NON_PM;}
boolean is_art(struct obj*o,int n){return o&&o->oartifact==n;}boolean debugcore(const char*f,boolean b){logmsg("debug:%s:%d;",f,b);return opts[11];}
#define MSG(name) void name(const char*f,...){va_list a;va_start(a,f);logmsg(#name ":");vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");callback();}
MSG(raw_printf)MSG(impossible)MSG(pline)MSG(Norep)
void pline_mon(struct monst*m,const char*f,...){va_list a;va_start(a,f);logmsg("pline_mon:%d:",id(m));vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");callback();}
void nh_snprintf(const char*fn,int line,char*out,size_t n,const char*f,...){va_list a;va_start(a,f);logmsg("snprintf:%s:%d;",fn,line);vsnprintf(out,n,f,a);va_end(a);}
int little_to_big(int n){return opts[12]?opts[12]:n;}
#ifdef TELEPORT_REFERENCE_TU
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/makemon.c"
#else
extern boolean teleport_makemon_test_wrong_elem_type(struct permonst *);
#define wrong_elem_type teleport_makemon_test_wrong_elem_type
extern void teleport_makemon_test_m_initgrp(struct monst *,coordxy,coordxy,int,mmflags_nht);
#define m_initgrp teleport_makemon_test_m_initgrp
extern void teleport_makemon_test_m_initthrow(struct monst *,int,int);
#define m_initthrow teleport_makemon_test_m_initthrow
extern void teleport_makemon_test_m_initweap(struct monst *);
#define m_initweap teleport_makemon_test_m_initweap
extern void teleport_makemon_test_m_initinv(struct monst *);
#define m_initinv teleport_makemon_test_m_initinv
extern void teleport_makemon_test_init_mextra(struct mextra *);
#define init_mextra teleport_makemon_test_init_mextra
extern boolean teleport_makemon_test_makemon_rnd_goodpos(struct monst *,mmflags_nht,coord *);
#define makemon_rnd_goodpos teleport_makemon_test_makemon_rnd_goodpos
extern boolean teleport_makemon_test_uncommon(int);
#define uncommon teleport_makemon_test_uncommon
extern int teleport_makemon_test_align_shift(struct permonst *);
#define align_shift teleport_makemon_test_align_shift
extern int teleport_makemon_test_temperature_shift(struct permonst *);
#define temperature_shift teleport_makemon_test_temperature_shift
extern boolean teleport_makemon_test_mk_gen_ok(int,unsigned int,unsigned int);
#define mk_gen_ok teleport_makemon_test_mk_gen_ok
extern int teleport_makemon_test_cmp_init_mongen_order(const void *,const void *);
#define cmp_init_mongen_order teleport_makemon_test_cmp_init_mongen_order
extern void teleport_makemon_test_init_mongen_order(void);
#define init_mongen_order teleport_makemon_test_init_mongen_order
#endif
#include "tu-makemon-layout.h"
#include "../nethack-c/wasm/tu-fragments/makemon-support.inc"
char * Amonnam(struct monst * a0){logmsg("Amonnam;" );return named("Amonnam");}
boolean In_V_tower(d_level * a0){logmsg("In_V_tower;" );return opts[26];}
boolean In_hell(d_level * a0){logmsg("In_hell;" );return opts[23];}
boolean In_mines(d_level * a0){logmsg("In_mines;" );return opts[25];}
boolean In_quest(d_level * a0){logmsg("In_quest;" );return opts[24];}
int Mgender(struct monst * a0){logmsg("Mgender;" );return a0->female;}
char * YMonnam(struct monst * a0){logmsg("YMonnam;" );return named("YMonnam");}
char * an(const char * a0){logmsg("an;" );return named("an");}
boolean attacktype(struct permonst * a0,int a1){logmsg("attacktype;" );return opts[20];}
void begin_burn(struct obj * a0,boolean a1){logmsg("begin_burn;" );callback();}
void bless(struct obj * a0){logmsg("bless;" );callback();}
void block_point(int a0,int a1){logmsg("block_point;" );callback();}
int can_be_hatched(int a0){logmsg("can_be_hatched;" );return opts[27];}
boolean can_saddle(struct monst * a0){logmsg("can_saddle;" );return opts[18];}
int canseemon(struct monst * a0){logmsg("canseemon;" );return opts[16];}
void consume_obj_charge(struct obj * a0,boolean a1){logmsg("consume_obj_charge;" );callback();}
int count_wsegs(struct monst * a0){logmsg("count_wsegs;" );return 0;}
boolean create_particular(void){logmsg("create_particular;" );return 0;}
void curse(struct obj * a0){logmsg("curse;" );callback();}
void deliver_obj_to_mon(struct monst * a0,int a1,unsigned long a2){logmsg("deliver_obj_to_mon;" );callback();}
schar depth(d_level * a0){logmsg("depth;" );return a0->dlevel;}
void discard_minvent(struct monst * a0,boolean a1){logmsg("discard_minvent;" );callback();}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object;" );callback();}
int dist2(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logmsg("dist2;" );return (a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
int dochugw(struct monst * a0,boolean a1){logmsg("dochugw;" );return 0;}
int does_block(int a0,int a1,struct rm * a2){logmsg("does_block;" );return opts[22];}
struct obj * findgold(struct obj * a0){logmsg("findgold;" );return 0;}
void freedynamicdata(void){logmsg("freedynamicdata;" );callback();}
int get_shop_item(int a0){logmsg("get_shop_item;" );return opts[28]?opts[14]:WEAPON_CLASS;}
int get_wormno(void){logmsg("get_wormno;" );return opts[15];}
boolean hideunder(struct monst * a0){logmsg("hideunder;" );return 0;}
boolean in_town(coordxy a0,coordxy a1){logmsg("in_town;" );return opts[21];}
void initworm(struct monst * a0,int a1){logmsg("initworm;" );callback();}
int isok(coordxy a0,coordxy a1){logmsg("isok;" );return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
xint16 level_difficulty(void){logmsg("level_difficulty;" );return opts[13]?opts[13]:8;}
void m_dowear(struct monst * a0,boolean a1){logmsg("m_dowear;" );callback();}
char * makeplural(const char * a0){logmsg("makeplural;" );return named("makeplural");}
void mhidden_description(struct monst * a0,unsigned int a1,char * a2){logmsg("mhidden_description;" );callback();}
void mon_adjust_speed(struct monst * a0,int a1,struct obj * a2){logmsg("mon_adjust_speed;" );callback();}
void mon_learns_traps(struct monst * a0,int a1){logmsg("mon_learns_traps;" );callback();}
char * mon_nam(struct monst * a0){logmsg("mon_nam;" );return named("mon_nam");}
void mon_set_minvis(struct monst * a0,boolean a1){logmsg("mon_set_minvis;" );callback();}
void mon_track_clear(struct monst * a0){logmsg("mon_track_clear;" );callback();}
void mondied(struct monst * a0){logmsg("mondied;" );callback();}
void mongone(struct monst * a0){logmsg("mongone;" );callback();}
void new_light_source(coordxy a0,coordxy a1,int a2,int a3,union any * a4){logmsg("new_light_source;" );callback();}
int newcham(struct monst * a0,struct permonst * a1,unsigned int a2){logmsg("newcham;" );return opts[19];}
void newegd(struct monst * a0){logmsg("newegd;" );callback();}
void neweshk(struct monst * a0){logmsg("neweshk;" );callback();}
void newsym(coordxy a0,coordxy a1){logmsg("newsym;" );callback();}
struct obj * oname(struct obj * a0,const char * a1,unsigned int a2){logmsg("oname;" );return 0;}
void place_worm_tail_randomly(struct monst * a0,coordxy a1,coordxy a2){logmsg("place_worm_tail_randomly;" );callback();}
void put_saddle_on_mon(struct obj * a0,struct monst * a1){logmsg("put_saddle_on_mon;" );callback();}
short quest_info(int a0){logmsg("quest_info;" );return 0;}
int rnd_class(int a0,int a1){logmsg("rnd_class;" );return a0;}
int rnd_defensive_item(struct monst * a0){logmsg("rnd_defensive_item;" );return 0;}
int rnd_misc_item(struct monst * a0){logmsg("rnd_misc_item;" );return 0;}
int rnd_offensive_item(struct monst * a0){logmsg("rnd_offensive_item;" );return 0;}
const char * rndghostname(void){logmsg("rndghostname;" );return named("rndghostname");}
int rndmonnum(void){logmsg("rndmonnum;" );return PM_HUMAN;}
int sensemon(struct monst * a0){logmsg("sensemon;" );return opts[17];}
void set_apparxy(struct monst * a0){logmsg("set_apparxy;" );callback();}
void set_corpsenm(struct obj * a0,int a1){logmsg("set_corpsenm;" );callback();}
void set_msg_xy(coordxy a0,coordxy a1){logmsg("set_msg_xy;" );callback();}
int sgn(int a0){logmsg("sgn;" );return (a0>0)-(a0<0);}
char * shkname(struct monst * a0){logmsg("shkname;" );return named("shkname");}
long stop_timer(short a0,union any * a1){logmsg("stop_timer;" );return 0;}
struct trap * t_at(coordxy a0,coordxy a1){logmsg("t_at;" );return 0;}
void update_inventory(void){logmsg("update_inventory;" );callback();}
char * upstart(char * a0){logmsg("upstart;" );return named("upstart");}
char * vtense(const char * a0,const char * a1){logmsg("vtense;" );return named("vtense");}
int weight(struct obj * a0){logmsg("weight;" );return a0->otyp+(unsigned)a0->quan;}
struct obj * which_armor(struct monst * a0,long a1){logmsg("which_armor;" );return 0;}
static void window_raw(const char*s){logmsg("raw:%s;",s);callback();}
static void callback(void){if(opts[95])iflags.last_msg++;if(opts[93]){logmsg("forced-unwind;");longjmp(fixture_jump,1);}if(opts[92]&&!callbackdepth){objpool[0].spe++;monpool[0].mhp+=2;logmsg("alias:%d:%d;",objpool[0].spe,monpool[0].mhp);}if(opts[90]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)longjmp(fixture_jump,1);logmsg("growth;");}if(opts[91]&&!callbackdepth){callbackdepth++;coord nested;logmsg("reentry:%d;",golemhp(PM_IRON_GOLEM));if(makemon_rnd_goodpos(0,GP_CHECKSCARY,&nested))logmsg("nestedcoord:%d:%d;",nested.x,nested.y);callbackdepth--;}}
int probe_layout_count(void){return SIZE(makemon_layout);}const char*probe_layout_name(int i){return makemon_layout[i].name;}long long probe_layout_value(int i){return makemon_layout[i].value;}size_t probe_stack(void){return emscripten_stack_get_current();}const char*probe_trace(void){return tracebuf;}void probe_clear(void){tracebuf[0]=0;}void probe_option(int i,int n){opts[i]=n;}void probe_seed(unsigned n){rngstate=n;}
void probe_reset(void){monst_globals_init();objects_globals_init();if(growth){free(growth);growth=0;}memset(opts,0,sizeof opts);memset(monpool,0,sizeof monpool);memset(objpool,0,sizeof objpool);memset(mextrapool,0,sizeof mextrapool);memset(eminpool,0,sizeof eminpool);memset(edogpool,0,sizeof edogpool);memset(epripool,0,sizeof epripool);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&svl,0,sizeof svl);memset(&svm,0,sizeof svm);memset(&svc,0,sizeof svc);memset(&svd,0,sizeof svd);memset(&gi,0,sizeof gi);memset(&gu,0,sizeof gu);memset(&gm,0,sizeof gm);memset(&gs,0,sizeof gs);memset(&special,0,sizeof special);
for(int i=0;i<NUMMONS;i++){snprintf(namesbuf[i],24,"NAME%d",i);monsdump[i].nm=namesbuf[i];}u.ux=10;u.uy=10;u.ulevel=5;u.umonnum=u.umonster=PM_HUMAN;u.uz.dlevel=3;u.ualign.type=A_NEUTRAL;gu.urole.mnum=PM_WIZARD;gu.urace.mnum=PM_HUMAN;svm.moves=100;svl.level.flags.rndmongen=1;svd.dungeon_topology.d_astral_level.dnum=8;svd.dungeon_topology.d_astral_level.dlevel=1;svd.dungeon_topology.d_quest_dnum=9;svd.dungeon_topology.d_mines_dnum=2;svd.dungeon_topology.d_sokoban_dnum=3;svd.dungeon_topology.d_tower_dnum=4;
static seenV rows[ROWNO][COLNO];static seenV*rowptr[ROWNO];for(int y=0;y<ROWNO;y++){rowptr[y]=rows[y];memset(rows[y],0,COLNO);}gv.viz_array=rowptr;windowprocs.win_raw_print=window_raw;
for(int i=0;i<128;i++){monpool[i].data=&mons[PM_HUMAN];monpool[i].mnum=PM_HUMAN;monpool[i].mhp=20;monpool[i].mhpmax=30;monpool[i].m_lev=5;monpool[i].m_id=i+1;monpool[i].mx=10+i;monpool[i].my=10;monpool[i].cham=NON_PM;monpool[i].mextra=&mextrapool[i];mextrapool[i].mcorpsenm=NON_PM;}
for(int i=0;i<256;i++){objpool[i].otyp=DAGGER;objpool[i].oclass=WEAPON_CLASS;objpool[i].quan=1;}monnext=objnext=alloccount=freecount=callbackdepth=0;serial=50;rngstate=1;tracebuf[0]=snapshotbuf[0]=origin[0]=0;}
void probe_monster_setup(int i,int pm,int lev,int hp,int flags_){struct monst*m=&monpool[i];m->data=&mons[pm];m->mnum=pm;m->m_lev=lev;m->mhp=hp;m->mhpmax=hp;m->mpeaceful=flags_&1;m->female=(flags_>>1)&1;m->mtame=(flags_&4)?10:0;m->isminion=(flags_>>3)&1;m->ispriest=(flags_>>4)&1;m->cham=(flags_&32)?pm:NON_PM;m->mextra=&mextrapool[i];m->mextra->emin=&eminpool[i];m->mextra->edog=&edogpool[i];m->mextra->epri=&epripool[i];}
void probe_global(int which,long n){switch(which){case 0:u.uz.dnum=n;break;case 1:u.uz.dlevel=n;break;case 2:u.ulevel=n;break;case 3:u.ualign.type=n;break;case 4:u.ualign.record=n;break;case 5:u.ualign.abuse=n;break;case 6:u.uhave.amulet=n;break;case 7:gi.in_mklev=n;break;case 8:flags.debug=n;break;case 9:svm.moves=n;break;case 10:special.flags.align=n;break;case 11:svd.dungeons[u.uz.dnum].flags.align=n;break;case 12:svl.level.flags.temperature=n;break;case 13:svl.level.flags.rndmongen=n;break;case 14:iflags.debug_mongen=n;break;case 15:svc.context.mon_moving=n;break;case 16:u.uluck=n;break;case 17:u.uprops[PROT_FROM_SHAPE_CHANGERS].intrinsic=n;break;case 18:gu.urole.mnum=n;break;case 19:gu.urace.mnum=n;break;case 20:svl.level.flags.is_maze_lev=n;break;case 21:u.uprops[BLINDED].intrinsic=n;break;}}
void probe_vital(int i,int born,int died,int flags_){svm.mvitals[i].born=born;svm.mvitals[i].died=died;svm.mvitals[i].mvflags=flags_;}
void probe_square(int x,int y,int typ,int room){svl.level.locations[x][y].typ=typ;svl.level.locations[x][y].roomno=room;}
void probe_planes(void){svd.dungeon_topology.d_air_level=(d_level){8,1};svd.dungeon_topology.d_fire_level=(d_level){8,2};svd.dungeon_topology.d_earth_level=(d_level){8,3};svd.dungeon_topology.d_water_level=(d_level){8,4};svd.dungeon_topology.d_astral_level=(d_level){8,5};}
void probe_room(int room,int type){svr.rooms[room].rtype=type;}
void probe_map_object(int x,int y,int type){objpool[254].otyp=type;svl.level.objects[x][y]=&objpool[254];}
long probe_action(int op,int a,int b,int c,long n){long result=0;if(setjmp(fixture_jump))return -999;switch(op){
case 0:result=is_home_elemental(&mons[a]);break;case 1:result=wrong_elem_type(&mons[a]);break;case 2:m_initgrp(&monpool[0],a,b,c,n);break;case 3:m_initthrow(&monpool[0],a,b);break;case 4:m_initweap(&monpool[0]);break;case 5:mkmonmoney(&monpool[0],n);break;case 6:m_initinv(&monpool[0]);break;case 7:result=id(clone_mon(&monpool[0],a,b));break;case 8:result=propagate(a,b,c);break;case 9:result=monhp_per_lvl(&monpool[0]);break;case 10:newmonhp(&monpool[0],a);break;case 11:init_mextra(&mextrapool[0]);break;case 12:{struct mextra*p=newmextra();result=p->mcorpsenm;free(p);}break;case 13:{coord cc;result=makemon_rnd_goodpos(a?&monpool[0]:0,b,&cc);if(result)logmsg("coord:%d:%d;",cc.x,cc.y);}break;case 14:result=id(makemon(a<0?0:&mons[a],b,c,n));break;case 15:result=id(unmakemon(&monpool[0],a));break;case 16:result=mbirth_limit(a);break;case 17:result=create_critters(a,b<0?0:&mons[b],c);break;case 18:result=uncommon(a);break;case 19:result=align_shift(&mons[a]);break;case 20:result=temperature_shift(&mons[a]);break;case 21:result=id(rndmonst());break;case 22:result=id(rndmonst_adj(a,b));break;case 23:result=mk_gen_ok(a,b,c);break;case 24:{int x=a,y=b;result=cmp_init_mongen_order(&x,&y);}break;case 25:init_mongen_order();break;case 26:dump_mongen();break;case 27:result=id(mkclass(a,b));break;case 28:result=id(mkclass_aligned(a,b,c));break;case 29:result=mkclass_poly(a);break;case 30:result=adj_lev(&mons[a]);break;case 31:result=id(grow_up(&monpool[0],a?&monpool[1]:0));break;case 32:result=id(mongets(&monpool[0],a));break;case 33:result=golemhp(a);break;case 34:result=peace_minded(&mons[a]);break;case 35:set_malign(&monpool[0]);break;case 36:newmcorpsenm(&monpool[0]);break;case 37:freemcorpsenm(&monpool[0]);break;case 38:set_mimic_sym(&monpool[0]);break;case 39:{int seen=c;objpool[0].otyp=a;objpool[0].spe=b;result=bagotricks(&objpool[0],n,&seen);logmsg("seen:%d;",seen);}break;case 40:summon_furies(a);break;}
return result;}
const char*probe_snapshot(void){char*p=snapshotbuf;p+=sprintf(p,"rng:%u;alloc:%d;id:%u;hero:%d,%d,%d,%d;",rngstate,alloccount,serial,u.ulevel,u.ualign.type,u.ualign.record,u.ualign.abuse);p+=sprintf(p,"msg:%d;",iflags.last_msg);for(int i=0;i<128;i++){struct monst*m=&monpool[i];p+=sprintf(p,"m%d:%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d,%d,%ld,%d;",i,m->data?m->data->pmidx:-1,m->mhp,m->mhpmax,m->m_lev,m->mpeaceful,m->malign,m->mtame,m->female,m->mextra?m->mextra->mcorpsenm:NON_PM,m->m_ap_type,m->mappearance,m->cham,m->mstrategy,m->mcloned);}for(struct monst*m=fmon;m;m=m->nmon)p+=sprintf(p,"chain:%d,%d,%d,%d,%d,%u;",m->data->pmidx,m->mhp,m->mhpmax,m->mx,m->my,m->m_id);for(int i=0;i<objnext;i++){struct obj*o=&objpool[i];p+=sprintf(p,"o:%d,%ld,%d,%d,%d,%d,%d,%d,%ld;",o->otyp,o->quan,o->spe,o->blessed,o->cursed,o->oeroded,o->oeroded2,o->opoisoned,o->age);}for(int i=0;i<NUMMONS;i++)p+=sprintf(p,"v:%u,%u,%u;",svm.mvitals[i].born,svm.mvitals[i].died,svm.mvitals[i].mvflags);return snapshotbuf;}
