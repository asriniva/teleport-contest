/* Typed field/header/dependency ABI only. ALLMAIN source algorithms remain JS. */
#include "../../../scripts/tu-allmain-layout.h"
#include <stdint.h>
_Static_assert(sizeof(gc.command_count)==8,"ALLMAIN gc.command_count width changed");
_Static_assert(((__typeof__(gc.command_count))-1<0)==1,"ALLMAIN gc.command_count signedness changed");
_Static_assert(sizeof(gh.hero_seq)==8,"ALLMAIN gh.hero_seq width changed");
_Static_assert(((__typeof__(gh.hero_seq))-1<0)==1,"ALLMAIN gh.hero_seq signedness changed");
_Static_assert(sizeof(gm.multi)==8,"ALLMAIN gm.multi width changed");
_Static_assert(((__typeof__(gm.multi))-1<0)==1,"ALLMAIN gm.multi signedness changed");
_Static_assert(sizeof(gw.were_changes)==8,"ALLMAIN gw.were_changes width changed");
_Static_assert(((__typeof__(gw.were_changes))-1<0)==1,"ALLMAIN gw.were_changes signedness changed");
_Static_assert(sizeof(iflags.hilite_delta)==8,"ALLMAIN iflags.hilite_delta width changed");
_Static_assert(((__typeof__(iflags.hilite_delta))-1<0)==1,"ALLMAIN iflags.hilite_delta signedness changed");
_Static_assert(sizeof(svc.context.next_attrib_check)==8,"ALLMAIN svc.context.next_attrib_check width changed");
_Static_assert(((__typeof__(svc.context.next_attrib_check))-1<0)==1,"ALLMAIN svc.context.next_attrib_check signedness changed");
_Static_assert(sizeof(svc.context.seer_turn)==8,"ALLMAIN svc.context.seer_turn width changed");
_Static_assert(((__typeof__(svc.context.seer_turn))-1<0)==1,"ALLMAIN svc.context.seer_turn signedness changed");
_Static_assert(sizeof(svc.context.tribute.tributesz)==8,"ALLMAIN svc.context.tribute.tributesz width changed");
_Static_assert(((__typeof__(svc.context.tribute.tributesz))-1<0)==0,"ALLMAIN svc.context.tribute.tributesz signedness changed");
_Static_assert(sizeof(svm.moves)==8,"ALLMAIN svm.moves width changed");
_Static_assert(((__typeof__(svm.moves))-1<0)==1,"ALLMAIN svm.moves signedness changed");
_Static_assert(sizeof(u.usleep)==8,"ALLMAIN u.usleep width changed");
_Static_assert(((__typeof__(u.usleep))-1<0)==1,"ALLMAIN u.usleep signedness changed");
_Static_assert(sizeof(urealtime.realtime)==8,"ALLMAIN urealtime.realtime width changed");
_Static_assert(((__typeof__(urealtime.realtime))-1<0)==1,"ALLMAIN urealtime.realtime signedness changed");
_Static_assert(sizeof(urealtime.start_timing)==8,"ALLMAIN urealtime.start_timing width changed");
_Static_assert(((__typeof__(urealtime.start_timing))-1<0)==1,"ALLMAIN urealtime.start_timing signedness changed");

long teleport_allmain_get(int index){switch(index){
case 0:return (long)a11y.glyph_updates;
case 1:return (long)disp.botl;
case 2:return (long)disp.botlx;
case 3:return (long)disp.time_botl;
case 4:return (long)flags.female;
case 5:return (long)flags.friday13;
case 6:return (long)flags.initgend;
case 7:return (long)flags.legacy;
case 8:return (long)flags.moonphase;
case 9:return (long)flags.pantheon;
case 10:return (long)flags.randomall;
case 11:return (long)flags.runmode;
case 12:return (long)flags.time;
case 13:return (long)flags.verbose;
case 14:return (long)gc.cmd_key;
case 15:return (long)gc.command_count;
case 16:return (long)gd.defer_see_monsters;
case 17:return (long)gh.hero_seq;
case 18:return (long)(intptr_t)gi.invent;
case 19:return (long)(intptr_t)gl.luacore;
case 20:return (long)gm.multi;
case 21:return (long)(intptr_t)go.occtxt;
case 22:return (long)(intptr_t)go.occupation;
case 23:return (long)(intptr_t)gu.urace.adj;
case 24:return (long)gu.urole.allow;
case 25:return (long)(intptr_t)gu.urole.name.f;
case 26:return (long)(intptr_t)gu.urole.name.m;
case 27:return (long)gv.vision_full_recalc;
case 28:return (long)gw.were_changes;
case 29:return (long)iflags.debug_fuzzer;
case 30:return (long)iflags.deferred_X;
case 31:return (long)iflags.fuzzerpending;
case 32:return (long)iflags.hilite_delta;
case 33:return (long)iflags.news;
case 34:return (long)iflags.nofollowers;
case 35:return (long)iflags.pending_customizations;
case 36:return (long)iflags.perm_invent;
case 37:return (long)iflags.sanity_check;
case 38:return (long)iflags.wc_splash_screen;
case 39:return (long)program_state.beyond_savefile_load;
case 40:return (long)program_state.done_hup;
case 41:return (long)program_state.in_moveloop;
case 42:return (long)program_state.something_worth_saving;
case 43:return (long)svc.context.bypasses;
case 44:return (long)svc.context.ident;
case 45:return (long)svc.context.mon_moving;
case 46:return (long)svc.context.move;
case 47:return (long)svc.context.mv;
case 48:return (long)svc.context.next_attrib_check;
case 49:return (long)svc.context.resume_wish;
case 50:return (long)svc.context.rndencode;
case 51:return (long)svc.context.run;
case 52:return (long)svc.context.seer_turn;
case 53:return (long)svc.context.travel;
case 54:return (long)svc.context.tribute.enabled;
case 55:return (long)svc.context.tribute.tributesz;
case 56:return (long)svc.context.warnlevel;
case 57:return (long)svl.level.flags.fumaroles;
case 58:return (long)svl.level.flags.noautosearch;
case 59:return (long)svm.moves;
case 60:return (long)u.mfemale;
case 61:return (long)u.mh;
case 62:return (long)u.mhmax;
case 63:return (long)u.ualign.type;
case 64:return (long)u.ublesscnt;
case 65:return (long)u.uburied;
case 66:return (long)u.udg_cnt;
case 67:return (long)u.uen;
case 68:return (long)u.uenmax;
case 69:return (long)u.uevent.amulet_wish;
case 70:return (long)u.uevent.udemigod;
case 71:return (long)u.uhave.amulet;
case 72:return (long)u.uhp;
case 73:return (long)u.uhpmax;
case 74:return (long)u.uinvulnerable;
case 75:return (long)u.ulevel;
case 76:return (long)u.ulycn;
case 77:return (long)u.umoved;
case 78:return (long)u.umovement;
case 79:return (long)u.uroleplay.pauper;
case 80:return (long)u.uroleplay.reroll;
case 81:return (long)u.usleep;
case 82:return (long)(intptr_t)u.usteed;
case 83:return (long)u.uswallow;
case 84:return (long)u.utotype;
case 85:return (long)u.utrap;
case 86:return (long)u.utraptype;
case 87:return (long)u.ux;
case 88:return (long)u.uy;
case 89:return (long)u.uz.dlevel;
case 90:return (long)u.uz0.dlevel;
case 91:return (long)urealtime.realtime;
case 92:return (long)urealtime.start_timing;
case 93:return (long)gu.urole.mnum;
case 94:return (long)WIN_MESSAGE;
case 95:return (long)WIN_STATUS;
case 96:return (long)WIN_MAP;
case 97:return (long)WIN_INVEN;
}return 0;}
void teleport_allmain_set(int index,long value){switch(index){
case 0:a11y.glyph_updates=value;return;
case 1:disp.botl=value;return;
case 2:disp.botlx=value;return;
case 3:disp.time_botl=value;return;
case 4:flags.female=value;return;
case 5:flags.friday13=value;return;
case 6:flags.initgend=value;return;
case 7:flags.legacy=value;return;
case 8:flags.moonphase=value;return;
case 9:flags.pantheon=value;return;
case 10:flags.randomall=value;return;
case 11:flags.runmode=value;return;
case 12:flags.time=value;return;
case 13:flags.verbose=value;return;
case 14:gc.cmd_key=value;return;
case 15:gc.command_count=value;return;
case 16:gd.defer_see_monsters=value;return;
case 17:gh.hero_seq=value;return;
case 18:gi.invent=(void*)(intptr_t)value;return;
case 19:gl.luacore=(void*)(intptr_t)value;return;
case 20:gm.multi=value;return;
case 21:go.occtxt=(const char*)(intptr_t)value;return;
case 22:go.occupation=(int(*)(void))(intptr_t)value;return;
case 23:gu.urace.adj=(const char*)(intptr_t)value;return;
case 24:gu.urole.allow=value;return;
case 25:gu.urole.name.f=(const char*)(intptr_t)value;return;
case 26:gu.urole.name.m=(const char*)(intptr_t)value;return;
case 27:gv.vision_full_recalc=value;return;
case 28:gw.were_changes=value;return;
case 29:iflags.debug_fuzzer=value;return;
case 30:iflags.deferred_X=value;return;
case 31:iflags.fuzzerpending=value;return;
case 32:iflags.hilite_delta=value;return;
case 33:iflags.news=value;return;
case 34:iflags.nofollowers=value;return;
case 35:iflags.pending_customizations=value;return;
case 36:iflags.perm_invent=value;return;
case 37:iflags.sanity_check=value;return;
case 38:iflags.wc_splash_screen=value;return;
case 39:program_state.beyond_savefile_load=value;return;
case 40:program_state.done_hup=value;return;
case 41:program_state.in_moveloop=value;return;
case 42:program_state.something_worth_saving=value;return;
case 43:svc.context.bypasses=value;return;
case 44:svc.context.ident=value;return;
case 45:svc.context.mon_moving=value;return;
case 46:svc.context.move=value;return;
case 47:svc.context.mv=value;return;
case 48:svc.context.next_attrib_check=value;return;
case 49:svc.context.resume_wish=value;return;
case 50:svc.context.rndencode=value;return;
case 51:svc.context.run=value;return;
case 52:svc.context.seer_turn=value;return;
case 53:svc.context.travel=value;return;
case 54:svc.context.tribute.enabled=value;return;
case 55:svc.context.tribute.tributesz=value;return;
case 56:svc.context.warnlevel=value;return;
case 57:svl.level.flags.fumaroles=value;return;
case 58:svl.level.flags.noautosearch=value;return;
case 59:svm.moves=value;return;
case 60:u.mfemale=value;return;
case 61:u.mh=value;return;
case 62:u.mhmax=value;return;
case 63:u.ualign.type=value;return;
case 64:u.ublesscnt=value;return;
case 65:u.uburied=value;return;
case 66:u.udg_cnt=value;return;
case 67:u.uen=value;return;
case 68:u.uenmax=value;return;
case 69:u.uevent.amulet_wish=value;return;
case 70:u.uevent.udemigod=value;return;
case 71:u.uhave.amulet=value;return;
case 72:u.uhp=value;return;
case 73:u.uhpmax=value;return;
case 74:u.uinvulnerable=value;return;
case 75:u.ulevel=value;return;
case 76:u.ulycn=value;return;
case 77:u.umoved=value;return;
case 78:u.umovement=value;return;
case 79:u.uroleplay.pauper=value;return;
case 80:u.uroleplay.reroll=value;return;
case 81:u.usleep=value;return;
case 82:u.usteed=(void*)(intptr_t)value;return;
case 83:u.uswallow=value;return;
case 84:u.utotype=value;return;
case 85:u.utrap=value;return;
case 86:u.utraptype=value;return;
case 87:u.ux=value;return;
case 88:u.uy=value;return;
case 89:u.uz.dlevel=value;return;
case 90:u.uz0.dlevel=value;return;
case 91:urealtime.realtime=value;return;
case 92:urealtime.start_timing=value;return;
case 93:gu.urole.mnum=value;return;
case 94:WIN_MESSAGE=value;return;
case 95:WIN_STATUS=value;return;
case 96:WIN_MAP=value;return;
case 97:WIN_INVEN=value;return;
}}
void*teleport_allmain_address(int index){switch(index){case 0:return &u.uz;case 1:return &u.uz0;case 2:return &u.ucamefrom;case 3:return &gy.youmonst;case 4:return &stronghold_level;case 5:return &iflags.menu_headings;case 6:return &svp.plname;default:return 0;}}
long teleport_allmain_hero(int index){switch(index){case 0:return !!(Very_fast);case 1:return !!(Fast);case 2:return !!(Glib);case 3:return !!(Upolyd);case 4:return !!(Teleportation);case 5:return !!(Polymorph);case 6:return !!(Unchanging);case 7:return !!(Searching);case 8:return !!(Warning);case 9:return !!(Clairvoyant);case 10:return !!(BClairvoyant);case 11:return !!(Underwater);case 12:return !!(Blind);case 13:return !!(Hallucination);case 14:return !!(Unblind_telepat);case 15:return !!(Warn_of_mon);case 16:return !!(Energy_regeneration);case 17:return !!(EMagical_breathing);case 18:return !!(Breathless);case 19:return !!(Regeneration);case 20:return !!(Half_physical_damage);case 21:return !!(Sleepy);case 22:return !!(wizard);default:return 0;}}
long teleport_allmain_record_get(int kind,int field,void*p){if(kind==0){struct monst*v=p;switch(field){case 0:return(long)(intptr_t)v->nmon;case 1:return(long)(intptr_t)v->data;case 2:return v->movement;}}else{struct permonst*v=p;switch(field){case 0:return v->mmove;case 1:return v->mlet;case 2:return v->geno;}}return 0;}
void teleport_allmain_record_set(int kind,int field,void*p,long value){if(kind==0&&field==2)((struct monst*)p)->movement=value;}
void*teleport_allmain_array_pointer(int kind,int index){switch(kind){case 0:return &mons[index];case 1:return (void*)genders[index].adj;case 2:return (void*)nhcb_name[index];}return 0;}
long teleport_allmain_array_get(int kind,int index){switch(kind){case 0:return svm.mvitals[index].mvflags;case 1:return u.ualignbase[index];case 2:return nhcb_counts[index];}return 0;}
void teleport_allmain_array_set(int kind,int index,long value){switch(kind){case 0:svm.mvitals[index].mvflags=value;break;case 1:u.ualignbase[index]=value;break;}}
struct monst*teleport_allmain_fmon(void){return fmon;}
void*teleport_allmain_dlevel(s_level*p){return &p->dlevel;}
int teleport_allmain_occupation(void*p){return ((int(*)(void))p)();}
void*teleport_allmain_done1(void){return(void*)done1;}
void*teleport_allmain_signal(int n,void*p){return(void*)signal(n,(SIG_RET_TYPE)p);}
long teleport_allmain_from_double(double n){return(long)n;}
int teleport_allmain_level_flag(int kind,d_level*p){switch(kind){case 0:return In_endgame(p);case 1:return Is_airlevel(p);case 2:return Is_waterlevel(p);}return 0;}
int teleport_allmain_windowflag(void){return VIA_WINDOWPORT();}
int teleport_allmain_ismnum(int n){return ismnum(n);}
int teleport_allmain_monat(coordxy x,coordxy y){return MON_AT(x,y);}
struct monst*teleport_allmain_mat(coordxy x,coordxy y){return m_at(x,y);}
void teleport_allmain_notice_off(void){notice_mon_off();}
void teleport_allmain_notice_on(void){notice_mon_on();}
void teleport_allmain_assert(int test){if(!test)nhassert_failed("gc.command_count != 0","allmain.c",529);}
int teleport_allmain_acurr(int a){return ACURR(a);}
const char*teleport_allmain_news(void){return NEWS;}
void teleport_allmain_sound(int a,int b,int c){SoundAchievement(a,b,c);}
void teleport_allmain_rng_caller(int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("allmain.c",line,fn);}
int teleport_allmain_rn2(int n){return(rn2)(n);}
int teleport_allmain_rnd(int n){return(rnd)(n);}
void teleport_allmain_format(char*out,const char*f,const char*a,const char*b){Sprintf(out,f,a,b);}
void teleport_allmain_pline(const char*f,const char*a,const char*b,const char*c){pline(f,a,b,c);}
void teleport_allmain_urgent_pline(const char*f,const char*a,const char*b,const char*c){urgent_pline(f,a,b,c);}
void teleport_allmain_Norep(const char*f,const char*a,const char*b,const char*c){Norep(f,a,b,c);}
void teleport_allmain_You(const char*f,const char*a,const char*b,const char*c){You(f,a,b,c);}
void teleport_allmain_livelog(long flags,const char*f,const char*a,const char*b){livelog_printf(flags,f,a,b);}
double teleport_allmain_dep_difftime(time_t a0,time_t a1){return difftime(a0,a1);}
void teleport_allmain_dep_lua_settop(lua_State * a0,int a1){lua_settop(a0,a1);}
const char * teleport_allmain_dep_lua_pushstring(lua_State * a0,const char * a1){return lua_pushstring(a0,a1);}
int teleport_allmain_dep_lua_getglobal(lua_State * a0,const char * a1){return lua_getglobal(a0,a1);}
char * teleport_allmain_dep_eos(char * a0){return eos(a0);}
boolean teleport_allmain_dep_next_to_u(void){return next_to_u();}
void teleport_allmain_dep_check_leash(coordxy a0,coordxy a1){check_leash(a0,a1);}
void teleport_allmain_dep_init_artifacts(void){init_artifacts();}
void teleport_allmain_dep_mkot_trap_warn(void){mkot_trap_warn();}
void teleport_allmain_dep_change_luck(schar a0){change_luck(a0);}
void teleport_allmain_dep_exerchk(void){exerchk();}
void teleport_allmain_dep_bot(void){bot();}
void teleport_allmain_dep_timebot(void){timebot();}
void teleport_allmain_dep_status_initialize(boolean a0){status_initialize(a0);}
void teleport_allmain_dep_status_eval_next_unhilite(void){status_eval_next_unhilite();}
time_t teleport_allmain_dep_getnow(void){return getnow();}
int teleport_allmain_dep_phase_of_the_moon(void){return phase_of_the_moon();}
boolean teleport_allmain_dep_friday_13th(void){return friday_13th();}
int teleport_allmain_dep_night(void){return night();}
int teleport_allmain_dep_dolookaround(void){return dolookaround();}
void teleport_allmain_dep_cmdq_clear(int a0){cmdq_clear(a0);}
void teleport_allmain_dep_rhack(int a0){rhack(a0);}
int teleport_allmain_dep_enter_explore_mode(void){return enter_explore_mode();}
void teleport_allmain_dep_end_of_input(void){end_of_input();}
boolean teleport_allmain_dep_is_pool(coordxy a0,coordxy a1){return is_pool(a0,a1);}
void teleport_allmain_dep_program_state_init(void){program_state_init();}
void teleport_allmain_dep_decl_globals_init(void){decl_globals_init();}
void teleport_allmain_dep_do_vicinity_map(struct obj * a0){do_vicinity_map(a0);}
void teleport_allmain_dep_warnreveal(void){warnreveal();}
int teleport_allmain_dep_dosearch0(int a0){return dosearch0(a0);}
void teleport_allmain_dep_swallowed(int a0){swallowed(a0);}
void teleport_allmain_dep_under_ground(int a0){under_ground(a0);}
void teleport_allmain_dep_under_water(int a0){under_water(a0);}
void teleport_allmain_dep_see_monsters(void){see_monsters();}
void teleport_allmain_dep_see_objects(void){see_objects();}
void teleport_allmain_dep_see_traps(void){see_traps();}
void teleport_allmain_dep_curs_on_u(void){curs_on_u();}
void teleport_allmain_dep_docrt(void){docrt();}
void teleport_allmain_dep_clear_glyph_buffer(void){clear_glyph_buffer();}
void teleport_allmain_dep_flush_screen(int a0){flush_screen(a0);}
void teleport_allmain_dep_reset_glyphmap(enum glyphmap_change_triggers a0){reset_glyphmap(a0);}
void teleport_allmain_dep_save_currentstate(void){save_currentstate();}
void teleport_allmain_dep_hellish_smoke_mesg(void){hellish_smoke_mesg();}
void teleport_allmain_dep_schedule_goto(d_level * a0,int a1,const char * a2,const char * a3){schedule_goto(a0,a1,a2,a3);}
void teleport_allmain_dep_deferred_goto(void){deferred_goto();}
void teleport_allmain_dep_set_wear(struct obj * a0){set_wear(a0);}
void teleport_allmain_dep_find_ac(void){find_ac();}
void teleport_allmain_dep_glibr(void){glibr();}
struct monst * teleport_allmain_dep_makedog(void){return makedog();}
void teleport_allmain_dep_obj_delivery(boolean a0){obj_delivery(a0);}
void teleport_allmain_dep_init_dungeons(void){init_dungeons();}
s_level * teleport_allmain_dep_find_level(const char * a0){return find_level(a0);}
schar teleport_allmain_dep_depth(d_level * a0){return depth(a0);}
void teleport_allmain_dep_assign_level(d_level * a0,d_level * a1){assign_level(a0,a1);}
void teleport_allmain_dep_print_level_annotation(void){print_level_annotation();}
void teleport_allmain_dep_reset_eat(void){reset_eat();}
void teleport_allmain_dep_gethungry(void){gethungry();}
boolean teleport_allmain_dep_maybe_finished_meal(boolean a0){return maybe_finished_meal(a0);}
void teleport_allmain_dep_done(int a0){done(a0);}
void teleport_allmain_dep_u_wipe_engr(int a0){u_wipe_engr(a0);}
void teleport_allmain_dep_read_engr_at(coordxy a0,coordxy a1){read_engr_at(a0,a1);}
void teleport_allmain_dep_read_wizkit(void){read_wizkit();}
void teleport_allmain_dep_get_nhuuid(void){get_nhuuid();}
void teleport_allmain_dep_maybe_shuffle_customizations(void){maybe_shuffle_customizations();}
void teleport_allmain_dep_notice_all_mons(boolean a0){notice_all_mons(a0);}
void teleport_allmain_dep_domove(void){domove();}
void teleport_allmain_dep_runmode_delay_output(void){runmode_delay_output();}
void teleport_allmain_dep_overexert_hp(void){overexert_hp();}
boolean teleport_allmain_dep_pooleffects(boolean a0){return pooleffects(a0);}
void teleport_allmain_dep_check_special_room(boolean a0){check_special_room(a0);}
void teleport_allmain_dep_lookaround(void){lookaround();}
int teleport_allmain_dep_monster_nearby(void){return monster_nearby();}
void teleport_allmain_dep_end_running(boolean a0){end_running(a0);}
void teleport_allmain_dep_nomul(int a0){nomul(a0);}
void teleport_allmain_dep_unmul(const char * a0){unmul(a0);}
int teleport_allmain_dep_near_capacity(void){return near_capacity();}
const char * teleport_allmain_dep_align_str(aligntyp a0){return align_str(a0);}
void teleport_allmain_dep_update_inventory(void){update_inventory();}
void teleport_allmain_dep_ckmailstatus(void){ckmailstatus();}
struct monst * teleport_allmain_dep_makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){return makemon(a0,a1,a2,a3);}
void teleport_allmain_dep_runtime_info_init(void){runtime_info_init();}
void teleport_allmain_dep_mklev(void){mklev();}
void teleport_allmain_dep_fumaroles(void){fumaroles();}
void teleport_allmain_dep_movebubbles(void){movebubbles();}
void teleport_allmain_dep_clear_splitobjs(void){clear_splitobjs();}
void teleport_allmain_dep_dobjsfree(void){dobjsfree();}
int teleport_allmain_dep_movemon(void){return movemon();}
int teleport_allmain_dep_mcalcmove(struct monst * a0,boolean a1){return mcalcmove(a0,a1);}
void teleport_allmain_dep_mcalcdistress(void){mcalcdistress();}
void teleport_allmain_dep_mnexto(struct monst * a0,unsigned int a1){mnexto(a0,a1);}
void teleport_allmain_dep_see_nearby_monsters(void){see_nearby_monsters();}
void teleport_allmain_dep_m_everyturn_effect(struct monst * a0){m_everyturn_effect(a0);}
void teleport_allmain_dep_monst_globals_init(void){monst_globals_init();}
void teleport_allmain_dep_l_nhcore_init(void){l_nhcore_init();}
void teleport_allmain_dep_l_nhcore_call(int a0){l_nhcore_call(a0);}
int teleport_allmain_dep_nhl_pcall_handle(lua_State * a0,int a1,int a2,const char * a3,NHL_pcall_action a4){return nhl_pcall_handle(a0,a1,a2,a3,a4);}
void teleport_allmain_dep_init_objects(void){init_objects();}
void teleport_allmain_dep_objects_globals_init(void){objects_globals_init();}
boolean teleport_allmain_dep_ask_do_tutorial(void){return ask_do_tutorial();}
void teleport_allmain_dep_reset_justpicked(struct obj * a0){reset_justpicked(a0);}
int teleport_allmain_dep_pickup(int a0){return pickup(a0);}
boolean teleport_allmain_dep_reroll_menu(void){return reroll_menu();}
void teleport_allmain_dep_encumber_msg(void){encumber_msg();}
void teleport_allmain_dep_set_uasmon(void){set_uasmon();}
void teleport_allmain_dep_polyself(int a0){polyself(a0);}
void teleport_allmain_dep_rehumanize(void){rehumanize();}
boolean teleport_allmain_dep_ugenocided(void){return ugenocided();}
const char * teleport_allmain_dep_udeadinside(void){return udeadinside();}
void teleport_allmain_dep_com_pager(const char * a0){com_pager(a0);}
void teleport_allmain_dep_run_regions(void){run_regions();}
boolean teleport_allmain_dep_any_visible_region(void){return any_visible_region();}
void teleport_allmain_dep_crashreport_init(int a0,char ** a1){crashreport_init(a0,a1);}
void teleport_allmain_dep_role_init(void){role_init();}
const char * teleport_allmain_dep_Hello(struct monst * a0){return Hello(a0);}
void teleport_allmain_dep_fix_shop_damage(void){fix_shop_damage();}
void teleport_allmain_dep_dosounds(void){dosounds();}
void teleport_allmain_dep_activate_chosen_soundlib(void){activate_chosen_soundlib();}
void teleport_allmain_dep_age_spells(void){age_spells();}
void teleport_allmain_dep_u_on_upstairs(void){u_on_upstairs();}
void teleport_allmain_dep_sys_early_init(void){sys_early_init();}
void teleport_allmain_dep_tele(void){tele();}
void teleport_allmain_dep_nh_timeout(void){nh_timeout();}
void teleport_allmain_dep_do_storms(void){do_storms();}
void teleport_allmain_dep_initrack(void){initrack();}
void teleport_allmain_dep_settrack(void){settrack();}
void teleport_allmain_dep_sink_into_lava(void){sink_into_lava();}
void teleport_allmain_dep_u_init_misc(void){u_init_misc();}
void teleport_allmain_dep_u_init_inventory_attrs(void){u_init_inventory_attrs();}
void teleport_allmain_dep_u_init_skills_discoveries(void){u_init_skills_discoveries();}
void teleport_allmain_dep_invault(void){invault();}
void teleport_allmain_dep_vision_reset(void){vision_reset();}
void teleport_allmain_dep_vision_recalc(int a0){vision_recalc(a0);}
void teleport_allmain_dep_you_were(void){you_were();}
void teleport_allmain_dep_adjust_menu_promptstyle(winid a0,color_attr * a1){adjust_menu_promptstyle(a0,a1);}
void teleport_allmain_dep_amulet(void){amulet();}
void teleport_allmain_dep_intervene(void){intervene();}
void teleport_allmain_dep_sanity_check(void){sanity_check();}
void teleport_allmain_dep_clear_bypasses(void){clear_bypasses();}
void teleport_allmain_dep_makewish(void){makewish();}
winid teleport_allmain_dep_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_allmain_dep_display_file(const char * a0,boolean a1){display_file(a0,a1);}
void teleport_allmain_dep_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
void teleport_allmain_dep_start_menu(winid a0,unsigned long a1){start_menu(a0,a1);}
void teleport_allmain_dep_end_menu(winid a0,const char * a1){end_menu(a0,a1);}
void teleport_allmain_dep_get_nh_event(void){get_nh_event();}
void teleport_allmain_dep_cliparound(int a0,int a1){cliparound(a0,a1);}
static char teleport_allmain_literals[636];
void*teleport_allmain_literal_storage(void){return teleport_allmain_literals;}
size_t teleport_allmain_literal_capacity(void){return sizeof teleport_allmain_literals;}
