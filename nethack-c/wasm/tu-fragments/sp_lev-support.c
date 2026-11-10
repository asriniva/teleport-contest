/* SP_LEV typed ABI/backing only; all config algorithms/tables remain JS. */
#include "sp_lev-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "sp_lev-source-data.h"
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(va_list)==8 && sizeof(size_t)==8,"SP_LEV memory64 long/pointer/va_list/size_t ABI");
_Static_assert(sizeof(int)==4 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"SP_LEV scalar ABI");
_Static_assert(sizeof(unpacked_coord)==16 && _Alignof(unpacked_coord)==4 && sizeof(struct rm)==8 && sizeof(struct mkroom)==224,"SP_LEV record ABI");
_Static_assert(sizeof(lua_Integer)==8 && sizeof(coordxy)==2 && sizeof(struct sp_coder)==96 && sizeof(luaL_Reg)==16,"SP_LEV Lua/coord/coder ABI");
/* Source data/backing is emitted below; no initialized C source mirror. */
static signed char sp_lev_data_splev_init_present;
static signed char sp_lev_data_icedpools;
static char sp_lev_data_SpLev_Map[80][21];
static int sp_lev_data_container_idx;
static struct obj * sp_lev_data_container_obj[10];
static struct monst * sp_lev_data_invent_carrying_monster;
static signed char (*sp_lev_data_is_ok_location_func)(coordxy, coordxy);
static sp_lev_room_type sp_lev_data_room_types[27];
static sp_lev_trap_type sp_lev_data_trap_types[25];
static signed char sp_lev_data_floodfillchk_match_under_typ;
static struct luaL_Reg sp_lev_data_nhl_functions[35];
static int sp_lev_local_rnddoor_state[5];
static unpacked_coord sp_lev_local_get_unpacked_coord_c;
static char sp_lev_local_create_object_prize_warning[28];
static char * sp_lev_local_get_table_align_gtaligns[8];
static int sp_lev_local_get_table_align_aligns2i[8];
static char * sp_lev_local_get_table_buc_bucs[8];
static int sp_lev_local_get_table_buc_bucs2i[8];
static sp_lev_objclasspfx sp_lev_local_find_objtype_class_prefixes[6];
static object sp_lev_local_lspo_object_zeroobject;
static char * sp_lev_local_lspo_level_init_initstyles[7];
static int sp_lev_local_lspo_level_init_initstyles2i[7];
static char * sp_lev_local_lspo_engraving_engrtypes[6];
static int sp_lev_local_lspo_engraving_engrtypes2i[6];
static char * sp_lev_local_lspo_room_left_or_right[8];
static int sp_lev_local_lspo_room_l_or_r2i[8];
static char * sp_lev_local_lspo_room_top_or_bot[6];
static int sp_lev_local_lspo_room_t_or_b2i[6];
static char * sp_lev_local_l_create_stairway_stairdirs[3];
static int sp_lev_local_l_create_stairway_stairdirs2i[2];
static char * sp_lev_local_lspo_altar_shrines[4];
static int sp_lev_local_lspo_altar_shrines2i[4];
static char * sp_lev_local_lspo_corridor_walldirs[7];
static int sp_lev_local_lspo_corridor_walldirs2i[7];
static short sp_lev_local_random_wdir_wdirs[4];
static char * sp_lev_local_lspo_door_doorstates[8];
static int sp_lev_local_lspo_door_doorstates2i[7];
static char * sp_lev_local_lspo_door_walldirs[7];
static int sp_lev_local_lspo_door_walldirs2i[7];
static char * sp_lev_local_lspo_feature_features[6];
static int sp_lev_local_lspo_feature_features2i[6];
static int sp_lev_local_generate_way_out_method_escapeitems[6];
static char * sp_lev_local_lspo_teleport_region_teledirs[4];
static int sp_lev_local_lspo_teleport_region_teledirs2i[4];
static char * sp_lev_local_lspo_levregion_regiontypes[8];
static int sp_lev_local_lspo_levregion_regiontypes2i[8];
static char * sp_lev_local_lspo_exclusion_ez_types[5];
static int sp_lev_local_lspo_exclusion_ez_types2i[5];
static char * sp_lev_local_lspo_region_lits[3];
static char * sp_lev_local_lspo_drawbridge_mwdirs[6];
static int sp_lev_local_lspo_drawbridge_mwdirs2i[6];
static char * sp_lev_local_lspo_drawbridge_dbopens[4];
static int sp_lev_local_lspo_drawbridge_dbopens2i[4];
static char * sp_lev_local_lspo_mazewalk_mwdirs[6];
static int sp_lev_local_lspo_mazewalk_mwdirs2i[6];
static char * sp_lev_local_lspo_wall_property_wprops[3];
static int sp_lev_local_lspo_wall_property_wprop2i[3];
static char * sp_lev_local_lspo_map_left_or_right[7];
static int sp_lev_local_lspo_map_l_or_r2i[7];
static char * sp_lev_local_lspo_map_top_or_bot[5];
static int sp_lev_local_lspo_map_t_or_b2i[5];
void*teleport_sp_lev_global(int index){switch(index){
case 0:return(void*)&gx;
case 1:return(void*)&gy;
case 2:return(void*)&svl;
case 3:return(void*)&uball;
case 4:return(void*)&u;
case 5:return(void*)&uchain;
case 6:return(void*)&gs;
case 7:return(void*)&gf;
case 8:return(void*)&gm;
case 9:return(void*)&head_engr;
case 10:return(void*)&gn;
case 11:return(void*)&gl;
case 12:return(void*)&svn;
case 13:return(void*)&gr;
case 14:return(void*)&svr;
case 15:return(void*)&gd;
case 16:return(void*)&svd;
case 17:return(void*)&gt;
case 18:return(void*)&sve;
case 19:return(void*)&iflags;
case 20:return(void*)&svc;
case 21:return(void*)&gi;
case 22:return(void*)&svi;
case 23:return(void*)&mons;
case 24:return(void*)&svm;
case 25:return(void*)&gu;
case 26:return(void*)&defsyms;
case 27:return(void*)&obj_descr;
case 28:return(void*)&objects;
case 29:return(void*)&def_monsyms;
case 30:return(void*)&gc;
case 31:return(void*)&emptystr;
case 32:return(void*)&cg;
case 33:return(void*)&sp_lev_data_splev_init_present;
case 34:return(void*)&sp_lev_data_icedpools;
case 35:return(void*)&sp_lev_data_SpLev_Map;
case 36:return(void*)&sp_lev_data_container_idx;
case 37:return(void*)&sp_lev_data_container_obj;
case 38:return(void*)&sp_lev_data_invent_carrying_monster;
case 39:return(void*)&sp_lev_data_is_ok_location_func;
case 40:return(void*)&sp_lev_data_room_types;
case 41:return(void*)&sp_lev_data_trap_types;
case 42:return(void*)&sp_lev_data_floodfillchk_match_under_typ;
case 43:return(void*)&sp_lev_data_nhl_functions;
case 44:return(void*)&sp_lev_local_rnddoor_state;
case 45:return(void*)&sp_lev_local_get_unpacked_coord_c;
case 46:return(void*)&sp_lev_local_create_object_prize_warning;
case 47:return(void*)&sp_lev_local_get_table_align_gtaligns;
case 48:return(void*)&sp_lev_local_get_table_align_aligns2i;
case 49:return(void*)&sp_lev_local_get_table_buc_bucs;
case 50:return(void*)&sp_lev_local_get_table_buc_bucs2i;
case 51:return(void*)&sp_lev_local_find_objtype_class_prefixes;
case 52:return(void*)&sp_lev_local_lspo_object_zeroobject;
case 53:return(void*)&sp_lev_local_lspo_level_init_initstyles;
case 54:return(void*)&sp_lev_local_lspo_level_init_initstyles2i;
case 55:return(void*)&sp_lev_local_lspo_engraving_engrtypes;
case 56:return(void*)&sp_lev_local_lspo_engraving_engrtypes2i;
case 57:return(void*)&sp_lev_local_lspo_room_left_or_right;
case 58:return(void*)&sp_lev_local_lspo_room_l_or_r2i;
case 59:return(void*)&sp_lev_local_lspo_room_top_or_bot;
case 60:return(void*)&sp_lev_local_lspo_room_t_or_b2i;
case 61:return(void*)&sp_lev_local_l_create_stairway_stairdirs;
case 62:return(void*)&sp_lev_local_l_create_stairway_stairdirs2i;
case 63:return(void*)&sp_lev_local_lspo_altar_shrines;
case 64:return(void*)&sp_lev_local_lspo_altar_shrines2i;
case 65:return(void*)&sp_lev_local_lspo_corridor_walldirs;
case 66:return(void*)&sp_lev_local_lspo_corridor_walldirs2i;
case 67:return(void*)&sp_lev_local_random_wdir_wdirs;
case 68:return(void*)&sp_lev_local_lspo_door_doorstates;
case 69:return(void*)&sp_lev_local_lspo_door_doorstates2i;
case 70:return(void*)&sp_lev_local_lspo_door_walldirs;
case 71:return(void*)&sp_lev_local_lspo_door_walldirs2i;
case 72:return(void*)&sp_lev_local_lspo_feature_features;
case 73:return(void*)&sp_lev_local_lspo_feature_features2i;
case 74:return(void*)&sp_lev_local_generate_way_out_method_escapeitems;
case 75:return(void*)&sp_lev_local_lspo_teleport_region_teledirs;
case 76:return(void*)&sp_lev_local_lspo_teleport_region_teledirs2i;
case 77:return(void*)&sp_lev_local_lspo_levregion_regiontypes;
case 78:return(void*)&sp_lev_local_lspo_levregion_regiontypes2i;
case 79:return(void*)&sp_lev_local_lspo_exclusion_ez_types;
case 80:return(void*)&sp_lev_local_lspo_exclusion_ez_types2i;
case 81:return(void*)&sp_lev_local_lspo_region_lits;
case 82:return(void*)&sp_lev_local_lspo_drawbridge_mwdirs;
case 83:return(void*)&sp_lev_local_lspo_drawbridge_mwdirs2i;
case 84:return(void*)&sp_lev_local_lspo_drawbridge_dbopens;
case 85:return(void*)&sp_lev_local_lspo_drawbridge_dbopens2i;
case 86:return(void*)&sp_lev_local_lspo_mazewalk_mwdirs;
case 87:return(void*)&sp_lev_local_lspo_mazewalk_mwdirs2i;
case 88:return(void*)&sp_lev_local_lspo_wall_property_wprops;
case 89:return(void*)&sp_lev_local_lspo_wall_property_wprop2i;
case 90:return(void*)&sp_lev_local_lspo_map_left_or_right;
case 91:return(void*)&sp_lev_local_lspo_map_l_or_r2i;
case 92:return(void*)&sp_lev_local_lspo_map_top_or_bot;
case 93:return(void*)&sp_lev_local_lspo_map_t_or_b2i;
default:abort();}}
uint64_t teleport_sp_lev_read(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bounding_box);
case 1:return(uint64_t)(uintptr_t)(p->rects);
case 2:return(uint64_t)(uintptr_t)(p->nrects);
case 3:return(uint64_t)(uintptr_t)(p->ttl);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
case 1:return(uint64_t)(uintptr_t)(p->selfmask);
default:abort();}}
case 2:{struct _room*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
case 2:return(uint64_t)(uintptr_t)(p->w);
case 3:return(uint64_t)(uintptr_t)(p->h);
case 4:return(uint64_t)(uintptr_t)(p->xalign);
case 5:return(uint64_t)(uintptr_t)(p->yalign);
case 6:return(uint64_t)(uintptr_t)(p->rtype);
case 7:return(uint64_t)(uintptr_t)(p->chance);
case 8:return(uint64_t)(uintptr_t)(p->rlit);
case 9:return(uint64_t)(uintptr_t)(p->needfill);
case 10:return(uint64_t)(uintptr_t)(p->joined);
default:abort();}}
case 3:{struct achievement_tracking*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mines_prize_oid);
case 1:return(uint64_t)(uintptr_t)(p->soko_prize_oid);
case 2:return(uint64_t)(uintptr_t)(p->mines_prize_otyp);
case 3:return(uint64_t)(uintptr_t)(p->soko_prize_otyp);
default:abort();}}
case 4:{altar*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->coord);
case 1:return(uint64_t)(uintptr_t)(p->sp_amask);
case 2:return(uint64_t)(uintptr_t)(p->shrine);
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_long);
default:abort();}}
case 6:{struct class_sym*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sym);
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroNhRect);
default:abort();}}
case 8:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->digging);
case 1:return(uint64_t)(uintptr_t)(&p->achieveo);
default:abort();}}
case 9:{corridor*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->src);
case 1:return(uint64_t)(uintptr_t)(&p->dest);
default:abort();}}
case 10:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 11:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_medusa_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_astral_level);
case 3:return(uint64_t)(uintptr_t)(&p->d_mineend_level);
case 4:return(uint64_t)(uintptr_t)(&p->d_sokoend_level);
default:abort();}}
case 12:{struct dig_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->pos);
default:abort();}}
case 13:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(p->objlist);
case 4:return(uint64_t)(uintptr_t)(p->buriedobjlist);
case 5:return(uint64_t)(uintptr_t)(p->monlist);
case 6:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 14:{struct egd*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->fcbeg);
case 1:return(uint64_t)(uintptr_t)(p->fcend);
case 2:return(uint64_t)(uintptr_t)(p->gdx);
case 3:return(uint64_t)(uintptr_t)(p->gdy);
case 4:return(uint64_t)(uintptr_t)(p->ogx);
case 5:return(uint64_t)(uintptr_t)(p->ogy);
case 6:return(uint64_t)(uintptr_t)(&p->gdlevel);
case 7:return(uint64_t)(uintptr_t)(&p->fakecorr);
default:abort();}}
case 15:{struct engr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nxt_engr);
case 1:return(uint64_t)(uintptr_t)(p->engr_x);
case 2:return(uint64_t)(uintptr_t)(p->engr_y);
case 3:return(uint64_t)(uintptr_t)(p->guardobjects);
case 4:return(uint64_t)(uintptr_t)(p->nowipeout);
default:abort();}}
case 16:{struct epri*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->shrpos);
case 1:return(uint64_t)(uintptr_t)(&p->shrlevel);
default:abort();}}
case 17:{struct eshk*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->shk);
case 1:return(uint64_t)(uintptr_t)(&p->shd);
case 2:return(uint64_t)(uintptr_t)(&p->shoplevel);
default:abort();}}
case 18:{struct exclusion_zone*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->zonetype);
case 1:return(uint64_t)(uintptr_t)(p->lx);
case 2:return(uint64_t)(uintptr_t)(p->ly);
case 3:return(uint64_t)(uintptr_t)(p->hx);
case 4:return(uint64_t)(uintptr_t)(p->hy);
case 5:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 19:{struct fakecorridor*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->fx);
case 1:return(uint64_t)(uintptr_t)(p->fy);
default:abort();}}
case 20:{struct fe*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->next);
case 1:return(uint64_t)(uintptr_t)(p->func_index);
case 2:return(uint64_t)(uintptr_t)(&p->arg);
default:abort();}}
case 21:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lua_testing);
case 1:return(uint64_t)(uintptr_t)(p->last_msg);
case 2:return(uint64_t)(uintptr_t)(&p->travelcc);
default:abort();}}
case 22:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->coder);
default:abort();}}
case 23:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->doorindex);
default:abort();}}
case 24:{struct instance_globals_f*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 25:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_mklev);
case 1:return(uint64_t)(uintptr_t)(p->in_mk_themerooms);
default:abort();}}
case 26:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lev_message);
case 1:return(uint64_t)(uintptr_t)(p->lregions);
case 2:return(uint64_t)(uintptr_t)(&p->launchplace);
default:abort();}}
case 27:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->migrating_mons);
case 1:return(uint64_t)(uintptr_t)(p->min_rx);
case 2:return(uint64_t)(uintptr_t)(p->max_rx);
case 3:return(uint64_t)(uintptr_t)(p->min_ry);
case 4:return(uint64_t)(uintptr_t)(p->max_ry);
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nsubroom);
case 1:return(uint64_t)(uintptr_t)(p->num_lregions);
default:abort();}}
case 29:{struct instance_globals_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->regions);
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->stairs);
case 1:return(uint64_t)(uintptr_t)(&p->smeq);
case 2:return(uint64_t)(uintptr_t)(p->subrooms);
default:abort();}}
case 31:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 32:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
case 1:return(uint64_t)(uintptr_t)(p->doors);
default:abort();}}
case 33:{struct instance_globals_saved_e*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->exclusion_zones);
default:abort();}}
case 34:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->inv_pos);
default:abort();}}
case 35:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 36:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 37:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nroom);
case 1:return(uint64_t)(uintptr_t)(p->n_regions);
default:abort();}}
case 38:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 39:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->themeroom_failed);
case 1:return(uint64_t)(uintptr_t)(p->timer_base);
default:abort();}}
case 40:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 41:{struct instance_globals_x*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x_maze_max);
case 1:return(uint64_t)(uintptr_t)(p->xstart);
case 2:return(uint64_t)(uintptr_t)(p->xsize);
default:abort();}}
case 42:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->y_maze_max);
case 1:return(uint64_t)(uintptr_t)(p->ystart);
case 2:return(uint64_t)(uintptr_t)(p->ysize);
default:abort();}}
case 43:{struct launchplace*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 44:{lev_init*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->init_style);
case 1:return(uint64_t)(uintptr_t)(p->filling);
case 2:return(uint64_t)(uintptr_t)(p->fg);
case 3:return(uint64_t)(uintptr_t)(p->bg);
case 4:return(uint64_t)(uintptr_t)(p->smoothed);
case 5:return(uint64_t)(uintptr_t)(p->joined);
case 6:return(uint64_t)(uintptr_t)(p->lit);
case 7:return(uint64_t)(uintptr_t)(p->walled);
case 8:return(uint64_t)(uintptr_t)(p->icedpools);
case 9:return(uint64_t)(uintptr_t)(p->corrwid);
case 10:return(uint64_t)(uintptr_t)(p->wallthick);
case 11:return(uint64_t)(uintptr_t)(p->rm_deadends);
default:abort();}}
case 45:{lev_region*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->inarea);
case 1:return(uint64_t)(uintptr_t)(&p->delarea);
case 2:return(uint64_t)(uintptr_t)(p->in_islev);
case 3:return(uint64_t)(uintptr_t)(p->del_islev);
case 4:return(uint64_t)(uintptr_t)(p->rtype);
case 5:return(uint64_t)(uintptr_t)(p->padding);
case 6:return(uint64_t)(uintptr_t)(&p->rname);
default:abort();}}
case 46:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->has_shop);
case 1:return(uint64_t)(uintptr_t)(p->has_vault);
case 2:return(uint64_t)(uintptr_t)(p->has_zoo);
case 3:return(uint64_t)(uintptr_t)(p->has_court);
case 4:return(uint64_t)(uintptr_t)(p->has_morgue);
case 5:return(uint64_t)(uintptr_t)(p->has_beehive);
case 6:return(uint64_t)(uintptr_t)(p->has_barracks);
case 7:return(uint64_t)(uintptr_t)(p->has_temple);
case 8:return(uint64_t)(uintptr_t)(p->has_swamp);
case 9:return(uint64_t)(uintptr_t)(p->noteleport);
case 10:return(uint64_t)(uintptr_t)(p->hardfloor);
case 11:return(uint64_t)(uintptr_t)(p->nommap);
case 12:return(uint64_t)(uintptr_t)(p->hero_memory);
case 13:return(uint64_t)(uintptr_t)(p->shortsighted);
case 14:return(uint64_t)(uintptr_t)(p->graveyard);
case 15:return(uint64_t)(uintptr_t)(p->sokoban_rules);
case 16:return(uint64_t)(uintptr_t)(p->is_maze_lev);
case 17:return(uint64_t)(uintptr_t)(p->arboreal);
case 18:return(uint64_t)(uintptr_t)(p->corrmaze);
case 19:return(uint64_t)(uintptr_t)(p->rndmongen);
case 20:return(uint64_t)(uintptr_t)(p->deathdrops);
case 21:return(uint64_t)(uintptr_t)(p->noautosearch);
case 22:return(uint64_t)(uintptr_t)(p->fumaroles);
case 23:return(uint64_t)(uintptr_t)(p->stormy);
case 24:return(uint64_t)(uintptr_t)(p->temperature);
default:abort();}}
case 47:{struct luaL_Reg*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->func);
default:abort();}}
case 48:{struct mapfragment*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->wid);
case 1:return(uint64_t)(uintptr_t)(p->hei);
case 2:return(uint64_t)(uintptr_t)(p->data);
default:abort();}}
case 49:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->egd);
case 1:return(uint64_t)(uintptr_t)(p->epri);
case 2:return(uint64_t)(uintptr_t)(p->eshk);
default:abort();}}
case 50:{struct mkroom*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lx);
case 1:return(uint64_t)(uintptr_t)(p->hx);
case 2:return(uint64_t)(uintptr_t)(p->ly);
case 3:return(uint64_t)(uintptr_t)(p->hy);
case 4:return(uint64_t)(uintptr_t)(p->rtype);
case 5:return(uint64_t)(uintptr_t)(p->rlit);
case 6:return(uint64_t)(uintptr_t)(p->needfill);
case 7:return(uint64_t)(uintptr_t)(p->needjoining);
case 8:return(uint64_t)(uintptr_t)(p->nsubrooms);
case 9:return(uint64_t)(uintptr_t)(p->irregular);
case 10:return(uint64_t)(uintptr_t)(&p->sbrooms);
default:abort();}}
case 51:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nmon);
case 1:return(uint64_t)(uintptr_t)(p->data);
case 2:return(uint64_t)(uintptr_t)(p->cham);
case 3:return(uint64_t)(uintptr_t)(p->m_lev);
case 4:return(uint64_t)(uintptr_t)(p->mx);
case 5:return(uint64_t)(uintptr_t)(p->my);
case 6:return(uint64_t)(uintptr_t)(p->mappearance);
case 7:return(uint64_t)(uintptr_t)(p->m_ap_type);
case 8:return(uint64_t)(uintptr_t)(p->female);
case 9:return(uint64_t)(uintptr_t)(p->minvis);
case 10:return(uint64_t)(uintptr_t)(p->perminvis);
case 11:return(uint64_t)(uintptr_t)(p->mcan);
case 12:return(uint64_t)(uintptr_t)(p->mcansee);
case 13:return(uint64_t)(uintptr_t)(p->mrevived);
case 14:return(uint64_t)(uintptr_t)(p->mavenge);
case 15:return(uint64_t)(uintptr_t)(p->mflee);
case 16:return(uint64_t)(uintptr_t)(p->mfleetim);
case 17:return(uint64_t)(uintptr_t)(p->msleeping);
case 18:return(uint64_t)(uintptr_t)(p->mblinded);
case 19:return(uint64_t)(uintptr_t)(p->mstun);
case 20:return(uint64_t)(uintptr_t)(p->mfrozen);
case 21:return(uint64_t)(uintptr_t)(p->mcanmove);
case 22:return(uint64_t)(uintptr_t)(p->mconf);
case 23:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 24:return(uint64_t)(uintptr_t)(p->isshk);
case 25:return(uint64_t)(uintptr_t)(p->isgd);
case 26:return(uint64_t)(uintptr_t)(p->ispriest);
case 27:return(uint64_t)(uintptr_t)(p->wormno);
case 28:return(uint64_t)(uintptr_t)(p->mstrategy);
case 29:return(uint64_t)(uintptr_t)(&p->mgoal);
case 30:return(uint64_t)(uintptr_t)(p->mtrapseen);
case 31:return(uint64_t)(uintptr_t)(p->minvent);
case 32:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 52:{monster*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->name);
case 1:return(uint64_t)(uintptr_t)(&p->appear_as);
case 2:return(uint64_t)(uintptr_t)(p->id);
case 3:return(uint64_t)(uintptr_t)(p->sp_amask);
case 4:return(uint64_t)(uintptr_t)(p->coord);
case 5:return(uint64_t)(uintptr_t)(p->x);
case 6:return(uint64_t)(uintptr_t)(p->y);
case 7:return(uint64_t)(uintptr_t)(p->class);
case 8:return(uint64_t)(uintptr_t)(p->appear);
case 9:return(uint64_t)(uintptr_t)(p->peaceful);
case 10:return(uint64_t)(uintptr_t)(p->asleep);
case 11:return(uint64_t)(uintptr_t)(p->female);
case 12:return(uint64_t)(uintptr_t)(p->invis);
case 13:return(uint64_t)(uintptr_t)(p->cancelled);
case 14:return(uint64_t)(uintptr_t)(p->revived);
case 15:return(uint64_t)(uintptr_t)(p->avenge);
case 16:return(uint64_t)(uintptr_t)(p->fleeing);
case 17:return(uint64_t)(uintptr_t)(p->blinded);
case 18:return(uint64_t)(uintptr_t)(p->paralyzed);
case 19:return(uint64_t)(uintptr_t)(p->stunned);
case 20:return(uint64_t)(uintptr_t)(p->confused);
case 21:return(uint64_t)(uintptr_t)(p->waiting);
case 22:return(uint64_t)(uintptr_t)(p->m_lev_adj);
case 23:return(uint64_t)(uintptr_t)(p->seentraps);
case 24:return(uint64_t)(uintptr_t)(p->has_invent);
case 25:return(uint64_t)(uintptr_t)(p->mm_flags);
default:abort();}}
case 53:{struct mvitals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 54:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 55:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->flags);
case 1:return(uint64_t)(uintptr_t)(p->memlimit);
case 2:return(uint64_t)(uintptr_t)(p->steps);
case 3:return(uint64_t)(uintptr_t)(p->perpcall);
default:abort();}}
case 56:{struct nhrect*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lx);
case 1:return(uint64_t)(uintptr_t)(p->ly);
case 2:return(uint64_t)(uintptr_t)(p->hx);
case 3:return(uint64_t)(uintptr_t)(p->hy);
default:abort();}}
case 57:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(p->o_id);
case 2:return(uint64_t)(uintptr_t)(p->ox);
case 3:return(uint64_t)(uintptr_t)(p->oy);
case 4:return(uint64_t)(uintptr_t)(p->otyp);
case 5:return(uint64_t)(uintptr_t)(p->owt);
case 6:return(uint64_t)(uintptr_t)(p->quan);
case 7:return(uint64_t)(uintptr_t)(p->spe);
case 8:return(uint64_t)(uintptr_t)(p->oartifact);
case 9:return(uint64_t)(uintptr_t)(p->where);
case 10:return(uint64_t)(uintptr_t)(p->recharged);
case 11:return(uint64_t)(uintptr_t)(p->tknown);
case 12:return(uint64_t)(uintptr_t)(p->nomerge);
case 13:return(uint64_t)(uintptr_t)(p->oeroded);
case 14:return(uint64_t)(uintptr_t)(p->oeroded2);
case 15:return(uint64_t)(uintptr_t)(p->oerodeproof);
case 16:return(uint64_t)(uintptr_t)(p->olocked);
case 17:return(uint64_t)(uintptr_t)(p->obroken);
case 18:return(uint64_t)(uintptr_t)(p->otrapped);
case 19:return(uint64_t)(uintptr_t)(p->greased);
case 20:return(uint64_t)(uintptr_t)(p->corpsenm);
case 21:return(uint64_t)(uintptr_t)(p->owornmask);
default:abort();}}
case 58:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name_idx);
case 1:return(uint64_t)(uintptr_t)(p->oc_descr_idx);
case 2:return(uint64_t)(uintptr_t)(p->oc_merge);
case 3:return(uint64_t)(uintptr_t)(p->oc_class);
default:abort();}}
case 59:{sp_lev_objclasspfx*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->prefix);
case 1:return(uint64_t)(uintptr_t)(p->class);
default:abort();}}
case 60:{struct objdescr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name);
case 1:return(uint64_t)(uintptr_t)(p->oc_descr);
default:abort();}}
case 61:{object*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->name);
case 1:return(uint64_t)(uintptr_t)(p->corpsenm);
case 2:return(uint64_t)(uintptr_t)(p->id);
case 3:return(uint64_t)(uintptr_t)(p->spe);
case 4:return(uint64_t)(uintptr_t)(p->coord);
case 5:return(uint64_t)(uintptr_t)(p->x);
case 6:return(uint64_t)(uintptr_t)(p->y);
case 7:return(uint64_t)(uintptr_t)(p->class);
case 8:return(uint64_t)(uintptr_t)(p->containment);
case 9:return(uint64_t)(uintptr_t)(p->curse_state);
case 10:return(uint64_t)(uintptr_t)(p->quan);
case 11:return(uint64_t)(uintptr_t)(p->buried);
case 12:return(uint64_t)(uintptr_t)(p->lit);
case 13:return(uint64_t)(uintptr_t)(p->eroded);
case 14:return(uint64_t)(uintptr_t)(p->locked);
case 15:return(uint64_t)(uintptr_t)(p->trapped);
case 16:return(uint64_t)(uintptr_t)(p->tknown);
case 17:return(uint64_t)(uintptr_t)(p->recharged);
case 18:return(uint64_t)(uintptr_t)(p->invis);
case 19:return(uint64_t)(uintptr_t)(p->greased);
case 20:return(uint64_t)(uintptr_t)(p->broken);
case 21:return(uint64_t)(uintptr_t)(p->achievement);
default:abort();}}
case 62:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->pmnames);
case 1:return(uint64_t)(uintptr_t)(p->pmidx);
case 2:return(uint64_t)(uintptr_t)(p->mlet);
case 3:return(uint64_t)(uintptr_t)(p->geno);
case 4:return(uint64_t)(uintptr_t)(p->mflags1);
case 5:return(uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 63:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 64:{region*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x1);
case 1:return(uint64_t)(uintptr_t)(p->y1);
case 2:return(uint64_t)(uintptr_t)(p->x2);
case 3:return(uint64_t)(uintptr_t)(p->y2);
case 4:return(uint64_t)(uintptr_t)(p->rlit);
default:abort();}}
case 65:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
case 1:return(uint64_t)(uintptr_t)(p->typ);
case 2:return(uint64_t)(uintptr_t)(p->seenv);
case 3:return(uint64_t)(uintptr_t)(p->flags);
case 4:return(uint64_t)(uintptr_t)(p->horizontal);
case 5:return(uint64_t)(uintptr_t)(p->lit);
case 6:return(uint64_t)(uintptr_t)(p->roomno);
case 7:return(uint64_t)(uintptr_t)(p->edge);
default:abort();}}
case 66:{room_door*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->wall);
case 1:return(uint64_t)(uintptr_t)(p->pos);
case 2:return(uint64_t)(uintptr_t)(p->secret);
case 3:return(uint64_t)(uintptr_t)(p->mask);
default:abort();}}
case 67:{struct sp_coder*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->premapped);
case 1:return(uint64_t)(uintptr_t)(p->solidify);
case 2:return(uint64_t)(uintptr_t)(p->croom);
case 3:return(uint64_t)(uintptr_t)(p->room_stack);
case 4:return(uint64_t)(uintptr_t)(&p->tmproomlist);
case 5:return(uint64_t)(uintptr_t)(&p->failed_room);
case 6:return(uint64_t)(uintptr_t)(p->n_subroom);
case 7:return(uint64_t)(uintptr_t)(p->lvl_is_joined);
case 8:return(uint64_t)(uintptr_t)(p->check_inaccessibles);
case 9:return(uint64_t)(uintptr_t)(p->allow_flips);
default:abort();}}
case 68:{sp_lev_corridor_end*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->room);
case 1:return(uint64_t)(uintptr_t)(p->wall);
case 2:return(uint64_t)(uintptr_t)(p->door);
default:abort();}}
case 69:{sp_lev_lregion_delarea*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x1);
case 1:return(uint64_t)(uintptr_t)(p->y1);
case 2:return(uint64_t)(uintptr_t)(p->x2);
case 3:return(uint64_t)(uintptr_t)(p->y2);
default:abort();}}
case 70:{sp_lev_lregion_inarea*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x1);
case 1:return(uint64_t)(uintptr_t)(p->y1);
case 2:return(uint64_t)(uintptr_t)(p->x2);
case 3:return(uint64_t)(uintptr_t)(p->y2);
default:abort();}}
case 71:{sp_lev_room_type*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 72:{sp_lev_trap_type*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 73:{spltrap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->coord);
case 1:return(uint64_t)(uintptr_t)(p->type);
case 2:return(uint64_t)(uintptr_t)(p->spider_on_web);
case 3:return(uint64_t)(uintptr_t)(p->seen);
case 4:return(uint64_t)(uintptr_t)(p->novictim);
default:abort();}}
case 74:{struct stairway*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sx);
case 1:return(uint64_t)(uintptr_t)(p->sy);
case 2:return(uint64_t)(uintptr_t)(&p->tolev);
case 3:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 75:{union str_or_len*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->str);
case 1:return(uint64_t)(uintptr_t)(p->len);
default:abort();}}
case 76:{struct symdef*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->explanation);
default:abort();}}
case 77:{terrain*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ter);
case 1:return(uint64_t)(uintptr_t)(p->tlit);
default:abort();}}
case 78:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ntrap);
case 1:return(uint64_t)(uintptr_t)(p->tx);
case 2:return(uint64_t)(uintptr_t)(p->ty);
case 3:return(uint64_t)(uintptr_t)(&p->launch);
case 4:return(uint64_t)(uintptr_t)(p->ttyp);
case 5:return(uint64_t)(uintptr_t)(&p->vl);
default:abort();}}
case 79:{unpacked_coord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->is_random);
case 1:return(uint64_t)(uintptr_t)(p->getloc_flags);
case 2:return(uint64_t)(uintptr_t)(p->x);
case 3:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 80:{union vlaunchinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->v_launch2);
case 1:return(uint64_t)(uintptr_t)(p->v_conjoined);
default:abort();}}
case 81:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(p->ux0);
case 3:return(uint64_t)(uintptr_t)(p->uy0);
case 4:return(uint64_t)(uintptr_t)(&p->uz);
case 5:return(uint64_t)(uintptr_t)(&p->uprops);
case 6:return(uint64_t)(uintptr_t)(&p->ualignbase);
default:abort();}}
default:abort();}}
void teleport_sp_lev_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 1:p->rects=(NhRect *)value;return;
case 2:p->nrects=(short)value;return;
case 3:p->ttl=(long)value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->mnum=(short)value;return;
case 1:p->selfmask=(short)value;return;
default:abort();}}
case 2:{struct _room*p=at;switch(field){
case 0:p->x=(coordxy)value;return;
case 1:p->y=(coordxy)value;return;
case 2:p->w=(xint16)value;return;
case 3:p->h=(xint16)value;return;
case 4:p->xalign=(xint16)value;return;
case 5:p->yalign=(xint16)value;return;
case 6:p->rtype=(xint16)value;return;
case 7:p->chance=(xint16)value;return;
case 8:p->rlit=(xint16)value;return;
case 9:p->needfill=(xint16)value;return;
case 10:p->joined=(boolean)value;return;
default:abort();}}
case 3:{struct achievement_tracking*p=at;switch(field){
case 0:p->mines_prize_oid=(unsigned int)value;return;
case 1:p->soko_prize_oid=(unsigned int)value;return;
case 2:p->mines_prize_otyp=(short)value;return;
case 3:p->soko_prize_otyp=(short)value;return;
default:abort();}}
case 4:{altar*p=at;switch(field){
case 0:p->coord=(long)value;return;
case 1:p->sp_amask=(unsigned int)value;return;
case 2:p->shrine=(xint16)value;return;
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:p->a_long=(long)value;return;
default:abort();}}
case 6:{struct class_sym*p=at;switch(field){
case 0:p->sym=(char)value;return;
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
default:abort();}}
case 8:{struct context_info*p=at;switch(field){
default:abort();}}
case 9:{corridor*p=at;switch(field){
default:abort();}}
case 10:{struct d_level*p=at;switch(field){
case 0:p->dnum=(xint16)value;return;
case 1:p->dlevel=(xint16)value;return;
default:abort();}}
case 11:{struct dgn_topology*p=at;switch(field){
default:abort();}}
case 12:{struct dig_info*p=at;switch(field){
default:abort();}}
case 13:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(struct obj *)value;return;
case 4:p->buriedobjlist=(struct obj *)value;return;
case 5:p->monlist=(struct monst *)value;return;
default:abort();}}
case 14:{struct egd*p=at;switch(field){
case 0:p->fcbeg=(int)value;return;
case 1:p->fcend=(int)value;return;
case 2:p->gdx=(coordxy)value;return;
case 3:p->gdy=(coordxy)value;return;
case 4:p->ogx=(coordxy)value;return;
case 5:p->ogy=(coordxy)value;return;
default:abort();}}
case 15:{struct engr*p=at;switch(field){
case 0:p->nxt_engr=(struct engr *)value;return;
case 1:p->engr_x=(coordxy)value;return;
case 2:p->engr_y=(coordxy)value;return;
case 3:p->guardobjects=(unsigned int)value;return;
case 4:p->nowipeout=(unsigned int)value;return;
default:abort();}}
case 16:{struct epri*p=at;switch(field){
default:abort();}}
case 17:{struct eshk*p=at;switch(field){
default:abort();}}
case 18:{struct exclusion_zone*p=at;switch(field){
case 0:p->zonetype=(xint16)value;return;
case 1:p->lx=(coordxy)value;return;
case 2:p->ly=(coordxy)value;return;
case 3:p->hx=(coordxy)value;return;
case 4:p->hy=(coordxy)value;return;
case 5:p->next=(struct exclusion_zone *)value;return;
default:abort();}}
case 19:{struct fakecorridor*p=at;switch(field){
case 0:p->fx=(coordxy)value;return;
case 1:p->fy=(coordxy)value;return;
default:abort();}}
case 20:{struct fe*p=at;switch(field){
case 0:p->next=(struct fe *)value;return;
case 1:p->func_index=(short)value;return;
default:abort();}}
case 21:{struct instance_flags*p=at;switch(field){
case 0:p->lua_testing=(boolean)value;return;
case 1:p->last_msg=(int)value;return;
default:abort();}}
case 22:{struct instance_globals_c*p=at;switch(field){
case 0:p->coder=(struct sp_coder *)value;return;
default:abort();}}
case 23:{struct instance_globals_d*p=at;switch(field){
case 0:p->doorindex=(int)value;return;
default:abort();}}
case 24:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(struct trap *)value;return;
default:abort();}}
case 25:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_mklev=(boolean)value;return;
case 1:p->in_mk_themerooms=(boolean)value;return;
default:abort();}}
case 26:{struct instance_globals_l*p=at;switch(field){
case 0:p->lev_message=(char *)value;return;
case 1:p->lregions=(lev_region *)value;return;
default:abort();}}
case 27:{struct instance_globals_m*p=at;switch(field){
case 0:p->migrating_mons=(struct monst *)value;return;
case 1:p->min_rx=(coordxy)value;return;
case 2:p->max_rx=(coordxy)value;return;
case 3:p->min_ry=(coordxy)value;return;
case 4:p->max_ry=(coordxy)value;return;
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:p->nsubroom=(int)value;return;
case 1:p->num_lregions=(int)value;return;
default:abort();}}
case 29:{struct instance_globals_r*p=at;switch(field){
case 0:p->regions=(NhRegion **)value;return;
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:p->stairs=(stairway *)value;return;
case 2:p->subrooms=(struct mkroom *)value;return;
default:abort();}}
case 31:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 32:{struct instance_globals_saved_d*p=at;switch(field){
case 1:p->doors=(coord *)value;return;
default:abort();}}
case 33:{struct instance_globals_saved_e*p=at;switch(field){
case 0:p->exclusion_zones=(struct exclusion_zone *)value;return;
default:abort();}}
case 34:{struct instance_globals_saved_i*p=at;switch(field){
default:abort();}}
case 35:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 36:{struct instance_globals_saved_m*p=at;switch(field){
default:abort();}}
case 37:{struct instance_globals_saved_n*p=at;switch(field){
case 0:p->nroom=(int)value;return;
case 1:p->n_regions=(int)value;return;
default:abort();}}
case 38:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 39:{struct instance_globals_t*p=at;switch(field){
case 0:p->themeroom_failed=(boolean)value;return;
case 1:p->timer_base=(struct fe *)value;return;
default:abort();}}
case 40:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 41:{struct instance_globals_x*p=at;switch(field){
case 0:p->x_maze_max=(int)value;return;
case 1:p->xstart=(coordxy)value;return;
case 2:p->xsize=(coordxy)value;return;
default:abort();}}
case 42:{struct instance_globals_y*p=at;switch(field){
case 0:p->y_maze_max=(int)value;return;
case 1:p->ystart=(coordxy)value;return;
case 2:p->ysize=(coordxy)value;return;
default:abort();}}
case 43:{struct launchplace*p=at;switch(field){
case 0:p->x=(coordxy)value;return;
case 1:p->y=(coordxy)value;return;
default:abort();}}
case 44:{lev_init*p=at;switch(field){
case 0:p->init_style=(xint16)value;return;
case 1:p->filling=(schar)value;return;
case 2:p->fg=(char)value;return;
case 3:p->bg=(char)value;return;
case 4:p->smoothed=(boolean)value;return;
case 5:p->joined=(boolean)value;return;
case 6:p->lit=(xint16)value;return;
case 7:p->walled=(xint16)value;return;
case 8:p->icedpools=(boolean)value;return;
case 9:p->corrwid=(int)value;return;
case 10:p->wallthick=(int)value;return;
case 11:p->rm_deadends=(boolean)value;return;
default:abort();}}
case 45:{lev_region*p=at;switch(field){
case 2:p->in_islev=(boolean)value;return;
case 3:p->del_islev=(boolean)value;return;
case 4:p->rtype=(coordxy)value;return;
case 5:p->padding=(coordxy)value;return;
default:abort();}}
case 46:{struct levelflags*p=at;switch(field){
case 0:p->has_shop=(unsigned int)value;return;
case 1:p->has_vault=(unsigned int)value;return;
case 2:p->has_zoo=(unsigned int)value;return;
case 3:p->has_court=(unsigned int)value;return;
case 4:p->has_morgue=(unsigned int)value;return;
case 5:p->has_beehive=(unsigned int)value;return;
case 6:p->has_barracks=(unsigned int)value;return;
case 7:p->has_temple=(unsigned int)value;return;
case 8:p->has_swamp=(unsigned int)value;return;
case 9:p->noteleport=(unsigned int)value;return;
case 10:p->hardfloor=(unsigned int)value;return;
case 11:p->nommap=(unsigned int)value;return;
case 12:p->hero_memory=(unsigned int)value;return;
case 13:p->shortsighted=(unsigned int)value;return;
case 14:p->graveyard=(unsigned int)value;return;
case 15:p->sokoban_rules=(unsigned int)value;return;
case 16:p->is_maze_lev=(unsigned int)value;return;
case 17:p->arboreal=(unsigned int)value;return;
case 18:p->corrmaze=(unsigned int)value;return;
case 19:p->rndmongen=(unsigned int)value;return;
case 20:p->deathdrops=(unsigned int)value;return;
case 21:p->noautosearch=(unsigned int)value;return;
case 22:p->fumaroles=(unsigned int)value;return;
case 23:p->stormy=(unsigned int)value;return;
case 24:p->temperature=(schar)value;return;
default:abort();}}
case 47:{struct luaL_Reg*p=at;switch(field){
case 0:p->name=(const char *)value;return;
case 1:p->func=(lua_CFunction)value;return;
default:abort();}}
case 48:{struct mapfragment*p=at;switch(field){
case 0:p->wid=(int)value;return;
case 1:p->hei=(int)value;return;
case 2:p->data=(char *)value;return;
default:abort();}}
case 49:{struct mextra*p=at;switch(field){
case 0:p->egd=(struct egd *)value;return;
case 1:p->epri=(struct epri *)value;return;
case 2:p->eshk=(struct eshk *)value;return;
default:abort();}}
case 50:{struct mkroom*p=at;switch(field){
case 0:p->lx=(coordxy)value;return;
case 1:p->hx=(coordxy)value;return;
case 2:p->ly=(coordxy)value;return;
case 3:p->hy=(coordxy)value;return;
case 4:p->rtype=(schar)value;return;
case 5:p->rlit=(schar)value;return;
case 6:p->needfill=(schar)value;return;
case 7:p->needjoining=(boolean)value;return;
case 8:p->nsubrooms=(schar)value;return;
case 9:p->irregular=(boolean)value;return;
default:abort();}}
case 51:{struct monst*p=at;switch(field){
case 0:p->nmon=(struct monst *)value;return;
case 1:p->data=(struct permonst *)value;return;
case 2:p->cham=(short)value;return;
case 3:p->m_lev=(uchar)value;return;
case 4:p->mx=(coordxy)value;return;
case 5:p->my=(coordxy)value;return;
case 6:p->mappearance=(unsigned int)value;return;
case 7:p->m_ap_type=(uchar)value;return;
case 8:p->female=(unsigned int)value;return;
case 9:p->minvis=(unsigned int)value;return;
case 10:p->perminvis=(unsigned int)value;return;
case 11:p->mcan=(unsigned int)value;return;
case 12:p->mcansee=(unsigned int)value;return;
case 13:p->mrevived=(unsigned int)value;return;
case 14:p->mavenge=(unsigned int)value;return;
case 15:p->mflee=(unsigned int)value;return;
case 16:p->mfleetim=(unsigned int)value;return;
case 17:p->msleeping=(unsigned int)value;return;
case 18:p->mblinded=(unsigned int)value;return;
case 19:p->mstun=(unsigned int)value;return;
case 20:p->mfrozen=(unsigned int)value;return;
case 21:p->mcanmove=(unsigned int)value;return;
case 22:p->mconf=(unsigned int)value;return;
case 23:p->mpeaceful=(unsigned int)value;return;
case 24:p->isshk=(unsigned int)value;return;
case 25:p->isgd=(unsigned int)value;return;
case 26:p->ispriest=(unsigned int)value;return;
case 27:p->wormno=(unsigned int)value;return;
case 28:p->mstrategy=(unsigned long)value;return;
case 30:p->mtrapseen=(long)value;return;
case 31:p->minvent=(struct obj *)value;return;
case 32:p->mextra=(struct mextra *)value;return;
default:abort();}}
case 52:{monster*p=at;switch(field){
case 2:p->id=(short)value;return;
case 3:p->sp_amask=(unsigned int)value;return;
case 4:p->coord=(long)value;return;
case 5:p->x=(coordxy)value;return;
case 6:p->y=(coordxy)value;return;
case 7:p->class=(xint16)value;return;
case 8:p->appear=(xint16)value;return;
case 9:p->peaceful=(schar)value;return;
case 10:p->asleep=(schar)value;return;
case 11:p->female=(short)value;return;
case 12:p->invis=(short)value;return;
case 13:p->cancelled=(short)value;return;
case 14:p->revived=(short)value;return;
case 15:p->avenge=(short)value;return;
case 16:p->fleeing=(short)value;return;
case 17:p->blinded=(short)value;return;
case 18:p->paralyzed=(short)value;return;
case 19:p->stunned=(short)value;return;
case 20:p->confused=(short)value;return;
case 21:p->waiting=(short)value;return;
case 22:p->m_lev_adj=(short)value;return;
case 23:p->seentraps=(long)value;return;
case 24:p->has_invent=(short)value;return;
case 25:p->mm_flags=(mmflags_nht)value;return;
default:abort();}}
case 53:{struct mvitals*p=at;switch(field){
case 0:p->mvflags=(uchar)value;return;
default:abort();}}
case 54:{struct nhcoord*p=at;switch(field){
case 0:p->x=(coordxy)value;return;
case 1:p->y=(coordxy)value;return;
default:abort();}}
case 55:{struct nhl_sandbox_info*p=at;switch(field){
case 0:p->flags=(uint32_t)value;return;
case 1:p->memlimit=(uint32_t)value;return;
case 2:p->steps=(uint32_t)value;return;
case 3:p->perpcall=(uint32_t)value;return;
default:abort();}}
case 56:{struct nhrect*p=at;switch(field){
case 0:p->lx=(coordxy)value;return;
case 1:p->ly=(coordxy)value;return;
case 2:p->hx=(coordxy)value;return;
case 3:p->hy=(coordxy)value;return;
default:abort();}}
case 57:{struct obj*p=at;switch(field){
case 0:p->nobj=(struct obj *)value;return;
case 1:p->o_id=(unsigned int)value;return;
case 2:p->ox=(coordxy)value;return;
case 3:p->oy=(coordxy)value;return;
case 4:p->otyp=(short)value;return;
case 5:p->owt=(unsigned int)value;return;
case 6:p->quan=(long)value;return;
case 7:p->spe=(schar)value;return;
case 8:p->oartifact=(char)value;return;
case 9:p->where=(xint8)value;return;
case 10:p->recharged=(unsigned int)value;return;
case 11:p->tknown=(unsigned int)value;return;
case 12:p->nomerge=(unsigned int)value;return;
case 13:p->oeroded=(unsigned int)value;return;
case 14:p->oeroded2=(unsigned int)value;return;
case 15:p->oerodeproof=(unsigned int)value;return;
case 16:p->olocked=(unsigned int)value;return;
case 17:p->obroken=(unsigned int)value;return;
case 18:p->otrapped=(unsigned int)value;return;
case 19:p->greased=(unsigned int)value;return;
case 20:p->corpsenm=(int)value;return;
case 21:p->owornmask=(long)value;return;
default:abort();}}
case 58:{struct objclass*p=at;switch(field){
case 0:p->oc_name_idx=(short)value;return;
case 1:p->oc_descr_idx=(short)value;return;
case 2:p->oc_merge=(unsigned int)value;return;
case 3:p->oc_class=(char)value;return;
default:abort();}}
case 59:{sp_lev_objclasspfx*p=at;switch(field){
case 0:p->prefix=(const char *)value;return;
case 1:p->class=(char)value;return;
default:abort();}}
case 60:{struct objdescr*p=at;switch(field){
case 0:p->oc_name=(const char *)value;return;
case 1:p->oc_descr=(const char *)value;return;
default:abort();}}
case 61:{object*p=at;switch(field){
case 1:p->corpsenm=(int)value;return;
case 2:p->id=(short)value;return;
case 3:p->spe=(short)value;return;
case 4:p->coord=(long)value;return;
case 5:p->x=(coordxy)value;return;
case 6:p->y=(coordxy)value;return;
case 7:p->class=(xint16)value;return;
case 8:p->containment=(xint16)value;return;
case 9:p->curse_state=(schar)value;return;
case 10:p->quan=(int)value;return;
case 11:p->buried=(short)value;return;
case 12:p->lit=(short)value;return;
case 13:p->eroded=(short)value;return;
case 14:p->locked=(short)value;return;
case 15:p->trapped=(short)value;return;
case 16:p->tknown=(short)value;return;
case 17:p->recharged=(short)value;return;
case 18:p->invis=(short)value;return;
case 19:p->greased=(short)value;return;
case 20:p->broken=(short)value;return;
case 21:p->achievement=(short)value;return;
default:abort();}}
case 62:{struct permonst*p=at;switch(field){
case 2:p->mlet=(char)value;return;
case 3:p->geno=(unsigned short)value;return;
case 4:p->mflags1=(unsigned long)value;return;
case 5:p->mflags2=(unsigned long)value;return;
default:abort();}}
case 63:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(long)value;return;
case 1:p->intrinsic=(long)value;return;
default:abort();}}
case 64:{region*p=at;switch(field){
case 0:p->x1=(coordxy)value;return;
case 1:p->y1=(coordxy)value;return;
case 2:p->x2=(coordxy)value;return;
case 3:p->y2=(coordxy)value;return;
case 4:p->rlit=(xint16)value;return;
default:abort();}}
case 65:{struct rm*p=at;switch(field){
case 0:p->glyph=(int)value;return;
case 1:p->typ=(schar)value;return;
case 2:p->seenv=(uchar)value;return;
case 3:p->flags=(unsigned int)value;return;
case 4:p->horizontal=(unsigned int)value;return;
case 5:p->lit=(unsigned int)value;return;
case 6:p->roomno=(unsigned int)value;return;
case 7:p->edge=(unsigned int)value;return;
default:abort();}}
case 66:{room_door*p=at;switch(field){
case 0:p->wall=(xint16)value;return;
case 1:p->pos=(xint16)value;return;
case 2:p->secret=(xint16)value;return;
case 3:p->mask=(xint16)value;return;
default:abort();}}
case 67:{struct sp_coder*p=at;switch(field){
case 0:p->premapped=(int)value;return;
case 1:p->solidify=(boolean)value;return;
case 2:p->croom=(struct mkroom *)value;return;
case 3:p->room_stack=(int)value;return;
case 6:p->n_subroom=(int)value;return;
case 7:p->lvl_is_joined=(boolean)value;return;
case 8:p->check_inaccessibles=(boolean)value;return;
case 9:p->allow_flips=(int)value;return;
default:abort();}}
case 68:{sp_lev_corridor_end*p=at;switch(field){
case 0:p->room=(xint16)value;return;
case 1:p->wall=(xint16)value;return;
case 2:p->door=(xint16)value;return;
default:abort();}}
case 69:{sp_lev_lregion_delarea*p=at;switch(field){
case 0:p->x1=(coordxy)value;return;
case 1:p->y1=(coordxy)value;return;
case 2:p->x2=(coordxy)value;return;
case 3:p->y2=(coordxy)value;return;
default:abort();}}
case 70:{sp_lev_lregion_inarea*p=at;switch(field){
case 0:p->x1=(coordxy)value;return;
case 1:p->y1=(coordxy)value;return;
case 2:p->x2=(coordxy)value;return;
case 3:p->y2=(coordxy)value;return;
default:abort();}}
case 71:{sp_lev_room_type*p=at;switch(field){
case 0:p->name=(const char *)value;return;
case 1:p->type=(int)value;return;
default:abort();}}
case 72:{sp_lev_trap_type*p=at;switch(field){
case 0:p->name=(const char *)value;return;
case 1:p->type=(int)value;return;
default:abort();}}
case 73:{spltrap*p=at;switch(field){
case 0:p->coord=(long)value;return;
case 1:p->type=(xint16)value;return;
case 2:p->spider_on_web=(boolean)value;return;
case 3:p->seen=(boolean)value;return;
case 4:p->novictim=(boolean)value;return;
default:abort();}}
case 74:{struct stairway*p=at;switch(field){
case 0:p->sx=(coordxy)value;return;
case 1:p->sy=(coordxy)value;return;
case 3:p->next=(struct stairway *)value;return;
default:abort();}}
case 75:{union str_or_len*p=at;switch(field){
case 0:p->str=(char *)value;return;
case 1:p->len=(int)value;return;
default:abort();}}
case 76:{struct symdef*p=at;switch(field){
case 0:p->explanation=(const char *)value;return;
default:abort();}}
case 77:{terrain*p=at;switch(field){
case 0:p->ter=(xint16)value;return;
case 1:p->tlit=(xint16)value;return;
default:abort();}}
case 78:{struct trap*p=at;switch(field){
case 0:p->ntrap=(struct trap *)value;return;
case 1:p->tx=(coordxy)value;return;
case 2:p->ty=(coordxy)value;return;
case 4:p->ttyp=(unsigned int)value;return;
default:abort();}}
case 79:{unpacked_coord*p=at;switch(field){
case 0:p->is_random=(xint16)value;return;
case 1:p->getloc_flags=(getloc_flags_t)value;return;
case 2:p->x=(int)value;return;
case 3:p->y=(int)value;return;
default:abort();}}
case 80:{union vlaunchinfo*p=at;switch(field){
case 1:p->v_conjoined=(uchar)value;return;
default:abort();}}
case 81:{struct you*p=at;switch(field){
case 0:p->ux=(coordxy)value;return;
case 1:p->uy=(coordxy)value;return;
case 2:p->ux0=(coordxy)value;return;
case 3:p->uy0=(coordxy)value;return;
default:abort();}}
default:abort();}}
void* teleport_sp_lev_address(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(void*)&p->bounding_box;
case 1:return(void*)&p->rects;
case 2:return(void*)&p->nrects;
case 3:return(void*)&p->ttl;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
case 1:return(void*)&p->selfmask;
default:abort();}}
case 2:{struct _room*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
case 2:return(void*)&p->w;
case 3:return(void*)&p->h;
case 4:return(void*)&p->xalign;
case 5:return(void*)&p->yalign;
case 6:return(void*)&p->rtype;
case 7:return(void*)&p->chance;
case 8:return(void*)&p->rlit;
case 9:return(void*)&p->needfill;
case 10:return(void*)&p->joined;
default:abort();}}
case 3:{struct achievement_tracking*p=at;switch(field){
case 0:return(void*)&p->mines_prize_oid;
case 1:return(void*)&p->soko_prize_oid;
case 2:return(void*)&p->mines_prize_otyp;
case 3:return(void*)&p->soko_prize_otyp;
default:abort();}}
case 4:{altar*p=at;switch(field){
case 0:return(void*)&p->coord;
case 1:return(void*)&p->sp_amask;
case 2:return(void*)&p->shrine;
default:abort();}}
case 5:{union any*p=at;switch(field){
case 0:return(void*)&p->a_long;
default:abort();}}
case 6:{struct class_sym*p=at;switch(field){
case 0:return(void*)&p->sym;
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroNhRect;
default:abort();}}
case 8:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->digging;
case 1:return(void*)&p->achieveo;
default:abort();}}
case 9:{corridor*p=at;switch(field){
case 0:return(void*)&p->src;
case 1:return(void*)&p->dest;
default:abort();}}
case 10:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 11:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_medusa_level;
case 1:return(void*)&p->d_water_level;
case 2:return(void*)&p->d_astral_level;
case 3:return(void*)&p->d_mineend_level;
case 4:return(void*)&p->d_sokoend_level;
default:abort();}}
case 12:{struct dig_info*p=at;switch(field){
case 0:return(void*)&p->pos;
default:abort();}}
case 13:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->objlist;
case 4:return(void*)&p->buriedobjlist;
case 5:return(void*)&p->monlist;
case 6:return(void*)&p->flags;
default:abort();}}
case 14:{struct egd*p=at;switch(field){
case 0:return(void*)&p->fcbeg;
case 1:return(void*)&p->fcend;
case 2:return(void*)&p->gdx;
case 3:return(void*)&p->gdy;
case 4:return(void*)&p->ogx;
case 5:return(void*)&p->ogy;
case 6:return(void*)&p->gdlevel;
case 7:return(void*)&p->fakecorr;
default:abort();}}
case 15:{struct engr*p=at;switch(field){
case 0:return(void*)&p->nxt_engr;
case 1:return(void*)&p->engr_x;
case 2:return(void*)&p->engr_y;
default:abort();}}
case 16:{struct epri*p=at;switch(field){
case 0:return(void*)&p->shrpos;
case 1:return(void*)&p->shrlevel;
default:abort();}}
case 17:{struct eshk*p=at;switch(field){
case 0:return(void*)&p->shk;
case 1:return(void*)&p->shd;
case 2:return(void*)&p->shoplevel;
default:abort();}}
case 18:{struct exclusion_zone*p=at;switch(field){
case 0:return(void*)&p->zonetype;
case 1:return(void*)&p->lx;
case 2:return(void*)&p->ly;
case 3:return(void*)&p->hx;
case 4:return(void*)&p->hy;
case 5:return(void*)&p->next;
default:abort();}}
case 19:{struct fakecorridor*p=at;switch(field){
case 0:return(void*)&p->fx;
case 1:return(void*)&p->fy;
default:abort();}}
case 20:{struct fe*p=at;switch(field){
case 0:return(void*)&p->next;
case 1:return(void*)&p->func_index;
case 2:return(void*)&p->arg;
default:abort();}}
case 21:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->lua_testing;
case 1:return(void*)&p->last_msg;
case 2:return(void*)&p->travelcc;
default:abort();}}
case 22:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->coder;
default:abort();}}
case 23:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->doorindex;
default:abort();}}
case 24:{struct instance_globals_f*p=at;switch(field){
case 0:return(void*)&p->ftrap;
default:abort();}}
case 25:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_mklev;
case 1:return(void*)&p->in_mk_themerooms;
default:abort();}}
case 26:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->lev_message;
case 1:return(void*)&p->lregions;
case 2:return(void*)&p->launchplace;
default:abort();}}
case 27:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->migrating_mons;
case 1:return(void*)&p->min_rx;
case 2:return(void*)&p->max_rx;
case 3:return(void*)&p->min_ry;
case 4:return(void*)&p->max_ry;
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nsubroom;
case 1:return(void*)&p->num_lregions;
default:abort();}}
case 29:{struct instance_globals_r*p=at;switch(field){
case 0:return(void*)&p->regions;
default:abort();}}
case 30:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->stairs;
case 1:return(void*)&p->smeq;
case 2:return(void*)&p->subrooms;
default:abort();}}
case 31:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 32:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
case 1:return(void*)&p->doors;
default:abort();}}
case 33:{struct instance_globals_saved_e*p=at;switch(field){
case 0:return(void*)&p->exclusion_zones;
default:abort();}}
case 34:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(void*)&p->inv_pos;
default:abort();}}
case 35:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 36:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->mvitals;
default:abort();}}
case 37:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(void*)&p->nroom;
case 1:return(void*)&p->n_regions;
default:abort();}}
case 38:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(void*)&p->rooms;
default:abort();}}
case 39:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->themeroom_failed;
case 1:return(void*)&p->timer_base;
default:abort();}}
case 40:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urace;
default:abort();}}
case 41:{struct instance_globals_x*p=at;switch(field){
case 0:return(void*)&p->x_maze_max;
case 1:return(void*)&p->xstart;
case 2:return(void*)&p->xsize;
default:abort();}}
case 42:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->y_maze_max;
case 1:return(void*)&p->ystart;
case 2:return(void*)&p->ysize;
default:abort();}}
case 43:{struct launchplace*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 44:{lev_init*p=at;switch(field){
case 0:return(void*)&p->init_style;
case 1:return(void*)&p->filling;
case 2:return(void*)&p->fg;
case 3:return(void*)&p->bg;
case 4:return(void*)&p->smoothed;
case 5:return(void*)&p->joined;
case 6:return(void*)&p->lit;
case 7:return(void*)&p->walled;
case 8:return(void*)&p->icedpools;
case 9:return(void*)&p->corrwid;
case 10:return(void*)&p->wallthick;
case 11:return(void*)&p->rm_deadends;
default:abort();}}
case 45:{lev_region*p=at;switch(field){
case 0:return(void*)&p->inarea;
case 1:return(void*)&p->delarea;
case 2:return(void*)&p->in_islev;
case 3:return(void*)&p->del_islev;
case 4:return(void*)&p->rtype;
case 5:return(void*)&p->padding;
case 6:return(void*)&p->rname;
default:abort();}}
case 46:{struct levelflags*p=at;switch(field){
case 24:return(void*)&p->temperature;
default:abort();}}
case 47:{struct luaL_Reg*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->func;
default:abort();}}
case 48:{struct mapfragment*p=at;switch(field){
case 0:return(void*)&p->wid;
case 1:return(void*)&p->hei;
case 2:return(void*)&p->data;
default:abort();}}
case 49:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->egd;
case 1:return(void*)&p->epri;
case 2:return(void*)&p->eshk;
default:abort();}}
case 50:{struct mkroom*p=at;switch(field){
case 0:return(void*)&p->lx;
case 1:return(void*)&p->hx;
case 2:return(void*)&p->ly;
case 3:return(void*)&p->hy;
case 4:return(void*)&p->rtype;
case 5:return(void*)&p->rlit;
case 6:return(void*)&p->needfill;
case 7:return(void*)&p->needjoining;
case 8:return(void*)&p->nsubrooms;
case 9:return(void*)&p->irregular;
case 10:return(void*)&p->sbrooms;
default:abort();}}
case 51:{struct monst*p=at;switch(field){
case 0:return(void*)&p->nmon;
case 1:return(void*)&p->data;
case 2:return(void*)&p->cham;
case 3:return(void*)&p->m_lev;
case 4:return(void*)&p->mx;
case 5:return(void*)&p->my;
case 6:return(void*)&p->mappearance;
case 7:return(void*)&p->m_ap_type;
case 28:return(void*)&p->mstrategy;
case 29:return(void*)&p->mgoal;
case 30:return(void*)&p->mtrapseen;
case 31:return(void*)&p->minvent;
case 32:return(void*)&p->mextra;
default:abort();}}
case 52:{monster*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->appear_as;
case 2:return(void*)&p->id;
case 3:return(void*)&p->sp_amask;
case 4:return(void*)&p->coord;
case 5:return(void*)&p->x;
case 6:return(void*)&p->y;
case 7:return(void*)&p->class;
case 8:return(void*)&p->appear;
case 9:return(void*)&p->peaceful;
case 10:return(void*)&p->asleep;
case 11:return(void*)&p->female;
case 12:return(void*)&p->invis;
case 13:return(void*)&p->cancelled;
case 14:return(void*)&p->revived;
case 15:return(void*)&p->avenge;
case 16:return(void*)&p->fleeing;
case 17:return(void*)&p->blinded;
case 18:return(void*)&p->paralyzed;
case 19:return(void*)&p->stunned;
case 20:return(void*)&p->confused;
case 21:return(void*)&p->waiting;
case 22:return(void*)&p->m_lev_adj;
case 23:return(void*)&p->seentraps;
case 24:return(void*)&p->has_invent;
case 25:return(void*)&p->mm_flags;
default:abort();}}
case 53:{struct mvitals*p=at;switch(field){
case 0:return(void*)&p->mvflags;
default:abort();}}
case 54:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 55:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return(void*)&p->flags;
case 1:return(void*)&p->memlimit;
case 2:return(void*)&p->steps;
case 3:return(void*)&p->perpcall;
default:abort();}}
case 56:{struct nhrect*p=at;switch(field){
case 0:return(void*)&p->lx;
case 1:return(void*)&p->ly;
case 2:return(void*)&p->hx;
case 3:return(void*)&p->hy;
default:abort();}}
case 57:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->o_id;
case 2:return(void*)&p->ox;
case 3:return(void*)&p->oy;
case 4:return(void*)&p->otyp;
case 5:return(void*)&p->owt;
case 6:return(void*)&p->quan;
case 7:return(void*)&p->spe;
case 8:return(void*)&p->oartifact;
case 9:return(void*)&p->where;
case 20:return(void*)&p->corpsenm;
case 21:return(void*)&p->owornmask;
default:abort();}}
case 58:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_name_idx;
case 1:return(void*)&p->oc_descr_idx;
case 3:return(void*)&p->oc_class;
default:abort();}}
case 59:{sp_lev_objclasspfx*p=at;switch(field){
case 0:return(void*)&p->prefix;
case 1:return(void*)&p->class;
default:abort();}}
case 60:{struct objdescr*p=at;switch(field){
case 0:return(void*)&p->oc_name;
case 1:return(void*)&p->oc_descr;
default:abort();}}
case 61:{object*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->corpsenm;
case 2:return(void*)&p->id;
case 3:return(void*)&p->spe;
case 4:return(void*)&p->coord;
case 5:return(void*)&p->x;
case 6:return(void*)&p->y;
case 7:return(void*)&p->class;
case 8:return(void*)&p->containment;
case 9:return(void*)&p->curse_state;
case 10:return(void*)&p->quan;
case 11:return(void*)&p->buried;
case 12:return(void*)&p->lit;
case 13:return(void*)&p->eroded;
case 14:return(void*)&p->locked;
case 15:return(void*)&p->trapped;
case 16:return(void*)&p->tknown;
case 17:return(void*)&p->recharged;
case 18:return(void*)&p->invis;
case 19:return(void*)&p->greased;
case 20:return(void*)&p->broken;
case 21:return(void*)&p->achievement;
default:abort();}}
case 62:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->pmnames;
case 1:return(void*)&p->pmidx;
case 2:return(void*)&p->mlet;
case 3:return(void*)&p->geno;
case 4:return(void*)&p->mflags1;
case 5:return(void*)&p->mflags2;
default:abort();}}
case 63:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->intrinsic;
default:abort();}}
case 64:{region*p=at;switch(field){
case 0:return(void*)&p->x1;
case 1:return(void*)&p->y1;
case 2:return(void*)&p->x2;
case 3:return(void*)&p->y2;
case 4:return(void*)&p->rlit;
default:abort();}}
case 65:{struct rm*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->typ;
case 2:return(void*)&p->seenv;
default:abort();}}
case 66:{room_door*p=at;switch(field){
case 0:return(void*)&p->wall;
case 1:return(void*)&p->pos;
case 2:return(void*)&p->secret;
case 3:return(void*)&p->mask;
default:abort();}}
case 67:{struct sp_coder*p=at;switch(field){
case 0:return(void*)&p->premapped;
case 1:return(void*)&p->solidify;
case 2:return(void*)&p->croom;
case 3:return(void*)&p->room_stack;
case 4:return(void*)&p->tmproomlist;
case 5:return(void*)&p->failed_room;
case 6:return(void*)&p->n_subroom;
case 7:return(void*)&p->lvl_is_joined;
case 8:return(void*)&p->check_inaccessibles;
case 9:return(void*)&p->allow_flips;
default:abort();}}
case 68:{sp_lev_corridor_end*p=at;switch(field){
case 0:return(void*)&p->room;
case 1:return(void*)&p->wall;
case 2:return(void*)&p->door;
default:abort();}}
case 69:{sp_lev_lregion_delarea*p=at;switch(field){
case 0:return(void*)&p->x1;
case 1:return(void*)&p->y1;
case 2:return(void*)&p->x2;
case 3:return(void*)&p->y2;
default:abort();}}
case 70:{sp_lev_lregion_inarea*p=at;switch(field){
case 0:return(void*)&p->x1;
case 1:return(void*)&p->y1;
case 2:return(void*)&p->x2;
case 3:return(void*)&p->y2;
default:abort();}}
case 71:{sp_lev_room_type*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->type;
default:abort();}}
case 72:{sp_lev_trap_type*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->type;
default:abort();}}
case 73:{spltrap*p=at;switch(field){
case 0:return(void*)&p->coord;
case 1:return(void*)&p->type;
case 2:return(void*)&p->spider_on_web;
case 3:return(void*)&p->seen;
case 4:return(void*)&p->novictim;
default:abort();}}
case 74:{struct stairway*p=at;switch(field){
case 0:return(void*)&p->sx;
case 1:return(void*)&p->sy;
case 2:return(void*)&p->tolev;
case 3:return(void*)&p->next;
default:abort();}}
case 75:{union str_or_len*p=at;switch(field){
case 0:return(void*)&p->str;
case 1:return(void*)&p->len;
default:abort();}}
case 76:{struct symdef*p=at;switch(field){
case 0:return(void*)&p->explanation;
default:abort();}}
case 77:{terrain*p=at;switch(field){
case 0:return(void*)&p->ter;
case 1:return(void*)&p->tlit;
default:abort();}}
case 78:{struct trap*p=at;switch(field){
case 0:return(void*)&p->ntrap;
case 1:return(void*)&p->tx;
case 2:return(void*)&p->ty;
case 3:return(void*)&p->launch;
case 5:return(void*)&p->vl;
default:abort();}}
case 79:{unpacked_coord*p=at;switch(field){
case 0:return(void*)&p->is_random;
case 1:return(void*)&p->getloc_flags;
case 2:return(void*)&p->x;
case 3:return(void*)&p->y;
default:abort();}}
case 80:{union vlaunchinfo*p=at;switch(field){
case 0:return(void*)&p->v_launch2;
case 1:return(void*)&p->v_conjoined;
default:abort();}}
case 81:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->ux0;
case 3:return(void*)&p->uy0;
case 4:return(void*)&p->uz;
case 5:return(void*)&p->uprops;
case 6:return(void*)&p->ualignbase;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_sp_lev_var0(char * a0,int a1,int a2,int a3,int a4){(panic)(a0,a1,a2,a3,a4);}
void teleport_sp_lev_var1(char * a0){(impossible)(a0);}
void teleport_sp_lev_var2(char * a0){(panic)(a0);}
void teleport_sp_lev_var3(char * a0){(panic)(a0);}
void teleport_sp_lev_var4(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_sp_lev_var5(char * a0){(pline)(a0);}
void teleport_sp_lev_var6(char * a0){(impossible)(a0);}
void teleport_sp_lev_var7(char * a0,int a1){(panic)(a0,a1);}
void teleport_sp_lev_var8(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_sp_lev_var9(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_sp_lev_var10(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_sp_lev_var11(char * a0,char * a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_sp_lev_var12(char * a0,int a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_sp_lev_var13(char * a0,int a1){(panic)(a0,a1);}
void teleport_sp_lev_var14(char * a0){(impossible)(a0);}
void teleport_sp_lev_var15(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_sp_lev_var16(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_sp_lev_var17(char * a0,char * a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_sp_lev_var18(char * a0){(panic)(a0);}
void teleport_sp_lev_var19(char * a0,int a1,int a2,int a3,int a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_sp_lev_var20(char * a0){(impossible)(a0);}
void teleport_sp_lev_var21(char * a0){(impossible)(a0);}
int teleport_sp_lev_var22(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_sp_lev_var23(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_sp_lev_var24(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_sp_lev_var25(char * a0,int a1){(impossible)(a0,a1);}
void teleport_sp_lev_var26(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_sp_lev_var27(char * a0){(panic)(a0);}
void teleport_sp_lev_var28(char * a0){(impossible)(a0);}
int teleport_sp_lev_var29(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_sp_lev_var30(char * a0){(impossible)(a0);}
void teleport_sp_lev_var31(char * a0){(impossible)(a0);}
void teleport_sp_lev_var32(char * a0){(impossible)(a0);}
void teleport_sp_lev_var33(char * a0){(impossible)(a0);}
boolean teleport_sp_lev_call0(boolean(*fn)(coordxy, coordxy),coordxy a0,coordxy a1){return fn(a0,a1);}
#pragma clang diagnostic pop
void*teleport_sp_lev_copy(void*to,const void*from,size_t n){return memcpy(to,from,n);}
extern void reset_xystart_size(void);
extern boolean match_maptyps(xint16 typ,xint16 levltyp);
extern struct mapfragment * mapfrag_fromstr(char * str);
extern void mapfrag_free(struct mapfragment ** mf);
extern schar mapfrag_get(struct mapfragment * mf,int x,int y);
extern boolean mapfrag_canmatch(struct mapfragment * mf);
extern const char * mapfrag_error(struct mapfragment * mf);
extern boolean mapfrag_match(struct mapfragment * mf,int x,int y);
extern void teleport_sp_lev_solidify_map(void);
extern void teleport_sp_lev_map_cleanup(void);
extern void teleport_sp_lev_lvlfill_maze_grid(int x1,int y1,int x2,int y2,schar filling);
extern void teleport_sp_lev_lvlfill_solid(schar filling,schar lit);
extern void teleport_sp_lev_lvlfill_swamp(schar fg,schar bg,schar lit);
extern void teleport_sp_lev_flip_dbridge_horizontal(struct rm * lev);
extern void teleport_sp_lev_flip_dbridge_vertical(struct rm * lev);
extern void teleport_sp_lev_flip_visuals(int flp,int minx,int miny,int maxx,int maxy);
extern int teleport_sp_lev_flip_encoded_dir_bits(int flp,int val);
extern void flip_level(int flp,boolean extras);
extern void teleport_sp_lev_flip_vault_guard(int flp,struct monst * grd,coordxy minx,coordxy miny,coordxy maxx,coordxy maxy);
extern void flip_level_rnd(int flp,boolean extras);
extern void teleport_sp_lev_sel_set_wall_property(coordxy x,coordxy y,genericptr_t arg);
extern void teleport_sp_lev_set_wall_property(coordxy x1,coordxy y1,coordxy x2,coordxy y2,int prop);
extern void teleport_sp_lev_remove_boundary_syms(void);
extern void teleport_sp_lev_set_door_orientation(int x,int y);
extern boolean teleport_sp_lev_shared_with_room(int x,int y,struct mkroom * droom);
extern void teleport_sp_lev_maybe_add_door(int x,int y,struct mkroom * droom);
extern void teleport_sp_lev_link_doors_rooms(void);
extern int teleport_sp_lev_rnddoor(void);
extern int teleport_sp_lev_rndtrap(void);
extern void teleport_sp_lev_get_location(coordxy * x,coordxy * y,getloc_flags_t humidity,struct mkroom * croom);
extern void teleport_sp_lev_set_ok_location_func(boolean (*func)(coordxy, coordxy));
extern boolean teleport_sp_lev_is_ok_location(coordxy x,coordxy y,getloc_flags_t humidity);
extern boolean pm_good_location(coordxy x,coordxy y,struct permonst * pm);
extern unpacked_coord teleport_sp_lev_get_unpacked_coord(long loc,int defhumidity);
extern void get_location_coord(coordxy * x,coordxy * y,int humidity,struct mkroom * croom,long crd);
extern void teleport_sp_lev_get_room_loc(coordxy * x,coordxy * y,struct mkroom * croom);
extern void teleport_sp_lev_get_free_room_loc(coordxy * x,coordxy * y,struct mkroom * croom,long pos);
extern boolean check_room(coordxy * lowx,coordxy * ddx,coordxy * lowy,coordxy * ddy,boolean vault);
extern boolean create_room(coordxy x,coordxy y,coordxy w,coordxy h,coordxy xal,coordxy yal,xint16 rtype,xint16 rlit);
extern boolean teleport_sp_lev_create_subroom(struct mkroom * proom,coordxy x,coordxy y,coordxy w,coordxy h,xint16 rtype,xint16 rlit);
extern void teleport_sp_lev_create_door(room_door * dd,struct mkroom * broom);
extern void teleport_sp_lev_create_trap(spltrap * t,struct mkroom * croom);
extern int teleport_sp_lev_noncoalignment(aligntyp alignment);
extern boolean teleport_sp_lev_m_bad_boulder_spot(coordxy x,coordxy y);
extern int teleport_sp_lev_pm_to_humidity(struct permonst * pm);
extern unsigned int teleport_sp_lev_sp_amask_to_amask(unsigned int sp_amask);
extern void teleport_sp_lev_create_monster(monster * m,struct mkroom * croom);
extern struct obj * teleport_sp_lev_create_object(object * o,struct mkroom * croom);
extern void teleport_sp_lev_create_altar(altar * a,struct mkroom * croom);
extern boolean teleport_sp_lev_search_door(struct mkroom * croom,coordxy * x,coordxy * y,xint16 wall,int cnt);
extern boolean dig_corridor(coord * org,coord * dest,int * npoints,boolean nxcor,schar ftyp,schar btyp);
extern void teleport_sp_lev_create_corridor(corridor * c);
extern void fill_special_room(struct mkroom * croom);
extern struct mkroom * teleport_sp_lev_build_room(room * r,struct mkroom * mkr);
extern void teleport_sp_lev_light_region(region * tmpregion);
extern void wallify_map(coordxy x1,coordxy y1,coordxy x2,coordxy y2);
extern void teleport_sp_lev_maze1xy(coord * m,int humidity);
extern void teleport_sp_lev_fill_empty_maze(void);
extern void teleport_sp_lev_splev_initlev(lev_init * linit);
extern void teleport_sp_lev_spo_end_moninvent(void);
extern void teleport_sp_lev_spo_pop_container(void);
extern void teleport_sp_lev_l_push_wid_hei_table(lua_State * L,int wid,int hei);
extern void teleport_sp_lev_l_push_mkroom_table(lua_State * L,struct mkroom * tmpr);
extern int lspo_message(lua_State * L);
extern int teleport_sp_lev_get_table_align(lua_State * L);
extern int teleport_sp_lev_get_table_monclass(lua_State * L);
extern int teleport_sp_lev_find_montype(lua_State * L,const char * s,int * mgender);
extern int teleport_sp_lev_get_table_montype(lua_State * L,int * mgender);
extern void teleport_sp_lev_get_table_xy_or_coord(lua_State * L,lua_Integer * x,lua_Integer * y);
extern int lspo_monster(lua_State * L);
extern lua_Integer teleport_sp_lev_get_table_int_or_random(lua_State * L,const char * name,int rndval);
extern int teleport_sp_lev_get_table_buc(lua_State * L);
extern int get_table_objclass(lua_State * L);
extern int teleport_sp_lev_find_objtype(lua_State * L,const char * s,char oclass);
extern int get_table_objtype(lua_State * L);
extern int lspo_object(lua_State * L);
extern int lspo_level_flags(lua_State * L);
extern int lspo_level_init(lua_State * L);
extern int lspo_engraving(lua_State * L);
extern int lspo_mineralize(lua_State * L);
extern const char * teleport_sp_lev_get_mkroom_name(int rtype);
extern int teleport_sp_lev_get_table_roomtype_opt(lua_State * L,const char * name,int defval);
extern int lspo_room(lua_State * L);
extern void teleport_sp_lev_spo_endroom(struct sp_coder * coder);
extern boolean teleport_sp_lev_good_stair_loc(coordxy x,coordxy y);
extern int teleport_sp_lev_l_create_stairway(lua_State * L,boolean using_ladder);
extern int lspo_stair(lua_State * L);
extern int lspo_ladder(lua_State * L);
extern int lspo_grave(lua_State * L);
extern int lspo_altar(lua_State * L);
extern int teleport_sp_lev_get_table_traptype_opt(lua_State * L,const char * name,int defval);
extern const char * get_trapname_bytype(int ttyp);
extern int teleport_sp_lev_get_traptype_byname(const char * trapname);
extern int lspo_trap(lua_State * L);
extern int lspo_gold(lua_State * L);
extern int lspo_corridor(lua_State * L);
extern int lspo_random_corridors(lua_State * L);
extern coordxy random_wdir(void);
extern int teleport_sp_lev_floodfillchk_match_under(coordxy x,coordxy y);
extern void set_floodfillchk_match_under(coordxy typ);
extern int teleport_sp_lev_floodfillchk_match_accessible(coordxy x,coordxy y);
extern void teleport_sp_lev_sel_set_ter(coordxy x,coordxy y,genericptr_t arg);
extern void teleport_sp_lev_sel_set_feature(coordxy x,coordxy y,genericptr_t arg);
extern void teleport_sp_lev_sel_set_door(coordxy dx,coordxy dy,genericptr_t arg);
extern int lspo_door(lua_State * L);
extern void teleport_sp_lev_l_table_getset_feature_flag(lua_State * L,int x,int y,const char * name,int flag);
extern void cvt_to_abscoord(coordxy * x,coordxy * y);
extern void cvt_to_relcoord(coordxy * x,coordxy * y);
extern int nhl_abs_coord(lua_State * L);
extern int lspo_feature(lua_State * L);
extern int lspo_gas_cloud(lua_State * L);
extern int lspo_terrain(lua_State * L);
extern int lspo_replace_terrain(lua_State * L);
extern boolean teleport_sp_lev_generate_way_out_method(coordxy nx,coordxy ny,struct selectionvar * ov);
extern void teleport_sp_lev_ensure_way_out(void);
extern lua_Integer teleport_sp_lev_get_table_intarray_entry(lua_State * L,int tableidx,int entrynum);
extern int teleport_sp_lev_get_table_region(lua_State * L,const char * name,lua_Integer * x1,lua_Integer * y1,lua_Integer * x2,lua_Integer * y2,boolean optional);
extern boolean get_coord(lua_State * L,int i,lua_Integer * x,lua_Integer * y);
extern void teleport_sp_lev_levregion_add(lev_region * lregion);
extern void teleport_sp_lev_l_get_lregion(lua_State * L,lev_region * tmplregion);
extern int lspo_teleport_region(lua_State * L);
extern int lspo_levregion(lua_State * L);
extern int lspo_exclusion(lua_State * L);
extern void teleport_sp_lev_sel_set_lit(coordxy x,coordxy y,genericptr_t arg);
extern void teleport_sp_lev_add_doors_to_room(struct mkroom * croom);
extern void teleport_sp_lev_get_table_coords_or_region(lua_State * L,coordxy * dx1,coordxy * dy1,coordxy * dx2,coordxy * dy2);
extern int lspo_region(lua_State * L);
extern int lspo_drawbridge(lua_State * L);
extern int lspo_mazewalk(lua_State * L);
extern int lspo_wall_property(lua_State * L);
extern void teleport_sp_lev_set_wallprop_in_selection(lua_State * L,int prop);
extern int lspo_non_diggable(lua_State * L);
extern int lspo_non_passwall(lua_State * L);
extern int lspo_wallify(lua_State * L);
extern int lspo_reset_level(lua_State * L);
extern int lspo_finalize_level(lua_State * L);
extern int lspo_map(lua_State * L);
extern void update_croom(void);
extern struct sp_coder * teleport_sp_lev_sp_level_coder_init(void);
extern void l_register_des(lua_State * L);
extern void create_des_coder(void);
extern boolean load_special(const char * name);
uintptr_t teleport_sp_lev_function0(void){return(uintptr_t)teleport_sp_lev_good_stair_loc;}
uintptr_t teleport_sp_lev_function1(void){return(uintptr_t)teleport_sp_lev_floodfillchk_match_under;}
uintptr_t teleport_sp_lev_function2(void){return(uintptr_t)teleport_sp_lev_sel_set_ter;}
uintptr_t teleport_sp_lev_function3(void){return(uintptr_t)teleport_sp_lev_floodfillchk_match_accessible;}
uintptr_t teleport_sp_lev_function4(void){return(uintptr_t)teleport_sp_lev_sel_set_lit;}
uintptr_t teleport_sp_lev_function5(void){return(uintptr_t)teleport_sp_lev_sel_set_wall_property;}
uintptr_t teleport_sp_lev_function6(void){return(uintptr_t)lspo_message;}
uintptr_t teleport_sp_lev_function7(void){return(uintptr_t)lspo_monster;}
uintptr_t teleport_sp_lev_function8(void){return(uintptr_t)lspo_object;}
uintptr_t teleport_sp_lev_function9(void){return(uintptr_t)lspo_level_flags;}
uintptr_t teleport_sp_lev_function10(void){return(uintptr_t)lspo_level_init;}
uintptr_t teleport_sp_lev_function11(void){return(uintptr_t)lspo_engraving;}
uintptr_t teleport_sp_lev_function12(void){return(uintptr_t)lspo_mineralize;}
uintptr_t teleport_sp_lev_function13(void){return(uintptr_t)lspo_door;}
uintptr_t teleport_sp_lev_function14(void){return(uintptr_t)lspo_stair;}
uintptr_t teleport_sp_lev_function15(void){return(uintptr_t)lspo_ladder;}
uintptr_t teleport_sp_lev_function16(void){return(uintptr_t)lspo_grave;}
uintptr_t teleport_sp_lev_function17(void){return(uintptr_t)lspo_altar;}
uintptr_t teleport_sp_lev_function18(void){return(uintptr_t)lspo_map;}
uintptr_t teleport_sp_lev_function19(void){return(uintptr_t)lspo_feature;}
uintptr_t teleport_sp_lev_function20(void){return(uintptr_t)lspo_terrain;}
uintptr_t teleport_sp_lev_function21(void){return(uintptr_t)lspo_replace_terrain;}
uintptr_t teleport_sp_lev_function22(void){return(uintptr_t)lspo_room;}
uintptr_t teleport_sp_lev_function23(void){return(uintptr_t)lspo_corridor;}
uintptr_t teleport_sp_lev_function24(void){return(uintptr_t)lspo_random_corridors;}
uintptr_t teleport_sp_lev_function25(void){return(uintptr_t)lspo_gold;}
uintptr_t teleport_sp_lev_function26(void){return(uintptr_t)lspo_trap;}
uintptr_t teleport_sp_lev_function27(void){return(uintptr_t)lspo_mazewalk;}
uintptr_t teleport_sp_lev_function28(void){return(uintptr_t)lspo_drawbridge;}
uintptr_t teleport_sp_lev_function29(void){return(uintptr_t)lspo_region;}
uintptr_t teleport_sp_lev_function30(void){return(uintptr_t)lspo_levregion;}
uintptr_t teleport_sp_lev_function31(void){return(uintptr_t)lspo_exclusion;}
uintptr_t teleport_sp_lev_function32(void){return(uintptr_t)lspo_wallify;}
uintptr_t teleport_sp_lev_function33(void){return(uintptr_t)lspo_wall_property;}
uintptr_t teleport_sp_lev_function34(void){return(uintptr_t)lspo_non_diggable;}
uintptr_t teleport_sp_lev_function35(void){return(uintptr_t)lspo_non_passwall;}
uintptr_t teleport_sp_lev_function36(void){return(uintptr_t)lspo_teleport_region;}
uintptr_t teleport_sp_lev_function37(void){return(uintptr_t)lspo_reset_level;}
uintptr_t teleport_sp_lev_function38(void){return(uintptr_t)lspo_finalize_level;}
uintptr_t teleport_sp_lev_function39(void){return(uintptr_t)lspo_gas_cloud;}
#include "sp_lev-source-data.h"
static char sp_lev_literals[SP_LEV_LITERAL_CAPACITY];
char*teleport_sp_lev_literal_storage(void){return sp_lev_literals;}
size_t teleport_sp_lev_literal_capacity(void){return sizeof sp_lev_literals;}
