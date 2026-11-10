/* MKMAZE ABI/header/native dependency transport and zero backing only. */
#include "hack.h"
#include "sp_lev.h"
#include <stdint.h>
#include <stdlib.h>
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(size_t)==8,"MKMAZE memory64 LP64 ABI");
_Static_assert(sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"MKMAZE signed native scalar ABI");
void*teleport_mkmaze_global(int index){switch(index){
case 0:return(void*)&svl;
case 1:return(void*)&iflags;
case 2:return(void*)&gb;
case 3:return(void*)&gx;
case 4:return(void*)&gy;
case 5:return(void*)&sve;
case 6:return(void*)&svn;
case 7:return(void*)&u;
case 8:return(void*)&gl;
case 9:return(void*)&svd;
case 10:return(void*)&gn;
case 11:return(void*)&svu;
case 12:return(void*)&svr;
case 13:return(void*)&mons;
case 14:return(void*)&gu;
case 15:return(void*)&gr;
case 16:return(void*)&objects;
case 17:return(void*)&svi;
case 18:return(void*)&flags;
case 19:return(void*)&gi;
case 20:return(void*)&gw;
case 21:return(void*)&uball;
case 22:return(void*)&svb;
case 23:return(void*)&ge;
case 24:return(void*)&svx;
case 25:return(void*)&svy;
case 26:return(void*)&gv;
case 27:return(void*)&program_state;
case 28:return(void*)&gf;
default:abort();}}
uint64_t teleport_mkmaze_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(NhRegion));
case 6:return(uint64_t)(sizeof(dlevel_t));
case 7:return(uint64_t)(sizeof(lev_region));
case 8:return(uint64_t)(sizeof(struct Role));
case 9:return(uint64_t)(sizeof(struct bubble));
case 10:return(uint64_t)(sizeof(struct container));
case 11:return(uint64_t)(sizeof(struct d_flags));
case 12:return(uint64_t)(sizeof(struct d_level));
case 13:return(uint64_t)(sizeof(struct dest_area));
case 14:return(uint64_t)(sizeof(struct dgn_topology));
case 15:return(uint64_t)(sizeof(struct dungeon));
case 16:return(uint64_t)(sizeof(struct exclusion_zone));
case 17:return(uint64_t)(sizeof(struct flag));
case 18:return(uint64_t)(sizeof(struct instance_flags));
case 19:return(uint64_t)(sizeof(struct instance_globals_b));
case 20:return(uint64_t)(sizeof(struct instance_globals_e));
case 21:return(uint64_t)(sizeof(struct instance_globals_f));
case 22:return(uint64_t)(sizeof(struct instance_globals_i));
case 23:return(uint64_t)(sizeof(struct instance_globals_l));
case 24:return(uint64_t)(sizeof(struct instance_globals_n));
case 25:return(uint64_t)(sizeof(struct instance_globals_r));
case 26:return(uint64_t)(sizeof(struct instance_globals_saved_b));
case 27:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 28:return(uint64_t)(sizeof(struct instance_globals_saved_e));
case 29:return(uint64_t)(sizeof(struct instance_globals_saved_i));
case 30:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 31:return(uint64_t)(sizeof(struct instance_globals_saved_n));
case 32:return(uint64_t)(sizeof(struct instance_globals_saved_r));
case 33:return(uint64_t)(sizeof(struct instance_globals_saved_u));
case 34:return(uint64_t)(sizeof(struct instance_globals_saved_x));
case 35:return(uint64_t)(sizeof(struct instance_globals_saved_y));
case 36:return(uint64_t)(sizeof(struct instance_globals_u));
case 37:return(uint64_t)(sizeof(struct instance_globals_v));
case 38:return(uint64_t)(sizeof(struct instance_globals_w));
case 39:return(uint64_t)(sizeof(struct instance_globals_x));
case 40:return(uint64_t)(sizeof(struct instance_globals_y));
case 41:return(uint64_t)(sizeof(struct levelflags));
case 42:return(uint64_t)(sizeof(struct mextra));
case 43:return(uint64_t)(sizeof(struct mkroom));
case 44:return(uint64_t)(sizeof(struct monst));
case 45:return(uint64_t)(sizeof(struct nh_file));
case 46:return(uint64_t)(sizeof(struct nhcoord));
case 47:return(uint64_t)(sizeof(struct obj));
case 48:return(uint64_t)(sizeof(struct objclass));
case 49:return(uint64_t)(sizeof(struct oextra));
case 50:return(uint64_t)(sizeof(struct permonst));
case 51:return(uint64_t)(sizeof(struct prop));
case 52:return(uint64_t)(sizeof(struct rm));
case 53:return(uint64_t)(sizeof(struct s_level));
case 54:return(uint64_t)(sizeof(struct sinfo));
case 55:return(uint64_t)(sizeof(struct stairway));
case 56:return(uint64_t)(sizeof(struct trap));
case 57:return(uint64_t)(sizeof(struct u_roleplay));
case 58:return(uint64_t)(sizeof(struct you));
case 59:return(uint64_t)(sizeof(union str_or_len));
case 60:return(uint64_t)(sizeof(union vptrs));
case 61:return(uint64_t)(AIR);
case 62:return(uint64_t)(BLCORNER);
case 63:return(uint64_t)(BOULDER);
case 64:return(uint64_t)(BRCORNER);
case 65:return(uint64_t)(CLOUD);
case 66:return(uint64_t)(CONS_HERO);
case 67:return(uint64_t)(CONS_MON);
case 68:return(uint64_t)(CONS_OBJ);
case 69:return(uint64_t)(CONS_TRAP);
case 70:return(uint64_t)(CORPSE);
case 71:return(uint64_t)(CORR);
case 72:return(uint64_t)(CROSSWALL);
case 73:return(uint64_t)(C_RATION);
case 74:return(uint64_t)(DBWALL);
case 75:return(uint64_t)(DEAF);
case 76:return(uint64_t)(DOOR);
case 77:return(uint64_t)(EGG);
case 78:return(uint64_t)(FOOD_CLASS);
case 79:return(uint64_t)(FOUNTAIN);
case 80:return(uint64_t)(GAUNTLETS_OF_DEXTERITY);
case 81:return(uint64_t)(GEM_CLASS);
case 82:return(uint64_t)(GLYPH_ALTAR_OFF);
case 83:return(uint64_t)(GLYPH_CMAP_A_OFF);
case 84:return(uint64_t)(GLYPH_CMAP_B_OFF);
case 85:return(uint64_t)(GLYPH_CMAP_C_OFF);
case 86:return(uint64_t)(GLYPH_CMAP_GEH_OFF);
case 87:return(uint64_t)(GLYPH_CMAP_KNOX_OFF);
case 88:return(uint64_t)(GLYPH_CMAP_MAIN_OFF);
case 89:return(uint64_t)(GLYPH_CMAP_MINES_OFF);
case 90:return(uint64_t)(GLYPH_CMAP_SOKO_OFF);
case 91:return(uint64_t)(GLYPH_CMAP_STONE_OFF);
case 92:return(uint64_t)(GOLD_PIECE);
case 93:return(uint64_t)(HWALL);
case 94:return(uint64_t)(ICE);
case 95:return(uint64_t)(IRONBARS);
case 96:return(uint64_t)(K_RATION);
case 97:return(uint64_t)(LADDER);
case 98:return(uint64_t)(LAVAPOOL);
case 99:return(uint64_t)(LAVAWALL);
case 100:return(uint64_t)(LEATHER_GLOVES);
case 101:return(uint64_t)(LEMBAS_WAFER);
case 102:return(uint64_t)(LONG_SWORD);
case 103:return(uint64_t)(LR_BRANCH);
case 104:return(uint64_t)(LR_DOWNSTAIR);
case 105:return(uint64_t)(LR_DOWNTELE);
case 106:return(uint64_t)(LR_PORTAL);
case 107:return(uint64_t)(LR_TELE);
case 108:return(uint64_t)(LR_UPSTAIR);
case 109:return(uint64_t)(LR_UPTELE);
case 110:return(uint64_t)(MAGIC_PORTAL);
case 111:return(uint64_t)(MAX_GLYPH);
case 112:return(uint64_t)(MAX_TYPE);
case 113:return(uint64_t)(MELT_ICE_AWAY);
case 114:return(uint64_t)(PM_CLERIC);
case 115:return(uint64_t)(PM_MINOTAUR);
case 116:return(uint64_t)(PM_ORC);
case 117:return(uint64_t)(PM_ORC_CAPTAIN);
case 118:return(uint64_t)(PM_ORC_SHAMAN);
case 119:return(uint64_t)(POOL);
case 120:return(uint64_t)(RANDOM_CLASS);
case 121:return(uint64_t)(RING_CLASS);
case 122:return(uint64_t)(ROCK);
case 123:return(uint64_t)(ROOM);
case 124:return(uint64_t)(SDOOR);
case 125:return(uint64_t)(SILVER_SABER);
case 126:return(uint64_t)(SINK);
case 127:return(uint64_t)(SKELETON_KEY);
case 128:return(uint64_t)(SLIME_MOLD);
case 129:return(uint64_t)(STAIRS);
case 130:return(uint64_t)(STATUE);
case 131:return(uint64_t)(STONE);
case 132:return(uint64_t)(STRANGE_OBJECT);
case 133:return(uint64_t)(SWIMMING);
case 134:return(uint64_t)(S_air);
case 135:return(uint64_t)(S_altar);
case 136:return(uint64_t)(S_arrow_trap);
case 137:return(uint64_t)(S_cloud);
case 138:return(uint64_t)(S_digbeam);
case 139:return(uint64_t)(S_goodpos);
case 140:return(uint64_t)(S_grave);
case 141:return(uint64_t)(S_ndoor);
case 142:return(uint64_t)(S_stone);
case 143:return(uint64_t)(S_trwall);
case 144:return(uint64_t)(S_vwall);
case 145:return(uint64_t)(S_water);
case 146:return(uint64_t)(TALLOW_CANDLE);
case 147:return(uint64_t)(TDWALL);
case 148:return(uint64_t)(TIN);
case 149:return(uint64_t)(TLCORNER);
case 150:return(uint64_t)(TLWALL);
case 151:return(uint64_t)(TRAPNUM);
case 152:return(uint64_t)(TRCORNER);
case 153:return(uint64_t)(TRIPE_RATION);
case 154:return(uint64_t)(TRWALL);
case 155:return(uint64_t)(TUWALL);
case 156:return(uint64_t)(VIBRATING_SQUARE);
case 157:return(uint64_t)(VWALL);
case 158:return(uint64_t)(WATER);
case 159:return(uint64_t)(WAX_CANDLE);
case 160:return(uint64_t)(altar_chaotic);
case 161:return(uint64_t)(altar_lawful);
case 162:return(uint64_t)(altar_neutral);
case 163:return(uint64_t)(altar_other);
case 164:return(uint64_t)(altar_unaligned);
default:abort();}}
uint64_t teleport_mkmaze_read(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->player_flags);
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{__typeof__(((lev_region*)0)->inarea)*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x1);
case 1:return(uint64_t)(uintptr_t)(p->y1);
case 2:return(uint64_t)(uintptr_t)(p->x2);
case 3:return(uint64_t)(uintptr_t)(p->y2);
default:abort();}}
case 3:{__typeof__(((lev_region*)0)->delarea)*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x1);
case 1:return(uint64_t)(uintptr_t)(p->y1);
case 2:return(uint64_t)(uintptr_t)(p->x2);
case 3:return(uint64_t)(uintptr_t)(p->y2);
default:abort();}}
case 4:{struct bubble*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
case 2:return(uint64_t)(uintptr_t)(p->dx);
case 3:return(uint64_t)(uintptr_t)(p->dy);
case 4:return(uint64_t)(uintptr_t)(&p->bm);
case 5:return(uint64_t)(uintptr_t)(p->prev);
case 6:return(uint64_t)(uintptr_t)(p->next);
case 7:return(uint64_t)(uintptr_t)(p->cons);
default:abort();}}
case 5:{struct container*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->next);
case 1:return(uint64_t)(uintptr_t)(p->x);
case 2:return(uint64_t)(uintptr_t)(p->y);
case 3:return(uint64_t)(uintptr_t)(p->what);
case 4:return(uint64_t)(uintptr_t)(p->list);
default:abort();}}
case 6:{struct d_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->town);
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 8:{struct dest_area*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lx);
case 1:return(uint64_t)(uintptr_t)(p->ly);
case 2:return(uint64_t)(uintptr_t)(p->hx);
case 3:return(uint64_t)(uintptr_t)(p->hy);
case 4:return(uint64_t)(uintptr_t)(p->nlx);
case 5:return(uint64_t)(uintptr_t)(p->nly);
case 6:return(uint64_t)(uintptr_t)(p->nhx);
case 7:return(uint64_t)(uintptr_t)(p->nhy);
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_medusa_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_stronghold_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_baalzebub_level);
case 3:return(uint64_t)(uintptr_t)(&p->d_earth_level);
case 4:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 5:return(uint64_t)(uintptr_t)(&p->d_fire_level);
case 6:return(uint64_t)(uintptr_t)(&p->d_air_level);
case 7:return(uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 8:return(uint64_t)(uintptr_t)(p->d_mines_dnum);
case 9:return(uint64_t)(uintptr_t)(&p->d_knox_level);
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(p->monlist);
case 4:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 11:{struct dungeon*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dname);
case 1:return(uint64_t)(uintptr_t)(&p->proto);
case 2:return(uint64_t)(uintptr_t)(p->depth_start);
default:abort();}}
case 12:{struct exclusion_zone*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->zonetype);
case 1:return(uint64_t)(uintptr_t)(p->lx);
case 2:return(uint64_t)(uintptr_t)(p->ly);
case 3:return(uint64_t)(uintptr_t)(p->hx);
case 4:return(uint64_t)(uintptr_t)(p->hy);
case 5:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 13:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
case 1:return(uint64_t)(uintptr_t)(p->debug_overwrite_stairs);
default:abort();}}
case 15:{struct instance_globals_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bughack);
default:abort();}}
case 16:{struct instance_globals_e*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ebubbles);
default:abort();}}
case 17:{struct instance_globals_f*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 18:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_mk_themerooms);
default:abort();}}
case 19:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lregions);
default:abort();}}
case 20:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->num_lregions);
default:abort();}}
case 21:{struct instance_globals_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ransacked);
default:abort();}}
case 22:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->bbubbles);
default:abort();}}
case 23:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeons);
case 1:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
case 2:return(uint64_t)(uintptr_t)(&p->dndest);
default:abort();}}
case 24:{struct instance_globals_saved_e*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->exclusion_zones);
default:abort();}}
case 25:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->inv_pos);
default:abort();}}
case 26:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 27:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nroom);
default:abort();}}
case 28:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 29:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->updest);
default:abort();}}
case 30:{struct instance_globals_saved_x*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->xmin);
case 1:return(uint64_t)(uintptr_t)(p->xmax);
default:abort();}}
case 31:{struct instance_globals_saved_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ymin);
case 1:return(uint64_t)(uintptr_t)(p->ymax);
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
case 1:return(uint64_t)(uintptr_t)(&p->uz_save);
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 34:{struct instance_globals_w*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->wportal);
default:abort();}}
case 35:{struct instance_globals_x*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x_maze_max);
default:abort();}}
case 36:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->y_maze_max);
default:abort();}}
case 37:{lev_region*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->inarea);
case 1:return(uint64_t)(uintptr_t)(&p->delarea);
case 2:return(uint64_t)(uintptr_t)(p->rtype);
case 3:return(uint64_t)(uintptr_t)(&p->rname);
default:abort();}}
case 38:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hero_memory);
case 1:return(uint64_t)(uintptr_t)(p->graveyard);
case 2:return(uint64_t)(uintptr_t)(p->is_maze_lev);
case 3:return(uint64_t)(uintptr_t)(p->has_town);
case 4:return(uint64_t)(uintptr_t)(p->corrmaze);
case 5:return(uint64_t)(uintptr_t)(p->temperature);
default:abort();}}
case 39:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mgivenname);
default:abort();}}
case 40:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nmon);
case 1:return(uint64_t)(uintptr_t)(p->data);
case 2:return(uint64_t)(uintptr_t)(p->mx);
case 3:return(uint64_t)(uintptr_t)(p->my);
case 4:return(uint64_t)(uintptr_t)(p->mhp);
case 5:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 6:return(uint64_t)(uintptr_t)(p->mtrapped);
case 7:return(uint64_t)(uintptr_t)(p->wormno);
case 8:return(uint64_t)(uintptr_t)(p->mstate);
case 9:return(uint64_t)(uintptr_t)(p->migflags);
case 10:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 41:{struct nh_file*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mode);
default:abort();}}
case 42:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 43:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->v);
case 1:return(uint64_t)(uintptr_t)(p->ox);
case 2:return(uint64_t)(uintptr_t)(p->oy);
case 3:return(uint64_t)(uintptr_t)(p->otyp);
case 4:return(uint64_t)(uintptr_t)(p->owt);
case 5:return(uint64_t)(uintptr_t)(p->quan);
case 6:return(uint64_t)(uintptr_t)(p->spe);
case 7:return(uint64_t)(uintptr_t)(p->corpsenm);
case 8:return(uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 44:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_class);
case 1:return(uint64_t)(uintptr_t)(p->oc_prob);
default:abort();}}
case 45:{struct oextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oname);
default:abort();}}
case 46:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mresists);
case 1:return(uint64_t)(uintptr_t)(p->mflags1);
case 2:return(uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 47:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 48:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
case 1:return(uint64_t)(uintptr_t)(p->typ);
case 2:return(uint64_t)(uintptr_t)(p->seenv);
case 3:return(uint64_t)(uintptr_t)(p->flags);
case 4:return(uint64_t)(uintptr_t)(p->horizontal);
case 5:return(uint64_t)(uintptr_t)(p->lit);
case 6:return(uint64_t)(uintptr_t)(p->waslit);
case 7:return(uint64_t)(uintptr_t)(p->roomno);
case 8:return(uint64_t)(uintptr_t)(p->edge);
case 9:return(uint64_t)(uintptr_t)(p->candig);
default:abort();}}
case 49:{struct s_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dlevel);
case 1:return(uint64_t)(uintptr_t)(p->rndlevs);
case 2:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 50:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->something_worth_saving);
default:abort();}}
case 51:{struct stairway*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sx);
case 1:return(uint64_t)(uintptr_t)(p->sy);
default:abort();}}
case 52:{union str_or_len*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->str);
default:abort();}}
case 53:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ntrap);
case 1:return(uint64_t)(uintptr_t)(p->tx);
case 2:return(uint64_t)(uintptr_t)(p->ty);
case 3:return(uint64_t)(uintptr_t)(&p->dst);
case 4:return(uint64_t)(uintptr_t)(p->ttyp);
default:abort();}}
case 54:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 55:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 56:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(p->dx);
case 3:return(uint64_t)(uintptr_t)(p->dy);
case 4:return(uint64_t)(uintptr_t)(&p->uz);
case 5:return(uint64_t)(uintptr_t)(&p->uprops);
case 6:return(uint64_t)(uintptr_t)(p->uswallow);
case 7:return(uint64_t)(uintptr_t)(&p->uroleplay);
case 8:return(uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
default:abort();}}
void teleport_mkmaze_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:p->player_flags=(__typeof__(p->player_flags))value;return;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 2:{__typeof__(((lev_region*)0)->inarea)*p=at;switch(field){
case 0:p->x1=(__typeof__(p->x1))value;return;
case 1:p->y1=(__typeof__(p->y1))value;return;
case 2:p->x2=(__typeof__(p->x2))value;return;
case 3:p->y2=(__typeof__(p->y2))value;return;
default:abort();}}
case 3:{__typeof__(((lev_region*)0)->delarea)*p=at;switch(field){
case 0:p->x1=(__typeof__(p->x1))value;return;
case 1:p->y1=(__typeof__(p->y1))value;return;
case 2:p->x2=(__typeof__(p->x2))value;return;
case 3:p->y2=(__typeof__(p->y2))value;return;
default:abort();}}
case 4:{struct bubble*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
case 2:p->dx=(__typeof__(p->dx))value;return;
case 3:p->dy=(__typeof__(p->dy))value;return;
case 5:p->prev=(__typeof__(p->prev))value;return;
case 6:p->next=(__typeof__(p->next))value;return;
case 7:p->cons=(__typeof__(p->cons))value;return;
default:abort();}}
case 5:{struct container*p=at;switch(field){
case 0:p->next=(__typeof__(p->next))value;return;
case 1:p->x=(__typeof__(p->x))value;return;
case 2:p->y=(__typeof__(p->y))value;return;
case 3:p->what=(__typeof__(p->what))value;return;
case 4:p->list=(__typeof__(p->list))value;return;
default:abort();}}
case 6:{struct d_flags*p=at;switch(field){
case 0:p->town=(unsigned int)value;return;
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 8:{struct dest_area*p=at;switch(field){
case 0:p->lx=(__typeof__(p->lx))value;return;
case 1:p->ly=(__typeof__(p->ly))value;return;
case 2:p->hx=(__typeof__(p->hx))value;return;
case 3:p->hy=(__typeof__(p->hy))value;return;
case 4:p->nlx=(__typeof__(p->nlx))value;return;
case 5:p->nly=(__typeof__(p->nly))value;return;
case 6:p->nhx=(__typeof__(p->nhx))value;return;
case 7:p->nhy=(__typeof__(p->nhy))value;return;
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
case 7:p->d_sokoban_dnum=(__typeof__(p->d_sokoban_dnum))value;return;
case 8:p->d_mines_dnum=(__typeof__(p->d_mines_dnum))value;return;
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 3:p->monlist=(__typeof__(p->monlist))value;return;
default:abort();}}
case 11:{struct dungeon*p=at;switch(field){
case 2:p->depth_start=(__typeof__(p->depth_start))value;return;
default:abort();}}
case 12:{struct exclusion_zone*p=at;switch(field){
case 0:p->zonetype=(__typeof__(p->zonetype))value;return;
case 1:p->lx=(__typeof__(p->lx))value;return;
case 2:p->ly=(__typeof__(p->ly))value;return;
case 3:p->hx=(__typeof__(p->hx))value;return;
case 4:p->hy=(__typeof__(p->hy))value;return;
case 5:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 13:{struct flag*p=at;switch(field){
case 0:p->debug=(__typeof__(p->debug))value;return;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(__typeof__(p->last_msg))value;return;
case 1:p->debug_overwrite_stairs=(__typeof__(p->debug_overwrite_stairs))value;return;
default:abort();}}
case 15:{struct instance_globals_b*p=at;switch(field){
default:abort();}}
case 16:{struct instance_globals_e*p=at;switch(field){
case 0:p->ebubbles=(__typeof__(p->ebubbles))value;return;
default:abort();}}
case 17:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(__typeof__(p->ftrap))value;return;
default:abort();}}
case 18:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_mk_themerooms=(__typeof__(p->in_mk_themerooms))value;return;
default:abort();}}
case 19:{struct instance_globals_l*p=at;switch(field){
case 0:p->lregions=(__typeof__(p->lregions))value;return;
default:abort();}}
case 20:{struct instance_globals_n*p=at;switch(field){
case 0:p->num_lregions=(__typeof__(p->num_lregions))value;return;
default:abort();}}
case 21:{struct instance_globals_r*p=at;switch(field){
case 0:p->ransacked=(__typeof__(p->ransacked))value;return;
default:abort();}}
case 22:{struct instance_globals_saved_b*p=at;switch(field){
case 0:p->bbubbles=(__typeof__(p->bbubbles))value;return;
default:abort();}}
case 23:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_saved_e*p=at;switch(field){
case 0:p->exclusion_zones=(__typeof__(p->exclusion_zones))value;return;
default:abort();}}
case 25:{struct instance_globals_saved_i*p=at;switch(field){
default:abort();}}
case 26:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_saved_n*p=at;switch(field){
case 0:p->nroom=(__typeof__(p->nroom))value;return;
default:abort();}}
case 28:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 29:{struct instance_globals_saved_u*p=at;switch(field){
default:abort();}}
case 30:{struct instance_globals_saved_x*p=at;switch(field){
case 0:p->xmin=(__typeof__(p->xmin))value;return;
case 1:p->xmax=(__typeof__(p->xmax))value;return;
default:abort();}}
case 31:{struct instance_globals_saved_y*p=at;switch(field){
case 0:p->ymin=(__typeof__(p->ymin))value;return;
case 1:p->ymax=(__typeof__(p->ymax))value;return;
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:p->vision_full_recalc=(__typeof__(p->vision_full_recalc))value;return;
default:abort();}}
case 34:{struct instance_globals_w*p=at;switch(field){
case 0:p->wportal=(__typeof__(p->wportal))value;return;
default:abort();}}
case 35:{struct instance_globals_x*p=at;switch(field){
case 0:p->x_maze_max=(__typeof__(p->x_maze_max))value;return;
default:abort();}}
case 36:{struct instance_globals_y*p=at;switch(field){
case 0:p->y_maze_max=(__typeof__(p->y_maze_max))value;return;
default:abort();}}
case 37:{lev_region*p=at;switch(field){
case 2:p->rtype=(__typeof__(p->rtype))value;return;
default:abort();}}
case 38:{struct levelflags*p=at;switch(field){
case 0:p->hero_memory=(unsigned int)value;return;
case 1:p->graveyard=(unsigned int)value;return;
case 2:p->is_maze_lev=(unsigned int)value;return;
case 3:p->has_town=(unsigned int)value;return;
case 4:p->corrmaze=(unsigned int)value;return;
case 5:p->temperature=(__typeof__(p->temperature))value;return;
default:abort();}}
case 39:{struct mextra*p=at;switch(field){
case 0:p->mgivenname=(__typeof__(p->mgivenname))value;return;
default:abort();}}
case 40:{struct monst*p=at;switch(field){
case 0:p->nmon=(__typeof__(p->nmon))value;return;
case 1:p->data=(__typeof__(p->data))value;return;
case 2:p->mx=(__typeof__(p->mx))value;return;
case 3:p->my=(__typeof__(p->my))value;return;
case 4:p->mhp=(__typeof__(p->mhp))value;return;
case 5:p->mpeaceful=(unsigned int)value;return;
case 6:p->mtrapped=(unsigned int)value;return;
case 7:p->wormno=(unsigned int)value;return;
case 8:p->mstate=(__typeof__(p->mstate))value;return;
case 9:p->migflags=(__typeof__(p->migflags))value;return;
case 10:p->mextra=(__typeof__(p->mextra))value;return;
default:abort();}}
case 41:{struct nh_file*p=at;switch(field){
case 0:p->mode=(__typeof__(p->mode))value;return;
default:abort();}}
case 42:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 43:{struct obj*p=at;switch(field){
case 1:p->ox=(__typeof__(p->ox))value;return;
case 2:p->oy=(__typeof__(p->oy))value;return;
case 3:p->otyp=(__typeof__(p->otyp))value;return;
case 4:p->owt=(__typeof__(p->owt))value;return;
case 5:p->quan=(__typeof__(p->quan))value;return;
case 6:p->spe=(__typeof__(p->spe))value;return;
case 7:p->corpsenm=(__typeof__(p->corpsenm))value;return;
case 8:p->oextra=(__typeof__(p->oextra))value;return;
default:abort();}}
case 44:{struct objclass*p=at;switch(field){
case 0:p->oc_class=(__typeof__(p->oc_class))value;return;
case 1:p->oc_prob=(__typeof__(p->oc_prob))value;return;
default:abort();}}
case 45:{struct oextra*p=at;switch(field){
case 0:p->oname=(__typeof__(p->oname))value;return;
default:abort();}}
case 46:{struct permonst*p=at;switch(field){
case 0:p->mresists=(__typeof__(p->mresists))value;return;
case 1:p->mflags1=(__typeof__(p->mflags1))value;return;
case 2:p->mflags2=(__typeof__(p->mflags2))value;return;
default:abort();}}
case 47:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(__typeof__(p->extrinsic))value;return;
case 1:p->intrinsic=(__typeof__(p->intrinsic))value;return;
default:abort();}}
case 48:{struct rm*p=at;switch(field){
case 0:p->glyph=(__typeof__(p->glyph))value;return;
case 1:p->typ=(__typeof__(p->typ))value;return;
case 2:p->seenv=(__typeof__(p->seenv))value;return;
case 3:p->flags=(unsigned int)value;return;
case 4:p->horizontal=(unsigned int)value;return;
case 5:p->lit=(unsigned int)value;return;
case 6:p->waslit=(unsigned int)value;return;
case 7:p->roomno=(unsigned int)value;return;
case 8:p->edge=(unsigned int)value;return;
case 9:p->candig=(unsigned int)value;return;
default:abort();}}
case 49:{struct s_level*p=at;switch(field){
case 1:p->rndlevs=(__typeof__(p->rndlevs))value;return;
default:abort();}}
case 50:{struct sinfo*p=at;switch(field){
case 0:p->something_worth_saving=(__typeof__(p->something_worth_saving))value;return;
default:abort();}}
case 51:{struct stairway*p=at;switch(field){
case 0:p->sx=(__typeof__(p->sx))value;return;
case 1:p->sy=(__typeof__(p->sy))value;return;
default:abort();}}
case 52:{union str_or_len*p=at;switch(field){
case 0:p->str=(__typeof__(p->str))value;return;
default:abort();}}
case 53:{struct trap*p=at;switch(field){
case 0:p->ntrap=(__typeof__(p->ntrap))value;return;
case 1:p->tx=(__typeof__(p->tx))value;return;
case 2:p->ty=(__typeof__(p->ty))value;return;
case 4:p->ttyp=(unsigned int)value;return;
default:abort();}}
case 54:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=(__typeof__(p->deaf))value;return;
default:abort();}}
case 55:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(__typeof__(p->v_nexthere))value;return;
default:abort();}}
case 56:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 2:p->dx=(__typeof__(p->dx))value;return;
case 3:p->dy=(__typeof__(p->dy))value;return;
case 6:p->uswallow=(unsigned int)value;return;
case 8:p->usteed=(__typeof__(p->usteed))value;return;
default:abort();}}
default:abort();}}
void* teleport_mkmaze_address(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(void*)&p->player_flags;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{__typeof__(((lev_region*)0)->inarea)*p=at;switch(field){
case 0:return(void*)&p->x1;
case 1:return(void*)&p->y1;
case 2:return(void*)&p->x2;
case 3:return(void*)&p->y2;
default:abort();}}
case 3:{__typeof__(((lev_region*)0)->delarea)*p=at;switch(field){
case 0:return(void*)&p->x1;
case 1:return(void*)&p->y1;
case 2:return(void*)&p->x2;
case 3:return(void*)&p->y2;
default:abort();}}
case 4:{struct bubble*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
case 2:return(void*)&p->dx;
case 3:return(void*)&p->dy;
case 4:return(void*)&p->bm;
case 5:return(void*)&p->prev;
case 6:return(void*)&p->next;
case 7:return(void*)&p->cons;
default:abort();}}
case 5:{struct container*p=at;switch(field){
case 0:return(void*)&p->next;
case 1:return(void*)&p->x;
case 2:return(void*)&p->y;
case 3:return(void*)&p->what;
case 4:return(void*)&p->list;
default:abort();}}
case 6:{struct d_flags*p=at;switch(field){
default:abort();}}
case 7:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 8:{struct dest_area*p=at;switch(field){
case 0:return(void*)&p->lx;
case 1:return(void*)&p->ly;
case 2:return(void*)&p->hx;
case 3:return(void*)&p->hy;
case 4:return(void*)&p->nlx;
case 5:return(void*)&p->nly;
case 6:return(void*)&p->nhx;
case 7:return(void*)&p->nhy;
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_medusa_level;
case 1:return(void*)&p->d_stronghold_level;
case 2:return(void*)&p->d_baalzebub_level;
case 3:return(void*)&p->d_earth_level;
case 4:return(void*)&p->d_water_level;
case 5:return(void*)&p->d_fire_level;
case 6:return(void*)&p->d_air_level;
case 7:return(void*)&p->d_sokoban_dnum;
case 8:return(void*)&p->d_mines_dnum;
case 9:return(void*)&p->d_knox_level;
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->monlist;
case 4:return(void*)&p->flags;
default:abort();}}
case 11:{struct dungeon*p=at;switch(field){
case 0:return(void*)&p->dname;
case 1:return(void*)&p->proto;
case 2:return(void*)&p->depth_start;
default:abort();}}
case 12:{struct exclusion_zone*p=at;switch(field){
case 0:return(void*)&p->zonetype;
case 1:return(void*)&p->lx;
case 2:return(void*)&p->ly;
case 3:return(void*)&p->hx;
case 4:return(void*)&p->hy;
case 5:return(void*)&p->next;
default:abort();}}
case 13:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
case 1:return(void*)&p->debug_overwrite_stairs;
default:abort();}}
case 15:{struct instance_globals_b*p=at;switch(field){
case 0:return(void*)&p->bughack;
default:abort();}}
case 16:{struct instance_globals_e*p=at;switch(field){
case 0:return(void*)&p->ebubbles;
default:abort();}}
case 17:{struct instance_globals_f*p=at;switch(field){
case 0:return(void*)&p->ftrap;
default:abort();}}
case 18:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_mk_themerooms;
default:abort();}}
case 19:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->lregions;
default:abort();}}
case 20:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->num_lregions;
default:abort();}}
case 21:{struct instance_globals_r*p=at;switch(field){
case 0:return(void*)&p->ransacked;
default:abort();}}
case 22:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(void*)&p->bbubbles;
default:abort();}}
case 23:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeons;
case 1:return(void*)&p->dungeon_topology;
case 2:return(void*)&p->dndest;
default:abort();}}
case 24:{struct instance_globals_saved_e*p=at;switch(field){
case 0:return(void*)&p->exclusion_zones;
default:abort();}}
case 25:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(void*)&p->inv_pos;
default:abort();}}
case 26:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 27:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(void*)&p->nroom;
default:abort();}}
case 28:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(void*)&p->rooms;
default:abort();}}
case 29:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return(void*)&p->updest;
default:abort();}}
case 30:{struct instance_globals_saved_x*p=at;switch(field){
case 0:return(void*)&p->xmin;
case 1:return(void*)&p->xmax;
default:abort();}}
case 31:{struct instance_globals_saved_y*p=at;switch(field){
case 0:return(void*)&p->ymin;
case 1:return(void*)&p->ymax;
default:abort();}}
case 32:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
case 1:return(void*)&p->uz_save;
default:abort();}}
case 33:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->vision_full_recalc;
default:abort();}}
case 34:{struct instance_globals_w*p=at;switch(field){
case 0:return(void*)&p->wportal;
default:abort();}}
case 35:{struct instance_globals_x*p=at;switch(field){
case 0:return(void*)&p->x_maze_max;
default:abort();}}
case 36:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->y_maze_max;
default:abort();}}
case 37:{lev_region*p=at;switch(field){
case 0:return(void*)&p->inarea;
case 1:return(void*)&p->delarea;
case 2:return(void*)&p->rtype;
case 3:return(void*)&p->rname;
default:abort();}}
case 38:{struct levelflags*p=at;switch(field){
case 5:return(void*)&p->temperature;
default:abort();}}
case 39:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->mgivenname;
default:abort();}}
case 40:{struct monst*p=at;switch(field){
case 0:return(void*)&p->nmon;
case 1:return(void*)&p->data;
case 2:return(void*)&p->mx;
case 3:return(void*)&p->my;
case 4:return(void*)&p->mhp;
case 8:return(void*)&p->mstate;
case 9:return(void*)&p->migflags;
case 10:return(void*)&p->mextra;
default:abort();}}
case 41:{struct nh_file*p=at;switch(field){
case 0:return(void*)&p->mode;
default:abort();}}
case 42:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 43:{struct obj*p=at;switch(field){
case 0:return(void*)&p->v;
case 1:return(void*)&p->ox;
case 2:return(void*)&p->oy;
case 3:return(void*)&p->otyp;
case 4:return(void*)&p->owt;
case 5:return(void*)&p->quan;
case 6:return(void*)&p->spe;
case 7:return(void*)&p->corpsenm;
case 8:return(void*)&p->oextra;
default:abort();}}
case 44:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_class;
case 1:return(void*)&p->oc_prob;
default:abort();}}
case 45:{struct oextra*p=at;switch(field){
case 0:return(void*)&p->oname;
default:abort();}}
case 46:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->mresists;
case 1:return(void*)&p->mflags1;
case 2:return(void*)&p->mflags2;
default:abort();}}
case 47:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->intrinsic;
default:abort();}}
case 48:{struct rm*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->typ;
case 2:return(void*)&p->seenv;
default:abort();}}
case 49:{struct s_level*p=at;switch(field){
case 0:return(void*)&p->dlevel;
case 1:return(void*)&p->rndlevs;
case 2:return(void*)&p->flags;
default:abort();}}
case 50:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->something_worth_saving;
default:abort();}}
case 51:{struct stairway*p=at;switch(field){
case 0:return(void*)&p->sx;
case 1:return(void*)&p->sy;
default:abort();}}
case 52:{union str_or_len*p=at;switch(field){
case 0:return(void*)&p->str;
default:abort();}}
case 53:{struct trap*p=at;switch(field){
case 0:return(void*)&p->ntrap;
case 1:return(void*)&p->tx;
case 2:return(void*)&p->ty;
case 3:return(void*)&p->dst;
default:abort();}}
case 54:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->deaf;
default:abort();}}
case 55:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
default:abort();}}
case 56:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->dx;
case 3:return(void*)&p->dy;
case 4:return(void*)&p->uz;
case 5:return(void*)&p->uprops;
case 7:return(void*)&p->uroleplay;
case 8:return(void*)&p->usteed;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_mkmaze_var0(char * a0,int a1,int a2,int a3,int a4){(panic)(a0,a1,a2,a3,a4);}
void teleport_mkmaze_var1(char * a0,int a1,int a2,int a3,int a4){(panic)(a0,a1,a2,a3,a4);}
void teleport_mkmaze_var2(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var3(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var4(char * a0,int a1){(impossible)(a0,a1);}
void teleport_mkmaze_var5(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var6(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var7(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var8(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var9(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_mkmaze_var10(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,int a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_mkmaze_var11(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,int a6,int a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_mkmaze_var12(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,int a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_mkmaze_var13(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,int a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
int teleport_mkmaze_var14(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_mkmaze_var15(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_mkmaze_var16(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var17(char * a0,int a1){(panic)(a0,a1);}
void teleport_mkmaze_var18(char * a0){(panic)(a0);}
void teleport_mkmaze_var19(char * a0){(impossible)(a0);}
void teleport_mkmaze_var20(char * a0,int a1,int a2,char * a3,int a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_mkmaze_var21(char * a0,char * a1){(Norep)(a0,a1);}
void teleport_mkmaze_var22(char * a0){(panic)(a0);}
void teleport_mkmaze_var23(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_mkmaze_var24(char * a0){(pline)(a0);}
void teleport_mkmaze_var25(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_mkmaze_var26(char * a0){(impossible)(a0);}
void teleport_mkmaze_var27(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
void teleport_mkmaze_var28(char * a0){(impossible)(a0);}
void teleport_mkmaze_var29(char * a0){(panic)(a0);}
void teleport_mkmaze_var30(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_mkmaze_var31(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_mkmaze_var32(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_mkmaze_var33(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_mkmaze_var34(char * a0){(impossible)(a0);}
#pragma clang diagnostic pop
void teleport_mkmaze_free(void*p){(free)(p);}
static char mkmaze_literals[1290];
char*teleport_mkmaze_literal_storage(void){return mkmaze_literals;}
size_t teleport_mkmaze_literal_capacity(void){return sizeof mkmaze_literals;}
static short mkmaze_backing_0[16];
static char * mkmaze_backing_1[2];
static struct bubble * mkmaze_backing_2;
static struct rm mkmaze_backing_3;
static struct rm mkmaze_backing_4;
static signed char mkmaze_backing_5;
static unsigned char mkmaze_backing_6[3];
static unsigned char mkmaze_backing_7[4];
static unsigned char mkmaze_backing_8[5];
static unsigned char mkmaze_backing_9[5];
static unsigned char mkmaze_backing_10[6];
static unsigned char mkmaze_backing_11[6];
static unsigned char mkmaze_backing_12[6];
static unsigned char * mkmaze_backing_13[7];
void*teleport_mkmaze_storage(int i){switch(i){
case 0:return &mkmaze_backing_0;
case 1:return &mkmaze_backing_1;
case 2:return &mkmaze_backing_2;
case 3:return &mkmaze_backing_3;
case 4:return &mkmaze_backing_4;
case 5:return &mkmaze_backing_5;
case 6:return &mkmaze_backing_6;
case 7:return &mkmaze_backing_7;
case 8:return &mkmaze_backing_8;
case 9:return &mkmaze_backing_9;
case 10:return &mkmaze_backing_10;
case 11:return &mkmaze_backing_11;
case 12:return &mkmaze_backing_12;
case 13:return &mkmaze_backing_13;
default:abort();}}
