#include "hack.h"
#include "quest.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
__typeof__(svq) svq;
__typeof__(svc) svc;
__typeof__(gf) gf;
__typeof__(gi) gi;
__typeof__(svd) svd;
__typeof__(flags) flags;
struct you u;
static struct monst victim;
static struct permonst victim_data;
static struct obj items[5];
static struct trap traps[4];
static branch quest_branch;
static s_level special;
static unsigned random_state;
static int random_values[128],random_length,random_index,options[8],deleted_trap;
static char probe_trace_storage[65536],caller[128];
void panic(const char *format,...) {abort();}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(probe_trace_storage+strlen(probe_trace_storage),sizeof probe_trace_storage-strlen(probe_trace_storage),format,ap);va_end(ap);}
static void message(const char *kind,const char *format,va_list ap){char b[BUFSZ*2];vsnprintf(b,sizeof b,format,ap);append("%s:%s;",kind,b);}
#define MESSAGE(name) void name(const char *format,...){va_list ap;va_start(ap,format);message(#name,format,ap);va_end(ap);}
MESSAGE(You) MESSAGE(pline) MESSAGE(verbalize) MESSAGE(impossible)
void livelog_printf(long mask,const char *format,...){va_list ap;append("live:%ld;",mask);va_start(ap,format);message("log",format,ap);va_end(ap);}
boolean rng_log_enabled(void){return options[7];}
void rng_log_set_caller(const char *file,int line,const char *function){const char *base=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",base?base+1:file,line,function);}
int (rn2)(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;append("rn2:%d:%d@%s;",n,v,caller);return v;}
void qt_pager(const char *key){append("qt:%s;",key);if(options[3]&&!strcmp(key,"firsttime"))nemdead();}
void com_pager(const char *key){append("com:%s;",key);}
boolean on_level(d_level *a,d_level *b){append("on:%d:%d:%d:%d;",a->dnum,a->dlevel,b->dnum,b->dlevel);return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
s_level *Is_special(d_level *level){append("special:%d:%d;",level->dnum,level->dlevel);return options[0]?&special:NULL;}
struct obj *find_quest_artifact(unsigned mask){append("find:%u;",mask);return options[1]?&items[0]:NULL;}
boolean is_quest_artifact(struct obj *o){append("artifact:%d;",(int)(o-items));return o->oartifact==7;}
void observe_object(struct obj *o){append("observe:%d;",(int)(o-items));o->dknown=1;}
void exercise(int attr,boolean good){append("exercise:%d:%d;",attr,good);}
const char *align_str(aligntyp a){append("align:%d;",a);return a==A_LAWFUL?"lawful":a==A_NEUTRAL?"neutral":"chaotic";}
char yn_function(const char *query,const char *choices,char def,boolean override){append("yn:%s:%s:%d:%d;",query,choices?choices:"<null>",def,override);return options[2];}
branch *dungeon_branch(const char *name){append("branch:%s;",name);return &quest_branch;}
void nomul(int n){append("nomul:%d;",n);}
void schedule_goto(d_level *dest,int flags,const char *pre,const char *post){append("goto:%d:%d:%d:%s:%s;",dest->dnum,dest->dlevel,flags,pre?pre:"<null>",post?post:"<null>");if(options[4])u.uevent.qexpelled=1;}
void remdun_mapseen(int dnum){append("mapseen:%d;",dnum);}
void deltrap(struct trap *t){struct trap **link=&gf.ftrap;append("deltrap:%d;",(int)(t-traps));while(*link&&*link!=t)link=&(*link)->ntrap;if(*link)*link=t->ntrap;deleted_trap=t-traps;}
void fully_identify_obj(struct obj *o){append("identify:%d;",(int)(o-items));o->dknown=o->bknown=o->known=1;}
void update_inventory(void){append("inventory;");}
struct obj *carrying(int typ){struct obj *o;append("carry:%d;",typ);for(o=gi.invent;o;o=o->nobj)if(o->otyp==typ)return o;return NULL;}
char *xname(struct obj *o){append("xname:%d;",(int)(o-items));return "fixture item";}
char *the(const char *s){static char b[BUFSZ];append("the:%s;",s);snprintf(b,sizeof b,"the %s",s);return b;}
char *noit_mon_nam(struct monst *m){append("noit:%u;",m->m_id);return "Fixture Leader";}
char *mon_nam(struct monst *m){append("monname:%u;",m->m_id);return "fixture monster";}
char *Monnam(struct monst *m){append("Monnam:%u;",m->m_id);return "Fixture Prisoner";}
int canseemon(struct monst *m){append("see:%u;",m->m_id);return options[5];}
void set_voice(struct monst *m,int32_t tone,int32_t volume,int32_t more){append("voice:%u:%d:%d:%d;",m->m_id,tone,volume,more);}
void adjalign(int n){append("adjalign:%d;",n);u.ualign.record+=n;}
boolean angry_guards(boolean silent){append("guards:%d;",silent);return TRUE;}
void setmangry(struct monst *m,boolean via_attack){append("angry:%u:%d;",m->m_id,via_attack);m->mpeaceful=0;}
boolean monnear(struct monst *m,coordxy x,coordxy y){append("near:%u:%d:%d;",m->m_id,x,y);return options[6];}
NhRegion *create_gas_cloud(coordxy x,coordxy y,int radius,int damage){append("cloud:%d:%d:%d:%d:%d;",x,y,radius,damage,svc.context.mon_moving);svc.context.mon_moving=7;if(options[3])leaddead();return NULL;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/quest.c"
#define PRIVATE(name) name
#else
extern void teleport_quest_test_on_start(void),teleport_quest_test_on_locate(void),teleport_quest_test_on_goal(void),teleport_quest_test_expulsion(boolean),teleport_quest_test_chat_with_leader(struct monst *),teleport_quest_test_chat_with_nemesis(void),teleport_quest_test_chat_with_guardian(void),teleport_quest_test_prisoner_speaks(struct monst *);
extern boolean teleport_quest_test_not_capable(void);
extern int teleport_quest_test_is_pure(boolean);
#define PRIVATE(name) teleport_quest_test_##name
#endif
#include "tu-quest-layout.h"
void probe_reset(unsigned seed){int i;monst_globals_init();memset(&u,0,sizeof u);memset(&svq,0,sizeof svq);memset(&svc,0,sizeof svc);memset(&gf,0,sizeof gf);memset(&gi,0,sizeof gi);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&victim,0,sizeof victim);memcpy(&victim_data,&mons[PM_HUMAN],sizeof victim_data);victim.data=&victim_data;victim.m_id=17;victim.mpeaceful=victim.mcanmove=1;victim.mstrategy=0xfedcba9876543210UL;svq.quest_status.leader_m_id=17;svq.quest_status.ldrgend=3;svq.quest_status.nemgend=2;svq.quest_status.godgend=1;svq.quest_status.met_intermed=svq.quest_status.got_final=svq.quest_status.offered_artifact=svq.quest_status.leader_is_dead=1;quest_dnum=2;qstart_level.dnum=qlocate_level.dnum=nemesis_level.dnum=2;qstart_level.dlevel=1;qlocate_level.dlevel=3;nemesis_level.dlevel=5;u.uz=qstart_level;u.uz0.dnum=1;u.uz0.dlevel=8;u.ulevel=MIN_QUEST_LEVEL;u.ualign.type=u.ualignbase[A_CURRENT]=u.ualignbase[A_ORIGINAL]=A_LAWFUL;u.ualign.record=MIN_QUEST_ALIGN;u.ux=11;u.uy=13;memset(items,0,sizeof items);items[0].otyp=LONG_SWORD;items[0].oartifact=7;items[1].otyp=AMULET_OF_YENDOR;items[2].otyp=BELL_OF_OPENING;items[3].otyp=FAKE_AMULET_OF_YENDOR;items[4].otyp=CANDELABRUM_OF_INVOCATION;memset(traps,0,sizeof traps);memset(&quest_branch,0,sizeof quest_branch);quest_branch.end1.dnum=1;quest_branch.end1.dlevel=8;quest_branch.end2=qstart_level;memset(options,0,sizeof options);options[0]=options[5]=options[6]=options[7]=1;options[2]='n';random_state=seed;random_length=random_index=0;deleted_trap=-1;probe_trace_storage[0]=caller[0]=0;for(i=0;i<5;i++)items[i].quan=9007199254740993L;}
void probe_clear(void){probe_trace_storage[0]=0;}
const char *probe_trace(void){return probe_trace_storage;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_option(int n,int value){options[n]=value;}
void probe_qset(int n,unsigned value){switch(n){case 0:svq.quest_status.first_start=value;break;case 1:svq.quest_status.not_ready=value;break;case 2:svq.quest_status.killed_nemesis=value;break;case 3:svq.quest_status.first_locate=value;break;case 4:svq.quest_status.made_goal=value;break;case 5:svq.quest_status.killed_leader=value;break;case 6:svq.quest_status.touched_artifact=value;break;case 7:svq.quest_status.got_quest=value;break;case 8:svq.quest_status.got_thanks=value;break;case 9:svq.quest_status.pissed_off=value;break;case 10:svq.quest_status.met_nemesis=value;break;case 11:svq.quest_status.cheater=value;break;case 12:svq.quest_status.met_leader=value;break;case 13:svq.quest_status.in_battle=value;break;}}
int probe_qget(int n){switch(n){case 0:return svq.quest_status.first_start;case 1:return svq.quest_status.not_ready;case 2:return svq.quest_status.killed_nemesis;case 3:return svq.quest_status.first_locate;case 4:return svq.quest_status.made_goal;case 5:return svq.quest_status.killed_leader;case 6:return svq.quest_status.touched_artifact;case 7:return svq.quest_status.got_quest;case 8:return svq.quest_status.got_thanks;case 9:return svq.quest_status.pissed_off;case 10:return svq.quest_status.met_nemesis;case 11:return svq.quest_status.cheater;case 12:return svq.quest_status.met_leader;default:return svq.quest_status.in_battle;}}
void probe_hset(int n,int v){switch(n){case 0:u.uevent.qcompleted=v;break;case 1:u.uevent.qexpelled=v;break;case 2:u.uhave.amulet=v;break;case 3:u.uhave.questart=v;break;case 4:u.uroleplay.deaf=v;break;case 5:flags.debug=v;break;case 6:svc.context.mon_moving=v;break;default:victim.mfrozen=v;}}
void probe_levels(int d,int lev,int od,int olev){u.uz.dnum=d;u.uz.dlevel=lev;u.uz0.dnum=od;u.uz0.dlevel=olev;}
void probe_alignment(int type,int current,int original,int record,int level){u.ualign.type=type;u.ualignbase[A_CURRENT]=current;u.ualignbase[A_ORIGINAL]=original;u.ualign.record=record;u.ulevel=level;}
void probe_deaf(long intrinsic,long extrinsic){u.uprops[DEAF].intrinsic=intrinsic;u.uprops[DEAF].extrinsic=extrinsic;}
void probe_ids(unsigned leader,unsigned id){svq.quest_status.leader_m_id=leader;victim.m_id=id;}
void probe_victim(int sound,int prisoner,int peaceful,int sleeping,int move,unsigned long strategy){memcpy(&victim_data,&mons[prisoner?PM_PRISONER:PM_HUMAN],sizeof victim_data);victim_data.msound=sound;victim.data=prisoner==1?&mons[PM_PRISONER]:&victim_data;victim.mpeaceful=peaceful;victim.msleeping=sleeping;victim.mcanmove=move;victim.mstrategy=strategy;}
void probe_inventory(unsigned mask){struct obj **link=&gi.invent;int i;for(i=0;i<5;i++){items[i].nobj=NULL;if(mask&(1U<<i)){*link=&items[i];link=&items[i].nobj;}}*link=NULL;}
void probe_traps(int a,int b,int c,int d){int types[4]={a,b,c,d},i;struct trap **link=&gf.ftrap;for(i=0;i<4;i++){memset(&traps[i],0,sizeof traps[i]);if(types[i]>=0){traps[i].ttyp=types[i];*link=&traps[i];link=&traps[i].ntrap;}}*link=NULL;}
void probe_branch(int d1,int l1,int d2,int l2){quest_branch.end1.dnum=d1;quest_branch.end1.dlevel=l1;quest_branch.end2.dnum=d2;quest_branch.end2.dlevel=l2;}
int probe_scalar(int n){switch(n){case 0:return u.uevent.qcompleted;case 1:return u.uevent.qexpelled;case 2:return svc.context.mon_moving;case 3:return deleted_trap;case 4:return victim.mpeaceful;case 5:return u.ualign.record;default:return victim.mcanmove;}}
unsigned long probe_strategy(void){return victim.mstrategy;}
int probe_trap_chain(int index){struct trap *t=gf.ftrap;while(t&&index--)t=t->ntrap;return t?t-traps:-1;}
int probe_item_bit(int index,int bit){return bit==0?items[index].dknown:bit==1?items[index].bknown:items[index].known;}
void *probe_state_pointer(int n){return n==0?(void*)&u:(void*)&svq.quest_status;}
size_t probe_state_size(int n){return n==0?sizeof u:sizeof svq.quest_status;}
void probe_action(int n,int obj){switch(n){case 0:PRIVATE(on_start)();break;case 1:PRIVATE(on_locate)();break;case 2:PRIVATE(on_goal)();break;case 3:onquest();break;case 4:nemdead();break;case 5:leaddead();break;case 6:artitouch(&items[obj]);break;case 7:PRIVATE(expulsion)(obj);break;case 8:finish_quest(obj<0?NULL:&items[obj]);break;case 9:PRIVATE(chat_with_leader)(&victim);break;case 10:leader_speaks(&victim);break;case 11:PRIVATE(chat_with_nemesis)();break;case 12:nemesis_speaks();break;case 13:nemesis_stinks(obj,13);break;case 14:PRIVATE(chat_with_guardian)();break;case 15:PRIVATE(prisoner_speaks)(&victim);break;case 16:quest_chat(&victim);break;case 17:quest_talk(&victim);break;case 18:quest_stat_check(&victim);break;}}
int probe_check(int n,int talk){return n==0?ok_to_quest():n==1?PRIVATE(not_capable)():PRIVATE(is_pure)(talk);}
size_t probe_stack(void){return emscripten_stack_get_current();}
