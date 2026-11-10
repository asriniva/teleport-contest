/* DO typed fields, aliases, callbacks and native dependency transport only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static char teleport_do_wear_offdelaybuf[60];
void*teleport_do_wear_buffer(void){return teleport_do_wear_offdelaybuf;}
void *teleport_do_wear_global(int index){switch(index){
case 0:return (void*)&objects;
case 1:return (void*)&flags;
case 2:return (void*)&iflags;
case 3:return (void*)&mons;
case 4:return (void*)&condtests;
case 5:return (void*)&c_color_names;
case 6:return (void*)&c_common_strings;
case 7:return (void*)&rightleftchars;
case 8:return (void*)&uarm;
case 9:return (void*)&uarmc;
case 10:return (void*)&uarmh;
case 11:return (void*)&uarms;
case 12:return (void*)&uarmg;
case 13:return (void*)&uarmf;
case 14:return (void*)&uarmu;
case 15:return (void*)&uskin;
case 16:return (void*)&uamul;
case 17:return (void*)&uleft;
case 18:return (void*)&uright;
case 19:return (void*)&ublindf;
case 20:return (void*)&uwep;
case 21:return (void*)&uswapwep;
case 22:return (void*)&uquiver;
case 23:return (void*)&uball;
case 24:return (void*)&u;
case 25:return (void*)&disp;
case 26:return (void*)&ga;
case 27:return (void*)&gi;
case 28:return (void*)&gm;
case 29:return (void*)&gn;
case 30:return (void*)&gu;
case 31:return (void*)&gw;
case 32:return (void*)&gy;
case 33:return (void*)&svc;
case 34:return (void*)&svd;
case 35:return (void*)&program_state;
case 36:return (void*)&cg;
default:abort();}}
uint64_t teleport_do_wear_read(int kind,void*at,int field){switch(kind){
case 0:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(&p->uz);
case 3:return (uint64_t)(uintptr_t)(p->utrap);
case 4:return (uint64_t)(uintptr_t)(p->utraptype);
case 5:return (uint64_t)(uintptr_t)(&p->uprops);
case 6:return (uint64_t)(uintptr_t)(p->umonster);
case 7:return (uint64_t)(uintptr_t)(p->umonnum);
case 8:return (uint64_t)(uintptr_t)(p->uswallow);
case 9:return (uint64_t)(uintptr_t)(p->uinwater);
case 10:return (uint64_t)(uintptr_t)(p->uhandedness);
case 11:return (uint64_t)(uintptr_t)(&p->uroleplay);
case 12:return (uint64_t)(uintptr_t)(&p->acurr);
case 13:return (uint64_t)(uintptr_t)(&p->abon);
case 14:return (uint64_t)(uintptr_t)(&p->atemp);
case 15:return (uint64_t)(uintptr_t)(&p->ualign);
case 16:return (uint64_t)(uintptr_t)(&p->ualignbase);
case 17:return (uint64_t)(uintptr_t)(p->uhitinc);
case 18:return (uint64_t)(uintptr_t)(p->udaminc);
case 19:return (uint64_t)(uintptr_t)(p->uac);
case 20:return (uint64_t)(uintptr_t)(p->uspellprot);
case 21:return (uint64_t)(uintptr_t)(p->ublessed);
case 22:return (uint64_t)(uintptr_t)(p->usteed);
case 23:return (uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
case 1:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 2:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->blocked);
case 2:return (uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 3:{struct u_roleplay*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->blind);
default:abort();}}
case 4:{struct attribs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->a);
default:abort();}}
case 5:{struct align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 6:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
default:abort();}}
case 7:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mlet);
case 1:return (uint64_t)(uintptr_t)(p->ac);
case 2:return (uint64_t)(uintptr_t)(p->msize);
case 3:return (uint64_t)(uintptr_t)(p->mflags1);
default:abort();}}
case 8:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 9:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
case 1:return (uint64_t)(uintptr_t)(p->initial_don);
case 2:return (uint64_t)(uintptr_t)(p->item_action_in_progress);
default:abort();}}
case 10:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nobj);
case 1:return (uint64_t)(uintptr_t)(p->o_id);
case 2:return (uint64_t)(uintptr_t)(p->otyp);
case 3:return (uint64_t)(uintptr_t)(p->quan);
case 4:return (uint64_t)(uintptr_t)(p->spe);
case 5:return (uint64_t)(uintptr_t)(p->oclass);
case 6:return (uint64_t)(uintptr_t)(p->cursed);
case 7:return (uint64_t)(uintptr_t)(p->unpaid);
case 8:return (uint64_t)(uintptr_t)(p->lamplit);
case 9:return (uint64_t)(uintptr_t)(p->known);
case 10:return (uint64_t)(uintptr_t)(p->dknown);
case 11:return (uint64_t)(uintptr_t)(p->bknown);
case 12:return (uint64_t)(uintptr_t)(p->oeroded);
case 13:return (uint64_t)(uintptr_t)(p->oeroded2);
case 14:return (uint64_t)(uintptr_t)(p->oerodeproof);
case 15:return (uint64_t)(uintptr_t)(p->in_use);
case 16:return (uint64_t)(uintptr_t)(p->corpsenm);
case 17:return (uint64_t)(uintptr_t)(p->owornmask);
default:abort();}}
case 11:{struct instance_globals_w*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wasinwater);
default:abort();}}
case 12:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_name_known);
case 1:return (uint64_t)(uintptr_t)(p->oc_charged);
case 2:return (uint64_t)(uintptr_t)(p->oc_big);
case 3:return (uint64_t)(uintptr_t)(p->oc_material);
case 4:return (uint64_t)(uintptr_t)(p->oc_subtyp);
case 5:return (uint64_t)(uintptr_t)(p->oc_oprop);
case 6:return (uint64_t)(uintptr_t)(p->oc_delay);
case 7:return (uint64_t)(uintptr_t)(p->oc_oc1);
default:abort();}}
case 13:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mon_moving);
case 1:return (uint64_t)(uintptr_t)(&p->takeoff);
default:abort();}}
case 14:{struct takeoff_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mask);
case 1:return (uint64_t)(uintptr_t)(p->what);
case 2:return (uint64_t)(uintptr_t)(p->delay);
case 3:return (uint64_t)(uintptr_t)(p->cancelled_don);
case 4:return (uint64_t)(uintptr_t)(&p->disrobing);
default:abort();}}
case 15:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_something);
default:abort();}}
case 16:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->multi);
case 1:return (uint64_t)(uintptr_t)(p->multi_reason);
default:abort();}}
case 17:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_water_level);
case 1:return (uint64_t)(uintptr_t)(&p->d_air_level);
case 2:return (uint64_t)(uintptr_t)(&p->d_qstart_level);
default:abort();}}
case 18:{union any*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->a_obj);
case 1:return (uint64_t)(uintptr_t)(p->a_int);
default:abort();}}
case 19:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->in_lava_effects);
default:abort();}}
case 20:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 21:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 22:{struct const_globals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->zeroobj);
default:abort();}}
case 23:{struct c_color_names*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_black);
default:abort();}}
case 24:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->female);
case 1:return (uint64_t)(uintptr_t)(p->verbose);
case 2:return (uint64_t)(uintptr_t)(p->paranoia_bits);
case 3:return (uint64_t)(uintptr_t)(p->menu_style);
default:abort();}}
case 25:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 26:{struct mi*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 27:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 28:{struct _cmd_queue*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->typ);
case 1:return (uint64_t)(uintptr_t)(p->key);
default:abort();}}
case 29:{struct condtests_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->enabled);
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 31:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 32:{struct instance_globals_a*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->afternmv);
default:abort();}}
case 33:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->restoring);
default:abort();}}
case 34:{struct rm*p=at;switch(field){
default:abort();}}
default:abort();}}
void teleport_do_wear_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:memmove(&p->uz, (void*)(uintptr_t)value,sizeof p->uz);return;
case 3:p->utrap=value;return;
case 4:p->utraptype=value;return;
case 6:p->umonster=value;return;
case 7:p->umonnum=value;return;
case 8:p->uswallow=value;return;
case 9:p->uinwater=value;return;
case 10:p->uhandedness=value;return;
case 11:memmove(&p->uroleplay, (void*)(uintptr_t)value,sizeof p->uroleplay);return;
case 12:memmove(&p->acurr, (void*)(uintptr_t)value,sizeof p->acurr);return;
case 13:memmove(&p->abon, (void*)(uintptr_t)value,sizeof p->abon);return;
case 14:memmove(&p->atemp, (void*)(uintptr_t)value,sizeof p->atemp);return;
case 15:memmove(&p->ualign, (void*)(uintptr_t)value,sizeof p->ualign);return;
case 17:p->uhitinc=value;return;
case 18:p->udaminc=value;return;
case 19:p->uac=value;return;
case 20:p->uspellprot=value;return;
case 21:p->ublessed=value;return;
case 22:p->usteed=(void*)(uintptr_t)value;return;
case 23:p->twoweap=value;return;
default:abort();}}
case 1:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 2:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->blocked=value;return;
case 2:p->intrinsic=value;return;
default:abort();}}
case 3:{struct u_roleplay*p=at;switch(field){
case 0:p->blind=value;return;
default:abort();}}
case 4:{struct attribs*p=at;switch(field){
default:abort();}}
case 5:{struct align*p=at;switch(field){
case 0:p->type=value;return;
default:abort();}}
case 6:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
default:abort();}}
case 7:{struct permonst*p=at;switch(field){
case 0:p->mlet=value;return;
case 1:p->ac=value;return;
case 2:p->msize=value;return;
case 3:p->mflags1=value;return;
default:abort();}}
case 8:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(void*)(uintptr_t)value;return;
default:abort();}}
case 9:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
case 1:p->initial_don=value;return;
case 2:p->item_action_in_progress=value;return;
default:abort();}}
case 10:{struct obj*p=at;switch(field){
case 0:p->nobj=(void*)(uintptr_t)value;return;
case 1:p->o_id=value;return;
case 2:p->otyp=value;return;
case 3:p->quan=value;return;
case 4:p->spe=value;return;
case 5:p->oclass=value;return;
case 6:p->cursed=value;return;
case 7:p->unpaid=value;return;
case 8:p->lamplit=value;return;
case 9:p->known=value;return;
case 10:p->dknown=value;return;
case 11:p->bknown=value;return;
case 12:p->oeroded=value;return;
case 13:p->oeroded2=value;return;
case 14:p->oerodeproof=value;return;
case 15:p->in_use=value;return;
case 16:p->corpsenm=value;return;
case 17:p->owornmask=value;return;
default:abort();}}
case 11:{struct instance_globals_w*p=at;switch(field){
case 0:p->wasinwater=value;return;
default:abort();}}
case 12:{struct objclass*p=at;switch(field){
case 0:p->oc_name_known=value;return;
case 1:p->oc_charged=value;return;
case 2:p->oc_big=value;return;
case 3:p->oc_material=value;return;
case 4:p->oc_subtyp=value;return;
case 5:p->oc_oprop=value;return;
case 6:p->oc_delay=value;return;
case 7:p->oc_oc1=value;return;
default:abort();}}
case 13:{struct context_info*p=at;switch(field){
case 0:p->mon_moving=value;return;
case 1:memmove(&p->takeoff, (void*)(uintptr_t)value,sizeof p->takeoff);return;
default:abort();}}
case 14:{struct takeoff_info*p=at;switch(field){
case 0:p->mask=value;return;
case 1:p->what=value;return;
case 2:p->delay=value;return;
case 3:p->cancelled_don=value;return;
default:abort();}}
case 15:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 16:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=value;return;
case 1:p->multi_reason=(void*)(uintptr_t)value;return;
default:abort();}}
case 17:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_water_level, (void*)(uintptr_t)value,sizeof p->d_water_level);return;
case 1:memmove(&p->d_air_level, (void*)(uintptr_t)value,sizeof p->d_air_level);return;
case 2:memmove(&p->d_qstart_level, (void*)(uintptr_t)value,sizeof p->d_qstart_level);return;
default:abort();}}
case 18:{union any*p=at;switch(field){
case 0:p->a_obj=(void*)(uintptr_t)value;return;
case 1:p->a_int=value;return;
default:abort();}}
case 19:{struct instance_flags*p=at;switch(field){
case 0:p->in_lava_effects=value;return;
default:abort();}}
case 20:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology, (void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 21:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst, (void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 22:{struct const_globals*p=at;switch(field){
default:abort();}}
case 23:{struct c_color_names*p=at;switch(field){
default:abort();}}
case 24:{struct flag*p=at;switch(field){
case 0:p->female=value;return;
case 1:p->verbose=value;return;
case 2:p->paranoia_bits=value;return;
case 3:p->menu_style=value;return;
default:abort();}}
case 25:{struct Role*p=at;switch(field){
case 0:p->mnum=value;return;
default:abort();}}
case 26:{struct mi*p=at;switch(field){
case 0:memmove(&p->item, (void*)(uintptr_t)value,sizeof p->item);return;
default:abort();}}
case 27:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context, (void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 28:{struct _cmd_queue*p=at;switch(field){
case 0:p->typ=value;return;
case 1:p->key=value;return;
default:abort();}}
case 29:{struct condtests_t*p=at;switch(field){
case 0:p->enabled=value;return;
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole, (void*)(uintptr_t)value,sizeof p->urole);return;
default:abort();}}
case 31:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
default:abort();}}
case 32:{struct instance_globals_a*p=at;switch(field){
case 0:p->afternmv=(__typeof__(p->afternmv))(uintptr_t)value;return;
default:abort();}}
case 33:{struct sinfo*p=at;switch(field){
case 0:p->restoring=value;return;
default:abort();}}
case 34:{struct rm*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_do_wear_address(int kind,void*at,int field){switch(kind){
case 0:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->uz;
case 3:return (void*)&p->utrap;
case 4:return (void*)&p->utraptype;
case 5:return (void*)&p->uprops;
case 6:return (void*)&p->umonster;
case 7:return (void*)&p->umonnum;
case 11:return (void*)&p->uroleplay;
case 12:return (void*)&p->acurr;
case 13:return (void*)&p->abon;
case 14:return (void*)&p->atemp;
case 15:return (void*)&p->ualign;
case 16:return (void*)&p->ualignbase;
case 17:return (void*)&p->uhitinc;
case 18:return (void*)&p->udaminc;
case 19:return (void*)&p->uac;
case 20:return (void*)&p->uspellprot;
case 21:return (void*)&p->ublessed;
case 22:return (void*)&p->usteed;
case 23:return (void*)&p->twoweap;
default:abort();}}
case 1:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 2:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->blocked;
case 2:return (void*)&p->intrinsic;
default:abort();}}
case 3:{struct u_roleplay*p=at;switch(field){
case 0:return (void*)&p->blind;
default:abort();}}
case 4:{struct attribs*p=at;switch(field){
case 0:return (void*)&p->a;
default:abort();}}
case 5:{struct align*p=at;switch(field){
case 0:return (void*)&p->type;
default:abort();}}
case 6:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
default:abort();}}
case 7:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->mlet;
case 1:return (void*)&p->ac;
case 2:return (void*)&p->msize;
case 3:return (void*)&p->mflags1;
default:abort();}}
case 8:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->nomovemsg;
default:abort();}}
case 9:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
case 1:return (void*)&p->initial_don;
case 2:return (void*)&p->item_action_in_progress;
default:abort();}}
case 10:{struct obj*p=at;switch(field){
case 0:return (void*)&p->nobj;
case 1:return (void*)&p->o_id;
case 2:return (void*)&p->otyp;
case 3:return (void*)&p->quan;
case 4:return (void*)&p->spe;
case 5:return (void*)&p->oclass;
case 16:return (void*)&p->corpsenm;
case 17:return (void*)&p->owornmask;
default:abort();}}
case 11:{struct instance_globals_w*p=at;switch(field){
case 0:return (void*)&p->wasinwater;
default:abort();}}
case 12:{struct objclass*p=at;switch(field){
case 4:return (void*)&p->oc_subtyp;
case 5:return (void*)&p->oc_oprop;
case 6:return (void*)&p->oc_delay;
case 7:return (void*)&p->oc_oc1;
default:abort();}}
case 13:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->mon_moving;
case 1:return (void*)&p->takeoff;
default:abort();}}
case 14:{struct takeoff_info*p=at;switch(field){
case 0:return (void*)&p->mask;
case 1:return (void*)&p->what;
case 2:return (void*)&p->delay;
case 3:return (void*)&p->cancelled_don;
case 4:return (void*)&p->disrobing;
default:abort();}}
case 15:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_something;
default:abort();}}
case 16:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->multi;
case 1:return (void*)&p->multi_reason;
default:abort();}}
case 17:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_water_level;
case 1:return (void*)&p->d_air_level;
case 2:return (void*)&p->d_qstart_level;
default:abort();}}
case 18:{union any*p=at;switch(field){
case 0:return (void*)&p->a_obj;
case 1:return (void*)&p->a_int;
default:abort();}}
case 19:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->in_lava_effects;
default:abort();}}
case 20:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
default:abort();}}
case 21:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 22:{struct const_globals*p=at;switch(field){
case 0:return (void*)&p->zeroobj;
default:abort();}}
case 23:{struct c_color_names*p=at;switch(field){
case 0:return (void*)&p->c_black;
default:abort();}}
case 24:{struct flag*p=at;switch(field){
case 0:return (void*)&p->female;
case 1:return (void*)&p->verbose;
case 2:return (void*)&p->paranoia_bits;
case 3:return (void*)&p->menu_style;
default:abort();}}
case 25:{struct Role*p=at;switch(field){
case 0:return (void*)&p->mnum;
default:abort();}}
case 26:{struct mi*p=at;switch(field){
case 0:return (void*)&p->item;
default:abort();}}
case 27:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 28:{struct _cmd_queue*p=at;switch(field){
case 0:return (void*)&p->typ;
case 1:return (void*)&p->key;
default:abort();}}
case 29:{struct condtests_t*p=at;switch(field){
case 0:return (void*)&p->enabled;
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
default:abort();}}
case 31:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
default:abort();}}
case 32:{struct instance_globals_a*p=at;switch(field){
case 0:return (void*)&p->afternmv;
default:abort();}}
case 33:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->restoring;
default:abort();}}
case 34:{struct rm*p=at;switch(field){
default:abort();}}
default:abort();}}
void*teleport_do_wear_literal(unsigned n){return malloc(n);}

#include "tu-do_wear-varargs.inc"
