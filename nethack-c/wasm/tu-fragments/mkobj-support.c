/* MKOBJ typed ABI/backing only; all config algorithms/tables remain JS. */
#include "mkobj-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "mkobj-source-data.h"
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(va_list)==8 && sizeof(size_t)==8,"MKOBJ memory64 long/pointer/va_list/size_t ABI");
_Static_assert(sizeof(int)==4 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"MKOBJ scalar ABI");
/* Source data/backing is emitted below; no initialized C source mirror. */
static struct icp mkobj_data_mkobjprobs[11];
static struct icp mkobj_data_boxiprobs[9];
static struct icp mkobj_data_rogueprobs[7];
static struct icp mkobj_data_hellprobs[10];
static struct oextra mkobj_data_zerooextra;
static char * mkobj_data_alteration_verbs[20];
static char mkobj_data_dknowns[10];
static int mkobj_data_treefruits[5];
static char mkobj_data_ofmt0[17];
static char mkobj_data_ofmt3[24];
static char mkobj_data_mfmt1[18];
static char mkobj_data_mfmt2[24];
static char * mkobj_data_obj_state_names[10];
static char mkobj_local_where_name_unknown[32];
static unsigned long mkobj_local_sanity_check_worn_wearbits[18];
void*teleport_mkobj_global(int index){switch(index){
case 0:return(void*)&cg;
case 1:return(void*)&svm;
case 2:return(void*)&gi;
case 3:return(void*)&objects;
case 4:return(void*)&svd;
case 5:return(void*)&u;
case 6:return(void*)&svb;
case 7:return(void*)&go;
case 8:return(void*)&obj_descr;
case 9:return(void*)&mons;
case 10:return(void*)&svc;
case 11:return(void*)&svl;
case 12:return(void*)&flags;
case 13:return(void*)&gu;
case 14:return(void*)&gz;
case 15:return(void*)&iflags;
case 16:return(void*)&gv;
case 17:return(void*)&uwep;
case 18:return(void*)&uswapwep;
case 19:return(void*)&gm;
case 20:return(void*)&gb;
case 21:return(void*)&hands_obj;
case 22:return(void*)&gt;
case 23:return(void*)&gk;
case 24:return(void*)&program_state;
case 25:return(void*)&c_common_strings;
case 26:return(void*)&gc;
case 27:return(void*)&uchain;
case 28:return(void*)&uball;
case 29:return(void*)&genders;
case 30:return(void*)&uskin;
case 31:return(void*)&uarm;
case 32:return(void*)&uarmc;
case 33:return(void*)&uarmh;
case 34:return(void*)&uarms;
case 35:return(void*)&uarmg;
case 36:return(void*)&uarmf;
case 37:return(void*)&uarmu;
case 38:return(void*)&uquiver;
case 39:return(void*)&uamul;
case 40:return(void*)&uleft;
case 41:return(void*)&uright;
case 42:return(void*)&ublindf;
case 43:return(void*)&def_oc_syms;
case 44:return(void*)&mkobj_data_mkobjprobs;
case 45:return(void*)&mkobj_data_boxiprobs;
case 46:return(void*)&mkobj_data_rogueprobs;
case 47:return(void*)&mkobj_data_hellprobs;
case 48:return(void*)&mkobj_data_zerooextra;
case 49:return(void*)&mkobj_data_alteration_verbs;
case 50:return(void*)&mkobj_data_dknowns;
case 51:return(void*)&mkobj_data_treefruits;
case 52:return(void*)&mkobj_data_ofmt0;
case 53:return(void*)&mkobj_data_ofmt3;
case 54:return(void*)&mkobj_data_mfmt1;
case 55:return(void*)&mkobj_data_mfmt2;
case 56:return(void*)&mkobj_data_obj_state_names;
case 57:return(void*)&mkobj_local_where_name_unknown;
case 58:return(void*)&mkobj_local_sanity_check_worn_wearbits;
default:abort();}}
uint64_t teleport_mkobj_read(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->his);
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{struct achievement_tracking*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mines_prize_oid);
case 1:return(uint64_t)(uintptr_t)(p->soko_prize_oid);
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_obj);
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_nothing_happens);
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroobj);
case 1:return(uint64_t)(uintptr_t)(&p->zeromonst);
default:abort();}}
case 7:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ident);
case 1:return(uint64_t)(uintptr_t)(p->current_fruit);
case 2:return(uint64_t)(uintptr_t)(p->made_amulet);
case 3:return(uint64_t)(uintptr_t)(&p->tin);
case 4:return(uint64_t)(uintptr_t)(&p->objsplit);
case 5:return(uint64_t)(uintptr_t)(&p->achieveo);
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_rogue_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_air_level);
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(p->objlist);
case 3:return(uint64_t)(uintptr_t)(p->buriedobjlist);
case 4:return(uint64_t)(uintptr_t)(p->monlist);
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->made_fruit);
default:abort();}}
case 12:{struct icp*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->iprob);
case 1:return(uint64_t)(uintptr_t)(p->iclass);
default:abort();}}
case 13:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->partly_eaten_hack);
case 1:return(uint64_t)(uintptr_t)(p->last_msg);
case 2:return(uint64_t)(uintptr_t)(p->override_ID);
case 3:return(uint64_t)(uintptr_t)(p->suppress_price);
case 4:return(uint64_t)(uintptr_t)(p->returning_missile);
default:abort();}}
case 14:{struct instance_globals_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->billobjs);
default:abort();}}
case 15:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->current_wand);
default:abort();}}
case 16:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_mklev);
case 1:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 17:{struct instance_globals_k*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->kickedobj);
default:abort();}}
case 18:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->migrating_objs);
case 1:return(uint64_t)(uintptr_t)(p->mydogs);
case 2:return(uint64_t)(uintptr_t)(p->migrating_mons);
case 3:return(uint64_t)(uintptr_t)(p->mkcorpstat_norevive);
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->objs_deleted);
case 1:return(uint64_t)(uintptr_t)(&p->oclass_prob_totals);
case 2:return(uint64_t)(uintptr_t)(p->oldcap);
default:abort();}}
case 20:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bases);
default:abort();}}
case 21:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 22:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 24:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->moves);
case 1:return(uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->thrownobj);
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 27:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 28:{struct instance_globals_z*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->zombify);
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nmon);
case 1:return(uint64_t)(uintptr_t)(p->data);
case 2:return(uint64_t)(uintptr_t)(p->m_id);
case 3:return(uint64_t)(uintptr_t)(p->mnum);
case 4:return(uint64_t)(uintptr_t)(p->mx);
case 5:return(uint64_t)(uintptr_t)(p->my);
case 6:return(uint64_t)(uintptr_t)(p->mhp);
case 7:return(uint64_t)(uintptr_t)(p->mhpmax);
case 8:return(uint64_t)(uintptr_t)(p->mcan);
case 9:return(uint64_t)(uintptr_t)(p->mleashed);
case 10:return(uint64_t)(uintptr_t)(p->ispriest);
case 11:return(uint64_t)(uintptr_t)(p->wormno);
case 12:return(uint64_t)(uintptr_t)(p->mstate);
case 13:return(uint64_t)(uintptr_t)(p->minvent);
case 14:return(uint64_t)(uintptr_t)(p->mw);
case 15:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(&p->v);
case 2:return(uint64_t)(uintptr_t)(p->cobj);
case 3:return(uint64_t)(uintptr_t)(p->o_id);
case 4:return(uint64_t)(uintptr_t)(p->ox);
case 5:return(uint64_t)(uintptr_t)(p->oy);
case 6:return(uint64_t)(uintptr_t)(p->otyp);
case 7:return(uint64_t)(uintptr_t)(p->owt);
case 8:return(uint64_t)(uintptr_t)(p->quan);
case 9:return(uint64_t)(uintptr_t)(p->spe);
case 10:return(uint64_t)(uintptr_t)(p->oclass);
case 11:return(uint64_t)(uintptr_t)(p->oartifact);
case 12:return(uint64_t)(uintptr_t)(p->where);
case 13:return(uint64_t)(uintptr_t)(p->timed);
case 14:return(uint64_t)(uintptr_t)(p->cursed);
case 15:return(uint64_t)(uintptr_t)(p->blessed);
case 16:return(uint64_t)(uintptr_t)(p->unpaid);
case 17:return(uint64_t)(uintptr_t)(p->no_charge);
case 18:return(uint64_t)(uintptr_t)(p->recharged);
case 19:return(uint64_t)(uintptr_t)(p->lamplit);
case 20:return(uint64_t)(uintptr_t)(p->known);
case 21:return(uint64_t)(uintptr_t)(p->dknown);
case 22:return(uint64_t)(uintptr_t)(p->bknown);
case 23:return(uint64_t)(uintptr_t)(p->rknown);
case 24:return(uint64_t)(uintptr_t)(p->cknown);
case 25:return(uint64_t)(uintptr_t)(p->lknown);
case 26:return(uint64_t)(uintptr_t)(p->tknown);
case 27:return(uint64_t)(uintptr_t)(p->nomerge);
case 28:return(uint64_t)(uintptr_t)(p->oeroded);
case 29:return(uint64_t)(uintptr_t)(p->oeroded2);
case 30:return(uint64_t)(uintptr_t)(p->oerodeproof);
case 31:return(uint64_t)(uintptr_t)(p->olocked);
case 32:return(uint64_t)(uintptr_t)(p->otrapped);
case 33:return(uint64_t)(uintptr_t)(p->globby);
case 34:return(uint64_t)(uintptr_t)(p->greased);
case 35:return(uint64_t)(uintptr_t)(p->in_use);
case 36:return(uint64_t)(uintptr_t)(p->bypass);
case 37:return(uint64_t)(uintptr_t)(p->pickup_prev);
case 38:return(uint64_t)(uintptr_t)(p->how_lost);
case 39:return(uint64_t)(uintptr_t)(p->corpsenm);
case 40:return(uint64_t)(uintptr_t)(p->usecount);
case 41:return(uint64_t)(uintptr_t)(p->oeaten);
case 42:return(uint64_t)(uintptr_t)(p->age);
case 43:return(uint64_t)(uintptr_t)(p->owornmask);
case 44:return(uint64_t)(uintptr_t)(p->lua_ref_cnt);
case 45:return(uint64_t)(uintptr_t)(p->omigr_from_dnum);
case 46:return(uint64_t)(uintptr_t)(p->omigr_from_dlevel);
case 47:return(uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 32:{struct obj_split*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->parent_oid);
case 1:return(uint64_t)(uintptr_t)(p->child_oid);
default:abort();}}
case 33:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name_idx);
case 1:return(uint64_t)(uintptr_t)(p->oc_merge);
case 2:return(uint64_t)(uintptr_t)(p->oc_uses_known);
case 3:return(uint64_t)(uintptr_t)(p->oc_magic);
case 4:return(uint64_t)(uintptr_t)(p->oc_charged);
case 5:return(uint64_t)(uintptr_t)(p->oc_unique);
case 6:return(uint64_t)(uintptr_t)(p->oc_big);
case 7:return(uint64_t)(uintptr_t)(p->oc_dir);
case 8:return(uint64_t)(uintptr_t)(p->oc_material);
case 9:return(uint64_t)(uintptr_t)(p->oc_subtyp);
case 10:return(uint64_t)(uintptr_t)(p->oc_oprop);
case 11:return(uint64_t)(uintptr_t)(p->oc_class);
case 12:return(uint64_t)(uintptr_t)(p->oc_prob);
case 13:return(uint64_t)(uintptr_t)(p->oc_weight);
case 14:return(uint64_t)(uintptr_t)(p->oc_cost);
default:abort();}}
case 34:{struct objdescr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name);
default:abort();}}
case 35:{struct oextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oname);
case 1:return(uint64_t)(uintptr_t)(p->omonst);
case 2:return(uint64_t)(uintptr_t)(p->omailcmd);
case 3:return(uint64_t)(uintptr_t)(p->omid);
default:abort();}}
case 36:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->pmidx);
case 1:return(uint64_t)(uintptr_t)(p->mlet);
case 2:return(uint64_t)(uintptr_t)(p->mlevel);
case 3:return(uint64_t)(uintptr_t)(p->geno);
case 4:return(uint64_t)(uintptr_t)(p->cwt);
case 5:return(uint64_t)(uintptr_t)(p->cnutrit);
case 6:return(uint64_t)(uintptr_t)(p->msize);
case 7:return(uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 37:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 38:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
default:abort();}}
case 39:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->freeingdata);
default:abort();}}
case 40:{struct tin_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tin);
case 1:return(uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 41:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
case 1:return(uint64_t)(uintptr_t)(p->v_ocontainer);
case 2:return(uint64_t)(uintptr_t)(p->v_ocarry);
default:abort();}}
case 42:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(&p->uz);
case 3:return(uint64_t)(uintptr_t)(&p->ushops);
case 4:return(uint64_t)(uintptr_t)(&p->uprops);
case 5:return(uint64_t)(uintptr_t)(p->uswallow);
case 6:return(uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
default:abort();}}
void teleport_mkobj_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:p->his=(const char *)value;return;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:p->mnum=(short)value;return;
default:abort();}}
case 2:{struct achievement_tracking*p=at;switch(field){
case 0:p->mines_prize_oid=(unsigned int)value;return;
case 1:p->soko_prize_oid=(unsigned int)value;return;
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:p->a_obj=(struct obj *)value;return;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:p->name=(const char *)value;return;
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
default:abort();}}
case 7:{struct context_info*p=at;switch(field){
case 0:p->ident=(unsigned int)value;return;
case 1:p->current_fruit=(int)value;return;
case 2:p->made_amulet=(boolean)value;return;
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:p->dnum=(xint16)value;return;
case 1:p->dlevel=(xint16)value;return;
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 2:p->objlist=(struct obj *)value;return;
case 3:p->buriedobjlist=(struct obj *)value;return;
case 4:p->monlist=(struct monst *)value;return;
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:p->made_fruit=(boolean)value;return;
default:abort();}}
case 12:{struct icp*p=at;switch(field){
case 0:p->iprob=(int)value;return;
case 1:p->iclass=(char)value;return;
default:abort();}}
case 13:{struct instance_flags*p=at;switch(field){
case 0:p->partly_eaten_hack=(boolean)value;return;
case 1:p->last_msg=(int)value;return;
case 2:p->override_ID=(int)value;return;
case 3:p->suppress_price=(int)value;return;
case 4:p->returning_missile=(genericptr_t)value;return;
default:abort();}}
case 14:{struct instance_globals_b*p=at;switch(field){
case 0:p->billobjs=(struct obj *)value;return;
default:abort();}}
case 15:{struct instance_globals_c*p=at;switch(field){
case 0:p->current_wand=(struct obj *)value;return;
default:abort();}}
case 16:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_mklev=(boolean)value;return;
case 1:p->invent=(struct obj *)value;return;
default:abort();}}
case 17:{struct instance_globals_k*p=at;switch(field){
case 0:p->kickedobj=(struct obj *)value;return;
default:abort();}}
case 18:{struct instance_globals_m*p=at;switch(field){
case 0:p->migrating_objs=(struct obj *)value;return;
case 1:p->mydogs=(struct monst *)value;return;
case 2:p->migrating_mons=(struct monst *)value;return;
case 3:p->mkcorpstat_norevive=(boolean)value;return;
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:p->objs_deleted=(struct obj *)value;return;
case 2:p->oldcap=(int)value;return;
default:abort();}}
case 20:{struct instance_globals_saved_b*p=at;switch(field){
default:abort();}}
case 21:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=(long)value;return;
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:p->thrownobj=(struct obj *)value;return;
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(seenV **)value;return;
default:abort();}}
case 28:{struct instance_globals_z*p=at;switch(field){
case 0:p->zombify=(boolean)value;return;
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:p->nmon=(struct monst *)value;return;
case 1:p->data=(struct permonst *)value;return;
case 2:p->m_id=(unsigned int)value;return;
case 3:p->mnum=(short)value;return;
case 4:p->mx=(coordxy)value;return;
case 5:p->my=(coordxy)value;return;
case 6:p->mhp=(int)value;return;
case 7:p->mhpmax=(int)value;return;
case 8:p->mcan=(unsigned int)value;return;
case 9:p->mleashed=(unsigned int)value;return;
case 10:p->ispriest=(unsigned int)value;return;
case 11:p->wormno=(unsigned int)value;return;
case 12:p->mstate=(long)value;return;
case 13:p->minvent=(struct obj *)value;return;
case 14:p->mw=(struct obj *)value;return;
case 15:p->mextra=(struct mextra *)value;return;
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:p->mvflags=(uchar)value;return;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:p->nobj=(struct obj *)value;return;
case 2:p->cobj=(struct obj *)value;return;
case 3:p->o_id=(unsigned int)value;return;
case 4:p->ox=(coordxy)value;return;
case 5:p->oy=(coordxy)value;return;
case 6:p->otyp=(short)value;return;
case 7:p->owt=(unsigned int)value;return;
case 8:p->quan=(long)value;return;
case 9:p->spe=(schar)value;return;
case 10:p->oclass=(char)value;return;
case 11:p->oartifact=(char)value;return;
case 12:p->where=(xint8)value;return;
case 13:p->timed=(xint16)value;return;
case 14:p->cursed=(unsigned int)value;return;
case 15:p->blessed=(unsigned int)value;return;
case 16:p->unpaid=(unsigned int)value;return;
case 17:p->no_charge=(unsigned int)value;return;
case 18:p->recharged=(unsigned int)value;return;
case 19:p->lamplit=(unsigned int)value;return;
case 20:p->known=(unsigned int)value;return;
case 21:p->dknown=(unsigned int)value;return;
case 22:p->bknown=(unsigned int)value;return;
case 23:p->rknown=(unsigned int)value;return;
case 24:p->cknown=(unsigned int)value;return;
case 25:p->lknown=(unsigned int)value;return;
case 26:p->tknown=(unsigned int)value;return;
case 27:p->nomerge=(unsigned int)value;return;
case 28:p->oeroded=(unsigned int)value;return;
case 29:p->oeroded2=(unsigned int)value;return;
case 30:p->oerodeproof=(unsigned int)value;return;
case 31:p->olocked=(unsigned int)value;return;
case 32:p->otrapped=(unsigned int)value;return;
case 33:p->globby=(unsigned int)value;return;
case 34:p->greased=(unsigned int)value;return;
case 35:p->in_use=(unsigned int)value;return;
case 36:p->bypass=(unsigned int)value;return;
case 37:p->pickup_prev=(unsigned int)value;return;
case 38:p->how_lost=(unsigned int)value;return;
case 39:p->corpsenm=(int)value;return;
case 40:p->usecount=(int)value;return;
case 41:p->oeaten=(unsigned int)value;return;
case 42:p->age=(long)value;return;
case 43:p->owornmask=(long)value;return;
case 44:p->lua_ref_cnt=(unsigned int)value;return;
case 45:p->omigr_from_dnum=(xint16)value;return;
case 46:p->omigr_from_dlevel=(xint16)value;return;
case 47:p->oextra=(struct oextra *)value;return;
default:abort();}}
case 32:{struct obj_split*p=at;switch(field){
case 0:p->parent_oid=(unsigned int)value;return;
case 1:p->child_oid=(unsigned int)value;return;
default:abort();}}
case 33:{struct objclass*p=at;switch(field){
case 0:p->oc_name_idx=(short)value;return;
case 1:p->oc_merge=(unsigned int)value;return;
case 2:p->oc_uses_known=(unsigned int)value;return;
case 3:p->oc_magic=(unsigned int)value;return;
case 4:p->oc_charged=(unsigned int)value;return;
case 5:p->oc_unique=(unsigned int)value;return;
case 6:p->oc_big=(unsigned int)value;return;
case 7:p->oc_dir=(unsigned int)value;return;
case 8:p->oc_material=(unsigned int)value;return;
case 9:p->oc_subtyp=(schar)value;return;
case 10:p->oc_oprop=(uchar)value;return;
case 11:p->oc_class=(char)value;return;
case 12:p->oc_prob=(short)value;return;
case 13:p->oc_weight=(unsigned int)value;return;
case 14:p->oc_cost=(short)value;return;
default:abort();}}
case 34:{struct objdescr*p=at;switch(field){
case 0:p->oc_name=(const char *)value;return;
default:abort();}}
case 35:{struct oextra*p=at;switch(field){
case 0:p->oname=(char *)value;return;
case 1:p->omonst=(struct monst *)value;return;
case 2:p->omailcmd=(char *)value;return;
case 3:p->omid=(unsigned int)value;return;
default:abort();}}
case 36:{struct permonst*p=at;switch(field){
case 1:p->mlet=(char)value;return;
case 2:p->mlevel=(schar)value;return;
case 3:p->geno=(unsigned short)value;return;
case 4:p->cwt=(unsigned int)value;return;
case 5:p->cnutrit=(unsigned short)value;return;
case 6:p->msize=(uchar)value;return;
case 7:p->mflags2=(unsigned long)value;return;
default:abort();}}
case 37:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(long)value;return;
case 1:p->blocked=(long)value;return;
case 2:p->intrinsic=(long)value;return;
default:abort();}}
case 38:{struct rm*p=at;switch(field){
case 0:p->typ=(schar)value;return;
default:abort();}}
case 39:{struct sinfo*p=at;switch(field){
case 0:p->freeingdata=(int)value;return;
default:abort();}}
case 40:{struct tin_info*p=at;switch(field){
case 0:p->tin=(struct obj *)value;return;
case 1:p->o_id=(unsigned int)value;return;
default:abort();}}
case 41:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(struct obj *)value;return;
case 1:p->v_ocontainer=(struct obj *)value;return;
case 2:p->v_ocarry=(struct monst *)value;return;
default:abort();}}
case 42:{struct you*p=at;switch(field){
case 0:p->ux=(coordxy)value;return;
case 1:p->uy=(coordxy)value;return;
case 5:p->uswallow=(unsigned int)value;return;
case 6:p->twoweap=(boolean)value;return;
default:abort();}}
default:abort();}}
void* teleport_mkobj_address(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->his;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{struct achievement_tracking*p=at;switch(field){
case 0:return(void*)&p->mines_prize_oid;
case 1:return(void*)&p->soko_prize_oid;
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:return(void*)&p->a_obj;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_nothing_happens;
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:return(void*)&p->name;
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroobj;
case 1:return(void*)&p->zeromonst;
default:abort();}}
case 7:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->ident;
case 1:return(void*)&p->current_fruit;
case 2:return(void*)&p->made_amulet;
case 3:return(void*)&p->tin;
case 4:return(void*)&p->objsplit;
case 5:return(void*)&p->achieveo;
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_rogue_level;
case 1:return(void*)&p->d_water_level;
case 2:return(void*)&p->d_air_level;
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->objlist;
case 3:return(void*)&p->buriedobjlist;
case 4:return(void*)&p->monlist;
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(void*)&p->made_fruit;
default:abort();}}
case 12:{struct icp*p=at;switch(field){
case 0:return(void*)&p->iprob;
case 1:return(void*)&p->iclass;
default:abort();}}
case 13:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->partly_eaten_hack;
case 1:return(void*)&p->last_msg;
case 2:return(void*)&p->override_ID;
case 3:return(void*)&p->suppress_price;
case 4:return(void*)&p->returning_missile;
default:abort();}}
case 14:{struct instance_globals_b*p=at;switch(field){
case 0:return(void*)&p->billobjs;
default:abort();}}
case 15:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->current_wand;
default:abort();}}
case 16:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_mklev;
case 1:return(void*)&p->invent;
default:abort();}}
case 17:{struct instance_globals_k*p=at;switch(field){
case 0:return(void*)&p->kickedobj;
default:abort();}}
case 18:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->migrating_objs;
case 1:return(void*)&p->mydogs;
case 2:return(void*)&p->migrating_mons;
case 3:return(void*)&p->mkcorpstat_norevive;
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->objs_deleted;
case 1:return(void*)&p->oclass_prob_totals;
case 2:return(void*)&p->oldcap;
default:abort();}}
case 20:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(void*)&p->bases;
default:abort();}}
case 21:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 22:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 24:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->moves;
case 1:return(void*)&p->mvitals;
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->thrownobj;
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
default:abort();}}
case 27:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->viz_array;
default:abort();}}
case 28:{struct instance_globals_z*p=at;switch(field){
case 0:return(void*)&p->zombify;
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:return(void*)&p->nmon;
case 1:return(void*)&p->data;
case 2:return(void*)&p->m_id;
case 3:return(void*)&p->mnum;
case 4:return(void*)&p->mx;
case 5:return(void*)&p->my;
case 6:return(void*)&p->mhp;
case 7:return(void*)&p->mhpmax;
case 12:return(void*)&p->mstate;
case 13:return(void*)&p->minvent;
case 14:return(void*)&p->mw;
case 15:return(void*)&p->mextra;
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:return(void*)&p->mvflags;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->v;
case 2:return(void*)&p->cobj;
case 3:return(void*)&p->o_id;
case 4:return(void*)&p->ox;
case 5:return(void*)&p->oy;
case 6:return(void*)&p->otyp;
case 7:return(void*)&p->owt;
case 8:return(void*)&p->quan;
case 9:return(void*)&p->spe;
case 10:return(void*)&p->oclass;
case 11:return(void*)&p->oartifact;
case 12:return(void*)&p->where;
case 13:return(void*)&p->timed;
case 39:return(void*)&p->corpsenm;
case 40:return(void*)&p->usecount;
case 41:return(void*)&p->oeaten;
case 42:return(void*)&p->age;
case 43:return(void*)&p->owornmask;
case 44:return(void*)&p->lua_ref_cnt;
case 45:return(void*)&p->omigr_from_dnum;
case 46:return(void*)&p->omigr_from_dlevel;
case 47:return(void*)&p->oextra;
default:abort();}}
case 32:{struct obj_split*p=at;switch(field){
case 0:return(void*)&p->parent_oid;
case 1:return(void*)&p->child_oid;
default:abort();}}
case 33:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_name_idx;
case 9:return(void*)&p->oc_subtyp;
case 10:return(void*)&p->oc_oprop;
case 11:return(void*)&p->oc_class;
case 12:return(void*)&p->oc_prob;
case 13:return(void*)&p->oc_weight;
case 14:return(void*)&p->oc_cost;
default:abort();}}
case 34:{struct objdescr*p=at;switch(field){
case 0:return(void*)&p->oc_name;
default:abort();}}
case 35:{struct oextra*p=at;switch(field){
case 0:return(void*)&p->oname;
case 1:return(void*)&p->omonst;
case 2:return(void*)&p->omailcmd;
case 3:return(void*)&p->omid;
default:abort();}}
case 36:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->pmidx;
case 1:return(void*)&p->mlet;
case 2:return(void*)&p->mlevel;
case 3:return(void*)&p->geno;
case 4:return(void*)&p->cwt;
case 5:return(void*)&p->cnutrit;
case 6:return(void*)&p->msize;
case 7:return(void*)&p->mflags2;
default:abort();}}
case 37:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 38:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
default:abort();}}
case 39:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->freeingdata;
default:abort();}}
case 40:{struct tin_info*p=at;switch(field){
case 0:return(void*)&p->tin;
case 1:return(void*)&p->o_id;
default:abort();}}
case 41:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
case 1:return(void*)&p->v_ocontainer;
case 2:return(void*)&p->v_ocarry;
default:abort();}}
case 42:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->uz;
case 3:return(void*)&p->ushops;
case 4:return(void*)&p->uprops;
case 6:return(void*)&p->twoweap;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_mkobj_var0(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_mkobj_var1(char * a0,char * a1,long a2,long a3){(panic)(a0,a1,a2,a3);}
void teleport_mkobj_var2(char * a0){(panic)(a0);}
void teleport_mkobj_var3(char * a0,int a1){(impossible)(a0,a1);}
void teleport_mkobj_var4(char * a0,char * a1,char * a2,char * a3,char * a4){(verbalize)(a0,a1,a2,a3,a4);}
void teleport_mkobj_var5(char * a0,char * a1,char * a2,char * a3){(verbalize)(a0,a1,a2,a3);}
void teleport_mkobj_var6(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
void teleport_mkobj_var7(char * a0,int a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_mkobj_var8(char * a0,int a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_mkobj_var9(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_mkobj_var10(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_mkobj_var11(char * a0,char * a1){(pline)(a0,a1);}
void teleport_mkobj_var12(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_mkobj_var13(char * a0,long a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_mkobj_var14(char * a0,int a1){(impossible)(a0,a1);}
void teleport_mkobj_var15(void (*fn)(const char *, ...),char * a0,char * a1,int a2,int a3,int a4){(fn)(a0,a1,a2,a3,a4);}
void teleport_mkobj_var16(char * a0,char * a1,int a2){(panic)(a0,a1,a2);}
void teleport_mkobj_var17(char * a0,char * a1,long a2,long a3){(pline)(a0,a1,a2,a3);}
void teleport_mkobj_var18(char * a0,long a1){(pline)(a0,a1);}
void teleport_mkobj_var19(char * a0,char * a1,int a2,int a3){(pline)(a0,a1,a2,a3);}
void teleport_mkobj_var20(char * a0,char * a1,int a2,int a3){(pline)(a0,a1,a2,a3);}
void teleport_mkobj_var21(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkobj_var22(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkobj_var23(char * a0){(panic)(a0);}
void teleport_mkobj_var24(char * a0){(panic)(a0);}
void teleport_mkobj_var25(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkobj_var26(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkobj_var27(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkobj_var28(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_mkobj_var29(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkobj_var30(char * a0,int a1){(impossible)(a0,a1);}
void teleport_mkobj_var31(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
void teleport_mkobj_var32(char * a0){(panic)(a0);}
void teleport_mkobj_var33(char * a0){(panic)(a0);}
void teleport_mkobj_var34(char * a0){(impossible)(a0);}
void teleport_mkobj_var35(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkobj_var36(char * a0){(impossible)(a0);}
void teleport_mkobj_var37(char * a0,char * a1){(pline)(a0,a1);}
void teleport_mkobj_var38(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_mkobj_var39(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
int teleport_mkobj_var40(char * a0,char * a1,int a2,int a3,int a4,int a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_mkobj_var41(char * a0,char * a1,int a2,int a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_mkobj_var42(char * a0,char * a1,int a2,int a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_mkobj_var43(char * a0){(impossible)(a0);}
int teleport_mkobj_var44(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_mkobj_var45(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
int teleport_mkobj_var46(char * a0,char * a1,unsigned int a2){return (sprintf)(a0,a1,a2);}
int teleport_mkobj_var47(char * a0,char * a1,unsigned int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_mkobj_var48(char * a0,char * a1,unsigned int a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_mkobj_var49(char * a0,char * a1,unsigned int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_mkobj_var50(char * a0,char * a1,unsigned int a2,char * a3,unsigned int a4,char * a5){(impossible)(a0,a1,a2,a3,a4,a5);}
int teleport_mkobj_var51(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_mkobj_var52(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_mkobj_var53(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5,char * a6){(impossible)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_mkobj_var54(char * a0,char * a1,char * a2,char * a3,char * a4){(impossible)(a0,a1,a2,a3,a4);}
void teleport_mkobj_var55(char * a0){(panic)(a0);}
void teleport_mkobj_var56(char * a0,char * a1,char * a2,char * a3,char * a4){(impossible)(a0,a1,a2,a3,a4);}
void teleport_mkobj_var57(char * a0){(panic)(a0);}
int teleport_mkobj_var58(char * a0,char * a1,int a2,long a3,unsigned int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_mkobj_var59(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
int teleport_mkobj_var60(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
int teleport_mkobj_var61(char * a0,char * a1,long a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_mkobj_var62(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_mkobj_var63(char * a0){(impossible)(a0);}
void teleport_mkobj_var64(char * a0){(impossible)(a0);}
void teleport_mkobj_var65(char * a0){(impossible)(a0);}
void teleport_mkobj_var66(char * a0){(You_see)(a0);}
void teleport_mkobj_var67(char * a0){(Your)(a0);}
void teleport_mkobj_var68(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_mkobj_var69(char * a0){(You_hear)(a0);}
#pragma clang diagnostic pop
void*teleport_mkobj_copy(void*to,const void*from,size_t n){return memcpy(to,from,n);}
extern void teleport_mkobj_init_oextra(struct oextra * oex);
extern boolean teleport_mkobj_may_generate_eroded(struct obj * otmp);
extern void teleport_mkobj_mkobj_erosions(struct obj * otmp);
extern void teleport_mkobj_mkbox_cnts(struct obj * box);
extern unsigned int teleport_mkobj_nextoid(struct obj * oldobj,struct obj * newobj);
extern void teleport_mkobj_mksobj_init(struct obj ** obj,boolean artif);
extern int teleport_mkobj_item_on_ice(struct obj * item);
extern void teleport_mkobj_shrinking_glob_gone(struct obj * obj);
extern struct obj * teleport_mkobj_save_mtraits(struct obj * obj,struct monst * mtmp);
extern void teleport_mkobj_obj_timer_checks(struct obj * otmp,coordxy x,coordxy y,int force);
extern void teleport_mkobj_dealloc_obj_real(struct obj * obj);
extern void teleport_mkobj_objlist_sanity(struct obj * objlist,int wheretype,const char * mesg);
extern void teleport_mkobj_shop_obj_sanity(struct obj * obj,const char * mesg);
extern void teleport_mkobj_mon_obj_sanity(struct monst * monlist,const char * mesg);
extern void teleport_mkobj_insane_obj_bits(struct obj * obj,struct monst * mon);
extern boolean teleport_mkobj_nomerge_exception(struct obj * obj);
extern const char * teleport_mkobj_where_name(struct obj * obj);
extern void teleport_mkobj_insane_object(struct obj * obj,const char * fmt,const char * mesg,struct monst * mon);
extern void teleport_mkobj_check_contained(struct obj * container,const char * mesg);
extern void teleport_mkobj_check_glob(struct obj * obj,const char * mesg);
extern void teleport_mkobj_sanity_check_worn(struct obj * obj);
uintptr_t teleport_mkobj_function0(void){return(uintptr_t)panic;}
uintptr_t teleport_mkobj_function1(void){return(uintptr_t)impossible;}
#include "mkobj-source-data.h"
static char mkobj_literals[MKOBJ_LITERAL_CAPACITY];
char*teleport_mkobj_literal_storage(void){return mkobj_literals;}
size_t teleport_mkobj_literal_capacity(void){return sizeof mkobj_literals;}
