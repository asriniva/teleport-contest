/* Controlled PICKUP world/menu/predicate/ownership dependencies; not a game. */
#include "hack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <errno.h>
static char namebuf[256]="fixture",pronoun[16]="their";
__typeof__(windowprocs) windowprocs;
const struct class_sym def_oc_syms[18]={{.sym=65},{.sym=66},{.sym=67},{.sym=68},{.sym=69},{.sym=70},{.sym=71},{.sym=72},{.sym=73},{.sym=74},{.sym=75},{.sym=76},{.sym=77},{.sym=78},{.sym=79},{.sym=80},{.sym=81},{.sym=82}};
__typeof__(gi) gi;
__typeof__(uarmg) uarmg;
struct permonst mons[NUMMONS+1]={{.pmidx=0},{.pmidx=1},{.pmidx=2},{.pmidx=3},{.pmidx=4},{.pmidx=5},{.pmidx=6},{.pmidx=7},{.pmidx=8},{.pmidx=9},{.pmidx=10},{.pmidx=11},{.pmidx=12},{.pmidx=13},{.pmidx=14},{.pmidx=15},{.pmidx=16},{.pmidx=17},{.pmidx=18},{.pmidx=19},{.pmidx=20},{.pmidx=21},{.pmidx=22},{.pmidx=23},{.pmidx=24},{.pmidx=25},{.pmidx=26},{.pmidx=27},{.pmidx=28},{.pmidx=29},{.pmidx=30},{.pmidx=31},{.pmidx=32},{.pmidx=33},{.pmidx=34},{.pmidx=35},{.pmidx=36},{.pmidx=37},{.pmidx=38},{.pmidx=39},{.pmidx=40},{.pmidx=41},{.pmidx=42},{.pmidx=43},{.pmidx=44},{.pmidx=45},{.pmidx=46},{.pmidx=47},{.pmidx=48},{.pmidx=49},{.pmidx=50},{.pmidx=51},{.pmidx=52},{.pmidx=53},{.pmidx=54},{.pmidx=55},{.pmidx=56},{.pmidx=57},{.pmidx=58},{.pmidx=59},{.pmidx=60},{.pmidx=61},{.pmidx=62},{.pmidx=63},{.pmidx=64},{.pmidx=65},{.pmidx=66},{.pmidx=67},{.pmidx=68},{.pmidx=69},{.pmidx=70},{.pmidx=71},{.pmidx=72},{.pmidx=73},{.pmidx=74},{.pmidx=75},{.pmidx=76},{.pmidx=77},{.pmidx=78},{.pmidx=79},{.pmidx=80},{.pmidx=81},{.pmidx=82},{.pmidx=83},{.pmidx=84},{.pmidx=85},{.pmidx=86},{.pmidx=87},{.pmidx=88},{.pmidx=89},{.pmidx=90},{.pmidx=91},{.pmidx=92},{.pmidx=93},{.pmidx=94},{.pmidx=95},{.pmidx=96},{.pmidx=97},{.pmidx=98},{.pmidx=99},{.pmidx=100},{.pmidx=101},{.pmidx=102},{.pmidx=103},{.pmidx=104},{.pmidx=105},{.pmidx=106},{.pmidx=107},{.pmidx=108},{.pmidx=109},{.pmidx=110},{.pmidx=111},{.pmidx=112},{.pmidx=113},{.pmidx=114},{.pmidx=115},{.pmidx=116},{.pmidx=117},{.pmidx=118},{.pmidx=119},{.pmidx=120},{.pmidx=121},{.pmidx=122},{.pmidx=123},{.pmidx=124},{.pmidx=125},{.pmidx=126},{.pmidx=127},{.pmidx=128},{.pmidx=129},{.pmidx=130},{.pmidx=131},{.pmidx=132},{.pmidx=133},{.pmidx=134},{.pmidx=135},{.pmidx=136},{.pmidx=137},{.pmidx=138},{.pmidx=139},{.pmidx=140},{.pmidx=141},{.pmidx=142},{.pmidx=143},{.pmidx=144},{.pmidx=145},{.pmidx=146},{.pmidx=147},{.pmidx=148},{.pmidx=149},{.pmidx=150},{.pmidx=151},{.pmidx=152},{.pmidx=153},{.pmidx=154},{.pmidx=155},{.pmidx=156},{.pmidx=157},{.pmidx=158},{.pmidx=159},{.pmidx=160},{.pmidx=161},{.pmidx=162},{.pmidx=163},{.pmidx=164},{.pmidx=165},{.pmidx=166},{.pmidx=167},{.pmidx=168},{.pmidx=169},{.pmidx=170},{.pmidx=171},{.pmidx=172},{.pmidx=173},{.pmidx=174},{.pmidx=175},{.pmidx=176},{.pmidx=177},{.pmidx=178},{.pmidx=179},{.pmidx=180},{.pmidx=181},{.pmidx=182},{.pmidx=183},{.pmidx=184},{.pmidx=185},{.pmidx=186},{.pmidx=187},{.pmidx=188},{.pmidx=189},{.pmidx=190},{.pmidx=191},{.pmidx=192},{.pmidx=193},{.pmidx=194},{.pmidx=195},{.pmidx=196},{.pmidx=197},{.pmidx=198},{.pmidx=199},{.pmidx=200},{.pmidx=201},{.pmidx=202},{.pmidx=203},{.pmidx=204},{.pmidx=205},{.pmidx=206},{.pmidx=207},{.pmidx=208},{.pmidx=209},{.pmidx=210},{.pmidx=211},{.pmidx=212},{.pmidx=213},{.pmidx=214},{.pmidx=215},{.pmidx=216},{.pmidx=217},{.pmidx=218},{.pmidx=219},{.pmidx=220},{.pmidx=221},{.pmidx=222},{.pmidx=223},{.pmidx=224},{.pmidx=225},{.pmidx=226},{.pmidx=227},{.pmidx=228},{.pmidx=229},{.pmidx=230},{.pmidx=231},{.pmidx=232},{.pmidx=233},{.pmidx=234},{.pmidx=235},{.pmidx=236},{.pmidx=237},{.pmidx=238},{.pmidx=239},{.pmidx=240},{.pmidx=241},{.pmidx=242},{.pmidx=243},{.pmidx=244},{.pmidx=245},{.pmidx=246},{.pmidx=247},{.pmidx=248},{.pmidx=249},{.pmidx=250},{.pmidx=251},{.pmidx=252},{.pmidx=253},{.pmidx=254},{.pmidx=255},{.pmidx=256},{.pmidx=257},{.pmidx=258},{.pmidx=259},{.pmidx=260},{.pmidx=261},{.pmidx=262},{.pmidx=263},{.pmidx=264},{.pmidx=265},{.pmidx=266},{.pmidx=267},{.pmidx=268},{.pmidx=269},{.pmidx=270},{.pmidx=271},{.pmidx=272},{.pmidx=273},{.pmidx=274},{.pmidx=275},{.pmidx=276},{.pmidx=277},{.pmidx=278},{.pmidx=279},{.pmidx=280},{.pmidx=281},{.pmidx=282},{.pmidx=283},{.pmidx=284},{.pmidx=285},{.pmidx=286},{.pmidx=287},{.pmidx=288},{.pmidx=289},{.pmidx=290},{.pmidx=291},{.pmidx=292},{.pmidx=293},{.pmidx=294},{.pmidx=295},{.pmidx=296},{.pmidx=297},{.pmidx=298},{.pmidx=299},{.pmidx=300},{.pmidx=301},{.pmidx=302},{.pmidx=303},{.pmidx=304},{.pmidx=305},{.pmidx=306},{.pmidx=307},{.pmidx=308},{.pmidx=309},{.pmidx=310},{.pmidx=311},{.pmidx=312},{.pmidx=313},{.pmidx=314},{.pmidx=315},{.pmidx=316},{.pmidx=317},{.pmidx=318},{.pmidx=319},{.pmidx=320},{.pmidx=321},{.pmidx=322},{.pmidx=323},{.pmidx=324},{.pmidx=325},{.pmidx=326},{.pmidx=327},{.pmidx=328},{.pmidx=329},{.pmidx=330},{.pmidx=331},{.pmidx=332},{.pmidx=333},{.pmidx=334},{.pmidx=335},{.pmidx=336},{.pmidx=337},{.pmidx=338},{.pmidx=339},{.pmidx=340},{.pmidx=341},{.pmidx=342},{.pmidx=343},{.pmidx=344},{.pmidx=345},{.pmidx=346},{.pmidx=347},{.pmidx=348},{.pmidx=349},{.pmidx=350},{.pmidx=351},{.pmidx=352},{.pmidx=353},{.pmidx=354},{.pmidx=355},{.pmidx=356},{.pmidx=357},{.pmidx=358},{.pmidx=359},{.pmidx=360},{.pmidx=361},{.pmidx=362},{.pmidx=363},{.pmidx=364},{.pmidx=365},{.pmidx=366},{.pmidx=367},{.pmidx=368},{.pmidx=369},{.pmidx=370},{.pmidx=371},{.pmidx=372},{.pmidx=373},{.pmidx=374},{.pmidx=375},{.pmidx=376},{.pmidx=377},{.pmidx=378},{.pmidx=379},{.pmidx=380},{.pmidx=381},{.pmidx=382},{.pmidx=383}};
__typeof__(u) u;
__typeof__(gy) gy;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(gd) gd;
__typeof__(iflags) iflags;
__typeof__(svl) svl;
__typeof__(flags) flags;
__typeof__(uchain) uchain;
__typeof__(svc) svc;
__typeof__(gv) gv;
__typeof__(gc) gc;
__typeof__(gb) gb;
__typeof__(gs) gs;
__typeof__(gp) gp;
__typeof__(gu) gu;
__typeof__(gm) gm;
const struct c_common_strings c_common_strings={.c_something=namebuf,.c_nothing_happens=namebuf,.c_nothing_seems_to_happen=namebuf};
const char ynaqchars[5]="ynaq";
const char ynNaqchars[7]="yn#aq";
__typeof__(yn_number) yn_number;
__typeof__(ga) ga;
const glyph_info nul_glyphinfo={.glyph=NO_GLYPH,.ttychar=32,.framecolor=NO_COLOR,.gm={.glyphflags=MG_UNEXPL,.sym={NO_COLOR,SYM_UNEXPLORED+SYM_OFF_X}}};
__typeof__(cg) cg;
__typeof__(gt) gt;
__typeof__(go) go;
__typeof__(objects) objects;
const char ynqchars[4]="ynq";
__typeof__(disp) disp;
__typeof__(uwep) uwep;
__typeof__(uball) uball;
__typeof__(gl) gl;
__typeof__(uswapwep) uswapwep;
__typeof__(uquiver) uquiver;
__typeof__(svm) svm;
const struct Gender genders[3]={{.his=pronoun},{.his=pronoun},{.his=pronoun}};
__typeof__(gn) gn;
__typeof__(uarmh) uarmh;
#ifdef HYBRID_PICKUP
extern void teleport_pickup_simple_look(struct obj * a0,boolean a1);
extern int collect_obj_classes(char * a0,struct obj * a1,boolean a2,boolean (*a3)(struct obj *),int * a4);
extern boolean teleport_pickup_query_classes(char * a0,boolean * a1,boolean * a2,const char * a3,struct obj * a4,boolean a5,int * a6);
extern boolean u_safe_from_fatal_corpse(struct obj * a0,int a1);
extern boolean teleport_pickup_fatal_corpse_mistake(struct obj * a0,boolean a1);
extern boolean rider_corpse_revival(struct obj * a0,boolean a1);
extern void force_decor(boolean a0);
extern void deferred_decor(boolean a0);
extern boolean teleport_pickup_describe_decor(void);
extern void teleport_pickup_check_here(boolean a0);
extern boolean teleport_pickup_n_or_more(struct obj * a0);
extern boolean menu_class_present(int a0);
extern void add_valid_menu_class(int a0);
extern boolean teleport_pickup_all_but_uchain(struct obj * a0);
extern boolean allow_all(struct obj * a0);
extern boolean allow_category(struct obj * a0);
extern boolean is_worn_by_type(struct obj * a0);
extern void reset_justpicked(struct obj * a0);
extern int count_justpicked(struct obj * a0);
extern struct obj * find_justpicked(struct obj * a0);
extern int pickup(int a0);
extern struct autopickup_exception * check_autopickup_exceptions(struct obj * a0);
extern boolean autopick_testobj(struct obj * a0,boolean a1);
extern int teleport_pickup_autopick(struct obj * a0,int a1,menu_item ** a2);
extern int query_objlist(const char * a0,struct obj ** a1,int a2,menu_item ** a3,int a4,boolean (*a5)(struct obj *));
extern int query_category(const char * a0,struct obj * a1,int a2,menu_item ** a3,int a4);
extern int teleport_pickup_count_categories(struct obj * a0,int a1);
extern int teleport_pickup_delta_cwt(struct obj * a0,struct obj * a1);
extern long teleport_pickup_carry_count(struct obj * a0,struct obj * a1,long a2,boolean a3,int * a4,int * a5);
extern int teleport_pickup_lift_object(struct obj * a0,struct obj * a1,long * a2,boolean a3);
extern int pickup_object(struct obj * a0,long a1,boolean a2);
extern struct obj * pick_obj(struct obj * a0);
extern void teleport_pickup_pickup_prinv(struct obj * a0,long a1,const char * a2);
extern void encumber_msg(void);
extern int container_at(coordxy a0,coordxy a1,boolean a2);
extern boolean teleport_pickup_able_to_loot(coordxy a0,coordxy a1,boolean a2);
extern boolean teleport_pickup_mon_beside(coordxy a0,coordxy a1);
extern int teleport_pickup_do_loot_cont(struct obj ** a0,int a1,int a2);
extern int doloot(void);
extern int teleport_pickup_doloot_core(void);
extern boolean teleport_pickup_reverse_loot(void);
extern int loot_mon(struct monst * a0,int * a1,boolean * a2);
extern boolean teleport_pickup_mbag_explodes(struct obj * a0,int a1);
extern boolean teleport_pickup_is_boh_item_gone(void);
extern void teleport_pickup_do_boh_explosion(struct obj * a0,boolean a1);
extern long teleport_pickup_boh_loss(struct obj * a0,boolean a1);
extern int teleport_pickup_in_container(struct obj * a0);
extern int ck_bag(struct obj * a0);
extern int teleport_pickup_out_container(struct obj * a0);
extern void removed_from_icebox(struct obj * a0);
extern long teleport_pickup_mbag_item_gone(boolean a0,struct obj * a1,boolean a2);
extern void observe_quantum_cat(struct obj * a0,boolean a1,boolean a2);
extern boolean container_gone(int (*a0)(struct obj *));
extern void teleport_pickup_explain_container_prompt(boolean a0);
extern boolean u_handsy(void);
extern int teleport_pickup_stash_ok(struct obj * a0);
extern int use_container(struct obj ** a0,boolean a1,boolean a2);
extern int teleport_pickup_traditional_loot(boolean a0);
extern int teleport_pickup_menu_loot(int a0,boolean a1);
extern char teleport_pickup_in_or_out_menu(const char * a0,struct obj * a1,boolean a2,boolean a3,boolean a4,boolean a5);
extern int teleport_pickup_tip_ok(struct obj * a0);
extern int teleport_pickup_choose_tip_container_menu(void);
extern int dotip(void);
extern void teleport_pickup_tipcontainer(struct obj * a0);
extern struct obj * teleport_pickup_tipcontainer_gettarget(struct obj * a0,boolean * a1);
extern int teleport_pickup_tipcontainer_checks(struct obj * a0,struct obj * a1,boolean a2);
#else
static void simple_look(struct obj * a0,boolean a1);
#define teleport_pickup_simple_look simple_look
static boolean query_classes(char * a0,boolean * a1,boolean * a2,const char * a3,struct obj * a4,boolean a5,int * a6);
#define teleport_pickup_query_classes query_classes
static boolean fatal_corpse_mistake(struct obj * a0,boolean a1);
#define teleport_pickup_fatal_corpse_mistake fatal_corpse_mistake
static boolean describe_decor(void);
#define teleport_pickup_describe_decor describe_decor
static void check_here(boolean a0);
#define teleport_pickup_check_here check_here
static boolean n_or_more(struct obj * a0);
#define teleport_pickup_n_or_more n_or_more
static boolean all_but_uchain(struct obj * a0);
#define teleport_pickup_all_but_uchain all_but_uchain
static int autopick(struct obj * a0,int a1,menu_item ** a2);
#define teleport_pickup_autopick autopick
static int count_categories(struct obj * a0,int a1);
#define teleport_pickup_count_categories count_categories
static int delta_cwt(struct obj * a0,struct obj * a1);
#define teleport_pickup_delta_cwt delta_cwt
static long carry_count(struct obj * a0,struct obj * a1,long a2,boolean a3,int * a4,int * a5);
#define teleport_pickup_carry_count carry_count
static int lift_object(struct obj * a0,struct obj * a1,long * a2,boolean a3);
#define teleport_pickup_lift_object lift_object
static void pickup_prinv(struct obj * a0,long a1,const char * a2);
#define teleport_pickup_pickup_prinv pickup_prinv
static boolean able_to_loot(coordxy a0,coordxy a1,boolean a2);
#define teleport_pickup_able_to_loot able_to_loot
static boolean mon_beside(coordxy a0,coordxy a1);
#define teleport_pickup_mon_beside mon_beside
static int do_loot_cont(struct obj ** a0,int a1,int a2);
#define teleport_pickup_do_loot_cont do_loot_cont
static int doloot_core(void);
#define teleport_pickup_doloot_core doloot_core
static boolean reverse_loot(void);
#define teleport_pickup_reverse_loot reverse_loot
static boolean mbag_explodes(struct obj * a0,int a1);
#define teleport_pickup_mbag_explodes mbag_explodes
static boolean is_boh_item_gone(void);
#define teleport_pickup_is_boh_item_gone is_boh_item_gone
static void do_boh_explosion(struct obj * a0,boolean a1);
#define teleport_pickup_do_boh_explosion do_boh_explosion
static long boh_loss(struct obj * a0,boolean a1);
#define teleport_pickup_boh_loss boh_loss
static int in_container(struct obj * a0);
#define teleport_pickup_in_container in_container
static int out_container(struct obj * a0);
#define teleport_pickup_out_container out_container
static long mbag_item_gone(boolean a0,struct obj * a1,boolean a2);
#define teleport_pickup_mbag_item_gone mbag_item_gone
static void explain_container_prompt(boolean a0);
#define teleport_pickup_explain_container_prompt explain_container_prompt
static int stash_ok(struct obj * a0);
#define teleport_pickup_stash_ok stash_ok
static int traditional_loot(boolean a0);
#define teleport_pickup_traditional_loot traditional_loot
static int menu_loot(int a0,boolean a1);
#define teleport_pickup_menu_loot menu_loot
static char in_or_out_menu(const char * a0,struct obj * a1,boolean a2,boolean a3,boolean a4,boolean a5);
#define teleport_pickup_in_or_out_menu in_or_out_menu
static int tip_ok(struct obj * a0);
#define teleport_pickup_tip_ok tip_ok
static int choose_tip_container_menu(void);
#define teleport_pickup_choose_tip_container_menu choose_tip_container_menu
static void tipcontainer(struct obj * a0);
#define teleport_pickup_tipcontainer tipcontainer
static struct obj * tipcontainer_gettarget(struct obj * a0,boolean * a1);
#define teleport_pickup_tipcontainer_gettarget tipcontainer_gettarget
static int tipcontainer_checks(struct obj * a0,struct obj * a1,boolean a2);
#define teleport_pickup_tipcontainer_checks tipcontainer_checks
#endif

static char tracebuf[8388608];static size_t traceused;static uint32_t seed=1;static int draws,callerline,options[128],errorcode;static const char*callerfile,*callerfn;static jmp_buf panicframe;
static struct obj opool[256];static struct monst mpool[32];static struct trap tpool[8];static struct autopickup_exception exceptions[8];static struct mextra mextra;static struct eshk eshk;static int no,nm;
_Alignas(16)static unsigned char scratch[65536];static char roomstr[8],feature[128],input[32][256];static int ninput,nextinput,answers[128],nanswer,nextanswer;
static uintptr_t borrowed[64];static unsigned char borrowedbytes[64][112];static int borrowkind[64];static int nborrow;static anything objany;static int(*queue[64])(void);static int nq;
static void*allocations[4096];static size_t allocsizes[4096];static int alloclive[4096],allockind[4096],nalloc;
static unsigned char eventbytes[4096][56];static int eventkind[4096],nevents;
static anything menuids[32][256];static int menuevent[32][256],menun[32],menukind[32],nw,activewin;static int choices[32],choices2[32];static long choicecount[32],choicecount2[32];
static void logfmt(const char*f,...){va_list ap;va_start(ap,f);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,f,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=n;}
static void fpidentity(uintptr_t);static void ptrlog(const void*p){if(!p){logfmt("0");return;}

if((uintptr_t)p>=(uintptr_t)&windowprocs&&(uintptr_t)p<(uintptr_t)&windowprocs+sizeof windowprocs){logfmt("windowprocs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&windowprocs));return;}
if((uintptr_t)p>=(uintptr_t)&def_oc_syms&&(uintptr_t)p<(uintptr_t)&def_oc_syms+sizeof def_oc_syms){logfmt("def_oc_syms+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&def_oc_syms));return;}
if((uintptr_t)p>=(uintptr_t)&gi&&(uintptr_t)p<(uintptr_t)&gi+sizeof gi){logfmt("gi+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gi));return;}
if((uintptr_t)p>=(uintptr_t)&uarmg&&(uintptr_t)p<(uintptr_t)&uarmg+sizeof uarmg){logfmt("uarmg+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uarmg));return;}
if((uintptr_t)p>=(uintptr_t)&mons&&(uintptr_t)p<(uintptr_t)&mons+sizeof mons){logfmt("mons+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mons));return;}
if((uintptr_t)p>=(uintptr_t)&u&&(uintptr_t)p<(uintptr_t)&u+sizeof u){logfmt("u+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&u));return;}
if((uintptr_t)p>=(uintptr_t)&gy&&(uintptr_t)p<(uintptr_t)&gy+sizeof gy){logfmt("gy+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gy));return;}
if((uintptr_t)p>=(uintptr_t)&WIN_MESSAGE&&(uintptr_t)p<(uintptr_t)&WIN_MESSAGE+sizeof WIN_MESSAGE){logfmt("WIN_MESSAGE+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&WIN_MESSAGE));return;}
if((uintptr_t)p>=(uintptr_t)&gd&&(uintptr_t)p<(uintptr_t)&gd+sizeof gd){logfmt("gd+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gd));return;}
if((uintptr_t)p>=(uintptr_t)&iflags&&(uintptr_t)p<(uintptr_t)&iflags+sizeof iflags){logfmt("iflags+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&iflags));return;}
if((uintptr_t)p>=(uintptr_t)&svl&&(uintptr_t)p<(uintptr_t)&svl+sizeof svl){logfmt("svl+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svl));return;}
if((uintptr_t)p>=(uintptr_t)&flags&&(uintptr_t)p<(uintptr_t)&flags+sizeof flags){logfmt("flags+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&flags));return;}
if((uintptr_t)p>=(uintptr_t)&uchain&&(uintptr_t)p<(uintptr_t)&uchain+sizeof uchain){logfmt("uchain+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uchain));return;}
if((uintptr_t)p>=(uintptr_t)&svc&&(uintptr_t)p<(uintptr_t)&svc+sizeof svc){logfmt("svc+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svc));return;}
if((uintptr_t)p>=(uintptr_t)&gv&&(uintptr_t)p<(uintptr_t)&gv+sizeof gv){logfmt("gv+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gv));return;}
if((uintptr_t)p>=(uintptr_t)&gc&&(uintptr_t)p<(uintptr_t)&gc+sizeof gc){logfmt("gc+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gc));return;}
if((uintptr_t)p>=(uintptr_t)&gb&&(uintptr_t)p<(uintptr_t)&gb+sizeof gb){logfmt("gb+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gb));return;}
if((uintptr_t)p>=(uintptr_t)&gs&&(uintptr_t)p<(uintptr_t)&gs+sizeof gs){logfmt("gs+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gs));return;}
if((uintptr_t)p>=(uintptr_t)&gp&&(uintptr_t)p<(uintptr_t)&gp+sizeof gp){logfmt("gp+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gp));return;}
if((uintptr_t)p>=(uintptr_t)&gu&&(uintptr_t)p<(uintptr_t)&gu+sizeof gu){logfmt("gu+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gu));return;}
if((uintptr_t)p>=(uintptr_t)&gm&&(uintptr_t)p<(uintptr_t)&gm+sizeof gm){logfmt("gm+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gm));return;}
if((uintptr_t)p>=(uintptr_t)&c_common_strings&&(uintptr_t)p<(uintptr_t)&c_common_strings+sizeof c_common_strings){logfmt("c_common_strings+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&c_common_strings));return;}
if((uintptr_t)p>=(uintptr_t)&ynaqchars&&(uintptr_t)p<(uintptr_t)&ynaqchars+sizeof ynaqchars){logfmt("ynaqchars+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ynaqchars));return;}
if((uintptr_t)p>=(uintptr_t)&ynNaqchars&&(uintptr_t)p<(uintptr_t)&ynNaqchars+sizeof ynNaqchars){logfmt("ynNaqchars+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ynNaqchars));return;}
if((uintptr_t)p>=(uintptr_t)&yn_number&&(uintptr_t)p<(uintptr_t)&yn_number+sizeof yn_number){logfmt("yn_number+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&yn_number));return;}
if((uintptr_t)p>=(uintptr_t)&ga&&(uintptr_t)p<(uintptr_t)&ga+sizeof ga){logfmt("ga+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ga));return;}
if((uintptr_t)p>=(uintptr_t)&nul_glyphinfo&&(uintptr_t)p<(uintptr_t)&nul_glyphinfo+sizeof nul_glyphinfo){logfmt("nul_glyphinfo+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&nul_glyphinfo));return;}
if((uintptr_t)p>=(uintptr_t)&cg&&(uintptr_t)p<(uintptr_t)&cg+sizeof cg){logfmt("cg+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&cg));return;}
if((uintptr_t)p>=(uintptr_t)&gt&&(uintptr_t)p<(uintptr_t)&gt+sizeof gt){logfmt("gt+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gt));return;}
if((uintptr_t)p>=(uintptr_t)&go&&(uintptr_t)p<(uintptr_t)&go+sizeof go){logfmt("go+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&go));return;}
if((uintptr_t)p>=(uintptr_t)&objects&&(uintptr_t)p<(uintptr_t)&objects+sizeof objects){logfmt("objects+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&objects));return;}
if((uintptr_t)p>=(uintptr_t)&ynqchars&&(uintptr_t)p<(uintptr_t)&ynqchars+sizeof ynqchars){logfmt("ynqchars+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ynqchars));return;}
if((uintptr_t)p>=(uintptr_t)&disp&&(uintptr_t)p<(uintptr_t)&disp+sizeof disp){logfmt("disp+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&disp));return;}
if((uintptr_t)p>=(uintptr_t)&uwep&&(uintptr_t)p<(uintptr_t)&uwep+sizeof uwep){logfmt("uwep+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uwep));return;}
if((uintptr_t)p>=(uintptr_t)&uball&&(uintptr_t)p<(uintptr_t)&uball+sizeof uball){logfmt("uball+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uball));return;}
if((uintptr_t)p>=(uintptr_t)&gl&&(uintptr_t)p<(uintptr_t)&gl+sizeof gl){logfmt("gl+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gl));return;}
if((uintptr_t)p>=(uintptr_t)&uswapwep&&(uintptr_t)p<(uintptr_t)&uswapwep+sizeof uswapwep){logfmt("uswapwep+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uswapwep));return;}
if((uintptr_t)p>=(uintptr_t)&uquiver&&(uintptr_t)p<(uintptr_t)&uquiver+sizeof uquiver){logfmt("uquiver+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uquiver));return;}
if((uintptr_t)p>=(uintptr_t)&svm&&(uintptr_t)p<(uintptr_t)&svm+sizeof svm){logfmt("svm+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svm));return;}
if((uintptr_t)p>=(uintptr_t)&genders&&(uintptr_t)p<(uintptr_t)&genders+sizeof genders){logfmt("genders+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&genders));return;}
if((uintptr_t)p>=(uintptr_t)&gn&&(uintptr_t)p<(uintptr_t)&gn+sizeof gn){logfmt("gn+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gn));return;}
if((uintptr_t)p>=(uintptr_t)&uarmh&&(uintptr_t)p<(uintptr_t)&uarmh+sizeof uarmh){logfmt("uarmh+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uarmh));return;}
if((uintptr_t)p>=(uintptr_t)&scratch&&(uintptr_t)p<(uintptr_t)&scratch+sizeof scratch){logfmt("scratch+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&scratch));return;}
if((uintptr_t)p>=(uintptr_t)&opool&&(uintptr_t)p<(uintptr_t)&opool+sizeof opool){logfmt("opool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&opool));return;}
if((uintptr_t)p>=(uintptr_t)&mpool&&(uintptr_t)p<(uintptr_t)&mpool+sizeof mpool){logfmt("mpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mpool));return;}
if((uintptr_t)p>=(uintptr_t)&tpool&&(uintptr_t)p<(uintptr_t)&tpool+sizeof tpool){logfmt("tpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&tpool));return;}
if((uintptr_t)p>=(uintptr_t)&exceptions&&(uintptr_t)p<(uintptr_t)&exceptions+sizeof exceptions){logfmt("exceptions+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&exceptions));return;}
if((uintptr_t)p>=(uintptr_t)&mextra&&(uintptr_t)p<(uintptr_t)&mextra+sizeof mextra){logfmt("mextra+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mextra));return;}
if((uintptr_t)p>=(uintptr_t)&eshk&&(uintptr_t)p<(uintptr_t)&eshk+sizeof eshk){logfmt("eshk+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&eshk));return;}
if((uintptr_t)p>=(uintptr_t)&roomstr&&(uintptr_t)p<(uintptr_t)&roomstr+sizeof roomstr){logfmt("roomstr+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&roomstr));return;}
if((uintptr_t)p>=(uintptr_t)&feature&&(uintptr_t)p<(uintptr_t)&feature+sizeof feature){logfmt("feature+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&feature));return;}
if((uintptr_t)p>=(uintptr_t)&input&&(uintptr_t)p<(uintptr_t)&input+sizeof input){logfmt("input+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&input));return;}
if((uintptr_t)p>=(uintptr_t)&objany&&(uintptr_t)p<(uintptr_t)&objany+sizeof objany){logfmt("objany+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&objany));return;}
if((uintptr_t)p>=(uintptr_t)&namebuf&&(uintptr_t)p<(uintptr_t)&namebuf+sizeof namebuf){logfmt("namebuf+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&namebuf));return;}
if((uintptr_t)p>=(uintptr_t)&pronoun&&(uintptr_t)p<(uintptr_t)&pronoun+sizeof pronoun){logfmt("pronoun+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&pronoun));return;}
if((uintptr_t)p>=(uintptr_t)&eventbytes&&(uintptr_t)p<(uintptr_t)&eventbytes+sizeof eventbytes){logfmt("eventbytes+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&eventbytes));return;}
if((uintptr_t)p>=(uintptr_t)&borrowedbytes&&(uintptr_t)p<(uintptr_t)&borrowedbytes+sizeof borrowedbytes){logfmt("borrowedbytes+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&borrowedbytes));return;}

for(int i=0;i<nalloc;i++)if(alloclive[i]&&(uintptr_t)p>=(uintptr_t)allocations[i]&&(uintptr_t)p<(uintptr_t)allocations[i]+allocsizes[i]){logfmt("A%d+%llu",i,(unsigned long long)((uintptr_t)p-(uintptr_t)allocations[i]));return;}logfmt("UNKNOWN:%llu",(unsigned long long)(uintptr_t)p);}
void*__real_malloc(size_t);void __real_free(void*);
void*__wrap_malloc(size_t n){if(nalloc==4096)abort();void*p=__real_malloc(n);if(p)memset(p,0,n);allocations[nalloc]=p;allocsizes[nalloc]=n;alloclive[nalloc++]=1;return p;}
void __wrap_free(void*p){logfmt("free(");ptrlog(p);logfmt(")\n");for(int i=0;i<nalloc;i++)if(alloclive[i]&&allocations[i]==p){alloclive[i]=0;break;}__real_free(p);}
static int roll(const char*n,int bound){if(bound<=0){logfmt("BADRNG %d\n",bound);longjmp(panicframe,2);}seed=seed*1664525U+1013904223U;int v=seed%(unsigned)bound;draws++;logfmt("%s[%s:%d:%s](%d)=%d\n",n,callerfile?callerfile:"",callerline,callerfn?callerfn:"",bound,v);return v;}
static struct obj*fixture_newobj(int typ){if(no==256)abort();struct obj*o=&opool[no++];memset(o,0,sizeof*o);o->o_id=no;o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;o->where=OBJ_FREE;return o;}
static void unlinkobj(struct obj*o){struct obj**p=0;if(o->where==OBJ_INVENT)p=&gi.invent;else if(o->where==OBJ_CONTAINED)p=&o->ocontainer->cobj;else if(o->where==OBJ_MINVENT)p=&o->ocarry->minvent;else if(o->where==OBJ_FLOOR){p=&svl.level.objects[o->ox][o->oy];while(*p&&*p!=o)p=&(*p)->nexthere;if(*p)*p=o->nexthere;p=&svl.level.objlist;}if(p){while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;}o->where=OBJ_FREE;o->nobj=0;o->v.v_ocarry=0;}
static void deleteobj(struct obj*o){if(!o)return;unlinkobj(o);o->where=OBJ_DELETED;}
static void floorobj(struct obj*o){o->where=OBJ_FLOOR;o->ox=u.ux;o->oy=u.uy;o->nexthere=svl.level.objects[u.ux][u.uy];svl.level.objects[u.ux][u.uy]=o;o->nobj=svl.level.objlist;svl.level.objlist=o;}
static winid win_create(int k){if(nw==32)abort();activewin=nw;logfmt("window.create(%d)=%d\n",k,nw+1);return ++nw;}
static void win_start(winid w,unsigned long f){activewin=w-1;menun[activewin]=0;logfmt("window.start(%d,%lu)\n",w,f);}
static void win_end(winid w,const char*s){logfmt("window.end(%d,%s)\n",w,s?s:"NULL");}
static void win_destroy(winid w){logfmt("window.destroy(%d)\n",w);}
static void win_display(winid w,boolean b){logfmt("window.display(%d,%d)\n",w,b);}
static void win_put(winid w,int a,const char*s){logfmt("window.put(%d,%d,%s)\n",w,a,s?s:"NULL");}

char * (doname)(struct obj * a0){logfmt("doname(");ptrlog(a0);logfmt(")\n");return namebuf;}
int (def_char_to_objclass)(char a0){logfmt("def_char_to_objclass(");logfmt("%lld",(long long)a0);logfmt(")\n");for(int i=0;i<MAXOCLASSES;i++)if(def_oc_syms[i].sym==a0)return i;return MAXOCLASSES;}
int (count_unpaid)(struct obj * a0){logfmt("count_unpaid(");ptrlog(a0);logfmt(")\n");int n=0;for(struct obj*o=a0;o;o=o->nobj)n+=o->unpaid;return n;}
void (tally_BUCX)(struct obj * a0,boolean a1,int * a2,int * a3,int * a4,int * a5,int * a6,int * a7){logfmt("tally_BUCX(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("OUT:int4");logfmt(",");logfmt("OUT:int4");logfmt(",");logfmt("OUT:int4");logfmt(",");logfmt("OUT:int4");logfmt(",");logfmt("OUT:int4");logfmt(",");logfmt("OUT:int4");logfmt(")\n");*a2=*a3=*a4=*a5=*a6=*a7=0;for(struct obj*o=a0;o;o=a1?o->nexthere:o->nobj){if(!o->bknown)(*a5)++;else if(o->blessed)(*a2)++;else if(o->cursed)(*a4)++;else(*a3)++;(*a6)++;if(o->pickup_prev)(*a7)++;}}
void (getlin)(const char * a0,char * a1){logfmt("getlin(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("OUT:char256");logfmt(")\n");strcpy(a1,nextinput<ninput?input[nextinput++]:"a");}
char (display_inventory)(const char * a0,boolean a1){logfmt("display_inventory(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return 0;}
boolean (poly_when_stoned)(struct permonst * a0){logfmt("poly_when_stoned(");ptrlog(a0);logfmt(")\n");return options[17];}
int (polymon)(int a0){logfmt("polymon(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[17];}
char * (corpse_xname)(struct obj * a0,const char * a1,unsigned int a2){logfmt("corpse_xname(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return namebuf;}
char * (killer_xname)(struct obj * a0){logfmt("killer_xname(");ptrlog(a0);logfmt(")\n");return namebuf;}
void (instapetrify)(const char * a0){logfmt("instapetrify(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");longjmp(panicframe,4);}
boolean (revive_corpse)(struct obj * a0){logfmt("revive_corpse(");ptrlog(a0);logfmt(")\n");if(options[18])deleteobj(a0);return options[18];}
void (exercise)(int a0,boolean a1){logfmt("exercise(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
schar (db_under_typ)(int a0){logfmt("db_under_typ(");logfmt("%lld",(long long)a0);logfmt(")\n");return ROOM;}
const char * (dfeature_at)(coordxy a0,coordxy a1,char * a2){logfmt("dfeature_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("OUT:char128");logfmt(")\n");if(!options[12])return 0;strcpy(a2,feature);return a2;}
const char * (waterbody_name)(coordxy a0,coordxy a1){logfmt("waterbody_name(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return namebuf;}
char * (an)(const char * a0){logfmt("an(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return(char*)a0;}
char * (upstart)(char * a0){logfmt("upstart(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return(char*)a0;}
void (back_on_ground)(boolean a0){logfmt("back_on_ground(");logfmt("%lld",(long long)a0);logfmt(")\n");}
void (nomul)(int a0){logfmt("nomul(");logfmt("%lld",(long long)a0);logfmt(")\n");gm.multi=a0;}
void (flush_screen)(int a0){logfmt("flush_screen(");logfmt("%lld",(long long)a0);logfmt(")\n");}
int (look_here)(int a0,unsigned int a1){logfmt("look_here(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return 0;}
void (read_engr_at)(coordxy a0,coordxy a1){logfmt("read_engr_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
void (set_bknown)(struct obj * a0,unsigned int a1){logfmt("set_bknown(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");a0->bknown=a1;}
boolean (is_worn)(struct obj * a0){logfmt("is_worn(");ptrlog(a0);logfmt(")\n");return(a0->owornmask&(W_ARMOR|W_ACCESSORY|W_WEAPONS))!=0;}
boolean (unconscious)(void){logfmt("unconscious(");logfmt(")\n");return 0;}
boolean (is_pool)(coordxy a0,coordxy a1){logfmt("is_pool(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==POOL||levl[a0][a1].typ==MOAT;}
boolean (is_lava)(coordxy a0,coordxy a1){logfmt("is_lava(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return levl[a0][a1].typ==LAVAPOOL;}
struct trap * (t_at)(coordxy a0,coordxy a1){logfmt("t_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[22]?&tpool[0]:0;}
boolean (can_reach_floor)(boolean a0){logfmt("can_reach_floor(");logfmt("%lld",(long long)a0);logfmt(")\n");return !options[2];}
boolean (uteetering_at_seen_pit)(struct trap * a0){logfmt("uteetering_at_seen_pit(");ptrlog(a0);logfmt(")\n");return 0;}
boolean (uescaped_shaft)(struct trap * a0){logfmt("uescaped_shaft(");ptrlog(a0);logfmt(")\n");return 0;}
char * (safe_qbuf)(char * a0,const char * a1,const char * a2,struct obj * a3,char *(*a4)(struct obj *),char *(*a5)(struct obj *),const char * a6){logfmt("safe_qbuf(");logfmt("OUT:charQBUFSZ");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(",");ptrlog(a3);logfmt(",");fpidentity((uintptr_t)a4);logfmt(",");fpidentity((uintptr_t)a5);logfmt(",");logfmt("%s",a6?a6:"NULL");logfmt(")\n");char*first=a4(a3);char*second=a5(a3);logfmt("safe_names:%s,%s\n",first,second);snprintf(a0,QBUFSZ,"%s%s%s",a1?a1:"",first,a2?a2:"");return a0;}
char (yn_function)(const char * a0,const char * a1,char a2,boolean a3){logfmt("yn_function(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");return nextanswer<nanswer?answers[nextanswer++]:'q';}
boolean (hideunder)(struct monst * a0){logfmt("hideunder(");ptrlog(a0);logfmt(")\n");return 0;}
void (newsym_force)(coordxy a0,coordxy a1){logfmt("newsym_force(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
char * (makesingular)(const char * a0){logfmt("makesingular(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return(char*)a0;}
boolean (regex_match)(const char * a0,struct nhregex * a1){logfmt("regex_match(");logfmt("%s",a0?a0:"NULL");logfmt(",");ptrlog(a1);logfmt(")\n");return options[25];}
boolean (costly_spot)(coordxy a0,coordxy a1){logfmt("costly_spot(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[4];}
long * (alloc)(unsigned int a0){logfmt("alloc(");logfmt("%lld",(long long)a0);logfmt(")\n");void*p=__wrap_malloc(a0);allockind[nalloc-1]=2;return(long*)p;}
Loot * (sortloot)(struct obj ** a0,unsigned int a1,boolean a2,boolean (*a3)(struct obj *)){logfmt("sortloot(");logfmt("OBJ**:");ptrlog(*a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");fpidentity((uintptr_t)a3);logfmt(")\n");int n=0;for(struct obj*o=*a0;o;o=a2?o->nexthere:o->nobj)if(!a3||a3(o))n++;Loot*out=__wrap_malloc(sizeof(*out)*(n+1));allockind[nalloc-1]=1;int j=0;for(struct obj*o=*a0;o;o=a2?o->nexthere:o->nobj)if(!a3||a3(o)){out[j].obj=o;out[j].indx=j;j++;}return out;}
void (add_menu_str)(winid a0,const char * a1){logfmt("add_menu_str(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");}
char * (strkitten)(char * a0,char a1){logfmt("strkitten(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");size_t n=strlen(a0);a0[n]=(char)a1;a0[n+1]=0;return a0;}
boolean (will_feel_cockatrice)(struct obj * a0,boolean a1){logfmt("will_feel_cockatrice(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return 0;}
void (unsortloot)(Loot ** a0){logfmt("unsortloot(");logfmt("LOOT**:");ptrlog(*a0);logfmt(")\n");__wrap_free(*a0);*a0=0;}
char * (let_to_name)(char a0,boolean a1,boolean a2){logfmt("let_to_name(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return namebuf;}
void (add_menu_heading)(winid a0,const char * a1){logfmt("add_menu_heading(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");}
int (rn2_on_display_rng)(int a0){return roll("display_rng",a0);}
void (map_glyphinfo)(coordxy a0,coordxy a1,int a2,unsigned int a3,glyph_info * a4){logfmt("map_glyphinfo(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("OUT:glyph48");logfmt(")\n");a4->glyph=a2;a4->ttychar=65;a4->gm.sym.symidx=0;a4->gm.sym.color=NO_COLOR;}
char * (doname_with_price)(struct obj * a0){logfmt("doname_with_price(");ptrlog(a0);logfmt(")\n");return namebuf;}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){logfmt("add_menu(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("BORROW:glyph48");logfmt(",");logfmt("BORROW:anything8");logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("%lld",(long long)a4);logfmt(",");logfmt("%lld",(long long)a5);logfmt(",");logfmt("%lld",(long long)a6);logfmt(",");logfmt("%s",a7?a7:"NULL");logfmt(",");logfmt("%lld",(long long)a8);logfmt(")\n");if(menukind[activewin]&&options[50]&&a2->a_obj&&((uintptr_t)a2->a_obj<(uintptr_t)opool||(uintptr_t)a2->a_obj>=(uintptr_t)(opool+256))){int found=0;for(int i=0;i<nborrow;i++)found|=borrowed[i]==(uintptr_t)a2->a_obj;if(!found){if(nborrow==64)abort();borrowed[nborrow]=(uintptr_t)a2->a_obj;borrowkind[nborrow]=options[50];if(options[50]==2)memcpy(borrowedbytes[nborrow],a2->a_obj,112);nborrow++;}}int j=menun[activewin]++;if(j==256||nevents==4096)abort();menuids[activewin][j]=*a2;menuevent[activewin][j]=nevents;memcpy(eventbytes[nevents],a1,48);memcpy(eventbytes[nevents]+48,a2,8);eventkind[nevents++]=menukind[activewin];}
struct attack * (dmgtype_fromattack)(struct permonst * a0,int a1,int a2){logfmt("dmgtype_fromattack(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return options[20]?&mons[PM_HOUSECAT].mattk[0]:0;}
char * (self_lookat)(char * a0){logfmt("self_lookat(");logfmt("OUT:char256");logfmt(")\n");strcpy(a0,"fixture hero");return a0;}
int (select_menu)(winid a0,int a1,menu_item ** a2){logfmt("select_menu(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("OUT:menu_item24**");logfmt(")\n");*a2=0;int k=choices[a0-1];if(a1==PICK_NONE||k<0)return k==-2?-1:0;if(k>=menun[a0-1])abort();int n=choices2[a0-1]>=0?2:1;menu_item*p=__wrap_malloc(n*sizeof*p);allockind[nalloc-1]=menukind[a0-1]?2:3;for(int i=0;i<n;i++){int ix=i?choices2[a0-1]:k;if(ix>=menun[a0-1])abort();p[i].item=menuids[a0-1][ix];p[i].count=i?choicecount2[a0-1]:choicecount[a0-1];p[i].itemflags=0xA1B2C3D4+i;memset((char*)&p[i]+20,0xE5+i,4);}*a2=p;return n;}
char * (ysimple_name)(struct obj * a0){logfmt("ysimple_name(");ptrlog(a0);logfmt(")\n");return namebuf;}
int (count_buc)(struct obj * a0,int a1,boolean (*a2)(struct obj *)){logfmt("count_buc(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");fpidentity((uintptr_t)a2);logfmt(")\n");int n=0;for(struct obj*o=a0;o;o=o->nobj)if((!a2||a2(o))&&(a1==BUC_BLESSED?o->blessed:a1==BUC_CURSED?o->cursed:a1==BUC_UNCURSED?o->bknown&&!o->blessed&&!o->cursed:!o->bknown))n++;return n;}
boolean (debugcore)(const char * a0,boolean a1){logfmt("debugcore(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[28];}
void (__assert_fail)(const char * a0,const char * a1,int a2,const char * a3){logfmt("__assert_fail(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%s",a3?a3:"NULL");logfmt(")\n");longjmp(panicframe,3);}
char (paranoid_ynq)(boolean a0,const char * a1,boolean a2){logfmt("paranoid_ynq(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return nextanswer<nanswer?answers[nextanswer++]:'n';}
int (weight)(struct obj * a0){logfmt("weight(");ptrlog(a0);logfmt(")\n");int n=(int)(a0->quan*2);for(struct obj*o=a0->cobj;o;o=o->nobj)n+=(int)o->owt;return n;}
long (money_cnt)(struct obj * a0){logfmt("money_cnt(");ptrlog(a0);logfmt(")\n");long n=0;for(struct obj*o=a0;o;o=o->nobj)if(o->oclass==COIN_CLASS)n+=o->quan;return n;}
int (max_capacity)(void){logfmt("max_capacity(");logfmt(")\n");return options[6]?options[6]:-1000;}
char * (xname)(struct obj * a0){logfmt("xname(");ptrlog(a0);logfmt(")\n");return namebuf;}
char * (the)(const char * a0){logfmt("the(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return(char*)a0;}
char * (otense)(struct obj * a0,const char * a1){logfmt("otense(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");return(char*)a1;}
const char * (body_part)(int a0){logfmt("body_part(");logfmt("%lld",(long long)a0);logfmt(")\n");return namebuf;}
int (inv_cnt)(boolean a0){logfmt("inv_cnt(");logfmt("%lld",(long long)a0);logfmt(")\n");int n=0;for(struct obj*o=gi.invent;o;o=o->nobj)n++;return n;}
struct obj * (carrying)(int a0){logfmt("carrying(");logfmt("%lld",(long long)a0);logfmt(")\n");for(struct obj*o=gi.invent;o;o=o->nobj)if(o->otyp==a0)return o;return 0;}
struct obj * (merge_choice)(struct obj * a0,struct obj * a1){logfmt("merge_choice(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return options[30]?&opool[0]:0;}
struct obj * (nxtobj)(struct obj * a0,int a1,boolean a2){logfmt("nxtobj(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");for(struct obj*o=a2?a0->nexthere:a0->nobj;o;o=a2?o->nexthere:o->nobj)if(o->otyp==a1)return o;return 0;}
int (near_capacity)(void){logfmt("near_capacity(");logfmt(")\n");return options[5];}
int (calc_capacity)(int a0){logfmt("calc_capacity(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[7];}
void (observe_object)(struct obj * a0){logfmt("observe_object(");ptrlog(a0);logfmt(")\n");}
int (touch_artifact)(struct obj * a0,struct monst * a1){logfmt("touch_artifact(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return !options[16];}
struct obj * (splitobj)(struct obj * a0,long a1){logfmt("splitobj(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");struct obj*o=fixture_newobj(a0->otyp);*o=*a0;o->o_id=no;o->quan=a1;a0->quan-=a1;o->nobj=a0->nobj;a0->nobj=o;svc.context.objsplit.parent_oid=a0->o_id;svc.context.objsplit.child_oid=o->o_id;return o;}
void (unbless)(struct obj * a0){logfmt("unbless(");ptrlog(a0);logfmt(")\n");a0->blessed=0;}
void (trycall)(struct obj * a0){logfmt("trycall(");ptrlog(a0);logfmt(")\n");}
void (useupf)(struct obj * a0,long a1){logfmt("useupf(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");deleteobj(a0);}
void (fix_ghostly_obj)(struct obj * a0){logfmt("fix_ghostly_obj(");ptrlog(a0);logfmt(")\n");}
boolean (get_obj_location)(struct obj * a0,coordxy * a1,coordxy * a2,int a3){logfmt("get_obj_location(");ptrlog(a0);logfmt(",");logfmt("OUT:short2");logfmt(",");logfmt("OUT:short2");logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");if(options[11])return FALSE;*a1=a0->where==OBJ_INVENT?u.ux:a0->ox;*a2=a0->where==OBJ_INVENT?u.uy:a0->oy;return TRUE;}
void (obj_extract_self)(struct obj * a0){logfmt("obj_extract_self(");ptrlog(a0);logfmt(")\n");unlinkobj(a0);}
void (newsym)(coordxy a0,coordxy a1){logfmt("newsym(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){logfmt("in_rooms(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");roomstr[0]=options[4]?ROOMOFFSET:0;roomstr[1]=0;return roomstr;}
void (addtobill)(struct obj * a0,boolean a1,boolean a2,boolean a3){logfmt("addtobill(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");}
struct obj * (addinv)(struct obj * a0){logfmt("addinv(");ptrlog(a0);logfmt(")\n");if(options[29]){struct obj*to=gi.invent;if(!to||to==a0)abort();to->quan+=a0->quan;deleteobj(a0);return to;}a0->nobj=gi.invent;gi.invent=a0;a0->where=OBJ_INVENT;return a0;}
void (remote_burglary)(coordxy a0,coordxy a1){logfmt("remote_burglary(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
void (prinv)(const char * a0,struct obj * a1,long a2){logfmt("prinv(");logfmt("%s",a0?a0:"NULL");logfmt(",");ptrlog(a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");}
const char * (stagger)(const struct permonst * a0,const char * a1){logfmt("stagger(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");return(char*)a1;}
void (rider_cant_reach)(void){logfmt("rider_cant_reach(");logfmt(")\n");}
void (cant_reach_floor)(coordxy a0,coordxy a1,boolean a2,boolean a3,boolean a4){logfmt("cant_reach_floor(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("%lld",(long long)a4);logfmt(")\n");}
const char * (hliquid)(const char * a0){logfmt("hliquid(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return namebuf;}
int (freehand)(void){logfmt("freehand(");logfmt(")\n");return !options[1];}
int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
char * (The)(const char * a0){logfmt("The(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return(char*)a0;}
struct obj * (autokey)(boolean a0){logfmt("autokey(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[24]?&opool[1]:0;}
int (pick_lock)(struct obj * a0,coordxy a1,coordxy a2,struct obj * a3){logfmt("pick_lock(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");ptrlog(a3);logfmt(")\n");return options[32];}
boolean (u_have_forceable_weapon)(void){logfmt("u_have_forceable_weapon(");logfmt(")\n");return options[35];}
void (cmdq_add_ec)(int a0,int (*a1)(void)){logfmt("cmdq_add_ec(");logfmt("%lld",(long long)a0);logfmt(",");fpidentity((uintptr_t)a1);logfmt(")\n");if(nq==64)abort();queue[nq++]=a1;}
boolean (rng_log_enabled)(void){return !options[0];}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerfn=a2;}
int (rnd)(int a0){return roll("rnd",a0)+1;}
void (losehp)(int a0,const char * a1,schar a2){logfmt("losehp(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");u.uhp-=a0;}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){logfmt("discover_object(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");}
boolean (check_capacity)(const char * a0){logfmt("check_capacity(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return options[3];}
int (rn2)(int a0){return roll("rn2",a0);}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){logfmt("sobj_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");for(struct obj*o=svl.level.objects[a1][a2];o;o=o->nexthere)if(o->otyp==a0)return o;return 0;}
void (feel_cockatrice)(struct obj * a0,boolean a1){logfmt("feel_cockatrice(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
int (get_adjacent_loc)(const char * a0,const char * a1,coordxy a2,coordxy a3,coord * a4){logfmt("get_adjacent_loc(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("OUT:coord4");logfmt(")\n");a4->x=options[8]?options[8]:u.ux;a4->y=options[9]?options[9]:u.uy;return !options[10];}
const char * (ceiling)(coordxy a0,coordxy a1){logfmt("ceiling(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return namebuf;}
char * (mon_nam)(struct monst * a0){logfmt("mon_nam(");ptrlog(a0);logfmt(")\n");return namebuf;}
void (remove_worn_item)(struct obj * a0,boolean a1){logfmt("remove_worn_item(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");a0->owornmask=0;}
void (dropx)(struct obj * a0){logfmt("dropx(");ptrlog(a0);logfmt(")\n");unlinkobj(a0);floorobj(a0);}
struct obj * (g_at)(coordxy a0,coordxy a1){logfmt("g_at(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");for(struct obj*o=svl.level.objects[a0][a1];o;o=o->nexthere)if(o->otyp==GOLD_PIECE)return o;return 0;}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logfmt("dist2(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");return(a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
void (freeinv)(struct obj * a0){logfmt("freeinv(");ptrlog(a0);logfmt(")\n");unlinkobj(a0);}
struct obj * (add_to_container)(struct obj * a0,struct obj * a1){logfmt("add_to_container(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");a1->nobj=a0->cobj;a0->cobj=a1;a1->where=OBJ_CONTAINED;a1->ocontainer=a0;return a1;}
boolean (boxlock)(struct obj * a0,struct obj * a1){logfmt("boxlock(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return options[32];}
struct permonst * (courtmon)(void){logfmt("courtmon(");logfmt(")\n");return &mons[PM_ORC];}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logfmt("makemon(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");if(options[21])return 0;if(nm==32)abort();struct monst*m=&mpool[nm++];memset(m,0,sizeof*m);m->data=a0?a0:&mons[PM_ORC];m->mx=a1;m->my=a2;return m;}
int (add_to_minv)(struct monst * a0,struct obj * a1){logfmt("add_to_minv(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");a1->nobj=a0->minvent;a0->minvent=a1;a1->where=OBJ_MINVENT;a1->ocarry=a0;return 0;}
struct obj * (which_armor)(struct monst * a0,long a1){logfmt("which_armor(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[23]?&opool[1]:0;}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){logfmt("x_monnam(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("%lld",(long long)a4);logfmt(")\n");return namebuf;}
void (extract_from_minvent)(struct monst * a0,struct obj * a1,boolean a2,boolean a3){logfmt("extract_from_minvent(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");unlinkobj(a1);}
char * (thesimpleoname)(struct obj * a0){logfmt("thesimpleoname(");ptrlog(a0);logfmt(")\n");return namebuf;}
struct obj * (hold_another_object)(struct obj * a0,const char * a1,const char * a2,const char * a3){logfmt("hold_another_object(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%s",a2?a2:"NULL");logfmt(",");logfmt("%s",a3?a3:"NULL");logfmt(")\n");a0->nobj=gi.invent;gi.invent=a0;a0->where=OBJ_INVENT;return a0;}
long (scatter)(coordxy a0,coordxy a1,int a2,unsigned int a3,struct obj * a4){logfmt("scatter(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");ptrlog(a4);logfmt(")\n");unlinkobj(a4);floorobj(a4);return a4->quan;}
char * (Tobjnam)(struct obj * a0,const char * a1){logfmt("Tobjnam(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");return namebuf;}
int (welded)(struct obj * a0){logfmt("welded(");ptrlog(a0);logfmt(")\n");return options[13];}
void (weldmsg)(struct obj * a0){logfmt("weldmsg(");ptrlog(a0);logfmt(")\n");}
void (setuwep)(struct obj * a0){logfmt("setuwep(");ptrlog(a0);logfmt(")\n");uwep=a0;}
void (setuswapwep)(struct obj * a0){logfmt("setuswapwep(");ptrlog(a0);logfmt(")\n");uswapwep=a0;}
void (setuqwep)(struct obj * a0){logfmt("setuqwep(");ptrlog(a0);logfmt(")\n");uquiver=a0;}
boolean (obj_is_burning)(struct obj * a0){logfmt("obj_is_burning(");ptrlog(a0);logfmt(")\n");return 0;}
boolean (snuff_lit)(struct obj * a0){logfmt("snuff_lit(");ptrlog(a0);logfmt(")\n");return 0;}
void (sellobj_state)(int a0){logfmt("sellobj_state(");logfmt("%lld",(long long)a0);logfmt(")\n");}
void (sellobj)(struct obj * a0,coordxy a1,coordxy a2){logfmt("sellobj(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");}
anything * (obj_to_any)(struct obj * a0){logfmt("obj_to_any(");ptrlog(a0);logfmt(")\n");objany.a_obj=a0;return &objany;}
long (stop_timer)(short a0,union any * a1){logfmt("stop_timer(");logfmt("%lld",(long long)a0);logfmt(",");ptrlog(a1);logfmt(")\n");return options[27];}
void (obfree)(struct obj * a0,struct obj * a1){logfmt("obfree(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");deleteobj(a0);}
void (useup)(struct obj * a0){logfmt("useup(");ptrlog(a0);logfmt(")\n");if(a0->quan>1)a0->quan--;else deleteobj(a0);}
boolean (obj_here)(struct obj * a0,coordxy a1,coordxy a2){logfmt("obj_here(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");for(struct obj*o=svl.level.objects[a1][a2];o;o=o->nexthere)if(o==a0)return TRUE;return FALSE;}
int (d)(int a0,int a1){int n=0;for(int i=0;i<a0;i++)n+=roll("d",a1)+1;return n;}
void (bot)(void){logfmt("bot(");logfmt(")\n");}
void (pick_pick)(struct obj * a0){logfmt("pick_pick(");ptrlog(a0);logfmt(")\n");}
struct monst * (get_mtraits)(struct obj * a0,boolean a1){logfmt("get_mtraits(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return options[19]?&mpool[0]:0;}
void (start_corpse_timeout)(struct obj * a0){logfmt("start_corpse_timeout(");ptrlog(a0);logfmt(")\n");}
void (start_glob_timeout)(struct obj * a0,long a1){logfmt("start_glob_timeout(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
char * (Doname2)(struct obj * a0){logfmt("Doname2(");ptrlog(a0);logfmt(")\n");return namebuf;}
struct monst * (shop_keeper)(char a0){logfmt("shop_keeper(");logfmt("%lld",(long long)a0);logfmt(")\n");return options[4]?&mpool[0]:0;}
long (stolen_value)(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logfmt("stolen_value(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(",");logfmt("%lld",(long long)a4);logfmt(")\n");return options[4]?options[26]:0;}
void (set_malign)(struct monst * a0){logfmt("set_malign(");ptrlog(a0);logfmt(")\n");}
int (canseemon)(struct monst * a0){logfmt("canseemon(");ptrlog(a0);logfmt(")\n");return !options[14];}
int (sensemon)(struct monst * a0){logfmt("sensemon(");ptrlog(a0);logfmt(")\n");return options[15];}
char * (Monnam)(struct monst * a0){logfmt("Monnam(");ptrlog(a0);logfmt(")\n");return namebuf;}
struct monst * (christen_monst)(struct monst * a0,const char * a1){logfmt("christen_monst(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");return a0;}
void (more_experienced)(int a0,int a1){logfmt("more_experienced(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
void (newexplevel)(void){logfmt("newexplevel(");logfmt(")\n");}
char * (rndmonnam)(char * a0){logfmt("rndmonnam(");logfmt("%s",a0?a0:"NULL");logfmt(")\n");return namebuf;}
void (set_corpsenm)(struct obj * a0,int a1){logfmt("set_corpsenm(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");a0->corpsenm=a1;}
struct obj * (oname)(struct obj * a0,const char * a1,unsigned int a2){logfmt("oname(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return a0;}
void (update_inventory)(void){logfmt("update_inventory(");logfmt(")\n");}
boolean (chest_trap)(struct obj * a0,int a1,boolean a2){logfmt("chest_trap(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");return options[33];}
const char * (currency)(long a0){logfmt("currency(");logfmt("%lld",(long long)a0);logfmt(")\n");return namebuf;}
char * (Ysimple_name2)(struct obj * a0){logfmt("Ysimple_name2(");ptrlog(a0);logfmt(")\n");return namebuf;}
void (container_contents)(struct obj * a0,boolean a1,boolean a2,boolean a3){logfmt("container_contents(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");logfmt("%lld",(long long)a3);logfmt(")\n");}
struct obj * (getobj)(const char * a0,int (*a1)(struct obj *),unsigned int a2){logfmt("getobj(");logfmt("%s",a0?a0:"NULL");logfmt(",");fpidentity((uintptr_t)a1);logfmt(",");logfmt("%lld",(long long)a2);logfmt(")\n");int code=a1(options[31]?0:&opool[0]);logfmt("getobj.callback=%d\n",code);return options[31]?0:&opool[0];}
struct obj * (unsplitobj)(struct obj * a0){logfmt("unsplitobj(");ptrlog(a0);logfmt(")\n");for(int i=0;i<no;i++)if(opool[i].o_id==svc.context.objsplit.parent_oid){opool[i].quan+=a0->quan;deleteobj(a0);svc.context.objsplit.parent_oid=svc.context.objsplit.child_oid=0;return &opool[i];}return 0;}
int (askchain)(struct obj ** a0,const char * a1,int a2,int (*a3)(struct obj *),int (*a4)(struct obj *),int a5,const char * a6){logfmt("askchain(");logfmt("OBJ**:");ptrlog(*a0);logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(",");logfmt("%lld",(long long)a2);logfmt(",");fpidentity((uintptr_t)a3);logfmt(",");fpidentity((uintptr_t)a4);logfmt(",");logfmt("%lld",(long long)a5);logfmt(",");logfmt("%s",a6?a6:"NULL");logfmt(")\n");int n=0;struct obj*o=*a0;while(o){struct obj*next=o->nobj;if(!a4||a4(o)){int v=a3(o);if(v<0)break;n+=v;}o=next;}return n;}
char * (vtense)(const char * a0,const char * a1){logfmt("vtense(");logfmt("%s",a0?a0:"NULL");logfmt(",");logfmt("%s",a1?a1:"NULL");logfmt(")\n");return(char*)a1;}
const char * (surface)(coordxy a0,coordxy a1){logfmt("surface(");logfmt("%lld",(long long)a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");return namebuf;}
void (consume_obj_charge)(struct obj * a0,boolean a1){logfmt("consume_obj_charge(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");if(a0->spe)a0->spe--;}
int (tiphat)(void){logfmt("tiphat(");logfmt(")\n");return 0;}
void (hitfloor)(struct obj * a0,boolean a1){logfmt("hitfloor(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");floorobj(a0);}
void (doaltarobj)(struct obj * a0){logfmt("doaltarobj(");ptrlog(a0);logfmt(")\n");}
void (dropy)(struct obj * a0){logfmt("dropy(");ptrlog(a0);logfmt(")\n");floorobj(a0);}
int (bagotricks)(struct obj * a0,boolean a1,int * a2){logfmt("bagotricks(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");ptrlog(a2);logfmt(")\n");return 0;}
int (hornoplenty)(struct obj * a0,boolean a1,struct obj * a2){logfmt("hornoplenty(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(",");ptrlog(a2);logfmt(")\n");return options[34];}
void (check_unpaid_usage)(struct obj * a0,boolean a1){logfmt("check_unpaid_usage(");ptrlog(a0);logfmt(",");logfmt("%lld",(long long)a1);logfmt(")\n");}
void (subfrombill)(struct obj * a0,struct monst * a1){logfmt("subfrombill(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");}
char * (Shk_Your)(char * a0,struct obj * a1){logfmt("Shk_Your(");logfmt("OUT:char256");logfmt(",");ptrlog(a1);logfmt(")\n");strcpy(a0,"Your ");return a0;}
char*ansimpleoname(struct obj*o){logfmt("ansimpleoname\n");return namebuf;}
char*Yname2(struct obj*o){logfmt("Yname2\n");return namebuf;}
char*yname(struct obj*o){logfmt("yname\n");return namebuf;}
int doforce(void){logfmt("doforce\n");return ECMD_TIME;}
void Norep(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("Norep:%s\n",b);}
void There(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("There:%s\n",b);}
void You(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You:%s\n",b);}
void You_cant(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You_cant:%s\n",b);}
void Your(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("Your:%s\n",b);}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("impossible:%s\n",b);}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("panic:%s\n",b);longjmp(panicframe,1);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline:%s\n",b);}
void pline_The(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline_The:%s\n",b);}
void urgent_pline(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("urgent_pline:%s\n",b);}
void verbalize(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("verbalize:%s\n",b);}
void livelog_printf(long flags,const char*fmt,...){va_list ap;va_start(ap,fmt);char b[4096];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("livelog[%ld]:%s\n",flags,b);}
#ifndef HYBRID_PICKUP
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/pickup.c"
#endif
uintptr_t probe_identity(int i){switch(i){
case 0:return(uintptr_t)(teleport_pickup_all_but_uchain);
case 1:return(uintptr_t)(allow_all);
case 2:return(uintptr_t)(allow_category);
case 3:return(uintptr_t)(ck_bag);
case 4:return(uintptr_t)(teleport_pickup_in_container);
case 5:return(uintptr_t)(teleport_pickup_n_or_more);
case 6:return(uintptr_t)(teleport_pickup_out_container);
case 7:return(uintptr_t)(teleport_pickup_stash_ok);
case 8:return(uintptr_t)(teleport_pickup_tip_ok);
case 9:return(uintptr_t)(Yname2);
case 10:return(uintptr_t)(Ysimple_name2);
case 11:return(uintptr_t)(ansimpleoname);
case 12:return(uintptr_t)(doforce);
case 13:return(uintptr_t)(doname);
case 14:return(uintptr_t)(is_worn);
case 15:return(uintptr_t)(yname);
case 16:return(uintptr_t)(ysimple_name);
default:abort();}}
static void fpidentity(uintptr_t p){if(!p){logfmt("0");return;}
if(p==(uintptr_t)(teleport_pickup_all_but_uchain)){logfmt("all_but_uchain");return;}
if(p==(uintptr_t)(allow_all)){logfmt("allow_all");return;}
if(p==(uintptr_t)(allow_category)){logfmt("allow_category");return;}
if(p==(uintptr_t)(ck_bag)){logfmt("ck_bag");return;}
if(p==(uintptr_t)(teleport_pickup_in_container)){logfmt("in_container");return;}
if(p==(uintptr_t)(teleport_pickup_n_or_more)){logfmt("n_or_more");return;}
if(p==(uintptr_t)(teleport_pickup_out_container)){logfmt("out_container");return;}
if(p==(uintptr_t)(teleport_pickup_stash_ok)){logfmt("stash_ok");return;}
if(p==(uintptr_t)(teleport_pickup_tip_ok)){logfmt("tip_ok");return;}
if(p==(uintptr_t)(Yname2)){logfmt("Yname2");return;}
if(p==(uintptr_t)(Ysimple_name2)){logfmt("Ysimple_name2");return;}
if(p==(uintptr_t)(ansimpleoname)){logfmt("ansimpleoname");return;}
if(p==(uintptr_t)(doforce)){logfmt("doforce");return;}
if(p==(uintptr_t)(doname)){logfmt("doname");return;}
if(p==(uintptr_t)(is_worn)){logfmt("is_worn");return;}
if(p==(uintptr_t)(yname)){logfmt("yname");return;}
if(p==(uintptr_t)(ysimple_name)){logfmt("ysimple_name");return;}
logfmt("UNKNOWN_FUNCTION:%llu",(unsigned long long)p);}
int probe_queue_count(void){return nq;}int probe_queue_identity(int i){for(int j=0;j<17;j++)if((uintptr_t)queue[i]==probe_identity(j))return j;return-1;}int probe_queue_run(int i){return queue[i]();}
#ifndef HYBRID_PICKUP
#undef teleport_pickup_all_but_uchain
boolean teleport_pickup_all_but_uchain(struct obj * a0){return (all_but_uchain)(a0);}
#undef teleport_pickup_in_container
int teleport_pickup_in_container(struct obj * a0){return (in_container)(a0);}
#undef teleport_pickup_n_or_more
boolean teleport_pickup_n_or_more(struct obj * a0){return (n_or_more)(a0);}
#undef teleport_pickup_out_container
int teleport_pickup_out_container(struct obj * a0){return (out_container)(a0);}
#undef teleport_pickup_stash_ok
int teleport_pickup_stash_ok(struct obj * a0){return (stash_ok)(a0);}
#undef teleport_pickup_tip_ok
int teleport_pickup_tip_ok(struct obj * a0){return (tip_ok)(a0);}
#endif
__attribute__((noinline))static void probe_poison(void){volatile unsigned char b[65536];for(int i=0;i<sizeof b;i++)b[i]=0;}
int64_t probe_action(int i,int64_t a0,int64_t a1,int64_t a2,int64_t a3,int64_t a4,int64_t a5,int64_t a6,int64_t a7,int64_t a8,int64_t a9){probe_poison();errorcode=0;int jump=setjmp(panicframe);if(jump){errorcode=jump;return-999;}switch(i){
case 0:(teleport_pickup_simple_look)((struct obj *)a0,(boolean)a1);return 0;
case 1:return(int64_t)(collect_obj_classes)((char *)a0,(struct obj *)a1,(boolean)a2,(boolean (*)(struct obj *))a3,(int *)a4);
case 2:return(int64_t)(teleport_pickup_query_classes)((char *)a0,(boolean *)a1,(boolean *)a2,(const char *)a3,(struct obj *)a4,(boolean)a5,(int *)a6);
case 3:return(int64_t)(u_safe_from_fatal_corpse)((struct obj *)a0,(int)a1);
case 4:return(int64_t)(teleport_pickup_fatal_corpse_mistake)((struct obj *)a0,(boolean)a1);
case 5:return(int64_t)(rider_corpse_revival)((struct obj *)a0,(boolean)a1);
case 6:(force_decor)((boolean)a0);return 0;
case 7:(deferred_decor)((boolean)a0);return 0;
case 8:return(int64_t)(teleport_pickup_describe_decor)();
case 9:(teleport_pickup_check_here)((boolean)a0);return 0;
case 10:return(int64_t)(teleport_pickup_n_or_more)((struct obj *)a0);
case 11:return(int64_t)(menu_class_present)((int)a0);
case 12:(add_valid_menu_class)((int)a0);return 0;
case 13:return(int64_t)(teleport_pickup_all_but_uchain)((struct obj *)a0);
case 14:return(int64_t)(allow_all)((struct obj *)a0);
case 15:return(int64_t)(allow_category)((struct obj *)a0);
case 16:return(int64_t)(is_worn_by_type)((struct obj *)a0);
case 17:(reset_justpicked)((struct obj *)a0);return 0;
case 18:return(int64_t)(count_justpicked)((struct obj *)a0);
case 19:return(int64_t)(find_justpicked)((struct obj *)a0);
case 20:return(int64_t)(pickup)((int)a0);
case 21:return(int64_t)(check_autopickup_exceptions)((struct obj *)a0);
case 22:return(int64_t)(autopick_testobj)((struct obj *)a0,(boolean)a1);
case 23:return(int64_t)(teleport_pickup_autopick)((struct obj *)a0,(int)a1,(menu_item **)a2);
case 24:return(int64_t)(query_objlist)((const char *)a0,(struct obj **)a1,(int)a2,(menu_item **)a3,(int)a4,(boolean (*)(struct obj *))a5);
case 25:return(int64_t)(query_category)((const char *)a0,(struct obj *)a1,(int)a2,(menu_item **)a3,(int)a4);
case 26:return(int64_t)(teleport_pickup_count_categories)((struct obj *)a0,(int)a1);
case 27:return(int64_t)(teleport_pickup_delta_cwt)((struct obj *)a0,(struct obj *)a1);
case 28:return(int64_t)(teleport_pickup_carry_count)((struct obj *)a0,(struct obj *)a1,(long)a2,(boolean)a3,(int *)a4,(int *)a5);
case 29:return(int64_t)(teleport_pickup_lift_object)((struct obj *)a0,(struct obj *)a1,(long *)a2,(boolean)a3);
case 30:return(int64_t)(pickup_object)((struct obj *)a0,(long)a1,(boolean)a2);
case 31:return(int64_t)(pick_obj)((struct obj *)a0);
case 32:(teleport_pickup_pickup_prinv)((struct obj *)a0,(long)a1,(const char *)a2);return 0;
case 33:(encumber_msg)();return 0;
case 34:return(int64_t)(container_at)((coordxy)a0,(coordxy)a1,(boolean)a2);
case 35:return(int64_t)(teleport_pickup_able_to_loot)((coordxy)a0,(coordxy)a1,(boolean)a2);
case 36:return(int64_t)(teleport_pickup_mon_beside)((coordxy)a0,(coordxy)a1);
case 37:return(int64_t)(teleport_pickup_do_loot_cont)((struct obj **)a0,(int)a1,(int)a2);
case 38:return(int64_t)(doloot)();
case 39:return(int64_t)(teleport_pickup_doloot_core)();
case 40:return(int64_t)(teleport_pickup_reverse_loot)();
case 41:return(int64_t)(loot_mon)((struct monst *)a0,(int *)a1,(boolean *)a2);
case 42:return(int64_t)(teleport_pickup_mbag_explodes)((struct obj *)a0,(int)a1);
case 43:return(int64_t)(teleport_pickup_is_boh_item_gone)();
case 44:(teleport_pickup_do_boh_explosion)((struct obj *)a0,(boolean)a1);return 0;
case 45:return(int64_t)(teleport_pickup_boh_loss)((struct obj *)a0,(boolean)a1);
case 46:return(int64_t)(teleport_pickup_in_container)((struct obj *)a0);
case 47:return(int64_t)(ck_bag)((struct obj *)a0);
case 48:return(int64_t)(teleport_pickup_out_container)((struct obj *)a0);
case 49:(removed_from_icebox)((struct obj *)a0);return 0;
case 50:return(int64_t)(teleport_pickup_mbag_item_gone)((boolean)a0,(struct obj *)a1,(boolean)a2);
case 51:(observe_quantum_cat)((struct obj *)a0,(boolean)a1,(boolean)a2);return 0;
case 52:return(int64_t)(container_gone)((int (*)(struct obj *))a0);
case 53:(teleport_pickup_explain_container_prompt)((boolean)a0);return 0;
case 54:return(int64_t)(u_handsy)();
case 55:return(int64_t)(teleport_pickup_stash_ok)((struct obj *)a0);
case 56:return(int64_t)(use_container)((struct obj **)a0,(boolean)a1,(boolean)a2);
case 57:return(int64_t)(teleport_pickup_traditional_loot)((boolean)a0);
case 58:return(int64_t)(teleport_pickup_menu_loot)((int)a0,(boolean)a1);
case 59:return(int64_t)(teleport_pickup_in_or_out_menu)((const char *)a0,(struct obj *)a1,(boolean)a2,(boolean)a3,(boolean)a4,(boolean)a5);
case 60:return(int64_t)(teleport_pickup_tip_ok)((struct obj *)a0);
case 61:return(int64_t)(teleport_pickup_choose_tip_container_menu)();
case 62:return(int64_t)(dotip)();
case 63:(teleport_pickup_tipcontainer)((struct obj *)a0);return 0;
case 64:return(int64_t)(teleport_pickup_tipcontainer_gettarget)((struct obj *)a0,(boolean *)a1);
case 65:return(int64_t)(teleport_pickup_tipcontainer_checks)((struct obj *)a0,(struct obj *)a1,(boolean)a2);
default:abort();}}

size_t probe_extra_offset(int i){return i?offsetof(struct mextra,eshk):offsetof(struct monst,mextra);}
const char*probe_trace(void){return tracebuf;}void probe_clear(void){traceused=0;tracebuf[0]=0;}int probe_draws(void){return draws;}int probe_error(void){return errorcode;}int probe_errno(void){return errno;}
void probe_seed(uint32_t n){seed=n;draws=0;}void probe_option(int i,int v){options[i]=v;}
void probe_input(const char*p){if(ninput==32)abort();strncpy(input[ninput++],p,255);}void probe_answer(int n){if(nanswer==128)abort();answers[nanswer++]=n;}void probe_choice(int w,int index,int count,int kind){choices[w]=index;choicecount[w]=count;menukind[w]=kind;}
void probe_choice2(int w,int index,int count){choices2[w]=index;choicecount2[w]=count;}void probe_choicewide(int w,int64_t n){choicecount[w]=n;}
void*probe_pointer(int i){switch(i){

case 0:return(void*)&scratch;
case 1:return(void*)&opool;
case 2:return(void*)&mpool;
case 3:return(void*)&tpool;
case 4:return(void*)&exceptions;
case 5:return(void*)&mextra;
case 6:return(void*)&eshk;
case 7:return(void*)&roomstr;
case 8:return(void*)&feature;
case 9:return(void*)&input;
case 10:return(void*)&objany;
case 11:return(void*)&namebuf;
case 12:return(void*)&pronoun;
case 13:return(void*)&eventbytes;
case 14:return(void*)&borrowedbytes;
default:abort();}}
void*probe_grid(void){return levl;}
size_t probe_region_size(int i){switch(i){
case 0:return sizeof scratch;
case 1:return sizeof opool;
case 2:return sizeof mpool;
case 3:return sizeof tpool;
case 4:return sizeof exceptions;
case 5:return sizeof mextra;
case 6:return sizeof eshk;
case 7:return sizeof roomstr;
case 8:return sizeof feature;
case 9:return sizeof input;
case 10:return sizeof objany;
case 11:return sizeof namebuf;
case 12:return sizeof pronoun;
case 13:return sizeof eventbytes;
case 14:return sizeof borrowedbytes;
default:abort();}}

int probe_count(void){return nalloc;}void*probe_alloc_pointer(int i){return allocations[i];}size_t probe_alloc_size(int i){return allocsizes[i];}int probe_alloc_kind(int i){return allockind[i];}int probe_alloc_live(int i){return alloclive[i];}void*probe_growth(void){return __real_malloc(50000000);}
int probe_borrow_kind(int i){return borrowkind[i];}int probe_borrow_count(void){return nborrow;}uintptr_t probe_borrow_pointer(int i){return borrowed[i];}int probe_event_count(void){return nevents;}int probe_event_kind(int i){return eventkind[i];}void*probe_newobj(int typ){return fixture_newobj(typ);}void probe_floor(struct obj*o){unlinkobj(o);floorobj(o);}void probe_inventory(struct obj*o){unlinkobj(o);o->where=OBJ_INVENT;o->nobj=gi.invent;gi.invent=o;}
void probe_reset(void){for(int i=0;i<nalloc;i++)if(alloclive[i])__real_free(allocations[i]);nalloc=0;memset(alloclive,0,sizeof alloclive);memset(allockind,0,sizeof allockind);memset(options,0,sizeof options);memset(opool,0,sizeof opool);memset(mpool,0,sizeof mpool);memset(tpool,0,sizeof tpool);memset(exceptions,0,sizeof exceptions);memset(&mextra,0,sizeof mextra);memset(&eshk,0,sizeof eshk);memset(scratch,0,sizeof scratch);memset(input,0,sizeof input);memset(eventbytes,0,sizeof eventbytes);memset(eventkind,0,sizeof eventkind);memset(menuids,0,sizeof menuids);memset(menun,0,sizeof menun);memset(menuevent,0,sizeof menuevent);memset(menukind,0,sizeof menukind);memset(borrowedbytes,0,sizeof borrowedbytes);memset(borrowkind,0,sizeof borrowkind);memset(choices2,0xFF,sizeof choices2);memset(choicecount2,0,sizeof choicecount2);memset(choices,0xFF,sizeof choices);memset(choicecount,0,sizeof choicecount);no=nm=nborrow=0;

memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gi,0,sizeof gi);
memset((void*)&uarmg,0,sizeof uarmg);
memset((void*)&u,0,sizeof u);
memset((void*)&gy,0,sizeof gy);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&gd,0,sizeof gd);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&svl,0,sizeof svl);
memset((void*)&flags,0,sizeof flags);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&svc,0,sizeof svc);
memset((void*)&gv,0,sizeof gv);
memset((void*)&gc,0,sizeof gc);
memset((void*)&gb,0,sizeof gb);
memset((void*)&gs,0,sizeof gs);
memset((void*)&gp,0,sizeof gp);
memset((void*)&gu,0,sizeof gu);
memset((void*)&gm,0,sizeof gm);
memset((void*)&yn_number,0,sizeof yn_number);
memset((void*)&ga,0,sizeof ga);
memset((void*)&cg,0,sizeof cg);
memset((void*)&gt,0,sizeof gt);
memset((void*)&go,0,sizeof go);
memset((void*)&objects,0,sizeof objects);
memset((void*)&disp,0,sizeof disp);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&uball,0,sizeof uball);
memset((void*)&gl,0,sizeof gl);
memset((void*)&uswapwep,0,sizeof uswapwep);
memset((void*)&uquiver,0,sizeof uquiver);
memset((void*)&svm,0,sizeof svm);
memset((void*)&gn,0,sizeof gn);
memset((void*)&uarmh,0,sizeof uarmh);

for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_class=WEAPON_CLASS;objects[i].oc_name_known=1;objects[i].oc_weight=2;}objects[GOLD_PIECE].oc_class=COIN_CLASS;objects[CORPSE].oc_class=FOOD_CLASS;objects[STATUE].oc_class=ROCK_CLASS;objects[BAG_OF_HOLDING].oc_class=TOOL_CLASS;objects[ICE_BOX].oc_class=TOOL_CLASS;objects[SACK].oc_class=TOOL_CLASS;objects[CHEST].oc_class=TOOL_CLASS;objects[LARGE_BOX].oc_class=TOOL_CLASS;objects[BAG_OF_TRICKS].oc_class=TOOL_CLASS;objects[HORN_OF_PLENTY].oc_class=TOOL_CLASS;objects[SADDLE].oc_class=TOOL_CLASS;objects[LEASH].oc_class=TOOL_CLASS;objects[WAN_CANCELLATION].oc_class=WAND_CLASS;objects[LOADSTONE].oc_class=GEM_CLASS;objects[BOULDER].oc_class=ROCK_CLASS;
struct obj*o=fixture_newobj(DAGGER);o->quan=4;o->owt=8;o->where=OBJ_INVENT;o->dknown=o->bknown=1;o->ox=40;o->oy=10;gi.invent=o;
o=fixture_newobj(SACK);o->owt=2;o->ox=40;o->oy=10;
nm=1;mpool[0].data=&mons[PM_HUMAN];mpool[0].m_id=1;mpool[0].mx=41;mpool[0].my=10;mpool[0].mhp=20;mpool[0].mcanmove=1;mpool[0].mextra=&mextra;mextra.eshk=&eshk;tpool[0].tx=40;tpool[0].ty=10;tpool[0].ttyp=PIT;
u.ux=40;u.uy=10;u.uz.dlevel=3;u.uhp=u.uhpmax=50;u.ulevel=5;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mx=40;gy.youmonst.my=10;
for(int i=1;i<MAXOCLASSES;i++)flags.inv_order[i-1]=i;flags.inv_order[MAXOCLASSES-1]=0;
windowprocs.win_create_nhwindow=win_create;windowprocs.win_start_menu=win_start;windowprocs.win_end_menu=win_end;windowprocs.win_destroy_nhwindow=win_destroy;windowprocs.win_display_nhwindow=win_display;windowprocs.win_putstr=win_put;
for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;
seed=1;draws=callerline=errorcode=ninput=nextinput=nanswer=nextanswer=nq=nevents=nw=activewin=0;callerfile=callerfn=0;errno=0;strcpy(namebuf,"fixture");strcpy(feature,"fountain");roomstr[0]=0;objany.a_void=0;(add_valid_menu_class)(0);probe_clear();}
size_t probe_global_size(int i){switch(i){

case 0:return sizeof windowprocs;
case 1:return sizeof def_oc_syms;
case 2:return sizeof gi;
case 3:return sizeof uarmg;
case 4:return sizeof mons;
case 5:return sizeof u;
case 6:return sizeof gy;
case 7:return sizeof WIN_MESSAGE;
case 8:return sizeof gd;
case 9:return sizeof iflags;
case 10:return sizeof svl;
case 11:return sizeof flags;
case 12:return sizeof uchain;
case 13:return sizeof svc;
case 14:return sizeof gv;
case 15:return sizeof gc;
case 16:return sizeof gb;
case 17:return sizeof gs;
case 18:return sizeof gp;
case 19:return sizeof gu;
case 20:return sizeof gm;
case 21:return sizeof c_common_strings;
case 22:return sizeof ynaqchars;
case 23:return sizeof ynNaqchars;
case 24:return sizeof yn_number;
case 25:return sizeof ga;
case 26:return sizeof nul_glyphinfo;
case 27:return sizeof cg;
case 28:return sizeof gt;
case 29:return sizeof go;
case 30:return sizeof objects;
case 31:return sizeof ynqchars;
case 32:return sizeof disp;
case 33:return sizeof uwep;
case 34:return sizeof uball;
case 35:return sizeof gl;
case 36:return sizeof uswapwep;
case 37:return sizeof uquiver;
case 38:return sizeof svm;
case 39:return sizeof genders;
case 40:return sizeof gn;
case 41:return sizeof uarmh;
default:abort();}}
const void*probe_literal(int i){switch(i){
case 0:return(const void*)"";
case 1:return(const void*)"\033";
case 2:return(const void*)" ";
case 3:return(const void*)"    ";
case 4:return(const void*)"    (if no other choices are picked, 'a' is implied)";
case 5:return(const void*)"    (ignored unless some other choices are also picked)";
case 6:return(const void*)" (except gold)";
case 7:return(const void*)" : -- Look: examine contents";
case 8:return(const void*)" ? -- Help: display this text.";
case 9:return(const void*)" and gradually %s";
case 10:return(const void*)" and immediately %s away";
case 11:return(const void*)" any more";
case 12:return(const void*)" b -- Both: first take things out, then put things in";
case 13:return(const void*)" else";
case 14:return(const void*)" here, tip it?";
case 15:return(const void*)" i -- In: put things in";
case 16:return(const void*)" is empty.  Do what with it?";
case 17:return(const void*)" n ";
case 18:return(const void*)" n -- Next: loot next selected container";
case 19:return(const void*)" o -- Out: take things out";
case 20:return(const void*)" or ?";
case 21:return(const void*)" q -- Quit: finished";
case 22:return(const void*)" r -- Reversed: put things in, then take things out";
case 23:return(const void*)" s -- Stash: put one item in";
case 24:return(const void*)"%s";
case 25:return(const void*)"%s %s";
case 26:return(const void*)"%s %s ";
case 27:return(const void*)"%s %s %s, but %s%s%s%s.";
case 28:return(const void*)"%s %s disappear!";
case 29:return(const void*)"%s %s securely sealed.";
case 30:return(const void*)"%s %s to loot.";
case 31:return(const void*)"%s %s to the %s.";
case 32:return(const void*)"%s %s vanished!";
case 33:return(const void*)"%s %s%shere to loot.";
case 34:return(const void*)"%s Creatures";
case 35:return(const void*)"%s attached to your pet.";
case 36:return(const void*)"%s cannot be confined in such trappings.";
case 37:return(const void*)"%s inside the box is dead!";
case 38:return(const void*)"%s inside the box is still alive!";
case 39:return(const void*)"%s into %s.";
case 40:return(const void*)"%s is %sempty.";
case 41:return(const void*)"%s is empty.";
case 42:return(const void*)"%s is locked.";
case 43:return(const void*)"%s locked.";
case 44:return(const void*)"%s move a handspan with this load!";
case 45:return(const void*)"%s out%c";
case 46:return(const void*)"%s to loot on the %s.";
case 47:return(const void*)"%s under your heavy load.  Movement is very hard.";
case 48:return(const void*)"%s under your load.  Movement is still very hard.";
case 49:return(const void*)"%s what type of objects?";
case 50:return(const void*)"%s what?";
case 51:return(const void*)"%s%c";
case 52:return(const void*)"%s%s";
case 53:return(const void*)"%s.";
case 54:return(const void*)"%sbox is now empty.";
case 55:return(const void*)"%sput in, then take out";
case 56:return(const void*)"%stake out, then put in";
case 57:return(const void*)"*pick_list != NULL";
case 58:return(const void*)".  Continue?";
case 59:return(const void*)":";
case 60:return(const void*)"<in> no gc.current_container?";
case 61:return(const void*)"<out> no gc.current_container?";
case 62:return(const void*)"?";
case 63:return(const void*)"All types";
case 64:return(const void*)"All worn and wielded types";
case 65:return(const void*)"An object spills";
case 66:return(const void*)"An object tumbles";
case 67:return(const void*)"As %s %s inside, you are blasted by a magical explosion!";
case 68:return(const void*)"As you put %s inside, you are blasted by a magical explosion!";
case 69:return(const void*)"At your %s, the corpse suddenly moves...";
case 70:return(const void*)"Auto-select every item being worn or wielded";
case 71:return(const void*)"Auto-select every relevant item";
case 72:return(const void*)"Being confused, you find nothing to loot.";
case 73:return(const void*)"Container actions:";
case 74:return(const void*)"Do what with ";
case 75:return(const void*)"Do you want to remove the saddle from %s?";
case 76:return(const void*)"Engulfed";
case 77:return(const void*)"Hmmm, %s turns out to be locked.";
case 78:return(const void*)"Invalid loot location";
case 79:return(const void*)"It develops a huge set of teeth and bites you!";
case 80:return(const void*)"Items known to be Blessed";
case 81:return(const void*)"Items known to be Cursed";
case 82:return(const void*)"Items known to be Uncursed";
case 83:return(const void*)"Items of unknown Bless/Curse status";
case 84:return(const void*)"Items you just picked up";
case 85:return(const void*)"Just picked up: %s";
case 86:return(const void*)"Look inside %s";
case 87:return(const void*)"Loot in what direction?";
case 88:return(const void*)"Loot which containers?";
case 89:return(const void*)"No relevant items selected.";
case 90:return(const void*)"Nothing interesting happens.";
case 91:return(const void*)"Objects spill";
case 92:return(const void*)"Objects tumble";
case 93:return(const void*)"Ok, now there is loot here.";
case 94:return(const void*)"Pick %d of what?";
case 95:return(const void*)"Pick up ";
case 96:return(const void*)"Pick up what?";
case 97:return(const void*)"Put in";
case 98:return(const void*)"Really autoselect All?";
case 99:return(const void*)"Schroedinger's Cat";
case 100:return(const void*)"Some %s %s onto the %s%s.";
case 101:return(const void*)"Swallowed";
case 102:return(const void*)"Take out";
case 103:return(const void*)"Thank you for your contribution to reduce the debt.";
case 104:return(const void*)"That would be an interesting topological exercise.";
case 105:return(const void*)"The exchequer accepts your contribution.";
case 106:return(const void*)"There is ";
case 107:return(const void*)"There is %s here.";
case 108:return(const void*)"This";
case 109:return(const void*)"Tip which container?";
case 110:return(const void*)"Touching %s is a fatal mistake.";
case 111:return(const void*)"Unpaid items";
case 112:return(const void*)"Unpaid items already used up";
case 113:return(const void*)"What kinds of thing do you want to %s? [%s]";
case 114:return(const void*)"Where to tip the contents of %s";
case 115:return(const void*)"Without a free %s, you cannot loot anything.";
case 116:return(const void*)"Without limbs, you cannot %s anything.";
case 117:return(const void*)"You can't tip %s while carrying so much.";
case 118:return(const void*)"You cannot %s %s you are wearing.";
case 119:return(const void*)"You drop %s!";
case 120:return(const void*)"You find old loot:";
case 121:return(const void*)"You have a little trouble";
case 122:return(const void*)"You have extreme difficulty";
case 123:return(const void*)"You have much trouble";
case 124:return(const void*)"You have trouble";
case 125:return(const void*)"_:abcdenq";
case 126:return(const void*)"_:oibrsnq";
case 127:return(const void*)"a container";
case 128:return(const void*)"acquire";
case 129:return(const void*)"another";
case 130:return(const void*)"are";
case 131:return(const void*)"are %s objects here.";
case 132:return(const void*)"are carrying too much stuff to pick up %s %s.";
case 133:return(const void*)"are no %c's %s.";
case 134:return(const void*)"are physically incapable of picking anything up.";
case 135:return(const void*)"attempted acquisition";
case 136:return(const void*)"b";
case 137:return(const void*)"both reversed; ";
case 138:return(const void*)"both; ";
case 139:return(const void*)"burn";
case 140:return(const void*)"can barely";
case 141:return(const void*)"can only %s %s of the %s %s.";
case 142:return(const void*)"can't even";
case 143:return(const void*)"can't.  The saddle seems to be stuck to %s.";
case 144:return(const void*)"cannot %s things that are deep in the %s.";
case 145:return(const void*)"cannot fit %s into %s.";
case 146:return(const void*)"cannot get your %s around this %s.";
case 147:return(const void*)"carefully open %s...";
case 148:return(const void*)"carnivorous bag";
case 149:return(const void*)"carry";
case 150:return(const void*)"container";
case 151:return(const void*)"crumbs";
case 152:return(const void*)"delta_cwt: obj not inside container?";
case 153:return(const void*)"dissipate";
case 154:return(const void*)"do nothing";
case 155:return(const void*)"do that without limbs.";
case 156:return(const void*)"do_loot_cont";
case 157:return(const void*)"doloot_core";
case 158:return(const void*)"don't find anything";
case 159:return(const void*)"don't have anything%s to %s.";
case 160:return(const void*)"done";
case 161:return(const void*)"doorway";
case 162:return(const void*)"drop";
case 163:return(const void*)"drop %s.";
case 164:return(const void*)"else ";
case 165:return(const void*)"even one ";
case 166:return(const void*)"grease";
case 167:return(const void*)"have";
case 168:return(const void*)"have no %c's.";
case 169:return(const void*)"have no free %s.";
case 170:return(const void*)"have no hands!";
case 171:return(const void*)"have to be at a container to loot it.";
case 172:return(const void*)"here";
case 173:return(const void*)"housecat";
case 174:return(const void*)"i";
case 175:return(const void*)"in %s";
case 176:return(const void*)"in_container";
case 177:return(const void*)"in_container:  bag not found.";
case 178:return(const void*)"inside";
case 179:return(const void*)"is too heavy for you to ";
case 180:return(const void*)"is_boh_item_gone";
case 181:return(const void*)"it";
case 182:return(const void*)"it ";
case 183:return(const void*)"just blew up %s bag of holding";
case 184:return(const void*)"just blew up %s bag of holding via tipping";
case 185:return(const void*)"knapsack cannot accommodate any more items%s.";
case 186:return(const void*)"lava";
case 187:return(const void*)"lift";
case 188:return(const void*)"lifting";
case 189:return(const void*)"loot";
case 190:return(const void*)"loot anything %sthere with %s in the way.";
case 191:return(const void*)"loot next container";
case 192:return(const void*)"loot_mon";
case 193:return(const void*)"lying here";
case 194:return(const void*)"magical explosion";
case 195:return(const void*)"many";
case 196:return(const void*)"mbag_explodes";
case 197:return(const void*)"menu_loot";
case 198:return(const void*)"more";
case 199:return(const void*)"movements are now unencumbered.";
case 200:return(const void*)"movements are only slowed slightly by your load.";
case 201:return(const void*)"movements are slowed slightly because of your load.";
case 202:return(const void*)"must be kidding.";
case 203:return(const void*)"must put it down to unlock.";
case 204:return(const void*)"n";
case 205:return(const void*)"need to dig up the grave to effectively loot it...";
case 206:return(const void*)"notice";
case 207:return(const void*)"now ";
case 208:return(const void*)"o";
case 209:return(const void*)"observe_quantum_cat";
case 210:return(const void*)"oil";
case 211:return(const void*)"on the floor";
case 212:return(const void*)"one";
case 213:return(const void*)"open %s...";
case 214:return(const void*)"open door";
case 215:return(const void*)"opening a container";
case 216:return(const void*)"otmp != 0";
case 217:return(const void*)"owe %ld %s for lost merchandise.";
case 218:return(const void*)"pick";
case 219:return(const void*)"pick %s up.";
case 220:return(const void*)"pick up";
case 221:return(const void*)"pick yourself up!";
case 222:return(const void*)"pickup.c";
case 223:return(const void*)"pickup_object: count %ld > quan %ld?";
case 224:return(const void*)"pool of water";
case 225:return(const void*)"put %s in";
case 226:return(const void*)"put %s into %s.";
case 227:return(const void*)"put in";
case 228:return(const void*)"q";
case 229:return(const void*)"query_category";
case 230:return(const void*)"query_category: no single object match";
case 231:return(const void*)"query_category: too many categories";
case 232:return(const void*)"raise";
case 233:return(const void*)"rebalance your load.  Movement is difficult.";
case 234:return(const void*)"rebalance your load.  Movement is still difficult.";
case 235:return(const void*)"refrigerate";
case 236:return(const void*)"removing";
case 237:return(const void*)"reverse_loot";
case 238:return(const void*)"rs";
case 239:return(const void*)"s";
case 240:return(const void*)"scroll%s %s to dust as you %s %s up.";
case 241:return(const void*)"see";
case 242:return(const void*)"several";
case 243:return(const void*)"simple_look(null)";
case 244:return(const void*)"some";
case 245:return(const void*)"spill";
case 246:return(const void*)"stagger";
case 247:return(const void*)"stash";
case 248:return(const void*)"stash one item into %s";
case 249:return(const void*)"stone%s won't leave your person.";
case 250:return(const void*)"swamp";
case 251:return(const void*)"t";
case 252:return(const void*)"take %s off of %s.";
case 253:return(const void*)"take %s out";
case 254:return(const void*)"take out";
case 255:return(const void*)"them";
case 256:return(const void*)"there";
case 257:return(const void*)"think %s brushed your %s.";
case 258:return(const void*)"tip";
case 259:return(const void*)"tip something being carried";
case 260:return(const void*)"tipcontainer";
case 261:return(const void*)"tipping a container";
case 262:return(const void*)"touch";
case 263:return(const void*)"tumble";
case 264:return(const void*)"turn";
case 265:return(const void*)"uBUCXP";
case 266:return(const void*)"venom";
case 267:return(const void*)"water";
case 268:return(const void*)"wax";
case 269:return(const void*)"you cannot ";
default:abort();}}
const void*probe_prefix(int i){
#ifdef HYBRID_PICKUP
extern void*teleport_pickup_storage(int);return teleport_pickup_storage(i);
#else
switch(i){
case 0:return slightloadpfx;
case 1:return moderateloadpfx;
case 2:return nearloadpfx;
case 3:return overloadpfx;
default:abort();}
#endif
}
int64_t probe_constant(int i){switch(i){
case 0:return(int64_t)(ALL_TYPES);
case 1:return(int64_t)(ALTAR);
case 2:return(int64_t)(AUTOSELECT_SINGLE);
case 3:return(int64_t)(AUTOUNLOCK_APPLY_KEY);
case 4:return(int64_t)(AUTOUNLOCK_FORCE);
case 5:return(int64_t)(BAG_OF_HOLDING);
case 6:return(int64_t)(BAG_OF_TRICKS);
case 7:return(int64_t)(BILLED_TYPES);
case 8:return(int64_t)(BOULDER);
case 9:return(int64_t)(BUC_BLESSED);
case 10:return(int64_t)(BUC_CURSED);
case 11:return(int64_t)(BUC_UNCURSED);
case 12:return(int64_t)(BUC_UNKNOWN);
case 13:return(int64_t)(BY_NEXTHERE);
case 14:return(int64_t)(CHEST);
case 15:return(int64_t)(COIN_CLASS);
case 16:return(int64_t)(CORPSE);
case 17:return(int64_t)(DAGGER);
case 18:return(int64_t)(DOOR);
case 19:return(int64_t)(ECMD_CANCEL);
case 20:return(int64_t)(ECMD_OK);
case 21:return(int64_t)(ECMD_TIME);
case 22:return(int64_t)(FEEL_COCKATRICE);
case 23:return(int64_t)(FOOD_CLASS);
case 24:return(int64_t)(GOLD_PIECE);
case 25:return(int64_t)(GRAVE);
case 26:return(int64_t)(HORN_OF_PLENTY);
case 27:return(int64_t)(ICE);
case 28:return(int64_t)(ICE_BOX);
case 29:return(int64_t)(INCLUDE_HERO);
case 30:return(int64_t)(INVORDER_SORT);
case 31:return(int64_t)(JUSTPICKED);
case 32:return(int64_t)(LARGE_BOX);
case 33:return(int64_t)(LAVAPOOL);
case 34:return(int64_t)(LOADSTONE);
case 35:return(int64_t)(MENU_COMBINATION);
case 36:return(int64_t)(MENU_FULL);
case 37:return(int64_t)(MENU_PARTIAL);
case 38:return(int64_t)(MENU_TRADITIONAL);
case 39:return(int64_t)(MOAT);
case 40:return(int64_t)(OBJ_CONTAINED);
case 41:return(int64_t)(OBJ_FLOOR);
case 42:return(int64_t)(OBJ_FREE);
case 43:return(int64_t)(OBJ_INVENT);
case 44:return(int64_t)(OBJ_MINVENT);
case 45:return(int64_t)(PICK_ANY);
case 46:return(int64_t)(PICK_NONE);
case 47:return(int64_t)(PICK_ONE);
case 48:return(int64_t)(PIT);
case 49:return(int64_t)(PM_CLERIC);
case 50:return(int64_t)(PM_COCKATRICE);
case 51:return(int64_t)(PM_DEATH);
case 52:return(int64_t)(PM_HOUSECAT);
case 53:return(int64_t)(PM_HUMAN);
case 54:return(int64_t)(PM_ICE_TROLL);
case 55:return(int64_t)(PM_ORC);
case 56:return(int64_t)(POOL);
case 57:return(int64_t)(ROOM);
case 58:return(int64_t)(SACK);
case 59:return(int64_t)(SADDLE);
case 60:return(int64_t)(SIGNAL_ESCAPE);
case 61:return(int64_t)(SIGNAL_NOMENU);
case 62:return(int64_t)(STATUE);
case 63:return(int64_t)(THRONE);
case 64:return(int64_t)(TOOL_CLASS);
case 65:return(int64_t)(UNPAID_TYPES);
case 66:return(int64_t)(USE_INVLET);
case 67:return(int64_t)(WAN_CANCELLATION);
case 68:return(int64_t)(WEAPON_CLASS);
case 69:return(int64_t)(WORN_TYPES);
case 70:return(int64_t)(W_ARMOR);
case 71:return(int64_t)(W_SADDLE);
case 72:return(int64_t)(W_WEP);
default:abort();}}
