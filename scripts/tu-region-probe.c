/* Controlled world dependencies only; region algorithms are the unchanged C oracle or JS imports. */
#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten/stack.h>
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/region.c"
#else
extern boolean inside_rect(NhRect*,int,int);
extern NhRegion *create_region(NhRect*,int);
extern void add_rect_to_reg(NhRegion*,NhRect*),add_mon_to_reg(NhRegion*,struct monst*),remove_mon_from_reg(NhRegion*,struct monst*),free_region(NhRegion*),add_region(NhRegion*),remove_region(NhRegion*);
extern boolean mon_in_region(NhRegion*,struct monst*),inside_gas_cloud(genericptr_t,genericptr_t),expire_gas_cloud(genericptr_t,genericptr_t);
extern void teleport_region_test_reset_mids(NhRegion*),teleport_region_test_make_cloud(NhRegion*,int,boolean);
extern boolean teleport_region_test_inside_cloud(void);
#define reset_region_mids teleport_region_test_reset_mids
#define make_gas_cloud teleport_region_test_make_cloud
#define is_hero_inside_gas_cloud teleport_region_test_inside_cloud
#endif
#include "tu-region-layout.h"
__typeof__(gr) gr;__typeof__(gm) gm;__typeof__(svn) svn;__typeof__(svm) svm;__typeof__(gg) gg;struct you u;__typeof__(gy) gy;__typeof__(gi) gi;__typeof__(svc) svc;struct instance_flags iflags;__typeof__(svl) svl;__typeof__(gv) gv;
const __typeof__(cg) cg={.zeroany={.a_ulong=0xa5a5a5a500000000UL}};
struct obj *ublindf;
__typeof__(windowprocs) windowprocs;
const struct c_common_strings c_common_strings={.c_something="something",.c_Something="Something"};
static NhRegion *slots[32];static struct monst monsters[16];static int options[32],rolls[4096],nroll,atroll;static NhRect rects[64];static NHFILE nhfile;static unsigned char io[65536];static size_t io_len,io_pos;static char tracebuf[1048576],snapshot[1048576];static int tracepos,freecount;static void *grown;
static void record(const char *fmt,...){va_list ap;va_start(ap,fmt);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);}
#undef free
extern void free(void*);
void teleport_probe_free(void*p){if(p){for(int i=0;i<32;i++)if(slots[i]==p)slots[i]=0;freecount++;free(p);}}
void panic(const char*fmt,...){abort();}
static void textmsg(const char*tag,const char*fmt,va_list ap){char b[4096];vsnprintf(b,sizeof b,fmt,ap);record("%s:%s;",tag,b);}
void pline(const char*f,...){va_list a;va_start(a,f);textmsg("pline",f,a);va_end(a);}
void pline_The(const char*f,...){va_list a;va_start(a,f);textmsg("The",f,a);va_end(a);}
void You(const char*f,...){va_list a;va_start(a,f);textmsg("You",f,a);va_end(a);}
void Your(const char*f,...){va_list a;va_start(a,f);textmsg("Your",f,a);va_end(a);}
void You_see(const char*f,...){va_list a;va_start(a,f);textmsg("see",f,a);va_end(a);}
void You_feel(const char*f,...){va_list a;va_start(a,f);textmsg("feel",f,a);va_end(a);}
void impossible(const char*f,...){va_list a;va_start(a,f);textmsg("impossible",f,a);va_end(a);}
static void win_putstr(winid w,int a,const char*s){record("put:%d:%d:%s;",w,a,s);}
static void grow(int at){if(options[20]==at){options[20]=0;grown=malloc(48*1024*1024);record("grow:%d;",at);if(options[21]){record("reenter:%d;",any_visible_region());}}}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
void block_point(int x,int y){record("block:%d,%d;",x,y);grow(1);}
void unblock_point(int x,int y){record("unblock:%d,%d;",x,y);grow(2);}
void newsym(coordxy x,coordxy y){record("newsym:%d,%d;",x,y);grow(3);}
int does_block(int x,int y,struct rm*l){record("does:%d,%d:%d;",x,y,l->typ);return options[0];}
void show_glyph(coordxy x,coordxy y,int g){record("show:%d,%d:%d;",x,y,g);}
struct monst *find_mid(unsigned id,unsigned flags){record("find:%u:%u;",id,flags);for(int i=0;i<16;i++)if(monsters[i].m_id==id)return &monsters[i];return 0;}
boolean lookup_id_mapping(unsigned old,unsigned*out){record("mapping:%u;",old);if(old%2){*out=old+100;return TRUE;}return FALSE;}
int m_poisongas_ok(struct monst*m){record("gasok:%u;",m->m_id);return options[1];}
boolean Resists_Elem(struct monst*m,int n){record("resist:%u:%d;",m->m_id,n);return options[2];}
char *m_monnam(struct monst*m){return "creature";}
char *Monnam(struct monst*m){return "Creature";}
char *makeplural(const char*s){static char b[256];snprintf(b,sizeof b,"%ss",s);return b;}
const char *body_part(int n){return n==EYE?"eye":"lung";}
void make_blinded(long n,boolean b){record("blind:%ld:%d;",n,b);u.uprops[BLINDED].intrinsic=n;}
void wake_nearto(coordxy x,coordxy y,int n){record("wake:%d,%d:%d;",x,y,n);}
void losehp(int n,const char*s,schar k){record("lose:%d:%s:%d;",n,s,k);u.uhp-=n;grow(4);}
void monstunseesu(unsigned long b){record("unsees:%lu;",b);}
void monstseesu(unsigned long b){record("sees:%lu;",b);}
void setmangry(struct monst*m,boolean b){record("angry:%u:%d;",m->m_id,b);m->mpeaceful=0;}
void killed(struct monst*m){record("kill:%u;",m->m_id);if(options[3])m->mhp=1;}
void monkilled(struct monst*m,const char*s,int n){record("monkill:%u:%s:%d;",m->m_id,s,n);if(options[3])m->mhp=1;}
boolean valid_cloud_pos(coordxy x,coordxy y){record("valid:%d,%d;",x,y);return isok(x,y)&&(!options[4]||(x>=9&&x<=11&&y>=9&&y<=11));}
boolean safe_teleds(int f){record("teleport:%d;",f);if(options[5]){u.ux=1;u.uy=1;update_player_regions();}return options[5];}
void set_itimeout(long*p,long n){record("timeout:%ld;",n);*p=n;}
static const char *rngfile,*rngfunc;static int rngline;
boolean rng_log_enabled(void){return !options[6];}
void rng_log_set_caller(const char*f,int line,const char*fn){rngfile=strrchr(f,'/');rngfile=rngfile?rngfile+1:f;rngline=line;rngfunc=fn;}
static int draw(const char*kind,int a,int b){record("rng:%s:%d:%d",kind,a,b);if(!options[6])record(":%s:%d:%s",rngfile,rngline,rngfunc);record(";");int v=atroll<nroll?rolls[atroll++]:0;return a>0?(unsigned)v%(unsigned)a:0;}
int (rn2)(int n){return draw("rn2",n,0);}
int (rnd)(int n){return draw("rnd",n,0)+1;}
int (d)(int n,int x){return draw("d",n,x)+n;}
void selection_getbounds(struct selectionvar*s,NhRect*r){*r=(NhRect){8,8,12,12};record("bounds;");}
coordxy selection_getpoint(coordxy x,coordxy y,struct selectionvar*s){return (x+y)%2==0;}
static void output(void*p,size_t n,const char*s){record("sfo:%s:%zu;",s,n);if(nhfile.mode&WRITING){memcpy(io+io_len,p,n);io_len+=n;}grow(5);}
static void input(void*p,size_t n,const char*s){record("sfi:%s:%zu;",s,n);if(io_pos+n>io_len)abort();memcpy(p,io+io_pos,n);io_pos+=n;grow(6);}
#define SF(T,TYPE) void sfo_##T(NHFILE*f,TYPE*p,const char*s){output(p,sizeof(TYPE),s);}void sfi_##T(NHFILE*f,TYPE*p,const char*s){input(p,sizeof(TYPE),s);}
SF(long,long) SF(int,int) SF(short,short) SF(unsigned,unsigned) SF(boolean,boolean) SF(nhrect,NhRect) SF(any,anything)
#undef SF
void sfo_char(NHFILE*f,char*p,const char*s,int n){output(p,n,s);}
void sfi_char(NHFILE*f,char*p,const char*s,int n){input(p,n,s);}
void probe_reset(void){clear_regions();for(int i=0;i<32;i++)slots[i]=0;if(grown){free(grown);grown=0;}memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&svc,0,sizeof svc);memset(&svl,0,sizeof svl);memset(&gg,0,sizeof gg);memset(&gv,0,sizeof gv);memset(&iflags,0,sizeof iflags);memset(options,0,sizeof options);memset(monsters,0,sizeof monsters);monst_globals_init();u.ux=u.uy=10;u.uhp=100;gy.youmonst.data=&mons[PM_HUMAN];for(int i=0;i<16;i++){monsters[i].m_id=i+1;monsters[i].data=&mons[PM_HUMAN];monsters[i].mhp=100;monsters[i].mx=8+i%5;monsters[i].my=8+i/5;monsters[i].mcansee=1;svl.level.monsters[monsters[i].mx][monsters[i].my]=&monsters[i];}windowprocs.win_putstr=win_putstr;svm.moves=100;io_len=io_pos=0;tracepos=tracebuf[0]=0;freecount=0;nroll=atroll=0;static uchar rows[ROWNO][COLNO];static uchar*rowp[ROWNO];for(int y=0;y<ROWNO;y++){memset(rows[y],IN_SIGHT,sizeof rows[y]);rowp[y]=rows[y];}gv.viz_array=rowp;}
void probe_option(int i,long v){options[i]=(int)v;}
void probe_roll(int n){rolls[nroll++]=n;}
void probe_rect(int i,int lx,int ly,int hx,int hy){rects[i]=(NhRect){lx,ly,hx,hy};}
void *probe_pointer(int kind,int i){switch(kind){case 0:return slots[i];case 1:return &monsters[i];case 2:return &rects[i];case 3:return &nhfile;case 4:return io;case 5:return &u;case 6:return &gy.youmonst;}return 0;}
void probe_set_monster(int i,int field,long v){struct monst*m=&monsters[i];switch(field){case 0:m->m_id=v;break;case 1:m->data=&mons[v];break;case 2:m->mhp=v;break;case 3:m->mx=v;break;case 4:m->my=v;break;case 5:m->mcansee=v;break;case 6:m->mblinded=v;break;}}
void probe_hero(int field,long v){switch(field){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:svm.moves=v;break;case 3:gy.youmonst.data=&mons[v];break;case 4:gi.in_mklev=v;break;case 5:svc.context.mon_moving=v;break;case 6:u.uinwater=v;break;case 7:u.uswallow=v;break;case 8:u.xray_range=v;break;}}
void probe_property(int n,int f,long v){if(f==0)u.uprops[n].intrinsic=v;else if(f==1)u.uprops[n].extrinsic=v;else u.uprops[n].blocked=v;}
void probe_field(int slot,int field,long v){NhRegion*r=slots[slot];switch(field){case 0:r->ttl=v;break;case 1:r->arg.a_int=v;break;case 2:r->visible=v;break;case 3:r->player_flags=v;break;case 4:r->inside_f=v;break;case 5:r->expire_f=v;break;case 6:r->can_enter_f=v;break;case 7:r->enter_f=v;break;case 8:r->can_leave_f=v;break;case 9:r->leave_f=v;break;case 10:r->attach_2_u=v;break;case 11:r->attach_2_m=v;break;case 12:r->glyph=v;break;}}
void probe_messages(int slot,const char*a,const char*b){slots[slot]->enter_msg=a?dupstr(a):0;slots[slot]->leave_msg=b?dupstr(b):0;}
long probe_action(int op,int a,int b,int c,int d){NhRegion*r=slots[a];switch(op){case 0:slots[a]=create_region(b?rects:0,b);break;case 1:return inside_rect(&rects[a],b,c);case 2:return inside_region(r,b,c);case 3:add_rect_to_reg(r,&rects[b]);break;case 4:add_mon_to_reg(r,&monsters[b]);break;case 5:remove_mon_from_reg(r,&monsters[b]);break;case 6:return mon_in_region(r,&monsters[b]);case 7:free_region(r);slots[a]=0;break;case 8:add_region(r);break;case 9:remove_region(r);slots[a]=0;break;case 10:clear_regions();memset(slots,0,sizeof slots);break;case 11:run_regions();break;case 12:return in_out_region(b,c);case 13:return m_in_out_region(&monsters[a],b,c);case 14:update_player_regions();break;case 15:update_monster_region(&monsters[a]);break;case 16:return reg_damg(r);case 17:return any_visible_region();case 18:visible_region_summary(17);break;case 19:{NhRegion*q=visible_region_at(b,c);for(int i=0;i<32;i++)if(q==slots[i])return i;return -1;}case 20:show_region(r,b,c);break;case 21:nhfile.mode=b;io_len=0;save_regions(&nhfile);if(b&FREEING)memset(slots,0,sizeof slots);break;case 22:nhfile.ftype=b;io_pos=0;rest_regions(&nhfile);memset(slots,0,sizeof slots);for(int i=0;i<svn.n_regions;i++)slots[i]=gr.regions[i];break;case 23:{char buf[128];long n=0,z=0;region_stats("regions %ld rects %ld",buf,&n,b?&n:&z);record("stats:%s:%ld:%ld;",buf,n,z);break;}case 24:reset_region_mids(r);break;case 25:return expire_gas_cloud(r,b?&monsters[b-1]:0);case 26:return inside_gas_cloud(r,b?&monsters[b-1]:0);case 27:return is_hero_inside_gas_cloud();case 28:make_gas_cloud(r,b,c);break;case 29:slots[a]=create_gas_cloud(b,c,d,options[7]);break;case 30:{struct selectionvar sel;memset(&sel,0,sizeof sel);slots[a]=create_gas_cloud_selection(&sel,b);break;}case 31:return region_danger();case 32:region_safety();break;}return 0;}
const char *probe_trace(void){return tracebuf;}
size_t probe_io_size(void){return io_len;}
int probe_free_count(void){return freecount;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){char*p=snapshot;p+=sprintf(p,"global:%d:%d:%ld:%d:%d:%d:%d:%d:%d:%d:%ld:%ld;",svn.n_regions,gm.max_regions,svm.moves,gg.gas_cloud_diss_within,gg.gas_cloud_diss_seen,u.ux,u.uy,u.uinwater,u.uswallow,u.uhp,u.uprops[BLINDED].intrinsic,u.uprops[MAGICAL_BREATHING].intrinsic);for(int i=0;i<32;i++){NhRegion*r=slots[i];if(!r)continue;boolean active=FALSE;for(int j=0;j<svn.n_regions;j++)if(gr.regions[j]==r)active=TRUE;p+=sprintf(p,"r%d:%d:%d,%d,%d,%d:%d:%d:%u:%s:%s:%ld:%d,%d,%d,%d,%d,%d:%u:%d:%d:%d:%d:%016lx;",i,active,r->bounding_box.lx,r->bounding_box.ly,r->bounding_box.hx,r->bounding_box.hy,r->nrects,r->attach_2_u,r->attach_2_m,r->enter_msg?r->enter_msg:"(NULL)",r->leave_msg?r->leave_msg:"(NULL)",r->ttl,r->expire_f,r->can_enter_f,r->enter_f,r->can_leave_f,r->leave_f,r->inside_f,r->player_flags,r->n_monst,r->max_monst,r->visible,r->glyph,r->arg.a_ulong);for(int j=0;j<r->nrects;j++)p+=sprintf(p,"rect:%d,%d,%d,%d;",r->rects[j].lx,r->rects[j].ly,r->rects[j].hx,r->rects[j].hy);for(int j=0;j<r->n_monst;j++)p+=sprintf(p,"mid:%u;",r->monsters[j]);}for(int i=0;i<16;i++)p+=sprintf(p,"m%d:%u:%d:%d,%d:%d:%d:%d;",i,monsters[i].m_id,monsndx(monsters[i].data),monsters[i].mx,monsters[i].my,monsters[i].mhp,monsters[i].mcansee,monsters[i].mblinded);for(size_t i=0;i<io_len;i++)p+=sprintf(p,"%02x",io[i]);return snapshot;}
__typeof__(svd) svd;
boolean In_mines(d_level*l){return l->dnum==mines_dnum;}
boolean In_hell(d_level*l){return svd.dungeons[l->dnum].flags.hellish;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
