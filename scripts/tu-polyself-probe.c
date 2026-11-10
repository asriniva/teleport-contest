/* Controlled POLYSELF fixture; original source and JS share the same typed C world. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-polyself-layout.h"
__typeof__(mons) mons;
__typeof__(u) u;
__typeof__(gy) gy;
__typeof__(uwep) uwep;
__typeof__(gu) gu;
__typeof__(program_state) program_state;
__typeof__(windowprocs) windowprocs;
__typeof__(gw) gw;
__typeof__(disp) disp;
__typeof__(uamul) uamul;
__typeof__(flags) flags;
__typeof__(gm) gm;
__typeof__(svk) svk;
__typeof__(svp) svp;
__typeof__(gs) gs;
__typeof__(uarmg) uarmg;
__typeof__(uarm) uarm;
__typeof__(svm) svm;
__typeof__(uskin) uskin;
__typeof__(svd) svd;
__typeof__(uball) uball;
__typeof__(gv) gv;
__typeof__(gi) gi;
__typeof__(uarmc) uarmc;
__typeof__(uarmu) uarmu;
__typeof__(uarmh) uarmh;
__typeof__(objects) objects;
__typeof__(uarms) uarms;
__typeof__(uarmf) uarmf;
__typeof__(ublindf) ublindf;
__typeof__(uswapwep) uswapwep;
__typeof__(svl) svl;
__typeof__(gn) gn;
__typeof__(svc) svc;
const struct Gender genders[4]={{.adj="male"},{.adj="female"},{.adj="neuter"},{.adj="plural"}};
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind.",.c_shudder_for_moment="You shudder for a moment.",.c_thats_enough_tries="That's enough tries!",.c_the_your={"the","your"}};
const char ynchars[]="yn";
static struct permonst pmcopies[4];static struct obj objpool[16];static struct monst mpool[8];static struct trap trap;static struct kinfo delayed;static anything any;
static char tracebuf[262144],statebuf[2097152],input[2048],labelbuf[16][64];static int tracepos,seed,opts[256],linecount,reentered;static void*growth;
static seenV vis[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char*fmt,...){if(tracepos>sizeof tracebuf-4096)abort();va_list ap;va_start(ap,fmt);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);}
static uint64_t canonical(uint64_t);
static int mid(struct monst*m){if(!m)return -1;if(m==&gy.youmonst)return 98;for(int i=0;i<8;i++)if(m==&mpool[i])return i;return 99;}
static int oid(struct obj*o){if(!o)return -1;for(int i=0;i<16;i++)if(o==&objpool[i])return i;return 99;}
static void grow(void){if(opts[50]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}}
boolean rng_log_enabled(void){return opts[49];}
void rng_log_set_caller(const char*file,int line,const char*fn){append("site:%s:%d:%s;",file,line,fn);grow();if(opts[51]){u.ulevel=opts[51];append("ulevel:%d;",u.ulevel);}if(opts[54]){mpool[0].m_lev=opts[54];append("mlev:%d;",mpool[0].m_lev);}if(opts[52]&&!reentered){reentered=1;float_vs_flight();append("reentered;");}}
static int random_(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;return (unsigned)seed%n;}
int (rn2)(int n){int v=random_(n);append("rn2:%d:%d;",n,v);return v;}
int (rnd)(int n){int v=random_(n)+1;append("rnd:%d:%d;",n,v);return v;}
int (rnl)(int n){int v=random_(n);append("rnl:%d:%d;",n,v);return v;}
int (d)(int n,int x){int v=0;for(int i=0;i<n;i++)v+=random_(x)+1;append("d:%d:%d:%d;",n,x,v);return v;}
static void message(const char*kind,const char*fmt,va_list ap){char b[2048];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",kind,b);grow();}
void (pline)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("pline",fmt,ap);va_end(ap);}
void (You)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You",fmt,ap);va_end(ap);}
void (Your)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("Your",fmt,ap);va_end(ap);}
void (You_feel)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You_feel",fmt,ap);va_end(ap);}
void (You_cant)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You_cant",fmt,ap);va_end(ap);}
void (There)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("There",fmt,ap);va_end(ap);}
void (urgent_pline)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("urgent_pline",fmt,ap);va_end(ap);}
void (pline_The)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("pline_The",fmt,ap);va_end(ap);}
void (impossible)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("impossible",fmt,ap);va_end(ap);}
void livelog_printf(long mask,const char*fmt,...){append("logmask:%ld;",mask);va_list ap;va_start(ap,fmt);message("livelog",fmt,ap);va_end(ap);}
void set_mon_data(struct monst*m,struct permonst*p){append("set_mon_data:%d:%d;",mid(m),(int)(p-mons));m->data=p;m->mnum=p-mons;}
void set_ustuck(struct monst*m){append("set_ustuck:%d;",mid(m));u.ustuck=m;}
void set_utrap(unsigned int n,unsigned int type){append("set_utrap:%u:%u;",n,type);u.utrap=n;u.utraptype=type;}
void reset_utrap(boolean n){append("reset_utrap:%d;",n);u.utrap=u.utraptype=0;}
void set_itimeout(long*p,long n){append("timeout:%ld:%ld;",*p,n);*p=(*p&~TIMEOUT)|(n&TIMEOUT);}
void getlin(const char*prompt,char*out){append("getlin:%s;",prompt);linecount++;if(opts[53]&&linecount>opts[53])strcpy(out,"random");else strcpy(out,input);grow();}
int name_to_mon(const char*s,int*g){append("name:%s:%d;",s,*g);*g=opts[2];if(!strncmp(s,"monster",7))return atoi(s+7);return NON_PM;}
int name_to_monclass(const char*s,int*n){append("class:%s;",s);*n=opts[3];return opts[4];}
char yn_function(const char*q,const char*c,char def,boolean isyn){append("yn:%s:%s:%d:%d;",q,c,def,isyn);return opts[5]?opts[5]:def;}
int getdir(const char*prompt){append("getdir:%s;",prompt?prompt:"(null)");return opts[6];}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
int dist2(coordxy x,coordxy y,coordxy a,coordxy b){return (x-a)*(x-a)+(y-b)*(y-b);}
boolean Resists_Elem(struct monst*m,int n){append("resists:%d:%d;",mid(m),n);return opts[7];}
boolean valid_vampshiftform(int a,int b){append("vampshift:%d:%d;",a,b);return opts[8];}
boolean can_be_strangled(struct monst*m){append("strangle:%d;",mid(m));return opts[9];}
boolean resists_drli(struct monst*m){append("drli:%d:%d;",mid(m),oid(uwep));return opts[10];}
boolean attacktype(struct permonst*p,int a){for(int i=0;i<NATTK;i++)if(p->mattk[i].aatyp==a)return TRUE;return FALSE;}
struct attack*dmgtype_fromattack(struct permonst*p,int d,int a){for(int i=0;i<NATTK;i++)if(p->mattk[i].adtyp==d&&p->mattk[i].aatyp==a)return &p->mattk[i];return 0;}
boolean dmgtype(struct permonst*p,int d){for(int i=0;i<NATTK;i++)if(p->mattk[i].adtyp==d)return TRUE;return FALSE;}
struct attack*attacktype_fordmg(struct permonst*p,int a,int d){for(int i=0;i<NATTK;i++)if(p->mattk[i].aatyp==a&&(d==AD_ANY||p->mattk[i].adtyp==d))return &p->mattk[i];return 0;}
int rounddiv(long n,int d){int neg=(n<0)^(d<0);if(n<0)n=-n;if(d<0)d=-d;long v=n/d;if(n%d*2>=d)v++;return neg?-v:v;}
int newhp(void){u.uhpinc[u.ulevel]=3;append("newhp:%d;",u.ulevel);return 3;}int newpw(void){u.ueninc[u.ulevel]=2;append("newpw:%d;",u.ulevel);return 2;}
long rndexp(boolean b){append("rndexp:%d;",b);return 9007199254740997L;}
void setuhpmax(int n,boolean clamp){append("setuhpmax:%d:%d;",n,clamp);u.uhpmax=n;if(clamp&&u.uhp>n)u.uhp=n;}
void make_sick(long n,const char*why,boolean talk,int mask){append("sick:%ld:%d:%d;",n,talk,mask);u.uprops[SICK].intrinsic=n;}
void make_stoned(long n,const char*why,int k,const char*s){append("stoned:%ld:%d;",n,k);u.uprops[STONED].intrinsic=n;}
void make_slimed(long n,const char*s){append("slimed:%ld;",n);u.uprops[SLIMED].intrinsic=n;}
void make_blinded(long n,boolean talk){append("blinded:%ld:%d;",n,talk);u.uprops[BLINDED].intrinsic=n;}
void nomul(int n){append("nomul:%d;",n);gm.multi=n;}
void newuhs(boolean n){append("newuhs:%d;",n);}
void done(int how){append("done:%d:%s;",how,svk.killer.name);}
void losehp(int n,const char*why,schar fmt){append("losehp:%d:%s:%d;",n,why,fmt);u.uhp-=n;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
void setworn(struct obj*o,long mask){append("setworn:%d:%ld;",oid(o),mask);if(o)o->owornmask=mask;}
struct trap*t_at(coordxy x,coordxy y){return opts[11]?&trap:0;}
struct trap*maketrap(coordxy x,coordxy y,int typ){append("maketrap:%d:%d:%d;",x,y,typ);if(opts[12])return 0;trap.ttyp=typ;return &trap;}
struct obj*mksobj(int typ,boolean init,boolean art){append("mksobj:%d:%d:%d;",typ,init,art);objpool[15].otyp=typ;return &objpool[15];}
anything*monst_to_any(struct monst*m){any.a_monst=m;return &any;}
struct kinfo*find_delayed_killer(int n){return opts[13]?&delayed:0;}
const struct Race*character_race(short n){return opts[14]?&gu.urace:0;}
int golemhp(int n){return 40;}
int were_summon(struct permonst*p,boolean you,int*n,char*out){append("were_summon:%d;",you);*n=opts[15];if(out)strcpy(out,"friends");return opts[16];}

int Armor_gone(void){append("armor_gone;");uarm=0;return 0;}int Cloak_off(void){append("cloak_off;");uarmc=0;return 0;}int Gloves_off(void){append("gloves_off;");uarmg=0;return 0;}int Boots_off(void){append("boots_off;");uarmf=0;return 0;}int Helmet_off(void){append("helmet_off;");uarmh=0;return 0;}int Shield_off(void){append("shield_off;");uarms=0;return 0;}
void Blindf_off(struct obj*o){append("blindf_off;");ublindf=0;}
void uwepgone(void){append("uwepgone;");uwep=0;}void uswapwepgone(void){append("uswapwepgone;");uswapwep=0;}
void dropx(struct obj*o){append("dropx:%d;",oid(o));struct obj**p=&gi.invent;while(*p){if(*p==o){*p=o->nobj;break;}p=&(*p)->nobj;}o->nobj=0;}
void useup(struct obj*o){append("useup:%d;",oid(o));o->quan=0;}
char*Monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*Some_Monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*mon_nam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*l_monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*y_monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*simpleonames(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
char*cxname(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
char*yname(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*weapon_descr(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*cloak_simple_name(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*helm_simple_name(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*pmname(struct permonst*p,int g){return "form";}
const char*rank_of(int level,short role,boolean female){return "rank";}
char*an(const char*s){return (char*)s;}char*the(const char*s){return (char*)s;}char*s_suffix(const char*s){return (char*)s;}char*makeplural(const char*s){return (char*)s;}
char*vtense(const char*s,const char*v){return (char*)v;}char*otense(struct obj*o,const char*v){return (char*)v;}
const char*hliquid(const char*s){return s;}const char*surface(coordxy x,coordxy y){return "floor";}
char*mungspaces(char*s){return s;}char*in_rooms(coordxy x,coordxy y,int n){return opts[17]?"A":"";}
char*strstri(const char*a,const char*b){return strstr(a,b);}char*strsubst(char*a,const char*b,const char*c){return a;}
schar acurr(int a){return u.acurr.a[a];}
int (Mgender)(struct monst * a0){append("dependency:Mgender:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[64];}
signed char (On_stairs)(coordxy a0,coordxy a1){append("dependency:On_stairs:%d:%d;",(int)a0,(int)a1);return opts[65];}
void (add_damage)(coordxy a0,coordxy a1,long a2){append("dependency:add_damage:%d:%d:%llu;",(int)a0,(int)a1,(unsigned long long)a2);}
void (adjabil)(int a0,int a1){append("dependency:adjabil:%d:%d;",(int)a0,(int)a1);}
int (arti_light_radius)(struct obj * a0){append("dependency:arti_light_radius:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[66];}
signed char (artifact_light)(struct obj * a0){append("dependency:artifact_light:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[67];}
signed char (breakarm)(struct permonst * a0){append("dependency:breakarm:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[68];}
void (buried_ball_to_freedom)(void){append("dependency:buried_ball_to_freedom;");}
void (bury_objs)(int a0,int a1){append("dependency:bury_objs:%d:%d;",(int)a0,(int)a1);}
signed char (can_ride)(struct monst * a0){append("dependency:can_ride:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[69];}
void (cancel_don)(void){append("dependency:cancel_don;");}
signed char (canletgo)(struct obj * a0,const char * a1){append("dependency:canletgo:%llu:%s;",(unsigned long long)canonical((uintptr_t)a0),a1);return opts[70];}
int (canseemon)(struct monst * a0){append("dependency:canseemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[71];}
int (counter_were)(int a0){append("dependency:counter_were:%d;",(int)a0);return opts[72];}
void (dealloc_killer)(struct kinfo * a0){append("dependency:dealloc_killer:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
signed char (defended)(struct monst * a0,int a1){append("dependency:defended:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[73];}
void (del_light_source)(int a0,union any * a1){append("dependency:del_light_source:%d:%llu;",(int)a0,(unsigned long long)canonical((uintptr_t)a1));}
void (deltrap)(struct trap * a0){append("dependency:deltrap:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (destroy_items)(struct monst * a0,int a1,int a2){append("dependency:destroy_items:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return opts[74];}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){append("dependency:discover_object:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3);}
void (dismount_steed)(int a0){append("dependency:dismount_steed:%d;",(int)a0);}
signed char (donning)(struct obj * a0){append("dependency:donning:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[75];}
void (dotrap)(struct trap * a0,unsigned int a1){append("dependency:dotrap:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
int (egg_type_from_parent)(int a0,boolean a1){append("dependency:egg_type_from_parent:%d:%d;",(int)a0,(int)a1);return opts[76];}
void (encumber_msg)(void){append("dependency:encumber_msg;");}
void (end_burn)(struct obj * a0,boolean a1){append("dependency:end_burn:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (exercise)(int a0,boolean a1){append("dependency:exercise:%d:%d;",(int)a0,(int)a1);}
void (expels)(struct monst * a0,struct permonst * a1,boolean a2){append("dependency:expels:%llu:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1),(int)a2);}
void (feeltrap)(struct trap * a0){append("dependency:feeltrap:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (find_ac)(void){append("dependency:find_ac;");}
signed char (has_ceiling)(d_level * a0){append("dependency:has_ceiling:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[77];}
signed char (hideunder)(struct monst * a0){append("dependency:hideunder:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[78];}
void (ignite_items)(struct obj * a0){append("dependency:ignite_items:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (instapetrify)(const char * a0){append("dependency:instapetrify:%s;",a0?a0:"(null)");}
signed char (is_fainted)(void){append("dependency:is_fainted;");return opts[79];}
signed char (is_home_elemental)(struct permonst * a0){append("dependency:is_home_elemental:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[80];}
signed char (is_pool)(coordxy a0,coordxy a1){append("dependency:is_pool:%d:%d;",(int)a0,(int)a1);return opts[81];}
signed char (is_pool_or_lava)(coordxy a0,coordxy a1){append("dependency:is_pool_or_lava:%d:%d;",(int)a0,(int)a1);return opts[82];}
void (killed)(struct monst * a0){append("dependency:killed:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (learn_egg_type)(int a0){append("dependency:learn_egg_type:%d;",(int)a0);}
void (make_glib)(int a0){append("dependency:make_glib:%d;",(int)a0);}
void (max_rank_sz)(void){append("dependency:max_rank_sz;");}
void (maybe_adjust_light)(struct obj * a0,int a1){append("dependency:maybe_adjust_light:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
int (mkclass_poly)(int a0){append("dependency:mkclass_poly:%d;",(int)a0);return opts[83];}
void (new_light_source)(coordxy a0,coordxy a1,int a2,int a3,union any * a4){append("dependency:new_light_source:%d:%d:%d:%d:%llu;",(int)a0,(int)a1,(int)a2,(int)a3,(unsigned long long)canonical((uintptr_t)a4));}
int (num_horns)(struct permonst * a0){append("dependency:num_horns:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[84];}
void (observe_object)(struct obj * a0){append("dependency:observe_object:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
signed char (poly_when_stoned)(struct permonst * a0){append("dependency:poly_when_stoned:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[85];}
int (racial_exception)(struct monst * a0,struct obj * a1){append("dependency:racial_exception:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[86];}
void (redist_attr)(void){append("dependency:redist_attr;");}
void (retouch_equipment)(int a0){append("dependency:retouch_equipment:%d;",(int)a0);}
void (see_monsters)(void){append("dependency:see_monsters;");}
void (selftouch)(const char * a0){append("dependency:selftouch:%s;",a0);}
int (sensemon)(struct monst * a0){append("dependency:sensemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[87];}
void (set_mimic_blocking)(void){append("dependency:set_mimic_blocking;");}
void (setmangry)(struct monst * a0,boolean a1){append("dependency:setmangry:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
signed char (sliparm)(struct permonst * a0){append("dependency:sliparm:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[88];}
void (spoteffects)(boolean a0){append("dependency:spoteffects:%d;",(int)a0);}
void (status_initialize)(boolean a0){append("dependency:status_initialize:%d;",(int)a0);}
signed char (sticks)(struct permonst * a0){append("dependency:sticks:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[89];}
signed char (the_unique_pm)(struct permonst * a0){append("dependency:the_unique_pm:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[90];}
void (throwit)(struct obj * a0,long a1,boolean a2,struct obj * a3){append("dependency:throwit:%llu:%llu:%d:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)a1,(int)a2,(unsigned long long)canonical((uintptr_t)a3));}
void (ubreatheu)(struct attack * a0){append("dependency:ubreatheu:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (ubuzz)(int a0,int a1){append("dependency:ubuzz:%d:%d;",(int)a0,(int)a1);}
signed char (unconscious)(void){append("dependency:unconscious;");return opts[91];}
void (unmul)(const char * a0){append("dependency:unmul:%s;",a0?a0:"(null)");}
void (unpunish)(void){append("dependency:unpunish;");}
void (untwoweapon)(void){append("dependency:untwoweapon;");}
void (update_inventory)(void){append("dependency:update_inventory;");}
void (wakeup)(struct monst * a0,boolean a1){append("dependency:wakeup:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
int (were_beastie)(int a0){append("dependency:were_beastie:%d;",(int)a0);return opts[92];}
void (youhiding)(boolean a0,int a1){append("dependency:youhiding:%d:%d;",(int)a0,(int)a1);}

#ifdef HYBRID_POLYSELF
extern void set_uasmon();
extern void float_vs_flight();
extern void steed_vs_stealth();
extern void teleport_polyself_check_strangling(boolean on);
#define check_strangling teleport_polyself_check_strangling
extern void teleport_polyself_polyman(const char * fmt,const char * arg);
#define polyman teleport_polyself_polyman
extern void change_sex();
extern void livelog_newform(boolean viapoly,int oldgend,int newgend);
extern void teleport_polyself_newman();
#define newman teleport_polyself_newman
extern void polyself(int psflags);
extern int polymon(int mntmp);
extern schar uasmon_maxStr();
extern void teleport_polyself_dropp(struct obj * obj);
#define dropp teleport_polyself_dropp
extern void teleport_polyself_break_armor();
#define break_armor teleport_polyself_break_armor
extern void teleport_polyself_drop_weapon(int alone);
#define drop_weapon teleport_polyself_drop_weapon
extern void rehumanize();
extern int dobreathe();
extern int dospit();
extern int doremove();
extern int dospinweb();
extern int dosummon();
extern int dogaze();
extern int dohide();
extern int dopoly();
extern int domindblast();
extern void uunstick();
extern void skinback(boolean silently);
extern const char * mbodypart(struct monst * mon,int part);
extern const char * body_part(int part);
extern int poly_gender();
extern void ugolemeffects(int damtype,int dam);
extern int teleport_polyself_armor_to_dragon(int atyp);
#define armor_to_dragon teleport_polyself_armor_to_dragon
extern void teleport_polyself_polysense();
#define polysense teleport_polyself_polysense
extern boolean ugenocided();
extern const char * udeadinside();
#else
#include "../.cache/wasm64-build/tree/src/polyself.c"
#endif
static uint64_t canonical(uint64_t value){
#define REGION(v,id) if(value>=(uintptr_t)&(v)&&value<(uintptr_t)&(v)+sizeof(v))return ((uint64_t)(id)<<48)+(value-(uintptr_t)&(v))
REGION(mons,1);REGION(objpool,2);REGION(mpool,3);REGION(u,4);REGION(gy.youmonst,5);REGION(trap,6);REGION(input,7);REGION(labelbuf,8);REGION(gu,9);REGION(delayed,10);REGION(any,11);REGION(pmcopies,12);REGION(visrows,13);REGION(vis,14);
#undef REGION
return value;}
static void typed_pointer(unsigned char*out,const void*base,const void*field){uint64_t v;memcpy(&v,field,8);v=canonical(v);memcpy(out+((const unsigned char*)field-(const unsigned char*)base),&v,8);}
static void typed_text_pointer(unsigned char*out,const void*base,const void*field){const unsigned char*p;memcpy(&p,field,8);uint64_t value=0;if(p){value=1469598103934665603ULL;for(;*p;p++){value^=*p;value*=1099511628211ULL;}}memcpy(out+((const unsigned char*)field-(const unsigned char*)base),&value,8);}static void normalize_d_level(unsigned char*,const void*,const struct d_level*);
static void normalize_RoleName(unsigned char*,const void*,const struct RoleName*);
static void normalize_vptrs(unsigned char*,const void*,const union vptrs*);
static void normalize_flag(unsigned char*,const void*,const struct flag*);
static void normalize_trap(unsigned char*,const void*,const struct trap*);
static void normalize_window_procs(unsigned char*,const void*,const struct window_procs*);
static void normalize_attribs(unsigned char*,const void*,const struct attribs*);
static void normalize_obj(unsigned char*,const void*,const struct obj*);
static void normalize_objclass(unsigned char*,const void*,const struct objclass*);
static void normalize_attack(unsigned char*,const void*,const struct attack*);
static void normalize_permonst(unsigned char*,const void*,const struct permonst*);
static void normalize_warntype_info(unsigned char*,const void*,const struct warntype_info*);
static void normalize_prop(unsigned char*,const void*,const struct prop*);
static void normalize_monst(unsigned char*,const void*,const struct monst*);
static void normalize_display_hints(unsigned char*,const void*,const struct display_hints*);
static void normalize_context_info(unsigned char*,const void*,const struct context_info*);
static void normalize_rm(unsigned char*,const void*,const struct rm*);
static void normalize_u_conduct(unsigned char*,const void*,const struct u_conduct*);
static void normalize_c_common_strings(unsigned char*,const void*,const struct c_common_strings*);
static void normalize_Role(unsigned char*,const void*,const struct Role*);
static void normalize_dgn_topology(unsigned char*,const void*,const struct dgn_topology*);
static void normalize_Race(unsigned char*,const void*,const struct Race*);
static void normalize_Gender(unsigned char*,const void*,const struct Gender*);
static void normalize_instance_globals_i(unsigned char*,const void*,const struct instance_globals_i*);
static void normalize_you(unsigned char*,const void*,const struct you*);
static void normalize_instance_globals_m(unsigned char*,const void*,const struct instance_globals_m*);
static void normalize_dlevel_t(unsigned char*,const void*,const dlevel_t*);
static void normalize_instance_globals_n(unsigned char*,const void*,const struct instance_globals_n*);
static void normalize_kinfo(unsigned char*,const void*,const struct kinfo*);
static void normalize_mvitals(unsigned char*,const void*,const struct mvitals*);
static void normalize_instance_globals_s(unsigned char*,const void*,const struct instance_globals_s*);
static void normalize_sinfo(unsigned char*,const void*,const struct sinfo*);
static void normalize_instance_globals_u(unsigned char*,const void*,const struct instance_globals_u*);
static void normalize_instance_globals_v(unsigned char*,const void*,const struct instance_globals_v*);
static void normalize_instance_globals_w(unsigned char*,const void*,const struct instance_globals_w*);
static void normalize_instance_globals_y(unsigned char*,const void*,const struct instance_globals_y*);
static void normalize_instance_globals_saved_c(unsigned char*,const void*,const struct instance_globals_saved_c*);
static void normalize_instance_globals_saved_d(unsigned char*,const void*,const struct instance_globals_saved_d*);
static void normalize_instance_globals_saved_k(unsigned char*,const void*,const struct instance_globals_saved_k*);
static void normalize_instance_globals_saved_l(unsigned char*,const void*,const struct instance_globals_saved_l*);
static void normalize_instance_globals_saved_m(unsigned char*,const void*,const struct instance_globals_saved_m*);
static void normalize_instance_globals_saved_p(unsigned char*,const void*,const struct instance_globals_saved_p*);
static void normalize_d_level(unsigned char*out,const void*base,const struct d_level*p){}
static void normalize_RoleName(unsigned char*out,const void*base,const struct RoleName*p){typed_text_pointer(out,base,&p->m);typed_text_pointer(out,base,&p->f);}
static void normalize_vptrs(unsigned char*out,const void*base,const union vptrs*p){typed_pointer(out,base,&p->v_nexthere);}
static void normalize_flag(unsigned char*out,const void*base,const struct flag*p){}
static void normalize_trap(unsigned char*out,const void*base,const struct trap*p){}
static void normalize_window_procs(unsigned char*out,const void*base,const struct window_procs*p){}
static void normalize_attribs(unsigned char*out,const void*base,const struct attribs*p){}
static void normalize_obj(unsigned char*out,const void*base,const struct obj*p){typed_pointer(out,base,&p->nobj);normalize_vptrs(out,base,&p->v);}
static void normalize_objclass(unsigned char*out,const void*base,const struct objclass*p){}
static void normalize_attack(unsigned char*out,const void*base,const struct attack*p){}
static void normalize_permonst(unsigned char*out,const void*base,const struct permonst*p){for(int i0=0;i0<6;i0++){normalize_attack(out,base,&p->mattk[i0]);}}
static void normalize_warntype_info(unsigned char*out,const void*base,const struct warntype_info*p){typed_pointer(out,base,&p->species);}
static void normalize_prop(unsigned char*out,const void*base,const struct prop*p){}
static void normalize_monst(unsigned char*out,const void*base,const struct monst*p){typed_pointer(out,base,&p->nmon);typed_pointer(out,base,&p->data);typed_pointer(out,base,&p->minvent);}
static void normalize_display_hints(unsigned char*out,const void*base,const struct display_hints*p){}
static void normalize_context_info(unsigned char*out,const void*base,const struct context_info*p){normalize_warntype_info(out,base,&p->warntype);}
static void normalize_rm(unsigned char*out,const void*base,const struct rm*p){}
static void normalize_u_conduct(unsigned char*out,const void*base,const struct u_conduct*p){}
static void normalize_c_common_strings(unsigned char*out,const void*base,const struct c_common_strings*p){typed_text_pointer(out,base,&p->c_thats_enough_tries);typed_text_pointer(out,base,&p->c_shudder_for_moment);typed_text_pointer(out,base,&p->c_Never_mind);for(int i0=0;i0<2;i0++){typed_pointer(out,base,&p->c_the_your[i0]);}}
static void normalize_Role(unsigned char*out,const void*base,const struct Role*p){normalize_RoleName(out,base,&p->name);}
static void normalize_dgn_topology(unsigned char*out,const void*base,const struct dgn_topology*p){normalize_d_level(out,base,&p->d_water_level);normalize_d_level(out,base,&p->d_air_level);normalize_d_level(out,base,&p->d_astral_level);}
static void normalize_Race(unsigned char*out,const void*base,const struct Race*p){typed_text_pointer(out,base,&p->noun);typed_text_pointer(out,base,&p->adj);normalize_RoleName(out,base,&p->individual);}
static void normalize_Gender(unsigned char*out,const void*base,const struct Gender*p){typed_text_pointer(out,base,&p->adj);}
static void normalize_instance_globals_i(unsigned char*out,const void*base,const struct instance_globals_i*p){typed_pointer(out,base,&p->invent);}
static void normalize_you(unsigned char*out,const void*base,const struct you*p){normalize_d_level(out,base,&p->uz);for(int i0=0;i0<69;i0++){normalize_prop(out,base,&p->uprops[i0]);}normalize_attribs(out,base,&p->macurr);normalize_attribs(out,base,&p->mamax);normalize_u_conduct(out,base,&p->uconduct);normalize_attribs(out,base,&p->acurr);normalize_attribs(out,base,&p->amax);typed_pointer(out,base,&p->ustuck);typed_pointer(out,base,&p->usteed);}
static void normalize_instance_globals_m(unsigned char*out,const void*base,const struct instance_globals_m*p){typed_text_pointer(out,base,&p->multi_reason);}
static void normalize_dlevel_t(unsigned char*out,const void*base,const dlevel_t*p){for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){normalize_rm(out,base,&p->locations[i0][i1]);}}for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){typed_pointer(out,base,&p->objects[i0][i1]);}}typed_pointer(out,base,&p->monlist);}
static void normalize_instance_globals_n(unsigned char*out,const void*base,const struct instance_globals_n*p){typed_text_pointer(out,base,&p->nomovemsg);}
static void normalize_kinfo(unsigned char*out,const void*base,const struct kinfo*p){}
static void normalize_mvitals(unsigned char*out,const void*base,const struct mvitals*p){}
static void normalize_instance_globals_s(unsigned char*out,const void*base,const struct instance_globals_s*p){}
static void normalize_sinfo(unsigned char*out,const void*base,const struct sinfo*p){}
static void normalize_instance_globals_u(unsigned char*out,const void*base,const struct instance_globals_u*p){normalize_Role(out,base,&p->urole);normalize_Race(out,base,&p->urace);}
static void normalize_instance_globals_v(unsigned char*out,const void*base,const struct instance_globals_v*p){typed_pointer(out,base,&p->viz_array);}
static void normalize_instance_globals_w(unsigned char*out,const void*base,const struct instance_globals_w*p){}
static void normalize_instance_globals_y(unsigned char*out,const void*base,const struct instance_globals_y*p){normalize_monst(out,base,&p->youmonst);}
static void normalize_instance_globals_saved_c(unsigned char*out,const void*base,const struct instance_globals_saved_c*p){normalize_context_info(out,base,&p->context);}
static void normalize_instance_globals_saved_d(unsigned char*out,const void*base,const struct instance_globals_saved_d*p){normalize_dgn_topology(out,base,&p->dungeon_topology);}
static void normalize_instance_globals_saved_k(unsigned char*out,const void*base,const struct instance_globals_saved_k*p){normalize_kinfo(out,base,&p->killer);}
static void normalize_instance_globals_saved_l(unsigned char*out,const void*base,const struct instance_globals_saved_l*p){normalize_dlevel_t(out,base,&p->level);}
static void normalize_instance_globals_saved_m(unsigned char*out,const void*base,const struct instance_globals_saved_m*p){for(int i0=0;i0<383;i0++){normalize_mvitals(out,base,&p->mvitals[i0]);}}
static void normalize_instance_globals_saved_p(unsigned char*out,const void*base,const struct instance_globals_saved_p*p){}
static void dump(char**out,const void*data,size_t n,void(*norm)(unsigned char*,const void*,const void*)){unsigned char bytes[n];memcpy(bytes,data,n);if(norm)norm(bytes,data,data);static const char hex[]="0123456789abcdef";for(size_t i=0;i<n;i++){*(*out)++=hex[bytes[i]>>4];*(*out)++=hex[bytes[i]&15];}}
const char*probe_snapshot(void){char*out=statebuf;
#define DUMP(v,t) dump(&out,&(v),sizeof(v),(void(*)(unsigned char*,const void*,const void*))normalize_##t)
DUMP(u,you);DUMP(gy.youmonst,monst);for(int i=0;i<16;i++)DUMP(objpool[i],obj);for(int i=0;i<8;i++)DUMP(mpool[i],monst);DUMP(trap,trap);DUMP(svc.context,context_info);DUMP(gu,instance_globals_u);DUMP(svk.killer,kinfo);DUMP(disp,display_hints);DUMP(flags,flag);DUMP(gw,instance_globals_w);DUMP(gn,instance_globals_n);DUMP(gs,instance_globals_s);DUMP(gi,instance_globals_i);DUMP(gm,instance_globals_m);DUMP(gv,instance_globals_v);DUMP(svp,instance_globals_saved_p);DUMP(svl.level,dlevel_t);
#undef DUMP
out+=sprintf(out,";equip:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;multi:%ld;",oid(uwep),oid(uswapwep),oid(uarm),oid(uarmc),oid(uarmu),oid(uarmh),oid(uarmg),oid(uarms),oid(uarmf),oid(uamul),oid(ublindf),oid(uskin),gm.multi);*out=0;return statebuf;}
void probe_reset(void){
memset((void*)&mons,0,sizeof mons);
memset((void*)&u,0,sizeof u);
memset((void*)&gy,0,sizeof gy);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&gu,0,sizeof gu);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gw,0,sizeof gw);
memset((void*)&disp,0,sizeof disp);
memset((void*)&uamul,0,sizeof uamul);
memset((void*)&flags,0,sizeof flags);
memset((void*)&gm,0,sizeof gm);
memset((void*)&svk,0,sizeof svk);
memset((void*)&svp,0,sizeof svp);
memset((void*)&gs,0,sizeof gs);
memset((void*)&uarmg,0,sizeof uarmg);
memset((void*)&uarm,0,sizeof uarm);
memset((void*)&svm,0,sizeof svm);
memset((void*)&uskin,0,sizeof uskin);
memset((void*)&svd,0,sizeof svd);
memset((void*)&uball,0,sizeof uball);
memset((void*)&gv,0,sizeof gv);
memset((void*)&gi,0,sizeof gi);
memset((void*)&uarmc,0,sizeof uarmc);
memset((void*)&uarmu,0,sizeof uarmu);
memset((void*)&uarmh,0,sizeof uarmh);
memset((void*)&objects,0,sizeof objects);
memset((void*)&uarms,0,sizeof uarms);
memset((void*)&uarmf,0,sizeof uarmf);
memset((void*)&ublindf,0,sizeof ublindf);
memset((void*)&uswapwep,0,sizeof uswapwep);
memset((void*)&svl,0,sizeof svl);
memset((void*)&gn,0,sizeof gn);
memset((void*)&svc,0,sizeof svc);
memset(objpool,0,sizeof objpool);memset(mpool,0,sizeof mpool);memset(&trap,0,sizeof trap);memset(&delayed,0,sizeof delayed);memset(opts,0,sizeof opts);memset(input,0,sizeof input);memset(vis,0,sizeof vis);tracepos=0;tracebuf[0]=0;seed=1;linecount=0;reentered=0;if(growth){free(growth);growth=0;}
for(int y=0;y<ROWNO;y++){visrows[y]=vis[y];for(int x=0;x<COLNO;x++)levl[x][y].typ=ROOM;}gv.viz_array=visrows;
for(int i=0;i<NUMMONS+1;i++){memcpy((void*)&mons[i].pmidx,&i,sizeof i);mons[i].mlevel=5;mons[i].msize=MZ_MEDIUM;mons[i].mlet=S_HUMAN;mons[i].mattk[0].aatyp=AT_WEAP;mons[i].mattk[0].adtyp=AD_PHYS;mons[i].mattk[0].damn=2;mons[i].mattk[0].damd=6;mons[i].mflags1=M1_HUMANOID;}
u.ux=20;u.uy=10;u.uz.dnum=1;u.uz.dlevel=3;u.ulevel=u.ulevelmax=10;u.uhp=u.uhpmax=40;u.uen=u.uenmax=30;u.mh=u.mhmax=50;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;u.acurr.a[A_STR]=u.amax.a[A_STR]=18;
gu.urole.mnum=PM_ARCHEOLOGIST;gu.urole.name.m="role";gu.urole.name.f="rolef";gu.urace.mnum=PM_HUMAN;gu.urace.noun="human";gu.urace.individual.m="human";gu.urace.individual.f="humanf";gu.urace.attrmax[A_STR]=18;
gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mnum=PM_HUMAN;gy.youmonst.cham=NON_PM;gy.youmonst.m_id=1;gy.youmonst.mcansee=gy.youmonst.mcanmove=1;
for(int i=0;i<16;i++){objpool[i].otyp=LONG_SWORD;objpool[i].oclass=WEAPON_CLASS;objpool[i].quan=1;snprintf(labelbuf[i],sizeof labelbuf[i],"name%d",i);}
for(int i=0;i<8;i++){mpool[i].data=&mons[PM_HUMAN];mpool[i].mnum=PM_HUMAN;mpool[i].m_id=100+i;mpool[i].mx=20+i;mpool[i].my=10;mpool[i].mhp=mpool[i].mhpmax=20;mpool[i].mcansee=mpool[i].mcanmove=1;}
opts[6]=1;opts[9]=1;}
void probe_option(int i,int v){if(i<0||i>=256)abort();opts[i]=v;if(i==48)seed=v;}
void probe_equipment(int k,int i){struct obj*o=i<0?0:&objpool[i];switch(k){case 0:uwep=o;break;case 1:uswapwep=o;break;case 2:uarm=o;break;case 3:uarmc=o;break;case 4:uarmu=o;break;case 5:uarmh=o;break;case 6:uarmg=o;break;case 7:uarms=o;break;case 8:uarmf=o;break;case 9:uamul=o;break;case 10:ublindf=o;break;case 11:uskin=o;break;}}
void*probe_pointer(int k,int i){switch(k){case 0:return &mpool[i];case 1:return &objpool[i];case 2:return &mons[i];case 3:return &objects[i];case 4:return &trap;case 5:return input;case 6:return &gy.youmonst;case 7:return &delayed;case 8:return &pmcopies[i];default:abort();}}
void probe_copy_permonst(int target,int source){memcpy(&pmcopies[target],&mons[source],sizeof pmcopies[target]);}
void probe_vision(int mask){for(int y=0;y<ROWNO;y++)for(int x=0;x<COLNO;x++)vis[y][x]=mask;}
const char*probe_trace(void){return tracebuf;}
int probe_lines(void){return linecount;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return sizeof polyself_layout/sizeof polyself_layout[0];}
const char*probe_layout_name(int i){return polyself_layout[i].name;}
uint64_t probe_layout_value(int i){return polyself_layout[i].value;}
void probe_call_set_uasmon(){set_uasmon();}
void probe_call_float_vs_flight(){float_vs_flight();}
void probe_call_steed_vs_stealth(){steed_vs_stealth();}
void probe_call_check_strangling(boolean on){check_strangling(on);}
void probe_call_polyman(const char * fmt,const char * arg){polyman(fmt,arg);}
void probe_call_change_sex(){change_sex();}
void probe_call_livelog_newform(boolean viapoly,int oldgend,int newgend){livelog_newform(viapoly,oldgend,newgend);}
void probe_call_newman(){newman();}
void probe_call_polyself(int psflags){polyself(psflags);}
int probe_call_polymon(int mntmp){return polymon(mntmp);}
schar probe_call_uasmon_maxStr(){return uasmon_maxStr();}
void probe_call_dropp(struct obj * obj){dropp(obj);}
void probe_call_break_armor(){break_armor();}
void probe_call_drop_weapon(int alone){drop_weapon(alone);}
void probe_call_rehumanize(){rehumanize();}
int probe_call_dobreathe(){return dobreathe();}
int probe_call_dospit(){return dospit();}
int probe_call_doremove(){return doremove();}
int probe_call_dospinweb(){return dospinweb();}
int probe_call_dosummon(){return dosummon();}
int probe_call_dogaze(){return dogaze();}
int probe_call_dohide(){return dohide();}
int probe_call_dopoly(){return dopoly();}
int probe_call_domindblast(){return domindblast();}
void probe_call_uunstick(){uunstick();}
void probe_call_skinback(boolean silently){skinback(silently);}
const char * probe_call_mbodypart(struct monst * mon,int part){return mbodypart(mon,part);}
const char * probe_call_body_part(int part){return body_part(part);}
int probe_call_poly_gender(){return poly_gender();}
void probe_call_ugolemeffects(int damtype,int dam){ugolemeffects(damtype,dam);}
int probe_call_armor_to_dragon(int atyp){return armor_to_dragon(atyp);}
void probe_call_polysense(){polysense();}
boolean probe_call_ugenocided(){return ugenocided();}
const char * probe_call_udeadinside(){return udeadinside();}
