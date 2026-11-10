/* DOTHROW ABI/header/native dependency transport and zero backing only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(size_t)==8,"DOTHROW memory64 LP64 ABI");
_Static_assert(sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"DOTHROW signed native scalar ABI");
void*teleport_dothrow_global(int index){switch(index){
case 0:return(void*)&objects;
case 1:return(void*)&svc;
case 2:return(void*)&uquiver;
case 3:return(void*)&uwep;
case 4:return(void*)&gy;
case 5:return(void*)&u;
case 6:return(void*)&uarmg;
case 7:return(void*)&mons;
case 8:return(void*)&svk;
case 9:return(void*)&gu;
case 10:return(void*)&gm;
case 11:return(void*)&gc;
case 12:return(void*)&uswapwep;
case 13:return(void*)&gi;
case 14:return(void*)&flags;
case 15:return(void*)&iflags;
case 16:return(void*)&svl;
case 17:return(void*)&genders;
case 18:return(void*)&uarmu;
case 19:return(void*)&uarm;
case 20:return(void*)&uarmc;
case 21:return(void*)&uball;
case 22:return(void*)&svd;
case 23:return(void*)&windowprocs;
case 24:return(void*)&gn;
case 25:return(void*)&gt;
case 26:return(void*)&uarmh;
case 27:return(void*)&c_common_strings;
case 28:return(void*)&gb;
case 29:return(void*)&go;
case 30:return(void*)&uchain;
case 31:return(void*)&gv;
case 32:return(void*)&gk;
case 33:return(void*)&svq;
case 34:return(void*)&ublindf;
case 35:return(void*)&gh;
default:abort();}}
uint64_t teleport_dothrow_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(dlevel_t));
case 6:return(uint64_t)(sizeof(struct Gender));
case 7:return(uint64_t)(sizeof(struct Race));
case 8:return(uint64_t)(sizeof(struct Role));
case 9:return(uint64_t)(sizeof(struct align));
case 10:return(uint64_t)(sizeof(struct c_common_strings));
case 11:return(uint64_t)(sizeof(struct context_info));
case 12:return(uint64_t)(sizeof(struct d_level));
case 13:return(uint64_t)(sizeof(struct dgn_topology));
case 14:return(uint64_t)(sizeof(struct eshk));
case 15:return(uint64_t)(sizeof(struct flag));
case 16:return(uint64_t)(sizeof(struct instance_flags));
case 17:return(uint64_t)(sizeof(struct instance_globals_b));
case 18:return(uint64_t)(sizeof(struct instance_globals_c));
case 19:return(uint64_t)(sizeof(struct instance_globals_h));
case 20:return(uint64_t)(sizeof(struct instance_globals_i));
case 21:return(uint64_t)(sizeof(struct instance_globals_k));
case 22:return(uint64_t)(sizeof(struct instance_globals_m));
case 23:return(uint64_t)(sizeof(struct instance_globals_n));
case 24:return(uint64_t)(sizeof(struct instance_globals_o));
case 25:return(uint64_t)(sizeof(struct instance_globals_saved_c));
case 26:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 27:return(uint64_t)(sizeof(struct instance_globals_saved_k));
case 28:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 29:return(uint64_t)(sizeof(struct instance_globals_saved_q));
case 30:return(uint64_t)(sizeof(struct instance_globals_t));
case 31:return(uint64_t)(sizeof(struct instance_globals_u));
case 32:return(uint64_t)(sizeof(struct instance_globals_v));
case 33:return(uint64_t)(sizeof(struct instance_globals_y));
case 34:return(uint64_t)(sizeof(struct kinfo));
case 35:return(uint64_t)(sizeof(struct levelflags));
case 36:return(uint64_t)(sizeof(struct mextra));
case 37:return(uint64_t)(sizeof(struct monst));
case 38:return(uint64_t)(sizeof(struct multishot));
case 39:return(uint64_t)(sizeof(struct nhcoord));
case 40:return(uint64_t)(sizeof(struct obj));
case 41:return(uint64_t)(sizeof(struct obj_split));
case 42:return(uint64_t)(sizeof(struct objclass));
case 43:return(uint64_t)(sizeof(struct oextra));
case 44:return(uint64_t)(sizeof(struct permonst));
case 45:return(uint64_t)(sizeof(struct prop));
case 46:return(uint64_t)(sizeof(struct q_score));
case 47:return(uint64_t)(sizeof(struct rm));
case 48:return(uint64_t)(sizeof(struct skills));
case 49:return(uint64_t)(sizeof(struct throw_and_return_weapon));
case 50:return(uint64_t)(sizeof(struct trap));
case 51:return(uint64_t)(sizeof(struct u_conduct));
case 52:return(uint64_t)(sizeof(struct u_event));
case 53:return(uint64_t)(sizeof(struct u_roleplay));
case 54:return(uint64_t)(sizeof(struct window_procs));
case 55:return(uint64_t)(sizeof(struct you));
case 56:return(uint64_t)(sizeof(union vptrs));
case 57:return(uint64_t)(ACCFOOD);
case 58:return(uint64_t)(ACID_VENOM);
case 59:return(uint64_t)(AIR);
case 60:return(uint64_t)(AKLYS);
case 61:return(uint64_t)(ALTAR);
case 62:return(uint64_t)(AMULET_OF_YENDOR);
case 63:return(uint64_t)(ARM);
case 64:return(uint64_t)(ARMOR_CLASS);
case 65:return(uint64_t)(ART_MJOLLNIR);
case 66:return(uint64_t)(ART_SNICKERSNEE);
case 67:return(uint64_t)(A_CON);
case 68:return(uint64_t)(A_DEX);
case 69:return(uint64_t)(A_STR);
case 70:return(uint64_t)(BAG_OF_HOLDING);
case 71:return(uint64_t)(BAG_OF_TRICKS);
case 72:return(uint64_t)(BANANA);
case 73:return(uint64_t)(BLINDED);
case 74:return(uint64_t)(BLINDING_VENOM);
case 75:return(uint64_t)(BOOMERANG);
case 76:return(uint64_t)(BOULDER);
case 77:return(uint64_t)(BULLWHIP);
case 78:return(uint64_t)(CLOTH);
case 79:return(uint64_t)(CLOUD);
case 80:return(uint64_t)(COIN_CLASS);
case 81:return(uint64_t)(CONFUSION);
case 82:return(uint64_t)(CORPSE);
case 83:return(uint64_t)(CQ_CANNED);
case 84:return(uint64_t)(CREAM_PIE);
case 85:return(uint64_t)(CRYSTAL_BALL);
case 86:return(uint64_t)(DEAF);
case 87:return(uint64_t)(DOOR);
case 88:return(uint64_t)(DRAWBRIDGE_UP);
case 89:return(uint64_t)(EGG);
case 90:return(uint64_t)(ELVEN_ARROW);
case 91:return(uint64_t)(ELVEN_BOW);
case 92:return(uint64_t)(EUCALYPTUS_LEAF);
case 93:return(uint64_t)(EXPENSIVE_CAMERA);
case 94:return(uint64_t)(EXPL_FIERY);
case 95:return(uint64_t)(EYE);
case 96:return(uint64_t)(FACE);
case 97:return(uint64_t)(FAKE_AMULET_OF_YENDOR);
case 98:return(uint64_t)(FIRE_TRAP);
case 99:return(uint64_t)(FIRST_OBJECT);
case 100:return(uint64_t)(FIRST_REAL_GEM);
case 101:return(uint64_t)(FIRST_SPELL);
case 102:return(uint64_t)(FLINT);
case 103:return(uint64_t)(FLYING);
case 104:return(uint64_t)(FOOD_CLASS);
case 105:return(uint64_t)(FOOT);
case 106:return(uint64_t)(FORTUNE_COOKIE);
case 107:return(uint64_t)(FUMBLING);
case 108:return(uint64_t)(GAUNTLETS_OF_DEXTERITY);
case 109:return(uint64_t)(GAUNTLETS_OF_FUMBLING);
case 110:return(uint64_t)(GAUNTLETS_OF_POWER);
case 111:return(uint64_t)(GEMSTONE);
case 112:return(uint64_t)(GEM_CLASS);
case 113:return(uint64_t)(GETOBJ_DOWNPLAY);
case 114:return(uint64_t)(GETOBJ_EXCLUDE);
case 115:return(uint64_t)(GETOBJ_SUGGEST);
case 116:return(uint64_t)(GLASS);
case 117:return(uint64_t)(GLYPH_BODY_OFF);
case 118:return(uint64_t)(GLYPH_BODY_PILETOP_OFF);
case 119:return(uint64_t)(GLYPH_DETECT_FEM_OFF);
case 120:return(uint64_t)(GLYPH_DETECT_MALE_OFF);
case 121:return(uint64_t)(GLYPH_INVIS_OFF);
case 122:return(uint64_t)(GLYPH_MON_FEM_OFF);
case 123:return(uint64_t)(GLYPH_MON_MALE_OFF);
case 124:return(uint64_t)(GLYPH_OBJ_OFF);
case 125:return(uint64_t)(GLYPH_OBJ_PILETOP_OFF);
case 126:return(uint64_t)(GLYPH_PET_FEM_OFF);
case 127:return(uint64_t)(GLYPH_PET_MALE_OFF);
case 128:return(uint64_t)(GLYPH_RIDDEN_FEM_OFF);
case 129:return(uint64_t)(GLYPH_RIDDEN_MALE_OFF);
case 130:return(uint64_t)(GLYPH_STATUE_FEM_OFF);
case 131:return(uint64_t)(GLYPH_STATUE_FEM_PILETOP_OFF);
case 132:return(uint64_t)(GLYPH_STATUE_MALE_OFF);
case 133:return(uint64_t)(GLYPH_STATUE_MALE_PILETOP_OFF);
case 134:return(uint64_t)(HALF_PHDAM);
case 135:return(uint64_t)(HALLUC);
case 136:return(uint64_t)(HALLUC_RES);
case 137:return(uint64_t)(HAND);
case 138:return(uint64_t)(HEAD);
case 139:return(uint64_t)(HEAVY_IRON_BALL);
case 140:return(uint64_t)(HMON_APPLIED);
case 141:return(uint64_t)(HMON_KICKED);
case 142:return(uint64_t)(HMON_THROWN);
case 143:return(uint64_t)(HOLE);
case 144:return(uint64_t)(IRONBARS);
case 145:return(uint64_t)(KELP_FROND);
case 146:return(uint64_t)(LAST_GLASS_GEM);
case 147:return(uint64_t)(LAST_SPELL);
case 148:return(uint64_t)(LEATHER_GLOVES);
case 149:return(uint64_t)(LENSES);
case 150:return(uint64_t)(LEVITATION);
case 151:return(uint64_t)(LOW_PM);
case 152:return(uint64_t)(MAGIC_PORTAL);
case 153:return(uint64_t)(MELON);
case 154:return(uint64_t)(MINERAL);
case 155:return(uint64_t)(MIRROR);
case 156:return(uint64_t)(M_AP_MONSTER);
case 157:return(uint64_t)(NEUTRAL);
case 158:return(uint64_t)(NUMMONS);
case 159:return(uint64_t)(NUM_OBJECTS);
case 160:return(uint64_t)(OILSKIN_SACK);
case 161:return(uint64_t)(ORCISH_ARROW);
case 162:return(uint64_t)(ORCISH_BOW);
case 163:return(uint64_t)(PANCAKE);
case 164:return(uint64_t)(PASSES_WALLS);
case 165:return(uint64_t)(PIT);
case 166:return(uint64_t)(PM_AIR_ELEMENTAL);
case 167:return(uint64_t)(PM_APE);
case 168:return(uint64_t)(PM_CAVE_DWELLER);
case 169:return(uint64_t)(PM_CHICKATRICE);
case 170:return(uint64_t)(PM_CLERIC);
case 171:return(uint64_t)(PM_COCKATRICE);
case 172:return(uint64_t)(PM_CYCLOPS);
case 173:return(uint64_t)(PM_DWARF);
case 174:return(uint64_t)(PM_ELF);
case 175:return(uint64_t)(PM_FLOATING_EYE);
case 176:return(uint64_t)(PM_GNOME);
case 177:return(uint64_t)(PM_GRID_BUG);
case 178:return(uint64_t)(PM_HEALER);
case 179:return(uint64_t)(PM_HOMUNCULUS);
case 180:return(uint64_t)(PM_HUMAN);
case 181:return(uint64_t)(PM_IMP);
case 182:return(uint64_t)(PM_LICHEN);
case 183:return(uint64_t)(PM_MONK);
case 184:return(uint64_t)(PM_MONKEY);
case 185:return(uint64_t)(PM_NINJA);
case 186:return(uint64_t)(PM_ORC);
case 187:return(uint64_t)(PM_PYROLISK);
case 188:return(uint64_t)(PM_RANGER);
case 189:return(uint64_t)(PM_ROGUE);
case 190:return(uint64_t)(PM_SAMURAI);
case 191:return(uint64_t)(PM_SHADE);
case 192:return(uint64_t)(PM_STONE_GOLEM);
case 193:return(uint64_t)(PM_TOURIST);
case 194:return(uint64_t)(PM_VALKYRIE);
case 195:return(uint64_t)(PM_WIZARD);
case 196:return(uint64_t)(POOL);
case 197:return(uint64_t)(POTION_CLASS);
case 198:return(uint64_t)(POT_OIL);
case 199:return(uint64_t)(POT_WATER);
case 200:return(uint64_t)(P_AXE);
case 201:return(uint64_t)(P_BOOMERANG);
case 202:return(uint64_t)(P_BOW);
case 203:return(uint64_t)(P_CROSSBOW);
case 204:return(uint64_t)(P_DAGGER);
case 205:return(uint64_t)(P_DART);
case 206:return(uint64_t)(P_EXPERT);
case 207:return(uint64_t)(P_KNIFE);
case 208:return(uint64_t)(P_LANCE);
case 209:return(uint64_t)(P_NONE);
case 210:return(uint64_t)(P_PICK_AXE);
case 211:return(uint64_t)(P_POLEARMS);
case 212:return(uint64_t)(P_SABER);
case 213:return(uint64_t)(P_SHORT_SWORD);
case 214:return(uint64_t)(P_SHURIKEN);
case 215:return(uint64_t)(P_SKILLED);
case 216:return(uint64_t)(P_SLING);
case 217:return(uint64_t)(P_SPEAR);
case 218:return(uint64_t)(RING_CLASS);
case 219:return(uint64_t)(ROCK);
case 220:return(uint64_t)(RUBBER_HOSE);
case 221:return(uint64_t)(SACK);
case 222:return(uint64_t)(SCROLL_CLASS);
case 223:return(uint64_t)(SHOPBASE);
case 224:return(uint64_t)(SILVER);
case 225:return(uint64_t)(SLING);
case 226:return(uint64_t)(SLT_ENCUMBER);
case 227:return(uint64_t)(SPIKED_PIT);
case 228:return(uint64_t)(SPRIG_OF_WOLFSBANE);
case 229:return(uint64_t)(STATUE);
case 230:return(uint64_t)(STONE);
case 231:return(uint64_t)(STONE_RES);
case 232:return(uint64_t)(STONING);
case 233:return(uint64_t)(STRANGE_OBJECT);
case 234:return(uint64_t)(STUNNED);
case 235:return(uint64_t)(S_UNICORN);
case 236:return(uint64_t)(S_VORTEX);
case 237:return(uint64_t)(THROWN_TETHERED_WEAPON);
case 238:return(uint64_t)(THROWN_WEAPON);
case 239:return(uint64_t)(TOOL_CLASS);
case 240:return(uint64_t)(TOWEL);
case 241:return(uint64_t)(TRAPDOOR);
case 242:return(uint64_t)(TREE);
case 243:return(uint64_t)(TT_BURIEDBALL);
case 244:return(uint64_t)(TT_INFLOOR);
case 245:return(uint64_t)(TT_LAVA);
case 246:return(uint64_t)(TT_WEB);
case 247:return(uint64_t)(Trap_Caught_Mon);
case 248:return(uint64_t)(Trap_Killed_Mon);
case 249:return(uint64_t)(Trap_Moved_Mon);
case 250:return(uint64_t)(VEGGY);
case 251:return(uint64_t)(VENOM_CLASS);
case 252:return(uint64_t)(VIBRATING_SQUARE);
case 253:return(uint64_t)(WAND_CLASS);
case 254:return(uint64_t)(WAN_STRIKING);
case 255:return(uint64_t)(WAR_HAMMER);
case 256:return(uint64_t)(WEAPON_CLASS);
case 257:return(uint64_t)(WT_SPLASH_THRESHOLD);
case 258:return(uint64_t)(WT_TOOMUCH_DIAGONAL);
case 259:return(uint64_t)(WT_TO_DMG);
case 260:return(uint64_t)(WWALKING);
case 261:return(uint64_t)(YA);
case 262:return(uint64_t)(YUMI);
default:abort();}}
uint64_t teleport_dothrow_read(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->him);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
case 1:return(uint64_t)(uintptr_t)(p->selfmask);
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_something);
case 1:return(uint64_t)(uintptr_t)(p->c_Something);
case 2:return(uint64_t)(uintptr_t)(p->c_vision_clears);
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mon_moving);
case 1:return(uint64_t)(uintptr_t)(&p->objsplit);
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_air_level);
default:abort();}}
case 8:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 9:{struct eshk*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->break_seq);
case 1:return(uint64_t)(uintptr_t)(p->seq_peaceful);
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->autoquiver);
case 1:return(uint64_t)(uintptr_t)(p->pushweapon);
case 2:return(uint64_t)(uintptr_t)(p->verbose);
default:abort();}}
case 11:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->fireassist);
case 1:return(uint64_t)(uintptr_t)(p->returning_missile);
default:abort();}}
case 12:{struct instance_globals_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bhitpos);
default:abort();}}
case 13:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->command_count);
default:abort();}}
case 14:{struct instance_globals_h*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hero_seq);
default:abort();}}
case 15:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_doagain);
case 1:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 16:{struct instance_globals_k*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->kickedobj);
default:abort();}}
case 17:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->multi);
case 1:return(uint64_t)(uintptr_t)(p->multi_reason);
case 2:return(uint64_t)(uintptr_t)(&p->m_shot);
default:abort();}}
case 18:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nomovemsg);
case 1:return(uint64_t)(uintptr_t)(p->notonhead);
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->otg_temp);
case 1:return(uint64_t)(uintptr_t)(p->otg_otmp);
default:abort();}}
case 20:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 21:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 22:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 24:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->quest_status);
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->thrownobj);
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
case 1:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 27:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->viz_array);
case 1:return(uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 28:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 29:{struct kinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->format);
case 1:return(uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 30:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sokoban_rules);
case 1:return(uint64_t)(uintptr_t)(p->arboreal);
default:abort();}}
case 31:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mgivenname);
case 1:return(uint64_t)(uintptr_t)(p->eshk);
default:abort();}}
case 32:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->m_id);
case 2:return(uint64_t)(uintptr_t)(p->movement);
case 3:return(uint64_t)(uintptr_t)(p->mx);
case 4:return(uint64_t)(uintptr_t)(p->my);
case 5:return(uint64_t)(uintptr_t)(p->mhp);
case 6:return(uint64_t)(uintptr_t)(p->m_ap_type);
case 7:return(uint64_t)(uintptr_t)(p->mtame);
case 8:return(uint64_t)(uintptr_t)(p->mundetected);
case 9:return(uint64_t)(uintptr_t)(p->mavenge);
case 10:return(uint64_t)(uintptr_t)(p->msleeping);
case 11:return(uint64_t)(uintptr_t)(p->mstun);
case 12:return(uint64_t)(uintptr_t)(p->mfrozen);
case 13:return(uint64_t)(uintptr_t)(p->mcanmove);
case 14:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 15:return(uint64_t)(uintptr_t)(p->mtrapped);
case 16:return(uint64_t)(uintptr_t)(p->isshk);
case 17:return(uint64_t)(uintptr_t)(p->wormno);
case 18:return(uint64_t)(uintptr_t)(p->mstrategy);
case 19:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 33:{struct multishot*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->n);
case 1:return(uint64_t)(uintptr_t)(p->i);
case 2:return(uint64_t)(uintptr_t)(p->o);
case 3:return(uint64_t)(uintptr_t)(p->s);
default:abort();}}
case 34:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 35:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(&p->v);
case 2:return(uint64_t)(uintptr_t)(p->cobj);
case 3:return(uint64_t)(uintptr_t)(p->o_id);
case 4:return(uint64_t)(uintptr_t)(p->ox);
case 5:return(uint64_t)(uintptr_t)(p->oy);
case 6:return(uint64_t)(uintptr_t)(p->otyp);
case 7:return(uint64_t)(uintptr_t)(p->owt);
case 8:return(uint64_t)(uintptr_t)(p->quan);
case 9:return(uint64_t)(uintptr_t)(p->spe);
case 10:return(uint64_t)(uintptr_t)(p->oclass);
case 11:return(uint64_t)(uintptr_t)(p->invlet);
case 12:return(uint64_t)(uintptr_t)(p->oartifact);
case 13:return(uint64_t)(uintptr_t)(p->where);
case 14:return(uint64_t)(uintptr_t)(p->cursed);
case 15:return(uint64_t)(uintptr_t)(p->blessed);
case 16:return(uint64_t)(uintptr_t)(p->unpaid);
case 17:return(uint64_t)(uintptr_t)(p->no_charge);
case 18:return(uint64_t)(uintptr_t)(p->lamplit);
case 19:return(uint64_t)(uintptr_t)(p->known);
case 20:return(uint64_t)(uintptr_t)(p->dknown);
case 21:return(uint64_t)(uintptr_t)(p->bknown);
case 22:return(uint64_t)(uintptr_t)(p->nomerge);
case 23:return(uint64_t)(uintptr_t)(p->oeroded);
case 24:return(uint64_t)(uintptr_t)(p->oeroded2);
case 25:return(uint64_t)(uintptr_t)(p->greased);
case 26:return(uint64_t)(uintptr_t)(p->in_use);
case 27:return(uint64_t)(uintptr_t)(p->how_lost);
case 28:return(uint64_t)(uintptr_t)(p->corpsenm);
case 29:return(uint64_t)(uintptr_t)(p->owornmask);
case 30:return(uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 36:{struct obj_split*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->parent_oid);
case 1:return(uint64_t)(uintptr_t)(p->child_oid);
default:abort();}}
case 37:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_uname);
case 1:return(uint64_t)(uintptr_t)(p->oc_name_known);
case 2:return(uint64_t)(uintptr_t)(p->oc_magic);
case 3:return(uint64_t)(uintptr_t)(p->oc_unique);
case 4:return(uint64_t)(uintptr_t)(p->oc_tough);
case 5:return(uint64_t)(uintptr_t)(p->oc_dir);
case 6:return(uint64_t)(uintptr_t)(p->oc_material);
case 7:return(uint64_t)(uintptr_t)(p->oc_subtyp);
default:abort();}}
case 38:{struct oextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oname);
default:abort();}}
case 39:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->pmidx);
case 1:return(uint64_t)(uintptr_t)(p->mlet);
case 2:return(uint64_t)(uintptr_t)(p->mlevel);
case 3:return(uint64_t)(uintptr_t)(p->mmove);
case 4:return(uint64_t)(uintptr_t)(p->maligntyp);
case 5:return(uint64_t)(uintptr_t)(p->msize);
case 6:return(uint64_t)(uintptr_t)(p->mflags1);
case 7:return(uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 40:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 41:{struct q_score*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->leader_m_id);
default:abort();}}
case 42:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 43:{struct skills*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->skill);
default:abort();}}
case 44:{struct throw_and_return_weapon*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->range);
case 1:return(uint64_t)(uintptr_t)(p->tethered);
default:abort();}}
case 45:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ttyp);
case 1:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 46:{struct u_conduct*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->weaphit);
default:abort();}}
case 47:{struct u_event*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->invoked);
default:abort();}}
case 48:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 49:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
case 1:return(uint64_t)(uintptr_t)(p->v_ocarry);
default:abort();}}
case 50:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_delay_output);
default:abort();}}
case 51:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(p->dx);
case 3:return(uint64_t)(uintptr_t)(p->dy);
case 4:return(uint64_t)(uintptr_t)(p->dz);
case 5:return(uint64_t)(uintptr_t)(p->ux0);
case 6:return(uint64_t)(uintptr_t)(p->uy0);
case 7:return(uint64_t)(uintptr_t)(&p->uz);
case 8:return(uint64_t)(uintptr_t)(p->ulevel);
case 9:return(uint64_t)(uintptr_t)(p->utrap);
case 10:return(uint64_t)(uintptr_t)(p->utraptype);
case 11:return(uint64_t)(uintptr_t)(&p->ushops);
case 12:return(uint64_t)(uintptr_t)(&p->ushops0);
case 13:return(uint64_t)(uintptr_t)(&p->uprops);
case 14:return(uint64_t)(uintptr_t)(p->umonster);
case 15:return(uint64_t)(uintptr_t)(p->umonnum);
case 16:return(uint64_t)(uintptr_t)(p->mh);
case 17:return(uint64_t)(uintptr_t)(p->mhmax);
case 18:return(uint64_t)(uintptr_t)(p->ulycn);
case 19:return(uint64_t)(uintptr_t)(p->ucreamed);
case 20:return(uint64_t)(uintptr_t)(p->uswallow);
case 21:return(uint64_t)(uintptr_t)(p->uinwater);
case 22:return(uint64_t)(uintptr_t)(&p->uevent);
case 23:return(uint64_t)(uintptr_t)(&p->uconduct);
case 24:return(uint64_t)(uintptr_t)(&p->uroleplay);
case 25:return(uint64_t)(uintptr_t)(&p->ualign);
case 26:return(uint64_t)(uintptr_t)(&p->ualignbase);
case 27:return(uint64_t)(uintptr_t)(p->uluck);
case 28:return(uint64_t)(uintptr_t)(p->moreluck);
case 29:return(uint64_t)(uintptr_t)(p->uhitinc);
case 30:return(uint64_t)(uintptr_t)(p->udaminc);
case 31:return(uint64_t)(uintptr_t)(p->uhp);
case 32:return(uint64_t)(uintptr_t)(p->uhpmax);
case 33:return(uint64_t)(uintptr_t)(p->ustuck);
case 34:return(uint64_t)(uintptr_t)(p->usteed);
case 35:return(uint64_t)(uintptr_t)(&p->weapon_skills);
case 36:return(uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
default:abort();}}
void teleport_dothrow_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:p->him=(__typeof__(p->him))value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
case 1:p->selfmask=(__typeof__(p->selfmask))value;return;
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:p->type=(__typeof__(p->type))value;return;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:p->mon_moving=(__typeof__(p->mon_moving))value;return;
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
default:abort();}}
case 8:{dlevel_t*p=at;switch(field){
default:abort();}}
case 9:{struct eshk*p=at;switch(field){
case 0:p->break_seq=(__typeof__(p->break_seq))value;return;
case 1:p->seq_peaceful=(__typeof__(p->seq_peaceful))value;return;
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:p->autoquiver=(__typeof__(p->autoquiver))value;return;
case 1:p->pushweapon=(__typeof__(p->pushweapon))value;return;
case 2:p->verbose=(__typeof__(p->verbose))value;return;
default:abort();}}
case 11:{struct instance_flags*p=at;switch(field){
case 0:p->fireassist=(__typeof__(p->fireassist))value;return;
case 1:p->returning_missile=(__typeof__(p->returning_missile))value;return;
default:abort();}}
case 12:{struct instance_globals_b*p=at;switch(field){
default:abort();}}
case 13:{struct instance_globals_c*p=at;switch(field){
case 0:p->command_count=(__typeof__(p->command_count))value;return;
default:abort();}}
case 14:{struct instance_globals_h*p=at;switch(field){
case 0:p->hero_seq=(__typeof__(p->hero_seq))value;return;
default:abort();}}
case 15:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_doagain=(__typeof__(p->in_doagain))value;return;
case 1:p->invent=(__typeof__(p->invent))value;return;
default:abort();}}
case 16:{struct instance_globals_k*p=at;switch(field){
case 0:p->kickedobj=(__typeof__(p->kickedobj))value;return;
default:abort();}}
case 17:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=(__typeof__(p->multi))value;return;
case 1:p->multi_reason=(__typeof__(p->multi_reason))value;return;
default:abort();}}
case 18:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(__typeof__(p->nomovemsg))value;return;
case 1:p->notonhead=(__typeof__(p->notonhead))value;return;
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:p->otg_temp=(__typeof__(p->otg_temp))value;return;
case 1:p->otg_otmp=(__typeof__(p->otg_otmp))value;return;
default:abort();}}
case 20:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 21:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_saved_k*p=at;switch(field){
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_saved_q*p=at;switch(field){
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:p->thrownobj=(__typeof__(p->thrownobj))value;return;
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(__typeof__(p->viz_array))value;return;
case 1:p->vision_full_recalc=(__typeof__(p->vision_full_recalc))value;return;
default:abort();}}
case 28:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 29:{struct kinfo*p=at;switch(field){
case 0:p->format=(__typeof__(p->format))value;return;
default:abort();}}
case 30:{struct levelflags*p=at;switch(field){
case 0:p->sokoban_rules=(unsigned int)value;return;
case 1:p->arboreal=(unsigned int)value;return;
default:abort();}}
case 31:{struct mextra*p=at;switch(field){
case 0:p->mgivenname=(__typeof__(p->mgivenname))value;return;
case 1:p->eshk=(__typeof__(p->eshk))value;return;
default:abort();}}
case 32:{struct monst*p=at;switch(field){
case 0:p->data=(__typeof__(p->data))value;return;
case 1:p->m_id=(__typeof__(p->m_id))value;return;
case 2:p->movement=(__typeof__(p->movement))value;return;
case 3:p->mx=(__typeof__(p->mx))value;return;
case 4:p->my=(__typeof__(p->my))value;return;
case 5:p->mhp=(__typeof__(p->mhp))value;return;
case 6:p->m_ap_type=(__typeof__(p->m_ap_type))value;return;
case 7:p->mtame=(__typeof__(p->mtame))value;return;
case 8:p->mundetected=(unsigned int)value;return;
case 9:p->mavenge=(unsigned int)value;return;
case 10:p->msleeping=(unsigned int)value;return;
case 11:p->mstun=(unsigned int)value;return;
case 12:p->mfrozen=(unsigned int)value;return;
case 13:p->mcanmove=(unsigned int)value;return;
case 14:p->mpeaceful=(unsigned int)value;return;
case 15:p->mtrapped=(unsigned int)value;return;
case 16:p->isshk=(unsigned int)value;return;
case 17:p->wormno=(unsigned int)value;return;
case 18:p->mstrategy=(__typeof__(p->mstrategy))value;return;
case 19:p->mextra=(__typeof__(p->mextra))value;return;
default:abort();}}
case 33:{struct multishot*p=at;switch(field){
case 0:p->n=(__typeof__(p->n))value;return;
case 1:p->i=(__typeof__(p->i))value;return;
case 2:p->o=(__typeof__(p->o))value;return;
case 3:p->s=(__typeof__(p->s))value;return;
default:abort();}}
case 34:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 35:{struct obj*p=at;switch(field){
case 0:p->nobj=(__typeof__(p->nobj))value;return;
case 2:p->cobj=(__typeof__(p->cobj))value;return;
case 3:p->o_id=(__typeof__(p->o_id))value;return;
case 4:p->ox=(__typeof__(p->ox))value;return;
case 5:p->oy=(__typeof__(p->oy))value;return;
case 6:p->otyp=(__typeof__(p->otyp))value;return;
case 7:p->owt=(__typeof__(p->owt))value;return;
case 8:p->quan=(__typeof__(p->quan))value;return;
case 9:p->spe=(__typeof__(p->spe))value;return;
case 10:p->oclass=(__typeof__(p->oclass))value;return;
case 11:p->invlet=(__typeof__(p->invlet))value;return;
case 12:p->oartifact=(__typeof__(p->oartifact))value;return;
case 13:p->where=(__typeof__(p->where))value;return;
case 14:p->cursed=(unsigned int)value;return;
case 15:p->blessed=(unsigned int)value;return;
case 16:p->unpaid=(unsigned int)value;return;
case 17:p->no_charge=(unsigned int)value;return;
case 18:p->lamplit=(unsigned int)value;return;
case 19:p->known=(unsigned int)value;return;
case 20:p->dknown=(unsigned int)value;return;
case 21:p->bknown=(unsigned int)value;return;
case 22:p->nomerge=(unsigned int)value;return;
case 23:p->oeroded=(unsigned int)value;return;
case 24:p->oeroded2=(unsigned int)value;return;
case 25:p->greased=(unsigned int)value;return;
case 26:p->in_use=(unsigned int)value;return;
case 27:p->how_lost=(unsigned int)value;return;
case 28:p->corpsenm=(__typeof__(p->corpsenm))value;return;
case 29:p->owornmask=(__typeof__(p->owornmask))value;return;
case 30:p->oextra=(__typeof__(p->oextra))value;return;
default:abort();}}
case 36:{struct obj_split*p=at;switch(field){
case 0:p->parent_oid=(__typeof__(p->parent_oid))value;return;
case 1:p->child_oid=(__typeof__(p->child_oid))value;return;
default:abort();}}
case 37:{struct objclass*p=at;switch(field){
case 0:p->oc_uname=(__typeof__(p->oc_uname))value;return;
case 1:p->oc_name_known=(unsigned int)value;return;
case 2:p->oc_magic=(unsigned int)value;return;
case 3:p->oc_unique=(unsigned int)value;return;
case 4:p->oc_tough=(unsigned int)value;return;
case 5:p->oc_dir=(unsigned int)value;return;
case 6:p->oc_material=(unsigned int)value;return;
case 7:p->oc_subtyp=(__typeof__(p->oc_subtyp))value;return;
default:abort();}}
case 38:{struct oextra*p=at;switch(field){
case 0:p->oname=(__typeof__(p->oname))value;return;
default:abort();}}
case 39:{struct permonst*p=at;switch(field){
case 1:p->mlet=(__typeof__(p->mlet))value;return;
case 2:p->mlevel=(__typeof__(p->mlevel))value;return;
case 3:p->mmove=(__typeof__(p->mmove))value;return;
case 4:p->maligntyp=(__typeof__(p->maligntyp))value;return;
case 5:p->msize=(__typeof__(p->msize))value;return;
case 6:p->mflags1=(__typeof__(p->mflags1))value;return;
case 7:p->mflags2=(__typeof__(p->mflags2))value;return;
default:abort();}}
case 40:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(__typeof__(p->extrinsic))value;return;
case 1:p->blocked=(__typeof__(p->blocked))value;return;
case 2:p->intrinsic=(__typeof__(p->intrinsic))value;return;
default:abort();}}
case 41:{struct q_score*p=at;switch(field){
case 0:p->leader_m_id=(__typeof__(p->leader_m_id))value;return;
default:abort();}}
case 42:{struct rm*p=at;switch(field){
case 0:p->typ=(__typeof__(p->typ))value;return;
case 1:p->flags=(unsigned int)value;return;
default:abort();}}
case 43:{struct skills*p=at;switch(field){
case 0:p->skill=(__typeof__(p->skill))value;return;
default:abort();}}
case 44:{struct throw_and_return_weapon*p=at;switch(field){
case 0:p->range=(__typeof__(p->range))value;return;
case 1:p->tethered=(unsigned int)value;return;
default:abort();}}
case 45:{struct trap*p=at;switch(field){
case 0:p->ttyp=(unsigned int)value;return;
case 1:p->tseen=(unsigned int)value;return;
default:abort();}}
case 46:{struct u_conduct*p=at;switch(field){
case 0:p->weaphit=(__typeof__(p->weaphit))value;return;
default:abort();}}
case 47:{struct u_event*p=at;switch(field){
case 0:p->invoked=(unsigned int)value;return;
default:abort();}}
case 48:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=(__typeof__(p->deaf))value;return;
default:abort();}}
case 49:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(__typeof__(p->v_nexthere))value;return;
case 1:p->v_ocarry=(__typeof__(p->v_ocarry))value;return;
default:abort();}}
case 50:{struct window_procs*p=at;switch(field){
case 0:p->win_delay_output=(__typeof__(p->win_delay_output))value;return;
default:abort();}}
case 51:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 2:p->dx=(__typeof__(p->dx))value;return;
case 3:p->dy=(__typeof__(p->dy))value;return;
case 4:p->dz=(__typeof__(p->dz))value;return;
case 5:p->ux0=(__typeof__(p->ux0))value;return;
case 6:p->uy0=(__typeof__(p->uy0))value;return;
case 8:p->ulevel=(__typeof__(p->ulevel))value;return;
case 9:p->utrap=(__typeof__(p->utrap))value;return;
case 10:p->utraptype=(__typeof__(p->utraptype))value;return;
case 14:p->umonster=(__typeof__(p->umonster))value;return;
case 15:p->umonnum=(__typeof__(p->umonnum))value;return;
case 16:p->mh=(__typeof__(p->mh))value;return;
case 17:p->mhmax=(__typeof__(p->mhmax))value;return;
case 18:p->ulycn=(__typeof__(p->ulycn))value;return;
case 19:p->ucreamed=(__typeof__(p->ucreamed))value;return;
case 20:p->uswallow=(unsigned int)value;return;
case 21:p->uinwater=(unsigned int)value;return;
case 27:p->uluck=(__typeof__(p->uluck))value;return;
case 28:p->moreluck=(__typeof__(p->moreluck))value;return;
case 29:p->uhitinc=(__typeof__(p->uhitinc))value;return;
case 30:p->udaminc=(__typeof__(p->udaminc))value;return;
case 31:p->uhp=(__typeof__(p->uhp))value;return;
case 32:p->uhpmax=(__typeof__(p->uhpmax))value;return;
case 33:p->ustuck=(__typeof__(p->ustuck))value;return;
case 34:p->usteed=(__typeof__(p->usteed))value;return;
case 36:p->twoweap=(__typeof__(p->twoweap))value;return;
default:abort();}}
default:abort();}}
void* teleport_dothrow_address(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->him;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
case 1:return(void*)&p->selfmask;
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return(void*)&p->type;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_something;
case 1:return(void*)&p->c_Something;
case 2:return(void*)&p->c_vision_clears;
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->mon_moving;
case 1:return(void*)&p->objsplit;
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_water_level;
case 1:return(void*)&p->d_air_level;
default:abort();}}
case 8:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->flags;
default:abort();}}
case 9:{struct eshk*p=at;switch(field){
case 0:return(void*)&p->break_seq;
case 1:return(void*)&p->seq_peaceful;
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:return(void*)&p->autoquiver;
case 1:return(void*)&p->pushweapon;
case 2:return(void*)&p->verbose;
default:abort();}}
case 11:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->fireassist;
case 1:return(void*)&p->returning_missile;
default:abort();}}
case 12:{struct instance_globals_b*p=at;switch(field){
case 0:return(void*)&p->bhitpos;
default:abort();}}
case 13:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->command_count;
default:abort();}}
case 14:{struct instance_globals_h*p=at;switch(field){
case 0:return(void*)&p->hero_seq;
default:abort();}}
case 15:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_doagain;
case 1:return(void*)&p->invent;
default:abort();}}
case 16:{struct instance_globals_k*p=at;switch(field){
case 0:return(void*)&p->kickedobj;
default:abort();}}
case 17:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->multi;
case 1:return(void*)&p->multi_reason;
case 2:return(void*)&p->m_shot;
default:abort();}}
case 18:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nomovemsg;
case 1:return(void*)&p->notonhead;
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->otg_temp;
case 1:return(void*)&p->otg_otmp;
default:abort();}}
case 20:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 21:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
default:abort();}}
case 22:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return(void*)&p->killer;
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 24:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return(void*)&p->quest_status;
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->thrownobj;
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
case 1:return(void*)&p->urace;
default:abort();}}
case 27:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->viz_array;
case 1:return(void*)&p->vision_full_recalc;
default:abort();}}
case 28:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 29:{struct kinfo*p=at;switch(field){
case 0:return(void*)&p->format;
case 1:return(void*)&p->name;
default:abort();}}
case 30:{struct levelflags*p=at;switch(field){
default:abort();}}
case 31:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->mgivenname;
case 1:return(void*)&p->eshk;
default:abort();}}
case 32:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 1:return(void*)&p->m_id;
case 2:return(void*)&p->movement;
case 3:return(void*)&p->mx;
case 4:return(void*)&p->my;
case 5:return(void*)&p->mhp;
case 6:return(void*)&p->m_ap_type;
case 7:return(void*)&p->mtame;
case 18:return(void*)&p->mstrategy;
case 19:return(void*)&p->mextra;
default:abort();}}
case 33:{struct multishot*p=at;switch(field){
case 0:return(void*)&p->n;
case 1:return(void*)&p->i;
case 2:return(void*)&p->o;
case 3:return(void*)&p->s;
default:abort();}}
case 34:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 35:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->v;
case 2:return(void*)&p->cobj;
case 3:return(void*)&p->o_id;
case 4:return(void*)&p->ox;
case 5:return(void*)&p->oy;
case 6:return(void*)&p->otyp;
case 7:return(void*)&p->owt;
case 8:return(void*)&p->quan;
case 9:return(void*)&p->spe;
case 10:return(void*)&p->oclass;
case 11:return(void*)&p->invlet;
case 12:return(void*)&p->oartifact;
case 13:return(void*)&p->where;
case 28:return(void*)&p->corpsenm;
case 29:return(void*)&p->owornmask;
case 30:return(void*)&p->oextra;
default:abort();}}
case 36:{struct obj_split*p=at;switch(field){
case 0:return(void*)&p->parent_oid;
case 1:return(void*)&p->child_oid;
default:abort();}}
case 37:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_uname;
case 7:return(void*)&p->oc_subtyp;
default:abort();}}
case 38:{struct oextra*p=at;switch(field){
case 0:return(void*)&p->oname;
default:abort();}}
case 39:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->pmidx;
case 1:return(void*)&p->mlet;
case 2:return(void*)&p->mlevel;
case 3:return(void*)&p->mmove;
case 4:return(void*)&p->maligntyp;
case 5:return(void*)&p->msize;
case 6:return(void*)&p->mflags1;
case 7:return(void*)&p->mflags2;
default:abort();}}
case 40:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 41:{struct q_score*p=at;switch(field){
case 0:return(void*)&p->leader_m_id;
default:abort();}}
case 42:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
default:abort();}}
case 43:{struct skills*p=at;switch(field){
case 0:return(void*)&p->skill;
default:abort();}}
case 44:{struct throw_and_return_weapon*p=at;switch(field){
case 0:return(void*)&p->range;
default:abort();}}
case 45:{struct trap*p=at;switch(field){
default:abort();}}
case 46:{struct u_conduct*p=at;switch(field){
case 0:return(void*)&p->weaphit;
default:abort();}}
case 47:{struct u_event*p=at;switch(field){
default:abort();}}
case 48:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->deaf;
default:abort();}}
case 49:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
case 1:return(void*)&p->v_ocarry;
default:abort();}}
case 50:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_delay_output;
default:abort();}}
case 51:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->dx;
case 3:return(void*)&p->dy;
case 4:return(void*)&p->dz;
case 5:return(void*)&p->ux0;
case 6:return(void*)&p->uy0;
case 7:return(void*)&p->uz;
case 8:return(void*)&p->ulevel;
case 9:return(void*)&p->utrap;
case 10:return(void*)&p->utraptype;
case 11:return(void*)&p->ushops;
case 12:return(void*)&p->ushops0;
case 13:return(void*)&p->uprops;
case 14:return(void*)&p->umonster;
case 15:return(void*)&p->umonnum;
case 16:return(void*)&p->mh;
case 17:return(void*)&p->mhmax;
case 18:return(void*)&p->ulycn;
case 19:return(void*)&p->ucreamed;
case 22:return(void*)&p->uevent;
case 23:return(void*)&p->uconduct;
case 24:return(void*)&p->uroleplay;
case 25:return(void*)&p->ualign;
case 26:return(void*)&p->ualignbase;
case 27:return(void*)&p->uluck;
case 28:return(void*)&p->moreluck;
case 29:return(void*)&p->uhitinc;
case 30:return(void*)&p->udaminc;
case 31:return(void*)&p->uhp;
case 32:return(void*)&p->uhpmax;
case 33:return(void*)&p->ustuck;
case 34:return(void*)&p->usteed;
case 35:return(void*)&p->weapon_skills;
case 36:return(void*)&p->twoweap;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_dothrow_var0(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var1(char * a0){(pline)(a0);}
void teleport_dothrow_var2(char * a0){(You)(a0);}
void teleport_dothrow_var3(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
int teleport_dothrow_var4(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_dothrow_var5(char * a0,char * a1,int a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_dothrow_var6(char * a0){(You)(a0);}
void teleport_dothrow_var7(char * a0){(You_cant)(a0);}
void teleport_dothrow_var8(char * a0){(You)(a0);}
void teleport_dothrow_var9(char * a0){(You)(a0);}
void teleport_dothrow_var10(char * a0,char * a1,int a2,char * a3,char * a4){(You)(a0,a1,a2,a3,a4);}
void teleport_dothrow_var11(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_dothrow_var12(char * a0){(You_feel)(a0);}
void teleport_dothrow_var13(char * a0){(You)(a0);}
void teleport_dothrow_var14(char * a0){(pline)(a0);}
void teleport_dothrow_var15(char * a0){(You)(a0);}
void teleport_dothrow_var16(char * a0,char * a1){(You)(a0,a1);}
void teleport_dothrow_var17(char * a0){(You)(a0);}
void teleport_dothrow_var18(char * a0,char * a1){(You)(a0,a1);}
void teleport_dothrow_var19(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_dothrow_var20(char * a0,char * a1){(You)(a0,a1);}
int teleport_dothrow_var21(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_dothrow_var22(char * a0){(You)(a0);}
void teleport_dothrow_var23(char * a0,char * a1){(Norep)(a0,a1);}
void teleport_dothrow_var24(char * a0){(Norep)(a0);}
void teleport_dothrow_var25(char * a0){(pline)(a0);}
void teleport_dothrow_var26(char * a0,char * a1){(You)(a0,a1);}
void teleport_dothrow_var27(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var28(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var29(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_dothrow_var30(char * a0){(You_feel)(a0);}
void teleport_dothrow_var31(char * a0,char * a1){(You)(a0,a1);}
void teleport_dothrow_var32(char * a0,char * a1){(You)(a0,a1);}
void teleport_dothrow_var33(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var34(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var35(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_dothrow_var36(char * a0,char * a1){(Your)(a0,a1);}
void teleport_dothrow_var37(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var38(char * a0){(pline)(a0);}
void teleport_dothrow_var39(char * a0,char * a1){(Your)(a0,a1);}
void teleport_dothrow_var40(char * a0){(pline)(a0);}
void teleport_dothrow_var41(char * a0){(pline)(a0);}
void teleport_dothrow_var42(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var43(char * a0,char * a1){(Your)(a0,a1);}
void teleport_dothrow_var44(char * a0){(pline_The)(a0);}
void teleport_dothrow_var45(char * a0){(You)(a0);}
void teleport_dothrow_var46(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var47(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var48(char * a0,char * a1){(You)(a0,a1);}
void teleport_dothrow_var49(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var50(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_dothrow_var51(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var52(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_dothrow_var53(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var54(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var55(char * a0){(pline)(a0);}
void teleport_dothrow_var56(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var57(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var58(char * a0,int a1){(impossible)(a0,a1);}
void teleport_dothrow_var59(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var60(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var61(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dothrow_var62(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_dothrow_var63(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_dothrow_var64(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_dothrow_var65(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_dothrow_var66(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var67(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var68(char * a0){(You)(a0);}
void teleport_dothrow_var69(char * a0,char * a1,char * a2){(Your)(a0,a1,a2);}
void teleport_dothrow_var70(char * a0,int a1){(impossible)(a0,a1);}
void teleport_dothrow_var71(char * a0,char * a1){(You_hear)(a0,a1);}
void teleport_dothrow_var72(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_dothrow_var73(char * a0){(pline)(a0);}
void teleport_dothrow_var74(char * a0){(pline)(a0);}
void teleport_dothrow_var75(char * a0){(pline)(a0);}
void teleport_dothrow_var76(char * a0){(You)(a0);}
void teleport_dothrow_var77(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_dothrow_var78(char * a0,char * a1,char * a2){(pline_The)(a0,a1,a2);}
void teleport_dothrow_var79(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dothrow_var80(char * a0,char * a1){(pline_The)(a0,a1);}
signed char teleport_dothrow_indirect0(signed char (*fn)(genericptr_t, coordxy, coordxy),void * a0,short a1,short a2){return fn(a0,a1,a2);}
signed char teleport_dothrow_indirect1(signed char (*fn)(genericptr_t, coordxy, coordxy),void * a0,short a1,short a2){return fn(a0,a1,a2);}
void teleport_dothrow_indirect2(void (*fn)(void)){fn();}
void teleport_dothrow_indirect3(void (*fn)(void)){fn();}
void teleport_dothrow_indirect4(void (*fn)(void)){fn();}
void teleport_dothrow_indirect5(void (*fn)(void)){fn();}
extern int dofire(void);
extern boolean hurtle_step(genericptr_t a0,coordxy a1,coordxy a2);
extern boolean teleport_dothrow_mhurtle_step(genericptr_t a0,coordxy a1,coordxy a2);
extern int teleport_dothrow_throw_ok(struct obj * a0);
uintptr_t teleport_dothrow_owned_pointer(int i){switch(i){
case 0:return(uintptr_t)(dofire);
case 1:return(uintptr_t)(hurtle_step);
case 2:return(uintptr_t)(teleport_dothrow_mhurtle_step);
case 3:return(uintptr_t)(teleport_dothrow_throw_ok);
default:abort();}}
uintptr_t teleport_dothrow_native_pointer(int i){switch(i){
case 0:return(uintptr_t)(doswapweapon);
case 1:return(uintptr_t)(dowield);
case 2:return(uintptr_t)(xname);
default:abort();}}
#pragma clang diagnostic pop
void teleport_dothrow_free(void*p){(free)(p);}
static char dothrow_literals[2870];
char*teleport_dothrow_literal_storage(void){return dothrow_literals;}
size_t teleport_dothrow_literal_capacity(void){return sizeof dothrow_literals;}
static char dothrow_backing_0[33];
static char dothrow_backing_1[20];
static char dothrow_backing_2[14];
static char dothrow_backing_3[12];
static char dothrow_backing_4[12];
void*teleport_dothrow_storage(int i){switch(i){
case 0:return &dothrow_backing_0;
case 1:return &dothrow_backing_1;
case 2:return &dothrow_backing_2;
case 3:return &dothrow_backing_3;
case 4:return &dothrow_backing_4;
default:abort();}}
