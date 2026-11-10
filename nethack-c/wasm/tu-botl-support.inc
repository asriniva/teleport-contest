/* BOTL typed fields, aliases, callbacks and native dependency transport only. */
#include "hack.h"
#include "tu-botl-abi.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
void *teleport_botl_global(int index){switch(index){
case 0:return (void*)&objects;
case 1:return (void*)&flags;
case 2:return (void*)&iflags;
case 3:return (void*)&mons;
case 4:return (void*)&nul_glyphinfo;
case 5:return (void*)&conditions;
case 6:return (void*)&condtests;
case 7:return (void*)&cond_idx;
case 8:return (void*)&windowprocs;
case 9:return (void*)&roles;
case 10:return (void*)&uarm;
case 11:return (void*)&uarmc;
case 12:return (void*)&uarmh;
case 13:return (void*)&uarms;
case 14:return (void*)&uarmg;
case 15:return (void*)&uarmf;
case 16:return (void*)&uarmu;
case 17:return (void*)&uamul;
case 18:return (void*)&uleft;
case 19:return (void*)&uright;
case 20:return (void*)&uwep;
case 21:return (void*)&uswapwep;
case 22:return (void*)&u;
case 23:return (void*)&WIN_STATUS;
case 24:return (void*)&disp;
case 25:return (void*)&gb;
case 26:return (void*)&gc;
case 27:return (void*)&gi;
case 28:return (void*)&gm;
case 29:return (void*)&gn;
case 30:return (void*)&gs;
case 31:return (void*)&gu;
case 32:return (void*)&gv;
case 33:return (void*)&gy;
case 34:return (void*)&svc;
case 35:return (void*)&svd;
case 36:return (void*)&svl;
case 37:return (void*)&svm;
case 38:return (void*)&svp;
case 39:return (void*)&cg;
case 40:return (void*)&hu_stat;
case 41:return (void*)&enc_stat;
case 42:return (void*)&terrain_descr;
default:abort();}}
uint64_t teleport_botl_read(int kind,void*at,int field){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->name);
case 1:return (uint64_t)(uintptr_t)(&p->rank);
case 2:return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 1:{struct RoleName*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->m);
case 1:return (uint64_t)(uintptr_t)(p->f);
default:abort();}}
case 2:{struct teleport_botl__cond_map*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->bm);
case 1:return (uint64_t)(uintptr_t)(p->clratr);
default:abort();}}
case 3:{struct teleport_botl__status_hilite_line_str*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->id);
case 1:return (uint64_t)(uintptr_t)(p->fld);
case 2:return (uint64_t)(uintptr_t)(p->hl);
case 3:return (uint64_t)(uintptr_t)(p->mask);
case 4:return (uint64_t)(uintptr_t)(&p->str);
case 5:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 4:{struct hilite_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->fld);
case 1:return (uint64_t)(uintptr_t)(p->set);
case 2:return (uint64_t)(uintptr_t)(p->anytype);
case 3:return (uint64_t)(uintptr_t)(&p->value);
case 4:return (uint64_t)(uintptr_t)(p->behavior);
case 5:return (uint64_t)(uintptr_t)(&p->textmatch);
case 6:return (uint64_t)(uintptr_t)(p->rel);
case 7:return (uint64_t)(uintptr_t)(p->coloridx);
case 8:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->a_void);
case 1:return (uint64_t)(uintptr_t)(p->a_obj);
case 2:return (uint64_t)(uintptr_t)(p->a_monst);
case 3:return (uint64_t)(uintptr_t)(p->a_int);
case 4:return (uint64_t)(uintptr_t)(p->a_xint16);
case 5:return (uint64_t)(uintptr_t)(p->a_xint8);
case 6:return (uint64_t)(uintptr_t)(p->a_char);
case 7:return (uint64_t)(uintptr_t)(p->a_schar);
case 8:return (uint64_t)(uintptr_t)(p->a_uchar);
case 9:return (uint64_t)(uintptr_t)(p->a_uint);
case 10:return (uint64_t)(uintptr_t)(p->a_long);
case 11:return (uint64_t)(uintptr_t)(p->a_ulong);
case 12:return (uint64_t)(uintptr_t)(p->a_coordxy);
case 13:return (uint64_t)(uintptr_t)(p->a_iptr);
case 14:return (uint64_t)(uintptr_t)(p->a_xint16ptr);
case 15:return (uint64_t)(uintptr_t)(p->a_xint8ptr);
case 16:return (uint64_t)(uintptr_t)(p->a_lptr);
case 17:return (uint64_t)(uintptr_t)(p->a_coordxyptr);
case 18:return (uint64_t)(uintptr_t)(p->a_ulptr);
case 19:return (uint64_t)(uintptr_t)(p->a_uptr);
case 20:return (uint64_t)(uintptr_t)(p->a_string);
case 21:return (uint64_t)(uintptr_t)(p->a_nfunc);
case 22:return (uint64_t)(uintptr_t)(p->a_mask32);
case 23:return (uint64_t)(uintptr_t)(p->a_int64);
case 24:return (uint64_t)(uintptr_t)(p->a_uint64);
default:abort();}}
case 6:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->otyp);
case 1:return (uint64_t)(uintptr_t)(p->oclass);
case 2:return (uint64_t)(uintptr_t)(p->oartifact);
default:abort();}}
case 7:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
default:abort();}}
case 8:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mlet);
case 1:return (uint64_t)(uintptr_t)(p->mlevel);
case 2:return (uint64_t)(uintptr_t)(p->mflags1);
default:abort();}}
case 9:{struct align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 10:{struct conditions_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ranking);
case 1:return (uint64_t)(uintptr_t)(p->mask);
case 2:return (uint64_t)(uintptr_t)(p->c);
case 3:return (uint64_t)(uintptr_t)(&p->text);
default:abort();}}
case 11:{struct condmap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->id);
case 1:return (uint64_t)(uintptr_t)(p->bitmask);
default:abort();}}
case 12:{struct condtests_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c);
case 1:return (uint64_t)(uintptr_t)(p->useroption);
case 2:return (uint64_t)(uintptr_t)(p->opt);
case 3:return (uint64_t)(uintptr_t)(p->enabled);
case 4:return (uint64_t)(uintptr_t)(p->choice);
case 5:return (uint64_t)(uintptr_t)(p->test);
default:abort();}}
case 13:{struct const_globals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 14:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->rndencode);
default:abort();}}
case 15:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 16:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_astral_level);
case 1:return (uint64_t)(uintptr_t)(p->d_tutorial_dnum);
case 2:return (uint64_t)(uintptr_t)(&p->d_knox_level);
default:abort();}}
case 17:{struct display_hints*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->botl);
case 1:return (uint64_t)(uintptr_t)(p->botlx);
case 2:return (uint64_t)(uintptr_t)(p->time_botl);
default:abort();}}
case 18:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->locations);
default:abort();}}
case 19:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->typ);
default:abort();}}
case 20:{struct dungeon*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dname);
default:abort();}}
case 21:{struct teleport_botl_fieldid_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->fieldname);
case 1:return (uint64_t)(uintptr_t)(p->fldid);
default:abort();}}
case 22:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->armorstatus);
case 1:return (uint64_t)(uintptr_t)(p->female);
case 2:return (uint64_t)(uintptr_t)(p->showexp);
case 3:return (uint64_t)(uintptr_t)(p->showscore);
case 4:return (uint64_t)(uintptr_t)(p->showvers);
case 5:return (uint64_t)(uintptr_t)(p->terrainstatus);
case 6:return (uint64_t)(uintptr_t)(p->time);
case 7:return (uint64_t)(uintptr_t)(p->weaponstatus);
case 8:return (uint64_t)(uintptr_t)(p->versinfo);
default:abort();}}
case 23:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invis_goldsym);
case 1:return (uint64_t)(uintptr_t)(p->debug_fuzzer);
case 2:return (uint64_t)(uintptr_t)(p->in_dumplog);
case 3:return (uint64_t)(uintptr_t)(p->terrain_typ);
case 4:return (uint64_t)(uintptr_t)(p->status_updates);
case 5:return (uint64_t)(uintptr_t)(p->hilite_delta);
case 6:return (uint64_t)(uintptr_t)(p->wc2_hitpointbar);
default:abort();}}
case 24:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->blstats);
case 1:return (uint64_t)(uintptr_t)(p->blinit);
case 2:return (uint64_t)(uintptr_t)(p->bl_hilite_moves);
case 3:return (uint64_t)(uintptr_t)(p->bot_disabled);
default:abort();}}
case 25:{struct istat_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->fldname);
case 1:return (uint64_t)(uintptr_t)(p->fldfmt);
case 2:return (uint64_t)(uintptr_t)(p->time);
case 3:return (uint64_t)(uintptr_t)(p->chg);
case 4:return (uint64_t)(uintptr_t)(p->percent_matters);
case 5:return (uint64_t)(uintptr_t)(p->percent_value);
case 6:return (uint64_t)(uintptr_t)(p->anytype);
case 7:return (uint64_t)(uintptr_t)(&p->a);
case 8:return (uint64_t)(uintptr_t)(&p->rawval);
case 9:return (uint64_t)(uintptr_t)(p->val);
case 10:return (uint64_t)(uintptr_t)(p->valwidth);
case 11:return (uint64_t)(uintptr_t)(p->idxmax);
case 12:return (uint64_t)(uintptr_t)(p->fld);
case 13:return (uint64_t)(uintptr_t)(p->hilite_rule);
case 14:return (uint64_t)(uintptr_t)(p->thresholds);
default:abort();}}
case 26:{struct instance_globals_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->cond_hilites);
case 1:return (uint64_t)(uintptr_t)(p->condmenu_sortorder);
default:abort();}}
case 27:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 28:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mrank_sz);
case 1:return (uint64_t)(uintptr_t)(p->multi);
case 2:return (uint64_t)(uintptr_t)(p->multi_reason);
default:abort();}}
case 29:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->now_or_before_idx);
case 1:return (uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->showsyms);
default:abort();}}
case 31:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 32:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeons);
case 1:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 33:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 34:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
default:abort();}}
case 35:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 36:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->update_all);
case 1:return (uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 37:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->valset);
default:abort();}}
case 38:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 39:{struct mi*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 40:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_big);
case 1:return (uint64_t)(uintptr_t)(p->oc_subtyp);
default:abort();}}
case 41:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->blocked);
case 2:return (uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 42:{struct u_roleplay*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 43:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wincap2);
case 1:return (uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 2:return (uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 3:return (uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 4:return (uint64_t)(uintptr_t)(p->win_curs);
case 5:return (uint64_t)(uintptr_t)(p->win_putstr);
case 6:return (uint64_t)(uintptr_t)(p->win_putmixed);
case 7:return (uint64_t)(uintptr_t)(p->win_start_menu);
case 8:return (uint64_t)(uintptr_t)(p->win_end_menu);
case 9:return (uint64_t)(uintptr_t)(p->win_status_init);
case 10:return (uint64_t)(uintptr_t)(p->win_status_finish);
case 11:return (uint64_t)(uintptr_t)(p->win_status_enablefield);
case 12:return (uint64_t)(uintptr_t)(p->win_status_update);
default:abort();}}
case 44:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(&p->uz);
case 3:return (uint64_t)(uintptr_t)(p->ulevel);
case 4:return (uint64_t)(uintptr_t)(p->utrap);
case 5:return (uint64_t)(uintptr_t)(p->utraptype);
case 6:return (uint64_t)(uintptr_t)(p->uhs);
case 7:return (uint64_t)(uintptr_t)(&p->uprops);
case 8:return (uint64_t)(uintptr_t)(p->umconf);
case 9:return (uint64_t)(uintptr_t)(p->usick_type);
case 10:return (uint64_t)(uintptr_t)(p->umonster);
case 11:return (uint64_t)(uintptr_t)(p->umonnum);
case 12:return (uint64_t)(uintptr_t)(p->mh);
case 13:return (uint64_t)(uintptr_t)(p->mhmax);
case 14:return (uint64_t)(uintptr_t)(p->uswallow);
case 15:return (uint64_t)(uintptr_t)(p->uinwater);
case 16:return (uint64_t)(uintptr_t)(p->mfemale);
case 17:return (uint64_t)(uintptr_t)(&p->uroleplay);
case 18:return (uint64_t)(uintptr_t)(&p->ualign);
case 19:return (uint64_t)(uintptr_t)(p->uac);
case 20:return (uint64_t)(uintptr_t)(p->uhp);
case 21:return (uint64_t)(uintptr_t)(p->uhpmax);
case 22:return (uint64_t)(uintptr_t)(p->uen);
case 23:return (uint64_t)(uintptr_t)(p->uenmax);
case 24:return (uint64_t)(uintptr_t)(p->uexp);
case 25:return (uint64_t)(uintptr_t)(p->usleep);
case 26:return (uint64_t)(uintptr_t)(p->ustuck);
case 27:return (uint64_t)(uintptr_t)(p->usteed);
case 28:return (uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
case 45:{struct glyphinfo*p=at;switch(field){
default:abort();}}
default:abort();}}
void teleport_botl_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:memmove(&p->name, (void*)(uintptr_t)value,sizeof p->name);return;
case 2:p->mnum=value;return;
default:abort();}}
case 1:{struct RoleName*p=at;switch(field){
case 0:p->m=(void*)(uintptr_t)value;return;
case 1:p->f=(void*)(uintptr_t)value;return;
default:abort();}}
case 2:{struct teleport_botl__cond_map*p=at;switch(field){
case 0:p->bm=value;return;
case 1:p->clratr=value;return;
default:abort();}}
case 3:{struct teleport_botl__status_hilite_line_str*p=at;switch(field){
case 0:p->id=value;return;
case 1:p->fld=value;return;
case 2:p->hl=(void*)(uintptr_t)value;return;
case 3:p->mask=value;return;
case 5:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 4:{struct hilite_s*p=at;switch(field){
case 0:p->fld=value;return;
case 1:p->set=value;return;
case 2:p->anytype=value;return;
case 3:memmove(&p->value, (void*)(uintptr_t)value,sizeof p->value);return;
case 4:p->behavior=value;return;
case 6:p->rel=value;return;
case 7:p->coloridx=value;return;
case 8:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:p->a_void=(void*)(uintptr_t)value;return;
case 1:p->a_obj=(void*)(uintptr_t)value;return;
case 2:p->a_monst=(void*)(uintptr_t)value;return;
case 3:p->a_int=value;return;
case 4:p->a_xint16=value;return;
case 5:p->a_xint8=value;return;
case 6:p->a_char=value;return;
case 7:p->a_schar=value;return;
case 8:p->a_uchar=value;return;
case 9:p->a_uint=value;return;
case 10:p->a_long=value;return;
case 11:p->a_ulong=value;return;
case 12:p->a_coordxy=value;return;
case 13:p->a_iptr=(void*)(uintptr_t)value;return;
case 14:p->a_xint16ptr=(void*)(uintptr_t)value;return;
case 15:p->a_xint8ptr=(void*)(uintptr_t)value;return;
case 16:p->a_lptr=(void*)(uintptr_t)value;return;
case 17:p->a_coordxyptr=(void*)(uintptr_t)value;return;
case 18:p->a_ulptr=(void*)(uintptr_t)value;return;
case 19:p->a_uptr=(void*)(uintptr_t)value;return;
case 20:p->a_string=(void*)(uintptr_t)value;return;
case 21:p->a_nfunc=(__typeof__(p->a_nfunc))(uintptr_t)value;return;
case 22:p->a_mask32=value;return;
case 23:p->a_int64=value;return;
case 24:p->a_uint64=value;return;
default:abort();}}
case 6:{struct obj*p=at;switch(field){
case 0:p->otyp=value;return;
case 1:p->oclass=value;return;
case 2:p->oartifact=value;return;
default:abort();}}
case 7:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
default:abort();}}
case 8:{struct permonst*p=at;switch(field){
case 0:p->mlet=value;return;
case 1:p->mlevel=value;return;
case 2:p->mflags1=value;return;
default:abort();}}
case 9:{struct align*p=at;switch(field){
case 0:p->type=value;return;
default:abort();}}
case 10:{struct conditions_t*p=at;switch(field){
case 0:p->ranking=value;return;
case 1:p->mask=value;return;
case 2:p->c=value;return;
default:abort();}}
case 11:{struct condmap*p=at;switch(field){
case 0:p->id=(void*)(uintptr_t)value;return;
case 1:p->bitmask=value;return;
default:abort();}}
case 12:{struct condtests_t*p=at;switch(field){
case 0:p->c=value;return;
case 1:p->useroption=(void*)(uintptr_t)value;return;
case 2:p->opt=value;return;
case 3:p->enabled=value;return;
case 4:p->choice=value;return;
case 5:p->test=value;return;
default:abort();}}
case 13:{struct const_globals*p=at;switch(field){
default:abort();}}
case 14:{struct context_info*p=at;switch(field){
case 0:p->rndencode=value;return;
default:abort();}}
case 15:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 16:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_astral_level, (void*)(uintptr_t)value,sizeof p->d_astral_level);return;
case 1:p->d_tutorial_dnum=value;return;
case 2:memmove(&p->d_knox_level, (void*)(uintptr_t)value,sizeof p->d_knox_level);return;
default:abort();}}
case 17:{struct display_hints*p=at;switch(field){
case 0:p->botl=value;return;
case 1:p->botlx=value;return;
case 2:p->time_botl=value;return;
default:abort();}}
case 18:{dlevel_t*p=at;switch(field){
default:abort();}}
case 19:{struct rm*p=at;switch(field){
case 0:p->typ=value;return;
default:abort();}}
case 20:{struct dungeon*p=at;switch(field){
default:abort();}}
case 21:{struct teleport_botl_fieldid_t*p=at;switch(field){
case 0:p->fieldname=(void*)(uintptr_t)value;return;
case 1:p->fldid=value;return;
default:abort();}}
case 22:{struct flag*p=at;switch(field){
case 0:p->armorstatus=value;return;
case 1:p->female=value;return;
case 2:p->showexp=value;return;
case 3:p->showscore=value;return;
case 4:p->showvers=value;return;
case 5:p->terrainstatus=value;return;
case 6:p->time=value;return;
case 7:p->weaponstatus=value;return;
case 8:p->versinfo=value;return;
default:abort();}}
case 23:{struct instance_flags*p=at;switch(field){
case 0:p->invis_goldsym=value;return;
case 1:p->debug_fuzzer=value;return;
case 2:p->in_dumplog=value;return;
case 3:p->terrain_typ=value;return;
case 4:p->status_updates=value;return;
case 5:p->hilite_delta=value;return;
case 6:p->wc2_hitpointbar=value;return;
default:abort();}}
case 24:{struct instance_globals_b*p=at;switch(field){
case 1:p->blinit=value;return;
case 2:p->bl_hilite_moves=value;return;
case 3:p->bot_disabled=value;return;
default:abort();}}
case 25:{struct istat_s*p=at;switch(field){
case 0:p->fldname=(void*)(uintptr_t)value;return;
case 1:p->fldfmt=(void*)(uintptr_t)value;return;
case 2:p->time=value;return;
case 3:p->chg=value;return;
case 4:p->percent_matters=value;return;
case 5:p->percent_value=value;return;
case 6:p->anytype=value;return;
case 7:memmove(&p->a, (void*)(uintptr_t)value,sizeof p->a);return;
case 8:memmove(&p->rawval, (void*)(uintptr_t)value,sizeof p->rawval);return;
case 9:p->val=(void*)(uintptr_t)value;return;
case 10:p->valwidth=value;return;
case 11:p->idxmax=value;return;
case 12:p->fld=value;return;
case 13:p->hilite_rule=(void*)(uintptr_t)value;return;
case 14:p->thresholds=(void*)(uintptr_t)value;return;
default:abort();}}
case 26:{struct instance_globals_c*p=at;switch(field){
case 1:p->condmenu_sortorder=value;return;
default:abort();}}
case 27:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 28:{struct instance_globals_m*p=at;switch(field){
case 0:p->mrank_sz=value;return;
case 1:p->multi=value;return;
case 2:p->multi_reason=(void*)(uintptr_t)value;return;
default:abort();}}
case 29:{struct instance_globals_n*p=at;switch(field){
case 0:p->now_or_before_idx=value;return;
case 1:p->nomovemsg=(void*)(uintptr_t)value;return;
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
default:abort();}}
case 31:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context, (void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 32:{struct instance_globals_saved_d*p=at;switch(field){
case 1:memmove(&p->dungeon_topology, (void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 33:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level, (void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 34:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 35:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 36:{struct instance_globals_u*p=at;switch(field){
case 0:p->update_all=value;return;
case 1:memmove(&p->urole, (void*)(uintptr_t)value,sizeof p->urole);return;
default:abort();}}
case 37:{struct instance_globals_v*p=at;switch(field){
default:abort();}}
case 38:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst, (void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 39:{struct mi*p=at;switch(field){
case 0:memmove(&p->item, (void*)(uintptr_t)value,sizeof p->item);return;
default:abort();}}
case 40:{struct objclass*p=at;switch(field){
case 0:p->oc_big=value;return;
case 1:p->oc_subtyp=value;return;
default:abort();}}
case 41:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->blocked=value;return;
case 2:p->intrinsic=value;return;
default:abort();}}
case 42:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=value;return;
default:abort();}}
case 43:{struct window_procs*p=at;switch(field){
case 0:p->wincap2=value;return;
case 1:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))(uintptr_t)value;return;
case 2:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))(uintptr_t)value;return;
case 3:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))(uintptr_t)value;return;
case 4:p->win_curs=(__typeof__(p->win_curs))(uintptr_t)value;return;
case 5:p->win_putstr=(__typeof__(p->win_putstr))(uintptr_t)value;return;
case 6:p->win_putmixed=(__typeof__(p->win_putmixed))(uintptr_t)value;return;
case 7:p->win_start_menu=(__typeof__(p->win_start_menu))(uintptr_t)value;return;
case 8:p->win_end_menu=(__typeof__(p->win_end_menu))(uintptr_t)value;return;
case 9:p->win_status_init=(__typeof__(p->win_status_init))(uintptr_t)value;return;
case 10:p->win_status_finish=(__typeof__(p->win_status_finish))(uintptr_t)value;return;
case 11:p->win_status_enablefield=(__typeof__(p->win_status_enablefield))(uintptr_t)value;return;
case 12:p->win_status_update=(__typeof__(p->win_status_update))(uintptr_t)value;return;
default:abort();}}
case 44:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:memmove(&p->uz, (void*)(uintptr_t)value,sizeof p->uz);return;
case 3:p->ulevel=value;return;
case 4:p->utrap=value;return;
case 5:p->utraptype=value;return;
case 6:p->uhs=value;return;
case 8:p->umconf=value;return;
case 9:p->usick_type=value;return;
case 10:p->umonster=value;return;
case 11:p->umonnum=value;return;
case 12:p->mh=value;return;
case 13:p->mhmax=value;return;
case 14:p->uswallow=value;return;
case 15:p->uinwater=value;return;
case 16:p->mfemale=value;return;
case 17:memmove(&p->uroleplay, (void*)(uintptr_t)value,sizeof p->uroleplay);return;
case 18:memmove(&p->ualign, (void*)(uintptr_t)value,sizeof p->ualign);return;
case 19:p->uac=value;return;
case 20:p->uhp=value;return;
case 21:p->uhpmax=value;return;
case 22:p->uen=value;return;
case 23:p->uenmax=value;return;
case 24:p->uexp=value;return;
case 25:p->usleep=value;return;
case 26:p->ustuck=(void*)(uintptr_t)value;return;
case 27:p->usteed=(void*)(uintptr_t)value;return;
case 28:p->twoweap=value;return;
default:abort();}}
case 45:{struct glyphinfo*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_botl_address(int kind,void*at,int field){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:return (void*)&p->name;
case 1:return (void*)&p->rank;
case 2:return (void*)&p->mnum;
default:abort();}}
case 1:{struct RoleName*p=at;switch(field){
case 0:return (void*)&p->m;
case 1:return (void*)&p->f;
default:abort();}}
case 2:{struct teleport_botl__cond_map*p=at;switch(field){
case 0:return (void*)&p->bm;
case 1:return (void*)&p->clratr;
default:abort();}}
case 3:{struct teleport_botl__status_hilite_line_str*p=at;switch(field){
case 0:return (void*)&p->id;
case 1:return (void*)&p->fld;
case 2:return (void*)&p->hl;
case 3:return (void*)&p->mask;
case 4:return (void*)&p->str;
case 5:return (void*)&p->next;
default:abort();}}
case 4:{struct hilite_s*p=at;switch(field){
case 0:return (void*)&p->fld;
case 1:return (void*)&p->set;
case 2:return (void*)&p->anytype;
case 3:return (void*)&p->value;
case 4:return (void*)&p->behavior;
case 5:return (void*)&p->textmatch;
case 6:return (void*)&p->rel;
case 7:return (void*)&p->coloridx;
case 8:return (void*)&p->next;
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:return (void*)&p->a_void;
case 1:return (void*)&p->a_obj;
case 2:return (void*)&p->a_monst;
case 3:return (void*)&p->a_int;
case 4:return (void*)&p->a_xint16;
case 5:return (void*)&p->a_xint8;
case 6:return (void*)&p->a_char;
case 7:return (void*)&p->a_schar;
case 8:return (void*)&p->a_uchar;
case 9:return (void*)&p->a_uint;
case 10:return (void*)&p->a_long;
case 11:return (void*)&p->a_ulong;
case 12:return (void*)&p->a_coordxy;
case 13:return (void*)&p->a_iptr;
case 14:return (void*)&p->a_xint16ptr;
case 15:return (void*)&p->a_xint8ptr;
case 16:return (void*)&p->a_lptr;
case 17:return (void*)&p->a_coordxyptr;
case 18:return (void*)&p->a_ulptr;
case 19:return (void*)&p->a_uptr;
case 20:return (void*)&p->a_string;
case 21:return (void*)&p->a_nfunc;
case 22:return (void*)&p->a_mask32;
case 23:return (void*)&p->a_int64;
case 24:return (void*)&p->a_uint64;
default:abort();}}
case 6:{struct obj*p=at;switch(field){
case 0:return (void*)&p->otyp;
case 1:return (void*)&p->oclass;
case 2:return (void*)&p->oartifact;
default:abort();}}
case 7:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
default:abort();}}
case 8:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->mlet;
case 1:return (void*)&p->mlevel;
case 2:return (void*)&p->mflags1;
default:abort();}}
case 9:{struct align*p=at;switch(field){
case 0:return (void*)&p->type;
default:abort();}}
case 10:{struct conditions_t*p=at;switch(field){
case 0:return (void*)&p->ranking;
case 1:return (void*)&p->mask;
case 2:return (void*)&p->c;
case 3:return (void*)&p->text;
default:abort();}}
case 11:{struct condmap*p=at;switch(field){
case 0:return (void*)&p->id;
case 1:return (void*)&p->bitmask;
default:abort();}}
case 12:{struct condtests_t*p=at;switch(field){
case 0:return (void*)&p->c;
case 1:return (void*)&p->useroption;
case 2:return (void*)&p->opt;
case 3:return (void*)&p->enabled;
case 4:return (void*)&p->choice;
case 5:return (void*)&p->test;
default:abort();}}
case 13:{struct const_globals*p=at;switch(field){
case 0:return (void*)&p->zeroany;
default:abort();}}
case 14:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->rndencode;
default:abort();}}
case 15:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 16:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_astral_level;
case 1:return (void*)&p->d_tutorial_dnum;
case 2:return (void*)&p->d_knox_level;
default:abort();}}
case 17:{struct display_hints*p=at;switch(field){
case 0:return (void*)&p->botl;
case 1:return (void*)&p->botlx;
case 2:return (void*)&p->time_botl;
default:abort();}}
case 18:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->locations;
default:abort();}}
case 19:{struct rm*p=at;switch(field){
case 0:return (void*)&p->typ;
default:abort();}}
case 20:{struct dungeon*p=at;switch(field){
case 0:return (void*)&p->dname;
default:abort();}}
case 21:{struct teleport_botl_fieldid_t*p=at;switch(field){
case 0:return (void*)&p->fieldname;
case 1:return (void*)&p->fldid;
default:abort();}}
case 22:{struct flag*p=at;switch(field){
case 0:return (void*)&p->armorstatus;
case 1:return (void*)&p->female;
case 2:return (void*)&p->showexp;
case 3:return (void*)&p->showscore;
case 4:return (void*)&p->showvers;
case 5:return (void*)&p->terrainstatus;
case 6:return (void*)&p->time;
case 7:return (void*)&p->weaponstatus;
case 8:return (void*)&p->versinfo;
default:abort();}}
case 23:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->invis_goldsym;
case 1:return (void*)&p->debug_fuzzer;
case 2:return (void*)&p->in_dumplog;
case 3:return (void*)&p->terrain_typ;
case 4:return (void*)&p->status_updates;
case 5:return (void*)&p->hilite_delta;
case 6:return (void*)&p->wc2_hitpointbar;
default:abort();}}
case 24:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->blstats;
case 1:return (void*)&p->blinit;
case 2:return (void*)&p->bl_hilite_moves;
case 3:return (void*)&p->bot_disabled;
default:abort();}}
case 25:{struct istat_s*p=at;switch(field){
case 0:return (void*)&p->fldname;
case 1:return (void*)&p->fldfmt;
case 2:return (void*)&p->time;
case 3:return (void*)&p->chg;
case 4:return (void*)&p->percent_matters;
case 5:return (void*)&p->percent_value;
case 6:return (void*)&p->anytype;
case 7:return (void*)&p->a;
case 8:return (void*)&p->rawval;
case 9:return (void*)&p->val;
case 10:return (void*)&p->valwidth;
case 11:return (void*)&p->idxmax;
case 12:return (void*)&p->fld;
case 13:return (void*)&p->hilite_rule;
case 14:return (void*)&p->thresholds;
default:abort();}}
case 26:{struct instance_globals_c*p=at;switch(field){
case 0:return (void*)&p->cond_hilites;
case 1:return (void*)&p->condmenu_sortorder;
default:abort();}}
case 27:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 28:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->mrank_sz;
case 1:return (void*)&p->multi;
case 2:return (void*)&p->multi_reason;
default:abort();}}
case 29:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->now_or_before_idx;
case 1:return (void*)&p->nomovemsg;
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->showsyms;
default:abort();}}
case 31:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 32:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeons;
case 1:return (void*)&p->dungeon_topology;
default:abort();}}
case 33:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
default:abort();}}
case 34:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
default:abort();}}
case 35:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (void*)&p->plname;
default:abort();}}
case 36:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->update_all;
case 1:return (void*)&p->urole;
default:abort();}}
case 37:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->valset;
default:abort();}}
case 38:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 39:{struct mi*p=at;switch(field){
case 0:return (void*)&p->item;
default:abort();}}
case 40:{struct objclass*p=at;switch(field){
case 1:return (void*)&p->oc_subtyp;
default:abort();}}
case 41:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->blocked;
case 2:return (void*)&p->intrinsic;
default:abort();}}
case 42:{struct u_roleplay*p=at;switch(field){
case 0:return (void*)&p->deaf;
default:abort();}}
case 43:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->wincap2;
case 1:return (void*)&p->win_create_nhwindow;
case 2:return (void*)&p->win_display_nhwindow;
case 3:return (void*)&p->win_destroy_nhwindow;
case 4:return (void*)&p->win_curs;
case 5:return (void*)&p->win_putstr;
case 6:return (void*)&p->win_putmixed;
case 7:return (void*)&p->win_start_menu;
case 8:return (void*)&p->win_end_menu;
case 9:return (void*)&p->win_status_init;
case 10:return (void*)&p->win_status_finish;
case 11:return (void*)&p->win_status_enablefield;
case 12:return (void*)&p->win_status_update;
default:abort();}}
case 44:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->uz;
case 3:return (void*)&p->ulevel;
case 4:return (void*)&p->utrap;
case 5:return (void*)&p->utraptype;
case 6:return (void*)&p->uhs;
case 7:return (void*)&p->uprops;
case 8:return (void*)&p->umconf;
case 10:return (void*)&p->umonster;
case 11:return (void*)&p->umonnum;
case 12:return (void*)&p->mh;
case 13:return (void*)&p->mhmax;
case 17:return (void*)&p->uroleplay;
case 18:return (void*)&p->ualign;
case 19:return (void*)&p->uac;
case 20:return (void*)&p->uhp;
case 21:return (void*)&p->uhpmax;
case 22:return (void*)&p->uen;
case 23:return (void*)&p->uenmax;
case 24:return (void*)&p->uexp;
case 25:return (void*)&p->usleep;
case 26:return (void*)&p->ustuck;
case 27:return (void*)&p->usteed;
case 28:return (void*)&p->twoweap;
default:abort();}}
case 45:{struct glyphinfo*p=at;switch(field){
default:abort();}}
default:abort();}}
void*teleport_botl_literal(unsigned n){return malloc(n);}

#include "tu-botl-varargs.inc"
