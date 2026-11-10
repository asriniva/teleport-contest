/* Private APPLY actual-C/imported-JS differential; foreign world is controlled. */
#define NEED_VARARGS
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <setjmp.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(u) u;
__typeof__(uwep) uwep;
__typeof__(ublindf) ublindf;
__typeof__(uarmg) uarmg;
__typeof__(go) go;
__typeof__(svl) svl;
__typeof__(gu) gu;
__typeof__(gy) gy;
__typeof__(gh) gh;
__typeof__(svc) svc;
__typeof__(gb) gb;
__typeof__(gn) gn;
__typeof__(svd) svd;
__typeof__(defsyms) defsyms;
__typeof__(flags) flags;
__typeof__(svm) svm;
__typeof__(iflags) iflags;
__typeof__(gi) gi;
__typeof__(gm) gm;
__typeof__(gs) gs;
__typeof__(uchain) uchain;
__typeof__(gv) gv;
__typeof__(gj) gj;
__typeof__(disp) disp;
__typeof__(hands_obj) hands_obj;
__typeof__(gt) gt;
__typeof__(gp) gp;
__typeof__(windowprocs) windowprocs;
__typeof__(cg) cg;
__typeof__(nul_glyphinfo) nul_glyphinfo;
__typeof__(gc) gc;
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
const char *c_obj_colors[] = {
    "black",          /* CLR_BLACK */
    "red",            /* CLR_RED */
    "green",          /* CLR_GREEN */
    "brown",          /* CLR_BROWN */
    "blue",           /* CLR_BLUE */
    "magenta",        /* CLR_MAGENTA */
    "cyan",           /* CLR_CYAN */
    "gray",           /* CLR_GRAY */
    "transparent",    /* no_color */
    "orange",         /* CLR_ORANGE */
    "bright green",   /* CLR_BRIGHT_GREEN */
    "yellow",         /* CLR_YELLOW */
    "bright blue",    /* CLR_BRIGHT_BLUE */
    "bright magenta", /* CLR_BRIGHT_MAGENTA */
    "bright cyan",    /* CLR_BRIGHT_CYAN */
    "white",          /* CLR_WHITE */
};
const schar xdir[N_DIRS_Z] = { -1, -1,  0,  1,  1,  1,  0, -1, 0,  0 };
const schar ydir[N_DIRS_Z] = {  0, -1, -1, -1,  0,  1,  1,  1, 0,  0 };
const char ynchars[] = "yn";
static void*record_result;static struct obj object_pool[64];static struct monst monster_pool[16];static struct trap trap_pool[8];static coord coord_pool[8];static anything any_pool;static struct attack attack_pool[2];static stairway stairs_pool[2];static int scalar_pool[8];
static int opts[128],object_next,allocation_count,callback_depth;static unsigned rngstate;static jmp_buf fixture_jump;static void*growth;
static char tracebuf[2097152],snapshotbuf[262144],buf[4096],namesbuf[32][128],inputbuf[BUFSZ];static char origin[128];
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static int id(const void*p){if(!p)return-1;uintptr_t n=(uintptr_t)p;if(n>=(uintptr_t)object_pool&&n<(uintptr_t)(object_pool+64))return 1000+(int)(n-(uintptr_t)object_pool);if(n>=(uintptr_t)monster_pool&&n<(uintptr_t)(monster_pool+16))return 100000+(int)(n-(uintptr_t)monster_pool);if(n>=(uintptr_t)mons&&n<(uintptr_t)(mons+NUMMONS+1))return 1000000+(int)(n-(uintptr_t)mons);return 999;}
static void callback(void);
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*f,int line,const char*fn){snprintf(origin,sizeof origin,"%s:%d:%s",f,line,fn);}
int(rn2)(int n){if(n<=0){logmsg("BADRNG:%d;",n);longjmp(fixture_jump,1);}rngstate=rngstate*1664525u+1013904223u;int result=(rngstate>>8)%n;logmsg("rng:%d:%d@%s;",n,result,origin);if(opts[98]&&n==10){u.uprops[HALF_PHDAM].intrinsic=!u.uprops[HALF_PHDAM].intrinsic;logmsg("half-toggle:%ld;",u.uprops[HALF_PHDAM].intrinsic);}return result;}
int(rnd)(int n){return(rn2)(n)+1;}int(d)(int n,int x){int result=0;for(int i=0;i<n;i++)result+=(rn2)(x)+1;return result;}
int(rnl)(int n){return(rn2)(n);}
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
struct obj*getobj(const char*verb,int(*fn)(struct obj*),unsigned flags_){struct obj*o=opts[0]?0:&object_pool[0];logmsg("getobj:%s:%u:%d;",verb,flags_,fn(o));callback();record_result=o;return o;}
void getlin(const char*prompt,char*out){logmsg("getlin:%s;",prompt);strcpy(out,inputbuf);}
void do_clear_area(coordxy x,coordxy y,int radius,void(*fn)(coordxy,coordxy,void*),genericptr_t value){logmsg("area:%d:%d:%d;",x,y,radius);for(int dx=-1;dx<=1;dx++)for(int dy=-1;dy<=1;dy++)if(isok(x+dx,y+dy))fn(x+dx,y+dy,value);callback();}
void getpos_sethilite(void(*display)(boolean),boolean(*valid)(coordxy,coordxy)){logmsg("hilite:%d;",valid(u.ux,u.uy));if(opts[10]){display(TRUE);display(FALSE);}}
int getpos(coord*c,boolean force,const char*goal){logmsg("getpos:%d:%s;",force,goal);c->x=u.ux;c->y=u.uy;return opts[11]?-1:0;}
struct obj*mksobj(int typ,boolean init,boolean arti){logmsg("mksobj:%d:%d:%d;",typ,init,arti);struct obj*o=&object_pool[(object_next++)%64];memset(o,0,sizeof*o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;record_result=o;return o;}
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
/* Controlled external seams: source APPLY policy remains exclusively in the included original C or imported JavaScript. */
static int window_create(int type){logmsg("window:%d;",type);return 1;}
static void window_start(int win,unsigned long behavior){logmsg("start:%d:%lu;",win,behavior);}
static void window_end(int win,const char*text){logmsg("end:%d:%s;",win,text);}
static void window_destroy(int win){logmsg("destroy:%d;",win);}
struct monst*bhit(int x,int y,int range,enum bhit_call_types kind,int(*hitmon)(struct monst*,struct obj*),int(*hitobj)(struct obj*,struct obj*),struct obj**o){logmsg("bhit:%d:%d:%d:%d;",x,y,range,kind);if(opts[97])*o=&object_pool[2];record_result=opts[2]?0:&monster_pool[1];return record_result;}
boolean walk_path(coord*start,coord*target,boolean(*fn)(genericptr_t,coordxy,coordxy),genericptr_t data){logmsg("walk:%d:%d:%d:%d;",start->x,start->y,target->x,target->y);if(opts[12]){boolean result=fn(data,target->x,target->y);logmsg("walk_cb:%d;",result);return result;}return opts[3];}
void set_occupation(int(*fn)(void),const char*text,cmdcount_nht turns){logmsg("occupation:%s:%ld;",text,turns);go.occupation=fn;}
int get_adjacent_loc(const char*question,const char*msg,coordxy x,coordxy y,coord*out){logmsg("adjacent:%d:%d;",x,y);out->x=x+1;out->y=y;return opts[3];}
boolean get_obj_location(struct obj*o,coordxy*x,coordxy*y,int flags_){logmsg("loc:%d:%d;",id(o),flags_);*x=o->ox;*y=o->oy;return opts[3];}
int select_menu(winid win,int how,menu_item**out){logmsg("menu:%d:%d;",win,how);*out=0;if(!opts[3])return 0;*out=malloc(sizeof **out);if(!*out)longjmp(fixture_jump,1);(*out)->item.a_int=opts[13];(*out)->count=1;return 1;}
schar acurr(int attribute){logmsg("acurr:%d;",attribute);return opts[20]?opts[20]:18;}
boolean check_capacity(const char*message){logmsg("capacity;");return opts[21];}
int freehand(void){logmsg("freehand;");return !opts[22];}
int getdir(const char*question){logmsg("getdir;");return !opts[23];}
int retouch_object(struct obj**object,boolean drop){logmsg("retouch:%d:%d;",id(*object),drop);if(opts[96])*object=&object_pool[2];return !opts[24];}
boolean paranoid_query(boolean paranoid,const char*question){logmsg("confirm:%d:%s;",paranoid,question);return !opts[25];}
int zappable(struct obj*o){logmsg("charge:%d;",o->spe);if(opts[26]||o->spe<=0)return 0;--o->spe;return 1;}
int isqrt(int n){int x=0;while((x+1)*(x+1)<=n)x++;return x;}
int glyph_at(coordxy x,coordxy y){return levl[x][y].glyph;}
anything*obj_to_any(struct obj*o){any_pool.a_obj=o;record_result=&any_pool;return &any_pool;}
struct obj*init_dummyobj(struct obj*o,short typ,long quantity){memset(o,0,sizeof*o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=quantity;logmsg("dummy:%d:%ld;",typ,quantity);record_result=o;return o;}

void losehp(int n,const char*cause,schar how){logmsg("damage:%d:%s:%d;",n,cause,how);}
char * Amonnam(struct monst * a0){logmsg("Amonnam;");return namecopy("fixture");}
void Blindf_off(struct obj * a0){logmsg("Blindf_off;");}
void Blindf_on(struct obj * a0){logmsg("Blindf_on;");}
boolean Can_dig_down(d_level * a0){logmsg("Can_dig_down;");return opts[3];}
boolean In_hell(d_level * a0){logmsg("In_hell;");return opts[3];}
boolean In_mines(d_level * a0){logmsg("In_mines;");return opts[3];}
int Mgender(struct monst * a0){logmsg("Mgender;");return opts[3];}
char * Monnam(struct monst * a0){logmsg("Monnam;");return namecopy("fixture");}
boolean On_stairs(coordxy a0,coordxy a1){logmsg("On_stairs;");return opts[3];}
char * Shk_Your(char * a0,struct obj * a1){logmsg("Shk_Your;");return namecopy("fixture");}
char * The(const char * a0){logmsg("The;");return namecopy("fixture");}
void There(const char * a0,...){logmsg("There;");}
char * Tobjnam(struct obj * a0,const char * a1){logmsg("Tobjnam;");return namecopy("fixture");}
char * YMonnam(struct monst * a0){logmsg("YMonnam;");return namecopy("fixture");}
char * Yname2(struct obj * a0){logmsg("Yname2;");return namecopy("fixture");}
char * Yobjnam2(struct obj * a0,const char * a1){logmsg("Yobjnam2;");return namecopy("fixture");}
void You_see(const char * a0,...){logmsg("You_see;");}
char * a_monnam(struct monst * a0){logmsg("a_monnam;");return namecopy("fixture");}
boolean accessible(coordxy a0,coordxy a1){logmsg("accessible;");return opts[3];}
struct monst * activate_statue_trap(struct trap * a0,coordxy a1,coordxy a2,boolean a3){logmsg("activate_statue_trap;");return (record_result=(opts[2]?0:&monster_pool[1]));}
void add_damage(coordxy a0,coordxy a1,long a2){logmsg("add_damage;");}
void add_menu(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){logmsg("add_menu;");}
struct obj * addinv(struct obj * a0){logmsg("addinv;");return (record_result=(opts[1]?0:&object_pool[1]));}
struct obj * addinv_nomerge(struct obj * a0){logmsg("addinv_nomerge;");return (record_result=(opts[1]?0:&object_pool[1]));}
int any_obj_ok(struct obj * a0){logmsg("any_obj_ok;");return opts[3];}
int arti_speak(struct obj * a0){logmsg("arti_speak;");return opts[3];}
void attach_egg_hatch_timeout(struct obj * a0,long a1){logmsg("attach_egg_hatch_timeout;");}
boolean attack_checks(struct monst * a0,struct obj * a1){logmsg("attack_checks;");return opts[3];}
struct attack * attacktype_fordmg(struct permonst * a0,int a1,int a2){logmsg("attacktype_fordmg;");return (record_result=(opts[5]?0:&attack_pool[0]));}
int bagotricks(struct obj * a0,boolean a1,int * a2){logmsg("bagotricks;");return opts[3];}
void begin_burn(struct obj * a0,boolean a1){logmsg("begin_burn;");}
int bhitm(struct monst * a0,struct obj * a1){logmsg("bhitm;");return opts[3];}
int bhito(struct obj * a0,struct obj * a1){logmsg("bhito;");return opts[3];}
int bhitpile(struct obj * a0,int (*a1)(struct obj *, struct obj *),coordxy a2,coordxy a3,schar a4){logmsg("bhitpile;");return opts[3];}
int big_to_little(int a0){logmsg("big_to_little;");return opts[3];}
void bill_dummy_object(struct obj * a0){logmsg("bill_dummy_object;");}
const char * body_part(int a0){logmsg("body_part;");return namecopy("fixture");}
void bot(void){logmsg("bot;");}
boolean boulder_hits_pool(struct obj * a0,coordxy a1,coordxy a2,boolean a3){logmsg("boulder_hits_pool;");return opts[3];}
void buried_ball_to_freedom(void){logmsg("buried_ball_to_freedom;");}
boolean can_blnd(struct monst * a0,struct monst * a1,uchar a2,struct obj * a3){logmsg("can_blnd;");return opts[3];}
boolean can_blow(struct monst * a0){logmsg("can_blow;");return opts[3];}
boolean can_reach_floor(boolean a0){logmsg("can_reach_floor;");return opts[3];}
int canseemon(struct monst * a0){logmsg("canseemon;");return opts[3];}
void cant_reach_floor(coordxy a0,coordxy a1,boolean a2,boolean a3,boolean a4){logmsg("cant_reach_floor;");}
struct obj * carrying(int a0){logmsg("carrying;");return (record_result=(opts[1]?0:&object_pool[1]));}
const char * ceiling(coordxy a0,coordxy a1){logmsg("ceiling;");return namecopy("fixture");}
void change_luck(schar a0){logmsg("change_luck;");}
void check_caitiff(struct monst * a0){logmsg("check_caitiff;");}
void check_unpaid(struct obj * a0){logmsg("check_unpaid;");}
void check_unpaid_usage(struct obj * a0,boolean a1){logmsg("check_unpaid_usage;");}
boolean closed_door(coordxy a0,coordxy a1){logmsg("closed_door;");return opts[3];}
void cmdq_add_ec(int a0,int (*a1)(void)){logmsg("cmdq_add_ec;");}
void cmdq_add_key(int a0,char a1){logmsg("cmdq_add_key;");}
void confdir(boolean a0){logmsg("confdir;");}
void consume_obj_charge(struct obj * a0,boolean a1){logmsg("consume_obj_charge;");}
void copynchars(char * a0,const char * a1,int a2){logmsg("copynchars;");}
void costly_alteration(struct obj * a0,int a1){logmsg("costly_alteration;");}
boolean costly_spot(coordxy a0,coordxy a1){logmsg("costly_spot;");return opts[3];}
int cursed(struct obj * a0){logmsg("cursed;");return opts[3];}
void cvt_sdoor_to_door(struct rm * a0){logmsg("cvt_sdoor_to_door;");}
char * cxname(struct obj * a0){logmsg("cxname;");return namecopy("fixture");}
int dbon(void){logmsg("dbon;");return opts[3];}
void delobj(struct obj * a0){logmsg("delobj;");}
void deltrap(struct trap * a0){logmsg("deltrap;");}
enum digcheck_result dig_check(struct monst * a0,coordxy a1,coordxy a2){logmsg("dig_check;");return opts[3];}
void digactualhole(coordxy a0,coordxy a1,struct monst * a2,int a3){logmsg("digactualhole;");}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object;");}
void djinni_from_bottle(struct obj * a0){logmsg("djinni_from_bottle;");}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){logmsg("dmgtype_fromattack;");return (record_result=(opts[5]?0:&attack_pool[0]));}
int do_play_instrument(struct obj * a0){logmsg("do_play_instrument;");return opts[3];}
void dotrap(struct trap * a0,unsigned int a1){logmsg("dotrap;");}
int dowrite(struct obj * a0){logmsg("dowrite;");return opts[3];}
void dropx(struct obj * a0){logmsg("dropx;");}
void dry_a_towel(struct obj * a0,int a1,boolean a2){logmsg("dry_a_towel;");}
void end_burn(struct obj * a0,boolean a1){logmsg("end_burn;");}
boolean enexto(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){logmsg("enexto;");return opts[3];}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logmsg("explode;");}
void feel_newsym(coordxy a0,coordxy a1){logmsg("feel_newsym;");}
void feeltrap(struct trap * a0){logmsg("feeltrap;");}
void fill_pit(coordxy a0,coordxy a1){logmsg("fill_pit;");}
schar fillholetyp(coordxy a0,coordxy a1,boolean a2){logmsg("fillholetyp;");return opts[3];}
struct monst * find_mid(unsigned int a0,unsigned int a1){logmsg("find_mid;");return (record_result=(opts[2]?0:&monster_pool[1]));}
int findit(void){logmsg("findit;");return opts[3];}
const char * fingers_or_gloves(boolean a0){logmsg("fingers_or_gloves;");return namecopy("fixture");}
boolean fire_damage(struct obj * a0,boolean a1,coordxy a2,coordxy a3){logmsg("fire_damage;");return opts[3];}
int flash_hits_mon(struct monst * a0,struct obj * a1){logmsg("flash_hits_mon;");return opts[3];}
struct obj * floorfood(const char * a0,int a1){logmsg("floorfood;");return (record_result=(opts[1]?0:&object_pool[1]));}
boolean force_attack(struct monst * a0,boolean a1){logmsg("force_attack;");return opts[3];}
void freeinv(struct obj * a0){logmsg("freeinv;");}
struct monst * get_iter_mons(boolean (*a0)(struct monst *)){logmsg("get_iter_mons;");return (record_result=(opts[2]?0:&monster_pool[1]));}
struct monst * get_mtraits(struct obj * a0,boolean a1){logmsg("get_mtraits;");return (record_result=(opts[2]?0:&monster_pool[1]));}
const char * gloves_simple_name(struct obj * a0){logmsg("gloves_simple_name;");return namecopy("fixture");}
int glyph_to_cmap(int a0){logmsg("glyph_to_cmap;");return opts[3];}
void growl(struct monst * a0){logmsg("growl;");}
boolean gulp_blnd_check(void){logmsg("gulp_blnd_check;");return opts[3];}
const char * hcolor(const char * a0){logmsg("hcolor;");return namecopy("fixture");}
char highc(char a0){logmsg("highc;");return opts[3];}
const char * hliquid(const char * a0){logmsg("hliquid;");return namecopy("fixture");}
struct obj * hold_another_object(struct obj * a0,const char * a1,const char * a2,const char * a3){logmsg("hold_another_object;");return (record_result=(opts[1]?0:&object_pool[1]));}
int hornoplenty(struct obj * a0,boolean a1,struct obj * a2){logmsg("hornoplenty;");return opts[3];}
unsigned int howmonseen(struct monst * a0){logmsg("howmonseen;");return opts[3];}
void hurtle(int a0,int a1,int a2,boolean a3){logmsg("hurtle;");}
boolean hurtle_jump(genericptr_t a0,coordxy a1,coordxy a2){logmsg("hurtle_jump;");return opts[3];}
char * in_rooms(coordxy a0,coordxy a1,int a2){logmsg("in_rooms;");return namecopy("fixture");}
boolean inaccessible_equipment(struct obj * a0,const char * a1,boolean a2){logmsg("inaccessible_equipment;");return opts[3];}
void incr_itimeout(long * a0,int a1){logmsg("incr_itimeout;");}
void instapetrify(const char * a0){logmsg("instapetrify;");}
boolean invocation_pos(coordxy a0,coordxy a1){logmsg("invocation_pos;");return opts[3];}
boolean is_lava(coordxy a0,coordxy a1){logmsg("is_lava;");return opts[3];}
boolean is_pool(coordxy a0,coordxy a1){logmsg("is_pool;");return opts[3];}
boolean is_pool_or_lava(coordxy a0,coordxy a1){logmsg("is_pool_or_lava;");return opts[3];}
void kick_steed(void){logmsg("kick_steed;");}
void kill_egg(struct obj * a0){logmsg("kill_egg;");}
void killed(struct monst * a0){logmsg("killed;");}
int known_spell(short a0){logmsg("known_spell;");return opts[3];}
char * l_monnam(struct monst * a0){logmsg("l_monnam;");return namecopy("fixture");}
void legs_in_no_shape(const char * a0,boolean a1){logmsg("legs_in_no_shape;");}
void liquid_flow(coordxy a0,coordxy a1,schar a2,struct trap * a3,const char * a4){logmsg("liquid_flow;");}
void litroom(boolean a0,struct obj * a1){logmsg("litroom;");}
int little_to_big(int a0){logmsg("little_to_big;");return opts[3];}
const char * locomotion(const struct permonst * a0,const char * a1){logmsg("locomotion;");return namecopy("fixture");}
char * m_monnam(struct monst * a0){logmsg("m_monnam;");return namecopy("fixture");}
void make_blinded(long a0,boolean a1){logmsg("make_blinded;");}
void make_deaf(long a0,boolean a1){logmsg("make_deaf;");}
struct monst * make_familiar(struct obj * a0,coordxy a1,coordxy a2,boolean a3){logmsg("make_familiar;");return (record_result=(opts[2]?0:&monster_pool[1]));}
void make_glib(int a0){logmsg("make_glib;");}
boolean make_hallucinated(long a0,boolean a1,long a2){logmsg("make_hallucinated;");return opts[3];}
void make_sick(long a0,const char * a1,boolean a2,int a3){logmsg("make_sick;");}
void make_vomiting(long a0,boolean a1){logmsg("make_vomiting;");}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logmsg("makemon;");return (record_result=(opts[2]?0:&monster_pool[1]));}
struct trap * maketrap(coordxy a0,coordxy a1,int a2){logmsg("maketrap;");return (record_result=(opts[4]?0:&trap_pool[0]));}
void map_invisible(coordxy a0,coordxy a1){logmsg("map_invisible;");}
void map_object(struct obj * a0,int a1){logmsg("map_object;");}
boolean may_passwall(coordxy a0,coordxy a1){logmsg("may_passwall;");return opts[3];}
const char * mbodypart(struct monst * a0,int a1){logmsg("mbodypart;");return namecopy("fixture");}
int mintrap(struct monst * a0,unsigned int a1){logmsg("mintrap;");return opts[3];}
struct permonst * mkclass(char a0,int a1){logmsg("mkclass;");return (record_result=(opts[7]?0:&mons[PM_HUMAN]));}
void mkundead(coord * a0,boolean a1,int a2){logmsg("mkundead;");}
void mnexto(struct monst * a0,unsigned int a1){logmsg("mnexto;");}
void mon_adjust_speed(struct monst * a0,int a1,struct obj * a2){logmsg("mon_adjust_speed;");}
int mon_has_amulet(struct monst * a0){logmsg("mon_has_amulet;");return opts[3];}
char * mon_nam(struct monst * a0){logmsg("mon_nam;");return namecopy("fixture");}
boolean mon_reflects(struct monst * a0,const char * a1){logmsg("mon_reflects;");return opts[3];}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){logmsg("monflee;");}
char * monverbself(struct monst * a0,char * a1,const char * a2,const char * a3){logmsg("monverbself;");return namecopy("fixture");}
void morehungry(int a0){logmsg("morehungry;");}
int mpickobj(struct monst * a0,struct obj * a1){logmsg("mpickobj;");return opts[3];}
void mstatusline(struct monst * a0){logmsg("mstatusline;");}
boolean mwelded(struct obj * a0){logmsg("mwelded;");return opts[3];}
int near_capacity(void){logmsg("near_capacity;");return opts[3];}
void newsym(coordxy a0,coordxy a1){logmsg("newsym;");}
char * noit_mon_nam(struct monst * a0){logmsg("noit_mon_nam;");return namecopy("fixture");}
void nomul(int a0){logmsg("nomul;");}
boolean noteleport_level(struct monst * a0){logmsg("noteleport_level;");return opts[3];}
struct obj * nxtobj(struct obj * a0,int a1,boolean a2){logmsg("nxtobj;");return (record_result=(opts[1]?0:&object_pool[1]));}
void obfree(struct obj * a0,struct obj * a1){logmsg("obfree;");}
void obj_extract_self(struct obj * a0){logmsg("obj_extract_self;");}
boolean obj_has_timer(struct obj * a0,short a1){logmsg("obj_has_timer;");return opts[3];}
void obj_merge_light_sources(struct obj * a0,struct obj * a1){logmsg("obj_merge_light_sources;");}
void obj_no_longer_held(struct obj * a0){logmsg("obj_no_longer_held;");}
const char * obj_pmname(struct obj * a0){logmsg("obj_pmname;");return namecopy("fixture");}
boolean obj_resists(struct obj * a0,int a1,int a2){logmsg("obj_resists;");return opts[3];}
boolean objdescr_is(struct obj * a0,const char * a1){logmsg("objdescr_is;");return opts[3];}
void observe_object(struct obj * a0){logmsg("observe_object;");}
int openit(void){logmsg("openit;");return opts[3];}
char * otense(struct obj * a0,const char * a1){logmsg("otense;");return namecopy("fixture");}
boolean overexertion(void){logmsg("overexertion;");return opts[3];}
void paralyze_monst(struct monst * a0,int a1){logmsg("paralyze_monst;");}
void pay_for_damage(const char * a0,boolean a1){logmsg("pay_for_damage;");}
int pick_lock(struct obj * a0,coordxy a1,coordxy a2,struct obj * a3){logmsg("pick_lock;");return opts[3];}
int pickup_object(struct obj * a0,long a1,boolean a2){logmsg("pickup_object;");return opts[3];}
void place_object(struct obj * a0,coordxy a1,coordxy a2){logmsg("place_object;");}
void pline_mon(struct monst * a0,const char * a1,...){logmsg("pline_mon;");}
int poly_gender(void){logmsg("poly_gender;");return opts[3];}
boolean poly_when_stoned(struct permonst * a0){logmsg("poly_when_stoned;");return opts[3];}
int polymon(int a0){logmsg("polymon;");return opts[3];}
void possibly_unwield(struct monst * a0,boolean a1){logmsg("possibly_unwield;");}
void prinv(const char * a0,struct obj * a1,long a2){logmsg("prinv;");}
int pronoun_gender(struct monst * a0,unsigned int a1){logmsg("pronoun_gender;");return opts[3];}
void recalc_block_point(coordxy a0,coordxy a1){logmsg("recalc_block_point;");}
void release_hold(void){logmsg("release_hold;");}
void reset_utrap(boolean a0){logmsg("reset_utrap;");}
boolean revive_corpse(struct obj * a0){logmsg("revive_corpse;");return opts[3];}
boolean rloc(struct monst * a0,unsigned int a1){logmsg("rloc;");return opts[3];}
void rloc_to(struct monst * a0,coordxy a1,coordxy a2){logmsg("rloc_to;");}
char * s_suffix(const char * a0){logmsg("s_suffix;");return namecopy("fixture");}
char * safe_qbuf(char * a0,const char * a1,const char * a2,struct obj * a3,char *(*a4)(struct obj *),char *(*a5)(struct obj *),const char * a6){logmsg("safe_qbuf;");return namecopy("fixture");}
void see_monster_closeup(struct monst * a0,boolean a1){logmsg("see_monster_closeup;");}
void seemimic(struct monst * a0){logmsg("seemimic;");}
int sensemon(struct monst * a0){logmsg("sensemon;");return opts[3];}
void set_bknown(struct obj * a0,unsigned int a1){logmsg("set_bknown;");}
void set_itimeout(long * a0,long a1){logmsg("set_itimeout;");}
void set_msg_xy(coordxy a0,coordxy a1){logmsg("set_msg_xy;");}
void set_tin_variety(struct obj * a0,int a1){logmsg("set_tin_variety;");}
void set_ustuck(struct monst * a0){logmsg("set_ustuck;");}
void set_wounded_legs(long a0,int a1){logmsg("set_wounded_legs;");}
void setmnotwielded(struct monst * a0,struct obj * a1){logmsg("setmnotwielded;");}
void setnotworn(struct obj * a0){logmsg("setnotworn;");}
char * shk_your(char * a0,struct obj * a1){logmsg("shk_your;");return namecopy("fixture");}
struct monst * shop_keeper(char a0){logmsg("shop_keeper;");return (record_result=(opts[2]?0:&monster_pool[1]));}
void shuffle_int_array(int * a0,int a1){logmsg("shuffle_int_array;");}
char * simple_typename(int a0){logmsg("simple_typename;");return namecopy("fixture");}
char * simpleonames(struct obj * a0){logmsg("simpleonames;");return namecopy("fixture");}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){logmsg("sobj_at;");return (record_result=(opts[1]?0:&object_pool[1]));}
int spelleffects(int a0,boolean a1,boolean a2){logmsg("spelleffects;");return opts[3];}
struct obj * splitobj(struct obj * a0,long a1){logmsg("splitobj;");return (record_result=(opts[1]?0:&object_pool[1]));}
void spot_stop_timers(coordxy a0,coordxy a1,short a2){logmsg("spot_stop_timers;");}
void spoteffects(boolean a0){logmsg("spoteffects;");}
void stackobj(struct obj * a0){logmsg("stackobj;");}
stairway * stairway_at(coordxy a0,coordxy a1){logmsg("stairway_at;");return (record_result=(opts[6]?0:&stairs_pool[0]));}
boolean start_timer(long a0,short a1,short a2,union any * a3){logmsg("start_timer;");return opts[3];}
long stop_timer(short a0,union any * a1){logmsg("stop_timer;");return opts[3];}
boolean stucksteed(boolean a0){logmsg("stucksteed;");return opts[3];}
void stumble_onto_mimic(struct monst * a0){logmsg("stumble_onto_mimic;");}
const char * surface(coordxy a0,coordxy a1){logmsg("surface;");return namecopy("fixture");}
struct trap * t_at(coordxy a0,coordxy a1){logmsg("t_at;");return (record_result=(opts[4]?0:&trap_pool[0]));}
boolean tele_restrict(struct monst * a0){logmsg("tele_restrict;");return opts[3];}
void tele_to_rnd_pet(void){logmsg("tele_to_rnd_pet;");}
void teleds(coordxy a0,coordxy a1,int a2){logmsg("teleds;");}
char * the(const char * a0){logmsg("the;");return namecopy("fixture");}
char * thesimpleoname(struct obj * a0){logmsg("thesimpleoname;");return namecopy("fixture");}
int thitmonst(struct monst * a0,struct obj * a1){logmsg("thitmonst;");return opts[3];}
void tmp_at(coordxy a0,coordxy a1){logmsg("tmp_at;");}
void transient_light_cleanup(void){logmsg("transient_light_cleanup;");}
const char * trapname(int a0,boolean a1){logmsg("trapname;");return namecopy("fixture");}
void u_wipe_engr(int a0){logmsg("u_wipe_engr;");}
void unbless(struct obj * a0){logmsg("unbless;");}
void unblock_point(int a0,int a1){logmsg("unblock_point;");}
boolean unmap_invisible(coordxy a0,coordxy a1){logmsg("unmap_invisible;");return opts[3];}
void unpunish(void){logmsg("unpunish;");}
struct obj * unsplitobj(struct obj * a0){logmsg("unsplitobj;");return (record_result=(opts[1]?0:&object_pool[1]));}
void update_inventory(void){logmsg("update_inventory;");}
char * upstart(char * a0){logmsg("upstart;");return namecopy("fixture");}
int use_container(struct obj ** a0,boolean a1,boolean a2){logmsg("use_container;");return opts[3];}
void use_crystal_ball(struct obj ** a0){logmsg("use_crystal_ball;");}
int use_pick_axe(struct obj * a0){logmsg("use_pick_axe;");return opts[3];}
int use_saddle(struct obj * a0){logmsg("use_saddle;");return opts[3];}
int use_tin_opener(struct obj * a0){logmsg("use_tin_opener;");return opts[3];}
void use_unpaid_trapobj(struct obj * a0,coordxy a1,coordxy a2){logmsg("use_unpaid_trapobj;");}
void useupall(struct obj * a0){logmsg("useupall;");}
void useupf(struct obj * a0,long a1){logmsg("useupf;");}
void ustatusline(void){logmsg("ustatusline;");}
int uwep_skill_type(void){logmsg("uwep_skill_type;");return opts[3];}
void vault_summon_gd(void){logmsg("vault_summon_gd;");}
void vomit(void){logmsg("vomit;");}
char * vtense(const char * a0,const char * a1){logmsg("vtense;");return namecopy("fixture");}
void wake_nearby(boolean a0){logmsg("wake_nearby;");}
void wake_nearto(coordxy a0,coordxy a1,int a2){logmsg("wake_nearto;");}
void wakeup(struct monst * a0,boolean a1){logmsg("wakeup;");}
void watch_dig(struct monst * a0,coordxy a1,coordxy a2,boolean a3){logmsg("watch_dig;");}
int weight(struct obj * a0){logmsg("weight;");return opts[3];}
void whimper(struct monst * a0){logmsg("whimper;");}
boolean wield_tool(struct obj * a0,const char * a1){logmsg("wield_tool;");return opts[3];}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){logmsg("x_monnam;");return namecopy("fixture");}
void xkilled(struct monst * a0,int a1){logmsg("xkilled;");}
char * y_monnam(struct monst * a0){logmsg("y_monnam;");return namecopy("fixture");}
void yelp(struct monst * a0){logmsg("yelp;");}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){logmsg("yn_function;");return opts[3];}
char * yname(struct obj * a0){logmsg("yname;");return namecopy("fixture");}
char * ysimple_name(struct obj * a0){logmsg("ysimple_name;");return namecopy("fixture");}
void zapsetup(void){logmsg("zapsetup;");}
void zapwrapup(void){logmsg("zapwrapup;");}
int zapyourself(struct obj * a0,boolean a1){logmsg("zapyourself;");return opts[3];}
#ifdef TELEPORT_REFERENCE_TU
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/apply.c"
#else
extern int teleport_apply_test_use_camera(struct obj *);
#define use_camera teleport_apply_test_use_camera
extern int teleport_apply_test_use_towel(struct obj *);
#define use_towel teleport_apply_test_use_towel
extern boolean teleport_apply_test_its_dead(coordxy,coordxy,int *);
#define its_dead teleport_apply_test_its_dead
extern int teleport_apply_test_use_stethoscope(struct obj *);
#define use_stethoscope teleport_apply_test_use_stethoscope
extern void teleport_apply_test_use_whistle(struct obj *);
#define use_whistle teleport_apply_test_use_whistle
extern void teleport_apply_test_use_magic_whistle(struct obj *);
#define use_magic_whistle teleport_apply_test_use_magic_whistle
extern void teleport_apply_test_magic_whistled(struct obj *);
#define magic_whistled teleport_apply_test_magic_whistled
extern int teleport_apply_test_use_leash(struct obj *);
#define use_leash teleport_apply_test_use_leash
extern void teleport_apply_test_use_leash_core(struct obj *,struct monst *,coord *,int);
#define use_leash_core teleport_apply_test_use_leash_core
extern boolean teleport_apply_test_mleashed_next2u(struct monst *);
#define mleashed_next2u teleport_apply_test_mleashed_next2u
extern int teleport_apply_test_use_mirror(struct obj *);
#define use_mirror teleport_apply_test_use_mirror
extern void teleport_apply_test_use_bell(struct obj **);
#define use_bell teleport_apply_test_use_bell
extern void teleport_apply_test_use_candelabrum(struct obj *);
#define use_candelabrum teleport_apply_test_use_candelabrum
extern void teleport_apply_test_use_candle(struct obj **);
#define use_candle teleport_apply_test_use_candle
extern void teleport_apply_test_use_lamp(struct obj *);
#define use_lamp teleport_apply_test_use_lamp
extern void teleport_apply_test_light_cocktail(struct obj **);
#define light_cocktail teleport_apply_test_light_cocktail
extern int teleport_apply_test_rub_ok(struct obj *);
#define rub_ok teleport_apply_test_rub_ok
extern boolean teleport_apply_test_check_jump(void *,coordxy,coordxy);
#define check_jump teleport_apply_test_check_jump
extern boolean teleport_apply_test_is_valid_jump_pos(coordxy,coordxy,int,boolean);
#define is_valid_jump_pos teleport_apply_test_is_valid_jump_pos
extern boolean teleport_apply_test_get_valid_jump_position(coordxy,coordxy);
#define get_valid_jump_position teleport_apply_test_get_valid_jump_position
extern void teleport_apply_test_display_jump_positions(boolean);
#define display_jump_positions teleport_apply_test_display_jump_positions
extern void teleport_apply_test_use_tinning_kit(struct obj *);
#define use_tinning_kit teleport_apply_test_use_tinning_kit
extern boolean teleport_apply_test_figurine_location_checks(struct obj *,coord *,boolean);
#define figurine_location_checks teleport_apply_test_figurine_location_checks
extern int teleport_apply_test_use_figurine(struct obj **);
#define use_figurine teleport_apply_test_use_figurine
extern int teleport_apply_test_grease_ok(struct obj *);
#define grease_ok teleport_apply_test_grease_ok
extern int teleport_apply_test_use_grease(struct obj *);
#define use_grease teleport_apply_test_use_grease
extern int teleport_apply_test_touchstone_ok(struct obj *);
#define touchstone_ok teleport_apply_test_touchstone_ok
extern int teleport_apply_test_use_stone(struct obj *);
#define use_stone teleport_apply_test_use_stone
extern void teleport_apply_test_use_trap(struct obj *);
#define use_trap teleport_apply_test_use_trap
extern int teleport_apply_test_set_trap(void);
#define set_trap teleport_apply_test_set_trap
extern boolean teleport_apply_test_find_poleable_mon(coord *);
#define find_poleable_mon teleport_apply_test_find_poleable_mon
extern boolean teleport_apply_test_get_valid_polearm_position(coordxy,coordxy);
#define get_valid_polearm_position teleport_apply_test_get_valid_polearm_position
extern void teleport_apply_test_display_polearm_positions(boolean);
#define display_polearm_positions teleport_apply_test_display_polearm_positions
extern void teleport_apply_test_calc_pole_range(int *,int *);
#define calc_pole_range teleport_apply_test_calc_pole_range
extern boolean teleport_apply_test_snickersnee_used_dist_attk(struct obj *);
#define snickersnee_used_dist_attk teleport_apply_test_snickersnee_used_dist_attk
extern int teleport_apply_test_use_cream_pie(struct obj *);
#define use_cream_pie teleport_apply_test_use_cream_pie
extern int teleport_apply_test_jelly_ok(struct obj *);
#define jelly_ok teleport_apply_test_jelly_ok
extern int teleport_apply_test_use_royal_jelly(struct obj **);
#define use_royal_jelly teleport_apply_test_use_royal_jelly
extern int teleport_apply_test_grapple_range(void);
#define grapple_range teleport_apply_test_grapple_range
extern boolean teleport_apply_test_can_grapple_location(coordxy,coordxy);
#define can_grapple_location teleport_apply_test_can_grapple_location
extern void teleport_apply_test_display_grapple_positions(boolean);
#define display_grapple_positions teleport_apply_test_display_grapple_positions
extern int teleport_apply_test_use_grapple(struct obj *);
#define use_grapple teleport_apply_test_use_grapple
extern void teleport_apply_test_discard_broken_wand(void);
#define discard_broken_wand teleport_apply_test_discard_broken_wand
extern void teleport_apply_test_broken_wand_explode(struct obj *,int,int);
#define broken_wand_explode teleport_apply_test_broken_wand_explode
extern int teleport_apply_test_do_break_wand(struct obj *);
#define do_break_wand teleport_apply_test_do_break_wand
extern int teleport_apply_test_apply_ok(struct obj *);
#define apply_ok teleport_apply_test_apply_ok
extern int teleport_apply_test_flip_through_book(struct obj *);
#define flip_through_book teleport_apply_test_flip_through_book
extern int teleport_apply_test_flip_coin(struct obj *);
#define flip_coin teleport_apply_test_flip_coin
#endif
#include "../nethack-c/wasm/tu-fragments/apply-support.inc"
#include "tu-apply-layout.h"
void probe_input(const char*s){snprintf(inputbuf,sizeof inputbuf,"%s",s);}
/* Controlled fixture transport only: never exit the real process. */
static void callback(void){if(opts[93])longjmp(fixture_jump,1);if(opts[90]&&!callback_depth){callback_depth++;logmsg("reentry:%d;",um_dist(u.ux,u.uy,2));if(opts[92]&&!growth){growth=malloc(40000000);logmsg("growth:%d;",growth!=0);}if(opts[94]){object_pool[0].spe=3;monster_pool[0].mhp=17;logmsg("alias_write;");}callback_depth--;}}
int probe_layout_count(void){return SIZE(apply_layout);}const char*probe_layout_name(int i){return apply_layout[i].name;}long long probe_layout_value(int i){return apply_layout[i].value;}
const char*probe_trace(void){return tracebuf;}const char*probe_buffer(void){return buf;}size_t probe_stack(void){return emscripten_stack_get_current();}
void probe_clear(void){tracebuf[0]=0;buf[0]=0;}void probe_option(int i,int value){opts[i]=value;}void probe_seed(unsigned value){rngstate=value;}
void probe_reset(void){if(growth){free(growth);growth=0;}monst_globals_init();objects_globals_init();memset(opts,0,sizeof opts);opts[1]=opts[2]=opts[4]=opts[5]=opts[6]=1;memset(object_pool,0,sizeof object_pool);memset(monster_pool,0,sizeof monster_pool);memset(trap_pool,0,sizeof trap_pool);memset(coord_pool,0,sizeof coord_pool);memset(scalar_pool,0,sizeof scalar_pool);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&svl,0,sizeof svl);memset(&svm,0,sizeof svm);object_next=4;allocation_count=0;callback_depth=0;rngstate=1;tracebuf[0]=0;buf[0]=0;origin[0]=0;strcpy(inputbuf,"\033");u.ux=10;u.uy=10;u.ulevel=10;u.uhp=100;u.uhpmax=100;u.uhunger=1000;u.umonnum=u.umonster=PM_HUMAN;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urace.mnum=PM_HUMAN;uwep=&object_pool[0];ublindf=uarmg=uchain=0;svl.level.monlist=0;gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<64;i++){object_pool[i].otyp=DAGGER;object_pool[i].oclass=WEAPON_CLASS;object_pool[i].quan=1;object_pool[i].o_id=i+1;object_pool[i].spe=1;object_pool[i].where=OBJ_INVENT;}for(int i=0;i<16;i++){monster_pool[i].data=&mons[PM_HUMAN];monster_pool[i].mhp=20;monster_pool[i].mhpmax=30;monster_pool[i].m_lev=5;monster_pool[i].mx=10+i;monster_pool[i].my=10;monster_pool[i].m_id=i+1;monster_pool[i].cham=NON_PM;}static seenV rows[ROWNO][COLNO];static seenV*rowptr[ROWNO];for(int y=0;y<ROWNO;y++){rowptr[y]=rows[y];for(int x=0;x<COLNO;x++){rows[y][x]=IN_SIGHT|COULD_SEE;svl.level.locations[x][y].typ=ROOM;}}gv.viz_array=rowptr;coord_pool[0].x=10;coord_pool[0].y=10;gt.trapinfo.tobj=0;go.occupation=0;windowprocs.win_create_nhwindow=window_create;windowprocs.win_start_menu=window_start;windowprocs.win_end_menu=window_end;windowprocs.win_destroy_nhwindow=window_destroy;}
void probe_object(int i,int typ,int spe,int flags_,unsigned oid,long quantity){struct obj*o=&object_pool[i];o->otyp=typ;o->oclass=objects[typ].oc_class;o->spe=spe;o->blessed=flags_&1;o->cursed=(flags_>>1)&1;o->oeroded=(flags_>>2)&3;o->oeroded2=(flags_>>4)&3;o->dknown=(flags_>>6)&1;o->o_id=oid;o->quan=quantity;}
void probe_global(int which,long value){switch(which){case 0:u.uprops[BLINDED].intrinsic=value;break;case 1:flags.verbose=value;break;case 2:flags.debug=value;break;case 3:HConfusion=value;break;case 4:u.uprops[HALLUC].intrinsic=value;break;case 5:u.uprops[HALF_PHDAM].intrinsic=value;break;case 6:u.uinwater=value;break;case 7:u.uswallow=value;u.ustuck=value?&monster_pool[0]:0;break;case 8:u.uprops[GLIB].intrinsic=value;break;case 9:u.ucreamed=value;break;case 10:u.uprops[FUMBLING].intrinsic=value;break;}}
void*probe_pointer(int kind){switch(kind){case 0:return &object_pool[0];case 1:return &monster_pool[0];case 2:return &coord_pool[0];case 3:return &scalar_pool[0];case 4:return &trap_pool[0];default:return 0;}}
const char*probe_snapshot(void){char*p=snapshotbuf;p+=sprintf(p,"rng:%u;alloc:%d;prop:%ld,%ld,%ld,%ld;trap:%d,%d,%d,%d;",rngstate,allocation_count,HConfusion,HStun,HBlinded,Glib,gt.trapinfo.tx,gt.trapinfo.ty,gt.trapinfo.time_needed,gt.trapinfo.force_bungle);for(int i=0;i<64;i++){struct obj*o=&object_pool[i];p+=sprintf(p,"o:%d,%d,%u,%u,%u,%u,%u,%u,%ld,%ld,%ld,%u;",o->otyp,o->spe,o->blessed,o->cursed,o->oeroded,o->oeroded2,o->in_use,o->lamplit,o->quan,o->age,o->owornmask,o->leashmon);}for(int i=0;i<16;i++){struct monst*m=&monster_pool[i];p+=sprintf(p,"m:%d,%d,%d,%d,%d,%d,%d;",m->mhp,m->mhpmax,m->mtame,m->mpeaceful,m->msleeping,m->mundetected,m->mleashed);}p+=sprintf(p,"refs:%d,%d,%d,%d;",coord_pool[0].x,coord_pool[0].y,scalar_pool[0],id(gt.trapinfo.tobj));return snapshotbuf;}
void probe_property(int n,long intrinsic,long extrinsic,long blocked){u.uprops[n].intrinsic=intrinsic;u.uprops[n].extrinsic=extrinsic;u.uprops[n].blocked=blocked;}
void probe_scene(int which,int a,int b){switch(which){case 0:u.dx=a;u.dy=b;u.dz=0;break;case 1:u.dz=a;break;case 2:gi.invent=a?&object_pool[0]:0;object_pool[0].nobj=a>1?&object_pool[1]:0;break;case 3:svl.level.monlist=a?&monster_pool[0]:0;svl.level.monsters[11][10]=a?&monster_pool[0]:0;monster_pool[0].mx=11;monster_pool[0].my=10;monster_pool[0].mtame=b;break;case 4:object_pool[0].leashmon=a;monster_pool[0].mleashed=b;break;case 5:svm.moves=a;svl.level.flags.stasis_until=b;break;case 6:u.utrap=a;u.utraptype=b;break;case 7:gt.trapinfo.tobj=a?&object_pool[0]:0;gt.trapinfo.tx=u.ux;gt.trapinfo.ty=u.uy;gt.trapinfo.time_needed=b;break;case 8:u.uswallow=a;u.ustuck=a?&monster_pool[0]:0;break;case 9:object_pool[0].age=a;object_pool[0].lamplit=b;break;case 10:u.weapon_skills[P_POLEARMS].skill=a;u.weapon_skills[P_LANCE].skill=a;u.weapon_skills[P_WHIP].skill=a;break;case 11:u.usteed=a?&monster_pool[0]:0;break;case 12:monster_pool[0].data=&mons[a];monster_pool[0].cham=b;break;case 13:object_pool[0].corpsenm=a;break;case 15:svl.level.locations[a][b].glyph=GLYPH_MON_MALE_OFF+PM_HUMAN;gp.polearm_range_max=9;gp.polearm_range_min=0;break;case 14:svl.level.locations[a][b].typ=DOOR;svl.level.locations[a][b].doormask=D_ISOPEN;break;}}
long long probe_action(int op,int a,int b,int c){long long result=0;if(setjmp(fixture_jump))return-999;switch(op){
case 0:{struct obj*sobj=&object_pool[0];do_blinding_ray(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 1:{struct obj*sobj=&object_pool[0];result=use_camera(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 2:{struct obj*sobj=&object_pool[0];result=use_towel(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 3:{struct obj*sobj=&object_pool[0];result=its_dead(a,b,&scalar_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 4:{struct obj*sobj=&object_pool[0];result=use_stethoscope(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 5:{struct obj*sobj=&object_pool[0];use_whistle(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 6:{struct obj*sobj=&object_pool[0];use_magic_whistle(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 7:{struct obj*sobj=&object_pool[0];magic_whistled(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 8:{struct obj*sobj=&object_pool[0];result=um_dist(a,b,c);logmsg("out:%d;",id(sobj));break;}
case 9:{struct obj*sobj=&object_pool[0];result=number_leashed();logmsg("out:%d;",id(sobj));break;}
case 10:{struct obj*sobj=&object_pool[0];o_unleash(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
case 11:{struct obj*sobj=&object_pool[0];m_unleash(&monster_pool[0],a);logmsg("out:%d;",id(sobj));break;}
case 12:{struct obj*sobj=&object_pool[0];unleash_all();logmsg("out:%d;",id(sobj));break;}
case 13:{struct obj*sobj=&object_pool[0];result=leashable(&monster_pool[0]);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 14:{struct obj*sobj=&object_pool[0];result=use_leash(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 15:{struct obj*sobj=&object_pool[0];use_leash_core(&object_pool[0],&monster_pool[0],&coord_pool[0],a);logmsg("out:%d;",id(sobj));break;}
#endif
case 16:{struct obj*sobj=&object_pool[0];result=id(get_mleash(&monster_pool[0]));logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 17:{struct obj*sobj=&object_pool[0];result=mleashed_next2u(&monster_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 18:{struct obj*sobj=&object_pool[0];result=next_to_u();logmsg("out:%d;",id(sobj));break;}
case 19:{struct obj*sobj=&object_pool[0];check_leash(a,b);logmsg("out:%d;",id(sobj));break;}
case 20:{struct obj*sobj=&object_pool[0];const char*text=beautiful();if(text)snprintf(buf,sizeof buf,"%s",text);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 21:{struct obj*sobj=&object_pool[0];result=use_mirror(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 22:{struct obj*sobj=&object_pool[0];use_bell(&sobj);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 23:{struct obj*sobj=&object_pool[0];use_candelabrum(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 24:{struct obj*sobj=&object_pool[0];use_candle(&sobj);logmsg("out:%d;",id(sobj));break;}
#endif
case 25:{struct obj*sobj=&object_pool[0];result=snuff_candle(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
case 26:{struct obj*sobj=&object_pool[0];result=snuff_lit(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
case 27:{struct obj*sobj=&object_pool[0];result=splash_lit(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
case 28:{struct obj*sobj=&object_pool[0];result=catch_lit(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 29:{struct obj*sobj=&object_pool[0];use_lamp(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 30:{struct obj*sobj=&object_pool[0];light_cocktail(&sobj);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 31:{struct obj*sobj=&object_pool[0];result=rub_ok(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 32:{struct obj*sobj=&object_pool[0];result=dorub();logmsg("out:%d;",id(sobj));break;}
case 33:{struct obj*sobj=&object_pool[0];result=dojump();logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 34:{struct obj*sobj=&object_pool[0];result=check_jump(&scalar_pool[0],a,b);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 35:{struct obj*sobj=&object_pool[0];result=is_valid_jump_pos(a,b,c,c);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 36:{struct obj*sobj=&object_pool[0];result=get_valid_jump_position(a,b);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 37:{struct obj*sobj=&object_pool[0];display_jump_positions(a);logmsg("out:%d;",id(sobj));break;}
#endif
case 38:{struct obj*sobj=&object_pool[0];result=jump(a);logmsg("out:%d;",id(sobj));break;}
case 39:{struct obj*sobj=&object_pool[0];result=tinnable(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 40:{struct obj*sobj=&object_pool[0];use_tinning_kit(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 41:{struct obj*sobj=&object_pool[0];use_unicorn_horn(&sobj);logmsg("out:%d;",id(sobj));break;}
case 42:{struct obj*sobj=&object_pool[0];fig_transform(&any_pool,a);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 43:{struct obj*sobj=&object_pool[0];result=figurine_location_checks(&object_pool[0],&coord_pool[0],a);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 44:{struct obj*sobj=&object_pool[0];result=use_figurine(&sobj);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 45:{struct obj*sobj=&object_pool[0];result=grease_ok(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 46:{struct obj*sobj=&object_pool[0];result=use_grease(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 47:{struct obj*sobj=&object_pool[0];result=touchstone_ok(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 48:{struct obj*sobj=&object_pool[0];result=use_stone(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 49:{struct obj*sobj=&object_pool[0];reset_trapset();logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 50:{struct obj*sobj=&object_pool[0];use_trap(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 51:{struct obj*sobj=&object_pool[0];result=set_trap();logmsg("out:%d;",id(sobj));break;}
#endif
case 52:{struct obj*sobj=&object_pool[0];result=use_whip(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 53:{struct obj*sobj=&object_pool[0];result=find_poleable_mon(&coord_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 54:{struct obj*sobj=&object_pool[0];result=get_valid_polearm_position(a,b);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 55:{struct obj*sobj=&object_pool[0];display_polearm_positions(a);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 56:{struct obj*sobj=&object_pool[0];calc_pole_range(&scalar_pool[0],&scalar_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 57:{struct obj*sobj=&object_pool[0];result=could_pole_mon();logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 58:{struct obj*sobj=&object_pool[0];result=snickersnee_used_dist_attk(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 59:{struct obj*sobj=&object_pool[0];result=use_pole(&object_pool[0],a);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 60:{struct obj*sobj=&object_pool[0];result=use_cream_pie(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 61:{struct obj*sobj=&object_pool[0];result=jelly_ok(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 62:{struct obj*sobj=&object_pool[0];result=use_royal_jelly(&sobj);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 63:{struct obj*sobj=&object_pool[0];result=grapple_range();logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 64:{struct obj*sobj=&object_pool[0];result=can_grapple_location(a,b);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 65:{struct obj*sobj=&object_pool[0];display_grapple_positions(a);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 66:{struct obj*sobj=&object_pool[0];result=use_grapple(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 67:{struct obj*sobj=&object_pool[0];discard_broken_wand();logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 68:{struct obj*sobj=&object_pool[0];broken_wand_explode(&object_pool[0],a,b);logmsg("out:%d;",id(sobj));break;}
#endif
case 69:{struct obj*sobj=&object_pool[0];maybe_dunk_boulders(a,b);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 70:{struct obj*sobj=&object_pool[0];result=do_break_wand(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 71:{struct obj*sobj=&object_pool[0];result=apply_ok(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
case 72:{struct obj*sobj=&object_pool[0];result=doapply();logmsg("out:%d;",id(sobj));break;}
case 73:{struct obj*sobj=&object_pool[0];result=unfixable_trouble_count(a);logmsg("out:%d;",id(sobj));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 74:{struct obj*sobj=&object_pool[0];result=flip_through_book(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 75:{struct obj*sobj=&object_pool[0];result=flip_coin(&object_pool[0]);logmsg("out:%d;",id(sobj));break;}
#endif
default:abort();}return result;}

/* Native function pointer identity and original typed indirect calls. */
int probe_callback_identity(int which){switch(which){
case 1:return teleport_apply_callback(which)==(void*)teleport_apply_callback_apply_ok;
case 3:return teleport_apply_callback(which)==(void*)teleport_apply_callback_can_grapple_location;
case 4:return teleport_apply_callback(which)==(void*)teleport_apply_callback_check_jump;
case 5:return teleport_apply_callback(which)==(void*)teleport_apply_callback_display_grapple_positions;
case 6:return teleport_apply_callback(which)==(void*)teleport_apply_callback_display_jump_positions;
case 7:return teleport_apply_callback(which)==(void*)teleport_apply_callback_display_polearm_positions;
case 8:return teleport_apply_callback(which)==(void*)doapply;
case 9:return teleport_apply_callback(which)==(void*)dorub;
case 10:return teleport_apply_callback(which)==(void*)teleport_apply_callback_get_valid_jump_position;
case 11:return teleport_apply_callback(which)==(void*)teleport_apply_callback_get_valid_polearm_position;
case 12:return teleport_apply_callback(which)==(void*)teleport_apply_callback_grease_ok;
case 14:return teleport_apply_callback(which)==(void*)teleport_apply_callback_jelly_ok;
case 15:return teleport_apply_callback(which)==(void*)teleport_apply_callback_mleashed_next2u;
case 16:return teleport_apply_callback(which)==(void*)teleport_apply_callback_rub_ok;
case 17:return teleport_apply_callback(which)==(void*)teleport_apply_callback_set_trap;
case 19:return teleport_apply_callback(which)==(void*)teleport_apply_callback_touchstone_ok;
default:abort();}}
long long probe_callback_action(int which){if(setjmp(fixture_jump))return -999;switch(which){
case 1:return ((int(*)(struct obj *))teleport_apply_callback(which))(&object_pool[0]);
case 3:return ((boolean(*)(coordxy,coordxy))teleport_apply_callback(which))(10,10);
case 4:return ((boolean(*)(void *,coordxy,coordxy))teleport_apply_callback(which))(&scalar_pool[0],10,10);
case 5:((void(*)(boolean))teleport_apply_callback(which))(0);return 0;
case 6:((void(*)(boolean))teleport_apply_callback(which))(0);return 0;
case 7:((void(*)(boolean))teleport_apply_callback(which))(0);return 0;
case 8:return ((int(*)(void))teleport_apply_callback(which))();
case 9:return ((int(*)(void))teleport_apply_callback(which))();
case 10:return ((boolean(*)(coordxy,coordxy))teleport_apply_callback(which))(10,10);
case 11:return ((boolean(*)(coordxy,coordxy))teleport_apply_callback(which))(10,10);
case 12:return ((int(*)(struct obj *))teleport_apply_callback(which))(&object_pool[0]);
case 14:return ((int(*)(struct obj *))teleport_apply_callback(which))(&object_pool[0]);
case 15:return ((boolean(*)(struct monst *))teleport_apply_callback(which))(&monster_pool[0]);
case 16:return ((int(*)(struct obj *))teleport_apply_callback(which))(&object_pool[0]);
case 17:return ((int(*)(void))teleport_apply_callback(which))();
case 19:return ((int(*)(struct obj *))teleport_apply_callback(which))(&object_pool[0]);
default:abort();}}

void*probe_record_pointer(void){return record_result;}
long long probe_record(int which){struct obj*cell=&object_pool[0];switch(which){
case 0:{struct monst * value=make_familiar(&object_pool[0],10,10,0);record_result=value;return value?value->mhp:-777;}
case 1:{struct obj * value=floorfood("apply.c",0);record_result=value;return value?value->otyp:-777;}
case 2:{anything * value=obj_to_any(&object_pool[0]);record_result=value;return value?id(value->a_obj):-777;}
case 3:{struct obj * value=addinv(&object_pool[0]);record_result=value;return value?value->otyp:-777;}
case 4:{struct obj * value=addinv_nomerge(&object_pool[0]);record_result=value;return value?value->otyp:-777;}
case 5:{struct obj * value=hold_another_object(&object_pool[0],"apply.c","apply.c","apply.c");record_result=value;return value?value->otyp:-777;}
case 6:{struct obj * value=sobj_at(0,10,10);record_result=value;return value?value->otyp:-777;}
case 7:{struct obj * value=nxtobj(&object_pool[0],0,0);record_result=value;return value?value->otyp:-777;}
case 8:{struct obj * value=carrying(0);record_result=value;return value?value->otyp:-777;}
case 9:{struct obj * value=getobj("apply.c",teleport_apply_callback_apply_ok,0);record_result=value;return value?value->otyp:-777;}
case 10:{struct monst * value=find_mid(0,0);record_result=value;return value?value->mhp:-777;}
case 11:{struct monst * value=makemon(&mons[PM_HUMAN],10,10,0);record_result=value;return value?value->mhp:-777;}
case 12:{struct permonst * value=mkclass(0,0);record_result=value;return value?value->msize:-777;}
case 13:{struct obj * value=splitobj(&object_pool[0],0);record_result=value;return value?value->otyp:-777;}
case 14:{struct obj * value=unsplitobj(&object_pool[0]);record_result=value;return value?value->otyp:-777;}
case 15:{struct obj * value=mksobj(DAGGER,0,0);record_result=value;return value?value->otyp:-777;}
case 16:{struct monst * value=get_mtraits(&object_pool[0],0);record_result=value;return value?value->mhp:-777;}
case 17:{struct obj * value=init_dummyobj(&object_pool[0],0,0);record_result=value;return value?value->otyp:-777;}
case 18:{struct monst * value=get_iter_mons(teleport_apply_callback_mleashed_next2u);record_result=value;return value?value->mhp:-777;}
case 19:{struct attack * value=attacktype_fordmg(&mons[PM_HUMAN],0,0);record_result=value;return value?value->damd:-777;}
case 20:{struct attack * value=dmgtype_fromattack(&mons[PM_HUMAN],0,0);record_result=value;return value?value->damd:-777;}
case 21:{struct monst * value=shop_keeper(0);record_result=value;return value?value->mhp:-777;}
case 22:{stairway * value=stairway_at(10,10);record_result=value;return value?value->isladder:-777;}
case 23:{struct trap * value=maketrap(10,10,0);record_result=value;return value?value->ttyp:-777;}
case 24:{struct monst * value=activate_statue_trap(&trap_pool[0],10,10,0);record_result=value;return value?value->mhp:-777;}
case 25:{struct trap * value=t_at(10,10);record_result=value;return value?value->ttyp:-777;}
case 26:{struct monst * value=bhit(0,0,0,0,0,0,&cell);record_result=value;return value?value->mhp:-777;}
default:abort();}}
void probe_record_write(int which,int v){switch(which){
case 0:((struct monst*)record_result)->mhp=v;return;
case 1:((struct obj*)record_result)->spe=v;return;
case 3:((struct obj*)record_result)->spe=v;return;
case 4:((struct obj*)record_result)->spe=v;return;
case 5:((struct obj*)record_result)->spe=v;return;
case 6:((struct obj*)record_result)->spe=v;return;
case 7:((struct obj*)record_result)->spe=v;return;
case 8:((struct obj*)record_result)->spe=v;return;
case 9:((struct obj*)record_result)->spe=v;return;
case 10:((struct monst*)record_result)->mhp=v;return;
case 11:((struct monst*)record_result)->mhp=v;return;
case 13:((struct obj*)record_result)->spe=v;return;
case 14:((struct obj*)record_result)->spe=v;return;
case 15:((struct obj*)record_result)->spe=v;return;
case 16:((struct monst*)record_result)->mhp=v;return;
case 17:((struct obj*)record_result)->spe=v;return;
case 18:((struct monst*)record_result)->mhp=v;return;
case 19:((struct attack*)record_result)->damd=v;return;
case 20:((struct attack*)record_result)->damd=v;return;
case 21:((struct monst*)record_result)->mhp=v;return;
case 22:((struct stairway*)record_result)->isladder=v;return;
case 23:((struct trap*)record_result)->ttyp=v;return;
case 24:((struct monst*)record_result)->mhp=v;return;
case 25:((struct trap*)record_result)->ttyp=v;return;
case 26:((struct monst*)record_result)->mhp=v;return;
default:abort();}}
