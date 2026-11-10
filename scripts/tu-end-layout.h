#ifndef TELEPORT_END_LAYOUT_H
#define TELEPORT_END_LAYOUT_H
#include "hack.h"
#include "wintty.h"
#include <stddef.h>
#include <signal.h>
#ifdef DUMPLOG
#error END DUMPLOG profile requires reviewed functions and bodies
#endif
#if !defined(UNIX) || !defined(HANGUPHANDLING) || !defined(PANICTRACE) || !defined(CRASHREPORT) || !defined(NOMUX_CAPTURE)
#error Review changed END configured profile
#endif
struct end_layout_entry {const char *name;long long value;};
#define END_META(k,v) {#k,(long long)(v)}
static const struct end_layout_entry end_layout[]={
END_META(pointerSize,sizeof(void*)),
END_META(longSize,sizeof(long)),
END_META(booleanSize,sizeof(boolean)),
END_META(kinfoSize,sizeof(struct kinfo)),
END_META(valuableSize,sizeof(struct valuable_data)),
END_META(lootSize,sizeof(Loot)),
END_META(valListSize,sizeof(struct val_list)),
END_META(MultiReasonSize,sizeof gm.multireasonbuf),
END_META(R0_size,sizeof(struct instance_flags)),
END_META(R0_F0,offsetof(struct instance_flags,debug_fuzzer)),
END_META(R0_F0_size,sizeof(((struct instance_flags*)0)->debug_fuzzer)),
END_META(R0_F1,offsetof(struct instance_flags,window_inited)),
END_META(R0_F1_size,sizeof(((struct instance_flags*)0)->window_inited)),
END_META(R0_F2,offsetof(struct instance_flags,force_invmenu)),
END_META(R0_F2_size,sizeof(((struct instance_flags*)0)->force_invmenu)),
END_META(R0_F3,offsetof(struct instance_flags,perm_invent)),
END_META(R0_F3_size,sizeof(((struct instance_flags*)0)->perm_invent)),
END_META(R0_F4,offsetof(struct instance_flags,last_msg)),
END_META(R0_F4_size,sizeof(((struct instance_flags*)0)->last_msg)),
END_META(R0_F5,offsetof(struct instance_flags,vision_inited)),
END_META(R0_F5_size,sizeof(((struct instance_flags*)0)->vision_inited)),
END_META(R0_F6,offsetof(struct instance_flags,at_night)),
END_META(R0_F6_size,sizeof(((struct instance_flags*)0)->at_night)),
END_META(R0_F7,offsetof(struct instance_flags,at_midnight)),
END_META(R0_F7_size,sizeof(((struct instance_flags*)0)->at_midnight)),
END_META(R0_F8,offsetof(struct instance_flags,toptenwin)),
END_META(R0_F8_size,sizeof(((struct instance_flags*)0)->toptenwin)),
END_META(R0_F9,offsetof(struct instance_flags,in_dumplog)),
END_META(R0_F9_size,sizeof(((struct instance_flags*)0)->in_dumplog)),
END_META(R1_size,sizeof(struct flag)),
END_META(R1_F0,offsetof(struct flag,ignintr)),
END_META(R1_F0_size,sizeof(((struct flag*)0)->ignintr)),
END_META(R1_F1,offsetof(struct flag,paranoia_bits)),
END_META(R1_F1_size,sizeof(((struct flag*)0)->paranoia_bits)),
END_META(R1_F2,offsetof(struct flag,debug)),
END_META(R1_F2_size,sizeof(((struct flag*)0)->debug)),
END_META(R1_F3,offsetof(struct flag,end_disclose)),
END_META(R1_F3_size,sizeof(((struct flag*)0)->end_disclose)),
END_META(R1_F3_stride,sizeof(((struct flag*)0)->end_disclose[0])),
END_META(R1_F4,offsetof(struct flag,explore)),
END_META(R1_F4_size,sizeof(((struct flag*)0)->explore)),
END_META(R1_F5,offsetof(struct flag,beginner)),
END_META(R1_F5_size,sizeof(((struct flag*)0)->beginner)),
END_META(R1_F6,offsetof(struct flag,female)),
END_META(R1_F6_size,sizeof(((struct flag*)0)->female)),
END_META(R1_F7,offsetof(struct flag,tombstone)),
END_META(R1_F7_size,sizeof(((struct flag*)0)->tombstone)),
END_META(R1_F8,offsetof(struct flag,sortloot)),
END_META(R1_F8_size,sizeof(((struct flag*)0)->sortloot)),
END_META(R1_F9,offsetof(struct flag,sortpack)),
END_META(R1_F9_size,sizeof(((struct flag*)0)->sortpack)),
END_META(R2_size,sizeof(struct window_procs)),
END_META(R2_F0,offsetof(struct window_procs,win_clear_nhwindow)),
END_META(R2_F0_size,sizeof(((struct window_procs*)0)->win_clear_nhwindow)),
END_META(R2_F1,offsetof(struct window_procs,win_wait_synch)),
END_META(R2_F1_size,sizeof(((struct window_procs*)0)->win_wait_synch)),
END_META(R2_F2,offsetof(struct window_procs,win_exit_nhwindows)),
END_META(R2_F2_size,sizeof(((struct window_procs*)0)->win_exit_nhwindows)),
END_META(R2_F3,offsetof(struct window_procs,win_mark_synch)),
END_META(R2_F3_size,sizeof(((struct window_procs*)0)->win_mark_synch)),
END_META(R2_F4,offsetof(struct window_procs,win_raw_print)),
END_META(R2_F4_size,sizeof(((struct window_procs*)0)->win_raw_print)),
END_META(R2_F5,offsetof(struct window_procs,win_putstr)),
END_META(R2_F5_size,sizeof(((struct window_procs*)0)->win_putstr)),
END_META(R2_F6,offsetof(struct window_procs,win_display_nhwindow)),
END_META(R2_F6_size,sizeof(((struct window_procs*)0)->win_display_nhwindow)),
END_META(R2_F7,offsetof(struct window_procs,win_destroy_nhwindow)),
END_META(R2_F7_size,sizeof(((struct window_procs*)0)->win_destroy_nhwindow)),
END_META(R2_F8,offsetof(struct window_procs,win_create_nhwindow)),
END_META(R2_F8_size,sizeof(((struct window_procs*)0)->win_create_nhwindow)),
END_META(R2_F9,offsetof(struct window_procs,win_outrip)),
END_META(R2_F9_size,sizeof(((struct window_procs*)0)->win_outrip)),
END_META(R3_size,sizeof(struct instance_globals_m)),
END_META(R3_F0,offsetof(struct instance_globals_m,multi)),
END_META(R3_F0_size,sizeof(((struct instance_globals_m*)0)->multi)),
END_META(R3_F1,offsetof(struct instance_globals_m,multi_reason)),
END_META(R3_F1_size,sizeof(((struct instance_globals_m*)0)->multi_reason)),
END_META(R3_F2,offsetof(struct instance_globals_m,multireasonbuf)),
END_META(R3_F2_size,sizeof(((struct instance_globals_m*)0)->multireasonbuf)),
END_META(R3_F2_stride,sizeof(((struct instance_globals_m*)0)->multireasonbuf[0])),
END_META(R3_F3,offsetof(struct instance_globals_m,mydogs)),
END_META(R3_F3_size,sizeof(((struct instance_globals_m*)0)->mydogs)),
END_META(R4_size,sizeof(d_level)),
END_META(R4_F0,offsetof(d_level,dnum)),
END_META(R4_F0_size,sizeof(((d_level*)0)->dnum)),
END_META(R4_F1,offsetof(d_level,dlevel)),
END_META(R4_F1_size,sizeof(((d_level*)0)->dlevel)),
END_META(R5_size,sizeof(struct you)),
END_META(R5_F0,offsetof(struct you,uz)),
END_META(R5_F0_size,sizeof(((struct you*)0)->uz)),
END_META(R5_F2,offsetof(struct you,usleep)),
END_META(R5_F2_size,sizeof(((struct you*)0)->usleep)),
END_META(R5_F3,offsetof(struct you,ucamefrom)),
END_META(R5_F3_size,sizeof(((struct you*)0)->ucamefrom)),
END_META(R5_F4,offsetof(struct you,uprops)),
END_META(R5_F4_size,sizeof(((struct you*)0)->uprops)),
END_META(R5_F4_stride,sizeof(((struct you*)0)->uprops[0])),
END_META(R5_F5,offsetof(struct you,ugrave_arise)),
END_META(R5_F5_size,sizeof(((struct you*)0)->ugrave_arise)),
END_META(R5_F6,offsetof(struct you,ulevel)),
END_META(R5_F6_size,sizeof(((struct you*)0)->ulevel)),
END_META(R5_F7,offsetof(struct you,uhpmax)),
END_META(R5_F7_size,sizeof(((struct you*)0)->uhpmax)),
END_META(R5_F8,offsetof(struct you,uhp)),
END_META(R5_F8_size,sizeof(((struct you*)0)->uhp)),
END_META(R5_F9,offsetof(struct you,umonnum)),
END_META(R5_F9_size,sizeof(((struct you*)0)->umonnum)),
END_META(R5_F10,offsetof(struct you,umonster)),
END_META(R5_F10_size,sizeof(((struct you*)0)->umonster)),
END_META(R5_F11,offsetof(struct you,mh)),
END_META(R5_F11_size,sizeof(((struct you*)0)->mh)),
END_META(R5_F12,offsetof(struct you,mhmax)),
END_META(R5_F12_size,sizeof(((struct you*)0)->mhmax)),
END_META(R5_F13,offsetof(struct you,uhunger)),
END_META(R5_F13_size,sizeof(((struct you*)0)->uhunger)),
END_META(R5_F14,offsetof(struct you,utrap)),
END_META(R5_F14_size,sizeof(((struct you*)0)->utrap)),
END_META(R5_F15,offsetof(struct you,utraptype)),
END_META(R5_F15_size,sizeof(((struct you*)0)->utraptype)),
END_META(R5_F17,offsetof(struct you,ustuck)),
END_META(R5_F17_size,sizeof(((struct you*)0)->ustuck)),
END_META(R5_F18,offsetof(struct you,ux)),
END_META(R5_F18_size,sizeof(((struct you*)0)->ux)),
END_META(R5_F19,offsetof(struct you,dx)),
END_META(R5_F19_size,sizeof(((struct you*)0)->dx)),
END_META(R5_F20,offsetof(struct you,uy)),
END_META(R5_F20_size,sizeof(((struct you*)0)->uy)),
END_META(R5_F21,offsetof(struct you,dy)),
END_META(R5_F21_size,sizeof(((struct you*)0)->dy)),
END_META(R5_F22,offsetof(struct you,urexp)),
END_META(R5_F22_size,sizeof(((struct you*)0)->urexp)),
END_META(R5_F23,offsetof(struct you,ulycn)),
END_META(R5_F23_size,sizeof(((struct you*)0)->ulycn)),
END_META(R5_F24,offsetof(struct you,umortality)),
END_META(R5_F24_size,sizeof(((struct you*)0)->umortality)),
END_META(R5_F25,offsetof(struct you,uachieved)),
END_META(R5_F25_size,sizeof(((struct you*)0)->uachieved)),
END_META(R5_F25_stride,sizeof(((struct you*)0)->uachieved[0])),
END_META(R5_F26,offsetof(struct you,uroleplay)),
END_META(R5_F26_size,sizeof(((struct you*)0)->uroleplay)),
END_META(R5_F27,offsetof(struct you,umoney0)),
END_META(R5_F27_size,sizeof(((struct you*)0)->umoney0)),
END_META(R5_F28,offsetof(struct you,ualign)),
END_META(R5_F28_size,sizeof(((struct you*)0)->ualign)),
END_META(R5_F29,offsetof(struct you,ualignbase)),
END_META(R5_F29_size,sizeof(((struct you*)0)->ualignbase)),
END_META(R5_F29_stride,sizeof(((struct you*)0)->ualignbase[0])),
END_META(R5_F31,offsetof(struct you,uhave)),
END_META(R5_F31_size,sizeof(((struct you*)0)->uhave)),
END_META(R6_size,sizeof(struct dgn_topology)),
END_META(R6_F0,offsetof(struct dgn_topology,d_tutorial_dnum)),
END_META(R6_F0_size,sizeof(((struct dgn_topology*)0)->d_tutorial_dnum)),
END_META(R6_F1,offsetof(struct dgn_topology,d_astral_level)),
END_META(R6_F1_size,sizeof(((struct dgn_topology*)0)->d_astral_level)),
END_META(R7_size,sizeof(struct instance_globals_saved_d)),
END_META(R7_F0,offsetof(struct instance_globals_saved_d,dungeon_topology)),
END_META(R7_F0_size,sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology)),
END_META(R7_F1,offsetof(struct instance_globals_saved_d,dungeons)),
END_META(R7_F1_size,sizeof(((struct instance_globals_saved_d*)0)->dungeons)),
END_META(R7_F1_stride,sizeof(((struct instance_globals_saved_d*)0)->dungeons[0])),
END_META(R8_size,sizeof(struct sound_procs)),
END_META(R8_F0,offsetof(struct sound_procs,sound_exit_nhsound)),
END_META(R8_F0_size,sizeof(((struct sound_procs*)0)->sound_exit_nhsound)),
END_META(R9_size,sizeof(struct sinfo)),
END_META(R9_F0,offsetof(struct sinfo,stopprint)),
END_META(R9_F0_size,sizeof(((struct sinfo*)0)->stopprint)),
END_META(R9_F1,offsetof(struct sinfo,done_hup)),
END_META(R9_F1_size,sizeof(((struct sinfo*)0)->done_hup)),
END_META(R9_F2,offsetof(struct sinfo,panicking)),
END_META(R9_F2_size,sizeof(((struct sinfo*)0)->panicking)),
END_META(R9_F3,offsetof(struct sinfo,gameover)),
END_META(R9_F3_size,sizeof(((struct sinfo*)0)->gameover)),
END_META(R9_F4,offsetof(struct sinfo,something_worth_saving)),
END_META(R9_F4_size,sizeof(((struct sinfo*)0)->something_worth_saving)),
END_META(R9_F5,offsetof(struct sinfo,in_moveloop)),
END_META(R9_F5_size,sizeof(((struct sinfo*)0)->in_moveloop)),
END_META(R9_F6,offsetof(struct sinfo,exiting)),
END_META(R9_F6_size,sizeof(((struct sinfo*)0)->exiting)),
END_META(R10_size,sizeof(struct monst)),
END_META(R10_F0,offsetof(struct monst,data)),
END_META(R10_F0_size,sizeof(((struct monst*)0)->data)),
END_META(R10_F1,offsetof(struct monst,cham)),
END_META(R10_F1_size,sizeof(((struct monst*)0)->cham)),
END_META(R10_F2,offsetof(struct monst,m_ap_type)),
END_META(R10_F2_size,sizeof(((struct monst*)0)->m_ap_type)),
END_META(R10_F4,offsetof(struct monst,mextra)),
END_META(R10_F4_size,sizeof(((struct monst*)0)->mextra)),
END_META(R10_F6,offsetof(struct monst,mappearance)),
END_META(R10_F6_size,sizeof(((struct monst*)0)->mappearance)),
END_META(R10_F10,offsetof(struct monst,m_id)),
END_META(R10_F10_size,sizeof(((struct monst*)0)->m_id)),
END_META(R10_F11,offsetof(struct monst,mtame)),
END_META(R10_F11_size,sizeof(((struct monst*)0)->mtame)),
END_META(R10_F12,offsetof(struct monst,mhp)),
END_META(R10_F12_size,sizeof(((struct monst*)0)->mhp)),
END_META(R10_F13,offsetof(struct monst,nmon)),
END_META(R10_F13_size,sizeof(((struct monst*)0)->nmon)),
END_META(R11_size,sizeof(struct prop)),
END_META(R11_F0,offsetof(struct prop,intrinsic)),
END_META(R11_F0_size,sizeof(((struct prop*)0)->intrinsic)),
END_META(R11_F1,offsetof(struct prop,extrinsic)),
END_META(R11_F1_size,sizeof(((struct prop*)0)->extrinsic)),
END_META(R11_F2,offsetof(struct prop,blocked)),
END_META(R11_F2_size,sizeof(((struct prop*)0)->blocked)),
END_META(R12_size,sizeof(struct kinfo)),
END_META(R12_F0,offsetof(struct kinfo,format)),
END_META(R12_F0_size,sizeof(((struct kinfo*)0)->format)),
END_META(R12_F1,offsetof(struct kinfo,name)),
END_META(R12_F1_size,sizeof(((struct kinfo*)0)->name)),
END_META(R12_F1_stride,sizeof(((struct kinfo*)0)->name[0])),
END_META(R12_F2,offsetof(struct kinfo,id)),
END_META(R12_F2_size,sizeof(((struct kinfo*)0)->id)),
END_META(R12_F3,offsetof(struct kinfo,next)),
END_META(R12_F3_size,sizeof(((struct kinfo*)0)->next)),
END_META(R13_size,sizeof(struct instance_globals_saved_k)),
END_META(R13_F0,offsetof(struct instance_globals_saved_k,killer)),
END_META(R13_F0_size,sizeof(((struct instance_globals_saved_k*)0)->killer)),
END_META(R14_size,sizeof(struct permonst)),
END_META(R14_F0,offsetof(struct permonst,geno)),
END_META(R14_F0_size,sizeof(((struct permonst*)0)->geno)),
END_META(R14_F1,offsetof(struct permonst,mflags2)),
END_META(R14_F1_size,sizeof(((struct permonst*)0)->mflags2)),
END_META(R14_F2,offsetof(struct permonst,mlet)),
END_META(R14_F2_size,sizeof(((struct permonst*)0)->mlet)),
END_META(R15_size,sizeof(struct mextra)),
END_META(R15_F0,offsetof(struct mextra,mgivenname)),
END_META(R15_F0_size,sizeof(((struct mextra*)0)->mgivenname)),
END_META(R15_F1,offsetof(struct mextra,ebones)),
END_META(R15_F1_size,sizeof(((struct mextra*)0)->ebones)),
END_META(R16_size,sizeof(struct Race)),
END_META(R16_F0,offsetof(struct Race,mummynum)),
END_META(R16_F0_size,sizeof(((struct Race*)0)->mummynum)),
END_META(R16_F1,offsetof(struct Race,zombienum)),
END_META(R16_F1_size,sizeof(((struct Race*)0)->zombienum)),
END_META(R16_F2,offsetof(struct Race,mnum)),
END_META(R16_F2_size,sizeof(((struct Race*)0)->mnum)),
END_META(R17_size,sizeof(struct instance_globals_u)),
END_META(R17_F0,offsetof(struct instance_globals_u,urace)),
END_META(R17_F0_size,sizeof(((struct instance_globals_u*)0)->urace)),
END_META(R17_F1,offsetof(struct instance_globals_u,urole)),
END_META(R17_F1_size,sizeof(((struct instance_globals_u*)0)->urole)),
END_META(R18_size,sizeof(struct mvitals)),
END_META(R18_F0,offsetof(struct mvitals,mvflags)),
END_META(R18_F0_size,sizeof(((struct mvitals*)0)->mvflags)),
END_META(R19_size,sizeof(struct instance_globals_saved_m)),
END_META(R19_F0,offsetof(struct instance_globals_saved_m,mvitals)),
END_META(R19_F0_size,sizeof(((struct instance_globals_saved_m*)0)->mvitals)),
END_META(R19_F0_stride,sizeof(((struct instance_globals_saved_m*)0)->mvitals[0])),
END_META(R19_F1,offsetof(struct instance_globals_saved_m,moves)),
END_META(R19_F1_size,sizeof(((struct instance_globals_saved_m*)0)->moves)),
END_META(R20_size,sizeof(struct instance_globals_b)),
END_META(R20_F0,offsetof(struct instance_globals_b,bot_disabled)),
END_META(R20_F0_size,sizeof(((struct instance_globals_b*)0)->bot_disabled)),
END_META(R21_size,sizeof(struct sysopt_s)),
END_META(R21_F0,offsetof(struct sysopt_s,support)),
END_META(R21_F0_size,sizeof(((struct sysopt_s*)0)->support)),
END_META(R21_F1,offsetof(struct sysopt_s,fmtd_wizard_list)),
END_META(R21_F1_size,sizeof(((struct sysopt_s*)0)->fmtd_wizard_list)),
END_META(R21_F2,offsetof(struct sysopt_s,recover)),
END_META(R21_F2_size,sizeof(((struct sysopt_s*)0)->recover)),
END_META(R21_F3,offsetof(struct sysopt_s,panictrace_gdb)),
END_META(R21_F3_size,sizeof(((struct sysopt_s*)0)->panictrace_gdb)),
END_META(R22_size,sizeof(struct instance_globals_i)),
END_META(R22_F0,offsetof(struct instance_globals_i,invent)),
END_META(R22_F0_size,sizeof(((struct instance_globals_i*)0)->invent)),
END_META(R23_size,sizeof(struct instance_globals_n)),
END_META(R23_F0,offsetof(struct instance_globals_n,nomovemsg)),
END_META(R23_F0_size,sizeof(((struct instance_globals_n*)0)->nomovemsg)),
END_META(R24_size,sizeof(struct context_info)),
END_META(R24_F0,offsetof(struct context_info,move)),
END_META(R24_F0_size,sizeof(((struct context_info*)0)->move)),
END_META(R24_F1,offsetof(struct context_info,mon_moving)),
END_META(R24_F1_size,sizeof(((struct context_info*)0)->mon_moving)),
END_META(R25_size,sizeof(struct instance_globals_saved_c)),
END_META(R25_F0,offsetof(struct instance_globals_saved_c,context)),
END_META(R25_F0_size,sizeof(((struct instance_globals_saved_c*)0)->context)),
END_META(R26_size,sizeof(struct Role)),
END_META(R26_F0,offsetof(struct Role,mnum)),
END_META(R26_F0_size,sizeof(((struct Role*)0)->mnum)),
END_META(R26_F1,offsetof(struct Role,name)),
END_META(R26_F1_size,sizeof(((struct Role*)0)->name)),
END_META(R27_size,sizeof(struct display_hints)),
END_META(R27_F0,offsetof(struct display_hints,botl)),
END_META(R27_F0_size,sizeof(((struct display_hints*)0)->botl)),
END_META(R27_F1,offsetof(struct display_hints,botlx)),
END_META(R27_F1_size,sizeof(((struct display_hints*)0)->botlx)),
END_META(R27_F2,offsetof(struct display_hints,time_botl)),
END_META(R27_F2_size,sizeof(((struct display_hints*)0)->time_botl)),
END_META(R28_size,sizeof(struct instance_globals_y)),
END_META(R28_F0,offsetof(struct instance_globals_y,youmonst)),
END_META(R28_F0_size,sizeof(((struct instance_globals_y*)0)->youmonst)),
END_META(R29_size,sizeof(struct obj)),
END_META(R29_F0,offsetof(struct obj,nobj)),
END_META(R29_F0_size,sizeof(((struct obj*)0)->nobj)),
END_META(R29_F1,offsetof(struct obj,cobj)),
END_META(R29_F1_size,sizeof(((struct obj*)0)->cobj)),
END_META(R29_F2,offsetof(struct obj,oartifact)),
END_META(R29_F2_size,sizeof(((struct obj*)0)->oartifact)),
END_META(R29_F3,offsetof(struct obj,oclass)),
END_META(R29_F3_size,sizeof(((struct obj*)0)->oclass)),
END_META(R29_F4,offsetof(struct obj,otyp)),
END_META(R29_F4_size,sizeof(((struct obj*)0)->otyp)),
END_META(R29_F5,offsetof(struct obj,quan)),
END_META(R29_F5_size,sizeof(((struct obj*)0)->quan)),
END_META(R29_F6,offsetof(struct obj,where)),
END_META(R29_F6_size,sizeof(((struct obj*)0)->where)),
END_META(R29_F11,offsetof(struct obj,spe)),
END_META(R29_F11_size,sizeof(((struct obj*)0)->spe)),
END_META(R29_F12,offsetof(struct obj,oextra)),
END_META(R29_F12_size,sizeof(((struct obj*)0)->oextra)),
END_META(R30_size,sizeof(struct valuable_data)),
END_META(R30_F0,offsetof(struct valuable_data,count)),
END_META(R30_F0_size,sizeof(((struct valuable_data*)0)->count)),
END_META(R30_F1,offsetof(struct valuable_data,typ)),
END_META(R30_F1_size,sizeof(((struct valuable_data*)0)->typ)),
END_META(R31_size,sizeof(struct instance_globals_a)),
END_META(R31_F0,offsetof(struct instance_globals_a,amulets)),
END_META(R31_F0_size,sizeof(((struct instance_globals_a*)0)->amulets)),
END_META(R31_F0_stride,sizeof(((struct instance_globals_a*)0)->amulets[0])),
END_META(R32_size,sizeof(struct instance_globals_g)),
END_META(R32_F0,offsetof(struct instance_globals_g,gems)),
END_META(R32_F0_size,sizeof(((struct instance_globals_g*)0)->gems)),
END_META(R32_F0_stride,sizeof(((struct instance_globals_g*)0)->gems[0])),
END_META(R33_size,sizeof(struct instance_globals_t)),
END_META(R33_F0,offsetof(struct instance_globals_t,thrownobj)),
END_META(R33_F0_size,sizeof(((struct instance_globals_t*)0)->thrownobj)),
END_META(R34_size,sizeof(struct instance_globals_k)),
END_META(R34_F0,offsetof(struct instance_globals_k,kickedobj)),
END_META(R34_F0_size,sizeof(((struct instance_globals_k*)0)->kickedobj)),
END_META(R35_size,sizeof(struct objdescr)),
END_META(R35_F0,offsetof(struct objdescr,oc_name)),
END_META(R35_F0_size,sizeof(((struct objdescr*)0)->oc_name)),
END_META(R36_size,sizeof(struct objclass)),
END_META(R36_F0,offsetof(struct objclass,oc_name_idx)),
END_META(R36_F0_size,sizeof(((struct objclass*)0)->oc_name_idx)),
END_META(R36_F1,offsetof(struct objclass,oc_cost)),
END_META(R36_F1_size,sizeof(((struct objclass*)0)->oc_cost)),
END_META(R36_F2,offsetof(struct objclass,oc_class)),
END_META(R36_F2_size,sizeof(((struct objclass*)0)->oc_class)),
END_META(R37_size,sizeof(struct instance_globals_d)),
END_META(R37_F0,offsetof(struct instance_globals_d,done_seq)),
END_META(R37_F0_size,sizeof(((struct instance_globals_d*)0)->done_seq)),
END_META(R37_F1,offsetof(struct instance_globals_d,done_money)),
END_META(R37_F1_size,sizeof(((struct instance_globals_d*)0)->done_money)),
END_META(R38_size,sizeof(struct instance_globals_h)),
END_META(R38_F0,offsetof(struct instance_globals_h,hero_seq)),
END_META(R38_F0_size,sizeof(((struct instance_globals_h*)0)->hero_seq)),
END_META(R39_size,sizeof(struct u_realtime)),
END_META(R39_F0,offsetof(struct u_realtime,finish_time)),
END_META(R39_F0_size,sizeof(((struct u_realtime*)0)->finish_time)),
END_META(R39_F1,offsetof(struct u_realtime,realtime)),
END_META(R39_F1_size,sizeof(((struct u_realtime*)0)->realtime)),
END_META(R39_F2,offsetof(struct u_realtime,start_timing)),
END_META(R39_F2_size,sizeof(((struct u_realtime*)0)->start_timing)),
END_META(R40_size,sizeof(struct u_roleplay)),
END_META(R40_F0,offsetof(struct u_roleplay,blind)),
END_META(R40_F0_size,sizeof(((struct u_roleplay*)0)->blind)),
END_META(R40_F1,offsetof(struct u_roleplay,nudist)),
END_META(R40_F1_size,sizeof(((struct u_roleplay*)0)->nudist)),
END_META(R41_size,sizeof(struct rm)),
END_META(R41_F0,offsetof(struct rm,typ)),
END_META(R41_F0_size,sizeof(((struct rm*)0)->typ)),
END_META(R42_size,sizeof(dlevel_t)),
END_META(R42_F0,offsetof(dlevel_t,locations)),
END_META(R42_F0_size,sizeof(((dlevel_t*)0)->locations)),
END_META(R42_F0_stride,sizeof(((dlevel_t*)0)->locations[0])),
END_META(R43_size,sizeof(struct instance_globals_saved_l)),
END_META(R43_F0,offsetof(struct instance_globals_saved_l,level)),
END_META(R43_F0_size,sizeof(((struct instance_globals_saved_l*)0)->level)),
END_META(R44_size,sizeof(struct instance_globals_saved_p)),
END_META(R44_F0,offsetof(struct instance_globals_saved_p,plname)),
END_META(R44_F0_size,sizeof(((struct instance_globals_saved_p*)0)->plname)),
END_META(R44_F0_stride,sizeof(((struct instance_globals_saved_p*)0)->plname[0])),
END_META(R45_size,sizeof(align)),
END_META(R45_F0,offsetof(align,type)),
END_META(R45_F0_size,sizeof(((align*)0)->type)),
END_META(R46_size,sizeof(struct u_have)),
END_META(R47_size,sizeof(struct RoleName)),
END_META(R47_F0,offsetof(struct RoleName,f)),
END_META(R47_F0_size,sizeof(((struct RoleName*)0)->f)),
END_META(R47_F1,offsetof(struct RoleName,m)),
END_META(R47_F1_size,sizeof(((struct RoleName*)0)->m)),
END_META(R48_size,sizeof(struct instance_globals_v)),
END_META(R48_F0,offsetof(struct instance_globals_v,valuables)),
END_META(R48_F0_size,sizeof(((struct instance_globals_v*)0)->valuables)),
END_META(R48_F0_stride,sizeof(((struct instance_globals_v*)0)->valuables[0])),
END_META(R48_F1,offsetof(struct instance_globals_v,viz_array)),
END_META(R48_F1_size,sizeof(((struct instance_globals_v*)0)->viz_array)),
END_META(R49_size,sizeof(struct val_list)),
END_META(R49_F0,offsetof(struct val_list,list)),
END_META(R49_F0_size,sizeof(((struct val_list*)0)->list)),
END_META(R49_F1,offsetof(struct val_list,size)),
END_META(R49_F1_size,sizeof(((struct val_list*)0)->size)),
END_META(R50_size,sizeof(struct oextra)),
END_META(R50_F0,offsetof(struct oextra,oname)),
END_META(R50_F0_size,sizeof(((struct oextra*)0)->oname)),
END_META(R51_size,sizeof(dungeon)),
END_META(R51_F0,offsetof(dungeon,dname)),
END_META(R51_F0_size,sizeof(((dungeon*)0)->dname)),
END_META(R51_F0_stride,sizeof(((dungeon*)0)->dname[0])),
END_META(R52_size,sizeof(Loot)),
END_META(R52_F0,offsetof(Loot,obj)),
END_META(R52_F0_size,sizeof(((Loot*)0)->obj)),
END_META(R53_size,sizeof(NHFILE)),
END_META(R53_F0,offsetof(NHFILE,mode)),
END_META(R53_F0_size,sizeof(((NHFILE*)0)->mode)),
END_META(config_DEBUG,1),
END_META(SIG_IGN,(intptr_t)SIG_IGN),
END_META(fuzzer_off,fuzzer_off),
END_META(override_restriction,override_restriction),
END_META(ACH_BLND,ACH_BLND),
END_META(ACH_NUDE,ACH_NUDE),
END_META(ACH_UWIN,ACH_UWIN),
END_META(AMULET_CLASS,AMULET_CLASS),
END_META(AMULET_OF_LIFE_SAVING,AMULET_OF_LIFE_SAVING),
END_META(ASCENDED,ASCENDED),
END_META(A_CON,A_CON),
END_META(A_CURRENT,A_CURRENT),
END_META(A_ORIGINAL,A_ORIGINAL),
END_META(BAG_OF_TRICKS,BAG_OF_TRICKS),
END_META(BASICENLIGHTENMENT,BASICENLIGHTENMENT),
END_META(BELL_OF_OPENING,BELL_OF_OPENING),
END_META(BLINDED,BLINDED),
END_META(BUFSZ,BUFSZ),
END_META(BURNING,BURNING),
END_META(CANDELABRUM_OF_INVOCATION,CANDELABRUM_OF_INVOCATION),
END_META(CHOKING,CHOKING),
END_META(COLNO,COLNO),
END_META(CORPSE,CORPSE),
END_META(COUNTING,COUNTING),
END_META(CQ_CANNED,CQ_CANNED),
END_META(DIED,DIED),
END_META(DISCLOSE_NO_WITHOUT_PROMPT,DISCLOSE_NO_WITHOUT_PROMPT),
END_META(DISCLOSE_PROMPT_DEFAULT_SPECIAL,DISCLOSE_PROMPT_DEFAULT_SPECIAL),
END_META(DISCLOSE_PROMPT_DEFAULT_YES,DISCLOSE_PROMPT_DEFAULT_YES),
END_META(DISCLOSE_SPECIAL_WITHOUT_PROMPT,DISCLOSE_SPECIAL_WITHOUT_PROMPT),
END_META(DISCLOSE_YES_WITHOUT_PROMPT,DISCLOSE_YES_WITHOUT_PROMPT),
END_META(DISSOLVED,DISSOLVED),
END_META(ECMD_OK,ECMD_OK),
END_META(ENL_GAMEOVERALIVE,ENL_GAMEOVERALIVE),
END_META(ENL_GAMEOVERDEAD,ENL_GAMEOVERDEAD),
END_META(ESCAPED,ESCAPED),
END_META(EXIT_SUCCESS,EXIT_SUCCESS),
END_META(FAKE_AMULET_OF_YENDOR,FAKE_AMULET_OF_YENDOR),
END_META(FIRST_AMULET,FIRST_AMULET),
END_META(FIRST_REAL_GEM,FIRST_REAL_GEM),
END_META(FOOD_CLASS,FOOD_CLASS),
END_META(FREEING,FREEING),
END_META(GEM_CLASS,GEM_CLASS),
END_META(GENOCIDED,GENOCIDED),
END_META(GRAVE,GRAVE),
END_META(G_GENOD,G_GENOD),
END_META(G_NOCORPSE,G_NOCORPSE),
END_META(G_UNIQ,G_UNIQ),
END_META(HALLUC,HALLUC),
END_META(HALLUC_RES,HALLUC_RES),
END_META(IN_SIGHT,IN_SIGHT),
END_META(KILLED_BY,KILLED_BY),
END_META(KILLED_BY_AN,KILLED_BY_AN),
END_META(LARGE_BOX,LARGE_BOX),
END_META(LAST_GLASS_GEM,LAST_GLASS_GEM),
END_META(LAST_REAL_GEM,LAST_REAL_GEM),
END_META(LEAVESTATUE,LEAVESTATUE),
END_META(LIFESAVED,LIFESAVED),
END_META(LL_DUMP,LL_DUMP),
END_META(LL_LIFESAVE,LL_LIFESAVE),
END_META(LOW_PM,LOW_PM),
END_META(M2_PNAME,M2_PNAME),
END_META(MAGICENLIGHTENMENT,MAGICENLIGHTENMENT),
END_META(M_AP_MONSTER,M_AP_MONSTER),
END_META(M_AP_TYPMASK,M_AP_TYPMASK),
END_META(NHCORE_GAME_EXIT,NHCORE_GAME_EXIT),
END_META(NHW_MENU,NHW_MENU),
END_META(NHW_TEXT,NHW_TEXT),
END_META(NON_PM,NON_PM),
END_META(NO_KILLER_PREFIX,NO_KILLER_PREFIX),
END_META(NUMMONS,NUMMONS),
END_META(NUM_DISCLOSURE_OPTIONS,NUM_DISCLOSURE_OPTIONS),
END_META(OBJ_FREE,OBJ_FREE),
END_META(PANICKED,PANICKED),
END_META(PARANOID_BONES,PARANOID_BONES),
END_META(PARANOID_DIE,PARANOID_DIE),
END_META(PARANOID_QUIT,PARANOID_QUIT),
END_META(PLNMSG_OK_DONT_DIE,PLNMSG_OK_DONT_DIE),
END_META(PM_GHOST,PM_GHOST),
END_META(PM_GHOUL,PM_GHOUL),
END_META(PM_GREEN_SLIME,PM_GREEN_SLIME),
END_META(PM_HIGH_CLERIC,PM_HIGH_CLERIC),
END_META(PM_HOUSECAT,PM_HOUSECAT),
END_META(PM_HUMAN,PM_HUMAN),
END_META(PM_TOURIST,PM_TOURIST),
END_META(PM_VAMPIRE,PM_VAMPIRE),
END_META(PM_VAMPIRE_LEADER,PM_VAMPIRE_LEADER),
END_META(PM_VLAD_THE_IMPALER,PM_VLAD_THE_IMPALER),
END_META(PM_WRAITH,PM_WRAITH),
END_META(POT_RESTORE_ABILITY,POT_RESTORE_ABILITY),
END_META(POT_WATER,POT_WATER),
END_META(QBUFSZ,QBUFSZ),
END_META(QUIT,QUIT),
END_META(ROWNO,ROWNO),
END_META(SICK,SICK),
END_META(SICK_ALL,SICK_ALL),
END_META(SIGINT,SIGINT),
END_META(SIGQUIT,SIGQUIT),
END_META(SORTLOOT_LOOT,SORTLOOT_LOOT),
END_META(SORTLOOT_PACK,SORTLOOT_PACK),
END_META(SPE_BOOK_OF_THE_DEAD,SPE_BOOK_OF_THE_DEAD),
END_META(STARVING,STARVING),
END_META(STATUE,STATUE),
END_META(STONING,STONING),
END_META(S_MUMMY,S_MUMMY),
END_META(S_VAMPIRE,S_VAMPIRE),
END_META(S_WRAITH,S_WRAITH),
END_META(TIMEOUT,TIMEOUT),
END_META(TRICKED,TRICKED),
END_META(TT_LAVA,TT_LAVA),
END_META(TURNED_SLIME,TURNED_SLIME),
END_META(UNCHANGING,UNCHANGING),
END_META(UTOTYPE_ATSTAIRS,UTOTYPE_ATSTAIRS),
END_META(WIN_ERR,WIN_ERR),
END_META(WRITING,WRITING),
};
#undef END_META
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(boolean)==1,"END native widths");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_fuzzer)==1,"END R0_F0 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->debug_fuzzer))-1)<0)==1,"END R0_F0 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->window_inited)==1,"END R0_F1 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->window_inited))-1)<0)==1,"END R0_F1 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->force_invmenu)==1,"END R0_F2 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->force_invmenu))-1)<0)==1,"END R0_F2 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->perm_invent)==1,"END R0_F3 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->perm_invent))-1)<0)==1,"END R0_F3 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"END R0_F4 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->last_msg))-1)<0)==1,"END R0_F4 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->vision_inited)==1,"END R0_F5 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->vision_inited))-1)<0)==1,"END R0_F5 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->at_night)==4,"END R0_F6 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->at_night))-1)<0)==1,"END R0_F6 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->at_midnight)==4,"END R0_F7 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->at_midnight))-1)<0)==1,"END R0_F7 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->toptenwin)==1,"END R0_F8 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->toptenwin))-1)<0)==1,"END R0_F8 sign");
_Static_assert(sizeof(((struct instance_flags*)0)->in_dumplog)==1,"END R0_F9 width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->in_dumplog))-1)<0)==1,"END R0_F9 sign");
_Static_assert(sizeof(((struct flag*)0)->ignintr)==1,"END R1_F0 width");
_Static_assert((((__typeof__(((struct flag*)0)->ignintr))-1)<0)==1,"END R1_F0 sign");
_Static_assert(sizeof(((struct flag*)0)->paranoia_bits)==4,"END R1_F1 width");
_Static_assert((((__typeof__(((struct flag*)0)->paranoia_bits))-1)<0)==0,"END R1_F1 sign");
_Static_assert(sizeof(((struct flag*)0)->debug)==1,"END R1_F2 width");
_Static_assert((((__typeof__(((struct flag*)0)->debug))-1)<0)==1,"END R1_F2 sign");
_Static_assert(sizeof(((struct flag*)0)->explore)==1,"END R1_F4 width");
_Static_assert((((__typeof__(((struct flag*)0)->explore))-1)<0)==1,"END R1_F4 sign");
_Static_assert(sizeof(((struct flag*)0)->beginner)==1,"END R1_F5 width");
_Static_assert((((__typeof__(((struct flag*)0)->beginner))-1)<0)==1,"END R1_F5 sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"END R1_F6 width");
_Static_assert((((__typeof__(((struct flag*)0)->female))-1)<0)==1,"END R1_F6 sign");
_Static_assert(sizeof(((struct flag*)0)->tombstone)==1,"END R1_F7 width");
_Static_assert((((__typeof__(((struct flag*)0)->tombstone))-1)<0)==1,"END R1_F7 sign");
_Static_assert(sizeof(((struct flag*)0)->sortloot)==1,"END R1_F8 width");
_Static_assert((((__typeof__(((struct flag*)0)->sortloot))-1)<0)==1,"END R1_F8 sign");
_Static_assert(sizeof(((struct flag*)0)->sortpack)==1,"END R1_F9 width");
_Static_assert((((__typeof__(((struct flag*)0)->sortpack))-1)<0)==1,"END R1_F9 sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"END R3_F0 width");
_Static_assert((((__typeof__(((struct instance_globals_m*)0)->multi))-1)<0)==1,"END R3_F0 sign");
_Static_assert(sizeof(((d_level*)0)->dnum)==2,"END R4_F0 width");
_Static_assert((((__typeof__(((d_level*)0)->dnum))-1)<0)==1,"END R4_F0 sign");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2,"END R4_F1 width");
_Static_assert((((__typeof__(((d_level*)0)->dlevel))-1)<0)==1,"END R4_F1 sign");
_Static_assert(sizeof(((struct you*)0)->usleep)==8,"END R5_F2 width");
_Static_assert((((__typeof__(((struct you*)0)->usleep))-1)<0)==1,"END R5_F2 sign");
_Static_assert(sizeof(((struct you*)0)->ugrave_arise)==4,"END R5_F5 width");
_Static_assert((((__typeof__(((struct you*)0)->ugrave_arise))-1)<0)==1,"END R5_F5 sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4,"END R5_F6 width");
_Static_assert((((__typeof__(((struct you*)0)->ulevel))-1)<0)==1,"END R5_F6 sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4,"END R5_F7 width");
_Static_assert((((__typeof__(((struct you*)0)->uhpmax))-1)<0)==1,"END R5_F7 sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"END R5_F8 width");
_Static_assert((((__typeof__(((struct you*)0)->uhp))-1)<0)==1,"END R5_F8 sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4,"END R5_F9 width");
_Static_assert((((__typeof__(((struct you*)0)->umonnum))-1)<0)==1,"END R5_F9 sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4,"END R5_F10 width");
_Static_assert((((__typeof__(((struct you*)0)->umonster))-1)<0)==1,"END R5_F10 sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4,"END R5_F11 width");
_Static_assert((((__typeof__(((struct you*)0)->mh))-1)<0)==1,"END R5_F11 sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4,"END R5_F12 width");
_Static_assert((((__typeof__(((struct you*)0)->mhmax))-1)<0)==1,"END R5_F12 sign");
_Static_assert(sizeof(((struct you*)0)->uhunger)==4,"END R5_F13 width");
_Static_assert((((__typeof__(((struct you*)0)->uhunger))-1)<0)==1,"END R5_F13 sign");
_Static_assert(sizeof(((struct you*)0)->utrap)==4,"END R5_F14 width");
_Static_assert((((__typeof__(((struct you*)0)->utrap))-1)<0)==0,"END R5_F14 sign");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4,"END R5_F15 width");
_Static_assert((((__typeof__(((struct you*)0)->utraptype))-1)<0)==0,"END R5_F15 sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2,"END R5_F18 width");
_Static_assert((((__typeof__(((struct you*)0)->ux))-1)<0)==1,"END R5_F18 sign");
_Static_assert(sizeof(((struct you*)0)->dx)==4,"END R5_F19 width");
_Static_assert((((__typeof__(((struct you*)0)->dx))-1)<0)==1,"END R5_F19 sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2,"END R5_F20 width");
_Static_assert((((__typeof__(((struct you*)0)->uy))-1)<0)==1,"END R5_F20 sign");
_Static_assert(sizeof(((struct you*)0)->dy)==4,"END R5_F21 width");
_Static_assert((((__typeof__(((struct you*)0)->dy))-1)<0)==1,"END R5_F21 sign");
_Static_assert(sizeof(((struct you*)0)->urexp)==8,"END R5_F22 width");
_Static_assert((((__typeof__(((struct you*)0)->urexp))-1)<0)==1,"END R5_F22 sign");
_Static_assert(sizeof(((struct you*)0)->ulycn)==4,"END R5_F23 width");
_Static_assert((((__typeof__(((struct you*)0)->ulycn))-1)<0)==1,"END R5_F23 sign");
_Static_assert(sizeof(((struct you*)0)->umortality)==4,"END R5_F24 width");
_Static_assert((((__typeof__(((struct you*)0)->umortality))-1)<0)==1,"END R5_F24 sign");
_Static_assert(sizeof(((struct you*)0)->umoney0)==8,"END R5_F27 width");
_Static_assert((((__typeof__(((struct you*)0)->umoney0))-1)<0)==1,"END R5_F27 sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_tutorial_dnum)==2,"END R6_F0 width");
_Static_assert((((__typeof__(((struct dgn_topology*)0)->d_tutorial_dnum))-1)<0)==1,"END R6_F0 sign");
_Static_assert(sizeof(((struct sinfo*)0)->stopprint)==4,"END R9_F0 width");
_Static_assert((((__typeof__(((struct sinfo*)0)->stopprint))-1)<0)==1,"END R9_F0 sign");
_Static_assert(sizeof(((struct sinfo*)0)->panicking)==4,"END R9_F2 width");
_Static_assert((((__typeof__(((struct sinfo*)0)->panicking))-1)<0)==1,"END R9_F2 sign");
_Static_assert(sizeof(((struct sinfo*)0)->gameover)==4,"END R9_F3 width");
_Static_assert((((__typeof__(((struct sinfo*)0)->gameover))-1)<0)==1,"END R9_F3 sign");
_Static_assert(sizeof(((struct sinfo*)0)->something_worth_saving)==4,"END R9_F4 width");
_Static_assert((((__typeof__(((struct sinfo*)0)->something_worth_saving))-1)<0)==1,"END R9_F4 sign");
_Static_assert(sizeof(((struct sinfo*)0)->in_moveloop)==4,"END R9_F5 width");
_Static_assert((((__typeof__(((struct sinfo*)0)->in_moveloop))-1)<0)==1,"END R9_F5 sign");
_Static_assert(sizeof(((struct sinfo*)0)->exiting)==4,"END R9_F6 width");
_Static_assert((((__typeof__(((struct sinfo*)0)->exiting))-1)<0)==1,"END R9_F6 sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2,"END R10_F1 width");
_Static_assert((((__typeof__(((struct monst*)0)->cham))-1)<0)==1,"END R10_F1 sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1,"END R10_F2 width");
_Static_assert((((__typeof__(((struct monst*)0)->m_ap_type))-1)<0)==0,"END R10_F2 sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4,"END R10_F6 width");
_Static_assert((((__typeof__(((struct monst*)0)->mappearance))-1)<0)==0,"END R10_F6 sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"END R10_F10 width");
_Static_assert((((__typeof__(((struct monst*)0)->m_id))-1)<0)==0,"END R10_F10 sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1,"END R10_F11 width");
_Static_assert((((__typeof__(((struct monst*)0)->mtame))-1)<0)==1,"END R10_F11 sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4,"END R10_F12 width");
_Static_assert((((__typeof__(((struct monst*)0)->mhp))-1)<0)==1,"END R10_F12 sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8,"END R11_F0 width");
_Static_assert((((__typeof__(((struct prop*)0)->intrinsic))-1)<0)==1,"END R11_F0 sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8,"END R11_F1 width");
_Static_assert((((__typeof__(((struct prop*)0)->extrinsic))-1)<0)==1,"END R11_F1 sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8,"END R11_F2 width");
_Static_assert((((__typeof__(((struct prop*)0)->blocked))-1)<0)==1,"END R11_F2 sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4,"END R12_F0 width");
_Static_assert((((__typeof__(((struct kinfo*)0)->format))-1)<0)==1,"END R12_F0 sign");
_Static_assert(sizeof(((struct kinfo*)0)->id)==4,"END R12_F2 width");
_Static_assert((((__typeof__(((struct kinfo*)0)->id))-1)<0)==1,"END R12_F2 sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2,"END R14_F0 width");
_Static_assert((((__typeof__(((struct permonst*)0)->geno))-1)<0)==0,"END R14_F0 sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8,"END R14_F1 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mflags2))-1)<0)==0,"END R14_F1 sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1,"END R14_F2 width");
_Static_assert((((__typeof__(((struct permonst*)0)->mlet))-1)<0)==1,"END R14_F2 sign");
_Static_assert(sizeof(((struct Race*)0)->mummynum)==2,"END R16_F0 width");
_Static_assert((((__typeof__(((struct Race*)0)->mummynum))-1)<0)==1,"END R16_F0 sign");
_Static_assert(sizeof(((struct Race*)0)->zombienum)==2,"END R16_F1 width");
_Static_assert((((__typeof__(((struct Race*)0)->zombienum))-1)<0)==1,"END R16_F1 sign");
_Static_assert(sizeof(((struct Race*)0)->mnum)==2,"END R16_F2 width");
_Static_assert((((__typeof__(((struct Race*)0)->mnum))-1)<0)==1,"END R16_F2 sign");
_Static_assert(sizeof(((struct mvitals*)0)->mvflags)==1,"END R18_F0 width");
_Static_assert((((__typeof__(((struct mvitals*)0)->mvflags))-1)<0)==0,"END R18_F0 sign");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8,"END R19_F1 width");
_Static_assert((((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1)<0)==1,"END R19_F1 sign");
_Static_assert(sizeof(((struct instance_globals_b*)0)->bot_disabled)==1,"END R20_F0 width");
_Static_assert((((__typeof__(((struct instance_globals_b*)0)->bot_disabled))-1)<0)==1,"END R20_F0 sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->panictrace_gdb)==4,"END R21_F3 width");
_Static_assert((((__typeof__(((struct sysopt_s*)0)->panictrace_gdb))-1)<0)==1,"END R21_F3 sign");
_Static_assert(sizeof(((struct context_info*)0)->move)==1,"END R24_F0 width");
_Static_assert((((__typeof__(((struct context_info*)0)->move))-1)<0)==1,"END R24_F0 sign");
_Static_assert(sizeof(((struct context_info*)0)->mon_moving)==1,"END R24_F1 width");
_Static_assert((((__typeof__(((struct context_info*)0)->mon_moving))-1)<0)==1,"END R24_F1 sign");
_Static_assert(sizeof(((struct Role*)0)->mnum)==2,"END R26_F0 width");
_Static_assert((((__typeof__(((struct Role*)0)->mnum))-1)<0)==1,"END R26_F0 sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1,"END R27_F0 width");
_Static_assert((((__typeof__(((struct display_hints*)0)->botl))-1)<0)==1,"END R27_F0 sign");
_Static_assert(sizeof(((struct display_hints*)0)->botlx)==1,"END R27_F1 width");
_Static_assert((((__typeof__(((struct display_hints*)0)->botlx))-1)<0)==1,"END R27_F1 sign");
_Static_assert(sizeof(((struct display_hints*)0)->time_botl)==1,"END R27_F2 width");
_Static_assert((((__typeof__(((struct display_hints*)0)->time_botl))-1)<0)==1,"END R27_F2 sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1,"END R29_F2 width");
_Static_assert((((__typeof__(((struct obj*)0)->oartifact))-1)<0)==1,"END R29_F2 sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"END R29_F3 width");
_Static_assert((((__typeof__(((struct obj*)0)->oclass))-1)<0)==1,"END R29_F3 sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"END R29_F4 width");
_Static_assert((((__typeof__(((struct obj*)0)->otyp))-1)<0)==1,"END R29_F4 sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"END R29_F5 width");
_Static_assert((((__typeof__(((struct obj*)0)->quan))-1)<0)==1,"END R29_F5 sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"END R29_F6 width");
_Static_assert((((__typeof__(((struct obj*)0)->where))-1)<0)==1,"END R29_F6 sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"END R29_F11 width");
_Static_assert((((__typeof__(((struct obj*)0)->spe))-1)<0)==1,"END R29_F11 sign");
_Static_assert(sizeof(((struct valuable_data*)0)->count)==8,"END R30_F0 width");
_Static_assert((((__typeof__(((struct valuable_data*)0)->count))-1)<0)==1,"END R30_F0 sign");
_Static_assert(sizeof(((struct valuable_data*)0)->typ)==4,"END R30_F1 width");
_Static_assert((((__typeof__(((struct valuable_data*)0)->typ))-1)<0)==1,"END R30_F1 sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2,"END R36_F0 width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_name_idx))-1)<0)==1,"END R36_F0 sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_cost)==2,"END R36_F1 width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_cost))-1)<0)==1,"END R36_F1 sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_class)==1,"END R36_F2 width");
_Static_assert((((__typeof__(((struct objclass*)0)->oc_class))-1)<0)==1,"END R36_F2 sign");
_Static_assert(sizeof(((struct instance_globals_d*)0)->done_seq)==8,"END R37_F0 width");
_Static_assert((((__typeof__(((struct instance_globals_d*)0)->done_seq))-1)<0)==1,"END R37_F0 sign");
_Static_assert(sizeof(((struct instance_globals_d*)0)->done_money)==8,"END R37_F1 width");
_Static_assert((((__typeof__(((struct instance_globals_d*)0)->done_money))-1)<0)==1,"END R37_F1 sign");
_Static_assert(sizeof(((struct instance_globals_h*)0)->hero_seq)==8,"END R38_F0 width");
_Static_assert((((__typeof__(((struct instance_globals_h*)0)->hero_seq))-1)<0)==1,"END R38_F0 sign");
_Static_assert(sizeof(((struct u_realtime*)0)->finish_time)==8,"END R39_F0 width");
_Static_assert((((__typeof__(((struct u_realtime*)0)->finish_time))-1)<0)==1,"END R39_F0 sign");
_Static_assert(sizeof(((struct u_realtime*)0)->realtime)==8,"END R39_F1 width");
_Static_assert((((__typeof__(((struct u_realtime*)0)->realtime))-1)<0)==1,"END R39_F1 sign");
_Static_assert(sizeof(((struct u_realtime*)0)->start_timing)==8,"END R39_F2 width");
_Static_assert((((__typeof__(((struct u_realtime*)0)->start_timing))-1)<0)==1,"END R39_F2 sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->blind)==1,"END R40_F0 width");
_Static_assert((((__typeof__(((struct u_roleplay*)0)->blind))-1)<0)==1,"END R40_F0 sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->nudist)==1,"END R40_F1 width");
_Static_assert((((__typeof__(((struct u_roleplay*)0)->nudist))-1)<0)==1,"END R40_F1 sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1,"END R41_F0 width");
_Static_assert((((__typeof__(((struct rm*)0)->typ))-1)<0)==1,"END R41_F0 sign");
_Static_assert(sizeof(((align*)0)->type)==1,"END R45_F0 width");
_Static_assert((((__typeof__(((align*)0)->type))-1)<0)==1,"END R45_F0 sign");
_Static_assert(sizeof(((struct val_list*)0)->size)==4,"END R49_F1 width");
_Static_assert((((__typeof__(((struct val_list*)0)->size))-1)<0)==1,"END R49_F1 sign");
_Static_assert(sizeof(((NHFILE*)0)->mode)==4,"END R53_F0 width");
_Static_assert((((__typeof__(((NHFILE*)0)->mode))-1)<0)==1,"END R53_F0 sign");
#endif
