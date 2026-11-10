/* MHITU typed native field/global/literal/dependency transport only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "mhitu-source-data.h"
extern const struct attack c_sa_no[NATTK];
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4,"MHITU memory64 ABI");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0,"MHITU signed boolean");
_Static_assert(sizeof(coordxy)==2&&(coordxy)-1<0,"MHITU signed coordxy");
void*teleport_mhitu_global(int i){switch(i){
case 0:return (void*)&gy;
case 1:return (void*)&u;
case 2:return (void*)&gh;
case 3:return (void*)&flags;
case 4:return (void*)&objects;
case 5:return (void*)&genders;
case 6:return (void*)&uwep;
case 7:return (void*)&gv;
case 8:return (void*)&disp;
case 9:return (void*)&mons;
case 10:return (void*)&sysopt;
case 11:return (void*)&gb;
case 12:return (void*)&gn;
case 13:return (void*)&svl;
case 14:return (void*)&svp;
case 15:return (void*)&c_common_strings;
case 16:return (void*)&gm;
case 17:return (void*)&gs;
case 18:return (void*)&svd;
case 19:return (void*)&svm;
case 20:return (void*)&uarmc;
case 21:return (void*)&uarm;
case 22:return (void*)&uarmu;
case 23:return (void*)&uarmh;
case 24:return (void*)&gi;
case 25:return (void*)&gu;
case 26:return (void*)&uball;
case 27:return (void*)&windowprocs;
case 28:return (void*)&WIN_MESSAGE;
case 29:return (void*)&uchain;
case 30:return (void*)&svk;
case 31:return (void*)&uarmg;
case 32:return (void*)&ynchars;
case 33:return (void*)&uleft;
case 34:return (void*)&uright;
case 35:return (void*)&uarmf;
case 36:return (void*)&uarms;
case 37:return (void*)&c_sa_no;
default:abort();}}
uint64_t teleport_mhitu_read(int kind,void*at,int field){switch(kind){
case 0:{struct sysopt_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->seduce);
default:abort();}}
case 1:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 2:{struct align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 3:{struct nhcoord*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->x);
case 1:return (uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 4:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->female);
case 1:return (uint64_t)(uintptr_t)(p->verbose);
default:abort();}}
case 5:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ttyp);
default:abort();}}
case 6:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->win_display_nhwindow);
default:abort();}}
case 7:{struct attribs*p=at;switch(field){
default:abort();}}
case 8:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nobj);
case 1:return (uint64_t)(uintptr_t)(p->ox);
case 2:return (uint64_t)(uintptr_t)(p->oy);
case 3:return (uint64_t)(uintptr_t)(p->otyp);
case 4:return (uint64_t)(uintptr_t)(p->quan);
case 5:return (uint64_t)(uintptr_t)(p->spe);
case 6:return (uint64_t)(uintptr_t)(p->oclass);
case 7:return (uint64_t)(uintptr_t)(p->where);
case 8:return (uint64_t)(uintptr_t)(p->cursed);
case 9:return (uint64_t)(uintptr_t)(p->dknown);
case 10:return (uint64_t)(uintptr_t)(p->otrapped);
case 11:return (uint64_t)(uintptr_t)(p->greased);
case 12:return (uint64_t)(uintptr_t)(p->corpsenm);
case 13:return (uint64_t)(uintptr_t)(p->owornmask);
default:abort();}}
case 9:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_name_known);
case 1:return (uint64_t)(uintptr_t)(p->oc_dir);
case 2:return (uint64_t)(uintptr_t)(p->oc_subtyp);
case 3:return (uint64_t)(uintptr_t)(p->oc_oc2);
default:abort();}}
case 10:{struct attack*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->aatyp);
case 1:return (uint64_t)(uintptr_t)(p->adtyp);
case 2:return (uint64_t)(uintptr_t)(p->damn);
case 3:return (uint64_t)(uintptr_t)(p->damd);
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->pmnames);
case 1:return (uint64_t)(uintptr_t)(p->pmidx);
case 2:return (uint64_t)(uintptr_t)(p->mlet);
case 3:return (uint64_t)(uintptr_t)(p->mlevel);
case 4:return (uint64_t)(uintptr_t)(&p->mattk);
case 5:return (uint64_t)(uintptr_t)(p->msize);
case 6:return (uint64_t)(uintptr_t)(p->mflags1);
case 7:return (uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->blocked);
case 2:return (uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
case 1:return (uint64_t)(uintptr_t)(p->m_id);
case 2:return (uint64_t)(uintptr_t)(p->cham);
case 3:return (uint64_t)(uintptr_t)(p->m_lev);
case 4:return (uint64_t)(uintptr_t)(p->mx);
case 5:return (uint64_t)(uintptr_t)(p->my);
case 6:return (uint64_t)(uintptr_t)(p->mux);
case 7:return (uint64_t)(uintptr_t)(p->muy);
case 8:return (uint64_t)(uintptr_t)(p->mhp);
case 9:return (uint64_t)(uintptr_t)(p->mhpmax);
case 10:return (uint64_t)(uintptr_t)(p->mappearance);
case 11:return (uint64_t)(uintptr_t)(p->m_ap_type);
case 12:return (uint64_t)(uintptr_t)(p->mtame);
case 13:return (uint64_t)(uintptr_t)(p->seen_resistance);
case 14:return (uint64_t)(uintptr_t)(p->mspec_used);
case 15:return (uint64_t)(uintptr_t)(p->female);
case 16:return (uint64_t)(uintptr_t)(p->minvis);
case 17:return (uint64_t)(uintptr_t)(p->mcan);
case 18:return (uint64_t)(uintptr_t)(p->mundetected);
case 19:return (uint64_t)(uintptr_t)(p->mcansee);
case 20:return (uint64_t)(uintptr_t)(p->mcloned);
case 21:return (uint64_t)(uintptr_t)(p->mflee);
case 22:return (uint64_t)(uintptr_t)(p->mstun);
case 23:return (uint64_t)(uintptr_t)(p->mconf);
case 24:return (uint64_t)(uintptr_t)(p->mpeaceful);
case 25:return (uint64_t)(uintptr_t)(p->mtrapped);
case 26:return (uint64_t)(uintptr_t)(p->wormno);
case 27:return (uint64_t)(uintptr_t)(p->minvent);
case 28:return (uint64_t)(uintptr_t)(p->mw);
case 29:return (uint64_t)(uintptr_t)(p->misc_worn_check);
case 30:return (uint64_t)(uintptr_t)(p->weapon_check);
default:abort();}}
case 14:{struct mhitm_data*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->damage);
case 1:return (uint64_t)(uintptr_t)(p->hitflags);
case 2:return (uint64_t)(uintptr_t)(p->done);
case 3:return (uint64_t)(uintptr_t)(p->permdmg);
case 4:return (uint64_t)(uintptr_t)(p->specialdmg);
default:abort();}}
case 15:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 16:{struct rm*p=at;switch(field){
default:abort();}}
case 17:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->bhitpos);
default:abort();}}
case 18:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_something);
case 1:return (uint64_t)(uintptr_t)(p->c_Something);
case 2:return (uint64_t)(uintptr_t)(p->c_vision_clears);
default:abort();}}
case 19:{struct u_roleplay*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 20:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 21:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_rogue_level);
default:abort();}}
case 22:{struct instance_globals_h*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hitmsg_mid);
case 1:return (uint64_t)(uintptr_t)(p->hitmsg_prev);
default:abort();}}
case 23:{struct Gender*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->he);
case 1:return (uint64_t)(uintptr_t)(p->him);
case 2:return (uint64_t)(uintptr_t)(p->his);
default:abort();}}
case 24:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 25:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(&p->uz);
case 3:return (uint64_t)(uintptr_t)(p->utotype);
case 4:return (uint64_t)(uintptr_t)(p->ulevel);
case 5:return (uint64_t)(uintptr_t)(p->utrap);
case 6:return (uint64_t)(uintptr_t)(p->utraptype);
case 7:return (uint64_t)(uintptr_t)(&p->uprops);
case 8:return (uint64_t)(uintptr_t)(p->umonster);
case 9:return (uint64_t)(uintptr_t)(p->umonnum);
case 10:return (uint64_t)(uintptr_t)(p->mh);
case 11:return (uint64_t)(uintptr_t)(p->mhmax);
case 12:return (uint64_t)(uintptr_t)(p->uswldtim);
case 13:return (uint64_t)(uintptr_t)(p->uswallow);
case 14:return (uint64_t)(uintptr_t)(p->uinwater);
case 15:return (uint64_t)(uintptr_t)(p->uundetected);
case 16:return (uint64_t)(uintptr_t)(p->mfemale);
case 17:return (uint64_t)(uintptr_t)(p->uinvulnerable);
case 18:return (uint64_t)(uintptr_t)(&p->uroleplay);
case 19:return (uint64_t)(uintptr_t)(&p->ualign);
case 20:return (uint64_t)(uintptr_t)(p->uac);
case 21:return (uint64_t)(uintptr_t)(p->uspellprot);
case 22:return (uint64_t)(uintptr_t)(p->uhp);
case 23:return (uint64_t)(uintptr_t)(p->uhpmax);
case 24:return (uint64_t)(uintptr_t)(p->uen);
case 25:return (uint64_t)(uintptr_t)(p->uenmax);
case 26:return (uint64_t)(uintptr_t)(p->uenpeak);
case 27:return (uint64_t)(uintptr_t)(p->ublessed);
case 28:return (uint64_t)(uintptr_t)(p->usleep);
case 29:return (uint64_t)(uintptr_t)(p->ustuck);
case 30:return (uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
case 26:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->multi);
case 1:return (uint64_t)(uintptr_t)(p->mswallower);
case 2:return (uint64_t)(uintptr_t)(p->mhitu_dieroll);
default:abort();}}
case 27:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->objects);
case 1:return (uint64_t)(uintptr_t)(&p->monsters);
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nomovemsg);
case 1:return (uint64_t)(uintptr_t)(p->notonhead);
default:abort();}}
case 29:{struct kinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->format);
case 1:return (uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 31:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->stoned);
case 1:return (uint64_t)(uintptr_t)(p->skipdrin);
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 34:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 35:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 36:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 37:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 38:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
case 1:return (uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 39:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
default:abort();}}
void teleport_mhitu_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct sysopt_s*p=at;switch(field){
case 0:p->seduce=value;return;
default:abort();}}
case 1:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 2:{struct align*p=at;switch(field){
case 0:p->type=value;return;
default:abort();}}
case 3:{struct nhcoord*p=at;switch(field){
case 0:p->x=value;return;
case 1:p->y=value;return;
default:abort();}}
case 4:{struct flag*p=at;switch(field){
case 0:p->female=value;return;
case 1:p->verbose=value;return;
default:abort();}}
case 5:{struct trap*p=at;switch(field){
case 0:p->ttyp=value;return;
default:abort();}}
case 6:{struct window_procs*p=at;switch(field){
case 0:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))(uintptr_t)value;return;
default:abort();}}
case 7:{struct attribs*p=at;switch(field){
default:abort();}}
case 8:{struct obj*p=at;switch(field){
case 0:p->nobj=(void*)(uintptr_t)value;return;
case 1:p->ox=value;return;
case 2:p->oy=value;return;
case 3:p->otyp=value;return;
case 4:p->quan=value;return;
case 5:p->spe=value;return;
case 6:p->oclass=value;return;
case 7:p->where=value;return;
case 8:p->cursed=value;return;
case 9:p->dknown=value;return;
case 10:p->otrapped=value;return;
case 11:p->greased=value;return;
case 12:p->corpsenm=value;return;
case 13:p->owornmask=value;return;
default:abort();}}
case 9:{struct objclass*p=at;switch(field){
case 0:p->oc_name_known=value;return;
case 1:p->oc_dir=value;return;
case 2:p->oc_subtyp=value;return;
case 3:p->oc_oc2=value;return;
default:abort();}}
case 10:{struct attack*p=at;switch(field){
case 0:p->aatyp=value;return;
case 1:p->adtyp=value;return;
case 2:p->damn=value;return;
case 3:p->damd=value;return;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 2:p->mlet=value;return;
case 3:p->mlevel=value;return;
case 5:p->msize=value;return;
case 6:p->mflags1=value;return;
case 7:p->mflags2=value;return;
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->blocked=value;return;
case 2:p->intrinsic=value;return;
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
case 1:p->m_id=value;return;
case 2:p->cham=value;return;
case 3:p->m_lev=value;return;
case 4:p->mx=value;return;
case 5:p->my=value;return;
case 6:p->mux=value;return;
case 7:p->muy=value;return;
case 8:p->mhp=value;return;
case 9:p->mhpmax=value;return;
case 10:p->mappearance=value;return;
case 11:p->m_ap_type=value;return;
case 12:p->mtame=value;return;
case 13:p->seen_resistance=value;return;
case 14:p->mspec_used=value;return;
case 15:p->female=value;return;
case 16:p->minvis=value;return;
case 17:p->mcan=value;return;
case 18:p->mundetected=value;return;
case 19:p->mcansee=value;return;
case 20:p->mcloned=value;return;
case 21:p->mflee=value;return;
case 22:p->mstun=value;return;
case 23:p->mconf=value;return;
case 24:p->mpeaceful=value;return;
case 25:p->mtrapped=value;return;
case 26:p->wormno=value;return;
case 27:p->minvent=(void*)(uintptr_t)value;return;
case 28:p->mw=(void*)(uintptr_t)value;return;
case 29:p->misc_worn_check=value;return;
case 30:p->weapon_check=value;return;
default:abort();}}
case 14:{struct mhitm_data*p=at;switch(field){
case 0:p->damage=value;return;
case 1:p->hitflags=value;return;
case 2:p->done=value;return;
case 3:p->permdmg=value;return;
case 4:p->specialdmg=value;return;
default:abort();}}
case 15:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
default:abort();}}
case 16:{struct rm*p=at;switch(field){
default:abort();}}
case 17:{struct instance_globals_b*p=at;switch(field){
case 0:memmove(&p->bhitpos,(void*)(uintptr_t)value,sizeof p->bhitpos);return;
default:abort();}}
case 18:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 19:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=value;return;
default:abort();}}
case 20:{struct Role*p=at;switch(field){
case 0:p->mnum=value;return;
default:abort();}}
case 21:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_rogue_level,(void*)(uintptr_t)value,sizeof p->d_rogue_level);return;
default:abort();}}
case 22:{struct instance_globals_h*p=at;switch(field){
case 0:p->hitmsg_mid=value;return;
case 1:p->hitmsg_prev=(void*)(uintptr_t)value;return;
default:abort();}}
case 23:{struct Gender*p=at;switch(field){
case 0:p->he=(void*)(uintptr_t)value;return;
case 1:p->him=(void*)(uintptr_t)value;return;
case 2:p->his=(void*)(uintptr_t)value;return;
default:abort();}}
case 24:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 25:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:memmove(&p->uz,(void*)(uintptr_t)value,sizeof p->uz);return;
case 3:p->utotype=value;return;
case 4:p->ulevel=value;return;
case 5:p->utrap=value;return;
case 6:p->utraptype=value;return;
case 8:p->umonster=value;return;
case 9:p->umonnum=value;return;
case 10:p->mh=value;return;
case 11:p->mhmax=value;return;
case 12:p->uswldtim=value;return;
case 13:p->uswallow=value;return;
case 14:p->uinwater=value;return;
case 15:p->uundetected=value;return;
case 16:p->mfemale=value;return;
case 17:p->uinvulnerable=value;return;
case 18:memmove(&p->uroleplay,(void*)(uintptr_t)value,sizeof p->uroleplay);return;
case 19:memmove(&p->ualign,(void*)(uintptr_t)value,sizeof p->ualign);return;
case 20:p->uac=value;return;
case 21:p->uspellprot=value;return;
case 22:p->uhp=value;return;
case 23:p->uhpmax=value;return;
case 24:p->uen=value;return;
case 25:p->uenmax=value;return;
case 26:p->uenpeak=value;return;
case 27:p->ublessed=value;return;
case 28:p->usleep=value;return;
case 29:p->ustuck=(void*)(uintptr_t)value;return;
case 30:p->usteed=(void*)(uintptr_t)value;return;
default:abort();}}
case 26:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=value;return;
case 1:p->mswallower=(void*)(uintptr_t)value;return;
case 2:p->mhitu_dieroll=value;return;
default:abort();}}
case 27:{dlevel_t*p=at;switch(field){
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(void*)(uintptr_t)value;return;
case 1:p->notonhead=value;return;
default:abort();}}
case 29:{struct kinfo*p=at;switch(field){
case 0:p->format=value;return;
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:p->mvflags=value;return;
default:abort();}}
case 31:{struct instance_globals_s*p=at;switch(field){
case 0:p->stoned=value;return;
case 1:p->skipdrin=value;return;
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole,(void*)(uintptr_t)value,sizeof p->urole);return;
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(void*)(uintptr_t)value;return;
default:abort();}}
case 34:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst,(void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 35:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology,(void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 36:{struct instance_globals_saved_k*p=at;switch(field){
case 0:memmove(&p->killer,(void*)(uintptr_t)value,sizeof p->killer);return;
default:abort();}}
case 37:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level,(void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 38:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 39:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_mhitu_address(int kind,void*at,int field){switch(kind){
case 0:{struct sysopt_s*p=at;switch(field){
case 0:return (void*)&p->seduce;
default:abort();}}
case 1:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 2:{struct align*p=at;switch(field){
case 0:return (void*)&p->type;
default:abort();}}
case 3:{struct nhcoord*p=at;switch(field){
case 0:return (void*)&p->x;
case 1:return (void*)&p->y;
default:abort();}}
case 4:{struct flag*p=at;switch(field){
case 0:return (void*)&p->female;
case 1:return (void*)&p->verbose;
default:abort();}}
case 5:{struct trap*p=at;switch(field){
default:abort();}}
case 6:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->win_display_nhwindow;
default:abort();}}
case 7:{struct attribs*p=at;switch(field){
default:abort();}}
case 8:{struct obj*p=at;switch(field){
case 0:return (void*)&p->nobj;
case 1:return (void*)&p->ox;
case 2:return (void*)&p->oy;
case 3:return (void*)&p->otyp;
case 4:return (void*)&p->quan;
case 5:return (void*)&p->spe;
case 6:return (void*)&p->oclass;
case 7:return (void*)&p->where;
case 12:return (void*)&p->corpsenm;
case 13:return (void*)&p->owornmask;
default:abort();}}
case 9:{struct objclass*p=at;switch(field){
case 2:return (void*)&p->oc_subtyp;
case 3:return (void*)&p->oc_oc2;
default:abort();}}
case 10:{struct attack*p=at;switch(field){
case 0:return (void*)&p->aatyp;
case 1:return (void*)&p->adtyp;
case 2:return (void*)&p->damn;
case 3:return (void*)&p->damd;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->pmnames;
case 1:return (void*)&p->pmidx;
case 2:return (void*)&p->mlet;
case 3:return (void*)&p->mlevel;
case 4:return (void*)&p->mattk;
case 5:return (void*)&p->msize;
case 6:return (void*)&p->mflags1;
case 7:return (void*)&p->mflags2;
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->blocked;
case 2:return (void*)&p->intrinsic;
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
case 1:return (void*)&p->m_id;
case 2:return (void*)&p->cham;
case 3:return (void*)&p->m_lev;
case 4:return (void*)&p->mx;
case 5:return (void*)&p->my;
case 6:return (void*)&p->mux;
case 7:return (void*)&p->muy;
case 8:return (void*)&p->mhp;
case 9:return (void*)&p->mhpmax;
case 10:return (void*)&p->mappearance;
case 11:return (void*)&p->m_ap_type;
case 12:return (void*)&p->mtame;
case 13:return (void*)&p->seen_resistance;
case 14:return (void*)&p->mspec_used;
case 27:return (void*)&p->minvent;
case 28:return (void*)&p->mw;
case 29:return (void*)&p->misc_worn_check;
case 30:return (void*)&p->weapon_check;
default:abort();}}
case 14:{struct mhitm_data*p=at;switch(field){
case 0:return (void*)&p->damage;
case 1:return (void*)&p->hitflags;
case 2:return (void*)&p->done;
case 3:return (void*)&p->permdmg;
case 4:return (void*)&p->specialdmg;
default:abort();}}
case 15:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
default:abort();}}
case 16:{struct rm*p=at;switch(field){
default:abort();}}
case 17:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->bhitpos;
default:abort();}}
case 18:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_something;
case 1:return (void*)&p->c_Something;
case 2:return (void*)&p->c_vision_clears;
default:abort();}}
case 19:{struct u_roleplay*p=at;switch(field){
case 0:return (void*)&p->deaf;
default:abort();}}
case 20:{struct Role*p=at;switch(field){
case 0:return (void*)&p->mnum;
default:abort();}}
case 21:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_rogue_level;
default:abort();}}
case 22:{struct instance_globals_h*p=at;switch(field){
case 0:return (void*)&p->hitmsg_mid;
case 1:return (void*)&p->hitmsg_prev;
default:abort();}}
case 23:{struct Gender*p=at;switch(field){
case 0:return (void*)&p->he;
case 1:return (void*)&p->him;
case 2:return (void*)&p->his;
default:abort();}}
case 24:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 25:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->uz;
case 3:return (void*)&p->utotype;
case 4:return (void*)&p->ulevel;
case 5:return (void*)&p->utrap;
case 6:return (void*)&p->utraptype;
case 7:return (void*)&p->uprops;
case 8:return (void*)&p->umonster;
case 9:return (void*)&p->umonnum;
case 10:return (void*)&p->mh;
case 11:return (void*)&p->mhmax;
case 12:return (void*)&p->uswldtim;
case 18:return (void*)&p->uroleplay;
case 19:return (void*)&p->ualign;
case 20:return (void*)&p->uac;
case 21:return (void*)&p->uspellprot;
case 22:return (void*)&p->uhp;
case 23:return (void*)&p->uhpmax;
case 24:return (void*)&p->uen;
case 25:return (void*)&p->uenmax;
case 26:return (void*)&p->uenpeak;
case 27:return (void*)&p->ublessed;
case 28:return (void*)&p->usleep;
case 29:return (void*)&p->ustuck;
case 30:return (void*)&p->usteed;
default:abort();}}
case 26:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->multi;
case 1:return (void*)&p->mswallower;
case 2:return (void*)&p->mhitu_dieroll;
default:abort();}}
case 27:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->objects;
case 1:return (void*)&p->monsters;
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->nomovemsg;
case 1:return (void*)&p->notonhead;
default:abort();}}
case 29:{struct kinfo*p=at;switch(field){
case 0:return (void*)&p->format;
case 1:return (void*)&p->name;
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:return (void*)&p->mvflags;
default:abort();}}
case 31:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->stoned;
case 1:return (void*)&p->skipdrin;
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->viz_array;
default:abort();}}
case 34:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 35:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
default:abort();}}
case 36:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (void*)&p->killer;
default:abort();}}
case 37:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
default:abort();}}
case 38:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
case 1:return (void*)&p->mvitals;
default:abort();}}
case 39:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (void*)&p->plname;
default:abort();}}
default:abort();}}
uintptr_t teleport_mhitu_callback(int i){switch(i){case 0:return (uintptr_t)&xname;case 1:return (uintptr_t)&simpleonames;default:abort();}}
void teleport_mhitu_display_nhwindow(winid window,boolean blocking){display_nhwindow(window,blocking);}
_Static_assert(sizeof(((struct sysopt_s*)0)->seduce)==4 && (((__typeof__(((struct sysopt_s*)0)->seduce))-1<0)==1),"MHITU sysopt_s.seduce width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"MHITU d_level.dnum width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"MHITU d_level.dlevel width/sign");
_Static_assert(sizeof(((struct align*)0)->type)==1 && (((__typeof__(((struct align*)0)->type))-1<0)==1),"MHITU align.type width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2 && (((__typeof__(((struct nhcoord*)0)->x))-1<0)==1),"MHITU nhcoord.x width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2 && (((__typeof__(((struct nhcoord*)0)->y))-1<0)==1),"MHITU nhcoord.y width/sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1 && (((__typeof__(((struct flag*)0)->female))-1<0)==1),"MHITU flag.female width/sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1 && (((__typeof__(((struct flag*)0)->verbose))-1<0)==1),"MHITU flag.verbose width/sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2 && (((__typeof__(((struct obj*)0)->ox))-1<0)==1),"MHITU obj.ox width/sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2 && (((__typeof__(((struct obj*)0)->oy))-1<0)==1),"MHITU obj.oy width/sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"MHITU obj.otyp width/sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"MHITU obj.quan width/sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1 && (((__typeof__(((struct obj*)0)->spe))-1<0)==1),"MHITU obj.spe width/sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1 && (((__typeof__(((struct obj*)0)->oclass))-1<0)==1),"MHITU obj.oclass width/sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1 && (((__typeof__(((struct obj*)0)->where))-1<0)==1),"MHITU obj.where width/sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4 && (((__typeof__(((struct obj*)0)->corpsenm))-1<0)==1),"MHITU obj.corpsenm width/sign");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8 && (((__typeof__(((struct obj*)0)->owornmask))-1<0)==1),"MHITU obj.owornmask width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1 && (((__typeof__(((struct objclass*)0)->oc_subtyp))-1<0)==1),"MHITU objclass.oc_subtyp width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_oc2)==1 && (((__typeof__(((struct objclass*)0)->oc_oc2))-1<0)==1),"MHITU objclass.oc_oc2 width/sign");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1 && (((__typeof__(((struct attack*)0)->aatyp))-1<0)==0),"MHITU attack.aatyp width/sign");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1 && (((__typeof__(((struct attack*)0)->adtyp))-1<0)==0),"MHITU attack.adtyp width/sign");
_Static_assert(sizeof(((struct attack*)0)->damn)==1 && (((__typeof__(((struct attack*)0)->damn))-1<0)==0),"MHITU attack.damn width/sign");
_Static_assert(sizeof(((struct attack*)0)->damd)==1 && (((__typeof__(((struct attack*)0)->damd))-1<0)==0),"MHITU attack.damd width/sign");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4 && (((__typeof__(((struct permonst*)0)->pmidx))-1<0)==1),"MHITU permonst.pmidx width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"MHITU permonst.mlet width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1 && (((__typeof__(((struct permonst*)0)->mlevel))-1<0)==1),"MHITU permonst.mlevel width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1 && (((__typeof__(((struct permonst*)0)->msize))-1<0)==0),"MHITU permonst.msize width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"MHITU permonst.mflags1 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8 && (((__typeof__(((struct permonst*)0)->mflags2))-1<0)==0),"MHITU permonst.mflags2 width/sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"MHITU prop.extrinsic width/sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"MHITU prop.blocked width/sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"MHITU prop.intrinsic width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4 && (((__typeof__(((struct monst*)0)->m_id))-1<0)==0),"MHITU monst.m_id width/sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2 && (((__typeof__(((struct monst*)0)->cham))-1<0)==1),"MHITU monst.cham width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1 && (((__typeof__(((struct monst*)0)->m_lev))-1<0)==0),"MHITU monst.m_lev width/sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"MHITU monst.mx width/sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"MHITU monst.my width/sign");
_Static_assert(sizeof(((struct monst*)0)->mux)==2 && (((__typeof__(((struct monst*)0)->mux))-1<0)==1),"MHITU monst.mux width/sign");
_Static_assert(sizeof(((struct monst*)0)->muy)==2 && (((__typeof__(((struct monst*)0)->muy))-1<0)==1),"MHITU monst.muy width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"MHITU monst.mhp width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4 && (((__typeof__(((struct monst*)0)->mhpmax))-1<0)==1),"MHITU monst.mhpmax width/sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4 && (((__typeof__(((struct monst*)0)->mappearance))-1<0)==0),"MHITU monst.mappearance width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"MHITU monst.m_ap_type width/sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"MHITU monst.mtame width/sign");
_Static_assert(sizeof(((struct monst*)0)->seen_resistance)==8 && (((__typeof__(((struct monst*)0)->seen_resistance))-1<0)==0),"MHITU monst.seen_resistance width/sign");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4 && (((__typeof__(((struct monst*)0)->mspec_used))-1<0)==1),"MHITU monst.mspec_used width/sign");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8 && (((__typeof__(((struct monst*)0)->misc_worn_check))-1<0)==1),"MHITU monst.misc_worn_check width/sign");
_Static_assert(sizeof(((struct monst*)0)->weapon_check)==2 && (((__typeof__(((struct monst*)0)->weapon_check))-1<0)==1),"MHITU monst.weapon_check width/sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->damage)==4 && (((__typeof__(((struct mhitm_data*)0)->damage))-1<0)==1),"MHITU mhitm_data.damage width/sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->hitflags)==4 && (((__typeof__(((struct mhitm_data*)0)->hitflags))-1<0)==1),"MHITU mhitm_data.hitflags width/sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->done)==1 && (((__typeof__(((struct mhitm_data*)0)->done))-1<0)==1),"MHITU mhitm_data.done width/sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->permdmg)==1 && (((__typeof__(((struct mhitm_data*)0)->permdmg))-1<0)==1),"MHITU mhitm_data.permdmg width/sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->specialdmg)==4 && (((__typeof__(((struct mhitm_data*)0)->specialdmg))-1<0)==1),"MHITU mhitm_data.specialdmg width/sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1 && (((__typeof__(((struct display_hints*)0)->botl))-1<0)==1),"MHITU display_hints.botl width/sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1 && (((__typeof__(((struct u_roleplay*)0)->deaf))-1<0)==1),"MHITU u_roleplay.deaf width/sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2 && (((__typeof__(((struct Role*)0)->mnum))-1<0)==1),"MHITU Role.mnum width/sign");
_Static_assert(sizeof(((struct instance_globals_h*)0)->hitmsg_mid)==4 && (((__typeof__(((struct instance_globals_h*)0)->hitmsg_mid))-1<0)==0),"MHITU instance_globals_h.hitmsg_mid width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"MHITU you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"MHITU you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->utotype)==1 && (((__typeof__(((struct you*)0)->utotype))-1<0)==0),"MHITU you.utotype width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4 && (((__typeof__(((struct you*)0)->ulevel))-1<0)==1),"MHITU you.ulevel width/sign");
_Static_assert(sizeof(((struct you*)0)->utrap)==4 && (((__typeof__(((struct you*)0)->utrap))-1<0)==0),"MHITU you.utrap width/sign");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4 && (((__typeof__(((struct you*)0)->utraptype))-1<0)==0),"MHITU you.utraptype width/sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"MHITU you.umonster width/sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"MHITU you.umonnum width/sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4 && (((__typeof__(((struct you*)0)->mh))-1<0)==1),"MHITU you.mh width/sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4 && (((__typeof__(((struct you*)0)->mhmax))-1<0)==1),"MHITU you.mhmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uswldtim)==4 && (((__typeof__(((struct you*)0)->uswldtim))-1<0)==0),"MHITU you.uswldtim width/sign");
_Static_assert(sizeof(((struct you*)0)->uac)==1 && (((__typeof__(((struct you*)0)->uac))-1<0)==1),"MHITU you.uac width/sign");
_Static_assert(sizeof(((struct you*)0)->uspellprot)==1 && (((__typeof__(((struct you*)0)->uspellprot))-1<0)==0),"MHITU you.uspellprot width/sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4 && (((__typeof__(((struct you*)0)->uhp))-1<0)==1),"MHITU you.uhp width/sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4 && (((__typeof__(((struct you*)0)->uhpmax))-1<0)==1),"MHITU you.uhpmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uen)==4 && (((__typeof__(((struct you*)0)->uen))-1<0)==1),"MHITU you.uen width/sign");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4 && (((__typeof__(((struct you*)0)->uenmax))-1<0)==1),"MHITU you.uenmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uenpeak)==4 && (((__typeof__(((struct you*)0)->uenpeak))-1<0)==1),"MHITU you.uenpeak width/sign");
_Static_assert(sizeof(((struct you*)0)->ublessed)==4 && (((__typeof__(((struct you*)0)->ublessed))-1<0)==1),"MHITU you.ublessed width/sign");
_Static_assert(sizeof(((struct you*)0)->usleep)==8 && (((__typeof__(((struct you*)0)->usleep))-1<0)==1),"MHITU you.usleep width/sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8 && (((__typeof__(((struct instance_globals_m*)0)->multi))-1<0)==1),"MHITU instance_globals_m.multi width/sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->mhitu_dieroll)==4 && (((__typeof__(((struct instance_globals_m*)0)->mhitu_dieroll))-1<0)==1),"MHITU instance_globals_m.mhitu_dieroll width/sign");
_Static_assert(sizeof(((struct instance_globals_n*)0)->notonhead)==1 && (((__typeof__(((struct instance_globals_n*)0)->notonhead))-1<0)==1),"MHITU instance_globals_n.notonhead width/sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4 && (((__typeof__(((struct kinfo*)0)->format))-1<0)==1),"MHITU kinfo.format width/sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1 && (((__typeof__(((struct mvitals*)0)->mvflags))-1<0)==0),"MHITU mvitals.mvflags width/sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->stoned)==1 && (((__typeof__(((struct instance_globals_s*)0)->stoned))-1<0)==1),"MHITU instance_globals_s.stoned width/sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->skipdrin)==1 && (((__typeof__(((struct instance_globals_s*)0)->skipdrin))-1<0)==1),"MHITU instance_globals_s.skipdrin width/sign");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8 && (((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1<0)==1),"MHITU instance_globals_saved_m.moves width/sign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Amonnam),char * (*)(struct monst *)),"MHITU dependency Amonnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_hell),signed char (*)(d_level *)),"MHITU dependency In_hell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Mgender),int (*)(struct monst *)),"MHITU dependency Mgender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Monnam),char * (*)(struct monst *)),"MHITU dependency Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Resists_Elem),signed char (*)(struct monst *,int)),"MHITU dependency Resists_Elem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Ring_gone),void (*)(struct obj *)),"MHITU dependency Ring_gone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Ring_on),void (*)(struct obj *)),"MHITU dependency Ring_on");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Some_Monnam),char * (*)(struct monst *)),"MHITU dependency Some_Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&acid_damage),void (*)(struct obj *)),"MHITU dependency acid_damage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&acurr),signed char (*)(int)),"MHITU dependency acurr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&adjalign),void (*)(int)),"MHITU dependency adjalign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&adjattrib),signed char (*)(int,int,int)),"MHITU dependency adjattrib");
_Static_assert(__builtin_types_compatible_p(__typeof__(&an),char * (*)(const char *)),"MHITU dependency an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype_fordmg),struct attack * (*)(struct permonst *,int,int)),"MHITU dependency attacktype_fordmg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attk_protection),long (*)(int)),"MHITU dependency attk_protection");
_Static_assert(__builtin_types_compatible_p(__typeof__(&body_part),const char * (*)(int)),"MHITU dependency body_part");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bot),void (*)(void)),"MHITU dependency bot");
_Static_assert(__builtin_types_compatible_p(__typeof__(&breamu),int (*)(struct monst *,struct attack *)),"MHITU dependency breamu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&burn_away_slime),void (*)(void)),"MHITU dependency burn_away_slime");
_Static_assert(__builtin_types_compatible_p(__typeof__(&burnarmor),signed char (*)(struct monst *)),"MHITU dependency burnarmor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&buzzmu),int (*)(struct monst *,struct attack *)),"MHITU dependency buzzmu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_blnd),signed char (*)(struct monst *,struct monst *,uchar,struct obj *)),"MHITU dependency can_blnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"MHITU dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&castmu),int (*)(struct monst *,struct attack *,boolean,boolean)),"MHITU dependency castmu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ceiling),const char * (*)(coordxy,coordxy)),"MHITU dependency ceiling");
_Static_assert(__builtin_types_compatible_p(__typeof__(&christen_monst),struct monst * (*)(struct monst *,const char *)),"MHITU dependency christen_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cloak_simple_name),const char * (*)(struct obj *)),"MHITU dependency cloak_simple_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&currency),const char * (*)(long)),"MHITU dependency currency");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cvt_adtyp_to_mseenres),unsigned long (*)(uchar)),"MHITU dependency cvt_adtyp_to_mseenres");
_Static_assert(__builtin_types_compatible_p(__typeof__(&defended),signed char (*)(struct monst *,int)),"MHITU dependency defended");
_Static_assert(__builtin_types_compatible_p(__typeof__(&destroy_items),int (*)(struct monst *,int,int)),"MHITU dependency destroy_items");
_Static_assert(__builtin_types_compatible_p(__typeof__(&discover_object),void (*)(int,boolean,boolean,boolean)),"MHITU dependency discover_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dismount_steed),void (*)(int)),"MHITU dependency dismount_steed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy,coordxy,coordxy,coordxy)),"MHITU dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype),signed char (*)(struct permonst *,int)),"MHITU dependency dmgtype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype_fromattack),struct attack * (*)(struct permonst *,int,int)),"MHITU dependency dmgtype_fromattack");
_Static_assert(__builtin_types_compatible_p(__typeof__(&doname),char * (*)(struct obj *)),"MHITU dependency doname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done),void (*)(int)),"MHITU dependency done");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done_in_by),void (*)(struct monst *,int)),"MHITU dependency done_in_by");
_Static_assert(__builtin_types_compatible_p(__typeof__(&drain_en),void (*)(int,boolean)),"MHITU dependency drain_en");
_Static_assert(__builtin_types_compatible_p(__typeof__(&drain_item),signed char (*)(struct obj *,boolean)),"MHITU dependency drain_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&enexto),signed char (*)(coord *,coordxy,coordxy,struct permonst *)),"MHITU dependency enexto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&engulf_target),signed char (*)(struct monst *,struct monst *)),"MHITU dependency engulf_target");
_Static_assert(__builtin_types_compatible_p(__typeof__(&erode_armor),void (*)(struct monst *,int)),"MHITU dependency erode_armor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exercise),void (*)(int,boolean)),"MHITU dependency exercise");
_Static_assert(__builtin_types_compatible_p(__typeof__(&failed_grab),signed char (*)(struct monst *,struct monst *,struct attack *)),"MHITU dependency failed_grab");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_mac),int (*)(struct monst *)),"MHITU dependency find_mac");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_offensive),signed char (*)(struct monst *)),"MHITU dependency find_offensive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flush_screen),void (*)(int)),"MHITU dependency flush_screen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&freeinv),void (*)(struct obj *)),"MHITU dependency freeinv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&gender),int (*)(struct monst *)),"MHITU dependency gender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_atkdam_type),int (*)(int)),"MHITU dependency get_atkdam_type");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getyear),int (*)(void)),"MHITU dependency getyear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&golemeffects),void (*)(struct monst *,int,int)),"MHITU dependency golemeffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&growl_sound),const char * (*)(struct monst *)),"MHITU dependency growl_sound");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hard_helmet),signed char (*)(struct obj *)),"MHITU dependency hard_helmet");
_Static_assert(__builtin_types_compatible_p(__typeof__(&helm_simple_name),const char * (*)(struct obj *)),"MHITU dependency helm_simple_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hitval),int (*)(struct obj *,struct monst *)),"MHITU dependency hitval");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hliquid),const char * (*)(const char *)),"MHITU dependency hliquid");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ignite_items),void (*)(struct obj *)),"MHITU dependency ignite_items");
_Static_assert(__builtin_types_compatible_p(__typeof__(&incr_itimeout),void (*)(long *,int)),"MHITU dependency incr_itimeout");
_Static_assert(__builtin_types_compatible_p(__typeof__(&initedog),void (*)(struct monst *,boolean)),"MHITU dependency initedog");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_art),signed char (*)(struct obj *,int)),"MHITU dependency is_art");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_fainted),signed char (*)(void)),"MHITU dependency is_fainted");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_home_elemental),signed char (*)(struct permonst *)),"MHITU dependency is_home_elemental");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool),signed char (*)(coordxy,coordxy)),"MHITU dependency is_pool");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_quest_artifact),signed char (*)(struct obj *)),"MHITU dependency is_quest_artifact");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_waterwall),signed char (*)(coordxy,coordxy)),"MHITU dependency is_waterwall");
_Static_assert(__builtin_types_compatible_p(__typeof__(&killed),void (*)(struct monst *)),"MHITU dependency killed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losehp),void (*)(int,const char *,schar)),"MHITU dependency losehp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losexp),void (*)(const char *)),"MHITU dependency losexp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_monnam),char * (*)(struct monst *)),"MHITU dependency m_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_blinded),void (*)(long,boolean)),"MHITU dependency make_blinded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_confused),void (*)(long,boolean)),"MHITU dependency make_confused");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_hallucinated),signed char (*)(long,boolean,long)),"MHITU dependency make_hallucinated");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_sick),void (*)(long,const char *,boolean,int)),"MHITU dependency make_sick");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_stunned),void (*)(long,boolean)),"MHITU dependency make_stunned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makemon),struct monst * (*)(struct permonst *,coordxy,coordxy,mmflags_nht)),"MHITU dependency makemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makeplural),char * (*)(const char *)),"MHITU dependency makeplural");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_invisible),void (*)(coordxy,coordxy)),"MHITU dependency map_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mattackm),int (*)(struct monst *,struct monst *)),"MHITU dependency mattackm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mhitm_adtyping),void (*)(struct monst *,struct attack *,struct monst *,struct mhitm_data *)),"MHITU dependency mhitm_adtyping");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mhitm_knockback),signed char (*)(struct monst *,struct monst *,struct attack *,int *,boolean)),"MHITU dependency mhitm_knockback");
_Static_assert(__builtin_types_compatible_p(__typeof__(&midnight),int (*)(void)),"MHITU dependency midnight");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mimic_obj_name),const char * (*)(struct monst *)),"MHITU dependency mimic_obj_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&minstapetrify),void (*)(struct monst *,boolean)),"MHITU dependency minstapetrify");
_Static_assert(__builtin_types_compatible_p(__typeof__(&minuhpmax),int (*)(int)),"MHITU dependency minuhpmax");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mnexto),void (*)(struct monst *,unsigned int)),"MHITU dependency mnexto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_explodes),void (*)(struct monst *,struct attack *)),"MHITU dependency mon_explodes");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_hates_blessings),signed char (*)(struct monst *)),"MHITU dependency mon_hates_blessings");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_nam),char * (*)(struct monst *)),"MHITU dependency mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_reflects),signed char (*)(struct monst *,const char *)),"MHITU dependency mon_reflects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_to_stone),void (*)(struct monst *)),"MHITU dependency mon_to_stone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_visible),int (*)(struct monst *)),"MHITU dependency mon_visible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_wield_item),int (*)(struct monst *)),"MHITU dependency mon_wield_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mondead),void (*)(struct monst *)),"MHITU dependency mondead");
_Static_assert(__builtin_types_compatible_p(__typeof__(&money2mon),long (*)(struct monst *,long)),"MHITU dependency money2mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&money_cnt),long (*)(struct obj *)),"MHITU dependency money_cnt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monnear),signed char (*)(struct monst *,coordxy,coordxy)),"MHITU dependency monnear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monstseesu),void (*)(unsigned long)),"MHITU dependency monstseesu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monstunseesu),void (*)(unsigned long)),"MHITU dependency monstunseesu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mpickobj),int (*)(struct monst *,struct obj *)),"MHITU dependency mpickobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&msummon),int (*)(struct monst *)),"MHITU dependency msummon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&new_were),void (*)(struct monst *)),"MHITU dependency new_were");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy,coordxy)),"MHITU dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&night),int (*)(void)),"MHITU dependency night");
_Static_assert(__builtin_types_compatible_p(__typeof__(&noit_Monnam),char * (*)(struct monst *)),"MHITU dependency noit_Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&noit_mon_nam),char * (*)(struct monst *)),"MHITU dependency noit_mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nomul),void (*)(int)),"MHITU dependency nomul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&number_leashed),int (*)(void)),"MHITU dependency number_leashed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&observe_object),void (*)(struct obj *)),"MHITU dependency observe_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),signed char (*)(d_level *,d_level *)),"MHITU dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&paralyze_monst),void (*)(struct monst *,int)),"MHITU dependency paralyze_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&place_monster),void (*)(struct monst *,coordxy,coordxy)),"MHITU dependency place_monster");
_Static_assert(__builtin_types_compatible_p(__typeof__(&placebc),void (*)(void)),"MHITU dependency placebc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pluslvl),void (*)(boolean)),"MHITU dependency pluslvl");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pmname),const char * (*)(struct permonst *,int)),"MHITU dependency pmname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&poly_gender),int (*)(void)),"MHITU dependency poly_gender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&poly_when_stoned),signed char (*)(struct permonst *)),"MHITU dependency poly_when_stoned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&polymon),int (*)(int)),"MHITU dependency polymon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&prinv),void (*)(const char *,struct obj *,long)),"MHITU dependency prinv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pronoun_gender),int (*)(struct monst *,unsigned int)),"MHITU dependency pronoun_gender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&protects),signed char (*)(struct obj *,boolean)),"MHITU dependency protects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rehumanize),void (*)(void)),"MHITU dependency rehumanize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&remove_worn_item),void (*)(struct obj *,boolean)),"MHITU dependency remove_worn_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reset_occupations),void (*)(void)),"MHITU dependency reset_occupations");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reset_utrap),void (*)(boolean)),"MHITU dependency reset_utrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resists_blnd),signed char (*)(struct monst *)),"MHITU dependency resists_blnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resists_drli),signed char (*)(struct monst *)),"MHITU dependency resists_drli");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rloc),signed char (*)(struct monst *,unsigned int)),"MHITU dependency rloc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&s_suffix),char * (*)(const char *)),"MHITU dependency s_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&safe_qbuf),char * (*)(char *,const char *,const char *,struct obj *,char *(*)(struct obj *),char *(*)(struct obj *),const char *)),"MHITU dependency safe_qbuf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"MHITU dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_apparxy),void (*)(struct monst *)),"MHITU dependency set_apparxy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_msg_xy),void (*)(coordxy,coordxy)),"MHITU dependency set_msg_xy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_ustuck),void (*)(struct monst *)),"MHITU dependency set_ustuck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setworn),void (*)(struct obj *,long)),"MHITU dependency setworn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&shieldeff),void (*)(coordxy,coordxy)),"MHITU dependency shieldeff");
_Static_assert(__builtin_types_compatible_p(__typeof__(&showdamage),void (*)(int)),"MHITU dependency showdamage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&simpleonames),char * (*)(struct obj *)),"MHITU dependency simpleonames");
_Static_assert(__builtin_types_compatible_p(__typeof__(&snuff_lit),signed char (*)(struct obj *)),"MHITU dependency snuff_lit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sobj_at),struct obj * (*)(int,coordxy,coordxy)),"MHITU dependency sobj_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spitmu),int (*)(struct monst *,struct attack *)),"MHITU dependency spitmu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&split_mon),struct monst * (*)(struct monst *,struct monst *)),"MHITU dependency split_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spoteffects),void (*)(boolean)),"MHITU dependency spoteffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stagger),const char * (*)(const struct permonst *,const char *)),"MHITU dependency stagger");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sticks),signed char (*)(struct permonst *)),"MHITU dependency sticks");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stop_donning),int (*)(struct obj *)),"MHITU dependency stop_donning");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stop_occupation),void (*)(void)),"MHITU dependency stop_occupation");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcat),char * (*)(char *restrict,const char *restrict)),"MHITU dependency strcat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strchr),char * (*)(const char *,int)),"MHITU dependency strchr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *,const char *)),"MHITU dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char * (*)(char *restrict,const char *restrict)),"MHITU dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&suit_simple_name),const char * (*)(struct obj *)),"MHITU dependency suit_simple_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&swallowed),void (*)(int)),"MHITU dependency swallowed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&t_at),struct trap * (*)(coordxy,coordxy)),"MHITU dependency t_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tele_restrict),signed char (*)(struct monst *)),"MHITU dependency tele_restrict");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleds),void (*)(coordxy,coordxy,int)),"MHITU dependency teleds");
_Static_assert(__builtin_types_compatible_p(__typeof__(&the),char * (*)(const char *)),"MHITU dependency the");
_Static_assert(__builtin_types_compatible_p(__typeof__(&thrwmu),void (*)(struct monst *)),"MHITU dependency thrwmu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tp_sensemon),int (*)(struct monst *)),"MHITU dependency tp_sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&u_carried_gloves),struct obj * (*)(void)),"MHITU dependency u_carried_gloves");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ugolemeffects),void (*)(int,int)),"MHITU dependency ugolemeffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&um_dist),signed char (*)(coordxy,coordxy,xint16)),"MHITU dependency um_dist");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unconscious),signed char (*)(void)),"MHITU dependency unconscious");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unleash_all),void (*)(void)),"MHITU dependency unleash_all");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unmul),void (*)(const char *)),"MHITU dependency unmul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unplacebc),void (*)(void)),"MHITU dependency unplacebc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unresponsive),signed char (*)(void)),"MHITU dependency unresponsive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unstuck),void (*)(struct monst *)),"MHITU dependency unstuck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&update_inventory),void (*)(void)),"MHITU dependency update_inventory");
_Static_assert(__builtin_types_compatible_p(__typeof__(&upstart),char * (*)(char *)),"MHITU dependency upstart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ureflects),signed char (*)(const char *,const char *)),"MHITU dependency ureflects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_offensive),int (*)(struct monst *)),"MHITU dependency use_offensive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vision_recalc),void (*)(int)),"MHITU dependency vision_recalc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vtense),char * (*)(const char *,const char *)),"MHITU dependency vtense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wake_nearto),void (*)(coordxy,coordxy,int)),"MHITU dependency wake_nearto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&welded),int (*)(struct obj *)),"MHITU dependency welded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&were_summon),int (*)(struct permonst *,boolean,int *,char *)),"MHITU dependency were_summon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&which_armor),struct obj * (*)(struct monst *,long)),"MHITU dependency which_armor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&worm_move),void (*)(struct monst *)),"MHITU dependency worm_move");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xkilled),void (*)(struct monst *,int)),"MHITU dependency xkilled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xname),char * (*)(struct obj *)),"MHITU dependency xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yn_function),char (*)(const char *,const char *,char,boolean)),"MHITU dependency yn_function");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yname),char * (*)(struct obj *)),"MHITU dependency yname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yyyymmdd),long (*)(time_t)),"MHITU dependency yyyymmdd");
static char mhitu_literals[MHITU_LITERAL_CAPACITY];
char*teleport_mhitu_literal_storage(void){return mhitu_literals;}
size_t teleport_mhitu_literal_capacity(void){return sizeof mhitu_literals;}
void teleport_mhitu_rng_caller(int site){if(site<0||site>=MHITU_RNG_COUNT)abort();if(rng_log_enabled())rng_log_set_caller(MHITU_SOURCE_FILE,mhitu_rng_lines[site],mhitu_rng_functions[site]);}
int teleport_mhitu_rn2_value(int n){return (rn2)(n);}
int teleport_mhitu_rnd_value(int n){return (rnd)(n);}
int teleport_mhitu_rnl_value(int n){return (rnl)(n);}
int teleport_mhitu_d_value(int n,int x){return (d)(n,x);}
/* These wrappers intentionally forward the exact original variable format; no extra argument is introduced. */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
void teleport_mhitu_pline_mon_ppppp(struct monst * a0,const char * a1,char * a2,char * a3,const char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_mhitu_pline_mon_pppppp(struct monst * a0,const char * a1,char * a2,char * a3,char * a4,const char * a5){(pline_mon)(a0,a1,a2,a3,a4,a5);}
void teleport_mhitu_pline_mon_ppp(struct monst * a0,const char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_mhitu_pline_mon_pppp(struct monst * a0,const char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_mhitu_pline_mon_ppppppp(struct monst * a0,const char * a1,char * a2,const char * a3,char * a4,const char * a5,char * a6){(pline_mon)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_mhitu_You_p(const char * a0){(You)(a0);}
void teleport_mhitu_Your_p(const char * a0){(Your)(a0);}
void teleport_mhitu_impossible_pp(const char * a0,char * a1){(impossible)(a0,a1);}
void teleport_mhitu_pline_pp(const char * a0,const char * a1){(pline)(a0,a1);}
void teleport_mhitu_pline_ppp(const char * a0,const char * a1,const char * a2){(pline)(a0,a1,a2);}
void teleport_mhitu_pline_pppp(const char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_mhitu_impossible_p(const char * a0){(impossible)(a0);}
void teleport_mhitu_You_ppp(const char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_mhitu_pline_p(const char * a0){(pline)(a0);}
void teleport_mhitu_You_pp(const char * a0,char * a1){(You)(a0,a1);}
void teleport_mhitu_Your_ppp(const char * a0,char * a1,const char * a2){(Your)(a0,a1,a2);}
void teleport_mhitu_pline_ppppp(const char * a0,char * a1,const char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
int teleport_mhitu_sprintf_ppp(char * a0,const char * a1,const char * a2){return (sprintf)(a0,a1,a2);}
void teleport_mhitu_You_feel_pp(const char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_mhitu_You_hear_pp(const char * a0,char * a1){(You_hear)(a0,a1);}
void teleport_mhitu_You_feel_p(const char * a0){(You_feel)(a0);}
void teleport_mhitu_pline_The_p(const char * a0){(pline_The)(a0);}
void teleport_mhitu_urgent_pline_pppp(const char * a0,char * a1,char * a2,char * a3){(urgent_pline)(a0,a1,a2,a3);}
void teleport_mhitu_urgent_pline_ppp(const char * a0,char * a1,char * a2){(urgent_pline)(a0,a1,a2);}
void teleport_mhitu_pline_The_ppp(const char * a0,const char * a1,char * a2){(pline_The)(a0,a1,a2);}
void teleport_mhitu_You_cant_p(const char * a0){(You_cant)(a0);}
void teleport_mhitu_Your_pp(const char * a0,const char * a1){(Your)(a0,a1);}
void teleport_mhitu_impossible_pi(const char * a0,int a1){(impossible)(a0,a1);}
void teleport_mhitu_urgent_pline_p(const char * a0){(urgent_pline)(a0);}
void teleport_mhitu_verbalize_pp(const char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_mhitu_verbalize_ppp(const char * a0,const char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_mhitu_urgent_pline_pp(const char * a0,char * a1){(urgent_pline)(a0,a1);}
void teleport_mhitu_verbalize_p(const char * a0){(verbalize)(a0);}
void teleport_mhitu_pline_mon_ppplp(struct monst * a0,const char * a1,char * a2,long a3,const char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
int teleport_mhitu_sprintf_pppp(char * a0,const char * a1,const char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
#pragma clang diagnostic pop
