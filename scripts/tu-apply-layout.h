#ifndef TELEPORT_APPLY_LAYOUT_H
#define TELEPORT_APPLY_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#if !defined(UNIX) || !defined(DEBUG) || !defined(MAIL) || !defined(MAIL_STRUCTURES)
#error Review changed APPLY configured profile
#endif
#define MAXLEASHED 2
#define SEENMON (MONSEEN_NORMAL | MONSEEN_SEEINVIS | MONSEEN_INFRAVIS)
struct apply_layout_entry {const char *name;long long value;};
#define APPLY_META(k,v) {#k,(long long)(v)}
static const struct apply_layout_entry apply_layout[]={
APPLY_META(pointerSize,sizeof(void*)),
APPLY_META(longSize,sizeof(long)),
APPLY_META(booleanSize,sizeof(boolean)),
APPLY_META(NUMMONS,NUMMONS),
APPLY_META(MAXMCLASSES,MAXMCLASSES),
APPLY_META(R0_size,sizeof(struct you)),
APPLY_META(R0_F0,offsetof(struct you,dx)),
APPLY_META(R0_F0_size,sizeof(((struct you*)0)->dx)),
APPLY_META(R0_F1,offsetof(struct you,dy)),
APPLY_META(R0_F1_size,sizeof(((struct you*)0)->dy)),
APPLY_META(R0_F2,offsetof(struct you,ux)),
APPLY_META(R0_F2_size,sizeof(((struct you*)0)->ux)),
APPLY_META(R0_F3,offsetof(struct you,uy)),
APPLY_META(R0_F3_size,sizeof(((struct you*)0)->uy)),
APPLY_META(R0_F6,offsetof(struct you,ustuck)),
APPLY_META(R0_F6_size,sizeof(((struct you*)0)->ustuck)),
APPLY_META(R0_F7,offsetof(struct you,dz)),
APPLY_META(R0_F7_size,sizeof(((struct you*)0)->dz)),
APPLY_META(R0_F8,offsetof(struct you,uprops)),
APPLY_META(R0_F8_size,sizeof(((struct you*)0)->uprops)),
APPLY_META(R0_F8_stride,sizeof(((struct you*)0)->uprops[0])),
APPLY_META(R0_F9,offsetof(struct you,ucreamed)),
APPLY_META(R0_F9_size,sizeof(((struct you*)0)->ucreamed)),
APPLY_META(R0_F10,offsetof(struct you,uroleplay)),
APPLY_META(R0_F10_size,sizeof(((struct you*)0)->uroleplay)),
APPLY_META(R0_F11,offsetof(struct you,usteed)),
APPLY_META(R0_F11_size,sizeof(((struct you*)0)->usteed)),
APPLY_META(R0_F12,offsetof(struct you,uz)),
APPLY_META(R0_F12_size,sizeof(((struct you*)0)->uz)),
APPLY_META(R0_F13,offsetof(struct you,uconduct)),
APPLY_META(R0_F13_size,sizeof(((struct you*)0)->uconduct)),
APPLY_META(R0_F14,offsetof(struct you,umonnum)),
APPLY_META(R0_F14_size,sizeof(((struct you*)0)->umonnum)),
APPLY_META(R0_F15,offsetof(struct you,ulevel)),
APPLY_META(R0_F15_size,sizeof(((struct you*)0)->ulevel)),
APPLY_META(R0_F16,offsetof(struct you,uhs)),
APPLY_META(R0_F16_size,sizeof(((struct you*)0)->uhs)),
APPLY_META(R0_F17,offsetof(struct you,umonster)),
APPLY_META(R0_F17_size,sizeof(((struct you*)0)->umonster)),
APPLY_META(R0_F19,offsetof(struct you,utrap)),
APPLY_META(R0_F19_size,sizeof(((struct you*)0)->utrap)),
APPLY_META(R0_F20,offsetof(struct you,utraptype)),
APPLY_META(R0_F20_size,sizeof(((struct you*)0)->utraptype)),
APPLY_META(R0_F21,offsetof(struct you,uhunger)),
APPLY_META(R0_F21_size,sizeof(((struct you*)0)->uhunger)),
APPLY_META(R0_F22,offsetof(struct you,weapon_skills)),
APPLY_META(R0_F22_size,sizeof(((struct you*)0)->weapon_skills)),
APPLY_META(R0_F22_stride,sizeof(((struct you*)0)->weapon_skills[0])),
APPLY_META(R0_F23,offsetof(struct you,atemp)),
APPLY_META(R0_F23_size,sizeof(((struct you*)0)->atemp)),
APPLY_META(R1_size,sizeof(struct obj)),
APPLY_META(R1_F0,offsetof(struct obj,ox)),
APPLY_META(R1_F0_size,sizeof(((struct obj*)0)->ox)),
APPLY_META(R1_F1,offsetof(struct obj,oy)),
APPLY_META(R1_F1_size,sizeof(((struct obj*)0)->oy)),
APPLY_META(R1_F2,offsetof(struct obj,otyp)),
APPLY_META(R1_F2_size,sizeof(((struct obj*)0)->otyp)),
APPLY_META(R1_F3,offsetof(struct obj,spe)),
APPLY_META(R1_F3_size,sizeof(((struct obj*)0)->spe)),
APPLY_META(R1_F5,offsetof(struct obj,corpsenm)),
APPLY_META(R1_F5_size,sizeof(((struct obj*)0)->corpsenm)),
APPLY_META(R1_F6,offsetof(struct obj,quan)),
APPLY_META(R1_F6_size,sizeof(((struct obj*)0)->quan)),
APPLY_META(R1_F7,offsetof(struct obj,where)),
APPLY_META(R1_F7_size,sizeof(((struct obj*)0)->where)),
APPLY_META(R1_F8,offsetof(struct obj,v)),
APPLY_META(R1_F8_size,sizeof(((struct obj*)0)->v)),
APPLY_META(R1_F10,offsetof(struct obj,oclass)),
APPLY_META(R1_F10_size,sizeof(((struct obj*)0)->oclass)),
APPLY_META(R1_F11,offsetof(struct obj,cobj)),
APPLY_META(R1_F11_size,sizeof(((struct obj*)0)->cobj)),
APPLY_META(R1_F12,offsetof(struct obj,nobj)),
APPLY_META(R1_F12_size,sizeof(((struct obj*)0)->nobj)),
APPLY_META(R1_F13,offsetof(struct obj,age)),
APPLY_META(R1_F13_size,sizeof(((struct obj*)0)->age)),
APPLY_META(R1_F18,offsetof(struct obj,owt)),
APPLY_META(R1_F18_size,sizeof(((struct obj*)0)->owt)),
APPLY_META(R1_F19,offsetof(struct obj,owornmask)),
APPLY_META(R1_F19_size,sizeof(((struct obj*)0)->owornmask)),
APPLY_META(R1_F21,offsetof(struct obj,invlet)),
APPLY_META(R1_F21_size,sizeof(((struct obj*)0)->invlet)),
APPLY_META(R1_F22,offsetof(struct obj,oeaten)),
APPLY_META(R1_F22_size,sizeof(((struct obj*)0)->oeaten)),
APPLY_META(R1_F26,offsetof(struct obj,timed)),
APPLY_META(R1_F26_size,sizeof(((struct obj*)0)->timed)),
APPLY_META(R1_F27,offsetof(struct obj,oartifact)),
APPLY_META(R1_F27_size,sizeof(((struct obj*)0)->oartifact)),
APPLY_META(R1_F28,offsetof(struct obj,usecount)),
APPLY_META(R1_F28_size,sizeof(((struct obj*)0)->usecount)),
APPLY_META(R2_size,sizeof(struct c_common_strings)),
APPLY_META(R2_F0,offsetof(struct c_common_strings,c_nothing_happens)),
APPLY_META(R2_F0_size,sizeof(((struct c_common_strings*)0)->c_nothing_happens)),
APPLY_META(R2_F1,offsetof(struct c_common_strings,c_nothing_seems_to_happen)),
APPLY_META(R2_F1_size,sizeof(((struct c_common_strings*)0)->c_nothing_seems_to_happen)),
APPLY_META(R2_F2,offsetof(struct c_common_strings,c_something)),
APPLY_META(R2_F2_size,sizeof(((struct c_common_strings*)0)->c_something)),
APPLY_META(R2_F3,offsetof(struct c_common_strings,c_Something)),
APPLY_META(R2_F3_size,sizeof(((struct c_common_strings*)0)->c_Something)),
APPLY_META(R3_size,sizeof(struct prop)),
APPLY_META(R3_F0,offsetof(struct prop,intrinsic)),
APPLY_META(R3_F0_size,sizeof(((struct prop*)0)->intrinsic)),
APPLY_META(R3_F1,offsetof(struct prop,blocked)),
APPLY_META(R3_F1_size,sizeof(((struct prop*)0)->blocked)),
APPLY_META(R3_F2,offsetof(struct prop,extrinsic)),
APPLY_META(R3_F2_size,sizeof(((struct prop*)0)->extrinsic)),
APPLY_META(R4_size,sizeof(struct permonst)),
APPLY_META(R4_F0,offsetof(struct permonst,msize)),
APPLY_META(R4_F0_size,sizeof(((struct permonst*)0)->msize)),
APPLY_META(R4_F1,offsetof(struct permonst,mflags2)),
APPLY_META(R4_F1_size,sizeof(((struct permonst*)0)->mflags2)),
APPLY_META(R4_F2,offsetof(struct permonst,mflags1)),
APPLY_META(R4_F2_size,sizeof(((struct permonst*)0)->mflags1)),
APPLY_META(R4_F3,offsetof(struct permonst,mlet)),
APPLY_META(R4_F3_size,sizeof(((struct permonst*)0)->mlet)),
APPLY_META(R4_F4,offsetof(struct permonst,msound)),
APPLY_META(R4_F4_size,sizeof(((struct permonst*)0)->msound)),
APPLY_META(R4_F5,offsetof(struct permonst,mattk)),
APPLY_META(R4_F5_size,sizeof(((struct permonst*)0)->mattk)),
APPLY_META(R4_F5_stride,sizeof(((struct permonst*)0)->mattk[0])),
APPLY_META(R4_F6,offsetof(struct permonst,cnutrit)),
APPLY_META(R4_F6_size,sizeof(((struct permonst*)0)->cnutrit)),
APPLY_META(R5_size,sizeof(struct monst)),
APPLY_META(R5_F0,offsetof(struct monst,data)),
APPLY_META(R5_F0_size,sizeof(((struct monst*)0)->data)),
APPLY_META(R5_F1,offsetof(struct monst,mnum)),
APPLY_META(R5_F1_size,sizeof(((struct monst*)0)->mnum)),
APPLY_META(R5_F2,offsetof(struct monst,mx)),
APPLY_META(R5_F2_size,sizeof(((struct monst*)0)->mx)),
APPLY_META(R5_F3,offsetof(struct monst,my)),
APPLY_META(R5_F3_size,sizeof(((struct monst*)0)->my)),
APPLY_META(R5_F5,offsetof(struct monst,mappearance)),
APPLY_META(R5_F5_size,sizeof(((struct monst*)0)->mappearance)),
APPLY_META(R5_F6,offsetof(struct monst,m_ap_type)),
APPLY_META(R5_F6_size,sizeof(((struct monst*)0)->m_ap_type)),
APPLY_META(R5_F7,offsetof(struct monst,mextra)),
APPLY_META(R5_F7_size,sizeof(((struct monst*)0)->mextra)),
APPLY_META(R5_F8,offsetof(struct monst,nmon)),
APPLY_META(R5_F8_size,sizeof(((struct monst*)0)->nmon)),
APPLY_META(R5_F9,offsetof(struct monst,mhp)),
APPLY_META(R5_F9_size,sizeof(((struct monst*)0)->mhp)),
APPLY_META(R5_F10,offsetof(struct monst,mtame)),
APPLY_META(R5_F10_size,sizeof(((struct monst*)0)->mtame)),
APPLY_META(R5_F12,offsetof(struct monst,m_id)),
APPLY_META(R5_F12_size,sizeof(((struct monst*)0)->m_id)),
APPLY_META(R5_F15,offsetof(struct monst,cham)),
APPLY_META(R5_F15_size,sizeof(((struct monst*)0)->cham)),
APPLY_META(R5_F19,offsetof(struct monst,m_lev)),
APPLY_META(R5_F19_size,sizeof(((struct monst*)0)->m_lev)),
APPLY_META(R5_F23,offsetof(struct monst,mw)),
APPLY_META(R5_F23_size,sizeof(((struct monst*)0)->mw)),
APPLY_META(R6_size,sizeof(struct Gender)),
APPLY_META(R6_F0,offsetof(struct Gender,he)),
APPLY_META(R6_F0_size,sizeof(((struct Gender*)0)->he)),
APPLY_META(R6_F1,offsetof(struct Gender,his)),
APPLY_META(R6_F1_size,sizeof(((struct Gender*)0)->his)),
APPLY_META(R6_F2,offsetof(struct Gender,him)),
APPLY_META(R6_F2_size,sizeof(((struct Gender*)0)->him)),
APPLY_META(R7_size,sizeof(struct instance_globals_o)),
APPLY_META(R7_F0,offsetof(struct instance_globals_o,otg_otmp)),
APPLY_META(R7_F0_size,sizeof(((struct instance_globals_o*)0)->otg_otmp)),
APPLY_META(R7_F1,offsetof(struct instance_globals_o,otg_temp)),
APPLY_META(R7_F1_size,sizeof(((struct instance_globals_o*)0)->otg_temp)),
APPLY_META(R7_F2,offsetof(struct instance_globals_o,occupation)),
APPLY_META(R7_F2_size,sizeof(((struct instance_globals_o*)0)->occupation)),
APPLY_META(R8_size,sizeof(union vptrs)),
APPLY_META(R8_F0,offsetof(union vptrs,v_nexthere)),
APPLY_META(R8_F0_size,sizeof(((union vptrs*)0)->v_nexthere)),
APPLY_META(R8_F1,offsetof(union vptrs,v_ocarry)),
APPLY_META(R8_F1_size,sizeof(((union vptrs*)0)->v_ocarry)),
APPLY_META(R9_size,sizeof(dlevel_t)),
APPLY_META(R9_F0,offsetof(dlevel_t,objects)),
APPLY_META(R9_F0_size,sizeof(((dlevel_t*)0)->objects)),
APPLY_META(R9_F0_stride,sizeof(((dlevel_t*)0)->objects[0])),
APPLY_META(R9_F1,offsetof(dlevel_t,monsters)),
APPLY_META(R9_F1_size,sizeof(((dlevel_t*)0)->monsters)),
APPLY_META(R9_F1_stride,sizeof(((dlevel_t*)0)->monsters[0])),
APPLY_META(R9_F2,offsetof(dlevel_t,locations)),
APPLY_META(R9_F2_size,sizeof(((dlevel_t*)0)->locations)),
APPLY_META(R9_F2_stride,sizeof(((dlevel_t*)0)->locations[0])),
APPLY_META(R9_F3,offsetof(dlevel_t,flags)),
APPLY_META(R9_F3_size,sizeof(((dlevel_t*)0)->flags)),
APPLY_META(R9_F4,offsetof(dlevel_t,monlist)),
APPLY_META(R9_F4_size,sizeof(((dlevel_t*)0)->monlist)),
APPLY_META(R10_size,sizeof(struct instance_globals_saved_l)),
APPLY_META(R10_F0,offsetof(struct instance_globals_saved_l,level)),
APPLY_META(R10_F0_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
APPLY_META(R11_size,sizeof(struct Role)),
APPLY_META(R11_F0,offsetof(struct Role,mnum)),
APPLY_META(R11_F0_size,sizeof(((struct Role*)0)->mnum)),
APPLY_META(R12_size,sizeof(struct instance_globals_u)),
APPLY_META(R12_F0,offsetof(struct instance_globals_u,urole)),
APPLY_META(R12_F0_size,sizeof(((struct instance_globals_u*)0)->urole)),
APPLY_META(R12_F1,offsetof(struct instance_globals_u,urace)),
APPLY_META(R12_F1_size,sizeof(((struct instance_globals_u*)0)->urace)),
APPLY_META(R13_size,sizeof(struct trap)),
APPLY_META(R13_F2,offsetof(struct trap,tx)),
APPLY_META(R13_F2_size,sizeof(((struct trap*)0)->tx)),
APPLY_META(R13_F3,offsetof(struct trap,ty)),
APPLY_META(R13_F3_size,sizeof(((struct trap*)0)->ty)),
APPLY_META(R14_size,sizeof(struct instance_globals_y)),
APPLY_META(R14_F0,offsetof(struct instance_globals_y,youmonst)),
APPLY_META(R14_F0_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
APPLY_META(R15_size,sizeof(struct u_roleplay)),
APPLY_META(R15_F0,offsetof(struct u_roleplay,deaf)),
APPLY_META(R15_F0_size,sizeof(((struct u_roleplay*)0)->deaf)),
APPLY_META(R16_size,sizeof(struct instance_globals_h)),
APPLY_META(R16_F0,offsetof(struct instance_globals_h,hero_seq)),
APPLY_META(R16_F0_size,sizeof(((struct instance_globals_h*)0)->hero_seq)),
APPLY_META(R17_size,sizeof(struct context_info)),
APPLY_META(R17_F0,offsetof(struct context_info,stethoscope_seq)),
APPLY_META(R17_F0_size,sizeof(((struct context_info*)0)->stethoscope_seq)),
APPLY_META(R17_F1,offsetof(struct context_info,move)),
APPLY_META(R17_F1_size,sizeof(((struct context_info*)0)->move)),
APPLY_META(R17_F2,offsetof(struct context_info,polearm)),
APPLY_META(R17_F2_size,sizeof(((struct context_info*)0)->polearm)),
APPLY_META(R17_F3,offsetof(struct context_info,snickersnee_turn)),
APPLY_META(R17_F3_size,sizeof(((struct context_info*)0)->snickersnee_turn)),
APPLY_META(R18_size,sizeof(struct instance_globals_saved_c)),
APPLY_META(R18_F0,offsetof(struct instance_globals_saved_c,context)),
APPLY_META(R18_F0_size,sizeof(((struct instance_globals_saved_c*)0)->context)),
APPLY_META(R19_size,sizeof(coord)),
APPLY_META(R19_F0,offsetof(coord,x)),
APPLY_META(R19_F0_size,sizeof(((coord*)0)->x)),
APPLY_META(R19_F1,offsetof(coord,y)),
APPLY_META(R19_F1_size,sizeof(((coord*)0)->y)),
APPLY_META(R20_size,sizeof(struct instance_globals_b)),
APPLY_META(R20_F0,offsetof(struct instance_globals_b,bhitpos)),
APPLY_META(R20_F0_size,sizeof(((struct instance_globals_b*)0)->bhitpos)),
APPLY_META(R21_size,sizeof(struct instance_globals_n)),
APPLY_META(R21_F0,offsetof(struct instance_globals_n,notonhead)),
APPLY_META(R21_F0_size,sizeof(((struct instance_globals_n*)0)->notonhead)),
APPLY_META(R21_F1,offsetof(struct instance_globals_n,nomovemsg)),
APPLY_META(R21_F1_size,sizeof(((struct instance_globals_n*)0)->nomovemsg)),
APPLY_META(R22_size,sizeof(d_level)),
APPLY_META(R22_F0,offsetof(d_level,dlevel)),
APPLY_META(R22_F0_size,sizeof(((d_level*)0)->dlevel)),
APPLY_META(R22_F1,offsetof(d_level,dnum)),
APPLY_META(R22_F1_size,sizeof(((d_level*)0)->dnum)),
APPLY_META(R23_size,sizeof(struct dgn_topology)),
APPLY_META(R23_F0,offsetof(struct dgn_topology,d_stronghold_level)),
APPLY_META(R23_F0_size,sizeof(((struct dgn_topology*)0)->d_stronghold_level)),
APPLY_META(R23_F1,offsetof(struct dgn_topology,d_water_level)),
APPLY_META(R23_F1_size,sizeof(((struct dgn_topology*)0)->d_water_level)),
APPLY_META(R23_F2,offsetof(struct dgn_topology,d_knox_level)),
APPLY_META(R23_F2_size,sizeof(((struct dgn_topology*)0)->d_knox_level)),
APPLY_META(R23_F3,offsetof(struct dgn_topology,d_sokoban_dnum)),
APPLY_META(R23_F3_size,sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)),
APPLY_META(R23_F4,offsetof(struct dgn_topology,d_air_level)),
APPLY_META(R23_F4_size,sizeof(((struct dgn_topology*)0)->d_air_level)),
APPLY_META(R24_size,sizeof(struct instance_globals_saved_d)),
APPLY_META(R24_F0,offsetof(struct instance_globals_saved_d,dungeon_topology)),
APPLY_META(R24_F0_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
APPLY_META(R25_size,sizeof(struct mextra)),
APPLY_META(R25_F0,offsetof(struct mextra,mcorpsenm)),
APPLY_META(R25_F0_size,sizeof(((struct mextra*)0)->mcorpsenm)),
APPLY_META(R26_size,sizeof(struct objclass)),
APPLY_META(R26_F0,offsetof(struct objclass,oc_subtyp)),
APPLY_META(R26_F0_size,sizeof(((struct objclass*)0)->oc_subtyp)),
APPLY_META(R26_F2,offsetof(struct objclass,oc_cost)),
APPLY_META(R26_F2_size,sizeof(((struct objclass*)0)->oc_cost)),
APPLY_META(R26_F4,offsetof(struct objclass,oc_color)),
APPLY_META(R26_F4_size,sizeof(((struct objclass*)0)->oc_color)),
APPLY_META(R27_size,sizeof(struct symdef)),
APPLY_META(R27_F0,offsetof(struct symdef,explanation)),
APPLY_META(R27_F0_size,sizeof(((struct symdef*)0)->explanation)),
APPLY_META(R28_size,sizeof(struct flag)),
APPLY_META(R28_F0,offsetof(struct flag,verbose)),
APPLY_META(R28_F0_size,sizeof(((struct flag*)0)->verbose)),
APPLY_META(R28_F1,offsetof(struct flag,female)),
APPLY_META(R28_F1_size,sizeof(((struct flag*)0)->female)),
APPLY_META(R28_F2,offsetof(struct flag,confirm)),
APPLY_META(R28_F2_size,sizeof(((struct flag*)0)->confirm)),
APPLY_META(R28_F3,offsetof(struct flag,paranoia_bits)),
APPLY_META(R28_F3_size,sizeof(((struct flag*)0)->paranoia_bits)),
APPLY_META(R29_size,sizeof(struct rm)),
APPLY_META(R29_F0,offsetof(struct rm,typ)),
APPLY_META(R29_F0_size,sizeof(((struct rm*)0)->typ)),
APPLY_META(R29_F2,offsetof(struct rm,glyph)),
APPLY_META(R29_F2_size,sizeof(((struct rm*)0)->glyph)),
APPLY_META(R30_size,sizeof(struct levelflags)),
APPLY_META(R30_F0,offsetof(struct levelflags,stasis_until)),
APPLY_META(R30_F0_size,sizeof(((struct levelflags*)0)->stasis_until)),
APPLY_META(R31_size,sizeof(struct instance_globals_saved_m)),
APPLY_META(R31_F0,offsetof(struct instance_globals_saved_m,moves)),
APPLY_META(R31_F0_size,sizeof(((struct instance_globals_saved_m*)0)->moves)),
APPLY_META(R31_F1,offsetof(struct instance_globals_saved_m,mvitals)),
APPLY_META(R31_F1_size,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
APPLY_META(R31_F1_stride,sizeof(((struct instance_globals_saved_m*)0)->mvitals[0])),
APPLY_META(R32_size,sizeof(struct instance_flags)),
APPLY_META(R32_F0,offsetof(struct instance_flags,last_msg)),
APPLY_META(R32_F0_size,sizeof(((struct instance_flags*)0)->last_msg)),
APPLY_META(R33_size,sizeof(struct instance_globals_i)),
APPLY_META(R33_F0,offsetof(struct instance_globals_i,invent)),
APPLY_META(R33_F0_size,sizeof(((struct instance_globals_i*)0)->invent)),
APPLY_META(R34_size,sizeof(struct u_conduct)),
APPLY_META(R34_F0,offsetof(struct u_conduct,killer)),
APPLY_META(R34_F0_size,sizeof(((struct u_conduct*)0)->killer)),
APPLY_META(R35_size,sizeof(struct instance_globals_m)),
APPLY_META(R35_F0,offsetof(struct instance_globals_m,multi_reason)),
APPLY_META(R35_F0_size,sizeof(((struct instance_globals_m*)0)->multi_reason)),
APPLY_META(R35_F1,offsetof(struct instance_globals_m,multi)),
APPLY_META(R35_F1_size,sizeof(((struct instance_globals_m*)0)->multi)),
APPLY_META(R36_size,sizeof(struct instance_globals_s)),
APPLY_META(R36_F0,offsetof(struct instance_globals_s,stoned)),
APPLY_META(R36_F0_size,sizeof(((struct instance_globals_s*)0)->stoned)),
APPLY_META(R37_size,sizeof(struct attack)),
APPLY_META(R37_F0,offsetof(struct attack,damd)),
APPLY_META(R37_F0_size,sizeof(((struct attack*)0)->damd)),
APPLY_META(R38_size,sizeof(struct mvitals)),
APPLY_META(R38_F0,offsetof(struct mvitals,mvflags)),
APPLY_META(R38_F0_size,sizeof(((struct mvitals*)0)->mvflags)),
APPLY_META(R39_size,sizeof(struct instance_globals_v)),
APPLY_META(R39_F0,offsetof(struct instance_globals_v,viz_array)),
APPLY_META(R39_F0_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
APPLY_META(R39_F1,offsetof(struct instance_globals_v,vision_full_recalc)),
APPLY_META(R39_F1_size,sizeof(((struct instance_globals_v*)0)->vision_full_recalc)),
APPLY_META(R40_size,sizeof(struct instance_globals_j)),
APPLY_META(R40_F0,offsetof(struct instance_globals_j,jumping_is_magic)),
APPLY_META(R40_F0_size,sizeof(((struct instance_globals_j*)0)->jumping_is_magic)),
APPLY_META(R41_size,sizeof(struct display_hints)),
APPLY_META(R41_F0,offsetof(struct display_hints,botl)),
APPLY_META(R41_F0_size,sizeof(((struct display_hints*)0)->botl)),
APPLY_META(R42_size,sizeof(anything)),
APPLY_META(R42_F0,offsetof(anything,a_obj)),
APPLY_META(R42_F0_size,sizeof(((anything*)0)->a_obj)),
APPLY_META(R42_F1,offsetof(anything,a_int)),
APPLY_META(R42_F1_size,sizeof(((anything*)0)->a_int)),
APPLY_META(R43_size,sizeof(struct Race)),
APPLY_META(R43_F0,offsetof(struct Race,mnum)),
APPLY_META(R43_F0_size,sizeof(((struct Race*)0)->mnum)),
APPLY_META(R44_size,sizeof(struct trapinfo)),
APPLY_META(R44_F0,offsetof(struct trapinfo,tobj)),
APPLY_META(R44_F0_size,sizeof(((struct trapinfo*)0)->tobj)),
APPLY_META(R44_F1,offsetof(struct trapinfo,force_bungle)),
APPLY_META(R44_F1_size,sizeof(((struct trapinfo*)0)->force_bungle)),
APPLY_META(R44_F2,offsetof(struct trapinfo,tx)),
APPLY_META(R44_F2_size,sizeof(((struct trapinfo*)0)->tx)),
APPLY_META(R44_F3,offsetof(struct trapinfo,ty)),
APPLY_META(R44_F3_size,sizeof(((struct trapinfo*)0)->ty)),
APPLY_META(R44_F4,offsetof(struct trapinfo,time_needed)),
APPLY_META(R44_F4_size,sizeof(((struct trapinfo*)0)->time_needed)),
APPLY_META(R45_size,sizeof(struct instance_globals_t)),
APPLY_META(R45_F0,offsetof(struct instance_globals_t,trapinfo)),
APPLY_META(R45_F0_size,sizeof(((struct instance_globals_t*)0)->trapinfo)),
APPLY_META(R46_size,sizeof(stairway)),
APPLY_META(R46_F0,offsetof(stairway,isladder)),
APPLY_META(R46_F0_size,sizeof(((stairway*)0)->isladder)),
APPLY_META(R47_size,sizeof(struct skills)),
APPLY_META(R47_F0,offsetof(struct skills,skill)),
APPLY_META(R47_F0_size,sizeof(((struct skills*)0)->skill)),
APPLY_META(R48_size,sizeof(struct instance_globals_p)),
APPLY_META(R48_F0,offsetof(struct instance_globals_p,polearm_range_max)),
APPLY_META(R48_F0_size,sizeof(((struct instance_globals_p*)0)->polearm_range_max)),
APPLY_META(R48_F1,offsetof(struct instance_globals_p,polearm_range_min)),
APPLY_META(R48_F1_size,sizeof(((struct instance_globals_p*)0)->polearm_range_min)),
APPLY_META(R49_size,sizeof(struct polearm_info)),
APPLY_META(R49_F0,offsetof(struct polearm_info,hitmon)),
APPLY_META(R49_F0_size,sizeof(((struct polearm_info*)0)->hitmon)),
APPLY_META(R50_size,sizeof(struct window_procs)),
APPLY_META(R50_F0,offsetof(struct window_procs,win_create_nhwindow)),
APPLY_META(R50_F0_size,sizeof(((struct window_procs*)0)->win_create_nhwindow)),
APPLY_META(R50_F1,offsetof(struct window_procs,win_start_menu)),
APPLY_META(R50_F1_size,sizeof(((struct window_procs*)0)->win_start_menu)),
APPLY_META(R50_F2,offsetof(struct window_procs,win_end_menu)),
APPLY_META(R50_F2_size,sizeof(((struct window_procs*)0)->win_end_menu)),
APPLY_META(R50_F3,offsetof(struct window_procs,win_destroy_nhwindow)),
APPLY_META(R50_F3_size,sizeof(((struct window_procs*)0)->win_destroy_nhwindow)),
APPLY_META(R51_size,sizeof(struct const_globals)),
APPLY_META(R51_F0,offsetof(struct const_globals,zeroany)),
APPLY_META(R51_F0_size,sizeof(((struct const_globals*)0)->zeroany)),
APPLY_META(R52_size,sizeof(menu_item)),
APPLY_META(R52_F0,offsetof(menu_item,item)),
APPLY_META(R52_F0_size,sizeof(((menu_item*)0)->item)),
APPLY_META(R53_size,sizeof(struct instance_globals_c)),
APPLY_META(R53_F0,offsetof(struct instance_globals_c,current_wand)),
APPLY_META(R53_F0_size,sizeof(((struct instance_globals_c*)0)->current_wand)),
APPLY_META(R54_size,sizeof(struct attribs)),
APPLY_META(R54_F0,offsetof(struct attribs,a)),
APPLY_META(R54_F0_size,sizeof(((struct attribs*)0)->a)),
APPLY_META(R54_F0_stride,sizeof(((struct attribs*)0)->a[0])),
APPLY_META(R55_size,sizeof(struct c_color_names)),
APPLY_META(R55_F0,offsetof(struct c_color_names,c_red)),
APPLY_META(R55_F0_size,sizeof(((struct c_color_names*)0)->c_red)),
APPLY_META(AD_BLND,AD_BLND),
APPLY_META(AD_DGST,AD_DGST),
APPLY_META(AIR,AIR),
APPLY_META(ALTAR,ALTAR),
APPLY_META(AM_CHAOTIC,AM_CHAOTIC),
APPLY_META(AM_LAWFUL,AM_LAWFUL),
APPLY_META(AM_MASK,AM_MASK),
APPLY_META(AM_NEUTRAL,AM_NEUTRAL),
APPLY_META(AM_SANCTUM,AM_SANCTUM),
APPLY_META(ARMOR_CLASS,ARMOR_CLASS),
APPLY_META(ARM_BOOTS,ARM_BOOTS),
APPLY_META(ARM_GLOVES,ARM_GLOVES),
APPLY_META(ARTICLE_A,ARTICLE_A),
APPLY_META(ART_SNICKERSNEE,ART_SNICKERSNEE),
APPLY_META(ATR_NONE,ATR_NONE),
APPLY_META(AT_ENGL,AT_ENGL),
APPLY_META(AT_WEAP,AT_WEAP),
APPLY_META(A_CHA,A_CHA),
APPLY_META(A_CON,A_CON),
APPLY_META(A_DEX,A_DEX),
APPLY_META(A_STR,A_STR),
APPLY_META(BAG_OF_HOLDING,BAG_OF_HOLDING),
APPLY_META(BAG_OF_TRICKS,BAG_OF_TRICKS),
APPLY_META(BANANA,BANANA),
APPLY_META(BEARTRAP,BEARTRAP),
APPLY_META(BEAR_TRAP,BEAR_TRAP),
APPLY_META(BELL,BELL),
APPLY_META(BELL_OF_OPENING,BELL_OF_OPENING),
APPLY_META(BLINDED,BLINDED),
APPLY_META(BLINDFOLD,BLINDFOLD),
APPLY_META(BOULDER,BOULDER),
APPLY_META(BRASS_LANTERN,BRASS_LANTERN),
APPLY_META(BUGLE,BUGLE),
APPLY_META(BULLWHIP,BULLWHIP),
APPLY_META(CANDELABRUM_OF_INVOCATION,CANDELABRUM_OF_INVOCATION),
APPLY_META(CAN_OF_GREASE,CAN_OF_GREASE),
APPLY_META(CHEST,CHEST),
APPLY_META(CLOTH,CLOTH),
APPLY_META(CLOUD,CLOUD),
APPLY_META(COIN_CLASS,COIN_CLASS),
APPLY_META(COLNO,COLNO),
APPLY_META(CONFLICT,CONFLICT),
APPLY_META(CONFUSION,CONFUSION),
APPLY_META(CORPSE,CORPSE),
APPLY_META(CORPSTAT_FEMALE,CORPSTAT_FEMALE),
APPLY_META(CORPSTAT_GENDER,CORPSTAT_GENDER),
APPLY_META(CORR,CORR),
APPLY_META(COST_DSTROY,COST_DSTROY),
APPLY_META(COST_SPLAT,COST_SPLAT),
APPLY_META(COULD_SEE,COULD_SEE),
APPLY_META(CQ_CANNED,CQ_CANNED),
APPLY_META(CREAM_PIE,CREAM_PIE),
APPLY_META(CREDIT_CARD,CREDIT_CARD),
APPLY_META(CRYSTAL_BALL,CRYSTAL_BALL),
APPLY_META(DAGGER,DAGGER),
APPLY_META(DBWALL,DBWALL),
APPLY_META(DEAF,DEAF),
APPLY_META(DIGCHECK_FAILED,DIGCHECK_FAILED),
APPLY_META(DIGCHECK_FAIL_BOULDER,DIGCHECK_FAIL_BOULDER),
APPLY_META(DISP_BEAM,DISP_BEAM),
APPLY_META(DISP_END,DISP_END),
APPLY_META(DOOR,DOOR),
APPLY_META(DRUM_OF_EARTHQUAKE,DRUM_OF_EARTHQUAKE),
APPLY_META(DWARVISH_MATTOCK,DWARVISH_MATTOCK),
APPLY_META(D_ISOPEN,D_ISOPEN),
APPLY_META(ECMD_CANCEL,ECMD_CANCEL),
APPLY_META(ECMD_FAIL,ECMD_FAIL),
APPLY_META(ECMD_OK,ECMD_OK),
APPLY_META(ECMD_TIME,ECMD_TIME),
APPLY_META(EGG,EGG),
APPLY_META(EUCALYPTUS_LEAF,EUCALYPTUS_LEAF),
APPLY_META(EXPENSIVE_CAMERA,EXPENSIVE_CAMERA),
APPLY_META(EXPL_FIERY,EXPL_FIERY),
APPLY_META(EXPL_FROSTY,EXPL_FROSTY),
APPLY_META(EXPL_MAGICAL,EXPL_MAGICAL),
APPLY_META(FACE,FACE),
APPLY_META(FIGURINE,FIGURINE),
APPLY_META(FIG_TRANSFORM,FIG_TRANSFORM),
APPLY_META(FIRE_HORN,FIRE_HORN),
APPLY_META(FIRST_OBJECT,FIRST_OBJECT),
APPLY_META(FIRST_REAL_GEM,FIRST_REAL_GEM),
APPLY_META(FIRST_SPELL,FIRST_SPELL),
APPLY_META(FLASHED_LIGHT,FLASHED_LIGHT),
APPLY_META(FLINT,FLINT),
APPLY_META(FLYING,FLYING),
APPLY_META(FM_FMON,FM_FMON),
APPLY_META(FOOD_CLASS,FOOD_CLASS),
APPLY_META(FOOT,FOOT),
APPLY_META(FORCEBUNGLE,FORCEBUNGLE),
APPLY_META(FORCETRAP,FORCETRAP),
APPLY_META(FREE_ACTION,FREE_ACTION),
APPLY_META(FROST_HORN,FROST_HORN),
APPLY_META(FUMBLING,FUMBLING),
APPLY_META(GEMSTONE,GEMSTONE),
APPLY_META(GEM_CLASS,GEM_CLASS),
APPLY_META(GETOBJ_DOWNPLAY,GETOBJ_DOWNPLAY),
APPLY_META(GETOBJ_EXCLUDE,GETOBJ_EXCLUDE),
APPLY_META(GETOBJ_EXCLUDE_INACCESS,GETOBJ_EXCLUDE_INACCESS),
APPLY_META(GETOBJ_EXCLUDE_SELECTABLE,GETOBJ_EXCLUDE_SELECTABLE),
APPLY_META(GETOBJ_NOFLAGS,GETOBJ_NOFLAGS),
APPLY_META(GETOBJ_PROMPT,GETOBJ_PROMPT),
APPLY_META(GETOBJ_SUGGEST,GETOBJ_SUGGEST),
APPLY_META(GLASS,GLASS),
APPLY_META(GLIB,GLIB),
APPLY_META(GLYPH_ALTAR_OFF,GLYPH_ALTAR_OFF),
APPLY_META(GLYPH_BODY_OFF,GLYPH_BODY_OFF),
APPLY_META(GLYPH_BODY_PILETOP_OFF,GLYPH_BODY_PILETOP_OFF),
APPLY_META(GLYPH_CMAP_A_OFF,GLYPH_CMAP_A_OFF),
APPLY_META(GLYPH_CMAP_B_OFF,GLYPH_CMAP_B_OFF),
APPLY_META(GLYPH_CMAP_C_OFF,GLYPH_CMAP_C_OFF),
APPLY_META(GLYPH_CMAP_GEH_OFF,GLYPH_CMAP_GEH_OFF),
APPLY_META(GLYPH_CMAP_KNOX_OFF,GLYPH_CMAP_KNOX_OFF),
APPLY_META(GLYPH_CMAP_MAIN_OFF,GLYPH_CMAP_MAIN_OFF),
APPLY_META(GLYPH_CMAP_MINES_OFF,GLYPH_CMAP_MINES_OFF),
APPLY_META(GLYPH_CMAP_SOKO_OFF,GLYPH_CMAP_SOKO_OFF),
APPLY_META(GLYPH_CMAP_STONE_OFF,GLYPH_CMAP_STONE_OFF),
APPLY_META(GLYPH_DETECT_FEM_OFF,GLYPH_DETECT_FEM_OFF),
APPLY_META(GLYPH_DETECT_MALE_OFF,GLYPH_DETECT_MALE_OFF),
APPLY_META(GLYPH_INVISIBLE,GLYPH_INVISIBLE),
APPLY_META(GLYPH_MON_FEM_OFF,GLYPH_MON_FEM_OFF),
APPLY_META(GLYPH_MON_MALE_OFF,GLYPH_MON_MALE_OFF),
APPLY_META(GLYPH_OBJ_OFF,GLYPH_OBJ_OFF),
APPLY_META(GLYPH_OBJ_PILETOP_OFF,GLYPH_OBJ_PILETOP_OFF),
APPLY_META(GLYPH_PET_FEM_OFF,GLYPH_PET_FEM_OFF),
APPLY_META(GLYPH_PET_MALE_OFF,GLYPH_PET_MALE_OFF),
APPLY_META(GLYPH_RIDDEN_FEM_OFF,GLYPH_RIDDEN_FEM_OFF),
APPLY_META(GLYPH_RIDDEN_MALE_OFF,GLYPH_RIDDEN_MALE_OFF),
APPLY_META(GLYPH_STATUE_FEM_OFF,GLYPH_STATUE_FEM_OFF),
APPLY_META(GLYPH_STATUE_FEM_PILETOP_OFF,GLYPH_STATUE_FEM_PILETOP_OFF),
APPLY_META(GLYPH_STATUE_MALE_OFF,GLYPH_STATUE_MALE_OFF),
APPLY_META(GLYPH_STATUE_MALE_PILETOP_OFF,GLYPH_STATUE_MALE_PILETOP_OFF),
APPLY_META(GOLD,GOLD),
APPLY_META(GOLD_PIECE,GOLD_PIECE),
APPLY_META(GRAPPLING_HOOK,GRAPPLING_HOOK),
APPLY_META(G_GONE,G_GONE),
APPLY_META(HALBERD,HALBERD),
APPLY_META(HALF_PHDAM,HALF_PHDAM),
APPLY_META(HALLUC,HALLUC),
APPLY_META(HALLUC_RES,HALLUC_RES),
APPLY_META(HAND,HAND),
APPLY_META(HEAD,HEAD),
APPLY_META(HOLE,HOLE),
APPLY_META(HOMEMADE_TIN,HOMEMADE_TIN),
APPLY_META(HORN_OF_PLENTY,HORN_OF_PLENTY),
APPLY_META(ICE,ICE),
APPLY_META(ICE_BOX,ICE_BOX),
APPLY_META(INTRINSIC,INTRINSIC),
APPLY_META(INVIS,INVIS),
APPLY_META(INVIS_BEAM,INVIS_BEAM),
APPLY_META(IN_SIGHT,IN_SIGHT),
APPLY_META(JUMPING,JUMPING),
APPLY_META(KILLED_BY,KILLED_BY),
APPLY_META(LANDMINE,LANDMINE),
APPLY_META(LAND_MINE,LAND_MINE),
APPLY_META(LARGE_BOX,LARGE_BOX),
APPLY_META(LAST_GLASS_GEM,LAST_GLASS_GEM),
APPLY_META(LAST_SPELL,LAST_SPELL),
APPLY_META(LAVAWALL,LAVAWALL),
APPLY_META(LEASH,LEASH),
APPLY_META(LEATHER,LEATHER),
APPLY_META(LEATHER_DRUM,LEATHER_DRUM),
APPLY_META(LEFT_SIDE,LEFT_SIDE),
APPLY_META(LEG,LEG),
APPLY_META(LENSES,LENSES),
APPLY_META(LEVITATION,LEVITATION),
APPLY_META(LIQUID,LIQUID),
APPLY_META(LOADSTONE,LOADSTONE),
APPLY_META(LOCK_PICK,LOCK_PICK),
APPLY_META(LUCKSTONE,LUCKSTONE),
APPLY_META(LUMP_OF_ROYAL_JELLY,LUMP_OF_ROYAL_JELLY),
APPLY_META(M1_BREATHLESS,M1_BREATHLESS),
APPLY_META(M1_CONCEAL,M1_CONCEAL),
APPLY_META(M1_FLY,M1_FLY),
APPLY_META(M1_HUMANOID,M1_HUMANOID),
APPLY_META(M1_NOEYES,M1_NOEYES),
APPLY_META(M1_NOHANDS,M1_NOHANDS),
APPLY_META(M1_NOHEAD,M1_NOHEAD),
APPLY_META(M1_NOLIMBS,M1_NOLIMBS),
APPLY_META(M1_SEE_INVIS,M1_SEE_INVIS),
APPLY_META(M1_SLITHY,M1_SLITHY),
APPLY_META(M1_UNSOLID,M1_UNSOLID),
APPLY_META(M1_WALLWALK,M1_WALLWALK),
APPLY_META(M2_DEMON,M2_DEMON),
APPLY_META(M2_FEMALE,M2_FEMALE),
APPLY_META(M2_JEWELS,M2_JEWELS),
APPLY_META(M2_MALE,M2_MALE),
APPLY_META(M2_PNAME,M2_PNAME),
APPLY_META(M2_ROCKTHROW,M2_ROCKTHROW),
APPLY_META(M2_STRONG,M2_STRONG),
APPLY_META(MAGIC_FLUTE,MAGIC_FLUTE),
APPLY_META(MAGIC_HARP,MAGIC_HARP),
APPLY_META(MAGIC_LAMP,MAGIC_LAMP),
APPLY_META(MAGIC_MARKER,MAGIC_MARKER),
APPLY_META(MAGIC_WHISTLE,MAGIC_WHISTLE),
APPLY_META(MAXLEASHED,MAXLEASHED),
APPLY_META(MAXMCLASSES,MAXMCLASSES),
APPLY_META(MAXTCHARS,MAXTCHARS),
APPLY_META(MAXULEV,MAXULEV),
APPLY_META(MAX_SPELL_STUDY,MAX_SPELL_STUDY),
APPLY_META(MELT_ICE_AWAY,MELT_ICE_AWAY),
APPLY_META(MENU_BEHAVE_STANDARD,MENU_BEHAVE_STANDARD),
APPLY_META(MENU_ITEMFLAGS_NONE,MENU_ITEMFLAGS_NONE),
APPLY_META(MINERAL,MINERAL),
APPLY_META(MIRROR,MIRROR),
APPLY_META(MM_NOMSG,MM_NOMSG),
APPLY_META(MONSEEN_INFRAVIS,MONSEEN_INFRAVIS),
APPLY_META(MS_SILENT,MS_SILENT),
APPLY_META(MZ_LARGE,MZ_LARGE),
APPLY_META(MZ_SMALL,MZ_SMALL),
APPLY_META(MZ_TINY,MZ_TINY),
APPLY_META(M_AP_FURNITURE,M_AP_FURNITURE),
APPLY_META(M_AP_MONSTER,M_AP_MONSTER),
APPLY_META(M_AP_NOTHING,M_AP_NOTHING),
APPLY_META(M_AP_OBJECT,M_AP_OBJECT),
APPLY_META(M_AP_TYPMASK,M_AP_TYPMASK),
APPLY_META(NHW_MENU,NHW_MENU),
APPLY_META(NH_RED,NH_RED),
APPLY_META(NON_PM,NON_PM),
APPLY_META(NOSE,NOSE),
APPLY_META(NO_COLOR,NO_COLOR),
APPLY_META(NO_GLYPH,NO_GLYPH),
APPLY_META(NO_KILLER_PREFIX,NO_KILLER_PREFIX),
APPLY_META(NO_MINVENT,NO_MINVENT),
APPLY_META(NO_MM_FLAGS,NO_MM_FLAGS),
APPLY_META(NO_TRAP_FLAGS,NO_TRAP_FLAGS),
APPLY_META(NUMMONS,NUMMONS),
APPLY_META(NUM_OBJECTS,NUM_OBJECTS),
APPLY_META(N_DIRS,N_DIRS),
APPLY_META(OBJ_FLOOR,OBJ_FLOOR),
APPLY_META(OBJ_INVENT,OBJ_INVENT),
APPLY_META(OBJ_MINVENT,OBJ_MINVENT),
APPLY_META(OILSKIN_SACK,OILSKIN_SACK),
APPLY_META(OIL_LAMP,OIL_LAMP),
APPLY_META(PARANOID_BREAKWAND,PARANOID_BREAKWAND),
APPLY_META(PASSES_WALLS,PASSES_WALLS),
APPLY_META(PICK_AXE,PICK_AXE),
APPLY_META(PICK_ONE,PICK_ONE),
APPLY_META(PIT,PIT),
APPLY_META(PLNMSG_enum,PLNMSG_enum),
APPLY_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
APPLY_META(PM_AMOROUS_DEMON,PM_AMOROUS_DEMON),
APPLY_META(PM_ARCHEOLOGIST,PM_ARCHEOLOGIST),
APPLY_META(PM_CHICKATRICE,PM_CHICKATRICE),
APPLY_META(PM_COCKATRICE,PM_COCKATRICE),
APPLY_META(PM_DEATH,PM_DEATH),
APPLY_META(PM_FAMINE,PM_FAMINE),
APPLY_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
APPLY_META(PM_GNOME,PM_GNOME),
APPLY_META(PM_HEALER,PM_HEALER),
APPLY_META(PM_HORSE,PM_HORSE),
APPLY_META(PM_HUMAN,PM_HUMAN),
APPLY_META(PM_KILLER_BEE,PM_KILLER_BEE),
APPLY_META(PM_LONG_WORM,PM_LONG_WORM),
APPLY_META(PM_MEDUSA,PM_MEDUSA),
APPLY_META(PM_MOUNTAIN_NYMPH,PM_MOUNTAIN_NYMPH),
APPLY_META(PM_PESTILENCE,PM_PESTILENCE),
APPLY_META(PM_QUEEN_BEE,PM_QUEEN_BEE),
APPLY_META(PM_STONE_GOLEM,PM_STONE_GOLEM),
APPLY_META(PM_UMBER_HULK,PM_UMBER_HULK),
APPLY_META(PM_VAMPIRE,PM_VAMPIRE),
APPLY_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
APPLY_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
APPLY_META(PM_WATER_NYMPH,PM_WATER_NYMPH),
APPLY_META(PM_WOOD_NYMPH,PM_WOOD_NYMPH),
APPLY_META(POOL,POOL),
APPLY_META(POTION_CLASS,POTION_CLASS),
APPLY_META(POT_OIL,POT_OIL),
APPLY_META(PRONOUN_HALLU,PRONOUN_HALLU),
APPLY_META(PRONOUN_NO_IT,PRONOUN_NO_IT),
APPLY_META(PROT_FROM_SHAPE_CHANGERS,PROT_FROM_SHAPE_CHANGERS),
APPLY_META(P_AXE,P_AXE),
APPLY_META(P_BASIC,P_BASIC),
APPLY_META(P_LANCE,P_LANCE),
APPLY_META(P_NONE,P_NONE),
APPLY_META(P_PICK_AXE,P_PICK_AXE),
APPLY_META(P_POLEARMS,P_POLEARMS),
APPLY_META(P_RIDING,P_RIDING),
APPLY_META(P_SKILLED,P_SKILLED),
APPLY_META(RANDOM_CLASS,RANDOM_CLASS),
APPLY_META(REVIVE_MON,REVIVE_MON),
APPLY_META(RIGHT_SIDE,RIGHT_SIDE),
APPLY_META(RING_CLASS,RING_CLASS),
APPLY_META(RLOC_MSG,RLOC_MSG),
APPLY_META(RLOC_NOMSG,RLOC_NOMSG),
APPLY_META(RLOC_NONE,RLOC_NONE),
APPLY_META(ROOM,ROOM),
APPLY_META(ROWNO,ROWNO),
APPLY_META(RUBBER_HOSE,RUBBER_HOSE),
APPLY_META(SACK,SACK),
APPLY_META(SADDLE,SADDLE),
APPLY_META(SCORR,SCORR),
APPLY_META(SDOOR,SDOOR),
APPLY_META(SEENMON,SEENMON),
APPLY_META(SEE_INVIS,SEE_INVIS),
APPLY_META(SHOPBASE,SHOPBASE),
APPLY_META(SICK,SICK),
APPLY_META(SICK_ALL,SICK_ALL),
APPLY_META(SICK_NONVOMITABLE,SICK_NONVOMITABLE),
APPLY_META(SILVER,SILVER),
APPLY_META(SKELETON_KEY,SKELETON_KEY),
APPLY_META(SLIMED,SLIMED),
APPLY_META(SLIME_MOLD,SLIME_MOLD),
APPLY_META(SPBOOK_CLASS,SPBOOK_CLASS),
APPLY_META(SPE_BLANK_PAPER,SPE_BLANK_PAPER),
APPLY_META(SPE_BOOK_OF_THE_DEAD,SPE_BOOK_OF_THE_DEAD),
APPLY_META(SPE_JUMPING,SPE_JUMPING),
APPLY_META(SPE_NOVEL,SPE_NOVEL),
APPLY_META(STAIRS,STAIRS),
APPLY_META(STATUE,STATUE),
APPLY_META(STATUE_TRAP,STATUE_TRAP),
APPLY_META(STETHOSCOPE,STETHOSCOPE),
APPLY_META(STOMACH,STOMACH),
APPLY_META(STONE,STONE),
APPLY_META(STONED,STONED),
APPLY_META(STONE_RES,STONE_RES),
APPLY_META(STRANGLED,STRANGLED),
APPLY_META(STUNNED,STUNNED),
APPLY_META(SUPPRESS_INVISIBLE,SUPPRESS_INVISIBLE),
APPLY_META(SUPPRESS_IT,SUPPRESS_IT),
APPLY_META(S_EEL,S_EEL),
APPLY_META(S_EYE,S_EYE),
APPLY_META(S_GHOST,S_GHOST),
APPLY_META(S_LIGHT,S_LIGHT),
APPLY_META(S_MIMIC,S_MIMIC),
APPLY_META(S_NYMPH,S_NYMPH),
APPLY_META(S_UNICORN,S_UNICORN),
APPLY_META(S_VAMPIRE,S_VAMPIRE),
APPLY_META(S_VORTEX,S_VORTEX),
APPLY_META(S_altar,S_altar),
APPLY_META(S_arrow_trap,S_arrow_trap),
APPLY_META(S_digbeam,S_digbeam),
APPLY_META(S_goodpos,S_goodpos),
APPLY_META(S_grave,S_grave),
APPLY_META(S_ndoor,S_ndoor),
APPLY_META(S_stone,S_stone),
APPLY_META(S_trwall,S_trwall),
APPLY_META(S_vwall,S_vwall),
APPLY_META(TALLOW_CANDLE,TALLOW_CANDLE),
APPLY_META(TELEDS_ALLOW_DRAG,TELEDS_ALLOW_DRAG),
APPLY_META(TELEDS_NO_FLAGS,TELEDS_NO_FLAGS),
APPLY_META(TIMEOUT,TIMEOUT),
APPLY_META(TIMER_OBJECT,TIMER_OBJECT),
APPLY_META(TIN,TIN),
APPLY_META(TINNING_KIT,TINNING_KIT),
APPLY_META(TIN_OPENER,TIN_OPENER),
APPLY_META(TIN_WHISTLE,TIN_WHISTLE),
APPLY_META(TOOKPLUNGE,TOOKPLUNGE),
APPLY_META(TOOLED_HORN,TOOLED_HORN),
APPLY_META(TOOL_CLASS,TOOL_CLASS),
APPLY_META(TOUCHSTONE,TOUCHSTONE),
APPLY_META(TOWEL,TOWEL),
APPLY_META(TREE,TREE),
APPLY_META(TT_BEARTRAP,TT_BEARTRAP),
APPLY_META(TT_BURIEDBALL,TT_BURIEDBALL),
APPLY_META(TT_INFLOOR,TT_INFLOOR),
APPLY_META(TT_LAVA,TT_LAVA),
APPLY_META(TT_PIT,TT_PIT),
APPLY_META(TT_WEB,TT_WEB),
APPLY_META(Trap_Killed_Mon,Trap_Killed_Mon),
APPLY_META(UNENCUMBERED,UNENCUMBERED),
APPLY_META(UNICORN_HORN,UNICORN_HORN),
APPLY_META(VOMITING,VOMITING),
APPLY_META(WAND_CLASS,WAND_CLASS),
APPLY_META(WAN_CANCELLATION,WAN_CANCELLATION),
APPLY_META(WAN_COLD,WAN_COLD),
APPLY_META(WAN_CREATE_MONSTER,WAN_CREATE_MONSTER),
APPLY_META(WAN_DEATH,WAN_DEATH),
APPLY_META(WAN_DIGGING,WAN_DIGGING),
APPLY_META(WAN_ENLIGHTENMENT,WAN_ENLIGHTENMENT),
APPLY_META(WAN_FIRE,WAN_FIRE),
APPLY_META(WAN_LIGHT,WAN_LIGHT),
APPLY_META(WAN_LIGHTNING,WAN_LIGHTNING),
APPLY_META(WAN_LOCKING,WAN_LOCKING),
APPLY_META(WAN_MAGIC_MISSILE,WAN_MAGIC_MISSILE),
APPLY_META(WAN_NOTHING,WAN_NOTHING),
APPLY_META(WAN_OPENING,WAN_OPENING),
APPLY_META(WAN_POLYMORPH,WAN_POLYMORPH),
APPLY_META(WAN_PROBING,WAN_PROBING),
APPLY_META(WAN_SECRET_DOOR_DETECTION,WAN_SECRET_DOOR_DETECTION),
APPLY_META(WAN_STASIS,WAN_STASIS),
APPLY_META(WAN_STRIKING,WAN_STRIKING),
APPLY_META(WAN_TELEPORTATION,WAN_TELEPORTATION),
APPLY_META(WAN_UNDEAD_TURNING,WAN_UNDEAD_TURNING),
APPLY_META(WAN_WISHING,WAN_WISHING),
APPLY_META(WATER,WATER),
APPLY_META(WAX,WAX),
APPLY_META(WAX_CANDLE,WAX_CANDLE),
APPLY_META(WEAK,WEAK),
APPLY_META(WEAPON_CLASS,WEAPON_CLASS),
APPLY_META(WOOD,WOOD),
APPLY_META(WOODEN_FLUTE,WOODEN_FLUTE),
APPLY_META(WOODEN_HARP,WOODEN_HARP),
APPLY_META(WOUNDED_LEGS,WOUNDED_LEGS),
APPLY_META(WWALKING,WWALKING),
APPLY_META(XKILL_NOMSG,XKILL_NOMSG),
APPLY_META(altar_chaotic,altar_chaotic),
APPLY_META(altar_lawful,altar_lawful),
APPLY_META(altar_neutral,altar_neutral),
APPLY_META(altar_other,altar_other),
APPLY_META(altar_unaligned,altar_unaligned),
APPLY_META(spe_Fresh,spe_Fresh),
};
#undef APPLY_META
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(boolean)==1,"APPLY native widths");
_Static_assert(sizeof(coordxy)==2 && (coordxy)-1<0,"APPLY coord width/sign");
_Static_assert(sizeof(enum monnums)==4 && (enum monnums)-1<0,"APPLY monnum width/sign");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->dx))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->dy))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->dz)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->dz))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->ucreamed)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->ucreamed))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->ulevel))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->uhs)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->uhs))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->utrap))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->utraptype))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct you*)0)->uhunger))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->ox))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->oy))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->corpsenm))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->where))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->age))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->owt))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->owornmask))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->invlet)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->invlet))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->oeaten)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->oeaten))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->timed)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->timed))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct obj*)0)->usecount)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct obj*)0)->usecount))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct permonst*)0)->msize))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct permonst*)0)->msound))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct permonst*)0)->cnutrit)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct permonst*)0)->cnutrit))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->mnum)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->mnum))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->mappearance))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->m_ap_type))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->m_id))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->cham))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct monst*)0)->m_lev))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_o*)0)->otg_temp)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_o*)0)->otg_temp))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct Role*)0)->mnum))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct trap*)0)->tx)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct trap*)0)->tx))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct trap*)0)->ty)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct trap*)0)->ty))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct u_roleplay*)0)->deaf))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_h*)0)->hero_seq)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_h*)0)->hero_seq))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct context_info*)0)->stethoscope_seq)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct context_info*)0)->stethoscope_seq))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct context_info*)0)->move)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct context_info*)0)->move))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct context_info*)0)->snickersnee_turn)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct context_info*)0)->snickersnee_turn))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((coord*)0)->x)==2,"APPLY field width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((coord*)0)->y)==2,"APPLY field width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_n*)0)->notonhead)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_n*)0)->notonhead))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"APPLY field width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"APPLY field width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct dgn_topology*)0)->d_sokoban_dnum))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct mextra*)0)->mcorpsenm))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_subtyp))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_cost)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_cost))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_color)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_color))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct flag*)0)->verbose))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct flag*)0)->female))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct flag*)0)->confirm)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct flag*)0)->confirm))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct flag*)0)->paranoia_bits)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct flag*)0)->paranoia_bits))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct rm*)0)->glyph))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct levelflags*)0)->stasis_until)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct levelflags*)0)->stasis_until))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->last_msg))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct u_conduct*)0)->killer)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct u_conduct*)0)->killer))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_m*)0)->multi))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->stoned)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_s*)0)->stoned))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct attack*)0)->damd)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct attack*)0)->damd))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct mvitals*)0)->mvflags))-1)<0)==0,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vision_full_recalc)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_v*)0)->vision_full_recalc))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_j*)0)->jumping_is_magic)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_j*)0)->jumping_is_magic))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct display_hints*)0)->botl))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((anything*)0)->a_int)==4,"APPLY field width");
_Static_assert((((__typeof__(((anything*)0)->a_int))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct Race*)0)->mnum))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct trapinfo*)0)->force_bungle)==1,"APPLY field width");
_Static_assert((((__typeof__(((struct trapinfo*)0)->force_bungle))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct trapinfo*)0)->tx)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct trapinfo*)0)->tx))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct trapinfo*)0)->ty)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct trapinfo*)0)->ty))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct trapinfo*)0)->time_needed)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct trapinfo*)0)->time_needed))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((stairway*)0)->isladder)==1,"APPLY field width");
_Static_assert((((__typeof__(((stairway*)0)->isladder))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct skills*)0)->skill)==2,"APPLY field width");
_Static_assert((((__typeof__(((struct skills*)0)->skill))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_p*)0)->polearm_range_max)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_p*)0)->polearm_range_max))-1)<0)==1,"APPLY field sign");
_Static_assert(sizeof(((struct instance_globals_p*)0)->polearm_range_min)==4,"APPLY field width");
_Static_assert((((__typeof__(((struct instance_globals_p*)0)->polearm_range_min))-1)<0)==1,"APPLY field sign");
#endif
