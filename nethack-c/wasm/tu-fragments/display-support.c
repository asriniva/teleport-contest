/* DISPLAY ABI/header/native dependency transport and zero backing only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#define TMP_AT_MAX_GLYPHS (COLNO*2)
struct tmp_glyph {
    coord saved[TMP_AT_MAX_GLYPHS]; /* previously updated positions */
    int sidx;                       /* index of next unused slot in saved[] */
    int style; /* either DISP_BEAM or DISP_FLASH or DISP_ALWAYS */
    int glyph; /* glyph to use when printing */
    struct tmp_glyph *prev;
};
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(size_t)==8,"DISPLAY memory64 LP64 ABI");
_Static_assert(sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"DISPLAY signed native scalar ABI");
void*teleport_display_global(int index){switch(index){
case 0:return(void*)&u;
case 1:return(void*)&svc;
case 2:return(void*)&gv;
case 3:return(void*)&flags;
case 4:return(void*)&svl;
case 5:return(void*)&svd;
case 6:return(void*)&iflags;
case 7:return(void*)&go;
case 8:return(void*)&cg;
case 9:return(void*)&gi;
case 10:return(void*)&program_state;
case 11:return(void*)&uball;
case 12:return(void*)&uchain;
case 13:return(void*)&gy;
case 14:return(void*)&gu;
case 15:return(void*)&shield_static;
case 16:return(void*)&windowprocs;
case 17:return(void*)&gd;
case 18:return(void*)&gw;
case 19:return(void*)&gf;
case 20:return(void*)&gg;
case 21:return(void*)&disp;
case 22:return(void*)&WIN_MAP;
case 23:return(void*)&gs;
case 24:return(void*)&a11y;
case 25:return(void*)&WIN_MESSAGE;
case 26:return(void*)&gc;
case 27:return(void*)&sysopt;
case 28:return(void*)&mons;
case 29:return(void*)&objects;
case 30:return(void*)&def_warnsyms;
case 31:return(void*)&defsyms;
case 32:return(void*)&svm;
default:abort();}}
uint64_t teleport_display_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(NhRegion));
case 6:return(uint64_t)(sizeof(dlevel_t));
case 7:return(uint64_t)(sizeof(gbuf_entry));
case 8:return(uint64_t)(sizeof(struct Race));
case 9:return(uint64_t)(sizeof(struct accessibility_data));
case 10:return(uint64_t)(sizeof(struct classic_representation));
case 11:return(uint64_t)(sizeof(struct const_globals));
case 12:return(uint64_t)(sizeof(struct context_info));
case 13:return(uint64_t)(sizeof(struct d_level));
case 14:return(uint64_t)(sizeof(struct dgn_topology));
case 15:return(uint64_t)(sizeof(struct display_hints));
case 16:return(uint64_t)(sizeof(struct engr));
case 17:return(uint64_t)(sizeof(struct flag));
case 18:return(uint64_t)(sizeof(struct glyph_map_entry));
case 19:return(uint64_t)(sizeof(struct glyphinfo));
case 20:return(uint64_t)(sizeof(struct instance_flags));
case 21:return(uint64_t)(sizeof(struct instance_globals_c));
case 22:return(uint64_t)(sizeof(struct instance_globals_d));
case 23:return(uint64_t)(sizeof(struct instance_globals_f));
case 24:return(uint64_t)(sizeof(struct instance_globals_g));
case 25:return(uint64_t)(sizeof(struct instance_globals_i));
case 26:return(uint64_t)(sizeof(struct instance_globals_o));
case 27:return(uint64_t)(sizeof(struct instance_globals_s));
case 28:return(uint64_t)(sizeof(struct instance_globals_saved_c));
case 29:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 30:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 31:return(uint64_t)(sizeof(struct instance_globals_saved_m));
case 32:return(uint64_t)(sizeof(struct instance_globals_u));
case 33:return(uint64_t)(sizeof(struct instance_globals_v));
case 34:return(uint64_t)(sizeof(struct instance_globals_w));
case 35:return(uint64_t)(sizeof(struct instance_globals_y));
case 36:return(uint64_t)(sizeof(struct levelflags));
case 37:return(uint64_t)(sizeof(struct mextra));
case 38:return(uint64_t)(sizeof(struct monst));
case 39:return(uint64_t)(sizeof(struct nhcoord));
case 40:return(uint64_t)(sizeof(struct obj));
case 41:return(uint64_t)(sizeof(struct objclass));
case 42:return(uint64_t)(sizeof(struct permonst));
case 43:return(uint64_t)(sizeof(struct prop));
case 44:return(uint64_t)(sizeof(struct rm));
case 45:return(uint64_t)(sizeof(struct sinfo));
case 46:return(uint64_t)(sizeof(struct symdef));
case 47:return(uint64_t)(sizeof(struct symsetentry));
case 48:return(uint64_t)(sizeof(struct sysopt_s));
case 49:return(uint64_t)(sizeof(struct tmp_glyph));
case 50:return(uint64_t)(sizeof(struct trap));
case 51:return(uint64_t)(sizeof(struct warntype_info));
case 52:return(uint64_t)(sizeof(struct win_settings));
case 53:return(uint64_t)(sizeof(struct window_procs));
case 54:return(uint64_t)(sizeof(struct you));
case 55:return(uint64_t)(sizeof(union vptrs));
case 56:return(uint64_t)(AIR);
case 57:return(uint64_t)(ALTAR);
case 58:return(uint64_t)(BEAR_TRAP);
case 59:return(uint64_t)(BLCORNER);
case 60:return(uint64_t)(BLINDED);
case 61:return(uint64_t)(BOULDER);
case 62:return(uint64_t)(BRCORNER);
case 63:return(uint64_t)(CLOUD);
case 64:return(uint64_t)(COIN_CLASS);
case 65:return(uint64_t)(CONFUSION);
case 66:return(uint64_t)(CORPSE);
case 67:return(uint64_t)(CORR);
case 68:return(uint64_t)(CROSSWALL);
case 69:return(uint64_t)(DBWALL);
case 70:return(uint64_t)(DETECT_MONSTERS);
case 71:return(uint64_t)(DOOR);
case 72:return(uint64_t)(DRAWBRIDGE_DOWN);
case 73:return(uint64_t)(DRAWBRIDGE_UP);
case 74:return(uint64_t)(FEMALE);
case 75:return(uint64_t)(FIRST_OBJECT);
case 76:return(uint64_t)(FIRST_REAL_GEM);
case 77:return(uint64_t)(FIRST_SPELL);
case 78:return(uint64_t)(FOOD_CLASS);
case 79:return(uint64_t)(FOUNTAIN);
case 80:return(uint64_t)(GLYPH_ALTAR_OFF);
case 81:return(uint64_t)(GLYPH_BODY_OFF);
case 82:return(uint64_t)(GLYPH_BODY_PILETOP_OFF);
case 83:return(uint64_t)(GLYPH_CMAP_A_OFF);
case 84:return(uint64_t)(GLYPH_CMAP_B_OFF);
case 85:return(uint64_t)(GLYPH_CMAP_C_OFF);
case 86:return(uint64_t)(GLYPH_CMAP_GEH_OFF);
case 87:return(uint64_t)(GLYPH_CMAP_KNOX_OFF);
case 88:return(uint64_t)(GLYPH_CMAP_MAIN_OFF);
case 89:return(uint64_t)(GLYPH_CMAP_MINES_OFF);
case 90:return(uint64_t)(GLYPH_CMAP_SOKO_OFF);
case 91:return(uint64_t)(GLYPH_CMAP_STONE_OFF);
case 92:return(uint64_t)(GLYPH_DETECT_FEM_OFF);
case 93:return(uint64_t)(GLYPH_DETECT_MALE_OFF);
case 94:return(uint64_t)(GLYPH_EXPLODE_DARK_OFF);
case 95:return(uint64_t)(GLYPH_EXPLODE_FIERY_OFF);
case 96:return(uint64_t)(GLYPH_EXPLODE_FROSTY_OFF);
case 97:return(uint64_t)(GLYPH_EXPLODE_MAGICAL_OFF);
case 98:return(uint64_t)(GLYPH_EXPLODE_MUDDY_OFF);
case 99:return(uint64_t)(GLYPH_EXPLODE_NOXIOUS_OFF);
case 100:return(uint64_t)(GLYPH_EXPLODE_WET_OFF);
case 101:return(uint64_t)(GLYPH_INVIS_OFF);
case 102:return(uint64_t)(GLYPH_MON_FEM_OFF);
case 103:return(uint64_t)(GLYPH_MON_MALE_OFF);
case 104:return(uint64_t)(GLYPH_NOTHING_OFF);
case 105:return(uint64_t)(GLYPH_OBJ_OFF);
case 106:return(uint64_t)(GLYPH_OBJ_PILETOP_OFF);
case 107:return(uint64_t)(GLYPH_PET_FEM_OFF);
case 108:return(uint64_t)(GLYPH_PET_MALE_OFF);
case 109:return(uint64_t)(GLYPH_RIDDEN_FEM_OFF);
case 110:return(uint64_t)(GLYPH_RIDDEN_MALE_OFF);
case 111:return(uint64_t)(GLYPH_STATUE_FEM_OFF);
case 112:return(uint64_t)(GLYPH_STATUE_FEM_PILETOP_OFF);
case 113:return(uint64_t)(GLYPH_STATUE_MALE_OFF);
case 114:return(uint64_t)(GLYPH_STATUE_MALE_PILETOP_OFF);
case 115:return(uint64_t)(GLYPH_SWALLOW_OFF);
case 116:return(uint64_t)(GLYPH_UNEXPLORED_OFF);
case 117:return(uint64_t)(GLYPH_WARNING_OFF);
case 118:return(uint64_t)(GLYPH_ZAP_OFF);
case 119:return(uint64_t)(GRAVE);
case 120:return(uint64_t)(HALLUC);
case 121:return(uint64_t)(HALLUC_RES);
case 122:return(uint64_t)(HWALL);
case 123:return(uint64_t)(H_IBM);
case 124:return(uint64_t)(ICE);
case 125:return(uint64_t)(INFRAVISION);
case 126:return(uint64_t)(INVIS);
case 127:return(uint64_t)(IRONBARS);
case 128:return(uint64_t)(LADDER);
case 129:return(uint64_t)(LAST_GLASS_GEM);
case 130:return(uint64_t)(LAST_SPELL);
case 131:return(uint64_t)(LAVAPOOL);
case 132:return(uint64_t)(LAVAWALL);
case 133:return(uint64_t)(MALE);
case 134:return(uint64_t)(MAXMCLASSES);
case 135:return(uint64_t)(MAXOCLASSES);
case 136:return(uint64_t)(MAXPCHARS);
case 137:return(uint64_t)(MAX_GLYPH);
case 138:return(uint64_t)(MOAT);
case 139:return(uint64_t)(M_AP_FURNITURE);
case 140:return(uint64_t)(M_AP_MONSTER);
case 141:return(uint64_t)(M_AP_NOTHING);
case 142:return(uint64_t)(M_AP_OBJECT);
case 143:return(uint64_t)(NON_PM);
case 144:return(uint64_t)(NO_TRAP);
case 145:return(uint64_t)(NUMMONS);
case 146:return(uint64_t)(NUM_OBJECTS);
case 147:return(uint64_t)(PIT);
case 148:return(uint64_t)(PM_LONG_WORM_TAIL);
case 149:return(uint64_t)(PM_TENGU);
case 150:return(uint64_t)(POOL);
case 151:return(uint64_t)(POTION_CLASS);
case 152:return(uint64_t)(PROT_FROM_SHAPE_CHANGERS);
case 153:return(uint64_t)(ROGUESET);
case 154:return(uint64_t)(ROOM);
case 155:return(uint64_t)(SCORR);
case 156:return(uint64_t)(SDOOR);
case 157:return(uint64_t)(SEE_INVIS);
case 158:return(uint64_t)(SINK);
case 159:return(uint64_t)(SPIKED_PIT);
case 160:return(uint64_t)(STAIRS);
case 161:return(uint64_t)(STATUE);
case 162:return(uint64_t)(STONE);
case 163:return(uint64_t)(STUNNED);
case 164:return(uint64_t)(SYM_BOULDER);
case 165:return(uint64_t)(SYM_HERO_OVERRIDE);
case 166:return(uint64_t)(SYM_INVISIBLE);
case 167:return(uint64_t)(SYM_NOTHING);
case 168:return(uint64_t)(SYM_PET_OVERRIDE);
case 169:return(uint64_t)(SYM_UNEXPLORED);
case 170:return(uint64_t)(S_air);
case 171:return(uint64_t)(S_altar);
case 172:return(uint64_t)(S_arrow_trap);
case 173:return(uint64_t)(S_bars);
case 174:return(uint64_t)(S_blcorn);
case 175:return(uint64_t)(S_brcorn);
case 176:return(uint64_t)(S_brdnladder);
case 177:return(uint64_t)(S_brdnstair);
case 178:return(uint64_t)(S_brupladder);
case 179:return(uint64_t)(S_brupstair);
case 180:return(uint64_t)(S_cloud);
case 181:return(uint64_t)(S_corr);
case 182:return(uint64_t)(S_crwall);
case 183:return(uint64_t)(S_darkroom);
case 184:return(uint64_t)(S_digbeam);
case 185:return(uint64_t)(S_dnladder);
case 186:return(uint64_t)(S_dnstair);
case 187:return(uint64_t)(S_engrcorr);
case 188:return(uint64_t)(S_engroom);
case 189:return(uint64_t)(S_expl_tl);
case 190:return(uint64_t)(S_fountain);
case 191:return(uint64_t)(S_goodpos);
case 192:return(uint64_t)(S_grave);
case 193:return(uint64_t)(S_hcdbridge);
case 194:return(uint64_t)(S_hcdoor);
case 195:return(uint64_t)(S_hodbridge);
case 196:return(uint64_t)(S_hodoor);
case 197:return(uint64_t)(S_hwall);
case 198:return(uint64_t)(S_ice);
case 199:return(uint64_t)(S_lava);
case 200:return(uint64_t)(S_lavawall);
case 201:return(uint64_t)(S_litcorr);
case 202:return(uint64_t)(S_ndoor);
case 203:return(uint64_t)(S_polymorph_trap);
case 204:return(uint64_t)(S_pool);
case 205:return(uint64_t)(S_room);
case 206:return(uint64_t)(S_sink);
case 207:return(uint64_t)(S_stone);
case 208:return(uint64_t)(S_sw_bc);
case 209:return(uint64_t)(S_sw_bl);
case 210:return(uint64_t)(S_sw_br);
case 211:return(uint64_t)(S_sw_ml);
case 212:return(uint64_t)(S_sw_mr);
case 213:return(uint64_t)(S_sw_tc);
case 214:return(uint64_t)(S_sw_tl);
case 215:return(uint64_t)(S_sw_tr);
case 216:return(uint64_t)(S_tdwall);
case 217:return(uint64_t)(S_throne);
case 218:return(uint64_t)(S_tlcorn);
case 219:return(uint64_t)(S_tlwall);
case 220:return(uint64_t)(S_trcorn);
case 221:return(uint64_t)(S_tree);
case 222:return(uint64_t)(S_trwall);
case 223:return(uint64_t)(S_tuwall);
case 224:return(uint64_t)(S_upladder);
case 225:return(uint64_t)(S_upstair);
case 226:return(uint64_t)(S_vbeam);
case 227:return(uint64_t)(S_vcdbridge);
case 228:return(uint64_t)(S_vcdoor);
case 229:return(uint64_t)(S_vodbridge);
case 230:return(uint64_t)(S_vodoor);
case 231:return(uint64_t)(S_vwall);
case 232:return(uint64_t)(S_water);
case 233:return(uint64_t)(TDWALL);
case 234:return(uint64_t)(TELEPAT);
case 235:return(uint64_t)(THRONE);
case 236:return(uint64_t)(TLCORNER);
case 237:return(uint64_t)(TLWALL);
case 238:return(uint64_t)(TRAPNUM);
case 239:return(uint64_t)(TRCORNER);
case 240:return(uint64_t)(TREE);
case 241:return(uint64_t)(TRWALL);
case 242:return(uint64_t)(TUWALL);
case 243:return(uint64_t)(VWALL);
case 244:return(uint64_t)(WARNING);
case 245:return(uint64_t)(WARN_OF_MON);
case 246:return(uint64_t)(WATER);
case 247:return(uint64_t)(WEB);
case 248:return(uint64_t)(altar_chaotic);
case 249:return(uint64_t)(altar_color_chaotic);
case 250:return(uint64_t)(altar_color_lawful);
case 251:return(uint64_t)(altar_color_neutral);
case 252:return(uint64_t)(altar_color_other);
case 253:return(uint64_t)(altar_color_unaligned);
case 254:return(uint64_t)(altar_lawful);
case 255:return(uint64_t)(altar_neutral);
case 256:return(uint64_t)(altar_other);
case 257:return(uint64_t)(altar_unaligned);
case 258:return(uint64_t)(docrtMapOnly);
case 259:return(uint64_t)(docrtNocls);
case 260:return(uint64_t)(docrtRecalc);
case 261:return(uint64_t)(docrtRefresh);
case 262:return(uint64_t)(expl_dark);
case 263:return(uint64_t)(expl_fiery);
case 264:return(uint64_t)(expl_frosty);
case 265:return(uint64_t)(expl_magical);
case 266:return(uint64_t)(expl_muddy);
case 267:return(uint64_t)(expl_noxious);
case 268:return(uint64_t)(expl_wet);
case 269:return(uint64_t)(explode_color_dark);
case 270:return(uint64_t)(explode_color_fiery);
case 271:return(uint64_t)(explode_color_frosty);
case 272:return(uint64_t)(explode_color_magical);
case 273:return(uint64_t)(explode_color_muddy);
case 274:return(uint64_t)(explode_color_noxious);
case 275:return(uint64_t)(explode_color_wet);
case 276:return(uint64_t)(gehennom_walls);
case 277:return(uint64_t)(gm_levelchange);
case 278:return(uint64_t)(knox_walls);
case 279:return(uint64_t)(main_walls);
case 280:return(uint64_t)(mines_walls);
case 281:return(uint64_t)(sokoban_walls);
case 282:return(uint64_t)(zap_color_acid);
case 283:return(uint64_t)(zap_color_death);
case 284:return(uint64_t)(zap_color_fire);
case 285:return(uint64_t)(zap_color_frost);
case 286:return(uint64_t)(zap_color_lightning);
case 287:return(uint64_t)(zap_color_missile);
case 288:return(uint64_t)(zap_color_poison_gas);
case 289:return(uint64_t)(zap_color_sleep);
default:abort();}}
uint64_t teleport_display_read(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->visible);
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 2:{struct accessibility_data*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->accessiblemsg);
case 1:return(uint64_t)(uintptr_t)(p->mon_notices);
case 2:return(uint64_t)(uintptr_t)(p->mon_notices_blocked);
case 3:return(uint64_t)(uintptr_t)(p->glyph_updates);
default:abort();}}
case 3:{struct classic_representation*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->color);
case 1:return(uint64_t)(uintptr_t)(p->symidx);
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroobj);
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->warnlevel);
case 1:return(uint64_t)(uintptr_t)(&p->warntype);
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_rogue_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 2:return(uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 3:return(uint64_t)(uintptr_t)(&p->d_knox_level);
default:abort();}}
case 8:{struct display_hints*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->botl);
case 1:return(uint64_t)(uintptr_t)(p->botlx);
case 2:return(uint64_t)(uintptr_t)(p->time_botl);
default:abort();}}
case 9:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->objects);
case 2:return(uint64_t)(uintptr_t)(&p->monsters);
case 3:return(uint64_t)(uintptr_t)(p->objlist);
case 4:return(uint64_t)(uintptr_t)(p->monlist);
case 5:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 10:{struct engr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->engr_x);
case 1:return(uint64_t)(uintptr_t)(p->engr_y);
case 2:return(uint64_t)(uintptr_t)(p->erevealed);
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dark_room);
case 1:return(uint64_t)(uintptr_t)(p->female);
case 2:return(uint64_t)(uintptr_t)(p->lit_corridor);
case 3:return(uint64_t)(uintptr_t)(p->safe_dog);
case 4:return(uint64_t)(uintptr_t)(p->sparkle);
case 5:return(uint64_t)(uintptr_t)(p->showrace);
default:abort();}}
case 12:{gbuf_entry*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->gnew);
case 1:return(uint64_t)(uintptr_t)(&p->glyphinfo);
default:abort();}}
case 13:{struct glyph_map_entry*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyphflags);
case 1:return(uint64_t)(uintptr_t)(&p->sym);
case 2:return(uint64_t)(uintptr_t)(p->customcolor);
case 3:return(uint64_t)(uintptr_t)(p->color256idx);
case 4:return(uint64_t)(uintptr_t)(p->tileidx);
case 5:return(uint64_t)(uintptr_t)(p->u);
default:abort();}}
case 14:{struct glyphinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
case 1:return(uint64_t)(uintptr_t)(p->ttychar);
case 2:return(uint64_t)(uintptr_t)(p->framecolor);
case 3:return(uint64_t)(uintptr_t)(&p->gm);
default:abort();}}
case 15:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->bgcolors);
case 1:return(uint64_t)(uintptr_t)(p->use_background_glyph);
case 2:return(uint64_t)(uintptr_t)(p->wc_color);
default:abort();}}
case 16:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->currentgraphics);
default:abort();}}
case 17:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->defer_see_monsters);
default:abort();}}
case 18:{struct instance_globals_f*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 19:{struct instance_globals_g*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->gbuf);
case 1:return(uint64_t)(uintptr_t)(&p->gbuf_start);
case 2:return(uint64_t)(uintptr_t)(&p->gbuf_stop);
case 3:return(uint64_t)(uintptr_t)(p->glyph_reset_timestamp);
case 4:return(uint64_t)(uintptr_t)(p->glyphmap_perlevel_flags);
default:abort();}}
case 20:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_mklev);
default:abort();}}
case 21:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->otg_temp);
case 1:return(uint64_t)(uintptr_t)(p->otg_otmp);
case 2:return(uint64_t)(uintptr_t)(&p->ov_primary_syms);
case 3:return(uint64_t)(uintptr_t)(&p->ov_rogue_syms);
default:abort();}}
case 22:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->symset);
case 1:return(uint64_t)(uintptr_t)(&p->showsyms);
default:abort();}}
case 23:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 24:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 25:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->lastseentyp);
case 1:return(uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 26:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->moves);
default:abort();}}
case 27:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 28:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 29:{struct instance_globals_w*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->warn_obj_cnt);
case 1:return(uint64_t)(uintptr_t)(&p->wsettings);
default:abort();}}
case 30:{struct instance_globals_y*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 31:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hero_memory);
case 1:return(uint64_t)(uintptr_t)(p->arboreal);
default:abort();}}
case 32:{struct mextra*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mcorpsenm);
default:abort();}}
case 33:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nmon);
case 1:return(uint64_t)(uintptr_t)(p->data);
case 2:return(uint64_t)(uintptr_t)(p->m_lev);
case 3:return(uint64_t)(uintptr_t)(p->mx);
case 4:return(uint64_t)(uintptr_t)(p->my);
case 5:return(uint64_t)(uintptr_t)(p->mhp);
case 6:return(uint64_t)(uintptr_t)(p->mappearance);
case 7:return(uint64_t)(uintptr_t)(p->m_ap_type);
case 8:return(uint64_t)(uintptr_t)(p->mtame);
case 9:return(uint64_t)(uintptr_t)(p->female);
case 10:return(uint64_t)(uintptr_t)(p->minvis);
case 11:return(uint64_t)(uintptr_t)(p->mundetected);
case 12:return(uint64_t)(uintptr_t)(p->mpeaceful);
case 13:return(uint64_t)(uintptr_t)(p->mtrapped);
case 14:return(uint64_t)(uintptr_t)(p->wormno);
case 15:return(uint64_t)(uintptr_t)(p->meverseen);
case 16:return(uint64_t)(uintptr_t)(p->mstate);
case 17:return(uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 34:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 35:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(&p->v);
case 2:return(uint64_t)(uintptr_t)(p->ox);
case 3:return(uint64_t)(uintptr_t)(p->oy);
case 4:return(uint64_t)(uintptr_t)(p->otyp);
case 5:return(uint64_t)(uintptr_t)(p->spe);
case 6:return(uint64_t)(uintptr_t)(p->oclass);
case 7:return(uint64_t)(uintptr_t)(p->where);
case 8:return(uint64_t)(uintptr_t)(p->dknown);
case 9:return(uint64_t)(uintptr_t)(p->corpsenm);
default:abort();}}
case 36:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_class);
case 1:return(uint64_t)(uintptr_t)(p->oc_color);
default:abort();}}
case 37:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->pmidx);
case 1:return(uint64_t)(uintptr_t)(p->mlet);
case 2:return(uint64_t)(uintptr_t)(p->mflags1);
case 3:return(uint64_t)(uintptr_t)(p->mflags2);
case 4:return(uint64_t)(uintptr_t)(p->mflags3);
case 5:return(uint64_t)(uintptr_t)(p->mcolor);
default:abort();}}
case 38:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 39:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->glyph);
case 1:return(uint64_t)(uintptr_t)(p->typ);
case 2:return(uint64_t)(uintptr_t)(p->seenv);
case 3:return(uint64_t)(uintptr_t)(p->flags);
case 4:return(uint64_t)(uintptr_t)(p->horizontal);
case 5:return(uint64_t)(uintptr_t)(p->lit);
case 6:return(uint64_t)(uintptr_t)(p->waslit);
case 7:return(uint64_t)(uintptr_t)(p->candig);
default:abort();}}
case 40:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->gameover);
case 1:return(uint64_t)(uintptr_t)(p->stopprint);
case 2:return(uint64_t)(uintptr_t)(p->done_hup);
case 3:return(uint64_t)(uintptr_t)(p->saving);
case 4:return(uint64_t)(uintptr_t)(p->restoring);
case 5:return(uint64_t)(uintptr_t)(p->in_getlev);
case 6:return(uint64_t)(uintptr_t)(p->in_docrt);
default:abort();}}
case 41:{struct symdef*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->color);
default:abort();}}
case 42:{struct symsetentry*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->handling);
case 1:return(uint64_t)(uintptr_t)(p->nocolor);
default:abort();}}
case 43:{struct sysopt_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->accessibility);
default:abort();}}
case 44:{struct tmp_glyph*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->saved);
case 1:return(uint64_t)(uintptr_t)(p->sidx);
case 2:return(uint64_t)(uintptr_t)(p->style);
case 3:return(uint64_t)(uintptr_t)(p->glyph);
case 4:return(uint64_t)(uintptr_t)(p->prev);
default:abort();}}
case 45:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ntrap);
case 1:return(uint64_t)(uintptr_t)(p->tx);
case 2:return(uint64_t)(uintptr_t)(p->ty);
case 3:return(uint64_t)(uintptr_t)(p->ttyp);
case 4:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 46:{union vptrs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 47:{struct warntype_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->obj);
case 1:return(uint64_t)(uintptr_t)(p->polyd);
case 2:return(uint64_t)(uintptr_t)(p->species);
default:abort();}}
case 48:{struct win_settings*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->map_frame_color);
default:abort();}}
case 49:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 1:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 2:return(uint64_t)(uintptr_t)(p->win_curs);
case 3:return(uint64_t)(uintptr_t)(p->win_print_glyph);
case 4:return(uint64_t)(uintptr_t)(p->win_delay_output);
default:abort();}}
case 50:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(&p->uz);
case 3:return(uint64_t)(uintptr_t)(&p->uz0);
case 4:return(uint64_t)(uintptr_t)(&p->uprops);
case 5:return(uint64_t)(uintptr_t)(p->xray_range);
case 6:return(uint64_t)(uintptr_t)(p->unblind_telepat_range);
case 7:return(uint64_t)(uintptr_t)(p->bc_felt);
case 8:return(uint64_t)(uintptr_t)(p->umonster);
case 9:return(uint64_t)(uintptr_t)(p->umonnum);
case 10:return(uint64_t)(uintptr_t)(p->uswallow);
case 11:return(uint64_t)(uintptr_t)(p->uinwater);
case 12:return(uint64_t)(uintptr_t)(p->uundetected);
case 13:return(uint64_t)(uintptr_t)(p->mfemale);
case 14:return(uint64_t)(uintptr_t)(p->uburied);
case 15:return(uint64_t)(uintptr_t)(p->ustuck);
case 16:return(uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
default:abort();}}
void teleport_display_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:p->visible=(__typeof__(p->visible))value;return;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 2:{struct accessibility_data*p=at;switch(field){
case 0:p->accessiblemsg=(__typeof__(p->accessiblemsg))value;return;
case 1:p->mon_notices=(__typeof__(p->mon_notices))value;return;
case 2:p->mon_notices_blocked=(__typeof__(p->mon_notices_blocked))value;return;
case 3:p->glyph_updates=(__typeof__(p->glyph_updates))value;return;
default:abort();}}
case 3:{struct classic_representation*p=at;switch(field){
case 0:p->color=(__typeof__(p->color))value;return;
case 1:p->symidx=(__typeof__(p->symidx))value;return;
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:p->warnlevel=(__typeof__(p->warnlevel))value;return;
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 2:p->d_sokoban_dnum=(__typeof__(p->d_sokoban_dnum))value;return;
default:abort();}}
case 8:{struct display_hints*p=at;switch(field){
case 0:p->botl=(__typeof__(p->botl))value;return;
case 1:p->botlx=(__typeof__(p->botlx))value;return;
case 2:p->time_botl=(__typeof__(p->time_botl))value;return;
default:abort();}}
case 9:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(__typeof__(p->objlist))value;return;
case 4:p->monlist=(__typeof__(p->monlist))value;return;
default:abort();}}
case 10:{struct engr*p=at;switch(field){
case 0:p->engr_x=(__typeof__(p->engr_x))value;return;
case 1:p->engr_y=(__typeof__(p->engr_y))value;return;
case 2:p->erevealed=(unsigned int)value;return;
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:p->dark_room=(__typeof__(p->dark_room))value;return;
case 1:p->female=(__typeof__(p->female))value;return;
case 2:p->lit_corridor=(__typeof__(p->lit_corridor))value;return;
case 3:p->safe_dog=(__typeof__(p->safe_dog))value;return;
case 4:p->sparkle=(__typeof__(p->sparkle))value;return;
case 5:p->showrace=(__typeof__(p->showrace))value;return;
default:abort();}}
case 12:{gbuf_entry*p=at;switch(field){
case 0:p->gnew=(__typeof__(p->gnew))value;return;
default:abort();}}
case 13:{struct glyph_map_entry*p=at;switch(field){
case 0:p->glyphflags=(__typeof__(p->glyphflags))value;return;
case 2:p->customcolor=(__typeof__(p->customcolor))value;return;
case 3:p->color256idx=(__typeof__(p->color256idx))value;return;
case 4:p->tileidx=(__typeof__(p->tileidx))value;return;
case 5:p->u=(__typeof__(p->u))value;return;
default:abort();}}
case 14:{struct glyphinfo*p=at;switch(field){
case 0:p->glyph=(__typeof__(p->glyph))value;return;
case 1:p->ttychar=(__typeof__(p->ttychar))value;return;
case 2:p->framecolor=(__typeof__(p->framecolor))value;return;
default:abort();}}
case 15:{struct instance_flags*p=at;switch(field){
case 0:p->bgcolors=(__typeof__(p->bgcolors))value;return;
case 1:p->use_background_glyph=(__typeof__(p->use_background_glyph))value;return;
case 2:p->wc_color=(__typeof__(p->wc_color))value;return;
default:abort();}}
case 16:{struct instance_globals_c*p=at;switch(field){
case 0:p->currentgraphics=(__typeof__(p->currentgraphics))value;return;
default:abort();}}
case 17:{struct instance_globals_d*p=at;switch(field){
case 0:p->defer_see_monsters=(__typeof__(p->defer_see_monsters))value;return;
default:abort();}}
case 18:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(__typeof__(p->ftrap))value;return;
default:abort();}}
case 19:{struct instance_globals_g*p=at;switch(field){
case 3:p->glyph_reset_timestamp=(__typeof__(p->glyph_reset_timestamp))value;return;
case 4:p->glyphmap_perlevel_flags=(__typeof__(p->glyphmap_perlevel_flags))value;return;
default:abort();}}
case 20:{struct instance_globals_i*p=at;switch(field){
case 0:p->in_mklev=(__typeof__(p->in_mklev))value;return;
default:abort();}}
case 21:{struct instance_globals_o*p=at;switch(field){
case 0:p->otg_temp=(__typeof__(p->otg_temp))value;return;
case 1:p->otg_otmp=(__typeof__(p->otg_otmp))value;return;
default:abort();}}
case 22:{struct instance_globals_s*p=at;switch(field){
default:abort();}}
case 23:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 25:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 26:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=(__typeof__(p->moves))value;return;
default:abort();}}
case 27:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 28:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(__typeof__(p->viz_array))value;return;
default:abort();}}
case 29:{struct instance_globals_w*p=at;switch(field){
case 0:p->warn_obj_cnt=(__typeof__(p->warn_obj_cnt))value;return;
default:abort();}}
case 30:{struct instance_globals_y*p=at;switch(field){
default:abort();}}
case 31:{struct levelflags*p=at;switch(field){
case 0:p->hero_memory=(unsigned int)value;return;
case 1:p->arboreal=(unsigned int)value;return;
default:abort();}}
case 32:{struct mextra*p=at;switch(field){
case 0:p->mcorpsenm=(__typeof__(p->mcorpsenm))value;return;
default:abort();}}
case 33:{struct monst*p=at;switch(field){
case 0:p->nmon=(__typeof__(p->nmon))value;return;
case 1:p->data=(__typeof__(p->data))value;return;
case 2:p->m_lev=(__typeof__(p->m_lev))value;return;
case 3:p->mx=(__typeof__(p->mx))value;return;
case 4:p->my=(__typeof__(p->my))value;return;
case 5:p->mhp=(__typeof__(p->mhp))value;return;
case 6:p->mappearance=(__typeof__(p->mappearance))value;return;
case 7:p->m_ap_type=(__typeof__(p->m_ap_type))value;return;
case 8:p->mtame=(__typeof__(p->mtame))value;return;
case 9:p->female=(unsigned int)value;return;
case 10:p->minvis=(unsigned int)value;return;
case 11:p->mundetected=(unsigned int)value;return;
case 12:p->mpeaceful=(unsigned int)value;return;
case 13:p->mtrapped=(unsigned int)value;return;
case 14:p->wormno=(unsigned int)value;return;
case 15:p->meverseen=(unsigned int)value;return;
case 16:p->mstate=(__typeof__(p->mstate))value;return;
case 17:p->mextra=(__typeof__(p->mextra))value;return;
default:abort();}}
case 34:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 35:{struct obj*p=at;switch(field){
case 0:p->nobj=(__typeof__(p->nobj))value;return;
case 2:p->ox=(__typeof__(p->ox))value;return;
case 3:p->oy=(__typeof__(p->oy))value;return;
case 4:p->otyp=(__typeof__(p->otyp))value;return;
case 5:p->spe=(__typeof__(p->spe))value;return;
case 6:p->oclass=(__typeof__(p->oclass))value;return;
case 7:p->where=(__typeof__(p->where))value;return;
case 8:p->dknown=(unsigned int)value;return;
case 9:p->corpsenm=(__typeof__(p->corpsenm))value;return;
default:abort();}}
case 36:{struct objclass*p=at;switch(field){
case 0:p->oc_class=(__typeof__(p->oc_class))value;return;
case 1:p->oc_color=(__typeof__(p->oc_color))value;return;
default:abort();}}
case 37:{struct permonst*p=at;switch(field){
case 1:p->mlet=(__typeof__(p->mlet))value;return;
case 2:p->mflags1=(__typeof__(p->mflags1))value;return;
case 3:p->mflags2=(__typeof__(p->mflags2))value;return;
case 4:p->mflags3=(__typeof__(p->mflags3))value;return;
case 5:p->mcolor=(__typeof__(p->mcolor))value;return;
default:abort();}}
case 38:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(__typeof__(p->extrinsic))value;return;
case 1:p->blocked=(__typeof__(p->blocked))value;return;
case 2:p->intrinsic=(__typeof__(p->intrinsic))value;return;
default:abort();}}
case 39:{struct rm*p=at;switch(field){
case 0:p->glyph=(__typeof__(p->glyph))value;return;
case 1:p->typ=(__typeof__(p->typ))value;return;
case 2:p->seenv=(__typeof__(p->seenv))value;return;
case 3:p->flags=(unsigned int)value;return;
case 4:p->horizontal=(unsigned int)value;return;
case 5:p->lit=(unsigned int)value;return;
case 6:p->waslit=(unsigned int)value;return;
case 7:p->candig=(unsigned int)value;return;
default:abort();}}
case 40:{struct sinfo*p=at;switch(field){
case 0:p->gameover=(__typeof__(p->gameover))value;return;
case 1:p->stopprint=(__typeof__(p->stopprint))value;return;
case 2:p->done_hup=(__typeof__(p->done_hup))value;return;
case 3:p->saving=(__typeof__(p->saving))value;return;
case 4:p->restoring=(__typeof__(p->restoring))value;return;
case 5:p->in_getlev=(__typeof__(p->in_getlev))value;return;
case 6:p->in_docrt=(__typeof__(p->in_docrt))value;return;
default:abort();}}
case 41:{struct symdef*p=at;switch(field){
case 0:p->color=(__typeof__(p->color))value;return;
default:abort();}}
case 42:{struct symsetentry*p=at;switch(field){
case 0:p->handling=(__typeof__(p->handling))value;return;
case 1:p->nocolor=(unsigned int)value;return;
default:abort();}}
case 43:{struct sysopt_s*p=at;switch(field){
case 0:p->accessibility=(__typeof__(p->accessibility))value;return;
default:abort();}}
case 44:{struct tmp_glyph*p=at;switch(field){
case 1:p->sidx=(__typeof__(p->sidx))value;return;
case 2:p->style=(__typeof__(p->style))value;return;
case 3:p->glyph=(__typeof__(p->glyph))value;return;
case 4:p->prev=(__typeof__(p->prev))value;return;
default:abort();}}
case 45:{struct trap*p=at;switch(field){
case 0:p->ntrap=(__typeof__(p->ntrap))value;return;
case 1:p->tx=(__typeof__(p->tx))value;return;
case 2:p->ty=(__typeof__(p->ty))value;return;
case 3:p->ttyp=(unsigned int)value;return;
case 4:p->tseen=(unsigned int)value;return;
default:abort();}}
case 46:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(__typeof__(p->v_nexthere))value;return;
default:abort();}}
case 47:{struct warntype_info*p=at;switch(field){
case 0:p->obj=(__typeof__(p->obj))value;return;
case 1:p->polyd=(__typeof__(p->polyd))value;return;
case 2:p->species=(__typeof__(p->species))value;return;
default:abort();}}
case 48:{struct win_settings*p=at;switch(field){
case 0:p->map_frame_color=(__typeof__(p->map_frame_color))value;return;
default:abort();}}
case 49:{struct window_procs*p=at;switch(field){
case 0:p->win_clear_nhwindow=(__typeof__(p->win_clear_nhwindow))value;return;
case 1:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 2:p->win_curs=(__typeof__(p->win_curs))value;return;
case 3:p->win_print_glyph=(__typeof__(p->win_print_glyph))value;return;
case 4:p->win_delay_output=(__typeof__(p->win_delay_output))value;return;
default:abort();}}
case 50:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 5:p->xray_range=(__typeof__(p->xray_range))value;return;
case 6:p->unblind_telepat_range=(__typeof__(p->unblind_telepat_range))value;return;
case 7:p->bc_felt=(__typeof__(p->bc_felt))value;return;
case 8:p->umonster=(__typeof__(p->umonster))value;return;
case 9:p->umonnum=(__typeof__(p->umonnum))value;return;
case 10:p->uswallow=(unsigned int)value;return;
case 11:p->uinwater=(unsigned int)value;return;
case 12:p->uundetected=(unsigned int)value;return;
case 13:p->mfemale=(unsigned int)value;return;
case 14:p->uburied=(unsigned int)value;return;
case 15:p->ustuck=(__typeof__(p->ustuck))value;return;
case 16:p->usteed=(__typeof__(p->usteed))value;return;
default:abort();}}
default:abort();}}
void* teleport_display_address(int kind,void*at,int field){switch(kind){
case 0:{NhRegion*p=at;switch(field){
case 0:return(void*)&p->visible;
default:abort();}}
case 1:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 2:{struct accessibility_data*p=at;switch(field){
case 0:return(void*)&p->accessiblemsg;
case 1:return(void*)&p->mon_notices;
case 2:return(void*)&p->mon_notices_blocked;
case 3:return(void*)&p->glyph_updates;
default:abort();}}
case 3:{struct classic_representation*p=at;switch(field){
case 0:return(void*)&p->color;
case 1:return(void*)&p->symidx;
default:abort();}}
case 4:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroobj;
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->warnlevel;
case 1:return(void*)&p->warntype;
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 7:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_rogue_level;
case 1:return(void*)&p->d_water_level;
case 2:return(void*)&p->d_sokoban_dnum;
case 3:return(void*)&p->d_knox_level;
default:abort();}}
case 8:{struct display_hints*p=at;switch(field){
case 0:return(void*)&p->botl;
case 1:return(void*)&p->botlx;
case 2:return(void*)&p->time_botl;
default:abort();}}
case 9:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->objects;
case 2:return(void*)&p->monsters;
case 3:return(void*)&p->objlist;
case 4:return(void*)&p->monlist;
case 5:return(void*)&p->flags;
default:abort();}}
case 10:{struct engr*p=at;switch(field){
case 0:return(void*)&p->engr_x;
case 1:return(void*)&p->engr_y;
default:abort();}}
case 11:{struct flag*p=at;switch(field){
case 0:return(void*)&p->dark_room;
case 1:return(void*)&p->female;
case 2:return(void*)&p->lit_corridor;
case 3:return(void*)&p->safe_dog;
case 4:return(void*)&p->sparkle;
case 5:return(void*)&p->showrace;
default:abort();}}
case 12:{gbuf_entry*p=at;switch(field){
case 0:return(void*)&p->gnew;
case 1:return(void*)&p->glyphinfo;
default:abort();}}
case 13:{struct glyph_map_entry*p=at;switch(field){
case 0:return(void*)&p->glyphflags;
case 1:return(void*)&p->sym;
case 2:return(void*)&p->customcolor;
case 3:return(void*)&p->color256idx;
case 4:return(void*)&p->tileidx;
case 5:return(void*)&p->u;
default:abort();}}
case 14:{struct glyphinfo*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->ttychar;
case 2:return(void*)&p->framecolor;
case 3:return(void*)&p->gm;
default:abort();}}
case 15:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->bgcolors;
case 1:return(void*)&p->use_background_glyph;
case 2:return(void*)&p->wc_color;
default:abort();}}
case 16:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->currentgraphics;
default:abort();}}
case 17:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->defer_see_monsters;
default:abort();}}
case 18:{struct instance_globals_f*p=at;switch(field){
case 0:return(void*)&p->ftrap;
default:abort();}}
case 19:{struct instance_globals_g*p=at;switch(field){
case 0:return(void*)&p->gbuf;
case 1:return(void*)&p->gbuf_start;
case 2:return(void*)&p->gbuf_stop;
case 3:return(void*)&p->glyph_reset_timestamp;
case 4:return(void*)&p->glyphmap_perlevel_flags;
default:abort();}}
case 20:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->in_mklev;
default:abort();}}
case 21:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->otg_temp;
case 1:return(void*)&p->otg_otmp;
case 2:return(void*)&p->ov_primary_syms;
case 3:return(void*)&p->ov_rogue_syms;
default:abort();}}
case 22:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->symset;
case 1:return(void*)&p->showsyms;
default:abort();}}
case 23:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 24:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
default:abort();}}
case 25:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->lastseentyp;
case 1:return(void*)&p->level;
default:abort();}}
case 26:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->moves;
default:abort();}}
case 27:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urace;
default:abort();}}
case 28:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->viz_array;
default:abort();}}
case 29:{struct instance_globals_w*p=at;switch(field){
case 0:return(void*)&p->warn_obj_cnt;
case 1:return(void*)&p->wsettings;
default:abort();}}
case 30:{struct instance_globals_y*p=at;switch(field){
case 0:return(void*)&p->youmonst;
default:abort();}}
case 31:{struct levelflags*p=at;switch(field){
default:abort();}}
case 32:{struct mextra*p=at;switch(field){
case 0:return(void*)&p->mcorpsenm;
default:abort();}}
case 33:{struct monst*p=at;switch(field){
case 0:return(void*)&p->nmon;
case 1:return(void*)&p->data;
case 2:return(void*)&p->m_lev;
case 3:return(void*)&p->mx;
case 4:return(void*)&p->my;
case 5:return(void*)&p->mhp;
case 6:return(void*)&p->mappearance;
case 7:return(void*)&p->m_ap_type;
case 8:return(void*)&p->mtame;
case 16:return(void*)&p->mstate;
case 17:return(void*)&p->mextra;
default:abort();}}
case 34:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 35:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->v;
case 2:return(void*)&p->ox;
case 3:return(void*)&p->oy;
case 4:return(void*)&p->otyp;
case 5:return(void*)&p->spe;
case 6:return(void*)&p->oclass;
case 7:return(void*)&p->where;
case 9:return(void*)&p->corpsenm;
default:abort();}}
case 36:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_class;
case 1:return(void*)&p->oc_color;
default:abort();}}
case 37:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->pmidx;
case 1:return(void*)&p->mlet;
case 2:return(void*)&p->mflags1;
case 3:return(void*)&p->mflags2;
case 4:return(void*)&p->mflags3;
case 5:return(void*)&p->mcolor;
default:abort();}}
case 38:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 39:{struct rm*p=at;switch(field){
case 0:return(void*)&p->glyph;
case 1:return(void*)&p->typ;
case 2:return(void*)&p->seenv;
default:abort();}}
case 40:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->gameover;
case 1:return(void*)&p->stopprint;
case 2:return(void*)&p->done_hup;
case 3:return(void*)&p->saving;
case 4:return(void*)&p->restoring;
case 5:return(void*)&p->in_getlev;
case 6:return(void*)&p->in_docrt;
default:abort();}}
case 41:{struct symdef*p=at;switch(field){
case 0:return(void*)&p->color;
default:abort();}}
case 42:{struct symsetentry*p=at;switch(field){
case 0:return(void*)&p->handling;
default:abort();}}
case 43:{struct sysopt_s*p=at;switch(field){
case 0:return(void*)&p->accessibility;
default:abort();}}
case 44:{struct tmp_glyph*p=at;switch(field){
case 0:return(void*)&p->saved;
case 1:return(void*)&p->sidx;
case 2:return(void*)&p->style;
case 3:return(void*)&p->glyph;
case 4:return(void*)&p->prev;
default:abort();}}
case 45:{struct trap*p=at;switch(field){
case 0:return(void*)&p->ntrap;
case 1:return(void*)&p->tx;
case 2:return(void*)&p->ty;
default:abort();}}
case 46:{union vptrs*p=at;switch(field){
case 0:return(void*)&p->v_nexthere;
default:abort();}}
case 47:{struct warntype_info*p=at;switch(field){
case 0:return(void*)&p->obj;
case 1:return(void*)&p->polyd;
case 2:return(void*)&p->species;
default:abort();}}
case 48:{struct win_settings*p=at;switch(field){
case 0:return(void*)&p->map_frame_color;
default:abort();}}
case 49:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_clear_nhwindow;
case 1:return(void*)&p->win_display_nhwindow;
case 2:return(void*)&p->win_curs;
case 3:return(void*)&p->win_print_glyph;
case 4:return(void*)&p->win_delay_output;
default:abort();}}
case 50:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->uz;
case 3:return(void*)&p->uz0;
case 4:return(void*)&p->uprops;
case 5:return(void*)&p->xray_range;
case 6:return(void*)&p->unblind_telepat_range;
case 7:return(void*)&p->bc_felt;
case 8:return(void*)&p->umonster;
case 9:return(void*)&p->umonnum;
case 15:return(void*)&p->ustuck;
case 16:return(void*)&p->usteed;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_display_var0(char * a0,int a1){(impossible)(a0,a1);}
void teleport_display_var1(char * a0){(impossible)(a0);}
void teleport_display_var2(char * a0){(panic)(a0);}
void teleport_display_var3(char * a0,int a1,int a2,int a3,char * a4,int a5){(impossible)(a0,a1,a2,a3,a4,a5);}
void teleport_display_var4(char * a0,int a1,int a2,int a3,int a4){(impossible)(a0,a1,a2,a3,a4);}
void teleport_display_var5(short a0,short a1,char * a2,char * a3){(pline_xy)(a0,a1,a2,a3);}
void teleport_display_var6(char * a0,int a1){(impossible)(a0,a1);}
void teleport_display_var7(char * a0,int a1){(impossible)(a0,a1);}
void teleport_display_var8(char * a0){(impossible)(a0);}
void teleport_display_var9(char * a0){(impossible)(a0);}
void teleport_display_var10(char * a0,char * a1,int a2,unsigned int a3){(impossible)(a0,a1,a2,a3);}
void teleport_display_var11(char * a0,int a1){(impossible)(a0,a1);}
void teleport_display_var12(char * a0,int a1){(impossible)(a0,a1);}
void teleport_display_var13(char * a0,int a1){(impossible)(a0,a1);}
void teleport_display_var14(char * a0,char * a1,int a2){(impossible)(a0,a1,a2);}
void teleport_display_var15(char * a0,char * a1,int a2){(impossible)(a0,a1,a2);}
void teleport_display_var16(char * a0,char * a1,int a2){(impossible)(a0,a1,a2);}
void teleport_display_var17(char * a0,char * a1,int a2){(impossible)(a0,a1,a2);}
void teleport_display_var18(char * a0){(impossible)(a0);}
void teleport_display_var19(char * a0){(impossible)(a0);}
void teleport_display_var20(char * a0,int a1){(impossible)(a0,a1);}
void teleport_display_indirect0(void (*fn)(void)){fn();}
void teleport_display_indirect1(void (*fn)(void)){fn();}
void teleport_display_indirect2(void (*fn)(void)){fn();}
void teleport_display_indirect3(void (*fn)(winid, coordxy, coordxy, const glyph_info *, const glyph_info *),int a0,short a1,short a2,struct glyphinfo * a3,struct glyphinfo * a4){fn(a0,a1,a2,a3,a4);}
void teleport_display_indirect4(void (*fn)(winid, coordxy, coordxy, const glyph_info *, const glyph_info *),int a0,short a1,short a2,struct glyphinfo * a3,struct glyphinfo * a4){fn(a0,a1,a2,a3,a4);}
void teleport_display_indirect5(void (*fn)(winid, boolean),int a0,signed char a1){fn(a0,a1);}
void teleport_display_indirect6(void (*fn)(winid),int a0){fn(a0);}
void teleport_display_indirect7(void (*fn)(winid, coordxy, coordxy, const glyph_info *, const glyph_info *),int a0,short a1,short a2,struct glyphinfo * a3,struct glyphinfo * a4){fn(a0,a1,a2,a3,a4);}
void teleport_display_indirect8(void (*fn)(winid, int, int),int a0,int a1,int a2){fn(a0,a1,a2);}
void teleport_display_indirect9(void (*fn)(winid, boolean),int a0,signed char a1){fn(a0,a1);}
void teleport_display_dynamic0_panic(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
void teleport_display_dynamic0_impossible(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
extern void teleport_display_mimic_light_blocking(struct monst * a0);
uintptr_t teleport_display_owned_pointer(int i){switch(i){
case 0:return(uintptr_t)(teleport_display_mimic_light_blocking);
default:abort();}}
uintptr_t teleport_display_native_pointer(int i){switch(i){
default:abort();}}
#pragma clang diagnostic pop
void teleport_display_free(void*p){(free)(p);}
static char display_literals[1509];
char*teleport_display_literal_storage(void){return display_literals;}
size_t teleport_display_literal_capacity(void){return sizeof display_literals;}
static struct tmp_glyph display_backing_0;
static struct tmp_glyph * display_backing_1;
static short display_backing_2;
static short display_backing_3;
static short display_backing_4;
static short display_backing_5;
static signed char display_backing_6;
static signed char display_backing_7;
static struct glyphinfo display_backing_8;
extern const glyph_info nul_glyphinfo;
extern glyph_map glyphmap[9624];
static gbuf_entry display_backing_11;
static signed char display_backing_12;
static int display_backing_13;
static int display_backing_14;
extern const int zapcolors[8];
extern const int altarcolors[5];
extern const int explodecolors[7];
extern int wallcolors[5];
extern const seenV seenv_matrix[3][3];
static int display_backing_20[4][5];
static int display_backing_21[4][6];
static char display_backing_22[38];
void*teleport_display_storage(int i){switch(i){
case 0:return(void*)&display_backing_0;
case 1:return(void*)&display_backing_1;
case 2:return(void*)&display_backing_2;
case 3:return(void*)&display_backing_3;
case 4:return(void*)&display_backing_4;
case 5:return(void*)&display_backing_5;
case 6:return(void*)&display_backing_6;
case 7:return(void*)&display_backing_7;
case 8:return(void*)&display_backing_8;
case 9:return(void*)&nul_glyphinfo;
case 10:return(void*)&glyphmap;
case 11:return(void*)&display_backing_11;
case 12:return(void*)&display_backing_12;
case 13:return(void*)&display_backing_13;
case 14:return(void*)&display_backing_14;
case 15:return(void*)&zapcolors;
case 16:return(void*)&altarcolors;
case 17:return(void*)&explodecolors;
case 18:return(void*)&wallcolors;
case 19:return(void*)&seenv_matrix;
case 20:return(void*)&display_backing_20;
case 21:return(void*)&display_backing_21;
case 22:return(void*)&display_backing_22;
default:abort();}}
int teleport_display_dep_do_screen_description(const coord* a0,boolean a1,int a2,char * a3,const char ** a4,struct permonst ** a5){return (do_screen_description)(*a0,a1,a2,a3,a4,a5);}
