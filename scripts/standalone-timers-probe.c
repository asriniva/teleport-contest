/* Actual timeout queue and item policies; input/result transport only. */
#include "standalone-item-inventory-probe.c"
#include "timeout.h"
#include <stddef.h>
static anything timer_args[4];
void *probe_timer_arg(int i){return &timer_args[i];}
void *probe_timer_global(int i){switch(i){case 0:return &gt.timer_base;case 1:return &svt.timer_id;case 2:return &svm.moves;}return NULL;}
long probe_timer_op(int op,long when,int kind,int fn,int arg,int a,int b){switch(op){
 case 0:return start_timer(when,kind,fn,&timer_args[arg]);
 case 1:return stop_timer(fn,&timer_args[arg]);case 2:return peek_timer(fn,&timer_args[arg]);
 case 3:obj_stop_timers(items[a]);break;case 4:obj_move_timers(items[a],items[b]);break;
 case 5:obj_split_timers(items[a],items[b]);break;case 6:return obj_has_timer(items[a],fn);
 case 7:run_timers();break;case 8:attach_egg_hatch_timeout(items[a],when);break;
 case 9:attach_fig_transform_timeout(items[a]);break;case 10:kill_egg(items[a]);break;
 }return 0;}
long probe_timer_layout(int i){static const size_t v[]={sizeof(timer_element),__alignof__(timer_element),offsetof(timer_element,next),offsetof(timer_element,timeout),offsetof(timer_element,tid),offsetof(timer_element,kind),offsetof(timer_element,func_index),offsetof(timer_element,arg),sizeof(anything)};return v[i];}
unsigned probe_timer_fixup(timer_element *timer,unsigned value){timer->needs_fixup=value;return timer->needs_fixup;}
