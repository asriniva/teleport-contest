/* CMD typed ABI/backing only; all config algorithms/tables remain JS. */
#include "cmd-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "cmd-source-data.h"
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(va_list)==8 && sizeof(size_t)==8,"CMD memory64 long/pointer/va_list/size_t ABI");
_Static_assert(sizeof(int)==4 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"CMD scalar ABI");
_Static_assert(sizeof(int(*)(void))==8 && sizeof(int(*[3])(void))==24 && sizeof(int(*[10][3])(void))==240,"CMD function-pointer array ABI");
_Static_assert(sizeof(cmdcount_nht)==8 && sizeof(time_t)==8 && sizeof(coord)==4 && sizeof(coordxy)==2,"CMD count/time/coord ABI");
/* Source data/backing is emitted below; no initialized C source mirror. */
static int (*cmd_data_timed_occ_fn)(void);
static char * cmd_data_readchar_queue;
static char cmd_data_cmdnotavail[28];
static int (*cmd_data_move_funcs[10][3])(void);
static cmd_misc_key cmd_data_misc_keys[3];
static int cmd_data_extcmdlist_length;
static cmd_spkey_bind cmd_data_spkeys_binds[29];
static char cmd_local_doc_extcmd_flagstr_Abuf[10];
static char * cmd_local_doextlist_headings[2];
static char cmd_local_makemap_prepost_Unachieve[24];
static int cmd_local_extcmds_match_retmatchlist[171];
static char cmd_local_key2extcmddesc_key2cmdbuf[128];
static char cmd_local_cmd_from_ecname_cmdnamebuf[128];
static struct ext_func_tab * cmd_local_lock_mouse_buttons_mousebtn[2];
static char cmd_local_reset_commands_sdir[11];
static char cmd_local_reset_commands_sdir_swap_yz[11];
static char cmd_local_reset_commands_ndir[11];
static char cmd_local_reset_commands_ndir_phone_layout[11];
static int cmd_local_reset_commands_ylist[6];
static struct ext_func_tab * cmd_local_reset_commands_back_dir_cmd[8][3];
static unsigned char cmd_local_reset_commands_back_dir_key[8][3];
static signed char cmd_local_reset_commands_backed_dir_cmd;
static struct ext_func_tab cmd_local_update_rest_on_space_restonspace;
static struct ext_func_tab * cmd_local_update_rest_on_space_unrestonspace;
static unsigned int cmd_local_randomkey_i;
static char cmd_local_randomkey_last_c;
static char cmd_local_help_dir_wiz_only_list[7];
static char * cmd_local_directionname_dirnames[10];
void*teleport_cmd_global(int index){switch(index){
case 0:return(void*)&windowprocs;
case 1:return(void*)&gm;
case 2:return(void*)&go;
case 3:return(void*)&gc;
case 4:return(void*)&gi;
case 5:return(void*)&iflags;
case 6:return(void*)&gl;
case 7:return(void*)&nhcb_counts;
case 8:return(void*)&nhcb_name;
case 9:return(void*)&flags;
case 10:return(void*)&u;
case 11:return(void*)&ge;
case 12:return(void*)&cg;
case 13:return(void*)&nul_glyphinfo;
case 14:return(void*)&gy;
case 15:return(void*)&mons;
case 16:return(void*)&hidespinchars;
case 17:return(void*)&svl;
case 18:return(void*)&WIN_MESSAGE;
case 19:return(void*)&svd;
case 20:return(void*)&svc;
case 21:return(void*)&uball;
case 22:return(void*)&svu;
case 23:return(void*)&gv;
case 24:return(void*)&a11y;
case 25:return(void*)&xdir;
case 26:return(void*)&ydir;
case 27:return(void*)&zdir;
case 28:return(void*)&gd;
case 29:return(void*)&program_state;
case 30:return(void*)&gt;
case 31:return(void*)&gk;
case 32:return(void*)&c_common_strings;
case 33:return(void*)&quitchars;
case 34:return(void*)&dirs_ord;
case 35:return(void*)&defsyms;
case 36:return(void*)&gu;
case 37:return(void*)&soundprocs;
case 38:return(void*)&stdin;
case 39:return(void*)&ynchars;
case 40:return(void*)&ynqchars;
case 41:return(void*)&ynaqchars;
case 42:return(void*)&rightleftchars;
case 43:return(void*)&gs;
case 44:return(void*)&urealtime;
case 45:return(void*)&cmd_data_timed_occ_fn;
case 46:return(void*)&cmd_data_readchar_queue;
case 47:return(void*)&unavailcmd;
case 48:return(void*)&cmd_data_cmdnotavail;
case 49:return(void*)&levltyp;
case 50:return(void*)&extcmdlist;
case 51:return(void*)&cmd_data_move_funcs;
case 52:return(void*)&cmd_data_misc_keys;
case 53:return(void*)&cmd_data_extcmdlist_length;
case 54:return(void*)&cmd_data_spkeys_binds;
case 55:return(void*)&cmd_local_doc_extcmd_flagstr_Abuf;
case 56:return(void*)&cmd_local_doextlist_headings;
case 57:return(void*)&cmd_local_makemap_prepost_Unachieve;
case 58:return(void*)&cmd_local_extcmds_match_retmatchlist;
case 59:return(void*)&cmd_local_key2extcmddesc_key2cmdbuf;
case 60:return(void*)&cmd_local_cmd_from_ecname_cmdnamebuf;
case 61:return(void*)&cmd_local_lock_mouse_buttons_mousebtn;
case 62:return(void*)&cmd_local_reset_commands_sdir;
case 63:return(void*)&cmd_local_reset_commands_sdir_swap_yz;
case 64:return(void*)&cmd_local_reset_commands_ndir;
case 65:return(void*)&cmd_local_reset_commands_ndir_phone_layout;
case 66:return(void*)&cmd_local_reset_commands_ylist;
case 67:return(void*)&cmd_local_reset_commands_back_dir_cmd;
case 68:return(void*)&cmd_local_reset_commands_back_dir_key;
case 69:return(void*)&cmd_local_reset_commands_backed_dir_cmd;
case 70:return(void*)&cmd_local_update_rest_on_space_restonspace;
case 71:return(void*)&cmd_local_update_rest_on_space_unrestonspace;
case 72:return(void*)&cmd_local_randomkey_i;
case 73:return(void*)&cmd_local_randomkey_last_c;
case 74:return(void*)&cmd_local_help_dir_wiz_only_list;
case 75:return(void*)&cmd_local_directionname_dirnames;
default:abort();}}
uint64_t teleport_cmd_read(int kind,void*at,int field){switch(kind){
case 0:{struct Cmd_bind*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->key);
case 1:return(uint64_t)(uintptr_t)(p->userbind);
case 2:return(uint64_t)(uintptr_t)(p->param);
case 3:return(uint64_t)(uintptr_t)(p->cmd);
case 4:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{struct _cmd_queue*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->key);
case 2:return(uint64_t)(uintptr_t)(p->dirx);
case 3:return(uint64_t)(uintptr_t)(p->diry);
case 4:return(uint64_t)(uintptr_t)(p->dirz);
case 5:return(uint64_t)(uintptr_t)(p->intval);
case 6:return(uint64_t)(uintptr_t)(p->ec_entry);
case 7:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 3:{struct accessibility_data*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->accessiblemsg);
default:abort();}}
case 4:{struct achievement_tracking*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mines_prize_oid);
case 1:return(uint64_t)(uintptr_t)(p->soko_prize_oid);
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_int);
case 1:return(uint64_t)(uintptr_t)(p->a_char);
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_Never_mind);
default:abort();}}
case 7:{struct cmd*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->serialno);
case 1:return(uint64_t)(uintptr_t)(p->num_pad);
case 2:return(uint64_t)(uintptr_t)(p->pcHack_compat);
case 3:return(uint64_t)(uintptr_t)(p->phone_layout);
case 4:return(uint64_t)(uintptr_t)(p->swap_yz);
case 5:return(uint64_t)(uintptr_t)(p->dirchars);
case 6:return(uint64_t)(uintptr_t)(p->alphadirchars);
case 7:return(uint64_t)(uintptr_t)(p->cmdbinds);
case 8:return(uint64_t)(uintptr_t)(&p->mousebtn);
case 9:return(uint64_t)(uintptr_t)(&p->spkeys);
case 10:return(uint64_t)(uintptr_t)(p->extcmd_char);
default:abort();}}
case 8:{cmd_misc_key*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nhkf);
case 1:return(uint64_t)(uintptr_t)(p->desc);
case 2:return(uint64_t)(uintptr_t)(p->numpad);
default:abort();}}
case 9:{cmd_spkey_bind*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nhkf);
case 1:return(uint64_t)(uintptr_t)(p->key);
case 2:return(uint64_t)(uintptr_t)(p->name);
default:abort();}}
case 10:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroany);
case 1:return(uint64_t)(uintptr_t)(&p->zeroNhRect);
default:abort();}}
case 11:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->run);
case 1:return(uint64_t)(uintptr_t)(p->travel);
case 2:return(uint64_t)(uintptr_t)(p->travel1);
case 3:return(uint64_t)(uintptr_t)(p->forcefight);
case 4:return(uint64_t)(uintptr_t)(p->nopick);
case 5:return(uint64_t)(uintptr_t)(p->move);
case 6:return(uint64_t)(uintptr_t)(p->mv);
case 7:return(uint64_t)(uintptr_t)(&p->digging);
case 8:return(uint64_t)(uintptr_t)(&p->polearm);
case 9:return(uint64_t)(uintptr_t)(&p->achieveo);
default:abort();}}
case 12:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 13:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->d_tutorial_dnum);
case 1:return(uint64_t)(uintptr_t)(&p->d_mineend_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_sokoend_level);
default:abort();}}
case 14:{struct dig_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 15:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 16:{struct ext_func_tab*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->key);
case 1:return(uint64_t)(uintptr_t)(p->ef_txt);
case 2:return(uint64_t)(uintptr_t)(p->ef_desc);
case 3:return(uint64_t)(uintptr_t)(p->ef_funct);
case 4:return(uint64_t)(uintptr_t)(p->flags);
case 5:return(uint64_t)(uintptr_t)(p->f_text);
default:abort();}}
case 17:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
case 1:return(uint64_t)(uintptr_t)(p->explore);
case 2:return(uint64_t)(uintptr_t)(p->female);
case 3:return(uint64_t)(uintptr_t)(p->rest_on_space);
case 4:return(uint64_t)(uintptr_t)(p->paranoia_bits);
case 5:return(uint64_t)(uintptr_t)(p->showrace);
case 6:return(uint64_t)(uintptr_t)(p->travelcmd);
default:abort();}}
case 18:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->query_menu);
case 1:return(uint64_t)(uintptr_t)(p->debug_fuzzer);
case 2:return(uint64_t)(uintptr_t)(p->getdir_click);
case 3:return(uint64_t)(uintptr_t)(p->getloc_filter);
case 4:return(uint64_t)(uintptr_t)(p->last_msg);
case 5:return(uint64_t)(uintptr_t)(p->getloc_travelmode);
case 6:return(uint64_t)(uintptr_t)(&p->travelcc);
case 7:return(uint64_t)(uintptr_t)(p->window_inited);
case 8:return(uint64_t)(uintptr_t)(p->sanity_check);
case 9:return(uint64_t)(uintptr_t)(p->sanity_no_check);
case 10:return(uint64_t)(uintptr_t)(p->in_parse);
case 11:return(uint64_t)(uintptr_t)(p->altmeta);
case 12:return(uint64_t)(uintptr_t)(p->menu_requested);
case 13:return(uint64_t)(uintptr_t)(p->num_pad);
case 14:return(uint64_t)(uintptr_t)(p->num_pad_mode);
case 15:return(uint64_t)(uintptr_t)(p->extmenu);
case 16:return(uint64_t)(uintptr_t)(p->cmdassist);
case 17:return(uint64_t)(uintptr_t)(p->wc_eight_bit_input);
default:abort();}}
case 19:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->command_queue);
case 1:return(uint64_t)(uintptr_t)(&p->Cmd);
case 2:return(uint64_t)(uintptr_t)(&p->clicklook_cc);
case 3:return(uint64_t)(uintptr_t)(p->cmd_key);
case 4:return(uint64_t)(uintptr_t)(p->cmd_bind);
case 5:return(uint64_t)(uintptr_t)(p->command_count);
default:abort();}}
case 20:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->domove_attempting);
default:abort();}}
case 21:{struct instance_globals_e*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ext_tlist);
default:abort();}}
case 22:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_doagain);
case 1:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 23:{struct instance_globals_k*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->kickedloc);
default:abort();}}
case 24:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_command_count);
case 1:return(uint64_t)(uintptr_t)(p->luacore);
default:abort();}}
case 25:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->multi);
default:abort();}}
case 26:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->occupation);
case 1:return(uint64_t)(uintptr_t)(p->occtime);
case 2:return(uint64_t)(uintptr_t)(p->occtxt);
default:abort();}}
case 27:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->saved_pline_index);
default:abort();}}
case 28:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 29:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
case 1:return(uint64_t)(uintptr_t)(&p->dndest);
default:abort();}}
case 30:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 31:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->updest);
default:abort();}}
case 32:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->travelmap);
default:abort();}}
case 33:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 34:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->viz_array);
case 1:return(uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 35:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 36:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->arboreal);
default:abort();}}
case 37:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mgivenname);
default:abort();}}
case 38:{struct mi*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 39:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->cham);
case 2:return(uint64_t)(uintptr_t)(p->mtame);
case 3:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 4:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 40:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 41:{struct nhrect*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lx);
case 1:return(uint64_t)(uintptr_t)(p->ly);
case 2:return(uint64_t)(uintptr_t)(p->hx);
case 3:return(uint64_t)(uintptr_t)(p->hy);
default:abort();}}
case 42:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->v);
case 1:return(uint64_t)(uintptr_t)(p->otyp);
case 2:return(uint64_t)(uintptr_t)(p->oclass);
case 3:return(uint64_t)(uintptr_t)(p->invlet);
default:abort();}}
case 43:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mlet);
case 1:return(uint64_t)(uintptr_t)(p->msound);
case 2:return(uint64_t)(uintptr_t)(p->mflags1);
case 3:return(uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 44:{struct polearm_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hitmon);
default:abort();}}
case 45:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
case 1:return(uint64_t)(uintptr_t)(p->typ);
case 2:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 46:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->done_hup);
case 1:return(uint64_t)(uintptr_t)(p->something_worth_saving);
case 2:return(uint64_t)(uintptr_t)(p->exiting);
case 3:return(uint64_t)(uintptr_t)(p->in_moveloop);
case 4:return(uint64_t)(uintptr_t)(p->input_state);
default:abort();}}
case 47:{struct sound_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sound_exit_nhsound);
default:abort();}}
case 48:{struct stairway*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->up);
case 1:return(uint64_t)(uintptr_t)(p->isladder);
default:abort();}}
case 49:{struct symdef*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->explanation);
default:abort();}}
case 50:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ttyp);
case 1:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 51:{struct u_have*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->amulet);
default:abort();}}
case 52:{struct u_realtime*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->realtime);
case 1:return(uint64_t)(uintptr_t)(p->start_timing);
default:abort();}}
case 53:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 54:{volatile struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_exit_nhwindows);
case 1:return(uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 2:return(uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 3:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 4:return(uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 5:return(uint64_t)(uintptr_t)(p->win_putstr);
case 6:return(uint64_t)(uintptr_t)(p->win_start_menu);
case 7:return(uint64_t)(uintptr_t)(p->win_end_menu);
case 8:return(uint64_t)(uintptr_t)(p->win_mark_synch);
case 9:return(uint64_t)(uintptr_t)(p->win_wait_synch);
case 10:return(uint64_t)(uintptr_t)(p->win_nhgetch);
case 11:return(uint64_t)(uintptr_t)(p->win_nh_poskey);
case 12:return(uint64_t)(uintptr_t)(p->win_nhbell);
case 13:return(uint64_t)(uintptr_t)(p->win_doprev_message);
case 14:return(uint64_t)(uintptr_t)(p->win_yn_function);
case 15:return(uint64_t)(uintptr_t)(p->win_get_ext_cmd);
case 16:return(uint64_t)(uintptr_t)(p->win_putmsghistory);
case 17:return(uint64_t)(uintptr_t)(p->win_can_suspend);
default:abort();}}
case 55:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(p->dx);
case 3:return(uint64_t)(uintptr_t)(p->dy);
case 4:return(uint64_t)(uintptr_t)(p->dz);
case 5:return(uint64_t)(uintptr_t)(p->tx);
case 6:return(uint64_t)(uintptr_t)(p->ty);
case 7:return(uint64_t)(uintptr_t)(&p->uz);
case 8:return(uint64_t)(uintptr_t)(p->last_str_turn);
case 9:return(uint64_t)(uintptr_t)(&p->urooms);
case 10:return(uint64_t)(uintptr_t)(p->umonster);
case 11:return(uint64_t)(uintptr_t)(p->umonnum);
case 12:return(uint64_t)(uintptr_t)(p->uswldtim);
case 13:return(uint64_t)(uintptr_t)(p->uswallow);
case 14:return(uint64_t)(uintptr_t)(p->uundetected);
case 15:return(uint64_t)(uintptr_t)(p->mfemale);
case 16:return(uint64_t)(uintptr_t)(p->uburied);
case 17:return(uint64_t)(uintptr_t)(&p->uhave);
case 18:return(uint64_t)(uintptr_t)(p->ustuck);
case 19:return(uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
default:abort();}}
void teleport_cmd_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Cmd_bind*p=at;switch(field){
case 0:p->key=(uchar)value;return;
case 1:p->userbind=(boolean)value;return;
case 2:p->param=(char *)value;return;
case 3:p->cmd=(const struct ext_func_tab *)value;return;
case 4:p->next=(struct Cmd_bind *)value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->mnum=(short)value;return;
default:abort();}}
case 2:{struct _cmd_queue*p=at;switch(field){
case 0:p->typ=(int)value;return;
case 1:p->key=(char)value;return;
case 2:p->dirx=(schar)value;return;
case 3:p->diry=(schar)value;return;
case 4:p->dirz=(schar)value;return;
case 5:p->intval=(int)value;return;
case 6:p->ec_entry=(const struct ext_func_tab *)value;return;
case 7:p->next=(struct _cmd_queue *)value;return;
default:abort();}}
case 3:{struct accessibility_data*p=at;switch(field){
case 0:p->accessiblemsg=(boolean)value;return;
default:abort();}}
case 4:{struct achievement_tracking*p=at;switch(field){
case 0:p->mines_prize_oid=(unsigned int)value;return;
case 1:p->soko_prize_oid=(unsigned int)value;return;
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:p->a_int=(int)value;return;
case 1:p->a_char=(char)value;return;
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 7:{struct cmd*p=at;switch(field){
case 0:p->serialno=(unsigned int)value;return;
case 1:p->num_pad=(boolean)value;return;
case 2:p->pcHack_compat=(boolean)value;return;
case 3:p->phone_layout=(boolean)value;return;
case 4:p->swap_yz=(boolean)value;return;
case 5:p->dirchars=(const char *)value;return;
case 6:p->alphadirchars=(const char *)value;return;
case 7:p->cmdbinds=(struct Cmd_bind *)value;return;
case 10:p->extcmd_char=(char)value;return;
default:abort();}}
case 8:{cmd_misc_key*p=at;switch(field){
case 0:p->nhkf=(int)value;return;
case 1:p->desc=(const char *)value;return;
case 2:p->numpad=(boolean)value;return;
default:abort();}}
case 9:{cmd_spkey_bind*p=at;switch(field){
case 0:p->nhkf=(int)value;return;
case 1:p->key=(uchar)value;return;
case 2:p->name=(const char *)value;return;
default:abort();}}
case 10:{struct const_globals*p=at;switch(field){
default:abort();}}
case 11:{struct context_info*p=at;switch(field){
case 0:p->run=(unsigned int)value;return;
case 1:p->travel=(boolean)value;return;
case 2:p->travel1=(boolean)value;return;
case 3:p->forcefight=(boolean)value;return;
case 4:p->nopick=(boolean)value;return;
case 5:p->move=(boolean)value;return;
case 6:p->mv=(boolean)value;return;
default:abort();}}
case 12:{struct d_level*p=at;switch(field){
case 0:p->dnum=(xint16)value;return;
case 1:p->dlevel=(xint16)value;return;
default:abort();}}
case 13:{struct dgn_topology*p=at;switch(field){
case 0:p->d_tutorial_dnum=(xint16)value;return;
default:abort();}}
case 14:{struct dig_info*p=at;switch(field){
default:abort();}}
case 15:{dlevel_t*p=at;switch(field){
default:abort();}}
case 16:{struct ext_func_tab*p=at;switch(field){
case 0:p->key=(uchar)value;return;
case 1:p->ef_txt=(const char *)value;return;
case 2:p->ef_desc=(const char *)value;return;
case 3:p->ef_funct=(int (*)(void))value;return;
case 4:p->flags=(unsigned int)value;return;
case 5:p->f_text=(const char *)value;return;
default:abort();}}
case 17:{struct flag*p=at;switch(field){
case 0:p->debug=(boolean)value;return;
case 1:p->explore=(boolean)value;return;
case 2:p->female=(boolean)value;return;
case 3:p->rest_on_space=(boolean)value;return;
case 4:p->paranoia_bits=(unsigned int)value;return;
case 5:p->showrace=(boolean)value;return;
case 6:p->travelcmd=(boolean)value;return;
default:abort();}}
case 18:{struct instance_flags*p=at;switch(field){
case 0:p->query_menu=(boolean)value;return;
case 1:p->debug_fuzzer=(xint8)value;return;
case 2:p->getdir_click=(int)value;return;
case 3:p->getloc_filter=(int)value;return;
case 4:p->last_msg=(int)value;return;
case 5:p->getloc_travelmode=(boolean)value;return;
case 7:p->window_inited=(boolean)value;return;
case 8:p->sanity_check=(boolean)value;return;
case 9:p->sanity_no_check=(boolean)value;return;
case 10:p->in_parse=(boolean)value;return;
case 11:p->altmeta=(boolean)value;return;
case 12:p->menu_requested=(boolean)value;return;
case 13:p->num_pad=(boolean)value;return;
case 14:p->num_pad_mode=(uchar)value;return;
case 15:p->extmenu=(boolean)value;return;
case 16:p->cmdassist=(boolean)value;return;
case 17:p->wc_eight_bit_input=(boolean)value;return;
default:abort();}}
case 19:{struct instance_globals_c*p=at;switch(field){
case 3:p->cmd_key=(int)value;return;
case 4:p->cmd_bind=(struct Cmd_bind *)value;return;
case 5:p->command_count=(cmdcount_nht)value;return;
default:abort();}}
case 20:{struct instance_globals_d*p=at;switch(field){
case 0:p->domove_attempting=(long)value;return;
default:abort();}}
case 21:{struct instance_globals_e*p=at;switch(field){
case 0:p->ext_tlist=(struct ext_func_tab *)value;return;
default:abort();}}
case 22:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_doagain=(int)value;return;
case 1:p->invent=(struct obj *)value;return;
default:abort();}}
case 23:{struct instance_globals_k*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_l*p=at;switch(field){
case 0:p->last_command_count=(cmdcount_nht)value;return;
case 1:p->luacore=(genericptr_t)value;return;
default:abort();}}
case 25:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=(cmdcount_nht)value;return;
default:abort();}}
case 26:{struct instance_globals_o*p=at;switch(field){
case 0:p->occupation=(int (*)(void))value;return;
case 1:p->occtime=(int)value;return;
case 2:p->occtxt=(const char *)value;return;
default:abort();}}
case 27:{struct instance_globals_s*p=at;switch(field){
case 0:p->saved_pline_index=(unsigned int)value;return;
default:abort();}}
case 28:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 29:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 30:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 31:{struct instance_globals_saved_u*p=at;switch(field){
default:abort();}}
case 32:{struct instance_globals_t*p=at;switch(field){
case 0:p->travelmap=(struct selectionvar *)value;return;
default:abort();}}
case 33:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 34:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(seenV **)value;return;
case 1:p->vision_full_recalc=(boolean)value;return;
default:abort();}}
case 35:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 36:{struct levelflags*p=at;switch(field){
case 0:p->arboreal=(unsigned int)value;return;
default:abort();}}
case 37:{struct mextra*p=at;switch(field){
case 0:p->mgivenname=(char *)value;return;
default:abort();}}
case 38:{struct mi*p=at;switch(field){
default:abort();}}
case 39:{struct monst*p=at;switch(field){
case 0:p->data=(struct permonst *)value;return;
case 1:p->cham=(short)value;return;
case 2:p->mtame=(schar)value;return;
case 3:p->mpeaceful=(unsigned int)value;return;
case 4:p->mextra=(struct mextra *)value;return;
default:abort();}}
case 40:{struct nhcoord*p=at;switch(field){
case 0:p->x=(coordxy)value;return;
case 1:p->y=(coordxy)value;return;
default:abort();}}
case 41:{struct nhrect*p=at;switch(field){
case 0:p->lx=(coordxy)value;return;
case 1:p->ly=(coordxy)value;return;
case 2:p->hx=(coordxy)value;return;
case 3:p->hy=(coordxy)value;return;
default:abort();}}
case 42:{struct obj*p=at;switch(field){
case 1:p->otyp=(short)value;return;
case 2:p->oclass=(char)value;return;
case 3:p->invlet=(char)value;return;
default:abort();}}
case 43:{struct permonst*p=at;switch(field){
case 0:p->mlet=(char)value;return;
case 1:p->msound=(uchar)value;return;
case 2:p->mflags1=(unsigned long)value;return;
case 3:p->mflags2=(unsigned long)value;return;
default:abort();}}
case 44:{struct polearm_info*p=at;switch(field){
case 0:p->hitmon=(struct monst *)value;return;
default:abort();}}
case 45:{struct rm*p=at;switch(field){
case 0:p->glyph=(int)value;return;
case 1:p->typ=(schar)value;return;
case 2:p->flags=(unsigned int)value;return;
default:abort();}}
case 46:{struct sinfo*p=at;switch(field){
case 0:p->done_hup=(volatile int)value;return;
case 1:p->something_worth_saving=(int)value;return;
case 2:p->exiting=(int)value;return;
case 3:p->in_moveloop=(int)value;return;
case 4:p->input_state=(int)value;return;
default:abort();}}
case 47:{struct sound_procs*p=at;switch(field){
case 0:p->sound_exit_nhsound=(void (*)(const char *))value;return;
default:abort();}}
case 48:{struct stairway*p=at;switch(field){
case 0:p->up=(boolean)value;return;
case 1:p->isladder=(boolean)value;return;
default:abort();}}
case 49:{struct symdef*p=at;switch(field){
case 0:p->explanation=(const char *)value;return;
default:abort();}}
case 50:{struct trap*p=at;switch(field){
case 0:p->ttyp=(unsigned int)value;return;
case 1:p->tseen=(unsigned int)value;return;
default:abort();}}
case 51:{struct u_have*p=at;switch(field){
case 0:p->amulet=(unsigned int)value;return;
default:abort();}}
case 52:{struct u_realtime*p=at;switch(field){
case 0:p->realtime=(long)value;return;
case 1:p->start_timing=(time_t)value;return;
default:abort();}}
case 53:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(struct obj *)value;return;
default:abort();}}
case 54:{volatile struct window_procs*p=at;switch(field){
case 0:p->win_exit_nhwindows=(void (*)(const char *))value;return;
case 1:p->win_create_nhwindow=(winid (*)(int))value;return;
case 2:p->win_clear_nhwindow=(void (*)(winid))value;return;
case 3:p->win_display_nhwindow=(void (*)(winid, boolean))value;return;
case 4:p->win_destroy_nhwindow=(void (*)(winid))value;return;
case 5:p->win_putstr=(void (*)(winid, int, const char *))value;return;
case 6:p->win_start_menu=(void (*)(winid, unsigned long))value;return;
case 7:p->win_end_menu=(void (*)(winid, const char *))value;return;
case 8:p->win_mark_synch=(void (*)(void))value;return;
case 9:p->win_wait_synch=(void (*)(void))value;return;
case 10:p->win_nhgetch=(int (*)(void))value;return;
case 11:p->win_nh_poskey=(int (*)(coordxy *, coordxy *, int *))value;return;
case 12:p->win_nhbell=(void (*)(void))value;return;
case 13:p->win_doprev_message=(int (*)(void))value;return;
case 14:p->win_yn_function=(char (*)(const char *, const char *, char))value;return;
case 15:p->win_get_ext_cmd=(int (*)(void))value;return;
case 16:p->win_putmsghistory=(void (*)(const char *, boolean))value;return;
case 17:p->win_can_suspend=(boolean (*)(void))value;return;
default:abort();}}
case 55:{struct you*p=at;switch(field){
case 0:p->ux=(coordxy)value;return;
case 1:p->uy=(coordxy)value;return;
case 2:p->dx=(int)value;return;
case 3:p->dy=(int)value;return;
case 4:p->dz=(int)value;return;
case 5:p->tx=(coordxy)value;return;
case 6:p->ty=(coordxy)value;return;
case 8:p->last_str_turn=(int)value;return;
case 10:p->umonster=(int)value;return;
case 11:p->umonnum=(int)value;return;
case 12:p->uswldtim=(unsigned int)value;return;
case 13:p->uswallow=(unsigned int)value;return;
case 14:p->uundetected=(unsigned int)value;return;
case 15:p->mfemale=(unsigned int)value;return;
case 16:p->uburied=(unsigned int)value;return;
case 18:p->ustuck=(struct monst *)value;return;
case 19:p->usteed=(struct monst *)value;return;
default:abort();}}
default:abort();}}
void* teleport_cmd_address(int kind,void*at,int field){switch(kind){
case 0:{struct Cmd_bind*p=at;switch(field){
case 0:return(void*)&p->key;
case 1:return(void*)&p->userbind;
case 2:return(void*)&p->param;
case 3:return(void*)&p->cmd;
case 4:return(void*)&p->next;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{struct _cmd_queue*p=at;switch(field){
case 0:return(void*)&p->typ;
case 1:return(void*)&p->key;
case 2:return(void*)&p->dirx;
case 3:return(void*)&p->diry;
case 4:return(void*)&p->dirz;
case 5:return(void*)&p->intval;
case 6:return(void*)&p->ec_entry;
case 7:return(void*)&p->next;
default:abort();}}
case 3:{struct accessibility_data*p=at;switch(field){
case 0:return(void*)&p->accessiblemsg;
default:abort();}}
case 4:{struct achievement_tracking*p=at;switch(field){
case 0:return(void*)&p->mines_prize_oid;
case 1:return(void*)&p->soko_prize_oid;
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:return(void*)&p->a_int;
case 1:return(void*)&p->a_char;
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_Never_mind;
default:abort();}}
case 7:{struct cmd*p=at;switch(field){
case 0:return(void*)&p->serialno;
case 1:return(void*)&p->num_pad;
case 2:return(void*)&p->pcHack_compat;
case 3:return(void*)&p->phone_layout;
case 4:return(void*)&p->swap_yz;
case 5:return(void*)&p->dirchars;
case 6:return(void*)&p->alphadirchars;
case 7:return(void*)&p->cmdbinds;
case 8:return(void*)&p->mousebtn;
case 9:return(void*)&p->spkeys;
case 10:return(void*)&p->extcmd_char;
default:abort();}}
case 8:{cmd_misc_key*p=at;switch(field){
case 0:return(void*)&p->nhkf;
case 1:return(void*)&p->desc;
case 2:return(void*)&p->numpad;
default:abort();}}
case 9:{cmd_spkey_bind*p=at;switch(field){
case 0:return(void*)&p->nhkf;
case 1:return(void*)&p->key;
case 2:return(void*)&p->name;
default:abort();}}
case 10:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroany;
case 1:return(void*)&p->zeroNhRect;
default:abort();}}
case 11:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->run;
case 1:return(void*)&p->travel;
case 2:return(void*)&p->travel1;
case 3:return(void*)&p->forcefight;
case 4:return(void*)&p->nopick;
case 5:return(void*)&p->move;
case 6:return(void*)&p->mv;
case 7:return(void*)&p->digging;
case 8:return(void*)&p->polearm;
case 9:return(void*)&p->achieveo;
default:abort();}}
case 12:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 13:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_tutorial_dnum;
case 1:return(void*)&p->d_mineend_level;
case 2:return(void*)&p->d_sokoend_level;
default:abort();}}
case 14:{struct dig_info*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 15:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->flags;
default:abort();}}
case 16:{struct ext_func_tab*p=at;switch(field){
case 0:return(void*)&p->key;
case 1:return(void*)&p->ef_txt;
case 2:return(void*)&p->ef_desc;
case 3:return(void*)&p->ef_funct;
case 4:return(void*)&p->flags;
case 5:return(void*)&p->f_text;
default:abort();}}
case 17:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
case 1:return(void*)&p->explore;
case 2:return(void*)&p->female;
case 3:return(void*)&p->rest_on_space;
case 4:return(void*)&p->paranoia_bits;
case 5:return(void*)&p->showrace;
case 6:return(void*)&p->travelcmd;
default:abort();}}
case 18:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->query_menu;
case 1:return(void*)&p->debug_fuzzer;
case 2:return(void*)&p->getdir_click;
case 3:return(void*)&p->getloc_filter;
case 4:return(void*)&p->last_msg;
case 5:return(void*)&p->getloc_travelmode;
case 6:return(void*)&p->travelcc;
case 7:return(void*)&p->window_inited;
case 8:return(void*)&p->sanity_check;
case 9:return(void*)&p->sanity_no_check;
case 10:return(void*)&p->in_parse;
case 11:return(void*)&p->altmeta;
case 12:return(void*)&p->menu_requested;
case 13:return(void*)&p->num_pad;
case 14:return(void*)&p->num_pad_mode;
case 15:return(void*)&p->extmenu;
case 16:return(void*)&p->cmdassist;
case 17:return(void*)&p->wc_eight_bit_input;
default:abort();}}
case 19:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->command_queue;
case 1:return(void*)&p->Cmd;
case 2:return(void*)&p->clicklook_cc;
case 3:return(void*)&p->cmd_key;
case 4:return(void*)&p->cmd_bind;
case 5:return(void*)&p->command_count;
default:abort();}}
case 20:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->domove_attempting;
default:abort();}}
case 21:{struct instance_globals_e*p=at;switch(field){
case 0:return(void*)&p->ext_tlist;
default:abort();}}
case 22:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_doagain;
case 1:return(void*)&p->invent;
default:abort();}}
case 23:{struct instance_globals_k*p=at;switch(field){
case 0:return(void*)&p->kickedloc;
default:abort();}}
case 24:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->last_command_count;
case 1:return(void*)&p->luacore;
default:abort();}}
case 25:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->multi;
default:abort();}}
case 26:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->occupation;
case 1:return(void*)&p->occtime;
case 2:return(void*)&p->occtxt;
default:abort();}}
case 27:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->saved_pline_index;
default:abort();}}
case 28:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 29:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
case 1:return(void*)&p->dndest;
default:abort();}}
case 30:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 31:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return(void*)&p->updest;
default:abort();}}
case 32:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->travelmap;
default:abort();}}
case 33:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urace;
default:abort();}}
case 34:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->viz_array;
case 1:return(void*)&p->vision_full_recalc;
default:abort();}}
case 35:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 36:{struct levelflags*p=at;switch(field){
default:abort();}}
case 37:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->mgivenname;
default:abort();}}
case 38:{struct mi*p=at;switch(field){
case 0:return(void*)&p->item;
default:abort();}}
case 39:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 1:return(void*)&p->cham;
case 2:return(void*)&p->mtame;
case 4:return(void*)&p->mextra;
default:abort();}}
case 40:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 41:{struct nhrect*p=at;switch(field){
case 0:return(void*)&p->lx;
case 1:return(void*)&p->ly;
case 2:return(void*)&p->hx;
case 3:return(void*)&p->hy;
default:abort();}}
case 42:{struct obj*p=at;switch(field){
case 0:return(void*)&p->v;
case 1:return(void*)&p->otyp;
case 2:return(void*)&p->oclass;
case 3:return(void*)&p->invlet;
default:abort();}}
case 43:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->mlet;
case 1:return(void*)&p->msound;
case 2:return(void*)&p->mflags1;
case 3:return(void*)&p->mflags2;
default:abort();}}
case 44:{struct polearm_info*p=at;switch(field){
case 0:return(void*)&p->hitmon;
default:abort();}}
case 45:{struct rm*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->typ;
default:abort();}}
case 46:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->done_hup;
case 1:return(void*)&p->something_worth_saving;
case 2:return(void*)&p->exiting;
case 3:return(void*)&p->in_moveloop;
case 4:return(void*)&p->input_state;
default:abort();}}
case 47:{struct sound_procs*p=at;switch(field){
case 0:return(void*)&p->sound_exit_nhsound;
default:abort();}}
case 48:{struct stairway*p=at;switch(field){
case 0:return(void*)&p->up;
case 1:return(void*)&p->isladder;
default:abort();}}
case 49:{struct symdef*p=at;switch(field){
case 0:return(void*)&p->explanation;
default:abort();}}
case 50:{struct trap*p=at;switch(field){
default:abort();}}
case 51:{struct u_have*p=at;switch(field){
default:abort();}}
case 52:{struct u_realtime*p=at;switch(field){
case 0:return(void*)&p->realtime;
case 1:return(void*)&p->start_timing;
default:abort();}}
case 53:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
default:abort();}}
case 54:{volatile struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_exit_nhwindows;
case 1:return(void*)&p->win_create_nhwindow;
case 2:return(void*)&p->win_clear_nhwindow;
case 3:return(void*)&p->win_display_nhwindow;
case 4:return(void*)&p->win_destroy_nhwindow;
case 5:return(void*)&p->win_putstr;
case 6:return(void*)&p->win_start_menu;
case 7:return(void*)&p->win_end_menu;
case 8:return(void*)&p->win_mark_synch;
case 9:return(void*)&p->win_wait_synch;
case 10:return(void*)&p->win_nhgetch;
case 11:return(void*)&p->win_nh_poskey;
case 12:return(void*)&p->win_nhbell;
case 13:return(void*)&p->win_doprev_message;
case 14:return(void*)&p->win_yn_function;
case 15:return(void*)&p->win_get_ext_cmd;
case 16:return(void*)&p->win_putmsghistory;
case 17:return(void*)&p->win_can_suspend;
default:abort();}}
case 55:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->dx;
case 3:return(void*)&p->dy;
case 4:return(void*)&p->dz;
case 5:return(void*)&p->tx;
case 6:return(void*)&p->ty;
case 7:return(void*)&p->uz;
case 8:return(void*)&p->last_str_turn;
case 9:return(void*)&p->urooms;
case 10:return(void*)&p->umonster;
case 11:return(void*)&p->umonnum;
case 12:return(void*)&p->uswldtim;
case 17:return(void*)&p->uhave;
case 18:return(void*)&p->ustuck;
case 19:return(void*)&p->usteed;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_cmd_var0(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cmd_var1(char * a0){(You_cant)(a0);}
void teleport_cmd_var2(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
int teleport_cmd_var3(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var4(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var5(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var6(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var7(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var8(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var9(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var10(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var11(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var12(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_cmd_var13(char * a0){(There)(a0);}
void teleport_cmd_var14(char * a0){(You)(a0);}
void teleport_cmd_var15(char * a0){(pline)(a0);}
void teleport_cmd_var16(char * a0){(pline)(a0);}
void teleport_cmd_var17(char * a0){(You)(a0);}
void teleport_cmd_var18(char * a0){(You)(a0);}
void teleport_cmd_var19(char * a0){(You)(a0);}
void teleport_cmd_var20(char * a0){(pline)(a0);}
void teleport_cmd_var21(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cmd_var22(char * a0){(You)(a0);}
void teleport_cmd_var23(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cmd_var24(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cmd_var25(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cmd_var26(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_cmd_var27(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_cmd_var28(char * a0,char * a1){(You)(a0,a1);}
void teleport_cmd_var29(short a0,short a1,char * a2,char * a3){(pline_xy)(a0,a1,a2,a3);}
void teleport_cmd_var30(char * a0){(pline)(a0);}
void teleport_cmd_var31(char * a0,char * a1){(Norep)(a0,a1);}
void teleport_cmd_var32(char * a0){(Norep)(a0);}
void teleport_cmd_var33(char * a0){(Norep)(a0);}
void teleport_cmd_var34(char * a0){(Norep)(a0);}
void teleport_cmd_var35(char * a0){(Norep)(a0);}
int teleport_cmd_var36(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_cmd_var37(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var38(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_cmd_var39(char * a0){(pline)(a0);}
int teleport_cmd_var40(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var41(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var42(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var43(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var44(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_cmd_var45(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var46(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_cmd_var47(char * a0){(pline)(a0);}
void teleport_cmd_var48(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_cmd_var49(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_cmd_var50(char * a0){(pline)(a0);}
int teleport_cmd_var51(char * a0,char * a1,int a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var52(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var53(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var54(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_cmd_var55(char * a0,int a1){(config_error_add)(a0,a1);}
void teleport_cmd_var56(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_cmd_var57(char * a0){(config_error_add)(a0);}
void teleport_cmd_var58(char * a0,char * a1){(config_error_add)(a0,a1);}
int teleport_cmd_var59(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_cmd_var60(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var61(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var62(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var63(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var64(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var65(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var66(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var67(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var68(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var69(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
int teleport_cmd_var70(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var71(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var72(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
int teleport_cmd_var73(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_cmd_var74(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_cmd_var75(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_cmd_var76(char * a0,char * a1){return (sprintf)(a0,a1);}
void teleport_cmd_var77(char * a0,char * a1){(raw_printf)(a0,a1);}
int teleport_cmd_var78(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_cmd_var79(unsigned int a0,char * a1,char * a2,char * a3){(custompline)(a0,a1,a2,a3);}
void teleport_cmd_var80(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_cmd_var81(char * a0){(You_cant)(a0);}
void teleport_cmd_var82(unsigned int a0,char * a1,char * a2){(custompline)(a0,a1,a2);}
void teleport_cmd_var83(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cmd_var84(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cmd_var85(char * a0){(impossible)(a0);}
int teleport_cmd_var86(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_cmd_var87(char * a0,int a1){(impossible)(a0,a1);}
void teleport_cmd_var88(char * a0){(pline)(a0);}
void teleport_cmd_var89(char * a0){(You_cant)(a0);}
int teleport_cmd_var90(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var91(char * a0,char * a1,char * a2,int a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var92(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var93(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var94(char * a0,char * a1,char * a2,int a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var95(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var96(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var97(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var98(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var99(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_cmd_var100(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var101(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var102(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var103(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var104(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var105(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var106(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var107(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var108(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var109(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var110(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var111(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var112(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var113(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var114(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_cmd_var115(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_cmd_var116(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var117(char * a0){(impossible)(a0);}
int teleport_cmd_var118(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_cmd_var119(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var120(unsigned int a0,char * a1,char * a2){(custompline)(a0,a1,a2);}
int teleport_cmd_var121(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var122(char * a0){(pline)(a0);}
void teleport_cmd_var123(char * a0){(pline)(a0);}
void teleport_cmd_var124(char * a0){(You)(a0);}
void teleport_cmd_var125(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
int teleport_cmd_var126(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_cmd_var127(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,char * a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_cmd_var128(char * a0,char * a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_cmd_var129(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,char * a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_cmd_var130(char * a0,char * a1){(Norep)(a0,a1);}
int teleport_cmd_call0(int(*fn)(void)){return fn();}
winid teleport_cmd_call1(winid(*fn)(int),int a0){return fn(a0);}
void teleport_cmd_call2(void(*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_cmd_call3(void(*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_cmd_call4(void(*fn)(winid),winid a0){fn(a0);}
void teleport_cmd_call5(void(*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_cmd_call6(void(*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
void teleport_cmd_call7(void(*fn)(void)){fn();}
void teleport_cmd_call8(void(*fn)(const char *, boolean),const char * a0,boolean a1){fn(a0,a1);}
void teleport_cmd_call9(void(*fn)(const char *),const char * a0){fn(a0);}
int teleport_cmd_call10(int(*fn)(coordxy *, coordxy *, int *),coordxy * a0,coordxy * a1,int * a2){return fn(a0,a1,a2);}
char teleport_cmd_call11(char(*fn)(const char *, const char *, char),const char * a0,const char * a1,char a2){return fn(a0,a1,a2);}
boolean teleport_cmd_call12(boolean(*fn)(void)){return fn();}
#pragma clang diagnostic pop
void*teleport_cmd_copy(void*to,const void*from,size_t n){return memcpy(to,from,n);}
extern int teleport_cmd_doprev_message(void);
extern int teleport_cmd_timed_occupation(void);
extern boolean teleport_cmd_can_do_extcmd(const struct ext_func_tab * extcmd);
extern char * teleport_cmd_doc_extcmd_flagstr(winid menuwin,const struct ext_func_tab * efp);
extern int teleport_cmd_doterrain(void);
extern boolean teleport_cmd_u_have_seen_whole_selection(struct selectionvar * sel);
extern boolean teleport_cmd_u_have_seen_bounds_selection(struct selectionvar * sel);
extern boolean teleport_cmd_u_can_see_whole_selection(struct selectionvar * sel);
extern int teleport_cmd_dolookaround_floodfill_findroom(coordxy x,coordxy y);
extern void teleport_cmd_lookaround_known_room(coordxy x,coordxy y);
extern struct Cmd_bind * teleport_cmd_cmdbind_get(uchar key);
extern void teleport_cmd_cmdbind_add(uchar key,const struct ext_func_tab * extcmd,boolean user);
extern void teleport_cmd_cmdbind_remove(uchar key);
extern void teleport_cmd_cmdbind_swapkeys(uchar key1,uchar key2);
extern void teleport_cmd_handler_rebind_keys_add(boolean keyfirst);
extern boolean teleport_cmd_bind_key_fn(uchar key,int (*fn)(void));
extern void teleport_cmd_commands_init(void);
extern boolean teleport_cmd_keylist_func_has_key(const struct ext_func_tab * extcmd,boolean * skip_keys_used);
extern int teleport_cmd_keylist_putcmds(winid datawin,boolean docount,int incl_flags,int excl_flags,boolean * keys_used);
extern const char * teleport_cmd_spkey_name(int nhkf);
extern boolean teleport_cmd_accept_menu_prefix(const struct ext_func_tab * ec);
extern void teleport_cmd_reset_cmd_vars(boolean reset_cmdq);
extern void teleport_cmd_show_direction_keys(winid win,char centerchar,boolean nodiag);
extern boolean teleport_cmd_help_dir(char sym,uchar spkey,const char * msg);
extern int teleport_cmd_doherecmdmenu(void);
extern int teleport_cmd_dotherecmdmenu(void);
extern void teleport_cmd_mcmd_addmenu(winid win,int act,const char * txt);
extern int teleport_cmd_there_cmd_menu_self(winid win,coordxy x,coordxy y,int * act);
extern int teleport_cmd_there_cmd_menu_next2u(winid win,coordxy x,coordxy y,int mod,int * act);
extern int teleport_cmd_there_cmd_menu_far(winid win,coordxy x,coordxy y,int mod);
extern int teleport_cmd_there_cmd_menu_common(winid win,coordxy x,coordxy y,int mod,int * act);
extern void teleport_cmd_act_on_act(int act,coordxy dx,coordxy dy);
extern char teleport_cmd_there_cmd_menu(coordxy x,coordxy y,int mod);
extern char teleport_cmd_here_cmd_menu(void);
extern int teleport_cmd_domouseaction(void);
extern int teleport_cmd_parse(void);
extern char teleport_cmd_readchar_core(coordxy * x,coordxy * y,int * mod);
extern int teleport_cmd_dotravel(void);
extern int teleport_cmd_dotravel_target(void);
extern int teleport_cmd_doclicklook(void);
extern boolean teleport_cmd_yn_menuable_resp(const char * resp);
extern void teleport_cmd_yn_func_menu_opt(winid win,char key,const char * text,char def);
extern boolean teleport_cmd_yn_function_menu(const char * query,const char * resp,char def,char * res);
extern int teleport_cmd_dosuspend_core(void);
extern int teleport_cmd_dosh_core(void);
extern int teleport_cmd_dummyfunction(void);
uintptr_t teleport_cmd_function0(void){return(uintptr_t)teleport_cmd_timed_occupation;}
uintptr_t teleport_cmd_function1(void){return(uintptr_t)do_reqmenu;}
uintptr_t teleport_cmd_function2(void){return(uintptr_t)doextlist;}
uintptr_t teleport_cmd_function3(void){return(uintptr_t)teleport_cmd_dolookaround_floodfill_findroom;}
uintptr_t teleport_cmd_function4(void){return(uintptr_t)doextcmd;}
uintptr_t teleport_cmd_function5(void){return(uintptr_t)doorganize;}
uintptr_t teleport_cmd_function6(void){return(uintptr_t)donamelevel;}
uintptr_t teleport_cmd_function7(void){return(uintptr_t)doapply;}
uintptr_t teleport_cmd_function8(void){return(uintptr_t)doattributes;}
uintptr_t teleport_cmd_function9(void){return(uintptr_t)dotogglepickup;}
uintptr_t teleport_cmd_function10(void){return(uintptr_t)dobugreport;}
uintptr_t teleport_cmd_function11(void){return(uintptr_t)docallcmd;}
uintptr_t teleport_cmd_function12(void){return(uintptr_t)docast;}
uintptr_t teleport_cmd_function13(void){return(uintptr_t)dotalk;}
uintptr_t teleport_cmd_function14(void){return(uintptr_t)do_gamelog;}
uintptr_t teleport_cmd_function15(void){return(uintptr_t)doclose;}
uintptr_t teleport_cmd_function16(void){return(uintptr_t)doconduct;}
uintptr_t teleport_cmd_function17(void){return(uintptr_t)wiz_fuzzer;}
uintptr_t teleport_cmd_function18(void){return(uintptr_t)dodip;}
uintptr_t teleport_cmd_function19(void){return(uintptr_t)dodown;}
uintptr_t teleport_cmd_function20(void){return(uintptr_t)dodrop;}
uintptr_t teleport_cmd_function21(void){return(uintptr_t)doddrop;}
uintptr_t teleport_cmd_function22(void){return(uintptr_t)doeat;}
uintptr_t teleport_cmd_function23(void){return(uintptr_t)doengrave;}
uintptr_t teleport_cmd_function24(void){return(uintptr_t)enhance_weapon_skill;}
uintptr_t teleport_cmd_function25(void){return(uintptr_t)enter_explore_mode;}
uintptr_t teleport_cmd_function26(void){return(uintptr_t)do_fight;}
uintptr_t teleport_cmd_function27(void){return(uintptr_t)dofire;}
uintptr_t teleport_cmd_function28(void){return(uintptr_t)doforce;}
uintptr_t teleport_cmd_function29(void){return(uintptr_t)dogenocided;}
uintptr_t teleport_cmd_function30(void){return(uintptr_t)doquickwhatis;}
uintptr_t teleport_cmd_function31(void){return(uintptr_t)dohelp;}
uintptr_t teleport_cmd_function32(void){return(uintptr_t)teleport_cmd_doherecmdmenu;}
uintptr_t teleport_cmd_function33(void){return(uintptr_t)dohistory;}
uintptr_t teleport_cmd_function34(void){return(uintptr_t)ddoinv;}
uintptr_t teleport_cmd_function35(void){return(uintptr_t)dotypeinv;}
uintptr_t teleport_cmd_function36(void){return(uintptr_t)doinvoke;}
uintptr_t teleport_cmd_function37(void){return(uintptr_t)dojump;}
uintptr_t teleport_cmd_function38(void){return(uintptr_t)dokick;}
uintptr_t teleport_cmd_function39(void){return(uintptr_t)dodiscovered;}
uintptr_t teleport_cmd_function40(void){return(uintptr_t)doclassdisco;}
uintptr_t teleport_cmd_function41(void){return(uintptr_t)wiz_level_change;}
uintptr_t teleport_cmd_function42(void){return(uintptr_t)wiz_light_sources;}
uintptr_t teleport_cmd_function43(void){return(uintptr_t)dolook;}
uintptr_t teleport_cmd_function44(void){return(uintptr_t)dolookaround;}
uintptr_t teleport_cmd_function45(void){return(uintptr_t)doloot;}
uintptr_t teleport_cmd_function46(void){return(uintptr_t)wiz_migrate_mons;}
uintptr_t teleport_cmd_function47(void){return(uintptr_t)domonability;}
uintptr_t teleport_cmd_function48(void){return(uintptr_t)dosacrifice;}
uintptr_t teleport_cmd_function49(void){return(uintptr_t)doopen;}
uintptr_t teleport_cmd_function50(void){return(uintptr_t)doset_simple;}
uintptr_t teleport_cmd_function51(void){return(uintptr_t)doset;}
uintptr_t teleport_cmd_function52(void){return(uintptr_t)dooverview;}
uintptr_t teleport_cmd_function53(void){return(uintptr_t)wiz_panic;}
uintptr_t teleport_cmd_function54(void){return(uintptr_t)dopay;}
uintptr_t teleport_cmd_function55(void){return(uintptr_t)doperminv;}
uintptr_t teleport_cmd_function56(void){return(uintptr_t)dopickup;}
uintptr_t teleport_cmd_function57(void){return(uintptr_t)wiz_polyself;}
uintptr_t teleport_cmd_function58(void){return(uintptr_t)dopray;}
uintptr_t teleport_cmd_function59(void){return(uintptr_t)teleport_cmd_doprev_message;}
uintptr_t teleport_cmd_function60(void){return(uintptr_t)doputon;}
uintptr_t teleport_cmd_function61(void){return(uintptr_t)dodrink;}
uintptr_t teleport_cmd_function62(void){return(uintptr_t)done2;}
uintptr_t teleport_cmd_function63(void){return(uintptr_t)dowieldquiver;}
uintptr_t teleport_cmd_function64(void){return(uintptr_t)doread;}
uintptr_t teleport_cmd_function65(void){return(uintptr_t)doredraw;}
uintptr_t teleport_cmd_function66(void){return(uintptr_t)doremring;}
uintptr_t teleport_cmd_function67(void){return(uintptr_t)do_repeat;}
uintptr_t teleport_cmd_function68(void){return(uintptr_t)teleport_cmd_dotravel_target;}
uintptr_t teleport_cmd_function69(void){return(uintptr_t)doride;}
uintptr_t teleport_cmd_function70(void){return(uintptr_t)dorub;}
uintptr_t teleport_cmd_function71(void){return(uintptr_t)do_run;}
uintptr_t teleport_cmd_function72(void){return(uintptr_t)do_rush;}
uintptr_t teleport_cmd_function73(void){return(uintptr_t)dosave;}
uintptr_t teleport_cmd_function74(void){return(uintptr_t)do_write_config_file;}
uintptr_t teleport_cmd_function75(void){return(uintptr_t)dosearch;}
uintptr_t teleport_cmd_function76(void){return(uintptr_t)doprinuse;}
uintptr_t teleport_cmd_function77(void){return(uintptr_t)dopramulet;}
uintptr_t teleport_cmd_function78(void){return(uintptr_t)doprarm;}
uintptr_t teleport_cmd_function79(void){return(uintptr_t)doprring;}
uintptr_t teleport_cmd_function80(void){return(uintptr_t)doprtool;}
uintptr_t teleport_cmd_function81(void){return(uintptr_t)doprwep;}
uintptr_t teleport_cmd_function82(void){return(uintptr_t)teleport_cmd_dosh_core;}
uintptr_t teleport_cmd_function83(void){return(uintptr_t)doprgold;}
uintptr_t teleport_cmd_function84(void){return(uintptr_t)dovspell;}
uintptr_t teleport_cmd_function85(void){return(uintptr_t)doidtrap;}
uintptr_t teleport_cmd_function86(void){return(uintptr_t)dosit;}
uintptr_t teleport_cmd_function87(void){return(uintptr_t)wiz_show_stats;}
uintptr_t teleport_cmd_function88(void){return(uintptr_t)teleport_cmd_dosuspend_core;}
uintptr_t teleport_cmd_function89(void){return(uintptr_t)doswapweapon;}
uintptr_t teleport_cmd_function90(void){return(uintptr_t)dotakeoff;}
uintptr_t teleport_cmd_function91(void){return(uintptr_t)doddoremarm;}
uintptr_t teleport_cmd_function92(void){return(uintptr_t)dotelecmd;}
uintptr_t teleport_cmd_function93(void){return(uintptr_t)teleport_cmd_doterrain;}
uintptr_t teleport_cmd_function94(void){return(uintptr_t)teleport_cmd_dotherecmdmenu;}
uintptr_t teleport_cmd_function95(void){return(uintptr_t)dothrow;}
uintptr_t teleport_cmd_function96(void){return(uintptr_t)wiz_timeout_queue;}
uintptr_t teleport_cmd_function97(void){return(uintptr_t)dotip;}
uintptr_t teleport_cmd_function98(void){return(uintptr_t)dotoggleoption;}
uintptr_t teleport_cmd_function99(void){return(uintptr_t)teleport_cmd_dotravel;}
uintptr_t teleport_cmd_function100(void){return(uintptr_t)doturn;}
uintptr_t teleport_cmd_function101(void){return(uintptr_t)dotwoweapon;}
uintptr_t teleport_cmd_function102(void){return(uintptr_t)dountrap;}
uintptr_t teleport_cmd_function103(void){return(uintptr_t)doup;}
uintptr_t teleport_cmd_function104(void){return(uintptr_t)dovanquished;}
uintptr_t teleport_cmd_function105(void){return(uintptr_t)doextversion;}
uintptr_t teleport_cmd_function106(void){return(uintptr_t)doversion;}
uintptr_t teleport_cmd_function107(void){return(uintptr_t)wiz_show_vision;}
uintptr_t teleport_cmd_function108(void){return(uintptr_t)donull;}
uintptr_t teleport_cmd_function109(void){return(uintptr_t)dowear;}
uintptr_t teleport_cmd_function110(void){return(uintptr_t)dowhatdoes;}
uintptr_t teleport_cmd_function111(void){return(uintptr_t)dowhatis;}
uintptr_t teleport_cmd_function112(void){return(uintptr_t)dowield;}
uintptr_t teleport_cmd_function113(void){return(uintptr_t)dowipe;}
uintptr_t teleport_cmd_function114(void){return(uintptr_t)doborn;}
uintptr_t teleport_cmd_function115(void){return(uintptr_t)wiz_debug_cmd_bury;}
uintptr_t teleport_cmd_function116(void){return(uintptr_t)dowizcast;}
uintptr_t teleport_cmd_function117(void){return(uintptr_t)wiz_custom;}
uintptr_t teleport_cmd_function118(void){return(uintptr_t)wiz_detect;}
uintptr_t teleport_cmd_function119(void){return(uintptr_t)wiz_display_macros;}
uintptr_t teleport_cmd_function120(void){return(uintptr_t)wiz_flip_level;}
uintptr_t teleport_cmd_function121(void){return(uintptr_t)wiz_genesis;}
uintptr_t teleport_cmd_function122(void){return(uintptr_t)wiz_identify;}
uintptr_t teleport_cmd_function123(void){return(uintptr_t)wiz_intrinsic;}
uintptr_t teleport_cmd_function124(void){return(uintptr_t)wiz_kill;}
uintptr_t teleport_cmd_function125(void){return(uintptr_t)wiz_level_tele;}
uintptr_t teleport_cmd_function126(void){return(uintptr_t)wiz_load_splua;}
uintptr_t teleport_cmd_function127(void){return(uintptr_t)wiz_load_lua;}
uintptr_t teleport_cmd_function128(void){return(uintptr_t)wiz_objprobs;}
uintptr_t teleport_cmd_function129(void){return(uintptr_t)wiz_makemap;}
uintptr_t teleport_cmd_function130(void){return(uintptr_t)wiz_map;}
uintptr_t teleport_cmd_function131(void){return(uintptr_t)wiz_mon_diff;}
uintptr_t teleport_cmd_function132(void){return(uintptr_t)wiz_rumor_check;}
uintptr_t teleport_cmd_function133(void){return(uintptr_t)wiz_show_seenv;}
uintptr_t teleport_cmd_function134(void){return(uintptr_t)wiz_show_nhuuid;}
uintptr_t teleport_cmd_function135(void){return(uintptr_t)wiz_smell;}
uintptr_t teleport_cmd_function136(void){return(uintptr_t)wiz_telekinesis;}
uintptr_t teleport_cmd_function137(void){return(uintptr_t)wiz_where;}
uintptr_t teleport_cmd_function138(void){return(uintptr_t)wiz_wish;}
uintptr_t teleport_cmd_function139(void){return(uintptr_t)wiz_show_wmodes;}
uintptr_t teleport_cmd_function140(void){return(uintptr_t)dozap;}
uintptr_t teleport_cmd_function141(void){return(uintptr_t)do_move_west;}
uintptr_t teleport_cmd_function142(void){return(uintptr_t)do_move_northwest;}
uintptr_t teleport_cmd_function143(void){return(uintptr_t)do_move_north;}
uintptr_t teleport_cmd_function144(void){return(uintptr_t)do_move_northeast;}
uintptr_t teleport_cmd_function145(void){return(uintptr_t)do_move_east;}
uintptr_t teleport_cmd_function146(void){return(uintptr_t)do_move_southeast;}
uintptr_t teleport_cmd_function147(void){return(uintptr_t)do_move_south;}
uintptr_t teleport_cmd_function148(void){return(uintptr_t)do_move_southwest;}
uintptr_t teleport_cmd_function149(void){return(uintptr_t)do_rush_west;}
uintptr_t teleport_cmd_function150(void){return(uintptr_t)do_rush_northwest;}
uintptr_t teleport_cmd_function151(void){return(uintptr_t)do_rush_north;}
uintptr_t teleport_cmd_function152(void){return(uintptr_t)do_rush_northeast;}
uintptr_t teleport_cmd_function153(void){return(uintptr_t)do_rush_east;}
uintptr_t teleport_cmd_function154(void){return(uintptr_t)do_rush_southeast;}
uintptr_t teleport_cmd_function155(void){return(uintptr_t)do_rush_south;}
uintptr_t teleport_cmd_function156(void){return(uintptr_t)do_rush_southwest;}
uintptr_t teleport_cmd_function157(void){return(uintptr_t)do_run_west;}
uintptr_t teleport_cmd_function158(void){return(uintptr_t)do_run_northwest;}
uintptr_t teleport_cmd_function159(void){return(uintptr_t)do_run_north;}
uintptr_t teleport_cmd_function160(void){return(uintptr_t)do_run_northeast;}
uintptr_t teleport_cmd_function161(void){return(uintptr_t)do_run_east;}
uintptr_t teleport_cmd_function162(void){return(uintptr_t)do_run_southeast;}
uintptr_t teleport_cmd_function163(void){return(uintptr_t)do_run_south;}
uintptr_t teleport_cmd_function164(void){return(uintptr_t)do_run_southwest;}
uintptr_t teleport_cmd_function165(void){return(uintptr_t)teleport_cmd_doclicklook;}
uintptr_t teleport_cmd_function166(void){return(uintptr_t)teleport_cmd_domouseaction;}
uintptr_t teleport_cmd_function167(void){return(uintptr_t)adjust_split;}
uintptr_t teleport_cmd_function168(void){return(uintptr_t)dip_into;}
uintptr_t teleport_cmd_function169(void){return(uintptr_t)ia_dotakeoff;}
uintptr_t teleport_cmd_function170(void){return(uintptr_t)remarm_swapwep;}
uintptr_t teleport_cmd_function171(void){return(uintptr_t)teleport_cmd_dummyfunction;}
#include "cmd-source-data.h"
static char cmd_literals[CMD_LITERAL_CAPACITY];
char*teleport_cmd_literal_storage(void){return cmd_literals;}
size_t teleport_cmd_literal_capacity(void){return sizeof cmd_literals;}
int teleport_cmd_screen_description(const coord*value,boolean looked,int sym,char*buf,const char**first,struct permonst**pm){return do_screen_description(*value,looked,sym,buf,first,pm);}
