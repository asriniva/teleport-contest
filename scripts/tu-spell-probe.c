#include "hack.h"
#include "artifact.h"
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(u) u;__typeof__(gy) gy;__typeof__(svc) svc;__typeof__(go) go;__typeof__(gm) gm;__typeof__(gn) gn;__typeof__(gi) gi;__typeof__(svm) svm;__typeof__(svs) svs;__typeof__(gs) gs;__typeof__(svb) svb;__typeof__(gu) gu;__typeof__(gb) gb;__typeof__(cg) cg;__typeof__(flags) flags;__typeof__(iflags) iflags;__typeof__(disp) disp;__typeof__(svl) svl;__typeof__(gv) gv;__typeof__(svd) svd;__typeof__(windowprocs) windowprocs;
struct obj *uwep,*uarm,*uarmc,*uarmh,*uarmg,*uarmf,*uarms,*ublindf;
winid WIN_MESSAGE=1;
const glyph_info nul_glyphinfo={0};
const schar xdir[N_DIRS_Z]={-1,-1,0,1,1,1,0,-1,0,0};
const schar ydir[N_DIRS_Z]={0,-1,-1,-1,0,1,1,1,0,0};
const char ynchars[]="yn";
const char quitchars[]=" \r\n\033";
const struct c_color_names c_color_names={.c_golden="golden"};
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind.",.c_something="something",.c_nothing_happens="Nothing happens."};
const struct Gender genders[]={{.him="him"},{.him="her"}};
static struct obj items[16];static struct monst monsters[3];static char buffers[8][BUFSZ];static coord position;static int integers[8];
static void (*hilite)(boolean);static boolean (*center)(coordxy,coordxy);
static int opts[96],seed=1,selection_count;static void *growth;static char trace[262144],result[BUFSZ],snap[32768];static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static int unrelated_occupation(void){return -7;}
static long oid(const struct obj*p){return !p?-1:p>=items&&p<items+16?p-items:-3;}
static long mid(const struct monst*p){return !p?-1:p==&gy.youmonst?-2:p>=monsters&&p<monsters+3?p-monsters:-3;}
static void callback(int stage){if(opts[80]==stage){opts[80]=0;append("nested:%d;",num_spells());}if(opts[81]==stage&&!growth){opts[81]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char *fmt,...){(void)fmt;abort();}
void impossible(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
#define MSG(fn) void fn(const char*fmt,...){char b[8192];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#fn ":%s;",b);callback(1);}
MSG(pline)MSG(pline_The)MSG(You)MSG(Your)MSG(You_feel)MSG(You_hear)
void livelog_printf(long cat,const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("livelog:%ld:%s;",cat,b);}
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char*f,int l,const char*n){append("caller:%s:%d:%s;",f,l,n);}
int(rn2)(int n){seed=(int)((unsigned)seed*1664525U+1013904223U);append("rn2:%d;",n);return n?(unsigned)seed%(unsigned)n:0;}
int(rnd)(int n){append("rnd:%d;",n);return n?1+(rn2)(n):1;}
int(rnl)(int n){append("rnl:%d;",n);return(rn2)(n);}
int(d)(int n,int x){int v=0;append("d:%d:%d;",n,x);for(int i=0;i<n;i++)v+=(rnd)(x);return v;}
int rn2_on_display_rng(int n){append("displayrng:%d;",n);return n?(unsigned)seed%n:0;}
char * Monnam(struct monst * a0){append("Monnam:");append("m%ld;",mid(a0));return "Monster";}
boolean On_stairs(coordxy a0,coordxy a1){append("On_stairs:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return opts[8];}
boolean Resists_Elem(struct monst * a0,int a1){append("Resists_Elem:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);return opts[12];}
char * Tobjnam(struct obj * a0,const char * a1){append("Tobjnam:");append("o%ld;",oid(a0));return "Book slams";}
schar acurr(int a0){append("acurr:");append("%lld;",(long long)a0);return opts[1];}
void aggravate(void){append("aggravate:");}
char * an(const char * a0){append("an:");return "an aura";}
const char * body_part(int a0){append("body_part:");append("%lld;",(long long)a0);return "body";}
boolean can_chant(struct monst * a0){append("can_chant:");append("m%ld;",mid(a0));return opts[2];}
int canseemon(struct monst * a0){append("canseemon:");append("m%ld;",mid(a0));return opts[9];}
boolean check_capacity(const char * a0){append("check_capacity:");return opts[4];}
void check_unpaid(struct obj * a0){append("check_unpaid:");append("o%ld;",oid(a0));callback(4);}
void cmdq_add_key(int a0,char a1){append("cmdq_add_key:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
struct _cmd_queue * cmdq_pop(void){append("cmdq_pop:");if(!opts[24])return NULL;struct _cmd_queue*p=calloc(1,sizeof*p);p->typ=opts[25];p->key=opts[26];opts[24]=0;callback(10);return p;}
boolean defended(struct monst * a0,int a1){append("defended:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);return opts[11];}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){append("discover_object:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);objects[a0].oc_name_known=a1;callback(5);}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){append("dmgtype_fromattack:");append("%lld;",(long long)a1);append("%lld;",(long long)a2);return NULL;}
void do_vicinity_map(struct obj * a0){append("do_vicinity_map:");append("o%ld;",oid(a0));}
int erode_obj(struct obj * a0,const char * a1,int a2,int a3){append("erode_obj:");append("o%ld;",oid(a0));append("%lld;",(long long)a2);append("%lld;",(long long)a3);return opts[28];}
const char * exclam(int a0){append("exclam:");append("%lld;",(long long)a0);return a0>4?"!":".";}
void exercise(int a0,boolean a1){append("exercise:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){append("explode:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);append("%lld;",(long long)a4);append("%lld;",(long long)a5);}
void fall_asleep(int a0,boolean a1){append("fall_asleep:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);gm.multi=a0;}
void find_ac(void){append("find_ac:");}
int freehand(void){append("freehand:");return opts[3];}
int getdir(const char * a0){append("getdir:");u.dx=opts[15];u.dy=opts[16];u.dz=opts[17];return opts[18];}
int getpos(coord * a0,boolean a1,const char * a2){append("getpos:");append("%lld;",(long long)a1);if(opts[50]){if(hilite)hilite(1);if(center)append("center:%d;",center(opts[33],opts[34]));if(hilite)hilite(0);}a0->x=opts[33];a0->y=opts[34];callback(13);return opts[35];}
const char * hcolor(const char * a0){append("hcolor:");return (char*)a0;}
void healup(int a0,int a1,boolean a2,boolean a3){append("healup:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);u.uhp+=a0;if(a2)u.uprops[SICK].intrinsic=0;if(a3)u.uprops[BLINDED].intrinsic=0;}
const char * hliquid(const char * a0){append("hliquid:");return (char*)a0;}
boolean invocation_pos(coordxy a0,coordxy a1){append("invocation_pos:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return opts[7];}
int isok(coordxy a0,coordxy a1){append("isok:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
int jump(int a0){append("jump:");append("%lld;",(long long)a0);return opts[29];}
void losehp(int a0,const char * a1,schar a2){append("losehp:");append("%lld;",(long long)a0);append("%lld;",(long long)a2);u.uhp-=a0;}
void make_blinded(long a0,boolean a1){append("make_blinded:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[BLINDED].intrinsic=a0;}
void make_confused(long a0,boolean a1){append("make_confused:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[CONFUSION].intrinsic=a0;}
struct monst * make_familiar(struct obj * a0,coordxy a1,coordxy a2,boolean a3){append("make_familiar:");append("o%ld;",oid(a0));append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);return &monsters[2];}
void make_slimed(long a0,const char * a1){append("make_slimed:");append("%lld;",(long long)a0);u.uprops[SLIMED].intrinsic=a0;}
void make_stunned(long a0,boolean a1){append("make_stunned:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);u.uprops[STUNNED].intrinsic=a0;}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:");append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);callback(6);return opts[14]?NULL:&monsters[2];}
char * makeplural(const char * a0){append("makeplural:");return "bodies";}
void map_invisible(coordxy a0,coordxy a1){append("map_invisible:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
void mkinvokearea(void){append("mkinvokearea:");}
struct obj * mksobj(int a0,boolean a1,boolean a2){append("mksobj:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);items[15].otyp=a0;items[15].quan=1;callback(7);return &items[15];}
void mkundead(coord * a0,boolean a1,int a2){append("mkundead:");append("%lld;",(long long)a1);append("%lld;",(long long)a2);}
char * mon_nam(struct monst * a0){append("mon_nam:");append("m%ld;",mid(a0));return "monster";}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){append("monflee:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);append("%lld;",(long long)a2);append("%lld;",(long long)a3);a0->mflee=1;}
void more_experienced(int a0,int a1){append("more_experienced:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
void morehungry(int a0){append("morehungry:");append("%lld;",(long long)a0);u.uhunger-=a0;}
void newexplevel(void){append("newexplevel:");}
void nomul(int a0){append("nomul:");append("%lld;",(long long)a0);gm.multi=a0;}
const char * noveltitle(int * a0){append("noveltitle:");*a0=opts[27];return "Test Novel";}
void obfree(struct obj * a0,struct obj * a1){append("obfree:");append("o%ld;",oid(a0));append("o%ld;",oid(a1));a0->quan=0;callback(8);}
boolean objdescr_is(struct obj * a0,const char * a1){append("objdescr_is:");append("o%ld;",oid(a0));return opts[5];}
void observe_object(struct obj * a0){append("observe_object:");append("o%ld;",oid(a0));a0->dknown=1;}
boolean on_level(d_level * a0,d_level * a1){append("on_level:");return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
int peffects(struct obj * a0){append("peffects:");append("o%ld;",oid(a0));return opts[31];}
void poison_strdmg(int a0,int a1,const char * a2,schar a3){append("poison_strdmg:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a3);}
boolean read_tribute(const char * a0,const char * a1,int a2,char * a3,int a4,unsigned a5){append("read_tribute:");append("%lld;",(long long)a2);append("%lld;",(long long)a4);append("%lld;",(long long)a5);callback(2);return opts[6];}
void record_achievement(schar a0){append("record_achievement:");append("%lld;",(long long)a0);}
void rndcurse(void){append("rndcurse:");}
int seffects(struct obj * a0){append("seffects:");append("o%ld;",oid(a0));return opts[31];}
int select_menu(winid a0,int a1,menu_item ** a2){append("select_menu:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);if(selection_count++>=opts[20]){*a2=NULL;return 0;}int n=opts[21]>0?opts[21]:1;*a2=malloc(n*sizeof(menu_item));memset(*a2,0,n*sizeof(menu_item));for(int i=0;i<n;i++)(*a2)[i].item.a_int=(i==0&&selection_count<=16&&opts[59+selection_count])?opts[59+selection_count]:opts[22+i];callback(9);return n;}
int sensemon(struct monst * a0){append("sensemon:");append("m%ld;",mid(a0));return opts[10];}
void set_bknown(struct obj * a0,unsigned a1){append("set_bknown:");append("o%ld;",oid(a0));append("%lld;",(long long)a1);a0->bknown=a1;}
void set_malign(struct monst * a0){append("set_malign:");append("m%ld;",mid(a0));}
void shieldeff(coordxy a0,coordxy a1){append("shieldeff:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
int spell_damage_bonus(int a0){append("spell_damage_bonus:");append("%lld;",(long long)a0);return a0;}
void stop_occupation(void){append("stop_occupation:");go.occupation=NULL;}
void take_gold(void){append("take_gold:");}
boolean tamedog(struct monst * a0,struct obj * a1,boolean a2){append("tamedog:");append("m%ld;",mid(a0));append("o%ld;",oid(a1));append("%lld;",(long long)a2);a0->mtame=1;return 1;}
void tele(void){append("tele:");}
void tmp_at(coordxy a0,coordxy a1){append("tmp_at:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
void trycall(struct obj * a0){append("trycall:");append("o%ld;",oid(a0));}
int unturn_dead(struct monst * a0){append("unturn_dead:");append("m%ld;",mid(a0));return 0;}
void update_inventory(void){append("update_inventory:");}
void use_skill(int a0,int a1){append("use_skill:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);}
void useup(struct obj * a0){append("useup:");append("o%ld;",oid(a0));a0->in_use=0;a0->quan--;callback(3);}
void wakeup(struct monst * a0,boolean a1){append("wakeup:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);a0->msleeping=0;}
void weffects(struct obj * a0){append("weffects:");append("o%ld;",oid(a0));}
int weight(struct obj * a0){append("weight:");append("o%ld;",oid(a0));return opts[13];}
void xkilled(struct monst * a0,int a1){append("xkilled:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);a0->mhp=0;}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){append("yn_function:");append("%lld;",(long long)a2);append("%lld;",(long long)a3);return opts[19];}
int zapdir_to_glyph(int a0,int a1,int a2){append("zapdir_to_glyph:");append("%lld;",(long long)a0);append("%lld;",(long long)a1);append("%lld;",(long long)a2);return 0;}
int zapyourself(struct obj * a0,boolean a1){append("zapyourself:");append("o%ld;",oid(a0));append("%lld;",(long long)a1);callback(11);return opts[30];}
int zhitm(struct monst * a0,int a1,int a2,struct obj ** a3){append("zhitm:");append("m%ld;",mid(a0));append("%lld;",(long long)a1);append("%lld;",(long long)a2);*a3=NULL;a0->mhp-=opts[32];callback(12);return opts[32];}

static winid newwin(int t){append("create:%d;",t);return 1;}
static void displaywin(winid w,boolean b){append("display:%d:%d;",w,b);}
static void destroywin(winid w){append("destroy:%d;",w);}
static void clearwin(winid w){append("clear:%d;",w);}
static void startwin(winid w,unsigned long b){append("start:%d:%lu;",w,b);}
static void endwin(winid w,const char*p){append("end:%d:%s;",w,p?p:"[NULL]");}
void add_menu(winid w,const glyph_info*g,const anything*a,char c,char group,int attr,int color,const char*t,unsigned flags){(void)g;append("menu:%d:%d:%d:%d:%d:%s:%u;",w,a->a_int,c,attr,color,t,flags);}
void add_menu_heading(winid w,const char*t){append("heading:%d:%s;",w,t);}
void add_menu_str(winid w,const char*t){append("str:%d:%s;",w,t);}
void getpos_sethilite(void(*h)(boolean),boolean(*c)(coordxy,coordxy)){hilite=h;center=c;append("hilite:1:1;");}
boolean walk_path(coord*a,coord*b,boolean(*fn)(genericptr_t,coordxy,coordxy),genericptr_t arg){append("walk:%d:%d:%d:%d:%d;",a->x,a->y,b->x,b->y,fn(arg,b->x,b->y));callback(14);return 1;}
void iter_mons(void(*fn)(struct monst*)){for(int i=0;i<3;i++){fn(&monsters[i]);append("iter:%d;",i);}callback(15);}
void set_occupation(int(*fn)(void),const char*t,cmdcount_nht n){go.occupation=fn;append("occupation:%s:%ld;",t,n);callback(16);}
static void delaywin(void){append("delay;");}

#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/spell.c"
#else
struct teleport_spell_queue;struct teleport_spell_zap;
extern boolean teleport_spell_test_spell_aim_step(genericptr_t arg, coordxy x, coordxy y);
#define spell_aim_step teleport_spell_test_spell_aim_step
extern void teleport_spell_test_display_spell_target_positions(boolean on_off);
#define display_spell_target_positions teleport_spell_test_display_spell_target_positions
extern int teleport_spell_test_spell_let_to_idx(char ilet);
#define spell_let_to_idx teleport_spell_test_spell_let_to_idx
extern void teleport_spell_test_deadbook_pacify_undead(struct monst *mtmp);
#define deadbook_pacify_undead teleport_spell_test_deadbook_pacify_undead
extern void teleport_spell_test_sortspells(void);
#define sortspells teleport_spell_test_sortspells
extern boolean teleport_spell_test_dospellmenu(
    const char *prompt,
    int splaction, 
    int *spell_no);
#define dospellmenu teleport_spell_test_dospellmenu
extern int teleport_spell_test_spell_cmp(const genericptr vptr1, const genericptr vptr2);
#define spell_cmp teleport_spell_test_spell_cmp
extern boolean teleport_spell_test_can_center_spell_location(coordxy x, coordxy y);
#define can_center_spell_location teleport_spell_test_can_center_spell_location
extern int teleport_spell_test_throwspell(void);
#define throwspell teleport_spell_test_throwspell
extern void teleport_spell_test_propagate_chain_lightning(struct teleport_spell_queue *,const struct teleport_spell_zap *);
#define propagate_chain_lightning teleport_spell_test_propagate_chain_lightning
extern void teleport_spell_test_spell_backfire(int spell);
#define spell_backfire teleport_spell_test_spell_backfire
extern boolean teleport_spell_test_spelleffects_check(int spell, int *res, int *energy);
#define spelleffects_check teleport_spell_test_spelleffects_check
extern boolean teleport_spell_test_cursed_book(struct obj *bp);
#define cursed_book teleport_spell_test_cursed_book
extern boolean teleport_spell_test_getspell(int *spell_no);
#define getspell teleport_spell_test_getspell
extern boolean teleport_spell_test_spellsortmenu(void);
#define spellsortmenu teleport_spell_test_spellsortmenu
extern const char * teleport_spell_test_spelltypemnemonic(int skill);
#define spelltypemnemonic teleport_spell_test_spelltypemnemonic
extern int teleport_spell_test_learn(void);
#define learn teleport_spell_test_learn
extern void teleport_spell_test_deadbook(struct obj *book2);
#define deadbook teleport_spell_test_deadbook
extern void teleport_spell_test_cast_protection(void);
#define cast_protection teleport_spell_test_cast_protection
extern int teleport_spell_test_percent_success(int spell);
#define percent_success teleport_spell_test_percent_success
extern char * teleport_spell_test_spellretention(int idx, char * outbuf);
#define spellretention teleport_spell_test_spellretention
extern boolean teleport_spell_test_rejectcasting(void);
#define rejectcasting teleport_spell_test_rejectcasting
extern void teleport_spell_test_cast_chain_lightning(void);
#define cast_chain_lightning teleport_spell_test_cast_chain_lightning
extern boolean teleport_spell_test_confused_book(struct obj *spellbook);
#define confused_book teleport_spell_test_confused_book

#endif
#include "tu-spell-layout.h"
#ifdef TELEPORT_REFERENCE_TU
_Static_assert(sizeof(struct chain_lightning_zap)==sizeof(struct teleport_spell_zap),"zap layout");
_Static_assert(offsetof(struct chain_lightning_zap,strength)==offsetof(struct teleport_spell_zap,strength),"zap strength");
_Static_assert(sizeof(struct chain_lightning_queue)==sizeof(struct teleport_spell_queue),"queue layout");
_Static_assert(offsetof(struct chain_lightning_queue,head)==offsetof(struct teleport_spell_queue,head),"queue head");
#endif
int probe_layout_count(void){return SIZE(spell_layout);}const char*probe_layout_name(int i){return spell_layout[i].name;}size_t probe_layout_value(int i){return spell_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}const char*probe_trace(void){return trace;}const char*probe_result(void){return result;}
void probe_option(int i,int v){opts[i]=v;}void probe_seed(int s){seed=s;}void probe_clear(void){trace[0]=result[0]=0;}
void*probe_obj(int i){return i<0?NULL:items+i;}void*probe_mon(int i){return i<0?NULL:monsters+i;}void*probe_buffer(int i){return buffers[i];}void*probe_int(int i){return integers+i;}int probe_intvalue(int i){return integers[i];}
void probe_spell(int i,int id,int lev,int know){svs.spl_book[i].sp_id=id;svs.spl_book[i].sp_lev=lev;svs.spl_book[i].sp_know=know;}
void probe_item(int i,int typ,int field,long value){struct obj*o=items+i;o->otyp=typ;if(field==0)o->blessed=value;if(field==1)o->cursed=value;if(field==2)o->in_use=value;if(field==3)o->spestudied=value;if(field==4)o->novelidx=value;if(field==5)o->spe=value;if(field==6)o->lamplit=value;if(field==7)o->age=value;}
void probe_monset(int i,int pm,int field,int value){struct monst*m=monsters+i;if(pm>=0)m->data=&mons[pm];if(field==0)m->mpeaceful=value;if(field==1)m->mtame=value;if(field==2)m->mhp=value;if(field==3)m->cham=value;}
void probe_global(int field,long v){switch(field){case 0:gu.urole.mnum=v;break;case 1:u.ulevel=v;break;case 2:u.uen=v;break;case 3:u.uenmax=v;break;case 4:u.uenpeak=v;break;case 5:u.uhunger=v;break;case 6:u.uspellprot=v;break;case 7:u.uac=v;break;case 8:gs.spl_sortmode=v;break;case 9:flags.menu_style=v;break;case 10:iflags.menu_tab_sep=v;break;case 11:flags.debug=v;break;case 12:svc.context.spbook.delay=v;break;case 13:svc.context.spbook.book=v<0?NULL:&items[v];break;case 14:gm.multi=v;break;case 15:gu.urole.spelbase=v;break;case 16:gu.urole.spelheal=v;break;case 17:gu.urole.spelshld=v;break;case 18:gu.urole.spelarmr=v;break;case 19:gu.urole.spelstat=v;break;case 20:gu.urole.spelspec=v;break;case 21:gu.urole.spelsbon=v;break;case 22:u.uswallow=v;break;case 23:u.uinwater=v;break;case 24:u.uhave.bell=v;break;case 25:u.uhave.menorah=v;break;case 26:u.uhave.amulet=v;break;case 27:gi.invent=v<0?NULL:&items[v];break;case 28:svm.moves=v;break;case 29:u.ualign.type=v;break;case 30:u.uroleplay.pauper=v;break;case 31:u.uhp=v;break;case 32:u.weapon_skills[P_ATTACK_SPELL].skill=v;break;case 33:u.ustuck=v<0?NULL:&monsters[v];break;case 34:u.uconduct.literate=v;break;case 35:u.uevent.read_tribute=v;break;case 36:go.occupation=v?unrelated_occupation:NULL;break;}}
void probe_skill(int i,int v){u.weapon_skills[i].skill=v;}void probe_link(int i,int j){items[i].nobj=j<0?NULL:&items[j];}
void probe_equipment(int i,int j){struct obj**a[]={&uwep,&uarm,&uarmc,&uarmh,&uarmg,&uarmf,&uarms,&ublindf};*a[i]=j<0?NULL:&items[j];}
void probe_property(int i,long a,long b,long c){u.uprops[i].intrinsic=a;u.uprops[i].extrinsic=b;u.uprops[i].blocked=c;}
void probe_terrain(int x,int y,int typ,int mask){svl.level.locations[x][y].typ=typ;svl.level.locations[x][y].doormask=mask;}
void probe_reset(void){if(gs.spl_orderindx)free(gs.spl_orderindx);if(growth){free(growth);growth=NULL;}memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&svc,0,sizeof svc);memset(&go,0,sizeof go);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&gi,0,sizeof gi);memset(&svm,0,sizeof svm);memset(&svs,0,sizeof svs);memset(&gs,0,sizeof gs);memset(&svb,0,sizeof svb);memset(&gu,0,sizeof gu);memset(&gb,0,sizeof gb);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&svl,0,sizeof svl);memset(&svd,0,sizeof svd);memset(monsters,0,sizeof monsters);memset(items,0,sizeof items);memset(opts,0,sizeof opts);memset(buffers,0,sizeof buffers);memset(integers,0,sizeof integers);seed=1;selection_count=0;hilite=NULL;center=NULL;objects_globals_init();monst_globals_init();u.ux=10;u.uy=10;u.ulevel=12;u.uen=u.uenmax=u.uenpeak=200;u.uhunger=500;u.uhp=100;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];gu.urole.mnum=PM_WIZARD;gu.urole.spelstat=A_INT;gu.urole.spelbase=0;svm.moves=100;opts[0]=1;opts[1]=18;opts[2]=opts[3]=1;opts[9]=1;opts[19]='y';opts[33]=11;opts[34]=10;opts[18]=1;opts[22]=1;opts[35]=0;for(int i=0;i<P_NUM_SKILLS;i++)u.weapon_skills[i].skill=P_BASIC;for(int i=0;i<3;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].mx=11+i;monsters[i].my=10;monsters[i].mhp=40;svl.level.monsters[11+i][10]=&monsters[i];}for(int i=0;i<16;i++){items[i].otyp=SPE_HEALING;items[i].quan=1;items[i].o_id=i+1;}uwep=uarm=uarmc=uarmh=uarmg=uarmf=uarms=ublindf=NULL;for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)svl.level.locations[x][y].typ=ROOM;for(int y=0;y<ROWNO;y++){visrows[y]=visibility[y];for(int x=0;x<COLNO;x++)visibility[y][x]=IN_SIGHT|COULD_SEE;}gv.viz_array=visrows;windowprocs.win_create_nhwindow=newwin;windowprocs.win_display_nhwindow=displaywin;windowprocs.win_destroy_nhwindow=destroywin;windowprocs.win_clear_nhwindow=clearwin;windowprocs.win_start_menu=startwin;windowprocs.win_end_menu=endwin;windowprocs.win_delay_output=delaywin;probe_clear();}
const char*probe_snapshot(void){char*p=snap;p+=sprintf(p,"u:%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%d,%ld,%ld,%ld;book:%ld,%u,%d;sort:%d;",u.uen,u.uhunger,u.uhp,u.uspellprot,u.usptime,u.uspmtime,u.dx,u.dy,u.dz,u.udg_cnt,disp.botl,u.uconduct.literate,gm.multi,svm.moves,oid(svc.context.spbook.book),svc.context.spbook.o_id,svc.context.spbook.delay,gs.spl_sortmode);for(int i=0;i<MAXSPELL+1;i++)p+=sprintf(p,"s%d:%d,%d,%d,%d;",i,svs.spl_book[i].sp_id,svs.spl_book[i].sp_lev,svs.spl_book[i].sp_know,gs.spl_orderindx?gs.spl_orderindx[i<MAXSPELL?i:0]:-1);for(int i=0;i<16;i++)p+=sprintf(p,"o%d:%d,%ld,%d,%d,%d,%d,%d,%d,%d;",i,items[i].otyp,items[i].quan,items[i].blessed,items[i].cursed,items[i].in_use,items[i].known,items[i].spestudied,items[i].novelidx,items[i].lamplit);for(int i=0;i<3;i++)p+=sprintf(p,"m%d:%d,%d,%d,%d;",i,monsters[i].mhp,monsters[i].mpeaceful,monsters[i].mtame,monsters[i].mflee);for(int i=0;i<LAST_PROP+1;i++)if(u.uprops[i].intrinsic||u.uprops[i].extrinsic||u.uprops[i].blocked)p+=sprintf(p,"p%d:%ld,%ld,%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);p+=sprintf(p,"event:%d,%d,%d;",u.uevent.invoked,u.uevent.udemigod,u.uevent.read_tribute);for(int i=0;i<8;i++)p+=sprintf(p,"i%d:%d;",i,integers[i]);return snap;}
#ifdef TELEPORT_REFERENCE_TU
static struct chain_lightning_queue chain;static struct chain_lightning_zap zaprecord;
#else
static struct teleport_spell_queue chain;static struct teleport_spell_zap zaprecord;
#endif
void*probe_chain(void){return &chain;}void*probe_zap(void){return &zaprecord;}
void probe_zapset(int dir,int x,int y,int strength,int tail){memset(&chain,0,sizeof chain);memset(&zaprecord,0,sizeof zaprecord);zaprecord.dir=dir;zaprecord.x=x;zaprecord.y=y;zaprecord.strength=strength;chain.tail=tail;}
const char*probe_chain_state(void){static char buf[8192];char*p=buf;p+=sprintf(p,"zap:%d,%d,%d,%d;queue:%d,%d,%d;",zaprecord.dir,zaprecord.x,zaprecord.y,zaprecord.strength,chain.head,chain.tail,chain.displayed_beam);for(int i=0;i<chain.tail;i++)p+=sprintf(p,"q%d:%d,%d,%d,%d;",i,chain.q[i].dir,chain.q[i].x,chain.q[i].y,chain.q[i].strength);return buf;}
int probe_occupation(void){int ret=go.occupation?go.occupation():-1;snprintf(result,sizeof result,"%d",ret);return ret;}
long probe_invoke(int op,uintptr_t a,uintptr_t b,uintptr_t c,uintptr_t d){long out=0;result[0]=0;switch(op){
case 0:out=spell_let_to_idx((char)a);break;
case 1:out=cursed_book((struct obj *)a);break;
case 2:out=confused_book((struct obj *)a);break;
case 3:deadbook_pacify_undead((struct monst *)a);break;
case 4:deadbook((struct obj *)a);break;
case 5:book_cursed((struct obj *)a);break;
case 6:out=learn();break;
case 7:out=study_book((struct obj *)a);break;
case 8:book_disappears((struct obj *)a);break;
case 9:book_substitution((struct obj *)a,(struct obj *)b);break;
case 10:age_spells();break;
case 11:out=rejectcasting();break;
case 12:out=getspell((int *)a);break;
case 13:out=dowizcast();break;
case 14:out=docast();break;
case 15:{const char*p=spelltypemnemonic((int)a);snprintf(result,sizeof result,"%s",p?p:"[NULL]");}break;
case 16:out=spell_skilltype((int)a);break;
case 17:skill_based_spellbook_id();break;
case 18:
#ifdef TELEPORT_REFERENCE_TU
propagate_chain_lightning((struct chain_lightning_queue *)a,*(struct chain_lightning_zap*)b);
#else
propagate_chain_lightning((struct teleport_spell_queue*)a,(struct teleport_spell_zap*)b);
#endif
break;
case 19:cast_chain_lightning();break;
case 20:cast_protection();break;
case 21:spell_backfire((int)a);break;
case 22:out=spelleffects_check((int)a,(int *)b,(int *)c);break;
case 23:out=spelleffects((int)a,(boolean)b,(boolean)c);break;
case 24:out=spell_aim_step((genericptr_t)a,(coordxy)b,(coordxy)c);break;
case 25:out=can_center_spell_location((coordxy)a,(coordxy)b);break;
case 26:display_spell_target_positions((boolean)a);break;
case 27:out=throwspell();break;
case 28:out=tport_spell((int)a);break;
case 29:losespells();break;
case 30:out=spell_cmp((const genericptr)a,(const genericptr)b);break;
case 31:sortspells();break;
case 32:out=spellsortmenu();break;
case 33:out=dovspell();break;
case 34:show_spells();break;
case 35:out=dospellmenu((const char *)a,(int)b,(int *)c);break;
case 36:out=percent_success((int)a);break;
case 37:{const char*p=spellretention((int)a,(char *)b);snprintf(result,sizeof result,"%s",p?p:"[NULL]");}break;
case 38:initialspell((struct obj *)a);break;
case 39:out=known_spell((short)a);break;
case 40:out=spell_idx((short)a);break;
case 41:out=force_learn_spell((short)a);break;
case 42:out=num_spells();break;
default:abort();}if(!result[0])snprintf(result,sizeof result,"%ld",out);return out;}
#ifdef TELEPORT_REFERENCE_TU
int probe_table_count(void){return SIZE(spl_sortchoices);}const char*probe_table_text(int i){return spl_sortchoices[i];}
#else
int probe_table_count(void){return 0;}const char*probe_table_text(int i){(void)i;return NULL;}
#endif
