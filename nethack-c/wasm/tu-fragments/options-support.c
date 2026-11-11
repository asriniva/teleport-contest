/* OPTIONS typed field/header/dependency/storage transport only. Source algorithms remain JS. */
#include "../../../scripts/tu-options-layout.h"
extern int options_set_window_colors_flag;
extern struct condtests_t condtests[30];
extern struct instance_globals_saved_c svc;
extern struct instance_globals_f gf;
extern struct instance_globals_saved_b svb;
extern struct instance_globals_n gn;
extern const struct class_sym def_oc_syms[18];
extern struct objdescr obj_descr[482];
extern struct instance_globals_t gt;
extern const struct symdef def_warnsyms[6];
extern struct instance_globals_w gw;
extern const char hexdd[33];
extern struct instance_globals_m gm;
extern struct instance_globals_a ga;
extern winid WIN_INVEN;
extern struct instance_globals_v gv;
extern struct display_hints disp;
extern int wcolors_opt[4];
extern struct nomakedefs_s nomakedefs;
extern const char *const known_handling[];
extern const char *const vanqorders[][3];
extern const struct Role roles[];
extern const struct Race races[];
extern struct instance_globals_p gp;
extern const struct Gender genders[];
extern struct instance_globals_saved_p svp;
extern const char disclosure_options[];
extern struct objclass objects[482];
extern struct instance_globals_s gs;
extern struct instance_globals_saved_d svd;
extern const struct Align aligns[];
extern struct instance_globals_h gh;
extern struct instance_globals_d gd;
extern struct instance_globals_c gc;
extern struct sinfo program_state;
extern struct instance_globals_o go;
extern const glyph_info nul_glyphinfo;
extern const struct const_globals cg;
extern volatile struct window_procs windowprocs;
extern struct you u;
extern struct instance_flags iflags;
extern struct flag flags;
extern struct accessibility_data a11y;
#ifndef TELEPORT_REFERENCE_OPTIONS
int wcolors_opt[4];
int options_set_window_colors_flag;
#endif
#include <stdlib.h>
#include "../tu-options-abi.h"
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(size_t)==8,"Review OPTIONS LP64");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0&&sizeof(xint8)==1&&(xint8)-1<0&&sizeof(coordxy)==2&&(char)-1<0,"Review OPTIONS scalar widths");
void*teleport_options_global(int index){switch(index){
case 0:return(void*)&a11y;
case 1:return(void*)&flags;
case 2:return(void*)&iflags;
case 3:return(void*)&u;
case 4:return(void*)&windowprocs;
case 5:return(void*)&cg;
case 6:return(void*)&nul_glyphinfo;
case 7:return(void*)&go;
case 8:return(void*)&program_state;
case 9:return(void*)&gc;
case 10:return(void*)&gd;
case 11:return(void*)&gh;
case 12:return(void*)&aligns;
case 13:return(void*)&svd;
case 14:return(void*)&gs;
case 15:return(void*)&objects;
case 16:return(void*)&disclosure_options;
case 17:return(void*)&svp;
case 18:return(void*)&genders;
case 19:return(void*)&gp;
case 20:return(void*)&races;
case 21:return(void*)&roles;
case 22:return(void*)&vanqorders;
case 23:return(void*)&known_handling;
case 24:return(void*)&nomakedefs;
case 25:return(void*)&wcolors_opt;
case 26:return(void*)&disp;
case 27:return(void*)&gv;
case 28:return(void*)&WIN_INVEN;
case 29:return(void*)&ga;
case 30:return(void*)&gm;
case 31:return(void*)&hexdd;
case 32:return(void*)&gw;
case 33:return(void*)&def_warnsyms;
case 34:return(void*)&gt;
case 35:return(void*)&obj_descr;
case 36:return(void*)&def_oc_syms;
case 37:return(void*)&gn;
case 38:return(void*)&svb;
case 39:return(void*)&gf;
case 40:return(void*)&svc;
case 41:return(void*)&condtests;
case 42:return(void*)&options_set_window_colors_flag;
default:abort();}}
uint64_t teleport_options_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(struct teleport_options_menu_cmd_t));
case 6:return(uint64_t)(sizeof(struct Align));
case 7:return(uint64_t)(sizeof(struct Gender));
case 8:return(uint64_t)(sizeof(struct Race));
case 9:return(uint64_t)(sizeof(struct Role));
case 10:return(uint64_t)(sizeof(struct RoleName));
case 11:return(uint64_t)(sizeof(struct accessibility_data));
case 12:return(uint64_t)(sizeof(struct teleport_options_action));
case 13:return(uint64_t)(sizeof(struct allopt_t));
case 14:return(uint64_t)(sizeof(struct autopickup_exception));
case 15:return(uint64_t)(sizeof(struct class_sym));
case 16:return(uint64_t)(sizeof(struct cmd));
case 17:return(uint64_t)(sizeof(struct color_and_attr));
case 18:return(uint64_t)(sizeof(struct condtests_t));
case 19:return(uint64_t)(sizeof(struct const_globals));
case 20:return(uint64_t)(sizeof(struct context_info));
case 21:return(uint64_t)(sizeof(struct d_level));
case 22:return(uint64_t)(sizeof(struct dgn_topology));
case 23:return(uint64_t)(sizeof(struct display_hints));
case 24:return(uint64_t)(sizeof(struct flag));
case 25:return(uint64_t)(sizeof(struct fruit));
case 26:return(uint64_t)(sizeof(struct instance_flags));
case 27:return(uint64_t)(sizeof(struct instance_globals_a));
case 28:return(uint64_t)(sizeof(struct instance_globals_c));
case 29:return(uint64_t)(sizeof(struct instance_globals_d));
case 30:return(uint64_t)(sizeof(struct instance_globals_f));
case 31:return(uint64_t)(sizeof(struct instance_globals_h));
case 32:return(uint64_t)(sizeof(struct instance_globals_m));
case 33:return(uint64_t)(sizeof(struct instance_globals_n));
case 34:return(uint64_t)(sizeof(struct instance_globals_o));
case 35:return(uint64_t)(sizeof(struct instance_globals_p));
case 36:return(uint64_t)(sizeof(struct instance_globals_s));
case 37:return(uint64_t)(sizeof(struct instance_globals_saved_b));
case 38:return(uint64_t)(sizeof(struct instance_globals_saved_c));
case 39:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 40:return(uint64_t)(sizeof(struct instance_globals_saved_p));
case 41:return(uint64_t)(sizeof(struct instance_globals_t));
case 42:return(uint64_t)(sizeof(struct instance_globals_v));
case 43:return(uint64_t)(sizeof(struct instance_globals_w));
case 44:return(uint64_t)(sizeof(struct menucoloring));
case 45:return(uint64_t)(sizeof(struct teleport_options_menuscrollinfo));
case 46:return(uint64_t)(sizeof(struct mi));
case 47:return(uint64_t)(sizeof(struct nhcoord));
case 48:return(uint64_t)(sizeof(struct nomakedefs_s));
case 49:return(uint64_t)(sizeof(struct objclass));
case 50:return(uint64_t)(sizeof(struct objdescr));
case 51:return(uint64_t)(sizeof(struct teleport_options_objsymopt));
case 52:return(uint64_t)(sizeof(struct teleport_options_options_msgtype_name));
case 53:return(uint64_t)(sizeof(struct teleport_options_paranoia_opts));
case 54:return(uint64_t)(sizeof(struct plinemsg_type));
case 55:return(uint64_t)(sizeof(struct sinfo));
case 56:return(uint64_t)(sizeof(struct symdef));
case 57:return(uint64_t)(sizeof(struct symsetentry));
case 58:return(uint64_t)(sizeof(struct tc_gbl_data));
case 59:return(uint64_t)(sizeof(struct teleport_options_action));
case 60:return(uint64_t)(sizeof(struct teleport_options_menu_cmd_t));
case 61:return(uint64_t)(sizeof(struct teleport_options_menuscrollinfo));
case 62:return(uint64_t)(sizeof(struct teleport_options_objsymopt));
case 63:return(uint64_t)(sizeof(struct teleport_options_options_msgtype_name));
case 64:return(uint64_t)(sizeof(struct teleport_options_paranoia_opts));
case 65:return(uint64_t)(sizeof(struct teleport_options_xtra_cntrls));
case 66:return(uint64_t)(sizeof(struct u_roleplay));
case 67:return(uint64_t)(sizeof(struct wc_Opt));
case 68:return(uint64_t)(sizeof(struct window_procs));
case 69:return(uint64_t)(sizeof(struct windowcolors_struct));
case 70:return(uint64_t)(sizeof(struct teleport_options_xtra_cntrls));
case 71:return(uint64_t)(sizeof(struct you));
case 72:return(uint64_t)(sizeof(union any));
case 73:return(uint64_t)(AMULET_CLASS);
case 74:return(uint64_t)(ARMOR_CLASS);
case 75:return(uint64_t)(BALL_CLASS);
case 76:return(uint64_t)(BOULDER);
case 77:return(uint64_t)(BoolOpt);
case 78:return(uint64_t)(CHAIN_CLASS);
case 79:return(uint64_t)(COIN_CLASS);
case 80:return(uint64_t)(CONDITION_COUNT);
case 81:return(uint64_t)(CompOpt);
case 82:return(uint64_t)(EXT_ENCUMBER);
case 83:return(uint64_t)(FOOD_CLASS);
case 84:return(uint64_t)(GEM_CLASS);
case 85:return(uint64_t)(GFILTER_AREA);
case 86:return(uint64_t)(GFILTER_NONE);
case 87:return(uint64_t)(GFILTER_VIEW);
case 88:return(uint64_t)(GOLD_SYM);
case 89:return(uint64_t)(HVY_ENCUMBER);
case 90:return(uint64_t)(InvOptInUse);
case 91:return(uint64_t)(InvOptNone);
case 92:return(uint64_t)(InvOptOn);
case 93:return(uint64_t)(InvSparse);
case 94:return(uint64_t)(LOW_PM);
case 95:return(uint64_t)(MAP_OPTION);
case 96:return(uint64_t)(MAXMCLASSES);
case 97:return(uint64_t)(MAXOCLASSES);
case 98:return(uint64_t)(MAXPCHARS);
case 99:return(uint64_t)(MAX_ROLEOPT);
case 100:return(uint64_t)(MENU_OPTION);
case 101:return(uint64_t)(MESSAGE_OPTION);
case 102:return(uint64_t)(MOD_ENCUMBER);
case 103:return(uint64_t)(NUMMONS);
case 104:return(uint64_t)(NUM_GRAPHICS);
case 105:return(uint64_t)(No);
case 106:return(uint64_t)(OPTCOUNT);
case 107:return(uint64_t)(OVERLOADED);
case 108:return(uint64_t)(Off);
case 109:return(uint64_t)(On);
case 110:return(uint64_t)(OptS_Advanced);
case 111:return(uint64_t)(OptS_Behavior);
case 112:return(uint64_t)(OptS_General);
case 113:return(uint64_t)(OptS_Map);
case 114:return(uint64_t)(OptS_Status);
case 115:return(uint64_t)(OthrOpt);
case 116:return(uint64_t)(POTION_CLASS);
case 117:return(uint64_t)(PRIMARYSET);
case 118:return(uint64_t)(RING_CLASS);
case 119:return(uint64_t)(ROCK_CLASS);
case 120:return(uint64_t)(ROGUESET);
case 121:return(uint64_t)(RUN_CRAWL);
case 122:return(uint64_t)(RUN_LEAP);
case 123:return(uint64_t)(RUN_STEP);
case 124:return(uint64_t)(RUN_TPORT);
case 125:return(uint64_t)(SCROLL_CLASS);
case 126:return(uint64_t)(SLIME_MOLD);
case 127:return(uint64_t)(SLT_ENCUMBER);
case 128:return(uint64_t)(SPBOOK_CLASS);
case 129:return(uint64_t)(STATUS_OPTION);
case 130:return(uint64_t)(STONE);
case 131:return(uint64_t)(SYM_BOULDER);
case 132:return(uint64_t)(S_expl_br);
case 133:return(uint64_t)(S_stone);
case 134:return(uint64_t)(S_vbeam);
case 135:return(uint64_t)(S_water);
case 136:return(uint64_t)(TEXT_OPTION);
case 137:return(uint64_t)(TOOL_CLASS);
case 138:return(uint64_t)(TRAPNUM);
case 139:return(uint64_t)(Term_Excluded);
case 140:return(uint64_t)(Term_False);
case 141:return(uint64_t)(Term_Off);
case 142:return(uint64_t)(UNENCUMBERED);
case 143:return(uint64_t)(VANQ_MLVL_MNDX);
case 144:return(uint64_t)(VENOM_SYM);
case 145:return(uint64_t)(WAND_CLASS);
case 146:return(uint64_t)(WC_COUNT);
case 147:return(uint64_t)(WEAPON_CLASS);
case 148:return(uint64_t)(Yes);
case 149:return(uint64_t)(builtin_opt);
case 150:return(uint64_t)(cmdline_opt);
case 151:return(uint64_t)(do_custom_colors);
case 152:return(uint64_t)(do_custom_symbols);
case 153:return(uint64_t)(do_handler);
case 154:return(uint64_t)(do_init);
case 155:return(uint64_t)(do_set);
case 156:return(uint64_t)(environ_opt);
case 157:return(uint64_t)(get_cnf_val);
case 158:return(uint64_t)(get_val);
case 159:return(uint64_t)(gm_optionchange);
case 160:return(uint64_t)(num_opt_phases);
case 161:return(uint64_t)(num_terms);
case 162:return(uint64_t)(opt_BIOS);
case 163:return(uint64_t)(opt_DECgraphics);
case 164:return(uint64_t)(opt_IBMgraphics);
case 165:return(uint64_t)(opt_accessiblemsg);
case 166:return(uint64_t)(opt_acoustics);
case 167:return(uint64_t)(opt_align_message);
case 168:return(uint64_t)(opt_align_status);
case 169:return(uint64_t)(opt_alignment);
case 170:return(uint64_t)(opt_altkeyhandling);
case 171:return(uint64_t)(opt_altmeta);
case 172:return(uint64_t)(opt_armorstatus);
case 173:return(uint64_t)(opt_ascii_map);
case 174:return(uint64_t)(opt_autodescribe);
case 175:return(uint64_t)(opt_autodig);
case 176:return(uint64_t)(opt_autoopen);
case 177:return(uint64_t)(opt_autopickup);
case 178:return(uint64_t)(opt_autoquiver);
case 179:return(uint64_t)(opt_autounlock);
case 180:return(uint64_t)(opt_bgcolors);
case 181:return(uint64_t)(opt_blind);
case 182:return(uint64_t)(opt_bones);
case 183:return(uint64_t)(opt_boulder);
case 184:return(uint64_t)(opt_catname);
case 185:return(uint64_t)(opt_checkpoint);
case 186:return(uint64_t)(opt_cmdassist);
case 187:return(uint64_t)(opt_color);
case 188:return(uint64_t)(opt_confirm);
case 189:return(uint64_t)(opt_crash_email);
case 190:return(uint64_t)(opt_crash_name);
case 191:return(uint64_t)(opt_crash_urlmax);
case 192:return(uint64_t)(opt_customcolors);
case 193:return(uint64_t)(opt_customsymbols);
case 194:return(uint64_t)(opt_dark_room);
case 195:return(uint64_t)(opt_deaf);
case 196:return(uint64_t)(opt_debug_hunger);
case 197:return(uint64_t)(opt_debug_mongen);
case 198:return(uint64_t)(opt_debug_overwrite_stairs);
case 199:return(uint64_t)(opt_disclose);
case 200:return(uint64_t)(opt_dogname);
case 201:return(uint64_t)(opt_dropped_nopick);
case 202:return(uint64_t)(opt_dungeon);
case 203:return(uint64_t)(opt_effects);
case 204:return(uint64_t)(opt_eight_bit_tty);
case 205:return(uint64_t)(opt_extmenu);
case 206:return(uint64_t)(opt_female);
case 207:return(uint64_t)(opt_fireassist);
case 208:return(uint64_t)(opt_fixinv);
case 209:return(uint64_t)(opt_font_map);
case 210:return(uint64_t)(opt_font_menu);
case 211:return(uint64_t)(opt_font_message);
case 212:return(uint64_t)(opt_font_size_map);
case 213:return(uint64_t)(opt_font_size_menu);
case 214:return(uint64_t)(opt_font_size_message);
case 215:return(uint64_t)(opt_font_size_status);
case 216:return(uint64_t)(opt_font_size_text);
case 217:return(uint64_t)(opt_font_status);
case 218:return(uint64_t)(opt_font_text);
case 219:return(uint64_t)(opt_force_invmenu);
case 220:return(uint64_t)(opt_fruit);
case 221:return(uint64_t)(opt_fullscreen);
case 222:return(uint64_t)(opt_gender);
case 223:return(uint64_t)(opt_glyph);
case 224:return(uint64_t)(opt_goldX);
case 225:return(uint64_t)(opt_guicolor);
case 226:return(uint64_t)(opt_help);
case 227:return(uint64_t)(opt_herecmd_menu);
case 228:return(uint64_t)(opt_hilite_pet);
case 229:return(uint64_t)(opt_hilite_pile);
case 230:return(uint64_t)(opt_hilite_status);
case 231:return(uint64_t)(opt_hitpointbar);
case 232:return(uint64_t)(opt_horsename);
case 233:return(uint64_t)(opt_idlecheckpoint);
case 234:return(uint64_t)(opt_ignintr);
case 235:return(uint64_t)(opt_implicit_uncursed);
case 236:return(uint64_t)(opt_in);
case 237:return(uint64_t)(opt_legacy);
case 238:return(uint64_t)(opt_lit_corridor);
case 239:return(uint64_t)(opt_lootabc);
case 240:return(uint64_t)(opt_mail);
case 241:return(uint64_t)(opt_map_mode);
case 242:return(uint64_t)(opt_mention_decor);
case 243:return(uint64_t)(opt_mention_map);
case 244:return(uint64_t)(opt_mention_walls);
case 245:return(uint64_t)(opt_menu_deselect_all);
case 246:return(uint64_t)(opt_menu_deselect_page);
case 247:return(uint64_t)(opt_menu_first_page);
case 248:return(uint64_t)(opt_menu_headings);
case 249:return(uint64_t)(opt_menu_invert_all);
case 250:return(uint64_t)(opt_menu_invert_page);
case 251:return(uint64_t)(opt_menu_last_page);
case 252:return(uint64_t)(opt_menu_next_page);
case 253:return(uint64_t)(opt_menu_objsyms);
case 254:return(uint64_t)(opt_menu_overlay);
case 255:return(uint64_t)(opt_menu_previous_page);
case 256:return(uint64_t)(opt_menu_search);
case 257:return(uint64_t)(opt_menu_select_all);
case 258:return(uint64_t)(opt_menu_select_page);
case 259:return(uint64_t)(opt_menu_shift_left);
case 260:return(uint64_t)(opt_menu_shift_right);
case 261:return(uint64_t)(opt_menu_tab_sep);
case 262:return(uint64_t)(opt_menucolors);
case 263:return(uint64_t)(opt_menuinvertmode);
case 264:return(uint64_t)(opt_menustyle);
case 265:return(uint64_t)(opt_mon_movement);
case 266:return(uint64_t)(opt_monpolycontrol);
case 267:return(uint64_t)(opt_monsters);
case 268:return(uint64_t)(opt_montelecontrol);
case 269:return(uint64_t)(opt_mouse_support);
case 270:return(uint64_t)(opt_msg_window);
case 271:return(uint64_t)(opt_msghistory);
case 272:return(uint64_t)(opt_name);
case 273:return(uint64_t)(opt_news);
case 274:return(uint64_t)(opt_nudist);
case 275:return(uint64_t)(opt_null);
case 276:return(uint64_t)(opt_number_pad);
case 277:return(uint64_t)(opt_o_autocomplete);
case 278:return(uint64_t)(opt_o_autopickup_exceptions);
case 279:return(uint64_t)(opt_o_bind_keys);
case 280:return(uint64_t)(opt_o_menu_colors);
case 281:return(uint64_t)(opt_o_message_types);
case 282:return(uint64_t)(opt_o_status_cond);
case 283:return(uint64_t)(opt_o_status_hilites);
case 284:return(uint64_t)(opt_objects);
case 285:return(uint64_t)(opt_out);
case 286:return(uint64_t)(opt_packorder);
case 287:return(uint64_t)(opt_paranoid_confirmation);
case 288:return(uint64_t)(opt_pauper);
case 289:return(uint64_t)(opt_perm_invent);
case 290:return(uint64_t)(opt_perminv_mode);
case 291:return(uint64_t)(opt_petattr);
case 292:return(uint64_t)(opt_pettype);
case 293:return(uint64_t)(opt_pickup_burden);
case 294:return(uint64_t)(opt_pickup_stolen);
case 295:return(uint64_t)(opt_pickup_thrown);
case 296:return(uint64_t)(opt_pickup_types);
case 297:return(uint64_t)(opt_pile_limit);
case 298:return(uint64_t)(opt_player_selection);
case 299:return(uint64_t)(opt_playmode);
case 300:return(uint64_t)(opt_popup_dialog);
case 301:return(uint64_t)(opt_preload_tiles);
case 302:return(uint64_t)(opt_price_quotes);
case 303:return(uint64_t)(opt_pushweapon);
case 304:return(uint64_t)(opt_query_menu);
case 305:return(uint64_t)(opt_quick_farsight);
case 306:return(uint64_t)(opt_race);
case 307:return(uint64_t)(opt_rawio);
case 308:return(uint64_t)(opt_reroll);
case 309:return(uint64_t)(opt_rest_on_space);
case 310:return(uint64_t)(opt_roguesymset);
case 311:return(uint64_t)(opt_role);
case 312:return(uint64_t)(opt_runmode);
case 313:return(uint64_t)(opt_safe_pet);
case 314:return(uint64_t)(opt_safe_wait);
case 315:return(uint64_t)(opt_sanity_check);
case 316:return(uint64_t)(opt_scores);
case 317:return(uint64_t)(opt_scroll_amount);
case 318:return(uint64_t)(opt_scroll_margin);
case 319:return(uint64_t)(opt_selectsaved);
case 320:return(uint64_t)(opt_showdamage);
case 321:return(uint64_t)(opt_showexp);
case 322:return(uint64_t)(opt_showrace);
case 323:return(uint64_t)(opt_showscore);
case 324:return(uint64_t)(opt_showvers);
case 325:return(uint64_t)(opt_silent);
case 326:return(uint64_t)(opt_softkeyboard);
case 327:return(uint64_t)(opt_sortdiscoveries);
case 328:return(uint64_t)(opt_sortloot);
case 329:return(uint64_t)(opt_sortpack);
case 330:return(uint64_t)(opt_sortvanquished);
case 331:return(uint64_t)(opt_soundlib);
case 332:return(uint64_t)(opt_sounds);
case 333:return(uint64_t)(opt_sparkle);
case 334:return(uint64_t)(opt_splash_screen);
case 335:return(uint64_t)(opt_spot_monsters);
case 336:return(uint64_t)(opt_standout);
case 337:return(uint64_t)(opt_status_updates);
case 338:return(uint64_t)(opt_statushilites);
case 339:return(uint64_t)(opt_statuslines);
case 340:return(uint64_t)(opt_suppress_alert);
case 341:return(uint64_t)(opt_symset);
case 342:return(uint64_t)(opt_term_cols);
case 343:return(uint64_t)(opt_term_rows);
case 344:return(uint64_t)(opt_terrainstatus);
case 345:return(uint64_t)(opt_tile_file);
case 346:return(uint64_t)(opt_tile_height);
case 347:return(uint64_t)(opt_tile_width);
case 348:return(uint64_t)(opt_tiled_map);
case 349:return(uint64_t)(opt_time);
case 350:return(uint64_t)(opt_timed_delay);
case 351:return(uint64_t)(opt_tips);
case 352:return(uint64_t)(opt_tombstone);
case 353:return(uint64_t)(opt_toptenwin);
case 354:return(uint64_t)(opt_traps);
case 355:return(uint64_t)(opt_travel);
case 356:return(uint64_t)(opt_travel_debug);
case 357:return(uint64_t)(opt_tutorial);
case 358:return(uint64_t)(opt_use_darkgray);
case 359:return(uint64_t)(opt_use_inverse);
case 360:return(uint64_t)(opt_use_truecolor);
case 361:return(uint64_t)(opt_vary_msgcount);
case 362:return(uint64_t)(opt_verbose);
case 363:return(uint64_t)(opt_versinfo);
case 364:return(uint64_t)(opt_voices);
case 365:return(uint64_t)(opt_vt_sounddata);
case 366:return(uint64_t)(opt_vt_tiledata);
case 367:return(uint64_t)(opt_warnings);
case 368:return(uint64_t)(opt_weaponstatus);
case 369:return(uint64_t)(opt_whatis_coord);
case 370:return(uint64_t)(opt_whatis_filter);
case 371:return(uint64_t)(opt_whatis_menu);
case 372:return(uint64_t)(opt_whatis_moveskip);
case 373:return(uint64_t)(opt_windowborders);
case 374:return(uint64_t)(opt_windowcolors);
case 375:return(uint64_t)(opt_windowtype);
case 376:return(uint64_t)(opt_wizmgender);
case 377:return(uint64_t)(opt_wizweight);
case 378:return(uint64_t)(opt_wraptext);
case 379:return(uint64_t)(optn_err);
case 380:return(uint64_t)(optn_ok);
case 381:return(uint64_t)(optn_silenterr);
case 382:return(uint64_t)(pfx_cond_);
case 383:return(uint64_t)(pfx_font);
case 384:return(uint64_t)(play_opt);
case 385:return(uint64_t)(set_gameview);
case 386:return(uint64_t)(set_hidden);
case 387:return(uint64_t)(set_in_config);
case 388:return(uint64_t)(set_in_game);
case 389:return(uint64_t)(set_in_sysconf);
case 390:return(uint64_t)(set_wiznofuz);
case 391:return(uint64_t)(set_wizonly);
case 392:return(uint64_t)(syscf_opt);
case 393:return(uint64_t)(wcolor_menu);
case 394:return(uint64_t)(wcolor_message);
case 395:return(uint64_t)(wcolor_status);
case 396:return(uint64_t)(wcolor_text);
case 397:return(uint64_t)(wp_curses);
case 398:return(uint64_t)(wp_tty);
case 399:return(uint64_t)(((enum OptSection)-1)<0);
case 400:return(uint64_t)(((enum OptType)-1)<0);
case 401:return(uint64_t)(((enum Y_N)-1)<0);
case 402:return(uint64_t)(((enum menu_terminology_preference)-1)<0);
case 403:return(uint64_t)(((enum opt)-1)<0);
case 404:return(uint64_t)(((enum option_phases)-1)<0);
case 405:return(uint64_t)(((enum optn_result)-1)<0);
case 406:return(uint64_t)(((enum optset_restrictions)-1)<0);
case 407:return(uint64_t)(((enum requests)-1)<0);
case 408:return(uint64_t)(((enum soundlib_ids)-1)<0);
case 409:return(uint64_t)(((enum symset_handling_types)-1)<0);
case 410:return(uint64_t)(((enum window_option_types)-1)<0);
case 411:return(uint64_t)(((enum wp_ids)-1)<0);
default:abort();}}
uint64_t teleport_options_read(int kind,void*at,int field){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->adj);
default:abort();}}
case 1:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->adj);
default:abort();}}
case 2:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->noun);
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 4:{struct RoleName*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->m);
default:abort();}}
case 5:{struct accessibility_data*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->accessiblemsg);
case 1:return(uint64_t)(uintptr_t)(&p->msg_loc);
case 2:return(uint64_t)(uintptr_t)(p->mon_notices);
case 3:return(uint64_t)(uintptr_t)(p->mon_movement);
case 4:return(uint64_t)(uintptr_t)(p->glyph_updates);
default:abort();}}
case 6:{struct teleport_options_action*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->letr);
case 1:return(uint64_t)(uintptr_t)(p->desc);
default:abort();}}
case 7:{struct allopt_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->section);
case 2:return(uint64_t)(uintptr_t)(p->minmatch);
case 3:return(uint64_t)(uintptr_t)(p->expectedbuf);
case 4:return(uint64_t)(uintptr_t)(p->idx);
case 5:return(uint64_t)(uintptr_t)(p->setwhere);
case 6:return(uint64_t)(uintptr_t)(p->opttyp);
case 7:return(uint64_t)(uintptr_t)(p->negateok);
case 8:return(uint64_t)(uintptr_t)(p->valok);
case 9:return(uint64_t)(uintptr_t)(p->dupeok);
case 10:return(uint64_t)(uintptr_t)(p->pfx);
case 11:return(uint64_t)(uintptr_t)(p->termpref);
case 12:return(uint64_t)(uintptr_t)(p->opt_in_out);
case 13:return(uint64_t)(uintptr_t)(p->addr);
case 14:return(uint64_t)(uintptr_t)(p->optfn);
case 15:return(uint64_t)(uintptr_t)(p->alias);
case 16:return(uint64_t)(uintptr_t)(p->descr);
case 17:return(uint64_t)(uintptr_t)(p->prefixgw);
case 18:return(uint64_t)(uintptr_t)(p->initval);
case 19:return(uint64_t)(uintptr_t)(p->has_handler);
case 20:return(uint64_t)(uintptr_t)(p->dupdetected);
case 21:return(uint64_t)(uintptr_t)(p->disregarded);
default:abort();}}
case 8:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_void);
case 1:return(uint64_t)(uintptr_t)(p->a_int);
case 2:return(uint64_t)(uintptr_t)(p->a_char);
default:abort();}}
case 9:{struct autopickup_exception*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->regex);
case 1:return(uint64_t)(uintptr_t)(p->pattern);
case 2:return(uint64_t)(uintptr_t)(p->grab);
case 3:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 10:{struct class_sym*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sym);
default:abort();}}
case 11:{struct cmd*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->num_pad);
case 1:return(uint64_t)(uintptr_t)(p->pcHack_compat);
case 2:return(uint64_t)(uintptr_t)(p->phone_layout);
case 3:return(uint64_t)(uintptr_t)(p->swap_yz);
default:abort();}}
case 12:{struct color_and_attr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->color);
case 1:return(uint64_t)(uintptr_t)(p->attr);
default:abort();}}
case 13:{struct condtests_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->enabled);
default:abort();}}
case 14:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 15:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->current_fruit);
default:abort();}}
case 16:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 17:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_rogue_level);
default:abort();}}
case 18:{struct display_hints*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->botl);
case 1:return(uint64_t)(uintptr_t)(p->botlx);
default:abort();}}
case 19:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->acoustics);
case 1:return(uint64_t)(uintptr_t)(p->armorstatus);
case 2:return(uint64_t)(uintptr_t)(p->autodig);
case 3:return(uint64_t)(uintptr_t)(p->autoquiver);
case 4:return(uint64_t)(uintptr_t)(p->autoopen);
case 5:return(uint64_t)(uintptr_t)(p->biff);
case 6:return(uint64_t)(uintptr_t)(p->bones);
case 7:return(uint64_t)(uintptr_t)(p->confirm);
case 8:return(uint64_t)(uintptr_t)(p->dark_room);
case 9:return(uint64_t)(uintptr_t)(p->debug);
case 10:return(uint64_t)(uintptr_t)(p->end_own);
case 11:return(uint64_t)(uintptr_t)(p->explore);
case 12:return(uint64_t)(uintptr_t)(p->female);
case 13:return(uint64_t)(uintptr_t)(p->goldX);
case 14:return(uint64_t)(uintptr_t)(p->help);
case 15:return(uint64_t)(uintptr_t)(p->tips);
case 16:return(uint64_t)(uintptr_t)(p->tutorial);
case 17:return(uint64_t)(uintptr_t)(p->ignintr);
case 18:return(uint64_t)(uintptr_t)(p->implicit_uncursed);
case 19:return(uint64_t)(uintptr_t)(p->ins_chkpt);
case 20:return(uint64_t)(uintptr_t)(p->invlet_constant);
case 21:return(uint64_t)(uintptr_t)(p->legacy);
case 22:return(uint64_t)(uintptr_t)(p->lit_corridor);
case 23:return(uint64_t)(uintptr_t)(p->mention_decor);
case 24:return(uint64_t)(uintptr_t)(p->mention_walls);
case 25:return(uint64_t)(uintptr_t)(p->nopick_dropped);
case 26:return(uint64_t)(uintptr_t)(p->null);
case 27:return(uint64_t)(uintptr_t)(p->pickup);
case 28:return(uint64_t)(uintptr_t)(p->pickup_stolen);
case 29:return(uint64_t)(uintptr_t)(p->pickup_thrown);
case 30:return(uint64_t)(uintptr_t)(p->pushweapon);
case 31:return(uint64_t)(uintptr_t)(p->quick_farsight);
case 32:return(uint64_t)(uintptr_t)(p->rest_on_space);
case 33:return(uint64_t)(uintptr_t)(p->safe_dog);
case 34:return(uint64_t)(uintptr_t)(p->safe_wait);
case 35:return(uint64_t)(uintptr_t)(p->showexp);
case 36:return(uint64_t)(uintptr_t)(p->showvers);
case 37:return(uint64_t)(uintptr_t)(p->silent);
case 38:return(uint64_t)(uintptr_t)(p->sortpack);
case 39:return(uint64_t)(uintptr_t)(p->sparkle);
case 40:return(uint64_t)(uintptr_t)(p->standout);
case 41:return(uint64_t)(uintptr_t)(p->terrainstatus);
case 42:return(uint64_t)(uintptr_t)(p->time);
case 43:return(uint64_t)(uintptr_t)(p->tombstone);
case 44:return(uint64_t)(uintptr_t)(p->verbose);
case 45:return(uint64_t)(uintptr_t)(p->weaponstatus);
case 46:return(uint64_t)(uintptr_t)(p->end_top);
case 47:return(uint64_t)(uintptr_t)(p->end_around);
case 48:return(uint64_t)(uintptr_t)(p->autounlock);
case 49:return(uint64_t)(uintptr_t)(p->suppress_alert);
case 50:return(uint64_t)(uintptr_t)(p->paranoia_bits);
case 51:return(uint64_t)(uintptr_t)(p->versinfo);
case 52:return(uint64_t)(uintptr_t)(p->pickup_burden);
case 53:return(uint64_t)(uintptr_t)(p->pile_limit);
case 54:return(uint64_t)(uintptr_t)(p->discosort);
case 55:return(uint64_t)(uintptr_t)(p->sortloot);
case 56:return(uint64_t)(uintptr_t)(p->vanq_sortmode);
case 57:return(uint64_t)(uintptr_t)(&p->inv_order);
case 58:return(uint64_t)(uintptr_t)(&p->pickup_types);
case 59:return(uint64_t)(uintptr_t)(&p->end_disclose);
case 60:return(uint64_t)(uintptr_t)(p->menu_style);
case 61:return(uint64_t)(uintptr_t)(p->made_fruit);
case 62:return(uint64_t)(uintptr_t)(p->initrole);
case 63:return(uint64_t)(uintptr_t)(p->initrace);
case 64:return(uint64_t)(uintptr_t)(p->initgend);
case 65:return(uint64_t)(uintptr_t)(p->initalign);
case 66:return(uint64_t)(uintptr_t)(p->lootabc);
case 67:return(uint64_t)(uintptr_t)(p->showrace);
case 68:return(uint64_t)(uintptr_t)(p->travelcmd);
case 69:return(uint64_t)(uintptr_t)(p->runmode);
default:abort();}}
case 20:{struct fruit*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->fname);
case 1:return(uint64_t)(uintptr_t)(p->fid);
case 2:return(uint64_t)(uintptr_t)(p->nextf);
default:abort();}}
case 21:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->herecmd_menu);
case 1:return(uint64_t)(uintptr_t)(p->idlecheckpoint);
case 2:return(uint64_t)(uintptr_t)(p->query_menu);
case 3:return(uint64_t)(uintptr_t)(p->showdamage);
case 4:return(uint64_t)(uintptr_t)(p->debug_fuzzer);
case 5:return(uint64_t)(uintptr_t)(p->getloc_filter);
case 6:return(uint64_t)(uintptr_t)(p->menuobjsyms);
case 7:return(uint64_t)(uintptr_t)(p->bgcolors);
case 8:return(uint64_t)(uintptr_t)(p->getloc_moveskip);
case 9:return(uint64_t)(uintptr_t)(p->getloc_usemenu);
case 10:return(uint64_t)(uintptr_t)(p->trav_debug);
case 11:return(uint64_t)(uintptr_t)(p->window_inited);
case 12:return(uint64_t)(uintptr_t)(p->sanity_check);
case 13:return(uint64_t)(uintptr_t)(p->debug_overwrite_stairs);
case 14:return(uint64_t)(uintptr_t)(p->debug_mongen);
case 15:return(uint64_t)(uintptr_t)(p->debug_hunger);
case 16:return(uint64_t)(uintptr_t)(p->mon_polycontrol);
case 17:return(uint64_t)(uintptr_t)(p->mon_telecontrol);
case 18:return(uint64_t)(uintptr_t)(p->initoptions_noterminate);
case 19:return(uint64_t)(uintptr_t)(p->msg_history);
case 20:return(uint64_t)(uintptr_t)(p->getpos_coords);
case 21:return(uint64_t)(uintptr_t)(p->menuinvertmode);
case 22:return(uint64_t)(uintptr_t)(&p->menu_headings);
case 23:return(uint64_t)(uintptr_t)(p->use_truecolor);
case 24:return(uint64_t)(uintptr_t)(p->altmeta);
case 25:return(uint64_t)(uintptr_t)(p->autodescribe);
case 26:return(uint64_t)(uintptr_t)(p->deferred_X);
case 27:return(uint64_t)(uintptr_t)(p->force_invmenu);
case 28:return(uint64_t)(uintptr_t)(p->hilite_pile);
case 29:return(uint64_t)(uintptr_t)(p->menu_head_objsym);
case 30:return(uint64_t)(uintptr_t)(p->menu_overlay);
case 31:return(uint64_t)(uintptr_t)(p->menu_requested);
case 32:return(uint64_t)(uintptr_t)(p->menu_tab_sep);
case 33:return(uint64_t)(uintptr_t)(p->news);
case 34:return(uint64_t)(uintptr_t)(p->num_pad);
case 35:return(uint64_t)(uintptr_t)(p->perm_invent);
case 36:return(uint64_t)(uintptr_t)(p->pricequotes);
case 37:return(uint64_t)(uintptr_t)(p->sounds);
case 38:return(uint64_t)(uintptr_t)(p->status_updates);
case 39:return(uint64_t)(uintptr_t)(p->toptenwin);
case 40:return(uint64_t)(uintptr_t)(p->use_menu_color);
case 41:return(uint64_t)(uintptr_t)(p->use_menu_glyphs);
case 42:return(uint64_t)(uintptr_t)(p->hilite_delta);
case 43:return(uint64_t)(uintptr_t)(p->voices);
case 44:return(uint64_t)(uintptr_t)(p->prev_decor);
case 45:return(uint64_t)(uintptr_t)(p->num_pad_mode);
case 46:return(uint64_t)(uintptr_t)(p->perminv_mode);
case 47:return(uint64_t)(uintptr_t)(p->prevmsg_window);
case 48:return(uint64_t)(uintptr_t)(p->extmenu);
case 49:return(uint64_t)(uintptr_t)(p->cmdassist);
case 50:return(uint64_t)(uintptr_t)(p->fireassist);
case 51:return(uint64_t)(uintptr_t)(p->wizweight);
case 52:return(uint64_t)(uintptr_t)(p->wizmgender);
case 53:return(uint64_t)(uintptr_t)(p->customcolors);
case 54:return(uint64_t)(uintptr_t)(p->customsymbols);
case 55:return(uint64_t)(uintptr_t)(p->wc_color);
case 56:return(uint64_t)(uintptr_t)(p->wc_hilite_pet);
case 57:return(uint64_t)(uintptr_t)(p->wc_ascii_map);
case 58:return(uint64_t)(uintptr_t)(p->wc_tiled_map);
case 59:return(uint64_t)(uintptr_t)(p->wc_preload_tiles);
case 60:return(uint64_t)(uintptr_t)(p->wc_tile_width);
case 61:return(uint64_t)(uintptr_t)(p->wc_tile_height);
case 62:return(uint64_t)(uintptr_t)(p->wc_tile_file);
case 63:return(uint64_t)(uintptr_t)(p->wc_inverse);
case 64:return(uint64_t)(uintptr_t)(p->wc_align_status);
case 65:return(uint64_t)(uintptr_t)(p->wc_align_message);
case 66:return(uint64_t)(uintptr_t)(p->wc_vary_msgcount);
case 67:return(uint64_t)(uintptr_t)(&p->wcolors);
case 68:return(uint64_t)(uintptr_t)(p->wc_font_map);
case 69:return(uint64_t)(uintptr_t)(p->wc_font_message);
case 70:return(uint64_t)(uintptr_t)(p->wc_font_status);
case 71:return(uint64_t)(uintptr_t)(p->wc_font_menu);
case 72:return(uint64_t)(uintptr_t)(p->wc_font_text);
case 73:return(uint64_t)(uintptr_t)(p->wc_fontsiz_map);
case 74:return(uint64_t)(uintptr_t)(p->wc_fontsiz_message);
case 75:return(uint64_t)(uintptr_t)(p->wc_fontsiz_status);
case 76:return(uint64_t)(uintptr_t)(p->wc_fontsiz_menu);
case 77:return(uint64_t)(uintptr_t)(p->wc_fontsiz_text);
case 78:return(uint64_t)(uintptr_t)(p->wc_scroll_amount);
case 79:return(uint64_t)(uintptr_t)(p->wc_scroll_margin);
case 80:return(uint64_t)(uintptr_t)(p->wc_map_mode);
case 81:return(uint64_t)(uintptr_t)(p->wc_player_selection);
case 82:return(uint64_t)(uintptr_t)(p->wc_splash_screen);
case 83:return(uint64_t)(uintptr_t)(p->wc_popup_dialog);
case 84:return(uint64_t)(uintptr_t)(p->wc_eight_bit_input);
case 85:return(uint64_t)(uintptr_t)(p->wc2_fullscreen);
case 86:return(uint64_t)(uintptr_t)(p->wc2_softkeyboard);
case 87:return(uint64_t)(uintptr_t)(p->wc2_wraptext);
case 88:return(uint64_t)(uintptr_t)(p->wc2_selectsaved);
case 89:return(uint64_t)(uintptr_t)(p->wc2_darkgray);
case 90:return(uint64_t)(uintptr_t)(p->wc2_hitpointbar);
case 91:return(uint64_t)(uintptr_t)(p->wc2_guicolor);
case 92:return(uint64_t)(uintptr_t)(p->wc_mouse_support);
case 93:return(uint64_t)(uintptr_t)(p->wc2_term_cols);
case 94:return(uint64_t)(uintptr_t)(p->wc2_term_rows);
case 95:return(uint64_t)(uintptr_t)(p->wc2_statuslines);
case 96:return(uint64_t)(uintptr_t)(p->wc2_windowborders);
case 97:return(uint64_t)(uintptr_t)(p->wc2_petattr);
case 98:return(uint64_t)(uintptr_t)(p->windowtype_locked);
case 99:return(uint64_t)(uintptr_t)(p->windowtype_deferred);
default:abort();}}
case 22:{struct instance_globals_a*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->apelist);
default:abort();}}
case 23:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->Cmd);
case 1:return(uint64_t)(uintptr_t)(&p->chosen_windowtype);
case 2:return(uint64_t)(uintptr_t)(&p->catname);
case 3:return(uint64_t)(uintptr_t)(p->crash_email);
case 4:return(uint64_t)(uintptr_t)(p->crash_name);
case 5:return(uint64_t)(uintptr_t)(p->crash_urlmax);
case 6:return(uint64_t)(uintptr_t)(p->currentgraphics);
case 7:return(uint64_t)(uintptr_t)(p->cmdline_windowsys);
case 8:return(uint64_t)(uintptr_t)(p->chosen_soundlib);
default:abort();}}
case 24:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dogname);
case 1:return(uint64_t)(uintptr_t)(p->deferred_showpaths);
default:abort();}}
case 25:{struct instance_globals_f*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ffruit);
default:abort();}}
case 26:{struct instance_globals_h*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->horsename);
default:abort();}}
case 27:{struct instance_globals_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->menu_colorings);
case 1:return(uint64_t)(uintptr_t)(&p->mapped_menu_cmds);
case 2:return(uint64_t)(uintptr_t)(&p->mapped_menu_op);
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->n_menu_mapped);
default:abort();}}
case 29:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->ov_primary_syms);
case 1:return(uint64_t)(uintptr_t)(&p->ov_rogue_syms);
case 2:return(uint64_t)(uintptr_t)(p->opt_phase);
case 3:return(uint64_t)(uintptr_t)(p->opt_initial);
case 4:return(uint64_t)(uintptr_t)(p->opt_from_file);
case 5:return(uint64_t)(uintptr_t)(p->opt_need_redraw);
case 6:return(uint64_t)(uintptr_t)(p->opt_need_glyph_reset);
case 7:return(uint64_t)(uintptr_t)(p->opt_need_promptstyle);
case 8:return(uint64_t)(uintptr_t)(p->opt_reset_customcolors);
case 9:return(uint64_t)(uintptr_t)(p->opt_reset_customsymbols);
case 10:return(uint64_t)(uintptr_t)(p->opt_update_basic_palette);
case 11:return(uint64_t)(uintptr_t)(p->opt_symset_changed);
default:abort();}}
case 30:{struct instance_globals_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->plnamelen);
case 1:return(uint64_t)(uintptr_t)(p->pl_race);
case 2:return(uint64_t)(uintptr_t)(p->plinemsg_types);
case 3:return(uint64_t)(uintptr_t)(p->preferred_pet);
default:abort();}}
case 31:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->symset);
case 1:return(uint64_t)(uintptr_t)(&p->showsyms);
case 2:return(uint64_t)(uintptr_t)(p->simple_options_help);
default:abort();}}
case 32:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bases);
default:abort();}}
case 33:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 34:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 35:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->plname);
case 1:return(uint64_t)(uintptr_t)(&p->pl_character);
case 2:return(uint64_t)(uintptr_t)(&p->pl_fruit);
default:abort();}}
case 36:{struct instance_globals_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->tc_gbl_data);
default:abort();}}
case 37:{struct instance_globals_v*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->vision_full_recalc);
default:abort();}}
case 38:{struct instance_globals_w*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->warnsyms);
case 1:return(uint64_t)(uintptr_t)(&p->wizkit);
default:abort();}}
case 39:{struct teleport_options_menu_cmd_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->cmd);
case 2:return(uint64_t)(uintptr_t)(p->desc);
default:abort();}}
case 40:{struct menucoloring*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->origstr);
case 1:return(uint64_t)(uintptr_t)(p->color);
case 2:return(uint64_t)(uintptr_t)(p->attr);
case 3:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 41:{struct teleport_options_menuscrollinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->cmdkey);
case 1:return(uint64_t)(uintptr_t)(p->maskindx);
default:abort();}}
case 42:{struct mi*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 43:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 44:{struct nomakedefs_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->git_branch);
default:abort();}}
case 45:{struct objclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name_idx);
case 1:return(uint64_t)(uintptr_t)(p->oc_class);
default:abort();}}
case 46:{struct objdescr*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->oc_name);
default:abort();}}
case 47:{struct teleport_options_objsymopt*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->num);
case 1:return(uint64_t)(uintptr_t)(p->nam);
case 2:return(uint64_t)(uintptr_t)(p->descr);
default:abort();}}
case 48:{struct teleport_options_options_msgtype_name*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->msgtyp);
case 2:return(uint64_t)(uintptr_t)(p->descr);
default:abort();}}
case 49:{struct teleport_options_paranoia_opts*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->flagmask);
case 1:return(uint64_t)(uintptr_t)(p->argname);
case 2:return(uint64_t)(uintptr_t)(p->argMinLen);
case 3:return(uint64_t)(uintptr_t)(p->synonym);
case 4:return(uint64_t)(uintptr_t)(p->synMinLen);
case 5:return(uint64_t)(uintptr_t)(p->explain);
default:abort();}}
case 50:{struct plinemsg_type*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->msgtype);
case 1:return(uint64_t)(uintptr_t)(p->regex);
case 2:return(uint64_t)(uintptr_t)(p->pattern);
case 3:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 51:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_parseoptions);
default:abort();}}
case 52:{struct symdef*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sym);
default:abort();}}
case 53:{struct symsetentry*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->handling);
case 2:return(uint64_t)(uintptr_t)(p->explicitly);
default:abort();}}
case 54:{struct tc_gbl_data*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->tc_AS);
case 1:return(uint64_t)(uintptr_t)(p->tc_AE);
default:abort();}}
case 55:{struct u_roleplay*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->blind);
case 1:return(uint64_t)(uintptr_t)(p->nudist);
case 2:return(uint64_t)(uintptr_t)(p->deaf);
case 3:return(uint64_t)(uintptr_t)(p->pauper);
case 4:return(uint64_t)(uintptr_t)(p->reroll);
default:abort();}}
case 56:{struct wc_Opt*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->wc_name);
case 1:return(uint64_t)(uintptr_t)(p->wc_bit);
default:abort();}}
case 57:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->wp_id);
case 2:return(uint64_t)(uintptr_t)(p->wincap);
case 3:return(uint64_t)(uintptr_t)(p->wincap2);
case 4:return(uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 5:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 6:return(uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 7:return(uint64_t)(uintptr_t)(p->win_putstr);
case 8:return(uint64_t)(uintptr_t)(p->win_display_file);
case 9:return(uint64_t)(uintptr_t)(p->win_start_menu);
case 10:return(uint64_t)(uintptr_t)(p->win_end_menu);
case 11:return(uint64_t)(uintptr_t)(p->win_wait_synch);
case 12:return(uint64_t)(uintptr_t)(p->win_number_pad);
case 13:return(uint64_t)(uintptr_t)(p->win_preference_update);
default:abort();}}
case 58:{struct windowcolors_struct*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->fg);
case 1:return(uint64_t)(uintptr_t)(p->bg);
default:abort();}}
case 59:{struct teleport_options_xtra_cntrls*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->key);
case 1:return(uint64_t)(uintptr_t)(p->desc);
default:abort();}}
case 60:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->uz);
case 1:return(uint64_t)(uintptr_t)(&p->uroleplay);
default:abort();}}
default:abort();}}
void teleport_options_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:p->adj=(__typeof__(p->adj))value;return;
default:abort();}}
case 1:{struct Gender*p=at;switch(field){
case 0:p->adj=(__typeof__(p->adj))value;return;
default:abort();}}
case 2:{struct Race*p=at;switch(field){
case 0:p->noun=(__typeof__(p->noun))value;return;
default:abort();}}
case 3:{struct Role*p=at;switch(field){
default:abort();}}
case 4:{struct RoleName*p=at;switch(field){
case 0:p->m=(__typeof__(p->m))value;return;
default:abort();}}
case 5:{struct accessibility_data*p=at;switch(field){
case 0:p->accessiblemsg=(__typeof__(p->accessiblemsg))value;return;
case 2:p->mon_notices=(__typeof__(p->mon_notices))value;return;
case 3:p->mon_movement=(__typeof__(p->mon_movement))value;return;
case 4:p->glyph_updates=(__typeof__(p->glyph_updates))value;return;
default:abort();}}
case 6:{struct teleport_options_action*p=at;switch(field){
case 0:p->letr=(__typeof__(p->letr))value;return;
case 1:p->desc=(__typeof__(p->desc))value;return;
default:abort();}}
case 7:{struct allopt_t*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->section=(__typeof__(p->section))value;return;
case 2:p->minmatch=(__typeof__(p->minmatch))value;return;
case 3:p->expectedbuf=(__typeof__(p->expectedbuf))value;return;
case 4:p->idx=(__typeof__(p->idx))value;return;
case 5:p->setwhere=(__typeof__(p->setwhere))value;return;
case 6:p->opttyp=(__typeof__(p->opttyp))value;return;
case 7:p->negateok=(__typeof__(p->negateok))value;return;
case 8:p->valok=(__typeof__(p->valok))value;return;
case 9:p->dupeok=(__typeof__(p->dupeok))value;return;
case 10:p->pfx=(__typeof__(p->pfx))value;return;
case 11:p->termpref=(__typeof__(p->termpref))value;return;
case 12:p->opt_in_out=(__typeof__(p->opt_in_out))value;return;
case 13:p->addr=(__typeof__(p->addr))value;return;
case 14:p->optfn=(__typeof__(p->optfn))value;return;
case 15:p->alias=(__typeof__(p->alias))value;return;
case 16:p->descr=(__typeof__(p->descr))value;return;
case 17:p->prefixgw=(__typeof__(p->prefixgw))value;return;
case 18:p->initval=(__typeof__(p->initval))value;return;
case 19:p->has_handler=(__typeof__(p->has_handler))value;return;
case 20:p->dupdetected=(__typeof__(p->dupdetected))value;return;
case 21:p->disregarded=(__typeof__(p->disregarded))value;return;
default:abort();}}
case 8:{union any*p=at;switch(field){
case 0:p->a_void=(__typeof__(p->a_void))value;return;
case 1:p->a_int=(__typeof__(p->a_int))value;return;
case 2:p->a_char=(__typeof__(p->a_char))value;return;
default:abort();}}
case 9:{struct autopickup_exception*p=at;switch(field){
case 0:p->regex=(__typeof__(p->regex))value;return;
case 1:p->pattern=(__typeof__(p->pattern))value;return;
case 2:p->grab=(__typeof__(p->grab))value;return;
case 3:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 10:{struct class_sym*p=at;switch(field){
case 0:p->sym=(__typeof__(p->sym))value;return;
default:abort();}}
case 11:{struct cmd*p=at;switch(field){
case 0:p->num_pad=(__typeof__(p->num_pad))value;return;
case 1:p->pcHack_compat=(__typeof__(p->pcHack_compat))value;return;
case 2:p->phone_layout=(__typeof__(p->phone_layout))value;return;
case 3:p->swap_yz=(__typeof__(p->swap_yz))value;return;
default:abort();}}
case 12:{struct color_and_attr*p=at;switch(field){
case 0:p->color=(__typeof__(p->color))value;return;
case 1:p->attr=(__typeof__(p->attr))value;return;
default:abort();}}
case 13:{struct condtests_t*p=at;switch(field){
case 0:p->enabled=(__typeof__(p->enabled))value;return;
default:abort();}}
case 14:{struct const_globals*p=at;switch(field){
default:abort();}}
case 15:{struct context_info*p=at;switch(field){
case 0:p->current_fruit=(__typeof__(p->current_fruit))value;return;
default:abort();}}
case 16:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 17:{struct dgn_topology*p=at;switch(field){
default:abort();}}
case 18:{struct display_hints*p=at;switch(field){
case 0:p->botl=(__typeof__(p->botl))value;return;
case 1:p->botlx=(__typeof__(p->botlx))value;return;
default:abort();}}
case 19:{struct flag*p=at;switch(field){
case 0:p->acoustics=(__typeof__(p->acoustics))value;return;
case 1:p->armorstatus=(__typeof__(p->armorstatus))value;return;
case 2:p->autodig=(__typeof__(p->autodig))value;return;
case 3:p->autoquiver=(__typeof__(p->autoquiver))value;return;
case 4:p->autoopen=(__typeof__(p->autoopen))value;return;
case 5:p->biff=(__typeof__(p->biff))value;return;
case 6:p->bones=(__typeof__(p->bones))value;return;
case 7:p->confirm=(__typeof__(p->confirm))value;return;
case 8:p->dark_room=(__typeof__(p->dark_room))value;return;
case 9:p->debug=(__typeof__(p->debug))value;return;
case 10:p->end_own=(__typeof__(p->end_own))value;return;
case 11:p->explore=(__typeof__(p->explore))value;return;
case 12:p->female=(__typeof__(p->female))value;return;
case 13:p->goldX=(__typeof__(p->goldX))value;return;
case 14:p->help=(__typeof__(p->help))value;return;
case 15:p->tips=(__typeof__(p->tips))value;return;
case 16:p->tutorial=(__typeof__(p->tutorial))value;return;
case 17:p->ignintr=(__typeof__(p->ignintr))value;return;
case 18:p->implicit_uncursed=(__typeof__(p->implicit_uncursed))value;return;
case 19:p->ins_chkpt=(__typeof__(p->ins_chkpt))value;return;
case 20:p->invlet_constant=(__typeof__(p->invlet_constant))value;return;
case 21:p->legacy=(__typeof__(p->legacy))value;return;
case 22:p->lit_corridor=(__typeof__(p->lit_corridor))value;return;
case 23:p->mention_decor=(__typeof__(p->mention_decor))value;return;
case 24:p->mention_walls=(__typeof__(p->mention_walls))value;return;
case 25:p->nopick_dropped=(__typeof__(p->nopick_dropped))value;return;
case 26:p->null=(__typeof__(p->null))value;return;
case 27:p->pickup=(__typeof__(p->pickup))value;return;
case 28:p->pickup_stolen=(__typeof__(p->pickup_stolen))value;return;
case 29:p->pickup_thrown=(__typeof__(p->pickup_thrown))value;return;
case 30:p->pushweapon=(__typeof__(p->pushweapon))value;return;
case 31:p->quick_farsight=(__typeof__(p->quick_farsight))value;return;
case 32:p->rest_on_space=(__typeof__(p->rest_on_space))value;return;
case 33:p->safe_dog=(__typeof__(p->safe_dog))value;return;
case 34:p->safe_wait=(__typeof__(p->safe_wait))value;return;
case 35:p->showexp=(__typeof__(p->showexp))value;return;
case 36:p->showvers=(__typeof__(p->showvers))value;return;
case 37:p->silent=(__typeof__(p->silent))value;return;
case 38:p->sortpack=(__typeof__(p->sortpack))value;return;
case 39:p->sparkle=(__typeof__(p->sparkle))value;return;
case 40:p->standout=(__typeof__(p->standout))value;return;
case 41:p->terrainstatus=(__typeof__(p->terrainstatus))value;return;
case 42:p->time=(__typeof__(p->time))value;return;
case 43:p->tombstone=(__typeof__(p->tombstone))value;return;
case 44:p->verbose=(__typeof__(p->verbose))value;return;
case 45:p->weaponstatus=(__typeof__(p->weaponstatus))value;return;
case 46:p->end_top=(__typeof__(p->end_top))value;return;
case 47:p->end_around=(__typeof__(p->end_around))value;return;
case 48:p->autounlock=(__typeof__(p->autounlock))value;return;
case 49:p->suppress_alert=(__typeof__(p->suppress_alert))value;return;
case 50:p->paranoia_bits=(__typeof__(p->paranoia_bits))value;return;
case 51:p->versinfo=(__typeof__(p->versinfo))value;return;
case 52:p->pickup_burden=(__typeof__(p->pickup_burden))value;return;
case 53:p->pile_limit=(__typeof__(p->pile_limit))value;return;
case 54:p->discosort=(__typeof__(p->discosort))value;return;
case 55:p->sortloot=(__typeof__(p->sortloot))value;return;
case 56:p->vanq_sortmode=(__typeof__(p->vanq_sortmode))value;return;
case 60:p->menu_style=(__typeof__(p->menu_style))value;return;
case 61:p->made_fruit=(__typeof__(p->made_fruit))value;return;
case 62:p->initrole=(__typeof__(p->initrole))value;return;
case 63:p->initrace=(__typeof__(p->initrace))value;return;
case 64:p->initgend=(__typeof__(p->initgend))value;return;
case 65:p->initalign=(__typeof__(p->initalign))value;return;
case 66:p->lootabc=(__typeof__(p->lootabc))value;return;
case 67:p->showrace=(__typeof__(p->showrace))value;return;
case 68:p->travelcmd=(__typeof__(p->travelcmd))value;return;
case 69:p->runmode=(__typeof__(p->runmode))value;return;
default:abort();}}
case 20:{struct fruit*p=at;switch(field){
case 1:p->fid=(__typeof__(p->fid))value;return;
case 2:p->nextf=(__typeof__(p->nextf))value;return;
default:abort();}}
case 21:{struct instance_flags*p=at;switch(field){
case 0:p->herecmd_menu=(__typeof__(p->herecmd_menu))value;return;
case 1:p->idlecheckpoint=(__typeof__(p->idlecheckpoint))value;return;
case 2:p->query_menu=(__typeof__(p->query_menu))value;return;
case 3:p->showdamage=(__typeof__(p->showdamage))value;return;
case 4:p->debug_fuzzer=(__typeof__(p->debug_fuzzer))value;return;
case 5:p->getloc_filter=(__typeof__(p->getloc_filter))value;return;
case 6:p->menuobjsyms=(__typeof__(p->menuobjsyms))value;return;
case 7:p->bgcolors=(__typeof__(p->bgcolors))value;return;
case 8:p->getloc_moveskip=(__typeof__(p->getloc_moveskip))value;return;
case 9:p->getloc_usemenu=(__typeof__(p->getloc_usemenu))value;return;
case 10:p->trav_debug=(__typeof__(p->trav_debug))value;return;
case 11:p->window_inited=(__typeof__(p->window_inited))value;return;
case 12:p->sanity_check=(__typeof__(p->sanity_check))value;return;
case 13:p->debug_overwrite_stairs=(__typeof__(p->debug_overwrite_stairs))value;return;
case 14:p->debug_mongen=(__typeof__(p->debug_mongen))value;return;
case 15:p->debug_hunger=(__typeof__(p->debug_hunger))value;return;
case 16:p->mon_polycontrol=(__typeof__(p->mon_polycontrol))value;return;
case 17:p->mon_telecontrol=(__typeof__(p->mon_telecontrol))value;return;
case 18:p->initoptions_noterminate=(__typeof__(p->initoptions_noterminate))value;return;
case 19:p->msg_history=(__typeof__(p->msg_history))value;return;
case 20:p->getpos_coords=(__typeof__(p->getpos_coords))value;return;
case 21:p->menuinvertmode=(__typeof__(p->menuinvertmode))value;return;
case 23:p->use_truecolor=(__typeof__(p->use_truecolor))value;return;
case 24:p->altmeta=(__typeof__(p->altmeta))value;return;
case 25:p->autodescribe=(__typeof__(p->autodescribe))value;return;
case 26:p->deferred_X=(__typeof__(p->deferred_X))value;return;
case 27:p->force_invmenu=(__typeof__(p->force_invmenu))value;return;
case 28:p->hilite_pile=(__typeof__(p->hilite_pile))value;return;
case 29:p->menu_head_objsym=(__typeof__(p->menu_head_objsym))value;return;
case 30:p->menu_overlay=(__typeof__(p->menu_overlay))value;return;
case 31:p->menu_requested=(__typeof__(p->menu_requested))value;return;
case 32:p->menu_tab_sep=(__typeof__(p->menu_tab_sep))value;return;
case 33:p->news=(__typeof__(p->news))value;return;
case 34:p->num_pad=(__typeof__(p->num_pad))value;return;
case 35:p->perm_invent=(__typeof__(p->perm_invent))value;return;
case 36:p->pricequotes=(__typeof__(p->pricequotes))value;return;
case 37:p->sounds=(__typeof__(p->sounds))value;return;
case 38:p->status_updates=(__typeof__(p->status_updates))value;return;
case 39:p->toptenwin=(__typeof__(p->toptenwin))value;return;
case 40:p->use_menu_color=(__typeof__(p->use_menu_color))value;return;
case 41:p->use_menu_glyphs=(__typeof__(p->use_menu_glyphs))value;return;
case 42:p->hilite_delta=(__typeof__(p->hilite_delta))value;return;
case 43:p->voices=(__typeof__(p->voices))value;return;
case 44:p->prev_decor=(__typeof__(p->prev_decor))value;return;
case 45:p->num_pad_mode=(__typeof__(p->num_pad_mode))value;return;
case 46:p->perminv_mode=(__typeof__(p->perminv_mode))value;return;
case 47:p->prevmsg_window=(__typeof__(p->prevmsg_window))value;return;
case 48:p->extmenu=(__typeof__(p->extmenu))value;return;
case 49:p->cmdassist=(__typeof__(p->cmdassist))value;return;
case 50:p->fireassist=(__typeof__(p->fireassist))value;return;
case 51:p->wizweight=(__typeof__(p->wizweight))value;return;
case 52:p->wizmgender=(__typeof__(p->wizmgender))value;return;
case 53:p->customcolors=(__typeof__(p->customcolors))value;return;
case 54:p->customsymbols=(__typeof__(p->customsymbols))value;return;
case 55:p->wc_color=(__typeof__(p->wc_color))value;return;
case 56:p->wc_hilite_pet=(__typeof__(p->wc_hilite_pet))value;return;
case 57:p->wc_ascii_map=(__typeof__(p->wc_ascii_map))value;return;
case 58:p->wc_tiled_map=(__typeof__(p->wc_tiled_map))value;return;
case 59:p->wc_preload_tiles=(__typeof__(p->wc_preload_tiles))value;return;
case 60:p->wc_tile_width=(__typeof__(p->wc_tile_width))value;return;
case 61:p->wc_tile_height=(__typeof__(p->wc_tile_height))value;return;
case 62:p->wc_tile_file=(__typeof__(p->wc_tile_file))value;return;
case 63:p->wc_inverse=(__typeof__(p->wc_inverse))value;return;
case 64:p->wc_align_status=(__typeof__(p->wc_align_status))value;return;
case 65:p->wc_align_message=(__typeof__(p->wc_align_message))value;return;
case 66:p->wc_vary_msgcount=(__typeof__(p->wc_vary_msgcount))value;return;
case 68:p->wc_font_map=(__typeof__(p->wc_font_map))value;return;
case 69:p->wc_font_message=(__typeof__(p->wc_font_message))value;return;
case 70:p->wc_font_status=(__typeof__(p->wc_font_status))value;return;
case 71:p->wc_font_menu=(__typeof__(p->wc_font_menu))value;return;
case 72:p->wc_font_text=(__typeof__(p->wc_font_text))value;return;
case 73:p->wc_fontsiz_map=(__typeof__(p->wc_fontsiz_map))value;return;
case 74:p->wc_fontsiz_message=(__typeof__(p->wc_fontsiz_message))value;return;
case 75:p->wc_fontsiz_status=(__typeof__(p->wc_fontsiz_status))value;return;
case 76:p->wc_fontsiz_menu=(__typeof__(p->wc_fontsiz_menu))value;return;
case 77:p->wc_fontsiz_text=(__typeof__(p->wc_fontsiz_text))value;return;
case 78:p->wc_scroll_amount=(__typeof__(p->wc_scroll_amount))value;return;
case 79:p->wc_scroll_margin=(__typeof__(p->wc_scroll_margin))value;return;
case 80:p->wc_map_mode=(__typeof__(p->wc_map_mode))value;return;
case 81:p->wc_player_selection=(__typeof__(p->wc_player_selection))value;return;
case 82:p->wc_splash_screen=(__typeof__(p->wc_splash_screen))value;return;
case 83:p->wc_popup_dialog=(__typeof__(p->wc_popup_dialog))value;return;
case 84:p->wc_eight_bit_input=(__typeof__(p->wc_eight_bit_input))value;return;
case 85:p->wc2_fullscreen=(__typeof__(p->wc2_fullscreen))value;return;
case 86:p->wc2_softkeyboard=(__typeof__(p->wc2_softkeyboard))value;return;
case 87:p->wc2_wraptext=(__typeof__(p->wc2_wraptext))value;return;
case 88:p->wc2_selectsaved=(__typeof__(p->wc2_selectsaved))value;return;
case 89:p->wc2_darkgray=(__typeof__(p->wc2_darkgray))value;return;
case 90:p->wc2_hitpointbar=(__typeof__(p->wc2_hitpointbar))value;return;
case 91:p->wc2_guicolor=(__typeof__(p->wc2_guicolor))value;return;
case 92:p->wc_mouse_support=(__typeof__(p->wc_mouse_support))value;return;
case 93:p->wc2_term_cols=(__typeof__(p->wc2_term_cols))value;return;
case 94:p->wc2_term_rows=(__typeof__(p->wc2_term_rows))value;return;
case 95:p->wc2_statuslines=(__typeof__(p->wc2_statuslines))value;return;
case 96:p->wc2_windowborders=(__typeof__(p->wc2_windowborders))value;return;
case 97:p->wc2_petattr=(__typeof__(p->wc2_petattr))value;return;
case 98:p->windowtype_locked=(__typeof__(p->windowtype_locked))value;return;
case 99:p->windowtype_deferred=(__typeof__(p->windowtype_deferred))value;return;
default:abort();}}
case 22:{struct instance_globals_a*p=at;switch(field){
case 0:p->apelist=(__typeof__(p->apelist))value;return;
default:abort();}}
case 23:{struct instance_globals_c*p=at;switch(field){
case 3:p->crash_email=(__typeof__(p->crash_email))value;return;
case 4:p->crash_name=(__typeof__(p->crash_name))value;return;
case 5:p->crash_urlmax=(__typeof__(p->crash_urlmax))value;return;
case 6:p->currentgraphics=(__typeof__(p->currentgraphics))value;return;
case 7:p->cmdline_windowsys=(__typeof__(p->cmdline_windowsys))value;return;
case 8:p->chosen_soundlib=(__typeof__(p->chosen_soundlib))value;return;
default:abort();}}
case 24:{struct instance_globals_d*p=at;switch(field){
case 1:p->deferred_showpaths=(__typeof__(p->deferred_showpaths))value;return;
default:abort();}}
case 25:{struct instance_globals_f*p=at;switch(field){
case 0:p->ffruit=(__typeof__(p->ffruit))value;return;
default:abort();}}
case 26:{struct instance_globals_h*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_m*p=at;switch(field){
case 0:p->menu_colorings=(__typeof__(p->menu_colorings))value;return;
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:p->n_menu_mapped=(__typeof__(p->n_menu_mapped))value;return;
default:abort();}}
case 29:{struct instance_globals_o*p=at;switch(field){
case 2:p->opt_phase=(__typeof__(p->opt_phase))value;return;
case 3:p->opt_initial=(__typeof__(p->opt_initial))value;return;
case 4:p->opt_from_file=(__typeof__(p->opt_from_file))value;return;
case 5:p->opt_need_redraw=(__typeof__(p->opt_need_redraw))value;return;
case 6:p->opt_need_glyph_reset=(__typeof__(p->opt_need_glyph_reset))value;return;
case 7:p->opt_need_promptstyle=(__typeof__(p->opt_need_promptstyle))value;return;
case 8:p->opt_reset_customcolors=(__typeof__(p->opt_reset_customcolors))value;return;
case 9:p->opt_reset_customsymbols=(__typeof__(p->opt_reset_customsymbols))value;return;
case 10:p->opt_update_basic_palette=(__typeof__(p->opt_update_basic_palette))value;return;
case 11:p->opt_symset_changed=(__typeof__(p->opt_symset_changed))value;return;
default:abort();}}
case 30:{struct instance_globals_p*p=at;switch(field){
case 0:p->plnamelen=(__typeof__(p->plnamelen))value;return;
case 1:p->pl_race=(__typeof__(p->pl_race))value;return;
case 2:p->plinemsg_types=(__typeof__(p->plinemsg_types))value;return;
case 3:p->preferred_pet=(__typeof__(p->preferred_pet))value;return;
default:abort();}}
case 31:{struct instance_globals_s*p=at;switch(field){
case 2:p->simple_options_help=(__typeof__(p->simple_options_help))value;return;
default:abort();}}
case 32:{struct instance_globals_saved_b*p=at;switch(field){
default:abort();}}
case 33:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 34:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 35:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 36:{struct instance_globals_t*p=at;switch(field){
default:abort();}}
case 37:{struct instance_globals_v*p=at;switch(field){
case 0:p->vision_full_recalc=(__typeof__(p->vision_full_recalc))value;return;
default:abort();}}
case 38:{struct instance_globals_w*p=at;switch(field){
default:abort();}}
case 39:{struct teleport_options_menu_cmd_t*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->cmd=(__typeof__(p->cmd))value;return;
case 2:p->desc=(__typeof__(p->desc))value;return;
default:abort();}}
case 40:{struct menucoloring*p=at;switch(field){
case 0:p->origstr=(__typeof__(p->origstr))value;return;
case 1:p->color=(__typeof__(p->color))value;return;
case 2:p->attr=(__typeof__(p->attr))value;return;
case 3:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 41:{struct teleport_options_menuscrollinfo*p=at;switch(field){
case 0:p->cmdkey=(__typeof__(p->cmdkey))value;return;
case 1:p->maskindx=(__typeof__(p->maskindx))value;return;
default:abort();}}
case 42:{struct mi*p=at;switch(field){
default:abort();}}
case 43:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 44:{struct nomakedefs_s*p=at;switch(field){
case 0:p->git_branch=(__typeof__(p->git_branch))value;return;
default:abort();}}
case 45:{struct objclass*p=at;switch(field){
case 0:p->oc_name_idx=(__typeof__(p->oc_name_idx))value;return;
case 1:p->oc_class=(__typeof__(p->oc_class))value;return;
default:abort();}}
case 46:{struct objdescr*p=at;switch(field){
case 0:p->oc_name=(__typeof__(p->oc_name))value;return;
default:abort();}}
case 47:{struct teleport_options_objsymopt*p=at;switch(field){
case 0:p->num=(__typeof__(p->num))value;return;
case 1:p->nam=(__typeof__(p->nam))value;return;
case 2:p->descr=(__typeof__(p->descr))value;return;
default:abort();}}
case 48:{struct teleport_options_options_msgtype_name*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->msgtyp=(__typeof__(p->msgtyp))value;return;
case 2:p->descr=(__typeof__(p->descr))value;return;
default:abort();}}
case 49:{struct teleport_options_paranoia_opts*p=at;switch(field){
case 0:p->flagmask=(__typeof__(p->flagmask))value;return;
case 1:p->argname=(__typeof__(p->argname))value;return;
case 2:p->argMinLen=(__typeof__(p->argMinLen))value;return;
case 3:p->synonym=(__typeof__(p->synonym))value;return;
case 4:p->synMinLen=(__typeof__(p->synMinLen))value;return;
case 5:p->explain=(__typeof__(p->explain))value;return;
default:abort();}}
case 50:{struct plinemsg_type*p=at;switch(field){
case 0:p->msgtype=(__typeof__(p->msgtype))value;return;
case 1:p->regex=(__typeof__(p->regex))value;return;
case 2:p->pattern=(__typeof__(p->pattern))value;return;
case 3:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 51:{struct sinfo*p=at;switch(field){
case 0:p->in_parseoptions=(__typeof__(p->in_parseoptions))value;return;
default:abort();}}
case 52:{struct symdef*p=at;switch(field){
case 0:p->sym=(__typeof__(p->sym))value;return;
default:abort();}}
case 53:{struct symsetentry*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->handling=(__typeof__(p->handling))value;return;
case 2:p->explicitly=(unsigned int)value;return;
default:abort();}}
case 54:{struct tc_gbl_data*p=at;switch(field){
case 0:p->tc_AS=(__typeof__(p->tc_AS))value;return;
case 1:p->tc_AE=(__typeof__(p->tc_AE))value;return;
default:abort();}}
case 55:{struct u_roleplay*p=at;switch(field){
case 0:p->blind=(__typeof__(p->blind))value;return;
case 1:p->nudist=(__typeof__(p->nudist))value;return;
case 2:p->deaf=(__typeof__(p->deaf))value;return;
case 3:p->pauper=(__typeof__(p->pauper))value;return;
case 4:p->reroll=(__typeof__(p->reroll))value;return;
default:abort();}}
case 56:{struct wc_Opt*p=at;switch(field){
case 0:p->wc_name=(__typeof__(p->wc_name))value;return;
case 1:p->wc_bit=(__typeof__(p->wc_bit))value;return;
default:abort();}}
case 57:{struct window_procs*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->wp_id=(__typeof__(p->wp_id))value;return;
case 2:p->wincap=(__typeof__(p->wincap))value;return;
case 3:p->wincap2=(__typeof__(p->wincap2))value;return;
case 4:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))value;return;
case 5:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 6:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))value;return;
case 7:p->win_putstr=(__typeof__(p->win_putstr))value;return;
case 8:p->win_display_file=(__typeof__(p->win_display_file))value;return;
case 9:p->win_start_menu=(__typeof__(p->win_start_menu))value;return;
case 10:p->win_end_menu=(__typeof__(p->win_end_menu))value;return;
case 11:p->win_wait_synch=(__typeof__(p->win_wait_synch))value;return;
case 12:p->win_number_pad=(__typeof__(p->win_number_pad))value;return;
case 13:p->win_preference_update=(__typeof__(p->win_preference_update))value;return;
default:abort();}}
case 58:{struct windowcolors_struct*p=at;switch(field){
case 0:p->fg=(__typeof__(p->fg))value;return;
case 1:p->bg=(__typeof__(p->bg))value;return;
default:abort();}}
case 59:{struct teleport_options_xtra_cntrls*p=at;switch(field){
case 0:p->key=(__typeof__(p->key))value;return;
case 1:p->desc=(__typeof__(p->desc))value;return;
default:abort();}}
case 60:{struct you*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_options_address(int kind,void*at,int field){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:return(void*)&p->adj;
default:abort();}}
case 1:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->adj;
default:abort();}}
case 2:{struct Race*p=at;switch(field){
case 0:return(void*)&p->noun;
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:return(void*)&p->name;
default:abort();}}
case 4:{struct RoleName*p=at;switch(field){
case 0:return(void*)&p->m;
default:abort();}}
case 5:{struct accessibility_data*p=at;switch(field){
case 0:return(void*)&p->accessiblemsg;
case 1:return(void*)&p->msg_loc;
case 2:return(void*)&p->mon_notices;
case 3:return(void*)&p->mon_movement;
case 4:return(void*)&p->glyph_updates;
default:abort();}}
case 6:{struct teleport_options_action*p=at;switch(field){
case 0:return(void*)&p->letr;
case 1:return(void*)&p->desc;
default:abort();}}
case 7:{struct allopt_t*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->section;
case 2:return(void*)&p->minmatch;
case 3:return(void*)&p->expectedbuf;
case 4:return(void*)&p->idx;
case 5:return(void*)&p->setwhere;
case 6:return(void*)&p->opttyp;
case 7:return(void*)&p->negateok;
case 8:return(void*)&p->valok;
case 9:return(void*)&p->dupeok;
case 10:return(void*)&p->pfx;
case 11:return(void*)&p->termpref;
case 12:return(void*)&p->opt_in_out;
case 13:return(void*)&p->addr;
case 14:return(void*)&p->optfn;
case 15:return(void*)&p->alias;
case 16:return(void*)&p->descr;
case 17:return(void*)&p->prefixgw;
case 18:return(void*)&p->initval;
case 19:return(void*)&p->has_handler;
case 20:return(void*)&p->dupdetected;
case 21:return(void*)&p->disregarded;
default:abort();}}
case 8:{union any*p=at;switch(field){
case 0:return(void*)&p->a_void;
case 1:return(void*)&p->a_int;
case 2:return(void*)&p->a_char;
default:abort();}}
case 9:{struct autopickup_exception*p=at;switch(field){
case 0:return(void*)&p->regex;
case 1:return(void*)&p->pattern;
case 2:return(void*)&p->grab;
case 3:return(void*)&p->next;
default:abort();}}
case 10:{struct class_sym*p=at;switch(field){
case 0:return(void*)&p->sym;
default:abort();}}
case 11:{struct cmd*p=at;switch(field){
case 0:return(void*)&p->num_pad;
case 1:return(void*)&p->pcHack_compat;
case 2:return(void*)&p->phone_layout;
case 3:return(void*)&p->swap_yz;
default:abort();}}
case 12:{struct color_and_attr*p=at;switch(field){
case 0:return(void*)&p->color;
case 1:return(void*)&p->attr;
default:abort();}}
case 13:{struct condtests_t*p=at;switch(field){
case 0:return(void*)&p->enabled;
default:abort();}}
case 14:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroany;
default:abort();}}
case 15:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->current_fruit;
default:abort();}}
case 16:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 17:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_rogue_level;
default:abort();}}
case 18:{struct display_hints*p=at;switch(field){
case 0:return(void*)&p->botl;
case 1:return(void*)&p->botlx;
default:abort();}}
case 19:{struct flag*p=at;switch(field){
case 0:return(void*)&p->acoustics;
case 1:return(void*)&p->armorstatus;
case 2:return(void*)&p->autodig;
case 3:return(void*)&p->autoquiver;
case 4:return(void*)&p->autoopen;
case 5:return(void*)&p->biff;
case 6:return(void*)&p->bones;
case 7:return(void*)&p->confirm;
case 8:return(void*)&p->dark_room;
case 9:return(void*)&p->debug;
case 10:return(void*)&p->end_own;
case 11:return(void*)&p->explore;
case 12:return(void*)&p->female;
case 13:return(void*)&p->goldX;
case 14:return(void*)&p->help;
case 15:return(void*)&p->tips;
case 16:return(void*)&p->tutorial;
case 17:return(void*)&p->ignintr;
case 18:return(void*)&p->implicit_uncursed;
case 19:return(void*)&p->ins_chkpt;
case 20:return(void*)&p->invlet_constant;
case 21:return(void*)&p->legacy;
case 22:return(void*)&p->lit_corridor;
case 23:return(void*)&p->mention_decor;
case 24:return(void*)&p->mention_walls;
case 25:return(void*)&p->nopick_dropped;
case 26:return(void*)&p->null;
case 27:return(void*)&p->pickup;
case 28:return(void*)&p->pickup_stolen;
case 29:return(void*)&p->pickup_thrown;
case 30:return(void*)&p->pushweapon;
case 31:return(void*)&p->quick_farsight;
case 32:return(void*)&p->rest_on_space;
case 33:return(void*)&p->safe_dog;
case 34:return(void*)&p->safe_wait;
case 35:return(void*)&p->showexp;
case 36:return(void*)&p->showvers;
case 37:return(void*)&p->silent;
case 38:return(void*)&p->sortpack;
case 39:return(void*)&p->sparkle;
case 40:return(void*)&p->standout;
case 41:return(void*)&p->terrainstatus;
case 42:return(void*)&p->time;
case 43:return(void*)&p->tombstone;
case 44:return(void*)&p->verbose;
case 45:return(void*)&p->weaponstatus;
case 46:return(void*)&p->end_top;
case 47:return(void*)&p->end_around;
case 48:return(void*)&p->autounlock;
case 49:return(void*)&p->suppress_alert;
case 50:return(void*)&p->paranoia_bits;
case 51:return(void*)&p->versinfo;
case 52:return(void*)&p->pickup_burden;
case 53:return(void*)&p->pile_limit;
case 54:return(void*)&p->discosort;
case 55:return(void*)&p->sortloot;
case 56:return(void*)&p->vanq_sortmode;
case 57:return(void*)&p->inv_order;
case 58:return(void*)&p->pickup_types;
case 59:return(void*)&p->end_disclose;
case 60:return(void*)&p->menu_style;
case 61:return(void*)&p->made_fruit;
case 62:return(void*)&p->initrole;
case 63:return(void*)&p->initrace;
case 64:return(void*)&p->initgend;
case 65:return(void*)&p->initalign;
case 66:return(void*)&p->lootabc;
case 67:return(void*)&p->showrace;
case 68:return(void*)&p->travelcmd;
case 69:return(void*)&p->runmode;
default:abort();}}
case 20:{struct fruit*p=at;switch(field){
case 0:return(void*)&p->fname;
case 1:return(void*)&p->fid;
case 2:return(void*)&p->nextf;
default:abort();}}
case 21:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->herecmd_menu;
case 1:return(void*)&p->idlecheckpoint;
case 2:return(void*)&p->query_menu;
case 3:return(void*)&p->showdamage;
case 4:return(void*)&p->debug_fuzzer;
case 5:return(void*)&p->getloc_filter;
case 6:return(void*)&p->menuobjsyms;
case 7:return(void*)&p->bgcolors;
case 8:return(void*)&p->getloc_moveskip;
case 9:return(void*)&p->getloc_usemenu;
case 10:return(void*)&p->trav_debug;
case 11:return(void*)&p->window_inited;
case 12:return(void*)&p->sanity_check;
case 13:return(void*)&p->debug_overwrite_stairs;
case 14:return(void*)&p->debug_mongen;
case 15:return(void*)&p->debug_hunger;
case 16:return(void*)&p->mon_polycontrol;
case 17:return(void*)&p->mon_telecontrol;
case 18:return(void*)&p->initoptions_noterminate;
case 19:return(void*)&p->msg_history;
case 20:return(void*)&p->getpos_coords;
case 21:return(void*)&p->menuinvertmode;
case 22:return(void*)&p->menu_headings;
case 23:return(void*)&p->use_truecolor;
case 24:return(void*)&p->altmeta;
case 25:return(void*)&p->autodescribe;
case 26:return(void*)&p->deferred_X;
case 27:return(void*)&p->force_invmenu;
case 28:return(void*)&p->hilite_pile;
case 29:return(void*)&p->menu_head_objsym;
case 30:return(void*)&p->menu_overlay;
case 31:return(void*)&p->menu_requested;
case 32:return(void*)&p->menu_tab_sep;
case 33:return(void*)&p->news;
case 34:return(void*)&p->num_pad;
case 35:return(void*)&p->perm_invent;
case 36:return(void*)&p->pricequotes;
case 37:return(void*)&p->sounds;
case 38:return(void*)&p->status_updates;
case 39:return(void*)&p->toptenwin;
case 40:return(void*)&p->use_menu_color;
case 41:return(void*)&p->use_menu_glyphs;
case 42:return(void*)&p->hilite_delta;
case 43:return(void*)&p->voices;
case 44:return(void*)&p->prev_decor;
case 45:return(void*)&p->num_pad_mode;
case 46:return(void*)&p->perminv_mode;
case 47:return(void*)&p->prevmsg_window;
case 48:return(void*)&p->extmenu;
case 49:return(void*)&p->cmdassist;
case 50:return(void*)&p->fireassist;
case 51:return(void*)&p->wizweight;
case 52:return(void*)&p->wizmgender;
case 53:return(void*)&p->customcolors;
case 54:return(void*)&p->customsymbols;
case 55:return(void*)&p->wc_color;
case 56:return(void*)&p->wc_hilite_pet;
case 57:return(void*)&p->wc_ascii_map;
case 58:return(void*)&p->wc_tiled_map;
case 59:return(void*)&p->wc_preload_tiles;
case 60:return(void*)&p->wc_tile_width;
case 61:return(void*)&p->wc_tile_height;
case 62:return(void*)&p->wc_tile_file;
case 63:return(void*)&p->wc_inverse;
case 64:return(void*)&p->wc_align_status;
case 65:return(void*)&p->wc_align_message;
case 66:return(void*)&p->wc_vary_msgcount;
case 67:return(void*)&p->wcolors;
case 68:return(void*)&p->wc_font_map;
case 69:return(void*)&p->wc_font_message;
case 70:return(void*)&p->wc_font_status;
case 71:return(void*)&p->wc_font_menu;
case 72:return(void*)&p->wc_font_text;
case 73:return(void*)&p->wc_fontsiz_map;
case 74:return(void*)&p->wc_fontsiz_message;
case 75:return(void*)&p->wc_fontsiz_status;
case 76:return(void*)&p->wc_fontsiz_menu;
case 77:return(void*)&p->wc_fontsiz_text;
case 78:return(void*)&p->wc_scroll_amount;
case 79:return(void*)&p->wc_scroll_margin;
case 80:return(void*)&p->wc_map_mode;
case 81:return(void*)&p->wc_player_selection;
case 82:return(void*)&p->wc_splash_screen;
case 83:return(void*)&p->wc_popup_dialog;
case 84:return(void*)&p->wc_eight_bit_input;
case 85:return(void*)&p->wc2_fullscreen;
case 86:return(void*)&p->wc2_softkeyboard;
case 87:return(void*)&p->wc2_wraptext;
case 88:return(void*)&p->wc2_selectsaved;
case 89:return(void*)&p->wc2_darkgray;
case 90:return(void*)&p->wc2_hitpointbar;
case 91:return(void*)&p->wc2_guicolor;
case 92:return(void*)&p->wc_mouse_support;
case 93:return(void*)&p->wc2_term_cols;
case 94:return(void*)&p->wc2_term_rows;
case 95:return(void*)&p->wc2_statuslines;
case 96:return(void*)&p->wc2_windowborders;
case 97:return(void*)&p->wc2_petattr;
case 98:return(void*)&p->windowtype_locked;
case 99:return(void*)&p->windowtype_deferred;
default:abort();}}
case 22:{struct instance_globals_a*p=at;switch(field){
case 0:return(void*)&p->apelist;
default:abort();}}
case 23:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->Cmd;
case 1:return(void*)&p->chosen_windowtype;
case 2:return(void*)&p->catname;
case 3:return(void*)&p->crash_email;
case 4:return(void*)&p->crash_name;
case 5:return(void*)&p->crash_urlmax;
case 6:return(void*)&p->currentgraphics;
case 7:return(void*)&p->cmdline_windowsys;
case 8:return(void*)&p->chosen_soundlib;
default:abort();}}
case 24:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->dogname;
case 1:return(void*)&p->deferred_showpaths;
default:abort();}}
case 25:{struct instance_globals_f*p=at;switch(field){
case 0:return(void*)&p->ffruit;
default:abort();}}
case 26:{struct instance_globals_h*p=at;switch(field){
case 0:return(void*)&p->horsename;
default:abort();}}
case 27:{struct instance_globals_m*p=at;switch(field){
case 0:return(void*)&p->menu_colorings;
case 1:return(void*)&p->mapped_menu_cmds;
case 2:return(void*)&p->mapped_menu_op;
default:abort();}}
case 28:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->n_menu_mapped;
default:abort();}}
case 29:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->ov_primary_syms;
case 1:return(void*)&p->ov_rogue_syms;
case 2:return(void*)&p->opt_phase;
case 3:return(void*)&p->opt_initial;
case 4:return(void*)&p->opt_from_file;
case 5:return(void*)&p->opt_need_redraw;
case 6:return(void*)&p->opt_need_glyph_reset;
case 7:return(void*)&p->opt_need_promptstyle;
case 8:return(void*)&p->opt_reset_customcolors;
case 9:return(void*)&p->opt_reset_customsymbols;
case 10:return(void*)&p->opt_update_basic_palette;
case 11:return(void*)&p->opt_symset_changed;
default:abort();}}
case 30:{struct instance_globals_p*p=at;switch(field){
case 0:return(void*)&p->plnamelen;
case 1:return(void*)&p->pl_race;
case 2:return(void*)&p->plinemsg_types;
case 3:return(void*)&p->preferred_pet;
default:abort();}}
case 31:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->symset;
case 1:return(void*)&p->showsyms;
case 2:return(void*)&p->simple_options_help;
default:abort();}}
case 32:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(void*)&p->bases;
default:abort();}}
case 33:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 34:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeon_topology;
default:abort();}}
case 35:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(void*)&p->plname;
case 1:return(void*)&p->pl_character;
case 2:return(void*)&p->pl_fruit;
default:abort();}}
case 36:{struct instance_globals_t*p=at;switch(field){
case 0:return(void*)&p->tc_gbl_data;
default:abort();}}
case 37:{struct instance_globals_v*p=at;switch(field){
case 0:return(void*)&p->vision_full_recalc;
default:abort();}}
case 38:{struct instance_globals_w*p=at;switch(field){
case 0:return(void*)&p->warnsyms;
case 1:return(void*)&p->wizkit;
default:abort();}}
case 39:{struct teleport_options_menu_cmd_t*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->cmd;
case 2:return(void*)&p->desc;
default:abort();}}
case 40:{struct menucoloring*p=at;switch(field){
case 0:return(void*)&p->origstr;
case 1:return(void*)&p->color;
case 2:return(void*)&p->attr;
case 3:return(void*)&p->next;
default:abort();}}
case 41:{struct teleport_options_menuscrollinfo*p=at;switch(field){
case 0:return(void*)&p->cmdkey;
case 1:return(void*)&p->maskindx;
default:abort();}}
case 42:{struct mi*p=at;switch(field){
case 0:return(void*)&p->item;
default:abort();}}
case 43:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 44:{struct nomakedefs_s*p=at;switch(field){
case 0:return(void*)&p->git_branch;
default:abort();}}
case 45:{struct objclass*p=at;switch(field){
case 0:return(void*)&p->oc_name_idx;
case 1:return(void*)&p->oc_class;
default:abort();}}
case 46:{struct objdescr*p=at;switch(field){
case 0:return(void*)&p->oc_name;
default:abort();}}
case 47:{struct teleport_options_objsymopt*p=at;switch(field){
case 0:return(void*)&p->num;
case 1:return(void*)&p->nam;
case 2:return(void*)&p->descr;
default:abort();}}
case 48:{struct teleport_options_options_msgtype_name*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->msgtyp;
case 2:return(void*)&p->descr;
default:abort();}}
case 49:{struct teleport_options_paranoia_opts*p=at;switch(field){
case 0:return(void*)&p->flagmask;
case 1:return(void*)&p->argname;
case 2:return(void*)&p->argMinLen;
case 3:return(void*)&p->synonym;
case 4:return(void*)&p->synMinLen;
case 5:return(void*)&p->explain;
default:abort();}}
case 50:{struct plinemsg_type*p=at;switch(field){
case 0:return(void*)&p->msgtype;
case 1:return(void*)&p->regex;
case 2:return(void*)&p->pattern;
case 3:return(void*)&p->next;
default:abort();}}
case 51:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->in_parseoptions;
default:abort();}}
case 52:{struct symdef*p=at;switch(field){
case 0:return(void*)&p->sym;
default:abort();}}
case 53:{struct symsetentry*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->handling;
default:abort();}}
case 54:{struct tc_gbl_data*p=at;switch(field){
case 0:return(void*)&p->tc_AS;
case 1:return(void*)&p->tc_AE;
default:abort();}}
case 55:{struct u_roleplay*p=at;switch(field){
case 0:return(void*)&p->blind;
case 1:return(void*)&p->nudist;
case 2:return(void*)&p->deaf;
case 3:return(void*)&p->pauper;
case 4:return(void*)&p->reroll;
default:abort();}}
case 56:{struct wc_Opt*p=at;switch(field){
case 0:return(void*)&p->wc_name;
case 1:return(void*)&p->wc_bit;
default:abort();}}
case 57:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->wp_id;
case 2:return(void*)&p->wincap;
case 3:return(void*)&p->wincap2;
case 4:return(void*)&p->win_create_nhwindow;
case 5:return(void*)&p->win_display_nhwindow;
case 6:return(void*)&p->win_destroy_nhwindow;
case 7:return(void*)&p->win_putstr;
case 8:return(void*)&p->win_display_file;
case 9:return(void*)&p->win_start_menu;
case 10:return(void*)&p->win_end_menu;
case 11:return(void*)&p->win_wait_synch;
case 12:return(void*)&p->win_number_pad;
case 13:return(void*)&p->win_preference_update;
default:abort();}}
case 58:{struct windowcolors_struct*p=at;switch(field){
case 0:return(void*)&p->fg;
case 1:return(void*)&p->bg;
default:abort();}}
case 59:{struct teleport_options_xtra_cntrls*p=at;switch(field){
case 0:return(void*)&p->key;
case 1:return(void*)&p->desc;
default:abort();}}
case 60:{struct you*p=at;switch(field){
case 0:return(void*)&p->uz;
case 1:return(void*)&p->uroleplay;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_options_var0(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_options_var1(char * a0,int a1){(config_error_add)(a0,a1);}
void teleport_options_var2(char * a0){(config_error_add)(a0);}
void teleport_options_var3(char * a0,char * a1,int a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var4(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_options_var5(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var6(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var7(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
int teleport_options_var8(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var9(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var10(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var11(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var12(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var13(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var14(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var15(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var16(char * a0,char * a1){(config_error_add)(a0,a1);}
int teleport_options_var17(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var18(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var19(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var20(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_options_var21(char * a0){(config_error_add)(a0);}
void teleport_options_var22(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var23(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var24(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var25(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var26(char * a0,int a1){(config_error_add)(a0,a1);}
int teleport_options_var27(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var28(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var29(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_options_var30(char * a0,char * a1,int a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var31(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var32(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var33(char * a0){(config_error_add)(a0);}
void teleport_options_var34(char * a0,char * a1){(pline)(a0,a1);}
int teleport_options_var35(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var36(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var37(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var38(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var39(char * a0){(config_error_add)(a0);}
void teleport_options_var40(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var41(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var42(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var43(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var44(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var45(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var46(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var47(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var48(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var49(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var50(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var51(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var52(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var53(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var54(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var55(char * a0,char * a1,unsigned int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var56(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var57(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var58(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var59(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var60(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var61(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var62(char * a0,char * a1,char * a2,int a3){(config_error_add)(a0,a1,a2,a3);}
int teleport_options_var63(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var64(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var65(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var66(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var67(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_options_var68(char * a0,char * a1,char * a2,char * a3){(config_error_add)(a0,a1,a2,a3);}
void teleport_options_var69(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var70(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var71(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var72(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var73(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var74(char * a0,char * a1){(config_error_add)(a0,a1);}
int teleport_options_var75(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var76(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var77(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var78(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var79(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_options_var80(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var81(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var82(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var83(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var84(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var85(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var86(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var87(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var88(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var89(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var90(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var91(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var92(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var93(char * a0,char * a1){(config_error_add)(a0,a1);}
int teleport_options_var94(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var95(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var96(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var97(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var98(char * a0,char * a1,char * a2,int a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var99(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var100(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var101(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var102(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var103(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var104(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var105(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var106(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var107(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
int teleport_options_var108(char * a0,char * a1,long a2,long a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var109(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var110(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var111(char * a0,char * a1,unsigned long a2,unsigned long a3,unsigned long a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_options_var112(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var113(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var114(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var115(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var116(char * a0,char * a1,long a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var117(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var118(char * a0,char * a1,long a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var119(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var120(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var121(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var122(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var123(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var124(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var125(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var126(char * a0,char * a1,int a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var127(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var128(char * a0,char * a1,char * a2,unsigned int a3){(pline)(a0,a1,a2,a3);}
int teleport_options_var129(char * a0,char * a1,unsigned int a2,char * a3,char * a4,char * a5,char * a6,char * a7,char * a8){return (sprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_options_var130(char * a0,char * a1,unsigned int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var131(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var132(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var133(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var134(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var135(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var136(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var137(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var138(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var139(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_options_var140(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var141(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var142(char * a0,char * a1,int a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var143(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var144(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var145(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var146(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var147(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var148(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var149(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var150(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var151(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var152(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var153(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var154(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var155(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var156(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var157(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var158(char * a0){(pline)(a0);}
void teleport_options_var159(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var160(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
int teleport_options_var161(char * a0,char * a1,char * a2,int a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var162(char * a0,char * a1,char * a2,char * a3,int a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_options_var163(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
int teleport_options_var164(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var165(char * a0,char * a1,char * a2,int a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var166(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var167(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
int teleport_options_var168(char * a0,char * a1,char * a2,int a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var169(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var170(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,int a6,char * a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
int teleport_options_var171(char * a0,char * a1,char * a2,int a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var172(char * a0,char * a1,char * a2,char * a3,int a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_options_var173(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_options_var174(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
int teleport_options_var175(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var176(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var177(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var178(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_options_var179(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
int teleport_options_var180(char * a0,char * a1,int a2,int a3,int a4,int a5,char * a6){return (sprintf)(a0,a1,a2,a3,a4,a5,a6);}
int teleport_options_var181(char * a0,char * a1,int a2,int a3,int a4,int a5,char * a6){return (sprintf)(a0,a1,a2,a3,a4,a5,a6);}
int teleport_options_var182(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var183(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var184(char * a0){(pline)(a0);}
int teleport_options_var185(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var186(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var187(char * a0){(pline)(a0);}
int teleport_options_var188(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var189(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var190(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var191(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var192(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var193(char * a0,char * a1,char * a2,char * a3){(config_error_add)(a0,a1,a2,a3);}
void teleport_options_var194(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_options_var195(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_options_var196(char * a0,int a1){(config_error_add)(a0,a1);}
void teleport_options_var197(char * a0,int a1){(config_error_add)(a0,a1);}
void teleport_options_var198(char * a0,int a1){(config_error_add)(a0,a1);}
void teleport_options_var199(char * a0){(You_cant)(a0);}
void teleport_options_var200(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var201(char * a0,char * a1,unsigned long a2,unsigned long a3,unsigned long a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_options_var202(char * a0,char * a1){(pline)(a0,a1);}
void teleport_options_var203(char * a0,int a1){(config_error_add)(a0,a1);}
void teleport_options_var204(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var205(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var206(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var207(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
int teleport_options_var208(char * a0,char * a1,char * a2,char * a3){return (sscanf)(a0,a1,a2,a3);}
void teleport_options_var209(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var210(char * a0){(config_error_add)(a0);}
void teleport_options_var211(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var212(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var213(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var214(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var215(char * a0){(config_error_add)(a0);}
void teleport_options_var216(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var217(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var218(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var219(char * a0,int a1){(impossible)(a0,a1);}
void teleport_options_var220(char * a0){(pline)(a0);}
int teleport_options_var221(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var222(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var223(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var224(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var225(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var226(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var227(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var228(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var229(char * a0,char * a1,unsigned int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var230(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var231(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var232(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var233(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_options_var234(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var235(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var236(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var237(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var238(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var239(char * a0,char * a1,unsigned int a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var240(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var241(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var242(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var243(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var244(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var245(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var246(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var247(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var248(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var249(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var250(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var251(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var252(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var253(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var254(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var255(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var256(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var257(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var258(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_options_var259(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var260(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_options_var261(char * a0,char * a1){(pline)(a0,a1);}
int teleport_options_var262(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var263(char * a0,char * a1,char * a2,char * a3){return (sscanf)(a0,a1,a2,a3);}
int teleport_options_var264(char * a0,char * a1,char * a2,char * a3){return (sscanf)(a0,a1,a2,a3);}
int teleport_options_var265(char * a0,char * a1,char * a2,char * a3){return (sscanf)(a0,a1,a2,a3);}
void teleport_options_var266(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var267(char * a0,char * a1,char * a2){(config_error_add)(a0,a1,a2);}
void teleport_options_var268(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_options_var269(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var270(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,int a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
int teleport_options_var271(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var272(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var273(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_options_var274(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var275(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_options_var276(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_options_var277(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_options_var278(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
int teleport_options_var279(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_options_var280(char * a0,int a1){(impossible)(a0,a1);}
void teleport_options_var281(char * a0,int a1){(impossible)(a0,a1);}
void teleport_options_var282(char * a0,int a1){(impossible)(a0,a1);}
void teleport_options_var283(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_options_var284(char * a0,char * a1){(config_error_add)(a0,a1);}
winid teleport_options_cb0(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb1(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb2(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb3(void (*fn)(winid),winid a0){fn(a0);}
int teleport_options_cb4(int (*fn)(int, int, boolean, char *, char *),int a0,int a1,boolean a2,char * a3,char * a4){return fn(a0,a1,a2,a3,a4);}
void teleport_options_cb5(void (*fn)(const char *),const char * a0){fn(a0);}
void teleport_options_cb6(void (*fn)(int),int a0){fn(a0);}
winid teleport_options_cb7(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb8(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb9(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb10(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb11(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb12(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb13(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb14(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb15(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb16(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb17(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb18(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb19(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb20(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb21(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb22(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb23(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb24(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb25(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb26(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb27(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb28(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb29(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb30(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb31(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb32(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb33(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb34(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb35(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb36(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb37(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb38(void (*fn)(int),int a0){fn(a0);}
void teleport_options_cb39(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb40(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb41(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb42(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb43(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb44(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb45(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb46(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb47(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb48(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb49(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb50(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb51(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb52(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb53(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb54(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb55(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb56(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb57(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb58(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb59(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb60(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb61(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb62(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb63(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb64(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb65(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb66(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb67(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb68(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb69(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb70(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb71(void (*fn)(winid),winid a0){fn(a0);}
void teleport_options_cb72(void (*fn)(void)){fn();}
winid teleport_options_cb73(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb74(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb75(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb76(void (*fn)(winid),winid a0){fn(a0);}
void teleport_options_cb77(void (*fn)(void)){fn();}
winid teleport_options_cb78(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb79(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb80(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb81(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb82(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb83(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb84(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb85(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb86(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb87(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb88(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb89(void (*fn)(winid),winid a0){fn(a0);}
int teleport_options_cb90(int (*fn)(int, int, boolean, char *, char *),int a0,int a1,boolean a2,char * a3,char * a4){return fn(a0,a1,a2,a3,a4);}
winid teleport_options_cb91(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb92(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb93(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb94(void (*fn)(winid),winid a0){fn(a0);}
void teleport_options_cb95(void (*fn)(const char *),const char * a0){fn(a0);}
int teleport_options_cb96(int (*fn)(int, int, boolean, char *, char *),int a0,int a1,boolean a2,char * a3,char * a4){return fn(a0,a1,a2,a3,a4);}
winid teleport_options_cb97(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb98(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
int teleport_options_cb99(int (*fn)(int, int, boolean, char *, char *),int a0,int a1,boolean a2,char * a3,char * a4){return fn(a0,a1,a2,a3,a4);}
void teleport_options_cb100(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
int teleport_options_cb101(int (*fn)(int, int, boolean, char *, char *),int a0,int a1,boolean a2,char * a3,char * a4){return fn(a0,a1,a2,a3,a4);}
void teleport_options_cb102(void (*fn)(const char *),const char * a0){fn(a0);}
void teleport_options_cb103(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb104(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb105(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb106(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb107(void (*fn)(const char *, boolean),const char * a0,boolean a1){fn(a0,a1);}
int teleport_options_cb108(int (*fn)(int, int, boolean, char *, char *),int a0,int a1,boolean a2,char * a3,char * a4){return fn(a0,a1,a2,a3,a4);}
void teleport_options_cb109(void (*fn)(const char *),const char * a0){fn(a0);}
void teleport_options_cb110(void (*fn)(winid),winid a0){fn(a0);}
int teleport_options_cb111(int (*fn)(int, int, boolean, char *, char *),int a0,int a1,boolean a2,char * a3,char * a4){return fn(a0,a1,a2,a3,a4);}
void teleport_options_cb112(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb113(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb114(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb115(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb116(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb117(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb118(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb119(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb120(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb121(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb122(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb123(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb124(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb125(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb126(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb127(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb128(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb129(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb130(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
winid teleport_options_cb131(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb132(void (*fn)(winid, unsigned long),winid a0,unsigned long a1){fn(a0,a1);}
void teleport_options_cb133(void (*fn)(winid, const char *),winid a0,const char * a1){fn(a0,a1);}
void teleport_options_cb134(void (*fn)(winid),winid a0){fn(a0);}
winid teleport_options_cb135(winid (*fn)(int),int a0){return fn(a0);}
void teleport_options_cb136(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb137(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb138(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb139(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb140(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb141(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb142(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb143(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb144(void (*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
void teleport_options_cb145(void (*fn)(winid),winid a0){fn(a0);}
void teleport_options_cb146(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_options_cb147(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
#pragma clang diagnostic pop
static char options_literals[21694];
char*teleport_options_literal_storage(void){return options_literals;}
size_t teleport_options_literal_capacity(void){return sizeof options_literals;}
static struct allopt_t options_backing_0[218];
static struct allopt_t options_backing_1[218];
static char options_backing_2[1];
static signed char options_backing_3;
static signed char options_backing_4;
static signed char options_backing_5;
static signed char options_backing_6[217];
static char * options_backing_7[4][7];
static char * options_backing_8[5];
static char options_backing_9[18];
static char options_backing_10[7];
static char options_backing_11[7];
static char options_backing_12[13];
static char options_backing_13[8];
static char options_backing_14[4];
static struct teleport_options_paranoia_opts options_backing_15[15];
static char * options_backing_16[4][3];
static char * options_backing_17[4][3];
static char * options_backing_18[4][2];
static char * options_backing_19[6];
static char * options_backing_20[4];
static char * options_backing_21[3];
static char * options_backing_22[9][3];
static struct teleport_options_objsymopt options_backing_23[6];
static struct teleport_options_menu_cmd_t options_backing_24[14];
static char options_backing_25[19];
static int options_backing_26[4];
static char options_backing_27[4];
static char options_backing_28[7];
static char options_backing_29[17];
static char * options_backing_30[3][2];
static char * options_backing_31[6];
static char options_backing_32[9];
static char options_backing_33[6];
static char * options_backing_34[4];
static char * options_backing_35[4];
static char * options_backing_36[6];
static char * options_backing_37[6];
static char * options_backing_38[5];
static char options_backing_39[9];
static char options_backing_40[11];
static signed char options_backing_41;
static char * options_backing_42[2];
static struct teleport_options_options_msgtype_name options_backing_43[6];
static char * options_backing_44;
static char options_backing_45[14];
static char options_backing_46[2];
static struct teleport_options_menuscrollinfo options_backing_47[6];
static char options_backing_48[256];
static char options_backing_49[8];
static char * options_backing_50[2][4];
static char options_backing_51[10];
static char * options_backing_52[5];
static struct teleport_options_xtra_cntrls options_backing_53[6];
static char options_backing_54[16];
static char options_backing_55[13];
static struct teleport_options_action options_backing_56[4];
static char options_backing_57[36];
static char options_backing_58[37];
static char * options_backing_59[10];
static char * options_backing_60[10];
static char * options_backing_61;
static struct wc_Opt options_backing_62[34];
static struct wc_Opt options_backing_63[19];
static char ** options_backing_64[4];
static char ** options_backing_65[4];
void*teleport_options_storage(int i){switch(i){
case 0:return &options_backing_0;
case 1:return &options_backing_1;
case 2:return &options_backing_2;
case 3:return &options_backing_3;
case 4:return &options_backing_4;
case 5:return &options_backing_5;
case 6:return &options_backing_6;
case 7:return &options_backing_7;
case 8:return &options_backing_8;
case 9:return &options_backing_9;
case 10:return &options_backing_10;
case 11:return &options_backing_11;
case 12:return &options_backing_12;
case 13:return &options_backing_13;
case 14:return &options_backing_14;
case 15:return &options_backing_15;
case 16:return &options_backing_16;
case 17:return &options_backing_17;
case 18:return &options_backing_18;
case 19:return &options_backing_19;
case 20:return &options_backing_20;
case 21:return &options_backing_21;
case 22:return &options_backing_22;
case 23:return &options_backing_23;
case 24:return &options_backing_24;
case 25:return &options_backing_25;
case 26:return &options_backing_26;
case 27:return &options_backing_27;
case 28:return &options_backing_28;
case 29:return &options_backing_29;
case 30:return &options_backing_30;
case 31:return &options_backing_31;
case 32:return &options_backing_32;
case 33:return &options_backing_33;
case 34:return &options_backing_34;
case 35:return &options_backing_35;
case 36:return &options_backing_36;
case 37:return &options_backing_37;
case 38:return &options_backing_38;
case 39:return &options_backing_39;
case 40:return &options_backing_40;
case 41:return &options_backing_41;
case 42:return &options_backing_42;
case 43:return &options_backing_43;
case 44:return &options_backing_44;
case 45:return &options_backing_45;
case 46:return &options_backing_46;
case 47:return &options_backing_47;
case 48:return &options_backing_48;
case 49:return &options_backing_49;
case 50:return &options_backing_50;
case 51:return &options_backing_51;
case 52:return &options_backing_52;
case 53:return &options_backing_53;
case 54:return &options_backing_54;
case 55:return &options_backing_55;
case 56:return &options_backing_56;
case 57:return &options_backing_57;
case 58:return &options_backing_58;
case 59:return &options_backing_59;
case 60:return &options_backing_60;
case 61:return &options_backing_61;
case 62:return &options_backing_62;
case 63:return &options_backing_63;
case 64:return &options_backing_64;
case 65:return &options_backing_65;
default:abort();}}
extern int teleport_options_callback_optfn_DECgraphics(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_IBMgraphics(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_align_message(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_align_status(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_alignment(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_altkeyhandling(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_autounlock(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_boulder(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_catname(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_crash_email(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_crash_name(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_crash_urlmax(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_disclose(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_dogname(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_dungeon(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_effects(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_map(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_menu(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_message(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_size_map(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_size_menu(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_size_message(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_size_status(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_size_text(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_status(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_font_text(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_fruit(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_gender(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_glyph(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_hilite_status(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_horsename(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_map_mode(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_deselect_all(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_deselect_page(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_first_page(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_headings(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_invert_all(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_invert_page(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_last_page(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_next_page(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_objsyms(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_previous_page(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_search(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_select_all(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_select_page(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_shift_left(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menu_shift_right(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menuinvertmode(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_menustyle(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_monsters(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_mouse_support(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_msg_window(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_msghistory(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_name(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_number_pad(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_o_autocomplete(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_o_autopickup_exceptions(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_o_bind_keys(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_o_menu_colors(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_o_message_types(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_o_status_cond(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_o_status_hilites(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_objects(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_packorder(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_paranoid_confirmation(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_perminv_mode(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_petattr(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_pettype(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_pickup_burden(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_pickup_types(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_pile_limit(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_player_selection(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_playmode(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_race(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_roguesymset(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_role(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_runmode(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_scores(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_scroll_amount(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_scroll_margin(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_sortdiscoveries(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_sortloot(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_sortvanquished(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_soundlib(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_statushilites(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_statuslines(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_suppress_alert(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_symset(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_term_cols(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_term_rows(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_tile_file(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_tile_height(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_tile_width(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_traps(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_vary_msgcount(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_versinfo(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_warnings(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_whatis_coord(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_whatis_filter(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_windowborders(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_windowcolors(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_optfn_windowtype(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_pfxfn_cond_(int a0,int a1,boolean a2,char * a3,char * a4);
extern int teleport_options_callback_pfxfn_font(int a0,int a1,boolean a2,char * a3,char * a4);
void*teleport_options_function(int i){switch(i){
case 0:return(void*)do_reqmenu;
case 1:return(void*)teleport_options_callback_optfn_DECgraphics;
case 2:return(void*)teleport_options_callback_optfn_IBMgraphics;
case 3:return(void*)teleport_options_callback_optfn_align_message;
case 4:return(void*)teleport_options_callback_optfn_align_status;
case 5:return(void*)teleport_options_callback_optfn_alignment;
case 6:return(void*)teleport_options_callback_optfn_altkeyhandling;
case 7:return(void*)teleport_options_callback_optfn_autounlock;
case 8:return(void*)optfn_boolean;
case 9:return(void*)teleport_options_callback_optfn_boulder;
case 10:return(void*)teleport_options_callback_optfn_catname;
case 11:return(void*)teleport_options_callback_optfn_crash_email;
case 12:return(void*)teleport_options_callback_optfn_crash_name;
case 13:return(void*)teleport_options_callback_optfn_crash_urlmax;
case 14:return(void*)teleport_options_callback_optfn_disclose;
case 15:return(void*)teleport_options_callback_optfn_dogname;
case 16:return(void*)teleport_options_callback_optfn_dungeon;
case 17:return(void*)teleport_options_callback_optfn_effects;
case 18:return(void*)teleport_options_callback_optfn_font_map;
case 19:return(void*)teleport_options_callback_optfn_font_menu;
case 20:return(void*)teleport_options_callback_optfn_font_message;
case 21:return(void*)teleport_options_callback_optfn_font_size_map;
case 22:return(void*)teleport_options_callback_optfn_font_size_menu;
case 23:return(void*)teleport_options_callback_optfn_font_size_message;
case 24:return(void*)teleport_options_callback_optfn_font_size_status;
case 25:return(void*)teleport_options_callback_optfn_font_size_text;
case 26:return(void*)teleport_options_callback_optfn_font_status;
case 27:return(void*)teleport_options_callback_optfn_font_text;
case 28:return(void*)teleport_options_callback_optfn_fruit;
case 29:return(void*)teleport_options_callback_optfn_gender;
case 30:return(void*)teleport_options_callback_optfn_glyph;
case 31:return(void*)teleport_options_callback_optfn_hilite_status;
case 32:return(void*)teleport_options_callback_optfn_horsename;
case 33:return(void*)teleport_options_callback_optfn_map_mode;
case 34:return(void*)teleport_options_callback_optfn_menu_deselect_all;
case 35:return(void*)teleport_options_callback_optfn_menu_deselect_page;
case 36:return(void*)teleport_options_callback_optfn_menu_first_page;
case 37:return(void*)teleport_options_callback_optfn_menu_headings;
case 38:return(void*)teleport_options_callback_optfn_menu_invert_all;
case 39:return(void*)teleport_options_callback_optfn_menu_invert_page;
case 40:return(void*)teleport_options_callback_optfn_menu_last_page;
case 41:return(void*)teleport_options_callback_optfn_menu_next_page;
case 42:return(void*)teleport_options_callback_optfn_menu_objsyms;
case 43:return(void*)teleport_options_callback_optfn_menu_previous_page;
case 44:return(void*)teleport_options_callback_optfn_menu_search;
case 45:return(void*)teleport_options_callback_optfn_menu_select_all;
case 46:return(void*)teleport_options_callback_optfn_menu_select_page;
case 47:return(void*)teleport_options_callback_optfn_menu_shift_left;
case 48:return(void*)teleport_options_callback_optfn_menu_shift_right;
case 49:return(void*)teleport_options_callback_optfn_menuinvertmode;
case 50:return(void*)teleport_options_callback_optfn_menustyle;
case 51:return(void*)teleport_options_callback_optfn_monsters;
case 52:return(void*)teleport_options_callback_optfn_mouse_support;
case 53:return(void*)teleport_options_callback_optfn_msg_window;
case 54:return(void*)teleport_options_callback_optfn_msghistory;
case 55:return(void*)teleport_options_callback_optfn_name;
case 56:return(void*)teleport_options_callback_optfn_number_pad;
case 57:return(void*)teleport_options_callback_optfn_o_autocomplete;
case 58:return(void*)teleport_options_callback_optfn_o_autopickup_exceptions;
case 59:return(void*)teleport_options_callback_optfn_o_bind_keys;
case 60:return(void*)teleport_options_callback_optfn_o_menu_colors;
case 61:return(void*)teleport_options_callback_optfn_o_message_types;
case 62:return(void*)teleport_options_callback_optfn_o_status_cond;
case 63:return(void*)teleport_options_callback_optfn_o_status_hilites;
case 64:return(void*)teleport_options_callback_optfn_objects;
case 65:return(void*)teleport_options_callback_optfn_packorder;
case 66:return(void*)teleport_options_callback_optfn_paranoid_confirmation;
case 67:return(void*)teleport_options_callback_optfn_perminv_mode;
case 68:return(void*)teleport_options_callback_optfn_petattr;
case 69:return(void*)teleport_options_callback_optfn_pettype;
case 70:return(void*)teleport_options_callback_optfn_pickup_burden;
case 71:return(void*)teleport_options_callback_optfn_pickup_types;
case 72:return(void*)teleport_options_callback_optfn_pile_limit;
case 73:return(void*)teleport_options_callback_optfn_player_selection;
case 74:return(void*)teleport_options_callback_optfn_playmode;
case 75:return(void*)teleport_options_callback_optfn_race;
case 76:return(void*)teleport_options_callback_optfn_roguesymset;
case 77:return(void*)teleport_options_callback_optfn_role;
case 78:return(void*)teleport_options_callback_optfn_runmode;
case 79:return(void*)teleport_options_callback_optfn_scores;
case 80:return(void*)teleport_options_callback_optfn_scroll_amount;
case 81:return(void*)teleport_options_callback_optfn_scroll_margin;
case 82:return(void*)teleport_options_callback_optfn_sortdiscoveries;
case 83:return(void*)teleport_options_callback_optfn_sortloot;
case 84:return(void*)teleport_options_callback_optfn_sortvanquished;
case 85:return(void*)teleport_options_callback_optfn_soundlib;
case 86:return(void*)teleport_options_callback_optfn_statushilites;
case 87:return(void*)teleport_options_callback_optfn_statuslines;
case 88:return(void*)teleport_options_callback_optfn_suppress_alert;
case 89:return(void*)teleport_options_callback_optfn_symset;
case 90:return(void*)teleport_options_callback_optfn_term_cols;
case 91:return(void*)teleport_options_callback_optfn_term_rows;
case 92:return(void*)teleport_options_callback_optfn_tile_file;
case 93:return(void*)teleport_options_callback_optfn_tile_height;
case 94:return(void*)teleport_options_callback_optfn_tile_width;
case 95:return(void*)teleport_options_callback_optfn_traps;
case 96:return(void*)teleport_options_callback_optfn_vary_msgcount;
case 97:return(void*)teleport_options_callback_optfn_versinfo;
case 98:return(void*)teleport_options_callback_optfn_warnings;
case 99:return(void*)teleport_options_callback_optfn_whatis_coord;
case 100:return(void*)teleport_options_callback_optfn_whatis_filter;
case 101:return(void*)teleport_options_callback_optfn_windowborders;
case 102:return(void*)teleport_options_callback_optfn_windowcolors;
case 103:return(void*)teleport_options_callback_optfn_windowtype;
case 104:return(void*)teleport_options_callback_pfxfn_cond_;
case 105:return(void*)teleport_options_callback_pfxfn_font;
case 106:return(void*)rn2;
case 107:return(void*)rn2_on_display_rng;
default:abort();}}
#ifdef TELEPORT_OPTIONS_VALIDATE_ORIGINAL
_Static_assert(sizeof allopt_init==sizeof options_backing_0,"OPTIONS private backing size");
_Static_assert(sizeof allopt==sizeof options_backing_1,"OPTIONS private backing size");
_Static_assert(sizeof empty_optstr==sizeof options_backing_2,"OPTIONS private backing size");
_Static_assert(sizeof duplicate==sizeof options_backing_3,"OPTIONS private backing size");
_Static_assert(sizeof using_alias==sizeof options_backing_4,"OPTIONS private backing size");
_Static_assert(sizeof give_opt_msg==sizeof options_backing_5,"OPTIONS private backing size");
_Static_assert(sizeof opt_set_in_config==sizeof options_backing_6,"OPTIONS private backing size");
_Static_assert(sizeof roleoptvals==sizeof options_backing_7,"OPTIONS private backing size");
_Static_assert(sizeof OptS_type==sizeof options_backing_8,"OPTIONS private backing size");
_Static_assert(sizeof def_inv_order==sizeof options_backing_9,"OPTIONS private backing size");
_Static_assert(sizeof none==sizeof options_backing_10,"OPTIONS private backing size");
_Static_assert(sizeof randomrole==sizeof options_backing_11,"OPTIONS private backing size");
_Static_assert(sizeof to_be_done==sizeof options_backing_12,"OPTIONS private backing size");
_Static_assert(sizeof defopt==sizeof options_backing_13,"OPTIONS private backing size");
_Static_assert(sizeof defbrief==sizeof options_backing_14,"OPTIONS private backing size");
_Static_assert(sizeof paranoia==sizeof options_backing_15,"OPTIONS private backing size");
_Static_assert(sizeof menutype==sizeof options_backing_16,"OPTIONS private backing size");
_Static_assert(sizeof msgwind==sizeof options_backing_17,"OPTIONS private backing size");
_Static_assert(sizeof unlocktypes==sizeof options_backing_18,"OPTIONS private backing size");
_Static_assert(sizeof burdentype==sizeof options_backing_19,"OPTIONS private backing size");
_Static_assert(sizeof runmodes==sizeof options_backing_20,"OPTIONS private backing size");
_Static_assert(sizeof sortltype==sizeof options_backing_21,"OPTIONS private backing size");
_Static_assert(sizeof perminv_modes==sizeof options_backing_22,"OPTIONS private backing size");
_Static_assert(sizeof objsymvals==sizeof options_backing_23,"OPTIONS private backing size");
_Static_assert(sizeof default_menu_cmd_info==sizeof options_backing_24,"OPTIONS private backing size");
_Static_assert(sizeof n_currently_set==sizeof options_backing_25,"OPTIONS private backing size");
_Static_assert(sizeof roleopt2opt==sizeof options_backing_26,"OPTIONS private backing size");
_Static_assert(sizeof wcnames==sizeof options_backing_34,"OPTIONS private backing size");
_Static_assert(sizeof wcshortnames==sizeof options_backing_35,"OPTIONS private backing size");
_Static_assert(sizeof msgtype_names==sizeof options_backing_43,"OPTIONS private backing size");
_Static_assert(sizeof opt_intro==sizeof options_backing_59,"OPTIONS private backing size");
_Static_assert(sizeof opt_epilog==sizeof options_backing_60,"OPTIONS private backing size");
_Static_assert(sizeof wc_options==sizeof options_backing_62,"OPTIONS private backing size");
_Static_assert(sizeof wc2_options==sizeof options_backing_63,"OPTIONS private backing size");
_Static_assert(sizeof fgp==sizeof options_backing_64,"OPTIONS private backing size");
_Static_assert(sizeof bgp==sizeof options_backing_65,"OPTIONS private backing size");
#endif
int teleport_options_isspace(int c){return isspace(c); }
void teleport_options_free(void*p){free(p); }
