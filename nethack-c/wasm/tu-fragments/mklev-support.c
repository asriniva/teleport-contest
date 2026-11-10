/* MKLEV ABI/header/native dependency transport and zero backing only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(size_t)==8,"MKLEV memory64 LP64 ABI");
_Static_assert(sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"MKLEV signed native scalar ABI");
void*teleport_mklev_global(int index){switch(index){
case 0:return(void*)&svl;
case 1:return(void*)&xdir;
case 2:return(void*)&ydir;
case 3:return(void*)&svr;
case 4:return(void*)&svn;
case 5:return(void*)&gd;
case 6:return(void*)&gn;
case 7:return(void*)&gs;
case 8:return(void*)&svd;
case 9:return(void*)&gl;
case 10:return(void*)&u;
case 11:return(void*)&iflags;
case 12:return(void*)&gi;
case 13:return(void*)&gt;
case 14:return(void*)&gv;
case 15:return(void*)&svm;
case 16:return(void*)&gm;
case 17:return(void*)&mons;
case 18:return(void*)&objects;
case 19:return(void*)&gc;
case 20:return(void*)&gu;
case 21:return(void*)&flags;
case 22:return(void*)&nhcb_counts;
case 23:return(void*)&nhcb_name;
case 24:return(void*)&gx;
case 25:return(void*)&gy;
case 26:return(void*)&defsyms;
case 27:return(void*)&svi;
case 28:return(void*)&WIN_MESSAGE;
case 29:return(void*)&windowprocs;
default:abort();}}
uint64_t teleport_mklev_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(dlevel_t));
case 6:return(uint64_t)(sizeof(struct Role));
case 7:return(uint64_t)(sizeof(struct branch));
case 8:return(uint64_t)(sizeof(struct d_flags));
case 9:return(uint64_t)(sizeof(struct d_level));
case 10:return(uint64_t)(sizeof(struct dgn_topology));
case 11:return(uint64_t)(sizeof(struct dungeon));
case 12:return(uint64_t)(sizeof(struct flag));
case 13:return(uint64_t)(sizeof(struct instance_flags));
case 14:return(uint64_t)(sizeof(struct instance_globals_c));
case 15:return(uint64_t)(sizeof(struct instance_globals_d));
case 16:return(uint64_t)(sizeof(struct instance_globals_i));
case 17:return(uint64_t)(sizeof(struct instance_globals_l));
case 18:return(uint64_t)(sizeof(struct instance_globals_m));
case 19:return(uint64_t)(sizeof(struct instance_globals_n));
case 20:return(uint64_t)(sizeof(struct instance_globals_s));
case 21:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 22:return(uint64_t)(sizeof(struct instance_globals_saved_i));
case 23:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 24:return(uint64_t)(sizeof(struct instance_globals_saved_m));
case 25:return(uint64_t)(sizeof(struct instance_globals_saved_n));
case 26:return(uint64_t)(sizeof(struct instance_globals_saved_r));
case 27:return(uint64_t)(sizeof(struct instance_globals_t));
case 28:return(uint64_t)(sizeof(struct instance_globals_u));
case 29:return(uint64_t)(sizeof(struct instance_globals_v));
case 30:return(uint64_t)(sizeof(struct instance_globals_x));
case 31:return(uint64_t)(sizeof(struct instance_globals_y));
case 32:return(uint64_t)(sizeof(struct levelflags));
case 33:return(uint64_t)(sizeof(struct mkroom));
case 34:return(uint64_t)(sizeof(struct monst));
case 35:return(uint64_t)(sizeof(struct mvitals));
case 36:return(uint64_t)(sizeof(struct nhcoord));
case 37:return(uint64_t)(sizeof(struct nhl_sandbox_info));
case 38:return(uint64_t)(sizeof(struct obj));
case 39:return(uint64_t)(sizeof(struct objclass));
case 40:return(uint64_t)(sizeof(struct permonst));
case 41:return(uint64_t)(sizeof(struct rm));
case 42:return(uint64_t)(sizeof(struct s_level));
case 43:return(uint64_t)(sizeof(struct stairway));
case 44:return(uint64_t)(sizeof(struct symdef));
case 45:return(uint64_t)(sizeof(struct trap));
case 46:return(uint64_t)(sizeof(struct u_have));
case 47:return(uint64_t)(sizeof(struct window_procs));
case 48:return(uint64_t)(sizeof(struct you));
case 49:return(uint64_t)(ALTAR);
case 50:return(uint64_t)(ANTHOLE);
case 51:return(uint64_t)(ARMOR_CLASS);
case 52:return(uint64_t)(ARROW);
case 53:return(uint64_t)(ARROW_TRAP);
case 54:return(uint64_t)(BARRACKS);
case 55:return(uint64_t)(BEAR_TRAP);
case 56:return(uint64_t)(BEEHIVE);
case 57:return(uint64_t)(BELL);
case 58:return(uint64_t)(BLCORNER);
case 59:return(uint64_t)(BOULDER);
case 60:return(uint64_t)(BRCORNER);
case 61:return(uint64_t)(CHEST);
case 62:return(uint64_t)(COCKNEST);
case 63:return(uint64_t)(CORPSE);
case 64:return(uint64_t)(CORR);
case 65:return(uint64_t)(COURT);
case 66:return(uint64_t)(CRAM_RATION);
case 67:return(uint64_t)(DART);
case 68:return(uint64_t)(DART_TRAP);
case 69:return(uint64_t)(DBWALL);
case 70:return(uint64_t)(DIR_E);
case 71:return(uint64_t)(DIR_N);
case 72:return(uint64_t)(DIR_S);
case 73:return(uint64_t)(DIR_W);
case 74:return(uint64_t)(DOOR);
case 75:return(uint64_t)(DRAWBRIDGE_UP);
case 76:return(uint64_t)(FIRE_TRAP);
case 77:return(uint64_t)(FOOD_CLASS);
case 78:return(uint64_t)(FOOD_RATION);
case 79:return(uint64_t)(FOUNTAIN);
case 80:return(uint64_t)(GEM_CLASS);
case 81:return(uint64_t)(GLYPH_UNEXPLORED_OFF);
case 82:return(uint64_t)(GOLD_PIECE);
case 83:return(uint64_t)(HOLE);
case 84:return(uint64_t)(HWALL);
case 85:return(uint64_t)(ICE);
case 86:return(uint64_t)(IRONBARS);
case 87:return(uint64_t)(KELP_FROND);
case 88:return(uint64_t)(LANDMINE);
case 89:return(uint64_t)(LARGE_BOX);
case 90:return(uint64_t)(LEMBAS_WAFER);
case 91:return(uint64_t)(LEPREHALL);
case 92:return(uint64_t)(LEVEL_TELEP);
case 93:return(uint64_t)(MAGIC_PORTAL);
case 94:return(uint64_t)(MAGIC_TRAP);
case 95:return(uint64_t)(MOAT);
case 96:return(uint64_t)(MORGUE);
case 97:return(uint64_t)(NHCB_LVL_ENTER);
case 98:return(uint64_t)(NHLpa_impossible);
case 99:return(uint64_t)(NHLpa_panic);
case 100:return(uint64_t)(NO_TRAP);
case 101:return(uint64_t)(N_DIRS_Z);
case 102:return(uint64_t)(OROOM);
case 103:return(uint64_t)(PIT);
case 104:return(uint64_t)(PM_ARCHEOLOGIST);
case 105:return(uint64_t)(PM_COCKATRICE);
case 106:return(uint64_t)(PM_DWARF);
case 107:return(uint64_t)(PM_ELF);
case 108:return(uint64_t)(PM_GIANT_MIMIC);
case 109:return(uint64_t)(PM_GIANT_SPIDER);
case 110:return(uint64_t)(PM_GNOME);
case 111:return(uint64_t)(PM_HUMAN);
case 112:return(uint64_t)(PM_KILLER_BEE);
case 113:return(uint64_t)(PM_LARGE_MIMIC);
case 114:return(uint64_t)(PM_LEPRECHAUN);
case 115:return(uint64_t)(PM_ORC);
case 116:return(uint64_t)(PM_SMALL_MIMIC);
case 117:return(uint64_t)(PM_SOLDIER);
case 118:return(uint64_t)(PM_WIZARD);
case 119:return(uint64_t)(POLY_TRAP);
case 120:return(uint64_t)(POOL);
case 121:return(uint64_t)(POTION_CLASS);
case 122:return(uint64_t)(POT_EXTRA_HEALING);
case 123:return(uint64_t)(POT_GAIN_ENERGY);
case 124:return(uint64_t)(POT_HEALING);
case 125:return(uint64_t)(POT_SPEED);
case 126:return(uint64_t)(RANDOM_CLASS);
case 127:return(uint64_t)(RING_CLASS);
case 128:return(uint64_t)(ROCK);
case 129:return(uint64_t)(ROCKTRAP);
case 130:return(uint64_t)(ROLLING_BOULDER_TRAP);
case 131:return(uint64_t)(ROOM);
case 132:return(uint64_t)(RUST_TRAP);
case 133:return(uint64_t)(SCORR);
case 134:return(uint64_t)(SCROLL_CLASS);
case 135:return(uint64_t)(SCR_CONFUSE_MONSTER);
case 136:return(uint64_t)(SCR_ENCHANT_ARMOR);
case 137:return(uint64_t)(SCR_ENCHANT_WEAPON);
case 138:return(uint64_t)(SCR_SCARE_MONSTER);
case 139:return(uint64_t)(SCR_TELEPORTATION);
case 140:return(uint64_t)(SDOOR);
case 141:return(uint64_t)(SHOPBASE);
case 142:return(uint64_t)(SINK);
case 143:return(uint64_t)(SLP_GAS_TRAP);
case 144:return(uint64_t)(SPBOOK_CLASS);
case 145:return(uint64_t)(SPE_HEALING);
case 146:return(uint64_t)(SPIKED_PIT);
case 147:return(uint64_t)(SQKY_BOARD);
case 148:return(uint64_t)(STAIRS);
case 149:return(uint64_t)(STATUE);
case 150:return(uint64_t)(STATUE_TRAP);
case 151:return(uint64_t)(STONE);
case 152:return(uint64_t)(SWAMP);
case 153:return(uint64_t)(S_HUMAN);
case 154:return(uint64_t)(S_MIMIC);
case 155:return(uint64_t)(TALLOW_CANDLE);
case 156:return(uint64_t)(TELEP_TRAP);
case 157:return(uint64_t)(TEMPLE);
case 158:return(uint64_t)(THEMEROOM);
case 159:return(uint64_t)(TLCORNER);
case 160:return(uint64_t)(TOOL_CLASS);
case 161:return(uint64_t)(TRAPDOOR);
case 162:return(uint64_t)(TRAPNUM);
case 163:return(uint64_t)(TRAPPED_CHEST);
case 164:return(uint64_t)(TRAPPED_DOOR);
case 165:return(uint64_t)(TRCORNER);
case 166:return(uint64_t)(TREE);
case 167:return(uint64_t)(TT_BURIEDBALL);
case 168:return(uint64_t)(VAULT);
case 169:return(uint64_t)(VIBRATING_SQUARE);
case 170:return(uint64_t)(VWALL);
case 171:return(uint64_t)(WAN_DIGGING);
case 172:return(uint64_t)(WATER);
case 173:return(uint64_t)(WAX_CANDLE);
case 174:return(uint64_t)(WEAPON_CLASS);
case 175:return(uint64_t)(WEB);
case 176:return(uint64_t)(ZOO);
case 177:return(uint64_t)(most_themes);
case 178:return(uint64_t)(tut_themes);
default:abort();}}
uint64_t teleport_mklev_read(int kind,void*at,int field){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 1:{struct branch*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->type);
case 1:return(uint64_t)(uintptr_t)(&p->end1);
case 2:return(uint64_t)(uintptr_t)(&p->end2);
case 3:return(uint64_t)(uintptr_t)(p->end1_up);
default:abort();}}
case 2:{struct d_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->town);
default:abort();}}
case 3:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 4:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_oracle_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_rogue_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_medusa_level);
case 3:return(uint64_t)(uintptr_t)(&p->d_wiz1_level);
case 4:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 5:return(uint64_t)(uintptr_t)(&p->d_astral_level);
case 6:return(uint64_t)(uintptr_t)(p->d_mines_dnum);
case 7:return(uint64_t)(uintptr_t)(p->d_tutorial_dnum);
case 8:return(uint64_t)(uintptr_t)(&p->d_knox_level);
default:abort();}}
case 5:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(p->objlist);
case 4:return(uint64_t)(uintptr_t)(p->buriedobjlist);
case 5:return(uint64_t)(uintptr_t)(p->monlist);
case 6:return(uint64_t)(uintptr_t)(p->damagelist);
case 7:return(uint64_t)(uintptr_t)(p->bonesinfo);
case 8:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 6:{struct dungeon*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->proto);
case 1:return(uint64_t)(uintptr_t)(&p->fill_lvl);
case 2:return(uint64_t)(uintptr_t)(&p->themerms);
default:abort();}}
case 7:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
default:abort();}}
case 8:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_lua);
case 1:return(uint64_t)(uintptr_t)(p->debug_fuzzer);
case 2:return(uint64_t)(uintptr_t)(p->last_msg);
case 3:return(uint64_t)(uintptr_t)(p->sanity_check);
default:abort();}}
case 9:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->coder);
default:abort();}}
case 10:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->doorindex);
default:abort();}}
case 11:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_mklev);
case 1:return(uint64_t)(uintptr_t)(p->in_mk_themerooms);
default:abort();}}
case 12:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->luathemes);
case 1:return(uint64_t)(uintptr_t)(p->luacore);
case 2:return(uint64_t)(uintptr_t)(p->lev_message);
default:abort();}}
case 13:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->made_branch);
default:abort();}}
case 14:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nsubroom);
default:abort();}}
case 15:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->stairs);
case 1:return(uint64_t)(uintptr_t)(&p->smeq);
case 2:return(uint64_t)(uintptr_t)(p->subrooms);
default:abort();}}
case 16:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeons);
case 1:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
case 2:return(uint64_t)(uintptr_t)(p->doors);
case 3:return(uint64_t)(uintptr_t)(p->doors_alloc);
default:abort();}}
case 17:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->inv_pos);
default:abort();}}
case 18:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 19:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 20:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->n_dgns);
case 1:return(uint64_t)(uintptr_t)(p->nroom);
default:abort();}}
case 21:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 22:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->themeroom_failed);
default:abort();}}
case 23:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 24:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->vault_x);
case 1:return(uint64_t)(uintptr_t)(p->vault_y);
case 2:return(uint64_t)(uintptr_t)(p->viz_array);
case 3:return(uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 25:{struct instance_globals_x*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x_maze_max);
case 1:return(uint64_t)(uintptr_t)(p->xstart);
default:abort();}}
case 26:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->y_maze_max);
case 1:return(uint64_t)(uintptr_t)(p->ystart);
default:abort();}}
case 27:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nfountains);
case 1:return(uint64_t)(uintptr_t)(p->nsinks);
case 2:return(uint64_t)(uintptr_t)(p->has_shop);
case 3:return(uint64_t)(uintptr_t)(p->has_vault);
case 4:return(uint64_t)(uintptr_t)(p->has_zoo);
case 5:return(uint64_t)(uintptr_t)(p->has_court);
case 6:return(uint64_t)(uintptr_t)(p->has_morgue);
case 7:return(uint64_t)(uintptr_t)(p->has_beehive);
case 8:return(uint64_t)(uintptr_t)(p->has_barracks);
case 9:return(uint64_t)(uintptr_t)(p->has_temple);
case 10:return(uint64_t)(uintptr_t)(p->has_swamp);
case 11:return(uint64_t)(uintptr_t)(p->noteleport);
case 12:return(uint64_t)(uintptr_t)(p->hardfloor);
case 13:return(uint64_t)(uintptr_t)(p->nommap);
case 14:return(uint64_t)(uintptr_t)(p->hero_memory);
case 15:return(uint64_t)(uintptr_t)(p->shortsighted);
case 16:return(uint64_t)(uintptr_t)(p->graveyard);
case 17:return(uint64_t)(uintptr_t)(p->sokoban_rules);
case 18:return(uint64_t)(uintptr_t)(p->is_maze_lev);
case 19:return(uint64_t)(uintptr_t)(p->is_cavernous_lev);
case 20:return(uint64_t)(uintptr_t)(p->arboreal);
case 21:return(uint64_t)(uintptr_t)(p->has_town);
case 22:return(uint64_t)(uintptr_t)(p->wizard_bones);
case 23:return(uint64_t)(uintptr_t)(p->corrmaze);
case 24:return(uint64_t)(uintptr_t)(p->rndmongen);
case 25:return(uint64_t)(uintptr_t)(p->deathdrops);
case 26:return(uint64_t)(uintptr_t)(p->noautosearch);
case 27:return(uint64_t)(uintptr_t)(p->fumaroles);
case 28:return(uint64_t)(uintptr_t)(p->stormy);
case 29:return(uint64_t)(uintptr_t)(p->temperature);
case 30:return(uint64_t)(uintptr_t)(p->stasis_until);
default:abort();}}
case 28:{struct mkroom*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lx);
case 1:return(uint64_t)(uintptr_t)(p->hx);
case 2:return(uint64_t)(uintptr_t)(p->ly);
case 3:return(uint64_t)(uintptr_t)(p->hy);
case 4:return(uint64_t)(uintptr_t)(p->rtype);
case 5:return(uint64_t)(uintptr_t)(p->orig_rtype);
case 6:return(uint64_t)(uintptr_t)(p->rlit);
case 7:return(uint64_t)(uintptr_t)(p->needfill);
case 8:return(uint64_t)(uintptr_t)(p->needjoining);
case 9:return(uint64_t)(uintptr_t)(p->doorct);
case 10:return(uint64_t)(uintptr_t)(p->fdoor);
case 11:return(uint64_t)(uintptr_t)(p->nsubrooms);
case 12:return(uint64_t)(uintptr_t)(p->irregular);
case 13:return(uint64_t)(uintptr_t)(p->roomnoidx);
case 14:return(uint64_t)(uintptr_t)(&p->sbrooms);
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->m_ap_type);
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 31:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 32:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->flags);
case 1:return(uint64_t)(uintptr_t)(p->memlimit);
case 2:return(uint64_t)(uintptr_t)(p->steps);
case 3:return(uint64_t)(uintptr_t)(p->perpcall);
default:abort();}}
case 33:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ox);
case 1:return(uint64_t)(uintptr_t)(p->oy);
case 2:return(uint64_t)(uintptr_t)(p->otyp);
case 3:return(uint64_t)(uintptr_t)(p->owt);
case 4:return(uint64_t)(uintptr_t)(p->quan);
case 5:return(uint64_t)(uintptr_t)(p->cursed);
case 6:return(uint64_t)(uintptr_t)(p->olocked);
case 7:return(uint64_t)(uintptr_t)(p->otrapped);
case 8:return(uint64_t)(uintptr_t)(p->age);
default:abort();}}
case 34:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_oc2);
default:abort();}}
case 35:{struct rm*p=at;switch(field){
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
case 36:{struct s_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dlevel);
case 1:return(uint64_t)(uintptr_t)(&p->proto);
case 2:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 37:{struct stairway*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->u_traversed);
default:abort();}}
case 38:{struct symdef*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->explanation);
default:abort();}}
case 39:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tx);
case 1:return(uint64_t)(uintptr_t)(p->ty);
case 2:return(uint64_t)(uintptr_t)(&p->dst);
case 3:return(uint64_t)(uintptr_t)(&p->launch);
case 4:return(uint64_t)(uintptr_t)(p->ttyp);
case 5:return(uint64_t)(uintptr_t)(p->tseen);
case 6:return(uint64_t)(uintptr_t)(p->once);
default:abort();}}
case 40:{struct u_have*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->amulet);
default:abort();}}
case 41:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 1:return(uint64_t)(uintptr_t)(p->win_delay_output);
default:abort();}}
case 42:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(&p->uz);
case 3:return(uint64_t)(uintptr_t)(&p->ucamefrom);
case 4:return(uint64_t)(uintptr_t)(p->utrap);
case 5:return(uint64_t)(uintptr_t)(p->utraptype);
case 6:return(uint64_t)(uintptr_t)(&p->uhave);
default:abort();}}
default:abort();}}
void teleport_mklev_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:p->filecode=(__typeof__(p->filecode))value;return;
default:abort();}}
case 1:{struct branch*p=at;switch(field){
case 0:p->type=(__typeof__(p->type))value;return;
case 3:p->end1_up=(__typeof__(p->end1_up))value;return;
default:abort();}}
case 2:{struct d_flags*p=at;switch(field){
case 0:p->town=(unsigned int)value;return;
default:abort();}}
case 3:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 4:{struct dgn_topology*p=at;switch(field){
case 6:p->d_mines_dnum=(__typeof__(p->d_mines_dnum))value;return;
case 7:p->d_tutorial_dnum=(__typeof__(p->d_tutorial_dnum))value;return;
default:abort();}}
case 5:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(__typeof__(p->objlist))value;return;
case 4:p->buriedobjlist=(__typeof__(p->buriedobjlist))value;return;
case 5:p->monlist=(__typeof__(p->monlist))value;return;
case 6:p->damagelist=(__typeof__(p->damagelist))value;return;
case 7:p->bonesinfo=(__typeof__(p->bonesinfo))value;return;
default:abort();}}
case 6:{struct dungeon*p=at;switch(field){
default:abort();}}
case 7:{struct flag*p=at;switch(field){
case 0:p->debug=(__typeof__(p->debug))value;return;
default:abort();}}
case 8:{struct instance_flags*p=at;switch(field){
case 0:p->in_lua=(__typeof__(p->in_lua))value;return;
case 1:p->debug_fuzzer=(__typeof__(p->debug_fuzzer))value;return;
case 2:p->last_msg=(__typeof__(p->last_msg))value;return;
case 3:p->sanity_check=(__typeof__(p->sanity_check))value;return;
default:abort();}}
case 9:{struct instance_globals_c*p=at;switch(field){
case 0:p->coder=(__typeof__(p->coder))value;return;
default:abort();}}
case 10:{struct instance_globals_d*p=at;switch(field){
case 0:p->doorindex=(__typeof__(p->doorindex))value;return;
default:abort();}}
case 11:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_mklev=(__typeof__(p->in_mklev))value;return;
case 1:p->in_mk_themerooms=(__typeof__(p->in_mk_themerooms))value;return;
default:abort();}}
case 12:{struct instance_globals_l*p=at;switch(field){
case 1:p->luacore=(__typeof__(p->luacore))value;return;
case 2:p->lev_message=(__typeof__(p->lev_message))value;return;
default:abort();}}
case 13:{struct instance_globals_m*p=at;switch(field){
case 0:p->made_branch=(__typeof__(p->made_branch))value;return;
default:abort();}}
case 14:{struct instance_globals_n*p=at;switch(field){
case 0:p->nsubroom=(__typeof__(p->nsubroom))value;return;
default:abort();}}
case 15:{struct instance_globals_s*p=at;switch(field){
case 0:p->stairs=(__typeof__(p->stairs))value;return;
case 2:p->subrooms=(__typeof__(p->subrooms))value;return;
default:abort();}}
case 16:{struct instance_globals_saved_d*p=at;switch(field){
case 2:p->doors=(__typeof__(p->doors))value;return;
case 3:p->doors_alloc=(__typeof__(p->doors_alloc))value;return;
default:abort();}}
case 17:{struct instance_globals_saved_i*p=at;switch(field){
default:abort();}}
case 18:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 19:{struct instance_globals_saved_m*p=at;switch(field){
default:abort();}}
case 20:{struct instance_globals_saved_n*p=at;switch(field){
case 0:p->n_dgns=(__typeof__(p->n_dgns))value;return;
case 1:p->nroom=(__typeof__(p->nroom))value;return;
default:abort();}}
case 21:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_t*p=at;switch(field){
case 0:p->themeroom_failed=(__typeof__(p->themeroom_failed))value;return;
default:abort();}}
case 23:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_v*p=at;switch(field){
case 0:p->vault_x=(__typeof__(p->vault_x))value;return;
case 1:p->vault_y=(__typeof__(p->vault_y))value;return;
case 2:p->viz_array=(__typeof__(p->viz_array))value;return;
case 3:p->vision_full_recalc=(__typeof__(p->vision_full_recalc))value;return;
default:abort();}}
case 25:{struct instance_globals_x*p=at;switch(field){
case 0:p->x_maze_max=(__typeof__(p->x_maze_max))value;return;
case 1:p->xstart=(__typeof__(p->xstart))value;return;
default:abort();}}
case 26:{struct instance_globals_y*p=at;switch(field){
case 0:p->y_maze_max=(__typeof__(p->y_maze_max))value;return;
case 1:p->ystart=(__typeof__(p->ystart))value;return;
default:abort();}}
case 27:{struct levelflags*p=at;switch(field){
case 0:p->nfountains=(__typeof__(p->nfountains))value;return;
case 1:p->nsinks=(__typeof__(p->nsinks))value;return;
case 2:p->has_shop=(unsigned int)value;return;
case 3:p->has_vault=(unsigned int)value;return;
case 4:p->has_zoo=(unsigned int)value;return;
case 5:p->has_court=(unsigned int)value;return;
case 6:p->has_morgue=(unsigned int)value;return;
case 7:p->has_beehive=(unsigned int)value;return;
case 8:p->has_barracks=(unsigned int)value;return;
case 9:p->has_temple=(unsigned int)value;return;
case 10:p->has_swamp=(unsigned int)value;return;
case 11:p->noteleport=(unsigned int)value;return;
case 12:p->hardfloor=(unsigned int)value;return;
case 13:p->nommap=(unsigned int)value;return;
case 14:p->hero_memory=(unsigned int)value;return;
case 15:p->shortsighted=(unsigned int)value;return;
case 16:p->graveyard=(unsigned int)value;return;
case 17:p->sokoban_rules=(unsigned int)value;return;
case 18:p->is_maze_lev=(unsigned int)value;return;
case 19:p->is_cavernous_lev=(unsigned int)value;return;
case 20:p->arboreal=(unsigned int)value;return;
case 21:p->has_town=(unsigned int)value;return;
case 22:p->wizard_bones=(unsigned int)value;return;
case 23:p->corrmaze=(unsigned int)value;return;
case 24:p->rndmongen=(unsigned int)value;return;
case 25:p->deathdrops=(unsigned int)value;return;
case 26:p->noautosearch=(unsigned int)value;return;
case 27:p->fumaroles=(unsigned int)value;return;
case 28:p->stormy=(unsigned int)value;return;
case 29:p->temperature=(__typeof__(p->temperature))value;return;
case 30:p->stasis_until=(__typeof__(p->stasis_until))value;return;
default:abort();}}
case 28:{struct mkroom*p=at;switch(field){
case 0:p->lx=(__typeof__(p->lx))value;return;
case 1:p->hx=(__typeof__(p->hx))value;return;
case 2:p->ly=(__typeof__(p->ly))value;return;
case 3:p->hy=(__typeof__(p->hy))value;return;
case 4:p->rtype=(__typeof__(p->rtype))value;return;
case 5:p->orig_rtype=(__typeof__(p->orig_rtype))value;return;
case 6:p->rlit=(__typeof__(p->rlit))value;return;
case 7:p->needfill=(__typeof__(p->needfill))value;return;
case 8:p->needjoining=(__typeof__(p->needjoining))value;return;
case 9:p->doorct=(__typeof__(p->doorct))value;return;
case 10:p->fdoor=(__typeof__(p->fdoor))value;return;
case 11:p->nsubrooms=(__typeof__(p->nsubrooms))value;return;
case 12:p->irregular=(__typeof__(p->irregular))value;return;
case 13:p->roomnoidx=(__typeof__(p->roomnoidx))value;return;
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:p->data=(__typeof__(p->data))value;return;
case 1:p->m_ap_type=(__typeof__(p->m_ap_type))value;return;
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:p->mvflags=(__typeof__(p->mvflags))value;return;
default:abort();}}
case 31:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 32:{struct nhl_sandbox_info*p=at;switch(field){
case 0:p->flags=(__typeof__(p->flags))value;return;
case 1:p->memlimit=(__typeof__(p->memlimit))value;return;
case 2:p->steps=(__typeof__(p->steps))value;return;
case 3:p->perpcall=(__typeof__(p->perpcall))value;return;
default:abort();}}
case 33:{struct obj*p=at;switch(field){
case 0:p->ox=(__typeof__(p->ox))value;return;
case 1:p->oy=(__typeof__(p->oy))value;return;
case 2:p->otyp=(__typeof__(p->otyp))value;return;
case 3:p->owt=(__typeof__(p->owt))value;return;
case 4:p->quan=(__typeof__(p->quan))value;return;
case 5:p->cursed=(unsigned int)value;return;
case 6:p->olocked=(unsigned int)value;return;
case 7:p->otrapped=(unsigned int)value;return;
case 8:p->age=(__typeof__(p->age))value;return;
default:abort();}}
case 34:{struct objclass*p=at;switch(field){
case 0:p->oc_oc2=(__typeof__(p->oc_oc2))value;return;
default:abort();}}
case 35:{struct rm*p=at;switch(field){
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
case 36:{struct s_level*p=at;switch(field){
default:abort();}}
case 37:{struct stairway*p=at;switch(field){
case 0:p->u_traversed=(__typeof__(p->u_traversed))value;return;
default:abort();}}
case 38:{struct symdef*p=at;switch(field){
case 0:p->explanation=(__typeof__(p->explanation))value;return;
default:abort();}}
case 39:{struct trap*p=at;switch(field){
case 0:p->tx=(__typeof__(p->tx))value;return;
case 1:p->ty=(__typeof__(p->ty))value;return;
case 4:p->ttyp=(unsigned int)value;return;
case 5:p->tseen=(unsigned int)value;return;
case 6:p->once=(unsigned int)value;return;
default:abort();}}
case 40:{struct u_have*p=at;switch(field){
case 0:p->amulet=(unsigned int)value;return;
default:abort();}}
case 41:{struct window_procs*p=at;switch(field){
case 0:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 1:p->win_delay_output=(__typeof__(p->win_delay_output))value;return;
default:abort();}}
case 42:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 4:p->utrap=(__typeof__(p->utrap))value;return;
case 5:p->utraptype=(__typeof__(p->utraptype))value;return;
default:abort();}}
default:abort();}}
void* teleport_mklev_address(int kind,void*at,int field){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:return(void*)&p->filecode;
default:abort();}}
case 1:{struct branch*p=at;switch(field){
case 0:return(void*)&p->type;
case 1:return(void*)&p->end1;
case 2:return(void*)&p->end2;
case 3:return(void*)&p->end1_up;
default:abort();}}
case 2:{struct d_flags*p=at;switch(field){
default:abort();}}
case 3:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 4:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_oracle_level;
case 1:return(void*)&p->d_rogue_level;
case 2:return(void*)&p->d_medusa_level;
case 3:return(void*)&p->d_wiz1_level;
case 4:return(void*)&p->d_water_level;
case 5:return(void*)&p->d_astral_level;
case 6:return(void*)&p->d_mines_dnum;
case 7:return(void*)&p->d_tutorial_dnum;
case 8:return(void*)&p->d_knox_level;
default:abort();}}
case 5:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->objlist;
case 4:return(void*)&p->buriedobjlist;
case 5:return(void*)&p->monlist;
case 6:return(void*)&p->damagelist;
case 7:return(void*)&p->bonesinfo;
case 8:return(void*)&p->flags;
default:abort();}}
case 6:{struct dungeon*p=at;switch(field){
case 0:return(void*)&p->proto;
case 1:return(void*)&p->fill_lvl;
case 2:return(void*)&p->themerms;
default:abort();}}
case 7:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
default:abort();}}
case 8:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->in_lua;
case 1:return(void*)&p->debug_fuzzer;
case 2:return(void*)&p->last_msg;
case 3:return(void*)&p->sanity_check;
default:abort();}}
case 9:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->coder;
default:abort();}}
case 10:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->doorindex;
default:abort();}}
case 11:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_mklev;
case 1:return(void*)&p->in_mk_themerooms;
default:abort();}}
case 12:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->luathemes;
case 1:return(void*)&p->luacore;
case 2:return(void*)&p->lev_message;
default:abort();}}
case 13:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->made_branch;
default:abort();}}
case 14:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nsubroom;
default:abort();}}
case 15:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->stairs;
case 1:return(void*)&p->smeq;
case 2:return(void*)&p->subrooms;
default:abort();}}
case 16:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeons;
case 1:return(void*)&p->dungeon_topology;
case 2:return(void*)&p->doors;
case 3:return(void*)&p->doors_alloc;
default:abort();}}
case 17:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(void*)&p->inv_pos;
default:abort();}}
case 18:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 19:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->mvitals;
default:abort();}}
case 20:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(void*)&p->n_dgns;
case 1:return(void*)&p->nroom;
default:abort();}}
case 21:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(void*)&p->rooms;
default:abort();}}
case 22:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->themeroom_failed;
default:abort();}}
case 23:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
default:abort();}}
case 24:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->vault_x;
case 1:return(void*)&p->vault_y;
case 2:return(void*)&p->viz_array;
case 3:return(void*)&p->vision_full_recalc;
default:abort();}}
case 25:{struct instance_globals_x*p=at;switch(field){
case 0:return(void*)&p->x_maze_max;
case 1:return(void*)&p->xstart;
default:abort();}}
case 26:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->y_maze_max;
case 1:return(void*)&p->ystart;
default:abort();}}
case 27:{struct levelflags*p=at;switch(field){
case 0:return(void*)&p->nfountains;
case 1:return(void*)&p->nsinks;
case 29:return(void*)&p->temperature;
case 30:return(void*)&p->stasis_until;
default:abort();}}
case 28:{struct mkroom*p=at;switch(field){
case 0:return(void*)&p->lx;
case 1:return(void*)&p->hx;
case 2:return(void*)&p->ly;
case 3:return(void*)&p->hy;
case 4:return(void*)&p->rtype;
case 5:return(void*)&p->orig_rtype;
case 6:return(void*)&p->rlit;
case 7:return(void*)&p->needfill;
case 8:return(void*)&p->needjoining;
case 9:return(void*)&p->doorct;
case 10:return(void*)&p->fdoor;
case 11:return(void*)&p->nsubrooms;
case 12:return(void*)&p->irregular;
case 13:return(void*)&p->roomnoidx;
case 14:return(void*)&p->sbrooms;
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 1:return(void*)&p->m_ap_type;
default:abort();}}
case 30:{struct mvitals*p=at;switch(field){
case 0:return(void*)&p->mvflags;
default:abort();}}
case 31:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 32:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return(void*)&p->flags;
case 1:return(void*)&p->memlimit;
case 2:return(void*)&p->steps;
case 3:return(void*)&p->perpcall;
default:abort();}}
case 33:{struct obj*p=at;switch(field){
case 0:return(void*)&p->ox;
case 1:return(void*)&p->oy;
case 2:return(void*)&p->otyp;
case 3:return(void*)&p->owt;
case 4:return(void*)&p->quan;
case 8:return(void*)&p->age;
default:abort();}}
case 34:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_oc2;
default:abort();}}
case 35:{struct rm*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->typ;
case 2:return(void*)&p->seenv;
default:abort();}}
case 36:{struct s_level*p=at;switch(field){
case 0:return(void*)&p->dlevel;
case 1:return(void*)&p->proto;
case 2:return(void*)&p->flags;
default:abort();}}
case 37:{struct stairway*p=at;switch(field){
case 0:return(void*)&p->u_traversed;
default:abort();}}
case 38:{struct symdef*p=at;switch(field){
case 0:return(void*)&p->explanation;
default:abort();}}
case 39:{struct trap*p=at;switch(field){
case 0:return(void*)&p->tx;
case 1:return(void*)&p->ty;
case 2:return(void*)&p->dst;
case 3:return(void*)&p->launch;
default:abort();}}
case 40:{struct u_have*p=at;switch(field){
default:abort();}}
case 41:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_display_nhwindow;
case 1:return(void*)&p->win_delay_output;
default:abort();}}
case 42:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->uz;
case 3:return(void*)&p->ucamefrom;
case 4:return(void*)&p->utrap;
case 5:return(void*)&p->utraptype;
case 6:return(void*)&p->uhave;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_mklev_var0(char * a0){(impossible)(a0);}
void teleport_mklev_var1(char * a0){(panic)(a0);}
void teleport_mklev_var2(char * a0){(panic)(a0);}
void teleport_mklev_var3(char * a0){(panic)(a0);}
void teleport_mklev_var4(char * a0){(impossible)(a0);}
void teleport_mklev_var5(char * a0){(impossible)(a0);}
void teleport_mklev_var6(char * a0){(impossible)(a0);}
int teleport_mklev_var7(struct lua_State * a0,int a1){return (lua_gc)(a0,a1);}
void teleport_mklev_var8(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_mklev_var9(char * a0,int a1){(impossible)(a0,a1);}
void teleport_mklev_var10(char * a0){(impossible)(a0);}
int teleport_mklev_var11(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_mklev_var12(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_mklev_var13(char * a0){(pline)(a0);}
void teleport_mklev_var14(char * a0){(impossible)(a0);}
void teleport_mklev_var15(char * a0,int a1,char * a2,unsigned long a3,char * a4,int a5,unsigned int a6,char * a7,char * a8){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
void teleport_mklev_var16(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_mklev_var17(char * a0,char * a1,char * a2,int a3,int a4){(impossible)(a0,a1,a2,a3,a4);}
void teleport_mklev_var18(char * a0,int a1){(panic)(a0,a1);}
void teleport_mklev_var19(char * a0,int a1){(panic)(a0,a1);}
void teleport_mklev_var20(char * a0){(pline_The)(a0);}
void teleport_mklev_var21(char * a0){(pline_The)(a0);}
void teleport_mklev_var22(char * a0){(You)(a0);}
void teleport_mklev_var23(char * a0,int a1){(impossible)(a0,a1);}
void teleport_mklev_var24(char * a0){(pline)(a0);}
void teleport_mklev_indirect0(void (*fn)(winid, boolean),int a0,signed char a1){fn(a0,a1);}
void teleport_mklev_indirect1(void (*fn)(void)){fn();}
void teleport_mklev_dynamic0_panic(char * a0,int a1,int a2,int a3){(panic)(a0,a1,a2,a3);}
void teleport_mklev_dynamic0_impossible(char * a0,int a1,int a2,int a3){(impossible)(a0,a1,a2,a3);}
extern int teleport_mklev_mkroom_cmp(const void*,const void*);
int(*teleport_mklev_owned_pointer(int i))(const void*,const void*){(void)i;return teleport_mklev_mkroom_cmp;}
int(*teleport_mklev_native_pointer(int i))(int){switch(i){case 0:return(rn2);case 1:return(rn2_on_display_rng);default:abort();}}
#pragma clang diagnostic pop
void teleport_mklev_free(void*p){(free)(p);}
static char mklev_literals[1405];
char*teleport_mklev_literal_storage(void){return mklev_literals;}
size_t teleport_mklev_literal_capacity(void){return sizeof mklev_literals;}
static char * mklev_backing_0[26];
static struct rm mklev_backing_1;
static int mklev_backing_2[9];
static int mklev_backing_3[10];
static int mklev_backing_4;
static char mklev_backing_5[45];
void*teleport_mklev_storage(int i){switch(i){
case 0:return &mklev_backing_0;
case 1:return &mklev_backing_1;
case 2:return &mklev_backing_2;
case 3:return &mklev_backing_3;
case 4:return &mklev_backing_4;
case 5:return &mklev_backing_5;
default:abort();}}
