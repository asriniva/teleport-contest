/* Controlled external world; unchanged original potion.c is the policy oracle. */
#include "hack.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
__typeof__(u)u;__typeof__(svc)svc;__typeof__(svm)svm;__typeof__(svl)svl;__typeof__(gy)gy;__typeof__(gv)gv;__typeof__(gm)gm;__typeof__(gn)gn;__typeof__(gi)gi;__typeof__(gp)gp;__typeof__(gu)gu;__typeof__(svd)svd;__typeof__(flags)flags;__typeof__(iflags)iflags;__typeof__(disp)disp;__typeof__(gs)gs;const __typeof__(cg)cg={0};const struct c_common_strings c_common_strings={.c_nothing_happens="Nothing happens.",.c_nothing_seems_to_happen="Nothing seems to happen.",.c_Something="Something",.c_something="something",.c_vision_clears="vision clears",.c_You_can_move_again="You can move again.",.c_the_your={"the","your"}};const struct c_color_names c_color_names={.c_black="black",.c_orange="orange",.c_light_blue="light blue",.c_amber="amber",.c_red="red"};
struct obj*uwep,*uarm,*uarmg,*uarmh,*uarmf,*uarmc,*uarmu,*ublindf,*uamul,*uswapwep,*uball,*uchain;struct obj hands_obj;const char ynchars[]="yn";void paniclog(const char*a,const char*b){(void)a;(void)b;}
const struct Gender genders[4]={{.his="his",.he="he",.him="him"},{.his="her",.he="she",.him="her"},{.his="its",.he="it",.him="it"},{.his="their",.he="they",.him="them"}};
static struct monst*monsters[16];static struct obj*nodes[64];static seenV vision[ROWNO][COLNO],*visionrows[ROWNO];static int opts[128],rolls[4096],nr,ri,nmon,nobj;static unsigned seed;static long ret[256];static char tracebuf[1048576],caller[256];static void*growth;static long cells[8];static unsigned char fake_bytes[sizeof(struct obj)];static int fake_calls;static struct kinfo killer_record;static stairway stairs;
static int mid(struct monst*m){int i;if(!m)return-1;if(m==&gy.youmonst)return-2;for(i=0;i<nmon;i++)if(m==monsters[i])return i;return-3;}static int oid(struct obj*o){int i;if(!o)return-1;if(o==&hands_obj)return-2;for(i=0;i<nobj;i++)if(o==nodes[i])return i;return-3;}
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static void callback(int n){if(opts[120]==n&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("grow:%d;",n);}if(opts[121]==n){u.uprops[HALF_PHDAM].intrinsic^=FROMOUTSIDE;logmsg("fliphalf;");}if(opts[122]==n){nodes[0]->blessed=!nodes[0]->blessed;logmsg("flipbless;");}if(opts[123]==n)logmsg("live_ustuck:%d;",mid(u.ustuck));if(opts[125]==n&&!opts[126]&&nmon>1){opts[126]=1;split_mon(monsters[0],monsters[1]);logmsg("reenter:%d;",n);}}
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
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}boolean unconscious(void){return opts[2];}boolean is_fainted(void){return opts[3];}boolean has_ceiling(d_level*l){return opts[4];}schar acurr(int i){logmsg("attribute:%d;",i);return u.acurr.a[i];}int pronoun_gender(struct monst*m,unsigned flags){return opts[6];}boolean is_pool(coordxy x,coordxy y){return isok(x,y)&&(levl[x][y].typ==POOL||levl[x][y].typ==MOAT||levl[x][y].typ==WATER);}int bcsign(struct obj*o){return o->blessed?1:o->cursed?-1:0;}
char yn_function(const char*q,const char*c,char d,boolean add){logmsg("history:%d;",add);return yn(q,c,d);}
struct obj*getobj(const char*q,int(*select)(struct obj*),unsigned flags){int i;logmsg("getobj:%s:%u;",q,flags);for(i=0;i<nobj;i++)logmsg("select:%d:%d;",i,select(nodes[i]));callback(2);return opts[11]==-2?&hands_obj:opts[11]>=0&&opts[11]<nobj?nodes[opts[11]]:NULL;}
char*short_oname(struct obj*o,char*(*one)(struct obj*),char*(*two)(struct obj*),unsigned len){logmsg("short:%d:%u:%d:%d;",oid(o),len,one==doname,two==thesimpleoname);return "short object";}
void docall(struct obj*o){logmsg("docall:%d:;",oid(o));memcpy(fake_bytes,o,sizeof *o);fake_calls++;}
void get_level(d_level*l,int n){logmsg("getlevel:%d;",n);l->dnum=1;l->dlevel=n;}void assign_level(d_level*to,d_level*from){*to=*from;}
boolean Can_rise_up(coordxy a0,coordxy a1,d_level * a2){logmsg("Can_rise_up:%d:%d:%d:;",(int)a0,(int)a1,a2!=NULL);callback(20+0);return (boolean)ret[0];}
char * Monnam(struct monst * a0){logmsg("Monnam:%d:;",mid(a0));callback(20+1);return "Monnam";}
void Sting_effects(int a0){logmsg("Sting_effects:%d:;",(int)a0);callback(20+2);}
char * The(const char * a0){logmsg("The:%s:;",(a0?a0:"NULL"));callback(20+3);return "The";}
char * Tobjnam(struct obj * a0,const char * a1){logmsg("Tobjnam:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+4);return "Tobjnam";}
char * Yname2(struct obj * a0){logmsg("Yname2:%d:;",oid(a0));callback(20+5);return "Yname2";}
char * Yobjnam2(struct obj * a0,const char * a1){logmsg("Yobjnam2:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+6);return "Yobjnam2";}
char * a_monnam(struct monst * a0){logmsg("a_monnam:%d:;",mid(a0));callback(20+7);return "a_monnam";}
boolean adjattrib(int a0,int a1,int a2){logmsg("adjattrib:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+8);return (boolean)ret[8];}
void aggravate(void){logmsg("aggravate:;");callback(20+9);}
void alter_cost(struct obj * a0,long a1){logmsg("alter_cost:%d:%ld:;",oid(a0),(long)a1);callback(20+10);}
char * an(const char * a0){logmsg("an:%s:;",(a0?a0:"NULL"));callback(20+11);return "an";}
char * aobjnam(struct obj * a0,const char * a1){logmsg("aobjnam:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+12);return "aobjnam";}
int bhitm(struct monst * a0,struct obj * a1){logmsg("bhitm:%d:%d:;",mid(a0),oid(a1));callback(20+13);return (int)ret[13];}
void bless(struct obj * a0){logmsg("bless:%d:;",oid(a0));callback(20+14);a0->blessed=1;}
const char * body_part(int a0){logmsg("body_part:%d:;",(int)a0);callback(20+15);return "body_part";}
void burn_away_slime(void){logmsg("burn_away_slime:;");callback(20+16);}
boolean can_reach_floor(boolean a0){logmsg("can_reach_floor:%d:;",(int)a0);callback(20+17);return (boolean)ret[17];}
int canseemon(struct monst * a0){logmsg("canseemon:%d:;",mid(a0));callback(20+18);return (int)ret[18];}
const char * ceiling(coordxy a0,coordxy a1){logmsg("ceiling:%d:%d:;",(int)a0,(int)a1);callback(20+19);return "ceiling";}
void check_unpaid(struct obj * a0){logmsg("check_unpaid:%d:;",oid(a0));callback(20+20);}
struct monst * clone_mon(struct monst * a0,coordxy a1,coordxy a2){logmsg("clone_mon:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+21);return ret[21]==-2?&gy.youmonst:ret[21]>=0&&ret[21]<nmon?monsters[ret[21]]:NULL;}
struct monst * cloneu(void){logmsg("cloneu:;");callback(20+22);return ret[22]==-2?&gy.youmonst:ret[22]>=0&&ret[22]<nmon?monsters[ret[22]]:NULL;}
struct _cmd_queue * cmdq_peek(int a0){logmsg("cmdq_peek:%d:;",(int)a0);callback(20+23);return NULL;}
void costly_alteration(struct obj * a0,int a1){logmsg("costly_alteration:%d:%d:;",oid(a0),(int)a1);callback(20+24);}
void curse(struct obj * a0){logmsg("curse:%d:;",oid(a0));callback(20+25);a0->cursed=1;}
char * cxname(struct obj * a0){logmsg("cxname:%d:;",oid(a0));callback(20+26);return "cxname";}
void dealloc_killer(struct kinfo * a0){logmsg("dealloc_killer:%d:;",a0!=NULL);callback(20+27);}
void dealloc_obj(struct obj * a0){logmsg("dealloc_obj:%d:;",oid(a0));callback(20+28);}
void delayed_killer(int a0,int a1,const char * a2){logmsg("delayed_killer:%d:%d:%s:;",(int)a0,(int)a1,(a2?a2:"NULL"));callback(20+29);}
schar depth(d_level * a0){logmsg("depth:%d:;",a0!=NULL);callback(20+30);return (schar)ret[30];}
void dipfountain(struct obj * a0){logmsg("dipfountain:%d:;",oid(a0));callback(20+31);}
void dipsink(struct obj * a0){logmsg("dipsink:%d:;",oid(a0));callback(20+32);}
boolean dmgtype(struct permonst * a0,int a1){logmsg("dmgtype:%d:%d:;",a0?a0->pmidx:-1,(int)a1);callback(20+33);return (boolean)ret[33];}
void do_enlightenment_effect(void){logmsg("do_enlightenment_effect:;");callback(20+34);}
char * doname(struct obj * a0){logmsg("doname:%d:;",oid(a0));callback(20+35);return "doname";}
int doup(void){logmsg("doup:;");callback(20+36);return (int)ret[36];}
void drinkfountain(void){logmsg("drinkfountain:;");callback(20+37);}
void drinksink(void){logmsg("drinksink:;");callback(20+38);}
void eatmupdate(void){logmsg("eatmupdate:;");callback(20+39);}
void enlightenment(int a0,int a1){logmsg("enlightenment:%d:%d:;",(int)a0,(int)a1);callback(20+40);}
int erode_obj(struct obj * a0,const char * a1,int a2,int a3){logmsg("erode_obj:%d:%s:%d:%d:;",oid(a0),(a1?a1:"NULL"),(int)a2,(int)a3);callback(20+41);return (int)ret[41];}
void exercise(int a0,boolean a1){logmsg("exercise:%d:%d:;",(int)a0,(int)a1);callback(20+42);}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logmsg("explode:%d:%d:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);callback(20+43);}
void explode_oil(struct obj * a0,coordxy a1,coordxy a2){logmsg("explode_oil:%d:%d:%d:;",oid(a0),(int)a1,(int)a2);callback(20+44);}
void fall_asleep(int a0,boolean a1){logmsg("fall_asleep:%d:%d:;",(int)a0,(int)a1);callback(20+45);}
struct kinfo * find_delayed_killer(int a0){logmsg("find_delayed_killer:%d:;",(int)a0);callback(20+46);return opts[12]?&killer_record:NULL;}
const char * fingers_or_gloves(boolean a0){logmsg("fingers_or_gloves:%d:;",(int)a0);callback(20+47);return "fingers_or_gloves";}
boolean fire_damage(struct obj * a0,boolean a1,coordxy a2,coordxy a3){logmsg("fire_damage:%d:%d:%d:%d:;",oid(a0),(int)a1,(int)a2,(int)a3);callback(20+48);return (boolean)ret[48];}
void fix_petrification(void){logmsg("fix_petrification:;");callback(20+49);}
void fixup_oil(struct obj * a0,struct obj * a1){logmsg("fixup_oil:%d:%d:;",oid(a0),oid(a1));callback(20+50);}
void float_up(void){logmsg("float_up:;");callback(20+51);}
void float_vs_flight(void){logmsg("float_vs_flight:;");callback(20+52);}
void floating_above(const char * a0){logmsg("floating_above:%s:;",(a0?a0:"NULL"));callback(20+53);}
void freeinv(struct obj * a0){logmsg("freeinv:%d:;",oid(a0));callback(20+54);}
char * fruitname(boolean a0){logmsg("fruitname:%d:;",(int)a0);callback(20+55);return "fruitname";}
int glyph_at(coordxy a0,coordxy a1){logmsg("glyph_at:%d:%d:;",(int)a0,(int)a1);callback(20+56);return (int)ret[56];}
void goto_level(d_level * a0,boolean a1,boolean a2,boolean a3){logmsg("goto_level:%d:%d:%d:%d:;",a0!=NULL,(int)a1,(int)a2,(int)a3);callback(20+57);}
boolean hard_helmet(struct obj * a0){logmsg("hard_helmet:%d:;",oid(a0));callback(20+58);return (boolean)ret[58];}
const char * hcolor(const char * a0){logmsg("hcolor:%s:;",(a0?a0:"NULL"));callback(20+59);return "hcolor";}
void heal_legs(int a0){logmsg("heal_legs:%d:;",(int)a0);callback(20+60);}
int healmon(struct monst * a0,int a1,int a2){logmsg("healmon:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+61);a0->mhp+=a1;if(a0->mhp>a0->mhpmax)a0->mhp=a0->mhpmax;return (int)ret[61];}
const char * hliquid(const char * a0){logmsg("hliquid:%s:;",(a0?a0:"NULL"));callback(20+62);return "hliquid";}
struct obj * hold_another_object(struct obj * a0,const char * a1,const char * a2,const char * a3){logmsg("hold_another_object:%d:%s:%s:%s:;",oid(a0),(a1?a1:"NULL"),(a2?a2:"NULL"),(a3?a3:"NULL"));callback(20+63);return ret[63]>=0&&ret[63]<nobj?nodes[ret[63]]:NULL;}
char * in_rooms(coordxy a0,coordxy a1,int a2){logmsg("in_rooms:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+64);return "in_rooms";}
boolean inaccessible_equipment(struct obj * a0,const char * a1,boolean a2){logmsg("inaccessible_equipment:%d:%s:%d:;",oid(a0),(a1?a1:"NULL"),(int)a2);callback(20+65);return (boolean)ret[65];}
void killed(struct monst * a0){logmsg("killed:%d:;",mid(a0));callback(20+66);}
void learn_unseen_invent(void){logmsg("learn_unseen_invent:;");callback(20+67);}
xint16 ledger_no(d_level * a0){logmsg("ledger_no:%d:;",a0!=NULL);callback(20+68);return (xint16)ret[68];}
void losehp(int a0,const char * a1,schar a2){logmsg("losehp:%d:%s:%d:;",(int)a0,(a1?a1:"NULL"),(int)a2);callback(20+69);u.uhp-=a0;}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logmsg("makemon:%d:%d:%d:%d:;",a0?a0->pmidx:-1,(int)a1,(int)a2,(int)a3);callback(20+70);return ret[70]==-2?&gy.youmonst:ret[70]>=0&&ret[70]<nmon?monsters[ret[70]]:NULL;}
char * makeplural(const char * a0){logmsg("makeplural:%s:;",(a0?a0:"NULL"));callback(20+71);return "makeplural";}
void makewish(void){logmsg("makewish:;");callback(20+72);}
void map_invisible(coordxy a0,coordxy a1){logmsg("map_invisible:%d:%d:;",(int)a0,(int)a1);callback(20+73);}
void mcureblindness(struct monst * a0,boolean a1){logmsg("mcureblindness:%d:%d:;",mid(a0),(int)a1);callback(20+74);a0->mcansee=1;a0->mblinded=0;}
struct obj * mkobj(int a0,boolean a1){logmsg("mkobj:%d:%d:;",(int)a0,(int)a1);callback(20+75);return ret[75]>=0&&ret[75]<nobj?nodes[ret[75]]:NULL;}
struct obj * mksobj(int a0,boolean a1,boolean a2){logmsg("mksobj:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+76);return ret[76]>=0&&ret[76]<nobj?nodes[ret[76]]:NULL;}
void mon_adjust_speed(struct monst * a0,int a1,struct obj * a2){logmsg("mon_adjust_speed:%d:%d:%d:;",mid(a0),(int)a1,oid(a2));callback(20+77);}
boolean mon_hates_blessings(struct monst * a0){logmsg("mon_hates_blessings:%d:;",mid(a0));callback(20+78);return (boolean)ret[78];}
char * mon_nam(struct monst * a0){logmsg("mon_nam:%d:;",mid(a0));callback(20+79);return "mon_nam";}
void mon_set_minvis(struct monst * a0,boolean a1){logmsg("mon_set_minvis:%d:%d:;",mid(a0),(int)a1);callback(20+80);a0->minvis=1;}
void mongone(struct monst * a0){logmsg("mongone:%d:;",mid(a0));callback(20+81);a0->mhp=0;}
void monkilled(struct monst * a0,const char * a1,int a2){logmsg("monkilled:%d:%s:%d:;",mid(a0),(a1?a1:"NULL"),(int)a2);callback(20+82);a0->mhp=0;}
int monster_detect(struct obj * a0,int a1){logmsg("monster_detect:%d:%d:;",oid(a0),(int)a1);callback(20+83);return (int)ret[83];}
void monstseesu(unsigned long a0){logmsg("monstseesu:%ld:;",(long)a0);callback(20+84);}
void monstunseesu(unsigned long a0){logmsg("monstunseesu:%ld:;",(long)a0);callback(20+85);}
void more_experienced(int a0,int a1){logmsg("more_experienced:%d:%d:;",(int)a0,(int)a1);callback(20+86);}
int near_capacity(void){logmsg("near_capacity:;");callback(20+87);return (int)ret[87];}
void new_were(struct monst * a0){logmsg("new_were:%d:;",mid(a0));callback(20+88);}
void newsym(coordxy a0,coordxy a1){logmsg("newsym:%d:%d:;",(int)a0,(int)a1);callback(20+89);}
void newuhs(boolean a0){logmsg("newuhs:%d:;",(int)a0);callback(20+90);}
void nomul(int a0){logmsg("nomul:%d:;",(int)a0);callback(20+91);gm.multi=a0;}
void obfree(struct obj * a0,struct obj * a1){logmsg("obfree:%d:%d:;",oid(a0),oid(a1));callback(20+92);}
void obj_extract_self(struct obj * a0){logmsg("obj_extract_self:%d:;",oid(a0));callback(20+93);}
boolean obj_resists(struct obj * a0,int a1,int a2){logmsg("obj_resists:%d:%d:%d:;",oid(a0),(int)a1,(int)a2);callback(20+94);return (boolean)ret[94];}
boolean obj_unpolyable(struct obj * a0){logmsg("obj_unpolyable:%d:;",oid(a0));callback(20+95);return (boolean)ret[95];}
boolean objdescr_is(struct obj * a0,const char * a1){logmsg("objdescr_is:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+96);return (boolean)ret[96];}
int object_detect(struct obj * a0,int a1){logmsg("object_detect:%d:%d:;",oid(a0),(int)a1);callback(20+97);return (int)ret[97];}
void observe_object(struct obj * a0){logmsg("observe_object:%d:;",oid(a0));callback(20+98);}
char * otense(struct obj * a0,const char * a1){logmsg("otense:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+99);return "otense";}
void paralyze_monst(struct monst * a0,int a1){logmsg("paralyze_monst:%d:%d:;",mid(a0),(int)a1);callback(20+100);}
boolean permapoisoned(struct obj * a0){logmsg("permapoisoned:%d:;",oid(a0));callback(20+101);return (boolean)ret[101];}
void pluslvl(boolean a0){logmsg("pluslvl:%d:;",(int)a0);callback(20+102);u.ulevel++;}
void poisontell(int a0,boolean a1){logmsg("poisontell:%d:%d:;",(int)a0,(int)a1);callback(20+103);}
struct obj * poly_obj(struct obj * a0,int a1){logmsg("poly_obj:%d:%d:;",oid(a0),(int)a1);callback(20+104);return ret[104]>=0&&ret[104]<nobj?nodes[ret[104]]:NULL;}
void polyself(int a0){logmsg("polyself:%d:;",(int)a0);callback(20+105);if(opts[124]){u.umonnum=opts[124];gy.youmonst.data=&mons[opts[124]];}}
void prinv(const char * a0,struct obj * a1,long a2){logmsg("prinv:%s:%d:%ld:;",(a0?a0:"NULL"),oid(a1),(long)a2);callback(20+106);}
void remove_worn_item(struct obj * a0,boolean a1){logmsg("remove_worn_item:%d:%d:;",oid(a0),(int)a1);callback(20+107);}
int resist(struct monst * a0,char a1,int a2,int a3){logmsg("resist:%d:%d:%d:%d:;",mid(a0),(int)a1,(int)a2,(int)a3);callback(20+108);return (int)ret[108];}
void rider_cant_reach(void){logmsg("rider_cant_reach:;");callback(20+109);}
long rndexp(boolean a0){logmsg("rndexp:%d:;",(int)a0);callback(20+110);return (long)ret[110];}
char * rndmonnam(char * a0){logmsg("rndmonnam:%s:;",(a0?a0:"NULL"));callback(20+111);return "rndmonnam";}
void see_monsters(void){logmsg("see_monsters:;");callback(20+112);}
void see_objects(void){logmsg("see_objects:;");callback(20+113);}
void see_traps(void){logmsg("see_traps:;");callback(20+114);}
void set_bc(int a0){logmsg("set_bc:%d:;",(int)a0);callback(20+115);}
void set_malign(struct monst * a0){logmsg("set_malign:%d:;",mid(a0));callback(20+116);}
void set_mimic_blocking(void){logmsg("set_mimic_blocking:;");callback(20+117);}
void set_ulycn(int a0){logmsg("set_ulycn:%d:;",(int)a0);callback(20+118);u.ulycn=a0;}
struct monst * shop_keeper(char a0){logmsg("shop_keeper:%d:;",(int)a0);callback(20+119);return ret[119]==-2?&gy.youmonst:ret[119]>=0&&ret[119]<nmon?monsters[ret[119]]:NULL;}
char * simpleonames(struct obj * a0){logmsg("simpleonames:%d:;",oid(a0));callback(20+120);return "simpleonames";}
int sleep_monst(struct monst * a0,int a1,int a2){logmsg("sleep_monst:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+121);return (int)ret[121];}
void slept_monst(struct monst * a0){logmsg("slept_monst:%d:;",mid(a0));callback(20+122);}
struct obj * splitobj(struct obj * a0,long a1){logmsg("splitobj:%d:%ld:;",oid(a0),(long)a1);callback(20+123);return ret[123]>=0&&ret[123]<nobj?nodes[ret[123]]:NULL;}
void spoteffects(boolean a0){logmsg("spoteffects:%d:;",(int)a0);callback(20+124);}
const char * stagger(const struct permonst * a0,const char * a1){logmsg("stagger:%d:%s:;",a0?a0->pmidx:-1,(a1?a1:"NULL"));callback(20+125);return "stagger";}
stairway * stairway_at(coordxy a0,coordxy a1){logmsg("stairway_at:%d:%d:;",(int)a0,(int)a1);callback(20+126);return opts[13]?&stairs:NULL;}
long stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logmsg("stolen_value:%d:%d:%d:%d:%d:;",oid(a0),(int)a1,(int)a2,(int)a3,(int)a4);callback(20+127);return (long)ret[127];}
void subfrombill(struct obj * a0,struct monst * a1){logmsg("subfrombill:%d:%d:;",oid(a0),mid(a1));callback(20+128);}
const char * surface(coordxy a0,coordxy a1){logmsg("surface:%d:%d:;",(int)a0,(int)a1);callback(20+129);return "surface";}
void swallowed(int a0){logmsg("swallowed:%d:;",(int)a0);callback(20+130);}
boolean tamedog(struct monst * a0,struct obj * a1,boolean a2){logmsg("tamedog:%d:%d:%d:;",mid(a0),oid(a1),(int)a2);callback(20+131);return (boolean)ret[131];}
char * the(const char * a0){logmsg("the:%s:;",(a0?a0:"NULL"));callback(20+132);return "the";}
char * thesimpleoname(struct obj * a0){logmsg("thesimpleoname:%d:;",oid(a0));callback(20+133);return "thesimpleoname";}
void tmp_at(coordxy a0,coordxy a1){logmsg("tmp_at:%d:%d:;",(int)a0,(int)a1);callback(20+134);}
void trycall(struct obj * a0){logmsg("trycall:%d:;",oid(a0));callback(20+135);}
int unfixable_trouble_count(boolean a0){logmsg("unfixable_trouble_count:%d:;",(int)a0);callback(20+136);return (int)ret[136];}
void unmap_object(coordxy a0,coordxy a1){logmsg("unmap_object:%d:%d:;",(int)a0,(int)a1);callback(20+137);}
void update_inventory(void){logmsg("update_inventory:;");callback(20+138);}
void useup(struct obj * a0){logmsg("useup:%d:;",oid(a0));callback(20+139);}
void useupall(struct obj * a0){logmsg("useupall:%d:;",oid(a0));callback(20+140);}
void vision_recalc(int a0){logmsg("vision_recalc:%d:;",(int)a0);callback(20+141);}
char * vtense(const char * a0,const char * a1){logmsg("vtense:%s:%s:;",(a0?a0:"NULL"),(a1?a1:"NULL"));callback(20+142);return "vtense";}
void wake_nearto(coordxy a0,coordxy a1,int a2){logmsg("wake_nearto:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+143);}
void wakeup(struct monst * a0,boolean a1){logmsg("wakeup:%d:%d:;",mid(a0),(int)a1);callback(20+144);}
int wash_hands(void){logmsg("wash_hands:;");callback(20+145);return (int)ret[145];}
int water_damage(struct obj * a0,const char * a1,boolean a2){logmsg("water_damage:%d:%s:%d:;",oid(a0),(a1?a1:"NULL"),(int)a2);callback(20+146);return (int)ret[146];}
const char * waterbody_name(coordxy a0,coordxy a1){logmsg("waterbody_name:%d:%d:;",(int)a0,(int)a1);callback(20+147);return "waterbody_name";}
struct obj * which_armor(struct monst * a0,long a1){logmsg("which_armor:%d:%ld:;",mid(a0),(long)a1);callback(20+148);return ret[148]>=0&&ret[148]<nobj?nodes[ret[148]]:NULL;}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){logmsg("x_monnam:%d:%d:%s:%d:%d:;",mid(a0),(int)a1,(a2?a2:"NULL"),(int)a3,(int)a4);callback(20+149);return "x_monnam";}
char * xname(struct obj * a0){logmsg("xname:%d:;",oid(a0));callback(20+150);return "xname";}
char * yname(struct obj * a0){logmsg("yname:%d:;",oid(a0));callback(20+151);return "yname";}
void you_unwere(boolean a0){logmsg("you_unwere:%d:;",(int)a0);callback(20+152);}
void you_were(void){logmsg("you_were:;");callback(20+153);}
void unbless(struct obj * a0){logmsg("unbless:%d:;",oid(a0));callback(20+154);a0->blessed=0;}
void uncurse(struct obj * a0){logmsg("uncurse:%d:;",oid(a0));callback(20+155);a0->cursed=0;}
schar uasmon_maxStr(void){logmsg("uasmon_maxStr:;");callback(20+156);return (schar)ret[156];}
boolean defended(struct monst * a0,int a1){logmsg("defended:%d:%d:;",mid(a0),(int)a1);callback(20+157);return (boolean)ret[157];}
boolean undiscovered_artifact(xint16 a0){logmsg("undiscovered_artifact:%d:;",(int)a0);callback(20+158);return (boolean)ret[158];}
boolean Resists_Elem(struct monst * a0,int a1){logmsg("Resists_Elem:%d:%d:;",mid(a0),(int)a1);callback(20+159);return (boolean)ret[159];}
int sensemon(struct monst * a0){logmsg("sensemon:%d:;",mid(a0));callback(20+160);return (int)ret[160];}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+161);}

#ifdef TELEPORT_REFERENCE_TU
#include "potion.c"
#else
extern long teleport_potion_test_itimeout(long val);
#define itimeout teleport_potion_test_itimeout
extern long teleport_potion_test_itimeout_incr(long old, int incr);
#define itimeout_incr teleport_potion_test_itimeout_incr
extern void teleport_potion_test_ghost_from_bottle(void);
#define ghost_from_bottle teleport_potion_test_ghost_from_bottle
extern int teleport_potion_test_drink_ok(struct obj *obj);
#define drink_ok teleport_potion_test_drink_ok
extern void teleport_potion_test_peffect_restore_ability(struct obj *otmp);
#define peffect_restore_ability teleport_potion_test_peffect_restore_ability
extern void teleport_potion_test_peffect_hallucination(struct obj *otmp);
#define peffect_hallucination teleport_potion_test_peffect_hallucination
extern void teleport_potion_test_peffect_water(struct obj *otmp);
#define peffect_water teleport_potion_test_peffect_water
extern void teleport_potion_test_peffect_booze(struct obj *otmp);
#define peffect_booze teleport_potion_test_peffect_booze
extern void teleport_potion_test_peffect_enlightenment(struct obj *otmp);
#define peffect_enlightenment teleport_potion_test_peffect_enlightenment
extern void teleport_potion_test_peffect_invisibility(struct obj *otmp);
#define peffect_invisibility teleport_potion_test_peffect_invisibility
extern void teleport_potion_test_peffect_see_invisible(struct obj *otmp);
#define peffect_see_invisible teleport_potion_test_peffect_see_invisible
extern void teleport_potion_test_peffect_paralysis(struct obj *otmp);
#define peffect_paralysis teleport_potion_test_peffect_paralysis
extern void teleport_potion_test_peffect_sleeping(struct obj *otmp);
#define peffect_sleeping teleport_potion_test_peffect_sleeping
extern int teleport_potion_test_peffect_monster_detection(struct obj *otmp);
#define peffect_monster_detection teleport_potion_test_peffect_monster_detection
extern int teleport_potion_test_peffect_object_detection(struct obj *otmp);
#define peffect_object_detection teleport_potion_test_peffect_object_detection
extern void teleport_potion_test_peffect_sickness(struct obj *otmp);
#define peffect_sickness teleport_potion_test_peffect_sickness
extern void teleport_potion_test_peffect_confusion(struct obj *otmp);
#define peffect_confusion teleport_potion_test_peffect_confusion
extern void teleport_potion_test_peffect_gain_ability(struct obj *otmp);
#define peffect_gain_ability teleport_potion_test_peffect_gain_ability
extern void teleport_potion_test_peffect_speed(struct obj *otmp);
#define peffect_speed teleport_potion_test_peffect_speed
extern void teleport_potion_test_peffect_blindness(struct obj *otmp);
#define peffect_blindness teleport_potion_test_peffect_blindness
extern void teleport_potion_test_peffect_gain_level(struct obj *otmp);
#define peffect_gain_level teleport_potion_test_peffect_gain_level
extern void teleport_potion_test_peffect_healing(struct obj *otmp);
#define peffect_healing teleport_potion_test_peffect_healing
extern void teleport_potion_test_peffect_extra_healing(struct obj *otmp);
#define peffect_extra_healing teleport_potion_test_peffect_extra_healing
extern void teleport_potion_test_peffect_full_healing(struct obj *otmp);
#define peffect_full_healing teleport_potion_test_peffect_full_healing
extern void teleport_potion_test_peffect_levitation(struct obj *otmp);
#define peffect_levitation teleport_potion_test_peffect_levitation
extern void teleport_potion_test_peffect_gain_energy(struct obj *otmp);
#define peffect_gain_energy teleport_potion_test_peffect_gain_energy
extern void teleport_potion_test_peffect_oil(struct obj *otmp);
#define peffect_oil teleport_potion_test_peffect_oil
extern void teleport_potion_test_peffect_acid(struct obj *otmp);
#define peffect_acid teleport_potion_test_peffect_acid
extern void teleport_potion_test_peffect_polymorph(struct obj *otmp);
#define peffect_polymorph teleport_potion_test_peffect_polymorph
extern boolean teleport_potion_test_H2Opotion_dip(
    struct obj *potion,    
    struct obj *targobj,   
    boolean useeit,        
    const char *objphrase);
#define H2Opotion_dip teleport_potion_test_H2Opotion_dip
extern short teleport_potion_test_mixtype(struct obj *o1, struct obj *o2);
#define mixtype teleport_potion_test_mixtype
extern int teleport_potion_test_dip_ok(struct obj *obj);
#define dip_ok teleport_potion_test_dip_ok
extern int teleport_potion_test_dip_hands_ok(struct obj *obj);
#define dip_hands_ok teleport_potion_test_dip_hands_ok
extern void teleport_potion_test_hold_potion(
    struct obj *potobj,
    const char *drop_fmt, const char *drop_arg,
    const char *hold_msg);
#define hold_potion teleport_potion_test_hold_potion
extern void teleport_potion_test_poof(struct obj *potion);
#define poof teleport_potion_test_poof
extern boolean teleport_potion_test_dip_potion_explosion(struct obj *obj, int dmg);
#define dip_potion_explosion teleport_potion_test_dip_potion_explosion
extern int teleport_potion_test_potion_dip(struct obj *obj, struct obj *potion);
#define potion_dip teleport_potion_test_potion_dip
#endif
#include "tu-potion-layout.h"

static struct monst*actor(long i){return i==-2?&gy.youmonst:i>=0&&i<nmon?monsters[i]:NULL;}static struct obj*item(long i){return i==-2?&hands_obj:i>=0&&i<nobj?nodes[i]:NULL;}static char resultbuf[BUFSZ];static struct monst*moncell;
void probe_reset(unsigned initial){int i,x,y;for(i=0;i<nobj;i++)free(nodes[i]);for(i=0;i<nmon;i++)free(monsters[i]);if(growth)free(growth);growth=NULL;nmon=nobj=nr=ri=0;seed=initial;memset(nodes,0,sizeof nodes);memset(monsters,0,sizeof monsters);memset(opts,0,sizeof opts);memset(ret,0,sizeof ret);memset(cells,0,sizeof cells);memset(fake_bytes,0,sizeof fake_bytes);fake_calls=0;memset(&u,0,sizeof u);memset(&svc,0,sizeof svc);memset(&svm,0,sizeof svm);memset(&svl,0,sizeof svl);memset(&gy,0,sizeof gy);memset(&gv,0,sizeof gv);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&gi,0,sizeof gi);memset(&gp,0,sizeof gp);memset(&gu,0,sizeof gu);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&hands_obj,0,sizeof hands_obj);memset(&killer_record,0,sizeof killer_record);moncell=NULL;objects_globals_init();monst_globals_init();for(i=0;i<NUM_OBJECTS;i++)objects[i].oc_name_idx=objects[i].oc_descr_idx=i;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;vision[y][x]=IN_SIGHT|COULD_SEE;}for(y=0;y<ROWNO;y++)visionrows[y]=vision[y];gv.viz_array=visionrows;u.ux=10;u.uy=10;u.uz.dnum=1;u.uz.dlevel=2;u.uhp=50;u.uhpmax=100;u.uen=30;u.uenmax=50;u.mh=50;u.mhmax=100;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;u.ulevel=10;u.ulevelmax=15;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=gy.youmonst.mhpmax=100;gy.youmonst.mcansee=gy.youmonst.mcanmove=1;for(i=0;i<A_MAX;i++){u.acurr.a[i]=10;u.amax.a[i]=15;gu.urace.attrmax[i]=18;gu.urace.attrmin[i]=3;}flags.verbose=1;opts[0]=1;opts[4]=1;opts[11]=-1;opts[120]=opts[121]=opts[122]=-1;uwep=uarm=uarmg=uarmh=uarmf=uarmc=uarmu=ublindf=uamul=uswapwep=uball=uchain=NULL;resultbuf[0]=tracebuf[0]=caller[0]=0;
ret[1]=-1;ret[3]=-1;ret[4]=-1;ret[5]=-1;ret[6]=-1;ret[7]=-1;ret[11]=-1;ret[12]=-1;ret[15]=-1;ret[19]=-1;ret[21]=-1;ret[22]=-1;ret[23]=-1;ret[26]=-1;ret[35]=-1;ret[46]=-1;ret[47]=-1;ret[55]=-1;ret[59]=-1;ret[62]=-1;ret[63]=-1;ret[64]=-1;ret[70]=-1;ret[71]=-1;ret[75]=-1;ret[76]=-1;ret[79]=-1;ret[99]=-1;ret[104]=-1;ret[111]=-1;ret[119]=-1;ret[120]=-1;ret[123]=-1;ret[125]=-1;ret[126]=-1;ret[129]=-1;ret[132]=-1;ret[133]=-1;ret[142]=-1;ret[147]=-1;ret[148]=-1;ret[149]=-1;ret[150]=-1;ret[151]=-1;}
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
void probe_mon_bit(int slot,int field,unsigned v){struct monst*o=actor(slot);switch(field){case 0:o->mblinded=v;break;case 1:o->mcanmove=v;break;case 2:o->mcansee=v;break;case 3:o->mconf=v;break;case 4:o->minvis=v;break;case 5:o->mpeaceful=v;break;case 6:o->msleeping=v;break;}}
void probe_obj_bit(int slot,int field,unsigned v){struct obj*o=item(slot);switch(field){case 0:o->bknown=v;break;case 1:o->blessed=v;break;case 2:o->cursed=v;break;case 3:o->dknown=v;break;case 4:o->in_use=v;break;case 5:o->lamplit=v;break;case 6:o->oeroded=v;break;case 7:o->oeroded2=v;break;case 8:o->otrapped=v;break;case 9:o->pickup_prev=v;break;case 10:o->unpaid=v;break;}}
long probe_action(int op,long a,long b,long c,long d){switch(op){case 0:return itimeout(a);case 1:return itimeout_incr(a,b);case 2:set_itimeout(&cells[0],b);break;case 3:incr_itimeout(&cells[0],b);break;case 4:make_confused(a,b);break;case 5:make_stunned(a,b);break;case 6:make_sick(a,opts[33]?NULL:"fixture reason",c,d);break;case 7:make_slimed(a,opts[33]?NULL:"fixture reason");break;case 8:make_stoned(a,opts[33]?NULL:"fixture reason",c,opts[33]?NULL:"fixture reason");break;case 9:make_vomiting(a,b);break;case 10:make_blinded(a,b);break;case 11:toggle_blindness();break;case 12:return make_hallucinated(a,b,c);case 13:make_deaf(a,b);break;case 14:make_glib(a);break;case 15:self_invis_message();break;case 16:ghost_from_bottle();break;case 17:return drink_ok(item(a));case 18:return dodrink();case 19:return dopotion(item(a));case 20:peffect_restore_ability(item(a));break;case 21:peffect_hallucination(item(a));break;case 22:peffect_water(item(a));break;case 23:peffect_booze(item(a));break;case 24:peffect_enlightenment(item(a));break;case 25:peffect_invisibility(item(a));break;case 26:peffect_see_invisible(item(a));break;case 27:peffect_paralysis(item(a));break;case 28:peffect_sleeping(item(a));break;case 29:return peffect_monster_detection(item(a));case 30:return peffect_object_detection(item(a));case 31:peffect_sickness(item(a));break;case 32:peffect_confusion(item(a));break;case 33:peffect_gain_ability(item(a));break;case 34:peffect_speed(item(a));break;case 35:peffect_blindness(item(a));break;case 36:peffect_gain_level(item(a));break;case 37:peffect_healing(item(a));break;case 38:peffect_extra_healing(item(a));break;case 39:peffect_full_healing(item(a));break;case 40:peffect_levitation(item(a));break;case 41:peffect_gain_energy(item(a));break;case 42:peffect_oil(item(a));break;case 43:peffect_acid(item(a));break;case 44:peffect_polymorph(item(a));break;case 45:return peffects(item(a));case 46:healup(a,b,c,d);break;case 47:strange_feeling(item(a),opts[33]?NULL:"fixture reason");break;case 48:snprintf(resultbuf,sizeof resultbuf,"%s",bottlename());return 1;case 49:return H2Opotion_dip(item(a),item(b),c,opts[33]?NULL:"fixture reason");case 50:impact_arti_light(item(a),b,c);break;case 51:potionhit(actor(a),item(b),c);break;case 52:potionbreathe(item(a));break;case 53:return mixtype(item(a),item(b));case 54:return dip_ok(item(a));case 55:return dip_hands_ok(item(a));case 56:hold_potion(item(a),opts[33]?NULL:"fixture reason",opts[33]?NULL:"fixture reason",opts[33]?NULL:"fixture reason");break;case 57:return dodip();case 58:return dip_into();case 59:poof(item(a));break;case 60:return dip_potion_explosion(item(a),b);case 61:return potion_dip(item(a),item(b));case 62:mongrantswish(opts[32]?&u.ustuck:&moncell);break;case 63:djinni_from_bottle(item(a));break;case 64:return mid(split_mon(actor(a),actor(b)));case 65:speed_up(a);break;default:panic("bad action %d",op);}return 0;}
void*probe_pointer(int kind,int i){switch(kind){case 0:return &u;case 1:return actor(i);case 2:return item(i);case 3:return levl;case 4:return vision;case 5:return cells;case 6:return &gp;case 7:return &gm;case 8:return &disp;case 9:return &svc;case 10:return &gy.youmonst;case 11:return &gu;case 12:return &gn;case 13:return &moncell;case 14:return fake_bytes;default:return NULL;}}int probe_count(int k){return k?nobj:nmon;}long probe_scalar(int i){switch(i){case 0:return mid(moncell);case 1:return mid(u.ustuck);case 2:return mid(u.usteed);case 3:return oid(gi.invent);case 4:return gp.potion_unkn;case 5:return gp.potion_nothing;case 6:return gm.multi;case 7:return disp.botl;case 8:return gv.vision_full_recalc;case 9:return svc.context.mon_moving;case 10:return fake_calls;default:return 0;}}
