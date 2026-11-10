/* Controlled world/dependency fixture. Original TELEPORT is reference-only. */
#include "hack.h"
#include "tu-teleport-layout.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <emscripten.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(u) u;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(svl) svl;
__typeof__(svd) svd;
__typeof__(svu) svu;
__typeof__(svm) svm;
__typeof__(gi) gi;
__typeof__(gy) gy;
__typeof__(gv) gv;
__typeof__(gc) gc;
__typeof__(go) go;
__typeof__(gu) gu;
__typeof__(svk) svk;
__typeof__(svn) svn;
__typeof__(cg) cg;
__typeof__(disp) disp;
__typeof__(gs) gs;
__typeof__(gt) gt;
__typeof__(gb) gb;
__typeof__(gw) gw;
__typeof__(gl) gl;
__typeof__(gm) gm;
__typeof__(a11y) a11y;
struct permonst mons[NUMMONS+1];struct objclass objects[NUM_OBJECTS+1];
volatile struct window_procs windowprocs;winid WIN_MESSAGE;struct obj *uball,*uchain,*uarmf;
const struct c_common_strings c_common_strings={.c_shudder_for_moment="shudder for a moment."};
const char ynchars[]="yn",ynqchars[]="ynq";
const struct Gender genders[3]={{.his="his"},{.his="her"},{.his="its"}};
const glyph_info nul_glyphinfo={0};
static seenV vision[ROWNO][COLNO];static seenV*visionrows[ROWNO];static struct mkroom room;static struct monst mon[4];static struct obj obj[4];static struct trap traps[4];static stairway stairs[4];static coord resultcc,candy[ROWNO*(COLNO-1)],nested[ROWNO*(COLNO-1)];
static char tracebuf[4194304],snap[4194304],textbuf[BUFSZ];static long opts[2048];static int pos,draws,filtercalls,nestedguard,reenter,menu_mode,input_count,debug_count;static unsigned rngstate;
static const char*current_file,*current_fn;static int current_line;static long callback_sp;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);if(pos>=sizeof tracebuf-1024)abort();}
static int mid(struct monst*p){if(!p)return 0;if(p==&gy.youmonst)return 9;for(int i=0;i<4;i++)if(p==&mon[i])return i+1;return -1;}
static int oid(struct obj*p){if(!p)return 0;for(int i=0;i<4;i++)if(p==&obj[i])return i+1;return -1;}
static void observe_mon(const char*n,struct monst*p){logmsg("%s:m%d/%d/%d/%ld/%lu/%d;",n,mid(p),p?p->mx:0,p?p->my:0,p?p->mstate:0L,p?p->mstrategy:0UL,p?(int)(p->data-mons):-1);}
EM_JS(void,fixture_throw,(void),{throw new Error('TELEPORT controlled callback');});
static void callback(void){if(opts[30]){long sp=emscripten_stack_get_current();if(!callback_sp)callback_sp=sp;logmsg("stack:%ld;",sp-callback_sp);}if(opts[31]){opts[31]=0;emscripten_resize_heap(emscripten_get_heap_size()+16777216);}if(opts[32]){opts[32]=0;fixture_throw();}}
boolean rng_log_enabled(void){return TRUE;}
void rng_log_set_caller(const char*f,int line,const char*fun){current_file=f;current_line=line;current_fn=fun;}
static int draw(int n,int plus){if(n<=0)abort();rngstate=rngstate*1664525U+1013904223U;int v=(rngstate>>1)%(unsigned)n;logmsg("rng:%s:%d:%s:%d:%d;",current_file,current_line,current_fn,n,v+plus);draws++;return v+plus;}
int(rn2)(int n){return draw(n,0);}int(rnd)(int n){return draw(n,1);}int(rnl)(int n){return draw(n,0);}
void pline(const char*f,...){va_list ap;logmsg("pline:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");iflags.last_msg=123;callback();}
void impossible(const char*f,...){va_list ap;logmsg("impossible:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void pline_mon(struct monst*m,const char*f,...){va_list ap;observe_mon("pline_mon",m);va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void You(const char*f,...){va_list ap;logmsg("You:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void You_cant(const char*f,...){va_list ap;logmsg("You_cant:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void You_feel(const char*f,...){va_list ap;logmsg("You_feel:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void Your(const char*f,...){va_list ap;logmsg("Your:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void verbalize(const char*f,...){va_list ap;logmsg("verbalize:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
char * Amonnam(struct monst * a0){logmsg("Amonnam:;");callback();return "monster";}
boolean In_W_tower(coordxy a0,coordxy a1,d_level * a2){logmsg("In_W_tower:%ld:%ld;",(long)a0,(long)a1);callback();return opts[1001] ? opts[1001] : 0;}
boolean In_hell(d_level * a0){logmsg("In_hell:;");callback();return opts[1002] ? opts[1002] : 0;}
boolean In_mines(d_level * a0){logmsg("In_mines:;");callback();return opts[1003] ? opts[1003] : 0;}
boolean In_quest(d_level * a0){logmsg("In_quest:;");callback();return opts[1004] ? opts[1004] : 0;}
boolean Is_botlevel(d_level * a0){logmsg("Is_botlevel:;");callback();return opts[1005] ? opts[1005] : 0;}
char * Monnam(struct monst * a0){logmsg("Monnam:;");callback();return "monster";}
boolean On_W_tower_level(d_level * a0){logmsg("On_W_tower_level:;");callback();return opts[1007] ? opts[1007] : 0;}
boolean accessible(coordxy x,coordxy y){return isok(x,y)&&ACCESSIBLE(levl[x][y].typ);}
schar acurr(int a0){logmsg("acurr:%ld;",(long)a0);callback();return opts[1009] ? opts[1009] : 0;}
struct obj * addinv(struct obj * a0){logmsg("addinv:;");callback();return a0;}
void addtobill(struct obj * a0,boolean a1,boolean a2,boolean a3){logmsg("addtobill:%ld:%ld:%ld;",(long)a1,(long)a2,(long)a3);callback();}
void assign_level(d_level * dest,d_level * src){*dest=*src;}
void buried_ball_to_punishment(void){logmsg("buried_ball_to_punishment:;");callback();}
int canseemon(struct monst * a0){logmsg("canseemon:;");callback();return opts[1014] ? opts[1014] : 1;}
boolean check_capacity(const char * a0){logmsg("check_capacity:;");callback();return opts[1015] ? opts[1015] : 0;}
void check_special_room(boolean a0){logmsg("check_special_room:%ld;",(long)a0);callback();}
d_level * clamp_hole_destination(d_level * a0){logmsg("clamp_hole_destination:;");callback();return 0;}
boolean closed_door(coordxy x,coordxy y){return isok(x,y)&&IS_DOOR(levl[x][y].typ)&&(levl[x][y].doormask&D_CLOSED);}
boolean costly_adjacent(struct monst * a0,coordxy a1,coordxy a2){logmsg("costly_adjacent:%ld:%ld;",(long)a1,(long)a2);callback();return opts[1019] ? opts[1019] : 0;}
boolean costly_spot(coordxy a0,coordxy a1){logmsg("costly_spot:%ld:%ld;",(long)a0,(long)a1);callback();return opts[1020] ? opts[1020] : 0;}
boolean debugcore(const char * file,boolean wild){logmsg("debug:%s:%d;",file,wild);if(opts[73])mons[0].pmnames[NEUTRAL]=(++debug_count&1)?"debug-A":"debug-B";if(opts[74])iflags.last_msg=74;callback();return opts[50];}
void deltrap(struct trap * a0){logmsg("deltrap:;");callback();}
schar depth(d_level * lev){return lev->dlevel+svd.dungeons[lev->dnum].depth_start-1;}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){logmsg("discover_object:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2,(long)a3);callback();}
int dist2(coordxy x0,coordxy y0,coordxy x1,coordxy y1){return (x0-x1)*(x0-x1)+(y0-y1)*(y0-y1);}
int distmin(coordxy x0,coordxy y0,coordxy x1,coordxy y1){int dx=abs(x0-x1),dy=abs(y0-y1);return dx>dy?dx:dy;}
int dochugw(struct monst * a0,boolean a1){logmsg("dochugw:%ld;",(long)a1);callback();return opts[1027] ? opts[1027] : 0;}
void docrt(void){logmsg("docrt:;");callback();}
void done(int a0){logmsg("done:%ld;",(long)a0);callback();}
boolean drag_ball(coordxy x,coordxy y,int * control,coordxy * bx,coordxy * by,coordxy * cx,coordxy * cy,boolean * delay,boolean allow){logmsg("drag_ball:%d/%d:%d;",x,y,allow);*control=3;*bx=12;*by=13;*cx=14;*cy=15;*delay=1;return opts[65];}
xint16 dunlevs_in_dungeon(d_level * lev){return svd.dungeons[lev->dnum].num_dunlevs;}
void exercise(int a0,boolean a1){logmsg("exercise:%ld:%ld;",(long)a0,(long)a1);callback();}
void fill_pit(coordxy a0,coordxy a1){logmsg("fill_pit:%ld:%ld;",(long)a0,(long)a1);callback();}
void find_hell(d_level * lev){lev->dnum=9;lev->dlevel=1;}
struct monst * find_objowner(struct obj * obj,coordxy x,coordxy y){return opts[71]?&mon[1]:0;}
struct monst * findgd(void){return opts[69]?&mon[0]:0;}
boolean flooreffects(struct obj * a0,coordxy a1,coordxy a2,const char * a3){logmsg("flooreffects:%ld:%ld;",(long)a1,(long)a2);callback();return opts[1037] ? opts[1037] : 0;}
struct monst * get_iter_mons(boolean (*func)(struct monst *)){for(int i=0;i<4;i++)if(mon[i].data&&func(&mon[i]))return &mon[i];return 0;}
void get_level(d_level * lev,int n){logmsg("get_level:%d;",n);lev->dnum=0;lev->dlevel=n;}
struct obj * get_mleash(struct monst * mon){return opts[60]?&obj[0]:0;}
void getlin(const char * query,char * buf){logmsg("getlin:%s;",query);strcpy(buf,textbuf);input_count++;callback();}
int getpos(coord * cc,boolean force,const char * goal){logmsg("getpos:%d/%d;",cc->x,cc->y);cc->x=opts[40];cc->y=opts[41];callback();return opts[42];}
boolean hideunder(struct monst * a0){logmsg("hideunder:;");callback();return opts[1043] ? opts[1043] : 0;}
boolean in_out_region(coordxy a0,coordxy a1){logmsg("in_out_region:%ld:%ld;",(long)a0,(long)a1);callback();return opts[1044] ? opts[1044] : 1;}
char * in_rooms(coordxy x,coordxy y,int type){return opts[62]?"":"A";}
int inhishop(struct monst * a0){logmsg("inhishop:;");callback();return opts[1046] ? opts[1046] : 0;}
boolean inhistemple(struct monst * a0){logmsg("inhistemple:;");callback();return opts[1047] ? opts[1047] : 0;}
void invocation_message(void){logmsg("invocation_message:;");callback();}
boolean is_exclusion_zone(xint16 a0,coordxy a1,coordxy a2){logmsg("is_exclusion_zone:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback();return opts[1049] ? opts[1049] : 0;}
boolean is_home_elemental(struct permonst * a0){logmsg("is_home_elemental:;");callback();return opts[1050] ? opts[1050] : 0;}
boolean is_lava(coordxy x,coordxy y){return isok(x,y)&&IS_LAVA(levl[x][y].typ);}
boolean is_pool(coordxy x,coordxy y){return isok(x,y)&&IS_POOL(levl[x][y].typ);}
boolean is_waterwall(coordxy x,coordxy y){return isok(x,y)&&levl[x][y].typ==WATER;}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
int known_spell(short a0){logmsg("known_spell:%ld;",(long)a0);callback();return opts[1055] ? opts[1055] : 0;}
void learnscroll(struct obj * a0){logmsg("learnscroll:;");callback();}
xint16 ledger_no(d_level * lev){return lev->dnum*100+lev->dlevel;}
schar lev_by_name(const char * a0){logmsg("lev_by_name:;");callback();return opts[1058] ? opts[1058] : 0;}
boolean m_in_air(struct monst * a0){logmsg("m_in_air:;");callback();return opts[1059] ? opts[1059] : 0;}
void m_into_limbo(struct monst * a0){logmsg("m_into_limbo:;");callback();}
void m_unleash(struct monst * a0,boolean a1){logmsg("m_unleash:%ld;",(long)a1);callback();}
void make_angry_shk(struct monst * a0,coordxy a1,coordxy a2){logmsg("make_angry_shk:%ld:%ld;",(long)a1,(long)a2);callback();}
void make_blinded(long a0,boolean a1){logmsg("make_blinded:%ld:%ld;",(long)a0,(long)a1);callback();}
void make_confused(long a0,boolean a1){logmsg("make_confused:%ld:%ld;",(long)a0,(long)a1);callback();}
void make_stunned(long a0,boolean a1){logmsg("make_stunned:%ld:%ld;",(long)a0,(long)a1);callback();}
boolean may_passwall(coordxy a0,coordxy a1){logmsg("may_passwall:%ld:%ld;",(long)a0,(long)a1);callback();return opts[1066] ? opts[1066] : 1;}
void maybe_unhide_at(coordxy a0,coordxy a1){logmsg("maybe_unhide_at:%ld:%ld;",(long)a0,(long)a1);callback();}
void migrate_to_level(struct monst * a0,xint16 a1,xint16 a2,coord * a3){logmsg("migrate_to_level:%ld:%ld;",(long)a1,(long)a2);callback();}
int mintrap(struct monst * a0,unsigned int a1){logmsg("mintrap:%ld;",(long)a1);callback();return opts[1069] ? opts[1069] : 0;}
struct obj * mksobj(int a0,boolean a1,boolean a2){logmsg("mksobj:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback();return &obj[0];}
int mon_has_amulet(struct monst * a0){logmsg("mon_has_amulet:;");callback();return opts[1071] ? opts[1071] : 0;}
char * mon_nam(struct monst * a0){logmsg("mon_nam:;");callback();return "monster";}
void mon_track_clear(struct monst * a0){logmsg("mon_track_clear:;");callback();}
void morehungry(int a0){logmsg("morehungry:%ld;",(long)a0);callback();}
void move_bc(int a0,int a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5){logmsg("move_bc:%ld:%ld:%ld:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2,(long)a3,(long)a4,(long)a5);callback();}
int near_capacity(void){logmsg("near_capacity:;");callback();return opts[1076] ? opts[1076] : 0;}
void newsym(coordxy a0,coordxy a1){logmsg("newsym:%ld:%ld;",(long)a0,(long)a1);callback();}
boolean next_to_u(void){logmsg("next_to_u;");return !opts[67];}
char * noit_mon_nam(struct monst * a0){logmsg("noit_mon_nam:;");callback();return "monster";}
void nomul(int a0){logmsg("nomul:%ld;",(long)a0);callback();}
void notice_all_mons(boolean a0){logmsg("notice_all_mons:%ld;",(long)a0);callback();}
void obj_extract_self(struct obj * a0){logmsg("obj_extract_self:;");callback();}
boolean on_level(d_level * lev1,d_level * lev2){return lev1->dnum==lev2->dnum&&lev1->dlevel==lev2->dlevel;}
boolean onscary(coordxy a0,coordxy a1,struct monst * a2){logmsg("onscary:%ld:%ld;",(long)a0,(long)a1);callback();return opts[1084] ? opts[1084] : 0;}
boolean onshopbill(struct obj * a0,struct monst * a1,boolean a2){logmsg("onshopbill:%ld;",(long)a2);callback();return opts[1085] ? opts[1085] : 0;}
void place_monster(struct monst * mon,coordxy x,coordxy y){observe_mon("place",mon);logmsg("to:%d/%d;",x,y);mon->mx=x;mon->my=y;svl.level.monsters[x][y]=mon;callback();}
void place_object(struct obj * otmp,coordxy x,coordxy y){logmsg("placeobj:%d:%d/%d;",oid(otmp),x,y);otmp->ox=x;otmp->oy=y;callback();}
void place_worm_tail_randomly(struct monst * a0,coordxy a1,coordxy a2){logmsg("place_worm_tail_randomly:%ld:%ld;",(long)a1,(long)a2);callback();}
void placebc(void){logmsg("placebc:;");callback();}
schar print_dungeon(boolean menu,schar * dlev,xint16 * dnum){logmsg("print_dungeon:%d;",menu);*dlev=7;*dnum=1;return opts[66];}
void prinv(const char * a0,struct obj * a1,long a2){logmsg("prinv:%ld;",(long)a2);callback();}
void remove_worm(struct monst * a0){logmsg("remove_worm:;");callback();}
void reset_utrap(boolean a0){logmsg("reset_utrap:%ld;",(long)a0);callback();}
boolean revive_corpse(struct obj * a0){logmsg("revive_corpse:;");callback();return opts[1094] ? opts[1094] : 0;}
void schedule_goto(d_level * lev,int utotype,const char * pre_msg,const char * post_msg){logmsg("goto:%d/%d:%d:%s:%s;",lev->dnum,lev->dlevel,utotype,pre_msg?pre_msg:"NULL",post_msg?post_msg:"NULL");callback();}
struct mkroom * search_special(schar typ){return opts[63]?&room:0;}
void see_monsters(void){logmsg("see_monsters:;");callback();}
void seetrap(struct trap * a0){logmsg("seetrap:;");callback();}
struct engr * sengr_at(const char * a0,coordxy a1,coordxy a2,boolean a3){logmsg("sengr_at:%ld:%ld:%ld;",(long)a1,(long)a2,(long)a3);callback();return 0;}
int sensemon(struct monst * a0){logmsg("sensemon:;");callback();return opts[1100] ? opts[1100] : 1;}
void set_apparxy(struct monst * a0){logmsg("set_apparxy:;");callback();}
void set_mon_data(struct monst * mon,struct permonst * ptr){unsigned long h=1469598103934665603UL;for(size_t i=0;i<sizeof *mon;i++){h^=((unsigned char*)mon)[i];h*=1099511628211UL;}logmsg("zero-monster-bytes:%lu;",h);mon->data=ptr;mon->mnum=(short)(ptr-mons);}
void set_msg_xy(coordxy a0,coordxy a1){logmsg("set_msg_xy:%ld:%ld;",(long)a0,(long)a1);callback();}
void set_ustuck(struct monst * mtmp){u.ustuck=mtmp;if(!mtmp)u.uswallow=0;}
void settrack(void){logmsg("settrack:;");callback();}
void shieldeff(coordxy a0,coordxy a1){logmsg("shieldeff:%ld:%ld;",(long)a0,(long)a1);callback();}
boolean single_level_branch(d_level * a0){logmsg("single_level_branch:;");callback();return opts[1107] ? opts[1107] : 0;}
struct obj * sobj_at(int otyp,coordxy x,coordxy y){return opts[61]?&obj[0]:0;}
boolean somexyspace(struct mkroom * room,coord * cc){cc->x=15;cc->y=15;return opts[64];}
int spelleffects(int a0,boolean a1,boolean a2){logmsg("spelleffects:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback();return opts[1110] ? opts[1110] : 0;}
void spoteffects(boolean pick){logmsg("spoteffects:%d;",pick);callback();if(opts[33]&&!reenter){reenter=1;tele_trap(&traps[0]);reenter=0;}}
long stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logmsg("stolen_value:%ld:%ld:%ld:%ld;",(long)a1,(long)a2,(long)a3,(long)a4);callback();return opts[1112] ? opts[1112] : 0;}
void subfrombill(struct obj * a0,struct monst * a1){logmsg("subfrombill:;");callback();}
const char * surface(coordxy a0,coordxy a1){logmsg("surface:%ld:%ld;",(long)a0,(long)a1);callback();return "monster";}
void switch_terrain(void){logmsg("switch_terrain:;");callback();}
struct trap * t_at(coordxy x,coordxy y){for(int i=0;i<4;i++)if(traps[i].ttyp&&traps[i].tx==x&&traps[i].ty==y)return &traps[i];return 0;}
int tport_spell(int a0){logmsg("tport_spell:%ld;",(long)a0);callback();return opts[1117] ? opts[1117] : 0;}
void u_left_shop(char * a0,boolean a1){logmsg("u_left_shop:%ld;",(long)a1);callback();}
const char * u_locomotion(const char * a0){logmsg("u_locomotion:;");callback();return "monster";}
void u_on_newpos(coordxy x,coordxy y){logmsg("hero:%d/%d;",x,y);u.ux=x;u.uy=y;callback();}
void uleftvault(struct monst * a0){logmsg("uleftvault:;");callback();}
boolean unconscious(void){logmsg("unconscious:;");callback();return opts[1122] ? opts[1122] : 0;}
void unplacebc(void){logmsg("unplacebc:;");callback();}
void unstuck(struct monst * a0){logmsg("unstuck:;");callback();}
void update_monster_region(struct monst * a0){logmsg("update_monster_region:;");callback();}
void update_player_regions(void){logmsg("update_player_regions:;");callback();}
char vault_occupied(char * rooms){return opts[68];}
void vision_recalc(int a0){logmsg("vision_recalc:%ld;",(long)a0);callback();}
void yelp(struct monst * a0){logmsg("yelp:;");callback();}
char yn_function(const char * query,const char * resp,char def,boolean hidden){logmsg("yn:%s:%s:%d;",query,resp,def);return opts[43]?opts[43]:def;}
boolean digit(char c){return c>=48&&c<=57;}
char*eos(char*s){return s+strlen(s);}
static void backend_start2(winid w,unsigned long f){logmsg("start2:%d:%lu;",w,f);}
static winid backend_create(int typ){logmsg("create:%d;",typ);if(opts[75]&&!reenter){reenter=1;dotelecmd();reenter=0;}if(opts[76])windowprocs.win_start_menu=backend_start2;callback();return 17;}
static void backend_start(winid w,unsigned long f){logmsg("start:%d:%lu;",w,f);}
static void backend_end(winid w,const char*s){logmsg("end:%d:%s;",w,s);}
static void backend_destroy(winid w){logmsg("destroy:%d;",w);}
static void backend_display(winid w,boolean b){logmsg("display:%d:%d;",w,b);callback();}
void add_menu(winid w,const glyph_info*g,const anything*a,char c,char group,int attr,int color,const char*s,unsigned f){logmsg("menu:%d:%d:%d:%d:%d:%d:%s:%u;",w,a?a->a_int:0,c,group,attr,color,s,f);callback();}
int select_menu(winid w,int how,menu_item**p){logmsg("select:%d:%d;",w,how);*p=0;if(menu_mode>0){*p=malloc(sizeof **p);(*p)->item.a_int=menu_mode;return 1;}return menu_mode;}
boolean probe_filter(coordxy x,coordxy y){filtercalls++;if(opts[34]&&!nestedguard){nestedguard=1;collect_coords(nested,3,3,1,CC_UNSHUFFLED,0);nestedguard=0;}callback();return (x+y)%3!=0;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/teleport.c"
#define TELEPORT_TELEPORT_VALIDATE_SOURCE
#endif
#include "../nethack-c/wasm/tu-fragments/teleport-support.c"
void probe_reset(unsigned seed){
memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&svd,0,sizeof svd);memset(&svu,0,sizeof svu);memset(&svm,0,sizeof svm);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&gv,0,sizeof gv);memset(&svk,0,sizeof svk);memset(mon,0,sizeof mon);memset(obj,0,sizeof obj);memset(traps,0,sizeof traps);memset(stairs,0,sizeof stairs);memset(mons,0,sizeof mons);memset(objects,0,sizeof objects);memset(opts,0,sizeof opts);memset(candy,0x5a,sizeof candy);memset(&resultcc,0x5a,sizeof resultcc);
pos=draws=filtercalls=nestedguard=reenter=input_count=debug_count=0;callback_sp=0;tracebuf[0]=0;rngstate=seed;menu_mode=-1;uball=uchain=uarmf=0;gs.stairs=0;go.occupation=0;gc.current_wand=0;gi.invent=0;flags.debug=0;strcpy(textbuf,"\033");
u.ux=u.ux0=40;u.uy=u.uy0=10;u.uz.dlevel=5;u.uz0=u.uz;u.ulevel=20;u.uen=100;u.uhunger=900;svm.moves=1;svn.n_dgns=3;
svd.dungeon_topology.d_astral_level.dnum=14;svd.dungeon_topology.d_sokoban_dnum=13;svd.dungeon_topology.d_tutorial_dnum=12;svd.dungeon_topology.d_qstart_level.dnum=11;svd.dungeon_topology.d_mineend_level.dnum=10;svd.dungeon_topology.d_valley_level.dnum=9;
for(int i=0;i<16;i++){svd.dungeons[i].num_dunlevs=20;svd.dungeons[i].depth_start=1;}
for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;
for(int i=0;i<NUMMONS+1;i++){mons[i].pmnames[NEUTRAL]="fixture";mons[i].mlet=S_HUMAN;}
for(int i=0;i<4;i++){mon[i].data=&mons[i];mon[i].mnum=i;mon[i].mx=10+i;mon[i].my=10;mon[i].mhp=20;mon[i].m_id=i+1;mon[i].nmon=i<3?&mon[i+1]:0;svl.level.monsters[10+i][10]=&mon[i];obj[i].otyp=BOULDER;obj[i].ox=10+i;obj[i].oy=10;traps[i].tx=20+i;traps[i].ty=10;}
svl.level.monlist=mon;gy.youmonst.data=&mons[0];gy.youmonst.mhp=20;
for(int y=0;y<ROWNO;y++){visionrows[y]=vision[y];for(int x=0;x<COLNO;x++)vision[y][x]=COULD_SEE|IN_SIGHT;}gv.viz_array=visionrows;
windowprocs.win_create_nhwindow=backend_create;windowprocs.win_start_menu=backend_start;windowprocs.win_end_menu=backend_end;windowprocs.win_destroy_nhwindow=backend_destroy;windowprocs.win_display_nhwindow=backend_display;
}
void probe_clear(void){pos=0;tracebuf[0]=0;draws=filtercalls=0;callback_sp=0;}
void probe_option(int i,long v){opts[i]=v;}
void probe_input(const char*s){strcpy(textbuf,s);}
void probe_menu(int n){menu_mode=n;}
void*probe_pointer(int kind,int i){switch(kind){case 0:return &mon[i];case 1:return &mons[i];case 2:return &obj[i];case 3:return &traps[i];case 4:return &resultcc;case 5:return candy;case 6:return(void*)probe_filter;case 7:return &stairs[i];case 8:return &gy.youmonst;case 9:return &u.uz;}return 0;}
void probe_record(int kind,int field,int i,long value){void*p=probe_pointer(kind,i);int map[]={0,1,2,3,4};teleport_teleport_record_set(map[kind],field,p,value);}
void probe_field(int i,long v){teleport_teleport_set(i,v);}
void probe_link(int kind,int i){switch(kind){case 0:u.ustuck=i<0?0:&mon[i];break;case 1:u.usteed=i<0?0:&mon[i];break;case 2:uball=i<0?0:&obj[i];break;case 3:uchain=i<0?0:&obj[i];break;case 4:uarmf=i<0?0:&obj[i];break;case 5:gi.invent=i<0?0:&obj[i];break;case 6:gs.stairs=i<0?0:&stairs[i];break;case 7:mon[0].minvent=i<0?0:&obj[i];break;}}
void probe_trap(int i,int type,int x,int y,int dx,int dy,int once){traps[i].ttyp=type;traps[i].tx=x;traps[i].ty=y;traps[i].teledest.x=dx;traps[i].teledest.y=dy;traps[i].once=once;traps[i].tseen=1;traps[i].dst.dnum=1;traps[i].dst.dlevel=7;}
void probe_dest(int which,int lx,int ly,int hx,int hy,int nlx,int nly,int nhx,int nhy){struct dest_area*p=which?&svu.updest:&svd.dndest;*p=(struct dest_area){lx,ly,hx,hy,nlx,nly,nhx,nhy};}
void probe_level(int dnum,int dlevel){u.uz.dnum=dnum;u.uz.dlevel=dlevel;u.uz0=u.uz;}
void probe_stair(int i,int x,int y,int ladder,int up){stairs[i].sx=x;stairs[i].sy=y;stairs[i].isladder=ladder;stairs[i].up=up;stairs[i].tolev=u.uz;stairs[i].next=i<3?&stairs[i+1]:0;}
void probe_role(int pm){gu.urole.mnum=pm;}
void probe_debug(int b){flags.debug=b;}
void probe_vision(int mask){for(int y=0;y<ROWNO;y++)for(int x=0;x<COLNO;x++)vision[y][x]=mask;}
void probe_objlevel(int n){objects[SPE_TELEPORT_AWAY].oc_level=n;}
void probe_dungeon(int i,int n,int depth,int reached){svd.dungeons[i].num_dunlevs=n;svd.dungeons[i].depth_start=depth;svd.dungeons[i].dunlev_ureached=reached;svd.dungeon_topology.d_qlocate_level.dnum=11;svd.dungeon_topology.d_qlocate_level.dlevel=3;}

void probe_tile(int x,int y,int typ,int flags){levl[x][y].typ=typ;levl[x][y].flags=flags;}
void probe_property(int i,long intrinsic,long extrinsic,long blocked){u.uprops[i].intrinsic=intrinsic;u.uprops[i].extrinsic=extrinsic;u.uprops[i].blocked=blocked;}
const char*probe_trace(void){return tracebuf;}
const char*probe_snapshot(int n){int p=0;p+=snprintf(snap+p,sizeof snap-p,"cc:%d/%d;hero:%d/%d/%d/%d/%ld/%ld/%ld/%ld;draws:%d;filters:%d;",resultcc.x,resultcc.y,u.ux,u.uy,u.uz.dnum,u.uz.dlevel,HTeleportation,ETeleportation,HStun,HConfusion,draws,filtercalls);p+=snprintf(snap+p,sizeof snap-p,"state:%ld/%ld/%d/%d/%d/%d/%s;",svm.moves,svl.level.flags.stasis_until,u.uen,u.uhunger,disp.botl,iflags.last_msg,u.urooms);for(int i=0;i<4;i++)p+=snprintf(snap+p,sizeof snap-p,"mon%d:%d/%d/%u/%ld/%lu/%u/%d;obj%d:%d/%d/%u/%u;",i,mon[i].mx,mon[i].my,mon[i].mconf,mon[i].mstate,mon[i].mstrategy,mon[i].mtrapped,(int)(mon[i].data-mons),i,obj[i].ox,obj[i].oy,obj[i].no_charge,obj[i].unpaid);for(int i=0;i<n;i++)p+=snprintf(snap+p,sizeof snap-p,"%d/%d,",candy[i].x,candy[i].y);return snap;}
int probe_layout_count(void){return SIZE(teleport_teleport_layout);}const char*probe_layout_name(int i){return teleport_teleport_layout[i].name;}long probe_layout_value(int i){return teleport_teleport_layout[i].value;}
long probe_stack(void){return emscripten_stack_get_current();}
long probe_call(int which,long a0,long a1,long a2,long a3,long a4,long a5){switch(which){
#ifndef TELEPORT_REFERENCE_TU
extern boolean teleport_teleport_callback_m_blocks_teleporting(struct monst * mtmp);
#define m_blocks_teleporting teleport_teleport_callback_m_blocks_teleporting
#endif
case 0:return(long)m_blocks_teleporting((struct monst *)(intptr_t)a0);
case 1:return(long)noteleport_level((struct monst *)(intptr_t)a0);
#ifndef TELEPORT_REFERENCE_TU
extern boolean teleport_teleport_callback_goodpos_onscary(coordxy x,coordxy y,struct permonst * mptr);
#define goodpos_onscary teleport_teleport_callback_goodpos_onscary
#endif
case 2:return(long)goodpos_onscary((coordxy)a0,(coordxy)a1,(struct permonst *)(intptr_t)a2);
case 3:return(long)goodpos((coordxy)a0,(coordxy)a1,(struct monst *)(intptr_t)a2,(mmflags_nht)a3);
case 4:return(long)enexto((coord *)(intptr_t)a0,(coordxy)a1,(coordxy)a2,(struct permonst *)(intptr_t)a3);
case 5:return(long)enexto_gpflags((coord *)(intptr_t)a0,(coordxy)a1,(coordxy)a2,(struct permonst *)(intptr_t)a3,(mmflags_nht)a4);
case 6:return(long)enexto_core((coord *)(intptr_t)a0,(coordxy)a1,(coordxy)a2,(struct permonst *)(intptr_t)a3,(mmflags_nht)a4);
#ifndef TELEPORT_REFERENCE_TU
extern boolean teleport_teleport_callback_tele_jump_ok(coordxy x1,coordxy y1,coordxy x2,coordxy y2);
#define tele_jump_ok teleport_teleport_callback_tele_jump_ok
#endif
case 7:return(long)tele_jump_ok((coordxy)a0,(coordxy)a1,(coordxy)a2,(coordxy)a3);
#ifndef TELEPORT_REFERENCE_TU
extern boolean teleport_teleport_callback_teleok(coordxy x,coordxy y,boolean trapok);
#define teleok teleport_teleport_callback_teleok
#endif
case 8:return(long)teleok((coordxy)a0,(coordxy)a1,(boolean)a2);
case 9:teleds((coordxy)a0,(coordxy)a1,(int)a2);return 0;
case 10:return(long)collect_coords((coord *)(intptr_t)a0,(coordxy)a1,(coordxy)a2,(int)a3,(unsigned int)a4,(boolean (*)(coordxy, coordxy))(intptr_t)a5);
case 11:return(long)safe_teleds((int)a0);
#ifndef TELEPORT_REFERENCE_TU
extern void teleport_teleport_callback_vault_tele(void);
#define vault_tele teleport_teleport_callback_vault_tele
#endif
case 12:vault_tele();return 0;
case 13:return(long)teleport_pet((struct monst *)(intptr_t)a0,(boolean)a1);
case 14:tele_to_rnd_pet();return 0;
case 15:tele();return 0;
case 16:scrolltele((struct obj *)(intptr_t)a0);return 0;
case 17:return(long)dotelecmd();
case 18:return(long)dotele((boolean)a0);
case 19:level_tele();return 0;
case 20:domagicportal((struct trap *)(intptr_t)a0);return 0;
case 21:tele_trap((struct trap *)(intptr_t)a0);return 0;
case 22:level_tele_trap((struct trap *)(intptr_t)a0,(unsigned int)a1);return 0;
#ifndef TELEPORT_REFERENCE_TU
extern boolean teleport_teleport_callback_rloc_pos_ok(coordxy x,coordxy y,struct monst * mtmp);
#define rloc_pos_ok teleport_teleport_callback_rloc_pos_ok
#endif
case 23:return(long)rloc_pos_ok((coordxy)a0,(coordxy)a1,(struct monst *)(intptr_t)a2);
#ifndef TELEPORT_REFERENCE_TU
extern void teleport_teleport_callback_rloc_to_core(struct monst * mtmp,coordxy x,coordxy y,unsigned int rlocflags);
#define rloc_to_core teleport_teleport_callback_rloc_to_core
#endif
case 24:rloc_to_core((struct monst *)(intptr_t)a0,(coordxy)a1,(coordxy)a2,(unsigned int)a3);return 0;
case 25:rloc_to((struct monst *)(intptr_t)a0,(coordxy)a1,(coordxy)a2);return 0;
case 26:rloc_to_flag((struct monst *)(intptr_t)a0,(coordxy)a1,(coordxy)a2,(unsigned int)a3);return 0;
#ifndef TELEPORT_REFERENCE_TU
extern stairway * teleport_teleport_callback_stairway_find_forwiz(boolean isladder,boolean up);
#define stairway_find_forwiz teleport_teleport_callback_stairway_find_forwiz
#endif
case 27:return(long)(intptr_t)stairway_find_forwiz((boolean)a0,(boolean)a1);
case 28:return(long)rloc((struct monst *)(intptr_t)a0,(unsigned int)a1);
case 29:return(long)control_mon_tele((struct monst *)(intptr_t)a0,(coord *)(intptr_t)a1,(unsigned int)a2,(boolean)a3);
#ifndef TELEPORT_REFERENCE_TU
extern void teleport_teleport_callback_mvault_tele(struct monst * mtmp);
#define mvault_tele teleport_teleport_callback_mvault_tele
#endif
case 30:mvault_tele((struct monst *)(intptr_t)a0);return 0;
case 31:return(long)tele_restrict((struct monst *)(intptr_t)a0);
case 32:mtele_trap((struct monst *)(intptr_t)a0,(struct trap *)(intptr_t)a1,(int)a2);return 0;
case 33:return(long)mlevel_tele_trap((struct monst *)(intptr_t)a0,(struct trap *)(intptr_t)a1,(boolean)a2,(int)a3);
case 34:return(long)rloco((struct obj *)(intptr_t)a0);
case 35:return(long)random_teleport_level();
case 36:return(long)u_teleport_mon((struct monst *)(intptr_t)a0,(boolean)a1);
}return -999;}
