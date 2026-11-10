/* Controlled mainloop/startup dependencies; no original ALLMAIN body in hybrid. */
#include "hack.h"
#include "tu-allmain-layout.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <emscripten.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(u) u;
__typeof__(svc) svc;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(program_state) program_state;
__typeof__(disp) disp;
__typeof__(gd) gd;
__typeof__(gy) gy;
__typeof__(gw) gw;
__typeof__(svm) svm;
__typeof__(gh) gh;
__typeof__(gm) gm;
__typeof__(svl) svl;
__typeof__(go) go;
__typeof__(gc) gc;
__typeof__(gl) gl;
__typeof__(gu) gu;
__typeof__(urealtime) urealtime;
__typeof__(a11y) a11y;
__typeof__(svp) svp;
__typeof__(gi) gi;
__typeof__(gv) gv;
__typeof__(svd) svd;
winid WIN_MESSAGE,WIN_STATUS,WIN_MAP,WIN_INVEN;
__typeof__(windowprocs) windowprocs;
struct permonst mons[NUMMONS+1];
const struct Gender genders[]={{"male","he","him","his","Mal",ROLE_MALE},{"female","she","her","her","Fem",ROLE_FEMALE},{"neuter","it","it","its","Neu",ROLE_NEUTER}};
const char*const nhcb_name[]={"end_turn","enter_level","leave_level","end_turn"};int nhcb_counts[8];
static struct monst monsters[3];static s_level fixture_tutorial;static struct obj dummyobj;
static int opts[32],counts[256],rolls[4096],roll_pos,roll_count;static unsigned seed;static long clock_value;static void*growth;
static char tracebuf[1048576],snapshotbuf[262144],caller[128];
static const char *retstrings[]={"Greetings","wrong","human","Archeologist","Archeologistess"};
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
EM_JS(void,fixture_throw,(int reason),{throw new Error('ALLMAIN fixture exit '+reason);});
void panic(const char*f,...){logmsg("panic;");fixture_throw(99);__builtin_unreachable();}
void impossible(const char*f,...){logmsg("impossible:%s;",f);}
void nhassert_failed(const char*e,const char*f,int line){const char*p=strrchr(f,'/');logmsg("assert:%s:%s:%d;",e,p?p+1:f,line);fixture_throw(98);}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*f,int line,const char*fn){const char*p=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();seed=seed*1664525U+1013904223U;v=(unsigned)(roll_pos<roll_count?rolls[roll_pos]:seed)%n;roll_pos++;logmsg("rng:%d:%d@%s;",n,v,caller);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/allmain.c"
#else
extern void teleport_allmain_test_moveloop_preamble(boolean);
#define moveloop_preamble teleport_allmain_test_moveloop_preamble
extern void teleport_allmain_test_u_calc_moveamt(int);
#define u_calc_moveamt teleport_allmain_test_u_calc_moveamt
extern void teleport_allmain_test_maybe_generate_rnd_mon(void);
#define maybe_generate_rnd_mon teleport_allmain_test_maybe_generate_rnd_mon
extern void teleport_allmain_test_maybe_do_tutorial(void);
#define maybe_do_tutorial teleport_allmain_test_maybe_do_tutorial
extern void teleport_allmain_test_regen_pw(int);
#define regen_pw teleport_allmain_test_regen_pw
extern void teleport_allmain_test_regen_hp(int);
#define regen_hp teleport_allmain_test_regen_hp
extern void teleport_allmain_test_interrupt_multi(const char*);
#define interrupt_multi teleport_allmain_test_interrupt_multi
#endif
#include "../nethack-c/wasm/tu-fragments/allmain-support.c"
static void callback(void){if(opts[20]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}if(opts[21]){opts[21]=0;logmsg("reentry;");interrupt_multi("You feel full of energy.");}if(opts[23])fixture_throw(23);}
static void message(const char*tag,const char*f,va_list ap){logmsg("%s:",tag);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);logmsg(";");callback();}
void pline(const char*f,...){va_list ap;va_start(ap,f);message("pline",f,ap);va_end(ap);}
void urgent_pline(const char*f,...){va_list ap;va_start(ap,f);message("urgent_pline",f,ap);va_end(ap);}
void Norep(const char*f,...){va_list ap;va_start(ap,f);message("Norep",f,ap);va_end(ap);}
void You(const char*f,...){va_list ap;va_start(ap,f);message("You",f,ap);va_end(ap);}
void livelog_printf(long flags,const char*f,...){va_list ap;logmsg("live:%ld:",flags);va_start(ap,f);message("livelog",f,ap);va_end(ap);}
void done1(int sig){logmsg("done1:%d;",sig);fixture_throw(96);}
void(*teleport_native_signal(int sig,void(*f)(int)))(int){logmsg("signal:%d:%d;",sig,f==done1);return 0;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
static int fixture_occupation(void){logmsg("occupation;");callback();return opts[14];}
void lua_settop(lua_State * a0,int a1){counts[1]++;logmsg("lua_settop");logmsg(":p%d",a0!=0);logmsg(":%d",(int)a1);logmsg(";");callback();}
const char * lua_pushstring(lua_State * a0,const char * a1){counts[2]++;logmsg("lua_pushstring");logmsg(":p%d",a0!=0);logmsg(":%s",a1?a1:"<null>");logmsg(";");callback();return a1;}
int lua_getglobal(lua_State * a0,const char * a1){counts[3]++;logmsg("lua_getglobal");logmsg(":p%d",a0!=0);logmsg(":%s",a1?a1:"<null>");logmsg(";");callback();return 1;}
boolean next_to_u(void){counts[5]++;logmsg("next_to_u");logmsg(";");callback();return opts[12];}
void check_leash(coordxy a0,coordxy a1){counts[6]++;logmsg("check_leash");logmsg(":%d",(int)a0);logmsg(":%d",(int)a1);logmsg(";");callback();}
void init_artifacts(void){counts[7]++;logmsg("init_artifacts");logmsg(";");callback();}
void mkot_trap_warn(void){counts[8]++;logmsg("mkot_trap_warn");logmsg(";");callback();}
void change_luck(schar a0){counts[9]++;logmsg("change_luck");logmsg(":%d",(int)a0);logmsg(";");callback();}
void exerchk(void){counts[10]++;logmsg("exerchk");logmsg(";");callback();}
void bot(void){counts[11]++;logmsg("bot");logmsg(";");disp.botl=disp.botlx=disp.time_botl=0;callback();}
void timebot(void){counts[12]++;logmsg("timebot");logmsg(";");disp.time_botl=0;callback();}
void status_initialize(boolean a0){counts[13]++;logmsg("status_initialize");logmsg(":%d",(int)a0);logmsg(";");callback();}
void status_eval_next_unhilite(void){counts[14]++;logmsg("status_eval_next_unhilite");logmsg(";");callback();}
time_t getnow(void){counts[15]++;logmsg("getnow");logmsg(";");callback();return clock_value;}
int phase_of_the_moon(void){counts[16]++;logmsg("phase_of_the_moon");logmsg(";");callback();return opts[0];}
boolean friday_13th(void){counts[17]++;logmsg("friday_13th");logmsg(";");callback();return opts[1];}
int night(void){counts[18]++;logmsg("night");logmsg(";");if(opts[25]){rng_log_set_caller("fixture.c",1,"bound_callback");(void)(rn2)(7);}callback();return opts[9];}
int dolookaround(void){counts[19]++;logmsg("dolookaround");logmsg(";");callback();return 0;}
void cmdq_clear(int a0){counts[20]++;logmsg("cmdq_clear");logmsg(":%d",(int)a0);logmsg(";");callback();}
void rhack(int a0){counts[21]++;logmsg("rhack");logmsg(":%d",(int)a0);logmsg(";");callback();}
int enter_explore_mode(void){counts[22]++;logmsg("enter_explore_mode");logmsg(";");callback();return TRUE;}
void end_of_input(void){counts[23]++;logmsg("end_of_input");logmsg(";");fixture_throw(97);__builtin_unreachable();}
boolean is_pool(coordxy a0,coordxy a1){counts[24]++;logmsg("is_pool");logmsg(":%d",(int)a0);logmsg(":%d",(int)a1);logmsg(";");callback();return opts[13];}
void program_state_init(void){counts[25]++;logmsg("program_state_init");logmsg(";");callback();}
void decl_globals_init(void){counts[26]++;logmsg("decl_globals_init");logmsg(";");callback();}
void do_vicinity_map(struct obj * a0){counts[27]++;logmsg("do_vicinity_map");logmsg(":p%d",a0!=0);logmsg(";");callback();}
void warnreveal(void){counts[28]++;logmsg("warnreveal");logmsg(";");callback();}
int dosearch0(int a0){counts[29]++;logmsg("dosearch0");logmsg(":%d",(int)a0);logmsg(";");callback();return 0;}
void swallowed(int a0){counts[30]++;logmsg("swallowed");logmsg(":%d",(int)a0);logmsg(";");callback();}
void under_ground(int a0){counts[31]++;logmsg("under_ground");logmsg(":%d",(int)a0);logmsg(";");callback();}
void under_water(int a0){counts[32]++;logmsg("under_water");logmsg(":%d",(int)a0);logmsg(";");callback();}
void see_monsters(void){counts[33]++;logmsg("see_monsters");logmsg(";");callback();}
void see_objects(void){counts[34]++;logmsg("see_objects");logmsg(";");callback();}
void see_traps(void){counts[35]++;logmsg("see_traps");logmsg(";");callback();}
void curs_on_u(void){counts[36]++;logmsg("curs_on_u");logmsg(";");callback();}
void docrt(void){counts[37]++;logmsg("docrt");logmsg(";");callback();}
void clear_glyph_buffer(void){counts[38]++;logmsg("clear_glyph_buffer");logmsg(";");callback();}
void flush_screen(int a0){counts[39]++;logmsg("flush_screen");logmsg(":%d",(int)a0);logmsg(";");callback();}
void reset_glyphmap(enum glyphmap_change_triggers a0){counts[40]++;logmsg("reset_glyphmap");logmsg(":%d",(int)a0);logmsg(";");callback();}
void save_currentstate(void){counts[41]++;logmsg("save_currentstate");logmsg(";");callback();}
void hellish_smoke_mesg(void){counts[42]++;logmsg("hellish_smoke_mesg");logmsg(";");callback();}
void schedule_goto(d_level * a0,int a1,const char * a2,const char * a3){counts[43]++;logmsg("schedule_goto");logmsg(":p%d",a0!=0);logmsg(":%d",(int)a1);logmsg(":%s",a2?a2:"<null>");logmsg(":%s",a3?a3:"<null>");logmsg(";");callback();}
void deferred_goto(void){counts[44]++;logmsg("deferred_goto");logmsg(";");u.utotype=0;callback();}
void set_wear(struct obj * a0){counts[45]++;logmsg("set_wear");logmsg(":p%d",a0!=0);logmsg(";");callback();}
void find_ac(void){counts[46]++;logmsg("find_ac");logmsg(";");callback();}
void glibr(void){counts[47]++;logmsg("glibr");logmsg(";");callback();}
struct monst * makedog(void){counts[48]++;logmsg("makedog");logmsg(";");callback();return &monsters[2];}
void obj_delivery(boolean a0){counts[49]++;logmsg("obj_delivery");logmsg(":%d",(int)a0);logmsg(";");callback();}
void init_dungeons(void){counts[50]++;logmsg("init_dungeons");logmsg(";");callback();}
s_level * find_level(const char * a0){counts[51]++;logmsg("find_level");logmsg(":%s",a0?a0:"<null>");logmsg(";");callback();return opts[8]?&fixture_tutorial:0;}
schar depth(d_level * a0){counts[52]++;logmsg("depth");logmsg(":p%d",a0!=0);logmsg(";");if(opts[25]){rng_log_set_caller("fixture.c",1,"bound_callback");(void)(rn2)(7);}callback();return a0->dlevel;}
void assign_level(d_level * a0,d_level * a1){counts[53]++;logmsg("assign_level");logmsg(":p%d",a0!=0);logmsg(":p%d",a1!=0);logmsg(";");callback();*a0=*a1;}
void print_level_annotation(void){counts[54]++;logmsg("print_level_annotation");logmsg(";");callback();}
void reset_eat(void){counts[55]++;logmsg("reset_eat");logmsg(";");callback();}
void gethungry(void){counts[56]++;logmsg("gethungry");logmsg(";");callback();}
boolean maybe_finished_meal(boolean a0){counts[57]++;logmsg("maybe_finished_meal");logmsg(":%d",(int)a0);logmsg(";");callback();return opts[6];}
void done(int a0){counts[58]++;logmsg("done");logmsg(":%d",(int)a0);logmsg(";");fixture_throw(a0);__builtin_unreachable();}
void u_wipe_engr(int a0){counts[59]++;logmsg("u_wipe_engr");logmsg(":%d",(int)a0);logmsg(";");callback();}
void read_engr_at(coordxy a0,coordxy a1){counts[60]++;logmsg("read_engr_at");logmsg(":%d",(int)a0);logmsg(":%d",(int)a1);logmsg(";");callback();}
void read_wizkit(void){counts[61]++;logmsg("read_wizkit");logmsg(";");callback();}
void get_nhuuid(void){counts[62]++;logmsg("get_nhuuid");logmsg(";");callback();}
void maybe_shuffle_customizations(void){counts[63]++;logmsg("maybe_shuffle_customizations");logmsg(";");callback();}
void notice_all_mons(boolean a0){counts[64]++;logmsg("notice_all_mons");logmsg(":%d",(int)a0);logmsg(";");callback();}
void domove(void){counts[65]++;logmsg("domove");logmsg(";");callback();}
void runmode_delay_output(void){counts[66]++;logmsg("runmode_delay_output");logmsg(";");callback();}
void overexert_hp(void){counts[67]++;logmsg("overexert_hp");logmsg(";");callback();}
boolean pooleffects(boolean a0){counts[68]++;logmsg("pooleffects");logmsg(":%d",(int)a0);logmsg(";");callback();return 0;}
void check_special_room(boolean a0){counts[69]++;logmsg("check_special_room");logmsg(":%d",(int)a0);logmsg(";");callback();}
void lookaround(void){counts[70]++;logmsg("lookaround");logmsg(";");if(opts[10])gm.multi=0;callback();}
int monster_nearby(void){counts[71]++;logmsg("monster_nearby");logmsg(";");callback();return opts[5];}
void end_running(boolean a0){counts[72]++;logmsg("end_running");logmsg(":%d",(int)a0);logmsg(";");callback();}
void nomul(int a0){counts[73]++;logmsg("nomul");logmsg(":%d",(int)a0);logmsg(";");gm.multi=a0;callback();}
void unmul(const char * a0){counts[74]++;logmsg("unmul");logmsg(":%s",a0?a0:"<null>");logmsg(";");callback();}
int near_capacity(void){counts[75]++;logmsg("near_capacity");logmsg(";");callback();return opts[2];}
const char * align_str(aligntyp a0){counts[76]++;logmsg("align_str");logmsg(":%d",(int)a0);logmsg(";");callback();return a0==A_CHAOTIC?"chaotic":a0==A_LAWFUL?"lawful":"neutral";}
void update_inventory(void){counts[77]++;logmsg("update_inventory");logmsg(";");callback();}
void ckmailstatus(void){counts[78]++;logmsg("ckmailstatus");logmsg(";");callback();}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){counts[79]++;logmsg("makemon");logmsg(":p%d",a0!=0);logmsg(":%d",(int)a1);logmsg(":%d",(int)a2);logmsg(":%d",(int)a3);logmsg(";");callback();return &monsters[2];}
void runtime_info_init(void){counts[80]++;logmsg("runtime_info_init");logmsg(";");callback();}
void mklev(void){counts[81]++;logmsg("mklev");logmsg(";");u.uz.dlevel=1;callback();}
void fumaroles(void){counts[82]++;logmsg("fumaroles");logmsg(";");callback();}
void movebubbles(void){counts[83]++;logmsg("movebubbles");logmsg(";");callback();}
void clear_splitobjs(void){counts[84]++;logmsg("clear_splitobjs");logmsg(";");callback();}
void dobjsfree(void){counts[85]++;logmsg("dobjsfree");logmsg(";");callback();}
int movemon(void){counts[86]++;logmsg("movemon");logmsg(";");callback();if(opts[26])u.umovement+=opts[26];return opts[4]>0?(opts[4]--,TRUE):FALSE;}
int mcalcmove(struct monst * a0,boolean a1){counts[87]++;logmsg("mcalcmove");logmsg(":p%d",a0!=0);logmsg(":%d",(int)a1);logmsg(";");callback();return opts[3];}
void mcalcdistress(void){counts[88]++;logmsg("mcalcdistress");logmsg(";");callback();}
void mnexto(struct monst * a0,unsigned int a1){counts[89]++;logmsg("mnexto");logmsg(":p%d",a0!=0);logmsg(":%d",(int)a1);logmsg(";");callback();}
void see_nearby_monsters(void){counts[90]++;logmsg("see_nearby_monsters");logmsg(";");callback();}
void m_everyturn_effect(struct monst * a0){counts[91]++;logmsg("m_everyturn_effect");logmsg(":p%d",a0!=0);logmsg(";");callback();}
void monst_globals_init(void){counts[92]++;logmsg("monst_globals_init");logmsg(";");callback();}
void l_nhcore_init(void){counts[93]++;logmsg("l_nhcore_init");logmsg(";");callback();}
void l_nhcore_call(int a0){counts[94]++;logmsg("l_nhcore_call");logmsg(":%d",(int)a0);logmsg(";");callback();}
int nhl_pcall_handle(lua_State * a0,int a1,int a2,const char * a3,NHL_pcall_action a4){counts[95]++;logmsg("nhl_pcall_handle");logmsg(":p%d",a0!=0);logmsg(":%d",(int)a1);logmsg(":%d",(int)a2);logmsg(":%s",a3?a3:"<null>");logmsg(":%d",(int)a4);logmsg(";");callback();return 0;}
void init_objects(void){counts[96]++;logmsg("init_objects");logmsg(";");callback();}
void objects_globals_init(void){counts[97]++;logmsg("objects_globals_init");logmsg(";");callback();}
boolean ask_do_tutorial(void){counts[98]++;logmsg("ask_do_tutorial");logmsg(";");callback();return opts[7];}
void reset_justpicked(struct obj * a0){counts[99]++;logmsg("reset_justpicked");logmsg(":p%d",a0!=0);logmsg(";");callback();}
int pickup(int a0){counts[100]++;logmsg("pickup");logmsg(":%d",(int)a0);logmsg(";");callback();return 1;}
boolean reroll_menu(void){counts[101]++;logmsg("reroll_menu");logmsg(";");callback();return opts[17]>0?(opts[17]--,TRUE):FALSE;}
void encumber_msg(void){counts[102]++;logmsg("encumber_msg");logmsg(";");callback();}
void set_uasmon(void){counts[103]++;logmsg("set_uasmon");logmsg(";");callback();}
void polyself(int a0){counts[104]++;logmsg("polyself");logmsg(":%d",(int)a0);logmsg(";");u.umonnum=1;callback();}
void rehumanize(void){counts[105]++;logmsg("rehumanize");logmsg(";");u.umonnum=u.umonster;callback();}
boolean ugenocided(void){counts[106]++;logmsg("ugenocided");logmsg(";");callback();return opts[16];}
const char * udeadinside(void){counts[107]++;logmsg("udeadinside");logmsg(";");callback();return retstrings[1];}
void com_pager(const char * a0){counts[108]++;logmsg("com_pager");logmsg(":%s",a0?a0:"<null>");logmsg(";");callback();}
void run_regions(void){counts[109]++;logmsg("run_regions");logmsg(";");callback();}
boolean any_visible_region(void){counts[110]++;logmsg("any_visible_region");logmsg(";");callback();return opts[15];}
void crashreport_init(int a0,char ** a1){counts[111]++;logmsg("crashreport_init");logmsg(":%d",(int)a0);logmsg(":p%d",a1!=0);logmsg(";");callback();}
void role_init(void){counts[112]++;logmsg("role_init");logmsg(";");callback();}
const char * Hello(struct monst * a0){counts[113]++;logmsg("Hello");logmsg(":p%d",a0!=0);logmsg(";");callback();return retstrings[0];}
void fix_shop_damage(void){counts[114]++;logmsg("fix_shop_damage");logmsg(";");callback();}
void dosounds(void){counts[115]++;logmsg("dosounds");logmsg(";");callback();}
void activate_chosen_soundlib(void){counts[116]++;logmsg("activate_chosen_soundlib");logmsg(";");callback();}
void age_spells(void){counts[117]++;logmsg("age_spells");logmsg(";");callback();}
void u_on_upstairs(void){counts[118]++;logmsg("u_on_upstairs");logmsg(";");callback();}
void sys_early_init(void){counts[119]++;logmsg("sys_early_init");logmsg(";");callback();}
void tele(void){counts[120]++;logmsg("tele");logmsg(";");u.ux+=opts[11];callback();}
void nh_timeout(void){counts[121]++;logmsg("nh_timeout");logmsg(";");callback();}
void do_storms(void){counts[122]++;logmsg("do_storms");logmsg(";");callback();}
void initrack(void){counts[123]++;logmsg("initrack");logmsg(";");callback();}
void settrack(void){counts[124]++;logmsg("settrack");logmsg(";");callback();}
void sink_into_lava(void){counts[125]++;logmsg("sink_into_lava");logmsg(";");callback();}
void u_init_misc(void){counts[126]++;logmsg("u_init_misc");logmsg(";");callback();}
void u_init_inventory_attrs(void){counts[127]++;logmsg("u_init_inventory_attrs");logmsg(";");callback();}
void u_init_skills_discoveries(void){counts[128]++;logmsg("u_init_skills_discoveries");logmsg(";");callback();}
void invault(void){counts[129]++;logmsg("invault");logmsg(";");callback();}
void vision_reset(void){counts[130]++;logmsg("vision_reset");logmsg(";");callback();}
void vision_recalc(int a0){counts[131]++;logmsg("vision_recalc");logmsg(":%d",(int)a0);logmsg(";");gv.vision_full_recalc=0;callback();}
void you_were(void){counts[132]++;logmsg("you_were");logmsg(";");u.umonnum=1;callback();}
void adjust_menu_promptstyle(winid a0,color_attr * a1){counts[133]++;logmsg("adjust_menu_promptstyle");logmsg(":%d",(int)a0);logmsg(":p%d",a1!=0);logmsg(";");callback();}
void amulet(void){counts[134]++;logmsg("amulet");logmsg(";");callback();}
void intervene(void){counts[135]++;logmsg("intervene");logmsg(";");callback();}
void sanity_check(void){counts[136]++;logmsg("sanity_check");logmsg(";");callback();}
void clear_bypasses(void){counts[137]++;logmsg("clear_bypasses");logmsg(";");svc.context.bypasses=0;callback();}
void makewish(void){counts[138]++;logmsg("makewish");logmsg(";");svc.context.resume_wish=0;callback();}
winid fixture_create_nhwindow(int a0){counts[139]++;logmsg("create_nhwindow");logmsg(":%d",(int)a0);logmsg(";");callback();return opts[18]?WIN_ERR:++opts[19];}
void fixture_display_file(const char * a0,boolean a1){counts[140]++;logmsg("display_file");logmsg(":%s",a0?a0:"<null>");logmsg(":%d",(int)a1);logmsg(";");callback();}
void fixture_display_nhwindow(winid a0,boolean a1){counts[141]++;logmsg("display_nhwindow");logmsg(":%d",(int)a0);logmsg(":%d",(int)a1);logmsg(";");callback();}
void fixture_start_menu(winid a0,unsigned long a1){counts[142]++;logmsg("start_menu");logmsg(":%d",(int)a0);logmsg(":%ld",(long)a1);logmsg(";");callback();}
void fixture_end_menu(winid a0,const char * a1){counts[143]++;logmsg("end_menu");logmsg(":%d",(int)a0);logmsg(":%s",a1?a1:"<null>");logmsg(";");callback();}
void fixture_get_nh_event(void){counts[144]++;logmsg("get_nh_event");logmsg(";");if(opts[22]&&counts[144]>=opts[22]){fixture_throw(22);__builtin_unreachable();}callback();}
void fixture_cliparound(int a0,int a1){counts[145]++;logmsg("cliparound");logmsg(":%d",(int)a0);logmsg(":%d",(int)a1);logmsg(";");callback();}
char*eos(char*s){return s+strlen(s);}
schar acurr(int attr){logmsg("acurr:%d;",attr);if(opts[25]){rng_log_set_caller("fixture.c",1,"bound_callback");(void)(rn2)(7);}return opts[24];}
void probe_clear(void){tracebuf[0]=0;}
void probe_reset(unsigned v){int i;if(growth){free(growth);growth=0;}
memset(&u,0,sizeof u);
memset(&svc,0,sizeof svc);
memset(&flags,0,sizeof flags);
memset(&iflags,0,sizeof iflags);
memset(&program_state,0,sizeof program_state);
memset(&disp,0,sizeof disp);
memset(&gd,0,sizeof gd);
memset(&gy,0,sizeof gy);
memset(&gw,0,sizeof gw);
memset(&svm,0,sizeof svm);
memset(&gh,0,sizeof gh);
memset(&gm,0,sizeof gm);
memset(&svl,0,sizeof svl);
memset(&go,0,sizeof go);
memset(&gc,0,sizeof gc);
memset(&gl,0,sizeof gl);
memset(&gu,0,sizeof gu);
memset(&urealtime,0,sizeof urealtime);
memset(&a11y,0,sizeof a11y);
memset(&svp,0,sizeof svp);
memset(&gi,0,sizeof gi);
memset(&gv,0,sizeof gv);
memset(&svd,0,sizeof svd);
memset(monsters,0,sizeof monsters);memset(mons,0,sizeof mons);memset(opts,0,sizeof opts);memset(counts,0,sizeof counts);memset(nhcb_counts,0,sizeof nhcb_counts);seed=v;roll_pos=roll_count=0;clock_value=1700000000L;opts[3]=12;opts[24]=12;u.ux=5;u.uy=4;u.uz.dlevel=1;stronghold_level.dlevel=20;u.umovement=12;u.ulevel=5;u.uhp=10;u.uhpmax=15;u.mh=10;u.mhmax=15;u.uen=1;u.uenmax=10;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urole.allow=ROLE_MALE|ROLE_FEMALE;gu.urole.name.m=retstrings[3];gu.urole.name.f=0;gu.urace.adj=retstrings[2];flags.verbose=TRUE;svc.context.seer_turn=999999;gy.youmonst.data=&mons[0];mons[0].mmove=12;mons[0].mlet=S_HUMAN;for(i=0;i<NUMMONS;i++)mons[i].geno=(i*37)&65535;monsters[0].data=&mons[0];monsters[1].data=&mons[0];monsters[0].nmon=&monsters[1];fmon=&monsters[0];gc.command_count=1;strcpy(svp.plname,"Player");fixture_tutorial.dlevel.dlevel=4;WIN_MESSAGE=1;WIN_STATUS=2;WIN_MAP=3;WIN_INVEN=4;go.occtxt="working";
windowprocs.win_get_nh_event=fixture_get_nh_event;
windowprocs.win_cliparound=fixture_cliparound;
windowprocs.win_end_menu=fixture_end_menu;
windowprocs.win_display_file=fixture_display_file;
windowprocs.win_start_menu=fixture_start_menu;
windowprocs.win_create_nhwindow=fixture_create_nhwindow;
windowprocs.win_display_nhwindow=fixture_display_nhwindow;
probe_clear();}
int probe_fields(void){return 98;}
const char*probe_field_name(int i){static const char*names[]={"a11y.glyph_updates","disp.botl","disp.botlx","disp.time_botl","flags.female","flags.friday13","flags.initgend","flags.legacy","flags.moonphase","flags.pantheon","flags.randomall","flags.runmode","flags.time","flags.verbose","gc.cmd_key","gc.command_count","gd.defer_see_monsters","gh.hero_seq","gi.invent","gl.luacore","gm.multi","go.occtxt","go.occupation","gu.urace.adj","gu.urole.allow","gu.urole.name.f","gu.urole.name.m","gv.vision_full_recalc","gw.were_changes","iflags.debug_fuzzer","iflags.deferred_X","iflags.fuzzerpending","iflags.hilite_delta","iflags.news","iflags.nofollowers","iflags.pending_customizations","iflags.perm_invent","iflags.sanity_check","iflags.wc_splash_screen","program_state.beyond_savefile_load","program_state.done_hup","program_state.in_moveloop","program_state.something_worth_saving","svc.context.bypasses","svc.context.ident","svc.context.mon_moving","svc.context.move","svc.context.mv","svc.context.next_attrib_check","svc.context.resume_wish","svc.context.rndencode","svc.context.run","svc.context.seer_turn","svc.context.travel","svc.context.tribute.enabled","svc.context.tribute.tributesz","svc.context.warnlevel","svl.level.flags.fumaroles","svl.level.flags.noautosearch","svm.moves","u.mfemale","u.mh","u.mhmax","u.ualign.type","u.ublesscnt","u.uburied","u.udg_cnt","u.uen","u.uenmax","u.uevent.amulet_wish","u.uevent.udemigod","u.uhave.amulet","u.uhp","u.uhpmax","u.uinvulnerable","u.ulevel","u.ulycn","u.umoved","u.umovement","u.uroleplay.pauper","u.uroleplay.reroll","u.usleep","u.usteed","u.uswallow","u.utotype","u.utrap","u.utraptype","u.ux","u.uy","u.uz.dlevel","u.uz0.dlevel","urealtime.realtime","urealtime.start_timing","gu.urole.mnum","WIN_MESSAGE","WIN_STATUS","WIN_MAP","WIN_INVEN"};return names[i];}
void probe_field(int i,long v){teleport_allmain_set(i,v);}
void probe_option(int i,int v){opts[i]=v;}
void probe_roll(int v){rolls[roll_count++]=v;}
void probe_clock(long v){clock_value=v;}
void probe_caps(unsigned long v){windowprocs.wincap2=v;}
void probe_poly(int flag,int move,int letter){u.umonster=0;u.umonnum=flag;mons[0].mmove=move;mons[0].mlet=letter;}
void probe_occupation(int flag){go.occupation=flag?fixture_occupation:0;}
void probe_steed(int flag){u.usteed=flag?&monsters[0]:0;}
void probe_sex(int female,int original,int rolefemale){flags.female=female;flags.initgend=original;u.mfemale=female;gu.urole.name.f=rolefemale?retstrings[4]:0;}
void probe_lua(int flag){gl.luacore=flag?(void*)&clock_value:0;nhcb_counts[NHCB_END_TURN]=flag;}
void probe_role(int wizard_role){gu.urole.mnum=wizard_role?PM_WIZARD:PM_ARCHEOLOGIST;}
void probe_prop(int index,long intrinsic,long extrinsic,long blocked){u.uprops[index].intrinsic=intrinsic;u.uprops[index].extrinsic=extrinsic;u.uprops[index].blocked=blocked;}
int probe_prop_count(void){return 20;}
int probe_prop_id(int i){static const int ids[]={FAST,GLIB,HALLUC,HALLUC_RES,TELEPORT,POLYMORPH,UNCHANGING,SEARCHING,WARNING,CLAIRVOYANT,BLINDED,TELEPAT,WARN_OF_MON,ENERGY_REGENERATION,MAGICAL_BREATHING,REGENERATION,HALF_PHDAM,SLEEPY,DRAIN_RES,SEE_INVIS};return ids[i];}
long probe_time(int mode,time_t a,time_t b){return mode?timet_delta(a,b):timet_to_seconds(a);}
void probe_call(int action,int value){switch(action){case 0:early_init(0,0);break;case 1:moveloop_preamble(value);break;case 2:u_calc_moveamt(value);break;case 3:maybe_generate_rnd_mon();break;case 4:moveloop_core();break;case 5:maybe_do_tutorial();break;case 6:moveloop(value);break;case 7:regen_pw(value);break;case 8:regen_hp(value);break;case 9:stop_occupation();break;case 10:init_sound_disp_gamewindows();break;case 11:newgame();break;case 12:welcome(value);break;case 13:interrupt_multi(value?"You feel full of energy.":0);break;}}
char*probe_trace(void){return tracebuf;}
char*probe_snapshot(void){char*p=snapshotbuf;int i;struct monst*m;
#define APP(...) p+=sprintf(p,__VA_ARGS__)
APP("a11y.glyph_updates:%ld;",(long)a11y.glyph_updates);
APP("disp.botl:%ld;",(long)disp.botl);
APP("disp.botlx:%ld;",(long)disp.botlx);
APP("disp.time_botl:%ld;",(long)disp.time_botl);
APP("flags.female:%ld;",(long)flags.female);
APP("flags.friday13:%ld;",(long)flags.friday13);
APP("flags.initgend:%ld;",(long)flags.initgend);
APP("flags.legacy:%ld;",(long)flags.legacy);
APP("flags.moonphase:%ld;",(long)flags.moonphase);
APP("flags.pantheon:%ld;",(long)flags.pantheon);
APP("flags.randomall:%ld;",(long)flags.randomall);
APP("flags.runmode:%ld;",(long)flags.runmode);
APP("flags.time:%ld;",(long)flags.time);
APP("flags.verbose:%ld;",(long)flags.verbose);
APP("gc.cmd_key:%ld;",(long)gc.cmd_key);
APP("gc.command_count:%ld;",(long)gc.command_count);
APP("gd.defer_see_monsters:%ld;",(long)gd.defer_see_monsters);
APP("gh.hero_seq:%ld;",(long)gh.hero_seq);
APP("gi.invent:%d;",!!gi.invent);
APP("gl.luacore:%d;",!!gl.luacore);
APP("gm.multi:%ld;",(long)gm.multi);
APP("go.occtxt:%s;",go.occtxt?go.occtxt:"<null>");
APP("go.occupation:%d;",!!go.occupation);
APP("gu.urace.adj:%s;",gu.urace.adj?gu.urace.adj:"<null>");
APP("gu.urole.allow:%ld;",(long)gu.urole.allow);
APP("gu.urole.name.f:%s;",gu.urole.name.f?gu.urole.name.f:"<null>");
APP("gu.urole.name.m:%s;",gu.urole.name.m?gu.urole.name.m:"<null>");
APP("gv.vision_full_recalc:%ld;",(long)gv.vision_full_recalc);
APP("gw.were_changes:%ld;",(long)gw.were_changes);
APP("iflags.debug_fuzzer:%ld;",(long)iflags.debug_fuzzer);
APP("iflags.deferred_X:%ld;",(long)iflags.deferred_X);
APP("iflags.fuzzerpending:%ld;",(long)iflags.fuzzerpending);
APP("iflags.hilite_delta:%ld;",(long)iflags.hilite_delta);
APP("iflags.news:%ld;",(long)iflags.news);
APP("iflags.nofollowers:%ld;",(long)iflags.nofollowers);
APP("iflags.pending_customizations:%ld;",(long)iflags.pending_customizations);
APP("iflags.perm_invent:%ld;",(long)iflags.perm_invent);
APP("iflags.sanity_check:%ld;",(long)iflags.sanity_check);
APP("iflags.wc_splash_screen:%ld;",(long)iflags.wc_splash_screen);
APP("program_state.beyond_savefile_load:%ld;",(long)program_state.beyond_savefile_load);
APP("program_state.done_hup:%ld;",(long)program_state.done_hup);
APP("program_state.in_moveloop:%ld;",(long)program_state.in_moveloop);
APP("program_state.something_worth_saving:%ld;",(long)program_state.something_worth_saving);
APP("svc.context.bypasses:%ld;",(long)svc.context.bypasses);
APP("svc.context.ident:%ld;",(long)svc.context.ident);
APP("svc.context.mon_moving:%ld;",(long)svc.context.mon_moving);
APP("svc.context.move:%ld;",(long)svc.context.move);
APP("svc.context.mv:%ld;",(long)svc.context.mv);
APP("svc.context.next_attrib_check:%ld;",(long)svc.context.next_attrib_check);
APP("svc.context.resume_wish:%ld;",(long)svc.context.resume_wish);
APP("svc.context.rndencode:%ld;",(long)svc.context.rndencode);
APP("svc.context.run:%ld;",(long)svc.context.run);
APP("svc.context.seer_turn:%ld;",(long)svc.context.seer_turn);
APP("svc.context.travel:%ld;",(long)svc.context.travel);
APP("svc.context.tribute.enabled:%ld;",(long)svc.context.tribute.enabled);
APP("svc.context.tribute.tributesz:%ld;",(long)svc.context.tribute.tributesz);
APP("svc.context.warnlevel:%ld;",(long)svc.context.warnlevel);
APP("svl.level.flags.fumaroles:%ld;",(long)svl.level.flags.fumaroles);
APP("svl.level.flags.noautosearch:%ld;",(long)svl.level.flags.noautosearch);
APP("svm.moves:%ld;",(long)svm.moves);
APP("u.mfemale:%ld;",(long)u.mfemale);
APP("u.mh:%ld;",(long)u.mh);
APP("u.mhmax:%ld;",(long)u.mhmax);
APP("u.ualign.type:%ld;",(long)u.ualign.type);
APP("u.ublesscnt:%ld;",(long)u.ublesscnt);
APP("u.uburied:%ld;",(long)u.uburied);
APP("u.udg_cnt:%ld;",(long)u.udg_cnt);
APP("u.uen:%ld;",(long)u.uen);
APP("u.uenmax:%ld;",(long)u.uenmax);
APP("u.uevent.amulet_wish:%ld;",(long)u.uevent.amulet_wish);
APP("u.uevent.udemigod:%ld;",(long)u.uevent.udemigod);
APP("u.uhave.amulet:%ld;",(long)u.uhave.amulet);
APP("u.uhp:%ld;",(long)u.uhp);
APP("u.uhpmax:%ld;",(long)u.uhpmax);
APP("u.uinvulnerable:%ld;",(long)u.uinvulnerable);
APP("u.ulevel:%ld;",(long)u.ulevel);
APP("u.ulycn:%ld;",(long)u.ulycn);
APP("u.umoved:%ld;",(long)u.umoved);
APP("u.umovement:%ld;",(long)u.umovement);
APP("u.uroleplay.pauper:%ld;",(long)u.uroleplay.pauper);
APP("u.uroleplay.reroll:%ld;",(long)u.uroleplay.reroll);
APP("u.usleep:%ld;",(long)u.usleep);
APP("u.usteed:%d;",!!u.usteed);
APP("u.uswallow:%ld;",(long)u.uswallow);
APP("u.utotype:%ld;",(long)u.utotype);
APP("u.utrap:%ld;",(long)u.utrap);
APP("u.utraptype:%ld;",(long)u.utraptype);
APP("u.ux:%ld;",(long)u.ux);
APP("u.uy:%ld;",(long)u.uy);
APP("u.uz.dlevel:%ld;",(long)u.uz.dlevel);
APP("u.uz0.dlevel:%ld;",(long)u.uz0.dlevel);
APP("urealtime.realtime:%ld;",(long)urealtime.realtime);
APP("urealtime.start_timing:%ld;",(long)urealtime.start_timing);
APP("gu.urole.mnum:%ld;",(long)gu.urole.mnum);
APP("WIN_MESSAGE:%ld;",(long)WIN_MESSAGE);
APP("WIN_STATUS:%ld;",(long)WIN_STATUS);
APP("WIN_MAP:%ld;",(long)WIN_MAP);
APP("WIN_INVEN:%ld;",(long)WIN_INVEN);
APP("prop:");for(i=1;i<=LAST_PROP;i++)APP("%ld/%ld/%ld,",u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);APP(";flags:%d/%d/%ld/%d;poly:%d/%d;notices:%d;realtime:%ld/%lld;roll:%d;mons:",flags.debug,u.uinwater,u.usleep,u.uburied,u.umonnum,u.umonster,a11y.mon_notices_blocked,urealtime.realtime,urealtime.start_timing,roll_pos);for(m=fmon;m;m=m->nmon)APP("%d,",m->movement);APP(";vitals:");for(i=0;i<NUMMONS;i++)APP("%d,",svm.mvitals[i].mvflags);APP(";align:%d/%d;",u.ualignbase[0],u.ualignbase[1]);return snapshotbuf;
#undef APP
}
long probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return SIZE(teleport_allmain_layout);}
const char*probe_layout_name(int i){return teleport_allmain_layout[i].name;}
long probe_layout_value(int i){return teleport_allmain_layout[i].value;}
