/* Controlled DOGMOVE world/dependency fixture. No pet algorithm fallback.
 * Original C and imported JS receive identical native records and RNG stream. */
#include "hack.h"
#include "mfndpos.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-dogmove-layout.h"
__typeof__(cg) cg;
__typeof__(objects) objects;
__typeof__(svl) svl;
__typeof__(mons) mons;
__typeof__(svm) svm;
__typeof__(iflags) iflags;
__typeof__(u) u;
__typeof__(gv) gv;
__typeof__(flags) flags;
__typeof__(svc) svc;
__typeof__(gg) gg;
__typeof__(gi) gi;
__typeof__(gf) gf;
__typeof__(gy) gy;
__typeof__(svd) svd;
__typeof__(gb) gb;
__typeof__(gn) gn;
__typeof__(windowprocs) windowprocs;
__typeof__(WIN_MAP) WIN_MAP;
const struct Gender genders[4]={{.his="his"},{.his="her"},{.his="its"}};
const struct c_common_strings c_common_strings={.c_something="something"};
const struct symdef defsyms[MAXPCHARS+1]={[S_sink]={.explanation="sink"}};
struct objdescr obj_descr[NUM_OBJECTS+1]={[TRIPE_RATION]={.oc_name="tripe ration",.oc_descr="ration"}};
static struct obj objpool[16];static struct monst mpool[8];static struct mextra mextras[8];static struct edog dogs[8];static struct emin minions[8];static struct epri priests[8];static struct trap traps[4];static coord tracks[4];
static char names[16][128],tracebuf[262144],statebuf[1048576],input[2048] __attribute__((aligned(4)));static int opts[40],seed,tracepos,reentered,dogmove_attack_count;static void*growth;
static seenV vis[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char*fmt,...){if(tracepos>sizeof tracebuf-4096)abort();va_list ap;va_start(ap,fmt);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);}
static int oid(struct obj*p){if(!p)return -1;for(int i=0;i<16;i++)if(p==&objpool[i])return i;return 99;}
static int mid(struct monst*p){if(!p)return -1;if(p==&gy.youmonst)return 98;for(int i=0;i<8;i++)if(p==&mpool[i])return i;return 99;}
static void grow(void){if(opts[30]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}}
boolean rng_log_enabled(void){return opts[29];}
void rng_log_set_caller(const char*file,int line,const char*fn){const char*p=strrchr(file,'/');append("site:%s:%d:%s;",p?p+1:file,line,fn);grow();if(opts[31]){dogs[0].apport=opts[31];append("apport:%d;",dogs[0].apport);}}
int (rn2)(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;int value=(unsigned)seed%n;append("rn2:%d:%d;",n,value);return value;}
int (rnd)(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;int value=1+(unsigned)seed%n;append("rnd:%d:%d;",n,value);return value;}
static void message(const char*kind,const char*fmt,va_list ap){char buf[1024];vsnprintf(buf,sizeof buf,fmt,ap);append("%s:%s;",kind,buf);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);message("pline",fmt,ap);va_end(ap);}
void pline_mon(struct monst*m,const char*fmt,...){append("mon:%d;",mid(m));va_list ap;va_start(ap,fmt);message("pline_mon",fmt,ap);va_end(ap);}
void pline_xy(coordxy x,coordxy y,const char*fmt,...){append("xy:%d:%d;",x,y);va_list ap;va_start(ap,fmt);message("pline_xy",fmt,ap);va_end(ap);}
void Your(const char*fmt,...){va_list ap;va_start(ap,fmt);message("Your",fmt,ap);va_end(ap);}
void You(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You",fmt,ap);va_end(ap);}
void You_feel(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You_feel",fmt,ap);va_end(ap);}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);message("impossible",fmt,ap);va_end(ap);}
static void displaywin(winid w,boolean b){append("display:%d:%d;",w,b);}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
int dist2(coordxy x,coordxy y,coordxy a,coordxy b){return (x-a)*(x-a)+(y-b)*(y-b);}
int distmin(coordxy x,coordxy y,coordxy a,coordxy b){int dx=abs(x-a),dy=abs(y-b);return dx>dy?dx:dy;}
int sgn(int x){return x<0?-1:x>0?1:0;}
boolean clear_path(int x,int y,int a,int b){append("path:%d:%d:%d:%d;",x,y,a,b);return opts[0];}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean is_pool(coordxy x,coordxy y){return opts[1];}boolean is_lava(coordxy x,coordxy y){return opts[2];}
struct obj*sobj_at(int typ,coordxy x,coordxy y){return opts[3]?&objpool[15]:0;}
boolean may_dig(coordxy x,coordxy y){return opts[4];}
int canseemon(struct monst*m){append("seen:%d;",mid(m));return opts[5];}
int mon_visible(struct monst*m){append("visible:%d;",mid(m));return opts[6];}
int sensemon(struct monst*m){append("sense:%d;",mid(m));return opts[7];}
int dogfood(struct monst*m,struct obj*o){append("food:%d:%d;",mid(m),oid(o));return opts[8];}
int can_carry(struct monst*m,struct obj*o){return opts[9];}
int eaten_stat(int n,struct obj*o){append("eaten:%d:%d;",n,oid(o));return opts[10]?n/opts[10]:n;}
int bee_eat_jelly(struct monst*m,struct obj*o){append("bee:%d:%d;",mid(m),oid(o));return opts[11];}
struct obj*splitobj(struct obj*o,long n){append("split:%d:%ld;",oid(o),n);objpool[14]=*o;objpool[14].quan=n;o->quan-=n;return &objpool[14];}
char*doname(struct obj*o){return names[oid(o)<16?oid(o):0];}
char*distant_name(struct obj*o,char*(*cb)(struct obj*)){append("distant:%d;",oid(o));grow();return cb(o);}
char*xname(struct obj*o){return doname(o);}char*Monnam(struct monst*m){return names[8+mid(m)%8];}char*noit_Monnam(struct monst*m){return Monnam(m);}char*y_monnam(struct monst*m){return Monnam(m);}
void m_consume_obj(struct monst*m,struct obj*o){append("consume:%d:%d;",mid(m),oid(o));o->quan=0;if(opts[12])m->mhp=0;}
void mondied(struct monst*m){append("died:%d;",mid(m));m->mhp=0;}
void relobj(struct monst*m,int show,boolean pet){append("relobj:%d:%d:%d;",mid(m),show,pet);m->minvent=0;}
long unpaid_cost(struct obj*o,uchar mask){append("cost:%d:%u;",oid(o),mask);return 9007199254740997L;}
const char*currency(long cost){append("currency:%ld;",cost);return "zorkmids";}
coord*gettrack(coordxy x,coordxy y){return opts[13]?&tracks[0]:0;}
void do_clear_area(coordxy x,coordxy y,int r,void(*cb)(coordxy,coordxy,void*),genericptr_t p){append("area:%d:%d:%d:%d;",x,y,r,*(int*)p);grow();if(opts[32]&&!reentered){reentered=1;finish_meating(&mpool[1]);append("reentered;");}cb(x+1,y,p);cb(x,y+1,p);append("area_result:%d;",*(int*)p);}
boolean Resists_Elem(struct monst*m,int r){return opts[14];}
int mattackm(struct monst*a,struct monst*b){dogmove_attack_count++;int result=dogmove_attack_count>1&&opts[33]?opts[33]:opts[15];append("attack:%d:%d:%d;",mid(a),mid(b),result);return result;}
int mattacku(struct monst*a){append("attacku:%d;",mid(a));return opts[16];}
long mon_allowflags(struct monst*m){return ALLOW_M|ALLOW_MDISP|ALLOW_TRAPS|ALLOW_U;}
int mfndpos(struct monst*m,struct mfndposdata*p,long allow){append("mfndpos:%d:%ld;",mid(m),allow);grow();p->cnt=opts[17];for(int i=0;i<p->cnt;i++){p->poss[i].x=m->mx+1+i%2;p->poss[i].y=m->my+i/2;p->info[i]=opts[18];}return p->cnt;}
boolean should_displace(struct monst*m,const struct mfndposdata*p,coordxy x,coordxy y){append("should_displace:%d:%d:%d:%d;",mid(m),p->cnt,x,y);return opts[19];}
void place_monster(struct monst*m,coordxy x,coordxy y){append("place:%d:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;svl.level.monsters[x][y]=m;}
void mon_track_add(struct monst*m,coordxy x,coordxy y){append("track:%d:%d:%d;",mid(m),x,y);for(int i=MTSZ-1;i>0;i--)m->mtrack[i]=m->mtrack[i-1];m->mtrack[0].x=x;m->mtrack[0].y=y;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);if(opts[20])levl[x][y].glyph++;}
int glyph_at(coordxy x,coordxy y){return levl[x][y].glyph;}
boolean goodpos(coordxy x,coordxy y,struct monst*m,mmflags_nht flags){append("goodpos:%d:%d:%d;",x,y,mid(m));return opts[21];}
void dirtocoord(coord*p,int d){static const int dx[]={0,1,1,1,0,-1,-1,-1},dy[]={-1,-1,0,1,1,1,0,-1};p->x=dx[d%8];p->y=dy[d%8];}
int xytodir(int x,int y){return 0;}
boolean m_in_out_region(struct monst*m,coordxy x,coordxy y){append("region:%d:%d:%d;",mid(m),x,y);return opts[22];}
boolean m_digweapon_check(struct monst*m,coordxy x,coordxy y){return opts[23];}
struct trap*t_at(coordxy x,coordxy y){return opts[24]?&traps[0]:0;}
int mdisplacem(struct monst*a,struct monst*b,boolean q){append("displace:%d:%d:%d;",mid(a),mid(b),q);return opts[34];}
int Mgender(struct monst*m){return 0;}int pronoun_gender(struct monst*m,unsigned f){return opts[25];}
char*vtense(const char*s,const char*verb){return (char*)verb;}const char*locomotion(const struct permonst*p,const char*verb){return verb;}
const char*pmname(struct permonst*p,int g){return "mimic";}char*an(const char*s){return (char*)s;}
signed char (On_stairs)(coordxy a0,coordxy a1){append("dependency:On_stairs;");return 0;}
signed char (attacktype)(struct permonst * a0,int a1){append("dependency:attacktype;");return 0;}
void (beg)(struct monst * a0){append("dependency:beg;");}
void (check_gear_next_turn)(struct monst * a0){append("dependency:check_gear_next_turn;");}
void (costly_alteration)(struct obj * a0,int a1){append("dependency:costly_alteration;");}
void (dismount_steed)(int a0){append("dependency:dismount_steed;");}
int (domonnoise)(struct monst * a0){append("dependency:domonnoise;");return 0;}
void (lose_guardian_angel)(struct monst * a0){append("dependency:lose_guardian_angel;");}
signed char (m_avoid_kicked_loc)(struct monst * a0,coordxy a1,coordxy a2){append("dependency:m_avoid_kicked_loc;");return 0;}
signed char (m_avoid_soko_push_loc)(struct monst * a0,coordxy a1,coordxy a2){append("dependency:m_avoid_soko_push_loc;");return 0;}
void (m_unleash)(struct monst * a0,boolean a1){append("dependency:m_unleash;");}
int (max_passive_dmg)(struct monst * a0,struct monst * a1){append("dependency:max_passive_dmg;");return opts[27];}
signed char (mon_reflects)(struct monst * a0,const char * a1){append("dependency:mon_reflects;");return 0;}
int (mon_wield_item)(struct monst * a0){append("dependency:mon_wield_item;");return 0;}
signed char (monnear)(struct monst * a0,coordxy a1,coordxy a2){append("dependency:monnear;");return 0;}
int (mpickobj)(struct monst * a0,struct obj * a1){append("dependency:mpickobj;");return 0;}
void (obj_extract_self)(struct obj * a0){append("dependency:obj_extract_self;");}
signed char (onscary)(coordxy a0,coordxy a1,struct monst * a2){append("dependency:onscary;");return 0;}
signed char (resist_conflict)(struct monst * a0){append("dependency:resist_conflict;");return opts[26];}
void (set_apparxy)(struct monst * a0){append("dependency:set_apparxy;");}
void (stop_occupation)(void){append("dependency:stop_occupation;");}
signed char (undesirable_disp)(struct monst * a0,coordxy a1,coordxy a2){append("dependency:undesirable_disp;");return 0;}
struct obj * (which_armor)(struct monst * a0,long a1){append("dependency:which_armor;");return 0;}
void (whimper)(struct monst * a0){append("dependency:whimper;");}
#ifdef HYBRID_DOGMOVE
extern struct obj * droppables(struct monst * mon);
extern boolean cursed_object_at(coordxy x,coordxy y);
extern int dog_nutrition(struct monst * mtmp,struct obj * obj);
extern int dog_eat(struct monst * mtmp,struct obj * obj,coordxy x,coordxy y,boolean devour);
extern void teleport_dogmove_dog_starve(struct monst * mtmp);
#define dog_starve teleport_dogmove_dog_starve
extern boolean teleport_dogmove_dog_hunger(struct monst * mtmp,struct edog * edog);
#define dog_hunger teleport_dogmove_dog_hunger
extern int teleport_dogmove_dog_invent(struct monst * mtmp,struct edog * edog,int udist);
#define dog_invent teleport_dogmove_dog_invent
extern int teleport_dogmove_dog_goal(struct monst * mtmp,struct edog * edog,int after,int udist,int whappr);
#define dog_goal teleport_dogmove_dog_goal
extern struct monst * teleport_dogmove_find_targ(struct monst * mtmp,int dx,int dy,int maxdist);
#define find_targ teleport_dogmove_find_targ
extern int teleport_dogmove_find_friends(struct monst * mtmp,struct monst * mtarg,int maxdist);
#define find_friends teleport_dogmove_find_friends
extern long teleport_dogmove_score_targ(struct monst * mtmp,struct monst * mtarg);
#define score_targ teleport_dogmove_score_targ
extern struct monst * teleport_dogmove_best_target(struct monst * mtmp,boolean forced);
#define best_target teleport_dogmove_best_target
extern int pet_ranged_attk(struct monst * mtmp,boolean forced);
extern int dog_move(struct monst * mtmp,int after);
extern boolean could_reach_item(struct monst * mon,coordxy nx,coordxy ny);
extern boolean teleport_dogmove_can_reach_location(struct monst * mon,coordxy mx,coordxy my,coordxy fx,coordxy fy);
#define can_reach_location teleport_dogmove_can_reach_location
extern void teleport_dogmove_wantdoor(coordxy x,coordxy y,genericptr_t distance);
#define wantdoor teleport_dogmove_wantdoor
extern void finish_meating(struct monst * mtmp);
extern boolean teleport_dogmove_mnum_leashable(int mnum);
#define mnum_leashable teleport_dogmove_mnum_leashable
extern void quickmimic(struct monst * mtmp);
#else
#include "../.cache/wasm64-build/tree/src/dogmove.c"
void teleport_dogmove_wantdoor_callback(coordxy x,coordxy y,genericptr_t p){wantdoor(x,y,p);}
#endif
static uint64_t canonical(uint64_t value){
#define REGION(v,id) if(value>=(uintptr_t)&(v)&&value<(uintptr_t)&(v)+sizeof(v))return ((uint64_t)(id)<<48)+(value-(uintptr_t)&(v))
REGION(mons,1);REGION(objpool,2);REGION(mpool,3);REGION(mextras,4);REGION(dogs,5);REGION(priests,6);REGION(minions,7);REGION(names,8);REGION(u,9);REGION(gy.youmonst,10);REGION(tracks,11);REGION(traps,12);
#undef REGION
return value;}
static void typed_pointer(unsigned char*out,const void*base,const void*field){uint64_t value;memcpy(&value,field,8);value=canonical(value);memcpy(out+((const unsigned char*)field-(const unsigned char*)base),&value,8);}
static void normalize_d_level(unsigned char*,const void*,const struct d_level*);
static void normalize_nhcoord(unsigned char*,const void*,const struct nhcoord*);
static void normalize_vptrs(unsigned char*,const void*,const union vptrs*);
static void normalize_flag(unsigned char*,const void*,const struct flag*);
static void normalize_trap(unsigned char*,const void*,const struct trap*);
static void normalize_window_procs(unsigned char*,const void*,const struct window_procs*);
static void normalize_symdef(unsigned char*,const void*,const struct symdef*);
static void normalize_obj(unsigned char*,const void*,const struct obj*);
static void normalize_objclass(unsigned char*,const void*,const struct objclass*);
static void normalize_mfndposdata(unsigned char*,const void*,const struct mfndposdata*);
static void normalize_attack(unsigned char*,const void*,const struct attack*);
static void normalize_permonst(unsigned char*,const void*,const struct permonst*);
static void normalize_prop(unsigned char*,const void*,const struct prop*);
static void normalize_monst(unsigned char*,const void*,const struct monst*);
static void normalize_epri(unsigned char*,const void*,const struct epri*);
static void normalize_achievement_tracking(unsigned char*,const void*,const struct achievement_tracking*);
static void normalize_objdescr(unsigned char*,const void*,const struct objdescr*);
static void normalize_context_info(unsigned char*,const void*,const struct context_info*);
static void normalize_rm(unsigned char*,const void*,const struct rm*);
static void normalize_instance_globals_b(unsigned char*,const void*,const struct instance_globals_b*);
static void normalize_emin(unsigned char*,const void*,const struct emin*);
static void normalize_edog(unsigned char*,const void*,const struct edog*);
static void normalize_c_common_strings(unsigned char*,const void*,const struct c_common_strings*);
static void normalize_u_roleplay(unsigned char*,const void*,const struct u_roleplay*);
static void normalize_mextra(unsigned char*,const void*,const struct mextra*);
static void normalize_dgn_topology(unsigned char*,const void*,const struct dgn_topology*);
static void normalize_instance_flags(unsigned char*,const void*,const struct instance_flags*);
static void normalize_instance_globals_f(unsigned char*,const void*,const struct instance_globals_f*);
static void normalize_instance_globals_g(unsigned char*,const void*,const struct instance_globals_g*);
static void normalize_Gender(unsigned char*,const void*,const struct Gender*);
static void normalize_instance_globals_i(unsigned char*,const void*,const struct instance_globals_i*);
static void normalize_you(unsigned char*,const void*,const struct you*);
static void normalize_levelflags(unsigned char*,const void*,const struct levelflags*);
static void normalize_dlevel_t(unsigned char*,const void*,const dlevel_t*);
static void normalize_instance_globals_n(unsigned char*,const void*,const struct instance_globals_n*);
static void normalize_instance_globals_v(unsigned char*,const void*,const struct instance_globals_v*);
static void normalize_instance_globals_y(unsigned char*,const void*,const struct instance_globals_y*);
static void normalize_instance_globals_saved_c(unsigned char*,const void*,const struct instance_globals_saved_c*);
static void normalize_instance_globals_saved_d(unsigned char*,const void*,const struct instance_globals_saved_d*);
static void normalize_instance_globals_saved_l(unsigned char*,const void*,const struct instance_globals_saved_l*);
static void normalize_instance_globals_saved_m(unsigned char*,const void*,const struct instance_globals_saved_m*);
static void normalize_const_globals(unsigned char*,const void*,const struct const_globals*);
static void normalize_d_level(unsigned char*out,const void*base,const struct d_level*p){}
static void normalize_nhcoord(unsigned char*out,const void*base,const struct nhcoord*p){}
static void normalize_vptrs(unsigned char*out,const void*base,const union vptrs*p){typed_pointer(out,base,&p->v_nexthere);}
static void normalize_flag(unsigned char*out,const void*base,const struct flag*p){}
static void normalize_trap(unsigned char*out,const void*base,const struct trap*p){typed_pointer(out,base,&p->ntrap);}
static void normalize_window_procs(unsigned char*out,const void*base,const struct window_procs*p){typed_pointer(out,base,&p->win_display_nhwindow);}
static void normalize_symdef(unsigned char*out,const void*base,const struct symdef*p){typed_pointer(out,base,&p->explanation);}
static void normalize_obj(unsigned char*out,const void*base,const struct obj*p){typed_pointer(out,base,&p->nobj);normalize_vptrs(out,base,&p->v);}
static void normalize_objclass(unsigned char*out,const void*base,const struct objclass*p){}
static void normalize_mfndposdata(unsigned char*out,const void*base,const struct mfndposdata*p){for(int i0=0;i0<9;i0++){normalize_nhcoord(out,base,&p->poss[i0]);}}
static void normalize_attack(unsigned char*out,const void*base,const struct attack*p){}
static void normalize_permonst(unsigned char*out,const void*base,const struct permonst*p){for(int i0=0;i0<6;i0++){normalize_attack(out,base,&p->mattk[i0]);}}
static void normalize_prop(unsigned char*out,const void*base,const struct prop*p){}
static void normalize_monst(unsigned char*out,const void*base,const struct monst*p){typed_pointer(out,base,&p->data);for(int i0=0;i0<4;i0++){normalize_nhcoord(out,base,&p->mtrack[i0]);}typed_pointer(out,base,&p->minvent);typed_pointer(out,base,&p->mw);typed_pointer(out,base,&p->mextra);}
static void normalize_epri(unsigned char*out,const void*base,const struct epri*p){}
static void normalize_achievement_tracking(unsigned char*out,const void*base,const struct achievement_tracking*p){}
static void normalize_objdescr(unsigned char*out,const void*base,const struct objdescr*p){typed_pointer(out,base,&p->oc_name);typed_pointer(out,base,&p->oc_descr);}
static void normalize_context_info(unsigned char*out,const void*base,const struct context_info*p){normalize_achievement_tracking(out,base,&p->achieveo);}
static void normalize_rm(unsigned char*out,const void*base,const struct rm*p){}
static void normalize_instance_globals_b(unsigned char*out,const void*base,const struct instance_globals_b*p){normalize_nhcoord(out,base,&p->bhitpos);}
static void normalize_emin(unsigned char*out,const void*base,const struct emin*p){}
static void normalize_edog(unsigned char*out,const void*base,const struct edog*p){normalize_nhcoord(out,base,&p->ogoal);}
static void normalize_c_common_strings(unsigned char*out,const void*base,const struct c_common_strings*p){typed_pointer(out,base,&p->c_something);}
static void normalize_u_roleplay(unsigned char*out,const void*base,const struct u_roleplay*p){}
static void normalize_mextra(unsigned char*out,const void*base,const struct mextra*p){typed_pointer(out,base,&p->epri);typed_pointer(out,base,&p->emin);typed_pointer(out,base,&p->edog);}
static void normalize_dgn_topology(unsigned char*out,const void*base,const struct dgn_topology*p){normalize_d_level(out,base,&p->d_rogue_level);normalize_d_level(out,base,&p->d_qstart_level);}
static void normalize_instance_flags(unsigned char*out,const void*base,const struct instance_flags*p){}
static void normalize_instance_globals_f(unsigned char*out,const void*base,const struct instance_globals_f*p){typed_pointer(out,base,&p->ftrap);}
static void normalize_instance_globals_g(unsigned char*out,const void*base,const struct instance_globals_g*p){}
static void normalize_Gender(unsigned char*out,const void*base,const struct Gender*p){typed_pointer(out,base,&p->his);}
static void normalize_instance_globals_i(unsigned char*out,const void*base,const struct instance_globals_i*p){typed_pointer(out,base,&p->invent);}
static void normalize_you(unsigned char*out,const void*base,const struct you*p){normalize_d_level(out,base,&p->uz);for(int i0=0;i0<69;i0++){normalize_prop(out,base,&p->uprops[i0]);}normalize_u_roleplay(out,base,&p->uroleplay);typed_pointer(out,base,&p->usteed);}
static void normalize_levelflags(unsigned char*out,const void*base,const struct levelflags*p){}
static void normalize_dlevel_t(unsigned char*out,const void*base,const dlevel_t*p){for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){normalize_rm(out,base,&p->locations[i0][i1]);}}for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){typed_pointer(out,base,&p->objects[i0][i1]);}}for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){typed_pointer(out,base,&p->monsters[i0][i1]);}}typed_pointer(out,base,&p->objlist);normalize_levelflags(out,base,&p->flags);}
static void normalize_instance_globals_n(unsigned char*out,const void*base,const struct instance_globals_n*p){}
static void normalize_instance_globals_v(unsigned char*out,const void*base,const struct instance_globals_v*p){typed_pointer(out,base,&p->viz_array);}
static void normalize_instance_globals_y(unsigned char*out,const void*base,const struct instance_globals_y*p){normalize_monst(out,base,&p->youmonst);}
static void normalize_instance_globals_saved_c(unsigned char*out,const void*base,const struct instance_globals_saved_c*p){normalize_context_info(out,base,&p->context);}
static void normalize_instance_globals_saved_d(unsigned char*out,const void*base,const struct instance_globals_saved_d*p){normalize_dgn_topology(out,base,&p->dungeon_topology);}
static void normalize_instance_globals_saved_l(unsigned char*out,const void*base,const struct instance_globals_saved_l*p){normalize_dlevel_t(out,base,&p->level);}
static void normalize_instance_globals_saved_m(unsigned char*out,const void*base,const struct instance_globals_saved_m*p){}
static void normalize_const_globals(unsigned char*out,const void*base,const struct const_globals*p){normalize_obj(out,base,&p->zeroobj);}
static void dump(char**out,const void*data,size_t n,void(*normalize)(unsigned char*,const void*,const void*)){unsigned char bytes[n];memcpy(bytes,data,n);if(normalize)normalize(bytes,data,data);static const char hex[]="0123456789abcdef";for(size_t i=0;i<n;i++){*(*out)++=hex[bytes[i]>>4];*(*out)++=hex[bytes[i]&15];}}
const char*probe_snapshot(void){char*out=statebuf;out+=sprintf(out,"goal:%d:%d:%d bhit:%d:%d nothead:%d suppress:%d;",gg.gtyp,gg.gx,gg.gy,gb.bhitpos.x,gb.bhitpos.y,gn.notonhead,iflags.suppress_price);
#define DUMP(v,type) dump(&out,&(v),sizeof(v),(void(*)(unsigned char*,const void*,const void*))normalize_##type)
for(int i=0;i<16;i++)DUMP(objpool[i],obj);for(int i=0;i<8;i++){DUMP(mpool[i],monst);DUMP(dogs[i],edog);DUMP(mextras[i],mextra);}DUMP(u,you);DUMP(gy.youmonst,monst);DUMP(svl.level,dlevel_t);
#undef DUMP
*out=0;return statebuf;}
void probe_reset(void){
memset((void*)&objects,0,sizeof objects);
memset((void*)&svl,0,sizeof svl);
memset((void*)&mons,0,sizeof mons);
memset((void*)&svm,0,sizeof svm);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&u,0,sizeof u);
memset((void*)&gv,0,sizeof gv);
memset((void*)&flags,0,sizeof flags);
memset((void*)&svc,0,sizeof svc);
memset((void*)&gg,0,sizeof gg);
memset((void*)&gi,0,sizeof gi);
memset((void*)&gf,0,sizeof gf);
memset((void*)&gy,0,sizeof gy);
memset((void*)&svd,0,sizeof svd);
memset((void*)&gb,0,sizeof gb);
memset((void*)&gn,0,sizeof gn);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&WIN_MAP,0,sizeof WIN_MAP);
memset(objpool,0,sizeof objpool);memset(mpool,0,sizeof mpool);memset(mextras,0,sizeof mextras);memset(dogs,0,sizeof dogs);memset(priests,0,sizeof priests);memset(minions,0,sizeof minions);memset(traps,0,sizeof traps);memset(tracks,0,sizeof tracks);memset(opts,0,sizeof opts);memset(input,0,sizeof input);memset(vis,0,sizeof vis);tracepos=0;tracebuf[0]=0;seed=1;growth=0;reentered=0;dogmove_attack_count=0;
for(int y=0;y<ROWNO;y++){visrows[y]=vis[y];for(int x=0;x<COLNO;x++)levl[x][y].typ=ROOM;}gv.viz_array=visrows;
u.ux=20;u.uy=10;u.uz.dnum=1;u.uz.dlevel=3;u.ulevel=10;svm.moves=9007199254740997L;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mx=u.ux;gy.youmonst.my=u.uy;
for(int i=0;i<NUMMONS+1;i++){memcpy((void*)&mons[i].pmidx,&i,sizeof i);mons[i].msize=MZ_MEDIUM;mons[i].mflags1=M1_CARNIVORE;mons[i].mattk[0].aatyp=AT_BREA;mons[i].cnutrit=100;mons[i].cwt=640;}
for(int i=0;i<NUM_OBJECTS+1;i++){objects[i].oc_nutrition=100;objects[i].oc_delay=4;}
for(int i=0;i<16;i++){objpool[i].o_id=100+i;objpool[i].quan=1;objpool[i].otyp=TRIPE_RATION;objpool[i].oclass=FOOD_CLASS;objpool[i].ox=10+i;objpool[i].oy=10;snprintf(names[i],sizeof names[i],"name%d",i);}
for(int i=0;i<8;i++){mpool[i].data=&mons[PM_LITTLE_DOG];mpool[i].m_id=200+i;mpool[i].mhp=mpool[i].mhpmax=30;mpool[i].mx=10+i;mpool[i].my=10;mpool[i].mux=20;mpool[i].muy=10;mpool[i].mtame=5;mpool[i].mcansee=1;mpool[i].mcanmove=1;mpool[i].mstate=MON_FLOOR;mpool[i].mextra=&mextras[i];mextras[i].edog=&dogs[i];dogs[i].parentmid=mpool[i].m_id;dogs[i].apport=5;dogs[i].hungrytime=svm.moves+1000;dogs[i].droptime=svm.moves-10;dogs[i].whistletime=svm.moves-100;}
windowprocs.win_display_nhwindow=displaywin;opts[0]=1;opts[4]=1;opts[8]=DOGFOOD;opts[9]=1;opts[11]=-1;opts[22]=1;opts[26]=1;}
void probe_option(int i,int value){opts[i]=value;if(i==28)seed=value;}
void probe_vision(int x,int y,int mask){vis[y][x]=mask;}
void*probe_pointer(int k,int i){switch(k){case 0:return &mpool[i];case 1:return &objpool[i];case 2:return &dogs[i];case 3:return &mextras[i];case 4:return &mons[i];case 5:return &objects[i];case 6:return &priests[i];case 7:return &minions[i];case 8:return &tracks[i];case 9:return &traps[i];case 10:return input;case 11:return &gy.youmonst;default:abort();}}
void probe_map(int what,int x,int y,int i){if(what==0)svl.level.monsters[x][y]=i<0?0:i==98?&gy.youmonst:&mpool[i];else svl.level.objects[x][y]=i<0?0:&objpool[i];}
int64_t probe_action(int op,int a,int b,int c,int d,int e){switch(op){case 0:return oid(droppables(&mpool[a]));case 1:return cursed_object_at(a,b);case 2:return dog_nutrition(&mpool[a],&objpool[b]);case 3:return dog_eat(&mpool[a],&objpool[b],c,d,e);case 4:dog_starve(&mpool[a]);break;case 5:return dog_hunger(&mpool[a],b?&dogs[a]:0);case 6:return dog_invent(&mpool[a],&dogs[a],b);case 7:return dog_goal(&mpool[a],b?&dogs[a]:0,c,d,e);case 8:return mid(find_targ(&mpool[a],b,c,d));case 9:return find_friends(&mpool[a],b==98?&gy.youmonst:&mpool[b],c);case 10:return score_targ(&mpool[a],b==98?&gy.youmonst:&mpool[b]);case 11:return mid(best_target(a<0?0:&mpool[a],b));case 12:return pet_ranged_attk(&mpool[a],b);case 13:return dog_move(&mpool[a],b);case 14:return could_reach_item(&mpool[a],b,c);case 15:return can_reach_location(&mpool[a],b,c,d,e);case 16:wantdoor(a,b,input);break;case 17:finish_meating(&mpool[a]);break;case 18:return mnum_leashable(a);case 19:quickmimic(&mpool[a]);break;default:abort();}return 0;}
int probe_clear_area(int x,int y,int initial){int distance=initial;do_clear_area(x,y,9,wantdoor,&distance);return distance;}
const char*probe_trace(void){return tracebuf;}
int probe_qm(int i,int field){
#ifdef HYBRID_DOGMOVE
return -1;
#else
switch(field){case 0:return qm[i].mndx;case 1:return qm[i].mlet;case 2:return qm[i].mappearance;case 3:return qm[i].m_ap_type;default:abort();}
#endif
}
const char*probe_nofetch(void){
#ifdef HYBRID_DOGMOVE
extern void*teleport_dogmove_global(int);return teleport_dogmove_global(24);
#else
return nofetch;
#endif
}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return sizeof dogmove_layout/sizeof dogmove_layout[0];}const char*probe_layout_name(int i){return dogmove_layout[i].name;}int64_t probe_layout_value(int i){return (int64_t)dogmove_layout[i].value;}
