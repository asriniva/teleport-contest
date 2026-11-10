/* Controlled external world; PAGER source is included in reference mode only.
 * File parsing uses actual libc stdio, not dependency stubs. */
#include "hack.h"
#include "tu-pager-layout.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
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
__typeof__(gd) gd;
__typeof__(gf) gf;
__typeof__(svc) svc;
__typeof__(svp) svp;
__typeof__(sysopt) sysopt;
__typeof__(program_state) program_state;
struct permonst mons[NUMMONS+1];struct objclass objects[NUM_OBJECTS+1];struct objdescr obj_descr[NUM_OBJECTS+1];
volatile struct window_procs windowprocs;winid WIN_MESSAGE;struct obj*uball;
const struct c_common_strings c_common_strings={.c_something="something"};
const char ynchars[]="yn";
const glyph_info nul_glyphinfo={0};
static seenV vision[ROWNO][COLNO];static seenV*visionrows[ROWNO];static struct monst mon[4];static struct obj obj[4];static struct trap traps[4];static struct engr engr;static NhRegion region;
static coord cc;static coord*heldcc;static long automatic_sp;static anything resultany;static union {struct obj*o;struct permonst*pm;const char*s;long l;unsigned long u;int i;coordxy c;boolean b;} resultcell[4];static char buf[4096],buf2[4096],input[BUFSZ],scratch[4][BUFSZ];
static char tracebuf[4194304],snap[4194304];static long opts[2048];static int pos,reenter,menu_mode,glyphs[COLNO][ROWNO],cmdqueued,draws;static unsigned rngstate;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);if(pos>=sizeof tracebuf-2048)abort();}
EM_JS(void,fixture_throw,(void),{throw new Error('PAGER controlled callback');});
static void callback(void){if(opts[30]){opts[30]=0;emscripten_resize_heap(emscripten_get_heap_size()+16777216);}if(opts[31]){opts[31]=0;fixture_throw();}if(opts[32]&&!reenter){reenter=1;char tmp[BUFSZ];ice_descr(12,10,tmp);logmsg("reentry:%s;",tmp);reenter=0;}if(opts[33]){cc.x=opts[34];cc.y=opts[35];}}
void pline(const char*f,...){va_list ap;logmsg("pline:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
void impossible(const char*f,...){va_list ap;logmsg("impossible:");va_start(ap,f);pos+=vsnprintf(tracebuf+pos,sizeof tracebuf-pos,f,ap);va_end(ap);logmsg(";");callback();}
static int mid(struct monst*p){return p==&gy.youmonst?9:p&&p>=mon&&p<mon+4?1+(p-mon):0;}
static int oid(struct obj*p){return p&&p>=obj&&p<obj+4?1+(p-obj):0;}
static winid backend_create(int t){logmsg("create:%d;",t);callback();return 17;}
static void backend_start(winid w,unsigned long f){logmsg("start:%d/%lu;",w,f);callback();}
static void backend_end(winid w,const char*s){logmsg("end:%d:%s;",w,s);callback();}
static void backend_destroy(winid w){logmsg("destroy:%d;",w);callback();}
static void backend_display(winid w,boolean b){logmsg("display:%d/%d;",w,b);callback();}
static void backend_file(const char*s,boolean b){logmsg("file:%s/%d;",s,b);callback();}
static void backend_putstr(winid w,int attr,const char*s){if(opts[57]){long sp=emscripten_stack_get_current();if(!automatic_sp)automatic_sp=sp;logmsg("line-stack:%ld;",sp-automatic_sp);}logmsg("put:%d/%d:%s;",w,attr,s);callback();}
static void backend_putmixed(winid w,int attr,const char*s){logmsg("mixed:%d/%d:%s;",w,attr,s);callback();}
void add_menu(winid w,const glyph_info*g,const anything*a,char c,char group,int attr,int color,const char*s,unsigned f){logmsg("menu:%d:%d/%d/%d/%d/%d:%s:%u;",w,a?a->a_int:0,c,group,attr,color,s,f);callback();}
int select_menu(winid w,int how,menu_item**p){logmsg("select:%d/%d;",w,how);*p=0;callback();if(menu_mode>0){*p=malloc(sizeof **p);(*p)->item.a_int=menu_mode;return 1;}return menu_mode;}
void add_menu_str(winid w,const char*s){backend_putstr(w,ATR_NONE,s);}
void option_help(void){logmsg("option_help;");callback();}
void dokeylist(void){logmsg("dokeylist;");callback();}
boolean In_hell(d_level * a0){logmsg("In_hell:;");callback();return opts[100];}
boolean In_mines(d_level * a0){logmsg("In_mines:;");callback();return opts[101];}
int Mgender(struct monst * a0){logmsg("Mgender:;");callback();return opts[102];}
const char * align_str(aligntyp a0){logmsg("align_str:%ld;",(long)a0);callback();return "fixture";}
int altarmask_at(coordxy a0,coordxy a1){logmsg("altarmask_at:%ld:%ld;",(long)a0,(long)a1);callback();return opts[103];}
char * an(const char * a0){logmsg("an:;");callback();return (char*)a0;}
char * ansimpleoname(struct obj * a0){logmsg("ansimpleoname:;");callback();return "fixture";}
boolean closed_door(coordxy x,coordxy y){return isok(x,y)&&IS_DOOR(levl[x][y].typ)&&(levl[x][y].doormask&D_CLOSED);}
char cmd_from_func(int (*f)(void)){logmsg("command:%d;",f==doset?1:f==do_reqmenu?2:f==doset_simple?3:0);callback();return opts[42];}
const char * cmdname_from_func(int (*f)(void),char * out,boolean full){logmsg("cmdname:%d/%d;",f==doset?1:f==do_reqmenu?2:f==doset_simple?3:0,full);callback();return opts[43]?0:opts[44]?"#custom":"custom";}
void cmdq_clear(int which){logmsg("cmdq_clear:%d;",which);}
struct _cmd_queue * cmdq_pop(void){if(!cmdqueued)return 0;cmdqueued=0;struct _cmd_queue*p=malloc(sizeof *p);memset(p,0,sizeof *p);p->typ=opts[48];p->key=opts[49];return p;}
char * coord_desc(coordxy x,coordxy y,char * out,char mode){sprintf(out,"%d,%d/%d",x,y,mode);callback();return out;}
boolean costly_spot(coordxy a0,coordxy a1){logmsg("costly_spot:%ld:%ld;",(long)a0,(long)a1);callback();return opts[104];}
char * coyotename(struct monst * m,char * out){strcpy(out,"Coyote");callback();return out;}
schar db_under_typ(int a0){logmsg("db_under_typ:%ld;",(long)a0);callback();return opts[105];}
void dealloc_obj(struct obj * o){logmsg("dealloc:%d;",oid(o));o->where=0;callback();}
char * decode_mixed(char * a0,const char * a1){logmsg("decode_mixed:;");callback();return "fixture";}
char display_inventory(const char * a0,boolean a1){logmsg("display_inventory:%ld;",(long)a1);callback();return opts[106];}
char * distant_monnam(struct monst * m,int article,char * out){sprintf(out,"monster%d",mid(m));callback();return out;}
char * distant_name(struct obj * o,char *(*f)(struct obj *)){logmsg("distant:%d/%d;",oid(o),f==doname_with_price?1:f==doname_vague_quan?2:0);callback();return f(o);}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){logmsg("dmgtype_fromattack:%ld:%ld;",(long)a1,(long)a2);callback();return 0;}
int do_reqmenu(void){logmsg("do_reqmenu:;");callback();return opts[107];}
int doextlist(void){logmsg("doextlist:;");callback();return opts[108];}
int doextversion(void){logmsg("doextversion:;");callback();return opts[109];}
char * doname_vague_quan(struct obj * o){sprintf(scratch[2],"vague object%d",o->otyp);callback();return scratch[2];}
char * doname_with_price(struct obj * o){sprintf(scratch[2],"priced object%d",o->otyp);callback();return scratch[2];}
int doset(void){logmsg("doset:;");callback();return opts[110];}
int doset_simple(void){logmsg("doset_simple:;");callback();return opts[111];}
void dumplogmsg(const char * a0){logmsg("dumplogmsg:;");callback();}
char * encglyph(int a0){logmsg("encglyph:%ld;",(long)a0);callback();return "fixture";}
struct engr * engr_at(coordxy x,coordxy y){return opts[51]?&engr:0;}
struct fruit * fruit_from_name(const char * s,boolean exact,int * id){return 0;}
int getdir(const char * s){logmsg("getdir:%s;",s);callback();return !opts[50];}
void getlin(const char * query,char * out){logmsg("getlin:%s;",query);strcpy(out,input);callback();}
int getpos(coord * c,boolean force,const char * goal){logmsg("getpos:%d/%d:%d:%s;",c->x,c->y,force,goal);c->x=12;c->y=10;heldcc=c;callback();return opts[40];}
int glyph_at(coordxy x,coordxy y){return isok(x,y)?glyphs[x][y]:NO_GLYPH;}
const char * hliquid(const char * s){logmsg("hliquid:%s;",s);callback();return Hallucination?"orange juice":s;}
unsigned int howmonseen(struct monst * m){logmsg("seen:%d;",mid(m));callback();return opts[52];}
void introff(void){logmsg("introff:;");callback();}
void intron(void){logmsg("intron:;");callback();}
int is_drawbridge_wall(coordxy a0,coordxy a1){logmsg("is_drawbridge_wall:%ld:%ld;",(long)a0,(long)a1);callback();return opts[112];}
boolean is_lava(coordxy x,coordxy y){return isok(x,y)&&IS_LAVA(levl[x][y].typ);}
boolean is_pool(coordxy x,coordxy y){return isok(x,y)&&IS_POOL(levl[x][y].typ);}
boolean is_treefruit(struct obj * a0){logmsg("is_treefruit:;");callback();return opts[113];}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
const char * key2extcmddesc(uchar key){logmsg("keydesc:%d;",key);callback();return opts[46]?0:opts[47]?"description with\nnewline":"command description";}
char * key2txt(uchar key,char * out){sprintf(out,"K%d",key);return out;}
char * makeplural(const char * a0){logmsg("makeplural:;");callback();return (char*)a0;}
char * makesingular(const char * a0){logmsg("makesingular:;");callback();return (char*)a0;}
void map_glyphinfo(coordxy x,coordxy y,int g,unsigned int f,glyph_info * out){logmsg("mapglyph:%d/%d/%d/%u;",x,y,g,f);*out=nul_glyphinfo;out->glyph=g;out->ttychar=opts[54]?opts[54]:gs.showsyms[glyph_to_cmap(g)];if(opts[56]&&heldcc){heldcc->x=30;heldcc->y=15;logmsg("heldcc_mutate:30/15;");opts[56]=0;}callback();}
struct obj * mkobj(int cls,boolean art){logmsg("mkobj:%d/%d;",cls,art);obj[3].otyp=SLIME_MOLD;obj[3].oclass=cls;callback();return &obj[3];}
struct obj * mksobj(int typ,boolean init,boolean art){logmsg("mksobj:%d/%d/%d;",typ,init,art);obj[3].otyp=typ;obj[3].oclass=objects[typ].oc_class;callback();return &obj[3];}
char * mon_nam(struct monst * m){sprintf(scratch[0],"monster%d",mid(m));callback();return scratch[0];}
void obj_stop_timers(struct obj * o){logmsg("stop:%d;",oid(o));o->timed=0;callback();}
void observe_object(struct obj * o){logmsg("observe:%d:%ld;",oid(o),o->quan);o->dknown=1;callback();}
boolean ok_to_quest(void){logmsg("ok_to_quest:;");callback();return opts[114];}
boolean on_level(d_level * a,d_level * b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
const char * pmname(struct permonst * p,int gender){return p->pmnames[gender];}
int rn2_on_display_rng(int n){rngstate=rngstate*1664525U+1013904223U;int v=(rngstate>>1)%(unsigned)n;logmsg("displayrng:%d/%d;",n,v);draws++;if(opts[55]){u.ustuck=&mon[1];logmsg("rng_mutate_ustuck:%d;",mid(u.ustuck));}callback();return v;}
char * rndmonnam(char * a0){logmsg("rndmonnam:;");callback();return "fixture";}
void show_menu_controls(winid a0,boolean a1){logmsg("show_menu_controls:%ld:%ld;",(long)a0,(long)a1);callback();}
char * simpleonames(struct obj * a0){logmsg("simpleonames:;");callback();return "fixture";}
const char * singular(struct obj * o,char *(*f)(struct obj *)){logmsg("singular:%d/%d;",oid(o),f==xname);callback();return f(o);}
struct obj * sobj_at(int typ,coordxy x,coordxy y){for(int i=0;i<3;i++)if(obj[i].where==OBJ_FLOOR&&obj[i].otyp==typ&&obj[i].ox==x&&obj[i].oy==y)return &obj[i];return 0;}
long spot_time_left(coordxy x,coordxy y,short typ){logmsg("time:%d/%d/%d:%ld;",x,y,typ,opts[45]);callback();return opts[45];}
boolean sticks(struct permonst * a0){logmsg("sticks:;");callback();return opts[115];}
const char * surface(coordxy a0,coordxy a1){logmsg("surface:%ld:%ld;",(long)a0,(long)a1);callback();return "fixture";}
struct trap * t_at(coordxy x,coordxy y){for(int i=0;i<4;i++)if(traps[i].ttyp&&traps[i].tx==x&&traps[i].ty==y)return &traps[i];return 0;}
char * the(const char * a0){logmsg("the:;");callback();return (char*)a0;}
char * trap_predicament(char * a0,int a1,boolean a2){logmsg("trap_predicament:%ld:%ld;",(long)a1,(long)a2);callback();return "fixture";}
const char * trapname(int a0,boolean a1){logmsg("trapname:%ld:%ld;",(long)a0,(long)a1);callback();return "fixture";}
boolean trapped_chest_at(int a0,coordxy a1,coordxy a2){logmsg("trapped_chest_at:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback();return opts[116];}
boolean trapped_door_at(int a0,coordxy a1,coordxy a2){logmsg("trapped_door_at:%ld:%ld:%ld;",(long)a0,(long)a1,(long)a2);callback();return opts[117];}
NhRegion * visible_region_at(coordxy x,coordxy y){return opts[58]?&region:0;}
char * xname(struct obj * o){sprintf(scratch[2],"object%d",o->otyp);callback();return scratch[2];}
char * y_monnam(struct monst * m){sprintf(scratch[1],"your monster%d",mid(m));callback();return scratch[1];}
char yn_function(const char * query,const char * resp,char def,boolean hidden){logmsg("yn:%s:%s/%d/%d;",query,resp?resp:"NULL",def,hidden);callback();return opts[41]?opts[41]:def;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/pager.c"
#define TELEPORT_PAGER_VALIDATE_SOURCE
_Static_assert(sizeof what_is_a_location==30,"PAGER public array changed");
boolean teleport_pager_callback_is_swallow_sym(int c){return is_swallow_sym(c);}
int teleport_pager_callback_append_str(char * buf,const char * new_str){return append_str(buf,new_str);}
void teleport_pager_callback_trap_description(char * outbuf,int tnum,coordxy x,coordxy y){trap_description(outbuf,tnum,x,y);}
void teleport_pager_callback_look_at_object(char * buf,coordxy x,coordxy y,int glyph){look_at_object(buf,x,y,glyph);}
void teleport_pager_callback_look_at_monster(char * buf,char * monbuf,struct monst * mtmp,coordxy x,coordxy y){look_at_monster(buf,monbuf,mtmp,x,y);}
struct permonst * teleport_pager_callback_lookat(coordxy x,coordxy y,char * buf,char * monbuf){return lookat(x,y,buf,monbuf);}
boolean teleport_pager_callback_checkfile(char * inp,struct permonst * pm,unsigned int chkflags,char * supplemental_name){return checkfile(inp,pm,chkflags,supplemental_name);}
int teleport_pager_callback_add_cmap_descr(int found,int idx,int glyph,int article,coord cc,const char * x_str,const char * prefix,boolean * hit_trap,const char ** firstmatch,char * out_str){return add_cmap_descr(found,idx,glyph,article,cc,x_str,prefix,hit_trap,firstmatch,out_str);}
boolean teleport_pager_callback_add_quoted_engraving(coordxy x,coordxy y,char * buf,boolean force){return add_quoted_engraving(x,y,buf,force);}
void teleport_pager_callback_look_region_nearby(coordxy * lo_x,coordxy * lo_y,coordxy * hi_x,coordxy * hi_y,boolean nearby){look_region_nearby(lo_x,lo_y,hi_x,hi_y,nearby);}
void teleport_pager_callback_look_all(boolean nearby,boolean do_mons){look_all(nearby,do_mons);}
void teleport_pager_callback_look_traps(boolean nearby){look_traps(nearby);}
void teleport_pager_callback_look_engrs(boolean nearby){look_engrs(nearby);}
void teleport_pager_callback_do_supplemental_info(char * name,struct permonst * pm,boolean without_asking){do_supplemental_info(name,pm,without_asking);}
void teleport_pager_callback_whatdoes_help(void){whatdoes_help();}
void teleport_pager_callback_docontact(void){docontact();}
void teleport_pager_callback_dispfile_help(void){dispfile_help();}
void teleport_pager_callback_dispfile_shelp(void){dispfile_shelp();}
void teleport_pager_callback_dispfile_optionfile(void){dispfile_optionfile();}
void teleport_pager_callback_dispfile_optmenu(void){dispfile_optmenu();}
void teleport_pager_callback_dispfile_license(void){dispfile_license();}
void teleport_pager_callback_dispfile_debughelp(void){dispfile_debughelp();}
void teleport_pager_callback_dispfile_usagehelp(void){dispfile_usagehelp();}
void teleport_pager_callback_hmenu_doextversion(void){hmenu_doextversion();}
void teleport_pager_callback_hmenu_dohistory(void){hmenu_dohistory();}
void teleport_pager_callback_hmenu_dowhatis(void){hmenu_dowhatis();}
void teleport_pager_callback_hmenu_dowhatdoes(void){hmenu_dowhatdoes();}
void teleport_pager_callback_hmenu_doextlist(void){hmenu_doextlist();}
void teleport_pager_callback_domenucontrols(void){domenucontrols();}
char * teleport_pager_callback_setopt_cmd(char * outbuf){return setopt_cmd(outbuf);}
#else
extern boolean teleport_pager_callback_is_swallow_sym(int c);
extern int teleport_pager_callback_append_str(char * buf,const char * new_str);
extern void teleport_pager_callback_trap_description(char * outbuf,int tnum,coordxy x,coordxy y);
extern void teleport_pager_callback_look_at_object(char * buf,coordxy x,coordxy y,int glyph);
extern void teleport_pager_callback_look_at_monster(char * buf,char * monbuf,struct monst * mtmp,coordxy x,coordxy y);
extern struct permonst * teleport_pager_callback_lookat(coordxy x,coordxy y,char * buf,char * monbuf);
extern boolean teleport_pager_callback_checkfile(char * inp,struct permonst * pm,unsigned int chkflags,char * supplemental_name);
extern int teleport_pager_callback_add_cmap_descr(int found,int idx,int glyph,int article,coord cc,const char * x_str,const char * prefix,boolean * hit_trap,const char ** firstmatch,char * out_str);
extern boolean teleport_pager_callback_add_quoted_engraving(coordxy x,coordxy y,char * buf,boolean force);
extern void teleport_pager_callback_look_region_nearby(coordxy * lo_x,coordxy * lo_y,coordxy * hi_x,coordxy * hi_y,boolean nearby);
extern void teleport_pager_callback_look_all(boolean nearby,boolean do_mons);
extern void teleport_pager_callback_look_traps(boolean nearby);
extern void teleport_pager_callback_look_engrs(boolean nearby);
extern void teleport_pager_callback_do_supplemental_info(char * name,struct permonst * pm,boolean without_asking);
extern void teleport_pager_callback_whatdoes_help(void);
extern void teleport_pager_callback_docontact(void);
extern void teleport_pager_callback_dispfile_help(void);
extern void teleport_pager_callback_dispfile_shelp(void);
extern void teleport_pager_callback_dispfile_optionfile(void);
extern void teleport_pager_callback_dispfile_optmenu(void);
extern void teleport_pager_callback_dispfile_license(void);
extern void teleport_pager_callback_dispfile_debughelp(void);
extern void teleport_pager_callback_dispfile_usagehelp(void);
extern void teleport_pager_callback_hmenu_doextversion(void);
extern void teleport_pager_callback_hmenu_dohistory(void);
extern void teleport_pager_callback_hmenu_dowhatis(void);
extern void teleport_pager_callback_hmenu_dowhatdoes(void);
extern void teleport_pager_callback_hmenu_doextlist(void);
extern void teleport_pager_callback_domenucontrols(void);
extern char * teleport_pager_callback_setopt_cmd(char * outbuf);
#endif
#include "../nethack-c/wasm/tu-fragments/pager-support.c"
extern const char what_is_a_location[];
extern unsigned long teleport_pager_consumer(char*);
void probe_reset(unsigned seed){
memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(&gy,0,sizeof gy);memset(&svc,0,sizeof svc);memset(&program_state,0,sizeof program_state);memset(&sysopt,0,sizeof sysopt);memset(&gu,0,sizeof gu);memset(&gd,0,sizeof gd);memset(mon,0,sizeof mon);memset(obj,0,sizeof obj);memset(traps,0,sizeof traps);memset(&engr,0,sizeof engr);memset(&region,0,sizeof region);region.glyph=cmap_to_glyph(S_poisoncloud);memset(opts,0,sizeof opts);memset(buf,0,sizeof buf);memset(buf2,0,sizeof buf2);memset(resultcell,0,sizeof resultcell);memset(&cc,0,sizeof cc);
pos=reenter=cmdqueued=draws=0;heldcc=0;automatic_sp=0;tracebuf[0]=0;rngstate=seed;menu_mode=-1;uball=0;gi.invent=0;gf.ftrap=0;strcpy(input,"\033");
u.ux=40;u.uy=10;u.umonnum=u.umonster=PM_HUMAN;u.uz.dlevel=5;strcpy(svp.plname,"Player");gu.urace.adj="human";u.xray_range=2;
svd.dungeon_topology.d_air_level.dnum=19;svd.dungeon_topology.d_astral_level.dnum=18;svd.dungeon_topology.d_juiblex_level.dnum=17;svd.dungeon_topology.d_medusa_level.dnum=16;svd.dungeon_topology.d_qstart_level.dnum=15;svd.dungeon_topology.d_rogue_level.dnum=14;svd.dungeon_topology.d_water_level.dnum=13;svd.dungeon_topology.d_knox_level.dnum=12;
for(int i=0;i<NUMMONS+1;i++){mons[i].pmnames[0]="male fixture";mons[i].pmnames[1]="female fixture";mons[i].pmnames[2]="neutral fixture";mons[i].mflags1=mons[i].mflags2=0;mons[i].mlet=S_HUMAN;}
for(int i=0;i<NUM_OBJECTS+1;i++){objects[i].oc_name_idx=i;objects[i].oc_class=TOOL_CLASS;obj_descr[i].oc_name="object";obj_descr[i].oc_descr="object description";}
for(int i=0;i<4;i++){mon[i].data=&mons[i];mon[i].mx=10+i;mon[i].my=10;mon[i].mhp=20;mon[i].mnum=i;obj[i].otyp=BOULDER;obj[i].ox=10+i;obj[i].oy=10;obj[i].quan=1;obj[i].oclass=ROCK_CLASS;traps[i].tx=20+i;traps[i].ty=10;}
gy.youmonst.data=&mons[PM_HUMAN];
for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;levl[x][y].seenv=0xff;glyphs[x][y]=levl[x][y].glyph=cmap_to_glyph(S_room);}
for(int i=0;i<MAXPCHARS;i++)gs.showsyms[i]=defsyms[i].sym;
for(int i=0;i<MAXMCLASSES;i++)gs.showsyms[i+SYM_OFF_M]=def_monsyms[i].sym;
for(int i=0;i<MAXOCLASSES;i++)gs.showsyms[i+SYM_OFF_O]=def_oc_syms[i].sym;
for(int i=0;i<WARNCOUNT;i++)gw.warnsyms[i]=def_warnsyms[i].sym;
for(int y=0;y<ROWNO;y++){visionrows[y]=vision[y];for(int x=0;x<COLNO;x++)vision[y][x]=COULD_SEE|IN_SIGHT;}gv.viz_array=visionrows;
windowprocs.win_create_nhwindow=backend_create;windowprocs.win_start_menu=backend_start;windowprocs.win_end_menu=backend_end;windowprocs.win_destroy_nhwindow=backend_destroy;windowprocs.win_display_nhwindow=backend_display;windowprocs.win_display_file=backend_file;windowprocs.win_putstr=backend_putstr;windowprocs.win_putmixed=backend_putmixed;
}
void probe_clear(void){pos=0;tracebuf[0]=0;}
void probe_option(int i,long v){opts[i]=v;}
void probe_menu(int n){menu_mode=n;}
void probe_input(const char*s){strcpy(input,s);}
void probe_buffer(int i,const char*s){strcpy(i?buf2:buf,s);}
void*probe_pointer(int kind,int i){switch(kind){case 0:return &mon[i];case 1:return &mons[i];case 2:return &obj[i];case 3:return &traps[i];case 4:return &cc;case 5:return i?buf2:buf;case 6:return &resultcell[i];case 7:return &engr;case 8:return &gy.youmonst;case 9:return &u.uz;}return 0;}
void probe_record(int kind,int field,int i,long v){int map[]={0,1,2,3,4};teleport_pager_record_set(map[kind],field,probe_pointer(kind,i),v);}
void probe_field(int i,long v){teleport_pager_set(i,v);}
void probe_tile(int x,int y,int typ,int flags,int glyph){levl[x][y].typ=typ;levl[x][y].doormask=flags;glyphs[x][y]=levl[x][y].glyph=glyph;}
void probe_link(int kind,int i){switch(kind){case 0:u.ustuck=i<0?0:&mon[i];break;case 1:u.usteed=i<0?0:&mon[i];break;case 2:uball=i<0?0:&obj[i];break;case 3:gi.invent=i<0?0:&obj[i];break;case 4:svl.level.buriedobjlist=i<0?0:&obj[i];break;case 5:svl.level.monsters[12][10]=i<0?0:&mon[i];break;}}
void probe_property(int i,long intrinsic,long extrinsic,long blocked){u.uprops[i].intrinsic=intrinsic;u.uprops[i].extrinsic=extrinsic;u.uprops[i].blocked=blocked;}
int probe_glyph(int sym){return cmap_to_glyph(sym);}
void probe_level(int n,int d){u.uz.dnum=n;u.uz.dlevel=d;}
void probe_queue(int key,int type){cmdqueued=1;opts[48]=type;opts[49]=key;}
void probe_engr(int read,const char*s){engr.eread=read;engr.engr_txt[remembered_text]=(char*)s;}
const char*probe_trace(void){return tracebuf;}
long probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return SIZE(teleport_pager_layout);}
const char*probe_layout_name(int i){return teleport_pager_layout[i].name;}
long probe_layout_value(int i){return teleport_pager_layout[i].value;}
const char*probe_consumer(void){teleport_pager_consumer(buf2);return buf2;}
const char*probe_snapshot(void){char*p=snap;p+=sprintf(p,"buffers:%s|%s;hero:%d/%d:%d:%ld;cc:%d/%d;ice:%d;draw:%d;",buf,buf2,u.ux,u.uy,flags.verbose,EHalluc_resistance,cc.x,cc.y,iflags.ice_rating,draws);p+=sprintf(p,"ustuck:%d;",mid(u.ustuck));for(int i=0;i<4;i++)p+=sprintf(p,"o%d:%d/%d/%ld/%d/%d/%d/%d;",i,obj[i].otyp,obj[i].where,obj[i].quan,obj[i].corpsenm,obj[i].spe,obj[i].dknown,obj[i].no_charge);return snap;}
static struct {void*pointer;long scalar;} observation;
void*probe_observe(unsigned long p,long scalar){observation.pointer=(void*)p;observation.scalar=scalar;return &observation;}
size_t probe_observe_offset(int i){return i?offsetof(__typeof__(observation),scalar):offsetof(__typeof__(observation),pointer);}
long probe_call(int which,const long*a){switch(which){
case 0:return(long)teleport_pager_callback_is_swallow_sym((int)a[0]);
case 1:return(long)teleport_pager_callback_append_str((char *)a[0],(const char *)a[1]);
case 2:return(long)self_lookat((char *)a[0]);
case 3:return(long)monhealthdescr((struct monst *)a[0],(boolean)a[1],(char *)a[2]);
case 4:teleport_pager_callback_trap_description((char *)a[0],(int)a[1],(coordxy)a[2],(coordxy)a[3]);return 0;
case 5:mhidden_description((struct monst *)a[0],(unsigned int)a[1],(char *)a[2]);return 0;
case 6:return(long)object_from_map((int)a[0],(coordxy)a[1],(coordxy)a[2],(struct obj **)a[3]);
case 7:teleport_pager_callback_look_at_object((char *)a[0],(coordxy)a[1],(coordxy)a[2],(int)a[3]);return 0;
case 8:teleport_pager_callback_look_at_monster((char *)a[0],(char *)a[1],(struct monst *)a[2],(coordxy)a[3],(coordxy)a[4]);return 0;
case 9:return(long)waterbody_name((coordxy)a[0],(coordxy)a[1]);
case 10:return(long)ice_descr((coordxy)a[0],(coordxy)a[1],(char *)a[2]);
case 11:return(long)teleport_pager_callback_lookat((coordxy)a[0],(coordxy)a[1],(char *)a[2],(char *)a[3]);
case 12:return(long)ia_checkfile((struct obj *)a[0]);
case 13:return(long)teleport_pager_callback_checkfile((char *)a[0],(struct permonst *)a[1],(unsigned int)a[2],(char *)a[3]);
case 14:return(long)teleport_pager_callback_add_cmap_descr((int)a[0],(int)a[1],(int)a[2],(int)a[3],*(coord*)a[4],(const char *)a[5],(const char *)a[6],(boolean *)a[7],(const char **)a[8],(char *)a[9]);
case 15:return(long)do_screen_description(*(coord*)a[0],(boolean)a[1],(int)a[2],(char *)a[3],(const char **)a[4],(struct permonst **)a[5]);
case 16:return(long)teleport_pager_callback_add_quoted_engraving((coordxy)a[0],(coordxy)a[1],(char *)a[2],(boolean)a[3]);
case 17:return(long)do_look((int)a[0],(coord *)a[1]);
case 18:teleport_pager_callback_look_region_nearby((coordxy *)a[0],(coordxy *)a[1],(coordxy *)a[2],(coordxy *)a[3],(boolean)a[4]);return 0;
case 19:teleport_pager_callback_look_all((boolean)a[0],(boolean)a[1]);return 0;
case 20:teleport_pager_callback_look_traps((boolean)a[0]);return 0;
case 21:teleport_pager_callback_look_engrs((boolean)a[0]);return 0;
case 22:teleport_pager_callback_do_supplemental_info((char *)a[0],(struct permonst *)a[1],(boolean)a[2]);return 0;
case 23:return(long)dowhatis();
case 24:return(long)doquickwhatis();
case 25:return(long)doidtrap();
case 26:teleport_pager_callback_whatdoes_help();return 0;
case 27:return(long)dowhatdoes_core((char)a[0],(char *)a[1]);
case 28:return(long)dowhatdoes();
case 29:teleport_pager_callback_docontact();return 0;
case 30:teleport_pager_callback_dispfile_help();return 0;
case 31:teleport_pager_callback_dispfile_shelp();return 0;
case 32:teleport_pager_callback_dispfile_optionfile();return 0;
case 33:teleport_pager_callback_dispfile_optmenu();return 0;
case 34:teleport_pager_callback_dispfile_license();return 0;
case 35:teleport_pager_callback_dispfile_debughelp();return 0;
case 36:teleport_pager_callback_dispfile_usagehelp();return 0;
case 37:teleport_pager_callback_hmenu_doextversion();return 0;
case 38:teleport_pager_callback_hmenu_dohistory();return 0;
case 39:teleport_pager_callback_hmenu_dowhatis();return 0;
case 40:teleport_pager_callback_hmenu_dowhatdoes();return 0;
case 41:teleport_pager_callback_hmenu_doextlist();return 0;
case 42:teleport_pager_callback_domenucontrols();return 0;
case 43:return(long)dohelp();
case 44:return(long)teleport_pager_callback_setopt_cmd((char *)a[0]);
case 45:return(long)dohistory();
}abort();}
