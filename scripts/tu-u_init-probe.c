/* Controlled U_INIT dependency fixture with the real original object catalogue.
 * No original U_INIT algorithm or initialized inventory/skill table is in hybrid C. */
#include "hack.h"
#include "tu-u_init-layout.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include <emscripten.h>
__typeof__(u) u;__typeof__(gu) gu;__typeof__(gi) gi;__typeof__(gn) gn;__typeof__(gl) gl;__typeof__(svm) svm;__typeof__(svs) svs;__typeof__(svb) svb;__typeof__(flags) flags;__typeof__(iflags) iflags;
const struct const_globals cg={0};time_t ubirthday;struct u_realtime urealtime;
struct obj *uarms,*uwep,*uarmh,*uarmg,*uarmu,*uarmc,*uarmf,*uarm,*uquiver,*uswapwep;
const struct Align aligns[]={{"law","lawful","Law",0,A_LAWFUL},{"balance","neutral","Neu",0,A_NEUTRAL},{"chaos","chaotic","Cha",0,A_CHAOTIC}};
#include "../.cache/wasm64-build/tree/src/objects.c"
static struct obj nodes[512];static int used[512],opts[24],rolls[4096],roll_pos,roll_count,seq[2048],seq_count,seq_pos;static unsigned seed;
static long clock_value,hidden_value;static char tracebuf[1048576],snapshotbuf[131072],caller[128];static void *growth;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
EM_JS(void,fixture_throw,(void),{throw new Error('U_INIT controlled panic');});
void panic(const char*f,...){va_list ap;logmsg("panic:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");fixture_throw();__builtin_unreachable();}
boolean debugcore(const char*f,boolean b){(void)f;return opts[7];}
void pline(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*f,int line,const char*fn){const char*p=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();seed=seed*1664525U+1013904223U;v=(unsigned)(roll_pos<roll_count?rolls[roll_pos]:seed)%n;roll_pos++;logmsg("rng:%d:%d@%s;",n,v,caller);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}int(rne)(int n){return draw(n)+1;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/u_init.c"
#define TELEPORT_U_INIT_VALIDATE_SOURCE 1
#else
#define trobj teleport_u_init_trobj
extern void teleport_u_init_test_knows_object(int,boolean);
#define knows_object teleport_u_init_test_knows_object
extern void teleport_u_init_test_knows_class(char);
#define knows_class teleport_u_init_test_knows_class
extern void teleport_u_init_test_u_init_role(void);
#define u_init_role teleport_u_init_test_u_init_role
extern void teleport_u_init_test_u_init_race(void);
#define u_init_race teleport_u_init_test_u_init_race
extern void teleport_u_init_test_pauper_reinit(void);
#define pauper_reinit teleport_u_init_test_pauper_reinit
extern void teleport_u_init_test_u_init_carry_attr_boost(void);
#define u_init_carry_attr_boost teleport_u_init_test_u_init_carry_attr_boost
extern const struct def_skill *teleport_u_init_test_skills_for_role(void);
#define skills_for_role teleport_u_init_test_skills_for_role
extern boolean teleport_u_init_test_restricted_spell_discipline(int);
#define restricted_spell_discipline teleport_u_init_test_restricted_spell_discipline
extern long teleport_u_init_test_trquan(const struct trobj*);
#define trquan teleport_u_init_test_trquan
extern struct obj *teleport_u_init_test_ini_inv_mkobj_filter(int,boolean);
#define ini_inv_mkobj_filter teleport_u_init_test_ini_inv_mkobj_filter
extern short teleport_u_init_test_ini_inv_obj_substitution(const struct trobj*,struct obj*);
#define ini_inv_obj_substitution teleport_u_init_test_ini_inv_obj_substitution
extern boolean teleport_u_init_test_ini_inv_adjust_obj(const struct trobj*,struct obj*);
#define ini_inv_adjust_obj teleport_u_init_test_ini_inv_adjust_obj
extern void teleport_u_init_test_ini_inv_use_obj(struct obj*);
#define ini_inv_use_obj teleport_u_init_test_ini_inv_use_obj
extern void teleport_u_init_test_ini_inv(const struct trobj*);
#define ini_inv teleport_u_init_test_ini_inv
#endif
#include "../nethack-c/wasm/tu-fragments/u_init-support.c"
static void callback(void){if(opts[8]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("grow;");}if(opts[9]){opts[9]=0;logmsg("reenter;");knows_object(SACK,TRUE);}if(opts[10])fixture_throw();}
boolean is_art(struct obj*o,int id){return o&&o->oartifact==id;}
void discover_object(int o,boolean a,boolean b,boolean c){logmsg("discover:%d:%d:%d:%d;",o,a,b,c);objects[o].oc_name_known=a;callback();}
const char*Japanese_item_name(int o,const char*unused){(void)unused;return o%19==0?"fixture-japanese":0;}
boolean adjattrib(int a,int n,int silent){logmsg("adj:%d:%d:%d;",a,n,silent);if(opts[a==A_STR?0:1]>0){opts[a==A_STR?0:1]--;return TRUE;}return FALSE;}
int inv_weight(void){int r=opts[0]+opts[1]+opts[2];logmsg("invweight:%d;",r);return r;}
void set_uasmon(void){logmsg("uasmon:%d;",u.umonnum);}
int newhp(void){logmsg("newhp:%d;",u.ulevel);callback();return 14;}
int newpw(void){logmsg("newpw:%d;",u.ulevel);return opts[3];}
void adjabil(int a,int b){logmsg("adjabil:%d:%d;",a,b);}
void init_uhunger(void){logmsg("hunger;");u.uhunger=900;}
time_t getnow(void){logmsg("clock:%ld;",clock_value);return clock_value;}
void max_rank_sz(void){logmsg("rank;");}
int spell_skilltype(int o){logmsg("spellskill:%d;",o);return objects[o].oc_skill;}
static int node_index(struct obj*o){return o?(int)(o-nodes):-1;}
struct obj*mksobj(int typ,boolean init,boolean art){int i;struct obj*o=0;for(i=0;i<512;i++)if(!used[i]){used[i]=1;o=&nodes[i];break;}if(!o)abort();memset(o,0,sizeof *o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;o->spe=opts[4];o->known=opts[5];o->cursed=1;o->opoisoned=opts[6];o->otrapped=1;logmsg("mks:%d:%d:%d:%d;",typ,init,art,i);callback();return o;}
struct obj*mkobj(int cl,boolean art){int typ=0,i,start;logmsg("mk:%d:%d;",cl,art);if(seq_pos<seq_count)typ=seq[seq_pos++];else{start=draw(NUM_OBJECTS-1)+1;for(i=0;i<NUM_OBJECTS;i++){typ=(start+i)%NUM_OBJECTS;if(objects[typ].oc_class==cl)break;}}return mksobj(typ,TRUE,art);}
void dealloc_obj(struct obj*o){logmsg("dealloc:%d;",node_index(o));used[node_index(o)]=0;}
int weight(struct obj*o){int result=(int)(o->quan*(objects[o->otyp].oc_weight?objects[o->otyp].oc_weight:1));logmsg("weight:%d:%ld:%d:%d;",o->otyp,o->quan,o->blessed,result);return result;}
void set_twoweap(boolean b){logmsg("twoweap:%d;",b);u.twoweap=b;}
void setworn(struct obj*o,long mask){logmsg("worn:%d:%ld;",node_index(o),mask);if(mask==W_ARMS)uarms=o;else if(mask==W_ARMH)uarmh=o;else if(mask==W_ARMG)uarmg=o;else if(mask==W_ARMU)uarmu=o;else if(mask==W_ARMC)uarmc=o;else if(mask==W_ARMF)uarmf=o;else if(mask==W_ARM)uarm=o;}
void setuqwep(struct obj*o){logmsg("quiver:%d;",node_index(o));uquiver=o;}
void setuwep(struct obj*o){logmsg("wield:%d;",node_index(o));uwep=o;}
void setuswapwep(struct obj*o){logmsg("swap:%d;",node_index(o));uswapwep=o;}
void initialspell(struct obj*o){logmsg("learn:%d;",o->otyp);svs.spl_book[0].sp_id=o->otyp;}
struct obj*addinv(struct obj*o){struct obj *p;logmsg("add:%d;",node_index(o));if(opts[11]){for(p=gi.invent;p;p=p->nobj)if(p->otyp==o->otyp){p->quan+=o->quan;used[node_index(o)]=0;return p;}}o->nobj=gi.invent;gi.invent=o;return o;}
void useupall(struct obj*o){logmsg("useup:%d;",node_index(o));gi.invent=o->nobj;used[node_index(o)]=0;}
long hidden_gold(boolean b){logmsg("hidden:%d:%ld;",b,hidden_value);return hidden_value;}
void init_attr(int n){logmsg("attr:%d;",n);}
void vary_init_attr(void){logmsg("vary;");}
void skill_init(const struct def_skill*s){logmsg("skills:");for(;s->skill!=P_NONE;s++){logmsg("%d/%d,",s->skill,s->skmax);u.weapon_skills[s->skill].skill=P_BASIC;u.weapon_skills[s->skill].max_skill=s->skmax;}logmsg(";");}
int num_spells(void){logmsg("numspells:%d;",opts[12]);return opts[12];}
void find_ac(void){logmsg("ac;");}
static const int fixture_roles[]={PM_ARCHEOLOGIST,PM_BARBARIAN,PM_CAVE_DWELLER,PM_HEALER,PM_KNIGHT,PM_MONK,PM_CLERIC,PM_RANGER,PM_ROGUE,PM_SAMURAI,PM_TOURIST,PM_VALKYRIE,PM_WIZARD};
static const int fixture_races[]={PM_HUMAN,PM_ELF,PM_DWARF,PM_GNOME,PM_ORC};
void probe_clear(void){tracebuf[0]=0;}
void probe_reset(unsigned v){int i,j;if(growth){free(growth);growth=0;}memset(&u,0,sizeof u);memset(&gu,0,sizeof gu);memset(&gi,0,sizeof gi);memset(&gn,0,sizeof gn);memset(&gl,0,sizeof gl);memset(&svm,0,sizeof svm);memset(&svs,0,sizeof svs);memset(&svb,0,sizeof svb);memset(&flags,0,sizeof flags);memset(nodes,0,sizeof nodes);memset(used,0,sizeof used);memset(opts,0,sizeof opts);memset(&urealtime,0x55,sizeof urealtime);objects_globals_init();seed=v;roll_pos=roll_count=seq_pos=seq_count=0;clock_value=1700000000L;hidden_value=0;ubirthday=-7;opts[3]=1;opts[4]=-2;gu.urole.mnum=fixture_roles[0];gu.urace.mnum=fixture_races[0];flags.initalign=1;u.ualign.type=A_NEUTRAL;uarms=uwep=uarmh=uarmg=uarmu=uarmc=uarmf=uarm=uquiver=uswapwep=0;discover=0;for(i=0;i<MAXOCLASSES;i++){for(j=0;j<NUM_OBJECTS;j++)if(objects[j].oc_class==i){svb.bases[i]=j;break;}}svb.bases[MAXOCLASSES]=NUM_OBJECTS;probe_clear();}
void probe_role(int r,int race){gu.urole.mnum=r<0?NON_PM:fixture_roles[r];gu.urace.mnum=race<0?NON_PM:fixture_races[race];}
void probe_option(int i,int v){opts[i]=v;}
void probe_flags(int pauper,int nudist,int blind,int disc){u.uroleplay.pauper=pauper;u.uroleplay.nudist=nudist;u.uroleplay.blind=blind;discover=disc;}
void probe_clock(long v){clock_value=v;}
void probe_long(int field,long v){switch(field){case 0:u.uroleplay.numbones=v;break;case 1:u.uroleplay.numrerolls=v;break;case 2:svm.moves=v;break;case 3:if(gi.invent)gi.invent->quan=v;break;case 4:u.umoney0=v;break;}}
void probe_money(long v){u.umoney0=v;hidden_value=v;}
void probe_roll(int v){rolls[roll_count++]=v;}
void probe_sequence(int typ){seq[seq_count++]=typ;}
void probe_skill(int i,int level,int advance){u.weapon_skills[i].skill=level;u.weapon_skills[i].advance=advance;}
void probe_object(int typ,int known,int spe,int poison){struct obj*o=mksobj(typ,TRUE,FALSE);o->known=known;o->spe=spe;o->opoisoned=poison;addinv(o);}
void probe_align(int v){u.ualign.type=v;}
static struct trobj local_trop[4];
void probe_trop(int i,int typ,int spe,int cl,int min,int max,int bless){local_trop[i]=(struct trobj){typ,spe,cl,min,max,bless};}
long probe_call(int action,int x,int y){switch(action){case 0:u_init_misc();break;case 1:u_init_inventory_attrs();break;case 2:u_init_skills_discoveries();break;case 3:u_init_role();break;case 4:u_init_race();break;case 5:pauper_reinit();break;case 6:u_init_carry_attr_boost();break;case 7:knows_object(x,y);break;case 8:knows_class(x);break;case 9:{const struct def_skill*s=skills_for_role();long z=0;for(;s->skill!=P_NONE;s++)z=z*33+s->skill*7+s->skmax;return z;}case 10:return restricted_spell_discipline(x);case 11:return trquan(&local_trop[x]);case 12:{struct obj*o=ini_inv_mkobj_filter(x,y);return o->otyp;}case 13:return ini_inv_obj_substitution(&local_trop[0],gi.invent);case 14:return ini_inv_adjust_obj(&local_trop[0],gi.invent);case 15:ini_inv_use_obj(gi.invent);break;case 16:ini_inv(local_trop);break;}return 0;}
char *probe_trace(void){return tracebuf;}
char *probe_snapshot(void){char*p=snapshotbuf;int i;struct obj*o;
#define APP(...) p+=sprintf(p,__VA_ARGS__)
APP("u:");for(i=0;i<sizeof u;i++)APP("%02x",((unsigned char*)&u)[i]);APP(";birthday:%ld;realtime:",(long)ubirthday);for(i=0;i<sizeof urealtime;i++)APP("%02x",((unsigned char*)&urealtime)[i]);APP(";flags:%d/%d/%d/%d;money:%ld;move:%ld;last:%d;nocreate:%d/%d/%d/%d;roll:%d;",flags.female,flags.initgend,flags.beginner,flags.initalign,u.umoney0,svm.moves,gl.lastinvnr,gn.nocreate,gn.nocreate2,gn.nocreate3,gn.nocreate4,roll_pos);
APP("inv:");for(o=gi.invent;o;o=o->nobj)APP("%d:%d/%d/%ld/%d/%d%d%d%d%d%d%d%d%d%d/%u,",node_index(o),o->otyp,o->oclass,o->quan,o->spe,o->known,o->dknown,o->bknown,o->rknown,o->cknown,o->lknown,o->otrapped,o->cursed,o->opoisoned,o->blessed,o->owt);
APP(";equip:%d/%d/%d/%d/%d/%d/%d/%d/%d/%d;known:",node_index(uarms),node_index(uwep),node_index(uarmh),node_index(uarmg),node_index(uarmu),node_index(uarmc),node_index(uarmf),node_index(uarm),node_index(uquiver),node_index(uswapwep));for(i=0;i<NUM_OBJECTS;i++)if(objects[i].oc_name_known)APP("%d,",i);APP(";spells:");for(i=0;i<=MAXSPELL;i++)APP("%d,",svs.spl_book[i].sp_id);return snapshotbuf;
#undef APP
}
long probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return SIZE(teleport_u_init_layout);}
const char*probe_layout_name(int i){return teleport_u_init_layout[i].name;}
long probe_layout_value(int i){return teleport_u_init_layout[i].value;}
int probe_table_count(void){return 40;}
int probe_table_rows(int i){switch(i){case 0:return 9;case 1:return 5;case 2:return 5;case 3:return 6;case 4:return 11;case 5:return 9;case 6:return 9;case 7:return 8;case 8:return 7;case 9:return 7;case 10:return 6;case 11:return 8;case 12:return 5;case 13:return 10;case 14:return 2;case 15:return 2;case 16:return 2;case 17:return 2;case 18:return 2;case 19:return 2;case 20:return 2;case 21:return 2;case 22:return 2;case 23:return 2;case 24:return 2;case 25:return 2;case 26:return 26;case 27:return 20;case 28:return 23;case 29:return 21;case 30:return 17;case 31:return 27;case 32:return 13;case 33:return 22;case 34:return 24;case 35:return 25;case 36:return 21;case 37:return 33;case 38:return 21;case 39:return 23;default:return 0;}}
long probe_table_value(int table,int row,int field){
#ifdef TELEPORT_REFERENCE_TU
switch(table){
case 0:switch(field){case 0:return Archeologist[row].trotyp;case 1:return Archeologist[row].trspe;case 2:return Archeologist[row].trclass;case 3:return Archeologist[row].trquan_min;case 4:return Archeologist[row].trquan_max;case 5:return Archeologist[row].trbless;}break;
case 1:switch(field){case 0:return Barbarian_0[row].trotyp;case 1:return Barbarian_0[row].trspe;case 2:return Barbarian_0[row].trclass;case 3:return Barbarian_0[row].trquan_min;case 4:return Barbarian_0[row].trquan_max;case 5:return Barbarian_0[row].trbless;}break;
case 2:switch(field){case 0:return Barbarian_1[row].trotyp;case 1:return Barbarian_1[row].trspe;case 2:return Barbarian_1[row].trclass;case 3:return Barbarian_1[row].trquan_min;case 4:return Barbarian_1[row].trquan_max;case 5:return Barbarian_1[row].trbless;}break;
case 3:switch(field){case 0:return Cave_man[row].trotyp;case 1:return Cave_man[row].trspe;case 2:return Cave_man[row].trclass;case 3:return Cave_man[row].trquan_min;case 4:return Cave_man[row].trquan_max;case 5:return Cave_man[row].trbless;}break;
case 4:switch(field){case 0:return Healer[row].trotyp;case 1:return Healer[row].trspe;case 2:return Healer[row].trclass;case 3:return Healer[row].trquan_min;case 4:return Healer[row].trquan_max;case 5:return Healer[row].trbless;}break;
case 5:switch(field){case 0:return Knight[row].trotyp;case 1:return Knight[row].trspe;case 2:return Knight[row].trclass;case 3:return Knight[row].trquan_min;case 4:return Knight[row].trquan_max;case 5:return Knight[row].trbless;}break;
case 6:switch(field){case 0:return Monk[row].trotyp;case 1:return Monk[row].trspe;case 2:return Monk[row].trclass;case 3:return Monk[row].trquan_min;case 4:return Monk[row].trquan_max;case 5:return Monk[row].trbless;}break;
case 7:switch(field){case 0:return Priest[row].trotyp;case 1:return Priest[row].trspe;case 2:return Priest[row].trclass;case 3:return Priest[row].trquan_min;case 4:return Priest[row].trquan_max;case 5:return Priest[row].trbless;}break;
case 8:switch(field){case 0:return Ranger[row].trotyp;case 1:return Ranger[row].trspe;case 2:return Ranger[row].trclass;case 3:return Ranger[row].trquan_min;case 4:return Ranger[row].trquan_max;case 5:return Ranger[row].trbless;}break;
case 9:switch(field){case 0:return Rogue[row].trotyp;case 1:return Rogue[row].trspe;case 2:return Rogue[row].trclass;case 3:return Rogue[row].trquan_min;case 4:return Rogue[row].trquan_max;case 5:return Rogue[row].trbless;}break;
case 10:switch(field){case 0:return Samurai[row].trotyp;case 1:return Samurai[row].trspe;case 2:return Samurai[row].trclass;case 3:return Samurai[row].trquan_min;case 4:return Samurai[row].trquan_max;case 5:return Samurai[row].trbless;}break;
case 11:switch(field){case 0:return Tourist[row].trotyp;case 1:return Tourist[row].trspe;case 2:return Tourist[row].trclass;case 3:return Tourist[row].trquan_min;case 4:return Tourist[row].trquan_max;case 5:return Tourist[row].trbless;}break;
case 12:switch(field){case 0:return Valkyrie[row].trotyp;case 1:return Valkyrie[row].trspe;case 2:return Valkyrie[row].trclass;case 3:return Valkyrie[row].trquan_min;case 4:return Valkyrie[row].trquan_max;case 5:return Valkyrie[row].trbless;}break;
case 13:switch(field){case 0:return Wizard[row].trotyp;case 1:return Wizard[row].trspe;case 2:return Wizard[row].trclass;case 3:return Wizard[row].trquan_min;case 4:return Wizard[row].trquan_max;case 5:return Wizard[row].trbless;}break;
case 14:switch(field){case 0:return Healing_book[row].trotyp;case 1:return Healing_book[row].trspe;case 2:return Healing_book[row].trclass;case 3:return Healing_book[row].trquan_min;case 4:return Healing_book[row].trquan_max;case 5:return Healing_book[row].trbless;}break;
case 15:switch(field){case 0:return Protection_book[row].trotyp;case 1:return Protection_book[row].trspe;case 2:return Protection_book[row].trclass;case 3:return Protection_book[row].trquan_min;case 4:return Protection_book[row].trquan_max;case 5:return Protection_book[row].trbless;}break;
case 16:switch(field){case 0:return Confuse_monster_book[row].trotyp;case 1:return Confuse_monster_book[row].trspe;case 2:return Confuse_monster_book[row].trclass;case 3:return Confuse_monster_book[row].trquan_min;case 4:return Confuse_monster_book[row].trquan_max;case 5:return Confuse_monster_book[row].trbless;}break;
case 17:switch(field){case 0:return Tinopener[row].trotyp;case 1:return Tinopener[row].trspe;case 2:return Tinopener[row].trclass;case 3:return Tinopener[row].trquan_min;case 4:return Tinopener[row].trquan_max;case 5:return Tinopener[row].trbless;}break;
case 18:switch(field){case 0:return Magicmarker[row].trotyp;case 1:return Magicmarker[row].trspe;case 2:return Magicmarker[row].trclass;case 3:return Magicmarker[row].trquan_min;case 4:return Magicmarker[row].trquan_max;case 5:return Magicmarker[row].trbless;}break;
case 19:switch(field){case 0:return Lamp[row].trotyp;case 1:return Lamp[row].trspe;case 2:return Lamp[row].trclass;case 3:return Lamp[row].trquan_min;case 4:return Lamp[row].trquan_max;case 5:return Lamp[row].trbless;}break;
case 20:switch(field){case 0:return Blindfold[row].trotyp;case 1:return Blindfold[row].trspe;case 2:return Blindfold[row].trclass;case 3:return Blindfold[row].trquan_min;case 4:return Blindfold[row].trquan_max;case 5:return Blindfold[row].trbless;}break;
case 21:switch(field){case 0:return Xtra_food[row].trotyp;case 1:return Xtra_food[row].trspe;case 2:return Xtra_food[row].trclass;case 3:return Xtra_food[row].trquan_min;case 4:return Xtra_food[row].trquan_max;case 5:return Xtra_food[row].trbless;}break;
case 22:switch(field){case 0:return Leash[row].trotyp;case 1:return Leash[row].trspe;case 2:return Leash[row].trclass;case 3:return Leash[row].trquan_min;case 4:return Leash[row].trquan_max;case 5:return Leash[row].trbless;}break;
case 23:switch(field){case 0:return Towel[row].trotyp;case 1:return Towel[row].trspe;case 2:return Towel[row].trclass;case 3:return Towel[row].trquan_min;case 4:return Towel[row].trquan_max;case 5:return Towel[row].trbless;}break;
case 24:switch(field){case 0:return Wishing[row].trotyp;case 1:return Wishing[row].trspe;case 2:return Wishing[row].trclass;case 3:return Wishing[row].trquan_min;case 4:return Wishing[row].trquan_max;case 5:return Wishing[row].trbless;}break;
case 25:switch(field){case 0:return Money[row].trotyp;case 1:return Money[row].trspe;case 2:return Money[row].trclass;case 3:return Money[row].trquan_min;case 4:return Money[row].trquan_max;case 5:return Money[row].trbless;}break;
case 26:switch(field){case 0:return inv_subs[row].race_pm;case 1:return inv_subs[row].item_otyp;case 2:return inv_subs[row].subs_otyp;}break;
case 27:switch(field){case 0:return Skill_A[row].skill;case 1:return Skill_A[row].skmax;}break;
case 28:switch(field){case 0:return Skill_B[row].skill;case 1:return Skill_B[row].skmax;}break;
case 29:switch(field){case 0:return Skill_C[row].skill;case 1:return Skill_C[row].skmax;}break;
case 30:switch(field){case 0:return Skill_H[row].skill;case 1:return Skill_H[row].skmax;}break;
case 31:switch(field){case 0:return Skill_K[row].skill;case 1:return Skill_K[row].skmax;}break;
case 32:switch(field){case 0:return Skill_Mon[row].skill;case 1:return Skill_Mon[row].skmax;}break;
case 33:switch(field){case 0:return Skill_P[row].skill;case 1:return Skill_P[row].skmax;}break;
case 34:switch(field){case 0:return Skill_R[row].skill;case 1:return Skill_R[row].skmax;}break;
case 35:switch(field){case 0:return Skill_Ran[row].skill;case 1:return Skill_Ran[row].skmax;}break;
case 36:switch(field){case 0:return Skill_S[row].skill;case 1:return Skill_S[row].skmax;}break;
case 37:switch(field){case 0:return Skill_T[row].skill;case 1:return Skill_T[row].skmax;}break;
case 38:switch(field){case 0:return Skill_V[row].skill;case 1:return Skill_V[row].skmax;}break;
case 39:switch(field){case 0:return Skill_W[row].skill;case 1:return Skill_W[row].skmax;}break;
}
#else
int group=0,size=0;switch(table){
case 0:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 1:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 2:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 3:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 4:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 5:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 6:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 7:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 8:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 9:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 10:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 11:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 12:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 13:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 14:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 15:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 16:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 17:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 18:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 19:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 20:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 21:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 22:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 23:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 24:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 25:group=14;size=sizeof(struct teleport_u_init_trobj);break;
case 26:group=15;size=sizeof(struct teleport_u_init_invsub);break;
case 27:group=6;size=sizeof(struct def_skill);break;
case 28:group=6;size=sizeof(struct def_skill);break;
case 29:group=6;size=sizeof(struct def_skill);break;
case 30:group=6;size=sizeof(struct def_skill);break;
case 31:group=6;size=sizeof(struct def_skill);break;
case 32:group=6;size=sizeof(struct def_skill);break;
case 33:group=6;size=sizeof(struct def_skill);break;
case 34:group=6;size=sizeof(struct def_skill);break;
case 35:group=6;size=sizeof(struct def_skill);break;
case 36:group=6;size=sizeof(struct def_skill);break;
case 37:group=6;size=sizeof(struct def_skill);break;
case 38:group=6;size=sizeof(struct def_skill);break;
case 39:group=6;size=sizeof(struct def_skill);break;
}return teleport_u_init_get(group,field,(char*)teleport_u_init_table(table)+row*size);
#endif
return 0;}
