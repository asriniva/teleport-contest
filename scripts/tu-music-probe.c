#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
struct you u;
__typeof__(gy) gy;
__typeof__(svl) svl;
__typeof__(svc) svc;
__typeof__(svt) svt;
__typeof__(gc) gc;
__typeof__(disp) disp;
__typeof__(svd) svd;
__typeof__(gu) gu;
__typeof__(gv) gv;
__typeof__(flags) flags;
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
const char ynqchars[]="ynq";
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind."};
static struct monst monsters[16];
static struct obj instrument,boulder;
static struct trap traps[COLNO][ROWNO];
static unsigned char trap_present[COLNO][ROWNO];
static seenV vision[ROWNO][COLNO],*visionrows[ROWNO];
static int opts[40],random_values[4096],random_length,random_index,yn_count;
static unsigned random_state;
static char tracebuf[2097152],statebuf[131072],caller[128],inputbuf[BUFSZ],resultbuf[BUFSZ];
static void *growth;
static int mid(struct monst *m){return m==&gy.youmonst?-1:m?(int)(m-monsters)+1:0;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
void impossible(const char *f,...){char b[BUFSZ];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append("impossible:%s;",b);}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(Your) MSG(You_feel) MSG(You_cant) MSG(You_hear) MSG(pline_The) MSG(Norep)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *f,int line,const char *fn){const char *b=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
int (rnl)(int n){int v=draw(n);append("rnl:%d:%d@%s;",n,v,caller);return v;}
int (d)(int n,int x){int i,v=n;for(i=0;i<n;i++)v+=draw(x);append("d:%d:%d:%d@%s;",n,x,v,caller);return v;}
static void callback(void){if(opts[30]){opts[30]=0;append("nested;");awaken_soldiers(&gy.youmonst);}if(opts[31]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew;");}}
char *Monnam(struct monst *m){append("Monnam:%d;",mid(m));return "Fixture monster";}
char *mon_nam(struct monst *m){append("mon_nam:%d;",mid(m));return "fixture monster";}
char *Amonnam(struct monst *m){return "A fixture monster";}
char *a_monnam(struct monst *m){return "a fixture monster";}
char *x_monnam(struct monst *m,int a,const char *s,int suppress,boolean cap){append("xname:%d:%d:%s:%d:%d;",mid(m),a,s,suppress,cap);return "the poor fixture monster";}
int canseemon(struct monst *m){boolean visible=!Blind&&!m->mundetected&&opts[24]&&cansee(m->mx,m->my);append("canseemon:%d:%d;",mid(m),visible);return visible;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);callback();}
int resist(struct monst *m,char c,int dmg,int tell){append("resist:%d:%d:%d:%d;",mid(m),c,dmg,tell);callback();return opts[1];}
boolean onscary(coordxy x,coordxy y,struct monst *m){append("onscary:%d:%d:%d;",x,y,mid(m));return opts[2];}
void monflee(struct monst *m,int duration,boolean first,boolean fleemsg){append("flee:%d:%d:%d:%d;",mid(m),duration,first,fleemsg);m->mflee=1;}
int sleep_monst(struct monst *m,int duration,int how){append("sleep:%d:%d:%d;",mid(m),duration,how);callback();return opts[3];}
void slept_monst(struct monst *m){append("slept:%d;",mid(m));}
boolean tamedog(struct monst *m,struct obj *o,boolean tame){append("tame:%d:%d:%d;",mid(m),o!=NULL,tame);m->mtame=5;m->mpeaceful=1;if(opts[4])m->nmon=NULL;callback();return TRUE;}
struct trap *t_at(coordxy x,coordxy y){return isok(x,y)&&trap_present[x][y]?&traps[x][y]:NULL;}
struct trap *maketrap(coordxy x,coordxy y,int typ){append("maketrap:%d:%d:%d;",x,y,typ);callback();if(opts[5])return NULL;trap_present[x][y]=1;traps[x][y].tx=x;traps[x][y].ty=y;traps[x][y].ttyp=typ;return &traps[x][y];}
struct obj *sobj_at(int typ,coordxy x,coordxy y){append("sobj:%d:%d:%d;",typ,x,y);return opts[6]?&boulder:NULL;}
void obj_extract_self(struct obj *o){append("extract-boulder;");o->where=OBJ_FREE;}
boolean flooreffects(struct obj *o,coordxy x,coordxy y,const char *s){append("flooreffects:%d:%d:%s;",x,y,s);o->where=OBJ_DELETED;return TRUE;}
schar fillholetyp(coordxy x,coordxy y,boolean b){append("fill:%d:%d:%d;",x,y,b);return opts[7];}
boolean set_levltyp(coordxy x,coordxy y,schar typ){append("settyp:%d:%d:%d;",x,y,typ);levl[x][y].typ=typ;return TRUE;}
void liquid_flow(coordxy x,coordxy y,schar typ,struct trap *t,const char *s){append("liquid:%d:%d:%d:%d;",x,y,typ,s!=NULL);if(opts[8])trap_present[x][y]=0;if(opts[9]&&m_at(x,y))m_at(x,y)->mhp=0;callback();}
void mselftouch(struct monst *m,const char *s,boolean b){append("mself:%d:%s:%d;",mid(m),s,b);if(opts[10])m->mhp=0;}
void xkilled(struct monst *m,int flags){append("killed:%d:%d;",mid(m),flags);m->mhp=0;}
void reset_utrap(boolean msg){append("reset-utrap:%d;",msg);u.utrap=0;}
void set_utrap(unsigned n,unsigned typ){append("utrap:%u:%u;",n,typ);u.utrap=n;u.utraptype=typ;}
void losehp(int dmg,const char *why,schar how){append("losehp:%d:%s:%d;",dmg,why,how);u.uhp-=dmg;}
void selftouch(const char *s){append("selftouch:%s;",s);}
void exercise(int attr,boolean inc){append("exercise:%d:%d;",attr,inc);}
schar acurr(int attr){append("acurr:%d;",attr);return opts[11];}
void wakeup(struct monst *m,boolean via){append("wakeup:%d:%d;",mid(m),via);m->msleeping=0;m->mpeaceful=0;}
void seemimic(struct monst *m){append("seemimic:%d;",mid(m));m->m_ap_type=M_AP_NOTHING;}
int altarmask_at(coordxy x,coordxy y){append("altar:%d:%d;",x,y);return opts[12];}
const char *align_str(aligntyp a){return a<0?"chaotic":a>0?"lawful":"neutral";}
void desecrate_altar(boolean a,aligntyp b){append("desecrate:%d:%d;",a,b);}
void unblock_point(int x,int y){append("unblock:%d:%d;",x,y);}
void cvt_sdoor_to_door(struct rm *r){append("convert-door;");r->typ=DOOR;r->doormask=D_CLOSED;}
void recalc_block_point(coordxy x,coordxy y){append("recalc:%d:%d;",x,y);}
char *in_rooms(coordxy x,coordxy y,int typ){append("rooms:%d:%d:%d;",x,y,typ);return opts[13]?"A":"";}
void add_damage(coordxy x,coordxy y,long n){append("damage:%d:%d:%ld;",x,y,n);}
boolean on_level(d_level *a,d_level *b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean In_V_tower(d_level *l){append("tower:%d:%d;",l->dnum,l->dlevel);return opts[14];}
char *the(const char *s){static char b[BUFSZ];append("the:%s;",s);snprintf(b,sizeof b,"the %s",s);return b;}
char *an(const char *s){static char b[BUFSZ];append("an:%s;",s);snprintf(b,sizeof b,"a %s",s);return b;}
char *yname(struct obj *o){append("yname:%d:%d;",o->otyp,o->spe);return "your instrument";}
char *Tobjnam(struct obj *o,const char *v){static char b[BUFSZ];snprintf(b,sizeof b,"The instrument %s",v);return b;}
char *Yname2(struct obj *o){return "Your instrument";}
char *xname(struct obj *o){return "instrument";}
char *thesimpleoname(struct obj *o){return "the instrument";}
void consume_obj_charge(struct obj *o,boolean b){append("charge:%d:%d;",o->spe,b);o->spe--;}
int getdir(const char *s){append("getdir:%d;",s!=NULL);callback();return opts[15];}
int zapyourself(struct obj *o,boolean b){append("zapyourself:%d:%d;",o->otyp,b);return opts[16];}
const char *flash_str(int n,boolean b){append("flash:%d:%d;",n,b);return "flash";}
void ubuzz(int n,int dice){append("ubuzz:%d:%d:%d;",n,dice,gc.current_wand==&instrument);callback();}
void discover_object(int typ,boolean m,boolean h,boolean c){append("known:%d:%d:%d:%d;",typ,m,h,c);objects[typ].oc_name_known=1;}
void incr_itimeout(long *p,int n){append("timeout:%ld:%d;",*p,n);*p+=n;}
boolean can_blow(struct monst *m){append("blow:%d;",mid(m));return opts[17];}
char yn_function(const char *q,const char *choices,char def,boolean save){append("yn:%s:%s:%d:%d;",q,choices,def,save);return opts[yn_count++?19:18];}
void getlin(const char *q,char *out){append("getlin:%s;",q);strcpy(out,inputbuf);callback();}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
boolean find_drawbridge(coordxy *x,coordxy *y){append("findbridge:%d:%d;",*x,*y);if(opts[20]){*x=opts[21];*y=opts[22];return TRUE;}return FALSE;}
int is_drawbridge_wall(coordxy x,coordxy y){append("bridgewall:%d:%d;",x,y);return opts[23];}
void close_drawbridge(coordxy x,coordxy y){append("closebridge:%d:%d;",x,y);levl[x][y].typ=DRAWBRIDGE_UP;}
void open_drawbridge(coordxy x,coordxy y){append("openbridge:%d:%d;",x,y);levl[x][y].typ=DRAWBRIDGE_DOWN;}
void record_achievement(schar a){append("achievement:%d;",a);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/music.c"
#else
extern void teleport_music_test_awaken_scare(struct monst*,boolean),teleport_music_test_awaken(int),teleport_music_test_sleep(int),teleport_music_test_snakes(int),teleport_music_test_nymphs(int),teleport_music_test_charm(int),teleport_music_test_pit(coordxy,coordxy,unsigned),teleport_music_test_earthquake(int);
extern const char *teleport_music_test_description(void);
extern int teleport_music_test_improvise(struct obj*);
extern char *teleport_music_test_notes(boolean*);
#define awaken_scare teleport_music_test_awaken_scare
#define awaken_monsters teleport_music_test_awaken
#define put_monsters_to_sleep teleport_music_test_sleep
#define charm_snakes teleport_music_test_snakes
#define calm_nymphs teleport_music_test_nymphs
#define charm_monsters teleport_music_test_charm
#define do_pit teleport_music_test_pit
#define do_earthquake teleport_music_test_earthquake
#define generic_lvl_desc teleport_music_test_description
#define do_improvisation teleport_music_test_improvise
#define improvised_notes teleport_music_test_notes
#endif
#include "tu-music-layout.h"
void probe_reset(unsigned seed){int x,y;if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&svc,0,sizeof svc);memset(&svt,0,sizeof svt);memset(&gc,0,sizeof gc);memset(&disp,0,sizeof disp);memset(&svd,0,sizeof svd);memset(&gu,0,sizeof gu);memset(&gv,0,sizeof gv);memset(&flags,0,sizeof flags);memset(monsters,0,sizeof monsters);memset(&instrument,0,sizeof instrument);memset(&boulder,0,sizeof boulder);memset(traps,0,sizeof traps);memset(trap_present,0,sizeof trap_present);memset(opts,0,sizeof opts);opts[0]=opts[2]=opts[3]=opts[15]=opts[17]=opts[24]=1;opts[7]=ROOM;opts[11]=18;opts[18]=opts[19]='y';opts[23]=-1;monst_globals_init();objects_globals_init();for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=STONE;vision[y][x]=IN_SIGHT;}for(y=0;y<ROWNO;y++)visionrows[y]=vision[y];gv.viz_array=visionrows;u.ux=u.uy=10;u.ulevel=10;u.uhp=100;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=100;gu.urole.mnum=PM_ARCHEOLOGIST;u.uz.dnum=1;u.uz.dlevel=2;astral_level.dnum=5;astral_level.dlevel=9;sanctum_level.dnum=6;sanctum_level.dlevel=7;sokoban_dnum=8;stronghold_level.dnum=9;stronghold_level.dlevel=2;strcpy(svt.tune,"ABCDE");instrument.otyp=WOODEN_FLUTE;instrument.spe=3;instrument.quan=1;random_state=seed;random_length=random_index=yn_count=0;inputbuf[0]=resultbuf[0]=tracebuf[0]=caller[0]=0;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int i,int v){opts[i]=v;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_add_monster(int i,int pm,int x,int y){struct monst *m=&monsters[i];m->data=&mons[pm];m->mx=x;m->my=y;m->mhp=m->mhpmax=20;m->mcanmove=1;m->msleeping=1;m->mfrozen=3;m->mavenge=1;m->mstrategy=STRAT_WAITMASK|1UL;m->nmon=NULL;if(i){monsters[i-1].nmon=m;}fmon=monsters;svl.level.monsters[x][y]=m;}
void probe_monster_field(int i,int k,unsigned long v){struct monst *m=&monsters[i];switch(k){case 0:m->mhp=v;break;case 1:m->mpeaceful=v;break;case 2:m->mtame=v;break;case 3:m->mcanmove=v;break;case 4:m->mundetected=v;break;case 5:m->mstrategy=v;break;case 6:m->mtrapped=v;break;case 7:m->isshk=v;break;case 8:m->m_ap_type=v;break;case 9:m->msleeping=v;break;case 10:m->mfrozen=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.ulevel=v;break;case 3:u.utrap=v;break;case 4:u.utraptype=v;break;case 5:u.uswallow=v;u.ustuck=v?monsters:NULL;break;case 6:u.uinwater=v;break;case 7:u.uroleplay.deaf=v;break;case 8:u.uevent.uheard_tune=v;break;case 9:u.dx=v;break;case 10:u.dy=v;break;case 11:u.dz=v;break;case 12:u.umonnum=v;gy.youmonst.data=&mons[v];break;case 13:gu.urole.mnum=v;break;case 14:u.uz.dnum=v;break;case 15:u.uz.dlevel=v;break;case 16:u.usteed=v?monsters:NULL;break;case 17:vision[10][10]=v;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_terrain(int x,int y,int typ,int door){levl[x][y].typ=typ;levl[x][y].doormask=door;levl[x][y].seenv=0x80;levl[x][y].lit=1;levl[x][y].waslit=1;levl[x][y].edge=1;levl[x][y].roomno=5;}
void probe_trap(int x,int y,int typ){trap_present[x][y]=typ!=0;traps[x][y].tx=x;traps[x][y].ty=y;traps[x][y].ttyp=typ;}
void probe_object(int typ,int spe){instrument.otyp=typ;instrument.spe=spe;}
void probe_input(const char *s){strncpy(inputbuf,s,sizeof inputbuf-1);inputbuf[sizeof inputbuf-1]=0;}
void probe_tune(const char *s){strncpy(svt.tune,s,sizeof svt.tune-1);svt.tune[sizeof svt.tune-1]=0;}
int probe_action(int op,int a,int b,int c){boolean same=c;switch(op){case 0:awaken_scare(&monsters[a],b);break;case 1:awaken_monsters(a);break;case 2:put_monsters_to_sleep(a);break;case 3:charm_snakes(a);break;case 4:calm_nymphs(a);break;case 5:awaken_soldiers(a<0?&gy.youmonst:&monsters[a]);break;case 6:charm_monsters(a);break;case 7:do_pit(a,b,c);break;case 8:do_earthquake(a);break;case 9:strcpy(resultbuf,generic_lvl_desc());break;case 10:return do_improvisation(&instrument);case 11:strcpy(resultbuf,improvised_notes(&same));return same;case 12:return do_play_instrument(&instrument);case 13:return obj_to_instr(&instrument);}return 0;}
void *probe_pointer(int id){switch(id){case 0:return &instrument;case 1:return monsters;case 2:return &u;case 3:return &svc;case 4:return svt.tune;case 5:return resultbuf;case 6:return levl;case 7:return traps;case 8:return &boulder;case 9:return &gc;}return NULL;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){char *p=statebuf;int i,x,y;p+=sprintf(p,"hero:%d:%d:%d:%d:%u:%u:%d:%d:%ld:%d:%s:%s:%d;",u.ux,u.uy,u.ulevel,u.uhp,u.utrap,u.utraptype,u.uevent.uheard_tune,disp.botl,HDeaf,gc.current_wand==&instrument,svc.context.jingle,resultbuf,instrument.spe);for(i=0;i<16;i++){struct monst *m=&monsters[i];p+=sprintf(p,"mon%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%lu:%d;",i,m->data?monsndx(m->data):-1,m->mx,m->my,m->mhp,m->msleeping,m->mcanmove,m->mfrozen,m->mpeaceful,m->mavenge,m->mundetected,m->mtrapped,m->mtame,m->mflee,m->mstrategy,m->nmon?mid(m->nmon):0);}p+=sprintf(p,"map:");for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){unsigned char *r=(unsigned char*)&levl[x][y];for(i=0;i<sizeof levl[x][y];i++)p+=sprintf(p,"%02x",r[i]);if(trap_present[x][y])p+=sprintf(p,"t%d,%d,%d,%d/",x,y,traps[x][y].ttyp,traps[x][y].tseen);}p+=sprintf(p,"instrument:");{unsigned char *r=(unsigned char*)&instrument;for(i=0;i<sizeof instrument;i++)p+=sprintf(p,"%02x",r[i]);}p+=sprintf(p,"props:");{unsigned char *r=(unsigned char*)u.uprops;for(i=0;i<sizeof u.uprops;i++)p+=sprintf(p,"%02x",r[i]);}p+=sprintf(p,"known:");for(i=0;i<NUM_OBJECTS;i++)p+=sprintf(p,"%d",objects[i].oc_name_known);return statebuf;}
