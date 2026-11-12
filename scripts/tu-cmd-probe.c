/* CMD controlled dependency fixture: source bodies remain original C or JS. */
#include "hack.h"
#include "func_tab.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <emscripten.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(windowprocs) windowprocs;
__typeof__(gm) gm;
__typeof__(go) go;
__typeof__(gc) gc;
__typeof__(gi) gi;
__typeof__(iflags) iflags;
__typeof__(gl) gl;
__typeof__(nhcb_counts[0]) nhcb_counts[NUM_NHCB]={0};
__typeof__(nhcb_name[0]) nhcb_name[NUM_NHCB]={0};
__typeof__(flags) flags;
__typeof__(u) u;
__typeof__(ge) ge;
__typeof__(cg) cg={0};
__typeof__(nul_glyphinfo) nul_glyphinfo;
__typeof__(gy) gy;
__typeof__(mons) mons={[PM_HUMAN]={.pmidx=PM_HUMAN,.mlet=S_HUMAN,.mflags2=M2_HUMAN}};
__typeof__(hidespinchars[0]) hidespinchars[4]="hsq";
__typeof__(svl) svl;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(svd) svd;
__typeof__(svc) svc;
__typeof__(uball) uball;
__typeof__(svu) svu;
__typeof__(gv) gv;
__typeof__(a11y) a11y;
__typeof__(xdir[0]) xdir[N_DIRS_Z]={-1,-1,0,1,1,1,0,-1,0,0};
__typeof__(ydir[0]) ydir[N_DIRS_Z]={0,-1,-1,-1,0,1,1,1,0,0};
__typeof__(zdir[0]) zdir[N_DIRS_Z]={0,0,0,0,0,0,0,0,1,-1};
__typeof__(gd) gd;
__typeof__(program_state) program_state;
__typeof__(gt) gt;
__typeof__(gk) gk;
__typeof__(c_common_strings) c_common_strings={.c_Never_mind="Never mind."};
__typeof__(quitchars[0]) quitchars[5]=" \r\n\033";
__typeof__(dirs_ord[0]) dirs_ord[N_DIRS]={DIR_W,DIR_N,DIR_E,DIR_S,DIR_NW,DIR_NE,DIR_SE,DIR_SW};
__typeof__(defsyms) defsyms;
__typeof__(gu) gu;
__typeof__(soundprocs) soundprocs;
__typeof__(ynchars[0]) ynchars[3]="yn";
__typeof__(ynqchars[0]) ynqchars[4]="ynq";
__typeof__(ynaqchars[0]) ynaqchars[5]="ynaq";
__typeof__(rightleftchars[0]) rightleftchars[3]="rl";
__typeof__(gs) gs;
__typeof__(urealtime) urealtime;
static struct obj objpool[8];static struct monst monpool[8];static struct _cmd_queue queuepool[8];static struct Cmd_bind bindpool[8];static struct nh_file filepool;static stairway stairpool;static struct selectionvar selpool;static coord coords[8];static _Alignas(void*) char buffers[16384];static long counts[8];static void*ptrs[8];static char tracebuf[524288];static size_t traceused;static int result,rngvalue,query,grow,reentry,inputpos,extindex=-1,selection_index,interesting;static char inputs[1024];static jmp_buf escape;static coord*watched;
struct block{void*p;size_t n;int live;};static struct block blocks[1024];static int blockcount;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);if(n<0||(size_t)n>=sizeof tracebuf-traceused)abort();traceused+=(size_t)n;}
static uint64_t token(const void*p){uintptr_t a=(uintptr_t)p;if(!p)return 0;
if(a>=(uintptr_t)&objpool&&a<(uintptr_t)&objpool+sizeof objpool)return 100000+a-(uintptr_t)&objpool;
if(a>=(uintptr_t)&monpool&&a<(uintptr_t)&monpool+sizeof monpool)return 200000+a-(uintptr_t)&monpool;
if(a>=(uintptr_t)&buffers&&a<(uintptr_t)&buffers+sizeof buffers)return 300000+a-(uintptr_t)&buffers;
if(a>=(uintptr_t)&queuepool&&a<(uintptr_t)&queuepool+sizeof queuepool)return 400000+a-(uintptr_t)&queuepool;
if(a>=(uintptr_t)&bindpool&&a<(uintptr_t)&bindpool+sizeof bindpool)return 500000+a-(uintptr_t)&bindpool;
if(a>=(uintptr_t)&coords&&a<(uintptr_t)&coords+sizeof coords)return 600000+a-(uintptr_t)&coords;
if(a>=(uintptr_t)&counts&&a<(uintptr_t)&counts+sizeof counts)return 700000+a-(uintptr_t)&counts;
if(a>=(uintptr_t)&ptrs&&a<(uintptr_t)&ptrs+sizeof ptrs)return 800000+a-(uintptr_t)&ptrs;
if(a>=(uintptr_t)&filepool&&a<(uintptr_t)&filepool+sizeof filepool)return 900000+a-(uintptr_t)&filepool;
if(a>=(uintptr_t)&stairpool&&a<(uintptr_t)&stairpool+sizeof stairpool)return 1000000+a-(uintptr_t)&stairpool;
if(a>=(uintptr_t)&selpool&&a<(uintptr_t)&selpool+sizeof selpool)return 1100000+a-(uintptr_t)&selpool;
if(a>=(uintptr_t)&windowprocs&&a<(uintptr_t)&windowprocs+sizeof windowprocs)return 2000000+a-(uintptr_t)&windowprocs;
if(a>=(uintptr_t)&gm&&a<(uintptr_t)&gm+sizeof gm)return 2100000+a-(uintptr_t)&gm;
if(a>=(uintptr_t)&go&&a<(uintptr_t)&go+sizeof go)return 2200000+a-(uintptr_t)&go;
if(a>=(uintptr_t)&gc&&a<(uintptr_t)&gc+sizeof gc)return 2300000+a-(uintptr_t)&gc;
if(a>=(uintptr_t)&gi&&a<(uintptr_t)&gi+sizeof gi)return 2400000+a-(uintptr_t)&gi;
if(a>=(uintptr_t)&iflags&&a<(uintptr_t)&iflags+sizeof iflags)return 2500000+a-(uintptr_t)&iflags;
if(a>=(uintptr_t)&gl&&a<(uintptr_t)&gl+sizeof gl)return 2600000+a-(uintptr_t)&gl;
if(a>=(uintptr_t)&nhcb_counts&&a<(uintptr_t)&nhcb_counts+sizeof nhcb_counts)return 2700000+a-(uintptr_t)&nhcb_counts;
if(a>=(uintptr_t)&nhcb_name&&a<(uintptr_t)&nhcb_name+sizeof nhcb_name)return 2800000+a-(uintptr_t)&nhcb_name;
if(a>=(uintptr_t)&flags&&a<(uintptr_t)&flags+sizeof flags)return 2900000+a-(uintptr_t)&flags;
if(a>=(uintptr_t)&u&&a<(uintptr_t)&u+sizeof u)return 3000000+a-(uintptr_t)&u;
if(a>=(uintptr_t)&ge&&a<(uintptr_t)&ge+sizeof ge)return 3100000+a-(uintptr_t)&ge;
if(a>=(uintptr_t)&cg&&a<(uintptr_t)&cg+sizeof cg)return 3200000+a-(uintptr_t)&cg;
if(a>=(uintptr_t)&nul_glyphinfo&&a<(uintptr_t)&nul_glyphinfo+sizeof nul_glyphinfo)return 3300000+a-(uintptr_t)&nul_glyphinfo;
if(a>=(uintptr_t)&gy&&a<(uintptr_t)&gy+sizeof gy)return 3400000+a-(uintptr_t)&gy;
if(a>=(uintptr_t)&mons&&a<(uintptr_t)&mons+sizeof mons)return 3500000+a-(uintptr_t)&mons;
if(a>=(uintptr_t)&hidespinchars&&a<(uintptr_t)&hidespinchars+sizeof hidespinchars)return 3600000+a-(uintptr_t)&hidespinchars;
if(a>=(uintptr_t)&svl&&a<(uintptr_t)&svl+sizeof svl)return 3700000+a-(uintptr_t)&svl;
if(a>=(uintptr_t)&WIN_MESSAGE&&a<(uintptr_t)&WIN_MESSAGE+sizeof WIN_MESSAGE)return 3800000+a-(uintptr_t)&WIN_MESSAGE;
if(a>=(uintptr_t)&svd&&a<(uintptr_t)&svd+sizeof svd)return 3900000+a-(uintptr_t)&svd;
if(a>=(uintptr_t)&svc&&a<(uintptr_t)&svc+sizeof svc)return 4000000+a-(uintptr_t)&svc;
if(a>=(uintptr_t)&uball&&a<(uintptr_t)&uball+sizeof uball)return 4100000+a-(uintptr_t)&uball;
if(a>=(uintptr_t)&svu&&a<(uintptr_t)&svu+sizeof svu)return 4200000+a-(uintptr_t)&svu;
if(a>=(uintptr_t)&gv&&a<(uintptr_t)&gv+sizeof gv)return 4300000+a-(uintptr_t)&gv;
if(a>=(uintptr_t)&a11y&&a<(uintptr_t)&a11y+sizeof a11y)return 4400000+a-(uintptr_t)&a11y;
if(a>=(uintptr_t)&xdir&&a<(uintptr_t)&xdir+sizeof xdir)return 4500000+a-(uintptr_t)&xdir;
if(a>=(uintptr_t)&ydir&&a<(uintptr_t)&ydir+sizeof ydir)return 4600000+a-(uintptr_t)&ydir;
if(a>=(uintptr_t)&zdir&&a<(uintptr_t)&zdir+sizeof zdir)return 4700000+a-(uintptr_t)&zdir;
if(a>=(uintptr_t)&gd&&a<(uintptr_t)&gd+sizeof gd)return 4800000+a-(uintptr_t)&gd;
if(a>=(uintptr_t)&program_state&&a<(uintptr_t)&program_state+sizeof program_state)return 4900000+a-(uintptr_t)&program_state;
if(a>=(uintptr_t)&gt&&a<(uintptr_t)&gt+sizeof gt)return 5000000+a-(uintptr_t)&gt;
if(a>=(uintptr_t)&gk&&a<(uintptr_t)&gk+sizeof gk)return 5100000+a-(uintptr_t)&gk;
if(a>=(uintptr_t)&c_common_strings&&a<(uintptr_t)&c_common_strings+sizeof c_common_strings)return 5200000+a-(uintptr_t)&c_common_strings;
if(a>=(uintptr_t)&quitchars&&a<(uintptr_t)&quitchars+sizeof quitchars)return 5300000+a-(uintptr_t)&quitchars;
if(a>=(uintptr_t)&dirs_ord&&a<(uintptr_t)&dirs_ord+sizeof dirs_ord)return 5400000+a-(uintptr_t)&dirs_ord;
if(a>=(uintptr_t)&defsyms&&a<(uintptr_t)&defsyms+sizeof defsyms)return 5500000+a-(uintptr_t)&defsyms;
if(a>=(uintptr_t)&gu&&a<(uintptr_t)&gu+sizeof gu)return 5600000+a-(uintptr_t)&gu;
if(a>=(uintptr_t)&soundprocs&&a<(uintptr_t)&soundprocs+sizeof soundprocs)return 5700000+a-(uintptr_t)&soundprocs;
if(a>=(uintptr_t)&ynchars&&a<(uintptr_t)&ynchars+sizeof ynchars)return 5900000+a-(uintptr_t)&ynchars;
if(a>=(uintptr_t)&ynqchars&&a<(uintptr_t)&ynqchars+sizeof ynqchars)return 6000000+a-(uintptr_t)&ynqchars;
if(a>=(uintptr_t)&ynaqchars&&a<(uintptr_t)&ynaqchars+sizeof ynaqchars)return 6100000+a-(uintptr_t)&ynaqchars;
if(a>=(uintptr_t)&rightleftchars&&a<(uintptr_t)&rightleftchars+sizeof rightleftchars)return 6200000+a-(uintptr_t)&rightleftchars;
if(a>=(uintptr_t)&gs&&a<(uintptr_t)&gs+sizeof gs)return 6300000+a-(uintptr_t)&gs;
if(a>=(uintptr_t)&urealtime&&a<(uintptr_t)&urealtime+sizeof urealtime)return 6400000+a-(uintptr_t)&urealtime;
for(int i=blockcount-1;i>=0;i--)if(a>=(uintptr_t)blocks[i].p&&a<(uintptr_t)blocks[i].p+blocks[i].n)return 10000000+(uint64_t)i*100000+a-(uintptr_t)blocks[i].p;return a;}
void __real_free(void*);void __wrap_free(void*p){if(!p)return;for(int i=blockcount-1;i>=0;i--)if(blocks[i].p==p){if(!blocks[i].live)abort();blocks[i].live=0;append("free:%d;",i);__real_free(p);return;}__real_free(p);}
static void*tracked(size_t n){if(blockcount==1024)abort();void*p=malloc(n);if(!p)abort();memset(p,0x5a,n);blocks[blockcount]=(struct block){p,n,1};append("alloc:%d:%zu;",blockcount,n);blockcount++;return p;}
static void hook(void){if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentry){reentry=0;(void)isok(1,1);}}
static int nextinput(void){return inputs[inputpos]?(unsigned char)inputs[inputpos++]:27;}
void (reset_remarm)(void){append("reset_remarm:;");}
void (reset_pick)(void){append("reset_pick:;");}
void (reset_trapset)(void){append("reset_trapset:;");}
long * (alloc)(unsigned int a0){return tracked(a0);}
int (lua_getglobal)(lua_State * a0,const char * a1){append("lua_getglobal:%lld:%s;",(long long)token((const void*)a0),(a1?a1:"NULL"));return 0;}
const char * (lua_pushstring)(lua_State * a0,const char * a1){append("lua_pushstring:%lld:%s;",(long long)token((const void*)a0),(a1?a1:"NULL"));return 0;}
int (nhl_pcall_handle)(lua_State * a0,int a1,int a2,const char * a3,NHL_pcall_action a4){append("nhl_pcall_handle:%lld:%lld:%lld:%s:%lld;",(long long)token((const void*)a0),(long long)a1,(long long)a2,(a3?a3:"NULL"),(long long)a4);return 0;}
int (lua_toboolean)(lua_State * a0,int a1){append("lua_toboolean:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);return 0;}
void (lua_settop)(lua_State * a0,int a1){append("lua_settop:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);}
char * (visctrl)(char a0){static char b[4];b[0]=a0;b[1]=0;return b;}
void (add_menu_str)(winid a0,const char * a1){append("add_menu_str:%lld:%s;",(long long)a0,(a1?a1:"NULL"));}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){append("add_menu:%d:%llu:%d:%d:%d:%d:%s:%u;",a0,(unsigned long long)a2->a_ulong,a3,a4,a5,a6,a7,a8);}
char * (eos)(char * a0){return a0+strlen(a0);}
char * (strstri)(const char * a0,const char * a1){return (char*)strstr(a0,a1);}
char * (strsubst)(char * a0,const char * a1,const char * a2){char*p=strstr(a0,a1);if(p){size_t n=strlen(a1),m=strlen(a2);memmove(p+m,p+n,strlen(p+n)+1);memcpy(p,a2,m);}return a0;}
boolean (pmatchi)(const char * a0,const char * a1){return !strcasecmp(a0,a1);}
void (add_menu_heading)(winid a0,const char * a1){append("add_menu_heading:%lld:%s;",(long long)a0,(a1?a1:"NULL"));}
int (select_menu)(winid a0,int a1,menu_item ** a2){*a2=0;if(selection_index){menu_item*p=tracked(sizeof *p);p->item.a_int=selection_index;p->count=1;*a2=p;selection_index=0;return 1;}return 0;}
void (getlin)(const char * a0,char * a1){strcpy(a1,inputs[0]?inputs:"");}
char * (mungspaces)(char * a0){return a0;}
boolean (attacktype)(struct permonst * a0,int a1){append("attacktype:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);return 0;}
int (dobreathe)(void){append("dobreathe:;");return 0;}
int (dospit)(void){append("dospit:;");return 0;}
int (doremove)(void){append("doremove:;");return 0;}
int (dogaze)(void){append("dogaze:;");return 0;}
int (dosummon)(void){append("dosummon:;");return 0;}
int (dohide)(void){append("dohide:;");return 0;}
int (dospinweb)(void){append("dospinweb:;");return 0;}
int (domindblast)(void){append("domindblast:;");return 0;}
struct monst * (split_mon)(struct monst * a0,struct monst * a1){append("split_mon:%lld:%lld;",(long long)token((const void*)a0),(long long)token((const void*)a1));return 0;}
void (dryup)(coordxy a0,coordxy a1,boolean a2){append("dryup:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2);}
boolean (is_pool)(coordxy a0,coordxy a1){return 0;}
void (use_unicorn_horn)(struct obj ** a0){append("use_unicorn_horn:%lld;",(long long)token((const void*)a0));}
void (aggravate)(void){append("aggravate:;");}
int (dopoly)(void){append("dopoly:;");return 0;}
int (pet_ranged_attk)(struct monst * a0,boolean a1){append("pet_ranged_attk:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);return 0;}
boolean (authorize_explore_mode)(void){append("authorize_explore_mode:;");return 0;}
void (makemap_remove_mons)(void){append("makemap_remove_mons:;");}
xint16 (ledger_no)(d_level * a0){append("ledger_no:%lld;",(long long)token((const void*)a0));return 0;}
void (rm_mapseen)(int a0){append("rm_mapseen:%lld;",(long long)a0);}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
boolean (remove_achievement)(schar a0){append("remove_achievement:%lld;",(long long)a0);return 0;}
void (ballrelease)(boolean a0){append("ballrelease:%lld;",(long long)a0);}
void (unplacebc)(void){append("unplacebc:;");}
void (maybe_reset_pick)(struct obj * a0){append("maybe_reset_pick:%lld;",(long long)token((const void*)a0));}
void (reset_utrap)(boolean a0){append("reset_utrap:%lld;",(long long)a0);}
void (check_special_room)(boolean a0){append("check_special_room:%lld;",(long long)a0);}
void (set_uinwater)(int a0){append("set_uinwater:%lld;",(long long)a0);}
void (dmonsfree)(void){append("dmonsfree:;");}
void (dobjsfree)(void){append("dobjsfree:;");}
NHFILE * (get_freeing_nhfile)(void){return query?&filepool:0;}
void (savelev)(NHFILE * a0,xint8 a1){append("savelev:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);}
void (close_nhfile)(NHFILE * a0){append("close_nhfile:%lld;",(long long)token((const void*)a0));}
void (vision_reset)(void){append("vision_reset:;");}
void (cls)(void){append("cls:;");}
void (u_on_rndspot)(int a0){append("u_on_rndspot:%lld;",(long long)a0);}
void (losedogs)(void){append("losedogs:;");}
void (kill_genocided_monsters)(void){append("kill_genocided_monsters:;");}
void (u_collide_m)(struct monst * a0){append("u_collide_m:%lld;",(long long)token((const void*)a0));}
void (initrack)(void){append("initrack:;");}
void (placebc)(void){append("placebc:;");}
void (docrt)(void){append("docrt:;");}
void (flush_screen)(int a0){append("flush_screen:%lld;",(long long)a0);}
void (deliver_splev_message)(void){append("deliver_splev_message:;");}
void (save_currentstate)(void){append("save_currentstate:;");}
void (recalc_mapseen)(void){append("recalc_mapseen:;");}
void (reveal_terrain)(unsigned int a0){append("reveal_terrain:%lld;",(long long)a0);}
void (wiz_map_levltyp)(void){append("wiz_map_levltyp:;");}
void (wiz_levltyp_legend)(void){append("wiz_levltyp_legend:;");}
void (selection_getbounds)(struct selectionvar * a0,NhRect * a1){a1->lx=10;a1->ly=10;a1->hx=11;a1->hy=11;}
coordxy (selection_getpoint)(coordxy a0,coordxy a1,struct selectionvar * a2){return query;}
int (glyph_at)(coordxy a0,coordxy a1){return -1;}
struct selectionvar * (selection_new)(void){return &selpool;}
uintptr_t probe_function(int);
void (set_selection_floodfillchk)(int (*a0)(coordxy, coordxy)){append("set_selection_floodfillchk:%lld;",(long long)((uintptr_t)a0==probe_function(3)?70000000ULL+3:token((const void*)a0)));}
void (selection_floodfill)(struct selectionvar * a0,coordxy a1,coordxy a2,boolean a3){append("selection_floodfill:%lld:%lld:%lld:%lld;",(long long)token((const void*)a0),(long long)a1,(long long)a2,(long long)a3);}
void (set_msg_xy)(coordxy a0,coordxy a1){append("set_msg_xy:%lld:%lld;",(long long)a0,(long long)a1);}
char * (selection_size_description)(struct selectionvar * a0,char * a1){return "small";}
char * (an)(const char * a0){return (char*)a0;}
void (selection_free)(struct selectionvar * a0,boolean a1){(void)a0;(void)a1;}
int (glyph_to_cmap)(int a0){append("glyph_to_cmap:%lld;",(long long)a0);return 0;}
boolean (gather_locs_interesting)(coordxy a0,coordxy a1,int a2){return interesting&&a0==11&&a1==10;}
int (do_screen_description)(coord a0,boolean a1,int a2,char * a3,const char ** a4,struct permonst ** a5){append("description:%d:%d:%d;",a0.x,a0.y,a2);extern int cmd_fixture_copy_observer(const coord*,coord*);int copy=cmd_fixture_copy_observer(&a0,watched);append("copied:%d;",copy);strcpy(a3,"an item");if(a4)*a4="an item";if(a5)*a5=&mons[PM_HUMAN];return 1;}
int (toggle_bool_option)(const char * a0){append("toggle_bool_option:%s;",(a0?a0:"NULL"));return 0;}
int (doorganize)(void){append("doorganize:;");return 0;}
int (donamelevel)(void){append("donamelevel:;");return 0;}
int (doapply)(void){append("doapply:;");return 0;}
int (doattributes)(void){append("doattributes:;");return 0;}
int (dotogglepickup)(void){append("dotogglepickup:;");return 0;}
int (dobugreport)(void){append("dobugreport:;");return 0;}
int (docallcmd)(void){append("docallcmd:;");return 0;}
int (docast)(void){append("docast:;");return 0;}
int (dotalk)(void){append("dotalk:;");return 0;}
int (do_gamelog)(void){append("do_gamelog:;");return 0;}
int (doclose)(void){append("doclose:;");return 0;}
int (doconduct)(void){append("doconduct:;");return 0;}
int (wiz_fuzzer)(void){append("wiz_fuzzer:;");return 0;}
int (dodip)(void){append("dodip:;");return 0;}
int (dodown)(void){append("dodown:;");return 0;}
int (dodrop)(void){append("dodrop:;");return 0;}
int (doddrop)(void){append("doddrop:;");return 0;}
int (doeat)(void){append("doeat:;");return 0;}
int (doengrave)(void){append("doengrave:;");return 0;}
int (enhance_weapon_skill)(void){append("enhance_weapon_skill:;");return 0;}
int (dofire)(void){append("dofire:;");return 0;}
int (doforce)(void){append("doforce:;");return 0;}
int (dogenocided)(void){append("dogenocided:;");return 0;}
int (doquickwhatis)(void){append("doquickwhatis:;");return 0;}
int (dohelp)(void){append("dohelp:;");return 0;}
int (dohistory)(void){append("dohistory:;");return 0;}
int (ddoinv)(void){append("ddoinv:;");return 0;}
int (dotypeinv)(void){append("dotypeinv:;");return 0;}
int (doinvoke)(void){append("doinvoke:;");return 0;}
int (dojump)(void){append("dojump:;");return 0;}
int (dokick)(void){append("dokick:;");return 0;}
int (dodiscovered)(void){append("dodiscovered:;");return 0;}
int (doclassdisco)(void){append("doclassdisco:;");return 0;}
int (wiz_level_change)(void){append("wiz_level_change:;");return 0;}
int (wiz_light_sources)(void){append("wiz_light_sources:;");return 0;}
int (dolook)(void){append("dolook:;");return 0;}
int (doloot)(void){append("doloot:;");return 0;}
int (wiz_migrate_mons)(void){append("wiz_migrate_mons:;");return 0;}
int (dosacrifice)(void){append("dosacrifice:;");return 0;}
int (doopen)(void){append("doopen:;");return 0;}
int (doset_simple)(void){append("doset_simple:;");return 0;}
int (doset)(void){append("doset:;");return 0;}
int (dooverview)(void){append("dooverview:;");return 0;}
int (wiz_panic)(void){append("wiz_panic:;");return 0;}
int (dopay)(void){append("dopay:;");return 0;}
int (doperminv)(void){append("doperminv:;");return 0;}
int (dopickup)(void){append("dopickup:;");return 0;}
int (wiz_polyself)(void){append("wiz_polyself:;");return 0;}
int (dopray)(void){append("dopray:;");return 0;}
int (doputon)(void){append("doputon:;");return 0;}
int (dodrink)(void){append("dodrink:;");return 0;}
int (done2)(void){append("done2:;");return 0;}
int (dowieldquiver)(void){append("dowieldquiver:;");return 0;}
int (doread)(void){append("doread:;");return 0;}
int (doredraw)(void){append("doredraw:;");return 0;}
int (doremring)(void){append("doremring:;");return 0;}
int (doride)(void){append("doride:;");return 0;}
int (dorub)(void){append("dorub:;");return 0;}
int (dosave)(void){append("dosave:;");return 0;}
int (do_write_config_file)(void){append("do_write_config_file:;");return 0;}
int (dosearch)(void){append("dosearch:;");return 0;}
int (doprinuse)(void){append("doprinuse:;");return 0;}
int (dopramulet)(void){append("dopramulet:;");return 0;}
int (doprarm)(void){append("doprarm:;");return 0;}
int (doprring)(void){append("doprring:;");return 0;}
int (doprtool)(void){append("doprtool:;");return 0;}
int (doprwep)(void){append("doprwep:;");return 0;}
int (doprgold)(void){append("doprgold:;");return 0;}
int (dovspell)(void){append("dovspell:;");return 0;}
int (doidtrap)(void){append("doidtrap:;");return 0;}
int (dosit)(void){append("dosit:;");return 0;}
int (wiz_show_stats)(void){append("wiz_show_stats:;");return 0;}
int (doswapweapon)(void){append("doswapweapon:;");return 0;}
int (dotakeoff)(void){append("dotakeoff:;");return 0;}
int (doddoremarm)(void){append("doddoremarm:;");return 0;}
int (dotelecmd)(void){append("dotelecmd:;");return 0;}
int (dothrow)(void){append("dothrow:;");return 0;}
int (wiz_timeout_queue)(void){append("wiz_timeout_queue:;");return 0;}
int (dotip)(void){append("dotip:;");return 0;}
int (doturn)(void){append("doturn:;");return 0;}
int (dotwoweapon)(void){append("dotwoweapon:;");return 0;}
int (dountrap)(void){append("dountrap:;");return 0;}
int (doup)(void){append("doup:;");return 0;}
int (dovanquished)(void){append("dovanquished:;");return 0;}
int (doextversion)(void){append("doextversion:;");return 0;}
int (doversion)(void){append("doversion:;");return 0;}
int (wiz_show_vision)(void){append("wiz_show_vision:;");return 0;}
int (donull)(void){append("donull:;");return 0;}
int (dowear)(void){append("dowear:;");return 0;}
int (dowhatdoes)(void){append("dowhatdoes:;");return 0;}
int (dowhatis)(void){append("dowhatis:;");return 0;}
int (dowield)(void){append("dowield:;");return 0;}
int (dowipe)(void){append("dowipe:;");return 0;}
int (doborn)(void){append("doborn:;");return 0;}
int (wiz_debug_cmd_bury)(void){append("wiz_debug_cmd_bury:;");return 0;}
int (dowizcast)(void){append("dowizcast:;");return 0;}
int (wiz_custom)(void){append("wiz_custom:;");return 0;}
int (wiz_detect)(void){append("wiz_detect:;");return 0;}
int (wiz_display_macros)(void){append("wiz_display_macros:;");return 0;}
int (wiz_flip_level)(void){append("wiz_flip_level:;");return 0;}
int (wiz_genesis)(void){append("wiz_genesis:;");return 0;}
int (wiz_identify)(void){append("wiz_identify:;");return 0;}
int (wiz_intrinsic)(void){append("wiz_intrinsic:;");return 0;}
int (wiz_kill)(void){append("wiz_kill:;");return 0;}
int (wiz_level_tele)(void){append("wiz_level_tele:;");return 0;}
int (wiz_load_splua)(void){append("wiz_load_splua:;");return 0;}
int (wiz_load_lua)(void){append("wiz_load_lua:;");return 0;}
int (wiz_objprobs)(void){append("wiz_objprobs:;");return 0;}
int (wiz_makemap)(void){append("wiz_makemap:;");return 0;}
int (wiz_map)(void){append("wiz_map:;");return 0;}
int (wiz_mon_diff)(void){append("wiz_mon_diff:;");return 0;}
int (wiz_rumor_check)(void){append("wiz_rumor_check:;");return 0;}
int (wiz_show_seenv)(void){append("wiz_show_seenv:;");return 0;}
int (wiz_show_nhuuid)(void){append("wiz_show_nhuuid:;");return 0;}
int (wiz_smell)(void){append("wiz_smell:;");return 0;}
int (wiz_telekinesis)(void){append("wiz_telekinesis:;");return 0;}
int (wiz_where)(void){append("wiz_where:;");return 0;}
int (wiz_wish)(void){append("wiz_wish:;");return 0;}
int (wiz_show_wmodes)(void){append("wiz_show_wmodes:;");return 0;}
int (dozap)(void){append("dozap:;");return 0;}
int (adjust_split)(void){append("adjust_split:;");return 0;}
int (dip_into)(void){append("dip_into:;");return 0;}
int (ia_dotakeoff)(void){append("ia_dotakeoff:;");return 0;}
int (remarm_swapwep)(void){append("remarm_swapwep:;");return 0;}
void (strbuf_append)(strbuf_t * a0,const char * a1){append("strbuf_append:%lld:%s;",(long long)token((const void*)a0),(a1?a1:"NULL"));}
unsigned int (Strlen_)(const char * a0,const char * a1,int a2){return strlen(a0);}
int (strncmpi)(const char * a0,const char * a1,int a2){return strncasecmp(a0,a1,a2);}
boolean (digit)(char a0){return a0>='0'&&a0<='9';}
void (show_menu_controls)(winid a0,boolean a1){append("show_menu_controls:%lld:%lld;",(long long)a0,(long long)a1);}
void (copynchars)(char * a0,const char * a1,int a2){int i=0;while(i<a2&&a1[i]){a0[i]=a1[i];i++;}a0[i]=0;}
boolean (debugcore)(const char * a0,boolean a1){return result;}
char * (trimspaces)(char * a0){return a0;}
char (highc)(char a0){return a0>='a'&&a0<='z'?a0-'a'+'A':a0;}
boolean (rng_log_enabled)(void){return 1;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("rngcaller:%s:%d:%s;",a0,a1,a2);}
int (rn2)(int a0){if(a0<=0)abort();int v=(unsigned)rngvalue%(unsigned)a0;append("rn2:%d:%d;",a0,v);hook();return v;}
int (rnd)(int a0){if(a0<=0)abort();int v=1+(unsigned)rngvalue%(unsigned)a0;append("rnd:%d:%d;",a0,v);hook();return v;}
void (domove)(void){append("domove:;");}
void (docrt_flags)(int a0){append("docrt_flags:%lld;",(long long)a0);}
int (getpos)(coord * a0,boolean a1,const char * a2){a0->x=11;a0->y=10;return query?0:-1;}
int (sgn)(int a0){return (a0>0)-(a0<0);}
boolean (letter)(char a0){return (a0>='a'&&a0<='z')||(a0>='A'&&a0<='Z');}
char * (dowhatdoes_core)(char a0,char * a1){return "command";}
boolean (u_maybe_impaired)(void){append("u_maybe_impaired:;");return 0;}
stairway * (stairway_at)(coordxy a0,coordxy a1){return query?&stairpool:0;}
boolean (can_reach_floor)(boolean a0){return 1;}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return "monster";}
char * (doname)(struct obj * a0){append("doname:%lld;",(long long)token((const void*)a0));return 0;}
int (num_spells)(void){return 0;}
struct trap * (t_at)(coordxy a0,coordxy a1){append("t_at:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){append("dist2:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3);return 0;}
struct obj * (carrying)(int a0){append("carrying:%lld;",(long long)a0);return 0;}
char * (upstart)(char * a0){if(*a0>='a'&&*a0<='z')*a0-=32;return a0;}
int (canseemon)(struct monst * a0){append("canseemon:%lld;",(long long)token((const void*)a0));return 0;}
int (sensemon)(struct monst * a0){append("sensemon:%lld;",(long long)token((const void*)a0));return 0;}
struct obj * (which_armor)(struct monst * a0,long a1){append("which_armor:%lld:%lld;",(long long)token((const void*)a0),(long long)a1);return 0;}
boolean (can_saddle)(struct monst * a0){append("can_saddle:%lld;",(long long)token((const void*)a0));return 0;}
char * (mon_nam)(struct monst * a0){return "monster";}
boolean (linedup)(coordxy a0,coordxy a1,coordxy a2,coordxy a3,int a4){append("linedup:%lld:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3,(long long)a4);return 0;}
boolean (test_move)(coordxy a0,coordxy a1,coordxy a2,coordxy a3,int a4){append("test_move:%lld:%lld:%lld:%lld:%lld;",(long long)a0,(long long)a1,(long long)a2,(long long)a3,(long long)a4);return 0;}
boolean (On_stairs_up)(coordxy a0,coordxy a1){append("On_stairs_up:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
boolean (On_stairs_dn)(coordxy a0,coordxy a1){append("On_stairs_dn:%lld:%lld;",(long long)a0,(long long)a1);return 0;}
void (nhwindows_hangup)(void){append("nhwindows_hangup:;");}
int (dosave0)(void){append("dosave0:;");return 0;}
void (clearlocks)(void){append("clearlocks:;");}
void (nh_terminate)(int a0){longjmp(escape,1);}
boolean (getpos_menu)(coord * a0,int a1){return 0;}
void (auto_describe)(coordxy a0,coordxy a1){append("auto_describe:%lld:%lld;",(long long)a0,(long long)a1);}
void (paniclog)(const char * a0,const char * a1){append("paniclog:%s:%s;",(a0?a0:"NULL"),(a1?a1:"NULL"));}
void (dumplogmsg)(const char * a0){append("dumplogmsg:%s;",(a0?a0:"NULL"));}
time_t (getnow)(void){return 9007199254741011LL;}
long (timet_delta)(time_t a0,time_t a1){return (long)(a0-a1);}
int (dosuspend)(void){append("dosuspend:;");return 0;}
int (dosh)(void){append("dosh:;");return 0;}
void (Norep)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("Norep:%s;",b);}
void (There)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("There:%s;",b);}
void (You)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You:%s;",b);}
void (You_cant)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("You_cant:%s;",b);}
void (config_error_add)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("config_error_add:%s;",b);}
void (custompline)(unsigned int a0,const char * a1,...){char b[4096];va_list ap;va_start(ap,a1);vsnprintf(b,sizeof b,a1,ap);va_end(ap);append("custompline:%s;",b);}
void (impossible)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("impossible:%s;",b);}
void (pline)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("pline:%s;",b);}
void (pline_xy)(coordxy a0,coordxy a1,const char * a2,...){char b[4096];va_list ap;va_start(ap,a2);vsnprintf(b,sizeof b,a2,ap);va_end(ap);append("pline_xy:%s;",b);}
void (raw_printf)(const char * a0,...){char b[4096];va_list ap;va_start(ap,a0);vsnprintf(b,sizeof b,a0,ap);va_end(ap);append("raw_printf:%s;",b);}
void nh_snprintf(const char*file,int line,char*buf,size_t n,const char*fmt,...){va_list ap;va_start(ap,fmt);int r=vsnprintf(buf,n,fmt,ap);va_end(ap);}
static void fixture_win_exit_nhwindows(const char * a0){append("exit:%s;",a0?a0:"");}
static winid fixture_win_create_nhwindow(int a0){append("create:%d;",a0);return 3;}
static void fixture_win_clear_nhwindow(winid a0){append("clear:%d;",a0);}
static void fixture_win_display_nhwindow(winid a0,boolean a1){append("display:%d:%d;",a0,a1);}
static void fixture_win_destroy_nhwindow(winid a0){append("destroy:%d;",a0);}
static void fixture_win_putstr(winid a0,int a1,const char * a2){append("putstr:%d:%d:%s;",a0,a1,a2);}
static void fixture_win_start_menu(winid a0,unsigned long a1){append("start:%d:%lu;",a0,a1);hook();}
static void fixture_win_end_menu(winid a0,const char * a1){append("end:%d:%s;",a0,a1?a1:"");}
static void fixture_win_mark_synch(void){append("mark;");}
static void fixture_win_wait_synch(void){append("wait;");}
static int fixture_win_nhgetch(void){return nextinput();}
static int fixture_win_nh_poskey(coordxy * a0,coordxy * a1,int * a2){*a0=11;*a1=10;*a2=0;return nextinput();}
static void fixture_win_nhbell(void){append("bell;");}
static int fixture_win_doprev_message(void){return 7;}
static char fixture_win_yn_function(const char * a0,const char * a1,char a2){append("yn:%s:%s:%d;",a0?a0:"",a1?a1:"",a2);return query?a2:nextinput();}
static int fixture_win_get_ext_cmd(void){int n=extindex;extindex=-1;return n;}
static void fixture_win_putmsghistory(const char * a0,boolean a1){append("history:%s:%d;",a0,a1);}
static boolean fixture_win_can_suspend(void){return query;}
#ifdef HYBRID_CMD
#include "../nethack-c/wasm/tu-fragments/cmd-types.h"
extern int teleport_cmd_doprev_message(void);
#define doprev_message teleport_cmd_doprev_message
extern int teleport_cmd_timed_occupation(void);
#define timed_occupation teleport_cmd_timed_occupation
extern boolean teleport_cmd_can_do_extcmd(const struct ext_func_tab * extcmd);
#define can_do_extcmd teleport_cmd_can_do_extcmd
extern char * teleport_cmd_doc_extcmd_flagstr(winid menuwin,const struct ext_func_tab * efp);
#define doc_extcmd_flagstr teleport_cmd_doc_extcmd_flagstr
extern int teleport_cmd_doterrain(void);
#define doterrain teleport_cmd_doterrain
extern boolean teleport_cmd_u_have_seen_whole_selection(struct selectionvar * sel);
#define u_have_seen_whole_selection teleport_cmd_u_have_seen_whole_selection
extern boolean teleport_cmd_u_have_seen_bounds_selection(struct selectionvar * sel);
#define u_have_seen_bounds_selection teleport_cmd_u_have_seen_bounds_selection
extern boolean teleport_cmd_u_can_see_whole_selection(struct selectionvar * sel);
#define u_can_see_whole_selection teleport_cmd_u_can_see_whole_selection
extern int teleport_cmd_dolookaround_floodfill_findroom(coordxy x,coordxy y);
#define dolookaround_floodfill_findroom teleport_cmd_dolookaround_floodfill_findroom
extern void teleport_cmd_lookaround_known_room(coordxy x,coordxy y);
#define lookaround_known_room teleport_cmd_lookaround_known_room
extern struct Cmd_bind * teleport_cmd_cmdbind_get(uchar key);
#define cmdbind_get teleport_cmd_cmdbind_get
extern void teleport_cmd_cmdbind_add(uchar key,const struct ext_func_tab * extcmd,boolean user);
#define cmdbind_add teleport_cmd_cmdbind_add
extern void teleport_cmd_cmdbind_remove(uchar key);
#define cmdbind_remove teleport_cmd_cmdbind_remove
extern void teleport_cmd_cmdbind_swapkeys(uchar key1,uchar key2);
#define cmdbind_swapkeys teleport_cmd_cmdbind_swapkeys
extern void teleport_cmd_handler_rebind_keys_add(boolean keyfirst);
#define handler_rebind_keys_add teleport_cmd_handler_rebind_keys_add
extern boolean teleport_cmd_bind_key_fn(uchar key,int (*fn)(void));
#define bind_key_fn teleport_cmd_bind_key_fn
extern void teleport_cmd_commands_init(void);
#define commands_init teleport_cmd_commands_init
extern boolean teleport_cmd_keylist_func_has_key(const struct ext_func_tab * extcmd,boolean * skip_keys_used);
#define keylist_func_has_key teleport_cmd_keylist_func_has_key
extern int teleport_cmd_keylist_putcmds(winid datawin,boolean docount,int incl_flags,int excl_flags,boolean * keys_used);
#define keylist_putcmds teleport_cmd_keylist_putcmds
extern const char * teleport_cmd_spkey_name(int nhkf);
#define spkey_name teleport_cmd_spkey_name
extern boolean teleport_cmd_accept_menu_prefix(const struct ext_func_tab * ec);
#define accept_menu_prefix teleport_cmd_accept_menu_prefix
extern void teleport_cmd_reset_cmd_vars(boolean reset_cmdq);
#define reset_cmd_vars teleport_cmd_reset_cmd_vars
extern void teleport_cmd_show_direction_keys(winid win,char centerchar,boolean nodiag);
#define show_direction_keys teleport_cmd_show_direction_keys
extern boolean teleport_cmd_help_dir(char sym,uchar spkey,const char * msg);
#define help_dir teleport_cmd_help_dir
extern int teleport_cmd_doherecmdmenu(void);
#define doherecmdmenu teleport_cmd_doherecmdmenu
extern int teleport_cmd_dotherecmdmenu(void);
#define dotherecmdmenu teleport_cmd_dotherecmdmenu
extern void teleport_cmd_mcmd_addmenu(winid win,int act,const char * txt);
#define mcmd_addmenu teleport_cmd_mcmd_addmenu
extern int teleport_cmd_there_cmd_menu_self(winid win,coordxy x,coordxy y,int * act);
#define there_cmd_menu_self teleport_cmd_there_cmd_menu_self
extern int teleport_cmd_there_cmd_menu_next2u(winid win,coordxy x,coordxy y,int mod,int * act);
#define there_cmd_menu_next2u teleport_cmd_there_cmd_menu_next2u
extern int teleport_cmd_there_cmd_menu_far(winid win,coordxy x,coordxy y,int mod);
#define there_cmd_menu_far teleport_cmd_there_cmd_menu_far
extern int teleport_cmd_there_cmd_menu_common(winid win,coordxy x,coordxy y,int mod,int * act);
#define there_cmd_menu_common teleport_cmd_there_cmd_menu_common
extern void teleport_cmd_act_on_act(int act,coordxy dx,coordxy dy);
#define act_on_act teleport_cmd_act_on_act
extern char teleport_cmd_there_cmd_menu(coordxy x,coordxy y,int mod);
#define there_cmd_menu teleport_cmd_there_cmd_menu
extern char teleport_cmd_here_cmd_menu(void);
#define here_cmd_menu teleport_cmd_here_cmd_menu
extern int teleport_cmd_domouseaction(void);
#define domouseaction teleport_cmd_domouseaction
extern int teleport_cmd_parse(void);
#define parse teleport_cmd_parse
extern char teleport_cmd_readchar_core(coordxy * x,coordxy * y,int * mod);
#define readchar_core teleport_cmd_readchar_core
extern int teleport_cmd_dotravel(void);
#define dotravel teleport_cmd_dotravel
extern int teleport_cmd_dotravel_target(void);
#define dotravel_target teleport_cmd_dotravel_target
extern int teleport_cmd_doclicklook(void);
#define doclicklook teleport_cmd_doclicklook
extern boolean teleport_cmd_yn_menuable_resp(const char * resp);
#define yn_menuable_resp teleport_cmd_yn_menuable_resp
extern void teleport_cmd_yn_func_menu_opt(winid win,char key,const char * text,char def);
#define yn_func_menu_opt teleport_cmd_yn_func_menu_opt
extern boolean teleport_cmd_yn_function_menu(const char * query,const char * resp,char def,char * res);
#define yn_function_menu teleport_cmd_yn_function_menu
extern int teleport_cmd_dosuspend_core(void);
#define dosuspend_core teleport_cmd_dosuspend_core
extern int teleport_cmd_dosh_core(void);
#define dosh_core teleport_cmd_dosh_core
extern int teleport_cmd_dummyfunction(void);
#define dummyfunction teleport_cmd_dummyfunction
#else
#include "../.cache/wasm64-build/tree/src/cmd.c"
#define TELEPORT_CMD_REFERENCE_TYPES 1
#define teleport_cmd_doprev_message doprev_message
#define teleport_cmd_timed_occupation timed_occupation
#define teleport_cmd_can_do_extcmd can_do_extcmd
#define teleport_cmd_doc_extcmd_flagstr doc_extcmd_flagstr
#define teleport_cmd_doterrain doterrain
#define teleport_cmd_u_have_seen_whole_selection u_have_seen_whole_selection
#define teleport_cmd_u_have_seen_bounds_selection u_have_seen_bounds_selection
#define teleport_cmd_u_can_see_whole_selection u_can_see_whole_selection
#define teleport_cmd_dolookaround_floodfill_findroom dolookaround_floodfill_findroom
#define teleport_cmd_lookaround_known_room lookaround_known_room
#define teleport_cmd_cmdbind_get cmdbind_get
#define teleport_cmd_cmdbind_add cmdbind_add
#define teleport_cmd_cmdbind_remove cmdbind_remove
#define teleport_cmd_cmdbind_swapkeys cmdbind_swapkeys
#define teleport_cmd_handler_rebind_keys_add handler_rebind_keys_add
#define teleport_cmd_bind_key_fn bind_key_fn
#define teleport_cmd_commands_init commands_init
#define teleport_cmd_keylist_func_has_key keylist_func_has_key
#define teleport_cmd_keylist_putcmds keylist_putcmds
#define teleport_cmd_spkey_name spkey_name
#define teleport_cmd_accept_menu_prefix accept_menu_prefix
#define teleport_cmd_reset_cmd_vars reset_cmd_vars
#define teleport_cmd_show_direction_keys show_direction_keys
#define teleport_cmd_help_dir help_dir
#define teleport_cmd_doherecmdmenu doherecmdmenu
#define teleport_cmd_dotherecmdmenu dotherecmdmenu
#define teleport_cmd_mcmd_addmenu mcmd_addmenu
#define teleport_cmd_there_cmd_menu_self there_cmd_menu_self
#define teleport_cmd_there_cmd_menu_next2u there_cmd_menu_next2u
#define teleport_cmd_there_cmd_menu_far there_cmd_menu_far
#define teleport_cmd_there_cmd_menu_common there_cmd_menu_common
#define teleport_cmd_act_on_act act_on_act
#define teleport_cmd_there_cmd_menu there_cmd_menu
#define teleport_cmd_here_cmd_menu here_cmd_menu
#define teleport_cmd_domouseaction domouseaction
#define teleport_cmd_parse parse
#define teleport_cmd_readchar_core readchar_core
#define teleport_cmd_dotravel dotravel
#define teleport_cmd_dotravel_target dotravel_target
#define teleport_cmd_doclicklook doclicklook
#define teleport_cmd_yn_menuable_resp yn_menuable_resp
#define teleport_cmd_yn_func_menu_opt yn_func_menu_opt
#define teleport_cmd_yn_function_menu yn_function_menu
#define teleport_cmd_dosuspend_core dosuspend_core
#define teleport_cmd_dosh_core dosh_core
#define teleport_cmd_dummyfunction dummyfunction
#endif
#include "../nethack-c/wasm/tu-fragments/cmd-support.c"
#include "tu-cmd-layout.h"
void probe_watch(int on){watched=on?&coords[0]:0;}
int probe_byvalue(void){char b[BUFSZ];const char*f=0;return do_screen_description(coords[0],1,0,b,&f,0);}
uintptr_t probe_pool(int k,int i){switch(k){case 0:return(uintptr_t)&objpool[i];case 1:return(uintptr_t)&monpool[i];case 2:return(uintptr_t)&buffers[i];case 3:return(uintptr_t)&queuepool[i];case 4:return(uintptr_t)&bindpool[i];case 5:return(uintptr_t)&coords[i];case 6:return(uintptr_t)&counts[i];case 7:return(uintptr_t)&ptrs[i];case 8:return(uintptr_t)&selpool;default:abort();}}
int probe_block_count(void){return blockcount;}
uintptr_t probe_block(int i){return(uintptr_t)blocks[i].p;}
size_t probe_block_size(int i){return blocks[i].n;}
int probe_block_live(int i){return blocks[i].live;}
int probe_layout_count(void){return sizeof cmd_layout/sizeof cmd_layout[0];}
const char*probe_layout_name(int i){return cmd_layout[i].name;}
int64_t probe_layout_value(int i){return(int64_t)cmd_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}
void probe_input(const char*s){strncpy(inputs,s,sizeof inputs-1);inputpos=0;}
void probe_option(int k,int64_t v){switch(k){case 0:result=v;break;case 1:rngvalue=v;break;case 2:query=v;break;case 3:grow=v;break;case 4:reentry=v;break;case 5:extindex=v;break;case 6:selection_index=v;break;case 7:interesting=v;break;default:abort();}}
uint64_t probe_action(int which,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f){if(setjmp(escape))return 0x70000000;switch(which){
case 0:return(uint64_t)(uintptr_t)(doprev_message());
case 1:return(uint64_t)(uintptr_t)(timed_occupation());
case 2:reset_occupations();return 0;
case 3:set_occupation((int (*)(void))(uintptr_t)a,(const char *)(uintptr_t)b,(cmdcount_nht)(uintptr_t)c);return 0;
case 4:cmdq_add_ec((int)(uintptr_t)a,(int (*)(void))(uintptr_t)b);return 0;
case 5:cmdq_add_key((int)(uintptr_t)a,(char)(uintptr_t)b);return 0;
case 6:cmdq_add_dir((int)(uintptr_t)a,(schar)(uintptr_t)b,(schar)(uintptr_t)c,(schar)(uintptr_t)d);return 0;
case 7:cmdq_add_userinput((int)(uintptr_t)a);return 0;
case 8:cmdq_add_int((int)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 9:cmdq_shift((int)(uintptr_t)a);return 0;
case 10:return(uint64_t)(uintptr_t)(cmdq_reverse((struct _cmd_queue *)(uintptr_t)a));
case 11:return(uint64_t)(uintptr_t)(cmdq_copy((int)(uintptr_t)a));
case 12:return(uint64_t)(uintptr_t)(cmdq_pop());
case 13:return(uint64_t)(uintptr_t)(cmdq_peek((int)(uintptr_t)a));
case 14:cmdq_clear((int)(uintptr_t)a);return 0;
case 15:return(uint64_t)(uintptr_t)(pgetchar());
case 16:return(uint64_t)(uintptr_t)(extcmd_initiator());
case 17:return(uint64_t)(uintptr_t)(can_do_extcmd((const struct ext_func_tab *)(uintptr_t)a));
case 18:return(uint64_t)(uintptr_t)(doextcmd());
case 19:return(uint64_t)(uintptr_t)(doc_extcmd_flagstr((winid)(uintptr_t)a,(const struct ext_func_tab *)(uintptr_t)b));
case 20:return(uint64_t)(uintptr_t)(doextlist());
case 21:return(uint64_t)(uintptr_t)(extcmd_via_menu());
case 22:return(uint64_t)(uintptr_t)(domonability());
case 23:return(uint64_t)(uintptr_t)(enter_explore_mode());
case 24:makemap_prepost((boolean)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 25:return(uint64_t)(uintptr_t)(levltyp_to_name((int)(uintptr_t)a));
case 26:return(uint64_t)(uintptr_t)(doterrain());
case 27:return(uint64_t)(uintptr_t)(u_have_seen_whole_selection((struct selectionvar *)(uintptr_t)a));
case 28:return(uint64_t)(uintptr_t)(u_have_seen_bounds_selection((struct selectionvar *)(uintptr_t)a));
case 29:return(uint64_t)(uintptr_t)(u_can_see_whole_selection((struct selectionvar *)(uintptr_t)a));
case 30:return(uint64_t)(uintptr_t)(dolookaround_floodfill_findroom((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));
case 31:lookaround_known_room((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b);return 0;
case 32:return(uint64_t)(uintptr_t)(dolookaround());
case 33:return(uint64_t)(uintptr_t)(dotoggleoption());
case 34:set_move_cmd((int)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 35:return(uint64_t)(uintptr_t)(do_move_west());
case 36:return(uint64_t)(uintptr_t)(do_move_northwest());
case 37:return(uint64_t)(uintptr_t)(do_move_north());
case 38:return(uint64_t)(uintptr_t)(do_move_northeast());
case 39:return(uint64_t)(uintptr_t)(do_move_east());
case 40:return(uint64_t)(uintptr_t)(do_move_southeast());
case 41:return(uint64_t)(uintptr_t)(do_move_south());
case 42:return(uint64_t)(uintptr_t)(do_move_southwest());
case 43:return(uint64_t)(uintptr_t)(do_rush_west());
case 44:return(uint64_t)(uintptr_t)(do_rush_northwest());
case 45:return(uint64_t)(uintptr_t)(do_rush_north());
case 46:return(uint64_t)(uintptr_t)(do_rush_northeast());
case 47:return(uint64_t)(uintptr_t)(do_rush_east());
case 48:return(uint64_t)(uintptr_t)(do_rush_southeast());
case 49:return(uint64_t)(uintptr_t)(do_rush_south());
case 50:return(uint64_t)(uintptr_t)(do_rush_southwest());
case 51:return(uint64_t)(uintptr_t)(do_run_west());
case 52:return(uint64_t)(uintptr_t)(do_run_northwest());
case 53:return(uint64_t)(uintptr_t)(do_run_north());
case 54:return(uint64_t)(uintptr_t)(do_run_northeast());
case 55:return(uint64_t)(uintptr_t)(do_run_east());
case 56:return(uint64_t)(uintptr_t)(do_run_southeast());
case 57:return(uint64_t)(uintptr_t)(do_run_south());
case 58:return(uint64_t)(uintptr_t)(do_run_southwest());
case 59:return(uint64_t)(uintptr_t)(do_reqmenu());
case 60:return(uint64_t)(uintptr_t)(do_rush());
case 61:return(uint64_t)(uintptr_t)(do_run());
case 62:return(uint64_t)(uintptr_t)(do_fight());
case 63:return(uint64_t)(uintptr_t)(do_repeat());
case 64:return(uint64_t)(uintptr_t)(extcmds_getentry((int)(uintptr_t)a));
case 65:return(uint64_t)(uintptr_t)(cmdbind_get((uchar)(uintptr_t)a));
case 66:cmdbind_add((uchar)(uintptr_t)a,(const struct ext_func_tab *)(uintptr_t)b,(boolean)(uintptr_t)c);return 0;
case 67:cmdbind_remove((uchar)(uintptr_t)a);return 0;
case 68:cmdbind_freeall();return 0;
case 69:cmdbind_swapkeys((uchar)(uintptr_t)a,(uchar)(uintptr_t)b);return 0;
case 70:return(uint64_t)(uintptr_t)(count_bind_keys());
case 71:get_changed_key_binds((strbuf_t *)(uintptr_t)a);return 0;
case 72:handler_rebind_keys_add((boolean)(uintptr_t)a);return 0;
case 73:handler_rebind_keys();return 0;
case 74:handler_change_autocompletions();return 0;
case 75:return(uint64_t)(uintptr_t)(extcmds_match((const char *)(uintptr_t)a,(int)(uintptr_t)b,(int **)(uintptr_t)c));
case 76:return(uint64_t)(uintptr_t)(key2extcmddesc((uchar)(uintptr_t)a));
case 77:return(uint64_t)(uintptr_t)(bind_mousebtn((int)(uintptr_t)a,(const char *)(uintptr_t)b));
case 78:return(uint64_t)(uintptr_t)(bind_key((uchar)(uintptr_t)a,(const char *)(uintptr_t)b,(boolean)(uintptr_t)c));
case 79:return(uint64_t)(uintptr_t)(bind_key_fn((uchar)(uintptr_t)a,(int (*)(void))(uintptr_t)b));
case 80:commands_init();return 0;
case 81:return(uint64_t)(uintptr_t)(keylist_func_has_key((const struct ext_func_tab *)(uintptr_t)a,(boolean *)(uintptr_t)b));
case 82:return(uint64_t)(uintptr_t)(keylist_putcmds((winid)(uintptr_t)a,(boolean)(uintptr_t)b,(int)(uintptr_t)c,(int)(uintptr_t)d,(boolean *)(uintptr_t)e));
case 83:dokeylist();return 0;
case 84:return(uint64_t)(uintptr_t)(ext_func_tab_from_func((int (*)(void))(uintptr_t)a));
case 85:return(uint64_t)(uintptr_t)(cmd_from_dir((int)(uintptr_t)a,(int)(uintptr_t)b));
case 86:return(uint64_t)(uintptr_t)(cmd_from_func((int (*)(void))(uintptr_t)a));
case 87:return(uint64_t)(uintptr_t)(cmd_from_ecname((const char *)(uintptr_t)a));
case 88:return(uint64_t)(uintptr_t)(ecname_from_fn((int (*)(void))(uintptr_t)a));
case 89:return(uint64_t)(uintptr_t)(cmdname_from_func((int (*)(void))(uintptr_t)a,(char *)(uintptr_t)b,(boolean)(uintptr_t)c));
case 90:return(uint64_t)(uintptr_t)(bind_specialkey((uchar)(uintptr_t)a,(const char *)(uintptr_t)b));
case 91:return(uint64_t)(uintptr_t)(spkey_name((int)(uintptr_t)a));
case 92:return(uint64_t)(uintptr_t)(key2txt((uchar)(uintptr_t)a,(char *)(uintptr_t)b));
case 93:parseautocomplete((char *)(uintptr_t)a,(boolean)(uintptr_t)b);return 0;
case 94:all_options_autocomplete((strbuf_t *)(uintptr_t)a);return 0;
case 95:return(uint64_t)(uintptr_t)(count_autocompletions());
case 96:lock_mouse_buttons((boolean)(uintptr_t)a);return 0;
case 97:reset_commands((boolean)(uintptr_t)a);return 0;
case 98:update_rest_on_space();return 0;
case 99:return(uint64_t)(uintptr_t)(accept_menu_prefix((const struct ext_func_tab *)(uintptr_t)a));
case 100:return(uint64_t)(uintptr_t)(randomkey());
case 101:random_response((char *)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 102:return(uint64_t)(uintptr_t)(rnd_extcmd_idx());
case 103:reset_cmd_vars((boolean)(uintptr_t)a);return 0;
case 104:rhack((int)(uintptr_t)a);return 0;
case 105:return(uint64_t)(uintptr_t)(xytodir((int)(uintptr_t)a,(int)(uintptr_t)b));
case 106:dirtocoord((coord *)(uintptr_t)a,(int)(uintptr_t)b);return 0;
case 107:return(uint64_t)(uintptr_t)(movecmd((char)(uintptr_t)a,(int)(uintptr_t)b));
case 108:return(uint64_t)(uintptr_t)(dxdy_moveok());
case 109:return(uint64_t)(uintptr_t)(redraw_cmd((char)(uintptr_t)a));
case 110:return(uint64_t)(uintptr_t)(get_adjacent_loc((const char *)(uintptr_t)a,(const char *)(uintptr_t)b,(coordxy)(uintptr_t)c,(coordxy)(uintptr_t)d,(coord *)(uintptr_t)e));
case 111:return(uint64_t)(uintptr_t)(getdir((const char *)(uintptr_t)a));
case 112:show_direction_keys((winid)(uintptr_t)a,(char)(uintptr_t)b,(boolean)(uintptr_t)c);return 0;
case 113:return(uint64_t)(uintptr_t)(help_dir((char)(uintptr_t)a,(uchar)(uintptr_t)b,(const char *)(uintptr_t)c));
case 114:confdir((boolean)(uintptr_t)a);return 0;
case 115:return(uint64_t)(uintptr_t)(directionname((int)(uintptr_t)a));
case 116:return(uint64_t)(uintptr_t)(isok((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b));
case 117:return(uint64_t)(uintptr_t)(doherecmdmenu());
case 118:return(uint64_t)(uintptr_t)(dotherecmdmenu());
case 119:mcmd_addmenu((winid)(uintptr_t)a,(int)(uintptr_t)b,(const char *)(uintptr_t)c);return 0;
case 120:return(uint64_t)(uintptr_t)(there_cmd_menu_self((winid)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(int *)(uintptr_t)d));
case 121:return(uint64_t)(uintptr_t)(there_cmd_menu_next2u((winid)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(int)(uintptr_t)d,(int *)(uintptr_t)e));
case 122:return(uint64_t)(uintptr_t)(there_cmd_menu_far((winid)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(int)(uintptr_t)d));
case 123:return(uint64_t)(uintptr_t)(there_cmd_menu_common((winid)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c,(int)(uintptr_t)d,(int *)(uintptr_t)e));
case 124:act_on_act((int)(uintptr_t)a,(coordxy)(uintptr_t)b,(coordxy)(uintptr_t)c);return 0;
case 125:return(uint64_t)(uintptr_t)(there_cmd_menu((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(int)(uintptr_t)c));
case 126:return(uint64_t)(uintptr_t)(here_cmd_menu());
case 127:click_to_cmd((coordxy)(uintptr_t)a,(coordxy)(uintptr_t)b,(int)(uintptr_t)c);return 0;
case 128:return(uint64_t)(uintptr_t)(domouseaction());
case 129:return(uint64_t)(uintptr_t)(get_count((const char *)(uintptr_t)a,(char)(uintptr_t)b,(long)(uintptr_t)c,(cmdcount_nht *)(uintptr_t)d,(unsigned int)(uintptr_t)e));
case 130:return(uint64_t)(uintptr_t)(parse());
case 131:hangup((int)(uintptr_t)a);return 0;
case 132:end_of_input();return 0;
case 133:return(uint64_t)(uintptr_t)(readchar_core((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(int *)(uintptr_t)c));
case 134:return(uint64_t)(uintptr_t)(readchar());
case 135:return(uint64_t)(uintptr_t)(readchar_poskey((coordxy *)(uintptr_t)a,(coordxy *)(uintptr_t)b,(int *)(uintptr_t)c));
case 136:return(uint64_t)(uintptr_t)(dotravel());
case 137:return(uint64_t)(uintptr_t)(dotravel_target());
case 138:return(uint64_t)(uintptr_t)(doclicklook());
case 139:return(uint64_t)(uintptr_t)(yn_menuable_resp((const char *)(uintptr_t)a));
case 140:yn_func_menu_opt((winid)(uintptr_t)a,(char)(uintptr_t)b,(const char *)(uintptr_t)c,(char)(uintptr_t)d);return 0;
case 141:return(uint64_t)(uintptr_t)(yn_function_menu((const char *)(uintptr_t)a,(const char *)(uintptr_t)b,(char)(uintptr_t)c,(char *)(uintptr_t)d));
case 142:return(uint64_t)(uintptr_t)(yn_function((const char *)(uintptr_t)a,(const char *)(uintptr_t)b,(char)(uintptr_t)c,(boolean)(uintptr_t)d));
case 143:return(uint64_t)(uintptr_t)(paranoid_ynq((boolean)(uintptr_t)a,(const char *)(uintptr_t)b,(boolean)(uintptr_t)c));
case 144:return(uint64_t)(uintptr_t)(paranoid_query((boolean)(uintptr_t)a,(const char *)(uintptr_t)b));
case 145:return(uint64_t)(uintptr_t)(dosuspend_core());
case 146:return(uint64_t)(uintptr_t)(dosh_core());
case 147:return(uint64_t)(uintptr_t)(dummyfunction());
default:abort();}}
void probe_reset(void){for(int i=0;i<blockcount;i++)if(blocks[i].live)__real_free(blocks[i].p);blockcount=0;traceused=0;tracebuf[0]=0;result=rngvalue=grow=reentry=inputpos=selection_index=interesting=0;watched=0;query=1;extindex=-1;inputs[0]=0;memset(objpool,0,sizeof objpool);memset(monpool,0,sizeof monpool);memset(queuepool,0,sizeof queuepool);memset(bindpool,0,sizeof bindpool);memset(coords,0,sizeof coords);memset(counts,0,sizeof counts);memset(ptrs,0,sizeof ptrs);memset(buffers,0,sizeof buffers);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gm,0,sizeof gm);
memset((void*)&go,0,sizeof go);
memset((void*)&gc,0,sizeof gc);
memset((void*)&gi,0,sizeof gi);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&gl,0,sizeof gl);
memset((void*)&flags,0,sizeof flags);
memset((void*)&u,0,sizeof u);
memset((void*)&ge,0,sizeof ge);
memset((void*)&gy,0,sizeof gy);
memset((void*)&svl,0,sizeof svl);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&svd,0,sizeof svd);
memset((void*)&svc,0,sizeof svc);
memset((void*)&uball,0,sizeof uball);
memset((void*)&svu,0,sizeof svu);
memset((void*)&gv,0,sizeof gv);
memset((void*)&a11y,0,sizeof a11y);
memset((void*)&gd,0,sizeof gd);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&gt,0,sizeof gt);
memset((void*)&gk,0,sizeof gk);
memset((void*)&gu,0,sizeof gu);
memset((void*)&soundprocs,0,sizeof soundprocs);
memset((void*)&gs,0,sizeof gs);
memset((void*)&urealtime,0,sizeof urealtime);
windowprocs.win_exit_nhwindows=fixture_win_exit_nhwindows;
windowprocs.win_create_nhwindow=fixture_win_create_nhwindow;
windowprocs.win_clear_nhwindow=fixture_win_clear_nhwindow;
windowprocs.win_display_nhwindow=fixture_win_display_nhwindow;
windowprocs.win_destroy_nhwindow=fixture_win_destroy_nhwindow;
windowprocs.win_putstr=fixture_win_putstr;
windowprocs.win_start_menu=fixture_win_start_menu;
windowprocs.win_end_menu=fixture_win_end_menu;
windowprocs.win_mark_synch=fixture_win_mark_synch;
windowprocs.win_wait_synch=fixture_win_wait_synch;
windowprocs.win_nhgetch=fixture_win_nhgetch;
windowprocs.win_nh_poskey=fixture_win_nh_poskey;
windowprocs.win_nhbell=fixture_win_nhbell;
windowprocs.win_doprev_message=fixture_win_doprev_message;
windowprocs.win_yn_function=fixture_win_yn_function;
windowprocs.win_get_ext_cmd=fixture_win_get_ext_cmd;
windowprocs.win_putmsghistory=fixture_win_putmsghistory;
windowprocs.win_can_suspend=fixture_win_can_suspend;
u.ux=u.uy=10;u.uhp=u.uhpmax=20;u.umonnum=PM_HUMAN;gu.urace.mnum=PM_HUMAN;gc.Cmd.dirchars="hykulnjb><";gc.Cmd.alphadirchars="hykulnjb><";for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;levl[x][y].seenv=0xff;}}
uintptr_t probe_data(int i){switch(i){
case 0:
#ifdef HYBRID_CMD
return(uintptr_t)&cmd_data_timed_occ_fn;
#else
return(uintptr_t)&timed_occ_fn;
#endif
case 1:
#ifdef HYBRID_CMD
return(uintptr_t)&cmd_data_readchar_queue;
#else
return(uintptr_t)&readchar_queue;
#endif
case 2:
#ifdef HYBRID_CMD
return(uintptr_t)&unavailcmd;
#else
return(uintptr_t)&unavailcmd;
#endif
case 3:
#ifdef HYBRID_CMD
return(uintptr_t)&cmd_data_cmdnotavail;
#else
return(uintptr_t)&cmdnotavail;
#endif
case 4:
#ifdef HYBRID_CMD
return(uintptr_t)&levltyp;
#else
return(uintptr_t)&levltyp;
#endif
case 5:
#ifdef HYBRID_CMD
return(uintptr_t)&extcmdlist;
#else
return(uintptr_t)&extcmdlist;
#endif
case 6:
#ifdef HYBRID_CMD
return(uintptr_t)&cmd_data_move_funcs;
#else
return(uintptr_t)&move_funcs;
#endif
case 7:
#ifdef HYBRID_CMD
return(uintptr_t)&cmd_data_misc_keys;
#else
return(uintptr_t)&misc_keys;
#endif
case 8:
#ifdef HYBRID_CMD
return(uintptr_t)&cmd_data_extcmdlist_length;
#else
return(uintptr_t)&extcmdlist_length;
#endif
case 9:
#ifdef HYBRID_CMD
return(uintptr_t)&cmd_data_spkeys_binds;
#else
return(uintptr_t)&spkeys_binds;
#endif
default:abort();}}
uintptr_t probe_function(int i){switch(i){
case 0:return(uintptr_t)timed_occupation;
case 1:return(uintptr_t)do_reqmenu;
case 2:return(uintptr_t)doextlist;
case 3:return(uintptr_t)dolookaround_floodfill_findroom;
case 4:return(uintptr_t)doextcmd;
case 5:return(uintptr_t)doorganize;
case 6:return(uintptr_t)donamelevel;
case 7:return(uintptr_t)doapply;
case 8:return(uintptr_t)doattributes;
case 9:return(uintptr_t)dotogglepickup;
case 10:return(uintptr_t)dobugreport;
case 11:return(uintptr_t)docallcmd;
case 12:return(uintptr_t)docast;
case 13:return(uintptr_t)dotalk;
case 14:return(uintptr_t)do_gamelog;
case 15:return(uintptr_t)doclose;
case 16:return(uintptr_t)doconduct;
case 17:return(uintptr_t)wiz_fuzzer;
case 18:return(uintptr_t)dodip;
case 19:return(uintptr_t)dodown;
case 20:return(uintptr_t)dodrop;
case 21:return(uintptr_t)doddrop;
case 22:return(uintptr_t)doeat;
case 23:return(uintptr_t)doengrave;
case 24:return(uintptr_t)enhance_weapon_skill;
case 25:return(uintptr_t)enter_explore_mode;
case 26:return(uintptr_t)do_fight;
case 27:return(uintptr_t)dofire;
case 28:return(uintptr_t)doforce;
case 29:return(uintptr_t)dogenocided;
case 30:return(uintptr_t)doquickwhatis;
case 31:return(uintptr_t)dohelp;
case 32:return(uintptr_t)doherecmdmenu;
case 33:return(uintptr_t)dohistory;
case 34:return(uintptr_t)ddoinv;
case 35:return(uintptr_t)dotypeinv;
case 36:return(uintptr_t)doinvoke;
case 37:return(uintptr_t)dojump;
case 38:return(uintptr_t)dokick;
case 39:return(uintptr_t)dodiscovered;
case 40:return(uintptr_t)doclassdisco;
case 41:return(uintptr_t)wiz_level_change;
case 42:return(uintptr_t)wiz_light_sources;
case 43:return(uintptr_t)dolook;
case 44:return(uintptr_t)dolookaround;
case 45:return(uintptr_t)doloot;
case 46:return(uintptr_t)wiz_migrate_mons;
case 47:return(uintptr_t)domonability;
case 48:return(uintptr_t)dosacrifice;
case 49:return(uintptr_t)doopen;
case 50:return(uintptr_t)doset_simple;
case 51:return(uintptr_t)doset;
case 52:return(uintptr_t)dooverview;
case 53:return(uintptr_t)wiz_panic;
case 54:return(uintptr_t)dopay;
case 55:return(uintptr_t)doperminv;
case 56:return(uintptr_t)dopickup;
case 57:return(uintptr_t)wiz_polyself;
case 58:return(uintptr_t)dopray;
case 59:return(uintptr_t)doprev_message;
case 60:return(uintptr_t)doputon;
case 61:return(uintptr_t)dodrink;
case 62:return(uintptr_t)done2;
case 63:return(uintptr_t)dowieldquiver;
case 64:return(uintptr_t)doread;
case 65:return(uintptr_t)doredraw;
case 66:return(uintptr_t)doremring;
case 67:return(uintptr_t)do_repeat;
case 68:return(uintptr_t)dotravel_target;
case 69:return(uintptr_t)doride;
case 70:return(uintptr_t)dorub;
case 71:return(uintptr_t)do_run;
case 72:return(uintptr_t)do_rush;
case 73:return(uintptr_t)dosave;
case 74:return(uintptr_t)do_write_config_file;
case 75:return(uintptr_t)dosearch;
case 76:return(uintptr_t)doprinuse;
case 77:return(uintptr_t)dopramulet;
case 78:return(uintptr_t)doprarm;
case 79:return(uintptr_t)doprring;
case 80:return(uintptr_t)doprtool;
case 81:return(uintptr_t)doprwep;
case 82:return(uintptr_t)dosh_core;
case 83:return(uintptr_t)doprgold;
case 84:return(uintptr_t)dovspell;
case 85:return(uintptr_t)doidtrap;
case 86:return(uintptr_t)dosit;
case 87:return(uintptr_t)wiz_show_stats;
case 88:return(uintptr_t)dosuspend_core;
case 89:return(uintptr_t)doswapweapon;
case 90:return(uintptr_t)dotakeoff;
case 91:return(uintptr_t)doddoremarm;
case 92:return(uintptr_t)dotelecmd;
case 93:return(uintptr_t)doterrain;
case 94:return(uintptr_t)dotherecmdmenu;
case 95:return(uintptr_t)dothrow;
case 96:return(uintptr_t)wiz_timeout_queue;
case 97:return(uintptr_t)dotip;
case 98:return(uintptr_t)dotoggleoption;
case 99:return(uintptr_t)dotravel;
case 100:return(uintptr_t)doturn;
case 101:return(uintptr_t)dotwoweapon;
case 102:return(uintptr_t)dountrap;
case 103:return(uintptr_t)doup;
case 104:return(uintptr_t)dovanquished;
case 105:return(uintptr_t)doextversion;
case 106:return(uintptr_t)doversion;
case 107:return(uintptr_t)wiz_show_vision;
case 108:return(uintptr_t)donull;
case 109:return(uintptr_t)dowear;
case 110:return(uintptr_t)dowhatdoes;
case 111:return(uintptr_t)dowhatis;
case 112:return(uintptr_t)dowield;
case 113:return(uintptr_t)dowipe;
case 114:return(uintptr_t)doborn;
case 115:return(uintptr_t)wiz_debug_cmd_bury;
case 116:return(uintptr_t)dowizcast;
case 117:return(uintptr_t)wiz_custom;
case 118:return(uintptr_t)wiz_detect;
case 119:return(uintptr_t)wiz_display_macros;
case 120:return(uintptr_t)wiz_flip_level;
case 121:return(uintptr_t)wiz_genesis;
case 122:return(uintptr_t)wiz_identify;
case 123:return(uintptr_t)wiz_intrinsic;
case 124:return(uintptr_t)wiz_kill;
case 125:return(uintptr_t)wiz_level_tele;
case 126:return(uintptr_t)wiz_load_splua;
case 127:return(uintptr_t)wiz_load_lua;
case 128:return(uintptr_t)wiz_objprobs;
case 129:return(uintptr_t)wiz_makemap;
case 130:return(uintptr_t)wiz_map;
case 131:return(uintptr_t)wiz_mon_diff;
case 132:return(uintptr_t)wiz_rumor_check;
case 133:return(uintptr_t)wiz_show_seenv;
case 134:return(uintptr_t)wiz_show_nhuuid;
case 135:return(uintptr_t)wiz_smell;
case 136:return(uintptr_t)wiz_telekinesis;
case 137:return(uintptr_t)wiz_where;
case 138:return(uintptr_t)wiz_wish;
case 139:return(uintptr_t)wiz_show_wmodes;
case 140:return(uintptr_t)dozap;
case 141:return(uintptr_t)do_move_west;
case 142:return(uintptr_t)do_move_northwest;
case 143:return(uintptr_t)do_move_north;
case 144:return(uintptr_t)do_move_northeast;
case 145:return(uintptr_t)do_move_east;
case 146:return(uintptr_t)do_move_southeast;
case 147:return(uintptr_t)do_move_south;
case 148:return(uintptr_t)do_move_southwest;
case 149:return(uintptr_t)do_rush_west;
case 150:return(uintptr_t)do_rush_northwest;
case 151:return(uintptr_t)do_rush_north;
case 152:return(uintptr_t)do_rush_northeast;
case 153:return(uintptr_t)do_rush_east;
case 154:return(uintptr_t)do_rush_southeast;
case 155:return(uintptr_t)do_rush_south;
case 156:return(uintptr_t)do_rush_southwest;
case 157:return(uintptr_t)do_run_west;
case 158:return(uintptr_t)do_run_northwest;
case 159:return(uintptr_t)do_run_north;
case 160:return(uintptr_t)do_run_northeast;
case 161:return(uintptr_t)do_run_east;
case 162:return(uintptr_t)do_run_southeast;
case 163:return(uintptr_t)do_run_south;
case 164:return(uintptr_t)do_run_southwest;
case 165:return(uintptr_t)doclicklook;
case 166:return(uintptr_t)domouseaction;
case 167:return(uintptr_t)adjust_split;
case 168:return(uintptr_t)dip_into;
case 169:return(uintptr_t)ia_dotakeoff;
case 170:return(uintptr_t)remarm_swapwep;
case 171:return(uintptr_t)dummyfunction;
default:abort();}}
uintptr_t probe_callback(int i){switch(i){
case 0:return(uintptr_t)fixture_win_exit_nhwindows;
case 1:return(uintptr_t)fixture_win_create_nhwindow;
case 2:return(uintptr_t)fixture_win_clear_nhwindow;
case 3:return(uintptr_t)fixture_win_display_nhwindow;
case 4:return(uintptr_t)fixture_win_destroy_nhwindow;
case 5:return(uintptr_t)fixture_win_putstr;
case 6:return(uintptr_t)fixture_win_start_menu;
case 7:return(uintptr_t)fixture_win_end_menu;
case 8:return(uintptr_t)fixture_win_mark_synch;
case 9:return(uintptr_t)fixture_win_wait_synch;
case 10:return(uintptr_t)fixture_win_nhgetch;
case 11:return(uintptr_t)fixture_win_nh_poskey;
case 12:return(uintptr_t)fixture_win_nhbell;
case 13:return(uintptr_t)fixture_win_doprev_message;
case 14:return(uintptr_t)fixture_win_yn_function;
case 15:return(uintptr_t)fixture_win_get_ext_cmd;
case 16:return(uintptr_t)fixture_win_putmsghistory;
case 17:return(uintptr_t)fixture_win_can_suspend;
default:abort();}}
const char*probe_string(int i){switch(i){
case 0:return "Never mind.";
case 1:return "an item";
case 2:return "monster";
case 3:return "small";
case 4:return "command";
case 5:return "hykulnjb><";
case 6:return "";
case 7:return "\n";
case 8:return "             %s   ";
case 9:return "             |   ";
case 10:return "           / | \\ ";
case 11:return "           \\ | / ";
case 12:return "          %s  %s  %s";
case 13:return "          %s- %c -%s";
case 14:return "          <  up";
case 15:return "          >  down";
case 16:return "       %4s  direct at yourself";
case 17:return "    Full Current Key Bindings List";
case 18:return " %-14s %4s %s";
case 19:return " (\"\")";
case 20:return " (\"%s\")";
case 21:return " (##)";
case 22:return " as specified in the Guidebook";
case 23:return " been genocided";
case 24:return " been genocided or become extinct";
case 25:return " in your current form";
case 26:return " interrupt: break out of NetHack (SIGINT)";
case 27:return " or ";
case 28:return " other than up or down";
case 29:return " to ";
case 30:return "!";
case 31:return "\"Yes\" or \"No\": ";
case 32:return "#";
case 33:return "#%-20s %s";
case 34:return "#%s";
case 35:return "#suspend";
case 36:return "%%-%ds";
case 37:return "%-21s %s";
case 38:return "%-7s";
case 39:return "%-7s %-13s %s";
case 40:return "%-7s %-13s %s \"%s\"";
case 41:return "%-7s %s";
case 42:return "%7s %s";
case 43:return "%c %s: %s";
case 44:return "%s";
case 45:return "%s ";
case 46:return "%s %s";
case 47:return "%s %s %s.";
case 48:return "%s (#%s)";
case 49:return "%s [%s] (%s)";
case 50:return "%s achievement revoked.";
case 51:return "%s prefix";
case 52:return "%s%s %s";
case 53:return "%s%s [%s]";
case 54:return "%s%s or %s";
case 55:return "%s(%s)";
case 56:return "%s.";
case 57:return "%s: %s";
case 58:return "%sunlock the door";
case 59:return "'%s' command not available.";
case 60:return "'%s' does not take a parameter";
case 61:return "'%s' prefix has no effect for the %s command.";
case 62:return "'%s' requires a parameter";
case 63:return "(Suppress this message with !cmdassist in config file.)";
case 64:return "(also commands with no key assignment)";
case 65:return "+<direction> will run in specified direction until you encounter";
case 66:return "...";
case 67:return "...?";
case 68:return "41236987><";
case 69:return "47896321><";
case 70:return "<del>";
case 71:return "<enter>";
case 72:return "<esc>";
case 73:return "<space>";
case 74:return "?";
case 75:return "AUTOCOMPLETE=%s%s\n";
case 76:return "All";
case 77:return "Any special ability you may have is purely reflexive.";
case 78:return "Are you trying to use ^%c%s?";
case 79:return "Attack %s";
case 80:return "Attempt to disarm trap";
case 81:return "BIND=%s:%s%s";
case 82:return "BIND=%s:%s(%s)%s";
case 83:return "BIND=%s:nothing%s";
case 84:return "Bad autocomplete: invalid extended command '%s'.";
case 85:return "Beware!  From explore mode there will be no return to %s,";
case 86:return "Bind '%s' to what command?";
case 87:return "Bind what command?";
case 88:return "Bind which key? ";
case 89:return "Bound key '%s' to \"%s\".";
case 90:return "Cast a spell";
case 91:return "Changed key '%s' from \"%s\" to \"%s\".";
case 92:return "Close the door";
case 93:return "Command %s requires a parameter:";
case 94:return "Continuing with %s.";
case 95:return "Count: ";
case 96:return "Count: %ld";
case 97:return "Count: %ld ";
case 98:return "Ctrl+<direction> will run in specified direction until something very";
case 99:return "Debug mode commands:";
case 100:return "Debugging Extended Commands";
case 101:return "Dip something into the fountain";
case 102:return "Directional keys:";
case 103:return "Dismount %s";
case 104:return "Do what?";
case 105:return "Do you want to enter explore mode?";
case 106:return "Double %s prefix, canceled.";
case 107:return "Double fight prefix, canceled.";
case 108:return "Double run prefix, canceled.";
case 109:return "Double rush prefix, canceled.";
case 110:return "Drink from the %s";
case 111:return "Drop items";
case 112:return "EFGIVW";
case 113:return "Eat %s";
case 114:return "Examine trap";
case 115:return "Extended Command: %s";
case 116:return "Extended Commands List";
case 117:return "Extended command list search phrase";
case 118:return "Extended commands";
case 119:return "Game commands:";
case 120:return "General commands:";
case 121:return "Go down the %s";
case 122:return "Go up the %s";
case 123:return "Hide";
case 124:return "Hide [h] or spin a web [s]?";
case 125:return "In what direction?";
case 126:return "Invalid direction key!";
case 127:return "Inventory";
case 128:return "Key '%s' is currently bound to \"%s\".";
case 129:return "Key '%s' is not bound to anything.";
case 130:return "Key binding failed?!";
case 131:return "Kick the door";
case 132:return "Left";
case 133:return "Look at map symbol";
case 134:return "Look at what is here";
case 135:return "Loot %s";
case 136:return "Meta";
case 137:return "Mine's-end";
case 138:return "Miscellaneous keys:";
case 139:return "Move on the trap";
case 140:return "Name";
case 141:return "No";
case 142:return "No travel destination set.";
case 143:return "Note: normally you wouldn't be allowed into explore mode.";
case 144:return "Open the door";
case 145:return "Pick up %s";
case 146:return "Prefix: for digits when preceding a command with a count";
case 147:return "Push the boulder";
case 148:return "Put saddle on %s";
case 149:return "Query truncated: ";
case 150:return "Quit";
case 151:return "Remove saddle from %s";
case 152:return "Rename";
case 153:return "Required parameter cannot be empty";
case 154:return "Rest one turn";
case 155:return "Ride %s";
case 156:return "Right";
case 157:return "Sacrifice something on the altar";
case 158:return "Search around you";
case 159:return "Search extended commands";
case 160:return "Search for secret doors";
case 161:return "Search the door for a trap";
case 162:return "Shift";
case 163:return "Sit on the throne";
case 164:return "Soko-prize";
case 165:return "Spin a web";
case 166:return "Swap places with %s";
case 167:return "Switch back from search";
case 168:return "Switch to %s commands that don't autocomplete";
case 169:return "Switch to showing all alphabetically, including debugging commands";
case 170:return "Switch to showing debugging commands in separate section";
case 171:return "Talk to %s";
case 172:return "The %s command does not accept '%s' prefix.";
case 173:return "The '%s' prefix should be followed by a movement command%s.";
case 174:return "There is no command available to repeat.";
case 175:return "Throw something";
case 176:return "Tip %s";
case 177:return "To use that command, hold down the <Ctrl> key as a shift";
case 178:return "Travel here";
case 179:return "Unavailable command '%s'.";
case 180:return "Unfortunately sound does not carry well through rock.";
case 181:return "Unknown command '%s'.";
case 182:return "Use #optionsfull to set any option instead.";
case 183:return "Valid direction keys%s%s%s are:";
case 184:return "View which?";
case 185:return "What a strange direction!";
case 186:return "What do you want to do?";
case 187:return "Where do you want to travel to?";
case 188:return "Which commands autocomplete?";
case 189:return "Wrong mouse button, valid are 1-%i";
case 190:return "Yes";
case 191:return "[%s]";
case 192:return "[A] Command autocompletes";
case 193:return "[m] Command accepts '%s' prefix";
case 194:return "[yes|n] (n)";
case 195:return "[yes|no]";
case 196:return "[yes|no|quit]";
case 197:return "[yes|n|q] (n)";
case 198:return "adjust";
case 199:return "adjust inventory letters";
case 200:return "advance or check weapon and spell skills";
case 201:return "air";
case 202:return "altadjust";
case 203:return "altar";
case 204:return "altdip";
case 205:return "alttakeoff";
case 206:return "altunwield";
case 207:return "an obstacle.";
case 208:return "and press the <%c> key.";
case 209:return "annotate";
case 210:return "apply";
case 211:return "apply (use) a tool (pick-axe, key, lamp...)";
case 212:return "are already here.";
case 213:return "are already in explore mode.";
case 214:return "are in";
case 215:return "are now in non-scoring explore mode.";
case 216:return "area";
case 217:return "attributes";
case 218:return "autopickup";
case 219:return "bind command to a key";
case 220:return "bind key to a command";
case 221:return "bottom-left corner wall";
case 222:return "bottom-right corner wall";
case 223:return "bugreport";
case 224:return "bury objs under and around you";
case 225:return "call";
case 226:return "can't guess the size of %s area.";
case 227:return "can_do_extcmd";
case 228:return "cancel current prompt or pending prefix";
case 229:return "cannot access explore mode.";
case 230:return "cast";
case 231:return "cast any spell";
case 232:return "change experience level";
case 233:return "chat";
case 234:return "chronicle";
case 235:return "clicklook";
case 236:return "close";
case 237:return "close a door";
case 238:return "cloud";
case 239:return "cmd.c";
case 240:return "cmdassist: %s";
case 241:return "cmdname_from_func";
case 242:return "conduct";
case 243:return "confdir";
case 244:return "corridor";
case 245:return "count";
case 246:return "create a monster";
case 247:return "cross wall";
case 248:return "debug mode";
case 249:return "debugfuzzer";
case 250:return "describe an adjacent, discovered trap";
case 251:return "describe what you can see";
case 252:return "desired location, then type '%s' for left click, '%s' for right";
case 253:return "dip";
case 254:return "dip an object into something";
case 255:return "do that";
case 256:return "do that while you are buried!";
case 257:return "dokeylist";
case 258:return "don't have a special ability in your normal form!";
case 259:return "door";
case 260:return "down";
case 261:return "drawbridge down";
case 262:return "drawbridge up";
case 263:return "drawbridge wall";
case 264:return "drop";
case 265:return "drop an item";
case 266:return "drop specific item types";
case 267:return "droptype";
case 268:return "east";
case 269:return "eat";
case 270:return "eat something";
case 271:return "empty a container";
case 272:return "end_of_input";
case 273:return "engrave";
case 274:return "engrave writing on the floor";
case 275:return "enhance";
case 276:return "enter and perform an extended command";
case 277:return "enter explore (discovery) mode";
case 278:return "escape";
case 279:return "excluding";
case 280:return "exit without saving current game";
case 281:return "exploremode";
case 282:return "extcmd_via_menu";
case 283:return "extcmds_match";
case 284:return "extinct";
case 285:return "fight";
case 286:return "file a bug report";
case 287:return "fire";
case 288:return "fire ammunition from quiver";
case 289:return "flip the level";
case 290:return "force";
case 291:return "force a lock";
case 292:return "fountain";
case 293:return "full map without monsters, objects, and traps";
case 294:return "genocided";
case 295:return "get there from here...";
case 296:return "get_count: cmdcount_nht";
case 297:return "getdir";
case 298:return "getdir.help";
case 299:return "getdir.mouse";
case 300:return "getdir.self";
case 301:return "getdir.self2";
case 302:return "getdir: command queue had no dir?";
case 303:return "getpos successful but not one of [.,;:] (%d)";
case 304:return "getpos.all.next";
case 305:return "getpos.all.prev";
case 306:return "getpos.autodescribe";
case 307:return "getpos.door.next";
case 308:return "getpos.door.prev";
case 309:return "getpos.filter";
case 310:return "getpos.help";
case 311:return "getpos.menu";
case 312:return "getpos.mon.next";
case 313:return "getpos.mon.prev";
case 314:return "getpos.moveskip";
case 315:return "getpos.obj.next";
case 316:return "getpos.obj.prev";
case 317:return "getpos.pick";
case 318:return "getpos.pick.once";
case 319:return "getpos.pick.quick";
case 320:return "getpos.pick.verbose";
case 321:return "getpos.self";
case 322:return "getpos.unexplored.next";
case 323:return "getpos.unexplored.prev";
case 324:return "getpos.valid";
case 325:return "getpos.valid.next";
case 326:return "getpos.valid.prev";
case 327:return "give a help message";
case 328:return "glance";
case 329:return "go down a staircase";
case 330:return "go up a staircase";
case 331:return "grave";
case 332:return "guess %s to be %s %s.";
case 333:return "handler_rebind_keys_add";
case 334:return "help";
case 335:return "herecmdmenu";
case 336:return "history";
case 337:return "horizontal wall";
case 338:return "hykulnjb><";
case 339:return "hzkulnjb><";
case 340:return "ice";
case 341:return "identify all items in inventory";
case 342:return "including";
case 343:return "interesting is seen.";
case 344:return "internal levl[][].typ codes in base-36";
case 345:return "invalid";
case 346:return "inventory";
case 347:return "inventtype";
case 348:return "invoke";
case 349:return "invoke an object's special powers";
case 350:return "iron bars";
case 351:return "is no fountain here.";
case 352:return "items";
case 353:return "jump";
case 354:return "jump to another location";
case 355:return "kick";
case 356:return "kick something";
case 357:return "known";
case 358:return "known map without monsters";
case 359:return "known map without monsters and objects";
case 360:return "known map without monsters, objects, and traps";
case 361:return "knownclass";
case 362:return "ladder";
case 363:return "lava pool";
case 364:return "lava wall";
case 365:return "leave game to enter a sub-shell ('exit' to come back)";
case 366:return "legend of base-36 levl[][].typ codes";
case 367:return "levelchange";
case 368:return "lightsources";
case 369:return "list all extended commands";
case 370:return "list and reorder known spells";
case 371:return "list compile time options for this version of NetHack";
case 372:return "list monsters that have been genocided or become extinct";
case 373:return "list object generation probabilities";
case 374:return "list vanquished monsters";
case 375:return "list voluntary challenges you have maintained";
case 376:return "load and execute a des-file lua script";
case 377:return "load and execute a lua script";
case 378:return "lock or ";
case 379:return "look";
case 380:return "look at timeout queue and hero's timed intrinsics";
case 381:return "look at what is here";
case 382:return "lookaround";
case 383:return "loot";
case 384:return "loot a box on the floor";
case 385:return "map the level";
case 386:return "menu of commands you can do from here to adjacent spot";
case 387:return "migratemons";
case 388:return "moat";
case 389:return "monster";
case 390:return "mount or dismount a saddled steed";
case 391:return "mouseaction";
case 392:return "move";
case 393:return "move east (screen right)";
case 394:return "move north (screen up)";
case 395:return "move northeast (screen upper right)";
case 396:return "move northwest (screen upper left)";
case 397:return "move south (screen down)";
case 398:return "move southeast (screen lower right)";
case 399:return "move southwest (screen lower left)";
case 400:return "move west (screen left)";
case 401:return "move-no-pickup or request-menu";
case 402:return "moveeast";
case 403:return "movement prefix: move without autopickup and without attacking\nnon-movement prefix:";
case 404:return "movenorth";
case 405:return "movenortheast";
case 406:return "movenorthwest";
case 407:return "movesouth";
case 408:return "movesoutheast";
case 409:return "movesouthwest";
case 410:return "movewest";
case 411:return "name";
case 412:return "name a monster, specific object, or type of object";
case 413:return "name current level";
case 414:return "nh_callback_run";
case 415:return "no";
case 416:return "no matches";
case 417:return "normal game";
case 418:return "north";
case 419:return "northeast";
case 420:return "northwest";
case 421:return "nothing";
case 422:return "nothing: unbind the key";
case 423:return "offer";
case 424:return "offer a sacrifice to the gods";
case 425:return "open";
case 426:return "open a door";
case 427:return "options";
case 428:return "optionsfull";
case 429:return "or ";
case 430:return "orient yourself that direction.";
case 431:return "overview";
case 432:return "panic";
case 433:return "paranoid_ynq";
case 434:return "pay";
case 435:return "pay your shopping bill";
case 436:return "perminv";
case 437:return "pick up things at the current location";
case 438:return "pickup";
case 439:return "polymorph self";
case 440:return "polyself";
case 441:return "pool";
case 442:return "pray";
case 443:return "pray to the gods for help";
case 444:return "prefix:";
case 445:return "prefix: force fight even if you don't see a monster";
case 446:return "prefix: request menu or modify command";
case 447:return "prefix: run until something interesting is seen";
case 448:return "prefix: rush until something interesting is seen";
case 449:return "prevmsg";
case 450:return "push game to background ('fg' to come back)";
case 451:return "put on an accessory (ring, amulet, etc)";
case 452:return "puton";
case 453:return "quaff";
case 454:return "quaff (drink) something";
case 455:return "quit";
case 456:return "quiver";
case 457:return "randomkey";
case 458:return "read";
case 459:return "read a scroll or spellbook";
case 460:return "recreate the current level";
case 461:return "redraw";
case 462:return "redraw screen";
case 463:return "remember that as";
case 464:return "remember this as";
case 465:return "remove";
case 466:return "remove all armor";
case 467:return "remove an accessory (ring, amulet, etc)";
case 468:return "repeat";
case 469:return "repeat a previous command";
case 470:return "reqmenu";
case 471:return "rest one move via 'rest_on_space' option";
case 472:return "rest one move while doing nothing";
case 473:return "retravel";
case 474:return "reveal hidden things within a small radius";
case 475:return "ride";
case 476:return "rnd_extcmd_idx";
case 477:return "room";
case 478:return "rub";
case 479:return "rub a lamp or a stone";
case 480:return "run";
case 481:return "run east (screen right)";
case 482:return "run north (screen up)";
case 483:return "run northeast (screen upper right)";
case 484:return "run northwest (screen upper left)";
case 485:return "run south (screen down)";
case 486:return "run southeast (screen lower right)";
case 487:return "run southwest (screen lower left)";
case 488:return "run west (screen left)";
case 489:return "runeast";
case 490:return "runnorth";
case 491:return "runnortheast";
case 492:return "runnorthwest";
case 493:return "runsouth";
case 494:return "runsoutheast";
case 495:return "runsouthwest";
case 496:return "runwest";
case 497:return "rush";
case 498:return "rush east (screen right)";
case 499:return "rush north (screen up)";
case 500:return "rush northeast (screen upper right)";
case 501:return "rush northwest (screen upper left)";
case 502:return "rush south (screen down)";
case 503:return "rush southeast (screen lower right)";
case 504:return "rush southwest (screen lower left)";
case 505:return "rush west (screen left)";
case 506:return "rusheast";
case 507:return "rushnorth";
case 508:return "rushnortheast";
case 509:return "rushnorthwest";
case 510:return "rushsouth";
case 511:return "rushsoutheast";
case 512:return "rushsouthwest";
case 513:return "rushwest";
case 514:return "same as call; name a monster or object or object type";
case 515:return "save";
case 516:return "save the game and exit";
case 517:return "save the game configuration";
case 518:return "saveoptions";
case 519:return "scroll persistent inventory display";
case 520:return "search";
case 521:return "search for traps and secret doors";
case 522:return "searching";
case 523:return "secret corridor";
case 524:return "secret door";
case 525:return "seeall";
case 526:return "seeamulet";
case 527:return "seearmor";
case 528:return "seerings";
case 529:return "seetools";
case 530:return "seeweapon";
case 531:return "select ammunition for quiver";
case 532:return "set an intrinsic";
case 533:return "shell";
case 534:return "shortened %s: \"%s\"";
case 535:return "show NHUUID for this game";
case 536:return "show a summary of the explored dungeon";
case 537:return "show a summary of the game's development";
case 538:return "show all equipment in use";
case 539:return "show all option settings, possibly change them";
case 540:return "show customized glyphs";
case 541:return "show discovered types for one class of objects";
case 542:return "show gold, possibly shop credit or debt";
case 543:return "show inventory of one specific item class";
case 544:return "show journal of major events";
case 545:return "show locations of special levels";
case 546:return "show map locations' seen vectors";
case 547:return "show memory statistics";
case 548:return "show menu of commands you can do here";
case 549:return "show migrating monsters and migrate N random ones";
case 550:return "show mobile light sources";
case 551:return "show option settings";
case 552:return "show stats of monsters created";
case 553:return "show the amulet currently worn";
case 554:return "show the armor currently worn";
case 555:return "show the ring(s) currently worn";
case 556:return "show the tools currently in use";
case 557:return "show the weapon currently wielded";
case 558:return "show version and date+time program was built";
case 559:return "show vision array";
case 560:return "show wall modes";
case 561:return "show what object types have been discovered";
case 562:return "show what type of thing a map symbol corresponds to";
case 563:return "show what type of thing a symbol corresponds to";
case 564:return "show your attributes";
case 565:return "show your inventory";
case 566:return "showgold";
case 567:return "showspells";
case 568:return "showtrap";
case 569:return "shriek.";
case 570:return "sink";
case 571:return "sit";
case 572:return "sit down";
case 573:return "slay a monster";
case 574:return "smell monster";
case 575:return "south";
case 576:return "southeast";
case 577:return "southwest";
case 578:return "stairs";
case 579:return "start of, or continuation of, a count";
case 580:return "start the fuzz tester";
case 581:return "stats";
case 582:return "stone";
case 583:return "suspend";
case 584:return "swap";
case 585:return "swap wielded and secondary weapons";
case 586:return "synonym for 'i'";
case 587:return "take off one piece of armor";
case 588:return "takeoff";
case 589:return "takeoffall";
case 590:return "talk to someone";
case 591:return "tee-down wall";
case 592:return "tee-left wall";
case 593:return "tee-right wall";
case 594:return "tee-up wall";
case 595:return "telekinesis";
case 596:return "teleport";
case 597:return "teleport around the level";
case 598:return "teleport to another level";
case 599:return "tell what a command does";
case 600:return "terrain";
case 601:return "test panic routine (fatal to game)";
case 602:return "that";
case 603:return "the desired destination";
case 604:return "therecmdmenu";
case 605:return "this";
case 606:return "throne";
case 607:return "throw";
case 608:return "throw something";
case 609:return "timeout";
case 610:return "tip";
case 611:return "toggle";
case 612:return "toggle boolean option";
case 613:return "toggle the 'autopickup' option on/off";
case 614:return "toggle two-weapon combat";
case 615:return "top-left corner wall";
case 616:return "top-right corner wall";
case 617:return "travel";
case 618:return "travel to a specific location on the map";
case 619:return "travel to previously selected travel location";
case 620:return "tree";
case 621:return "turn";
case 622:return "turn undead away";
case 623:return "twoweapon";
case 624:return "unreachable/undiggable";
case 625:return "unseen creature";
case 626:return "untrap";
case 627:return "untrap something";
case 628:return "up";
case 629:return "use monster's special ability";
case 630:return "validate the difficulty ratings of monsters";
case 631:return "validate the display macro ranges";
case 632:return "vanquished";
case 633:return "verify rumor boundaries";
case 634:return "version";
case 635:return "versionshort";
case 636:return "vertical wall";
case 637:return "view changed key binds";
case 638:return "view map without monsters or objects obstructing it";
case 639:return "view recent game messages";
case 640:return "vision";
case 641:return "wait";
case 642:return "waiting";
case 643:return "water";
case 644:return "wear";
case 645:return "wear a piece of armor";
case 646:return "west";
case 647:return "whatdoes";
case 648:return "whatis";
case 649:return "wield";
case 650:return "wield (put in use) a weapon";
case 651:return "wipe";
case 652:return "wipe off your face";
case 653:return "wish for something";
case 654:return "wizborn";
case 655:return "wizbury";
case 656:return "wizcast";
case 657:return "wizcustom";
case 658:return "wizdetect";
case 659:return "wizdispmacros";
case 660:return "wizfliplevel";
case 661:return "wizgenesis";
case 662:return "wizidentify";
case 663:return "wizintrinsic";
case 664:return "wizkill";
case 665:return "wizlevelport";
case 666:return "wizloaddes";
case 667:return "wizloadlua";
case 668:return "wizmakemap";
case 669:return "wizmap";
case 670:return "wizmondiff";
case 671:return "wizobjprobs";
case 672:return "wizrumorcheck";
case 673:return "wizseenv";
case 674:return "wizshownhuuid";
case 675:return "wizsmell";
case 676:return "wiztelekinesis";
case 677:return "wizwhere";
case 678:return "wizwish";
case 679:return "wmode";
case 680:return "yes";
case 681:return "yn debug";
case 682:return "yn_function";
case 683:return "yn_function() returned '%s'; using '%s' instead";
case 684:return "zap";
case 685:return "zap (cast) a spell";
case 686:return "zap a wand";
default:return 0;}}
int probe_string_count(void){return 687;}
size_t probe_string_capacity(int i){const char*p=probe_string(i);return p?strlen(p)+1:0;}
