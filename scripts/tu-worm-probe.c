#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef free
extern void free(void*);
struct you u;
__typeof__(svl) svl;
__typeof__(svm) svm;
__typeof__(svc) svc;
__typeof__(gv) gv;
static struct monst monsters[8];
static struct mextra extras[8];
static struct obj dummy_object;
static int opts[40],rolls[8192],nroll,rollidx,free_count,step_calls,long_index;
static unsigned seed;
static char tracebuf[2097152],statebuf[262144],caller[128];
static unsigned char io[262144],nested_io[262144];
static int nested_depth,nested_len,nested_pos;
static long *outer_time_cell;
static int io_len,io_pos;
static NHFILE nhfile;
static seenV vision[ROWNO][COLNO],*vision_rows[ROWNO];
static void *growth,*loose;
static int mid(struct monst *m){uintptr_t p=(uintptr_t)m,b=(uintptr_t)monsters;if(!m)return -1;return p>=b&&p<b+sizeof monsters&&(p-b)%sizeof *m==0?(int)((p-b)/sizeof *m):-99;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*3];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(impossible)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *f,int line,const char *fn){const char *b=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(rollidx<nroll)v=rolls[rollidx]%(unsigned)n;else{seed=seed*1664525U+1013904223U;v=(seed>>8)%(unsigned)n;}rollidx++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
int (d)(int n,int x){int i,v=0;for(i=0;i<n;i++)v+=draw(x)+1;append("dice:%d:%d:%d@%s;",n,x,v,caller);return v;}
int rn2_on_display_rng(int n){int v=draw(n);append("display-rng:%d:%d;",n,v);return v;}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("nested-slot:%d;",get_wormno());}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}}
void teleport_probe_free(void*);
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);callback(1);}
int mcalcmove(struct monst *m,boolean b){append("speed:%d:%d;",mid(m),b);callback(2);return opts[1];}
int mattacku(struct monst *m){append("attack:%d;",mid(m));callback(3);if(opts[2])m->mhp=0;return opts[2];}
struct monst *clone_mon(struct monst *m,coordxy x,coordxy y){struct monst *n=&monsters[1];append("clone:%d:%d:%d;",mid(m),x,y);if(opts[3])return NULL;*n=*m;n->m_id=101;n->mx=x;n->my=y;n->mcloned=1;n->wormno=0;svl.level.monsters[x][y]=n;callback(4);return n;}
boolean rnd_nextto_goodpos(coordxy *x,coordxy *y,struct monst *m){boolean yes=step_calls++<opts[4];append("step:%d:%d:%d:%d;",*x,*y,mid(m),yes);if(yes){*x+=opts[5];*y+=opts[6];}callback(5);return yes;}
int canseemon(struct monst *m){append("visible:%d;",mid(m));return opts[7];}
int sensemon(struct monst *m){append("sense:%d;",mid(m));return opts[8];}
char *mon_nam(struct monst *m){return "worm";}
char *Monnam(struct monst *m){return "Worm";}
void show_glyph(coordxy x,coordxy y,int g){append("glyph:%d:%d:%d;",x,y,g);callback(6);}
static void write_bytes(void *p,size_t n,const char *s){int *pos=nested_depth?&nested_pos:&io_pos,*len=nested_depth?&nested_len:&io_len;unsigned char *buffer=nested_depth?nested_io:io;if(*pos+n>sizeof io)abort();memcpy(buffer+*pos,p,n);*pos+=n;if(*pos>*len)*len=*pos;append("out:%s:%zu:%d;",s,n,nested_depth);callback(8);}
static void read_bytes(void *p,size_t n,const char *s){if(io_pos+n>io_len)abort();memcpy(p,io+io_pos,n);io_pos+=n;append("in:%s:%zu;",s,n);callback(9);}
void sfo_int(NHFILE *f,int *p,const char *s){write_bytes(p,sizeof *p,s);}
void sfi_int(NHFILE *f,int *p,const char *s){read_bytes(p,sizeof *p,s);}
void sfo_int16(NHFILE *f,int16 *p,const char *s){write_bytes(p,sizeof *p,s);}
void sfi_int16(NHFILE *f,int16 *p,const char *s){read_bytes(p,sizeof *p,s);}
static void long_callback(long *p){int index=long_index++;if(nested_depth&&index==1){append("same-time-address:%d;",p==outer_time_cell);*p+=7;append("nested-time:%ld;",*p);}if(opts[20]==index+1){*p=svm.moves+1000;append("mutated-time:%d:%ld;",index,*p);opts[20]=0;worm_move(&monsters[0]);if(opts[22]){NHFILE inner={0};int saved_index=long_index;opts[22]=0;inner.mode=COUNTING;outer_time_cell=p;nested_pos=nested_len=0;nested_depth++;long_index=0;save_worm(&inner);long_index=saved_index;nested_depth--;outer_time_cell=NULL;}append("after-alias:%ld;",*p);}callback(10);}
void sfo_long(NHFILE *f,long *p,const char *s){write_bytes(p,sizeof *p,s);long_callback(p);}
void sfi_long(NHFILE *f,long *p,const char *s){read_bytes(p,sizeof *p,s);long_callback(p);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/worm.c"
#undef free
#endif
#include "tu-worm-layout.h"
#ifndef TELEPORT_REFERENCE_TU
#define wseg teleport_worm_segment
extern void teleport_worm_test_toss(struct wseg*,boolean),teleport_worm_test_shrink(int);
extern struct wseg *teleport_worm_test_create(int);
extern struct wseg *teleport_worm_test_segment(int,int);
extern long teleport_worm_test_time(int);
extern void teleport_worm_test_set_time(int,long);
#define toss_wsegs teleport_worm_test_toss
#define shrink_worm teleport_worm_test_shrink
#define create_worm_tail teleport_worm_test_create
#endif
static struct wseg *head(int n){
#ifdef TELEPORT_REFERENCE_TU
return wheads[n];
#else
return teleport_worm_test_segment(0,n);
#endif
}
static struct wseg *tail(int n){
#ifdef TELEPORT_REFERENCE_TU
return wtails[n];
#else
return teleport_worm_test_segment(1,n);
#endif
}
static long time_value(int n){
#ifdef TELEPORT_REFERENCE_TU
return wgrowtime[n];
#else
return teleport_worm_test_time(n);
#endif
}
void probe_set_time(int n,long v){
#ifdef TELEPORT_REFERENCE_TU
wgrowtime[n]=v;
#else
teleport_worm_test_set_time(n,v);
#endif
}
void teleport_probe_free(void *p){struct wseg *seg=p;if(!p)return;append("free:%d:%d:%d;",seg->wx,seg->wy,seg->nseg!=NULL);free_count++;callback(7);free(p);}
void probe_reset(unsigned s){int i,x,y;NHFILE release={0};opts[30]=opts[31]=opts[20]=opts[22]=0;release.mode=FREEING;save_worm(&release);if(loose)toss_wsegs(loose,FALSE);loose=NULL;if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&svm,0,sizeof svm);memset(&svc,0,sizeof svc);memset(&gv,0,sizeof gv);memset(monsters,0,sizeof monsters);memset(extras,0,sizeof extras);memset(opts,0,sizeof opts);memset(&nhfile,0,sizeof nhfile);monst_globals_init();objects_globals_init();for(i=0;i<8;i++){monsters[i].data=&mons[PM_LONG_WORM];monsters[i].m_id=100+i;monsters[i].mx=20+i;monsters[i].my=10;monsters[i].mhp=monsters[i].mhpmax=30;monsters[i].m_lev=8;monsters[i].mcanmove=1;}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)vision[y][x]=COULD_SEE|IN_SIGHT;for(y=0;y<ROWNO;y++)vision_rows[y]=vision[y];gv.viz_array=vision_rows;u.ux=10;u.uy=10;u.uz.dnum=1;u.uz.dlevel=2;svm.moves=100;opts[0]=opts[7]=1;opts[1]=3;opts[4]=100;opts[5]=1;nhfile.mode=WRITING;seed=s;rollidx=nroll=free_count=step_calls=long_index=io_len=io_pos=0;nested_depth=nested_pos=nested_len=0;outer_time_cell=NULL;tracebuf[0]=statebuf[0]=caller[0]=0;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;}
int *probe_rng_pointer(void){return rolls;}
void probe_rng_length(int n){nroll=n;rollidx=0;}
int probe_rng_count(void){return rollidx;}
unsigned probe_rng_state(void){return seed;}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:svm.moves=v;break;case 3:svc.context.mon_moving=v;break;case 4:memset(vision,v?IN_SIGHT:0,sizeof vision);break;}}
void probe_monster_field(int i,int k,long v){struct monst *m=&monsters[i];switch(k){case 0:m->wormno=v;break;case 1:m->mx=v;break;case 2:m->my=v;break;case 3:m->mhp=v;break;case 4:m->mhpmax=v;break;case 5:m->m_lev=v;break;case 6:m->female=v;break;case 7:m->mtame=v;break;case 8:m->mcloned=v;break;case 9:svl.level.monsters[m->mx][m->my]=v?m:NULL;break;case 10:m->mextra=v?&extras[i]:NULL;extras[i].mcorpsenm=v?PM_LONG_WORM:NON_PM;break;case 11:m->data=&mons[v];break;case 12:svl.level.monsters[u.ux][u.uy]=(struct monst*)(uintptr_t)v;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_node(int slot,int index,int x,int y,int monster){struct wseg *s=tail(slot);while(s&&index-->0)s=s->nseg;if(!s)abort();s->wx=x;s->wy=y;if(monster>=0)svl.level.monsters[x][y]=&monsters[monster];}
void probe_nhfile(int k,int v){switch(k){case 0:nhfile.mode=v;break;case 1:nhfile.structlevel=v;break;case 2:nhfile.fnidx=v;break;}}
void probe_io_size(int n){io_len=n;io_pos=0;}
int probe_io_length(void){return io_len;}
int probe_io_position(int n){if(n>=0)io_pos=n;return io_pos;}
int probe_free_count(void){return free_count;}
void *probe_pointer(int k,int i){switch(k){case 0:return &monsters[i];case 1:return &nhfile;case 2:return io;case 3:return &svl.level.monsters[0][0];case 4:return &u;case 5:return &mons[i];case 6:return loose;}return NULL;}
void *probe_node_pointer(int slot,int index){struct wseg *s=tail(slot);while(s&&index-->0)s=s->nseg;return s;}
long probe_action(int op,int i,int a,int b,int c,int d){struct monst *m=i<0?NULL:&monsters[i];switch(op){case 0:return get_wormno();case 1:initworm(m,a);return 0;case 2:toss_wsegs(loose,a);loose=NULL;return 0;case 3:shrink_worm(a);return 0;case 4:worm_move(m);return 0;case 5:worm_nomove(m);return 0;case 6:wormgone(m);return 0;case 7:return wormhitu(m);case 8:cutworm(m,a,b,c);return 0;case 9:see_wsegs(m);return 0;case 10:detect_wsegs(m,a);return 0;case 11:io_pos=io_len=long_index=0;save_worm(&nhfile);return 0;case 12:io_pos=long_index=0;rest_worm(&nhfile);return 0;case 13:place_wsegs(m,a<0?NULL:&monsters[a]);return 0;case 14:sanity_check_worm(m);return 0;case 15:wormno_sanity_check();return 0;case 16:remove_worm(m);return 0;case 17:place_worm_tail_randomly(m,a,b);return 0;case 18:return size_wseg(m);case 19:return count_wsegs(m);case 20:loose=create_worm_tail(a);return loose!=NULL;case 21:return worm_known(m);case 22:return worm_cross(a,b,c,d);case 23:return wseg_at(m,a,b);case 24:flip_worm_segs_vertical(m,a,b);return 0;case 25:flip_worm_segs_horizontal(m,a,b);return 0;case 26:redraw_worm(m);return 0;}return -999;}
const char *probe_snapshot(void){int i,j;char *p=statebuf;struct wseg *s;p+=sprintf(p,"world:%ld:%d:%d:%d:%d;",svm.moves,u.ux,u.uy,svc.context.mon_moving,free_count);for(i=0;i<8;i++){struct monst *m=&monsters[i];p+=sprintf(p,"m%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;",i,m->wormno,m->mx,m->my,m->mhp,m->mhpmax,m->m_lev,m->female,m->mtame,m->mcloned,m->mextra?MCORPSENM(m):NON_PM,monsndx(m->data));}for(i=0;i<MAX_NUM_WORMS;i++){p+=sprintf(p,"w%d:%ld:%d:%d;",i,time_value(i),head(i)!=NULL,tail(i)!=NULL);for(j=0,s=tail(i);s;s=s->nseg){if(j++>=1024)abort();p+=sprintf(p,"s:%d:%d:%d:%d;",s->wx,s->wy,s==head(i),s->nseg!=NULL);}}p+=sprintf(p,"loose:%d;",loose!=NULL);for(s=loose,j=0;s;s=s->nseg){if(j++>=1024)abort();p+=sprintf(p,"l:%d:%d:%d;",s->wx,s->wy,s->nseg!=NULL);}for(i=0;i<COLNO*ROWNO;i++){struct monst *m=svl.level.monsters[i/ROWNO][i%ROWNO];int id=mid(m);if(id==-99)p+=sprintf(p,"raw%016lx,",(unsigned long)(uintptr_t)m);else p+=sprintf(p,"%d,",id);}p+=sprintf(p,";nested-io:%d:",nested_len);for(i=0;i<nested_len;i++)p+=sprintf(p,"%02x",nested_io[i]);return statebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
