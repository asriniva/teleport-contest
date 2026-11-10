/* Controlled external world; unchanged original eat.c is the policy oracle. */
#include "hack.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
__typeof__(u)u;__typeof__(svc)svc;__typeof__(svm)svm;__typeof__(svl)svl;__typeof__(gy)gy;__typeof__(gv)gv;__typeof__(gm)gm;__typeof__(gn)gn;__typeof__(gi)gi;__typeof__(gp)gp;__typeof__(gu)gu;__typeof__(svd)svd;__typeof__(flags)flags;__typeof__(iflags)iflags;__typeof__(disp)disp;__typeof__(gs)gs;__typeof__(ge)ge;__typeof__(ga)ga;__typeof__(go)go;__typeof__(gc)gc;__typeof__(gf)gf;__typeof__(svk)svk;const __typeof__(cg)cg={0};const struct c_common_strings c_common_strings={.c_nothing_happens="Nothing happens.",.c_nothing_seems_to_happen="Nothing seems to happen.",.c_Something="Something",.c_something="something",.c_vision_clears="vision clears",.c_You_can_move_again="You can move again.",.c_the_your={"the","your"}};const struct c_color_names c_color_names={.c_black="black",.c_orange="orange",.c_light_blue="light blue",.c_amber="amber",.c_red="red"};
struct obj*uwep,*uarm,*uarmg,*uarmh,*uarmf,*uarmc,*uarmu,*ublindf,*uamul,*uswapwep,*uball,*uchain,*uleft,*uright,*uquiver;struct obj hands_obj;const char ynchars[]="yn";const char ynqchars[]="ynq";void paniclog(const char*a,const char*b){(void)a;(void)b;}
const struct Gender genders[4]={{.his="his",.he="he",.him="him"},{.his="her",.he="she",.him="her"},{.his="its",.he="it",.him="it"},{.his="their",.he="they",.him="them"}};
static struct monst*monsters[16];static struct obj*nodes[64];static seenV vision[ROWNO][COLNO],*visionrows[ROWNO];static int opts[128],rolls[4096],nr,ri,nmon,nobj;static unsigned seed;static long ret[256];static char tracebuf[1048576],caller[256];static void*growth;static long cells[8];static unsigned char fake_bytes[sizeof(struct obj)];static int fake_calls;static struct trap fixture_trap;static struct kinfo killer_record;static stairway stairs;
static int mid(struct monst*m){int i;if(!m)return-1;if(m==&gy.youmonst)return-2;for(i=0;i<nmon;i++)if(m==monsters[i])return i;return-3;}static int oid(struct obj*o){int i;if(!o)return-1;if(o==&hands_obj)return-2;for(i=0;i<nobj;i++)if(o==nodes[i])return i;return-3;}
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static void callback(int n){if(opts[120]==n&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("grow:%d;",n);}if(opts[121]==n){u.uprops[HALF_PHDAM].intrinsic^=FROMOUTSIDE;logmsg("fliphalf;");}if(opts[122]==n){nodes[0]->blessed=!nodes[0]->blessed;logmsg("flipbless;");}if(opts[123]==n)logmsg("live_ustuck:%d;",mid(u.ustuck));if(opts[125]==n&&!opts[126]&&nmon>1){opts[126]=1;gethungry();logmsg("reenter:%d;",n);}}
void panic(const char*f,...){va_list ap;va_start(ap,f);vfprintf(stderr,f,ap);va_end(ap);abort();}
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char*f,int line,const char*fn){snprintf(caller,sizeof caller,"%s:%d:%s",f,line,fn);}
static int draw(int n){unsigned v;if(n<=0)panic("bad rng %d",n);seed=seed*1664525U+1013904223U;v=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;logmsg("rng:%d:%u@%s;",n,v,caller);callback(1);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}int(rnl)(int n){return draw(n);}int(d)(int n,int z){int t=0;while(n--)t+=draw(z)+1;return t;}
static void display(winid w,boolean b){logmsg("display:%d:%d;",w,b);}static char yn(const char*q,const char*c,char def){logmsg("yn:%s:%s:%d;",q,c,def);return opts[10]?opts[10]:'n';}__typeof__(windowprocs)windowprocs={.win_display_nhwindow=display,.win_yn_function=yn};winid WIN_MESSAGE=1;
void pline(const char*f,...){va_list ap;logmsg("pline:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void pline_The(const char*f,...){va_list ap;logmsg("pline_The:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You(const char*f,...){va_list ap;logmsg("You:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You_feel(const char*f,...){va_list ap;logmsg("You_feel:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void Your(const char*f,...){va_list ap;logmsg("Your:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void verbalize(const char*f,...){va_list ap;logmsg("verbalize:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void impossible(const char*f,...){va_list ap;logmsg("impossible:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void livelog_printf(long category,const char*f,...){va_list ap;logmsg("livelog:%ld:",category);va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}boolean unconscious(void){return opts[2];}boolean has_ceiling(d_level*l){return opts[4];}schar acurr(int i){logmsg("attribute:%d;",i);return u.acurr.a[i];}int pronoun_gender(struct monst*m,unsigned flags){return opts[6];}boolean is_pool(coordxy x,coordxy y){return isok(x,y)&&(levl[x][y].typ==POOL||levl[x][y].typ==MOAT||levl[x][y].typ==WATER);}int bcsign(struct obj*o){return o->blessed?1:o->cursed?-1:0;}
char yn_function(const char*q,const char*c,char d,boolean add){logmsg("history:%d;",add);return yn(q,c,d);}
struct obj*getobj(const char*q,int(*select)(struct obj*),unsigned flags){int i;logmsg("getobj:%s:%u;",q,flags);for(i=0;i<nobj;i++)logmsg("select:%d:%d;",i,select(nodes[i]));callback(2);return opts[11]==-2?&hands_obj:opts[11]>=0&&opts[11]<nobj?nodes[opts[11]]:NULL;}
char*short_oname(struct obj*o,char*(*one)(struct obj*),char*(*two)(struct obj*),unsigned len){logmsg("short:%d:%u:%d:%d;",oid(o),len,one==doname,two==thesimpleoname);return "short object";}
void docall(struct obj*o){logmsg("docall:%d:;",oid(o));memcpy(fake_bytes,o,sizeof *o);fake_calls++;}
void get_level(d_level*l,int n){logmsg("getlevel:%d;",n);l->dnum=1;l->dlevel=n;}void assign_level(d_level*to,d_level*from){*to=*from;}
int Mgender(struct monst * a0){logmsg("Mgender:%d:;",mid(a0));callback(20+0);return (int)ret[0];}
char * Monnam(struct monst * a0){logmsg("Monnam:%d:;",mid(a0));callback(20+1);return "Monnam";}
boolean Resists_Elem(struct monst * a0,int a1){logmsg("Resists_Elem:%d:%d:;",mid(a0),(int)a1);callback(20+2);return (boolean)ret[2];}
void Ring_gone(struct obj * a0){logmsg("Ring_gone:%d:;",oid(a0));callback(20+3);}
char * Tobjnam(struct obj * a0,const char * a1){logmsg("Tobjnam:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+4);return "Tobjnam";}
schar acurrstr(void){logmsg("acurrstr:;");callback(20+6);return (schar)ret[6];}
struct obj * addinv_nomerge(struct obj * a0){logmsg("addinv_nomerge:%d:;",oid(a0));callback(20+7);return ret[7]>=0&&ret[7]<nobj?nodes[ret[7]]:NULL;}
void adjalign(int a0){logmsg("adjalign:%d:;",(int)a0);callback(20+8);}
boolean adjattrib(int a0,int a1,int a2){logmsg("adjattrib:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+9);return (boolean)ret[9];}
void altar_wrath(coordxy a0,coordxy a1){logmsg("altar_wrath:%d:%d:;",(int)a0,(int)a1);callback(20+10);}
char * an(const char * a0){logmsg("an:%s:;",(a0?a0:"NULL"));callback(20+11);return "an";}
char * ansimpleoname(struct obj * a0){logmsg("ansimpleoname:%d:;",oid(a0));callback(20+12);return "ansimpleoname";}
boolean attacktype(struct permonst * a0,int a1){logmsg("attacktype:%d:%d:;",a0?a0->pmidx:-1,(int)a1);callback(20+13);return (boolean)ret[13];}
struct attack * attacktype_fordmg(struct permonst * a0,int a1,int a2){logmsg("attacktype_fordmg:%d:%d:%d:;",a0?a0->pmidx:-1,(int)a1,(int)a2);callback(20+14);return ret[14]>=0?&mons[PM_HUMAN].mattk[ret[14]%NATTK]:NULL;}
int attrcurse(void){logmsg("attrcurse:;");callback(20+15);return (int)ret[15];}
void b_trapped(const char * a0,int a1){logmsg("b_trapped:%s:%d:;",(a0?a0:"NULL"),(int)a1);callback(20+16);}
const char * body_part(int a0){logmsg("body_part:%d:;",(int)a0);callback(20+17);return "body_part";}
void bot(void){logmsg("bot:;");callback(20+18);}
boolean can_reach_floor(boolean a0){logmsg("can_reach_floor:%d:;",(int)a0);callback(20+19);return (boolean)ret[19];}
int canseemon(struct monst * a0){logmsg("canseemon:%d:;",mid(a0));callback(20+20);return (int)ret[20];}
boolean cantvomit(struct permonst * a0){logmsg("cantvomit:%d:;",a0?a0->pmidx:-1);callback(20+21);return (boolean)ret[21];}
struct obj * carrying(int a0){logmsg("carrying:%d:;",(int)a0);callback(20+22);return ret[22]>=0&&ret[22]<nobj?nodes[ret[22]]:NULL;}
void change_luck(schar a0){logmsg("change_luck:%d:;",(int)a0);callback(20+23);}
void change_sex(void){logmsg("change_sex:;");callback(20+24);}
boolean check_capacity(const char * a0){logmsg("check_capacity:%s:;",(a0?a0:"NULL"));callback(20+25);return (boolean)ret[25];}
char * corpse_xname(struct obj * a0,const char * a1,unsigned int a2){logmsg("corpse_xname:%d:%s:%d:;",oid(a0),(a1?a1:"NULL"),(int)a2);callback(20+26);return "corpse_xname";}
void costly_alteration(struct obj * a0,int a1){logmsg("costly_alteration:%d:%d:;",oid(a0),(int)a1);callback(20+27);}
boolean costly_spot(coordxy a0,coordxy a1){logmsg("costly_spot:%d:%d:;",(int)a0,(int)a1);callback(20+28);return (boolean)ret[28];}
void curs_on_u(void){logmsg("curs_on_u:;");callback(20+29);}
boolean debugcore(const char * a0,boolean a1){logmsg("debugcore:%s:%d:;",(a0?a0:"NULL"),(int)a1);callback(20+30);return (boolean)ret[30];}
boolean defended(struct monst * a0,int a1){logmsg("defended:%d:%d:;",mid(a0),(int)a1);callback(20+31);return (boolean)ret[31];}
void delayed_killer(int a0,int a1,const char * a2){logmsg("delayed_killer:%d:%d:%s:;",(int)a0,(int)a1,(a2?a2:"NULL"));callback(20+32);}
void deltrap(struct trap * a0){logmsg("deltrap:%d:;",a0!=NULL);callback(20+33);}
void dismount_steed(int a0){logmsg("dismount_steed:%d:;",(int)a0);callback(20+34);}
boolean dmgtype(struct permonst * a0,int a1){logmsg("dmgtype:%d:%d:;",a0?a0->pmidx:-1,(int)a1);callback(20+35);return (boolean)ret[35];}
char * doname(struct obj * a0){logmsg("doname:%d:;",oid(a0));callback(20+36);return "doname";}
void done(int a0){logmsg("done:%d:;",(int)a0);callback(20+37);u.uhp=1;u.uprops[LIFESAVED].extrinsic=1;}
int dopotion(struct obj * a0){logmsg("dopotion:%d:;",oid(a0));callback(20+38);return (int)ret[38];}
void dropx(struct obj * a0){logmsg("dropx:%d:;",oid(a0));callback(20+39);}
void dropy(struct obj * a0){logmsg("dropy:%d:;",oid(a0));callback(20+40);}
void encumber_msg(void){logmsg("encumber_msg:;");callback(20+42);}
void end_running(boolean a0){logmsg("end_running:%d:;",(int)a0);callback(20+43);}
void exercise(int a0,boolean a1){logmsg("exercise:%d:%d:;",(int)a0,(int)a1);callback(20+45);}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logmsg("explode:%d:%d:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);callback(20+46);}
void fall_asleep(int a0,boolean a1){logmsg("fall_asleep:%d:%d:;",(int)a0,(int)a1);callback(20+47);}
void feel_cockatrice(struct obj * a0,boolean a1){logmsg("feel_cockatrice:%d:%d:;",oid(a0),(int)a1);callback(20+48);}
const char * fingers_or_gloves(boolean a0){logmsg("fingers_or_gloves:%d:;",(int)a0);callback(20+49);return "fingers_or_gloves";}
void float_up(void){logmsg("float_up:;");callback(20+50);}
void freeinv(struct obj * a0){logmsg("freeinv:%d:;",oid(a0));callback(20+52);}
struct obj * g_at(coordxy a0,coordxy a1){logmsg("g_at:%d:%d:;",(int)a0,(int)a1);callback(20+53);return ret[53]>=0&&ret[53]<nobj?nodes[ret[53]]:NULL;}
void gainstr(struct obj * a0,int a1,boolean a2){logmsg("gainstr:%d:%d:%d:;",oid(a0),(int)a1,(int)a2);callback(20+54);}
const char * hcolor(const char * a0){logmsg("hcolor:%s:;",(a0?a0:"NULL"));callback(20+55);return "hcolor";}
void heal_legs(int a0){logmsg("heal_legs:%d:;",(int)a0);callback(20+56);}
void incr_itimeout(long * a0,int a1){logmsg("incr_itimeout:%d:%d:;",a0!=NULL,(int)a1);callback(20+57);}
int inv_cnt(boolean a0){logmsg("inv_cnt:%d:;",(int)a0);callback(20+58);return (int)ret[58];}
boolean is_flammable(struct obj * a0){logmsg("is_flammable:%d:;",oid(a0));callback(20+59);return (boolean)ret[59];}
boolean is_ice(coordxy a0,coordxy a1){logmsg("is_ice:%d:%d:;",(int)a0,(int)a1);callback(20+60);return (boolean)ret[60];}
boolean is_pool_or_lava(coordxy a0,coordxy a1){logmsg("is_pool_or_lava:%d:%d:;",(int)a0,(int)a1);callback(20+61);return (boolean)ret[61];}
boolean is_rottable(struct obj * a0){logmsg("is_rottable:%d:;",oid(a0));callback(20+62);return (boolean)ret[62];}
char * killer_xname(struct obj * a0){logmsg("killer_xname:%d:;",oid(a0));callback(20+63);return "killer_xname";}
void losehp(int a0,const char * a1,schar a2){logmsg("losehp:%d:%s:%d:;",(int)a0,(a1?a1:"NULL"),(int)a2);callback(20+64);u.uhp-=a0;}
void make_blinded(long a0,boolean a1){logmsg("make_blinded:%ld:%d:;",(long)a0,(int)a1);callback(20+65);}
void make_confused(long a0,boolean a1){logmsg("make_confused:%ld:%d:;",(long)a0,(int)a1);callback(20+66);}
void make_deaf(long a0,boolean a1){logmsg("make_deaf:%ld:%d:;",(long)a0,(int)a1);callback(20+67);}
void make_glib(int a0){logmsg("make_glib:%d:;",(int)a0);callback(20+68);}
boolean make_hallucinated(long a0,boolean a1,long a2){logmsg("make_hallucinated:%ld:%d:%ld:;",(long)a0,(int)a1,(long)a2);callback(20+69);return (boolean)ret[69];}
void make_sick(long a0,const char * a1,boolean a2,int a3){logmsg("make_sick:%ld:%s:%d:%d:;",(long)a0,(a1?a1:"NULL"),(int)a2,(int)a3);callback(20+70);}
void make_slimed(long a0,const char * a1){logmsg("make_slimed:%ld:%s:;",(long)a0,(a1?a1:"NULL"));callback(20+71);}
void make_stoned(long a0,const char * a1,int a2,const char * a3){logmsg("make_stoned:%ld:%s:%d:%s:;",(long)a0,(a1?a1:"NULL"),(int)a2,(a3?a3:"NULL"));callback(20+72);}
void make_stunned(long a0,boolean a1){logmsg("make_stunned:%ld:%d:;",(long)a0,(int)a1);callback(20+73);}
void make_vomiting(long a0,boolean a1){logmsg("make_vomiting:%ld:%d:;",(long)a0,(int)a1);callback(20+74);}
char * makeplural(const char * a0){logmsg("makeplural:%s:;",(a0?a0:"NULL"));callback(20+75);return "makeplural";}
void melt_ice(coordxy a0,coordxy a1,const char * a2){logmsg("melt_ice:%d:%d:%s:;",(int)a0,(int)a1,(a2?a2:"NULL"));callback(20+76);}
struct obj * mksobj(int a0,boolean a1,boolean a2){logmsg("mksobj:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+77);return ret[77]>=0&&ret[77]<nobj?nodes[ret[77]]:NULL;}
char * mon_nam(struct monst * a0){logmsg("mon_nam:%d:;",mid(a0));callback(20+78);return "mon_nam";}
void mondied(struct monst * a0){logmsg("mondied:%d:;",mid(a0));callback(20+79);}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){logmsg("monflee:%d:%d:%d:%d:;",mid(a0),(int)a1,(int)a2,(int)a3);callback(20+80);}
void monstone(struct monst * a0){logmsg("monstone:%d:;",mid(a0));callback(20+81);}
void more_experienced(int a0,int a1){logmsg("more_experienced:%d:%d:;",(int)a0,(int)a1);callback(20+82);}
int near_capacity(void){logmsg("near_capacity:;");callback(20+83);return (int)ret[83];}
void newexplevel(void){logmsg("newexplevel:;");callback(20+84);}
void newsym(coordxy a0,coordxy a1){logmsg("newsym:%d:%d:;",(int)a0,(int)a1);callback(20+85);}
void nomul(int a0){logmsg("nomul:%d:;",(int)a0);callback(20+86);gm.multi=a0;}
void o_unleash(struct obj * a0){logmsg("o_unleash:%d:;",oid(a0));callback(20+87);}
void obj_extract_self(struct obj * a0){logmsg("obj_extract_self:%d:;",oid(a0));callback(20+88);}
boolean obj_here(struct obj * a0,coordxy a1,coordxy a2){logmsg("obj_here:%d:%d:%d:;",oid(a0),(int)a1,(int)a2);callback(20+89);return (boolean)ret[89];}
boolean obj_is_pname(struct obj * a0){logmsg("obj_is_pname:%d:;",oid(a0));callback(20+90);return (boolean)ret[90];}
void obj_stop_timers(struct obj * a0){logmsg("obj_stop_timers:%d:;",oid(a0));callback(20+91);}
boolean objdescr_is(struct obj * a0,const char * a1){logmsg("objdescr_is:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+92);return (boolean)ret[92];}
void observe_object(struct obj * a0){logmsg("observe_object:%d:;",oid(a0));callback(20+93);}
boolean olfaction(struct permonst * a0){logmsg("olfaction:%d:;",a0?a0->pmidx:-1);callback(20+94);return (boolean)ret[94];}
char * otense(struct obj * a0,const char * a1){logmsg("otense:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+95);return "otense";}
void outrumor(int a0,int a1){logmsg("outrumor:%d:%d:;",(int)a0,(int)a1);callback(20+96);}
long peek_at_iced_corpse_age(struct obj * a0){logmsg("peek_at_iced_corpse_age:%d:;",oid(a0));callback(20+98);return (long)ret[98];}
void pluslvl(boolean a0){logmsg("pluslvl:%d:;",(int)a0);callback(20+99);u.ulevel++;}
int pm_to_cham(int a0){logmsg("pm_to_cham:%d:;",(int)a0);callback(20+100);return (int)ret[100];}
const char * pmname(struct permonst * a0,int a1){logmsg("pmname:%d:%d:;",a0?a0->pmidx:-1,(int)a1);callback(20+101);return "pmname";}
void poison_strdmg(int a0,int a1,const char * a2,schar a3){logmsg("poison_strdmg:%d:%d:%s:%d:;",(int)a0,(int)a1,(a2?a2:"NULL"),(int)a3);callback(20+102);}
boolean poly_when_stoned(struct permonst * a0){logmsg("poly_when_stoned:%d:;",a0?a0->pmidx:-1);callback(20+103);return (boolean)ret[103];}
int polymon(int a0){logmsg("polymon:%d:;",(int)a0);callback(20+104);return (int)ret[104];}
void polyself(int a0){logmsg("polyself:%d:;",(int)a0);callback(20+105);if(opts[124]){u.umonnum=opts[124];gy.youmonst.data=&mons[opts[124]];}}
void rehumanize(void){logmsg("rehumanize:;");callback(20+106);}
void remove_worn_item(struct obj * a0,boolean a1){logmsg("remove_worn_item:%d:%d:;",oid(a0),(int)a1);callback(20+107);}
void rescham(void){logmsg("rescham:;");callback(20+108);}
void reset_utrap(boolean a0){logmsg("reset_utrap:%d:;",(int)a0);callback(20+109);}
void retouch_equipment(int a0){logmsg("retouch_equipment:%d:;",(int)a0);callback(20+110);}
boolean revive_corpse(struct obj * a0){logmsg("revive_corpse:%d:;",oid(a0));callback(20+111);return (boolean)ret[111];}
char * rndmonnam(char * a0){logmsg("rndmonnam:%s:;",(a0?a0:"NULL"));callback(20+112);return "rndmonnam";}
int rounddiv(long a0,int a1){logmsg("rounddiv:%ld:%d:;",(long)a0,(int)a1);callback(20+113);return (int)ret[113];}
void sa_victual(volatile struct victual_info * a0){logmsg("sa_victual:%d:;",a0!=NULL);callback(20+114);}
boolean same_race(struct permonst * a0,struct permonst * a1){logmsg("same_race:%d:%d:;",a0?a0->pmidx:-1,a1?a1->pmidx:-1);callback(20+115);return (boolean)ret[115];}
void see_monsters(void){logmsg("see_monsters:;");callback(20+116);}
void self_invis_message(void){logmsg("self_invis_message:;");callback(20+117);}
void selftouch(const char * a0){logmsg("selftouch:%s:;",(a0?a0:"NULL"));callback(20+118);}
void sellobj_state(int a0){logmsg("sellobj_state:%d:;",(int)a0);callback(20+119);}
void set_bknown(struct obj * a0,unsigned int a1){logmsg("set_bknown:%d:%d:;",oid(a0),(int)a1);callback(20+120);}
void set_itimeout(long * a0,long a1){logmsg("set_itimeout:%d:%ld:;",a0!=NULL,(long)a1);callback(20+121);*a0=(*a0 & ~TIMEOUT)|(a1 & TIMEOUT);}
void set_mimic_blocking(void){logmsg("set_mimic_blocking:;");callback(20+122);}
void set_ulycn(int a0){logmsg("set_ulycn:%d:;",(int)a0);callback(20+123);u.ulycn=a0;}
void setuhpmax(int a0,boolean a1){logmsg("setuhpmax:%d:%d:;",(int)a0,(int)a1);callback(20+124);}
struct obj * splitobj(struct obj * a0,long a1){logmsg("splitobj:%d:%ld:;",oid(a0),(long)a1);callback(20+125);return ret[125]>=0&&ret[125]<nobj?nodes[ret[125]]:NULL;}
void stackobj(struct obj * a0){logmsg("stackobj:%d:;",oid(a0));callback(20+126);}
int still_chewing(coordxy a0,coordxy a1){logmsg("still_chewing:%d:%d:;",(int)a0,(int)a1);callback(20+127);return (int)ret[127];}
void stop_occupation(void){logmsg("stop_occupation:;");callback(20+128);}
const char * surface(coordxy a0,coordxy a1){logmsg("surface:%d:%d:;",(int)a0,(int)a1);callback(20+132);return "surface";}
struct trap * t_at(coordxy a0,coordxy a1){logmsg("t_at:%d:%d:;",(int)a0,(int)a1);callback(20+133);return opts[36]?&fixture_trap:NULL;}
char * the(const char * a0){logmsg("the:%s:;",(a0?a0:"NULL"));callback(20+134);return "the";}
boolean the_unique_pm(struct permonst * a0){logmsg("the_unique_pm:%d:;",a0?a0->pmidx:-1);callback(20+135);return (boolean)ret[135];}
boolean tinnable(struct obj * a0){logmsg("tinnable:%d:;",oid(a0));callback(20+136);return (boolean)ret[136];}
void toggle_displacement(struct obj * a0,long a1,boolean a2){logmsg("toggle_displacement:%d:%ld:%d:;",oid(a0),(long)a1,(int)a2);callback(20+137);}
int touch_artifact(struct obj * a0,struct monst * a1){logmsg("touch_artifact:%d:%d:;",oid(a0),mid(a1));callback(20+138);return (int)ret[138];}
void trycall(struct obj * a0){logmsg("trycall:%d:;",oid(a0));callback(20+139);}
schar uasmon_maxStr(void){logmsg("uasmon_maxStr:;");callback(20+140);return (schar)ret[140];}
void ubreatheu(struct attack * a0){logmsg("ubreatheu:%d:;",a0!=NULL);callback(20+141);}
boolean undiscovered_artifact(xint16 a0){logmsg("undiscovered_artifact:%d:;",(int)a0);callback(20+142);return (boolean)ret[142];}
void unmul(const char * a0){logmsg("unmul:%s:;",(a0?a0:"NULL"));callback(20+143);}
void unpunish(void){logmsg("unpunish:;");callback(20+144);}
void uqwepgone(void){logmsg("uqwepgone:;");callback(20+145);}
void useup(struct obj * a0){logmsg("useup:%d:;",oid(a0));callback(20+146);}
void useupall(struct obj * a0){logmsg("useupall:%d:;",oid(a0));callback(20+147);}
void useupf(struct obj * a0,long a1){logmsg("useupf:%d:%ld:;",oid(a0),(long)a1);callback(20+148);}
void uswapwepgone(void){logmsg("uswapwepgone:;");callback(20+149);}
void uwepgone(void){logmsg("uwepgone:;");callback(20+150);}
void vault_gd_watching(unsigned int a0){logmsg("vault_gd_watching:%d:;",(int)a0);callback(20+151);}
int weight(struct obj * a0){logmsg("weight:%d:;",oid(a0));callback(20+152);return (int)ret[152];}
int welded(struct obj * a0){logmsg("welded:%d:;",oid(a0));callback(20+153);return (int)ret[153];}
int were_beastie(int a0){logmsg("were_beastie:%d:;",(int)a0);callback(20+154);return (int)ret[154];}
boolean wield_tool(struct obj * a0,const char * a1){logmsg("wield_tool:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+155);return (boolean)ret[155];}
boolean will_feel_cockatrice(struct obj * a0,boolean a1){logmsg("will_feel_cockatrice:%d:%d:;",oid(a0),(int)a1);callback(20+156);return (boolean)ret[156];}
char * xname(struct obj * a0){logmsg("xname:%d:;",oid(a0));callback(20+157);return "xname";}
char * yobjnam(struct obj * a0,const char * a1){logmsg("yobjnam:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+159);return "yobjnam";}
void you_unwere(boolean a0){logmsg("you_unwere:%d:;",(int)a0);callback(20+160);}

int donull(void){return 0;}
void set_occupation(int(*fn)(void),const char*text,cmdcount_nht time){go.occupation=fn;logmsg("occupation:%s:%ld;",text,time);}
const char*singular(struct obj*o,char*(*fn)(struct obj*)){logmsg("singular:%d:%d;",oid(o),fn==xname);return fn(o);}
char*safe_qbuf(char*buf,const char*prefix,const char*suffix,struct obj*o,char*(*one)(struct obj*),char*(*two)(struct obj*),const char*last){logmsg("safeq:%d:%d:%d;",oid(o),one==doname,two==ansimpleoname);snprintf(buf,QBUFSZ,"%s%s%s",prefix?prefix:"","object",suffix?suffix:"");return buf;}
void iter_mons(void(*fn)(struct monst*)){int i;for(i=0;i<nmon;i++)fn(monsters[i]);}
int retouch_object(struct obj**o,boolean loseit){logmsg("retouch:%d:%d;",oid(*o),loseit);callback(3);if(opts[31]) *o=opts[31]>0?nodes[opts[31]-1]:NULL;return opts[30];}

static int fixture_frees;void teleport_eat_fixture_free(void*p){if(p)fixture_frees++;free(p);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_eat_fixture_free
#include "eat.c"
#undef free
#else
extern int teleport_eat_test_eatmdone(void);
#define eatmdone teleport_eat_test_eatmdone
extern const char * teleport_eat_test_food_xname(struct obj *food, boolean the_pfx);
#define food_xname teleport_eat_test_food_xname
extern void teleport_eat_test_choke(struct obj *food);
#define choke teleport_eat_test_choke
extern void teleport_eat_test_recalc_wt(void);
#define recalc_wt teleport_eat_test_recalc_wt
extern int teleport_eat_test_adj_victual_nutrition(void);
#define adj_victual_nutrition teleport_eat_test_adj_victual_nutrition
extern struct obj * teleport_eat_test_touchfood(struct obj *otmp);
#define touchfood teleport_eat_test_touchfood
extern void teleport_eat_test_do_reset_eat(void);
#define do_reset_eat teleport_eat_test_do_reset_eat
extern int teleport_eat_test_eatfood(void);
#define eatfood teleport_eat_test_eatfood
extern void teleport_eat_test_done_eating(boolean message);
#define done_eating teleport_eat_test_done_eating
extern boolean teleport_eat_test_maybe_cannibal(int pm, boolean allowmsg);
#define maybe_cannibal teleport_eat_test_maybe_cannibal
extern void teleport_eat_test_cprefx(int pm);
#define cprefx teleport_eat_test_cprefx
extern boolean teleport_eat_test_temp_givit(int type, struct permonst *ptr);
#define temp_givit teleport_eat_test_temp_givit
extern void teleport_eat_test_givit(int type, struct permonst *ptr);
#define givit teleport_eat_test_givit
extern void teleport_eat_test_eye_of_newt_buzz(void);
#define eye_of_newt_buzz teleport_eat_test_eye_of_newt_buzz
extern void teleport_eat_test_cpostfx(int pm);
#define cpostfx teleport_eat_test_cpostfx
extern struct obj * teleport_eat_test_costly_tin(int alter_type);
#define costly_tin teleport_eat_test_costly_tin
extern int teleport_eat_test_tin_variety(
    struct obj *obj,
    boolean displ);
#define tin_variety teleport_eat_test_tin_variety
extern void teleport_eat_test_use_up_tin(struct obj *tin);
#define use_up_tin teleport_eat_test_use_up_tin
extern void teleport_eat_test_consume_tin(const char *mesg);
#define consume_tin teleport_eat_test_consume_tin
extern int teleport_eat_test_opentin(void);
#define opentin teleport_eat_test_opentin
extern void teleport_eat_test_start_tin(struct obj *otmp);
#define start_tin teleport_eat_test_start_tin
extern int teleport_eat_test_rottenfood(struct obj *obj);
#define rottenfood teleport_eat_test_rottenfood
extern int teleport_eat_test_eatcorpse(struct obj *otmp);
#define eatcorpse teleport_eat_test_eatcorpse
extern void teleport_eat_test_start_eating(struct obj *otmp, boolean already_partly_eaten);
#define start_eating teleport_eat_test_start_eating
extern void teleport_eat_test_garlic_breath(struct monst *mtmp);
#define garlic_breath teleport_eat_test_garlic_breath
extern boolean teleport_eat_test_fprefx(struct obj *otmp);
#define fprefx teleport_eat_test_fprefx
extern int teleport_eat_test_bounded_increase(int old, int inc, int typ);
#define bounded_increase teleport_eat_test_bounded_increase
extern void teleport_eat_test_accessory_has_effect(struct obj *otmp);
#define accessory_has_effect teleport_eat_test_accessory_has_effect
extern void teleport_eat_test_eataccessory(struct obj *otmp);
#define eataccessory teleport_eat_test_eataccessory
extern void teleport_eat_test_eatspecial(void);
#define eatspecial teleport_eat_test_eatspecial
extern const char * teleport_eat_test_foodword(struct obj *otmp);
#define foodword teleport_eat_test_foodword
extern void teleport_eat_test_fpostfx(struct obj *otmp);
#define fpostfx teleport_eat_test_fpostfx
extern int teleport_eat_test_edibility_prompts(struct obj *otmp);
#define edibility_prompts teleport_eat_test_edibility_prompts
extern int teleport_eat_test_doeat_nonfood(struct obj *otmp);
#define doeat_nonfood teleport_eat_test_doeat_nonfood
extern int teleport_eat_test_tinopen_ok(struct obj *obj);
#define tinopen_ok teleport_eat_test_tinopen_ok
extern int teleport_eat_test_bite(void);
#define bite teleport_eat_test_bite
extern int teleport_eat_test_unfaint(void);
#define unfaint teleport_eat_test_unfaint
extern int teleport_eat_test_eat_ok(struct obj *obj);
#define eat_ok teleport_eat_test_eat_ok
extern int teleport_eat_test_offer_ok(struct obj *obj);
#define offer_ok teleport_eat_test_offer_ok
extern int teleport_eat_test_tin_ok(struct obj *obj);
#define tin_ok teleport_eat_test_tin_ok
#endif
#include "tu-eat-layout.h"

static struct monst*actor(long i){return i==-2?&gy.youmonst:i>=0&&i<nmon?monsters[i]:NULL;}static struct obj*item(long i){return i==-2?&hands_obj:i>=0&&i<nobj?nodes[i]:NULL;}static char resultbuf[BUFSZ];static struct monst*moncell;
void probe_reset(unsigned initial){int i,x,y;for(i=0;i<nobj;i++)free(nodes[i]);for(i=0;i<nmon;i++)free(monsters[i]);if(growth)free(growth);growth=NULL;nmon=nobj=nr=ri=0;seed=initial;memset(nodes,0,sizeof nodes);memset(monsters,0,sizeof monsters);memset(opts,0,sizeof opts);memset(ret,0,sizeof ret);memset(cells,0,sizeof cells);memset(fake_bytes,0,sizeof fake_bytes);fake_calls=0;fixture_frees=0;memset(&u,0,sizeof u);memset(&svc,0,sizeof svc);memset(&svm,0,sizeof svm);memset(&svl,0,sizeof svl);memset(&gy,0,sizeof gy);memset(&gv,0,sizeof gv);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&gi,0,sizeof gi);memset(&gp,0,sizeof gp);memset(&gu,0,sizeof gu);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&hands_obj,0,sizeof hands_obj);memset(&killer_record,0,sizeof killer_record);moncell=NULL;memset(&ge,0,sizeof ge);memset(&ga,0,sizeof ga);memset(&go,0,sizeof go);memset(&gc,0,sizeof gc);memset(&gf,0,sizeof gf);memset(&svk,0,sizeof svk);objects_globals_init();monst_globals_init();for(i=0;i<NUM_OBJECTS;i++)objects[i].oc_name_idx=objects[i].oc_descr_idx=i;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;vision[y][x]=IN_SIGHT|COULD_SEE;}for(y=0;y<ROWNO;y++)visionrows[y]=vision[y];gv.viz_array=visionrows;u.ux=10;u.uy=10;u.uz.dnum=1;u.uz.dlevel=2;u.uhp=50;u.uhpmax=100;u.uen=30;u.uenmax=50;u.mh=50;u.mhmax=100;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;u.ulevel=10;u.ulevelmax=15;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=gy.youmonst.mhpmax=100;gy.youmonst.mcansee=gy.youmonst.mcanmove=1;for(i=0;i<A_MAX;i++){u.acurr.a[i]=10;u.amax.a[i]=15;gu.urace.attrmax[i]=18;gu.urace.attrmin[i]=3;}u.uhunger=900;u.uhs=NOT_HUNGRY;svm.moves=100;gu.urace.mnum=PM_HUMAN;gu.urace.selfmask=M2_HUMAN;flags.verbose=1;opts[0]=1;opts[4]=1;opts[11]=-1;opts[120]=opts[121]=opts[122]=-1;uwep=uarm=uarmg=uarmh=uarmf=uarmc=uarmu=ublindf=uamul=uswapwep=uball=uchain=NULL;strcpy(resultbuf,"rotten");tracebuf[0]=caller[0]=0;opts[30]=1;
ret[1]=-1;ret[4]=-1;ret[7]=-1;ret[11]=-1;ret[12]=-1;ret[14]=-1;ret[17]=-1;ret[22]=-1;ret[26]=-1;ret[36]=-1;ret[41]=-1;ret[44]=-1;ret[49]=-1;ret[51]=-1;ret[53]=-1;ret[55]=-1;ret[63]=-1;ret[75]=-1;ret[77]=-1;ret[78]=-1;ret[95]=-1;ret[101]=-1;ret[112]=-1;ret[125]=-1;ret[129]=-1;ret[132]=-1;ret[133]=-1;ret[134]=-1;ret[157]=-1;ret[159]=-1;}
void probe_class_known(int type,int known){objects[type].oc_name_known=known;objects[type].oc_uname=NULL;}void probe_option(int i,int v){opts[i]=v;}void probe_return(int i,long v){ret[i]=v;}int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nr=n;ri=0;}int probe_rng_count(void){return ri;}unsigned probe_rng_state(void){return seed;}const char*probe_trace(void){return tracebuf;}const char*probe_result_string(void){return resultbuf;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_new_mon(int type,int x,int y){struct monst*m;if(nmon>=16)panic("mon limit");m=calloc(1,sizeof*m);m->data=&mons[type];m->mnum=type;m->cham=NON_PM;m->m_id=nmon+100;m->mx=x;m->my=y;m->mhp=50;m->mhpmax=100;m->mcanmove=m->mcansee=1;m->m_lev=10;monsters[nmon++]=m;return nmon-1;}
int probe_new_obj(int type,int place){struct obj*o;if(nobj>=64)panic("obj limit");o=calloc(1,sizeof*o);o->otyp=type;o->oclass=objects[type].oc_class;o->o_id=nobj+100;o->quan=1;o->corpsenm=NON_PM;o->where=place;nodes[nobj++]=o;return nobj-1;}
void probe_equipment(int i,int index){struct obj*o=item(index);switch(i){case 0:uwep=o;break;case 1:uarm=o;break;case 2:uarmg=o;break;case 3:uarmh=o;break;case 4:uarmf=o;break;case 5:uarmc=o;break;case 6:uarmu=o;break;case 7:ublindf=o;break;case 8:uamul=o;break;case 9:uswapwep=o;break;case 10:uball=o;break;case 11:uchain=o;break;}}
void probe_property(int id,int field,long v){if(field==0)u.uprops[id].intrinsic=v;else if(field==1)u.uprops[id].extrinsic=v;else u.uprops[id].blocked=v;}
void probe_cells(int i,long v){cells[i]=v;}void probe_moncell(int i){moncell=actor(i);}
void probe_hero(int i,long v){switch(i){case 0:u.umonnum=v;gy.youmonst.data=&mons[v];break;case 1:u.ulycn=v;break;case 2:u.uhp=v;break;case 3:u.uhpmax=v;break;case 4:u.mh=v;break;case 5:u.mhmax=v;break;case 6:u.mtimedone=v;break;case 7:u.ulevel=v;break;case 8:u.ulevelmax=v;break;case 9:u.uen=v;break;case 10:u.uenmax=v;break;case 11:u.uhunger=v;break;case 12:u.ualign.type=v;break;case 13:u.uroleplay.deaf=v;break;case 14:gm.multi=v;break;case 15:u.usteed=actor(v);break;case 16:u.ustuck=actor(v);break;case 17:gi.invent=item(v);break;case 18:u.uconduct.polypiles=v;break;case 19:u.usick_type=v;break;case 20:u.ucreamed=v;break;case 21:gu.urole.mnum=v;break;case 22:flags.female=v;break;case 23:flags.beginner=v;break;case 24:u.uswallow=v;break;case 25:u.uinwater=v;break;case 26:gy.youmonst.m_ap_type=v;break;case 27:gy.youmonst.mappearance=v;break;case 28:iflags.menu_requested=v;break;case 29:u.acurr.a[A_STR]=v;break;case 30:u.acurr.a[A_DEX]=v;break;}}
void probe_mon(int slot,int i,long v){struct monst*m=actor(slot);switch(i){case 0:m->mhp=v;break;case 1:m->mhpmax=v;break;case 2:m->data=&mons[v];break;case 3:m->cham=v;break;case 4:m->misc_worn_check=v;break;case 5:m->mx=v;break;case 6:m->my=v;break;}}
void probe_obj(int slot,int i,long v){struct obj*o=item(slot);switch(i){case 0:o->otyp=v;o->oclass=objects[v].oc_class;break;case 1:o->quan=v;break;case 2:o->age=v;break;case 3:o->spe=v;break;case 4:o->corpsenm=v;break;case 5:o->where=v;break;case 6:o->owornmask=v;break;case 7:o->oartifact=v;break;case 8:o->oclass=v;break;}}
void probe_tile(int x,int y,int type,int flags){levl[x][y].typ=type;vision[y][x]=flags;}
void probe_mon_bit(int slot,int field,unsigned v){struct monst*o=actor(slot);switch(field){case 0:o->isminion=v;break;case 1:o->mconf=v;break;}}
void probe_obj_bit(int slot,int field,unsigned v){struct obj*o=item(slot);switch(field){case 0:o->bknown=v;break;case 1:o->blessed=v;break;case 2:o->cknown=v;break;case 3:o->cursed=v;break;case 4:o->dknown=v;break;case 5:o->globby=v;break;case 6:o->in_use=v;break;case 7:o->known=v;break;case 8:o->no_charge=v;break;case 9:o->oeroded=v;break;case 10:o->oerodeproof=v;break;case 11:o->otrapped=v;break;case 12:o->rknown=v;break;case 13:o->unpaid=v;break;}}
long probe_action(int op,long a,long b,long c,long d){switch(op){case 0:return is_edible(item(a));case 1:init_uhunger();break;case 2:return eatmdone();case 3:eatmupdate();break;case 4:snprintf(resultbuf,sizeof resultbuf,"%s",food_xname(item(a),b));return 1;case 5:choke(item(a));break;case 6:recalc_wt();break;case 7:reset_eat();break;case 8:return obj_nutrition(item(a));case 9:return adj_victual_nutrition();case 10:return oid(touchfood(item(a)));case 11:food_disappears(item(a));break;case 12:food_substitution(item(a),item(b));break;case 13:do_reset_eat();break;case 14:return temp_resist(a);case 15:return eating_dangerous_corpse(a);case 16:return eatfood();case 17:done_eating(a);break;case 18:eating_conducts(&mons[a]);break;case 19:return eat_brains(actor(a),actor(b),c,(int*)&cells[0]);case 20:return maybe_cannibal(a,b);case 21:cprefx(a);break;case 22:fix_petrification();break;case 23:return intrinsic_possible(a,&mons[b]);case 24:return should_givit(a,&mons[b]);case 25:return temp_givit(a,&mons[b]);case 26:givit(a,&mons[b]);break;case 27:eye_of_newt_buzz();break;case 28:cpostfx(a);break;case 29:return corpse_intrinsic(&mons[a]);case 30:violated_vegetarian();break;case 31:return oid(costly_tin(a));case 32:return tin_variety_txt((opts[33]?NULL:resultbuf),(int*)&cells[0]);case 33:tin_details(item(a),b,resultbuf);break;case 34:set_tin_variety(item(a),b);break;case 35:return tin_variety(item(a),b);case 36:use_up_tin(item(a));break;case 37:consume_tin((opts[33]?NULL:resultbuf));break;case 38:return opentin();case 39:start_tin(item(a));break;case 40:return Hear_again();case 41:return rottenfood(item(a));case 42:return eatcorpse(item(a));case 43:start_eating(item(a),b);break;case 44:return eating_glob(item(a));case 45:garlic_breath(actor(a));break;case 46:return fprefx(item(a));case 47:return bounded_increase(a,b,c);case 48:accessory_has_effect(item(a));break;case 49:eataccessory(item(a));break;case 50:eatspecial();break;case 51:snprintf(resultbuf,sizeof resultbuf,"%s",foodword(item(a)));return 1;case 52:fpostfx(item(a));break;case 53:return edibility_prompts(item(a));case 54:return doeat_nonfood(item(a));case 55:return doeat();case 56:return tinopen_ok(item(a));case 57:return use_tin_opener(item(a));case 58:return bite();case 59:gethungry();break;case 60:morehungry(a);break;case 61:lesshungry(a);break;case 62:return unfaint();case 63:return is_fainted();case 64:reset_faint();break;case 65:newuhs(a);break;case 66:return eat_ok(item(a));case 67:return offer_ok(item(a));case 68:return tin_ok(item(a));case 69:return oid(floorfood((opts[33]?NULL:resultbuf),b));case 70:vomit();break;case 71:return eaten_stat(a,item(b));case 72:consume_oeaten(item(a),b);break;case 73:return maybe_finished_meal(a);case 74:cant_finish_meal(item(a));break;case 75:return Popeye(a);case 76:return Finish_digestion();default:panic("bad action %d",op);}return 0;}
void*probe_pointer(int kind,int i){switch(kind){case 0:return &u;case 1:return actor(i);case 2:return item(i);case 3:return levl;case 4:return vision;case 5:return cells;case 6:return &gp;case 7:return &gm;case 8:return &disp;case 9:return &svc;case 10:return &gy.youmonst;case 11:return &gu;case 12:return &gn;case 13:return &moncell;case 14:return fake_bytes;default:return NULL;}}int probe_count(int k){return k?nobj:nmon;}long probe_scalar(int i){switch(i){case 0:return mid(moncell);case 1:return mid(u.ustuck);case 2:return mid(u.usteed);case 3:return oid(gi.invent);case 4:return gp.potion_unkn;case 5:return gp.potion_nothing;case 6:return gm.multi;case 7:return disp.botl;case 8:return gv.vision_full_recalc;case 9:return svc.context.mon_moving;case 10:return fake_calls;default:return 0;}}
int sensemon(struct monst*m){return opts[34];}void discover_object(int t,boolean a,boolean b,boolean c){logmsg("discover:%d:%d:%d:%d;",t,a,b,c);}winid WIN_MAP=2;const char hidespinchars[]="|/-\\";
void You_cant(const char*f,...){va_list a;logmsg("You_cant:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
void You_hear(const char*f,...){va_list a;logmsg("You_hear:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
void probe_victual(int field,long value){switch(field){case 0:svc.context.victual.piece=item(value);break;case 1:svc.context.victual.usedtime=value;break;case 2:svc.context.victual.reqtime=value;break;case 3:svc.context.victual.nmod=value;break;case 4:svc.context.victual.canchoke=value;break;case 5:svc.context.victual.fullwarn=value;break;case 6:svc.context.victual.eating=value;break;case 7:svc.context.victual.doreset=value;break;case 8:svc.context.victual.o_id=value;break;}}
void probe_tin(int field,long value){switch(field){case 0:svc.context.tin.tin=item(value);break;case 1:svc.context.tin.usedtime=value;break;case 2:svc.context.tin.reqtime=value;break;case 3:svc.context.tin.o_id=value;break;}}
void probe_text(const char*s){snprintf(resultbuf,sizeof resultbuf,"%s",s);}
void probe_eaten(int i,unsigned value){item(i)->oeaten=value;}void probe_weight(int i,unsigned value){item(i)->owt=value;}
void probe_hunger(unsigned state,int hunger){u.uhs=state;u.uhunger=hunger;}void probe_moves(long value){svm.moves=value;}
void*probe_more_pointer(int kind){switch(kind){case 0:return &ge;case 1:return &ga;case 2:return &go;case 3:return &gc;case 4:return &gf;case 5:return &svk;default:return NULL;}}
long probe_context(int i){switch(i){case 0:return oid(svc.context.victual.piece);case 1:return oid(svc.context.tin.tin);case 2:return gc.corpsenm_digested;default:return 0;}}
extern const char*const hu_stat[7];
const char*probe_table(int which,int i){
#ifdef TELEPORT_REFERENCE_TU
return which==0?hu_stat[i]:which==1?tintxts[i].txt:foodwords[i];
#else
return which==0?hu_stat[i]:NULL;
#endif
}
long probe_tin_row(int i,int field){
#ifdef TELEPORT_REFERENCE_TU
return field==0?tintxts[i].nut:field==1?tintxts[i].fodder:tintxts[i].greasy;
#else
return 0;
#endif
}

boolean paranoid_query(boolean p,const char*q){logmsg("paranoid:%d:%s;",p,q);return opts[35];}

void probe_trap(int type,int seen){fixture_trap.ttyp=type;fixture_trap.tseen=seen;}void probe_wall(unsigned flags){levl[u.ux][u.uy].wall_info=flags;}

void probe_mimic(const char*text,boolean alias){ge.eatmbuf=dupstr(text);gn.nomovemsg=alias?ge.eatmbuf:"independent";}
int probe_free_count(void){return fixture_frees;}
const char*probe_mimic_text(void){return ge.eatmbuf;}const char*probe_nomove_text(void){return gn.nomovemsg;}
long probe_callback_identity(int slot){int(*p)(void)=slot?ga.afternmv:go.occupation;int i;
#ifdef TELEPORT_REFERENCE_TU
int(*f[])(void)={eatmdone,eatfood,opentin,unfaint,Hear_again,Finish_digestion};
for(i=0;i<6;i++)if(p==f[i])return i;
#else
extern uintptr_t teleport_eat_callback_pointer(int);
for(i=0;i<6;i++)if((uintptr_t)p==teleport_eat_callback_pointer(i))return i;
#endif
return p?(long)(uintptr_t)p:-1;
}
void probe_callback_set(int slot,unsigned long raw){if(slot)ga.afternmv=(int(*)(void))(uintptr_t)raw;else go.occupation=(int(*)(void))(uintptr_t)raw;}
