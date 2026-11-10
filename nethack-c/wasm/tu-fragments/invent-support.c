/* INVENT typed field/header/dependency/storage transport only. Source algorithms remain JS. */
#include "../../../scripts/tu-invent-layout.h"
#include <stdlib.h>
#ifndef TELEPORT_INVENT_ORIGINAL_INCLUDED
struct xprnctx { char let; boolean dot; };
#endif
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(size_t)==8,"Review INVENT LP64");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0&&sizeof(xint8)==1&&(xint8)-1<0&&sizeof(coordxy)==2&&(char)-1<0,"Review INVENT scalar widths");
void*teleport_invent_global(int index){switch(index){
case 0:return(void*)&u;
case 1:return(void*)&objects;
case 2:return(void*)&flags;
case 3:return(void*)&obj_descr;
case 4:return(void*)&program_state;
case 5:return(void*)&gs;
case 6:return(void*)&mons;
case 7:return(void*)&gi;
case 8:return(void*)&gl;
case 9:return(void*)&gu;
case 10:return(void*)&disp;
case 11:return(void*)&svc;
case 12:return(void*)&uquiver;
case 13:return(void*)&gy;
case 14:return(void*)&uwep;
case 15:return(void*)&uswapwep;
case 16:return(void*)&svl;
case 17:return(void*)&uball;
case 18:return(void*)&uchain;
case 19:return(void*)&uarmg;
case 20:return(void*)&hands_obj;
case 21:return(void*)&iflags;
case 22:return(void*)&windowprocs;
case 23:return(void*)&quitchars;
case 24:return(void*)&c_common_strings;
case 25:return(void*)&uarm;
case 26:return(void*)&uarmc;
case 27:return(void*)&uarmf;
case 28:return(void*)&uarmh;
case 29:return(void*)&uarms;
case 30:return(void*)&uarmu;
case 31:return(void*)&uright;
case 32:return(void*)&uleft;
case 33:return(void*)&uamul;
case 34:return(void*)&ublindf;
case 35:return(void*)&ynaqchars;
case 36:return(void*)&ynNaqchars;
case 37:return(void*)&yn_number;
case 38:return(void*)&cg;
case 39:return(void*)&nul_glyphinfo;
case 40:return(void*)&gd;
case 41:return(void*)&go;
case 42:return(void*)&ynchars;
case 43:return(void*)&gc;
case 44:return(void*)&WIN_INVEN;
case 45:return(void*)&def_oc_syms;
case 46:return(void*)&gt;
case 47:return(void*)&WIN_MESSAGE;
case 48:return(void*)&defsyms;
case 49:return(void*)&svd;
case 50:return(void*)&uskin;
case 51:return(void*)&zerowri;
case 52:return(void*)&gp;
default:abort();}}
uint64_t teleport_invent_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(dlevel_t));
case 6:return(uint64_t)(sizeof(struct Role));
case 7:return(uint64_t)(sizeof(struct _cmd_queue));
case 8:return(uint64_t)(sizeof(struct achievement_tracking));
case 9:return(uint64_t)(sizeof(struct c_common_strings));
case 10:return(uint64_t)(sizeof(struct class_sym));
case 11:return(uint64_t)(sizeof(struct const_globals));
case 12:return(uint64_t)(sizeof(struct context_info));
case 13:return(uint64_t)(sizeof(struct d_level));
case 14:return(uint64_t)(sizeof(struct dgn_topology));
case 15:return(uint64_t)(sizeof(struct display_hints));
case 16:return(uint64_t)(sizeof(struct flag));
case 17:return(uint64_t)(sizeof(struct from_core));
case 18:return(uint64_t)(sizeof(struct glyphinfo));
case 19:return(uint64_t)(sizeof(struct instance_flags));
case 20:return(uint64_t)(sizeof(struct instance_globals_c));
case 21:return(uint64_t)(sizeof(struct instance_globals_d));
case 22:return(uint64_t)(sizeof(struct instance_globals_i));
case 23:return(uint64_t)(sizeof(struct instance_globals_l));
case 24:return(uint64_t)(sizeof(struct instance_globals_o));
case 25:return(uint64_t)(sizeof(struct instance_globals_p));
case 26:return(uint64_t)(sizeof(struct instance_globals_s));
case 27:return(uint64_t)(sizeof(struct instance_globals_saved_c));
case 28:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 29:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 30:return(uint64_t)(sizeof(struct instance_globals_t));
case 31:return(uint64_t)(sizeof(struct instance_globals_u));
case 32:return(uint64_t)(sizeof(struct instance_globals_y));
case 33:return(uint64_t)(sizeof(struct mi));
case 34:return(uint64_t)(sizeof(struct monst));
case 35:return(uint64_t)(sizeof(struct nhcoord));
case 36:return(uint64_t)(sizeof(struct obj));
case 37:return(uint64_t)(sizeof(struct objclass));
case 38:return(uint64_t)(sizeof(struct objdescr));
case 39:return(uint64_t)(sizeof(struct oextra));
case 40:return(uint64_t)(sizeof(struct permonst));
case 41:return(uint64_t)(sizeof(struct prop));
case 42:return(uint64_t)(sizeof(struct rm));
case 43:return(uint64_t)(sizeof(struct sinfo));
case 44:return(uint64_t)(sizeof(struct sortloot_item));
case 45:return(uint64_t)(sizeof(struct symdef));
case 46:return(uint64_t)(sizeof(struct tin_info));
case 47:return(uint64_t)(sizeof(struct to_core));
case 48:return(uint64_t)(sizeof(struct trap));
case 49:return(uint64_t)(sizeof(struct u_conduct));
case 50:return(uint64_t)(sizeof(struct u_have));
case 51:return(uint64_t)(sizeof(struct u_roleplay));
case 52:return(uint64_t)(sizeof(struct win_request_info_t));
case 53:return(uint64_t)(sizeof(struct window_procs));
case 54:return(uint64_t)(sizeof(struct xprnctx));
case 55:return(uint64_t)(sizeof(struct you));
case 56:return(uint64_t)(sizeof(union any));
case 57:return(uint64_t)(sizeof(union vptrs));
case 58:return(uint64_t)(ACH_AMUL);
case 59:return(uint64_t)(ACH_BELL);
case 60:return(uint64_t)(ACH_BOOK);
case 61:return(uint64_t)(ACH_CNDL);
case 62:return(uint64_t)(ACH_MINE_PRIZE);
case 63:return(uint64_t)(ACH_SOKO_PRIZE);
case 64:return(uint64_t)(AKLYS);
case 65:return(uint64_t)(ALTAR);
case 66:return(uint64_t)(AMULET_CLASS);
case 67:return(uint64_t)(AMULET_OF_YENDOR);
case 68:return(uint64_t)(ARMOR_CLASS);
case 69:return(uint64_t)(ARM_BOOTS);
case 70:return(uint64_t)(ARM_CLOAK);
case 71:return(uint64_t)(ARM_GLOVES);
case 72:return(uint64_t)(ARM_HELM);
case 73:return(uint64_t)(ARM_SHIELD);
case 74:return(uint64_t)(ARM_SHIRT);
case 75:return(uint64_t)(ARM_SUIT);
case 76:return(uint64_t)(ART_EYES_OF_THE_OVERWORLD);
case 77:return(uint64_t)(ART_MJOLLNIR);
case 78:return(uint64_t)(ART_SNICKERSNEE);
case 79:return(uint64_t)(A_CHA);
case 80:return(uint64_t)(A_CON);
case 81:return(uint64_t)(A_DEX);
case 82:return(uint64_t)(A_INT);
case 83:return(uint64_t)(A_WIS);
case 84:return(uint64_t)(BAG_OF_TRICKS);
case 85:return(uint64_t)(BALL_CLASS);
case 86:return(uint64_t)(BELL_OF_OPENING);
case 87:return(uint64_t)(BLINDED);
case 88:return(uint64_t)(BOULDER);
case 89:return(uint64_t)(BUGLE);
case 90:return(uint64_t)(CANDELABRUM_OF_INVOCATION);
case 91:return(uint64_t)(CHAIN_CLASS);
case 92:return(uint64_t)(CMDQ_INT);
case 93:return(uint64_t)(CMDQ_KEY);
case 94:return(uint64_t)(CMDQ_USER_INPUT);
case 95:return(uint64_t)(COIN_CLASS);
case 96:return(uint64_t)(CORPSE);
case 97:return(uint64_t)(COST_NOCONTENTS);
case 98:return(uint64_t)(CQ_CANNED);
case 99:return(uint64_t)(CQ_REPEAT);
case 100:return(uint64_t)(CRYSKNIFE);
case 101:return(uint64_t)(DBWALL);
case 102:return(uint64_t)(DOOR);
case 103:return(uint64_t)(DRAWBRIDGE_DOWN);
case 104:return(uint64_t)(DRAWBRIDGE_UP);
case 105:return(uint64_t)(DRUM_OF_EARTHQUAKE);
case 106:return(uint64_t)(EGG);
case 107:return(uint64_t)(FAKE_AMULET_OF_YENDOR);
case 108:return(uint64_t)(FIGURINE);
case 109:return(uint64_t)(FIG_TRANSFORM);
case 110:return(uint64_t)(FINGERTIP);
case 111:return(uint64_t)(FIRE_HORN);
case 112:return(uint64_t)(FIRST_OBJECT);
case 113:return(uint64_t)(FIRST_REAL_GEM);
case 114:return(uint64_t)(FIRST_SPELL);
case 115:return(uint64_t)(FOOD_CLASS);
case 116:return(uint64_t)(FOUNTAIN);
case 117:return(uint64_t)(FROST_HORN);
case 118:return(uint64_t)(FUMBLING);
case 119:return(uint64_t)(GEMSTONE);
case 120:return(uint64_t)(GEM_CLASS);
case 121:return(uint64_t)(GETOBJ_DOWNPLAY);
case 122:return(uint64_t)(GETOBJ_EXCLUDE);
case 123:return(uint64_t)(GETOBJ_EXCLUDE_INACCESS);
case 124:return(uint64_t)(GETOBJ_EXCLUDE_NONINVENT);
case 125:return(uint64_t)(GETOBJ_EXCLUDE_SELECTABLE);
case 126:return(uint64_t)(GETOBJ_SUGGEST);
case 127:return(uint64_t)(GLASS);
case 128:return(uint64_t)(GLOB_OF_BLACK_PUDDING);
case 129:return(uint64_t)(GLOB_OF_BROWN_PUDDING);
case 130:return(uint64_t)(GLOB_OF_GRAY_OOZE);
case 131:return(uint64_t)(GLOB_OF_GREEN_SLIME);
case 132:return(uint64_t)(GLYPH_BODY_OFF);
case 133:return(uint64_t)(GLYPH_BODY_PILETOP_OFF);
case 134:return(uint64_t)(GLYPH_MON_FEM_OFF);
case 135:return(uint64_t)(GLYPH_MON_MALE_OFF);
case 136:return(uint64_t)(GLYPH_OBJ_OFF);
case 137:return(uint64_t)(GLYPH_OBJ_PILETOP_OFF);
case 138:return(uint64_t)(GLYPH_STATUE_FEM_OFF);
case 139:return(uint64_t)(GLYPH_STATUE_FEM_PILETOP_OFF);
case 140:return(uint64_t)(GLYPH_STATUE_MALE_OFF);
case 141:return(uint64_t)(GLYPH_STATUE_MALE_PILETOP_OFF);
case 142:return(uint64_t)(GOLD_PIECE);
case 143:return(uint64_t)(GOLD_SYM);
case 144:return(uint64_t)(GRAVE);
case 145:return(uint64_t)(HALLUC);
case 146:return(uint64_t)(HALLUC_RES);
case 147:return(uint64_t)(HAND);
case 148:return(uint64_t)(HORN_OF_PLENTY);
case 149:return(uint64_t)(ICE);
case 150:return(uint64_t)(ILLOBJ_CLASS);
case 151:return(uint64_t)(IRONBARS);
case 152:return(uint64_t)(InvInUse);
case 153:return(uint64_t)(InvOptNone);
case 154:return(uint64_t)(InvOptOn);
case 155:return(uint64_t)(InvShowGold);
case 156:return(uint64_t)(LARGE_BOX);
case 157:return(uint64_t)(LAST_GLASS_GEM);
case 158:return(uint64_t)(LAST_SPELL);
case 159:return(uint64_t)(LEASH);
case 160:return(uint64_t)(LEATHER_DRUM);
case 161:return(uint64_t)(LENSES);
case 162:return(uint64_t)(LOADSTONE);
case 163:return(uint64_t)(LOW_PM);
case 164:return(uint64_t)(MAGIC_FLUTE);
case 165:return(uint64_t)(MAGIC_HARP);
case 166:return(uint64_t)(MAXOCLASSES);
case 167:return(uint64_t)(NON_PM);
case 168:return(uint64_t)(NUMMONS);
case 169:return(uint64_t)(NUM_OBJECTS);
case 170:return(uint64_t)(PIT);
case 171:return(uint64_t)(PLNMSG_ONE_ITEM_HERE);
case 172:return(uint64_t)(PM_ARCHEOLOGIST);
case 173:return(uint64_t)(PM_CHICKATRICE);
case 174:return(uint64_t)(PM_CLERIC);
case 175:return(uint64_t)(PM_COCKATRICE);
case 176:return(uint64_t)(PM_DEATH);
case 177:return(uint64_t)(PM_FAMINE);
case 178:return(uint64_t)(PM_PESTILENCE);
case 179:return(uint64_t)(POTION_CLASS);
case 180:return(uint64_t)(POT_OIL);
case 181:return(uint64_t)(POT_WATER);
case 182:return(uint64_t)(P_BOOMERANG);
case 183:return(uint64_t)(P_BOW);
case 184:return(uint64_t)(P_CROSSBOW);
case 185:return(uint64_t)(P_DAGGER);
case 186:return(uint64_t)(P_DART);
case 187:return(uint64_t)(P_KNIFE);
case 188:return(uint64_t)(P_LANCE);
case 189:return(uint64_t)(P_POLEARMS);
case 190:return(uint64_t)(P_SPEAR);
case 191:return(uint64_t)(RING_CLASS);
case 192:return(uint64_t)(ROCK);
case 193:return(uint64_t)(ROCK_CLASS);
case 194:return(uint64_t)(SCROLL_CLASS);
case 195:return(uint64_t)(SCR_BLANK_PAPER);
case 196:return(uint64_t)(SCR_MAIL);
case 197:return(uint64_t)(SCR_SCARE_MONSTER);
case 198:return(uint64_t)(SINK);
case 199:return(uint64_t)(SLIME_MOLD);
case 200:return(uint64_t)(SPBOOK_CLASS);
case 201:return(uint64_t)(SPE_BOOK_OF_THE_DEAD);
case 202:return(uint64_t)(SPE_NOVEL);
case 203:return(uint64_t)(SPIKED_PIT);
case 204:return(uint64_t)(STATUE);
case 205:return(uint64_t)(STOMACH);
case 206:return(uint64_t)(STONE_RES);
case 207:return(uint64_t)(S_TROLL);
case 208:return(uint64_t)(S_fountain);
case 209:return(uint64_t)(S_grave);
case 210:return(uint64_t)(S_lava);
case 211:return(uint64_t)(S_ndoor);
case 212:return(uint64_t)(S_sink);
case 213:return(uint64_t)(S_throne);
case 214:return(uint64_t)(S_tree);
case 215:return(uint64_t)(S_vcdbridge);
case 216:return(uint64_t)(S_vcdoor);
case 217:return(uint64_t)(S_vodbridge);
case 218:return(uint64_t)(S_vodoor);
case 219:return(uint64_t)(TALLOW_CANDLE);
case 220:return(uint64_t)(THRONE);
case 221:return(uint64_t)(TIN);
case 222:return(uint64_t)(TOOLED_HORN);
case 223:return(uint64_t)(TOOL_CLASS);
case 224:return(uint64_t)(TOWEL);
case 225:return(uint64_t)(TREE);
case 226:return(uint64_t)(VENOM_CLASS);
case 227:return(uint64_t)(WAND_CLASS);
case 228:return(uint64_t)(WAX_CANDLE);
case 229:return(uint64_t)(WEAPON_CLASS);
case 230:return(uint64_t)(WOODEN_FLUTE);
case 231:return(uint64_t)(WOODEN_HARP);
case 232:return(uint64_t)(invlet_basic);
case 233:return(uint64_t)(prohibited);
case 234:return(uint64_t)(request_settings);
case 235:return(uint64_t)(set_gameview);
case 236:return(uint64_t)(set_mode);
case 237:return(uint64_t)(st_all);
case 238:return(uint64_t)(toggling_not);
case 239:return(uint64_t)(toggling_off);
case 240:return(uint64_t)(toggling_on);
case 241:return(uint64_t)(too_early);
case 242:return(uint64_t)(too_small);
case 243:return(uint64_t)(wp_tty);
default:abort();}}
uint64_t teleport_invent_read(int kind,void*at,int field){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 1:{struct _cmd_queue*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->key);
case 2:return(uint64_t)(uintptr_t)(p->intval);
default:abort();}}
case 2:{struct achievement_tracking*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mines_prize_oid);
case 1:return(uint64_t)(uintptr_t)(p->soko_prize_oid);
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_obj);
case 1:return(uint64_t)(uintptr_t)(p->a_int);
case 2:return(uint64_t)(uintptr_t)(p->a_char);
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_thats_enough_tries);
case 1:return(uint64_t)(uintptr_t)(p->c_silly_thing_to);
case 2:return(uint64_t)(uintptr_t)(p->c_Never_mind);
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sym);
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroobj);
case 1:return(uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 7:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mon_moving);
case 1:return(uint64_t)(uintptr_t)(&p->tin);
case 2:return(uint64_t)(uintptr_t)(&p->achieveo);
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_air_level);
default:abort();}}
case 10:{struct display_hints*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 11:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(p->objlist);
case 3:return(uint64_t)(uintptr_t)(p->buriedobjlist);
default:abort();}}
case 12:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->autoquiver);
case 1:return(uint64_t)(uintptr_t)(p->debug);
case 2:return(uint64_t)(uintptr_t)(p->goldX);
case 3:return(uint64_t)(uintptr_t)(p->invlet_constant);
case 4:return(uint64_t)(uintptr_t)(p->mention_decor);
case 5:return(uint64_t)(uintptr_t)(p->pickup_thrown);
case 6:return(uint64_t)(uintptr_t)(p->sortpack);
case 7:return(uint64_t)(uintptr_t)(p->verbose);
case 8:return(uint64_t)(uintptr_t)(p->pickup_burden);
case 9:return(uint64_t)(uintptr_t)(p->pile_limit);
case 10:return(uint64_t)(uintptr_t)(p->sortloot);
case 11:return(uint64_t)(uintptr_t)(&p->inv_order);
case 12:return(uint64_t)(uintptr_t)(p->menu_style);
case 13:return(uint64_t)(uintptr_t)(p->lootabc);
default:abort();}}
case 13:{struct from_core*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->invmode);
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
case 1:return(uint64_t)(uintptr_t)(p->override_ID);
case 2:return(uint64_t)(uintptr_t)(p->suppress_price);
case 3:return(uint64_t)(uintptr_t)(p->force_invmenu);
case 4:return(uint64_t)(uintptr_t)(p->menu_head_objsym);
case 5:return(uint64_t)(uintptr_t)(p->menu_requested);
case 6:return(uint64_t)(uintptr_t)(p->menu_tab_sep);
case 7:return(uint64_t)(uintptr_t)(p->perm_invent);
case 8:return(uint64_t)(uintptr_t)(p->perm_invent_pending);
case 9:return(uint64_t)(uintptr_t)(p->prev_decor);
case 10:return(uint64_t)(uintptr_t)(p->perminv_mode);
default:abort();}}
case 15:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->cached_pickinv_win);
case 1:return(uint64_t)(uintptr_t)(p->core_invent_state);
default:abort();}}
case 16:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->distantname);
default:abort();}}
case 17:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_doagain);
case 1:return(uint64_t)(uintptr_t)(p->invent);
case 2:return(uint64_t)(uintptr_t)(p->invbuf);
case 3:return(uint64_t)(uintptr_t)(p->invbufsiz);
case 4:return(uint64_t)(uintptr_t)(p->in_sync_perminvent);
default:abort();}}
case 18:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lastinvnr);
case 1:return(uint64_t)(uintptr_t)(p->loot_reset_justpicked);
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->otg_temp);
case 1:return(uint64_t)(uintptr_t)(p->otg_otmp);
case 2:return(uint64_t)(uintptr_t)(&p->only);
default:abort();}}
case 20:{struct instance_globals_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->perm_invent_toggling_direction);
default:abort();}}
case 21:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sortlootmode);
default:abort();}}
case 22:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 23:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 24:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->this_type);
case 1:return(uint64_t)(uintptr_t)(p->this_title);
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 27:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 28:{struct mi*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->item);
case 1:return(uint64_t)(uintptr_t)(p->count);
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->minvent);
case 2:return(uint64_t)(uintptr_t)(p->mw);
case 3:return(uint64_t)(uintptr_t)(p->misc_worn_check);
default:abort();}}
case 30:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 31:{struct obj*p=at;switch(field){
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
case 14:return(uint64_t)(uintptr_t)(p->timed);
case 15:return(uint64_t)(uintptr_t)(p->cursed);
case 16:return(uint64_t)(uintptr_t)(p->blessed);
case 17:return(uint64_t)(uintptr_t)(p->unpaid);
case 18:return(uint64_t)(uintptr_t)(p->no_charge);
case 19:return(uint64_t)(uintptr_t)(p->lamplit);
case 20:return(uint64_t)(uintptr_t)(p->known);
case 21:return(uint64_t)(uintptr_t)(p->dknown);
case 22:return(uint64_t)(uintptr_t)(p->bknown);
case 23:return(uint64_t)(uintptr_t)(p->rknown);
case 24:return(uint64_t)(uintptr_t)(p->cknown);
case 25:return(uint64_t)(uintptr_t)(p->lknown);
case 26:return(uint64_t)(uintptr_t)(p->nomerge);
case 27:return(uint64_t)(uintptr_t)(p->oeroded);
case 28:return(uint64_t)(uintptr_t)(p->oeroded2);
case 29:return(uint64_t)(uintptr_t)(p->oerodeproof);
case 30:return(uint64_t)(uintptr_t)(p->obroken);
case 31:return(uint64_t)(uintptr_t)(p->otrapped);
case 32:return(uint64_t)(uintptr_t)(p->globby);
case 33:return(uint64_t)(uintptr_t)(p->greased);
case 34:return(uint64_t)(uintptr_t)(p->in_use);
case 35:return(uint64_t)(uintptr_t)(p->bypass);
case 36:return(uint64_t)(uintptr_t)(p->pickup_prev);
case 37:return(uint64_t)(uintptr_t)(p->how_lost);
case 38:return(uint64_t)(uintptr_t)(p->corpsenm);
case 39:return(uint64_t)(uintptr_t)(p->usecount);
case 40:return(uint64_t)(uintptr_t)(p->oeaten);
case 41:return(uint64_t)(uintptr_t)(p->age);
case 42:return(uint64_t)(uintptr_t)(p->owornmask);
case 43:return(uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_descr_idx);
case 1:return(uint64_t)(uintptr_t)(p->oc_uname);
case 2:return(uint64_t)(uintptr_t)(p->oc_name_known);
case 3:return(uint64_t)(uintptr_t)(p->oc_merge);
case 4:return(uint64_t)(uintptr_t)(p->oc_uses_known);
case 5:return(uint64_t)(uintptr_t)(p->oc_material);
case 6:return(uint64_t)(uintptr_t)(p->oc_subtyp);
default:abort();}}
case 33:{struct objdescr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_descr);
default:abort();}}
case 34:{struct oextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oname);
case 1:return(uint64_t)(uintptr_t)(p->omonst);
case 2:return(uint64_t)(uintptr_t)(p->omailcmd);
case 3:return(uint64_t)(uintptr_t)(p->omid);
default:abort();}}
case 35:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mlet);
case 1:return(uint64_t)(uintptr_t)(p->mflags1);
default:abort();}}
case 36:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 37:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 38:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->something_worth_saving);
case 1:return(uint64_t)(uintptr_t)(p->in_moveloop);
case 2:return(uint64_t)(uintptr_t)(p->beyond_savefile_load);
default:abort();}}
case 39:{struct sortloot_item*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->obj);
case 1:return(uint64_t)(uintptr_t)(p->str);
case 2:return(uint64_t)(uintptr_t)(p->indx);
case 3:return(uint64_t)(uintptr_t)(p->orderclass);
case 4:return(uint64_t)(uintptr_t)(p->subclass);
case 5:return(uint64_t)(uintptr_t)(p->disco);
case 6:return(uint64_t)(uintptr_t)(p->inuse);
default:abort();}}
case 40:{struct symdef*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->explanation);
default:abort();}}
case 41:{struct tin_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tin);
case 1:return(uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 42:{struct to_core*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tocore_flags);
case 1:return(uint64_t)(uintptr_t)(p->maxslot);
case 2:return(uint64_t)(uintptr_t)(p->needrows);
case 3:return(uint64_t)(uintptr_t)(p->needcols);
case 4:return(uint64_t)(uintptr_t)(p->haverows);
case 5:return(uint64_t)(uintptr_t)(p->havecols);
default:abort();}}
case 43:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ttyp);
case 1:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 44:{struct u_conduct*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->literate);
default:abort();}}
case 45:{struct u_have*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->amulet);
case 1:return(uint64_t)(uintptr_t)(p->bell);
case 2:return(uint64_t)(uintptr_t)(p->book);
case 3:return(uint64_t)(uintptr_t)(p->menorah);
case 4:return(uint64_t)(uintptr_t)(p->questart);
default:abort();}}
case 46:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->numrerolls);
default:abort();}}
case 47:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
case 1:return(uint64_t)(uintptr_t)(p->v_ocontainer);
default:abort();}}
case 48:{struct win_request_info_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->tocore);
case 1:return(uint64_t)(uintptr_t)(&p->fromcore);
default:abort();}}
case 49:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->wp_id);
case 2:return(uint64_t)(uintptr_t)(p->wincap);
case 3:return(uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 4:return(uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 5:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 6:return(uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 7:return(uint64_t)(uintptr_t)(p->win_putstr);
case 8:return(uint64_t)(uintptr_t)(p->win_start_menu);
case 9:return(uint64_t)(uintptr_t)(p->win_end_menu);
case 10:return(uint64_t)(uintptr_t)(p->win_message_menu);
case 11:return(uint64_t)(uintptr_t)(p->win_wait_synch);
case 12:return(uint64_t)(uintptr_t)(p->win_putmsghistory);
case 13:return(uint64_t)(uintptr_t)(p->win_update_inventory);
case 14:return(uint64_t)(uintptr_t)(p->win_ctrl_nhwindow);
default:abort();}}
case 50:{struct xprnctx*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->let);
case 1:return(uint64_t)(uintptr_t)(p->dot);
default:abort();}}
case 51:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(&p->uz);
case 3:return(uint64_t)(uintptr_t)(&p->urooms);
case 4:return(uint64_t)(uintptr_t)(&p->ushops);
case 5:return(uint64_t)(uintptr_t)(&p->uprops);
case 6:return(uint64_t)(uintptr_t)(p->umonster);
case 7:return(uint64_t)(uintptr_t)(p->umonnum);
case 8:return(uint64_t)(uintptr_t)(p->uswallow);
case 9:return(uint64_t)(uintptr_t)(p->uinwater);
case 10:return(uint64_t)(uintptr_t)(p->uundetected);
case 11:return(uint64_t)(uintptr_t)(p->uhandedness);
case 12:return(uint64_t)(uintptr_t)(&p->uhave);
case 13:return(uint64_t)(uintptr_t)(&p->uconduct);
case 14:return(uint64_t)(uintptr_t)(&p->uroleplay);
case 15:return(uint64_t)(uintptr_t)(p->ustuck);
case 16:return(uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
default:abort();}}
void teleport_invent_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 1:{struct _cmd_queue*p=at;switch(field){
case 0:p->typ=(__typeof__(p->typ))value;return;
case 1:p->key=(__typeof__(p->key))value;return;
case 2:p->intval=(__typeof__(p->intval))value;return;
default:abort();}}
case 2:{struct achievement_tracking*p=at;switch(field){
case 0:p->mines_prize_oid=(__typeof__(p->mines_prize_oid))value;return;
case 1:p->soko_prize_oid=(__typeof__(p->soko_prize_oid))value;return;
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:p->a_obj=(__typeof__(p->a_obj))value;return;
case 1:p->a_int=(__typeof__(p->a_int))value;return;
case 2:p->a_char=(__typeof__(p->a_char))value;return;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:p->sym=(__typeof__(p->sym))value;return;
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
default:abort();}}
case 7:{struct context_info*p=at;switch(field){
case 0:p->mon_moving=(__typeof__(p->mon_moving))value;return;
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
default:abort();}}
case 10:{struct display_hints*p=at;switch(field){
case 0:p->botl=(__typeof__(p->botl))value;return;
default:abort();}}
case 11:{dlevel_t*p=at;switch(field){
case 2:p->objlist=(__typeof__(p->objlist))value;return;
case 3:p->buriedobjlist=(__typeof__(p->buriedobjlist))value;return;
default:abort();}}
case 12:{struct flag*p=at;switch(field){
case 0:p->autoquiver=(__typeof__(p->autoquiver))value;return;
case 1:p->debug=(__typeof__(p->debug))value;return;
case 2:p->goldX=(__typeof__(p->goldX))value;return;
case 3:p->invlet_constant=(__typeof__(p->invlet_constant))value;return;
case 4:p->mention_decor=(__typeof__(p->mention_decor))value;return;
case 5:p->pickup_thrown=(__typeof__(p->pickup_thrown))value;return;
case 6:p->sortpack=(__typeof__(p->sortpack))value;return;
case 7:p->verbose=(__typeof__(p->verbose))value;return;
case 8:p->pickup_burden=(__typeof__(p->pickup_burden))value;return;
case 9:p->pile_limit=(__typeof__(p->pile_limit))value;return;
case 10:p->sortloot=(__typeof__(p->sortloot))value;return;
case 12:p->menu_style=(__typeof__(p->menu_style))value;return;
case 13:p->lootabc=(__typeof__(p->lootabc))value;return;
default:abort();}}
case 13:{struct from_core*p=at;switch(field){
case 0:p->invmode=(__typeof__(p->invmode))value;return;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(__typeof__(p->last_msg))value;return;
case 1:p->override_ID=(__typeof__(p->override_ID))value;return;
case 2:p->suppress_price=(__typeof__(p->suppress_price))value;return;
case 3:p->force_invmenu=(__typeof__(p->force_invmenu))value;return;
case 4:p->menu_head_objsym=(__typeof__(p->menu_head_objsym))value;return;
case 5:p->menu_requested=(__typeof__(p->menu_requested))value;return;
case 6:p->menu_tab_sep=(__typeof__(p->menu_tab_sep))value;return;
case 7:p->perm_invent=(__typeof__(p->perm_invent))value;return;
case 8:p->perm_invent_pending=(__typeof__(p->perm_invent_pending))value;return;
case 9:p->prev_decor=(__typeof__(p->prev_decor))value;return;
case 10:p->perminv_mode=(__typeof__(p->perminv_mode))value;return;
default:abort();}}
case 15:{struct instance_globals_c*p=at;switch(field){
case 0:p->cached_pickinv_win=(__typeof__(p->cached_pickinv_win))value;return;
case 1:p->core_invent_state=(__typeof__(p->core_invent_state))value;return;
default:abort();}}
case 16:{struct instance_globals_d*p=at;switch(field){
case 0:p->distantname=(__typeof__(p->distantname))value;return;
default:abort();}}
case 17:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_doagain=(__typeof__(p->in_doagain))value;return;
case 1:p->invent=(__typeof__(p->invent))value;return;
case 2:p->invbuf=(__typeof__(p->invbuf))value;return;
case 3:p->invbufsiz=(__typeof__(p->invbufsiz))value;return;
case 4:p->in_sync_perminvent=(__typeof__(p->in_sync_perminvent))value;return;
default:abort();}}
case 18:{struct instance_globals_l*p=at;switch(field){
case 0:p->lastinvnr=(__typeof__(p->lastinvnr))value;return;
case 1:p->loot_reset_justpicked=(__typeof__(p->loot_reset_justpicked))value;return;
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:p->otg_temp=(__typeof__(p->otg_temp))value;return;
case 1:p->otg_otmp=(__typeof__(p->otg_otmp))value;return;
default:abort();}}
case 20:{struct instance_globals_p*p=at;switch(field){
case 0:p->perm_invent_toggling_direction=(__typeof__(p->perm_invent_toggling_direction))value;return;
default:abort();}}
case 21:{struct instance_globals_s*p=at;switch(field){
case 0:p->sortlootmode=(__typeof__(p->sortlootmode))value;return;
default:abort();}}
case 22:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 23:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:p->this_type=(__typeof__(p->this_type))value;return;
case 1:p->this_title=(__typeof__(p->this_title))value;return;
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 28:{struct mi*p=at;switch(field){
case 1:p->count=(__typeof__(p->count))value;return;
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:p->data=(__typeof__(p->data))value;return;
case 1:p->minvent=(__typeof__(p->minvent))value;return;
case 2:p->mw=(__typeof__(p->mw))value;return;
case 3:p->misc_worn_check=(__typeof__(p->misc_worn_check))value;return;
default:abort();}}
case 30:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
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
case 14:p->timed=(__typeof__(p->timed))value;return;
case 15:p->cursed=(unsigned int)value;return;
case 16:p->blessed=(unsigned int)value;return;
case 17:p->unpaid=(unsigned int)value;return;
case 18:p->no_charge=(unsigned int)value;return;
case 19:p->lamplit=(unsigned int)value;return;
case 20:p->known=(unsigned int)value;return;
case 21:p->dknown=(unsigned int)value;return;
case 22:p->bknown=(unsigned int)value;return;
case 23:p->rknown=(unsigned int)value;return;
case 24:p->cknown=(unsigned int)value;return;
case 25:p->lknown=(unsigned int)value;return;
case 26:p->nomerge=(unsigned int)value;return;
case 27:p->oeroded=(unsigned int)value;return;
case 28:p->oeroded2=(unsigned int)value;return;
case 29:p->oerodeproof=(unsigned int)value;return;
case 30:p->obroken=(unsigned int)value;return;
case 31:p->otrapped=(unsigned int)value;return;
case 32:p->globby=(unsigned int)value;return;
case 33:p->greased=(unsigned int)value;return;
case 34:p->in_use=(unsigned int)value;return;
case 35:p->bypass=(unsigned int)value;return;
case 36:p->pickup_prev=(unsigned int)value;return;
case 37:p->how_lost=(unsigned int)value;return;
case 38:p->corpsenm=(__typeof__(p->corpsenm))value;return;
case 39:p->usecount=(__typeof__(p->usecount))value;return;
case 40:p->oeaten=(__typeof__(p->oeaten))value;return;
case 41:p->age=(__typeof__(p->age))value;return;
case 42:p->owornmask=(__typeof__(p->owornmask))value;return;
case 43:p->oextra=(__typeof__(p->oextra))value;return;
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:p->oc_descr_idx=(__typeof__(p->oc_descr_idx))value;return;
case 1:p->oc_uname=(__typeof__(p->oc_uname))value;return;
case 2:p->oc_name_known=(unsigned int)value;return;
case 3:p->oc_merge=(unsigned int)value;return;
case 4:p->oc_uses_known=(unsigned int)value;return;
case 5:p->oc_material=(unsigned int)value;return;
case 6:p->oc_subtyp=(__typeof__(p->oc_subtyp))value;return;
default:abort();}}
case 33:{struct objdescr*p=at;switch(field){
case 0:p->oc_descr=(__typeof__(p->oc_descr))value;return;
default:abort();}}
case 34:{struct oextra*p=at;switch(field){
case 0:p->oname=(__typeof__(p->oname))value;return;
case 1:p->omonst=(__typeof__(p->omonst))value;return;
case 2:p->omailcmd=(__typeof__(p->omailcmd))value;return;
case 3:p->omid=(__typeof__(p->omid))value;return;
default:abort();}}
case 35:{struct permonst*p=at;switch(field){
case 0:p->mlet=(__typeof__(p->mlet))value;return;
case 1:p->mflags1=(__typeof__(p->mflags1))value;return;
default:abort();}}
case 36:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(__typeof__(p->extrinsic))value;return;
case 1:p->blocked=(__typeof__(p->blocked))value;return;
case 2:p->intrinsic=(__typeof__(p->intrinsic))value;return;
default:abort();}}
case 37:{struct rm*p=at;switch(field){
case 0:p->typ=(__typeof__(p->typ))value;return;
case 1:p->flags=(unsigned int)value;return;
default:abort();}}
case 38:{struct sinfo*p=at;switch(field){
case 0:p->something_worth_saving=(__typeof__(p->something_worth_saving))value;return;
case 1:p->in_moveloop=(__typeof__(p->in_moveloop))value;return;
case 2:p->beyond_savefile_load=(__typeof__(p->beyond_savefile_load))value;return;
default:abort();}}
case 39:{struct sortloot_item*p=at;switch(field){
case 0:p->obj=(__typeof__(p->obj))value;return;
case 1:p->str=(__typeof__(p->str))value;return;
case 2:p->indx=(__typeof__(p->indx))value;return;
case 3:p->orderclass=(__typeof__(p->orderclass))value;return;
case 4:p->subclass=(__typeof__(p->subclass))value;return;
case 5:p->disco=(__typeof__(p->disco))value;return;
case 6:p->inuse=(__typeof__(p->inuse))value;return;
default:abort();}}
case 40:{struct symdef*p=at;switch(field){
case 0:p->explanation=(__typeof__(p->explanation))value;return;
default:abort();}}
case 41:{struct tin_info*p=at;switch(field){
case 0:p->tin=(__typeof__(p->tin))value;return;
case 1:p->o_id=(__typeof__(p->o_id))value;return;
default:abort();}}
case 42:{struct to_core*p=at;switch(field){
case 0:p->tocore_flags=(__typeof__(p->tocore_flags))value;return;
case 1:p->maxslot=(__typeof__(p->maxslot))value;return;
case 2:p->needrows=(__typeof__(p->needrows))value;return;
case 3:p->needcols=(__typeof__(p->needcols))value;return;
case 4:p->haverows=(__typeof__(p->haverows))value;return;
case 5:p->havecols=(__typeof__(p->havecols))value;return;
default:abort();}}
case 43:{struct trap*p=at;switch(field){
case 0:p->ttyp=(unsigned int)value;return;
case 1:p->tseen=(unsigned int)value;return;
default:abort();}}
case 44:{struct u_conduct*p=at;switch(field){
case 0:p->literate=(__typeof__(p->literate))value;return;
default:abort();}}
case 45:{struct u_have*p=at;switch(field){
case 0:p->amulet=(unsigned int)value;return;
case 1:p->bell=(unsigned int)value;return;
case 2:p->book=(unsigned int)value;return;
case 3:p->menorah=(unsigned int)value;return;
case 4:p->questart=(unsigned int)value;return;
default:abort();}}
case 46:{struct u_roleplay*p=at;switch(field){
case 0:p->numrerolls=(__typeof__(p->numrerolls))value;return;
default:abort();}}
case 47:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(__typeof__(p->v_nexthere))value;return;
case 1:p->v_ocontainer=(__typeof__(p->v_ocontainer))value;return;
default:abort();}}
case 48:{struct win_request_info_t*p=at;switch(field){
default:abort();}}
case 49:{struct window_procs*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->wp_id=(__typeof__(p->wp_id))value;return;
case 2:p->wincap=(__typeof__(p->wincap))value;return;
case 3:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))value;return;
case 4:p->win_clear_nhwindow=(__typeof__(p->win_clear_nhwindow))value;return;
case 5:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 6:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))value;return;
case 7:p->win_putstr=(__typeof__(p->win_putstr))value;return;
case 8:p->win_start_menu=(__typeof__(p->win_start_menu))value;return;
case 9:p->win_end_menu=(__typeof__(p->win_end_menu))value;return;
case 10:p->win_message_menu=(__typeof__(p->win_message_menu))value;return;
case 11:p->win_wait_synch=(__typeof__(p->win_wait_synch))value;return;
case 12:p->win_putmsghistory=(__typeof__(p->win_putmsghistory))value;return;
case 13:p->win_update_inventory=(__typeof__(p->win_update_inventory))value;return;
case 14:p->win_ctrl_nhwindow=(__typeof__(p->win_ctrl_nhwindow))value;return;
default:abort();}}
case 50:{struct xprnctx*p=at;switch(field){
case 0:p->let=(__typeof__(p->let))value;return;
case 1:p->dot=(__typeof__(p->dot))value;return;
default:abort();}}
case 51:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 6:p->umonster=(__typeof__(p->umonster))value;return;
case 7:p->umonnum=(__typeof__(p->umonnum))value;return;
case 8:p->uswallow=(unsigned int)value;return;
case 9:p->uinwater=(unsigned int)value;return;
case 10:p->uundetected=(unsigned int)value;return;
case 11:p->uhandedness=(unsigned int)value;return;
case 15:p->ustuck=(__typeof__(p->ustuck))value;return;
case 16:p->twoweap=(__typeof__(p->twoweap))value;return;
default:abort();}}
default:abort();}}
void* teleport_invent_address(int kind,void*at,int field){switch(kind){
case 0:{struct Role*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 1:{struct _cmd_queue*p=at;switch(field){
case 0:return(void*)&p->typ;
case 1:return(void*)&p->key;
case 2:return(void*)&p->intval;
default:abort();}}
case 2:{struct achievement_tracking*p=at;switch(field){
case 0:return(void*)&p->mines_prize_oid;
case 1:return(void*)&p->soko_prize_oid;
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:return(void*)&p->a_obj;
case 1:return(void*)&p->a_int;
case 2:return(void*)&p->a_char;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_thats_enough_tries;
case 1:return(void*)&p->c_silly_thing_to;
case 2:return(void*)&p->c_Never_mind;
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:return(void*)&p->sym;
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroobj;
case 1:return(void*)&p->zeroany;
default:abort();}}
case 7:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->mon_moving;
case 1:return(void*)&p->tin;
case 2:return(void*)&p->achieveo;
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 9:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_water_level;
case 1:return(void*)&p->d_air_level;
default:abort();}}
case 10:{struct display_hints*p=at;switch(field){
case 0:return(void*)&p->botl;
default:abort();}}
case 11:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->objlist;
case 3:return(void*)&p->buriedobjlist;
default:abort();}}
case 12:{struct flag*p=at;switch(field){
case 0:return(void*)&p->autoquiver;
case 1:return(void*)&p->debug;
case 2:return(void*)&p->goldX;
case 3:return(void*)&p->invlet_constant;
case 4:return(void*)&p->mention_decor;
case 5:return(void*)&p->pickup_thrown;
case 6:return(void*)&p->sortpack;
case 7:return(void*)&p->verbose;
case 8:return(void*)&p->pickup_burden;
case 9:return(void*)&p->pile_limit;
case 10:return(void*)&p->sortloot;
case 11:return(void*)&p->inv_order;
case 12:return(void*)&p->menu_style;
case 13:return(void*)&p->lootabc;
default:abort();}}
case 13:{struct from_core*p=at;switch(field){
case 0:return(void*)&p->invmode;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
case 1:return(void*)&p->override_ID;
case 2:return(void*)&p->suppress_price;
case 3:return(void*)&p->force_invmenu;
case 4:return(void*)&p->menu_head_objsym;
case 5:return(void*)&p->menu_requested;
case 6:return(void*)&p->menu_tab_sep;
case 7:return(void*)&p->perm_invent;
case 8:return(void*)&p->perm_invent_pending;
case 9:return(void*)&p->prev_decor;
case 10:return(void*)&p->perminv_mode;
default:abort();}}
case 15:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->cached_pickinv_win;
case 1:return(void*)&p->core_invent_state;
default:abort();}}
case 16:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->distantname;
default:abort();}}
case 17:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_doagain;
case 1:return(void*)&p->invent;
case 2:return(void*)&p->invbuf;
case 3:return(void*)&p->invbufsiz;
case 4:return(void*)&p->in_sync_perminvent;
default:abort();}}
case 18:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->lastinvnr;
case 1:return(void*)&p->loot_reset_justpicked;
default:abort();}}
case 19:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->otg_temp;
case 1:return(void*)&p->otg_otmp;
case 2:return(void*)&p->only;
default:abort();}}
case 20:{struct instance_globals_p*p=at;switch(field){
case 0:return(void*)&p->perm_invent_toggling_direction;
default:abort();}}
case 21:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->sortlootmode;
default:abort();}}
case 22:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 23:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
default:abort();}}
case 24:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 25:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->this_type;
case 1:return(void*)&p->this_title;
default:abort();}}
case 26:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
default:abort();}}
case 27:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 28:{struct mi*p=at;switch(field){
case 0:return(void*)&p->item;
case 1:return(void*)&p->count;
default:abort();}}
case 29:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 1:return(void*)&p->minvent;
case 2:return(void*)&p->mw;
case 3:return(void*)&p->misc_worn_check;
default:abort();}}
case 30:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 31:{struct obj*p=at;switch(field){
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
case 14:return(void*)&p->timed;
case 38:return(void*)&p->corpsenm;
case 39:return(void*)&p->usecount;
case 40:return(void*)&p->oeaten;
case 41:return(void*)&p->age;
case 42:return(void*)&p->owornmask;
case 43:return(void*)&p->oextra;
default:abort();}}
case 32:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_descr_idx;
case 1:return(void*)&p->oc_uname;
case 6:return(void*)&p->oc_subtyp;
default:abort();}}
case 33:{struct objdescr*p=at;switch(field){
case 0:return(void*)&p->oc_descr;
default:abort();}}
case 34:{struct oextra*p=at;switch(field){
case 0:return(void*)&p->oname;
case 1:return(void*)&p->omonst;
case 2:return(void*)&p->omailcmd;
case 3:return(void*)&p->omid;
default:abort();}}
case 35:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->mlet;
case 1:return(void*)&p->mflags1;
default:abort();}}
case 36:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 37:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
default:abort();}}
case 38:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->something_worth_saving;
case 1:return(void*)&p->in_moveloop;
case 2:return(void*)&p->beyond_savefile_load;
default:abort();}}
case 39:{struct sortloot_item*p=at;switch(field){
case 0:return(void*)&p->obj;
case 1:return(void*)&p->str;
case 2:return(void*)&p->indx;
case 3:return(void*)&p->orderclass;
case 4:return(void*)&p->subclass;
case 5:return(void*)&p->disco;
case 6:return(void*)&p->inuse;
default:abort();}}
case 40:{struct symdef*p=at;switch(field){
case 0:return(void*)&p->explanation;
default:abort();}}
case 41:{struct tin_info*p=at;switch(field){
case 0:return(void*)&p->tin;
case 1:return(void*)&p->o_id;
default:abort();}}
case 42:{struct to_core*p=at;switch(field){
case 0:return(void*)&p->tocore_flags;
case 1:return(void*)&p->maxslot;
case 2:return(void*)&p->needrows;
case 3:return(void*)&p->needcols;
case 4:return(void*)&p->haverows;
case 5:return(void*)&p->havecols;
default:abort();}}
case 43:{struct trap*p=at;switch(field){
default:abort();}}
case 44:{struct u_conduct*p=at;switch(field){
case 0:return(void*)&p->literate;
default:abort();}}
case 45:{struct u_have*p=at;switch(field){
default:abort();}}
case 46:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->numrerolls;
default:abort();}}
case 47:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
case 1:return(void*)&p->v_ocontainer;
default:abort();}}
case 48:{struct win_request_info_t*p=at;switch(field){
case 0:return(void*)&p->tocore;
case 1:return(void*)&p->fromcore;
default:abort();}}
case 49:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->wp_id;
case 2:return(void*)&p->wincap;
case 3:return(void*)&p->win_create_nhwindow;
case 4:return(void*)&p->win_clear_nhwindow;
case 5:return(void*)&p->win_display_nhwindow;
case 6:return(void*)&p->win_destroy_nhwindow;
case 7:return(void*)&p->win_putstr;
case 8:return(void*)&p->win_start_menu;
case 9:return(void*)&p->win_end_menu;
case 10:return(void*)&p->win_message_menu;
case 11:return(void*)&p->win_wait_synch;
case 12:return(void*)&p->win_putmsghistory;
case 13:return(void*)&p->win_update_inventory;
case 14:return(void*)&p->win_ctrl_nhwindow;
default:abort();}}
case 50:{struct xprnctx*p=at;switch(field){
case 0:return(void*)&p->let;
case 1:return(void*)&p->dot;
default:abort();}}
case 51:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->uz;
case 3:return(void*)&p->urooms;
case 4:return(void*)&p->ushops;
case 5:return(void*)&p->uprops;
case 6:return(void*)&p->umonster;
case 7:return(void*)&p->umonnum;
case 12:return(void*)&p->uhave;
case 13:return(void*)&p->uconduct;
case 14:return(void*)&p->uroleplay;
case 15:return(void*)&p->ustuck;
case 16:return(void*)&p->twoweap;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_invent_var0(char * a0,long a1){(impossible)(a0,a1);}
void teleport_invent_var1(char * a0){(pline)(a0);}
void teleport_invent_var2(char * a0){(impossible)(a0);}
void teleport_invent_var3(char * a0){(impossible)(a0);}
void teleport_invent_var4(char * a0){(impossible)(a0);}
void teleport_invent_var5(char * a0){(impossible)(a0);}
void teleport_invent_var6(char * a0){(impossible)(a0);}
void teleport_invent_var7(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var8(long a0,char * a1){(livelog_printf)(a0,a1);}
void teleport_invent_var9(char * a0){(panic)(a0);}
void teleport_invent_var10(char * a0,int a1){(panic)(a0,a1);}
void teleport_invent_var11(char * a0,int a1){(panic)(a0,a1);}
void teleport_invent_var12(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var13(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var14(char * a0){(impossible)(a0);}
void teleport_invent_var15(char * a0){(impossible)(a0);}
void teleport_invent_var16(char * a0){(impossible)(a0);}
void teleport_invent_var17(char * a0){(impossible)(a0);}
void teleport_invent_var18(char * a0){(impossible)(a0);}
void teleport_invent_var19(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){(You)(a0,a1,a2,a3,a4,a5);}
int teleport_invent_var20(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var21(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var22(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_invent_var23(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var24(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var25(char * a0){(impossible)(a0);}
void teleport_invent_var26(char * a0){(impossible)(a0);}
void teleport_invent_var27(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
int teleport_invent_var28(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var29(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var30(char * a0){(pline)(a0);}
void teleport_invent_var31(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var32(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_invent_var33(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var34(char * a0,char * a1){(You)(a0,a1);}
void teleport_invent_var35(char * a0){(pline_The)(a0);}
void teleport_invent_var36(char * a0,long a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_invent_var37(char * a0,char * a1){(You)(a0,a1);}
void teleport_invent_var38(char * a0){(You)(a0);}
void teleport_invent_var39(char * a0,long a1){(You)(a0,a1);}
void teleport_invent_var40(char * a0){(pline_The)(a0);}
void teleport_invent_var41(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var42(char * a0,char * a1){(You)(a0,a1);}
int teleport_invent_var43(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_invent_var44(char * a0){(pline)(a0);}
void teleport_invent_var45(char * a0){(You)(a0);}
void teleport_invent_var46(char * a0){(You)(a0);}
void teleport_invent_var47(char * a0){(You)(a0);}
void teleport_invent_var48(char * a0){(You)(a0);}
void teleport_invent_var49(char * a0,int a1){(You)(a0,a1);}
int teleport_invent_var50(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var51(char * a0){(pline)(a0);}
void teleport_invent_var52(char * a0){(pline)(a0);}
int teleport_invent_var53(char * a0,char * a1,char * a2,int a3,int a4,int a5,int a6,int a7){return (sprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
int teleport_invent_var54(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var55(char * a0){(pline)(a0);}
void teleport_invent_var56(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var57(char * a0){(pline)(a0);}
void teleport_invent_var58(char * a0,char * a1){(You)(a0,a1);}
void teleport_invent_var59(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var60(char * a0){(pline)(a0);}
void teleport_invent_var61(char * a0){(pline)(a0);}
void teleport_invent_var62(char * a0,int a1,char * a2,unsigned long a3,char * a4,long a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_invent_var63(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
int teleport_invent_var64(char * a0,char * a1,int a2,long a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_invent_var65(char * a0,char * a1,int a2,int a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_invent_var66(char * a0,char * a1){(pline)(a0,a1);}
int teleport_invent_var67(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_invent_var68(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var69(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var70(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var71(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_invent_var72(char * a0,char * a1){(pline)(a0,a1);}
int teleport_invent_var73(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var74(char * a0,char * a1,int a2,char * a3){(You)(a0,a1,a2,a3);}
int teleport_invent_var75(char * a0,char * a1,char * a2,int a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_invent_var76(char * a0){(You)(a0);}
void teleport_invent_var77(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var78(char * a0){(You)(a0);}
void teleport_invent_var79(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
int teleport_invent_var80(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var81(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_invent_var82(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_invent_var83(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_invent_var84(char * a0,char * a1){(You)(a0,a1);}
int teleport_invent_var85(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var86(char * a0,char * a1,char * a2,char * a3){(There)(a0,a1,a2,a3);}
void teleport_invent_var87(char * a0){(You)(a0);}
void teleport_invent_var88(char * a0){(You)(a0);}
void teleport_invent_var89(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_invent_var90(char * a0){(pline)(a0);}
int teleport_invent_var91(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_invent_var92(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var93(char * a0,char * a1){(You)(a0,a1);}
void teleport_invent_var94(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var95(char * a0,char * a1){(There)(a0,a1);}
void teleport_invent_var96(char * a0,char * a1,char * a2){(There)(a0,a1,a2);}
void teleport_invent_var97(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_invent_var98(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var99(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
int teleport_invent_var100(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_invent_var101(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var102(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_invent_var103(char * a0,char * a1){(pline)(a0,a1);}
int teleport_invent_var104(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var105(char * a0,char * a1,long a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_invent_var106(char * a0,char * a1,char * a2,long a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_invent_var107(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var108(char * a0,long a1,char * a2){(You)(a0,a1,a2);}
void teleport_invent_var109(char * a0){(You)(a0);}
void teleport_invent_var110(char * a0,char * a1){(You)(a0,a1);}
void teleport_invent_var111(char * a0){(You)(a0);}
void teleport_invent_var112(char * a0,char * a1){(You)(a0,a1);}
void teleport_invent_var113(char * a0){(You)(a0);}
void teleport_invent_var114(char * a0){(You)(a0);}
void teleport_invent_var115(char * a0){(You)(a0);}
void teleport_invent_var116(char * a0){(You)(a0);}
int teleport_invent_var117(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var118(char * a0,char * a1,char * a2,char * a3,char * a4){(impossible)(a0,a1,a2,a3,a4);}
void teleport_invent_var119(char * a0,char * a1){(You)(a0,a1);}
void teleport_invent_var120(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var121(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var122(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var123(char * a0,char * a1,long a2){(pline)(a0,a1,a2);}
int teleport_invent_var124(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var125(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_invent_var126(char * a0,int a1){(pline)(a0,a1);}
void teleport_invent_var127(char * a0){(pline)(a0);}
void teleport_invent_var128(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var129(char * a0){(Your)(a0);}
int teleport_invent_var130(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_invent_var131(char * a0,char * a1,char * a2,char * a3){(There)(a0,a1,a2,a3);}
int teleport_invent_var132(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_invent_var133(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_invent_var134(char * a0,char * a1){(pline)(a0,a1);}
void teleport_invent_var135(char * a0,char * a1,int a2,int a3,int a4,int a5){(pline)(a0,a1,a2,a3,a4,a5);}
boolean teleport_invent_cb0(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_invent_cb1(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_invent_cb2(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_invent_cb3(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_invent_cb4(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
void teleport_invent_cb5(void (*fn)(const char *, boolean),const char * a0,boolean a1){fn(a0,a1);}
int teleport_invent_cb6(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_invent_cb7(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
boolean teleport_invent_cb8(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_invent_cb9(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_invent_cb10(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
winid teleport_invent_cb11(winid (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb12(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
int teleport_invent_cb13(int (*fn)(int),int a0){return fn(a0);}
int teleport_invent_cb14(int (*fn)(int),int a0){return fn(a0);}
int teleport_invent_cb15(int (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb16(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_invent_cb17(void (*fn)(winid),winid a0){fn(a0);}
void teleport_invent_cb18(void (*fn)(void)){fn();}
void teleport_invent_cb19(void (*fn)(int),int a0){fn(a0);}
void teleport_invent_cb20(void (*fn)(int),int a0){fn(a0);}
void teleport_invent_cb21(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_invent_cb22(winid (*fn)(int),int a0){return fn(a0);}
char teleport_invent_cb23(char (*fn)(char, int, const char *),char a0,int a1,const char * a2){return fn(a0,a1,a2);}
char teleport_invent_cb24(char (*fn)(char, int, const char *),char a0,int a1,const char * a2){return fn(a0,a1,a2);}
void teleport_invent_cb25(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
int teleport_invent_cb26(int (*fn)(int),int a0){return fn(a0);}
int teleport_invent_cb27(int (*fn)(int),int a0){return fn(a0);}
int teleport_invent_cb28(int (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb29(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
winid teleport_invent_cb30(winid (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb31(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
int teleport_invent_cb32(int (*fn)(int),int a0){return fn(a0);}
int teleport_invent_cb33(int (*fn)(int),int a0){return fn(a0);}
int teleport_invent_cb34(int (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb35(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_invent_cb36(void (*fn)(winid),winid a0){fn(a0);}
boolean teleport_invent_cb37(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
winid teleport_invent_cb38(winid (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb39(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb40(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb41(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb42(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb43(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb44(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb45(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb46(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb47(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb48(void (*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
void teleport_invent_cb49(void (*fn)(winid),winid a0){fn(a0);}
void teleport_invent_cb50(void (*fn)(winid),winid a0){fn(a0);}
void teleport_invent_cb51(void (*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
winid teleport_invent_cb52(winid (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb53(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb54(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb55(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb56(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb57(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_invent_cb58(void (*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
void teleport_invent_cb59(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_invent_cb60(winid (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb61(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_invent_cb62(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_invent_cb63(void (*fn)(winid),winid a0){fn(a0);}
win_request_info * teleport_invent_cb64(win_request_info *(*fn)(winid, int, win_request_info *),winid a0,int a1,win_request_info * a2){return fn(a0,a1,a2);}
win_request_info * teleport_invent_cb65(win_request_info *(*fn)(winid, int, win_request_info *),winid a0,int a1,win_request_info * a2){return fn(a0,a1,a2);}
void teleport_invent_cb66(void (*fn)(winid),winid a0){fn(a0);}
void teleport_invent_cb67(void (*fn)(void)){fn();}
winid teleport_invent_cb68(winid (*fn)(int),int a0){return fn(a0);}
void teleport_invent_cb69(void (*fn)(winid),winid a0){fn(a0);}
#pragma clang diagnostic pop
static char invent_literals[5403];
char*teleport_invent_literal_storage(void){return invent_literals;}
size_t teleport_invent_literal_capacity(void){return sizeof invent_literals;}
static struct win_request_info_t invent_backing_0;
static int invent_backing_1;
static signed char invent_backing_2;
static char invent_backing_3[2];
static char * invent_backing_4[5];
static char invent_backing_5[18];
static char invent_backing_6[8];
static struct sortloot_item invent_backing_7;
static char * invent_backing_8[21];
static char invent_backing_9[29];
static struct xprnctx invent_backing_10;
static char invent_backing_11[6];
static char invent_backing_12[256];
static char invent_backing_13[22];
static char invent_backing_14[20];
static char invent_backing_15[19];
static char invent_backing_16[49];
static char invent_backing_17[256];
static char * invent_backing_18[18];
static char invent_backing_19[2];
static char * invent_backing_20[1];
static char invent_backing_21[43];
static struct win_request_info_t * invent_backing_22;
void*teleport_invent_storage(int i){switch(i){
case 0:return &invent_backing_0;
case 1:return &invent_backing_1;
case 2:return &invent_backing_2;
case 3:return &invent_backing_3;
case 4:return &invent_backing_4;
case 5:return &invent_backing_5;
case 6:return &invent_backing_6;
case 7:return &invent_backing_7;
case 8:return &invent_backing_8;
case 9:return &invent_backing_9;
case 10:return &invent_backing_10;
case 11:return &invent_backing_11;
case 12:return &invent_backing_12;
case 13:return &invent_backing_13;
case 14:return &invent_backing_14;
case 15:return &invent_backing_15;
case 16:return &invent_backing_16;
case 17:return &invent_backing_17;
case 18:return &invent_backing_18;
case 19:return &invent_backing_19;
case 20:return &invent_backing_20;
case 21:return &invent_backing_21;
case 22:return &invent_backing_22;
default:abort();}}
extern int teleport_invent_adjust_gold_ok(struct obj * a0);
extern int teleport_invent_adjust_ok(struct obj * a0);
extern char * teleport_invent_cinv_ansimpleoname(struct obj * a0);
extern char * teleport_invent_cinv_doname(struct obj * a0);
extern int teleport_invent_ckunpaid(struct obj * a0);
extern int teleport_invent_ckvalidcat(struct obj * a0);
extern boolean teleport_invent_only_here(struct obj * a0);
extern char * teleport_invent_safeq_shortxprname(struct obj * a0);
extern char * teleport_invent_safeq_xprname(struct obj * a0);
extern int teleport_invent_sortloot_cmp(const void * a0,const void * a1);
extern boolean teleport_invent_this_type_only(struct obj * a0);
extern boolean teleport_invent_worn_wield_only(struct obj * a0);
void*teleport_invent_function(int i){switch(i){
case 0:return(void*)teleport_invent_adjust_gold_ok;
case 1:return(void*)teleport_invent_adjust_ok;
case 2:return(void*)allow_all;
case 3:return(void*)ansimpleoname;
case 4:return(void*)teleport_invent_cinv_ansimpleoname;
case 5:return(void*)teleport_invent_cinv_doname;
case 6:return(void*)teleport_invent_ckunpaid;
case 7:return(void*)teleport_invent_ckvalidcat;
case 8:return(void*)doname;
case 9:return(void*)identify;
case 10:return(void*)is_inuse;
case 11:return(void*)is_worn;
case 12:return(void*)not_fully_identified;
case 13:return(void*)teleport_invent_only_here;
case 14:return(void*)rn2_on_display_rng;
case 15:return(void*)teleport_invent_safeq_shortxprname;
case 16:return(void*)teleport_invent_safeq_xprname;
case 17:return(void*)teleport_invent_sortloot_cmp;
case 18:return(void*)teleport_invent_this_type_only;
case 19:return(void*)teleport_invent_worn_wield_only;
default:abort();}}
#ifdef TELEPORT_INVENT_VALIDATE_ORIGINAL
_Static_assert(sizeof wri_info==sizeof invent_backing_0,"INVENT private backing size");
_Static_assert(sizeof perminv_flags==sizeof invent_backing_1,"INVENT private backing size");
_Static_assert(sizeof in_perm_invent_toggled==sizeof invent_backing_2,"INVENT private backing size");
_Static_assert(sizeof venom_inv==sizeof invent_backing_3,"INVENT private backing size");
_Static_assert(sizeof inuse_headers==sizeof invent_backing_4,"INVENT private backing size");
_Static_assert(sizeof currencies==sizeof invent_backing_8,"INVENT private backing size");
_Static_assert(sizeof safeq_xprn_ctx==sizeof invent_backing_10,"INVENT private backing size");
_Static_assert(sizeof removeables==sizeof invent_backing_11,"INVENT private backing size");
_Static_assert(sizeof names==sizeof invent_backing_18,"INVENT private backing size");
_Static_assert(sizeof oth_symbols==sizeof invent_backing_19,"INVENT private backing size");
_Static_assert(sizeof oth_names==sizeof invent_backing_20,"INVENT private backing size");
_Static_assert(sizeof(Loot)==24&&sizeof(win_request_info)==48,"INVENT actual Loot/WRI stride");
#endif
