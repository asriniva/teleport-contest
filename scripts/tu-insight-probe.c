/* Controlled foreign dependencies; original INSIGHT reference stays unchanged. */
#include "hack.h"
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include "tu-insight-layout.h"
extern const char *const vanqorders[NUM_VANQ_ORDER_MODES][3];
static unsigned char startup_vanq[NUM_VANQ_ORDER_MODES];
__attribute__((constructor))static void capture_vanq(void){for(int i=0;i<NUM_VANQ_ORDER_MODES;i++)startup_vanq[i]=vanqorders[i][0][0];}
int probe_startup(int i){return startup_vanq[i];}
__typeof__(ge) ge;
__typeof__(flags) flags;
__typeof__(u) u;
__typeof__(svd) svd;
__typeof__(gi) gi;
__typeof__(urealtime) urealtime;
__typeof__(svp) svp;
__typeof__(gu) gu;
__typeof__(gy) gy;
__typeof__(svm) svm;
__typeof__(iflags) iflags;
__typeof__(ga) ga;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(uarmg) uarmg;
__typeof__(uwep) uwep;
__typeof__(uarmh) uarmh;
__typeof__(svk) svk;
__typeof__(uball) uball;
__typeof__(uarm) uarm;
__typeof__(uarmu) uarmu;
__typeof__(uarmc) uarmc;
__typeof__(uarms) uarms;
__typeof__(uarmf) uarmf;
__typeof__(uswapwep) uswapwep;
__typeof__(svc) svc;
__typeof__(uamul) uamul;
__typeof__(ublindf) ublindf;
__typeof__(svs) svs;
__typeof__(gf) gf;
__typeof__(svl) svl;
__typeof__(program_state) program_state;
__typeof__(gg) gg;
__typeof__(gb) gb;
__typeof__(windowprocs)windowprocs;__typeof__(gv)gv;
const char ynaqchars[]="ynaq",ynqchars[]="ynq";
const struct const_globals cg={0};const glyph_info nul_glyphinfo={0};
const struct c_common_strings c_common_strings={.c_something="something"};
const struct Gender genders[]={{.adj="male",.he="he"},{.adj="female",.he="she"},{.adj="neuter",.he="it"}};
const char *const hu_stat[]={"Satiated","Not hungry","Hungry","Weak","Fainting","Fainted","Starved"};
const char *const enc_stat[]={"Unencumbered","Burdened","Stressed","Strained","Overtaxed","Overloaded"};
const char *const attrname[]={"strength","intelligence","wisdom","dexterity","constitution","charisma"};
winid WIN_MESSAGE=1;
static struct obj items[12];static struct monst monsters[4];static struct mextra extra;static struct edog dog;
static char buffers[8][4096],trace[1048576],result[8192],snap[16384];static int integers[NUMMONS];static long options[256];static void*growth;static union any menu_values[32];static int menu_count;
static struct gamelog_line logs[3];static struct fruit fruits[2];static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long oid(const struct obj*p){return !p?-1:p>=items&&p<items+12?p-items:-3;}
static long mid(const struct monst*p){return !p?-1:p==&gy.youmonst?-2:p>=monsters&&p<monsters+4?p-monsters:-3;}
static void callback(int stage){if(options[240]==stage){options[240]=0;append("nested:%d;",count_achievements());}if(options[241]==stage&&!growth){options[241]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char*fmt,...){fprintf(stderr,"INSIGHT fixture panic: %s\n",fmt);abort();}
void impossible(const char*fmt,...){char b[8192];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
#define MESSAGE(fn)void fn(const char*fmt,...){char b[8192];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#fn ":%s;",b);callback(1);}
MESSAGE(pline)MESSAGE(You)MESSAGE(Your)MESSAGE(You_feel)MESSAGE(You_hear)MESSAGE(You_see)MESSAGE(Norep)MESSAGE(urgent_pline)MESSAGE(verbalize)
void livelog_printf(long flags,const char*fmt,...){char b[8192];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("livelog:%ld:%s;",flags,b);callback(1);}
static winid newwin(int t){append("create:%d;",t);return 1;}
static void putwin(winid w,int a,const char*t){append("put:%d:%d:%s;",w,a,t);callback(2);}
static void startwin(winid w,unsigned long f){append("start:%d:%lu;",w,f);menu_count=0;}
static void endwin(winid w,const char*s){append("end:%d:%s;",w,s?s:"[NULL]");}
static void displaywin(winid w,boolean b){append("display:%d:%d;",w,b);}
static void destroywin(winid w){append("destroy:%d;",w);}
void add_menu(winid w,const glyph_info*g,const anything*a,char c,char d,int attr,int color,const char*t,unsigned f){append("menu:%d:%d:%d:%d:%d:%u:%s;",a?a->a_int:0,c,d,attr,color,f,t);if(menu_count<32)menu_values[menu_count++]=*a;(void)w;(void)g;callback(3);}
int select_menu(winid w,int how,menu_item**out){append("select:%d:%d;",w,how);callback(4);if(options[220]<=0){*out=0;return(int)options[220];}int n=options[220]>2?2:options[220];*out=malloc(n*sizeof**out);memset(*out,0,n*sizeof**out);for(int i=0;i<n;i++)(*out)[i].item=menu_values[(options[221]+i)%menu_count];return n;}
boolean In_quest(d_level * a0){append("In_quest:");return(boolean)options[0];}
char * a_monnam(struct monst * a0){append("a_monnam:");append("m%ld;",mid(a0));return "a_monnam";}
schar acurr(int a0){append("acurr:");append("%lld;",(long long)a0);return(schar)options[2];}
void add_menu_str(winid a0,const char * a1){append("add_menu_str:");append("%lld;",(long long)a0);append("%s;",a1?a1:"[NULL]");return;}
const char * align_gname(aligntyp a0){append("align_gname:");append("%lld;",(long long)a0);return "align_gname";}
char * an(const char * a0){append("an:");append("%s;",a0?a0:"[NULL]");return "an";}
char * ansimpleoname(struct obj * a0){append("ansimpleoname:");append("o%ld;",oid(a0));return "ansimpleoname";}
const char * body_part(int a0){append("body_part:");append("%lld;",(long long)a0);return "body_part";}
boolean can_advance(int a0,boolean a1){append("can_advance:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return(boolean)options[9];}
boolean can_pray(boolean a0){append("can_pray:");append("%lld;",(long long)a0);return(boolean)options[10];}
struct obj * carrying(int a0){append("carrying:");append("%lld;",(long long)a0);return 0;}
const char * ceiling(coordxy a0,coordxy a1){append("ceiling:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return "ceiling";}
boolean costly_spot(coordxy a0,coordxy a1){append("costly_spot:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return(boolean)options[13];}
int count_wsegs(struct monst * a0){append("count_wsegs:");append("m%ld;",mid(a0));return(int)options[14];}
const char * currency(long a0){append("currency:");append("%lld;",(long long)a0);return "currency";}
boolean defended(struct monst * a0,int a1){append("defended:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);return(boolean)options[17];}
schar depth(d_level * a0){append("depth:");return(schar)options[18];}
boolean dmgtype(struct permonst * a0,int a1){append("dmgtype:");append("pm%ld;",a0?a0-mons:-1L);append("%lld;",(long long)a1);return(boolean)options[20];}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){append("dmgtype_fromattack:");append("pm%ld;",a0?a0-mons:-1L);append("%lld;",(long long)a1);append("%lld;",(long long)a2);return 0;}
xint16 dunlev(d_level * a0){append("dunlev:");return(xint16)options[22];}
char * dxdy_to_dist_descr(coordxy a0,coordxy a1,boolean a2){append("dxdy_to_dist_descr:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);return "dxdy_to_dist_descr";}
const char * empty_handed(void){append("empty_handed:");return "empty_handed";}
const char * endgamelevelname(char * a0,int a1){append("endgamelevelname:");append("%lld;",(long long)a1);strcpy(a0,"endgamelevelname");return a0;}
void find_ac(void){append("find_ac:");return;}
int find_mac(struct monst * a0){append("find_mac:");append("m%ld;",mid(a0));return(int)options[28];}
const char * fingers_or_gloves(boolean a0){append("fingers_or_gloves:");append("%lld;",(long long)a0);return "fingers_or_gloves";}
char * from_what(int a0){append("from_what:");append("%lld;",(long long)a0);return "from_what";}
boolean has_ceiling(d_level * a0){append("has_ceiling:");return(boolean)options[32];}
boolean hates_silver(struct permonst * a0){append("hates_silver:");append("pm%ld;",a0?a0-mons:-1L);return(boolean)options[33];}
long hidden_gold(boolean a0){append("hidden_gold:");append("%lld;",(long long)a0);return(long)options[34];}
const char * hliquid(const char * a0){append("hliquid:");append("%s;",a0?a0:"[NULL]");return "hliquid";}
int inv_weight(void){append("inv_weight:");return(int)options[37];}
boolean is_art(struct obj * a0,int a1){append("is_art:");append("o%ld;",oid(a0));append("%lld;",(long long)a1);return(boolean)options[38];}
boolean is_lava(coordxy a0,coordxy a1){append("is_lava:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return(boolean)options[39];}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return(boolean)options[40];}
boolean is_pool_or_lava(coordxy a0,coordxy a1){append("is_pool_or_lava:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return(boolean)options[41];}
char * item_what(int a0){append("item_what:");append("%lld;",(long long)a0);return "item_what";}
char * just_an(char * a0,const char * a1){append("just_an:");append("%s;",a1?a1:"[NULL]");strcpy(a0,"just_an");return a0;}
int magic_negation(struct monst * a0){append("magic_negation:");append("m%ld;",mid(a0));return(int)options[46];}
char * makeplural(const char * a0){append("makeplural:");append("%s;",a0?a0:"[NULL]");return "makeplural";}
const char * mbodypart(struct monst * a0,int a1){append("mbodypart:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);return "mbodypart";}
int midnight(void){append("midnight:");return(int)options[51];}
aligntyp mon_aligntyp(struct monst * a0){append("mon_aligntyp:");append("m%ld;",mid(a0));return(aligntyp)options[52];}
long money_cnt(struct obj * a0){append("money_cnt:");append("o%ld;",oid(a0));return(long)options[53];}
int near_capacity(void){append("near_capacity:");return(int)options[55];}
long newuexp(int a0){append("newuexp:");append("%lld;",(long long)a0);return(long)options[56];}
int night(void){append("night:");return(int)options[57];}
int observable_depth(d_level * a0){append("observable_depth:");return(int)options[58];}
boolean on_level(d_level * a0,d_level * a1){append("on_level:");return(boolean)options[60];}
const char * pmname(struct permonst * a0,int a1){append("pmname:");append("pm%ld;",a0?a0-mons:-1L);append("%lld;",(long long)a1);return "pmname";}
const char * rank_of(int a0,short a1,boolean a2){append("rank_of:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);return "rank_of";}
int rank_to_xlev(int a0){append("rank_to_xlev:");append("%lld;",(long long)a0);return(int)options[64];}
int reg_damg(NhRegion * a0){append("reg_damg:");return(int)options[65];}
void reorder_fruit(boolean a0){append("reorder_fruit:");append("%lld;",(long long)a0);return;}
const char * shield_simple_name(struct obj * a0){append("shield_simple_name:");append("o%ld;",oid(a0));return "shield_simple_name";}
char * simple_typename(int a0){append("simple_typename:");append("%lld;",(long long)a0);return "simple_typename";}
char * simpleonames(struct obj * a0){append("simpleonames:");append("o%ld;",oid(a0));return "simpleonames";}
char * skill_level_name(int a0,char * a1){append("skill_level_name:");append("%lld;",(long long)a0);strcpy(a1,"skill_level_name");return a1;}
const char * skill_name(int a0){append("skill_name:");append("%lld;",(long long)a0);return "skill_name";}
boolean sticks(struct permonst * a0){append("sticks:");append("pm%ld;",a0?a0-mons:-1L);return(boolean)options[74];}
int stone_luck(boolean a0){append("stone_luck:");append("%lld;",(long long)a0);return(int)options[75];}
struct obj * stuck_ring(struct obj * a0,int a1){append("stuck_ring:");append("o%ld;",oid(a0));append("%lld;",(long long)a1);return 0;}
const char * suit_simple_name(struct obj * a0){append("suit_simple_name:");append("o%ld;",oid(a0));return "suit_simple_name";}
const char * surface(coordxy a0,coordxy a1){append("surface:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return "surface";}
struct trap * t_at(coordxy a0,coordxy a1){append("t_at:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return 0;}
long temp_resist(int a0){append("temp_resist:");append("%lld;",(long long)a0);return(long)options[89];}
char * the(const char * a0){append("the:");append("%s;",a0?a0:"[NULL]");return "the";}
const char * trapname(int a0,boolean a1){append("trapname:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return "trapname";}
int u_adtyp_resistance_obj(int a0){append("u_adtyp_resistance_obj:");append("%lld;",(long long)a0);return(int)options[93];}
const char * u_gname(void){append("u_gname:");return "u_gname";}
schar uasmon_maxStr(void){append("uasmon_maxStr:");return(schar)options[95];}
const char * udeadinside(void){append("udeadinside:");return "udeadinside";}
boolean ugenocided(void){append("ugenocided:");return(boolean)options[97];}
NhRegion * visible_region_at(coordxy a0,coordxy a1){append("visible_region_at:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return 0;}
const char * waterbody_name(coordxy a0,coordxy a1){append("waterbody_name:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return "waterbody_name";}
const char * weapon_descr(struct obj * a0){append("weapon_descr:");append("o%ld;",oid(a0));return "weapon_descr";}
int weapon_type(struct obj * a0){append("weapon_type:");append("o%ld;",oid(a0));return(int)options[102];}
struct obj * which_armor(struct monst * a0,long a1){append("which_armor:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);return 0;}
int wseg_at(struct monst * a0,int a1,int a2){append("wseg_at:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);append("%lld;",(long long)a2);return(int)options[104];}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){append("x_monnam:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);append("%s;",a2?a2:"[NULL]");append("%lld;",(long long)a3);append("%lld;",(long long)a4);return "x_monnam";}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){append("yn_function:");append("%s;",a0?a0:"[NULL]");append("%s;",a1?a1:"[NULL]");append("%lld;",(long long)a2);append("%lld;",(long long)a3);return(char)options[106];}
boolean debugcore(const char*s,boolean b){append("debugcore:%s:%d;",s,b);return options[210];}
time_t getnow(void){append("getnow;");return(time_t)options[211];}
long timet_delta(time_t a,time_t b){append("timet_delta:%lld:%lld;",(long long)a,(long long)b);return(long)(a-b);}
void oc_to_str(char*a,char*b){(void)a;strcpy(b,"weapons");append("oc_to_str;");}
void mhidden_description(struct monst*m,unsigned f,char*b){(void)m;strcpy(b,"hidden");append("mhidden_description:%u;",f);}

static void rawprint(const char*s){append("raw:%s;",s);}
boolean rng_log_enabled(void){return 0;}
void rng_log_set_caller(const char*f,int l,const char*n){(void)f;(void)l;(void)n;}
int(rn2)(int n){return n?0:0;}int rn2_on_display_rng(int n){return n?0:0;}
void insane_object(const struct obj*o){(void)o;}

extern void teleport_insight_test_enlght_out(const char *);

extern void teleport_insight_test_enlght_line(const char *,const char *,const char *,const char *);

extern char * teleport_insight_test_enlght_combatinc(const char *,int,int,char *);

extern void teleport_insight_test_enlght_halfdmg(int,int);

extern boolean teleport_insight_test_walking_on_water();


extern boolean teleport_insight_test_cause_known(int);

extern char * teleport_insight_test_attrval(int,int,char *);

extern char * teleport_insight_test_fmt_elapsed_time(char *,int);

extern char * teleport_insight_test_N_times(long,char *);


extern void teleport_insight_test_background_enlightenment(int,int);

extern void teleport_insight_test_basics_enlightenment(int,int);

extern void teleport_insight_test_characteristics_enlightenment(int,int);

extern void teleport_insight_test_one_characteristic(int,int,int);

extern void teleport_insight_test_status_enlightenment(int,int);

extern void teleport_insight_test_weapon_insight(int);

extern void teleport_insight_test_item_resistance_message(int,const char *,int);

extern void teleport_insight_test_attributes_enlightenment(int,int);





extern void teleport_insight_test_show_achievements(int);








extern int teleport_insight_test_vanqsort_cmp(const void *,const void *);





extern int teleport_insight_test_num_extinct();

extern int teleport_insight_test_num_gone(int,int *);





extern char * teleport_insight_test_size_str(int);



#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/insight.c"
#else
#define N_times teleport_insight_test_N_times
#define attributes_enlightenment teleport_insight_test_attributes_enlightenment
#define attrval teleport_insight_test_attrval
#define background_enlightenment teleport_insight_test_background_enlightenment
#define basics_enlightenment teleport_insight_test_basics_enlightenment
#define cause_known teleport_insight_test_cause_known
#define characteristics_enlightenment teleport_insight_test_characteristics_enlightenment
#define enlght_combatinc teleport_insight_test_enlght_combatinc
#define enlght_halfdmg teleport_insight_test_enlght_halfdmg
#define enlght_line teleport_insight_test_enlght_line
#define enlght_out teleport_insight_test_enlght_out
#define fmt_elapsed_time teleport_insight_test_fmt_elapsed_time
#define item_resistance_message teleport_insight_test_item_resistance_message
#define num_extinct teleport_insight_test_num_extinct
#define num_gone teleport_insight_test_num_gone
#define one_characteristic teleport_insight_test_one_characteristic
#define show_achievements teleport_insight_test_show_achievements
#define size_str teleport_insight_test_size_str
#define status_enlightenment teleport_insight_test_status_enlightenment
#define vanqsort_cmp teleport_insight_test_vanqsort_cmp
#define walking_on_water teleport_insight_test_walking_on_water
#define weapon_insight teleport_insight_test_weapon_insight
#endif
int probe_layout_count(void){return SIZE(insight_layout);}const char*probe_layout_name(int i){return insight_layout[i].name;}size_t probe_layout_value(int i){return insight_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return trace;}const char*probe_result(void){return result;}
void probe_option(int i,long v){options[i]=v;}
void*probe_obj(int i){return i<0?0:&items[i];}void*probe_mon(int i){return i<0?0:&monsters[i];}void*probe_pm(int i){return &mons[i];}void*probe_buffer(int i){return buffers[i];}void*probe_ints(void){return integers;}
void probe_clear(void){trace[0]=result[0]=0;}
void probe_property(int i,long a,long b,long c){u.uprops[i].intrinsic=a;u.uprops[i].extrinsic=b;u.uprops[i].blocked=c;}
void probe_vital(int i,int born,int died,int f){svm.mvitals[i].born=born;svm.mvitals[i].died=died;svm.mvitals[i].mvflags=f;}
int probe_dependency_count(void){return 107;}
const char*probe_dependency_name(int i){static const char*const names[]={"In_quest","a_monnam","acurr","add_menu","add_menu_str","align_gname","an","ansimpleoname","body_part","can_advance","can_pray","carrying","ceiling","costly_spot","count_wsegs","currency","debugcore","defended","depth","digit","dmgtype","dmgtype_fromattack","dunlev","dxdy_to_dist_descr","empty_handed","endgamelevelname","eos","find_ac","find_mac","fingers_or_gloves","from_what","getnow","has_ceiling","hates_silver","hidden_gold","highc","hliquid","inv_weight","is_art","is_lava","is_pool","is_pool_or_lava","item_what","just_an","lcase","lowc","magic_negation","makeplural","mbodypart","memset","mhidden_description","midnight","mon_aligntyp","money_cnt","mungspaces","near_capacity","newuexp","night","observable_depth","oc_to_str","on_level","ordin","pmname","rank_of","rank_to_xlev","reg_damg","reorder_fruit","s_suffix","select_menu","shield_simple_name","simple_typename","simpleonames","skill_level_name","skill_name","sticks","stone_luck","strcat","strchr","strcmp","strcpy","strlen","strncmp","strncmpi","strstri","strsubst","stuck_ring","suit_simple_name","surface","t_at","temp_resist","the","timet_delta","trapname","u_adtyp_resistance_obj","u_gname","uasmon_maxStr","udeadinside","ugenocided","upstart","visible_region_at","waterbody_name","weapon_descr","weapon_type","which_armor","wseg_at","x_monnam","yn_function"};return names[i];}
const char*probe_table(int i,int j){return vanqorders[i][j];}
void probe_global(int i,long v){switch(i){case 0:flags.debug=v;break;case 1:flags.explore=v;break;case 2:program_state.gameover=v;break;case 3:urealtime.realtime=v;break;case 4:urealtime.start_timing=v;break;case 5:u.ualign.record=v;break;case 6:flags.vanq_sortmode=v;break;case 7:iflags.menu_requested=v;break;case 8:ge.en_via_menu=v;break;case 9:ge.en_win=v;break;case 10:u.ulevel=v;break;case 11:u.umonnum=v;break;case 12:u.umonster=v;break;case 13:u.ustuck=v<0?0:&monsters[v];break;case 14:u.usteed=v<0?0:&monsters[v];break;case 15:u.uswallow=v;break;case 16:u.utrap=v;break;case 17:u.utraptype=v;break;case 18:u.uhs=v;break;case 19:flags.female=v;break;case 20:u.uevent.ascended=v;break;case 21:u.uhave.amulet=v;break;case 22:u.ux=v;break;case 23:u.uy=v;break;case 24:gi.invent=v<0?0:&items[v];break;case 25:u.umortality=v;break;case 26:u.uinwater=v;break;case 27:u.uhandedness=v;break;case 28:u.mfemale=v;break;case 29:u.uroleplay.numbones=v;break;case 30:u.uroleplay.blind=v;break;case 31:u.uroleplay.nudist=v;break;case 32:u.uroleplay.deaf=v;break;case 33:flags.bones=v;break;case 34:flags.pickup=v;break;case 35:flags.pickup_thrown=v;break;case 36:flags.made_fruit=v;break;case 37:u.uundetected=v;break;case 38:u.uburied=v;break;case 39:u.usick_type=v;break;case 40:u.uhunger=v;break;case 41:u.twoweap=v;break;case 42:u.uhitinc=v;break;case 43:u.udaminc=v;break;case 44:u.uspellprot=v;break;case 45:u.ublessed=v;break;case 46:u.ulycn=v;break;case 47:u.mtimedone=v;break;case 48:u.uluck=v;break;case 49:u.moreluck=v;break;case 50:u.ugangr=v;break;case 51:u.ublesscnt=v;break;case 52:u.uedibility=v;break;case 53:u.umconf=v;break;case 54:u.uevent.ascended=v;break;case 55:u.ualign.type=v;break;case 56:u.ualignbase[A_CURRENT]=v;break;case 57:u.ualignbase[A_ORIGINAL]=v;break;case 58:svm.moves=v;break;case 59:u.ucreamed=v;break;case 60:u.uevent.uhand_of_elbereth=v;break;case 61:svc.context.warntype.speciesidx=v;break;}}
void probe_attribute(int i,int a,int b,int c){u.acurr.a[i]=a;u.amax.a[i]=b;gu.urace.attrmax[i]=c;}
void probe_skill(int i,int level){u.weapon_skills[i].skill=level;}
void probe_class(int i,int known){objects[i].oc_name_known=known;}
void probe_form(int i){u.umonnum=i;gy.youmonst.data=&mons[i];}
void probe_conduct(int i,long v){switch(i){case 0:u.uconduct.gnostic=v;break;case 1:u.uconduct.food=v;break;case 2:u.uconduct.unvegan=v;break;case 3:u.uconduct.unvegetarian=v;break;case 4:u.uconduct.weaphit=v;break;case 5:u.uconduct.killer=v;break;case 6:u.uconduct.literate=v;break;case 7:u.uconduct.pets=v;break;case 8:u.uconduct.polypiles=v;break;case 9:u.uconduct.polyselfs=v;break;case 10:u.uconduct.wishes=v;break;case 11:u.uconduct.wisharti=v;break;case 12:u.uconduct.sokocheat=v;break;}}
void probe_logs(void){for(int i=0;i<3;i++){logs[i].next=i<2?&logs[i+1]:0;logs[i].turn=9007199254740993L+i;logs[i].text=i==0?"discovered a secret":i==1?"hidden spoiler":"minor event";}logs[0].flags=LL_ACHIEVE;logs[1].flags=LL_SPOILER;logs[2].flags=LL_MINORAC;gg.gamelog=logs;}
void probe_fruits(void){fruits[0].nextf=&fruits[1];fruits[0].fid=1;fruits[1].fid=2;strcpy(fruits[0].fname,"Apple");strcpy(fruits[1].fname,"Pear");gf.ffruit=fruits;}
void probe_equipment(int slot,int i){struct obj**p[]={&uwep,&uswapwep,&uarm,&uarmc,&uarmh,&uarmg,&uarmf,&uarms,&uarmu,&uleft,&uright,&uamul,&ublindf,&uball};*p[slot]=i<0?0:&items[i];}
void probe_item(int i,int typ,long mask,int spe,int known){items[i].otyp=typ;items[i].owornmask=mask;items[i].spe=spe;items[i].dknown=known;items[i].oclass=objects[typ].oc_class;items[i].quan=1;}
void probe_monset(int i,int pm,int field,long v){struct monst*m=&monsters[i];if(pm>=0)m->data=&mons[pm];switch(field){case 0:m->mtame=v;break;case 1:m->mcan=v;break;case 2:m->mconf=v;break;case 3:m->mblinded=v;break;case 4:m->mcansee=v;break;case 5:m->mstun=v;break;case 6:m->msleeping=v;break;case 7:m->mfrozen=v;break;case 8:m->mcanmove=v;break;case 9:m->mstrategy=v;break;case 10:m->mflee=v;break;case 11:m->mtrapped=v;break;case 12:m->mspeed=v;break;case 13:m->minvis=v;break;case 14:m->mleashed=v;break;case 15:m->cham=v;break;case 16:m->mhp=v;break;case 17:m->mhpmax=v;break;}}
void probe_reset(void){objects_globals_init();monst_globals_init();if(growth){free(growth);growth=0;}memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&ge,0,sizeof ge);memset(&program_state,0,sizeof program_state);memset(options,0,sizeof options);memset(items,0,sizeof items);memset(monsters,0,sizeof monsters);memset(svm.mvitals,0,sizeof svm.mvitals);memset(buffers,0,sizeof buffers);memset(integers,0,sizeof integers);memset(&svc,0,sizeof svc);memset(&svd,0,sizeof svd);memset(&gu,0,sizeof gu);memset(&extra,0,sizeof extra);memset(&dog,0,sizeof dog);memset(logs,0,sizeof logs);memset(fruits,0,sizeof fruits);ge.en_win=1;u.ux=10;u.uy=10;u.ulevel=1;u.ualign.type=A_NEUTRAL;u.umonnum=u.umonster=PM_HUMAN;u.uenmax=u.uen=10;u.uhpmax=u.uhp=20;u.uz.dnum=0;u.uz.dlevel=1;u.uluck=0;u.moreluck=0;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.cham=NON_PM;flags.initgend=NEUTRAL;flags.pickup=0;gu.urole.mnum=PM_WIZARD;gu.urole.name.m="Wizard";gu.urole.name.f="Wizard";gu.urace.noun="human";gu.urace.adj="human";for(int i=0;i<A_MAX;i++)u.acurr.a[i]=u.amax.a[i]=gu.urace.attrmax[i]=18;strcpy(svp.plname,"Test Hero");strcpy(svd.dungeons[0].dname,"The Dungeons");svk.killer.name[0]=0;for(int i=0;i<4;i++){monsters[i].mextra=&extra;extra.edog=&dog;monsters[i].data=&mons[PM_HUMAN];monsters[i].mcansee=monsters[i].mcanmove=1;monsters[i].mhp=monsters[i].mhpmax=20;monsters[i].cham=NON_PM;monsters[i].mx=11+i;monsters[i].my=10;}for(int i=0;i<12;i++)items[i].otyp=DAGGER;for(int i=0;i<12-1;i++)items[i].nobj=&items[i+1];uwep=uswapwep=uarm=uarmc=uarmh=uarmg=uarmf=uarms=uarmu=uleft=uright=uamul=ublindf=uball=0;gi.invent=0;gg.gamelog=0;gf.ffruit=0;for(int i=0;i<ROWNO;i++){visrows[i]=visibility[i];memset(visibility[i],IN_SIGHT|COULD_SEE,COLNO);}gv.viz_array=visrows;windowprocs.win_create_nhwindow=newwin;windowprocs.win_putstr=putwin;windowprocs.win_putmixed=putwin;windowprocs.win_raw_print=rawprint;windowprocs.win_start_menu=startwin;windowprocs.win_end_menu=endwin;windowprocs.win_display_nhwindow=displaywin;windowprocs.win_destroy_nhwindow=destroywin;options[211]=1000;menu_count=0;probe_clear();}
const char*probe_snapshot(void){snprintf(snap,sizeof snap,"ach:");for(int i=0;i<SIZE(u.uachieved);i++)snprintf(snap+strlen(snap),sizeof snap-strlen(snap),"%d,",u.uachieved[i]);snprintf(snap+strlen(snap),sizeof snap-strlen(snap),"flags:%d:%d:%d:%d;prop:%ld:%ld;",flags.vanq_sortmode,program_state.stopprint,iflags.menu_requested,ge.en_via_menu,u.uprops[LEVITATION].blocked,u.uprops[FLYING].blocked);for(int i=0;i<8;i++)snprintf(snap+strlen(snap),sizeof snap-strlen(snap),"buf%d:%s;",i,buffers[i]);return snap;}
long probe_invoke(int op,long a,long b,long c,long d){switch(op){
case 0:enlght_out((const char *)a);return 0;
case 1:enlght_line((const char *)a,(const char *)b,(const char *)c,(const char *)d);return 0;
case 2:{const char*r=enlght_combatinc((const char *)a,(int)b,(int)c,(char *)d);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 3:enlght_halfdmg((int)a,(int)b);return 0;
case 4:{long r=walking_on_water();snprintf(result,sizeof result,"%ld",r);return r;}
case 5:{const char*r=trap_predicament((char *)a,(int)b,(signed char)c);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 6:{long r=cause_known((int)a);snprintf(result,sizeof result,"%ld",r);return r;}
case 7:{const char*r=attrval((int)a,(int)b,(char *)c);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 8:{const char*r=fmt_elapsed_time((char *)a,(int)b);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 9:{const char*r=N_times((long)a,(char *)b);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 10:enlightenment((int)a,(int)b);return 0;
case 11:background_enlightenment((int)a,(int)b);return 0;
case 12:basics_enlightenment((int)a,(int)b);return 0;
case 13:characteristics_enlightenment((int)a,(int)b);return 0;
case 14:one_characteristic((int)a,(int)b,(int)c);return 0;
case 15:status_enlightenment((int)a,(int)b);return 0;
case 16:weapon_insight((int)a);return 0;
case 17:item_resistance_message((int)a,(const char *)b,(int)c);return 0;
case 18:attributes_enlightenment((int)a,(int)b);return 0;
case 19:{long r=doattributes();snprintf(result,sizeof result,"%ld",r);return r;}
case 20:youhiding((signed char)a,(int)b);return 0;
case 21:{long r=doconduct();snprintf(result,sizeof result,"%ld",r);return r;}
case 22:show_conduct((int)a);return 0;
case 23:show_achievements((int)a);return 0;
case 24:record_achievement((signed char)a);return 0;
case 25:{long r=remove_achievement((signed char)a);snprintf(result,sizeof result,"%ld",r);return r;}
case 26:{long r=count_achievements();snprintf(result,sizeof result,"%ld",r);return r;}
case 27:{long r=achieve_rank((int)a);snprintf(result,sizeof result,"%ld",r);return r;}
case 28:{long r=sokoban_in_play();snprintf(result,sizeof result,"%ld",r);return r;}
case 29:{long r=do_gamelog();snprintf(result,sizeof result,"%ld",r);return r;}
case 30:show_gamelog((int)a);return 0;
case 31:{long r=vanqsort_cmp((const void *)a,(const void *)b);snprintf(result,sizeof result,"%ld",r);return r;}
case 32:{long r=set_vanq_order((signed char)a);snprintf(result,sizeof result,"%ld",r);return r;}
case 33:{long r=dovanquished();snprintf(result,sizeof result,"%ld",r);return r;}
case 34:list_vanquished((char)a,(signed char)b);return 0;
case 35:{long r=num_genocides();snprintf(result,sizeof result,"%ld",r);return r;}
case 36:{long r=num_extinct();snprintf(result,sizeof result,"%ld",r);return r;}
case 37:{long r=num_gone((int)a,(int *)b);snprintf(result,sizeof result,"%ld",r);return r;}
case 38:list_genocided((char)a,(signed char)b);return 0;
case 39:{long r=dogenocided();snprintf(result,sizeof result,"%ld",r);return r;}
case 40:{long r=doborn();snprintf(result,sizeof result,"%ld",r);return r;}
case 41:{const char*r=align_str((signed char)a);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 42:{const char*r=size_str((int)a);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 43:{const char*r=piousness((signed char)a,(const char *)b);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return(long)r;}
case 44:mstatusline((struct monst *)a);return 0;
case 45:ustatusline();return 0;
default:abort();}}
