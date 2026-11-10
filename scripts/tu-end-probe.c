/* Actual original configured END versus imported JS; foreign world/UI controlled. */
#define NEED_VARARGS
#include "hack.h"
#include "wintty.h"
#include "dlb.h"
#include <signal.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef free
extern void free(void*);
__typeof__(iflags)iflags;
__typeof__(flags)flags;
__typeof__(windowprocs)windowprocs;
__typeof__(WIN_MESSAGE)WIN_MESSAGE;
__typeof__(gm)gm;
__typeof__(u)u;
__typeof__(svd)svd;
__typeof__(soundprocs)soundprocs;
__typeof__(program_state)program_state;
__typeof__(svk)svk;
__typeof__(gu)gu;
__typeof__(svm)svm;
__typeof__(gb)gb;
__typeof__(sysopt)sysopt;
__typeof__(gi)gi;
__typeof__(gn)gn;
__typeof__(svc)svc;
__typeof__(disp)disp;
__typeof__(gy)gy;
__typeof__(ga)ga;
__typeof__(gg)gg;
__typeof__(gt)gt;
__typeof__(gk)gk;
__typeof__(uchain)uchain;
__typeof__(gd)gd;
__typeof__(gh)gh;
__typeof__(uamul)uamul;
__typeof__(urealtime)urealtime;
__typeof__(svl)svl;
__typeof__(svp)svp;
__typeof__(WIN_INVEN)WIN_INVEN;
__typeof__(WIN_MAP)WIN_MAP;
__typeof__(WIN_STATUS)WIN_STATUS;
__typeof__(gv)gv;
const char ynchars[]="yn",ynqchars[]="ynq",disclosure_options[]="iavgco";
static char tracebuf[1048576],snapbuf[1048576],inputbuf[4096],textbuf[32][2048],streambuf[8192];
static struct obj nodes[16];static struct monst monsters[4];static struct mextra mextras[4];static struct oextra oextras[16];static struct valuable_data valuables[24];static Loot loot[17];static NHFILE file;
static int opts[96],serial,heapfrees,allocs,exitstatus,callback_depth,callback_count,restorepos;static unsigned rngstate;static void*growth;static jmp_buf exitpoint;
static void logmsg(const char*f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
static int address_id(const void*p){if(!p)return -1;if((const char*)p>=(const char*)nodes&&(const char*)p<(const char*)(nodes+16))return 100+(int)((const char*)p-(const char*)nodes);if((const char*)p>=(const char*)monsters&&(const char*)p<(const char*)(monsters+4))return 20000+(int)((const char*)p-(const char*)monsters);if(p==&u)return 30000;if(p==&u.uz)return 30001;if((const char*)p>=(const char*)mons&&(const char*)p<(const char*)(mons+NUMMONS+1))return 40000+(int)((const char*)p-(const char*)mons);return 999;}
static void callback(void);
static void fixture_exit(int status){exitstatus=status;logmsg("exit:%d;",status);longjmp(exitpoint,1);}
static void fixture_abort(void){exitstatus=-99;logmsg("abort;");longjmp(exitpoint,1);}
#define exit fixture_exit
#define abort fixture_abort
void teleport_probe_free(void*p){if(p){heapfrees++;logmsg("free;");}free(p);}
#define free teleport_probe_free
long*alloc(unsigned n){allocs++;logmsg("alloc:%u;",n);void*p=malloc(n);if(!p)__builtin_trap();return p;}
static void (*fixture_signal(int sig,void(*fn)(int)))(int);
#define signal fixture_signal
#ifdef TELEPORT_REFERENCE_TU
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/end.c"
#else
extern void teleport_end_test_done_intr(int);
#define done_intr teleport_end_test_done_intr
extern void teleport_end_test_done_hangup(int);
#define done_hangup teleport_end_test_done_hangup
extern void teleport_end_test_fixup_death(int);
#define fixup_death teleport_end_test_fixup_death
extern boolean teleport_end_test_should_query_disclose_option(int,char *);
#define should_query_disclose_option teleport_end_test_should_query_disclose_option
extern void teleport_end_test_dump_everything(int,time_t);
#define dump_everything teleport_end_test_dump_everything
extern void teleport_end_test_disclose(int,boolean);
#define disclose teleport_end_test_disclose
extern void teleport_end_test_savelife(int);
#define savelife teleport_end_test_savelife
extern void teleport_end_test_get_valuables(struct obj *);
#define get_valuables teleport_end_test_get_valuables
extern void teleport_end_test_sort_valuables(struct valuable_data *,int);
#define sort_valuables teleport_end_test_sort_valuables
extern void teleport_end_test_artifact_score(struct obj *,boolean,winid);
#define artifact_score teleport_end_test_artifact_score
extern boolean teleport_end_test_fuzzer_savelife(int);
#define fuzzer_savelife teleport_end_test_fuzzer_savelife
extern void teleport_end_test_really_done(int);
#define really_done teleport_end_test_really_done
extern int teleport_end_test_wordcount(char *);
#define wordcount teleport_end_test_wordcount
extern void teleport_end_test_bel_copy1(char **,char *);
#define bel_copy1 teleport_end_test_bel_copy1
#endif
#include "tu-end-layout.h"
#include "../nethack-c/wasm/tu-fragments/end-support.inc"
static int handler_id(void(*fn)(int)){if(fn==SIG_IGN)return -1;if(fn==done1)return 0;if(fn==done_intr||fn==teleport_end_intr_callback)return 1;if(fn==done_hangup||fn==teleport_end_hangup_callback)return 2;return -99;}
static void (*fixture_signal(int sig,void(*fn)(int)))(int){logmsg("signal:%d:%d;",sig,handler_id(fn));return SIG_DFL;}
void sethanguphandler(void(*fn)(int)){logmsg("hangup:%d;",handler_id(fn));}
static void window_clear(winid w){logmsg("clear:%d;",w);callback();}static void window_sync(void){logmsg("sync;");callback();}static void window_exit(const char*s){logmsg("exitwin:%s;",s?s:"NULL");callback();}static winid window_create(int type){logmsg("create:%d;",type);return ++serial;}static void window_display(winid w,boolean b){logmsg("display:%d:%d;",w,b);callback();}static void window_destroy(winid w){logmsg("destroy:%d;",w);callback();}static void window_putstr(winid w,int a,const char*s){logmsg("put:%d:%d:%s;",w,a,s);callback();if(opts[92]){nodes[0].known=!nodes[0].known;logmsg("alias-put:%s:%d;",s,nodes[0].known);}}static void window_raw(const char*s){logmsg("raw:%s;",s);callback();}static void window_rip(winid w,int h,time_t t){logmsg("rip:%d:%d:%lld;",w,h,t);callback();}static void sound_exit(const char*s){logmsg("sound:%s;",s);callback();}
static void callback(void){callback_count++;if(opts[90]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)__builtin_trap();logmsg("growth;");}if(opts[91]&&!callback_depth){callback_depth++;char s[80]="reentry words";char*p=build_english_list(s);logmsg("nested:%s;",p);free(p);callback_depth--;}}
static char*named(const char*name){static int index;char*b=textbuf[index++%32];snprintf(b,2048,"%s",name);return b;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean rng_log_enabled(void){return TRUE;}static char origin[120];void rng_log_set_caller(const char*f,int l,const char*n){snprintf(origin,sizeof origin,"%s:%d:%s",f,l,n);}
int(rn2)(int n){rngstate=rngstate*1664525u+1013904223u;int value=(rngstate>>8)%n;logmsg("rng:%d:%d@%s;",n,value,origin);return value;}
int(d)(int n,int count){int total=0;for(int i=0;i<n;i++)total+=(rn2)(count)+1;return total;}
char*eos(char*s){return s+strlen(s);}char*strstri(const char*s,const char*t){for(;*s;s++)if(!strncasecmp(s,t,strlen(t)))return(char*)s;return 0;}
char*monhealthdescr(struct monst*m,boolean b,char*out){logmsg("health:%d:%d;",address_id(m),b);strcpy(out,opts[3]?"injured ":"");return out;}
const char*pmname(struct permonst*p,int gender){snprintf(textbuf[0],2048,"creature%d%c",(int)(p-mons),gender?'F':'M');return textbuf[0];}int Mgender(struct monst*m){return m->female;}
char*an(const char*s){char*b=named("");snprintf(b,2048,"an %s",s);return b;}char*shkname(struct monst*m){return "Izchak";}boolean shkname_is_pname(struct monst*m){return opts[4];}char*m_monnam(struct monst*m){return named("high priest");}
#define MSG(name) void name(const char*f,...){va_list a;va_start(a,f);logmsg(#name ":");vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");callback();}
MSG(raw_printf)MSG(impossible)MSG(You)MSG(Your)MSG(You_feel)MSG(pline)MSG(pline_The)
void livelog_printf(long flags,const char*f,...){va_list a;va_start(a,f);logmsg("live:%ld:",flags);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");callback();}
char yn_function(const char*q,const char*c,char d,boolean hist){logmsg("query:%s:%s:%d:%d;",q,c,d,hist);callback();return opts[0]?opts[0]:d;}
schar acurr(int n){logmsg("acurr:%d;",n);return opts[5]?opts[5]:13;}int minuhpmax(int n){return n+opts[6];}void setuhpmax(int n,boolean b){logmsg("hpmax:%d:%d;",n,b);u.uhpmax=n;}void init_uhunger(void){logmsg("hunger;");u.uhunger=900;}void make_sick(long n,const char*s,boolean b,int what){logmsg("sick:%ld:%d:%d;",n,b,what);u.uprops[SICK].intrinsic=n;}void expels(struct monst*m,struct permonst*p,boolean b){logmsg("expels:%d:%d:%d;",address_id(m),address_id(p),b);callback();u.uswallow=0;u.ustuck=0;}void unstuck(struct monst*m){logmsg("unstuck:%d;",address_id(m));u.ustuck=0;}
void place_object(struct obj*o,coordxy x,coordxy y){logmsg("place:%d:%d:%d;",address_id(o),x,y);o->where=OBJ_FLOOR;o->ox=x;o->oy=y;}void stackobj(struct obj*o){logmsg("stack:%d;",address_id(o));}
long arti_cost(struct obj*o){return (long)o->otyp*100+opts[7];}const char*currency(long n){return n==1?"zorkmid":"zorkmids";}const char*artiname(int n){return "Artifact";}
struct obj*mksobj(int typ,boolean b,boolean a){struct obj*o=&nodes[15];memset(o,0,sizeof *o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;logmsg("mksobj:%d:%d:%d;",typ,b,a);return o;}void obfree(struct obj*o,struct obj*m){logmsg("obfree:%d:%d;",address_id(o),address_id(m));}void set_itimeout(long*p,long n){logmsg("timeout:%ld;",n);*p=(*p&~TIMEOUT)|n;}
void cmdq_add_ec(int q,int(*fn)(void)){logmsg("cmd:%d:%d;",q,fn==wiz_makemap);}
void formatkiller(char*out,unsigned cap,int how,boolean b){snprintf(out,cap,"reason%d%s",how,b?" while busy":"");logmsg("killer:%u:%d:%d;",cap,how,b);}
time_t getnow(void){return (1LL<<54)+17;}long timet_delta(time_t a,time_t b){return a-b;}void record_achievement(schar n){logmsg("achievement:%d;",n);u.uachieved[0]=1;}
boolean paybill(int h,boolean b){logmsg("pay:%d:%d;",h,b);return opts[8];}void set_cknown_lknown(struct obj*o){if(Is_container(o)){o->cknown=o->lknown=1;}}void observe_quantum_cat(struct obj*o,boolean make,boolean say){logmsg("cat:%d:%d;",make,say);if(opts[9])o->spe=0;}
struct obj*mk_named_object(int typ,struct permonst*p,coordxy x,coordxy y,const char*s){logmsg("named:%d:%d:%d:%d:%s;",typ,address_id(p),x,y,s);return &nodes[14];}
unsigned Strlen_(const char*s,const char*f,int l){logmsg("Strlen:%s:%d;",f,l);return strlen(s);}long money_cnt(struct obj*o){return opts[10]?(1L<<54)+3:50;}long hidden_gold(boolean b){return opts[11]?(1L<<53)+7:20;}struct obj*carrying(int typ){return opts[12]?&nodes[0]:0;}const char*Goodbye(void){return "Goodbye";}void dump_forward_putstr(winid w,int a,const char*s,int stop){logmsg("dump:%d:%d:%d:%s;",w,a,stop,s);callback();}
char*xname(struct obj*o){char*b=named("");snprintf(b,2048,"object%d",o->otyp);return b;}char*doname_with_price(struct obj*o){return xname(o);}char*the(const char*s){char*b=named("");snprintf(b,2048,"the %s",s);return b;}char*upstart(char*s){if(*s)*s=toupper(*s);return s;}char*thesimpleoname(struct obj*o){return the(xname(o));}
Loot*sortloot(struct obj**chain,unsigned flags,boolean b,boolean(*fn)(struct obj*)){logmsg("sort:%u:%d:%d;",flags,b,fn!=0);int i=0;for(struct obj*o=*chain;o;o=o->nobj)loot[i++].obj=o;loot[i].obj=0;return loot;}void unsortloot(Loot**p){logmsg("unsort;");*p=0;}
void sfo_kinfo(NHFILE*f,struct kinfo*k,const char*s){size_t off=strlen(streambuf);snprintf(streambuf+off,sizeof streambuf-off,"%d,%d,%s;",k->id,k->format,k->name);logmsg("savekiller:%s;",s);if(opts[85]){k->format+=3;k->name[0]='!';}}void sfi_kinfo(NHFILE*f,struct kinfo*k,const char*s){logmsg("loadkiller:%s;",s);k->next=++restorepos<opts[86]?(struct kinfo*)1:0;k->id=opts[13]+restorepos;k->format=opts[14]+restorepos;strcpy(k->name,"restored");}
boolean debugcore(const char*f,boolean b){logmsg("debugcore:%s:%d;",f,b);return opts[33];}
boolean submit_web_report(int cos,const char*s,const char*why){logmsg("report:%d:%s:%s;",cos,s,why?why:"NULL");return opts[15];}boolean NH_panictrace_gdb(void){logmsg("gdb;");return opts[16];}boolean NH_panictrace_libc(void){logmsg("libctrace;");return opts[17];}
boolean In_quest(d_level * a0){logmsg("In_quest;" );return opts[32];}
char * Monnam(struct monst * a0){logmsg("Monnam;" );return named("Monnam");}
boolean accessible(coordxy a0,coordxy a1){logmsg("accessible;" );return opts[25];}
int adj_lev(struct permonst * a0){logmsg("adj_lev;" );return opts[30]?opts[30]:4;}
boolean adjattrib(int a0,int a1,int a2){logmsg("adjattrib;" );return 0;}
void bless(struct obj * a0){logmsg("bless;" );callback();}
void bot(void){logmsg("bot;" );callback();}
boolean can_make_bones(void){logmsg("can_make_bones;" );return opts[27];}
int canseemon(struct monst * a0){logmsg("canseemon;" );return opts[19];}
void clearlocks(void){logmsg("clearlocks;" );callback();}
void clearpriests(void){logmsg("clearpriests;" );callback();}
int count_achievements(void){logmsg("count_achievements;" );return opts[23];}
void curs_on_u(void){logmsg("curs_on_u;" );callback();}
xint16 deepest_lev_reached(boolean a0){logmsg("deepest_lev_reached;" );return opts[29]?opts[29]:7;}
schar depth(d_level * a0){logmsg("depth;" );return a0->dlevel;}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object;" );callback();}
char display_inventory(const char * a0,boolean a1){logmsg("display_inventory;" );return 0;}
int dosave0(void){logmsg("dosave0;" );return opts[22];}
void dump_close_log(void){logmsg("dump_close_log;" );callback();}
void dump_open_log(time_t a0){logmsg("dump_open_log;" );callback();}
xint16 dunlev(d_level * a0){logmsg("dunlev;" );return a0->dlevel;}
void endmultishot(boolean a0){logmsg("endmultishot;" );callback();}
void enlightenment(int a0,int a1){logmsg("enlightenment;" );callback();}
void finish_paybill(void){logmsg("finish_paybill;" );callback();}
void force_launch_placement(void){logmsg("force_launch_placement;" );callback();}
void free_oname(struct obj * a0){logmsg("free_oname;" );callback();}
void free_pickinv_cache(void){logmsg("free_pickinv_cache;" );callback();}
void freedynamicdata(void){logmsg("freedynamicdata;" );callback();}
void inven_inuse(boolean a0){logmsg("inven_inuse;" );callback();}
int isok(coordxy a0,coordxy a1){logmsg("isok;" );return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
void keepdogs(boolean a0){logmsg("keepdogs;" );callback();}
void l_nhcore_call(int a0){logmsg("l_nhcore_call;" );callback();}
void l_nhcore_done(void){logmsg("l_nhcore_done;" );callback();}
boolean launch_in_progress(void){logmsg("launch_in_progress;" );return opts[28];}
void lift_covet_and_placebc(int a0){logmsg("lift_covet_and_placebc;" );callback();}
void list_genocided(char a0,boolean a1){logmsg("list_genocided;" );callback();}
void list_vanquished(char a0,boolean a1){logmsg("list_vanquished;" );callback();}
void make_grave(coordxy a0,coordxy a1,const char * a2){logmsg("make_grave;" );callback();}
int midnight(void){logmsg("midnight;" );return 0;}
char * mon_nam(struct monst * a0){logmsg("mon_nam;" );return named("mon_nam");}
int night(void){logmsg("night;" );return 1;}
void nomul(int a0){logmsg("nomul;" );callback();}
void nomux_capture_write_input_boundary(void){logmsg("nomux_capture_write_input_boundary;" );callback();}
void paniclog(const char * a0,const char * a1){logmsg("paniclog;" );callback();}
void panictrace_setsignals(boolean a0){logmsg("panictrace_setsignals;" );callback();}
boolean paranoid_query(boolean a0,const char * a1){logmsg("paranoid_query;" );return opts[1];}
void paygd(boolean a0){logmsg("paygd;" );callback();}
int peffects(struct obj * a0){logmsg("peffects;" );return 0;}
void perm_invent_toggled(boolean a0){logmsg("perm_invent_toggled;" );callback();}
void reset_utrap(boolean a0){logmsg("reset_utrap;" );callback();}
void savebones(int a0,time_t a1,struct obj * a2){logmsg("savebones;" );callback();}
void schedule_goto(d_level * a0,int a1,const char * a2,const char * a3){logmsg("schedule_goto;" );callback();}
int sensemon(struct monst * a0){logmsg("sensemon;" );return opts[20];}
void set_error_savefile(void){logmsg("set_error_savefile;" );callback();}
void show_conduct(int a0){logmsg("show_conduct;" );callback();}
void show_overview(int a0,int a1){logmsg("show_overview;" );callback();}
boolean single_level_branch(d_level * a0){logmsg("single_level_branch;" );return opts[31];}
boolean sticks(struct permonst * a0){logmsg("sticks;" );return opts[24];}
boolean the_unique_obj(struct obj * a0){logmsg("the_unique_obj;" );return opts[26];}
boolean the_unique_pm(struct permonst * a0){logmsg("the_unique_pm;" );return opts[18];}
void topten(int a0,time_t a1){logmsg("topten;" );callback();}
void update_inventory(void){logmsg("update_inventory;" );callback();}
void useup(struct obj * a0){logmsg("useup;" );callback();}
int wiz_makemap(void){logmsg("wiz_makemap;" );return 0;}
boolean zombie_maker(struct monst * a0){logmsg("zombie_maker;" );return opts[21];}
int probe_layout_count(void){return SIZE(end_layout);}const char*probe_layout_name(int i){return end_layout[i].name;}long long probe_layout_value(int i){return end_layout[i].value;}size_t probe_stack(void){return emscripten_stack_get_current();}const char*probe_trace(void){return tracebuf;}const char*probe_output(void){return streambuf;}
void probe_clear(void){tracebuf[0]=0;}void probe_option(int n,int v){opts[n]=v;}void probe_input(const char*s){snprintf(inputbuf,sizeof inputbuf,"%s",s?s:"");}void probe_seed(unsigned n){rngstate=n;}
void probe_reset(void){
 if(growth){free(growth);growth=0;}memset(opts,0,sizeof opts);memset(nodes,0,sizeof nodes);memset(monsters,0,sizeof monsters);memset(mextras,0,sizeof mextras);memset(oextras,0,sizeof oextras);memset(valuables,0,sizeof valuables);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(&svk,0,sizeof svk);memset(&gm,0,sizeof gm);memset(&svm,0,sizeof svm);memset(&svc,0,sizeof svc);memset(&svd,0,sizeof svd);memset(&gv,0,sizeof gv);memset(&ga,0,sizeof ga);memset(&gg,0,sizeof gg);memset(&sysopt,0,sizeof sysopt);memset(&disp,0,sizeof disp);memset(&gd,0,sizeof gd);memset(&gh,0,sizeof gh);
 gi.invent=0;gt.thrownobj=gk.kickedobj=0;uchain=uamul=0;gu.urole.mnum=PM_TOURIST;gu.urace.mnum=PM_HUMAN;gu.urace.mummynum=PM_HUMAN_MUMMY;gu.urace.zombienum=PM_HUMAN_ZOMBIE;gu.urace.mnum=PM_HUMAN;gu.urole.name.m="Wizard";gu.urole.name.f="Witch";strcpy(svp.plname,"Tester");
 u.ux=10;u.uy=10;u.uhp=20;u.uhpmax=30;u.ulevel=5;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;u.ugrave_arise=NON_PM;u.uz.dnum=0;u.uz.dlevel=3;u.uhunger=900;svm.moves=100;urealtime.realtime=50;urealtime.start_timing=(1LL<<54)+7;svd.dungeon_topology.d_astral_level.dnum=8;svd.dungeon_topology.d_astral_level.dlevel=1;svd.dungeon_topology.d_tutorial_dnum=9;strcpy(svd.dungeons[0].dname,"Dungeons");
 WIN_MESSAGE=1;WIN_MAP=2;WIN_STATUS=3;WIN_INVEN=4;flags.sortloot='l';flags.sortpack=1;memset(flags.end_disclose,'n',6);flags.end_disclose[6]=0;
 windowprocs.win_clear_nhwindow=window_clear;windowprocs.win_wait_synch=window_sync;windowprocs.win_mark_synch=window_sync;windowprocs.win_exit_nhwindows=window_exit;windowprocs.win_create_nhwindow=window_create;windowprocs.win_display_nhwindow=window_display;windowprocs.win_destroy_nhwindow=window_destroy;windowprocs.win_putstr=window_putstr;windowprocs.win_raw_print=window_raw;windowprocs.win_outrip=window_rip;soundprocs.sound_exit_nhsound=sound_exit;
 gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<4;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].cham=NON_PM;monsters[i].mextra=&mextras[i];monsters[i].m_id=42+i;monsters[i].mhp=9;}for(int i=0;i<16;i++){nodes[i].quan=1;nodes[i].where=OBJ_FREE;nodes[i].oextra=&oextras[i];}
 gv.valuables[0].list=ga.amulets;gv.valuables[0].size=SIZE(ga.amulets);gv.valuables[1].list=gg.gems;gv.valuables[1].size=SIZE(gg.gems);static seenV rows[ROWNO][COLNO];static seenV*rowptr[ROWNO];for(int y=0;y<ROWNO;y++){rowptr[y]=rows[y];memset(rows[y],0,COLNO);}gv.viz_array=rowptr;
 rngstate=1;serial=10;heapfrees=allocs=exitstatus=callback_depth=callback_count=restorepos=0;tracebuf[0]=snapbuf[0]=streambuf[0]=inputbuf[0]=0;
#ifdef TELEPORT_REFERENCE_TU
 Schroedingers_cat=0;
#endif
}
void probe_item(int i,int typ,int cls,long quan,int next,int child){nodes[i].otyp=typ;nodes[i].oclass=cls;nodes[i].quan=quan;nodes[i].nobj=next<0?0:&nodes[next];nodes[i].cobj=child<0?0:&nodes[child];objects[typ].oc_class=cls;objects[typ].oc_cost=10;objects[typ].oc_name_idx=typ;obj_descr[typ].oc_name="named object";}
void probe_inventory(int i){gi.invent=i<0?0:&nodes[i];}void probe_equipment(int slot,int i){struct obj*o=i<0?0:&nodes[i];if(slot==0)uamul=o;else if(slot==1)uchain=o;else if(slot==2)gt.thrownobj=o;else gk.kickedobj=o;}
void probe_monster_setup(int pm,int cham,int bits){monsters[0].data=&mons[pm];monsters[0].cham=cham;monsters[0].minvis=bits&1;monsters[0].isshk=(bits>>1)&1;monsters[0].ispriest=(bits>>2)&1;monsters[0].isminion=(bits>>3)&1;monsters[0].female=(bits>>4)&1;monsters[0].m_ap_type=(bits>>5)&3;monsters[0].mappearance=PM_GHOST;mextras[0].mgivenname=(bits&128)?"Dudley":0;}
void probe_global(int which,long n){switch(which){case 0:flags.ignintr=n;break;case 1:flags.debug=n;break;case 2:flags.explore=n;break;case 3:iflags.window_inited=n;break;case 4:program_state.panicking=n;break;case 5:program_state.stopprint=n;break;case 6:u.uhp=n;break;case 7:u.uhpmax=n;break;case 8:u.uhunger=n;break;case 9:gm.multi=n;break;case 10:u.uswallow=n;u.ustuck=n?&monsters[0]:0;break;case 11:iflags.debug_fuzzer=n;break;case 12:gd.done_seq=n;break;case 13:gh.hero_seq=n;break;case 14:svm.moves=n;break;case 15:iflags.perm_invent=n;break;case 16:u.urexp=n;break;case 17:u.ugrave_arise=n;break;case 18:program_state.done_hup=n;break;case 19:sysopt.panictrace_gdb=n;break;case 20:u.uz.dnum=n;break;case 21:flags.tombstone=n;break;case 22:u.uhave.amulet=n;break;case 23:u.ualign.type=n;break;case 24:u.umoney0=n;break;case 25:flags.female=n;break;case 26:iflags.toptenwin=n;break;case 27:flags.paranoia_bits=n;break;case 28:program_state.something_worth_saving=n;break;case 29:nodes[0].oartifact=n;break;case 30:nodes[0].spe=n;break;case 31:flags.sortloot=n;break;}}
void probe_property(int i,long intrinsic,long extrinsic,long blocked){u.uprops[i].intrinsic=intrinsic;u.uprops[i].extrinsic=extrinsic;u.uprops[i].blocked=blocked;}
void probe_reason(const char*s,int mode){strcpy(gm.multireasonbuf,s);gm.multi_reason=mode?gm.multireasonbuf+(mode==2?3:0):0;}
void probe_disclosure(const char*s){snprintf(flags.end_disclose,sizeof flags.end_disclose,"%s",s);}
long probe_action(int op,int a,int b,int c,long n){long result=0;if(setjmp(exitpoint))return exitstatus;switch(op){case 0:done1(a);break;case 1:result=done2();break;case 2:done_intr(a);break;case 3:done_hangup(a);break;case 4:done_in_by(&monsters[0],a);break;case 5:fixup_death(a);break;case 6:panic("panic number %ld string %s",n,inputbuf);break;case 7:{char v=0;result=should_query_disclose_option(a,&v);result=(result<<8)|(uchar)v;}break;case 8:dump_everything(a,n);break;case 9:disclose(a,b);break;case 10:savelife(a);break;case 11:get_valuables(gi.invent);break;case 12:sort_valuables(ga.amulets,SIZE(ga.amulets));break;case 13:done_object_cleanup();break;case 14:artifact_score(gi.invent,a,b);break;case 15:result=fuzzer_savelife(a);break;case 16:done(a);break;case 17:really_done(a);break;case 18:container_contents(gi.invent,a,b,c);break;case 19:nh_terminate(a);break;case 20:delayed_killer(a,b,inputbuf);break;case 21:{struct kinfo*k=find_delayed_killer(a);result=k?k->format:-1;}break;case 22:dealloc_killer(find_delayed_killer(a));break;case 23:file.mode=a;save_killers(&file);break;case 24:restore_killers(&file);break;case 25:result=wordcount(inputbuf);break;case 26:{char out[4096]="prefix ";char*p=inputbuf;bel_copy1(&p,out);logmsg("copy:%s:%ld;",out,(long)(p-inputbuf));}break;case 27:{char*out=build_english_list(inputbuf);logmsg("english:%s;",out);free(out);}break;case 28:NH_abort(inputbuf);break;case 29:memset(ga.amulets,0xa5,sizeof ga.amulets);for(int i=0;i<SIZE(ga.amulets);i++){ga.amulets[i].typ=i;ga.amulets[i].count=(i*7)%13;}break;case 30:svk.killer.format=a;strcpy(svk.killer.name,inputbuf);break;}return result;}
const char*probe_snapshot(void){char*p=snapbuf;p+=sprintf(p,"hero:%d,%d,%d,%d,%d,%d,%ld,%ld,%d,%d,%d;",u.uhp,u.uhpmax,u.mh,u.ulevel,u.uhunger,u.ugrave_arise,u.urexp,u.usleep,u.umortality,u.ualign.type,u.uhave.amulet);p+=sprintf(p,"state:%d,%d,%d,%d,%d,%d,%d,%d;",program_state.gameover,program_state.panicking,program_state.stopprint,program_state.done_hup,program_state.exiting,program_state.in_moveloop,program_state.something_worth_saving,iflags.window_inited);p+=sprintf(p,"m:%ld,%s,%ld,%ld,%ld,%lld,%ld;",gm.multi,gm.multi_reason?gm.multi_reason:"NULL",gd.done_seq,gh.hero_seq,gd.done_money,urealtime.finish_time,urealtime.realtime);p+=sprintf(p,"killer:%d:%s;",svk.killer.format,svk.killer.name);for(struct kinfo*k=svk.killer.next;k;k=k->next)p+=sprintf(p,"k:%d:%d:%s;",k->id,k->format,k->name);for(int i=0;i<16;i++){struct obj*o=&nodes[i];p+=sprintf(p,"o%d:%d,%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d;",i,o->otyp,o->oclass,o->quan,o->known,o->bknown,o->dknown,o->rknown,o->cknown,o->lknown,o->where,o->ox,o->oy);}for(int i=0;i<SIZE(ga.amulets);i++)p+=sprintf(p,"a:%d,%ld;",ga.amulets[i].typ,ga.amulets[i].count);for(int i=0;i<SIZE(gg.gems);i++)p+=sprintf(p,"g:%d,%ld;",gg.gems[i].typ,gg.gems[i].count);for(int i=0;i<LAST_PROP+1;i++)p+=sprintf(p,"prop%d:%ld,%ld,%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);p+=sprintf(p,"flags:%d,%d,%d,%d,%d,%d,%d,%d;",iflags.debug_fuzzer,iflags.perm_invent,iflags.last_msg,disp.botl,disp.botlx,disp.time_botl,WIN_MAP,WIN_MESSAGE);unsigned digest=2166136261u;for(size_t i=0;i<sizeof ga.amulets;i++)digest=(digest^((unsigned char*)ga.amulets)[i])*16777619u;p+=sprintf(p,"bytes:%u;",digest);p+=sprintf(p,"mem:%d,%d;%u;",allocs,heapfrees,rngstate);return snapbuf;}
