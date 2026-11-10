#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef free
extern void free(void*);
struct you u;
__typeof__(gl) gl;
__typeof__(gv) gv;
__typeof__(cg) cg={0};
__typeof__(gy) gy;
__typeof__(svl) svl;
__typeof__(gm) gm;
__typeof__(gb) gb;
__typeof__(gi) gi;
__typeof__(windowprocs) windowprocs;
struct obj *uskin;
/* Exact external vision.c circle tables; no visibility algorithm is duplicated. */
const coordxy circle_data[] = {
    /*  0*/ 0,
    /*  1*/ 1,  1,
    /*  3*/ 2,  2,  1,
    /*  6*/ 3,  3,  2,  1,
    /* 10*/ 4,  4,  4,  3,  2,
    /* 15*/ 5,  5,  5,  4,  3,  2,
    /* 21*/ 6,  6,  6,  5,  5,  4,  2,
    /* 28*/ 7,  7,  7,  6,  6,  5,  4,  2,
    /* 36*/ 8,  8,  8,  7,  7,  6,  6,  4,  2,
    /* 45*/ 9,  9,  9,  9,  8,  8,  7,  6,  5,  3,
    /* 55*/ 10, 10, 10, 10, 9,  9,  8,  7,  6,  5,  3,
    /* 66*/ 11, 11, 11, 11, 10, 10, 9,  9,  8,  7,  5,  3,
    /* 78*/ 12, 12, 12, 12, 11, 11, 10, 10, 9,  8,  7,  5,  3,
    /* 91*/ 13, 13, 13, 13, 12, 12, 12, 11, 10, 10, 9,  7,  6, 3,
    /*105*/ 14, 14, 14, 14, 13, 13, 13, 12, 12, 11, 10, 9,  8, 6, 3,
    /*120*/ 15, 15, 15, 15, 14, 14, 14, 13, 13, 12, 11, 10, 9, 8, 6, 3,
    /*136*/ 16 /* MAX_RADIUS+1; used to terminate range loops -dlc */
};

/*
 * These are the starting indexes into the circle_data[] array for a
 * circle of a given radius.  Radius 0 used to be unused, but is now
 * used for a single point:  temporary light source of a camera flash
 * as it traverses its path.
 */
const coordxy circle_start[] = {
    /* 0*/ 0,
    /* 1*/ 1,
    /* 2*/ 3,
    /* 3*/ 6,
    /* 4*/ 10,
    /* 5*/ 15,
    /* 6*/ 21,
    /* 7*/ 28,
    /* 8*/ 36,
    /* 9*/ 45,
    /*10*/ 55,
    /*11*/ 66,
    /*12*/ 78,
    /*13*/ 91,
    /*14*/ 105,
    /*15*/ 120,
};

static struct obj objects_pool[16];
static struct monst monsters[16];
static seenV vision[ROWNO][COLNO],*vision_rows[ROWNO];
static anything identifier;
static NHFILE fixture_file;
static int opts[40],free_count,zero_fail,panic_guard;
static unsigned char io[65536];
static unsigned io_size,io_position;
static char tracebuf[2097152],statebuf[131072],output[BUFSZ];
static long stats_count,stats_size;
static void *growth;
static jmp_buf panic_jump;
static int oid(struct obj *o){return o?(int)(o-objects_pool):-1;}
static int mid(struct monst *m){return m==&gy.youmonst?-2:m?(int)(m-monsters):-1;}
static light_source *node(int i){light_source *l=gl.light_base;while(l&&i-->0)l=l->next;return l;}
static int nodeid(light_source *l){light_source *p;int i=0;for(p=gl.light_base;p;p=p->next,i++)if(p==l)return i;return -1;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append("panic:%s;",b);if(panic_guard)longjmp(panic_jump,1);abort();}
void impossible(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append("impossible:%s;",b);}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("nested-any:%d;",any_light_source());}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}}
void teleport_probe_free(void *p){unsigned i;int zero=1;for(i=0;i<sizeof(light_source);i++)if(((unsigned char*)p)[i])zero=0;append("free-zero:%d;",zero);free_count++;if(!zero)zero_fail++;callback(6);free(p);}
boolean get_obj_location(struct obj *o,coordxy *x,coordxy *y,int f){append("objloc:%d:%d;",oid(o),f);*x=o->ox;*y=o->oy;callback(1);return opts[0];}
boolean get_mon_location(struct monst *m,coordxy *x,coordxy *y,int f){append("monloc:%d:%d;",mid(m),f);*x=m==&gy.youmonst?u.ux:m->mx;*y=m==&gy.youmonst?u.uy:m->my;callback(1);return opts[1];}
boolean clear_path(int x1,int y1,int x2,int y2){append("path:%d:%d:%d:%d;",x1,y1,x2,y2);callback(2);return opts[2];}
void place_object(struct obj *o,coordxy x,coordxy y){append("place:%d:%d:%d;",oid(o),x,y);o->ox=x;o->oy=y;o->where=OBJ_FLOOR;}
void remove_object(struct obj *o){append("remove:%d;",oid(o));o->where=OBJ_FREE;}
void vision_recalc(int n){append("recalc:%d;",n);do_light_sources(vision_rows);gv.vision_full_recalc=0;callback(3);}
void flush_screen(int n){append("flush:%d;",n);}
static void delay_window(void){append("delay;");}
int canseemon(struct monst *m){append("cansee:%d;",mid(m));return opts[3];}
int sensemon(struct monst *m){append("sense:%d;",mid(m));return opts[4];}
void map_invisible(coordxy x,coordxy y){append("invisible:%d:%d;",x,y);}
boolean obj_is_local(struct obj *o){append("local:%d;",oid(o));return o->where==OBJ_FLOOR||o->where==OBJ_BURIED;}
boolean lookup_id_mapping(unsigned old,unsigned *newid){append("mapping:%u;",old);*newid=old+opts[5];callback(4);return opts[6];}
struct obj *find_oid(unsigned id){int i;append("findoid:%u;",id);callback(4);if(opts[7])return NULL;for(i=0;i<16;i++)if(objects_pool[i].o_id==id)return &objects_pool[i];return NULL;}
boolean artifact_light(struct obj *o){append("artifact:%d;",oid(o));return o->oartifact!=0;}
void end_burn(struct obj *o,boolean timer){anything id;append("endburn:%d:%d;",oid(o),timer);id=cg.zeroany;id.a_obj=o;del_light_source(LS_OBJECT,&id);o->lamplit=0;}
char *simpleonames(struct obj *o){return "fixture object";}
char *otense(struct obj *o,const char *s){return "is";}
char *xname(struct obj *o){return "fixture object";}
static winid create_window(int type){append("create:%d;",type);return opts[8]?WIN_ERR:19;}
static void put_window(winid win,int attr,const char *s){append("put:%d:%d:%s;",win,attr,s);}
static void display_window(winid win,boolean b){append("display:%d:%d;",win,b);}
static void destroy_window(winid win){append("destroy:%d;",win);}
static void write_bytes(const void *p,unsigned n,const char *s){if(io_size+n>sizeof io)abort();append("write:%s:%u;",s,n);memcpy(io+io_size,p,n);io_size+=n;callback(5);}
static void read_bytes(void *p,unsigned n,const char *s){if(io_position+n>io_size)abort();append("read:%s:%u;",s,n);memcpy(p,io+io_position,n);io_position+=n;callback(5);}
void sfo_int(NHFILE *f,int *p,const char *s){write_bytes(p,sizeof *p,s);if(opts[9]){*p+=opts[9];append("mutated-count:%d;",*p);}}
void sfi_int(NHFILE *f,int *p,const char *s){read_bytes(p,sizeof *p,s);}
void sfo_ls_t(NHFILE *f,struct ls_t *p,const char *s){write_bytes(p,sizeof *p,s);}
void sfi_ls_t(NHFILE *f,struct ls_t *p,const char *s){read_bytes(p,sizeof *p,s);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/light.c"
#undef free
#else
extern light_source *teleport_light_test_new(coordxy,coordxy,int,int,anything*);
extern void teleport_light_test_delete(light_source*),teleport_light_test_discard(void),teleport_light_test_write(NHFILE*,light_source*);
extern int teleport_light_test_maybe(NHFILE*,int,boolean);
extern unsigned teleport_light_test_where(struct monst*,unsigned);
#define new_light_core teleport_light_test_new
#define delete_ls teleport_light_test_delete
#define discard_flashes teleport_light_test_discard
#define write_ls teleport_light_test_write
#define maybe_write_ls teleport_light_test_maybe
#define whereis_mon teleport_light_test_where
#endif
#include "tu-light-layout.h"
void probe_reset(void){light_source *l,*next;int i,x,y;for(l=gl.light_base;l;l=next){next=l->next;free(l);}if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&gl,0,sizeof gl);memset(&gv,0,sizeof gv);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&gm,0,sizeof gm);memset(&gb,0,sizeof gb);memset(&gi,0,sizeof gi);memset(objects_pool,0,sizeof objects_pool);memset(monsters,0,sizeof monsters);memset(&identifier,0,sizeof identifier);memset(&fixture_file,0,sizeof fixture_file);memset(opts,0,sizeof opts);opts[0]=opts[1]=opts[2]=opts[3]=opts[6]=1;monst_globals_init();objects_globals_init();u.ux=u.uy=10;gy.youmonst.m_id=1;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mhp=20;for(i=0;i<16;i++){objects_pool[i].o_id=100+i;objects_pool[i].otyp=TALLOW_CANDLE;objects_pool[i].quan=1;objects_pool[i].where=OBJ_FREE;objects_pool[i].ox=objects_pool[i].oy=10;monsters[i].m_id=200+i;monsters[i].mhp=20;monsters[i].data=&mons[PM_HUMAN];monsters[i].mx=12+i;monsters[i].my=10;}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)vision[y][x]=COULD_SEE;for(y=0;y<ROWNO;y++)vision_rows[y]=vision[y];gv.viz_array=vision_rows;gb.bhitpos.x=11;gb.bhitpos.y=10;uskin=NULL;fixture_file.mode=WRITING;free_count=zero_fail=panic_guard=0;stats_count=stats_size=0;io_size=io_position=0;output[0]=tracebuf[0]=0;windowprocs.win_create_nhwindow=create_window;windowprocs.win_putstr=put_window;windowprocs.win_display_nhwindow=display_window;windowprocs.win_destroy_nhwindow=destroy_window;windowprocs.win_delay_output=delay_window;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;}
void probe_object(int i,int key,long v){struct obj *o=&objects_pool[i];switch(key){case 0:o->otyp=v;break;case 1:o->o_id=v;break;case 2:o->quan=v;break;case 3:o->spe=v;break;case 4:o->lamplit=v;break;case 5:o->blessed=v;break;case 6:o->cursed=v;break;case 7:o->oartifact=v;break;case 8:o->where=v;break;case 9:o->ox=v;break;case 10:o->oy=v;break;case 11:uskin=v?o:NULL;break;}}
void probe_monster_field(int i,int key,long v){struct monst *m=i<0?&gy.youmonst:&monsters[i];switch(key){case 0:m->m_id=v;break;case 1:m->mhp=v;break;case 2:m->mx=v;break;case 3:m->my=v;break;case 4:m->isgd=v;break;case 5:m->mtemplit=v;break;case 6:m->nmon=v<0?NULL:&monsters[v];break;case 7:if(v==0)fmon=m;else if(v==1)gm.migrating_mons=m;else gm.mydogs=m;break;}}
void probe_hero(int k,int v){if(k==0)u.ux=v;else if(k==1)u.uy=v;else if(k==2)gb.bhitpos.x=v;else if(k==3)gb.bhitpos.y=v;else if(k==4)gv.vision_full_recalc=v;else if(k==5)levl[11][10].lit=v;}
void probe_ls(int i,int key,long v){light_source *l=node(i);if(!l)abort();switch(key){case 0:l->x=v;break;case 1:l->y=v;break;case 2:l->range=v;break;case 3:l->flags=v;break;case 4:l->type=v;break;}}
long probe_action(int op,int a,int b,int c,int d,int e){light_source *l;struct obj *o=a<0?NULL:&objects_pool[a];struct monst *m=a==-2?&gy.youmonst:a<0?NULL:&monsters[a];if(setjmp(panic_jump)){panic_guard=0;return -2147483647L;}panic_guard=1;switch(op){case 0:new_light_source(a,b,c,d,&identifier);break;case 1:l=new_light_core(a,b,c,d,&identifier);panic_guard=0;return l?nodeid(l):-1;case 2:del_light_source(a,&identifier);break;case 3:delete_ls(node(a));break;case 4:do_light_sources(vision_rows);break;case 5:show_transient_light(o,b,c);break;case 6:transient_light_cleanup();break;case 7:discard_flashes();break;case 8:m=find_mid((unsigned)a,(unsigned)b);panic_guard=0;return mid(m);case 9:{unsigned value=whereis_mon(m,(unsigned)b);panic_guard=0;return value;}case 10:save_light_sources(&fixture_file,a);break;case 11:restore_light_sources(&fixture_file);break;case 12:light_stats("light-size=%ld",output,&stats_count,a?&stats_count:&stats_size);break;case 13:relink_light_sources(a);break;case 14:b=maybe_write_ls(&fixture_file,a,b);panic_guard=0;return b;case 15:light_sources_sanity_check();break;case 16:write_ls(&fixture_file,node(a));break;case 17:obj_move_light_source(o,&objects_pool[b]);break;case 18:b=any_light_source();panic_guard=0;return b;case 19:snuff_light_source(a,b);break;case 20:b=obj_sheds_light(o);panic_guard=0;return b;case 21:b=obj_is_burning(o);panic_guard=0;return b;case 22:obj_split_light_source(o,&objects_pool[b]);break;case 23:obj_merge_light_sources(o,&objects_pool[b]);break;case 24:obj_adjust_light_radius(o,b);break;case 25:b=candle_light_range(o);panic_guard=0;return b;case 26:b=arti_light_radius(o);panic_guard=0;return b;case 27:strcpy(output,arti_light_description(o));break;case 28:b=wiz_light_sources();panic_guard=0;return b;}panic_guard=0;return 0;}
long probe_panic_code(void){return -2147483647L;}
anything *probe_union_pointer(void){return &identifier;}
void *probe_pointer(int kind,int index){switch(kind){case 0:return &objects_pool[index];case 1:return index<0?&gy.youmonst:&monsters[index];case 2:return &u;case 3:return vision;case 4:return vision_rows;case 5:return output;case 6:return (void*)circle_data;case 7:return (void*)circle_start;case 8:return &fixture_file;}return NULL;}
light_source *probe_node_pointer(int i){return node(i);}
int probe_node_count(void){light_source *l;int n=0;for(l=gl.light_base;l;l=l->next)if(++n>1000)abort();return n;}
void probe_nhfile(int key,int value){if(key==0)fixture_file.mode=value;else if(key==1)fixture_file.structlevel=value;else fixture_file.fnidx=value;}
unsigned char *probe_io_pointer(void){return io;}
void probe_io_length(unsigned n){io_size=n;}
void probe_io_position(unsigned n){io_position=n;}
unsigned probe_io_size(void){return io_size;}
int probe_free_count(void){return free_count;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){char *p=statebuf;int i;p+=sprintf(p,"state:%d:%d:%d:%ld:%ld:%u:%u;objects:",gv.vision_full_recalc,free_count,zero_fail,stats_count,stats_size,io_size,io_position);for(i=0;i<16;i++){struct obj *o=&objects_pool[i];p+=sprintf(p,"%d,%u,%ld,%d,%d,%d,%d,%d,%d,%d/",o->otyp,o->o_id,o->quan,o->spe,o->lamplit,o->blessed,o->cursed,o->where,o->ox,o->oy);}p+=sprintf(p,";mons:");for(i=0;i<16;i++){struct monst *m=&monsters[i];p+=sprintf(p,"%u,%d,%d,%d,%d,%d,%d/",m->m_id,m->mhp,m->mx,m->my,m->isgd,m->mtemplit,m->nmon?mid(m->nmon):-1);}p+=sprintf(p,";output:%s;",output);return statebuf;}
