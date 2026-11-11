/* Controlled external world; unchanged configured mon.c supplies all policy. */
#include "hack.h"
#include "region.h"
#include "mfndpos.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
__typeof__(flags)flags;__typeof__(iflags)iflags;__typeof__(u)u;__typeof__(disp)disp;__typeof__(ga)ga;__typeof__(gb)gb;__typeof__(gd)gd;__typeof__(gi)gi;__typeof__(gl)gl;__typeof__(gm)gm;__typeof__(gn)gn;__typeof__(gp)gp;__typeof__(gs)gs;__typeof__(gt)gt;__typeof__(gu)gu;__typeof__(gv)gv;__typeof__(gy)gy;__typeof__(gz)gz;__typeof__(svc)svc;__typeof__(svd)svd;__typeof__(svk)svk;__typeof__(svl)svl;__typeof__(svm)svm;__typeof__(svq)svq;__typeof__(program_state)program_state;
const __typeof__(cg)cg={0};
const struct c_common_strings c_common_strings={.c_nothing_happens="Nothing happens.",.c_nothing_seems_to_happen="Nothing seems to happen.",.c_Something="Something",.c_something="something",.c_vision_clears="vision clears",.c_thats_enough_tries="That's enough tries!",.c_the_your={"the","your"}};
const struct c_color_names c_color_names={.c_black="black",.c_green="green",.c_red="red"};
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
const struct shclass shtypes[1]={{.name="shop"}};
struct obj*uwep,*uarm,*uarmg,*uarmh,*uarmf,*uarmc,*uarmu,*ublindf,*uamul,*uswapwep,*uball,*uchain,*uleft,*uright,*uquiver;struct obj hands_obj;
const struct Gender genders[4]={{.his="his",.he="he",.him="him"},{.his="her",.he="she",.him="her"},{.his="its",.he="it",.him="it"},{.his="their",.he="they",.him="them"}};
static struct monst*monsters[32];static struct obj*nodes[128];static seenV vision[ROWNO][COLNO],*visionrows[ROWNO];static int opts[160],rolls[4096],nr,ri,nmon,nobj;static unsigned seed;static long ret[512];static char tracebuf[1048576],caller[256];static void*growth;static long cells[8];static struct mfndposdata fixture_mfp;static struct trap fixture_trap;static stairway stairs;static NhRegion fixture_region;static struct engr fixture_engr;
static int mid(struct monst*m){int i;if(!m)return-1;if(m==&gy.youmonst)return-2;for(i=0;i<nmon;i++)if(m==monsters[i])return i;return-3;}
static int pidx(struct permonst*p){return p?p->pmidx:NON_PM;}
static int oid(struct obj*o){int i;if(!o)return-1;if(o==&hands_obj)return-2;for(i=0;i<nobj;i++)if(o==nodes[i])return i;return-3;}
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static struct obj*fixture_object(int typ){struct obj*o=calloc(1,sizeof *o);if(nobj>=128)abort();nodes[nobj]=o;o->o_id=++nobj;o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;o->owt=objects[typ].oc_weight;o->where=OBJ_FREE;o->corpsenm=NON_PM;return o;}
static void fixture_floor(struct obj*o,coordxy x,coordxy y){o->where=OBJ_FLOOR;o->ox=x;o->oy=y;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;o->nobj=fobj;fobj=o;}
static void callback(int n){if(opts[120]==n&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("grow:%d;",n);}if(opts[121]==n){u.uprops[HALF_PHDAM].intrinsic^=FROMOUTSIDE;logmsg("fliphalf;");}if(opts[122]==n&&nmon){monsters[0]->mpeaceful=!monsters[0]->mpeaceful;logmsg("flippeaceful;");}if(opts[123]==n&&nmon){logmsg("live_ustuck:%d;",mid(u.ustuck));}if(opts[125]==n&&!opts[126]&&nmon){opts[126]=1;healmon(monsters[0],1,0);logmsg("reenter:%d;",n);}}
void panic(const char*f,...){va_list ap;va_start(ap,f);vfprintf(stderr,f,ap);va_end(ap);abort();}
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char*f,int line,const char*fn){snprintf(caller,sizeof caller,"%s:%d:%s",f,line,fn);}
static int draw(int n){unsigned v;if(n<=0)panic("bad rng %d",n);seed=seed*1664525U+1013904223U;v=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;logmsg("rng:%d:%u@%s;",n,v,caller);callback(1);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}int(rnl)(int n){return draw(n);}int(d)(int n,int z){int t=0;while(n--)t+=draw(z)+1;return t;}
int rn2_on_display_rng(int n){logmsg("displayrng;");return draw(n);}
void paniclog(const char*a,const char*b){logmsg("paniclog:%s:%s;",a,b);}
static void display(winid w,boolean b){logmsg("display:%d:%d;",w,b);}__typeof__(windowprocs)windowprocs={.win_display_nhwindow=display};winid WIN_MESSAGE=1;
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean unconscious(void){return opts[2];}boolean is_fainted(void){return opts[3];}schar acurr(int i){logmsg("attribute:%d;",i);return u.acurr.a[i];}

boolean is_pool(coordxy x,coordxy y){return isok(x,y)&&(levl[x][y].typ==POOL||levl[x][y].typ==MOAT||levl[x][y].typ==WATER);}

int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
char*distant_name(struct obj*o,char*(*fn)(struct obj*)){logmsg("distant_name:%d:%d;",oid(o),fn==doname?0:fn==xname?1:-1);return fn(o);}
void pline(const char*f,...){va_list ap;logmsg("pline:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void pline_The(const char*f,...){va_list ap;logmsg("pline_The:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void There(const char*f,...){va_list ap;logmsg("There:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You(const char*f,...){va_list ap;logmsg("You:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You_feel(const char*f,...){va_list ap;logmsg("You_feel:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You_hear(const char*f,...){va_list ap;logmsg("You_hear:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You_see(const char*f,...){va_list ap;logmsg("You_see:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void Your(const char*f,...){va_list ap;logmsg("Your:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You_cant(const char*f,...){va_list ap;logmsg("You_cant:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void verbalize(const char*f,...){va_list ap;logmsg("verbalize:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void impossible(const char*f,...){va_list ap;logmsg("impossible:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void raw_printf(const char*f,...){va_list ap;logmsg("raw_printf:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void pline_mon(struct monst*m,const char*f,...){va_list ap;logmsg("pline_mon:%d:",mid(m));va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void livelog_printf(long category,const char*f,...){va_list ap;logmsg("livelog:%ld:",category);va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
char * Amonnam(struct monst * a0){logmsg("Amonnam:%d:;",mid(a0));callback(20+0);return "Amonnam";}
boolean In_W_tower(coordxy a0,coordxy a1,d_level * a2){logmsg("In_W_tower:%d:%d:%d:;",(int)a0,(int)a1,a2!=NULL);callback(20+1);return (boolean)ret[1];}
boolean In_hell(d_level * a0){logmsg("In_hell:%d:;",a0!=NULL);callback(20+2);return (boolean)ret[2];}
boolean In_mines(d_level * a0){logmsg("In_mines:%d:;",a0!=NULL);callback(20+3);return (boolean)ret[3];}
int Mgender(struct monst * a0){logmsg("Mgender:%d:;",mid(a0));callback(20+4);return (int)ret[4];}
char * Monnam(struct monst * a0){logmsg("Monnam:%d:;",mid(a0));callback(20+5);return "Monnam";}
boolean On_W_tower_level(d_level * a0){logmsg("On_W_tower_level:%d:;",a0!=NULL);callback(20+6);return (boolean)ret[6];}
char * The(const char * a0){logmsg("The:%s:;",(a0?a0:"NULL"));callback(20+7);return "The";}
char * a_monnam(struct monst * a0){logmsg("a_monnam:%d:;",mid(a0));callback(20+8);return "a_monnam";}
boolean accessible(coordxy a0,coordxy a1){logmsg("accessible:%d:%d:;",(int)a0,(int)a1);callback(20+9);return (boolean)ret[9];}
struct obj * add_to_container(struct obj * a0,struct obj * a1){logmsg("add_to_container:%d:%d:;",oid(a0),oid(a1));callback(20+10);return ret[10]>=0&&ret[10]<nobj?nodes[ret[10]]:NULL;}
int add_to_minv(struct monst * a0,struct obj * a1){logmsg("add_to_minv:%d:%d:;",mid(a0),oid(a1));callback(20+11);return (int)ret[11];}
void adjalign(int a0){logmsg("adjalign:%d:;",(int)a0);callback(20+12);}
void aggravate(void){logmsg("aggravate:;");callback(20+13);}
char * an(const char * a0){logmsg("an:%s:;",(a0?a0:"NULL"));callback(20+14);return "an";}
char * ansimpleoname(struct obj * a0){logmsg("ansimpleoname:%d:;",oid(a0));callback(20+15);return "ansimpleoname";}
boolean any_light_source(void){logmsg("any_light_source:;");callback(20+16);return (boolean)ret[16];}
void artifact_exists(struct obj * a0,const char * a1,boolean a2,unsigned int a3){logmsg("artifact_exists:%d:%s:%d:%d:;",oid(a0),(a1?a1:"NULL"),(int)a2,(int)a3);callback(20+17);}
boolean bad_rock(struct permonst * a0,coordxy a1,coordxy a2){logmsg("bad_rock:%d:%d:%d:;",a0?a0->pmidx:-1,(int)a1,(int)a2);callback(20+18);return (boolean)ret[18];}
const char * body_part(int a0){logmsg("body_part:%d:;",(int)a0);callback(20+19);return "body_part";}
struct obj * bury_an_obj(struct obj * a0,boolean * a1){logmsg("bury_an_obj:%d:%d:;",oid(a0),a1!=NULL);callback(20+20);if(a1)*a1=(boolean)opts[154];return ret[20]>=0&&ret[20]<nobj?nodes[ret[20]]:NULL;}
void bypass_obj(struct obj * a0){logmsg("bypass_obj:%d:;",oid(a0));callback(20+21);}
boolean can_fog(struct monst * a0){logmsg("can_fog:%d:;",mid(a0));callback(20+22);return (boolean)ret[22];}
boolean can_hide_under_obj(struct obj * a0){logmsg("can_hide_under_obj:%d:;",oid(a0));callback(20+23);return (boolean)ret[23];}
int canseemon(struct monst * a0){logmsg("canseemon:%d:;",mid(a0));callback(20+24);return (int)ret[24];}
int cant_squeeze_thru(struct monst * a0){logmsg("cant_squeeze_thru:%d:;",mid(a0));callback(20+25);return (int)ret[25];}
void change_luck(schar a0){logmsg("change_luck:%d:;",(int)a0);callback(20+26);}
void clear_bypasses(void){logmsg("clear_bypasses:;");callback(20+27);}
void clear_dknown(struct obj * a0){logmsg("clear_dknown:%d:;",oid(a0));callback(20+28);}
void clear_splitobjs(void){logmsg("clear_splitobjs:;");callback(20+29);}
boolean closed_door(coordxy a0,coordxy a1){logmsg("closed_door:%d:%d:;",(int)a0,(int)a1);callback(20+30);return (boolean)ret[30];}
boolean control_mon_tele(struct monst * a0,coord * a1,unsigned int a2,boolean a3){logmsg("control_mon_tele:%d:%d:%d:%d:;",mid(a0),a1!=NULL,(int)a2,(int)a3);callback(20+31);return (boolean)ret[31];}
char * coord_desc(coordxy a0,coordxy a1,char * a2,char a3){logmsg("coord_desc:%d:%d:%d:%d:;",(int)a0,(int)a1,a2!=NULL,(int)a3);callback(20+32);strcpy(a2,"fixture coordinate");return a2;}
int corpse_intrinsic(struct permonst * a0){logmsg("corpse_intrinsic:%d:;",a0?a0->pmidx:-1);callback(20+33);return (int)ret[33];}
boolean could_reach_item(struct monst * a0,coordxy a1,coordxy a2){logmsg("could_reach_item:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+34);return (boolean)ret[34];}
int count_wsegs(struct monst * a0){logmsg("count_wsegs:%d:;",mid(a0));callback(20+35);return (int)ret[35];}
NhRegion * create_gas_cloud(coordxy a0,coordxy a1,int a2,int a3){logmsg("create_gas_cloud:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+36);return ret[36]>=0?&fixture_region:NULL;}
boolean cursed_object_at(coordxy a0,coordxy a1){logmsg("cursed_object_at:%d:%d:;",(int)a0,(int)a1);callback(20+37);return (boolean)ret[37];}
boolean debugcore(const char * a0,boolean a1){logmsg("debugcore:%s:%d:;",(a0?a0:"NULL"),(int)a1);callback(20+38);return (boolean)ret[38];}
void deferred_goto(void){logmsg("deferred_goto:;");callback(20+39);}
void del_engr_at(coordxy a0,coordxy a1){logmsg("del_engr_at:%d:%d:;",(int)a0,(int)a1);callback(20+40);}
void del_light_source(int a0,union any * a1){logmsg("del_light_source:%d:%d:;",(int)a0,a1!=NULL);callback(20+41);}
void delobj(struct obj * a0){logmsg("delobj:%d:;",oid(a0));callback(20+42);}
int describe_level(char * a0,int a1){logmsg("describe_level:%d:%d:;",a0!=NULL,(int)a1);callback(20+43);strcpy(a0,"fixture level");return 0;}
void discard_minvent(struct monst * a0,boolean a1){logmsg("discard_minvent:%d:%d:;",mid(a0),(int)a1);callback(20+44);}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+45);}
void dismount_steed(int a0){logmsg("dismount_steed:%d:;",(int)a0);callback(20+46);}
void disturb_buried_zombies(coordxy a0,coordxy a1){logmsg("disturb_buried_zombies:%d:%d:;",(int)a0,(int)a1);callback(20+47);}
int dochugw(struct monst * a0,boolean a1){logmsg("dochugw:%d:%d:;",mid(a0),(int)a1);callback(20+48);return (int)ret[48];}
void docrt(void){logmsg("docrt:;");callback(20+49);}
int does_block(int a0,int a1,struct rm * a2){logmsg("does_block:%d:%d:%d:;",(int)a0,(int)a1,a2!=NULL);callback(20+50);return (int)ret[50];}
char * doname(struct obj * a0){logmsg("doname:%d:;",oid(a0));callback(20+51);return "doname";}
void dryup(coordxy a0,coordxy a1,boolean a2){logmsg("dryup:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+52);}
void end_burn(struct obj * a0,boolean a1){logmsg("end_burn:%d:%d:;",oid(a0),(int)a1);callback(20+53);}
boolean enexto(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){logmsg("enexto:%d:%d:%d:%d:;",a0!=NULL,(int)a1,(int)a2,a3?a3->pmidx:-1);callback(20+54);return (boolean)ret[54];}
void expels(struct monst * a0,struct permonst * a1,boolean a2){logmsg("expels:%d:%d:%d:;",mid(a0),a1?a1->pmidx:-1,(int)a2);callback(20+55);}
int experience(struct monst * a0,int a1){logmsg("experience:%d:%d:;",mid(a0),(int)a1);callback(20+56);return (int)ret[56];}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logmsg("explode:%d:%d:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);callback(20+57);}
void extract_from_minvent(struct monst * a0,struct obj * a1,boolean a2,boolean a3){logmsg("extract_from_minvent:%d:%d:%d:%d:;",mid(a0),oid(a1),(int)a2,(int)a3);callback(20+58);}
int fightm(struct monst * a0){logmsg("fightm:%d:;",mid(a0));callback(20+59);return (int)ret[59];}
void fill_pit(coordxy a0,coordxy a1){logmsg("fill_pit:%d:%d:;",(int)a0,(int)a1);callback(20+60);}
void finish_meating(struct monst * a0){logmsg("finish_meating:%d:;",mid(a0));callback(20+61);}
int fire_damage_chain(struct obj * a0,boolean a1,boolean a2,coordxy a3,coordxy a4){logmsg("fire_damage_chain:%d:%d:%d:%d:%d:;",oid(a0),(int)a1,(int)a2,(int)a3,(int)a4);callback(20+62);return (int)ret[62];}
void flash_glyph_at(coordxy a0,coordxy a1,int a2,int a3){logmsg("flash_glyph_at:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+63);}
boolean flooreffects(struct obj * a0,coordxy a1,coordxy a2,const char * a3){logmsg("flooreffects:%d:%d:%d:%s:;",oid(a0),(int)a1,(int)a2,(a3?a3:"NULL"));callback(20+64);return (boolean)ret[64];}
void free_mgivenname(struct monst * a0){logmsg("free_mgivenname:%d:;",mid(a0));callback(20+65);if(a0->mextra&&a0->mextra->mgivenname){free(a0->mextra->mgivenname);a0->mextra->mgivenname=NULL;}}
void freemcorpsenm(struct monst * a0){logmsg("freemcorpsenm:%d:;",mid(a0));callback(20+66);}
struct obj * g_at(coordxy a0,coordxy a1){logmsg("g_at:%d:%d:;",(int)a0,(int)a1);callback(20+67);return ret[67]>=0&&ret[67]<nobj?nodes[ret[67]]:NULL;}
int gazemu(struct monst * a0,struct attack * a1){logmsg("gazemu:%d:%d:;",mid(a0),a1!=NULL);callback(20+68);return (int)ret[68];}
int gd_move(struct monst * a0){logmsg("gd_move:%d:;",mid(a0));callback(20+69);return (int)ret[69];}
struct obj * get_mleash(struct monst * a0){logmsg("get_mleash:%d:;",mid(a0));callback(20+70);return ret[70]>=0&&ret[70]<nobj?nodes[ret[70]]:NULL;}
int get_wormno(void){logmsg("get_wormno:;");callback(20+71);return (int)ret[71];}
void getlin(const char * a0,char * a1){logmsg("getlin:%s:%d:;",(a0?a0:"NULL"),a1!=NULL);callback(20+72);strcpy(a1,opts[150]==1?"human":opts[150]==2?"random":"\033");}
void ghod_hitsu(struct monst * a0){logmsg("ghod_hitsu:%d:;",mid(a0));callback(20+73);}
boolean goodpos(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){logmsg("goodpos:%d:%d:%d:%d:;",(int)a0,(int)a1,mid(a2),(int)a3);callback(20+74);return (boolean)ret[74];}
boolean grddead(struct monst * a0){logmsg("grddead:%d:;",mid(a0));callback(20+75);return (boolean)ret[75];}
struct permonst * grow_up(struct monst * a0,struct monst * a1){logmsg("grow_up:%d:%d:;",mid(a0),mid(a1));callback(20+76);return a0->data;}
void growl(struct monst * a0){logmsg("growl:%d:;",mid(a0));callback(20+77);}
boolean has_ceiling(d_level * a0){logmsg("has_ceiling:%d:;",a0!=NULL);callback(20+78);return (boolean)ret[78];}
boolean hastrack(coordxy a0,coordxy a1){logmsg("hastrack:%d:%d:;",(int)a0,(int)a1);callback(20+79);return (boolean)ret[79];}
void healup(int a0,int a1,boolean a2,boolean a3){logmsg("healup:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+80);}
const char * hliquid(const char * a0){logmsg("hliquid:%s:;",(a0?a0:"NULL"));callback(20+81);return "hliquid";}
void hot_pursuit(struct monst * a0){logmsg("hot_pursuit:%d:;",mid(a0));callback(20+82);}
char * in_rooms(coordxy a0,coordxy a1,int a2){logmsg("in_rooms:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+83);static char roomlist[5];roomlist[0]=(char)opts[151];roomlist[1]=0;return roomlist;}
boolean in_your_sanctuary(struct monst * a0,coordxy a1,coordxy a2){logmsg("in_your_sanctuary:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+84);return (boolean)ret[84];}
int inhishop(struct monst * a0){logmsg("inhishop:%d:;",mid(a0));callback(20+85);return (int)ret[85];}
void initworm(struct monst * a0,int a1){logmsg("initworm:%d:%d:;",mid(a0),(int)a1);callback(20+86);}
boolean is_home_elemental(struct permonst * a0){logmsg("is_home_elemental:%d:;",a0?a0->pmidx:-1);callback(20+87);return (boolean)ret[87];}
boolean is_lava(coordxy a0,coordxy a1){logmsg("is_lava:%d:%d:;",(int)a0,(int)a1);callback(20+88);return (boolean)ret[88];}
boolean is_pool_or_lava(coordxy a0,coordxy a1){logmsg("is_pool_or_lava:%d:%d:;",(int)a0,(int)a1);callback(20+89);return (boolean)ret[89];}
boolean is_waterwall(coordxy a0,coordxy a1){logmsg("is_waterwall:%d:%d:;",(int)a0,(int)a1);callback(20+90);return (boolean)ret[90];}
void kill_egg(struct obj * a0){logmsg("kill_egg:%d:;",oid(a0));callback(20+91);}
void leaddead(void){logmsg("leaddead:;");callback(20+92);}
boolean leashable(struct monst * a0){logmsg("leashable:%d:;",mid(a0));callback(20+93);return (boolean)ret[93];}
xint16 ledger_no(d_level * a0){logmsg("ledger_no:%d:;",a0!=NULL);callback(20+94);return (xint16)ret[94];}
xint16 level_difficulty(void){logmsg("level_difficulty:;");callback(20+95);return (xint16)ret[95];}
void losehp(int a0,const char * a1,schar a2){logmsg("losehp:%d:%s:%d:;",(int)a0,(a1?a1:"NULL"),(int)a2);callback(20+96);}
boolean m_can_break_boulder(struct monst * a0){logmsg("m_can_break_boulder:%d:;",mid(a0));callback(20+97);return (boolean)ret[97];}
struct obj * m_carrying(struct monst * a0,int a1){logmsg("m_carrying:%d:%d:;",mid(a0),(int)a1);callback(20+98);return ret[98]>=0&&ret[98]<nobj?nodes[ret[98]]:NULL;}
void m_dowear(struct monst * a0,boolean a1){logmsg("m_dowear:%d:%d:;",mid(a0),(int)a1);callback(20+99);}
void m_everyturn_effect(struct monst * a0){logmsg("m_everyturn_effect:%d:;",mid(a0));callback(20+100);}
boolean m_harmless_trap(struct monst * a0,struct trap * a1){logmsg("m_harmless_trap:%d:%d:;",mid(a0),a1!=NULL);callback(20+101);return (boolean)ret[101];}
char * m_monnam(struct monst * a0){logmsg("m_monnam:%d:;",mid(a0));callback(20+102);return "m_monnam";}
void m_unleash(struct monst * a0,boolean a1){logmsg("m_unleash:%d:%d:;",mid(a0),(int)a1);callback(20+103);}
void m_useup(struct monst * a0,struct obj * a1){logmsg("m_useup:%d:%d:;",mid(a0),oid(a1));callback(20+104);}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logmsg("makemon:%d:%d:%d:%d:;",a0?a0->pmidx:-1,(int)a1,(int)a2,(int)a3);callback(20+105);return ret[105]==-2?&gy.youmonst:ret[105]>=0&&ret[105]<nmon?monsters[ret[105]]:NULL;}
char * makeplural(const char * a0){logmsg("makeplural:%s:;",(a0?a0:"NULL"));callback(20+106);return "makeplural";}
boolean may_dig(coordxy a0,coordxy a1){logmsg("may_dig:%d:%d:;",(int)a0,(int)a1);callback(20+107);return (boolean)ret[107];}
boolean may_passwall(coordxy a0,coordxy a1){logmsg("may_passwall:%d:%d:;",(int)a0,(int)a1);callback(20+108);return (boolean)ret[108];}
const char * maybe_gasp(struct monst * a0){logmsg("maybe_gasp:%d:;",mid(a0));callback(20+109);return "maybe_gasp";}
boolean mb_trapped(struct monst * a0,boolean a1){logmsg("mb_trapped:%d:%d:;",mid(a0),(int)a1);callback(20+110);return (boolean)ret[110];}
int mbirth_limit(int a0){logmsg("mbirth_limit:%d:;",(int)a0);callback(20+111);return (int)ret[111];}
void mcureblindness(struct monst * a0,boolean a1){logmsg("mcureblindness:%d:%d:;",mid(a0),(int)a1);callback(20+112);}
void mdrop_special_objs(struct monst * a0){logmsg("mdrop_special_objs:%d:;",mid(a0));callback(20+113);}
void migrate_to_level(struct monst * a0,xint16 a1,xint16 a2,coord * a3){logmsg("migrate_to_level:%d:%d:%d:%d:;",mid(a0),(int)a1,(int)a2,a3!=NULL);callback(20+114);}
char * minimal_monnam(struct monst * a0,boolean a1){logmsg("minimal_monnam:%d:%d:;",mid(a0),(int)a1);callback(20+115);return "minimal_monnam";}
int mkclass_poly(int a0){logmsg("mkclass_poly:%d:;",(int)a0);callback(20+116);return (int)ret[116];}
struct obj * mkcorpstat(int a0,struct monst * a1,struct permonst * a2,coordxy a3,coordxy a4,unsigned int a5){logmsg("mkcorpstat:%d:%d:%d:%d:%d:%d:;",(int)a0,mid(a1),a2?a2->pmidx:-1,(int)a3,(int)a4,(int)a5);callback(20+117);struct obj*o=fixture_object(a0);o->corpsenm=a2?a2->pmidx:NON_PM;fixture_floor(o,a3,a4);return o;}
struct obj * mkgold(long a0,coordxy a1,coordxy a2){logmsg("mkgold:%ld:%d:%d:;",(long)a0,(int)a1,(int)a2);callback(20+118);struct obj*o=fixture_object(GOLD_PIECE);o->quan=a0;fixture_floor(o,a1,a2);return o;}
struct obj * mkobj(int a0,boolean a1){logmsg("mkobj:%d:%d:;",(int)a0,(int)a1);callback(20+119);return fixture_object(ROCK);}
struct obj * mksobj_at(int a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logmsg("mksobj_at:%d:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4);callback(20+120);struct obj*o=fixture_object(a0);fixture_floor(o,a1,a2);return o;}
void mon_adjust_speed(struct monst * a0,int a1,struct obj * a2){logmsg("mon_adjust_speed:%d:%d:%d:;",mid(a0),(int)a1,oid(a2));callback(20+121);}
void mon_break_armor(struct monst * a0,boolean a1){logmsg("mon_break_armor:%d:%d:;",mid(a0),(int)a1);callback(20+122);}
void mon_explodes(struct monst * a0,struct attack * a1){logmsg("mon_explodes:%d:%d:;",mid(a0),a1!=NULL);callback(20+123);}
int mon_has_amulet(struct monst * a0){logmsg("mon_has_amulet:%d:;",mid(a0));callback(20+124);return (int)ret[124];}
int mon_has_special(struct monst * a0){logmsg("mon_has_special:%d:;",mid(a0));callback(20+125);return (int)ret[125];}
char * mon_nam(struct monst * a0){logmsg("mon_nam:%d:;",mid(a0));callback(20+126);return "mon_nam";}
const char * mon_pmname(struct monst * a0){logmsg("mon_pmname:%d:;",mid(a0));callback(20+127);return "mon_pmname";}
void mon_regen(struct monst * a0,boolean a1){logmsg("mon_regen:%d:%d:;",mid(a0),(int)a1);callback(20+128);}
void mon_set_minvis(struct monst * a0,boolean a1){logmsg("mon_set_minvis:%d:%d:;",mid(a0),(int)a1);callback(20+129);}
void mon_track_clear(struct monst * a0){logmsg("mon_track_clear:%d:;",mid(a0));callback(20+130);}
boolean mon_would_take_item(struct monst * a0,struct obj * a1){logmsg("mon_would_take_item:%d:%d:;",mid(a0),oid(a1));callback(20+131);return (boolean)ret[131];}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){logmsg("monflee:%d:%d:%d:%d:;",mid(a0),(int)a1,(int)a2,(int)a3);callback(20+132);}
boolean monhaskey(struct monst * a0,boolean a1){logmsg("monhaskey:%d:%d:;",mid(a0),(int)a1);callback(20+133);return (boolean)ret[133];}
anything * monst_to_any(struct monst * a0){logmsg("monst_to_any:%d:;",mid(a0));callback(20+134);return NULL;}
void more_experienced(int a0,int a1){logmsg("more_experienced:%d:%d:;",(int)a0,(int)a1);callback(20+135);}
int mpickobj(struct monst * a0,struct obj * a1){logmsg("mpickobj:%d:%d:;",mid(a0),oid(a1));callback(20+136);return (int)ret[136];}
void mselftouch(struct monst * a0,const char * a1,boolean a2){logmsg("mselftouch:%d:%s:%d:;",mid(a0),(a1?a1:"NULL"),(int)a2);callback(20+137);}
void nemdead(void){logmsg("nemdead:;");callback(20+138);}
void nemesis_stinks(coordxy a0,coordxy a1){logmsg("nemesis_stinks:%d:%d:;",(int)a0,(int)a1);callback(20+139);}
void new_light_source(coordxy a0,coordxy a1,int a2,int a3,union any * a4){logmsg("new_light_source:%d:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3,a4!=NULL);callback(20+140);}
void new_mgivenname(struct monst * a0,int a1){logmsg("new_mgivenname:%d:%d:;",mid(a0),(int)a1);callback(20+141);if(!a0->mextra){a0->mextra=calloc(1,sizeof *a0->mextra);a0->mextra->mcorpsenm=NON_PM;}a0->mextra->mgivenname=calloc(1,a1);}
void new_were(struct monst * a0){logmsg("new_were:%d:;",mid(a0));callback(20+142);}
void newebones(struct monst * a0){logmsg("newebones:%d:;",mid(a0));callback(20+143);if(!a0->mextra){a0->mextra=calloc(1,sizeof *a0->mextra);a0->mextra->mcorpsenm=NON_PM;}if(!a0->mextra->ebones)a0->mextra->ebones=calloc(1,sizeof *a0->mextra->ebones);}
void newedog(struct monst * a0){logmsg("newedog:%d:;",mid(a0));callback(20+144);if(!a0->mextra){a0->mextra=calloc(1,sizeof *a0->mextra);a0->mextra->mcorpsenm=NON_PM;}if(!a0->mextra->edog)a0->mextra->edog=calloc(1,sizeof *a0->mextra->edog);}
void newegd(struct monst * a0){logmsg("newegd:%d:;",mid(a0));callback(20+145);if(!a0->mextra){a0->mextra=calloc(1,sizeof *a0->mextra);a0->mextra->mcorpsenm=NON_PM;}if(!a0->mextra->egd)a0->mextra->egd=calloc(1,sizeof *a0->mextra->egd);}
void newemin(struct monst * a0){logmsg("newemin:%d:;",mid(a0));callback(20+146);if(!a0->mextra){a0->mextra=calloc(1,sizeof *a0->mextra);a0->mextra->mcorpsenm=NON_PM;}if(!a0->mextra->emin)a0->mextra->emin=calloc(1,sizeof *a0->mextra->emin);}
void newepri(struct monst * a0){logmsg("newepri:%d:;",mid(a0));callback(20+147);if(!a0->mextra){a0->mextra=calloc(1,sizeof *a0->mextra);a0->mextra->mcorpsenm=NON_PM;}if(!a0->mextra->epri)a0->mextra->epri=calloc(1,sizeof *a0->mextra->epri);}
void neweshk(struct monst * a0){logmsg("neweshk:%d:;",mid(a0));callback(20+148);if(!a0->mextra){a0->mextra=calloc(1,sizeof *a0->mextra);a0->mextra->mcorpsenm=NON_PM;}if(!a0->mextra->eshk)a0->mextra->eshk=calloc(1,sizeof *a0->mextra->eshk);}
void newexplevel(void){logmsg("newexplevel:;");callback(20+149);}
struct mextra * newmextra(void){logmsg("newmextra:;");callback(20+150);struct mextra*x=calloc(1,sizeof *x);x->mcorpsenm=NON_PM;return x;}
void newmonhp(struct monst * a0,int a1){logmsg("newmonhp:%d:%d:;",mid(a0),(int)a1);callback(20+151);a0->mhp=a0->mhpmax=opts[153]?opts[153]:40;a0->m_lev=mons[a1].mlevel;}
void newsym(coordxy a0,coordxy a1){logmsg("newsym:%d:%d:;",(int)a0,(int)a1);callback(20+152);}
char * noit_mon_nam(struct monst * a0){logmsg("noit_mon_nam:%d:;",mid(a0));callback(20+153);return "noit_mon_nam";}
char * noname_monnam(struct monst * a0,int a1){logmsg("noname_monnam:%d:%d:;",mid(a0),(int)a1);callback(20+154);return "noname_monnam";}
boolean noteleport_level(struct monst * a0){logmsg("noteleport_level:%d:;",mid(a0));callback(20+155);return (boolean)ret[155];}
struct obj * nxtobj(struct obj * a0,int a1,boolean a2){logmsg("nxtobj:%d:%d:%d:;",oid(a0),(int)a1,(int)a2);callback(20+156);return ret[156]>=0&&ret[156]<nobj?nodes[ret[156]]:NULL;}
void obj_extract_self(struct obj * a0){logmsg("obj_extract_self:%d:;",oid(a0));callback(20+157);}
struct obj * obj_meld(struct obj ** a0,struct obj ** a1){logmsg("obj_meld:%d:%d:;",oid(*a0),oid(*a1));callback(20+158);if(opts[155]){*a0=nodes[1];*a1=nodes[0];ret[159]=-1;}return opts[155]?*a0:(ret[158]>=0&&ret[158]<nobj?nodes[ret[158]]:NULL);}
struct obj * obj_nexto(struct obj * a0){logmsg("obj_nexto:%d:;",oid(a0));callback(20+159);return ret[159]>=0&&ret[159]<nobj?nodes[ret[159]]:NULL;}
boolean obj_resists(struct obj * a0,int a1,int a2){logmsg("obj_resists:%d:%d:%d:;",oid(a0),(int)a1,(int)a2);callback(20+160);return (boolean)ret[160];}
boolean objdescr_is(struct obj * a0,const char * a1){logmsg("objdescr_is:%d:%s:;",oid(a0),(a1?a1:"NULL"));callback(20+161);return (boolean)ret[161];}
struct obj * oname(struct obj * a0,const char * a1,unsigned int a2){logmsg("oname:%d:%s:%d:;",oid(a0),(a1?a1:"NULL"),(int)a2);callback(20+162);return a0;}
boolean onscary(coordxy a0,coordxy a1,struct monst * a2){logmsg("onscary:%d:%d:%d:;",(int)a0,(int)a1,mid(a2));callback(20+163);return (boolean)ret[163];}
boolean p_coaligned(struct monst * a0){logmsg("p_coaligned:%d:;",mid(a0));callback(20+164);return (boolean)ret[164];}
int pick_nasty(int a0){logmsg("pick_nasty:%d:;",(int)a0);callback(20+165);return (int)ret[165];}
void place_monster(struct monst * a0,coordxy a1,coordxy a2){logmsg("place_monster:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+166);}
void place_object(struct obj * a0,coordxy a1,coordxy a2){logmsg("place_object:%d:%d:%d:;",oid(a0),(int)a1,(int)a2);callback(20+167);}
void place_worm_tail_randomly(struct monst * a0,coordxy a1,coordxy a2){logmsg("place_worm_tail_randomly:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+168);}
void place_wsegs(struct monst * a0,struct monst * a1){logmsg("place_wsegs:%d:%d:;",mid(a0),mid(a1));callback(20+169);}
void placebc(void){logmsg("placebc:;");callback(20+170);}
const char * pmname(struct permonst * a0,int a1){logmsg("pmname:%d:%d:;",a0?a0->pmidx:-1,(int)a1);callback(20+171);return "pmname";}
void poly_steed(struct monst * a0,struct permonst * a1){logmsg("poly_steed:%d:%d:;",mid(a0),a1?a1->pmidx:-1);callback(20+172);}
void possibly_unwield(struct monst * a0,boolean a1){logmsg("possibly_unwield:%d:%d:;",mid(a0),(int)a1);callback(20+173);}
void pudding_merge_message(struct obj * a0,struct obj * a1){logmsg("pudding_merge_message:%d:%d:;",oid(a0),oid(a1));callback(20+174);}
short quest_info(int a0){logmsg("quest_info:%d:;",(int)a0);callback(20+175);return (short)ret[175];}
void quickmimic(struct monst * a0){logmsg("quickmimic:%d:;",mid(a0));callback(20+176);}
void recalc_block_point(coordxy a0,coordxy a1){logmsg("recalc_block_point:%d:%d:;",(int)a0,(int)a1);callback(20+177);}
void record_achievement(schar a0){logmsg("record_achievement:%d:;",(int)a0);callback(20+178);}
void relobj(struct monst * a0,int a1,boolean a2){logmsg("relobj:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+179);}
void remove_worm(struct monst * a0){logmsg("remove_worm:%d:;",mid(a0));callback(20+180);}
void removed_from_icebox(struct obj * a0){logmsg("removed_from_icebox:%d:;",oid(a0));callback(20+181);}
void replshk(struct monst * a0,struct monst * a1){logmsg("replshk:%d:%d:;",mid(a0),mid(a1));callback(20+182);}
boolean revive_corpse(struct obj * a0){logmsg("revive_corpse:%d:;",oid(a0));callback(20+183);return (boolean)ret[183];}
boolean rloc(struct monst * a0,unsigned int a1){logmsg("rloc:%d:%d:;",mid(a0),(int)a1);callback(20+184);return (boolean)ret[184];}
void rloc_to(struct monst * a0,coordxy a1,coordxy a2){logmsg("rloc_to:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+185);}
void rloc_to_flag(struct monst * a0,coordxy a1,coordxy a2,unsigned int a3){logmsg("rloc_to_flag:%d:%d:%d:%d:;",mid(a0),(int)a1,(int)a2,(int)a3);callback(20+186);}
const char * safe_oname(struct obj * a0){logmsg("safe_oname:%d:;",oid(a0));callback(20+187);return "safe_oname";}
void sanity_check_worm(struct monst * a0){logmsg("sanity_check_worm:%d:;",mid(a0));callback(20+188);}
void see_monsters(void){logmsg("see_monsters:;");callback(20+189);}
struct engr * sengr_at(const char * a0,coordxy a1,coordxy a2,boolean a3){logmsg("sengr_at:%s:%d:%d:%d:;",(a0?a0:"NULL"),(int)a1,(int)a2,(int)a3);callback(20+190);return ret[190]>=0?&fixture_engr:NULL;}
int sensemon(struct monst * a0){logmsg("sensemon:%d:;",mid(a0));callback(20+191);return (int)ret[191];}
void set_apparxy(struct monst * a0){logmsg("set_apparxy:%d:;",mid(a0));callback(20+192);}
void set_mimic_sym(struct monst * a0){logmsg("set_mimic_sym:%d:;",mid(a0));callback(20+193);}
void set_msg_xy(coordxy a0,coordxy a1){logmsg("set_msg_xy:%d:%d:;",(int)a0,(int)a1);callback(20+194);}
void shieldeff(coordxy a0,coordxy a1){logmsg("shieldeff:%d:%d:;",(int)a0,(int)a1);callback(20+195);}
void shkgone(struct monst * a0){logmsg("shkgone:%d:;",mid(a0));callback(20+196);}
boolean should_givit(int a0,struct permonst * a1){logmsg("should_givit:%d:%d:;",(int)a0,a1?a1->pmidx:-1);callback(20+197);return (boolean)ret[197];}
char * simple_typename(int a0){logmsg("simple_typename:%d:;",(int)a0);callback(20+198);return "simple_typename";}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){logmsg("sobj_at:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+199);return ret[199]>=0&&ret[199]<nobj?nodes[ret[199]]:NULL;}
struct monst * split_mon(struct monst * a0,struct monst * a1){logmsg("split_mon:%d:%d:;",mid(a0),mid(a1));callback(20+200);return ret[200]==-2?&gy.youmonst:ret[200]>=0&&ret[200]<nmon?monsters[ret[200]]:NULL;}
struct obj * splitobj(struct obj * a0,long a1){logmsg("splitobj:%d:%ld:;",oid(a0),(long)a1);callback(20+201);return ret[201]>=0&&ret[201]<nobj?nodes[ret[201]]:NULL;}
void spoteffects(boolean a0){logmsg("spoteffects:%d:;",(int)a0);callback(20+202);}
void stackobj(struct obj * a0){logmsg("stackobj:%d:;",oid(a0));callback(20+203);}
stairway * stairway_find_type_dir(boolean a0,boolean a1){logmsg("stairway_find_type_dir:%d:%d:;",(int)a0,(int)a1);callback(20+204);return ret[204]>=0?&stairs:NULL;}
int stinky_nemesis(struct monst * a0){logmsg("stinky_nemesis:%d:;",mid(a0));callback(20+205);return (int)ret[205];}
void stop_occupation(void){logmsg("stop_occupation:;");callback(20+206);}
char * strstr(const char * a0,const char * a1){logmsg("strstr:%s:%s:;",(a0?a0:"NULL"),(a1?a1:"NULL"));callback(20+207);return "strstr";}
const char * surface(coordxy a0,coordxy a1){logmsg("surface:%d:%d:;",(int)a0,(int)a1);callback(20+208);return "surface";}
void swallowed(int a0){logmsg("swallowed:%d:;",(int)a0);callback(20+209);}
struct trap * t_at(coordxy a0,coordxy a1){logmsg("t_at:%d:%d:;",(int)a0,(int)a1);callback(20+210);return ret[210]>=0?&fixture_trap:NULL;}
boolean tele_restrict(struct monst * a0){logmsg("tele_restrict:%d:;",mid(a0));callback(20+211);return (boolean)ret[211];}
void thiefdead(void){logmsg("thiefdead:;");callback(20+212);}
int touch_artifact(struct obj * a0,struct monst * a1){logmsg("touch_artifact:%d:%d:;",oid(a0),mid(a1));callback(20+213);return (int)ret[213];}
int tt_doppel(struct monst * a0){logmsg("tt_doppel:%d:;",mid(a0));callback(20+214);return (int)ret[214];}
const char * u_locomotion(const char * a0){logmsg("u_locomotion:%s:;",(a0?a0:"NULL"));callback(20+215);return "u_locomotion";}
boolean um_dist(coordxy a0,coordxy a1,xint16 a2){logmsg("um_dist:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+216);return (boolean)ret[216];}
void unblock_point(int a0,int a1){logmsg("unblock_point:%d:%d:;",(int)a0,(int)a1);callback(20+217);}
void unmap_object(coordxy a0,coordxy a1){logmsg("unmap_object:%d:%d:;",(int)a0,(int)a1);callback(20+218);}
void unpunish(void){logmsg("unpunish:;");callback(20+219);}
void update_inventory(void){logmsg("update_inventory:;");callback(20+220);}
void uunstick(void){logmsg("uunstick:;");callback(20+221);}
NhRegion * visible_region_at(coordxy a0,coordxy a1){logmsg("visible_region_at:%d:%d:;",(int)a0,(int)a1);callback(20+222);return ret[222]>=0?&fixture_region:NULL;}
void vision_recalc(int a0){logmsg("vision_recalc:%d:;",(int)a0);callback(20+223);}
char * vtense(const char * a0,const char * a1){logmsg("vtense:%s:%s:;",(a0?a0:"NULL"),(a1?a1:"NULL"));callback(20+224);return "vtense";}
void wary_dog(struct monst * a0,boolean a1){logmsg("wary_dog:%d:%d:;",mid(a0),(int)a1);callback(20+225);}
void water_damage_chain(struct obj * a0,boolean a1){logmsg("water_damage_chain:%d:%d:;",oid(a0),(int)a1);callback(20+226);}
int weight(struct obj * a0){logmsg("weight:%d:;",oid(a0));callback(20+227);return (int)ret[227];}
void were_change(struct monst * a0){logmsg("were_change:%d:;",mid(a0));callback(20+228);}
struct obj * which_armor(struct monst * a0,long a1){logmsg("which_armor:%d:%ld:;",mid(a0),(long)a1);callback(20+229);return ret[229]>=0&&ret[229]<nobj?nodes[ret[229]]:NULL;}
void wizdeadorgone(void){logmsg("wizdeadorgone:;");callback(20+230);}
boolean worm_cross(int a0,int a1,int a2,int a3){logmsg("worm_cross:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+231);return (boolean)ret[231];}
boolean worm_known(struct monst * a0){logmsg("worm_known:%d:;",mid(a0));callback(20+232);return (boolean)ret[232];}
void wormgone(struct monst * a0){logmsg("wormgone:%d:;",mid(a0));callback(20+233);}
void wormno_sanity_check(void){logmsg("wormno_sanity_check:;");callback(20+234);}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){logmsg("x_monnam:%d:%d:%s:%d:%d:;",mid(a0),(int)a1,(a2?a2:"NULL"),(int)a3,(int)a4);callback(20+235);return "x_monnam";}
char * xname(struct obj * a0){logmsg("xname:%d:;",oid(a0));callback(20+236);return "xname";}
char * y_monnam(struct monst * a0){logmsg("y_monnam:%d:;",mid(a0));callback(20+237);return "y_monnam";}
boolean defends(int a0,struct obj * a1){logmsg("defends:%d:%d:;",(int)a0,oid(a1));callback(20+238);return (boolean)ret[238];}
boolean defends_when_carried(int a0,struct obj * a1){logmsg("defends_when_carried:%d:%d:;",(int)a0,oid(a1));callback(20+239);return (boolean)ret[239];}
int title_to_mon(const char * a0,int * a1,int * a2){logmsg("title_to_mon:%s:%d:%d:;",(a0?a0:"NULL"),a1!=NULL,a2!=NULL);callback(20+240);if(a1)*a1=0;if(a2)*a2=NEUTRAL;return NON_PM;}
char * makesingular(const char * a0){logmsg("makesingular:%s:;",(a0?a0:"NULL"));callback(20+241);static char word[BUFSZ];snprintf(word,sizeof word,"%s",a0);return word;}

void teleport_mon_fixture_free(void*);
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_mon_fixture_free
#include "mon.c"
#undef free
#else
extern void teleport_mon_test_pet_sanity_check(
    struct monst *mtmp,
    const char *msgarg);
#define pet_sanity_check teleport_mon_test_pet_sanity_check
extern void teleport_mon_test_sanity_check_single_mon(
    struct monst *mtmp,
    boolean chk_geno,
    const char *msg);
#define sanity_check_single_mon teleport_mon_test_sanity_check_single_mon
extern struct obj * teleport_mon_test_make_corpse(struct monst *mtmp, unsigned int corpseflags);
#define make_corpse teleport_mon_test_make_corpse
extern int teleport_mon_test_minliquid_core(struct monst *mtmp);
#define minliquid_core teleport_mon_test_minliquid_core
extern void teleport_mon_test_m_calcdistress(struct monst *mtmp);
#define m_calcdistress teleport_mon_test_m_calcdistress
extern boolean teleport_mon_test_monlineu(struct monst *mon, int nx, int ny);
#define monlineu teleport_mon_test_monlineu
extern long teleport_mon_test_mm_2way_aggression(struct monst *magr, struct monst *mdef);
#define mm_2way_aggression teleport_mon_test_mm_2way_aggression
extern long teleport_mon_test_mm_aggression(
    struct monst *magr, 
    struct monst *mdef);
#define mm_aggression teleport_mon_test_mm_aggression
extern long teleport_mon_test_mm_displacement(
    struct monst *magr, 
    struct monst *mdef);
#define mm_displacement teleport_mon_test_mm_displacement
extern void teleport_mon_test_mon_leaving_level(struct monst *mon);
#define mon_leaving_level teleport_mon_test_mon_leaving_level
extern void teleport_mon_test_m_detach(
    struct monst *mtmp,
    struct permonst *mptr, 
    boolean due_to_death);
#define m_detach teleport_mon_test_m_detach
extern void teleport_mon_test_set_mon_min_mhpmax(
    struct monst *mon,
    int minimum_mhpmax);
#define set_mon_min_mhpmax teleport_mon_test_set_mon_min_mhpmax
extern void teleport_mon_test_lifesaved_monster(struct monst *mtmp);
#define lifesaved_monster teleport_mon_test_lifesaved_monster
extern boolean teleport_mon_test_vamprises(struct monst *mtmp);
#define vamprises teleport_mon_test_vamprises
extern void teleport_mon_test_logdeadmon(struct monst *mtmp, int mndx);
#define logdeadmon teleport_mon_test_logdeadmon
extern void teleport_mon_test_anger_quest_guardians(struct monst *mtmp);
#define anger_quest_guardians teleport_mon_test_anger_quest_guardians
extern boolean teleport_mon_test_ok_to_obliterate(struct monst *mtmp);
#define ok_to_obliterate teleport_mon_test_ok_to_obliterate
extern void teleport_mon_test_m_respond_shrieker(struct monst *mtmp);
#define m_respond_shrieker teleport_mon_test_m_respond_shrieker
extern void teleport_mon_test_m_respond_medusa(struct monst *mtmp);
#define m_respond_medusa teleport_mon_test_m_respond_medusa
extern void teleport_mon_test_qst_guardians_respond(void);
#define qst_guardians_respond teleport_mon_test_qst_guardians_respond
extern void teleport_mon_test_peacefuls_respond(struct monst *mtmp);
#define peacefuls_respond teleport_mon_test_peacefuls_respond
extern void teleport_mon_test_wake_nearto_core(coordxy x, coordxy y, int distance, boolean petcall);
#define wake_nearto_core teleport_mon_test_wake_nearto_core
extern void teleport_mon_test_m_restartcham(struct monst *mtmp);
#define m_restartcham teleport_mon_test_m_restartcham
extern boolean teleport_mon_test_restrap(struct monst *mtmp);
#define restrap teleport_mon_test_restrap
extern int teleport_mon_test_pick_animal(void);
#define pick_animal teleport_mon_test_pick_animal
extern int teleport_mon_test_pickvampshape(struct monst *mon);
#define pickvampshape teleport_mon_test_pickvampshape
extern boolean teleport_mon_test_isspecmon(struct monst *mon);
#define isspecmon teleport_mon_test_isspecmon
extern boolean teleport_mon_test_validspecmon(struct monst *mon, int mndx);
#define validspecmon teleport_mon_test_validspecmon
extern int teleport_mon_test_wiz_force_cham_form(struct monst *mon);
#define wiz_force_cham_form teleport_mon_test_wiz_force_cham_form
extern struct permonst * teleport_mon_test_accept_newcham_form(struct monst *mon, int mndx);
#define accept_newcham_form teleport_mon_test_accept_newcham_form
extern void teleport_mon_test_kill_eggs(struct obj *obj_list);
#define kill_eggs teleport_mon_test_kill_eggs
extern void teleport_mon_test_pacify_guard(struct monst *mtmp);
#define pacify_guard teleport_mon_test_pacify_guard
#endif
#include "tu-mon-layout.h"
static int frees,zero_frees;void teleport_mon_fixture_free(void*p){int i;if(!p)return;for(i=0;i<nmon;i++)if(monsters[i]==p){unsigned char*b=p;int j,zero=1;for(j=0;j<sizeof(struct monst);j++)if(b[j])zero=0;logmsg("free_mon:%d:%d;",i,zero);zero_frees+=zero;monsters[i]=NULL;break;}for(i=0;i<nobj;i++)if(nodes[i]==p){logmsg("free_obj:%d;",i);nodes[i]=NULL;break;}frees++;free(p);}
static coord probe_xy;static int probe_int;static char textbuf[BUFSZ];static int callback_count;
static boolean cb_nested(struct monst*m){logmsg("nested-iterator:%d;",mid(m));return FALSE;}
static boolean cb_bool(struct monst*m){if(opts[133]&&!opts[134]&&nmon==2){opts[134]=1;monsters[0]->nmon=monsters[1];monsters[1]->nmon=NULL;fmon=monsters[0];iter_mons_safe(cb_nested);}logmsg("callback-bool:%d;",mid(m));callback_count++;if(opts[130])m->mhp+=opts[130];return (boolean)opts[131];}
static void cb_void(struct monst*m){logmsg("callback-void:%d;",mid(m));callback_count++;if(opts[130])m->mhp+=opts[130];}
static boolean cb_xy(struct monst*m,coordxy x,coordxy y){logmsg("callback-xy:%d:%d:%d;",mid(m),x,y);callback_count++;return (boolean)opts[131];}
void probe_reset(unsigned s){int i;/* Tests consume each allocated list before a full reset. */
 memset(&u,0,sizeof u);memset(&svc,0,sizeof svc);memset(&svm,0,sizeof svm);memset(&svl,0,sizeof svl);memset(&gy,0,sizeof gy);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&gi,0,sizeof gi);memset(&gp,0,sizeof gp);memset(&gu,0,sizeof gu);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&gv,0,sizeof gv);memset(opts,0,sizeof opts);ret[0]=-1;ret[1]=0;ret[2]=0;ret[3]=0;ret[4]=0;ret[5]=-1;ret[6]=0;ret[7]=-1;ret[8]=-1;ret[9]=0;ret[10]=-1;ret[11]=0;ret[12]=0;ret[13]=0;ret[14]=-1;ret[15]=-1;ret[16]=0;ret[17]=0;ret[18]=0;ret[19]=-1;ret[20]=-1;ret[21]=0;ret[22]=0;ret[23]=0;ret[24]=0;ret[25]=0;ret[26]=0;ret[27]=0;ret[28]=0;ret[29]=0;ret[30]=0;ret[31]=0;ret[32]=-1;ret[33]=0;ret[34]=0;ret[35]=0;ret[36]=-1;ret[37]=0;ret[38]=0;ret[39]=0;ret[40]=0;ret[41]=0;ret[42]=0;ret[43]=0;ret[44]=0;ret[45]=0;ret[46]=0;ret[47]=0;ret[48]=0;ret[49]=0;ret[50]=0;ret[51]=-1;ret[52]=0;ret[53]=0;ret[54]=0;ret[55]=0;ret[56]=0;ret[57]=0;ret[58]=0;ret[59]=0;ret[60]=0;ret[61]=0;ret[62]=0;ret[63]=0;ret[64]=0;ret[65]=0;ret[66]=0;ret[67]=-1;ret[68]=0;ret[69]=0;ret[70]=-1;ret[71]=0;ret[72]=0;ret[73]=0;ret[74]=0;ret[75]=0;ret[76]=-1;ret[77]=0;ret[78]=0;ret[79]=0;ret[80]=0;ret[81]=-1;ret[82]=0;ret[83]=-1;ret[84]=0;ret[85]=0;ret[86]=0;ret[87]=0;ret[88]=0;ret[89]=0;ret[90]=0;ret[91]=0;ret[92]=0;ret[93]=0;ret[94]=0;ret[95]=0;ret[96]=0;ret[97]=0;ret[98]=-1;ret[99]=0;ret[100]=0;ret[101]=0;ret[102]=-1;ret[103]=0;ret[104]=0;ret[105]=-1;ret[106]=-1;ret[107]=0;ret[108]=0;ret[109]=-1;ret[110]=0;ret[111]=0;ret[112]=0;ret[113]=0;ret[114]=0;ret[115]=-1;ret[116]=0;ret[117]=-1;ret[118]=-1;ret[119]=-1;ret[120]=-1;ret[121]=0;ret[122]=0;ret[123]=0;ret[124]=0;ret[125]=0;ret[126]=-1;ret[127]=-1;ret[128]=0;ret[129]=0;ret[130]=0;ret[131]=0;ret[132]=0;ret[133]=0;ret[134]=-1;ret[135]=0;ret[136]=0;ret[137]=0;ret[138]=0;ret[139]=0;ret[140]=0;ret[141]=0;ret[142]=0;ret[143]=0;ret[144]=0;ret[145]=0;ret[146]=0;ret[147]=0;ret[148]=0;ret[149]=0;ret[150]=-1;ret[151]=0;ret[152]=0;ret[153]=-1;ret[154]=-1;ret[155]=0;ret[156]=-1;ret[157]=0;ret[158]=-1;ret[159]=-1;ret[160]=0;ret[161]=0;ret[162]=-1;ret[163]=0;ret[164]=0;ret[165]=0;ret[166]=0;ret[167]=0;ret[168]=0;ret[169]=0;ret[170]=0;ret[171]=-1;ret[172]=0;ret[173]=0;ret[174]=0;ret[175]=0;ret[176]=0;ret[177]=0;ret[178]=0;ret[179]=0;ret[180]=0;ret[181]=0;ret[182]=0;ret[183]=0;ret[184]=0;ret[185]=0;ret[186]=0;ret[187]=-1;ret[188]=0;ret[189]=0;ret[190]=-1;ret[191]=0;ret[192]=0;ret[193]=0;ret[194]=0;ret[195]=0;ret[196]=0;ret[197]=0;ret[198]=-1;ret[199]=-1;ret[200]=-1;ret[201]=-1;ret[202]=0;ret[203]=0;ret[204]=-1;ret[205]=0;ret[206]=0;ret[207]=-1;ret[208]=-1;ret[209]=0;ret[210]=-1;ret[211]=0;ret[212]=0;ret[213]=0;ret[214]=0;ret[215]=-1;ret[216]=0;ret[217]=0;ret[218]=0;ret[219]=0;ret[220]=0;ret[221]=0;ret[222]=-1;ret[223]=0;ret[224]=-1;ret[225]=0;ret[226]=0;ret[227]=0;ret[228]=0;ret[229]=-1;ret[230]=0;ret[231]=0;ret[232]=0;ret[233]=0;ret[234]=0;ret[235]=-1;ret[236]=-1;ret[237]=-1;ret[238]=0;ret[239]=0;ret[240]=0;ret[241]=-1;memset(&fixture_trap,0,sizeof fixture_trap);memset(&fixture_region,0,sizeof fixture_region);memset(&fixture_engr,0,sizeof fixture_engr);memset(cells,0,sizeof cells);
 if(growth){free(growth);growth=NULL;}for(i=0;i<nobj;i++)free(nodes[i]);for(i=0;i<nmon;i++){/* Explicit ownership tests clear their mextra first. */free(monsters[i]);}nmon=nobj=0;ri=nr=0;seed=s;tracebuf[0]=caller[0]=0;callback_count=0;frees=zero_frees=0;
 objects_globals_init();monst_globals_init();u.ux=40;u.uy=10;u.umonster=u.umonnum=PM_HUMAN;u.uhp=u.uhpmax=100;u.ulevel=10;u.uz.dnum=1;u.uz.dlevel=5;svm.moves=100;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mnum=PM_HUMAN;gy.youmonst.mhp=gy.youmonst.mhpmax=100;gy.youmonst.mx=u.ux;gy.youmonst.my=u.uy;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urace.mnum=PM_HUMAN;for(i=0;i<ROWNO;i++){visionrows[i]=vision[i];memset(vision[i],IN_SIGHT|COULD_SEE,COLNO);}gv.viz_array=visionrows;for(i=0;i<COLNO*ROWNO;i++)((struct rm*)svl.level.locations)[i].typ=ROOM;opts[0]=1;uwep=uball=uchain=NULL;opts[120]=opts[121]=opts[122]=opts[123]=opts[125]=-1;probe_int=0;probe_xy.x=probe_xy.y=0;strcpy(textbuf,"named monster");}
int probe_new_mon(int pm){struct monst*m=calloc(1,sizeof *m);if(nmon>=32)abort();monsters[nmon]=m;m->data=&mons[pm];m->mnum=pm;m->m_id=nmon+1;m->mhp=m->mhpmax=40;m->m_lev=10;m->mx=10+nmon;m->my=10;m->mux=u.ux;m->muy=u.uy;m->mcansee=m->mcanmove=1;m->cham=NON_PM;m->mstate=MON_FLOOR;m->nmon=fmon;fmon=m;svl.level.monsters[m->mx][m->my]=m;return nmon++;}
int probe_object(int typ){struct obj*o=calloc(1,sizeof *o);if(nobj>=128)abort();nodes[nobj]=o;o->o_id=nobj+1;o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;o->owt=objects[typ].oc_weight;o->where=OBJ_FREE;o->corpsenm=NON_PM;return nobj++;}
void probe_option(int i,int v){opts[i]=v;}void probe_return(int i,long v){ret[i]=v;}void probe_roll(int n){rolls[nr++]=n;}void probe_clear_trace(void){tracebuf[0]=0;}
const char*probe_trace(void){return tracebuf;}void*probe_pointer(int kind,int i){switch(kind){case 0:return i>=0&&i<nmon?monsters[i]:NULL;case 1:return i>=0&&i<nobj?nodes[i]:NULL;case 2:return &mons[i];case 3:return &objects[i];case 4:return &u;case 5:return &gy.youmonst;case 6:return &svm;case 7:return &svl;case 8:return &probe_xy;case 9:return &probe_int;case 10:return &fixture_trap;case 11:return &fixture_region;case 12:return textbuf;case 13:return &gv;case 14:return &flags;case 15:return &svd;case 16:return &ga;case 17:return &fixture_mfp;case 18:return &fmon;default:return NULL;}}
uintptr_t probe_callback(int type){return type==0?(uintptr_t)cb_bool:type==1?(uintptr_t)cb_void:(uintptr_t)cb_xy;}
long probe_aux(int kind){return kind==0?probe_int:kind==1?probe_xy.x:kind==2?probe_xy.y:callback_count;}
unsigned probe_count(int what){return what==0?nmon:what==1?nobj:(unsigned)ri;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}

int probe_frees(int zero){return zero?zero_frees:frees;}
void probe_tile(coordxy x,coordxy y,int typ,unsigned flags){levl[x][y].typ=typ;levl[x][y].flags=flags;}
void probe_put_object(int index,int where,int monindex){struct obj*o=nodes[index];o->where=where;if(where==OBJ_MINVENT){o->nobj=monsters[monindex]->minvent;monsters[monindex]->minvent=o;o->ocarry=monsters[monindex];}else if(where==OBJ_INVENT){o->nobj=gi.invent;gi.invent=o;}else if(where==OBJ_FLOOR){o->ox=monsters[monindex]->mx;o->oy=monsters[monindex]->my;o->nexthere=svl.level.objects[o->ox][o->oy];svl.level.objects[o->ox][o->oy]=o;o->nobj=fobj;fobj=o;}}
int probe_grid_mon(coordxy x,coordxy y){return mid(svl.level.monsters[x][y]);}
int probe_grid_obj(coordxy x,coordxy y){return oid(svl.level.objects[x][y]);}
int probe_gas_glyph(void){return cmap_to_glyph(S_poisoncloud);}

#ifndef TELEPORT_REFERENCE_TU
extern uint64_t teleport_mon_test_state(int);
#endif
uint64_t probe_iterator(int which){
#ifdef TELEPORT_REFERENCE_TU
return which?itermonsiz:(uintptr_t)itermonarr;
#else
return teleport_mon_test_state(which);
#endif
}
int probe_pointer_equal(uintptr_t a,uintptr_t b){return (void*)a==(void*)b;}
const char*probe_format_pointer(uintptr_t p){return fmt_ptr((void*)p);}
uint64_t probe_unsigned64(uintptr_t p){uint64_t value;memcpy(&value,(void*)p,sizeof value);return value;}

uintptr_t probe_extra(int index,int kind,int salt){struct monst*m=monsters[index];void*p=NULL;size_t n=0;switch(kind){case 0:newegd(m);p=EGD(m);n=sizeof *EGD(m);break;case 1:newepri(m);p=EPRI(m);n=sizeof *EPRI(m);break;case 2:neweshk(m);p=ESHK(m);n=sizeof *ESHK(m);break;case 3:newemin(m);p=EMIN(m);n=sizeof *EMIN(m);break;case 4:newedog(m);p=EDOG(m);n=sizeof *EDOG(m);break;case 5:newebones(m);p=EBONES(m);n=sizeof *EBONES(m);break;case 6:new_mgivenname(m,32);p=MGIVENNAME(m);n=32;break;}if(salt&&p){memset(p,salt,n);if(kind==6)strcpy(p,"MON copied name");}return(uintptr_t)p;}
uintptr_t probe_extra_pointer(int index,int kind){struct monst*m=monsters[index];if(!m->mextra)return 0;switch(kind){case 0:return(uintptr_t)EGD(m);case 1:return(uintptr_t)EPRI(m);case 2:return(uintptr_t)ESHK(m);case 3:return(uintptr_t)EMIN(m);case 4:return(uintptr_t)EDOG(m);case 5:return(uintptr_t)EBONES(m);case 6:return(uintptr_t)MGIVENNAME(m);}return 0;}

uintptr_t probe_native_return(int which){boolean flag=FALSE;struct obj*one=nodes[0],*two=nodes[1];switch(which){
case 0:return(uintptr_t)add_to_container(nodes[0],nodes[1]);
case 1:return(uintptr_t)attacktype_fordmg(&mons[PM_HUMAN],AT_ANY,AD_ANY);
case 2:return(uintptr_t)bury_an_obj(nodes[0],&flag);
case 3:return(uintptr_t)create_gas_cloud(10,10,2,5);
case 4:return(uintptr_t)dmgtype_fromattack(&mons[PM_HUMAN],AD_ANY,AT_ANY);
case 5:return(uintptr_t)g_at(10,10);
case 6:return(uintptr_t)get_mleash(monsters[0]);
case 7:return(uintptr_t)grow_up(monsters[0],monsters[1]);
case 8:return(uintptr_t)m_carrying(monsters[0],CORPSE);
case 9:return(uintptr_t)makemon(&mons[PM_HUMAN],10,10,0);
case 10:return(uintptr_t)mkcorpstat(CORPSE,monsters[0],&mons[PM_HUMAN],10,10,0);
case 11:return(uintptr_t)mkgold(31L,10,10);
case 12:return(uintptr_t)mkobj(RANDOM_CLASS,FALSE);
case 13:return(uintptr_t)mksobj_at(CORPSE,10,10,FALSE,FALSE);
case 14:return(uintptr_t)newmextra();
case 15:return(uintptr_t)nxtobj(nodes[0],CORPSE,FALSE);
case 16:return(uintptr_t)obj_meld(&one,&two);
case 17:return(uintptr_t)obj_nexto(nodes[0]);
case 18:return(uintptr_t)oname(nodes[0],"native name",0);
case 19:return(uintptr_t)sengr_at("native engraving",10,10,FALSE);
case 20:return(uintptr_t)sobj_at(CORPSE,10,10);
case 21:return(uintptr_t)split_mon(monsters[0],monsters[1]);
case 22:return(uintptr_t)splitobj(nodes[0],1L);
case 23:return(uintptr_t)stairway_find_type_dir(FALSE,FALSE);
case 24:return(uintptr_t)t_at(10,10);
case 25:return(uintptr_t)visible_region_at(10,10);
case 26:return(uintptr_t)which_armor(monsters[0],W_ARM);
}return 0;}

long probe_run(int op,int a,int b,long c,long d,long e){switch(op){
case 0:pet_sanity_check(monsters[a],textbuf);return 0;
case 1:sanity_check_single_mon(monsters[a],b,textbuf);return 0;
case 2:mon_sanity_check();return 0;
case 3:return m_poisongas_ok(monsters[a]);
case 4:return zombie_maker(monsters[a]);
case 5:return zombie_form(&mons[b]);
case 6:return undead_to_corpse(a);
case 7:return genus(a,b);
case 8:return pm_to_cham(a);
case 9:return oid(make_corpse(monsters[a],b));
case 10:return minliquid(monsters[a]);
case 11:return minliquid_core(monsters[a]);
case 12:return mcalcmove(monsters[a],b);
case 13:mcalcdistress();return 0;
case 14:m_calcdistress(monsters[a]);return 0;
case 15:return movemon_singlemon(monsters[a]);
case 16:return movemon();
case 17:meatbox(monsters[a],nodes[b]);return 0;
case 18:m_consume_obj(monsters[a],nodes[b]);return 0;
case 19:return meatmetal(monsters[a]);
case 20:return meatobj(monsters[a]);
case 21:return meatcorpse(monsters[a]);
case 22:mon_give_prop(monsters[a],b);return 0;
case 23:mon_givit(monsters[a],&mons[b]);return 0;
case 24:mpickgold(monsters[a]);return 0;
case 25:return mpickstuff(monsters[a]);
case 26:return curr_mon_load(monsters[a]);
case 27:return max_mon_load(monsters[a]);
case 28:return can_touch_safely(monsters[a],nodes[b]);
case 29:return can_carry(monsters[a],nodes[b]);
case 30:return monlineu(monsters[a],b,c);
case 31:return mon_allowflags(monsters[a]);
case 32:return m_in_air(monsters[a]);
case 33:return mfndpos(monsters[a],&fixture_mfp,c);
case 34:return mm_2way_aggression(monsters[a],monsters[b]);
case 35:return mm_aggression(monsters[a],monsters[b]);
case 36:return mm_displacement(monsters[a],monsters[b]);
case 37:return monnear(monsters[a],b,c);
case 38:dmonsfree();return 0;
case 39:replmon(monsters[a],monsters[b]);return 0;
case 40:relmon(monsters[a],opts[132]?NULL:&gm.migrating_mons);return 0;
case 41:copy_mextra(monsters[a],monsters[b]);return 0;
case 42:dealloc_mextra(monsters[a]);return 0;
case 43:dealloc_monst(monsters[a]);return 0;
case 44:mon_leaving_level(monsters[a]);return 0;
case 45:m_detach(monsters[a],&mons[b],c);return 0;
case 46:set_mon_min_mhpmax(monsters[a],b);return 0;
case 47:return oid(mlifesaver(monsters[a]));
case 48:lifesaved_monster(monsters[a]);return 0;
case 49:return vamprises(monsters[a]);
case 50:logdeadmon(monsters[a],b);return 0;
case 51:anger_quest_guardians(monsters[a]);return 0;
case 52:mondead(monsters[a]);return 0;
case 53:return corpse_chance(monsters[a],monsters[b],c);
case 54:mondied(monsters[a]);return 0;
case 55:mongone(monsters[a]);return 0;
case 56:monstone(monsters[a]);return 0;
case 57:monkilled(monsters[a],textbuf,c);return 0;
case 58:set_ustuck(monsters[a]);return 0;
case 59:unstuck(monsters[a]);return 0;
case 60:killed(monsters[a]);return 0;
case 61:xkilled(monsters[a],b);return 0;
case 62:mon_to_stone(monsters[a]);return 0;
case 63:return vamp_stone(monsters[a]);
case 64:m_into_limbo(monsters[a]);return 0;
case 65:migrate_mon(monsters[a],b,c);return 0;
case 66:return ok_to_obliterate(monsters[a]);
case 67:elemental_clog(monsters[a]);return 0;
case 68:mnexto(monsters[a],b);return 0;
case 69:deal_with_overcrowding(monsters[a]);return 0;
case 70:maybe_mnexto(monsters[a]);return 0;
case 71:return mnearto(monsters[a],b,c,d,e);
case 72:m_respond_shrieker(monsters[a]);return 0;
case 73:m_respond_medusa(monsters[a]);return 0;
case 74:m_respond(monsters[a]);return 0;
case 75:qst_guardians_respond();return 0;
case 76:peacefuls_respond(monsters[a]);return 0;
case 77:setmangry(monsters[a],b);return 0;
case 78:wake_msg(monsters[a],b);return 0;
case 79:wakeup(monsters[a],b);return 0;
case 80:wake_nearby(a);return 0;
case 81:wake_nearto_core(a,b,c,d);return 0;
case 82:wake_nearto(a,b,c);return 0;
case 83:seemimic(monsters[a]);return 0;
case 84:normal_shape(monsters[a]);return 0;
case 85:alloc_itermonarr(a);return 0;
case 86:iter_mons_safe(cb_bool);return 0;
case 87:iter_mons(cb_void);return 0;
case 88:return mid(get_iter_mons(cb_bool));
case 89:return mid(get_iter_mons_xy(cb_xy,b,c));
case 90:return healmon(monsters[a],b,c);
case 91:rescham();return 0;
case 92:m_restartcham(monsters[a]);return 0;
case 93:restartcham();return 0;
case 94:restore_cham(monsters[a]);return 0;
case 95:return restrap(monsters[a]);
case 96:maybe_unhide_at(a,b);return 0;
case 97:return hideunder(monsters[a]);
case 98:hide_monst(monsters[a]);return 0;
case 99:mon_animal_list(a);return 0;
case 100:return pick_animal();
case 101:decide_to_shapeshift(monsters[a]);return 0;
case 102:return pickvampshape(monsters[a]);
case 103:return isspecmon(monsters[a]);
case 104:return validspecmon(monsters[a],b);
case 105:return valid_vampshiftform(a,b);
case 106:return validvamp(monsters[a],&probe_int,c);
case 107:return wiz_force_cham_form(monsters[a]);
case 108:return select_newcham_form(monsters[a]);
case 109:return pidx(accept_newcham_form(monsters[a],b));
case 110:mgender_from_permonst(monsters[a],&mons[b]);return 0;
case 111:return newcham(monsters[a],&mons[b],c);
case 112:return can_be_hatched(a);
case 113:return egg_type_from_parent(a,b);
case 114:return dead_species(a,b);
case 115:kill_eggs(nodes[b]);return 0;
case 116:kill_genocided_monsters();return 0;
case 117:golemeffects(monsters[a],b,c);return 0;
case 118:return angry_guards(a);
case 119:pacify_guard(monsters[a]);return 0;
case 120:pacify_guards();return 0;
case 121:mimic_hit_msg(monsters[a],b);return 0;
case 122:return usmellmon(&mons[b]);
case 123:check_gear_next_turn(monsters[a]);return 0;
case 124:adj_erinys(a);return 0;
case 125:see_monster_closeup(monsters[a],b);return 0;
case 126:see_nearby_monsters();return 0;
case 127:shieldeff_mon(monsters[a]);return 0;
case 128:flash_mon(monsters[a]);return 0;
default:abort();}}

void probe_bit(int type,uintptr_t at,int field,unsigned v){switch(type){
case 0:{struct monst*o=(void*)at;switch(field){case 0:o->female=v;break;case 1:o->invis_blkd=v;break;case 2:o->isgd=v;break;case 3:o->isminion=v;break;case 4:o->ispriest=v;break;case 5:o->isshk=v;break;case 6:o->iswiz=v;break;case 7:o->mblinded=v;break;case 8:o->mcan=v;break;case 9:o->mcanmove=v;break;case 10:o->mcansee=v;break;case 11:o->mcloned=v;break;case 12:o->mconf=v;break;case 13:o->meverseen=v;break;case 14:o->mflee=v;break;case 15:o->mfleetim=v;break;case 16:o->mfrozen=v;break;case 17:o->mgenmklev=v;break;case 18:o->minvis=v;break;case 19:o->mleashed=v;break;case 20:o->mpeaceful=v;break;case 21:o->mrevived=v;break;case 22:o->msleeping=v;break;case 23:o->mspeed=v;break;case 24:o->mstun=v;break;case 25:o->mtrapped=v;break;case 26:o->mundetected=v;break;case 27:o->perminvis=v;break;case 28:o->wormno=v;break;default:abort();}break;}
case 1:{struct you*o=(void*)at;switch(field){case 0:o->mfemale=v;break;case 1:o->uinvulnerable=v;break;case 2:o->uinwater=v;break;case 3:o->uswallow=v;break;case 4:o->uundetected=v;break;default:abort();}break;}
case 2:{struct obj*o=(void*)at;switch(field){case 0:o->blessed=v;break;case 1:o->cursed=v;break;case 2:o->lamplit=v;break;case 3:o->obroken=v;break;case 4:o->oerodeproof=v;break;case 5:o->otrapped=v;break;default:abort();}break;}
case 3:{struct objclass*o=(void*)at;switch(field){case 0:o->oc_big=v;break;case 1:o->oc_material=v;break;default:abort();}break;}
case 4:{struct mvitals*o=(void*)at;switch(field){case 0:o->photographed=v;break;case 1:o->seen_close=v;break;default:abort();}break;}
case 5:{struct rm*o=(void*)at;switch(field){case 0:o->flags=v;break;default:abort();}break;}
case 6:{struct edog*o=(void*)at;switch(field){case 0:o->killed_by_u=v;break;default:abort();}break;}
case 7:{struct levelflags*o=(void*)at;switch(field){case 0:o->arboreal=v;break;case 1:o->deathdrops=v;break;case 2:o->graveyard=v;break;case 3:o->has_temple=v;break;default:abort();}break;}
case 8:{struct trap*o=(void*)at;switch(field){case 0:o->ttyp=v;break;default:abort();}break;}
case 9:{struct q_score*o=(void*)at;switch(field){case 0:o->killed_leader=v;break;case 1:o->leader_is_dead=v;break;default:abort();}break;}
case 10:{struct u_event*o=(void*)at;switch(field){case 0:o->qcompleted=v;break;default:abort();}break;}
default:abort();}}

/* Bounded native pointer-slot store only: no dereference of opaque successor/replacement. */
uint64_t probe_store_fmon(uint64_t bits){struct monst*replacement=(struct monst*)(uintptr_t)bits;fmon=replacement;return(uintptr_t)fmon;}
