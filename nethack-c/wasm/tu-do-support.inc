/* DO typed fields, aliases, callbacks and native dependency transport only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static char teleport_do_wipebuf[39];
void*teleport_do_buffer(void){return teleport_do_wipebuf;}
void *teleport_do_global(int index){switch(index){
case 0:return (void*)&objects;
case 1:return (void*)&flags;
case 2:return (void*)&iflags;
case 3:return (void*)&a11y;
case 4:return (void*)&defsyms;
case 5:return (void*)&mons;
case 6:return (void*)&windowprocs;
case 7:return (void*)&nhcb_name;
case 8:return (void*)&nhcb_counts;
case 9:return (void*)&c_color_names;
case 10:return (void*)&c_common_strings;
case 11:return (void*)&ynchars;
case 12:return (void*)&uwep;
case 13:return (void*)&uswapwep;
case 14:return (void*)&uquiver;
case 15:return (void*)&uchain;
case 16:return (void*)&uball;
case 17:return (void*)&u;
case 18:return (void*)&disp;
case 19:return (void*)&ga;
case 20:return (void*)&gb;
case 21:return (void*)&gd;
case 22:return (void*)&gf;
case 23:return (void*)&gi;
case 24:return (void*)&gl;
case 25:return (void*)&gm;
case 26:return (void*)&gu;
case 27:return (void*)&gv;
case 28:return (void*)&gy;
case 29:return (void*)&svc;
case 30:return (void*)&svd;
case 31:return (void*)&svh;
case 32:return (void*)&svl;
case 33:return (void*)&svm;
case 34:return (void*)&svn;
case 35:return (void*)&svp;
case 36:return (void*)&svq;
case 37:return (void*)&svu;
case 38:return (void*)&program_state;
default:abort();}}
uint64_t teleport_do_read(int kind,void*at,int field){switch(kind){
case 0:{struct nh_file*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->fd);
case 1:return (uint64_t)(uintptr_t)(p->mode);
case 2:return (uint64_t)(uintptr_t)(p->structlevel);
default:abort();}}
case 1:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(p->dz);
case 3:return (uint64_t)(uintptr_t)(&p->uz);
case 4:return (uint64_t)(uintptr_t)(&p->uz0);
case 5:return (uint64_t)(uintptr_t)(&p->utolev);
case 6:return (uint64_t)(uintptr_t)(p->utotype);
case 7:return (uint64_t)(uintptr_t)(p->utrap);
case 8:return (uint64_t)(uintptr_t)(p->utraptype);
case 9:return (uint64_t)(uintptr_t)(&p->ushops);
case 10:return (uint64_t)(uintptr_t)(&p->uprops);
case 11:return (uint64_t)(uintptr_t)(p->umonster);
case 12:return (uint64_t)(uintptr_t)(p->umonnum);
case 13:return (uint64_t)(uintptr_t)(p->ucreamed);
case 14:return (uint64_t)(uintptr_t)(p->uswallow);
case 15:return (uint64_t)(uintptr_t)(p->uinwater);
case 16:return (uint64_t)(uintptr_t)(p->uundetected);
case 17:return (uint64_t)(uintptr_t)(&p->uevent);
case 18:return (uint64_t)(uintptr_t)(&p->uhave);
case 19:return (uint64_t)(uintptr_t)(&p->uconduct);
case 20:return (uint64_t)(uintptr_t)(&p->uroleplay);
case 21:return (uint64_t)(uintptr_t)(&p->atemp);
case 22:return (uint64_t)(uintptr_t)(&p->ualign);
case 23:return (uint64_t)(uintptr_t)(p->uluck);
case 24:return (uint64_t)(uintptr_t)(p->moreluck);
case 25:return (uint64_t)(uintptr_t)(p->ustuck);
case 26:return (uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
case 2:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 3:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->blocked);
case 2:return (uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 4:{struct u_event*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->qcalled);
case 1:return (uint64_t)(uintptr_t)(p->qexpelled);
case 2:return (uint64_t)(uintptr_t)(p->qcompleted);
case 3:return (uint64_t)(uintptr_t)(p->gehennom_entered);
default:abort();}}
case 5:{struct u_have*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->amulet);
default:abort();}}
case 6:{struct u_conduct*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->gnostic);
default:abort();}}
case 7:{struct u_roleplay*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 8:{struct attribs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->a);
default:abort();}}
case 9:{struct align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 10:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nmon);
case 1:return (uint64_t)(uintptr_t)(p->data);
case 2:return (uint64_t)(uintptr_t)(p->cham);
case 3:return (uint64_t)(uintptr_t)(p->mx);
case 4:return (uint64_t)(uintptr_t)(p->my);
case 5:return (uint64_t)(uintptr_t)(p->mhp);
case 6:return (uint64_t)(uintptr_t)(p->mhpmax);
case 7:return (uint64_t)(uintptr_t)(p->msleeping);
case 8:return (uint64_t)(uintptr_t)(p->mtrapped);
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mlet);
case 1:return (uint64_t)(uintptr_t)(p->msize);
case 2:return (uint64_t)(uintptr_t)(p->mflags1);
case 3:return (uint64_t)(uintptr_t)(p->mflags2);
case 4:return (uint64_t)(uintptr_t)(p->mflags3);
default:abort();}}
case 12:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 13:{union any*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->a_obj);
case 1:return (uint64_t)(uintptr_t)(p->a_int);
default:abort();}}
case 14:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nobj);
case 1:return (uint64_t)(uintptr_t)(&p->v);
case 2:return (uint64_t)(uintptr_t)(p->cobj);
case 3:return (uint64_t)(uintptr_t)(p->ox);
case 4:return (uint64_t)(uintptr_t)(p->oy);
case 5:return (uint64_t)(uintptr_t)(p->otyp);
case 6:return (uint64_t)(uintptr_t)(p->quan);
case 7:return (uint64_t)(uintptr_t)(p->spe);
case 8:return (uint64_t)(uintptr_t)(p->oclass);
case 9:return (uint64_t)(uintptr_t)(p->invlet);
case 10:return (uint64_t)(uintptr_t)(p->oartifact);
case 11:return (uint64_t)(uintptr_t)(p->where);
case 12:return (uint64_t)(uintptr_t)(p->cursed);
case 13:return (uint64_t)(uintptr_t)(p->blessed);
case 14:return (uint64_t)(uintptr_t)(p->bknown);
case 15:return (uint64_t)(uintptr_t)(p->oerodeproof);
case 16:return (uint64_t)(uintptr_t)(p->globby);
case 17:return (uint64_t)(uintptr_t)(p->in_use);
case 18:return (uint64_t)(uintptr_t)(p->bypass);
case 19:return (uint64_t)(uintptr_t)(p->how_lost);
case 20:return (uint64_t)(uintptr_t)(p->corpsenm);
case 21:return (uint64_t)(uintptr_t)(p->oeaten);
case 22:return (uint64_t)(uintptr_t)(p->age);
case 23:return (uint64_t)(uintptr_t)(p->owornmask);
case 24:return (uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 15:{union vptrs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->v_nexthere);
case 1:return (uint64_t)(uintptr_t)(p->v_ocontainer);
case 2:return (uint64_t)(uintptr_t)(p->v_ocarry);
default:abort();}}
case 16:{struct oextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->omonst);
case 1:return (uint64_t)(uintptr_t)(p->omid);
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeons);
case 1:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
case 2:return (uint64_t)(uintptr_t)(&p->dndest);
default:abort();}}
case 18:{struct dungeon*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dunlev_ureached);
default:abort();}}
case 19:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_bigroom_level);
case 1:return (uint64_t)(uintptr_t)(&p->d_rogue_level);
case 2:return (uint64_t)(uintptr_t)(&p->d_stronghold_level);
case 3:return (uint64_t)(uintptr_t)(&p->d_valley_level);
case 4:return (uint64_t)(uintptr_t)(&p->d_earth_level);
case 5:return (uint64_t)(uintptr_t)(&p->d_water_level);
case 6:return (uint64_t)(uintptr_t)(&p->d_air_level);
case 7:return (uint64_t)(uintptr_t)(&p->d_astral_level);
case 8:return (uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 9:return (uint64_t)(uintptr_t)(p->d_tutorial_dnum);
case 10:return (uint64_t)(uintptr_t)(&p->d_qstart_level);
case 11:return (uint64_t)(uintptr_t)(&p->d_knox_level);
default:abort();}}
case 20:{struct dest_area*p=at;switch(field){
default:abort();}}
case 21:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->locations);
case 1:return (uint64_t)(uintptr_t)(&p->objects);
case 2:return (uint64_t)(uintptr_t)(&p->monsters);
case 3:return (uint64_t)(uintptr_t)(p->monlist);
case 4:return (uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 22:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->glyph);
case 1:return (uint64_t)(uintptr_t)(p->typ);
case 2:return (uint64_t)(uintptr_t)(p->flags);
case 3:return (uint64_t)(uintptr_t)(p->horizontal);
default:abort();}}
case 23:{struct levelflags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->has_shop);
case 1:return (uint64_t)(uintptr_t)(p->fumaroles);
case 2:return (uint64_t)(uintptr_t)(p->temperature);
case 3:return (uint64_t)(uintptr_t)(p->stasis_until);
default:abort();}}
case 24:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->gameover);
case 1:return (uint64_t)(uintptr_t)(p->in_checkpoint);
default:abort();}}
case 25:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
case 1:return (uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 26:{struct mvitals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->died);
case 1:return (uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 27:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ntrap);
case 1:return (uint64_t)(uintptr_t)(p->tx);
case 2:return (uint64_t)(uintptr_t)(p->ty);
case 3:return (uint64_t)(uintptr_t)(&p->dst);
case 4:return (uint64_t)(uintptr_t)(p->ttyp);
case 5:return (uint64_t)(uintptr_t)(p->tseen);
case 6:return (uint64_t)(uintptr_t)(p->madeby_u);
default:abort();}}
case 28:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nofollowers);
case 1:return (uint64_t)(uintptr_t)(p->debug_fuzzer);
case 2:return (uint64_t)(uintptr_t)(&p->travelcc);
case 3:return (uint64_t)(uintptr_t)(p->menu_requested);
case 4:return (uint64_t)(uintptr_t)(p->cmdassist);
default:abort();}}
case 29:{struct nhcoord*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->x);
case 1:return (uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 30:{struct q_score*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->leader_is_dead);
default:abort();}}
case 31:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->bhitpos);
default:abort();}}
case 32:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mysteryforce);
case 1:return (uint64_t)(uintptr_t)(p->nopick);
case 2:return (uint64_t)(uintptr_t)(p->mon_moving);
case 3:return (uint64_t)(uintptr_t)(&p->polearm);
default:abort();}}
case 33:{struct polearm_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hitmon);
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->item);
case 1:return (uint64_t)(uintptr_t)(p->count);
default:abort();}}
case 35:{struct accessibility_data*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mon_notices_blocked);
default:abort();}}
case 36:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 37:{struct instance_globals_f*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 38:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->autodig);
case 1:return (uint64_t)(uintptr_t)(p->debug);
case 2:return (uint64_t)(uintptr_t)(p->ins_chkpt);
case 3:return (uint64_t)(uintptr_t)(p->safe_wait);
case 4:return (uint64_t)(uintptr_t)(p->verbose);
case 5:return (uint64_t)(uintptr_t)(p->menu_style);
default:abort();}}
case 39:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_something);
case 1:return (uint64_t)(uintptr_t)(p->c_Something);
case 2:return (uint64_t)(uintptr_t)(&p->c_the_your);
default:abort();}}
case 40:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 41:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 42:{struct stairway*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->sx);
case 1:return (uint64_t)(uintptr_t)(p->sy);
case 2:return (uint64_t)(uintptr_t)(p->up);
case 3:return (uint64_t)(uintptr_t)(p->isladder);
case 4:return (uint64_t)(uintptr_t)(p->u_traversed);
default:abort();}}
case 43:{struct linfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 44:{struct c_color_names*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_black);
case 1:return (uint64_t)(uintptr_t)(p->c_amber);
case 2:return (uint64_t)(uintptr_t)(p->c_silver);
case 3:return (uint64_t)(uintptr_t)(p->c_white);
default:abort();}}
case 45:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hackpid);
default:abort();}}
case 46:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->win_mark_synch);
default:abort();}}
case 47:{struct symdef*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->explanation);
default:abort();}}
case 48:{struct instance_globals_a*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->at_ladder);
default:abort();}}
case 49:{struct instance_globals_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dfr_pre_msg);
case 1:return (uint64_t)(uintptr_t)(p->dfr_post_msg);
case 2:return (uint64_t)(uintptr_t)(p->did_nothing_flag);
default:abort();}}
case 50:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->viz_array);
case 1:return (uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 51:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 52:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->n_dgns);
default:abort();}}
case 53:{struct instance_globals_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->luacore);
default:abort();}}
case 54:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->updest);
default:abort();}}
case 55:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 56:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
case 1:return (uint64_t)(uintptr_t)(&p->level_info);
default:abort();}}
case 57:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_uname);
case 1:return (uint64_t)(uintptr_t)(p->oc_name_known);
case 2:return (uint64_t)(uintptr_t)(p->oc_big);
case 3:return (uint64_t)(uintptr_t)(p->oc_subtyp);
default:abort();}}
case 58:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->multi);
default:abort();}}
case 59:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->quest_status);
default:abort();}}
case 60:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
default:abort();}}
void teleport_do_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct nh_file*p=at;switch(field){
case 0:p->fd=value;return;
case 1:p->mode=value;return;
case 2:p->structlevel=value;return;
default:abort();}}
case 1:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:p->dz=value;return;
case 3:memmove(&p->uz, (void*)(uintptr_t)value,sizeof p->uz);return;
case 4:memmove(&p->uz0, (void*)(uintptr_t)value,sizeof p->uz0);return;
case 5:memmove(&p->utolev, (void*)(uintptr_t)value,sizeof p->utolev);return;
case 6:p->utotype=value;return;
case 7:p->utrap=value;return;
case 8:p->utraptype=value;return;
case 11:p->umonster=value;return;
case 12:p->umonnum=value;return;
case 13:p->ucreamed=value;return;
case 14:p->uswallow=value;return;
case 15:p->uinwater=value;return;
case 16:p->uundetected=value;return;
case 17:memmove(&p->uevent, (void*)(uintptr_t)value,sizeof p->uevent);return;
case 18:memmove(&p->uhave, (void*)(uintptr_t)value,sizeof p->uhave);return;
case 19:memmove(&p->uconduct, (void*)(uintptr_t)value,sizeof p->uconduct);return;
case 20:memmove(&p->uroleplay, (void*)(uintptr_t)value,sizeof p->uroleplay);return;
case 21:memmove(&p->atemp, (void*)(uintptr_t)value,sizeof p->atemp);return;
case 22:memmove(&p->ualign, (void*)(uintptr_t)value,sizeof p->ualign);return;
case 23:p->uluck=value;return;
case 24:p->moreluck=value;return;
case 25:p->ustuck=(void*)(uintptr_t)value;return;
case 26:p->usteed=(void*)(uintptr_t)value;return;
default:abort();}}
case 2:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 3:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->blocked=value;return;
case 2:p->intrinsic=value;return;
default:abort();}}
case 4:{struct u_event*p=at;switch(field){
case 0:p->qcalled=value;return;
case 1:p->qexpelled=value;return;
case 2:p->qcompleted=value;return;
case 3:p->gehennom_entered=value;return;
default:abort();}}
case 5:{struct u_have*p=at;switch(field){
case 0:p->amulet=value;return;
default:abort();}}
case 6:{struct u_conduct*p=at;switch(field){
case 0:p->gnostic=value;return;
default:abort();}}
case 7:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=value;return;
default:abort();}}
case 8:{struct attribs*p=at;switch(field){
default:abort();}}
case 9:{struct align*p=at;switch(field){
case 0:p->type=value;return;
default:abort();}}
case 10:{struct monst*p=at;switch(field){
case 0:p->nmon=(void*)(uintptr_t)value;return;
case 1:p->data=(void*)(uintptr_t)value;return;
case 2:p->cham=value;return;
case 3:p->mx=value;return;
case 4:p->my=value;return;
case 5:p->mhp=value;return;
case 6:p->mhpmax=value;return;
case 7:p->msleeping=value;return;
case 8:p->mtrapped=value;return;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:p->mlet=value;return;
case 1:p->msize=value;return;
case 2:p->mflags1=value;return;
case 3:p->mflags2=value;return;
case 4:p->mflags3=value;return;
default:abort();}}
case 12:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 13:{union any*p=at;switch(field){
case 0:p->a_obj=(void*)(uintptr_t)value;return;
case 1:p->a_int=value;return;
default:abort();}}
case 14:{struct obj*p=at;switch(field){
case 0:p->nobj=(void*)(uintptr_t)value;return;
case 1:memmove(&p->v, (void*)(uintptr_t)value,sizeof p->v);return;
case 2:p->cobj=(void*)(uintptr_t)value;return;
case 3:p->ox=value;return;
case 4:p->oy=value;return;
case 5:p->otyp=value;return;
case 6:p->quan=value;return;
case 7:p->spe=value;return;
case 8:p->oclass=value;return;
case 9:p->invlet=value;return;
case 10:p->oartifact=value;return;
case 11:p->where=value;return;
case 12:p->cursed=value;return;
case 13:p->blessed=value;return;
case 14:p->bknown=value;return;
case 15:p->oerodeproof=value;return;
case 16:p->globby=value;return;
case 17:p->in_use=value;return;
case 18:p->bypass=value;return;
case 19:p->how_lost=value;return;
case 20:p->corpsenm=value;return;
case 21:p->oeaten=value;return;
case 22:p->age=value;return;
case 23:p->owornmask=value;return;
case 24:p->oextra=(void*)(uintptr_t)value;return;
default:abort();}}
case 15:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(void*)(uintptr_t)value;return;
case 1:p->v_ocontainer=(void*)(uintptr_t)value;return;
case 2:p->v_ocarry=(void*)(uintptr_t)value;return;
default:abort();}}
case 16:{struct oextra*p=at;switch(field){
case 0:p->omonst=(void*)(uintptr_t)value;return;
case 1:p->omid=value;return;
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 1:memmove(&p->dungeon_topology, (void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
case 2:memmove(&p->dndest, (void*)(uintptr_t)value,sizeof p->dndest);return;
default:abort();}}
case 18:{struct dungeon*p=at;switch(field){
case 0:p->dunlev_ureached=value;return;
default:abort();}}
case 19:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_bigroom_level, (void*)(uintptr_t)value,sizeof p->d_bigroom_level);return;
case 1:memmove(&p->d_rogue_level, (void*)(uintptr_t)value,sizeof p->d_rogue_level);return;
case 2:memmove(&p->d_stronghold_level, (void*)(uintptr_t)value,sizeof p->d_stronghold_level);return;
case 3:memmove(&p->d_valley_level, (void*)(uintptr_t)value,sizeof p->d_valley_level);return;
case 4:memmove(&p->d_earth_level, (void*)(uintptr_t)value,sizeof p->d_earth_level);return;
case 5:memmove(&p->d_water_level, (void*)(uintptr_t)value,sizeof p->d_water_level);return;
case 6:memmove(&p->d_air_level, (void*)(uintptr_t)value,sizeof p->d_air_level);return;
case 7:memmove(&p->d_astral_level, (void*)(uintptr_t)value,sizeof p->d_astral_level);return;
case 8:p->d_sokoban_dnum=value;return;
case 9:p->d_tutorial_dnum=value;return;
case 10:memmove(&p->d_qstart_level, (void*)(uintptr_t)value,sizeof p->d_qstart_level);return;
case 11:memmove(&p->d_knox_level, (void*)(uintptr_t)value,sizeof p->d_knox_level);return;
default:abort();}}
case 20:{struct dest_area*p=at;switch(field){
default:abort();}}
case 21:{dlevel_t*p=at;switch(field){
case 3:p->monlist=(void*)(uintptr_t)value;return;
case 4:memmove(&p->flags, (void*)(uintptr_t)value,sizeof p->flags);return;
default:abort();}}
case 22:{struct rm*p=at;switch(field){
case 0:p->glyph=value;return;
case 1:p->typ=value;return;
case 2:p->flags=value;return;
case 3:p->horizontal=value;return;
default:abort();}}
case 23:{struct levelflags*p=at;switch(field){
case 0:p->has_shop=value;return;
case 1:p->fumaroles=value;return;
case 2:p->temperature=value;return;
case 3:p->stasis_until=value;return;
default:abort();}}
case 24:{struct sinfo*p=at;switch(field){
case 0:p->gameover=value;return;
case 1:p->in_checkpoint=value;return;
default:abort();}}
case 25:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 26:{struct mvitals*p=at;switch(field){
case 0:p->died=value;return;
case 1:p->mvflags=value;return;
default:abort();}}
case 27:{struct trap*p=at;switch(field){
case 0:p->ntrap=(void*)(uintptr_t)value;return;
case 1:p->tx=value;return;
case 2:p->ty=value;return;
case 3:memmove(&p->dst, (void*)(uintptr_t)value,sizeof p->dst);return;
case 4:p->ttyp=value;return;
case 5:p->tseen=value;return;
case 6:p->madeby_u=value;return;
default:abort();}}
case 28:{struct instance_flags*p=at;switch(field){
case 0:p->nofollowers=value;return;
case 1:p->debug_fuzzer=value;return;
case 2:memmove(&p->travelcc, (void*)(uintptr_t)value,sizeof p->travelcc);return;
case 3:p->menu_requested=value;return;
case 4:p->cmdassist=value;return;
default:abort();}}
case 29:{struct nhcoord*p=at;switch(field){
case 0:p->x=value;return;
case 1:p->y=value;return;
default:abort();}}
case 30:{struct q_score*p=at;switch(field){
case 0:p->leader_is_dead=value;return;
default:abort();}}
case 31:{struct instance_globals_b*p=at;switch(field){
case 0:memmove(&p->bhitpos, (void*)(uintptr_t)value,sizeof p->bhitpos);return;
default:abort();}}
case 32:{struct context_info*p=at;switch(field){
case 0:p->mysteryforce=value;return;
case 1:p->nopick=value;return;
case 2:p->mon_moving=value;return;
case 3:memmove(&p->polearm, (void*)(uintptr_t)value,sizeof p->polearm);return;
default:abort();}}
case 33:{struct polearm_info*p=at;switch(field){
case 0:p->hitmon=(void*)(uintptr_t)value;return;
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 0:memmove(&p->item, (void*)(uintptr_t)value,sizeof p->item);return;
case 1:p->count=value;return;
default:abort();}}
case 35:{struct accessibility_data*p=at;switch(field){
case 0:p->mon_notices_blocked=value;return;
default:abort();}}
case 36:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context, (void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 37:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(void*)(uintptr_t)value;return;
default:abort();}}
case 38:{struct flag*p=at;switch(field){
case 0:p->autodig=value;return;
case 1:p->debug=value;return;
case 2:p->ins_chkpt=value;return;
case 3:p->safe_wait=value;return;
case 4:p->verbose=value;return;
case 5:p->menu_style=value;return;
default:abort();}}
case 39:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 40:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole, (void*)(uintptr_t)value,sizeof p->urole);return;
default:abort();}}
case 41:{struct Role*p=at;switch(field){
case 0:p->mnum=value;return;
default:abort();}}
case 42:{struct stairway*p=at;switch(field){
case 0:p->sx=value;return;
case 1:p->sy=value;return;
case 2:p->up=value;return;
case 3:p->isladder=value;return;
case 4:p->u_traversed=value;return;
default:abort();}}
case 43:{struct linfo*p=at;switch(field){
case 0:p->flags=value;return;
default:abort();}}
case 44:{struct c_color_names*p=at;switch(field){
default:abort();}}
case 45:{struct instance_globals_saved_h*p=at;switch(field){
case 0:p->hackpid=value;return;
default:abort();}}
case 46:{struct window_procs*p=at;switch(field){
case 0:p->win_mark_synch=(__typeof__(p->win_mark_synch))(uintptr_t)value;return;
default:abort();}}
case 47:{struct symdef*p=at;switch(field){
default:abort();}}
case 48:{struct instance_globals_a*p=at;switch(field){
case 0:p->at_ladder=value;return;
default:abort();}}
case 49:{struct instance_globals_d*p=at;switch(field){
case 0:p->dfr_pre_msg=(void*)(uintptr_t)value;return;
case 1:p->dfr_post_msg=(void*)(uintptr_t)value;return;
case 2:p->did_nothing_flag=value;return;
default:abort();}}
case 50:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(void*)(uintptr_t)value;return;
case 1:p->vision_full_recalc=value;return;
default:abort();}}
case 51:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 52:{struct instance_globals_saved_n*p=at;switch(field){
case 0:p->n_dgns=value;return;
default:abort();}}
case 53:{struct instance_globals_l*p=at;switch(field){
case 0:p->luacore=(void*)(uintptr_t)value;return;
default:abort();}}
case 54:{struct instance_globals_saved_u*p=at;switch(field){
case 0:memmove(&p->updest, (void*)(uintptr_t)value,sizeof p->updest);return;
default:abort();}}
case 55:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
default:abort();}}
case 56:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level, (void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 57:{struct objclass*p=at;switch(field){
case 0:p->oc_uname=(void*)(uintptr_t)value;return;
case 1:p->oc_name_known=value;return;
case 2:p->oc_big=value;return;
case 3:p->oc_subtyp=value;return;
default:abort();}}
case 58:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=value;return;
default:abort();}}
case 59:{struct instance_globals_saved_q*p=at;switch(field){
case 0:memmove(&p->quest_status, (void*)(uintptr_t)value,sizeof p->quest_status);return;
default:abort();}}
case 60:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst, (void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
default:abort();}}
void* teleport_do_address(int kind,void*at,int field){switch(kind){
case 0:{struct nh_file*p=at;switch(field){
case 0:return (void*)&p->fd;
case 1:return (void*)&p->mode;
case 2:return (void*)&p->structlevel;
default:abort();}}
case 1:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->dz;
case 3:return (void*)&p->uz;
case 4:return (void*)&p->uz0;
case 5:return (void*)&p->utolev;
case 6:return (void*)&p->utotype;
case 7:return (void*)&p->utrap;
case 8:return (void*)&p->utraptype;
case 9:return (void*)&p->ushops;
case 10:return (void*)&p->uprops;
case 11:return (void*)&p->umonster;
case 12:return (void*)&p->umonnum;
case 13:return (void*)&p->ucreamed;
case 17:return (void*)&p->uevent;
case 18:return (void*)&p->uhave;
case 19:return (void*)&p->uconduct;
case 20:return (void*)&p->uroleplay;
case 21:return (void*)&p->atemp;
case 22:return (void*)&p->ualign;
case 23:return (void*)&p->uluck;
case 24:return (void*)&p->moreluck;
case 25:return (void*)&p->ustuck;
case 26:return (void*)&p->usteed;
default:abort();}}
case 2:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 3:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->blocked;
case 2:return (void*)&p->intrinsic;
default:abort();}}
case 4:{struct u_event*p=at;switch(field){
default:abort();}}
case 5:{struct u_have*p=at;switch(field){
default:abort();}}
case 6:{struct u_conduct*p=at;switch(field){
case 0:return (void*)&p->gnostic;
default:abort();}}
case 7:{struct u_roleplay*p=at;switch(field){
case 0:return (void*)&p->deaf;
default:abort();}}
case 8:{struct attribs*p=at;switch(field){
case 0:return (void*)&p->a;
default:abort();}}
case 9:{struct align*p=at;switch(field){
case 0:return (void*)&p->type;
default:abort();}}
case 10:{struct monst*p=at;switch(field){
case 0:return (void*)&p->nmon;
case 1:return (void*)&p->data;
case 2:return (void*)&p->cham;
case 3:return (void*)&p->mx;
case 4:return (void*)&p->my;
case 5:return (void*)&p->mhp;
case 6:return (void*)&p->mhpmax;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->mlet;
case 1:return (void*)&p->msize;
case 2:return (void*)&p->mflags1;
case 3:return (void*)&p->mflags2;
case 4:return (void*)&p->mflags3;
default:abort();}}
case 12:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (void*)&p->plname;
default:abort();}}
case 13:{union any*p=at;switch(field){
case 0:return (void*)&p->a_obj;
case 1:return (void*)&p->a_int;
default:abort();}}
case 14:{struct obj*p=at;switch(field){
case 0:return (void*)&p->nobj;
case 1:return (void*)&p->v;
case 2:return (void*)&p->cobj;
case 3:return (void*)&p->ox;
case 4:return (void*)&p->oy;
case 5:return (void*)&p->otyp;
case 6:return (void*)&p->quan;
case 7:return (void*)&p->spe;
case 8:return (void*)&p->oclass;
case 9:return (void*)&p->invlet;
case 10:return (void*)&p->oartifact;
case 11:return (void*)&p->where;
case 20:return (void*)&p->corpsenm;
case 21:return (void*)&p->oeaten;
case 22:return (void*)&p->age;
case 23:return (void*)&p->owornmask;
case 24:return (void*)&p->oextra;
default:abort();}}
case 15:{union vptrs*p=at;switch(field){
case 0:return (void*)&p->v_nexthere;
case 1:return (void*)&p->v_ocontainer;
case 2:return (void*)&p->v_ocarry;
default:abort();}}
case 16:{struct oextra*p=at;switch(field){
case 0:return (void*)&p->omonst;
case 1:return (void*)&p->omid;
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeons;
case 1:return (void*)&p->dungeon_topology;
case 2:return (void*)&p->dndest;
default:abort();}}
case 18:{struct dungeon*p=at;switch(field){
case 0:return (void*)&p->dunlev_ureached;
default:abort();}}
case 19:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_bigroom_level;
case 1:return (void*)&p->d_rogue_level;
case 2:return (void*)&p->d_stronghold_level;
case 3:return (void*)&p->d_valley_level;
case 4:return (void*)&p->d_earth_level;
case 5:return (void*)&p->d_water_level;
case 6:return (void*)&p->d_air_level;
case 7:return (void*)&p->d_astral_level;
case 8:return (void*)&p->d_sokoban_dnum;
case 9:return (void*)&p->d_tutorial_dnum;
case 10:return (void*)&p->d_qstart_level;
case 11:return (void*)&p->d_knox_level;
default:abort();}}
case 20:{struct dest_area*p=at;switch(field){
default:abort();}}
case 21:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->locations;
case 1:return (void*)&p->objects;
case 2:return (void*)&p->monsters;
case 3:return (void*)&p->monlist;
case 4:return (void*)&p->flags;
default:abort();}}
case 22:{struct rm*p=at;switch(field){
case 0:return (void*)&p->glyph;
case 1:return (void*)&p->typ;
default:abort();}}
case 23:{struct levelflags*p=at;switch(field){
case 2:return (void*)&p->temperature;
case 3:return (void*)&p->stasis_until;
default:abort();}}
case 24:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->gameover;
case 1:return (void*)&p->in_checkpoint;
default:abort();}}
case 25:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
case 1:return (void*)&p->mvitals;
default:abort();}}
case 26:{struct mvitals*p=at;switch(field){
case 0:return (void*)&p->died;
case 1:return (void*)&p->mvflags;
default:abort();}}
case 27:{struct trap*p=at;switch(field){
case 0:return (void*)&p->ntrap;
case 1:return (void*)&p->tx;
case 2:return (void*)&p->ty;
case 3:return (void*)&p->dst;
default:abort();}}
case 28:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->nofollowers;
case 1:return (void*)&p->debug_fuzzer;
case 2:return (void*)&p->travelcc;
case 3:return (void*)&p->menu_requested;
case 4:return (void*)&p->cmdassist;
default:abort();}}
case 29:{struct nhcoord*p=at;switch(field){
case 0:return (void*)&p->x;
case 1:return (void*)&p->y;
default:abort();}}
case 30:{struct q_score*p=at;switch(field){
default:abort();}}
case 31:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->bhitpos;
default:abort();}}
case 32:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->mysteryforce;
case 1:return (void*)&p->nopick;
case 2:return (void*)&p->mon_moving;
case 3:return (void*)&p->polearm;
default:abort();}}
case 33:{struct polearm_info*p=at;switch(field){
case 0:return (void*)&p->hitmon;
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 0:return (void*)&p->item;
case 1:return (void*)&p->count;
default:abort();}}
case 35:{struct accessibility_data*p=at;switch(field){
case 0:return (void*)&p->mon_notices_blocked;
default:abort();}}
case 36:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 37:{struct instance_globals_f*p=at;switch(field){
case 0:return (void*)&p->ftrap;
default:abort();}}
case 38:{struct flag*p=at;switch(field){
case 0:return (void*)&p->autodig;
case 1:return (void*)&p->debug;
case 2:return (void*)&p->ins_chkpt;
case 3:return (void*)&p->safe_wait;
case 4:return (void*)&p->verbose;
case 5:return (void*)&p->menu_style;
default:abort();}}
case 39:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_something;
case 1:return (void*)&p->c_Something;
case 2:return (void*)&p->c_the_your;
default:abort();}}
case 40:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
default:abort();}}
case 41:{struct Role*p=at;switch(field){
case 0:return (void*)&p->mnum;
default:abort();}}
case 42:{struct stairway*p=at;switch(field){
case 0:return (void*)&p->sx;
case 1:return (void*)&p->sy;
case 2:return (void*)&p->up;
case 3:return (void*)&p->isladder;
case 4:return (void*)&p->u_traversed;
default:abort();}}
case 43:{struct linfo*p=at;switch(field){
case 0:return (void*)&p->flags;
default:abort();}}
case 44:{struct c_color_names*p=at;switch(field){
case 0:return (void*)&p->c_black;
case 1:return (void*)&p->c_amber;
case 2:return (void*)&p->c_silver;
case 3:return (void*)&p->c_white;
default:abort();}}
case 45:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return (void*)&p->hackpid;
default:abort();}}
case 46:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->win_mark_synch;
default:abort();}}
case 47:{struct symdef*p=at;switch(field){
case 0:return (void*)&p->explanation;
default:abort();}}
case 48:{struct instance_globals_a*p=at;switch(field){
case 0:return (void*)&p->at_ladder;
default:abort();}}
case 49:{struct instance_globals_d*p=at;switch(field){
case 0:return (void*)&p->dfr_pre_msg;
case 1:return (void*)&p->dfr_post_msg;
case 2:return (void*)&p->did_nothing_flag;
default:abort();}}
case 50:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->viz_array;
case 1:return (void*)&p->vision_full_recalc;
default:abort();}}
case 51:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 52:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (void*)&p->n_dgns;
default:abort();}}
case 53:{struct instance_globals_l*p=at;switch(field){
case 0:return (void*)&p->luacore;
default:abort();}}
case 54:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return (void*)&p->updest;
default:abort();}}
case 55:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
default:abort();}}
case 56:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
case 1:return (void*)&p->level_info;
default:abort();}}
case 57:{struct objclass*p=at;switch(field){
case 0:return (void*)&p->oc_uname;
case 3:return (void*)&p->oc_subtyp;
default:abort();}}
case 58:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->multi;
default:abort();}}
case 59:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (void*)&p->quest_status;
default:abort();}}
case 60:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
default:abort();}}
void*teleport_do_literal(unsigned n){return malloc(n);}

#include "tu-do-varargs.inc"
