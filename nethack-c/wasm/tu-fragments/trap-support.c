/* TRAP native ABI only: typed calls, addresses, storage, callbacks and native identities. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "trap-support.h"
#include "trap-source-data.h"
extern const char *const destroy_strings[][3];
static const char * teleport_trap_storage_0[2];
static const char * teleport_trap_storage_1[2];
static char teleport_trap_storage_2[15];
static const char * teleport_trap_storage_3;
static const char * teleport_trap_storage_4[6];
static char teleport_trap_storage_5[12];
static const char * teleport_trap_storage_6[5];
static const char * teleport_trap_storage_7[5];
static const char * teleport_trap_storage_8[5];
static char teleport_trap_storage_9[34];
static union vlaunchinfo teleport_trap_storage_10;
static char teleport_trap_storage_11[37];
static boolean teleport_trap_storage_12;
static const char * teleport_trap_storage_13[12];
static char teleport_trap_storage_14[12];
static char teleport_trap_storage_15[14];
static char teleport_trap_storage_16[31];
static const char * teleport_trap_storage_17[62];
static char teleport_trap_storage_18[33];
void *teleport_trap_storage(int index){switch(index){
case 0:return &teleport_trap_storage_0;
case 1:return &teleport_trap_storage_1;
case 2:return &teleport_trap_storage_2;
case 3:return &teleport_trap_storage_3;
case 4:return &teleport_trap_storage_4;
case 5:return &teleport_trap_storage_5;
case 6:return &teleport_trap_storage_6;
case 7:return &teleport_trap_storage_7;
case 8:return &teleport_trap_storage_8;
case 9:return &teleport_trap_storage_9;
case 10:return &teleport_trap_storage_10;
case 11:return &teleport_trap_storage_11;
case 12:return &teleport_trap_storage_12;
case 13:return &teleport_trap_storage_13;
case 14:return &teleport_trap_storage_14;
case 15:return &teleport_trap_storage_15;
case 16:return &teleport_trap_storage_16;
case 17:return &teleport_trap_storage_17;
case 18:return &teleport_trap_storage_18;
default:abort();}}
void *teleport_trap_global(int index){switch(index){
case 0:return (void*)&gy;
case 1:return (void*)&uarmh;
case 2:return (void*)&objects;
case 3:return (void*)&materialnm;
case 4:return (void*)&uarmc;
case 5:return (void*)&uarm;
case 6:return (void*)&uarmu;
case 7:return (void*)&uarms;
case 8:return (void*)&uarmg;
case 9:return (void*)&uarmf;
case 10:return (void*)&gv;
case 11:return (void*)&gb;
case 12:return (void*)&u;
case 13:return (void*)&flags;
case 14:return (void*)&mons;
case 15:return (void*)&svd;
case 16:return (void*)&svl;
case 17:return (void*)&iflags;
case 18:return (void*)&svc;
case 19:return (void*)&gl;
case 20:return (void*)&gx;
case 21:return (void*)&gf;
case 22:return (void*)&WIN_MESSAGE;
case 23:return (void*)&windowprocs;
case 24:return (void*)&gu;
case 25:return (void*)&c_common_strings;
case 26:return (void*)&disp;
case 27:return (void*)&uwep;
case 28:return (void*)&uswapwep;
case 29:return (void*)&gi;
case 30:return (void*)&uball;
case 31:return (void*)&gm;
case 32:return (void*)&gn;
case 33:return (void*)&uquiver;
case 34:return (void*)&go;
case 35:return (void*)&xdir;
case 36:return (void*)&ydir;
case 37:return (void*)&svk;
case 38:return (void*)&gs;
case 39:return (void*)&uchain;
case 40:return (void*)&cg;
case 41:return (void*)&destroy_strings;
case 42:return (void*)&gt;
case 43:return (void*)&gk;
case 44:return (void*)&ga;
case 45:return (void*)&uamul;
case 46:return (void*)&uleft;
case 47:return (void*)&uright;
case 48:return (void*)&ublindf;
case 49:return (void*)&ynqchars;
case 50:return (void*)&defsyms;
case 51:return (void*)&vowels;
default:abort();}}
_Static_assert(sizeof(((struct Role*)0)->mnum)==2 && (((__typeof__(((struct Role*)0)->mnum))-1<0)==1),"TRAP field Role.mnum width/sign");
_Static_assert(sizeof(((struct RoleName*)0)->f)==8,"TRAP pointer RoleName.f");
_Static_assert(sizeof(((struct RoleName*)0)->m)==8,"TRAP pointer RoleName.m");
_Static_assert(sizeof(((struct align*)0)->type)==1 && (((__typeof__(((struct align*)0)->type))-1<0)==1),"TRAP field align.type width/sign");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_Something)==8,"TRAP pointer c_common_strings.c_Something");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_You_can_move_again)==8,"TRAP pointer c_common_strings.c_You_can_move_again");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_something)==8,"TRAP pointer c_common_strings.c_something");
_Static_assert(sizeof(((struct c_common_strings*)0)->c_vision_clears)==8,"TRAP pointer c_common_strings.c_vision_clears");
_Static_assert(sizeof(((struct context_info*)0)->mon_moving)==1 && (((__typeof__(((struct context_info*)0)->mon_moving))-1<0)==1),"TRAP field context_info.mon_moving width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"TRAP field d_level.dlevel width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"TRAP field d_level.dnum width/sign");
_Static_assert(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum)==2 && (((__typeof__(((struct dgn_topology*)0)->d_sokoban_dnum))-1<0)==1),"TRAP field dgn_topology.d_sokoban_dnum width/sign");
_Static_assert(sizeof(((struct display_hints*)0)->botl)==1 && (((__typeof__(((struct display_hints*)0)->botl))-1<0)==1),"TRAP field display_hints.botl width/sign");
_Static_assert(sizeof(((struct dungeon*)0)->dunlev_ureached)==2 && (((__typeof__(((struct dungeon*)0)->dunlev_ureached))-1<0)==1),"TRAP field dungeon.dunlev_ureached width/sign");
_Static_assert(sizeof(((struct dungeon*)0)->entry_lev)==2 && (((__typeof__(((struct dungeon*)0)->entry_lev))-1<0)==1),"TRAP field dungeon.entry_lev width/sign");
_Static_assert(sizeof(((struct flag*)0)->debug)==1 && (((__typeof__(((struct flag*)0)->debug))-1<0)==1),"TRAP field flag.debug width/sign");
_Static_assert(sizeof(((struct flag*)0)->explore)==1 && (((__typeof__(((struct flag*)0)->explore))-1<0)==1),"TRAP field flag.explore width/sign");
_Static_assert(sizeof(((struct flag*)0)->female)==1 && (((__typeof__(((struct flag*)0)->female))-1<0)==1),"TRAP field flag.female width/sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1 && (((__typeof__(((struct flag*)0)->verbose))-1<0)==1),"TRAP field flag.verbose width/sign");
_Static_assert(sizeof(((struct h2o_ctx*)0)->ctx_valid)==1 && (((__typeof__(((struct h2o_ctx*)0)->ctx_valid))-1<0)==1),"TRAP field h2o_ctx.ctx_valid width/sign");
_Static_assert(sizeof(((struct h2o_ctx*)0)->dkn_boom)==4 && (((__typeof__(((struct h2o_ctx*)0)->dkn_boom))-1<0)==1),"TRAP field h2o_ctx.dkn_boom width/sign");
_Static_assert(sizeof(((struct h2o_ctx*)0)->unk_boom)==4 && (((__typeof__(((struct h2o_ctx*)0)->unk_boom))-1<0)==1),"TRAP field h2o_ctx.unk_boom width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_overwrite_stairs)==1 && (((__typeof__(((struct instance_flags*)0)->debug_overwrite_stairs))-1<0)==1),"TRAP field instance_flags.debug_overwrite_stairs width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->failing_untrap)==4 && (((__typeof__(((struct instance_flags*)0)->failing_untrap))-1<0)==1),"TRAP field instance_flags.failing_untrap width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->in_lava_effects)==4 && (((__typeof__(((struct instance_flags*)0)->in_lava_effects))-1<0)==1),"TRAP field instance_flags.in_lava_effects width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4 && (((__typeof__(((struct instance_flags*)0)->last_msg))-1<0)==1),"TRAP field instance_flags.last_msg width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->menu_requested)==1 && (((__typeof__(((struct instance_flags*)0)->menu_requested))-1<0)==1),"TRAP field instance_flags.menu_requested width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->prev_decor)==1 && (((__typeof__(((struct instance_flags*)0)->prev_decor))-1<0)==1),"TRAP field instance_flags.prev_decor width/sign");
_Static_assert(sizeof(((struct instance_globals_f*)0)->ftrap)==8,"TRAP pointer instance_globals_f.ftrap");
_Static_assert(sizeof(((struct instance_globals_i*)0)->in_mklev)==1 && (((__typeof__(((struct instance_globals_i*)0)->in_mklev))-1<0)==1),"TRAP field instance_globals_i.in_mklev width/sign");
_Static_assert(sizeof(((struct instance_globals_i*)0)->invent)==8,"TRAP pointer instance_globals_i.invent");
_Static_assert(sizeof(((struct instance_globals_k*)0)->kickedobj)==8,"TRAP pointer instance_globals_k.kickedobj");
_Static_assert(sizeof(((struct instance_globals_m*)0)->mentioned_water)==1 && (((__typeof__(((struct instance_globals_m*)0)->mentioned_water))-1<0)==1),"TRAP field instance_globals_m.mentioned_water width/sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8 && (((__typeof__(((struct instance_globals_m*)0)->multi))-1<0)==1),"TRAP field instance_globals_m.multi width/sign");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi_reason)==8,"TRAP pointer instance_globals_m.multi_reason");
_Static_assert(sizeof(((struct instance_globals_n*)0)->nomovemsg)==8,"TRAP pointer instance_globals_n.nomovemsg");
_Static_assert(sizeof(((struct instance_globals_o*)0)->otg_otmp)==8,"TRAP pointer instance_globals_o.otg_otmp");
_Static_assert(sizeof(((struct instance_globals_o*)0)->otg_temp)==4 && (((__typeof__(((struct instance_globals_o*)0)->otg_temp))-1<0)==1),"TRAP field instance_globals_o.otg_temp width/sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->stealoid)==4 && (((__typeof__(((struct instance_globals_s*)0)->stealoid))-1<0)==0),"TRAP field instance_globals_s.stealoid width/sign");
_Static_assert(sizeof(((struct instance_globals_s*)0)->stoned)==1 && (((__typeof__(((struct instance_globals_s*)0)->stoned))-1<0)==1),"TRAP field instance_globals_s.stoned width/sign");
_Static_assert(sizeof(((struct instance_globals_t*)0)->thrownobj)==8,"TRAP pointer instance_globals_t.thrownobj");
_Static_assert(sizeof(((struct instance_globals_v*)0)->vision_full_recalc)==1 && (((__typeof__(((struct instance_globals_v*)0)->vision_full_recalc))-1<0)==1),"TRAP field instance_globals_v.vision_full_recalc width/sign");
_Static_assert(sizeof(((struct instance_globals_v*)0)->viz_array)==8,"TRAP pointer instance_globals_v.viz_array");
_Static_assert(sizeof(((struct instance_globals_x*)0)->xstart)==2 && (((__typeof__(((struct instance_globals_x*)0)->xstart))-1<0)==1),"TRAP field instance_globals_x.xstart width/sign");
_Static_assert(sizeof(((struct instance_globals_y*)0)->ystart)==2 && (((__typeof__(((struct instance_globals_y*)0)->ystart))-1<0)==1),"TRAP field instance_globals_y.ystart width/sign");
_Static_assert(sizeof(((struct kinfo*)0)->format)==4 && (((__typeof__(((struct kinfo*)0)->format))-1<0)==1),"TRAP field kinfo.format width/sign");
_Static_assert(sizeof(((struct launchplace*)0)->obj)==8,"TRAP pointer launchplace.obj");
_Static_assert(sizeof(((struct launchplace*)0)->x)==2 && (((__typeof__(((struct launchplace*)0)->x))-1<0)==1),"TRAP field launchplace.x width/sign");
_Static_assert(sizeof(((struct launchplace*)0)->y)==2 && (((__typeof__(((struct launchplace*)0)->y))-1<0)==1),"TRAP field launchplace.y width/sign");
_Static_assert(sizeof(((struct mextra*)0)->mgivenname)==8,"TRAP pointer mextra.mgivenname");
_Static_assert(sizeof(((struct monst*)0)->cham)==2 && (((__typeof__(((struct monst*)0)->cham))-1<0)==1),"TRAP field monst.cham width/sign");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"TRAP pointer monst.data");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"TRAP field monst.m_ap_type width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4 && (((__typeof__(((struct monst*)0)->m_id))-1<0)==0),"TRAP field monst.m_id width/sign");
_Static_assert(sizeof(((struct monst*)0)->meating)==4 && (((__typeof__(((struct monst*)0)->meating))-1<0)==1),"TRAP field monst.meating width/sign");
_Static_assert(sizeof(((struct monst*)0)->mextra)==8,"TRAP pointer monst.mextra");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"TRAP field monst.mhp width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4 && (((__typeof__(((struct monst*)0)->mhpmax))-1<0)==1),"TRAP field monst.mhpmax width/sign");
_Static_assert(sizeof(((struct monst*)0)->minvent)==8,"TRAP pointer monst.minvent");
_Static_assert(sizeof(((struct monst*)0)->misc_worn_check)==8 && (((__typeof__(((struct monst*)0)->misc_worn_check))-1<0)==1),"TRAP field monst.misc_worn_check width/sign");
_Static_assert(sizeof(((struct monst*)0)->mspec_used)==4 && (((__typeof__(((struct monst*)0)->mspec_used))-1<0)==1),"TRAP field monst.mspec_used width/sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"TRAP field monst.mtame width/sign");
_Static_assert(sizeof(((struct monst*)0)->mw)==8,"TRAP pointer monst.mw");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"TRAP field monst.mx width/sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"TRAP field monst.my width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2 && (((__typeof__(((struct nhcoord*)0)->x))-1<0)==1),"TRAP field nhcoord.x width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2 && (((__typeof__(((struct nhcoord*)0)->y))-1<0)==1),"TRAP field nhcoord.y width/sign");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"TRAP pointer obj.cobj");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4 && (((__typeof__(((struct obj*)0)->corpsenm))-1<0)==1),"TRAP field obj.corpsenm width/sign");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"TRAP pointer obj.nobj");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4 && (((__typeof__(((struct obj*)0)->o_id))-1<0)==0),"TRAP field obj.o_id width/sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1 && (((__typeof__(((struct obj*)0)->oartifact))-1<0)==1),"TRAP field obj.oartifact width/sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1 && (((__typeof__(((struct obj*)0)->oclass))-1<0)==1),"TRAP field obj.oclass width/sign");
_Static_assert(sizeof(((struct obj*)0)->oextra)==8,"TRAP pointer obj.oextra");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"TRAP field obj.otyp width/sign");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8 && (((__typeof__(((struct obj*)0)->owornmask))-1<0)==1),"TRAP field obj.owornmask width/sign");
_Static_assert(sizeof(((struct obj*)0)->owt)==4 && (((__typeof__(((struct obj*)0)->owt))-1<0)==0),"TRAP field obj.owt width/sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2 && (((__typeof__(((struct obj*)0)->ox))-1<0)==1),"TRAP field obj.ox width/sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2 && (((__typeof__(((struct obj*)0)->oy))-1<0)==1),"TRAP field obj.oy width/sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"TRAP field obj.quan width/sign");
_Static_assert(sizeof(((struct obj*)0)->spe)==1 && (((__typeof__(((struct obj*)0)->spe))-1<0)==1),"TRAP field obj.spe width/sign");
_Static_assert(sizeof(((struct obj*)0)->usecount)==4 && (((__typeof__(((struct obj*)0)->usecount))-1<0)==1),"TRAP field obj.usecount width/sign");
_Static_assert(sizeof(((struct obj*)0)->where)==1 && (((__typeof__(((struct obj*)0)->where))-1<0)==1),"TRAP field obj.where width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_oprop)==1 && (((__typeof__(((struct objclass*)0)->oc_oprop))-1<0)==0),"TRAP field objclass.oc_oprop width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1 && (((__typeof__(((struct objclass*)0)->oc_subtyp))-1<0)==1),"TRAP field objclass.oc_subtyp width/sign");
_Static_assert(sizeof(((struct oextra*)0)->omonst)==8,"TRAP pointer oextra.omonst");
_Static_assert(sizeof(((struct oextra*)0)->oname)==8,"TRAP pointer oextra.oname");
_Static_assert(sizeof(((struct permonst*)0)->cwt)==4 && (((__typeof__(((struct permonst*)0)->cwt))-1<0)==0),"TRAP field permonst.cwt width/sign");
_Static_assert(sizeof(((struct permonst*)0)->geno)==2 && (((__typeof__(((struct permonst*)0)->geno))-1<0)==0),"TRAP field permonst.geno width/sign");
_Static_assert(sizeof(((struct permonst*)0)->maligntyp)==1 && (((__typeof__(((struct permonst*)0)->maligntyp))-1<0)==1),"TRAP field permonst.maligntyp width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"TRAP field permonst.mflags1 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8 && (((__typeof__(((struct permonst*)0)->mflags2))-1<0)==0),"TRAP field permonst.mflags2 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"TRAP field permonst.mlet width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1 && (((__typeof__(((struct permonst*)0)->mlevel))-1<0)==1),"TRAP field permonst.mlevel width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mmove)==1 && (((__typeof__(((struct permonst*)0)->mmove))-1<0)==1),"TRAP field permonst.mmove width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1 && (((__typeof__(((struct permonst*)0)->msize))-1<0)==0),"TRAP field permonst.msize width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1 && (((__typeof__(((struct permonst*)0)->msound))-1<0)==0),"TRAP field permonst.msound width/sign");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4 && (((__typeof__(((struct permonst*)0)->pmidx))-1<0)==1),"TRAP field permonst.pmidx width/sign");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"TRAP field prop.blocked width/sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"TRAP field prop.extrinsic width/sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"TRAP field prop.intrinsic width/sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"TRAP field rm.typ width/sign");
_Static_assert(sizeof(((struct skills*)0)->skill)==2 && (((__typeof__(((struct skills*)0)->skill))-1<0)==1),"TRAP field skills.skill width/sign");
_Static_assert(sizeof(((struct symdef*)0)->explanation)==8,"TRAP pointer symdef.explanation");
_Static_assert(sizeof(((struct trap*)0)->ntrap)==8,"TRAP pointer trap.ntrap");
_Static_assert(sizeof(((struct trap*)0)->tx)==2 && (((__typeof__(((struct trap*)0)->tx))-1<0)==1),"TRAP field trap.tx width/sign");
_Static_assert(sizeof(((struct trap*)0)->ty)==2 && (((__typeof__(((struct trap*)0)->ty))-1<0)==1),"TRAP field trap.ty width/sign");
_Static_assert(sizeof(((struct u_conduct*)0)->sokocheat)==8 && (((__typeof__(((struct u_conduct*)0)->sokocheat))-1<0)==1),"TRAP field u_conduct.sokocheat width/sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1 && (((__typeof__(((struct u_roleplay*)0)->deaf))-1<0)==1),"TRAP field u_roleplay.deaf width/sign");
_Static_assert(sizeof(((union vlaunchinfo*)0)->v_conjoined)==1 && (((__typeof__(((union vlaunchinfo*)0)->v_conjoined))-1<0)==0),"TRAP field vlaunchinfo.v_conjoined width/sign");
_Static_assert(sizeof(((union vlaunchinfo*)0)->v_launch_otyp)==2 && (((__typeof__(((union vlaunchinfo*)0)->v_launch_otyp))-1<0)==1),"TRAP field vlaunchinfo.v_launch_otyp width/sign");
_Static_assert(sizeof(((union vlaunchinfo*)0)->v_tnote)==2 && (((__typeof__(((union vlaunchinfo*)0)->v_tnote))-1<0)==1),"TRAP field vlaunchinfo.v_tnote width/sign");
_Static_assert(sizeof(((union vptrs*)0)->v_nexthere)==8,"TRAP pointer vptrs.v_nexthere");
_Static_assert(sizeof(((union vptrs*)0)->v_ocarry)==8,"TRAP pointer vptrs.v_ocarry");
_Static_assert(sizeof(((struct window_procs*)0)->win_clear_nhwindow)==8,"TRAP pointer window_procs.win_clear_nhwindow");
_Static_assert(sizeof(((struct window_procs*)0)->win_delay_output)==8,"TRAP pointer window_procs.win_delay_output");
_Static_assert(sizeof(((struct window_procs*)0)->win_display_nhwindow)==8,"TRAP pointer window_procs.win_display_nhwindow");
_Static_assert(sizeof(((struct you*)0)->dx)==4 && (((__typeof__(((struct you*)0)->dx))-1<0)==1),"TRAP field you.dx width/sign");
_Static_assert(sizeof(((struct you*)0)->dy)==4 && (((__typeof__(((struct you*)0)->dy))-1<0)==1),"TRAP field you.dy width/sign");
_Static_assert(sizeof(((struct you*)0)->dz)==4 && (((__typeof__(((struct you*)0)->dz))-1<0)==1),"TRAP field you.dz width/sign");
_Static_assert(sizeof(((struct you*)0)->mh)==4 && (((__typeof__(((struct you*)0)->mh))-1<0)==1),"TRAP field you.mh width/sign");
_Static_assert(sizeof(((struct you*)0)->mhmax)==4 && (((__typeof__(((struct you*)0)->mhmax))-1<0)==1),"TRAP field you.mhmax width/sign");
_Static_assert(sizeof(((struct you*)0)->moreluck)==1 && (((__typeof__(((struct you*)0)->moreluck))-1<0)==1),"TRAP field you.moreluck width/sign");
_Static_assert(sizeof(((struct you*)0)->twoweap)==1 && (((__typeof__(((struct you*)0)->twoweap))-1<0)==1),"TRAP field you.twoweap width/sign");
_Static_assert(sizeof(((struct you*)0)->uen)==4 && (((__typeof__(((struct you*)0)->uen))-1<0)==1),"TRAP field you.uen width/sign");
_Static_assert(sizeof(((struct you*)0)->uenmax)==4 && (((__typeof__(((struct you*)0)->uenmax))-1<0)==1),"TRAP field you.uenmax width/sign");
_Static_assert(sizeof(((struct you*)0)->uenpeak)==4 && (((__typeof__(((struct you*)0)->uenpeak))-1<0)==1),"TRAP field you.uenpeak width/sign");
_Static_assert(sizeof(((struct you*)0)->uhp)==4 && (((__typeof__(((struct you*)0)->uhp))-1<0)==1),"TRAP field you.uhp width/sign");
_Static_assert(sizeof(((struct you*)0)->uhpmax)==4 && (((__typeof__(((struct you*)0)->uhpmax))-1<0)==1),"TRAP field you.uhpmax width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4 && (((__typeof__(((struct you*)0)->ulevel))-1<0)==1),"TRAP field you.ulevel width/sign");
_Static_assert(sizeof(((struct you*)0)->uluck)==1 && (((__typeof__(((struct you*)0)->uluck))-1<0)==1),"TRAP field you.uluck width/sign");
_Static_assert(sizeof(((struct you*)0)->umonnum)==4 && (((__typeof__(((struct you*)0)->umonnum))-1<0)==1),"TRAP field you.umonnum width/sign");
_Static_assert(sizeof(((struct you*)0)->umonster)==4 && (((__typeof__(((struct you*)0)->umonster))-1<0)==1),"TRAP field you.umonster width/sign");
_Static_assert(sizeof(((struct you*)0)->umortality)==4 && (((__typeof__(((struct you*)0)->umortality))-1<0)==1),"TRAP field you.umortality width/sign");
_Static_assert(sizeof(((struct you*)0)->umoved)==1 && (((__typeof__(((struct you*)0)->umoved))-1<0)==1),"TRAP field you.umoved width/sign");
_Static_assert(sizeof(((struct you*)0)->usleep)==8 && (((__typeof__(((struct you*)0)->usleep))-1<0)==1),"TRAP field you.usleep width/sign");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"TRAP pointer you.usteed");
_Static_assert(sizeof(((struct you*)0)->ustuck)==8,"TRAP pointer you.ustuck");
_Static_assert(sizeof(((struct you*)0)->utrap)==4 && (((__typeof__(((struct you*)0)->utrap))-1<0)==0),"TRAP field you.utrap width/sign");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4 && (((__typeof__(((struct you*)0)->utraptype))-1<0)==0),"TRAP field you.utraptype width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"TRAP field you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->ux0)==2 && (((__typeof__(((struct you*)0)->ux0))-1<0)==1),"TRAP field you.ux0 width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"TRAP field you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->uy0)==2 && (((__typeof__(((struct you*)0)->uy0))-1<0)==1),"TRAP field you.uy0 width/sign");
extern boolean teleport_trap_js_burnarmor(struct monst * victim);
boolean teleport_trap_entry_burnarmor(struct monst * victim){return teleport_trap_js_burnarmor(victim);}
boolean burnarmor(struct monst * victim){return teleport_trap_entry_burnarmor(victim);}
extern int teleport_trap_js_erode_obj(struct obj * otmp,const char * ostr,int type,int ef_flags);
int teleport_trap_entry_erode_obj(struct obj * otmp,const char * ostr,int type,int ef_flags){return teleport_trap_js_erode_obj(otmp,ostr,type,ef_flags);}
int erode_obj(struct obj * otmp,const char * ostr,int type,int ef_flags){return teleport_trap_entry_erode_obj(otmp,ostr,type,ef_flags);}
extern boolean teleport_trap_js_grease_protect(struct obj * otmp,const char * ostr,struct monst * victim);
boolean teleport_trap_entry_grease_protect(struct obj * otmp,const char * ostr,struct monst * victim){return teleport_trap_js_grease_protect(otmp,ostr,victim);}
boolean grease_protect(struct obj * otmp,const char * ostr,struct monst * victim){return teleport_trap_entry_grease_protect(otmp,ostr,victim);}
extern void teleport_trap_js_mk_trap_statue(coordxy x,coordxy y);
void teleport_trap_entry_mk_trap_statue(coordxy x,coordxy y){teleport_trap_js_mk_trap_statue(x,y);}
extern int teleport_trap_js_dng_bottom(d_level * lev);
int teleport_trap_entry_dng_bottom(d_level * lev){return teleport_trap_js_dng_bottom(lev);}
extern void teleport_trap_js_hole_destination(d_level * dst);
void teleport_trap_entry_hole_destination(d_level * dst){teleport_trap_js_hole_destination(dst);}
extern struct trap * teleport_trap_js_maketrap(coordxy x,coordxy y,int typ);
struct trap * teleport_trap_entry_maketrap(coordxy x,coordxy y,int typ){return teleport_trap_js_maketrap(x,y,typ);}
struct trap * maketrap(coordxy x,coordxy y,int typ){return teleport_trap_entry_maketrap(x,y,typ);}
extern d_level * teleport_trap_js_clamp_hole_destination(d_level * dlev);
d_level * teleport_trap_entry_clamp_hole_destination(d_level * dlev){return teleport_trap_js_clamp_hole_destination(dlev);}
d_level * clamp_hole_destination(d_level * dlev){return teleport_trap_entry_clamp_hole_destination(dlev);}
extern void teleport_trap_js_fall_through(boolean td,unsigned int ftflags);
void teleport_trap_entry_fall_through(boolean td,unsigned int ftflags){teleport_trap_js_fall_through(td,ftflags);}
void fall_through(boolean td,unsigned int ftflags){teleport_trap_entry_fall_through(td,ftflags);}
extern struct monst * teleport_trap_js_animate_statue(struct obj * statue,coordxy x,coordxy y,int cause,int * fail_reason);
struct monst * teleport_trap_entry_animate_statue(struct obj * statue,coordxy x,coordxy y,int cause,int * fail_reason){return teleport_trap_js_animate_statue(statue,x,y,cause,fail_reason);}
struct monst * animate_statue(struct obj * statue,coordxy x,coordxy y,int cause,int * fail_reason){return teleport_trap_entry_animate_statue(statue,x,y,cause,fail_reason);}
extern struct monst * teleport_trap_js_activate_statue_trap(struct trap * trap,coordxy x,coordxy y,boolean shatter);
struct monst * teleport_trap_entry_activate_statue_trap(struct trap * trap,coordxy x,coordxy y,boolean shatter){return teleport_trap_js_activate_statue_trap(trap,x,y,shatter);}
struct monst * activate_statue_trap(struct trap * trap,coordxy x,coordxy y,boolean shatter){return teleport_trap_entry_activate_statue_trap(trap,x,y,shatter);}
extern boolean teleport_trap_js_keep_saddle_with_steedcorpse(unsigned int steed_mid,struct obj * objchn,struct obj * saddle);
boolean teleport_trap_entry_keep_saddle_with_steedcorpse(unsigned int steed_mid,struct obj * objchn,struct obj * saddle){return teleport_trap_js_keep_saddle_with_steedcorpse(steed_mid,objchn,saddle);}
extern boolean teleport_trap_js_mu_maybe_destroy_web(struct monst * mtmp,boolean domsg,struct trap * trap);
boolean teleport_trap_entry_mu_maybe_destroy_web(struct monst * mtmp,boolean domsg,struct trap * trap){return teleport_trap_js_mu_maybe_destroy_web(mtmp,domsg,trap);}
extern struct obj * teleport_trap_js_t_missile(int otyp,struct trap * trap);
struct obj * teleport_trap_entry_t_missile(int otyp,struct trap * trap){return teleport_trap_js_t_missile(otyp,trap);}
extern void teleport_trap_js_set_utrap(unsigned int tim,unsigned int typ);
void teleport_trap_entry_set_utrap(unsigned int tim,unsigned int typ){teleport_trap_js_set_utrap(tim,typ);}
void set_utrap(unsigned int tim,unsigned int typ){teleport_trap_entry_set_utrap(tim,typ);}
extern void teleport_trap_js_reset_utrap(boolean msg);
void teleport_trap_entry_reset_utrap(boolean msg){teleport_trap_js_reset_utrap(msg);}
void reset_utrap(boolean msg){teleport_trap_entry_reset_utrap(msg);}
extern boolean teleport_trap_js_floor_trigger(int ttyp);
boolean teleport_trap_entry_floor_trigger(int ttyp){return teleport_trap_js_floor_trigger(ttyp);}
extern boolean teleport_trap_js_check_in_air(struct monst * mtmp,unsigned int trflags);
boolean teleport_trap_entry_check_in_air(struct monst * mtmp,unsigned int trflags){return teleport_trap_js_check_in_air(mtmp,trflags);}
extern boolean teleport_trap_js_wearing_iron_shoes(struct monst * mtmp);
boolean teleport_trap_entry_wearing_iron_shoes(struct monst * mtmp){return teleport_trap_js_wearing_iron_shoes(mtmp);}
boolean wearing_iron_shoes(struct monst * mtmp){return teleport_trap_entry_wearing_iron_shoes(mtmp);}
extern boolean teleport_trap_js_m_harmless_trap(struct monst * mtmp,struct trap * ttmp);
boolean teleport_trap_entry_m_harmless_trap(struct monst * mtmp,struct trap * ttmp){return teleport_trap_js_m_harmless_trap(mtmp,ttmp);}
boolean m_harmless_trap(struct monst * mtmp,struct trap * ttmp){return teleport_trap_entry_m_harmless_trap(mtmp,ttmp);}
extern int teleport_trap_js_trapeffect_arrow_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_arrow_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_arrow_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_dart_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_dart_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_dart_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_rocktrap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_rocktrap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_rocktrap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_sqky_board(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_sqky_board(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_sqky_board(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_bear_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_bear_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_bear_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_slp_gas_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_slp_gas_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_slp_gas_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_rust_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_rust_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_rust_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_fire_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_fire_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_fire_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_pit(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_pit(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_pit(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_hole(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_hole(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_hole(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_telep_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_telep_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_telep_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_level_telep(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_level_telep(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_level_telep(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_web(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_web(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_web(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_statue_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_statue_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_statue_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_magic_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_magic_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_magic_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_anti_magic(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_anti_magic(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_anti_magic(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_poly_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_poly_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_poly_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_landmine(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_landmine(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_landmine(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_rolling_boulder_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_rolling_boulder_trap(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_rolling_boulder_trap(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_magic_portal(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_magic_portal(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_magic_portal(mtmp,trap,trflags);}
extern int teleport_trap_js_trapeffect_vibrating_square(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_vibrating_square(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_vibrating_square(mtmp,trap,trflags);}
extern int teleport_trap_js_immune_to_trap(struct monst * mon,unsigned int ttype);
int teleport_trap_entry_immune_to_trap(struct monst * mon,unsigned int ttype){return teleport_trap_js_immune_to_trap(mon,ttype);}
int immune_to_trap(struct monst * mon,unsigned int ttype){return teleport_trap_entry_immune_to_trap(mon,ttype);}
extern int teleport_trap_js_trapeffect_selector(struct monst * mtmp,struct trap * trap,unsigned int trflags);
int teleport_trap_entry_trapeffect_selector(struct monst * mtmp,struct trap * trap,unsigned int trflags){return teleport_trap_js_trapeffect_selector(mtmp,trap,trflags);}
extern void teleport_trap_js_dotrap(struct trap * trap,unsigned int trflags);
void teleport_trap_entry_dotrap(struct trap * trap,unsigned int trflags){teleport_trap_js_dotrap(trap,trflags);}
void dotrap(struct trap * trap,unsigned int trflags){teleport_trap_entry_dotrap(trap,trflags);}
extern char * teleport_trap_js_trapnote(struct trap * trap,boolean noprefix);
char * teleport_trap_entry_trapnote(struct trap * trap,boolean noprefix){return teleport_trap_js_trapnote(trap,noprefix);}
extern int teleport_trap_js_choose_trapnote(struct trap * ttmp);
int teleport_trap_entry_choose_trapnote(struct trap * ttmp){return teleport_trap_js_choose_trapnote(ttmp);}
extern int teleport_trap_js_steedintrap(struct trap * trap,struct obj * otmp);
int teleport_trap_entry_steedintrap(struct trap * trap,struct obj * otmp){return teleport_trap_js_steedintrap(trap,otmp);}
extern void teleport_trap_js_blow_up_landmine(struct trap * trap);
void teleport_trap_entry_blow_up_landmine(struct trap * trap){teleport_trap_js_blow_up_landmine(trap);}
void blow_up_landmine(struct trap * trap){teleport_trap_entry_blow_up_landmine(trap);}
extern void teleport_trap_js_launch_drop_spot(struct obj * obj,coordxy x,coordxy y);
void teleport_trap_entry_launch_drop_spot(struct obj * obj,coordxy x,coordxy y){teleport_trap_js_launch_drop_spot(obj,x,y);}
extern boolean teleport_trap_js_launch_in_progress(void);
boolean teleport_trap_entry_launch_in_progress(void){return teleport_trap_js_launch_in_progress();}
boolean launch_in_progress(void){return teleport_trap_entry_launch_in_progress();}
extern void teleport_trap_js_force_launch_placement(void);
void teleport_trap_entry_force_launch_placement(void){teleport_trap_js_force_launch_placement();}
void force_launch_placement(void){teleport_trap_entry_force_launch_placement();}
extern int teleport_trap_js_launch_obj(short otyp,coordxy x1,coordxy y1,coordxy x2,coordxy y2,int style);
int teleport_trap_entry_launch_obj(short otyp,coordxy x1,coordxy y1,coordxy x2,coordxy y2,int style){return teleport_trap_js_launch_obj(otyp,x1,y1,x2,y2,style);}
int launch_obj(short otyp,coordxy x1,coordxy y1,coordxy x2,coordxy y2,int style){return teleport_trap_entry_launch_obj(otyp,x1,y1,x2,y2,style);}
extern void teleport_trap_js_seetrap(struct trap * trap);
void teleport_trap_entry_seetrap(struct trap * trap){teleport_trap_js_seetrap(trap);}
void seetrap(struct trap * trap){teleport_trap_entry_seetrap(trap);}
extern void teleport_trap_js_feeltrap(struct trap * trap);
void teleport_trap_entry_feeltrap(struct trap * trap){teleport_trap_js_feeltrap(trap);}
void feeltrap(struct trap * trap){teleport_trap_entry_feeltrap(trap);}
extern boolean teleport_trap_js_find_random_launch_coord(struct trap * ttmp,coord * cc);
boolean teleport_trap_entry_find_random_launch_coord(struct trap * ttmp,coord * cc){return teleport_trap_js_find_random_launch_coord(ttmp,cc);}
extern int teleport_trap_js_mkroll_launch(struct trap * ttmp,coordxy x,coordxy y,short otyp,long ocount);
int teleport_trap_entry_mkroll_launch(struct trap * ttmp,coordxy x,coordxy y,short otyp,long ocount){return teleport_trap_js_mkroll_launch(ttmp,x,y,otyp,ocount);}
extern boolean teleport_trap_js_isclearpath(coord * cc,int distance,schar dx,schar dy);
boolean teleport_trap_entry_isclearpath(coord * cc,int distance,schar dx,schar dy){return teleport_trap_js_isclearpath(cc,distance,dx,dy);}
extern boolean teleport_trap_js_m_easy_escape_pit(struct monst * mtmp);
boolean teleport_trap_entry_m_easy_escape_pit(struct monst * mtmp){return teleport_trap_js_m_easy_escape_pit(mtmp);}
extern int teleport_trap_js_mintrap(struct monst * mtmp,unsigned int mintrapflags);
int teleport_trap_entry_mintrap(struct monst * mtmp,unsigned int mintrapflags){return teleport_trap_js_mintrap(mtmp,mintrapflags);}
int mintrap(struct monst * mtmp,unsigned int mintrapflags){return teleport_trap_entry_mintrap(mtmp,mintrapflags);}
extern void teleport_trap_js_instapetrify(const char * str);
void teleport_trap_entry_instapetrify(const char * str){teleport_trap_js_instapetrify(str);}
void instapetrify(const char * str){teleport_trap_entry_instapetrify(str);}
extern void teleport_trap_js_minstapetrify(struct monst * mon,boolean byplayer);
void teleport_trap_entry_minstapetrify(struct monst * mon,boolean byplayer){teleport_trap_js_minstapetrify(mon,byplayer);}
void minstapetrify(struct monst * mon,boolean byplayer){teleport_trap_entry_minstapetrify(mon,byplayer);}
extern void teleport_trap_js_selftouch(const char * arg);
void teleport_trap_entry_selftouch(const char * arg){teleport_trap_js_selftouch(arg);}
void selftouch(const char * arg){teleport_trap_entry_selftouch(arg);}
extern void teleport_trap_js_mselftouch(struct monst * mon,const char * arg,boolean byplayer);
void teleport_trap_entry_mselftouch(struct monst * mon,const char * arg,boolean byplayer){teleport_trap_js_mselftouch(mon,arg,byplayer);}
void mselftouch(struct monst * mon,const char * arg,boolean byplayer){teleport_trap_entry_mselftouch(mon,arg,byplayer);}
extern void teleport_trap_js_float_up(void);
void teleport_trap_entry_float_up(void){teleport_trap_js_float_up();}
void float_up(void){teleport_trap_entry_float_up();}
extern void teleport_trap_js_fill_pit(coordxy x,coordxy y);
void teleport_trap_entry_fill_pit(coordxy x,coordxy y){teleport_trap_js_fill_pit(x,y);}
void fill_pit(coordxy x,coordxy y){teleport_trap_entry_fill_pit(x,y);}
extern int teleport_trap_js_float_down(long hmask,long emask);
int teleport_trap_entry_float_down(long hmask,long emask){return teleport_trap_js_float_down(hmask,emask);}
int float_down(long hmask,long emask){return teleport_trap_entry_float_down(hmask,emask);}
extern void teleport_trap_js_climb_pit(void);
void teleport_trap_entry_climb_pit(void){teleport_trap_js_climb_pit();}
void climb_pit(void){teleport_trap_entry_climb_pit();}
extern void teleport_trap_js_dofiretrap(struct obj * box);
void teleport_trap_entry_dofiretrap(struct obj * box){teleport_trap_js_dofiretrap(box);}
extern void teleport_trap_js_domagictrap(void);
void teleport_trap_entry_domagictrap(void){teleport_trap_js_domagictrap();}
extern boolean teleport_trap_js_fire_damage(struct obj * obj,boolean force,coordxy x,coordxy y);
boolean teleport_trap_entry_fire_damage(struct obj * obj,boolean force,coordxy x,coordxy y){return teleport_trap_js_fire_damage(obj,force,x,y);}
boolean fire_damage(struct obj * obj,boolean force,coordxy x,coordxy y){return teleport_trap_entry_fire_damage(obj,force,x,y);}
extern int teleport_trap_js_fire_damage_chain(struct obj * chain,boolean force,boolean here,coordxy x,coordxy y);
int teleport_trap_entry_fire_damage_chain(struct obj * chain,boolean force,boolean here,coordxy x,coordxy y){return teleport_trap_js_fire_damage_chain(chain,force,here,x,y);}
int fire_damage_chain(struct obj * chain,boolean force,boolean here,coordxy x,coordxy y){return teleport_trap_entry_fire_damage_chain(chain,force,here,x,y);}
extern boolean teleport_trap_js_lava_damage(struct obj * obj,coordxy x,coordxy y);
boolean teleport_trap_entry_lava_damage(struct obj * obj,coordxy x,coordxy y){return teleport_trap_js_lava_damage(obj,x,y);}
boolean lava_damage(struct obj * obj,coordxy x,coordxy y){return teleport_trap_entry_lava_damage(obj,x,y);}
extern void teleport_trap_js_acid_damage(struct obj * obj);
void teleport_trap_entry_acid_damage(struct obj * obj){teleport_trap_js_acid_damage(obj);}
void acid_damage(struct obj * obj){teleport_trap_entry_acid_damage(obj);}
extern void teleport_trap_js_pot_acid_damage(struct obj * obj,boolean in_invent,boolean described);
void teleport_trap_entry_pot_acid_damage(struct obj * obj,boolean in_invent,boolean described){teleport_trap_js_pot_acid_damage(obj,in_invent,described);}
extern int teleport_trap_js_water_damage(struct obj * obj,const char * ostr,boolean force);
int teleport_trap_entry_water_damage(struct obj * obj,const char * ostr,boolean force){return teleport_trap_js_water_damage(obj,ostr,force);}
int water_damage(struct obj * obj,const char * ostr,boolean force){return teleport_trap_entry_water_damage(obj,ostr,force);}
extern void teleport_trap_js_water_damage_chain(struct obj * obj,boolean here);
void teleport_trap_entry_water_damage_chain(struct obj * obj,boolean here){teleport_trap_js_water_damage_chain(obj,here);}
void water_damage_chain(struct obj * obj,boolean here){teleport_trap_entry_water_damage_chain(obj,here);}
extern boolean teleport_trap_js_emergency_disrobe(boolean * lostsome);
boolean teleport_trap_entry_emergency_disrobe(boolean * lostsome){return teleport_trap_js_emergency_disrobe(lostsome);}
extern boolean teleport_trap_js_rnd_nextto_goodpos(coordxy * x,coordxy * y,struct monst * mtmp);
boolean teleport_trap_entry_rnd_nextto_goodpos(coordxy * x,coordxy * y,struct monst * mtmp){return teleport_trap_js_rnd_nextto_goodpos(x,y,mtmp);}
boolean rnd_nextto_goodpos(coordxy * x,coordxy * y,struct monst * mtmp){return teleport_trap_entry_rnd_nextto_goodpos(x,y,mtmp);}
extern void teleport_trap_js_back_on_ground(boolean rescued);
void teleport_trap_entry_back_on_ground(boolean rescued){teleport_trap_js_back_on_ground(rescued);}
void back_on_ground(boolean rescued){teleport_trap_entry_back_on_ground(rescued);}
extern void teleport_trap_js_rescued_from_terrain(int how);
void teleport_trap_entry_rescued_from_terrain(int how){teleport_trap_js_rescued_from_terrain(how);}
void rescued_from_terrain(int how){teleport_trap_entry_rescued_from_terrain(how);}
extern boolean teleport_trap_js_drown(void);
boolean teleport_trap_entry_drown(void){return teleport_trap_js_drown();}
boolean drown(void){return teleport_trap_entry_drown();}
extern void teleport_trap_js_drain_en(int n,boolean max_already_drained);
void teleport_trap_entry_drain_en(int n,boolean max_already_drained){teleport_trap_js_drain_en(n,max_already_drained);}
void drain_en(int n,boolean max_already_drained){teleport_trap_entry_drain_en(n,max_already_drained);}
extern int teleport_trap_js_dountrap(void);
int teleport_trap_entry_dountrap(void){return teleport_trap_js_dountrap();}
int dountrap(void){return teleport_trap_entry_dountrap();}
extern int teleport_trap_js_could_untrap(boolean verbosely,boolean check_floor);
int teleport_trap_entry_could_untrap(boolean verbosely,boolean check_floor){return teleport_trap_js_could_untrap(verbosely,check_floor);}
int could_untrap(boolean verbosely,boolean check_floor){return teleport_trap_entry_could_untrap(verbosely,check_floor);}
extern int teleport_trap_js_untrap_prob(struct trap * ttmp);
int teleport_trap_entry_untrap_prob(struct trap * ttmp){return teleport_trap_js_untrap_prob(ttmp);}
extern void teleport_trap_js_cnv_trap_obj(int otyp,int cnt,struct trap * ttmp,boolean bury_it);
void teleport_trap_entry_cnv_trap_obj(int otyp,int cnt,struct trap * ttmp,boolean bury_it){teleport_trap_js_cnv_trap_obj(otyp,cnt,ttmp,bury_it);}
void cnv_trap_obj(int otyp,int cnt,struct trap * ttmp,boolean bury_it){teleport_trap_entry_cnv_trap_obj(otyp,cnt,ttmp,bury_it);}
extern boolean teleport_trap_js_into_vs_onto(int traptype);
boolean teleport_trap_entry_into_vs_onto(int traptype){return teleport_trap_js_into_vs_onto(traptype);}
boolean into_vs_onto(int traptype){return teleport_trap_entry_into_vs_onto(traptype);}
extern void teleport_trap_js_move_into_trap(struct trap * ttmp);
void teleport_trap_entry_move_into_trap(struct trap * ttmp){teleport_trap_js_move_into_trap(ttmp);}
extern int teleport_trap_js_try_disarm(struct trap * ttmp,boolean force_failure);
int teleport_trap_entry_try_disarm(struct trap * ttmp,boolean force_failure){return teleport_trap_js_try_disarm(ttmp,force_failure);}
extern void teleport_trap_js_reward_untrap(struct trap * ttmp,struct monst * mtmp);
void teleport_trap_entry_reward_untrap(struct trap * ttmp,struct monst * mtmp){teleport_trap_js_reward_untrap(ttmp,mtmp);}
extern int teleport_trap_js_disarm_holdingtrap(struct trap * ttmp);
int teleport_trap_entry_disarm_holdingtrap(struct trap * ttmp){return teleport_trap_js_disarm_holdingtrap(ttmp);}
extern int teleport_trap_js_disarm_landmine(struct trap * ttmp);
int teleport_trap_entry_disarm_landmine(struct trap * ttmp){return teleport_trap_js_disarm_landmine(ttmp);}
extern int teleport_trap_js_unsqueak_ok(struct obj * obj);
int teleport_trap_entry_unsqueak_ok(struct obj * obj){return teleport_trap_js_unsqueak_ok(obj);}
extern int teleport_trap_js_disarm_squeaky_board(struct trap * ttmp);
int teleport_trap_entry_disarm_squeaky_board(struct trap * ttmp){return teleport_trap_js_disarm_squeaky_board(ttmp);}
extern int teleport_trap_js_disarm_shooting_trap(struct trap * ttmp,int otyp);
int teleport_trap_entry_disarm_shooting_trap(struct trap * ttmp,int otyp){return teleport_trap_js_disarm_shooting_trap(ttmp,otyp);}
extern int teleport_trap_js_try_lift(struct monst * mtmp,struct trap * ttmp,int xtra_wt,boolean stuff);
int teleport_trap_entry_try_lift(struct monst * mtmp,struct trap * ttmp,int xtra_wt,boolean stuff){return teleport_trap_js_try_lift(mtmp,ttmp,xtra_wt,stuff);}
extern int teleport_trap_js_help_monster_out(struct monst * mtmp,struct trap * ttmp);
int teleport_trap_entry_help_monster_out(struct monst * mtmp,struct trap * ttmp){return teleport_trap_js_help_monster_out(mtmp,ttmp);}
extern void teleport_trap_js_disarm_box(struct obj * box,boolean force,boolean confused);
void teleport_trap_entry_disarm_box(struct obj * box,boolean force,boolean confused){teleport_trap_js_disarm_box(box,force,confused);}
extern void teleport_trap_js_untrap_box(struct obj * box,boolean force,boolean confused);
void teleport_trap_entry_untrap_box(struct obj * box,boolean force,boolean confused){teleport_trap_js_untrap_box(box,force,confused);}
extern int teleport_trap_js_untrap(boolean force,coordxy rx,coordxy ry,struct obj * container);
int teleport_trap_entry_untrap(boolean force,coordxy rx,coordxy ry,struct obj * container){return teleport_trap_js_untrap(force,rx,ry,container);}
int untrap(boolean force,coordxy rx,coordxy ry,struct obj * container){return teleport_trap_entry_untrap(force,rx,ry,container);}
extern boolean teleport_trap_js_openholdingtrap(struct monst * mon,boolean * noticed);
boolean teleport_trap_entry_openholdingtrap(struct monst * mon,boolean * noticed){return teleport_trap_js_openholdingtrap(mon,noticed);}
boolean openholdingtrap(struct monst * mon,boolean * noticed){return teleport_trap_entry_openholdingtrap(mon,noticed);}
extern boolean teleport_trap_js_closeholdingtrap(struct monst * mon,boolean * noticed);
boolean teleport_trap_entry_closeholdingtrap(struct monst * mon,boolean * noticed){return teleport_trap_js_closeholdingtrap(mon,noticed);}
boolean closeholdingtrap(struct monst * mon,boolean * noticed){return teleport_trap_entry_closeholdingtrap(mon,noticed);}
extern boolean teleport_trap_js_openfallingtrap(struct monst * mon,boolean trapdoor_only,boolean * noticed);
boolean teleport_trap_entry_openfallingtrap(struct monst * mon,boolean trapdoor_only,boolean * noticed){return teleport_trap_js_openfallingtrap(mon,trapdoor_only,noticed);}
boolean openfallingtrap(struct monst * mon,boolean trapdoor_only,boolean * noticed){return teleport_trap_entry_openfallingtrap(mon,trapdoor_only,noticed);}
extern boolean teleport_trap_js_chest_trap(struct obj * obj,int bodypart,boolean disarm);
boolean teleport_trap_entry_chest_trap(struct obj * obj,int bodypart,boolean disarm){return teleport_trap_js_chest_trap(obj,bodypart,disarm);}
boolean chest_trap(struct obj * obj,int bodypart,boolean disarm){return teleport_trap_entry_chest_trap(obj,bodypart,disarm);}
extern struct trap * teleport_trap_js_t_at(coordxy x,coordxy y);
struct trap * teleport_trap_entry_t_at(coordxy x,coordxy y){return teleport_trap_js_t_at(x,y);}
struct trap * t_at(coordxy x,coordxy y){return teleport_trap_entry_t_at(x,y);}
extern int teleport_trap_js_count_traps(int ttyp);
int teleport_trap_entry_count_traps(int ttyp){return teleport_trap_js_count_traps(ttyp);}
int count_traps(int ttyp){return teleport_trap_entry_count_traps(ttyp);}
extern void teleport_trap_js_deltrap(struct trap * trap);
void teleport_trap_entry_deltrap(struct trap * trap){teleport_trap_js_deltrap(trap);}
void deltrap(struct trap * trap){teleport_trap_entry_deltrap(trap);}
extern boolean teleport_trap_js_conjoined_pits(struct trap * trap2,struct trap * trap1,boolean u_entering_trap2);
boolean teleport_trap_entry_conjoined_pits(struct trap * trap2,struct trap * trap1,boolean u_entering_trap2){return teleport_trap_js_conjoined_pits(trap2,trap1,u_entering_trap2);}
boolean conjoined_pits(struct trap * trap2,struct trap * trap1,boolean u_entering_trap2){return teleport_trap_entry_conjoined_pits(trap2,trap1,u_entering_trap2);}
extern void teleport_trap_js_clear_conjoined_pits(struct trap * trap);
void teleport_trap_entry_clear_conjoined_pits(struct trap * trap){teleport_trap_js_clear_conjoined_pits(trap);}
extern boolean teleport_trap_js_adj_nonconjoined_pit(struct trap * adjtrap);
boolean teleport_trap_entry_adj_nonconjoined_pit(struct trap * adjtrap){return teleport_trap_js_adj_nonconjoined_pit(adjtrap);}
extern boolean teleport_trap_js_uteetering_at_seen_pit(struct trap * trap);
boolean teleport_trap_entry_uteetering_at_seen_pit(struct trap * trap){return teleport_trap_js_uteetering_at_seen_pit(trap);}
boolean uteetering_at_seen_pit(struct trap * trap){return teleport_trap_entry_uteetering_at_seen_pit(trap);}
extern boolean teleport_trap_js_uescaped_shaft(struct trap * trap);
boolean teleport_trap_entry_uescaped_shaft(struct trap * trap){return teleport_trap_js_uescaped_shaft(trap);}
boolean uescaped_shaft(struct trap * trap){return teleport_trap_entry_uescaped_shaft(trap);}
extern boolean teleport_trap_js_delfloortrap(struct trap * ttmp);
boolean teleport_trap_entry_delfloortrap(struct trap * ttmp){return teleport_trap_js_delfloortrap(ttmp);}
boolean delfloortrap(struct trap * ttmp){return teleport_trap_entry_delfloortrap(ttmp);}
extern void teleport_trap_js_b_trapped(const char * item,int bodypart);
void teleport_trap_entry_b_trapped(const char * item,int bodypart){teleport_trap_js_b_trapped(item,bodypart);}
void b_trapped(const char * item,int bodypart){teleport_trap_entry_b_trapped(item,bodypart);}
extern boolean teleport_trap_js_thitm(int tlev,struct monst * mon,struct obj * obj,int d_override,boolean nocorpse);
boolean teleport_trap_entry_thitm(int tlev,struct monst * mon,struct obj * obj,int d_override,boolean nocorpse){return teleport_trap_js_thitm(tlev,mon,obj,d_override,nocorpse);}
extern boolean teleport_trap_js_unconscious(void);
boolean teleport_trap_entry_unconscious(void){return teleport_trap_js_unconscious();}
boolean unconscious(void){return teleport_trap_entry_unconscious();}
extern boolean teleport_trap_js_lava_effects(void);
boolean teleport_trap_entry_lava_effects(void){return teleport_trap_js_lava_effects();}
boolean lava_effects(void){return teleport_trap_entry_lava_effects();}
extern void teleport_trap_js_sink_into_lava(void);
void teleport_trap_entry_sink_into_lava(void){teleport_trap_js_sink_into_lava();}
void sink_into_lava(void){teleport_trap_entry_sink_into_lava();}
extern void teleport_trap_js_sokoban_guilt(void);
void teleport_trap_entry_sokoban_guilt(void){teleport_trap_js_sokoban_guilt();}
void sokoban_guilt(void){teleport_trap_entry_sokoban_guilt();}
extern void teleport_trap_js_maybe_finish_sokoban(void);
void teleport_trap_entry_maybe_finish_sokoban(void){teleport_trap_js_maybe_finish_sokoban();}
extern const char * teleport_trap_js_trapname(int ttyp,boolean override);
const char * teleport_trap_entry_trapname(int ttyp,boolean override){return teleport_trap_js_trapname(ttyp,override);}
const char * trapname(int ttyp,boolean override){return teleport_trap_entry_trapname(ttyp,override);}
extern void teleport_trap_js_ignite_items(struct obj * objchn);
void teleport_trap_entry_ignite_items(struct obj * objchn){teleport_trap_js_ignite_items(objchn);}
void ignite_items(struct obj * objchn){teleport_trap_entry_ignite_items(objchn);}
extern void teleport_trap_js_trap_ice_effects(coordxy x,coordxy y,boolean ice_is_melting);
void teleport_trap_entry_trap_ice_effects(coordxy x,coordxy y,boolean ice_is_melting){teleport_trap_js_trap_ice_effects(x,y,ice_is_melting);}
void trap_ice_effects(coordxy x,coordxy y,boolean ice_is_melting){teleport_trap_entry_trap_ice_effects(x,y,ice_is_melting);}
extern void teleport_trap_js_trap_sanity_check(void);
void teleport_trap_entry_trap_sanity_check(void){teleport_trap_js_trap_sanity_check();}
void trap_sanity_check(void){teleport_trap_entry_trap_sanity_check();}
uintptr_t teleport_trap_function_pointer(int index){switch(index){
case 0:return (uintptr_t)&ansimpleoname;
case 1:return (uintptr_t)&doname;
case 2:return (uintptr_t)&rn2_on_display_rng;
case 3:return (uintptr_t)&teleport_trap_entry_unsqueak_ok;
case 4:return (uintptr_t)&xname;
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
uint64_t teleport_trap_api_0(int a0){return (uint64_t)(uintptr_t)(carrying)((int)a0);}
uint64_t teleport_trap_api_1(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(m_carrying)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_2(void){return (rng_log_enabled)();}
void teleport_trap_api_3(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_4(int a0){return (rn2)((int)a0);}
int teleport_trap_api_5(int a0){return (rn2)((int)a0);}
void teleport_trap_api_6(uint64_t a0,int a1,int a2){(dry_a_towel)((struct obj *)(uintptr_t)a0,(int)a1,(signed char)a2);}
int teleport_trap_api_7(void){return (rng_log_enabled)();}
void teleport_trap_api_8(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_9(int a0){return (rn2)((int)a0);}
int teleport_trap_api_10(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_11(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_12(uint64_t a0){return (uint64_t)(uintptr_t)(helm_simple_name)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_13(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_14(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_15(uint64_t a0){return (uint64_t)(uintptr_t)(cloak_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_16(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_17(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_18(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_19(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_20(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_21(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
int teleport_trap_api_22(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_23(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
int teleport_trap_api_24(int a0,int a1,int a2,int a3){return (dist2)((short)a0,(short)a1,(short)a2,(short)a3);}
int teleport_trap_api_25(int a0){return (inventory_resistance_check)((int)a0);}
int teleport_trap_api_26(uint64_t a0){return (is_flammable)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_27(uint64_t a0){return (is_rottable)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_28(int a0){return (inventory_resistance_check)((int)a0);}
void teleport_trap_api_29(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_30(uint64_t a0){return (uint64_t)(uintptr_t)(cxname)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_31(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_32(uint64_t a0){return (erosion_matters)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_33(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_34(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_35(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_36(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
int teleport_trap_api_37(void){return (rng_log_enabled)();}
void teleport_trap_api_38(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_39(int a0){return (rnl)((int)a0);}
int teleport_trap_api_40(int a0){return (rnl)((int)a0);}
uint64_t teleport_trap_api_41(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_42(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_43(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_44(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
void teleport_trap_api_45(void){(update_inventory)();}
uint64_t teleport_trap_api_46(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_47(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_48(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_49(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
void teleport_trap_api_50(uint64_t a0,int a1){(costly_alteration)((struct obj *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_51(void){(update_inventory)();}
uint64_t teleport_trap_api_52(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_53(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_54(uint64_t a0,uint64_t a1){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_55(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_56(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
void teleport_trap_api_57(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
void teleport_trap_api_58(uint64_t a0,int a1){(costly_alteration)((struct obj *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_59(uint64_t a0,int a1){(remove_worn_item)((struct obj *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_60(uint64_t a0,uint64_t a1,int a2,int a3){(extract_from_minvent)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1,(signed char)a2,(signed char)a3);}
uint64_t teleport_trap_api_61(uint64_t a0){return (uint64_t)(uintptr_t)(simpleonames)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_62(uint64_t a0,int a1,int a2,int64_t a3,uint64_t a4){(impossible)((const char *)(uintptr_t)a0,(int)a1,(int)a2,(long)a3,(char *)(uintptr_t)a4);}
void teleport_trap_api_63(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_64(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_65(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_66(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_67(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_68(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_69(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
int teleport_trap_api_70(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_71(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_72(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_73(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_74(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_75(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
uint64_t teleport_trap_api_76(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(Yobjnam2)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_77(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_78(void){return (rng_log_enabled)();}
void teleport_trap_api_79(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_80(int a0){return (rn2)((int)a0);}
int teleport_trap_api_81(int a0){return (rn2)((int)a0);}
void teleport_trap_api_82(uint64_t a0){(pline_The)((const char *)(uintptr_t)a0);}
void teleport_trap_api_83(void){(update_inventory)();}
int teleport_trap_api_84(int a0,int a1){return (rndmonnum_adj)((int)a0,(int)a1);}
int teleport_trap_api_85(int a0){return (sgn)((int)a0);}
int teleport_trap_api_86(int a0){return (sgn)((int)a0);}
uint64_t teleport_trap_api_87(int a0,uint64_t a1,uint64_t a2,int a3,int a4,unsigned a5){return (uint64_t)(uintptr_t)(mkcorpstat)((int)a0,(struct monst *)(uintptr_t)a1,(struct permonst *)(uintptr_t)a2,(short)a3,(short)a4,(unsigned int)a5);}
uint64_t teleport_trap_api_88(uint64_t a0,int a1,int a2,unsigned a3){return (uint64_t)(uintptr_t)(makemon)((struct permonst *)(uintptr_t)a0,(short)a1,(short)a2,(unsigned int)a3);}
void teleport_trap_api_89(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_90(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(add_to_container)((struct obj *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
int teleport_trap_api_91(uint64_t a0){return (weight)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_92(uint64_t a0){(mongone)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_93(uint64_t a0){return (dunlevs_in_dungeon)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_94(uint64_t a0){return (In_quest)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_95(uint64_t a0){return (In_hell)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_96(uint64_t a0){return (dunlev)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_97(void){return (rng_log_enabled)();}
void teleport_trap_api_98(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_99(int a0){return (rn2)((int)a0);}
int teleport_trap_api_100(int a0){return (rn2)((int)a0);}
int teleport_trap_api_101(int a0,int a1){return (is_lava)((short)a0,(short)a1);}
int teleport_trap_api_102(int a0,int a1){return (is_pool_or_lava)((short)a0,(short)a1);}
int teleport_trap_api_103(uint64_t a0){return (single_level_branch)((d_level *)(uintptr_t)a0);}
uint64_t teleport_trap_api_104(unsigned a0){return (uint64_t)(uintptr_t)(alloc)((unsigned int)a0);}
uint64_t teleport_trap_api_105(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(memset)((void *)(uintptr_t)a0,(int)a1,(unsigned long)a2);}
uint64_t teleport_trap_api_106(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(in_rooms)((short)a0,(short)a1,(int)a2);}
void teleport_trap_api_107(int a0,int a1,int64_t a2){(add_damage)((short)a0,(short)a1,(long)a2);}
void teleport_trap_api_108(int a0,int a1,int a2){(obj_ice_effects)((short)a0,(short)a1,(signed char)a2);}
void teleport_trap_api_109(int a0,int a1,int a2){(spot_stop_timers)((short)a0,(short)a1,(short)a2);}
int teleport_trap_api_110(int a0,int a1,int a2){return (set_levltyp)((short)a0,(short)a1,(signed char)a2);}
int teleport_trap_api_111(int a0,int a1,int a2){return (set_levltyp)((short)a0,(short)a1,(signed char)a2);}
int teleport_trap_api_112(int a0,int a1,int a2){return (set_levltyp)((short)a0,(short)a1,(signed char)a2);}
void teleport_trap_api_113(int a0,int a1){(unearth_objs)((int)a0,(int)a1);}
void teleport_trap_api_114(int a0,int a1){(recalc_block_point)((short)a0,(short)a1);}
int teleport_trap_api_115(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_trap_api_116(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
int teleport_trap_api_117(uint64_t a0){return (dunlev)((d_level *)(uintptr_t)a0);}
void teleport_trap_api_118(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_119(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_120(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
void teleport_trap_api_121(uint64_t a0,uint64_t a1){(pline_The)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_122(uint64_t a0){return (Can_fall_thru)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_123(uint64_t a0){return (Can_fall_thru)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_124(void){return (next_to_u)();}
void teleport_trap_api_125(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_126(uint64_t a0,int a1,int a2,int a3){(impact_drop)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(short)a3);}
void teleport_trap_api_127(uint64_t target,int a0,int a1){((void (*)(winid, boolean))(uintptr_t)target)((int)a0,(signed char)a1);}
void teleport_trap_api_128(uint64_t a0){(pline_The)((const char *)(uintptr_t)a0);}
void teleport_trap_api_129(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_130(int a0){(shopdig)((int)a0);}
int teleport_trap_api_131(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_132(uint64_t a0){(find_hell)((d_level *)(uintptr_t)a0);}
void teleport_trap_api_133(uint64_t a0,uint64_t a1){(assign_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_134(uint64_t a0){return (depth)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_135(uint64_t a0){return (depth)((d_level *)(uintptr_t)a0);}
void teleport_trap_api_136(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_137(int a0,int a1){return (uint64_t)(uintptr_t)(ceiling)((short)a0,(short)a1);}
int teleport_trap_api_138(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_139(uint64_t a0,int a1,uint64_t a2,uint64_t a3){(schedule_goto)((d_level *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_140(uint64_t a0,int a1,uint64_t a2){return (cant_revive)((int *)(uintptr_t)a0,(signed char)a1,(struct obj *)(uintptr_t)a2);}
uint64_t teleport_trap_api_141(uint64_t a0,uint64_t a1,int a2){return (uint64_t)(uintptr_t)(montraits)((struct obj *)(uintptr_t)a0,(coord *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_142(uint64_t a0,int a1){(wary_dog)((struct monst *)(uintptr_t)a0,(signed char)a1);}
int teleport_trap_api_143(int a0){return (quest_info)((int)a0);}
uint64_t teleport_trap_api_144(uint64_t a0,int a1,int a2,unsigned a3){return (uint64_t)(uintptr_t)(makemon)((struct permonst *)(uintptr_t)a0,(short)a1,(short)a2,(unsigned int)a3);}
int teleport_trap_api_145(uint64_t a0,uint64_t a1,unsigned a2){return (newcham)((struct monst *)(uintptr_t)a0,(struct permonst *)(uintptr_t)a1,(unsigned int)a2);}
uint64_t teleport_trap_api_146(uint64_t a0,int a1,int a2,unsigned a3){return (uint64_t)(uintptr_t)(makemon)((struct permonst *)(uintptr_t)a0,(short)a1,(short)a2,(unsigned int)a3);}
uint64_t teleport_trap_api_147(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(christen_monst)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_148(uint64_t a0){(seemimic)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_149(uint64_t a0){(set_malign)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_150(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_151(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_152(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(in_rooms)((short)a0,(short)a1,(int)a2);}
uint64_t teleport_trap_api_153(int a0){return (uint64_t)(uintptr_t)(shop_keeper)((char)a0);}
uint64_t teleport_trap_api_154(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(shk_your)((char *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
uint64_t teleport_trap_api_155(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_156(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_157(uint64_t a0){return (uint64_t)(uintptr_t)(upstart)((char *)(uintptr_t)a0);}
void teleport_trap_api_158(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_159(uint64_t a0){return (uint64_t)(uintptr_t)(rndmonnam)((char *)(uintptr_t)a0);}
void teleport_trap_api_160(uint64_t a0,uint64_t a1){(pline_The)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_161(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(shk_your)((char *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
uint64_t teleport_trap_api_162(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_163(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_164(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_165(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_166(int a0,int a1){(set_msg_xy)((short)a0,(short)a1);}
int teleport_trap_api_167(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_168(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_169(uint64_t a0){return (uint64_t)(uintptr_t)(a_monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_170(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_171(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_172(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_173(int a0,int a1){(map_invisible)((short)a0,(short)a1);}
void teleport_trap_api_174(void){(stop_occupation)();}
int teleport_trap_api_175(int a0,int a1){return (costly_spot)((short)a0,(short)a1);}
uint64_t teleport_trap_api_176(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(in_rooms)((short)a0,(short)a1,(int)a2);}
uint64_t teleport_trap_api_177(int a0){return (uint64_t)(uintptr_t)(shop_keeper)((char)a0);}
int64_t teleport_trap_api_178(uint64_t a0,int a1,int a2,int a3,int a4){return (stolen_value)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(signed char)a3,(signed char)a4);}
void teleport_trap_api_179(uint64_t a0,uint64_t a1){(You_feel)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_180(int a0){(adjalign)((int)a0);}
void teleport_trap_api_181(uint64_t a0,uint64_t a1){(You_feel)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_182(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_183(uint64_t a0,uint64_t a1){return (mpickobj)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
void teleport_trap_api_184(uint64_t a0,int a1){(m_dowear)((struct monst *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_185(uint64_t a0,int a1){(remove_worn_item)((struct obj *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_186(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_187(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
uint64_t teleport_trap_api_188(uint64_t a0,int a1,int a2){return (uint64_t)(uintptr_t)(nxtobj)((struct obj *)(uintptr_t)a0,(int)a1,(signed char)a2);}
void teleport_trap_api_189(int a0,int a1){(feel_newsym)((short)a0,(short)a1);}
int teleport_trap_api_190(uint64_t a0,uint64_t a1,uint64_t a2,int a3){return (get_obj_location)((struct obj *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1,(coordxy *)(uintptr_t)a2,(int)a3);}
void teleport_trap_api_191(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_192(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_193(uint64_t a0){(stackobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_194(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_195(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_196(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
void teleport_trap_api_197(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_198(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_199(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_200(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_201(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(mksobj)((int)a0,(signed char)a1,(signed char)a2);}
int teleport_trap_api_202(uint64_t a0){return (weight)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_203(void){(float_vs_flight)();}
void teleport_trap_api_204(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_205(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
int teleport_trap_api_206(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_207(uint64_t a0,int a1){return (defended)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_208(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_209(uint64_t a0,int a1){return (defended)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_210(uint64_t a0){return (resists_magm)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_211(uint64_t a0,int a1){return (defended)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_212(uint64_t a0,int a1){(impossible)((const char *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_213(void){return (rng_log_enabled)();}
void teleport_trap_api_214(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_215(int a0){return (rn2)((int)a0);}
int teleport_trap_api_216(int a0){return (rn2)((int)a0);}
void teleport_trap_api_217(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
void teleport_trap_api_218(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_219(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_220(uint64_t a0,uint64_t a1){return (dmgval)((struct obj *)(uintptr_t)a0,(struct monst *)(uintptr_t)a1);}
int teleport_trap_api_221(void){return (rng_log_enabled)();}
void teleport_trap_api_222(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_223(int a0){return (rn2)((int)a0);}
int teleport_trap_api_224(int a0){return (rn2)((int)a0);}
int teleport_trap_api_225(int a0,int a1,uint64_t a2,uint64_t a3){return (thitu)((int)a0,(int)a1,(struct obj **)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_226(uint64_t a0,uint64_t a1){(obfree)((struct obj *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
void teleport_trap_api_227(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_228(uint64_t a0){(observe_object)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_229(uint64_t a0){(stackobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_230(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_231(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_232(void){return (rng_log_enabled)();}
void teleport_trap_api_233(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_234(int a0){return (rn2)((int)a0);}
int teleport_trap_api_235(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_236(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_237(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_238(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_239(void){return (rng_log_enabled)();}
void teleport_trap_api_240(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_241(int a0){return (rn2)((int)a0);}
int teleport_trap_api_242(int a0){return (rn2)((int)a0);}
void teleport_trap_api_243(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
void teleport_trap_api_244(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_245(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_246(void){return (rng_log_enabled)();}
void teleport_trap_api_247(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_248(int a0){return (rn2)((int)a0);}
int teleport_trap_api_249(int a0){return (rn2)((int)a0);}
int teleport_trap_api_250(uint64_t a0,uint64_t a1){return (dmgval)((struct obj *)(uintptr_t)a0,(struct monst *)(uintptr_t)a1);}
int teleport_trap_api_251(void){return (rng_log_enabled)();}
void teleport_trap_api_252(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_253(int a0){return (rn2)((int)a0);}
int teleport_trap_api_254(int a0){return (rn2)((int)a0);}
int teleport_trap_api_255(int a0,int a1,uint64_t a2,uint64_t a3){return (thitu)((int)a0,(int)a1,(struct obj **)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_256(uint64_t a0,int a1,uint64_t a2,int a3,int a4){(poisoned)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
void teleport_trap_api_257(uint64_t a0,uint64_t a1){(obfree)((struct obj *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
void teleport_trap_api_258(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_259(uint64_t a0){(observe_object)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_260(uint64_t a0){(stackobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_261(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_262(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_263(void){return (rng_log_enabled)();}
void teleport_trap_api_264(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_265(int a0){return (rn2)((int)a0);}
int teleport_trap_api_266(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_267(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_268(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_269(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_270(void){return (rng_log_enabled)();}
void teleport_trap_api_271(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_272(int a0){return (rn2)((int)a0);}
int teleport_trap_api_273(int a0){return (rn2)((int)a0);}
int teleport_trap_api_274(void){return (rng_log_enabled)();}
void teleport_trap_api_275(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_276(int a0){return (rn2)((int)a0);}
int teleport_trap_api_277(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_278(int a0,int a1){return (uint64_t)(uintptr_t)(ceiling)((short)a0,(short)a1);}
uint64_t teleport_trap_api_279(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_280(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_281(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_282(void){return (rng_log_enabled)();}
void teleport_trap_api_283(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_284(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_285(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_286(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
uint64_t teleport_trap_api_287(int a0,int a1){return (uint64_t)(uintptr_t)(ceiling)((short)a0,(short)a1);}
uint64_t teleport_trap_api_288(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_289(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_290(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_291(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_292(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_293(uint64_t a0){return (uint64_t)(uintptr_t)(helm_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_294(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
void teleport_trap_api_295(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_296(uint64_t a0){return (hard_helmet)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_297(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_298(uint64_t a0){return (uint64_t)(uintptr_t)(Yname2)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_299(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_300(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_301(uint64_t a0){(observe_object)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_302(uint64_t a0){(stackobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_303(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_304(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_305(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
int teleport_trap_api_306(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_307(void){return (rng_log_enabled)();}
void teleport_trap_api_308(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_309(int a0){return (rn2)((int)a0);}
int teleport_trap_api_310(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_311(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_312(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_313(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_314(void){return (rng_log_enabled)();}
void teleport_trap_api_315(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_316(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_317(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_318(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_319(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_320(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
void teleport_trap_api_321(int a0){(wake_nearby)((signed char)a0);}
int teleport_trap_api_322(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_323(uint64_t a0){return (m_in_air)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_324(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_325(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_326(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_327(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_328(int a0,int a1,int a2,int a3){return (dist2)((short)a0,(short)a1,(short)a2,(short)a3);}
void teleport_trap_api_329(uint64_t a0,uint64_t a1,uint64_t a2){(You_hear)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_330(int a0,int a1,int a2){(wake_nearto)((short)a0,(short)a1,(int)a2);}
int teleport_trap_api_331(void){return (rng_log_enabled)();}
void teleport_trap_api_332(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_333(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_334(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_335(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_336(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_337(void){return (rng_log_enabled)();}
void teleport_trap_api_338(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_339(int a0){return (rn2)((int)a0);}
int teleport_trap_api_340(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_341(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_342(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_343(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(mbodypart)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_344(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_345(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_346(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_347(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_348(uint64_t a0){return (uint64_t)(uintptr_t)(Yname2)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_349(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_350(void){return (rng_log_enabled)();}
void teleport_trap_api_351(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_352(int a0){return (rn2)((int)a0);}
int teleport_trap_api_353(int a0){return (rn2)((int)a0);}
int teleport_trap_api_354(void){return (rng_log_enabled)();}
void teleport_trap_api_355(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_356(int a0){return (rn2)((int)a0);}
int teleport_trap_api_357(int a0){return (rn2)((int)a0);}
void teleport_trap_api_358(int64_t a0,int a1){(set_wounded_legs)((long)a0,(int)a1);}
void teleport_trap_api_359(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_360(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
int teleport_trap_api_361(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_362(uint64_t a0){return (m_in_air)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_363(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_364(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_365(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_366(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_367(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_368(void){return (rng_log_enabled)();}
void teleport_trap_api_369(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_370(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_371(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_372(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_373(uint64_t a0){(monstseesu)((unsigned long)a0);}
void teleport_trap_api_374(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_375(void){return (rng_log_enabled)();}
void teleport_trap_api_376(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_377(int a0){return (rnd)((int)a0);}
int teleport_trap_api_378(int a0){return (rnd)((int)a0);}
void teleport_trap_api_379(int a0,int a1){(fall_asleep)((int)a0,(signed char)a1);}
void teleport_trap_api_380(uint64_t a0){(monstunseesu)((unsigned long)a0);}
int teleport_trap_api_381(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_382(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_383(void){return (rng_log_enabled)();}
void teleport_trap_api_384(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_385(int a0){return (rnd)((int)a0);}
int teleport_trap_api_386(int a0){return (rnd)((int)a0);}
int teleport_trap_api_387(uint64_t a0,int a1,int a2){return (sleep_monst)((struct monst *)(uintptr_t)a0,(int)a1,(int)a2);}
uint64_t teleport_trap_api_388(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_389(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_390(void){return (rng_log_enabled)();}
void teleport_trap_api_391(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_392(int a0){return (rn2)((int)a0);}
int teleport_trap_api_393(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_394(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_395(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_396(uint64_t a0){return (uint64_t)(uintptr_t)(helm_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_397(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_398(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_399(uint64_t a0){return (uint64_t)(uintptr_t)(gloves_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_400(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_401(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_402(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_403(uint64_t a0){return (splash_lit)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_404(uint64_t a0){return (uint64_t)(uintptr_t)(cloak_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_405(uint64_t a0){return (uint64_t)(uintptr_t)(suit_simple_name)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_406(void){(update_inventory)();}
void teleport_trap_api_407(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_408(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
int teleport_trap_api_409(void){return (rng_log_enabled)();}
void teleport_trap_api_410(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_411(int a0){return (rn2)((int)a0);}
int teleport_trap_api_412(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_413(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(split_mon)((struct monst *)(uintptr_t)a0,(struct monst *)(uintptr_t)a1);}
int teleport_trap_api_414(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_415(void){return (rng_log_enabled)();}
void teleport_trap_api_416(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_417(int a0){return (rn2)((int)a0);}
int teleport_trap_api_418(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_419(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_420(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(mbodypart)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_421(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
uint64_t teleport_trap_api_422(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_423(uint64_t a0){return (uint64_t)(uintptr_t)(helm_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_424(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_425(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(mbodypart)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_426(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
uint64_t teleport_trap_api_427(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_428(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_429(uint64_t a0){return (uint64_t)(uintptr_t)(gloves_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_430(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_431(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(mbodypart)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_432(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
uint64_t teleport_trap_api_433(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_434(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_435(uint64_t a0){return (splash_lit)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_436(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_437(uint64_t a0){return (uint64_t)(uintptr_t)(cloak_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_438(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_439(uint64_t a0){return (uint64_t)(uintptr_t)(suit_simple_name)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_440(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_441(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_442(uint64_t a0){return (uint64_t)(uintptr_t)(mlifesaver)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_443(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
void teleport_trap_api_444(uint64_t a0,uint64_t a1,int a2){(monkilled)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_445(void){return (rng_log_enabled)();}
void teleport_trap_api_446(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_447(int a0){return (rn2)((int)a0);}
int teleport_trap_api_448(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_449(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(split_mon)((struct monst *)(uintptr_t)a0,(struct monst *)(uintptr_t)a1);}
int teleport_trap_api_450(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_451(void){return (rng_log_enabled)();}
void teleport_trap_api_452(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_453(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_454(int a0,int a1){return (d)((int)a0,(int)a1);}
uint64_t teleport_trap_api_455(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
uint64_t teleport_trap_api_456(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_457(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3,(char *)(uintptr_t)a4);}
void teleport_trap_api_458(int a0,int a1){(set_msg_xy)((short)a0,(short)a1);}
uint64_t teleport_trap_api_459(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
void teleport_trap_api_460(uint64_t a0,uint64_t a1,uint64_t a2){(You_see)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_461(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_462(int a0,int a1){(shieldeff)((short)a0,(short)a1);}
uint64_t teleport_trap_api_463(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_464(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_465(void){return (rng_log_enabled)();}
void teleport_trap_api_466(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_467(int a0){return (rn2)((int)a0);}
int teleport_trap_api_468(int a0){return (rn2)((int)a0);}
int teleport_trap_api_469(void){return (rng_log_enabled)();}
void teleport_trap_api_470(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_471(int a0){return (rn2)((int)a0);}
int teleport_trap_api_472(int a0){return (rn2)((int)a0);}
int teleport_trap_api_473(uint64_t a0,int a1,int a2){return (destroy_items)((struct monst *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_trap_api_474(uint64_t a0,uint64_t a1,int a2){(monkilled)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_475(int a0,int a1,int a2,int a3){return (burn_floor_objects)((short)a0,(short)a1,(signed char)a2,(signed char)a3);}
int teleport_trap_api_476(int a0,int a1,int a2,int a3){return (dist2)((short)a0,(short)a1,(short)a2,(short)a3);}
void teleport_trap_api_477(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_478(int a0,int a1){return (is_ice)((short)a0,(short)a1);}
void teleport_trap_api_479(int a0,int a1,uint64_t a2){(melt_ice)((short)a0,(short)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_480(uint64_t a0,uint64_t a1,uint64_t a2){(You_see)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_481(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_482(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_483(uint64_t a0,int a1,uint64_t a2,int a3,int a4){return (uint64_t)(uintptr_t)(x_monnam)((struct monst *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
int teleport_trap_api_484(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_485(uint64_t a0,int a1,uint64_t a2,int a3,int a4){return (uint64_t)(uintptr_t)(x_monnam)((struct monst *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
int teleport_trap_api_486(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_487(uint64_t a0){return (uint64_t)(uintptr_t)(u_locomotion)((const char *)(uintptr_t)a0);}
void teleport_trap_api_488(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_489(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_490(void){return (rng_log_enabled)();}
void teleport_trap_api_491(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_492(int a0){return (rn2)((int)a0);}
int teleport_trap_api_493(int a0){return (rn2)((int)a0);}
void teleport_trap_api_494(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_495(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_496(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_497(uint64_t a0){return (In_quest)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_498(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_499(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_500(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_501(uint64_t a0){return (uint64_t)(uintptr_t)(Yname2)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_502(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_503(uint64_t a0,int a1,uint64_t a2,int a3,int a4){return (uint64_t)(uintptr_t)(x_monnam)((struct monst *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
uint64_t teleport_trap_api_504(uint64_t a0){return (uint64_t)(uintptr_t)(upstart)((char *)(uintptr_t)a0);}
void teleport_trap_api_505(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_506(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_507(void){return (rng_log_enabled)();}
void teleport_trap_api_508(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_509(int a0){return (rn2)((int)a0);}
int teleport_trap_api_510(int a0){return (rn2)((int)a0);}
int teleport_trap_api_511(void){return (rng_log_enabled)();}
void teleport_trap_api_512(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_513(int a0){return (rnd)((int)a0);}
int teleport_trap_api_514(int a0){return (rnd)((int)a0);}
int teleport_trap_api_515(void){return (rng_log_enabled)();}
void teleport_trap_api_516(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_517(int a0){return (rnd)((int)a0);}
int teleport_trap_api_518(int a0){return (rnd)((int)a0);}
void teleport_trap_api_519(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
int teleport_trap_api_520(void){return (rng_log_enabled)();}
void teleport_trap_api_521(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_522(int a0){return (rn2)((int)a0);}
int teleport_trap_api_523(int a0){return (rn2)((int)a0);}
void teleport_trap_api_524(uint64_t a0,int a1,uint64_t a2,int a3,int a4){(poisoned)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
int teleport_trap_api_525(void){return (rng_log_enabled)();}
void teleport_trap_api_526(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_527(int a0){return (rnd)((int)a0);}
int teleport_trap_api_528(int a0){return (rnd)((int)a0);}
int teleport_trap_api_529(void){return (rng_log_enabled)();}
void teleport_trap_api_530(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_531(int a0){return (rnd)((int)a0);}
int teleport_trap_api_532(int a0){return (rnd)((int)a0);}
void teleport_trap_api_533(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_534(void){(unplacebc)();}
void teleport_trap_api_535(void){(ballfall)();}
void teleport_trap_api_536(void){(placebc)();}
void teleport_trap_api_537(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
void teleport_trap_api_538(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
int teleport_trap_api_539(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_540(uint64_t a0){return (has_ceiling)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_541(uint64_t a0){return (count_wsegs)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_542(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_543(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_544(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_545(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
void teleport_trap_api_546(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_547(void){return (rng_log_enabled)();}
void teleport_trap_api_548(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_549(int a0){return (rnd)((int)a0);}
int teleport_trap_api_550(int a0){return (rnd)((int)a0);}
int teleport_trap_api_551(uint64_t a0){return (Can_fall_thru)((d_level *)(uintptr_t)a0);}
void teleport_trap_api_552(uint64_t a0,uint64_t a1){(impossible)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_553(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_554(uint64_t a0){return (Can_fall_thru)((d_level *)(uintptr_t)a0);}
void teleport_trap_api_555(uint64_t a0,uint64_t a1){(impossible)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_556(uint64_t a0){return (has_ceiling)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_557(uint64_t a0){return (count_wsegs)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_558(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_559(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_560(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_561(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_562(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_563(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_564(uint64_t a0){(tele_trap)((struct trap *)(uintptr_t)a0);}
int teleport_trap_api_565(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_566(uint64_t a0,uint64_t a1,int a2){(mtele_trap)((struct monst *)(uintptr_t)a0,(struct trap *)(uintptr_t)a1,(int)a2);}
void teleport_trap_api_567(uint64_t a0,unsigned a1){(level_tele_trap)((struct trap *)(uintptr_t)a0,(unsigned int)a1);}
int teleport_trap_api_568(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_569(uint64_t a0,uint64_t a1,int a2,int a3){return (mlevel_tele_trap)((struct monst *)(uintptr_t)a0,(struct trap *)(uintptr_t)a1,(signed char)a2,(int)a3);}
void teleport_trap_api_570(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_571(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_572(uint64_t a0,int a1,uint64_t a2,int a3,int a4){return (uint64_t)(uintptr_t)(x_monnam)((struct monst *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
int teleport_trap_api_573(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_574(uint64_t a0){return (uint64_t)(uintptr_t)(u_locomotion)((const char *)(uintptr_t)a0);}
int teleport_trap_api_575(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_576(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_577(int a0){return (acurr)((int)a0);}
int teleport_trap_api_578(void){return (rng_log_enabled)();}
void teleport_trap_api_579(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_580(int a0){return (rn2)((int)a0);}
int teleport_trap_api_581(int a0){return (rn2)((int)a0);}
int teleport_trap_api_582(void){return (rng_log_enabled)();}
void teleport_trap_api_583(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_584(int a0){return (rn2)((int)a0);}
int teleport_trap_api_585(int a0){return (rn2)((int)a0);}
int teleport_trap_api_586(void){return (rng_log_enabled)();}
void teleport_trap_api_587(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_588(int a0){return (rn2)((int)a0);}
int teleport_trap_api_589(int a0){return (rn2)((int)a0);}
int teleport_trap_api_590(void){return (rng_log_enabled)();}
void teleport_trap_api_591(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_592(int a0){return (rn2)((int)a0);}
int teleport_trap_api_593(int a0){return (rn2)((int)a0);}
int teleport_trap_api_594(void){return (rng_log_enabled)();}
void teleport_trap_api_595(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_596(int a0){return (rn2)((int)a0);}
int teleport_trap_api_597(int a0){return (rn2)((int)a0);}
int teleport_trap_api_598(void){return (rng_log_enabled)();}
void teleport_trap_api_599(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_600(int a0){return (rnd)((int)a0);}
int teleport_trap_api_601(int a0){return (rnd)((int)a0);}
void teleport_trap_api_602(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_603(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_604(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_605(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
int teleport_trap_api_606(uint64_t a0){return (count_wsegs)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_607(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_608(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_609(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_610(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_611(int a0,int a1){(newsym)((short)a0,(short)a1);}
uint64_t teleport_trap_api_612(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_613(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_614(void){return (rng_log_enabled)();}
void teleport_trap_api_615(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_616(int a0){return (rn2)((int)a0);}
int teleport_trap_api_617(int a0){return (rn2)((int)a0);}
void teleport_trap_api_618(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_619(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_620(void){return (rng_log_enabled)();}
void teleport_trap_api_621(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_622(int a0){return (rnd)((int)a0);}
int teleport_trap_api_623(int a0){return (rnd)((int)a0);}
void teleport_trap_api_624(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_625(uint64_t a0){(Your)((const char *)(uintptr_t)a0);}
int teleport_trap_api_626(void){return (rng_log_enabled)();}
void teleport_trap_api_627(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_628(int a0){return (rn2)((int)a0);}
int teleport_trap_api_629(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_630(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
uint64_t teleport_trap_api_631(uint64_t a0){return (uint64_t)(uintptr_t)(yname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_632(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_633(uint64_t a0,int a1){(costly_alteration)((struct obj *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_634(void){(update_inventory)();}
int teleport_trap_api_635(void){return (rng_log_enabled)();}
void teleport_trap_api_636(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_637(int a0){return (rnd)((int)a0);}
int teleport_trap_api_638(int a0){return (rnd)((int)a0);}
int teleport_trap_api_639(void){return (rng_log_enabled)();}
void teleport_trap_api_640(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_641(int a0){return (rnd)((int)a0);}
int teleport_trap_api_642(int a0){return (rnd)((int)a0);}
int teleport_trap_api_643(uint64_t a0,int a1){return (is_art)((struct obj *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_644(void){return (rng_log_enabled)();}
void teleport_trap_api_645(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_646(int a0){return (rnd)((int)a0);}
int teleport_trap_api_647(int a0){return (rnd)((int)a0);}
int teleport_trap_api_648(uint64_t a0){return (is_quest_artifact)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_649(int a0,uint64_t a1){return (defends_when_carried)((int)a0,(struct obj *)(uintptr_t)a1);}
int teleport_trap_api_650(void){return (rng_log_enabled)();}
void teleport_trap_api_651(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_652(int a0){return (rnd)((int)a0);}
int teleport_trap_api_653(int a0){return (rnd)((int)a0);}
void teleport_trap_api_654(uint64_t a0){(You_feel)((const char *)(uintptr_t)a0);}
void teleport_trap_api_655(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
int teleport_trap_api_656(void){return (rng_log_enabled)();}
void teleport_trap_api_657(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_658(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_659(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_660(void){return (rng_log_enabled)();}
void teleport_trap_api_661(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_662(int a0){return (rnd)((int)a0);}
int teleport_trap_api_663(int a0){return (rnd)((int)a0);}
int teleport_trap_api_664(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_665(uint64_t a0){return (resists_magm)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_666(uint64_t a0,int a1){return (attacktype)((struct permonst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_667(uint64_t a0,int a1){return (attacktype)((struct permonst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_668(void){return (rng_log_enabled)();}
void teleport_trap_api_669(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_670(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_671(int a0,int a1){return (d)((int)a0,(int)a1);}
uint64_t teleport_trap_api_672(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_673(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_674(void){return (rng_log_enabled)();}
void teleport_trap_api_675(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_676(int a0){return (rnd)((int)a0);}
int teleport_trap_api_677(int a0){return (rnd)((int)a0);}
int teleport_trap_api_678(uint64_t a0,int a1){return (is_art)((struct obj *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_679(void){return (rng_log_enabled)();}
void teleport_trap_api_680(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_681(int a0){return (rnd)((int)a0);}
int teleport_trap_api_682(int a0){return (rnd)((int)a0);}
int teleport_trap_api_683(int a0,uint64_t a1){return (defends_when_carried)((int)a0,(struct obj *)(uintptr_t)a1);}
int teleport_trap_api_684(void){return (rng_log_enabled)();}
void teleport_trap_api_685(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_686(int a0){return (rnd)((int)a0);}
int teleport_trap_api_687(int a0){return (rnd)((int)a0);}
void teleport_trap_api_688(uint64_t a0,uint64_t a1,int a2){(monkilled)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
void teleport_trap_api_689(int a0,int a1){(newsym)((short)a0,(short)a1);}
uint64_t teleport_trap_api_690(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_691(uint64_t a0,int a1,uint64_t a2,int a3,int a4){return (uint64_t)(uintptr_t)(x_monnam)((struct monst *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
int teleport_trap_api_692(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_693(uint64_t a0){return (uint64_t)(uintptr_t)(u_locomotion)((const char *)(uintptr_t)a0);}
int teleport_trap_api_694(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_695(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_696(uint64_t a0){return (uint64_t)(uintptr_t)(Yname2)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_697(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_698(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(poly_obj)((struct obj *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_699(void){(update_inventory)();}
void teleport_trap_api_700(uint64_t a0,uint64_t a1,int64_t a2){(prinv)((const char *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1,(long)a2);}
void teleport_trap_api_701(int a0,int a1){(shieldeff)((short)a0,(short)a1);}
void teleport_trap_api_702(uint64_t a0){(You_feel)((const char *)(uintptr_t)a0);}
void teleport_trap_api_703(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_704(uint64_t a0){(You_feel)((const char *)(uintptr_t)a0);}
void teleport_trap_api_705(int a0){(polyself)((int)a0);}
int teleport_trap_api_706(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_707(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
void teleport_trap_api_708(uint64_t a0,uint64_t a1,int a2,int a3){(extract_from_minvent)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1,(signed char)a2,(signed char)a3);}
int teleport_trap_api_709(uint64_t a0,uint64_t a1){return (mpickobj)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
void teleport_trap_api_710(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_711(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(poly_obj)((struct obj *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_712(uint64_t a0,uint64_t a1,int a2,int a3){(update_mon_extrinsics)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1,(signed char)a2,(signed char)a3);}
int teleport_trap_api_713(uint64_t a0){return (resists_magm)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_714(uint64_t a0){(shieldeff_mon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_715(uint64_t a0,int a1,int a2,int a3){return (resist)((struct monst *)(uintptr_t)a0,(char)a1,(int)a2,(int)a3);}
int teleport_trap_api_716(uint64_t a0,uint64_t a1,unsigned a2){return (newcham)((struct monst *)(uintptr_t)a0,(struct permonst *)(uintptr_t)a1,(unsigned int)a2);}
int teleport_trap_api_717(void){return (rng_log_enabled)();}
void teleport_trap_api_718(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_719(int a0){return (rnd)((int)a0);}
int teleport_trap_api_720(int a0){return (rnd)((int)a0);}
int teleport_trap_api_721(void){return (rng_log_enabled)();}
void teleport_trap_api_722(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_723(int a0){return (rn2)((int)a0);}
int teleport_trap_api_724(int a0){return (rn2)((int)a0);}
void teleport_trap_api_725(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_726(void){return (rng_log_enabled)();}
void teleport_trap_api_727(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_728(int a0){return (rn2)((int)a0);}
int teleport_trap_api_729(int a0){return (rn2)((int)a0);}
void teleport_trap_api_730(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
void teleport_trap_api_731(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_732(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
int teleport_trap_api_733(void){return (rng_log_enabled)();}
void teleport_trap_api_734(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_735(int a0){return (rn2)((int)a0);}
int teleport_trap_api_736(int a0){return (rn2)((int)a0);}
void teleport_trap_api_737(int64_t a0,int a1){(set_wounded_legs)((long)a0,(int)a1);}
int teleport_trap_api_738(void){return (rng_log_enabled)();}
void teleport_trap_api_739(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_740(int a0){return (rn2)((int)a0);}
int teleport_trap_api_741(int a0){return (rn2)((int)a0);}
void teleport_trap_api_742(int64_t a0,int a1){(set_wounded_legs)((long)a0,(int)a1);}
void teleport_trap_api_743(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
void teleport_trap_api_744(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_745(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_746(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_747(void){return (rng_log_enabled)();}
void teleport_trap_api_748(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_749(int a0){return (rn2)((int)a0);}
int teleport_trap_api_750(int a0){return (rn2)((int)a0);}
int teleport_trap_api_751(uint64_t a0){return (m_in_air)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_752(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_753(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_754(void){return (rng_log_enabled)();}
void teleport_trap_api_755(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_756(int a0){return (rn2)((int)a0);}
int teleport_trap_api_757(int a0){return (rn2)((int)a0);}
void teleport_trap_api_758(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_759(uint64_t a0,uint64_t a1){(pline_The)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_760(int a0,int a1){(newsym)((short)a0,(short)a1);}
uint64_t teleport_trap_api_761(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_762(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
void teleport_trap_api_763(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_764(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_765(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_766(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_767(uint64_t a0){return (m_in_air)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_768(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_769(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_770(int a0,int a1){(newsym)((short)a0,(short)a1);}
uint64_t teleport_trap_api_771(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_772(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
void teleport_trap_api_773(uint64_t a0){(domagicportal)((struct trap *)(uintptr_t)a0);}
int teleport_trap_api_774(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_775(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_776(uint64_t a0){return (m_in_air)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_777(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_778(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_779(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_780(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_781(uint64_t a0){return (uint64_t)(uintptr_t)(eos)((char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_782(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(mbodypart)((struct monst *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_trap_api_783(uint64_t a0){return (uint64_t)(uintptr_t)(makeplural)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_784(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_785(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t)(strsubst)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_786(uint64_t a0,uint64_t a1){(You_see)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_787(int a0,int a1,int a2,int a3){return (dist2)((short)a0,(short)a1,(short)a2,(short)a3);}
void teleport_trap_api_788(uint64_t a0,uint64_t a1){(You_see)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_789(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
int teleport_trap_api_790(uint64_t a0){return (has_ceiling)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_791(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_792(uint64_t a0){return (mon_has_amulet)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_793(uint64_t a0){return (resists_magm)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_794(uint64_t a0){return (resists_magm)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_795(uint64_t a0,int a1){return (attacktype)((struct permonst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_796(uint64_t a0,int a1){return (attacktype)((struct permonst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_797(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_798(uint64_t a0){return (is_flammable)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_799(uint64_t a0,unsigned a1){(impossible)((const char *)(uintptr_t)a0,(unsigned int)a1);}
void teleport_trap_api_800(uint64_t a0,uint64_t a1,int a2){(impossible)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(int)a2);}
void teleport_trap_api_801(int a0){(nomul)((int)a0);}
int teleport_trap_api_802(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_trap_api_803(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_804(uint64_t a0){return (uint64_t)(uintptr_t)(u_locomotion)((const char *)(uintptr_t)a0);}
void teleport_trap_api_805(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_806(void){return (rng_log_enabled)();}
void teleport_trap_api_807(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_808(int a0){return (rn2)((int)a0);}
int teleport_trap_api_809(int a0){return (rn2)((int)a0);}
void teleport_trap_api_810(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_811(uint64_t a0,int a1){(mon_learns_traps)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_812(uint64_t a0){(mons_see_trap)((struct trap *)(uintptr_t)a0);}
uint64_t teleport_trap_api_813(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(just_an)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_814(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_815(void){return (rng_log_enabled)();}
void teleport_trap_api_816(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_817(int a0){return (rn2)((int)a0);}
int teleport_trap_api_818(int a0){return (rn2)((int)a0);}
int teleport_trap_api_819(void){return (rng_log_enabled)();}
void teleport_trap_api_820(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_821(int a0){return (rn2)((int)a0);}
int teleport_trap_api_822(int a0){return (rn2)((int)a0);}
void teleport_trap_api_823(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
void teleport_trap_api_824(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
int teleport_trap_api_825(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_826(void){return (rng_log_enabled)();}
void teleport_trap_api_827(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_828(int a0){return (rnd)((int)a0);}
int teleport_trap_api_829(int a0){return (rnd)((int)a0);}
int teleport_trap_api_830(uint64_t a0,int a1,int a2){return (sleep_monst)((struct monst *)(uintptr_t)a0,(int)a1,(int)a2);}
uint64_t teleport_trap_api_831(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_832(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_833(void){return (rng_log_enabled)();}
void teleport_trap_api_834(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_835(int a0){return (rnd)((int)a0);}
int teleport_trap_api_836(int a0){return (rnd)((int)a0);}
int teleport_trap_api_837(void){return (rng_log_enabled)();}
void teleport_trap_api_838(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_839(int a0){return (rnd)((int)a0);}
int teleport_trap_api_840(int a0){return (rnd)((int)a0);}
int teleport_trap_api_841(uint64_t a0){return (resists_magm)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_842(uint64_t a0,int a1,int a2,int a3){return (resist)((struct monst *)(uintptr_t)a0,(char)a1,(int)a2,(int)a3);}
int teleport_trap_api_843(uint64_t a0,uint64_t a1,unsigned a2){return (newcham)((struct monst *)(uintptr_t)a0,(struct permonst *)(uintptr_t)a1,(unsigned int)a2);}
void teleport_trap_api_844(int a0){(dismount_steed)((int)a0);}
int64_t teleport_trap_api_845(int a0,int a1,int a2,unsigned a3,uint64_t a4){return (scatter)((short)a0,(short)a1,(int)a2,(unsigned int)a3,(struct obj *)(uintptr_t)a4);}
void teleport_trap_api_846(int a0,int a1){(del_engr_at)((short)a0,(short)a1);}
void teleport_trap_api_847(int a0,int a1,int a2){(wake_nearto)((short)a0,(short)a1,(int)a2);}
int teleport_trap_api_848(int a0,int a1){return (is_drawbridge_wall)((short)a0,(short)a1);}
int teleport_trap_api_849(uint64_t a0,uint64_t a1){return (find_drawbridge)((coordxy *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1);}
void teleport_trap_api_850(int a0,int a1){(destroy_drawbridge)((short)a0,(short)a1);}
int teleport_trap_api_851(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_852(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_853(int a0,int a1,int a2){return (fillholetyp)((short)a0,(short)a1,(signed char)a2);}
void teleport_trap_api_854(int a0,int a1,int a2,uint64_t a3,uint64_t a4){(liquid_flow)((short)a0,(short)a1,(signed char)a2,(struct trap *)(uintptr_t)a3,(const char *)(uintptr_t)a4);}
void teleport_trap_api_855(int a0,int a1){(maybe_dunk_boulders)((short)a0,(short)a1);}
void teleport_trap_api_856(int a0,int a1){(recalc_block_point)((short)a0,(short)a1);}
void teleport_trap_api_857(int a0,int a1,int a2){(spot_checks)((short)a0,(short)a1,(signed char)a2);}
void teleport_trap_api_858(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
uint64_t teleport_trap_api_859(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
uint64_t teleport_trap_api_860(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
void teleport_trap_api_861(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_862(int a0,int a1){(maybe_unhide_at)((short)a0,(short)a1);}
uint64_t teleport_trap_api_863(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(splitobj)((struct obj *)(uintptr_t)a0,(long)a1);}
void teleport_trap_api_864(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_865(int a0,int a1){(newsym)((short)a0,(short)a1);}
uint64_t teleport_trap_api_866(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(memset)((void *)(uintptr_t)a0,(int)a1,(unsigned long)a2);}
int teleport_trap_api_867(int a0,int a1,int a2,int a3){return (distmin)((short)a0,(short)a1,(short)a2,(short)a3);}
int teleport_trap_api_868(int a0){return (sgn)((int)a0);}
int teleport_trap_api_869(int a0){return (sgn)((int)a0);}
uint64_t teleport_trap_api_870(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_871(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
void teleport_trap_api_872(uint64_t a0,uint64_t a1){(You_see)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_873(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
int teleport_trap_api_874(int a0,int a1,int a2,int a3){return (dist2)((short)a0,(short)a1,(short)a2,(short)a3);}
void teleport_trap_api_875(uint64_t a0,uint64_t a1){(You_hear)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_876(void){(curs_on_u)();}
int teleport_trap_api_877(uint64_t target,int a0){return ((int (*)(int))(uintptr_t)target)((int)a0);}
int teleport_trap_api_878(int a0){return (rn2_on_display_rng)((int)a0);}
int teleport_trap_api_879(uint64_t target,int a0){return ((int (*)(int))(uintptr_t)target)((int)a0);}
int teleport_trap_api_880(uint64_t target,int a0){return ((int (*)(int))(uintptr_t)target)((int)a0);}
void teleport_trap_api_881(int a0,int a1){(tmp_at)((short)a0,(short)a1);}
void teleport_trap_api_882(int a0,int a1){(tmp_at)((short)a0,(short)a1);}
void teleport_trap_api_883(int a0,int a1){(tmp_at)((short)a0,(short)a1);}
void teleport_trap_api_884(uint64_t target){((void (*)(void))(uintptr_t)target)();}
int teleport_trap_api_885(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_886(void){return (rng_log_enabled)();}
void teleport_trap_api_887(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_888(int a0){return (rn2)((int)a0);}
int teleport_trap_api_889(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_890(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_891(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_892(uint64_t a0,uint64_t a1){return (mpickobj)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1);}
int teleport_trap_api_893(uint64_t a0,uint64_t a1,int a2,int a3){return (ohitmon)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1,(int)a2,(signed char)a3);}
int teleport_trap_api_894(uint64_t a0,uint64_t a1){return (dmgval)((struct obj *)(uintptr_t)a0,(struct monst *)(uintptr_t)a1);}
void teleport_trap_api_895(int a0){(nomul)((int)a0);}
int teleport_trap_api_896(int a0,int a1,uint64_t a2,uint64_t a3){return (thitu)((int)a0,(int)a1,(struct obj **)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_897(void){(stop_occupation)();}
int teleport_trap_api_898(int a0,int a1){return (down_gate)((short)a0,(short)a1);}
int teleport_trap_api_899(uint64_t a0,int a1,int a2,int a3){return (ship_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(signed char)a3);}
int teleport_trap_api_900(void){return (rng_log_enabled)();}
void teleport_trap_api_901(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_902(int a0){return (rn2)((int)a0);}
int teleport_trap_api_903(int a0){return (rn2)((int)a0);}
void teleport_trap_api_904(int a0,int a1){(set_msg_xy)((short)a0,(short)a1);}
void teleport_trap_api_905(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_906(int a0,int a1){(del_engr_at)((short)a0,(short)a1);}
void teleport_trap_api_907(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_908(uint64_t a0){(fracture_rock)((struct obj *)(uintptr_t)a0);}
int64_t teleport_trap_api_909(int a0,int a1,int a2,unsigned a3,uint64_t a4){return (scatter)((short)a0,(short)a1,(int)a2,(unsigned int)a3,(struct obj *)(uintptr_t)a4);}
void teleport_trap_api_910(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_911(void){return (random_teleport_level)();}
int teleport_trap_api_912(uint64_t a0){return (depth)((d_level *)(uintptr_t)a0);}
void teleport_trap_api_913(int a0,int a1,uint64_t a2){(pline_xy)((short)a0,(short)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_914(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
int teleport_trap_api_915(uint64_t a0){return (rloco)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_916(uint64_t a0){(add_to_migration)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_917(uint64_t a0,int a1){(get_level)((d_level *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_918(uint64_t a0,int a1,int a2,uint64_t a3){return (flooreffects)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_919(uint64_t a0,int a1,int a2,uint64_t a3){return (flooreffects)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_920(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
int teleport_trap_api_921(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_trap_api_922(uint64_t a0,uint64_t a1){(You_hear)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_923(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_924(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_925(int a0,int a1,int a2){(wake_nearto)((short)a0,(short)a1,(int)a2);}
int teleport_trap_api_926(int a0,int a1){return (closed_door)((short)a0,(short)a1);}
void teleport_trap_api_927(int a0,int a1){(set_msg_xy)((short)a0,(short)a1);}
void teleport_trap_api_928(uint64_t a0){(pline_The)((const char *)(uintptr_t)a0);}
void teleport_trap_api_929(int a0,int a1){(recalc_block_point)((short)a0,(short)a1);}
int teleport_trap_api_930(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_931(void){return (rng_log_enabled)();}
void teleport_trap_api_932(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_933(int a0){return (rn2)((int)a0);}
int teleport_trap_api_934(int a0){return (rn2)((int)a0);}
int teleport_trap_api_935(uint64_t a0,int a1,int a2,int a3,int a4,int a5,int a6){return (hits_bars)((struct obj **)(uintptr_t)a0,(short)a1,(short)a2,(short)a3,(short)a4,(int)a5,(int)a6);}
void teleport_trap_api_936(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_937(int a0,int a1,int a2){(wake_nearto)((short)a0,(short)a1,(int)a2);}
void teleport_trap_api_938(int a0,int a1){(tmp_at)((short)a0,(short)a1);}
void teleport_trap_api_939(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_940(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_941(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_942(uint64_t a0,int a1){(map_trap)((struct trap *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_943(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_944(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_945(int a0,int a1,int a2,int a3,int a4){return (linedup)((short)a0,(short)a1,(short)a2,(short)a3,(int)a4);}
int teleport_trap_api_946(void){return (rng_log_enabled)();}
void teleport_trap_api_947(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_948(int a0){return (rn2)((int)a0);}
int teleport_trap_api_949(int a0){return (rn2)((int)a0);}
int teleport_trap_api_950(void){return (rng_log_enabled)();}
void teleport_trap_api_951(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_952(int a0){return (rn2)((int)a0);}
int teleport_trap_api_953(int a0){return (rn2)((int)a0);}
int teleport_trap_api_954(int a0,int a1){return (is_pool_or_lava)((short)a0,(short)a1);}
uint64_t teleport_trap_api_955(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(mksobj)((int)a0,(signed char)a1,(signed char)a2);}
int teleport_trap_api_956(uint64_t a0){return (weight)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_957(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_958(uint64_t a0){(stackobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_959(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_960(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_961(int a0,int a1){return (closed_door)((short)a0,(short)a1);}
int teleport_trap_api_962(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_963(void){return (rng_log_enabled)();}
void teleport_trap_api_964(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_965(int a0){return (rn2)((int)a0);}
int teleport_trap_api_966(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_967(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
int teleport_trap_api_968(void){return (rng_log_enabled)();}
void teleport_trap_api_969(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_970(int a0){return (rn2)((int)a0);}
int teleport_trap_api_971(int a0){return (rn2)((int)a0);}
int teleport_trap_api_972(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_973(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_974(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_975(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_976(int a0,int a1){(set_msg_xy)((short)a0,(short)a1);}
uint64_t teleport_trap_api_977(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_978(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_979(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_980(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_981(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_982(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_983(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_984(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_985(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_986(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_987(uint64_t a0,int a1){return (mon_knows_traps)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_988(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_989(void){return (rng_log_enabled)();}
void teleport_trap_api_990(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_991(int a0){return (rn2)((int)a0);}
int teleport_trap_api_992(int a0){return (rn2)((int)a0);}
void teleport_trap_api_993(uint64_t a0,int a1){(mon_learns_traps)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_994(uint64_t a0){(mons_see_trap)((struct trap *)(uintptr_t)a0);}
int teleport_trap_api_995(void){return (rng_log_enabled)();}
void teleport_trap_api_996(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_997(int a0){return (rnl)((int)a0);}
int teleport_trap_api_998(int a0){return (rnl)((int)a0);}
void teleport_trap_api_999(uint64_t a0,int a1){(setmangry)((struct monst *)(uintptr_t)a0,(signed char)a1);}
int teleport_trap_api_1000(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1001(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1002(int a0,int a1){(maybe_unhide_at)((short)a0,(short)a1);}
int teleport_trap_api_1003(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1004(uint64_t a0){return (uint64_t)(uintptr_t)(Amonnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1005(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1006(uint64_t a0){return (poly_when_stoned)((struct permonst *)(uintptr_t)a0);}
int teleport_trap_api_1007(int a0){return (polymon)((int)a0);}
void teleport_trap_api_1008(uint64_t a0){(urgent_pline)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1009(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1010(int a0){(done)((int)a0);}
int teleport_trap_api_1011(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_1012(uint64_t a0){return (poly_when_stoned)((struct permonst *)(uintptr_t)a0);}
void teleport_trap_api_1013(uint64_t a0){(mon_to_stone)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1014(uint64_t a0){return (vamp_stone)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1015(uint64_t a0,int a1,uint64_t a2){(mon_adjust_speed)((struct monst *)(uintptr_t)a0,(int)a1,(struct obj *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1016(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1017(uint64_t a0,uint64_t a1,uint64_t a2){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1018(uint64_t a0,int a1){(xkilled)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_1019(uint64_t a0){(monstone)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1020(uint64_t a0){return (uint64_t)(uintptr_t)(obj_pmname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1021(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1022(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1023(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1024(void){(uwepgone)();}
uint64_t teleport_trap_api_1025(uint64_t a0){return (uint64_t)(uintptr_t)(obj_pmname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1026(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1027(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1028(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1029(void){(uswapwepgone)();}
int teleport_trap_api_1030(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_trap_api_1031(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1032(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1033(uint64_t a0,uint64_t a1,unsigned a2){return (uint64_t)(uintptr_t)(corpse_xname)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned int)a2);}
void teleport_trap_api_1034(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);}
uint64_t teleport_trap_api_1035(uint64_t a0,int64_t a1){return (uint64_t)(uintptr_t)(which_armor)((struct monst *)(uintptr_t)a0,(long)a1);}
int teleport_trap_api_1036(uint64_t a0,int a1){return (Resists_Elem)((struct monst *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_1037(uint64_t a0){(mwepgone)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1038(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1039(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
uint64_t teleport_trap_api_1040(uint64_t a0){return (uint64_t)(uintptr_t)(makeplural)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1041(uint64_t a0,uint64_t a1){(Your)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1042(uint64_t a0){return (uint64_t)(uintptr_t)(buried_ball)((coord *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1043(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_1044(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1045(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1046(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_1047(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1048(int a0){(spoteffects)((signed char)a0);}
uint64_t teleport_trap_api_1049(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
void teleport_trap_api_1050(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1051(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1052(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1053(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1054(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_1055(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1056(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1057(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1058(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1059(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1060(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1061(int a0){(dismount_steed)((int)a0);}
void teleport_trap_api_1062(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1063(void){(float_vs_flight)();}
void teleport_trap_api_1064(void){(encumber_msg)();}
uint64_t teleport_trap_api_1065(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
void teleport_trap_api_1066(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1067(uint64_t a0,int a1,int a2,uint64_t a3){return (flooreffects)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_1068(void){(float_vs_flight)();}
void teleport_trap_api_1069(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1070(void){(encumber_msg)();}
void teleport_trap_api_1071(int a0){(nomul)((int)a0);}
void teleport_trap_api_1072(void){(float_vs_flight)();}
void teleport_trap_api_1073(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1074(void){(encumber_msg)();}
uint64_t teleport_trap_api_1075(uint64_t a0,int a1,int a2){return (uint64_t)(uintptr_t)(dmgtype_fromattack)((struct permonst *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_trap_api_1076(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1077(void){(encumber_msg)();}
int teleport_trap_api_1078(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
void teleport_trap_api_1079(uint64_t a0,int a1,int a2){(movobj)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_1080(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_1081(uint64_t a0){return (sticks)((struct permonst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1082(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1083(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1084(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1085(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1086(uint64_t a0){(set_ustuck)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1087(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
int teleport_trap_api_1088(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_1089(int a0,int a1){return (is_lava)((short)a0,(short)a1);}
int teleport_trap_api_1090(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_1091(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1092(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_1093(uint64_t a0){(You_feel)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1094(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1095(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1096(void){return (rng_log_enabled)();}
void teleport_trap_api_1097(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1098(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1099(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1100(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_1101(int a0){(dismount_steed)((int)a0);}
void teleport_trap_api_1102(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1103(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
void teleport_trap_api_1104(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1105(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
void teleport_trap_api_1106(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1107(void){(encumber_msg)();}
void teleport_trap_api_1108(uint64_t a0,uint64_t a1){(assign_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_1109(uint64_t a0){return (Can_fall_thru)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_1110(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_1111(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_1112(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_1113(int a0){return (pickup)((int)a0);}
void teleport_trap_api_1114(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1115(void){return (rng_log_enabled)();}
void teleport_trap_api_1116(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1117(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1118(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1119(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
uint64_t teleport_trap_api_1120(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_1121(uint64_t a0,uint64_t a1){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1122(uint64_t target,int a0,int a1){((void (*)(winid, boolean))(uintptr_t)target)((int)a0,(signed char)a1);}
void teleport_trap_api_1123(uint64_t target,int a0){((void (*)(winid))(uintptr_t)target)((int)a0);}
uint64_t teleport_trap_api_1124(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_1125(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1126(uint64_t a0){return (uint64_t)(uintptr_t)(u_locomotion)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1127(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_1128(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1129(uint64_t a0){return (uint64_t)(uintptr_t)(YMonnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1130(uint64_t a0,uint64_t a1){(Norep)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1131(void){return (rng_log_enabled)();}
void teleport_trap_api_1132(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1133(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1134(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1135(uint64_t a0){(Norep)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1136(void){return (rng_log_enabled)();}
void teleport_trap_api_1137(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1138(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1139(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1140(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1141(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1142(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1143(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1144(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1145(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1146(void){return (rng_log_enabled)();}
void teleport_trap_api_1147(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1148(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1149(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1150(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
uint64_t teleport_trap_api_1151(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1152(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1153(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1154(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
void teleport_trap_api_1155(int a0,int a1){(shieldeff)((short)a0,(short)a1);}
void teleport_trap_api_1156(uint64_t a0){(monstseesu)((unsigned long)a0);}
int teleport_trap_api_1157(void){return (rng_log_enabled)();}
void teleport_trap_api_1158(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1159(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1160(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1161(void){return (rng_log_enabled)();}
void teleport_trap_api_1162(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1163(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1164(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1165(uint64_t a0){(monstunseesu)((unsigned long)a0);}
int teleport_trap_api_1166(int a0){return (minuhpmax)((int)a0);}
int teleport_trap_api_1167(void){return (rng_log_enabled)();}
void teleport_trap_api_1168(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1169(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1170(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1171(void){return (rng_log_enabled)();}
void teleport_trap_api_1172(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1173(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1174(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1175(int a0,int a1){(setuhpmax)((int)a0,(signed char)a1);}
void teleport_trap_api_1176(uint64_t a0){(losexp)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1177(uint64_t a0){(monstunseesu)((unsigned long)a0);}
void teleport_trap_api_1178(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1179(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_1180(void){(burn_away_slime)();}
int teleport_trap_api_1181(void){return (rng_log_enabled)();}
void teleport_trap_api_1182(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1183(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1184(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1185(uint64_t a0,int a1,int a2){return (destroy_items)((struct monst *)(uintptr_t)a0,(int)a1,(int)a2);}
int teleport_trap_api_1186(int a0,int a1,int a2,int a3){return (burn_floor_objects)((short)a0,(short)a1,(signed char)a2,(signed char)a3);}
void teleport_trap_api_1187(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1188(int a0,int a1){return (is_ice)((short)a0,(short)a1);}
void teleport_trap_api_1189(int a0,int a1,uint64_t a2){(melt_ice)((short)a0,(short)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1190(void){return (rng_log_enabled)();}
void teleport_trap_api_1191(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1192(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1193(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1194(void){return (rng_log_enabled)();}
void teleport_trap_api_1195(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1196(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1197(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1198(uint64_t a0){return (resists_blnd)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1199(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1200(void){return (rng_log_enabled)();}
void teleport_trap_api_1201(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1202(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1203(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1204(int64_t a0,int a1){(make_blinded)((long)a0,(signed char)a1);}
void teleport_trap_api_1205(uint64_t a0,uint64_t a1){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1206(uint64_t a0){(You_see)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1207(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1208(void){return (rng_log_enabled)();}
void teleport_trap_api_1209(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1210(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1211(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1212(uint64_t a0,int a1){(incr_itimeout)((long *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_1213(uint64_t a0){(You_feel)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1214(void){return (rng_log_enabled)();}
void teleport_trap_api_1215(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1216(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1217(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1218(uint64_t a0,int a1){(incr_itimeout)((long *)(uintptr_t)a0,(int)a1);}
uint64_t teleport_trap_api_1219(uint64_t a0,int a1,int a2,unsigned a3){return (uint64_t)(uintptr_t)(makemon)((struct permonst *)(uintptr_t)a0,(short)a1,(short)a2,(unsigned int)a3);}
void teleport_trap_api_1220(int a0,int a1,int a2){(wake_nearto)((short)a0,(short)a1,(int)a2);}
void teleport_trap_api_1221(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1222(void){(self_invis_message)();}
void teleport_trap_api_1223(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1224(uint64_t a0){(You_cant)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1225(uint64_t a0,uint64_t a1){(You_feel)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1226(int a0,int a1){(newsym)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1227(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_1228(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1229(uint64_t a0){(You_hear)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1230(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_1231(uint64_t a0,uint64_t a1){(You_feel)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1232(uint64_t a0){return (In_quest)((d_level *)(uintptr_t)a0);}
int teleport_trap_api_1233(uint64_t a0){return (at_dgn_entrance)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1234(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1235(uint64_t a0){(Your)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1236(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1237(uint64_t a0){(You_feel)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1238(int a0,int a1,int a2){return (adjattrib)((int)a0,(int)a1,(int)a2);}
int teleport_trap_api_1239(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_1240(uint64_t a0,uint64_t a1,int a2){return (tamedog)((struct monst *)(uintptr_t)a0,(struct obj *)(uintptr_t)a1,(signed char)a2);}
int teleport_trap_api_1241(uint64_t a0){return (seffects)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1242(uint64_t a0){return (catch_lit)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1243(void){return (rng_log_enabled)();}
void teleport_trap_api_1244(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1245(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1246(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1247(uint64_t a0){return (uint64_t)(uintptr_t)(Yname2)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1248(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1249(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1250(uint64_t a0){(obj_extract_self)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1251(uint64_t a0,int a1,int a2,uint64_t a3){return (flooreffects)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_1252(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_1253(uint64_t a0){(setnotworn)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1254(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1255(void){return (rng_log_enabled)();}
void teleport_trap_api_1256(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1257(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1258(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1259(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1260(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1261(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1262(uint64_t a0){return (uint64_t)(uintptr_t)(Yname2)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1263(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_1264(uint64_t a0){(setnotworn)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1265(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1266(uint64_t a0){return (uint64_t)(uintptr_t)(Yname2)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1267(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_1268(uint64_t a0){(setnotworn)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1269(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1270(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1271(uint64_t a0,int a1,int a2){return (obj_resists)((struct obj *)(uintptr_t)a0,(int)a1,(int)a2);}
int teleport_trap_api_1272(int a0){return (undiscovered_artifact)((short)a0);}
uint64_t teleport_trap_api_1273(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(otense)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1274(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1275(uint64_t a0){return (uint64_t)(uintptr_t)(doname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1276(uint64_t a0,uint64_t a1){(You_see)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1277(uint64_t a0,int a1){(remove_worn_item)((struct obj *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_1278(uint64_t a0){(useupall)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1279(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1280(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1281(int a0){return (inventory_resistance_check)((int)a0);}
uint64_t teleport_trap_api_1282(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(aobjnam)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1283(uint64_t a0,uint64_t a1){(Your)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1284(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1285(uint64_t a0){return (uint64_t)(uintptr_t)(s_suffix)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1286(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(aobjnam)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1287(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1288(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(otense)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1289(uint64_t a0,uint64_t a1,uint64_t a2){(pline_The)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1290(uint64_t a0){return (uint64_t)(uintptr_t)(simpleonames)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1291(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1292(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
void teleport_trap_api_1293(uint64_t a0){(setnotworn)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1294(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1295(void){(update_inventory)();}
int teleport_trap_api_1296(uint64_t a0){return (splash_lit)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1297(uint64_t a0){return (uint64_t)(uintptr_t)(cxname)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1298(void){return (rng_log_enabled)();}
void teleport_trap_api_1299(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1300(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1301(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1302(uint64_t a0,int a1,int a2){(wet_a_towel)((struct obj *)(uintptr_t)a0,(int)a1,(signed char)a2);}
int teleport_trap_api_1303(void){return (rng_log_enabled)();}
void teleport_trap_api_1304(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1305(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1306(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1307(uint64_t a0){return (uint64_t)(uintptr_t)(yname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1308(uint64_t a0,uint64_t a1){(pline_The)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1309(void){(update_inventory)();}
int teleport_trap_api_1310(void){return (rng_log_enabled)();}
void teleport_trap_api_1311(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1312(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1313(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1314(uint64_t a0){return (uint64_t)(uintptr_t)(hliquid)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1315(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1316(uint64_t a0){return (uint64_t)(uintptr_t)(hliquid)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1317(uint64_t a0,uint64_t a1,uint64_t a2){(pline_The)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_1318(int a0,int a1,int a2,int a3){(discover_object)((int)a0,(signed char)a1,(signed char)a2,(signed char)a3);}
int teleport_trap_api_1319(void){return (rng_log_enabled)();}
void teleport_trap_api_1320(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1321(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1322(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1323(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1324(uint64_t a0,uint64_t a1,uint64_t a2){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1325(void){(update_inventory)();}
int teleport_trap_api_1326(uint64_t a0,uint64_t a1,uint64_t a2,int a3){return (get_obj_location)((struct obj *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1,(coordxy *)(uintptr_t)a2,(int)a3);}
int teleport_trap_api_1327(int a0,int a1){return (isok)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1328(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1329(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1330(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1331(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1332(uint64_t a0,uint64_t a1,uint64_t a2){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1333(void){return (rng_log_enabled)();}
void teleport_trap_api_1334(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1335(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1336(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1337(uint64_t a0){(blank_novel)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1338(void){(update_inventory)();}
uint64_t teleport_trap_api_1339(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1340(uint64_t a0,uint64_t a1,uint64_t a2){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1341(void){(update_inventory)();}
uint64_t teleport_trap_api_1342(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(vtense)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1343(uint64_t a0,uint64_t a1,uint64_t a2){(Your)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1344(void){(update_inventory)();}
int teleport_trap_api_1345(uint64_t a0,uint64_t a1,uint64_t a2,int a3){return (get_obj_location)((struct obj *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1,(coordxy *)(uintptr_t)a2,(int)a3);}
int teleport_trap_api_1346(int a0){return (inv_cnt)((signed char)a0);}
int teleport_trap_api_1347(void){return (near_capacity)();}
int teleport_trap_api_1348(void){return (rng_log_enabled)();}
void teleport_trap_api_1349(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1350(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1351(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1352(uint64_t a0){return (welded)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1353(uint64_t a0,int a1){(remove_worn_item)((struct obj *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_1354(uint64_t a0){(dropx)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1355(void){return (rng_log_enabled)();}
void teleport_trap_api_1356(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1357(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1358(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1359(int a0,int a1){return (crawl_destination)((short)a0,(short)a1);}
int teleport_trap_api_1360(int a0,int a1,uint64_t a2,unsigned a3){return (goodpos)((short)a0,(short)a1,(struct monst *)(uintptr_t)a2,(unsigned int)a3);}
uint64_t teleport_trap_api_1361(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
int teleport_trap_api_1362(int a0,int a1){return (is_ice)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1363(int a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(ice_descr)((short)a0,(short)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1364(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_1365(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_1366(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_1367(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_1368(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_trap_api_1369(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1370(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_1371(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_1372(uint64_t a0,uint64_t a1,int a2){return (strncmpi)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_trap_api_1373(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1374(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1375(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1376(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1377(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_1378(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
int teleport_trap_api_1379(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1380(uint64_t a0){return (uint64_t)(uintptr_t)(hliquid)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1381(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_1382(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_1383(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1384(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1385(uint64_t a0){return (uint64_t)(uintptr_t)(hliquid)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1386(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_1387(int a0,int a1){return (is_lava)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1388(uint64_t a0){return (uint64_t)(uintptr_t)(hliquid)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1389(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_1390(int a0,int a1){(update_lastseentyp)((short)a0,(short)a1);}
int teleport_trap_api_1391(int a0,int a1){return (is_waterwall)((short)a0,(short)a1);}
void teleport_trap_api_1392(int a0,int a1){(feel_newsym)((short)a0,(short)a1);}
int teleport_trap_api_1393(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
int teleport_trap_api_1394(void){return (rng_log_enabled)();}
void teleport_trap_api_1395(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1396(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1397(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1398(int a0,int a1){return (uint64_t)(uintptr_t)(waterbody_name)((short)a0,(short)a1);}
void teleport_trap_api_1399(uint64_t a0,uint64_t a1,uint64_t a2,int a3){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3);}
void teleport_trap_api_1400(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1401(void){return (rng_log_enabled)();}
void teleport_trap_api_1402(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1403(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1404(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1405(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(split_mon)((struct monst *)(uintptr_t)a0,(struct monst *)(uintptr_t)a1);}
void teleport_trap_api_1406(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1407(void){return (rng_log_enabled)();}
void teleport_trap_api_1408(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1409(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1410(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1411(void){return (rng_log_enabled)();}
void teleport_trap_api_1412(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1413(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1414(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_1415(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
int teleport_trap_api_1416(void){return (number_leashed)();}
void teleport_trap_api_1417(uint64_t a0,uint64_t a1,uint64_t a2){(pline_The)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1418(void){(unleash_all)();}
void teleport_trap_api_1419(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1420(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_1421(uint64_t a0){(Your)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1422(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1423(void){(unplacebc)();}
void teleport_trap_api_1424(void){(placebc)();}
void teleport_trap_api_1425(int a0){(vision_recalc)((int)a0);}
void teleport_trap_api_1426(int a0){(set_uinwater)((int)a0);}
void teleport_trap_api_1427(int a0){(under_water)((int)a0);}
int teleport_trap_api_1428(void){return (is_fainted)();}
int teleport_trap_api_1429(void){return (rng_log_enabled)();}
void teleport_trap_api_1430(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1431(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1432(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1433(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1434(uint64_t a0){return (noteleport_level)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1435(int a0){return (dotele)((signed char)a0);}
int teleport_trap_api_1436(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
void teleport_trap_api_1437(uint64_t a0){(pline_The)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1438(int a0){(dismount_steed)((int)a0);}
int teleport_trap_api_1439(int a0,int a1){return (is_pool)((short)a0,(short)a1);}
void teleport_trap_api_1440(uint64_t a0){(unmul)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1441(void){return (is_fainted)();}
void teleport_trap_api_1442(void){(reset_faint)();}
int teleport_trap_api_1443(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1444(uint64_t a0){return (uint64_t)(uintptr_t)(hliquid)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1445(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1446(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1447(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1448(int a0,int a1,int a2){(teleds)((short)a0,(short)a1,(int)a2);}
void teleport_trap_api_1449(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1450(int a0){(set_uinwater)((int)a0);}
void teleport_trap_api_1451(uint64_t a0){(urgent_pline)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1452(int a0,int a1){return (uint64_t)(uintptr_t)(waterbody_name)((short)a0,(short)a1);}
int teleport_trap_api_1453(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1454(uint64_t a0,uint64_t a1){return (strcmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1455(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1456(int a0){(done)((int)a0);}
int teleport_trap_api_1457(int a0){return (safe_teleds)((int)a0);}
void teleport_trap_api_1458(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1459(int a0){(set_uinwater)((int)a0);}
int teleport_trap_api_1460(void){return (rng_log_enabled)();}
void teleport_trap_api_1461(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1462(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1463(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1464(void){return (rng_log_enabled)();}
void teleport_trap_api_1465(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1466(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1467(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1468(uint64_t a0,uint64_t a1,int a2){(You_feel)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
int teleport_trap_api_1469(void){return (near_capacity)();}
uint64_t teleport_trap_api_1470(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1471(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1472(uint64_t a0){return (sticks)((struct permonst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1473(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1474(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1475(uint64_t a0){return (welded)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1476(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
uint64_t teleport_trap_api_1477(uint64_t a0){return (uint64_t)(uintptr_t)(makeplural)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1478(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1479(int a0){return (can_reach_floor)((signed char)a0);}
uint64_t teleport_trap_api_1480(int a0,int a1){return (uint64_t)(uintptr_t)(surface)((short)a0,(short)a1);}
int teleport_trap_api_1481(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_1482(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1483(uint64_t a0,int a1){return (is_art)((struct obj *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_1484(int a0,uint64_t a1){return (attacks)((int)a0,(struct obj *)(uintptr_t)a1);}
int teleport_trap_api_1485(void){return (rng_log_enabled)();}
void teleport_trap_api_1486(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1487(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1488(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1489(void){return (rng_log_enabled)();}
void teleport_trap_api_1490(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1491(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1492(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1493(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(mksobj)((int)a0,(signed char)a1,(signed char)a2);}
int teleport_trap_api_1494(uint64_t a0){return (weight)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1495(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
uint64_t teleport_trap_api_1496(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(bury_an_obj)((struct obj *)(uintptr_t)a0,(boolean *)(uintptr_t)a1);}
void teleport_trap_api_1497(uint64_t a0,int a1,int a2){(sellobj)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_1498(uint64_t a0){(stackobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1499(int a0,int a1){(newsym)((short)a0,(short)a1);}
int teleport_trap_api_1500(int a0){return (sgn)((int)a0);}
int teleport_trap_api_1501(int a0){return (sgn)((int)a0);}
int teleport_trap_api_1502(int a0,int a1,int a2,int a3,int a4){return (test_move)((short)a0,(short)a1,(short)a2,(short)a3,(int)a4);}
int teleport_trap_api_1503(int a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7,int a8){return (drag_ball)((short)a0,(short)a1,(int *)(uintptr_t)a2,(coordxy *)(uintptr_t)a3,(coordxy *)(uintptr_t)a4,(coordxy *)(uintptr_t)a5,(coordxy *)(uintptr_t)a6,(boolean *)(uintptr_t)a7,(signed char)a8);}
void teleport_trap_api_1504(int a0,int a1){(u_on_newpos)((short)a0,(short)a1);}
void teleport_trap_api_1505(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_1506(int a0){(vision_recalc)((int)a0);}
void teleport_trap_api_1507(int a0,int a1){(check_leash)((short)a0,(short)a1);}
void teleport_trap_api_1508(int a0,int a1,int a2,int a3,int a4,int a5){(move_bc)((int)a0,(int)a1,(short)a2,(short)a3,(short)a4,(short)a5);}
void teleport_trap_api_1509(int a0){(spoteffects)((signed char)a0);}
void teleport_trap_api_1510(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
void teleport_trap_api_1511(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1512(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1513(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1514(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(sobj_at)((int)a0,(short)a1,(short)a2);}
void teleport_trap_api_1515(uint64_t a0){(There)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1516(uint64_t a0,int a1,int a2){return (bad_rock)((struct permonst *)(uintptr_t)a0,(short)a1,(short)a2);}
int teleport_trap_api_1517(uint64_t a0,int a1,int a2){return (bad_rock)((struct permonst *)(uintptr_t)a0,(short)a1,(short)a2);}
int teleport_trap_api_1518(void){return (inv_weight)();}
int teleport_trap_api_1519(void){return (weight_cap)();}
void teleport_trap_api_1520(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1521(int a0){return (can_reach_floor)((signed char)a0);}
void teleport_trap_api_1522(void){(rider_cant_reach)();}
void teleport_trap_api_1523(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1524(void){return (rng_log_enabled)();}
void teleport_trap_api_1525(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1526(int a0){return (rnl)((int)a0);}
int teleport_trap_api_1527(int a0){return (rnl)((int)a0);}
void teleport_trap_api_1528(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1529(uint64_t a0){(abuse_dog)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1530(void){return (rng_log_enabled)();}
void teleport_trap_api_1531(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1532(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1533(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1534(uint64_t a0){(killed)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1535(void){return (rng_log_enabled)();}
void teleport_trap_api_1536(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1537(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1538(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1539(uint64_t a0){(pline_The)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1540(int a0){(dismount_steed)((int)a0);}
uint64_t teleport_trap_api_1541(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1542(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1543(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
int teleport_trap_api_1544(void){return (rng_log_enabled)();}
void teleport_trap_api_1545(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1546(int a0){return (rnl)((int)a0);}
int teleport_trap_api_1547(int a0){return (rnl)((int)a0);}
void teleport_trap_api_1548(uint64_t a0){(set_malign)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1549(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1550(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1551(void){return (rng_log_enabled)();}
void teleport_trap_api_1552(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1553(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1554(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1555(void){return (rng_log_enabled)();}
void teleport_trap_api_1556(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1557(int a0){return (rnl)((int)a0);}
int teleport_trap_api_1558(int a0){return (rnl)((int)a0);}
void teleport_trap_api_1559(int a0){(adjalign)((int)a0);}
void teleport_trap_api_1560(uint64_t a0){(You_feel)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1561(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1562(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
void teleport_trap_api_1563(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1564(uint64_t a0,int a1){return (is_art)((struct obj *)(uintptr_t)a0,(int)a1);}
int teleport_trap_api_1565(int a0,uint64_t a1){return (attacks)((int)a0,(struct obj *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1566(uint64_t a0){return (uint64_t)(uintptr_t)(bare_artifactname)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1567(uint64_t a0,int a1){return (is_art)((struct obj *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_1568(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_1569(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1570(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1571(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_1572(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1573(uint64_t a0,uint64_t a1,unsigned a2){return (uint64_t)(uintptr_t)(getobj)((const char *)(uintptr_t)a0,(int (*)(struct obj *))(uintptr_t)a1,(unsigned int)a2);}
void teleport_trap_api_1574(uint64_t a0,int a1){(consume_obj_charge)((struct obj *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_1575(uint64_t a0){(useup)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1576(int a0,int a1,int a2,int a3){(discover_object)((int)a0,(signed char)a1,(signed char)a2,(signed char)a3);}
void teleport_trap_api_1577(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1578(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_1579(int a0,int a1){(more_experienced)((int)a0,(int)a1);}
void teleport_trap_api_1580(void){(newexplevel)();}
void teleport_trap_api_1581(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1582(void){return (rng_log_enabled)();}
void teleport_trap_api_1583(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1584(int a0){return (rnl)((int)a0);}
int teleport_trap_api_1585(int a0){return (rnl)((int)a0);}
int teleport_trap_api_1586(int a0){return (calc_capacity)((int)a0);}
uint64_t teleport_trap_api_1587(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1588(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1589(void){return (rng_log_enabled)();}
void teleport_trap_api_1590(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1591(int a0){return (rnl)((int)a0);}
int teleport_trap_api_1592(int a0){return (rnl)((int)a0);}
void teleport_trap_api_1593(uint64_t a0){(set_malign)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1594(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1595(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1596(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1597(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1598(uint64_t a0){return (check_capacity)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1599(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
uint64_t teleport_trap_api_1600(uint64_t a0){return (uint64_t)(uintptr_t)(makeplural)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1601(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1602(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1603(uint64_t a0){return (uint64_t)(uintptr_t)(mon_pmname)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1604(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
uint64_t teleport_trap_api_1605(uint64_t a0){return (uint64_t)(uintptr_t)(makeplural)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1606(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1607(uint64_t a0){return (poly_when_stoned)((struct permonst *)(uintptr_t)a0);}
int teleport_trap_api_1608(int a0){return (polymon)((int)a0);}
void teleport_trap_api_1609(uint64_t target,int a0,int a1){((void (*)(winid, boolean))(uintptr_t)target)((int)a0,(signed char)a1);}
uint64_t teleport_trap_api_1610(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1611(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1612(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1613(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1614(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1615(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1616(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
uint64_t teleport_trap_api_1617(uint64_t a0){return (uint64_t)(uintptr_t)(makeplural)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1618(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1619(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1620(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1621(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1622(void){return (rng_log_enabled)();}
void teleport_trap_api_1623(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1624(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1625(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1626(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1627(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1628(uint64_t a0){return (uint64_t)(uintptr_t)(mon_nam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1629(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1630(int a0){return (acurr)((int)a0);}
int teleport_trap_api_1631(void){return (rng_log_enabled)();}
void teleport_trap_api_1632(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1633(void){return (level_difficulty)();}
int teleport_trap_api_1634(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1635(void){return (level_difficulty)();}
int teleport_trap_api_1636(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1637(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1638(int a0,int a1){(more_experienced)((int)a0,(int)a1);}
void teleport_trap_api_1639(void){(newexplevel)();}
void teleport_trap_api_1640(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
uint64_t teleport_trap_api_1641(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1642(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1643(void){return (rng_log_enabled)();}
void teleport_trap_api_1644(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1645(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1646(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1647(void){return (rng_log_enabled)();}
void teleport_trap_api_1648(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1649(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1650(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1651(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1652(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1653(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1654(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1655(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1656(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1657(uint64_t a0){(observe_object)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1658(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
int teleport_trap_api_1659(uint64_t a0,uint64_t a1,int a2,int a3){return (yn_function)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char)a2,(signed char)a3);}
uint64_t teleport_trap_api_1660(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1661(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1662(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1663(uint64_t a0){return (uint64_t)(uintptr_t)(has_magic_key)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1664(uint64_t a0){return (getdir)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1665(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_trap_api_1666(uint64_t a0){(pline_The)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1667(int a0){return (can_reach_floor)((signed char)a0);}
uint64_t teleport_trap_api_1668(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1669(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1670(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1671(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1672(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){(There)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4,(char *)(uintptr_t)a5);}
uint64_t teleport_trap_api_1673(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1674(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1675(uint64_t a0,uint64_t a1,uint64_t a2){(You_cant)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1676(uint64_t a0){return (uint64_t)(uintptr_t)(an)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1677(uint64_t a0,int a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7,uint64_t a8){(nh_snprintf)((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(char *)(uintptr_t)a5,(char *)(uintptr_t)a6,(char *)(uintptr_t)a7,(char *)(uintptr_t)a8);}
int teleport_trap_api_1678(uint64_t a0,uint64_t a1,int a2,int a3){return (yn_function)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char)a2,(signed char)a3);}
void teleport_trap_api_1679(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1680(uint64_t a0){(stumble_onto_mimic)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1681(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1682(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1683(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1684(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6){return (uint64_t)(uintptr_t)(safe_qbuf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(struct obj *)(uintptr_t)a3,(char *(*)(struct obj *))(uintptr_t)a4,(char *(*)(struct obj *))(uintptr_t)a5,(const char *)(uintptr_t)a6);}
uint64_t teleport_trap_api_1685(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6){return (uint64_t)(uintptr_t)(safe_qbuf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(struct obj *)(uintptr_t)a3,(char *(*)(struct obj *))(uintptr_t)a4,(char *(*)(struct obj *))(uintptr_t)a5,(const char *)(uintptr_t)a6);}
int teleport_trap_api_1686(uint64_t a0,uint64_t a1,int a2,int a3){return (yn_function)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char)a2,(signed char)a3);}
void teleport_trap_api_1687(uint64_t a0){(There)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1688(int a0,int a1){return (stumble_on_door_mimic)((short)a0,(short)a1);}
void teleport_trap_api_1689(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1690(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1691(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1692(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1693(void){return (rng_log_enabled)();}
void teleport_trap_api_1694(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1695(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1696(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1697(void){return (rng_log_enabled)();}
void teleport_trap_api_1698(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1699(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1700(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1701(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1702(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
int teleport_trap_api_1703(uint64_t a0,uint64_t a1,int a2,int a3){return (yn_function)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char)a2,(signed char)a3);}
void teleport_trap_api_1704(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
int teleport_trap_api_1705(void){return (rng_log_enabled)();}
void teleport_trap_api_1706(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1707(void){return (level_difficulty)();}
int teleport_trap_api_1708(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1709(void){return (level_difficulty)();}
int teleport_trap_api_1710(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1711(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1712(int a0,int a1){(unblock_point)((int)a0,(int)a1);}
void teleport_trap_api_1713(int a0,int a1){(newsym)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1714(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(in_rooms)((short)a0,(short)a1,(int)a2);}
void teleport_trap_api_1715(int a0,int a1,int64_t a2){(add_damage)((short)a0,(short)a1,(long)a2);}
void teleport_trap_api_1716(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1717(int a0,int a1){(more_experienced)((int)a0,(int)a1);}
void teleport_trap_api_1718(void){(newexplevel)();}
void teleport_trap_api_1719(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1720(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1721(uint64_t a0,int a1,uint64_t a2){return (uint64_t)(uintptr_t)(memset)((void *)(uintptr_t)a0,(int)a1,(unsigned long)a2);}
void teleport_trap_api_1722(uint64_t a0,uint64_t a1,int a2,uint64_t a3){(__assert_fail)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_1723(uint64_t a0,int a1){return (uint64_t)(uintptr_t)(strchr)((const char *)(uintptr_t)a0,(int)a1);}
void teleport_trap_api_1724(uint64_t a0,uint64_t a1,int a2,uint64_t a3){(__assert_fail)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_1725(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1726(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1727(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1728(uint64_t a0){return (uint64_t)(uintptr_t)(y_monnam)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1729(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1730(uint64_t a0){return (uint64_t)(uintptr_t)(noit_Monnam)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1731(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1732(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_1733(int a0){(vision_recalc)((int)a0);}
int teleport_trap_api_1734(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1735(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1736(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1737(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
void teleport_trap_api_1738(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_1739(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1740(uint64_t a0){return (uint64_t)(uintptr_t)(upstart)((char *)(uintptr_t)a0);}
void teleport_trap_api_1741(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1742(void){return (rng_log_enabled)();}
void teleport_trap_api_1743(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1744(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1745(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1746(int a0,int a1,int a2,int a3){return (dist2)((short)a0,(short)a1,(short)a2,(short)a3);}
int teleport_trap_api_1747(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1748(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1749(uint64_t a0){return (canseemon)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1750(uint64_t a0){return (sensemon)((struct monst *)(uintptr_t)a0);}
void teleport_trap_api_1751(uint64_t a0,int a1){(wakeup)((struct monst *)(uintptr_t)a0,(signed char)a1);}
int teleport_trap_api_1752(uint64_t a0,uint64_t a1,uint64_t a2,int a3){return (get_obj_location)((struct obj *)(uintptr_t)a0,(coordxy *)(uintptr_t)a1,(coordxy *)(uintptr_t)a2,(int)a3);}
void teleport_trap_api_1753(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1754(uint64_t target,int a0,int a1){((void (*)(winid, boolean))(uintptr_t)target)((int)a0,(signed char)a1);}
int teleport_trap_api_1755(void){return (rng_log_enabled)();}
void teleport_trap_api_1756(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1757(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1758(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1759(void){return (rng_log_enabled)();}
void teleport_trap_api_1760(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1761(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1762(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1763(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1764(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
int teleport_trap_api_1765(void){return (rng_log_enabled)();}
void teleport_trap_api_1766(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1767(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1768(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1769(void){return (rng_log_enabled)();}
void teleport_trap_api_1770(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1771(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1772(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1773(void){return (rng_log_enabled)();}
void teleport_trap_api_1774(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1775(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1776(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1777(int a0,int a1){return (costly_spot)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1778(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(in_rooms)((short)a0,(short)a1,(int)a2);}
uint64_t teleport_trap_api_1779(int a0){return (uint64_t)(uintptr_t)(shop_keeper)((char)a0);}
int teleport_trap_api_1780(int a0,int a1){return (inside_shop)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1781(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(in_rooms)((short)a0,(short)a1,(int)a2);}
uint64_t teleport_trap_api_1782(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(Tobjnam)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1783(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1784(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1785(uint64_t a0,uint64_t a1,uint64_t a2){return (sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int64_t teleport_trap_api_1786(uint64_t a0,int a1,int a2,int a3,int a4){return (stolen_value)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(signed char)a3,(signed char)a4);}
void teleport_trap_api_1787(uint64_t a0){(delete_contents)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1788(void){(unpunish)();}
int64_t teleport_trap_api_1789(uint64_t a0,int a1,int a2,int a3,int a4){return (stolen_value)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2,(signed char)a3,(signed char)a4);}
void teleport_trap_api_1790(uint64_t a0){(delobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1791(int a0){(wake_nearby)((signed char)a0);}
int teleport_trap_api_1792(void){return (rng_log_enabled)();}
void teleport_trap_api_1793(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1794(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1795(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1796(void){return (rng_log_enabled)();}
void teleport_trap_api_1797(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1798(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1799(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_1800(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_1801(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
uint64_t teleport_trap_api_1802(int64_t a0){return (uint64_t)(uintptr_t)(currency)((long)a0);}
void teleport_trap_api_1803(uint64_t a0,int64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(long)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1804(int64_t a0){return (uint64_t)(uintptr_t)(currency)((long)a0);}
void teleport_trap_api_1805(uint64_t a0,int64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(long)a1,(const char *)(uintptr_t)a2);}
void teleport_trap_api_1806(uint64_t a0,int a1,int a2){(make_angry_shk)((struct monst *)(uintptr_t)a0,(short)a1,(short)a2);}
uint64_t teleport_trap_api_1807(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1808(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1809(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1810(void){return (rng_log_enabled)();}
void teleport_trap_api_1811(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1812(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1813(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1814(uint64_t a0,int a1,uint64_t a2,int a3,int a4){(poisoned)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
uint64_t teleport_trap_api_1815(int a0,int a1,int a2,int a3){return (uint64_t)(uintptr_t)(create_gas_cloud)((short)a0,(short)a1,(int)a2,(int)a3);}
void teleport_trap_api_1816(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
uint64_t teleport_trap_api_1817(int a0){return (uint64_t)(uintptr_t)(body_part)((int)a0);}
void teleport_trap_api_1818(uint64_t a0,uint64_t a1){(You_feel)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1819(uint64_t a0,int a1,uint64_t a2,int a3,int a4){(poisoned)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2,(int)a3,(signed char)a4);}
void teleport_trap_api_1820(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
int teleport_trap_api_1821(void){return (rng_log_enabled)();}
void teleport_trap_api_1822(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1823(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1824(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_1825(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1826(int a0,int a1){(shieldeff)((short)a0,(short)a1);}
void teleport_trap_api_1827(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1828(uint64_t a0){(monstseesu)((unsigned long)a0);}
void teleport_trap_api_1829(uint64_t a0){(monstunseesu)((unsigned long)a0);}
int teleport_trap_api_1830(uint64_t a0,int a1,int a2){return (destroy_items)((struct monst *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_trap_api_1831(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_1832(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1833(void){return (rng_log_enabled)();}
void teleport_trap_api_1834(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1835(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1836(int a0,int a1){return (d)((int)a0,(int)a1);}
void teleport_trap_api_1837(int a0){(nomul)((int)a0);}
void teleport_trap_api_1838(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
void teleport_trap_api_1839(uint64_t a0){(You)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1840(void){return (rng_log_enabled)();}
void teleport_trap_api_1841(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1842(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1843(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1844(void){return (uint64_t)(uintptr_t)(rndcolor)();}
uint64_t teleport_trap_api_1845(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1846(uint64_t a0){return (uint64_t)(uintptr_t)(the)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1847(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1848(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1849(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(stagger)((const struct permonst *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1850(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
int teleport_trap_api_1851(void){return (rng_log_enabled)();}
void teleport_trap_api_1852(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1853(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1854(int a0){return (rn2)((int)a0);}
void teleport_trap_api_1855(int64_t a0,int a1){(make_stunned)((long)a0,(signed char)a1);}
int teleport_trap_api_1856(void){return (rng_log_enabled)();}
void teleport_trap_api_1857(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1858(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1859(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1860(int64_t a0,int a1,int64_t a2){return (make_hallucinated)((long)a0,(signed char)a1,(long)a2);}
void teleport_trap_api_1861(uint64_t a0){(impossible)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1862(void){(bot)();}
void teleport_trap_api_1863(uint64_t a0){(panic)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1864(uint64_t a0){(free)((void *)(uintptr_t)a0);}
int teleport_trap_api_1865(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_1866(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_1867(int a0){return (sgn)((int)a0);}
int teleport_trap_api_1868(int a0){return (sgn)((int)a0);}
int teleport_trap_api_1869(int a0,int a1){return (xytodir)((int)a0,(int)a1);}
int teleport_trap_api_1870(int a0,int a1){return (isok)((short)a0,(short)a1);}
int teleport_trap_api_1871(int a0,int a1){return (xytodir)((int)a0,(int)a1);}
int teleport_trap_api_1872(void){return (level_difficulty)();}
int teleport_trap_api_1873(void){return (rng_log_enabled)();}
void teleport_trap_api_1874(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1875(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1876(int a0){return (rnd)((int)a0);}
uint64_t teleport_trap_api_1877(uint64_t a0){return (uint64_t)(uintptr_t)(The)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1878(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1879(int a0){(wake_nearby)((signed char)a0);}
void teleport_trap_api_1880(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
void teleport_trap_api_1881(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
void teleport_trap_api_1882(int a0,int a1){(exercise)((int)a0,(signed char)a1);}
void teleport_trap_api_1883(int64_t a0,int a1){(make_stunned)((long)a0,(signed char)a1);}
int teleport_trap_api_1884(uint64_t a0){return (find_mac)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1885(void){return (rng_log_enabled)();}
void teleport_trap_api_1886(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1887(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1888(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1889(uint64_t a0){return (find_mac)((struct monst *)(uintptr_t)a0);}
int teleport_trap_api_1890(void){return (rng_log_enabled)();}
void teleport_trap_api_1891(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1892(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1893(int a0){return (rnd)((int)a0);}
uint64_t teleport_trap_api_1894(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1895(uint64_t a0){return (uint64_t)(uintptr_t)(doname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1896(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_1897(uint64_t a0){return (uint64_t)(uintptr_t)(Monnam)((struct monst *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1898(uint64_t a0){return (uint64_t)(uintptr_t)(doname)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1899(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){(pline_mon)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);}
int teleport_trap_api_1900(uint64_t a0,uint64_t a1){return (dmgval)((struct obj *)(uintptr_t)a0,(struct monst *)(uintptr_t)a1);}
void teleport_trap_api_1901(uint64_t a0,uint64_t a1,int a2){(monkilled)((struct monst *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
void teleport_trap_api_1902(int a0,int a1){(newsym)((short)a0,(short)a1);}
void teleport_trap_api_1903(uint64_t a0,int a1,int a2){(place_object)((struct obj *)(uintptr_t)a0,(short)a1,(short)a2);}
void teleport_trap_api_1904(uint64_t a0){(stackobj)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1905(uint64_t a0){(dealloc_obj)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1906(uint64_t a0,uint64_t a1,uint64_t a2){return (strncmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2);}
int teleport_trap_api_1907(uint64_t a0,uint64_t a1,uint64_t a2){return (strncmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2);}
int teleport_trap_api_1908(uint64_t a0,uint64_t a1,uint64_t a2){return (strncmp)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2);}
int teleport_trap_api_1909(void){return (rng_log_enabled)();}
void teleport_trap_api_1910(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1911(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1912(int a0,int a1){return (d)((int)a0,(int)a1);}
int teleport_trap_api_1913(uint64_t a0,int a1){return (debugcore)((const char *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_1914(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1915(int a0,int a1){(feel_newsym)((short)a0,(short)a1);}
void teleport_trap_api_1916(void){(burn_away_slime)();}
int teleport_trap_api_1917(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1918(uint64_t a0){return (uint64_t)(uintptr_t)(simpleonames)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1919(uint64_t a0,uint64_t a1,unsigned a2,unsigned a3){(impossible)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(unsigned int)a2,(unsigned int)a3);}
int teleport_trap_api_1920(uint64_t a0,int a1,int a2){return (obj_resists)((struct obj *)(uintptr_t)a0,(int)a1,(int)a2);}
uint64_t teleport_trap_api_1921(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(Yobjnam2)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1922(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
int teleport_trap_api_1923(void){return (Boots_off)();}
void teleport_trap_api_1924(uint64_t a0){(useup)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1925(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1926(uint64_t a0){return (uint64_t)(uintptr_t)(hliquid)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1927(uint64_t a0,uint64_t a1){(pline_The)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1928(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
uint64_t teleport_trap_api_1929(int a0,int a1){return (uint64_t)(uintptr_t)(waterbody_name)((short)a0,(short)a1);}
void teleport_trap_api_1930(uint64_t a0,uint64_t a1){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1931(uint64_t a0){return (uint64_t)(uintptr_t)(xname)((struct obj *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1932(uint64_t a0){return (uint64_t)(uintptr_t)(The)((const char *)(uintptr_t)a0);}
uint64_t teleport_trap_api_1933(uint64_t a0){return (uint64_t)(uintptr_t)(hcolor)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1934(uint64_t a0,uint64_t a1,uint64_t a2){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_trap_api_1935(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(Yobjnam2)((struct obj *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1936(uint64_t a0,uint64_t a1){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1937(uint64_t a0,int a1){(remove_worn_item)((struct obj *)(uintptr_t)a0,(signed char)a1);}
void teleport_trap_api_1938(uint64_t a0){(useupall)((struct obj *)(uintptr_t)a0);}
void teleport_trap_api_1939(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){(pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_trap_api_1940(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1941(uint64_t a0,uint64_t a1){(urgent_pline)((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);}
void teleport_trap_api_1942(int a0){(done)((int)a0);}
int teleport_trap_api_1943(int a0){return (safe_teleds)((int)a0);}
void teleport_trap_api_1944(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1945(uint64_t a0,int64_t a1){(set_itimeout)((long *)(uintptr_t)a0,(long)a1);}
int teleport_trap_api_1946(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
void teleport_trap_api_1947(uint64_t a0,int64_t a1){(set_itimeout)((long *)(uintptr_t)a0,(long)a1);}
void teleport_trap_api_1948(int a0){(spoteffects)((signed char)a0);}
int teleport_trap_api_1949(uint64_t a0,uint64_t a1){return (on_level)((d_level *)(uintptr_t)a0,(d_level *)(uintptr_t)a1);}
int teleport_trap_api_1950(void){return (rng_log_enabled)();}
void teleport_trap_api_1951(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1952(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1953(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1954(void){return (rng_log_enabled)();}
void teleport_trap_api_1955(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1956(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1957(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1958(int a0,int a1){return (uint64_t)(uintptr_t)(waterbody_name)((short)a0,(short)a1);}
void teleport_trap_api_1959(uint64_t a0,uint64_t a1,uint64_t a2){(You)((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
void teleport_trap_api_1960(uint64_t a0){(monstseesu)((unsigned long)a0);}
void teleport_trap_api_1961(uint64_t a0){(monstunseesu)((unsigned long)a0);}
void teleport_trap_api_1962(int a0,uint64_t a1,int a2){(losehp)((int)a0,(const char *)(uintptr_t)a1,(signed char)a2);}
int teleport_trap_api_1963(uint64_t a0,int a1,int a2){return (destroy_items)((struct monst *)(uintptr_t)a0,(int)a1,(int)a2);}
int teleport_trap_api_1964(int a0,int a1){return (is_lava)((short)a0,(short)a1);}
uint64_t teleport_trap_api_1965(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcpy)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
void teleport_trap_api_1966(uint64_t a0){(urgent_pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1967(void){(burn_away_slime)();}
void teleport_trap_api_1968(int a0){(done)((int)a0);}
int teleport_trap_api_1969(int a0){return (safe_teleds)((int)a0);}
int teleport_trap_api_1970(void){return (rng_log_enabled)();}
void teleport_trap_api_1971(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1972(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1973(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1974(uint64_t a0){(pline)((const char *)(uintptr_t)a0);}
void teleport_trap_api_1975(void){(burn_away_slime)();}
void teleport_trap_api_1976(uint64_t a0){(Norep)((const char *)(uintptr_t)a0);}
int teleport_trap_api_1977(void){return (rng_log_enabled)();}
void teleport_trap_api_1978(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1979(int a0){return (rnd)((int)a0);}
int teleport_trap_api_1980(int a0){return (rnd)((int)a0);}
void teleport_trap_api_1981(int a0){(change_luck)((signed char)a0);}
uint64_t teleport_trap_api_1982(int a0){return (uint64_t)(uintptr_t)(ordin)((int)a0);}
void teleport_trap_api_1983(int64_t a0,uint64_t a1,int a2,uint64_t a3){(livelog_printf)((long)a0,(const char *)(uintptr_t)a1,(int)a2,(const char *)(uintptr_t)a3);}
int teleport_trap_api_1984(int a0){return (rn2_on_display_rng)((int)a0);}
int teleport_trap_api_1985(void){return (rng_log_enabled)();}
void teleport_trap_api_1986(uint64_t a0,int a1,uint64_t a2){(rng_log_set_caller)((const char *)(uintptr_t)a0,(int)a1,(const char *)(uintptr_t)a2);}
int teleport_trap_api_1987(int a0){return (rn2)((int)a0);}
int teleport_trap_api_1988(int a0){return (rn2)((int)a0);}
uint64_t teleport_trap_api_1989(int a0,int a1,int a2){return (uint64_t)(uintptr_t)(rank_of)((int)a0,(short)a1,(signed char)a2);}
void teleport_trap_api_1990(uint64_t a0,uint64_t a1,int a2){(copynchars)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_trap_api_1991(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t)(strcat)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_trap_api_1992(uint64_t a0){return (uint64_t)(uintptr_t)(lcase)((char *)(uintptr_t)a0);}
int teleport_trap_api_1993(uint64_t a0){return (catch_lit)((struct obj *)(uintptr_t)a0);}
int teleport_trap_api_1994(int a0,int a1){return (isok)((short)a0,(short)a1);}
void teleport_trap_api_1995(uint64_t a0,int a1,int a2){(impossible)((const char *)(uintptr_t)a0,(int)a1,(int)a2);}
void teleport_trap_api_1996(uint64_t a0,int a1){(impossible)((const char *)(uintptr_t)a0,(int)a1);}
#pragma clang diagnostic pop
static char teleport_trap_literals[TELEPORT_TRAP_NATIVE_LITERAL_CAPACITY];
char *teleport_trap_literal_storage(void){return teleport_trap_literals;}
size_t teleport_trap_literal_capacity(void){return sizeof teleport_trap_literals;}
#include "tu-trap-layout.h"
size_t teleport_trap_layout_count(void){return sizeof teleport_trap_layout/sizeof *teleport_trap_layout;}
const char *teleport_trap_layout_name(size_t i){return teleport_trap_layout[i].name;}
uint64_t teleport_trap_layout_value(size_t i){return teleport_trap_layout[i].value;}
