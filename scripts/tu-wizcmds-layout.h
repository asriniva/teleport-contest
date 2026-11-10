#ifndef TELEPORT_WIZCMDS_LAYOUT_H
#define TELEPORT_WIZCMDS_LAYOUT_H
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#if !defined(DEBUG) || !defined(ENHANCED_SYMBOLS) || !defined(DEBUG_MIGRATING_MONS)
#error Review changed WIZCMDS configured profile
#endif
struct wizcmds_meta {const char*name;uint64_t value;};
#define WIZCMDS_META(k,v) {#k,(uint64_t)(v)}
static const struct wizcmds_meta wizcmds_layout[]={
WIZCMDS_META(pointerSize,sizeof(void*)),WIZCMDS_META(longSize,sizeof(long)),WIZCMDS_META(intSize,sizeof(int)),WIZCMDS_META(charSigned,((char)-1<0)),WIZCMDS_META(littleEndian,__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__),
WIZCMDS_META(AD_PHYS,AD_PHYS),
WIZCMDS_META(constwidth_AD_PHYS,sizeof(AD_PHYS)),
WIZCMDS_META(constsigned_AD_PHYS,((__typeof__(AD_PHYS))-1)<0),
WIZCMDS_META(ARM,ARM),
WIZCMDS_META(constwidth_ARM,sizeof(ARM)),
WIZCMDS_META(constsigned_ARM,((__typeof__(ARM))-1)<0),
WIZCMDS_META(ARTICLE_A,ARTICLE_A),
WIZCMDS_META(constwidth_ARTICLE_A,sizeof(ARTICLE_A)),
WIZCMDS_META(constsigned_ARTICLE_A,((__typeof__(ARTICLE_A))-1)<0),
WIZCMDS_META(ARTICLE_THE,ARTICLE_THE),
WIZCMDS_META(constwidth_ARTICLE_THE,sizeof(ARTICLE_THE)),
WIZCMDS_META(constsigned_ARTICLE_THE,((__typeof__(ARTICLE_THE))-1)<0),
WIZCMDS_META(ARTICLE_YOUR,ARTICLE_YOUR),
WIZCMDS_META(constwidth_ARTICLE_YOUR,sizeof(ARTICLE_YOUR)),
WIZCMDS_META(constsigned_ARTICLE_YOUR,((__typeof__(ARTICLE_YOUR))-1)<0),
WIZCMDS_META(ATR_NONE,ATR_NONE),
WIZCMDS_META(constwidth_ATR_NONE,sizeof(ATR_NONE)),
WIZCMDS_META(constsigned_ATR_NONE,((__typeof__(ATR_NONE))-1)<0),
WIZCMDS_META(BLINDED,BLINDED),
WIZCMDS_META(constwidth_BLINDED,sizeof(BLINDED)),
WIZCMDS_META(constsigned_BLINDED,((__typeof__(BLINDED))-1)<0),
WIZCMDS_META(BUFSZ,BUFSZ),
WIZCMDS_META(constwidth_BUFSZ,sizeof(BUFSZ)),
WIZCMDS_META(constsigned_BUFSZ,((__typeof__(BUFSZ))-1)<0),
WIZCMDS_META(COLBUFSZ,COLBUFSZ),
WIZCMDS_META(constwidth_COLBUFSZ,sizeof(COLBUFSZ)),
WIZCMDS_META(constsigned_COLBUFSZ,((__typeof__(COLBUFSZ))-1)<0),
WIZCMDS_META(COLNO,COLNO),
WIZCMDS_META(constwidth_COLNO,sizeof(COLNO)),
WIZCMDS_META(constsigned_COLNO,((__typeof__(COLNO))-1)<0),
WIZCMDS_META(CONFUSION,CONFUSION),
WIZCMDS_META(constwidth_CONFUSION,sizeof(CONFUSION)),
WIZCMDS_META(constsigned_CONFUSION,((__typeof__(CONFUSION))-1)<0),
WIZCMDS_META(CORPSE,CORPSE),
WIZCMDS_META(constwidth_CORPSE,sizeof(CORPSE)),
WIZCMDS_META(constsigned_CORPSE,((__typeof__(CORPSE))-1)<0),
WIZCMDS_META(CORR,CORR),
WIZCMDS_META(constwidth_CORR,sizeof(CORR)),
WIZCMDS_META(constsigned_CORR,((__typeof__(CORR))-1)<0),
WIZCMDS_META(COULD_SEE,COULD_SEE),
WIZCMDS_META(constwidth_COULD_SEE,sizeof(COULD_SEE)),
WIZCMDS_META(constsigned_COULD_SEE,((__typeof__(COULD_SEE))-1)<0),
WIZCMDS_META(DBWALL,DBWALL),
WIZCMDS_META(constwidth_DBWALL,sizeof(DBWALL)),
WIZCMDS_META(constsigned_DBWALL,((__typeof__(DBWALL))-1)<0),
WIZCMDS_META(DEAF,DEAF),
WIZCMDS_META(constwidth_DEAF,sizeof(DEAF)),
WIZCMDS_META(constsigned_DEAF,((__typeof__(DEAF))-1)<0),
WIZCMDS_META(DIED,DIED),
WIZCMDS_META(constwidth_DIED,sizeof(DIED)),
WIZCMDS_META(constsigned_DIED,((__typeof__(DIED))-1)<0),
WIZCMDS_META(DOOR,DOOR),
WIZCMDS_META(constwidth_DOOR,sizeof(DOOR)),
WIZCMDS_META(constsigned_DOOR,((__typeof__(DOOR))-1)<0),
WIZCMDS_META(ECMD_CANCEL,ECMD_CANCEL),
WIZCMDS_META(constwidth_ECMD_CANCEL,sizeof(ECMD_CANCEL)),
WIZCMDS_META(constsigned_ECMD_CANCEL,((__typeof__(ECMD_CANCEL))-1)<0),
WIZCMDS_META(ECMD_OK,ECMD_OK),
WIZCMDS_META(constwidth_ECMD_OK,sizeof(ECMD_OK)),
WIZCMDS_META(constsigned_ECMD_OK,((__typeof__(ECMD_OK))-1)<0),
WIZCMDS_META(FALSE,FALSE),
WIZCMDS_META(constwidth_FALSE,sizeof(FALSE)),
WIZCMDS_META(constsigned_FALSE,((__typeof__(FALSE))-1)<0),
WIZCMDS_META(FIRE_RES,FIRE_RES),
WIZCMDS_META(constwidth_FIRE_RES,sizeof(FIRE_RES)),
WIZCMDS_META(constsigned_FIRE_RES,((__typeof__(FIRE_RES))-1)<0),
WIZCMDS_META(FIRST_OBJECT,FIRST_OBJECT),
WIZCMDS_META(constwidth_FIRST_OBJECT,sizeof(FIRST_OBJECT)),
WIZCMDS_META(constsigned_FIRST_OBJECT,((__typeof__(FIRST_OBJECT))-1)<0),
WIZCMDS_META(FLYING,FLYING),
WIZCMDS_META(constwidth_FLYING,sizeof(FLYING)),
WIZCMDS_META(constsigned_FLYING,((__typeof__(FLYING))-1)<0),
WIZCMDS_META(GLIB,GLIB),
WIZCMDS_META(constwidth_GLIB,sizeof(GLIB)),
WIZCMDS_META(constsigned_GLIB,((__typeof__(GLIB))-1)<0),
WIZCMDS_META(GLYPH_BODY_OFF,GLYPH_BODY_OFF),
WIZCMDS_META(constwidth_GLYPH_BODY_OFF,sizeof(GLYPH_BODY_OFF)),
WIZCMDS_META(constsigned_GLYPH_BODY_OFF,((__typeof__(GLYPH_BODY_OFF))-1)<0),
WIZCMDS_META(GLYPH_BODY_PILETOP_OFF,GLYPH_BODY_PILETOP_OFF),
WIZCMDS_META(constwidth_GLYPH_BODY_PILETOP_OFF,sizeof(GLYPH_BODY_PILETOP_OFF)),
WIZCMDS_META(constsigned_GLYPH_BODY_PILETOP_OFF,((__typeof__(GLYPH_BODY_PILETOP_OFF))-1)<0),
WIZCMDS_META(GLYPH_CMAP_C_OFF,GLYPH_CMAP_C_OFF),
WIZCMDS_META(constwidth_GLYPH_CMAP_C_OFF,sizeof(GLYPH_CMAP_C_OFF)),
WIZCMDS_META(constsigned_GLYPH_CMAP_C_OFF,((__typeof__(GLYPH_CMAP_C_OFF))-1)<0),
WIZCMDS_META(GLYPH_CMAP_STONE_OFF,GLYPH_CMAP_STONE_OFF),
WIZCMDS_META(constwidth_GLYPH_CMAP_STONE_OFF,sizeof(GLYPH_CMAP_STONE_OFF)),
WIZCMDS_META(constsigned_GLYPH_CMAP_STONE_OFF,((__typeof__(GLYPH_CMAP_STONE_OFF))-1)<0),
WIZCMDS_META(GLYPH_DETECT_FEM_OFF,GLYPH_DETECT_FEM_OFF),
WIZCMDS_META(constwidth_GLYPH_DETECT_FEM_OFF,sizeof(GLYPH_DETECT_FEM_OFF)),
WIZCMDS_META(constsigned_GLYPH_DETECT_FEM_OFF,((__typeof__(GLYPH_DETECT_FEM_OFF))-1)<0),
WIZCMDS_META(GLYPH_DETECT_MALE_OFF,GLYPH_DETECT_MALE_OFF),
WIZCMDS_META(constwidth_GLYPH_DETECT_MALE_OFF,sizeof(GLYPH_DETECT_MALE_OFF)),
WIZCMDS_META(constsigned_GLYPH_DETECT_MALE_OFF,((__typeof__(GLYPH_DETECT_MALE_OFF))-1)<0),
WIZCMDS_META(GLYPH_INVISIBLE,GLYPH_INVISIBLE),
WIZCMDS_META(constwidth_GLYPH_INVISIBLE,sizeof(GLYPH_INVISIBLE)),
WIZCMDS_META(constsigned_GLYPH_INVISIBLE,((__typeof__(GLYPH_INVISIBLE))-1)<0),
WIZCMDS_META(GLYPH_MON_FEM_OFF,GLYPH_MON_FEM_OFF),
WIZCMDS_META(constwidth_GLYPH_MON_FEM_OFF,sizeof(GLYPH_MON_FEM_OFF)),
WIZCMDS_META(constsigned_GLYPH_MON_FEM_OFF,((__typeof__(GLYPH_MON_FEM_OFF))-1)<0),
WIZCMDS_META(GLYPH_MON_MALE_OFF,GLYPH_MON_MALE_OFF),
WIZCMDS_META(constwidth_GLYPH_MON_MALE_OFF,sizeof(GLYPH_MON_MALE_OFF)),
WIZCMDS_META(constsigned_GLYPH_MON_MALE_OFF,((__typeof__(GLYPH_MON_MALE_OFF))-1)<0),
WIZCMDS_META(GLYPH_OBJ_OFF,GLYPH_OBJ_OFF),
WIZCMDS_META(constwidth_GLYPH_OBJ_OFF,sizeof(GLYPH_OBJ_OFF)),
WIZCMDS_META(constsigned_GLYPH_OBJ_OFF,((__typeof__(GLYPH_OBJ_OFF))-1)<0),
WIZCMDS_META(GLYPH_OBJ_PILETOP_OFF,GLYPH_OBJ_PILETOP_OFF),
WIZCMDS_META(constwidth_GLYPH_OBJ_PILETOP_OFF,sizeof(GLYPH_OBJ_PILETOP_OFF)),
WIZCMDS_META(constsigned_GLYPH_OBJ_PILETOP_OFF,((__typeof__(GLYPH_OBJ_PILETOP_OFF))-1)<0),
WIZCMDS_META(GLYPH_PET_FEM_OFF,GLYPH_PET_FEM_OFF),
WIZCMDS_META(constwidth_GLYPH_PET_FEM_OFF,sizeof(GLYPH_PET_FEM_OFF)),
WIZCMDS_META(constsigned_GLYPH_PET_FEM_OFF,((__typeof__(GLYPH_PET_FEM_OFF))-1)<0),
WIZCMDS_META(GLYPH_PET_MALE_OFF,GLYPH_PET_MALE_OFF),
WIZCMDS_META(constwidth_GLYPH_PET_MALE_OFF,sizeof(GLYPH_PET_MALE_OFF)),
WIZCMDS_META(constsigned_GLYPH_PET_MALE_OFF,((__typeof__(GLYPH_PET_MALE_OFF))-1)<0),
WIZCMDS_META(GLYPH_RIDDEN_FEM_OFF,GLYPH_RIDDEN_FEM_OFF),
WIZCMDS_META(constwidth_GLYPH_RIDDEN_FEM_OFF,sizeof(GLYPH_RIDDEN_FEM_OFF)),
WIZCMDS_META(constsigned_GLYPH_RIDDEN_FEM_OFF,((__typeof__(GLYPH_RIDDEN_FEM_OFF))-1)<0),
WIZCMDS_META(GLYPH_RIDDEN_MALE_OFF,GLYPH_RIDDEN_MALE_OFF),
WIZCMDS_META(constwidth_GLYPH_RIDDEN_MALE_OFF,sizeof(GLYPH_RIDDEN_MALE_OFF)),
WIZCMDS_META(constsigned_GLYPH_RIDDEN_MALE_OFF,((__typeof__(GLYPH_RIDDEN_MALE_OFF))-1)<0),
WIZCMDS_META(GLYPH_STATUE_FEM_OFF,GLYPH_STATUE_FEM_OFF),
WIZCMDS_META(constwidth_GLYPH_STATUE_FEM_OFF,sizeof(GLYPH_STATUE_FEM_OFF)),
WIZCMDS_META(constsigned_GLYPH_STATUE_FEM_OFF,((__typeof__(GLYPH_STATUE_FEM_OFF))-1)<0),
WIZCMDS_META(GLYPH_STATUE_FEM_PILETOP_OFF,GLYPH_STATUE_FEM_PILETOP_OFF),
WIZCMDS_META(constwidth_GLYPH_STATUE_FEM_PILETOP_OFF,sizeof(GLYPH_STATUE_FEM_PILETOP_OFF)),
WIZCMDS_META(constsigned_GLYPH_STATUE_FEM_PILETOP_OFF,((__typeof__(GLYPH_STATUE_FEM_PILETOP_OFF))-1)<0),
WIZCMDS_META(GLYPH_STATUE_MALE_OFF,GLYPH_STATUE_MALE_OFF),
WIZCMDS_META(constwidth_GLYPH_STATUE_MALE_OFF,sizeof(GLYPH_STATUE_MALE_OFF)),
WIZCMDS_META(constsigned_GLYPH_STATUE_MALE_OFF,((__typeof__(GLYPH_STATUE_MALE_OFF))-1)<0),
WIZCMDS_META(GLYPH_STATUE_MALE_PILETOP_OFF,GLYPH_STATUE_MALE_PILETOP_OFF),
WIZCMDS_META(constwidth_GLYPH_STATUE_MALE_PILETOP_OFF,sizeof(GLYPH_STATUE_MALE_PILETOP_OFF)),
WIZCMDS_META(constsigned_GLYPH_STATUE_MALE_PILETOP_OFF,((__typeof__(GLYPH_STATUE_MALE_PILETOP_OFF))-1)<0),
WIZCMDS_META(GLYPH_ZAP_OFF,GLYPH_ZAP_OFF),
WIZCMDS_META(constwidth_GLYPH_ZAP_OFF,sizeof(GLYPH_ZAP_OFF)),
WIZCMDS_META(constsigned_GLYPH_ZAP_OFF,((__typeof__(GLYPH_ZAP_OFF))-1)<0),
WIZCMDS_META(G_EXTINCT,G_EXTINCT),
WIZCMDS_META(constwidth_G_EXTINCT,sizeof(G_EXTINCT)),
WIZCMDS_META(constsigned_G_EXTINCT,((__typeof__(G_EXTINCT))-1)<0),
WIZCMDS_META(G_UNIQ,G_UNIQ),
WIZCMDS_META(constwidth_G_UNIQ,sizeof(G_UNIQ)),
WIZCMDS_META(constsigned_G_UNIQ,((__typeof__(G_UNIQ))-1)<0),
WIZCMDS_META(HALLUC,HALLUC),
WIZCMDS_META(constwidth_HALLUC,sizeof(HALLUC)),
WIZCMDS_META(constsigned_HALLUC,((__typeof__(HALLUC))-1)<0),
WIZCMDS_META(HALLUC_RES,HALLUC_RES),
WIZCMDS_META(constwidth_HALLUC_RES,sizeof(HALLUC_RES)),
WIZCMDS_META(constsigned_HALLUC_RES,((__typeof__(HALLUC_RES))-1)<0),
WIZCMDS_META(IN_SIGHT,IN_SIGHT),
WIZCMDS_META(constwidth_IN_SIGHT,sizeof(IN_SIGHT)),
WIZCMDS_META(constsigned_IN_SIGHT,((__typeof__(IN_SIGHT))-1)<0),
WIZCMDS_META(KILLED_BY,KILLED_BY),
WIZCMDS_META(constwidth_KILLED_BY,sizeof(KILLED_BY)),
WIZCMDS_META(constsigned_KILLED_BY,((__typeof__(KILLED_BY))-1)<0),
WIZCMDS_META(LEVITATION,LEVITATION),
WIZCMDS_META(constwidth_LEVITATION,sizeof(LEVITATION)),
WIZCMDS_META(constsigned_LEVITATION,((__typeof__(LEVITATION))-1)<0),
WIZCMDS_META(LONG_MAX,LONG_MAX),
WIZCMDS_META(constwidth_LONG_MAX,sizeof(LONG_MAX)),
WIZCMDS_META(constsigned_LONG_MAX,((__typeof__(LONG_MAX))-1)<0),
WIZCMDS_META(LOW_PM,LOW_PM),
WIZCMDS_META(constwidth_LOW_PM,sizeof(LOW_PM)),
WIZCMDS_META(constsigned_LOW_PM,((__typeof__(LOW_PM))-1)<0),
WIZCMDS_META(M2_UNDEAD,M2_UNDEAD),
WIZCMDS_META(constwidth_M2_UNDEAD,sizeof(M2_UNDEAD)),
WIZCMDS_META(constsigned_M2_UNDEAD,((__typeof__(M2_UNDEAD))-1)<0),
WIZCMDS_META(MAXOCLASSES,MAXOCLASSES),
WIZCMDS_META(constwidth_MAXOCLASSES,sizeof(MAXOCLASSES)),
WIZCMDS_META(constsigned_MAXOCLASSES,((__typeof__(MAXOCLASSES))-1)<0),
WIZCMDS_META(MAXULEV,MAXULEV),
WIZCMDS_META(constwidth_MAXULEV,sizeof(MAXULEV)),
WIZCMDS_META(constsigned_MAXULEV,((__typeof__(MAXULEV))-1)<0),
WIZCMDS_META(MAX_GLYPH,MAX_GLYPH),
WIZCMDS_META(constwidth_MAX_GLYPH,sizeof(MAX_GLYPH)),
WIZCMDS_META(constsigned_MAX_GLYPH,((__typeof__(MAX_GLYPH))-1)<0),
WIZCMDS_META(MENU_BEHAVE_STANDARD,MENU_BEHAVE_STANDARD),
WIZCMDS_META(constwidth_MENU_BEHAVE_STANDARD,sizeof(MENU_BEHAVE_STANDARD)),
WIZCMDS_META(constsigned_MENU_BEHAVE_STANDARD,((__typeof__(MENU_BEHAVE_STANDARD))-1)<0),
WIZCMDS_META(MENU_ITEMFLAGS_NONE,MENU_ITEMFLAGS_NONE),
WIZCMDS_META(constwidth_MENU_ITEMFLAGS_NONE,sizeof(MENU_ITEMFLAGS_NONE)),
WIZCMDS_META(constsigned_MENU_ITEMFLAGS_NONE,((__typeof__(MENU_ITEMFLAGS_NONE))-1)<0),
WIZCMDS_META(MIGR_EXACT_XY,MIGR_EXACT_XY),
WIZCMDS_META(constwidth_MIGR_EXACT_XY,sizeof(MIGR_EXACT_XY)),
WIZCMDS_META(constsigned_MIGR_EXACT_XY,((__typeof__(MIGR_EXACT_XY))-1)<0),
WIZCMDS_META(MIGR_RANDOM,MIGR_RANDOM),
WIZCMDS_META(constwidth_MIGR_RANDOM,sizeof(MIGR_RANDOM)),
WIZCMDS_META(constsigned_MIGR_RANDOM,((__typeof__(MIGR_RANDOM))-1)<0),
WIZCMDS_META(MM_NOMSG,MM_NOMSG),
WIZCMDS_META(constwidth_MM_NOMSG,sizeof(MM_NOMSG)),
WIZCMDS_META(constsigned_MM_NOMSG,((__typeof__(MM_NOMSG))-1)<0),
WIZCMDS_META(MON_ENDGAME_MIGR,MON_ENDGAME_MIGR),
WIZCMDS_META(constwidth_MON_ENDGAME_MIGR,sizeof(MON_ENDGAME_MIGR)),
WIZCMDS_META(constsigned_MON_ENDGAME_MIGR,((__typeof__(MON_ENDGAME_MIGR))-1)<0),
WIZCMDS_META(MON_LIMBO,MON_LIMBO),
WIZCMDS_META(constwidth_MON_LIMBO,sizeof(MON_LIMBO)),
WIZCMDS_META(constsigned_MON_LIMBO,((__typeof__(MON_LIMBO))-1)<0),
WIZCMDS_META(MON_MIGRATING,MON_MIGRATING),
WIZCMDS_META(constwidth_MON_MIGRATING,sizeof(MON_MIGRATING)),
WIZCMDS_META(constsigned_MON_MIGRATING,((__typeof__(MON_MIGRATING))-1)<0),
WIZCMDS_META(MON_OFFMAP,MON_OFFMAP),
WIZCMDS_META(constwidth_MON_OFFMAP,sizeof(MON_OFFMAP)),
WIZCMDS_META(constsigned_MON_OFFMAP,((__typeof__(MON_OFFMAP))-1)<0),
WIZCMDS_META(NEUTRAL,NEUTRAL),
WIZCMDS_META(constwidth_NEUTRAL,sizeof(NEUTRAL)),
WIZCMDS_META(constsigned_NEUTRAL,((__typeof__(NEUTRAL))-1)<0),
WIZCMDS_META(NHL_SB_DEBUGGING,NHL_SB_DEBUGGING),
WIZCMDS_META(constwidth_NHL_SB_DEBUGGING,sizeof(NHL_SB_DEBUGGING)),
WIZCMDS_META(constsigned_NHL_SB_DEBUGGING,((__typeof__(NHL_SB_DEBUGGING))-1)<0),
WIZCMDS_META(NHL_SB_SAFE,NHL_SB_SAFE),
WIZCMDS_META(constwidth_NHL_SB_SAFE,sizeof(NHL_SB_SAFE)),
WIZCMDS_META(constsigned_NHL_SB_SAFE,((__typeof__(NHL_SB_SAFE))-1)<0),
WIZCMDS_META(NHW_MENU,NHW_MENU),
WIZCMDS_META(constwidth_NHW_MENU,sizeof(NHW_MENU)),
WIZCMDS_META(constsigned_NHW_MENU,((__typeof__(NHW_MENU))-1)<0),
WIZCMDS_META(NHW_TEXT,NHW_TEXT),
WIZCMDS_META(constwidth_NHW_TEXT,sizeof(NHW_TEXT)),
WIZCMDS_META(constsigned_NHW_TEXT,((__typeof__(NHW_TEXT))-1)<0),
WIZCMDS_META(NO_COLOR,NO_COLOR),
WIZCMDS_META(constwidth_NO_COLOR,sizeof(NO_COLOR)),
WIZCMDS_META(constsigned_NO_COLOR,((__typeof__(NO_COLOR))-1)<0),
WIZCMDS_META(NO_GLYPH,NO_GLYPH),
WIZCMDS_META(constwidth_NO_GLYPH,sizeof(NO_GLYPH)),
WIZCMDS_META(constsigned_NO_GLYPH,((__typeof__(NO_GLYPH))-1)<0),
WIZCMDS_META(NUMMONS,NUMMONS),
WIZCMDS_META(constwidth_NUMMONS,sizeof(NUMMONS)),
WIZCMDS_META(constsigned_NUMMONS,((__typeof__(NUMMONS))-1)<0),
WIZCMDS_META(NUM_OBJECTS,NUM_OBJECTS),
WIZCMDS_META(constwidth_NUM_OBJECTS,sizeof(NUM_OBJECTS)),
WIZCMDS_META(constsigned_NUM_OBJECTS,((__typeof__(NUM_OBJECTS))-1)<0),
WIZCMDS_META(NUM_ZAP,NUM_ZAP),
WIZCMDS_META(constwidth_NUM_ZAP,sizeof(NUM_ZAP)),
WIZCMDS_META(constsigned_NUM_ZAP,((__typeof__(NUM_ZAP))-1)<0),
WIZCMDS_META(PICK_ANY,PICK_ANY),
WIZCMDS_META(constwidth_PICK_ANY,sizeof(PICK_ANY)),
WIZCMDS_META(constsigned_PICK_ANY,((__typeof__(PICK_ANY))-1)<0),
WIZCMDS_META(PICK_NONE,PICK_NONE),
WIZCMDS_META(constwidth_PICK_NONE,sizeof(PICK_NONE)),
WIZCMDS_META(constsigned_PICK_NONE,((__typeof__(PICK_NONE))-1)<0),
WIZCMDS_META(PM_GRID_BUG,PM_GRID_BUG),
WIZCMDS_META(constwidth_PM_GRID_BUG,sizeof(PM_GRID_BUG)),
WIZCMDS_META(constsigned_PM_GRID_BUG,((__typeof__(PM_GRID_BUG))-1)<0),
WIZCMDS_META(PM_MANES,PM_MANES),
WIZCMDS_META(constwidth_PM_MANES,sizeof(PM_MANES)),
WIZCMDS_META(constsigned_PM_MANES,((__typeof__(PM_MANES))-1)<0),
WIZCMDS_META(PM_SAMURAI,PM_SAMURAI),
WIZCMDS_META(constwidth_PM_SAMURAI,sizeof(PM_SAMURAI)),
WIZCMDS_META(constsigned_PM_SAMURAI,((__typeof__(PM_SAMURAI))-1)<0),
WIZCMDS_META(POLY_CONTROLLED,POLY_CONTROLLED),
WIZCMDS_META(constwidth_POLY_CONTROLLED,sizeof(POLY_CONTROLLED)),
WIZCMDS_META(constsigned_POLY_CONTROLLED,((__typeof__(POLY_CONTROLLED))-1)<0),
WIZCMDS_META(PRIMARYSET,PRIMARYSET),
WIZCMDS_META(constwidth_PRIMARYSET,sizeof(PRIMARYSET)),
WIZCMDS_META(constsigned_PRIMARYSET,((__typeof__(PRIMARYSET))-1)<0),
WIZCMDS_META(PROT_FROM_SHAPE_CHANGERS,PROT_FROM_SHAPE_CHANGERS),
WIZCMDS_META(constwidth_PROT_FROM_SHAPE_CHANGERS,sizeof(PROT_FROM_SHAPE_CHANGERS)),
WIZCMDS_META(constsigned_PROT_FROM_SHAPE_CHANGERS,((__typeof__(PROT_FROM_SHAPE_CHANGERS))-1)<0),
WIZCMDS_META(QBUFSZ,QBUFSZ),
WIZCMDS_META(constwidth_QBUFSZ,sizeof(QBUFSZ)),
WIZCMDS_META(constsigned_QBUFSZ,((__typeof__(QBUFSZ))-1)<0),
WIZCMDS_META(ROOM,ROOM),
WIZCMDS_META(constwidth_ROOM,sizeof(ROOM)),
WIZCMDS_META(constsigned_ROOM,((__typeof__(ROOM))-1)<0),
WIZCMDS_META(ROWNO,ROWNO),
WIZCMDS_META(constwidth_ROWNO,sizeof(ROWNO)),
WIZCMDS_META(constsigned_ROWNO,((__typeof__(ROWNO))-1)<0),
WIZCMDS_META(SDOOR,SDOOR),
WIZCMDS_META(constwidth_SDOOR,sizeof(SDOOR)),
WIZCMDS_META(constsigned_SDOOR,((__typeof__(SDOOR))-1)<0),
WIZCMDS_META(SICK,SICK),
WIZCMDS_META(constwidth_SICK,sizeof(SICK)),
WIZCMDS_META(constsigned_SICK,((__typeof__(SICK))-1)<0),
WIZCMDS_META(SICK_NONVOMITABLE,SICK_NONVOMITABLE),
WIZCMDS_META(constwidth_SICK_NONVOMITABLE,sizeof(SICK_NONVOMITABLE)),
WIZCMDS_META(constsigned_SICK_NONVOMITABLE,((__typeof__(SICK_NONVOMITABLE))-1)<0),
WIZCMDS_META(SICK_VOMITABLE,SICK_VOMITABLE),
WIZCMDS_META(constwidth_SICK_VOMITABLE,sizeof(SICK_VOMITABLE)),
WIZCMDS_META(constsigned_SICK_VOMITABLE,((__typeof__(SICK_VOMITABLE))-1)<0),
WIZCMDS_META(SLIMED,SLIMED),
WIZCMDS_META(constwidth_SLIMED,sizeof(SLIMED)),
WIZCMDS_META(constsigned_SLIMED,((__typeof__(SLIMED))-1)<0),
WIZCMDS_META(STATUE,STATUE),
WIZCMDS_META(constwidth_STATUE,sizeof(STATUE)),
WIZCMDS_META(constsigned_STATUE,((__typeof__(STATUE))-1)<0),
WIZCMDS_META(STONE,STONE),
WIZCMDS_META(constwidth_STONE,sizeof(STONE)),
WIZCMDS_META(constsigned_STONE,((__typeof__(STONE))-1)<0),
WIZCMDS_META(STONED,STONED),
WIZCMDS_META(constwidth_STONED,sizeof(STONED)),
WIZCMDS_META(constsigned_STONED,((__typeof__(STONED))-1)<0),
WIZCMDS_META(STUNNED,STUNNED),
WIZCMDS_META(constwidth_STUNNED,sizeof(STUNNED)),
WIZCMDS_META(constsigned_STUNNED,((__typeof__(STUNNED))-1)<0),
WIZCMDS_META(SUPPRESS_HALLUCINATION,SUPPRESS_HALLUCINATION),
WIZCMDS_META(constwidth_SUPPRESS_HALLUCINATION,sizeof(SUPPRESS_HALLUCINATION)),
WIZCMDS_META(constsigned_SUPPRESS_HALLUCINATION,((__typeof__(SUPPRESS_HALLUCINATION))-1)<0),
WIZCMDS_META(SUPPRESS_IT,SUPPRESS_IT),
WIZCMDS_META(constwidth_SUPPRESS_IT,sizeof(SUPPRESS_IT)),
WIZCMDS_META(constsigned_SUPPRESS_IT,((__typeof__(SUPPRESS_IT))-1)<0),
WIZCMDS_META(SUPPRESS_SADDLE,SUPPRESS_SADDLE),
WIZCMDS_META(constwidth_SUPPRESS_SADDLE,sizeof(SUPPRESS_SADDLE)),
WIZCMDS_META(constsigned_SUPPRESS_SADDLE,((__typeof__(SUPPRESS_SADDLE))-1)<0),
WIZCMDS_META(S_GOLEM,S_GOLEM),
WIZCMDS_META(constwidth_S_GOLEM,sizeof(S_GOLEM)),
WIZCMDS_META(constsigned_S_GOLEM,((__typeof__(S_GOLEM))-1)<0),
WIZCMDS_META(S_VORTEX,S_VORTEX),
WIZCMDS_META(constwidth_S_VORTEX,sizeof(S_VORTEX)),
WIZCMDS_META(constsigned_S_VORTEX,((__typeof__(S_VORTEX))-1)<0),
WIZCMDS_META(S_digbeam,S_digbeam),
WIZCMDS_META(constwidth_S_digbeam,sizeof(S_digbeam)),
WIZCMDS_META(constsigned_S_digbeam,((__typeof__(S_digbeam))-1)<0),
WIZCMDS_META(S_fountain,S_fountain),
WIZCMDS_META(constwidth_S_fountain,sizeof(S_fountain)),
WIZCMDS_META(constsigned_S_fountain,((__typeof__(S_fountain))-1)<0),
WIZCMDS_META(S_goodpos,S_goodpos),
WIZCMDS_META(constwidth_S_goodpos,sizeof(S_goodpos)),
WIZCMDS_META(constsigned_S_goodpos,((__typeof__(S_goodpos))-1)<0),
WIZCMDS_META(S_rslant,S_rslant),
WIZCMDS_META(constwidth_S_rslant,sizeof(S_rslant)),
WIZCMDS_META(constsigned_S_rslant,((__typeof__(S_rslant))-1)<0),
WIZCMDS_META(S_sink,S_sink),
WIZCMDS_META(constwidth_S_sink,sizeof(S_sink)),
WIZCMDS_META(constsigned_S_sink,((__typeof__(S_sink))-1)<0),
WIZCMDS_META(S_vbeam,S_vbeam),
WIZCMDS_META(constwidth_S_vbeam,sizeof(S_vbeam)),
WIZCMDS_META(constsigned_S_vbeam,((__typeof__(S_vbeam))-1)<0),
WIZCMDS_META(TEMP_LIT,TEMP_LIT),
WIZCMDS_META(constwidth_TEMP_LIT,sizeof(TEMP_LIT)),
WIZCMDS_META(constsigned_TEMP_LIT,((__typeof__(TEMP_LIT))-1)<0),
WIZCMDS_META(TIMEOUT,TIMEOUT),
WIZCMDS_META(constwidth_TIMEOUT,sizeof(TIMEOUT)),
WIZCMDS_META(constsigned_TIMEOUT,((__typeof__(TIMEOUT))-1)<0),
WIZCMDS_META(TRUE,TRUE),
WIZCMDS_META(constwidth_TRUE,sizeof(TRUE)),
WIZCMDS_META(constsigned_TRUE,((__typeof__(TRUE))-1)<0),
WIZCMDS_META(UTOTYPE_NONE,UTOTYPE_NONE),
WIZCMDS_META(constwidth_UTOTYPE_NONE,sizeof(UTOTYPE_NONE)),
WIZCMDS_META(constsigned_UTOTYPE_NONE,((__typeof__(UTOTYPE_NONE))-1)<0),
WIZCMDS_META(VOMITING,VOMITING),
WIZCMDS_META(constwidth_VOMITING,sizeof(VOMITING)),
WIZCMDS_META(constsigned_VOMITING,((__typeof__(VOMITING))-1)<0),
WIZCMDS_META(WARN_OF_MON,WARN_OF_MON),
WIZCMDS_META(constwidth_WARN_OF_MON,sizeof(WARN_OF_MON)),
WIZCMDS_META(constsigned_WARN_OF_MON,((__typeof__(WARN_OF_MON))-1)<0),
WIZCMDS_META(WIN_ERR,WIN_ERR),
WIZCMDS_META(constwidth_WIN_ERR,sizeof(WIN_ERR)),
WIZCMDS_META(constsigned_WIN_ERR,((__typeof__(WIN_ERR))-1)<0),
WIZCMDS_META(WM_MASK,WM_MASK),
WIZCMDS_META(constwidth_WM_MASK,sizeof(WM_MASK)),
WIZCMDS_META(constsigned_WM_MASK,((__typeof__(WM_MASK))-1)<0),
WIZCMDS_META(WWALKING,WWALKING),
WIZCMDS_META(constwidth_WWALKING,sizeof(WWALKING)),
WIZCMDS_META(constsigned_WWALKING,((__typeof__(WWALKING))-1)<0),
WIZCMDS_META(XKILL_NOMSG,XKILL_NOMSG),
WIZCMDS_META(constwidth_XKILL_NOMSG,sizeof(XKILL_NOMSG)),
WIZCMDS_META(constsigned_XKILL_NOMSG,((__typeof__(XKILL_NOMSG))-1)<0),
WIZCMDS_META(fuzzer_impossible_continue,fuzzer_impossible_continue),
WIZCMDS_META(constwidth_fuzzer_impossible_continue,sizeof(fuzzer_impossible_continue)),
WIZCMDS_META(constsigned_fuzzer_impossible_continue,((__typeof__(fuzzer_impossible_continue))-1)<0),
WIZCMDS_META(fuzzer_impossible_panic,fuzzer_impossible_panic),
WIZCMDS_META(constwidth_fuzzer_impossible_panic,sizeof(fuzzer_impossible_panic)),
WIZCMDS_META(constsigned_fuzzer_impossible_panic,((__typeof__(fuzzer_impossible_panic))-1)<0),
WIZCMDS_META(wp_tty,wp_tty),
WIZCMDS_META(constwidth_wp_tty,sizeof(wp_tty)),
WIZCMDS_META(constsigned_wp_tty,((__typeof__(wp_tty))-1)<0),
WIZCMDS_META(flagSize,sizeof(struct flag)),
WIZCMDS_META(width_flag_debug,sizeof(((struct flag*)0)->debug)),
WIZCMDS_META(width_flag_verbose,sizeof(((struct flag*)0)->verbose)),
WIZCMDS_META(width_flag_female,sizeof(((struct flag*)0)->female)),
WIZCMDS_META(width_flag_suppress_alert,sizeof(((struct flag*)0)->suppress_alert)),
WIZCMDS_META(instance_flagsSize,sizeof(struct instance_flags)),
WIZCMDS_META(width_instance_flags_override_ID,sizeof(((struct instance_flags*)0)->override_ID)),
WIZCMDS_META(width_instance_flags_debug_mongen,sizeof(((struct instance_flags*)0)->debug_mongen)),
WIZCMDS_META(width_instance_flags_autodescribe,sizeof(((struct instance_flags*)0)->autodescribe)),
WIZCMDS_META(width_instance_flags_menu_requested,sizeof(((struct instance_flags*)0)->menu_requested)),
WIZCMDS_META(width_instance_flags_debug_fuzzer,sizeof(((struct instance_flags*)0)->debug_fuzzer)),
WIZCMDS_META(width_instance_flags_cmdassist,sizeof(((struct instance_flags*)0)->cmdassist)),
WIZCMDS_META(width_instance_flags_sanity_no_check,sizeof(((struct instance_flags*)0)->sanity_no_check)),
WIZCMDS_META(width_instance_flags_colorcount,sizeof(((struct instance_flags*)0)->colorcount)),
WIZCMDS_META(permonstSize,sizeof(struct permonst)),
WIZCMDS_META(width_permonst_pmidx,sizeof(((struct permonst*)0)->pmidx)),
WIZCMDS_META(width_permonst_geno,sizeof(((struct permonst*)0)->geno)),
WIZCMDS_META(width_permonst_mflags2,sizeof(((struct permonst*)0)->mflags2)),
WIZCMDS_META(width_permonst_mlet,sizeof(((struct permonst*)0)->mlet)),
WIZCMDS_META(width_permonst_difficulty,sizeof(((struct permonst*)0)->difficulty)),
WIZCMDS_META(width_permonst_mlevel,sizeof(((struct permonst*)0)->mlevel)),
WIZCMDS_META(width_permonst_pmnames,sizeof(((struct permonst*)0)->pmnames)),
WIZCMDS_META(monstSize,sizeof(struct monst)),
WIZCMDS_META(width_monst_data,sizeof(((struct monst*)0)->data)),
WIZCMDS_META(width_monst_mhp,sizeof(((struct monst*)0)->mhp)),
WIZCMDS_META(width_monst_mextra,sizeof(((struct monst*)0)->mextra)),
WIZCMDS_META(width_monst_mstate,sizeof(((struct monst*)0)->mstate)),
WIZCMDS_META(width_monst_nmon,sizeof(((struct monst*)0)->nmon)),
WIZCMDS_META(width_monst_mtame,sizeof(((struct monst*)0)->mtame)),
WIZCMDS_META(width_monst_mx,sizeof(((struct monst*)0)->mx)),
WIZCMDS_META(width_monst_my,sizeof(((struct monst*)0)->my)),
WIZCMDS_META(width_monst_minvent,sizeof(((struct monst*)0)->minvent)),
WIZCMDS_META(width_monst_mux,sizeof(((struct monst*)0)->mux)),
WIZCMDS_META(width_monst_muy,sizeof(((struct monst*)0)->muy)),
WIZCMDS_META(width_monst_m_id,sizeof(((struct monst*)0)->m_id)),
WIZCMDS_META(width_monst_mtrack,sizeof(((struct monst*)0)->mtrack)),
WIZCMDS_META(mvitalsSize,sizeof(struct mvitals)),
WIZCMDS_META(width_mvitals_mvflags,sizeof(((struct mvitals*)0)->mvflags)),
WIZCMDS_META(width_mvitals_born,sizeof(((struct mvitals*)0)->born)),
WIZCMDS_META(instance_globals_saved_mSize,sizeof(struct instance_globals_saved_m)),
WIZCMDS_META(width_instance_globals_saved_m_mvitals,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
WIZCMDS_META(youSize,sizeof(struct you)),
WIZCMDS_META(width_you_uz,sizeof(((struct you*)0)->uz)),
WIZCMDS_META(width_you_ux,sizeof(((struct you*)0)->ux)),
WIZCMDS_META(width_you_uy,sizeof(((struct you*)0)->uy)),
WIZCMDS_META(width_you_uprops,sizeof(((struct you*)0)->uprops)),
WIZCMDS_META(width_you_usteed,sizeof(((struct you*)0)->usteed)),
WIZCMDS_META(width_you_ustuck,sizeof(((struct you*)0)->ustuck)),
WIZCMDS_META(width_you_utotype,sizeof(((struct you*)0)->utotype)),
WIZCMDS_META(width_you_ulevel,sizeof(((struct you*)0)->ulevel)),
WIZCMDS_META(width_you_ulevelmax,sizeof(((struct you*)0)->ulevelmax)),
WIZCMDS_META(width_you_dx,sizeof(((struct you*)0)->dx)),
WIZCMDS_META(width_you_dy,sizeof(((struct you*)0)->dy)),
WIZCMDS_META(width_you_uhp,sizeof(((struct you*)0)->uhp)),
WIZCMDS_META(width_you_uhpmax,sizeof(((struct you*)0)->uhpmax)),
WIZCMDS_META(width_you_uen,sizeof(((struct you*)0)->uen)),
WIZCMDS_META(width_you_uenmax,sizeof(((struct you*)0)->uenmax)),
WIZCMDS_META(width_you_uswldtim,sizeof(((struct you*)0)->uswldtim)),
WIZCMDS_META(width_you_umonnum,sizeof(((struct you*)0)->umonnum)),
WIZCMDS_META(width_you_umonster,sizeof(((struct you*)0)->umonster)),
WIZCMDS_META(width_you_mh,sizeof(((struct you*)0)->mh)),
WIZCMDS_META(width_you_mhmax,sizeof(((struct you*)0)->mhmax)),
WIZCMDS_META(eshkSize,sizeof(struct eshk)),
WIZCMDS_META(width_eshk_shoplevel,sizeof(((struct eshk*)0)->shoplevel)),
WIZCMDS_META(mextraSize,sizeof(struct mextra)),
WIZCMDS_META(width_mextra_eshk,sizeof(((struct mextra*)0)->eshk)),
WIZCMDS_META(width_mextra_epri,sizeof(((struct mextra*)0)->epri)),
WIZCMDS_META(width_mextra_egd,sizeof(((struct mextra*)0)->egd)),
WIZCMDS_META(width_mextra_mgivenname,sizeof(((struct mextra*)0)->mgivenname)),
WIZCMDS_META(width_mextra_emin,sizeof(((struct mextra*)0)->emin)),
WIZCMDS_META(width_mextra_edog,sizeof(((struct mextra*)0)->edog)),
WIZCMDS_META(width_mextra_ebones,sizeof(((struct mextra*)0)->ebones)),
WIZCMDS_META(dlevel_tSize,sizeof(dlevel_t)),
WIZCMDS_META(width_dlevel_t_monlist,sizeof(((dlevel_t*)0)->monlist)),
WIZCMDS_META(width_dlevel_t_monsters,sizeof(((dlevel_t*)0)->monsters)),
WIZCMDS_META(width_dlevel_t_locations,sizeof(((dlevel_t*)0)->locations)),
WIZCMDS_META(width_dlevel_t_flags,sizeof(((dlevel_t*)0)->flags)),
WIZCMDS_META(width_dlevel_t_objlist,sizeof(((dlevel_t*)0)->objlist)),
WIZCMDS_META(width_dlevel_t_buriedobjlist,sizeof(((dlevel_t*)0)->buriedobjlist)),
WIZCMDS_META(width_dlevel_t_damagelist,sizeof(((dlevel_t*)0)->damagelist)),
WIZCMDS_META(width_dlevel_t_bonesinfo,sizeof(((dlevel_t*)0)->bonesinfo)),
WIZCMDS_META(instance_globals_saved_lSize,sizeof(struct instance_globals_saved_l)),
WIZCMDS_META(width_instance_globals_saved_l_level,sizeof(((struct instance_globals_saved_l*)0)->level)),
WIZCMDS_META(instance_globals_mSize,sizeof(struct instance_globals_m)),
WIZCMDS_META(width_instance_globals_m_migrating_mons,sizeof(((struct instance_globals_m*)0)->migrating_mons)),
WIZCMDS_META(width_instance_globals_m_migrating_objs,sizeof(((struct instance_globals_m*)0)->migrating_objs)),
WIZCMDS_META(width_instance_globals_m_mydogs,sizeof(((struct instance_globals_m*)0)->mydogs)),
WIZCMDS_META(epriSize,sizeof(struct epri)),
WIZCMDS_META(width_epri_shrlevel,sizeof(((struct epri*)0)->shrlevel)),
WIZCMDS_META(egdSize,sizeof(struct egd)),
WIZCMDS_META(width_egd_gdlevel,sizeof(((struct egd*)0)->gdlevel)),
WIZCMDS_META(propSize,sizeof(struct prop)),
WIZCMDS_META(width_prop_intrinsic,sizeof(((struct prop*)0)->intrinsic)),
WIZCMDS_META(width_prop_extrinsic,sizeof(((struct prop*)0)->extrinsic)),
WIZCMDS_META(accessibility_dataSize,sizeof(struct accessibility_data)),
WIZCMDS_META(width_accessibility_data_mon_notices_blocked,sizeof(((struct accessibility_data*)0)->mon_notices_blocked)),
WIZCMDS_META(instance_globals_fSize,sizeof(struct instance_globals_f)),
WIZCMDS_META(width_instance_globals_f_ftrap,sizeof(((struct instance_globals_f*)0)->ftrap)),
WIZCMDS_META(trapSize,sizeof(struct trap)),
WIZCMDS_META(width_trap_ntrap,sizeof(((struct trap*)0)->ntrap)),
WIZCMDS_META(engrSize,sizeof(struct engr)),
WIZCMDS_META(width_engr_nxt_engr,sizeof(((struct engr*)0)->nxt_engr)),
WIZCMDS_META(nhcoordSize,sizeof(struct nhcoord)),
WIZCMDS_META(width_nhcoord_x,sizeof(((struct nhcoord*)0)->x)),
WIZCMDS_META(width_nhcoord_y,sizeof(((struct nhcoord*)0)->y)),
WIZCMDS_META(RoleSize,sizeof(struct Role)),
WIZCMDS_META(width_Role_mnum,sizeof(((struct Role*)0)->mnum)),
WIZCMDS_META(instance_globals_uSize,sizeof(struct instance_globals_u)),
WIZCMDS_META(width_instance_globals_u_urole,sizeof(((struct instance_globals_u*)0)->urole)),
WIZCMDS_META(kinfoSize,sizeof(struct kinfo)),
WIZCMDS_META(width_kinfo_name,sizeof(((struct kinfo*)0)->name)),
WIZCMDS_META(width_kinfo_format,sizeof(((struct kinfo*)0)->format)),
WIZCMDS_META(width_kinfo_next,sizeof(((struct kinfo*)0)->next)),
WIZCMDS_META(instance_globals_saved_kSize,sizeof(struct instance_globals_saved_k)),
WIZCMDS_META(width_instance_globals_saved_k_killer,sizeof(((struct instance_globals_saved_k*)0)->killer)),
WIZCMDS_META(GenderSize,sizeof(struct Gender)),
WIZCMDS_META(width_Gender_his,sizeof(((struct Gender*)0)->his)),
WIZCMDS_META(context_infoSize,sizeof(struct context_info)),
WIZCMDS_META(width_context_info_mon_moving,sizeof(((struct context_info*)0)->mon_moving)),
WIZCMDS_META(width_context_info_warntype,sizeof(((struct context_info*)0)->warntype)),
WIZCMDS_META(instance_globals_saved_cSize,sizeof(struct instance_globals_saved_c)),
WIZCMDS_META(width_instance_globals_saved_c_context,sizeof(((struct instance_globals_saved_c*)0)->context)),
WIZCMDS_META(c_common_stringsSize,sizeof(struct c_common_strings)),
WIZCMDS_META(width_c_common_strings_c_Never_mind,sizeof(((struct c_common_strings*)0)->c_Never_mind)),
WIZCMDS_META(window_procsSize,sizeof(struct window_procs)),
WIZCMDS_META(width_window_procs_win_create_nhwindow,sizeof(((struct window_procs*)0)->win_create_nhwindow)),
WIZCMDS_META(width_window_procs_win_putstr,sizeof(((struct window_procs*)0)->win_putstr)),
WIZCMDS_META(width_window_procs_win_display_nhwindow,sizeof(((struct window_procs*)0)->win_display_nhwindow)),
WIZCMDS_META(width_window_procs_win_destroy_nhwindow,sizeof(((struct window_procs*)0)->win_destroy_nhwindow)),
WIZCMDS_META(width_window_procs_wp_id,sizeof(((struct window_procs*)0)->wp_id)),
WIZCMDS_META(width_window_procs_name,sizeof(((struct window_procs*)0)->name)),
WIZCMDS_META(width_window_procs_win_start_menu,sizeof(((struct window_procs*)0)->win_start_menu)),
WIZCMDS_META(width_window_procs_win_end_menu,sizeof(((struct window_procs*)0)->win_end_menu)),
WIZCMDS_META(rmSize,sizeof(struct rm)),
WIZCMDS_META(width_rm_seenv,sizeof(((struct rm*)0)->seenv)),
WIZCMDS_META(width_rm_typ,sizeof(((struct rm*)0)->typ)),
WIZCMDS_META(instance_globals_vSize,sizeof(struct instance_globals_v)),
WIZCMDS_META(width_instance_globals_v_viz_array,sizeof(((struct instance_globals_v*)0)->viz_array)),
WIZCMDS_META(d_levelSize,sizeof(struct d_level)),
WIZCMDS_META(width_d_level_dnum,sizeof(((struct d_level*)0)->dnum)),
WIZCMDS_META(width_d_level_dlevel,sizeof(((struct d_level*)0)->dlevel)),
WIZCMDS_META(s_levelSize,sizeof(struct s_level)),
WIZCMDS_META(width_s_level_proto,sizeof(((struct s_level*)0)->proto)),
WIZCMDS_META(width_s_level_flags,sizeof(((struct s_level*)0)->flags)),
WIZCMDS_META(d_flagsSize,sizeof(struct d_flags)),
WIZCMDS_META(levelflagsSize,sizeof(struct levelflags)),
WIZCMDS_META(width_levelflags_nfountains,sizeof(((struct levelflags*)0)->nfountains)),
WIZCMDS_META(width_levelflags_nsinks,sizeof(((struct levelflags*)0)->nsinks)),
WIZCMDS_META(symdefSize,sizeof(struct symdef)),
WIZCMDS_META(width_symdef_sym,sizeof(((struct symdef*)0)->sym)),
WIZCMDS_META(dgn_topologySize,sizeof(struct dgn_topology)),
WIZCMDS_META(width_dgn_topology_d_mines_dnum,sizeof(((struct dgn_topology*)0)->d_mines_dnum)),
WIZCMDS_META(width_dgn_topology_d_sokoban_dnum,sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)),
WIZCMDS_META(width_dgn_topology_d_quest_dnum,sizeof(((struct dgn_topology*)0)->d_quest_dnum)),
WIZCMDS_META(width_dgn_topology_d_knox_level,sizeof(((struct dgn_topology*)0)->d_knox_level)),
WIZCMDS_META(width_dgn_topology_d_tower_dnum,sizeof(((struct dgn_topology*)0)->d_tower_dnum)),
WIZCMDS_META(width_dgn_topology_d_astral_level,sizeof(((struct dgn_topology*)0)->d_astral_level)),
WIZCMDS_META(width_dgn_topology_d_stronghold_level,sizeof(((struct dgn_topology*)0)->d_stronghold_level)),
WIZCMDS_META(width_dgn_topology_d_valley_level,sizeof(((struct dgn_topology*)0)->d_valley_level)),
WIZCMDS_META(instance_globals_saved_dSize,sizeof(struct instance_globals_saved_d)),
WIZCMDS_META(width_instance_globals_saved_d_dungeon_topology,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
WIZCMDS_META(width_instance_globals_saved_d_dungeons,sizeof(((struct instance_globals_saved_d*)0)->dungeons)),
WIZCMDS_META(dungeonSize,sizeof(struct dungeon)),
WIZCMDS_META(width_dungeon_dname,sizeof(((struct dungeon*)0)->dname)),
WIZCMDS_META(instance_globals_ySize,sizeof(struct instance_globals_y)),
WIZCMDS_META(width_instance_globals_y_youmonst,sizeof(((struct instance_globals_y*)0)->youmonst)),
WIZCMDS_META(const_globalsSize,sizeof(struct const_globals)),
WIZCMDS_META(width_const_globals_zeroany,sizeof(((struct const_globals*)0)->zeroany)),
WIZCMDS_META(anySize,sizeof(union any)),
WIZCMDS_META(width_any_a_int,sizeof(((union any*)0)->a_int)),
WIZCMDS_META(miSize,sizeof(struct mi)),
WIZCMDS_META(width_mi_item,sizeof(((struct mi*)0)->item)),
WIZCMDS_META(width_mi_count,sizeof(((struct mi*)0)->count)),
WIZCMDS_META(warntype_infoSize,sizeof(struct warntype_info)),
WIZCMDS_META(width_warntype_info_speciesidx,sizeof(((struct warntype_info*)0)->speciesidx)),
WIZCMDS_META(width_warntype_info_species,sizeof(((struct warntype_info*)0)->species)),
WIZCMDS_META(display_hintsSize,sizeof(struct display_hints)),
WIZCMDS_META(width_display_hints_botl,sizeof(((struct display_hints*)0)->botl)),
WIZCMDS_META(objSize,sizeof(struct obj)),
WIZCMDS_META(width_obj_oextra,sizeof(((struct obj*)0)->oextra)),
WIZCMDS_META(width_obj_nobj,sizeof(((struct obj*)0)->nobj)),
WIZCMDS_META(width_obj_cobj,sizeof(((struct obj*)0)->cobj)),
WIZCMDS_META(oextraSize,sizeof(struct oextra)),
WIZCMDS_META(width_oextra_oname,sizeof(((struct oextra*)0)->oname)),
WIZCMDS_META(width_oextra_omonst,sizeof(((struct oextra*)0)->omonst)),
WIZCMDS_META(width_oextra_omailcmd,sizeof(((struct oextra*)0)->omailcmd)),
WIZCMDS_META(instance_globals_iSize,sizeof(struct instance_globals_i)),
WIZCMDS_META(width_instance_globals_i_invent,sizeof(((struct instance_globals_i*)0)->invent)),
WIZCMDS_META(damageSize,sizeof(struct damage)),
WIZCMDS_META(width_damage_next,sizeof(((struct damage*)0)->next)),
WIZCMDS_META(cemeterySize,sizeof(struct cemetery)),
WIZCMDS_META(width_cemetery_next,sizeof(((struct cemetery*)0)->next)),
WIZCMDS_META(objclassSize,sizeof(struct objclass)),
WIZCMDS_META(width_objclass_oc_uname,sizeof(((struct objclass*)0)->oc_uname)),
WIZCMDS_META(width_objclass_oc_class,sizeof(((struct objclass*)0)->oc_class)),
WIZCMDS_META(width_objclass_oc_prob,sizeof(((struct objclass*)0)->oc_prob)),
WIZCMDS_META(width_objclass_oc_name_idx,sizeof(((struct objclass*)0)->oc_name_idx)),
WIZCMDS_META(sinfoSize,sizeof(struct sinfo)),
WIZCMDS_META(width_sinfo_in_sanity_check,sizeof(((struct sinfo*)0)->in_sanity_check)),
WIZCMDS_META(instance_globals_bSize,sizeof(struct instance_globals_b)),
WIZCMDS_META(width_instance_globals_b_billobjs,sizeof(((struct instance_globals_b*)0)->billobjs)),
WIZCMDS_META(instance_globals_saved_nSize,sizeof(struct instance_globals_saved_n)),
WIZCMDS_META(width_instance_globals_saved_n_nhuuid,sizeof(((struct instance_globals_saved_n*)0)->nhuuid)),
WIZCMDS_META(objdescrSize,sizeof(struct objdescr)),
WIZCMDS_META(width_objdescr_oc_name,sizeof(((struct objdescr*)0)->oc_name)),
WIZCMDS_META(symsetentrySize,sizeof(struct symsetentry)),
WIZCMDS_META(width_symsetentry_name,sizeof(((struct symsetentry*)0)->name)),
WIZCMDS_META(width_symsetentry_handling,sizeof(((struct symsetentry*)0)->handling)),
WIZCMDS_META(instance_globals_sSize,sizeof(struct instance_globals_s)),
WIZCMDS_META(width_instance_globals_s_symset,sizeof(((struct instance_globals_s*)0)->symset)),
WIZCMDS_META(width_instance_globals_s_showsyms,sizeof(((struct instance_globals_s*)0)->showsyms)),
WIZCMDS_META(instance_globals_cSize,sizeof(struct instance_globals_c)),
WIZCMDS_META(width_instance_globals_c_currentgraphics,sizeof(((struct instance_globals_c*)0)->currentgraphics)),
WIZCMDS_META(glyph_map_entrySize,sizeof(struct glyph_map_entry)),
WIZCMDS_META(width_glyph_map_entry_u,sizeof(((struct glyph_map_entry*)0)->u)),
WIZCMDS_META(width_glyph_map_entry_customcolor,sizeof(((struct glyph_map_entry*)0)->customcolor)),
WIZCMDS_META(width_glyph_map_entry_sym,sizeof(((struct glyph_map_entry*)0)->sym)),
WIZCMDS_META(classic_representationSize,sizeof(struct classic_representation)),
WIZCMDS_META(width_classic_representation_symidx,sizeof(((struct classic_representation*)0)->symidx)),
WIZCMDS_META(width_classic_representation_color,sizeof(((struct classic_representation*)0)->color)),
WIZCMDS_META(unicode_representationSize,sizeof(struct unicode_representation)),
WIZCMDS_META(width_unicode_representation_utf8str,sizeof(((struct unicode_representation*)0)->utf8str)),
WIZCMDS_META(width_unicode_representation_utf32ch,sizeof(((struct unicode_representation*)0)->utf32ch)),
WIZCMDS_META(nhl_sandbox_infoSize,sizeof(struct nhl_sandbox_info)),
WIZCMDS_META(width_nhl_sandbox_info_flags,sizeof(((struct nhl_sandbox_info*)0)->flags)),
WIZCMDS_META(width_nhl_sandbox_info_memlimit,sizeof(((struct nhl_sandbox_info*)0)->memlimit)),
WIZCMDS_META(width_nhl_sandbox_info_steps,sizeof(((struct nhl_sandbox_info*)0)->steps)),
WIZCMDS_META(width_nhl_sandbox_info_perpcall,sizeof(((struct nhl_sandbox_info*)0)->perpcall)),
WIZCMDS_META(glyphinfoSize,sizeof(struct glyphinfo)),
WIZCMDS_META(eminSize,sizeof(struct emin)),
WIZCMDS_META(edogSize,sizeof(struct edog)),
WIZCMDS_META(ebonesSize,sizeof(struct ebones)),
};
#undef WIZCMDS_META
_Static_assert(sizeof(((struct flag*)0)->debug)==1,"WIZCMDS flag.debug width");
_Static_assert((((__typeof__(((struct flag*)0)->debug))-1)<0)==1,"WIZCMDS flag.debug sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"WIZCMDS flag.verbose width");
_Static_assert((((__typeof__(((struct flag*)0)->verbose))-1)<0)==1,"WIZCMDS flag.verbose sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"WIZCMDS flag.female width");
_Static_assert((((__typeof__(((struct flag*)0)->female))-1)<0)==1,"WIZCMDS flag.female sign");
_Static_assert(sizeof(((struct flag*)0)->suppress_alert)==8,"WIZCMDS flag.suppress_alert width");
_Static_assert((((__typeof__(((struct flag*)0)->suppress_alert))-1)<0)==0,"WIZCMDS flag.suppress_alert sign");
_Static_assert(sizeof(((struct instance_flags*)0)->override_ID)==4,"WIZCMDS instance_flags.override_ID width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->override_ID))-1)<0)==1,"WIZCMDS instance_flags.override_ID sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_mongen)==1,"WIZCMDS instance_flags.debug_mongen width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->debug_mongen))-1)<0)==1,"WIZCMDS instance_flags.debug_mongen sign");
_Static_assert(sizeof(((struct instance_flags*)0)->autodescribe)==1,"WIZCMDS instance_flags.autodescribe width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->autodescribe))-1)<0)==1,"WIZCMDS instance_flags.autodescribe sign");
_Static_assert(sizeof(((struct instance_flags*)0)->menu_requested)==1,"WIZCMDS instance_flags.menu_requested width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->menu_requested))-1)<0)==1,"WIZCMDS instance_flags.menu_requested sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_fuzzer)==1,"WIZCMDS instance_flags.debug_fuzzer width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->debug_fuzzer))-1)<0)==1,"WIZCMDS instance_flags.debug_fuzzer sign");
_Static_assert(sizeof(((struct instance_flags*)0)->cmdassist)==1,"WIZCMDS instance_flags.cmdassist width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->cmdassist))-1)<0)==1,"WIZCMDS instance_flags.cmdassist sign");
_Static_assert(sizeof(((struct instance_flags*)0)->sanity_no_check)==1,"WIZCMDS instance_flags.sanity_no_check width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->sanity_no_check))-1)<0)==1,"WIZCMDS instance_flags.sanity_no_check sign");
_Static_assert(sizeof(((struct instance_flags*)0)->colorcount)==4,"WIZCMDS instance_flags.colorcount width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->colorcount))-1)<0)==0,"WIZCMDS instance_flags.colorcount sign");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"WIZCMDS permonst.pmidx width");
_Static_assert((((__typeof__(((struct permonst*)0)->pmidx))-1)<0)==1,"WIZCMDS permonst.pmidx sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"WIZCMDS permonst.geno width");
_Static_assert((((__typeof__(((struct permonst*)0)->geno))-1)<0)==0,"WIZCMDS permonst.geno sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"WIZCMDS permonst.mflags2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"WIZCMDS permonst.mflags2 sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"WIZCMDS permonst.mlet width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"WIZCMDS permonst.mlet sign");
_Static_assert(sizeof(((struct permonst*)0)->difficulty)==1,"WIZCMDS permonst.difficulty width");
_Static_assert((((__typeof__(((struct permonst*)0)->difficulty))-1)<0)==0,"WIZCMDS permonst.difficulty sign");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1,"WIZCMDS permonst.mlevel width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlevel))-1)<0)==1,"WIZCMDS permonst.mlevel sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"WIZCMDS monst.mhp width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"WIZCMDS monst.mhp sign");
_Static_assert(sizeof(((struct monst*)0)->mstate)==8,"WIZCMDS monst.mstate width");
_Static_assert((((__typeof__(((struct monst*)0)->mstate))-1)<0)==1,"WIZCMDS monst.mstate sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"WIZCMDS monst.mtame width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"WIZCMDS monst.mtame sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"WIZCMDS monst.mx width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"WIZCMDS monst.mx sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"WIZCMDS monst.my width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"WIZCMDS monst.my sign");
_Static_assert(sizeof(((struct monst*)0)->mux)==2,"WIZCMDS monst.mux width");
_Static_assert((((__typeof__(((struct monst*)0)->mux))-1)<0)==1,"WIZCMDS monst.mux sign");
_Static_assert(sizeof(((struct monst*)0)->muy)==2,"WIZCMDS monst.muy width");
_Static_assert((((__typeof__(((struct monst*)0)->muy))-1)<0)==1,"WIZCMDS monst.muy sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"WIZCMDS monst.m_id width");
_Static_assert((((__typeof__(((struct monst*)0)->m_id))-1)<0)==0,"WIZCMDS monst.m_id sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"WIZCMDS mvitals.mvflags width");
_Static_assert((((__typeof__(((struct mvitals*)0)->mvflags))-1)<0)==0,"WIZCMDS mvitals.mvflags sign");
_Static_assert(sizeof(((struct mvitals*)0)->born)==1,"WIZCMDS mvitals.born width");
_Static_assert((((__typeof__(((struct mvitals*)0)->born))-1)<0)==0,"WIZCMDS mvitals.born sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"WIZCMDS you.ux width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"WIZCMDS you.ux sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"WIZCMDS you.uy width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"WIZCMDS you.uy sign");
_Static_assert(sizeof(((struct you*)0)->utotype)==1,"WIZCMDS you.utotype width");
_Static_assert((((__typeof__(((struct you*)0)->utotype))-1)<0)==0,"WIZCMDS you.utotype sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"WIZCMDS you.ulevel width");
_Static_assert((((__typeof__(((struct you*)0)->ulevel))-1)<0)==1,"WIZCMDS you.ulevel sign");
_Static_assert(sizeof(((struct you*)0)->ulevelmax)==4,"WIZCMDS you.ulevelmax width");
_Static_assert((((__typeof__(((struct you*)0)->ulevelmax))-1)<0)==1,"WIZCMDS you.ulevelmax sign");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"WIZCMDS you.dx width");
_Static_assert((((__typeof__(((struct you*)0)->dx))-1)<0)==1,"WIZCMDS you.dx sign");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"WIZCMDS you.dy width");
_Static_assert((((__typeof__(((struct you*)0)->dy))-1)<0)==1,"WIZCMDS you.dy sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"WIZCMDS you.uhp width");
_Static_assert((((__typeof__(((struct you*)0)->uhp))-1)<0)==1,"WIZCMDS you.uhp sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4,"WIZCMDS you.uhpmax width");
_Static_assert((((__typeof__(((struct you*)0)->uhpmax))-1)<0)==1,"WIZCMDS you.uhpmax sign");
_Static_assert(sizeof(((struct you*)0)->uen)==4,"WIZCMDS you.uen width");
_Static_assert((((__typeof__(((struct you*)0)->uen))-1)<0)==1,"WIZCMDS you.uen sign");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4,"WIZCMDS you.uenmax width");
_Static_assert((((__typeof__(((struct you*)0)->uenmax))-1)<0)==1,"WIZCMDS you.uenmax sign");
_Static_assert(sizeof(((struct you*)0)->uswldtim)==4,"WIZCMDS you.uswldtim width");
_Static_assert((((__typeof__(((struct you*)0)->uswldtim))-1)<0)==0,"WIZCMDS you.uswldtim sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"WIZCMDS you.umonnum width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"WIZCMDS you.umonnum sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"WIZCMDS you.umonster width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"WIZCMDS you.umonster sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4,"WIZCMDS you.mh width");
_Static_assert((((__typeof__(((struct you*)0)->mh))-1)<0)==1,"WIZCMDS you.mh sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4,"WIZCMDS you.mhmax width");
_Static_assert((((__typeof__(((struct you*)0)->mhmax))-1)<0)==1,"WIZCMDS you.mhmax sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"WIZCMDS prop.intrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"WIZCMDS prop.intrinsic sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"WIZCMDS prop.extrinsic width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"WIZCMDS prop.extrinsic sign");
_Static_assert(sizeof(((struct accessibility_data*)0)->mon_notices_blocked)==4,"WIZCMDS accessibility_data.mon_notices_blocked width");
_Static_assert((((__typeof__(((struct accessibility_data*)0)->mon_notices_blocked))-1)<0)==1,"WIZCMDS accessibility_data.mon_notices_blocked sign");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2,"WIZCMDS nhcoord.x width");
_Static_assert((((__typeof__(((struct nhcoord*)0)->x))-1)<0)==1,"WIZCMDS nhcoord.x sign");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2,"WIZCMDS nhcoord.y width");
_Static_assert((((__typeof__(((struct nhcoord*)0)->y))-1)<0)==1,"WIZCMDS nhcoord.y sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"WIZCMDS Role.mnum width");
_Static_assert((((__typeof__(((struct Role*)0)->mnum))-1)<0)==1,"WIZCMDS Role.mnum sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4,"WIZCMDS kinfo.format width");
_Static_assert((((__typeof__(((struct kinfo*)0)->format))-1)<0)==1,"WIZCMDS kinfo.format sign");
_Static_assert(sizeof(((struct context_info*)0)->mon_moving)==1,"WIZCMDS context_info.mon_moving width");
_Static_assert((((__typeof__(((struct context_info*)0)->mon_moving))-1)<0)==1,"WIZCMDS context_info.mon_moving sign");
_Static_assert(sizeof(((struct window_procs*)0)->wp_id)==4,"WIZCMDS window_procs.wp_id width");
_Static_assert((((__typeof__(((struct window_procs*)0)->wp_id))-1)<0)==0,"WIZCMDS window_procs.wp_id sign");
_Static_assert(sizeof(((struct rm*)0)->seenv)==1,"WIZCMDS rm.seenv width");
_Static_assert((((__typeof__(((struct rm*)0)->seenv))-1)<0)==0,"WIZCMDS rm.seenv sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"WIZCMDS rm.typ width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"WIZCMDS rm.typ sign");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2,"WIZCMDS d_level.dnum width");
_Static_assert((((__typeof__(((struct d_level*)0)->dnum))-1)<0)==1,"WIZCMDS d_level.dnum sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2,"WIZCMDS d_level.dlevel width");
_Static_assert((((__typeof__(((struct d_level*)0)->dlevel))-1)<0)==1,"WIZCMDS d_level.dlevel sign");
_Static_assert(sizeof(((struct levelflags*)0)->nfountains)==1,"WIZCMDS levelflags.nfountains width");
_Static_assert((((__typeof__(((struct levelflags*)0)->nfountains))-1)<0)==0,"WIZCMDS levelflags.nfountains sign");
_Static_assert(sizeof(((struct levelflags*)0)->nsinks)==1,"WIZCMDS levelflags.nsinks width");
_Static_assert((((__typeof__(((struct levelflags*)0)->nsinks))-1)<0)==0,"WIZCMDS levelflags.nsinks sign");
_Static_assert(sizeof(((struct symdef*)0)->sym)==1,"WIZCMDS symdef.sym width");
_Static_assert((((__typeof__(((struct symdef*)0)->sym))-1)<0)==0,"WIZCMDS symdef.sym sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_mines_dnum)==2,"WIZCMDS dgn_topology.d_mines_dnum width");
_Static_assert((((__typeof__(((struct dgn_topology*)0)->d_mines_dnum))-1)<0)==1,"WIZCMDS dgn_topology.d_mines_dnum sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)==2,"WIZCMDS dgn_topology.d_sokoban_dnum width");
_Static_assert((((__typeof__(((struct dgn_topology*)0)->d_sokoban_dnum))-1)<0)==1,"WIZCMDS dgn_topology.d_sokoban_dnum sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_quest_dnum)==2,"WIZCMDS dgn_topology.d_quest_dnum width");
_Static_assert((((__typeof__(((struct dgn_topology*)0)->d_quest_dnum))-1)<0)==1,"WIZCMDS dgn_topology.d_quest_dnum sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_tower_dnum)==2,"WIZCMDS dgn_topology.d_tower_dnum width");
_Static_assert((((__typeof__(((struct dgn_topology*)0)->d_tower_dnum))-1)<0)==1,"WIZCMDS dgn_topology.d_tower_dnum sign");
_Static_assert(sizeof(((union any*)0)->a_int)==4,"WIZCMDS any.a_int width");
_Static_assert((((__typeof__(((union any*)0)->a_int))-1)<0)==1,"WIZCMDS any.a_int sign");
_Static_assert(sizeof(((struct mi*)0)->count)==8,"WIZCMDS mi.count width");
_Static_assert((((__typeof__(((struct mi*)0)->count))-1)<0)==1,"WIZCMDS mi.count sign");
_Static_assert(sizeof(((struct warntype_info*)0)->speciesidx)==2,"WIZCMDS warntype_info.speciesidx width");
_Static_assert((((__typeof__(((struct warntype_info*)0)->speciesidx))-1)<0)==1,"WIZCMDS warntype_info.speciesidx sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"WIZCMDS display_hints.botl width");
_Static_assert((((__typeof__(((struct display_hints*)0)->botl))-1)<0)==1,"WIZCMDS display_hints.botl sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_class)==1,"WIZCMDS objclass.oc_class width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_class))-1)<0)==1,"WIZCMDS objclass.oc_class sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_prob)==2,"WIZCMDS objclass.oc_prob width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_prob))-1)<0)==1,"WIZCMDS objclass.oc_prob sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2,"WIZCMDS objclass.oc_name_idx width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_name_idx))-1)<0)==1,"WIZCMDS objclass.oc_name_idx sign");
_Static_assert(sizeof(((struct sinfo*)0)->in_sanity_check)==4,"WIZCMDS sinfo.in_sanity_check width");
_Static_assert((((__typeof__(((struct sinfo*)0)->in_sanity_check))-1)<0)==1,"WIZCMDS sinfo.in_sanity_check sign");
_Static_assert(sizeof(((struct symsetentry*)0)->handling)==4,"WIZCMDS symsetentry.handling width");
_Static_assert((((__typeof__(((struct symsetentry*)0)->handling))-1)<0)==0,"WIZCMDS symsetentry.handling sign");
_Static_assert(sizeof(((struct instance_globals_c*)0)->currentgraphics)==4,"WIZCMDS instance_globals_c.currentgraphics width");
_Static_assert((((__typeof__(((struct instance_globals_c*)0)->currentgraphics))-1)<0)==1,"WIZCMDS instance_globals_c.currentgraphics sign");
_Static_assert(sizeof(((struct glyph_map_entry*)0)->customcolor)==4,"WIZCMDS glyph_map_entry.customcolor width");
_Static_assert((((__typeof__(((struct glyph_map_entry*)0)->customcolor))-1)<0)==0,"WIZCMDS glyph_map_entry.customcolor sign");
_Static_assert(sizeof(((struct classic_representation*)0)->symidx)==4,"WIZCMDS classic_representation.symidx width");
_Static_assert((((__typeof__(((struct classic_representation*)0)->symidx))-1)<0)==1,"WIZCMDS classic_representation.symidx sign");
_Static_assert(sizeof(((struct classic_representation*)0)->color)==4,"WIZCMDS classic_representation.color width");
_Static_assert((((__typeof__(((struct classic_representation*)0)->color))-1)<0)==1,"WIZCMDS classic_representation.color sign");
_Static_assert(sizeof(((struct unicode_representation*)0)->utf32ch)==4,"WIZCMDS unicode_representation.utf32ch width");
_Static_assert((((__typeof__(((struct unicode_representation*)0)->utf32ch))-1)<0)==0,"WIZCMDS unicode_representation.utf32ch sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->flags)==4,"WIZCMDS nhl_sandbox_info.flags width");
_Static_assert((((__typeof__(((struct nhl_sandbox_info*)0)->flags))-1)<0)==0,"WIZCMDS nhl_sandbox_info.flags sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->memlimit)==4,"WIZCMDS nhl_sandbox_info.memlimit width");
_Static_assert((((__typeof__(((struct nhl_sandbox_info*)0)->memlimit))-1)<0)==0,"WIZCMDS nhl_sandbox_info.memlimit sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->steps)==4,"WIZCMDS nhl_sandbox_info.steps width");
_Static_assert((((__typeof__(((struct nhl_sandbox_info*)0)->steps))-1)<0)==0,"WIZCMDS nhl_sandbox_info.steps sign");
_Static_assert(sizeof(((struct nhl_sandbox_info*)0)->perpcall)==4,"WIZCMDS nhl_sandbox_info.perpcall width");
_Static_assert((((__typeof__(((struct nhl_sandbox_info*)0)->perpcall))-1)<0)==0,"WIZCMDS nhl_sandbox_info.perpcall sign");
#endif
