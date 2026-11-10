/* SAVE typed field/global/dependency ABI; no save.c algorithms. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "save-source-data.h"
#ifndef DEBUG
#error Review changed SAVE configuration DEBUG
#endif
#ifndef UNIX
#error Review changed SAVE configuration UNIX
#endif
#ifndef MAIL
#error Review changed SAVE configuration MAIL
#endif
#ifndef HANGUPHANDLING
#error Review changed SAVE configuration HANGUPHANDLING
#endif
#ifndef INSURANCE
#error Review changed SAVE configuration INSURANCE
#endif
#ifndef FREE_ALL_MEMORY
#error Review changed SAVE configuration FREE_ALL_MEMORY
#endif
#ifndef DUMPLOG_CORE
#error Review changed SAVE configuration DUMPLOG_CORE
#endif
#ifdef NO_SIGNAL
#error Review changed SAVE configuration NO_SIGNAL
#endif
#ifdef MICRO
#error Review changed SAVE configuration MICRO
#endif
#ifdef TOS
#error Review changed SAVE configuration TOS
#endif
#ifdef VMS
#error Review changed SAVE configuration VMS
#endif
#ifdef USER_SOUNDS
#error Review changed SAVE configuration USER_SOUNDS
#endif
#ifdef SFCTOOL
#error Review changed SAVE configuration SFCTOOL
#endif
_Static_assert(sizeof(size_t)==8 && sizeof(time_t)==8 && sizeof(long)==8 && sizeof(void*)==8,"Review SAVE64 ABI");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2,"Review SAVE field width d_level.dnum");
_Static_assert((((__typeof__(((struct d_level*)0)->dnum))-1)<0)==1,"Review SAVE field sign d_level.dnum");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2,"Review SAVE field width d_level.dlevel");
_Static_assert((((__typeof__(((struct d_level*)0)->dlevel))-1)<0)==1,"Review SAVE field sign d_level.dlevel");
_Static_assert(sizeof(((struct align*)0)->type)==1,"Review SAVE field width align.type");
_Static_assert((((__typeof__(((struct align*)0)->type))-1)<0)==1,"Review SAVE field sign align.type");
_Static_assert(sizeof(((struct flag*)0)->debug)==1,"Review SAVE field width flag.debug");
_Static_assert((((__typeof__(((struct flag*)0)->debug))-1)<0)==1,"Review SAVE field sign flag.debug");
_Static_assert(sizeof(((struct flag*)0)->explore)==1,"Review SAVE field width flag.explore");
_Static_assert((((__typeof__(((struct flag*)0)->explore))-1)<0)==1,"Review SAVE field sign flag.explore");
_Static_assert(sizeof(((struct flag*)0)->female)==1,"Review SAVE field width flag.female");
_Static_assert((((__typeof__(((struct flag*)0)->female))-1)<0)==1,"Review SAVE field sign flag.female");
_Static_assert(sizeof(((struct flag*)0)->friday13)==1,"Review SAVE field width flag.friday13");
_Static_assert((((__typeof__(((struct flag*)0)->friday13))-1)<0)==1,"Review SAVE field sign flag.friday13");
_Static_assert(sizeof(((struct flag*)0)->ins_chkpt)==1,"Review SAVE field width flag.ins_chkpt");
_Static_assert((((__typeof__(((struct flag*)0)->ins_chkpt))-1)<0)==1,"Review SAVE field sign flag.ins_chkpt");
_Static_assert(sizeof(((struct flag*)0)->moonphase)==4,"Review SAVE field width flag.moonphase");
_Static_assert((((__typeof__(((struct flag*)0)->moonphase))-1)<0)==0,"Review SAVE field sign flag.moonphase");
_Static_assert(sizeof(((struct window_procs*)0)->wincap2)==8,"Review SAVE field width window_procs.wincap2");
_Static_assert((((__typeof__(((struct window_procs*)0)->wincap2))-1)<0)==0,"Review SAVE field sign window_procs.wincap2");
_Static_assert(sizeof(((struct dig_info*)0)->lastdigtime)==8,"Review SAVE field width dig_info.lastdigtime");
_Static_assert((((__typeof__(((struct dig_info*)0)->lastdigtime))-1)<0)==1,"Review SAVE field sign dig_info.lastdigtime");
_Static_assert(sizeof(((struct oextra*)0)->omid)==4,"Review SAVE field width oextra.omid");
_Static_assert((((__typeof__(((struct oextra*)0)->omid))-1)<0)==0,"Review SAVE field sign oextra.omid");
_Static_assert(sizeof(((struct tin_info*)0)->o_id)==4,"Review SAVE field width tin_info.o_id");
_Static_assert((((__typeof__(((struct tin_info*)0)->o_id))-1)<0)==0,"Review SAVE field sign tin_info.o_id");
_Static_assert(sizeof(((struct book_info*)0)->o_id)==4,"Review SAVE field width book_info.o_id");
_Static_assert((((__typeof__(((struct book_info*)0)->o_id))-1)<0)==0,"Review SAVE field sign book_info.o_id");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4,"Review SAVE field width obj.o_id");
_Static_assert((((__typeof__(((struct obj*)0)->o_id))-1)<0)==0,"Review SAVE field sign obj.o_id");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"Review SAVE field width obj.where");
_Static_assert((((__typeof__(((struct obj*)0)->where))-1)<0)==1,"Review SAVE field sign obj.where");
_Static_assert(sizeof(((struct obj*)0)->timed)==2,"Review SAVE field width obj.timed");
_Static_assert((((__typeof__(((struct obj*)0)->timed))-1)<0)==1,"Review SAVE field sign obj.timed");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"Review SAVE field width obj.corpsenm");
_Static_assert((((__typeof__(((struct obj*)0)->corpsenm))-1)<0)==1,"Review SAVE field sign obj.corpsenm");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"Review SAVE field width obj.owornmask");
_Static_assert((((__typeof__(((struct obj*)0)->owornmask))-1)<0)==1,"Review SAVE field sign obj.owornmask");
_Static_assert(sizeof(((struct victual_info*)0)->o_id)==4,"Review SAVE field width victual_info.o_id");
_Static_assert((((__typeof__(((struct victual_info*)0)->o_id))-1)<0)==0,"Review SAVE field sign victual_info.o_id");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4,"Review SAVE field width permonst.pmidx");
_Static_assert((((__typeof__(((struct permonst*)0)->pmidx))-1)<0)==1,"Review SAVE field sign permonst.pmidx");
_Static_assert(sizeof(((struct polearm_info*)0)->m_id)==4,"Review SAVE field width polearm_info.m_id");
_Static_assert((((__typeof__(((struct polearm_info*)0)->m_id))-1)<0)==0,"Review SAVE field sign polearm_info.m_id");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4,"Review SAVE field width monst.m_id");
_Static_assert((((__typeof__(((struct monst*)0)->m_id))-1)<0)==0,"Review SAVE field sign monst.m_id");
_Static_assert(sizeof(((struct monst*)0)->mnum)==2,"Review SAVE field width monst.mnum");
_Static_assert((((__typeof__(((struct monst*)0)->mnum))-1)<0)==1,"Review SAVE field sign monst.mnum");
_Static_assert(sizeof(((struct context_info*)0)->seer_turn)==8,"Review SAVE field width context_info.seer_turn");
_Static_assert((((__typeof__(((struct context_info*)0)->seer_turn))-1)<0)==1,"Review SAVE field sign context_info.seer_turn");
_Static_assert(sizeof(((struct fruit*)0)->fid)==4,"Review SAVE field width fruit.fid");
_Static_assert((((__typeof__(((struct fruit*)0)->fid))-1)<0)==1,"Review SAVE field sign fruit.fid");
_Static_assert(sizeof(((struct u_realtime*)0)->realtime)==8,"Review SAVE field width u_realtime.realtime");
_Static_assert((((__typeof__(((struct u_realtime*)0)->realtime))-1)<0)==1,"Review SAVE field sign u_realtime.realtime");
_Static_assert(sizeof(((struct u_realtime*)0)->start_timing)==8,"Review SAVE field width u_realtime.start_timing");
_Static_assert((((__typeof__(((struct u_realtime*)0)->start_timing))-1)<0)==1,"Review SAVE field sign u_realtime.start_timing");
_Static_assert(sizeof(((struct u_realtime*)0)->finish_time)==8,"Review SAVE field width u_realtime.finish_time");
_Static_assert((((__typeof__(((struct u_realtime*)0)->finish_time))-1)<0)==1,"Review SAVE field sign u_realtime.finish_time");
_Static_assert(sizeof(((struct edog*)0)->droptime)==8,"Review SAVE field width edog.droptime");
_Static_assert((((__typeof__(((struct edog*)0)->droptime))-1)<0)==1,"Review SAVE field sign edog.droptime");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8,"Review SAVE field width edog.hungrytime");
_Static_assert((((__typeof__(((struct edog*)0)->hungrytime))-1)<0)==1,"Review SAVE field sign edog.hungrytime");
_Static_assert(sizeof(((struct linfo*)0)->flags)==1,"Review SAVE field width linfo.flags");
_Static_assert((((__typeof__(((struct linfo*)0)->flags))-1)<0)==0,"Review SAVE field sign linfo.flags");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4,"Review SAVE field width mextra.mcorpsenm");
_Static_assert((((__typeof__(((struct mextra*)0)->mcorpsenm))-1)<0)==1,"Review SAVE field sign mextra.mcorpsenm");
_Static_assert(sizeof(((struct accessibility_data*)0)->mon_notices_blocked)==4,"Review SAVE field width accessibility_data.mon_notices_blocked");
_Static_assert((((__typeof__(((struct accessibility_data*)0)->mon_notices_blocked))-1)<0)==1,"Review SAVE field sign accessibility_data.mon_notices_blocked");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4,"Review SAVE field width instance_flags.last_msg");
_Static_assert((((__typeof__(((struct instance_flags*)0)->last_msg))-1)<0)==1,"Review SAVE field sign instance_flags.last_msg");
_Static_assert(sizeof(((struct instance_flags*)0)->purge_monsters)==4,"Review SAVE field width instance_flags.purge_monsters");
_Static_assert((((__typeof__(((struct instance_flags*)0)->purge_monsters))-1)<0)==1,"Review SAVE field sign instance_flags.purge_monsters");
_Static_assert(sizeof(((struct instance_flags*)0)->window_inited)==1,"Review SAVE field width instance_flags.window_inited");
_Static_assert((((__typeof__(((struct instance_flags*)0)->window_inited))-1)<0)==1,"Review SAVE field sign instance_flags.window_inited");
_Static_assert(sizeof(((struct instance_globals_h*)0)->havestate)==1,"Review SAVE field width instance_globals_h.havestate");
_Static_assert((((__typeof__(((struct instance_globals_h*)0)->havestate))-1)<0)==1,"Review SAVE field sign instance_globals_h.havestate");
_Static_assert(sizeof(((struct you*)0)->uhp)==4,"Review SAVE field width you.uhp");
_Static_assert((((__typeof__(((struct you*)0)->uhp))-1)<0)==1,"Review SAVE field sign you.uhp");
_Static_assert(sizeof(((struct you*)0)->ustuck_mid)==4,"Review SAVE field width you.ustuck_mid");
_Static_assert((((__typeof__(((struct you*)0)->ustuck_mid))-1)<0)==0,"Review SAVE field sign you.ustuck_mid");
_Static_assert(sizeof(((struct you*)0)->usteed_mid)==4,"Review SAVE field width you.usteed_mid");
_Static_assert((((__typeof__(((struct you*)0)->usteed_mid))-1)<0)==0,"Review SAVE field sign you.usteed_mid");
_Static_assert(sizeof(((struct levelflags*)0)->stasis_until)==8,"Review SAVE field width levelflags.stasis_until");
_Static_assert((((__typeof__(((struct levelflags*)0)->stasis_until))-1)<0)==1,"Review SAVE field sign levelflags.stasis_until");
_Static_assert(sizeof(((struct instance_globals_m*)0)->multi)==8,"Review SAVE field width instance_globals_m.multi");
_Static_assert((((__typeof__(((struct instance_globals_m*)0)->multi))-1)<0)==1,"Review SAVE field sign instance_globals_m.multi");
_Static_assert(sizeof(((struct sinfo*)0)->done_hup)==4,"Review SAVE field width sinfo.done_hup");
_Static_assert((((__typeof__(((struct sinfo*)0)->done_hup))-1)<0)==1,"Review SAVE field sign sinfo.done_hup");
_Static_assert(sizeof(((struct sinfo*)0)->something_worth_saving)==4,"Review SAVE field width sinfo.something_worth_saving");
_Static_assert((((__typeof__(((struct sinfo*)0)->something_worth_saving))-1)<0)==1,"Review SAVE field sign sinfo.something_worth_saving");
_Static_assert(sizeof(((struct sinfo*)0)->saving)==4,"Review SAVE field width sinfo.saving");
_Static_assert((((__typeof__(((struct sinfo*)0)->saving))-1)<0)==1,"Review SAVE field sign sinfo.saving");
_Static_assert(sizeof(((struct sinfo*)0)->restoring)==4,"Review SAVE field width sinfo.restoring");
_Static_assert((((__typeof__(((struct sinfo*)0)->restoring))-1)<0)==1,"Review SAVE field sign sinfo.restoring");
_Static_assert(sizeof(((struct sinfo*)0)->freeingdata)==4,"Review SAVE field width sinfo.freeingdata");
_Static_assert((((__typeof__(((struct sinfo*)0)->freeingdata))-1)<0)==1,"Review SAVE field sign sinfo.freeingdata");
_Static_assert(sizeof(((struct sinfo*)0)->savefile_completed)==4,"Review SAVE field width sinfo.savefile_completed");
_Static_assert((((__typeof__(((struct sinfo*)0)->savefile_completed))-1)<0)==1,"Review SAVE field sign sinfo.savefile_completed");
_Static_assert(sizeof(((struct instance_globals_saved_d*)0)->doors_alloc)==4,"Review SAVE field width instance_globals_saved_d.doors_alloc");
_Static_assert((((__typeof__(((struct instance_globals_saved_d*)0)->doors_alloc))-1)<0)==1,"Review SAVE field sign instance_globals_saved_d.doors_alloc");
_Static_assert(sizeof(((struct instance_globals_saved_h*)0)->hackpid)==4,"Review SAVE field width instance_globals_saved_h.hackpid");
_Static_assert((((__typeof__(((struct instance_globals_saved_h*)0)->hackpid))-1)<0)==1,"Review SAVE field sign instance_globals_saved_h.hackpid");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8,"Review SAVE field width instance_globals_saved_m.moves");
_Static_assert((((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1)<0)==1,"Review SAVE field sign instance_globals_saved_m.moves");
_Static_assert(sizeof(((struct nh_file*)0)->fd)==4,"Review SAVE field width nh_file.fd");
_Static_assert((((__typeof__(((struct nh_file*)0)->fd))-1)<0)==1,"Review SAVE field sign nh_file.fd");
_Static_assert(sizeof(((struct nh_file*)0)->mode)==4,"Review SAVE field width nh_file.mode");
_Static_assert((((__typeof__(((struct nh_file*)0)->mode))-1)<0)==1,"Review SAVE field sign nh_file.mode");
_Static_assert(sizeof(((struct nh_file*)0)->rcount)==8,"Review SAVE field width nh_file.rcount");
_Static_assert((((__typeof__(((struct nh_file*)0)->rcount))-1)<0)==1,"Review SAVE field sign nh_file.rcount");
_Static_assert(sizeof(((struct nh_file*)0)->wcount)==8,"Review SAVE field width nh_file.wcount");
_Static_assert((((__typeof__(((struct nh_file*)0)->wcount))-1)<0)==1,"Review SAVE field sign nh_file.wcount");
_Static_assert(sizeof(((struct nh_file*)0)->structlevel)==1,"Review SAVE field width nh_file.structlevel");
_Static_assert((((__typeof__(((struct nh_file*)0)->structlevel))-1)<0)==1,"Review SAVE field sign nh_file.structlevel");
_Static_assert(sizeof(((struct instance_globals_saved_w*)0)->wreserve)==8,"Review SAVE field width instance_globals_saved_w.wreserve");
_Static_assert((((__typeof__(((struct instance_globals_saved_w*)0)->wreserve))-1)<0)==1,"Review SAVE field sign instance_globals_saved_w.wreserve");
_Static_assert(sizeof(((struct instance_globals_saved_w*)0)->wtreserved)==4,"Review SAVE field width instance_globals_saved_w.wtreserved");
_Static_assert((((__typeof__(((struct instance_globals_saved_w*)0)->wtreserved))-1)<0)==1,"Review SAVE field sign instance_globals_saved_w.wtreserved");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Strlen_),unsigned int (*)(const char *, const char *, int)),"Review SAVE dependency Strlen_");
_Static_assert(__builtin_types_compatible_p(__typeof__(&There),void (*)(const char *, ...)),"Review SAVE dependency There");
_Static_assert(__builtin_types_compatible_p(__typeof__(&alloc_itermonarr),void (*)(unsigned int)),"Review SAVE dependency alloc_itermonarr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&allunworn),void (*)(void)),"Review SAVE dependency allunworn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bflush),void (*)(int)),"Review SAVE dependency bflush");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bufoff),void (*)(int)),"Review SAVE dependency bufoff");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bufon),void (*)(int)),"Review SAVE dependency bufon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&change_luck),void (*)(schar)),"Review SAVE dependency change_luck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&clear_level_structures),void (*)(void)),"Review SAVE dependency clear_level_structures");
_Static_assert(__builtin_types_compatible_p(__typeof__(&close_nhfile),void (*)(NHFILE *)),"Review SAVE dependency close_nhfile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cmdbind_freeall),void (*)(void)),"Review SAVE dependency cmdbind_freeall");
_Static_assert(__builtin_types_compatible_p(__typeof__(&cmdq_clear),void (*)(int)),"Review SAVE dependency cmdq_clear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&create_levelfile),NHFILE *(*)(int, char *)),"Review SAVE dependency create_levelfile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&create_savefile),NHFILE *(*)(void)),"Review SAVE dependency create_savefile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dealloc_monst),void (*)(struct monst *)),"Review SAVE dependency dealloc_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dealloc_obj),void (*)(struct obj *)),"Review SAVE dependency dealloc_obj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&debugcore),boolean (*)(const char *, boolean)),"Review SAVE dependency debugcore");
_Static_assert(__builtin_types_compatible_p(__typeof__(&delete_levelfile),void (*)(int)),"Review SAVE dependency delete_levelfile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&delete_savefile),int (*)(void)),"Review SAVE dependency delete_savefile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dmonsfree),void (*)(void)),"Review SAVE dependency dmonsfree");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dobjsfree),void (*)(void)),"Review SAVE dependency dobjsfree");
_Static_assert(__builtin_types_compatible_p(__typeof__(&docrt),void (*)(void)),"Review SAVE dependency docrt");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done),void (*)(int)),"Review SAVE dependency done");
_Static_assert(__builtin_types_compatible_p(__typeof__(&done_object_cleanup),void (*)(void)),"Review SAVE dependency done_object_cleanup");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dumplogfreemessages),void (*)(void)),"Review SAVE dependency dumplogfreemessages");
_Static_assert(__builtin_types_compatible_p(__typeof__(&forget_temple_entry),void (*)(struct monst *)),"Review SAVE dependency forget_temple_entry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fqname),const char *(*)(const char *, int, int)),"Review SAVE dependency fqname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free),void (*)(void *)),"Review SAVE dependency free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_CapMons),void (*)(void)),"Review SAVE dependency free_CapMons");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_autopickup_exceptions),void (*)(void)),"Review SAVE dependency free_autopickup_exceptions");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_convert_filenames),void (*)(void)),"Review SAVE dependency free_convert_filenames");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_glyphid_cache),void (*)(void)),"Review SAVE dependency free_glyphid_cache");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_invbuf),void (*)(void)),"Review SAVE dependency free_invbuf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_luathemes),void (*)(enum lua_theme_group)),"Review SAVE dependency free_luathemes");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_maildata),void (*)(void)),"Review SAVE dependency free_maildata");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_menu_coloring),void (*)(void)),"Review SAVE dependency free_menu_coloring");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_nhuuid),void (*)(void)),"Review SAVE dependency free_nhuuid");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_rect),void (*)(void)),"Review SAVE dependency free_rect");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_symsets),void (*)(void)),"Review SAVE dependency free_symsets");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_tutorial),void (*)(void)),"Review SAVE dependency free_tutorial");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free_youbuf),void (*)(void)),"Review SAVE dependency free_youbuf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&freeroleoptvals),void (*)(void)),"Review SAVE dependency freeroleoptvals");
_Static_assert(__builtin_types_compatible_p(__typeof__(&get_freeing_nhfile),NHFILE *(*)(void)),"Review SAVE dependency get_freeing_nhfile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getlev),void (*)(NHFILE *, int, xint8)),"Review SAVE dependency getlev");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getnow),time_t (*)(void)),"Review SAVE dependency getnow");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getuid),uid_t (*)(void)),"Review SAVE dependency getuid");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyphid_cache_status),boolean (*)(void)),"Review SAVE dependency glyphid_cache_status");
_Static_assert(__builtin_types_compatible_p(__typeof__(&impossible),void (*)(const char *, ...)),"Review SAVE dependency impossible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&ledger_no),xint16 (*)(d_level *)),"Review SAVE dependency ledger_no");
_Static_assert(__builtin_types_compatible_p(__typeof__(&maxledgerno),xint16 (*)(void)),"Review SAVE dependency maxledgerno");
_Static_assert(__builtin_types_compatible_p(__typeof__(&memset),void *(*)(void *, int, unsigned long)),"Review SAVE dependency memset");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_animal_list),void (*)(boolean)),"Review SAVE dependency mon_animal_list");
_Static_assert(__builtin_types_compatible_p(__typeof__(&moves_to_relative_time),void (*)(long *)),"Review SAVE dependency moves_to_relative_time");
_Static_assert(__builtin_types_compatible_p(__typeof__(&msgtype_free),void (*)(void)),"Review SAVE dependency msgtype_free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_compress),void (*)(const char *)),"Review SAVE dependency nh_compress");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_sfconvert),void (*)(const char *)),"Review SAVE dependency nh_sfconvert");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_snprintf),void (*)(const char *, int, char *, size_t, const char *, ...)),"Review SAVE dependency nh_snprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_terminate),void (*)(int)),"Review SAVE dependency nh_terminate");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_uncompress),void (*)(const char *)),"Review SAVE dependency nh_uncompress");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nomul),void (*)(int)),"Review SAVE dependency nomul");
_Static_assert(__builtin_types_compatible_p(__typeof__(&open_levelfile),NHFILE *(*)(int, char *)),"Review SAVE dependency open_levelfile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&open_savefile),NHFILE *(*)(void)),"Review SAVE dependency open_savefile");
_Static_assert(__builtin_types_compatible_p(__typeof__(&options_free_window_colors),void (*)(void)),"Review SAVE dependency options_free_window_colors");
_Static_assert(__builtin_types_compatible_p(__typeof__(&panic),void (*)(const char *, ...)),"Review SAVE dependency panic");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline),void (*)(const char *, ...)),"Review SAVE dependency pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&purge_all_custom_entries),void (*)(void)),"Review SAVE dependency purge_all_custom_entries");
_Static_assert(__builtin_types_compatible_p(__typeof__(&relative_time_to_moves),void (*)(long *)),"Review SAVE dependency relative_time_to_moves");
_Static_assert(__builtin_types_compatible_p(__typeof__(&release_runtime_info),void (*)(void)),"Review SAVE dependency release_runtime_info");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rest_adjust_levelflags),void (*)(void)),"Review SAVE dependency rest_adjust_levelflags");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_artifacts),void (*)(NHFILE *)),"Review SAVE dependency save_artifacts");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_dungeon),void (*)(NHFILE *, boolean, boolean)),"Review SAVE dependency save_dungeon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_engravings),void (*)(NHFILE *)),"Review SAVE dependency save_engravings");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_exclusions),void (*)(NHFILE *)),"Review SAVE dependency save_exclusions");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_killers),void (*)(NHFILE *)),"Review SAVE dependency save_killers");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_light_sources),void (*)(NHFILE *, int)),"Review SAVE dependency save_light_sources");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_luadata),void (*)(NHFILE *)),"Review SAVE dependency save_luadata");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_oracles),void (*)(NHFILE *)),"Review SAVE dependency save_oracles");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_regions),void (*)(NHFILE *)),"Review SAVE dependency save_regions");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_rooms),void (*)(NHFILE *)),"Review SAVE dependency save_rooms");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_savefile_name),void (*)(NHFILE *)),"Review SAVE dependency save_savefile_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_timers),void (*)(NHFILE *, int)),"Review SAVE dependency save_timers");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_track),void (*)(NHFILE *)),"Review SAVE dependency save_track");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_waterlevel),void (*)(NHFILE *)),"Review SAVE dependency save_waterlevel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&save_worm),void (*)(NHFILE *)),"Review SAVE dependency save_worm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&savedsym_free),void (*)(void)),"Review SAVE dependency savedsym_free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&savenames),void (*)(NHFILE *)),"Review SAVE dependency savenames");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_ustuck),void (*)(struct monst *)),"Review SAVE dependency set_ustuck");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sethanguphandler),void (*)(void (*)(int))),"Review SAVE dependency sethanguphandler");
_Static_assert(__builtin_types_compatible_p(__typeof__(&setworn),void (*)(struct obj *, long)),"Review SAVE dependency setworn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfi_int),void (*)(NHFILE *, int *, const char *)),"Review SAVE dependency sfi_int");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_cemetery),void (*)(NHFILE *, struct cemetery *, const char *)),"Review SAVE dependency sfo_cemetery");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_char),void (*)(NHFILE *, char *, const char *, int)),"Review SAVE dependency sfo_char");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_context_info),void (*)(NHFILE *, struct context_info *, const char *)),"Review SAVE dependency sfo_context_info");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_damage),void (*)(NHFILE *, struct damage *, const char *)),"Review SAVE dependency sfo_damage");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_dest_area),void (*)(NHFILE *, struct dest_area *, const char *)),"Review SAVE dependency sfo_dest_area");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_ebones),void (*)(NHFILE *, struct ebones *, const char *)),"Review SAVE dependency sfo_ebones");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_edog),void (*)(NHFILE *, struct edog *, const char *)),"Review SAVE dependency sfo_edog");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_egd),void (*)(NHFILE *, struct egd *, const char *)),"Review SAVE dependency sfo_egd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_emin),void (*)(NHFILE *, struct emin *, const char *)),"Review SAVE dependency sfo_emin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_epri),void (*)(NHFILE *, struct epri *, const char *)),"Review SAVE dependency sfo_epri");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_eshk),void (*)(NHFILE *, struct eshk *, const char *)),"Review SAVE dependency sfo_eshk");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_flag),void (*)(NHFILE *, struct flag *, const char *)),"Review SAVE dependency sfo_flag");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_fruit),void (*)(NHFILE *, struct fruit *, const char *)),"Review SAVE dependency sfo_fruit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_gamelog_line),void (*)(NHFILE *, struct gamelog_line *, const char *)),"Review SAVE dependency sfo_gamelog_line");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_int),void (*)(NHFILE *, int *, const char *)),"Review SAVE dependency sfo_int");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_int32),void (*)(NHFILE *, int32 *, const char *)),"Review SAVE dependency sfo_int32");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_levelflags),void (*)(NHFILE *, struct levelflags *, const char *)),"Review SAVE dependency sfo_levelflags");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_long),void (*)(NHFILE *, long *, const char *)),"Review SAVE dependency sfo_long");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_monst),void (*)(NHFILE *, struct monst *, const char *)),"Review SAVE dependency sfo_monst");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_mvitals),void (*)(NHFILE *, struct mvitals *, const char *)),"Review SAVE dependency sfo_mvitals");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_nhcoord),void (*)(NHFILE *, struct nhcoord *, const char *)),"Review SAVE dependency sfo_nhcoord");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_obj),void (*)(NHFILE *, struct obj *, const char *)),"Review SAVE dependency sfo_obj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_q_score),void (*)(NHFILE *, struct q_score *, const char *)),"Review SAVE dependency sfo_q_score");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_rm),void (*)(NHFILE *, struct rm *, const char *)),"Review SAVE dependency sfo_rm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_s_level),void (*)(NHFILE *, struct s_level *, const char *)),"Review SAVE dependency sfo_s_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_schar),void (*)(NHFILE *, schar *, const char *)),"Review SAVE dependency sfo_schar");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_spell),void (*)(NHFILE *, struct spell *, const char *)),"Review SAVE dependency sfo_spell");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_stairway),void (*)(NHFILE *, struct stairway *, const char *)),"Review SAVE dependency sfo_stairway");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_trap),void (*)(NHFILE *, struct trap *, const char *)),"Review SAVE dependency sfo_trap");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_ulong),void (*)(NHFILE *, ulong *, const char *)),"Review SAVE dependency sfo_ulong");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_unsigned),void (*)(NHFILE *, unsigned int *, const char *)),"Review SAVE dependency sfo_unsigned");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_xint8),void (*)(NHFILE *, xint8 *, const char *)),"Review SAVE dependency sfo_xint8");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sfo_you),void (*)(NHFILE *, struct you *, const char *)),"Review SAVE dependency sfo_you");
_Static_assert(__builtin_types_compatible_p(__typeof__(&status_finish),void (*)(void)),"Review SAVE dependency status_finish");
_Static_assert(__builtin_types_compatible_p(__typeof__(&store_version),void (*)(NHFILE *)),"Review SAVE dependency store_version");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char *(*)(char *, const char *)),"Review SAVE dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strlen),unsigned long (*)(const char *)),"Review SAVE dependency strlen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sysopt_release),void (*)(void)),"Review SAVE dependency sysopt_release");
_Static_assert(__builtin_types_compatible_p(__typeof__(&timet_delta),long (*)(time_t, time_t)),"Review SAVE dependency timet_delta");
_Static_assert(__builtin_types_compatible_p(__typeof__(&tmp_at),void (*)(coordxy, coordxy)),"Review SAVE dependency tmp_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vision_recalc),void (*)(int)),"Review SAVE dependency vision_recalc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&wish_history_flush),void (*)(void)),"Review SAVE dependency wish_history_flush");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yn_function),char (*)(const char *, const char *, char, boolean)),"Review SAVE dependency yn_function");
_Static_assert(__builtin_types_compatible_p(__typeof__(&yyyymmddhhmmss),char *(*)(time_t)),"Review SAVE dependency yyyymmddhhmmss");
extern int options_set_window_colors_flag;
static struct trap save_zerotrap;static struct fruit save_zerofruit;
void *teleport_save_global(int index){switch(index){
case 0:return (void*)&windowprocs;
case 1:return (void*)&WIN_MESSAGE;
case 2:return (void*)&gm;
case 3:return (void*)&program_state;
case 4:return (void*)&u;
case 5:return (void*)&soundprocs;
case 6:return (void*)&a11y;
case 7:return (void*)&iflags;
case 8:return (void*)&gs;
case 9:return (void*)&flags;
case 10:return (void*)&gl;
case 11:return (void*)&uball;
case 12:return (void*)&uchain;
case 13:return (void*)&gu;
case 14:return (void*)&svl;
case 15:return (void*)&svk;
case 16:return (void*)&svh;
case 17:return (void*)&gg;
case 18:return (void*)&svn;
case 19:return (void*)&svm;
case 20:return (void*)&svc;
case 21:return (void*)&urealtime;
case 22:return (void*)&svw;
case 23:return (void*)&ubirthday;
case 24:return (void*)&gi;
case 25:return (void*)&svq;
case 26:return (void*)&svs;
case 27:return (void*)&svp;
case 28:return (void*)&gh;
case 29:return (void*)&go;
case 30:return (void*)&svu;
case 31:return (void*)&svd;
case 32:return (void*)&gf;
case 33:return (void*)&gb;
case 34:return (void*)&svr;
case 35:return (void*)&genders;
case 36:return (void*)&aligns;
case 37:return (void*)&options_set_window_colors_flag;
case 38:return &save_zerotrap;
case 39:return &save_zerofruit;
default:abort();}}
uint64_t teleport_save_read(int kind,void*at,int field){switch(kind){
case 0:{struct stairway*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->tolev);
case 1:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 1:{struct q_score*p=at;switch(field){
default:abort();}}
case 2:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 4:{struct nhcoord*p=at;switch(field){
default:abort();}}
case 5:{struct mkroom*p=at;switch(field){
default:abort();}}
case 6:{struct spell*p=at;switch(field){
default:abort();}}
case 7:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->debug);
case 1:return (uint64_t)(uintptr_t)(p->explore);
case 2:return (uint64_t)(uintptr_t)(p->female);
case 3:return (uint64_t)(uintptr_t)(p->friday13);
case 4:return (uint64_t)(uintptr_t)(p->ins_chkpt);
case 5:return (uint64_t)(uintptr_t)(p->moonphase);
default:abort();}}
case 8:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ntrap);
case 1:return (uint64_t)(uintptr_t)(&p->dst);
default:abort();}}
case 9:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wincap2);
case 1:return (uint64_t)(uintptr_t)(p->win_exit_nhwindows);
case 2:return (uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 3:return (uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 4:return (uint64_t)(uintptr_t)(p->win_mark_synch);
case 5:return (uint64_t)(uintptr_t)(p->win_getmsghistory);
default:abort();}}
case 10:{struct dig_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->lastdigtime);
default:abort();}}
case 11:{struct sound_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->sound_exit_nhsound);
default:abort();}}
case 12:{struct oextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oname);
case 1:return (uint64_t)(uintptr_t)(p->omonst);
case 2:return (uint64_t)(uintptr_t)(p->omailcmd);
case 3:return (uint64_t)(uintptr_t)(p->omid);
default:abort();}}
case 13:{struct s_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 14:{struct tin_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->tin);
case 1:return (uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 15:{struct book_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->book);
case 1:return (uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 16:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nobj);
case 1:return (uint64_t)(uintptr_t)(p->cobj);
case 2:return (uint64_t)(uintptr_t)(p->o_id);
case 3:return (uint64_t)(uintptr_t)(p->where);
case 4:return (uint64_t)(uintptr_t)(p->timed);
case 5:return (uint64_t)(uintptr_t)(p->lamplit);
case 6:return (uint64_t)(uintptr_t)(p->corpsenm);
case 7:return (uint64_t)(uintptr_t)(p->owornmask);
case 8:return (uint64_t)(uintptr_t)(p->oextra);
default:abort();}}
case 17:{struct victual_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->piece);
case 1:return (uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 18:{struct dest_area*p=at;switch(field){
default:abort();}}
case 19:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->pmidx);
default:abort();}}
case 20:{struct egd*p=at;switch(field){
default:abort();}}
case 21:{struct polearm_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hitmon);
case 1:return (uint64_t)(uintptr_t)(p->m_id);
default:abort();}}
case 22:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nmon);
case 1:return (uint64_t)(uintptr_t)(p->data);
case 2:return (uint64_t)(uintptr_t)(p->m_id);
case 3:return (uint64_t)(uintptr_t)(p->mnum);
case 4:return (uint64_t)(uintptr_t)(p->ispriest);
case 5:return (uint64_t)(uintptr_t)(p->mtemplit);
case 6:return (uint64_t)(uintptr_t)(p->minvent);
case 7:return (uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 23:{struct epri*p=at;switch(field){
default:abort();}}
case 24:{struct eshk*p=at;switch(field){
default:abort();}}
case 25:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->seer_turn);
case 1:return (uint64_t)(uintptr_t)(&p->digging);
case 2:return (uint64_t)(uintptr_t)(&p->victual);
case 3:return (uint64_t)(uintptr_t)(&p->tin);
case 4:return (uint64_t)(uintptr_t)(&p->spbook);
case 5:return (uint64_t)(uintptr_t)(&p->polearm);
default:abort();}}
case 26:{struct rm*p=at;switch(field){
default:abort();}}
case 27:{struct fruit*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->fid);
case 1:return (uint64_t)(uintptr_t)(p->nextf);
default:abort();}}
case 28:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->billobjs);
default:abort();}}
case 29:{struct emin*p=at;switch(field){
default:abort();}}
case 30:{struct u_realtime*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->realtime);
case 1:return (uint64_t)(uintptr_t)(p->start_timing);
case 2:return (uint64_t)(uintptr_t)(p->finish_time);
default:abort();}}
case 31:{struct edog*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->droptime);
case 1:return (uint64_t)(uintptr_t)(p->hungrytime);
default:abort();}}
case 32:{struct linfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 33:{struct ebones*p=at;switch(field){
default:abort();}}
case 34:{struct mextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mgivenname);
case 1:return (uint64_t)(uintptr_t)(p->egd);
case 2:return (uint64_t)(uintptr_t)(p->epri);
case 3:return (uint64_t)(uintptr_t)(p->eshk);
case 4:return (uint64_t)(uintptr_t)(p->emin);
case 5:return (uint64_t)(uintptr_t)(p->edog);
case 6:return (uint64_t)(uintptr_t)(p->ebones);
case 7:return (uint64_t)(uintptr_t)(p->mcorpsenm);
default:abort();}}
case 35:{struct Role*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 36:{struct accessibility_data*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mon_notices_blocked);
default:abort();}}
case 37:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_water_level);
case 1:return (uint64_t)(uintptr_t)(&p->d_air_level);
default:abort();}}
case 38:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->last_msg);
case 1:return (uint64_t)(uintptr_t)(p->purge_monsters);
case 2:return (uint64_t)(uintptr_t)(p->window_inited);
case 3:return (uint64_t)(uintptr_t)(p->wc_tile_file);
case 4:return (uint64_t)(uintptr_t)(p->wc_font_map);
case 5:return (uint64_t)(uintptr_t)(p->wc_font_message);
case 6:return (uint64_t)(uintptr_t)(p->wc_font_status);
case 7:return (uint64_t)(uintptr_t)(p->wc_font_menu);
case 8:return (uint64_t)(uintptr_t)(p->wc_font_text);
case 9:return (uint64_t)(uintptr_t)(p->save_uswallow);
case 10:return (uint64_t)(uintptr_t)(p->save_uinwater);
case 11:return (uint64_t)(uintptr_t)(p->save_uburied);
default:abort();}}
case 39:{struct instance_globals_f*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ftrap);
case 1:return (uint64_t)(uintptr_t)(p->ffruit);
default:abort();}}
case 40:{struct Race*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 41:{struct instance_globals_g*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->gamelog);
default:abort();}}
case 42:{struct instance_globals_h*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->havestate);
default:abort();}}
case 43:{struct Gender*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 44:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 45:{struct instance_globals_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->looseball);
case 1:return (uint64_t)(uintptr_t)(p->loosechain);
default:abort();}}
case 46:{struct Align*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 47:{struct damage*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 48:{struct cemetery*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 49:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->uz);
case 1:return (uint64_t)(uintptr_t)(p->uswallow);
case 2:return (uint64_t)(uintptr_t)(p->uinwater);
case 3:return (uint64_t)(uintptr_t)(p->uinvulnerable);
case 4:return (uint64_t)(uintptr_t)(p->uburied);
case 5:return (uint64_t)(uintptr_t)(&p->ualign);
case 6:return (uint64_t)(uintptr_t)(p->uhp);
case 7:return (uint64_t)(uintptr_t)(p->ustuck);
case 8:return (uint64_t)(uintptr_t)(p->usteed);
case 9:return (uint64_t)(uintptr_t)(p->ustuck_mid);
case 10:return (uint64_t)(uintptr_t)(p->usteed_mid);
default:abort();}}
case 50:{struct gamelog_line*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->text);
case 1:return (uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 51:{struct levelflags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->stasis_until);
default:abort();}}
case 52:{struct instance_globals_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->multi);
case 1:return (uint64_t)(uintptr_t)(p->migrating_objs);
case 2:return (uint64_t)(uintptr_t)(p->mydogs);
case 3:return (uint64_t)(uintptr_t)(p->migrating_mons);
default:abort();}}
case 53:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->locations);
case 1:return (uint64_t)(uintptr_t)(p->objlist);
case 2:return (uint64_t)(uintptr_t)(p->buriedobjlist);
case 3:return (uint64_t)(uintptr_t)(p->monlist);
case 4:return (uint64_t)(uintptr_t)(p->damagelist);
case 5:return (uint64_t)(uintptr_t)(p->bonesinfo);
case 6:return (uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 54:{struct instance_globals_o*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->objs_deleted);
default:abort();}}
case 55:{struct kinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->name);
default:abort();}}
case 56:{struct mvitals*p=at;switch(field){
default:abort();}}
case 57:{struct instance_globals_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->stairs);
case 1:return (uint64_t)(uintptr_t)(&p->SAVEF);
default:abort();}}
case 58:{struct sinfo*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->done_hup);
case 1:return (uint64_t)(uintptr_t)(p->something_worth_saving);
case 2:return (uint64_t)(uintptr_t)(p->saving);
case 3:return (uint64_t)(uintptr_t)(p->restoring);
case 4:return (uint64_t)(uintptr_t)(p->freeingdata);
case 5:return (uint64_t)(uintptr_t)(p->savefile_completed);
default:abort();}}
case 59:{struct instance_globals_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->urole);
case 1:return (uint64_t)(uintptr_t)(&p->urace);
case 2:return (uint64_t)(uintptr_t)(&p->uz_save);
default:abort();}}
case 60:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 61:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
case 1:return (uint64_t)(uintptr_t)(&p->dndest);
case 2:return (uint64_t)(uintptr_t)(p->doors);
case 3:return (uint64_t)(uintptr_t)(p->doors_alloc);
default:abort();}}
case 62:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hackpid);
default:abort();}}
case 63:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->killer);
default:abort();}}
case 64:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->lastseentyp);
case 1:return (uint64_t)(uintptr_t)(&p->level);
case 2:return (uint64_t)(uintptr_t)(&p->level_info);
default:abort();}}
case 65:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
case 1:return (uint64_t)(uintptr_t)(&p->mvitals);
default:abort();}}
case 66:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->nhuuid);
default:abort();}}
case 67:{struct nh_file*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->fd);
case 1:return (uint64_t)(uintptr_t)(p->mode);
case 2:return (uint64_t)(uintptr_t)(p->rcount);
case 3:return (uint64_t)(uintptr_t)(p->wcount);
case 4:return (uint64_t)(uintptr_t)(p->structlevel);
case 5:return (uint64_t)(uintptr_t)(p->fplog);
default:abort();}}
case 68:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->plname);
case 1:return (uint64_t)(uintptr_t)(&p->pl_character);
case 2:return (uint64_t)(uintptr_t)(&p->pl_fruit);
default:abort();}}
case 69:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->quest_status);
default:abort();}}
case 70:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 71:{struct instance_globals_saved_s*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->spl_book);
case 1:return (uint64_t)(uintptr_t)(p->sp_levchn);
default:abort();}}
case 72:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->updest);
default:abort();}}
case 73:{struct instance_globals_saved_w*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->wreserve);
case 1:return (uint64_t)(uintptr_t)(p->wtreserved);
default:abort();}}
default:abort();}}
void teleport_save_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct stairway*p=at;switch(field){
case 0:memmove(&p->tolev, (void*)(uintptr_t)value,sizeof p->tolev);return;
case 1:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 1:{struct q_score*p=at;switch(field){
default:abort();}}
case 2:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:p->type=value;return;
default:abort();}}
case 4:{struct nhcoord*p=at;switch(field){
default:abort();}}
case 5:{struct mkroom*p=at;switch(field){
default:abort();}}
case 6:{struct spell*p=at;switch(field){
default:abort();}}
case 7:{struct flag*p=at;switch(field){
case 0:p->debug=value;return;
case 1:p->explore=value;return;
case 2:p->female=value;return;
case 3:p->friday13=value;return;
case 4:p->ins_chkpt=value;return;
case 5:p->moonphase=value;return;
default:abort();}}
case 8:{struct trap*p=at;switch(field){
case 0:p->ntrap=(void*)(uintptr_t)value;return;
case 1:memmove(&p->dst, (void*)(uintptr_t)value,sizeof p->dst);return;
default:abort();}}
case 9:{struct window_procs*p=at;switch(field){
case 0:p->wincap2=value;return;
case 1:p->win_exit_nhwindows=(__typeof__(p->win_exit_nhwindows))(uintptr_t)value;return;
case 2:p->win_clear_nhwindow=(__typeof__(p->win_clear_nhwindow))(uintptr_t)value;return;
case 3:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))(uintptr_t)value;return;
case 4:p->win_mark_synch=(__typeof__(p->win_mark_synch))(uintptr_t)value;return;
case 5:p->win_getmsghistory=(__typeof__(p->win_getmsghistory))(uintptr_t)value;return;
default:abort();}}
case 10:{struct dig_info*p=at;switch(field){
case 0:p->lastdigtime=value;return;
default:abort();}}
case 11:{struct sound_procs*p=at;switch(field){
case 0:p->sound_exit_nhsound=(__typeof__(p->sound_exit_nhsound))(uintptr_t)value;return;
default:abort();}}
case 12:{struct oextra*p=at;switch(field){
case 0:p->oname=(void*)(uintptr_t)value;return;
case 1:p->omonst=(void*)(uintptr_t)value;return;
case 2:p->omailcmd=(void*)(uintptr_t)value;return;
case 3:p->omid=value;return;
default:abort();}}
case 13:{struct s_level*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 14:{struct tin_info*p=at;switch(field){
case 0:p->tin=(void*)(uintptr_t)value;return;
case 1:p->o_id=value;return;
default:abort();}}
case 15:{struct book_info*p=at;switch(field){
case 0:p->book=(void*)(uintptr_t)value;return;
case 1:p->o_id=value;return;
default:abort();}}
case 16:{struct obj*p=at;switch(field){
case 0:p->nobj=(void*)(uintptr_t)value;return;
case 1:p->cobj=(void*)(uintptr_t)value;return;
case 2:p->o_id=value;return;
case 3:p->where=value;return;
case 4:p->timed=value;return;
case 5:p->lamplit=value;return;
case 6:p->corpsenm=value;return;
case 7:p->owornmask=value;return;
case 8:p->oextra=(void*)(uintptr_t)value;return;
default:abort();}}
case 17:{struct victual_info*p=at;switch(field){
case 0:p->piece=(void*)(uintptr_t)value;return;
case 1:p->o_id=value;return;
default:abort();}}
case 18:{struct dest_area*p=at;switch(field){
default:abort();}}
case 19:{struct permonst*p=at;switch(field){
default:abort();}}
case 20:{struct egd*p=at;switch(field){
default:abort();}}
case 21:{struct polearm_info*p=at;switch(field){
case 0:p->hitmon=(void*)(uintptr_t)value;return;
case 1:p->m_id=value;return;
default:abort();}}
case 22:{struct monst*p=at;switch(field){
case 0:p->nmon=(void*)(uintptr_t)value;return;
case 1:p->data=(void*)(uintptr_t)value;return;
case 2:p->m_id=value;return;
case 3:p->mnum=value;return;
case 4:p->ispriest=value;return;
case 5:p->mtemplit=value;return;
case 6:p->minvent=(void*)(uintptr_t)value;return;
case 7:p->mextra=(void*)(uintptr_t)value;return;
default:abort();}}
case 23:{struct epri*p=at;switch(field){
default:abort();}}
case 24:{struct eshk*p=at;switch(field){
default:abort();}}
case 25:{struct context_info*p=at;switch(field){
case 0:p->seer_turn=value;return;
case 1:memmove(&p->digging, (void*)(uintptr_t)value,sizeof p->digging);return;
case 2:memmove(&p->victual, (void*)(uintptr_t)value,sizeof p->victual);return;
case 3:memmove(&p->tin, (void*)(uintptr_t)value,sizeof p->tin);return;
case 4:memmove(&p->spbook, (void*)(uintptr_t)value,sizeof p->spbook);return;
case 5:memmove(&p->polearm, (void*)(uintptr_t)value,sizeof p->polearm);return;
default:abort();}}
case 26:{struct rm*p=at;switch(field){
default:abort();}}
case 27:{struct fruit*p=at;switch(field){
case 0:p->fid=value;return;
case 1:p->nextf=(void*)(uintptr_t)value;return;
default:abort();}}
case 28:{struct instance_globals_b*p=at;switch(field){
case 0:p->billobjs=(void*)(uintptr_t)value;return;
default:abort();}}
case 29:{struct emin*p=at;switch(field){
default:abort();}}
case 30:{struct u_realtime*p=at;switch(field){
case 0:p->realtime=value;return;
case 1:p->start_timing=value;return;
case 2:p->finish_time=value;return;
default:abort();}}
case 31:{struct edog*p=at;switch(field){
case 0:p->droptime=value;return;
case 1:p->hungrytime=value;return;
default:abort();}}
case 32:{struct linfo*p=at;switch(field){
case 0:p->flags=value;return;
default:abort();}}
case 33:{struct ebones*p=at;switch(field){
default:abort();}}
case 34:{struct mextra*p=at;switch(field){
case 0:p->mgivenname=(void*)(uintptr_t)value;return;
case 1:p->egd=(void*)(uintptr_t)value;return;
case 2:p->epri=(void*)(uintptr_t)value;return;
case 3:p->eshk=(void*)(uintptr_t)value;return;
case 4:p->emin=(void*)(uintptr_t)value;return;
case 5:p->edog=(void*)(uintptr_t)value;return;
case 6:p->ebones=(void*)(uintptr_t)value;return;
case 7:p->mcorpsenm=value;return;
default:abort();}}
case 35:{struct Role*p=at;switch(field){
default:abort();}}
case 36:{struct accessibility_data*p=at;switch(field){
case 0:p->mon_notices_blocked=value;return;
default:abort();}}
case 37:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_water_level, (void*)(uintptr_t)value,sizeof p->d_water_level);return;
case 1:memmove(&p->d_air_level, (void*)(uintptr_t)value,sizeof p->d_air_level);return;
default:abort();}}
case 38:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=value;return;
case 1:p->purge_monsters=value;return;
case 2:p->window_inited=value;return;
case 3:p->wc_tile_file=(void*)(uintptr_t)value;return;
case 4:p->wc_font_map=(void*)(uintptr_t)value;return;
case 5:p->wc_font_message=(void*)(uintptr_t)value;return;
case 6:p->wc_font_status=(void*)(uintptr_t)value;return;
case 7:p->wc_font_menu=(void*)(uintptr_t)value;return;
case 8:p->wc_font_text=(void*)(uintptr_t)value;return;
case 9:p->save_uswallow=value;return;
case 10:p->save_uinwater=value;return;
case 11:p->save_uburied=value;return;
default:abort();}}
case 39:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(void*)(uintptr_t)value;return;
case 1:p->ffruit=(void*)(uintptr_t)value;return;
default:abort();}}
case 40:{struct Race*p=at;switch(field){
default:abort();}}
case 41:{struct instance_globals_g*p=at;switch(field){
case 0:p->gamelog=(void*)(uintptr_t)value;return;
default:abort();}}
case 42:{struct instance_globals_h*p=at;switch(field){
case 0:p->havestate=value;return;
default:abort();}}
case 43:{struct Gender*p=at;switch(field){
default:abort();}}
case 44:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 45:{struct instance_globals_l*p=at;switch(field){
case 0:p->looseball=(void*)(uintptr_t)value;return;
case 1:p->loosechain=(void*)(uintptr_t)value;return;
default:abort();}}
case 46:{struct Align*p=at;switch(field){
default:abort();}}
case 47:{struct damage*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 48:{struct cemetery*p=at;switch(field){
case 0:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 49:{struct you*p=at;switch(field){
case 0:memmove(&p->uz, (void*)(uintptr_t)value,sizeof p->uz);return;
case 1:p->uswallow=value;return;
case 2:p->uinwater=value;return;
case 3:p->uinvulnerable=value;return;
case 4:p->uburied=value;return;
case 5:memmove(&p->ualign, (void*)(uintptr_t)value,sizeof p->ualign);return;
case 6:p->uhp=value;return;
case 7:p->ustuck=(void*)(uintptr_t)value;return;
case 8:p->usteed=(void*)(uintptr_t)value;return;
case 9:p->ustuck_mid=value;return;
case 10:p->usteed_mid=value;return;
default:abort();}}
case 50:{struct gamelog_line*p=at;switch(field){
case 0:p->text=(void*)(uintptr_t)value;return;
case 1:p->next=(void*)(uintptr_t)value;return;
default:abort();}}
case 51:{struct levelflags*p=at;switch(field){
case 0:p->stasis_until=value;return;
default:abort();}}
case 52:{struct instance_globals_m*p=at;switch(field){
case 0:p->multi=value;return;
case 1:p->migrating_objs=(void*)(uintptr_t)value;return;
case 2:p->mydogs=(void*)(uintptr_t)value;return;
case 3:p->migrating_mons=(void*)(uintptr_t)value;return;
default:abort();}}
case 53:{dlevel_t*p=at;switch(field){
case 1:p->objlist=(void*)(uintptr_t)value;return;
case 2:p->buriedobjlist=(void*)(uintptr_t)value;return;
case 3:p->monlist=(void*)(uintptr_t)value;return;
case 4:p->damagelist=(void*)(uintptr_t)value;return;
case 5:p->bonesinfo=(void*)(uintptr_t)value;return;
case 6:memmove(&p->flags, (void*)(uintptr_t)value,sizeof p->flags);return;
default:abort();}}
case 54:{struct instance_globals_o*p=at;switch(field){
case 0:p->objs_deleted=(void*)(uintptr_t)value;return;
default:abort();}}
case 55:{struct kinfo*p=at;switch(field){
default:abort();}}
case 56:{struct mvitals*p=at;switch(field){
default:abort();}}
case 57:{struct instance_globals_s*p=at;switch(field){
case 0:p->stairs=(void*)(uintptr_t)value;return;
default:abort();}}
case 58:{struct sinfo*p=at;switch(field){
case 0:p->done_hup=value;return;
case 1:p->something_worth_saving=value;return;
case 2:p->saving=value;return;
case 3:p->restoring=value;return;
case 4:p->freeingdata=value;return;
case 5:p->savefile_completed=value;return;
default:abort();}}
case 59:{struct instance_globals_u*p=at;switch(field){
case 0:memmove(&p->urole, (void*)(uintptr_t)value,sizeof p->urole);return;
case 1:memmove(&p->urace, (void*)(uintptr_t)value,sizeof p->urace);return;
case 2:memmove(&p->uz_save, (void*)(uintptr_t)value,sizeof p->uz_save);return;
default:abort();}}
case 60:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context, (void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 61:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology, (void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
case 1:memmove(&p->dndest, (void*)(uintptr_t)value,sizeof p->dndest);return;
case 2:p->doors=(void*)(uintptr_t)value;return;
case 3:p->doors_alloc=value;return;
default:abort();}}
case 62:{struct instance_globals_saved_h*p=at;switch(field){
case 0:p->hackpid=value;return;
default:abort();}}
case 63:{struct instance_globals_saved_k*p=at;switch(field){
case 0:memmove(&p->killer, (void*)(uintptr_t)value,sizeof p->killer);return;
default:abort();}}
case 64:{struct instance_globals_saved_l*p=at;switch(field){
case 1:memmove(&p->level, (void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 65:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 66:{struct instance_globals_saved_n*p=at;switch(field){
default:abort();}}
case 67:{struct nh_file*p=at;switch(field){
case 0:p->fd=value;return;
case 1:p->mode=value;return;
case 2:p->rcount=value;return;
case 3:p->wcount=value;return;
case 4:p->structlevel=value;return;
case 5:p->fplog=(void*)(uintptr_t)value;return;
default:abort();}}
case 68:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 69:{struct instance_globals_saved_q*p=at;switch(field){
case 0:memmove(&p->quest_status, (void*)(uintptr_t)value,sizeof p->quest_status);return;
default:abort();}}
case 70:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 71:{struct instance_globals_saved_s*p=at;switch(field){
case 1:p->sp_levchn=(void*)(uintptr_t)value;return;
default:abort();}}
case 72:{struct instance_globals_saved_u*p=at;switch(field){
case 0:memmove(&p->updest, (void*)(uintptr_t)value,sizeof p->updest);return;
default:abort();}}
case 73:{struct instance_globals_saved_w*p=at;switch(field){
case 0:p->wreserve=value;return;
case 1:p->wtreserved=value;return;
default:abort();}}
default:abort();}}
void* teleport_save_address(int kind,void*at,int field){switch(kind){
case 0:{struct stairway*p=at;switch(field){
case 0:return (void*)&p->tolev;
case 1:return (void*)&p->next;
default:abort();}}
case 1:{struct q_score*p=at;switch(field){
default:abort();}}
case 2:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 3:{struct align*p=at;switch(field){
case 0:return (void*)&p->type;
default:abort();}}
case 4:{struct nhcoord*p=at;switch(field){
default:abort();}}
case 5:{struct mkroom*p=at;switch(field){
default:abort();}}
case 6:{struct spell*p=at;switch(field){
default:abort();}}
case 7:{struct flag*p=at;switch(field){
case 0:return (void*)&p->debug;
case 1:return (void*)&p->explore;
case 2:return (void*)&p->female;
case 3:return (void*)&p->friday13;
case 4:return (void*)&p->ins_chkpt;
case 5:return (void*)&p->moonphase;
default:abort();}}
case 8:{struct trap*p=at;switch(field){
case 0:return (void*)&p->ntrap;
case 1:return (void*)&p->dst;
default:abort();}}
case 9:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->wincap2;
case 1:return (void*)&p->win_exit_nhwindows;
case 2:return (void*)&p->win_clear_nhwindow;
case 3:return (void*)&p->win_display_nhwindow;
case 4:return (void*)&p->win_mark_synch;
case 5:return (void*)&p->win_getmsghistory;
default:abort();}}
case 10:{struct dig_info*p=at;switch(field){
case 0:return (void*)&p->lastdigtime;
default:abort();}}
case 11:{struct sound_procs*p=at;switch(field){
case 0:return (void*)&p->sound_exit_nhsound;
default:abort();}}
case 12:{struct oextra*p=at;switch(field){
case 0:return (void*)&p->oname;
case 1:return (void*)&p->omonst;
case 2:return (void*)&p->omailcmd;
case 3:return (void*)&p->omid;
default:abort();}}
case 13:{struct s_level*p=at;switch(field){
case 0:return (void*)&p->next;
default:abort();}}
case 14:{struct tin_info*p=at;switch(field){
case 0:return (void*)&p->tin;
case 1:return (void*)&p->o_id;
default:abort();}}
case 15:{struct book_info*p=at;switch(field){
case 0:return (void*)&p->book;
case 1:return (void*)&p->o_id;
default:abort();}}
case 16:{struct obj*p=at;switch(field){
case 0:return (void*)&p->nobj;
case 1:return (void*)&p->cobj;
case 2:return (void*)&p->o_id;
case 3:return (void*)&p->where;
case 4:return (void*)&p->timed;
case 6:return (void*)&p->corpsenm;
case 7:return (void*)&p->owornmask;
case 8:return (void*)&p->oextra;
default:abort();}}
case 17:{struct victual_info*p=at;switch(field){
case 0:return (void*)&p->piece;
case 1:return (void*)&p->o_id;
default:abort();}}
case 18:{struct dest_area*p=at;switch(field){
default:abort();}}
case 19:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->pmidx;
default:abort();}}
case 20:{struct egd*p=at;switch(field){
default:abort();}}
case 21:{struct polearm_info*p=at;switch(field){
case 0:return (void*)&p->hitmon;
case 1:return (void*)&p->m_id;
default:abort();}}
case 22:{struct monst*p=at;switch(field){
case 0:return (void*)&p->nmon;
case 1:return (void*)&p->data;
case 2:return (void*)&p->m_id;
case 3:return (void*)&p->mnum;
case 6:return (void*)&p->minvent;
case 7:return (void*)&p->mextra;
default:abort();}}
case 23:{struct epri*p=at;switch(field){
default:abort();}}
case 24:{struct eshk*p=at;switch(field){
default:abort();}}
case 25:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->seer_turn;
case 1:return (void*)&p->digging;
case 2:return (void*)&p->victual;
case 3:return (void*)&p->tin;
case 4:return (void*)&p->spbook;
case 5:return (void*)&p->polearm;
default:abort();}}
case 26:{struct rm*p=at;switch(field){
default:abort();}}
case 27:{struct fruit*p=at;switch(field){
case 0:return (void*)&p->fid;
case 1:return (void*)&p->nextf;
default:abort();}}
case 28:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->billobjs;
default:abort();}}
case 29:{struct emin*p=at;switch(field){
default:abort();}}
case 30:{struct u_realtime*p=at;switch(field){
case 0:return (void*)&p->realtime;
case 1:return (void*)&p->start_timing;
case 2:return (void*)&p->finish_time;
default:abort();}}
case 31:{struct edog*p=at;switch(field){
case 0:return (void*)&p->droptime;
case 1:return (void*)&p->hungrytime;
default:abort();}}
case 32:{struct linfo*p=at;switch(field){
case 0:return (void*)&p->flags;
default:abort();}}
case 33:{struct ebones*p=at;switch(field){
default:abort();}}
case 34:{struct mextra*p=at;switch(field){
case 0:return (void*)&p->mgivenname;
case 1:return (void*)&p->egd;
case 2:return (void*)&p->epri;
case 3:return (void*)&p->eshk;
case 4:return (void*)&p->emin;
case 5:return (void*)&p->edog;
case 6:return (void*)&p->ebones;
case 7:return (void*)&p->mcorpsenm;
default:abort();}}
case 35:{struct Role*p=at;switch(field){
case 0:return (void*)&p->filecode;
default:abort();}}
case 36:{struct accessibility_data*p=at;switch(field){
case 0:return (void*)&p->mon_notices_blocked;
default:abort();}}
case 37:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_water_level;
case 1:return (void*)&p->d_air_level;
default:abort();}}
case 38:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->last_msg;
case 1:return (void*)&p->purge_monsters;
case 2:return (void*)&p->window_inited;
case 3:return (void*)&p->wc_tile_file;
case 4:return (void*)&p->wc_font_map;
case 5:return (void*)&p->wc_font_message;
case 6:return (void*)&p->wc_font_status;
case 7:return (void*)&p->wc_font_menu;
case 8:return (void*)&p->wc_font_text;
default:abort();}}
case 39:{struct instance_globals_f*p=at;switch(field){
case 0:return (void*)&p->ftrap;
case 1:return (void*)&p->ffruit;
default:abort();}}
case 40:{struct Race*p=at;switch(field){
case 0:return (void*)&p->filecode;
default:abort();}}
case 41:{struct instance_globals_g*p=at;switch(field){
case 0:return (void*)&p->gamelog;
default:abort();}}
case 42:{struct instance_globals_h*p=at;switch(field){
case 0:return (void*)&p->havestate;
default:abort();}}
case 43:{struct Gender*p=at;switch(field){
case 0:return (void*)&p->filecode;
default:abort();}}
case 44:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 45:{struct instance_globals_l*p=at;switch(field){
case 0:return (void*)&p->looseball;
case 1:return (void*)&p->loosechain;
default:abort();}}
case 46:{struct Align*p=at;switch(field){
case 0:return (void*)&p->filecode;
default:abort();}}
case 47:{struct damage*p=at;switch(field){
case 0:return (void*)&p->next;
default:abort();}}
case 48:{struct cemetery*p=at;switch(field){
case 0:return (void*)&p->next;
default:abort();}}
case 49:{struct you*p=at;switch(field){
case 0:return (void*)&p->uz;
case 5:return (void*)&p->ualign;
case 6:return (void*)&p->uhp;
case 7:return (void*)&p->ustuck;
case 8:return (void*)&p->usteed;
case 9:return (void*)&p->ustuck_mid;
case 10:return (void*)&p->usteed_mid;
default:abort();}}
case 50:{struct gamelog_line*p=at;switch(field){
case 0:return (void*)&p->text;
case 1:return (void*)&p->next;
default:abort();}}
case 51:{struct levelflags*p=at;switch(field){
case 0:return (void*)&p->stasis_until;
default:abort();}}
case 52:{struct instance_globals_m*p=at;switch(field){
case 0:return (void*)&p->multi;
case 1:return (void*)&p->migrating_objs;
case 2:return (void*)&p->mydogs;
case 3:return (void*)&p->migrating_mons;
default:abort();}}
case 53:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->locations;
case 1:return (void*)&p->objlist;
case 2:return (void*)&p->buriedobjlist;
case 3:return (void*)&p->monlist;
case 4:return (void*)&p->damagelist;
case 5:return (void*)&p->bonesinfo;
case 6:return (void*)&p->flags;
default:abort();}}
case 54:{struct instance_globals_o*p=at;switch(field){
case 0:return (void*)&p->objs_deleted;
default:abort();}}
case 55:{struct kinfo*p=at;switch(field){
case 0:return (void*)&p->name;
default:abort();}}
case 56:{struct mvitals*p=at;switch(field){
default:abort();}}
case 57:{struct instance_globals_s*p=at;switch(field){
case 0:return (void*)&p->stairs;
case 1:return (void*)&p->SAVEF;
default:abort();}}
case 58:{struct sinfo*p=at;switch(field){
case 0:return (void*)&p->done_hup;
case 1:return (void*)&p->something_worth_saving;
case 2:return (void*)&p->saving;
case 3:return (void*)&p->restoring;
case 4:return (void*)&p->freeingdata;
case 5:return (void*)&p->savefile_completed;
default:abort();}}
case 59:{struct instance_globals_u*p=at;switch(field){
case 0:return (void*)&p->urole;
case 1:return (void*)&p->urace;
case 2:return (void*)&p->uz_save;
default:abort();}}
case 60:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 61:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
case 1:return (void*)&p->dndest;
case 2:return (void*)&p->doors;
case 3:return (void*)&p->doors_alloc;
default:abort();}}
case 62:{struct instance_globals_saved_h*p=at;switch(field){
case 0:return (void*)&p->hackpid;
default:abort();}}
case 63:{struct instance_globals_saved_k*p=at;switch(field){
case 0:return (void*)&p->killer;
default:abort();}}
case 64:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->lastseentyp;
case 1:return (void*)&p->level;
case 2:return (void*)&p->level_info;
default:abort();}}
case 65:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
case 1:return (void*)&p->mvitals;
default:abort();}}
case 66:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return (void*)&p->nhuuid;
default:abort();}}
case 67:{struct nh_file*p=at;switch(field){
case 0:return (void*)&p->fd;
case 1:return (void*)&p->mode;
case 2:return (void*)&p->rcount;
case 3:return (void*)&p->wcount;
case 4:return (void*)&p->structlevel;
case 5:return (void*)&p->fplog;
default:abort();}}
case 68:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return (void*)&p->plname;
case 1:return (void*)&p->pl_character;
case 2:return (void*)&p->pl_fruit;
default:abort();}}
case 69:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return (void*)&p->quest_status;
default:abort();}}
case 70:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return (void*)&p->rooms;
default:abort();}}
case 71:{struct instance_globals_saved_s*p=at;switch(field){
case 0:return (void*)&p->spl_book;
case 1:return (void*)&p->sp_levchn;
default:abort();}}
case 72:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return (void*)&p->updest;
default:abort();}}
case 73:{struct instance_globals_saved_w*p=at;switch(field){
case 0:return (void*)&p->wreserve;
case 1:return (void*)&p->wtreserved;
default:abort();}}
default:abort();}}
static char save_literals[SAVE_LITERAL_CAPACITY];
char*teleport_save_literal_storage(void){return save_literals;}
size_t teleport_save_literal_capacity(void){return sizeof save_literals;}
uintptr_t teleport_save_sig_ign(void){return (uintptr_t)SIG_IGN;}
void teleport_save_clear(int win){clear_nhwindow(win);}
void teleport_save_display(int win,boolean block){display_nhwindow(win,block);}
void teleport_save_exit(const char*s){exit_nhwindows(s);}
void teleport_save_synch(void){mark_synch();}
char*teleport_save_message(boolean init){return getmsghistory(init);}
char teleport_save_y_n(const char*s){return y_n(s);}
void teleport_save_sound(uintptr_t cb,const char*s){((void(*)(const char*))cb)(s);}
void teleport_save_pline(const char*s){pline("%s",s);}
void teleport_save_pline1(const char*s){pline1(s);}
void teleport_save_there(const char*s){There("%s",s);}
void teleport_save_panic(const char*s){panic("%s",s);}
void teleport_save_impossible(const char*s){impossible("%s",s);}
boolean teleport_save_debug_enabled(void){return debugcore(SAVE_SOURCE_FILE,FALSE);}
void teleport_save_debug_message(const char*s,int n){pline(s,n);}
void teleport_save_format(char*out,const char*fmt,int a,int b){Sprintf(out,fmt,a,b);}
void teleport_save_snprintf(char*out,size_t n,const char*fmt,const char*a,const char*b,const char*c,const char*d,const char*e){nh_snprintf("store_plname_in_file",SAVE_SNPRINTF_LINE,out,n,fmt,a,b,c,d,e);}
unsigned teleport_save_strlen(const char*s,int site){static const char*const names[]={"save_gamelog","save_msghistory"};static const int lines[]={SAVE_STRLEN_LINE0,SAVE_STRLEN_LINE1};if(site<0||site>1)abort();return Strlen_(s,names[site],lines[site]);}
void teleport_save_assert(void){__assert_fail("hero[PL_NSIZ_PLUS - 1 - 1] == \'\\0\'",SAVE_SOURCE_FILE,SAVE_ASSERT_LINE,"store_plname_in_file");}
