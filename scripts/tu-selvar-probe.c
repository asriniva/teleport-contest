#include "hack.h"
#include "selvar.h"
#include "sp_lev.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(cg) cg={0};
__typeof__(svl) svl;
__typeof__(svr) svr;
__typeof__(gc) gc;
static struct sp_coder coder;
static struct selectionvar *selections[8];
static NhRect output_rect;
static coordxy output_x,output_y,xs[32],ys[32];
static int random_values[256],random_length,random_index,options[4],token;
static unsigned random_state;
static char probe_trace_storage[262144],caller[128],description[BUFSZ+32];
static void *callback_allocation;
void panic(const char *format,...){abort();}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(probe_trace_storage+strlen(probe_trace_storage),sizeof probe_trace_storage-strlen(probe_trace_storage),format,ap);va_end(ap);}
void impossible(const char *format,...){char b[BUFSZ];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("impossible:%s;",b);}
boolean rng_log_enabled(void){return options[3];}
void rng_log_set_caller(const char *file,int line,const char *function){const char *base=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",base?base+1:file,line,function);}
int (rn2)(int bound){int value;if(bound<=0)abort();if(random_index<random_length)value=random_values[random_index]%bound;else{random_state=random_state*1664525U+1013904223U;value=(random_state>>8)%(unsigned)bound;}random_index++;append("rn2:%d:%d@%s;",bound,value,caller);return value;}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
boolean match_maptyps(xint16 requested,xint16 actual){append("match:%d:%d;",requested,actual);return requested==-1||requested==actual;}
coordxy random_wdir(void){append("direction;");return options[0];}
void newsym_force(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
static void callback_effect(coordxy x,coordxy y){if(options[1]&&selections[1])selection_setpoint(x,y,selections[1],1);if(options[2]&&!callback_allocation){callback_allocation=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!callback_allocation)abort();append("grow-callback;");}}
static int flood_a(coordxy x,coordxy y){append("flood-a:%d:%d;",x,y);callback_effect(x,y);return levl[x][y].typ==ROOM;}
static int flood_b(coordxy x,coordxy y){append("flood-b:%d:%d;",x,y);callback_effect(x,y);return levl[x][y].lit?2:0;}
static void iter_a(coordxy x,coordxy y,genericptr arg){append("iterate:%d:%d:%d;",x,y,arg==&token);callback_effect(x,y);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/selvar.c"
#else
extern boolean teleport_selvar_test_havepoint(coordxy,coordxy,coordxy *,coordxy *,int);
extern long teleport_selvar_test_line_dist(long,long,long,long,long,long);
#endif
#include "tu-selvar-layout.h"
static void replace(int index,struct selectionvar *s){if(selections[index])selection_free(selections[index],TRUE);selections[index]=s;}
void probe_reset(unsigned seed){int i;for(i=0;i<SIZE(selections);i++){selection_free(selections[i],TRUE);selections[i]=NULL;}if(callback_allocation)free(callback_allocation);callback_allocation=NULL;memset(&svl,0,sizeof svl);memset(&svr,0,sizeof svr);memset(&gc,0,sizeof gc);memset(&coder,0,sizeof coder);memset(&output_rect,0xa5,sizeof output_rect);output_x=output_y=-77;memset(options,0,sizeof options);options[3]=1;random_state=seed;random_length=random_index=0;probe_trace_storage[0]=caller[0]=0;memset(description,0xa5,sizeof description);set_selection_floodfillchk(NULL);}
void probe_clear_trace(void){probe_trace_storage[0]=0;}
const char *probe_trace(void){return probe_trace_storage;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_option(int n,int value){options[n]=value;}
void probe_new(int slot){replace(slot,selection_new());}
void probe_free(int slot,int all){selection_free(selections[slot],all);if((boolean)all)selections[slot]=NULL;}
void probe_clear(int slot,int val){selection_clear(selections[slot],val);}
void probe_clone(int from,int to){replace(to,selection_clone(selections[from]));}
int probe_get(int slot,int x,int y){return selection_getpoint(x,y,slot<0?NULL:selections[slot]);}
void probe_set(int slot,int x,int y,int value){selection_setpoint(x,y,slot<0?NULL:selections[slot],value);}
void probe_bounds(int slot,int nullout){selection_getbounds(slot<0?NULL:selections[slot],nullout?NULL:&output_rect);}
void probe_recalc(int slot){selection_recalc_bounds(selections[slot]);}
int probe_not(int slot){return selection_not(selections[slot])==selections[slot];}
void probe_filter(int from,int to,int percent){replace(to,selection_filter_percent(from<0?NULL:selections[from],percent));}
void probe_mapfilter(int from,int to,int typ,int lit){replace(to,selection_filter_mapchar(from<0?NULL:selections[from],typ,lit));}
int probe_rndcoord(int slot,int remove){return selection_rndcoord(selections[slot],&output_x,&output_y,remove);}
void probe_grow(int slot,int dir){selection_do_grow(slot<0?NULL:selections[slot],dir);}
void probe_flood_callback(int which){set_selection_floodfillchk(which==0?NULL:which==1?flood_a:flood_b);}
int probe_callback_identity(void){
#ifdef TELEPORT_REFERENCE_TU
return selection_flood_check_func==NULL?0:selection_flood_check_func==flood_a?1:selection_flood_check_func==flood_b?2:99;
#else
return 0;
#endif
}
uintptr_t probe_callback_pointer(int which){return (uintptr_t)(which==1?flood_a:flood_b);}
void probe_flood(int slot,int x,int y,int diagonals){selection_floodfill(selections[slot],x,y,diagonals);}
void probe_ellipse(int slot,int x,int y,int a,int b,int fill){selection_do_ellipse(slot<0?NULL:selections[slot],x,y,a,b,fill);}
long probe_distance(long x1,long y1,long x2,long y2,long x3,long y3){
#ifdef TELEPORT_REFERENCE_TU
return line_dist_coord(x1,y1,x2,y2,x3,y3);
#else
return teleport_selvar_test_line_dist(x1,y1,x2,y2,x3,y3);
#endif
}
void probe_gradient(int slot,long x,long y,long x2,long y2,long type,long min,long max){selection_do_gradient(selections[slot],x,y,x2,y2,type,min,max);}
void probe_line(int slot,int x1,int y1,int x2,int y2){selection_do_line(x1,y1,x2,y2,selections[slot]);}
void probe_randline(int slot,int x1,int y1,int x2,int y2,int rough,int rec){selection_do_randline(x1,y1,x2,y2,rough,rec,selections[slot]);}
void probe_iterate(int slot,int validarg){selection_iterate(slot<0?NULL:selections[slot],iter_a,validarg?&token:NULL);}
int probe_irregular(int slot){return selection_is_irregular(selections[slot]);}
int probe_description(int slot){return selection_size_description(selections[slot],description)==description;}
void probe_room(int index,int lx,int ly,int hx,int hy){svr.rooms[index].lx=lx;svr.rooms[index].ly=ly;svr.rooms[index].hx=hx;svr.rooms[index].hy=hy;}
void probe_coder(int which,int room){gc.coder=which?&coder:NULL;coder.croom=room<0?NULL:&svr.rooms[room];}
void probe_fromroom(int to,int room){replace(to,selection_from_mkroom(room<0?NULL:&svr.rooms[room]));}
void probe_newsyms(int slot){selection_force_newsyms(selections[slot]);}
void probe_cell(int x,int y,int typ,int lit,int edge,int room){levl[x][y].typ=typ;levl[x][y].lit=lit;levl[x][y].edge=edge;levl[x][y].roomno=room;}
void probe_array(int index,int x,int y){xs[index]=x;ys[index]=y;}
int probe_have(int x,int y,int n){
#ifdef TELEPORT_REFERENCE_TU
return sel_flood_havepoint(x,y,xs,ys,n);
#else
return teleport_selvar_test_havepoint(x,y,xs,ys,n);
#endif
}
void *probe_pointer(int slot){return selections[slot];}
void *probe_map(int slot){return selections[slot]?selections[slot]->map:NULL;}
int probe_field(int slot,int field){struct selectionvar *s=selections[slot];if(!s)return -999;switch(field){case 0:return s->wid;case 1:return s->hei;case 2:return s->bounds_dirty;case 3:return s->bounds.lx;case 4:return s->bounds.ly;case 5:return s->bounds.hx;default:return s->bounds.hy;}}
void *probe_rect(void){return &output_rect;}
size_t probe_rect_size(void){return sizeof output_rect;}
int probe_coord(int which){return which?output_y:output_x;}
const char *probe_description_pointer(void){return description;}
size_t probe_description_size(void){return sizeof description;}
size_t probe_stack(void){return emscripten_stack_get_current();}
