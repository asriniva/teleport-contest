#ifndef TELEPORT_READ_LAYOUT_H
#define TELEPORT_READ_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#if !defined(UNIX) || !defined(DEBUG) || !defined(MAIL) || !defined(MAIL_STRUCTURES)
#error Review changed READ configured profile
#endif
#if !defined(TELEPORT_REFERENCE_TU) && !defined(TELEPORT_READ_LITMON_DEFINED)
#define TELEPORT_READ_LITMON_DEFINED
struct litmon {struct monst *mon;struct litmon *nxt;};
#endif
#define ZT_SPELL_O_FIRE 11 /* explained in splatter_burning_oil(explode.c) */
#define REALLY 1
#define PLAYER 2
#define ONTHRONE 4
#define QUAN_LIMIT (ROWNO * (COLNO - 1))
#define CP_TRYLIM 5
struct read_layout_entry {const char *name;long long value;};
#define READ_META(k,v) {#k,(long long)(v)}
static const struct read_layout_entry read_layout[]={
READ_META(pointerSize,sizeof(void*)),
READ_META(longSize,sizeof(long)),
READ_META(booleanSize,sizeof(boolean)),
READ_META(litmonSize,sizeof(struct litmon)),
READ_META(NUMMONS,NUMMONS),
READ_META(MAXMCLASSES,MAXMCLASSES),
READ_META(R0_size,sizeof(struct objclass)),
READ_META(R0_F2,offsetof(struct objclass,oc_subtyp)),
READ_META(R0_F2_size,sizeof(((struct objclass*)0)->oc_subtyp)),
READ_META(R1_size,sizeof(struct obj)),
READ_META(R1_F0,offsetof(struct obj,oclass)),
READ_META(R1_F0_size,sizeof(((struct obj*)0)->oclass)),
READ_META(R1_F1,offsetof(struct obj,otyp)),
READ_META(R1_F1_size,sizeof(((struct obj*)0)->otyp)),
READ_META(R1_F2,offsetof(struct obj,spe)),
READ_META(R1_F2_size,sizeof(((struct obj*)0)->spe)),
READ_META(R1_F5,offsetof(struct obj,o_id)),
READ_META(R1_F5_size,sizeof(((struct obj*)0)->o_id)),
READ_META(R1_F8,offsetof(struct obj,oartifact)),
READ_META(R1_F8_size,sizeof(((struct obj*)0)->oartifact)),
READ_META(R1_F13,offsetof(struct obj,age)),
READ_META(R1_F13_size,sizeof(((struct obj*)0)->age)),
READ_META(R1_F19,offsetof(struct obj,nobj)),
READ_META(R1_F19_size,sizeof(((struct obj*)0)->nobj)),
READ_META(R1_F20,offsetof(struct obj,quan)),
READ_META(R1_F20_size,sizeof(((struct obj*)0)->quan)),
READ_META(R1_F21,offsetof(struct obj,owornmask)),
READ_META(R1_F21_size,sizeof(((struct obj*)0)->owornmask)),
READ_META(R1_F22,offsetof(struct obj,corpsenm)),
READ_META(R1_F22_size,sizeof(((struct obj*)0)->corpsenm)),
READ_META(R1_F24,offsetof(struct obj,owt)),
READ_META(R1_F24_size,sizeof(((struct obj*)0)->owt)),
READ_META(R1_F25,offsetof(struct obj,ox)),
READ_META(R1_F25_size,sizeof(((struct obj*)0)->ox)),
READ_META(R1_F26,offsetof(struct obj,oy)),
READ_META(R1_F26_size,sizeof(((struct obj*)0)->oy)),
READ_META(R1_F27,offsetof(struct obj,oextra)),
READ_META(R1_F27_size,sizeof(((struct obj*)0)->oextra)),
READ_META(R2_size,sizeof(struct instance_globals_k)),
READ_META(R2_F0,offsetof(struct instance_globals_k,known)),
READ_META(R2_F0_size,sizeof(((struct instance_globals_k*)0)->known)),
READ_META(R3_size,sizeof(struct flag)),
READ_META(R3_F0,offsetof(struct flag,verbose)),
READ_META(R3_F0_size,sizeof(((struct flag*)0)->verbose)),
READ_META(R3_F1,offsetof(struct flag,debug)),
READ_META(R3_F1_size,sizeof(((struct flag*)0)->debug)),
READ_META(R3_F2,offsetof(struct flag,female)),
READ_META(R3_F2_size,sizeof(((struct flag*)0)->female)),
READ_META(R4_size,sizeof(struct prop)),
READ_META(R4_F0,offsetof(struct prop,intrinsic)),
READ_META(R4_F0_size,sizeof(((struct prop*)0)->intrinsic)),
READ_META(R4_F1,offsetof(struct prop,extrinsic)),
READ_META(R4_F1_size,sizeof(((struct prop*)0)->extrinsic)),
READ_META(R4_F2,offsetof(struct prop,blocked)),
READ_META(R4_F2_size,sizeof(((struct prop*)0)->blocked)),
READ_META(R5_size,sizeof(struct you)),
READ_META(R5_F0,offsetof(struct you,uprops)),
READ_META(R5_F0_size,sizeof(((struct you*)0)->uprops)),
READ_META(R5_F0_stride,sizeof(((struct you*)0)->uprops[0])),
READ_META(R5_F1,offsetof(struct you,uconduct)),
READ_META(R5_F1_size,sizeof(((struct you*)0)->uconduct)),
READ_META(R5_F2,offsetof(struct you,bc_felt)),
READ_META(R5_F2_size,sizeof(((struct you*)0)->bc_felt)),
READ_META(R5_F3,offsetof(struct you,usteed)),
READ_META(R5_F3_size,sizeof(((struct you*)0)->usteed)),
READ_META(R5_F4,offsetof(struct you,ustuck)),
READ_META(R5_F4_size,sizeof(((struct you*)0)->ustuck)),
READ_META(R5_F5,offsetof(struct you,ux)),
READ_META(R5_F5_size,sizeof(((struct you*)0)->ux)),
READ_META(R5_F6,offsetof(struct you,uy)),
READ_META(R5_F6_size,sizeof(((struct you*)0)->uy)),
READ_META(R5_F7,offsetof(struct you,uz)),
READ_META(R5_F7_size,sizeof(((struct you*)0)->uz)),
READ_META(R5_F8,offsetof(struct you,umconf)),
READ_META(R5_F8_size,sizeof(((struct you*)0)->umconf)),
READ_META(R5_F9,offsetof(struct you,twoweap)),
READ_META(R5_F9_size,sizeof(((struct you*)0)->twoweap)),
READ_META(R5_F10,offsetof(struct you,utrap)),
READ_META(R5_F10_size,sizeof(((struct you*)0)->utrap)),
READ_META(R5_F11,offsetof(struct you,utraptype)),
READ_META(R5_F11_size,sizeof(((struct you*)0)->utraptype)),
READ_META(R5_F13,offsetof(struct you,uen)),
READ_META(R5_F13_size,sizeof(((struct you*)0)->uen)),
READ_META(R5_F14,offsetof(struct you,uenmax)),
READ_META(R5_F14_size,sizeof(((struct you*)0)->uenmax)),
READ_META(R5_F16,offsetof(struct you,uluck)),
READ_META(R5_F16_size,sizeof(((struct you*)0)->uluck)),
READ_META(R5_F17,offsetof(struct you,moreluck)),
READ_META(R5_F17_size,sizeof(((struct you*)0)->moreluck)),
READ_META(R5_F18,offsetof(struct you,uroleplay)),
READ_META(R5_F18_size,sizeof(((struct you*)0)->uroleplay)),
READ_META(R5_F19,offsetof(struct you,umonnum)),
READ_META(R5_F19_size,sizeof(((struct you*)0)->umonnum)),
READ_META(R5_F20,offsetof(struct you,umonster)),
READ_META(R5_F20_size,sizeof(((struct you*)0)->umonster)),
READ_META(R5_F21,offsetof(struct you,mh)),
READ_META(R5_F21_size,sizeof(((struct you*)0)->mh)),
READ_META(R5_F22,offsetof(struct you,uhp)),
READ_META(R5_F22_size,sizeof(((struct you*)0)->uhp)),
READ_META(R5_F24,offsetof(struct you,ualign)),
READ_META(R5_F24_size,sizeof(((struct you*)0)->ualign)),
READ_META(R6_size,sizeof(struct u_conduct)),
READ_META(R6_F0,offsetof(struct u_conduct,literate)),
READ_META(R6_F0_size,sizeof(((struct u_conduct*)0)->literate)),
READ_META(R7_size,sizeof(struct Role)),
READ_META(R7_F0,offsetof(struct Role,mnum)),
READ_META(R7_F0_size,sizeof(((struct Role*)0)->mnum)),
READ_META(R7_F1,offsetof(struct Role,name)),
READ_META(R7_F1_size,sizeof(((struct Role*)0)->name)),
READ_META(R8_size,sizeof(struct instance_globals_u)),
READ_META(R8_F0,offsetof(struct instance_globals_u,urole)),
READ_META(R8_F0_size,sizeof(((struct instance_globals_u*)0)->urole)),
READ_META(R8_F1,offsetof(struct instance_globals_u,urace)),
READ_META(R8_F1_size,sizeof(((struct instance_globals_u*)0)->urace)),
READ_META(R9_size,sizeof(struct c_common_strings)),
READ_META(R9_F0,offsetof(struct c_common_strings,c_silly_thing_to)),
READ_META(R9_F0_size,sizeof(((struct c_common_strings*)0)->c_silly_thing_to)),
READ_META(R9_F1,offsetof(struct c_common_strings,c_something)),
READ_META(R9_F1_size,sizeof(((struct c_common_strings*)0)->c_something)),
READ_META(R9_F2,offsetof(struct c_common_strings,c_nothing_happens)),
READ_META(R9_F2_size,sizeof(((struct c_common_strings*)0)->c_nothing_happens)),
READ_META(R9_F3,offsetof(struct c_common_strings,c_thats_enough_tries)),
READ_META(R9_F3_size,sizeof(((struct c_common_strings*)0)->c_thats_enough_tries)),
READ_META(R9_F4,offsetof(struct c_common_strings,c_Never_mind)),
READ_META(R9_F4_size,sizeof(((struct c_common_strings*)0)->c_Never_mind)),
READ_META(R10_size,sizeof(struct instance_globals_y)),
READ_META(R10_F0,offsetof(struct instance_globals_y,youmonst)),
READ_META(R10_F0_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
READ_META(R11_size,sizeof(struct c_color_names)),
READ_META(R11_F0,offsetof(struct c_color_names,c_blue)),
READ_META(R11_F0_size,sizeof(((struct c_color_names*)0)->c_blue)),
READ_META(R11_F1,offsetof(struct c_color_names,c_white)),
READ_META(R11_F1_size,sizeof(((struct c_color_names*)0)->c_white)),
READ_META(R11_F2,offsetof(struct c_color_names,c_black)),
READ_META(R11_F2_size,sizeof(((struct c_color_names*)0)->c_black)),
READ_META(R11_F3,offsetof(struct c_color_names,c_light_blue)),
READ_META(R11_F3_size,sizeof(((struct c_color_names*)0)->c_light_blue)),
READ_META(R11_F4,offsetof(struct c_color_names,c_amber)),
READ_META(R11_F4_size,sizeof(((struct c_color_names*)0)->c_amber)),
READ_META(R11_F5,offsetof(struct c_color_names,c_golden)),
READ_META(R11_F5_size,sizeof(((struct c_color_names*)0)->c_golden)),
READ_META(R11_F6,offsetof(struct c_color_names,c_silver)),
READ_META(R11_F6_size,sizeof(((struct c_color_names*)0)->c_silver)),
READ_META(R11_F7,offsetof(struct c_color_names,c_purple)),
READ_META(R11_F7_size,sizeof(((struct c_color_names*)0)->c_purple)),
READ_META(R11_F8,offsetof(struct c_color_names,c_red)),
READ_META(R11_F8_size,sizeof(((struct c_color_names*)0)->c_red)),
READ_META(R12_size,sizeof(dlevel_t)),
READ_META(R12_F0,offsetof(dlevel_t,monlist)),
READ_META(R12_F0_size,sizeof(((dlevel_t*)0)->monlist)),
READ_META(R12_F1,offsetof(dlevel_t,locations)),
READ_META(R12_F1_size,sizeof(((dlevel_t*)0)->locations)),
READ_META(R12_F1_stride,sizeof(((dlevel_t*)0)->locations[0])),
READ_META(R12_F2,offsetof(dlevel_t,monsters)),
READ_META(R12_F2_size,sizeof(((dlevel_t*)0)->monsters)),
READ_META(R12_F2_stride,sizeof(((dlevel_t*)0)->monsters[0])),
READ_META(R12_F3,offsetof(dlevel_t,flags)),
READ_META(R12_F3_size,sizeof(((dlevel_t*)0)->flags)),
READ_META(R12_F4,offsetof(dlevel_t,objects)),
READ_META(R12_F4_size,sizeof(((dlevel_t*)0)->objects)),
READ_META(R12_F4_stride,sizeof(((dlevel_t*)0)->objects[0])),
READ_META(R13_size,sizeof(struct instance_globals_saved_l)),
READ_META(R13_F0,offsetof(struct instance_globals_saved_l,level)),
READ_META(R13_F0_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
READ_META(R14_size,sizeof(struct monst)),
READ_META(R14_F0,offsetof(struct monst,nmon)),
READ_META(R14_F0_size,sizeof(((struct monst*)0)->nmon)),
READ_META(R14_F2,offsetof(struct monst,mtame)),
READ_META(R14_F2_size,sizeof(((struct monst*)0)->mtame)),
READ_META(R14_F5,offsetof(struct monst,data)),
READ_META(R14_F5_size,sizeof(((struct monst*)0)->data)),
READ_META(R14_F6,offsetof(struct monst,mhp)),
READ_META(R14_F6_size,sizeof(((struct monst*)0)->mhp)),
READ_META(R14_F7,offsetof(struct monst,my)),
READ_META(R14_F7_size,sizeof(((struct monst*)0)->my)),
READ_META(R14_F8,offsetof(struct monst,mx)),
READ_META(R14_F8_size,sizeof(((struct monst*)0)->mx)),
READ_META(R14_F15,offsetof(struct monst,cham)),
READ_META(R14_F15_size,sizeof(((struct monst*)0)->cham)),
READ_META(R15_size,sizeof(struct instance_globals_m)),
READ_META(R15_F0,offsetof(struct instance_globals_m,migrating_mons)),
READ_META(R15_F0_size,sizeof(((struct instance_globals_m*)0)->migrating_mons)),
READ_META(R15_F1,offsetof(struct instance_globals_m,multi)),
READ_META(R15_F1_size,sizeof(((struct instance_globals_m*)0)->multi)),
READ_META(R16_size,sizeof(struct rm)),
READ_META(R16_F0,offsetof(struct rm,typ)),
READ_META(R16_F0_size,sizeof(((struct rm*)0)->typ)),
READ_META(R17_size,sizeof(struct instance_globals_v)),
READ_META(R17_F0,offsetof(struct instance_globals_v,viz_array)),
READ_META(R17_F0_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
READ_META(R17_F1,offsetof(struct instance_globals_v,vision_full_recalc)),
READ_META(R17_F1_size,sizeof(((struct instance_globals_v*)0)->vision_full_recalc)),
READ_META(R18_size,sizeof(d_level)),
READ_META(R18_F0,offsetof(d_level,dlevel)),
READ_META(R18_F0_size,sizeof(((d_level*)0)->dlevel)),
READ_META(R18_F1,offsetof(d_level,dnum)),
READ_META(R18_F1_size,sizeof(((d_level*)0)->dnum)),
READ_META(R19_size,sizeof(struct dgn_topology)),
READ_META(R19_F0,offsetof(struct dgn_topology,d_knox_level)),
READ_META(R19_F0_size,sizeof(((struct dgn_topology*)0)->d_knox_level)),
READ_META(R19_F1,offsetof(struct dgn_topology,d_sokoban_dnum)),
READ_META(R19_F1_size,sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)),
READ_META(R19_F2,offsetof(struct dgn_topology,d_rogue_level)),
READ_META(R19_F2_size,sizeof(((struct dgn_topology*)0)->d_rogue_level)),
READ_META(R19_F3,offsetof(struct dgn_topology,d_astral_level)),
READ_META(R19_F3_size,sizeof(((struct dgn_topology*)0)->d_astral_level)),
READ_META(R19_F4,offsetof(struct dgn_topology,d_earth_level)),
READ_META(R19_F4_size,sizeof(((struct dgn_topology*)0)->d_earth_level)),
READ_META(R19_F5,offsetof(struct dgn_topology,d_water_level)),
READ_META(R19_F5_size,sizeof(((struct dgn_topology*)0)->d_water_level)),
READ_META(R20_size,sizeof(struct instance_globals_saved_d)),
READ_META(R20_F0,offsetof(struct instance_globals_saved_d,dungeon_topology)),
READ_META(R20_F0_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
READ_META(R21_size,sizeof(struct permonst)),
READ_META(R21_F0,offsetof(struct permonst,mlet)),
READ_META(R21_F0_size,sizeof(((struct permonst*)0)->mlet)),
READ_META(R21_F1,offsetof(struct permonst,mflags1)),
READ_META(R21_F1_size,sizeof(((struct permonst*)0)->mflags1)),
READ_META(R21_F2,offsetof(struct permonst,geno)),
READ_META(R21_F2_size,sizeof(((struct permonst*)0)->geno)),
READ_META(R21_F3,offsetof(struct permonst,pmnames)),
READ_META(R21_F3_size,sizeof(((struct permonst*)0)->pmnames)),
READ_META(R21_F3_stride,sizeof(((struct permonst*)0)->pmnames[0])),
READ_META(R21_F4,offsetof(struct permonst,msound)),
READ_META(R21_F4_size,sizeof(((struct permonst*)0)->msound)),
READ_META(R21_F5,offsetof(struct permonst,mflags2)),
READ_META(R21_F5_size,sizeof(((struct permonst*)0)->mflags2)),
READ_META(R21_F6,offsetof(struct permonst,pmidx)),
READ_META(R21_F6_size,sizeof(((struct permonst*)0)->pmidx)),
READ_META(R22_size,sizeof(struct instance_globals_i)),
READ_META(R22_F0,offsetof(struct instance_globals_i,invent)),
READ_META(R22_F0_size,sizeof(((struct instance_globals_i*)0)->invent)),
READ_META(R23_size,sizeof(struct mvitals)),
READ_META(R23_F0,offsetof(struct mvitals,mvflags)),
READ_META(R23_F0_size,sizeof(((struct mvitals*)0)->mvflags)),
READ_META(R24_size,sizeof(struct instance_globals_saved_m)),
READ_META(R24_F0,offsetof(struct instance_globals_saved_m,mvitals)),
READ_META(R24_F0_size,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
READ_META(R24_F0_stride,sizeof(((struct instance_globals_saved_m*)0)->mvitals[0])),
READ_META(R25_size,sizeof(struct display_hints)),
READ_META(R25_F0,offsetof(struct display_hints,botl)),
READ_META(R25_F0_size,sizeof(((struct display_hints*)0)->botl)),
READ_META(R26_size,sizeof(struct instance_globals_saved_p)),
READ_META(R26_F0,offsetof(struct instance_globals_saved_p,plname)),
READ_META(R26_F0_size,sizeof(((struct instance_globals_saved_p*)0)->plname)),
READ_META(R26_F0_stride,sizeof(((struct instance_globals_saved_p*)0)->plname[0])),
READ_META(R27_size,sizeof(coord)),
READ_META(R27_F0,offsetof(coord,x)),
READ_META(R27_F0_size,sizeof(((coord*)0)->x)),
READ_META(R27_F1,offsetof(coord,y)),
READ_META(R27_F1_size,sizeof(((coord*)0)->y)),
READ_META(R28_size,sizeof(struct instance_flags)),
READ_META(R28_F0,offsetof(struct instance_flags,last_msg)),
READ_META(R28_F0_size,sizeof(((struct instance_flags*)0)->last_msg)),
READ_META(R28_F1,offsetof(struct instance_flags,cmdassist)),
READ_META(R28_F1_size,sizeof(((struct instance_flags*)0)->cmdassist)),
READ_META(R29_size,sizeof(struct levelflags)),
READ_META(R30_size,sizeof(struct accessibility_data)),
READ_META(R30_F0,offsetof(struct accessibility_data,mon_notices_blocked)),
READ_META(R30_F0_size,sizeof(((struct accessibility_data*)0)->mon_notices_blocked)),
READ_META(R31_size,sizeof(struct u_roleplay)),
READ_META(R31_F0,offsetof(struct u_roleplay,deaf)),
READ_META(R31_F0_size,sizeof(((struct u_roleplay*)0)->deaf)),
READ_META(R32_size,sizeof(struct Gender)),
READ_META(R32_F0,offsetof(struct Gender,him)),
READ_META(R32_F0_size,sizeof(((struct Gender*)0)->him)),
READ_META(R32_F1,offsetof(struct Gender,his)),
READ_META(R32_F1_size,sizeof(((struct Gender*)0)->his)),
READ_META(R33_size,sizeof(struct litmon)),
READ_META(R33_F0,offsetof(struct litmon,mon)),
READ_META(R33_F0_size,sizeof(((struct litmon*)0)->mon)),
READ_META(R33_F1,offsetof(struct litmon,nxt)),
READ_META(R33_F1_size,sizeof(((struct litmon*)0)->nxt)),
READ_META(R34_size,sizeof(struct mkroom)),
READ_META(R34_F0,offsetof(struct mkroom,lx)),
READ_META(R34_F0_size,sizeof(((struct mkroom*)0)->lx)),
READ_META(R34_F1,offsetof(struct mkroom,hx)),
READ_META(R34_F1_size,sizeof(((struct mkroom*)0)->hx)),
READ_META(R34_F2,offsetof(struct mkroom,ly)),
READ_META(R34_F2_size,sizeof(((struct mkroom*)0)->ly)),
READ_META(R34_F3,offsetof(struct mkroom,hy)),
READ_META(R34_F3_size,sizeof(((struct mkroom*)0)->hy)),
READ_META(R34_F4,offsetof(struct mkroom,rlit)),
READ_META(R34_F4_size,sizeof(((struct mkroom*)0)->rlit)),
READ_META(R35_size,sizeof(struct instance_globals_saved_r)),
READ_META(R35_F0,offsetof(struct instance_globals_saved_r,rooms)),
READ_META(R35_F0_size,sizeof(((struct instance_globals_saved_r*)0)->rooms)),
READ_META(R35_F0_stride,sizeof(((struct instance_globals_saved_r*)0)->rooms[0])),
READ_META(R36_size,sizeof(struct Race)),
READ_META(R36_F0,offsetof(struct Race,mnum)),
READ_META(R36_F0_size,sizeof(((struct Race*)0)->mnum)),
READ_META(R37_size,sizeof(struct class_sym)),
READ_META(R37_F0,offsetof(struct class_sym,sym)),
READ_META(R37_F0_size,sizeof(((struct class_sym*)0)->sym)),
READ_META(R38_size,sizeof(struct kinfo)),
READ_META(R38_F0,offsetof(struct kinfo,format)),
READ_META(R38_F0_size,sizeof(((struct kinfo*)0)->format)),
READ_META(R38_F1,offsetof(struct kinfo,name)),
READ_META(R38_F1_size,sizeof(((struct kinfo*)0)->name)),
READ_META(R38_F1_stride,sizeof(((struct kinfo*)0)->name[0])),
READ_META(R39_size,sizeof(struct instance_globals_saved_k)),
READ_META(R39_F0,offsetof(struct instance_globals_saved_k,killer)),
READ_META(R39_F0_size,sizeof(((struct instance_globals_saved_k*)0)->killer)),
READ_META(R40_size,sizeof(align)),
READ_META(R40_F0,offsetof(align,type)),
READ_META(R40_F0_size,sizeof(((align*)0)->type)),
READ_META(R41_size,sizeof(struct RoleName)),
READ_META(R41_F0,offsetof(struct RoleName,f)),
READ_META(R41_F0_size,sizeof(((struct RoleName*)0)->f)),
READ_META(R41_F1,offsetof(struct RoleName,m)),
READ_META(R41_F1_size,sizeof(((struct RoleName*)0)->m)),
READ_META(R42_size,sizeof(struct oextra)),
READ_META(R42_F0,offsetof(struct oextra,omonst)),
READ_META(R42_F0_size,sizeof(((struct oextra*)0)->omonst)),
READ_META(R43_size,sizeof(struct _create_particular_data)),
READ_META(R43_F0,offsetof(struct _create_particular_data,quan)),
READ_META(R43_F0_size,sizeof(((struct _create_particular_data*)0)->quan)),
READ_META(R43_F1,offsetof(struct _create_particular_data,monclass)),
READ_META(R43_F1_size,sizeof(((struct _create_particular_data*)0)->monclass)),
READ_META(R43_F2,offsetof(struct _create_particular_data,which)),
READ_META(R43_F2_size,sizeof(((struct _create_particular_data*)0)->which)),
READ_META(R43_F3,offsetof(struct _create_particular_data,fem)),
READ_META(R43_F3_size,sizeof(((struct _create_particular_data*)0)->fem)),
READ_META(R43_F4,offsetof(struct _create_particular_data,genderconf)),
READ_META(R43_F4_size,sizeof(((struct _create_particular_data*)0)->genderconf)),
READ_META(R43_F5,offsetof(struct _create_particular_data,randmonst)),
READ_META(R43_F5_size,sizeof(((struct _create_particular_data*)0)->randmonst)),
READ_META(R43_F6,offsetof(struct _create_particular_data,maketame)),
READ_META(R43_F6_size,sizeof(((struct _create_particular_data*)0)->maketame)),
READ_META(R43_F7,offsetof(struct _create_particular_data,makepeaceful)),
READ_META(R43_F7_size,sizeof(((struct _create_particular_data*)0)->makepeaceful)),
READ_META(R43_F8,offsetof(struct _create_particular_data,makehostile)),
READ_META(R43_F8_size,sizeof(((struct _create_particular_data*)0)->makehostile)),
READ_META(R43_F9,offsetof(struct _create_particular_data,sleeping)),
READ_META(R43_F9_size,sizeof(((struct _create_particular_data*)0)->sleeping)),
READ_META(R43_F10,offsetof(struct _create_particular_data,saddled)),
READ_META(R43_F10_size,sizeof(((struct _create_particular_data*)0)->saddled)),
READ_META(R43_F11,offsetof(struct _create_particular_data,invisible)),
READ_META(R43_F11_size,sizeof(((struct _create_particular_data*)0)->invisible)),
READ_META(R43_F12,offsetof(struct _create_particular_data,hidden)),
READ_META(R43_F12_size,sizeof(((struct _create_particular_data*)0)->hidden)),
READ_META(AD_DGST,AD_DGST),
READ_META(AIR,AIR),
READ_META(ALCHEMY_SMOCK,ALCHEMY_SMOCK),
READ_META(ALL_SPELLS,ALL_SPELLS),
READ_META(ARMOR_CLASS,ARMOR_CLASS),
READ_META(ARM_SHIELD,ARM_SHIELD),
READ_META(ART_ORB_OF_FATE,ART_ORB_OF_FATE),
READ_META(ART_SUNSWORD,ART_SUNSWORD),
READ_META(AT_ENGL,AT_ENGL),
READ_META(A_CON,A_CON),
READ_META(A_STR,A_STR),
READ_META(A_WIS,A_WIS),
READ_META(BAG_OF_TRICKS,BAG_OF_TRICKS),
READ_META(BALL_CLASS,BALL_CLASS),
READ_META(BELL_OF_OPENING,BELL_OF_OPENING),
READ_META(BLACK_DRAGON_SCALES,BLACK_DRAGON_SCALES),
READ_META(BLACK_DRAGON_SCALE_MAIL,BLACK_DRAGON_SCALE_MAIL),
READ_META(BLINDED,BLINDED),
READ_META(BOULDER,BOULDER),
READ_META(BRASS_LANTERN,BRASS_LANTERN),
READ_META(BUFSZ,BUFSZ),
READ_META(BY_COOKIE,BY_COOKIE),
READ_META(CANDY_BAR,CANDY_BAR),
READ_META(CAN_OF_GREASE,CAN_OF_GREASE),
READ_META(CHAIN_CLASS,CHAIN_CLASS),
READ_META(CLOUD,CLOUD),
READ_META(COIN_CLASS,COIN_CLASS),
READ_META(COLNO,COLNO),
READ_META(CONFUSION,CONFUSION),
READ_META(CORNUTHAUM,CORNUTHAUM),
READ_META(CORR,CORR),
READ_META(COST_DECHNT,COST_DECHNT),
READ_META(COST_DEGRD,COST_DEGRD),
READ_META(COST_UNCHRG,COST_UNCHRG),
READ_META(COST_UNCURS,COST_UNCURS),
READ_META(CP_TRYLIM,CP_TRYLIM),
READ_META(CREDIT_CARD,CREDIT_CARD),
READ_META(CRYSTAL_BALL,CRYSTAL_BALL),
READ_META(DAGGER,DAGGER),
READ_META(DEAF,DEAF),
READ_META(DISP_BEAM,DISP_BEAM),
READ_META(DISP_END,DISP_END),
READ_META(DOOR,DOOR),
READ_META(DRUM_OF_EARTHQUAKE,DRUM_OF_EARTHQUAKE),
READ_META(DUNCE_CAP,DUNCE_CAP),
READ_META(ECMD_CANCEL,ECMD_CANCEL),
READ_META(ECMD_OK,ECMD_OK),
READ_META(ECMD_TIME,ECMD_TIME),
READ_META(ELVEN_BOOTS,ELVEN_BOOTS),
READ_META(ELVEN_CLOAK,ELVEN_CLOAK),
READ_META(ELVEN_LEATHER_HELM,ELVEN_LEATHER_HELM),
READ_META(ELVEN_MITHRIL_COAT,ELVEN_MITHRIL_COAT),
READ_META(ELVEN_SHIELD,ELVEN_SHIELD),
READ_META(EXPENSIVE_CAMERA,EXPENSIVE_CAMERA),
READ_META(EXPL_FIERY,EXPL_FIERY),
READ_META(FAST,FAST),
READ_META(FEMALE,FEMALE),
READ_META(FIRE_HORN,FIRE_HORN),
READ_META(FIRE_RES,FIRE_RES),
READ_META(FORTUNE_COOKIE,FORTUNE_COOKIE),
READ_META(FROST_HORN,FROST_HORN),
READ_META(GEM_CLASS,GEM_CLASS),
READ_META(GENOCIDED,GENOCIDED),
READ_META(GETOBJ_ALLOWCNT,GETOBJ_ALLOWCNT),
READ_META(GETOBJ_DOWNPLAY,GETOBJ_DOWNPLAY),
READ_META(GETOBJ_EXCLUDE,GETOBJ_EXCLUDE),
READ_META(GETOBJ_EXCLUDE_SELECTABLE,GETOBJ_EXCLUDE_SELECTABLE),
READ_META(GETOBJ_PROMPT,GETOBJ_PROMPT),
READ_META(GETOBJ_SUGGEST,GETOBJ_SUGGEST),
READ_META(GLYPH_ALTAR_OFF,GLYPH_ALTAR_OFF),
READ_META(GLYPH_CMAP_A_OFF,GLYPH_CMAP_A_OFF),
READ_META(GLYPH_CMAP_B_OFF,GLYPH_CMAP_B_OFF),
READ_META(GLYPH_CMAP_C_OFF,GLYPH_CMAP_C_OFF),
READ_META(GLYPH_CMAP_GEH_OFF,GLYPH_CMAP_GEH_OFF),
READ_META(GLYPH_CMAP_KNOX_OFF,GLYPH_CMAP_KNOX_OFF),
READ_META(GLYPH_CMAP_MAIN_OFF,GLYPH_CMAP_MAIN_OFF),
READ_META(GLYPH_CMAP_MINES_OFF,GLYPH_CMAP_MINES_OFF),
READ_META(GLYPH_CMAP_SOKO_OFF,GLYPH_CMAP_SOKO_OFF),
READ_META(GLYPH_CMAP_STONE_OFF,GLYPH_CMAP_STONE_OFF),
READ_META(GRAY_DRAGON_SCALES,GRAY_DRAGON_SCALES),
READ_META(GRAY_DRAGON_SCALE_MAIL,GRAY_DRAGON_SCALE_MAIL),
READ_META(G_EXTINCT,G_EXTINCT),
READ_META(G_GENO,G_GENO),
READ_META(G_GENOD,G_GENOD),
READ_META(G_GONE,G_GONE),
READ_META(G_NOCORPSE,G_NOCORPSE),
READ_META(G_UNIQ,G_UNIQ),
READ_META(HALF_PHDAM,HALF_PHDAM),
READ_META(HALLUC,HALLUC),
READ_META(HALLUC_RES,HALLUC_RES),
READ_META(HAND,HAND),
READ_META(HAWAIIAN_SHIRT,HAWAIIAN_SHIRT),
READ_META(HEAD,HEAD),
READ_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
READ_META(HELM_OF_OPPOSITE_ALIGNMENT,HELM_OF_OPPOSITE_ALIGNMENT),
READ_META(HORN_OF_PLENTY,HORN_OF_PLENTY),
READ_META(INVIS,INVIS),
READ_META(IN_SIGHT,IN_SIGHT),
READ_META(KILLED_BY,KILLED_BY),
READ_META(KILLED_BY_AN,KILLED_BY_AN),
READ_META(LEASH,LEASH),
READ_META(LEATHER_ARMOR,LEATHER_ARMOR),
READ_META(LEFT_RING,LEFT_RING),
READ_META(LEG,LEG),
READ_META(LL_CONDUCT,LL_CONDUCT),
READ_META(LL_GENOCIDE,LL_GENOCIDE),
READ_META(LOADSTONE,LOADSTONE),
READ_META(LOW_PM,LOW_PM),
READ_META(M1_AMORPHOUS,M1_AMORPHOUS),
READ_META(M1_CONCEAL,M1_CONCEAL),
READ_META(M1_HIDE,M1_HIDE),
READ_META(M1_UNSOLID,M1_UNSOLID),
READ_META(M1_WALLWALK,M1_WALLWALK),
READ_META(M2_DEMON,M2_DEMON),
READ_META(M2_FEMALE,M2_FEMALE),
READ_META(M2_HUMAN,M2_HUMAN),
READ_META(M2_MALE,M2_MALE),
READ_META(M2_PNAME,M2_PNAME),
READ_META(MAGIC_FLUTE,MAGIC_FLUTE),
READ_META(MAGIC_HARP,MAGIC_HARP),
READ_META(MAGIC_LAMP,MAGIC_LAMP),
READ_META(MAGIC_MARKER,MAGIC_MARKER),
READ_META(MALE,MALE),
READ_META(MAXMCLASSES,MAXMCLASSES),
READ_META(MAXTCHARS,MAXTCHARS),
READ_META(MAX_ERODE,MAX_ERODE),
READ_META(MM_EDOG,MM_EDOG),
READ_META(MM_FEMALE,MM_FEMALE),
READ_META(MM_MALE,MM_MALE),
READ_META(MM_MINVIS,MM_MINVIS),
READ_META(MM_NOEXCLAM,MM_NOEXCLAM),
READ_META(MM_NOGRP,MM_NOGRP),
READ_META(MM_NOMSG,MM_NOMSG),
READ_META(MS_GUARDIAN,MS_GUARDIAN),
READ_META(MS_LEADER,MS_LEADER),
READ_META(MS_NEMESIS,MS_NEMESIS),
READ_META(M_SEEN_FIRE,M_SEEN_FIRE),
READ_META(NEUTRAL,NEUTRAL),
READ_META(NODIR,NODIR),
READ_META(NON_PM,NON_PM),
READ_META(NOTELL,NOTELL),
READ_META(NO_GLYPH,NO_GLYPH),
READ_META(NO_MINVENT,NO_MINVENT),
READ_META(NO_MM_FLAGS,NO_MM_FLAGS),
READ_META(NO_NC_FLAGS,NO_NC_FLAGS),
READ_META(NUMMONS,NUMMONS),
READ_META(NUM_OBJECTS,NUM_OBJECTS),
READ_META(OIL_LAMP,OIL_LAMP),
READ_META(ONTHRONE,ONTHRONE),
READ_META(PASSES_WALLS,PASSES_WALLS),
READ_META(PLAYER,PLAYER),
READ_META(PLNMSG_TOWER_OF_FLAME,PLNMSG_TOWER_OF_FLAME),
READ_META(PM_ACID_BLOB,PM_ACID_BLOB),
READ_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
READ_META(PM_ALIGNED_CLERIC,PM_ALIGNED_CLERIC),
READ_META(PM_ANGEL,PM_ANGEL),
READ_META(PM_BARBED_DEVIL,PM_BARBED_DEVIL),
READ_META(PM_BLACK_LIGHT,PM_BLACK_LIGHT),
READ_META(PM_DOPPELGANGER,PM_DOPPELGANGER),
READ_META(PM_FIRE_ANT,PM_FIRE_ANT),
READ_META(PM_FLESH_GOLEM,PM_FLESH_GOLEM),
READ_META(PM_GIANT_BAT,PM_GIANT_BAT),
READ_META(PM_GREMLIN,PM_GREMLIN),
READ_META(PM_GUARD,PM_GUARD),
READ_META(PM_HELL_HOUND,PM_HELL_HOUND),
READ_META(PM_HIGH_CLERIC,PM_HIGH_CLERIC),
READ_META(PM_HUMAN,PM_HUMAN),
READ_META(PM_HUMAN_ZOMBIE,PM_HUMAN_ZOMBIE),
READ_META(PM_IMP,PM_IMP),
READ_META(PM_LARGE_MIMIC,PM_LARGE_MIMIC),
READ_META(PM_LEOCROTTA,PM_LEOCROTTA),
READ_META(PM_LONG_WORM,PM_LONG_WORM),
READ_META(PM_LONG_WORM_TAIL,PM_LONG_WORM_TAIL),
READ_META(PM_MARILITH,PM_MARILITH),
READ_META(PM_NINJA,PM_NINJA),
READ_META(PM_PIRANHA,PM_PIRANHA),
READ_META(PM_PYROLISK,PM_PYROLISK),
READ_META(PM_SAMURAI,PM_SAMURAI),
READ_META(PM_SCORPION,PM_SCORPION),
READ_META(PM_SHOPKEEPER,PM_SHOPKEEPER),
READ_META(PM_STALKER,PM_STALKER),
READ_META(PM_TOURIST,PM_TOURIST),
READ_META(PM_VAMPIRE,PM_VAMPIRE),
READ_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
READ_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
READ_META(PM_WATER_MOCCASIN,PM_WATER_MOCCASIN),
READ_META(PM_WIZARD,PM_WIZARD),
READ_META(PM_XAN,PM_XAN),
READ_META(PM_YELLOW_LIGHT,PM_YELLOW_LIGHT),
READ_META(POLYMORPH,POLYMORPH),
READ_META(POLY_REVERT,POLY_REVERT),
READ_META(POOL,POOL),
READ_META(POT_WATER,POT_WATER),
READ_META(PRONOUN_HALLU,PRONOUN_HALLU),
READ_META(P_NONE,P_NONE),
READ_META(P_SLING,P_SLING),
READ_META(QBUFSZ,QBUFSZ),
READ_META(QUAN_LIMIT,QUAN_LIMIT),
READ_META(REALLY,REALLY),
READ_META(RED_DRAGON_SCALES,RED_DRAGON_SCALES),
READ_META(RIGHT_RING,RIGHT_RING),
READ_META(RING_CLASS,RING_CLASS),
READ_META(RIN_ADORNMENT,RIN_ADORNMENT),
READ_META(ROCK,ROCK),
READ_META(ROOMOFFSET,ROOMOFFSET),
READ_META(ROWNO,ROWNO),
READ_META(SCROLL_CLASS,SCROLL_CLASS),
READ_META(SCR_AMNESIA,SCR_AMNESIA),
READ_META(SCR_BLANK_PAPER,SCR_BLANK_PAPER),
READ_META(SCR_CHARGING,SCR_CHARGING),
READ_META(SCR_CONFUSE_MONSTER,SCR_CONFUSE_MONSTER),
READ_META(SCR_CREATE_MONSTER,SCR_CREATE_MONSTER),
READ_META(SCR_DESTROY_ARMOR,SCR_DESTROY_ARMOR),
READ_META(SCR_EARTH,SCR_EARTH),
READ_META(SCR_ENCHANT_ARMOR,SCR_ENCHANT_ARMOR),
READ_META(SCR_ENCHANT_WEAPON,SCR_ENCHANT_WEAPON),
READ_META(SCR_FIRE,SCR_FIRE),
READ_META(SCR_FOOD_DETECTION,SCR_FOOD_DETECTION),
READ_META(SCR_GENOCIDE,SCR_GENOCIDE),
READ_META(SCR_GOLD_DETECTION,SCR_GOLD_DETECTION),
READ_META(SCR_IDENTIFY,SCR_IDENTIFY),
READ_META(SCR_LIGHT,SCR_LIGHT),
READ_META(SCR_MAGIC_MAPPING,SCR_MAGIC_MAPPING),
READ_META(SCR_MAIL,SCR_MAIL),
READ_META(SCR_PUNISHMENT,SCR_PUNISHMENT),
READ_META(SCR_REMOVE_CURSE,SCR_REMOVE_CURSE),
READ_META(SCR_SCARE_MONSTER,SCR_SCARE_MONSTER),
READ_META(SCR_STINKING_CLOUD,SCR_STINKING_CLOUD),
READ_META(SCR_TAMING,SCR_TAMING),
READ_META(SCR_TELEPORTATION,SCR_TELEPORTATION),
READ_META(SDOOR,SDOOR),
READ_META(SEE_INVIS,SEE_INVIS),
READ_META(SHIELD_OF_REFLECTION,SHIELD_OF_REFLECTION),
READ_META(SILVER_DRAGON_SCALES,SILVER_DRAGON_SCALES),
READ_META(SILVER_DRAGON_SCALE_MAIL,SILVER_DRAGON_SCALE_MAIL),
READ_META(SPBOOK_CLASS,SPBOOK_CLASS),
READ_META(SPE_BLANK_PAPER,SPE_BLANK_PAPER),
READ_META(SPE_BOOK_OF_THE_DEAD,SPE_BOOK_OF_THE_DEAD),
READ_META(SPE_CAUSE_FEAR,SPE_CAUSE_FEAR),
READ_META(SPE_CHARM_MONSTER,SPE_CHARM_MONSTER),
READ_META(SPE_CONFUSE_MONSTER,SPE_CONFUSE_MONSTER),
READ_META(SPE_CREATE_MONSTER,SPE_CREATE_MONSTER),
READ_META(SPE_DETECT_FOOD,SPE_DETECT_FOOD),
READ_META(SPE_IDENTIFY,SPE_IDENTIFY),
READ_META(SPE_LIM,SPE_LIM),
READ_META(SPE_MAGIC_MAPPING,SPE_MAGIC_MAPPING),
READ_META(SPE_NOVEL,SPE_NOVEL),
READ_META(SPE_REMOVE_CURSE,SPE_REMOVE_CURSE),
READ_META(STOMACH,STOMACH),
READ_META(STUNNED,STUNNED),
READ_META(S_EEL,S_EEL),
READ_META(S_GHOST,S_GHOST),
READ_META(S_HUMAN,S_HUMAN),
READ_META(S_MIMIC,S_MIMIC),
READ_META(S_ORC,S_ORC),
READ_META(S_VAMPIRE,S_VAMPIRE),
READ_META(S_VORTEX,S_VORTEX),
READ_META(S_WORM_TAIL,S_WORM_TAIL),
READ_META(S_altar,S_altar),
READ_META(S_arrow_trap,S_arrow_trap),
READ_META(S_digbeam,S_digbeam),
READ_META(S_goodpos,S_goodpos),
READ_META(S_grave,S_grave),
READ_META(S_invisible,S_invisible),
READ_META(S_ndoor,S_ndoor),
READ_META(S_stone,S_stone),
READ_META(S_trwall,S_trwall),
READ_META(S_vwall,S_vwall),
READ_META(TIMEOUT,TIMEOUT),
READ_META(TINNING_KIT,TINNING_KIT),
READ_META(TOOL_CLASS,TOOL_CLASS),
READ_META(TT_BURIEDBALL,TT_BURIEDBALL),
READ_META(T_SHIRT,T_SHIRT),
READ_META(UNCHANGING,UNCHANGING),
READ_META(WAND_CLASS,WAND_CLASS),
READ_META(WAN_CANCELLATION,WAN_CANCELLATION),
READ_META(WAN_COLD,WAN_COLD),
READ_META(WAN_DEATH,WAN_DEATH),
READ_META(WAN_FIRE,WAN_FIRE),
READ_META(WAN_LIGHTNING,WAN_LIGHTNING),
READ_META(WAN_MAGIC_MISSILE,WAN_MAGIC_MISSILE),
READ_META(WAN_NOTHING,WAN_NOTHING),
READ_META(WAN_POLYMORPH,WAN_POLYMORPH),
READ_META(WAN_UNDEAD_TURNING,WAN_UNDEAD_TURNING),
READ_META(WAN_WISHING,WAN_WISHING),
READ_META(WEAPON_CLASS,WEAPON_CLASS),
READ_META(WT_IRON_BALL_INCR,WT_IRON_BALL_INCR),
READ_META(W_ARM,W_ARM),
READ_META(W_ARMH,W_ARMH),
READ_META(W_ART,W_ART),
READ_META(W_ARTI,W_ARTI),
READ_META(W_BALL,W_BALL),
READ_META(W_CHAIN,W_CHAIN),
READ_META(W_SADDLE,W_SADDLE),
READ_META(YELLOW_DRAGON_SCALES,YELLOW_DRAGON_SCALES),
READ_META(ZT_SPELL_O_FIRE,ZT_SPELL_O_FIRE),
READ_META(altar_neutral,altar_neutral),
};
#undef READ_META
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(boolean)==1,"READ native widths");
_Static_assert(sizeof(coordxy)==2 && (coordxy)-1<0,"READ coord width/sign");
_Static_assert(sizeof(enum monnums)==4 && (enum monnums)-1<0,"READ monnum width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1,"READ field width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_subtyp))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->o_id))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->age))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->owornmask))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->corpsenm))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->owt))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->ox))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"READ field width");
_Static_assert((((__typeof__(((struct obj*)0)->oy))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct instance_globals_k*)0)->known)==1,"READ field width");
_Static_assert((((__typeof__(((struct instance_globals_k*)0)->known))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"READ field width");
_Static_assert((((__typeof__(((struct flag*)0)->verbose))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct flag*)0)->debug)==1,"READ field width");
_Static_assert((((__typeof__(((struct flag*)0)->debug))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"READ field width");
_Static_assert((((__typeof__(((struct flag*)0)->female))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"READ field width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"READ field width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"READ field width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->bc_felt)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->bc_felt))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->umconf)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->umconf))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->twoweap))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->utrap))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->utraptype))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->uen)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->uen))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->uenmax))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->uluck)==1,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->uluck))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->moreluck)==1,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->moreluck))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->mh))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"READ field width");
_Static_assert((((__typeof__(((struct you*)0)->uhp))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct u_conduct*)0)->literate)==8,"READ field width");
_Static_assert((((__typeof__(((struct u_conduct*)0)->literate))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"READ field width");
_Static_assert((((__typeof__(((struct Role*)0)->mnum))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"READ field width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"READ field width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"READ field width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"READ field width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"READ field width");
_Static_assert((((__typeof__(((struct monst*)0)->cham))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"READ field width");
_Static_assert((((__typeof__(((struct instance_globals_m*)0)->multi))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"READ field width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vision_full_recalc)==1,"READ field width");
_Static_assert((((__typeof__(((struct instance_globals_v*)0)->vision_full_recalc))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"READ field width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"READ field width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)==2,"READ field width");
_Static_assert((((__typeof__(((struct dgn_topology*)0)->d_sokoban_dnum))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"READ field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"READ field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"READ field width");
_Static_assert((((__typeof__(((struct permonst*)0)->geno))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1,"READ field width");
_Static_assert((((__typeof__(((struct permonst*)0)->msound))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"READ field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"READ field width");
_Static_assert((((__typeof__(((struct mvitals*)0)->mvflags))-1)<0)==0,"READ field sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"READ field width");
_Static_assert((((__typeof__(((struct display_hints*)0)->botl))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((coord*)0)->x)==2,"READ field width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((coord*)0)->y)==2,"READ field width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"READ field width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->last_msg))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct instance_flags*)0)->cmdassist)==1,"READ field width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->cmdassist))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct accessibility_data*)0)->mon_notices_blocked)==4,"READ field width");
_Static_assert((((__typeof__(((struct accessibility_data*)0)->mon_notices_blocked))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1,"READ field width");
_Static_assert((((__typeof__(((struct u_roleplay*)0)->deaf))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct mkroom*)0)->lx)==2,"READ field width");
_Static_assert((((__typeof__(((struct mkroom*)0)->lx))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct mkroom*)0)->hx)==2,"READ field width");
_Static_assert((((__typeof__(((struct mkroom*)0)->hx))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct mkroom*)0)->ly)==2,"READ field width");
_Static_assert((((__typeof__(((struct mkroom*)0)->ly))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct mkroom*)0)->hy)==2,"READ field width");
_Static_assert((((__typeof__(((struct mkroom*)0)->hy))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct mkroom*)0)->rlit)==1,"READ field width");
_Static_assert((((__typeof__(((struct mkroom*)0)->rlit))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"READ field width");
_Static_assert((((__typeof__(((struct Race*)0)->mnum))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct class_sym*)0)->sym)==1,"READ field width");
_Static_assert((((__typeof__(((struct class_sym*)0)->sym))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4,"READ field width");
_Static_assert((((__typeof__(((struct kinfo*)0)->format))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((align*)0)->type)==1,"READ field width");
_Static_assert((((__typeof__(((align*)0)->type))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->quan)==4,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->quan))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->monclass)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->monclass))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->which)==4,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->which))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->fem)==4,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->fem))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->genderconf)==4,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->genderconf))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->randmonst)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->randmonst))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->maketame)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->maketame))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->makepeaceful)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->makepeaceful))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->makehostile)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->makehostile))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->sleeping)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->sleeping))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->saddled)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->saddled))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->invisible)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->invisible))-1)<0)==1,"READ field sign");
_Static_assert(sizeof(((struct _create_particular_data*)0)->hidden)==1,"READ field width");
_Static_assert((((__typeof__(((struct _create_particular_data*)0)->hidden))-1)<0)==1,"READ field sign");
#endif
