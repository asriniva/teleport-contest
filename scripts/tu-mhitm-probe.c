#include "hack.h"
#include "artifact.h"
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(u) u;__typeof__(gf) gf;__typeof__(svm) svm;__typeof__(gn) gn;__typeof__(gv) gv;__typeof__(gb) gb;__typeof__(gs) gs;__typeof__(gl) gl;__typeof__(iflags) iflags;__typeof__(flags) flags;__typeof__(gy) gy;__typeof__(gm) gm;__typeof__(gz) gz;__typeof__(svl) svl;
const struct const_globals cg={0};
const struct c_common_strings c_common_strings={.c_something="something",.c_nothing_happens="Nothing happens."};
const struct Gender genders[]={{.his="his"},{.his="her"},{.his="its"}};
static struct permonst forms[3];
static struct monst victims[3];static struct obj items[3];static struct attack probe_attacks[3];
static int opts[64],rng_seed=1,rng_count;static void *growth;static char trace[262144],snapshot[16384],names[3][BUFSZ];
static struct mhitm_data *active_mhm;
static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long mid(const struct monst *m){return !m?-1:m==&gy.youmonst?-2:m>=victims&&m<victims+3?m-victims:-3;}
static long oid(const struct obj *o){return !o?-1:o>=items&&o<items+3?o-items:-3;}
static void callback(int stage){if(opts[50]==stage){opts[50]=0;append("nested:%ld;",attk_protection(AT_KICK));}if(opts[51]==stage&&!growth){opts[51]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}if(opts[52]==stage){opts[52]=0;victims[1].mcan=1;append("change:mcan;");}}
void panic(const char *fmt,...){(void)fmt;abort();}
void impossible(const char *fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void pline(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);callback(1);}
void pline_mon(struct monst *m,const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("mon:%ld:%s;",mid(m),b);callback(2);}
#define MSG(name) void name(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#name ":%s;",b);callback(3);}
MSG(You) MSG(Your) MSG(You_feel) MSG(You_hear)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file,int line,const char *fn){const char *p=strrchr(file,'/');append("caller:%s:%d:%s;",p?p+1:file,line,fn);}
int (rn2)(int n){rng_seed=(int)((unsigned)rng_seed*1664525U+1013904223U);rng_count++;append("rn2:%d;",n);return n?(unsigned)rng_seed%(unsigned)n:0;}
int (rnd)(int n){rng_seed=(int)((unsigned)rng_seed*1664525U+1013904223U);rng_count++;append("rnd:%d;",n);return n?1+(unsigned)rng_seed%(unsigned)n:1;}
int (d)(int n,int sides){int i,v=0;append("dice:%d:%d;",n,sides);for(i=0;i<n;i++)v+=(rnd)(sides);return v;}
boolean snuff_lit(struct obj * a0){return (boolean)opts[27];}

boolean is_art(struct obj * a0,int a1){return (boolean)opts[34];}

int sensemon(struct monst * a0){return (int)opts[2];}

int mon_visible(struct monst * a0){return (int)opts[1];}

int canseemon(struct monst * a0){return (int)opts[1];}

void map_invisible(coordxy a0,coordxy a1){append("map_invisible:%ld:%ld;",(long)a0,(long)a1);callback(4);}

void newsym(coordxy a0,coordxy a1){append("newsym:%ld:%ld;",(long)a0,(long)a1);callback(4);}

void shieldeff(coordxy a0,coordxy a1){append("shieldeff:%ld:%ld;",(long)a0,(long)a1);callback(4);}

void flush_screen(int a0){append("flush_screen:%ld;",(long)a0);callback(4);}

char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return names[a0==&gy.youmonst?2:(a0==&victims[1]?1:0)];}

char * mon_nam(struct monst * a0){return names[a0==&gy.youmonst?2:(a0==&victims[1]?1:0)];}

char * some_mon_nam(struct monst * a0){return names[a0==&gy.youmonst?2:(a0==&victims[1]?1:0)];}

char * Monnam(struct monst * a0){return names[a0==&gy.youmonst?2:(a0==&victims[1]?1:0)];}

char * noname_monnam(struct monst * a0,int a1){return names[a0==&gy.youmonst?2:(a0==&victims[1]?1:0)];}

char * Adjmonnam(struct monst * a0,const char * a1){return names[a0==&gy.youmonst?2:(a0==&victims[1]?1:0)];}

char * a_monnam(struct monst * a0){return names[a0==&gy.youmonst?2:(a0==&victims[1]?1:0)];}

char * mon_nam_too(struct monst * a0,struct monst * a1){return names[a0==&victims[1]?1:0];}

const char * hliquid(const char * a0){return (char*)a0;}

boolean is_fainted(void){return (boolean)opts[30];}

const char * mswings_verb(struct obj * a0,boolean a1){return "swings";}

boolean mtrapped_in_pit(struct monst * a0){return (boolean)opts[28];}

int could_seduce(struct monst * a0,struct monst * a1,struct attack * a2){return (int)opts[7];}

boolean zombie_maker(struct monst * a0){return (boolean)opts[32];}

int zombie_form(struct permonst * a0){return (int)opts[33];}

int pm_to_cham(int a0){return opts[41]?PM_VAMPIRE:NON_PM;}

int minliquid(struct monst * a0){return (int)opts[21];}

void mon_givit(struct monst * a0,struct permonst * a1){append("mon_givit:%ld:%d;",mid(a0),!!a1);callback(4);}

boolean monnear(struct monst * a0,coordxy a1,coordxy a2){return distmin(a0->mx,a0->my,a1,a2)<2;}

void xkilled(struct monst * a0,int a1){append("xkilled:%ld:%ld;",mid(a0),(long)a1);callback(4);}

void golemeffects(struct monst * a0,int a1,int a2){append("golemeffects:%ld:%ld:%ld;",mid(a0),(long)a1,(long)a2);callback(4);}

void shieldeff_mon(struct monst * a0){append("shieldeff_mon:%ld;",mid(a0));callback(4);}

boolean attacktype(struct permonst * a0,int a1){return (boolean)opts[35];}

boolean poly_when_stoned(struct permonst * a0){return (boolean)opts[24];}

boolean defended(struct monst * a0,int a1){return (boolean)opts[4];}

boolean Resists_Elem(struct monst * a0,int a1){return (opts[3]&(1<<a1))!=0;}

boolean resists_magm(struct monst * a0){return (boolean)opts[15];}

boolean resists_blnd(struct monst * a0){return (boolean)opts[16];}

boolean mon_hates_silver(struct monst * a0){return (boolean)opts[23];}

boolean sticks(struct permonst * a0){return (boolean)opts[26];}

struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){int i;for(i=0;i<NATTK;i++)if(a0->mattk[i].adtyp==a1&&a0->mattk[i].aatyp==a2)return &((struct permonst*)a0)->mattk[i];return NULL;}

boolean dmgtype(struct permonst * a0,int a1){int i;for(i=0;i<NATTK;i++)if(a0->mattk[i].adtyp==a1)return TRUE;return FALSE;}

int pronoun_gender(struct monst * a0,unsigned a1){return 2;}

const char * stagger(const struct permonst * a0,const char * a1){return (char*)a1;}

boolean resist_conflict(struct monst * a0){return (boolean)opts[17];}

boolean itsstuck(struct monst * a0){return (boolean)opts[18];}

boolean closed_door(coordxy a0,coordxy a1){return (boolean)opts[25];}

int thrwmm(struct monst * a0,struct monst * a1){return (int)opts[37];}

int spitmm(struct monst * a0,struct attack * a1,struct monst * a2){return (int)opts[39];}

int breamm(struct monst * a0,struct attack * a1,struct monst * a2){return (int)opts[38];}

char * xname(struct obj * a0){return "dagger";}

char * simpleonames(struct obj * a0){return "dagger";}

char * makeplural(const char * a0){return (char*)a0;}

void polyself(int a0){append("polyself:%ld;",(long)a0);callback(4);}

void update_monster_region(struct monst * a0){append("update_monster_region:%ld;",mid(a0));callback(4);}

boolean goodpos(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){return (boolean)opts[36];}

void tele(void){append("tele;");callback(4);}

boolean rloc(struct monst * a0,unsigned a1){append("rloc:%ld:%ld;",mid(a0),(long)a1);callback(4);return 0;}

boolean tele_restrict(struct monst * a0){return (boolean)opts[19];}

int mintrap(struct monst * a0,unsigned a1){return (int)opts[22];}

void acid_damage(struct obj * a0){append("acid_damage:%ld;",oid(a0));callback(4);}

struct trap * t_at(coordxy a0,coordxy a1){return (struct trap *)((uintptr_t)opts[31]);}

boolean unconscious(void){return (boolean)opts[29];}

void erode_armor(struct monst * a0,int a1){append("erode_armor:%ld:%ld;",mid(a0),(long)a1);callback(4);}

boolean shade_miss(struct monst * a0,struct monst * a1,struct obj * a2,boolean a3,boolean a4){return (boolean)opts[6];}

int hitval(struct obj * a0,struct monst * a1){append("hitval:%ld:%ld;",oid(a0),mid(a1));callback(4);return 0;}

void possibly_unwield(struct monst * a0,boolean a1){append("possibly_unwield:%ld:%ld;",mid(a0),(long)a1);callback(4);}

int mon_wield_item(struct monst * a0){return (int)opts[20];}

void you_were(void){append("you_were;");callback(4);}

void you_unwere(boolean a0){append("you_unwere:%ld;",(long)a0);callback(4);}

void remove_worm(struct monst * a0){append("remove_worm:%ld;",mid(a0));callback(4);}

void place_worm_tail_randomly(struct monst * a0,coordxy a1,coordxy a2){append("place_worm_tail_randomly:%ld:%ld:%ld;",mid(a0),(long)a1,(long)a2);callback(4);}

int find_mac(struct monst * a0){return opts[40];}

struct obj * which_armor(struct monst * a0,long a1){append("which_armor:%ld:%ld;",mid(a0),(long)a1);callback(4);return 0;}

int resist(struct monst * a0,char a1,int a2,int a3){return (int)opts[5];}
struct attack *getmattk(struct monst *a,struct monst *b,int i,int *res,struct attack *alt){int n;append("get:%ld:%ld:%d",mid(a),mid(b),i);for(n=0;n<=i;n++)append(":%d",res[n]);append(";");callback(5);*alt=a->data->mattk[i];if(opts[42]&&i==0)*alt=probe_attacks[0];return alt;}
void mhitm_adtyping(struct monst *a,struct attack *atk,struct monst *b,struct mhitm_data *mhm){append("ad:%ld:%ld:%d:%d:%d:%d:%d:%d:%d:%d;",mid(a),mid(b),atk->aatyp,atk->adtyp,mhm->damage,mhm->hitflags,mhm->done,mhm->permdmg,mhm->specialdmg,mhm->dieroll);active_mhm=mhm;callback(6);if(opts[11]){mhm->damage=opts[12];mhm->hitflags=opts[13];mhm->done=opts[14];}if(opts[43]){b->mstate=MON_OFFMAP;}}
void mhitm_ad_blnd(struct monst *a,struct attack *atk,struct monst *b,struct mhitm_data *mhm){append("blnd:%ld:%ld:%d:%d;",mid(a),mid(b),atk->adtyp,!!mhm);b->mcansee=0;callback(7);}
boolean mhitm_knockback(struct monst *a,struct monst *b,struct attack *atk,int *flags_,boolean weapon){append("knock:%ld:%ld:%d:%d:%d;",mid(a),mid(b),atk->aatyp,weapon,active_mhm&&flags_==&active_mhm->hitflags);callback(8);if(opts[44])*flags_=opts[45];return opts[44];}
void place_monster(struct monst *m,coordxy x,coordxy y){append("place:%ld:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;svl.level.monsters[x][y]=m;callback(9);}
void monkilled(struct monst *m,const char *text,int ad){append("killed:%ld:%s:%d:%d:%d;",mid(m),text,ad,gm.mkcorpstat_norevive,gz.zombify);m->mhp=opts[10]?7:0;callback(10);}
void mondead(struct monst *m){append("dead:%ld;",mid(m));m->mhp=opts[10]?7:0;m->mleashed=0;callback(10);}
void monstone(struct monst *m){append("stone:%ld;",mid(m));m->mhp=opts[10]?7:0;callback(10);}
struct permonst *grow_up(struct monst *a,struct monst *b){append("grow_up:%ld:%ld;",mid(a),mid(b));callback(11);return opts[46]?NULL:a->data;}
struct monst *clone_mon(struct monst *m,coordxy x,coordxy y){append("clone:%ld:%d:%d;",mid(m),x,y);callback(11);return opts[47]?&victims[2]:NULL;}
struct monst *split_mon(struct monst *a,struct monst *b){append("split:%ld:%ld;",mid(a),mid(b));callback(11);return &victims[2];}
int newcham(struct monst *m,struct permonst *pm,unsigned f){append("cham:%ld:%d:%u;",mid(m),pm?monsndx(pm):NON_PM,f);callback(12);if(opts[9]){m->data=pm?pm:&mons[PM_HUMAN];return 1;}return 0;}
int healmon(struct monst *m,int hp,int max){append("heal:%ld:%d:%d;",mid(m),hp,max);m->mhp+=hp;m->mhpmax+=max;return hp;}
void finish_meating(struct monst *m){append("finish:%ld;",mid(m));m->meating=0;}
void set_ustuck(struct monst *m){append("ustuck:%ld;",mid(m));u.ustuck=m;}
void unstuck(struct monst *m){append("unstuck:%ld;",mid(m));u.ustuck=NULL;}
void mon_explodes(struct monst *m,struct attack *a){append("explode:%ld:%d;",mid(m),a->adtyp);m->mhp=0;if(opts[48])victims[1].mhp=0;callback(10);}
void mon_to_stone(struct monst *m){append("poly_stone:%ld;",mid(m));m->data=&mons[PM_STONE_GOLEM];}
boolean mon_reflects(struct monst *m,const char *fmt){append("reflect:%ld:%d;",mid(m),!!fmt);callback(13);return opts[8];}
int erode_obj(struct obj *obj,const char *str,int type,int flags_){append("erode:%ld:%d:%d:%d;",oid(obj),!!str,type,flags_);callback(14);return 1;}
boolean drain_item(struct obj *obj,boolean byyou){append("drain:%ld:%d;",oid(obj),byyou);callback(14);return 1;}
void seemimic(struct monst *m){append("mimic:%ld;",mid(m));m->m_ap_type=M_AP_NOTHING;}
#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/mhitm.c"
#else
extern void teleport_mhitm_test_noises(struct monst*,struct attack*);
extern void teleport_mhitm_test_pre_mm_attack(struct monst*,struct monst*);
extern void teleport_mhitm_test_missmm(struct monst*,struct monst*,struct attack*);
extern int teleport_mhitm_test_hitmm(struct monst*,struct monst*,struct attack*,struct obj*,int);
extern int teleport_mhitm_test_gazemm(struct monst*,struct monst*,struct attack*);
extern int teleport_mhitm_test_gulpmm(struct monst*,struct monst*,struct attack*);
extern int teleport_mhitm_test_explmm(struct monst*,struct monst*,struct attack*);
extern int teleport_mhitm_test_mdamagem(struct monst*,struct monst*,struct attack*,struct obj*,int);
extern void teleport_mhitm_test_mswingsm(struct monst*,struct monst*,struct obj*);
extern int teleport_mhitm_test_passivemm(struct monst*,struct monst*,boolean,int,struct obj*);
#define noises teleport_mhitm_test_noises
#define pre_mm_attack teleport_mhitm_test_pre_mm_attack
#define missmm teleport_mhitm_test_missmm
#define hitmm teleport_mhitm_test_hitmm
#define gazemm teleport_mhitm_test_gazemm
#define gulpmm teleport_mhitm_test_gulpmm
#define explmm teleport_mhitm_test_explmm
#define mdamagem teleport_mhitm_test_mdamagem
#define mswingsm teleport_mhitm_test_mswingsm
#define passivemm teleport_mhitm_test_passivemm
#endif
#include "tu-mhitm-layout.h"
unsigned probe_layout_count(void){return SIZE(mhitm_layout);}
const char *probe_layout_name(unsigned i){return mhitm_layout[i].name;}
size_t probe_layout_value(unsigned i){return mhitm_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_trace(void){return trace;}
void probe_clear(void){*trace=0;}
void probe_option(int i,int value){opts[i]=value;}
void probe_seed(int seed){rng_seed=seed;}
static struct monst *mon(int index){return index<0?NULL:index==3?&gy.youmonst:&victims[index];}
void probe_reset(void){int i,x,y;objects_globals_init();monst_globals_init();if(growth){free(growth);growth=NULL;}memset(&u,0,sizeof u);memset(&gf,0,sizeof gf);memset(&gn,0,sizeof gn);memset(&gv,0,sizeof gv);memset(&gb,0,sizeof gb);memset(&gs,0,sizeof gs);memset(&gl,0,sizeof gl);memset(&gm,0,sizeof gm);memset(&gz,0,sizeof gz);memset(&svl,0,sizeof svl);memset(opts,0,sizeof opts);memset(victims,0,sizeof victims);memset(items,0,sizeof items);memset(probe_attacks,0,sizeof probe_attacks);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);for(i=0;i<3;i++){victims[i].data=&mons[PM_HUMAN];victims[i].mx=10+i;victims[i].my=10;victims[i].mhp=victims[i].mhpmax=50;victims[i].m_lev=10;victims[i].mcanmove=victims[i].mcansee=1;victims[i].movement=20;victims[i].cham=NON_PM;victims[i].m_id=i+1;victims[i].mstate=MON_FLOOR;items[i].otyp=DAGGER;items[i].oclass=WEAPON_CLASS;items[i].quan=1;sprintf(names[i],"Monster%d",i);}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)svl.level.locations[x][y].typ=ROOM;for(y=0;y<ROWNO;y++){visrows[y]=visibility[y];for(x=0;x<COLNO;x++)visibility[y][x]=IN_SIGHT;}for(i=0;i<3;i++)svl.level.monsters[victims[i].mx][victims[i].my]=&victims[i];gy.youmonst=victims[0];gy.youmonst.data=&mons[PM_HUMAN];u.ux=10;u.uy=11;u.ulycn=NON_PM;u.umonnum=PM_HUMAN;gv.viz_array=visrows;gv.vis=1;flags.verbose=1;svm.moves=20;svl.level.monlist=&victims[0];victims[0].nmon=&victims[1];opts[1]=1;opts[36]=1;opts[40]=10;gb.bhitpos.x=victims[1].mx;gb.bhitpos.y=victims[1].my;rng_seed=1;rng_count=0;active_mhm=NULL;*trace=0;}
void probe_mon(int index,int pm,int x,int y,int hp,long mask){struct monst *m=mon(index);if(svl.level.monsters[m->mx][m->my]==m)svl.level.monsters[m->mx][m->my]=NULL;m->data=&mons[pm];m->mx=x;m->my=y;m->mhp=hp;m->mhpmax=hp;m->misc_worn_check=mask;svl.level.monsters[x][y]=m;if(index==1){gb.bhitpos.x=x;gb.bhitpos.y=y;}}
void probe_field(int index,int key,long value){struct monst *m=mon(index);switch(key){case 0:m->mcan=value;break;case 1:m->mconf=value;break;case 2:m->mundetected=value;break;case 3:m->msleeping=value;break;case 4:m->mcanmove=value;break;case 5:m->wormno=value;break;case 6:m->mcansee=value;break;case 7:m->minvis=value;break;case 8:m->mleashed=value;break;case 9:m->mstun=value;break;case 10:m->mfrozen=value;break;case 11:m->mtrapped=value;break;case 12:m->cham=value;break;case 13:m->mstrategy=value;break;case 14:m->mspec_used=value;break;case 15:m->m_ap_type=value;break;case 16:m->movement=value;break;case 17:m->mtame=value;break;case 18:m->mhpmax=value;break;case 19:m->m_lev=value;break;case 20:m->meating=value;break;case 21:m->mstate=value;break;case 22:m->mhp=value;break;case 23:m->weapon_check=value;break;}}
void probe_item(int index,int typ,int artifact,int wield,long quantity){items[index].otyp=typ;items[index].oclass=objects[typ].oc_class;items[index].oartifact=artifact;items[index].quan=quantity;if(wield>=0)mon(wield)->mw=&items[index];}
void probe_attack(int slot,int type,int damage,int n,int sides){probe_attacks[slot]=(struct attack){type,damage,n,sides};}
void probe_hero(int swallow,int stuck,int steed,long multi,int deaf,int blind){u.uswallow=swallow;u.ustuck=mon(stuck);u.usteed=mon(steed);gm.multi=multi;u.uroleplay.deaf=deaf;u.uprops[BLINDED].intrinsic=blind;}
void probe_prop(int property,long intr,long extr,long blocked){u.uprops[property].intrinsic=intr;u.uprops[property].extrinsic=extr;u.uprops[property].blocked=blocked;}
void probe_global(int key,long value){switch(key){case 0:gv.vis=value;break;case 1:flags.verbose=value;break;case 2:svm.moves=value;break;case 3:gn.noisetime=value;break;case 4:gf.far_noise=value;break;case 5:gn.notonhead=value;break;case 6:gs.skipdrin=value;break;case 7:iflags.last_msg=value;break;case 8:gl.last_hider=value;break;case 9:svl.level.flags.arboreal=value;break;}}
void probe_terrain(int x,int y,int typ){svl.level.locations[x][y].typ=typ;}
long probe_action(int op,int a,int b,int c,int e){struct monst *ma=mon(a),*md=mon(b);struct attack *atk=&probe_attacks[0];struct obj *wep=c<0?NULL:&items[c];switch(op){case 0:noises(ma,atk);break;case 1:pre_mm_attack(ma,md);break;case 2:missmm(ma,md,atk);break;case 3:return fightm(ma);case 4:return mdisplacem(ma,md,e);case 5:return mattackm(ma,md);case 6:return failed_grab(ma,md,atk);case 7:return hitmm(ma,md,atk,wep,e);case 8:return gazemm(ma,md,atk);case 9:return engulf_target(ma,md);case 10:return gulpmm(ma,md,atk);case 11:return explmm(ma,md,atk);case 12:return mdamagem(ma,md,atk,wep,e);case 13:return mon_poly(ma,md,e);case 14:paralyze_monst(ma,e);break;case 15:return sleep_monst(ma,c,e);case 16:slept_monst(ma);break;case 17:rustm(ma,wep);break;case 18:mswingsm(ma,md,wep);break;case 19:return passivemm(ma,md,c,e,&items[0]);case 20:xdrainenergym(ma,e);break;case 21:return attk_protection(a);}return 0;}
const char *probe_snapshot(void){int i;char *p=snapshot;for(i=0;i<4;i++){struct monst *m=mon(i);p+=sprintf(p,"m%d:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lu,%ld,%ld,%d,%d,%ld;",i,monsndx(m->data),m->mx,m->my,m->mhp,m->mhpmax,m->mcan,m->mconf,m->mundetected,m->msleeping,m->mcanmove,m->wormno,m->mcansee,m->minvis,m->mleashed,m->mstun,m->mfrozen,m->mtrapped,m->mstrategy,m->mlstmv,m->mstate,m->mspec_used,m->movement,m->misc_worn_check);}p+=sprintf(p,"g:%d,%ld,%ld,%d,%d,%d,%u,%d,%d,%d,%d,%ld,%ld,%ld,%d,%d;",gf.far_noise,svm.moves,gn.noisetime,gn.notonhead,gv.vis,gs.skipdrin,gl.last_hider,iflags.last_msg,gm.mkcorpstat_norevive,gz.zombify,u.uswallow,mid(u.ustuck),mid(u.usteed),mid(gm.mswallower),gb.bhitpos.x,gb.bhitpos.y);p+=sprintf(p,"rng:%d;",rng_count);for(i=0;i<3;i++)p+=sprintf(p,"name%d:%s;",i,names[i]);for(i=0;i<3;i++)p+=sprintf(p,"grid%d:%ld;",i,mid(svl.level.monsters[10+i][10]));return snapshot;}

void probe_form(int index,int pm,int aatyp,int adtyp,int n,int sides){int i;memcpy(&forms[index],&mons[pm],sizeof forms[index]);for(i=0;i<NATTK;i++)forms[index].mattk[i]=(struct attack){AT_NONE,AD_PHYS,0,0};forms[index].mattk[0]=(struct attack){aatyp,adtyp,n,sides};victims[index].data=&forms[index];}

void probe_form_attack(int index,int slot,int aatyp,int adtyp,int n,int sides){forms[index].mattk[slot]=(struct attack){aatyp,adtyp,n,sides};}

unsigned long probe_catalogue(int index,int field){switch(field){case 0:return mons[index].mflags1;case 1:return mons[index].mflags2;case 2:return mons[index].msize;case 3:return mons[index].mattk[0].aatyp;case 4:return mons[index].mlet;default:return objects[index].oc_material;}}
