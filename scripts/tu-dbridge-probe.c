/* External-world fixtures only; all drawbridge/entity decisions stay in the original TU. */
#include "hack.h"
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
struct you u;__typeof__(go)go;__typeof__(gy)gy;__typeof__(svl)svl;__typeof__(svd)svd;__typeof__(svk)svk;__typeof__(svc)svc;__typeof__(gm)gm;__typeof__(gv)gv;__typeof__(iflags)iflags;
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
static struct monst monsters[4];static struct obj*objects_owned[32];static int nobj,opts[40],rolls[4096],nr,ri;static unsigned seed;static char tracebuf[262144],statebuf[262144],caller[128],verb[64],output[128];static const char*last_phrase;static struct trap traps[2];static coordxy xy[2];static seenV vision[ROWNO][COLNO],*rows[ROWNO];static void*growth;
static void append(const char*f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
static int mid(struct monst*m){if(!m)return-1;if(m==&gy.youmonst)return 4;return m>=monsters&&m<monsters+4?(int)(m-monsters):99;}
static int oid(struct obj*o){int i;if(!o)return-1;for(i=0;i<nobj;i++)if(objects_owned[i]==o)return i;return 99;}
static void callback(int k){if(opts[30]==k){opts[30]=0;append("nested:%d;",is_pool(5,5));}if(opts[31]==k&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();append("grow:%d;",k);}}
void panic(const char*f,...){abort();}
#define MSG(fn) void fn(const char*f,...){va_list a;append(#fn ":");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);append(";");}
MSG(impossible) MSG(pline) MSG(pline_The) MSG(You) MSG(You_hear) MSG(You_see)
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char*f,int l,const char*fn){snprintf(caller,sizeof caller,"%s:%d",fn,l);}static int draw(int n){int v;if(n<=0)abort();seed=seed*1664525U+1013904223U;v=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;return v;}int(rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);callback(1);return v;}int(rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);callback(1);return v;}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
int canseemon(struct monst*m){append("see:%d;",mid(m));return opts[1];}int sensemon(struct monst*m){return opts[2];}int pronoun_gender(struct monst*m,unsigned f){return opts[3];}char*mon_nam(struct monst*m){return "fixture monster";}char*Monnam(struct monst*m){return "Fixture monster";}char*vtense(const char*s,const char*v){static char b[4][80];static unsigned i;char*p=b[i++%4];if(!strcmp(v,"are"))strcpy(p,"is");else if(!strcmp(v,"have"))strcpy(p,"has");else snprintf(p,80,"%ss",v);return p;}
const char*hliquid(const char*s){return s;}boolean unconscious(void){append("unconscious;");return opts[4];}boolean is_fainted(void){append("fainted;");return opts[5];}boolean debugcore(const char*f,boolean w){const char*p=strrchr(f,'/');append("debug:%s:%d;",p?p+1:f,w);return opts[6];}
boolean drown(void){append("drown;");if(opts[7]){u.ux=14;u.uy=14;}callback(2);return FALSE;}boolean lava_effects(void){append("lava;");if(opts[7]){u.ux=14;u.uy=14;}callback(3);return FALSE;}void done(int n){append("done:%d:%d:%s;",n,svk.killer.format,svk.killer.name);callback(4);}boolean enexto(coord*p,coordxy x,coordxy y,struct permonst*m){append("enexto:%d:%d:%d;",x,y,m->pmidx);p->x=14;p->y=14;callback(5);return !opts[8];}void teleds(coordxy x,coordxy y,int f){append("tele:%d:%d:%d;",x,y,f);u.ux=x;u.uy=y;callback(6);}
static void killmon(struct monst*m){if(opts[9])opts[9]--;else{m->mhp=0;remove_monster(m->mx,m->my);}callback(7);}void monkilled(struct monst*m,const char*s,int a){append("monkilled:%d:%s:%d;",mid(m),s?s:"<NULL>",a);killmon(m);}void xkilled(struct monst*m,int f){append("xkilled:%d:%d;",mid(m),f);killmon(m);}
void place_monster(struct monst*m,coordxy x,coordxy y){append("place:%d:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;svl.level.monsters[x][y]=m;callback(8);}void update_monster_region(struct monst*m){append("region:%d;",mid(m));callback(9);}void spoteffects(boolean b){append("spot:%d;",b);callback(10);}int minliquid(struct monst*m){append("minliquid:%d;",mid(m));callback(11);return 0;}
boolean revive_nasty(coordxy x,coordxy y,const char*s){append("revive:%d:%d:%s;",x,y,s?s:"<NULL>");callback(12);return FALSE;}void delallobj(coordxy x,coordxy y){append("delobjs:%d:%d;",x,y);svl.level.objects[x][y]=0;callback(13);}
struct trap*t_at(coordxy x,coordxy y){int i;append("trap:%d:%d;",x,y);for(i=0;i<2;i++)if(opts[10+i]&&traps[i].tx==x&&traps[i].ty==y)return &traps[i];return 0;}void deltrap(struct trap*t){int i=(int)(t-traps);append("deltrap:%d;",i);opts[10+i]=0;callback(14);}void del_engr_at(coordxy x,coordxy y){append("engrave:%d:%d;",x,y);callback(15);}void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);callback(16);}void block_point(int x,int y){append("block:%d:%d;",x,y);callback(17);}void unblock_point(int x,int y){append("unblock:%d:%d;",x,y);callback(18);}void wake_nearto(coordxy x,coordxy y,int n){append("wake:%d:%d:%d;",x,y,n);callback(19);}int does_block(int x,int y,struct rm*r){append("doesblock:%d:%d;",x,y);return opts[12];}void vision_recalc(int n){append("vision:%d;",n);callback(20);}
struct obj*sobj_at(int t,coordxy x,coordxy y){struct obj*o;for(o=svl.level.objects[x][y];o;o=o->nexthere)if(o->otyp==t)return o;return 0;}void obj_extract_self(struct obj*o){struct obj**p=&svl.level.objects[o->ox][o->oy];append("extract:%d;",oid(o));while(*p&&*p!=o)p=&(*p)->nexthere;if(*p)*p=o->nexthere;o->nexthere=0;o->where=OBJ_FREE;}boolean flooreffects(struct obj*o,coordxy x,coordxy y,const char*s){append("floor:%d:%d:%d:%s;",oid(o),x,y,s);callback(21);return FALSE;}
struct obj*mksobj_at(int t,coordxy x,coordxy y,boolean init,boolean art){struct obj*o;if(nobj>=32)abort();o=calloc(1,sizeof*o);objects_owned[nobj++]=o;o->otyp=t;o->ox=x;o->oy=y;o->where=OBJ_FLOOR;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;append("mkobj:%d:%d:%d:%d:%d:%d;",oid(o),t,x,y,init,art);callback(22);return o;}long scatter(coordxy x,coordxy y,int n,unsigned f,struct obj*o){append("scatter:%d:%d:%d:%u:%d;",x,y,n,f,oid(o));callback(23);return 0;}

#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/dbridge.c"
#else
extern void teleport_dbridge_test_get_wall_for_db(coordxy*,coordxy*);
#define get_wall_for_db teleport_dbridge_test_get_wall_for_db
extern struct entity* teleport_dbridge_test_e_at(coordxy,coordxy);
#define e_at teleport_dbridge_test_e_at
extern void teleport_dbridge_test_m_to_e(struct monst*,coordxy,coordxy,struct entity*);
#define m_to_e teleport_dbridge_test_m_to_e
extern void teleport_dbridge_test_u_to_e(struct entity*);
#define u_to_e teleport_dbridge_test_u_to_e
extern void teleport_dbridge_test_set_entity(coordxy,coordxy,struct entity*);
#define set_entity teleport_dbridge_test_set_entity
extern const char* teleport_dbridge_test_e_nam(struct entity*);
#define e_nam teleport_dbridge_test_e_nam
extern const char* teleport_dbridge_test_E_phrase(struct entity*,const char*);
#define E_phrase teleport_dbridge_test_E_phrase
extern boolean teleport_dbridge_test_e_survives_at(struct entity*,coordxy,coordxy);
#define e_survives_at teleport_dbridge_test_e_survives_at
extern void teleport_dbridge_test_e_died(struct entity*,int,int);
#define e_died teleport_dbridge_test_e_died
extern boolean teleport_dbridge_test_automiss(struct entity*);
#define automiss teleport_dbridge_test_automiss
extern boolean teleport_dbridge_test_e_missed(struct entity*,boolean);
#define e_missed teleport_dbridge_test_e_missed
extern boolean teleport_dbridge_test_e_jumps(struct entity*);
#define e_jumps teleport_dbridge_test_e_jumps
extern void teleport_dbridge_test_do_entity(struct entity*);
#define do_entity teleport_dbridge_test_do_entity
extern void teleport_dbridge_test_nokiller(void);
#define nokiller teleport_dbridge_test_nokiller
#endif
#include "tu-dbridge-layout.h"
void probe_reset(unsigned s){int i,x,y;for(i=0;i<nobj;i++)free(objects_owned[i]);nobj=0;if(growth)free(growth);growth=0;memset(&u,0,sizeof u);memset(&go,0,sizeof go);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&svd,0,sizeof svd);memset(&svk,0,sizeof svk);memset(&svc,0,sizeof svc);memset(&gm,0,sizeof gm);memset(&gv,0,sizeof gv);memset(&iflags,0,sizeof iflags);memset(monsters,0,sizeof monsters);memset(opts,0,sizeof opts);objects_globals_init();monst_globals_init();u.ux=u.uy=5;u.umonnum=u.umonster=PM_HUMAN;u.uz.dnum=1;u.uz.dlevel=2;stronghold_level.dnum=3;stronghold_level.dlevel=4;juiblex_level.dnum=6;juiblex_level.dlevel=7;gy.youmonst.data=&mons[PM_HUMAN];for(i=0;i<4;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].mhp=20;monsters[i].mcanmove=1;}for(y=0;y<ROWNO;y++){rows[y]=vision[y];for(x=0;x<COLNO;x++){vision[y][x]=IN_SIGHT|COULD_SEE;levl[x][y].typ=ROOM;levl[x][y].glyph=700+x*ROWNO+y;}}gv.viz_array=rows;opts[0]=opts[1]=1;seed=s;ri=nr=0;xy[0]=xy[1]=10;verb[0]=output[0]=tracebuf[0]=caller[0]=0;last_phrase=0;}
void probe_option(int k,int v){int x,y;opts[k]=v;if(k==13)for(y=0;y<ROWNO;y++)for(x=0;x<COLNO;x++)vision[y][x]=v;}
int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nr=n;ri=0;}int probe_rng_count(void){return ri;}unsigned probe_rng_state(void){return seed;}const char*probe_trace(void){return tracebuf;}
void probe_set_monster(int i,int k,long v){struct monst*m=&monsters[i];switch(k){case 0:m->data=&mons[v];break;case 1:m->mx=v;break;case 2:m->my=v;break;case 3:m->wormno=v;break;case 4:m->msleeping=v;break;case 5:m->mcanmove=v;break;case 6:m->mconf=v;break;case 7:m->mstun=v;break;case 8:m->mhp=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:gy.youmonst.data=&mons[v];u.umonnum=v;break;case 3:u.uinwater=v;break;case 4:gm.multi=v;break;case 5:svc.context.mon_moving=v;break;case 6:stronghold_level=u.uz;break;case 7:juiblex_level=u.uz;break;case 8:u.uroleplay.deaf=v;break;case 9:svk.killer.format=v;strcpy(svk.killer.name,"fixture killer");break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_terrain(int x,int y,int k,int v){switch(k){case 0:levl[x][y].typ=v;break;case 1:levl[x][y].drawbridgemask=v;break;case 2:levl[x][y].doormask=v;break;case 3:levl[x][y].horizontal=v;break;case 4:levl[x][y].wall_info=v;break;case 5:levl[x][y].icedpool=v;break;}}
void probe_add_monster(int i,int x,int y){monsters[i].mx=x;monsters[i].my=y;svl.level.monsters[x][y]=&monsters[i];}
void probe_add_object(int t,int x,int y){mksobj_at(t,x,y,1,0);}
void probe_trap(int i,int x,int y){traps[i].tx=x;traps[i].ty=y;traps[i].ttyp=PIT;opts[10+i]=1;}
void probe_entity(int i,int kind,int x,int y){if(kind==4)u_to_e(&go.occupants[i]);else m_to_e(kind<0?0:&monsters[kind],x,y,&go.occupants[i]);}
long probe_action(int op,int a,int b,int c,int d){struct entity*e=&go.occupants[a>=0&&a<2?a:0];switch(op){case 0:return is_waterwall(a,b);case 1:return is_pool(a,b);case 2:return is_lava(a,b);case 3:return is_pool_or_lava(a,b);case 4:return is_ice(a,b);case 5:return is_moat(a,b);case 6:return db_under_typ(a);case 7:return is_drawbridge_wall(a,b);case 8:return is_db_wall(a,b);case 9:xy[0]=a;xy[1]=b;return find_drawbridge(&xy[0],&xy[opts[14]?0:1]);case 10:xy[0]=a;xy[1]=b;get_wall_for_db(&xy[0],&xy[opts[14]?0:1]);break;case 11:return create_drawbridge(a,b,c,d);case 12:{struct entity*f=e_at(a,b);return f?(f-go.occupants):-1;}case 13:m_to_e(b<0?0:&monsters[b],c,d,e);break;case 14:u_to_e(e);break;case 15:set_entity(b,c,e);break;case 16:strcpy(output,e_nam(e));break;case 17:last_phrase=E_phrase(e,b?verb:0);strcpy(output,last_phrase);break;case 18:return e_survives_at(e,b,c);case 19:e_died(e,b,c);break;case 20:return automiss(e);case 21:return e_missed(e,b);case 22:return e_jumps(e);case 23:do_entity(e);break;case 24:nokiller();break;case 25:close_drawbridge(a,b);break;case 26:open_drawbridge(a,b);break;case 27:destroy_drawbridge(a,b);break;}return 0;}
void*probe_pointer(int k,int i){if(k==0)return &go.occupants[i];if(k==1)return &monsters[i];if(k==2)return output;if(k==3)return xy;if(k==4)return(void*)last_phrase;if(k==5)return verb;return &u;}
const char*probe_snapshot(void){char*p=statebuf;int i,j,x,y;p+=sprintf(p,"u:%d:%d:%d:%d;kill:%d:%s;xy:%d:%d;out:%s;events:%d:%d;traps:%d:%d;props:",u.ux,u.uy,u.uevent.uopened_dbridge,u.uevent.uheard_tune,svk.killer.format,svk.killer.name,xy[0],xy[1],output,u.uevent.uopened_dbridge,u.uevent.uheard_tune,opts[10],opts[11]);for(i=0;i<sizeof u.uprops;i++)p+=sprintf(p,"%02x",((unsigned char*)u.uprops)[i]);for(i=0;i<2;i++)p+=sprintf(p,";e:%d:%d:%d:%d",mid(go.occupants[i].emon),go.occupants[i].edata?go.occupants[i].edata->pmidx:-1,go.occupants[i].ex,go.occupants[i].ey);for(i=0;i<4;i++)p+=sprintf(p,";m:%d:%d:%d:%d:%d:%d:%d:%d",monsters[i].data->pmidx,monsters[i].mx,monsters[i].my,monsters[i].mhp,monsters[i].msleeping,monsters[i].mcanmove,monsters[i].mconf,monsters[i].mstun);for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){p+=sprintf(p,";g:");for(j=0;j<sizeof(struct rm);j++)p+=sprintf(p,"%02x",((unsigned char*)&levl[x][y])[j]);p+=sprintf(p,":%d:%d",mid(svl.level.monsters[x][y]),oid(svl.level.objects[x][y]));}return statebuf;}
uintptr_t probe_stack(void){return(uintptr_t)emscripten_stack_get_current();}
