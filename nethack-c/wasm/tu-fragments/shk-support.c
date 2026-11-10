/* SHK typed field/header/dependency/zero storage only. */
#include "../../../scripts/tu-shk-layout.h"
#include "shk-types.h"
#include <stdlib.h>
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(size_t)==8,"Review SHK LP64");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0&&sizeof(int8)==1&&(int8)-1<0&&sizeof(coordxy)==2&&(char)-1<0,"Review SHK scalar widths");
void*teleport_shk_global(int index){switch(index){
case 0:return(void*)&gi;
case 1:return(void*)&disp;
case 2:return(void*)&svr;
case 3:return(void*)&u;
case 4:return(void*)&svl;
case 5:return(void*)&svp;
case 6:return(void*)&gt;
case 7:return(void*)&gk;
case 8:return(void*)&gm;
case 9:return(void*)&gb;
case 10:return(void*)&objects;
case 11:return(void*)&svm;
case 12:return(void*)&flags;
case 13:return(void*)&shtypes;
case 14:return(void*)&gu;
case 15:return(void*)&genders;
case 16:return(void*)&cg;
case 17:return(void*)&windowprocs;
case 18:return(void*)&nul_glyphinfo;
case 19:return(void*)&gv;
case 20:return(void*)&iflags;
case 21:return(void*)&ynchars;
case 22:return(void*)&gr;
case 23:return(void*)&uball;
case 24:return(void*)&uchain;
case 25:return(void*)&ubirthday;
case 26:return(void*)&uarmh;
case 27:return(void*)&uarmu;
case 28:return(void*)&uarm;
case 29:return(void*)&uarmc;
case 30:return(void*)&gy;
case 31:return(void*)&gs;
case 32:return(void*)&ga;
case 33:return(void*)&ynaqchars;
case 34:return(void*)&mons;
case 35:return(void*)&gf;
case 36:return(void*)&program_state;
case 37:return(void*)&uswapwep;
case 38:return(void*)&gc;
case 39:return(void*)&c_common_strings;
default:abort();}}
uint64_t teleport_shk_layout(int index){switch(index){
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
case 10:return(uint64_t)(sizeof(struct bill_x));
case 11:return(uint64_t)(sizeof(struct c_common_strings));
case 12:return(uint64_t)(sizeof(struct const_globals));
case 13:return(uint64_t)(sizeof(struct d_level));
case 14:return(uint64_t)(sizeof(struct damage));
case 15:return(uint64_t)(sizeof(struct display_hints));
case 16:return(uint64_t)(sizeof(struct eshk));
case 17:return(uint64_t)(sizeof(struct flag));
case 18:return(uint64_t)(sizeof(struct instance_flags));
case 19:return(uint64_t)(sizeof(struct instance_globals_a));
case 20:return(uint64_t)(sizeof(struct instance_globals_b));
case 21:return(uint64_t)(sizeof(struct instance_globals_c));
case 22:return(uint64_t)(sizeof(struct instance_globals_f));
case 23:return(uint64_t)(sizeof(struct instance_globals_i));
case 24:return(uint64_t)(sizeof(struct instance_globals_k));
case 25:return(uint64_t)(sizeof(struct instance_globals_m));
case 26:return(uint64_t)(sizeof(struct instance_globals_r));
case 27:return(uint64_t)(sizeof(struct instance_globals_s));
case 28:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 29:return(uint64_t)(sizeof(struct instance_globals_saved_m));
case 30:return(uint64_t)(sizeof(struct instance_globals_saved_p));
case 31:return(uint64_t)(sizeof(struct instance_globals_saved_r));
case 32:return(uint64_t)(sizeof(struct instance_globals_t));
case 33:return(uint64_t)(sizeof(struct instance_globals_u));
case 34:return(uint64_t)(sizeof(struct instance_globals_v));
case 35:return(uint64_t)(sizeof(struct instance_globals_y));
case 36:return(uint64_t)(sizeof(struct levelflags));
case 37:return(uint64_t)(sizeof(struct mextra));
case 38:return(uint64_t)(sizeof(struct mi));
case 39:return(uint64_t)(sizeof(struct mkroom));
case 40:return(uint64_t)(sizeof(struct monst));
case 41:return(uint64_t)(sizeof(struct mvitals));
case 42:return(uint64_t)(sizeof(struct nhcoord));
case 43:return(uint64_t)(sizeof(struct obj));
case 44:return(uint64_t)(sizeof(struct objclass));
case 45:return(uint64_t)(sizeof(struct oextra));
case 46:return(uint64_t)(sizeof(struct permonst));
case 47:return(uint64_t)(sizeof(struct prop));
case 48:return(uint64_t)(sizeof(struct repo));
case 49:return(uint64_t)(sizeof(struct rm));
case 50:return(uint64_t)(sizeof(struct shclass));
case 51:return(uint64_t)(sizeof(struct shk_icost));
case 52:return(uint64_t)(sizeof(struct sinfo));
case 53:return(uint64_t)(sizeof(struct sortbill_item));
case 54:return(uint64_t)(sizeof(struct trap));
case 55:return(uint64_t)(sizeof(struct u_event));
case 56:return(uint64_t)(sizeof(struct u_roleplay));
case 57:return(uint64_t)(sizeof(struct window_procs));
case 58:return(uint64_t)(sizeof(struct you));
case 59:return(uint64_t)(sizeof(union any));
case 60:return(uint64_t)(sizeof(union vptrs));
case 61:return(uint64_t)(ACH_SHOP);
case 62:return(uint64_t)(ACID_RES);
case 63:return(uint64_t)(AGATE);
case 64:return(uint64_t)(AMBER);
case 65:return(uint64_t)(AMETHYST);
case 66:return(uint64_t)(AMULET_CLASS);
case 67:return(uint64_t)(AQUAMARINE);
case 68:return(uint64_t)(ARM);
case 69:return(uint64_t)(ARMOR_CLASS);
case 70:return(uint64_t)(A_CHA);
case 71:return(uint64_t)(A_WIS);
case 72:return(uint64_t)(BAG_OF_TRICKS);
case 73:return(uint64_t)(BALL_CLASS);
case 74:return(uint64_t)(BEARTRAP);
case 75:return(uint64_t)(BEAR_TRAP);
case 76:return(uint64_t)(BLACK_OPAL);
case 77:return(uint64_t)(BLINDED);
case 78:return(uint64_t)(BOULDER);
case 79:return(uint64_t)(BRASS_LANTERN);
case 80:return(uint64_t)(CANDELABRUM_OF_INVOCATION);
case 81:return(uint64_t)(CANDLESHOP);
case 82:return(uint64_t)(CAN_OF_GREASE);
case 83:return(uint64_t)(CHAIN_CLASS);
case 84:return(uint64_t)(CHRYSOBERYL);
case 85:return(uint64_t)(CITRINE);
case 86:return(uint64_t)(COIN_CLASS);
case 87:return(uint64_t)(COLD_RES);
case 88:return(uint64_t)(CONFLICT);
case 89:return(uint64_t)(CORPSE);
case 90:return(uint64_t)(COST_CONTENTS);
case 91:return(uint64_t)(COST_SINGLEOBJ);
case 92:return(uint64_t)(CRYSTAL_BALL);
case 93:return(uint64_t)(DBWALL);
case 94:return(uint64_t)(DEAF);
case 95:return(uint64_t)(DETECT_MONSTERS);
case 96:return(uint64_t)(DIAMOND);
case 97:return(uint64_t)(DISINT_RES);
case 98:return(uint64_t)(DISPLACED);
case 99:return(uint64_t)(DOOR);
case 100:return(uint64_t)(DRUM_OF_EARTHQUAKE);
case 101:return(uint64_t)(DUNCE_CAP);
case 102:return(uint64_t)(DWARVISH_MATTOCK);
case 103:return(uint64_t)(EGG);
case 104:return(uint64_t)(EMERALD);
case 105:return(uint64_t)(EXPENSIVE_CAMERA);
case 106:return(uint64_t)(EYE);
case 107:return(uint64_t)(FAST);
case 108:return(uint64_t)(FIRE_RES);
case 109:return(uint64_t)(FIRST_GLASS_GEM);
case 110:return(uint64_t)(FIRST_REAL_GEM);
case 111:return(uint64_t)(FLUORITE);
case 112:return(uint64_t)(FOOD_CLASS);
case 113:return(uint64_t)(FullyIntact);
case 114:return(uint64_t)(FullyUsedUp);
case 115:return(uint64_t)(GEMSTONE);
case 116:return(uint64_t)(GEM_CLASS);
case 117:return(uint64_t)(GLASS);
case 118:return(uint64_t)(GOLD_SYM);
case 119:return(uint64_t)(HAND);
case 120:return(uint64_t)(HEAD);
case 121:return(uint64_t)(HOLE);
case 122:return(uint64_t)(HORN_OF_PLENTY);
case 123:return(uint64_t)(HUNGRY);
case 124:return(uint64_t)(INVIS);
case 125:return(uint64_t)(JACINTH);
case 126:return(uint64_t)(JADE);
case 127:return(uint64_t)(JASPER);
case 128:return(uint64_t)(JET);
case 129:return(uint64_t)(KnownContainer);
case 130:return(uint64_t)(LANDMINE);
case 131:return(uint64_t)(LAND_MINE);
case 132:return(uint64_t)(LARGE_BOX);
case 133:return(uint64_t)(LEASH);
case 134:return(uint64_t)(LOW_PM);
case 135:return(uint64_t)(MAGIC_FLUTE);
case 136:return(uint64_t)(MAGIC_LAMP);
case 137:return(uint64_t)(MAGIC_MARKER);
case 138:return(uint64_t)(MIRROR);
case 139:return(uint64_t)(MS_ANIMAL);
case 140:return(uint64_t)(MS_HUMANOID);
case 141:return(uint64_t)(MS_SILENT);
case 142:return(uint64_t)(M_AP_MONSTER);
case 143:return(uint64_t)(M_AP_NOTHING);
case 144:return(uint64_t)(NECK);
case 145:return(uint64_t)(NUMMONS);
case 146:return(uint64_t)(OIL_LAMP);
case 147:return(uint64_t)(OPAL);
case 148:return(uint64_t)(PASSES_WALLS);
case 149:return(uint64_t)(PICK_AXE);
case 150:return(uint64_t)(PIT);
case 151:return(uint64_t)(PM_ELF);
case 152:return(uint64_t)(PM_GRID_BUG);
case 153:return(uint64_t)(PM_KEYSTONE_KOP);
case 154:return(uint64_t)(PM_KNIGHT);
case 155:return(uint64_t)(PM_KOP_KAPTAIN);
case 156:return(uint64_t)(PM_KOP_LIEUTENANT);
case 157:return(uint64_t)(PM_KOP_SERGEANT);
case 158:return(uint64_t)(PM_ROGUE);
case 159:return(uint64_t)(PM_TOURIST);
case 160:return(uint64_t)(POISON_RES);
case 161:return(uint64_t)(POOL);
case 162:return(uint64_t)(POTION_CLASS);
case 163:return(uint64_t)(POT_OIL);
case 164:return(uint64_t)(POT_WATER);
case 165:return(uint64_t)(P_PICK_AXE);
case 166:return(uint64_t)(PartlyIntact);
case 167:return(uint64_t)(PartlyUsedUp);
case 168:return(uint64_t)(RING_CLASS);
case 169:return(uint64_t)(ROCK);
case 170:return(uint64_t)(ROOM);
case 171:return(uint64_t)(RUBY);
case 172:return(uint64_t)(SAPPHIRE);
case 173:return(uint64_t)(SCROLL_CLASS);
case 174:return(uint64_t)(SHOCK_RES);
case 175:return(uint64_t)(SHOPBASE);
case 176:return(uint64_t)(SLEEP_RES);
case 177:return(uint64_t)(SPBOOK_CLASS);
case 178:return(uint64_t)(SPIKED_PIT);
case 179:return(uint64_t)(STONE_RES);
case 180:return(uint64_t)(STRANGE_OBJECT);
case 181:return(uint64_t)(S_KOP);
case 182:return(uint64_t)(S_VAMPIRE);
case 183:return(uint64_t)(TALLOW_CANDLE);
case 184:return(uint64_t)(TELEPAT);
case 185:return(uint64_t)(TELEPORT);
case 186:return(uint64_t)(TELEPORT_CONTROL);
case 187:return(uint64_t)(TIN);
case 188:return(uint64_t)(TINNING_KIT);
case 189:return(uint64_t)(TOOL_CLASS);
case 190:return(uint64_t)(TOPAZ);
case 191:return(uint64_t)(TT_PIT);
case 192:return(uint64_t)(UndisclosedContainer);
case 193:return(uint64_t)(WAND_CLASS);
case 194:return(uint64_t)(WAX_CANDLE);
case 195:return(uint64_t)(WEAPON_CLASS);
case 196:return(uint64_t)(invlet_basic);
default:abort();}}
uint64_t teleport_shk_read(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->he);
case 1:return(uint64_t)(uintptr_t)(p->him);
case 2:return(uint64_t)(uintptr_t)(p->his);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 4:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_int);
default:abort();}}
case 5:{struct bill_x*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->bo_id);
case 1:return(uint64_t)(uintptr_t)(p->useup);
case 2:return(uint64_t)(uintptr_t)(p->price);
case 3:return(uint64_t)(uintptr_t)(p->bquan);
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->c_the_your);
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 9:{struct damage*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->next);
case 1:return(uint64_t)(uintptr_t)(p->when);
case 2:return(uint64_t)(uintptr_t)(p->cost);
case 3:return(uint64_t)(uintptr_t)(&p->place);
case 4:return(uint64_t)(uintptr_t)(p->typ);
case 5:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 10:{struct display_hints*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 11:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(p->objlist);
case 4:return(uint64_t)(uintptr_t)(p->buriedobjlist);
case 5:return(uint64_t)(uintptr_t)(p->monlist);
case 6:return(uint64_t)(uintptr_t)(p->damagelist);
case 7:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 12:{struct eshk*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->robbed);
case 1:return(uint64_t)(uintptr_t)(p->credit);
case 2:return(uint64_t)(uintptr_t)(p->debit);
case 3:return(uint64_t)(uintptr_t)(p->loan);
case 4:return(uint64_t)(uintptr_t)(p->shoptype);
case 5:return(uint64_t)(uintptr_t)(p->shoproom);
case 6:return(uint64_t)(uintptr_t)(p->following);
case 7:return(uint64_t)(uintptr_t)(p->surcharge);
case 8:return(uint64_t)(uintptr_t)(p->dismiss_kops);
case 9:return(uint64_t)(uintptr_t)(&p->shk);
case 10:return(uint64_t)(uintptr_t)(&p->shd);
case 11:return(uint64_t)(uintptr_t)(&p->shoplevel);
case 12:return(uint64_t)(uintptr_t)(p->billct);
case 13:return(uint64_t)(uintptr_t)(&p->bill);
case 14:return(uint64_t)(uintptr_t)(p->bill_p);
case 15:return(uint64_t)(uintptr_t)(p->visitct);
case 16:return(uint64_t)(uintptr_t)(&p->customer);
default:abort();}}
case 13:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->female);
case 1:return(uint64_t)(uintptr_t)(p->verbose);
case 2:return(uint64_t)(uintptr_t)(p->menu_style);
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
case 1:return(uint64_t)(uintptr_t)(p->suppress_price);
case 2:return(uint64_t)(uintptr_t)(p->menu_requested);
default:abort();}}
case 15:{struct instance_globals_a*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->auto_credit);
default:abort();}}
case 16:{struct instance_globals_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->billobjs);
default:abort();}}
case 17:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->current_wand);
default:abort();}}
case 18:{struct instance_globals_f*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->followmsg);
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 20:{struct instance_globals_k*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->kickedobj);
default:abort();}}
case 21:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->multi);
case 1:return(uint64_t)(uintptr_t)(p->migrating_objs);
case 2:return(uint64_t)(uintptr_t)(p->mydogs);
case 3:return(uint64_t)(uintptr_t)(p->migrating_mons);
default:abort();}}
case 22:{struct instance_globals_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->repo);
default:abort();}}
case 23:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sell_response);
case 1:return(uint64_t)(uintptr_t)(p->sell_how);
default:abort();}}
case 24:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 25:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->moves);
case 1:return(uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 26:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 27:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 28:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->thrownobj);
default:abort();}}
case 29:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
case 1:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 30:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 31:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 32:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->has_shop);
default:abort();}}
case 33:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mgivenname);
case 1:return(uint64_t)(uintptr_t)(p->eshk);
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 35:{struct mkroom*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lx);
case 1:return(uint64_t)(uintptr_t)(p->hx);
case 2:return(uint64_t)(uintptr_t)(p->ly);
case 3:return(uint64_t)(uintptr_t)(p->hy);
case 4:return(uint64_t)(uintptr_t)(p->rtype);
case 5:return(uint64_t)(uintptr_t)(p->resident);
default:abort();}}
case 36:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nmon);
case 1:return(uint64_t)(uintptr_t)(p->data);
case 2:return(uint64_t)(uintptr_t)(p->m_id);
case 3:return(uint64_t)(uintptr_t)(p->mnum);
case 4:return(uint64_t)(uintptr_t)(p->mx);
case 5:return(uint64_t)(uintptr_t)(p->my);
case 6:return(uint64_t)(uintptr_t)(p->mhp);
case 7:return(uint64_t)(uintptr_t)(p->m_ap_type);
case 8:return(uint64_t)(uintptr_t)(p->mtame);
case 9:return(uint64_t)(uintptr_t)(p->minvis);
case 10:return(uint64_t)(uintptr_t)(p->perminvis);
case 11:return(uint64_t)(uintptr_t)(p->mcansee);
case 12:return(uint64_t)(uintptr_t)(p->msleeping);
case 13:return(uint64_t)(uintptr_t)(p->mfrozen);
case 14:return(uint64_t)(uintptr_t)(p->mcanmove);
case 15:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 16:return(uint64_t)(uintptr_t)(p->mtrapped);
case 17:return(uint64_t)(uintptr_t)(p->isshk);
case 18:return(uint64_t)(uintptr_t)(p->minvent);
case 19:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 37:{struct mvitals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mvflags);
default:abort();}}
case 38:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 39:{struct obj*p=at;switch(field){
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
case 11:return(uint64_t)(uintptr_t)(p->oartifact);
case 12:return(uint64_t)(uintptr_t)(p->where);
case 13:return(uint64_t)(uintptr_t)(p->timed);
case 14:return(uint64_t)(uintptr_t)(p->cursed);
case 15:return(uint64_t)(uintptr_t)(p->blessed);
case 16:return(uint64_t)(uintptr_t)(p->unpaid);
case 17:return(uint64_t)(uintptr_t)(p->no_charge);
case 18:return(uint64_t)(uintptr_t)(p->dknown);
case 19:return(uint64_t)(uintptr_t)(p->cknown);
case 20:return(uint64_t)(uintptr_t)(p->globby);
case 21:return(uint64_t)(uintptr_t)(p->in_use);
case 22:return(uint64_t)(uintptr_t)(p->bypass);
case 23:return(uint64_t)(uintptr_t)(p->corpsenm);
case 24:return(uint64_t)(uintptr_t)(p->oeaten);
case 25:return(uint64_t)(uintptr_t)(p->age);
case 26:return(uint64_t)(uintptr_t)(p->owornmask);
case 27:return(uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 40:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name_known);
case 1:return(uint64_t)(uintptr_t)(p->oc_magic);
case 2:return(uint64_t)(uintptr_t)(p->oc_charged);
case 3:return(uint64_t)(uintptr_t)(p->oc_material);
case 4:return(uint64_t)(uintptr_t)(p->oc_subtyp);
case 5:return(uint64_t)(uintptr_t)(p->oc_weight);
case 6:return(uint64_t)(uintptr_t)(p->oc_cost);
case 7:return(uint64_t)(uintptr_t)(p->oc_sell_minseen);
case 8:return(uint64_t)(uintptr_t)(p->oc_sell_maxseen);
case 9:return(uint64_t)(uintptr_t)(p->oc_buy_minseen);
case 10:return(uint64_t)(uintptr_t)(p->oc_buy_maxseen);
default:abort();}}
case 41:{struct oextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->omid);
default:abort();}}
case 42:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mlet);
case 1:return(uint64_t)(uintptr_t)(p->mlevel);
case 2:return(uint64_t)(uintptr_t)(p->geno);
case 3:return(uint64_t)(uintptr_t)(p->cnutrit);
case 4:return(uint64_t)(uintptr_t)(p->msound);
case 5:return(uint64_t)(uintptr_t)(p->mflags1);
case 6:return(uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 43:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 44:{struct repo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->shopkeeper);
case 1:return(uint64_t)(uintptr_t)(&p->location);
default:abort();}}
case 45:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->seenv);
case 2:return(uint64_t)(uintptr_t)(p->flags);
case 3:return(uint64_t)(uintptr_t)(p->roomno);
case 4:return(uint64_t)(uintptr_t)(p->edge);
default:abort();}}
case 46:{struct shclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
default:abort();}}
case 47:{struct shk_icost*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->trinsic);
case 1:return(uint64_t)(uintptr_t)(p->cost);
default:abort();}}
case 48:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->gameover);
default:abort();}}
case 49:{struct sortbill_item*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->obj);
case 1:return(uint64_t)(uintptr_t)(p->cost);
case 2:return(uint64_t)(uintptr_t)(p->quan);
case 3:return(uint64_t)(uintptr_t)(p->bidx);
case 4:return(uint64_t)(uintptr_t)(p->usedup);
case 5:return(uint64_t)(uintptr_t)(p->queuedpay);
default:abort();}}
case 50:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tx);
case 1:return(uint64_t)(uintptr_t)(p->ty);
case 2:return(uint64_t)(uintptr_t)(p->ttyp);
case 3:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 51:{struct u_event*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->invoked);
case 1:return(uint64_t)(uintptr_t)(p->udemigod);
default:abort();}}
case 52:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 53:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
case 1:return(uint64_t)(uintptr_t)(p->v_ocontainer);
case 2:return(uint64_t)(uintptr_t)(p->v_ocarry);
default:abort();}}
case 54:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 1:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 2:return(uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 3:return(uint64_t)(uintptr_t)(p->win_putstr);
case 4:return(uint64_t)(uintptr_t)(p->win_start_menu);
case 5:return(uint64_t)(uintptr_t)(p->win_end_menu);
case 6:return(uint64_t)(uintptr_t)(p->win_mark_synch);
case 7:return(uint64_t)(uintptr_t)(p->win_wait_synch);
case 8:return(uint64_t)(uintptr_t)(p->win_delay_output);
default:abort();}}
case 55:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(p->ux0);
case 3:return(uint64_t)(uintptr_t)(p->uy0);
case 4:return(uint64_t)(uintptr_t)(&p->uz);
case 5:return(uint64_t)(uintptr_t)(p->ulevel);
case 6:return(uint64_t)(uintptr_t)(p->utraptype);
case 7:return(uint64_t)(uintptr_t)(&p->ushops);
case 8:return(uint64_t)(uintptr_t)(&p->ushops0);
case 9:return(uint64_t)(uintptr_t)(p->uhs);
case 10:return(uint64_t)(uintptr_t)(&p->uprops);
case 11:return(uint64_t)(uintptr_t)(p->umonster);
case 12:return(uint64_t)(uintptr_t)(p->umonnum);
case 13:return(uint64_t)(uintptr_t)(p->uswallow);
case 14:return(uint64_t)(uintptr_t)(p->uinwater);
case 15:return(uint64_t)(uintptr_t)(&p->uevent);
case 16:return(uint64_t)(uintptr_t)(&p->uroleplay);
case 17:return(uint64_t)(uintptr_t)(&p->ualign);
case 18:return(uint64_t)(uintptr_t)(p->usteed);
case 19:return(uint64_t)(uintptr_t)(p->ugrave_arise);
case 20:return(uint64_t)(uintptr_t)(p->twoweap);
default:abort();}}
default:abort();}}
void teleport_shk_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:p->he=(__typeof__(p->he))value;return;
case 1:p->him=(__typeof__(p->him))value;return;
case 2:p->his=(__typeof__(p->his))value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:p->type=(__typeof__(p->type))value;return;
default:abort();}}
case 4:{union any*p=at;switch(field){
case 0:p->a_int=(__typeof__(p->a_int))value;return;
default:abort();}}
case 5:{struct bill_x*p=at;switch(field){
case 0:p->bo_id=(__typeof__(p->bo_id))value;return;
case 1:p->useup=(__typeof__(p->useup))value;return;
case 2:p->price=(__typeof__(p->price))value;return;
case 3:p->bquan=(__typeof__(p->bquan))value;return;
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 9:{struct damage*p=at;switch(field){
case 0:p->next=(__typeof__(p->next))value;return;
case 1:p->when=(__typeof__(p->when))value;return;
case 2:p->cost=(__typeof__(p->cost))value;return;
case 4:p->typ=(__typeof__(p->typ))value;return;
case 5:p->flags=(__typeof__(p->flags))value;return;
default:abort();}}
case 10:{struct display_hints*p=at;switch(field){
case 0:p->botl=(__typeof__(p->botl))value;return;
default:abort();}}
case 11:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(__typeof__(p->objlist))value;return;
case 4:p->buriedobjlist=(__typeof__(p->buriedobjlist))value;return;
case 5:p->monlist=(__typeof__(p->monlist))value;return;
case 6:p->damagelist=(__typeof__(p->damagelist))value;return;
default:abort();}}
case 12:{struct eshk*p=at;switch(field){
case 0:p->robbed=(__typeof__(p->robbed))value;return;
case 1:p->credit=(__typeof__(p->credit))value;return;
case 2:p->debit=(__typeof__(p->debit))value;return;
case 3:p->loan=(__typeof__(p->loan))value;return;
case 4:p->shoptype=(__typeof__(p->shoptype))value;return;
case 5:p->shoproom=(__typeof__(p->shoproom))value;return;
case 6:p->following=(__typeof__(p->following))value;return;
case 7:p->surcharge=(__typeof__(p->surcharge))value;return;
case 8:p->dismiss_kops=(__typeof__(p->dismiss_kops))value;return;
case 12:p->billct=(__typeof__(p->billct))value;return;
case 14:p->bill_p=(__typeof__(p->bill_p))value;return;
case 15:p->visitct=(__typeof__(p->visitct))value;return;
default:abort();}}
case 13:{struct flag*p=at;switch(field){
case 0:p->female=(__typeof__(p->female))value;return;
case 1:p->verbose=(__typeof__(p->verbose))value;return;
case 2:p->menu_style=(__typeof__(p->menu_style))value;return;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(__typeof__(p->last_msg))value;return;
case 1:p->suppress_price=(__typeof__(p->suppress_price))value;return;
case 2:p->menu_requested=(__typeof__(p->menu_requested))value;return;
default:abort();}}
case 15:{struct instance_globals_a*p=at;switch(field){
case 0:p->auto_credit=(__typeof__(p->auto_credit))value;return;
default:abort();}}
case 16:{struct instance_globals_b*p=at;switch(field){
case 0:p->billobjs=(__typeof__(p->billobjs))value;return;
default:abort();}}
case 17:{struct instance_globals_c*p=at;switch(field){
case 0:p->current_wand=(__typeof__(p->current_wand))value;return;
default:abort();}}
case 18:{struct instance_globals_f*p=at;switch(field){
case 0:p->followmsg=(__typeof__(p->followmsg))value;return;
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(__typeof__(p->invent))value;return;
default:abort();}}
case 20:{struct instance_globals_k*p=at;switch(field){
case 0:p->kickedobj=(__typeof__(p->kickedobj))value;return;
default:abort();}}
case 21:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=(__typeof__(p->multi))value;return;
case 1:p->migrating_objs=(__typeof__(p->migrating_objs))value;return;
case 2:p->mydogs=(__typeof__(p->mydogs))value;return;
case 3:p->migrating_mons=(__typeof__(p->migrating_mons))value;return;
default:abort();}}
case 22:{struct instance_globals_r*p=at;switch(field){
default:abort();}}
case 23:{struct instance_globals_s*p=at;switch(field){
case 0:p->sell_response=(__typeof__(p->sell_response))value;return;
case 1:p->sell_how=(__typeof__(p->sell_how))value;return;
default:abort();}}
case 24:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 25:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=(__typeof__(p->moves))value;return;
default:abort();}}
case 26:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 28:{struct instance_globals_t*p=at;switch(field){
case 0:p->thrownobj=(__typeof__(p->thrownobj))value;return;
default:abort();}}
case 29:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 30:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(__typeof__(p->viz_array))value;return;
default:abort();}}
case 31:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 32:{struct levelflags*p=at;switch(field){
case 0:p->has_shop=(unsigned int)value;return;
default:abort();}}
case 33:{struct mextra*p=at;switch(field){
case 0:p->mgivenname=(__typeof__(p->mgivenname))value;return;
case 1:p->eshk=(__typeof__(p->eshk))value;return;
default:abort();}}
case 34:{struct mi*p=at;switch(field){
default:abort();}}
case 35:{struct mkroom*p=at;switch(field){
case 0:p->lx=(__typeof__(p->lx))value;return;
case 1:p->hx=(__typeof__(p->hx))value;return;
case 2:p->ly=(__typeof__(p->ly))value;return;
case 3:p->hy=(__typeof__(p->hy))value;return;
case 4:p->rtype=(__typeof__(p->rtype))value;return;
case 5:p->resident=(__typeof__(p->resident))value;return;
default:abort();}}
case 36:{struct monst*p=at;switch(field){
case 0:p->nmon=(__typeof__(p->nmon))value;return;
case 1:p->data=(__typeof__(p->data))value;return;
case 2:p->m_id=(__typeof__(p->m_id))value;return;
case 3:p->mnum=(__typeof__(p->mnum))value;return;
case 4:p->mx=(__typeof__(p->mx))value;return;
case 5:p->my=(__typeof__(p->my))value;return;
case 6:p->mhp=(__typeof__(p->mhp))value;return;
case 7:p->m_ap_type=(__typeof__(p->m_ap_type))value;return;
case 8:p->mtame=(__typeof__(p->mtame))value;return;
case 9:p->minvis=(unsigned int)value;return;
case 10:p->perminvis=(unsigned int)value;return;
case 11:p->mcansee=(unsigned int)value;return;
case 12:p->msleeping=(unsigned int)value;return;
case 13:p->mfrozen=(unsigned int)value;return;
case 14:p->mcanmove=(unsigned int)value;return;
case 15:p->mpeaceful=(unsigned int)value;return;
case 16:p->mtrapped=(unsigned int)value;return;
case 17:p->isshk=(unsigned int)value;return;
case 18:p->minvent=(__typeof__(p->minvent))value;return;
case 19:p->mextra=(__typeof__(p->mextra))value;return;
default:abort();}}
case 37:{struct mvitals*p=at;switch(field){
case 0:p->mvflags=(__typeof__(p->mvflags))value;return;
default:abort();}}
case 38:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 39:{struct obj*p=at;switch(field){
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
case 11:p->oartifact=(__typeof__(p->oartifact))value;return;
case 12:p->where=(__typeof__(p->where))value;return;
case 13:p->timed=(__typeof__(p->timed))value;return;
case 14:p->cursed=(unsigned int)value;return;
case 15:p->blessed=(unsigned int)value;return;
case 16:p->unpaid=(unsigned int)value;return;
case 17:p->no_charge=(unsigned int)value;return;
case 18:p->dknown=(unsigned int)value;return;
case 19:p->cknown=(unsigned int)value;return;
case 20:p->globby=(unsigned int)value;return;
case 21:p->in_use=(unsigned int)value;return;
case 22:p->bypass=(unsigned int)value;return;
case 23:p->corpsenm=(__typeof__(p->corpsenm))value;return;
case 24:p->oeaten=(__typeof__(p->oeaten))value;return;
case 25:p->age=(__typeof__(p->age))value;return;
case 26:p->owornmask=(__typeof__(p->owornmask))value;return;
case 27:p->oextra=(__typeof__(p->oextra))value;return;
default:abort();}}
case 40:{struct objclass*p=at;switch(field){
case 0:p->oc_name_known=(unsigned int)value;return;
case 1:p->oc_magic=(unsigned int)value;return;
case 2:p->oc_charged=(unsigned int)value;return;
case 3:p->oc_material=(unsigned int)value;return;
case 4:p->oc_subtyp=(__typeof__(p->oc_subtyp))value;return;
case 5:p->oc_weight=(__typeof__(p->oc_weight))value;return;
case 6:p->oc_cost=(__typeof__(p->oc_cost))value;return;
case 7:p->oc_sell_minseen=(__typeof__(p->oc_sell_minseen))value;return;
case 8:p->oc_sell_maxseen=(__typeof__(p->oc_sell_maxseen))value;return;
case 9:p->oc_buy_minseen=(__typeof__(p->oc_buy_minseen))value;return;
case 10:p->oc_buy_maxseen=(__typeof__(p->oc_buy_maxseen))value;return;
default:abort();}}
case 41:{struct oextra*p=at;switch(field){
case 0:p->omid=(__typeof__(p->omid))value;return;
default:abort();}}
case 42:{struct permonst*p=at;switch(field){
case 0:p->mlet=(__typeof__(p->mlet))value;return;
case 1:p->mlevel=(__typeof__(p->mlevel))value;return;
case 2:p->geno=(__typeof__(p->geno))value;return;
case 3:p->cnutrit=(__typeof__(p->cnutrit))value;return;
case 4:p->msound=(__typeof__(p->msound))value;return;
case 5:p->mflags1=(__typeof__(p->mflags1))value;return;
case 6:p->mflags2=(__typeof__(p->mflags2))value;return;
default:abort();}}
case 43:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(__typeof__(p->extrinsic))value;return;
case 1:p->blocked=(__typeof__(p->blocked))value;return;
case 2:p->intrinsic=(__typeof__(p->intrinsic))value;return;
default:abort();}}
case 44:{struct repo*p=at;switch(field){
case 0:p->shopkeeper=(__typeof__(p->shopkeeper))value;return;
default:abort();}}
case 45:{struct rm*p=at;switch(field){
case 0:p->typ=(__typeof__(p->typ))value;return;
case 1:p->seenv=(__typeof__(p->seenv))value;return;
case 2:p->flags=(unsigned int)value;return;
case 3:p->roomno=(unsigned int)value;return;
case 4:p->edge=(unsigned int)value;return;
default:abort();}}
case 46:{struct shclass*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
default:abort();}}
case 47:{struct shk_icost*p=at;switch(field){
case 0:p->trinsic=(__typeof__(p->trinsic))value;return;
case 1:p->cost=(__typeof__(p->cost))value;return;
default:abort();}}
case 48:{struct sinfo*p=at;switch(field){
case 0:p->gameover=(__typeof__(p->gameover))value;return;
default:abort();}}
case 49:{struct sortbill_item*p=at;switch(field){
case 0:p->obj=(__typeof__(p->obj))value;return;
case 1:p->cost=(__typeof__(p->cost))value;return;
case 2:p->quan=(__typeof__(p->quan))value;return;
case 3:p->bidx=(__typeof__(p->bidx))value;return;
case 4:p->usedup=(__typeof__(p->usedup))value;return;
case 5:p->queuedpay=(__typeof__(p->queuedpay))value;return;
default:abort();}}
case 50:{struct trap*p=at;switch(field){
case 0:p->tx=(__typeof__(p->tx))value;return;
case 1:p->ty=(__typeof__(p->ty))value;return;
case 2:p->ttyp=(unsigned int)value;return;
case 3:p->tseen=(unsigned int)value;return;
default:abort();}}
case 51:{struct u_event*p=at;switch(field){
case 0:p->invoked=(unsigned int)value;return;
case 1:p->udemigod=(unsigned int)value;return;
default:abort();}}
case 52:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=(__typeof__(p->deaf))value;return;
default:abort();}}
case 53:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(__typeof__(p->v_nexthere))value;return;
case 1:p->v_ocontainer=(__typeof__(p->v_ocontainer))value;return;
case 2:p->v_ocarry=(__typeof__(p->v_ocarry))value;return;
default:abort();}}
case 54:{struct window_procs*p=at;switch(field){
case 0:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))value;return;
case 1:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 2:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))value;return;
case 3:p->win_putstr=(__typeof__(p->win_putstr))value;return;
case 4:p->win_start_menu=(__typeof__(p->win_start_menu))value;return;
case 5:p->win_end_menu=(__typeof__(p->win_end_menu))value;return;
case 6:p->win_mark_synch=(__typeof__(p->win_mark_synch))value;return;
case 7:p->win_wait_synch=(__typeof__(p->win_wait_synch))value;return;
case 8:p->win_delay_output=(__typeof__(p->win_delay_output))value;return;
default:abort();}}
case 55:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 2:p->ux0=(__typeof__(p->ux0))value;return;
case 3:p->uy0=(__typeof__(p->uy0))value;return;
case 5:p->ulevel=(__typeof__(p->ulevel))value;return;
case 6:p->utraptype=(__typeof__(p->utraptype))value;return;
case 9:p->uhs=(__typeof__(p->uhs))value;return;
case 11:p->umonster=(__typeof__(p->umonster))value;return;
case 12:p->umonnum=(__typeof__(p->umonnum))value;return;
case 13:p->uswallow=(unsigned int)value;return;
case 14:p->uinwater=(unsigned int)value;return;
case 18:p->usteed=(__typeof__(p->usteed))value;return;
case 19:p->ugrave_arise=(__typeof__(p->ugrave_arise))value;return;
case 20:p->twoweap=(__typeof__(p->twoweap))value;return;
default:abort();}}
default:abort();}}
void* teleport_shk_address(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->he;
case 1:return(void*)&p->him;
case 2:return(void*)&p->his;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{struct Role*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return(void*)&p->type;
default:abort();}}
case 4:{union any*p=at;switch(field){
case 0:return(void*)&p->a_int;
default:abort();}}
case 5:{struct bill_x*p=at;switch(field){
case 0:return(void*)&p->bo_id;
case 1:return(void*)&p->useup;
case 2:return(void*)&p->price;
case 3:return(void*)&p->bquan;
default:abort();}}
case 6:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_the_your;
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroany;
default:abort();}}
case 8:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dlevel;
default:abort();}}
case 9:{struct damage*p=at;switch(field){
case 0:return(void*)&p->next;
case 1:return(void*)&p->when;
case 2:return(void*)&p->cost;
case 3:return(void*)&p->place;
case 4:return(void*)&p->typ;
case 5:return(void*)&p->flags;
default:abort();}}
case 10:{struct display_hints*p=at;switch(field){
case 0:return(void*)&p->botl;
default:abort();}}
case 11:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->objlist;
case 4:return(void*)&p->buriedobjlist;
case 5:return(void*)&p->monlist;
case 6:return(void*)&p->damagelist;
case 7:return(void*)&p->flags;
default:abort();}}
case 12:{struct eshk*p=at;switch(field){
case 0:return(void*)&p->robbed;
case 1:return(void*)&p->credit;
case 2:return(void*)&p->debit;
case 3:return(void*)&p->loan;
case 4:return(void*)&p->shoptype;
case 5:return(void*)&p->shoproom;
case 6:return(void*)&p->following;
case 7:return(void*)&p->surcharge;
case 8:return(void*)&p->dismiss_kops;
case 9:return(void*)&p->shk;
case 10:return(void*)&p->shd;
case 11:return(void*)&p->shoplevel;
case 12:return(void*)&p->billct;
case 13:return(void*)&p->bill;
case 14:return(void*)&p->bill_p;
case 15:return(void*)&p->visitct;
case 16:return(void*)&p->customer;
default:abort();}}
case 13:{struct flag*p=at;switch(field){
case 0:return(void*)&p->female;
case 1:return(void*)&p->verbose;
case 2:return(void*)&p->menu_style;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
case 1:return(void*)&p->suppress_price;
case 2:return(void*)&p->menu_requested;
default:abort();}}
case 15:{struct instance_globals_a*p=at;switch(field){
case 0:return(void*)&p->auto_credit;
default:abort();}}
case 16:{struct instance_globals_b*p=at;switch(field){
case 0:return(void*)&p->billobjs;
default:abort();}}
case 17:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->current_wand;
default:abort();}}
case 18:{struct instance_globals_f*p=at;switch(field){
case 0:return(void*)&p->followmsg;
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->invent;
default:abort();}}
case 20:{struct instance_globals_k*p=at;switch(field){
case 0:return(void*)&p->kickedobj;
default:abort();}}
case 21:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->multi;
case 1:return(void*)&p->migrating_objs;
case 2:return(void*)&p->mydogs;
case 3:return(void*)&p->migrating_mons;
default:abort();}}
case 22:{struct instance_globals_r*p=at;switch(field){
case 0:return(void*)&p->repo;
default:abort();}}
case 23:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->sell_response;
case 1:return(void*)&p->sell_how;
default:abort();}}
case 24:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level;
default:abort();}}
case 25:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->moves;
case 1:return(void*)&p->mvitals;
default:abort();}}
case 26:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(void*)&p->plname;
default:abort();}}
case 27:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(void*)&p->rooms;
default:abort();}}
case 28:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->thrownobj;
default:abort();}}
case 29:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
case 1:return(void*)&p->urace;
default:abort();}}
case 30:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->viz_array;
default:abort();}}
case 31:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 32:{struct levelflags*p=at;switch(field){
default:abort();}}
case 33:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->mgivenname;
case 1:return(void*)&p->eshk;
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 0:return(void*)&p->item;
default:abort();}}
case 35:{struct mkroom*p=at;switch(field){
case 0:return(void*)&p->lx;
case 1:return(void*)&p->hx;
case 2:return(void*)&p->ly;
case 3:return(void*)&p->hy;
case 4:return(void*)&p->rtype;
case 5:return(void*)&p->resident;
default:abort();}}
case 36:{struct monst*p=at;switch(field){
case 0:return(void*)&p->nmon;
case 1:return(void*)&p->data;
case 2:return(void*)&p->m_id;
case 3:return(void*)&p->mnum;
case 4:return(void*)&p->mx;
case 5:return(void*)&p->my;
case 6:return(void*)&p->mhp;
case 7:return(void*)&p->m_ap_type;
case 8:return(void*)&p->mtame;
case 18:return(void*)&p->minvent;
case 19:return(void*)&p->mextra;
default:abort();}}
case 37:{struct mvitals*p=at;switch(field){
case 0:return(void*)&p->mvflags;
default:abort();}}
case 38:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 39:{struct obj*p=at;switch(field){
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
case 11:return(void*)&p->oartifact;
case 12:return(void*)&p->where;
case 13:return(void*)&p->timed;
case 23:return(void*)&p->corpsenm;
case 24:return(void*)&p->oeaten;
case 25:return(void*)&p->age;
case 26:return(void*)&p->owornmask;
case 27:return(void*)&p->oextra;
default:abort();}}
case 40:{struct objclass*p=at;switch(field){
case 4:return(void*)&p->oc_subtyp;
case 5:return(void*)&p->oc_weight;
case 6:return(void*)&p->oc_cost;
case 7:return(void*)&p->oc_sell_minseen;
case 8:return(void*)&p->oc_sell_maxseen;
case 9:return(void*)&p->oc_buy_minseen;
case 10:return(void*)&p->oc_buy_maxseen;
default:abort();}}
case 41:{struct oextra*p=at;switch(field){
case 0:return(void*)&p->omid;
default:abort();}}
case 42:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->mlet;
case 1:return(void*)&p->mlevel;
case 2:return(void*)&p->geno;
case 3:return(void*)&p->cnutrit;
case 4:return(void*)&p->msound;
case 5:return(void*)&p->mflags1;
case 6:return(void*)&p->mflags2;
default:abort();}}
case 43:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 44:{struct repo*p=at;switch(field){
case 0:return(void*)&p->shopkeeper;
case 1:return(void*)&p->location;
default:abort();}}
case 45:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
case 1:return(void*)&p->seenv;
default:abort();}}
case 46:{struct shclass*p=at;switch(field){
case 0:return(void*)&p->name;
default:abort();}}
case 47:{struct shk_icost*p=at;switch(field){
case 0:return(void*)&p->trinsic;
case 1:return(void*)&p->cost;
default:abort();}}
case 48:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->gameover;
default:abort();}}
case 49:{struct sortbill_item*p=at;switch(field){
case 0:return(void*)&p->obj;
case 1:return(void*)&p->cost;
case 2:return(void*)&p->quan;
case 3:return(void*)&p->bidx;
case 4:return(void*)&p->usedup;
case 5:return(void*)&p->queuedpay;
default:abort();}}
case 50:{struct trap*p=at;switch(field){
case 0:return(void*)&p->tx;
case 1:return(void*)&p->ty;
default:abort();}}
case 51:{struct u_event*p=at;switch(field){
default:abort();}}
case 52:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->deaf;
default:abort();}}
case 53:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
case 1:return(void*)&p->v_ocontainer;
case 2:return(void*)&p->v_ocarry;
default:abort();}}
case 54:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_create_nhwindow;
case 1:return(void*)&p->win_display_nhwindow;
case 2:return(void*)&p->win_destroy_nhwindow;
case 3:return(void*)&p->win_putstr;
case 4:return(void*)&p->win_start_menu;
case 5:return(void*)&p->win_end_menu;
case 6:return(void*)&p->win_mark_synch;
case 7:return(void*)&p->win_wait_synch;
case 8:return(void*)&p->win_delay_output;
default:abort();}}
case 55:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->ux0;
case 3:return(void*)&p->uy0;
case 4:return(void*)&p->uz;
case 5:return(void*)&p->ulevel;
case 6:return(void*)&p->utraptype;
case 7:return(void*)&p->ushops;
case 8:return(void*)&p->ushops0;
case 9:return(void*)&p->uhs;
case 10:return(void*)&p->uprops;
case 11:return(void*)&p->umonster;
case 12:return(void*)&p->umonnum;
case 15:return(void*)&p->uevent;
case 16:return(void*)&p->uroleplay;
case 17:return(void*)&p->ualign;
case 18:return(void*)&p->usteed;
case 19:return(void*)&p->ugrave_arise;
case 20:return(void*)&p->twoweap;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_shk_var0(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_shk_var1(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_shk_var2(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_shk_var3(char * a0,char * a1,char * a2){(impossible)(a0,a1,a2);}
void teleport_shk_var4(char * a0){(You)(a0);}
int teleport_shk_var5(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_shk_var6(char * a0,char * a1,unsigned long a2,unsigned long a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_shk_var7(char * a0,char * a1,unsigned long a2){return (sprintf)(a0,a1,a2);}
int teleport_shk_var8(char * a0,char * a1,char * a2,unsigned long a3,unsigned long a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_shk_var9(char * a0,char * a1,char * a2,unsigned long a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_shk_var10(char * a0,char * a1){return (sprintf)(a0,a1);}
void teleport_shk_var11(char * a0){(pline)(a0);}
void teleport_shk_var12(char * a0){(pline)(a0);}
void teleport_shk_var13(char * a0){(pline_The)(a0);}
void teleport_shk_var14(char * a0){(pline_The)(a0);}
void teleport_shk_var15(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_shk_var16(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var17(char * a0,char * a1,long a2,char * a3){(Your)(a0,a1,a2,a3);}
void teleport_shk_var18(char * a0,long a1,char * a2){(Your)(a0,a1,a2);}
void teleport_shk_var19(char * a0){(You)(a0);}
void teleport_shk_var20(char * a0,long a1,char * a2){(You)(a0,a1,a2);}
void teleport_shk_var21(long a0,char * a1,long a2,char * a3,char * a4,char * a5){(livelog_printf)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var22(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var23(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var24(char * a0){(verbalize)(a0);}
void teleport_shk_var25(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var26(char * a0,char * a1,char * a2,char * a3){(verbalize)(a0,a1,a2,a3);}
void teleport_shk_var27(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_shk_var28(char * a0,char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_shk_var29(char * a0,char * a1,char * a2){(pline_The)(a0,a1,a2);}
void teleport_shk_var30(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var31(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var32(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){(verbalize)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var33(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_shk_var34(char * a0,char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_shk_var35(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_shk_var36(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_shk_var37(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var38(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_shk_var39(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var40(char * a0){(impossible)(a0);}
void teleport_shk_var41(char * a0){(You)(a0);}
void teleport_shk_var42(char * a0,long a1,char * a2,char * a3,char * a4){(You)(a0,a1,a2,a3,a4);}
void teleport_shk_var43(char * a0){(You)(a0);}
void teleport_shk_var44(char * a0,char * a1,long a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_shk_var45(char * a0){(You)(a0);}
void teleport_shk_var46(char * a0,char * a1,int a2,int a3,int a4,char * a5){(impossible)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var47(char * a0){(impossible)(a0);}
void teleport_shk_var48(char * a0,char * a1){(impossible)(a0,a1);}
void teleport_shk_var49(char * a0,char * a1,int a2,int a3,long a4,int a5,int a6,int a7,long a8,int a9){(impossible)(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9);}
void teleport_shk_var50(char * a0,int a1,long a2){(impossible)(a0,a1,a2);}
void teleport_shk_var51(char * a0){(pline_The)(a0);}
void teleport_shk_var52(char * a0){(pline_The)(a0);}
void teleport_shk_var53(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var54(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var55(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var56(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var57(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var58(char * a0,unsigned int a1){(impossible)(a0,a1);}
int teleport_shk_var59(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
int teleport_shk_var60(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_shk_var61(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_shk_var62(char * a0,int a1,char * a2,unsigned long a3,char * a4,int a5,long a6,char * a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_shk_var63(char * a0){(There)(a0);}
void teleport_shk_var64(char * a0){(You_cant)(a0);}
void teleport_shk_var65(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var66(char * a0){(pline)(a0);}
void teleport_shk_var67(char * a0){(pline)(a0);}
void teleport_shk_var68(char * a0){(You)(a0);}
void teleport_shk_var69(char * a0,char * a1){(You)(a0,a1);}
void teleport_shk_var70(char * a0){(There)(a0);}
void teleport_shk_var71(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var72(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var73(char * a0){(pline)(a0);}
void teleport_shk_var74(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var75(char * a0,char * a1){(You)(a0,a1);}
void teleport_shk_var76(char * a0,char * a1){(You)(a0,a1);}
void teleport_shk_var77(char * a0){(pline)(a0);}
void teleport_shk_var78(char * a0,char * a1,long a2,char * a3,char * a4){(You)(a0,a1,a2,a3,a4);}
void teleport_shk_var79(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_shk_var80(char * a0){(pline)(a0);}
void teleport_shk_var81(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var82(char * a0,char * a1){(You)(a0,a1);}
void teleport_shk_var83(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var84(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var85(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var86(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var87(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var88(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var89(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var90(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var91(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var92(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_shk_var93(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var94(char * a0){(impossible)(a0);}
int teleport_shk_var95(char * a0,char * a1,char * a2,long a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_shk_var96(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var97(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var98(char * a0){(Your)(a0);}
void teleport_shk_var99(char * a0){(You)(a0);}
void teleport_shk_var100(char * a0){(pline)(a0);}
void teleport_shk_var101(char * a0){(You)(a0);}
void teleport_shk_var102(char * a0,char * a1,char * a2,char * a3){(verbalize)(a0,a1,a2,a3);}
void teleport_shk_var103(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){(pline)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var104(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_shk_var105(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_shk_var106(char * a0){(pline)(a0);}
void teleport_shk_var107(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_shk_var108(char * a0){(impossible)(a0);}
int teleport_shk_var109(char * a0,char * a1,long a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_shk_var110(char * a0,unsigned int a1){(impossible)(a0,a1);}
void teleport_shk_var111(char * a0,char * a1,unsigned int a2){(impossible)(a0,a1,a2);}
void teleport_shk_var112(char * a0,char * a1,unsigned int a2,int a3){(impossible)(a0,a1,a2,a3);}
void teleport_shk_var113(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
int teleport_shk_var114(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_shk_var115(char * a0,char * a1,char * a2,char * a3){(verbalize)(a0,a1,a2,a3);}
void teleport_shk_var116(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_shk_var117(char * a0,char * a1){(You)(a0,a1);}
void teleport_shk_var118(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
int teleport_shk_var119(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_shk_var120(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_shk_var121(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var122(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var123(char * a0,char * a1,char * a2,long a3,char * a4,char * a5,char * a6){(pline)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_shk_var124(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_shk_var125(char * a0,int a1){(impossible)(a0,a1);}
void teleport_shk_var126(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var127(char * a0){(verbalize)(a0);}
void teleport_shk_var128(char * a0,int a1,char * a2,char * a3){(verbalize)(a0,a1,a2,a3);}
void teleport_shk_var129(char * a0){(verbalize)(a0);}
void teleport_shk_var130(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var131(char * a0){(impossible)(a0);}
void teleport_shk_var132(char * a0){(You)(a0);}
void teleport_shk_var133(char * a0){(panic)(a0);}
int teleport_shk_var134(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_shk_var135(char * a0,char * a1,char * a2,long a3,char * a4,char * a5){(pline)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var136(char * a0,char * a1,long a2,char * a3,char * a4){(You)(a0,a1,a2,a3,a4);}
void teleport_shk_var137(char * a0){(You)(a0);}
void teleport_shk_var138(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var139(char * a0,char * a1,long a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_shk_var140(char * a0,char * a1,long a2,char * a3,char * a4,char * a5,char * a6){(pline)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_shk_var141(char * a0,char * a1,char * a2,char * a3,long a4,char * a5,char * a6){(pline_The)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_shk_var142(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var143(char * a0){(impossible)(a0);}
void teleport_shk_var144(char * a0){(impossible)(a0);}
void teleport_shk_var145(char * a0){(impossible)(a0);}
void teleport_shk_var146(char * a0){(impossible)(a0);}
void teleport_shk_var147(char * a0){(impossible)(a0);}
void teleport_shk_var148(char * a0,long a1,char * a2){(You)(a0,a1,a2);}
void teleport_shk_var149(char * a0){(You)(a0);}
int teleport_shk_var150(char * a0,char * a1,char * a2,char * a3,long a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_shk_var151(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_shk_var152(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_shk_var153(char * a0,char * a1){(You)(a0,a1);}
void teleport_shk_var154(char * a0,char * a1,char * a2){(Norep)(a0,a1,a2);}
void teleport_shk_var155(char * a0){(Norep)(a0);}
void teleport_shk_var156(char * a0,char * a1){(Your)(a0,a1);}
void teleport_shk_var157(char * a0){(Your)(a0);}
void teleport_shk_var158(char * a0,char * a1,long a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_shk_var159(char * a0,long a1,char * a2,char * a3,long a4,char * a5){(pline)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var160(char * a0){(verbalize)(a0);}
void teleport_shk_var161(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var162(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var163(char * a0){(verbalize)(a0);}
void teleport_shk_var164(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var165(char * a0,char * a1){(pline)(a0,a1);}
int teleport_shk_var166(char * a0,char * a1,long a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_shk_var167(char * a0,char * a1,char * a2,char * a3,long a4,char * a5,char * a6,char * a7){return (sprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
int teleport_shk_var168(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_shk_var169(char * a0){(impossible)(a0);}
void teleport_shk_var170(char * a0){(impossible)(a0);}
void teleport_shk_var171(char * a0){(impossible)(a0);}
void teleport_shk_var172(char * a0){(verbalize)(a0);}
void teleport_shk_var173(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var174(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var175(char * a0){(You_hear)(a0);}
void teleport_shk_var176(char * a0){(verbalize)(a0);}
void teleport_shk_var177(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var178(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var179(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var180(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var181(char * a0){(pline)(a0);}
void teleport_shk_var182(char * a0){(pline)(a0);}
void teleport_shk_var183(char * a0){(You_feel)(a0);}
void teleport_shk_var184(char * a0){(Norep)(a0);}
void teleport_shk_var185(char * a0,char * a1){(Your)(a0,a1);}
void teleport_shk_var186(char * a0,char * a1,char * a2,char * a3){(verbalize)(a0,a1,a2,a3);}
void teleport_shk_var187(char * a0,char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_shk_var188(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var189(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var190(char * a0){(You_feel)(a0);}
void teleport_shk_var191(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_shk_var192(char * a0,char * a1){(verbalize)(a0,a1);}
void teleport_shk_var193(char * a0){(You_feel)(a0);}
void teleport_shk_var194(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var195(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var196(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var197(char * a0,char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_shk_var198(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){(pline)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var199(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var200(char * a0,char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_shk_var201(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){(pline)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var202(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var203(char * a0){(You_hear)(a0);}
void teleport_shk_var204(char * a0){(verbalize)(a0);}
void teleport_shk_var205(char * a0,char * a1){(Your)(a0,a1);}
int teleport_shk_var206(char * a0,char * a1,char * a2,long a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var207(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var208(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var209(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var210(char * a0){(verbalize)(a0);}
void teleport_shk_var211(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
int teleport_shk_var212(char * a0,char * a1,long a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_shk_var213(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_shk_var214(char * a0,char * a1){(verbalize)(a0,a1);}
int teleport_shk_var215(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_shk_var216(char * a0,char * a1,long a2,char * a3,char * a4,char * a5){(verbalize)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var217(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var218(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_shk_var219(char * a0,char * a1,char * a2,char * a3){(verbalize)(a0,a1,a2,a3);}
void teleport_shk_var220(char * a0,char * a1,char * a2){(verbalize)(a0,a1,a2);}
void teleport_shk_var221(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var222(char * a0,char * a1,char * a2,long a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_shk_var223(char * a0,char * a1,char * a2,char * a3,long a4,char * a5){(pline)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var224(char * a0,char * a1,long a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var225(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var226(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_shk_var227(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var228(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var229(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var230(char * a0,char * a1){(pline)(a0,a1);}
void teleport_shk_var231(char * a0,char * a1,char * a2){(pline_The)(a0,a1,a2);}
int teleport_shk_var232(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_shk_var233(char * a0,char * a1,char * a2,long a3,char * a4){(verbalize)(a0,a1,a2,a3,a4);}
void teleport_shk_var234(char * a0,long a1,char * a2){(Your)(a0,a1,a2);}
void teleport_shk_var235(char * a0){(Your)(a0);}
void teleport_shk_var236(char * a0){(Your)(a0);}
void teleport_shk_var237(char * a0,long a1,char * a2){(Your)(a0,a1,a2);}
void teleport_shk_var238(char * a0,char * a1,long a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_shk_var239(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var240(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_shk_var241(char * a0){(impossible)(a0);}
int teleport_shk_var242(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_shk_var243(char * a0){(impossible)(a0);}
void teleport_shk_var244(char * a0,char * a1,char * a2){(pline_The)(a0,a1,a2);}
void teleport_shk_var245(char * a0){(Your)(a0);}
void teleport_shk_var246(char * a0,char * a1,long a2,char * a3){(pline_The)(a0,a1,a2,a3);}
void teleport_shk_var247(char * a0,char * a1,long a2,char * a3,char * a4,long a5,char * a6){(pline_The)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_shk_var248(char * a0,long a1,char * a2,char * a3,char * a4,char * a5){(verbalize)(a0,a1,a2,a3,a4,a5);}
void teleport_shk_var249(char * a0){(verbalize)(a0);}
winid teleport_shk_cb0(winid (*fn)(int),int a0){return fn(a0);}
void teleport_shk_cb1(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_shk_cb2(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_shk_cb3(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_shk_cb4(winid (*fn)(int),int a0){return fn(a0);}
void teleport_shk_cb5(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb6(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb7(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb8(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb9(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb10(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb11(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb12(void (*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
void teleport_shk_cb13(void (*fn)(winid),winid a0){fn(a0);}
void teleport_shk_cb14(void (*fn)(void)){fn();}
void teleport_shk_cb15(void (*fn)(void)){fn();}
void teleport_shk_cb16(void (*fn)(void)){fn();}
winid teleport_shk_cb17(winid (*fn)(int),int a0){return fn(a0);}
void teleport_shk_cb18(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb19(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb20(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_shk_cb21(void (*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
void teleport_shk_cb22(void (*fn)(winid),winid a0){fn(a0);}
#pragma clang diagnostic pop
static char shk_literals[10132];
char*teleport_shk_literal_storage(void){return shk_literals;}
size_t teleport_shk_literal_capacity(void){return sizeof shk_literals;}
static char shk_backing_0[18];
static char shk_backing_1[17];
static char * shk_backing_2[3];
static long shk_backing_3[2][3];
static char shk_backing_4[5];
static long shk_backing_5;
static char shk_backing_6[30];
static char shk_backing_7[47];
static struct sortbill_item shk_backing_8;
static char * shk_backing_9[5];
static short shk_backing_10[4];
static char * shk_backing_11[9];
void*teleport_shk_storage(int i){switch(i){
case 0:return &shk_backing_0;
case 1:return &shk_backing_1;
case 2:return &shk_backing_2;
case 3:return &shk_backing_3;
case 4:return &shk_backing_4;
case 5:return &shk_backing_5;
case 6:return &shk_backing_6;
case 7:return &shk_backing_7;
case 8:return &shk_backing_8;
case 9:return &shk_backing_9;
case 10:return &shk_backing_10;
case 11:return &shk_backing_11;
default:abort();}}
extern int teleport_shk_sortbill_cmp(const void * a0,const void * a1);
void*teleport_shk_function(int i){switch(i){
case 0:return(void*)Doname2;
case 1:return(void*)ansimpleoname;
case 2:return(void*)doname;
case 3:return(void*)simpleonames;
case 4:return(void*)teleport_shk_sortbill_cmp;
case 5:return(void*)thesimpleoname;
case 6:return(void*)xname;
default:abort();}}
#ifdef TELEPORT_SHK_VALIDATE_ORIGINAL
_Static_assert(sizeof and_its_contents==sizeof shk_backing_0,"SHK private backing size");
_Static_assert(sizeof the_contents_of==sizeof shk_backing_1,"SHK private backing size");
_Static_assert(sizeof angrytexts==sizeof shk_backing_2,"SHK private backing size");
_Static_assert(sizeof no_money==sizeof shk_backing_6,"SHK private backing size");
_Static_assert(sizeof not_enough_money==sizeof shk_backing_7,"SHK private backing size");
_Static_assert(sizeof Izchak_speaks==sizeof shk_backing_11,"SHK private backing size");
_Static_assert(sizeof(Bill)==32&&sizeof(struct bill_x)==24,"SHK actual Bill/bill_x stride");
#endif
