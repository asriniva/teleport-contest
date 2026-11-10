/* Private READ actual-C/imported-JS differential; foreign world is controlled. */
#define NEED_VARARGS
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <setjmp.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(ubirthday) ubirthday;
__typeof__(gk) gk;
__typeof__(flags) flags;
__typeof__(u) u;
__typeof__(uarm) uarm;
__typeof__(uarmu) uarmu;
__typeof__(gu) gu;
__typeof__(gy) gy;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(uball) uball;
__typeof__(svl) svl;
__typeof__(gm) gm;
__typeof__(gv) gv;
__typeof__(svd) svd;
__typeof__(uarmc) uarmc;
__typeof__(uarmh) uarmh;
__typeof__(uarms) uarms;
__typeof__(uarmg) uarmg;
__typeof__(uarmf) uarmf;
__typeof__(gi) gi;
__typeof__(uswapwep) uswapwep;
__typeof__(uquiver) uquiver;
__typeof__(uwep) uwep;
__typeof__(svm) svm;
__typeof__(disp) disp;
__typeof__(svp) svp;
__typeof__(iflags) iflags;
__typeof__(a11y) a11y;
__typeof__(uchain) uchain;
__typeof__(svr) svr;
__typeof__(svk) svk;
const struct c_common_strings c_common_strings =
    { "Nothing happens.",
      "Nothing seems to happen.",
      "That's enough tries!",
      "That is a silly thing to %s.",
      "shudder for a moment.",
      "something",
      "Something",
      "You can move again.",
      "Never mind.",
      "vision quickly clears.",
      { "the", "your" },
      { "mon", "you" }
};
NEARDATA const struct c_color_names c_color_names = {
    "black",  "amber", "golden", "light blue", "red",   "green",
    "silver", "blue",  "purple", "white",      "orange"
};
const struct class_sym def_monsyms[MAXMCLASSES] = {
    { '\0', "", "" },
#define MONSYMS_DRAWING
#include "defsym.h"
#undef MONSYMS_DRAWING
};
const struct Gender genders[] = {
    { "male", "he", "him", "his", "Mal", ROLE_MALE },
    { "female", "she", "her", "her", "Fem", ROLE_FEMALE },
    { "neuter", "it", "it", "its", "Ntr", ROLE_NEUTER },
    /* used by pronoun_gender() when hallucinating */
    { "group", "they", "them", "their", "Grp", 0 },
};
const char ynchars[] = "yn";
static struct obj object_pool[64];static struct monst monster_pool[16];static struct _create_particular_data creation;
static int opts[128],object_next,allocation_count,callback_depth;static unsigned rngstate;static jmp_buf fixture_jump;static void*growth;
static char tracebuf[2097152],snapshotbuf[262144],buf[4096],namesbuf[32][128],inputbuf[BUFSZ];static char origin[128];
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static int id(const void*p){if(!p)return-1;uintptr_t n=(uintptr_t)p;if(n>=(uintptr_t)object_pool&&n<(uintptr_t)(object_pool+64))return 1000+(int)(n-(uintptr_t)object_pool);if(n>=(uintptr_t)monster_pool&&n<(uintptr_t)(monster_pool+16))return 100000+(int)(n-(uintptr_t)monster_pool);if(n>=(uintptr_t)mons&&n<(uintptr_t)(mons+NUMMONS+1))return 1000000+(int)(n-(uintptr_t)mons);return 999;}
static void callback(void);
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*f,int line,const char*fn){snprintf(origin,sizeof origin,"%s:%d:%s",f,line,fn);}
int(rn2)(int n){if(n<=0){logmsg("BADRNG:%d;",n);longjmp(fixture_jump,1);}rngstate=rngstate*1664525u+1013904223u;int result=(rngstate>>8)%n;logmsg("rng:%d:%d@%s;",n,result,origin);return result;}
int(rnd)(int n){return(rn2)(n)+1;}int(d)(int n,int x){int result=0;for(int i=0;i<n;i++)result+=(rn2)(x)+1;return result;}
long*alloc(unsigned n){void*p=malloc(n);allocation_count++;logmsg("alloc:%u;",n);if(!p)longjmp(fixture_jump,1);return p;}
#define MESSAGE(fn) void fn(const char*f,...){va_list ap;va_start(ap,f);logmsg(#fn ":");vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");callback();}
MESSAGE(pline)MESSAGE(pline_The)MESSAGE(urgent_pline)MESSAGE(You)MESSAGE(Your)MESSAGE(You_feel)MESSAGE(You_cant)MESSAGE(You_hear)MESSAGE(verbalize)MESSAGE(impossible)
void livelog_printf(long mask,const char*f,...){va_list ap;va_start(ap,f);logmsg("log:%ld:",mask);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void nh_snprintf(const char*fn,int line,char*out,size_t n,const char*f,...){va_list ap;va_start(ap,f);logmsg("snprintf:%s:%d;",fn,line);vsnprintf(out,n,f,ap);va_end(ap);}
int sgn(int n){return(n>0)-(n<0);}int dist2(coordxy x,coordxy y,coordxy a,coordxy b){return(x-a)*(x-a)+(y-b)*(y-b);}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
char*eos(char*s){return s+strlen(s);}boolean digit(char c){return c>='0'&&c<='9';}char lowc(char c){return c>='A'&&c<='Z'?c+32:c;}
void wipeout_text(char*s,int n,unsigned seed){logmsg("wipe:%d:%u;",n,seed);int len=strlen(s);for(int i=0;i<n&&len;i++){seed=seed*1103515245u+12345;s[(seed>>16)%len]='?';}}
static char*namecopy(const char*s){static unsigned n;char*p=namesbuf[(n++)%32];snprintf(p,128,"%s",s);return p;}
char*makeplural(const char*s){char*p=namecopy(s);if(strlen(p)<126)strcat(p,"s");return p;}char*an(const char*s){char*p=namecopy("");snprintf(p,128,"an %s",s);return p;}
char*xname(struct obj*o){char*p=namecopy("");snprintf(p,128,"object%d",o->otyp);return p;}char*doname(struct obj*o){return xname(o);}
const char*pmname(struct permonst*p,int gender){char*s=namecopy("");snprintf(s,128,"creature%d%c",p->pmidx,gender?'F':'M');return s;}
const char*singular(struct obj*o,char*(*fn)(struct obj*)){return fn(o);}
struct obj*getobj(const char*verb,int(*fn)(struct obj*),unsigned flags_){struct obj*o=opts[0]?0:&object_pool[0];logmsg("getobj:%s:%u:%d;",verb,flags_,fn(o));callback();return o;}
void getlin(const char*prompt,char*out){logmsg("getlin:%s;",prompt);strcpy(out,inputbuf);}
void do_clear_area(coordxy x,coordxy y,int radius,void(*fn)(coordxy,coordxy,void*),genericptr_t value){logmsg("area:%d:%d:%d;",x,y,radius);for(int dx=-1;dx<=1;dx++)for(int dy=-1;dy<=1;dy++)if(isok(x+dx,y+dy))fn(x+dx,y+dy,value);callback();}
void getpos_sethilite(void(*display)(boolean),boolean(*valid)(coordxy,coordxy)){logmsg("hilite:%d;",valid(u.ux,u.uy));if(opts[10]){display(TRUE);display(FALSE);}}
int getpos(coord*c,boolean force,const char*goal){logmsg("getpos:%d:%s;",force,goal);c->x=u.ux;c->y=u.uy;return opts[11]?-1:0;}
struct obj*mksobj(int typ,boolean init,boolean arti){logmsg("mksobj:%d:%d:%d;",typ,init,arti);struct obj*o=&object_pool[(object_next++)%64];memset(o,0,sizeof*o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;return o;}
struct obj*mkobj(int cls,boolean arti){logmsg("mkobj:%d;",cls);return mksobj(DAGGER,TRUE,arti);}
struct obj*some_armor(struct monst*m){logmsg("armor:%d;",id(m));return opts[1]?0:uarm;}
struct obj*which_armor(struct monst*m,long mask){logmsg("whicharmor:%d:%ld;",id(m),mask);return opts[1]?0:uarmh;}
void make_confused(long n,boolean message){HConfusion=n;logmsg("confuse:%ld:%d;",n,message);}void make_stunned(long n,boolean message){HStun=n;logmsg("stun:%ld:%d;",n,message);}
void useup(struct obj*o){logmsg("useup:%d;",id(o));o->in_use=0;callback();}void strange_feeling(struct obj*o,const char*s){logmsg("strange:%d:%s;",id(o),s?s:"");useup(o);}
boolean is_art(struct obj*o,int n){return o&&o->oartifact==n;}
int bcsign(struct obj*o){return o->blessed-o->cursed;}
int strncmpi(const char*a,const char*b,int n){while(n&&*a&&lowc(*a)==lowc(*b)){a++;b++;if(n>0)n--;}return n?lowc(*a)-lowc(*b):0;}
char*strstri(const char*s,const char*part){size_t n=strlen(part);for(;*s;s++)if(!strncmpi(s,part,(int)n))return(char*)s;return n?0:(char*)s;}
char*mungspaces(char*s){char*in=s,*out=s;while(*in==' ')in++;for(;*in;in++){if(*in==' '&&(out==s||out[-1]==' '))continue;*out++=*in;}if(out>s&&out[-1]==' ')out--;*out=0;return s;}
int name_to_mon(const char*s,int*gender){logmsg("name_to_mon:%s;",s);if(gender)*gender=opts[5]?FEMALE:NEUTRAL;return opts[4]?NON_PM:PM_HUMAN;}
int name_to_monclass(const char*s,int*type){logmsg("name_to_monclass:%s;",s);if(type)*type=NON_PM;return opts[6]?S_ORC:0;}
boolean In_hell(d_level * a0){logmsg("In_hell;");return opts[3];}
boolean In_mines(d_level * a0){logmsg("In_mines;");return opts[3];}
char * Monnam(struct monst * a0){logmsg("Monnam;");return namecopy("fixture");}
void Ring_gone(struct obj * a0){logmsg("Ring_gone;");}
void Ring_off(struct obj * a0){logmsg("Ring_off;");}
void Ring_on(struct obj * a0){logmsg("Ring_on;");}
char * Tobjnam(struct obj * a0,const char * a1){logmsg("Tobjnam;");return namecopy("fixture");}
char * Yname2(struct obj * a0){logmsg("Yname2;");return namecopy("fixture");}
char * Yobjnam2(struct obj * a0,const char * a1){logmsg("Yobjnam2;");return namecopy("fixture");}
char * actualoname(struct obj * a0){logmsg("actualoname;");return namecopy("fixture");}
void adj_abon(struct obj * a0,schar a1){logmsg("adj_abon;");}
void adjalign(int a0){logmsg("adjalign;");}
void alter_cost(struct obj * a0,long a1){logmsg("alter_cost;");}
int any_worn_armor_ok(struct obj * a0){logmsg("any_worn_armor_ok;");return opts[3];}
int arti_light_radius(struct obj * a0){logmsg("arti_light_radius;");return opts[3];}
boolean artifact_light(struct obj * a0){logmsg("artifact_light;");return opts[3];}
boolean avoid_ceiling(d_level * a0){logmsg("avoid_ceiling;");return opts[3];}
void bless(struct obj * a0){logmsg("bless;");}
void blessorcurse(struct obj * a0,int a1){logmsg("blessorcurse;");}
const char * body_part(int a0){logmsg("body_part;");return namecopy("fixture");}
void buried_ball_to_freedom(void){logmsg("buried_ball_to_freedom;");}
void burn_away_slime(void){logmsg("burn_away_slime;");}
boolean can_chant(struct monst * a0){logmsg("can_chant;");return opts[3];}
boolean can_saddle(struct monst * a0){logmsg("can_saddle;");return opts[3];}
int canseemon(struct monst * a0){logmsg("canseemon;");return opts[3];}
const char * ceiling(coordxy a0,coordxy a1){logmsg("ceiling;");return namecopy("fixture");}
boolean check_capacity(const char * a0){logmsg("check_capacity;");return opts[3];}
int chwepon(struct obj * a0,int a1){logmsg("chwepon;");return opts[3];}
boolean closed_door(coordxy a0,coordxy a1){logmsg("closed_door;");return opts[3];}
void costly_alteration(struct obj * a0,int a1){logmsg("costly_alteration;");}
int count_worn_armor(void){logmsg("count_worn_armor;");return opts[3];}
boolean create_critters(int a0,struct permonst * a1,boolean a2){logmsg("create_critters;");return opts[3];}
NhRegion * create_gas_cloud(coordxy a0,coordxy a1,int a2,int a3){logmsg("create_gas_cloud;");return 0;}
void curse(struct obj * a0){logmsg("curse;");}
void cvt_sdoor_to_door(struct rm * a0){logmsg("cvt_sdoor_to_door;");}
void delayed_killer(int a0,int a1,const char * a2){logmsg("delayed_killer;");}
void delobj(struct obj * a0){logmsg("delobj;");}
int destroy_arm(void){logmsg("destroy_arm;");return opts[3];}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object;");}
int disintegrate_arm(struct obj * a0){logmsg("disintegrate_arm;");return opts[3];}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){logmsg("dmgtype_fromattack;");return 0;}
int dmgval(struct obj * a0,struct monst * a1){logmsg("dmgval;");return opts[3];}
void do_mapping(void){logmsg("do_mapping;");}
void done(int a0){logmsg("done;");}
void drain_weapon_skill(int a0){logmsg("drain_weapon_skill;");}
void dropy(struct obj * a0){logmsg("dropy;");}
void end_burn(struct obj * a0,boolean a1){logmsg("end_burn;");}
boolean erosion_matters(struct obj * a0){logmsg("erosion_matters;");return opts[3];}
void exercise(int a0,boolean a1){logmsg("exercise;");}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logmsg("explode;");}
void flash_mon(struct monst * a0){logmsg("flash_mon;");}
boolean flooreffects(struct obj * a0,coordxy a1,coordxy a2,const char * a3){logmsg("flooreffects;");return opts[3];}
int food_detect(struct obj * a0){logmsg("food_detect;");return opts[3];}
int gold_detect(struct obj * a0){logmsg("gold_detect;");return opts[3];}
boolean hard_helmet(struct obj * a0){logmsg("hard_helmet;");return opts[3];}
boolean has_ceiling(d_level * a0){logmsg("has_ceiling;");return opts[3];}
const char * hcolor(const char * a0){logmsg("hcolor;");return namecopy("fixture");}
const char * hliquid(const char * a0){logmsg("hliquid;");return namecopy("fixture");}
void identify_pack(int a0,boolean a1){logmsg("identify_pack;");}
void impact_arti_light(struct obj * a0,boolean a1,boolean a2){logmsg("impact_arti_light;");}
void initedog(struct monst * a0,boolean a1){logmsg("initedog;");}
boolean is_lava(coordxy a0,coordxy a1){logmsg("is_lava;");return opts[3];}
boolean is_pool(coordxy a0,coordxy a1){logmsg("is_pool;");return opts[3];}
void kill_genocided_monsters(void){logmsg("kill_genocided_monsters;");}
void killed(struct monst * a0){logmsg("killed;");}
void level_tele(void){logmsg("level_tele;");}
void light_hits_gremlin(struct monst * a0,int a1){logmsg("light_hits_gremlin;");}
int lightdamage(struct obj * a0,boolean a1,int a2){logmsg("lightdamage;");return opts[3];}
void list_genocided(char a0,boolean a1){logmsg("list_genocided;");}
void losehp(int a0,const char * a1,schar a2){logmsg("losehp;");}
void losespells(void){logmsg("losespells;");}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logmsg("makemon;");return opts[2]?0:&monster_pool[1];}
void map_invisible(coordxy a0,coordxy a1){logmsg("map_invisible;");}
void maybe_adjust_light(struct obj * a0,int a1){logmsg("maybe_adjust_light;");}
const char * mbodypart(struct monst * a0,int a1){logmsg("mbodypart;");return namecopy("fixture");}
struct permonst * mkclass(char a0,int a1){logmsg("mkclass;");return opts[7]?0:&mons[PM_HUMAN];}
char * mon_nam(struct monst * a0){logmsg("mon_nam;");return namecopy("fixture");}
void mondied(struct monst * a0){logmsg("mondied;");}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){logmsg("monflee;");}
void mongone(struct monst * a0){logmsg("mongone;");}
int monster_census(boolean a0){logmsg("monster_census;");return opts[3];}
void monstseesu(unsigned long a0){logmsg("monstseesu;");}
void monstunseesu(unsigned long a0){logmsg("monstunseesu;");}
void more_experienced(int a0,int a1){logmsg("more_experienced;");}
void move_bc(int a0,int a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5){logmsg("move_bc;");}
int newcham(struct monst * a0,struct permonst * a1,unsigned int a2){logmsg("newcham;");return opts[3];}
void newsym(coordxy a0,coordxy a1){logmsg("newsym;");}
int num_genocides(void){logmsg("num_genocides;");return opts[3];}
void obfree(struct obj * a0,struct obj * a1){logmsg("obfree;");}
char * otense(struct obj * a0,const char * a1){logmsg("otense;");return namecopy("fixture");}
void outrumor(int a0,int a1){logmsg("outrumor;");}
void place_object(struct obj * a0,coordxy a1,coordxy a2){logmsg("place_object;");}
void placebc(void){logmsg("placebc;");}
void polyself(int a0){logmsg("polyself;");}
int pronoun_gender(struct monst * a0,unsigned int a1){logmsg("pronoun_gender;");return opts[3];}
void put_saddle_on_mon(struct obj * a0,struct monst * a1){logmsg("put_saddle_on_mon;");}
short quest_info(int a0){logmsg("quest_info;");return opts[3];}
void readmail(struct obj * a0){logmsg("readmail;");}
void rehumanize(void){logmsg("rehumanize;");}
void remove_worn_item(struct obj * a0,boolean a1){logmsg("remove_worn_item;");}
int resist(struct monst * a0,char a1,int a2,int a3){logmsg("resist;");return opts[3];}
struct permonst * rndmonst(void){logmsg("rndmonst;");return opts[7]?0:&mons[PM_HUMAN];}
char * s_suffix(const char * a0){logmsg("s_suffix;");return namecopy("fixture");}
void scrolltele(struct obj * a0){logmsg("scrolltele;");}
int sensemon(struct monst * a0){logmsg("sensemon;");return opts[3];}
void set_bc(int a0){logmsg("set_bc;");}
void set_malign(struct monst * a0){logmsg("set_malign;");}
void setmangry(struct monst * a0,boolean a1){logmsg("setmangry;");}
void setworn(struct obj * a0,long a1){logmsg("setworn;");}
void shieldeff(coordxy a0,coordxy a1){logmsg("shieldeff;");}
char * shk_your(char * a0,struct obj * a1){logmsg("shk_your;");return namecopy("fixture");}
char * simpleonames(struct obj * a0){logmsg("simpleonames;");return namecopy("fixture");}
void snuff_light_source(coordxy a0,coordxy a1){logmsg("snuff_light_source;");}
boolean snuff_lit(struct obj * a0){logmsg("snuff_lit;");return opts[3];}
void sokoban_guilt(void){logmsg("sokoban_guilt;");}
void stackobj(struct obj * a0){logmsg("stackobj;");}
int study_book(struct obj * a0){logmsg("study_book;");return opts[3];}
const char * suit_simple_name(struct obj * a0){logmsg("suit_simple_name;");return namecopy("fixture");}
boolean tamedog(struct monst * a0,struct obj * a1,boolean a2){logmsg("tamedog;");return opts[3];}
void tmp_at(coordxy a0,coordxy a1){logmsg("tmp_at;");}
int trap_detect(struct obj * a0){logmsg("trap_detect;");return opts[3];}
void trycall(struct obj * a0){logmsg("trycall;");}
const char * udeadinside(void){logmsg("udeadinside;");return namecopy("fixture");}
void unblock_point(int a0,int a1){logmsg("unblock_point;");}
void uncurse(struct obj * a0){logmsg("uncurse;");}
void update_inventory(void){logmsg("update_inventory;");}
char * upstart(char * a0){logmsg("upstart;");return namecopy("fixture");}
char * upwords(char * a0){logmsg("upwords;");return namecopy("fixture");}
void vision_recalc(int a0){logmsg("vision_recalc;");}
char * vtense(const char * a0,const char * a1){logmsg("vtense;");return namecopy("fixture");}
void wake_nearto(coordxy a0,coordxy a1,int a2){logmsg("wake_nearto;");}
void wakeup(struct monst * a0,boolean a1){logmsg("wakeup;");}
int weight(struct obj * a0){logmsg("weight;");return opts[3];}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){logmsg("yn_function;");return opts[3];}
#ifdef TELEPORT_REFERENCE_TU
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/read.c"
#else
extern boolean teleport_read_test_learnscrolltyp(short);
#define learnscrolltyp teleport_read_test_learnscrolltyp
extern void teleport_read_test_cap_spe(struct obj *);
#define cap_spe teleport_read_test_cap_spe
extern char * teleport_read_test_erode_obj_text(struct obj *,char *);
#define erode_obj_text teleport_read_test_erode_obj_text
extern char * teleport_read_test_hawaiian_design(struct obj *,char *);
#define hawaiian_design teleport_read_test_hawaiian_design
extern int teleport_read_test_read_ok(struct obj *);
#define read_ok teleport_read_test_read_ok
extern void teleport_read_test_stripspe(struct obj *);
#define stripspe teleport_read_test_stripspe
extern void teleport_read_test_p_glow1(struct obj *);
#define p_glow1 teleport_read_test_p_glow1
extern void teleport_read_test_p_glow2(struct obj *,const char *);
#define p_glow2 teleport_read_test_p_glow2
extern void teleport_read_test_p_glow3(struct obj *,const char *);
#define p_glow3 teleport_read_test_p_glow3
extern void teleport_read_test_forget(int);
#define forget teleport_read_test_forget
extern int teleport_read_test_maybe_tame(struct monst *,struct obj *);
#define maybe_tame teleport_read_test_maybe_tame
extern boolean teleport_read_test_can_center_cloud(coordxy,coordxy);
#define can_center_cloud teleport_read_test_can_center_cloud
extern void teleport_read_test_display_stinking_cloud_positions(boolean);
#define display_stinking_cloud_positions teleport_read_test_display_stinking_cloud_positions
extern void teleport_read_test_seffect_enchant_armor(struct obj **);
#define seffect_enchant_armor teleport_read_test_seffect_enchant_armor
extern boolean teleport_read_test_disintegrate_cursed_armor(void);
#define disintegrate_cursed_armor teleport_read_test_disintegrate_cursed_armor
extern void teleport_read_test_seffect_destroy_armor(struct obj **);
#define seffect_destroy_armor teleport_read_test_seffect_destroy_armor
extern void teleport_read_test_seffect_confuse_monster(struct obj **);
#define seffect_confuse_monster teleport_read_test_seffect_confuse_monster
extern void teleport_read_test_seffect_scare_monster(struct obj **);
#define seffect_scare_monster teleport_read_test_seffect_scare_monster
extern void teleport_read_test_seffect_remove_curse(struct obj **);
#define seffect_remove_curse teleport_read_test_seffect_remove_curse
extern void teleport_read_test_seffect_create_monster(struct obj **);
#define seffect_create_monster teleport_read_test_seffect_create_monster
extern void teleport_read_test_seffect_enchant_weapon(struct obj **);
#define seffect_enchant_weapon teleport_read_test_seffect_enchant_weapon
extern void teleport_read_test_seffect_taming(struct obj **);
#define seffect_taming teleport_read_test_seffect_taming
extern void teleport_read_test_seffect_genocide(struct obj **);
#define seffect_genocide teleport_read_test_seffect_genocide
extern void teleport_read_test_seffect_light(struct obj **);
#define seffect_light teleport_read_test_seffect_light
extern void teleport_read_test_seffect_charging(struct obj **);
#define seffect_charging teleport_read_test_seffect_charging
extern void teleport_read_test_seffect_amnesia(struct obj **);
#define seffect_amnesia teleport_read_test_seffect_amnesia
extern void teleport_read_test_seffect_fire(struct obj **);
#define seffect_fire teleport_read_test_seffect_fire
extern void teleport_read_test_seffect_earth(struct obj **);
#define seffect_earth teleport_read_test_seffect_earth
extern void teleport_read_test_seffect_punishment(struct obj **);
#define seffect_punishment teleport_read_test_seffect_punishment
extern void teleport_read_test_seffect_stinking_cloud(struct obj **);
#define seffect_stinking_cloud teleport_read_test_seffect_stinking_cloud
extern void teleport_read_test_seffect_blank_paper(struct obj **);
#define seffect_blank_paper teleport_read_test_seffect_blank_paper
extern void teleport_read_test_seffect_teleportation(struct obj **);
#define seffect_teleportation teleport_read_test_seffect_teleportation
extern void teleport_read_test_seffect_gold_detection(struct obj **);
#define seffect_gold_detection teleport_read_test_seffect_gold_detection
extern void teleport_read_test_seffect_food_detection(struct obj **);
#define seffect_food_detection teleport_read_test_seffect_food_detection
extern void teleport_read_test_seffect_identify(struct obj **);
#define seffect_identify teleport_read_test_seffect_identify
extern void teleport_read_test_seffect_magic_mapping(struct obj **);
#define seffect_magic_mapping teleport_read_test_seffect_magic_mapping
extern void teleport_read_test_seffect_mail(struct obj **);
#define seffect_mail teleport_read_test_seffect_mail
extern void teleport_read_test_set_lit(coordxy,coordxy,genericptr_t);
#define set_lit teleport_read_test_set_lit
extern void teleport_read_test_do_class_genocide(void);
#define do_class_genocide teleport_read_test_do_class_genocide
extern void teleport_read_test_do_stinking_cloud(struct obj *,boolean);
#define do_stinking_cloud teleport_read_test_do_stinking_cloud
extern boolean teleport_read_test_create_particular_parse(char *,struct _create_particular_data *);
#define create_particular_parse teleport_read_test_create_particular_parse
extern boolean teleport_read_test_create_particular_creation(struct _create_particular_data *);
#define create_particular_creation teleport_read_test_create_particular_creation
#endif
#include "../nethack-c/wasm/tu-fragments/read-support.inc"
#include "tu-read-layout.h"
static void callback(void){if(opts[93])longjmp(fixture_jump,1);if(opts[90]&&!callback_depth){callback_depth++;logmsg("callback;");if(opts[92]&&!growth){growth=malloc(40000000);logmsg("growth:%d;",growth!=0);}if(opts[94]){object_pool[0].spe=3;monster_pool[0].mhp=17;logmsg("write;");}if(opts[91]){char nested[BUFSZ];(void)tshirt_text(&object_pool[1],nested);logmsg("nested:%s;",nested);}callback_depth--;}}
int probe_layout_count(void){return SIZE(read_layout);}const char*probe_layout_name(int i){return read_layout[i].name;}long long probe_layout_value(int i){return read_layout[i].value;}
const char*probe_trace(void){return tracebuf;}const char*probe_buffer(void){return buf;}size_t probe_stack(void){return emscripten_stack_get_current();}
void probe_clear(void){tracebuf[0]=0;buf[0]=0;}void probe_option(int i,int value){opts[i]=value;}void probe_seed(unsigned value){rngstate=value;}
void probe_reset(void){monst_globals_init();objects_globals_init();if(growth){free(growth);growth=0;}memset(opts,0,sizeof opts);memset(object_pool,0,sizeof object_pool);memset(monster_pool,0,sizeof monster_pool);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&svl,0,sizeof svl);memset(&svm,0,sizeof svm);memset(&creation,0,sizeof creation);gi.invent=0;gm.migrating_mons=0;object_next=4;allocation_count=0;callback_depth=0;rngstate=1;tracebuf[0]=0;buf[0]=0;strcpy(inputbuf,"\033");u.ux=10;u.uy=10;u.ulevel=10;u.uhp=100;u.uhpmax=100;u.umonnum=u.umonster=PM_HUMAN;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urace.mnum=PM_HUMAN;uarm=&object_pool[2];uarmh=&object_pool[3];uwep=&object_pool[1];uleft=uright=uball=uchain=0;svl.level.monlist=0;gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<64;i++){object_pool[i].otyp=DAGGER;object_pool[i].oclass=WEAPON_CLASS;object_pool[i].quan=1;object_pool[i].o_id=i+1;object_pool[i].spe=0;}object_pool[0].otyp=SCR_BLANK_PAPER;object_pool[0].oclass=SCROLL_CLASS;for(int i=0;i<16;i++){monster_pool[i].data=&mons[PM_HUMAN];monster_pool[i].mhp=20;monster_pool[i].mhpmax=30;monster_pool[i].m_lev=5;monster_pool[i].mx=10+i;monster_pool[i].my=10;monster_pool[i].m_id=i+1;}static seenV rows[ROWNO][COLNO];static seenV*rowptr[ROWNO];for(int y=0;y<ROWNO;y++){rowptr[y]=rows[y];for(int x=0;x<COLNO;x++){rows[y][x]=IN_SIGHT;svl.level.locations[x][y].typ=ROOM;}}gv.viz_array=rowptr;}
void probe_object(int i,int typ,int spe,int flags_,unsigned oid,long quantity){struct obj*o=&object_pool[i];o->otyp=typ;o->oclass=objects[typ].oc_class;o->spe=spe;o->blessed=flags_&1;o->cursed=(flags_>>1)&1;o->oeroded=(flags_>>2)&3;o->oeroded2=(flags_>>4)&3;o->dknown=(flags_>>6)&1;o->o_id=oid;o->quan=quantity;}
void probe_global(int which,long value){switch(which){case 0:ubirthday=value;break;case 1:flags.verbose=value;break;case 2:flags.debug=value;break;case 3:HConfusion=value;break;case 4:u.uprops[BLINDED].intrinsic=value;break;case 5:u.uroleplay.blind=value;break;case 6:u.uprops[HALLUC].intrinsic=value;break;case 7:u.uprops[HALF_PHDAM].intrinsic=value;break;case 8:object_pool[0].recharged=value;break;case 9:gm.multi=value;break;case 10:u.uswallow=value;break;case 11:u.uinwater=value;break;case 12:u.uprops[UNCHANGING].intrinsic=value;break;}}
void probe_input(const char*s){snprintf(inputbuf,sizeof inputbuf,"%s",s);}
void*probe_pointer(int n){return n?(void*)&object_pool[0]:(void*)&monster_pool[0];}
void probe_scenario(int n,int a,int b){switch(n){case 0:gi.invent=a?&object_pool[0]:0;object_pool[0].nobj=&object_pool[1];object_pool[1].nobj=&object_pool[2];object_pool[2].nobj=0;break;case 1:u.usteed=a?&monster_pool[0]:0;break;case 2:monster_pool[0].data=&mons[a];monster_pool[0].cham=NON_PM;svl.level.monsters[10][10]=&monster_pool[0];svl.level.monlist=&monster_pool[0];break;case 3:uleft=a?&object_pool[0]:0;uright=b?&object_pool[0]:0;break;case 4:u.uroleplay.blind=a;u.uprops[BLINDED].blocked=b;break;case 5:u.uprops[INVIS].intrinsic=a;u.uprops[SEE_INVIS].intrinsic=b;break;case 6:uarm=a?&object_pool[2]:0;uarmc=uarmh=uarms=uarmg=uarmf=uarmu=0;break;}}
const char*probe_snapshot(void){char*p=snapshotbuf;p+=sprintf(p,"rng:%u;alloc:%d;prop:%ld,%ld;known:%d;notices:%d;",rngstate,allocation_count,HConfusion,HStun,gk.known,a11y.mon_notices_blocked);p+=sprintf(p,"creation:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;",creation.quan,creation.monclass,creation.which,creation.fem,creation.genderconf,creation.randmonst,creation.maketame,creation.makepeaceful,creation.makehostile,creation.sleeping,creation.saddled,creation.invisible,creation.hidden,teleport_read_gremlins!=0);for(int i=0;i<64;i++){struct obj*o=&object_pool[i];p+=sprintf(p,"o:%d,%d,%d,%u,%u,%u,%u,%u,%u,%ld,%ld;",o->otyp,o->spe,o->recharged,o->blessed,o->cursed,o->oeroded,o->oeroded2,o->oerodeproof,o->in_use,o->quan,o->owornmask);}for(int i=0;i<16;i++){struct monst*m=&monster_pool[i];p+=sprintf(p,"m:%d,%d,%d,%d,%d,%d;",m->mhp,m->mhpmax,m->mtame,m->mpeaceful,m->msleeping,m->mundetected);}return snapshotbuf;}
long long probe_action(int op,int a,int b,int c){long long result=0;if(setjmp(fixture_jump))return-999;switch(op){
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 0:{struct obj*sobj=&object_pool[0];int mtype=a;result=learnscrolltyp(a);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 1:{struct obj*sobj=&object_pool[0];int mtype=a;learnscroll(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 2:{struct obj*sobj=&object_pool[0];int mtype=a;cap_spe(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 3:{struct obj*sobj=&object_pool[0];int mtype=a;const char*text=erode_obj_text(&object_pool[0],buf);if(text&&text!=buf)snprintf(buf,sizeof buf,"%s",text);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 4:{struct obj*sobj=&object_pool[0];int mtype=a;const char*text=tshirt_text(&object_pool[0],buf);if(text&&text!=buf)snprintf(buf,sizeof buf,"%s",text);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 5:{struct obj*sobj=&object_pool[0];int mtype=a;const char*text=hawaiian_motif(&object_pool[0],buf);if(text&&text!=buf)snprintf(buf,sizeof buf,"%s",text);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 6:{struct obj*sobj=&object_pool[0];int mtype=a;const char*text=hawaiian_design(&object_pool[0],buf);if(text&&text!=buf)snprintf(buf,sizeof buf,"%s",text);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 7:{struct obj*sobj=&object_pool[0];int mtype=a;const char*text=apron_text(&object_pool[0],buf);if(text&&text!=buf)snprintf(buf,sizeof buf,"%s",text);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 8:{struct obj*sobj=&object_pool[0];int mtype=a;const char*text=candy_wrapper_text(&object_pool[0]);if(text&&text!=buf)snprintf(buf,sizeof buf,"%s",text);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 9:{struct obj*sobj=&object_pool[0];int mtype=a;assign_candy_wrapper(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 10:{struct obj*sobj=&object_pool[0];int mtype=a;result=read_ok(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 11:{struct obj*sobj=&object_pool[0];int mtype=a;result=doread();logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 12:{struct obj*sobj=&object_pool[0];int mtype=a;stripspe(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 13:{struct obj*sobj=&object_pool[0];int mtype=a;p_glow1(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 14:{struct obj*sobj=&object_pool[0];int mtype=a;p_glow2(&object_pool[0],"fixture color");logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 15:{struct obj*sobj=&object_pool[0];int mtype=a;p_glow3(&object_pool[0],"fixture color");logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 16:{struct obj*sobj=&object_pool[0];int mtype=a;result=charge_ok(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 17:{struct obj*sobj=&object_pool[0];int mtype=a;recharge(&object_pool[0],a);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 18:{struct obj*sobj=&object_pool[0];int mtype=a;forget(a);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 19:{struct obj*sobj=&object_pool[0];int mtype=a;result=maybe_tame(&monster_pool[0],&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 20:{struct obj*sobj=&object_pool[0];int mtype=a;result=valid_cloud_pos(a,b);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 21:{struct obj*sobj=&object_pool[0];int mtype=a;result=can_center_cloud(a,b);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 22:{struct obj*sobj=&object_pool[0];int mtype=a;display_stinking_cloud_positions(a);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 23:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_enchant_armor(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 24:{struct obj*sobj=&object_pool[0];int mtype=a;result=disintegrate_cursed_armor();logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 25:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_destroy_armor(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 26:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_confuse_monster(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 27:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_scare_monster(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 28:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_remove_curse(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 29:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_create_monster(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 30:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_enchant_weapon(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 31:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_taming(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 32:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_genocide(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 33:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_light(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 34:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_charging(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 35:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_amnesia(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 36:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_fire(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 37:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_earth(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 38:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_punishment(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 39:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_stinking_cloud(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 40:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_blank_paper(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 41:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_teleportation(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 42:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_gold_detection(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 43:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_food_detection(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 44:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_identify(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 45:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_magic_mapping(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 46:{struct obj*sobj=&object_pool[0];int mtype=a;seffect_mail(&sobj);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 47:{struct obj*sobj=&object_pool[0];int mtype=a;result=seffects(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 48:{struct obj*sobj=&object_pool[0];int mtype=a;drop_boulder_on_player(a,b,c,c);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 49:{struct obj*sobj=&object_pool[0];int mtype=a;result=drop_boulder_on_monster(a,b,c,c);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 50:{struct obj*sobj=&object_pool[0];int mtype=a;wand_explode(&object_pool[0],a);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 51:{struct obj*sobj=&object_pool[0];int mtype=a;set_lit(a,b,a?buf:0);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 52:{struct obj*sobj=&object_pool[0];int mtype=a;litroom(a,&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 53:{struct obj*sobj=&object_pool[0];int mtype=a;do_class_genocide();logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 54:{struct obj*sobj=&object_pool[0];int mtype=a;do_genocide(a);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 55:{struct obj*sobj=&object_pool[0];int mtype=a;punish(&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
case 56:{struct obj*sobj=&object_pool[0];int mtype=a;unpunish();logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 57:{struct obj*sobj=&object_pool[0];int mtype=a;do_stinking_cloud(&object_pool[0],a);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 58:{struct obj*sobj=&object_pool[0];int mtype=a;result=cant_revive(&mtype,a,&object_pool[0]);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 59:{struct obj*sobj=&object_pool[0];int mtype=a;result=create_particular_parse(inputbuf,&creation);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 60:{struct obj*sobj=&object_pool[0];int mtype=a;result=create_particular_creation(&creation);logmsg("out:%d:%d;",id(sobj),mtype);break;}
#endif
case 61:{struct obj*sobj=&object_pool[0];int mtype=a;result=create_particular();logmsg("out:%d:%d;",id(sobj),mtype);break;}
default:abort();}return result;}
/* Separate typed-adapter witness: nullable functions guard NULL.
mkobj/mksobj retain their actual ReturnsNonNullAttr contract. */
long long probe_projection(int which){struct obj*o=0;struct monst*m=0;struct permonst*p=0;switch(which){case 0:o=getobj("read",teleport_read_callback_read_ok,GETOBJ_PROMPT);break;case 1:m=makemon(&mons[PM_HUMAN],10,10,MM_NOGRP);return m?m->mhp:-777;case 2:p=mkclass(S_ORC,0);return p?p->pmidx:-777;case 3:o=mkobj(WEAPON_CLASS,FALSE);break;case 4:o=mksobj(DAGGER,TRUE,FALSE);break;case 5:p=rndmonst();return p?p->pmidx:-777;case 6:o=some_armor(&gy.youmonst);break;case 7:o=which_armor(&monster_pool[0],W_ARMH);break;default:abort();}return o?o->otyp:-777;}
int probe_callback_identity(int which){switch(which){case 0:return teleport_read_callback(1)==(void*)teleport_read_callback_can_center_cloud;case 1:return teleport_read_callback(3)==(void*)teleport_read_callback_display_stinking_cloud_positions;case 2:return teleport_read_callback(4)==(void*)teleport_read_callback_read_ok;case 3:return teleport_read_callback(5)==(void*)teleport_read_callback_set_lit;default:abort();}}
void*probe_projected_pointer(int which){switch(which){case 0:return opts[0]?0:&object_pool[0];case 1:return opts[2]?0:&monster_pool[1];case 2:case 5:return opts[7]?0:&mons[PM_HUMAN];case 3:case 4:return &object_pool[(object_next-1)%64];case 6:return opts[1]?0:uarm;case 7:return opts[1]?0:uarmh;default:abort();}}
void probe_projection_write(int which,int value){void*p=probe_projected_pointer(which);if(!p)return;if(which==1)((struct monst*)p)->mhp=value;else if(which!=2&&which!=5)((struct obj*)p)->spe=value;}
