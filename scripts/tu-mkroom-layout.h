#ifndef TELEPORT_MKROOM_LAYOUT_H
#define TELEPORT_MKROOM_LAYOUT_H
#include "hack.h"
#include <stddef.h>
struct teleport_mkroom_meta {const char*name;size_t value;};
#define MKROOM_META(k,v) {#k,(size_t)(v)}
static const struct teleport_mkroom_meta mkroom_layout[]={
MKROOM_META(pointerSize,sizeof(void*)),
MKROOM_META(intSize,sizeof(int)),
MKROOM_META(longSize,sizeof(long)),
MKROOM_META(shortSize,sizeof(short)),
MKROOM_META(coordSize,sizeof(coord)),
MKROOM_META(coordxySize,sizeof(coordxy)),
MKROOM_META(roomSize,sizeof(struct mkroom)),
MKROOM_META(terrainSize,sizeof(struct rm)),
MKROOM_META(monsterSize,sizeof(struct monst)),
MKROOM_META(objectSize,sizeof(struct obj)),
MKROOM_META(permonstSize,sizeof(struct permonst)),
MKROOM_META(vitalSize,sizeof(struct mvitals)),
MKROOM_META(stairSize,sizeof(stairway)),
MKROOM_META(shopSize,sizeof(struct shclass)),
MKROOM_META(symSize,sizeof(struct class_sym)),
MKROOM_META(levelSize,sizeof(d_level)),
MKROOM_META(roomCount,sizeof svr.rooms/sizeof svr.rooms[0]),
MKROOM_META(doorSize,sizeof svd.doors[0]),
MKROOM_META(room_lx,offsetof(struct mkroom,lx)),
MKROOM_META(room_lx_size,sizeof(((struct mkroom*)0)->lx)),
MKROOM_META(room_hx,offsetof(struct mkroom,hx)),
MKROOM_META(room_hx_size,sizeof(((struct mkroom*)0)->hx)),
MKROOM_META(room_ly,offsetof(struct mkroom,ly)),
MKROOM_META(room_ly_size,sizeof(((struct mkroom*)0)->ly)),
MKROOM_META(room_hy,offsetof(struct mkroom,hy)),
MKROOM_META(room_hy_size,sizeof(((struct mkroom*)0)->hy)),
MKROOM_META(room_rtype,offsetof(struct mkroom,rtype)),
MKROOM_META(room_rtype_size,sizeof(((struct mkroom*)0)->rtype)),
MKROOM_META(room_orig_rtype,offsetof(struct mkroom,orig_rtype)),
MKROOM_META(room_orig_rtype_size,sizeof(((struct mkroom*)0)->orig_rtype)),
MKROOM_META(room_rlit,offsetof(struct mkroom,rlit)),
MKROOM_META(room_rlit_size,sizeof(((struct mkroom*)0)->rlit)),
MKROOM_META(room_needfill,offsetof(struct mkroom,needfill)),
MKROOM_META(room_needfill_size,sizeof(((struct mkroom*)0)->needfill)),
MKROOM_META(room_needjoining,offsetof(struct mkroom,needjoining)),
MKROOM_META(room_needjoining_size,sizeof(((struct mkroom*)0)->needjoining)),
MKROOM_META(room_doorct,offsetof(struct mkroom,doorct)),
MKROOM_META(room_doorct_size,sizeof(((struct mkroom*)0)->doorct)),
MKROOM_META(room_nsubrooms,offsetof(struct mkroom,nsubrooms)),
MKROOM_META(room_nsubrooms_size,sizeof(((struct mkroom*)0)->nsubrooms)),
MKROOM_META(room_irregular,offsetof(struct mkroom,irregular)),
MKROOM_META(room_irregular_size,sizeof(((struct mkroom*)0)->irregular)),
MKROOM_META(room_roomnoidx,offsetof(struct mkroom,roomnoidx)),
MKROOM_META(room_roomnoidx_size,sizeof(((struct mkroom*)0)->roomnoidx)),
MKROOM_META(room_fdoor,offsetof(struct mkroom,fdoor)),
MKROOM_META(room_fdoor_size,sizeof(((struct mkroom*)0)->fdoor)),
MKROOM_META(room_sbrooms,offsetof(struct mkroom,sbrooms)),
MKROOM_META(room_resident,offsetof(struct mkroom,resident)),
MKROOM_META(subroomCapacity,sizeof(((struct mkroom*)0)->sbrooms)/sizeof(void*)),
MKROOM_META(coord_x,offsetof(coord,x)),
MKROOM_META(coord_x_size,sizeof(((coord*)0)->x)),
MKROOM_META(coord_y,offsetof(coord,y)),
MKROOM_META(coord_y_size,sizeof(((coord*)0)->y)),
MKROOM_META(terrain_typ,offsetof(struct rm,typ)),
MKROOM_META(terrain_typ_size,sizeof(((struct rm*)0)->typ)),
MKROOM_META(obj_quan,offsetof(struct obj,quan)),
MKROOM_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
MKROOM_META(obj_owt,offsetof(struct obj,owt)),
MKROOM_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
MKROOM_META(obj_spe,offsetof(struct obj,spe)),
MKROOM_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
MKROOM_META(obj_otyp,offsetof(struct obj,otyp)),
MKROOM_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
MKROOM_META(vital_mvflags,offsetof(struct mvitals,mvflags)),
MKROOM_META(vital_mvflags_size,sizeof(((struct mvitals*)0)->mvflags)),
MKROOM_META(stair_sx,offsetof(stairway,sx)),
MKROOM_META(stair_sx_size,sizeof(((stairway*)0)->sx)),
MKROOM_META(stair_sy,offsetof(stairway,sy)),
MKROOM_META(stair_sy_size,sizeof(((stairway*)0)->sy)),
MKROOM_META(stair_up,offsetof(stairway,up)),
MKROOM_META(stair_up_size,sizeof(((stairway*)0)->up)),
MKROOM_META(stair_next,offsetof(stairway,next)),
MKROOM_META(stair_next_size,sizeof(((stairway*)0)->next)),
MKROOM_META(shop_name,offsetof(struct shclass,name)),
MKROOM_META(shop_name_size,sizeof(((struct shclass*)0)->name)),
MKROOM_META(shop_prob,offsetof(struct shclass,prob)),
MKROOM_META(shop_prob_size,sizeof(((struct shclass*)0)->prob)),
MKROOM_META(shop_symb,offsetof(struct shclass,symb)),
MKROOM_META(shop_symb_size,sizeof(((struct shclass*)0)->symb)),
MKROOM_META(sym_sym,offsetof(struct class_sym,sym)),
MKROOM_META(sym_sym_size,sizeof(((struct class_sym*)0)->sym)),
MKROOM_META(level_dnum,offsetof(d_level,dnum)),
MKROOM_META(level_dnum_size,sizeof(((d_level*)0)->dnum)),
MKROOM_META(level_dlevel,offsetof(d_level,dlevel)),
MKROOM_META(level_dlevel_size,sizeof(((d_level*)0)->dlevel)),
MKROOM_META(u_uz,offsetof(struct you,uz)),
MKROOM_META(u_uz_size,sizeof(((struct you*)0)->uz)),
MKROOM_META(rooms,offsetof(__typeof__(svr),rooms)),
MKROOM_META(nroom,offsetof(__typeof__(svn),nroom)),
MKROOM_META(nroom_size,sizeof(((__typeof__(svn)*)0)->nroom)),
MKROOM_META(subrooms,offsetof(__typeof__(gs),subrooms)),
MKROOM_META(subrooms_size,sizeof(((__typeof__(gs)*)0)->subrooms)),
MKROOM_META(stairs,offsetof(__typeof__(gs),stairs)),
MKROOM_META(stairs_size,sizeof(((__typeof__(gs)*)0)->stairs)),
MKROOM_META(nsubroom,offsetof(__typeof__(gn),nsubroom)),
MKROOM_META(nsubroom_size,sizeof(((__typeof__(gn)*)0)->nsubroom)),
MKROOM_META(terrain,offsetof(__typeof__(svl),level.locations)),
MKROOM_META(floorObjects,offsetof(__typeof__(svl),level.objects)),
MKROOM_META(floorMonsters,offsetof(__typeof__(svl),level.monsters)),
MKROOM_META(doors,offsetof(__typeof__(svd),doors)),
MKROOM_META(doors_size,sizeof(((__typeof__(svd)*)0)->doors)),
MKROOM_META(astral,offsetof(__typeof__(svd),dungeon_topology.d_astral_level)),
MKROOM_META(astral_size,sizeof(((__typeof__(svd)*)0)->dungeon_topology.d_astral_level)),
MKROOM_META(mvitals,offsetof(__typeof__(svm),mvitals)),
MKROOM_META(wizard,offsetof(__typeof__(flags),debug)),
MKROOM_META(wizard_size,sizeof(((__typeof__(flags)*)0)->debug)),
MKROOM_META(AIR,AIR),
MKROOM_META(ALTAR,ALTAR),
MKROOM_META(AM_SHRINE,AM_SHRINE),
MKROOM_META(ANTHOLE,ANTHOLE),
MKROOM_META(ANY_SHOP,ANY_SHOP),
MKROOM_META(ANY_TYPE,ANY_TYPE),
MKROOM_META(A_NONE,A_NONE),
MKROOM_META(BARRACKS,BARRACKS),
MKROOM_META(BEEHIVE,BEEHIVE),
MKROOM_META(BLCORNER,BLCORNER),
MKROOM_META(BRCORNER,BRCORNER),
MKROOM_META(CHEST,CHEST),
MKROOM_META(CLOUD,CLOUD),
MKROOM_META(COCKNEST,COCKNEST),
MKROOM_META(COLNO,COLNO),
MKROOM_META(CORPSE,CORPSE),
MKROOM_META(CORR,CORR),
MKROOM_META(COURT,COURT),
MKROOM_META(CROSSWALL,CROSSWALL),
MKROOM_META(DBWALL,DBWALL),
MKROOM_META(DOOR,DOOR),
MKROOM_META(DRAWBRIDGE_DOWN,DRAWBRIDGE_DOWN),
MKROOM_META(FILL_NORMAL,FILL_NORMAL),
MKROOM_META(FODDERSHOP,FODDERSHOP),
MKROOM_META(FOOD_CLASS,FOOD_CLASS),
MKROOM_META(FOUNTAIN,FOUNTAIN),
MKROOM_META(FREEING,FREEING),
MKROOM_META(GOLD_PIECE,GOLD_PIECE),
MKROOM_META(GRAVE,GRAVE),
MKROOM_META(G_GONE,G_GONE),
MKROOM_META(HWALL,HWALL),
MKROOM_META(ICE,ICE),
MKROOM_META(IRONBARS,IRONBARS),
MKROOM_META(LADDER,LADDER),
MKROOM_META(LARGE_BOX,LARGE_BOX),
MKROOM_META(LAVAPOOL,LAVAPOOL),
MKROOM_META(LAVAWALL,LAVAWALL),
MKROOM_META(LEPREHALL,LEPREHALL),
MKROOM_META(LUMP_OF_ROYAL_JELLY,LUMP_OF_ROYAL_JELLY),
MKROOM_META(MACE,MACE),
MKROOM_META(MAXNROFROOMS,MAXNROFROOMS),
MKROOM_META(MAXOCLASSES,MAXOCLASSES),
MKROOM_META(MAX_SUBROOMS,MAX_SUBROOMS),
MKROOM_META(MM_ASLEEP,MM_ASLEEP),
MKROOM_META(MM_NOGRP,MM_NOGRP),
MKROOM_META(MORGUE,MORGUE),
MKROOM_META(NHFILE,NHFILE),
MKROOM_META(NON_PM,NON_PM),
MKROOM_META(NO_MM_FLAGS,NO_MM_FLAGS),
MKROOM_META(NUMMONS,NUMMONS),
MKROOM_META(NUM_OBJECTS,NUM_OBJECTS),
MKROOM_META(OROOM,OROOM),
MKROOM_META(PM_BUGBEAR,PM_BUGBEAR),
MKROOM_META(PM_CAPTAIN,PM_CAPTAIN),
MKROOM_META(PM_COCKATRICE,PM_COCKATRICE),
MKROOM_META(PM_DWARF_RULER,PM_DWARF_RULER),
MKROOM_META(PM_ELECTRIC_EEL,PM_ELECTRIC_EEL),
MKROOM_META(PM_ELVEN_MONARCH,PM_ELVEN_MONARCH),
MKROOM_META(PM_FIRE_ANT,PM_FIRE_ANT),
MKROOM_META(PM_GHOST,PM_GHOST),
MKROOM_META(PM_GIANT_ANT,PM_GIANT_ANT),
MKROOM_META(PM_GIANT_EEL,PM_GIANT_EEL),
MKROOM_META(PM_GNOME_RULER,PM_GNOME_RULER),
MKROOM_META(PM_HOBGOBLIN,PM_HOBGOBLIN),
MKROOM_META(PM_HUMAN,PM_HUMAN),
MKROOM_META(PM_KILLER_BEE,PM_KILLER_BEE),
MKROOM_META(PM_LEPRECHAUN,PM_LEPRECHAUN),
MKROOM_META(PM_LIEUTENANT,PM_LIEUTENANT),
MKROOM_META(PM_OGRE_TYRANT,PM_OGRE_TYRANT),
MKROOM_META(PM_PIRANHA,PM_PIRANHA),
MKROOM_META(PM_QUEEN_BEE,PM_QUEEN_BEE),
MKROOM_META(PM_SERGEANT,PM_SERGEANT),
MKROOM_META(PM_SOLDIER,PM_SOLDIER),
MKROOM_META(PM_SOLDIER_ANT,PM_SOLDIER_ANT),
MKROOM_META(PM_WRAITH,PM_WRAITH),
MKROOM_META(POOL,POOL),
MKROOM_META(RANDOM_CLASS,RANDOM_CLASS),
MKROOM_META(READING,READING),
MKROOM_META(ROOM,ROOM),
MKROOM_META(ROOMOFFSET,ROOMOFFSET),
MKROOM_META(ROWNO,ROWNO),
MKROOM_META(SDOOR,SDOOR),
MKROOM_META(SHOPBASE,SHOPBASE),
MKROOM_META(SINK,SINK),
MKROOM_META(SPBOOK_CLASS,SPBOOK_CLASS),
MKROOM_META(STAIRS,STAIRS),
MKROOM_META(STATUE,STATUE),
MKROOM_META(STONE,STONE),
MKROOM_META(SWAMP,SWAMP),
MKROOM_META(S_CENTAUR,S_CENTAUR),
MKROOM_META(S_DEMON,S_DEMON),
MKROOM_META(S_DRAGON,S_DRAGON),
MKROOM_META(S_FUNGUS,S_FUNGUS),
MKROOM_META(S_GIANT,S_GIANT),
MKROOM_META(S_GNOME,S_GNOME),
MKROOM_META(S_KOBOLD,S_KOBOLD),
MKROOM_META(S_ORC,S_ORC),
MKROOM_META(S_TROLL,S_TROLL),
MKROOM_META(S_VAMPIRE,S_VAMPIRE),
MKROOM_META(S_ZOMBIE,S_ZOMBIE),
MKROOM_META(S_air,S_air),
MKROOM_META(S_altar,S_altar),
MKROOM_META(S_bars,S_bars),
MKROOM_META(S_blcorn,S_blcorn),
MKROOM_META(S_brcorn,S_brcorn),
MKROOM_META(S_cloud,S_cloud),
MKROOM_META(S_corr,S_corr),
MKROOM_META(S_crwall,S_crwall),
MKROOM_META(S_darkroom,S_darkroom),
MKROOM_META(S_dnladder,S_dnladder),
MKROOM_META(S_dnstair,S_dnstair),
MKROOM_META(S_fountain,S_fountain),
MKROOM_META(S_grave,S_grave),
MKROOM_META(S_hcdbridge,S_hcdbridge),
MKROOM_META(S_hcdoor,S_hcdoor),
MKROOM_META(S_hodbridge,S_hodbridge),
MKROOM_META(S_hodoor,S_hodoor),
MKROOM_META(S_hwall,S_hwall),
MKROOM_META(S_ice,S_ice),
MKROOM_META(S_lava,S_lava),
MKROOM_META(S_lavawall,S_lavawall),
MKROOM_META(S_litcorr,S_litcorr),
MKROOM_META(S_ndoor,S_ndoor),
MKROOM_META(S_pool,S_pool),
MKROOM_META(S_room,S_room),
MKROOM_META(S_sink,S_sink),
MKROOM_META(S_stone,S_stone),
MKROOM_META(S_tdwall,S_tdwall),
MKROOM_META(S_throne,S_throne),
MKROOM_META(S_tlcorn,S_tlcorn),
MKROOM_META(S_tlwall,S_tlwall),
MKROOM_META(S_trcorn,S_trcorn),
MKROOM_META(S_tree,S_tree),
MKROOM_META(S_trwall,S_trwall),
MKROOM_META(S_tuwall,S_tuwall),
MKROOM_META(S_upladder,S_upladder),
MKROOM_META(S_upstair,S_upstair),
MKROOM_META(S_vcdbridge,S_vcdbridge),
MKROOM_META(S_vcdoor,S_vcdoor),
MKROOM_META(S_vodbridge,S_vodbridge),
MKROOM_META(S_vodoor,S_vodoor),
MKROOM_META(S_vwall,S_vwall),
MKROOM_META(S_water,S_water),
MKROOM_META(TDWALL,TDWALL),
MKROOM_META(TEMPLE,TEMPLE),
MKROOM_META(THRONE,THRONE),
MKROOM_META(TLCORNER,TLCORNER),
MKROOM_META(TLWALL,TLWALL),
MKROOM_META(TRCORNER,TRCORNER),
MKROOM_META(TREE,TREE),
MKROOM_META(TRWALL,TRWALL),
MKROOM_META(TUWALL,TUWALL),
MKROOM_META(VWALL,VWALL),
MKROOM_META(WAND_CLASS,WAND_CLASS),
MKROOM_META(WATER,WATER),
MKROOM_META(WRITING,WRITING),
MKROOM_META(ZOO,ZOO),
#ifdef SFCTOOL
MKROOM_META(config_SFCTOOL,1),
#else
MKROOM_META(config_SFCTOOL,0),
#endif
#ifdef SPECIALIZATION
MKROOM_META(config_SPECIALIZATION,1),
#else
MKROOM_META(config_SPECIALIZATION,0),
#endif
};
#undef MKROOM_META
_Static_assert(sizeof(((struct mkroom*)0)->lx)==2,"room_lx width");
_Static_assert(((__typeof__(((struct mkroom*)0)->lx))-1 < 0),"room_lx signedness");
_Static_assert(sizeof(((struct mkroom*)0)->hx)==2,"room_hx width");
_Static_assert(((__typeof__(((struct mkroom*)0)->hx))-1 < 0),"room_hx signedness");
_Static_assert(sizeof(((struct mkroom*)0)->ly)==2,"room_ly width");
_Static_assert(((__typeof__(((struct mkroom*)0)->ly))-1 < 0),"room_ly signedness");
_Static_assert(sizeof(((struct mkroom*)0)->hy)==2,"room_hy width");
_Static_assert(((__typeof__(((struct mkroom*)0)->hy))-1 < 0),"room_hy signedness");
_Static_assert(sizeof(((struct mkroom*)0)->rtype)==1,"room_rtype width");
_Static_assert(((__typeof__(((struct mkroom*)0)->rtype))-1 < 0),"room_rtype signedness");
_Static_assert(sizeof(((struct mkroom*)0)->orig_rtype)==1,"room_orig_rtype width");
_Static_assert(((__typeof__(((struct mkroom*)0)->orig_rtype))-1 < 0),"room_orig_rtype signedness");
_Static_assert(sizeof(((struct mkroom*)0)->rlit)==1,"room_rlit width");
_Static_assert(((__typeof__(((struct mkroom*)0)->rlit))-1 < 0),"room_rlit signedness");
_Static_assert(sizeof(((struct mkroom*)0)->needfill)==1,"room_needfill width");
_Static_assert(((__typeof__(((struct mkroom*)0)->needfill))-1 < 0),"room_needfill signedness");
_Static_assert(sizeof(((struct mkroom*)0)->needjoining)==1,"room_needjoining width");
_Static_assert(((__typeof__(((struct mkroom*)0)->needjoining))-1 < 0),"room_needjoining signedness");
_Static_assert(sizeof(((struct mkroom*)0)->doorct)==1,"room_doorct width");
_Static_assert(((__typeof__(((struct mkroom*)0)->doorct))-1 < 0),"room_doorct signedness");
_Static_assert(sizeof(((struct mkroom*)0)->nsubrooms)==1,"room_nsubrooms width");
_Static_assert(((__typeof__(((struct mkroom*)0)->nsubrooms))-1 < 0),"room_nsubrooms signedness");
_Static_assert(sizeof(((struct mkroom*)0)->irregular)==1,"room_irregular width");
_Static_assert(((__typeof__(((struct mkroom*)0)->irregular))-1 < 0),"room_irregular signedness");
_Static_assert(sizeof(((struct mkroom*)0)->roomnoidx)==1,"room_roomnoidx width");
_Static_assert(((__typeof__(((struct mkroom*)0)->roomnoidx))-1 < 0),"room_roomnoidx signedness");
_Static_assert(sizeof(((struct mkroom*)0)->fdoor)==4,"room_fdoor width");
_Static_assert(((__typeof__(((struct mkroom*)0)->fdoor))-1 < 0),"room_fdoor signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"coord_x width");
_Static_assert(((__typeof__(((coord*)0)->x))-1 < 0),"coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"coord_y width");
_Static_assert(((__typeof__(((coord*)0)->y))-1 < 0),"coord_y signedness");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"terrain_typ width");
_Static_assert(((__typeof__(((struct rm*)0)->typ))-1 < 0),"terrain_typ signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"obj_quan width");
_Static_assert(((__typeof__(((struct obj*)0)->quan))-1 < 0),"obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"obj_owt width");
_Static_assert(((__typeof__(((struct obj*)0)->owt))-1 > 0),"obj_owt signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"vital_mvflags width");
_Static_assert(((__typeof__(((struct mvitals*)0)->mvflags))-1 > 0),"vital_mvflags signedness");
_Static_assert(sizeof(((stairway*)0)->sx)==2,"stair_sx width");
_Static_assert(((__typeof__(((stairway*)0)->sx))-1 < 0),"stair_sx signedness");
_Static_assert(sizeof(((stairway*)0)->sy)==2,"stair_sy width");
_Static_assert(((__typeof__(((stairway*)0)->sy))-1 < 0),"stair_sy signedness");
_Static_assert(sizeof(((stairway*)0)->up)==1,"stair_up width");
_Static_assert(((__typeof__(((stairway*)0)->up))-1 < 0),"stair_up signedness");
_Static_assert(sizeof(((stairway*)0)->next)==8,"stair_next width");
_Static_assert(sizeof(((struct shclass*)0)->name)==8,"shop_name width");
_Static_assert(sizeof(((struct shclass*)0)->prob)==4,"shop_prob width");
_Static_assert(((__typeof__(((struct shclass*)0)->prob))-1 < 0),"shop_prob signedness");
_Static_assert(sizeof(((struct shclass*)0)->symb)==1,"shop_symb width");
_Static_assert(((__typeof__(((struct shclass*)0)->symb))-1 < 0),"shop_symb signedness");
_Static_assert(sizeof(((struct class_sym*)0)->sym)==1,"sym_sym width");
_Static_assert(((__typeof__(((struct class_sym*)0)->sym))-1 < 0),"sym_sym signedness");
_Static_assert(sizeof(((d_level*)0)->dnum)==1,"level_dnum width");
_Static_assert(((__typeof__(((d_level*)0)->dnum))-1 < 0),"level_dnum signedness");
_Static_assert(sizeof(((d_level*)0)->dlevel)==1,"level_dlevel width");
_Static_assert(((__typeof__(((d_level*)0)->dlevel))-1 < 0),"level_dlevel signedness");
_Static_assert(sizeof(((struct you*)0)->uz)==2,"u_uz width");
_Static_assert(sizeof(((__typeof__(svn)*)0)->nroom)==4,"nroom width");
_Static_assert(((__typeof__(((__typeof__(svn)*)0)->nroom))-1 < 0),"nroom signedness");
_Static_assert(sizeof(((__typeof__(gs)*)0)->subrooms)==8,"subrooms width");
_Static_assert(sizeof(((__typeof__(gs)*)0)->stairs)==8,"stairs width");
_Static_assert(sizeof(((__typeof__(gn)*)0)->nsubroom)==4,"nsubroom width");
_Static_assert(((__typeof__(((__typeof__(gn)*)0)->nsubroom))-1 < 0),"nsubroom signedness");
_Static_assert(sizeof(((__typeof__(svd)*)0)->doors)==8,"doors width");
_Static_assert(sizeof(((__typeof__(svd)*)0)->dungeon_topology.d_astral_level)==2,"astral width");
_Static_assert(sizeof(((__typeof__(flags)*)0)->debug)==1,"wizard width");
_Static_assert(((__typeof__(((__typeof__(flags)*)0)->debug))-1 < 0),"wizard signedness");
size_t probe_context_size(void){return sizeof(struct mkroom);}
int probe_layout_count(void){return sizeof mkroom_layout/sizeof mkroom_layout[0];}
const char*probe_layout_name(int i){return mkroom_layout[i].name;}
size_t probe_layout_value(int i){return mkroom_layout[i].value;}
#endif
