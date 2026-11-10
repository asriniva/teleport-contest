/* Controlled VISION world boundaries. Original vision.c is included unchanged
 * for the oracle. All grid/workspace/callback storage uses actual native types;
 * dependencies below do not implement line-of-sight or visibility policy. */
#include "hack.h"
extern const coordxy circle_data[137],circle_start[16];
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <emscripten/stack.h>
__typeof__(flags) flags; __typeof__(iflags) iflags; struct you u;
__typeof__(gi) gi; __typeof__(gs) gs; __typeof__(gv) gv;
__typeof__(svc) svc; __typeof__(svd) svd; __typeof__(svl) svl;
__typeof__(svr) svr; __typeof__(program_state) program_state;
/* Actual display.c external dependency initializer, source-projected by test. */
const seenV seenv_matrix[3][3] = {
    { SV2, SV1,   SV0 },
    { SV3, SVALL, SV7 },
    { SV4, SV5,   SV6 }
};
static int startup_circle[2];
static void __attribute__((constructor)) circle_startup_witness(void){startup_circle[0]=circle_data[136];startup_circle[1]=circle_start[15];}
int probe_startup_circle(int which){return startup_circle[which];}
static struct monst monsters[8];static struct obj items[8];
static char traces[4194304],snapshot[131072];static int ti,si,opts[32],calls;
static uintptr_t opaque_payload;
void probe_payload(uint64_t value){opaque_payload=value;}
static void *grown;static seenV **outrows;static coordxy *outmin,*outmax;
static void visit(coordxy,coordxy,genericptr_t);
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(traces+ti,sizeof traces-ti,fmt,ap);va_end(ap);if(n<0||n+ti>=sizeof traces)abort();ti+=n;}
static void observe(void){calls++;if(opts[10]&&calls==opts[10]){grown=malloc(48*1024*1024);if(!grown)abort();append("growth;");}if(opts[11]&&calls==opts[11])append("reentry:%d;",get_viz_clear(10,10));}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d:%u;",x,y,gv.viz_array?gv.viz_array[y][x]:0);observe();}
void notice_all_mons(boolean force){append("notice:%d;",force);observe();}
void do_light_sources(seenV **rows){append("lights;");if(opts[1])rows[opts[2]][opts[3]]|=TEMP_LIT;observe();}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
boolean is_moat(coordxy x,coordxy y){return levl[x][y].typ==MOAT;}
boolean is_pool(coordxy x,coordxy y){return levl[x][y].typ==POOL||levl[x][y].typ==MOAT||levl[x][y].typ==WATER;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
NhRegion *visible_region_at(coordxy x,coordxy y){return opts[0]&&x==opts[2]&&y==opts[3]?(NhRegion*)(uintptr_t)1:0;}
int canseemon(struct monst*m){append("canseemon:%ld;",(long)(m-monsters));return opts[4];}
int mon_visible(struct monst*m){append("visible:%ld;",(long)(m-monsters));return opts[5];}
int see_with_infrared(struct monst*m){append("infrared:%ld;",(long)(m-monsters));return opts[6];}
int tp_sensemon(struct monst*m){append("telepathy:%ld;",(long)(m-monsters));return opts[7];}
boolean worm_known(struct monst*m){append("worm:%ld;",(long)(m-monsters));return opts[8];}
boolean detecting(void(*fn)(coordxy,coordxy,void*)){append("detecting:%d;",fn==visit);return opts[9];}
boolean debugcore(const char*file,boolean wild){append("debug:%s:%d;",file,wild);return opts[12];}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);vfprintf(stderr,fmt,ap);va_end(ap);abort();}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/vision.c"
#else
extern void*teleport_vision_storage(int);
extern void teleport_vision_test_get_unused_cs(seenV***,coordxy**,coordxy**);
extern void teleport_vision_test_rogue_vision(seenV**,coordxy*,coordxy*);
extern void teleport_vision_test_dig_point(int,int),teleport_vision_test_fill_point(int,int),teleport_vision_test_view_init(void);
extern void teleport_vision_test_right_side(int,int,int,const coordxy*),teleport_vision_test_left_side(int,int,int,const coordxy*);
extern void teleport_vision_test_view_from(coordxy,coordxy,seenV**,coordxy*,coordxy*,int,void(*)(coordxy,coordxy,genericptr_t),genericptr_t);
#define get_unused_cs teleport_vision_test_get_unused_cs
#define rogue_vision teleport_vision_test_rogue_vision
#define dig_point teleport_vision_test_dig_point
#define fill_point teleport_vision_test_fill_point
#define view_init teleport_vision_test_view_init
#define right_side teleport_vision_test_right_side
#define left_side teleport_vision_test_left_side
#define view_from teleport_vision_test_view_from
#define could_see (*(seenV(*)[2][ROWNO][COLNO])teleport_vision_storage(0))
#define cs_rows0 (*(seenV*(*)[ROWNO])teleport_vision_storage(1))
#define cs_rows1 (*(seenV*(*)[ROWNO])teleport_vision_storage(2))
#define cs_rmin0 (*(coordxy(*)[ROWNO])teleport_vision_storage(3))
#define cs_rmax0 (*(coordxy(*)[ROWNO])teleport_vision_storage(4))
#define cs_rmin1 (*(coordxy(*)[ROWNO])teleport_vision_storage(5))
#define cs_rmax1 (*(coordxy(*)[ROWNO])teleport_vision_storage(6))
#define viz_clear (*(char(*)[ROWNO][COLNO])teleport_vision_storage(7))
#define viz_clear_rows (*(char*(*)[ROWNO])teleport_vision_storage(8))
#define left_ptrs (*(coordxy(*)[ROWNO][COLNO])teleport_vision_storage(9))
#define right_ptrs (*(coordxy(*)[ROWNO][COLNO])teleport_vision_storage(10))
#define start_row (*(int*)teleport_vision_storage(11))
#define start_col (*(int*)teleport_vision_storage(12))
#define step (*(int*)teleport_vision_storage(13))
#define cs_rows (*(seenV***)teleport_vision_storage(14))
#define cs_left (*(coordxy**)teleport_vision_storage(15))
#define cs_right (*(coordxy**)teleport_vision_storage(16))
#define vis_func (*(void(**)(coordxy,coordxy,genericptr_t))teleport_vision_storage(17))
#define varg (*(genericptr_t*)teleport_vision_storage(18))
#endif
#include "tu-vision-layout.h"
size_t probe_context_size(void){return sizeof(could_see);}
int probe_layout_count(void){return SIZE(teleport_vision_layout);}
const char*probe_layout_name(int i){return teleport_vision_layout[i].name;}
size_t probe_layout_value(int i){return teleport_vision_layout[i].value;}
int probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return traces;}
int probe_foreign_circle(int table,int i){return table?circle_start[i]:circle_data[i];}
static void visit(coordxy x,coordxy y,genericptr_t arg){append("visit:%d:%d:%llu;",x,y,(unsigned long long)(uintptr_t)arg);observe();if(opts[13]&&calls==opts[13])block_point(x,y);}
void probe_reset(void){monst_globals_init();if(grown){free(grown);grown=0;}memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&u,0,sizeof u);memset(&gi,0,sizeof gi);memset(&gs,0,sizeof gs);memset(&gv,0,sizeof gv);memset(&svc,0,sizeof svc);memset(&svd,0,sizeof svd);memset(&svl,0,sizeof svl);memset(&svr,0,sizeof svr);memset(&program_state,0,sizeof program_state);memset(monsters,0,sizeof monsters);memset(items,0,sizeof items);memset(opts,0,sizeof opts);memset(could_see,0,sizeof could_see);memset(left_ptrs,0,sizeof left_ptrs);memset(right_ptrs,0,sizeof right_ptrs);memset(viz_clear,0,sizeof viz_clear);start_row=start_col=step=0;cs_rows=0;cs_left=cs_right=0;vis_func=0;varg=0;outrows=0;outmin=outmax=0;u.ux=40;u.uy=10;u.uz=(d_level){2,3};u.xray_range=-1;u.nv_range=1;rogue_level=(d_level){8,9};water_level=(d_level){7,8};air_level=(d_level){6,7};for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=x?ROOM:STONE;for(int i=0;i<8;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].mx=40+i;monsters[i].my=10;items[i].otyp=BOULDER;}calls=ti=0;opaque_payload=0;traces[0]=0;}
void probe_option(int i,int value){opts[i]=value;}
void probe_hero(int i,long v){switch(i){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.nv_range=v;break;case 3:u.xray_range=v;break;case 4:u.uswallow=v;break;case 5:u.uinwater=v;break;case 6:u.utrap=v;break;case 7:u.utraptype=v;break;case 8:iflags.vision_inited=v;break;case 9:gi.in_mklev=v;break;case 10:program_state.in_getlev=v;break;case 11:program_state.panicking=v;break;case 12:flags.debug=v;break;case 13:u.uz=rogue_level;break;case 14:u.uz=water_level;break;case 15:u.uz=air_level;break;case 16:svc.context.warntype.obj=v;break;case 17:svc.context.warntype.polyd=v;break;case 18:svc.context.warntype.species=&mons[v];break;case 19:gv.vision_full_recalc=v;break;default:abort();}}
void probe_property(int n,int field,long value){switch(field){case 0:u.uprops[n].intrinsic=value;break;case 1:u.uprops[n].extrinsic=value;break;case 2:u.uprops[n].blocked=value;break;default:abort();}}
void probe_tile(int x,int y,int field,int value){struct rm*p=&levl[x][y];switch(field){case 0:p->typ=value;break;case 1:p->lit=value;break;case 2:p->waslit=value;break;case 3:p->seenv=value;break;case 4:p->doormask=value;break;case 5:p->roomno=value;break;default:abort();}}
void probe_set_monster(int i,int field,long value){struct monst*p=&monsters[i];switch(field){case 0:p->mx=value;break;case 1:p->my=value;break;case 2:p->minvis=value;break;case 3:p->m_ap_type=value;break;case 4:p->mappearance=value;break;case 5:p->wormno=value;break;case 6:p->data=&mons[value];break;case 7:svl.level.monsters[p->mx][p->my]=value?p:0;break;default:abort();}}
void probe_object(int i,int x,int y,int type){items[i].otyp=type;items[i].nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=&items[i];}
void probe_room(int lx,int hx,int ly,int hy,int lit){svr.rooms[0].lx=lx;svr.rooms[0].hx=hx;svr.rooms[0].ly=ly;svr.rooms[0].hy=hy;svr.rooms[0].rlit=lit;}
long probe_action(int op,int a,int b,int c,int d,int e){switch(op){case 0:vision_init();break;case 1:vision_reset();break;case 2:return get_viz_clear(a,b);case 3:return does_block(a,b,&levl[a][b]);case 4:vision_recalc(a);break;case 5:block_point(a,b);break;case 6:unblock_point(a,b);break;case 7:recalc_block_point(a,b);break;case 8:return clear_path(a,b,c,d);case 9:if(a)get_unused_cs(&outrows,&outmin,&outmin);else get_unused_cs(&outrows,&outmin,&outmax);break;case 10:rogue_vision(cs_rows1,cs_rmin1,cs_rmax1);break;case 11:dig_point(a,b);break;case 12:fill_point(a,b);break;case 13:view_init();break;case 14:view_from(a,b,cs_rows1,cs_rmin1,cs_rmax1,c,d?visit:0,(genericptr_t)(opts[14]?opaque_payload:(uintptr_t)(unsigned)e));break;case 15:right_side(a,b,c,d?circle_ptr(d):0);break;case 16:left_side(a,b,c,d?circle_ptr(d):0);break;case 17:do_clear_area(a,b,c,visit,(genericptr_t)(opts[14]?opaque_payload:(uintptr_t)(unsigned)d));break;case 18:return howmonseen(&monsters[a]);default:abort();}return 0;}
static unsigned long norm(const void*p){if(!p)return 0;if(p==(void*)cs_rows0)return 1;if(p==(void*)cs_rows1)return 2;if(p==(void*)cs_rmin0)return 3;if(p==(void*)cs_rmax0)return 4;if(p==(void*)cs_rmin1)return 5;if(p==(void*)cs_rmax1)return 6;return (unsigned long)(uintptr_t)p;}
static void snap(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(snapshot+si,sizeof snapshot-si,fmt,ap);va_end(ap);if(n<0||si+n>=sizeof snapshot)abort();si+=n;}
static void hex(const void*p,size_t n){const unsigned char*b=p;for(size_t i=0;i<n;i++)snap("%02x",b[i]);snap(";");}
const char*probe_snapshot(void){si=0;hex(could_see,sizeof could_see);hex(viz_clear,sizeof viz_clear);hex(left_ptrs,sizeof left_ptrs);hex(right_ptrs,sizeof right_ptrs);hex(cs_rmin0,sizeof cs_rmin0);hex(cs_rmax0,sizeof cs_rmax0);hex(cs_rmin1,sizeof cs_rmin1);hex(cs_rmax1,sizeof cs_rmax1);hex(levl,sizeof svl.level.locations);snap("v:%lu,%lu,%lu,%d;s:%d,%d,%d,%lu,%lu,%lu,%d,%llu;o:%lu,%lu,%lu;",norm(gv.viz_array),norm(gv.viz_rmin),norm(gv.viz_rmax),gv.vision_full_recalc,start_row,start_col,step,norm(cs_rows),norm(cs_left),norm(cs_right),vis_func==visit,(unsigned long long)(uintptr_t)varg,norm(outrows),norm(outmin),norm(outmax));snap("g:%d,%d;",gs.seethru,iflags.vision_inited);for(int y=0;y<ROWNO;y++)snap("p:%ld,%ld,%ld;",cs_rows0[y]?(long)(cs_rows0[y]-could_see[0][y]):-1,cs_rows1[y]?(long)(cs_rows1[y]-could_see[1][y]):-1,viz_clear_rows[y]?(long)(viz_clear_rows[y]-viz_clear[y]):-1);return snapshot;}
int probe_value(int key,int x,int y){switch(key){case 0:return gv.viz_array?gv.viz_array[y][x]:0;case 1:return viz_clear[y][x];case 2:return left_ptrs[y][x];case 3:return right_ptrs[y][x];case 4:return gv.viz_rmin?gv.viz_rmin[y]:0;case 5:return gv.viz_rmax?gv.viz_rmax[y]:0;case 6:return levl[x][y].seenv;case 7:return levl[x][y].waslit;default:abort();}}
