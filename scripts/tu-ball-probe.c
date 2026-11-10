/* Differential boundary fixtures; ball.c algorithms remain in the original TU. */
#include "hack.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
__typeof__(gi) gi; __typeof__(gv) gv; __typeof__(svl) svl; __typeof__(svd) svd;
__typeof__(flags) flags; struct you u;
struct obj *uball,*uchain,*uwep,*uswapwep,*uquiver,*uarmh;
static struct obj *nodes[12]; static struct monst victim; static struct trap trap;
static int opts[40],rolls[4096],nr,ri; static struct {int control;coordxy coords[4];boolean delay;unsigned char padding[19];} outputs; static unsigned seed;
static char tracebuf[262144],snapshotbuf[262144],caller[128]; static void *growth;
static void logmsg(const char*f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
static int id(struct obj *o){int i;if(!o)return -1;for(i=0;i<12;i++)if(nodes[i]==o)return i;return 99;}
static void callback(int k){if(opts[30]==k){opts[30]=0;bc_sanity_check();logmsg("nested;");}if(opts[31]==k&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("grow:%d;",k);}}
void panic(const char *f,...){abort();} void impossible(const char*f,...){va_list a;logmsg("impossible:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
void paniclog(const char*a,const char*b){logmsg("paniclog:%s:%s;",a,b);}
void pline(const char*f,...){va_list a;logmsg("msg:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
void pline_The(const char*f,...){va_list a;logmsg("The:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
void You(const char*f,...){va_list a;logmsg("You:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
void Your(const char*f,...){va_list a;logmsg("Your:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
void You_feel(const char*f,...){va_list a;logmsg("feel:");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);logmsg(";");}
boolean rng_log_enabled(void){return opts[0];} void rng_log_set_caller(const char*f,int l,const char*n){snprintf(caller,sizeof caller,"%s:%d",n,l);}
static int draw(int n){int v;if(n<=0)abort();seed=seed*1664525U+1013904223U;v=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;if(opts[32]&&ri==opts[33]){u.uprops[HALF_PHDAM].intrinsic=opts[32]>0;opts[32]=0;logmsg("fliphalf;");}logmsg("rng:%d:%d@%s;",n,v,caller);return v;}
int (rn2)(int n){return draw(n);} int (rnd)(int n){return draw(n)+1;}
int welded(struct obj*o){logmsg("welded:%d;",id(o));return opts[1];}boolean hard_helmet(struct obj*o){logmsg("helmet:%d;",id(o));return opts[2];}
void setuwep(struct obj*o){logmsg("setuwep:%d;",id(o));uwep=o;callback(1);}void setuswapwep(struct obj*o){logmsg("swap:%d;",id(o));uswapwep=o;}void setuqwep(struct obj*o){logmsg("quiver:%d;",id(o));uquiver=o;}
void freeinv(struct obj*o){struct obj**p=&gi.invent;logmsg("freeinv:%d;",id(o));while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;o->nobj=0;o->where=OBJ_FREE;callback(2);}void encumber_msg(void){logmsg("encumber;");}
void remove_object(struct obj*o){struct obj **p=&svl.level.objects[o->ox][o->oy];logmsg("remove:%d;",id(o));while(*p&&*p!=o)p=&(*p)->nexthere;if(*p)*p=o->nexthere;p=&fobj;while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;o->nobj=o->nexthere=0;o->where=OBJ_FREE;callback(3);}
void obj_extract_self(struct obj*o){logmsg("extract:%d;",id(o));if(o->where==OBJ_FLOOR)remove_object(o);else if(o->where==OBJ_INVENT)freeinv(o);}
void place_object(struct obj*o,coordxy x,coordxy y){logmsg("place:%d:%d:%d;",id(o),x,y);o->ox=x;o->oy=y;o->where=OBJ_FLOOR;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;o->nobj=fobj;fobj=o;callback(4);}
void newsym(coordxy x,coordxy y){struct obj*o=svl.level.objects[x][y];logmsg("newsym:%d:%d;",x,y);levl[x][y].glyph=o?1000+id(o):x*COLNO+y;callback(5);}
void movobj(struct obj*o,coordxy x,coordxy y){logmsg("mov:%d:%d:%d;",id(o),x,y);remove_object(o);place_object(o,x,y);newsym(x,y);}
void map_object(struct obj*o,int k){logmsg("map:%d:%d;",id(o),k);levl[o->ox][o->oy].glyph=1000+id(o);}void maybe_unhide_at(coordxy x,coordxy y){logmsg("unhide:%d:%d;",x,y);}
boolean flooreffects(struct obj*o,coordxy x,coordxy y,const char*s){logmsg("floor:%d:%d:%d:%s;",id(o),x,y,s);callback(6);return FALSE;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean is_pool(coordxy x,coordxy y){return levl[x][y].typ==POOL||levl[x][y].typ==MOAT;}
struct trap*t_at(coordxy x,coordxy y){logmsg("trap:%d:%d;",x,y);return opts[4]&&trap.tx==x&&trap.ty==y?&trap:0;}
void deltrap(struct trap*t){logmsg("deltrap;");opts[4]=0;}int near_capacity(void){logmsg("capacity;");return opts[3];}int weight_cap(void){return opts[5];}
void nomul(int n){logmsg("nomul:%d;",n);}void spoteffects(boolean b){logmsg("spot:%d;",b);callback(7);}void cls(void){logmsg("cls;");}
int find_mac(struct monst*m){logmsg("mac;");return opts[6];}int omon_adj(struct monst*m,struct obj*o,boolean b){logmsg("omon:%d:%d;",id(o),b);return opts[7];}
boolean hmon(struct monst*m,struct obj*o,int a,int b){logmsg("hit:%d:%d:%d;",id(o),a,b);if(opts[8])svl.level.monsters[m->mx][m->my]=0;callback(8);return TRUE;}void miss(const char*s,struct monst*m){logmsg("miss:%s;",s);}
void losehp(int n,const char*s,schar k){logmsg("hp:%d:%s:%d;",n,s,k);u.uhp-=n;callback(9);}void exercise(int n,boolean b){logmsg("exercise:%d:%d;",n,b);}
const char*body_part(int n){return n==HEAD?"head":"leg";}const char*hliquid(const char*s){return s;}
char*xname(struct obj*o){return "iron ball";}char*yname(struct obj*o){return id(o)==0?"your iron ball":"your item";}char*Yname2(struct obj*o){return "Your helmet";}char*otense(struct obj*o,const char*s){return o->quan==1?"falls":"fall";}char*safe_typename(int n){return "fixture type";}
void reset_utrap(boolean b){logmsg("resettrap:%d;",b);u.utrap=0;}void fill_pit(coordxy x,coordxy y){logmsg("fillpit:%d:%d;",x,y);}void set_wounded_legs(long s,int n){logmsg("legs:%ld:%d;",s,n);u.uprops[WOUNDED_LEGS].intrinsic=n;}
boolean canletgo(struct obj*o,const char*s){logmsg("letgo:%d;",id(o));return !opts[9];}void setnotworn(struct obj*o){logmsg("notworn:%d;",id(o));o->owornmask=0;}void hitfloor(struct obj*o,boolean b){logmsg("hitfloor:%d:%d;",id(o),b);place_object(o,u.ux,u.uy);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/ball.c"
#else
extern int teleport_ball_test_order(void);extern void teleport_ball_test_litter(void),teleport_ball_test_place(void),teleport_ball_test_unplace(void);extern boolean teleport_ball_test_restriction(int);extern int teleport_ball_test_state(int,int);
#define bc_order() teleport_ball_test_order()
#define litter teleport_ball_test_litter
#define placebc_core teleport_ball_test_place
#define unplacebc_core teleport_ball_test_unplace
#define check_restriction teleport_ball_test_restriction
#endif
#include "tu-ball-layout.h"
int probe_state(int set,int v){
#ifdef TELEPORT_REFERENCE_TU
if(set)bcrestriction=v;return bcrestriction;
#else
return teleport_ball_test_state(set,v);
#endif
}
void probe_reset(unsigned s){int i,x,y;for(i=0;i<12;i++){if(nodes[i])free(nodes[i]);nodes[i]=calloc(1,sizeof(struct obj));nodes[i]->o_id=i+1;nodes[i]->otyp=i?IRON_CHAIN:HEAVY_IRON_BALL;nodes[i]->quan=1;nodes[i]->owt=100;nodes[i]->owornmask=i?W_CHAIN:W_BALL;}if(growth)free(growth);growth=0;memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&gi,0,sizeof gi);memset(&flags,0,sizeof flags);memset(&gv,0,sizeof gv);memset(&svd,0,sizeof svd);memset(&victim,0,sizeof victim);memset(&trap,0,sizeof trap);memset(opts,0,sizeof opts);memset(&outputs,0x55,sizeof outputs);objects_globals_init();monst_globals_init();uball=nodes[0];uchain=nodes[1];uwep=uswapwep=uquiver=uarmh=0;u.ux=u.ux0=10;u.uy=u.uy0=10;u.uz.dnum=1;u.uz.dlevel=2;water_level.dnum=9;water_level.dlevel=9;u.uhp=100;u.dx=1;u.dy=0;flags.verbose=1;opts[0]=1;opts[5]=200;seed=s;ri=nr=0;probe_state(1,0);for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;levl[x][y].glyph=x*COLNO+y;}tracebuf[0]=caller[0]=0;}
void probe_option(int k,int v){opts[k]=v;}int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nr=n;ri=0;}int probe_rng_count(void){return ri;}unsigned probe_rng_state(void){return seed;}const char*probe_trace(void){return tracebuf;}
void probe_object(int i,int k,long v){struct obj*o=nodes[i];switch(k){case 0:o->ox=v;break;case 1:o->oy=v;break;case 2:o->where=v;break;case 3:o->owornmask=v;break;case 4:o->quan=v;break;case 5:o->owt=v;break;case 6:o->otyp=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.bc_order=v;break;case 3:u.bc_felt=v;break;case 4:u.bglyph=v;break;case 5:u.cglyph=v;break;case 6:u.uswallow=v;break;case 7:u.utrap=v;break;case 8:u.utraptype=v;break;case 9:u.dx=v;break;case 10:u.dy=v;break;case 11:u.uluck=v;break;case 12:water_level=u.uz;break;case 13:trap.ttyp=v;opts[4]=1;trap.tx=u.ux;trap.ty=u.uy;break;case 14:victim.mx=v;break;case 15:victim.my=v;svl.level.monsters[victim.mx][victim.my]=&victim;break;case 16:u.usteed=v?&victim:0;break;case 17:water_level.dnum=water_level.dlevel=0;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_terrain(int x,int y,int k,int v){if(k==0)levl[x][y].typ=v;else if(k==1)levl[x][y].glyph=v;else levl[x][y].doormask=v;}
void probe_equip(int k,int i){struct obj*o=i<0?0:nodes[i];switch(k){case 0:uball=o;break;case 1:uchain=o;break;case 2:uwep=o;break;case 3:uswapwep=o;break;case 4:uquiver=o;break;case 5:uarmh=o;break;}}
void probe_add(int i,int where,int x,int y){struct obj*o=nodes[i];if(where==OBJ_FLOOR)place_object(o,x,y);else if(where==OBJ_INVENT){o->where=where;o->nobj=gi.invent;gi.invent=o;}else o->where=where;}
void probe_setup_floor(int order,int bx,int by,int cx,int cy){if(order==2){place_object(uchain,cx,cy);place_object(uball,bx,by);}else{place_object(uball,bx,by);place_object(uchain,cx,cy);}}
long probe_action(int op,int a,int b,int c,int d,int e,int f){switch(op){case 0:ballrelease(a);break;case 1:ballfall();break;case 2:placebc();break;case 3:unplacebc();break;case 4:return unplacebc_and_covet_placebc();case 5:lift_covet_and_placebc(a);break;case 6:return bc_order();case 7:set_bc(a);break;case 8:move_bc(a,b,c,d,e,f);break;case 9:{coordxy *p=outputs.coords;return drag_ball(a,b,&outputs.control,&p[0],&p[opts[16]?0:1],&p[opts[16]?0:2],&p[opts[16]?0:3],&outputs.delay,c);}case 10:drop_ball(a,b);break;case 11:litter();break;case 12:drag_down();break;case 13:bc_sanity_check();break;case 14:placebc_core();break;case 15:unplacebc_core();break;case 16:return check_restriction(a);}return 0;}
void*probe_pointer(int k,int i){if(k==0)return nodes[i];if(k==1)return &u;if(k==2)return &outputs;if(k==3)return &trap;return 0;}
const char*probe_snapshot(void){char*p=snapshotbuf;int i,x,y;struct obj*o;p+=sprintf(p,"u:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;equip:%d:%d:%d:%d:%d:%d;state:%d;out:",u.ux,u.uy,u.ux0,u.uy0,u.bc_order,u.bc_felt,u.bglyph,u.cglyph,u.uhp,u.utrap,u.utraptype,gv.vision_full_recalc,id(uball),id(uchain),id(uwep),id(uswapwep),id(uquiver),id(uarmh),probe_state(0,0));for(i=0;i<sizeof outputs;i++)p+=sprintf(p,"%02x",((unsigned char*)&outputs)[i]);p+=sprintf(p,";inv:");for(o=gi.invent;o;o=o->nobj)p+=sprintf(p,"%d,",id(o));p+=sprintf(p,";floor:");for(o=fobj;o;o=o->nobj)p+=sprintf(p,"%d,",id(o));for(i=0;i<12;i++){o=nodes[i];p+=sprintf(p,";o%d:%d:%d:%d:%ld:%ld:%u:%d:%d",i,o->ox,o->oy,o->where,o->owornmask,o->quan,o->owt,id(o->nobj),id(o->nexthere));}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)p+=sprintf(p,";g:%d:%d:%d:%d:%d",levl[x][y].typ,levl[x][y].glyph,levl[x][y].doormask,id(svl.level.objects[x][y]),svl.level.monsters[x][y]!=0);p+=sprintf(p,";trap:%d:%d;props:",trap.ttyp,trap.tseen);for(i=0;i<sizeof u.uprops;i++)p+=sprintf(p,"%02x",((unsigned char*)u.uprops)[i]);return snapshotbuf;}
uintptr_t probe_stack(void){return (uintptr_t)emscripten_stack_get_current();}
