/* SP_LEV fixture: actual C Lua in BOTH modes; explicit controlled world models. */
#include "hack.h"
#include "sp_lev.h"
#include "lualib.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <emscripten.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(gx) gx;
__typeof__(gy) gy;
__typeof__(svl) svl;
__typeof__(uball) uball;
__typeof__(u) u;
__typeof__(uchain) uchain;
__typeof__(gs) gs;
__typeof__(gf) gf;
__typeof__(gm) gm;
__typeof__(head_engr) head_engr;
__typeof__(gn) gn;
__typeof__(gl) gl;
__typeof__(svn) svn;
__typeof__(gr) gr;
__typeof__(svr) svr;
__typeof__(gd) gd;
__typeof__(svd) svd;
__typeof__(gt) gt;
__typeof__(sve) sve;
__typeof__(iflags) iflags;
__typeof__(svc) svc;
__typeof__(gi) gi;
__typeof__(svi) svi;
__typeof__(mons) mons={[PM_HUMAN]={.pmidx=PM_HUMAN,.pmnames={"human","human","human"},.mlet=S_HUMAN,.mflags2=M2_HUMAN,.mmove=12}};
__typeof__(svm) svm;
__typeof__(gu) gu;
__typeof__(defsyms) defsyms={[S_room]={.sym='.',.explanation="floor"}};
__typeof__(obj_descr) obj_descr;
__typeof__(objects) objects;
__typeof__(def_monsyms) def_monsyms={[S_HUMAN]={.sym='@',.name="human"}};
__typeof__(gc) gc;
__typeof__(emptystr[0]) emptystr[1]="";
__typeof__(cg) cg={0};
static lua_State*probe_L;static monster templates_mon[8];static object templates_obj[8];static struct obj objpool[32];static struct monst monpool[16];static struct mkroom rooms_pool[8];static coord coordpool[16];static lua_Integer longcells[16];static void*ptrcells[16];static corridor corridors[8];static struct mapfragment fragments[8];static region regionpool[8];static lev_init initpool[4];static spltrap trappool[4];static room roompool[4];static room_door doorpool[4];static altar altarpool[4];static lev_region lregionpool[4];static terrain terrainpool[4];static unpacked_coord valueout[4];static _Alignas(void*) char buffers[32768];static char tracebuf[1048576];static size_t traceused;static unsigned cursor;static int result,query,rngvalue,grow,reentry,which_name,lua_fail;static jmp_buf escape;
struct block{void*p;size_t n;int live,kind;};static struct block blocks[4096];static int blockcount;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=(size_t)n;}
static uint64_t token(const void*p){uintptr_t a=(uintptr_t)p;if(!p)return 0;if(p==(void*)probe_L)return 990000;
if(a>=(uintptr_t)&buffers&&a<(uintptr_t)&buffers+sizeof buffers)return 100000+a-(uintptr_t)&buffers;
if(a>=(uintptr_t)&templates_mon&&a<(uintptr_t)&templates_mon+sizeof templates_mon)return 200000+a-(uintptr_t)&templates_mon;
if(a>=(uintptr_t)&templates_obj&&a<(uintptr_t)&templates_obj+sizeof templates_obj)return 300000+a-(uintptr_t)&templates_obj;
if(a>=(uintptr_t)&objpool&&a<(uintptr_t)&objpool+sizeof objpool)return 400000+a-(uintptr_t)&objpool;
if(a>=(uintptr_t)&monpool&&a<(uintptr_t)&monpool+sizeof monpool)return 500000+a-(uintptr_t)&monpool;
if(a>=(uintptr_t)&rooms_pool&&a<(uintptr_t)&rooms_pool+sizeof rooms_pool)return 600000+a-(uintptr_t)&rooms_pool;
if(a>=(uintptr_t)&coordpool&&a<(uintptr_t)&coordpool+sizeof coordpool)return 700000+a-(uintptr_t)&coordpool;
if(a>=(uintptr_t)&longcells&&a<(uintptr_t)&longcells+sizeof longcells)return 800000+a-(uintptr_t)&longcells;
if(a>=(uintptr_t)&ptrcells&&a<(uintptr_t)&ptrcells+sizeof ptrcells)return 900000+a-(uintptr_t)&ptrcells;
if(a>=(uintptr_t)&corridors&&a<(uintptr_t)&corridors+sizeof corridors)return 1000000+a-(uintptr_t)&corridors;
if(a>=(uintptr_t)&fragments&&a<(uintptr_t)&fragments+sizeof fragments)return 1100000+a-(uintptr_t)&fragments;
if(a>=(uintptr_t)&regionpool&&a<(uintptr_t)&regionpool+sizeof regionpool)return 1200000+a-(uintptr_t)&regionpool;
if(a>=(uintptr_t)&initpool&&a<(uintptr_t)&initpool+sizeof initpool)return 1300000+a-(uintptr_t)&initpool;
if(a>=(uintptr_t)&trappool&&a<(uintptr_t)&trappool+sizeof trappool)return 1400000+a-(uintptr_t)&trappool;
if(a>=(uintptr_t)&roompool&&a<(uintptr_t)&roompool+sizeof roompool)return 1500000+a-(uintptr_t)&roompool;
if(a>=(uintptr_t)&doorpool&&a<(uintptr_t)&doorpool+sizeof doorpool)return 1600000+a-(uintptr_t)&doorpool;
if(a>=(uintptr_t)&altarpool&&a<(uintptr_t)&altarpool+sizeof altarpool)return 1700000+a-(uintptr_t)&altarpool;
if(a>=(uintptr_t)&lregionpool&&a<(uintptr_t)&lregionpool+sizeof lregionpool)return 1800000+a-(uintptr_t)&lregionpool;
if(a>=(uintptr_t)&terrainpool&&a<(uintptr_t)&terrainpool+sizeof terrainpool)return 1900000+a-(uintptr_t)&terrainpool;
if(a>=(uintptr_t)&valueout&&a<(uintptr_t)&valueout+sizeof valueout)return 1950000+a-(uintptr_t)&valueout;
if(a>=(uintptr_t)&gx&&a<(uintptr_t)&gx+sizeof gx)return 2000000+a-(uintptr_t)&gx;
if(a>=(uintptr_t)&gy&&a<(uintptr_t)&gy+sizeof gy)return 2100000+a-(uintptr_t)&gy;
if(a>=(uintptr_t)&svl&&a<(uintptr_t)&svl+sizeof svl)return 2200000+a-(uintptr_t)&svl;
if(a>=(uintptr_t)&uball&&a<(uintptr_t)&uball+sizeof uball)return 2300000+a-(uintptr_t)&uball;
if(a>=(uintptr_t)&u&&a<(uintptr_t)&u+sizeof u)return 2400000+a-(uintptr_t)&u;
if(a>=(uintptr_t)&uchain&&a<(uintptr_t)&uchain+sizeof uchain)return 2500000+a-(uintptr_t)&uchain;
if(a>=(uintptr_t)&gs&&a<(uintptr_t)&gs+sizeof gs)return 2600000+a-(uintptr_t)&gs;
if(a>=(uintptr_t)&gf&&a<(uintptr_t)&gf+sizeof gf)return 2700000+a-(uintptr_t)&gf;
if(a>=(uintptr_t)&gm&&a<(uintptr_t)&gm+sizeof gm)return 2800000+a-(uintptr_t)&gm;
if(a>=(uintptr_t)&head_engr&&a<(uintptr_t)&head_engr+sizeof head_engr)return 2900000+a-(uintptr_t)&head_engr;
if(a>=(uintptr_t)&gn&&a<(uintptr_t)&gn+sizeof gn)return 3000000+a-(uintptr_t)&gn;
if(a>=(uintptr_t)&gl&&a<(uintptr_t)&gl+sizeof gl)return 3100000+a-(uintptr_t)&gl;
if(a>=(uintptr_t)&svn&&a<(uintptr_t)&svn+sizeof svn)return 3200000+a-(uintptr_t)&svn;
if(a>=(uintptr_t)&gr&&a<(uintptr_t)&gr+sizeof gr)return 3300000+a-(uintptr_t)&gr;
if(a>=(uintptr_t)&svr&&a<(uintptr_t)&svr+sizeof svr)return 3400000+a-(uintptr_t)&svr;
if(a>=(uintptr_t)&gd&&a<(uintptr_t)&gd+sizeof gd)return 3500000+a-(uintptr_t)&gd;
if(a>=(uintptr_t)&svd&&a<(uintptr_t)&svd+sizeof svd)return 3600000+a-(uintptr_t)&svd;
if(a>=(uintptr_t)&gt&&a<(uintptr_t)&gt+sizeof gt)return 3700000+a-(uintptr_t)&gt;
if(a>=(uintptr_t)&sve&&a<(uintptr_t)&sve+sizeof sve)return 3800000+a-(uintptr_t)&sve;
if(a>=(uintptr_t)&iflags&&a<(uintptr_t)&iflags+sizeof iflags)return 3900000+a-(uintptr_t)&iflags;
if(a>=(uintptr_t)&svc&&a<(uintptr_t)&svc+sizeof svc)return 4000000+a-(uintptr_t)&svc;
if(a>=(uintptr_t)&gi&&a<(uintptr_t)&gi+sizeof gi)return 4100000+a-(uintptr_t)&gi;
if(a>=(uintptr_t)&svi&&a<(uintptr_t)&svi+sizeof svi)return 4200000+a-(uintptr_t)&svi;
if(a>=(uintptr_t)&mons&&a<(uintptr_t)&mons+sizeof mons)return 4300000+a-(uintptr_t)&mons;
if(a>=(uintptr_t)&svm&&a<(uintptr_t)&svm+sizeof svm)return 4400000+a-(uintptr_t)&svm;
if(a>=(uintptr_t)&gu&&a<(uintptr_t)&gu+sizeof gu)return 4500000+a-(uintptr_t)&gu;
if(a>=(uintptr_t)&defsyms&&a<(uintptr_t)&defsyms+sizeof defsyms)return 4600000+a-(uintptr_t)&defsyms;
if(a>=(uintptr_t)&obj_descr&&a<(uintptr_t)&obj_descr+sizeof obj_descr)return 4700000+a-(uintptr_t)&obj_descr;
if(a>=(uintptr_t)&objects&&a<(uintptr_t)&objects+sizeof objects)return 4800000+a-(uintptr_t)&objects;
if(a>=(uintptr_t)&def_monsyms&&a<(uintptr_t)&def_monsyms+sizeof def_monsyms)return 4900000+a-(uintptr_t)&def_monsyms;
if(a>=(uintptr_t)&gc&&a<(uintptr_t)&gc+sizeof gc)return 5000000+a-(uintptr_t)&gc;
if(a>=(uintptr_t)&emptystr&&a<(uintptr_t)&emptystr+sizeof emptystr)return 5100000+a-(uintptr_t)&emptystr;
if(a>=(uintptr_t)&cg&&a<(uintptr_t)&cg+sizeof cg)return 5200000+a-(uintptr_t)&cg;
for(int i=blockcount-1;i>=0;i--)if(a>=(uintptr_t)blocks[i].p&&a<(uintptr_t)blocks[i].p+blocks[i].n)return 10000000+(uint64_t)i*100000+a-(uintptr_t)blocks[i].p;return a;}
void __real_free(void*);void __wrap_free(void*p){if(!p)return;for(int i=blockcount-1;i>=0;i--)if(blocks[i].p==p){if(!blocks[i].live)abort();blocks[i].live=0;append("free:%d;",i);__real_free(p);return;}__real_free(p);}
static void*tracked(size_t n){if(blockcount==4096)abort();void*p=malloc(n);if(!p)abort();memset(p,0x5a,n);blocks[blockcount]=(struct block){p,n,1};append("alloc:%d:%zu;",blockcount,n);blockcount++;return p;}
static void fixture_sret_reentry(void);
static void hook(void){if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentry){reentry=0;(void)match_maptyps(ROOM,ROOM);fixture_sret_reentry();}}
static struct obj*fixture_newobj(int typ,int x,int y){struct obj*p=tracked(sizeof *p);memset(p,0,sizeof *p);p->otyp=typ;p->oclass=FOOD_CLASS;p->quan=1;p->corpsenm=NON_PM;p->ox=x;p->oy=y;p->where=OBJ_FREE;for(int i=0;i<blockcount;i++)if(blocks[i].p==p)blocks[i].kind=2;return p;}
static struct monst*newmon(struct permonst*pm,int x,int y){struct monst*p=tracked(sizeof *p);memset(p,0,sizeof *p);p->data=pm?pm:&mons[PM_HUMAN];p->mx=x;p->my=y;p->mhp=p->mhpmax=20;p->mcansee=p->mcanmove=1;for(int i=0;i<blockcount;i++)if(blocks[i].p==p)blocks[i].kind=3;return p;}
static void tag(void*p,int kind){for(int i=blockcount-1;i>=0;i--)if(blocks[i].p==p){blocks[i].kind=kind;return;}abort();}
struct selectionvar*__real_selection_new(void);struct selectionvar*__wrap_selection_new(void){struct selectionvar*p=__real_selection_new();tag(p,1);return p;}
struct selectionvar*__real_selection_clone(struct selectionvar*);struct selectionvar*__wrap_selection_clone(struct selectionvar*sel){struct selectionvar*p=__real_selection_clone(sel);tag(p,1);return p;}
long * (alloc)(unsigned int a0){return tracked(a0);}
char * (dupstr)(const char * a0){size_t n=strlen(a0)+1;char*p=tracked(n);memcpy(p,a0,n);return p;}
char * (stripdigits)(char * a0){char*d=a0;for(char*s=a0;*s;s++)if(*s<'0'||*s>'9')*d++=*s;*d=0;return a0;}
int (str_lines_maxlen)(const char * a0){int max=0,n=0;for(const char*p=a0;;p++){if(*p=='\n'||!*p){if(n>max)max=n;n=0;if(!*p)break;}else n++;}return max;}
schar (splev_chr2typ)(char a0){switch(a0){case '.':return ROOM;case ' ':return STONE;case '-':return HWALL;case '|':return VWALL;case '+':return DOOR;case '#':return CORR;case 'x':return MAX_TYPE;default:return INVALID_TYPE;}}
int (isok)(coordxy a0,coordxy a1){return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){append("sobj_at:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);return 0;}
void (obj_extract_self)(struct obj * a0){append("obj_extract_self:%lld;",(long long)token((const void*)a0));}
void (obfree)(struct obj * a0,struct obj * a1){append("obfree:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1));}
struct trap * (t_at)(coordxy a0,coordxy a1){append("t_at:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
void (deltrap)(struct trap * a0){append("deltrap:%lld;",(long long)token((const void*)a0));}
struct engr * (engr_at)(coordxy a0,coordxy a1){append("engr_at:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
void (del_engr)(struct engr * a0){append("del_engr:%lld;",(long long)token((const void*)a0));}
boolean (set_levltyp_lit)(coordxy a0,coordxy a1,schar a2,schar a3){levl[a0][a1].typ=a2;levl[a0][a1].lit=a3;append("terlit:%d:%d:%d:%d;",a0,a1,a2,a3);return 1;}
boolean (rng_log_enabled)(void){return 1;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("rngcaller:%s:%d:%s;",a0,a1,a2);}
int (rn2)(int a0){if(a0<=0)abort();int v=(unsigned)(rngvalue>=0?rngvalue:cursor++)%(unsigned)a0;append("rn2:%d:%d;",a0,v);hook();return v;}
int (swapbits)(int a0,int a1,int a2){int x=(a0>>a1)&1,y=(a0>>a2)&1;return x==y?a0:a0^((1<<a1)|(1<<a2));}
int (back_to_glyph)(coordxy a0,coordxy a1){append("back_to_glyph:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
void (get_level_extends)(coordxy * a0,coordxy * a1,coordxy * a2,coordxy * a3){*a0=1;*a1=0;*a2=COLNO-1;*a3=ROWNO-1;}
void (unplacebc)(void){append("unplacebc:;");}
void (flip_worm_segs_vertical)(struct monst * a0,int a1,int a2){append("flip_worm_segs_vertical:%lld:%lld:%lld;",(long long)token((const void*)a0),(long long)a1,(long long)a2);}
void (flip_worm_segs_horizontal)(struct monst * a0,int a1,int a2){append("flip_worm_segs_horizontal:%lld:%lld:%lld;",(long long)token((const void*)a0),(long long)a1,(long long)a2);}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
void (placebc)(void){append("placebc:;");}
void (fix_wall_spines)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){append("fix_wall_spines:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
void (set_wall_state)(void){append("set_wall_state:;");}
void (vision_reset)(void){append("vision_reset:;");}
boolean (inside_room)(struct mkroom * a0,coordxy a1,coordxy a2){return a1>=a0->lx&&a1<=a0->hx&&a2>=a0->ly&&a2<=a0->hy;}
void (add_door)(coordxy a0,coordxy a1,struct mkroom * a2){append("door:%d:%d;",a0,a1);}
int (rnd)(int a0){if(a0<=0)abort();int v=1+(unsigned)(rngvalue>=0?rngvalue:cursor++)%(unsigned)a0;append("rnd:%d:%d;",a0,v);hook();return v;}
boolean (Can_dig_down)(d_level * a0){return query;}
boolean (somexy)(struct mkroom * a0,coord * a1){a1->x=a0->lx;a1->y=a0->ly;return query;}
boolean (is_pool)(coordxy a0,coordxy a1){return levl[a0][a1].typ==POOL;}
boolean (is_lava)(coordxy a0,coordxy a1){return levl[a0][a1].typ==LAVAPOOL;}
boolean (debugcore)(const char * a0,boolean a1){return result;}
boolean (litstate_rnd)(int a0){return a0<0?0:a0;}
NhRect * (rnd_rect)(void){static NhRect r={2,2,30,16};return query?&r:0;}
NhRect * (get_rect)(NhRect * a0){return query?a0:0;}
void (split_rects)(NhRect * a0,NhRect * a1){append("split_rects:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1));}
void (add_room)(coordxy a0,coordxy a1,coordxy a2,coordxy a3,boolean a4,schar a5,boolean a6){append("addroom:%d:%d:%d:%d;",a0,a1,a2,a3);}
void (add_subroom)(struct mkroom * a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,boolean a5,schar a6,boolean a7){append("subroom;");}
int (okdoor)(coordxy a0,coordxy a1){return query;}
boolean (set_levltyp)(coordxy a0,coordxy a1,schar a2){levl[a0][a1].typ=a2;return 1;}
void (pick_vibrasquare_location)(void){append("pick_vibrasquare_location:;");}
struct trap * (maketrap)(coordxy a0,coordxy a1,int a2){append("maketrap:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);return 0;}
void (mktrap)(int a0,unsigned int a1,struct mkroom * a2,coord * a3){append("mktrap:%d:%u:%llu:%d:%d;",a0,a1,(unsigned long long)token(a2),a3?a3->x:-1,a3?a3->y:-1);}
unsigned int (induced_align)(int a0){append("induced_align:%lld;",(long long)a0);return 0;}
int (def_char_to_monclass)(char a0){return S_HUMAN;}
struct permonst * (mkclass)(char a0,int a1){return &mons[PM_HUMAN];}
boolean (In_mines)(d_level * a0){append("In_mines:%lld;",(long long)token((const void*)a0));return 0;}
boolean (enexto)(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){a0->x=a1;a0->y=a2;return query;}
struct monst * (mk_roamer)(struct permonst * a0,aligntyp a1,coordxy a2,coordxy a3,boolean a4){return newmon(a0,a2,a3);}
struct monst * (mk_mplayer)(struct permonst * a0,coordxy a1,coordxy a2,boolean a3){return newmon(a0,a1,a2);}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:%llu:%d:%d:%u;",(unsigned long long)token(a0),a1,a2,a3);return newmon(a0,a1,a2);}
struct monst * (christen_monst)(struct monst * a0,const char * a1){return a0;}
void (place_monster)(struct monst * a0,coordxy a1,coordxy a2){append("place_monster:%lld:%lld:%lld;",(long long)token((const void*)a0),(long long)a1,(long long)a2);}
void (set_mimic_sym)(struct monst * a0){append("set_mimic_sym:%lld;",(long long)token((const void*)a0));}
int (strncmpi)(const char * a0,const char * a1,int a2){return strncasecmp(a0,a1,a2);}
int (select_newcham_form)(struct monst * a0){append("select_newcham_form:%lld;",(long long)token((const void*)a0));return 0;}
int (name_to_mon)(const char * a0,int * a1){return PM_HUMAN;}
boolean (validvamp)(struct monst * a0,int * a1,int a2){append("validvamp:%lld:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1),(long long)a2);return 0;}
void (mgender_from_permonst)(struct monst * a0,struct permonst * a1){append("mgender_from_permonst:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1));}
void (set_mon_data)(struct monst * a0,struct permonst * a1){a0->data=a1;}
anything * (monst_to_any)(struct monst * a0){append("monst_to_any:%lld;",(long long)token((const void*)a0));return 0;}
void (del_light_source)(int a0,union any * a1){append("del_light_source:%lld:%lld;",(long long)a0,(long long)token((const void*)a1));}
void (new_light_source)(coordxy a0,coordxy a1,int a2,int a3,union any * a4){append("new_light_source:%lld:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3,(long long)token((const void*)a4));}
int (does_block)(int a0,int a1,struct rm * a2){append("does_block:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)token((const void*)a2));return 0;}
void (block_point)(int a0,int a1){append("block_point:%lld:%lld;",(long long)a0,(long long)a1);}
void (set_malign)(struct monst * a0){append("set_malign:%lld;",(long long)token((const void*)a0));}
int (newcham)(struct monst * a0,struct permonst * a1,unsigned int a2){append("newcham:%lld:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1),(long long)a2);return 0;}
void (mdrop_special_objs)(struct monst * a0){append("mdrop_special_objs:%lld;",(long long)token((const void*)a0));}
void (discard_minvent)(struct monst * a0,boolean a1){append("discard_minvent:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);}
struct obj * (mkobj_at)(char a0,coordxy a1,coordxy a2,boolean a3){return fixture_newobj(FOOD_RATION,a1,a2);}
struct obj * (mksobj_at)(int a0,coordxy a1,coordxy a2,boolean a3,boolean a4){return fixture_newobj(a0,a1,a2);}
int (def_char_to_objclass)(char a0){return FOOD_CLASS;}
struct obj * (mkgold)(long a0,coordxy a1,coordxy a2){struct obj*p=fixture_newobj(GOLD_PIECE,a1,a2);p->quan=a0;return p;}
void (bless)(struct obj * a0){a0->blessed=1;a0->cursed=0;}
void (unbless)(struct obj * a0){a0->blessed=0;}
void (uncurse)(struct obj * a0){a0->cursed=0;}
void (curse)(struct obj * a0){a0->cursed=1;a0->blessed=0;}
void (blessorcurse)(struct obj * a0,int a1){append("blessorcurse:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);}
int (rndmonnum)(void){return PM_HUMAN;}
void (set_corpsenm)(struct obj * a0,int a1){a0->corpsenm=a1;}
struct obj * (oname)(struct obj * a0,const char * a1,unsigned int a2){return a0;}
const char * (lookup_novel)(const char * a0,int * a1){append("lookup_novel:%s:%lld;",(a0?a0:"NULL"),(long long)token((const void*)a1));return 0;}
int (weight)(struct obj * a0){return 10;}
void (remove_object)(struct obj * a0){append("remove_object:%lld;",(long long)token((const void*)a0));}
boolean (can_saddle)(struct monst * a0){append("can_saddle:%lld;",(long long)token((const void*)a0));return 0;}
void (put_saddle_on_mon)(struct obj * a0,struct monst * a1){append("put_saddle_on_mon:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1));}
int (mpickobj)(struct monst * a0,struct obj * a1){a1->nobj=a0->minvent;a0->minvent=a1;a1->ocarry=a0;a1->where=OBJ_MINVENT;return 0;}
struct obj * (add_to_container)(struct obj * a0,struct obj * a1){a1->nobj=a0->cobj;a0->cobj=a1;a1->ocontainer=a0;a1->where=OBJ_CONTAINED;return a1;}
const char * (safe_oname)(struct obj * a0){return "item";}
void (artifact_exists)(struct obj * a0,const char * a1,boolean a2,unsigned int a3){append("artifact_exists:%lld:%s:%lld:%lld;",(long long)token((const void*)a0),(a1?a1:"NULL"),(long long)a2,(long long)a3);}
void (delete_contents)(struct obj * a0){append("delete_contents:%lld;",(long long)token((const void*)a0));}
boolean (Resists_Elem)(struct monst * a0,int a1){append("Resists_Elem:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);return 0;}
boolean (poly_when_stoned)(struct permonst * a0){append("poly_when_stoned:%lld;",(long long)token((const void*)a0));return 0;}
boolean (propagate)(int a0,boolean a1,boolean a2){append("propagate:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);return 0;}
void (mongone)(struct monst * a0){append("mongone:%lld;",(long long)token((const void*)a0));}
int (describe_level)(char * a0,int a1){append("describe_level:%s:%lld;",(a0?a0:"NULL"),(long long)a1);return 0;}
char * (simpleonames)(struct obj * a0){return "item";}
void (stackobj)(struct obj * a0){append("stackobj:%lld;",(long long)token((const void*)a0));}
void (begin_burn)(struct obj * a0,boolean a1){append("begin_burn:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);}
struct obj * (bury_an_obj)(struct obj * a0,boolean * a1){*a1=0;return a0;}
char * (in_rooms)(coordxy a0,coordxy a1,int a2){return "";}
void (priestini)(d_level * a0,struct mkroom * a1,int a2,int a3,boolean a4){append("priestini:%lld:%lld:%lld:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1),(long long)a2,(long long)a3,(long long)a4);}
boolean (maybe_sdoor)(int a0){return result;}
void (makecorridors)(void){append("makecorridors:;");}
void (stock_room)(int a0,struct mkroom * a1){append("stock_room:%lld:%lld;",(long long)a0,(long long)token((const void*)a1));}
schar (depth)(d_level * a0){append("depth:%lld;",(long long)token((const void*)a0));return 0;}
void (fill_zoo)(struct mkroom * a0){append("fill_zoo:%lld;",(long long)token((const void*)a0));}
void (topologize)(struct mkroom * a0){append("topologize:%lld;",(long long)token((const void*)a0));}
void (create_maze)(int a0,int a1,boolean a2){append("create_maze:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);}
void (makeroguerooms)(void){append("makeroguerooms:;");}
void (mkmap)(lev_init * a0){append("mkmap:%lld;",(long long)token((const void*)a0));}
void (m_dowear)(struct monst * a0,boolean a1){append("m_dowear:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);}
void (nhl_add_table_entry_int)(lua_State * a0,const char * a1,lua_Integer a2){lua_pushinteger(a0,a2);lua_setfield(a0,-2,a1);}
void (nhl_add_table_entry_region)(lua_State * a0,const char * a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5){lua_createtable(a0,4,0);lua_pushinteger(a0,a2);lua_rawseti(a0,-2,1);lua_pushinteger(a0,a3);lua_rawseti(a0,-2,2);lua_pushinteger(a0,a4);lua_rawseti(a0,-2,3);lua_pushinteger(a0,a5);lua_rawseti(a0,-2,4);lua_setfield(a0,-2,a1);}
void (nhl_add_table_entry_bool)(lua_State * a0,const char * a1,boolean a2){lua_pushboolean(a0,a2);lua_setfield(a0,-2,a1);}
void (nhl_add_table_entry_str)(lua_State * a0,const char * a1,const char * a2){lua_pushstring(a0,a2);lua_setfield(a0,-2,a1);}
void (nhl_error)(lua_State * a0,const char * a1){luaL_error(a0,"%s",a1);abort();}
unsigned int (Strlen_)(const char * a0,const char * a1,int a2){return strlen(a0);}
int (get_table_option)(lua_State * a0,const char * a1,const char * a2,const char *const * a3){lua_getfield(a0,1,a1);int n=luaL_checkoption(a0,-1,a2,a3);lua_pop(a0,1);return n;}
char * (get_table_str_opt)(lua_State * a0,const char * a1,char * a2){lua_getfield(a0,1,a1);const char*s=lua_isnil(a0,-1)?a2:luaL_checkstring(a0,-1);char*p=s?dupstr(s):0;lua_pop(a0,1);return p;}
int (name_to_monplus)(const char * a0,const char ** a1,int * a2){if(a1)*a1=0;if(a2)*a2=NEUTRAL;return PM_HUMAN;}
int (get_table_int_opt)(lua_State * a0,const char * a1,int a2){lua_getfield(a0,1,a1);int n=(int)luaL_optinteger(a0,-1,a2);lua_pop(a0,1);return n;}
void (lcheck_param_table)(lua_State * a0){luaL_checktype(a0,1,LUA_TTABLE);}
int (get_table_boolean_opt)(lua_State * a0,const char * a1,int a2){lua_getfield(a0,1,a1);int n=lua_isnil(a0,-1)?a2:lua_toboolean(a0,-1);lua_pop(a0,1);return n;}
int (nhl_pcall_handle)(lua_State * a0,int a1,int a2,const char * a3,NHL_pcall_action a4){int status=lua_pcall(a0,a1,a2,0);append("pcall:%d;",status);if(status){append("luaerror:%s;",lua_tostring(a0,-1));lua_pop(a0,1);}return status;}
char * (eos)(char * a0){return a0+strlen(a0);}
char * (strstri)(const char * a0,const char * a1){return (char*)strstr(a0,a1);}
void (nhl_push_obj)(lua_State * a0,struct obj * a1){struct obj**p=lua_newuserdatauv(a0,sizeof *p,0);*p=a1;}
schar (get_table_mapchr_opt)(lua_State * a0,const char * a1,schar a2){lua_getfield(a0,1,a1);const char*s=lua_isnil(a0,-1)?0:luaL_checkstring(a0,-1);int n=s?splev_chr2typ(*s):a2;lua_pop(a0,1);return n;}
char * (get_table_str)(lua_State * a0,const char * a1){lua_getfield(a0,1,a1);char*p=dupstr(luaL_checkstring(a0,-1));lua_pop(a0,1);return p;}
void (make_engr_at)(coordxy a0,coordxy a1,const char * a2,const char * a3,long a4,int a5){append("make_engr_at:%lld:%lld:%s:%s:%lld:%lld;",(long long)a0,(long long)a1,(a2?a2:"NULL"),(a3?a3:"NULL"),(long long)a4,(long long)a5);}
void (mineralize)(int a0,int a1,int a2,int a3,boolean a4){append("mineralize:%lld:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3,(long long)a4);}
boolean (nhl_get_xy_params)(lua_State * a0,lua_Integer * a1,lua_Integer * a2){*a1=luaL_checkinteger(a0,1);*a2=luaL_checkinteger(a0,2);return 1;}
void (stairway_add)(coordxy a0,coordxy a1,boolean a2,boolean a3,d_level * a4){append("stairway:%d:%d:%d:%d:%d:%d;",a0,a1,a2,a3,a4->dnum,a4->dlevel);}
void (mkstairs)(coordxy a0,coordxy a1,char a2,struct mkroom * a3,boolean a4){append("mkstairs:%lld:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)token((const void*)a3),(long long)a4);}
void (make_grave)(coordxy a0,coordxy a1,const char * a2){append("make_grave:%lld:%lld:%s;",(long long)a0,(long long)a1,(a2?a2:"NULL"));}
int (get_table_int)(lua_State * a0,const char * a1){lua_getfield(a0,1,a1);int n=(int)luaL_checkinteger(a0,-1);lua_pop(a0,1);return n;}
void (del_engr_at)(coordxy a0,coordxy a1){append("del_engr_at:%lld:%lld;",(long long)a0,(long long)a1);}
NhRegion * (create_gas_cloud)(coordxy a0,coordxy a1,int a2,int a3){append("create_gas_cloud:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);return 0;}
NhRegion * (create_gas_cloud_selection)(struct selectionvar * a0,int a1){append("create_gas_cloud_selection:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);return 0;}
schar (get_table_mapchr)(lua_State * a0,const char * a1){lua_getfield(a0,1,a1);const char*s=luaL_checkstring(a0,-1);int n=splev_chr2typ(*s);lua_pop(a0,1);return n;}
schar (check_mapchr)(const char * a0){return splev_chr2typ(*a0);}
boolean (Can_fall_thru)(d_level * a0){return query;}
void (flood_fill_rm)(coordxy a0,coordxy a1,int a2,boolean a3,boolean a4){append("flood_fill_rm:%lld:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3,(long long)a4);}
boolean (create_drawbridge)(coordxy a0,coordxy a1,int a2,boolean a3){append("create_drawbridge:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);return 0;}
void (walkfrom)(coordxy a0,coordxy a1,schar a2){append("walkfrom:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);}
boolean (In_W_tower)(coordxy a0,coordxy a1,d_level * a2){append("In_W_tower:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)token((const void*)a2));return 0;}
void (makemap_prepost)(boolean a0,boolean a1){append("makemap_prepost:%lld:%lld;",(long long)a0,(long long)a1);}
void (oinit)(void){append("oinit:;");}
void (clear_level_structures)(void){append("clear_level_structures:;");}
void (wallification)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){append("wallification:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);}
void (count_level_features)(void){append("count_level_features:;");}
void (fixup_special)(void){append("fixup_special:;");}
void (premap_detect)(void){append("premap_detect:;");}
void (level_finalize_topology)(void){append("level_finalize_topology:;");}
int (somex)(struct mkroom * a0){return a0->lx;}
int (somey)(struct mkroom * a0){return a0->ly;}
boolean (In_hell)(d_level * a0){append("In_hell:%lld;",(long long)token((const void*)a0));return 0;}
boolean (load_lua)(const char * a0,nhl_sandbox_info * a1){append("load:%s:%u:%u:%u:%u;",a0,a1->flags,a1->memlimit,a1->steps,a1->perpcall);return !lua_fail;}
void (panic)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("panic:%s;",b);longjmp(escape,1);}
void (impossible)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void (pline)(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);}
int dist2(coordxy x0,coordxy y0,coordxy x1,coordxy y1){int dx=x1-x0,dy=y1-y0;return dx*dx+dy*dy;}
void rect_bounds(NhRect a,NhRect b,NhRect*out){out->lx=a.lx<b.lx?a.lx:b.lx;out->ly=a.ly<b.ly?a.ly:b.ly;out->hx=a.hx>b.hx?a.hx:b.hx;out->hy=a.hy>b.hy?a.hy:b.hy;}
static void*fixture_lua_allocator(void*ud,void*p,size_t old,size_t n){(void)ud;(void)old;if(!n){__real_free(p);return NULL;}return realloc(p,n);}
#ifdef HYBRID_SP_LEV
#include "../nethack-c/wasm/tu-fragments/sp_lev-types.h"
extern void teleport_sp_lev_solidify_map(void);
#define solidify_map teleport_sp_lev_solidify_map
extern void teleport_sp_lev_map_cleanup(void);
#define map_cleanup teleport_sp_lev_map_cleanup
extern void teleport_sp_lev_lvlfill_maze_grid(int x1,int y1,int x2,int y2,schar filling);
#define lvlfill_maze_grid teleport_sp_lev_lvlfill_maze_grid
extern void teleport_sp_lev_lvlfill_solid(schar filling,schar lit);
#define lvlfill_solid teleport_sp_lev_lvlfill_solid
extern void teleport_sp_lev_lvlfill_swamp(schar fg,schar bg,schar lit);
#define lvlfill_swamp teleport_sp_lev_lvlfill_swamp
extern void teleport_sp_lev_flip_dbridge_horizontal(struct rm * lev);
#define flip_dbridge_horizontal teleport_sp_lev_flip_dbridge_horizontal
extern void teleport_sp_lev_flip_dbridge_vertical(struct rm * lev);
#define flip_dbridge_vertical teleport_sp_lev_flip_dbridge_vertical
extern void teleport_sp_lev_flip_visuals(int flp,int minx,int miny,int maxx,int maxy);
#define flip_visuals teleport_sp_lev_flip_visuals
extern int teleport_sp_lev_flip_encoded_dir_bits(int flp,int val);
#define flip_encoded_dir_bits teleport_sp_lev_flip_encoded_dir_bits
extern void teleport_sp_lev_flip_vault_guard(int flp,struct monst * grd,coordxy minx,coordxy miny,coordxy maxx,coordxy maxy);
#define flip_vault_guard teleport_sp_lev_flip_vault_guard
extern void teleport_sp_lev_sel_set_wall_property(coordxy x,coordxy y,genericptr_t arg);
#define sel_set_wall_property teleport_sp_lev_sel_set_wall_property
extern void teleport_sp_lev_set_wall_property(coordxy x1,coordxy y1,coordxy x2,coordxy y2,int prop);
#define set_wall_property teleport_sp_lev_set_wall_property
extern void teleport_sp_lev_remove_boundary_syms(void);
#define remove_boundary_syms teleport_sp_lev_remove_boundary_syms
extern void teleport_sp_lev_set_door_orientation(int x,int y);
#define set_door_orientation teleport_sp_lev_set_door_orientation
extern boolean teleport_sp_lev_shared_with_room(int x,int y,struct mkroom * droom);
#define shared_with_room teleport_sp_lev_shared_with_room
extern void teleport_sp_lev_maybe_add_door(int x,int y,struct mkroom * droom);
#define maybe_add_door teleport_sp_lev_maybe_add_door
extern void teleport_sp_lev_link_doors_rooms(void);
#define link_doors_rooms teleport_sp_lev_link_doors_rooms
extern int teleport_sp_lev_rnddoor(void);
#define rnddoor teleport_sp_lev_rnddoor
extern int teleport_sp_lev_rndtrap(void);
#define rndtrap teleport_sp_lev_rndtrap
extern void teleport_sp_lev_get_location(coordxy * x,coordxy * y,getloc_flags_t humidity,struct mkroom * croom);
#define get_location teleport_sp_lev_get_location
extern void teleport_sp_lev_set_ok_location_func(boolean (*func)(coordxy, coordxy));
#define set_ok_location_func teleport_sp_lev_set_ok_location_func
extern boolean teleport_sp_lev_is_ok_location(coordxy x,coordxy y,getloc_flags_t humidity);
#define is_ok_location teleport_sp_lev_is_ok_location
extern unpacked_coord teleport_sp_lev_get_unpacked_coord(long loc,int defhumidity);
#define get_unpacked_coord teleport_sp_lev_get_unpacked_coord
extern void teleport_sp_lev_get_room_loc(coordxy * x,coordxy * y,struct mkroom * croom);
#define get_room_loc teleport_sp_lev_get_room_loc
extern void teleport_sp_lev_get_free_room_loc(coordxy * x,coordxy * y,struct mkroom * croom,long pos);
#define get_free_room_loc teleport_sp_lev_get_free_room_loc
extern boolean teleport_sp_lev_create_subroom(struct mkroom * proom,coordxy x,coordxy y,coordxy w,coordxy h,xint16 rtype,xint16 rlit);
#define create_subroom teleport_sp_lev_create_subroom
extern void teleport_sp_lev_create_door(room_door * dd,struct mkroom * broom);
#define create_door teleport_sp_lev_create_door
extern void teleport_sp_lev_create_trap(spltrap * t,struct mkroom * croom);
#define create_trap teleport_sp_lev_create_trap
extern int teleport_sp_lev_noncoalignment(aligntyp alignment);
#define noncoalignment teleport_sp_lev_noncoalignment
extern boolean teleport_sp_lev_m_bad_boulder_spot(coordxy x,coordxy y);
#define m_bad_boulder_spot teleport_sp_lev_m_bad_boulder_spot
extern int teleport_sp_lev_pm_to_humidity(struct permonst * pm);
#define pm_to_humidity teleport_sp_lev_pm_to_humidity
extern unsigned int teleport_sp_lev_sp_amask_to_amask(unsigned int sp_amask);
#define sp_amask_to_amask teleport_sp_lev_sp_amask_to_amask
extern void teleport_sp_lev_create_monster(monster * m,struct mkroom * croom);
#define create_monster teleport_sp_lev_create_monster
extern struct obj * teleport_sp_lev_create_object(object * o,struct mkroom * croom);
#define create_object teleport_sp_lev_create_object
extern void teleport_sp_lev_create_altar(altar * a,struct mkroom * croom);
#define create_altar teleport_sp_lev_create_altar
extern boolean teleport_sp_lev_search_door(struct mkroom * croom,coordxy * x,coordxy * y,xint16 wall,int cnt);
#define search_door teleport_sp_lev_search_door
extern void teleport_sp_lev_create_corridor(corridor * c);
#define create_corridor teleport_sp_lev_create_corridor
extern struct mkroom * teleport_sp_lev_build_room(room * r,struct mkroom * mkr);
#define build_room teleport_sp_lev_build_room
extern void teleport_sp_lev_light_region(region * tmpregion);
#define light_region teleport_sp_lev_light_region
extern void teleport_sp_lev_maze1xy(coord * m,int humidity);
#define maze1xy teleport_sp_lev_maze1xy
extern void teleport_sp_lev_fill_empty_maze(void);
#define fill_empty_maze teleport_sp_lev_fill_empty_maze
extern void teleport_sp_lev_splev_initlev(lev_init * linit);
#define splev_initlev teleport_sp_lev_splev_initlev
extern void teleport_sp_lev_spo_end_moninvent(void);
#define spo_end_moninvent teleport_sp_lev_spo_end_moninvent
extern void teleport_sp_lev_spo_pop_container(void);
#define spo_pop_container teleport_sp_lev_spo_pop_container
extern void teleport_sp_lev_l_push_wid_hei_table(lua_State * L,int wid,int hei);
#define l_push_wid_hei_table teleport_sp_lev_l_push_wid_hei_table
extern void teleport_sp_lev_l_push_mkroom_table(lua_State * L,struct mkroom * tmpr);
#define l_push_mkroom_table teleport_sp_lev_l_push_mkroom_table
extern int teleport_sp_lev_get_table_align(lua_State * L);
#define get_table_align teleport_sp_lev_get_table_align
extern int teleport_sp_lev_get_table_monclass(lua_State * L);
#define get_table_monclass teleport_sp_lev_get_table_monclass
extern int teleport_sp_lev_find_montype(lua_State * L,const char * s,int * mgender);
#define find_montype teleport_sp_lev_find_montype
extern int teleport_sp_lev_get_table_montype(lua_State * L,int * mgender);
#define get_table_montype teleport_sp_lev_get_table_montype
extern void teleport_sp_lev_get_table_xy_or_coord(lua_State * L,lua_Integer * x,lua_Integer * y);
#define get_table_xy_or_coord teleport_sp_lev_get_table_xy_or_coord
extern lua_Integer teleport_sp_lev_get_table_int_or_random(lua_State * L,const char * name,int rndval);
#define get_table_int_or_random teleport_sp_lev_get_table_int_or_random
extern int teleport_sp_lev_get_table_buc(lua_State * L);
#define get_table_buc teleport_sp_lev_get_table_buc
extern int teleport_sp_lev_find_objtype(lua_State * L,const char * s,char oclass);
#define find_objtype teleport_sp_lev_find_objtype
extern const char * teleport_sp_lev_get_mkroom_name(int rtype);
#define get_mkroom_name teleport_sp_lev_get_mkroom_name
extern int teleport_sp_lev_get_table_roomtype_opt(lua_State * L,const char * name,int defval);
#define get_table_roomtype_opt teleport_sp_lev_get_table_roomtype_opt
extern void teleport_sp_lev_spo_endroom(struct sp_coder * coder);
#define spo_endroom teleport_sp_lev_spo_endroom
extern boolean teleport_sp_lev_good_stair_loc(coordxy x,coordxy y);
#define good_stair_loc teleport_sp_lev_good_stair_loc
extern int teleport_sp_lev_l_create_stairway(lua_State * L,boolean using_ladder);
#define l_create_stairway teleport_sp_lev_l_create_stairway
extern int teleport_sp_lev_get_table_traptype_opt(lua_State * L,const char * name,int defval);
#define get_table_traptype_opt teleport_sp_lev_get_table_traptype_opt
extern int teleport_sp_lev_get_traptype_byname(const char * trapname);
#define get_traptype_byname teleport_sp_lev_get_traptype_byname
extern int teleport_sp_lev_floodfillchk_match_under(coordxy x,coordxy y);
#define floodfillchk_match_under teleport_sp_lev_floodfillchk_match_under
extern int teleport_sp_lev_floodfillchk_match_accessible(coordxy x,coordxy y);
#define floodfillchk_match_accessible teleport_sp_lev_floodfillchk_match_accessible
extern void teleport_sp_lev_sel_set_ter(coordxy x,coordxy y,genericptr_t arg);
#define sel_set_ter teleport_sp_lev_sel_set_ter
extern void teleport_sp_lev_sel_set_feature(coordxy x,coordxy y,genericptr_t arg);
#define sel_set_feature teleport_sp_lev_sel_set_feature
extern void teleport_sp_lev_sel_set_door(coordxy dx,coordxy dy,genericptr_t arg);
#define sel_set_door teleport_sp_lev_sel_set_door
extern void teleport_sp_lev_l_table_getset_feature_flag(lua_State * L,int x,int y,const char * name,int flag);
#define l_table_getset_feature_flag teleport_sp_lev_l_table_getset_feature_flag
extern boolean teleport_sp_lev_generate_way_out_method(coordxy nx,coordxy ny,struct selectionvar * ov);
#define generate_way_out_method teleport_sp_lev_generate_way_out_method
extern void teleport_sp_lev_ensure_way_out(void);
#define ensure_way_out teleport_sp_lev_ensure_way_out
extern lua_Integer teleport_sp_lev_get_table_intarray_entry(lua_State * L,int tableidx,int entrynum);
#define get_table_intarray_entry teleport_sp_lev_get_table_intarray_entry
extern int teleport_sp_lev_get_table_region(lua_State * L,const char * name,lua_Integer * x1,lua_Integer * y1,lua_Integer * x2,lua_Integer * y2,boolean optional);
#define get_table_region teleport_sp_lev_get_table_region
extern void teleport_sp_lev_levregion_add(lev_region * lregion);
#define levregion_add teleport_sp_lev_levregion_add
extern void teleport_sp_lev_l_get_lregion(lua_State * L,lev_region * tmplregion);
#define l_get_lregion teleport_sp_lev_l_get_lregion
extern void teleport_sp_lev_sel_set_lit(coordxy x,coordxy y,genericptr_t arg);
#define sel_set_lit teleport_sp_lev_sel_set_lit
extern void teleport_sp_lev_add_doors_to_room(struct mkroom * croom);
#define add_doors_to_room teleport_sp_lev_add_doors_to_room
extern void teleport_sp_lev_get_table_coords_or_region(lua_State * L,coordxy * dx1,coordxy * dy1,coordxy * dx2,coordxy * dy2);
#define get_table_coords_or_region teleport_sp_lev_get_table_coords_or_region
extern void teleport_sp_lev_set_wallprop_in_selection(lua_State * L,int prop);
#define set_wallprop_in_selection teleport_sp_lev_set_wallprop_in_selection
extern struct sp_coder * teleport_sp_lev_sp_level_coder_init(void);
#define sp_level_coder_init teleport_sp_lev_sp_level_coder_init
#else
#include "../.cache/wasm64-build/tree/src/sp_lev.c"
#define TELEPORT_SP_LEV_REFERENCE_TYPES 1
#define teleport_sp_lev_solidify_map solidify_map
#define teleport_sp_lev_map_cleanup map_cleanup
#define teleport_sp_lev_lvlfill_maze_grid lvlfill_maze_grid
#define teleport_sp_lev_lvlfill_solid lvlfill_solid
#define teleport_sp_lev_lvlfill_swamp lvlfill_swamp
#define teleport_sp_lev_flip_dbridge_horizontal flip_dbridge_horizontal
#define teleport_sp_lev_flip_dbridge_vertical flip_dbridge_vertical
#define teleport_sp_lev_flip_visuals flip_visuals
#define teleport_sp_lev_flip_encoded_dir_bits flip_encoded_dir_bits
#define teleport_sp_lev_flip_vault_guard flip_vault_guard
#define teleport_sp_lev_sel_set_wall_property sel_set_wall_property
#define teleport_sp_lev_set_wall_property set_wall_property
#define teleport_sp_lev_remove_boundary_syms remove_boundary_syms
#define teleport_sp_lev_set_door_orientation set_door_orientation
#define teleport_sp_lev_shared_with_room shared_with_room
#define teleport_sp_lev_maybe_add_door maybe_add_door
#define teleport_sp_lev_link_doors_rooms link_doors_rooms
#define teleport_sp_lev_rnddoor rnddoor
#define teleport_sp_lev_rndtrap rndtrap
#define teleport_sp_lev_get_location get_location
#define teleport_sp_lev_set_ok_location_func set_ok_location_func
#define teleport_sp_lev_is_ok_location is_ok_location
#define teleport_sp_lev_get_unpacked_coord get_unpacked_coord
#define teleport_sp_lev_get_room_loc get_room_loc
#define teleport_sp_lev_get_free_room_loc get_free_room_loc
#define teleport_sp_lev_create_subroom create_subroom
#define teleport_sp_lev_create_door create_door
#define teleport_sp_lev_create_trap create_trap
#define teleport_sp_lev_noncoalignment noncoalignment
#define teleport_sp_lev_m_bad_boulder_spot m_bad_boulder_spot
#define teleport_sp_lev_pm_to_humidity pm_to_humidity
#define teleport_sp_lev_sp_amask_to_amask sp_amask_to_amask
#define teleport_sp_lev_create_monster create_monster
#define teleport_sp_lev_create_object create_object
#define teleport_sp_lev_create_altar create_altar
#define teleport_sp_lev_search_door search_door
#define teleport_sp_lev_create_corridor create_corridor
#define teleport_sp_lev_build_room build_room
#define teleport_sp_lev_light_region light_region
#define teleport_sp_lev_maze1xy maze1xy
#define teleport_sp_lev_fill_empty_maze fill_empty_maze
#define teleport_sp_lev_splev_initlev splev_initlev
#define teleport_sp_lev_spo_end_moninvent spo_end_moninvent
#define teleport_sp_lev_spo_pop_container spo_pop_container
#define teleport_sp_lev_l_push_wid_hei_table l_push_wid_hei_table
#define teleport_sp_lev_l_push_mkroom_table l_push_mkroom_table
#define teleport_sp_lev_get_table_align get_table_align
#define teleport_sp_lev_get_table_monclass get_table_monclass
#define teleport_sp_lev_find_montype find_montype
#define teleport_sp_lev_get_table_montype get_table_montype
#define teleport_sp_lev_get_table_xy_or_coord get_table_xy_or_coord
#define teleport_sp_lev_get_table_int_or_random get_table_int_or_random
#define teleport_sp_lev_get_table_buc get_table_buc
#define teleport_sp_lev_find_objtype find_objtype
#define teleport_sp_lev_get_mkroom_name get_mkroom_name
#define teleport_sp_lev_get_table_roomtype_opt get_table_roomtype_opt
#define teleport_sp_lev_spo_endroom spo_endroom
#define teleport_sp_lev_good_stair_loc good_stair_loc
#define teleport_sp_lev_l_create_stairway l_create_stairway
#define teleport_sp_lev_get_table_traptype_opt get_table_traptype_opt
#define teleport_sp_lev_get_traptype_byname get_traptype_byname
#define teleport_sp_lev_floodfillchk_match_under floodfillchk_match_under
#define teleport_sp_lev_floodfillchk_match_accessible floodfillchk_match_accessible
#define teleport_sp_lev_sel_set_ter sel_set_ter
#define teleport_sp_lev_sel_set_feature sel_set_feature
#define teleport_sp_lev_sel_set_door sel_set_door
#define teleport_sp_lev_l_table_getset_feature_flag l_table_getset_feature_flag
#define teleport_sp_lev_generate_way_out_method generate_way_out_method
#define teleport_sp_lev_ensure_way_out ensure_way_out
#define teleport_sp_lev_get_table_intarray_entry get_table_intarray_entry
#define teleport_sp_lev_get_table_region get_table_region
#define teleport_sp_lev_levregion_add levregion_add
#define teleport_sp_lev_l_get_lregion l_get_lregion
#define teleport_sp_lev_sel_set_lit sel_set_lit
#define teleport_sp_lev_add_doors_to_room add_doors_to_room
#define teleport_sp_lev_get_table_coords_or_region get_table_coords_or_region
#define teleport_sp_lev_set_wallprop_in_selection set_wallprop_in_selection
#define teleport_sp_lev_sp_level_coder_init sp_level_coder_init
#endif
#include "../nethack-c/wasm/tu-fragments/sp_lev-support.c"
#include "tu-sp_lev-layout.h"
static void fixture_sret_reentry(void){valueout[3]=get_unpacked_coord(13L|(12L<<16),7);}
void probe_sret_sequence(long first,long second,int humidity){valueout[0]=get_unpacked_coord(first,humidity);valueout[1]=get_unpacked_coord(second,humidity);valueout[2]=valueout[0];}
static void create_lua(void){probe_L=luaL_newstate();if(!probe_L)abort();lua_setallocf(probe_L,fixture_lua_allocator,NULL);luaL_requiref(probe_L,"_G",luaopen_base,1);lua_pop(probe_L,1);luaL_requiref(probe_L,"table",luaopen_table,1);lua_pop(probe_L,1);luaL_requiref(probe_L,"string",luaopen_string,1);lua_pop(probe_L,1);l_register_des(probe_L);l_selection_register(probe_L);lua_settop(probe_L,0);}
int probe_lua_prepare(const char*source){lua_settop(probe_L,0);int status=luaL_loadstring(probe_L,source);if(!status)status=lua_pcall(probe_L,0,LUA_MULTRET,0);if(gc.coder)tag(gc.coder,5);return status;}
const char*probe_lua_text(int i){return lua_tostring(probe_L,i);}
lua_Integer probe_lua_int(int i){return lua_tointeger(probe_L,i);}
int probe_lua_top(void){return lua_gettop(probe_L);}
int probe_lua_type(int i){return lua_type(probe_L,i);}
uintptr_t probe_lua(void){return(uintptr_t)probe_L;}
uintptr_t probe_pool(int k,int i){switch(k){
case 0:return(uintptr_t)&buffers[i];
case 1:return(uintptr_t)&templates_mon[i];
case 2:return(uintptr_t)&templates_obj[i];
case 3:return(uintptr_t)&objpool[i];
case 4:return(uintptr_t)&monpool[i];
case 5:return(uintptr_t)&rooms_pool[i];
case 6:return(uintptr_t)&coordpool[i];
case 7:return(uintptr_t)&longcells[i];
case 8:return(uintptr_t)&ptrcells[i];
case 9:return(uintptr_t)&corridors[i];
case 10:return(uintptr_t)&fragments[i];
case 11:return(uintptr_t)&regionpool[i];
case 12:return(uintptr_t)&initpool[i];
case 13:return(uintptr_t)&trappool[i];
case 14:return(uintptr_t)&roompool[i];
case 15:return(uintptr_t)&doorpool[i];
case 16:return(uintptr_t)&altarpool[i];
case 17:return(uintptr_t)&lregionpool[i];
case 18:return(uintptr_t)&terrainpool[i];
case 19:return(uintptr_t)&valueout[i];
default:abort();}}
int probe_block_count(void){return blockcount;}
uintptr_t probe_block(int i){return(uintptr_t)blocks[i].p;}
size_t probe_block_size(int i){return blocks[i].n;}
int probe_block_live(int i){return blocks[i].live;}
int probe_block_kind(int i){return blocks[i].kind;}
size_t probe_selection_map_offset(void){return offsetof(struct selectionvar,map);}
int probe_layout_count(void){return sizeof sp_lev_layout/sizeof sp_lev_layout[0];}
const char*probe_layout_name(int i){return sp_lev_layout[i].name;}
int64_t probe_layout_value(int i){return(int64_t)sp_lev_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}
void probe_option(int k,int64_t v){switch(k){case 0:result=v;break;case 1:rngvalue=v;cursor=0;break;case 2:query=v;break;case 3:grow=v;break;case 4:reentry=v;break;case 5:lua_fail=v;break;default:abort();}}
uint64_t probe_action(int which,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f,uint64_t g,uint64_t h){if(setjmp(escape))return 0x70000000;switch(which){
case 0:{reset_xystart_size();return 0;}
case 1:{return(uint64_t)(uintptr_t)(match_maptyps((xint16)(uintptr_t)a,(xint16)(uintptr_t)b));}
case 2:{struct mapfragment*p=mapfrag_fromstr((char *)(uintptr_t)a);if(p)tag(p,4);return(uintptr_t)p;}
case 3:{mapfrag_free((struct mapfragment **)(uintptr_t)a);return 0;}
case 4:{return(uint64_t)(uintptr_t)(mapfrag_get((struct mapfragment *)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c));}
case 5:{return(uint64_t)(uintptr_t)(mapfrag_canmatch((struct mapfragment *)(uintptr_t)a));}
case 6:{return(uint64_t)(uintptr_t)(mapfrag_error((struct mapfragment *)(uintptr_t)a));}
case 7:{return(uint64_t)(uintptr_t)(mapfrag_match((struct mapfragment *)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c));}
case 8:{solidify_map();return 0;}
case 9:{map_cleanup();return 0;}
case 10:{lvlfill_maze_grid((int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c,(int)(uintptr_t)d,(schar)(uintptr_t)e);return 0;}
case 11:{lvlfill_solid((schar)(uintptr_t)a,(schar)(uintptr_t)b);return 0;}
case 12:{lvlfill_swamp((schar)(uintptr_t)a,(schar)(uintptr_t)b,(schar)(uintptr_t)c);return 0;}
case 13:{flip_dbridge_horizontal((struct rm *)(uintptr_t)a);return 0;}
case 14:{flip_dbridge_vertical((struct rm *)(uintptr_t)a);return 0;}
case 15:{flip_visuals((int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c,(int)(uintptr_t)d,(int)(uintptr_t)e);return 0;}
case 16:{return(uint64_t)(uintptr_t)(flip_encoded_dir_bits((int)(uintptr_t)a,(int)(uintptr_t)b));}
case 17:{flip_level((int)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;}
case 18:{flip_vault_guard((int)(uintptr_t)a,(struct monst *)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d,(coordxy)(uintptr_t)e,(coordxy)(uintptr_t)f);return 0;}
case 19:{flip_level_rnd((int)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;}
case 20:{sel_set_wall_property((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(genericptr_t)(uintptr_t)c);return 0;}
case 21:{set_wall_property((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d,(int)(uintptr_t)e);return 0;}
case 22:{remove_boundary_syms();return 0;}
case 23:{set_door_orientation((int)(uintptr_t)a,(int)(uintptr_t)b);return 0;}
case 24:{return(uint64_t)(uintptr_t)(shared_with_room((int)(uintptr_t)a,(int)(uintptr_t)b,(struct mkroom *)(uintptr_t)c));}
case 25:{maybe_add_door((int)(uintptr_t)a,(int)(uintptr_t)b,(struct mkroom *)(uintptr_t)c);return 0;}
case 26:{link_doors_rooms();return 0;}
case 27:{return(uint64_t)(uintptr_t)(rnddoor());}
case 28:{return(uint64_t)(uintptr_t)(rndtrap());}
case 29:{get_location((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(getloc_flags_t)(uintptr_t)c,(struct mkroom *)(uintptr_t)d);return 0;}
case 30:{set_ok_location_func((boolean (*)(coordxy, coordxy))(uintptr_t)a);return 0;}
case 31:{return(uint64_t)(uintptr_t)(is_ok_location((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(getloc_flags_t)(uintptr_t)c));}
case 32:{return(uint64_t)(uintptr_t)(pm_good_location((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(struct permonst *)(uintptr_t)c));}
case 33:{valueout[0]=get_unpacked_coord((long)(uintptr_t)a,(int)(uintptr_t)b);return(uintptr_t)&valueout[0];}
case 34:{get_location_coord((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(int)(uintptr_t)c,(struct mkroom *)(uintptr_t)d,(long)(uintptr_t)e);return 0;}
case 35:{get_room_loc((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(struct mkroom *)(uintptr_t)c);return 0;}
case 36:{get_free_room_loc((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(struct mkroom *)(uintptr_t)c,(long)(uintptr_t)d);return 0;}
case 37:{return(uint64_t)(uintptr_t)(check_room((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(coordxy *)(uintptr_t)c,(coordxy *)(uintptr_t)d,(boolean)(uintptr_t)e));}
case 38:{return(uint64_t)(uintptr_t)(create_room((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d,(coordxy)(uintptr_t)e,(coordxy)(uintptr_t)f,(xint16)(uintptr_t)g,(xint16)(uintptr_t)h));}
case 39:{return(uint64_t)(uintptr_t)(create_subroom((struct mkroom *)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d,(coordxy)(uintptr_t)e,(xint16)(uintptr_t)f,(xint16)(uintptr_t)g));}
case 40:{create_door((room_door *)(uintptr_t)a,(struct mkroom *)(uintptr_t)b);return 0;}
case 41:{create_trap((spltrap *)(uintptr_t)a,(struct mkroom *)(uintptr_t)b);return 0;}
case 42:{return(uint64_t)(uintptr_t)(noncoalignment((aligntyp)(uintptr_t)a));}
case 43:{return(uint64_t)(uintptr_t)(m_bad_boulder_spot((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));}
case 44:{return(uint64_t)(uintptr_t)(pm_to_humidity((struct permonst *)(uintptr_t)a));}
case 45:{return(uint64_t)(uintptr_t)(sp_amask_to_amask((unsigned int)(uintptr_t)a));}
case 46:{create_monster((monster *)(uintptr_t)a,(struct mkroom *)(uintptr_t)b);return 0;}
case 47:{return(uint64_t)(uintptr_t)(create_object((object *)(uintptr_t)a,(struct mkroom *)(uintptr_t)b));}
case 48:{create_altar((altar *)(uintptr_t)a,(struct mkroom *)(uintptr_t)b);return 0;}
case 49:{return(uint64_t)(uintptr_t)(search_door((struct mkroom *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(coordxy *)(uintptr_t)c,(xint16)(uintptr_t)d,(int)(uintptr_t)e));}
case 50:{return(uint64_t)(uintptr_t)(dig_corridor((coord *)(uintptr_t)a,(coord *)(uintptr_t)b,(int *)(uintptr_t)c,(boolean)(uintptr_t)d,(schar)(uintptr_t)e,(schar)(uintptr_t)f));}
case 51:{create_corridor((corridor *)(uintptr_t)a);return 0;}
case 52:{fill_special_room((struct mkroom *)(uintptr_t)a);return 0;}
case 53:{return(uint64_t)(uintptr_t)(build_room((room *)(uintptr_t)a,(struct mkroom *)(uintptr_t)b));}
case 54:{light_region((region *)(uintptr_t)a);return 0;}
case 55:{wallify_map((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d);return 0;}
case 56:{maze1xy((coord *)(uintptr_t)a,(int)(uintptr_t)b);return 0;}
case 57:{fill_empty_maze();return 0;}
case 58:{splev_initlev((lev_init *)(uintptr_t)a);return 0;}
case 59:{spo_end_moninvent();return 0;}
case 60:{spo_pop_container();return 0;}
case 61:{l_push_wid_hei_table((lua_State *)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);return 0;}
case 62:{l_push_mkroom_table((lua_State *)(uintptr_t)a,(struct mkroom *)(uintptr_t)b);return 0;}
case 63:{return(uint64_t)(uintptr_t)(lspo_message((lua_State *)(uintptr_t)a));}
case 64:{return(uint64_t)(uintptr_t)(get_table_align((lua_State *)(uintptr_t)a));}
case 65:{return(uint64_t)(uintptr_t)(get_table_monclass((lua_State *)(uintptr_t)a));}
case 66:{return(uint64_t)(uintptr_t)(find_montype((lua_State *)(uintptr_t)a,(const char *)(uintptr_t)b,(int *)(uintptr_t)c));}
case 67:{return(uint64_t)(uintptr_t)(get_table_montype((lua_State *)(uintptr_t)a,(int *)(uintptr_t)b));}
case 68:{get_table_xy_or_coord((lua_State *)(uintptr_t)a,(lua_Integer *)(uintptr_t)b,(lua_Integer *)(uintptr_t)c);return 0;}
case 69:{return(uint64_t)(uintptr_t)(lspo_monster((lua_State *)(uintptr_t)a));}
case 70:{return(uint64_t)(uintptr_t)(get_table_int_or_random((lua_State *)(uintptr_t)a,(const char *)(uintptr_t)b,(int)(uintptr_t)c));}
case 71:{return(uint64_t)(uintptr_t)(get_table_buc((lua_State *)(uintptr_t)a));}
case 72:{return(uint64_t)(uintptr_t)(get_table_objclass((lua_State *)(uintptr_t)a));}
case 73:{return(uint64_t)(uintptr_t)(find_objtype((lua_State *)(uintptr_t)a,(const char *)(uintptr_t)b,(char)(uintptr_t)c));}
case 74:{return(uint64_t)(uintptr_t)(get_table_objtype((lua_State *)(uintptr_t)a));}
case 75:{return(uint64_t)(uintptr_t)(lspo_object((lua_State *)(uintptr_t)a));}
case 76:{return(uint64_t)(uintptr_t)(lspo_level_flags((lua_State *)(uintptr_t)a));}
case 77:{return(uint64_t)(uintptr_t)(lspo_level_init((lua_State *)(uintptr_t)a));}
case 78:{return(uint64_t)(uintptr_t)(lspo_engraving((lua_State *)(uintptr_t)a));}
case 79:{return(uint64_t)(uintptr_t)(lspo_mineralize((lua_State *)(uintptr_t)a));}
case 80:{return(uint64_t)(uintptr_t)(get_mkroom_name((int)(uintptr_t)a));}
case 81:{return(uint64_t)(uintptr_t)(get_table_roomtype_opt((lua_State *)(uintptr_t)a,(const char *)(uintptr_t)b,(int)(uintptr_t)c));}
case 82:{return(uint64_t)(uintptr_t)(lspo_room((lua_State *)(uintptr_t)a));}
case 83:{spo_endroom((struct sp_coder *)(uintptr_t)a);return 0;}
case 84:{return(uint64_t)(uintptr_t)(good_stair_loc((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));}
case 85:{return(uint64_t)(uintptr_t)(l_create_stairway((lua_State *)(uintptr_t)a,(boolean)(uintptr_t)b));}
case 86:{return(uint64_t)(uintptr_t)(lspo_stair((lua_State *)(uintptr_t)a));}
case 87:{return(uint64_t)(uintptr_t)(lspo_ladder((lua_State *)(uintptr_t)a));}
case 88:{return(uint64_t)(uintptr_t)(lspo_grave((lua_State *)(uintptr_t)a));}
case 89:{return(uint64_t)(uintptr_t)(lspo_altar((lua_State *)(uintptr_t)a));}
case 90:{return(uint64_t)(uintptr_t)(get_table_traptype_opt((lua_State *)(uintptr_t)a,(const char *)(uintptr_t)b,(int)(uintptr_t)c));}
case 91:{return(uint64_t)(uintptr_t)(get_trapname_bytype((int)(uintptr_t)a));}
case 92:{return(uint64_t)(uintptr_t)(get_traptype_byname((const char *)(uintptr_t)a));}
case 93:{return(uint64_t)(uintptr_t)(lspo_trap((lua_State *)(uintptr_t)a));}
case 94:{return(uint64_t)(uintptr_t)(lspo_gold((lua_State *)(uintptr_t)a));}
case 95:{return(uint64_t)(uintptr_t)(lspo_corridor((lua_State *)(uintptr_t)a));}
case 96:{return(uint64_t)(uintptr_t)(lspo_random_corridors((lua_State *)(uintptr_t)a));}
case 97:{return(uint64_t)(uintptr_t)(random_wdir());}
case 98:{return(uint64_t)(uintptr_t)(floodfillchk_match_under((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));}
case 99:{set_floodfillchk_match_under((coordxy)(uintptr_t)a);return 0;}
case 100:{return(uint64_t)(uintptr_t)(floodfillchk_match_accessible((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));}
case 101:{sel_set_ter((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(genericptr_t)(uintptr_t)c);return 0;}
case 102:{sel_set_feature((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(genericptr_t)(uintptr_t)c);return 0;}
case 103:{sel_set_door((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(genericptr_t)(uintptr_t)c);return 0;}
case 104:{return(uint64_t)(uintptr_t)(lspo_door((lua_State *)(uintptr_t)a));}
case 105:{l_table_getset_feature_flag((lua_State *)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c,(const char *)(uintptr_t)d,(int)(uintptr_t)e);return 0;}
case 106:{cvt_to_abscoord((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b);return 0;}
case 107:{cvt_to_relcoord((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b);return 0;}
case 108:{return(uint64_t)(uintptr_t)(nhl_abs_coord((lua_State *)(uintptr_t)a));}
case 109:{return(uint64_t)(uintptr_t)(lspo_feature((lua_State *)(uintptr_t)a));}
case 110:{return(uint64_t)(uintptr_t)(lspo_gas_cloud((lua_State *)(uintptr_t)a));}
case 111:{return(uint64_t)(uintptr_t)(lspo_terrain((lua_State *)(uintptr_t)a));}
case 112:{return(uint64_t)(uintptr_t)(lspo_replace_terrain((lua_State *)(uintptr_t)a));}
case 113:{return(uint64_t)(uintptr_t)(generate_way_out_method((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(struct selectionvar *)(uintptr_t)c));}
case 114:{ensure_way_out();return 0;}
case 115:{return(uint64_t)(uintptr_t)(get_table_intarray_entry((lua_State *)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c));}
case 116:{return(uint64_t)(uintptr_t)(get_table_region((lua_State *)(uintptr_t)a,(const char *)(uintptr_t)b,(lua_Integer *)(uintptr_t)c,(lua_Integer *)(uintptr_t)d,(lua_Integer *)(uintptr_t)e,(lua_Integer *)(uintptr_t)f,(boolean)(uintptr_t)g));}
case 117:{return(uint64_t)(uintptr_t)(get_coord((lua_State *)(uintptr_t)a,(int)(uintptr_t)b,(lua_Integer *)(uintptr_t)c,(lua_Integer *)(uintptr_t)d));}
case 118:{levregion_add((lev_region *)(uintptr_t)a);return 0;}
case 119:{l_get_lregion((lua_State *)(uintptr_t)a,(lev_region *)(uintptr_t)b);return 0;}
case 120:{return(uint64_t)(uintptr_t)(lspo_teleport_region((lua_State *)(uintptr_t)a));}
case 121:{return(uint64_t)(uintptr_t)(lspo_levregion((lua_State *)(uintptr_t)a));}
case 122:{return(uint64_t)(uintptr_t)(lspo_exclusion((lua_State *)(uintptr_t)a));}
case 123:{sel_set_lit((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(genericptr_t)(uintptr_t)c);return 0;}
case 124:{add_doors_to_room((struct mkroom *)(uintptr_t)a);return 0;}
case 125:{get_table_coords_or_region((lua_State *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(coordxy *)(uintptr_t)c,(coordxy *)(uintptr_t)d,(coordxy *)(uintptr_t)e);return 0;}
case 126:{return(uint64_t)(uintptr_t)(lspo_region((lua_State *)(uintptr_t)a));}
case 127:{return(uint64_t)(uintptr_t)(lspo_drawbridge((lua_State *)(uintptr_t)a));}
case 128:{return(uint64_t)(uintptr_t)(lspo_mazewalk((lua_State *)(uintptr_t)a));}
case 129:{return(uint64_t)(uintptr_t)(lspo_wall_property((lua_State *)(uintptr_t)a));}
case 130:{set_wallprop_in_selection((lua_State *)(uintptr_t)a,(int)(uintptr_t)b);return 0;}
case 131:{return(uint64_t)(uintptr_t)(lspo_non_diggable((lua_State *)(uintptr_t)a));}
case 132:{return(uint64_t)(uintptr_t)(lspo_non_passwall((lua_State *)(uintptr_t)a));}
case 133:{return(uint64_t)(uintptr_t)(lspo_wallify((lua_State *)(uintptr_t)a));}
case 134:{return(uint64_t)(uintptr_t)(lspo_reset_level((lua_State *)(uintptr_t)a));}
case 135:{return(uint64_t)(uintptr_t)(lspo_finalize_level((lua_State *)(uintptr_t)a));}
case 136:{return(uint64_t)(uintptr_t)(lspo_map((lua_State *)(uintptr_t)a));}
case 137:{update_croom();return 0;}
case 138:{struct sp_coder*p=sp_level_coder_init();if(p)tag(p,5);return(uintptr_t)p;}
case 139:{l_register_des((lua_State *)(uintptr_t)a);return 0;}
case 140:{create_des_coder();return 0;}
case 141:{return(uint64_t)(uintptr_t)(load_special((const char *)(uintptr_t)a));}
default:abort();}}
static int fixture_lua_dispatch(lua_State*L){int which=(int)lua_tointeger(L,lua_upvalueindex(1));return(int)probe_action(which,(uintptr_t)L,0,0,0,0,0,0,0);}
int probe_invoke_lua(int which){int n=lua_gettop(probe_L);lua_pushinteger(probe_L,which);lua_pushcclosure(probe_L,fixture_lua_dispatch,1);lua_insert(probe_L,1);return lua_pcall(probe_L,n,LUA_MULTRET,0);}
uintptr_t probe_selection(void){return(uintptr_t)l_selection_check(probe_L,1);}
void probe_reset(void){if(probe_L){lua_close(probe_L);probe_L=0;}for(int i=0;i<blockcount;i++)if(blocks[i].live)__real_free(blocks[i].p);blockcount=0;traceused=0;tracebuf[0]=0;result=grow=reentry=lua_fail=0;query=1;rngvalue=0;cursor=0;
memset(buffers,0,sizeof buffers);
memset(templates_mon,0,sizeof templates_mon);
memset(templates_obj,0,sizeof templates_obj);
memset(objpool,0,sizeof objpool);
memset(monpool,0,sizeof monpool);
memset(rooms_pool,0,sizeof rooms_pool);
memset(coordpool,0,sizeof coordpool);
memset(longcells,0,sizeof longcells);
memset(ptrcells,0,sizeof ptrcells);
memset(corridors,0,sizeof corridors);
memset(fragments,0,sizeof fragments);
memset(regionpool,0,sizeof regionpool);
memset(initpool,0,sizeof initpool);
memset(trappool,0,sizeof trappool);
memset(roompool,0,sizeof roompool);
memset(doorpool,0,sizeof doorpool);
memset(altarpool,0,sizeof altarpool);
memset(lregionpool,0,sizeof lregionpool);
memset(terrainpool,0,sizeof terrainpool);
memset(valueout,0,sizeof valueout);
memset((void*)&gx,0,sizeof gx);
memset((void*)&gy,0,sizeof gy);
memset((void*)&svl,0,sizeof svl);
memset((void*)&uball,0,sizeof uball);
memset((void*)&u,0,sizeof u);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&gs,0,sizeof gs);
memset((void*)&gf,0,sizeof gf);
memset((void*)&gm,0,sizeof gm);
memset((void*)&head_engr,0,sizeof head_engr);
memset((void*)&gn,0,sizeof gn);
memset((void*)&gl,0,sizeof gl);
memset((void*)&svn,0,sizeof svn);
memset((void*)&gr,0,sizeof gr);
memset((void*)&svr,0,sizeof svr);
memset((void*)&gd,0,sizeof gd);
memset((void*)&svd,0,sizeof svd);
memset((void*)&gt,0,sizeof gt);
memset((void*)&sve,0,sizeof sve);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&svc,0,sizeof svc);
memset((void*)&gi,0,sizeof gi);
memset((void*)&svi,0,sizeof svi);
memset((void*)&svm,0,sizeof svm);
memset((void*)&gu,0,sizeof gu);
memset((void*)&obj_descr,0,sizeof obj_descr);
memset((void*)&objects,0,sizeof objects);
memset((void*)&gc,0,sizeof gc);
u.ux=u.uy=10;u.umonnum=PM_HUMAN;u.ulevel=10;u.uhp=u.uhpmax=20;u.uz.dnum=1;u.uz.dlevel=5;gx.xstart=1;gx.xsize=COLNO-1;gx.x_maze_max=COLNO-2;gy.ystart=0;gy.ysize=ROWNO;gy.y_maze_max=ROWNO-2;for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_class=FOOD_CLASS;objects[i].oc_name_idx=objects[i].oc_descr_idx=i;objects[i].oc_weight=10;obj_descr[i].oc_name=obj_descr[i].oc_descr="fixture";}gu.urace.mnum=PM_HUMAN;for(int i=0;i<8;i++){templates_mon[i].id=PM_HUMAN;templates_mon[i].class=-1;templates_mon[i].coord=11|(10L<<16);templates_mon[i].sp_amask=AM_SPLEV_RANDOM;templates_mon[i].has_invent=DEFAULT_INVENT;templates_obj[i].id=FOOD_RATION;templates_obj[i].class=FOOD_CLASS;templates_obj[i].coord=11|(10L<<16);templates_obj[i].corpsenm=NON_PM;templates_obj[i].quan=1;templates_obj[i].spe=-127;templates_obj[i].curse_state=-1;rooms_pool[i].lx=5;rooms_pool[i].ly=5;rooms_pool[i].hx=20;rooms_pool[i].hy=15;fragments[i].wid=fragments[i].hei=3;fragments[i].data=buffers+8192+i*16;memset(fragments[i].data,ROOM,9);corridors[i].src.room=-1;corridors[i].dest.room=-1;regionpool[i].x1=5;regionpool[i].y1=5;regionpool[i].x2=10;regionpool[i].y2=10;}create_lua();traceused=0;tracebuf[0]=0;}
uintptr_t probe_data(int i){switch(i){
case 0:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_splev_init_present;
#else
return(uintptr_t)&splev_init_present;
#endif
case 1:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_icedpools;
#else
return(uintptr_t)&icedpools;
#endif
case 2:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_SpLev_Map;
#else
return(uintptr_t)&SpLev_Map;
#endif
case 3:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_container_idx;
#else
return(uintptr_t)&container_idx;
#endif
case 4:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_container_obj;
#else
return(uintptr_t)&container_obj;
#endif
case 5:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_invent_carrying_monster;
#else
return(uintptr_t)&invent_carrying_monster;
#endif
case 6:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_is_ok_location_func;
#else
return(uintptr_t)&is_ok_location_func;
#endif
case 7:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_room_types;
#else
return(uintptr_t)&room_types;
#endif
case 8:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_trap_types;
#else
return(uintptr_t)&trap_types;
#endif
case 9:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_floodfillchk_match_under_typ;
#else
return(uintptr_t)&floodfillchk_match_under_typ;
#endif
case 10:
#ifdef HYBRID_SP_LEV
return(uintptr_t)&sp_lev_data_nhl_functions;
#else
return(uintptr_t)&nhl_functions;
#endif
default:abort();}}
uintptr_t probe_function(int i){switch(i){
case 0:return(uintptr_t)good_stair_loc;
case 1:return(uintptr_t)floodfillchk_match_under;
case 2:return(uintptr_t)sel_set_ter;
case 3:return(uintptr_t)floodfillchk_match_accessible;
case 4:return(uintptr_t)sel_set_lit;
case 5:return(uintptr_t)sel_set_wall_property;
case 6:return(uintptr_t)lspo_message;
case 7:return(uintptr_t)lspo_monster;
case 8:return(uintptr_t)lspo_object;
case 9:return(uintptr_t)lspo_level_flags;
case 10:return(uintptr_t)lspo_level_init;
case 11:return(uintptr_t)lspo_engraving;
case 12:return(uintptr_t)lspo_mineralize;
case 13:return(uintptr_t)lspo_door;
case 14:return(uintptr_t)lspo_stair;
case 15:return(uintptr_t)lspo_ladder;
case 16:return(uintptr_t)lspo_grave;
case 17:return(uintptr_t)lspo_altar;
case 18:return(uintptr_t)lspo_map;
case 19:return(uintptr_t)lspo_feature;
case 20:return(uintptr_t)lspo_terrain;
case 21:return(uintptr_t)lspo_replace_terrain;
case 22:return(uintptr_t)lspo_room;
case 23:return(uintptr_t)lspo_corridor;
case 24:return(uintptr_t)lspo_random_corridors;
case 25:return(uintptr_t)lspo_gold;
case 26:return(uintptr_t)lspo_trap;
case 27:return(uintptr_t)lspo_mazewalk;
case 28:return(uintptr_t)lspo_drawbridge;
case 29:return(uintptr_t)lspo_region;
case 30:return(uintptr_t)lspo_levregion;
case 31:return(uintptr_t)lspo_exclusion;
case 32:return(uintptr_t)lspo_wallify;
case 33:return(uintptr_t)lspo_wall_property;
case 34:return(uintptr_t)lspo_non_diggable;
case 35:return(uintptr_t)lspo_non_passwall;
case 36:return(uintptr_t)lspo_teleport_region;
case 37:return(uintptr_t)lspo_reset_level;
case 38:return(uintptr_t)lspo_finalize_level;
case 39:return(uintptr_t)lspo_gas_cloud;
default:abort();}}
const char*probe_string(int i){switch(i){
case 0:return "human";
case 1:return "fixture";
case 2:return "item";
case 3:return "floor";
case 4:return "";
case 5:return " of ";
case 6:return "\"%s\"";
case 7:return "<Null>";
case 8:return "Array entry #%i is %s, expected number";
case 9:return "Cannot create drawbridge.";
case 10:return "Erroneous map char";
case 11:return "Expected integer or \"random\" for \"%s\", got ";
case 12:return "Map data error";
case 13:return "Map requires either x,y or halign,valign params";
case 14:return "No more rects...";
case 15:return "Not a coordinate";
case 16:return "Not a region";
case 17:return "Room must have both w and h";
case 18:return "Room must have both x and y";
case 19:return "Too deeply nested rooms?!";
case 20:return "Too many rooms on new level!";
case 21:return "Unknown appear_as type";
case 22:return "Unknown level flag %s";
case 23:return "Unknown monster id";
case 24:return "Unknown montype";
case 25:return "Unknown object id";
case 26:return "Unknown room type '%s'";
case 27:return "Unknown trap type";
case 28:return "Unrecognized level init style.";
case 29:return "Wizard appearance";
case 30:return "Wrong parameters";
case 31:return "achievement";
case 32:return "adjacentok";
case 33:return "align";
case 34:return "all";
case 35:return "altar";
case 36:return "amount";
case 37:return "anthole";
case 38:return "anti magic";
case 39:return "appear_as";
case 40:return "arboreal";
case 41:return "armor shop";
case 42:return "arrival_room";
case 43:return "arrow";
case 44:return "asleep";
case 45:return "avenge";
case 46:return "barracks";
case 47:return "bear";
case 48:return "beehive";
case 49:return "bg";
case 50:return "blessed";
case 51:return "blinded";
case 52:return "blood";
case 53:return "board";
case 54:return "book shop";
case 55:return "both";
case 56:return "bottom";
case 57:return "branch";
case 58:return "broken";
case 59:return "buc";
case 60:return "build_room";
case 61:return "buried";
case 62:return "burn";
case 63:return "cancelled";
case 64:return "candle shop";
case 65:return "center";
case 66:return "chameleon shape";
case 67:return "chance";
case 68:return "chaos";
case 69:return "check_room";
case 70:return "class";
case 71:return "closed";
case 72:return "coaligned";
case 73:return "cocknest";
case 74:return "cold";
case 75:return "confused";
case 76:return "contents";
case 77:return "coord";
case 78:return "corridor";
case 79:return "corrmaze";
case 80:return "corrwid";
case 81:return "countbirth";
case 82:return "create_altar";
case 83:return "create_corridor to/from a random wall";
case 84:return "create_door";
case 85:return "create_door: Can't find a proper place!";
case 86:return "create_monster";
case 87:return "create_monster: can't find feature \"%s\"";
case 88:return "create_monster: can't find object \"%s\"";
case 89:return "create_monster: invalid %s (\"%s\")";
case 90:return "create_monster: mon has an appearance, \"%s\", but no type";
case 91:return "create_monster: unimplemented mon appear type [%d,\"%s\"]";
case 92:return "create_monster: unknown monster class '%c'";
case 93:return "create_object:  unexpected object class '%c'";
case 94:return "create_object: too deeply nested containers.";
case 95:return "create_object: unknown achievement (%s\"%s\")";
case 96:return "create_room";
case 97:return "create_subroom";
case 98:return "cursed";
case 99:return "damage";
case 100:return "dart";
case 101:return "deadends";
case 102:return "degrade";
case 103:return "delphi";
case 104:return "des";
case 105:return "destdoor";
case 106:return "destroom";
case 107:return "destwall";
case 108:return "dig_corridor";
case 109:return "dig_corridor: bad coords <%d,%d> <%d,%d>.";
case 110:return "dir";
case 111:return "dishwasher";
case 112:return "door";
case 113:return "door coord not ok";
case 114:return "down";
case 115:return "drawbridge";
case 116:return "drawbridge coord not ok";
case 117:return "dust";
case 118:return "east";
case 119:return "empty";
case 120:return "engrave";
case 121:return "engraving";
case 122:return "eroded";
case 123:return "exclude";
case 124:return "exclude_islev";
case 125:return "exclusion";
case 126:return "expected string params";
case 127:return "falling rock";
case 128:return "feature";
case 129:return "feature has unknown type param.";
case 130:return "female";
case 131:return "fg";
case 132:return "fill_empty_maze";
case 133:return "fill_special_room";
case 134:return "filled";
case 135:return "filling";
case 136:return "finalize_level";
case 137:return "find_montype";
case 138:return "fire";
case 139:return "fleeing";
case 140:return "flip_level_rnd";
case 141:return "food shop";
case 142:return "fountain";
case 143:return "fromterrain";
case 144:return "fumaroles";
case 145:return "gas_cloud";
case 146:return "gem_prob";
case 147:return "generate_way_out_method";
case 148:return "get_free_room_loc:  can't find a place!";
case 149:return "get_location";
case 150:return "get_location:  can't find a place!";
case 151:return "get_mkroom_name unknown rtype %d";
case 152:return "get_room_loc";
case 153:return "get_room_loc : can't find a place!";
case 154:return "gold";
case 155:return "gold_prob";
case 156:return "grave";
case 157:return "graveyard";
case 158:return "greased";
case 159:return "group";
case 160:return "guardobjects";
case 161:return "h";
case 162:return "half-left";
case 163:return "half-right";
case 164:return "halign";
case 165:return "hardfloor";
case 166:return "health food shop";
case 167:return "height";
case 168:return "historic";
case 169:return "hole";
case 170:return "hot";
case 171:return "icedpools";
case 172:return "id";
case 173:return "ignorewater";
case 174:return "inaccessibles";
case 175:return "inventory";
case 176:return "invisible";
case 177:return "irregular";
case 178:return "joined";
case 179:return "keep_default_invent";
case 180:return "kelp_moat";
case 181:return "kelp_pool";
case 182:return "l_table_getset_feature_flag";
case 183:return "ladder";
case 184:return "laid_by_you";
case 185:return "land mine";
case 186:return "launchfrom";
case 187:return "law";
case 188:return "left";
case 189:return "leprehall";
case 190:return "level teleport";
case 191:return "level_flags";
case 192:return "level_init";
case 193:return "levregion";
case 194:return "lit";
case 195:return "locked";
case 196:return "looted";
case 197:return "lspo_drawbridge";
case 198:return "lspo_gold";
case 199:return "lspo_map";
case 200:return "lspo_message";
case 201:return "lspo_monster";
case 202:return "lspo_object";
case 203:return "lspo_region";
case 204:return "lspo_replace_terrain";
case 205:return "lspo_room";
case 206:return "lvlfill_swamp";
case 207:return "m_lev_adj";
case 208:return "magic";
case 209:return "magic portal";
case 210:return "male";
case 211:return "map";
case 212:return "mapfragment";
case 213:return "mapfragment center must be valid terrain";
case 214:return "mapfragment error";
case 215:return "mapfragment needs to have odd height and width";
case 216:return "mark";
case 217:return "maze";
case 218:return "maze1xy";
case 219:return "mazegrid";
case 220:return "mazelevel";
case 221:return "mazewalk";
case 222:return "mazewalk coord not ok";
case 223:return "mazewalk: Bad direction";
case 224:return "message";
case 225:return "mimic appearance";
case 226:return "mineralize";
case 227:return "mines";
case 228:return "mines end";
case 229:return "mon:";
case 230:return "monster";
case 231:return "monster-generation";
case 232:return "montype";
case 233:return "morgue";
case 234:return "multiple prizes on %s level";
case 235:return "name";
case 236:return "needjoining";
case 237:return "neutral";
case 238:return "nhl_abs_coord: Wrong args";
case 239:return "noalign";
case 240:return "noautosearch";
case 241:return "nodeathdrops";
case 242:return "nodoor";
case 243:return "noflip";
case 244:return "noflipx";
case 245:return "noflipy";
case 246:return "nommap";
case 247:return "nomongen";
case 248:return "non-table coord specified";
case 249:return "non_diggable";
case 250:return "non_passwall";
case 251:return "noncoaligned";
case 252:return "noncoalignment";
case 253:return "nondiggable";
case 254:return "none";
case 255:return "nonpasswall";
case 256:return "north";
case 257:return "not-blessed";
case 258:return "not-cursed";
case 259:return "not-uncursed";
case 260:return "noteleport";
case 261:return "obj:";
case 262:return "object";
case 263:return "open";
case 264:return "ordinary";
case 265:return "outside mapfrag (%i,%i), wanted (%i,%i)";
case 266:return "padding";
case 267:return "paralyzed";
case 268:return "peaceful";
case 269:return "pit";
case 270:return "polymorph";
case 271:return "pool";
case 272:return "portal";
case 273:return "pos";
case 274:return "potion of ";
case 275:return "potion shop";
case 276:return "premapped";
case 277:return "property";
case 278:return "pudding";
case 279:return "quantity";
case 280:return "random";
case 281:return "random_corridors";
case 282:return "random_wdir";
case 283:return "recharged";
case 284:return "region";
case 285:return "region as subroom";
case 286:return "region needs region";
case 287:return "region_islev";
case 288:return "replace_terrain";
case 289:return "reset_level";
case 290:return "revived";
case 291:return "right";
case 292:return "ring";
case 293:return "ring of ";
case 294:return "ring shop";
case 295:return "rnddoor";
case 296:return "rndtrap";
case 297:return "rogue";
case 298:return "rolling boulder";
case 299:return "room";
case 300:return "rust";
case 301:return "sanctum";
case 302:return "scroll of ";
case 303:return "scroll shop";
case 304:return "search_door: Bad wall!";
case 305:return "secret";
case 306:return "seen";
case 307:return "selection";
case 308:return "shop";
case 309:return "shortsighted";
case 310:return "shrine";
case 311:return "shroud";
case 312:return "sink";
case 313:return "sleep gas";
case 314:return "smoothed";
case 315:return "sokoban";
case 316:return "sokoban end";
case 317:return "solidfill";
case 318:return "solidify";
case 319:return "south";
case 320:return "sp_lev.c";
case 321:return "spe";
case 322:return "spellbook of ";
case 323:return "spider_on_web";
case 324:return "spiked pit";
case 325:return "spinach";
case 326:return "splev_initlev";
case 327:return "srcdoor";
case 328:return "srcroom";
case 329:return "srcwall";
case 330:return "stair";
case 331:return "stair-down";
case 332:return "stair-up";
case 333:return "state";
case 334:return "statue";
case 335:return "stocked";
case 336:return "stormy";
case 337:return "strange area [%d,%d] in check_room.";
case 338:return "stunned";
case 339:return "style";
case 340:return "swamp";
case 341:return "swarm";
case 342:return "tail";
case 343:return "teledest";
case 344:return "teleport";
case 345:return "teleport-down";
case 346:return "teleport-up";
case 347:return "teleport_region";
case 348:return "temperate";
case 349:return "temple";
case 350:return "ter:";
case 351:return "terrain";
case 352:return "terrain coord not ok";
case 353:return "text";
case 354:return "themed";
case 355:return "throne";
case 356:return "tool shop";
case 357:return "top";
case 358:return "toterrain";
case 359:return "trap";
case 360:return "trap door";
case 361:return "trap_known";
case 362:return "trapped";
case 363:return "tree";
case 364:return "ttl";
case 365:return "typ";
case 366:return "type";
case 367:return "uncursed";
case 368:return "unknown";
case 369:return "unlit";
case 370:return "up";
case 371:return "valign";
case 372:return "vampire shape";
case 373:return "vault";
case 374:return "vibrating square";
case 375:return "victim";
case 376:return "w";
case 377:return "waiting";
case 378:return "wall";
case 379:return "wall_property";
case 380:return "walled";
case 381:return "wallify";
case 382:return "wallthick";
case 383:return "wand of ";
case 384:return "wand shop";
case 385:return "warned";
case 386:return "weapon shop";
case 387:return "web";
case 388:return "west";
case 389:return "width";
case 390:return "wrong parameters";
case 391:return "x";
case 392:return "x1";
case 393:return "x2";
case 394:return "xalign";
case 395:return "y";
case 396:return "y1";
case 397:return "y2";
case 398:return "yalign";
case 399:return "zoo";
default:return 0;}}
int probe_string_count(void){return 400;}
size_t probe_string_capacity(int i){const char*p=probe_string(i);return p?strlen(p)+1:0;}
