/* ROLE compiler-derived layouts and scalar expression values. */
#ifndef TELEPORT_ROLE_LAYOUT_H
#define TELEPORT_ROLE_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#define ROLE_META(k,v) {#k,(size_t)(v)}
static const struct {const char*name;size_t value;} role_layout[]={
ROLE_META(pointerSize,sizeof(void*)),
ROLE_META(intSize,sizeof(int)),
ROLE_META(longSize,sizeof(long)),
ROLE_META(roleCount,NUM_ROLES+1),
ROLE_META(raceCount,NUM_RACES+1),
ROLE_META(genderCount,4),
ROLE_META(alignCount,4),
ROLE_META(priestSuffixLength,sizeof "priest/priestess'" - sizeof ""),
ROLE_META(roleSize,sizeof(struct Role)),
ROLE_META(role_name,offsetof(struct Role,name)),
ROLE_META(role_name_size,sizeof(((struct Role*)0)->name)),
ROLE_META(role_rank,offsetof(struct Role,rank)),
ROLE_META(role_rank_size,sizeof(((struct Role*)0)->rank)),
ROLE_META(role_lgod,offsetof(struct Role,lgod)),
ROLE_META(role_lgod_size,sizeof(((struct Role*)0)->lgod)),
ROLE_META(role_ngod,offsetof(struct Role,ngod)),
ROLE_META(role_ngod_size,sizeof(((struct Role*)0)->ngod)),
ROLE_META(role_cgod,offsetof(struct Role,cgod)),
ROLE_META(role_cgod_size,sizeof(((struct Role*)0)->cgod)),
ROLE_META(role_filecode,offsetof(struct Role,filecode)),
ROLE_META(role_filecode_size,sizeof(((struct Role*)0)->filecode)),
ROLE_META(role_homebase,offsetof(struct Role,homebase)),
ROLE_META(role_homebase_size,sizeof(((struct Role*)0)->homebase)),
ROLE_META(role_intermed,offsetof(struct Role,intermed)),
ROLE_META(role_intermed_size,sizeof(((struct Role*)0)->intermed)),
ROLE_META(role_mnum,offsetof(struct Role,mnum)),
ROLE_META(role_mnum_size,sizeof(((struct Role*)0)->mnum)),
ROLE_META(role_petnum,offsetof(struct Role,petnum)),
ROLE_META(role_petnum_size,sizeof(((struct Role*)0)->petnum)),
ROLE_META(role_ldrnum,offsetof(struct Role,ldrnum)),
ROLE_META(role_ldrnum_size,sizeof(((struct Role*)0)->ldrnum)),
ROLE_META(role_guardnum,offsetof(struct Role,guardnum)),
ROLE_META(role_guardnum_size,sizeof(((struct Role*)0)->guardnum)),
ROLE_META(role_neminum,offsetof(struct Role,neminum)),
ROLE_META(role_neminum_size,sizeof(((struct Role*)0)->neminum)),
ROLE_META(role_enemy1num,offsetof(struct Role,enemy1num)),
ROLE_META(role_enemy1num_size,sizeof(((struct Role*)0)->enemy1num)),
ROLE_META(role_enemy2num,offsetof(struct Role,enemy2num)),
ROLE_META(role_enemy2num_size,sizeof(((struct Role*)0)->enemy2num)),
ROLE_META(role_enemy1sym,offsetof(struct Role,enemy1sym)),
ROLE_META(role_enemy1sym_size,sizeof(((struct Role*)0)->enemy1sym)),
ROLE_META(role_enemy2sym,offsetof(struct Role,enemy2sym)),
ROLE_META(role_enemy2sym_size,sizeof(((struct Role*)0)->enemy2sym)),
ROLE_META(role_questarti,offsetof(struct Role,questarti)),
ROLE_META(role_questarti_size,sizeof(((struct Role*)0)->questarti)),
ROLE_META(role_allow,offsetof(struct Role,allow)),
ROLE_META(role_allow_size,sizeof(((struct Role*)0)->allow)),
ROLE_META(role_attrbase,offsetof(struct Role,attrbase)),
ROLE_META(role_attrbase_size,sizeof(((struct Role*)0)->attrbase)),
ROLE_META(role_attrdist,offsetof(struct Role,attrdist)),
ROLE_META(role_attrdist_size,sizeof(((struct Role*)0)->attrdist)),
ROLE_META(role_hpadv,offsetof(struct Role,hpadv)),
ROLE_META(role_hpadv_size,sizeof(((struct Role*)0)->hpadv)),
ROLE_META(role_enadv,offsetof(struct Role,enadv)),
ROLE_META(role_enadv_size,sizeof(((struct Role*)0)->enadv)),
ROLE_META(role_xlev,offsetof(struct Role,xlev)),
ROLE_META(role_xlev_size,sizeof(((struct Role*)0)->xlev)),
ROLE_META(role_initrecord,offsetof(struct Role,initrecord)),
ROLE_META(role_initrecord_size,sizeof(((struct Role*)0)->initrecord)),
ROLE_META(role_spelbase,offsetof(struct Role,spelbase)),
ROLE_META(role_spelbase_size,sizeof(((struct Role*)0)->spelbase)),
ROLE_META(role_spelheal,offsetof(struct Role,spelheal)),
ROLE_META(role_spelheal_size,sizeof(((struct Role*)0)->spelheal)),
ROLE_META(role_spelshld,offsetof(struct Role,spelshld)),
ROLE_META(role_spelshld_size,sizeof(((struct Role*)0)->spelshld)),
ROLE_META(role_spelarmr,offsetof(struct Role,spelarmr)),
ROLE_META(role_spelarmr_size,sizeof(((struct Role*)0)->spelarmr)),
ROLE_META(role_spelstat,offsetof(struct Role,spelstat)),
ROLE_META(role_spelstat_size,sizeof(((struct Role*)0)->spelstat)),
ROLE_META(role_spelspec,offsetof(struct Role,spelspec)),
ROLE_META(role_spelspec_size,sizeof(((struct Role*)0)->spelspec)),
ROLE_META(role_spelsbon,offsetof(struct Role,spelsbon)),
ROLE_META(role_spelsbon_size,sizeof(((struct Role*)0)->spelsbon)),
ROLE_META(raceSize,sizeof(struct Race)),
ROLE_META(race_noun,offsetof(struct Race,noun)),
ROLE_META(race_noun_size,sizeof(((struct Race*)0)->noun)),
ROLE_META(race_adj,offsetof(struct Race,adj)),
ROLE_META(race_adj_size,sizeof(((struct Race*)0)->adj)),
ROLE_META(race_coll,offsetof(struct Race,coll)),
ROLE_META(race_coll_size,sizeof(((struct Race*)0)->coll)),
ROLE_META(race_filecode,offsetof(struct Race,filecode)),
ROLE_META(race_filecode_size,sizeof(((struct Race*)0)->filecode)),
ROLE_META(race_individual,offsetof(struct Race,individual)),
ROLE_META(race_individual_size,sizeof(((struct Race*)0)->individual)),
ROLE_META(race_mnum,offsetof(struct Race,mnum)),
ROLE_META(race_mnum_size,sizeof(((struct Race*)0)->mnum)),
ROLE_META(race_mummynum,offsetof(struct Race,mummynum)),
ROLE_META(race_mummynum_size,sizeof(((struct Race*)0)->mummynum)),
ROLE_META(race_zombienum,offsetof(struct Race,zombienum)),
ROLE_META(race_zombienum_size,sizeof(((struct Race*)0)->zombienum)),
ROLE_META(race_allow,offsetof(struct Race,allow)),
ROLE_META(race_allow_size,sizeof(((struct Race*)0)->allow)),
ROLE_META(race_selfmask,offsetof(struct Race,selfmask)),
ROLE_META(race_selfmask_size,sizeof(((struct Race*)0)->selfmask)),
ROLE_META(race_lovemask,offsetof(struct Race,lovemask)),
ROLE_META(race_lovemask_size,sizeof(((struct Race*)0)->lovemask)),
ROLE_META(race_hatemask,offsetof(struct Race,hatemask)),
ROLE_META(race_hatemask_size,sizeof(((struct Race*)0)->hatemask)),
ROLE_META(race_attrmin,offsetof(struct Race,attrmin)),
ROLE_META(race_attrmin_size,sizeof(((struct Race*)0)->attrmin)),
ROLE_META(race_attrmax,offsetof(struct Race,attrmax)),
ROLE_META(race_attrmax_size,sizeof(((struct Race*)0)->attrmax)),
ROLE_META(race_hpadv,offsetof(struct Race,hpadv)),
ROLE_META(race_hpadv_size,sizeof(((struct Race*)0)->hpadv)),
ROLE_META(race_enadv,offsetof(struct Race,enadv)),
ROLE_META(race_enadv_size,sizeof(((struct Race*)0)->enadv)),
ROLE_META(nameSize,sizeof(struct RoleName)),
ROLE_META(name_m,offsetof(struct RoleName,m)),
ROLE_META(name_m_size,sizeof(((struct RoleName*)0)->m)),
ROLE_META(name_f,offsetof(struct RoleName,f)),
ROLE_META(name_f_size,sizeof(((struct RoleName*)0)->f)),
ROLE_META(advanceSize,sizeof(struct RoleAdvance)),
ROLE_META(advance_infix,offsetof(struct RoleAdvance,infix)),
ROLE_META(advance_infix_size,sizeof(((struct RoleAdvance*)0)->infix)),
ROLE_META(advance_inrnd,offsetof(struct RoleAdvance,inrnd)),
ROLE_META(advance_inrnd_size,sizeof(((struct RoleAdvance*)0)->inrnd)),
ROLE_META(advance_lofix,offsetof(struct RoleAdvance,lofix)),
ROLE_META(advance_lofix_size,sizeof(((struct RoleAdvance*)0)->lofix)),
ROLE_META(advance_lornd,offsetof(struct RoleAdvance,lornd)),
ROLE_META(advance_lornd_size,sizeof(((struct RoleAdvance*)0)->lornd)),
ROLE_META(advance_hifix,offsetof(struct RoleAdvance,hifix)),
ROLE_META(advance_hifix_size,sizeof(((struct RoleAdvance*)0)->hifix)),
ROLE_META(advance_hirnd,offsetof(struct RoleAdvance,hirnd)),
ROLE_META(advance_hirnd_size,sizeof(((struct RoleAdvance*)0)->hirnd)),
ROLE_META(genderSize,sizeof(struct Gender)),
ROLE_META(gender_adj,offsetof(struct Gender,adj)),
ROLE_META(gender_adj_size,sizeof(((struct Gender*)0)->adj)),
ROLE_META(gender_he,offsetof(struct Gender,he)),
ROLE_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
ROLE_META(gender_him,offsetof(struct Gender,him)),
ROLE_META(gender_him_size,sizeof(((struct Gender*)0)->him)),
ROLE_META(gender_his,offsetof(struct Gender,his)),
ROLE_META(gender_his_size,sizeof(((struct Gender*)0)->his)),
ROLE_META(gender_filecode,offsetof(struct Gender,filecode)),
ROLE_META(gender_filecode_size,sizeof(((struct Gender*)0)->filecode)),
ROLE_META(gender_allow,offsetof(struct Gender,allow)),
ROLE_META(gender_allow_size,sizeof(((struct Gender*)0)->allow)),
ROLE_META(alignSize,sizeof(struct Align)),
ROLE_META(align_noun,offsetof(struct Align,noun)),
ROLE_META(align_noun_size,sizeof(((struct Align*)0)->noun)),
ROLE_META(align_adj,offsetof(struct Align,adj)),
ROLE_META(align_adj_size,sizeof(((struct Align*)0)->adj)),
ROLE_META(align_filecode,offsetof(struct Align,filecode)),
ROLE_META(align_filecode_size,sizeof(((struct Align*)0)->filecode)),
ROLE_META(align_allow,offsetof(struct Align,allow)),
ROLE_META(align_allow_size,sizeof(((struct Align*)0)->allow)),
ROLE_META(align_value,offsetof(struct Align,value)),
ROLE_META(align_value_size,sizeof(((struct Align*)0)->value)),
ROLE_META(pmSize,sizeof(struct permonst)),
ROLE_META(pm_msound,offsetof(struct permonst,msound)),
ROLE_META(pm_msound_size,sizeof(((struct permonst*)0)->msound)),
ROLE_META(pm_mflags2,offsetof(struct permonst,mflags2)),
ROLE_META(pm_mflags2_size,sizeof(((struct permonst*)0)->mflags2)),
ROLE_META(pm_mflags3,offsetof(struct permonst,mflags3)),
ROLE_META(pm_mflags3_size,sizeof(((struct permonst*)0)->mflags3)),
ROLE_META(pm_maligntyp,offsetof(struct permonst,maligntyp)),
ROLE_META(pm_maligntyp_size,sizeof(((struct permonst*)0)->maligntyp)),
ROLE_META(monSize,sizeof(struct monst)),
ROLE_META(mon_data,offsetof(struct monst,data)),
ROLE_META(mon_data_size,sizeof(((struct monst*)0)->data)),
ROLE_META(clsSize,sizeof(struct objclass)),
ROLE_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
ROLE_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
ROLE_META(anySize,sizeof(anything)),
ROLE_META(any_a_int,offsetof(anything,a_int)),
ROLE_META(any_a_int_size,sizeof(((anything*)0)->a_int)),
ROLE_META(any_a_string,offsetof(anything,a_string)),
ROLE_META(any_a_string_size,sizeof(((anything*)0)->a_string)),
ROLE_META(menuSize,sizeof(menu_item)),
ROLE_META(menu_item,offsetof(menu_item,item)),
ROLE_META(menu_item_size,sizeof(((menu_item*)0)->item)),
ROLE_META(menu_count,offsetof(menu_item,count)),
ROLE_META(menu_count_size,sizeof(((menu_item*)0)->count)),
ROLE_META(gu_role,offsetof(__typeof__(gu),urole)),
ROLE_META(gu_role_size,sizeof(gu.urole)),
ROLE_META(gu_race,offsetof(__typeof__(gu),urace)),
ROLE_META(gu_race_size,sizeof(gu.urace)),
ROLE_META(gr_mask,offsetof(__typeof__(gr),rfilter.mask)),
ROLE_META(gr_mask_size,sizeof(gr.rfilter.mask)),
ROLE_META(gr_roles,offsetof(__typeof__(gr),rfilter.roles)),
ROLE_META(gr_roles_size,sizeof(gr.rfilter.roles)),
ROLE_META(gr_post,offsetof(__typeof__(gr),role_post_attribs)),
ROLE_META(gr_post_size,sizeof(gr.role_post_attribs)),
ROLE_META(gr_pa,offsetof(__typeof__(gr),role_pa)),
ROLE_META(gr_pa_size,sizeof(gr.role_pa)),
ROLE_META(plname,offsetof(__typeof__(svp),plname)),
ROLE_META(plname_size,sizeof(svp.plname)),
ROLE_META(pl_character,offsetof(__typeof__(svp),pl_character)),
ROLE_META(pl_character_size,sizeof(svp.pl_character)),
ROLE_META(plnamelen,offsetof(__typeof__(gp),plnamelen)),
ROLE_META(plnamelen_size,sizeof(gp.plnamelen)),
ROLE_META(genericusers,offsetof(__typeof__(sysopt),genericusers)),
ROLE_META(genericusers_size,sizeof(sysopt.genericusers)),
ROLE_META(in_role_selection,offsetof(__typeof__(program_state),in_role_selection)),
ROLE_META(in_role_selection_size,sizeof(program_state.in_role_selection)),
ROLE_META(zeroany,offsetof(__typeof__(cg),zeroany)),
ROLE_META(zeroany_size,sizeof(cg.zeroany)),
ROLE_META(flags_initrole,offsetof(__typeof__(flags),initrole)),
ROLE_META(flags_initrole_size,sizeof(flags.initrole)),
ROLE_META(flags_initrace,offsetof(__typeof__(flags),initrace)),
ROLE_META(flags_initrace_size,sizeof(flags.initrace)),
ROLE_META(flags_initgend,offsetof(__typeof__(flags),initgend)),
ROLE_META(flags_initgend_size,sizeof(flags.initgend)),
ROLE_META(flags_initalign,offsetof(__typeof__(flags),initalign)),
ROLE_META(flags_initalign_size,sizeof(flags.initalign)),
ROLE_META(flags_pantheon,offsetof(__typeof__(flags),pantheon)),
ROLE_META(flags_pantheon_size,sizeof(flags.pantheon)),
ROLE_META(flags_female,offsetof(__typeof__(flags),female)),
ROLE_META(flags_female_size,sizeof(flags.female)),
ROLE_META(flags_randomall,offsetof(__typeof__(flags),randomall)),
ROLE_META(flags_randomall_size,sizeof(flags.randomall)),
ROLE_META(iflags_defer_plname,offsetof(__typeof__(iflags),defer_plname)),
ROLE_META(iflags_defer_plname_size,sizeof(iflags.defer_plname)),
ROLE_META(iflags_renameallowed,offsetof(__typeof__(iflags),renameallowed)),
ROLE_META(iflags_renameallowed_size,sizeof(iflags.renameallowed)),
ROLE_META(iflags_renameinprogress,offsetof(__typeof__(iflags),renameinprogress)),
ROLE_META(iflags_renameinprogress_size,sizeof(iflags.renameinprogress)),
ROLE_META(expr_0,PM_ARCHEOLOGIST),
ROLE_META(expr_1,NON_PM),
ROLE_META(expr_2,PM_LORD_CARNARVON),
ROLE_META(expr_3,PM_STUDENT),
ROLE_META(expr_4,PM_MINION_OF_HUHETOTL),
ROLE_META(expr_5,PM_HUMAN_MUMMY),
ROLE_META(expr_6,S_SNAKE),
ROLE_META(expr_7,S_MUMMY),
ROLE_META(expr_8,ART_ORB_OF_DETECTION),
ROLE_META(expr_9,MH_HUMAN | MH_DWARF | MH_GNOME | ROLE_MALE | ROLE_FEMALE | ROLE_LAWFUL
          | ROLE_NEUTRAL),
ROLE_META(expr_10,A_INT),
ROLE_META(expr_11,SPE_MAGIC_MAPPING),
ROLE_META(expr_12,PM_BARBARIAN),
ROLE_META(expr_13,PM_PELIAS),
ROLE_META(expr_14,PM_CHIEFTAIN),
ROLE_META(expr_15,PM_THOTH_AMON),
ROLE_META(expr_16,PM_OGRE),
ROLE_META(expr_17,PM_TROLL),
ROLE_META(expr_18,S_OGRE),
ROLE_META(expr_19,S_TROLL),
ROLE_META(expr_20,ART_HEART_OF_AHRIMAN),
ROLE_META(expr_21,MH_HUMAN | MH_ORC | ROLE_MALE | ROLE_FEMALE | ROLE_NEUTRAL
          | ROLE_CHAOTIC),
ROLE_META(expr_22,SPE_HASTE_SELF),
ROLE_META(expr_23,PM_CAVE_DWELLER),
ROLE_META(expr_24,PM_LITTLE_DOG),
ROLE_META(expr_25,PM_SHAMAN_KARNOV),
ROLE_META(expr_26,PM_NEANDERTHAL),
ROLE_META(expr_27,PM_CHROMATIC_DRAGON),
ROLE_META(expr_28,PM_BUGBEAR),
ROLE_META(expr_29,PM_HILL_GIANT),
ROLE_META(expr_30,S_HUMANOID),
ROLE_META(expr_31,S_GIANT),
ROLE_META(expr_32,ART_SCEPTRE_OF_MIGHT),
ROLE_META(expr_33,SPE_DIG),
ROLE_META(expr_34,PM_HEALER),
ROLE_META(expr_35,PM_HIPPOCRATES),
ROLE_META(expr_36,PM_ATTENDANT),
ROLE_META(expr_37,PM_CYCLOPS),
ROLE_META(expr_38,PM_GIANT_RAT),
ROLE_META(expr_39,PM_SNAKE),
ROLE_META(expr_40,S_RODENT),
ROLE_META(expr_41,S_YETI),
ROLE_META(expr_42,ART_STAFF_OF_AESCULAPIUS),
ROLE_META(expr_43,MH_HUMAN | MH_GNOME | ROLE_MALE | ROLE_FEMALE | ROLE_NEUTRAL),
ROLE_META(expr_44,A_WIS),
ROLE_META(expr_45,SPE_CURE_SICKNESS),
ROLE_META(expr_46,PM_KNIGHT),
ROLE_META(expr_47,PM_PONY),
ROLE_META(expr_48,PM_KING_ARTHUR),
ROLE_META(expr_49,PM_PAGE),
ROLE_META(expr_50,PM_IXOTH),
ROLE_META(expr_51,PM_QUASIT),
ROLE_META(expr_52,PM_OCHRE_JELLY),
ROLE_META(expr_53,S_IMP),
ROLE_META(expr_54,S_JELLY),
ROLE_META(expr_55,ART_MAGIC_MIRROR_OF_MERLIN),
ROLE_META(expr_56,MH_HUMAN | ROLE_MALE | ROLE_FEMALE | ROLE_LAWFUL),
ROLE_META(expr_57,SPE_TURN_UNDEAD),
ROLE_META(expr_58,PM_MONK),
ROLE_META(expr_59,PM_GRAND_MASTER),
ROLE_META(expr_60,PM_ABBOT),
ROLE_META(expr_61,PM_MASTER_KAEN),
ROLE_META(expr_62,PM_EARTH_ELEMENTAL),
ROLE_META(expr_63,PM_XORN),
ROLE_META(expr_64,S_ELEMENTAL),
ROLE_META(expr_65,S_XORN),
ROLE_META(expr_66,ART_EYES_OF_THE_OVERWORLD),
ROLE_META(expr_67,MH_HUMAN | ROLE_MALE | ROLE_FEMALE | ROLE_LAWFUL | ROLE_NEUTRAL
          | ROLE_CHAOTIC),
ROLE_META(expr_68,SPE_RESTORE_ABILITY),
ROLE_META(expr_69,PM_CLERIC),
ROLE_META(expr_70,PM_ARCH_PRIEST),
ROLE_META(expr_71,PM_ACOLYTE),
ROLE_META(expr_72,PM_NALZOK),
ROLE_META(expr_73,PM_HUMAN_ZOMBIE),
ROLE_META(expr_74,PM_WRAITH),
ROLE_META(expr_75,S_ZOMBIE),
ROLE_META(expr_76,S_WRAITH),
ROLE_META(expr_77,ART_MITRE_OF_HOLINESS),
ROLE_META(expr_78,MH_HUMAN | MH_ELF | ROLE_MALE | ROLE_FEMALE | ROLE_LAWFUL | ROLE_NEUTRAL
          | ROLE_CHAOTIC),
ROLE_META(expr_79,SPE_REMOVE_CURSE),
ROLE_META(expr_80,PM_ROGUE),
ROLE_META(expr_81,PM_MASTER_OF_THIEVES),
ROLE_META(expr_82,PM_THUG),
ROLE_META(expr_83,PM_MASTER_ASSASSIN),
ROLE_META(expr_84,PM_LEPRECHAUN),
ROLE_META(expr_85,PM_GUARDIAN_NAGA),
ROLE_META(expr_86,S_NYMPH),
ROLE_META(expr_87,S_NAGA),
ROLE_META(expr_88,ART_MASTER_KEY_OF_THIEVERY),
ROLE_META(expr_89,MH_HUMAN | MH_ORC | ROLE_MALE | ROLE_FEMALE | ROLE_CHAOTIC),
ROLE_META(expr_90,SPE_DETECT_TREASURE),
ROLE_META(expr_91,PM_RANGER),
ROLE_META(expr_92,PM_ORION),
ROLE_META(expr_93,PM_HUNTER),
ROLE_META(expr_94,PM_SCORPIUS),
ROLE_META(expr_95,PM_FOREST_CENTAUR),
ROLE_META(expr_96,PM_SCORPION),
ROLE_META(expr_97,S_CENTAUR),
ROLE_META(expr_98,S_SPIDER),
ROLE_META(expr_99,ART_LONGBOW_OF_DIANA),
ROLE_META(expr_100,MH_HUMAN | MH_ELF | MH_GNOME | MH_ORC | ROLE_MALE | ROLE_FEMALE
          | ROLE_NEUTRAL | ROLE_CHAOTIC),
ROLE_META(expr_101,SPE_INVISIBILITY),
ROLE_META(expr_102,PM_SAMURAI),
ROLE_META(expr_103,PM_LORD_SATO),
ROLE_META(expr_104,PM_ROSHI),
ROLE_META(expr_105,PM_ASHIKAGA_TAKAUJI),
ROLE_META(expr_106,PM_WOLF),
ROLE_META(expr_107,PM_STALKER),
ROLE_META(expr_108,S_DOG),
ROLE_META(expr_109,ART_TSURUGI_OF_MURAMASA),
ROLE_META(expr_110,SPE_CLAIRVOYANCE),
ROLE_META(expr_111,PM_TOURIST),
ROLE_META(expr_112,PM_TWOFLOWER),
ROLE_META(expr_113,PM_GUIDE),
ROLE_META(expr_114,PM_GIANT_SPIDER),
ROLE_META(expr_115,ART_YENDORIAN_EXPRESS_CARD),
ROLE_META(expr_116,MH_HUMAN | ROLE_MALE | ROLE_FEMALE | ROLE_NEUTRAL),
ROLE_META(expr_117,SPE_CHARM_MONSTER),
ROLE_META(expr_118,PM_VALKYRIE),
ROLE_META(expr_119,PM_NORN),
ROLE_META(expr_120,PM_WARRIOR),
ROLE_META(expr_121,PM_LORD_SURTUR),
ROLE_META(expr_122,PM_FIRE_ANT),
ROLE_META(expr_123,PM_FIRE_GIANT),
ROLE_META(expr_124,S_ANT),
ROLE_META(expr_125,ART_ORB_OF_FATE),
ROLE_META(expr_126,MH_HUMAN | MH_DWARF | ROLE_FEMALE | ROLE_LAWFUL | ROLE_NEUTRAL),
ROLE_META(expr_127,SPE_CONE_OF_COLD),
ROLE_META(expr_128,PM_WIZARD),
ROLE_META(expr_129,PM_KITTEN),
ROLE_META(expr_130,PM_NEFERET_THE_GREEN),
ROLE_META(expr_131,PM_APPRENTICE),
ROLE_META(expr_132,PM_DARK_ONE),
ROLE_META(expr_133,PM_VAMPIRE_BAT),
ROLE_META(expr_134,S_BAT),
ROLE_META(expr_135,ART_EYE_OF_THE_AETHIOPICA),
ROLE_META(expr_136,SPE_MAGIC_MISSILE),
ROLE_META(expr_137,STRANGE_OBJECT),
ROLE_META(expr_138,PM_HUMAN),
ROLE_META(expr_139,MH_HUMAN | ROLE_MALE | ROLE_FEMALE | ROLE_LAWFUL | ROLE_NEUTRAL
            | ROLE_CHAOTIC),
ROLE_META(expr_140,MH_HUMAN),
ROLE_META(expr_141,MH_GNOME | MH_ORC),
ROLE_META(expr_142,STR18(100)),
ROLE_META(expr_143,PM_ELF),
ROLE_META(expr_144,PM_ELF_MUMMY),
ROLE_META(expr_145,PM_ELF_ZOMBIE),
ROLE_META(expr_146,MH_ELF | ROLE_MALE | ROLE_FEMALE | ROLE_CHAOTIC),
ROLE_META(expr_147,MH_ELF),
ROLE_META(expr_148,MH_ORC),
ROLE_META(expr_149,PM_DWARF),
ROLE_META(expr_150,PM_DWARF_MUMMY),
ROLE_META(expr_151,PM_DWARF_ZOMBIE),
ROLE_META(expr_152,MH_DWARF | ROLE_MALE | ROLE_FEMALE | ROLE_LAWFUL),
ROLE_META(expr_153,MH_DWARF),
ROLE_META(expr_154,MH_DWARF | MH_GNOME),
ROLE_META(expr_155,PM_GNOME),
ROLE_META(expr_156,PM_GNOME_MUMMY),
ROLE_META(expr_157,PM_GNOME_ZOMBIE),
ROLE_META(expr_158,MH_GNOME | ROLE_MALE | ROLE_FEMALE | ROLE_NEUTRAL),
ROLE_META(expr_159,MH_GNOME),
ROLE_META(expr_160,STR18(50)),
ROLE_META(expr_161,PM_ORC),
ROLE_META(expr_162,PM_ORC_MUMMY),
ROLE_META(expr_163,PM_ORC_ZOMBIE),
ROLE_META(expr_164,MH_ORC | ROLE_MALE | ROLE_FEMALE | ROLE_CHAOTIC),
ROLE_META(expr_165,MH_HUMAN | MH_ELF | MH_DWARF),
ROLE_META(expr_166,ROLE_MALE),
ROLE_META(expr_167,ROLE_FEMALE),
ROLE_META(expr_168,ROLE_NEUTER),
ROLE_META(expr_169,ROLE_LAWFUL),
ROLE_META(expr_170,A_LAWFUL),
ROLE_META(expr_171,ROLE_NEUTRAL),
ROLE_META(expr_172,A_NEUTRAL),
ROLE_META(expr_173,ROLE_CHAOTIC),
ROLE_META(expr_174,A_CHAOTIC),
ROLE_META(expr_175,A_NONE),
ROLE_META(ROLE_RACEMASK,ROLE_RACEMASK),
ROLE_META(RS_GENDER,RS_GENDER),
ROLE_META(MENU_BEHAVE_STANDARD,MENU_BEHAVE_STANDARD),
ROLE_META(ROLE_ALIGNS,ROLE_ALIGNS),
ROLE_META(PM_HIGH_CLERIC,PM_HIGH_CLERIC),
ROLE_META(A_LAWFUL,A_LAWFUL),
ROLE_META(BUFSZ,BUFSZ),
ROLE_META(A_CHAOTIC,A_CHAOTIC),
ROLE_META(PICK_RIGID,PICK_RIGID),
ROLE_META(QBUFSZ,QBUFSZ),
ROLE_META(MS_NEMESIS,MS_NEMESIS),
ROLE_META(PM_SHOPKEEPER,PM_SHOPKEEPER),
ROLE_META(PM_KNIGHT,PM_KNIGHT),
ROLE_META(PL_CSIZ,PL_CSIZ),
ROLE_META(ROLE_FEMALE,ROLE_FEMALE),
ROLE_META(PM_TOURIST,PM_TOURIST),
ROLE_META(BP_ROLE,3),
ROLE_META(MS_LEADER,MS_LEADER),
ROLE_META(ROLE_LAWFUL,ROLE_LAWFUL),
ROLE_META(PICK_RANDOM,PICK_RANDOM),
ROLE_META(RS_NAME,RS_NAME),
ROLE_META(PM_WIZARD,PM_WIZARD),
ROLE_META(PM_SAMURAI,PM_SAMURAI),
ROLE_META(ROLE_NONE,ROLE_NONE),
ROLE_META(PM_CLERIC,PM_CLERIC),
ROLE_META(BP_RACE,2),
ROLE_META(AM_NEUTRAL,AM_NEUTRAL),
ROLE_META(AM_CHAOTIC,AM_CHAOTIC),
ROLE_META(RS_ALGNMNT,RS_ALGNMNT),
ROLE_META(ROLE_NEUTRAL,ROLE_NEUTRAL),
ROLE_META(BP_GEND,1),
ROLE_META(M2_PEACEFUL,M2_PEACEFUL),
ROLE_META(AM_LAWFUL,AM_LAWFUL),
ROLE_META(PM_ORC,PM_ORC),
ROLE_META(M2_MALE,M2_MALE),
ROLE_META(ROLE_NEUTER,ROLE_NEUTER),
ROLE_META(MENU_ITEMFLAGS_SELECTED,MENU_ITEMFLAGS_SELECTED),
ROLE_META(M2_NASTY,M2_NASTY),
ROLE_META(NUM_RACES,NUM_RACES),
ROLE_META(M3_CLOSE,M3_CLOSE),
ROLE_META(M3_WANTSARTI,M3_WANTSARTI),
ROLE_META(M2_HOSTILE,M2_HOSTILE),
ROLE_META(RS_RACE,RS_RACE),
ROLE_META(ROLE_MALE,ROLE_MALE),
ROLE_META(NON_PM,NON_PM),
ROLE_META(ROLE_RANDOM,ROLE_RANDOM),
ROLE_META(NUM_ROLES,NUM_ROLES),
ROLE_META(NUMMONS,NUMMONS),
ROLE_META(PL_NSIZ,PL_NSIZ),
ROLE_META(PICK_ONE,PICK_ONE),
ROLE_META(PICK_ANY,PICK_ANY),
ROLE_META(PM_HUMAN,PM_HUMAN),
ROLE_META(NHW_MENU,NHW_MENU),
ROLE_META(M2_FEMALE,M2_FEMALE),
ROLE_META(M2_STALK,M2_STALK),
ROLE_META(A_NONE,A_NONE),
ROLE_META(ROLE_ALIGNMASK,ROLE_ALIGNMASK),
ROLE_META(P_CLERIC_SPELL,P_CLERIC_SPELL),
ROLE_META(WIN_ERR,WIN_ERR),
ROLE_META(ROLE_CHAOTIC,ROLE_CHAOTIC),
ROLE_META(MH_HUMAN,MH_HUMAN),
ROLE_META(BP_ALIGN,0),

ROLE_META(ROLE_GENDMASK,ROLE_GENDMASK),
ROLE_META(EXIT_SUCCESS,EXIT_SUCCESS),
ROLE_META(ATR_NONE,ATR_NONE),
ROLE_META(NO_COLOR,NO_COLOR),
ROLE_META(RS_ROLE,RS_ROLE),
ROLE_META(ROLE_GENDERS,ROLE_GENDERS),
ROLE_META(NUM_BP,4),
ROLE_META(PM_VALKYRIE,PM_VALKYRIE),
ROLE_META(MENU_ITEMFLAGS_NONE,MENU_ITEMFLAGS_NONE),
ROLE_META(SPE_LIGHT,SPE_LIGHT),
ROLE_META(M3_WAITFORU,M3_WAITFORU),
ROLE_META(M2_NEUTER,M2_NEUTER),
ROLE_META(PM_MAIL_DAEMON,PM_MAIL_DAEMON),
ROLE_META(RS_filter,RS_filter),
};
_Static_assert(sizeof(((struct Role*)0)->lgod)==8,"role_lgod pointer");
_Static_assert(sizeof(((struct Role*)0)->ngod)==8,"role_ngod pointer");
_Static_assert(sizeof(((struct Role*)0)->cgod)==8,"role_cgod pointer");
_Static_assert(sizeof(((struct Role*)0)->filecode)==8,"role_filecode pointer");
_Static_assert(sizeof(((struct Role*)0)->homebase)==8,"role_homebase pointer");
_Static_assert(sizeof(((struct Role*)0)->intermed)==8,"role_intermed pointer");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"role_mnum width");
_Static_assert(((__typeof__(((struct Role*)0)->mnum))-1 < 0),"role_mnum signedness");
_Static_assert(sizeof(((struct Role*)0)->petnum)==2,"role_petnum width");
_Static_assert(((__typeof__(((struct Role*)0)->petnum))-1 < 0),"role_petnum signedness");
_Static_assert(sizeof(((struct Role*)0)->ldrnum)==2,"role_ldrnum width");
_Static_assert(((__typeof__(((struct Role*)0)->ldrnum))-1 < 0),"role_ldrnum signedness");
_Static_assert(sizeof(((struct Role*)0)->guardnum)==2,"role_guardnum width");
_Static_assert(((__typeof__(((struct Role*)0)->guardnum))-1 < 0),"role_guardnum signedness");
_Static_assert(sizeof(((struct Role*)0)->neminum)==2,"role_neminum width");
_Static_assert(((__typeof__(((struct Role*)0)->neminum))-1 < 0),"role_neminum signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy1num)==2,"role_enemy1num width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy1num))-1 < 0),"role_enemy1num signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy2num)==2,"role_enemy2num width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy2num))-1 < 0),"role_enemy2num signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy1sym)==1,"role_enemy1sym width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy1sym))-1 < 0),"role_enemy1sym signedness");
_Static_assert(sizeof(((struct Role*)0)->enemy2sym)==1,"role_enemy2sym width");
_Static_assert(((__typeof__(((struct Role*)0)->enemy2sym))-1 < 0),"role_enemy2sym signedness");
_Static_assert(sizeof(((struct Role*)0)->questarti)==2,"role_questarti width");
_Static_assert(((__typeof__(((struct Role*)0)->questarti))-1 < 0),"role_questarti signedness");
_Static_assert(sizeof(((struct Role*)0)->allow)==2,"role_allow width");
_Static_assert(((__typeof__(((struct Role*)0)->allow))-1 < 0),"role_allow signedness");
_Static_assert(sizeof(((struct Role*)0)->xlev)==2,"role_xlev width");
_Static_assert(((__typeof__(((struct Role*)0)->xlev))-1 < 0),"role_xlev signedness");
_Static_assert(sizeof(((struct Role*)0)->initrecord)==2,"role_initrecord width");
_Static_assert(((__typeof__(((struct Role*)0)->initrecord))-1 < 0),"role_initrecord signedness");
_Static_assert(sizeof(((struct Role*)0)->spelbase)==4,"role_spelbase width");
_Static_assert(((__typeof__(((struct Role*)0)->spelbase))-1 < 0),"role_spelbase signedness");
_Static_assert(sizeof(((struct Role*)0)->spelheal)==4,"role_spelheal width");
_Static_assert(((__typeof__(((struct Role*)0)->spelheal))-1 < 0),"role_spelheal signedness");
_Static_assert(sizeof(((struct Role*)0)->spelshld)==4,"role_spelshld width");
_Static_assert(((__typeof__(((struct Role*)0)->spelshld))-1 < 0),"role_spelshld signedness");
_Static_assert(sizeof(((struct Role*)0)->spelarmr)==4,"role_spelarmr width");
_Static_assert(((__typeof__(((struct Role*)0)->spelarmr))-1 < 0),"role_spelarmr signedness");
_Static_assert(sizeof(((struct Role*)0)->spelstat)==4,"role_spelstat width");
_Static_assert(((__typeof__(((struct Role*)0)->spelstat))-1 < 0),"role_spelstat signedness");
_Static_assert(sizeof(((struct Role*)0)->spelspec)==4,"role_spelspec width");
_Static_assert(((__typeof__(((struct Role*)0)->spelspec))-1 < 0),"role_spelspec signedness");
_Static_assert(sizeof(((struct Role*)0)->spelsbon)==4,"role_spelsbon width");
_Static_assert(((__typeof__(((struct Role*)0)->spelsbon))-1 < 0),"role_spelsbon signedness");
_Static_assert(sizeof(((struct Race*)0)->noun)==8,"race_noun pointer");
_Static_assert(sizeof(((struct Race*)0)->adj)==8,"race_adj pointer");
_Static_assert(sizeof(((struct Race*)0)->coll)==8,"race_coll pointer");
_Static_assert(sizeof(((struct Race*)0)->filecode)==8,"race_filecode pointer");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"race_mnum width");
_Static_assert(((__typeof__(((struct Race*)0)->mnum))-1 < 0),"race_mnum signedness");
_Static_assert(sizeof(((struct Race*)0)->mummynum)==2,"race_mummynum width");
_Static_assert(((__typeof__(((struct Race*)0)->mummynum))-1 < 0),"race_mummynum signedness");
_Static_assert(sizeof(((struct Race*)0)->zombienum)==2,"race_zombienum width");
_Static_assert(((__typeof__(((struct Race*)0)->zombienum))-1 < 0),"race_zombienum signedness");
_Static_assert(sizeof(((struct Race*)0)->allow)==2,"race_allow width");
_Static_assert(((__typeof__(((struct Race*)0)->allow))-1 < 0),"race_allow signedness");
_Static_assert(sizeof(((struct Race*)0)->selfmask)==2,"race_selfmask width");
_Static_assert(((__typeof__(((struct Race*)0)->selfmask))-1 < 0),"race_selfmask signedness");
_Static_assert(sizeof(((struct Race*)0)->lovemask)==2,"race_lovemask width");
_Static_assert(((__typeof__(((struct Race*)0)->lovemask))-1 < 0),"race_lovemask signedness");
_Static_assert(sizeof(((struct Race*)0)->hatemask)==2,"race_hatemask width");
_Static_assert(((__typeof__(((struct Race*)0)->hatemask))-1 < 0),"race_hatemask signedness");
_Static_assert(sizeof(((struct RoleName*)0)->m)==8,"name_m pointer");
_Static_assert(sizeof(((struct RoleName*)0)->f)==8,"name_f pointer");
_Static_assert(sizeof(((struct RoleAdvance*)0)->infix)==2,"advance_infix width");
_Static_assert(((__typeof__(((struct RoleAdvance*)0)->infix))-1 < 0),"advance_infix signedness");
_Static_assert(sizeof(((struct RoleAdvance*)0)->inrnd)==2,"advance_inrnd width");
_Static_assert(((__typeof__(((struct RoleAdvance*)0)->inrnd))-1 < 0),"advance_inrnd signedness");
_Static_assert(sizeof(((struct RoleAdvance*)0)->lofix)==2,"advance_lofix width");
_Static_assert(((__typeof__(((struct RoleAdvance*)0)->lofix))-1 < 0),"advance_lofix signedness");
_Static_assert(sizeof(((struct RoleAdvance*)0)->lornd)==2,"advance_lornd width");
_Static_assert(((__typeof__(((struct RoleAdvance*)0)->lornd))-1 < 0),"advance_lornd signedness");
_Static_assert(sizeof(((struct RoleAdvance*)0)->hifix)==2,"advance_hifix width");
_Static_assert(((__typeof__(((struct RoleAdvance*)0)->hifix))-1 < 0),"advance_hifix signedness");
_Static_assert(sizeof(((struct RoleAdvance*)0)->hirnd)==2,"advance_hirnd width");
_Static_assert(((__typeof__(((struct RoleAdvance*)0)->hirnd))-1 < 0),"advance_hirnd signedness");
_Static_assert(sizeof(((struct Gender*)0)->adj)==8,"gender_adj pointer");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"gender_he pointer");
_Static_assert(sizeof(((struct Gender*)0)->him)==8,"gender_him pointer");
_Static_assert(sizeof(((struct Gender*)0)->his)==8,"gender_his pointer");
_Static_assert(sizeof(((struct Gender*)0)->filecode)==8,"gender_filecode pointer");
_Static_assert(sizeof(((struct Gender*)0)->allow)==2,"gender_allow width");
_Static_assert(((__typeof__(((struct Gender*)0)->allow))-1 < 0),"gender_allow signedness");
_Static_assert(sizeof(((struct Align*)0)->noun)==8,"align_noun pointer");
_Static_assert(sizeof(((struct Align*)0)->adj)==8,"align_adj pointer");
_Static_assert(sizeof(((struct Align*)0)->filecode)==8,"align_filecode pointer");
_Static_assert(sizeof(((struct Align*)0)->allow)==2,"align_allow width");
_Static_assert(((__typeof__(((struct Align*)0)->allow))-1 < 0),"align_allow signedness");
_Static_assert(sizeof(((struct Align*)0)->value)==1,"align_value width");
_Static_assert(((__typeof__(((struct Align*)0)->value))-1 < 0),"align_value signedness");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1,"pm_msound width");
_Static_assert(((__typeof__(((struct permonst*)0)->msound))-1 > 0),"pm_msound signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"pm_mflags2 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags2))-1 > 0),"pm_mflags2 signedness");
_Static_assert(sizeof(((struct permonst*)0)->mflags3)==2,"pm_mflags3 width");
_Static_assert(((__typeof__(((struct permonst*)0)->mflags3))-1 > 0),"pm_mflags3 signedness");
_Static_assert(sizeof(((struct permonst*)0)->maligntyp)==1,"pm_maligntyp width");
_Static_assert(((__typeof__(((struct permonst*)0)->maligntyp))-1 < 0),"pm_maligntyp signedness");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"mon_data pointer");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((anything*)0)->a_int)==4,"any_a_int width");
_Static_assert(((__typeof__(((anything*)0)->a_int))-1 < 0),"any_a_int signedness");
_Static_assert(sizeof(((anything*)0)->a_string)==8,"any_a_string pointer");
_Static_assert(sizeof(((menu_item*)0)->count)==8,"menu_count width");
_Static_assert(((__typeof__(((menu_item*)0)->count))-1 < 0),"menu_count signedness");
// Independent native scalar guards for live global views.
_Static_assert(sizeof(gr.rfilter.mask)==2,"gr.rfilter.mask width");
_Static_assert(((__typeof__(gr.rfilter.mask))-1 < 0),"gr.rfilter.mask signedness");
_Static_assert(sizeof(gr.rfilter.roles[0])==1,"gr.rfilter.roles[0] width");
_Static_assert(((__typeof__(gr.rfilter.roles[0]))-1 < 0),"gr.rfilter.roles[0] signedness");
_Static_assert(sizeof(gr.role_post_attribs)==1,"gr.role_post_attribs width");
_Static_assert(((__typeof__(gr.role_post_attribs))-1 < 0),"gr.role_post_attribs signedness");
_Static_assert(sizeof(gr.role_pa[0])==1,"gr.role_pa[0] width");
_Static_assert(((__typeof__(gr.role_pa[0]))-1 < 0),"gr.role_pa[0] signedness");
_Static_assert(sizeof(gp.plnamelen)==4,"gp.plnamelen width");
_Static_assert(((__typeof__(gp.plnamelen))-1 < 0),"gp.plnamelen signedness");
_Static_assert(sizeof(program_state.in_role_selection)==4,"program_state.in_role_selection width");
_Static_assert(((__typeof__(program_state.in_role_selection))-1 < 0),"program_state.in_role_selection signedness");
_Static_assert(sizeof(flags.initrole)==4,"flags.initrole width");
_Static_assert(((__typeof__(flags.initrole))-1 < 0),"flags.initrole signedness");
_Static_assert(sizeof(flags.initrace)==4,"flags.initrace width");
_Static_assert(((__typeof__(flags.initrace))-1 < 0),"flags.initrace signedness");
_Static_assert(sizeof(flags.initgend)==4,"flags.initgend width");
_Static_assert(((__typeof__(flags.initgend))-1 < 0),"flags.initgend signedness");
_Static_assert(sizeof(flags.initalign)==4,"flags.initalign width");
_Static_assert(((__typeof__(flags.initalign))-1 < 0),"flags.initalign signedness");
_Static_assert(sizeof(flags.pantheon)==4,"flags.pantheon width");
_Static_assert(((__typeof__(flags.pantheon))-1 < 0),"flags.pantheon signedness");
_Static_assert(sizeof(flags.randomall)==4,"flags.randomall width");
_Static_assert(((__typeof__(flags.randomall))-1 < 0),"flags.randomall signedness");
_Static_assert(sizeof(flags.female)==1,"flags.female width");
_Static_assert(((__typeof__(flags.female))-1 < 0),"flags.female signedness");
_Static_assert(sizeof(iflags.defer_plname)==1,"iflags.defer_plname width");
_Static_assert(((__typeof__(iflags.defer_plname))-1 < 0),"iflags.defer_plname signedness");
_Static_assert(sizeof(iflags.renameallowed)==1,"iflags.renameallowed width");
_Static_assert(((__typeof__(iflags.renameallowed))-1 < 0),"iflags.renameallowed signedness");
_Static_assert(sizeof(iflags.renameinprogress)==1,"iflags.renameinprogress width");
_Static_assert(((__typeof__(iflags.renameinprogress))-1 < 0),"iflags.renameinprogress signedness");
_Static_assert(sizeof(sysopt.genericusers)==8,"genericusers pointer");
size_t probe_context_size(void){return sizeof(struct Role);}
int probe_layout_count(void){return sizeof role_layout/sizeof role_layout[0];}
const char*probe_layout_name(int i){return role_layout[i].name;}
size_t probe_layout_value(int i){return role_layout[i].value;}
#endif
