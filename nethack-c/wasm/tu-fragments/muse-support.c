/* MUSE typed ABI/backing only; all config algorithms/tables remain JS. */
#include "muse-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "muse-source-data.h"
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(va_list)==8 && sizeof(size_t)==8,"MUSE memory64 long/pointer/va_list/size_t ABI");
_Static_assert(sizeof(int)==4 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"MUSE scalar ABI");
static char muse_local_statics[MUSE_LOCAL_STATIC_BYTES];
void*teleport_muse_global(int index){switch(index){
case 0:return(void*)&gv;
case 1:return(void*)&svm;
case 2:return(void*)&mons;
case 3:return(void*)&u;
case 4:return(void*)&c_common_strings;
case 5:return(void*)&gm;
case 6:return(void*)&gy;
case 7:return(void*)&genders;
case 8:return(void*)&svl;
case 9:return(void*)&gt;
case 10:return(void*)&svd;
case 11:return(void*)&uwep;
case 12:return(void*)&svc;
case 13:return(void*)&gz;
case 14:return(void*)&iflags;
case 15:return(void*)&uarmu;
case 16:return(void*)&uarm;
case 17:return(void*)&uarmh;
case 18:return(void*)&uarms;
case 19:return(void*)&uarmg;
case 20:return(void*)&uarmc;
case 21:return(void*)&uarmf;
case 22:return(void*)&gb;
case 23:return(void*)&gc;
case 24:return(void*)&uswapwep;
case 25:return(void*)&objects;
case 26:return(void*)&windowprocs;
case 27:return(void*)&flags;
case 28:return(void*)&gu;
case 29:return(void*)&WIN_MAP;
case 30:return(void*)&gn;
case 31:return(void*)&uskin;
case 32:return(void*)&cg;
case 33:return(void*)&hands_obj;
case 34:return(void*)&c_color_names;
case 35:return muse_local_statics;
default:abort();}}
uint64_t teleport_muse_read(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->he);
case 1:return(uint64_t)(uintptr_t)(p->him);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{struct c_color_names*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_green);
default:abort();}}
case 3:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_something);
case 1:return(uint64_t)(uintptr_t)(p->c_Something);
case 2:return(uint64_t)(uintptr_t)(&p->c_fakename);
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroobj);
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->no_of_wizards);
case 1:return(uint64_t)(uintptr_t)(p->bypasses);
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_rogue_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_earth_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_astral_level);
case 3:return(uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 4:return(uint64_t)(uintptr_t)(&p->d_knox_level);
default:abort();}}
case 8:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 9:{struct edog*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hungrytime);
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->female);
case 1:return(uint64_t)(uintptr_t)(p->showrace);
default:abort();}}
case 11:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
default:abort();}}
case 12:{struct instance_globals_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bhitpos);
case 1:return(uint64_t)(uintptr_t)(p->buzzer);
default:abort();}}
case 13:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->current_wand);
default:abort();}}
case 14:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->multi);
case 1:return(uint64_t)(uintptr_t)(p->m_using);
case 2:return(uint64_t)(uintptr_t)(&p->m);
default:abort();}}
case 15:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 16:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 18:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 19:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->moves);
case 1:return(uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 20:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->trapx);
case 1:return(uint64_t)(uintptr_t)(p->trapy);
default:abort();}}
case 21:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 22:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 23:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 24:{struct instance_globals_z*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->zap_oseen);
default:abort();}}
case 25:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sokoban_rules);
default:abort();}}
case 26:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->edog);
default:abort();}}
case 27:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->cham);
case 2:return(uint64_t)(uintptr_t)(p->movement);
case 3:return(uint64_t)(uintptr_t)(p->mx);
case 4:return(uint64_t)(uintptr_t)(p->my);
case 5:return(uint64_t)(uintptr_t)(p->mux);
case 6:return(uint64_t)(uintptr_t)(p->muy);
case 7:return(uint64_t)(uintptr_t)(p->mhp);
case 8:return(uint64_t)(uintptr_t)(p->mhpmax);
case 9:return(uint64_t)(uintptr_t)(p->mappearance);
case 10:return(uint64_t)(uintptr_t)(p->m_ap_type);
case 11:return(uint64_t)(uintptr_t)(p->mtame);
case 12:return(uint64_t)(uintptr_t)(p->seen_resistance);
case 13:return(uint64_t)(uintptr_t)(p->mspec_used);
case 14:return(uint64_t)(uintptr_t)(p->female);
case 15:return(uint64_t)(uintptr_t)(p->minvis);
case 16:return(uint64_t)(uintptr_t)(p->invis_blkd);
case 17:return(uint64_t)(uintptr_t)(p->mcan);
case 18:return(uint64_t)(uintptr_t)(p->mcansee);
case 19:return(uint64_t)(uintptr_t)(p->mspeed);
case 20:return(uint64_t)(uintptr_t)(p->mflee);
case 21:return(uint64_t)(uintptr_t)(p->msleeping);
case 22:return(uint64_t)(uintptr_t)(p->mblinded);
case 23:return(uint64_t)(uintptr_t)(p->mstun);
case 24:return(uint64_t)(uintptr_t)(p->mcanmove);
case 25:return(uint64_t)(uintptr_t)(p->mconf);
case 26:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 27:return(uint64_t)(uintptr_t)(p->mtrapped);
case 28:return(uint64_t)(uintptr_t)(p->isshk);
case 29:return(uint64_t)(uintptr_t)(p->isminion);
case 30:return(uint64_t)(uintptr_t)(p->isgd);
case 31:return(uint64_t)(uintptr_t)(p->ispriest);
case 32:return(uint64_t)(uintptr_t)(p->iswiz);
case 33:return(uint64_t)(uintptr_t)(p->wormno);
case 34:return(uint64_t)(uintptr_t)(p->meverseen);
case 35:return(uint64_t)(uintptr_t)(p->mwandexp);
case 36:return(uint64_t)(uintptr_t)(p->mstrategy);
case 37:return(uint64_t)(uintptr_t)(p->mlstmv);
case 38:return(uint64_t)(uintptr_t)(p->mstate);
case 39:return(uint64_t)(uintptr_t)(p->minvent);
case 40:return(uint64_t)(uintptr_t)(p->mw);
case 41:return(uint64_t)(uintptr_t)(p->misc_worn_check);
case 42:return(uint64_t)(uintptr_t)(p->meating);
case 43:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 28:{struct musable*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->offensive);
case 1:return(uint64_t)(uintptr_t)(p->defensive);
case 2:return(uint64_t)(uintptr_t)(p->misc);
case 3:return(uint64_t)(uintptr_t)(p->has_offense);
case 4:return(uint64_t)(uintptr_t)(p->has_defense);
case 5:return(uint64_t)(uintptr_t)(p->has_misc);
default:abort();}}
case 29:{struct mvitals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->born);
case 1:return(uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 30:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(&p->v);
case 2:return(uint64_t)(uintptr_t)(p->cobj);
case 3:return(uint64_t)(uintptr_t)(p->ox);
case 4:return(uint64_t)(uintptr_t)(p->oy);
case 5:return(uint64_t)(uintptr_t)(p->otyp);
case 6:return(uint64_t)(uintptr_t)(p->owt);
case 7:return(uint64_t)(uintptr_t)(p->quan);
case 8:return(uint64_t)(uintptr_t)(p->spe);
case 9:return(uint64_t)(uintptr_t)(p->oclass);
case 10:return(uint64_t)(uintptr_t)(p->oartifact);
case 11:return(uint64_t)(uintptr_t)(p->where);
case 12:return(uint64_t)(uintptr_t)(p->cursed);
case 13:return(uint64_t)(uintptr_t)(p->blessed);
case 14:return(uint64_t)(uintptr_t)(p->lamplit);
case 15:return(uint64_t)(uintptr_t)(p->dknown);
case 16:return(uint64_t)(uintptr_t)(p->bknown);
case 17:return(uint64_t)(uintptr_t)(p->cknown);
case 18:return(uint64_t)(uintptr_t)(p->nomerge);
case 19:return(uint64_t)(uintptr_t)(p->olocked);
case 20:return(uint64_t)(uintptr_t)(p->otrapped);
case 21:return(uint64_t)(uintptr_t)(p->corpsenm);
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_big);
case 1:return(uint64_t)(uintptr_t)(p->oc_dir);
case 2:return(uint64_t)(uintptr_t)(p->oc_material);
case 3:return(uint64_t)(uintptr_t)(p->oc_subtyp);
default:abort();}}
case 33:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->pmidx);
case 1:return(uint64_t)(uintptr_t)(p->mlet);
case 2:return(uint64_t)(uintptr_t)(p->mmove);
case 3:return(uint64_t)(uintptr_t)(p->geno);
case 4:return(uint64_t)(uintptr_t)(p->msize);
case 5:return(uint64_t)(uintptr_t)(p->mflags1);
case 6:return(uint64_t)(uintptr_t)(p->mflags2);
case 7:return(uint64_t)(uintptr_t)(p->difficulty);
case 8:return(uint64_t)(uintptr_t)(p->mcolor);
default:abort();}}
case 34:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 35:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->flags);
case 2:return(uint64_t)(uintptr_t)(p->candig);
default:abort();}}
case 36:{struct stairway*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->tolev);
case 1:return(uint64_t)(uintptr_t)(p->up);
default:abort();}}
case 37:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tx);
case 1:return(uint64_t)(uintptr_t)(p->ty);
case 2:return(uint64_t)(uintptr_t)(p->ttyp);
case 3:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 38:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 39:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 40:{volatile struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 1:return(uint64_t)(uintptr_t)(p->win_cliparound);
default:abort();}}
case 41:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(&p->uz);
case 3:return(uint64_t)(uintptr_t)(p->ulevel);
case 4:return(uint64_t)(uintptr_t)(&p->uprops);
case 5:return(uint64_t)(uintptr_t)(p->umonster);
case 6:return(uint64_t)(uintptr_t)(p->umonnum);
case 7:return(uint64_t)(uintptr_t)(p->uswallow);
case 8:return(uint64_t)(uintptr_t)(p->uinwater);
case 9:return(uint64_t)(uintptr_t)(p->mfemale);
case 10:return(uint64_t)(uintptr_t)(&p->uroleplay);
case 11:return(uint64_t)(uintptr_t)(p->uac);
case 12:return(uint64_t)(uintptr_t)(p->ustuck);
case 13:return(uint64_t)(uintptr_t)(p->usteed);
case 14:return(uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
default:abort();}}
void teleport_muse_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:p->he=(const char *)value;return;
case 1:p->him=(const char *)value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->mnum=(short)value;return;
default:abort();}}
case 2:{struct c_color_names*p=at;switch(field){
default:abort();}}
case 3:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:p->no_of_wizards=(unsigned int)value;return;
case 1:p->bypasses=(boolean)value;return;
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:p->dnum=(xint16)value;return;
case 1:p->dlevel=(xint16)value;return;
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 3:p->d_sokoban_dnum=(xint16)value;return;
default:abort();}}
case 8:{dlevel_t*p=at;switch(field){
default:abort();}}
case 9:{struct edog*p=at;switch(field){
case 0:p->hungrytime=(long)value;return;
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:p->female=(boolean)value;return;
case 1:p->showrace=(boolean)value;return;
default:abort();}}
case 11:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(int)value;return;
default:abort();}}
case 12:{struct instance_globals_b*p=at;switch(field){
case 1:p->buzzer=(struct monst *)value;return;
default:abort();}}
case 13:{struct instance_globals_c*p=at;switch(field){
case 0:p->current_wand=(struct obj *)value;return;
default:abort();}}
case 14:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=(cmdcount_nht)value;return;
case 1:p->m_using=(boolean)value;return;
default:abort();}}
case 15:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(const char *)value;return;
default:abort();}}
case 16:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 18:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 19:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=(long)value;return;
default:abort();}}
case 20:{struct instance_globals_t*p=at;switch(field){
case 0:p->trapx=(coordxy)value;return;
case 1:p->trapy=(coordxy)value;return;
default:abort();}}
case 21:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(seenV **)value;return;
default:abort();}}
case 23:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_z*p=at;switch(field){
case 0:p->zap_oseen=(boolean)value;return;
default:abort();}}
case 25:{struct levelflags*p=at;switch(field){
case 0:p->sokoban_rules=(unsigned int)value;return;
default:abort();}}
case 26:{struct mextra*p=at;switch(field){
case 0:p->edog=(struct edog *)value;return;
default:abort();}}
case 27:{struct monst*p=at;switch(field){
case 0:p->data=(struct permonst *)value;return;
case 1:p->cham=(short)value;return;
case 2:p->movement=(short)value;return;
case 3:p->mx=(coordxy)value;return;
case 4:p->my=(coordxy)value;return;
case 5:p->mux=(coordxy)value;return;
case 6:p->muy=(coordxy)value;return;
case 7:p->mhp=(int)value;return;
case 8:p->mhpmax=(int)value;return;
case 9:p->mappearance=(unsigned int)value;return;
case 10:p->m_ap_type=(uchar)value;return;
case 11:p->mtame=(schar)value;return;
case 12:p->seen_resistance=(unsigned long)value;return;
case 13:p->mspec_used=(int)value;return;
case 14:p->female=(unsigned int)value;return;
case 15:p->minvis=(unsigned int)value;return;
case 16:p->invis_blkd=(unsigned int)value;return;
case 17:p->mcan=(unsigned int)value;return;
case 18:p->mcansee=(unsigned int)value;return;
case 19:p->mspeed=(unsigned int)value;return;
case 20:p->mflee=(unsigned int)value;return;
case 21:p->msleeping=(unsigned int)value;return;
case 22:p->mblinded=(unsigned int)value;return;
case 23:p->mstun=(unsigned int)value;return;
case 24:p->mcanmove=(unsigned int)value;return;
case 25:p->mconf=(unsigned int)value;return;
case 26:p->mpeaceful=(unsigned int)value;return;
case 27:p->mtrapped=(unsigned int)value;return;
case 28:p->isshk=(unsigned int)value;return;
case 29:p->isminion=(unsigned int)value;return;
case 30:p->isgd=(unsigned int)value;return;
case 31:p->ispriest=(unsigned int)value;return;
case 32:p->iswiz=(unsigned int)value;return;
case 33:p->wormno=(unsigned int)value;return;
case 34:p->meverseen=(unsigned int)value;return;
case 35:p->mwandexp=(unsigned int)value;return;
case 36:p->mstrategy=(unsigned long)value;return;
case 37:p->mlstmv=(long)value;return;
case 38:p->mstate=(long)value;return;
case 39:p->minvent=(struct obj *)value;return;
case 40:p->mw=(struct obj *)value;return;
case 41:p->misc_worn_check=(long)value;return;
case 42:p->meating=(int)value;return;
case 43:p->mextra=(struct mextra *)value;return;
default:abort();}}
case 28:{struct musable*p=at;switch(field){
case 0:p->offensive=(struct obj *)value;return;
case 1:p->defensive=(struct obj *)value;return;
case 2:p->misc=(struct obj *)value;return;
case 3:p->has_offense=(int)value;return;
case 4:p->has_defense=(int)value;return;
case 5:p->has_misc=(int)value;return;
default:abort();}}
case 29:{struct mvitals*p=at;switch(field){
case 0:p->born=(uchar)value;return;
case 1:p->mvflags=(uchar)value;return;
default:abort();}}
case 30:{struct nhcoord*p=at;switch(field){
case 0:p->x=(coordxy)value;return;
case 1:p->y=(coordxy)value;return;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:p->nobj=(struct obj *)value;return;
case 2:p->cobj=(struct obj *)value;return;
case 3:p->ox=(coordxy)value;return;
case 4:p->oy=(coordxy)value;return;
case 5:p->otyp=(short)value;return;
case 6:p->owt=(unsigned int)value;return;
case 7:p->quan=(long)value;return;
case 8:p->spe=(schar)value;return;
case 9:p->oclass=(char)value;return;
case 10:p->oartifact=(char)value;return;
case 11:p->where=(xint8)value;return;
case 12:p->cursed=(unsigned int)value;return;
case 13:p->blessed=(unsigned int)value;return;
case 14:p->lamplit=(unsigned int)value;return;
case 15:p->dknown=(unsigned int)value;return;
case 16:p->bknown=(unsigned int)value;return;
case 17:p->cknown=(unsigned int)value;return;
case 18:p->nomerge=(unsigned int)value;return;
case 19:p->olocked=(unsigned int)value;return;
case 20:p->otrapped=(unsigned int)value;return;
case 21:p->corpsenm=(int)value;return;
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:p->oc_big=(unsigned int)value;return;
case 1:p->oc_dir=(unsigned int)value;return;
case 2:p->oc_material=(unsigned int)value;return;
case 3:p->oc_subtyp=(schar)value;return;
default:abort();}}
case 33:{struct permonst*p=at;switch(field){
case 1:p->mlet=(char)value;return;
case 2:p->mmove=(schar)value;return;
case 3:p->geno=(unsigned short)value;return;
case 4:p->msize=(uchar)value;return;
case 5:p->mflags1=(unsigned long)value;return;
case 6:p->mflags2=(unsigned long)value;return;
case 7:p->difficulty=(uchar)value;return;
case 8:p->mcolor=(uchar)value;return;
default:abort();}}
case 34:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(long)value;return;
case 1:p->blocked=(long)value;return;
case 2:p->intrinsic=(long)value;return;
default:abort();}}
case 35:{struct rm*p=at;switch(field){
case 0:p->typ=(schar)value;return;
case 1:p->flags=(unsigned int)value;return;
case 2:p->candig=(unsigned int)value;return;
default:abort();}}
case 36:{struct stairway*p=at;switch(field){
case 1:p->up=(boolean)value;return;
default:abort();}}
case 37:{struct trap*p=at;switch(field){
case 0:p->tx=(coordxy)value;return;
case 1:p->ty=(coordxy)value;return;
case 2:p->ttyp=(unsigned int)value;return;
case 3:p->tseen=(unsigned int)value;return;
default:abort();}}
case 38:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=(boolean)value;return;
default:abort();}}
case 39:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(struct obj *)value;return;
default:abort();}}
case 40:{volatile struct window_procs*p=at;switch(field){
case 0:p->win_display_nhwindow=(void (*)(winid, boolean))value;return;
case 1:p->win_cliparound=(void (*)(int, int))value;return;
default:abort();}}
case 41:{struct you*p=at;switch(field){
case 0:p->ux=(coordxy)value;return;
case 1:p->uy=(coordxy)value;return;
case 3:p->ulevel=(int)value;return;
case 5:p->umonster=(int)value;return;
case 6:p->umonnum=(int)value;return;
case 7:p->uswallow=(unsigned int)value;return;
case 8:p->uinwater=(unsigned int)value;return;
case 9:p->mfemale=(unsigned int)value;return;
case 11:p->uac=(schar)value;return;
case 12:p->ustuck=(struct monst *)value;return;
case 13:p->usteed=(struct monst *)value;return;
case 14:p->twoweap=(boolean)value;return;
default:abort();}}
default:abort();}}
void* teleport_muse_address(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->he;
case 1:return(void*)&p->him;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{struct c_color_names*p=at;switch(field){
case 0:return(void*)&p->c_green;
default:abort();}}
case 3:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_something;
case 1:return(void*)&p->c_Something;
case 2:return(void*)&p->c_fakename;
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroobj;
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->no_of_wizards;
case 1:return(void*)&p->bypasses;
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_rogue_level;
case 1:return(void*)&p->d_earth_level;
case 2:return(void*)&p->d_astral_level;
case 3:return(void*)&p->d_sokoban_dnum;
case 4:return(void*)&p->d_knox_level;
default:abort();}}
case 8:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->flags;
default:abort();}}
case 9:{struct edog*p=at;switch(field){
case 0:return(void*)&p->hungrytime;
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:return(void*)&p->female;
case 1:return(void*)&p->showrace;
default:abort();}}
case 11:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
default:abort();}}
case 12:{struct instance_globals_b*p=at;switch(field){
case 0:return(void*)&p->bhitpos;
case 1:return(void*)&p->buzzer;
default:abort();}}
case 13:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->current_wand;
default:abort();}}
case 14:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->multi;
case 1:return(void*)&p->m_using;
case 2:return(void*)&p->m;
default:abort();}}
case 15:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nomovemsg;
default:abort();}}
case 16:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 17:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
default:abort();}}
case 18:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 19:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->moves;
case 1:return(void*)&p->mvitals;
default:abort();}}
case 20:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->trapx;
case 1:return(void*)&p->trapy;
default:abort();}}
case 21:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urace;
default:abort();}}
case 22:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->viz_array;
default:abort();}}
case 23:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 24:{struct instance_globals_z*p=at;switch(field){
case 0:return(void*)&p->zap_oseen;
default:abort();}}
case 25:{struct levelflags*p=at;switch(field){
default:abort();}}
case 26:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->edog;
default:abort();}}
case 27:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 1:return(void*)&p->cham;
case 2:return(void*)&p->movement;
case 3:return(void*)&p->mx;
case 4:return(void*)&p->my;
case 5:return(void*)&p->mux;
case 6:return(void*)&p->muy;
case 7:return(void*)&p->mhp;
case 8:return(void*)&p->mhpmax;
case 9:return(void*)&p->mappearance;
case 10:return(void*)&p->m_ap_type;
case 11:return(void*)&p->mtame;
case 12:return(void*)&p->seen_resistance;
case 13:return(void*)&p->mspec_used;
case 36:return(void*)&p->mstrategy;
case 37:return(void*)&p->mlstmv;
case 38:return(void*)&p->mstate;
case 39:return(void*)&p->minvent;
case 40:return(void*)&p->mw;
case 41:return(void*)&p->misc_worn_check;
case 42:return(void*)&p->meating;
case 43:return(void*)&p->mextra;
default:abort();}}
case 28:{struct musable*p=at;switch(field){
case 0:return(void*)&p->offensive;
case 1:return(void*)&p->defensive;
case 2:return(void*)&p->misc;
case 3:return(void*)&p->has_offense;
case 4:return(void*)&p->has_defense;
case 5:return(void*)&p->has_misc;
default:abort();}}
case 29:{struct mvitals*p=at;switch(field){
case 0:return(void*)&p->born;
case 1:return(void*)&p->mvflags;
default:abort();}}
case 30:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->v;
case 2:return(void*)&p->cobj;
case 3:return(void*)&p->ox;
case 4:return(void*)&p->oy;
case 5:return(void*)&p->otyp;
case 6:return(void*)&p->owt;
case 7:return(void*)&p->quan;
case 8:return(void*)&p->spe;
case 9:return(void*)&p->oclass;
case 10:return(void*)&p->oartifact;
case 11:return(void*)&p->where;
case 21:return(void*)&p->corpsenm;
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 3:return(void*)&p->oc_subtyp;
default:abort();}}
case 33:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->pmidx;
case 1:return(void*)&p->mlet;
case 2:return(void*)&p->mmove;
case 3:return(void*)&p->geno;
case 4:return(void*)&p->msize;
case 5:return(void*)&p->mflags1;
case 6:return(void*)&p->mflags2;
case 7:return(void*)&p->difficulty;
case 8:return(void*)&p->mcolor;
default:abort();}}
case 34:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 35:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
default:abort();}}
case 36:{struct stairway*p=at;switch(field){
case 0:return(void*)&p->tolev;
case 1:return(void*)&p->up;
default:abort();}}
case 37:{struct trap*p=at;switch(field){
case 0:return(void*)&p->tx;
case 1:return(void*)&p->ty;
default:abort();}}
case 38:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->deaf;
default:abort();}}
case 39:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
default:abort();}}
case 40:{volatile struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_display_nhwindow;
case 1:return(void*)&p->win_cliparound;
default:abort();}}
case 41:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->uz;
case 3:return(void*)&p->ulevel;
case 4:return(void*)&p->uprops;
case 5:return(void*)&p->umonster;
case 6:return(void*)&p->umonnum;
case 10:return(void*)&p->uroleplay;
case 11:return(void*)&p->uac;
case 12:return(void*)&p->ustuck;
case 13:return(void*)&p->usteed;
case 14:return(void*)&p->twoweap;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_muse_var0(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var1(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var2(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var3(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var4(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var5(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var6(char * a0){(verbalize)(a0);}
void teleport_muse_var7(char * a0){(verbalize)(a0);}
void teleport_muse_var8(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var9(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var10(char * a0,char * a1){(You_hear)(a0,a1);}
void teleport_muse_var11(char * a0,int a1){(impossible)(a0,a1);}
void teleport_muse_var12(char * a0,char * a1){(You_hear)(a0,a1);}
void teleport_muse_var13(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var14(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var15(char * a0,char * a1){(You_hear)(a0,a1);}
int teleport_muse_var16(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_muse_var17(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var18(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_muse_var19(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var20(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_muse_var21(char * a0,char * a1,char * a2){(You_hear)(a0,a1,a2);}
void teleport_muse_var22(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var23(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var24(char * a0){(You_hear)(a0);}
void teleport_muse_var25(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var26(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var27(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var28(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_muse_var29(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var30(char * a0){(impossible)(a0);}
void teleport_muse_var31(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var32(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var33(char * a0){(You_hear)(a0);}
void teleport_muse_var34(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var35(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var36(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var37(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var38(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var39(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var40(char * a0){(pline_The)(a0);}
void teleport_muse_var41(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_muse_var42(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var43(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var44(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var45(char * a0,char * a1,char * a2){(You_hear)(a0,a1,a2);}
void teleport_muse_var46(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var47(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var48(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var49(struct monst * a0,char * a1,char * a2,char * a3,char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_muse_var50(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var51(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var52(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var53(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var54(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var55(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var56(struct monst * a0,char * a1,char * a2,char * a3,char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_muse_var57(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var58(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var59(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var60(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var61(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var62(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var63(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var64(char * a0,char * a1,int a2){(impossible)(a0,a1,a2);}
void teleport_muse_var65(char * a0){(pline)(a0);}
void teleport_muse_var66(char * a0){(pline_The)(a0);}
void teleport_muse_var67(char * a0){(pline_The)(a0);}
void teleport_muse_var68(char * a0){(pline)(a0);}
void teleport_muse_var69(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var70(char * a0,char * a1,char * a2,char * a3){(pline_The)(a0,a1,a2,a3);}
void teleport_muse_var71(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_muse_var72(char * a0){(verbalize)(a0);}
void teleport_muse_var73(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var74(char * a0){(You)(a0);}
void teleport_muse_var75(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var76(char * a0,char * a1,int a2){(impossible)(a0,a1,a2);}
void teleport_muse_var77(char * a0,char * a1,char * a2){(Norep)(a0,a1,a2);}
void teleport_muse_var78(struct monst * a0,char * a1,char * a2,char * a3,char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_muse_var79(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var80(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var81(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var82(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var83(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var84(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var85(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var86(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var87(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var88(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var89(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var90(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var91(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var92(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var93(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var94(struct monst * a0,char * a1,char * a2,char * a3,char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_muse_var95(char * a0,char * a1){(panic)(a0,a1);}
void teleport_muse_var96(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var97(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var98(char * a0,char * a1,char * a2){(urgent_pline)(a0,a1,a2);}
void teleport_muse_var99(char * a0,char * a1,char * a2,int a3){(pline)(a0,a1,a2,a3);}
void teleport_muse_var100(char * a0){(pline_The)(a0);}
void teleport_muse_var101(struct monst * a0,char * a1,char * a2,char * a3,char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_muse_var102(struct monst * a0,char * a1,char * a2,char * a3,char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_muse_var103(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var104(char * a0,char * a1,int a2){(impossible)(a0,a1,a2);}
void teleport_muse_var105(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var106(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_muse_var107(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var108(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var109(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var110(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var111(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var112(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var113(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var114(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var115(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var116(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var117(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var118(struct monst * a0,char * a1,char * a2,char * a3,char * a4){(pline_mon)(a0,a1,a2,a3,a4);}
void teleport_muse_var119(char * a0,char * a1){(You_hear)(a0,a1);}
void teleport_muse_var120(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var121(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var122(char * a0,char * a1){(pline)(a0,a1);}
void teleport_muse_var123(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var124(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var125(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var126(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var127(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_muse_var128(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
void teleport_muse_var129(char * a0){(pline)(a0);}
void teleport_muse_var130(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var131(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_muse_var132(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var133(struct monst * a0,char * a1,char * a2,char * a3){(pline_mon)(a0,a1,a2,a3);}
void teleport_muse_var134(struct monst * a0,char * a1,char * a2){(pline_mon)(a0,a1,a2);}
int teleport_muse_call_object(int(*fn)(struct obj*,struct obj*),struct obj*a,struct obj*b){return fn(a,b);}
int teleport_muse_call_monster(int(*fn)(struct monst*,struct obj*),struct monst*a,struct obj*b){return fn(a,b);}
void teleport_muse_call_buzz(void(*fn)(int,int,coordxy,coordxy,int,int),int a,int b,coordxy c,coordxy d,int e,int f){fn(a,b,c,d,e,f);}
void teleport_muse_call_cursor(void(*fn)(int,int),int a,int b){fn(a,b);}
#pragma clang diagnostic pop
void*teleport_muse_copy(void*to,const void*from,size_t n){return memcpy(to,from,n);}
int teleport_muse_call_rng(int(*fn)(int),int n){return fn(n);}
void teleport_muse_call_window(void(*fn)(winid,boolean),winid id,boolean block){fn(id,block);}
extern int teleport_muse_precheck(struct monst * mon,struct obj * obj);
extern void teleport_muse_mzapwand(struct monst * mtmp,struct obj * otmp,boolean self);
extern void teleport_muse_mplayhorn(struct monst * mtmp,struct obj * otmp,boolean self);
extern void teleport_muse_mreadmsg(struct monst * mtmp,struct obj * otmp);
extern void teleport_muse_mquaffmsg(struct monst * mtmp,struct obj * otmp);
extern boolean teleport_muse_m_use_healing(struct monst * mtmp);
extern boolean teleport_muse_m_sees_sleepy_soldier(struct monst * mtmp);
extern void teleport_muse_m_tele(struct monst * mtmp,boolean vismon,boolean oseen,int how);
extern boolean teleport_muse_m_next2m(struct monst * mtmp);
extern void teleport_muse_reveal_trap(struct trap * t,boolean seeit);
extern int teleport_muse_mon_escape(struct monst * mtmp,boolean vismon);
extern boolean teleport_muse_linedup_chk_corpse(coordxy x,coordxy y);
extern void teleport_muse_m_use_undead_turning(struct monst * mtmp,struct obj * obj);
extern boolean teleport_muse_hero_behind_chokepoint(struct monst * mtmp);
extern boolean teleport_muse_mon_has_friends(struct monst * mtmp);
extern boolean teleport_muse_mon_likes_objpile_at(struct monst * mtmp,coordxy x,coordxy y);
extern int teleport_muse_mbhitm(struct monst * mtmp,struct obj * otmp);
extern boolean teleport_muse_fhito_loc(struct obj * obj,coordxy tx,coordxy ty,int (*fhito)(struct obj *, struct obj *));
extern void teleport_muse_mbhit(struct monst * mon,int range,int (*fhitm)(struct monst *, struct obj *),int (*fhito)(struct obj *, struct obj *),struct obj * obj);
extern void teleport_muse_buzz_force_miss(int type,int nd,coordxy sx,coordxy sy,int dx,int dy);
extern struct permonst * teleport_muse_muse_newcham_mon(struct monst * mon);
extern int teleport_muse_mloot_container(struct monst * mon,struct obj * container,boolean vismon);
extern void teleport_muse_you_aggravate(struct monst * mtmp);
extern void teleport_muse_mon_consume_unstone(struct monst * mon,struct obj * obj,boolean by_you,boolean stoning);
extern boolean teleport_muse_cures_stoning(struct monst * mon,struct obj * obj,boolean tinok);
extern boolean teleport_muse_mcould_eat_tin(struct monst * mon);
extern boolean teleport_muse_muse_unslime(struct monst * mon,struct obj * obj,struct trap * trap,boolean by_you);
extern int teleport_muse_cures_sliming(struct monst * mon,struct obj * obj);
extern boolean teleport_muse_green_mon(struct monst * mon);
uintptr_t teleport_muse_function0(void){return(uintptr_t)doname;}
uintptr_t teleport_muse_function1(void){return(uintptr_t)ansimpleoname;}
uintptr_t teleport_muse_function2(void){return(uintptr_t)teleport_muse_mbhitm;}
uintptr_t teleport_muse_function3(void){return(uintptr_t)bhito;}
uintptr_t teleport_muse_function4(void){return(uintptr_t)teleport_muse_linedup_chk_corpse;}
uintptr_t teleport_muse_function5(void){return(uintptr_t)buzz;}
uintptr_t teleport_muse_function6(void){return(uintptr_t)teleport_muse_buzz_force_miss;}
uintptr_t teleport_muse_function7(void){return(uintptr_t)xname;}
uintptr_t teleport_muse_function8(void){return(uintptr_t)rn2_on_display_rng;}
#include "muse-source-data.h"
static char muse_literals[MUSE_LITERAL_CAPACITY];
char*teleport_muse_literal_storage(void){return muse_literals;}
size_t teleport_muse_literal_capacity(void){return sizeof muse_literals;}
/* Configured source/field/dependency ABI guards; no algorithms. */
_Static_assert(sizeof(size_t)==8 && (size_t)-1>0 && sizeof(long)==8 && (long)-1<0,"MUSE size_t/long64");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2 && (((__typeof__(((struct Race*)0)->mnum))-1<0)==1),"MUSE Race.mnum width/sign");
_Static_assert(sizeof(((struct context_info*)0)->no_of_wizards)==4 && (((__typeof__(((struct context_info*)0)->no_of_wizards))-1<0)==0),"MUSE context_info.no_of_wizards width/sign");
_Static_assert(sizeof(((struct context_info*)0)->bypasses)==1 && (((__typeof__(((struct context_info*)0)->bypasses))-1<0)==1),"MUSE context_info.bypasses width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"MUSE d_level.dnum width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"MUSE d_level.dlevel width/sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)==2 && (((__typeof__(((struct dgn_topology*)0)->d_sokoban_dnum))-1<0)==1),"MUSE dgn_topology.d_sokoban_dnum width/sign");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8 && (((__typeof__(((struct edog*)0)->hungrytime))-1<0)==1),"MUSE edog.hungrytime width/sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1 && (((__typeof__(((struct flag*)0)->female))-1<0)==1),"MUSE flag.female width/sign");
_Static_assert(sizeof(((struct flag*)0)->showrace)==1 && (((__typeof__(((struct flag*)0)->showrace))-1<0)==1),"MUSE flag.showrace width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4 && (((__typeof__(((struct instance_flags*)0)->last_msg))-1<0)==1),"MUSE instance_flags.last_msg width/sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8 && (((__typeof__(((struct instance_globals_m*)0)->multi))-1<0)==1),"MUSE instance_globals_m.multi width/sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->m_using)==1 && (((__typeof__(((struct instance_globals_m*)0)->m_using))-1<0)==1),"MUSE instance_globals_m.m_using width/sign");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8 && (((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1<0)==1),"MUSE instance_globals_saved_m.moves width/sign");
_Static_assert(sizeof(((struct instance_globals_t*)0)->trapx)==2 && (((__typeof__(((struct instance_globals_t*)0)->trapx))-1<0)==1),"MUSE instance_globals_t.trapx width/sign");
_Static_assert(sizeof(((struct instance_globals_t*)0)->trapy)==2 && (((__typeof__(((struct instance_globals_t*)0)->trapy))-1<0)==1),"MUSE instance_globals_t.trapy width/sign");
_Static_assert(sizeof(((struct instance_globals_z*)0)->zap_oseen)==1 && (((__typeof__(((struct instance_globals_z*)0)->zap_oseen))-1<0)==1),"MUSE instance_globals_z.zap_oseen width/sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2 && (((__typeof__(((struct monst*)0)->cham))-1<0)==1),"MUSE monst.cham width/sign");
_Static_assert(sizeof(((struct monst*)0)->movement)==2 && (((__typeof__(((struct monst*)0)->movement))-1<0)==1),"MUSE monst.movement width/sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"MUSE monst.mx width/sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"MUSE monst.my width/sign");
_Static_assert(sizeof(((struct monst*)0)->mux)==2 && (((__typeof__(((struct monst*)0)->mux))-1<0)==1),"MUSE monst.mux width/sign");
_Static_assert(sizeof(((struct monst*)0)->muy)==2 && (((__typeof__(((struct monst*)0)->muy))-1<0)==1),"MUSE monst.muy width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"MUSE monst.mhp width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4 && (((__typeof__(((struct monst*)0)->mhpmax))-1<0)==1),"MUSE monst.mhpmax width/sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4 && (((__typeof__(((struct monst*)0)->mappearance))-1<0)==0),"MUSE monst.mappearance width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"MUSE monst.m_ap_type width/sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"MUSE monst.mtame width/sign");
_Static_assert(sizeof(((struct monst*)0)->seen_resistance)==8 && (((__typeof__(((struct monst*)0)->seen_resistance))-1<0)==0),"MUSE monst.seen_resistance width/sign");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4 && (((__typeof__(((struct monst*)0)->mspec_used))-1<0)==1),"MUSE monst.mspec_used width/sign");
_Static_assert(sizeof(((struct monst*)0)->mstrategy)==8 && (((__typeof__(((struct monst*)0)->mstrategy))-1<0)==0),"MUSE monst.mstrategy width/sign");
_Static_assert(sizeof(((struct monst*)0)->mlstmv)==8 && (((__typeof__(((struct monst*)0)->mlstmv))-1<0)==1),"MUSE monst.mlstmv width/sign");
_Static_assert(sizeof(((struct monst*)0)->mstate)==8 && (((__typeof__(((struct monst*)0)->mstate))-1<0)==1),"MUSE monst.mstate width/sign");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8 && (((__typeof__(((struct monst*)0)->misc_worn_check))-1<0)==1),"MUSE monst.misc_worn_check width/sign");
_Static_assert(sizeof(((struct monst*)0)->meating)==4 && (((__typeof__(((struct monst*)0)->meating))-1<0)==1),"MUSE monst.meating width/sign");
_Static_assert(sizeof(((struct musable*)0)->has_offense)==4 && (((__typeof__(((struct musable*)0)->has_offense))-1<0)==1),"MUSE musable.has_offense width/sign");
_Static_assert(sizeof(((struct musable*)0)->has_defense)==4 && (((__typeof__(((struct musable*)0)->has_defense))-1<0)==1),"MUSE musable.has_defense width/sign");
_Static_assert(sizeof(((struct musable*)0)->has_misc)==4 && (((__typeof__(((struct musable*)0)->has_misc))-1<0)==1),"MUSE musable.has_misc width/sign");
_Static_assert(sizeof(((struct mvitals*)0)->born)==1 && (((__typeof__(((struct mvitals*)0)->born))-1<0)==0),"MUSE mvitals.born width/sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1 && (((__typeof__(((struct mvitals*)0)->mvflags))-1<0)==0),"MUSE mvitals.mvflags width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2 && (((__typeof__(((struct nhcoord*)0)->x))-1<0)==1),"MUSE nhcoord.x width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2 && (((__typeof__(((struct nhcoord*)0)->y))-1<0)==1),"MUSE nhcoord.y width/sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2 && (((__typeof__(((struct obj*)0)->ox))-1<0)==1),"MUSE obj.ox width/sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2 && (((__typeof__(((struct obj*)0)->oy))-1<0)==1),"MUSE obj.oy width/sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"MUSE obj.otyp width/sign");
_Static_assert(sizeof(((struct obj*)0)->owt)==4 && (((__typeof__(((struct obj*)0)->owt))-1<0)==0),"MUSE obj.owt width/sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"MUSE obj.quan width/sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1 && (((__typeof__(((struct obj*)0)->spe))-1<0)==1),"MUSE obj.spe width/sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1 && (((__typeof__(((struct obj*)0)->oclass))-1<0)==1),"MUSE obj.oclass width/sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1 && (((__typeof__(((struct obj*)0)->oartifact))-1<0)==1),"MUSE obj.oartifact width/sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1 && (((__typeof__(((struct obj*)0)->where))-1<0)==1),"MUSE obj.where width/sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4 && (((__typeof__(((struct obj*)0)->corpsenm))-1<0)==1),"MUSE obj.corpsenm width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1 && (((__typeof__(((struct objclass*)0)->oc_subtyp))-1<0)==1),"MUSE objclass.oc_subtyp width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"MUSE permonst.mlet width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mmove)==1 && (((__typeof__(((struct permonst*)0)->mmove))-1<0)==1),"MUSE permonst.mmove width/sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2 && (((__typeof__(((struct permonst*)0)->geno))-1<0)==0),"MUSE permonst.geno width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1 && (((__typeof__(((struct permonst*)0)->msize))-1<0)==0),"MUSE permonst.msize width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"MUSE permonst.mflags1 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8 && (((__typeof__(((struct permonst*)0)->mflags2))-1<0)==0),"MUSE permonst.mflags2 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->difficulty)==1 && (((__typeof__(((struct permonst*)0)->difficulty))-1<0)==0),"MUSE permonst.difficulty width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mcolor)==1 && (((__typeof__(((struct permonst*)0)->mcolor))-1<0)==0),"MUSE permonst.mcolor width/sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"MUSE prop.extrinsic width/sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"MUSE prop.blocked width/sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"MUSE prop.intrinsic width/sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"MUSE rm.typ width/sign");
_Static_assert(sizeof(((struct stairway*)0)->up)==1 && (((__typeof__(((struct stairway*)0)->up))-1<0)==1),"MUSE stairway.up width/sign");
_Static_assert(sizeof(((struct trap*)0)->tx)==2 && (((__typeof__(((struct trap*)0)->tx))-1<0)==1),"MUSE trap.tx width/sign");
_Static_assert(sizeof(((struct trap*)0)->ty)==2 && (((__typeof__(((struct trap*)0)->ty))-1<0)==1),"MUSE trap.ty width/sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1 && (((__typeof__(((struct u_roleplay*)0)->deaf))-1<0)==1),"MUSE u_roleplay.deaf width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"MUSE you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"MUSE you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4 && (((__typeof__(((struct you*)0)->ulevel))-1<0)==1),"MUSE you.ulevel width/sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"MUSE you.umonster width/sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"MUSE you.umonnum width/sign");
_Static_assert(sizeof(((struct you*)0)->uac)==1 && (((__typeof__(((struct you*)0)->uac))-1<0)==1),"MUSE you.uac width/sign");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1 && (((__typeof__(((struct you*)0)->twoweap))-1<0)==1),"MUSE you.twoweap width/sign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&objdescr_is),boolean (*)(struct obj *, const char *)),"MUSE dependency objdescr_is");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"MUSE dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *, int, const char *)),"MUSE dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"MUSE dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&enexto),boolean (*)(coord *, coordxy, coordxy, struct permonst *)),"MUSE dependency enexto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_useup),void (*)(struct monst *, struct obj *)),"MUSE dependency m_useup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makemon),struct monst *(*)(struct permonst *, coordxy, coordxy, mmflags_nht)),"MUSE dependency makemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline),void (*)(const char *, ...)),"MUSE dependency pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_nam),char *(*)(struct monst *)),"MUSE dependency mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rndmonnam),char *(*)(char *)),"MUSE dependency rndmonnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Monnam),char *(*)(struct monst *)),"MUSE dependency Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&paralyze_monst),void (*)(struct monst *, int)),"MUSE dependency paralyze_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline_mon),void (*)(struct monst *, const char *, ...)),"MUSE dependency pline_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&a_monnam),char *(*)(struct monst *)),"MUSE dependency a_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&verbalize),void (*)(const char *, ...)),"MUSE dependency verbalize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_malign),void (*)(struct monst *)),"MUSE dependency set_malign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mongone),void (*)(struct monst *)),"MUSE dependency mongone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&d),int (*)(int, int)),"MUSE dependency d");
_Static_assert(__builtin_types_compatible_p(__typeof__(&an),char *(*)(const char *)),"MUSE dependency an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xname),char *(*)(struct obj *)),"MUSE dependency xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_hear),void (*)(const char *, ...)),"MUSE dependency You_hear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy, coordxy, coordxy, coordxy)),"MUSE dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monkilled),void (*)(struct monst *, const char *, int)),"MUSE dependency monkilled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&impossible),void (*)(const char *, ...)),"MUSE dependency impossible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"MUSE dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unknow_object),void (*)(struct obj *)),"MUSE dependency unknow_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monverbself),char *(*)(struct monst *, char *, const char *, const char *)),"MUSE dependency monverbself");
_Static_assert(__builtin_types_compatible_p(__typeof__(&doname),char *(*)(struct obj *)),"MUSE dependency doname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stop_occupation),void (*)(void)),"MUSE dependency stop_occupation");
_Static_assert(__builtin_types_compatible_p(__typeof__(&observe_object),void (*)(struct obj *)),"MUSE dependency observe_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strlen),unsigned long (*)(const char *)),"MUSE dependency strlen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&simpleonames),char *(*)(struct obj *)),"MUSE dependency simpleonames");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sprintf),int (*)(char *restrict, const char *restrict, ...)),"MUSE dependency sprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&discover_object),void (*)(int, boolean, boolean, boolean)),"MUSE dependency discover_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"MUSE dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char *(*)(char *, const char *)),"MUSE dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&singular),const char *(*)(struct obj *, char *(*)(struct obj *))),"MUSE dependency singular");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ansimpleoname),char *(*)(struct obj *)),"MUSE dependency ansimpleoname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&same_race),boolean (*)(struct permonst *, struct permonst *)),"MUSE dependency same_race");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_invisible),void (*)(coordxy, coordxy)),"MUSE dependency map_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_snprintf),void (*)(const char *, int, char *, size_t, const char *, ...)),"MUSE dependency nh_snprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strsubst),char *(*)(char *, const char *, const char *)),"MUSE dependency strsubst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&x_monnam),char *(*)(struct monst *, int, const char *, int, boolean)),"MUSE dependency x_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flash_mon),void (*)(struct monst *)),"MUSE dependency flash_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pronoun_gender),int (*)(struct monst *, unsigned int)),"MUSE dependency pronoun_gender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_carrying),struct obj *(*)(struct monst *, int)),"MUSE dependency m_carrying");
_Static_assert(__builtin_types_compatible_p(__typeof__(&isok),int (*)(coordxy, coordxy)),"MUSE dependency isok");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tele_restrict),boolean (*)(struct monst *)),"MUSE dependency tele_restrict");
_Static_assert(__builtin_types_compatible_p(__typeof__(&noteleport_level),boolean (*)(struct monst *)),"MUSE dependency noteleport_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_learns_traps),void (*)(struct monst *, int)),"MUSE dependency mon_learns_traps");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_has_amulet),int (*)(struct monst *)),"MUSE dependency mon_has_amulet");
_Static_assert(__builtin_types_compatible_p(__typeof__(&On_W_tower_level),boolean (*)(d_level *)),"MUSE dependency On_W_tower_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rloc),boolean (*)(struct monst *, unsigned int)),"MUSE dependency rloc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mintrap),int (*)(struct monst *, unsigned int)),"MUSE dependency mintrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),boolean (*)(d_level *, d_level *)),"MUSE dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&poly_when_stoned),boolean (*)(struct permonst *)),"MUSE dependency poly_when_stoned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Resists_Elem),boolean (*)(struct monst *, int)),"MUSE dependency Resists_Elem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lined_up),boolean (*)(struct monst *)),"MUSE dependency lined_up");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stairway_at),stairway *(*)(coordxy, coordxy)),"MUSE dependency stairway_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&t_at),struct trap *(*)(coordxy, coordxy)),"MUSE dependency t_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sobj_at),struct obj *(*)(int, coordxy, coordxy)),"MUSE dependency sobj_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&onscary),boolean (*)(coordxy, coordxy, struct monst *)),"MUSE dependency onscary");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Can_fall_thru),boolean (*)(d_level *)),"MUSE dependency Can_fall_thru");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Is_botlevel),boolean (*)(d_level *)),"MUSE dependency Is_botlevel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_ice),boolean (*)(coordxy, coordxy)),"MUSE dependency is_ice");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool),boolean (*)(coordxy, coordxy)),"MUSE dependency is_pool");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_lava),boolean (*)(coordxy, coordxy)),"MUSE dependency is_lava");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_V_tower),boolean (*)(d_level *)),"MUSE dependency In_V_tower");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_knows_traps),boolean (*)(struct monst *, int)),"MUSE dependency mon_knows_traps");
_Static_assert(__builtin_types_compatible_p(__typeof__(&inhishop),int (*)(struct monst *)),"MUSE dependency inhishop");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unblock_point),void (*)(int, int)),"MUSE dependency unblock_point");
_Static_assert(__builtin_types_compatible_p(__typeof__(&seetrap),void (*)(struct trap *)),"MUSE dependency seetrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_has_special),int (*)(struct monst *)),"MUSE dependency mon_has_special");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline_The),void (*)(const char *, ...)),"MUSE dependency pline_The");
_Static_assert(__builtin_types_compatible_p(__typeof__(&panic),void (*)(const char *, ...)),"MUSE dependency panic");
_Static_assert(__builtin_types_compatible_p(__typeof__(&awaken_soldiers),void (*)(struct monst *)),"MUSE dependency awaken_soldiers");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monflee),void (*)(struct monst *, int, boolean, boolean)),"MUSE dependency monflee");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bhito),int (*)(struct obj *, struct obj *)),"MUSE dependency bhito");
_Static_assert(__builtin_types_compatible_p(__typeof__(&splitobj),struct obj *(*)(struct obj *, long)),"MUSE dependency splitobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&extract_from_minvent),void (*)(struct monst *, struct obj *, boolean, boolean)),"MUSE dependency extract_from_minvent");
_Static_assert(__builtin_types_compatible_p(__typeof__(&random_teleport_level),int (*)(void)),"MUSE dependency random_teleport_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&depth),schar (*)(d_level *)),"MUSE dependency depth");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_level),void (*)(d_level *, int)),"MUSE dependency get_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&migrate_to_level),void (*)(struct monst *, xint16, xint16, coord *)),"MUSE dependency migrate_to_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ledger_no),xint16 (*)(d_level *)),"MUSE dependency ledger_no");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trycall),void (*)(struct obj *)),"MUSE dependency trycall");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obfree),void (*)(struct obj *, struct obj *)),"MUSE dependency obfree");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_drawbridge_wall),int (*)(coordxy, coordxy)),"MUSE dependency is_drawbridge_wall");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Can_dig_down),boolean (*)(d_level *)),"MUSE dependency Can_dig_down");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maketrap),struct trap *(*)(coordxy, coordxy, int)),"MUSE dependency maketrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&surface),const char *(*)(coordxy, coordxy)),"MUSE dependency surface");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fill_pit),void (*)(coordxy, coordxy)),"MUSE dependency fill_pit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&recalc_block_point),void (*)(coordxy, coordxy)),"MUSE dependency recalc_block_point");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd),int (*)(int)),"MUSE dependency rnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vtense),char *(*)(const char *, const char *)),"MUSE dependency vtense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&locomotion),const char *(*)(const struct permonst *, const char *)),"MUSE dependency locomotion");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trapname),const char *(*)(int, boolean)),"MUSE dependency trapname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy, coordxy)),"MUSE dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&place_monster),void (*)(struct monst *, coordxy, coordxy)),"MUSE dependency place_monster");
_Static_assert(__builtin_types_compatible_p(__typeof__(&worm_move),void (*)(struct monst *)),"MUSE dependency worm_move");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_hell),boolean (*)(d_level *)),"MUSE dependency In_hell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dunlev),xint16 (*)(d_level *)),"MUSE dependency dunlev");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dunlevs_in_dungeon),xint16 (*)(d_level *)),"MUSE dependency dunlevs_in_dungeon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maybe_unhide_at),void (*)(coordxy, coordxy)),"MUSE dependency maybe_unhide_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bcsign),int (*)(struct obj *)),"MUSE dependency bcsign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&healmon),int (*)(struct monst *, int, int)),"MUSE dependency healmon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unbless),void (*)(struct obj *)),"MUSE dependency unbless");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype),boolean (*)(struct permonst *, int)),"MUSE dependency attacktype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sgn),int (*)(int)),"MUSE dependency sgn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&carrying),struct obj *(*)(int)),"MUSE dependency carrying");
_Static_assert(__builtin_types_compatible_p(__typeof__(&linedup_callback),boolean (*)(coordxy, coordxy, coordxy, coordxy, boolean (*)(coordxy, coordxy))),"MUSE dependency linedup_callback");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xytodir),int (*)(int, int)),"MUSE dependency xytodir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dirtocoord),void (*)(coord *, int)),"MUSE dependency dirtocoord");
_Static_assert(__builtin_types_compatible_p(__typeof__(&accessible),boolean (*)(coordxy, coordxy)),"MUSE dependency accessible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_would_take_item),boolean (*)(struct monst *, struct obj *)),"MUSE dependency mon_would_take_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&in_your_sanctuary),boolean (*)(struct monst *, coordxy, coordxy)),"MUSE dependency in_your_sanctuary");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype),boolean (*)(struct permonst *, int)),"MUSE dependency dmgtype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monnear),boolean (*)(struct monst *, coordxy, coordxy)),"MUSE dependency monnear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&which_armor),struct obj *(*)(struct monst *, long)),"MUSE dependency which_armor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_blow),boolean (*)(struct monst *)),"MUSE dependency can_blow");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hard_helmet),boolean (*)(struct obj *)),"MUSE dependency hard_helmet");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resists_blnd),boolean (*)(struct monst *)),"MUSE dependency resists_blnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&seemimic),void (*)(struct monst *)),"MUSE dependency seemimic");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monstseesu),void (*)(unsigned long)),"MUSE dependency monstseesu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&shieldeff),void (*)(coordxy, coordxy)),"MUSE dependency shieldeff");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monstunseesu),void (*)(unsigned long)),"MUSE dependency monstunseesu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losehp),void (*)(int, const char *, schar)),"MUSE dependency losehp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nomul),void (*)(int)),"MUSE dependency nomul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resists_magm),boolean (*)(struct monst *)),"MUSE dependency resists_magm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_mac),int (*)(struct monst *)),"MUSE dependency find_mac");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hit),void (*)(const char *, struct monst *, const char *)),"MUSE dependency hit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exclam),const char *(*)(int)),"MUSE dependency exclam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resist),int (*)(struct monst *, char, int, int)),"MUSE dependency resist");
_Static_assert(__builtin_types_compatible_p(__typeof__(&miss),void (*)(const char *, struct monst *)),"MUSE dependency miss");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tele),void (*)(void)),"MUSE dependency tele");
_Static_assert(__builtin_types_compatible_p(__typeof__(&in_rooms),char *(*)(coordxy, coordxy, int)),"MUSE dependency in_rooms");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cancel_monst),boolean (*)(struct monst *, struct obj *, boolean, boolean, boolean)),"MUSE dependency cancel_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unturn_you),void (*)(void)),"MUSE dependency unturn_you");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unturn_dead),int (*)(struct monst *)),"MUSE dependency unturn_dead");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wakeup),void (*)(struct monst *, boolean)),"MUSE dependency wakeup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_drawbridge),boolean (*)(coordxy *, coordxy *)),"MUSE dependency find_drawbridge");
_Static_assert(__builtin_types_compatible_p(__typeof__(&destroy_drawbridge),void (*)(coordxy, coordxy)),"MUSE dependency destroy_drawbridge");
_Static_assert(__builtin_types_compatible_p(__typeof__(&doorlock),boolean (*)(struct obj *, coordxy, coordxy)),"MUSE dependency doorlock");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_damage),void (*)(coordxy, coordxy, long)),"MUSE dependency add_damage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dobuzz),void (*)(int, int, coordxy, coordxy, int, int, boolean, boolean, boolean)),"MUSE dependency dobuzz");
_Static_assert(__builtin_types_compatible_p(__typeof__(&buzz),void (*)(int, int, coordxy, coordxy, int, int)),"MUSE dependency buzz");
_Static_assert(__builtin_types_compatible_p(__typeof__(&abs),int (*)(int)),"MUSE dependency abs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ceiling),const char *(*)(coordxy, coordxy)),"MUSE dependency ceiling");
_Static_assert(__builtin_types_compatible_p(__typeof__(&closed_door),boolean (*)(coordxy, coordxy)),"MUSE dependency closed_door");
_Static_assert(__builtin_types_compatible_p(__typeof__(&drop_boulder_on_monster),boolean (*)(coordxy, coordxy, boolean, boolean)),"MUSE dependency drop_boulder_on_monster");
_Static_assert(__builtin_types_compatible_p(__typeof__(&distmin),int (*)(coordxy, coordxy, coordxy, coordxy)),"MUSE dependency distmin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&drop_boulder_on_player),void (*)(boolean, boolean, boolean, boolean)),"MUSE dependency drop_boulder_on_player");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You),void (*)(const char *, ...)),"MUSE dependency You");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_blinded),void (*)(long, boolean)),"MUSE dependency make_blinded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lightdamage),int (*)(struct obj *, boolean, int)),"MUSE dependency lightdamage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_throw),void (*)(struct monst *, coordxy, coordxy, coordxy, coordxy, int, struct obj *)),"MUSE dependency m_throw");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wearing_iron_shoes),boolean (*)(struct monst *)),"MUSE dependency wearing_iron_shoes");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canletgo),boolean (*)(struct obj *, const char *)),"MUSE dependency canletgo");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rndmonst),struct permonst *(*)(void)),"MUSE dependency rndmonst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&__assert_fail),void (*)(const char *, const char *, int, const char *)),"MUSE dependency __assert_fail");
_Static_assert(__builtin_types_compatible_p(__typeof__(&distant_name),char *(*)(struct obj *, char *(*)(struct obj *))),"MUSE dependency distant_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obj_extract_self),void (*)(struct obj *)),"MUSE dependency obj_extract_self");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_carry),int (*)(struct monst *, struct obj *)),"MUSE dependency can_carry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Norep),void (*)(const char *, ...)),"MUSE dependency Norep");
_Static_assert(__builtin_types_compatible_p(__typeof__(&upstart),char *(*)(char *)),"MUSE dependency upstart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&removed_from_icebox),void (*)(struct obj *)),"MUSE dependency removed_from_icebox");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mpickobj),int (*)(struct monst *, struct obj *)),"MUSE dependency mpickobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_to_container),struct obj *(*)(struct obj *, struct obj *)),"MUSE dependency add_to_container");
_Static_assert(__builtin_types_compatible_p(__typeof__(&weight),int (*)(struct obj *)),"MUSE dependency weight");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Can_rise_up),boolean (*)(coordxy, coordxy, d_level *)),"MUSE dependency Can_rise_up");
_Static_assert(__builtin_types_compatible_p(__typeof__(&grow_up),struct permonst *(*)(struct monst *, struct monst *)),"MUSE dependency grow_up");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_set_minvis),void (*)(struct monst *, boolean)),"MUSE dependency mon_set_minvis");
_Static_assert(__builtin_types_compatible_p(__typeof__(&s_suffix),char *(*)(const char *)),"MUSE dependency s_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_adjust_speed),void (*)(struct monst *, int, struct obj *)),"MUSE dependency mon_adjust_speed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newcham),int (*)(struct monst *, struct permonst *, unsigned int)),"MUSE dependency newcham");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Some_Monnam),char *(*)(struct monst *)),"MUSE dependency Some_Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&the),char *(*)(const char *)),"MUSE dependency the");
_Static_assert(__builtin_types_compatible_p(__typeof__(&body_part),const char *(*)(int)),"MUSE dependency body_part");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makeplural),char *(*)(const char *)),"MUSE dependency makeplural");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncpy),char *(*)(char *, const char *, unsigned long)),"MUSE dependency strncpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&urgent_pline),void (*)(const char *, ...)),"MUSE dependency urgent_pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&welded),int (*)(struct obj *)),"MUSE dependency welded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&undiscovered_artifact),boolean (*)(xint16)),"MUSE dependency undiscovered_artifact");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_hates_silver),boolean (*)(struct monst *)),"MUSE dependency mon_hates_silver");
_Static_assert(__builtin_types_compatible_p(__typeof__(&remove_worn_item),void (*)(struct obj *, boolean)),"MUSE dependency remove_worn_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&freeinv),void (*)(struct obj *)),"MUSE dependency freeinv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&place_object),void (*)(struct obj *, coordxy, coordxy)),"MUSE dependency place_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dropy),void (*)(struct obj *)),"MUSE dependency dropy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&noit_mon_nam),char *(*)(struct monst *)),"MUSE dependency noit_mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cls),void (*)(void)),"MUSE dependency cls");
_Static_assert(__builtin_types_compatible_p(__typeof__(&show_glyph),void (*)(coordxy, coordxy, int)),"MUSE dependency show_glyph");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2_on_display_rng),int (*)(int)),"MUSE dependency rn2_on_display_rng");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_visible),int (*)(struct monst *)),"MUSE dependency mon_visible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_mines),boolean (*)(d_level *)),"MUSE dependency In_mines");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_feel),void (*)(const char *, ...)),"MUSE dependency You_feel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&docrt),void (*)(void)),"MUSE dependency docrt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unconscious),boolean (*)(void)),"MUSE dependency unconscious");
_Static_assert(__builtin_types_compatible_p(__typeof__(&arti_reflects),boolean (*)(struct obj *)),"MUSE dependency arti_reflects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dog_nutrition),int (*)(struct monst *, struct obj *)),"MUSE dependency dog_nutrition");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xkilled),void (*)(struct monst *, int)),"MUSE dependency xkilled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mondead),void (*)(struct monst *)),"MUSE dependency mondead");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mwelded),boolean (*)(struct obj *)),"MUSE dependency mwelded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype_fordmg),struct attack *(*)(struct permonst *, int, int)),"MUSE dependency attacktype_fordmg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hcolor),const char *(*)(const char *)),"MUSE dependency hcolor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&zhitm),int (*)(struct monst *, int, int, struct obj **)),"MUSE dependency zhitm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&explode),void (*)(coordxy, coordxy, int, int, char, int)),"MUSE dependency explode");
_Static_assert(__builtin_types_compatible_p(__typeof__(&begin_burn),void (*)(struct obj *, boolean)),"MUSE dependency begin_burn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_fainted),boolean (*)(void)),"MUSE dependency is_fainted");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_precheck),int (*)(struct monst *, struct obj *)),"MUSE source prototype precheck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mzapwand),void (*)(struct monst *, struct obj *, boolean)),"MUSE source prototype mzapwand");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mplayhorn),void (*)(struct monst *, struct obj *, boolean)),"MUSE source prototype mplayhorn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mreadmsg),void (*)(struct monst *, struct obj *)),"MUSE source prototype mreadmsg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mquaffmsg),void (*)(struct monst *, struct obj *)),"MUSE source prototype mquaffmsg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_m_use_healing),boolean (*)(struct monst *)),"MUSE source prototype m_use_healing");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_m_sees_sleepy_soldier),boolean (*)(struct monst *)),"MUSE source prototype m_sees_sleepy_soldier");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_m_tele),void (*)(struct monst *, boolean, boolean, int)),"MUSE source prototype m_tele");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_m_next2m),boolean (*)(struct monst *)),"MUSE source prototype m_next2m");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_defensive),boolean (*)(struct monst *, boolean)),"MUSE source prototype find_defensive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_reveal_trap),void (*)(struct trap *, boolean)),"MUSE source prototype reveal_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mon_escape),int (*)(struct monst *, boolean)),"MUSE source prototype mon_escape");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_defensive),int (*)(struct monst *)),"MUSE source prototype use_defensive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd_defensive_item),int (*)(struct monst *)),"MUSE source prototype rnd_defensive_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_linedup_chk_corpse),boolean (*)(coordxy, coordxy)),"MUSE source prototype linedup_chk_corpse");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_m_use_undead_turning),void (*)(struct monst *, struct obj *)),"MUSE source prototype m_use_undead_turning");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_hero_behind_chokepoint),boolean (*)(struct monst *)),"MUSE source prototype hero_behind_chokepoint");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mon_has_friends),boolean (*)(struct monst *)),"MUSE source prototype mon_has_friends");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mon_likes_objpile_at),boolean (*)(struct monst *, coordxy, coordxy)),"MUSE source prototype mon_likes_objpile_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_offensive),boolean (*)(struct monst *)),"MUSE source prototype find_offensive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mbhitm),int (*)(struct monst *, struct obj *)),"MUSE source prototype mbhitm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_fhito_loc),boolean (*)(struct obj *, coordxy, coordxy, int (*)(struct obj *, struct obj *))),"MUSE source prototype fhito_loc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mbhit),void (*)(struct monst *, int, int (*)(struct monst *, struct obj *), int (*)(struct obj *, struct obj *), struct obj *)),"MUSE source prototype mbhit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_buzz_force_miss),void (*)(int, int, coordxy, coordxy, int, int)),"MUSE source prototype buzz_force_miss");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_offensive),int (*)(struct monst *)),"MUSE source prototype use_offensive");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd_offensive_item),int (*)(struct monst *)),"MUSE source prototype rnd_offensive_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_misc),boolean (*)(struct monst *)),"MUSE source prototype find_misc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_muse_newcham_mon),struct permonst *(*)(struct monst *)),"MUSE source prototype muse_newcham_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mloot_container),int (*)(struct monst *, struct obj *, boolean)),"MUSE source prototype mloot_container");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_misc),int (*)(struct monst *)),"MUSE source prototype use_misc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_you_aggravate),void (*)(struct monst *)),"MUSE source prototype you_aggravate");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd_misc_item),int (*)(struct monst *)),"MUSE source prototype rnd_misc_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&searches_for_item),boolean (*)(struct monst *, struct obj *)),"MUSE source prototype searches_for_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_reflects),boolean (*)(struct monst *, const char *)),"MUSE source prototype mon_reflects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ureflects),boolean (*)(const char *, const char *)),"MUSE source prototype ureflects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mcureblindness),void (*)(struct monst *, boolean)),"MUSE source prototype mcureblindness");
_Static_assert(__builtin_types_compatible_p(__typeof__(&munstone),boolean (*)(struct monst *, boolean)),"MUSE source prototype munstone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mon_consume_unstone),void (*)(struct monst *, struct obj *, boolean, boolean)),"MUSE source prototype mon_consume_unstone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_cures_stoning),boolean (*)(struct monst *, struct obj *, boolean)),"MUSE source prototype cures_stoning");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_mcould_eat_tin),boolean (*)(struct monst *)),"MUSE source prototype mcould_eat_tin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&munslime),boolean (*)(struct monst *, boolean)),"MUSE source prototype munslime");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_muse_unslime),boolean (*)(struct monst *, struct obj *, struct trap *, boolean)),"MUSE source prototype muse_unslime");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_cures_sliming),int (*)(struct monst *, struct obj *)),"MUSE source prototype cures_sliming");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_muse_green_mon),boolean (*)(struct monst *)),"MUSE source prototype green_mon");
