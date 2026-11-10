#include "hack.h"
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(u) u;__typeof__(gy) gy;__typeof__(gm) gm;__typeof__(gn) gn;__typeof__(svk) svk;__typeof__(svm) svm;__typeof__(svq) svq;__typeof__(svc) svc;__typeof__(svl) svl;__typeof__(svt) svt;__typeof__(gt) gt;__typeof__(gb) gb;__typeof__(cg) cg;__typeof__(gi) gi;__typeof__(flags) flags;__typeof__(iflags) iflags;__typeof__(disp) disp;__typeof__(gv) gv;__typeof__(gu) gu;__typeof__(svd) svd;__typeof__(windowprocs) windowprocs;
struct obj *uwep,*uswapwep,*uarmh,*uarmf,*uamul;
winid WIN_MESSAGE=1;
const struct c_color_names c_color_names={.c_golden="golden",.c_blue="blue",.c_green="green"};
const struct c_common_strings c_common_strings={.c_You_can_move_again="You can move again.",.c_something="something"};
const struct Gender genders[]={{.he="he"},{.he="she"},{.he="it"}};
static struct obj items[16];static struct monst monsters[4];static struct kinfo killers[4];static NHFILE file;
static char buffers[8][BUFSZ],result[BUFSZ],trace[262144],snap[32768];static int integers[8],opts[96],seed=1;static long longs[8];static anything arguments[8];static void *growth;
static unsigned char saved[65536];static size_t saved_write,saved_read;static timer_element *removed;
static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long oid(const struct obj*p){return !p?-1:p>=items&&p<items+16?p-items:-3;}
static long mid(const struct monst*p){return !p?-1:p==&gy.youmonst?-2:p>=monsters&&p<monsters+4?p-monsters:-3;}
static void callback(int stage){if(opts[80]==stage){opts[80]=0;append("nested:%ld;",peek_timer(HATCH_EGG,&arguments[0]));}if(opts[81]==stage&&!growth){opts[81]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char*fmt,...){fprintf(stderr,"probe panic: %s\n",fmt);abort();}
void impossible(const char*fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
#define MSG(fn) void fn(const char*fmt,...){char b[8192];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#fn ":%s;",b);callback(1);}
MSG(pline)MSG(Norep)MSG(You)MSG(Your)MSG(You_feel)MSG(You_hear)MSG(You_see)MSG(urgent_pline)MSG(verbalize)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char*f,int l,const char*n){append("caller:%s:%d:%s;",f,l,n);}
int(rn2)(int n){seed=(int)((unsigned)seed*1664525U+1013904223U);append("rn2:%d;",n);return n?(unsigned)seed%(unsigned)n:0;}
int(rnd)(int n){append("rnd:%d;",n);return n?1+(rn2)(n):1;}
int(d)(int n,int x){int v=0;append("d:%d:%d;",n,x);for(int i=0;i<n;i++)v+=(rnd)(x);return v;}
static winid newwin(int t){append("create:%d;",t);return opts[2]?WIN_ERR:1;}
static void displaywin(winid w,boolean b){append("display:%d:%d;",w,b);}
static void destroywin(winid w){append("destroy:%d;",w);}
static void putwin(winid w,int a,const char*t){append("put:%d:%d:%s;",w,a,t);callback(2);}
static void savebytes(const void*p,size_t n){memcpy(saved+saved_write,p,n);saved_write+=n;}
static void readbytes(void*p,size_t n){memcpy(p,saved+saved_read,n);saved_read+=n;}
void sfo_int(NHFILE*n,int*p,const char*k){(void)n;append("out-int:%s:%d;",k,*p);savebytes(p,sizeof*p);callback(3);}
void sfi_int(NHFILE*n,int*p,const char*k){(void)n;readbytes(p,sizeof*p);append("in-int:%s:%d;",k,*p);if(opts[37])*p=opts[38];callback(4);}
void sfo_ulong(NHFILE*n,ulong*p,const char*k){(void)n;append("out-long:%s:%lu;",k,*p);savebytes(p,sizeof*p);callback(3);}
void sfi_ulong(NHFILE*n,ulong*p,const char*k){(void)n;readbytes(p,sizeof*p);append("in-long:%s:%lu;",k,*p);callback(4);}
void sfo_fe(NHFILE*n,struct fe*p,const char*k){(void)n;append("out-timer:%s:%lu:%ld:%d:%d:%llu:%d;",k,p->tid,p->timeout,p->kind,p->func_index,(unsigned long long)p->arg.a_uint,p->needs_fixup);savebytes(p,sizeof*p);p->timeout+=opts[36];callback(3);}
void sfi_fe(NHFILE*n,struct fe*p,const char*k){(void)n;readbytes(p,sizeof*p);append("in-timer:%s:%lu:%ld:%d:%d:%llu:%d;",k,p->tid,p->timeout,p->kind,p->func_index,(unsigned long long)p->arg.a_uint,p->needs_fixup);callback(4);}
char * Monnam(struct monst * a0){append("Monnam:");append("m%ld;",mid(a0));return "Monster";}
boolean Popeye(int a0){append("Popeye:");append("%lld;",(long long)a0);return opts[4];}
char * Shk_Your(char * a0,struct obj * a1){append("Shk_Your:");append("o%ld;",oid(a1));strcpy(a0,"Your ");return a0;}
char * Yname2(struct obj * a0){append("Yname2:");append("o%ld;",oid(a0));return "Object";}
char * a_monnam(struct monst * a0){append("a_monnam:");append("m%ld;",mid(a0));return "a monster";}
schar acurr(int a0){append("acurr:");append("%lld;",(long long)a0);return opts[3];}
boolean adjattrib(int a0,int a1,int a2){append("adjattrib:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);return 0;}
char * an(const char * a0){append("an:");return "an object";}
boolean any_visible_region(void){append("any_visible_region:");return 0;}
int arti_light_radius(struct obj * a0){append("arti_light_radius:");append("o%ld;",oid(a0));return opts[15];}
boolean artifact_light(struct obj * a0){append("artifact_light:");append("o%ld;",oid(a0));return opts[14];}
int big_to_little(int a0){append("big_to_little:");append("%lld;",(long long)a0);return a0;}
const char * body_part(int a0){append("body_part:");append("%lld;",(long long)a0);return "body";}
void buzz(int a0,int a1,coordxy a2,coordxy a3,int a4,int a5){append("buzz:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);append("%lld;",(long long)a4);append("%lld;",(long long)a5);}
int candle_light_range(struct obj * a0){append("candle_light_range:");append("o%ld;",oid(a0));return opts[16];}
int canseemon(struct monst * a0){append("canseemon:");append("m%ld;",mid(a0));return opts[5];}
boolean cantvomit(struct permonst * a0){append("cantvomit:");append("pm%ld;",a0?a0-mons:-1L);return opts[6];}
struct obj * carrying(int a0){append("carrying:");append("%lld;",(long long)a0);return opts[30]?&items[0]:NULL;}
void confdir(boolean a0){append("confdir:");append("%lld;",(long long)a0);}
void container_weight(struct obj * a0){append("container_weight:");append("o%ld;",oid(a0));a0->owt=123;}
const char * cry_sound(struct monst * a0){append("cry_sound:");append("m%ld;",mid(a0));return "cry";}
void dealloc_killer(struct kinfo * a0){append("dealloc_killer:");if(a0)a0->id=0;}
void deferred_decor(boolean a0){append("deferred_decor:");append("%lld;",(long long)a0);}
void del_light_source(int a0,union any * a1){append("del_light_source:");append("%lld;",(long long)a0);}
void dismount_steed(int a0){append("dismount_steed:");append("%lld;",(long long)a0);}
char * doname(struct obj * a0){append("doname:");append("o%ld;",oid(a0));return "object";}
void done(int a0){append("done:");append("%lld;",(long long)a0);}
boolean eating_dangerous_corpse(int a0){append("eating_dangerous_corpse:");append("%lld;",(long long)a0);return opts[13];}
boolean enexto(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){append("enexto:");append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("pm%ld;",a3?a3-mons:-1L);a0->x=a1+1;a0->y=a2;return opts[23];}
void exercise(int a0,boolean a1){append("exercise:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
void find_ac(void){append("find_ac:");}
struct kinfo * find_delayed_killer(int a0){append("find_delayed_killer:");append("%lld;",(long long)a0);return opts[27]?&killers[0]:NULL;}
struct obj * find_oid(unsigned a0){append("find_oid:");append("%lld;",(long long)a0);for(int i=0;i<16;i++)if(items[i].o_id==a0)return &items[i];return NULL;}
int float_down(long a0,long a1){append("float_down:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[LEVITATION].intrinsic=0;return 1;}
boolean get_obj_location(struct obj * a0,coordxy * a1,coordxy * a2,int a3){append("get_obj_location:");append("o%ld;",oid(a0));append("%lld;",(long long)a3);callback(6);if(!opts[26])return 0;*a1=a0->ox;*a2=a0->oy;return 1;}
const char * hcolor(const char * a0){append("hcolor:");return (char*)a0;}
void heal_legs(int a0){append("heal_legs:");append("%lld;",(long long)a0);}
boolean hideunder(struct monst * a0){append("hideunder:");append("m%ld;",mid(a0));return opts[21];}
void hurtle(int a0,int a1,int a2,boolean a3){append("hurtle:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);}
void incr_itimeout(long * a0,int a1){append("incr_itimeout:");append("%lld;",(long long)a1);*a0+=a1;}
void instapetrify(const char * a0){append("instapetrify:");}
int inv_weight(void){append("inv_weight:");return opts[9];}
boolean is_fainted(void){append("is_fainted:");return opts[12];}
boolean is_ice(coordxy a0,coordxy a1){append("is_ice:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return opts[17];}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return opts[18];}
boolean is_pool_or_lava(coordxy a0,coordxy a1){append("is_pool_or_lava:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return opts[19];}
int isok(coordxy a0,coordxy a1){append("isok:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
int little_to_big(int a0){append("little_to_big:");append("%lld;",(long long)a0);return a0;}
const char * locomotion(const struct permonst * a0,const char * a1){append("locomotion:");return (char*)a1;}
boolean lookup_id_mapping(unsigned a0,unsigned * a1){append("lookup_id_mapping:");append("%lld;",(long long)a0);*a1=a0+opts[28];return opts[29];}
char * m_monnam(struct monst * a0){append("m_monnam:");append("m%ld;",mid(a0));return "monster";}
void make_blinded(long a0,boolean a1){append("make_blinded:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[BLINDED].intrinsic=a0;}
void make_confused(long a0,boolean a1){append("make_confused:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[CONFUSION].intrinsic=a0;}
void make_deaf(long a0,boolean a1){append("make_deaf:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[DEAF].intrinsic=a0;}
void make_glib(int a0){append("make_glib:");append("%lld;",(long long)a0);u.uprops[GLIB].intrinsic=a0;}
boolean make_hallucinated(long a0,boolean a1,long a2){append("make_hallucinated:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);u.uprops[HALLUC].intrinsic=a0;return 1;}
void make_sick(long a0,const char * a1,boolean a2,int a3){append("make_sick:");append("%lld;",(long long)a0);append("%lld;",(long long)a2);append("%lld;",(long long)a3);u.uprops[SICK].intrinsic=a0;}
void make_slimed(long a0,const char * a1){append("make_slimed:");append("%lld;",(long long)a0);u.uprops[SLIMED].intrinsic=a0;}
void make_stoned(long a0,const char * a1,int a2,const char * a3){append("make_stoned:");append("%lld;",(long long)a0);append("%lld;",(long long)a2);u.uprops[STONED].intrinsic=a0;}
void make_stunned(long a0,boolean a1){append("make_stunned:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[STUNNED].intrinsic=a0;}
void make_vomiting(long a0,boolean a1){append("make_vomiting:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[VOMITING].intrinsic=a0;}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:");append("pm%ld;",a0?a0-mons:-1L);append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);callback(5);if(opts[24])return NULL;monsters[3].data=a0;monsters[3].mx=a1;monsters[3].my=a2;return &monsters[3];}
char * makeplural(const char * a0){append("makeplural:");return "bodies";}
void maybe_unhide_at(coordxy a0,coordxy a1){append("maybe_unhide_at:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
anything * monst_to_any(struct monst * a0){append("monst_to_any:");append("m%ld;",mid(a0));gt.tmp_anything=cg.zeroany;gt.tmp_anything.a_monst=a0;return &gt.tmp_anything;}
void morehungry(int a0){append("morehungry:");append("%lld;",(long long)a0);u.uhunger+=a0;}
int name_to_mon(const char * a0,int * a1){append("name_to_mon:");return 0;}
void new_light_source(coordxy a0,coordxy a1,int a2,int a3,union any * a4){append("new_light_source:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);}
void newsym(coordxy a0,coordxy a1){append("newsym:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
void nomul(int a0){append("nomul:");append("%lld;",(long long)a0);gm.multi=a0;}
void obfree(struct obj * a0,struct obj * a1){append("obfree:");append("o%ld;",oid(a0));append("o%ld;",oid(a1));a0->where=OBJ_DELETED;callback(8);}
void obj_extract_self(struct obj * a0){append("obj_extract_self:");append("o%ld;",oid(a0));a0->where=OBJ_FREE;}
anything * obj_to_any(struct obj * a0){append("obj_to_any:");append("o%ld;",oid(a0));gt.tmp_anything=cg.zeroany;gt.tmp_anything.a_obj=a0;return &gt.tmp_anything;}
boolean on_level(d_level * a0,d_level * a1){append("on_level:");return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
int polymon(int a0){append("polymon:");append("%lld;",(long long)a0);u.umonnum=a0;gy.youmonst.data=&mons[a0];return opts[22];}
int pronoun_gender(struct monst * a0,unsigned a1){append("pronoun_gender:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);return opts[33];}
boolean region_danger(void){append("region_danger:");return opts[7];}
void rehumanize(void){append("rehumanize:");}
void restartcham(void){append("restartcham:");}
char * rndmonnam(char * a0){append("rndmonnam:");return "monster";}
void see_monsters(void){append("see_monsters:");}
void set_itimeout(long * a0,long a1){append("set_itimeout:");append("%lld;",(long long)a1);*a0=(*a0&~TIMEOUT)|(a1&TIMEOUT);}
void set_mimic_blocking(void){append("set_mimic_blocking:");}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){append("sobj_at:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);return opts[31]?&items[1]:NULL;}
void spoteffects(boolean a0){append("spoteffects:");append("%lld;",(long long)a0);}
int stone_luck(boolean a0){append("stone_luck:");append("%lld;",(long long)a0);return opts[10];}
void stop_occupation(void){append("stop_occupation:");}
boolean stuck_in_wall(void){append("stuck_in_wall:");return opts[8];}
const char * surface(coordxy a0,coordxy a1){append("surface:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return "surface";}
boolean tamedog(struct monst * a0,struct obj * a1,boolean a2){append("tamedog:");append("m%ld;",mid(a0));append("o%ld;",oid(a1));append("%lld;",(long long)a2);a0->mtame=1;return opts[25];}
char * the(const char * a0){append("the:");return (char*)a0;}
void toggle_displacement(struct obj * a0,long a1,boolean a2){append("toggle_displacement:");append("o%ld;",oid(a0));append("%lld;",(long long)a1);append("%lld;",(long long)a2);}
boolean unconscious(void){append("unconscious:");return opts[11];}
void update_inventory(void){append("update_inventory:");}
void useup(struct obj * a0){append("useup:");append("o%ld;",oid(a0));a0->quan--;callback(7);}
void useupall(struct obj * a0){append("useupall:");append("o%ld;",oid(a0));a0->quan=0;callback(7);}
void visible_region_summary(winid a0){append("visible_region_summary:");append("%lld;",(long long)a0);}
void vomit(void){append("vomit:");}
char * vtense(const char * a0,const char * a1){append("vtense:");return (char*)a1;}
void wake_nearby(boolean a0){append("wake_nearby:");append("%lld;",(long long)a0);}
int weight(struct obj * a0){append("weight:");append("o%ld;",oid(a0));return opts[20];}
struct obj * which_armor(struct monst * a0,long a1){append("which_armor:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);return opts[32]?&items[2]:NULL;}
void wielding_corpse(struct obj * a0,struct obj * a1,boolean a2){append("wielding_corpse:");append("o%ld;",oid(a0));append("o%ld;",oid(a1));append("%lld;",(long long)a2);}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){append("x_monnam:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);append("%lld;",(long long)a3);append("%lld;",(long long)a4);return "the monster";}
char * xname(struct obj * a0){append("xname:");append("o%ld;",oid(a0));return "object";}
void you_unwere(boolean a0){append("you_unwere:");append("%lld;",(long long)a0);}
void rot_organic(anything*a,long t){append("rot_organic:%ld;",t);if(opts[34]){opts[34]=0;start_timer(opts[35],TIMER_LEVEL,MELT_ICE_AWAY,&arguments[7]);}callback(9);}
void rot_corpse(anything*a,long t){append("rot_corpse:%ld;",t);if(opts[34]){opts[34]=0;start_timer(opts[35],TIMER_LEVEL,MELT_ICE_AWAY,&arguments[7]);}callback(9);}
void revive_mon(anything*a,long t){append("revive_mon:%ld;",t);if(opts[34]){opts[34]=0;start_timer(opts[35],TIMER_LEVEL,MELT_ICE_AWAY,&arguments[7]);}callback(9);}
void zombify_mon(anything*a,long t){append("zombify_mon:%ld;",t);if(opts[34]){opts[34]=0;start_timer(opts[35],TIMER_LEVEL,MELT_ICE_AWAY,&arguments[7]);}callback(9);}
void fig_transform(anything*a,long t){append("fig_transform:%ld;",t);if(opts[34]){opts[34]=0;start_timer(opts[35],TIMER_LEVEL,MELT_ICE_AWAY,&arguments[7]);}callback(9);}
void shrink_glob(anything*a,long t){append("shrink_glob:%ld;",t);if(opts[34]){opts[34]=0;start_timer(opts[35],TIMER_LEVEL,MELT_ICE_AWAY,&arguments[7]);}callback(9);}
void melt_ice_away(anything*a,long t){append("melt_ice_away:%ld;",t);if(opts[34]){opts[34]=0;start_timer(opts[35],TIMER_LEVEL,MELT_ICE_AWAY,&arguments[7]);}callback(9);}

#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/timeout.c"
#else
extern void teleport_timeout_test_levitation_dialogue(void);
#define levitation_dialogue teleport_timeout_test_levitation_dialogue
extern void teleport_timeout_test_stoned_dialogue(void);
#define stoned_dialogue teleport_timeout_test_stoned_dialogue
extern void teleport_timeout_test_see_lamp_flicker(struct obj *obj, const char *tailer);
#define see_lamp_flicker teleport_timeout_test_see_lamp_flicker
extern void teleport_timeout_test_region_dialogue(void);
#define region_dialogue teleport_timeout_test_region_dialogue
extern void teleport_timeout_test_lantern_message(struct obj *obj);
#define lantern_message teleport_timeout_test_lantern_message
extern void teleport_timeout_test_phaze_dialogue(void);
#define phaze_dialogue teleport_timeout_test_phaze_dialogue
extern void teleport_timeout_test_vomiting_dialogue(void);
#define vomiting_dialogue teleport_timeout_test_vomiting_dialogue
extern boolean teleport_timeout_test_timer_is_local(timer_element *timer);
#define timer_is_local teleport_timeout_test_timer_is_local
extern void teleport_timeout_test_sickness_dialogue(void);
#define sickness_dialogue teleport_timeout_test_sickness_dialogue
extern void teleport_timeout_test_print_queue(winid win, timer_element *base);
#define print_queue teleport_timeout_test_print_queue
extern void teleport_timeout_test_cleanup_burn(anything *arg, long expire_time);
#define cleanup_burn teleport_timeout_test_cleanup_burn
extern void teleport_timeout_test_sleep_dialogue(void);
#define sleep_dialogue teleport_timeout_test_sleep_dialogue
extern void teleport_timeout_test_write_timer(NHFILE *nhfp, timer_element *timer);
#define write_timer teleport_timeout_test_write_timer
extern const char * teleport_timeout_test_kind_name(short kind);
#define kind_name teleport_timeout_test_kind_name
extern void teleport_timeout_test_choke_dialogue(void);
#define choke_dialogue teleport_timeout_test_choke_dialogue
extern void teleport_timeout_test_done_timeout(int how, int which);
#define done_timeout teleport_timeout_test_done_timeout
extern boolean teleport_timeout_test_mon_is_local(struct monst *mon);
#define mon_is_local teleport_timeout_test_mon_is_local
extern timer_element * teleport_timeout_test_remove_timer(
    timer_element **base,
    short func_index,
    anything *arg);
#define remove_timer teleport_timeout_test_remove_timer
extern void teleport_timeout_test_slime_dialogue(void);
#define slime_dialogue teleport_timeout_test_slime_dialogue
extern int teleport_timeout_test_maybe_write_timer(NHFILE *nhfp, int range, boolean write_it);
#define maybe_write_timer teleport_timeout_test_maybe_write_timer
extern void teleport_timeout_test_slip_or_trip(void);
#define slip_or_trip teleport_timeout_test_slip_or_trip
extern void teleport_timeout_test_insert_timer(timer_element *gnu);
#define insert_timer teleport_timeout_test_insert_timer
extern void teleport_timeout_test_slimed_to_death(struct kinfo *kptr);
#define slimed_to_death teleport_timeout_test_slimed_to_death
#endif
#include "tu-timeout-layout.h"
int probe_layout_count(void){return SIZE(timeout_layout);}
const char *probe_layout_name(int i){return timeout_layout[i].name;}
size_t probe_layout_value(int i){return timeout_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_trace(void){return trace;}
const char *probe_result(void){return result;}
void probe_option(int i,int v){opts[i]=v;}
void probe_seed(int v){seed=v;}
void probe_clear(void){trace[0]=result[0]=0;}
void *probe_obj(int i){return i<0?NULL:&items[i];}
void *probe_mon(int i){return i<0?NULL:&monsters[i];}
void *probe_buffer(int i){return buffers[i];}
void *probe_int(int i){return &integers[i];}
void *probe_long(int i){return &longs[i];}
void *probe_arg(int i){return &arguments[i];}
void probe_argument(int i,int kind,long val){arguments[i]=cg.zeroany;if(kind==0)arguments[i].a_obj=val<0?NULL:&items[val];else if(kind==1)arguments[i].a_monst=val<0?NULL:&monsters[val];else arguments[i].a_long=val;}
static timer_element *timer_at(int n){if(n<0){timer_element*t=calloc(1,sizeof*t);t->tid=888;t->timeout=104;t->kind=TIMER_LEVEL;t->func_index=MELT_ICE_AWAY;t->arg.a_long=0;return t;}timer_element*t=gt.timer_base;for(;n>0&&t;n--)t=t->next;return t;}
void *probe_timer(int i){return timer_at(i);}
void probe_saved_rewind(void){saved_read=0;}
void probe_global(int key,long v){switch(key){case 0:svm.moves=v;break;case 1:svt.timer_id=v;break;case 2:file.mode=v;break;case 3:file.ftype=v;break;case 4:gm.multi=v;break;case 5:flags.moonphase=v;break;case 6:flags.friday13=v;break;case 7:flags.female=v;break;case 8:u.uluck=v;break;case 9:u.uinvulnerable=v;break;case 10:u.uburied=v;break;case 11:u.usick_type=v;break;case 12:svl.level.flags.stormy=v;break;case 13:svq.quest_status.killed_leader=v;break;case 14:gu.urole.mnum=v;break;case 15:u.ugangr=v;break;case 16:u.mtimedone=v;break;case 17:u.ucreamed=v;break;case 18:u.usptime=v;break;case 19:u.uspmtime=v;break;case 20:u.uspellprot=v;break;case 21:u.ugallop=v;break;case 22:u.uswldtim=v;break;case 23:u.uinvault=v;break;case 24:iflags.last_msg=v;break;case 25:iflags.defer_decor=v;break;case 26:u.umoved=v;break;case 27:u.uhs=v;break;case 28:u.usteed=v<0?NULL:&monsters[v];break;case 29:gm.migrating_mons=v<0?NULL:&monsters[v];break;case 30:gm.mydogs=v<0?NULL:&monsters[v];break;case 31:svl.level.flags.stasis_until=v;break;case 32:u.umonnum=v;break;case 33:u.umonster=v;break;case 34:killers[0].format=v;break;case 35:svd.dungeon_topology.d_water_level.dnum=v;break;case 36:svd.dungeon_topology.d_water_level.dlevel=v;break;}}
void probe_property(int p,long in,long ex,long block){u.uprops[p].intrinsic=in;u.uprops[p].extrinsic=ex;u.uprops[p].blocked=block;}
void probe_equipment(int i,int n){struct obj*o=n<0?NULL:&items[n];switch(i){case 0:uwep=o;break;case 1:uswapwep=o;break;case 2:uarmh=o;break;case 3:uarmf=o;break;case 4:uamul=o;break;}}
void probe_item(int n,int key,long v){struct obj*o=&items[n];switch(key){case 0:o->otyp=v;break;case 1:o->where=v;break;case 2:o->quan=v;break;case 3:o->age=v;break;case 4:o->spe=v;break;case 5:o->timed=v;break;case 6:o->lamplit=v;break;case 7:o->cursed=v;break;case 8:o->dknown=v;break;case 9:o->odiluted=v;break;case 10:o->corpsenm=v;break;case 11:o->ocontainer=v<0?NULL:&items[v];break;case 12:o->ocarry=v<0?NULL:&monsters[v];break;case 13:o->o_id=v;break;case 14:o->ox=v;break;case 15:o->oy=v;break;case 16:o->owornmask=v;break;case 17:o->nobj=v<0?NULL:&items[v];break;}}
void probe_monset(int n,int key,long v){struct monst*m=&monsters[n];switch(key){case 0:m->data=&mons[v];break;case 1:m->nmon=v<0?NULL:&monsters[v];break;case 2:m->wormno=v;break;case 3:m->mtame=v;break;case 4:m->mx=v;break;case 5:m->my=v;break;}}
void probe_terrain(int x,int y,int typ,int mask){levl[x][y].typ=typ;levl[x][y].drawbridgemask=mask;}
void probe_reset(void){
 if(removed){free(removed);removed=NULL;}timer_element*t=gt.timer_base;while(t){timer_element*n=t->next;free(t);t=n;}if(growth){free(growth);growth=0;}
 memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&svk,0,sizeof svk);memset(&svm,0,sizeof svm);memset(&svq,0,sizeof svq);memset(&svc,0,sizeof svc);memset(&svl,0,sizeof svl);memset(&svt,0,sizeof svt);memset(&gt,0,sizeof gt);memset(&gb,0,sizeof gb);memset(&gu,0,sizeof gu);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);
 memset(items,0,sizeof items);memset(monsters,0,sizeof monsters);memset(killers,0,sizeof killers);memset(opts,0,sizeof opts);memset(arguments,0,sizeof arguments);memset(buffers,0,sizeof buffers);memset(integers,0,sizeof integers);memset(longs,0,sizeof longs);
 objects_globals_init();monst_globals_init();gy.youmonst.data=&mons[PM_HUMAN];u.umonnum=u.umonster=PM_HUMAN;gu.urole.mnum=PM_HUMAN;u.ux=10;u.uy=8;u.ux0=9;u.uy0=8;u.uz.dnum=u.uz.dlevel=1;svm.moves=100;svt.timer_id=1;u.uhs=1;
 for(int i=0;i<16;i++){items[i].o_id=i+100;items[i].otyp=EGG;items[i].where=OBJ_INVENT;items[i].quan=1;items[i].age=200;items[i].ox=10;items[i].oy=8;items[i].corpsenm=PM_GIANT_ANT;}
 for(int i=0;i<4;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].m_id=i+10;monsters[i].mhp=10;monsters[i].mx=11;monsters[i].my=8;}
 for(int i=0;i<8;i++)arguments[i].a_obj=&items[i];arguments[7].a_long=(10L<<16)|8L;
 for(int y=0;y<ROWNO;y++){visrows[y]=visibility[y];for(int x=0;x<COLNO;x++){visibility[y][x]=IN_SIGHT|COULD_SEE;levl[x][y].typ=ROOM;}}gv.viz_array=visrows;svl.level.objects[10][8]=NULL;
 uwep=uswapwep=uarmh=uarmf=uamul=NULL;windowprocs.win_create_nhwindow=newwin;windowprocs.win_display_nhwindow=displaywin;windowprocs.win_destroy_nhwindow=destroywin;windowprocs.win_putstr=putwin;
 memset(&file,0,sizeof file);file.mode=WRITING;opts[0]=1;opts[3]=10;opts[5]=1;opts[23]=1;opts[25]=1;opts[26]=1;opts[29]=1;opts[33]=2;opts[16]=2;seed=1;saved_write=saved_read=0;trace[0]=result[0]=0;
}
const char *probe_snapshot(void){snap[0]=0;char*b=snap;size_t left=sizeof snap;
#define ADD(...) do{int n=snprintf(b,left,__VA_ARGS__);b+=n;left-=n;}while(0)
 ADD("moves:%ld,id:%lu,multi:%ld,msg:%s,reason:%s,bot:%d,save:%zu:%zu;",svm.moves,svt.timer_id,gm.multi,gn.nomovemsg?gn.nomovemsg:"[NULL]",gm.multi_reason?gm.multi_reason:"[NULL]",disp.botl,saved_write,saved_read);
 ADD("u:%d:%d:%d:%d:%d:%d:%d:%ld:%ld:%u:%d:killer:%d:%s;",u.uluck,u.mtimedone,u.ucreamed,u.usptime,u.uspmtime,u.uspellprot,u.usick_type,u.ugallop,u.usleep,u.uswldtim,u.uinvault,svk.killer.format,svk.killer.name);
 for(int i=0;i<SIZE(u.uprops);i++)if(u.uprops[i].intrinsic||u.uprops[i].extrinsic||u.uprops[i].blocked)ADD("p%d:%ld:%ld:%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);
 for(int i=0;i<16;i++){struct obj*o=&items[i];ADD("o%d:%d:%d:%ld:%ld:%d:%d:%d:%u:%ld:%ld:%ld;",i,o->otyp,o->where,o->quan,o->age,o->spe,o->timed,o->lamplit,o->owt,o->owornmask,oid(o->ocontainer),mid(o->ocarry));}
 ADD("form:%d:%d:%d:hero:%d:%d;",u.umonnum,gy.youmonst.m_ap_type,gy.youmonst.mappearance,gu.urole.mnum,iflags.last_msg);
 for(int i=0;i<4;i++)ADD("m%d:%ld:%d:%d:%d:%u;",i,monsters[i].data-mons,monsters[i].mx,monsters[i].my,monsters[i].mtame,monsters[i].wormno);
 for(int i=0;i<NUMMONS;i++)if(svm.mvitals[i].mvflags)ADD("v%d:%u;",i,svm.mvitals[i].mvflags);
 for(timer_element*t=gt.timer_base;t;t=t->next){ADD("t:%lu:%ld:%d:%d:%u:",t->tid,t->timeout,t->kind,t->func_index,t->needs_fixup);if(t->needs_fixup)ADD("id%u;",t->arg.a_uint);else if(t->kind==TIMER_OBJECT)ADD("obj%ld;",oid(t->arg.a_obj));else if(t->kind==TIMER_MONSTER)ADD("mon%ld;",mid(t->arg.a_monst));else ADD("bits%llu;",(unsigned long long)t->arg.a_long);}
 for(int i=0;i<8;i++)ADD("out%d:%d:%ld;",i,integers[i],longs[i]);
#undef ADD
 return snap;}
void probe_invoke(int op,long a,long b,long c,long d){result[0]=0;switch(op){
case 0:{const char*p=property_by_index(a,(b<0?NULL:&integers[b]));snprintf(result,sizeof result,"%s",p?p:"[NULL]");break;}
case 1:{stoned_dialogue();break;}
case 2:{vomiting_dialogue();break;}
case 3:{sleep_dialogue();break;}
case 4:{choke_dialogue();break;}
case 5:{sickness_dialogue();break;}
case 6:{levitation_dialogue();break;}
case 7:{slime_dialogue();break;}
case 8:{burn_away_slime();break;}
case 9:{slimed_to_death((a<0?NULL:&killers[a]));break;}
case 10:{phaze_dialogue();break;}
case 11:{region_dialogue();break;}
case 12:{done_timeout(a,b);break;}
case 13:{nh_timeout();break;}
case 14:{fall_asleep(a,b);break;}
case 15:{attach_egg_hatch_timeout((struct obj*)probe_obj(a),b);break;}
case 16:{kill_egg((struct obj*)probe_obj(a));break;}
case 17:{hatch_egg(&arguments[a],b);break;}
case 18:{learn_egg_type(a);break;}
case 19:{attach_fig_transform_timeout((struct obj*)probe_obj(a));break;}
case 20:{slip_or_trip();break;}
case 21:{see_lamp_flicker((struct obj*)probe_obj(a),(const char*)"timer:%ld");break;}
case 22:{lantern_message((struct obj*)probe_obj(a));break;}
case 23:{burn_object(&arguments[a],b);break;}
case 24:{begin_burn((struct obj*)probe_obj(a),b);break;}
case 25:{end_burn((struct obj*)probe_obj(a),b);break;}
case 26:{cleanup_burn(&arguments[a],b);break;}
case 27:{do_storms();break;}
case 28:{const char*p=kind_name(a);snprintf(result,sizeof result,"%s",p?p:"[NULL]");break;}
case 29:{print_queue(a,timer_at(b));break;}
case 30:{snprintf(result,sizeof result,"%lld",(long long)wiz_timeout_queue());break;}
case 31:{timer_sanity_check();break;}
case 32:{run_timers();break;}
case 33:{snprintf(result,sizeof result,"%lld",(long long)start_timer(a,b,c,&arguments[d]));break;}
case 34:{snprintf(result,sizeof result,"%lld",(long long)stop_timer(a,&arguments[b]));break;}
case 35:{snprintf(result,sizeof result,"%lld",(long long)peek_timer(a,&arguments[b]));break;}
case 36:{obj_move_timers((struct obj*)probe_obj(a),(struct obj*)probe_obj(b));break;}
case 37:{obj_split_timers((struct obj*)probe_obj(a),(struct obj*)probe_obj(b));break;}
case 38:{obj_stop_timers((struct obj*)probe_obj(a));break;}
case 39:{snprintf(result,sizeof result,"%lld",(long long)obj_has_timer((struct obj*)probe_obj(a),b));break;}
case 40:{spot_stop_timers(a,b,c);break;}
case 41:{snprintf(result,sizeof result,"%lld",(long long)spot_time_expires(a,b,c));break;}
case 42:{snprintf(result,sizeof result,"%lld",(long long)spot_time_left(a,b,c));break;}
case 43:{insert_timer(timer_at(a));break;}
case 44:{timer_element*p=remove_timer(&gt.timer_base,b,&arguments[c]);snprintf(result,sizeof result,"%lu",p?p->tid:0UL);if(removed)free(removed);removed=p;break;}
case 45:{write_timer(&file,timer_at(b));break;}
case 46:{snprintf(result,sizeof result,"%lld",(long long)obj_is_local((struct obj*)probe_obj(a)));break;}
case 47:{snprintf(result,sizeof result,"%lld",(long long)mon_is_local((struct monst*)probe_mon(a)));break;}
case 48:{snprintf(result,sizeof result,"%lld",(long long)timer_is_local(timer_at(a)));break;}
case 49:{snprintf(result,sizeof result,"%lld",(long long)maybe_write_timer(&file,b,c));break;}
case 50:{save_timers(&file,b);break;}
case 51:{restore_timers(&file,b,c);break;}
case 52:{timer_stats((const char*)"timer:%ld",buffers[b],&longs[c],&longs[d]);break;}
case 53:{relink_timers(a);break;}
default:abort();}}
int probe_table_count(int i){
#ifdef TELEPORT_REFERENCE_TU
return i==0?SIZE(propertynames):i==1?SIZE(timeout_funcs):0;
#else
(void)i;return 0;
#endif
}
const char *probe_table_text(int i,int n){
#ifdef TELEPORT_REFERENCE_TU
return i==0?propertynames[n].prop_name:timeout_funcs[n].name;
#else
(void)i;(void)n;return NULL;
#endif
}
