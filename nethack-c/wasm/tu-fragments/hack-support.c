/* HACK native storage, exact fields and typed dependency transport only. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hack-source-data.h"
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4,"HACK memory64 ABI");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0,"HACK signed boolean");
static char teleport_hack_in_rooms_buf[5];
void*teleport_hack_in_rooms_buf_storage(void){return teleport_hack_in_rooms_buf;}
void*teleport_hack_global(int i){switch(i){
case 0:return(void*)&gt;
case 1:return(void*)&cg;
case 2:return(void*)&svl;
case 3:return(void*)&mons;
case 4:return(void*)&u;
case 5:return(void*)&gy;
case 6:return(void*)&gi;
case 7:return(void*)&gb;
case 8:return(void*)&svm;
case 9:return(void*)&flags;
case 10:return(void*)&svc;
case 11:return(void*)&svd;
case 12:return(void*)&gv;
case 13:return(void*)&objects;
case 14:return(void*)&uarmf;
case 15:return(void*)&uleft;
case 16:return(void*)&uright;
case 17:return(void*)&svi;
case 18:return(void*)&uwep;
case 19:return(void*)&defsyms;
case 20:return(void*)&iflags;
case 21:return(void*)&xdir;
case 22:return(void*)&dirs_ord;
case 23:return(void*)&ydir;
case 24:return(void*)&windowprocs;
case 25:return(void*)&a11y;
case 26:return(void*)&uswapwep;
case 27:return(void*)&svq;
case 28:return(void*)&gd;
case 29:return(void*)&gk;
case 30:return(void*)&disp;
case 31:return(void*)&uball;
case 32:return(void*)&c_common_strings;
case 33:return(void*)&gm;
case 34:return(void*)&gn;
case 35:return(void*)&uarmh;
case 36:return(void*)&svr;
case 37:return(void*)&svp;
case 38:return(void*)&gc;
case 39:return(void*)&ga;
case 40:return(void*)&gw;
case 41:return(void*)&gu;
case 42:return(void*)&svk;
case 43:return(void*)&obj_descr;
default:abort();}}
uint64_t teleport_hack_read(int kind,void*at,int field){switch(kind){
case 0:{struct instance_globals_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->tmp_anything);
case 1:return (uint64_t)(uintptr_t)(p->travelmap);
default:abort();}}
case 1:{struct const_globals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 2:{union any*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->a_uint);
case 1:return (uint64_t)(uintptr_t)(p->a_long);
case 2:return (uint64_t)(uintptr_t)(p->a_monst);
case 3:return (uint64_t)(uintptr_t)(p->a_obj);
default:abort();}}
case 3:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->objects);
case 1:return (uint64_t)(uintptr_t)(&p->monsters);
case 2:return (uint64_t)(uintptr_t)(&p->locations);
case 3:return (uint64_t)(uintptr_t)(&p->flags);
case 4:return (uint64_t)(uintptr_t)(p->objlist);
case 5:return (uint64_t)(uintptr_t)(p->monlist);
case 6:return (uint64_t)(uintptr_t)(p->buriedobjlist);
default:abort();}}
case 4:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
case 1:return (uint64_t)(uintptr_t)(&p->lastseentyp);
default:abort();}}
case 5:{union vptrs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 6:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->v);
case 1:return (uint64_t)(uintptr_t)(p->otyp);
case 2:return (uint64_t)(uintptr_t)(p->corpsenm);
case 3:return (uint64_t)(uintptr_t)(p->o_id);
case 4:return (uint64_t)(uintptr_t)(p->unpaid);
case 5:return (uint64_t)(uintptr_t)(p->ox);
case 6:return (uint64_t)(uintptr_t)(p->oy);
case 7:return (uint64_t)(uintptr_t)(p->owornmask);
case 8:return (uint64_t)(uintptr_t)(p->oclass);
case 9:return (uint64_t)(uintptr_t)(p->oerodeproof);
case 10:return (uint64_t)(uintptr_t)(p->rknown);
case 11:return (uint64_t)(uintptr_t)(p->owt);
case 12:return (uint64_t)(uintptr_t)(p->nobj);
case 13:return (uint64_t)(uintptr_t)(p->timed);
case 14:return (uint64_t)(uintptr_t)(p->quan);
case 15:return (uint64_t)(uintptr_t)(p->oartifact);
case 16:return (uint64_t)(uintptr_t)(p->spe);
case 17:return (uint64_t)(uintptr_t)(p->lamplit);
case 18:return (uint64_t)(uintptr_t)(p->invlet);
default:abort();}}
case 7:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
case 1:return (uint64_t)(uintptr_t)(p->mextra);
case 2:return (uint64_t)(uintptr_t)(p->mtrapped);
case 3:return (uint64_t)(uintptr_t)(p->mundetected);
case 4:return (uint64_t)(uintptr_t)(p->m_ap_type);
case 5:return (uint64_t)(uintptr_t)(p->mspotted);
case 6:return (uint64_t)(uintptr_t)(p->mhp);
case 7:return (uint64_t)(uintptr_t)(p->mx);
case 8:return (uint64_t)(uintptr_t)(p->my);
case 9:return (uint64_t)(uintptr_t)(p->mtame);
case 10:return (uint64_t)(uintptr_t)(p->mpeaceful);
case 11:return (uint64_t)(uintptr_t)(p->nmon);
case 12:return (uint64_t)(uintptr_t)(p->mux);
case 13:return (uint64_t)(uintptr_t)(p->muy);
case 14:return (uint64_t)(uintptr_t)(p->msleeping);
case 15:return (uint64_t)(uintptr_t)(p->mcanmove);
case 16:return (uint64_t)(uintptr_t)(p->meating);
case 17:return (uint64_t)(uintptr_t)(p->minvent);
case 18:return (uint64_t)(uintptr_t)(p->ispriest);
case 19:return (uint64_t)(uintptr_t)(p->isshk);
case 20:return (uint64_t)(uintptr_t)(p->isgd);
case 21:return (uint64_t)(uintptr_t)(p->m_id);
case 22:return (uint64_t)(uintptr_t)(p->mfrozen);
case 23:return (uint64_t)(uintptr_t)(p->mconf);
case 24:return (uint64_t)(uintptr_t)(p->mappearance);
default:abort();}}
case 8:{struct nhcoord*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->x);
case 1:return (uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 9:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->intrinsic);
case 1:return (uint64_t)(uintptr_t)(p->extrinsic);
case 2:return (uint64_t)(uintptr_t)(p->blocked);
default:abort();}}
case 10:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->uprops);
case 1:return (uint64_t)(uintptr_t)(p->usteed);
case 2:return (uint64_t)(uintptr_t)(p->dx);
case 3:return (uint64_t)(uintptr_t)(p->dy);
case 4:return (uint64_t)(uintptr_t)(p->ux);
case 5:return (uint64_t)(uintptr_t)(p->uy);
case 6:return (uint64_t)(uintptr_t)(&p->weapon_skills);
case 7:return (uint64_t)(uintptr_t)(&p->uz);
case 8:return (uint64_t)(uintptr_t)(&p->uroleplay);
case 9:return (uint64_t)(uintptr_t)(p->uhunger);
case 10:return (uint64_t)(uintptr_t)(p->udaminc);
case 11:return (uint64_t)(uintptr_t)(&p->uconduct);
case 12:return (uint64_t)(uintptr_t)(p->uinwater);
case 13:return (uint64_t)(uintptr_t)(p->tx);
case 14:return (uint64_t)(uintptr_t)(p->ty);
case 15:return (uint64_t)(uintptr_t)(p->umonnum);
case 16:return (uint64_t)(uintptr_t)(p->utrap);
case 17:return (uint64_t)(uintptr_t)(p->utraptype);
case 18:return (uint64_t)(uintptr_t)(p->umoved);
case 19:return (uint64_t)(uintptr_t)(p->ux0);
case 20:return (uint64_t)(uintptr_t)(p->uy0);
case 21:return (uint64_t)(uintptr_t)(p->ustuck);
case 22:return (uint64_t)(uintptr_t)(p->twoweap);
case 23:return (uint64_t)(uintptr_t)(p->ugangr);
case 24:return (uint64_t)(uintptr_t)(p->umonster);
case 25:return (uint64_t)(uintptr_t)(p->mh);
case 26:return (uint64_t)(uintptr_t)(p->mhmax);
case 27:return (uint64_t)(uintptr_t)(p->uhp);
case 28:return (uint64_t)(uintptr_t)(p->uhpmax);
case 29:return (uint64_t)(uintptr_t)(p->uswallow);
case 30:return (uint64_t)(uintptr_t)(&p->uevent);
case 31:return (uint64_t)(uintptr_t)(p->uundetected);
case 32:return (uint64_t)(uintptr_t)(p->uac);
case 33:return (uint64_t)(uintptr_t)(&p->urooms0);
case 34:return (uint64_t)(uintptr_t)(&p->urooms);
case 35:return (uint64_t)(uintptr_t)(&p->ushops0);
case 36:return (uint64_t)(uintptr_t)(&p->ushops);
case 37:return (uint64_t)(uintptr_t)(&p->uentered);
case 38:return (uint64_t)(uintptr_t)(&p->ushops_entered);
case 39:return (uint64_t)(uintptr_t)(&p->ushops_left);
case 40:return (uint64_t)(uintptr_t)(p->last_str_turn);
case 41:return (uint64_t)(uintptr_t)(p->uinvulnerable);
case 42:return (uint64_t)(uintptr_t)(p->usleep);
case 43:return (uint64_t)(uintptr_t)(p->mfemale);
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mflags2);
case 1:return (uint64_t)(uintptr_t)(p->msize);
case 2:return (uint64_t)(uintptr_t)(p->mflags1);
case 3:return (uint64_t)(uintptr_t)(p->mlet);
case 4:return (uint64_t)(uintptr_t)(p->mmove);
case 5:return (uint64_t)(uintptr_t)(p->pmidx);
case 6:return (uint64_t)(uintptr_t)(p->cwt);
case 7:return (uint64_t)(uintptr_t)(p->geno);
case 8:return (uint64_t)(uintptr_t)(&p->pmnames);
default:abort();}}
case 12:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 13:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->typ);
case 1:return (uint64_t)(uintptr_t)(p->glyph);
case 2:return (uint64_t)(uintptr_t)(p->flags);
case 3:return (uint64_t)(uintptr_t)(p->candig);
case 4:return (uint64_t)(uintptr_t)(p->seenv);
case 5:return (uint64_t)(uintptr_t)(p->roomno);
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
case 1:return (uint64_t)(uintptr_t)(p->in_steed_dismounting);
default:abort();}}
case 15:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->bldrpush_oid);
case 1:return (uint64_t)(uintptr_t)(p->bldrpushtime);
case 2:return (uint64_t)(uintptr_t)(&p->bhitpos);
default:abort();}}
case 16:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
case 1:return (uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 17:{struct eshk*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->shoproom);
default:abort();}}
case 18:{struct mextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->eshk);
case 1:return (uint64_t)(uintptr_t)(p->mgivenname);
default:abort();}}
case 19:{struct levelflags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->sokoban_rules);
case 1:return (uint64_t)(uintptr_t)(p->arboreal);
case 2:return (uint64_t)(uintptr_t)(p->is_maze_lev);
case 3:return (uint64_t)(uintptr_t)(p->is_cavernous_lev);
case 4:return (uint64_t)(uintptr_t)(p->has_town);
case 5:return (uint64_t)(uintptr_t)(p->has_court);
case 6:return (uint64_t)(uintptr_t)(p->has_swamp);
case 7:return (uint64_t)(uintptr_t)(p->has_morgue);
case 8:return (uint64_t)(uintptr_t)(p->has_zoo);
case 9:return (uint64_t)(uintptr_t)(p->has_barracks);
case 10:return (uint64_t)(uintptr_t)(p->has_temple);
case 11:return (uint64_t)(uintptr_t)(p->has_beehive);
default:abort();}}
case 20:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->pickup);
case 1:return (uint64_t)(uintptr_t)(p->verbose);
case 2:return (uint64_t)(uintptr_t)(p->mention_walls);
case 3:return (uint64_t)(uintptr_t)(p->autodig);
case 4:return (uint64_t)(uintptr_t)(p->autoopen);
case 5:return (uint64_t)(uintptr_t)(p->runmode);
case 6:return (uint64_t)(uintptr_t)(p->tips);
case 7:return (uint64_t)(uintptr_t)(p->paranoia_bits);
case 8:return (uint64_t)(uintptr_t)(p->time);
case 9:return (uint64_t)(uintptr_t)(p->terrainstatus);
case 10:return (uint64_t)(uintptr_t)(p->female);
default:abort();}}
case 21:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nopick);
case 1:return (uint64_t)(uintptr_t)(p->door_opened);
case 2:return (uint64_t)(uintptr_t)(p->move);
case 3:return (uint64_t)(uintptr_t)(&p->digging);
case 4:return (uint64_t)(uintptr_t)(p->run);
case 5:return (uint64_t)(uintptr_t)(p->travel1);
case 6:return (uint64_t)(uintptr_t)(p->tips);
case 7:return (uint64_t)(uintptr_t)(p->travel);
case 8:return (uint64_t)(uintptr_t)(p->forcefight);
case 9:return (uint64_t)(uintptr_t)(p->mon_moving);
case 10:return (uint64_t)(uintptr_t)(&p->achieveo);
case 11:return (uint64_t)(uintptr_t)(p->mv);
default:abort();}}
case 22:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 23:{struct skills*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->skill);
default:abort();}}
case 24:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dlevel);
case 1:return (uint64_t)(uintptr_t)(p->dnum);
default:abort();}}
case 25:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_air_level);
case 1:return (uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 2:return (uint64_t)(uintptr_t)(&p->d_water_level);
case 3:return (uint64_t)(uintptr_t)(&p->d_earth_level);
case 4:return (uint64_t)(uintptr_t)(&p->d_medusa_level);
case 5:return (uint64_t)(uintptr_t)(&p->d_juiblex_level);
case 6:return (uint64_t)(uintptr_t)(&p->d_rogue_level);
default:abort();}}
case 26:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 27:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ttyp);
case 1:return (uint64_t)(uintptr_t)(p->madeby_u);
case 2:return (uint64_t)(uintptr_t)(p->tseen);
case 3:return (uint64_t)(uintptr_t)(&p->launch);
case 4:return (uint64_t)(uintptr_t)(&p->vl);
case 5:return (uint64_t)(uintptr_t)(p->tx);
case 6:return (uint64_t)(uintptr_t)(p->ty);
default:abort();}}
case 28:{struct u_roleplay*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 29:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->viz_array);
case 1:return (uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 30:{union vlaunchinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->v_launch2);
default:abort();}}
case 31:{struct dig_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->down);
case 1:return (uint64_t)(uintptr_t)(p->chew);
case 2:return (uint64_t)(uintptr_t)(&p->pos);
case 3:return (uint64_t)(uintptr_t)(&p->level);
case 4:return (uint64_t)(uintptr_t)(p->warned);
case 5:return (uint64_t)(uintptr_t)(p->effort);
default:abort();}}
case 32:{struct u_conduct*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->food);
case 1:return (uint64_t)(uintptr_t)(p->killer);
default:abort();}}
case 33:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_weight);
case 1:return (uint64_t)(uintptr_t)(p->oc_subtyp);
case 2:return (uint64_t)(uintptr_t)(p->oc_name_known);
case 3:return (uint64_t)(uintptr_t)(p->oc_material);
case 4:return (uint64_t)(uintptr_t)(p->oc_unique);
default:abort();}}
case 34:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->inv_pos);
default:abort();}}
case 35:{struct symdef*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->explanation);
default:abort();}}
case 36:{struct _cmd_queue*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->typ);
case 1:return (uint64_t)(uintptr_t)(p->ec_entry);
default:abort();}}
case 37:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->travelcc);
case 1:return (uint64_t)(uintptr_t)(p->trav_debug);
case 2:return (uint64_t)(uintptr_t)(p->terrain_typ);
case 3:return (uint64_t)(uintptr_t)(p->last_msg);
case 4:return (uint64_t)(uintptr_t)(p->failing_untrap);
case 5:return (uint64_t)(uintptr_t)(p->in_lava_effects);
case 6:return (uint64_t)(uintptr_t)(p->showdamage);
default:abort();}}
case 38:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->win_delay_output);
case 1:return (uint64_t)(uintptr_t)(p->win_raw_print);
default:abort();}}
case 39:{struct accessibility_data*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mon_notices);
case 1:return (uint64_t)(uintptr_t)(p->mon_notices_blocked);
default:abort();}}
case 40:{struct q_score*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->leader_m_id);
default:abort();}}
case 41:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->quest_status);
default:abort();}}
case 42:{struct mvitals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->died);
default:abort();}}
case 43:{struct instance_globals_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->domove_succeeded);
case 1:return (uint64_t)(uintptr_t)(p->domove_attempting);
default:abort();}}
case 44:{struct instance_globals_k*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->kickedloc);
default:abort();}}
case 45:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
case 1:return (uint64_t)(uintptr_t)(p->time_botl);
default:abort();}}
case 46:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_Something);
case 1:return (uint64_t)(uintptr_t)(p->c_something);
case 2:return (uint64_t)(uintptr_t)(p->c_You_can_move_again);
default:abort();}}
case 47:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->multi_reason);
case 1:return (uint64_t)(uintptr_t)(p->multi);
case 2:return (uint64_t)(uintptr_t)(&p->multireasonbuf);
default:abort();}}
case 48:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 49:{struct engr*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->engr_type);
default:abort();}}
case 50:{struct u_event*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->uvibrated);
default:abort();}}
case 51:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 52:{struct mkroom*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ly);
case 1:return (uint64_t)(uintptr_t)(p->hy);
case 2:return (uint64_t)(uintptr_t)(p->lx);
case 3:return (uint64_t)(uintptr_t)(p->hx);
case 4:return (uint64_t)(uintptr_t)(p->rtype);
case 5:return (uint64_t)(uintptr_t)(p->nsubrooms);
default:abort();}}
case 53:{struct achievement_tracking*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->minetn_reached);
default:abort();}}
case 54:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 55:{struct instance_globals_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->command_count);
default:abort();}}
case 56:{struct instance_globals_a*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->afternmv);
default:abort();}}
case 57:{struct instance_globals_w*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wailmsg);
case 1:return (uint64_t)(uintptr_t)(p->wc);
default:abort();}}
case 58:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mnum);
case 1:return (uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 59:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
case 1:return (uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 60:{struct Race*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 61:{struct RoleName*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->m);
default:abort();}}
case 62:{struct kinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->format);
case 1:return (uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 63:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 64:{struct weight_table_entry*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wt);
case 1:return (uint64_t)(uintptr_t)(p->idx);
case 2:return (uint64_t)(uintptr_t)(p->wtyp);
case 3:return (uint64_t)(uintptr_t)(p->unique);
case 4:return (uint64_t)(uintptr_t)(p->nm);
default:abort();}}
case 65:{struct objdescr*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_name);
default:abort();}}
case 66:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 67:{struct mi*p=at;switch(field){
default:abort();}}
default:abort();}}
void teleport_hack_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct instance_globals_t*p=at;switch(field){
case 0:memmove(&p->tmp_anything,(void*)(uintptr_t)value,sizeof p->tmp_anything);return;
case 1:p->travelmap=(void*)(uintptr_t)value;return;
default:abort();}}
case 1:{struct const_globals*p=at;switch(field){
default:abort();}}
case 2:{union any*p=at;switch(field){
case 0:p->a_uint=value;return;
case 1:p->a_long=value;return;
case 2:p->a_monst=(void*)(uintptr_t)value;return;
case 3:p->a_obj=(void*)(uintptr_t)value;return;
default:abort();}}
case 3:{dlevel_t*p=at;switch(field){
case 3:memmove(&p->flags,(void*)(uintptr_t)value,sizeof p->flags);return;
case 4:p->objlist=(void*)(uintptr_t)value;return;
case 5:p->monlist=(void*)(uintptr_t)value;return;
case 6:p->buriedobjlist=(void*)(uintptr_t)value;return;
default:abort();}}
case 4:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level,(void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 5:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(void*)(uintptr_t)value;return;
default:abort();}}
case 6:{struct obj*p=at;switch(field){
case 0:memmove(&p->v,(void*)(uintptr_t)value,sizeof p->v);return;
case 1:p->otyp=value;return;
case 2:p->corpsenm=value;return;
case 3:p->o_id=value;return;
case 4:p->unpaid=value;return;
case 5:p->ox=value;return;
case 6:p->oy=value;return;
case 7:p->owornmask=value;return;
case 8:p->oclass=value;return;
case 9:p->oerodeproof=value;return;
case 10:p->rknown=value;return;
case 11:p->owt=value;return;
case 12:p->nobj=(void*)(uintptr_t)value;return;
case 13:p->timed=value;return;
case 14:p->quan=value;return;
case 15:p->oartifact=value;return;
case 16:p->spe=value;return;
case 17:p->lamplit=value;return;
case 18:p->invlet=value;return;
default:abort();}}
case 7:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
case 1:p->mextra=(void*)(uintptr_t)value;return;
case 2:p->mtrapped=value;return;
case 3:p->mundetected=value;return;
case 4:p->m_ap_type=value;return;
case 5:p->mspotted=value;return;
case 6:p->mhp=value;return;
case 7:p->mx=value;return;
case 8:p->my=value;return;
case 9:p->mtame=value;return;
case 10:p->mpeaceful=value;return;
case 11:p->nmon=(void*)(uintptr_t)value;return;
case 12:p->mux=value;return;
case 13:p->muy=value;return;
case 14:p->msleeping=value;return;
case 15:p->mcanmove=value;return;
case 16:p->meating=value;return;
case 17:p->minvent=(void*)(uintptr_t)value;return;
case 18:p->ispriest=value;return;
case 19:p->isshk=value;return;
case 20:p->isgd=value;return;
case 21:p->m_id=value;return;
case 22:p->mfrozen=value;return;
case 23:p->mconf=value;return;
case 24:p->mappearance=value;return;
default:abort();}}
case 8:{struct nhcoord*p=at;switch(field){
case 0:p->x=value;return;
case 1:p->y=value;return;
default:abort();}}
case 9:{struct prop*p=at;switch(field){
case 0:p->intrinsic=value;return;
case 1:p->extrinsic=value;return;
case 2:p->blocked=value;return;
default:abort();}}
case 10:{struct you*p=at;switch(field){
case 1:p->usteed=(void*)(uintptr_t)value;return;
case 2:p->dx=value;return;
case 3:p->dy=value;return;
case 4:p->ux=value;return;
case 5:p->uy=value;return;
case 7:memmove(&p->uz,(void*)(uintptr_t)value,sizeof p->uz);return;
case 8:memmove(&p->uroleplay,(void*)(uintptr_t)value,sizeof p->uroleplay);return;
case 9:p->uhunger=value;return;
case 10:p->udaminc=value;return;
case 11:memmove(&p->uconduct,(void*)(uintptr_t)value,sizeof p->uconduct);return;
case 12:p->uinwater=value;return;
case 13:p->tx=value;return;
case 14:p->ty=value;return;
case 15:p->umonnum=value;return;
case 16:p->utrap=value;return;
case 17:p->utraptype=value;return;
case 18:p->umoved=value;return;
case 19:p->ux0=value;return;
case 20:p->uy0=value;return;
case 21:p->ustuck=(void*)(uintptr_t)value;return;
case 22:p->twoweap=value;return;
case 23:p->ugangr=value;return;
case 24:p->umonster=value;return;
case 25:p->mh=value;return;
case 26:p->mhmax=value;return;
case 27:p->uhp=value;return;
case 28:p->uhpmax=value;return;
case 29:p->uswallow=value;return;
case 30:memmove(&p->uevent,(void*)(uintptr_t)value,sizeof p->uevent);return;
case 31:p->uundetected=value;return;
case 32:p->uac=value;return;
case 40:p->last_str_turn=value;return;
case 41:p->uinvulnerable=value;return;
case 42:p->usleep=value;return;
case 43:p->mfemale=value;return;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:p->mflags2=value;return;
case 1:p->msize=value;return;
case 2:p->mflags1=value;return;
case 3:p->mlet=value;return;
case 4:p->mmove=value;return;
case 6:p->cwt=value;return;
case 7:p->geno=value;return;
default:abort();}}
case 12:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst,(void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 13:{struct rm*p=at;switch(field){
case 0:p->typ=value;return;
case 1:p->glyph=value;return;
case 2:p->flags=value;return;
case 3:p->candig=value;return;
case 4:p->seenv=value;return;
case 5:p->roomno=value;return;
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
case 1:p->in_steed_dismounting=value;return;
default:abort();}}
case 15:{struct instance_globals_b*p=at;switch(field){
case 0:p->bldrpush_oid=value;return;
case 1:p->bldrpushtime=value;return;
case 2:memmove(&p->bhitpos,(void*)(uintptr_t)value,sizeof p->bhitpos);return;
default:abort();}}
case 16:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 17:{struct eshk*p=at;switch(field){
case 0:p->shoproom=value;return;
default:abort();}}
case 18:{struct mextra*p=at;switch(field){
case 0:p->eshk=(void*)(uintptr_t)value;return;
case 1:p->mgivenname=(void*)(uintptr_t)value;return;
default:abort();}}
case 19:{struct levelflags*p=at;switch(field){
case 0:p->sokoban_rules=value;return;
case 1:p->arboreal=value;return;
case 2:p->is_maze_lev=value;return;
case 3:p->is_cavernous_lev=value;return;
case 4:p->has_town=value;return;
case 5:p->has_court=value;return;
case 6:p->has_swamp=value;return;
case 7:p->has_morgue=value;return;
case 8:p->has_zoo=value;return;
case 9:p->has_barracks=value;return;
case 10:p->has_temple=value;return;
case 11:p->has_beehive=value;return;
default:abort();}}
case 20:{struct flag*p=at;switch(field){
case 0:p->pickup=value;return;
case 1:p->verbose=value;return;
case 2:p->mention_walls=value;return;
case 3:p->autodig=value;return;
case 4:p->autoopen=value;return;
case 5:p->runmode=value;return;
case 6:p->tips=value;return;
case 7:p->paranoia_bits=value;return;
case 8:p->time=value;return;
case 9:p->terrainstatus=value;return;
case 10:p->female=value;return;
default:abort();}}
case 21:{struct context_info*p=at;switch(field){
case 0:p->nopick=value;return;
case 1:p->door_opened=value;return;
case 2:p->move=value;return;
case 3:memmove(&p->digging,(void*)(uintptr_t)value,sizeof p->digging);return;
case 4:p->run=value;return;
case 5:p->travel1=value;return;
case 6:p->tips=value;return;
case 7:p->travel=value;return;
case 8:p->forcefight=value;return;
case 9:p->mon_moving=value;return;
case 10:memmove(&p->achieveo,(void*)(uintptr_t)value,sizeof p->achieveo);return;
case 11:p->mv=value;return;
default:abort();}}
case 22:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context,(void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 23:{struct skills*p=at;switch(field){
case 0:p->skill=value;return;
default:abort();}}
case 24:{struct d_level*p=at;switch(field){
case 0:p->dlevel=value;return;
case 1:p->dnum=value;return;
default:abort();}}
case 25:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_air_level,(void*)(uintptr_t)value,sizeof p->d_air_level);return;
case 1:p->d_sokoban_dnum=value;return;
case 2:memmove(&p->d_water_level,(void*)(uintptr_t)value,sizeof p->d_water_level);return;
case 3:memmove(&p->d_earth_level,(void*)(uintptr_t)value,sizeof p->d_earth_level);return;
case 4:memmove(&p->d_medusa_level,(void*)(uintptr_t)value,sizeof p->d_medusa_level);return;
case 5:memmove(&p->d_juiblex_level,(void*)(uintptr_t)value,sizeof p->d_juiblex_level);return;
case 6:memmove(&p->d_rogue_level,(void*)(uintptr_t)value,sizeof p->d_rogue_level);return;
default:abort();}}
case 26:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology,(void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 27:{struct trap*p=at;switch(field){
case 0:p->ttyp=value;return;
case 1:p->madeby_u=value;return;
case 2:p->tseen=value;return;
case 3:memmove(&p->launch,(void*)(uintptr_t)value,sizeof p->launch);return;
case 4:memmove(&p->vl,(void*)(uintptr_t)value,sizeof p->vl);return;
case 5:p->tx=value;return;
case 6:p->ty=value;return;
default:abort();}}
case 28:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=value;return;
default:abort();}}
case 29:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(void*)(uintptr_t)value;return;
case 1:p->vision_full_recalc=value;return;
default:abort();}}
case 30:{union vlaunchinfo*p=at;switch(field){
case 0:memmove(&p->v_launch2,(void*)(uintptr_t)value,sizeof p->v_launch2);return;
default:abort();}}
case 31:{struct dig_info*p=at;switch(field){
case 0:p->down=value;return;
case 1:p->chew=value;return;
case 2:memmove(&p->pos,(void*)(uintptr_t)value,sizeof p->pos);return;
case 3:memmove(&p->level,(void*)(uintptr_t)value,sizeof p->level);return;
case 4:p->warned=value;return;
case 5:p->effort=value;return;
default:abort();}}
case 32:{struct u_conduct*p=at;switch(field){
case 0:p->food=value;return;
case 1:p->killer=value;return;
default:abort();}}
case 33:{struct objclass*p=at;switch(field){
case 0:p->oc_weight=value;return;
case 1:p->oc_subtyp=value;return;
case 2:p->oc_name_known=value;return;
case 3:p->oc_material=value;return;
case 4:p->oc_unique=value;return;
default:abort();}}
case 34:{struct instance_globals_saved_i*p=at;switch(field){
case 0:memmove(&p->inv_pos,(void*)(uintptr_t)value,sizeof p->inv_pos);return;
default:abort();}}
case 35:{struct symdef*p=at;switch(field){
case 0:p->explanation=(void*)(uintptr_t)value;return;
default:abort();}}
case 36:{struct _cmd_queue*p=at;switch(field){
case 0:p->typ=value;return;
case 1:p->ec_entry=(void*)(uintptr_t)value;return;
default:abort();}}
case 37:{struct instance_flags*p=at;switch(field){
case 0:memmove(&p->travelcc,(void*)(uintptr_t)value,sizeof p->travelcc);return;
case 1:p->trav_debug=value;return;
case 2:p->terrain_typ=value;return;
case 3:p->last_msg=value;return;
case 4:p->failing_untrap=value;return;
case 5:p->in_lava_effects=value;return;
case 6:p->showdamage=value;return;
default:abort();}}
case 38:{struct window_procs*p=at;switch(field){
case 0:p->win_delay_output=(__typeof__(p->win_delay_output))(uintptr_t)value;return;
case 1:p->win_raw_print=(__typeof__(p->win_raw_print))(uintptr_t)value;return;
default:abort();}}
case 39:{struct accessibility_data*p=at;switch(field){
case 0:p->mon_notices=value;return;
case 1:p->mon_notices_blocked=value;return;
default:abort();}}
case 40:{struct q_score*p=at;switch(field){
case 0:p->leader_m_id=value;return;
default:abort();}}
case 41:{struct instance_globals_saved_q*p=at;switch(field){
case 0:memmove(&p->quest_status,(void*)(uintptr_t)value,sizeof p->quest_status);return;
default:abort();}}
case 42:{struct mvitals*p=at;switch(field){
case 0:p->died=value;return;
default:abort();}}
case 43:{struct instance_globals_d*p=at;switch(field){
case 0:p->domove_succeeded=value;return;
case 1:p->domove_attempting=value;return;
default:abort();}}
case 44:{struct instance_globals_k*p=at;switch(field){
case 0:memmove(&p->kickedloc,(void*)(uintptr_t)value,sizeof p->kickedloc);return;
default:abort();}}
case 45:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
case 1:p->time_botl=value;return;
default:abort();}}
case 46:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 47:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi_reason=(void*)(uintptr_t)value;return;
case 1:p->multi=value;return;
default:abort();}}
case 48:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(void*)(uintptr_t)value;return;
default:abort();}}
case 49:{struct engr*p=at;switch(field){
case 0:p->engr_type=value;return;
default:abort();}}
case 50:{struct u_event*p=at;switch(field){
case 0:p->uvibrated=value;return;
default:abort();}}
case 51:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 52:{struct mkroom*p=at;switch(field){
case 0:p->ly=value;return;
case 1:p->hy=value;return;
case 2:p->lx=value;return;
case 3:p->hx=value;return;
case 4:p->rtype=value;return;
case 5:p->nsubrooms=value;return;
default:abort();}}
case 53:{struct achievement_tracking*p=at;switch(field){
case 0:p->minetn_reached=value;return;
default:abort();}}
case 54:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 55:{struct instance_globals_c*p=at;switch(field){
case 0:p->command_count=value;return;
default:abort();}}
case 56:{struct instance_globals_a*p=at;switch(field){
case 0:p->afternmv=(__typeof__(p->afternmv))(uintptr_t)value;return;
default:abort();}}
case 57:{struct instance_globals_w*p=at;switch(field){
case 0:p->wailmsg=value;return;
case 1:p->wc=value;return;
default:abort();}}
case 58:{struct Role*p=at;switch(field){
case 0:p->mnum=value;return;
case 1:memmove(&p->name,(void*)(uintptr_t)value,sizeof p->name);return;
default:abort();}}
case 59:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole,(void*)(uintptr_t)value,sizeof p->urole);return;
case 1:memmove(&p->urace,(void*)(uintptr_t)value,sizeof p->urace);return;
default:abort();}}
case 60:{struct Race*p=at;switch(field){
case 0:p->mnum=value;return;
default:abort();}}
case 61:{struct RoleName*p=at;switch(field){
case 0:p->m=(void*)(uintptr_t)value;return;
default:abort();}}
case 62:{struct kinfo*p=at;switch(field){
case 0:p->format=value;return;
default:abort();}}
case 63:{struct instance_globals_saved_k*p=at;switch(field){
case 0:memmove(&p->killer,(void*)(uintptr_t)value,sizeof p->killer);return;
default:abort();}}
case 64:{struct weight_table_entry*p=at;switch(field){
case 0:p->wt=value;return;
case 1:p->idx=value;return;
case 2:p->wtyp=value;return;
case 3:p->unique=value;return;
case 4:p->nm=(void*)(uintptr_t)value;return;
default:abort();}}
case 65:{struct objdescr*p=at;switch(field){
case 0:p->oc_name=(void*)(uintptr_t)value;return;
default:abort();}}
case 66:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 67:{struct mi*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_hack_address(int kind,void*at,int field){switch(kind){
case 0:{struct instance_globals_t*p=at;switch(field){
case 0:return (void*)&p->tmp_anything;
case 1:return (void*)&p->travelmap;
default:abort();}}
case 1:{struct const_globals*p=at;switch(field){
case 0:return (void*)&p->zeroany;
default:abort();}}
case 2:{union any*p=at;switch(field){
case 0:return (void*)&p->a_uint;
case 1:return (void*)&p->a_long;
case 2:return (void*)&p->a_monst;
case 3:return (void*)&p->a_obj;
default:abort();}}
case 3:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->objects;
case 1:return (void*)&p->monsters;
case 2:return (void*)&p->locations;
case 3:return (void*)&p->flags;
case 4:return (void*)&p->objlist;
case 5:return (void*)&p->monlist;
case 6:return (void*)&p->buriedobjlist;
default:abort();}}
case 4:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
case 1:return (void*)&p->lastseentyp;
default:abort();}}
case 5:{union vptrs*p=at;switch(field){
case 0:return (void*)&p->v_nexthere;
default:abort();}}
case 6:{struct obj*p=at;switch(field){
case 0:return (void*)&p->v;
case 1:return (void*)&p->otyp;
case 2:return (void*)&p->corpsenm;
case 3:return (void*)&p->o_id;
case 5:return (void*)&p->ox;
case 6:return (void*)&p->oy;
case 7:return (void*)&p->owornmask;
case 8:return (void*)&p->oclass;
case 11:return (void*)&p->owt;
case 12:return (void*)&p->nobj;
case 13:return (void*)&p->timed;
case 14:return (void*)&p->quan;
case 15:return (void*)&p->oartifact;
case 16:return (void*)&p->spe;
case 18:return (void*)&p->invlet;
default:abort();}}
case 7:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
case 1:return (void*)&p->mextra;
case 4:return (void*)&p->m_ap_type;
case 6:return (void*)&p->mhp;
case 7:return (void*)&p->mx;
case 8:return (void*)&p->my;
case 9:return (void*)&p->mtame;
case 11:return (void*)&p->nmon;
case 12:return (void*)&p->mux;
case 13:return (void*)&p->muy;
case 16:return (void*)&p->meating;
case 17:return (void*)&p->minvent;
case 21:return (void*)&p->m_id;
case 24:return (void*)&p->mappearance;
default:abort();}}
case 8:{struct nhcoord*p=at;switch(field){
case 0:return (void*)&p->x;
case 1:return (void*)&p->y;
default:abort();}}
case 9:{struct prop*p=at;switch(field){
case 0:return (void*)&p->intrinsic;
case 1:return (void*)&p->extrinsic;
case 2:return (void*)&p->blocked;
default:abort();}}
case 10:{struct you*p=at;switch(field){
case 0:return (void*)&p->uprops;
case 1:return (void*)&p->usteed;
case 2:return (void*)&p->dx;
case 3:return (void*)&p->dy;
case 4:return (void*)&p->ux;
case 5:return (void*)&p->uy;
case 6:return (void*)&p->weapon_skills;
case 7:return (void*)&p->uz;
case 8:return (void*)&p->uroleplay;
case 9:return (void*)&p->uhunger;
case 10:return (void*)&p->udaminc;
case 11:return (void*)&p->uconduct;
case 13:return (void*)&p->tx;
case 14:return (void*)&p->ty;
case 15:return (void*)&p->umonnum;
case 16:return (void*)&p->utrap;
case 17:return (void*)&p->utraptype;
case 18:return (void*)&p->umoved;
case 19:return (void*)&p->ux0;
case 20:return (void*)&p->uy0;
case 21:return (void*)&p->ustuck;
case 22:return (void*)&p->twoweap;
case 23:return (void*)&p->ugangr;
case 24:return (void*)&p->umonster;
case 25:return (void*)&p->mh;
case 26:return (void*)&p->mhmax;
case 27:return (void*)&p->uhp;
case 28:return (void*)&p->uhpmax;
case 30:return (void*)&p->uevent;
case 32:return (void*)&p->uac;
case 33:return (void*)&p->urooms0;
case 34:return (void*)&p->urooms;
case 35:return (void*)&p->ushops0;
case 36:return (void*)&p->ushops;
case 37:return (void*)&p->uentered;
case 38:return (void*)&p->ushops_entered;
case 39:return (void*)&p->ushops_left;
case 40:return (void*)&p->last_str_turn;
case 42:return (void*)&p->usleep;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->mflags2;
case 1:return (void*)&p->msize;
case 2:return (void*)&p->mflags1;
case 3:return (void*)&p->mlet;
case 4:return (void*)&p->mmove;
case 5:return (void*)&p->pmidx;
case 6:return (void*)&p->cwt;
case 7:return (void*)&p->geno;
case 8:return (void*)&p->pmnames;
default:abort();}}
case 12:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 13:{struct rm*p=at;switch(field){
case 0:return (void*)&p->typ;
case 1:return (void*)&p->glyph;
case 4:return (void*)&p->seenv;
default:abort();}}
case 14:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
case 1:return (void*)&p->in_steed_dismounting;
default:abort();}}
case 15:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->bldrpush_oid;
case 1:return (void*)&p->bldrpushtime;
case 2:return (void*)&p->bhitpos;
default:abort();}}
case 16:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
case 1:return (void*)&p->mvitals;
default:abort();}}
case 17:{struct eshk*p=at;switch(field){
case 0:return (void*)&p->shoproom;
default:abort();}}
case 18:{struct mextra*p=at;switch(field){
case 0:return (void*)&p->eshk;
case 1:return (void*)&p->mgivenname;
default:abort();}}
case 19:{struct levelflags*p=at;switch(field){
default:abort();}}
case 20:{struct flag*p=at;switch(field){
case 0:return (void*)&p->pickup;
case 1:return (void*)&p->verbose;
case 2:return (void*)&p->mention_walls;
case 3:return (void*)&p->autodig;
case 4:return (void*)&p->autoopen;
case 5:return (void*)&p->runmode;
case 6:return (void*)&p->tips;
case 7:return (void*)&p->paranoia_bits;
case 8:return (void*)&p->time;
case 9:return (void*)&p->terrainstatus;
case 10:return (void*)&p->female;
default:abort();}}
case 21:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->nopick;
case 1:return (void*)&p->door_opened;
case 2:return (void*)&p->move;
case 3:return (void*)&p->digging;
case 4:return (void*)&p->run;
case 5:return (void*)&p->travel1;
case 6:return (void*)&p->tips;
case 7:return (void*)&p->travel;
case 8:return (void*)&p->forcefight;
case 9:return (void*)&p->mon_moving;
case 10:return (void*)&p->achieveo;
case 11:return (void*)&p->mv;
default:abort();}}
case 22:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 23:{struct skills*p=at;switch(field){
case 0:return (void*)&p->skill;
default:abort();}}
case 24:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dlevel;
case 1:return (void*)&p->dnum;
default:abort();}}
case 25:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_air_level;
case 1:return (void*)&p->d_sokoban_dnum;
case 2:return (void*)&p->d_water_level;
case 3:return (void*)&p->d_earth_level;
case 4:return (void*)&p->d_medusa_level;
case 5:return (void*)&p->d_juiblex_level;
case 6:return (void*)&p->d_rogue_level;
default:abort();}}
case 26:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
default:abort();}}
case 27:{struct trap*p=at;switch(field){
case 3:return (void*)&p->launch;
case 4:return (void*)&p->vl;
case 5:return (void*)&p->tx;
case 6:return (void*)&p->ty;
default:abort();}}
case 28:{struct u_roleplay*p=at;switch(field){
case 0:return (void*)&p->deaf;
default:abort();}}
case 29:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->viz_array;
case 1:return (void*)&p->vision_full_recalc;
default:abort();}}
case 30:{union vlaunchinfo*p=at;switch(field){
case 0:return (void*)&p->v_launch2;
default:abort();}}
case 31:{struct dig_info*p=at;switch(field){
case 0:return (void*)&p->down;
case 1:return (void*)&p->chew;
case 2:return (void*)&p->pos;
case 3:return (void*)&p->level;
case 4:return (void*)&p->warned;
case 5:return (void*)&p->effort;
default:abort();}}
case 32:{struct u_conduct*p=at;switch(field){
case 0:return (void*)&p->food;
case 1:return (void*)&p->killer;
default:abort();}}
case 33:{struct objclass*p=at;switch(field){
case 0:return (void*)&p->oc_weight;
case 1:return (void*)&p->oc_subtyp;
default:abort();}}
case 34:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return (void*)&p->inv_pos;
default:abort();}}
case 35:{struct symdef*p=at;switch(field){
case 0:return (void*)&p->explanation;
default:abort();}}
case 36:{struct _cmd_queue*p=at;switch(field){
case 0:return (void*)&p->typ;
case 1:return (void*)&p->ec_entry;
default:abort();}}
case 37:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->travelcc;
case 1:return (void*)&p->trav_debug;
case 2:return (void*)&p->terrain_typ;
case 3:return (void*)&p->last_msg;
case 4:return (void*)&p->failing_untrap;
case 5:return (void*)&p->in_lava_effects;
case 6:return (void*)&p->showdamage;
default:abort();}}
case 38:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->win_delay_output;
case 1:return (void*)&p->win_raw_print;
default:abort();}}
case 39:{struct accessibility_data*p=at;switch(field){
case 0:return (void*)&p->mon_notices;
case 1:return (void*)&p->mon_notices_blocked;
default:abort();}}
case 40:{struct q_score*p=at;switch(field){
case 0:return (void*)&p->leader_m_id;
default:abort();}}
case 41:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (void*)&p->quest_status;
default:abort();}}
case 42:{struct mvitals*p=at;switch(field){
case 0:return (void*)&p->died;
default:abort();}}
case 43:{struct instance_globals_d*p=at;switch(field){
case 0:return (void*)&p->domove_succeeded;
case 1:return (void*)&p->domove_attempting;
default:abort();}}
case 44:{struct instance_globals_k*p=at;switch(field){
case 0:return (void*)&p->kickedloc;
default:abort();}}
case 45:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
case 1:return (void*)&p->time_botl;
default:abort();}}
case 46:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_Something;
case 1:return (void*)&p->c_something;
case 2:return (void*)&p->c_You_can_move_again;
default:abort();}}
case 47:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->multi_reason;
case 1:return (void*)&p->multi;
case 2:return (void*)&p->multireasonbuf;
default:abort();}}
case 48:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->nomovemsg;
default:abort();}}
case 49:{struct engr*p=at;switch(field){
case 0:return (void*)&p->engr_type;
default:abort();}}
case 50:{struct u_event*p=at;switch(field){
default:abort();}}
case 51:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (void*)&p->rooms;
default:abort();}}
case 52:{struct mkroom*p=at;switch(field){
case 0:return (void*)&p->ly;
case 1:return (void*)&p->hy;
case 2:return (void*)&p->lx;
case 3:return (void*)&p->hx;
case 4:return (void*)&p->rtype;
case 5:return (void*)&p->nsubrooms;
default:abort();}}
case 53:{struct achievement_tracking*p=at;switch(field){
case 0:return (void*)&p->minetn_reached;
default:abort();}}
case 54:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (void*)&p->plname;
default:abort();}}
case 55:{struct instance_globals_c*p=at;switch(field){
case 0:return (void*)&p->command_count;
default:abort();}}
case 56:{struct instance_globals_a*p=at;switch(field){
case 0:return (void*)&p->afternmv;
default:abort();}}
case 57:{struct instance_globals_w*p=at;switch(field){
case 0:return (void*)&p->wailmsg;
case 1:return (void*)&p->wc;
default:abort();}}
case 58:{struct Role*p=at;switch(field){
case 0:return (void*)&p->mnum;
case 1:return (void*)&p->name;
default:abort();}}
case 59:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
case 1:return (void*)&p->urace;
default:abort();}}
case 60:{struct Race*p=at;switch(field){
case 0:return (void*)&p->mnum;
default:abort();}}
case 61:{struct RoleName*p=at;switch(field){
case 0:return (void*)&p->m;
default:abort();}}
case 62:{struct kinfo*p=at;switch(field){
case 0:return (void*)&p->format;
case 1:return (void*)&p->name;
default:abort();}}
case 63:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (void*)&p->killer;
default:abort();}}
case 64:{struct weight_table_entry*p=at;switch(field){
case 0:return (void*)&p->wt;
case 1:return (void*)&p->idx;
case 2:return (void*)&p->wtyp;
case 3:return (void*)&p->unique;
case 4:return (void*)&p->nm;
default:abort();}}
case 65:{struct objdescr*p=at;switch(field){
case 0:return (void*)&p->oc_name;
default:abort();}}
case 66:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 67:{struct mi*p=at;switch(field){
default:abort();}}
default:abort();}}
static char hack_literals[HACK_LITERAL_CAPACITY];
char*teleport_hack_literal_storage(void){return hack_literals;}
size_t teleport_hack_literal_capacity(void){return sizeof hack_literals;}
void teleport_hack_rng_caller(int line,const char*caller){if(rng_log_enabled())rng_log_set_caller("hack.c",line,caller);}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
void teleport_hack_Norep_pp(char * a0,char * a1){(Norep)(a0,a1);}
void teleport_hack_pline_ppp(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_hack_You_pp(char * a0,char * a1){(You)(a0,a1);}
void teleport_hack_You_pppp(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_hack_pline_p(char * a0){(pline)(a0);}
void teleport_hack_There_p(char * a0){(There)(a0);}
void teleport_hack_pline_pp(char * a0,char * a1){(pline)(a0,a1);}
void teleport_hack_You_hear_pp(char * a0,char * a1){(You_hear)(a0,a1);}
void teleport_hack_pline_pppp(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_hack_pline_pppppp(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){(pline)(a0,a1,a2,a3,a4,a5);}
void teleport_hack_You_p(char * a0){(You)(a0);}
void teleport_hack_You_ppp(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_hack_livelog_printf_jpp(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_hack_pline_The_p(char * a0){(pline_The)(a0);}
int teleport_hack_sprintf_ppi(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_hack_pline_dir_ipp(int a0,char * a1,char * a2){(pline_dir)(a0,a1,a2);}
void teleport_hack_You_cant_pp(char * a0,char * a1){(You_cant)(a0,a1);}
void teleport_hack_You_cant_p(char * a0){(You_cant)(a0);}
void teleport_hack_Your_p(char * a0){(Your)(a0);}
void teleport_hack_pline_dir_ip(int a0,char * a1){(pline_dir)(a0,a1);}
void teleport_hack_Norep_ppp(char * a0,char * a1,char * a2){(Norep)(a0,a1,a2);}
void teleport_hack_Norep_p(char * a0){(Norep)(a0);}
void teleport_hack_Norep_pppp(char * a0,char * a1,char * a2,char * a3){(Norep)(a0,a1,a2,a3);}
void teleport_hack_impossible_p(char * a0){(impossible)(a0);}
void teleport_hack_impossible_pi(char * a0,int a1){(impossible)(a0,a1);}
void teleport_hack_You_cant_pppp(char * a0,char * a1,char * a2,char * a3){(You_cant)(a0,a1,a2,a3);}
void teleport_hack_livelog_printf_jp(long a0,char * a1){(livelog_printf)(a0,a1);}
void teleport_hack_You_feel_p(char * a0){(You_feel)(a0);}
int teleport_hack_sprintf_ppp(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_hack_nh_snprintf_pipjppp(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_hack_nh_snprintf_pipjpppp(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,char * a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_hack_You_feel_pp(char * a0,char * a1){(You_feel)(a0,a1);}
void teleport_hack_verbalize_pp(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_hack_verbalize_ppp(char * a0,char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_hack_pline_xy_iipp(short a0,short a1,char * a2,char * a3){(pline_xy)(a0,a1,a2,a3);}
void teleport_hack_You_hear_p(char * a0){(You_hear)(a0);}
void teleport_hack_pline_pii(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_hack_urgent_pline_p(char * a0){(urgent_pline)(a0);}
void teleport_hack_nh_snprintf_pipjpi(char * a0,int a1,char * a2,unsigned long a3,char * a4,int a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_hack_nh_snprintf_pipjpip(char * a0,int a1,char * a2,unsigned long a3,char * a4,int a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_hack_raw_printf_p(char * a0){(raw_printf)(a0);}
void teleport_hack_raw_printf_pipip(char * a0,int a1,char * a2,int a3,char * a4){(raw_printf)(a0,a1,a2,a3,a4);}
void teleport_hack_panic_p(char * a0){(panic)(a0);}
#pragma clang diagnostic pop
winid teleport_hack_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_hack_putstr(winid a0,int a1,const char * a2){putstr(a0,a1,a2);}
void teleport_hack_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
void teleport_hack_destroy_nhwindow(winid a0){destroy_nhwindow(a0);}
void teleport_hack_start_menu(winid a0,unsigned long a1){start_menu(a0,a1);}
void teleport_hack_end_menu(winid a0,const char * a1){end_menu(a0,a1);}
void teleport_hack_raw_print(const char * a0){raw_print(a0);}
void teleport_hack_nh_delay_output(){nh_delay_output();}
int teleport_hack_call_int_function(uintptr_t fn){return ((int(*)(void))fn)();}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_hack_callback_notice_mons_cmp notice_mons_cmp
#else
extern int teleport_hack_callback_notice_mons_cmp(const void * a0,const void * a1);
#endif
#ifdef TELEPORT_REFERENCE_TU
#define teleport_hack_callback_cmp_weights cmp_weights
#else
extern int teleport_hack_callback_cmp_weights(const void * a0,const void * a1);
#endif
uintptr_t teleport_hack_function_pointer(int kind){switch(kind){
case 27:return(uintptr_t)&teleport_hack_callback_notice_mons_cmp;
case 90:return(uintptr_t)&teleport_hack_callback_cmp_weights;
default:abort();}}
uintptr_t teleport_hack_foreign_function_pointer(int kind){switch(kind){
case 0:return(uintptr_t)&Boots_on;
case 1:return(uintptr_t)&do_reqmenu;
case 2:return(uintptr_t)&dokick;
default:abort();}}
_Static_assert(__builtin_types_compatible_p(__typeof__(&enexto),boolean (*)(coord *,coordxy,coordxy,struct permonst *)),"HACK dependency enexto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rloc_to),void (*)(struct monst *,coordxy,coordxy)),"HACK dependency rloc_to");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Norep),void (*)(const char *,...)),"HACK dependency Norep");
_Static_assert(__builtin_types_compatible_p(__typeof__(&revive_corpse),boolean (*)(struct obj *)),"HACK dependency revive_corpse");
_Static_assert(__builtin_types_compatible_p(__typeof__(&goodpos),boolean (*)(coordxy,coordxy,struct monst *,mmflags_nht)),"HACK dependency goodpos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&the),char * (*)(const char *)),"HACK dependency the");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xname),char * (*)(struct obj *)),"HACK dependency xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline),void (*)(const char *,...)),"HACK dependency pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exercise),void (*)(int,boolean)),"HACK dependency exercise");
_Static_assert(__builtin_types_compatible_p(__typeof__(&YMonnam),char * (*)(struct monst *)),"HACK dependency YMonnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unmap_object),void (*)(coordxy,coordxy)),"HACK dependency unmap_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&feel_location),void (*)(coordxy,coordxy)),"HACK dependency feel_location");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy,coordxy)),"HACK dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&costly_spot),boolean (*)(coordxy,coordxy)),"HACK dependency costly_spot");
_Static_assert(__builtin_types_compatible_p(__typeof__(&addtobill),void (*)(struct obj *,boolean,boolean,boolean)),"HACK dependency addtobill");
_Static_assert(__builtin_types_compatible_p(__typeof__(&shop_keeper),struct monst * (*)(char)),"HACK dependency shop_keeper");
_Static_assert(__builtin_types_compatible_p(__typeof__(&onshopbill),boolean (*)(struct obj *,struct monst *,boolean)),"HACK dependency onshopbill");
_Static_assert(__builtin_types_compatible_p(__typeof__(&subfrombill),void (*)(struct obj *,struct monst *)),"HACK dependency subfrombill");
_Static_assert(__builtin_types_compatible_p(__typeof__(&find_objowner),struct monst * (*)(struct obj *,coordxy,coordxy)),"HACK dependency find_objowner");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strchr),char * (*)(const char *,int)),"HACK dependency strchr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stolen_value),long (*)(struct obj *,coordxy,coordxy,boolean,boolean)),"HACK dependency stolen_value");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You),void (*)(const char *,...)),"HACK dependency You");
_Static_assert(__builtin_types_compatible_p(__typeof__(&carrying),struct obj * (*)(int)),"HACK dependency carrying");
_Static_assert(__builtin_types_compatible_p(__typeof__(&autopick_testobj),boolean (*)(struct obj *,boolean)),"HACK dependency autopick_testobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&y_monnam),char * (*)(struct monst *)),"HACK dependency y_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sokoban_guilt),void (*)(void)),"HACK dependency sokoban_guilt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sobj_at),struct obj * (*)(int,coordxy,coordxy)),"HACK dependency sobj_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_at),int (*)(coordxy,coordxy)),"HACK dependency glyph_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_object),void (*)(struct obj *,int)),"HACK dependency map_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&There),void (*)(const char *,...)),"HACK dependency There");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),boolean (*)(d_level *,d_level *)),"HACK dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&isok),int (*)(coordxy,coordxy)),"HACK dependency isok");
_Static_assert(__builtin_types_compatible_p(__typeof__(&t_at),struct trap * (*)(coordxy,coordxy)),"HACK dependency t_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&The),char * (*)(const char *)),"HACK dependency The");
_Static_assert(__builtin_types_compatible_p(__typeof__(&surface),const char * (*)(coordxy,coordxy)),"HACK dependency surface");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"HACK dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"HACK dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&a_monnam),char * (*)(struct monst *)),"HACK dependency a_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_hear),void (*)(const char *,...)),"HACK dependency You_hear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_invisible),void (*)(coordxy,coordxy)),"HACK dependency map_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char * (*)(char *restrict,const char *restrict)),"HACK dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&upstart),char * (*)(char *)),"HACK dependency upstart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&closed_door),boolean (*)(coordxy,coordxy)),"HACK dependency closed_door");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"HACK dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *,int,const char *)),"HACK dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"HACK dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obj_extract_self),void (*)(struct obj *)),"HACK dependency obj_extract_self");
_Static_assert(__builtin_types_compatible_p(__typeof__(&place_object),void (*)(struct obj *,coordxy,coordxy)),"HACK dependency place_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Tobjnam),char * (*)(struct obj *,const char *)),"HACK dependency Tobjnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&blow_up_landmine),void (*)(struct trap *)),"HACK dependency blow_up_landmine");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fill_pit),void (*)(coordxy,coordxy)),"HACK dependency fill_pit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flooreffects),boolean (*)(struct obj *,coordxy,coordxy,const char *)),"HACK dependency flooreffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&otense),char * (*)(struct obj *,const char *)),"HACK dependency otense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&deltrap),void (*)(struct trap *)),"HACK dependency deltrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&useupf),void (*)(struct obj *,long)),"HACK dependency useupf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bury_objs),void (*)(int,int)),"HACK dependency bury_objs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&random_teleport_level),int (*)(void)),"HACK dependency random_teleport_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&depth),schar (*)(d_level *)),"HACK dependency depth");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rloco),boolean (*)(struct obj *)),"HACK dependency rloco");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_to_migration),void (*)(struct obj *)),"HACK dependency add_to_migration");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_level),void (*)(d_level *,int)),"HACK dependency get_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&seetrap),void (*)(struct trap *)),"HACK dependency seetrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&feeltrap),void (*)(struct trap *)),"HACK dependency feeltrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&launch_obj),int (*)(short,coordxy,coordxy,coordxy,coordxy,int)),"HACK dependency launch_obj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&boulder_hits_pool),boolean (*)(struct obj *,coordxy,coordxy,boolean)),"HACK dependency boulder_hits_pool");
_Static_assert(__builtin_types_compatible_p(__typeof__(&remove_object),void (*)(struct obj *)),"HACK dependency remove_object");
_Static_assert(__builtin_types_compatible_p(__typeof__(&memset),void * (*)(void *,int,size_t)),"HACK dependency memset");
_Static_assert(__builtin_types_compatible_p(__typeof__(&assign_level),void (*)(d_level *,d_level *)),"HACK dependency assign_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&watch_dig),void (*)(struct monst *,coordxy,coordxy,boolean)),"HACK dependency watch_dig");
_Static_assert(__builtin_types_compatible_p(__typeof__(&livelog_printf),void (*)(long,const char *,...)),"HACK dependency livelog_printf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd),int (*)(int)),"HACK dependency rnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&delobj),void (*)(struct obj *)),"HACK dependency delobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&block_point),void (*)(int,int)),"HACK dependency block_point");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_damage),void (*)(coordxy,coordxy,long)),"HACK dependency add_damage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&acurrstr),schar (*)(void)),"HACK dependency acurrstr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&morehungry),void (*)(int)),"HACK dependency morehungry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dissolve_bars),void (*)(coordxy,coordxy)),"HACK dependency dissolve_bars");
_Static_assert(__builtin_types_compatible_p(__typeof__(&b_trapped),void (*)(const char *,int)),"HACK dependency b_trapped");
_Static_assert(__builtin_types_compatible_p(__typeof__(&recalc_block_point),void (*)(coordxy,coordxy)),"HACK dependency recalc_block_point");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pay_for_damage),void (*)(const char *,boolean)),"HACK dependency pay_for_damage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maybe_unhide_at),void (*)(coordxy,coordxy)),"HACK dependency maybe_unhide_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&acurr),schar (*)(int)),"HACK dependency acurr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&selftouch),void (*)(const char *)),"HACK dependency selftouch");
_Static_assert(__builtin_types_compatible_p(__typeof__(&doname),char * (*)(struct obj *)),"HACK dependency doname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stop_donning),int (*)(struct obj *)),"HACK dependency stop_donning");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Ring_off),void (*)(struct obj *)),"HACK dependency Ring_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&off_msg),void (*)(struct obj *)),"HACK dependency off_msg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Boots_off),int (*)(void)),"HACK dependency Boots_off");
_Static_assert(__builtin_types_compatible_p(__typeof__(&float_vs_flight),void (*)(void)),"HACK dependency float_vs_flight");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_fog),boolean (*)(struct monst *)),"HACK dependency can_fog");
_Static_assert(__builtin_types_compatible_p(__typeof__(&curr_mon_load),int (*)(struct monst *)),"HACK dependency curr_mon_load");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Invocation_lev),boolean (*)(d_level *)),"HACK dependency Invocation_lev");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype),boolean (*)(struct permonst *,int)),"HACK dependency dmgtype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&passes_bars),boolean (*)(struct permonst *)),"HACK dependency passes_bars");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_pick_axe2),int (*)(struct obj *)),"HACK dependency use_pick_axe2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_db_wall),boolean (*)(coordxy,coordxy)),"HACK dependency is_db_wall");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline_The),void (*)(const char *,...)),"HACK dependency pline_The");
_Static_assert(__builtin_types_compatible_p(__typeof__(&back_to_glyph),int (*)(coordxy,coordxy)),"HACK dependency back_to_glyph");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_to_cmap),int (*)(int)),"HACK dependency glyph_to_cmap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&an),char * (*)(const char *)),"HACK dependency an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sprintf),int (*)(char *restrict,const char *restrict,...)),"HACK dependency sprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline_dir),void (*)(int,const char *,...)),"HACK dependency pline_dir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xytodir),int (*)(int,int)),"HACK dependency xytodir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_ooze),boolean (*)(struct monst *)),"HACK dependency can_ooze");
_Static_assert(__builtin_types_compatible_p(__typeof__(&doopen_indir),int (*)(coordxy,coordxy)),"HACK dependency doopen_indir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cmdq_peek),struct _cmd_queue * (*)(int)),"HACK dependency cmdq_peek");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ext_func_tab_from_func),const struct ext_func_tab * (*)(int (*)(void))),"HACK dependency ext_func_tab_from_func");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dokick),int (*)(void)),"HACK dependency dokick");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_cant),void (*)(const char *,...)),"HACK dependency You_cant");
_Static_assert(__builtin_types_compatible_p(__typeof__(&block_door),boolean (*)(coordxy,coordxy)),"HACK dependency block_door");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Your),void (*)(const char *,...)),"HACK dependency Your");
_Static_assert(__builtin_types_compatible_p(__typeof__(&worm_cross),boolean (*)(int,int,int,int)),"HACK dependency worm_cross");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool_or_lava),boolean (*)(coordxy,coordxy)),"HACK dependency is_pool_or_lava");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool),boolean (*)(coordxy,coordxy)),"HACK dependency is_pool");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_lava),boolean (*)(coordxy,coordxy)),"HACK dependency is_lava");
_Static_assert(__builtin_types_compatible_p(__typeof__(&block_entry),boolean (*)(coordxy,coordxy)),"HACK dependency block_entry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&selection_new),struct selectionvar * (*)(void)),"HACK dependency selection_new");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy,coordxy,coordxy,coordxy)),"HACK dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&selection_getpoint),coordxy (*)(coordxy,coordxy,struct selectionvar *)),"HACK dependency selection_getpoint");
_Static_assert(__builtin_types_compatible_p(__typeof__(&selection_setpoint),void (*)(coordxy,coordxy,struct selectionvar *,int)),"HACK dependency selection_setpoint");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tmp_at),void (*)(coordxy,coordxy)),"HACK dependency tmp_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&distmin),int (*)(coordxy,coordxy,coordxy,coordxy)),"HACK dependency distmin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sgn),int (*)(int)),"HACK dependency sgn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&climb_pit),void (*)(void)),"HACK dependency climb_pit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_art),boolean (*)(struct obj *,int)),"HACK dependency is_art");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hliquid),const char * (*)(const char *)),"HACK dependency hliquid");
_Static_assert(__builtin_types_compatible_p(__typeof__(&buried_ball),struct obj * (*)(coord *)),"HACK dependency buried_ball");
_Static_assert(__builtin_types_compatible_p(__typeof__(&buried_ball_to_punishment),void (*)(void)),"HACK dependency buried_ball_to_punishment");
_Static_assert(__builtin_types_compatible_p(__typeof__(&impossible),void (*)(const char *,...)),"HACK dependency impossible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_msg_xy),void (*)(coordxy,coordxy)),"HACK dependency set_msg_xy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&x_monnam),char * (*)(struct monst *,int,const char *,int,boolean)),"HACK dependency x_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&alloc),long * (*)(unsigned int)),"HACK dependency alloc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_deterministic_qsort),void (*)(void *,size_t,size_t,int (*)(const void *, const void *))),"HACK dependency nh_deterministic_qsort");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free),void (*)(void *)),"HACK dependency free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&peek_timer),long (*)(short,union any *)),"HACK dependency peek_timer");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stop_timer),long (*)(short,union any *)),"HACK dependency stop_timer");
_Static_assert(__builtin_types_compatible_p(__typeof__(&start_timer),boolean (*)(long,short,short,union any *)),"HACK dependency start_timer");
_Static_assert(__builtin_types_compatible_p(__typeof__(&highc),char (*)(char)),"HACK dependency highc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&locomotion),const char * (*)(const struct permonst *,const char *)),"HACK dependency locomotion");
_Static_assert(__builtin_types_compatible_p(__typeof__(&has_ceiling),boolean (*)(d_level *)),"HACK dependency has_ceiling");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_waterwall),boolean (*)(coordxy,coordxy)),"HACK dependency is_waterwall");
_Static_assert(__builtin_types_compatible_p(__typeof__(&visctrl),char * (*)(char)),"HACK dependency visctrl");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cmd_from_func),char (*)(int (*)(void))),"HACK dependency cmd_from_func");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_reqmenu),int (*)(void)),"HACK dependency do_reqmenu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&l_nhcore_call),void (*)(int)),"HACK dependency l_nhcore_call");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ing_suffix),char * (*)(const char *)),"HACK dependency ing_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&waterbody_name),const char * (*)(coordxy,coordxy)),"HACK dependency waterbody_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stumble_onto_mimic),void (*)(struct monst *)),"HACK dependency stumble_onto_mimic");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_monnam),char * (*)(struct monst *)),"HACK dependency m_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_nam),char * (*)(struct monst *)),"HACK dependency mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_safemon),int (*)(struct monst *)),"HACK dependency is_safemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_attack),boolean (*)(struct monst *)),"HACK dependency do_attack");
_Static_assert(__builtin_types_compatible_p(__typeof__(&breaktest),boolean (*)(struct obj *)),"HACK dependency breaktest");
_Static_assert(__builtin_types_compatible_p(__typeof__(&splitobj),struct obj * (*)(struct obj *,long)),"HACK dependency splitobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setuwep),void (*)(struct obj *)),"HACK dependency setuwep");
_Static_assert(__builtin_types_compatible_p(__typeof__(&freeinv),void (*)(struct obj *)),"HACK dependency freeinv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hit_bars),void (*)(struct obj **,coordxy,coordxy,coordxy,coordxy,unsigned int)),"HACK dependency hit_bars");
_Static_assert(__builtin_types_compatible_p(__typeof__(&uwep_skill_type),int (*)(void)),"HACK dependency uwep_skill_type");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacks),boolean (*)(int,struct obj *)),"HACK dependency attacks");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bare_artifactname),char * (*)(struct obj *)),"HACK dependency bare_artifactname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&weapon_descr),const char * (*)(struct obj *)),"HACK dependency weapon_descr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *,const char *)),"HACK dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmpi),int (*)(const char *,const char *,int)),"HACK dependency strncmpi");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makeplural),char * (*)(const char *)),"HACK dependency makeplural");
_Static_assert(__builtin_types_compatible_p(__typeof__(&__assert_fail),void (*)(const char *,const char *,int,const char *)),"HACK dependency __assert_fail");
_Static_assert(__builtin_types_compatible_p(__typeof__(&use_skill),void (*)(int,int)),"HACK dependency use_skill");
_Static_assert(__builtin_types_compatible_p(__typeof__(&seemimic),void (*)(struct monst *)),"HACK dependency seemimic");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trapname),const char * (*)(int,boolean)),"HACK dependency trapname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&just_an),char * (*)(char *,const char *)),"HACK dependency just_an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&place_monster),void (*)(struct monst *,coordxy,coordxy)),"HACK dependency place_monster");
_Static_assert(__builtin_types_compatible_p(__typeof__(&minliquid),int (*)(struct monst *)),"HACK dependency minliquid");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mintrap),int (*)(struct monst *,unsigned int)),"HACK dependency mintrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&abuse_dog),void (*)(struct monst *)),"HACK dependency abuse_dog");
_Static_assert(__builtin_types_compatible_p(__typeof__(&adjalign),void (*)(int)),"HACK dependency adjalign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&experience),int (*)(struct monst *,int)),"HACK dependency experience");
_Static_assert(__builtin_types_compatible_p(__typeof__(&more_experienced),void (*)(int,int)),"HACK dependency more_experienced");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newexplevel),void (*)(void)),"HACK dependency newexplevel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You_feel),void (*)(const char *,...)),"HACK dependency You_feel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype),boolean (*)(struct permonst *,int)),"HACK dependency attacktype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&accessible),boolean (*)(coordxy,coordxy)),"HACK dependency accessible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dig_typ),int (*)(struct obj *,coordxy,coordxy)),"HACK dependency dig_typ");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ansimpleoname),char * (*)(struct obj *)),"HACK dependency ansimpleoname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype_fordmg),struct attack * (*)(struct permonst *,int,int)),"HACK dependency attacktype_fordmg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wake_nearto),void (*)(coordxy,coordxy,int)),"HACK dependency wake_nearto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&explum),int (*)(struct monst *,struct attack *)),"HACK dependency explum");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rehumanize),void (*)(void)),"HACK dependency rehumanize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&water_friction),void (*)(void)),"HACK dependency water_friction");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_ice),boolean (*)(coordxy,coordxy)),"HACK dependency is_ice");
_Static_assert(__builtin_types_compatible_p(__typeof__(&objdescr_is),boolean (*)(struct obj *,const char *)),"HACK dependency objdescr_is");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Resists_Elem),boolean (*)(struct monst *,int)),"HACK dependency Resists_Elem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&confdir),void (*)(boolean)),"HACK dependency confdir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&visible_region_at),NhRegion * (*)(coordxy,coordxy)),"HACK dependency visible_region_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reg_damg),int (*)(NhRegion *)),"HACK dependency reg_damg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_snprintf),void (*)(const char *,int,char *,size_t,const char *,...)),"HACK dependency nh_snprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&paranoid_query),boolean (*)(boolean,const char *)),"HACK dependency paranoid_query");
_Static_assert(__builtin_types_compatible_p(__typeof__(&immune_to_trap),int (*)(struct monst *,unsigned int)),"HACK dependency immune_to_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&into_vs_onto),boolean (*)(int)),"HACK dependency into_vs_onto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&directionname),const char * (*)(int)),"HACK dependency directionname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_ustuck),void (*)(struct monst *)),"HACK dependency set_ustuck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sticks),boolean (*)(struct permonst *)),"HACK dependency sticks");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maybe_adjust_hero_bubble),void (*)(void)),"HACK dependency maybe_adjust_hero_bubble");
_Static_assert(__builtin_types_compatible_p(__typeof__(&u_on_newpos),void (*)(coordxy,coordxy)),"HACK dependency u_on_newpos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_visible),int (*)(struct monst *)),"HACK dependency mon_visible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unmap_invisible),boolean (*)(coordxy,coordxy)),"HACK dependency unmap_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stucksteed),boolean (*)(boolean)),"HACK dependency stucksteed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reset_utrap),void (*)(boolean)),"HACK dependency reset_utrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&drag_ball),boolean (*)(coordxy,coordxy,int *,coordxy *,coordxy *,coordxy *,coordxy *,boolean *,boolean)),"HACK dependency drag_ball");
_Static_assert(__builtin_types_compatible_p(__typeof__(&in_out_region),boolean (*)(coordxy,coordxy)),"HACK dependency in_out_region");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_postmove_effect),void (*)(struct monst *)),"HACK dependency m_postmove_effect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exercise_steed),void (*)(void)),"HACK dependency exercise_steed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reset_occupations),void (*)(void)),"HACK dependency reset_occupations");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hideunder),boolean (*)(struct monst *)),"HACK dependency hideunder");
_Static_assert(__builtin_types_compatible_p(__typeof__(&check_leash),void (*)(coordxy,coordxy)),"HACK dependency check_leash");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vision_recalc),void (*)(int)),"HACK dependency vision_recalc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&move_bc),void (*)(int,int,coordxy,coordxy,coordxy,coordxy)),"HACK dependency move_bc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&curs_on_u),void (*)(void)),"HACK dependency curs_on_u");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_reach_floor),boolean (*)(boolean)),"HACK dependency can_reach_floor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&engr_at),struct engr * (*)(coordxy,coordxy)),"HACK dependency engr_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wipe_engr_at),void (*)(coordxy,coordxy,xint16,boolean)),"HACK dependency wipe_engr_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fall_asleep),void (*)(int,boolean)),"HACK dependency fall_asleep");
_Static_assert(__builtin_types_compatible_p(__typeof__(&gethungry),void (*)(void)),"HACK dependency gethungry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&On_stairs),boolean (*)(coordxy,coordxy)),"HACK dependency On_stairs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&body_part),const char * (*)(int)),"HACK dependency body_part");
_Static_assert(__builtin_types_compatible_p(__typeof__(&db_under_typ),schar (*)(int)),"HACK dependency db_under_typ");
_Static_assert(__builtin_types_compatible_p(__typeof__(&float_up),void (*)(void)),"HACK dependency float_up");
_Static_assert(__builtin_types_compatible_p(__typeof__(&back_on_ground),void (*)(boolean)),"HACK dependency back_on_ground");
_Static_assert(__builtin_types_compatible_p(__typeof__(&docrt),void (*)(void)),"HACK dependency docrt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dismount_steed),void (*)(int)),"HACK dependency dismount_steed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lava_effects),boolean (*)(void)),"HACK dependency lava_effects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&drown),boolean (*)(void)),"HACK dependency drown");
_Static_assert(__builtin_types_compatible_p(__typeof__(&incr_itimeout),void (*)(long *,int)),"HACK dependency incr_itimeout");
_Static_assert(__builtin_types_compatible_p(__typeof__(&float_down),int (*)(long,long)),"HACK dependency float_down");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pickup),int (*)(int)),"HACK dependency pickup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dotrap),void (*)(struct trap *,unsigned int)),"HACK dependency dotrap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spot_time_left),long (*)(coordxy,coordxy,short)),"HACK dependency spot_time_left");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Amonnam),char * (*)(struct monst *)),"HACK dependency Amonnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ceiling),const char * (*)(coordxy,coordxy)),"HACK dependency ceiling");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hard_helmet),boolean (*)(struct obj *)),"HACK dependency hard_helmet");
_Static_assert(__builtin_types_compatible_p(__typeof__(&helm_simple_name),const char * (*)(struct obj *)),"HACK dependency helm_simple_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&d),int (*)(int,int)),"HACK dependency d");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mdamageu),void (*)(struct monst *,int)),"HACK dependency mdamageu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mnexto),void (*)(struct monst *,unsigned int)),"HACK dependency mnexto");
_Static_assert(__builtin_types_compatible_p(__typeof__(&inside_room),boolean (*)(struct mkroom *,coordxy,coordxy)),"HACK dependency inside_room");
_Static_assert(__builtin_types_compatible_p(__typeof__(&u_left_shop),void (*)(char *,boolean)),"HACK dependency u_left_shop");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_mines),boolean (*)(d_level *)),"HACK dependency In_mines");
_Static_assert(__builtin_types_compatible_p(__typeof__(&record_achievement),void (*)(schar)),"HACK dependency record_achievement");
_Static_assert(__builtin_types_compatible_p(__typeof__(&u_entered_shop),void (*)(char *)),"HACK dependency u_entered_shop");
_Static_assert(__builtin_types_compatible_p(__typeof__(&midnight),int (*)(void)),"HACK dependency midnight");
_Static_assert(__builtin_types_compatible_p(__typeof__(&verbalize),void (*)(const char *,...)),"HACK dependency verbalize");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Hello),const char * (*)(struct monst *)),"HACK dependency Hello");
_Static_assert(__builtin_types_compatible_p(__typeof__(&intemple),void (*)(int)),"HACK dependency intemple");
_Static_assert(__builtin_types_compatible_p(__typeof__(&room_discovered),void (*)(int)),"HACK dependency room_discovered");
_Static_assert(__builtin_types_compatible_p(__typeof__(&search_special),struct mkroom * (*)(schar)),"HACK dependency search_special");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wake_msg),void (*)(struct monst *,boolean)),"HACK dependency wake_msg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmgtype_fromattack),struct attack * (*)(struct permonst *,int,int)),"HACK dependency dmgtype_fromattack");
_Static_assert(__builtin_types_compatible_p(__typeof__(&s_suffix),char * (*)(const char *)),"HACK dependency s_suffix");
_Static_assert(__builtin_types_compatible_p(__typeof__(&uteetering_at_seen_pit),boolean (*)(struct trap *)),"HACK dependency uteetering_at_seen_pit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rider_cant_reach),void (*)(void)),"HACK dependency rider_cant_reach");
_Static_assert(__builtin_types_compatible_p(__typeof__(&loot_mon),int (*)(struct monst *,int *,boolean *)),"HACK dependency loot_mon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline_xy),void (*)(coordxy,coordxy,const char *,...)),"HACK dependency pline_xy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&noattacks),boolean (*)(struct permonst *)),"HACK dependency noattacks");
_Static_assert(__builtin_types_compatible_p(__typeof__(&onscary),boolean (*)(coordxy,coordxy,struct monst *)),"HACK dependency onscary");
_Static_assert(__builtin_types_compatible_p(__typeof__(&selection_free),void (*)(struct selectionvar *,boolean)),"HACK dependency selection_free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cmdq_clear),void (*)(int)),"HACK dependency cmdq_clear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pmname),const char * (*)(struct permonst *,int)),"HACK dependency pmname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&urgent_pline),void (*)(const char *,...)),"HACK dependency urgent_pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done),void (*)(int)),"HACK dependency done");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Boots_on),int (*)(void)),"HACK dependency Boots_on");
_Static_assert(__builtin_types_compatible_p(__typeof__(&decl_globals_init),void (*)(void)),"HACK dependency decl_globals_init");
_Static_assert(__builtin_types_compatible_p(__typeof__(&init_objects),void (*)(void)),"HACK dependency init_objects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&CapitalMon),boolean (*)(const char *)),"HACK dependency CapitalMon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dupstr),char * (*)(const char *)),"HACK dependency dupstr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&simple_typename),char * (*)(int)),"HACK dependency simple_typename");
_Static_assert(__builtin_types_compatible_p(__typeof__(&raw_printf),void (*)(const char *,...)),"HACK dependency raw_printf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&freedynamicdata),void (*)(void)),"HACK dependency freedynamicdata");
_Static_assert(__builtin_types_compatible_p(__typeof__(&spot_stop_timers),void (*)(coordxy,coordxy,short)),"HACK dependency spot_stop_timers");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obj_ice_effects),void (*)(coordxy,coordxy,boolean)),"HACK dependency obj_ice_effects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&panic),void (*)(const char *,...)),"HACK dependency panic");
