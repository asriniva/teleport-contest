/* Controlled dependency fixture: only the reference inclusion below contains
 * explode.c policy. Stubs make mutation, messages and call order observable. */
#include "hack.h"
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include <stdarg.h>
#include <stdlib.h>
__typeof__(gy) gy;__typeof__(svl) svl;__typeof__(svk) svk;__typeof__(svc) svc;
__typeof__(gu) gu;__typeof__(gv) gv;__typeof__(gi) gi;__typeof__(gm) gm;__typeof__(gb) gb;__typeof__(gt) gt;
__typeof__(svd) svd;__typeof__(flags) flags;__typeof__(iflags) iflags;__typeof__(disp) disp;
struct you u;struct obj *uball,*uchain;
struct objclass objects[NUM_OBJECTS+1];struct permonst mons[NUMMONS+1];
__typeof__(windowprocs) windowprocs;
const struct Gender genders[]={ {"male","he","him","his",0,0}, {"female","she","her","her",0,0}, {"neuter","it","it","its",0,0} };
const schar xdir[N_DIRS]={-1,-1,0,1,1,1,0,-1},ydir[N_DIRS]={0,-1,-1,-1,0,1,1,1};
const int shield_static[SHIELD_COUNT]={S_ss1,S_ss2,S_ss3,S_ss4};
static struct monst victim;static struct obj nodes[64];static int node_count;
static struct attack attack;static struct permonst species;static struct trap fixture_trap;
static int opts[32],rng_count;static void *growth;static unsigned rng_state;static char caller[128];
static char tracebuf[131072],snapshotbuf[4096];
static seenV cells[ROWNO][COLNO];static seenV *rows[ROWNO];
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static void message(const char*tag,const char*f,va_list ap){logmsg("%s:",tag);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);logmsg(";");}
void panic(const char*f,...){abort();}
void impossible(const char*f,...){va_list ap;va_start(ap,f);message("impossible",f,ap);va_end(ap);}
void pline(const char*f,...){va_list ap;va_start(ap,f);message("msg",f,ap);va_end(ap);}
void pline_The(const char*f,...){va_list ap;va_start(ap,f);message("The",f,ap);va_end(ap);}
void You(const char*f,...){va_list ap;va_start(ap,f);message("You",f,ap);va_end(ap);}
void You_hear(const char*f,...){va_list ap;va_start(ap,f);message("hear",f,ap);va_end(ap);}
void nh_snprintf(const char*fn,int line,char*out,size_t size,const char*f,...){va_list ap;(void)fn;(void)line;va_start(ap,f);vsnprintf(out,size,f,ap);va_end(ap);}
boolean rng_log_enabled(void){return TRUE;}
void rng_log_set_caller(const char*f,int line,const char*fn){const char*base=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",base?base+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();rng_state=rng_state*1664525U+1013904223U;v=rng_state%(unsigned)n;rng_count++;logmsg("rng:%d:%d@%s;",n,v,caller);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}
int(d)(int count,int sides){int i,total=0;for(i=0;i<count;i++)total+=draw(sides)+1;return total;}
long*alloc(unsigned n){void*p=malloc(n);if(!p)abort();return p;}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
boolean Resists_Elem(struct monst*m,int p){(void)m;return !!(opts[0]&(1U<<p));}
boolean resists_magm(struct monst*m){(void)m;return opts[1];}
int canseemon(struct monst*m){(void)m;return opts[2];}int sensemon(struct monst*m){(void)m;return opts[3];}
boolean In_mines(d_level*d){(void)d;return FALSE;}boolean In_hell(d_level*d){(void)d;return FALSE;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
struct attack*dmgtype_fromattack(struct permonst*p,int a,int b){(void)p;(void)a;(void)b;return opts[4]?&attack:0;}
int Mgender(struct monst*m){return m->female?FEMALE:MALE;}
char*Monnam(struct monst*m){return m==&gy.youmonst?"You":"The target";}
const char*pmname(struct permonst*p,int gender){(void)p;(void)gender;return "sphere";}
char*Tobjnam(struct obj*o,const char*s){static char buf[80];snprintf(buf,sizeof buf,"object %s",s);return buf;}
char*s_suffix(const char*s){static char buf[80];snprintf(buf,sizeof buf,"%s's",s);return buf;}
char*rndmonnam(char*s){(void)s;return "gas spore";}
char*in_rooms(coordxy x,coordxy y,int k){(void)x;(void)y;(void)k;return opts[5]?"a":"";}
struct monst*shop_keeper(char room){return room?&victim:0;}
boolean costly_spot(coordxy x,coordxy y){(void)y;return opts[5]&&x<=10;}
boolean closed_door(coordxy x,coordxy y){return levl[x][y].typ==DOOR;}
char lowc(char c){return c>='A'&&c<='Z'?c+('a'-'A'):c;}
int strncmpi(const char*a,const char*b,int n){while(n--&&*a&&lowc(*a)==lowc(*b))a++,b++;return (unsigned char)lowc(*a)-(unsigned char)lowc(*b);}
char*strstri(const char*a,const char*b){size_t n=strlen(b);for(;*a;a++)if(!strncmpi(a,b,n))return(char*)a;return 0;}
int dist2(coordxy x,coordxy y,coordxy xx,coordxy yy){return(x-xx)*(x-xx)+(y-yy)*(y-yy);}
int zap_over_floor(coordxy x,coordxy y,int t,boolean*shop,boolean h,short w){logmsg("zap:%d:%d:%d:%d:%d;",x,y,t,h,w);if(opts[6])*shop=TRUE;return 0;}
int destroy_items(struct monst*m,int typ,int dam){if(opts[15]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}logmsg("items:%d:%d:%d;",m==&gy.youmonst,typ,dam);return opts[7];}
boolean burnarmor(struct monst*m){logmsg("armor:%d;",m==&gy.youmonst);return FALSE;}
int resist(struct monst*m,char olet,int dam,int tell){(void)m;logmsg("resist:%d:%d:%d;",olet,dam,tell);return opts[8];}
void mondead(struct monst*m){logmsg("mondead;");m->mhp=0;svl.level.monsters[m->mx][m->my]=0;}
void xkilled(struct monst*m,int f){logmsg("xkilled:%d;",f);m->mhp=0;svl.level.monsters[m->mx][m->my]=0;}
void monkilled(struct monst*m,const char*s,int a){logmsg("monkilled:%s:%d;",s,a);m->mhp=0;svl.level.monsters[m->mx][m->my]=0;}
void setmangry(struct monst*m,boolean b){logmsg("angry:%d;",b);m->mpeaceful=0;}
void end_burn(struct obj*o,boolean b){logmsg("endburn:%d;",b);o->lamplit=0;}
void obj_extract_self(struct obj*o){logmsg("extract:%ld;",o-nodes);if(o->where==OBJ_FLOOR){struct obj**p=&svl.level.objects[o->ox][o->oy];while(*p&&*p!=o)p=&(*p)->nexthere;if(*p)*p=o->nexthere;}o->where=OBJ_FREE;o->nexthere=0;}
void place_object(struct obj*o,coordxy x,coordxy y){logmsg("place:%ld:%d:%d;",o-nodes,x,y);o->ox=x;o->oy=y;o->where=OBJ_FLOOR;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;}
struct obj*splitobj(struct obj*o,long q){struct obj*n=&nodes[node_count++];*n=*o;o->quan-=q;n->quan=q;logmsg("split:%ld:%ld;",o-nodes,q);return n;}
struct obj*sobj_at(int typ,coordxy x,coordxy y){struct obj*o;for(o=svl.level.objects[x][y];o;o=o->nexthere)if(o->otyp==typ)return o;return 0;}
struct trap*t_at(coordxy x,coordxy y){return opts[9]&&fixture_trap.tx==x&&fixture_trap.ty==y?&fixture_trap:0;}
boolean ohitmon(struct monst*m,struct obj*o,int n,boolean b){(void)m;(void)o;logmsg("ohit:%d:%d;",n,b);return opts[10];}
int thitu(int hit,int dam,struct obj**o,const char*s){(void)s;logmsg("thitu:%d:%d;",hit,dam);if(opts[11])*o=0;return opts[12];}
int breaks(struct obj*o,coordxy x,coordxy y){(void)o;logmsg("breaks:%d:%d;",x,y);return opts[13];}
boolean flooreffects(struct obj*o,coordxy x,coordxy y,const char*s){(void)o;logmsg("floor:%d:%d:%s;",x,y,s);return opts[14];}
void fracture_rock(struct obj*o){logmsg("fracture;");o->otyp=ROCK;}
boolean break_statue(struct obj*o){logmsg("statue;");o->otyp=ROCK;return TRUE;}
boolean hideunder(struct monst*m){(void)m;logmsg("hideunder;");return TRUE;}
static void delay(void){logmsg("delay;");}
boolean sticks(struct permonst * a){(void)a;logmsg("sticks;");return 0;}
void map_invisible(coordxy a,coordxy b){logmsg("map:%d:%d;",a,b);}
boolean unmap_invisible(coordxy a,coordxy b){logmsg("unmap:%d:%d;",a,b);return 0;}
void tmp_at(coordxy a,coordxy b){logmsg("tmp:%d:%d;",a,b);}
void curs_on_u(void){logmsg("curs_on_u;");}
void show_glyph(coordxy a,coordxy b,int c){logmsg("glyph:%d:%d:%d;",a,b,c);}
void seemimic(struct monst * a){(void)a;logmsg("seemimic;");}
void ignite_items(struct obj * a){logmsg("ignite:%ld;",a?a-nodes:-1L);}
void golemeffects(struct monst * a,int b,int c){logmsg("golem:%d:%d:%d;",a==&gy.youmonst,b,c);}
void burn_away_slime(void){logmsg("burn_away_slime;");}
void ugolemeffects(int a,int b){logmsg("ugolem:%d:%d;",a,b);}
void monstseesu(unsigned long a){logmsg("seesu:%lu;",a);}
unsigned long cvt_adtyp_to_mseenres(uchar a){logmsg("seenres:%u;",a);return 1UL<<(a&31);}
void monstunseesu(unsigned long a){logmsg("unseesu:%lu;",a);}
void rehumanize(void){logmsg("rehumanize;");}
void done(int a){logmsg("done:%d;",a);}
void exercise(int a,boolean b){logmsg("exercise:%d:%d;",a,b);}
void pay_for_damage(const char * a,boolean b){logmsg("pay:%s:%d;",a,b);}
void wake_nearto(coordxy a,coordxy b,int c){logmsg("wake:%d:%d:%d;",a,b,c);}
void credit_report(struct monst * a,int b,boolean c){logmsg("credit:%d:%d:%d;",a==&victim,b,c);}
void unpunish(void){logmsg("unpunish;");}
void deltrap(struct trap * a){(void)a;logmsg("deltrap;");}
void newsym(coordxy a,coordxy b){logmsg("newsym:%d:%d;",a,b);}
void nomul(int a){logmsg("nomul:%d;",a);gm.multi=a;}
int dmgval(struct obj * a,struct monst * b){logmsg("dmgval:%ld:%d;",a-nodes,b==&gy.youmonst);return 7;}
void stop_occupation(void){logmsg("stop_occupation;");}
void addtobill(struct obj * a,boolean b,boolean c,boolean d){logmsg("bill:%ld:%d:%d:%d;",a-nodes,b,c,d);}
void stackobj(struct obj * a){logmsg("stack:%ld;",a-nodes);}
void maybe_unhide_at(coordxy a,coordxy b){logmsg("unhide:%d:%d;",a,b);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/explode.c"
#else
extern int teleport_explode_test_explosionmask(struct monst*,uchar,char);
extern void teleport_explode_test_engulfer_explosion_msg(uchar,char);
#define explosionmask teleport_explode_test_explosionmask
#define engulfer_explosion_msg teleport_explode_test_engulfer_explosion_msg
#endif
#include "tu-explode-layout.h"
void probe_reset(unsigned seed){int x,y;if(growth)free(growth);growth=0;memset(cells,0,sizeof cells);for(y=0;y<ROWNO;y++)rows[y]=cells[y];gv.viz_array=rows;memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&svk,0,sizeof svk);memset(&svc,0,sizeof svc);memset(&gi,0,sizeof gi);memset(&gm,0,sizeof gm);memset(&gb,0,sizeof gb);memset(&gt,0,sizeof gt);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(nodes,0,sizeof nodes);memset(&victim,0,sizeof victim);memset(&species,0,sizeof species);memset(&attack,0,sizeof attack);memset(opts,0,sizeof opts);memset(&gu,0,sizeof gu);fixture_trap.tx=fixture_trap.ty=10;fixture_trap.ttyp=STATUE_TRAP;u.ux=u.uy=10;u.uhp=u.mh=200;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&species;victim.data=&species;victim.mx=11;victim.my=10;victim.mhp=100;u.ustuck=&victim;species.mlevel=4;species.msize=MZ_MEDIUM;flags.verbose=1;windowprocs.win_delay_output=delay;rng_state=seed;rng_count=0;node_count=1;nodes[0].otyp=POT_OIL;nodes[0].quan=1;nodes[0].ox=nodes[0].oy=10;nodes[0].lamplit=1;nodes[0].owt=40;uball=uchain=0;tracebuf[0]=caller[0]=0;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;}
void probe_option(int k,long value){switch(k){case 100:u.uswallow=value;break;case 101:svl.level.monsters[victim.mx][victim.my]=value?&victim:0;break;case 102:flags.sparkle=value;break;case 103:svc.context.mon_moving=value;break;case 104:u.uhp=value;break;case 105:victim.mhp=value;break;case 106:nodes[0].quan=value;break;case 107:nodes[0].otyp=value;break;case 108:nodes[0].owt=value;break;case 109:nodes[0].odiluted=value;break;case 110:nodes[0].lamplit=value;break;case 111:attack.adtyp=value;break;case 112:attack.damn=value;break;case 113:attack.damd=value;break;case 114:u.uundetected=value;break;case 115:species.mflags1=value;break;case 116:species.mflags2=value;break;case 117:species.msize=value;break;case 118:u.ustuck=value?&victim:0;break;case 119:victim.mtrapped=value;break;case 120:nodes[0].spe=value;break;case 121:u.usteed=value?&victim:0;break;case 122:flags.verbose=value;break;case 123:u.umonnum=value?PM_RED_DRAGON:PM_HUMAN;break;case 124:gm.multi=value;break;case 125:gu.urole.mnum=value;break;case 126:species.mlevel=value;break;default:opts[k]=value;break;}}
void probe_prop(int p,long v){u.uprops[p].intrinsic=v;}
void probe_cell(int x,int y,int typ,int visible){levl[x][y].typ=typ;cells[y][x]=visible?IN_SIGHT:0;}
long probe_action(int op,int a,int b,int c,int d,int e,int f){switch(op){case 0:return explosionmask(a?&gy.youmonst:&victim,b,c);case 1:engulfer_explosion_msg(a,b);break;case 2:explode(a,b,c,d,e,f);break;case 3:return scatter(a,b,c,d,e?&nodes[0]:0);case 4:splatter_burning_oil(a,b,c);break;case 5:explode_oil(&nodes[0],a,b);break;case 6:return adtyp_to_expltype(a);case 7:mon_explodes(&victim,&attack);break;case 8:place_object(&nodes[0],a,b);break;}return 0;}
const char*probe_trace(void){return tracebuf;}
const char*probe_snapshot(void){int i;char*p=snapshotbuf;p+=sprintf(p,"hero:%d:%d:%d;victim:%d:%d:%d;kill:%d:%s;rng:%u:%d;objects:%d;",u.uhp,u.mh,disp.botl,victim.mhp,victim.mpeaceful,victim.mtrapped,svk.killer.format,svk.killer.name,rng_state,rng_count,node_count);for(i=0;i<node_count;i++)p+=sprintf(p,"o%d:%d:%d:%d:%ld:%d:%d:%d;",i,nodes[i].ox,nodes[i].oy,nodes[i].otyp,nodes[i].quan,nodes[i].lamplit,nodes[i].odiluted,nodes[i].how_lost);return snapshotbuf;}
void*probe_pointer(int id){switch(id){case 0:return &victim;case 1:return &attack;case 2:return &nodes[0];default:return &gy.youmonst;}}
uintptr_t probe_stack(void){return(uintptr_t)emscripten_stack_get_current();}
