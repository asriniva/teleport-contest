/* ARTIFACT native storage, exact fields and typed dependency transport only. */
#include "hack.h"
#include "artifact.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "artifact-source-data.h"
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4,"ARTIFACT memory64 ABI");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0,"ARTIFACT signed boolean");
#ifndef TELEPORT_ARTIFACT_REFERENCE
static struct artifact teleport_artifact_artilist[35];
static struct arti_info teleport_artifact_artiexist[34];
static xint16 teleport_artifact_artidisco[33];
static struct arti_info teleport_artifact_zero_artiexist;
#endif
static char teleport_artifact_resbuf[20];
void*teleport_artifact_resbuf_storage(void){return teleport_artifact_resbuf;}
void*teleport_artifact_global(int i){switch(i){
case 0:return(void*)&aligns;
case 1:return(void*)&flags;
#ifdef TELEPORT_ARTIFACT_REFERENCE
case 2:return(void*)&artilist;
#else
case 2:return(void*)&teleport_artifact_artilist;
#endif
case 3:return(void*)&gu;
#ifdef TELEPORT_ARTIFACT_REFERENCE
case 4:return(void*)&artiexist;
#else
case 4:return(void*)&teleport_artifact_artiexist;
#endif
#ifdef TELEPORT_ARTIFACT_REFERENCE
case 5:return(void*)&artidisco;
#else
case 5:return(void*)&teleport_artifact_artidisco;
#endif
case 6:return(void*)&objects;
case 7:return(void*)&mons;
case 8:return(void*)&u;
#ifdef TELEPORT_ARTIFACT_REFERENCE
case 9:return(void*)&zero_artiexist;
#else
case 9:return(void*)&teleport_artifact_zero_artiexist;
#endif
case 10:return(void*)&obj_descr;
case 11:return(void*)&svb;
case 12:return(void*)&gi;
case 13:return(void*)&program_state;
case 14:return(void*)&svc;
case 15:return(void*)&gv;
case 16:return(void*)&gy;
case 17:return(void*)&gs;
case 18:return(void*)&windowprocs;
case 19:return(void*)&iflags;
case 20:return(void*)&disp;
case 21:return(void*)&gm;
case 22:return(void*)&gn;
case 23:return(void*)&c_common_strings;
case 24:return(void*)&c_color_names;
case 25:return(void*)&cg;
case 26:return(void*)&svn;
case 27:return(void*)&svd;
case 28:return(void*)&nul_glyphinfo;
case 29:return(void*)&svl;
case 30:return(void*)&svq;
case 31:return(void*)&svm;
case 32:return(void*)&uwep;
case 33:return(void*)&gw;
case 34:return(void*)&uarmg;
case 35:return(void*)&uleft;
case 36:return(void*)&uright;
case 37:return(void*)&uswapwep;
default:abort();}}
uint64_t teleport_artifact_read(int kind,void*at,int field){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->value);
default:abort();}}
case 1:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->initalign);
case 1:return (uint64_t)(uintptr_t)(p->verbose);
case 2:return (uint64_t)(uintptr_t)(p->female);
default:abort();}}
case 2:{struct artifact*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->otyp);
case 1:return (uint64_t)(uintptr_t)(p->role);
case 2:return (uint64_t)(uintptr_t)(p->alignment);
case 3:return (uint64_t)(uintptr_t)(p->name);
case 4:return (uint64_t)(uintptr_t)(p->spfx);
case 5:return (uint64_t)(uintptr_t)(p->gift_value);
case 6:return (uint64_t)(uintptr_t)(p->race);
case 7:return (uint64_t)(uintptr_t)(p->gen_spe);
case 8:return (uint64_t)(uintptr_t)(p->cspfx);
case 9:return (uint64_t)(uintptr_t)(p->mtype);
case 10:return (uint64_t)(uintptr_t)(&p->attk);
case 11:return (uint64_t)(uintptr_t)(&p->defn);
case 12:return (uint64_t)(uintptr_t)(&p->cary);
case 13:return (uint64_t)(uintptr_t)(p->inv_prop);
case 14:return (uint64_t)(uintptr_t)(p->cost);
case 15:return (uint64_t)(uintptr_t)(p->acolor);
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mnum);
case 1:return (uint64_t)(uintptr_t)(p->questarti);
default:abort();}}
case 4:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
case 1:return (uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 5:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->otyp);
case 1:return (uint64_t)(uintptr_t)(p->oeroded);
case 2:return (uint64_t)(uintptr_t)(p->oeroded2);
case 3:return (uint64_t)(uintptr_t)(p->oartifact);
case 4:return (uint64_t)(uintptr_t)(p->spe);
case 5:return (uint64_t)(uintptr_t)(p->otrapped);
case 6:return (uint64_t)(uintptr_t)(p->age);
case 7:return (uint64_t)(uintptr_t)(p->where);
case 8:return (uint64_t)(uintptr_t)(p->ox);
case 9:return (uint64_t)(uintptr_t)(p->oy);
case 10:return (uint64_t)(uintptr_t)(p->owornmask);
case 11:return (uint64_t)(uintptr_t)(p->quan);
case 12:return (uint64_t)(uintptr_t)(p->nobj);
case 13:return (uint64_t)(uintptr_t)(p->known);
case 14:return (uint64_t)(uintptr_t)(p->blessed);
case 15:return (uint64_t)(uintptr_t)(p->cursed);
case 16:return (uint64_t)(uintptr_t)(p->bknown);
case 17:return (uint64_t)(uintptr_t)(p->owt);
case 18:return (uint64_t)(uintptr_t)(p->oclass);
case 19:return (uint64_t)(uintptr_t)(p->lamplit);
case 20:return (uint64_t)(uintptr_t)(p->corpsenm);
case 21:return (uint64_t)(uintptr_t)(p->cobj);
case 22:return (uint64_t)(uintptr_t)(&p->v);
default:abort();}}
case 6:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_unique);
case 1:return (uint64_t)(uintptr_t)(p->oc_class);
case 2:return (uint64_t)(uintptr_t)(p->oc_subtyp);
case 3:return (uint64_t)(uintptr_t)(p->oc_material);
case 4:return (uint64_t)(uintptr_t)(p->oc_name_known);
case 5:return (uint64_t)(uintptr_t)(p->oc_descr_idx);
case 6:return (uint64_t)(uintptr_t)(p->oc_oprop);
case 7:return (uint64_t)(uintptr_t)(p->oc_cost);
default:abort();}}
case 7:{struct arti_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->exists);
case 1:return (uint64_t)(uintptr_t)(p->found);
case 2:return (uint64_t)(uintptr_t)(p->wish);
case 3:return (uint64_t)(uintptr_t)(p->gift);
case 4:return (uint64_t)(uintptr_t)(p->viadip);
case 5:return (uint64_t)(uintptr_t)(p->named);
case 6:return (uint64_t)(uintptr_t)(p->lvldef);
case 7:return (uint64_t)(uintptr_t)(p->bones);
case 8:return (uint64_t)(uintptr_t)(p->rndm);
default:abort();}}
case 8:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mflags2);
case 1:return (uint64_t)(uintptr_t)(p->mflags3);
case 2:return (uint64_t)(uintptr_t)(p->mlet);
case 3:return (uint64_t)(uintptr_t)(p->mflags1);
case 4:return (uint64_t)(uintptr_t)(p->maligntyp);
case 5:return (uint64_t)(uintptr_t)(p->mr);
case 6:return (uint64_t)(uintptr_t)(p->msize);
case 7:return (uint64_t)(uintptr_t)(p->msound);
default:abort();}}
case 9:{struct Race*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hatemask);
case 1:return (uint64_t)(uintptr_t)(p->mnum);
case 2:return (uint64_t)(uintptr_t)(p->selfmask);
default:abort();}}
case 10:{struct skills*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->max_skill);
case 1:return (uint64_t)(uintptr_t)(p->skill);
default:abort();}}
case 11:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->weapon_skills);
case 1:return (uint64_t)(uintptr_t)(p->ugifts);
case 2:return (uint64_t)(uintptr_t)(&p->uprops);
case 3:return (uint64_t)(uintptr_t)(p->xray_range);
case 4:return (uint64_t)(uintptr_t)(&p->ualign);
case 5:return (uint64_t)(uintptr_t)(p->ulycn);
case 6:return (uint64_t)(uintptr_t)(p->umonnum);
case 7:return (uint64_t)(uintptr_t)(p->umonster);
case 8:return (uint64_t)(uintptr_t)(p->uenmax);
case 9:return (uint64_t)(uintptr_t)(p->uen);
case 10:return (uint64_t)(uintptr_t)(p->uenpeak);
case 11:return (uint64_t)(uintptr_t)(p->ustuck);
case 12:return (uint64_t)(uintptr_t)(p->ux);
case 13:return (uint64_t)(uintptr_t)(p->uy);
case 14:return (uint64_t)(uintptr_t)(p->uswallow);
case 15:return (uint64_t)(uintptr_t)(p->mh);
case 16:return (uint64_t)(uintptr_t)(p->uhp);
case 17:return (uint64_t)(uintptr_t)(p->uhpmax);
case 18:return (uint64_t)(uintptr_t)(p->ucreamed);
case 19:return (uint64_t)(uintptr_t)(p->mhmax);
case 20:return (uint64_t)(uintptr_t)(&p->uz);
case 21:return (uint64_t)(uintptr_t)(&p->uhave);
case 22:return (uint64_t)(uintptr_t)(p->dx);
case 23:return (uint64_t)(uintptr_t)(p->dy);
case 24:return (uint64_t)(uintptr_t)(p->dz);
case 25:return (uint64_t)(uintptr_t)(p->twoweap);
case 26:return (uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
case 12:{struct objdescr*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_descr);
default:abort();}}
case 13:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->bases);
default:abort();}}
case 14:{struct attack*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->aatyp);
case 1:return (uint64_t)(uintptr_t)(p->adtyp);
case 2:return (uint64_t)(uintptr_t)(p->damn);
case 3:return (uint64_t)(uintptr_t)(p->damd);
default:abort();}}
case 15:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->intrinsic);
case 2:return (uint64_t)(uintptr_t)(p->blocked);
default:abort();}}
case 16:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 17:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->restoring);
default:abort();}}
case 18:{struct warntype_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->obj);
default:abort();}}
case 19:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->warntype);
default:abort();}}
case 20:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 21:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->vision_full_recalc);
case 1:return (uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 22:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 23:{struct align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
case 1:return (uint64_t)(uintptr_t)(p->record);
default:abort();}}
case 24:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
case 1:return (uint64_t)(uintptr_t)(p->mx);
case 2:return (uint64_t)(uintptr_t)(p->my);
case 3:return (uint64_t)(uintptr_t)(p->mhp);
case 4:return (uint64_t)(uintptr_t)(p->mstun);
case 5:return (uint64_t)(uintptr_t)(p->mconf);
case 6:return (uint64_t)(uintptr_t)(p->minvent);
case 7:return (uint64_t)(uintptr_t)(p->m_lev);
case 8:return (uint64_t)(uintptr_t)(p->mhpmax);
case 9:return (uint64_t)(uintptr_t)(p->nmon);
case 10:return (uint64_t)(uintptr_t)(p->msleeping);
case 11:return (uint64_t)(uintptr_t)(p->mtame);
case 12:return (uint64_t)(uintptr_t)(p->mpeaceful);
default:abort();}}
case 25:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->spec_dbon_applies);
default:abort();}}
case 26:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->win_putstr);
case 1:return (uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 2:return (uint64_t)(uintptr_t)(p->win_start_menu);
case 3:return (uint64_t)(uintptr_t)(p->win_end_menu);
case 4:return (uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
default:abort();}}
case 27:{struct color_and_attr*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->attr);
default:abort();}}
case 28:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->menu_headings);
default:abort();}}
case 29:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 30:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->multi_reason);
case 1:return (uint64_t)(uintptr_t)(p->mkot_trap_warn_count);
default:abort();}}
case 31:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nomovemsg);
case 1:return (uint64_t)(uintptr_t)(p->notonhead);
default:abort();}}
case 32:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->c_fakename);
case 1:return (uint64_t)(uintptr_t)(p->c_Never_mind);
case 2:return (uint64_t)(uintptr_t)(p->c_nothing_seems_to_happen);
case 3:return (uint64_t)(uintptr_t)(p->c_nothing_happens);
default:abort();}}
case 33:{struct c_color_names*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_black);
default:abort();}}
case 34:{struct const_globals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->zeroobj);
case 1:return (uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 35:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->n_dgns);
default:abort();}}
case 36:{struct dungeon*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dunlev_ureached);
case 1:return (uint64_t)(uintptr_t)(&p->dname);
case 2:return (uint64_t)(uintptr_t)(p->depth_start);
case 3:return (uint64_t)(uintptr_t)(p->entry_lev);
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeons);
case 1:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 38:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->d_tutorial_dnum);
case 1:return (uint64_t)(uintptr_t)(&p->d_astral_level);
default:abort();}}
case 39:{union any*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->a_int);
default:abort();}}
case 40:{struct mi*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 41:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 42:{struct u_have*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->amulet);
default:abort();}}
case 43:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->monlist);
case 1:return (uint64_t)(uintptr_t)(&p->locations);
case 2:return (uint64_t)(uintptr_t)(&p->objects);
default:abort();}}
case 44:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 45:{struct q_score*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->killed_nemesis);
default:abort();}}
case 46:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->quest_status);
default:abort();}}
case 47:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
default:abort();}}
case 48:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->lit);
case 1:return (uint64_t)(uintptr_t)(p->waslit);
case 2:return (uint64_t)(uintptr_t)(p->typ);
case 3:return (uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 49:{struct instance_globals_w*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->warn_obj_cnt);
default:abort();}}
case 50:{union vptrs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 51:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 52:{struct nhcoord*p=at;switch(field){
default:abort();}}
default:abort();}}
void teleport_artifact_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:p->value=value;return;
default:abort();}}
case 1:{struct flag*p=at;switch(field){
case 0:p->initalign=value;return;
case 1:p->verbose=value;return;
case 2:p->female=value;return;
default:abort();}}
case 2:{struct artifact*p=at;switch(field){
case 0:p->otyp=value;return;
case 1:p->role=value;return;
case 2:p->alignment=value;return;
case 3:p->name=(void*)(uintptr_t)value;return;
case 4:p->spfx=value;return;
case 5:p->gift_value=value;return;
case 6:p->race=value;return;
case 7:p->gen_spe=value;return;
case 8:p->cspfx=value;return;
case 9:p->mtype=value;return;
case 10:memmove(&p->attk,(void*)(uintptr_t)value,sizeof p->attk);return;
case 11:memmove(&p->defn,(void*)(uintptr_t)value,sizeof p->defn);return;
case 12:memmove(&p->cary,(void*)(uintptr_t)value,sizeof p->cary);return;
case 13:p->inv_prop=value;return;
case 14:p->cost=value;return;
case 15:p->acolor=value;return;
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:p->mnum=value;return;
case 1:p->questarti=value;return;
default:abort();}}
case 4:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole,(void*)(uintptr_t)value,sizeof p->urole);return;
case 1:memmove(&p->urace,(void*)(uintptr_t)value,sizeof p->urace);return;
default:abort();}}
case 5:{struct obj*p=at;switch(field){
case 0:p->otyp=value;return;
case 1:p->oeroded=value;return;
case 2:p->oeroded2=value;return;
case 3:p->oartifact=value;return;
case 4:p->spe=value;return;
case 5:p->otrapped=value;return;
case 6:p->age=value;return;
case 7:p->where=value;return;
case 8:p->ox=value;return;
case 9:p->oy=value;return;
case 10:p->owornmask=value;return;
case 11:p->quan=value;return;
case 12:p->nobj=(void*)(uintptr_t)value;return;
case 13:p->known=value;return;
case 14:p->blessed=value;return;
case 15:p->cursed=value;return;
case 16:p->bknown=value;return;
case 17:p->owt=value;return;
case 18:p->oclass=value;return;
case 19:p->lamplit=value;return;
case 20:p->corpsenm=value;return;
case 21:p->cobj=(void*)(uintptr_t)value;return;
case 22:memmove(&p->v,(void*)(uintptr_t)value,sizeof p->v);return;
default:abort();}}
case 6:{struct objclass*p=at;switch(field){
case 0:p->oc_unique=value;return;
case 1:p->oc_class=value;return;
case 2:p->oc_subtyp=value;return;
case 3:p->oc_material=value;return;
case 4:p->oc_name_known=value;return;
case 5:p->oc_descr_idx=value;return;
case 6:p->oc_oprop=value;return;
case 7:p->oc_cost=value;return;
default:abort();}}
case 7:{struct arti_info*p=at;switch(field){
case 0:p->exists=value;return;
case 1:p->found=value;return;
case 2:p->wish=value;return;
case 3:p->gift=value;return;
case 4:p->viadip=value;return;
case 5:p->named=value;return;
case 6:p->lvldef=value;return;
case 7:p->bones=value;return;
case 8:p->rndm=value;return;
default:abort();}}
case 8:{struct permonst*p=at;switch(field){
case 0:p->mflags2=value;return;
case 1:p->mflags3=value;return;
case 2:p->mlet=value;return;
case 3:p->mflags1=value;return;
case 4:p->maligntyp=value;return;
case 5:p->mr=value;return;
case 6:p->msize=value;return;
case 7:p->msound=value;return;
default:abort();}}
case 9:{struct Race*p=at;switch(field){
case 0:p->hatemask=value;return;
case 1:p->mnum=value;return;
case 2:p->selfmask=value;return;
default:abort();}}
case 10:{struct skills*p=at;switch(field){
case 0:p->max_skill=value;return;
case 1:p->skill=value;return;
default:abort();}}
case 11:{struct you*p=at;switch(field){
case 1:p->ugifts=value;return;
case 3:p->xray_range=value;return;
case 4:memmove(&p->ualign,(void*)(uintptr_t)value,sizeof p->ualign);return;
case 5:p->ulycn=value;return;
case 6:p->umonnum=value;return;
case 7:p->umonster=value;return;
case 8:p->uenmax=value;return;
case 9:p->uen=value;return;
case 10:p->uenpeak=value;return;
case 11:p->ustuck=(void*)(uintptr_t)value;return;
case 12:p->ux=value;return;
case 13:p->uy=value;return;
case 14:p->uswallow=value;return;
case 15:p->mh=value;return;
case 16:p->uhp=value;return;
case 17:p->uhpmax=value;return;
case 18:p->ucreamed=value;return;
case 19:p->mhmax=value;return;
case 20:memmove(&p->uz,(void*)(uintptr_t)value,sizeof p->uz);return;
case 21:memmove(&p->uhave,(void*)(uintptr_t)value,sizeof p->uhave);return;
case 22:p->dx=value;return;
case 23:p->dy=value;return;
case 24:p->dz=value;return;
case 25:p->twoweap=value;return;
case 26:p->usteed=(void*)(uintptr_t)value;return;
default:abort();}}
case 12:{struct objdescr*p=at;switch(field){
case 0:p->oc_descr=(void*)(uintptr_t)value;return;
default:abort();}}
case 13:{struct instance_globals_saved_b*p=at;switch(field){
default:abort();}}
case 14:{struct attack*p=at;switch(field){
case 0:p->aatyp=value;return;
case 1:p->adtyp=value;return;
case 2:p->damn=value;return;
case 3:p->damd=value;return;
default:abort();}}
case 15:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->intrinsic=value;return;
case 2:p->blocked=value;return;
default:abort();}}
case 16:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 17:{struct sinfo*p=at;switch(field){
case 0:p->restoring=value;return;
default:abort();}}
case 18:{struct warntype_info*p=at;switch(field){
case 0:p->obj=value;return;
default:abort();}}
case 19:{struct context_info*p=at;switch(field){
case 0:memmove(&p->warntype,(void*)(uintptr_t)value,sizeof p->warntype);return;
default:abort();}}
case 20:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context,(void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 21:{struct instance_globals_v*p=at;switch(field){
case 0:p->vision_full_recalc=value;return;
case 1:p->viz_array=(void*)(uintptr_t)value;return;
default:abort();}}
case 22:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst,(void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 23:{struct align*p=at;switch(field){
case 0:p->type=value;return;
case 1:p->record=value;return;
default:abort();}}
case 24:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
case 1:p->mx=value;return;
case 2:p->my=value;return;
case 3:p->mhp=value;return;
case 4:p->mstun=value;return;
case 5:p->mconf=value;return;
case 6:p->minvent=(void*)(uintptr_t)value;return;
case 7:p->m_lev=value;return;
case 8:p->mhpmax=value;return;
case 9:p->nmon=(void*)(uintptr_t)value;return;
case 10:p->msleeping=value;return;
case 11:p->mtame=value;return;
case 12:p->mpeaceful=value;return;
default:abort();}}
case 25:{struct instance_globals_s*p=at;switch(field){
case 0:p->spec_dbon_applies=value;return;
default:abort();}}
case 26:{struct window_procs*p=at;switch(field){
case 0:p->win_putstr=(__typeof__(p->win_putstr))(uintptr_t)value;return;
case 1:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))(uintptr_t)value;return;
case 2:p->win_start_menu=(__typeof__(p->win_start_menu))(uintptr_t)value;return;
case 3:p->win_end_menu=(__typeof__(p->win_end_menu))(uintptr_t)value;return;
case 4:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))(uintptr_t)value;return;
default:abort();}}
case 27:{struct color_and_attr*p=at;switch(field){
case 0:p->attr=value;return;
default:abort();}}
case 28:{struct instance_flags*p=at;switch(field){
case 0:memmove(&p->menu_headings,(void*)(uintptr_t)value,sizeof p->menu_headings);return;
default:abort();}}
case 29:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
default:abort();}}
case 30:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi_reason=(void*)(uintptr_t)value;return;
case 1:p->mkot_trap_warn_count=value;return;
default:abort();}}
case 31:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(void*)(uintptr_t)value;return;
case 1:p->notonhead=value;return;
default:abort();}}
case 32:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 33:{struct c_color_names*p=at;switch(field){
default:abort();}}
case 34:{struct const_globals*p=at;switch(field){
default:abort();}}
case 35:{struct instance_globals_saved_n*p=at;switch(field){
case 0:p->n_dgns=value;return;
default:abort();}}
case 36:{struct dungeon*p=at;switch(field){
case 0:p->dunlev_ureached=value;return;
case 2:p->depth_start=value;return;
case 3:p->entry_lev=value;return;
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 1:memmove(&p->dungeon_topology,(void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 38:{struct dgn_topology*p=at;switch(field){
case 0:p->d_tutorial_dnum=value;return;
case 1:memmove(&p->d_astral_level,(void*)(uintptr_t)value,sizeof p->d_astral_level);return;
default:abort();}}
case 39:{union any*p=at;switch(field){
case 0:p->a_int=value;return;
default:abort();}}
case 40:{struct mi*p=at;switch(field){
case 0:memmove(&p->item,(void*)(uintptr_t)value,sizeof p->item);return;
default:abort();}}
case 41:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 42:{struct u_have*p=at;switch(field){
case 0:p->amulet=value;return;
default:abort();}}
case 43:{dlevel_t*p=at;switch(field){
case 0:p->monlist=(void*)(uintptr_t)value;return;
default:abort();}}
case 44:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level,(void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 45:{struct q_score*p=at;switch(field){
case 0:p->killed_nemesis=value;return;
default:abort();}}
case 46:{struct instance_globals_saved_q*p=at;switch(field){
case 0:memmove(&p->quest_status,(void*)(uintptr_t)value,sizeof p->quest_status);return;
default:abort();}}
case 47:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 48:{struct rm*p=at;switch(field){
case 0:p->lit=value;return;
case 1:p->waslit=value;return;
case 2:p->typ=value;return;
case 3:p->flags=value;return;
default:abort();}}
case 49:{struct instance_globals_w*p=at;switch(field){
case 0:p->warn_obj_cnt=value;return;
default:abort();}}
case 50:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(void*)(uintptr_t)value;return;
default:abort();}}
case 51:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 52:{struct nhcoord*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_artifact_address(int kind,void*at,int field){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:return (void*)&p->value;
default:abort();}}
case 1:{struct flag*p=at;switch(field){
case 0:return (void*)&p->initalign;
case 1:return (void*)&p->verbose;
case 2:return (void*)&p->female;
default:abort();}}
case 2:{struct artifact*p=at;switch(field){
case 0:return (void*)&p->otyp;
case 1:return (void*)&p->role;
case 2:return (void*)&p->alignment;
case 3:return (void*)&p->name;
case 4:return (void*)&p->spfx;
case 5:return (void*)&p->gift_value;
case 6:return (void*)&p->race;
case 7:return (void*)&p->gen_spe;
case 8:return (void*)&p->cspfx;
case 9:return (void*)&p->mtype;
case 10:return (void*)&p->attk;
case 11:return (void*)&p->defn;
case 12:return (void*)&p->cary;
case 13:return (void*)&p->inv_prop;
case 14:return (void*)&p->cost;
case 15:return (void*)&p->acolor;
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:return (void*)&p->mnum;
case 1:return (void*)&p->questarti;
default:abort();}}
case 4:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
case 1:return (void*)&p->urace;
default:abort();}}
case 5:{struct obj*p=at;switch(field){
case 0:return (void*)&p->otyp;
case 3:return (void*)&p->oartifact;
case 4:return (void*)&p->spe;
case 6:return (void*)&p->age;
case 7:return (void*)&p->where;
case 8:return (void*)&p->ox;
case 9:return (void*)&p->oy;
case 10:return (void*)&p->owornmask;
case 11:return (void*)&p->quan;
case 12:return (void*)&p->nobj;
case 17:return (void*)&p->owt;
case 18:return (void*)&p->oclass;
case 20:return (void*)&p->corpsenm;
case 21:return (void*)&p->cobj;
case 22:return (void*)&p->v;
default:abort();}}
case 6:{struct objclass*p=at;switch(field){
case 1:return (void*)&p->oc_class;
case 2:return (void*)&p->oc_subtyp;
case 5:return (void*)&p->oc_descr_idx;
case 6:return (void*)&p->oc_oprop;
case 7:return (void*)&p->oc_cost;
default:abort();}}
case 7:{struct arti_info*p=at;switch(field){
default:abort();}}
case 8:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->mflags2;
case 1:return (void*)&p->mflags3;
case 2:return (void*)&p->mlet;
case 3:return (void*)&p->mflags1;
case 4:return (void*)&p->maligntyp;
case 5:return (void*)&p->mr;
case 6:return (void*)&p->msize;
case 7:return (void*)&p->msound;
default:abort();}}
case 9:{struct Race*p=at;switch(field){
case 0:return (void*)&p->hatemask;
case 1:return (void*)&p->mnum;
case 2:return (void*)&p->selfmask;
default:abort();}}
case 10:{struct skills*p=at;switch(field){
case 0:return (void*)&p->max_skill;
case 1:return (void*)&p->skill;
default:abort();}}
case 11:{struct you*p=at;switch(field){
case 0:return (void*)&p->weapon_skills;
case 1:return (void*)&p->ugifts;
case 2:return (void*)&p->uprops;
case 3:return (void*)&p->xray_range;
case 4:return (void*)&p->ualign;
case 5:return (void*)&p->ulycn;
case 6:return (void*)&p->umonnum;
case 7:return (void*)&p->umonster;
case 8:return (void*)&p->uenmax;
case 9:return (void*)&p->uen;
case 10:return (void*)&p->uenpeak;
case 11:return (void*)&p->ustuck;
case 12:return (void*)&p->ux;
case 13:return (void*)&p->uy;
case 15:return (void*)&p->mh;
case 16:return (void*)&p->uhp;
case 17:return (void*)&p->uhpmax;
case 18:return (void*)&p->ucreamed;
case 19:return (void*)&p->mhmax;
case 20:return (void*)&p->uz;
case 21:return (void*)&p->uhave;
case 22:return (void*)&p->dx;
case 23:return (void*)&p->dy;
case 24:return (void*)&p->dz;
case 25:return (void*)&p->twoweap;
case 26:return (void*)&p->usteed;
default:abort();}}
case 12:{struct objdescr*p=at;switch(field){
case 0:return (void*)&p->oc_descr;
default:abort();}}
case 13:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return (void*)&p->bases;
default:abort();}}
case 14:{struct attack*p=at;switch(field){
case 0:return (void*)&p->aatyp;
case 1:return (void*)&p->adtyp;
case 2:return (void*)&p->damn;
case 3:return (void*)&p->damd;
default:abort();}}
case 15:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->intrinsic;
case 2:return (void*)&p->blocked;
default:abort();}}
case 16:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 17:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->restoring;
default:abort();}}
case 18:{struct warntype_info*p=at;switch(field){
case 0:return (void*)&p->obj;
default:abort();}}
case 19:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->warntype;
default:abort();}}
case 20:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 21:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->vision_full_recalc;
case 1:return (void*)&p->viz_array;
default:abort();}}
case 22:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 23:{struct align*p=at;switch(field){
case 0:return (void*)&p->type;
case 1:return (void*)&p->record;
default:abort();}}
case 24:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
case 1:return (void*)&p->mx;
case 2:return (void*)&p->my;
case 3:return (void*)&p->mhp;
case 6:return (void*)&p->minvent;
case 7:return (void*)&p->m_lev;
case 8:return (void*)&p->mhpmax;
case 9:return (void*)&p->nmon;
case 11:return (void*)&p->mtame;
default:abort();}}
case 25:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->spec_dbon_applies;
default:abort();}}
case 26:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->win_putstr;
case 1:return (void*)&p->win_create_nhwindow;
case 2:return (void*)&p->win_start_menu;
case 3:return (void*)&p->win_end_menu;
case 4:return (void*)&p->win_destroy_nhwindow;
default:abort();}}
case 27:{struct color_and_attr*p=at;switch(field){
case 0:return (void*)&p->attr;
default:abort();}}
case 28:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->menu_headings;
default:abort();}}
case 29:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
default:abort();}}
case 30:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->multi_reason;
case 1:return (void*)&p->mkot_trap_warn_count;
default:abort();}}
case 31:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->nomovemsg;
case 1:return (void*)&p->notonhead;
default:abort();}}
case 32:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_fakename;
case 1:return (void*)&p->c_Never_mind;
case 2:return (void*)&p->c_nothing_seems_to_happen;
case 3:return (void*)&p->c_nothing_happens;
default:abort();}}
case 33:{struct c_color_names*p=at;switch(field){
case 0:return (void*)&p->c_black;
default:abort();}}
case 34:{struct const_globals*p=at;switch(field){
case 0:return (void*)&p->zeroobj;
case 1:return (void*)&p->zeroany;
default:abort();}}
case 35:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (void*)&p->n_dgns;
default:abort();}}
case 36:{struct dungeon*p=at;switch(field){
case 0:return (void*)&p->dunlev_ureached;
case 1:return (void*)&p->dname;
case 2:return (void*)&p->depth_start;
case 3:return (void*)&p->entry_lev;
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeons;
case 1:return (void*)&p->dungeon_topology;
default:abort();}}
case 38:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_tutorial_dnum;
case 1:return (void*)&p->d_astral_level;
default:abort();}}
case 39:{union any*p=at;switch(field){
case 0:return (void*)&p->a_int;
default:abort();}}
case 40:{struct mi*p=at;switch(field){
case 0:return (void*)&p->item;
default:abort();}}
case 41:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 42:{struct u_have*p=at;switch(field){
default:abort();}}
case 43:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->monlist;
case 1:return (void*)&p->locations;
case 2:return (void*)&p->objects;
default:abort();}}
case 44:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
default:abort();}}
case 45:{struct q_score*p=at;switch(field){
default:abort();}}
case 46:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (void*)&p->quest_status;
default:abort();}}
case 47:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
default:abort();}}
case 48:{struct rm*p=at;switch(field){
case 2:return (void*)&p->typ;
default:abort();}}
case 49:{struct instance_globals_w*p=at;switch(field){
case 0:return (void*)&p->warn_obj_cnt;
default:abort();}}
case 50:{union vptrs*p=at;switch(field){
case 0:return (void*)&p->v_nexthere;
default:abort();}}
case 51:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 52:{struct nhcoord*p=at;switch(field){
default:abort();}}
default:abort();}}
static char artifact_literals[ARTIFACT_LITERAL_CAPACITY];
char*teleport_artifact_literal_storage(void){return artifact_literals;}
size_t teleport_artifact_literal_capacity(void){return sizeof artifact_literals;}
void teleport_artifact_rng_caller(int line,const char*caller){if(rng_log_enabled())rng_log_set_caller("artifact.c",line,caller);}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
void teleport_artifact_impossible_pi(char * a0,int a1){(impossible)(a0,a1);}
void teleport_artifact_livelog_printf_jppp(long a0,char * a1,char * a2,char * a3){(livelog_printf)(a0,a1,a2,a3);}
void teleport_artifact_You_pp(char * a0,char * a1){(You)(a0,a1);}
int teleport_artifact_sprintf_ppp(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_artifact_pline_pp(char * a0,char * a1){(pline)(a0,a1);}
void teleport_artifact_impossible_p(char * a0){(impossible)(a0);}
int teleport_artifact_sprintf_ppppp(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_artifact_nh_snprintf_pipjpppppppppp(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,char * a7,char * a8,char * a9,char * a10,char * a11,char * a12,char * a13){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);}
void teleport_artifact_nh_snprintf_pipjppp(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_artifact_pline_The_ppp(char * a0,char * a1,char * a2){(pline_The)(a0,a1,a2);}
void teleport_artifact_You_p(char * a0){(You)(a0);}
void teleport_artifact_pline_The_pp(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_artifact_pline_ppp(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_artifact_pline_ppppi(char * a0,char * a1,char * a2,char * a3,int a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_artifact_pline_The_pppi(char * a0,char * a1,char * a2,int a3){(pline_The)(a0,a1,a2,a3);}
void teleport_artifact_pline_pppp(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_artifact_pline_p(char * a0){(pline)(a0);}
void teleport_artifact_pline_The_pppp(char * a0,char * a1,char * a2,char * a3){(pline_The)(a0,a1,a2,a3);}
void teleport_artifact_You_feel_ppp(char * a0,char * a1,char * a2){(You_feel)(a0,a1,a2);}
void teleport_artifact_You_feel_p(char * a0){(You_feel)(a0);}
void teleport_artifact_You_feel_pp(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_artifact_Your_pp(char * a0,char * a1){(Your)(a0,a1);}
void teleport_artifact_Your_p(char * a0){(Your)(a0);}
void teleport_artifact_verbalize_pp(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_artifact_You_cant_ppp(char * a0,char * a1,char * a2){(You_cant)(a0,a1,a2);}
void teleport_artifact_pline_The_ppi(char * a0,char * a1,int a2){(pline_The)(a0,a1,a2);}
#pragma clang diagnostic pop
winid teleport_artifact_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_artifact_putstr(winid a0,int a1,const char * a2){putstr(a0,a1,a2);}
void teleport_artifact_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
void teleport_artifact_destroy_nhwindow(winid a0){destroy_nhwindow(a0);}
void teleport_artifact_start_menu(winid a0,unsigned long a1){start_menu(a0,a1);}
void teleport_artifact_end_menu(winid a0,const char * a1){end_menu(a0,a1);}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_artifact_callback_invoke_ok invoke_ok
#else
extern int teleport_artifact_callback_invoke_ok(struct obj * a0);
#endif
uintptr_t teleport_artifact_function_pointer(int kind){switch(kind){
case 37:return(uintptr_t)&teleport_artifact_callback_invoke_ok;
default:abort();}}
uintptr_t teleport_artifact_foreign_function_pointer(int kind){switch(kind){
case 0:return(uintptr_t)&charge_ok;
case 1:return(uintptr_t)&xname;
default:abort();}}
_Static_assert(__builtin_types_compatible_p(__typeof__(&memset),void * (*)(void *,int,size_t)),"ARTIFACT dependency memset");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_arti_info),void (*)(NHFILE *,struct arti_info *,const char *)),"ARTIFACT dependency sfo_arti_info");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_xint16),void (*)(NHFILE *,xint16 *,const char *)),"ARTIFACT dependency sfo_xint16");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfi_arti_info),void (*)(NHFILE *,struct arti_info *,const char *)),"ARTIFACT dependency sfi_arti_info");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfi_short),void (*)(NHFILE *,short *,const char *)),"ARTIFACT dependency sfi_short");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"ARTIFACT dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *,int,const char *)),"ARTIFACT dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"ARTIFACT dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mksobj),struct obj * (*)(int,boolean,boolean)),"ARTIFACT dependency mksobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&__assert_fail),void (*)(const char *,const char *,int,const char *)),"ARTIFACT dependency __assert_fail");
_Static_assert(__builtin_types_compatible_p(__typeof__(&oname),struct obj * (*)(struct obj *,const char *,unsigned int)),"ARTIFACT dependency oname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obj_extract_self),void (*)(struct obj *)),"ARTIFACT dependency obj_extract_self");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obfree),void (*)(struct obj *,struct obj *)),"ARTIFACT dependency obfree");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmpi),int (*)(const char *,const char *,int)),"ARTIFACT dependency strncmpi");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fuzzymatch),boolean (*)(const char *,const char *,const char *,boolean)),"ARTIFACT dependency fuzzymatch");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *,const char *)),"ARTIFACT dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&impossible),void (*)(const char *,...)),"ARTIFACT dependency impossible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&inside_shop),char (*)(coordxy,coordxy)),"ARTIFACT dependency inside_shop");
_Static_assert(__builtin_types_compatible_p(__typeof__(&livelog_printf),void (*)(long,const char *,...)),"ARTIFACT dependency livelog_printf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bare_artifactname),char * (*)(struct obj *)),"ARTIFACT dependency bare_artifactname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obj_shuffle_range),void (*)(int,int *,int *)),"ARTIFACT dependency obj_shuffle_range");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_hallucinated),boolean (*)(long,boolean,long)),"ARTIFACT dependency make_hallucinated");
_Static_assert(__builtin_types_compatible_p(__typeof__(&recalc_telepat_range),void (*)(void)),"ARTIFACT dependency recalc_telepat_range");
_Static_assert(__builtin_types_compatible_p(__typeof__(&see_monsters),void (*)(void)),"ARTIFACT dependency see_monsters");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_aligntyp),aligntyp (*)(struct monst *)),"ARTIFACT dependency mon_aligntyp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You),void (*)(const char *,...)),"ARTIFACT dependency You");
_Static_assert(__builtin_types_compatible_p(__typeof__(&s_suffix),char * (*)(const char *)),"ARTIFACT dependency s_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&the),char * (*)(const char *)),"ARTIFACT dependency the");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xname),char * (*)(struct obj *)),"ARTIFACT dependency xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&d),int (*)(int,int)),"ARTIFACT dependency d");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hates_silver),boolean (*)(struct permonst *)),"ARTIFACT dependency hates_silver");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd),int (*)(int)),"ARTIFACT dependency rnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sprintf),int (*)(char *restrict,const char *restrict,...)),"ARTIFACT dependency sprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losehp),void (*)(int,const char *,schar)),"ARTIFACT dependency losehp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exercise),void (*)(int,boolean)),"ARTIFACT dependency exercise");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline),void (*)(const char *,...)),"ARTIFACT dependency pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Tobjnam),char * (*)(struct obj *,const char *)),"ARTIFACT dependency Tobjnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sgn),int (*)(int)),"ARTIFACT dependency sgn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&defended),boolean (*)(struct monst *,int)),"ARTIFACT dependency defended");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Resists_Elem),boolean (*)(struct monst *,int)),"ARTIFACT dependency Resists_Elem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resists_drli),boolean (*)(struct monst *)),"ARTIFACT dependency resists_drli");
_Static_assert(__builtin_types_compatible_p(__typeof__(&align_str),const char * (*)(aligntyp)),"ARTIFACT dependency align_str");
_Static_assert(__builtin_types_compatible_p(__typeof__(&simple_typename),char * (*)(int)),"ARTIFACT dependency simple_typename");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_snprintf),void (*)(const char *,int,char *,size_t,const char *,...)),"ARTIFACT dependency nh_snprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline_The),void (*)(const char *,...)),"ARTIFACT dependency pline_The");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vtense),char * (*)(const char *,const char *)),"ARTIFACT dependency vtense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"ARTIFACT dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"ARTIFACT dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_invisible),void (*)(coordxy,coordxy)),"ARTIFACT dependency map_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cancel_monst),boolean (*)(struct monst *,struct obj *,boolean,boolean,boolean)),"ARTIFACT dependency cancel_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char * (*)(char *restrict,const char *restrict)),"ARTIFACT dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_nam),char * (*)(struct monst *)),"ARTIFACT dependency mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype),boolean (*)(struct permonst *,int)),"ARTIFACT dependency attacktype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nomul),void (*)(int)),"ARTIFACT dependency nomul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sticks),boolean (*)(struct permonst *)),"ARTIFACT dependency sticks");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_ustuck),void (*)(struct monst *)),"ARTIFACT dependency set_ustuck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resist),int (*)(struct monst *,char,int,int)),"ARTIFACT dependency resist");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monflee),void (*)(struct monst *,int,boolean,boolean)),"ARTIFACT dependency monflee");
_Static_assert(__builtin_types_compatible_p(__typeof__(&abs),int (*)(int)),"ARTIFACT dependency abs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&probe_monster),void (*)(struct monst *)),"ARTIFACT dependency probe_monster");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_stunned),void (*)(long,boolean)),"ARTIFACT dependency make_stunned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_confused),void (*)(long,boolean)),"ARTIFACT dependency make_confused");
_Static_assert(__builtin_types_compatible_p(__typeof__(&upstart),char * (*)(char *)),"ARTIFACT dependency upstart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&shieldeff),void (*)(coordxy,coordxy)),"ARTIFACT dependency shieldeff");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcat),char * (*)(char *restrict,const char *restrict)),"ARTIFACT dependency strcat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&destroy_items),int (*)(struct monst *,int,int)),"ARTIFACT dependency destroy_items");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ignite_items),void (*)(struct obj *)),"ARTIFACT dependency ignite_items");
_Static_assert(__builtin_types_compatible_p(__typeof__(&burn_away_slime),void (*)(void)),"ARTIFACT dependency burn_away_slime");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wake_nearto),void (*)(coordxy,coordxy,int)),"ARTIFACT dependency wake_nearto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Monnam),char * (*)(struct monst *)),"ARTIFACT dependency Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&observe_object),void (*)(struct obj *)),"ARTIFACT dependency observe_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mbodypart),const char * (*)(struct monst *,int)),"ARTIFACT dependency mbodypart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&body_part),const char * (*)(int)),"ARTIFACT dependency body_part");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monhp_per_lvl),int (*)(struct monst *)),"ARTIFACT dependency monhp_per_lvl");
_Static_assert(__builtin_types_compatible_p(__typeof__(&distant_name),char * (*)(struct obj *,char *(*)(struct obj *))),"ARTIFACT dependency distant_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hcolor),const char * (*)(const char *)),"ARTIFACT dependency hcolor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&The),char * (*)(const char *)),"ARTIFACT dependency The");
_Static_assert(__builtin_types_compatible_p(__typeof__(&healup),void (*)(int,int,boolean,boolean)),"ARTIFACT dependency healup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&healmon),int (*)(struct monst *,int,int)),"ARTIFACT dependency healmon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_feel),void (*)(const char *,...)),"ARTIFACT dependency You_feel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losexp),void (*)(const char *)),"ARTIFACT dependency losexp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getobj),struct obj * (*)(const char *,int (*)(struct obj *),unsigned int)),"ARTIFACT dependency getobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&seffects),int (*)(struct obj *)),"ARTIFACT dependency seffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_sick),void (*)(long,const char *,boolean,int)),"ARTIFACT dependency make_sick");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_slimed),void (*)(long,const char *)),"ARTIFACT dependency make_slimed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_blinded),void (*)(long,boolean)),"ARTIFACT dependency make_blinded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&untrap),int (*)(boolean,coordxy,coordxy,struct obj *)),"ARTIFACT dependency untrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&charge_ok),int (*)(struct obj *)),"ARTIFACT dependency charge_ok");
_Static_assert(__builtin_types_compatible_p(__typeof__(&recharge),void (*)(struct obj *,int)),"ARTIFACT dependency recharge");
_Static_assert(__builtin_types_compatible_p(__typeof__(&update_inventory),void (*)(void)),"ARTIFACT dependency update_inventory");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_menu),void (*)(winid,const glyph_info *,const union any *,char,char,int,int,const char *,unsigned int)),"ARTIFACT dependency add_menu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&select_menu),int (*)(winid,int,menu_item **)),"ARTIFACT dependency select_menu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free),void (*)(void *)),"ARTIFACT dependency free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&depth),schar (*)(d_level *)),"ARTIFACT dependency depth");
_Static_assert(__builtin_types_compatible_p(__typeof__(&next_to_u),boolean (*)(void)),"ARTIFACT dependency next_to_u");
_Static_assert(__builtin_types_compatible_p(__typeof__(&goto_level),void (*)(d_level *,boolean,boolean,boolean)),"ARTIFACT dependency goto_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&weight),int (*)(struct obj *)),"ARTIFACT dependency weight");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hold_another_object),struct obj * (*)(struct obj *,const char *,const char *,const char *)),"ARTIFACT dependency hold_another_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&aobjnam),char * (*)(struct obj *,const char *)),"ARTIFACT dependency aobjnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_hell),void (*)(d_level *)),"ARTIFACT dependency find_hell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&isok),int (*)(coordxy,coordxy)),"ARTIFACT dependency isok");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_quest),boolean (*)(d_level *)),"ARTIFACT dependency In_quest");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_hell),boolean (*)(d_level *)),"ARTIFACT dependency In_hell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dunlevs_in_dungeon),xint16 (*)(d_level *)),"ARTIFACT dependency dunlevs_in_dungeon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&migrate_mon),void (*)(struct monst *,xint16,xint16)),"ARTIFACT dependency migrate_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ledger_no),xint16 (*)(d_level *)),"ARTIFACT dependency ledger_no");
_Static_assert(__builtin_types_compatible_p(__typeof__(&u_teleport_mon),boolean (*)(struct monst *,boolean)),"ARTIFACT dependency u_teleport_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&eos),char * (*)(char *)),"ARTIFACT dependency eos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getdir),int (*)(const char *)),"ARTIFACT dependency getdir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&throwit),void (*)(struct obj *,long,boolean,struct obj *)),"ARTIFACT dependency throwit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spell_skilltype),int (*)(int)),"ARTIFACT dependency spell_skilltype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spelleffects),int (*)(int,boolean,boolean)),"ARTIFACT dependency spelleffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_blinding_ray),void (*)(struct obj *)),"ARTIFACT dependency do_blinding_ray");
_Static_assert(__builtin_types_compatible_p(__typeof__(&litroom),void (*)(boolean,struct obj *)),"ARTIFACT dependency litroom");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lightdamage),int (*)(struct obj *,boolean,int)),"ARTIFACT dependency lightdamage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flashburn),boolean (*)(long,boolean)),"ARTIFACT dependency flashburn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&otense),char * (*)(struct obj *,const char *)),"ARTIFACT dependency otense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnz),int (*)(int)),"ARTIFACT dependency rnz");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_crystal_ball),void (*)(struct obj **)),"ARTIFACT dependency use_crystal_ball");
_Static_assert(__builtin_types_compatible_p(__typeof__(&level_tele),void (*)(void)),"ARTIFACT dependency level_tele");
_Static_assert(__builtin_types_compatible_p(__typeof__(&enlightenment),void (*)(int,int)),"ARTIFACT dependency enlightenment");
_Static_assert(__builtin_types_compatible_p(__typeof__(&float_up),void (*)(void)),"ARTIFACT dependency float_up");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spoteffects),void (*)(boolean)),"ARTIFACT dependency spoteffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&float_down),int (*)(long,long)),"ARTIFACT dependency float_down");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy,coordxy)),"ARTIFACT dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Your),void (*)(const char *,...)),"ARTIFACT dependency Your");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getrumor),char * (*)(int,char *,boolean)),"ARTIFACT dependency getrumor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bcsign),int (*)(struct obj *)),"ARTIFACT dependency bcsign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&verbalize),void (*)(const char *,...)),"ARTIFACT dependency verbalize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&clr2colorname),const char * (*)(int)),"ARTIFACT dependency clr2colorname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maybe_lvltport_feedback),void (*)(void)),"ARTIFACT dependency maybe_lvltport_feedback");
_Static_assert(__builtin_types_compatible_p(__typeof__(&invocation_pos),boolean (*)(coordxy,coordxy)),"ARTIFACT dependency invocation_pos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&On_stairs),boolean (*)(coordxy,coordxy)),"ARTIFACT dependency On_stairs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_cant),void (*)(const char *,...)),"ARTIFACT dependency You_cant");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yname),char * (*)(struct obj *)),"ARTIFACT dependency yname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&killer_xname),char * (*)(struct obj *)),"ARTIFACT dependency killer_xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&remove_worn_item),void (*)(struct obj *,boolean)),"ARTIFACT dependency remove_worn_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&freeinv),void (*)(struct obj *)),"ARTIFACT dependency freeinv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hitfloor),void (*)(struct obj *,boolean)),"ARTIFACT dependency hitfloor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&surface),const char * (*)(coordxy,coordxy)),"ARTIFACT dependency surface");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dropx),void (*)(struct obj *)),"ARTIFACT dependency dropx");
_Static_assert(__builtin_types_compatible_p(__typeof__(&clear_bypasses),void (*)(void)),"ARTIFACT dependency clear_bypasses");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bypass_obj),void (*)(struct obj *)),"ARTIFACT dependency bypass_obj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&which_armor),struct obj * (*)(struct monst *,long)),"ARTIFACT dependency which_armor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dismount_steed),void (*)(int)),"ARTIFACT dependency dismount_steed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nxt_unbypassed_obj),struct obj * (*)(struct obj *)),"ARTIFACT dependency nxt_unbypassed_obj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&uncurse),void (*)(struct obj *)),"ARTIFACT dependency uncurse");
_Static_assert(__builtin_types_compatible_p(__typeof__(&selftouch),void (*)(const char *)),"ARTIFACT dependency selftouch");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_at),int (*)(coordxy,coordxy)),"ARTIFACT dependency glyph_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&t_at),struct trap * (*)(coordxy,coordxy)),"ARTIFACT dependency t_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nxtobj),struct obj * (*)(struct obj *,int,boolean)),"ARTIFACT dependency nxtobj");
