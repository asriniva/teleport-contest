/* DETECT typed ABI/backing only; all config algorithms/tables remain JS. */
#include "detect-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(va_list)==8 && sizeof(size_t)==8,"DETECT memory64 long/pointer/va_list/size_t ABI");
_Static_assert(sizeof(int)==4 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"DETECT scalar ABI");
static struct trap detect_dummytrap;
void*teleport_detect_global(int index){switch(index){
case 0:return(void*)&u;
case 1:return(void*)&iflags;
case 2:return(void*)&def_monsyms;
case 3:return(void*)&mons;
case 4:return(void*)&gi;
case 5:return(void*)&svl;
case 6:return(void*)&objects;
case 7:return(void*)&gk;
case 8:return(void*)&gy;
case 9:return(void*)&cg;
case 10:return(void*)&c_common_strings;
case 11:return(void*)&flags;
case 12:return(void*)&def_oc_syms;
case 13:return(void*)&gs;
case 14:return(void*)&WIN_MAP;
case 15:return(void*)&windowprocs;
case 16:return(void*)&gu;
case 17:return(void*)&svd;
case 18:return(void*)&gf;
case 19:return(void*)&gd;
case 20:return(void*)&gm;
case 21:return(void*)&gn;
case 22:return(void*)&quitchars;
case 23:return(void*)&gv;
case 24:return(void*)&WIN_MESSAGE;
case 25:return(void*)&uwep;
case 26:return(void*)&ublindf;
case 27:return(void*)&ga;
case 28:return &detect_dummytrap;
default:abort();}}
uint64_t teleport_detect_read(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_something);
case 1:return(uint64_t)(uintptr_t)(p->c_Never_mind);
case 2:return(uint64_t)(uintptr_t)(p->c_vision_clears);
default:abort();}}
case 3:{struct class_sym*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sym);
case 1:return(uint64_t)(uintptr_t)(p->name);
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroobj);
default:abort();}}
case 5:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 6:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_oracle_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_rogue_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_medusa_level);
case 3:return(uint64_t)(uintptr_t)(&p->d_stronghold_level);
case 4:return(uint64_t)(uintptr_t)(&p->d_wiz1_level);
case 5:return(uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 6:return(uint64_t)(uintptr_t)(&p->d_knox_level);
default:abort();}}
case 7:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(p->objlist);
case 4:return(uint64_t)(uintptr_t)(p->buriedobjlist);
case 5:return(uint64_t)(uintptr_t)(p->monlist);
case 6:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 8:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->beginner);
case 1:return(uint64_t)(uintptr_t)(p->female);
case 2:return(uint64_t)(uintptr_t)(p->quick_farsight);
case 3:return(uint64_t)(uintptr_t)(p->verbose);
case 4:return(uint64_t)(uintptr_t)(p->showrace);
default:abort();}}
case 9:{struct found_things*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->ft_cc);
case 1:return(uint64_t)(uintptr_t)(p->num_sdoors);
case 2:return(uint64_t)(uintptr_t)(p->num_scorrs);
case 3:return(uint64_t)(uintptr_t)(p->num_traps);
case 4:return(uint64_t)(uintptr_t)(p->num_mons);
case 5:return(uint64_t)(uintptr_t)(p->num_invis);
case 6:return(uint64_t)(uintptr_t)(p->num_cleared_invis);
case 7:return(uint64_t)(uintptr_t)(p->num_kept_invis);
default:abort();}}
case 10:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->terrainmode);
case 1:return(uint64_t)(uintptr_t)(p->autodescribe);
case 2:return(uint64_t)(uintptr_t)(p->save_uswallow);
case 3:return(uint64_t)(uintptr_t)(p->save_uinwater);
case 4:return(uint64_t)(uintptr_t)(p->save_uburied);
default:abort();}}
case 11:{struct instance_globals_a*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->already_found_flag);
default:abort();}}
case 12:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->doorindex);
default:abort();}}
case 13:{struct instance_globals_f*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 15:{struct instance_globals_k*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->known);
default:abort();}}
case 16:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->multi_reason);
default:abort();}}
case 17:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 18:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->showsyms);
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
case 1:return(uint64_t)(uintptr_t)(p->doors);
default:abort();}}
case 20:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->lastseentyp);
case 1:return(uint64_t)(uintptr_t)(&p->level);
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
case 24:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hero_memory);
case 1:return(uint64_t)(uintptr_t)(p->arboreal);
default:abort();}}
case 25:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mcorpsenm);
default:abort();}}
case 26:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nmon);
case 1:return(uint64_t)(uintptr_t)(p->data);
case 2:return(uint64_t)(uintptr_t)(p->mx);
case 3:return(uint64_t)(uintptr_t)(p->my);
case 4:return(uint64_t)(uintptr_t)(p->mhp);
case 5:return(uint64_t)(uintptr_t)(p->mappearance);
case 6:return(uint64_t)(uintptr_t)(p->m_ap_type);
case 7:return(uint64_t)(uintptr_t)(p->mtame);
case 8:return(uint64_t)(uintptr_t)(p->female);
case 9:return(uint64_t)(uintptr_t)(p->mundetected);
case 10:return(uint64_t)(uintptr_t)(p->msleeping);
case 11:return(uint64_t)(uintptr_t)(p->mfrozen);
case 12:return(uint64_t)(uintptr_t)(p->mcanmove);
case 13:return(uint64_t)(uintptr_t)(p->isgd);
case 14:return(uint64_t)(uintptr_t)(p->minvent);
case 15:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 27:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 28:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(&p->v);
case 2:return(uint64_t)(uintptr_t)(p->cobj);
case 3:return(uint64_t)(uintptr_t)(p->ox);
case 4:return(uint64_t)(uintptr_t)(p->oy);
case 5:return(uint64_t)(uintptr_t)(p->otyp);
case 6:return(uint64_t)(uintptr_t)(p->quan);
case 7:return(uint64_t)(uintptr_t)(p->spe);
case 8:return(uint64_t)(uintptr_t)(p->oclass);
case 9:return(uint64_t)(uintptr_t)(p->oartifact);
case 10:return(uint64_t)(uintptr_t)(p->cursed);
case 11:return(uint64_t)(uintptr_t)(p->blessed);
case 12:return(uint64_t)(uintptr_t)(p->tknown);
case 13:return(uint64_t)(uintptr_t)(p->olocked);
case 14:return(uint64_t)(uintptr_t)(p->otrapped);
case 15:return(uint64_t)(uintptr_t)(p->corpsenm);
default:abort();}}
case 29:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_merge);
case 1:return(uint64_t)(uintptr_t)(p->oc_material);
case 2:return(uint64_t)(uintptr_t)(p->oc_class);
default:abort();}}
case 30:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->pmidx);
case 1:return(uint64_t)(uintptr_t)(p->mlet);
case 2:return(uint64_t)(uintptr_t)(p->mflags1);
default:abort();}}
case 31:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 32:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
case 1:return(uint64_t)(uintptr_t)(p->typ);
case 2:return(uint64_t)(uintptr_t)(p->seenv);
case 3:return(uint64_t)(uintptr_t)(p->flags);
case 4:return(uint64_t)(uintptr_t)(p->horizontal);
case 5:return(uint64_t)(uintptr_t)(p->waslit);
case 6:return(uint64_t)(uintptr_t)(p->roomno);
case 7:return(uint64_t)(uintptr_t)(p->candig);
default:abort();}}
case 33:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ntrap);
case 1:return(uint64_t)(uintptr_t)(p->tx);
case 2:return(uint64_t)(uintptr_t)(p->ty);
case 3:return(uint64_t)(uintptr_t)(p->ttyp);
case 4:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 34:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 35:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 36:{volatile struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
default:abort();}}
case 37:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(&p->uz);
case 3:return(uint64_t)(uintptr_t)(&p->uprops);
case 4:return(uint64_t)(uintptr_t)(p->umonster);
case 5:return(uint64_t)(uintptr_t)(p->umonnum);
case 6:return(uint64_t)(uintptr_t)(p->uswallow);
case 7:return(uint64_t)(uintptr_t)(p->uinwater);
case 8:return(uint64_t)(uintptr_t)(p->mfemale);
case 9:return(uint64_t)(uintptr_t)(p->uburied);
case 10:return(uint64_t)(uintptr_t)(p->uedibility);
case 11:return(uint64_t)(uintptr_t)(&p->uroleplay);
case 12:return(uint64_t)(uintptr_t)(p->ustuck);
case 13:return(uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
default:abort();}}
void teleport_detect_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:p->glyph=(int)value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->mnum=(short)value;return;
default:abort();}}
case 2:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 3:{struct class_sym*p=at;switch(field){
case 0:p->sym=(char)value;return;
case 1:p->name=(const char *)value;return;
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
default:abort();}}
case 5:{struct d_level*p=at;switch(field){
case 0:p->dnum=(xint16)value;return;
case 1:p->dlevel=(xint16)value;return;
default:abort();}}
case 6:{struct dgn_topology*p=at;switch(field){
case 5:p->d_sokoban_dnum=(xint16)value;return;
default:abort();}}
case 7:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(struct obj *)value;return;
case 4:p->buriedobjlist=(struct obj *)value;return;
case 5:p->monlist=(struct monst *)value;return;
default:abort();}}
case 8:{struct flag*p=at;switch(field){
case 0:p->beginner=(boolean)value;return;
case 1:p->female=(boolean)value;return;
case 2:p->quick_farsight=(boolean)value;return;
case 3:p->verbose=(boolean)value;return;
case 4:p->showrace=(boolean)value;return;
default:abort();}}
case 9:{struct found_things*p=at;switch(field){
case 1:p->num_sdoors=(uchar)value;return;
case 2:p->num_scorrs=(uchar)value;return;
case 3:p->num_traps=(uchar)value;return;
case 4:p->num_mons=(uchar)value;return;
case 5:p->num_invis=(uchar)value;return;
case 6:p->num_cleared_invis=(uchar)value;return;
case 7:p->num_kept_invis=(uchar)value;return;
default:abort();}}
case 10:{struct instance_flags*p=at;switch(field){
case 0:p->terrainmode=(unsigned int)value;return;
case 1:p->autodescribe=(boolean)value;return;
case 2:p->save_uswallow=(unsigned int)value;return;
case 3:p->save_uinwater=(unsigned int)value;return;
case 4:p->save_uburied=(unsigned int)value;return;
default:abort();}}
case 11:{struct instance_globals_a*p=at;switch(field){
case 0:p->already_found_flag=(int)value;return;
default:abort();}}
case 12:{struct instance_globals_d*p=at;switch(field){
case 0:p->doorindex=(int)value;return;
default:abort();}}
case 13:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(struct trap *)value;return;
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(struct obj *)value;return;
default:abort();}}
case 15:{struct instance_globals_k*p=at;switch(field){
case 0:p->known=(boolean)value;return;
default:abort();}}
case 16:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi_reason=(const char *)value;return;
default:abort();}}
case 17:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(const char *)value;return;
default:abort();}}
case 18:{struct instance_globals_s*p=at;switch(field){
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
case 1:p->doors=(coord *)value;return;
default:abort();}}
case 20:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 21:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(seenV **)value;return;
default:abort();}}
case 23:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 24:{struct levelflags*p=at;switch(field){
case 0:p->hero_memory=(unsigned int)value;return;
case 1:p->arboreal=(unsigned int)value;return;
default:abort();}}
case 25:{struct mextra*p=at;switch(field){
case 0:p->mcorpsenm=(int)value;return;
default:abort();}}
case 26:{struct monst*p=at;switch(field){
case 0:p->nmon=(struct monst *)value;return;
case 1:p->data=(struct permonst *)value;return;
case 2:p->mx=(coordxy)value;return;
case 3:p->my=(coordxy)value;return;
case 4:p->mhp=(int)value;return;
case 5:p->mappearance=(unsigned int)value;return;
case 6:p->m_ap_type=(uchar)value;return;
case 7:p->mtame=(schar)value;return;
case 8:p->female=(unsigned int)value;return;
case 9:p->mundetected=(unsigned int)value;return;
case 10:p->msleeping=(unsigned int)value;return;
case 11:p->mfrozen=(unsigned int)value;return;
case 12:p->mcanmove=(unsigned int)value;return;
case 13:p->isgd=(unsigned int)value;return;
case 14:p->minvent=(struct obj *)value;return;
case 15:p->mextra=(struct mextra *)value;return;
default:abort();}}
case 27:{struct nhcoord*p=at;switch(field){
case 0:p->x=(coordxy)value;return;
case 1:p->y=(coordxy)value;return;
default:abort();}}
case 28:{struct obj*p=at;switch(field){
case 0:p->nobj=(struct obj *)value;return;
case 2:p->cobj=(struct obj *)value;return;
case 3:p->ox=(coordxy)value;return;
case 4:p->oy=(coordxy)value;return;
case 5:p->otyp=(short)value;return;
case 6:p->quan=(long)value;return;
case 7:p->spe=(schar)value;return;
case 8:p->oclass=(char)value;return;
case 9:p->oartifact=(char)value;return;
case 10:p->cursed=(unsigned int)value;return;
case 11:p->blessed=(unsigned int)value;return;
case 12:p->tknown=(unsigned int)value;return;
case 13:p->olocked=(unsigned int)value;return;
case 14:p->otrapped=(unsigned int)value;return;
case 15:p->corpsenm=(int)value;return;
default:abort();}}
case 29:{struct objclass*p=at;switch(field){
case 0:p->oc_merge=(unsigned int)value;return;
case 1:p->oc_material=(unsigned int)value;return;
case 2:p->oc_class=(char)value;return;
default:abort();}}
case 30:{struct permonst*p=at;switch(field){
case 1:p->mlet=(char)value;return;
case 2:p->mflags1=(unsigned long)value;return;
default:abort();}}
case 31:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(long)value;return;
case 1:p->blocked=(long)value;return;
case 2:p->intrinsic=(long)value;return;
default:abort();}}
case 32:{struct rm*p=at;switch(field){
case 0:p->glyph=(int)value;return;
case 1:p->typ=(schar)value;return;
case 2:p->seenv=(uchar)value;return;
case 3:p->flags=(unsigned int)value;return;
case 4:p->horizontal=(unsigned int)value;return;
case 5:p->waslit=(unsigned int)value;return;
case 6:p->roomno=(unsigned int)value;return;
case 7:p->candig=(unsigned int)value;return;
default:abort();}}
case 33:{struct trap*p=at;switch(field){
case 0:p->ntrap=(struct trap *)value;return;
case 1:p->tx=(coordxy)value;return;
case 2:p->ty=(coordxy)value;return;
case 3:p->ttyp=(unsigned int)value;return;
case 4:p->tseen=(unsigned int)value;return;
default:abort();}}
case 34:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=(boolean)value;return;
default:abort();}}
case 35:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(struct obj *)value;return;
default:abort();}}
case 36:{volatile struct window_procs*p=at;switch(field){
case 0:p->win_display_nhwindow=(void (*)(winid, boolean))value;return;
default:abort();}}
case 37:{struct you*p=at;switch(field){
case 0:p->ux=(coordxy)value;return;
case 1:p->uy=(coordxy)value;return;
case 4:p->umonster=(int)value;return;
case 5:p->umonnum=(int)value;return;
case 6:p->uswallow=(unsigned int)value;return;
case 7:p->uinwater=(unsigned int)value;return;
case 8:p->mfemale=(unsigned int)value;return;
case 9:p->uburied=(unsigned int)value;return;
case 10:p->uedibility=(unsigned int)value;return;
case 12:p->ustuck=(struct monst *)value;return;
case 13:p->usteed=(struct monst *)value;return;
default:abort();}}
default:abort();}}
void* teleport_detect_address(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(void*)&p->glyph;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_something;
case 1:return(void*)&p->c_Never_mind;
case 2:return(void*)&p->c_vision_clears;
default:abort();}}
case 3:{struct class_sym*p=at;switch(field){
case 0:return(void*)&p->sym;
case 1:return(void*)&p->name;
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroobj;
default:abort();}}
case 5:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 6:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_oracle_level;
case 1:return(void*)&p->d_rogue_level;
case 2:return(void*)&p->d_medusa_level;
case 3:return(void*)&p->d_stronghold_level;
case 4:return(void*)&p->d_wiz1_level;
case 5:return(void*)&p->d_sokoban_dnum;
case 6:return(void*)&p->d_knox_level;
default:abort();}}
case 7:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->objlist;
case 4:return(void*)&p->buriedobjlist;
case 5:return(void*)&p->monlist;
case 6:return(void*)&p->flags;
default:abort();}}
case 8:{struct flag*p=at;switch(field){
case 0:return(void*)&p->beginner;
case 1:return(void*)&p->female;
case 2:return(void*)&p->quick_farsight;
case 3:return(void*)&p->verbose;
case 4:return(void*)&p->showrace;
default:abort();}}
case 9:{struct found_things*p=at;switch(field){
case 0:return(void*)&p->ft_cc;
case 1:return(void*)&p->num_sdoors;
case 2:return(void*)&p->num_scorrs;
case 3:return(void*)&p->num_traps;
case 4:return(void*)&p->num_mons;
case 5:return(void*)&p->num_invis;
case 6:return(void*)&p->num_cleared_invis;
case 7:return(void*)&p->num_kept_invis;
default:abort();}}
case 10:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->terrainmode;
case 1:return(void*)&p->autodescribe;
default:abort();}}
case 11:{struct instance_globals_a*p=at;switch(field){
case 0:return(void*)&p->already_found_flag;
default:abort();}}
case 12:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->doorindex;
default:abort();}}
case 13:{struct instance_globals_f*p=at;switch(field){
case 0:return(void*)&p->ftrap;
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->invent;
default:abort();}}
case 15:{struct instance_globals_k*p=at;switch(field){
case 0:return(void*)&p->known;
default:abort();}}
case 16:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->multi_reason;
default:abort();}}
case 17:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nomovemsg;
default:abort();}}
case 18:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->showsyms;
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
case 1:return(void*)&p->doors;
default:abort();}}
case 20:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->lastseentyp;
case 1:return(void*)&p->level;
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
case 24:{struct levelflags*p=at;switch(field){
default:abort();}}
case 25:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->mcorpsenm;
default:abort();}}
case 26:{struct monst*p=at;switch(field){
case 0:return(void*)&p->nmon;
case 1:return(void*)&p->data;
case 2:return(void*)&p->mx;
case 3:return(void*)&p->my;
case 4:return(void*)&p->mhp;
case 5:return(void*)&p->mappearance;
case 6:return(void*)&p->m_ap_type;
case 7:return(void*)&p->mtame;
case 14:return(void*)&p->minvent;
case 15:return(void*)&p->mextra;
default:abort();}}
case 27:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 28:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->v;
case 2:return(void*)&p->cobj;
case 3:return(void*)&p->ox;
case 4:return(void*)&p->oy;
case 5:return(void*)&p->otyp;
case 6:return(void*)&p->quan;
case 7:return(void*)&p->spe;
case 8:return(void*)&p->oclass;
case 9:return(void*)&p->oartifact;
case 15:return(void*)&p->corpsenm;
default:abort();}}
case 29:{struct objclass*p=at;switch(field){
case 2:return(void*)&p->oc_class;
default:abort();}}
case 30:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->pmidx;
case 1:return(void*)&p->mlet;
case 2:return(void*)&p->mflags1;
default:abort();}}
case 31:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 32:{struct rm*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->typ;
case 2:return(void*)&p->seenv;
default:abort();}}
case 33:{struct trap*p=at;switch(field){
case 0:return(void*)&p->ntrap;
case 1:return(void*)&p->tx;
case 2:return(void*)&p->ty;
default:abort();}}
case 34:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->deaf;
default:abort();}}
case 35:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
default:abort();}}
case 36:{volatile struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_display_nhwindow;
default:abort();}}
case 37:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->uz;
case 3:return(void*)&p->uprops;
case 4:return(void*)&p->umonster;
case 5:return(void*)&p->umonnum;
case 11:return(void*)&p->uroleplay;
case 12:return(void*)&p->ustuck;
case 13:return(void*)&p->usteed;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
int teleport_detect_var0(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_detect_var1(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_detect_var2(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var3(char * a0){(You_feel)(a0);}
void teleport_detect_var4(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var5(char * a0,char * a1){(Your)(a0,a1);}
int teleport_detect_var6(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_detect_var7(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_detect_var8(char * a0,char * a1){(Your)(a0,a1);}
void teleport_detect_var9(char * a0,char * a1,char * a2,char * a3){(Your)(a0,a1,a2,a3);}
void teleport_detect_var10(char * a0,char * a1,char * a2){(Your)(a0,a1,a2);}
void teleport_detect_var11(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var12(char * a0,int a1){(impossible)(a0,a1);}
void teleport_detect_var13(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var14(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_detect_var15(char * a0){(You)(a0);}
void teleport_detect_var16(char * a0){(pline)(a0);}
void teleport_detect_var17(char * a0,char * a1){(You_feel)(a0,a1);}
int teleport_detect_var18(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_detect_var19(char * a0,char * a1){(Your)(a0,a1);}
void teleport_detect_var20(char * a0){(There)(a0);}
void teleport_detect_var21(char * a0){(Your)(a0);}
void teleport_detect_var22(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var23(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var24(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var25(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var26(char * a0,char * a1){(Your)(a0,a1);}
void teleport_detect_var27(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var28(char * a0){(You)(a0);}
void teleport_detect_var29(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var30(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var31(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var32(char * a0){(You)(a0);}
void teleport_detect_var33(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var34(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_detect_var35(char * a0){(You_see)(a0);}
void teleport_detect_var36(char * a0){(You_see)(a0);}
void teleport_detect_var37(char * a0){(pline)(a0);}
void teleport_detect_var38(char * a0){(You)(a0);}
void teleport_detect_var39(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var40(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var41(char * a0){(pline_The)(a0);}
void teleport_detect_var42(char * a0,char * a1,char * a2){(You_see)(a0,a1,a2);}
void teleport_detect_var43(char * a0){(You_see)(a0);}
void teleport_detect_var44(char * a0){(pline_The)(a0);}
void teleport_detect_var45(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var46(char * a0){(You)(a0);}
void teleport_detect_var47(char * a0,char * a1){(Norep)(a0,a1);}
int teleport_detect_var48(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_detect_var49(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_detect_var50(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_detect_var51(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_detect_var52(char * a0,char * a1){(You)(a0,a1);}
int teleport_detect_var53(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_detect_var54(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_detect_var55(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var56(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_detect_var57(char * a0){(You)(a0);}
void teleport_detect_var58(char * a0){(pline)(a0);}
void teleport_detect_var59(char * a0,char * a1){(pline)(a0,a1);}
void teleport_detect_var60(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var61(char * a0,char * a1){(Your)(a0,a1);}
void teleport_detect_var62(char * a0){(You_feel)(a0);}
void teleport_detect_var63(char * a0,char * a1){(You)(a0,a1);}
void teleport_detect_var64(char * a0){(Norep)(a0);}
void teleport_detect_var65(char * a0){(You)(a0);}
void teleport_detect_var66(char * a0){(You)(a0);}
void teleport_detect_var67(char * a0){(You)(a0);}
int teleport_detect_var68(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_detect_var69(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_detect_var70(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_detect_var71(char * a0,char * a1){(pline)(a0,a1);}
#pragma clang diagnostic pop
void*teleport_detect_copy(void*to,const void*from,size_t n){return memcpy(to,from,n);}
int teleport_detect_call_rng(int(*fn)(int),int n){return fn(n);}
void teleport_detect_call_window(void(*fn)(winid,boolean),winid id,boolean block){fn(id,block);}
extern boolean teleport_detect_unconstrain_map(void);
extern void teleport_detect_reconstrain_map(void);
extern void teleport_detect_map_redisplay(void);
extern void teleport_detect_browse_map(unsigned int ter_typ,const char * ter_explain);
extern void teleport_detect_map_monst(struct monst * mtmp,boolean showtail);
extern void teleport_detect_observe_recursively(struct obj * obj);
extern boolean teleport_detect_check_map_spot(coordxy x,coordxy y,char oclass,unsigned int material);
extern boolean teleport_detect_clear_stale_map(char oclass,unsigned int material);
extern void teleport_detect_sense_trap(struct trap * trap,coordxy x,coordxy y,int src_cursed);
extern int teleport_detect_detect_obj_traps(struct obj * objlist,boolean show_them,int how,struct found_things * ft);
extern void teleport_detect_display_trap_map(int cursed_src);
extern int teleport_detect_furniture_detect(void);
extern void teleport_detect_foundone(coordxy zx,coordxy zy,int glyph);
extern void teleport_detect_findone(coordxy zx,coordxy zy,genericptr_t whatfound);
extern void teleport_detect_openone(coordxy zx,coordxy zy,genericptr_t num);
extern int teleport_detect_mfind0(struct monst * mtmp,boolean via_warning);
extern boolean teleport_detect_skip_premap_detect(coordxy x,coordxy y);
extern int teleport_detect_reveal_terrain_getglyph(coordxy x,coordxy y,unsigned int swallowed,int default_glyph,unsigned int which_subset);
uintptr_t teleport_detect_function0(void){return(uintptr_t)rn2_on_display_rng;}
uintptr_t teleport_detect_function1(void){return(uintptr_t)rn2;}
uintptr_t teleport_detect_function2(void){return(uintptr_t)teleport_detect_findone;}
uintptr_t teleport_detect_function3(void){return(uintptr_t)teleport_detect_openone;}
#include "detect-source-data.h"
static char detect_literals[DETECT_LITERAL_CAPACITY];
char*teleport_detect_literal_storage(void){return detect_literals;}
size_t teleport_detect_literal_capacity(void){return sizeof detect_literals;}

/* Configured source/field/dependency ABI guards; no algorithms. */
_Static_assert(sizeof(size_t)==8 && (size_t)-1>0 && sizeof(long)==8 && (long)-1<0,"DETECT size_t/long64");
_Static_assert(sizeof(((NhRegion*)0)->glyph)==4 && (((__typeof__(((NhRegion*)0)->glyph))-1<0)==1),"DETECT NhRegion.glyph width/sign");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2 && (((__typeof__(((struct Race*)0)->mnum))-1<0)==1),"DETECT Race.mnum width/sign");
_Static_assert(sizeof(((struct class_sym*)0)->sym)==1 && (((__typeof__(((struct class_sym*)0)->sym))-1<0)==1),"DETECT class_sym.sym width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"DETECT d_level.dnum width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"DETECT d_level.dlevel width/sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)==2 && (((__typeof__(((struct dgn_topology*)0)->d_sokoban_dnum))-1<0)==1),"DETECT dgn_topology.d_sokoban_dnum width/sign");
_Static_assert(sizeof(((struct flag*)0)->beginner)==1 && (((__typeof__(((struct flag*)0)->beginner))-1<0)==1),"DETECT flag.beginner width/sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1 && (((__typeof__(((struct flag*)0)->female))-1<0)==1),"DETECT flag.female width/sign");
_Static_assert(sizeof(((struct flag*)0)->quick_farsight)==1 && (((__typeof__(((struct flag*)0)->quick_farsight))-1<0)==1),"DETECT flag.quick_farsight width/sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1 && (((__typeof__(((struct flag*)0)->verbose))-1<0)==1),"DETECT flag.verbose width/sign");
_Static_assert(sizeof(((struct flag*)0)->showrace)==1 && (((__typeof__(((struct flag*)0)->showrace))-1<0)==1),"DETECT flag.showrace width/sign");
_Static_assert(sizeof(((struct found_things*)0)->num_sdoors)==1 && (((__typeof__(((struct found_things*)0)->num_sdoors))-1<0)==0),"DETECT found_things.num_sdoors width/sign");
_Static_assert(sizeof(((struct found_things*)0)->num_scorrs)==1 && (((__typeof__(((struct found_things*)0)->num_scorrs))-1<0)==0),"DETECT found_things.num_scorrs width/sign");
_Static_assert(sizeof(((struct found_things*)0)->num_traps)==1 && (((__typeof__(((struct found_things*)0)->num_traps))-1<0)==0),"DETECT found_things.num_traps width/sign");
_Static_assert(sizeof(((struct found_things*)0)->num_mons)==1 && (((__typeof__(((struct found_things*)0)->num_mons))-1<0)==0),"DETECT found_things.num_mons width/sign");
_Static_assert(sizeof(((struct found_things*)0)->num_invis)==1 && (((__typeof__(((struct found_things*)0)->num_invis))-1<0)==0),"DETECT found_things.num_invis width/sign");
_Static_assert(sizeof(((struct found_things*)0)->num_cleared_invis)==1 && (((__typeof__(((struct found_things*)0)->num_cleared_invis))-1<0)==0),"DETECT found_things.num_cleared_invis width/sign");
_Static_assert(sizeof(((struct found_things*)0)->num_kept_invis)==1 && (((__typeof__(((struct found_things*)0)->num_kept_invis))-1<0)==0),"DETECT found_things.num_kept_invis width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->terrainmode)==4 && (((__typeof__(((struct instance_flags*)0)->terrainmode))-1<0)==0),"DETECT instance_flags.terrainmode width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->autodescribe)==1 && (((__typeof__(((struct instance_flags*)0)->autodescribe))-1<0)==1),"DETECT instance_flags.autodescribe width/sign");
_Static_assert(sizeof(((struct instance_globals_a*)0)->already_found_flag)==4 && (((__typeof__(((struct instance_globals_a*)0)->already_found_flag))-1<0)==1),"DETECT instance_globals_a.already_found_flag width/sign");
_Static_assert(sizeof(((struct instance_globals_d*)0)->doorindex)==4 && (((__typeof__(((struct instance_globals_d*)0)->doorindex))-1<0)==1),"DETECT instance_globals_d.doorindex width/sign");
_Static_assert(sizeof(((struct instance_globals_k*)0)->known)==1 && (((__typeof__(((struct instance_globals_k*)0)->known))-1<0)==1),"DETECT instance_globals_k.known width/sign");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4 && (((__typeof__(((struct mextra*)0)->mcorpsenm))-1<0)==1),"DETECT mextra.mcorpsenm width/sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"DETECT monst.mx width/sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"DETECT monst.my width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"DETECT monst.mhp width/sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4 && (((__typeof__(((struct monst*)0)->mappearance))-1<0)==0),"DETECT monst.mappearance width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"DETECT monst.m_ap_type width/sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"DETECT monst.mtame width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2 && (((__typeof__(((struct nhcoord*)0)->x))-1<0)==1),"DETECT nhcoord.x width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2 && (((__typeof__(((struct nhcoord*)0)->y))-1<0)==1),"DETECT nhcoord.y width/sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2 && (((__typeof__(((struct obj*)0)->ox))-1<0)==1),"DETECT obj.ox width/sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2 && (((__typeof__(((struct obj*)0)->oy))-1<0)==1),"DETECT obj.oy width/sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"DETECT obj.otyp width/sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"DETECT obj.quan width/sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1 && (((__typeof__(((struct obj*)0)->spe))-1<0)==1),"DETECT obj.spe width/sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1 && (((__typeof__(((struct obj*)0)->oclass))-1<0)==1),"DETECT obj.oclass width/sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1 && (((__typeof__(((struct obj*)0)->oartifact))-1<0)==1),"DETECT obj.oartifact width/sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4 && (((__typeof__(((struct obj*)0)->corpsenm))-1<0)==1),"DETECT obj.corpsenm width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_class)==1 && (((__typeof__(((struct objclass*)0)->oc_class))-1<0)==1),"DETECT objclass.oc_class width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"DETECT permonst.mlet width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"DETECT permonst.mflags1 width/sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"DETECT prop.extrinsic width/sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"DETECT prop.blocked width/sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"DETECT prop.intrinsic width/sign");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4 && (((__typeof__(((struct rm*)0)->glyph))-1<0)==1),"DETECT rm.glyph width/sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"DETECT rm.typ width/sign");
_Static_assert(sizeof(((struct rm*)0)->seenv)==1 && (((__typeof__(((struct rm*)0)->seenv))-1<0)==0),"DETECT rm.seenv width/sign");
_Static_assert(sizeof(((struct trap*)0)->tx)==2 && (((__typeof__(((struct trap*)0)->tx))-1<0)==1),"DETECT trap.tx width/sign");
_Static_assert(sizeof(((struct trap*)0)->ty)==2 && (((__typeof__(((struct trap*)0)->ty))-1<0)==1),"DETECT trap.ty width/sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1 && (((__typeof__(((struct u_roleplay*)0)->deaf))-1<0)==1),"DETECT u_roleplay.deaf width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"DETECT you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"DETECT you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"DETECT you.umonster width/sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"DETECT you.umonnum width/sign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&docrt),void (*)(void)),"DETECT dependency docrt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&under_water),void (*)(int)),"DETECT dependency under_water");
_Static_assert(__builtin_types_compatible_p(__typeof__(&under_ground),void (*)(int)),"DETECT dependency under_ground");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getpos),int (*)(coord *, boolean, const char *)),"DETECT dependency getpos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2_on_display_rng),int (*)(int)),"DETECT dependency rn2_on_display_rng");
_Static_assert(__builtin_types_compatible_p(__typeof__(&show_glyph),void (*)(coordxy, coordxy, int)),"DETECT dependency show_glyph");
_Static_assert(__builtin_types_compatible_p(__typeof__(&detect_wsegs),void (*)(struct monst *, boolean)),"DETECT dependency detect_wsegs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_at),int (*)(coordxy, coordxy)),"DETECT dependency glyph_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"DETECT dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *, int, const char *)),"DETECT dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"DETECT dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sobj_at),struct obj *(*)(int, coordxy, coordxy)),"DETECT dependency sobj_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&observe_object),void (*)(struct obj *)),"DETECT dependency observe_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unmap_object),void (*)(coordxy, coordxy)),"DETECT dependency unmap_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&findgold),struct obj *(*)(struct obj *)),"DETECT dependency findgold");
_Static_assert(__builtin_types_compatible_p(__typeof__(&currency),const char *(*)(long)),"DETECT dependency currency");
_Static_assert(__builtin_types_compatible_p(__typeof__(&money_cnt),long (*)(struct obj *)),"DETECT dependency money_cnt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hidden_gold),long (*)(boolean)),"DETECT dependency hidden_gold");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char *(*)(char *, const char *)),"DETECT dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&x_monnam),char *(*)(struct monst *, int, const char *, int, boolean)),"DETECT dependency x_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&s_suffix),char *(*)(const char *)),"DETECT dependency s_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strange_feeling),void (*)(struct obj *, const char *)),"DETECT dependency strange_feeling");
_Static_assert(__builtin_types_compatible_p(__typeof__(&body_part),const char *(*)(int)),"DETECT dependency body_part");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makeplural),char *(*)(const char *)),"DETECT dependency makeplural");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cls),void (*)(void)),"DETECT dependency cls");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_object),void (*)(struct obj *, int)),"DETECT dependency map_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd),int (*)(int)),"DETECT dependency rnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy, coordxy)),"DETECT dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exercise),void (*)(int, boolean)),"DETECT dependency exercise");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcat),char *(*)(char *, const char *)),"DETECT dependency strcat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_visible),int (*)(struct monst *)),"DETECT dependency mon_visible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_mines),boolean (*)(d_level *)),"DETECT dependency In_mines");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_hell),boolean (*)(d_level *)),"DETECT dependency In_hell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),boolean (*)(d_level *, d_level *)),"DETECT dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_trap),void (*)(struct trap *, int)),"DETECT dependency map_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_obj_location),boolean (*)(struct obj *, coordxy *, coordxy *, int)),"DETECT dependency get_obj_location");
_Static_assert(__builtin_types_compatible_p(__typeof__(&isok),int (*)(coordxy, coordxy)),"DETECT dependency isok");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flash_glyph_at),void (*)(coordxy, coordxy, int, int)),"DETECT dependency flash_glyph_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_to_cmap),int (*)(int)),"DETECT dependency glyph_to_cmap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&magic_map_background),void (*)(coordxy, coordxy, int)),"DETECT dependency magic_map_background");
_Static_assert(__builtin_types_compatible_p(__typeof__(&seemimic),void (*)(struct monst *)),"DETECT dependency seemimic");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"DETECT dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"DETECT dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_invisible),void (*)(coordxy, coordxy)),"DETECT dependency map_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&depth),schar (*)(d_level *)),"DETECT dependency depth");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xname),char *(*)(struct obj *)),"DETECT dependency xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&the),char *(*)(const char *)),"DETECT dependency the");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_quest_artifact),boolean (*)(struct obj *)),"DETECT dependency is_quest_artifact");
_Static_assert(__builtin_types_compatible_p(__typeof__(&acurr),schar (*)(int)),"DETECT dependency acurr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Tobjnam),char *(*)(struct obj *, const char *)),"DETECT dependency Tobjnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_confused),void (*)(long, boolean)),"DETECT dependency make_confused");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resists_blnd),boolean (*)(struct monst *)),"DETECT dependency resists_blnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_blinded),void (*)(long, boolean)),"DETECT dependency make_blinded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_hallucinated),boolean (*)(long, boolean, long)),"DETECT dependency make_hallucinated");
_Static_assert(__builtin_types_compatible_p(__typeof__(&useup),void (*)(struct obj *)),"DETECT dependency useup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losehp),void (*)(int, const char *, schar)),"DETECT dependency losehp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&consume_obj_charge),void (*)(struct obj *, boolean)),"DETECT dependency consume_obj_charge");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nomul),void (*)(int)),"DETECT dependency nomul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hcolor),const char *(*)(const char *)),"DETECT dependency hcolor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&poly_gender),int (*)(void)),"DETECT dependency poly_gender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yn_function),char (*)(const char *, const char *, char, boolean)),"DETECT dependency yn_function");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strchr),char *(*)(const char *, int)),"DETECT dependency strchr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&discover_object),void (*)(int, boolean, boolean, boolean)),"DETECT dependency discover_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&def_char_is_furniture),int (*)(char)),"DETECT dependency def_char_is_furniture");
_Static_assert(__builtin_types_compatible_p(__typeof__(&def_char_to_objclass),int (*)(char)),"DETECT dependency def_char_to_objclass");
_Static_assert(__builtin_types_compatible_p(__typeof__(&def_char_to_monclass),int (*)(char)),"DETECT dependency def_char_to_monclass");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unblock_point),void (*)(int, int)),"DETECT dependency unblock_point");
_Static_assert(__builtin_types_compatible_p(__typeof__(&t_at),struct trap *(*)(coordxy, coordxy)),"DETECT dependency t_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&engr_at),struct engr *(*)(coordxy, coordxy)),"DETECT dependency engr_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_engraving),void (*)(struct engr *, int)),"DETECT dependency map_engraving");
_Static_assert(__builtin_types_compatible_p(__typeof__(&room_discovered),void (*)(int)),"DETECT dependency room_discovered");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flush_screen),void (*)(int)),"DETECT dependency flush_screen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool),boolean (*)(coordxy, coordxy)),"DETECT dependency is_pool");
_Static_assert(__builtin_types_compatible_p(__typeof__(&see_monsters),void (*)(void)),"DETECT dependency see_monsters");
_Static_assert(__builtin_types_compatible_p(__typeof__(&recalc_block_point),void (*)(coordxy, coordxy)),"DETECT dependency recalc_block_point");
_Static_assert(__builtin_types_compatible_p(__typeof__(&back_to_glyph),int (*)(coordxy, coordxy)),"DETECT dependency back_to_glyph");
_Static_assert(__builtin_types_compatible_p(__typeof__(&closed_door),boolean (*)(coordxy, coordxy)),"DETECT dependency closed_door");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unmap_invisible),boolean (*)(coordxy, coordxy)),"DETECT dependency unmap_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy, coordxy, coordxy, coordxy)),"DETECT dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&b_trapped),void (*)(const char *, int)),"DETECT dependency b_trapped");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wake_nearto),void (*)(coordxy, coordxy, int)),"DETECT dependency wake_nearto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&openholdingtrap),boolean (*)(struct monst *, boolean *)),"DETECT dependency openholdingtrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&openfallingtrap),boolean (*)(struct monst *, boolean, boolean *)),"DETECT dependency openfallingtrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_drawbridge),boolean (*)(coordxy *, coordxy *)),"DETECT dependency find_drawbridge");
_Static_assert(__builtin_types_compatible_p(__typeof__(&open_drawbridge),void (*)(coordxy, coordxy)),"DETECT dependency open_drawbridge");
_Static_assert(__builtin_types_compatible_p(__typeof__(&memset),void *(*)(void *, int, unsigned long)),"DETECT dependency memset");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_clear_area),void (*)(coordxy, coordxy, int, void (*)(coordxy, coordxy, void *), genericptr_t)),"DETECT dependency do_clear_area");
_Static_assert(__builtin_types_compatible_p(__typeof__(&eos),char *(*)(char *)),"DETECT dependency eos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype_fromattack),struct attack *(*)(struct permonst *, int, int)),"DETECT dependency dmgtype_fromattack");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Monnam),char *(*)(struct monst *)),"DETECT dependency Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&expels),void (*)(struct monst *, struct permonst *, boolean)),"DETECT dependency expels");
_Static_assert(__builtin_types_compatible_p(__typeof__(&feel_newsym),void (*)(coordxy, coordxy)),"DETECT dependency feel_newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_msg_xy),void (*)(coordxy, coordxy)),"DETECT dependency set_msg_xy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trapname),const char *(*)(int, boolean)),"DETECT dependency trapname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&an),char *(*)(const char *)),"DETECT dependency an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&warning_of),int (*)(struct monst *)),"DETECT dependency warning_of");
_Static_assert(__builtin_types_compatible_p(__typeof__(&y_monnam),char *(*)(struct monst *)),"DETECT dependency y_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&a_monnam),char *(*)(struct monst *)),"DETECT dependency a_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spec_ability),boolean (*)(struct obj *, unsigned long)),"DETECT dependency spec_ability");
_Static_assert(__builtin_types_compatible_p(__typeof__(&visible_region_at),NhRegion *(*)(coordxy, coordxy)),"DETECT dependency visible_region_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&feel_location),void (*)(coordxy, coordxy)),"DETECT dependency feel_location");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnl),int (*)(int)),"DETECT dependency rnl");
_Static_assert(__builtin_types_compatible_p(__typeof__(&activate_statue_trap),struct monst *(*)(struct trap *, coordxy, coordxy, boolean)),"DETECT dependency activate_statue_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cmd_safety_prevention),boolean (*)(const char *, const char *, const char *, int *)),"DETECT dependency cmd_safety_prevention");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_background),void (*)(coordxy, coordxy, int)),"DETECT dependency map_background");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xy_set_wall_state),void (*)(coordxy, coordxy)),"DETECT dependency xy_set_wall_state");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_unconstrain_map),boolean (*)(void)),"DETECT source prototype unconstrain_map");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_reconstrain_map),void (*)(void)),"DETECT source prototype reconstrain_map");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_map_redisplay),void (*)(void)),"DETECT source prototype map_redisplay");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_browse_map),void (*)(unsigned int, const char *)),"DETECT source prototype browse_map");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_map_monst),void (*)(struct monst *, boolean)),"DETECT source prototype map_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trapped_chest_at),boolean (*)(int, coordxy, coordxy)),"DETECT source prototype trapped_chest_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trapped_door_at),boolean (*)(int, coordxy, coordxy)),"DETECT source prototype trapped_door_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&o_in),struct obj *(*)(struct obj *, char)),"DETECT source prototype o_in");
_Static_assert(__builtin_types_compatible_p(__typeof__(&o_material),struct obj *(*)(struct obj *, unsigned int)),"DETECT source prototype o_material");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_observe_recursively),void (*)(struct obj *)),"DETECT source prototype observe_recursively");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_check_map_spot),boolean (*)(coordxy, coordxy, char, unsigned int)),"DETECT source prototype check_map_spot");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_clear_stale_map),boolean (*)(char, unsigned int)),"DETECT source prototype clear_stale_map");
_Static_assert(__builtin_types_compatible_p(__typeof__(&gold_detect),int (*)(struct obj *)),"DETECT source prototype gold_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&food_detect),int (*)(struct obj *)),"DETECT source prototype food_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&object_detect),int (*)(struct obj *, int)),"DETECT source prototype object_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monster_detect),int (*)(struct obj *, int)),"DETECT source prototype monster_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_sense_trap),void (*)(struct trap *, coordxy, coordxy, int)),"DETECT source prototype sense_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_detect_obj_traps),int (*)(struct obj *, boolean, int, struct found_things *)),"DETECT source prototype detect_obj_traps");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_display_trap_map),void (*)(int)),"DETECT source prototype display_trap_map");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trap_detect),int (*)(struct obj *)),"DETECT source prototype trap_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_furniture_detect),int (*)(void)),"DETECT source prototype furniture_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&level_distance),const char *(*)(d_level *)),"DETECT source prototype level_distance");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_crystal_ball),void (*)(struct obj **)),"DETECT source prototype use_crystal_ball");
_Static_assert(__builtin_types_compatible_p(__typeof__(&show_map_spot),void (*)(coordxy, coordxy, boolean)),"DETECT source prototype show_map_spot");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_mapping),void (*)(void)),"DETECT source prototype do_mapping");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_vicinity_map),void (*)(struct obj *)),"DETECT source prototype do_vicinity_map");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cvt_sdoor_to_door),void (*)(struct rm *)),"DETECT source prototype cvt_sdoor_to_door");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_foundone),void (*)(coordxy, coordxy, int)),"DETECT source prototype foundone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_findone),void (*)(coordxy, coordxy, genericptr_t)),"DETECT source prototype findone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_openone),void (*)(coordxy, coordxy, genericptr_t)),"DETECT source prototype openone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&findit),int (*)(void)),"DETECT source prototype findit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&openit),int (*)(void)),"DETECT source prototype openit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&detecting),boolean (*)(void (*)(coordxy, coordxy, void *))),"DETECT source prototype detecting");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_trap),void (*)(struct trap *)),"DETECT source prototype find_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_mfind0),int (*)(struct monst *, boolean)),"DETECT source prototype mfind0");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dosearch0),int (*)(int)),"DETECT source prototype dosearch0");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dosearch),int (*)(void)),"DETECT source prototype dosearch");
_Static_assert(__builtin_types_compatible_p(__typeof__(&warnreveal),void (*)(void)),"DETECT source prototype warnreveal");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_skip_premap_detect),boolean (*)(coordxy, coordxy)),"DETECT source prototype skip_premap_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&premap_detect),void (*)(void)),"DETECT source prototype premap_detect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&teleport_detect_reveal_terrain_getglyph),int (*)(coordxy, coordxy, unsigned int, int, unsigned int)),"DETECT source prototype reveal_terrain_getglyph");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reveal_terrain),void (*)(unsigned int)),"DETECT source prototype reveal_terrain");
