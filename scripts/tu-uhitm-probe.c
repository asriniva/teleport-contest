/* Private UHITM actual-C/imported-JS differential; foreign world is controlled. */
#define NEED_VARARGS
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <setjmp.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(gy) gy;
__typeof__(gv) gv;
__typeof__(gm) gm;
__typeof__(u) u;
__typeof__(svc) svc;
__typeof__(gb) gb;
__typeof__(svl) svl;
__typeof__(flags) flags;
__typeof__(go) go;
__typeof__(gu) gu;
__typeof__(uarm) uarm;
__typeof__(uwep) uwep;
__typeof__(uarms) uarms;
__typeof__(uball) uball;
__typeof__(svr) svr;
__typeof__(gn) gn;
__typeof__(uarmg) uarmg;
__typeof__(uswapwep) uswapwep;
__typeof__(gt) gt;
__typeof__(svm) svm;
__typeof__(gi) gi;
__typeof__(gs) gs;
__typeof__(uarmh) uarmh;
__typeof__(svd) svd;
__typeof__(svk) svk;
__typeof__(uright) uright;
__typeof__(uleft) uleft;
__typeof__(uamul) uamul;
__typeof__(ublindf) ublindf;
__typeof__(disp) disp;
__typeof__(uarmu) uarmu;
__typeof__(uarmc) uarmc;
__typeof__(uarmf) uarmf;
__typeof__(sysopt) sysopt;
__typeof__(windowprocs) windowprocs;
__typeof__(gc) gc;
__typeof__(ga) ga;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
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
const struct symdef defsyms[MAXPCHARS + 1] = {
#define PCHAR_DRAWING
#include "defsym.h"
#undef PCHAR_DRAWING
    { 0, NULL, NO_COLOR }
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
static struct _hitmon_data hmd_pool; static struct mhitm_data mhm_pool;static void*record_result;static struct obj object_pool[64];static struct monst monster_pool[16];static struct trap trap_pool[8];static coord coord_pool[8];static anything any_pool;static struct attack attack_pool[2];static stairway stairs_pool[2];static int scalar_pool[8];
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
const char*singular(struct obj*o,char*(*fn)(struct obj*)){logmsg("singular_cb:%d;",fn==xname);return fn(o);}
struct obj*getobj(const char*verb,int(*fn)(struct obj*),unsigned flags_){struct obj*o=opts[0]?0:&object_pool[0];logmsg("getobj:%s:%u:%d;",verb,flags_,fn(o));callback();record_result=o;return o;}
void getlin(const char*prompt,char*out){logmsg("getlin:%s;",prompt);strcpy(out,inputbuf);}
void do_clear_area(coordxy x,coordxy y,int radius,void(*fn)(coordxy,coordxy,void*),genericptr_t value){logmsg("area:%d:%d:%d;",x,y,radius);for(int dx=-1;dx<=1;dx++)for(int dy=-1;dy<=1;dy++)if(isok(x+dx,y+dy))fn(x+dx,y+dy,value);callback();}
void getpos_sethilite(void(*display)(boolean),boolean(*valid)(coordxy,coordxy)){logmsg("hilite:%d;",valid(u.ux,u.uy));if(opts[10]){display(TRUE);display(FALSE);}}
int getpos(coord*c,boolean force,const char*goal){logmsg("getpos:%d:%s;",force,goal);c->x=u.ux;c->y=u.uy;return opts[11]?-1:0;}
struct obj*mksobj(int typ,boolean init,boolean arti){logmsg("mksobj:%d:%d:%d;",typ,init,arti);struct obj*o=&object_pool[(object_next++)%64];memset(o,0,sizeof*o);o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;record_result=o;return o;}
struct obj*mkobj(int cls,boolean arti){logmsg("mkobj:%d;",cls);return mksobj(DAGGER,TRUE,arti);}
struct obj*some_armor(struct monst*m){logmsg("armor:%d;",id(m));return (record_result=(opts[1]?0:uarm));}
struct obj*which_armor(struct monst*m,long mask){logmsg("whicharmor:%d:%ld;",id(m),mask);return (record_result=(opts[1]?0:uarmh));}
void make_confused(long n,boolean message){HConfusion=n;logmsg("confuse:%ld:%d;",n,message);}void make_stunned(long n,boolean message){HStun=n;logmsg("stun:%ld:%d;",n,message);}
void useup(struct obj*o){logmsg("useup:%d;",id(o));o->in_use=0;callback();}void strange_feeling(struct obj*o,const char*s){logmsg("strange:%d:%s;",id(o),s?s:"");useup(o);}
boolean is_art(struct obj*o,int n){return o&&o->oartifact==n;}
int bcsign(struct obj*o){return o->blessed-o->cursed;}
int strncmpi(const char*a,const char*b,int n){while(n&&*a&&lowc(*a)==lowc(*b)){a++;b++;if(n>0)n--;}return n?lowc(*a)-lowc(*b):0;}
char*strstri(const char*s,const char*part){size_t n=strlen(part);for(;*s;s++)if(!strncmpi(s,part,(int)n))return(char*)s;return n?0:(char*)s;}
char*mungspaces(char*s){char*in=s,*out=s;while(*in==' ')in++;for(;*in;in++){if(*in==' '&&(out==s||out[-1]==' '))continue;*out++=*in;}if(out>s&&out[-1]==' ')out--;*out=0;return s;}
int name_to_mon(const char*s,int*gender){logmsg("name_to_mon:%s;",s);if(gender)*gender=opts[5]?FEMALE:NEUTRAL;return opts[4]?NON_PM:PM_HUMAN;}
int name_to_monclass(const char*s,int*type){logmsg("name_to_monclass:%s;",s);if(type)*type=NON_PM;return opts[6]?S_ORC:0;}
/* Controlled external seams, not source combat policy. */
static void window_display(winid win,boolean block){logmsg("display:%d:%d;",win,block);callback();}
static void window_delay(void){logmsg("delay;");}
schar acurr(int attribute){logmsg("acurr:%d;",attribute);return opts[20]?opts[20]:18;}
boolean check_capacity(const char*message){logmsg("capacity;");return opts[21];}
int glyph_at(coordxy x,coordxy y){return levl[x][y].glyph;}
int rn2_on_display_rng(int n){return(rn2)(n);}
void pline_mon(struct monst*m,const char*f,...){va_list ap;va_start(ap,f);logmsg("mon:%d:",id(m));vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");callback();}
void nhassert_failed(const char*expr,const char*file,int line){logmsg("nhassert:%s:%s:%d;",expr,file,line);longjmp(fixture_jump,1);}

void xkilled(struct monst*m,int flags_){logmsg("xkilled:%d:%d;",id(m),flags_);if(opts[31])m->mhp=0;callback();}
void mhurtle(struct monst*m,int x,int y,int range){logmsg("mhurtle:%d:%d:%d:%d;",id(m),x,y,range);if(opts[32]){m->data=&mons[PM_IRON_GOLEM];m->mx+=x;m->my+=y;}if(opts[34])m->mhp=0;callback();}
boolean artifact_hit(struct monst*a,struct monst*b,struct obj*o,int*damage,int roll){logmsg("artifact:%d:%d:%d:%d:%d;",id(a),id(b),id(o),*damage,roll);if(opts[33])*damage+=17;if(opts[35])uwep=&object_pool[3];return opts[3];}

int is_safemon(struct monst*m){logmsg("safemon:%d;",id(m));return opts[41];}
char*in_rooms(coordxy x,coordxy y,int base){static char rooms[3]={ROOMOFFSET,ROOMOFFSET+1,0};logmsg("rooms:%d:%d:%d;",x,y,base);return rooms;}
boolean tended_shop(struct mkroom*r){logmsg("shoproom:%ld;",(long)(r-svr.rooms));return opts[42];}

struct attack*getmattk(struct monst*a,struct monst*d,int i,int*sum,struct attack*alt){logmsg("getmattk:%d:%d:%d:%d;",id(a),id(d),i,sum[i]);if(opts[43]){*alt=attack_pool[0];record_result=alt;}else record_result=&attack_pool[0];return record_result;}
char * Adjmonnam(struct monst * a0,const char * a1){logmsg("Adjmonnam:%d,%s;",id((const void*)a0),(a1?a1:"(null)"));return namecopy("fixture");}
char * An(const char * a0){logmsg("An:%s;",(a0?a0:"(null)"));return namecopy("fixture");}
int Finish_digestion(void){logmsg("Finish_digestion:;");return opts[3];}
int Mgender(struct monst * a0){logmsg("Mgender:%d;",id((const void*)a0));return opts[3];}
char * Monnam(struct monst * a0){logmsg("Monnam:%d;",id((const void*)a0));return namecopy("fixture");}
boolean Resists_Elem(struct monst * a0,int a1){logmsg("Resists_Elem:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
char * Some_Monnam(struct monst * a0){logmsg("Some_Monnam:%d;",id((const void*)a0));return namecopy("fixture");}
char * The(const char * a0){logmsg("The:%s;",(a0?a0:"(null)"));return namecopy("fixture");}
char * Yname2(struct obj * a0){logmsg("Yname2:%d;",id((const void*)a0));return namecopy("fixture");}
char * Yobjnam2(struct obj * a0,const char * a1){logmsg("Yobjnam2:%d,%s;",id((const void*)a0),(a1?a1:"(null)"));return namecopy("fixture");}
void __assert_fail(const char * a0,const char * a1,int a2,const char * a3){logmsg("__assert_fail:%s,%s,%d,%s;",(a0?a0:"(null)"),(a1?a1:"(null)"),(int)a2,(a3?a3:"(null)"));longjmp(fixture_jump,1);}
char * a_monnam(struct monst * a0){logmsg("a_monnam:%d;",id((const void*)a0));return namecopy("fixture");}
int abon(void){logmsg("abon:;");return opts[3];}
void abuse_dog(struct monst * a0){logmsg("abuse_dog:%d;",id((const void*)a0));}
void acid_damage(struct obj * a0){logmsg("acid_damage:%d;",id((const void*)a0));}
int add_to_minv(struct monst * a0,struct obj * a1){logmsg("add_to_minv:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
struct obj * addinv(struct obj * a0){logmsg("addinv:%d;",id((const void*)a0));return (record_result=(opts[1]?0:&object_pool[1]));}
void adjalign(int a0){logmsg("adjalign:%d;",(int)a0);}
boolean adjattrib(int a0,int a1,int a2){logmsg("adjattrib:%d,%d,%d;",(int)a0,(int)a1,(int)a2);return opts[3];}
int adtyp_to_expltype(const int a0){logmsg("adtyp_to_expltype:%d;",(int)a0);return opts[3];}
boolean angry_guards(boolean a0){logmsg("angry_guards:%d;",(int)a0);return opts[3];}
boolean artifact_light(struct obj * a0){logmsg("artifact_light:%d;",id((const void*)a0));return opts[3];}
boolean attacktype(struct permonst * a0,int a1){logmsg("attacktype:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
long attk_protection(int a0){logmsg("attk_protection:%d;",(int)a0);return opts[3];}
int attrcurse(void){logmsg("attrcurse:;");return opts[3];}
char * bare_artifactname(struct obj * a0){logmsg("bare_artifactname:%d;",id((const void*)a0));return namecopy("fixture");}
const char * body_part(int a0){logmsg("body_part:%d;",(int)a0);return namecopy("fixture");}
boolean breaktest(struct obj * a0){logmsg("breaktest:%d;",id((const void*)a0));return opts[3];}
void burn_away_slime(void){logmsg("burn_away_slime:;");}
boolean can_be_strangled(struct monst * a0){logmsg("can_be_strangled:%d;",id((const void*)a0));return opts[3];}
boolean can_blnd(struct monst * a0,struct monst * a1,uchar a2,struct obj * a3){logmsg("can_blnd:%d,%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2,id((const void*)a3));return opts[3];}
int can_twoweapon(void){logmsg("can_twoweapon:;");return opts[3];}
int canseemon(struct monst * a0){logmsg("canseemon:%d;",id((const void*)a0));return opts[3];}
struct obj * carrying(int a0){logmsg("carrying:%d;",(int)a0);return (record_result=(opts[1]?0:&object_pool[1]));}
void change_luck(schar a0){logmsg("change_luck:%d;",(int)a0);}
const char * cloak_simple_name(struct obj * a0){logmsg("cloak_simple_name:%d;",id((const void*)a0));return namecopy("fixture");}
struct monst * clone_mon(struct monst * a0,coordxy a1,coordxy a2){logmsg("clone_mon:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return (record_result=(opts[2]?0:&monster_pool[1]));}
struct monst * cloneu(void){logmsg("cloneu:;");return (record_result=(opts[2]?0:&monster_pool[1]));}
boolean corpse_chance(struct monst * a0,struct monst * a1,boolean a2){logmsg("corpse_chance:%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2);return opts[3];}
char * corpse_xname(struct obj * a0,const char * a1,unsigned int a2){logmsg("corpse_xname:%d,%s,%d;",id((const void*)a0),(a1?a1:"(null)"),(int)a2);return namecopy("fixture");}
int could_seduce(struct monst * a0,struct monst * a1,struct attack * a2){logmsg("could_seduce:%d,%d,%d;",id((const void*)a0),id((const void*)a1),id((const void*)a2));return opts[3];}
void cutworm(struct monst * a0,coordxy a1,coordxy a2,boolean a3){logmsg("cutworm:%d,%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2,(int)a3);}
char * cxname(struct obj * a0){logmsg("cxname:%d;",id((const void*)a0));return namecopy("fixture");}
int dbon(void){logmsg("dbon:;");return opts[3];}
void dealloc_obj(struct obj * a0){logmsg("dealloc_obj:%d;",id((const void*)a0));}
boolean defended(struct monst * a0,int a1){logmsg("defended:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
boolean defends(int a0,struct obj * a1){logmsg("defends:%d,%d;",(int)a0,id((const void*)a1));return opts[3];}
void delayed_killer(int a0,int a1,const char * a2){logmsg("delayed_killer:%d,%d,%s;",(int)a0,(int)a1,(a2?a2:"(null)"));}
int destroy_items(struct monst * a0,int a1,int a2){logmsg("destroy_items:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return opts[3];}
boolean diseasemu(struct permonst * a0){logmsg("diseasemu:%d;",id((const void*)a0));return opts[3];}
void dismount_steed(int a0){logmsg("dismount_steed:%d;",(int)a0);}
boolean dmgtype(struct permonst * a0,int a1){logmsg("dmgtype:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){logmsg("dmgtype_fromattack:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return (record_result=(opts[5]?0:&attack_pool[0]));}
int dmgval(struct obj * a0,struct monst * a1){logmsg("dmgval:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
int dog_nutrition(struct monst * a0,struct obj * a1){logmsg("dog_nutrition:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
void done(int a0){logmsg("done:%d;",(int)a0);}
void done_in_by(struct monst * a0,int a1){logmsg("done_in_by:%d,%d;",id((const void*)a0),(int)a1);}
boolean doorless_door(coordxy a0,coordxy a1){logmsg("doorless_door:%d,%d;",(int)a0,(int)a1);return opts[3];}
int dopay(void){logmsg("dopay:;");return opts[3];}
int doseduce(struct monst * a0){logmsg("doseduce:%d;",id((const void*)a0));return opts[3];}
void drain_en(int a0,boolean a1){logmsg("drain_en:%d,%d;",(int)a0,(int)a1);}
boolean drain_item(struct obj * a0,boolean a1){logmsg("drain_item:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
void drain_weapon_skill(int a0){logmsg("drain_weapon_skill:%d;",(int)a0);}
void drop_uswapwep(void){logmsg("drop_uswapwep:;");}
void dropy(struct obj * a0){logmsg("dropy:%d;",id((const void*)a0));}
void dry_a_towel(struct obj * a0,int a1,boolean a2){logmsg("dry_a_towel:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);}
int eat_brains(struct monst * a0,struct monst * a1,boolean a2,int * a3){logmsg("eat_brains:%d,%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2,id((const void*)a3));return opts[3];}
void eating_conducts(struct permonst * a0){logmsg("eating_conducts:%d;",id((const void*)a0));}
void end_running(boolean a0){logmsg("end_running:%d;",(int)a0);}
boolean engulf_target(struct monst * a0,struct monst * a1){logmsg("engulf_target:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
int erode_obj(struct obj * a0,const char * a1,int a2,int a3){logmsg("erode_obj:%d,%s,%d,%d;",id((const void*)a0),(a1?a1:"(null)"),(int)a2,(int)a3);return opts[3];}
const char * exclam(int a0){logmsg("exclam:%d;",(int)a0);return namecopy("fixture");}
void exercise(int a0,boolean a1){logmsg("exercise:%d,%d;",(int)a0,(int)a1);}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logmsg("explode:%d,%d,%d,%d,%d,%d;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);}
void extract_from_minvent(struct monst * a0,struct obj * a1,boolean a2,boolean a3){logmsg("extract_from_minvent:%d,%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2,(int)a3);}
boolean failed_grab(struct monst * a0,struct monst * a1,struct attack * a2){logmsg("failed_grab:%d,%d,%d;",id((const void*)a0),id((const void*)a1),id((const void*)a2));return opts[3];}
void fall_asleep(int a0,boolean a1){logmsg("fall_asleep:%d,%d;",(int)a0,(int)a1);}
void find_artifact(struct obj * a0){logmsg("find_artifact:%d;",id((const void*)a0));}
int find_mac(struct monst * a0){logmsg("find_mac:%d;",id((const void*)a0));return opts[3];}
struct obj * findgold(struct obj * a0){logmsg("findgold:%d;",id((const void*)a0));return (record_result=(opts[1]?0:&object_pool[1]));}
void freeinv(struct obj * a0){logmsg("freeinv:%d;",id((const void*)a0));}
int gender(struct monst * a0){logmsg("gender:%d;",id((const void*)a0));return opts[3];}
void ghod_hitsu(struct monst * a0){logmsg("ghod_hitsu:%d;",id((const void*)a0));}
int glyph_to_cmap(int a0){logmsg("glyph_to_cmap:%d;",(int)a0);return opts[3];}
void golemeffects(struct monst * a0,int a1,int a2){logmsg("golemeffects:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);}
struct permonst * grow_up(struct monst * a0,struct monst * a1){logmsg("grow_up:%d,%d;",id((const void*)a0),id((const void*)a1));return (record_result=(opts[7]?0:&mons[PM_HUMAN]));}
boolean hates_silver(struct permonst * a0){logmsg("hates_silver:%d;",id((const void*)a0));return opts[3];}
const char * hcolor(const char * a0){logmsg("hcolor:%s;",(a0?a0:"(null)"));return namecopy("fixture");}
int healmon(struct monst * a0,int a1,int a2){logmsg("healmon:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return opts[3];}
const char * helm_simple_name(struct obj * a0){logmsg("helm_simple_name:%d;",id((const void*)a0));return namecopy("fixture");}
char highc(char a0){logmsg("highc:%d;",(int)a0);return opts[3];}
void hit(const char * a0,struct monst * a1,const char * a2){logmsg("hit:%s,%d,%s;",a0,id((const void*)a1),a2);}
void hitmsg(struct monst * a0,struct attack * a1){logmsg("hitmsg:%d,%d;",id((const void*)a0),id((const void*)a1));}
int hitval(struct obj * a0,struct monst * a1){logmsg("hitval:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
const char * hliquid(const char * a0){logmsg("hliquid:%s;",(a0?a0:"(null)"));return namecopy("fixture");}
struct obj * hold_another_object(struct obj * a0,const char * a1,const char * a2,const char * a3){logmsg("hold_another_object:%d,%s,%s,%s;",id((const void*)a0),(a1?a1:"(null)"),(a2?a2:"(null)"),(a3?a3:"(null)"));return (record_result=(opts[1]?0:&object_pool[1]));}
void hurtle(int a0,int a1,int a2,boolean a3){logmsg("hurtle:%d,%d,%d,%d;",(int)a0,(int)a1,(int)a2,(int)a3);}
void ignite_items(struct obj * a0){logmsg("ignite_items:%d;",id((const void*)a0));}
char * ing_suffix(const char * a0){logmsg("ing_suffix:%s;",a0);return namecopy("fixture");}
void instapetrify(const char * a0){logmsg("instapetrify:%s;",(a0?a0:"(null)"));}
int inv_cnt(boolean a0){logmsg("inv_cnt:%d;",(int)a0);return opts[3];}
boolean is_fainted(void){logmsg("is_fainted:;");return opts[3];}
boolean is_pool(coordxy a0,coordxy a1){logmsg("is_pool:%d,%d;",(int)a0,(int)a1);return opts[3];}
boolean is_waterwall(coordxy a0,coordxy a1){logmsg("is_waterwall:%d,%d;",(int)a0,(int)a1);return opts[3];}
void killed(struct monst * a0){logmsg("killed:%d;",id((const void*)a0));}
char * l_monnam(struct monst * a0){logmsg("l_monnam:%d;",id((const void*)a0));return namecopy("fixture");}
const char * locomotion(const struct permonst * a0,const char * a1){logmsg("locomotion:%d,%s;",id((const void*)a0),a1);return namecopy("fixture");}
void losespells(void){logmsg("losespells:;");}
void losexp(const char * a0){logmsg("losexp:%s;",(a0?a0:"(null)"));}
struct obj * m_carrying(struct monst * a0,int a1){logmsg("m_carrying:%d,%d;",id((const void*)a0),(int)a1);return (record_result=(opts[1]?0:&object_pool[1]));}
int m_move(struct monst * a0,int a1){logmsg("m_move:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
void m_useup(struct monst * a0,struct obj * a1){logmsg("m_useup:%d,%d;",id((const void*)a0),id((const void*)a1));}
void m_useupall(struct monst * a0,struct obj * a1){logmsg("m_useupall:%d,%d;",id((const void*)a0),id((const void*)a1));}
int magic_negation(struct monst * a0){logmsg("magic_negation:%d;",id((const void*)a0));return opts[3];}
void make_blinded(long a0,boolean a1){logmsg("make_blinded:%ld,%d;",(long)a0,(int)a1);}
void make_sick(long a0,const char * a1,boolean a2,int a3){logmsg("make_sick:%ld,%s,%d,%d;",(long)a0,(a1?a1:"(null)"),(int)a2,(int)a3);}
void make_slimed(long a0,const char * a1){logmsg("make_slimed:%ld,%s;",(long)a0,(a1?a1:"(null)"));}
void make_stoned(long a0,const char * a1,int a2,const char * a3){logmsg("make_stoned:%ld,%s,%d,%s;",(long)a0,(a1?a1:"(null)"),(int)a2,(a3?a3:"(null)"));}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logmsg("makemon:%d,%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2,(int)a3);return (record_result=(opts[2]?0:&monster_pool[1]));}
void map_invisible(coordxy a0,coordxy a1){logmsg("map_invisible:%d,%d;",(int)a0,(int)a1);}
void map_location(coordxy a0,coordxy a1,int a2){logmsg("map_location:%d,%d,%d;",(int)a0,(int)a1,(int)a2);}
const char * mbodypart(struct monst * a0,int a1){logmsg("mbodypart:%d,%d;",id((const void*)a0),(int)a1);return namecopy("fixture");}
void mdamageu(struct monst * a0,int a1){logmsg("mdamageu:%d,%d;",id((const void*)a0),(int)a1);}
struct obj * merge_choice(struct obj * a0,struct obj * a1){logmsg("merge_choice:%d,%d;",id((const void*)a0),id((const void*)a1));return (record_result=(opts[1]?0:&object_pool[1]));}
void mhidden_description(struct monst * a0,unsigned int a1,char * a2){logmsg("mhidden_description:%d,%d,%d;",id((const void*)a0),(int)a1,id((const void*)a2));}
void minstapetrify(struct monst * a0,boolean a1){logmsg("minstapetrify:%d,%d;",id((const void*)a0),(int)a1);}
int mintrap(struct monst * a0,unsigned int a1){logmsg("mintrap:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
struct obj * mlifesaver(struct monst * a0){logmsg("mlifesaver:%d;",id((const void*)a0));return (record_result=(opts[1]?0:&object_pool[1]));}
void mon_adjust_speed(struct monst * a0,int a1,struct obj * a2){logmsg("mon_adjust_speed:%d,%d,%d;",id((const void*)a0),(int)a1,id((const void*)a2));}
void mon_give_prop(struct monst * a0,int a1){logmsg("mon_give_prop:%d,%d;",id((const void*)a0),(int)a1);}
boolean mon_hates_blessings(struct monst * a0){logmsg("mon_hates_blessings:%d;",id((const void*)a0));return opts[3];}
boolean mon_hates_light(struct monst * a0){logmsg("mon_hates_light:%d;",id((const void*)a0));return opts[3];}
boolean mon_hates_silver(struct monst * a0){logmsg("mon_hates_silver:%d;",id((const void*)a0));return opts[3];}
char * mon_nam(struct monst * a0){logmsg("mon_nam:%d;",id((const void*)a0));return namecopy("fixture");}
char * mon_nam_too(struct monst * a0,struct monst * a1){logmsg("mon_nam_too:%d,%d;",id((const void*)a0),id((const void*)a1));return namecopy("fixture");}
int mon_poly(struct monst * a0,struct monst * a1,int a2){logmsg("mon_poly:%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2);return opts[3];}
void mon_to_stone(struct monst * a0){logmsg("mon_to_stone:%d;",id((const void*)a0));}
void mondied(struct monst * a0){logmsg("mondied:%d;",id((const void*)a0));}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){logmsg("monflee:%d,%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2,(int)a3);}
void mongone(struct monst * a0){logmsg("mongone:%d;",id((const void*)a0));}
void monkilled(struct monst * a0,const char * a1,int a2){logmsg("monkilled:%d,%s,%d;",id((const void*)a0),(a1?a1:"(null)"),(int)a2);}
boolean monnear(struct monst * a0,coordxy a1,coordxy a2){logmsg("monnear:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return opts[3];}
void monstone(struct monst * a0){logmsg("monstone:%d;",id((const void*)a0));}
void monstseesu(unsigned long a0){logmsg("monstseesu:%ld;",(long)a0);}
void monstunseesu(unsigned long a0){logmsg("monstunseesu:%ld;",(long)a0);}
void morehungry(int a0){logmsg("morehungry:%d;",(int)a0);}
int mpickobj(struct monst * a0,struct obj * a1){logmsg("mpickobj:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
const char * mpoisons_subj(struct monst * a0,struct attack * a1){logmsg("mpoisons_subj:%d,%d;",id((const void*)a0),id((const void*)a1));return namecopy("fixture");}
void mselftouch(struct monst * a0,const char * a1,boolean a2){logmsg("mselftouch:%d,%s,%d;",id((const void*)a0),(a1?a1:"(null)"),(int)a2);}
char * mshot_xname(struct obj * a0){logmsg("mshot_xname:%d;",id((const void*)a0));return namecopy("fixture");}
boolean mtrapped_in_pit(struct monst * a0){logmsg("mtrapped_in_pit:%d;",id((const void*)a0));return opts[3];}
boolean munslime(struct monst * a0,boolean a1){logmsg("munslime:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
boolean munstone(struct monst * a0,boolean a1){logmsg("munstone:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
int ndemon(aligntyp a0){logmsg("ndemon:%d;",(int)a0);return opts[3];}
int near_capacity(void){logmsg("near_capacity:;");return opts[3];}
int newcham(struct monst * a0,struct permonst * a1,unsigned int a2){logmsg("newcham:%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2);return opts[3];}
void newsym(coordxy a0,coordxy a1){logmsg("newsym:%d,%d;",(int)a0,(int)a1);}
void newuhs(boolean a0){logmsg("newuhs:%d;",(int)a0);}
int night(void){logmsg("night:;");return opts[3];}
boolean noattacks(struct permonst * a0){logmsg("noattacks:%d;",id((const void*)a0));return opts[3];}
void nomul(int a0){logmsg("nomul:%d;",(int)a0);}
void obfree(struct obj * a0,struct obj * a1){logmsg("obfree:%d,%d;",id((const void*)a0),id((const void*)a1));}
void obj_extract_self(struct obj * a0){logmsg("obj_extract_self:%d;",id((const void*)a0));}
boolean obj_is_pname(struct obj * a0){logmsg("obj_is_pname:%d;",id((const void*)a0));return opts[3] && has_oname(a0);}
boolean obj_resists(struct obj * a0,int a1,int a2){logmsg("obj_resists:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return opts[3];}
void obj_stop_timers(struct obj * a0){logmsg("obj_stop_timers:%d;",id((const void*)a0));}
boolean object_from_map(int a0,coordxy a1,coordxy a2,struct obj ** a3){logmsg("object_from_map:%d,%d,%d,%d;",(int)a0,(int)a1,(int)a2,id((const void*)a3));return opts[3];}
void observe_object(struct obj * a0){logmsg("observe_object:%d;",id((const void*)a0));}
const char * on_fire(struct permonst * a0,struct attack * a1){logmsg("on_fire:%d,%d;",id((const void*)a0),id((const void*)a1));return namecopy("fixture");}
char * otense(struct obj * a0,const char * a1){logmsg("otense:%d,%s;",id((const void*)a0),a1);return namecopy("fixture");}
boolean overexertion(void){logmsg("overexertion:;");return opts[3];}
void panic(const char * a0,...){logmsg("panic:%s;",(a0?a0:"(null)"));longjmp(fixture_jump,1);}
void paralyze_monst(struct monst * a0,int a1){logmsg("paralyze_monst:%d,%d;",id((const void*)a0),(int)a1);}
boolean paranoid_query(boolean a0,const char * a1){logmsg("paranoid_query:%d,%s;",(int)a0,(a1?a1:"(null)"));return opts[3];}
boolean permapoisoned(struct obj * a0){logmsg("permapoisoned:%d;",id((const void*)a0));return opts[3];}
void place_object(struct obj * a0,coordxy a1,coordxy a2){logmsg("place_object:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);}
void poisoned(const char * a0,int a1,const char * a2,int a3,boolean a4){logmsg("poisoned:%s,%d,%s,%d,%d;",a0,(int)a1,(a2?a2:"(null)"),(int)a3,(int)a4);}
boolean poly_when_stoned(struct permonst * a0){logmsg("poly_when_stoned:%d;",id((const void*)a0));return opts[3];}
int polymon(int a0){logmsg("polymon:%d;",(int)a0);return opts[3];}
void possibly_unwield(struct monst * a0,boolean a1){logmsg("possibly_unwield:%d,%d;",id((const void*)a0),(int)a1);}
void potionhit(struct monst * a0,struct obj * a1,int a2){logmsg("potionhit:%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2);}
int pronoun_gender(struct monst * a0,unsigned int a1){logmsg("pronoun_gender:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
void rehumanize(void){logmsg("rehumanize:;");}
void release_camera_demon(struct obj * a0,coordxy a1,coordxy a2){logmsg("release_camera_demon:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);}
int resist(struct monst * a0,char a1,int a2,int a3){logmsg("resist:%d,%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2,(int)a3);return opts[3];}
boolean resists_blnd(struct monst * a0){logmsg("resists_blnd:%d;",id((const void*)a0));return opts[3];}
boolean resists_blnd_by_arti(struct monst * a0){logmsg("resists_blnd_by_arti:%d;",id((const void*)a0));return opts[3];}
boolean resists_drli(struct monst * a0){logmsg("resists_drli:%d;",id((const void*)a0));return opts[3];}
void retouch_equipment(int a0){logmsg("retouch_equipment:%d;",(int)a0);}
boolean rloc(struct monst * a0,unsigned int a1){logmsg("rloc:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
void rustm(struct monst * a0,struct obj * a1){logmsg("rustm:%d,%d;",id((const void*)a0),id((const void*)a1));}
char * s_suffix(const char * a0){logmsg("s_suffix:%s;",a0);return namecopy("fixture");}
void seemimic(struct monst * a0){logmsg("seemimic:%d;",id((const void*)a0));}
int sensemon(struct monst * a0){logmsg("sensemon:%d;",id((const void*)a0));return opts[3];}
void set_apparxy(struct monst * a0){logmsg("set_apparxy:%d;",id((const void*)a0));}
void set_corpsenm(struct obj * a0,int a1){logmsg("set_corpsenm:%d,%d;",id((const void*)a0),(int)a1);}
void set_twoweap(boolean a0){logmsg("set_twoweap:%d;",(int)a0);}
void set_ulycn(int a0){logmsg("set_ulycn:%d;",(int)a0);}
void set_ustuck(struct monst * a0){logmsg("set_ustuck:%d;",id((const void*)a0));}
void set_wounded_legs(long a0,int a1){logmsg("set_wounded_legs:%ld,%d;",(long)a0,(int)a1);}
void setmangry(struct monst * a0,boolean a1){logmsg("setmangry:%d,%d;",id((const void*)a0),(int)a1);}
void setmnotwielded(struct monst * a0,struct obj * a1){logmsg("setmnotwielded:%d,%d;",id((const void*)a0),id((const void*)a1));}
void setuwep(struct obj * a0){logmsg("setuwep:%d;",id((const void*)a0));}
boolean shade_glare(struct obj * a0){logmsg("shade_glare:%d;",id((const void*)a0));return opts[3];}
void shieldeff(coordxy a0,coordxy a1){logmsg("shieldeff:%d,%d;",(int)a0,(int)a1);}
void silver_sears(struct monst * a0,struct monst * a1,long a2){logmsg("silver_sears:%d,%d,%ld;",id((const void*)a0),id((const void*)a1),(long)a2);}
char * simpleonames(struct obj * a0){logmsg("simpleonames:%d;",id((const void*)a0));return namecopy("fixture");}
int sleep_monst(struct monst * a0,int a1,int a2){logmsg("sleep_monst:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return opts[3];}
void slept_monst(struct monst * a0){logmsg("slept_monst:%d;",id((const void*)a0));}
boolean snuff_lit(struct obj * a0){logmsg("snuff_lit:%d;",id((const void*)a0));return opts[3];}
char * some_mon_nam(struct monst * a0){logmsg("some_mon_nam:%d;",id((const void*)a0));return namecopy("fixture");}
int special_dmgval(struct monst * a0,struct monst * a1,long a2,long * a3){logmsg("special_dmgval:%d,%d,%ld,%d;",id((const void*)a0),id((const void*)a1),(long)a2,id((const void*)a3));return opts[3];}
struct monst * split_mon(struct monst * a0,struct monst * a1){logmsg("split_mon:%d,%d;",id((const void*)a0),id((const void*)a1));return (record_result=(opts[2]?0:&monster_pool[1]));}
struct obj * splitobj(struct obj * a0,long a1){logmsg("splitobj:%d,%ld;",id((const void*)a0),(long)a1);return (record_result=(opts[1]?0:&object_pool[1]));}
const char * stagger(const struct permonst * a0,const char * a1){logmsg("stagger:%d,%s;",id((const void*)a0),a1);return namecopy("fixture");}
int steal(struct monst * a0,char * a1){logmsg("steal:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
void stealamulet(struct monst * a0){logmsg("stealamulet:%d;",id((const void*)a0));}
void stealgold(struct monst * a0){logmsg("stealgold:%d;",id((const void*)a0));}
boolean sticks(struct permonst * a0){logmsg("sticks:%d;",id((const void*)a0));return opts[3];}
int strNsubst(char * a0,const char * a1,const char * a2,int a3){logmsg("strNsubst:%d,%s,%s,%d;",id((const void*)a0),a1,a2,(int)a3);return opts[3];}
char * strncat(char *restrict a0,const char *restrict a1,size_t a2){logmsg("strncat:%d,%d,%ld;",id((const void*)a0),id((const void*)a1),(long)a2);return namecopy("fixture");}
boolean tamedog(struct monst * a0,struct obj * a1,boolean a2){logmsg("tamedog:%d,%d,%d;",id((const void*)a0),id((const void*)a1),(int)a2);return opts[3];}
void tele(void){logmsg("tele:;");}
boolean tele_restrict(struct monst * a0){logmsg("tele_restrict:%d;",id((const void*)a0));return opts[3];}
boolean test_move(coordxy a0,coordxy a1,coordxy a2,coordxy a3,int a4){logmsg("test_move:%d,%d,%d,%d,%d;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4);return opts[3];}
char * the(const char * a0){logmsg("the:%s;",(a0?a0:"(null)"));return namecopy("fixture");}
void tmp_at(coordxy a0,coordxy a1){logmsg("tmp_at:%d,%d;",(int)a0,(int)a1);}
void touch_of_death(struct monst * a0){logmsg("touch_of_death:%d;",id((const void*)a0));}
int tp_sensemon(struct monst * a0){logmsg("tp_sensemon:%d;",id((const void*)a0));return opts[3];}
boolean u_slip_free(struct monst * a0,struct attack * a1){logmsg("u_slip_free:%d,%d;",id((const void*)a0),id((const void*)a1));return opts[3];}
void u_slow_down(void){logmsg("u_slow_down:;");}
boolean u_teleport_mon(struct monst * a0,boolean a1){logmsg("u_teleport_mon:%d,%d;",id((const void*)a0),(int)a1);return opts[3];}
void u_wipe_engr(int a0){logmsg("u_wipe_engr:%d;",(int)a0);}
void ugolemeffects(int a0,int a1){logmsg("ugolemeffects:%d,%d;",(int)a0,(int)a1);}
boolean unconscious(void){logmsg("unconscious:;");return opts[3];}
boolean undiscovered_artifact(xint16 a0){logmsg("undiscovered_artifact:%d;",(int)a0);return opts[3];}
boolean unmap_invisible(coordxy a0,coordxy a1){logmsg("unmap_invisible:%d,%d;",(int)a0,(int)a1);return opts[3];}
void unstuck(struct monst * a0){logmsg("unstuck:%d;",id((const void*)a0));}
void untwoweapon(void){logmsg("untwoweapon:;");}
void update_inventory(void){logmsg("update_inventory:;");}
char * upstart(char * a0){logmsg("upstart:%d;",id((const void*)a0));return namecopy("fixture");}
boolean ureflects(const char * a0,const char * a1){logmsg("ureflects:%s,%s;",(a0?a0:"(null)"),(a1?a1:"(null)"));return opts[3];}
void use_skill(int a0,int a1){logmsg("use_skill:%d,%d;",(int)a0,(int)a1);}
void useupall(struct obj * a0){logmsg("useupall:%d;",id((const void*)a0));}
void uunstick(void){logmsg("uunstick:;");}
int uwep_skill_type(void){logmsg("uwep_skill_type:;");return opts[3];}
void uwepgone(void){logmsg("uwepgone:;");}
char * vtense(const char * a0,const char * a1){logmsg("vtense:%s,%s;",(a0?a0:"(null)"),a1);return namecopy("fixture");}
void wake_nearto(coordxy a0,coordxy a1,int a2){logmsg("wake_nearto:%d,%d,%d;",(int)a0,(int)a1,(int)a2);}
void wakeup(struct monst * a0,boolean a1){logmsg("wakeup:%d,%d;",id((const void*)a0),(int)a1);}
int weapon_dam_bonus(struct obj * a0){logmsg("weapon_dam_bonus:%d;",id((const void*)a0));return opts[3];}
int weapon_hit_bonus(struct obj * a0){logmsg("weapon_hit_bonus:%d;",id((const void*)a0));return opts[3];}
int weapon_type(struct obj * a0){logmsg("weapon_type:%d;",id((const void*)a0));return opts[3];}
int weight(struct obj * a0){logmsg("weight:%d;",id((const void*)a0));return opts[3];}
void were_change(struct monst * a0){logmsg("were_change:%d;",id((const void*)a0));}
boolean will_hurtle(struct monst * a0,coordxy a1,coordxy a2){logmsg("will_hurtle:%d,%d,%d;",id((const void*)a0),(int)a1,(int)a2);return opts[3];}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){logmsg("x_monnam:%d,%d,%s,%d,%d;",id((const void*)a0),(int)a1,(a2?a2:"(null)"),(int)a3,(int)a4);return namecopy("fixture");}
void xdrainenergym(struct monst * a0,boolean a1){logmsg("xdrainenergym:%d,%d;",id((const void*)a0),(int)a1);}
int xytodir(int a0,int a1){logmsg("xytodir:%d,%d;",(int)a0,(int)a1);return opts[3];}
char * y_monnam(struct monst * a0){logmsg("y_monnam:%d;",id((const void*)a0));return namecopy("fixture");}
char * yname(struct obj * a0){logmsg("yname:%d;",id((const void*)a0));return namecopy("fixture");}
char * ysimple_name(struct obj * a0){logmsg("ysimple_name:%d;",id((const void*)a0));return namecopy("fixture");}
#ifdef TELEPORT_REFERENCE_TU
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/uhitm.c"
#else
extern boolean teleport_uhitm_test_mhitm_mgc_atk_negated(struct monst *,struct monst *,boolean);
#define mhitm_mgc_atk_negated teleport_uhitm_test_mhitm_mgc_atk_negated
extern boolean teleport_uhitm_test_known_hitum(struct monst *,struct obj *,int *,int,int,struct attack *,int);
#define known_hitum teleport_uhitm_test_known_hitum
extern boolean teleport_uhitm_test_hitum_cleave(struct monst *,struct attack *);
#define hitum_cleave teleport_uhitm_test_hitum_cleave
extern boolean teleport_uhitm_test_double_punch(void);
#define double_punch teleport_uhitm_test_double_punch
extern boolean teleport_uhitm_test_hitum(struct monst *,struct attack *);
#define hitum teleport_uhitm_test_hitum
extern void teleport_uhitm_test_hmon_hitmon_barehands(struct _hitmon_data *,struct monst *);
#define hmon_hitmon_barehands teleport_uhitm_test_hmon_hitmon_barehands
extern void teleport_uhitm_test_hmon_hitmon_weapon_ranged(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_weapon_ranged teleport_uhitm_test_hmon_hitmon_weapon_ranged
extern boolean teleport_uhitm_test_backstabbable(struct monst *);
#define backstabbable teleport_uhitm_test_backstabbable
extern void teleport_uhitm_test_hmon_hitmon_weapon_melee(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_weapon_melee teleport_uhitm_test_hmon_hitmon_weapon_melee
extern void teleport_uhitm_test_hmon_hitmon_weapon(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_weapon teleport_uhitm_test_hmon_hitmon_weapon
extern void teleport_uhitm_test_hmon_hitmon_potion(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_potion teleport_uhitm_test_hmon_hitmon_potion
extern void teleport_uhitm_test_hmon_hitmon_misc_obj(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_misc_obj teleport_uhitm_test_hmon_hitmon_misc_obj
extern void teleport_uhitm_test_hmon_hitmon_do_hit(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_do_hit teleport_uhitm_test_hmon_hitmon_do_hit
extern void teleport_uhitm_test_hmon_hitmon_dmg_recalc(struct _hitmon_data *,struct obj *);
#define hmon_hitmon_dmg_recalc teleport_uhitm_test_hmon_hitmon_dmg_recalc
extern void teleport_uhitm_test_hmon_hitmon_poison(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_poison teleport_uhitm_test_hmon_hitmon_poison
extern void teleport_uhitm_test_hmon_hitmon_jousting(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_jousting teleport_uhitm_test_hmon_hitmon_jousting
extern void teleport_uhitm_test_hmon_hitmon_stagger(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_stagger teleport_uhitm_test_hmon_hitmon_stagger
extern void teleport_uhitm_test_hmon_hitmon_pet(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_pet teleport_uhitm_test_hmon_hitmon_pet
extern void teleport_uhitm_test_hmon_hitmon_splitmon(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_splitmon teleport_uhitm_test_hmon_hitmon_splitmon
extern void teleport_uhitm_test_hmon_hitmon_msg_hit(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_msg_hit teleport_uhitm_test_hmon_hitmon_msg_hit
extern void teleport_uhitm_test_hmon_hitmon_msg_silver(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_msg_silver teleport_uhitm_test_hmon_hitmon_msg_silver
extern void teleport_uhitm_test_hmon_hitmon_msg_lightobj(struct _hitmon_data *,struct monst *,struct obj *);
#define hmon_hitmon_msg_lightobj teleport_uhitm_test_hmon_hitmon_msg_lightobj
extern boolean teleport_uhitm_test_hmon_hitmon(struct monst *,struct obj *,int,int);
#define hmon_hitmon teleport_uhitm_test_hmon_hitmon
extern boolean teleport_uhitm_test_mhurtle_to_doom(struct monst *,int,struct permonst **);
#define mhurtle_to_doom teleport_uhitm_test_mhurtle_to_doom
extern void teleport_uhitm_test_first_weapon_hit(struct obj *);
#define first_weapon_hit teleport_uhitm_test_first_weapon_hit
extern boolean teleport_uhitm_test_shade_aware(struct obj *);
#define shade_aware teleport_uhitm_test_shade_aware
extern boolean teleport_uhitm_test_m_slips_free(struct monst *,struct attack *);
#define m_slips_free teleport_uhitm_test_m_slips_free
extern int teleport_uhitm_test_joust(struct monst *,struct obj *);
#define joust teleport_uhitm_test_joust
extern void teleport_uhitm_test_demonpet(void);
#define demonpet teleport_uhitm_test_demonpet
extern boolean teleport_uhitm_test_theft_petrifies(struct obj *);
#define theft_petrifies teleport_uhitm_test_theft_petrifies
extern void teleport_uhitm_test_steal_it(struct monst *,struct attack *);
#define steal_it teleport_uhitm_test_steal_it
extern void teleport_uhitm_test_mhitm_really_poison(struct monst *,struct attack *,struct monst *,struct mhitm_data *);
#define mhitm_really_poison teleport_uhitm_test_mhitm_really_poison
extern void teleport_uhitm_test_start_engulf(struct monst *);
#define start_engulf teleport_uhitm_test_start_engulf
extern void teleport_uhitm_test_end_engulf(void);
#define end_engulf teleport_uhitm_test_end_engulf
extern int teleport_uhitm_test_gulpum(struct monst *,struct attack *);
#define gulpum teleport_uhitm_test_gulpum
extern boolean teleport_uhitm_test_hmonas(struct monst *);
#define hmonas teleport_uhitm_test_hmonas
extern void teleport_uhitm_test_nohandglow(struct monst *);
#define nohandglow teleport_uhitm_test_nohandglow
#endif
#include "../nethack-c/wasm/tu-fragments/uhitm-support.inc"
#include "tu-uhitm-layout.h"
static void callback(void){if(opts[93])longjmp(fixture_jump,1);if(opts[90]&&!callback_depth){callback_depth++;logmsg("reentry:%d;",disguised_as_mon(&monster_pool[0]));if(opts[92]&&!growth){growth=malloc(40000000);logmsg("growth:%d;",growth!=0);}if(opts[94]){object_pool[0].spe=3;monster_pool[0].mhp=17;logmsg("alias_write;");}callback_depth--;}}
void probe_input(const char*s){snprintf(inputbuf,sizeof inputbuf,"%s",s);}
int probe_layout_count(void){return SIZE(uhitm_layout);}const char*probe_layout_name(int i){return uhitm_layout[i].name;}long long probe_layout_value(int i){return uhitm_layout[i].value;}
const char*probe_trace(void){return tracebuf;}const char*probe_buffer(void){return buf;}size_t probe_stack(void){return emscripten_stack_get_current();}
void probe_clear(void){tracebuf[0]=0;buf[0]=0;}void probe_option(int i,int value){opts[i]=value;}void probe_seed(unsigned value){rngstate=value;}
void probe_reset(void){if(growth){free(growth);growth=0;}monst_globals_init();objects_globals_init();memset(opts,0,sizeof opts);memset(object_pool,0,sizeof object_pool);memset(monster_pool,0,sizeof monster_pool);memset(trap_pool,0,sizeof trap_pool);memset(coord_pool,0,sizeof coord_pool);memset(scalar_pool,0,sizeof scalar_pool);memset(&hmd_pool,0,sizeof hmd_pool);memset(&mhm_pool,0,sizeof mhm_pool);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&svl,0,sizeof svl);memset(&svm,0,sizeof svm);object_next=4;allocation_count=0;callback_depth=0;rngstate=1;tracebuf[0]=0;buf[0]=0;origin[0]=0;strcpy(inputbuf,"testing");u.ux=10;u.uy=10;u.dx=1;u.ulevel=10;u.uhp=100;u.uhpmax=100;u.mh=u.mhmax=100;u.uhunger=1000;u.umonnum=u.umonster=PM_HUMAN;u.acurr.a[A_STR]=u.acurr.a[A_DEX]=u.acurr.a[A_CON]=18;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urace.mnum=PM_HUMAN;uwep=&object_pool[0];uswapwep=ublindf=uarmg=uarmh=uarm=uarmc=uarmf=uarmu=uarms=uamul=uleft=uright=uball=0;svl.level.monlist=0;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=100;for(int i=0;i<64;i++){object_pool[i].otyp=DAGGER;object_pool[i].oclass=WEAPON_CLASS;object_pool[i].quan=1;object_pool[i].o_id=i+1;object_pool[i].spe=1;object_pool[i].where=OBJ_INVENT;}for(int i=0;i<16;i++){monster_pool[i].data=&mons[PM_HUMAN];monster_pool[i].mhp=20;monster_pool[i].mhpmax=30;monster_pool[i].m_lev=5;monster_pool[i].mx=11+i;monster_pool[i].my=10;monster_pool[i].m_id=i+1;monster_pool[i].cham=NON_PM;monster_pool[i].mcansee=monster_pool[i].mcanmove=1;}static seenV rows[ROWNO][COLNO];static seenV*rowptr[ROWNO];for(int y=0;y<ROWNO;y++){rowptr[y]=rows[y];for(int x=0;x<COLNO;x++){rows[y][x]=IN_SIGHT|COULD_SEE;svl.level.locations[x][y].typ=ROOM;}}gv.viz_array=rowptr;coord_pool[0].x=10;coord_pool[0].y=10;scalar_pool[0]=1;hmd_pool.dmg=7;hmd_pool.mdat=&mons[PM_HUMAN];hmd_pool.retval=TRUE;hmd_pool.get_dmg_bonus=TRUE;mhm_pool.damage=7;mhm_pool.hitflags=M_ATTK_HIT;mhm_pool.dieroll=10;attack_pool[0]=(struct attack){AT_CLAW,AD_PHYS,1,4};gn.nomovemsg=0;gn.notonhead=0;gv.vis=0;gt.twohits=0;go.override_confirmation=0;go.occupation=0;windowprocs.win_display_nhwindow=window_display;windowprocs.win_delay_output=window_delay;}
void probe_object(int i,int typ,int spe,int flags_,unsigned oid,long quantity){struct obj*o=&object_pool[i];o->otyp=typ;o->oclass=objects[typ].oc_class;o->spe=spe;o->blessed=flags_&1;o->cursed=(flags_>>1)&1;o->oeroded=(flags_>>2)&3;o->oeroded2=(flags_>>4)&3;o->dknown=(flags_>>6)&1;o->o_id=oid;o->quan=quantity;}
void probe_global(int which,long value){switch(which){case 0:u.uprops[BLINDED].intrinsic=value;break;case 1:flags.verbose=value;break;case 2:flags.debug=value;break;case 3:HConfusion=value;break;case 4:u.uprops[HALLUC].intrinsic=value;break;case 5:u.uprops[HALF_PHDAM].intrinsic=value;break;case 6:u.uinwater=value;break;case 7:u.uswallow=value;u.ustuck=value?&monster_pool[0]:0;break;}}
void*probe_pointer(int kind){switch(kind){case 0:return &object_pool[0];case 1:return &monster_pool[0];case 2:return &attack_pool[0];case 3:return &scalar_pool[0];case 4:return &hmd_pool;case 5:return &mhm_pool;case 6:return (void*)gn.nomovemsg;case 7:return &monster_pool[1];case 8:return &object_pool[1];case 9:return &attack_pool[1];default:return 0;}}
const char*probe_snapshot(void){char*p=snapshotbuf;p+=sprintf(p,"rng:%u;alloc:%d;prop:%ld,%ld,%ld;hero:%d,%d,%d,%d;hmd:%d,%d,%d;hit:%d,%d,%d,%d,%d;nomsg:%s;",rngstate,allocation_count,HConfusion,HStun,HBlinded,u.uhp,u.mh,u.ux,u.uy,hmd_pool.dmg,hmd_pool.retval,hmd_pool.doreturn,mhm_pool.damage,mhm_pool.hitflags,mhm_pool.done,mhm_pool.permdmg,mhm_pool.specialdmg,gn.nomovemsg?gn.nomovemsg:"");for(int i=0;i<64;i++){struct obj*o=&object_pool[i];p+=sprintf(p,"o:%d,%d,%u,%u,%u,%u,%u,%u,%ld,%ld,%ld;",o->otyp,o->spe,o->blessed,o->cursed,o->oeroded,o->oeroded2,o->in_use,o->lamplit,o->quan,o->age,o->owornmask);p+=sprintf(p,"nobj:%d;",id(o->nobj));}for(int i=0;i<16;i++){struct monst*m=&monster_pool[i];p+=sprintf(p,"m:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%ld;",m->mhp,m->mhpmax,m->mtame,m->mpeaceful,m->msleeping,m->mundetected,m->mcansee,m->mcanmove,m->mblinded,m->mfrozen,m->mconf,m->mstrategy);p+=sprintf(p,"minvent:%d;",id(m->minvent));}p+=sprintf(p,"ref:%d;mdat:%d;reason:%s;",scalar_pool[0],id(hmd_pool.mdat),gm.multi_reason?gm.multi_reason:"");return snapshotbuf;}
void probe_property(int n,long intrinsic,long extrinsic,long blocked){u.uprops[n].intrinsic=intrinsic;u.uprops[n].extrinsic=extrinsic;u.uprops[n].blocked=blocked;}
void probe_scene(int which,int a,int b){switch(which){case 0:u.dx=a;u.dy=b;break;case 1:attack_pool[0].aatyp=a;attack_pool[0].adtyp=b;break;case 2:monster_pool[0].data=&mons[a];break;case 3:monster_pool[1].data=&mons[a];break;case 4:u.umonnum=a;gy.youmonst.data=&mons[a];break;case 5:monster_pool[0].minvent=a?&object_pool[1]:0;object_pool[1].nobj=a>1?&object_pool[2]:0;break;case 6:monster_pool[0].mtame=a;monster_pool[0].mpeaceful=b;break;case 7:object_pool[0].corpsenm=a;break;case 8:object_pool[0].opoisoned=a;object_pool[0].greased=b;break;case 9:svl.level.monsters[11][10]=a?&monster_pool[0]:0;break;case 10:hmd_pool.thrown=a;hmd_pool.dmg=b;break;case 11:monster_pool[0].mcan=a;monster_pool[1].mcan=b;break;case 12:uarmh=a?&object_pool[1]:0;uarmg=b?&object_pool[2]:0;break;case 13:uwep=a?&object_pool[0]:0;uswapwep=b?&object_pool[1]:0;u.twoweap=b;break;case 15:object_pool[0].oartifact=a;monster_pool[0].mhp=b;break;case 18:monster_pool[0].minvent=&object_pool[1];object_pool[1].nobj=&object_pool[2];object_pool[1].owornmask=W_ARM;object_pool[1].otyp=LEATHER_ARMOR;object_pool[1].oclass=ARMOR_CLASS;object_pool[2].nobj=0;break;case 17:object_pool[0].owt=(unsigned)a;break;case 16:uarm=a?&object_pool[1]:0;uarmh=b?&object_pool[2]:0;break;case 14:svl.level.locations[11][10].glyph=a;monster_pool[0].m_ap_type=b;break;}}

int probe_callback_identity(int i){return teleport_uhitm_callback(i)==(i==0?(void*)Finish_digestion:i==1?(void*)rn2_on_display_rng:(void*)xname);}
int probe_callback_action(int i){void*p=teleport_uhitm_callback(i);if(i==0)return((int(*)(void))p)();if(i==1)return((int(*)(int))p)(7);const char*s=((char*(*)(struct obj*))p)(&object_pool[0]);snprintf(buf,sizeof buf,"%s",s);return(int)strlen(s);}
int probe_retained(int op){if(op==0)return ga.afternmv==Finish_digestion;if(op==1)return ga.afternmv?ga.afternmv():-1;if(op==2&&gn.nomovemsg){((char*)gn.nomovemsg)[0]='X';return 1;}return gn.nomovemsg!=NULL;}

long long probe_action(int op,int a,int b,int c){long long result=0;if(setjmp(fixture_jump))return-999;switch(op){
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 0:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=mhitm_mgc_atk_negated((opts[40]==1?&gy.youmonst:&monster_pool[1]),(opts[40]==2?&gy.youmonst:&monster_pool[0]),a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 1:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];dynamic_multi_reason((opts[40]==2?&gy.youmonst:&monster_pool[0]),inputbuf,a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 2:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];erode_armor((opts[40]==2?&gy.youmonst:&monster_pool[0]),a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 3:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=attack_checks((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 4:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];check_caitiff((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 5:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mon_maybe_unparalyze((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 6:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=find_roll_to_hit((opts[40]==2?&gy.youmonst:&monster_pool[0]),a,&object_pool[0],&scalar_pool[0],&scalar_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 7:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=force_attack((opts[40]==2?&gy.youmonst:&monster_pool[0]),a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 8:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=do_attack((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 9:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=known_hitum((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0],&scalar_pool[0],a,b,&attack_pool[0],c);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 10:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=hitum_cleave((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 11:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=double_punch();logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 12:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=hitum((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 13:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=hmon((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0],a,b);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 14:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_barehands(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 15:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_weapon_ranged(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 16:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=backstabbable((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 17:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_weapon_melee(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 18:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_weapon(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 19:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_potion(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 20:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_misc_obj(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 21:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_do_hit(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 22:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_dmg_recalc(&hmd_pool,&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 23:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_poison(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 24:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_jousting(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 25:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_stagger(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 26:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_pet(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 27:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_splitmon(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 28:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_msg_hit(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 29:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_msg_silver(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 30:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];hmon_hitmon_msg_lightobj(&hmd_pool,(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 31:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=hmon_hitmon((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0],a,b);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 32:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=mhurtle_to_doom((opts[40]==2?&gy.youmonst:&monster_pool[0]),a,&pm);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 33:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];first_weapon_hit(&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 34:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=shade_aware(&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 35:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=shade_miss((opts[40]==1?&gy.youmonst:&monster_pool[1]),(opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0],a,b);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 36:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=m_slips_free((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 37:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=joust((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 38:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];demonpet();logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 39:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=theft_petrifies(&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 40:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];steal_it((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 41:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_rust((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 42:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_corr((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 43:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_dcay((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 44:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_dren((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 45:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_drli((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 46:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_fire((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 47:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_cold((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 48:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_elec((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 49:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_acid((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 50:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_sgld((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 51:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_tlpt((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 52:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_blnd((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 53:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_curs((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 54:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_really_poison((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 55:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_drst((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 56:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_drin((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 57:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_stck((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 58:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_wrap((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 59:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_plys((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 60:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_slee((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 61:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_slim((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 62:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_ench((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 63:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_slow((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 64:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_conf((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 65:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_poly((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 66:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_famn((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 67:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_pest((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 68:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_deth((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 69:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_halu((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 70:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=do_stone_u((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 71:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];do_stone_mon((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 72:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_phys((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 73:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_ston((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 74:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_were((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 75:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_heal((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 76:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_stun((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 77:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_legs((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 78:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_dgst((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 79:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_samu((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 80:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_dise((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 81:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_sedu((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 82:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_ad_ssex((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 83:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];mhitm_adtyping((opts[40]==1?&gy.youmonst:&monster_pool[1]),&attack_pool[0],(opts[40]==2?&gy.youmonst:&monster_pool[0]),&mhm_pool);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 84:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=damageum((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0],a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 85:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=explum((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 86:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];start_engulf((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 87:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];end_engulf();logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 88:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=gulpum((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 89:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];missum((opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0],a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 90:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=m_is_steadfast((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 91:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=mhitm_knockback((opts[40]==1?&gy.youmonst:&monster_pool[1]),(opts[40]==2?&gy.youmonst:&monster_pool[0]),&attack_pool[0],&scalar_pool[0],a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 92:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=hmonas((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 93:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=passive((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0],a,b,c,c);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 94:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];passive_obj((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0],&attack_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 95:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];that_is_a_mimic((opts[40]==2?&gy.youmonst:&monster_pool[0]),a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 96:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];stumble_onto_mimic((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 97:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=disguised_as_non_mon((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 98:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=disguised_as_mon((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#ifndef TELEPORT_PRODUCTION_PROJECTION
case 99:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];nohandglow((opts[40]==2?&gy.youmonst:&monster_pool[0]));logmsg("out:%d,%d;",id(sobj),id(pm));break;}
#endif
case 100:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];result=flash_hits_mon((opts[40]==2?&gy.youmonst:&monster_pool[0]),&object_pool[0]);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
case 101:{struct obj*sobj=&object_pool[0];struct permonst*pm=&mons[PM_HUMAN];light_hits_gremlin((opts[40]==2?&gy.youmonst:&monster_pool[0]),a);logmsg("out:%d,%d;",id(sobj),id(pm));break;}
default:abort();}return result;}

void probe_record_prepare(void){object_pool[0].where=OBJ_FREE;object_pool[0].quan=3;object_pool[0].nobj=0;uarm=&object_pool[1];uarmh=&object_pool[1];}
long long probe_record(int i){record_result=0;switch(i){
case 0:{struct obj *p=addinv(&object_pool[0]);record_result=p;return p?p->otyp:-777;}
case 1:{struct obj *p=carrying(DAGGER);record_result=p;return p?p->otyp:-777;}
case 2:{struct monst *p=clone_mon(&monster_pool[0],11,10);record_result=p;return p?p->mhp:-777;}
case 3:{struct monst *p=cloneu();record_result=p;return p?p->mhp:-777;}
case 4:{struct attack *p=dmgtype_fromattack(&mons[PM_HUMAN],AD_PHYS,AT_CLAW);record_result=p;return p?p->adtyp:-777;}
case 5:{struct obj *p=findgold(&object_pool[0]);record_result=p;return p?p->otyp:-777;}
case 6:{struct attack *p=getmattk(&monster_pool[0],&monster_pool[1],0,&scalar_pool[0],&attack_pool[1]);record_result=p;return p?p->adtyp:-777;}
case 7:{struct permonst *p=grow_up(&monster_pool[0],&monster_pool[1]);record_result=p;return p?p->pmidx:-777;}
case 8:{struct obj *p=hold_another_object(&object_pool[0],"","","");record_result=p;return p?p->otyp:-777;}
case 9:{struct obj *p=m_carrying(&monster_pool[0],DAGGER);record_result=p;return p?p->otyp:-777;}
case 10:{struct monst *p=makemon(&mons[PM_HUMAN],11,10,0);record_result=p;return p?p->mhp:-777;}
case 11:{struct obj *p=merge_choice(&object_pool[0],&object_pool[1]);record_result=p;return p?p->otyp:-777;}
case 12:{struct obj *p=mksobj(DAGGER,TRUE,FALSE);record_result=p;return p?p->otyp:-777;}
case 13:{struct obj *p=mlifesaver(&monster_pool[0]);record_result=p;return p?p->otyp:-777;}
case 14:{struct obj *p=some_armor(&monster_pool[0]);record_result=p;return p?p->otyp:-777;}
case 15:{struct monst *p=split_mon(&monster_pool[0],&monster_pool[1]);record_result=p;return p?p->mhp:-777;}
case 16:{struct obj *p=splitobj(&object_pool[0],1L);record_result=p;return p?p->otyp:-777;}
case 17:{struct obj *p=which_armor(&monster_pool[0],W_ARM);record_result=p;return p?p->otyp:-777;}
default:abort();}}
void*probe_record_pointer(void){return record_result;}
void probe_record_write(int i,int n){if(!record_result)return;switch(i){
case 0:((struct obj*)record_result)->spe=n;break;
case 1:((struct obj*)record_result)->spe=n;break;
case 2:((struct monst*)record_result)->mhp=n;break;
case 3:((struct monst*)record_result)->mhp=n;break;
case 4:((struct attack*)record_result)->adtyp=n;break;
case 5:((struct obj*)record_result)->spe=n;break;
case 6:((struct attack*)record_result)->adtyp=n;break;
case 8:((struct obj*)record_result)->spe=n;break;
case 9:((struct obj*)record_result)->spe=n;break;
case 10:((struct monst*)record_result)->mhp=n;break;
case 11:((struct obj*)record_result)->spe=n;break;
case 12:((struct obj*)record_result)->spe=n;break;
case 13:((struct obj*)record_result)->spe=n;break;
case 14:((struct obj*)record_result)->spe=n;break;
case 15:((struct monst*)record_result)->mhp=n;break;
case 16:((struct obj*)record_result)->spe=n;break;
case 17:((struct obj*)record_result)->spe=n;break;
default:break;}}
