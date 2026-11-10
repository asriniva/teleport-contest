/* Controlled external world; original monmove.c remains the unchanged reference policy. */
#include "hack.h"
#include "mfndpos.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
__typeof__(u)u;__typeof__(svc)svc;__typeof__(svm)svm;__typeof__(svl)svl;__typeof__(gy)gy;__typeof__(gv)gv;__typeof__(gm)gm;__typeof__(go)go;__typeof__(gn)gn;__typeof__(gi)gi;__typeof__(gb)gb;__typeof__(gk)gk;__typeof__(svd)svd;__typeof__(flags)flags;__typeof__(a11y)a11y;__typeof__(iflags)iflags;__typeof__(disp)disp;const __typeof__(cg)cg={0};const struct c_common_strings c_common_strings={.c_something="something"};
struct obj*uwep,*uarm,*uball,*uchain;
const struct Gender genders[4]={{.his="his"},{.his="her"},{.his="its"},{.his="their"}};
const schar dirs_ord[N_DIRS]={DIR_W,DIR_N,DIR_E,DIR_S,DIR_NW,DIR_NE,DIR_SE,DIR_SW};
const schar xdir[N_DIRS_Z]={-1,-1,0,1,1,1,0,-1,0,0},ydir[N_DIRS_Z]={0,-1,-1,-1,0,1,1,1,0,0};
static struct monst*monsters[16];static struct obj*nodes[64];static struct trap traps[COLNO][ROWNO];static unsigned char trapactive[COLNO][ROWNO];static seenV vision[ROWNO][COLNO],*visionrows[ROWNO];static int opts[128],rolls[4096],nr,ri,nmon,nobj;static unsigned seed;static long ret[256];static char tracebuf[1048576],caller[256];static void*growth;static struct mfndposdata candidates;static struct engr engraving;static stairway stairs;static struct throw_and_return_weapon returning;static coord point;static int cells[6];
static int mid(struct monst*m){int i;if(!m)return-1;if(m==&gy.youmonst)return-2;for(i=0;i<nmon;i++)if(m==monsters[i])return i;return-3;}static int oid(struct obj*o){int i;if(!o)return-1;for(i=0;i<nobj;i++)if(o==nodes[i])return i;return-2;}
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static void callback(int n){if(opts[120]==n&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("grow:%d;",n);}if(opts[121]==n&&!opts[122]){opts[122]=1;if(nmon>1)mon_track_add(monsters[1],25,26);logmsg("reenter:%d;",n);}}
void panic(const char*f,...){va_list ap;va_start(ap,f);vfprintf(stderr,f,ap);va_end(ap);abort();}
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char*f,int line,const char*fn){snprintf(caller,sizeof caller,"%s:%d:%s",f,line,fn);}
static int draw(int n){unsigned v;if(n<=0)panic("bad rng %d",n);seed=seed*1664525U+1013904223U;v=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;logmsg("rng:%d:%u@%s;",n,v,caller);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}int(rnl)(int n){return draw(n);}int(d)(int n,int z){int t=0;while(n--)t+=draw(z)+1;return t;}
static void display(winid w,boolean b){logmsg("display:%d:%d;",w,b);}__typeof__(windowprocs)windowprocs={.win_display_nhwindow=display};winid WIN_MESSAGE=1;
void pline(const char*f,...){va_list ap;logmsg("pline:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void pline_The(const char*f,...){va_list ap;logmsg("pline_The:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You(const char*f,...){va_list ap;logmsg("You:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You_hear(const char*f,...){va_list ap;logmsg("You_hear:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void You_see(const char*f,...){va_list ap;logmsg("You_see:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void verbalize(const char*f,...){va_list ap;logmsg("verbalize:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void impossible(const char*f,...){va_list ap;logmsg("impossible:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void Norep(const char*f,...){va_list ap;logmsg("Norep:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
void pline_mon(struct monst*m,const char*f,...){va_list ap;logmsg("pline_mon:%d:",mid(m));va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}void pline_xy(coordxy x,coordxy y,const char*f,...){va_list ap;logmsg("pline_xy:%d:%d:",x,y);va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}boolean In_hell(d_level*l){return l->dnum==9;}boolean unconscious(void){return opts[2];}boolean is_fainted(void){return opts[3];}boolean has_ceiling(d_level*l){return opts[4];}schar acurrstr(void){return opts[5];}int pronoun_gender(struct monst*m,unsigned flags){return opts[6];}boolean clear_path(int x,int y,int a,int b){logmsg("clear:%d:%d:%d:%d;",x,y,a,b);return opts[7];}
boolean is_pool(coordxy x,coordxy y){return isok(x,y)&&(levl[x][y].typ==POOL||levl[x][y].typ==MOAT||levl[x][y].typ==WATER);}schar db_under_typ(int mask){return mask&DB_MOAT?MOAT:mask&DB_LAVA?LAVAPOOL:ROOM;}
boolean picking_lock(coordxy*x,coordxy*y){logmsg("picking;");if(opts[8]){*x=point.x;*y=point.y;}callback(1);return opts[8];}
struct trap*t_at(coordxy x,coordxy y){logmsg("trap:%d:%d;",x,y);return isok(x,y)&&trapactive[x][y]?&traps[x][y]:NULL;}
struct obj*sobj_at(int type,coordxy x,coordxy y){struct obj*o;logmsg("sobj:%d:%d:%d;",type,x,y);if(!isok(x,y))return NULL;for(o=svl.level.objects[x][y];o;o=o->nexthere)if(o->otyp==type)return o;return NULL;}
struct obj*m_carrying(struct monst*m,int type){struct obj*o;logmsg("carry:%d:%d;",mid(m),type);for(o=m->minvent;o;o=o->nobj)if(o->otyp==type)return o;return NULL;}struct obj*findgold(struct obj*o){while(o){if(o->oclass==COIN_CLASS)return o;o=o->nobj;}return NULL;}
int mfndpos(struct monst*m,struct mfndposdata*out,long allow){logmsg("mfndpos:%d:%ld;",mid(m),allow);*out=candidates;callback(2);return candidates.cnt;}void place_monster(struct monst*m,coordxy x,coordxy y){logmsg("place:%d:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;svl.level.monsters[x][y]=m;callback(3);}
coord*gettrack(coordxy x,coordxy y){logmsg("gettrack:%d:%d;",x,y);callback(5);return opts[9]?&point:NULL;}const struct throw_and_return_weapon*autoreturn_weapon(struct obj*o){logmsg("returning:%d;",oid(o));return opts[10]?&returning:NULL;}
struct engr*sengr_at(const char*s,coordxy x,coordxy y,boolean strict){logmsg("engr:%s:%d:%d:%d;",s,x,y,strict);return opts[11]?&engraving:NULL;}struct obj*g_at(coordxy x,coordxy y){return isok(x,y)?svl.level.objects[x][y]:NULL;}
stairway*stairway_at(coordxy x,coordxy y){return opts[12]?&stairs:NULL;}stairway*stairway_find_dir(boolean up){return opts[12]?&stairs:NULL;}
int mintrap(struct monst*m,unsigned flags){logmsg("mintrap:%d:%u;",mid(m),flags);callback(4);return opts[13];}
char * Adjmonnam(struct monst * a0,const char * a1){logmsg("Adjmonnam:%d:%s:;",mid(a0),(a1?a1:"NULL"));callback(20+0);return "Adjmonnam";}
char * Amonnam(struct monst * a0){logmsg("Amonnam:%d:;",mid(a0));callback(20+1);return "Amonnam";}
s_level * Is_special(d_level * a0){logmsg("Is_special:%d:;",a0!=NULL);callback(20+2);return NULL;}
char * Monnam(struct monst * a0){logmsg("Monnam:%d:;",mid(a0));callback(20+3);return "Monnam";}
char * YMonnam(struct monst * a0){logmsg("YMonnam:%d:;",mid(a0));callback(20+4);return "YMonnam";}
void add_damage(coordxy a0,coordxy a1,long a2){logmsg("add_damage:%d:%d:%ld:;",(int)a0,(int)a1,(long)a2);callback(20+5);}
void after_shk_move(struct monst * a0){logmsg("after_shk_move:%d:;",mid(a0));callback(20+6);}
char * an(const char * a0){logmsg("an:%s:;",(a0?a0:"NULL"));callback(20+7);return "an";}
boolean angry_guards(boolean a0){logmsg("angry_guards:%d:;",(int)a0);callback(20+8);return (boolean)ret[8];}
boolean artifact_light(struct obj * a0){logmsg("artifact_light:%d:;",oid(a0));callback(20+9);return (boolean)ret[9];}
boolean attacktype(struct permonst * a0,int a1){logmsg("attacktype:%d:%d:;",a0?a0->pmidx:-1,(int)a1);callback(20+10);return (boolean)ret[10];}
char * bare_artifactname(struct obj * a0){logmsg("bare_artifactname:%d:;",oid(a0));callback(20+11);return "bare_artifactname";}
void bill_dummy_object(struct obj * a0){logmsg("bill_dummy_object:%d:;",oid(a0));callback(20+12);}
struct obj * bury_an_obj(struct obj * a0,boolean * a1){logmsg("bury_an_obj:%d:%d:;",oid(a0),a1!=NULL);callback(20+13);return ret[13]>=0&&ret[13]<nobj?nodes[ret[13]]:NULL;}
int can_carry(struct monst * a0,struct obj * a1){logmsg("can_carry:%d:%d:;",mid(a0),oid(a1));callback(20+14);return (int)ret[14];}
boolean can_touch_safely(struct monst * a0,struct obj * a1){logmsg("can_touch_safely:%d:%d:;",mid(a0),oid(a1));callback(20+15);return (boolean)ret[15];}
boolean can_track(struct permonst * a0){logmsg("can_track:%d:;",a0?a0->pmidx:-1);callback(20+16);return (boolean)ret[16];}
int canseemon(struct monst * a0){logmsg("canseemon:%d:;",mid(a0));callback(20+17);return (int)ret[17];}
int castmu(struct monst * a0,struct attack * a1,boolean a2,boolean a3){logmsg("castmu:%d:%d:%d:%d:;",mid(a0),a1!=NULL,(int)a2,(int)a3);callback(20+18);return (int)ret[18];}
boolean costly_spot(coordxy a0,coordxy a1){logmsg("costly_spot:%d:%d:;",(int)a0,(int)a1);callback(20+19);return (boolean)ret[19];}
boolean could_reach_item(struct monst * a0,coordxy a1,coordxy a2){logmsg("could_reach_item:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+20);return (boolean)ret[20];}
int count_traps(int a0){logmsg("count_traps:%d:;",(int)a0);callback(20+21);return (int)ret[21];}
NhRegion * create_gas_cloud(coordxy a0,coordxy a1,int a2,int a3){logmsg("create_gas_cloud:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+22);return NULL;}
int curr_mon_load(struct monst * a0){logmsg("curr_mon_load:%d:;",mid(a0));callback(20+23);return (int)ret[23];}
boolean cursed_object_at(coordxy a0,coordxy a1){logmsg("cursed_object_at:%d:%d:;",(int)a0,(int)a1);callback(20+24);return (boolean)ret[24];}
void cuss(struct monst * a0){logmsg("cuss:%d:;",mid(a0));callback(20+25);}
void delobj(struct obj * a0){logmsg("delobj:%d:;",oid(a0));callback(20+26);}
int demon_talk(struct monst * a0){logmsg("demon_talk:%d:;",mid(a0));callback(20+27);return (int)ret[27];}
void disturb_buried_zombies(coordxy a0,coordxy a1){logmsg("disturb_buried_zombies:%d:%d:;",(int)a0,(int)a1);callback(20+28);}
boolean dmgtype(struct permonst * a0,int a1){logmsg("dmgtype:%d:%d:;",a0?a0->pmidx:-1,(int)a1);callback(20+29);return (boolean)ret[29];}
int dog_move(struct monst * a0,int a1){logmsg("dog_move:%d:%d:;",mid(a0),(int)a1);callback(20+30);return (int)ret[30];}
int dogfood(struct monst * a0,struct obj * a1){logmsg("dogfood:%d:%d:;",mid(a0),oid(a1));callback(20+31);return (int)ret[31];}
int eaten_stat(int a0,struct obj * a1){logmsg("eaten_stat:%d:%d:;",(int)a0,oid(a1));callback(20+32);return (int)ret[32];}
void expels(struct monst * a0,struct permonst * a1,boolean a2){logmsg("expels:%d:%d:%d:;",mid(a0),a1?a1->pmidx:-1,(int)a2);callback(20+33);}
void extract_from_minvent(struct monst * a0,struct obj * a1,boolean a2,boolean a3){logmsg("extract_from_minvent:%d:%d:%d:%d:;",mid(a0),oid(a1),(int)a2,(int)a3);callback(20+34);}
boolean find_defensive(struct monst * a0,boolean a1){logmsg("find_defensive:%d:%d:;",mid(a0),(int)a1);callback(20+35);return (boolean)ret[35];}
boolean find_misc(struct monst * a0){logmsg("find_misc:%d:;",mid(a0));callback(20+36);return (boolean)ret[36];}
boolean find_offensive(struct monst * a0){logmsg("find_offensive:%d:;",mid(a0));callback(20+37);return (boolean)ret[37];}
void finish_meating(struct monst * a0){logmsg("finish_meating:%d:;",mid(a0));callback(20+38);}
void fracture_rock(struct obj * a0){logmsg("fracture_rock:%d:;",oid(a0));callback(20+39);}
int gd_move(struct monst * a0){logmsg("gd_move:%d:;",mid(a0));callback(20+40);return (int)ret[40];}
struct permonst * grow_up(struct monst * a0,struct monst * a1){logmsg("grow_up:%d:%d:;",mid(a0),mid(a1));callback(20+41);return ret[41]>=0?&mons[ret[41]]:NULL;}
struct obj * has_magic_key(struct monst * a0){logmsg("has_magic_key:%d:;",mid(a0));callback(20+42);return ret[42]>=0&&ret[42]<nobj?nodes[ret[42]]:NULL;}
int healmon(struct monst * a0,int a1,int a2){logmsg("healmon:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+43);return (int)ret[43];}
boolean hideunder(struct monst * a0){logmsg("hideunder:%d:;",mid(a0));callback(20+44);return (boolean)ret[44];}
char * in_rooms(coordxy a0,coordxy a1,int a2){logmsg("in_rooms:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+45);return opts[14]?"A":"";}
boolean in_town(coordxy a0,coordxy a1){logmsg("in_town:%d:%d:;",(int)a0,(int)a1);callback(20+46);return (boolean)ret[46];}
boolean in_your_sanctuary(struct monst * a0,coordxy a1,coordxy a2){logmsg("in_your_sanctuary:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+47);return (boolean)ret[47];}
int inhishop(struct monst * a0){logmsg("inhishop:%d:;",mid(a0));callback(20+48);return (int)ret[48];}
boolean inhistemple(struct monst * a0){logmsg("inhistemple:%d:;",mid(a0));callback(20+49);return (boolean)ret[49];}
boolean is_digging(void){logmsg("is_digging:;");callback(20+50);return (boolean)ret[50];}
boolean lined_up(struct monst * a0){logmsg("lined_up:%d:;",mid(a0));callback(20+51);return (boolean)ret[51];}
const char * locomotion(const struct permonst * a0,const char * a1){logmsg("locomotion:%d:%s:;",a0?a0->pmidx:-1,(a1?a1:"NULL"));callback(20+52);return "locomotion";}
void losehp(int a0,const char * a1,schar a2){logmsg("losehp:%d:%s:%d:;",(int)a0,(a1?a1:"NULL"),(int)a2);callback(20+53);}
void m_consume_obj(struct monst * a0,struct obj * a1){logmsg("m_consume_obj:%d:%d:;",mid(a0),oid(a1));callback(20+54);}
boolean m_has_launcher_and_ammo(struct monst * a0){logmsg("m_has_launcher_and_ammo:%d:;",mid(a0));callback(20+55);return (boolean)ret[55];}
boolean m_in_out_region(struct monst * a0,coordxy a1,coordxy a2){logmsg("m_in_out_region:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+56);return (boolean)ret[56];}
void m_respond(struct monst * a0){logmsg("m_respond:%d:;",mid(a0));callback(20+57);}
char * makeplural(const char * a0){logmsg("makeplural:%s:;",(a0?a0:"NULL"));callback(20+58);return "makeplural";}
struct trap * maketrap(coordxy a0,coordxy a1,int a2){logmsg("maketrap:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+59);return NULL;}
int mattackm(struct monst * a0,struct monst * a1){logmsg("mattackm:%d:%d:;",mid(a0),mid(a1));callback(20+60);return (int)ret[60];}
int mattacku(struct monst * a0){logmsg("mattacku:%d:;",mid(a0));callback(20+61);return (int)ret[61];}
int max_mon_load(struct monst * a0){logmsg("max_mon_load:%d:;",mid(a0));callback(20+62);return (int)ret[62];}
boolean may_dig(coordxy a0,coordxy a1){logmsg("may_dig:%d:%d:;",(int)a0,(int)a1);callback(20+63);return (boolean)ret[63];}
void maybe_unhide_at(coordxy a0,coordxy a1){logmsg("maybe_unhide_at:%d:%d:;",(int)a0,(int)a1);callback(20+64);}
const char * mbodypart(struct monst * a0,int a1){logmsg("mbodypart:%d:%d:;",mid(a0),(int)a1);callback(20+65);return "mbodypart";}
boolean mdig_tunnel(struct monst * a0){logmsg("mdig_tunnel:%d:;",mid(a0));callback(20+66);return (boolean)ret[66];}
int mdisplacem(struct monst * a0,struct monst * a1,boolean a2){logmsg("mdisplacem:%d:%d:%d:;",mid(a0),mid(a1),(int)a2);callback(20+67);return (int)ret[67];}
void mdrop_obj(struct monst * a0,struct obj * a1,boolean a2){logmsg("mdrop_obj:%d:%d:%d:;",mid(a0),oid(a1),(int)a2);callback(20+68);}
int meatcorpse(struct monst * a0){logmsg("meatcorpse:%d:;",mid(a0));callback(20+69);return (int)ret[69];}
int meatmetal(struct monst * a0){logmsg("meatmetal:%d:;",mid(a0));callback(20+70);return (int)ret[70];}
int meatobj(struct monst * a0){logmsg("meatobj:%d:;",mid(a0));callback(20+71);return (int)ret[71];}
void mnexto(struct monst * a0,unsigned int a1){logmsg("mnexto:%d:%d:;",mid(a0),(int)a1);callback(20+72);}
long mon_allowflags(struct monst * a0){logmsg("mon_allowflags:%d:;",mid(a0));callback(20+73);return (long)ret[73];}
boolean mon_knows_traps(struct monst * a0,int a1){logmsg("mon_knows_traps:%d:%d:;",mid(a0),(int)a1);callback(20+74);return (boolean)ret[74];}
void mon_learns_traps(struct monst * a0,int a1){logmsg("mon_learns_traps:%d:%d:;",mid(a0),(int)a1);callback(20+75);}
char * mon_nam(struct monst * a0){logmsg("mon_nam:%d:;",mid(a0));callback(20+76);return "mon_nam";}
int mon_wield_item(struct monst * a0){logmsg("mon_wield_item:%d:;",mid(a0));callback(20+77);return (int)ret[77];}
void mondied(struct monst * a0){logmsg("mondied:%d:;",mid(a0));callback(20+78);}
long money_cnt(struct obj * a0){logmsg("money_cnt:%d:;",oid(a0));callback(20+79);return (long)ret[79];}
void monkilled(struct monst * a0,const char * a1,int a2){logmsg("monkilled:%d:%s:%d:;",mid(a0),(a1?a1:"NULL"),(int)a2);callback(20+80);}
boolean monnear(struct monst * a0,coordxy a1,coordxy a2){logmsg("monnear:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);callback(20+81);return (boolean)ret[81];}
boolean mpickstuff(struct monst * a0){logmsg("mpickstuff:%d:;",mid(a0));callback(20+82);return (boolean)ret[82];}
boolean mwelded(struct obj * a0){logmsg("mwelded:%d:;",oid(a0));callback(20+83);return (boolean)ret[83];}
int newcham(struct monst * a0,struct permonst * a1,unsigned int a2){logmsg("newcham:%d:%d:%d:;",mid(a0),a1?a1->pmidx:-1,(int)a2);callback(20+84);return (int)ret[84];}
void newsym(coordxy a0,coordxy a1){logmsg("newsym:%d:%d:;",(int)a0,(int)a1);callback(20+85);}
boolean noattacks(struct permonst * a0){logmsg("noattacks:%d:;",a0?a0->pmidx:-1);callback(20+86);return (boolean)ret[86];}
boolean noteleport_level(struct monst * a0){logmsg("noteleport_level:%d:;",mid(a0));callback(20+87);return (boolean)ret[87];}
void notice_mon(struct monst * a0){logmsg("notice_mon:%d:;",mid(a0));callback(20+88);}
int pri_move(struct monst * a0){logmsg("pri_move:%d:;",mid(a0));callback(20+89);return (int)ret[89];}
void quest_stat_check(struct monst * a0){logmsg("quest_stat_check:%d:;",mid(a0));callback(20+90);}
void quest_talk(struct monst * a0){logmsg("quest_talk:%d:;",mid(a0));callback(20+91);}
boolean ranged_attk_available(struct monst * a0){logmsg("ranged_attk_available:%d:;",mid(a0));callback(20+92);return (boolean)ret[92];}
void recalc_block_point(coordxy a0,coordxy a1){logmsg("recalc_block_point:%d:%d:;",(int)a0,(int)a1);callback(20+93);}
boolean resist_conflict(struct monst * a0){logmsg("resist_conflict:%d:;",mid(a0));callback(20+94);return (boolean)ret[94];}
boolean rloc(struct monst * a0,unsigned int a1){logmsg("rloc:%d:%d:;",mid(a0),(int)a1);callback(20+95);return (boolean)ret[95];}
boolean searches_for_item(struct monst * a0,struct obj * a1){logmsg("searches_for_item:%d:%d:;",mid(a0),oid(a1));callback(20+96);return (boolean)ret[96];}
void see_wsegs(struct monst * a0){logmsg("see_wsegs:%d:;",mid(a0));callback(20+97);}
struct obj * select_rwep(struct monst * a0){logmsg("select_rwep:%d:;",mid(a0));callback(20+98);return ret[98]>=0&&ret[98]<nobj?nodes[ret[98]]:NULL;}
int sensemon(struct monst * a0){logmsg("sensemon:%d:;",mid(a0));callback(20+99);return (int)ret[99];}
void set_malign(struct monst * a0){logmsg("set_malign:%d:;",mid(a0));callback(20+100);}
void set_msg_xy(coordxy a0,coordxy a1){logmsg("set_msg_xy:%d:%d:;",(int)a0,(int)a1);callback(20+101);}
int shk_move(struct monst * a0){logmsg("shk_move:%d:;",mid(a0));callback(20+102);return (int)ret[102];}
struct obj * splitobj(struct obj * a0,long a1){logmsg("splitobj:%d:%ld:;",oid(a0),(long)a1);callback(20+103);return ret[103]>=0&&ret[103]<nobj?nodes[ret[103]]:NULL;}
boolean sticks(struct permonst * a0){logmsg("sticks:%d:;",a0?a0->pmidx:-1);callback(20+104);return (boolean)ret[104];}
void stop_occupation(void){logmsg("stop_occupation:;");callback(20+105);}
void swallowed(int a0){logmsg("swallowed:%d:;",(int)a0);callback(20+106);}
void switch_terrain(void){logmsg("switch_terrain:;");callback(20+107);}
int tactics(struct monst * a0){logmsg("tactics:%d:;",mid(a0));callback(20+108);return (int)ret[108];}
boolean tele_restrict(struct monst * a0){logmsg("tele_restrict:%d:;",mid(a0));callback(20+109);return (boolean)ret[109];}
void u_on_newpos(coordxy a0,coordxy a1){logmsg("u_on_newpos:%d:%d:;",(int)a0,(int)a1);callback(20+110);}
void unstuck(struct monst * a0){logmsg("unstuck:%d:;",mid(a0));callback(20+111);}
int use_defensive(struct monst * a0){logmsg("use_defensive:%d:;",mid(a0));callback(20+112);return (int)ret[112];}
int use_misc(struct monst * a0){logmsg("use_misc:%d:;",mid(a0));callback(20+113);return (int)ret[113];}
NhRegion * visible_region_at(coordxy a0,coordxy a1){logmsg("visible_region_at:%d:%d:;",(int)a0,(int)a1);callback(20+114);return NULL;}
void vision_recalc(int a0){logmsg("vision_recalc:%d:;",(int)a0);callback(20+115);if(opts[15]){int xx,yy;for(xx=0;xx<COLNO;xx++)for(yy=0;yy<ROWNO;yy++)vision[yy][xx]=IN_SIGHT|COULD_SEE;}}
char * vtense(const char * a0,const char * a1){logmsg("vtense:%s:%s:;",(a0?a0:"NULL"),(a1?a1:"NULL"));callback(20+116);return "vtense";}
void wake_msg(struct monst * a0,boolean a1){logmsg("wake_msg:%d:%d:;",mid(a0),(int)a1);callback(20+117);}
void wake_nearto(coordxy a0,coordxy a1,int a2){logmsg("wake_nearto:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);callback(20+118);}
void wakeup(struct monst * a0,boolean a1){logmsg("wakeup:%d:%d:;",mid(a0),(int)a1);callback(20+119);}
void watch_dig(struct monst * a0,coordxy a1,coordxy a2,boolean a3){logmsg("watch_dig:%d:%d:%d:%d:;",mid(a0),(int)a1,(int)a2,(int)a3);callback(20+120);}
void wipe_engr_at(coordxy a0,coordxy a1,xint16 a2,boolean a3){logmsg("wipe_engr_at:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3);callback(20+121);}
void worm_move(struct monst * a0){logmsg("worm_move:%d:;",mid(a0));callback(20+122);}
void worm_nomove(struct monst * a0){logmsg("worm_nomove:%d:;",mid(a0));callback(20+123);}
int wormhitu(struct monst * a0){logmsg("wormhitu:%d:;",mid(a0));callback(20+124);return (int)ret[124];}
char * xname(struct obj * a0){logmsg("xname:%d:;",oid(a0));callback(20+125);return "xname";}
char * y_monnam(struct monst * a0){logmsg("y_monnam:%d:;",mid(a0));callback(20+126);return "y_monnam";}
char * yname(struct obj * a0){logmsg("yname:%d:;",oid(a0));callback(20+127);return "yname";}
boolean is_art(struct obj * a0,int a1){logmsg("is_art:%d:%d:;",oid(a0),(int)a1);callback(20+128);return (boolean)ret[128];}
aligntyp mon_aligntyp(struct monst * a0){logmsg("mon_aligntyp:%d:;",mid(a0));callback(20+129);return (aligntyp)ret[129];}

void mongone(struct monst*m){logmsg("mongone:%d;",mid(m));callback(5);}
#ifdef TELEPORT_REFERENCE_TU
#include "monmove.c"
#else
extern void teleport_monmove_test_msg_mon_movement(struct monst *mtmp, coordxy omx, coordxy omy);
#define msg_mon_movement teleport_monmove_test_msg_mon_movement
extern void teleport_monmove_test_watch_on_duty(struct monst *mtmp);
#define watch_on_duty teleport_monmove_test_watch_on_duty
extern int teleport_monmove_test_disturb(struct monst *mtmp);
#define disturb teleport_monmove_test_disturb
extern void teleport_monmove_test_release_hero(struct monst *mon);
#define release_hero teleport_monmove_test_release_hero
extern int teleport_monmove_test_gelcube_digests(struct monst *mtmp);
#define gelcube_digests teleport_monmove_test_gelcube_digests
extern void teleport_monmove_test_distfleeck(
    struct monst *mtmp,
    int *inrange, int *nearby, int *scared);
#define distfleeck teleport_monmove_test_distfleeck
extern int teleport_monmove_test_m_arrival(struct monst *mon);
#define m_arrival teleport_monmove_test_m_arrival
extern void teleport_monmove_test_mind_blast(struct monst *mtmp);
#define mind_blast teleport_monmove_test_mind_blast
extern boolean teleport_monmove_test_leppie_avoidance(struct monst *mtmp);
#define leppie_avoidance teleport_monmove_test_leppie_avoidance
extern void teleport_monmove_test_leppie_stash(struct monst *mtmp);
#define leppie_stash teleport_monmove_test_leppie_stash
extern int teleport_monmove_test_m_balks_at_approaching(int oldappr, struct monst *mtmp, int *pdistmin,
                       int *pdistmax);
#define m_balks_at_approaching teleport_monmove_test_m_balks_at_approaching
extern boolean teleport_monmove_test_holds_up_web(coordxy x, coordxy y);
#define holds_up_web teleport_monmove_test_holds_up_web
extern int teleport_monmove_test_count_webbing_walls(coordxy x, coordxy y);
#define count_webbing_walls teleport_monmove_test_count_webbing_walls
extern boolean teleport_monmove_test_soko_allow_web(struct monst *mon);
#define soko_allow_web teleport_monmove_test_soko_allow_web
extern void teleport_monmove_test_maybe_spin_web(struct monst *mtmp);
#define maybe_spin_web teleport_monmove_test_maybe_spin_web
extern boolean teleport_monmove_test_m_search_items(
    struct monst *mtmp,
    coordxy *ggx, coordxy *ggy,
    int *mmoved,
    int *appr);
#define m_search_items teleport_monmove_test_m_search_items
extern int teleport_monmove_test_postmov(
    struct monst *mtmp,
    struct permonst *ptr,
    coordxy omx, coordxy omy,
    int mmoved,
    unsigned seenflgs,
    boolean can_tunnel,
    boolean can_unlock,
    boolean can_open);
#define postmov teleport_monmove_test_postmov
extern boolean teleport_monmove_test_stuff_prevents_passage(struct monst *mtmp);
#define stuff_prevents_passage teleport_monmove_test_stuff_prevents_passage
extern int teleport_monmove_test_vamp_shift(
    struct monst *mon,
    struct permonst *ptr,
    boolean domsg);
#define vamp_shift teleport_monmove_test_vamp_shift
#endif
#include "tu-monmove-layout.h"

static struct monst*actor(int i){return i==-2?&gy.youmonst:i>=0&&i<nmon?monsters[i]:NULL;}
static int foreign_occupation(void){return 19;}
void probe_reset(unsigned initial){int i,x,y;for(i=0;i<nobj;i++)free(nodes[i]);for(i=0;i<nmon;i++){if(monsters[i]->mextra){free(monsters[i]->mextra->edog);free(monsters[i]->mextra);}free(monsters[i]);}if(growth)free(growth);growth=NULL;nmon=nobj=nr=ri=0;seed=initial;memset(nodes,0,sizeof nodes);memset(monsters,0,sizeof monsters);memset(traps,0,sizeof traps);memset(trapactive,0,sizeof trapactive);memset(opts,0,sizeof opts);memset(ret,0,sizeof ret);memset(cells,0,sizeof cells);memset(&candidates,0,sizeof candidates);memset(&point,0,sizeof point);memset(&engraving,0,sizeof engraving);memset(&stairs,0,sizeof stairs);memset(&returning,0,sizeof returning);memset(&u,0,sizeof u);memset(&svc,0,sizeof svc);memset(&svm,0,sizeof svm);memset(&svl,0,sizeof svl);memset(&gy,0,sizeof gy);memset(&gv,0,sizeof gv);memset(&gm,0,sizeof gm);memset(&go,0,sizeof go);memset(&gn,0,sizeof gn);memset(&gi,0,sizeof gi);memset(&gb,0,sizeof gb);memset(&gk,0,sizeof gk);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&a11y,0,sizeof a11y);objects_globals_init();monst_globals_init();for(i=0;i<NUM_OBJECTS;i++)objects[i].oc_name_idx=objects[i].oc_descr_idx=i;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;vision[y][x]=IN_SIGHT|COULD_SEE;}for(y=0;y<ROWNO;y++)visionrows[y]=vision[y];gv.viz_array=visionrows;u.ux=10;u.uy=10;u.ux0=9;u.uy0=10;u.uz.dnum=1;u.uz.dlevel=2;u.uhp=100;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=100;svm.moves=100;flags.verbose=1;opts[0]=1;opts[4]=1;opts[5]=12;opts[7]=1;point.x=11;point.y=10;returning.range=8;rogue_level.dnum=9;rogue_level.dlevel=1;astral_level.dnum=9;astral_level.dlevel=2;uwep=uarm=uball=uchain=NULL;tracebuf[0]=caller[0]=0;}
void probe_option(int i,int v){opts[i]=v;}void probe_return(int i,long v){ret[i]=v;}int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nr=n;ri=0;}int probe_rng_count(void){return ri;}unsigned probe_rng_state(void){return seed;}const char*probe_trace(void){return tracebuf;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_new_mon(int type,int x,int y){struct monst*m;if(nmon>=16)panic("mon limit");m=calloc(1,sizeof*m);m->data=&mons[type];m->mnum=type;m->cham=NON_PM;m->m_id=nmon+100;m->mx=x;m->my=y;m->mux=u.ux;m->muy=u.uy;m->mhp=m->mhpmax=100;m->mcanmove=m->mcansee=1;m->m_lev=10;m->mextra=calloc(1,sizeof*m->mextra);m->mextra->edog=calloc(1,sizeof* m->mextra->edog);m->nmon=fmon;fmon=m;svl.level.monsters[x][y]=m;monsters[nmon++]=m;return nmon-1;}
int probe_new_obj(int type,int place,int who,int x,int y){struct obj*o;if(nobj>=64)panic("obj limit");o=calloc(1,sizeof*o);o->otyp=type;o->oclass=objects[type].oc_class;o->o_id=nobj+100;o->quan=1;o->corpsenm=NON_PM;o->ox=x;o->oy=y;o->where=place;nodes[nobj++]=o;if(place==OBJ_FLOOR){o->nobj=fobj;fobj=o;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;}else if(place==OBJ_MINVENT){o->ocarry=actor(who);o->nobj=actor(who)->minvent;actor(who)->minvent=o;}else if(place==OBJ_INVENT){o->nobj=gi.invent;gi.invent=o;}return nobj-1;}
void probe_equipment(int i,int obj){struct obj*o=obj<0?NULL:nodes[obj];switch(i){case 0:uwep=o;break;case 1:uarm=o;break;case 2:uball=o;break;case 3:uchain=o;break;case 4:actor(0)->mw=o;break;}}
void probe_hero(int i,long v){switch(i){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.ux0=v;break;case 3:u.uy0=v;break;case 4:u.uz.dnum=v;break;case 5:u.uz.dlevel=v;break;case 6:u.dx=v;break;case 7:u.dy=v;break;case 8:u.uswallow=v;break;case 9:u.uinwater=v;break;case 10:u.uundetected=v;break;case 11:u.uinvulnerable=v;break;case 12:u.ustuck=actor(v);break;case 13:u.uhp=v;break;case 14:gm.multi=v;break;case 15:svm.moves=v;break;case 16:a11y.mon_movement=v;break;case 17:flags.verbose=v;break;case 18:go.occupation=v?foreign_occupation:NULL;break;case 19:u.umonnum=v;break;case 20:gy.youmonst.data=&mons[v];break;case 21:gi.invent=v<0?NULL:nodes[v];break;case 22:u.uroleplay.deaf=v;break;case 23:gy.youmonst.m_ap_type=v;break;case 24:gy.youmonst.mappearance=v;break;}}
void probe_property(int id,int field,long v){if(field==0)u.uprops[id].intrinsic=v;else if(field==1)u.uprops[id].extrinsic=v;else u.uprops[id].blocked=v;}
void probe_mon(int slot,int i,long v){struct monst*m=actor(slot);switch(i){case 0:m->mhp=v;break;case 1:m->mhpmax=v;break;case 2:m->mx=v;break;case 3:m->my=v;break;case 4:m->mux=v;break;case 5:m->muy=v;break;case 6:m->mspec_used=v;break;case 7:m->meating=v;break;case 8:m->movement=v;break;case 9:m->mtame=v;break;case 10:m->m_lev=v;break;case 11:m->weapon_check=v;break;case 12:m->m_ap_type=v;break;case 13:m->mappearance=v;break;case 14:m->mstrategy=v;break;case 15:m->mstate=v;break;case 16:m->cham=v;break;case 17:m->data=&mons[v];break;case 18:m->mw=v<0?NULL:nodes[v];break;case 19:m->mextra->edog->hungrytime=v;break;}}
void probe_obj(int slot,int i,long v){struct obj*o=nodes[slot];switch(i){case 0:o->quan=v;break;case 1:o->otyp=v;o->oclass=objects[v].oc_class;break;case 2:o->oclass=v;break;case 3:o->oartifact=v;break;case 4:o->corpsenm=v;break;case 5:o->o_id=v;break;case 6:o->ox=v;break;case 7:o->oy=v;break;case 8:o->cobj=v<0?NULL:nodes[v];break;}}
void probe_tile(int x,int y,int field,int v){if(field==0)levl[x][y].typ=v;else if(field==1)levl[x][y].flags=v;else if(field==2)levl[x][y].lit=v;else if(field==3)levl[x][y].edge=v;else vision[y][x]=v;}
void probe_level(int i,int v){switch(i){case 0:svl.level.flags.arboreal=v;break;case 1:svl.level.flags.shortsighted=v;break;case 2:svl.level.flags.sokoban_rules=v;break;case 3:rogue_level.dnum=v;break;case 4:rogue_level.dlevel=v;break;case 5:astral_level.dnum=v;break;}}
void probe_trap(int x,int y,int type,int seen){traps[x][y].tx=x;traps[x][y].ty=y;traps[x][y].ttyp=type;traps[x][y].tseen=seen;trapactive[x][y]=1;}
void probe_point(int x,int y){point.x=x;point.y=y;}void probe_candidate(int index,int x,int y,long flags){candidates.poss[index].x=x;candidates.poss[index].y=y;candidates.info[index]=flags;if(candidates.cnt<=index)candidates.cnt=index+1;}void probe_candidates(int n){candidates.cnt=n;}
void probe_mon_bit(int slot,int field,unsigned v){struct monst*o=actor(slot);switch(field){case 0:o->isgd=v;break;case 1:o->isminion=v;break;case 2:o->ispriest=v;break;case 3:o->isshk=v;break;case 4:o->iswiz=v;break;case 5:o->mblinded=v;break;case 6:o->mcan=v;break;case 7:o->mcanmove=v;break;case 8:o->mcansee=v;break;case 9:o->mconf=v;break;case 10:o->mflee=v;break;case 11:o->mfleetim=v;break;case 12:o->mfrozen=v;break;case 13:o->minvis=v;break;case 14:o->mpeaceful=v;break;case 15:o->msleeping=v;break;case 16:o->mspotted=v;break;case 17:o->mstun=v;break;case 18:o->mtrapped=v;break;case 19:o->mundetected=v;break;case 20:o->perminvis=v;break;case 21:o->wormno=v;break;}}
void probe_obj_bit(int slot,int field,unsigned v){struct obj*o=nodes[slot];switch(field){case 0:o->blessed=v;break;case 1:o->cursed=v;break;case 2:o->lamplit=v;break;case 3:o->no_charge=v;break;case 4:o->unpaid=v;break;}}
long probe_action(int op,int a,int b,int c){switch(op){case 0:msg_mon_movement(actor(a),b,c);break;case 1:return mb_trapped(actor(a),b);case 2:mon_track_add(actor(a),b,c);break;case 3:mon_track_clear(actor(a));break;case 4:return monhaskey(actor(a),b);case 5:mon_yells(actor(a),"Fixture shout");break;case 6:return m_can_break_boulder(actor(a));case 7:m_break_boulder(actor(a),b,c);break;case 8:watch_on_duty(actor(a));break;case 9:return dochugw(actor(a),b);case 10:return onscary(b,c,actor(a));case 11:mon_regen(actor(a),b);break;case 12:return disturb(actor(a));case 13:release_hero(actor(a));break;case 14:return mid(find_pmmonst(a));case 15:return bee_eat_jelly(actor(a),nodes[b]);case 16:return gelcube_digests(actor(a));case 17:monflee(actor(a),b,c,opts[30]);break;case 18:distfleeck(actor(a),&cells[0],opts[31]?&cells[0]:&cells[1],opts[31]?&cells[0]:&cells[2]);break;case 19:return m_arrival(actor(a));case 20:mind_blast(actor(a));break;case 21:m_everyturn_effect(actor(a));break;case 22:m_postmove_effect(actor(a));break;case 23:return dochug(actor(a));case 24:return mon_would_take_item(actor(a),nodes[b]);case 25:return mon_would_consume_item(actor(a),nodes[b]);case 26:return itsstuck(actor(a));case 27:return should_displace(actor(a),&candidates,b,c);case 28:return m_digweapon_check(actor(a),b,c);case 29:return leppie_avoidance(actor(a));case 30:leppie_stash(actor(a));break;case 31:return m_balks_at_approaching(b,actor(a),opts[32]?NULL:&cells[0],opts[32]?NULL:opts[31]?&cells[0]:&cells[1]);case 32:return holds_up_web(b,c);case 33:return count_webbing_walls(b,c);case 34:return soko_allow_web(actor(a));case 35:maybe_spin_web(actor(a));break;case 36:return m_avoid_kicked_loc(actor(a),b,c);case 37:return m_avoid_soko_push_loc(actor(a),b,c);case 38:return m_search_items(actor(a),&point.x,opts[31]?&point.x:&point.y,&cells[0],opts[31]?&cells[0]:&cells[1]);case 39:return postmov(actor(a),actor(a)->data,b,c,opts[33],opts[34],opts[35],opts[36],opts[37]);case 40:return m_move(actor(a),b);case 41:return m_move_aggress(actor(a),b,c);case 42:return can_hide_under_obj(a<0?NULL:nodes[a]);case 43:dissolve_bars(b,c);break;case 44:return closed_door(b,c);case 45:return accessible(b,c);case 46:set_apparxy(actor(a));break;case 47:return undesirable_disp(actor(a),b,c);case 48:return stuff_prevents_passage(actor(a));case 49:return can_ooze(actor(a));case 50:return can_fog(actor(a));case 51:return vamp_shift(actor(a),&mons[b],c);default:panic("bad action %d",op);}return 0;}
void*probe_pointer(int kind,int i){switch(kind){case 0:return &u;case 1:return actor(i);case 2:return nodes[i];case 3:return levl;case 4:return vision;case 5:return &point;case 6:return cells;case 7:return &candidates;case 8:return &traps[i/ROWNO][i%ROWNO];case 9:return &svc;case 10:return actor(i)->mextra->edog;case 11:return &gy.youmonst;case 12:return &gk.kickedloc;case 13:return &engraving;case 14:return &stairs;default:return NULL;}}
long probe_scalar(int i){switch(i){case 0:return mid(u.ustuck);case 1:return u.uhp;case 2:return u.uundetected;case 3:return gy.youmonst.m_ap_type;case 4:return gy.youmonst.mappearance;case 5:return gn.notonhead;case 6:return gb.bhitpos.x;case 7:return gb.bhitpos.y;case 8:return point.x;case 9:return point.y;case 10:return go.occupation!=NULL;case 11:return cells[0];case 12:return cells[1];case 13:return cells[2];default:return 0;}}
int probe_count(int k){return k?nobj:nmon;}int probe_mon_identity(int i,int k){struct monst*m=actor(i);switch(k){case 0:return m->data->pmidx;case 1:return mid(m->nmon);case 2:return oid(m->mw);case 3:return oid(m->minvent);default:return-1;}}int probe_obj_link(int i,int k){return oid(k?nodes[i]->nexthere:nodes[i]->nobj);}int probe_grid(int x,int y,int k){return k?oid(svl.level.objects[x][y]):mid(svl.level.monsters[x][y]);}
const char*probe_grid_state(void){static char out[65536];size_t n=0;int x,y;out[0]=0;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)if(svl.level.monsters[x][y]||svl.level.objects[x][y]||trapactive[x][y])n+=snprintf(out+n,sizeof out-n,"%d,%d:%d:%d:%d:%d:%d;",x,y,mid(svl.level.monsters[x][y]),oid(svl.level.objects[x][y]),trapactive[x][y],traps[x][y].ttyp,traps[x][y].tseen);return out;}
const unsigned char*probe_class_list(int which){
#ifdef TELEPORT_REFERENCE_TU
return (const unsigned char*)(which?magical:practical);
#else
extern void*teleport_monmove_storage(void);return (const unsigned char*)teleport_monmove_storage()+(which?5:0);
#endif
}

void probe_cells(int index,int v){cells[index]=v;}
