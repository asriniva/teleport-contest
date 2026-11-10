/* PRAY typed ABI/backing only; all config algorithms/tables remain JS. */
#include "pray-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "pray-source-data.h"
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(va_list)==8 && sizeof(size_t)==8,"PRAY memory64 long/pointer/va_list/size_t ABI");
_Static_assert(sizeof(int)==4 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"PRAY scalar ABI");
static char pray_local_statics[PRAY_LOCAL_STATIC_BYTES];
void*teleport_pray_global(int index){switch(index){
case 0:return(void*)&u;
case 1:return(void*)&svl;
case 2:return(void*)&gy;
case 3:return(void*)&uarmf;
case 4:return(void*)&uleft;
case 5:return(void*)&uright;
case 6:return(void*)&uwep;
case 7:return(void*)&ublindf;
case 8:return(void*)&uball;
case 9:return(void*)&uarmg;
case 10:return(void*)&gi;
case 11:return(void*)&objects;
case 12:return(void*)&uarms;
case 13:return(void*)&uarmc;
case 14:return(void*)&uarm;
case 15:return(void*)&uarmh;
case 16:return(void*)&uarmu;
case 17:return(void*)&uamul;
case 18:return(void*)&uswapwep;
case 19:return(void*)&c_color_names;
case 20:return(void*)&iflags;
case 21:return(void*)&disp;
case 22:return(void*)&mons;
case 23:return(void*)&svd;
case 24:return(void*)&genders;
case 25:return(void*)&flags;
case 26:return(void*)&svk;
case 27:return(void*)&c_common_strings;
case 28:return(void*)&gu;
case 29:return(void*)&svb;
case 30:return(void*)&obj_descr;
case 31:return(void*)&gp;
case 32:return(void*)&svt;
case 33:return(void*)&svm;
case 34:return(void*)&WIN_MESSAGE;
case 35:return(void*)&windowprocs;
case 36:return(void*)&gm;
case 37:return(void*)&gn;
case 38:return(void*)&ynchars;
case 39:return(void*)&ga;
case 40:return(void*)&gv;
case 41:return(void*)&roles;
case 42:return pray_local_statics;
default:abort();}}
uint64_t teleport_pray_read(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->him);
case 1:return(uint64_t)(uintptr_t)(p->his);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->adj);
case 1:return(uint64_t)(uintptr_t)(p->selfmask);
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lgod);
case 1:return(uint64_t)(uintptr_t)(p->ngod);
case 2:return(uint64_t)(uintptr_t)(p->cgod);
case 3:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->type);
case 1:return(uint64_t)(uintptr_t)(p->record);
default:abort();}}
case 4:{struct attribs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->a);
default:abort();}}
case 5:{struct c_color_names*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_black);
case 1:return(uint64_t)(uintptr_t)(p->c_amber);
case 2:return(uint64_t)(uintptr_t)(p->c_golden);
case 3:return(uint64_t)(uintptr_t)(p->c_light_blue);
case 4:return(uint64_t)(uintptr_t)(p->c_white);
case 5:return(uint64_t)(uintptr_t)(p->c_orange);
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_nothing_happens);
case 1:return(uint64_t)(uintptr_t)(p->c_something);
case 2:return(uint64_t)(uintptr_t)(p->c_Something);
case 3:return(uint64_t)(uintptr_t)(p->c_You_can_move_again);
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 8:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_sanctum_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_astral_level);
default:abort();}}
case 9:{struct display_hints*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
case 1:return(uint64_t)(uintptr_t)(p->female);
case 2:return(uint64_t)(uintptr_t)(p->paranoia_bits);
default:abort();}}
case 12:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
default:abort();}}
case 13:{struct instance_globals_a*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->afternmv);
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_doagain);
case 1:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 15:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->multi_reason);
default:abort();}}
case 16:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 17:{struct instance_globals_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->p_aligntyp);
case 1:return(uint64_t)(uintptr_t)(p->p_trouble);
case 2:return(uint64_t)(uintptr_t)(p->p_type);
default:abort();}}
case 18:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bases);
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 20:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 21:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 22:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->moves);
default:abort();}}
case 23:{struct instance_globals_saved_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->tune);
default:abort();}}
case 24:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
case 1:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 25:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 26:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 27:{struct kinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->format);
case 1:return(uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 28:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sokoban_rules);
default:abort();}}
case 29:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mcorpsenm);
default:abort();}}
case 30:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->cham);
case 2:return(uint64_t)(uintptr_t)(p->mx);
case 3:return(uint64_t)(uintptr_t)(p->my);
case 4:return(uint64_t)(uintptr_t)(p->mappearance);
case 5:return(uint64_t)(uintptr_t)(p->m_ap_type);
case 6:return(uint64_t)(uintptr_t)(p->mtame);
case 7:return(uint64_t)(uintptr_t)(p->mflee);
case 8:return(uint64_t)(uintptr_t)(p->msleeping);
case 9:return(uint64_t)(uintptr_t)(p->mfrozen);
case 10:return(uint64_t)(uintptr_t)(p->mcanmove);
case 11:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 12:return(uint64_t)(uintptr_t)(p->isminion);
case 13:return(uint64_t)(uintptr_t)(p->mstrategy);
case 14:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(&p->v);
case 2:return(uint64_t)(uintptr_t)(p->otyp);
case 3:return(uint64_t)(uintptr_t)(p->quan);
case 4:return(uint64_t)(uintptr_t)(p->spe);
case 5:return(uint64_t)(uintptr_t)(p->oclass);
case 6:return(uint64_t)(uintptr_t)(p->oartifact);
case 7:return(uint64_t)(uintptr_t)(p->where);
case 8:return(uint64_t)(uintptr_t)(p->cursed);
case 9:return(uint64_t)(uintptr_t)(p->blessed);
case 10:return(uint64_t)(uintptr_t)(p->known);
case 11:return(uint64_t)(uintptr_t)(p->bknown);
case 12:return(uint64_t)(uintptr_t)(p->rknown);
case 13:return(uint64_t)(uintptr_t)(p->oeroded);
case 14:return(uint64_t)(uintptr_t)(p->oeroded2);
case 15:return(uint64_t)(uintptr_t)(p->oerodeproof);
case 16:return(uint64_t)(uintptr_t)(p->corpsenm);
case 17:return(uint64_t)(uintptr_t)(p->oeaten);
case 18:return(uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name_idx);
case 1:return(uint64_t)(uintptr_t)(p->oc_name_known);
case 2:return(uint64_t)(uintptr_t)(p->oc_big);
case 3:return(uint64_t)(uintptr_t)(p->oc_subtyp);
case 4:return(uint64_t)(uintptr_t)(p->oc_class);
default:abort();}}
case 33:{struct objdescr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name);
default:abort();}}
case 34:{struct oextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->omonst);
default:abort();}}
case 35:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mlet);
case 1:return(uint64_t)(uintptr_t)(p->maligntyp);
case 2:return(uint64_t)(uintptr_t)(p->mflags1);
case 3:return(uint64_t)(uintptr_t)(p->mflags2);
case 4:return(uint64_t)(uintptr_t)(p->difficulty);
default:abort();}}
case 36:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 37:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 38:{struct skills*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->skill);
default:abort();}}
case 39:{struct u_conduct*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->unvegetarian);
case 1:return(uint64_t)(uintptr_t)(p->gnostic);
default:abort();}}
case 40:{struct u_event*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->uheard_tune);
case 1:return(uint64_t)(uintptr_t)(p->uopened_dbridge);
case 2:return(uint64_t)(uintptr_t)(p->gehennom_entered);
case 3:return(uint64_t)(uintptr_t)(p->uhand_of_elbereth);
case 4:return(uint64_t)(uintptr_t)(p->udemigod);
case 5:return(uint64_t)(uintptr_t)(p->ascended);
default:abort();}}
case 41:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 42:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 43:{volatile struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
default:abort();}}
case 44:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(&p->uz);
case 3:return(uint64_t)(uintptr_t)(p->ulevel);
case 4:return(uint64_t)(uintptr_t)(p->ulevelmax);
case 5:return(uint64_t)(uintptr_t)(p->utrap);
case 6:return(uint64_t)(uintptr_t)(p->utraptype);
case 7:return(uint64_t)(uintptr_t)(&p->urooms);
case 8:return(uint64_t)(uintptr_t)(p->uhunger);
case 9:return(uint64_t)(uintptr_t)(p->uhs);
case 10:return(uint64_t)(uintptr_t)(&p->uprops);
case 11:return(uint64_t)(uintptr_t)(p->umonster);
case 12:return(uint64_t)(uintptr_t)(p->umonnum);
case 13:return(uint64_t)(uintptr_t)(p->mh);
case 14:return(uint64_t)(uintptr_t)(p->mhmax);
case 15:return(uint64_t)(uintptr_t)(p->ulycn);
case 16:return(uint64_t)(uintptr_t)(p->ucreamed);
case 17:return(uint64_t)(uintptr_t)(p->uswallow);
case 18:return(uint64_t)(uintptr_t)(p->uinvulnerable);
case 19:return(uint64_t)(uintptr_t)(&p->uevent);
case 20:return(uint64_t)(uintptr_t)(&p->uconduct);
case 21:return(uint64_t)(uintptr_t)(&p->uroleplay);
case 22:return(uint64_t)(uintptr_t)(&p->acurr);
case 23:return(uint64_t)(uintptr_t)(&p->amax);
case 24:return(uint64_t)(uintptr_t)(&p->ualign);
case 25:return(uint64_t)(uintptr_t)(&p->ualignbase);
case 26:return(uint64_t)(uintptr_t)(p->uluck);
case 27:return(uint64_t)(uintptr_t)(p->moreluck);
case 28:return(uint64_t)(uintptr_t)(p->uhp);
case 29:return(uint64_t)(uintptr_t)(p->uhpmax);
case 30:return(uint64_t)(uintptr_t)(p->uhppeak);
case 31:return(uint64_t)(uintptr_t)(p->ugangr);
case 32:return(uint64_t)(uintptr_t)(p->ugifts);
case 33:return(uint64_t)(uintptr_t)(p->ublessed);
case 34:return(uint64_t)(uintptr_t)(p->ublesscnt);
case 35:return(uint64_t)(uintptr_t)(p->ustuck);
case 36:return(uint64_t)(uintptr_t)(p->usteed);
case 37:return(uint64_t)(uintptr_t)(&p->weapon_skills);
case 38:return(uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
default:abort();}}
void teleport_pray_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:p->him=(const char *)value;return;
case 1:p->his=(const char *)value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->adj=(const char *)value;return;
case 1:p->selfmask=(short)value;return;
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:p->lgod=(const char *)value;return;
case 1:p->ngod=(const char *)value;return;
case 2:p->cgod=(const char *)value;return;
case 3:p->mnum=(short)value;return;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:p->type=(aligntyp)value;return;
case 1:p->record=(int)value;return;
default:abort();}}
case 4:{struct attribs*p=at;switch(field){
default:abort();}}
case 5:{struct c_color_names*p=at;switch(field){
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:p->dnum=(xint16)value;return;
case 1:p->dlevel=(xint16)value;return;
default:abort();}}
case 8:{struct dgn_topology*p=at;switch(field){
default:abort();}}
case 9:{struct display_hints*p=at;switch(field){
case 0:p->botl=(boolean)value;return;
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:p->debug=(boolean)value;return;
case 1:p->female=(boolean)value;return;
case 2:p->paranoia_bits=(unsigned int)value;return;
default:abort();}}
case 12:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(int)value;return;
default:abort();}}
case 13:{struct instance_globals_a*p=at;switch(field){
case 0:p->afternmv=(int (*)(void))value;return;
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_doagain=(int)value;return;
case 1:p->invent=(struct obj *)value;return;
default:abort();}}
case 15:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi_reason=(const char *)value;return;
default:abort();}}
case 16:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(const char *)value;return;
default:abort();}}
case 17:{struct instance_globals_p*p=at;switch(field){
case 0:p->p_aligntyp=(aligntyp)value;return;
case 1:p->p_trouble=(int)value;return;
case 2:p->p_type=(int)value;return;
default:abort();}}
case 18:{struct instance_globals_saved_b*p=at;switch(field){
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 20:{struct instance_globals_saved_k*p=at;switch(field){
default:abort();}}
case 21:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=(long)value;return;
default:abort();}}
case 23:{struct instance_globals_saved_t*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 25:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(seenV **)value;return;
default:abort();}}
case 26:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 27:{struct kinfo*p=at;switch(field){
case 0:p->format=(int)value;return;
default:abort();}}
case 28:{struct levelflags*p=at;switch(field){
case 0:p->sokoban_rules=(unsigned int)value;return;
default:abort();}}
case 29:{struct mextra*p=at;switch(field){
case 0:p->mcorpsenm=(int)value;return;
default:abort();}}
case 30:{struct monst*p=at;switch(field){
case 0:p->data=(struct permonst *)value;return;
case 1:p->cham=(short)value;return;
case 2:p->mx=(coordxy)value;return;
case 3:p->my=(coordxy)value;return;
case 4:p->mappearance=(unsigned int)value;return;
case 5:p->m_ap_type=(uchar)value;return;
case 6:p->mtame=(schar)value;return;
case 7:p->mflee=(unsigned int)value;return;
case 8:p->msleeping=(unsigned int)value;return;
case 9:p->mfrozen=(unsigned int)value;return;
case 10:p->mcanmove=(unsigned int)value;return;
case 11:p->mpeaceful=(unsigned int)value;return;
case 12:p->isminion=(unsigned int)value;return;
case 13:p->mstrategy=(unsigned long)value;return;
case 14:p->mextra=(struct mextra *)value;return;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:p->nobj=(struct obj *)value;return;
case 2:p->otyp=(short)value;return;
case 3:p->quan=(long)value;return;
case 4:p->spe=(schar)value;return;
case 5:p->oclass=(char)value;return;
case 6:p->oartifact=(char)value;return;
case 7:p->where=(xint8)value;return;
case 8:p->cursed=(unsigned int)value;return;
case 9:p->blessed=(unsigned int)value;return;
case 10:p->known=(unsigned int)value;return;
case 11:p->bknown=(unsigned int)value;return;
case 12:p->rknown=(unsigned int)value;return;
case 13:p->oeroded=(unsigned int)value;return;
case 14:p->oeroded2=(unsigned int)value;return;
case 15:p->oerodeproof=(unsigned int)value;return;
case 16:p->corpsenm=(int)value;return;
case 17:p->oeaten=(unsigned int)value;return;
case 18:p->oextra=(struct oextra *)value;return;
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:p->oc_name_idx=(short)value;return;
case 1:p->oc_name_known=(unsigned int)value;return;
case 2:p->oc_big=(unsigned int)value;return;
case 3:p->oc_subtyp=(schar)value;return;
case 4:p->oc_class=(char)value;return;
default:abort();}}
case 33:{struct objdescr*p=at;switch(field){
case 0:p->oc_name=(const char *)value;return;
default:abort();}}
case 34:{struct oextra*p=at;switch(field){
case 0:p->omonst=(struct monst *)value;return;
default:abort();}}
case 35:{struct permonst*p=at;switch(field){
case 0:p->mlet=(char)value;return;
case 1:p->maligntyp=(aligntyp)value;return;
case 2:p->mflags1=(unsigned long)value;return;
case 3:p->mflags2=(unsigned long)value;return;
case 4:p->difficulty=(uchar)value;return;
default:abort();}}
case 36:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(long)value;return;
case 1:p->blocked=(long)value;return;
case 2:p->intrinsic=(long)value;return;
default:abort();}}
case 37:{struct rm*p=at;switch(field){
case 0:p->typ=(schar)value;return;
case 1:p->flags=(unsigned int)value;return;
default:abort();}}
case 38:{struct skills*p=at;switch(field){
case 0:p->skill=(xint16)value;return;
default:abort();}}
case 39:{struct u_conduct*p=at;switch(field){
case 0:p->unvegetarian=(long)value;return;
case 1:p->gnostic=(long)value;return;
default:abort();}}
case 40:{struct u_event*p=at;switch(field){
case 0:p->uheard_tune=(unsigned int)value;return;
case 1:p->uopened_dbridge=(unsigned int)value;return;
case 2:p->gehennom_entered=(unsigned int)value;return;
case 3:p->uhand_of_elbereth=(unsigned int)value;return;
case 4:p->udemigod=(unsigned int)value;return;
case 5:p->ascended=(unsigned int)value;return;
default:abort();}}
case 41:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=(boolean)value;return;
default:abort();}}
case 42:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(struct obj *)value;return;
default:abort();}}
case 43:{volatile struct window_procs*p=at;switch(field){
case 0:p->win_display_nhwindow=(void (*)(winid, boolean))value;return;
default:abort();}}
case 44:{struct you*p=at;switch(field){
case 0:p->ux=(coordxy)value;return;
case 1:p->uy=(coordxy)value;return;
case 3:p->ulevel=(int)value;return;
case 4:p->ulevelmax=(int)value;return;
case 5:p->utrap=(unsigned int)value;return;
case 6:p->utraptype=(unsigned int)value;return;
case 8:p->uhunger=(int)value;return;
case 9:p->uhs=(unsigned int)value;return;
case 11:p->umonster=(int)value;return;
case 12:p->umonnum=(int)value;return;
case 13:p->mh=(int)value;return;
case 14:p->mhmax=(int)value;return;
case 15:p->ulycn=(int)value;return;
case 16:p->ucreamed=(unsigned int)value;return;
case 17:p->uswallow=(unsigned int)value;return;
case 18:p->uinvulnerable=(unsigned int)value;return;
case 26:p->uluck=(schar)value;return;
case 27:p->moreluck=(schar)value;return;
case 28:p->uhp=(int)value;return;
case 29:p->uhpmax=(int)value;return;
case 30:p->uhppeak=(int)value;return;
case 31:p->ugangr=(int)value;return;
case 32:p->ugifts=(int)value;return;
case 33:p->ublessed=(int)value;return;
case 34:p->ublesscnt=(int)value;return;
case 35:p->ustuck=(struct monst *)value;return;
case 36:p->usteed=(struct monst *)value;return;
case 38:p->twoweap=(boolean)value;return;
default:abort();}}
default:abort();}}
void* teleport_pray_address(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->him;
case 1:return(void*)&p->his;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->adj;
case 1:return(void*)&p->selfmask;
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:return(void*)&p->lgod;
case 1:return(void*)&p->ngod;
case 2:return(void*)&p->cgod;
case 3:return(void*)&p->mnum;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return(void*)&p->type;
case 1:return(void*)&p->record;
default:abort();}}
case 4:{struct attribs*p=at;switch(field){
case 0:return(void*)&p->a;
default:abort();}}
case 5:{struct c_color_names*p=at;switch(field){
case 0:return(void*)&p->c_black;
case 1:return(void*)&p->c_amber;
case 2:return(void*)&p->c_golden;
case 3:return(void*)&p->c_light_blue;
case 4:return(void*)&p->c_white;
case 5:return(void*)&p->c_orange;
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_nothing_happens;
case 1:return(void*)&p->c_something;
case 2:return(void*)&p->c_Something;
case 3:return(void*)&p->c_You_can_move_again;
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 8:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_sanctum_level;
case 1:return(void*)&p->d_astral_level;
default:abort();}}
case 9:{struct display_hints*p=at;switch(field){
case 0:return(void*)&p->botl;
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->flags;
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
case 1:return(void*)&p->female;
case 2:return(void*)&p->paranoia_bits;
default:abort();}}
case 12:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
default:abort();}}
case 13:{struct instance_globals_a*p=at;switch(field){
case 0:return(void*)&p->afternmv;
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_doagain;
case 1:return(void*)&p->invent;
default:abort();}}
case 15:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->multi_reason;
default:abort();}}
case 16:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nomovemsg;
default:abort();}}
case 17:{struct instance_globals_p*p=at;switch(field){
case 0:return(void*)&p->p_aligntyp;
case 1:return(void*)&p->p_trouble;
case 2:return(void*)&p->p_type;
default:abort();}}
case 18:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(void*)&p->bases;
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
default:abort();}}
case 20:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return(void*)&p->killer;
default:abort();}}
case 21:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 22:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->moves;
default:abort();}}
case 23:{struct instance_globals_saved_t*p=at;switch(field){
case 0:return(void*)&p->tune;
default:abort();}}
case 24:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
case 1:return(void*)&p->urace;
default:abort();}}
case 25:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->viz_array;
default:abort();}}
case 26:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 27:{struct kinfo*p=at;switch(field){
case 0:return(void*)&p->format;
case 1:return(void*)&p->name;
default:abort();}}
case 28:{struct levelflags*p=at;switch(field){
default:abort();}}
case 29:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->mcorpsenm;
default:abort();}}
case 30:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 1:return(void*)&p->cham;
case 2:return(void*)&p->mx;
case 3:return(void*)&p->my;
case 4:return(void*)&p->mappearance;
case 5:return(void*)&p->m_ap_type;
case 6:return(void*)&p->mtame;
case 13:return(void*)&p->mstrategy;
case 14:return(void*)&p->mextra;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->v;
case 2:return(void*)&p->otyp;
case 3:return(void*)&p->quan;
case 4:return(void*)&p->spe;
case 5:return(void*)&p->oclass;
case 6:return(void*)&p->oartifact;
case 7:return(void*)&p->where;
case 16:return(void*)&p->corpsenm;
case 17:return(void*)&p->oeaten;
case 18:return(void*)&p->oextra;
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_name_idx;
case 3:return(void*)&p->oc_subtyp;
case 4:return(void*)&p->oc_class;
default:abort();}}
case 33:{struct objdescr*p=at;switch(field){
case 0:return(void*)&p->oc_name;
default:abort();}}
case 34:{struct oextra*p=at;switch(field){
case 0:return(void*)&p->omonst;
default:abort();}}
case 35:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->mlet;
case 1:return(void*)&p->maligntyp;
case 2:return(void*)&p->mflags1;
case 3:return(void*)&p->mflags2;
case 4:return(void*)&p->difficulty;
default:abort();}}
case 36:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 37:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
default:abort();}}
case 38:{struct skills*p=at;switch(field){
case 0:return(void*)&p->skill;
default:abort();}}
case 39:{struct u_conduct*p=at;switch(field){
case 0:return(void*)&p->unvegetarian;
case 1:return(void*)&p->gnostic;
default:abort();}}
case 40:{struct u_event*p=at;switch(field){
default:abort();}}
case 41:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->deaf;
default:abort();}}
case 42:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
default:abort();}}
case 43:{volatile struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_display_nhwindow;
default:abort();}}
case 44:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->uz;
case 3:return(void*)&p->ulevel;
case 4:return(void*)&p->ulevelmax;
case 5:return(void*)&p->utrap;
case 6:return(void*)&p->utraptype;
case 7:return(void*)&p->urooms;
case 8:return(void*)&p->uhunger;
case 9:return(void*)&p->uhs;
case 10:return(void*)&p->uprops;
case 11:return(void*)&p->umonster;
case 12:return(void*)&p->umonnum;
case 13:return(void*)&p->mh;
case 14:return(void*)&p->mhmax;
case 15:return(void*)&p->ulycn;
case 16:return(void*)&p->ucreamed;
case 19:return(void*)&p->uevent;
case 20:return(void*)&p->uconduct;
case 21:return(void*)&p->uroleplay;
case 22:return(void*)&p->acurr;
case 23:return(void*)&p->amax;
case 24:return(void*)&p->ualign;
case 25:return(void*)&p->ualignbase;
case 26:return(void*)&p->uluck;
case 27:return(void*)&p->moreluck;
case 28:return(void*)&p->uhp;
case 29:return(void*)&p->uhpmax;
case 30:return(void*)&p->uhppeak;
case 31:return(void*)&p->ugangr;
case 32:return(void*)&p->ugifts;
case 33:return(void*)&p->ublessed;
case 34:return(void*)&p->ublesscnt;
case 35:return(void*)&p->ustuck;
case 36:return(void*)&p->usteed;
case 37:return(void*)&p->weapon_skills;
case 38:return(void*)&p->twoweap;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_pray_var0(char * a0){(impossible)(a0);}
void teleport_pray_var1(char * a0,char * a1){(Your)(a0,a1);}
void teleport_pray_var2(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var3(char * a0){(Your)(a0);}
void teleport_pray_var4(char * a0){(You)(a0);}
void teleport_pray_var5(char * a0,char * a1){(Your)(a0,a1);}
void teleport_pray_var6(char * a0){(You_feel)(a0);}
void teleport_pray_var7(char * a0){(You_feel)(a0);}
void teleport_pray_var8(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_pray_var9(char * a0){(Your)(a0);}
void teleport_pray_var10(char * a0){(You_feel)(a0);}
void teleport_pray_var11(char * a0){(Your)(a0);}
void teleport_pray_var12(char * a0){(impossible)(a0);}
void teleport_pray_var13(char * a0){(Your)(a0);}
void teleport_pray_var14(char * a0){(pline)(a0);}
void teleport_pray_var15(char * a0){(You_feel)(a0);}
int teleport_pray_var16(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_pray_var17(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pray_var18(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var19(char * a0){(pline)(a0);}
void teleport_pray_var20(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var21(char * a0){(pline)(a0);}
void teleport_pray_var22(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var23(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var24(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var25(char * a0){(pline)(a0);}
void teleport_pray_var26(char * a0){(pline)(a0);}
void teleport_pray_var27(char * a0){(pline)(a0);}
void teleport_pray_var28(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var29(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var30(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var31(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var32(char * a0){(pline)(a0);}
void teleport_pray_var33(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var34(char * a0){(verbalize)(a0);}
void teleport_pray_var35(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_pray_var36(char * a0,char * a1){(You)(a0,a1);}
int teleport_pray_var37(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pray_var38(char * a0,char * a1,char * a2){(You_feel)(a0,a1,a2);}
void teleport_pray_var39(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var40(char * a0){(verbalize)(a0);}
void teleport_pray_var41(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var42(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_pray_var43(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var44(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_pray_var45(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_pray_var46(char * a0){(verbalize)(a0);}
void teleport_pray_var47(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_pray_var48(char * a0){(verbalize)(a0);}
void teleport_pray_var49(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_pray_var50(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_pray_var51(long a0,char * a1,char * a2,char * a3){(livelog_printf)(a0,a1,a2,a3);}
void teleport_pray_var52(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_pray_var53(char * a0){(Your)(a0);}
void teleport_pray_var54(long a0,char * a1,char * a2,char * a3,char * a4){(livelog_printf)(a0,a1,a2,a3,a4);}
void teleport_pray_var55(char * a0,char * a1){(Your)(a0,a1);}
void teleport_pray_var56(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
int teleport_pray_var57(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pray_var58(char * a0,char * a1){(Your)(a0,a1);}
void teleport_pray_var59(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_pray_var60(char * a0){(You_feel)(a0);}
void teleport_pray_var61(char * a0,char * a1,int a2){(pline)(a0,a1,a2);}
void teleport_pray_var62(char * a0,int a1,char * a2,char * a3){(Your)(a0,a1,a2,a3);}
void teleport_pray_var63(char * a0,char * a1,char * a2){(You_feel)(a0,a1,a2);}
int teleport_pray_var64(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pray_var65(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_pray_var66(char * a0,char * a1,char * a2){(You_feel)(a0,a1,a2);}
void teleport_pray_var67(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_pray_var68(char * a0,char * a1,char * a2){(You_feel)(a0,a1,a2);}
void teleport_pray_var69(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var70(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_pray_var71(char * a0){(verbalize)(a0);}
void teleport_pray_var72(char * a0){(You_hear)(a0);}
void teleport_pray_var73(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var74(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var75(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_pray_var76(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var77(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var78(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var79(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var80(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var81(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var82(char * a0){(verbalize)(a0);}
void teleport_pray_var83(char * a0){(impossible)(a0);}
void teleport_pray_var84(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_pray_var85(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){(pline_The)(a0,a1,a2,a3,a4,a5);}
void teleport_pray_var86(char * a0){(Your)(a0);}
void teleport_pray_var87(char * a0){(Your)(a0);}
void teleport_pray_var88(char * a0){(Your)(a0);}
void teleport_pray_var89(char * a0){(Your)(a0);}
void teleport_pray_var90(char * a0,char * a1){(Your)(a0,a1);}
void teleport_pray_var91(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_pray_var92(char * a0){(You_feel)(a0);}
void teleport_pray_var93(char * a0,char * a1){(pline)(a0,a1);}
int teleport_pray_var94(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pray_var95(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var96(char * a0){(pline)(a0);}
void teleport_pray_var97(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var98(char * a0){(pline)(a0);}
int teleport_pray_var99(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pray_var100(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var101(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var102(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var103(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var104(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var105(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var106(char * a0){(pline)(a0);}
void teleport_pray_var107(char * a0){(verbalize)(a0);}
void teleport_pray_var108(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var109(char * a0){(You_hear)(a0);}
void teleport_pray_var110(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var111(char * a0){(pline)(a0);}
void teleport_pray_var112(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var113(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var114(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var115(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pray_var116(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_pray_var117(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_pray_var118(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var119(char * a0){(You)(a0);}
void teleport_pray_var120(char * a0){(pline)(a0);}
void teleport_pray_var121(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_pray_var122(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var123(char * a0){(pline_The)(a0);}
void teleport_pray_var124(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var125(char * a0){(You)(a0);}
void teleport_pray_var126(char * a0,char * a1){(pline_The)(a0,a1);}
int teleport_pray_var127(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pray_var128(long a0,char * a1,char * a2,char * a3){(livelog_printf)(a0,a1,a2,a3);}
void teleport_pray_var129(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var130(char * a0){(You)(a0);}
void teleport_pray_var131(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var132(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var133(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_pray_var134(char * a0){(You_feel)(a0);}
void teleport_pray_var135(long a0,char * a1,char * a2,char * a3){(livelog_printf)(a0,a1,a2,a3);}
void teleport_pray_var136(char * a0){(pline)(a0);}
void teleport_pray_var137(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var138(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var139(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var140(char * a0){(pline_The)(a0);}
void teleport_pray_var141(char * a0){(You)(a0);}
void teleport_pray_var142(char * a0){(You_feel)(a0);}
void teleport_pray_var143(char * a0){(You)(a0);}
void teleport_pray_var144(char * a0){(You)(a0);}
void teleport_pray_var145(char * a0){(pline)(a0);}
void teleport_pray_var146(char * a0){(You)(a0);}
void teleport_pray_var147(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pray_var148(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var149(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_pray_var150(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var151(long a0,char * a1){(livelog_printf)(a0,a1);}
void teleport_pray_var152(char * a0){(You)(a0);}
void teleport_pray_var153(char * a0,char * a1){(You)(a0,a1);}
void teleport_pray_var154(char * a0){(pline)(a0);}
void teleport_pray_var155(char * a0){(You_feel)(a0);}
void teleport_pray_var156(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var157(char * a0){(pline)(a0);}
void teleport_pray_var158(char * a0){(You)(a0);}
void teleport_pray_var159(long a0,char * a1){(livelog_printf)(a0,a1);}
void teleport_pray_var160(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pray_var161(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var162(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pray_var163(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pray_var164(char * a0){(impossible)(a0);}
void teleport_pray_var165(char * a0){(impossible)(a0);}
void teleport_pray_var166(char * a0){(impossible)(a0);}
void teleport_pray_var167(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_pray_var168(char * a0){(verbalize)(a0);}
#pragma clang diagnostic pop
void*teleport_pray_copy(void*to,const void*from,size_t n){return memcpy(to,from,n);}
int teleport_pray_call_rng(int(*fn)(int),int n){return fn(n);}
void teleport_pray_call_window(void(*fn)(winid,boolean),winid id,boolean block){fn(id,block);}
extern int teleport_pray_in_trouble(void);
extern struct obj * teleport_pray_worst_cursed_item(void);
extern void teleport_pray_fix_curse_trouble(struct obj * otmp,const char * what);
extern void teleport_pray_fix_worst_trouble(int trouble);
extern void teleport_pray_god_zaps_you(aligntyp resp_god);
extern void teleport_pray_fry_by_god(aligntyp resp_god,boolean via_disintegration);
extern void teleport_pray_angrygods(aligntyp resp_god);
extern void teleport_pray_at_your_feet(const char * str);
extern void teleport_pray_gcrownu(void);
extern void teleport_pray_give_spell(void);
extern void teleport_pray_pleased(aligntyp g_align);
extern boolean teleport_pray_water_prayer(boolean bless_water);
extern void teleport_pray_godvoice(aligntyp g_align,const char * words);
extern void teleport_pray_gods_angry(aligntyp g_align);
extern void teleport_pray_gods_upset(aligntyp g_align);
extern void teleport_pray_consume_offering(struct obj * otmp);
extern void teleport_pray_offer_too_soon(aligntyp altaralign);
extern void teleport_pray_offer_real_amulet(struct obj * otmp,aligntyp altaralign);
extern void teleport_pray_offer_negative_valued(boolean highaltar,aligntyp altaralign);
extern void teleport_pray_offer_fake_amulet(struct obj * otmp,boolean highaltar,aligntyp altaralign);
extern void teleport_pray_offer_different_alignment_altar(struct obj * otmp,aligntyp altaralign);
extern void teleport_pray_sacrifice_your_race(struct obj * otmp,boolean highaltar,aligntyp altaralign);
extern int teleport_pray_bestow_artifact(uchar max_giftvalue);
extern int teleport_pray_sacrifice_value(struct obj * otmp);
extern int teleport_pray_eval_offering(struct obj * otmp,aligntyp altaralign);
extern void teleport_pray_offer_corpse(struct obj * otmp,boolean highaltar,aligntyp altaralign);
extern boolean teleport_pray_pray_revive(void);
extern int teleport_pray_prayer_done(void);
extern void teleport_pray_maybe_turn_mon_iter(struct monst * mtmp);
extern boolean teleport_pray_blocked_boulder(int dx,int dy);
uintptr_t teleport_pray_function0(void){return(uintptr_t)teleport_pray_prayer_done;}
uintptr_t teleport_pray_function1(void){return(uintptr_t)teleport_pray_maybe_turn_mon_iter;}
#include "pray-source-data.h"
static char pray_literals[PRAY_LITERAL_CAPACITY];
char*teleport_pray_literal_storage(void){return pray_literals;}
size_t teleport_pray_literal_capacity(void){return sizeof pray_literals;}
/* Configured source/field/dependency ABI guards; no algorithms. */
_Static_assert(sizeof(size_t)==8 && (size_t)-1>0 && sizeof(long)==8 && (long)-1<0,"PRAY size_t/long64");
_Static_assert(sizeof(((struct Race*)0)->selfmask)==2 && (((__typeof__(((struct Race*)0)->selfmask))-1<0)==1),"PRAY Race.selfmask width/sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2 && (((__typeof__(((struct Role*)0)->mnum))-1<0)==1),"PRAY Role.mnum width/sign");
_Static_assert(sizeof(((struct align*)0)->type)==1 && (((__typeof__(((struct align*)0)->type))-1<0)==1),"PRAY align.type width/sign");
_Static_assert(sizeof(((struct align*)0)->record)==4 && (((__typeof__(((struct align*)0)->record))-1<0)==1),"PRAY align.record width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"PRAY d_level.dnum width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"PRAY d_level.dlevel width/sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1 && (((__typeof__(((struct display_hints*)0)->botl))-1<0)==1),"PRAY display_hints.botl width/sign");
_Static_assert(sizeof(((struct flag*)0)->debug)==1 && (((__typeof__(((struct flag*)0)->debug))-1<0)==1),"PRAY flag.debug width/sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1 && (((__typeof__(((struct flag*)0)->female))-1<0)==1),"PRAY flag.female width/sign");
_Static_assert(sizeof(((struct flag*)0)->paranoia_bits)==4 && (((__typeof__(((struct flag*)0)->paranoia_bits))-1<0)==0),"PRAY flag.paranoia_bits width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4 && (((__typeof__(((struct instance_flags*)0)->last_msg))-1<0)==1),"PRAY instance_flags.last_msg width/sign");
_Static_assert(sizeof(((struct instance_globals_i*)0)->in_doagain)==4 && (((__typeof__(((struct instance_globals_i*)0)->in_doagain))-1<0)==1),"PRAY instance_globals_i.in_doagain width/sign");
_Static_assert(sizeof(((struct instance_globals_p*)0)->p_aligntyp)==1 && (((__typeof__(((struct instance_globals_p*)0)->p_aligntyp))-1<0)==1),"PRAY instance_globals_p.p_aligntyp width/sign");
_Static_assert(sizeof(((struct instance_globals_p*)0)->p_trouble)==4 && (((__typeof__(((struct instance_globals_p*)0)->p_trouble))-1<0)==1),"PRAY instance_globals_p.p_trouble width/sign");
_Static_assert(sizeof(((struct instance_globals_p*)0)->p_type)==4 && (((__typeof__(((struct instance_globals_p*)0)->p_type))-1<0)==1),"PRAY instance_globals_p.p_type width/sign");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8 && (((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1<0)==1),"PRAY instance_globals_saved_m.moves width/sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4 && (((__typeof__(((struct kinfo*)0)->format))-1<0)==1),"PRAY kinfo.format width/sign");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4 && (((__typeof__(((struct mextra*)0)->mcorpsenm))-1<0)==1),"PRAY mextra.mcorpsenm width/sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2 && (((__typeof__(((struct monst*)0)->cham))-1<0)==1),"PRAY monst.cham width/sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"PRAY monst.mx width/sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"PRAY monst.my width/sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4 && (((__typeof__(((struct monst*)0)->mappearance))-1<0)==0),"PRAY monst.mappearance width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"PRAY monst.m_ap_type width/sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"PRAY monst.mtame width/sign");
_Static_assert(sizeof(((struct monst*)0)->mstrategy)==8 && (((__typeof__(((struct monst*)0)->mstrategy))-1<0)==0),"PRAY monst.mstrategy width/sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"PRAY obj.otyp width/sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"PRAY obj.quan width/sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1 && (((__typeof__(((struct obj*)0)->spe))-1<0)==1),"PRAY obj.spe width/sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1 && (((__typeof__(((struct obj*)0)->oclass))-1<0)==1),"PRAY obj.oclass width/sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1 && (((__typeof__(((struct obj*)0)->oartifact))-1<0)==1),"PRAY obj.oartifact width/sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1 && (((__typeof__(((struct obj*)0)->where))-1<0)==1),"PRAY obj.where width/sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4 && (((__typeof__(((struct obj*)0)->corpsenm))-1<0)==1),"PRAY obj.corpsenm width/sign");
_Static_assert(sizeof(((struct obj*)0)->oeaten)==4 && (((__typeof__(((struct obj*)0)->oeaten))-1<0)==0),"PRAY obj.oeaten width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2 && (((__typeof__(((struct objclass*)0)->oc_name_idx))-1<0)==1),"PRAY objclass.oc_name_idx width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1 && (((__typeof__(((struct objclass*)0)->oc_subtyp))-1<0)==1),"PRAY objclass.oc_subtyp width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_class)==1 && (((__typeof__(((struct objclass*)0)->oc_class))-1<0)==1),"PRAY objclass.oc_class width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"PRAY permonst.mlet width/sign");
_Static_assert(sizeof(((struct permonst*)0)->maligntyp)==1 && (((__typeof__(((struct permonst*)0)->maligntyp))-1<0)==1),"PRAY permonst.maligntyp width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"PRAY permonst.mflags1 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8 && (((__typeof__(((struct permonst*)0)->mflags2))-1<0)==0),"PRAY permonst.mflags2 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->difficulty)==1 && (((__typeof__(((struct permonst*)0)->difficulty))-1<0)==0),"PRAY permonst.difficulty width/sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"PRAY prop.extrinsic width/sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"PRAY prop.blocked width/sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"PRAY prop.intrinsic width/sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"PRAY rm.typ width/sign");
_Static_assert(sizeof(((struct skills*)0)->skill)==2 && (((__typeof__(((struct skills*)0)->skill))-1<0)==1),"PRAY skills.skill width/sign");
_Static_assert(sizeof(((struct u_conduct*)0)->unvegetarian)==8 && (((__typeof__(((struct u_conduct*)0)->unvegetarian))-1<0)==1),"PRAY u_conduct.unvegetarian width/sign");
_Static_assert(sizeof(((struct u_conduct*)0)->gnostic)==8 && (((__typeof__(((struct u_conduct*)0)->gnostic))-1<0)==1),"PRAY u_conduct.gnostic width/sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1 && (((__typeof__(((struct u_roleplay*)0)->deaf))-1<0)==1),"PRAY u_roleplay.deaf width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"PRAY you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"PRAY you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4 && (((__typeof__(((struct you*)0)->ulevel))-1<0)==1),"PRAY you.ulevel width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevelmax)==4 && (((__typeof__(((struct you*)0)->ulevelmax))-1<0)==1),"PRAY you.ulevelmax width/sign");
_Static_assert(sizeof(((struct you*)0)->utrap)==4 && (((__typeof__(((struct you*)0)->utrap))-1<0)==0),"PRAY you.utrap width/sign");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4 && (((__typeof__(((struct you*)0)->utraptype))-1<0)==0),"PRAY you.utraptype width/sign");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4 && (((__typeof__(((struct you*)0)->uhunger))-1<0)==1),"PRAY you.uhunger width/sign");
_Static_assert(sizeof(((struct you*)0)->uhs)==4 && (((__typeof__(((struct you*)0)->uhs))-1<0)==0),"PRAY you.uhs width/sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"PRAY you.umonster width/sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"PRAY you.umonnum width/sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4 && (((__typeof__(((struct you*)0)->mh))-1<0)==1),"PRAY you.mh width/sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4 && (((__typeof__(((struct you*)0)->mhmax))-1<0)==1),"PRAY you.mhmax width/sign");
_Static_assert(sizeof(((struct you*)0)->ulycn)==4 && (((__typeof__(((struct you*)0)->ulycn))-1<0)==1),"PRAY you.ulycn width/sign");
_Static_assert(sizeof(((struct you*)0)->ucreamed)==4 && (((__typeof__(((struct you*)0)->ucreamed))-1<0)==0),"PRAY you.ucreamed width/sign");
_Static_assert(sizeof(((struct you*)0)->uluck)==1 && (((__typeof__(((struct you*)0)->uluck))-1<0)==1),"PRAY you.uluck width/sign");
_Static_assert(sizeof(((struct you*)0)->moreluck)==1 && (((__typeof__(((struct you*)0)->moreluck))-1<0)==1),"PRAY you.moreluck width/sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4 && (((__typeof__(((struct you*)0)->uhp))-1<0)==1),"PRAY you.uhp width/sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4 && (((__typeof__(((struct you*)0)->uhpmax))-1<0)==1),"PRAY you.uhpmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uhppeak)==4 && (((__typeof__(((struct you*)0)->uhppeak))-1<0)==1),"PRAY you.uhppeak width/sign");
_Static_assert(sizeof(((struct you*)0)->ugangr)==4 && (((__typeof__(((struct you*)0)->ugangr))-1<0)==1),"PRAY you.ugangr width/sign");
_Static_assert(sizeof(((struct you*)0)->ugifts)==4 && (((__typeof__(((struct you*)0)->ugifts))-1<0)==1),"PRAY you.ugifts width/sign");
_Static_assert(sizeof(((struct you*)0)->ublessed)==4 && (((__typeof__(((struct you*)0)->ublessed))-1<0)==1),"PRAY you.ublessed width/sign");
_Static_assert(sizeof(((struct you*)0)->ublesscnt)==4 && (((__typeof__(((struct you*)0)->ublesscnt))-1<0)==1),"PRAY you.ublesscnt width/sign");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1 && (((__typeof__(((struct you*)0)->twoweap))-1<0)==1),"PRAY you.twoweap width/sign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xlev_to_rank),int (*)(int)),"PRAY dependency xlev_to_rank");
_Static_assert(__builtin_types_compatible_p(__typeof__(&isok),int (*)(coordxy, coordxy)),"PRAY dependency isok");
_Static_assert(__builtin_types_compatible_p(__typeof__(&region_danger),boolean (*)(void)),"PRAY dependency region_danger");
_Static_assert(__builtin_types_compatible_p(__typeof__(&near_capacity),int (*)(void)),"PRAY dependency near_capacity");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stuck_ring),struct obj *(*)(struct obj *, int)),"PRAY dependency stuck_ring");
_Static_assert(__builtin_types_compatible_p(__typeof__(&freehand),int (*)(void)),"PRAY dependency freehand");
_Static_assert(__builtin_types_compatible_p(__typeof__(&welded),int (*)(struct obj *)),"PRAY dependency welded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unchanger),struct obj *(*)(void)),"PRAY dependency unchanger");
_Static_assert(__builtin_types_compatible_p(__typeof__(&which_armor),struct obj *(*)(struct monst *, long)),"PRAY dependency which_armor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype_fordmg),struct attack *(*)(struct permonst *, int, int)),"PRAY dependency attacktype_fordmg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&confers_luck),boolean (*)(struct obj *)),"PRAY dependency confers_luck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&impossible),void (*)(const char *, ...)),"PRAY dependency impossible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_glib),void (*)(int)),"PRAY dependency make_glib");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Your),void (*)(const char *, ...)),"PRAY dependency Your");
_Static_assert(__builtin_types_compatible_p(__typeof__(&gloves_simple_name),const char *(*)(struct obj *)),"PRAY dependency gloves_simple_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline),void (*)(const char *, ...)),"PRAY dependency pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Yobjnam2),char *(*)(struct obj *, const char *)),"PRAY dependency Yobjnam2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hcolor),const char *(*)(const char *)),"PRAY dependency hcolor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&uncurse),void (*)(struct obj *)),"PRAY dependency uncurse");
_Static_assert(__builtin_types_compatible_p(__typeof__(&update_inventory),void (*)(void)),"PRAY dependency update_inventory");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_stoned),void (*)(long, const char *, int, const char *)),"PRAY dependency make_stoned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_slimed),void (*)(long, const char *)),"PRAY dependency make_slimed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&useup),void (*)(struct obj *)),"PRAY dependency useup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You),void (*)(const char *, ...)),"PRAY dependency You");
_Static_assert(__builtin_types_compatible_p(__typeof__(&safe_teleds),boolean (*)(int)),"PRAY dependency safe_teleds");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reset_utrap),void (*)(boolean)),"PRAY dependency reset_utrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rescued_from_terrain),void (*)(int)),"PRAY dependency rescued_from_terrain");
_Static_assert(__builtin_types_compatible_p(__typeof__(&body_part),const char *(*)(int)),"PRAY dependency body_part");
_Static_assert(__builtin_types_compatible_p(__typeof__(&init_uhunger),void (*)(void)),"PRAY dependency init_uhunger");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_feel),void (*)(const char *, ...)),"PRAY dependency You_feel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_sick),void (*)(long, const char *, boolean, int)),"PRAY dependency make_sick");
_Static_assert(__builtin_types_compatible_p(__typeof__(&region_safety),void (*)(void)),"PRAY dependency region_safety");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"PRAY dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *, int, const char *)),"PRAY dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd),int (*)(int)),"PRAY dependency rnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setuhpmax),void (*)(int, boolean)),"PRAY dependency setuhpmax");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_itimeout),void (*)(long *, long)),"PRAY dependency set_itimeout");
_Static_assert(__builtin_types_compatible_p(__typeof__(&d),int (*)(int, int)),"PRAY dependency d");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rehumanize),void (*)(void)),"PRAY dependency rehumanize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&you_unwere),void (*)(boolean)),"PRAY dependency you_unwere");
_Static_assert(__builtin_types_compatible_p(__typeof__(&buried_ball_to_freedom),void (*)(void)),"PRAY dependency buried_ball_to_freedom");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unpunish),void (*)(void)),"PRAY dependency unpunish");
_Static_assert(__builtin_types_compatible_p(__typeof__(&encumber_msg),void (*)(void)),"PRAY dependency encumber_msg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makeplural),char *(*)(const char *)),"PRAY dependency makeplural");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sprintf),int (*)(char *restrict, const char *restrict, ...)),"PRAY dependency sprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vtense),char *(*)(const char *, const char *)),"PRAY dependency vtense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_blinded),void (*)(long, boolean)),"PRAY dependency make_blinded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_deaf),void (*)(long, boolean)),"PRAY dependency make_deaf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&eos),char *(*)(char *)),"PRAY dependency eos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&heal_legs),void (*)(int)),"PRAY dependency heal_legs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_stunned),void (*)(long, boolean)),"PRAY dependency make_stunned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_confused),void (*)(long, boolean)),"PRAY dependency make_confused");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_hallucinated),boolean (*)(long, boolean, long)),"PRAY dependency make_hallucinated");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_bknown),void (*)(struct obj *, unsigned int)),"PRAY dependency set_bknown");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_nam),char *(*)(struct monst *)),"PRAY dependency mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Resists_Elem),boolean (*)(struct monst *, int)),"PRAY dependency Resists_Elem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Monnam),char *(*)(struct monst *)),"PRAY dependency Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xkilled),void (*)(struct monst *, int)),"PRAY dependency xkilled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&shieldeff),void (*)(coordxy, coordxy)),"PRAY dependency shieldeff");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ureflects),boolean (*)(const char *, const char *)),"PRAY dependency ureflects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monstseesu),void (*)(unsigned long)),"PRAY dependency monstseesu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monstunseesu),void (*)(unsigned long)),"PRAY dependency monstunseesu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&disintegrate_arm),int (*)(struct obj *)),"PRAY dependency disintegrate_arm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),boolean (*)(d_level *, d_level *)),"PRAY dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&verbalize),void (*)(const char *, ...)),"PRAY dependency verbalize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&summon_minion),void (*)(aligntyp, boolean)),"PRAY dependency summon_minion");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done),void (*)(int)),"PRAY dependency done");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_hell),boolean (*)(d_level *)),"PRAY dependency In_hell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"PRAY dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&adjattrib),boolean (*)(int, int, int)),"PRAY dependency adjattrib");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losexp),void (*)(const char *)),"PRAY dependency losexp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&punish),void (*)(struct obj *)),"PRAY dependency punish");
_Static_assert(__builtin_types_compatible_p(__typeof__(&An),char *(*)(const char *)),"PRAY dependency An");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attrcurse),int (*)(void)),"PRAY dependency attrcurse");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rndcurse),void (*)(void)),"PRAY dependency rndcurse");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnz),int (*)(int)),"PRAY dependency rnz");
_Static_assert(__builtin_types_compatible_p(__typeof__(&s_suffix),char *(*)(const char *)),"PRAY dependency s_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mbodypart),const char *(*)(struct monst *, int)),"PRAY dependency mbodypart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_art),boolean (*)(struct obj *, int)),"PRAY dependency is_art");
_Static_assert(__builtin_types_compatible_p(__typeof__(&carrying),struct obj *(*)(int)),"PRAY dependency carrying");
_Static_assert(__builtin_types_compatible_p(__typeof__(&livelog_printf),void (*)(long, const char *, ...)),"PRAY dependency livelog_printf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exist_artifact),boolean (*)(int, const char *)),"PRAY dependency exist_artifact");
_Static_assert(__builtin_types_compatible_p(__typeof__(&artiname),const char *(*)(int)),"PRAY dependency artiname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mksobj),struct obj *(*)(int, boolean, boolean)),"PRAY dependency mksobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char *(*)(char *, const char *)),"PRAY dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&actualoname),char *(*)(struct obj *)),"PRAY dependency actualoname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bless),void (*)(struct obj *)),"PRAY dependency bless");
_Static_assert(__builtin_types_compatible_p(__typeof__(&observe_object),void (*)(struct obj *)),"PRAY dependency observe_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&upstart),char *(*)(char *)),"PRAY dependency upstart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ansimpleoname),char *(*)(struct obj *)),"PRAY dependency ansimpleoname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dropy),void (*)(struct obj *)),"PRAY dependency dropy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&known_spell),int (*)(short)),"PRAY dependency known_spell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&simpleonames),char *(*)(struct obj *)),"PRAY dependency simpleonames");
_Static_assert(__builtin_types_compatible_p(__typeof__(&oname),struct obj *(*)(struct obj *, const char *, unsigned int)),"PRAY dependency oname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unrestrict_weapon_skill),void (*)(int)),"PRAY dependency unrestrict_weapon_skill");
_Static_assert(__builtin_types_compatible_p(__typeof__(&discover_artifact),void (*)(xint16)),"PRAY dependency discover_artifact");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xname),char *(*)(struct obj *)),"PRAY dependency xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&weapon_type),int (*)(struct obj *)),"PRAY dependency weapon_type");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_weapon_skill),void (*)(int)),"PRAY dependency add_weapon_skill");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mkobj),struct obj *(*)(int, boolean)),"PRAY dependency mkobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spell_skilltype),int (*)(int)),"PRAY dependency spell_skilltype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd_class),int (*)(int, int)),"PRAY dependency rnd_class");
_Static_assert(__builtin_types_compatible_p(__typeof__(&force_learn_spell),char (*)(short)),"PRAY dependency force_learn_spell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obfree),void (*)(struct obj *, struct obj *)),"PRAY dependency obfree");
_Static_assert(__builtin_types_compatible_p(__typeof__(&discover_object),void (*)(int, boolean, boolean, boolean)),"PRAY dependency discover_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&place_object),void (*)(struct obj *, coordxy, coordxy)),"PRAY dependency place_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy, coordxy)),"PRAY dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&adjalign),void (*)(int)),"PRAY dependency adjalign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnl),int (*)(int)),"PRAY dependency rnl");
_Static_assert(__builtin_types_compatible_p(__typeof__(&otense),char *(*)(struct obj *, const char *)),"PRAY dependency otense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yname),char *(*)(struct obj *)),"PRAY dependency yname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&an),char *(*)(const char *)),"PRAY dependency an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_hear),void (*)(const char *, ...)),"PRAY dependency You_hear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&record_achievement),void (*)(schar)),"PRAY dependency record_achievement");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pluslvl),void (*)(boolean)),"PRAY dependency pluslvl");
_Static_assert(__builtin_types_compatible_p(__typeof__(&see_monsters),void (*)(void)),"PRAY dependency see_monsters");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline_The),void (*)(const char *, ...)),"PRAY dependency pline_The");
_Static_assert(__builtin_types_compatible_p(__typeof__(&useupf),void (*)(struct obj *, long)),"PRAY dependency useupf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exercise),void (*)(int, boolean)),"PRAY dependency exercise");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Amulet_off),void (*)(void)),"PRAY dependency Amulet_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&change_luck),void (*)(schar)),"PRAY dependency change_luck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&uchangealign),void (*)(int, int)),"PRAY dependency uchangealign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&findpriest),struct monst *(*)(char)),"PRAY dependency findpriest");
_Static_assert(__builtin_types_compatible_p(__typeof__(&temple_occupied),char (*)(char *)),"PRAY dependency temple_occupied");
_Static_assert(__builtin_types_compatible_p(__typeof__(&p_coaligned),boolean (*)(struct monst *)),"PRAY dependency p_coaligned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&angry_priest),void (*)(void)),"PRAY dependency angry_priest");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dlord),int (*)(aligntyp)),"PRAY dependency dlord");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makemon),struct monst *(*)(struct permonst *, coordxy, coordxy, mmflags_nht)),"PRAY dependency makemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&a_monnam),char *(*)(struct monst *)),"PRAY dependency a_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmpi),int (*)(const char *, const char *, int)),"PRAY dependency strncmpi");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sgn),int (*)(int)),"PRAY dependency sgn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nomul),void (*)(int)),"PRAY dependency nomul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nartifact_exist),int (*)(void)),"PRAY dependency nartifact_exist");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yn_function),char (*)(const char *, const char *, char, boolean)),"PRAY dependency yn_function");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mk_artifact),struct obj *(*)(struct obj *, aligntyp, uchar, boolean)),"PRAY dependency mk_artifact");
_Static_assert(__builtin_types_compatible_p(__typeof__(&artifact_origin),void (*)(struct obj *, unsigned int)),"PRAY dependency artifact_origin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bare_artifactname),char *(*)(struct obj *)),"PRAY dependency bare_artifactname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&peek_at_iced_corpse_age),long (*)(struct obj *)),"PRAY dependency peek_at_iced_corpse_age");
_Static_assert(__builtin_types_compatible_p(__typeof__(&eaten_stat),int (*)(int, struct obj *)),"PRAY dependency eaten_stat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&floorfood),struct obj *(*)(const char *, int)),"PRAY dependency floorfood");
_Static_assert(__builtin_types_compatible_p(__typeof__(&align_str),const char *(*)(aligntyp)),"PRAY dependency align_str");
_Static_assert(__builtin_types_compatible_p(__typeof__(&corpse_xname),char *(*)(struct obj *, const char *, unsigned int)),"PRAY dependency corpse_xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&feel_cockatrice),void (*)(struct obj *, boolean)),"PRAY dependency feel_cockatrice");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rider_corpse_revival),boolean (*)(struct obj *, boolean)),"PRAY dependency rider_corpse_revival");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_mtraits),struct monst *(*)(struct obj *, boolean)),"PRAY dependency get_mtraits");
_Static_assert(__builtin_types_compatible_p(__typeof__(&revive),struct monst *(*)(struct obj *, boolean)),"PRAY dependency revive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&animate_statue),struct monst *(*)(struct obj *, coordxy, coordxy, int, int *)),"PRAY dependency animate_statue");
_Static_assert(__builtin_types_compatible_p(__typeof__(&paranoid_query),boolean (*)(boolean, const char *)),"PRAY dependency paranoid_query");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wake_nearby),void (*)(boolean)),"PRAY dependency wake_nearby");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losehp),void (*)(int, const char *, schar)),"PRAY dependency losehp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy, coordxy, coordxy, coordxy)),"PRAY dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resist),int (*)(struct monst *, char, int, int)),"PRAY dependency resist");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_malign),void (*)(struct monst *)),"PRAY dependency set_malign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&killed),void (*)(struct monst *)),"PRAY dependency killed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monflee),void (*)(struct monst *, int, boolean, boolean)),"PRAY dependency monflee");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spelleffects),int (*)(int, boolean, boolean)),"PRAY dependency spelleffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_chant),boolean (*)(struct monst *)),"PRAY dependency can_chant");
_Static_assert(__builtin_types_compatible_p(__typeof__(&aggravate),void (*)(void)),"PRAY dependency aggravate");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *, const char *)),"PRAY dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&iter_mons),void (*)(void (*)(struct monst *))),"PRAY dependency iter_mons");
_Static_assert(__builtin_types_compatible_p(__typeof__(&randrole),int (*)(boolean)),"PRAY dependency randrole");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2_on_display_rng),int (*)(int)),"PRAY dependency rn2_on_display_rng");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool_or_lava),boolean (*)(coordxy, coordxy)),"PRAY dependency is_pool_or_lava");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sobj_at),struct obj *(*)(int, coordxy, coordxy)),"PRAY dependency sobj_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&critically_low_hp),boolean (*)(boolean)),"PRAY source prototype critically_low_hp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stuck_in_wall),boolean (*)(void)),"PRAY source prototype stuck_in_wall");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_in_trouble),int (*)(void)),"PRAY source prototype in_trouble");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_worst_cursed_item),struct obj *(*)(void)),"PRAY source prototype worst_cursed_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_fix_curse_trouble),void (*)(struct obj *, const char *)),"PRAY source prototype fix_curse_trouble");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_fix_worst_trouble),void (*)(int)),"PRAY source prototype fix_worst_trouble");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_god_zaps_you),void (*)(aligntyp)),"PRAY source prototype god_zaps_you");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_fry_by_god),void (*)(aligntyp, boolean)),"PRAY source prototype fry_by_god");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_angrygods),void (*)(aligntyp)),"PRAY source prototype angrygods");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_at_your_feet),void (*)(const char *)),"PRAY source prototype at_your_feet");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_gcrownu),void (*)(void)),"PRAY source prototype gcrownu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_give_spell),void (*)(void)),"PRAY source prototype give_spell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_pleased),void (*)(aligntyp)),"PRAY source prototype pleased");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_water_prayer),boolean (*)(boolean)),"PRAY source prototype water_prayer");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_godvoice),void (*)(aligntyp, const char *)),"PRAY source prototype godvoice");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_gods_angry),void (*)(aligntyp)),"PRAY source prototype gods_angry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_gods_upset),void (*)(aligntyp)),"PRAY source prototype gods_upset");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_consume_offering),void (*)(struct obj *)),"PRAY source prototype consume_offering");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_offer_too_soon),void (*)(aligntyp)),"PRAY source prototype offer_too_soon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&desecrate_altar),void (*)(boolean, aligntyp)),"PRAY source prototype desecrate_altar");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_offer_real_amulet),void (*)(struct obj *, aligntyp)),"PRAY source prototype offer_real_amulet");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_offer_negative_valued),void (*)(boolean, aligntyp)),"PRAY source prototype offer_negative_valued");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_offer_fake_amulet),void (*)(struct obj *, boolean, aligntyp)),"PRAY source prototype offer_fake_amulet");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_offer_different_alignment_altar),void (*)(struct obj *, aligntyp)),"PRAY source prototype offer_different_alignment_altar");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_sacrifice_your_race),void (*)(struct obj *, boolean, aligntyp)),"PRAY source prototype sacrifice_your_race");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_bestow_artifact),int (*)(uchar)),"PRAY source prototype bestow_artifact");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_sacrifice_value),int (*)(struct obj *)),"PRAY source prototype sacrifice_value");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dosacrifice),int (*)(void)),"PRAY source prototype dosacrifice");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_eval_offering),int (*)(struct obj *, aligntyp)),"PRAY source prototype eval_offering");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_offer_corpse),void (*)(struct obj *, boolean, aligntyp)),"PRAY source prototype offer_corpse");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_pray),boolean (*)(boolean)),"PRAY source prototype can_pray");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_pray_revive),boolean (*)(void)),"PRAY source prototype pray_revive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dopray),int (*)(void)),"PRAY source prototype dopray");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_prayer_done),int (*)(void)),"PRAY source prototype prayer_done");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_maybe_turn_mon_iter),void (*)(struct monst *)),"PRAY source prototype maybe_turn_mon_iter");
_Static_assert(__builtin_types_compatible_p(__typeof__(&doturn),int (*)(void)),"PRAY source prototype doturn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&altarmask_at),int (*)(coordxy, coordxy)),"PRAY source prototype altarmask_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&a_gname),const char *(*)(void)),"PRAY source prototype a_gname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&a_gname_at),const char *(*)(coordxy, coordxy)),"PRAY source prototype a_gname_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&u_gname),const char *(*)(void)),"PRAY source prototype u_gname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&align_gname),const char *(*)(aligntyp)),"PRAY source prototype align_gname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&halu_gname),const char *(*)(aligntyp)),"PRAY source prototype halu_gname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&align_gtitle),const char *(*)(aligntyp)),"PRAY source prototype align_gtitle");
_Static_assert(__builtin_types_compatible_p(__typeof__(&altar_wrath),void (*)(coordxy, coordxy)),"PRAY source prototype altar_wrath");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_pray_blocked_boulder),boolean (*)(int, int)),"PRAY source prototype blocked_boulder");
