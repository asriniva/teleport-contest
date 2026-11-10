/* POLYSELF typed native field/global/literal/dependency transport only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "polyself-source-data.h"
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4,"POLYSELF memory64 ABI");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0,"POLYSELF signed boolean");
_Static_assert(sizeof(coordxy)==2&&(coordxy)-1<0,"POLYSELF signed coordxy");
void*teleport_polyself_global(int i){switch(i){
case 0:return (void*)&mons;
case 1:return (void*)&u;
case 2:return (void*)&gy;
case 3:return (void*)&uwep;
case 4:return (void*)&gu;
case 5:return (void*)&program_state;
case 6:return (void*)&windowprocs;
case 7:return (void*)&gw;
case 8:return (void*)&disp;
case 9:return (void*)&uamul;
case 10:return (void*)&flags;
case 11:return (void*)&gm;
case 12:return (void*)&svk;
case 13:return (void*)&svp;
case 14:return (void*)&genders;
case 15:return (void*)&gs;
case 16:return (void*)&uarmg;
case 17:return (void*)&uarm;
case 18:return (void*)&c_common_strings;
case 19:return (void*)&svm;
case 20:return (void*)&uskin;
case 21:return (void*)&ynchars;
case 22:return (void*)&svd;
case 23:return (void*)&uball;
case 24:return (void*)&gv;
case 25:return (void*)&gi;
case 26:return (void*)&uarmc;
case 27:return (void*)&uarmu;
case 28:return (void*)&uarmh;
case 29:return (void*)&objects;
case 30:return (void*)&uarms;
case 31:return (void*)&uarmf;
case 32:return (void*)&ublindf;
case 33:return (void*)&uswapwep;
case 34:return (void*)&svl;
case 35:return (void*)&gn;
case 36:return (void*)&svc;
default:abort();}}
uint64_t teleport_polyself_read(int kind,void*at,int field){switch(kind){
case 0:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 1:{struct RoleName*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->m);
case 1:return (uint64_t)(uintptr_t)(p->f);
default:abort();}}
case 2:{union vptrs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->confirm);
case 1:return (uint64_t)(uintptr_t)(p->debug);
case 2:return (uint64_t)(uintptr_t)(p->female);
case 3:return (uint64_t)(uintptr_t)(p->safe_dog);
case 4:return (uint64_t)(uintptr_t)(p->verbose);
default:abort();}}
case 4:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ttyp);
case 1:return (uint64_t)(uintptr_t)(p->madeby_u);
default:abort();}}
case 5:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wincap2);
default:abort();}}
case 6:{struct attribs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->a);
default:abort();}}
case 7:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nobj);
case 1:return (uint64_t)(uintptr_t)(&p->v);
case 2:return (uint64_t)(uintptr_t)(p->otyp);
case 3:return (uint64_t)(uintptr_t)(p->quan);
case 4:return (uint64_t)(uintptr_t)(p->spe);
case 5:return (uint64_t)(uintptr_t)(p->oclass);
case 6:return (uint64_t)(uintptr_t)(p->lamplit);
case 7:return (uint64_t)(uintptr_t)(p->in_use);
case 8:return (uint64_t)(uintptr_t)(p->corpsenm);
case 9:return (uint64_t)(uintptr_t)(p->owornmask);
default:abort();}}
case 8:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_material);
case 1:return (uint64_t)(uintptr_t)(p->oc_subtyp);
default:abort();}}
case 9:{struct attack*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->aatyp);
case 1:return (uint64_t)(uintptr_t)(p->adtyp);
case 2:return (uint64_t)(uintptr_t)(p->damn);
case 3:return (uint64_t)(uintptr_t)(p->damd);
default:abort();}}
case 10:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mlet);
case 1:return (uint64_t)(uintptr_t)(p->mlevel);
case 2:return (uint64_t)(uintptr_t)(p->geno);
case 3:return (uint64_t)(uintptr_t)(&p->mattk);
case 4:return (uint64_t)(uintptr_t)(p->msound);
case 5:return (uint64_t)(uintptr_t)(p->msize);
case 6:return (uint64_t)(uintptr_t)(p->mresists);
case 7:return (uint64_t)(uintptr_t)(p->mflags1);
case 8:return (uint64_t)(uintptr_t)(p->mflags2);
case 9:return (uint64_t)(uintptr_t)(p->mflags3);
default:abort();}}
case 11:{struct warntype_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->polyd);
case 1:return (uint64_t)(uintptr_t)(p->species);
case 2:return (uint64_t)(uintptr_t)(p->speciesidx);
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->blocked);
case 2:return (uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nmon);
case 1:return (uint64_t)(uintptr_t)(p->data);
case 2:return (uint64_t)(uintptr_t)(p->m_id);
case 3:return (uint64_t)(uintptr_t)(p->mnum);
case 4:return (uint64_t)(uintptr_t)(p->cham);
case 5:return (uint64_t)(uintptr_t)(p->m_lev);
case 6:return (uint64_t)(uintptr_t)(p->mx);
case 7:return (uint64_t)(uintptr_t)(p->my);
case 8:return (uint64_t)(uintptr_t)(p->mhp);
case 9:return (uint64_t)(uintptr_t)(p->mappearance);
case 10:return (uint64_t)(uintptr_t)(p->m_ap_type);
case 11:return (uint64_t)(uintptr_t)(p->mtame);
case 12:return (uint64_t)(uintptr_t)(p->minvis);
case 13:return (uint64_t)(uintptr_t)(p->mcan);
case 14:return (uint64_t)(uintptr_t)(p->mcansee);
case 15:return (uint64_t)(uintptr_t)(p->msleeping);
case 16:return (uint64_t)(uintptr_t)(p->mstun);
case 17:return (uint64_t)(uintptr_t)(p->mcanmove);
case 18:return (uint64_t)(uintptr_t)(p->mconf);
case 19:return (uint64_t)(uintptr_t)(p->mpeaceful);
case 20:return (uint64_t)(uintptr_t)(p->minvent);
default:abort();}}
case 14:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 15:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->warntype);
default:abort();}}
case 16:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->typ);
default:abort();}}
case 17:{struct u_conduct*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->polyselfs);
default:abort();}}
case 18:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_thats_enough_tries);
case 1:return (uint64_t)(uintptr_t)(p->c_shudder_for_moment);
case 2:return (uint64_t)(uintptr_t)(p->c_Never_mind);
case 3:return (uint64_t)(uintptr_t)(&p->c_the_your);
default:abort();}}
case 19:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->name);
case 1:return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 20:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_water_level);
case 1:return (uint64_t)(uintptr_t)(&p->d_air_level);
case 2:return (uint64_t)(uintptr_t)(&p->d_astral_level);
default:abort();}}
case 21:{struct Race*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->noun);
case 1:return (uint64_t)(uintptr_t)(p->adj);
case 2:return (uint64_t)(uintptr_t)(&p->individual);
case 3:return (uint64_t)(uintptr_t)(p->mnum);
case 4:return (uint64_t)(uintptr_t)(p->selfmask);
case 5:return (uint64_t)(uintptr_t)(&p->attrmax);
default:abort();}}
case 22:{struct Gender*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->adj);
default:abort();}}
case 23:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 24:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(p->dx);
case 3:return (uint64_t)(uintptr_t)(p->dy);
case 4:return (uint64_t)(uintptr_t)(p->dz);
case 5:return (uint64_t)(uintptr_t)(&p->uz);
case 6:return (uint64_t)(uintptr_t)(p->ulevel);
case 7:return (uint64_t)(uintptr_t)(p->ulevelmax);
case 8:return (uint64_t)(uintptr_t)(p->utrap);
case 9:return (uint64_t)(uintptr_t)(p->utraptype);
case 10:return (uint64_t)(uintptr_t)(p->uhunger);
case 11:return (uint64_t)(uintptr_t)(&p->uprops);
case 12:return (uint64_t)(uintptr_t)(p->umonster);
case 13:return (uint64_t)(uintptr_t)(p->umonnum);
case 14:return (uint64_t)(uintptr_t)(p->mh);
case 15:return (uint64_t)(uintptr_t)(p->mhmax);
case 16:return (uint64_t)(uintptr_t)(p->mtimedone);
case 17:return (uint64_t)(uintptr_t)(&p->macurr);
case 18:return (uint64_t)(uintptr_t)(&p->mamax);
case 19:return (uint64_t)(uintptr_t)(p->ulycn);
case 20:return (uint64_t)(uintptr_t)(p->uswallow);
case 21:return (uint64_t)(uintptr_t)(p->uinwater);
case 22:return (uint64_t)(uintptr_t)(p->uundetected);
case 23:return (uint64_t)(uintptr_t)(p->mfemale);
case 24:return (uint64_t)(uintptr_t)(&p->uconduct);
case 25:return (uint64_t)(uintptr_t)(&p->acurr);
case 26:return (uint64_t)(uintptr_t)(&p->amax);
case 27:return (uint64_t)(uintptr_t)(p->uhp);
case 28:return (uint64_t)(uintptr_t)(p->uhpmax);
case 29:return (uint64_t)(uintptr_t)(p->uen);
case 30:return (uint64_t)(uintptr_t)(p->uenmax);
case 31:return (uint64_t)(uintptr_t)(&p->uhpinc);
case 32:return (uint64_t)(uintptr_t)(&p->ueninc);
case 33:return (uint64_t)(uintptr_t)(p->uexp);
case 34:return (uint64_t)(uintptr_t)(p->ustuck);
case 35:return (uint64_t)(uintptr_t)(p->usteed);
case 36:return (uint64_t)(uintptr_t)(p->twoweap);
case 37:return (uint64_t)(uintptr_t)(p->mcham);
default:abort();}}
case 25:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->multi);
case 1:return (uint64_t)(uintptr_t)(p->multi_reason);
default:abort();}}
case 26:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->locations);
case 1:return (uint64_t)(uintptr_t)(&p->objects);
case 2:return (uint64_t)(uintptr_t)(p->monlist);
default:abort();}}
case 27:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 28:{struct kinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->format);
case 1:return (uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 29:{struct mvitals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->sex_change_ok);
default:abort();}}
case 31:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->restoring);
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
case 1:return (uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->viz_array);
case 1:return (uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 34:{struct instance_globals_w*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->were_changes);
default:abort();}}
case 35:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 36:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 38:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 39:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 40:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 41:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->pl_character);
default:abort();}}
default:abort();}}
void teleport_polyself_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 1:{struct RoleName*p=at;switch(field){
case 0:p->m=(void*)(uintptr_t)value;return;
case 1:p->f=(void*)(uintptr_t)value;return;
default:abort();}}
case 2:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(void*)(uintptr_t)value;return;
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:p->confirm=value;return;
case 1:p->debug=value;return;
case 2:p->female=value;return;
case 3:p->safe_dog=value;return;
case 4:p->verbose=value;return;
default:abort();}}
case 4:{struct trap*p=at;switch(field){
case 0:p->ttyp=value;return;
case 1:p->madeby_u=value;return;
default:abort();}}
case 5:{struct window_procs*p=at;switch(field){
case 0:p->wincap2=value;return;
default:abort();}}
case 6:{struct attribs*p=at;switch(field){
default:abort();}}
case 7:{struct obj*p=at;switch(field){
case 0:p->nobj=(void*)(uintptr_t)value;return;
case 1:memmove(&p->v,(void*)(uintptr_t)value,sizeof p->v);return;
case 2:p->otyp=value;return;
case 3:p->quan=value;return;
case 4:p->spe=value;return;
case 5:p->oclass=value;return;
case 6:p->lamplit=value;return;
case 7:p->in_use=value;return;
case 8:p->corpsenm=value;return;
case 9:p->owornmask=value;return;
default:abort();}}
case 8:{struct objclass*p=at;switch(field){
case 0:p->oc_material=value;return;
case 1:p->oc_subtyp=value;return;
default:abort();}}
case 9:{struct attack*p=at;switch(field){
case 0:p->aatyp=value;return;
case 1:p->adtyp=value;return;
case 2:p->damn=value;return;
case 3:p->damd=value;return;
default:abort();}}
case 10:{struct permonst*p=at;switch(field){
case 0:p->mlet=value;return;
case 1:p->mlevel=value;return;
case 2:p->geno=value;return;
case 4:p->msound=value;return;
case 5:p->msize=value;return;
case 6:p->mresists=value;return;
case 7:p->mflags1=value;return;
case 8:p->mflags2=value;return;
case 9:p->mflags3=value;return;
default:abort();}}
case 11:{struct warntype_info*p=at;switch(field){
case 0:p->polyd=value;return;
case 1:p->species=(void*)(uintptr_t)value;return;
case 2:p->speciesidx=value;return;
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->blocked=value;return;
case 2:p->intrinsic=value;return;
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:p->nmon=(void*)(uintptr_t)value;return;
case 1:p->data=(void*)(uintptr_t)value;return;
case 2:p->m_id=value;return;
case 3:p->mnum=value;return;
case 4:p->cham=value;return;
case 5:p->m_lev=value;return;
case 6:p->mx=value;return;
case 7:p->my=value;return;
case 8:p->mhp=value;return;
case 9:p->mappearance=value;return;
case 10:p->m_ap_type=value;return;
case 11:p->mtame=value;return;
case 12:p->minvis=value;return;
case 13:p->mcan=value;return;
case 14:p->mcansee=value;return;
case 15:p->msleeping=value;return;
case 16:p->mstun=value;return;
case 17:p->mcanmove=value;return;
case 18:p->mconf=value;return;
case 19:p->mpeaceful=value;return;
case 20:p->minvent=(void*)(uintptr_t)value;return;
default:abort();}}
case 14:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
default:abort();}}
case 15:{struct context_info*p=at;switch(field){
case 0:memmove(&p->warntype,(void*)(uintptr_t)value,sizeof p->warntype);return;
default:abort();}}
case 16:{struct rm*p=at;switch(field){
case 0:p->typ=value;return;
default:abort();}}
case 17:{struct u_conduct*p=at;switch(field){
case 0:p->polyselfs=value;return;
default:abort();}}
case 18:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 19:{struct Role*p=at;switch(field){
case 0:memmove(&p->name,(void*)(uintptr_t)value,sizeof p->name);return;
case 1:p->mnum=value;return;
default:abort();}}
case 20:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_water_level,(void*)(uintptr_t)value,sizeof p->d_water_level);return;
case 1:memmove(&p->d_air_level,(void*)(uintptr_t)value,sizeof p->d_air_level);return;
case 2:memmove(&p->d_astral_level,(void*)(uintptr_t)value,sizeof p->d_astral_level);return;
default:abort();}}
case 21:{struct Race*p=at;switch(field){
case 0:p->noun=(void*)(uintptr_t)value;return;
case 1:p->adj=(void*)(uintptr_t)value;return;
case 2:memmove(&p->individual,(void*)(uintptr_t)value,sizeof p->individual);return;
case 3:p->mnum=value;return;
case 4:p->selfmask=value;return;
default:abort();}}
case 22:{struct Gender*p=at;switch(field){
case 0:p->adj=(void*)(uintptr_t)value;return;
default:abort();}}
case 23:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 24:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:p->dx=value;return;
case 3:p->dy=value;return;
case 4:p->dz=value;return;
case 5:memmove(&p->uz,(void*)(uintptr_t)value,sizeof p->uz);return;
case 6:p->ulevel=value;return;
case 7:p->ulevelmax=value;return;
case 8:p->utrap=value;return;
case 9:p->utraptype=value;return;
case 10:p->uhunger=value;return;
case 12:p->umonster=value;return;
case 13:p->umonnum=value;return;
case 14:p->mh=value;return;
case 15:p->mhmax=value;return;
case 16:p->mtimedone=value;return;
case 17:memmove(&p->macurr,(void*)(uintptr_t)value,sizeof p->macurr);return;
case 18:memmove(&p->mamax,(void*)(uintptr_t)value,sizeof p->mamax);return;
case 19:p->ulycn=value;return;
case 20:p->uswallow=value;return;
case 21:p->uinwater=value;return;
case 22:p->uundetected=value;return;
case 23:p->mfemale=value;return;
case 24:memmove(&p->uconduct,(void*)(uintptr_t)value,sizeof p->uconduct);return;
case 25:memmove(&p->acurr,(void*)(uintptr_t)value,sizeof p->acurr);return;
case 26:memmove(&p->amax,(void*)(uintptr_t)value,sizeof p->amax);return;
case 27:p->uhp=value;return;
case 28:p->uhpmax=value;return;
case 29:p->uen=value;return;
case 30:p->uenmax=value;return;
case 33:p->uexp=value;return;
case 34:p->ustuck=(void*)(uintptr_t)value;return;
case 35:p->usteed=(void*)(uintptr_t)value;return;
case 36:p->twoweap=value;return;
case 37:p->mcham=value;return;
default:abort();}}
case 25:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=value;return;
case 1:p->multi_reason=(void*)(uintptr_t)value;return;
default:abort();}}
case 26:{dlevel_t*p=at;switch(field){
case 2:p->monlist=(void*)(uintptr_t)value;return;
default:abort();}}
case 27:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(void*)(uintptr_t)value;return;
default:abort();}}
case 28:{struct kinfo*p=at;switch(field){
case 0:p->format=value;return;
default:abort();}}
case 29:{struct mvitals*p=at;switch(field){
case 0:p->mvflags=value;return;
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:p->sex_change_ok=value;return;
default:abort();}}
case 31:{struct sinfo*p=at;switch(field){
case 0:p->restoring=value;return;
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole,(void*)(uintptr_t)value,sizeof p->urole);return;
case 1:memmove(&p->urace,(void*)(uintptr_t)value,sizeof p->urace);return;
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(void*)(uintptr_t)value;return;
case 1:p->vision_full_recalc=value;return;
default:abort();}}
case 34:{struct instance_globals_w*p=at;switch(field){
case 0:p->were_changes=value;return;
default:abort();}}
case 35:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst,(void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 36:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context,(void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology,(void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 38:{struct instance_globals_saved_k*p=at;switch(field){
case 0:memmove(&p->killer,(void*)(uintptr_t)value,sizeof p->killer);return;
default:abort();}}
case 39:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level,(void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 40:{struct instance_globals_saved_m*p=at;switch(field){
default:abort();}}
case 41:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_polyself_address(int kind,void*at,int field){switch(kind){
case 0:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 1:{struct RoleName*p=at;switch(field){
case 0:return (void*)&p->m;
case 1:return (void*)&p->f;
default:abort();}}
case 2:{union vptrs*p=at;switch(field){
case 0:return (void*)&p->v_nexthere;
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:return (void*)&p->confirm;
case 1:return (void*)&p->debug;
case 2:return (void*)&p->female;
case 3:return (void*)&p->safe_dog;
case 4:return (void*)&p->verbose;
default:abort();}}
case 4:{struct trap*p=at;switch(field){
default:abort();}}
case 5:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->wincap2;
default:abort();}}
case 6:{struct attribs*p=at;switch(field){
case 0:return (void*)&p->a;
default:abort();}}
case 7:{struct obj*p=at;switch(field){
case 0:return (void*)&p->nobj;
case 1:return (void*)&p->v;
case 2:return (void*)&p->otyp;
case 3:return (void*)&p->quan;
case 4:return (void*)&p->spe;
case 5:return (void*)&p->oclass;
case 8:return (void*)&p->corpsenm;
case 9:return (void*)&p->owornmask;
default:abort();}}
case 8:{struct objclass*p=at;switch(field){
case 1:return (void*)&p->oc_subtyp;
default:abort();}}
case 9:{struct attack*p=at;switch(field){
case 0:return (void*)&p->aatyp;
case 1:return (void*)&p->adtyp;
case 2:return (void*)&p->damn;
case 3:return (void*)&p->damd;
default:abort();}}
case 10:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->mlet;
case 1:return (void*)&p->mlevel;
case 2:return (void*)&p->geno;
case 3:return (void*)&p->mattk;
case 4:return (void*)&p->msound;
case 5:return (void*)&p->msize;
case 6:return (void*)&p->mresists;
case 7:return (void*)&p->mflags1;
case 8:return (void*)&p->mflags2;
case 9:return (void*)&p->mflags3;
default:abort();}}
case 11:{struct warntype_info*p=at;switch(field){
case 0:return (void*)&p->polyd;
case 1:return (void*)&p->species;
case 2:return (void*)&p->speciesidx;
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->blocked;
case 2:return (void*)&p->intrinsic;
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:return (void*)&p->nmon;
case 1:return (void*)&p->data;
case 2:return (void*)&p->m_id;
case 3:return (void*)&p->mnum;
case 4:return (void*)&p->cham;
case 5:return (void*)&p->m_lev;
case 6:return (void*)&p->mx;
case 7:return (void*)&p->my;
case 8:return (void*)&p->mhp;
case 9:return (void*)&p->mappearance;
case 10:return (void*)&p->m_ap_type;
case 11:return (void*)&p->mtame;
case 20:return (void*)&p->minvent;
default:abort();}}
case 14:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
default:abort();}}
case 15:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->warntype;
default:abort();}}
case 16:{struct rm*p=at;switch(field){
case 0:return (void*)&p->typ;
default:abort();}}
case 17:{struct u_conduct*p=at;switch(field){
case 0:return (void*)&p->polyselfs;
default:abort();}}
case 18:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_thats_enough_tries;
case 1:return (void*)&p->c_shudder_for_moment;
case 2:return (void*)&p->c_Never_mind;
case 3:return (void*)&p->c_the_your;
default:abort();}}
case 19:{struct Role*p=at;switch(field){
case 0:return (void*)&p->name;
case 1:return (void*)&p->mnum;
default:abort();}}
case 20:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_water_level;
case 1:return (void*)&p->d_air_level;
case 2:return (void*)&p->d_astral_level;
default:abort();}}
case 21:{struct Race*p=at;switch(field){
case 0:return (void*)&p->noun;
case 1:return (void*)&p->adj;
case 2:return (void*)&p->individual;
case 3:return (void*)&p->mnum;
case 4:return (void*)&p->selfmask;
case 5:return (void*)&p->attrmax;
default:abort();}}
case 22:{struct Gender*p=at;switch(field){
case 0:return (void*)&p->adj;
default:abort();}}
case 23:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 24:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->dx;
case 3:return (void*)&p->dy;
case 4:return (void*)&p->dz;
case 5:return (void*)&p->uz;
case 6:return (void*)&p->ulevel;
case 7:return (void*)&p->ulevelmax;
case 8:return (void*)&p->utrap;
case 9:return (void*)&p->utraptype;
case 10:return (void*)&p->uhunger;
case 11:return (void*)&p->uprops;
case 12:return (void*)&p->umonster;
case 13:return (void*)&p->umonnum;
case 14:return (void*)&p->mh;
case 15:return (void*)&p->mhmax;
case 16:return (void*)&p->mtimedone;
case 17:return (void*)&p->macurr;
case 18:return (void*)&p->mamax;
case 19:return (void*)&p->ulycn;
case 24:return (void*)&p->uconduct;
case 25:return (void*)&p->acurr;
case 26:return (void*)&p->amax;
case 27:return (void*)&p->uhp;
case 28:return (void*)&p->uhpmax;
case 29:return (void*)&p->uen;
case 30:return (void*)&p->uenmax;
case 31:return (void*)&p->uhpinc;
case 32:return (void*)&p->ueninc;
case 33:return (void*)&p->uexp;
case 34:return (void*)&p->ustuck;
case 35:return (void*)&p->usteed;
case 36:return (void*)&p->twoweap;
case 37:return (void*)&p->mcham;
default:abort();}}
case 25:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->multi;
case 1:return (void*)&p->multi_reason;
default:abort();}}
case 26:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->locations;
case 1:return (void*)&p->objects;
case 2:return (void*)&p->monlist;
default:abort();}}
case 27:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->nomovemsg;
default:abort();}}
case 28:{struct kinfo*p=at;switch(field){
case 0:return (void*)&p->format;
case 1:return (void*)&p->name;
default:abort();}}
case 29:{struct mvitals*p=at;switch(field){
case 0:return (void*)&p->mvflags;
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->sex_change_ok;
default:abort();}}
case 31:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->restoring;
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
case 1:return (void*)&p->urace;
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->viz_array;
case 1:return (void*)&p->vision_full_recalc;
default:abort();}}
case 34:{struct instance_globals_w*p=at;switch(field){
case 0:return (void*)&p->were_changes;
default:abort();}}
case 35:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 36:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
default:abort();}}
case 38:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (void*)&p->killer;
default:abort();}}
case 39:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
default:abort();}}
case 40:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->mvitals;
default:abort();}}
case 41:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (void*)&p->pl_character;
default:abort();}}
default:abort();}}
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"POLYSELF d_level.dnum width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"POLYSELF d_level.dlevel width/sign");
_Static_assert(sizeof(((struct flag*)0)->confirm)==1 && (((__typeof__(((struct flag*)0)->confirm))-1<0)==1),"POLYSELF flag.confirm width/sign");
_Static_assert(sizeof(((struct flag*)0)->debug)==1 && (((__typeof__(((struct flag*)0)->debug))-1<0)==1),"POLYSELF flag.debug width/sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1 && (((__typeof__(((struct flag*)0)->female))-1<0)==1),"POLYSELF flag.female width/sign");
_Static_assert(sizeof(((struct flag*)0)->safe_dog)==1 && (((__typeof__(((struct flag*)0)->safe_dog))-1<0)==1),"POLYSELF flag.safe_dog width/sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1 && (((__typeof__(((struct flag*)0)->verbose))-1<0)==1),"POLYSELF flag.verbose width/sign");
_Static_assert(sizeof(((struct window_procs*)0)->wincap2)==8 && (((__typeof__(((struct window_procs*)0)->wincap2))-1<0)==0),"POLYSELF window_procs.wincap2 width/sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"POLYSELF obj.otyp width/sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"POLYSELF obj.quan width/sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1 && (((__typeof__(((struct obj*)0)->spe))-1<0)==1),"POLYSELF obj.spe width/sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1 && (((__typeof__(((struct obj*)0)->oclass))-1<0)==1),"POLYSELF obj.oclass width/sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4 && (((__typeof__(((struct obj*)0)->corpsenm))-1<0)==1),"POLYSELF obj.corpsenm width/sign");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8 && (((__typeof__(((struct obj*)0)->owornmask))-1<0)==1),"POLYSELF obj.owornmask width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1 && (((__typeof__(((struct objclass*)0)->oc_subtyp))-1<0)==1),"POLYSELF objclass.oc_subtyp width/sign");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1 && (((__typeof__(((struct attack*)0)->aatyp))-1<0)==0),"POLYSELF attack.aatyp width/sign");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1 && (((__typeof__(((struct attack*)0)->adtyp))-1<0)==0),"POLYSELF attack.adtyp width/sign");
_Static_assert(sizeof(((struct attack*)0)->damn)==1 && (((__typeof__(((struct attack*)0)->damn))-1<0)==0),"POLYSELF attack.damn width/sign");
_Static_assert(sizeof(((struct attack*)0)->damd)==1 && (((__typeof__(((struct attack*)0)->damd))-1<0)==0),"POLYSELF attack.damd width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"POLYSELF permonst.mlet width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1 && (((__typeof__(((struct permonst*)0)->mlevel))-1<0)==1),"POLYSELF permonst.mlevel width/sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2 && (((__typeof__(((struct permonst*)0)->geno))-1<0)==0),"POLYSELF permonst.geno width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1 && (((__typeof__(((struct permonst*)0)->msound))-1<0)==0),"POLYSELF permonst.msound width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1 && (((__typeof__(((struct permonst*)0)->msize))-1<0)==0),"POLYSELF permonst.msize width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mresists)==1 && (((__typeof__(((struct permonst*)0)->mresists))-1<0)==0),"POLYSELF permonst.mresists width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"POLYSELF permonst.mflags1 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8 && (((__typeof__(((struct permonst*)0)->mflags2))-1<0)==0),"POLYSELF permonst.mflags2 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags3)==2 && (((__typeof__(((struct permonst*)0)->mflags3))-1<0)==0),"POLYSELF permonst.mflags3 width/sign");
_Static_assert(sizeof(((struct warntype_info*)0)->polyd)==8 && (((__typeof__(((struct warntype_info*)0)->polyd))-1<0)==0),"POLYSELF warntype_info.polyd width/sign");
_Static_assert(sizeof(((struct warntype_info*)0)->speciesidx)==2 && (((__typeof__(((struct warntype_info*)0)->speciesidx))-1<0)==1),"POLYSELF warntype_info.speciesidx width/sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"POLYSELF prop.extrinsic width/sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"POLYSELF prop.blocked width/sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"POLYSELF prop.intrinsic width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4 && (((__typeof__(((struct monst*)0)->m_id))-1<0)==0),"POLYSELF monst.m_id width/sign");
_Static_assert(sizeof(((struct monst*)0)->mnum)==2 && (((__typeof__(((struct monst*)0)->mnum))-1<0)==1),"POLYSELF monst.mnum width/sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2 && (((__typeof__(((struct monst*)0)->cham))-1<0)==1),"POLYSELF monst.cham width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1 && (((__typeof__(((struct monst*)0)->m_lev))-1<0)==0),"POLYSELF monst.m_lev width/sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"POLYSELF monst.mx width/sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"POLYSELF monst.my width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"POLYSELF monst.mhp width/sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4 && (((__typeof__(((struct monst*)0)->mappearance))-1<0)==0),"POLYSELF monst.mappearance width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"POLYSELF monst.m_ap_type width/sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"POLYSELF monst.mtame width/sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1 && (((__typeof__(((struct display_hints*)0)->botl))-1<0)==1),"POLYSELF display_hints.botl width/sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"POLYSELF rm.typ width/sign");
_Static_assert(sizeof(((struct u_conduct*)0)->polyselfs)==8 && (((__typeof__(((struct u_conduct*)0)->polyselfs))-1<0)==1),"POLYSELF u_conduct.polyselfs width/sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2 && (((__typeof__(((struct Role*)0)->mnum))-1<0)==1),"POLYSELF Role.mnum width/sign");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2 && (((__typeof__(((struct Race*)0)->mnum))-1<0)==1),"POLYSELF Race.mnum width/sign");
_Static_assert(sizeof(((struct Race*)0)->selfmask)==2 && (((__typeof__(((struct Race*)0)->selfmask))-1<0)==1),"POLYSELF Race.selfmask width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"POLYSELF you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"POLYSELF you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->dx)==4 && (((__typeof__(((struct you*)0)->dx))-1<0)==1),"POLYSELF you.dx width/sign");
_Static_assert(sizeof(((struct you*)0)->dy)==4 && (((__typeof__(((struct you*)0)->dy))-1<0)==1),"POLYSELF you.dy width/sign");
_Static_assert(sizeof(((struct you*)0)->dz)==4 && (((__typeof__(((struct you*)0)->dz))-1<0)==1),"POLYSELF you.dz width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4 && (((__typeof__(((struct you*)0)->ulevel))-1<0)==1),"POLYSELF you.ulevel width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevelmax)==4 && (((__typeof__(((struct you*)0)->ulevelmax))-1<0)==1),"POLYSELF you.ulevelmax width/sign");
_Static_assert(sizeof(((struct you*)0)->utrap)==4 && (((__typeof__(((struct you*)0)->utrap))-1<0)==0),"POLYSELF you.utrap width/sign");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4 && (((__typeof__(((struct you*)0)->utraptype))-1<0)==0),"POLYSELF you.utraptype width/sign");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4 && (((__typeof__(((struct you*)0)->uhunger))-1<0)==1),"POLYSELF you.uhunger width/sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"POLYSELF you.umonster width/sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"POLYSELF you.umonnum width/sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4 && (((__typeof__(((struct you*)0)->mh))-1<0)==1),"POLYSELF you.mh width/sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4 && (((__typeof__(((struct you*)0)->mhmax))-1<0)==1),"POLYSELF you.mhmax width/sign");
_Static_assert(sizeof(((struct you*)0)->mtimedone)==4 && (((__typeof__(((struct you*)0)->mtimedone))-1<0)==1),"POLYSELF you.mtimedone width/sign");
_Static_assert(sizeof(((struct you*)0)->ulycn)==4 && (((__typeof__(((struct you*)0)->ulycn))-1<0)==1),"POLYSELF you.ulycn width/sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4 && (((__typeof__(((struct you*)0)->uhp))-1<0)==1),"POLYSELF you.uhp width/sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4 && (((__typeof__(((struct you*)0)->uhpmax))-1<0)==1),"POLYSELF you.uhpmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uen)==4 && (((__typeof__(((struct you*)0)->uen))-1<0)==1),"POLYSELF you.uen width/sign");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4 && (((__typeof__(((struct you*)0)->uenmax))-1<0)==1),"POLYSELF you.uenmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uexp)==8 && (((__typeof__(((struct you*)0)->uexp))-1<0)==1),"POLYSELF you.uexp width/sign");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1 && (((__typeof__(((struct you*)0)->twoweap))-1<0)==1),"POLYSELF you.twoweap width/sign");
_Static_assert(sizeof(((struct you*)0)->mcham)==2 && (((__typeof__(((struct you*)0)->mcham))-1<0)==1),"POLYSELF you.mcham width/sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8 && (((__typeof__(((struct instance_globals_m*)0)->multi))-1<0)==1),"POLYSELF instance_globals_m.multi width/sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4 && (((__typeof__(((struct kinfo*)0)->format))-1<0)==1),"POLYSELF kinfo.format width/sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1 && (((__typeof__(((struct mvitals*)0)->mvflags))-1<0)==0),"POLYSELF mvitals.mvflags width/sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->sex_change_ok)==4 && (((__typeof__(((struct instance_globals_s*)0)->sex_change_ok))-1<0)==1),"POLYSELF instance_globals_s.sex_change_ok width/sign");
_Static_assert(sizeof(((struct sinfo*)0)->restoring)==4 && (((__typeof__(((struct sinfo*)0)->restoring))-1<0)==1),"POLYSELF sinfo.restoring width/sign");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vision_full_recalc)==1 && (((__typeof__(((struct instance_globals_v*)0)->vision_full_recalc))-1<0)==1),"POLYSELF instance_globals_v.vision_full_recalc width/sign");
_Static_assert(sizeof(((struct instance_globals_w*)0)->were_changes)==8 && (((__typeof__(((struct instance_globals_w*)0)->were_changes))-1<0)==1),"POLYSELF instance_globals_w.were_changes width/sign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Armor_gone),int (*)(void)),"POLYSELF dependency Armor_gone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Blindf_off),void (*)(struct obj *)),"POLYSELF dependency Blindf_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Boots_off),int (*)(void)),"POLYSELF dependency Boots_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Cloak_off),int (*)(void)),"POLYSELF dependency Cloak_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Gloves_off),int (*)(void)),"POLYSELF dependency Gloves_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Helmet_off),int (*)(void)),"POLYSELF dependency Helmet_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Mgender),int (*)(struct monst *)),"POLYSELF dependency Mgender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Monnam),char * (*)(struct monst *)),"POLYSELF dependency Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&On_stairs),signed char (*)(coordxy,coordxy)),"POLYSELF dependency On_stairs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Resists_Elem),signed char (*)(struct monst *,int)),"POLYSELF dependency Resists_Elem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Shield_off),int (*)(void)),"POLYSELF dependency Shield_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Some_Monnam),char * (*)(struct monst *)),"POLYSELF dependency Some_Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&abs),int (*)(int)),"POLYSELF dependency abs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&acurr),signed char (*)(int)),"POLYSELF dependency acurr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_damage),void (*)(coordxy,coordxy,long)),"POLYSELF dependency add_damage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&adjabil),void (*)(int,int)),"POLYSELF dependency adjabil");
_Static_assert(__builtin_types_compatible_p(__typeof__(&an),char * (*)(const char *)),"POLYSELF dependency an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&arti_light_radius),int (*)(struct obj *)),"POLYSELF dependency arti_light_radius");
_Static_assert(__builtin_types_compatible_p(__typeof__(&artifact_light),signed char (*)(struct obj *)),"POLYSELF dependency artifact_light");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype),signed char (*)(struct permonst *,int)),"POLYSELF dependency attacktype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype_fordmg),struct attack * (*)(struct permonst *,int,int)),"POLYSELF dependency attacktype_fordmg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&breakarm),signed char (*)(struct permonst *)),"POLYSELF dependency breakarm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&buried_ball_to_freedom),void (*)(void)),"POLYSELF dependency buried_ball_to_freedom");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bury_objs),void (*)(int,int)),"POLYSELF dependency bury_objs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_be_strangled),signed char (*)(struct monst *)),"POLYSELF dependency can_be_strangled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_ride),signed char (*)(struct monst *)),"POLYSELF dependency can_ride");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cancel_don),void (*)(void)),"POLYSELF dependency cancel_don");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canletgo),signed char (*)(struct obj *,const char *)),"POLYSELF dependency canletgo");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"POLYSELF dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&character_race),const struct Race * (*)(short)),"POLYSELF dependency character_race");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cloak_simple_name),const char * (*)(struct obj *)),"POLYSELF dependency cloak_simple_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&counter_were),int (*)(int)),"POLYSELF dependency counter_were");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cxname),char * (*)(struct obj *)),"POLYSELF dependency cxname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dealloc_killer),void (*)(struct kinfo *)),"POLYSELF dependency dealloc_killer");
_Static_assert(__builtin_types_compatible_p(__typeof__(&defended),signed char (*)(struct monst *,int)),"POLYSELF dependency defended");
_Static_assert(__builtin_types_compatible_p(__typeof__(&del_light_source),void (*)(int,union any *)),"POLYSELF dependency del_light_source");
_Static_assert(__builtin_types_compatible_p(__typeof__(&deltrap),void (*)(struct trap *)),"POLYSELF dependency deltrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&destroy_items),int (*)(struct monst *,int,int)),"POLYSELF dependency destroy_items");
_Static_assert(__builtin_types_compatible_p(__typeof__(&discover_object),void (*)(int,boolean,boolean,boolean)),"POLYSELF dependency discover_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dismount_steed),void (*)(int)),"POLYSELF dependency dismount_steed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy,coordxy,coordxy,coordxy)),"POLYSELF dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype),signed char (*)(struct permonst *,int)),"POLYSELF dependency dmgtype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype_fromattack),struct attack * (*)(struct permonst *,int,int)),"POLYSELF dependency dmgtype_fromattack");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done),void (*)(int)),"POLYSELF dependency done");
_Static_assert(__builtin_types_compatible_p(__typeof__(&donning),signed char (*)(struct obj *)),"POLYSELF dependency donning");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dotrap),void (*)(struct trap *,unsigned int)),"POLYSELF dependency dotrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dropx),void (*)(struct obj *)),"POLYSELF dependency dropx");
_Static_assert(__builtin_types_compatible_p(__typeof__(&egg_type_from_parent),int (*)(int,boolean)),"POLYSELF dependency egg_type_from_parent");
_Static_assert(__builtin_types_compatible_p(__typeof__(&encumber_msg),void (*)(void)),"POLYSELF dependency encumber_msg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&end_burn),void (*)(struct obj *,boolean)),"POLYSELF dependency end_burn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exercise),void (*)(int,boolean)),"POLYSELF dependency exercise");
_Static_assert(__builtin_types_compatible_p(__typeof__(&expels),void (*)(struct monst *,struct permonst *,boolean)),"POLYSELF dependency expels");
_Static_assert(__builtin_types_compatible_p(__typeof__(&feeltrap),void (*)(struct trap *)),"POLYSELF dependency feeltrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_ac),void (*)(void)),"POLYSELF dependency find_ac");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_delayed_killer),struct kinfo * (*)(int)),"POLYSELF dependency find_delayed_killer");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getdir),int (*)(const char *)),"POLYSELF dependency getdir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getlin),void (*)(const char *,char *)),"POLYSELF dependency getlin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&golemhp),int (*)(int)),"POLYSELF dependency golemhp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&has_ceiling),signed char (*)(d_level *)),"POLYSELF dependency has_ceiling");
_Static_assert(__builtin_types_compatible_p(__typeof__(&helm_simple_name),const char * (*)(struct obj *)),"POLYSELF dependency helm_simple_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hideunder),signed char (*)(struct monst *)),"POLYSELF dependency hideunder");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hliquid),const char * (*)(const char *)),"POLYSELF dependency hliquid");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ignite_items),void (*)(struct obj *)),"POLYSELF dependency ignite_items");
_Static_assert(__builtin_types_compatible_p(__typeof__(&in_rooms),char * (*)(coordxy,coordxy,int)),"POLYSELF dependency in_rooms");
_Static_assert(__builtin_types_compatible_p(__typeof__(&instapetrify),void (*)(const char *)),"POLYSELF dependency instapetrify");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_fainted),signed char (*)(void)),"POLYSELF dependency is_fainted");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_home_elemental),signed char (*)(struct permonst *)),"POLYSELF dependency is_home_elemental");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool),signed char (*)(coordxy,coordxy)),"POLYSELF dependency is_pool");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool_or_lava),signed char (*)(coordxy,coordxy)),"POLYSELF dependency is_pool_or_lava");
_Static_assert(__builtin_types_compatible_p(__typeof__(&killed),void (*)(struct monst *)),"POLYSELF dependency killed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&l_monnam),char * (*)(struct monst *)),"POLYSELF dependency l_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&learn_egg_type),void (*)(int)),"POLYSELF dependency learn_egg_type");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losehp),void (*)(int,const char *,schar)),"POLYSELF dependency losehp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_blinded),void (*)(long,boolean)),"POLYSELF dependency make_blinded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_glib),void (*)(int)),"POLYSELF dependency make_glib");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_sick),void (*)(long,const char *,boolean,int)),"POLYSELF dependency make_sick");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_slimed),void (*)(long,const char *)),"POLYSELF dependency make_slimed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_stoned),void (*)(long,const char *,int,const char *)),"POLYSELF dependency make_stoned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makeplural),char * (*)(const char *)),"POLYSELF dependency makeplural");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maketrap),struct trap * (*)(coordxy,coordxy,int)),"POLYSELF dependency maketrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&max_rank_sz),void (*)(void)),"POLYSELF dependency max_rank_sz");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maybe_adjust_light),void (*)(struct obj *,int)),"POLYSELF dependency maybe_adjust_light");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mkclass_poly),int (*)(int)),"POLYSELF dependency mkclass_poly");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mksobj),struct obj * (*)(int,boolean,boolean)),"POLYSELF dependency mksobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_nam),char * (*)(struct monst *)),"POLYSELF dependency mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monst_to_any),anything * (*)(struct monst *)),"POLYSELF dependency monst_to_any");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mungspaces),char * (*)(char *)),"POLYSELF dependency mungspaces");
_Static_assert(__builtin_types_compatible_p(__typeof__(&name_to_mon),int (*)(const char *,int *)),"POLYSELF dependency name_to_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&name_to_monclass),int (*)(const char *,int *)),"POLYSELF dependency name_to_monclass");
_Static_assert(__builtin_types_compatible_p(__typeof__(&new_light_source),void (*)(coordxy,coordxy,int,int,union any *)),"POLYSELF dependency new_light_source");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newhp),int (*)(void)),"POLYSELF dependency newhp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newpw),int (*)(void)),"POLYSELF dependency newpw");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy,coordxy)),"POLYSELF dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newuhs),void (*)(boolean)),"POLYSELF dependency newuhs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nomul),void (*)(int)),"POLYSELF dependency nomul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&num_horns),int (*)(struct permonst *)),"POLYSELF dependency num_horns");
_Static_assert(__builtin_types_compatible_p(__typeof__(&observe_object),void (*)(struct obj *)),"POLYSELF dependency observe_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),signed char (*)(d_level *,d_level *)),"POLYSELF dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&otense),char * (*)(struct obj *,const char *)),"POLYSELF dependency otense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pmname),const char * (*)(struct permonst *,int)),"POLYSELF dependency pmname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&poly_when_stoned),signed char (*)(struct permonst *)),"POLYSELF dependency poly_when_stoned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&racial_exception),int (*)(struct monst *,struct obj *)),"POLYSELF dependency racial_exception");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rank_of),const char * (*)(int,short,boolean)),"POLYSELF dependency rank_of");
_Static_assert(__builtin_types_compatible_p(__typeof__(&redist_attr),void (*)(void)),"POLYSELF dependency redist_attr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reset_utrap),void (*)(boolean)),"POLYSELF dependency reset_utrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resists_drli),signed char (*)(struct monst *)),"POLYSELF dependency resists_drli");
_Static_assert(__builtin_types_compatible_p(__typeof__(&retouch_equipment),void (*)(int)),"POLYSELF dependency retouch_equipment");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rndexp),long (*)(boolean)),"POLYSELF dependency rndexp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rounddiv),int (*)(long,int)),"POLYSELF dependency rounddiv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&s_suffix),char * (*)(const char *)),"POLYSELF dependency s_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&see_monsters),void (*)(void)),"POLYSELF dependency see_monsters");
_Static_assert(__builtin_types_compatible_p(__typeof__(&selftouch),void (*)(const char *)),"POLYSELF dependency selftouch");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"POLYSELF dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_itimeout),void (*)(long *,long)),"POLYSELF dependency set_itimeout");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_mimic_blocking),void (*)(void)),"POLYSELF dependency set_mimic_blocking");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_mon_data),void (*)(struct monst *,struct permonst *)),"POLYSELF dependency set_mon_data");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_ustuck),void (*)(struct monst *)),"POLYSELF dependency set_ustuck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_utrap),void (*)(unsigned int,unsigned int)),"POLYSELF dependency set_utrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setmangry),void (*)(struct monst *,boolean)),"POLYSELF dependency setmangry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setuhpmax),void (*)(int,boolean)),"POLYSELF dependency setuhpmax");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setworn),void (*)(struct obj *,long)),"POLYSELF dependency setworn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&simpleonames),char * (*)(struct obj *)),"POLYSELF dependency simpleonames");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sliparm),signed char (*)(struct permonst *)),"POLYSELF dependency sliparm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spoteffects),void (*)(boolean)),"POLYSELF dependency spoteffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&status_initialize),void (*)(boolean)),"POLYSELF dependency status_initialize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sticks),signed char (*)(struct permonst *)),"POLYSELF dependency sticks");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcat),char * (*)(char *restrict,const char *restrict)),"POLYSELF dependency strcat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strchr),char * (*)(const char *,int)),"POLYSELF dependency strchr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *,const char *)),"POLYSELF dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char * (*)(char *restrict,const char *restrict)),"POLYSELF dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmp),int (*)(const char *,const char *,size_t)),"POLYSELF dependency strncmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strstri),char * (*)(const char *,const char *)),"POLYSELF dependency strstri");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strsubst),char * (*)(char *,const char *,const char *)),"POLYSELF dependency strsubst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&surface),const char * (*)(coordxy,coordxy)),"POLYSELF dependency surface");
_Static_assert(__builtin_types_compatible_p(__typeof__(&t_at),struct trap * (*)(coordxy,coordxy)),"POLYSELF dependency t_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&the),char * (*)(const char *)),"POLYSELF dependency the");
_Static_assert(__builtin_types_compatible_p(__typeof__(&the_unique_pm),signed char (*)(struct permonst *)),"POLYSELF dependency the_unique_pm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&throwit),void (*)(struct obj *,long,boolean,struct obj *)),"POLYSELF dependency throwit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ubreatheu),void (*)(struct attack *)),"POLYSELF dependency ubreatheu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ubuzz),void (*)(int,int)),"POLYSELF dependency ubuzz");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unconscious),signed char (*)(void)),"POLYSELF dependency unconscious");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unmul),void (*)(const char *)),"POLYSELF dependency unmul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unpunish),void (*)(void)),"POLYSELF dependency unpunish");
_Static_assert(__builtin_types_compatible_p(__typeof__(&untwoweapon),void (*)(void)),"POLYSELF dependency untwoweapon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&update_inventory),void (*)(void)),"POLYSELF dependency update_inventory");
_Static_assert(__builtin_types_compatible_p(__typeof__(&useup),void (*)(struct obj *)),"POLYSELF dependency useup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&uswapwepgone),void (*)(void)),"POLYSELF dependency uswapwepgone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&uwepgone),void (*)(void)),"POLYSELF dependency uwepgone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&valid_vampshiftform),signed char (*)(int,int)),"POLYSELF dependency valid_vampshiftform");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vtense),char * (*)(const char *,const char *)),"POLYSELF dependency vtense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wakeup),void (*)(struct monst *,boolean)),"POLYSELF dependency wakeup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&weapon_descr),const char * (*)(struct obj *)),"POLYSELF dependency weapon_descr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&were_beastie),int (*)(int)),"POLYSELF dependency were_beastie");
_Static_assert(__builtin_types_compatible_p(__typeof__(&were_summon),int (*)(struct permonst *,boolean,int *,char *)),"POLYSELF dependency were_summon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&y_monnam),char * (*)(struct monst *)),"POLYSELF dependency y_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yn_function),char (*)(const char *,const char *,char,boolean)),"POLYSELF dependency yn_function");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yname),char * (*)(struct obj *)),"POLYSELF dependency yname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&youhiding),void (*)(boolean,int)),"POLYSELF dependency youhiding");
static char polyself_literals[POLYSELF_LITERAL_CAPACITY];
char*teleport_polyself_literal_storage(void){return polyself_literals;}
size_t teleport_polyself_literal_capacity(void){return sizeof polyself_literals;}
void teleport_polyself_rng_caller(int site){if(site<0||site>=POLYSELF_RNG_COUNT)abort();if(rng_log_enabled())rng_log_set_caller(POLYSELF_SOURCE_FILE,polyself_rng_lines[site],polyself_rng_functions[site]);}
int teleport_polyself_rn2_value(int n){return (rn2)(n);}
int teleport_polyself_rnd_value(int n){return (rnd)(n);}
int teleport_polyself_rnl_value(int n){return (rnl)(n);}
int teleport_polyself_d_value(int n,int x){return (d)(n,x);}
/* These wrappers intentionally forward the exact original variable format; no extra argument is introduced. */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
void teleport_polyself_Your_pppp(const char * a0,char * a1,char * a2,char * a3){(Your)(a0,a1,a2,a3);}
void teleport_polyself_You_p(const char * a0){(You)(a0);}
void teleport_polyself_urgent_pline_pp(const char * a0,const char * a1){(urgent_pline)(a0,a1);}
int teleport_polyself_sprintf_pppp(char * a0,const char * a1,const char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_polyself_livelog_printf_lppp(long a0,const char * a1,char * a2,char * a3){(livelog_printf)(a0,a1,a2,a3);}
void teleport_polyself_urgent_pline_p(const char * a0){(urgent_pline)(a0);}
void teleport_polyself_livelog_printf_lpip(long a0,const char * a1,int a2,const char * a3){(livelog_printf)(a0,a1,a2,a3);}
void teleport_polyself_Your_p(const char * a0){(Your)(a0);}
void teleport_polyself_You_pp(const char * a0,char * a1){(You)(a0,a1);}
void teleport_polyself_pline_pp(const char * a0,char * a1){(pline)(a0,a1);}
void teleport_polyself_pline_p(const char * a0){(pline)(a0);}
void teleport_polyself_You_cant_p(const char * a0){(You_cant)(a0);}
void teleport_polyself_You_cant_pp(const char * a0,char * a1){(You_cant)(a0,a1);}
void teleport_polyself_Your_pp(const char * a0,char * a1){(Your)(a0,a1);}
int teleport_polyself_sprintf_ppp(char * a0,const char * a1,const char * a2){return (sprintf)(a0,a1,a2);}
void teleport_polyself_You_feel_pp(const char * a0,const char * a1){(You_feel)(a0,a1);}
void teleport_polyself_livelog_printf_lpp(long a0,const char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_polyself_You_ppp(const char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_polyself_pline_ppp(const char * a0,const char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_polyself_pline_The_p(const char * a0){(pline_The)(a0);}
void teleport_polyself_pline_The_pp(const char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_polyself_Your_ppp(const char * a0,char * a1,char * a2){(Your)(a0,a1,a2);}
void teleport_polyself_You_pppp(const char * a0,const char * a1,const char * a2,const char * a3){(You)(a0,a1,a2,a3);}
void teleport_polyself_impossible_p(const char * a0){(impossible)(a0);}
void teleport_polyself_impossible_pi(const char * a0,int a1){(impossible)(a0,a1);}
void teleport_polyself_There_pp(const char * a0,const char * a1){(There)(a0,a1);}
void teleport_polyself_There_p(const char * a0){(There)(a0);}
#pragma clang diagnostic pop
