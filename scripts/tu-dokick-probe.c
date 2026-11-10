#include "hack.h"
#include "artifact.h"
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(u) u;__typeof__(gy) gy;__typeof__(svc) svc;__typeof__(gb) gb;__typeof__(gm) gm;__typeof__(gk) gk;__typeof__(gn) gn;__typeof__(gg) gg;__typeof__(gi) gi;__typeof__(svm) svm;__typeof__(svl) svl;__typeof__(svd) svd;__typeof__(svk) svk;__typeof__(flags) flags;__typeof__(iflags) iflags;__typeof__(gu) gu;__typeof__(svp) svp;__typeof__(gv) gv;__typeof__(windowprocs) windowprocs;
const char ynchars[]="yn";const struct c_color_names c_color_names={.c_black="black"};
struct obj *uarm,*uarmf,*uball,*uchain;winid WIN_MESSAGE=1;
const struct c_common_strings c_common_strings={.c_something="something",.c_Something="Something",.c_nothing_happens="Nothing happens."};
const struct Gender genders[]={{.his="his"},{.his="her"},{.his="its"},{.his="their"}};
static struct monst monsters[3];static struct obj items[6];static struct mextra extras[3];static struct eshk shops[3];static struct oextra oextras[6];static stairway stairs;static struct trap trap;
static int opts[96],seed=1;static void *growth;static char trace[131072],result[16384],snap[16384],buffers[6][BUFSZ];static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long mid(const struct monst *p){return !p?-1:p==&gy.youmonst?-2:p>=monsters&&p<monsters+3?p-monsters:-3;}
static long oid(const struct obj *p){return !p?-1:p>=items&&p<items+6?p-items:-3;}
static void callback(int stage){if(opts[80]==stage){opts[80]=0;append("nested:%d;",down_gate(10,10));}if(opts[81]==stage&&!growth){opts[81]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char *fmt,...){(void)fmt;abort();}void impossible(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
#define MSG(fn) void fn(const char *fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#fn ":%s;",b);callback(1);}
MSG(pline) MSG(pline_The) MSG(Norep) MSG(You) MSG(Your) MSG(You_hear) MSG(You_cant) MSG(There) MSG(verbalize)
void mon_yells(struct monst *m,const char *text){append("yell:%ld:%s;",mid(m),text);callback(2);}
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char *file,int line,const char *fn){append("caller:%s:%d:%s;",file,line,fn);}
int(rn2)(int n){seed=(int)((unsigned)seed*1664525U+1013904223U);append("rn2:%d;",n);return n?(unsigned)seed%(unsigned)n:0;}int(rnd)(int n){append("rnd:%d;",n);return n?1+(rn2)(n):1;}int(rnl)(int n){append("rnl:%d;",n);return(rn2)(n);}
char * An(const char * a0){append("An:%s;",a0?a0:"[NULL]");return (char*)a0;}
char * Doname2(struct obj * a0){append("Doname2:%ld;",oid(a0));return "item";}
boolean In_mines(d_level * a0){append("In_mines:%d;",!!a0);return opts[16];}
boolean Is_botlevel(d_level * a0){append("Is_botlevel:%d;",!!a0);return opts[17];}
char * Monnam(struct monst * a0){append("Monnam:%ld;",mid(a0));return "monster";}
char * Shknam(struct monst * a0){append("Shknam:%ld;",mid(a0));return "monster";}
char * The(const char * a0){append("The:%s;",a0?a0:"[NULL]");return (char*)a0;}
char * Tobjnam(struct obj * a0,const char * a1){append("Tobjnam:%ld:%s;",oid(a0),a1?a1:"[NULL]");return "The item";}
char * a_monnam(struct monst * a0){append("a_monnam:%ld;",mid(a0));return "monster";}
void abuse_dog(struct monst * a0){append("abuse_dog:%ld;",mid(a0));if(opts[40])a0->mtame=0;}
struct monst * activate_statue_trap(struct trap * a0,coordxy a1,coordxy a2,boolean a3){append("activate_statue_trap:%d:%ld:%ld:%ld;",!!a0,(long)a1,(long)a2,(long)a3);return NULL;}
schar acurr(int a0){append("acurr:%ld;",(long)a0);return opts[30];}
schar acurrstr(void){append("acurrstr;");return opts[30];}
void add_damage(coordxy a0,coordxy a1,long a2){append("add_damage:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(14);}
void add_to_migration(struct obj * a0){append("add_to_migration:%ld;",oid(a0));a0->nobj=gm.migrating_objs;gm.migrating_objs=a0;a0->where=OBJ_MIGRATING;}
int add_to_minv(struct monst * a0,struct obj * a1){append("add_to_minv:%ld:%ld;",mid(a0),oid(a1));a1->nobj=a0->minvent;a0->minvent=a1;a1->where=OBJ_MINVENT;return 0;}
void addtobill(struct obj * a0,boolean a1,boolean a2,boolean a3){append("addtobill:%ld:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2,(long)a3);callback(14);}
void adjalign(int a0){append("adjalign:%ld;",(long)a0);callback(14);}
void altar_wrath(coordxy a0,coordxy a1){append("altar_wrath:%ld:%ld;",(long)a0,(long)a1);callback(14);}
boolean angry_guards(boolean a0){append("angry_guards:%ld;",(long)a0);return opts[58];}
boolean attack_checks(struct monst * a0,struct obj * a1){append("attack_checks:%ld:%ld;",mid(a0),oid(a1));callback(3);return opts[35];}
boolean attacktype(struct permonst * a0,int a1){append("attacktype:%d:%ld;",a0?monsndx(a0):NON_PM,(long)a1);for(int i=0;i<NATTK;i++)if(a0->mattk[i].aatyp==a1)return 1;return 0;}
void b_trapped(const char * a0,int a1){append("b_trapped:%s:%ld;",a0?a0:"[NULL]",(long)a1);}
const char * body_part(int a0){append("body_part:%ld;",(long)a0);return a0==FOOT?"foot":"leg";}
void breakchestlock(struct obj * a0,boolean a1){append("breakchestlock:%ld:%ld;",oid(a0),(long)a1);a0->olocked=0;a0->obroken=1;}
int breaks(struct obj * a0,coordxy a1,coordxy a2){append("breaks:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2);return opts[10];}
boolean breaktest(struct obj * a0){append("breaktest:%ld;",oid(a0));return opts[9];}
int canseemon(struct monst * a0){append("canseemon:%ld;",mid(a0));return opts[1];}
void change_luck(schar a0){append("change_luck:%ld;",(long)a0);callback(14);}
void check_caitiff(struct monst * a0){append("check_caitiff:%ld;",mid(a0));callback(14);}
boolean chest_trap(struct obj * a0,int a1,boolean a2){append("chest_trap:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2);return opts[59];}
struct monst * christen_orc(struct monst * a0,const char * a1,const char * a2){append("christen_orc:%ld:%s:%s;",mid(a0),a1?a1:"[NULL]",a2?a2:"[NULL]");return a0;}
boolean closed_door(coordxy a0,coordxy a1){append("closed_door:%ld:%ld;",(long)a0,(long)a1);return svl.level.locations[a0][a1].typ==DOOR&&(svl.level.locations[a0][a1].doormask&D_CLOSED);}
long contained_gold(struct obj * a0,boolean a1){append("contained_gold:%ld:%ld;",oid(a0),(long)a1);return opts[53];}
char * corpse_xname(struct obj * a0,const char * a1,unsigned a2){append("corpse_xname:%ld:%s:%ld;",oid(a0),a1?a1:"[NULL]",(long)a2);return "item";}
boolean costly_adjacent(struct monst * a0,coordxy a1,coordxy a2){append("costly_adjacent:%ld:%ld:%ld;",mid(a0),(long)a1,(long)a2);return opts[4];}
void costly_gold(coordxy a0,coordxy a1,long a2,boolean a3){append("costly_gold:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2,(long)a3);callback(14);}
boolean costly_spot(coordxy a0,coordxy a1){append("costly_spot:%ld:%ld;",(long)a0,(long)a1);return opts[4];}
const char * currency(long a0){append("currency:%ld;",(long)a0);return "zorkmids";}
void cvt_sdoor_to_door(struct rm * a0){append("cvt_sdoor_to_door:%d;",!!a0);a0->typ=DOOR;}
int damageum(struct monst * a0,struct attack * a1,int a2){append("damageum:%ld:%d:%ld;",mid(a0),!!a1,(long)a2);a0->mhp-=opts[41];return opts[42];}
void dealloc_obj(struct obj * a0){append("dealloc_obj:%ld;",oid(a0));a0->where=OBJ_FREE;}
void del_engr_at(coordxy a0,coordxy a1){append("del_engr_at:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void delobj(struct obj * a0){append("delobj:%ld;",oid(a0));a0->where=OBJ_FREE;}
void disturb_grave(coordxy a0,coordxy a1){append("disturb_grave:%ld:%ld;",(long)a0,(long)a1);callback(14);}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){append("dmgtype_fromattack:%d:%ld:%ld;",a0?monsndx(a0):NON_PM,(long)a1,(long)a2);for(int i=0;i<NATTK;i++)if(a0->mattk[i].adtyp==a1&&a0->mattk[i].aatyp==a2)return &((struct permonst*)a0)->mattk[i];return NULL;}
char * doname(struct obj * a0){append("doname:%ld;",oid(a0));return "item";}
void donate_gold(long a0,struct monst * a1,boolean a2){append("donate_gold:%ld:%ld:%ld;",(long)a0,mid(a1),(long)a2);callback(14);}
xint16 dunlev(d_level * a0){append("dunlev:%d;",!!a0);return a0->dlevel;}
xint16 dunlevs_in_dungeon(d_level * a0){append("dunlevs_in_dungeon:%d;",!!a0);return opts[18];}
boolean enexto(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){append("enexto:%d:%ld:%ld:%d;",!!a0,(long)a1,(long)a2,a3?monsndx(a3):NON_PM);if(opts[64]){a0->x=a1+1;a0->y=a2;return 1;}return 0;}
void exercise(int a0,boolean a1){append("exercise:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void fall_through(boolean a0,unsigned a1){append("fall_through:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void feel_location(coordxy a0,coordxy a1){append("feel_location:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void feel_newsym(coordxy a0,coordxy a1){append("feel_newsym:%ld:%ld;",(long)a0,(long)a1);callback(14);}
boolean find_drawbridge(coordxy * a0,coordxy * a1){append("find_drawbridge:%d:%d;",!!a0,!!a1);if(opts[15]){*a0=11;*a1=10;}callback(10);return opts[15];}
struct monst * find_objowner(struct obj * a0,coordxy a1,coordxy a2){append("find_objowner:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2);return opts[5]?&monsters[1]:NULL;}
int find_roll_to_hit(struct monst * a0,uchar a1,struct obj * a2,int * a3,int * a4){append("find_roll_to_hit:%ld:%ld:%ld:%d:%d;",mid(a0),(long)a1,oid(a2),!!a3,!!a4);*a3=opts[44];*a4=opts[45];callback(5);return opts[46];}
void find_trap(struct trap * a0){append("find_trap:%d;",!!a0);a0->tseen=1;}
void finish_meating(struct monst * a0){append("finish_meating:%ld;",mid(a0));callback(14);}
boolean flooreffects(struct obj * a0,coordxy a1,coordxy a2,const char * a3){append("flooreffects:%ld:%ld:%ld:%s;",oid(a0),(long)a1,(long)a2,a3?a3:"[NULL]");return opts[11];}
void free_oname(struct obj * a0){append("free_oname:%ld;",oid(a0));if(a0->oextra)a0->oextra->oname=NULL;}
int getdir(const char * a0){append("getdir:%s;",a0?a0:"[NULL]");callback(11);return opts[3];}
int glyph_at(coordxy a0,coordxy a1){append("glyph_at:%ld:%ld;",(long)a0,(long)a1);return opts[23];}
boolean goodpos(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){append("goodpos:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,mid(a2),(long)a3);return opts[36];}
const char * hcolor(const char * a0){append("hcolor:%s;",a0?a0:"[NULL]");return a0;}
int hero_breaks(struct obj * a0,coordxy a1,coordxy a2,unsigned a3){append("hero_breaks:%ld:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2,(long)a3);return opts[10];}
long hidden_gold(boolean a0){append("hidden_gold:%ld;",(long)a0);return opts[52];}
const char * hliquid(const char * a0){append("hliquid:%s;",a0?a0:"[NULL]");return a0;}
void hot_pursuit(struct monst * a0){append("hot_pursuit:%ld;",mid(a0));callback(14);}
void hurtle(int a0,int a1,int a2,boolean a3){append("hurtle:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2,(long)a3);callback(14);}
void impact_disturbs_zombies(struct obj * a0,boolean a1){append("impact_disturbs_zombies:%ld:%ld;",oid(a0),(long)a1);callback(14);}
char * in_rooms(coordxy a0,coordxy a1,int a2){append("in_rooms:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);static char room[2];room[0]=opts[6];room[1]=0;return room;}
boolean in_town(coordxy a0,coordxy a1){append("in_town:%ld:%ld;",(long)a0,(long)a1);return opts[7];}
char inside_shop(coordxy a0,coordxy a1){append("inside_shop:%ld:%ld;",(long)a0,(long)a1);return opts[6];}
void instapetrify(const char * a0){append("instapetrify:%s;",a0?a0:"[NULL]");callback(14);}
int inv_weight(void){append("inv_weight;");return opts[31];}
boolean is_art(struct obj * a0,int a1){append("is_art:%ld:%ld;",oid(a0),(long)a1);return a0&&a0->oartifact==a1;}
int is_drawbridge_wall(coordxy a0,coordxy a1){append("is_drawbridge_wall:%ld:%ld;",(long)a0,(long)a1);return opts[15];}
boolean is_ice(coordxy a0,coordxy a1){append("is_ice:%ld:%ld;",(long)a0,(long)a1);return svl.level.locations[a0][a1].typ==ICE;}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool:%ld:%ld;",(long)a0,(long)a1);return svl.level.locations[a0][a1].typ==POOL;}
boolean is_unpaid(struct obj * a0){append("is_unpaid:%ld;",oid(a0));return a0->unpaid||opts[8];}
int isok(coordxy a0,coordxy a1){append("isok:%ld:%ld;",(long)a0,(long)a1);return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
void kick_steed(void){append("kick_steed;");callback(14);}
void killed(struct monst * a0){append("killed:%ld;",mid(a0));a0->mhp=0;}
char * killer_xname(struct obj * a0){append("killer_xname:%ld;",oid(a0));return "item";}
void legs_in_no_shape(const char * a0,boolean a1){append("legs_in_no_shape:%s:%ld;",a0?a0:"[NULL]",(long)a1);callback(14);}
void losehp(int a0,const char * a1,schar a2){append("losehp:%ld:%s:%ld;",(long)a0,a1?a1:"[NULL]",(long)a2);callback(14);}
boolean m_in_out_region(struct monst * a0,coordxy a1,coordxy a2){append("m_in_out_region:%ld:%ld:%ld;",mid(a0),(long)a1,(long)a2);return opts[37];}
void make_angry_shk(struct monst * a0,coordxy a1,coordxy a2){append("make_angry_shk:%ld:%ld:%ld;",mid(a0),(long)a1,(long)a2);callback(14);}
void make_happy_shk(struct monst * a0,boolean a1){append("make_happy_shk:%ld:%ld;",mid(a0),(long)a1);callback(14);}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:%d:%ld:%ld:%ld;",a0?monsndx(a0):NON_PM,(long)a1,(long)a2,(long)a3);monsters[2].data=a0;monsters[2].mx=a1;monsters[2].my=a2;callback(12);return opts[26]?&monsters[2]:NULL;}
char * makeplural(const char * a0){append("makeplural:%s;",a0?a0:"[NULL]");return (char*)a0;}
void map_invisible(coordxy a0,coordxy a1){append("map_invisible:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void maybe_mnexto(struct monst * a0){append("maybe_mnexto:%ld;",mid(a0));if(opts[43]){a0->mx++;a0->my++;}}
void maybe_unhide_at(coordxy a0,coordxy a1){append("maybe_unhide_at:%ld:%ld;",(long)a0,(long)a1);callback(14);}
int mintrap(struct monst * a0,unsigned a1){append("mintrap:%ld:%ld;",mid(a0),(long)a1);return opts[38];}
void miss(const char * a0,struct monst * a1){append("miss:%s:%ld;",a0?a0:"[NULL]",mid(a1));callback(14);}
void missum(struct monst * a0,struct attack * a1,boolean a2){append("missum:%ld:%d:%ld;",mid(a0),!!a1,(long)a2);callback(14);}
struct obj * mkgold(long a0,coordxy a1,coordxy a2){append("mkgold:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);items[4].quan=a0;return &items[4];}
struct obj * mksobj(int a0,boolean a1,boolean a2){append("mksobj:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);items[4].otyp=a0;items[4].oclass=objects[a0].oc_class;items[4].quan=1;return &items[4];}
struct obj * mksobj_at(int a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("mksobj_at:%ld:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2,(long)a3,(long)a4);items[4].otyp=a0;items[4].oclass=objects[a0].oc_class;items[4].quan=1;items[4].ox=a1;items[4].oy=a2;return &items[4];}
void mon_maybe_unparalyze(struct monst * a0){append("mon_maybe_unparalyze:%ld;",mid(a0));if(opts[47])a0->mcanmove=1;}
char * mon_nam(struct monst * a0){append("mon_nam:%ld;",mid(a0));return "monster";}
long money_cnt(struct obj * a0){append("money_cnt:%ld;",oid(a0));return opts[51];}
void monflee(struct monst * a0,int a1,boolean a2,boolean a3){append("monflee:%ld:%ld:%ld:%ld;",mid(a0),(long)a1,(long)a2,(long)a3);a0->mflee=1;}
int mpickobj(struct monst * a0,struct obj * a1){append("mpickobj:%ld:%ld;",mid(a0),oid(a1));a1->where=OBJ_MINVENT;a0->minvent=a1;return 0;}
int near_capacity(void){append("near_capacity;");return opts[33];}
void newsym(coordxy a0,coordxy a1){append("newsym:%ld:%ld;",(long)a0,(long)a1);callback(14);}
boolean noteleport_level(struct monst * a0){append("noteleport_level:%ld;",mid(a0));callback(14);return 0;}
void obfree(struct obj * a0,struct obj * a1){append("obfree:%ld:%ld;",oid(a0),oid(a1));a0->where=OBJ_FREE;}
void obj_extract_self(struct obj * a0){append("obj_extract_self:%ld;",oid(a0));struct obj **p=&gm.migrating_objs;while(*p&&*p!=a0)p=&(*p)->nobj;if(*p==a0)*p=a0->nobj;for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){p=&svl.level.objects[x][y];while(*p&&*p!=a0)p=&(*p)->nexthere;if(*p==a0)*p=a0->nexthere;}for(int i=0;i<6;i++){p=&items[i].cobj;while(*p&&*p!=a0)p=&(*p)->nobj;if(*p==a0)*p=a0->nobj;}a0->nobj=a0->nexthere=NULL;a0->where=OBJ_FREE;callback(8);}
boolean obj_resists(struct obj * a0,int a1,int a2){append("obj_resists:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2);return opts[54];}
boolean ok_to_quest(void){append("ok_to_quest;");return opts[19];}
boolean on_level(d_level * a0,d_level * a1){append("on_level:%d:%d;",!!a0,!!a1);return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
char * otense(struct obj * a0,const char * a1){append("otense:%ld:%s;",oid(a0),a1?a1:"[NULL]");return (char*)a1;}
boolean overexertion(void){append("overexertion;");return opts[34];}
int passive(struct monst * a0,struct obj * a1,boolean a2,boolean a3,uchar a4,boolean a5){append("passive:%ld:%ld:%ld:%ld:%ld:%ld;",mid(a0),oid(a1),(long)a2,(long)a3,(long)a4,(long)a5);callback(4);return 0;}
void pay_for_damage(const char * a0,boolean a1){append("pay_for_damage:%s:%ld;",a0?a0:"[NULL]",(long)a1);callback(14);}
void picked_container(struct obj * a0){append("picked_container:%ld;",oid(a0));callback(14);}
void place_monster(struct monst * a0,coordxy a1,coordxy a2){append("place_monster:%ld:%ld:%ld;",mid(a0),(long)a1,(long)a2);a0->mx=a1;a0->my=a2;svl.level.monsters[a1][a2]=a0;}
void place_object(struct obj * a0,coordxy a1,coordxy a2){append("place_object:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2);a0->ox=a1;a0->oy=a2;a0->where=OBJ_FLOOR;a0->nexthere=svl.level.objects[a1][a2];svl.level.objects[a1][a2]=a0;callback(9);}
int poly_gender(void){append("poly_gender;");return opts[25];}
boolean poly_when_stoned(struct permonst * a0){append("poly_when_stoned:%d;",a0?monsndx(a0):NON_PM);return opts[13];}
int polymon(int a0){append("polymon:%ld;",(long)a0);u.umonnum=a0;return opts[14];}
int pronoun_gender(struct monst * a0,unsigned a1){append("pronoun_gender:%ld:%ld;",mid(a0),(long)a1);return 2;}
void recalc_block_point(coordxy a0,coordxy a1){append("recalc_block_point:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void remove_worn_item(struct obj * a0,boolean a1){append("remove_worn_item:%ld:%ld;",oid(a0),(long)a1);callback(14);}
boolean rloco(struct obj * a0){append("rloco:%ld;",oid(a0));a0->ox=12;a0->oy=11;return opts[56];}
int rnd_class(int a0,int a1){append("rnd_class:%ld:%ld;",(long)a0,(long)a1);return a0;}
struct obj * rnd_treefruit_at(coordxy a0,coordxy a1){append("rnd_treefruit_at:%ld:%ld;",(long)a0,(long)a1);return opts[27]?&items[4]:NULL;}
long scatter(coordxy a0,coordxy a1,int a2,unsigned int a3,struct obj * a4){append("scatter:%ld:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2,(long)a3,oid(a4));callback(13);return opts[55];}
void seemimic(struct monst * a0){append("seemimic:%ld;",mid(a0));callback(14);}
int sensemon(struct monst * a0){append("sensemon:%ld;",mid(a0));return opts[2];}
void set_apparxy(struct monst * a0){append("set_apparxy:%ld;",mid(a0));callback(14);}
void set_wounded_legs(long a0,int a1){append("set_wounded_legs:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void setmangry(struct monst * a0,boolean a1){append("setmangry:%ld:%ld;",mid(a0),(long)a1);a0->mpeaceful=0;}
char * shkname(struct monst * a0){append("shkname:%ld;",mid(a0));return "monster";}
struct monst * shop_keeper(char a0){append("shop_keeper:%ld;",(long)a0);return opts[5]?&monsters[1]:NULL;}
void show_glyph(coordxy a0,coordxy a1,int a2){append("show_glyph:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(14);}
void sink_backs_up(coordxy a0,coordxy a1){append("sink_backs_up:%ld:%ld;",(long)a0,(long)a1);callback(14);}
boolean snuff_candle(struct obj * a0){append("snuff_candle:%ld;",oid(a0));return opts[57];}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){append("sobj_at:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);return opts[28]?&items[3]:NULL;}
int special_dmgval(struct monst * a0,struct monst * a1,long a2,long * a3){append("special_dmgval:%ld:%ld:%ld:%d;",mid(a0),mid(a1),(long)a2,!!a3);return opts[39];}
struct obj * splitobj(struct obj * a0,long a1){append("splitobj:%ld:%ld;",oid(a0),(long)a1);items[5]=*a0;items[5].quan=a1;a0->quan-=a1;return &items[5];}
void stackobj(struct obj * a0){append("stackobj:%ld;",oid(a0));callback(14);}
stairway * stairway_at(coordxy a0,coordxy a1){append("stairway_at:%ld:%ld;",(long)a0,(long)a1);return opts[20]?&stairs:NULL;}
stairway * stairway_find_from(d_level * a0,boolean a1){append("stairway_find_from:%d:%ld;",!!a0,(long)a1);return opts[21]?&stairs:NULL;}
long stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("stolen_value:%ld:%ld:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2,(long)a3,(long)a4);shops[1].debit+=opts[48];shops[1].robbed+=opts[49];callback(7);return (long)opts[50];}
void subfrombill(struct obj * a0,struct monst * a1){append("subfrombill:%ld:%ld;",oid(a0),mid(a1));callback(14);}
const char * surface(coordxy a0,coordxy a1){append("surface:%ld:%ld;",(long)a0,(long)a1);return "floor";}
struct trap * t_at(coordxy a0,coordxy a1){append("t_at:%ld:%ld;",(long)a0,(long)a1);return opts[22]?&trap:NULL;}
int thitmonst(struct monst * a0,struct obj * a1){append("thitmonst:%ld:%ld;",mid(a0),oid(a1));return opts[61];}
void u_wipe_engr(int a0){append("u_wipe_engr:%ld;",(long)a0);callback(14);}
void unblock_point(int a0,int a1){append("unblock_point:%ld:%ld;",(long)a0,(long)a1);callback(14);}
boolean undiscovered_artifact(xint16 a0){append("undiscovered_artifact:%ld;",(long)a0);return opts[24];}
boolean unmap_invisible(coordxy a0,coordxy a1){append("unmap_invisible:%ld:%ld;",(long)a0,(long)a1);return 0;}
void use_skill(int a0,int a1){append("use_skill:%ld:%ld;",(long)a0,(long)a1);callback(14);}
void useup(struct obj * a0){append("useup:%ld;",oid(a0));if(a0->quan>1)a0->quan--;else a0->where=OBJ_FREE;}
void wake_nearby(boolean a0){append("wake_nearby:%ld;",(long)a0);callback(14);}
void wake_nearto(coordxy a0,coordxy a1,int a2){append("wake_nearto:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback(14);}
void wakeup(struct monst * a0,boolean a1){append("wakeup:%ld:%ld;",mid(a0),(long)a1);callback(14);}
int water_damage(struct obj * a0,const char * a1,boolean a2){append("water_damage:%ld:%s:%ld;",oid(a0),a1?a1:"[NULL]",(long)a2);return opts[12];}
int weight(struct obj * a0){append("weight:%ld;",oid(a0));callback(6);return a0->owt?a0->owt:10;}
int weight_cap(void){append("weight_cap;");return opts[32];}
char * xname(struct obj * a0){append("xname:%ld;",oid(a0));return "item";}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){append("yn_function:%s:%s:%ld:%ld;",a0?a0:"[NULL]",a1?a1:"[NULL]",(long)a2,(long)a3);return opts[60];}
char *distant_name(struct obj *o,char*(*fn)(struct obj*)){append("distant:%ld;",oid(o));return fn(o);}
const char *singular(struct obj *o,char*(*fn)(struct obj*)){append("singular:%ld;",oid(o));return fn(o);}
struct monst *get_iter_mons(boolean(*fn)(struct monst*)){for(int i=0;i<3;i++){boolean r=fn(&monsters[i]);append("iter:%d:%d;",i,r);if(r)return &monsters[i];}return NULL;}
struct monst *get_iter_mons_xy(boolean(*fn)(struct monst*,coordxy,coordxy),coordxy x,coordxy y){for(int i=0;i<3;i++){boolean r=fn(&monsters[i],x,y);append("iterxy:%d:%d;",i,r);if(r)return &monsters[i];}return NULL;}
struct monst *bhit(int dx,int dy,int range,enum bhit_call_types type,int(*fm)(struct monst*,struct obj*),int(*fo)(struct obj*,struct obj*),struct obj **o){append("bhit:%d:%d:%d:%d:%d:%d:%d;",dx,dy,range,type,!!fm,!!fo,o==&gk.kickedobj);gb.bhitpos.x=10+dx;gb.bhitpos.y=10+dy;if(opts[62])*o=NULL;callback(15);return opts[63]?&monsters[0]:NULL;}
static void fixture_display(winid win,boolean b){append("display:%d:%d;",win,b);callback(16);}
#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/dokick.c"
#else
extern int teleport_dokick_test_kick_nondoor(coordxy x, coordxy y, int avrg_attrib);
#define kick_nondoor teleport_dokick_test_kick_nondoor
extern void teleport_dokick_test_kick_dumb(coordxy x, coordxy y);
#define kick_dumb teleport_dokick_test_kick_dumb
extern boolean teleport_dokick_test_maybe_kick_monster(struct monst *mon, coordxy x, coordxy y);
#define maybe_kick_monster teleport_dokick_test_maybe_kick_monster
extern void teleport_dokick_test_otransit_msg(struct obj *otmp, boolean nodrop, boolean chainthere, long num);
#define otransit_msg teleport_dokick_test_otransit_msg
extern int teleport_dokick_test_kick_object(coordxy x, coordxy y, char *kickobjnam);
#define kick_object teleport_dokick_test_kick_object
extern boolean teleport_dokick_test_watchman_thief_arrest(struct monst *mtmp);
#define watchman_thief_arrest teleport_dokick_test_watchman_thief_arrest
extern void teleport_dokick_test_kick_door(coordxy x, coordxy y, int avrg_attrib);
#define kick_door teleport_dokick_test_kick_door
extern char * teleport_dokick_test_kickstr(char *buf, const char *kickobjnam);
#define kickstr teleport_dokick_test_kickstr
extern void teleport_dokick_test_drop_to(coord *cc, schar loc, coordxy x, coordxy y);
#define drop_to teleport_dokick_test_drop_to
extern boolean teleport_dokick_test_watchman_door_damage(struct monst *mtmp, coordxy x, coordxy y);
#define watchman_door_damage teleport_dokick_test_watchman_door_damage
extern void teleport_dokick_test_kick_ouch(coordxy x, coordxy y, const char *kickobjnam);
#define kick_ouch teleport_dokick_test_kick_ouch
extern void teleport_dokick_test_kick_monster(struct monst *mon, coordxy x, coordxy y);
#define kick_monster teleport_dokick_test_kick_monster
extern int teleport_dokick_test_really_kick_object(coordxy x, coordxy y);
#define really_kick_object teleport_dokick_test_really_kick_object
extern void teleport_dokick_test_kickdmg(struct monst *mon, boolean clumsy);
#define kickdmg teleport_dokick_test_kickdmg
#endif
#include "tu-dokick-layout.h"
unsigned probe_layout_count(void){return SIZE(dokick_layout);}const char *probe_layout_name(unsigned i){return dokick_layout[i].name;}size_t probe_layout_value(unsigned i){return dokick_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}const char *probe_trace(void){return trace;}const char *probe_result(void){return result;}
void probe_option(int i,int v){opts[i]=v;}void probe_seed(int v){seed=v;}void probe_clear(void){trace[0]=result[0]=0;}
void *probe_mon(int i){return i<0?NULL:i==3?&gy.youmonst:&monsters[i];}void *probe_obj(int i){return i<0?NULL:&items[i];}void *probe_buffer(int i){return buffers[i];}void *probe_coord(void){return &gb.bhitpos;}
void probe_reset(void){int x,y;if(growth){free(growth);growth=NULL;}memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&gk,0,sizeof gk);memset(&gm,0,sizeof gm);memset(&gg,0,sizeof gg);memset(&gb,0,sizeof gb);memset(&gn,0,sizeof gn);memset(&flags,0,sizeof flags);memset(&svc,0,sizeof svc);memset(monsters,0,sizeof monsters);memset(items,0,sizeof items);memset(extras,0,sizeof extras);memset(shops,0,sizeof shops);memset(oextras,0,sizeof oextras);memset(&trap,0,sizeof trap);memset(&stairs,0,sizeof stairs);memset(opts,0,sizeof opts);memset(buffers,0,sizeof buffers);objects_globals_init();monst_globals_init();opts[1]=1;opts[3]=1;opts[19]=1;opts[30]=18;opts[31]=-100;opts[32]=1000;opts[36]=1;opts[37]=1;opts[46]=20;opts[60]=121;seed=1;u.ux=u.uy=10;u.dx=1;u.dy=0;u.ulevel=5;u.umonster=u.umonnum=PM_HUMAN;u.uz.dnum=0;u.uz.dlevel=1;gu.urole.mnum=PM_WIZARD;gy.youmonst.data=&mons[PM_HUMAN];air_level.dnum=10;air_level.dlevel=1;water_level.dnum=11;water_level.dlevel=1;stronghold_level.dnum=12;stronghold_level.dlevel=1;qstart_level.dnum=13;qstart_level.dlevel=1;astral_level.dnum=14;astral_level.dlevel=1;valley_level.dnum=15;valley_level.dlevel=1;stairs.sx=12;stairs.sy=11;stairs.tolev.dnum=0;stairs.tolev.dlevel=2;stairs.up=0;for(x=0;x<3;x++){monsters[x].data=&mons[PM_HUMAN];monsters[x].mextra=&extras[x];extras[x].eshk=&shops[x];monsters[x].mx=11+x;monsters[x].my=10;monsters[x].mhp=40;monsters[x].mcanmove=monsters[x].mcansee=1;svl.level.monsters[11+x][10]=&monsters[x];}for(x=0;x<6;x++){items[x].otyp=ROCK;items[x].oclass=GEM_CLASS;items[x].quan=1;items[x].where=OBJ_FLOOR;items[x].ox=items[x].oy=10;items[x].oextra=&oextras[x];}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)svl.level.locations[x][y].typ=ROOM;for(y=0;y<ROWNO;y++){visrows[y]=visibility[y];for(x=0;x<COLNO;x++)visibility[y][x]=IN_SIGHT|COULD_SEE;}gv.viz_array=visrows;gk.kickedobj=&items[0];svl.level.objects[10][10]=&items[0];gm.maploc=&svl.level.locations[11][10];uarm=uarmf=uball=uchain=NULL;gi.invent=&items[1];windowprocs.win_display_nhwindow=fixture_display;trace[0]=result[0]=0;}
void probe_monset(int i,int pm,int field,long v){struct monst *m=i==3?&gy.youmonst:&monsters[i];if(pm>=0)m->data=&mons[pm];switch(field){case 0:m->mtame=v;break;case 1:m->mpeaceful=v;break;case 2:m->msleeping=v;break;case 3:m->mcanmove=v;break;case 4:m->mcansee=v;break;case 5:m->mundetected=v;break;case 6:m->mtrapped=v;break;case 7:m->mconf=v;break;case 8:m->mstun=v;break;case 9:m->isshk=v;break;case 10:m->ispriest=v;break;case 11:m->isgd=v;break;case 12:m->mhp=v;break;case 13:shops[i].robbed=v;break;case 14:shops[i].debit=v;break;case 15:shops[i].credit=v;break;case 16:m->m_ap_type=v;break;}}
void probe_item(int i,int typ,long quan,int field,long v){struct obj *o=&items[i];o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=quan;switch(field){case 0:o->unpaid=v;break;case 1:o->no_charge=v;break;case 2:o->cknown=v;break;case 3:o->greased=v;break;case 4:o->lknown=v;break;case 5:o->olocked=v;break;case 6:o->otrapped=v;break;case 7:o->spe=v;break;case 8:o->corpsenm=v;break;case 9:o->where=v;break;case 10:o->owt=v;break;case 11:o->owornmask=v;break;case 12:o->migr_species=v;break;case 13:o->ox=v;break;case 14:o->oy=v;break;case 15:o->oartifact=v;break;}}
void probe_link(int kind,int a,int b){struct obj *v=b<0?NULL:&items[b];if(kind==0)items[a].nobj=v;else if(kind==1)items[a].nexthere=v;else if(kind==2)items[a].cobj=v;else if(kind==3)gm.migrating_objs=v;else if(kind==4)svl.level.objects[10][10]=v;}
void probe_equipment(int slot,int i){struct obj *o=i<0?NULL:&items[i];if(slot==0)uarm=o;else if(slot==1)uarmf=o;else if(slot==2)uball=o;else uchain=o;}
void probe_oname(int i,char *s){oextras[i].oname=s;items[i].oextra=&oextras[i];}
void probe_property(int i,long a,long b,long c){u.uprops[i].intrinsic=a;u.uprops[i].extrinsic=b;u.uprops[i].blocked=c;}
void probe_terrain(int x,int y,int typ,int field,int value){struct rm *p=&svl.level.locations[x][y];p->typ=typ;switch(field){case 0:p->doormask=value;break;case 1:p->looted=value;break;case 2:p->disturbed=value;break;case 3:p->emptygrave=value;break;case 4:p->ladder=value;break;}}
void probe_global(int f,long v){switch(f){case 0:gu.urole.mnum=v;break;case 1:u.umonnum=v;break;case 2:u.uinwater=v;break;case 3:u.uswallow=v;u.ustuck=v?&monsters[0]:NULL;break;case 4:u.utrap=v;break;case 5:u.utraptype=v;break;case 6:u.uluck=v;break;case 7:svc.context.forcefight=v;break;case 8:gk.kickedobj=v<0?NULL:&items[v];break;case 9:stairs.isladder=v;break;case 10:stairs.up=v;break;case 11:trap.ttyp=v;break;case 12:trap.tseen=v;break;case 13:u.uroleplay.deaf=v;break;case 14:u.ulevel=v;break;case 15:u.ualign.record=v;break;case 16:gn.notonhead=v;break;case 17:gm.multi=v;break;case 18:flags.verbose=v;break;}}
uintptr_t probe_invoke(int op,uintptr_t a0,uintptr_t a1,uintptr_t a2,uintptr_t a3){switch(op){
case 0:{kickdmg((struct monst *)a0,(boolean)a1);strcpy(result,"void");return 0;}
case 1:{boolean r=maybe_kick_monster((struct monst *)a0,(coordxy)a1,(coordxy)a2);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 2:{kick_monster((struct monst *)a0,(coordxy)a1,(coordxy)a2);strcpy(result,"void");return 0;}
case 3:{boolean r=ghitm((struct monst *)a0,(struct obj *)a1);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 4:{container_impact_dmg((struct obj *)a0,(coordxy)a1,(coordxy)a2);strcpy(result,"void");return 0;}
case 5:{int r=kick_object((coordxy)a0,(coordxy)a1,(char *)a2);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 6:{int r=really_kick_object((coordxy)a0,(coordxy)a1);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 7:{char * r=kickstr((char *)a0,(const char *)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 8:{boolean r=watchman_thief_arrest((struct monst *)a0);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 9:{boolean r=watchman_door_damage((struct monst *)a0,(coordxy)a1,(coordxy)a2);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 10:{kick_dumb((coordxy)a0,(coordxy)a1);strcpy(result,"void");return 0;}
case 11:{kick_ouch((coordxy)a0,(coordxy)a1,(const char *)a2);strcpy(result,"void");return 0;}
case 12:{kick_door((coordxy)a0,(coordxy)a1,(int)a2);strcpy(result,"void");return 0;}
case 13:{int r=kick_nondoor((coordxy)a0,(coordxy)a1,(int)a2);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 14:{int r=dokick();snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 15:{drop_to((coord *)a0,(schar)a1,(coordxy)a2,(coordxy)a3);strcpy(result,"void");return 0;}
case 16:{impact_drop((struct obj *)a0,(coordxy)a1,(coordxy)a2,(xint16)a3);strcpy(result,"void");return 0;}
case 17:{boolean r=ship_object((struct obj *)a0,(coordxy)a1,(coordxy)a2,(boolean)a3);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 18:{obj_delivery((boolean)a0);strcpy(result,"void");return 0;}
case 19:{deliver_obj_to_mon((struct monst *)a0,(int)a1,(unsigned long)a2);strcpy(result,"void");return 0;}
case 20:{otransit_msg((struct obj *)a0,(boolean)a1,(boolean)a2,(long)a3);strcpy(result,"void");return 0;}
case 21:{schar r=down_gate((coordxy)a0,(coordxy)a1);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
default:abort();}}
const char *probe_snapshot(void){char *p=snap;int i;p+=sprintf(p,"kick:%ld;gate:%s;move:%d;ff:%d;hp:%d;luck:%d;multi:%ld;",oid(gk.kickedobj),gg.gate_str?gg.gate_str:"[NULL]",svc.context.move,svc.context.forcefight,u.uhp,u.uluck,gm.multi);for(i=0;i<3;i++)p+=sprintf(p,"m%d:%d,%d,%d,%d,%d,%d,%ld,%ld,%ld;",i,monsters[i].mhp,monsters[i].mtame,monsters[i].mpeaceful,monsters[i].mflee,monsters[i].mx,monsters[i].my,shops[i].robbed,shops[i].debit,shops[i].credit);for(i=0;i<6;i++)p+=sprintf(p,"o%d:%d,%ld,%ld,%d,%d,%d,%u,%u,%u,%u,%u,%ld,%ld;",i,items[i].otyp,items[i].quan,items[i].owornmask,items[i].where,items[i].ox,items[i].oy,items[i].no_charge,items[i].cknown,items[i].lknown,items[i].olocked,items[i].otrapped,oid(items[i].nobj),oid(items[i].nexthere));p+=sprintf(p,"floor:%ld;migr:%ld;room:%d,%u,%u,%u;trap:%u,%u;",oid(svl.level.objects[10][10]),oid(gm.migrating_objs),gm.maploc->typ,gm.maploc->doormask,gm.maploc->looted,gm.maploc->disturbed,trap.ttyp,trap.tseen);return snap;}
unsigned probe_table_count(void){return 0;}
