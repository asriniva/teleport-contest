#ifndef TELEPORT_UHITM_LAYOUT_H
#define TELEPORT_UHITM_LAYOUT_H
#include "hack.h"
#include <stddef.h>
#if !defined(UNIX) || !defined(DEBUG) || !defined(MAIL) || !defined(MAIL_STRUCTURES)
#error Review changed UHITM configured profile
#endif

struct uhitm_layout_entry {const char *name;long long value;};
#define UHITM_META(k,v) {#k,(long long)(v)}
static const struct uhitm_layout_entry uhitm_layout[]={
UHITM_META(pointerSize,sizeof(void*)),
UHITM_META(longSize,sizeof(long)),
UHITM_META(booleanSize,sizeof(boolean)),
UHITM_META(NUMMONS,NUMMONS),
UHITM_META(MAXMCLASSES,MAXMCLASSES),
UHITM_META(R0_size,sizeof(struct instance_globals_y)),
UHITM_META(R0_F0,offsetof(struct instance_globals_y,youmonst)),
UHITM_META(R0_F0_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
UHITM_META(R1_size,sizeof(struct monst)),
UHITM_META(R1_F1,offsetof(struct monst,m_id)),
UHITM_META(R1_F1_size,sizeof(((struct monst*)0)->m_id)),
UHITM_META(R1_F2,offsetof(struct monst,mstrategy)),
UHITM_META(R1_F2_size,sizeof(((struct monst*)0)->mstrategy)),
UHITM_META(R1_F4,offsetof(struct monst,data)),
UHITM_META(R1_F4_size,sizeof(((struct monst*)0)->data)),
UHITM_META(R1_F5,offsetof(struct monst,m_ap_type)),
UHITM_META(R1_F5_size,sizeof(((struct monst*)0)->m_ap_type)),
UHITM_META(R1_F7,offsetof(struct monst,mx)),
UHITM_META(R1_F7_size,sizeof(((struct monst*)0)->mx)),
UHITM_META(R1_F8,offsetof(struct monst,my)),
UHITM_META(R1_F8_size,sizeof(((struct monst*)0)->my)),
UHITM_META(R1_F10,offsetof(struct monst,mtame)),
UHITM_META(R1_F10_size,sizeof(((struct monst*)0)->mtame)),
UHITM_META(R1_F20,offsetof(struct monst,mhp)),
UHITM_META(R1_F20_size,sizeof(((struct monst*)0)->mhp)),
UHITM_META(R1_F21,offsetof(struct monst,mhpmax)),
UHITM_META(R1_F21_size,sizeof(((struct monst*)0)->mhpmax)),
UHITM_META(R1_F23,offsetof(struct monst,mw)),
UHITM_META(R1_F23_size,sizeof(((struct monst*)0)->mw)),
UHITM_META(R1_F24,offsetof(struct monst,weapon_check)),
UHITM_META(R1_F24_size,sizeof(((struct monst*)0)->weapon_check)),
UHITM_META(R1_F25,offsetof(struct monst,cham)),
UHITM_META(R1_F25_size,sizeof(((struct monst*)0)->cham)),
UHITM_META(R1_F27,offsetof(struct monst,minvent)),
UHITM_META(R1_F27_size,sizeof(((struct monst*)0)->minvent)),
UHITM_META(R1_F28,offsetof(struct monst,m_lev)),
UHITM_META(R1_F28_size,sizeof(((struct monst*)0)->m_lev)),
UHITM_META(R1_F29,offsetof(struct monst,misc_worn_check)),
UHITM_META(R1_F29_size,sizeof(((struct monst*)0)->misc_worn_check)),
UHITM_META(R1_F31,offsetof(struct monst,mspec_used)),
UHITM_META(R1_F31_size,sizeof(((struct monst*)0)->mspec_used)),
UHITM_META(R1_F33,offsetof(struct monst,meating)),
UHITM_META(R1_F33_size,sizeof(((struct monst*)0)->meating)),
UHITM_META(R1_F34,offsetof(struct monst,mextra)),
UHITM_META(R1_F34_size,sizeof(((struct monst*)0)->mextra)),
UHITM_META(R2_size,sizeof(struct instance_globals_v)),
UHITM_META(R2_F0,offsetof(struct instance_globals_v,vis)),
UHITM_META(R2_F0_size,sizeof(((struct instance_globals_v*)0)->vis)),
UHITM_META(R2_F1,offsetof(struct instance_globals_v,viz_array)),
UHITM_META(R2_F1_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
UHITM_META(R3_size,sizeof(struct instance_globals_m)),
UHITM_META(R3_F0,offsetof(struct instance_globals_m,multireasonbuf)),
UHITM_META(R3_F0_size,sizeof(((struct instance_globals_m*)0)->multireasonbuf)),
UHITM_META(R3_F0_stride,sizeof(((struct instance_globals_m*)0)->multireasonbuf[0])),
UHITM_META(R3_F1,offsetof(struct instance_globals_m,multi_reason)),
UHITM_META(R3_F1_size,sizeof(((struct instance_globals_m*)0)->multi_reason)),
UHITM_META(R3_F2,offsetof(struct instance_globals_m,multi)),
UHITM_META(R3_F2_size,sizeof(((struct instance_globals_m*)0)->multi)),
UHITM_META(R3_F3,offsetof(struct instance_globals_m,m_shot)),
UHITM_META(R3_F3_size,sizeof(((struct instance_globals_m*)0)->m_shot)),
UHITM_META(R3_F4,offsetof(struct instance_globals_m,mkcorpstat_norevive)),
UHITM_META(R3_F4_size,sizeof(((struct instance_globals_m*)0)->mkcorpstat_norevive)),
UHITM_META(R3_F5,offsetof(struct instance_globals_m,mhitu_dieroll)),
UHITM_META(R3_F5_size,sizeof(((struct instance_globals_m*)0)->mhitu_dieroll)),
UHITM_META(R3_F6,offsetof(struct instance_globals_m,mswallower)),
UHITM_META(R3_F6_size,sizeof(((struct instance_globals_m*)0)->mswallower)),
UHITM_META(R4_size,sizeof(struct you)),
UHITM_META(R4_F1,offsetof(struct you,ustuck)),
UHITM_META(R4_F1_size,sizeof(((struct you*)0)->ustuck)),
UHITM_META(R4_F2,offsetof(struct you,uprops)),
UHITM_META(R4_F2_size,sizeof(((struct you*)0)->uprops)),
UHITM_META(R4_F2_stride,sizeof(((struct you*)0)->uprops[0])),
UHITM_META(R4_F3,offsetof(struct you,ux)),
UHITM_META(R4_F3_size,sizeof(((struct you*)0)->ux)),
UHITM_META(R4_F4,offsetof(struct you,uy)),
UHITM_META(R4_F4_size,sizeof(((struct you*)0)->uy)),
UHITM_META(R4_F6,offsetof(struct you,ualign)),
UHITM_META(R4_F6_size,sizeof(((struct you*)0)->ualign)),
UHITM_META(R4_F7,offsetof(struct you,uhitinc)),
UHITM_META(R4_F7_size,sizeof(((struct you*)0)->uhitinc)),
UHITM_META(R4_F8,offsetof(struct you,uluck)),
UHITM_META(R4_F8_size,sizeof(((struct you*)0)->uluck)),
UHITM_META(R4_F9,offsetof(struct you,moreluck)),
UHITM_META(R4_F9_size,sizeof(((struct you*)0)->moreluck)),
UHITM_META(R4_F10,offsetof(struct you,umonnum)),
UHITM_META(R4_F10_size,sizeof(((struct you*)0)->umonnum)),
UHITM_META(R4_F11,offsetof(struct you,umonster)),
UHITM_META(R4_F11_size,sizeof(((struct you*)0)->umonster)),
UHITM_META(R4_F12,offsetof(struct you,ulevel)),
UHITM_META(R4_F12_size,sizeof(((struct you*)0)->ulevel)),
UHITM_META(R4_F13,offsetof(struct you,utrap)),
UHITM_META(R4_F13_size,sizeof(((struct you*)0)->utrap)),
UHITM_META(R4_F14,offsetof(struct you,dx)),
UHITM_META(R4_F14_size,sizeof(((struct you*)0)->dx)),
UHITM_META(R4_F15,offsetof(struct you,dy)),
UHITM_META(R4_F15_size,sizeof(((struct you*)0)->dy)),
UHITM_META(R4_F16,offsetof(struct you,twoweap)),
UHITM_META(R4_F16_size,sizeof(((struct you*)0)->twoweap)),
UHITM_META(R4_F17,offsetof(struct you,uconduct)),
UHITM_META(R4_F17_size,sizeof(((struct you*)0)->uconduct)),
UHITM_META(R4_F18,offsetof(struct you,dz)),
UHITM_META(R4_F18_size,sizeof(((struct you*)0)->dz)),
UHITM_META(R4_F19,offsetof(struct you,umortality)),
UHITM_META(R4_F19_size,sizeof(((struct you*)0)->umortality)),
UHITM_META(R4_F20,offsetof(struct you,weapon_skills)),
UHITM_META(R4_F20_size,sizeof(((struct you*)0)->weapon_skills)),
UHITM_META(R4_F20_stride,sizeof(((struct you*)0)->weapon_skills[0])),
UHITM_META(R4_F21,offsetof(struct you,uroleplay)),
UHITM_META(R4_F21_size,sizeof(((struct you*)0)->uroleplay)),
UHITM_META(R4_F22,offsetof(struct you,usteed)),
UHITM_META(R4_F22_size,sizeof(((struct you*)0)->usteed)),
UHITM_META(R4_F23,offsetof(struct you,udaminc)),
UHITM_META(R4_F23_size,sizeof(((struct you*)0)->udaminc)),
UHITM_META(R4_F24,offsetof(struct you,umconf)),
UHITM_META(R4_F24_size,sizeof(((struct you*)0)->umconf)),
UHITM_META(R4_F26,offsetof(struct you,mh)),
UHITM_META(R4_F26_size,sizeof(((struct you*)0)->mh)),
UHITM_META(R4_F27,offsetof(struct you,uhp)),
UHITM_META(R4_F27_size,sizeof(((struct you*)0)->uhp)),
UHITM_META(R4_F28,offsetof(struct you,uz)),
UHITM_META(R4_F28_size,sizeof(((struct you*)0)->uz)),
UHITM_META(R4_F29,offsetof(struct you,ulycn)),
UHITM_META(R4_F29_size,sizeof(((struct you*)0)->ulycn)),
UHITM_META(R4_F30,offsetof(struct you,uac)),
UHITM_META(R4_F30_size,sizeof(((struct you*)0)->uac)),
UHITM_META(R4_F31,offsetof(struct you,mhmax)),
UHITM_META(R4_F31_size,sizeof(((struct you*)0)->mhmax)),
UHITM_META(R4_F32,offsetof(struct you,uhpmax)),
UHITM_META(R4_F32_size,sizeof(((struct you*)0)->uhpmax)),
UHITM_META(R4_F33,offsetof(struct you,uhppeak)),
UHITM_META(R4_F33_size,sizeof(((struct you*)0)->uhppeak)),
UHITM_META(R4_F34,offsetof(struct you,uhunger)),
UHITM_META(R4_F34_size,sizeof(((struct you*)0)->uhunger)),
UHITM_META(R5_size,sizeof(struct context_info)),
UHITM_META(R5_F0,offsetof(struct context_info,forcefight)),
UHITM_META(R5_F0_size,sizeof(((struct context_info*)0)->forcefight)),
UHITM_META(R5_F1,offsetof(struct context_info,move)),
UHITM_META(R5_F1_size,sizeof(((struct context_info*)0)->move)),
UHITM_META(R5_F2,offsetof(struct context_info,travel)),
UHITM_META(R5_F2_size,sizeof(((struct context_info*)0)->travel)),
UHITM_META(R5_F3,offsetof(struct context_info,run)),
UHITM_META(R5_F3_size,sizeof(((struct context_info*)0)->run)),
UHITM_META(R5_F4,offsetof(struct context_info,mon_moving)),
UHITM_META(R5_F4_size,sizeof(((struct context_info*)0)->mon_moving)),
UHITM_META(R6_size,sizeof(struct instance_globals_saved_c)),
UHITM_META(R6_F0,offsetof(struct instance_globals_saved_c,context)),
UHITM_META(R6_F0_size,sizeof(((struct instance_globals_saved_c*)0)->context)),
UHITM_META(R7_size,sizeof(coord)),
UHITM_META(R7_F0,offsetof(coord,x)),
UHITM_META(R7_F0_size,sizeof(((coord*)0)->x)),
UHITM_META(R7_F1,offsetof(coord,y)),
UHITM_META(R7_F1_size,sizeof(((coord*)0)->y)),
UHITM_META(R8_size,sizeof(struct instance_globals_b)),
UHITM_META(R8_F0,offsetof(struct instance_globals_b,bhitpos)),
UHITM_META(R8_F0_size,sizeof(((struct instance_globals_b*)0)->bhitpos)),
UHITM_META(R9_size,sizeof(struct prop)),
UHITM_META(R9_F0,offsetof(struct prop,intrinsic)),
UHITM_META(R9_F0_size,sizeof(((struct prop*)0)->intrinsic)),
UHITM_META(R9_F1,offsetof(struct prop,extrinsic)),
UHITM_META(R9_F1_size,sizeof(((struct prop*)0)->extrinsic)),
UHITM_META(R9_F2,offsetof(struct prop,blocked)),
UHITM_META(R9_F2_size,sizeof(((struct prop*)0)->blocked)),
UHITM_META(R10_size,sizeof(struct permonst)),
UHITM_META(R10_F0,offsetof(struct permonst,mflags1)),
UHITM_META(R10_F0_size,sizeof(((struct permonst*)0)->mflags1)),
UHITM_META(R10_F1,offsetof(struct permonst,mlet)),
UHITM_META(R10_F1_size,sizeof(((struct permonst*)0)->mlet)),
UHITM_META(R10_F2,offsetof(struct permonst,mflags2)),
UHITM_META(R10_F2_size,sizeof(((struct permonst*)0)->mflags2)),
UHITM_META(R10_F3,offsetof(struct permonst,mlevel)),
UHITM_META(R10_F3_size,sizeof(((struct permonst*)0)->mlevel)),
UHITM_META(R10_F4,offsetof(struct permonst,mmove)),
UHITM_META(R10_F4_size,sizeof(((struct permonst*)0)->mmove)),
UHITM_META(R10_F5,offsetof(struct permonst,msize)),
UHITM_META(R10_F5_size,sizeof(((struct permonst*)0)->msize)),
UHITM_META(R10_F6,offsetof(struct permonst,mattk)),
UHITM_META(R10_F6_size,sizeof(((struct permonst*)0)->mattk)),
UHITM_META(R10_F6_stride,sizeof(((struct permonst*)0)->mattk[0])),
UHITM_META(R10_F7,offsetof(struct permonst,pmidx)),
UHITM_META(R10_F7_size,sizeof(((struct permonst*)0)->pmidx)),
UHITM_META(R10_F8,offsetof(struct permonst,pmnames)),
UHITM_META(R10_F8_size,sizeof(((struct permonst*)0)->pmnames)),
UHITM_META(R10_F8_stride,sizeof(((struct permonst*)0)->pmnames[0])),
UHITM_META(R10_F9,offsetof(struct permonst,geno)),
UHITM_META(R10_F9_size,sizeof(((struct permonst*)0)->geno)),
UHITM_META(R10_F10,offsetof(struct permonst,cwt)),
UHITM_META(R10_F10_size,sizeof(((struct permonst*)0)->cwt)),
UHITM_META(R10_F11,offsetof(struct permonst,cnutrit)),
UHITM_META(R10_F11_size,sizeof(((struct permonst*)0)->cnutrit)),
UHITM_META(R11_size,sizeof(struct c_common_strings)),
UHITM_META(R11_F0,offsetof(struct c_common_strings,c_something)),
UHITM_META(R11_F0_size,sizeof(((struct c_common_strings*)0)->c_something)),
UHITM_META(R11_F1,offsetof(struct c_common_strings,c_vision_clears)),
UHITM_META(R11_F1_size,sizeof(((struct c_common_strings*)0)->c_vision_clears)),
UHITM_META(R11_F2,offsetof(struct c_common_strings,c_You_can_move_again)),
UHITM_META(R11_F2_size,sizeof(((struct c_common_strings*)0)->c_You_can_move_again)),
UHITM_META(R12_size,sizeof(dlevel_t)),
UHITM_META(R12_F0,offsetof(dlevel_t,objects)),
UHITM_META(R12_F0_size,sizeof(((dlevel_t*)0)->objects)),
UHITM_META(R12_F0_stride,sizeof(((dlevel_t*)0)->objects[0])),
UHITM_META(R12_F1,offsetof(dlevel_t,locations)),
UHITM_META(R12_F1_size,sizeof(((dlevel_t*)0)->locations)),
UHITM_META(R12_F1_stride,sizeof(((dlevel_t*)0)->locations[0])),
UHITM_META(R12_F2,offsetof(dlevel_t,monsters)),
UHITM_META(R12_F2_size,sizeof(((dlevel_t*)0)->monsters)),
UHITM_META(R12_F2_stride,sizeof(((dlevel_t*)0)->monsters[0])),
UHITM_META(R13_size,sizeof(struct instance_globals_saved_l)),
UHITM_META(R13_F0,offsetof(struct instance_globals_saved_l,level)),
UHITM_META(R13_F0_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
UHITM_META(R14_size,sizeof(struct flag)),
UHITM_META(R14_F0,offsetof(struct flag,confirm)),
UHITM_META(R14_F0_size,sizeof(((struct flag*)0)->confirm)),
UHITM_META(R14_F1,offsetof(struct flag,paranoia_bits)),
UHITM_META(R14_F1_size,sizeof(((struct flag*)0)->paranoia_bits)),
UHITM_META(R14_F2,offsetof(struct flag,verbose)),
UHITM_META(R14_F2_size,sizeof(((struct flag*)0)->verbose)),
UHITM_META(R14_F3,offsetof(struct flag,moonphase)),
UHITM_META(R14_F3_size,sizeof(((struct flag*)0)->moonphase)),
UHITM_META(R14_F4,offsetof(struct flag,female)),
UHITM_META(R14_F4_size,sizeof(((struct flag*)0)->female)),
UHITM_META(R15_size,sizeof(struct instance_globals_o)),
UHITM_META(R15_F0,offsetof(struct instance_globals_o,override_confirmation)),
UHITM_META(R15_F0_size,sizeof(((struct instance_globals_o*)0)->override_confirmation)),
UHITM_META(R16_size,sizeof(align)),
UHITM_META(R16_F0,offsetof(align,record)),
UHITM_META(R16_F0_size,sizeof(((align*)0)->record)),
UHITM_META(R16_F1,offsetof(align,type)),
UHITM_META(R16_F1_size,sizeof(((align*)0)->type)),
UHITM_META(R17_size,sizeof(struct Role)),
UHITM_META(R17_F0,offsetof(struct Role,mnum)),
UHITM_META(R17_F0_size,sizeof(((struct Role*)0)->mnum)),
UHITM_META(R17_F1,offsetof(struct Role,spelarmr)),
UHITM_META(R17_F1_size,sizeof(((struct Role*)0)->spelarmr)),
UHITM_META(R18_size,sizeof(struct instance_globals_u)),
UHITM_META(R18_F0,offsetof(struct instance_globals_u,urole)),
UHITM_META(R18_F0_size,sizeof(((struct instance_globals_u*)0)->urole)),
UHITM_META(R18_F1,offsetof(struct instance_globals_u,urace)),
UHITM_META(R18_F1_size,sizeof(((struct instance_globals_u*)0)->urace)),
UHITM_META(R18_F2,offsetof(struct instance_globals_u,unweapon)),
UHITM_META(R18_F2_size,sizeof(((struct instance_globals_u*)0)->unweapon)),
UHITM_META(R19_size,sizeof(struct Race)),
UHITM_META(R19_F0,offsetof(struct Race,mnum)),
UHITM_META(R19_F0_size,sizeof(((struct Race*)0)->mnum)),
UHITM_META(R20_size,sizeof(struct rm)),
UHITM_META(R20_F0,offsetof(struct rm,typ)),
UHITM_META(R20_F0_size,sizeof(((struct rm*)0)->typ)),
UHITM_META(R20_F1,offsetof(struct rm,glyph)),
UHITM_META(R20_F1_size,sizeof(((struct rm*)0)->glyph)),
UHITM_META(R21_size,sizeof(struct instance_globals_saved_r)),
UHITM_META(R21_F0,offsetof(struct instance_globals_saved_r,rooms)),
UHITM_META(R21_F0_size,sizeof(((struct instance_globals_saved_r*)0)->rooms)),
UHITM_META(R21_F0_stride,sizeof(((struct instance_globals_saved_r*)0)->rooms[0])),
UHITM_META(R22_size,sizeof(struct instance_globals_n)),
UHITM_META(R22_F0,offsetof(struct instance_globals_n,notonhead)),
UHITM_META(R22_F0_size,sizeof(((struct instance_globals_n*)0)->notonhead)),
UHITM_META(R22_F1,offsetof(struct instance_globals_n,nomovemsg)),
UHITM_META(R22_F1_size,sizeof(((struct instance_globals_n*)0)->nomovemsg)),
UHITM_META(R23_size,sizeof(struct obj)),
UHITM_META(R23_F0,offsetof(struct obj,oclass)),
UHITM_META(R23_F0_size,sizeof(((struct obj*)0)->oclass)),
UHITM_META(R23_F1,offsetof(struct obj,otyp)),
UHITM_META(R23_F1_size,sizeof(((struct obj*)0)->otyp)),
UHITM_META(R23_F2,offsetof(struct obj,quan)),
UHITM_META(R23_F2_size,sizeof(((struct obj*)0)->quan)),
UHITM_META(R23_F5,offsetof(struct obj,oartifact)),
UHITM_META(R23_F5_size,sizeof(((struct obj*)0)->oartifact)),
UHITM_META(R23_F8,offsetof(struct obj,corpsenm)),
UHITM_META(R23_F8_size,sizeof(((struct obj*)0)->corpsenm)),
UHITM_META(R23_F10,offsetof(struct obj,spe)),
UHITM_META(R23_F10_size,sizeof(((struct obj*)0)->spe)),
UHITM_META(R23_F12,offsetof(struct obj,age)),
UHITM_META(R23_F12_size,sizeof(((struct obj*)0)->age)),
UHITM_META(R23_F13,offsetof(struct obj,timed)),
UHITM_META(R23_F13_size,sizeof(((struct obj*)0)->timed)),
UHITM_META(R23_F15,offsetof(struct obj,owt)),
UHITM_META(R23_F15_size,sizeof(((struct obj*)0)->owt)),
UHITM_META(R23_F18,offsetof(struct obj,oextra)),
UHITM_META(R23_F18_size,sizeof(((struct obj*)0)->oextra)),
UHITM_META(R23_F20,offsetof(struct obj,nobj)),
UHITM_META(R23_F20_size,sizeof(((struct obj*)0)->nobj)),
UHITM_META(R23_F21,offsetof(struct obj,owornmask)),
UHITM_META(R23_F21_size,sizeof(((struct obj*)0)->owornmask)),
UHITM_META(R23_F22,offsetof(struct obj,where)),
UHITM_META(R23_F22_size,sizeof(((struct obj*)0)->where)),
UHITM_META(R23_F23,offsetof(struct obj,ox)),
UHITM_META(R23_F23_size,sizeof(((struct obj*)0)->ox)),
UHITM_META(R23_F24,offsetof(struct obj,oy)),
UHITM_META(R23_F24_size,sizeof(((struct obj*)0)->oy)),
UHITM_META(R24_size,sizeof(struct objclass)),
UHITM_META(R24_F0,offsetof(struct objclass,oc_subtyp)),
UHITM_META(R24_F0_size,sizeof(((struct objclass*)0)->oc_subtyp)),
UHITM_META(R25_size,sizeof(struct u_conduct)),
UHITM_META(R25_F0,offsetof(struct u_conduct,weaphit)),
UHITM_META(R25_F0_size,sizeof(((struct u_conduct*)0)->weaphit)),
UHITM_META(R26_size,sizeof(struct attack)),
UHITM_META(R26_F0,offsetof(struct attack,aatyp)),
UHITM_META(R26_F0_size,sizeof(((struct attack*)0)->aatyp)),
UHITM_META(R26_F1,offsetof(struct attack,adtyp)),
UHITM_META(R26_F1_size,sizeof(((struct attack*)0)->adtyp)),
UHITM_META(R26_F2,offsetof(struct attack,damn)),
UHITM_META(R26_F2_size,sizeof(((struct attack*)0)->damn)),
UHITM_META(R26_F3,offsetof(struct attack,damd)),
UHITM_META(R26_F3_size,sizeof(((struct attack*)0)->damd)),
UHITM_META(R27_size,sizeof(struct skills)),
UHITM_META(R27_F0,offsetof(struct skills,skill)),
UHITM_META(R27_F0_size,sizeof(((struct skills*)0)->skill)),
UHITM_META(R28_size,sizeof(struct instance_globals_t)),
UHITM_META(R28_F0,offsetof(struct instance_globals_t,twohits)),
UHITM_META(R28_F0_size,sizeof(((struct instance_globals_t*)0)->twohits)),
UHITM_META(R29_size,sizeof(struct u_roleplay)),
UHITM_META(R29_F0,offsetof(struct u_roleplay,deaf)),
UHITM_META(R29_F0_size,sizeof(((struct u_roleplay*)0)->deaf)),
UHITM_META(R30_size,sizeof(struct _hitmon_data)),
UHITM_META(R30_F0,offsetof(struct _hitmon_data,mdat)),
UHITM_META(R30_F0_size,sizeof(((struct _hitmon_data*)0)->mdat)),
UHITM_META(R30_F1,offsetof(struct _hitmon_data,dmg)),
UHITM_META(R30_F1_size,sizeof(((struct _hitmon_data*)0)->dmg)),
UHITM_META(R30_F2,offsetof(struct _hitmon_data,use_weapon_skill)),
UHITM_META(R30_F2_size,sizeof(((struct _hitmon_data*)0)->use_weapon_skill)),
UHITM_META(R30_F3,offsetof(struct _hitmon_data,train_weapon_skill)),
UHITM_META(R30_F3_size,sizeof(((struct _hitmon_data*)0)->train_weapon_skill)),
UHITM_META(R30_F4,offsetof(struct _hitmon_data,twohits)),
UHITM_META(R30_F4_size,sizeof(((struct _hitmon_data*)0)->twohits)),
UHITM_META(R30_F5,offsetof(struct _hitmon_data,barehand_silver_rings)),
UHITM_META(R30_F5_size,sizeof(((struct _hitmon_data*)0)->barehand_silver_rings)),
UHITM_META(R30_F6,offsetof(struct _hitmon_data,silvermsg)),
UHITM_META(R30_F6_size,sizeof(((struct _hitmon_data*)0)->silvermsg)),
UHITM_META(R30_F7,offsetof(struct _hitmon_data,material)),
UHITM_META(R30_F7_size,sizeof(((struct _hitmon_data*)0)->material)),
UHITM_META(R30_F8,offsetof(struct _hitmon_data,silverobj)),
UHITM_META(R30_F8_size,sizeof(((struct _hitmon_data*)0)->silverobj)),
UHITM_META(R30_F9,offsetof(struct _hitmon_data,thrown)),
UHITM_META(R30_F9_size,sizeof(((struct _hitmon_data*)0)->thrown)),
UHITM_META(R30_F10,offsetof(struct _hitmon_data,hittxt)),
UHITM_META(R30_F10_size,sizeof(((struct _hitmon_data*)0)->hittxt)),
UHITM_META(R30_F11,offsetof(struct _hitmon_data,hand_to_hand)),
UHITM_META(R30_F11_size,sizeof(((struct _hitmon_data*)0)->hand_to_hand)),
UHITM_META(R30_F12,offsetof(struct _hitmon_data,dieroll)),
UHITM_META(R30_F12_size,sizeof(((struct _hitmon_data*)0)->dieroll)),
UHITM_META(R30_F13,offsetof(struct _hitmon_data,doreturn)),
UHITM_META(R30_F13_size,sizeof(((struct _hitmon_data*)0)->doreturn)),
UHITM_META(R30_F14,offsetof(struct _hitmon_data,retval)),
UHITM_META(R30_F14_size,sizeof(((struct _hitmon_data*)0)->retval)),
UHITM_META(R30_F15,offsetof(struct _hitmon_data,lightobj)),
UHITM_META(R30_F15_size,sizeof(((struct _hitmon_data*)0)->lightobj)),
UHITM_META(R30_F16,offsetof(struct _hitmon_data,jousting)),
UHITM_META(R30_F16_size,sizeof(((struct _hitmon_data*)0)->jousting)),
UHITM_META(R30_F17,offsetof(struct _hitmon_data,ispoisoned)),
UHITM_META(R30_F17_size,sizeof(((struct _hitmon_data*)0)->ispoisoned)),
UHITM_META(R30_F18,offsetof(struct _hitmon_data,unarmed)),
UHITM_META(R30_F18_size,sizeof(((struct _hitmon_data*)0)->unarmed)),
UHITM_META(R30_F19,offsetof(struct _hitmon_data,get_dmg_bonus)),
UHITM_META(R30_F19_size,sizeof(((struct _hitmon_data*)0)->get_dmg_bonus)),
UHITM_META(R30_F20,offsetof(struct _hitmon_data,dryit)),
UHITM_META(R30_F20_size,sizeof(((struct _hitmon_data*)0)->dryit)),
UHITM_META(R30_F21,offsetof(struct _hitmon_data,saved_oname)),
UHITM_META(R30_F21_size,sizeof(((struct _hitmon_data*)0)->saved_oname)),
UHITM_META(R30_F21_stride,sizeof(((struct _hitmon_data*)0)->saved_oname[0])),
UHITM_META(R30_F22,offsetof(struct _hitmon_data,unpoisonmsg)),
UHITM_META(R30_F22_size,sizeof(((struct _hitmon_data*)0)->unpoisonmsg)),
UHITM_META(R30_F23,offsetof(struct _hitmon_data,needpoismsg)),
UHITM_META(R30_F23_size,sizeof(((struct _hitmon_data*)0)->needpoismsg)),
UHITM_META(R30_F24,offsetof(struct _hitmon_data,poiskilled)),
UHITM_META(R30_F24_size,sizeof(((struct _hitmon_data*)0)->poiskilled)),
UHITM_META(R30_F25,offsetof(struct _hitmon_data,already_killed)),
UHITM_META(R30_F25_size,sizeof(((struct _hitmon_data*)0)->already_killed)),
UHITM_META(R30_F26,offsetof(struct _hitmon_data,destroyed)),
UHITM_META(R30_F26_size,sizeof(((struct _hitmon_data*)0)->destroyed)),
UHITM_META(R30_F27,offsetof(struct _hitmon_data,offmap)),
UHITM_META(R30_F27_size,sizeof(((struct _hitmon_data*)0)->offmap)),
UHITM_META(R31_size,sizeof(struct mvitals)),
UHITM_META(R31_F0,offsetof(struct mvitals,died)),
UHITM_META(R31_F0_size,sizeof(((struct mvitals*)0)->died)),
UHITM_META(R31_F1,offsetof(struct mvitals,mvflags)),
UHITM_META(R31_F1_size,sizeof(((struct mvitals*)0)->mvflags)),
UHITM_META(R32_size,sizeof(struct instance_globals_saved_m)),
UHITM_META(R32_F0,offsetof(struct instance_globals_saved_m,mvitals)),
UHITM_META(R32_F0_size,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
UHITM_META(R32_F0_stride,sizeof(((struct instance_globals_saved_m*)0)->mvitals[0])),
UHITM_META(R32_F1,offsetof(struct instance_globals_saved_m,moves)),
UHITM_META(R32_F1_size,sizeof(((struct instance_globals_saved_m*)0)->moves)),
UHITM_META(R33_size,sizeof(struct multishot)),
UHITM_META(R33_F0,offsetof(struct multishot,n)),
UHITM_META(R33_F0_size,sizeof(((struct multishot*)0)->n)),
UHITM_META(R33_F1,offsetof(struct multishot,o)),
UHITM_META(R33_F1_size,sizeof(((struct multishot*)0)->o)),
UHITM_META(R34_size,sizeof(struct oextra)),
UHITM_META(R34_F0,offsetof(struct oextra,oname)),
UHITM_META(R34_F0_size,sizeof(((struct oextra*)0)->oname)),
UHITM_META(R35_size,sizeof(struct Gender)),
UHITM_META(R35_F0,offsetof(struct Gender,he)),
UHITM_META(R35_F0_size,sizeof(((struct Gender*)0)->he)),
UHITM_META(R35_F1,offsetof(struct Gender,his)),
UHITM_META(R35_F1_size,sizeof(((struct Gender*)0)->his)),
UHITM_META(R36_size,sizeof(struct mhitm_data)),
UHITM_META(R36_F0,offsetof(struct mhitm_data,hitflags)),
UHITM_META(R36_F0_size,sizeof(((struct mhitm_data*)0)->hitflags)),
UHITM_META(R36_F1,offsetof(struct mhitm_data,damage)),
UHITM_META(R36_F1_size,sizeof(((struct mhitm_data*)0)->damage)),
UHITM_META(R36_F2,offsetof(struct mhitm_data,done)),
UHITM_META(R36_F2_size,sizeof(((struct mhitm_data*)0)->done)),
UHITM_META(R36_F3,offsetof(struct mhitm_data,permdmg)),
UHITM_META(R36_F3_size,sizeof(((struct mhitm_data*)0)->permdmg)),
UHITM_META(R36_F4,offsetof(struct mhitm_data,specialdmg)),
UHITM_META(R36_F4_size,sizeof(((struct mhitm_data*)0)->specialdmg)),
UHITM_META(R36_F5,offsetof(struct mhitm_data,dieroll)),
UHITM_META(R36_F5_size,sizeof(((struct mhitm_data*)0)->dieroll)),
UHITM_META(R37_size,sizeof(struct instance_globals_i)),
UHITM_META(R37_F0,offsetof(struct instance_globals_i,invent)),
UHITM_META(R37_F0_size,sizeof(((struct instance_globals_i*)0)->invent)),
UHITM_META(R38_size,sizeof(struct instance_globals_s)),
UHITM_META(R38_F0,offsetof(struct instance_globals_s,skipdrin)),
UHITM_META(R38_F0_size,sizeof(((struct instance_globals_s*)0)->skipdrin)),
UHITM_META(R39_size,sizeof(d_level)),
UHITM_META(R39_F0,offsetof(d_level,dlevel)),
UHITM_META(R39_F0_size,sizeof(((d_level*)0)->dlevel)),
UHITM_META(R39_F1,offsetof(d_level,dnum)),
UHITM_META(R39_F1_size,sizeof(((d_level*)0)->dnum)),
UHITM_META(R40_size,sizeof(struct dgn_topology)),
UHITM_META(R40_F0,offsetof(struct dgn_topology,d_medusa_level)),
UHITM_META(R40_F0_size,sizeof(((struct dgn_topology*)0)->d_medusa_level)),
UHITM_META(R40_F1,offsetof(struct dgn_topology,d_water_level)),
UHITM_META(R40_F1_size,sizeof(((struct dgn_topology*)0)->d_water_level)),
UHITM_META(R40_F2,offsetof(struct dgn_topology,d_air_level)),
UHITM_META(R40_F2_size,sizeof(((struct dgn_topology*)0)->d_air_level)),
UHITM_META(R41_size,sizeof(struct instance_globals_saved_d)),
UHITM_META(R41_F0,offsetof(struct instance_globals_saved_d,dungeon_topology)),
UHITM_META(R41_F0_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
UHITM_META(R42_size,sizeof(struct kinfo)),
UHITM_META(R42_F0,offsetof(struct kinfo,format)),
UHITM_META(R42_F0_size,sizeof(((struct kinfo*)0)->format)),
UHITM_META(R42_F1,offsetof(struct kinfo,name)),
UHITM_META(R42_F1_size,sizeof(((struct kinfo*)0)->name)),
UHITM_META(R42_F1_stride,sizeof(((struct kinfo*)0)->name[0])),
UHITM_META(R43_size,sizeof(struct instance_globals_saved_k)),
UHITM_META(R43_F0,offsetof(struct instance_globals_saved_k,killer)),
UHITM_META(R43_F0_size,sizeof(((struct instance_globals_saved_k*)0)->killer)),
UHITM_META(R44_size,sizeof(struct display_hints)),
UHITM_META(R44_F0,offsetof(struct display_hints,botl)),
UHITM_META(R44_F0_size,sizeof(((struct display_hints*)0)->botl)),
UHITM_META(R45_size,sizeof(struct edog)),
UHITM_META(R45_F0,offsetof(struct edog,hungrytime)),
UHITM_META(R45_F0_size,sizeof(((struct edog*)0)->hungrytime)),
UHITM_META(R46_size,sizeof(struct mextra)),
UHITM_META(R46_F0,offsetof(struct mextra,edog)),
UHITM_META(R46_F0_size,sizeof(((struct mextra*)0)->edog)),
UHITM_META(R47_size,sizeof(struct sysopt_s)),
UHITM_META(R47_F0,offsetof(struct sysopt_s,seduce)),
UHITM_META(R47_F0_size,sizeof(((struct sysopt_s*)0)->seduce)),
UHITM_META(R48_size,sizeof(struct window_procs)),
UHITM_META(R48_F0,offsetof(struct window_procs,win_delay_output)),
UHITM_META(R48_F0_size,sizeof(((struct window_procs*)0)->win_delay_output)),
UHITM_META(R48_F1,offsetof(struct window_procs,win_display_nhwindow)),
UHITM_META(R48_F1_size,sizeof(((struct window_procs*)0)->win_display_nhwindow)),
UHITM_META(R49_size,sizeof(struct instance_globals_c)),
UHITM_META(R49_F0,offsetof(struct instance_globals_c,corpsenm_digested)),
UHITM_META(R49_F0_size,sizeof(((struct instance_globals_c*)0)->corpsenm_digested)),
UHITM_META(R50_size,sizeof(struct instance_globals_a)),
UHITM_META(R50_F0,offsetof(struct instance_globals_a,afternmv)),
UHITM_META(R50_F0_size,sizeof(((struct instance_globals_a*)0)->afternmv)),
UHITM_META(R51_size,sizeof(struct symdef)),
UHITM_META(R51_F0,offsetof(struct symdef,explanation)),
UHITM_META(R51_F0_size,sizeof(((struct symdef*)0)->explanation)),
UHITM_META(R52_size,sizeof(struct c_color_names)),
UHITM_META(R52_F0,offsetof(struct c_color_names,c_red)),
UHITM_META(R52_F0_size,sizeof(((struct c_color_names*)0)->c_red)),
UHITM_META(R53_size,sizeof(struct mkroom)),
UHITM_META(ACID_RES,ACID_RES),
UHITM_META(ACID_VENOM,ACID_VENOM),
UHITM_META(AD_ACID,AD_ACID),
UHITM_META(AD_BLND,AD_BLND),
UHITM_META(AD_COLD,AD_COLD),
UHITM_META(AD_CONF,AD_CONF),
UHITM_META(AD_CORR,AD_CORR),
UHITM_META(AD_CURS,AD_CURS),
UHITM_META(AD_DCAY,AD_DCAY),
UHITM_META(AD_DETH,AD_DETH),
UHITM_META(AD_DGST,AD_DGST),
UHITM_META(AD_DISE,AD_DISE),
UHITM_META(AD_DRCO,AD_DRCO),
UHITM_META(AD_DRDX,AD_DRDX),
UHITM_META(AD_DREN,AD_DREN),
UHITM_META(AD_DRIN,AD_DRIN),
UHITM_META(AD_DRLI,AD_DRLI),
UHITM_META(AD_DRST,AD_DRST),
UHITM_META(AD_ELEC,AD_ELEC),
UHITM_META(AD_ENCH,AD_ENCH),
UHITM_META(AD_FAMN,AD_FAMN),
UHITM_META(AD_FIRE,AD_FIRE),
UHITM_META(AD_HALU,AD_HALU),
UHITM_META(AD_HEAL,AD_HEAL),
UHITM_META(AD_LEGS,AD_LEGS),
UHITM_META(AD_MAGM,AD_MAGM),
UHITM_META(AD_PEST,AD_PEST),
UHITM_META(AD_PHYS,AD_PHYS),
UHITM_META(AD_PLYS,AD_PLYS),
UHITM_META(AD_POLY,AD_POLY),
UHITM_META(AD_RUST,AD_RUST),
UHITM_META(AD_SAMU,AD_SAMU),
UHITM_META(AD_SEDU,AD_SEDU),
UHITM_META(AD_SGLD,AD_SGLD),
UHITM_META(AD_SITM,AD_SITM),
UHITM_META(AD_SLEE,AD_SLEE),
UHITM_META(AD_SLIM,AD_SLIM),
UHITM_META(AD_SLOW,AD_SLOW),
UHITM_META(AD_SPEL,AD_SPEL),
UHITM_META(AD_SSEX,AD_SSEX),
UHITM_META(AD_STCK,AD_STCK),
UHITM_META(AD_STON,AD_STON),
UHITM_META(AD_STUN,AD_STUN),
UHITM_META(AD_TLPT,AD_TLPT),
UHITM_META(AD_WERE,AD_WERE),
UHITM_META(AD_WRAP,AD_WRAP),
UHITM_META(AMULET_OF_LIFE_SAVING,AMULET_OF_LIFE_SAVING),
UHITM_META(ANTIMAGIC,ANTIMAGIC),
UHITM_META(ARMOR_CLASS,ARMOR_CLASS),
UHITM_META(ARM_SHIELD,ARM_SHIELD),
UHITM_META(ARTICLE_A,ARTICLE_A),
UHITM_META(ARTICLE_THE,ARTICLE_THE),
UHITM_META(ARTICLE_YOUR,ARTICLE_YOUR),
UHITM_META(ART_CLEAVER,ART_CLEAVER),
UHITM_META(ART_EXCALIBUR,ART_EXCALIBUR),
UHITM_META(ART_EYES_OF_THE_OVERWORLD,ART_EYES_OF_THE_OVERWORLD),
UHITM_META(ART_GIANTSLAYER,ART_GIANTSLAYER),
UHITM_META(ART_OGRESMASHER,ART_OGRESMASHER),
UHITM_META(ART_SNICKERSNEE,ART_SNICKERSNEE),
UHITM_META(ART_STORMBRINGER,ART_STORMBRINGER),
UHITM_META(ART_TROLLSBANE,ART_TROLLSBANE),
UHITM_META(AT_BITE,AT_BITE),
UHITM_META(AT_BOOM,AT_BOOM),
UHITM_META(AT_BREA,AT_BREA),
UHITM_META(AT_BUTT,AT_BUTT),
UHITM_META(AT_CLAW,AT_CLAW),
UHITM_META(AT_ENGL,AT_ENGL),
UHITM_META(AT_EXPL,AT_EXPL),
UHITM_META(AT_GAZE,AT_GAZE),
UHITM_META(AT_HUGS,AT_HUGS),
UHITM_META(AT_KICK,AT_KICK),
UHITM_META(AT_MAGC,AT_MAGC),
UHITM_META(AT_NONE,AT_NONE),
UHITM_META(AT_SPIT,AT_SPIT),
UHITM_META(AT_STNG,AT_STNG),
UHITM_META(AT_TENT,AT_TENT),
UHITM_META(AT_TUCH,AT_TUCH),
UHITM_META(AT_WEAP,AT_WEAP),
UHITM_META(A_CON,A_CON),
UHITM_META(A_DEX,A_DEX),
UHITM_META(A_INT,A_INT),
UHITM_META(A_LAWFUL,A_LAWFUL),
UHITM_META(A_STR,A_STR),
UHITM_META(A_WIS,A_WIS),
UHITM_META(BLINDED,BLINDED),
UHITM_META(BLINDING_VENOM,BLINDING_VENOM),
UHITM_META(BOOMERANG,BOOMERANG),
UHITM_META(BOULDER,BOULDER),
UHITM_META(CLOVE_OF_GARLIC,CLOVE_OF_GARLIC),
UHITM_META(COIN_CLASS,COIN_CLASS),
UHITM_META(COLD_RES,COLD_RES),
UHITM_META(CONFUSION,CONFUSION),
UHITM_META(CORPSE,CORPSE),
UHITM_META(CREAM_PIE,CREAM_PIE),
UHITM_META(CXN_ARTICLE,CXN_ARTICLE),
UHITM_META(CXN_PFX_THE,CXN_PFX_THE),
UHITM_META(DAGGER,DAGGER),
UHITM_META(DEAF,DEAF),
UHITM_META(DETECT_MONSTERS,DETECT_MONSTERS),
UHITM_META(DIED,DIED),
UHITM_META(DIR_ERR,DIR_ERR),
UHITM_META(DISMOUNT_KNOCKED,DISMOUNT_KNOCKED),
UHITM_META(DISMOUNT_POLY,DISMOUNT_POLY),
UHITM_META(DISP_ALWAYS,DISP_ALWAYS),
UHITM_META(DISP_END,DISP_END),
UHITM_META(DOOR,DOOR),
UHITM_META(DRAIN_RES,DRAIN_RES),
UHITM_META(DROWNING,DROWNING),
UHITM_META(DUNCE_CAP,DUNCE_CAP),
UHITM_META(ECMD_TIME,ECMD_TIME),
UHITM_META(EF_GREASE,EF_GREASE),
UHITM_META(EF_NONE,EF_NONE),
UHITM_META(EF_VERBOSE,EF_VERBOSE),
UHITM_META(EGG,EGG),
UHITM_META(ELVEN_ARROW,ELVEN_ARROW),
UHITM_META(ELVEN_BOW,ELVEN_BOW),
UHITM_META(ERODE_BURN,ERODE_BURN),
UHITM_META(ERODE_CORRODE,ERODE_CORRODE),
UHITM_META(ERODE_ROT,ERODE_ROT),
UHITM_META(ERODE_RUST,ERODE_RUST),
UHITM_META(ER_NOTHING,ER_NOTHING),
UHITM_META(EXACT_NAME,EXACT_NAME),
UHITM_META(EXPENSIVE_CAMERA,EXPENSIVE_CAMERA),
UHITM_META(EXPL_FIERY,EXPL_FIERY),
UHITM_META(FACE,FACE),
UHITM_META(FAST,FAST),
UHITM_META(FIRE_RES,FIRE_RES),
UHITM_META(FIRST_OBJECT,FIRST_OBJECT),
UHITM_META(FLYING,FLYING),
UHITM_META(FREE_ACTION,FREE_ACTION),
UHITM_META(FUMBLING,FUMBLING),
UHITM_META(GAUNTLETS_OF_POWER,GAUNTLETS_OF_POWER),
UHITM_META(GEMSTONE,GEMSTONE),
UHITM_META(GEM_CLASS,GEM_CLASS),
UHITM_META(GLYPH_BODY_OFF,GLYPH_BODY_OFF),
UHITM_META(GLYPH_BODY_PILETOP_OFF,GLYPH_BODY_PILETOP_OFF),
UHITM_META(GLYPH_CMAP_C_OFF,GLYPH_CMAP_C_OFF),
UHITM_META(GLYPH_CMAP_STONE_OFF,GLYPH_CMAP_STONE_OFF),
UHITM_META(GLYPH_DETECT_FEM_OFF,GLYPH_DETECT_FEM_OFF),
UHITM_META(GLYPH_DETECT_MALE_OFF,GLYPH_DETECT_MALE_OFF),
UHITM_META(GLYPH_INVISIBLE,GLYPH_INVISIBLE),
UHITM_META(GLYPH_MON_FEM_OFF,GLYPH_MON_FEM_OFF),
UHITM_META(GLYPH_MON_MALE_OFF,GLYPH_MON_MALE_OFF),
UHITM_META(GLYPH_OBJ_OFF,GLYPH_OBJ_OFF),
UHITM_META(GLYPH_OBJ_PILETOP_OFF,GLYPH_OBJ_PILETOP_OFF),
UHITM_META(GLYPH_PET_FEM_OFF,GLYPH_PET_FEM_OFF),
UHITM_META(GLYPH_PET_MALE_OFF,GLYPH_PET_MALE_OFF),
UHITM_META(GLYPH_RIDDEN_FEM_OFF,GLYPH_RIDDEN_FEM_OFF),
UHITM_META(GLYPH_RIDDEN_MALE_OFF,GLYPH_RIDDEN_MALE_OFF),
UHITM_META(GLYPH_STATUE_FEM_OFF,GLYPH_STATUE_FEM_OFF),
UHITM_META(GLYPH_STATUE_FEM_PILETOP_OFF,GLYPH_STATUE_FEM_PILETOP_OFF),
UHITM_META(GLYPH_STATUE_MALE_OFF,GLYPH_STATUE_MALE_OFF),
UHITM_META(GLYPH_STATUE_MALE_PILETOP_OFF,GLYPH_STATUE_MALE_PILETOP_OFF),
UHITM_META(GLYPH_WARNING_OFF,GLYPH_WARNING_OFF),
UHITM_META(G_NOCORPSE,G_NOCORPSE),
UHITM_META(G_UNIQ,G_UNIQ),
UHITM_META(HALF_PHDAM,HALF_PHDAM),
UHITM_META(HALLUC,HALLUC),
UHITM_META(HALLUC_RES,HALLUC_RES),
UHITM_META(HAND,HAND),
UHITM_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
UHITM_META(HIGH_PM,HIGH_PM),
UHITM_META(HMON_APPLIED,HMON_APPLIED),
UHITM_META(HMON_KICKED,HMON_KICKED),
UHITM_META(HMON_MELEE,HMON_MELEE),
UHITM_META(HMON_THROWN,HMON_THROWN),
UHITM_META(INVIS,INVIS),
UHITM_META(IN_SIGHT,IN_SIGHT),
UHITM_META(IRON,IRON),
UHITM_META(IRON_CHAIN,IRON_CHAIN),
UHITM_META(IRON_SHOES,IRON_SHOES),
UHITM_META(KATANA,KATANA),
UHITM_META(KILLED_BY,KILLED_BY),
UHITM_META(KILLED_BY_AN,KILLED_BY_AN),
UHITM_META(LEATHER,LEATHER),
UHITM_META(LEFT_SIDE,LEFT_SIDE),
UHITM_META(LEG,LEG),
UHITM_META(LEVITATION,LEVITATION),
UHITM_META(LL_CONDUCT,LL_CONDUCT),
UHITM_META(LOADSTONE,LOADSTONE),
UHITM_META(LOW_BOOTS,LOW_BOOTS),
UHITM_META(LOW_PM,LOW_PM),
UHITM_META(M1_AMORPHOUS,M1_AMORPHOUS),
UHITM_META(M1_AMPHIBIOUS,M1_AMPHIBIOUS),
UHITM_META(M1_ANIMAL,M1_ANIMAL),
UHITM_META(M1_BREATHLESS,M1_BREATHLESS),
UHITM_META(M1_CARNIVORE,M1_CARNIVORE),
UHITM_META(M1_CONCEAL,M1_CONCEAL),
UHITM_META(M1_FLY,M1_FLY),
UHITM_META(M1_HERBIVORE,M1_HERBIVORE),
UHITM_META(M1_HUMANOID,M1_HUMANOID),
UHITM_META(M1_METALLIVORE,M1_METALLIVORE),
UHITM_META(M1_MINDLESS,M1_MINDLESS),
UHITM_META(M1_NOEYES,M1_NOEYES),
UHITM_META(M1_NOHANDS,M1_NOHANDS),
UHITM_META(M1_NOHEAD,M1_NOHEAD),
UHITM_META(M1_SLITHY,M1_SLITHY),
UHITM_META(M1_SWIM,M1_SWIM),
UHITM_META(M1_THICK_HIDE,M1_THICK_HIDE),
UHITM_META(M1_UNSOLID,M1_UNSOLID),
UHITM_META(M1_WALLWALK,M1_WALLWALK),
UHITM_META(M2_DEMON,M2_DEMON),
UHITM_META(M2_ELF,M2_ELF),
UHITM_META(M2_ORC,M2_ORC),
UHITM_META(M2_PNAME,M2_PNAME),
UHITM_META(M2_UNDEAD,M2_UNDEAD),
UHITM_META(M2_WERE,M2_WERE),
UHITM_META(MAGICAL_BREATHING,MAGICAL_BREATHING),
UHITM_META(MAXMCLASSES,MAXMCLASSES),
UHITM_META(MAX_EGG_HATCH_TIME,MAX_EGG_HATCH_TIME),
UHITM_META(METAL,METAL),
UHITM_META(MHID_ALTMON,MHID_ALTMON),
UHITM_META(MIM_OMIT_WAIT,MIM_OMIT_WAIT),
UHITM_META(MIM_REVEAL,MIM_REVEAL),
UHITM_META(MINERAL,MINERAL),
UHITM_META(MIRROR,MIRROR),
UHITM_META(MMOVE_DIED,MMOVE_DIED),
UHITM_META(MON_EXPLODE,MON_EXPLODE),
UHITM_META(MSLOW,MSLOW),
UHITM_META(MZ_LARGE,MZ_LARGE),
UHITM_META(MZ_SMALL,MZ_SMALL),
UHITM_META(M_AP_FURNITURE,M_AP_FURNITURE),
UHITM_META(M_AP_MONSTER,M_AP_MONSTER),
UHITM_META(M_AP_NOTHING,M_AP_NOTHING),
UHITM_META(M_AP_OBJECT,M_AP_OBJECT),
UHITM_META(M_AP_TYPMASK,M_AP_TYPMASK),
UHITM_META(M_ATTK_AGR_DIED,M_ATTK_AGR_DIED),
UHITM_META(M_ATTK_AGR_DONE,M_ATTK_AGR_DONE),
UHITM_META(M_ATTK_DEF_DIED,M_ATTK_DEF_DIED),
UHITM_META(M_ATTK_HIT,M_ATTK_HIT),
UHITM_META(M_ATTK_MISS,M_ATTK_MISS),
UHITM_META(M_SEEN_ACID,M_SEEN_ACID),
UHITM_META(M_SEEN_COLD,M_SEEN_COLD),
UHITM_META(M_SEEN_ELEC,M_SEEN_ELEC),
UHITM_META(M_SEEN_FIRE,M_SEEN_FIRE),
UHITM_META(M_SEEN_MAGR,M_SEEN_MAGR),
UHITM_META(M_SEEN_SLEEP,M_SEEN_SLEEP),
UHITM_META(NATTK,NATTK),
UHITM_META(NC_SHOW_MSG,NC_SHOW_MSG),
UHITM_META(NEED_WEAPON,NEED_WEAPON),
UHITM_META(NEUTRAL,NEUTRAL),
UHITM_META(NEW_MOON,NEW_MOON),
UHITM_META(NON_PM,NON_PM),
UHITM_META(NOTELL,NOTELL),
UHITM_META(NO_KILLER_PREFIX,NO_KILLER_PREFIX),
UHITM_META(NO_MATERIAL,NO_MATERIAL),
UHITM_META(NO_MM_FLAGS,NO_MM_FLAGS),
UHITM_META(NO_NC_FLAGS,NO_NC_FLAGS),
UHITM_META(NO_TRAP_FLAGS,NO_TRAP_FLAGS),
UHITM_META(NUMMONS,NUMMONS),
UHITM_META(NUM_OBJECTS,NUM_OBJECTS),
UHITM_META(N_DIRS,N_DIRS),
UHITM_META(OBJ_FREE,OBJ_FREE),
UHITM_META(OBJ_INVENT,OBJ_INVENT),
UHITM_META(OILSKIN_CLOAK,OILSKIN_CLOAK),
UHITM_META(PAPER,PAPER),
UHITM_META(PARANOID_HIT,PARANOID_HIT),
UHITM_META(PM_AIR_ELEMENTAL,PM_AIR_ELEMENTAL),
UHITM_META(PM_AMOROUS_DEMON,PM_AMOROUS_DEMON),
UHITM_META(PM_ARCHON,PM_ARCHON),
UHITM_META(PM_BABY_LONG_WORM,PM_BABY_LONG_WORM),
UHITM_META(PM_BALROG,PM_BALROG),
UHITM_META(PM_BARBARIAN,PM_BARBARIAN),
UHITM_META(PM_BARBED_DEVIL,PM_BARBED_DEVIL),
UHITM_META(PM_BLACK_PUDDING,PM_BLACK_PUDDING),
UHITM_META(PM_BROWN_PUDDING,PM_BROWN_PUDDING),
UHITM_META(PM_CHICKATRICE,PM_CHICKATRICE),
UHITM_META(PM_CLAY_GOLEM,PM_CLAY_GOLEM),
UHITM_META(PM_COCKATRICE,PM_COCKATRICE),
UHITM_META(PM_DEATH,PM_DEATH),
UHITM_META(PM_ELF,PM_ELF),
UHITM_META(PM_FAMINE,PM_FAMINE),
UHITM_META(PM_FIRE_ELEMENTAL,PM_FIRE_ELEMENTAL),
UHITM_META(PM_FIRE_VORTEX,PM_FIRE_VORTEX),
UHITM_META(PM_FLAMING_SPHERE,PM_FLAMING_SPHERE),
UHITM_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
UHITM_META(PM_FOG_CLOUD,PM_FOG_CLOUD),
UHITM_META(PM_GHOUL,PM_GHOUL),
UHITM_META(PM_GIANT_EEL,PM_GIANT_EEL),
UHITM_META(PM_GREEN_SLIME,PM_GREEN_SLIME),
UHITM_META(PM_GREMLIN,PM_GREMLIN),
UHITM_META(PM_GRID_BUG,PM_GRID_BUG),
UHITM_META(PM_HEALER,PM_HEALER),
UHITM_META(PM_HOMUNCULUS,PM_HOMUNCULUS),
UHITM_META(PM_HUMAN,PM_HUMAN),
UHITM_META(PM_IRON_GOLEM,PM_IRON_GOLEM),
UHITM_META(PM_KNIGHT,PM_KNIGHT),
UHITM_META(PM_KOBOLD,PM_KOBOLD),
UHITM_META(PM_LEATHER_GOLEM,PM_LEATHER_GOLEM),
UHITM_META(PM_LICH,PM_LICH),
UHITM_META(PM_LONG_WORM,PM_LONG_WORM),
UHITM_META(PM_LONG_WORM_TAIL,PM_LONG_WORM_TAIL),
UHITM_META(PM_MANES,PM_MANES),
UHITM_META(PM_MEDUSA,PM_MEDUSA),
UHITM_META(PM_MONK,PM_MONK),
UHITM_META(PM_ORC,PM_ORC),
UHITM_META(PM_PAPER_GOLEM,PM_PAPER_GOLEM),
UHITM_META(PM_PESTILENCE,PM_PESTILENCE),
UHITM_META(PM_PURPLE_WORM,PM_PURPLE_WORM),
UHITM_META(PM_PYROLISK,PM_PYROLISK),
UHITM_META(PM_RED_DRAGON,PM_RED_DRAGON),
UHITM_META(PM_ROGUE,PM_ROGUE),
UHITM_META(PM_ROPE_GOLEM,PM_ROPE_GOLEM),
UHITM_META(PM_SALAMANDER,PM_SALAMANDER),
UHITM_META(PM_SAMURAI,PM_SAMURAI),
UHITM_META(PM_SHADE,PM_SHADE),
UHITM_META(PM_SHRIEKER,PM_SHRIEKER),
UHITM_META(PM_STEAM_VORTEX,PM_STEAM_VORTEX),
UHITM_META(PM_STONE_GOLEM,PM_STONE_GOLEM),
UHITM_META(PM_STRAW_GOLEM,PM_STRAW_GOLEM),
UHITM_META(PM_VAMPIRE,PM_VAMPIRE),
UHITM_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
UHITM_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
UHITM_META(PM_WATCHMAN,PM_WATCHMAN),
UHITM_META(PM_WATCH_CAPTAIN,PM_WATCH_CAPTAIN),
UHITM_META(PM_WOOD_GOLEM,PM_WOOD_GOLEM),
UHITM_META(POISON_RES,POISON_RES),
UHITM_META(POOL,POOL),
UHITM_META(POTHIT_HERO_BASH,POTHIT_HERO_BASH),
UHITM_META(POTHIT_HERO_THROW,POTHIT_HERO_THROW),
UHITM_META(POTION_CLASS,POTION_CLASS),
UHITM_META(PRONOUN_HALLU,PRONOUN_HALLU),
UHITM_META(PROT_FROM_SHAPE_CHANGERS,PROT_FROM_SHAPE_CHANGERS),
UHITM_META(P_AXE,P_AXE),
UHITM_META(P_BARE_HANDED_COMBAT,P_BARE_HANDED_COMBAT),
UHITM_META(P_BASIC,P_BASIC),
UHITM_META(P_BOOMERANG,P_BOOMERANG),
UHITM_META(P_BOW,P_BOW),
UHITM_META(P_CROSSBOW,P_CROSSBOW),
UHITM_META(P_DAGGER,P_DAGGER),
UHITM_META(P_DART,P_DART),
UHITM_META(P_ISRESTRICTED,P_ISRESTRICTED),
UHITM_META(P_KNIFE,P_KNIFE),
UHITM_META(P_LANCE,P_LANCE),
UHITM_META(P_NONE,P_NONE),
UHITM_META(P_POLEARMS,P_POLEARMS),
UHITM_META(P_SABER,P_SABER),
UHITM_META(P_SHURIKEN,P_SHURIKEN),
UHITM_META(P_SKILLED,P_SKILLED),
UHITM_META(P_TWO_WEAPON_COMBAT,P_TWO_WEAPON_COMBAT),
UHITM_META(P_UNSKILLED,P_UNSKILLED),
UHITM_META(P_WHIP,P_WHIP),
UHITM_META(RIGHT_SIDE,RIGHT_SIDE),
UHITM_META(RING_CLASS,RING_CLASS),
UHITM_META(RLOC_MSG,RLOC_MSG),
UHITM_META(RLOC_NOMSG,RLOC_NOMSG),
UHITM_META(ROCK,ROCK),
UHITM_META(ROOMOFFSET,ROOMOFFSET),
UHITM_META(RUBBER_HOSE,RUBBER_HOSE),
UHITM_META(SEE_INVIS,SEE_INVIS),
UHITM_META(SHOCK_RES,SHOCK_RES),
UHITM_META(SHOPBASE,SHOPBASE),
UHITM_META(SICK,SICK),
UHITM_META(SICK_ALL,SICK_ALL),
UHITM_META(SICK_RES,SICK_RES),
UHITM_META(SILVER,SILVER),
UHITM_META(SLEEP_RES,SLEEP_RES),
UHITM_META(SLIMED,SLIMED),
UHITM_META(SLOW_DIGESTION,SLOW_DIGESTION),
UHITM_META(SPBOOK_CLASS,SPBOOK_CLASS),
UHITM_META(STOMACH,STOMACH),
UHITM_META(STONED,STONED),
UHITM_META(STONE_RES,STONE_RES),
UHITM_META(STONING,STONING),
UHITM_META(STRANGE_OBJECT,STRANGE_OBJECT),
UHITM_META(STRAT_WAITFORU,STRAT_WAITFORU),
UHITM_META(STRAT_WAITMASK,STRAT_WAITMASK),
UHITM_META(STUNNED,STUNNED),
UHITM_META(SUPPRESS_HALLUCINATION,SUPPRESS_HALLUCINATION),
UHITM_META(SUPPRESS_INVISIBLE,SUPPRESS_INVISIBLE),
UHITM_META(SUPPRESS_IT,SUPPRESS_IT),
UHITM_META(SUPPRESS_NAME,SUPPRESS_NAME),
UHITM_META(SUPPRESS_SADDLE,SUPPRESS_SADDLE),
UHITM_META(SWIMMING,SWIMMING),
UHITM_META(S_BLOB,S_BLOB),
UHITM_META(S_EEL,S_EEL),
UHITM_META(S_EYE,S_EYE),
UHITM_META(S_FUNGUS,S_FUNGUS),
UHITM_META(S_GHOST,S_GHOST),
UHITM_META(S_GNOME,S_GNOME),
UHITM_META(S_GOLEM,S_GOLEM),
UHITM_META(S_HUMAN,S_HUMAN),
UHITM_META(S_KOBOLD,S_KOBOLD),
UHITM_META(S_LEPRECHAUN,S_LEPRECHAUN),
UHITM_META(S_LICH,S_LICH),
UHITM_META(S_LIGHT,S_LIGHT),
UHITM_META(S_MIMIC,S_MIMIC),
UHITM_META(S_MUMMY,S_MUMMY),
UHITM_META(S_NAGA,S_NAGA),
UHITM_META(S_NYMPH,S_NYMPH),
UHITM_META(S_ORC,S_ORC),
UHITM_META(S_SNAKE,S_SNAKE),
UHITM_META(S_TROLL,S_TROLL),
UHITM_META(S_VORTEX,S_VORTEX),
UHITM_META(S_ZOMBIE,S_ZOMBIE),
UHITM_META(S_digbeam,S_digbeam),
UHITM_META(S_goodpos,S_goodpos),
UHITM_META(S_trapped_chest,S_trapped_chest),
UHITM_META(TELEPAT,TELEPAT),
UHITM_META(TELEPORT_CONTROL,TELEPORT_CONTROL),
UHITM_META(TEST_MOVE,TEST_MOVE),
UHITM_META(TIMEOUT,TIMEOUT),
UHITM_META(TOOL_CLASS,TOOL_CLASS),
UHITM_META(TOWEL,TOWEL),
UHITM_META(UNCHANGING,UNCHANGING),
UHITM_META(VEGGY,VEGGY),
UHITM_META(WAN_LIGHT,WAN_LIGHT),
UHITM_META(WARNCOUNT,WARNCOUNT),
UHITM_META(WEAPON_CLASS,WEAPON_CLASS),
UHITM_META(WHACK,WHACK),
UHITM_META(W_AMUL,W_AMUL),
UHITM_META(W_ARM,W_ARM),
UHITM_META(W_ARMC,W_ARMC),
UHITM_META(W_ARMF,W_ARMF),
UHITM_META(W_ARMG,W_ARMG),
UHITM_META(W_ARMH,W_ARMH),
UHITM_META(W_ARMS,W_ARMS),
UHITM_META(W_ARMU,W_ARMU),
UHITM_META(W_RINGL,W_RINGL),
UHITM_META(W_RINGR,W_RINGR),
UHITM_META(W_SADDLE,W_SADDLE),
UHITM_META(W_WEP,W_WEP),
UHITM_META(XKILL_GIVEMSG,XKILL_GIVEMSG),
UHITM_META(XKILL_NOCORPSE,XKILL_NOCORPSE),
UHITM_META(XKILL_NOMSG,XKILL_NOMSG),
UHITM_META(YA,YA),
UHITM_META(YUMI,YUMI),
UHITM_META(invlet_basic,invlet_basic),
};
#undef UHITM_META
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(boolean)==1,"UHITM native widths");
_Static_assert(sizeof(coordxy)==2 && (coordxy)-1<0,"UHITM coord width/sign");
_Static_assert(sizeof(enum monnums)==4 && (enum monnums)-1<0,"UHITM monnum width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->m_id))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->mstrategy)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->mstrategy))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->m_ap_type))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->mx))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->my))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->mhpmax))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->weapon_check)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->weapon_check))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->cham))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->m_lev))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->misc_worn_check))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->mspec_used))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct monst*)0)->meating)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct monst*)0)->meating))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vis)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_v*)0)->vis))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_m*)0)->multi))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->mkcorpstat_norevive)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_m*)0)->mkcorpstat_norevive))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->mhitu_dieroll)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_m*)0)->mhitu_dieroll))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uhitinc)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uhitinc))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uluck)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uluck))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->moreluck)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->moreluck))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->ulevel))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->utrap))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->dx))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->dy))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->twoweap))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->dz)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->dz))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->umortality)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->umortality))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->udaminc)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->udaminc))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->umconf)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->umconf))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->mh))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uhp))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->ulycn)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->ulycn))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uac)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uac))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->mhmax))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uhpmax))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uhppeak)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uhppeak))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct you*)0)->uhunger))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct context_info*)0)->forcefight)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct context_info*)0)->forcefight))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct context_info*)0)->move)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct context_info*)0)->move))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct context_info*)0)->travel)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct context_info*)0)->travel))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct context_info*)0)->run)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct context_info*)0)->run))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct context_info*)0)->mon_moving)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct context_info*)0)->mon_moving))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((coord*)0)->x)==2,"UHITM field width");
_Static_assert((((__typeof__(((coord*)0)->x))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((coord*)0)->y)==2,"UHITM field width");
_Static_assert((((__typeof__(((coord*)0)->y))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags1))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlevel))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->mmove)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->mmove))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->msize))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->geno))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->cwt)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->cwt))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct permonst*)0)->cnutrit)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct permonst*)0)->cnutrit))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct flag*)0)->confirm)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct flag*)0)->confirm))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct flag*)0)->paranoia_bits)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct flag*)0)->paranoia_bits))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct flag*)0)->verbose))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct flag*)0)->moonphase)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct flag*)0)->moonphase))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct flag*)0)->female))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_o*)0)->override_confirmation)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_o*)0)->override_confirmation))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((align*)0)->record)==4,"UHITM field width");
_Static_assert((((__typeof__(((align*)0)->record))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((align*)0)->type)==1,"UHITM field width");
_Static_assert((((__typeof__(((align*)0)->type))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct Role*)0)->mnum))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct Role*)0)->spelarmr)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct Role*)0)->spelarmr))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_u*)0)->unweapon)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_u*)0)->unweapon))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct Race*)0)->mnum))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct rm*)0)->glyph))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_n*)0)->notonhead)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_n*)0)->notonhead))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->corpsenm))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->age))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->timed)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->timed))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->owt))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->owornmask))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->where))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->ox))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct obj*)0)->oy))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_subtyp))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct u_conduct*)0)->weaphit)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct u_conduct*)0)->weaphit))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct attack*)0)->aatyp))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct attack*)0)->adtyp)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct attack*)0)->adtyp))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct attack*)0)->damn)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct attack*)0)->damn))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct attack*)0)->damd)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct attack*)0)->damd))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct skills*)0)->skill)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct skills*)0)->skill))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_t*)0)->twohits)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_t*)0)->twohits))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct u_roleplay*)0)->deaf))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->dmg)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->dmg))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->use_weapon_skill)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->use_weapon_skill))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->train_weapon_skill)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->train_weapon_skill))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->twohits)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->twohits))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->barehand_silver_rings)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->barehand_silver_rings))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->silvermsg)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->silvermsg))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->material)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->material))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->silverobj)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->silverobj))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->thrown)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->thrown))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->hittxt)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->hittxt))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->hand_to_hand)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->hand_to_hand))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->dieroll)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->dieroll))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->doreturn)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->doreturn))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->retval)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->retval))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->lightobj)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->lightobj))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->jousting)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->jousting))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->ispoisoned)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->ispoisoned))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->unarmed)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->unarmed))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->get_dmg_bonus)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->get_dmg_bonus))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->dryit)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->dryit))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->unpoisonmsg)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->unpoisonmsg))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->needpoismsg)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->needpoismsg))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->poiskilled)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->poiskilled))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->already_killed)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->already_killed))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->destroyed)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->destroyed))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct _hitmon_data*)0)->offmap)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct _hitmon_data*)0)->offmap))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct mvitals*)0)->died)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct mvitals*)0)->died))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct mvitals*)0)->mvflags))-1)<0)==0,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct multishot*)0)->n)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct multishot*)0)->n))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct multishot*)0)->o)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct multishot*)0)->o))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->hitflags)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->hitflags))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->damage)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->damage))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->done)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->done))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->permdmg)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->permdmg))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->specialdmg)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->specialdmg))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct mhitm_data*)0)->dieroll)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct mhitm_data*)0)->dieroll))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->skipdrin)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_s*)0)->skipdrin))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"UHITM field width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"UHITM field width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct kinfo*)0)->format))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"UHITM field width");
_Static_assert((((__typeof__(((struct display_hints*)0)->botl))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8,"UHITM field width");
_Static_assert((((__typeof__(((struct edog*)0)->hungrytime))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->seduce)==4,"UHITM field width");
_Static_assert((((__typeof__(((struct sysopt_s*)0)->seduce))-1)<0)==1,"UHITM field sign");
_Static_assert(sizeof(((struct instance_globals_c*)0)->corpsenm_digested)==2,"UHITM field width");
_Static_assert((((__typeof__(((struct instance_globals_c*)0)->corpsenm_digested))-1)<0)==1,"UHITM field sign");
#endif
