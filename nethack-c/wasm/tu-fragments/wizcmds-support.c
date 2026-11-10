/* WIZCMDS native storage, exact fields and typed dependency transport only. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "wizcmds-source-data.h"
extern glyph_map glyphmap[MAX_GLYPH];
extern const char *const known_handling[];
extern const char unavailcmd[];
extern const char *levltyp[MAX_TYPE+2];
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(int)==4,"WIZCMDS memory64 ABI");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0,"WIZCMDS signed boolean");
void*teleport_wizcmds_global(int i){switch(i){
case 0:return (void*)&flags;
case 1:return (void*)&unavailcmd;
case 2:return (void*)&iflags;
case 3:return (void*)&svm;
case 4:return (void*)&u;
case 5:return (void*)&svl;
case 6:return (void*)&gm;
case 7:return (void*)&a11y;
case 8:return (void*)&gf;
case 9:return (void*)&head_engr;
case 10:return (void*)&ynqchars;
case 11:return (void*)&gu;
case 12:return (void*)&svk;
case 13:return (void*)&genders;
case 14:return (void*)&mons;
case 15:return (void*)&svc;
case 16:return (void*)&c_common_strings;
case 17:return (void*)&ynchars;
case 18:return (void*)&windowprocs;
case 19:return (void*)&gv;
case 20:return (void*)&defsyms;
case 21:return (void*)&svd;
case 22:return (void*)&levltyp;
case 23:return (void*)&gy;
case 24:return (void*)&cg;
case 25:return (void*)&nul_glyphinfo;
case 26:return (void*)&disp;
case 27:return (void*)&gi;
case 28:return (void*)&objects;
case 29:return (void*)&WIN_MESSAGE;
case 30:return (void*)&program_state;
case 31:return (void*)&gb;
case 32:return (void*)&svn;
case 33:return (void*)&obj_descr;
case 34:return (void*)&gs;
case 35:return (void*)&gc;
case 36:return (void*)&known_handling;
case 37:return (void*)&glyphmap;
default:abort();}}
uint64_t teleport_wizcmds_read(int kind,void*at,int field){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->debug);
case 1:return (uint64_t)(uintptr_t)(p->verbose);
case 2:return (uint64_t)(uintptr_t)(p->female);
case 3:return (uint64_t)(uintptr_t)(p->suppress_alert);
default:abort();}}
case 1:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->override_ID);
case 1:return (uint64_t)(uintptr_t)(p->debug_mongen);
case 2:return (uint64_t)(uintptr_t)(p->autodescribe);
case 3:return (uint64_t)(uintptr_t)(p->menu_requested);
case 4:return (uint64_t)(uintptr_t)(p->debug_fuzzer);
case 5:return (uint64_t)(uintptr_t)(p->cmdassist);
case 6:return (uint64_t)(uintptr_t)(p->sanity_no_check);
case 7:return (uint64_t)(uintptr_t)(p->colorcount);
default:abort();}}
case 2:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->pmidx);
case 1:return (uint64_t)(uintptr_t)(p->geno);
case 2:return (uint64_t)(uintptr_t)(p->mflags2);
case 3:return (uint64_t)(uintptr_t)(p->mlet);
case 4:return (uint64_t)(uintptr_t)(p->difficulty);
case 5:return (uint64_t)(uintptr_t)(p->mlevel);
case 6:return (uint64_t)(uintptr_t)(&p->pmnames);
default:abort();}}
case 3:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
case 1:return (uint64_t)(uintptr_t)(p->isgd);
case 2:return (uint64_t)(uintptr_t)(p->mhp);
case 3:return (uint64_t)(uintptr_t)(p->isshk);
case 4:return (uint64_t)(uintptr_t)(p->mextra);
case 5:return (uint64_t)(uintptr_t)(p->mstate);
case 6:return (uint64_t)(uintptr_t)(p->nmon);
case 7:return (uint64_t)(uintptr_t)(p->ispriest);
case 8:return (uint64_t)(uintptr_t)(p->mtame);
case 9:return (uint64_t)(uintptr_t)(p->mx);
case 10:return (uint64_t)(uintptr_t)(p->my);
case 11:return (uint64_t)(uintptr_t)(p->minvent);
case 12:return (uint64_t)(uintptr_t)(p->wormno);
case 13:return (uint64_t)(uintptr_t)(p->mux);
case 14:return (uint64_t)(uintptr_t)(p->muy);
case 15:return (uint64_t)(uintptr_t)(p->m_id);
case 16:return (uint64_t)(uintptr_t)(&p->mtrack);
default:abort();}}
case 4:{struct mvitals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mvflags);
case 1:return (uint64_t)(uintptr_t)(p->born);
default:abort();}}
case 5:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 6:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->uz);
case 1:return (uint64_t)(uintptr_t)(p->ux);
case 2:return (uint64_t)(uintptr_t)(p->uy);
case 3:return (uint64_t)(uintptr_t)(&p->uprops);
case 4:return (uint64_t)(uintptr_t)(p->usteed);
case 5:return (uint64_t)(uintptr_t)(p->uswallow);
case 6:return (uint64_t)(uintptr_t)(p->ustuck);
case 7:return (uint64_t)(uintptr_t)(p->utotype);
case 8:return (uint64_t)(uintptr_t)(p->ulevel);
case 9:return (uint64_t)(uintptr_t)(p->ulevelmax);
case 10:return (uint64_t)(uintptr_t)(p->dx);
case 11:return (uint64_t)(uintptr_t)(p->dy);
case 12:return (uint64_t)(uintptr_t)(p->uhp);
case 13:return (uint64_t)(uintptr_t)(p->uhpmax);
case 14:return (uint64_t)(uintptr_t)(p->uen);
case 15:return (uint64_t)(uintptr_t)(p->uenmax);
case 16:return (uint64_t)(uintptr_t)(p->uinwater);
case 17:return (uint64_t)(uintptr_t)(p->uswldtim);
case 18:return (uint64_t)(uintptr_t)(p->umonnum);
case 19:return (uint64_t)(uintptr_t)(p->umonster);
case 20:return (uint64_t)(uintptr_t)(p->mh);
case 21:return (uint64_t)(uintptr_t)(p->mhmax);
default:abort();}}
case 7:{struct eshk*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->shoplevel);
default:abort();}}
case 8:{struct mextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->eshk);
case 1:return (uint64_t)(uintptr_t)(p->epri);
case 2:return (uint64_t)(uintptr_t)(p->egd);
case 3:return (uint64_t)(uintptr_t)(p->mgivenname);
case 4:return (uint64_t)(uintptr_t)(p->emin);
case 5:return (uint64_t)(uintptr_t)(p->edog);
case 6:return (uint64_t)(uintptr_t)(p->ebones);
default:abort();}}
case 9:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->monlist);
case 1:return (uint64_t)(uintptr_t)(&p->monsters);
case 2:return (uint64_t)(uintptr_t)(&p->locations);
case 3:return (uint64_t)(uintptr_t)(&p->flags);
case 4:return (uint64_t)(uintptr_t)(p->objlist);
case 5:return (uint64_t)(uintptr_t)(p->buriedobjlist);
case 6:return (uint64_t)(uintptr_t)(p->damagelist);
case 7:return (uint64_t)(uintptr_t)(p->bonesinfo);
default:abort();}}
case 10:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 11:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->migrating_mons);
case 1:return (uint64_t)(uintptr_t)(p->migrating_objs);
case 2:return (uint64_t)(uintptr_t)(p->mydogs);
default:abort();}}
case 12:{struct epri*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->shrlevel);
default:abort();}}
case 13:{struct egd*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->gdlevel);
default:abort();}}
case 14:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->intrinsic);
case 1:return (uint64_t)(uintptr_t)(p->extrinsic);
default:abort();}}
case 15:{struct accessibility_data*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mon_notices_blocked);
default:abort();}}
case 16:{struct instance_globals_f*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 17:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ntrap);
case 1:return (uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 18:{struct engr*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nxt_engr);
default:abort();}}
case 19:{struct nhcoord*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->x);
case 1:return (uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 20:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 21:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 22:{struct kinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->name);
case 1:return (uint64_t)(uintptr_t)(p->format);
case 2:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 23:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 24:{struct Gender*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->his);
default:abort();}}
case 25:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mon_moving);
case 1:return (uint64_t)(uintptr_t)(&p->warntype);
default:abort();}}
case 26:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 27:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_Never_mind);
default:abort();}}
case 28:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 1:return (uint64_t)(uintptr_t)(p->win_putstr);
case 2:return (uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 3:return (uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 4:return (uint64_t)(uintptr_t)(p->wp_id);
case 5:return (uint64_t)(uintptr_t)(p->name);
case 6:return (uint64_t)(uintptr_t)(p->win_start_menu);
case 7:return (uint64_t)(uintptr_t)(p->win_end_menu);
default:abort();}}
case 29:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->seenv);
case 1:return (uint64_t)(uintptr_t)(p->typ);
case 2:return (uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 30:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 31:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 32:{struct s_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->proto);
case 1:return (uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 33:{struct d_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->maze_like);
case 1:return (uint64_t)(uintptr_t)(p->hellish);
case 2:return (uint64_t)(uintptr_t)(p->town);
case 3:return (uint64_t)(uintptr_t)(p->rogue_like);
default:abort();}}
case 34:{struct levelflags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nfountains);
case 1:return (uint64_t)(uintptr_t)(p->nsinks);
case 2:return (uint64_t)(uintptr_t)(p->has_vault);
case 3:return (uint64_t)(uintptr_t)(p->has_shop);
case 4:return (uint64_t)(uintptr_t)(p->has_temple);
case 5:return (uint64_t)(uintptr_t)(p->has_court);
case 6:return (uint64_t)(uintptr_t)(p->has_zoo);
case 7:return (uint64_t)(uintptr_t)(p->has_morgue);
case 8:return (uint64_t)(uintptr_t)(p->has_barracks);
case 9:return (uint64_t)(uintptr_t)(p->has_beehive);
case 10:return (uint64_t)(uintptr_t)(p->has_swamp);
case 11:return (uint64_t)(uintptr_t)(p->noteleport);
case 12:return (uint64_t)(uintptr_t)(p->hardfloor);
case 13:return (uint64_t)(uintptr_t)(p->nommap);
case 14:return (uint64_t)(uintptr_t)(p->hero_memory);
case 15:return (uint64_t)(uintptr_t)(p->shortsighted);
case 16:return (uint64_t)(uintptr_t)(p->graveyard);
case 17:return (uint64_t)(uintptr_t)(p->is_maze_lev);
case 18:return (uint64_t)(uintptr_t)(p->is_cavernous_lev);
case 19:return (uint64_t)(uintptr_t)(p->arboreal);
case 20:return (uint64_t)(uintptr_t)(p->sokoban_rules);
default:abort();}}
case 35:{struct symdef*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->sym);
default:abort();}}
case 36:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->d_mines_dnum);
case 1:return (uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 2:return (uint64_t)(uintptr_t)(p->d_quest_dnum);
case 3:return (uint64_t)(uintptr_t)(&p->d_knox_level);
case 4:return (uint64_t)(uintptr_t)(p->d_tower_dnum);
case 5:return (uint64_t)(uintptr_t)(&p->d_astral_level);
case 6:return (uint64_t)(uintptr_t)(&p->d_stronghold_level);
case 7:return (uint64_t)(uintptr_t)(&p->d_valley_level);
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
case 1:return (uint64_t)(uintptr_t)(&p->dungeons);
default:abort();}}
case 38:{struct dungeon*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dname);
default:abort();}}
case 39:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 40:{struct const_globals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 41:{union any*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->a_int);
default:abort();}}
case 42:{struct mi*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->item);
case 1:return (uint64_t)(uintptr_t)(p->count);
default:abort();}}
case 43:{struct warntype_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->speciesidx);
case 1:return (uint64_t)(uintptr_t)(p->species);
default:abort();}}
case 44:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 45:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oextra);
case 1:return (uint64_t)(uintptr_t)(p->nobj);
case 2:return (uint64_t)(uintptr_t)(p->cobj);
default:abort();}}
case 46:{struct oextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oname);
case 1:return (uint64_t)(uintptr_t)(p->omonst);
case 2:return (uint64_t)(uintptr_t)(p->omailcmd);
default:abort();}}
case 47:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 48:{struct damage*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 49:{struct cemetery*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 50:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_uname);
case 1:return (uint64_t)(uintptr_t)(p->oc_class);
case 2:return (uint64_t)(uintptr_t)(p->oc_prob);
case 3:return (uint64_t)(uintptr_t)(p->oc_name_idx);
default:abort();}}
case 51:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->in_sanity_check);
default:abort();}}
case 52:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->billobjs);
default:abort();}}
case 53:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->nhuuid);
default:abort();}}
case 54:{struct objdescr*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_name);
default:abort();}}
case 55:{struct symsetentry*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->name);
case 1:return (uint64_t)(uintptr_t)(p->handling);
default:abort();}}
case 56:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->symset);
case 1:return (uint64_t)(uintptr_t)(&p->showsyms);
default:abort();}}
case 57:{struct instance_globals_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->currentgraphics);
default:abort();}}
case 58:{struct glyph_map_entry*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->u);
case 1:return (uint64_t)(uintptr_t)(p->customcolor);
case 2:return (uint64_t)(uintptr_t)(&p->sym);
default:abort();}}
case 59:{struct classic_representation*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->symidx);
case 1:return (uint64_t)(uintptr_t)(p->color);
default:abort();}}
case 60:{struct unicode_representation*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->utf8str);
case 1:return (uint64_t)(uintptr_t)(p->utf32ch);
default:abort();}}
case 61:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->flags);
case 1:return (uint64_t)(uintptr_t)(p->memlimit);
case 2:return (uint64_t)(uintptr_t)(p->steps);
case 3:return (uint64_t)(uintptr_t)(p->perpcall);
default:abort();}}
case 62:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 63:{struct emin*p=at;switch(field){
default:abort();}}
case 64:{struct edog*p=at;switch(field){
default:abort();}}
case 65:{struct ebones*p=at;switch(field){
default:abort();}}
default:abort();}}
void teleport_wizcmds_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:p->debug=value;return;
case 1:p->verbose=value;return;
case 2:p->female=value;return;
case 3:p->suppress_alert=value;return;
default:abort();}}
case 1:{struct instance_flags*p=at;switch(field){
case 0:p->override_ID=value;return;
case 1:p->debug_mongen=value;return;
case 2:p->autodescribe=value;return;
case 3:p->menu_requested=value;return;
case 4:p->debug_fuzzer=value;return;
case 5:p->cmdassist=value;return;
case 6:p->sanity_no_check=value;return;
case 7:p->colorcount=value;return;
default:abort();}}
case 2:{struct permonst*p=at;switch(field){
case 1:p->geno=value;return;
case 2:p->mflags2=value;return;
case 3:p->mlet=value;return;
case 4:p->difficulty=value;return;
case 5:p->mlevel=value;return;
default:abort();}}
case 3:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
case 1:p->isgd=value;return;
case 2:p->mhp=value;return;
case 3:p->isshk=value;return;
case 4:p->mextra=(void*)(uintptr_t)value;return;
case 5:p->mstate=value;return;
case 6:p->nmon=(void*)(uintptr_t)value;return;
case 7:p->ispriest=value;return;
case 8:p->mtame=value;return;
case 9:p->mx=value;return;
case 10:p->my=value;return;
case 11:p->minvent=(void*)(uintptr_t)value;return;
case 12:p->wormno=value;return;
case 13:p->mux=value;return;
case 14:p->muy=value;return;
case 15:p->m_id=value;return;
default:abort();}}
case 4:{struct mvitals*p=at;switch(field){
case 0:p->mvflags=value;return;
case 1:p->born=value;return;
default:abort();}}
case 5:{struct instance_globals_saved_m*p=at;switch(field){
default:abort();}}
case 6:{struct you*p=at;switch(field){
case 0:memmove(&p->uz,(void*)(uintptr_t)value,sizeof p->uz);return;
case 1:p->ux=value;return;
case 2:p->uy=value;return;
case 4:p->usteed=(void*)(uintptr_t)value;return;
case 5:p->uswallow=value;return;
case 6:p->ustuck=(void*)(uintptr_t)value;return;
case 7:p->utotype=value;return;
case 8:p->ulevel=value;return;
case 9:p->ulevelmax=value;return;
case 10:p->dx=value;return;
case 11:p->dy=value;return;
case 12:p->uhp=value;return;
case 13:p->uhpmax=value;return;
case 14:p->uen=value;return;
case 15:p->uenmax=value;return;
case 16:p->uinwater=value;return;
case 17:p->uswldtim=value;return;
case 18:p->umonnum=value;return;
case 19:p->umonster=value;return;
case 20:p->mh=value;return;
case 21:p->mhmax=value;return;
default:abort();}}
case 7:{struct eshk*p=at;switch(field){
case 0:memmove(&p->shoplevel,(void*)(uintptr_t)value,sizeof p->shoplevel);return;
default:abort();}}
case 8:{struct mextra*p=at;switch(field){
case 0:p->eshk=(void*)(uintptr_t)value;return;
case 1:p->epri=(void*)(uintptr_t)value;return;
case 2:p->egd=(void*)(uintptr_t)value;return;
case 3:p->mgivenname=(void*)(uintptr_t)value;return;
case 4:p->emin=(void*)(uintptr_t)value;return;
case 5:p->edog=(void*)(uintptr_t)value;return;
case 6:p->ebones=(void*)(uintptr_t)value;return;
default:abort();}}
case 9:{dlevel_t*p=at;switch(field){
case 0:p->monlist=(void*)(uintptr_t)value;return;
case 3:memmove(&p->flags,(void*)(uintptr_t)value,sizeof p->flags);return;
case 4:p->objlist=(void*)(uintptr_t)value;return;
case 5:p->buriedobjlist=(void*)(uintptr_t)value;return;
case 6:p->damagelist=(void*)(uintptr_t)value;return;
case 7:p->bonesinfo=(void*)(uintptr_t)value;return;
default:abort();}}
case 10:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level,(void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 11:{struct instance_globals_m*p=at;switch(field){
case 0:p->migrating_mons=(void*)(uintptr_t)value;return;
case 1:p->migrating_objs=(void*)(uintptr_t)value;return;
case 2:p->mydogs=(void*)(uintptr_t)value;return;
default:abort();}}
case 12:{struct epri*p=at;switch(field){
case 0:memmove(&p->shrlevel,(void*)(uintptr_t)value,sizeof p->shrlevel);return;
default:abort();}}
case 13:{struct egd*p=at;switch(field){
case 0:memmove(&p->gdlevel,(void*)(uintptr_t)value,sizeof p->gdlevel);return;
default:abort();}}
case 14:{struct prop*p=at;switch(field){
case 0:p->intrinsic=value;return;
case 1:p->extrinsic=value;return;
default:abort();}}
case 15:{struct accessibility_data*p=at;switch(field){
case 0:p->mon_notices_blocked=value;return;
default:abort();}}
case 16:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(void*)(uintptr_t)value;return;
default:abort();}}
case 17:{struct trap*p=at;switch(field){
case 0:p->ntrap=(void*)(uintptr_t)value;return;
case 1:p->tseen=value;return;
default:abort();}}
case 18:{struct engr*p=at;switch(field){
case 0:p->nxt_engr=(void*)(uintptr_t)value;return;
default:abort();}}
case 19:{struct nhcoord*p=at;switch(field){
case 0:p->x=value;return;
case 1:p->y=value;return;
default:abort();}}
case 20:{struct Role*p=at;switch(field){
case 0:p->mnum=value;return;
default:abort();}}
case 21:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole,(void*)(uintptr_t)value,sizeof p->urole);return;
default:abort();}}
case 22:{struct kinfo*p=at;switch(field){
case 1:p->format=value;return;
case 2:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 23:{struct instance_globals_saved_k*p=at;switch(field){
case 0:memmove(&p->killer,(void*)(uintptr_t)value,sizeof p->killer);return;
default:abort();}}
case 24:{struct Gender*p=at;switch(field){
case 0:p->his=(void*)(uintptr_t)value;return;
default:abort();}}
case 25:{struct context_info*p=at;switch(field){
case 0:p->mon_moving=value;return;
case 1:memmove(&p->warntype,(void*)(uintptr_t)value,sizeof p->warntype);return;
default:abort();}}
case 26:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context,(void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 27:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 28:{struct window_procs*p=at;switch(field){
case 0:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))(uintptr_t)value;return;
case 1:p->win_putstr=(__typeof__(p->win_putstr))(uintptr_t)value;return;
case 2:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))(uintptr_t)value;return;
case 3:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))(uintptr_t)value;return;
case 4:p->wp_id=value;return;
case 5:p->name=(void*)(uintptr_t)value;return;
case 6:p->win_start_menu=(__typeof__(p->win_start_menu))(uintptr_t)value;return;
case 7:p->win_end_menu=(__typeof__(p->win_end_menu))(uintptr_t)value;return;
default:abort();}}
case 29:{struct rm*p=at;switch(field){
case 0:p->seenv=value;return;
case 1:p->typ=value;return;
case 2:p->flags=value;return;
default:abort();}}
case 30:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(void*)(uintptr_t)value;return;
default:abort();}}
case 31:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 32:{struct s_level*p=at;switch(field){
case 1:memmove(&p->flags,(void*)(uintptr_t)value,sizeof p->flags);return;
default:abort();}}
case 33:{struct d_flags*p=at;switch(field){
case 0:p->maze_like=value;return;
case 1:p->hellish=value;return;
case 2:p->town=value;return;
case 3:p->rogue_like=value;return;
default:abort();}}
case 34:{struct levelflags*p=at;switch(field){
case 0:p->nfountains=value;return;
case 1:p->nsinks=value;return;
case 2:p->has_vault=value;return;
case 3:p->has_shop=value;return;
case 4:p->has_temple=value;return;
case 5:p->has_court=value;return;
case 6:p->has_zoo=value;return;
case 7:p->has_morgue=value;return;
case 8:p->has_barracks=value;return;
case 9:p->has_beehive=value;return;
case 10:p->has_swamp=value;return;
case 11:p->noteleport=value;return;
case 12:p->hardfloor=value;return;
case 13:p->nommap=value;return;
case 14:p->hero_memory=value;return;
case 15:p->shortsighted=value;return;
case 16:p->graveyard=value;return;
case 17:p->is_maze_lev=value;return;
case 18:p->is_cavernous_lev=value;return;
case 19:p->arboreal=value;return;
case 20:p->sokoban_rules=value;return;
default:abort();}}
case 35:{struct symdef*p=at;switch(field){
case 0:p->sym=value;return;
default:abort();}}
case 36:{struct dgn_topology*p=at;switch(field){
case 0:p->d_mines_dnum=value;return;
case 1:p->d_sokoban_dnum=value;return;
case 2:p->d_quest_dnum=value;return;
case 3:memmove(&p->d_knox_level,(void*)(uintptr_t)value,sizeof p->d_knox_level);return;
case 4:p->d_tower_dnum=value;return;
case 5:memmove(&p->d_astral_level,(void*)(uintptr_t)value,sizeof p->d_astral_level);return;
case 6:memmove(&p->d_stronghold_level,(void*)(uintptr_t)value,sizeof p->d_stronghold_level);return;
case 7:memmove(&p->d_valley_level,(void*)(uintptr_t)value,sizeof p->d_valley_level);return;
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology,(void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 38:{struct dungeon*p=at;switch(field){
default:abort();}}
case 39:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst,(void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 40:{struct const_globals*p=at;switch(field){
default:abort();}}
case 41:{union any*p=at;switch(field){
case 0:p->a_int=value;return;
default:abort();}}
case 42:{struct mi*p=at;switch(field){
case 0:memmove(&p->item,(void*)(uintptr_t)value,sizeof p->item);return;
case 1:p->count=value;return;
default:abort();}}
case 43:{struct warntype_info*p=at;switch(field){
case 0:p->speciesidx=value;return;
case 1:p->species=(void*)(uintptr_t)value;return;
default:abort();}}
case 44:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
default:abort();}}
case 45:{struct obj*p=at;switch(field){
case 0:p->oextra=(void*)(uintptr_t)value;return;
case 1:p->nobj=(void*)(uintptr_t)value;return;
case 2:p->cobj=(void*)(uintptr_t)value;return;
default:abort();}}
case 46:{struct oextra*p=at;switch(field){
case 0:p->oname=(void*)(uintptr_t)value;return;
case 1:p->omonst=(void*)(uintptr_t)value;return;
case 2:p->omailcmd=(void*)(uintptr_t)value;return;
default:abort();}}
case 47:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 48:{struct damage*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 49:{struct cemetery*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 50:{struct objclass*p=at;switch(field){
case 0:p->oc_uname=(void*)(uintptr_t)value;return;
case 1:p->oc_class=value;return;
case 2:p->oc_prob=value;return;
case 3:p->oc_name_idx=value;return;
default:abort();}}
case 51:{struct sinfo*p=at;switch(field){
case 0:p->in_sanity_check=value;return;
default:abort();}}
case 52:{struct instance_globals_b*p=at;switch(field){
case 0:p->billobjs=(void*)(uintptr_t)value;return;
default:abort();}}
case 53:{struct instance_globals_saved_n*p=at;switch(field){
default:abort();}}
case 54:{struct objdescr*p=at;switch(field){
case 0:p->oc_name=(void*)(uintptr_t)value;return;
default:abort();}}
case 55:{struct symsetentry*p=at;switch(field){
case 0:p->name=(void*)(uintptr_t)value;return;
case 1:p->handling=value;return;
default:abort();}}
case 56:{struct instance_globals_s*p=at;switch(field){
default:abort();}}
case 57:{struct instance_globals_c*p=at;switch(field){
case 0:p->currentgraphics=value;return;
default:abort();}}
case 58:{struct glyph_map_entry*p=at;switch(field){
case 0:p->u=(void*)(uintptr_t)value;return;
case 1:p->customcolor=value;return;
case 2:memmove(&p->sym,(void*)(uintptr_t)value,sizeof p->sym);return;
default:abort();}}
case 59:{struct classic_representation*p=at;switch(field){
case 0:p->symidx=value;return;
case 1:p->color=value;return;
default:abort();}}
case 60:{struct unicode_representation*p=at;switch(field){
case 0:p->utf8str=(void*)(uintptr_t)value;return;
case 1:p->utf32ch=value;return;
default:abort();}}
case 61:{struct nhl_sandbox_info*p=at;switch(field){
case 0:p->flags=value;return;
case 1:p->memlimit=value;return;
case 2:p->steps=value;return;
case 3:p->perpcall=value;return;
default:abort();}}
case 62:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 63:{struct emin*p=at;switch(field){
default:abort();}}
case 64:{struct edog*p=at;switch(field){
default:abort();}}
case 65:{struct ebones*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_wizcmds_address(int kind,void*at,int field){switch(kind){
case 0:{struct flag*p=at;switch(field){
case 0:return (void*)&p->debug;
case 1:return (void*)&p->verbose;
case 2:return (void*)&p->female;
case 3:return (void*)&p->suppress_alert;
default:abort();}}
case 1:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->override_ID;
case 1:return (void*)&p->debug_mongen;
case 2:return (void*)&p->autodescribe;
case 3:return (void*)&p->menu_requested;
case 4:return (void*)&p->debug_fuzzer;
case 5:return (void*)&p->cmdassist;
case 6:return (void*)&p->sanity_no_check;
case 7:return (void*)&p->colorcount;
default:abort();}}
case 2:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->pmidx;
case 1:return (void*)&p->geno;
case 2:return (void*)&p->mflags2;
case 3:return (void*)&p->mlet;
case 4:return (void*)&p->difficulty;
case 5:return (void*)&p->mlevel;
case 6:return (void*)&p->pmnames;
default:abort();}}
case 3:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
case 2:return (void*)&p->mhp;
case 4:return (void*)&p->mextra;
case 5:return (void*)&p->mstate;
case 6:return (void*)&p->nmon;
case 8:return (void*)&p->mtame;
case 9:return (void*)&p->mx;
case 10:return (void*)&p->my;
case 11:return (void*)&p->minvent;
case 13:return (void*)&p->mux;
case 14:return (void*)&p->muy;
case 15:return (void*)&p->m_id;
case 16:return (void*)&p->mtrack;
default:abort();}}
case 4:{struct mvitals*p=at;switch(field){
case 0:return (void*)&p->mvflags;
case 1:return (void*)&p->born;
default:abort();}}
case 5:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->mvitals;
default:abort();}}
case 6:{struct you*p=at;switch(field){
case 0:return (void*)&p->uz;
case 1:return (void*)&p->ux;
case 2:return (void*)&p->uy;
case 3:return (void*)&p->uprops;
case 4:return (void*)&p->usteed;
case 6:return (void*)&p->ustuck;
case 7:return (void*)&p->utotype;
case 8:return (void*)&p->ulevel;
case 9:return (void*)&p->ulevelmax;
case 10:return (void*)&p->dx;
case 11:return (void*)&p->dy;
case 12:return (void*)&p->uhp;
case 13:return (void*)&p->uhpmax;
case 14:return (void*)&p->uen;
case 15:return (void*)&p->uenmax;
case 17:return (void*)&p->uswldtim;
case 18:return (void*)&p->umonnum;
case 19:return (void*)&p->umonster;
case 20:return (void*)&p->mh;
case 21:return (void*)&p->mhmax;
default:abort();}}
case 7:{struct eshk*p=at;switch(field){
case 0:return (void*)&p->shoplevel;
default:abort();}}
case 8:{struct mextra*p=at;switch(field){
case 0:return (void*)&p->eshk;
case 1:return (void*)&p->epri;
case 2:return (void*)&p->egd;
case 3:return (void*)&p->mgivenname;
case 4:return (void*)&p->emin;
case 5:return (void*)&p->edog;
case 6:return (void*)&p->ebones;
default:abort();}}
case 9:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->monlist;
case 1:return (void*)&p->monsters;
case 2:return (void*)&p->locations;
case 3:return (void*)&p->flags;
case 4:return (void*)&p->objlist;
case 5:return (void*)&p->buriedobjlist;
case 6:return (void*)&p->damagelist;
case 7:return (void*)&p->bonesinfo;
default:abort();}}
case 10:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
default:abort();}}
case 11:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->migrating_mons;
case 1:return (void*)&p->migrating_objs;
case 2:return (void*)&p->mydogs;
default:abort();}}
case 12:{struct epri*p=at;switch(field){
case 0:return (void*)&p->shrlevel;
default:abort();}}
case 13:{struct egd*p=at;switch(field){
case 0:return (void*)&p->gdlevel;
default:abort();}}
case 14:{struct prop*p=at;switch(field){
case 0:return (void*)&p->intrinsic;
case 1:return (void*)&p->extrinsic;
default:abort();}}
case 15:{struct accessibility_data*p=at;switch(field){
case 0:return (void*)&p->mon_notices_blocked;
default:abort();}}
case 16:{struct instance_globals_f*p=at;switch(field){
case 0:return (void*)&p->ftrap;
default:abort();}}
case 17:{struct trap*p=at;switch(field){
case 0:return (void*)&p->ntrap;
default:abort();}}
case 18:{struct engr*p=at;switch(field){
case 0:return (void*)&p->nxt_engr;
default:abort();}}
case 19:{struct nhcoord*p=at;switch(field){
case 0:return (void*)&p->x;
case 1:return (void*)&p->y;
default:abort();}}
case 20:{struct Role*p=at;switch(field){
case 0:return (void*)&p->mnum;
default:abort();}}
case 21:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
default:abort();}}
case 22:{struct kinfo*p=at;switch(field){
case 0:return (void*)&p->name;
case 1:return (void*)&p->format;
case 2:return (void*)&p->next;
default:abort();}}
case 23:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (void*)&p->killer;
default:abort();}}
case 24:{struct Gender*p=at;switch(field){
case 0:return (void*)&p->his;
default:abort();}}
case 25:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->mon_moving;
case 1:return (void*)&p->warntype;
default:abort();}}
case 26:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 27:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_Never_mind;
default:abort();}}
case 28:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->win_create_nhwindow;
case 1:return (void*)&p->win_putstr;
case 2:return (void*)&p->win_display_nhwindow;
case 3:return (void*)&p->win_destroy_nhwindow;
case 4:return (void*)&p->wp_id;
case 5:return (void*)&p->name;
case 6:return (void*)&p->win_start_menu;
case 7:return (void*)&p->win_end_menu;
default:abort();}}
case 29:{struct rm*p=at;switch(field){
case 0:return (void*)&p->seenv;
case 1:return (void*)&p->typ;
default:abort();}}
case 30:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->viz_array;
default:abort();}}
case 31:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 32:{struct s_level*p=at;switch(field){
case 0:return (void*)&p->proto;
case 1:return (void*)&p->flags;
default:abort();}}
case 33:{struct d_flags*p=at;switch(field){
default:abort();}}
case 34:{struct levelflags*p=at;switch(field){
case 0:return (void*)&p->nfountains;
case 1:return (void*)&p->nsinks;
default:abort();}}
case 35:{struct symdef*p=at;switch(field){
case 0:return (void*)&p->sym;
default:abort();}}
case 36:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_mines_dnum;
case 1:return (void*)&p->d_sokoban_dnum;
case 2:return (void*)&p->d_quest_dnum;
case 3:return (void*)&p->d_knox_level;
case 4:return (void*)&p->d_tower_dnum;
case 5:return (void*)&p->d_astral_level;
case 6:return (void*)&p->d_stronghold_level;
case 7:return (void*)&p->d_valley_level;
default:abort();}}
case 37:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
case 1:return (void*)&p->dungeons;
default:abort();}}
case 38:{struct dungeon*p=at;switch(field){
case 0:return (void*)&p->dname;
default:abort();}}
case 39:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 40:{struct const_globals*p=at;switch(field){
case 0:return (void*)&p->zeroany;
default:abort();}}
case 41:{union any*p=at;switch(field){
case 0:return (void*)&p->a_int;
default:abort();}}
case 42:{struct mi*p=at;switch(field){
case 0:return (void*)&p->item;
case 1:return (void*)&p->count;
default:abort();}}
case 43:{struct warntype_info*p=at;switch(field){
case 0:return (void*)&p->speciesidx;
case 1:return (void*)&p->species;
default:abort();}}
case 44:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
default:abort();}}
case 45:{struct obj*p=at;switch(field){
case 0:return (void*)&p->oextra;
case 1:return (void*)&p->nobj;
case 2:return (void*)&p->cobj;
default:abort();}}
case 46:{struct oextra*p=at;switch(field){
case 0:return (void*)&p->oname;
case 1:return (void*)&p->omonst;
case 2:return (void*)&p->omailcmd;
default:abort();}}
case 47:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 48:{struct damage*p=at;switch(field){
case 0:return (void*)&p->next;
default:abort();}}
case 49:{struct cemetery*p=at;switch(field){
case 0:return (void*)&p->next;
default:abort();}}
case 50:{struct objclass*p=at;switch(field){
case 0:return (void*)&p->oc_uname;
case 1:return (void*)&p->oc_class;
case 2:return (void*)&p->oc_prob;
case 3:return (void*)&p->oc_name_idx;
default:abort();}}
case 51:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->in_sanity_check;
default:abort();}}
case 52:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->billobjs;
default:abort();}}
case 53:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (void*)&p->nhuuid;
default:abort();}}
case 54:{struct objdescr*p=at;switch(field){
case 0:return (void*)&p->oc_name;
default:abort();}}
case 55:{struct symsetentry*p=at;switch(field){
case 0:return (void*)&p->name;
case 1:return (void*)&p->handling;
default:abort();}}
case 56:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->symset;
case 1:return (void*)&p->showsyms;
default:abort();}}
case 57:{struct instance_globals_c*p=at;switch(field){
case 0:return (void*)&p->currentgraphics;
default:abort();}}
case 58:{struct glyph_map_entry*p=at;switch(field){
case 0:return (void*)&p->u;
case 1:return (void*)&p->customcolor;
case 2:return (void*)&p->sym;
default:abort();}}
case 59:{struct classic_representation*p=at;switch(field){
case 0:return (void*)&p->symidx;
case 1:return (void*)&p->color;
default:abort();}}
case 60:{struct unicode_representation*p=at;switch(field){
case 0:return (void*)&p->utf8str;
case 1:return (void*)&p->utf32ch;
default:abort();}}
case 61:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return (void*)&p->flags;
case 1:return (void*)&p->memlimit;
case 2:return (void*)&p->steps;
case 3:return (void*)&p->perpcall;
default:abort();}}
case 62:{struct glyphinfo*p=at;switch(field){
default:abort();}}
case 63:{struct emin*p=at;switch(field){
default:abort();}}
case 64:{struct edog*p=at;switch(field){
default:abort();}}
case 65:{struct ebones*p=at;switch(field){
default:abort();}}
default:abort();}}
static char wizcmds_literals[WIZCMDS_LITERAL_CAPACITY];
char*teleport_wizcmds_literal_storage(void){return wizcmds_literals;}
size_t teleport_wizcmds_literal_capacity(void){return sizeof wizcmds_literals;}
int teleport_wizcmds_rn2(int n,int line,const char*caller){if(rng_log_enabled())rng_log_set_caller("wizcmds.c",line,caller);return(rn2)(n);}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
void teleport_wizcmds_pline_pp(char * a0,char * a1){(pline)(a0,a1);}
void teleport_wizcmds_impossible_p(char * a0){(impossible)(a0);}
int teleport_wizcmds_sprintf_ppp(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_wizcmds_You_ppp(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_wizcmds_pline_ppp(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_wizcmds_There_p(char * a0){(There)(a0);}
int teleport_wizcmds_sscanf_pppp(char * a0,char * a1,int * a2,char * a3){return (sscanf)(a0,a1,a2,a3);}
void teleport_wizcmds_You_p(char * a0){(You)(a0);}
void teleport_wizcmds_pline_p(char * a0){(pline)(a0);}
void teleport_wizcmds_panic_p(char * a0){(panic)(a0);}
int teleport_wizcmds_sprintf_ppi(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_wizcmds_sprintf_ppiii(char * a0,char * a1,int a2,int a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_wizcmds_sprintf_ppii(char * a0,char * a1,int a2,int a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_wizcmds_sprintf_ppip(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_wizcmds_You_pp(char * a0,char * a1){(You)(a0,a1);}
int teleport_wizcmds_sprintf_pppj(char * a0,char * a1,char * a2,long a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_wizcmds_sprintf_pppp(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_wizcmds_pline_pppi(char * a0,char * a1,char * a2,int a3){(pline)(a0,a1,a2,a3);}
int teleport_wizcmds_sprintf_pppjj(char * a0,char * a1,char * a2,long a3,long a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_wizcmds_sprintf_ppj(char * a0,char * a1,unsigned long a2){return (sprintf)(a0,a1,a2);}
void teleport_wizcmds_impossible_pii(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_wizcmds_pline_pipii(char * a0,int a1,char * a2,int a3,int a4){(pline)(a0,a1,a2,a3,a4);}
int teleport_wizcmds_sprintf_ppiiii(char * a0,char * a1,int a2,int a3,int a4,int a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_wizcmds_nh_snprintf_pipjppiiiii(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,int a6,int a7,int a8,int a9,int a10){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);}
void teleport_wizcmds_nh_snprintf_pipjpiidp(char * a0,int a1,char * a2,unsigned long a3,char * a4,int a5,int a6,double a7,char * a8){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_wizcmds_sprintf_pppjp(char * a0,char * a1,char * a2,long a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_wizcmds_nh_snprintf_pipjppppp(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,char * a7,char * a8){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
#pragma clang diagnostic pop
winid teleport_wizcmds_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_wizcmds_putstr(winid a0,int a1,const char * a2){putstr(a0,a1,a2);}
void teleport_wizcmds_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
void teleport_wizcmds_destroy_nhwindow(winid a0){destroy_nhwindow(a0);}
void teleport_wizcmds_start_menu(winid a0,unsigned long a1){start_menu(a0,a1);}
void teleport_wizcmds_end_menu(winid a0,const char * a1){end_menu(a0,a1);}
#ifdef TELEPORT_REFERENCE_TU
#define teleport_wizcmds_callback_migrsort_cmp migrsort_cmp
#else
extern int teleport_wizcmds_callback_migrsort_cmp(const void * a0,const void * a1);
#endif
uintptr_t teleport_wizcmds_function_pointer(int kind){switch(kind){
case 0:return(uintptr_t)&wiz_wish;
case 1:return(uintptr_t)&wiz_identify;
case 4:return(uintptr_t)&wiz_makemap;
case 5:return(uintptr_t)&wiz_map;
case 6:return(uintptr_t)&wiz_genesis;
case 7:return(uintptr_t)&wiz_where;
case 8:return(uintptr_t)&wiz_detect;
case 10:return(uintptr_t)&wiz_load_lua;
case 11:return(uintptr_t)&wiz_load_splua;
case 12:return(uintptr_t)&wiz_level_tele;
case 25:return(uintptr_t)&wiz_intrinsic;
case 38:return(uintptr_t)&teleport_wizcmds_callback_migrsort_cmp;
case 46:return(uintptr_t)&wiz_custom;
default:abort();}}
_Static_assert(__builtin_types_compatible_p(__typeof__(&makewish),void (*)(void)),"WIZCMDS dependency makewish");
_Static_assert(__builtin_types_compatible_p(__typeof__(&encumber_msg),void (*)(void)),"WIZCMDS dependency encumber_msg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline),void (*)(const char *,...)),"WIZCMDS dependency pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ecname_from_fn),const char * (*)(int (*)(void))),"WIZCMDS dependency ecname_from_fn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cmd_from_func),char (*)(int (*)(void))),"WIZCMDS dependency cmd_from_func");
_Static_assert(__builtin_types_compatible_p(__typeof__(&display_inventory),char (*)(const char *,boolean)),"WIZCMDS dependency display_inventory");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),boolean (*)(d_level *,d_level *)),"WIZCMDS dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setpaid),void (*)(struct monst *)),"WIZCMDS dependency setpaid");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mongone),void (*)(struct monst *)),"WIZCMDS dependency mongone");
_Static_assert(__builtin_types_compatible_p(__typeof__(&keepdogs),void (*)(boolean)),"WIZCMDS dependency keepdogs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmonsfree),void (*)(void)),"WIZCMDS dependency dmonsfree");
_Static_assert(__builtin_types_compatible_p(__typeof__(&impossible),void (*)(const char *,...)),"WIZCMDS dependency impossible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&In_W_tower),boolean (*)(coordxy,coordxy,d_level *)),"WIZCMDS dependency In_W_tower");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makemap_prepost),void (*)(boolean,boolean)),"WIZCMDS dependency makemap_prepost");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mklev),void (*)(void)),"WIZCMDS dependency mklev");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_trap),void (*)(struct trap *,int)),"WIZCMDS dependency map_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_engraving),void (*)(struct engr *,int)),"WIZCMDS dependency map_engraving");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_mapping),void (*)(void)),"WIZCMDS dependency do_mapping");
_Static_assert(__builtin_types_compatible_p(__typeof__(&create_particular),boolean (*)(void)),"WIZCMDS dependency create_particular");
_Static_assert(__builtin_types_compatible_p(__typeof__(&print_dungeon),schar (*)(boolean,schar *,xint16 *)),"WIZCMDS dependency print_dungeon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&findit),int (*)(void)),"WIZCMDS dependency findit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getpos),int (*)(coord *,boolean,const char *)),"WIZCMDS dependency getpos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sprintf),int (*)(char *restrict,const char *restrict,...)),"WIZCMDS dependency sprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_nam),char * (*)(struct monst *)),"WIZCMDS dependency mon_nam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yn_function),char (*)(const char *,const char *,char,boolean)),"WIZCMDS dependency yn_function");
_Static_assert(__builtin_types_compatible_p(__typeof__(&paranoid_query),boolean (*)(boolean,const char *)),"WIZCMDS dependency paranoid_query");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done),void (*)(int)),"WIZCMDS dependency done");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy,coordxy,coordxy,coordxy)),"WIZCMDS dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unmap_invisible),boolean (*)(coordxy,coordxy)),"WIZCMDS dependency unmap_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"WIZCMDS dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"WIZCMDS dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&x_monnam),char * (*)(struct monst *,int,const char *,int,boolean)),"WIZCMDS dependency x_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&You),void (*)(const char *,...)),"WIZCMDS dependency You");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xkilled),void (*)(struct monst *,int)),"WIZCMDS dependency xkilled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&upstart),char * (*)(char *)),"WIZCMDS dependency upstart");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monkilled),void (*)(struct monst *,const char *,int)),"WIZCMDS dependency monkilled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&There),void (*)(const char *,...)),"WIZCMDS dependency There");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getlin),void (*)(const char *,char *)),"WIZCMDS dependency getlin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strchr),char * (*)(const char *,int)),"WIZCMDS dependency strchr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcat),char * (*)(char *restrict,const char *restrict)),"WIZCMDS dependency strcat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&load_lua),boolean (*)(const char *,nhl_sandbox_info *)),"WIZCMDS dependency load_lua");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lspo_reset_level),int (*)(lua_State *)),"WIZCMDS dependency lspo_reset_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&load_special),boolean (*)(const char *)),"WIZCMDS dependency load_special");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lspo_finalize_level),int (*)(lua_State *)),"WIZCMDS dependency lspo_finalize_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&level_tele),void (*)(void)),"WIZCMDS dependency level_tele");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flip_level_rnd),void (*)(int,boolean)),"WIZCMDS dependency flip_level_rnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&flip_level),void (*)(int,boolean)),"WIZCMDS dependency flip_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&docrt),void (*)(void)),"WIZCMDS dependency docrt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mungspaces),char * (*)(char *)),"WIZCMDS dependency mungspaces");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sscanf),int (*)(const char *restrict,const char *restrict,...)),"WIZCMDS dependency sscanf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&losexp),void (*)(const char *)),"WIZCMDS dependency losexp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pluslvl),void (*)(boolean)),"WIZCMDS dependency pluslvl");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getdir),int (*)(const char *)),"WIZCMDS dependency getdir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mhurtle),void (*)(struct monst *,int,int,int)),"WIZCMDS dependency mhurtle");
_Static_assert(__builtin_types_compatible_p(__typeof__(&hurtle),void (*)(int,int,int,boolean)),"WIZCMDS dependency hurtle");
_Static_assert(__builtin_types_compatible_p(__typeof__(&panic),void (*)(const char *,...)),"WIZCMDS dependency panic");
_Static_assert(__builtin_types_compatible_p(__typeof__(&polyself),void (*)(int)),"WIZCMDS dependency polyself");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *,const char *)),"WIZCMDS dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&may_dig),boolean (*)(coordxy,coordxy)),"WIZCMDS dependency may_dig");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Is_special),s_level * (*)(d_level *)),"WIZCMDS dependency Is_special");
_Static_assert(__builtin_types_compatible_p(__typeof__(&eos),char * (*)(char *)),"WIZCMDS dependency eos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Invocation_lev),boolean (*)(d_level *)),"WIZCMDS dependency Invocation_lev");
_Static_assert(__builtin_types_compatible_p(__typeof__(&On_W_tower_level),boolean (*)(d_level *)),"WIZCMDS dependency On_W_tower_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmpi),int (*)(const char *,const char *,int)),"WIZCMDS dependency strncmpi");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strlen),unsigned long (*)(const char *)),"WIZCMDS dependency strlen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmp),int (*)(const char *,const char *,size_t)),"WIZCMDS dependency strncmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&olfaction),boolean (*)(struct permonst *)),"WIZCMDS dependency olfaction");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_at),int (*)(coordxy,coordxy)),"WIZCMDS dependency glyph_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&body_part),const char * (*)(int)),"WIZCMDS dependency body_part");
_Static_assert(__builtin_types_compatible_p(__typeof__(&usmellmon),boolean (*)(struct permonst *)),"WIZCMDS dependency usmellmon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&map_invisible),void (*)(coordxy,coordxy)),"WIZCMDS dependency map_invisible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_menu_str),void (*)(winid,const char *)),"WIZCMDS dependency add_menu_str");
_Static_assert(__builtin_types_compatible_p(__typeof__(&property_by_index),const char * (*)(int,int *)),"WIZCMDS dependency property_by_index");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_menu),void (*)(winid,const glyph_info *,const union any *,char,char,int,int,const char *,unsigned int)),"WIZCMDS dependency add_menu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&select_menu),int (*)(winid,int,menu_item **)),"WIZCMDS dependency select_menu");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_blinded),void (*)(long,boolean)),"WIZCMDS dependency make_blinded");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_deaf),void (*)(long,boolean)),"WIZCMDS dependency make_deaf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_hallucinated),boolean (*)(long,boolean,long)),"WIZCMDS dependency make_hallucinated");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"WIZCMDS dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *,int,const char *)),"WIZCMDS dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"WIZCMDS dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_sick),void (*)(long,const char *,boolean,int)),"WIZCMDS dependency make_sick");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_slimed),void (*)(long,const char *)),"WIZCMDS dependency make_slimed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_stoned),void (*)(long,const char *,int,const char *)),"WIZCMDS dependency make_stoned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_stunned),void (*)(long,boolean)),"WIZCMDS dependency make_stunned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_vomiting),void (*)(long,boolean)),"WIZCMDS dependency make_vomiting");
_Static_assert(__builtin_types_compatible_p(__typeof__(&make_glib),void (*)(int)),"WIZCMDS dependency make_glib");
_Static_assert(__builtin_types_compatible_p(__typeof__(&incr_itimeout),void (*)(long *,int)),"WIZCMDS dependency incr_itimeout");
_Static_assert(__builtin_types_compatible_p(__typeof__(&float_vs_flight),void (*)(void)),"WIZCMDS dependency float_vs_flight");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rescham),void (*)(void)),"WIZCMDS dependency rescham");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pooleffects),boolean (*)(boolean)),"WIZCMDS dependency pooleffects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free),void (*)(void *)),"WIZCMDS dependency free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rumor_check),void (*)(void)),"WIZCMDS dependency rumor_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&size_wseg),int (*)(struct monst *)),"WIZCMDS dependency size_wseg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&engr_stats),void (*)(const char *,char *,long *,long *)),"WIZCMDS dependency engr_stats");
_Static_assert(__builtin_types_compatible_p(__typeof__(&light_stats),void (*)(const char *,char *,long *,long *)),"WIZCMDS dependency light_stats");
_Static_assert(__builtin_types_compatible_p(__typeof__(&timer_stats),void (*)(const char *,char *,long *,long *)),"WIZCMDS dependency timer_stats");
_Static_assert(__builtin_types_compatible_p(__typeof__(&region_stats),void (*)(const char *,char *,long *,long *)),"WIZCMDS dependency region_stats");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char * (*)(char *restrict,const char *restrict)),"WIZCMDS dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&check_wornmask_slots),void (*)(void)),"WIZCMDS dependency check_wornmask_slots");
_Static_assert(__builtin_types_compatible_p(__typeof__(&check_invent_gold),boolean (*)(const char *)),"WIZCMDS dependency check_invent_gold");
_Static_assert(__builtin_types_compatible_p(__typeof__(&does_block),int (*)(int,int,struct rm *)),"WIZCMDS dependency does_block");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_viz_clear),boolean (*)(int,int)),"WIZCMDS dependency get_viz_clear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obj_sanity_check),void (*)(void)),"WIZCMDS dependency obj_sanity_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&timer_sanity_check),void (*)(void)),"WIZCMDS dependency timer_sanity_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_sanity_check),void (*)(void)),"WIZCMDS dependency mon_sanity_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&light_sources_sanity_check),void (*)(void)),"WIZCMDS dependency light_sources_sanity_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bc_sanity_check),void (*)(void)),"WIZCMDS dependency bc_sanity_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trap_sanity_check),void (*)(void)),"WIZCMDS dependency trap_sanity_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&engraving_sanity_check),void (*)(void)),"WIZCMDS dependency engraving_sanity_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strkitten),char * (*)(char *,char)),"WIZCMDS dependency strkitten");
_Static_assert(__builtin_types_compatible_p(__typeof__(&alloc),long * (*)(unsigned int)),"WIZCMDS dependency alloc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_deterministic_qsort),void (*)(void *,size_t,size_t,int (*)(const void *, const void *))),"WIZCMDS dependency nh_deterministic_qsort");
_Static_assert(__builtin_types_compatible_p(__typeof__(&minimal_monnam),char * (*)(struct monst *,boolean)),"WIZCMDS dependency minimal_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strsubst),char * (*)(char *,const char *,const char *)),"WIZCMDS dependency strsubst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&overview_stats),void (*)(winid,const char *,long *,long *)),"WIZCMDS dependency overview_stats");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_to_cmap),int (*)(int)),"WIZCMDS dependency glyph_to_cmap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mstrength),int (*)(struct permonst *)),"WIZCMDS dependency mstrength");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_snprintf),void (*)(const char *,int,char *,size_t,const char *,...)),"WIZCMDS dependency nh_snprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&memset),void * (*)(void *,int,size_t)),"WIZCMDS dependency memset");
_Static_assert(__builtin_types_compatible_p(__typeof__(&assign_level),void (*)(d_level *,d_level *)),"WIZCMDS dependency assign_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Is_botlevel),boolean (*)(d_level *)),"WIZCMDS dependency Is_botlevel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_level),void (*)(d_level *,int)),"WIZCMDS dependency get_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&depth),schar (*)(d_level *)),"WIZCMDS dependency depth");
_Static_assert(__builtin_types_compatible_p(__typeof__(&atoi),int (*)(const char *)),"WIZCMDS dependency atoi");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rndmonst),struct permonst * (*)(void)),"WIZCMDS dependency rndmonst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&makemon),struct monst * (*)(struct permonst *,coordxy,coordxy,mmflags_nht)),"WIZCMDS dependency makemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&migrate_to_level),void (*)(struct monst *,xint16,xint16,coord *)),"WIZCMDS dependency migrate_to_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ledger_no),xint16 (*)(d_level *)),"WIZCMDS dependency ledger_no");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyphid_cache_status),boolean (*)(void)),"WIZCMDS dependency glyphid_cache_status");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fill_glyphid_cache),void (*)(void)),"WIZCMDS dependency fill_glyphid_cache");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_menu_heading),void (*)(winid,const char *)),"WIZCMDS dependency add_menu_heading");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wizcustom_glyphids),void (*)(winid)),"WIZCMDS dependency wizcustom_glyphids");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_glyphid_cache),void (*)(void)),"WIZCMDS dependency free_glyphid_cache");
