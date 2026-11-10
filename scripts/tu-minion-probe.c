#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
struct you u;
__typeof__(gy) gy;
__typeof__(gi) gi;
__typeof__(gm) gm;
__typeof__(svm) svm;
__typeof__(svd) svd;
__typeof__(flags) flags;
__typeof__(disp) disp;
__typeof__(svl) svl;
struct obj *uwep;
static struct monst pool[32];
static struct permonst copied_monster;
static struct obj equipment[4];
static int options[20],random_values[256],random_length,random_index,created_count,make_calls;
static unsigned random_state;
static long cash;
static char input[BUFSZ],probe_trace_storage[262144],caller[128];
void panic(const char *format,...) {abort();}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(probe_trace_storage+strlen(probe_trace_storage),sizeof probe_trace_storage-strlen(probe_trace_storage),format,ap);va_end(ap);}
static void message(const char *kind,const char *format,va_list ap){char b[BUFSZ*2];vsnprintf(b,sizeof b,format,ap);append("%s:%s;",kind,b);}
#define MESSAGE(name) void name(const char *format,...){va_list ap;va_start(ap,format);message(#name,format,ap);va_end(ap);}
MESSAGE(pline) MESSAGE(pline_The) MESSAGE(You) MESSAGE(You_feel) MESSAGE(verbalize) MESSAGE(impossible)
void livelog_printf(long mask,const char *format,...){va_list ap;append("live:%ld;",mask);va_start(ap,format);message("log",format,ap);va_end(ap);}
boolean rng_log_enabled(void){return options[19];}
void rng_log_set_caller(const char *file,int line,const char *function){const char *base=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",base?base+1:file,line,function);}
static int draw(const char *kind,int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;append("%s:%d:%d@%s;",kind,n,v,caller);return v;}
int (rn2)(int n){return draw("rn2",n);}
int (rnd)(int n){return draw("rnd",n)+1;}
int (d)(int n,int sides){int i,total=0;append("dice:%d:%d;",n,sides);for(i=0;i<n;i++)total+=draw("die",sides)+1;return total;}
struct mextra *newmextra(void){append("newextra;");return calloc(1,sizeof(struct mextra));}
boolean is_art(struct obj *o,int art){append("isart:%d;",art);return o&&o->oartifact==art;}
aligntyp mon_aligntyp(struct monst *m){append("malign:%d;",(int)(m-pool));return m->ispriest?EPRI(m)->shralign:m->isminion?EMIN(m)->min_align:(m->data->maligntyp==A_NONE?A_NONE:sgn(m->data->maligntyp));}
int sensemon(struct monst *m){append("sense:%d;",(int)(m-pool));return options[3];}
int canseemon(struct monst *m){append("see:%d;",(int)(m-pool));return options[4]&&!m->minvis;}
#define MONNAME(name,text) char *name(struct monst *m){append(#name ":%d;",(int)(m-pool));return text;}
MONNAME(Monnam,"Fixture Demon") MONNAME(Amonnam,"A fixture demon") MONNAME(mon_nam,"the fixture demon")
char *x_monnam(struct monst *m,int article,const char *adj,int suppress,boolean called){append("xname:%d:%d:%s:%d:%d;",(int)(m-pool),article,adj?adj:"<null>",suppress,called);return "a fixture demon";}
const char *align_gname(aligntyp a){append("god:%d;",a);return "Fixture Deity";}
void set_voice(struct monst *m,int32_t tone,int32_t volume,int32_t more){append("voice:%d:%d:%d:%d;",m?(int)(m-pool):-1,tone,volume,more);}
struct permonst *mkclass(char symbol,int flags){append("class:%d:%d;",symbol,flags);return options[5]<0?NULL:&mons[options[5]];}
struct permonst *mkclass_aligned(char symbol,int flags,aligntyp a){append("aligned:%d:%d:%d;",symbol,flags,a);return options[6]<0?NULL:&mons[options[6]];}
static struct monst *create_mon(struct permonst *data,coordxy x,coordxy y,mmflags_nht flags){struct monst *m;int i,count=1+options[2];if(created_count+count>=SIZE(pool))abort();m=&pool[++created_count];memset(m,0,sizeof *m);m->data=data;m->m_id=100+created_count;m->mx=x;m->my=y;m->mhp=m->mhpmax=20;m->mpeaceful=options[1];m->mcanmove=1;m->cham=NON_PM;m->mstrategy=0xffffffffffffffffUL;if(flags&MM_EMIN)newemin(m);m->nmon=fmon;fmon=m;for(i=1;i<count;i++){struct monst *extra=&pool[++created_count];memset(extra,0,sizeof *extra);extra->data=&mons[PM_HUMAN];extra->mhp=10;extra->m_id=100+created_count;extra->nmon=fmon;fmon=extra;}return m;}
struct monst *makemon(struct permonst *data,coordxy x,coordxy y,mmflags_nht flags){append("make:%d:%d:%d:%lu;",monsndx(data),x,y,(unsigned long)flags);make_calls++;if(options[0]&&make_calls%options[0]==0)return NULL;return create_mon(data,x,y,flags);}
struct monst *mk_roamer(struct permonst *data,aligntyp a,coordxy x,coordxy y,boolean peaceful){struct monst *m;append("roam:%d:%d:%d:%d:%d;",monsndx(data),a,x,y,peaceful);if(options[7])return NULL;m=create_mon(data,x,y,MM_EMIN);m->mpeaceful=peaceful;m->isminion=1;EMIN(m)->min_align=a;return m;}
void show_transient_light(struct obj *o,coordxy x,coordxy y){append("light:%d:%d:%d;",o!=NULL,x,y);}
void transient_light_cleanup(void){append("light-clean;");}
const char *msummon_environ(struct permonst *data,const char **cloud){append("environ:%d;",monsndx(data));*cloud="cloud";return "fixture smoke";}
boolean In_hell(d_level *level){append("hell:%d:%d;",level->dnum,level->dlevel);return options[8];}
boolean is_fainted(void){append("fainted;");return options[9];}
void reset_faint(void){append("wake;");}
void stop_occupation(void){append("stop;");}
void nomul(int n){append("nomul:%d;",n);gm.multi=n;}
void unmul(const char *s){append("unmul:%s;",s?s:"<null>");}
boolean tele_restrict(struct monst *m){append("restrict:%d;",(int)(m-pool));return options[10];}
boolean rloc(struct monst *m,unsigned flags){append("rloc:%d:%u;",(int)(m-pool),flags);m->mx=31;m->my=17;return TRUE;}
long money_cnt(struct obj *o){append("money:%d:%ld;",o==gi.invent,cash);return cash;}
long money2mon(struct monst *m,long amount){append("pay:%d:%ld;",(int)(m-pool),amount);cash-=amount;return amount;}
int mon_has_amulet(struct monst *m){append("hasamulet:%d;",(int)(m-pool));return options[11];}
const char *currency(long amount){append("currency:%ld;",amount);return amount==1?"zorkmid":"zorkmids";}
schar acurr(int attribute){append("attribute:%d;",attribute);return options[12];}
void getlin(const char *prompt,char *out){append("getlin:%s;",prompt);strcpy(out,input);}
void set_malign(struct monst *m){append("setalign:%d;",(int)(m-pool));}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
void mongone(struct monst *m){struct monst **p=&fmon;append("gone:%d;",(int)(m-pool));m->mhp=0;while(*p&&*p!=m)p=&(*p)->nmon;if(*p)*p=m->nmon;}
boolean enexto(coord *c,coordxy x,coordxy y,struct permonst *data){append("next:%d:%d:%d;",x,y,monsndx(data));c->x=x+1;c->y=y+1;return !options[13];}
int Hear_again(void){append("hear;");if(options[14]){u.uprops[DEAF].intrinsic=u.uprops[DEAF].extrinsic=0;}return 0;}
struct obj *select_hwep(struct monst *m){append("weapon:%d;",(int)(m-pool));return options[15]?NULL:&equipment[0];}
struct obj *mksobj(int type,boolean init,boolean artifact){append("object:%d:%d:%d;",type,init,artifact);equipment[0].otyp=type;return &equipment[0];}
int mpickobj(struct monst *m,struct obj *o){append("pickup:%d:%d;",(int)(m-pool),(int)(o-equipment));m->minvent=o;return 0;}
void bless(struct obj *o){append("bless:%d;",(int)(o-equipment));o->blessed=1;o->cursed=0;}
struct obj *which_armor(struct monst *m,long slot){append("armor:%d:%ld;",(int)(m-pool),slot);return options[16]?NULL:&equipment[1];}
struct obj *mongets(struct monst *m,int type){append("mongets:%d:%d;",(int)(m-pool),type);equipment[2].otyp=type;return &equipment[2];}
void m_dowear(struct monst *m,boolean creation){append("wear:%d:%d;",(int)(m-pool),creation);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/minion.c"
#endif
#include "tu-minion-layout.h"
void probe_reset(unsigned seed){int i;for(i=0;i<SIZE(pool);i++)if(pool[i].mextra){free(EMIN(&pool[i]));free(EPRI(&pool[i]));free(pool[i].mextra);}monst_globals_init();objects_globals_init();memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&gm,0,sizeof gm);memset(&svm,0,sizeof svm);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&disp,0,sizeof disp);memset(&svl,0,sizeof svl);memset(pool,0,sizeof pool);memset(equipment,0,sizeof equipment);memset(options,0,sizeof options);pool[0].data=&mons[PM_HORNED_DEVIL];pool[0].m_id=100;pool[0].mx=9;pool[0].my=11;pool[0].mhp=pool[0].mhpmax=20;pool[0].mcanmove=pool[0].mpeaceful=1;pool[0].cham=NON_PM;pool[0].mstrategy=0xffffffffffffffffUL;fmon=&pool[0];gy.youmonst.data=&mons[PM_HUMAN];u.ux=10;u.uy=12;u.ualign.type=A_LAWFUL;u.ualign.record=20;u.uz.dnum=1;astral_level.dnum=3;u.uconduct.pets=1;cash=1000;options[1]=options[3]=options[4]=options[19]=1;options[5]=PM_ANGEL;options[6]=PM_HORNED_DEVIL;options[12]=18;equipment[0].otyp=SILVER_SABER;equipment[0].spe=1;equipment[0].quan=9007199254740993L;equipment[1].otyp=SHIELD_OF_REFLECTION;uwep=NULL;input[0]=0;random_state=seed;random_length=random_index=created_count=make_calls=0;probe_trace_storage[0]=caller[0]=0;}
void probe_clear(void){probe_trace_storage[0]=0;}
const char *probe_trace(void){return probe_trace_storage;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_option(int n,int value){options[n]=value;}
void probe_input(const char *text){strcpy(input,text);}
void probe_cash(long value){cash=value;}
long probe_cash_value(void){return cash;}
void probe_hero(int align,int record,int level,int multi,long pets){u.ualign.type=align;u.ualign.record=record;u.ulevel=level;gm.multi=multi;u.uconduct.pets=pets;}
void probe_properties(long deaf,long blind,long conflict,int roledeaf,int demon,int female){u.uprops[DEAF].intrinsic=deaf;u.uprops[BLINDED].intrinsic=blind;u.uprops[CONFLICT].intrinsic=conflict;u.uroleplay.deaf=roledeaf;gy.youmonst.data=&mons[demon?PM_HORNED_DEVIL:PM_HUMAN];flags.female=female;}
void probe_wield(int artifact){equipment[3].oartifact=artifact;uwep=artifact?&equipment[3]:NULL;}
void probe_vital(int pm,int gone){svm.mvitals[pm].mvflags=gone?G_GONE:0;}
void probe_unique(int pm,int unique){if(unique)mons[pm].geno|=G_UNIQ;else mons[pm].geno&=~G_UNIQ;}
void probe_copy_monster(int pm){memcpy(&copied_monster,&mons[pm],sizeof copied_monster);pool[0].data=&copied_monster;}
void probe_endgame(int value){u.uz.dnum=value?astral_level.dnum:1;}
void probe_victim(int index,int pm,int peaceful,int hp,int guard,int x,int invisible,int cham,unsigned id,unsigned long strategy){struct monst *m=&pool[index];m->data=&mons[pm];m->mpeaceful=peaceful;m->mhp=hp;m->isgd=guard;m->mx=x;m->my=11;m->minvis=m->perminvis=invisible;m->cham=cham;m->m_id=id;m->mstrategy=strategy;}
void probe_chain(int count){int i;fmon=count?&pool[0]:NULL;for(i=0;i<count;i++)pool[i].nmon=i+1<count?&pool[i+1]:NULL;}
void probe_priest(int index,int align){struct monst *m=&pool[index];if(!m->mextra)m->mextra=newmextra();if(!EPRI(m))EPRI(m)=calloc(1,sizeof(struct epri));EPRI(m)->shralign=align;m->ispriest=1;}
void probe_minion(int index,int align,int renegade){struct monst *m=&pool[index];newemin(m);m->isminion=1;EMIN(m)->min_align=align;EMIN(m)->renegade=renegade;}
void probe_emin_flags(int index,int set,int fill){struct monst *m=&pool[index];m->isminion=set;if(fill&&m->mextra&&EMIN(m))memset(EMIN(m),fill,sizeof(struct emin));}
void probe_equip(int spe,int shield){equipment[0].spe=spe;equipment[1].otyp=shield;}
void probe_emin(int index,int release){if(release)free_emin(&pool[index]);else newemin(&pool[index]);}
void *probe_emin_pointer(int index){return pool[index].mextra?EMIN(&pool[index]):NULL;}
size_t probe_emin_size(void){return sizeof(struct emin);}
int probe_mon_field(int index,int field){struct monst *m=&pool[index];switch(field){case 0:return m->data?monsndx(m->data):-1;case 1:return m->mpeaceful;case 2:return m->isminion;case 3:return m->mextra!=NULL;case 4:return m->mextra&&EMIN(m)!=NULL;case 5:return m->mtame;case 6:return m->minvis;case 7:return m->perminvis;case 8:return m->m_lev;case 9:return m->mhp;case 10:return m->mhpmax;case 11:return m->mx;case 12:return m->my;default:return m->nmon?(int)(m->nmon-pool):-1;}}
unsigned long probe_strategy(int index){return pool[index].mstrategy;}
unsigned probe_parent(int index){return EMIN(&pool[index])->parentmid;}
int probe_count(void){return created_count;}
long probe_pets(void){return u.uconduct.pets;}
int probe_botl(void){return disp.botl;}
void *probe_object_pointer(int n){return &equipment[n];}
size_t probe_object_size(void){return sizeof(struct obj);}
int probe_elemental(int n){
#ifdef TELEPORT_REFERENCE_TU
return elementals[n];
#else
return -1;
#endif
}
int probe_action(int action,int value){switch(action){case 0:return monster_census(value);case 1:return msummon(value?&pool[0]:NULL);case 2:summon_minion(value,TRUE);return 0;case 3:return demon_talk(&pool[0]);case 4:return dprince(value);case 5:return dlord(value);case 6:return llord();case 7:return lminion();case 8:return ndemon(value);case 9:lose_guardian_angel(value?&pool[0]:NULL);return 0;default:gain_guardian_angel();return 0;}}
void probe_summon(int align,int talk){summon_minion(align,talk);}
long probe_bribe(void){return bribe(&pool[0],"Fixture bribe?");}
size_t probe_stack(void){return emscripten_stack_get_current();}
