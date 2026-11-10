/* VISION typed fields, native aliases and original dependency transport only. */
#include "hack.h"
extern const coordxy circle_data[137],circle_start[16];
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
extern const seenV seenv_matrix[3][3];
static seenV teleport_vision_could_see[2][21][80];
static seenV * teleport_vision_cs_rows0[21];
static seenV * teleport_vision_cs_rows1[21];
static coordxy teleport_vision_cs_rmin0[21];
static coordxy teleport_vision_cs_rmax0[21];
static coordxy teleport_vision_cs_rmin1[21];
static coordxy teleport_vision_cs_rmax1[21];
static char teleport_vision_viz_clear[21][80];
static char * teleport_vision_viz_clear_rows[21];
static coordxy teleport_vision_left_ptrs[21][80];
static coordxy teleport_vision_right_ptrs[21][80];
static int teleport_vision_start_row;
static int teleport_vision_start_col;
static int teleport_vision_step;
static seenV ** teleport_vision_cs_rows;
static coordxy * teleport_vision_cs_left;
static coordxy * teleport_vision_cs_right;
static void (*teleport_vision_vis_func)(coordxy, coordxy, genericptr_t);
static genericptr_t teleport_vision_varg;
static coordxy  teleport_vision_colbump[81];
void *teleport_vision_storage(int index){switch(index){
case 0:return (void*)&teleport_vision_could_see;
case 1:return (void*)&teleport_vision_cs_rows0;
case 2:return (void*)&teleport_vision_cs_rows1;
case 3:return (void*)&teleport_vision_cs_rmin0;
case 4:return (void*)&teleport_vision_cs_rmax0;
case 5:return (void*)&teleport_vision_cs_rmin1;
case 6:return (void*)&teleport_vision_cs_rmax1;
case 7:return (void*)&teleport_vision_viz_clear;
case 8:return (void*)&teleport_vision_viz_clear_rows;
case 9:return (void*)&teleport_vision_left_ptrs;
case 10:return (void*)&teleport_vision_right_ptrs;
case 11:return (void*)&teleport_vision_start_row;
case 12:return (void*)&teleport_vision_start_col;
case 13:return (void*)&teleport_vision_step;
case 14:return (void*)&teleport_vision_cs_rows;
case 15:return (void*)&teleport_vision_cs_left;
case 16:return (void*)&teleport_vision_cs_right;
case 17:return (void*)&teleport_vision_vis_func;
case 18:return (void*)&teleport_vision_varg;
case 19:return (void*)&teleport_vision_colbump;
case 20:return (void*)circle_data;
case 21:return (void*)circle_start;
default:abort();}}
void *teleport_vision_global(int index){switch(index){
case 0:return (void*)&flags;
case 1:return (void*)&iflags;
case 2:return (void*)&u;
case 3:return (void*)&gi;
case 4:return (void*)&gs;
case 5:return (void*)&gv;
case 6:return (void*)&svc;
case 7:return (void*)&svd;
case 8:return (void*)&svl;
case 9:return (void*)&svr;
case 10:return (void*)&program_state;
case 11:return (void*)&seenv_matrix;
default:abort();}}
uint64_t teleport_vision_read(int kind,void*at,int field){switch(kind){
case 0:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->locations);
case 1:return (uint64_t)(uintptr_t)(&p->objects);
case 2:return (uint64_t)(uintptr_t)(&p->monsters);
default:abort();}}
case 1:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->typ);
case 1:return (uint64_t)(uintptr_t)(p->seenv);
case 2:return (uint64_t)(uintptr_t)(p->flags);
case 3:return (uint64_t)(uintptr_t)(p->lit);
case 4:return (uint64_t)(uintptr_t)(p->waslit);
case 5:return (uint64_t)(uintptr_t)(p->roomno);
default:abort();}}
case 2:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->v);
case 1:return (uint64_t)(uintptr_t)(p->otyp);
default:abort();}}
case 3:{union vptrs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 4:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
case 1:return (uint64_t)(uintptr_t)(p->mx);
case 2:return (uint64_t)(uintptr_t)(p->my);
case 3:return (uint64_t)(uintptr_t)(p->mappearance);
case 4:return (uint64_t)(uintptr_t)(p->m_ap_type);
case 5:return (uint64_t)(uintptr_t)(p->minvis);
case 6:return (uint64_t)(uintptr_t)(p->wormno);
default:abort();}}
case 5:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 6:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(&p->uz);
case 3:return (uint64_t)(uintptr_t)(p->utrap);
case 4:return (uint64_t)(uintptr_t)(p->utraptype);
case 5:return (uint64_t)(uintptr_t)(&p->uprops);
case 6:return (uint64_t)(uintptr_t)(p->nv_range);
case 7:return (uint64_t)(uintptr_t)(p->xray_range);
case 8:return (uint64_t)(uintptr_t)(p->uswallow);
case 9:return (uint64_t)(uintptr_t)(p->uinwater);
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 8:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->blocked);
case 2:return (uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 9:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 10:{struct mkroom*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->lx);
case 1:return (uint64_t)(uintptr_t)(p->hx);
case 2:return (uint64_t)(uintptr_t)(p->ly);
case 3:return (uint64_t)(uintptr_t)(p->hy);
case 4:return (uint64_t)(uintptr_t)(p->rlit);
default:abort();}}
case 11:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->panicking);
case 1:return (uint64_t)(uintptr_t)(p->in_getlev);
default:abort();}}
case 12:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->viz_array);
case 1:return (uint64_t)(uintptr_t)(p->viz_rmin);
case 2:return (uint64_t)(uintptr_t)(p->viz_rmax);
case 3:return (uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 13:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 14:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->warntype);
default:abort();}}
case 15:{struct warntype_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->obj);
case 1:return (uint64_t)(uintptr_t)(p->polyd);
case 2:return (uint64_t)(uintptr_t)(p->species);
default:abort();}}
case 16:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->seethru);
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 18:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_rogue_level);
case 1:return (uint64_t)(uintptr_t)(&p->d_water_level);
case 2:return (uint64_t)(uintptr_t)(&p->d_air_level);
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->in_mklev);
default:abort();}}
case 20:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->vision_inited);
default:abort();}}
case 21:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->debug);
default:abort();}}
case 22:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
default:abort();}}
void teleport_vision_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{dlevel_t*p=at;switch(field){
default:abort();}}
case 1:{struct rm*p=at;switch(field){
case 0:p->typ=value;return;
case 1:p->seenv=value;return;
case 2:p->flags=value;return;
case 3:p->lit=value;return;
case 4:p->waslit=value;return;
case 5:p->roomno=value;return;
default:abort();}}
case 2:{struct obj*p=at;switch(field){
case 0:memmove(&p->v, (void*)(uintptr_t)value,sizeof p->v);return;
case 1:p->otyp=value;return;
default:abort();}}
case 3:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(void*)(uintptr_t)value;return;
default:abort();}}
case 4:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
case 1:p->mx=value;return;
case 2:p->my=value;return;
case 3:p->mappearance=value;return;
case 4:p->m_ap_type=value;return;
case 5:p->minvis=value;return;
case 6:p->wormno=value;return;
default:abort();}}
case 5:{struct permonst*p=at;switch(field){
case 0:p->mflags2=value;return;
default:abort();}}
case 6:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:memmove(&p->uz, (void*)(uintptr_t)value,sizeof p->uz);return;
case 3:p->utrap=value;return;
case 4:p->utraptype=value;return;
case 6:p->nv_range=value;return;
case 7:p->xray_range=value;return;
case 8:p->uswallow=value;return;
case 9:p->uinwater=value;return;
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 8:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->blocked=value;return;
case 2:p->intrinsic=value;return;
default:abort();}}
case 9:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 10:{struct mkroom*p=at;switch(field){
case 0:p->lx=value;return;
case 1:p->hx=value;return;
case 2:p->ly=value;return;
case 3:p->hy=value;return;
case 4:p->rlit=value;return;
default:abort();}}
case 11:{struct sinfo*p=at;switch(field){
case 0:p->panicking=value;return;
case 1:p->in_getlev=value;return;
default:abort();}}
case 12:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(void*)(uintptr_t)value;return;
case 1:p->viz_rmin=(void*)(uintptr_t)value;return;
case 2:p->viz_rmax=(void*)(uintptr_t)value;return;
case 3:p->vision_full_recalc=value;return;
default:abort();}}
case 13:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context, (void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 14:{struct context_info*p=at;switch(field){
case 0:memmove(&p->warntype, (void*)(uintptr_t)value,sizeof p->warntype);return;
default:abort();}}
case 15:{struct warntype_info*p=at;switch(field){
case 0:p->obj=value;return;
case 1:p->polyd=value;return;
case 2:p->species=(void*)(uintptr_t)value;return;
default:abort();}}
case 16:{struct instance_globals_s*p=at;switch(field){
case 0:p->seethru=value;return;
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology, (void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 18:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_rogue_level, (void*)(uintptr_t)value,sizeof p->d_rogue_level);return;
case 1:memmove(&p->d_water_level, (void*)(uintptr_t)value,sizeof p->d_water_level);return;
case 2:memmove(&p->d_air_level, (void*)(uintptr_t)value,sizeof p->d_air_level);return;
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_mklev=value;return;
default:abort();}}
case 20:{struct instance_flags*p=at;switch(field){
case 0:p->vision_inited=value;return;
default:abort();}}
case 21:{struct flag*p=at;switch(field){
case 0:p->debug=value;return;
default:abort();}}
case 22:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level, (void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
default:abort();}}
void* teleport_vision_address(int kind,void*at,int field){switch(kind){
case 0:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->locations;
case 1:return (void*)&p->objects;
case 2:return (void*)&p->monsters;
default:abort();}}
case 1:{struct rm*p=at;switch(field){
case 0:return (void*)&p->typ;
case 1:return (void*)&p->seenv;
default:abort();}}
case 2:{struct obj*p=at;switch(field){
case 0:return (void*)&p->v;
case 1:return (void*)&p->otyp;
default:abort();}}
case 3:{union vptrs*p=at;switch(field){
case 0:return (void*)&p->v_nexthere;
default:abort();}}
case 4:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
case 1:return (void*)&p->mx;
case 2:return (void*)&p->my;
case 3:return (void*)&p->mappearance;
case 4:return (void*)&p->m_ap_type;
default:abort();}}
case 5:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->mflags2;
default:abort();}}
case 6:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->uz;
case 3:return (void*)&p->utrap;
case 4:return (void*)&p->utraptype;
case 5:return (void*)&p->uprops;
case 6:return (void*)&p->nv_range;
case 7:return (void*)&p->xray_range;
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 8:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->blocked;
case 2:return (void*)&p->intrinsic;
default:abort();}}
case 9:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (void*)&p->rooms;
default:abort();}}
case 10:{struct mkroom*p=at;switch(field){
case 0:return (void*)&p->lx;
case 1:return (void*)&p->hx;
case 2:return (void*)&p->ly;
case 3:return (void*)&p->hy;
case 4:return (void*)&p->rlit;
default:abort();}}
case 11:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->panicking;
case 1:return (void*)&p->in_getlev;
default:abort();}}
case 12:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->viz_array;
case 1:return (void*)&p->viz_rmin;
case 2:return (void*)&p->viz_rmax;
case 3:return (void*)&p->vision_full_recalc;
default:abort();}}
case 13:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 14:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->warntype;
default:abort();}}
case 15:{struct warntype_info*p=at;switch(field){
case 0:return (void*)&p->obj;
case 1:return (void*)&p->polyd;
case 2:return (void*)&p->species;
default:abort();}}
case 16:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->seethru;
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
default:abort();}}
case 18:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_rogue_level;
case 1:return (void*)&p->d_water_level;
case 2:return (void*)&p->d_air_level;
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->in_mklev;
default:abort();}}
case 20:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->vision_inited;
default:abort();}}
case 21:{struct flag*p=at;switch(field){
case 0:return (void*)&p->debug;
default:abort();}}
case 22:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
default:abort();}}
default:abort();}}
void teleport_vision_panic(const char*fmt,int n){panic(fmt,n);}
void teleport_vision_invoke(uintptr_t cb,coordxy x,coordxy y,void*arg){((void(*)(coordxy,coordxy,genericptr_t))cb)(x,y,arg);}
void*teleport_vision_literal(unsigned n){return malloc(n);}
int teleport_vision_debug(const char*s){return explicitdebug(s);}
void teleport_vision_assert(int ok,const char*expr,const char*fn,int line){if(!ok)__assert_fail(expr,"vision.c",line,fn);}
