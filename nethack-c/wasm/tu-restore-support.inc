/* RESTORE typed fields, globals, callbacks and dependency transport; no restoration policy. */
#include "hack.h"
#include "tu-restore-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
void *teleport_restore_global(int index){switch(index){
case 0:return (void*)&flags;
case 1:return (void*)&iflags;
case 2:return (void*)&mons;
case 3:return (void*)&nul_glyphinfo;
case 4:return (void*)&restoreinfo;
case 5:return (void*)&uwep;
case 6:return (void*)&uchain;
case 7:return (void*)&uball;
case 8:return (void*)&u;
case 9:return (void*)&ubirthday;
case 10:return (void*)&urealtime;
case 11:return (void*)&WIN_MESSAGE;
case 12:return (void*)&gb;
case 13:return (void*)&gc;
case 14:return (void*)&gd;
case 15:return (void*)&ge;
case 16:return (void*)&gf;
case 17:return (void*)&gh;
case 18:return (void*)&gi;
case 19:return (void*)&gm;
case 20:return (void*)&gn;
case 21:return (void*)&go;
case 22:return (void*)&gs;
case 23:return (void*)&gu;
case 24:return (void*)&gv;
case 25:return (void*)&gy;
case 26:return (void*)&svc;
case 27:return (void*)&svd;
case 28:return (void*)&svk;
case 29:return (void*)&svl;
case 30:return (void*)&svm;
case 31:return (void*)&svn;
case 32:return (void*)&svo;
case 33:return (void*)&svp;
case 34:return (void*)&svq;
case 35:return (void*)&svr;
case 36:return (void*)&svs;
case 37:return (void*)&svu;
case 38:return (void*)&svw;
case 39:return (void*)&program_state;
case 40:return (void*)&cg;
case 41:return (void*)&sysopt;
case 42:return (void*)&windowprocs;
default:abort();}}
uint64_t teleport_restore_read(int kind,void*at,int field){switch(kind){
case 0:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nmon);
case 1:return (uint64_t)(uintptr_t)(p->data);
case 2:return (uint64_t)(uintptr_t)(p->m_id);
case 3:return (uint64_t)(uintptr_t)(p->mnum);
case 4:return (uint64_t)(uintptr_t)(p->cham);
case 5:return (uint64_t)(uintptr_t)(p->mx);
case 6:return (uint64_t)(uintptr_t)(p->my);
case 7:return (uint64_t)(uintptr_t)(p->mhpmax);
case 8:return (uint64_t)(uintptr_t)(p->mtame);
case 9:return (uint64_t)(uintptr_t)(p->mundetected);
case 10:return (uint64_t)(uintptr_t)(p->mpeaceful);
case 11:return (uint64_t)(uintptr_t)(p->isshk);
case 12:return (uint64_t)(uintptr_t)(p->ispriest);
case 13:return (uint64_t)(uintptr_t)(p->wormno);
case 14:return (uint64_t)(uintptr_t)(p->minvent);
case 15:return (uint64_t)(uintptr_t)(p->mw);
case 16:return (uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 1:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->pmidx);
case 1:return (uint64_t)(uintptr_t)(p->mlet);
case 2:return (uint64_t)(uintptr_t)(p->maligntyp);
case 3:return (uint64_t)(uintptr_t)(p->mflags1);
case 4:return (uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 2:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nobj);
case 1:return (uint64_t)(uintptr_t)(&p->v);
case 2:return (uint64_t)(uintptr_t)(p->cobj);
case 3:return (uint64_t)(uintptr_t)(p->o_id);
case 4:return (uint64_t)(uintptr_t)(p->ox);
case 5:return (uint64_t)(uintptr_t)(p->oy);
case 6:return (uint64_t)(uintptr_t)(p->otyp);
case 7:return (uint64_t)(uintptr_t)(p->spe);
case 8:return (uint64_t)(uintptr_t)(p->where);
case 9:return (uint64_t)(uintptr_t)(p->in_use);
case 10:return (uint64_t)(uintptr_t)(p->bypass);
case 11:return (uint64_t)(uintptr_t)(p->age);
case 12:return (uint64_t)(uintptr_t)(p->owornmask);
case 13:return (uint64_t)(uintptr_t)(p->lua_ref_cnt);
case 14:return (uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 3:{union vptrs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->v_nexthere);
case 1:return (uint64_t)(uintptr_t)(p->v_ocontainer);
case 2:return (uint64_t)(uintptr_t)(p->v_ocarry);
default:abort();}}
case 4:{struct oextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oname);
case 1:return (uint64_t)(uintptr_t)(p->omonst);
case 2:return (uint64_t)(uintptr_t)(p->omid);
default:abort();}}
case 5:{struct mextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mgivenname);
case 1:return (uint64_t)(uintptr_t)(p->egd);
case 2:return (uint64_t)(uintptr_t)(p->epri);
case 3:return (uint64_t)(uintptr_t)(p->eshk);
case 4:return (uint64_t)(uintptr_t)(p->emin);
case 5:return (uint64_t)(uintptr_t)(p->edog);
case 6:return (uint64_t)(uintptr_t)(p->ebones);
case 7:return (uint64_t)(uintptr_t)(p->mcorpsenm);
default:abort();}}
case 6:{struct egd*p=at;switch(field){
default:abort();}}
case 7:{struct epri*p=at;switch(field){
default:abort();}}
case 8:{struct eshk*p=at;switch(field){
default:abort();}}
case 9:{struct emin*p=at;switch(field){
default:abort();}}
case 10:{struct edog*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->droptime);
case 1:return (uint64_t)(uintptr_t)(p->apport);
case 2:return (uint64_t)(uintptr_t)(p->hungrytime);
default:abort();}}
case 11:{struct ebones*p=at;switch(field){
default:abort();}}
case 12:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_rogue_level);
case 1:return (uint64_t)(uintptr_t)(&p->d_medusa_level);
case 2:return (uint64_t)(uintptr_t)(&p->d_stronghold_level);
case 3:return (uint64_t)(uintptr_t)(&p->d_wiz1_level);
default:abort();}}
case 13:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 14:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 1:return (uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 2:return (uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 3:return (uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 4:return (uint64_t)(uintptr_t)(p->win_putstr);
case 5:return (uint64_t)(uintptr_t)(p->win_start_menu);
case 6:return (uint64_t)(uintptr_t)(p->win_end_menu);
case 7:return (uint64_t)(uintptr_t)(p->win_wait_synch);
case 8:return (uint64_t)(uintptr_t)(p->win_cliparound);
case 9:return (uint64_t)(uintptr_t)(p->win_putmsghistory);
default:abort();}}
case 15:{struct instance_globals_o*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oldfruit);
default:abort();}}
case 16:{struct fruit*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->fname);
case 1:return (uint64_t)(uintptr_t)(p->fid);
case 2:return (uint64_t)(uintptr_t)(p->nextf);
default:abort();}}
case 17:{struct mi*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 18:{union any*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->a_int);
default:abort();}}
case 19:{struct damage*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
case 1:return (uint64_t)(uintptr_t)(p->when);
default:abort();}}
case 20:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->something_worth_saving);
case 1:return (uint64_t)(uintptr_t)(p->restoring);
case 2:return (uint64_t)(uintptr_t)(p->in_getlev);
case 3:return (uint64_t)(uintptr_t)(p->beyond_savefile_load);
default:abort();}}
case 21:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->locations);
case 1:return (uint64_t)(uintptr_t)(&p->objects);
case 2:return (uint64_t)(uintptr_t)(&p->monsters);
case 3:return (uint64_t)(uintptr_t)(p->objlist);
case 4:return (uint64_t)(uintptr_t)(p->buriedobjlist);
case 5:return (uint64_t)(uintptr_t)(p->monlist);
case 6:return (uint64_t)(uintptr_t)(p->damagelist);
case 7:return (uint64_t)(uintptr_t)(p->bonesinfo);
case 8:return (uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 22:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->typ);
default:abort();}}
case 23:{struct cemetery*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 24:{struct levelflags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->stasis_until);
default:abort();}}
case 25:{struct instance_globals_saved_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->spl_book);
case 1:return (uint64_t)(uintptr_t)(p->sp_levchn);
default:abort();}}
case 26:{struct spell*p=at;switch(field){
default:abort();}}
case 27:{struct s_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 28:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->nhuuid);
case 1:return (uint64_t)(uintptr_t)(p->nroom);
default:abort();}}
case 29:{struct instance_globals_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->converted_savefile_loaded);
default:abort();}}
case 30:{struct nh_file*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->fd);
case 1:return (uint64_t)(uintptr_t)(p->mode);
case 2:return (uint64_t)(uintptr_t)(p->ftype);
case 3:return (uint64_t)(uintptr_t)(p->eof);
default:abort();}}
case 31:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
case 1:return (uint64_t)(uintptr_t)(p->id_map);
default:abort();}}
case 32:{struct teleport_restore_bucket*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
case 1:return (uint64_t)(uintptr_t)(&p->map);
default:abort();}}
case 33:{__typeof__(((struct teleport_restore_bucket*)0)->map[0])*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->gid);
case 1:return (uint64_t)(uintptr_t)(p->nid);
default:abort();}}
case 34:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 35:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->unweapon);
default:abort();}}
case 36:{struct stairway*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->sx);
case 1:return (uint64_t)(uintptr_t)(p->sy);
case 2:return (uint64_t)(uintptr_t)(&p->tolev);
case 3:return (uint64_t)(uintptr_t)(p->up);
case 4:return (uint64_t)(uintptr_t)(p->isladder);
case 5:return (uint64_t)(uintptr_t)(p->u_traversed);
case 6:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 37:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->seer_turn);
case 1:return (uint64_t)(uintptr_t)(&p->digging);
case 2:return (uint64_t)(uintptr_t)(&p->victual);
case 3:return (uint64_t)(uintptr_t)(&p->tin);
case 4:return (uint64_t)(uintptr_t)(&p->spbook);
case 5:return (uint64_t)(uintptr_t)(&p->warntype);
case 6:return (uint64_t)(uintptr_t)(&p->polearm);
default:abort();}}
case 38:{struct dig_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->lastdigtime);
default:abort();}}
case 39:{struct victual_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->piece);
case 1:return (uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 40:{struct tin_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->tin);
case 1:return (uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 41:{struct book_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->book);
case 1:return (uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 42:{struct warntype_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->species);
case 1:return (uint64_t)(uintptr_t)(p->speciesidx);
default:abort();}}
case 43:{struct polearm_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hitmon);
case 1:return (uint64_t)(uintptr_t)(p->m_id);
default:abort();}}
case 44:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->n_ids_mapped);
default:abort();}}
case 45:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->updest);
default:abort();}}
case 46:{struct dest_area*p=at;switch(field){
default:abort();}}
case 47:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
case 1:return (uint64_t)(uintptr_t)(&p->dndest);
case 2:return (uint64_t)(uintptr_t)(p->doors);
case 3:return (uint64_t)(uintptr_t)(p->doors_alloc);
default:abort();}}
case 48:{struct nhcoord*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->x);
case 1:return (uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 49:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ntrap);
case 1:return (uint64_t)(uintptr_t)(p->tx);
case 2:return (uint64_t)(uintptr_t)(&p->dst);
case 3:return (uint64_t)(uintptr_t)(p->ttyp);
default:abort();}}
case 50:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->migrating_objs);
case 1:return (uint64_t)(uintptr_t)(p->migrating_mons);
default:abort();}}
case 51:{struct u_realtime*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->realtime);
case 1:return (uint64_t)(uintptr_t)(p->start_timing);
default:abort();}}
case 52:{struct instance_globals_f*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ftrap);
case 1:return (uint64_t)(uintptr_t)(p->ffruit);
default:abort();}}
case 53:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(&p->uz);
case 3:return (uint64_t)(uintptr_t)(&p->uz0);
case 4:return (uint64_t)(uintptr_t)(p->umonster);
case 5:return (uint64_t)(uintptr_t)(p->umonnum);
case 6:return (uint64_t)(uintptr_t)(p->mh);
case 7:return (uint64_t)(uintptr_t)(&p->ualign);
case 8:return (uint64_t)(uintptr_t)(p->uhp);
case 9:return (uint64_t)(uintptr_t)(p->ustuck);
case 10:return (uint64_t)(uintptr_t)(p->usteed);
case 11:return (uint64_t)(uintptr_t)(p->ustuck_mid);
case 12:return (uint64_t)(uintptr_t)(p->usteed_mid);
case 13:return (uint64_t)(uintptr_t)(p->mcham);
default:abort();}}
case 54:{struct align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
case 1:return (uint64_t)(uintptr_t)(p->abuse);
default:abort();}}
case 55:{struct instance_globals_e*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->early_raw_messages);
default:abort();}}
case 56:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->last_msg);
case 1:return (uint64_t)(uintptr_t)(p->deferred_X);
case 2:return (uint64_t)(uintptr_t)(p->perm_invent);
case 3:return (uint64_t)(uintptr_t)(p->explore_error_flag);
default:abort();}}
case 57:{struct mkroom*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->doorct);
case 1:return (uint64_t)(uintptr_t)(p->fdoor);
default:abort();}}
case 58:{struct branch*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
case 1:return (uint64_t)(uintptr_t)(&p->end1);
case 2:return (uint64_t)(uintptr_t)(&p->end2);
default:abort();}}
case 59:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 60:{struct const_globals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->zeromonst);
case 1:return (uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 61:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 62:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 63:{struct instance_globals_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->doorindex);
case 1:return (uint64_t)(uintptr_t)(p->defer_see_monsters);
default:abort();}}
case 64:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->stairs);
default:abort();}}
case 65:{struct sysopt_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->check_save_uid);
default:abort();}}
case 66:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->debug);
case 1:return (uint64_t)(uintptr_t)(p->explore);
default:abort();}}
case 67:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->billobjs);
default:abort();}}
case 68:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->quest_status);
default:abort();}}
case 69:{struct q_score*p=at;switch(field){
default:abort();}}
case 70:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 71:{struct kinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 72:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->plname);
case 1:return (uint64_t)(uintptr_t)(&p->pl_character);
case 2:return (uint64_t)(uintptr_t)(&p->pl_fruit);
default:abort();}}
case 73:{struct restore_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mread_flags);
default:abort();}}
case 74:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->lastseentyp);
case 1:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 75:{struct instance_globals_saved_w*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wreserve);
case 1:return (uint64_t)(uintptr_t)(p->wtreserved);
default:abort();}}
case 76:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
case 1:return (uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 77:{struct mvitals*p=at;switch(field){
default:abort();}}
case 78:{struct instance_globals_h*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hero_seq);
default:abort();}}
case 79:{struct gamelog_line*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->turn);
case 1:return (uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 80:{struct instance_globals_saved_o*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->omoves);
default:abort();}}
case 81:{struct glyphinfo*p=at;switch(field){
default:abort();}}
default:abort();}}
void teleport_restore_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct monst*p=at;switch(field){
case 0:p->nmon=(void*)(uintptr_t)value;return;
case 1:p->data=(void*)(uintptr_t)value;return;
case 2:p->m_id=value;return;
case 3:p->mnum=value;return;
case 4:p->cham=value;return;
case 5:p->mx=value;return;
case 6:p->my=value;return;
case 7:p->mhpmax=value;return;
case 8:p->mtame=value;return;
case 9:p->mundetected=value;return;
case 10:p->mpeaceful=value;return;
case 11:p->isshk=value;return;
case 12:p->ispriest=value;return;
case 13:p->wormno=value;return;
case 14:p->minvent=(void*)(uintptr_t)value;return;
case 15:p->mw=(void*)(uintptr_t)value;return;
case 16:p->mextra=(void*)(uintptr_t)value;return;
default:abort();}}
case 1:{struct permonst*p=at;switch(field){
case 1:p->mlet=value;return;
case 2:p->maligntyp=value;return;
case 3:p->mflags1=value;return;
case 4:p->mflags2=value;return;
default:abort();}}
case 2:{struct obj*p=at;switch(field){
case 0:p->nobj=(void*)(uintptr_t)value;return;
case 1:memmove(&p->v, (void*)(uintptr_t)value,sizeof p->v);return;
case 2:p->cobj=(void*)(uintptr_t)value;return;
case 3:p->o_id=value;return;
case 4:p->ox=value;return;
case 5:p->oy=value;return;
case 6:p->otyp=value;return;
case 7:p->spe=value;return;
case 8:p->where=value;return;
case 9:p->in_use=value;return;
case 10:p->bypass=value;return;
case 11:p->age=value;return;
case 12:p->owornmask=value;return;
case 13:p->lua_ref_cnt=value;return;
case 14:p->oextra=(void*)(uintptr_t)value;return;
default:abort();}}
case 3:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(void*)(uintptr_t)value;return;
case 1:p->v_ocontainer=(void*)(uintptr_t)value;return;
case 2:p->v_ocarry=(void*)(uintptr_t)value;return;
default:abort();}}
case 4:{struct oextra*p=at;switch(field){
case 0:p->oname=(void*)(uintptr_t)value;return;
case 1:p->omonst=(void*)(uintptr_t)value;return;
case 2:p->omid=value;return;
default:abort();}}
case 5:{struct mextra*p=at;switch(field){
case 0:p->mgivenname=(void*)(uintptr_t)value;return;
case 1:p->egd=(void*)(uintptr_t)value;return;
case 2:p->epri=(void*)(uintptr_t)value;return;
case 3:p->eshk=(void*)(uintptr_t)value;return;
case 4:p->emin=(void*)(uintptr_t)value;return;
case 5:p->edog=(void*)(uintptr_t)value;return;
case 6:p->ebones=(void*)(uintptr_t)value;return;
case 7:p->mcorpsenm=value;return;
default:abort();}}
case 6:{struct egd*p=at;switch(field){
default:abort();}}
case 7:{struct epri*p=at;switch(field){
default:abort();}}
case 8:{struct eshk*p=at;switch(field){
default:abort();}}
case 9:{struct emin*p=at;switch(field){
default:abort();}}
case 10:{struct edog*p=at;switch(field){
case 0:p->droptime=value;return;
case 1:p->apport=value;return;
case 2:p->hungrytime=value;return;
default:abort();}}
case 11:{struct ebones*p=at;switch(field){
default:abort();}}
case 12:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_rogue_level, (void*)(uintptr_t)value,sizeof p->d_rogue_level);return;
case 1:memmove(&p->d_medusa_level, (void*)(uintptr_t)value,sizeof p->d_medusa_level);return;
case 2:memmove(&p->d_stronghold_level, (void*)(uintptr_t)value,sizeof p->d_stronghold_level);return;
case 3:memmove(&p->d_wiz1_level, (void*)(uintptr_t)value,sizeof p->d_wiz1_level);return;
default:abort();}}
case 13:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 14:{struct window_procs*p=at;switch(field){
case 0:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))(uintptr_t)value;return;
case 1:p->win_clear_nhwindow=(__typeof__(p->win_clear_nhwindow))(uintptr_t)value;return;
case 2:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))(uintptr_t)value;return;
case 3:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))(uintptr_t)value;return;
case 4:p->win_putstr=(__typeof__(p->win_putstr))(uintptr_t)value;return;
case 5:p->win_start_menu=(__typeof__(p->win_start_menu))(uintptr_t)value;return;
case 6:p->win_end_menu=(__typeof__(p->win_end_menu))(uintptr_t)value;return;
case 7:p->win_wait_synch=(__typeof__(p->win_wait_synch))(uintptr_t)value;return;
case 8:p->win_cliparound=(__typeof__(p->win_cliparound))(uintptr_t)value;return;
case 9:p->win_putmsghistory=(__typeof__(p->win_putmsghistory))(uintptr_t)value;return;
default:abort();}}
case 15:{struct instance_globals_o*p=at;switch(field){
case 0:p->oldfruit=(void*)(uintptr_t)value;return;
default:abort();}}
case 16:{struct fruit*p=at;switch(field){
case 1:p->fid=value;return;
case 2:p->nextf=(void*)(uintptr_t)value;return;
default:abort();}}
case 17:{struct mi*p=at;switch(field){
case 0:memmove(&p->item, (void*)(uintptr_t)value,sizeof p->item);return;
default:abort();}}
case 18:{union any*p=at;switch(field){
case 0:p->a_int=value;return;
default:abort();}}
case 19:{struct damage*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
case 1:p->when=value;return;
default:abort();}}
case 20:{struct sinfo*p=at;switch(field){
case 0:p->something_worth_saving=value;return;
case 1:p->restoring=value;return;
case 2:p->in_getlev=value;return;
case 3:p->beyond_savefile_load=value;return;
default:abort();}}
case 21:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(void*)(uintptr_t)value;return;
case 4:p->buriedobjlist=(void*)(uintptr_t)value;return;
case 5:p->monlist=(void*)(uintptr_t)value;return;
case 6:p->damagelist=(void*)(uintptr_t)value;return;
case 7:p->bonesinfo=(void*)(uintptr_t)value;return;
case 8:memmove(&p->flags, (void*)(uintptr_t)value,sizeof p->flags);return;
default:abort();}}
case 22:{struct rm*p=at;switch(field){
case 0:p->typ=value;return;
default:abort();}}
case 23:{struct cemetery*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 24:{struct levelflags*p=at;switch(field){
case 0:p->stasis_until=value;return;
default:abort();}}
case 25:{struct instance_globals_saved_s*p=at;switch(field){
case 1:p->sp_levchn=(void*)(uintptr_t)value;return;
default:abort();}}
case 26:{struct spell*p=at;switch(field){
default:abort();}}
case 27:{struct s_level*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 28:{struct instance_globals_saved_n*p=at;switch(field){
case 1:p->nroom=value;return;
default:abort();}}
case 29:{struct instance_globals_c*p=at;switch(field){
case 0:p->converted_savefile_loaded=value;return;
default:abort();}}
case 30:{struct nh_file*p=at;switch(field){
case 0:p->fd=value;return;
case 1:p->mode=value;return;
case 2:p->ftype=value;return;
case 3:p->eof=value;return;
default:abort();}}
case 31:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
case 1:p->id_map=(void*)(uintptr_t)value;return;
default:abort();}}
case 32:{struct teleport_restore_bucket*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 33:{__typeof__(((struct teleport_restore_bucket*)0)->map[0])*p=at;switch(field){
case 0:p->gid=value;return;
case 1:p->nid=value;return;
default:abort();}}
case 34:{struct instance_globals_v*p=at;switch(field){
case 0:p->vision_full_recalc=value;return;
default:abort();}}
case 35:{struct instance_globals_u*p=at;switch(field){
case 0:p->unweapon=value;return;
default:abort();}}
case 36:{struct stairway*p=at;switch(field){
case 0:p->sx=value;return;
case 1:p->sy=value;return;
case 2:memmove(&p->tolev, (void*)(uintptr_t)value,sizeof p->tolev);return;
case 3:p->up=value;return;
case 4:p->isladder=value;return;
case 5:p->u_traversed=value;return;
case 6:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 37:{struct context_info*p=at;switch(field){
case 0:p->seer_turn=value;return;
case 1:memmove(&p->digging, (void*)(uintptr_t)value,sizeof p->digging);return;
case 2:memmove(&p->victual, (void*)(uintptr_t)value,sizeof p->victual);return;
case 3:memmove(&p->tin, (void*)(uintptr_t)value,sizeof p->tin);return;
case 4:memmove(&p->spbook, (void*)(uintptr_t)value,sizeof p->spbook);return;
case 5:memmove(&p->warntype, (void*)(uintptr_t)value,sizeof p->warntype);return;
case 6:memmove(&p->polearm, (void*)(uintptr_t)value,sizeof p->polearm);return;
default:abort();}}
case 38:{struct dig_info*p=at;switch(field){
case 0:p->lastdigtime=value;return;
default:abort();}}
case 39:{struct victual_info*p=at;switch(field){
case 0:p->piece=(void*)(uintptr_t)value;return;
case 1:p->o_id=value;return;
default:abort();}}
case 40:{struct tin_info*p=at;switch(field){
case 0:p->tin=(void*)(uintptr_t)value;return;
case 1:p->o_id=value;return;
default:abort();}}
case 41:{struct book_info*p=at;switch(field){
case 0:p->book=(void*)(uintptr_t)value;return;
case 1:p->o_id=value;return;
default:abort();}}
case 42:{struct warntype_info*p=at;switch(field){
case 0:p->species=(void*)(uintptr_t)value;return;
case 1:p->speciesidx=value;return;
default:abort();}}
case 43:{struct polearm_info*p=at;switch(field){
case 0:p->hitmon=(void*)(uintptr_t)value;return;
case 1:p->m_id=value;return;
default:abort();}}
case 44:{struct instance_globals_n*p=at;switch(field){
case 0:p->n_ids_mapped=value;return;
default:abort();}}
case 45:{struct instance_globals_saved_u*p=at;switch(field){
case 0:memmove(&p->updest, (void*)(uintptr_t)value,sizeof p->updest);return;
default:abort();}}
case 46:{struct dest_area*p=at;switch(field){
default:abort();}}
case 47:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology, (void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
case 1:memmove(&p->dndest, (void*)(uintptr_t)value,sizeof p->dndest);return;
case 2:p->doors=(void*)(uintptr_t)value;return;
case 3:p->doors_alloc=value;return;
default:abort();}}
case 48:{struct nhcoord*p=at;switch(field){
case 0:p->x=value;return;
case 1:p->y=value;return;
default:abort();}}
case 49:{struct trap*p=at;switch(field){
case 0:p->ntrap=(void*)(uintptr_t)value;return;
case 1:p->tx=value;return;
case 2:memmove(&p->dst, (void*)(uintptr_t)value,sizeof p->dst);return;
case 3:p->ttyp=value;return;
default:abort();}}
case 50:{struct instance_globals_m*p=at;switch(field){
case 0:p->migrating_objs=(void*)(uintptr_t)value;return;
case 1:p->migrating_mons=(void*)(uintptr_t)value;return;
default:abort();}}
case 51:{struct u_realtime*p=at;switch(field){
case 0:p->realtime=value;return;
case 1:p->start_timing=value;return;
default:abort();}}
case 52:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(void*)(uintptr_t)value;return;
case 1:p->ffruit=(void*)(uintptr_t)value;return;
default:abort();}}
case 53:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:memmove(&p->uz, (void*)(uintptr_t)value,sizeof p->uz);return;
case 3:memmove(&p->uz0, (void*)(uintptr_t)value,sizeof p->uz0);return;
case 4:p->umonster=value;return;
case 5:p->umonnum=value;return;
case 6:p->mh=value;return;
case 7:memmove(&p->ualign, (void*)(uintptr_t)value,sizeof p->ualign);return;
case 8:p->uhp=value;return;
case 9:p->ustuck=(void*)(uintptr_t)value;return;
case 10:p->usteed=(void*)(uintptr_t)value;return;
case 11:p->ustuck_mid=value;return;
case 12:p->usteed_mid=value;return;
case 13:p->mcham=value;return;
default:abort();}}
case 54:{struct align*p=at;switch(field){
case 0:p->type=value;return;
case 1:p->abuse=value;return;
default:abort();}}
case 55:{struct instance_globals_e*p=at;switch(field){
case 0:p->early_raw_messages=value;return;
default:abort();}}
case 56:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=value;return;
case 1:p->deferred_X=value;return;
case 2:p->perm_invent=value;return;
case 3:p->explore_error_flag=value;return;
default:abort();}}
case 57:{struct mkroom*p=at;switch(field){
case 0:p->doorct=value;return;
case 1:p->fdoor=value;return;
default:abort();}}
case 58:{struct branch*p=at;switch(field){
case 0:p->type=value;return;
case 1:memmove(&p->end1, (void*)(uintptr_t)value,sizeof p->end1);return;
case 2:memmove(&p->end2, (void*)(uintptr_t)value,sizeof p->end2);return;
default:abort();}}
case 59:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 60:{struct const_globals*p=at;switch(field){
default:abort();}}
case 61:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst, (void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 62:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context, (void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 63:{struct instance_globals_d*p=at;switch(field){
case 0:p->doorindex=value;return;
case 1:p->defer_see_monsters=value;return;
default:abort();}}
case 64:{struct instance_globals_s*p=at;switch(field){
case 0:p->stairs=(void*)(uintptr_t)value;return;
default:abort();}}
case 65:{struct sysopt_s*p=at;switch(field){
case 0:p->check_save_uid=value;return;
default:abort();}}
case 66:{struct flag*p=at;switch(field){
case 0:p->debug=value;return;
case 1:p->explore=value;return;
default:abort();}}
case 67:{struct instance_globals_b*p=at;switch(field){
case 0:p->billobjs=(void*)(uintptr_t)value;return;
default:abort();}}
case 68:{struct instance_globals_saved_q*p=at;switch(field){
case 0:memmove(&p->quest_status, (void*)(uintptr_t)value,sizeof p->quest_status);return;
default:abort();}}
case 69:{struct q_score*p=at;switch(field){
default:abort();}}
case 70:{struct instance_globals_saved_k*p=at;switch(field){
case 0:memmove(&p->killer, (void*)(uintptr_t)value,sizeof p->killer);return;
default:abort();}}
case 71:{struct kinfo*p=at;switch(field){
default:abort();}}
case 72:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 73:{struct restore_info*p=at;switch(field){
case 0:p->mread_flags=value;return;
default:abort();}}
case 74:{struct instance_globals_saved_l*p=at;switch(field){
case 1:memmove(&p->level, (void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 75:{struct instance_globals_saved_w*p=at;switch(field){
case 0:p->wreserve=value;return;
case 1:p->wtreserved=value;return;
default:abort();}}
case 76:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 77:{struct mvitals*p=at;switch(field){
default:abort();}}
case 78:{struct instance_globals_h*p=at;switch(field){
case 0:p->hero_seq=value;return;
default:abort();}}
case 79:{struct gamelog_line*p=at;switch(field){
case 0:p->turn=value;return;
case 1:p->flags=value;return;
default:abort();}}
case 80:{struct instance_globals_saved_o*p=at;switch(field){
case 0:p->omoves=value;return;
default:abort();}}
case 81:{struct glyphinfo*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_restore_address(int kind,void*at,int field){switch(kind){
case 0:{struct monst*p=at;switch(field){
case 0:return (void*)&p->nmon;
case 1:return (void*)&p->data;
case 2:return (void*)&p->m_id;
case 3:return (void*)&p->mnum;
case 4:return (void*)&p->cham;
case 5:return (void*)&p->mx;
case 6:return (void*)&p->my;
case 7:return (void*)&p->mhpmax;
case 8:return (void*)&p->mtame;
case 14:return (void*)&p->minvent;
case 15:return (void*)&p->mw;
case 16:return (void*)&p->mextra;
default:abort();}}
case 1:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->pmidx;
case 1:return (void*)&p->mlet;
case 2:return (void*)&p->maligntyp;
case 3:return (void*)&p->mflags1;
case 4:return (void*)&p->mflags2;
default:abort();}}
case 2:{struct obj*p=at;switch(field){
case 0:return (void*)&p->nobj;
case 1:return (void*)&p->v;
case 2:return (void*)&p->cobj;
case 3:return (void*)&p->o_id;
case 4:return (void*)&p->ox;
case 5:return (void*)&p->oy;
case 6:return (void*)&p->otyp;
case 7:return (void*)&p->spe;
case 8:return (void*)&p->where;
case 11:return (void*)&p->age;
case 12:return (void*)&p->owornmask;
case 13:return (void*)&p->lua_ref_cnt;
case 14:return (void*)&p->oextra;
default:abort();}}
case 3:{union vptrs*p=at;switch(field){
case 0:return (void*)&p->v_nexthere;
case 1:return (void*)&p->v_ocontainer;
case 2:return (void*)&p->v_ocarry;
default:abort();}}
case 4:{struct oextra*p=at;switch(field){
case 0:return (void*)&p->oname;
case 1:return (void*)&p->omonst;
case 2:return (void*)&p->omid;
default:abort();}}
case 5:{struct mextra*p=at;switch(field){
case 0:return (void*)&p->mgivenname;
case 1:return (void*)&p->egd;
case 2:return (void*)&p->epri;
case 3:return (void*)&p->eshk;
case 4:return (void*)&p->emin;
case 5:return (void*)&p->edog;
case 6:return (void*)&p->ebones;
case 7:return (void*)&p->mcorpsenm;
default:abort();}}
case 6:{struct egd*p=at;switch(field){
default:abort();}}
case 7:{struct epri*p=at;switch(field){
default:abort();}}
case 8:{struct eshk*p=at;switch(field){
default:abort();}}
case 9:{struct emin*p=at;switch(field){
default:abort();}}
case 10:{struct edog*p=at;switch(field){
case 0:return (void*)&p->droptime;
case 1:return (void*)&p->apport;
case 2:return (void*)&p->hungrytime;
default:abort();}}
case 11:{struct ebones*p=at;switch(field){
default:abort();}}
case 12:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_rogue_level;
case 1:return (void*)&p->d_medusa_level;
case 2:return (void*)&p->d_stronghold_level;
case 3:return (void*)&p->d_wiz1_level;
default:abort();}}
case 13:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 14:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->win_create_nhwindow;
case 1:return (void*)&p->win_clear_nhwindow;
case 2:return (void*)&p->win_display_nhwindow;
case 3:return (void*)&p->win_destroy_nhwindow;
case 4:return (void*)&p->win_putstr;
case 5:return (void*)&p->win_start_menu;
case 6:return (void*)&p->win_end_menu;
case 7:return (void*)&p->win_wait_synch;
case 8:return (void*)&p->win_cliparound;
case 9:return (void*)&p->win_putmsghistory;
default:abort();}}
case 15:{struct instance_globals_o*p=at;switch(field){
case 0:return (void*)&p->oldfruit;
default:abort();}}
case 16:{struct fruit*p=at;switch(field){
case 0:return (void*)&p->fname;
case 1:return (void*)&p->fid;
case 2:return (void*)&p->nextf;
default:abort();}}
case 17:{struct mi*p=at;switch(field){
case 0:return (void*)&p->item;
default:abort();}}
case 18:{union any*p=at;switch(field){
case 0:return (void*)&p->a_int;
default:abort();}}
case 19:{struct damage*p=at;switch(field){
case 0:return (void*)&p->next;
case 1:return (void*)&p->when;
default:abort();}}
case 20:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->something_worth_saving;
case 1:return (void*)&p->restoring;
case 2:return (void*)&p->in_getlev;
case 3:return (void*)&p->beyond_savefile_load;
default:abort();}}
case 21:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->locations;
case 1:return (void*)&p->objects;
case 2:return (void*)&p->monsters;
case 3:return (void*)&p->objlist;
case 4:return (void*)&p->buriedobjlist;
case 5:return (void*)&p->monlist;
case 6:return (void*)&p->damagelist;
case 7:return (void*)&p->bonesinfo;
case 8:return (void*)&p->flags;
default:abort();}}
case 22:{struct rm*p=at;switch(field){
case 0:return (void*)&p->typ;
default:abort();}}
case 23:{struct cemetery*p=at;switch(field){
case 0:return (void*)&p->next;
default:abort();}}
case 24:{struct levelflags*p=at;switch(field){
case 0:return (void*)&p->stasis_until;
default:abort();}}
case 25:{struct instance_globals_saved_s*p=at;switch(field){
case 0:return (void*)&p->spl_book;
case 1:return (void*)&p->sp_levchn;
default:abort();}}
case 26:{struct spell*p=at;switch(field){
default:abort();}}
case 27:{struct s_level*p=at;switch(field){
case 0:return (void*)&p->next;
default:abort();}}
case 28:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (void*)&p->nhuuid;
case 1:return (void*)&p->nroom;
default:abort();}}
case 29:{struct instance_globals_c*p=at;switch(field){
case 0:return (void*)&p->converted_savefile_loaded;
default:abort();}}
case 30:{struct nh_file*p=at;switch(field){
case 0:return (void*)&p->fd;
case 1:return (void*)&p->mode;
case 2:return (void*)&p->ftype;
case 3:return (void*)&p->eof;
default:abort();}}
case 31:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
case 1:return (void*)&p->id_map;
default:abort();}}
case 32:{struct teleport_restore_bucket*p=at;switch(field){
case 0:return (void*)&p->next;
case 1:return (void*)&p->map;
default:abort();}}
case 33:{__typeof__(((struct teleport_restore_bucket*)0)->map[0])*p=at;switch(field){
case 0:return (void*)&p->gid;
case 1:return (void*)&p->nid;
default:abort();}}
case 34:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->vision_full_recalc;
default:abort();}}
case 35:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->unweapon;
default:abort();}}
case 36:{struct stairway*p=at;switch(field){
case 0:return (void*)&p->sx;
case 1:return (void*)&p->sy;
case 2:return (void*)&p->tolev;
case 3:return (void*)&p->up;
case 4:return (void*)&p->isladder;
case 5:return (void*)&p->u_traversed;
case 6:return (void*)&p->next;
default:abort();}}
case 37:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->seer_turn;
case 1:return (void*)&p->digging;
case 2:return (void*)&p->victual;
case 3:return (void*)&p->tin;
case 4:return (void*)&p->spbook;
case 5:return (void*)&p->warntype;
case 6:return (void*)&p->polearm;
default:abort();}}
case 38:{struct dig_info*p=at;switch(field){
case 0:return (void*)&p->lastdigtime;
default:abort();}}
case 39:{struct victual_info*p=at;switch(field){
case 0:return (void*)&p->piece;
case 1:return (void*)&p->o_id;
default:abort();}}
case 40:{struct tin_info*p=at;switch(field){
case 0:return (void*)&p->tin;
case 1:return (void*)&p->o_id;
default:abort();}}
case 41:{struct book_info*p=at;switch(field){
case 0:return (void*)&p->book;
case 1:return (void*)&p->o_id;
default:abort();}}
case 42:{struct warntype_info*p=at;switch(field){
case 0:return (void*)&p->species;
case 1:return (void*)&p->speciesidx;
default:abort();}}
case 43:{struct polearm_info*p=at;switch(field){
case 0:return (void*)&p->hitmon;
case 1:return (void*)&p->m_id;
default:abort();}}
case 44:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->n_ids_mapped;
default:abort();}}
case 45:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return (void*)&p->updest;
default:abort();}}
case 46:{struct dest_area*p=at;switch(field){
default:abort();}}
case 47:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
case 1:return (void*)&p->dndest;
case 2:return (void*)&p->doors;
case 3:return (void*)&p->doors_alloc;
default:abort();}}
case 48:{struct nhcoord*p=at;switch(field){
case 0:return (void*)&p->x;
case 1:return (void*)&p->y;
default:abort();}}
case 49:{struct trap*p=at;switch(field){
case 0:return (void*)&p->ntrap;
case 1:return (void*)&p->tx;
case 2:return (void*)&p->dst;
default:abort();}}
case 50:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->migrating_objs;
case 1:return (void*)&p->migrating_mons;
default:abort();}}
case 51:{struct u_realtime*p=at;switch(field){
case 0:return (void*)&p->realtime;
case 1:return (void*)&p->start_timing;
default:abort();}}
case 52:{struct instance_globals_f*p=at;switch(field){
case 0:return (void*)&p->ftrap;
case 1:return (void*)&p->ffruit;
default:abort();}}
case 53:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->uz;
case 3:return (void*)&p->uz0;
case 4:return (void*)&p->umonster;
case 5:return (void*)&p->umonnum;
case 6:return (void*)&p->mh;
case 7:return (void*)&p->ualign;
case 8:return (void*)&p->uhp;
case 9:return (void*)&p->ustuck;
case 10:return (void*)&p->usteed;
case 11:return (void*)&p->ustuck_mid;
case 12:return (void*)&p->usteed_mid;
case 13:return (void*)&p->mcham;
default:abort();}}
case 54:{struct align*p=at;switch(field){
case 0:return (void*)&p->type;
case 1:return (void*)&p->abuse;
default:abort();}}
case 55:{struct instance_globals_e*p=at;switch(field){
case 0:return (void*)&p->early_raw_messages;
default:abort();}}
case 56:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->last_msg;
case 1:return (void*)&p->deferred_X;
case 2:return (void*)&p->perm_invent;
case 3:return (void*)&p->explore_error_flag;
default:abort();}}
case 57:{struct mkroom*p=at;switch(field){
case 0:return (void*)&p->doorct;
case 1:return (void*)&p->fdoor;
default:abort();}}
case 58:{struct branch*p=at;switch(field){
case 0:return (void*)&p->type;
case 1:return (void*)&p->end1;
case 2:return (void*)&p->end2;
default:abort();}}
case 59:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (void*)&p->rooms;
default:abort();}}
case 60:{struct const_globals*p=at;switch(field){
case 0:return (void*)&p->zeromonst;
case 1:return (void*)&p->zeroany;
default:abort();}}
case 61:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 62:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 63:{struct instance_globals_d*p=at;switch(field){
case 0:return (void*)&p->doorindex;
case 1:return (void*)&p->defer_see_monsters;
default:abort();}}
case 64:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->stairs;
default:abort();}}
case 65:{struct sysopt_s*p=at;switch(field){
case 0:return (void*)&p->check_save_uid;
default:abort();}}
case 66:{struct flag*p=at;switch(field){
case 0:return (void*)&p->debug;
case 1:return (void*)&p->explore;
default:abort();}}
case 67:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->billobjs;
default:abort();}}
case 68:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (void*)&p->quest_status;
default:abort();}}
case 69:{struct q_score*p=at;switch(field){
default:abort();}}
case 70:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (void*)&p->killer;
default:abort();}}
case 71:{struct kinfo*p=at;switch(field){
case 0:return (void*)&p->name;
default:abort();}}
case 72:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (void*)&p->plname;
case 1:return (void*)&p->pl_character;
case 2:return (void*)&p->pl_fruit;
default:abort();}}
case 73:{struct restore_info*p=at;switch(field){
case 0:return (void*)&p->mread_flags;
default:abort();}}
case 74:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->lastseentyp;
case 1:return (void*)&p->level;
default:abort();}}
case 75:{struct instance_globals_saved_w*p=at;switch(field){
case 0:return (void*)&p->wreserve;
case 1:return (void*)&p->wtreserved;
default:abort();}}
case 76:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
case 1:return (void*)&p->mvitals;
default:abort();}}
case 77:{struct mvitals*p=at;switch(field){
default:abort();}}
case 78:{struct instance_globals_h*p=at;switch(field){
case 0:return (void*)&p->hero_seq;
default:abort();}}
case 79:{struct gamelog_line*p=at;switch(field){
case 0:return (void*)&p->turn;
case 1:return (void*)&p->flags;
default:abort();}}
case 80:{struct instance_globals_saved_o*p=at;switch(field){
case 0:return (void*)&p->omoves;
default:abort();}}
case 81:{struct glyphinfo*p=at;switch(field){
default:abort();}}
default:abort();}}
void*teleport_restore_literal(unsigned n){return malloc(n);}
void teleport_restore_message(int kind,const char*fmt,const char*s,int n){switch(kind){case 0:pline(fmt,s);break;case 1:You("%s",fmt);break;case 2:pline1(fmt);break;case 3:impossible("%s",fmt);break;case 4:panic(fmt,n);break;case 5:pline(fmt,n);break;default:abort();}}
void teleport_restore_format(char*out,const char*fmt,int a,int b,const char*s){Sprintf(out,fmt,a,b,s);}
void teleport_restore_format_prec(char*out,const char*fmt,int precision,const char*s){Sprintf(out,fmt,precision,s);}
void teleport_restore_format_mode(char*out,const char*fmt,int mode,int precision,const char*s){Sprintf(out,fmt,mode,precision,s);}
void teleport_restore_assert(int which){switch(which){case 0:__assert_fail("otmp != 0","restore.c",246,"restobjchn");break;case 1:__assert_fail("mtmp != 0","restore.c",392,"restmonchn");break;default:abort();}}
void teleport_restore_clear(winid w){clear_nhwindow(w);}
void teleport_restore_display(winid w,boolean b){display_nhwindow(w,b);}
void teleport_restore_wait(void){wait_synch();}
winid teleport_restore_create(int n){return create_nhwindow(n);}
void teleport_restore_start(winid w,unsigned long f){start_menu(w,f);}
void teleport_restore_end(winid w,const char*s){end_menu(w,s);}
int teleport_restore_select(winid w,int how,menu_item**p){return select_menu(w,how,p);}
void teleport_restore_destroy(winid w){destroy_nhwindow(w);}
void teleport_restore_add(winid w,const glyph_info*g,const anything*a,char ch,char group,int attr,int color,const char*s,unsigned f){add_menu(w,g,a,ch,group,attr,color,s,f);}
void teleport_restore_add_str(winid w,const char*s){add_menu_str(w,s);}
void teleport_restore_put(winid w,int a,const char*s){putstr(w,a,s);}
void teleport_restore_history(const char*s,boolean b){putmsghistory(s,b);}
int teleport_restore_rnd(int n,int line){if(rng_log_enabled())rng_log_set_caller("restore.c",line,"getlev");return (rnd)(n);}

void teleport_restore_clip(coordxy x,coordxy y){cliparound(x,y);}

void teleport_restore_free(void*p){free(p);}

boolean teleport_restore_debug_enabled(void){return debugcore("restore.c",TRUE);}
