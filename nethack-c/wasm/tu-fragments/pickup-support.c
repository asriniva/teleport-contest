/* PICKUP ABI/header/native dependency transport and zero backing only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(size_t)==8,"PICKUP memory64 LP64 ABI");
_Static_assert(sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"PICKUP signed native scalar ABI");
void*teleport_pickup_global(int index){switch(index){
case 0:return(void*)&windowprocs;
case 1:return(void*)&def_oc_syms;
case 2:return(void*)&gi;
case 3:return(void*)&uarmg;
case 4:return(void*)&mons;
case 5:return(void*)&u;
case 6:return(void*)&gy;
case 7:return(void*)&WIN_MESSAGE;
case 8:return(void*)&gd;
case 9:return(void*)&iflags;
case 10:return(void*)&svl;
case 11:return(void*)&flags;
case 12:return(void*)&uchain;
case 13:return(void*)&svc;
case 14:return(void*)&gv;
case 15:return(void*)&gc;
case 16:return(void*)&gb;
case 17:return(void*)&gs;
case 18:return(void*)&gp;
case 19:return(void*)&gu;
case 20:return(void*)&gm;
case 21:return(void*)&c_common_strings;
case 22:return(void*)&ynaqchars;
case 23:return(void*)&ynNaqchars;
case 24:return(void*)&yn_number;
case 25:return(void*)&ga;
case 26:return(void*)&nul_glyphinfo;
case 27:return(void*)&cg;
case 28:return(void*)&gt;
case 29:return(void*)&go;
case 30:return(void*)&objects;
case 31:return(void*)&ynqchars;
case 32:return(void*)&disp;
case 33:return(void*)&uwep;
case 34:return(void*)&uball;
case 35:return(void*)&gl;
case 36:return(void*)&uswapwep;
case 37:return(void*)&uquiver;
case 38:return(void*)&svm;
case 39:return(void*)&genders;
case 40:return(void*)&gn;
case 41:return(void*)&uarmh;
default:abort();}}
uint64_t teleport_pickup_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(dlevel_t));
case 6:return(uint64_t)(sizeof(struct Gender));
case 7:return(uint64_t)(sizeof(struct Role));
case 8:return(uint64_t)(sizeof(struct autopickup_exception));
case 9:return(uint64_t)(sizeof(struct c_common_strings));
case 10:return(uint64_t)(sizeof(struct class_sym));
case 11:return(uint64_t)(sizeof(struct classic_representation));
case 12:return(uint64_t)(sizeof(struct const_globals));
case 13:return(uint64_t)(sizeof(struct context_info));
case 14:return(uint64_t)(sizeof(struct display_hints));
case 15:return(uint64_t)(sizeof(struct flag));
case 16:return(uint64_t)(sizeof(struct glyph_map_entry));
case 17:return(uint64_t)(sizeof(struct glyphinfo));
case 18:return(uint64_t)(sizeof(struct instance_flags));
case 19:return(uint64_t)(sizeof(struct instance_globals_a));
case 20:return(uint64_t)(sizeof(struct instance_globals_b));
case 21:return(uint64_t)(sizeof(struct instance_globals_c));
case 22:return(uint64_t)(sizeof(struct instance_globals_d));
case 23:return(uint64_t)(sizeof(struct instance_globals_i));
case 24:return(uint64_t)(sizeof(struct instance_globals_l));
case 25:return(uint64_t)(sizeof(struct instance_globals_m));
case 26:return(uint64_t)(sizeof(struct instance_globals_n));
case 27:return(uint64_t)(sizeof(struct instance_globals_o));
case 28:return(uint64_t)(sizeof(struct instance_globals_p));
case 29:return(uint64_t)(sizeof(struct instance_globals_s));
case 30:return(uint64_t)(sizeof(struct instance_globals_saved_c));
case 31:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 32:return(uint64_t)(sizeof(struct instance_globals_saved_m));
case 33:return(uint64_t)(sizeof(struct instance_globals_t));
case 34:return(uint64_t)(sizeof(struct instance_globals_u));
case 35:return(uint64_t)(sizeof(struct instance_globals_v));
case 36:return(uint64_t)(sizeof(struct instance_globals_y));
case 37:return(uint64_t)(sizeof(struct levelflags));
case 38:return(uint64_t)(sizeof(struct mi));
case 39:return(uint64_t)(sizeof(struct monst));
case 40:return(uint64_t)(sizeof(struct nhcoord));
case 41:return(uint64_t)(sizeof(struct obj));
case 42:return(uint64_t)(sizeof(struct objclass));
case 43:return(uint64_t)(sizeof(struct oextra));
case 44:return(uint64_t)(sizeof(struct permonst));
case 45:return(uint64_t)(sizeof(struct prop));
case 46:return(uint64_t)(sizeof(struct rm));
case 47:return(uint64_t)(sizeof(struct skills));
case 48:return(uint64_t)(sizeof(struct sortloot_item));
case 49:return(uint64_t)(sizeof(struct trap));
case 50:return(uint64_t)(sizeof(struct window_procs));
case 51:return(uint64_t)(sizeof(struct you));
case 52:return(uint64_t)(sizeof(union any));
case 53:return(uint64_t)(sizeof(union vptrs));
case 54:return(uint64_t)(ALTAR);
case 55:return(uint64_t)(AMULET_OF_YENDOR);
case 56:return(uint64_t)(A_WIS);
case 57:return(uint64_t)(BAG_OF_HOLDING);
case 58:return(uint64_t)(BAG_OF_TRICKS);
case 59:return(uint64_t)(BELL_OF_OPENING);
case 60:return(uint64_t)(BLINDED);
case 61:return(uint64_t)(BOULDER);
case 62:return(uint64_t)(BRASS_LANTERN);
case 63:return(uint64_t)(CANDELABRUM_OF_INVOCATION);
case 64:return(uint64_t)(CAN_OF_GREASE);
case 65:return(uint64_t)(CHEST);
case 66:return(uint64_t)(COIN_CLASS);
case 67:return(uint64_t)(CONFUSION);
case 68:return(uint64_t)(CORPSE);
case 69:return(uint64_t)(CQ_CANNED);
case 70:return(uint64_t)(CRAM_RATION);
case 71:return(uint64_t)(DRAWBRIDGE_UP);
case 72:return(uint64_t)(EXT_ENCUMBER);
case 73:return(uint64_t)(FIRST_OBJECT);
case 74:return(uint64_t)(FIRST_REAL_GEM);
case 75:return(uint64_t)(FIRST_SPELL);
case 76:return(uint64_t)(FOOD_RATION);
case 77:return(uint64_t)(FOOT);
case 78:return(uint64_t)(FUMBLING);
case 79:return(uint64_t)(GETOBJ_DOWNPLAY);
case 80:return(uint64_t)(GETOBJ_EXCLUDE);
case 81:return(uint64_t)(GETOBJ_EXCLUDE_SELECTABLE);
case 82:return(uint64_t)(GETOBJ_SUGGEST);
case 83:return(uint64_t)(GLYPH_BODY_OFF);
case 84:return(uint64_t)(GLYPH_BODY_PILETOP_OFF);
case 85:return(uint64_t)(GLYPH_MON_FEM_OFF);
case 86:return(uint64_t)(GLYPH_MON_MALE_OFF);
case 87:return(uint64_t)(GLYPH_OBJ_OFF);
case 88:return(uint64_t)(GLYPH_OBJ_PILETOP_OFF);
case 89:return(uint64_t)(GLYPH_STATUE_FEM_OFF);
case 90:return(uint64_t)(GLYPH_STATUE_FEM_PILETOP_OFF);
case 91:return(uint64_t)(GLYPH_STATUE_MALE_OFF);
case 92:return(uint64_t)(GLYPH_STATUE_MALE_PILETOP_OFF);
case 93:return(uint64_t)(GOLD_PIECE);
case 94:return(uint64_t)(GRAVE);
case 95:return(uint64_t)(HALF_PHDAM);
case 96:return(uint64_t)(HALLUC);
case 97:return(uint64_t)(HALLUC_RES);
case 98:return(uint64_t)(HAND);
case 99:return(uint64_t)(HORN_OF_PLENTY);
case 100:return(uint64_t)(HVY_ENCUMBER);
case 101:return(uint64_t)(ICE);
case 102:return(uint64_t)(ICE_BOX);
case 103:return(uint64_t)(LARGE_BOX);
case 104:return(uint64_t)(LAST_GLASS_GEM);
case 105:return(uint64_t)(LAST_SPELL);
case 106:return(uint64_t)(LAVAPOOL);
case 107:return(uint64_t)(LAVAWALL);
case 108:return(uint64_t)(LEASH);
case 109:return(uint64_t)(LEMBAS_WAFER);
case 110:return(uint64_t)(LOADSTONE);
case 111:return(uint64_t)(MAGIC_LAMP);
case 112:return(uint64_t)(MOD_ENCUMBER);
case 113:return(uint64_t)(NUMMONS);
case 114:return(uint64_t)(NUM_OBJECTS);
case 115:return(uint64_t)(OIL_LAMP);
case 116:return(uint64_t)(PIT);
case 117:return(uint64_t)(PLNMSG_BACK_ON_GROUND);
case 118:return(uint64_t)(PLNMSG_OBJNAM_ONLY);
case 119:return(uint64_t)(PM_CHICKATRICE);
case 120:return(uint64_t)(PM_CLERIC);
case 121:return(uint64_t)(PM_COCKATRICE);
case 122:return(uint64_t)(PM_DEATH);
case 123:return(uint64_t)(PM_FAMINE);
case 124:return(uint64_t)(PM_HOUSECAT);
case 125:return(uint64_t)(PM_ICE_TROLL);
case 126:return(uint64_t)(PM_PESTILENCE);
case 127:return(uint64_t)(PM_STONE_GOLEM);
case 128:return(uint64_t)(POOL);
case 129:return(uint64_t)(POTION_CLASS);
case 130:return(uint64_t)(POT_OIL);
case 131:return(uint64_t)(P_BASIC);
case 132:return(uint64_t)(P_PICK_AXE);
case 133:return(uint64_t)(P_RIDING);
case 134:return(uint64_t)(REVIVE_MON);
case 135:return(uint64_t)(ROT_CORPSE);
case 136:return(uint64_t)(SCR_SCARE_MONSTER);
case 137:return(uint64_t)(SHOPBASE);
case 138:return(uint64_t)(SHRINK_GLOB);
case 139:return(uint64_t)(SLT_ENCUMBER);
case 140:return(uint64_t)(SPE_BOOK_OF_THE_DEAD);
case 141:return(uint64_t)(SPE_WIZARD_LOCK);
case 142:return(uint64_t)(SPIKED_PIT);
case 143:return(uint64_t)(STAIRS);
case 144:return(uint64_t)(STATUE);
case 145:return(uint64_t)(STONE);
case 146:return(uint64_t)(STONE_RES);
case 147:return(uint64_t)(STUNNED);
case 148:return(uint64_t)(TALLOW_CANDLE);
case 149:return(uint64_t)(THRONE);
case 150:return(uint64_t)(TOOL_CLASS);
case 151:return(uint64_t)(VENOM_CLASS);
case 152:return(uint64_t)(WAN_CANCELLATION);
case 153:return(uint64_t)(WAX_CANDLE);
case 154:return(uint64_t)(WEAPON_CLASS);
case 155:return(uint64_t)(invlet_basic);
case 156:return(uint64_t)(st_all);
case 157:return(uint64_t)(st_corpse);
case 158:return(uint64_t)(st_gloves);
case 159:return(uint64_t)(st_petrifies);
case 160:return(uint64_t)(st_resists);
default:abort();}}
uint64_t teleport_pickup_read(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->his);
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_void);
case 1:return(uint64_t)(uintptr_t)(p->a_obj);
case 2:return(uint64_t)(uintptr_t)(p->a_monst);
case 3:return(uint64_t)(uintptr_t)(p->a_int);
case 4:return(uint64_t)(uintptr_t)(p->a_xint16);
case 5:return(uint64_t)(uintptr_t)(p->a_xint8);
case 6:return(uint64_t)(uintptr_t)(p->a_char);
case 7:return(uint64_t)(uintptr_t)(p->a_schar);
case 8:return(uint64_t)(uintptr_t)(p->a_uchar);
case 9:return(uint64_t)(uintptr_t)(p->a_uint);
case 10:return(uint64_t)(uintptr_t)(p->a_long);
case 11:return(uint64_t)(uintptr_t)(p->a_ulong);
case 12:return(uint64_t)(uintptr_t)(p->a_coordxy);
case 13:return(uint64_t)(uintptr_t)(p->a_iptr);
case 14:return(uint64_t)(uintptr_t)(p->a_xint16ptr);
case 15:return(uint64_t)(uintptr_t)(p->a_xint8ptr);
case 16:return(uint64_t)(uintptr_t)(p->a_lptr);
case 17:return(uint64_t)(uintptr_t)(p->a_coordxyptr);
case 18:return(uint64_t)(uintptr_t)(p->a_ulptr);
case 19:return(uint64_t)(uintptr_t)(p->a_uptr);
case 20:return(uint64_t)(uintptr_t)(p->a_string);
case 21:return(uint64_t)(uintptr_t)(p->a_nfunc);
case 22:return(uint64_t)(uintptr_t)(p->a_mask32);
case 23:return(uint64_t)(uintptr_t)(p->a_int64);
case 24:return(uint64_t)(uintptr_t)(p->a_uint64);
default:abort();}}
case 3:{struct autopickup_exception*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->regex);
case 1:return(uint64_t)(uintptr_t)(p->grab);
case 2:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->c_nothing_happens);
case 1:return(uint64_t)(uintptr_t)(p->c_nothing_seems_to_happen);
case 2:return(uint64_t)(uintptr_t)(p->c_something);
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sym);
default:abort();}}
case 6:{struct classic_representation*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->color);
case 1:return(uint64_t)(uintptr_t)(p->symidx);
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroobj);
case 1:return(uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 8:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->run);
case 1:return(uint64_t)(uintptr_t)(p->nopick);
case 2:return(uint64_t)(uintptr_t)(p->mon_moving);
default:abort();}}
case 9:{struct display_hints*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->botl);
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(p->objlist);
case 4:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->female);
case 1:return(uint64_t)(uintptr_t)(p->goldX);
case 2:return(uint64_t)(uintptr_t)(p->invlet_constant);
case 3:return(uint64_t)(uintptr_t)(p->mention_decor);
case 4:return(uint64_t)(uintptr_t)(p->nopick_dropped);
case 5:return(uint64_t)(uintptr_t)(p->pickup);
case 6:return(uint64_t)(uintptr_t)(p->pickup_stolen);
case 7:return(uint64_t)(uintptr_t)(p->pickup_thrown);
case 8:return(uint64_t)(uintptr_t)(p->sortpack);
case 9:return(uint64_t)(uintptr_t)(p->verbose);
case 10:return(uint64_t)(uintptr_t)(p->autounlock);
case 11:return(uint64_t)(uintptr_t)(p->paranoia_bits);
case 12:return(uint64_t)(uintptr_t)(p->pickup_burden);
case 13:return(uint64_t)(uintptr_t)(p->sortloot);
case 14:return(uint64_t)(uintptr_t)(&p->inv_order);
case 15:return(uint64_t)(uintptr_t)(&p->pickup_types);
case 16:return(uint64_t)(uintptr_t)(p->menu_style);
case 17:return(uint64_t)(uintptr_t)(p->lootabc);
default:abort();}}
case 12:{struct glyph_map_entry*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyphflags);
case 1:return(uint64_t)(uintptr_t)(&p->sym);
case 2:return(uint64_t)(uintptr_t)(p->customcolor);
case 3:return(uint64_t)(uintptr_t)(p->color256idx);
case 4:return(uint64_t)(uintptr_t)(p->tileidx);
case 5:return(uint64_t)(uintptr_t)(p->u);
default:abort();}}
case 13:{struct glyphinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
case 1:return(uint64_t)(uintptr_t)(p->ttychar);
case 2:return(uint64_t)(uintptr_t)(p->framecolor);
case 3:return(uint64_t)(uintptr_t)(&p->gm);
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
case 1:return(uint64_t)(uintptr_t)(p->suppress_price);
case 2:return(uint64_t)(uintptr_t)(p->defer_decor);
case 3:return(uint64_t)(uintptr_t)(p->menu_head_objsym);
case 4:return(uint64_t)(uintptr_t)(p->menu_requested);
case 5:return(uint64_t)(uintptr_t)(p->prev_decor);
case 6:return(uint64_t)(uintptr_t)(p->cmdassist);
default:abort();}}
case 15:{struct instance_globals_a*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->apelist);
case 1:return(uint64_t)(uintptr_t)(p->A_first_hint);
case 2:return(uint64_t)(uintptr_t)(p->A_second_hint);
case 3:return(uint64_t)(uintptr_t)(p->abort_looting);
default:abort();}}
case 16:{struct instance_globals_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->bucx_filter);
default:abort();}}
case 17:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->current_container);
case 1:return(uint64_t)(uintptr_t)(p->class_filter);
default:abort();}}
case 18:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->decor_fumble_override);
case 1:return(uint64_t)(uintptr_t)(p->decor_levitate_override);
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 20:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->loot_reset_justpicked);
default:abort();}}
case 21:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->multi);
case 1:return(uint64_t)(uintptr_t)(p->multi_reason);
case 2:return(uint64_t)(uintptr_t)(p->mrg_to_wielded);
default:abort();}}
case 22:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nomovemsg);
default:abort();}}
case 23:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->otg_temp);
case 1:return(uint64_t)(uintptr_t)(p->otg_otmp);
case 2:return(uint64_t)(uintptr_t)(p->oldcap);
default:abort();}}
case 24:{struct instance_globals_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->picked_filter);
case 1:return(uint64_t)(uintptr_t)(p->pickup_encumbrance);
default:abort();}}
case 25:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sellobj_first);
case 1:return(uint64_t)(uintptr_t)(p->shop_filter);
default:abort();}}
case 26:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 27:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->lastseentyp);
case 1:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 28:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->moves);
default:abort();}}
case 29:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->this_title);
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
default:abort();}}
case 31:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->val_for_n_or_more);
case 1:return(uint64_t)(uintptr_t)(&p->valid_menu_classes);
default:abort();}}
case 32:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 33:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sokoban_rules);
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->item);
case 1:return(uint64_t)(uintptr_t)(p->count);
case 2:return(uint64_t)(uintptr_t)(p->itemflags);
default:abort();}}
case 35:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->female);
case 2:return(uint64_t)(uintptr_t)(p->mcan);
case 3:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 4:return(uint64_t)(uintptr_t)(p->minvent);
default:abort();}}
case 36:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 37:{struct obj*p=at;switch(field){
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
case 19:return(uint64_t)(uintptr_t)(p->recharged);
case 20:return(uint64_t)(uintptr_t)(p->lamplit);
case 21:return(uint64_t)(uintptr_t)(p->known);
case 22:return(uint64_t)(uintptr_t)(p->dknown);
case 23:return(uint64_t)(uintptr_t)(p->bknown);
case 24:return(uint64_t)(uintptr_t)(p->rknown);
case 25:return(uint64_t)(uintptr_t)(p->cknown);
case 26:return(uint64_t)(uintptr_t)(p->lknown);
case 27:return(uint64_t)(uintptr_t)(p->tknown);
case 28:return(uint64_t)(uintptr_t)(p->nomerge);
case 29:return(uint64_t)(uintptr_t)(p->oeroded);
case 30:return(uint64_t)(uintptr_t)(p->oeroded2);
case 31:return(uint64_t)(uintptr_t)(p->oerodeproof);
case 32:return(uint64_t)(uintptr_t)(p->olocked);
case 33:return(uint64_t)(uintptr_t)(p->obroken);
case 34:return(uint64_t)(uintptr_t)(p->otrapped);
case 35:return(uint64_t)(uintptr_t)(p->globby);
case 36:return(uint64_t)(uintptr_t)(p->greased);
case 37:return(uint64_t)(uintptr_t)(p->in_use);
case 38:return(uint64_t)(uintptr_t)(p->bypass);
case 39:return(uint64_t)(uintptr_t)(p->pickup_prev);
case 40:return(uint64_t)(uintptr_t)(p->ghostly);
case 41:return(uint64_t)(uintptr_t)(p->how_lost);
case 42:return(uint64_t)(uintptr_t)(p->named_how);
case 43:return(uint64_t)(uintptr_t)(p->corpsenm);
case 44:return(uint64_t)(uintptr_t)(p->usecount);
case 45:return(uint64_t)(uintptr_t)(p->oeaten);
case 46:return(uint64_t)(uintptr_t)(p->age);
case 47:return(uint64_t)(uintptr_t)(p->owornmask);
case 48:return(uint64_t)(uintptr_t)(p->lua_ref_cnt);
case 49:return(uint64_t)(uintptr_t)(p->omigr_from_dnum);
case 50:return(uint64_t)(uintptr_t)(p->omigr_from_dlevel);
case 51:return(uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 38:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name_known);
case 1:return(uint64_t)(uintptr_t)(p->oc_subtyp);
case 2:return(uint64_t)(uintptr_t)(p->oc_class);
default:abort();}}
case 39:{struct oextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->omonst);
default:abort();}}
case 40:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->pmidx);
case 1:return(uint64_t)(uintptr_t)(p->msize);
case 2:return(uint64_t)(uintptr_t)(p->mflags1);
case 3:return(uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 41:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 42:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 43:{struct skills*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->skill);
default:abort();}}
case 44:{struct sortloot_item*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->obj);
case 1:return(uint64_t)(uintptr_t)(p->str);
case 2:return(uint64_t)(uintptr_t)(p->indx);
case 3:return(uint64_t)(uintptr_t)(p->orderclass);
case 4:return(uint64_t)(uintptr_t)(p->subclass);
case 5:return(uint64_t)(uintptr_t)(p->disco);
case 6:return(uint64_t)(uintptr_t)(p->inuse);
default:abort();}}
case 45:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ttyp);
default:abort();}}
case 46:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
case 1:return(uint64_t)(uintptr_t)(p->v_ocontainer);
case 2:return(uint64_t)(uintptr_t)(p->v_ocarry);
default:abort();}}
case 47:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 1:return(uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 2:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 3:return(uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 4:return(uint64_t)(uintptr_t)(p->win_putstr);
case 5:return(uint64_t)(uintptr_t)(p->win_start_menu);
case 6:return(uint64_t)(uintptr_t)(p->win_end_menu);
default:abort();}}
case 48:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(p->dz);
case 3:return(uint64_t)(uintptr_t)(&p->ushops);
case 4:return(uint64_t)(uintptr_t)(&p->uprops);
case 5:return(uint64_t)(uintptr_t)(p->uswallow);
case 6:return(uint64_t)(uintptr_t)(p->uinwater);
case 7:return(uint64_t)(uintptr_t)(p->ustuck);
case 8:return(uint64_t)(uintptr_t)(p->usteed);
case 9:return(uint64_t)(uintptr_t)(&p->weapon_skills);
default:abort();}}
default:abort();}}
void teleport_pickup_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:p->his=(__typeof__(p->his))value;return;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 2:{union any*p=at;switch(field){
case 0:p->a_void=(__typeof__(p->a_void))value;return;
case 1:p->a_obj=(__typeof__(p->a_obj))value;return;
case 2:p->a_monst=(__typeof__(p->a_monst))value;return;
case 3:p->a_int=(__typeof__(p->a_int))value;return;
case 4:p->a_xint16=(__typeof__(p->a_xint16))value;return;
case 5:p->a_xint8=(__typeof__(p->a_xint8))value;return;
case 6:p->a_char=(__typeof__(p->a_char))value;return;
case 7:p->a_schar=(__typeof__(p->a_schar))value;return;
case 8:p->a_uchar=(__typeof__(p->a_uchar))value;return;
case 9:p->a_uint=(__typeof__(p->a_uint))value;return;
case 10:p->a_long=(__typeof__(p->a_long))value;return;
case 11:p->a_ulong=(__typeof__(p->a_ulong))value;return;
case 12:p->a_coordxy=(__typeof__(p->a_coordxy))value;return;
case 13:p->a_iptr=(__typeof__(p->a_iptr))value;return;
case 14:p->a_xint16ptr=(__typeof__(p->a_xint16ptr))value;return;
case 15:p->a_xint8ptr=(__typeof__(p->a_xint8ptr))value;return;
case 16:p->a_lptr=(__typeof__(p->a_lptr))value;return;
case 17:p->a_coordxyptr=(__typeof__(p->a_coordxyptr))value;return;
case 18:p->a_ulptr=(__typeof__(p->a_ulptr))value;return;
case 19:p->a_uptr=(__typeof__(p->a_uptr))value;return;
case 20:p->a_string=(__typeof__(p->a_string))value;return;
case 21:p->a_nfunc=(__typeof__(p->a_nfunc))value;return;
case 22:p->a_mask32=(__typeof__(p->a_mask32))value;return;
case 23:p->a_int64=(__typeof__(p->a_int64))value;return;
case 24:p->a_uint64=(__typeof__(p->a_uint64))value;return;
default:abort();}}
case 3:{struct autopickup_exception*p=at;switch(field){
case 0:p->regex=(__typeof__(p->regex))value;return;
case 1:p->grab=(__typeof__(p->grab))value;return;
case 2:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:p->sym=(__typeof__(p->sym))value;return;
default:abort();}}
case 6:{struct classic_representation*p=at;switch(field){
case 0:p->color=(__typeof__(p->color))value;return;
case 1:p->symidx=(__typeof__(p->symidx))value;return;
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
default:abort();}}
case 8:{struct context_info*p=at;switch(field){
case 0:p->run=(__typeof__(p->run))value;return;
case 1:p->nopick=(__typeof__(p->nopick))value;return;
case 2:p->mon_moving=(__typeof__(p->mon_moving))value;return;
default:abort();}}
case 9:{struct display_hints*p=at;switch(field){
case 0:p->botl=(__typeof__(p->botl))value;return;
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(__typeof__(p->objlist))value;return;
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:p->female=(__typeof__(p->female))value;return;
case 1:p->goldX=(__typeof__(p->goldX))value;return;
case 2:p->invlet_constant=(__typeof__(p->invlet_constant))value;return;
case 3:p->mention_decor=(__typeof__(p->mention_decor))value;return;
case 4:p->nopick_dropped=(__typeof__(p->nopick_dropped))value;return;
case 5:p->pickup=(__typeof__(p->pickup))value;return;
case 6:p->pickup_stolen=(__typeof__(p->pickup_stolen))value;return;
case 7:p->pickup_thrown=(__typeof__(p->pickup_thrown))value;return;
case 8:p->sortpack=(__typeof__(p->sortpack))value;return;
case 9:p->verbose=(__typeof__(p->verbose))value;return;
case 10:p->autounlock=(__typeof__(p->autounlock))value;return;
case 11:p->paranoia_bits=(__typeof__(p->paranoia_bits))value;return;
case 12:p->pickup_burden=(__typeof__(p->pickup_burden))value;return;
case 13:p->sortloot=(__typeof__(p->sortloot))value;return;
case 16:p->menu_style=(__typeof__(p->menu_style))value;return;
case 17:p->lootabc=(__typeof__(p->lootabc))value;return;
default:abort();}}
case 12:{struct glyph_map_entry*p=at;switch(field){
case 0:p->glyphflags=(__typeof__(p->glyphflags))value;return;
case 2:p->customcolor=(__typeof__(p->customcolor))value;return;
case 3:p->color256idx=(__typeof__(p->color256idx))value;return;
case 4:p->tileidx=(__typeof__(p->tileidx))value;return;
case 5:p->u=(__typeof__(p->u))value;return;
default:abort();}}
case 13:{struct glyphinfo*p=at;switch(field){
case 0:p->glyph=(__typeof__(p->glyph))value;return;
case 1:p->ttychar=(__typeof__(p->ttychar))value;return;
case 2:p->framecolor=(__typeof__(p->framecolor))value;return;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(__typeof__(p->last_msg))value;return;
case 1:p->suppress_price=(__typeof__(p->suppress_price))value;return;
case 2:p->defer_decor=(__typeof__(p->defer_decor))value;return;
case 3:p->menu_head_objsym=(__typeof__(p->menu_head_objsym))value;return;
case 4:p->menu_requested=(__typeof__(p->menu_requested))value;return;
case 5:p->prev_decor=(__typeof__(p->prev_decor))value;return;
case 6:p->cmdassist=(__typeof__(p->cmdassist))value;return;
default:abort();}}
case 15:{struct instance_globals_a*p=at;switch(field){
case 0:p->apelist=(__typeof__(p->apelist))value;return;
case 1:p->A_first_hint=(__typeof__(p->A_first_hint))value;return;
case 2:p->A_second_hint=(__typeof__(p->A_second_hint))value;return;
case 3:p->abort_looting=(__typeof__(p->abort_looting))value;return;
default:abort();}}
case 16:{struct instance_globals_b*p=at;switch(field){
case 0:p->bucx_filter=(__typeof__(p->bucx_filter))value;return;
default:abort();}}
case 17:{struct instance_globals_c*p=at;switch(field){
case 0:p->current_container=(__typeof__(p->current_container))value;return;
case 1:p->class_filter=(__typeof__(p->class_filter))value;return;
default:abort();}}
case 18:{struct instance_globals_d*p=at;switch(field){
case 0:p->decor_fumble_override=(__typeof__(p->decor_fumble_override))value;return;
case 1:p->decor_levitate_override=(__typeof__(p->decor_levitate_override))value;return;
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(__typeof__(p->invent))value;return;
default:abort();}}
case 20:{struct instance_globals_l*p=at;switch(field){
case 0:p->loot_reset_justpicked=(__typeof__(p->loot_reset_justpicked))value;return;
default:abort();}}
case 21:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=(__typeof__(p->multi))value;return;
case 1:p->multi_reason=(__typeof__(p->multi_reason))value;return;
case 2:p->mrg_to_wielded=(__typeof__(p->mrg_to_wielded))value;return;
default:abort();}}
case 22:{struct instance_globals_n*p=at;switch(field){
case 0:p->nomovemsg=(__typeof__(p->nomovemsg))value;return;
default:abort();}}
case 23:{struct instance_globals_o*p=at;switch(field){
case 0:p->otg_temp=(__typeof__(p->otg_temp))value;return;
case 1:p->otg_otmp=(__typeof__(p->otg_otmp))value;return;
case 2:p->oldcap=(__typeof__(p->oldcap))value;return;
default:abort();}}
case 24:{struct instance_globals_p*p=at;switch(field){
case 0:p->picked_filter=(__typeof__(p->picked_filter))value;return;
case 1:p->pickup_encumbrance=(__typeof__(p->pickup_encumbrance))value;return;
default:abort();}}
case 25:{struct instance_globals_s*p=at;switch(field){
case 0:p->sellobj_first=(__typeof__(p->sellobj_first))value;return;
case 1:p->shop_filter=(__typeof__(p->shop_filter))value;return;
default:abort();}}
case 26:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 28:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=(__typeof__(p->moves))value;return;
default:abort();}}
case 29:{struct instance_globals_t*p=at;switch(field){
case 0:p->this_title=(__typeof__(p->this_title))value;return;
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 31:{struct instance_globals_v*p=at;switch(field){
case 0:p->val_for_n_or_more=(__typeof__(p->val_for_n_or_more))value;return;
default:abort();}}
case 32:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 33:{struct levelflags*p=at;switch(field){
case 0:p->sokoban_rules=(unsigned int)value;return;
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 1:p->count=(__typeof__(p->count))value;return;
case 2:p->itemflags=(__typeof__(p->itemflags))value;return;
default:abort();}}
case 35:{struct monst*p=at;switch(field){
case 0:p->data=(__typeof__(p->data))value;return;
case 1:p->female=(unsigned int)value;return;
case 2:p->mcan=(unsigned int)value;return;
case 3:p->mpeaceful=(unsigned int)value;return;
case 4:p->minvent=(__typeof__(p->minvent))value;return;
default:abort();}}
case 36:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 37:{struct obj*p=at;switch(field){
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
case 19:p->recharged=(unsigned int)value;return;
case 20:p->lamplit=(unsigned int)value;return;
case 21:p->known=(unsigned int)value;return;
case 22:p->dknown=(unsigned int)value;return;
case 23:p->bknown=(unsigned int)value;return;
case 24:p->rknown=(unsigned int)value;return;
case 25:p->cknown=(unsigned int)value;return;
case 26:p->lknown=(unsigned int)value;return;
case 27:p->tknown=(unsigned int)value;return;
case 28:p->nomerge=(unsigned int)value;return;
case 29:p->oeroded=(unsigned int)value;return;
case 30:p->oeroded2=(unsigned int)value;return;
case 31:p->oerodeproof=(unsigned int)value;return;
case 32:p->olocked=(unsigned int)value;return;
case 33:p->obroken=(unsigned int)value;return;
case 34:p->otrapped=(unsigned int)value;return;
case 35:p->globby=(unsigned int)value;return;
case 36:p->greased=(unsigned int)value;return;
case 37:p->in_use=(unsigned int)value;return;
case 38:p->bypass=(unsigned int)value;return;
case 39:p->pickup_prev=(unsigned int)value;return;
case 40:p->ghostly=(unsigned int)value;return;
case 41:p->how_lost=(unsigned int)value;return;
case 42:p->named_how=(unsigned int)value;return;
case 43:p->corpsenm=(__typeof__(p->corpsenm))value;return;
case 44:p->usecount=(__typeof__(p->usecount))value;return;
case 45:p->oeaten=(__typeof__(p->oeaten))value;return;
case 46:p->age=(__typeof__(p->age))value;return;
case 47:p->owornmask=(__typeof__(p->owornmask))value;return;
case 48:p->lua_ref_cnt=(__typeof__(p->lua_ref_cnt))value;return;
case 49:p->omigr_from_dnum=(__typeof__(p->omigr_from_dnum))value;return;
case 50:p->omigr_from_dlevel=(__typeof__(p->omigr_from_dlevel))value;return;
case 51:p->oextra=(__typeof__(p->oextra))value;return;
default:abort();}}
case 38:{struct objclass*p=at;switch(field){
case 0:p->oc_name_known=(unsigned int)value;return;
case 1:p->oc_subtyp=(__typeof__(p->oc_subtyp))value;return;
case 2:p->oc_class=(__typeof__(p->oc_class))value;return;
default:abort();}}
case 39:{struct oextra*p=at;switch(field){
case 0:p->omonst=(__typeof__(p->omonst))value;return;
default:abort();}}
case 40:{struct permonst*p=at;switch(field){
case 1:p->msize=(__typeof__(p->msize))value;return;
case 2:p->mflags1=(__typeof__(p->mflags1))value;return;
case 3:p->mflags2=(__typeof__(p->mflags2))value;return;
default:abort();}}
case 41:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(__typeof__(p->extrinsic))value;return;
case 1:p->blocked=(__typeof__(p->blocked))value;return;
case 2:p->intrinsic=(__typeof__(p->intrinsic))value;return;
default:abort();}}
case 42:{struct rm*p=at;switch(field){
case 0:p->typ=(__typeof__(p->typ))value;return;
case 1:p->flags=(unsigned int)value;return;
default:abort();}}
case 43:{struct skills*p=at;switch(field){
case 0:p->skill=(__typeof__(p->skill))value;return;
default:abort();}}
case 44:{struct sortloot_item*p=at;switch(field){
case 0:p->obj=(__typeof__(p->obj))value;return;
case 1:p->str=(__typeof__(p->str))value;return;
case 2:p->indx=(__typeof__(p->indx))value;return;
case 3:p->orderclass=(__typeof__(p->orderclass))value;return;
case 4:p->subclass=(__typeof__(p->subclass))value;return;
case 5:p->disco=(__typeof__(p->disco))value;return;
case 6:p->inuse=(__typeof__(p->inuse))value;return;
default:abort();}}
case 45:{struct trap*p=at;switch(field){
case 0:p->ttyp=(unsigned int)value;return;
default:abort();}}
case 46:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(__typeof__(p->v_nexthere))value;return;
case 1:p->v_ocontainer=(__typeof__(p->v_ocontainer))value;return;
case 2:p->v_ocarry=(__typeof__(p->v_ocarry))value;return;
default:abort();}}
case 47:{struct window_procs*p=at;switch(field){
case 0:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))value;return;
case 1:p->win_clear_nhwindow=(__typeof__(p->win_clear_nhwindow))value;return;
case 2:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 3:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))value;return;
case 4:p->win_putstr=(__typeof__(p->win_putstr))value;return;
case 5:p->win_start_menu=(__typeof__(p->win_start_menu))value;return;
case 6:p->win_end_menu=(__typeof__(p->win_end_menu))value;return;
default:abort();}}
case 48:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 2:p->dz=(__typeof__(p->dz))value;return;
case 5:p->uswallow=(unsigned int)value;return;
case 6:p->uinwater=(unsigned int)value;return;
case 7:p->ustuck=(__typeof__(p->ustuck))value;return;
case 8:p->usteed=(__typeof__(p->usteed))value;return;
default:abort();}}
default:abort();}}
void* teleport_pickup_address(int kind,void*at,int field){switch(kind){
case 0:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->his;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{union any*p=at;switch(field){
case 0:return(void*)&p->a_void;
case 1:return(void*)&p->a_obj;
case 2:return(void*)&p->a_monst;
case 3:return(void*)&p->a_int;
case 4:return(void*)&p->a_xint16;
case 5:return(void*)&p->a_xint8;
case 6:return(void*)&p->a_char;
case 7:return(void*)&p->a_schar;
case 8:return(void*)&p->a_uchar;
case 9:return(void*)&p->a_uint;
case 10:return(void*)&p->a_long;
case 11:return(void*)&p->a_ulong;
case 12:return(void*)&p->a_coordxy;
case 13:return(void*)&p->a_iptr;
case 14:return(void*)&p->a_xint16ptr;
case 15:return(void*)&p->a_xint8ptr;
case 16:return(void*)&p->a_lptr;
case 17:return(void*)&p->a_coordxyptr;
case 18:return(void*)&p->a_ulptr;
case 19:return(void*)&p->a_uptr;
case 20:return(void*)&p->a_string;
case 21:return(void*)&p->a_nfunc;
case 22:return(void*)&p->a_mask32;
case 23:return(void*)&p->a_int64;
case 24:return(void*)&p->a_uint64;
default:abort();}}
case 3:{struct autopickup_exception*p=at;switch(field){
case 0:return(void*)&p->regex;
case 1:return(void*)&p->grab;
case 2:return(void*)&p->next;
default:abort();}}
case 4:{struct c_common_strings*p=at;switch(field){
case 0:return(void*)&p->c_nothing_happens;
case 1:return(void*)&p->c_nothing_seems_to_happen;
case 2:return(void*)&p->c_something;
default:abort();}}
case 5:{struct class_sym*p=at;switch(field){
case 0:return(void*)&p->sym;
default:abort();}}
case 6:{struct classic_representation*p=at;switch(field){
case 0:return(void*)&p->color;
case 1:return(void*)&p->symidx;
default:abort();}}
case 7:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroobj;
case 1:return(void*)&p->zeroany;
default:abort();}}
case 8:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->run;
case 1:return(void*)&p->nopick;
case 2:return(void*)&p->mon_moving;
default:abort();}}
case 9:{struct display_hints*p=at;switch(field){
case 0:return(void*)&p->botl;
default:abort();}}
case 10:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->objlist;
case 4:return(void*)&p->flags;
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(void*)&p->female;
case 1:return(void*)&p->goldX;
case 2:return(void*)&p->invlet_constant;
case 3:return(void*)&p->mention_decor;
case 4:return(void*)&p->nopick_dropped;
case 5:return(void*)&p->pickup;
case 6:return(void*)&p->pickup_stolen;
case 7:return(void*)&p->pickup_thrown;
case 8:return(void*)&p->sortpack;
case 9:return(void*)&p->verbose;
case 10:return(void*)&p->autounlock;
case 11:return(void*)&p->paranoia_bits;
case 12:return(void*)&p->pickup_burden;
case 13:return(void*)&p->sortloot;
case 14:return(void*)&p->inv_order;
case 15:return(void*)&p->pickup_types;
case 16:return(void*)&p->menu_style;
case 17:return(void*)&p->lootabc;
default:abort();}}
case 12:{struct glyph_map_entry*p=at;switch(field){
case 0:return(void*)&p->glyphflags;
case 1:return(void*)&p->sym;
case 2:return(void*)&p->customcolor;
case 3:return(void*)&p->color256idx;
case 4:return(void*)&p->tileidx;
case 5:return(void*)&p->u;
default:abort();}}
case 13:{struct glyphinfo*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->ttychar;
case 2:return(void*)&p->framecolor;
case 3:return(void*)&p->gm;
default:abort();}}
case 14:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
case 1:return(void*)&p->suppress_price;
case 2:return(void*)&p->defer_decor;
case 3:return(void*)&p->menu_head_objsym;
case 4:return(void*)&p->menu_requested;
case 5:return(void*)&p->prev_decor;
case 6:return(void*)&p->cmdassist;
default:abort();}}
case 15:{struct instance_globals_a*p=at;switch(field){
case 0:return(void*)&p->apelist;
case 1:return(void*)&p->A_first_hint;
case 2:return(void*)&p->A_second_hint;
case 3:return(void*)&p->abort_looting;
default:abort();}}
case 16:{struct instance_globals_b*p=at;switch(field){
case 0:return(void*)&p->bucx_filter;
default:abort();}}
case 17:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->current_container;
case 1:return(void*)&p->class_filter;
default:abort();}}
case 18:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->decor_fumble_override;
case 1:return(void*)&p->decor_levitate_override;
default:abort();}}
case 19:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->invent;
default:abort();}}
case 20:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->loot_reset_justpicked;
default:abort();}}
case 21:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->multi;
case 1:return(void*)&p->multi_reason;
case 2:return(void*)&p->mrg_to_wielded;
default:abort();}}
case 22:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nomovemsg;
default:abort();}}
case 23:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->otg_temp;
case 1:return(void*)&p->otg_otmp;
case 2:return(void*)&p->oldcap;
default:abort();}}
case 24:{struct instance_globals_p*p=at;switch(field){
case 0:return(void*)&p->picked_filter;
case 1:return(void*)&p->pickup_encumbrance;
default:abort();}}
case 25:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->sellobj_first;
case 1:return(void*)&p->shop_filter;
default:abort();}}
case 26:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 27:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->lastseentyp;
case 1:return(void*)&p->level;
default:abort();}}
case 28:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->moves;
default:abort();}}
case 29:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->this_title;
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
default:abort();}}
case 31:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->val_for_n_or_more;
case 1:return(void*)&p->valid_menu_classes;
default:abort();}}
case 32:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 33:{struct levelflags*p=at;switch(field){
default:abort();}}
case 34:{struct mi*p=at;switch(field){
case 0:return(void*)&p->item;
case 1:return(void*)&p->count;
case 2:return(void*)&p->itemflags;
default:abort();}}
case 35:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 4:return(void*)&p->minvent;
default:abort();}}
case 36:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 37:{struct obj*p=at;switch(field){
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
case 43:return(void*)&p->corpsenm;
case 44:return(void*)&p->usecount;
case 45:return(void*)&p->oeaten;
case 46:return(void*)&p->age;
case 47:return(void*)&p->owornmask;
case 48:return(void*)&p->lua_ref_cnt;
case 49:return(void*)&p->omigr_from_dnum;
case 50:return(void*)&p->omigr_from_dlevel;
case 51:return(void*)&p->oextra;
default:abort();}}
case 38:{struct objclass*p=at;switch(field){
case 1:return(void*)&p->oc_subtyp;
case 2:return(void*)&p->oc_class;
default:abort();}}
case 39:{struct oextra*p=at;switch(field){
case 0:return(void*)&p->omonst;
default:abort();}}
case 40:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->pmidx;
case 1:return(void*)&p->msize;
case 2:return(void*)&p->mflags1;
case 3:return(void*)&p->mflags2;
default:abort();}}
case 41:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 42:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
default:abort();}}
case 43:{struct skills*p=at;switch(field){
case 0:return(void*)&p->skill;
default:abort();}}
case 44:{struct sortloot_item*p=at;switch(field){
case 0:return(void*)&p->obj;
case 1:return(void*)&p->str;
case 2:return(void*)&p->indx;
case 3:return(void*)&p->orderclass;
case 4:return(void*)&p->subclass;
case 5:return(void*)&p->disco;
case 6:return(void*)&p->inuse;
default:abort();}}
case 45:{struct trap*p=at;switch(field){
default:abort();}}
case 46:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
case 1:return(void*)&p->v_ocontainer;
case 2:return(void*)&p->v_ocarry;
default:abort();}}
case 47:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_create_nhwindow;
case 1:return(void*)&p->win_clear_nhwindow;
case 2:return(void*)&p->win_display_nhwindow;
case 3:return(void*)&p->win_destroy_nhwindow;
case 4:return(void*)&p->win_putstr;
case 5:return(void*)&p->win_start_menu;
case 6:return(void*)&p->win_end_menu;
default:abort();}}
case 48:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->dz;
case 3:return(void*)&p->ushops;
case 4:return(void*)&p->uprops;
case 7:return(void*)&p->ustuck;
case 8:return(void*)&p->usteed;
case 9:return(void*)&p->weapon_skills;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_pickup_var0(char * a0){(impossible)(a0);}
void teleport_pickup_var1(char * a0,char * a1){(pline)(a0,a1);}
int teleport_pickup_var2(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_pickup_var3(char * a0,int a1,char * a2){(There)(a0,a1,a2);}
void teleport_pickup_var4(char * a0,int a1){(You)(a0,a1);}
void teleport_pickup_var5(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var6(char * a0,char * a1){(pline)(a0,a1);}
int teleport_pickup_var7(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var8(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var9(char * a0,char * a1){(Norep)(a0,a1);}
void teleport_pickup_var10(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var11(char * a0){(You)(a0);}
int teleport_pickup_var12(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var13(char * a0,char * a1){(There)(a0,a1);}
int teleport_pickup_var14(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var15(char * a0){(You_cant)(a0);}
void teleport_pickup_var16(char * a0,char * a1){(You_cant)(a0,a1);}
void teleport_pickup_var17(char * a0){(pline)(a0);}
void teleport_pickup_var18(char * a0){(impossible)(a0);}
int teleport_pickup_var19(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var20(char * a0){(pline)(a0);}
void teleport_pickup_var21(char * a0){(panic)(a0);}
int teleport_pickup_var22(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var23(char * a0,char * a1,char * a2,char * a3,char * a4){(You)(a0,a1,a2,a3,a4);}
void teleport_pickup_var24(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5,char * a6,char * a7){(There)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_pickup_var25(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var26(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var27(char * a0,char * a1){(Your)(a0,a1);}
int teleport_pickup_var28(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_pickup_var29(char * a0,long a1,long a2){(impossible)(a0,a1,a2);}
void teleport_pickup_var30(char * a0,char * a1){(You_cant)(a0,a1);}
void teleport_pickup_var31(char * a0,char * a1,char * a2,char * a3,char * a4){(pline_The)(a0,a1,a2,a3,a4);}
int teleport_pickup_var32(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_pickup_var33(char * a0){(Your)(a0);}
void teleport_pickup_var34(char * a0){(You)(a0);}
void teleport_pickup_var35(char * a0,char * a1){(You)(a0,a1);}
void teleport_pickup_var36(char * a0,char * a1){(You)(a0,a1);}
void teleport_pickup_var37(char * a0){(Your)(a0);}
void teleport_pickup_var38(char * a0){(Your)(a0);}
void teleport_pickup_var39(char * a0){(You)(a0);}
void teleport_pickup_var40(char * a0,char * a1){(You)(a0,a1);}
void teleport_pickup_var41(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var42(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var43(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var44(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var45(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var46(char * a0,char * a1){(You)(a0,a1);}
void teleport_pickup_var47(char * a0){(pline)(a0);}
void teleport_pickup_var48(char * a0){(You)(a0);}
void teleport_pickup_var49(char * a0){(pline)(a0);}
void teleport_pickup_var50(char * a0){(You)(a0);}
void teleport_pickup_var51(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var52(char * a0,char * a1,char * a2){(You_cant)(a0,a1,a2);}
void teleport_pickup_var53(char * a0){(You)(a0);}
void teleport_pickup_var54(char * a0,char * a1,char * a2,char * a3){(You)(a0,a1,a2,a3);}
void teleport_pickup_var55(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var56(char * a0){(pline)(a0);}
void teleport_pickup_var57(char * a0){(verbalize)(a0);}
void teleport_pickup_var58(char * a0){(pline)(a0);}
void teleport_pickup_var59(char * a0,char * a1){(You)(a0,a1);}
int teleport_pickup_var60(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var61(char * a0){(You_cant)(a0);}
void teleport_pickup_var62(char * a0,char * a1){(You)(a0,a1);}
void teleport_pickup_var63(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var64(char * a0){(impossible)(a0);}
void teleport_pickup_var65(char * a0){(You)(a0);}
void teleport_pickup_var66(char * a0){(pline)(a0);}
void teleport_pickup_var67(char * a0,char * a1,char * a2){(Norep)(a0,a1,a2);}
void teleport_pickup_var68(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_pickup_var69(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var70(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var71(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var72(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_pickup_var73(char * a0,char * a1){(urgent_pline)(a0,a1);}
void teleport_pickup_var74(char * a0){(panic)(a0);}
void teleport_pickup_var75(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var76(char * a0){(impossible)(a0);}
void teleport_pickup_var77(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pickup_var78(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var79(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var80(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var81(char * a0,char * a1){(pline_The)(a0,a1);}
void teleport_pickup_var82(char * a0){(You)(a0);}
void teleport_pickup_var83(char * a0,char * a1){(You)(a0,a1);}
void teleport_pickup_var84(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var85(char * a0){(You)(a0);}
void teleport_pickup_var86(char * a0,char * a1){(You)(a0,a1);}
void teleport_pickup_var87(char * a0,long a1,char * a2){(You)(a0,a1,a2);}
int teleport_pickup_var88(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_pickup_var89(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var90(char * a0,char * a1,char * a2){(You)(a0,a1,a2);}
void teleport_pickup_var91(char * a0,char * a1){(pline)(a0,a1);}
int teleport_pickup_var92(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var93(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var94(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var95(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var96(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var97(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var98(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var99(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var100(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var101(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_pickup_var102(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var103(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_pickup_var104(char * a0,char * a1,char * a2){(pline_The)(a0,a1,a2);}
void teleport_pickup_var105(char * a0){(pline)(a0);}
void teleport_pickup_var106(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var107(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_pickup_var108(char * a0,char * a1,int a2){(pline)(a0,a1,a2);}
void teleport_pickup_var109(long a0,char * a1,char * a2){(livelog_printf)(a0,a1,a2);}
void teleport_pickup_var110(char * a0,char * a1,char * a2){(urgent_pline)(a0,a1,a2);}
void teleport_pickup_var111(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_pickup_var112(char * a0,char * a1,int a2){(pline)(a0,a1,a2);}
void teleport_pickup_var113(char * a0,long a1,char * a2){(You)(a0,a1,a2);}
int teleport_pickup_var114(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_pickup_var115(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_pickup_var116(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var117(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var118(char * a0,char * a1){(pline)(a0,a1);}
void teleport_pickup_var119(char * a0,char * a1){(pline)(a0,a1);}
int teleport_pickup_indirect0(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect1(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_pickup_indirect2(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_pickup_indirect3(void (*fn)(winid, boolean),int a0,signed char a1){fn(a0,a1);}
void teleport_pickup_indirect4(void (*fn)(winid),int a0){fn(a0);}
signed char teleport_pickup_indirect5(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
void teleport_pickup_indirect6(void (*fn)(winid, boolean),int a0,signed char a1){fn(a0,a1);}
signed char teleport_pickup_indirect7(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_pickup_indirect8(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect9(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
void teleport_pickup_indirect10(void (*fn)(winid),int a0){fn(a0);}
signed char teleport_pickup_indirect11(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
void teleport_pickup_indirect12(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_pickup_indirect13(void (*fn)(winid),int a0){fn(a0);}
signed char teleport_pickup_indirect14(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_pickup_indirect15(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect16(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
signed char teleport_pickup_indirect17(boolean (*fn)(struct obj *),struct obj * a0){return fn(a0);}
void teleport_pickup_indirect18(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_pickup_indirect19(void (*fn)(winid),int a0){fn(a0);}
void teleport_pickup_indirect20(void (*fn)(winid),int a0){fn(a0);}
int teleport_pickup_indirect21(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect22(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
void teleport_pickup_indirect23(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_pickup_indirect24(void (*fn)(winid),int a0){fn(a0);}
int teleport_pickup_indirect25(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect26(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_pickup_indirect27(void (*fn)(winid, boolean),int a0,signed char a1){fn(a0,a1);}
void teleport_pickup_indirect28(void (*fn)(winid),int a0){fn(a0);}
int teleport_pickup_indirect29(int (*fn)(struct obj *),struct obj * a0){return fn(a0);}
int teleport_pickup_indirect30(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect31(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
void teleport_pickup_indirect32(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_pickup_indirect33(void (*fn)(winid),int a0){fn(a0);}
int teleport_pickup_indirect34(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect35(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
void teleport_pickup_indirect36(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_pickup_indirect37(void (*fn)(winid),int a0){fn(a0);}
int teleport_pickup_indirect38(winid (*fn)(int),int a0){return fn(a0);}
void teleport_pickup_indirect39(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
void teleport_pickup_indirect40(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_pickup_indirect41(void (*fn)(winid),int a0){fn(a0);}
extern boolean teleport_pickup_all_but_uchain(struct obj * a0);
extern boolean allow_all(struct obj * a0);
extern boolean allow_category(struct obj * a0);
extern int ck_bag(struct obj * a0);
extern int teleport_pickup_in_container(struct obj * a0);
extern boolean teleport_pickup_n_or_more(struct obj * a0);
extern int teleport_pickup_out_container(struct obj * a0);
extern int teleport_pickup_stash_ok(struct obj * a0);
extern int teleport_pickup_tip_ok(struct obj * a0);
uintptr_t teleport_pickup_owned_pointer(int i){switch(i){
case 0:return(uintptr_t)(teleport_pickup_all_but_uchain);
case 1:return(uintptr_t)(allow_all);
case 2:return(uintptr_t)(allow_category);
case 3:return(uintptr_t)(ck_bag);
case 4:return(uintptr_t)(teleport_pickup_in_container);
case 5:return(uintptr_t)(teleport_pickup_n_or_more);
case 6:return(uintptr_t)(teleport_pickup_out_container);
case 7:return(uintptr_t)(teleport_pickup_stash_ok);
case 8:return(uintptr_t)(teleport_pickup_tip_ok);
default:abort();}}
uintptr_t teleport_pickup_native_pointer(int i){switch(i){
case 0:return(uintptr_t)(Yname2);
case 1:return(uintptr_t)(Ysimple_name2);
case 2:return(uintptr_t)(ansimpleoname);
case 3:return(uintptr_t)(doforce);
case 4:return(uintptr_t)(doname);
case 5:return(uintptr_t)(is_worn);
case 6:return(uintptr_t)(yname);
case 7:return(uintptr_t)(ysimple_name);
default:abort();}}
#pragma clang diagnostic pop
void teleport_pickup_free(void*p){(free)(p);}
static char pickup_literals[5198];
char*teleport_pickup_literal_storage(void){return pickup_literals;}
size_t teleport_pickup_literal_capacity(void){return sizeof pickup_literals;}
static char pickup_backing_0[26];
static char pickup_backing_1[17];
static char pickup_backing_2[22];
static char pickup_backing_3[28];
static int pickup_backing_4;
static signed char pickup_backing_5;
static char pickup_backing_6[19];
static char * pickup_backing_7[14];
static char pickup_backing_8[10];
static char pickup_backing_9[10];
void*teleport_pickup_storage(int i){switch(i){
case 0:return(void*)&pickup_backing_0;
case 1:return(void*)&pickup_backing_1;
case 2:return(void*)&pickup_backing_2;
case 3:return(void*)&pickup_backing_3;
case 4:return(void*)&pickup_backing_4;
case 5:return(void*)&pickup_backing_5;
case 6:return(void*)&pickup_backing_6;
case 7:return(void*)&pickup_backing_7;
case 8:return(void*)&pickup_backing_8;
case 9:return(void*)&pickup_backing_9;
default:abort();}}
