/* DECL actual configured native ABI metadata and scalar error transport. */
#include "hack.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "decl-source-data.h"
extern const char *const nhcb_name[4];
extern int nhcb_counts[4];
extern const struct c_color_names c_color_names;
extern const char * c_obj_colors[16];
extern const struct c_common_strings c_common_strings;
extern const char disclosure_options[7];
extern char emptystr[1];
extern struct flag flags;
extern const char hexdd[33];
extern const schar xdir[10];
extern const schar ydir[10];
extern const schar zdir[10];
extern const schar dirs_ord[8];
extern boolean has_strong_rngseed;
extern struct engr * head_engr;
extern struct instance_flags iflags;
extern struct accessibility_data a11y;
extern const char * materialnm[22];
extern const char quitchars[5];
extern const int shield_static[21];
extern struct you u;
extern time_t ubirthday;
extern struct u_realtime urealtime;
extern struct obj * uwep;
extern struct obj * uarm;
extern struct obj * uswapwep;
extern struct obj * uquiver;
extern struct obj * uarmu;
extern struct obj * uskin;
extern struct obj * uarmc;
extern struct obj * uarmh;
extern struct obj * uarms;
extern struct obj * uarmg;
extern struct obj * uarmf;
extern struct obj * uamul;
extern struct obj * uright;
extern struct obj * uleft;
extern struct obj * ublindf;
extern struct obj * uchain;
extern struct obj * uball;
extern const char vowels[11];
extern winid WIN_MESSAGE;
extern winid WIN_STATUS;
extern winid WIN_MAP;
extern winid WIN_INVEN;
extern const char ynchars[3];
extern const char ynqchars[4];
extern const char ynaqchars[5];
extern const char ynNaqchars[6];
extern const char rightleftchars[3];
extern const char hidespinchars[4];
extern long yn_number;
extern const char * ARGV0;
extern const struct Role teleport_decl_private_urole_init_data;
extern const struct Race teleport_decl_private_urace_init_data;
extern struct display_hints disp;
extern const struct instance_globals_a teleport_decl_private_g_init_a;
extern const struct instance_globals_b teleport_decl_private_g_init_b;
extern const struct instance_globals_c teleport_decl_private_g_init_c;
extern const struct instance_globals_d teleport_decl_private_g_init_d;
extern const struct instance_globals_e teleport_decl_private_g_init_e;
extern const struct instance_globals_f teleport_decl_private_g_init_f;
extern const struct instance_globals_g teleport_decl_private_g_init_g;
extern const struct instance_globals_h teleport_decl_private_g_init_h;
extern const struct instance_globals_i teleport_decl_private_g_init_i;
extern const struct instance_globals_j teleport_decl_private_g_init_j;
extern const struct instance_globals_k teleport_decl_private_g_init_k;
extern const struct instance_globals_l teleport_decl_private_g_init_l;
extern const struct instance_globals_m teleport_decl_private_g_init_m;
extern const struct instance_globals_n teleport_decl_private_g_init_n;
extern const struct instance_globals_o teleport_decl_private_g_init_o;
extern const struct instance_globals_p teleport_decl_private_g_init_p;
extern const struct instance_globals_q teleport_decl_private_g_init_q;
extern const struct instance_globals_r teleport_decl_private_g_init_r;
extern const struct instance_globals_s teleport_decl_private_g_init_s;
extern const struct instance_globals_t teleport_decl_private_g_init_t;
extern const struct instance_globals_u teleport_decl_private_g_init_u;
extern const struct instance_globals_v teleport_decl_private_g_init_v;
extern const struct instance_globals_w teleport_decl_private_g_init_w;
extern const struct instance_globals_x teleport_decl_private_g_init_x;
extern const struct instance_globals_y teleport_decl_private_g_init_y;
extern const struct instance_globals_z teleport_decl_private_g_init_z;
extern const struct instance_globals_saved_b teleport_decl_private_init_svb;
extern const struct instance_globals_saved_c teleport_decl_private_init_svc;
extern const struct instance_globals_saved_d teleport_decl_private_init_svd;
extern const struct instance_globals_saved_e teleport_decl_private_init_sve;
extern const struct instance_globals_saved_h teleport_decl_private_init_svh;
extern const struct instance_globals_saved_i teleport_decl_private_init_svi;
extern const struct instance_globals_saved_k teleport_decl_private_init_svk;
extern const struct instance_globals_saved_l teleport_decl_private_init_svl;
extern const struct instance_globals_saved_m teleport_decl_private_init_svm;
extern const struct instance_globals_saved_n teleport_decl_private_init_svn;
extern const struct instance_globals_saved_o teleport_decl_private_init_svo;
extern const struct instance_globals_saved_p teleport_decl_private_init_svp;
extern const struct instance_globals_saved_q teleport_decl_private_init_svq;
extern const struct instance_globals_saved_r teleport_decl_private_init_svr;
extern const struct instance_globals_saved_s teleport_decl_private_init_svs;
extern const struct instance_globals_saved_t teleport_decl_private_init_svt;
extern const struct instance_globals_saved_u teleport_decl_private_init_svu;
extern const struct instance_globals_saved_x teleport_decl_private_init_svx;
extern const struct instance_globals_saved_w teleport_decl_private_init_svw;
extern const struct instance_globals_saved_y teleport_decl_private_init_svy;
extern const struct sinfo teleport_decl_private_init_program_state;
extern struct instance_globals_a ga;
extern struct instance_globals_b gb;
extern struct instance_globals_c gc;
extern struct instance_globals_d gd;
extern struct instance_globals_e ge;
extern struct instance_globals_f gf;
extern struct instance_globals_g gg;
extern struct instance_globals_h gh;
extern struct instance_globals_i gi;
extern struct instance_globals_j gj;
extern struct instance_globals_k gk;
extern struct instance_globals_l gl;
extern struct instance_globals_m gm;
extern struct instance_globals_n gn;
extern struct instance_globals_o go;
extern struct instance_globals_p gp;
extern struct instance_globals_q gq;
extern struct instance_globals_r gr;
extern struct instance_globals_s gs;
extern struct instance_globals_t gt;
extern struct instance_globals_u gu;
extern struct instance_globals_v gv;
extern struct instance_globals_w gw;
extern struct instance_globals_x gx;
extern struct instance_globals_y gy;
extern struct instance_globals_z gz;
extern struct instance_globals_saved_b svb;
extern struct instance_globals_saved_c svc;
extern struct instance_globals_saved_d svd;
extern struct instance_globals_saved_e sve;
extern struct instance_globals_saved_h svh;
extern struct instance_globals_saved_i svi;
extern struct instance_globals_saved_k svk;
extern struct instance_globals_saved_l svl;
extern struct instance_globals_saved_m svm;
extern struct instance_globals_saved_n svn;
extern struct instance_globals_saved_o svo;
extern struct instance_globals_saved_p svp;
extern struct instance_globals_saved_q svq;
extern struct instance_globals_saved_r svr;
extern struct instance_globals_saved_s svs;
extern struct instance_globals_saved_t svt;
extern struct instance_globals_saved_u svu;
extern struct instance_globals_saved_w svw;
extern struct instance_globals_saved_x svx;
extern struct instance_globals_saved_y svy;
extern struct sinfo program_state;
extern const struct const_globals cg;
extern struct obj hands_obj;
_Static_assert(sizeof(struct Race)==112,"DECL Race size");
_Static_assert(offsetof(struct Race,noun)==0,"DECL Race.noun offset");
_Static_assert(offsetof(struct Race,adj)==8,"DECL Race.adj offset");
_Static_assert(offsetof(struct Race,coll)==16,"DECL Race.coll offset");
_Static_assert(offsetof(struct Race,filecode)==24,"DECL Race.filecode offset");
_Static_assert(offsetof(struct Race,individual)==32,"DECL Race.individual offset");
_Static_assert(offsetof(struct Race,mnum)==48,"DECL Race.mnum offset");
_Static_assert(offsetof(struct Race,mummynum)==50,"DECL Race.mummynum offset");
_Static_assert(offsetof(struct Race,zombienum)==52,"DECL Race.zombienum offset");
_Static_assert(offsetof(struct Race,allow)==54,"DECL Race.allow offset");
_Static_assert(offsetof(struct Race,selfmask)==56,"DECL Race.selfmask offset");
_Static_assert(offsetof(struct Race,lovemask)==58,"DECL Race.lovemask offset");
_Static_assert(offsetof(struct Race,hatemask)==60,"DECL Race.hatemask offset");
_Static_assert(offsetof(struct Race,attrmin)==62,"DECL Race.attrmin offset");
_Static_assert(offsetof(struct Race,attrmax)==74,"DECL Race.attrmax offset");
_Static_assert(offsetof(struct Race,hpadv)==86,"DECL Race.hpadv offset");
_Static_assert(offsetof(struct Race,enadv)==98,"DECL Race.enadv offset");
_Static_assert(sizeof(struct Role)==312,"DECL Role size");
_Static_assert(offsetof(struct Role,name)==0,"DECL Role.name offset");
_Static_assert(offsetof(struct Role,rank)==16,"DECL Role.rank offset");
_Static_assert(offsetof(struct Role,lgod)==160,"DECL Role.lgod offset");
_Static_assert(offsetof(struct Role,ngod)==168,"DECL Role.ngod offset");
_Static_assert(offsetof(struct Role,cgod)==176,"DECL Role.cgod offset");
_Static_assert(offsetof(struct Role,filecode)==184,"DECL Role.filecode offset");
_Static_assert(offsetof(struct Role,homebase)==192,"DECL Role.homebase offset");
_Static_assert(offsetof(struct Role,intermed)==200,"DECL Role.intermed offset");
_Static_assert(offsetof(struct Role,mnum)==208,"DECL Role.mnum offset");
_Static_assert(offsetof(struct Role,petnum)==210,"DECL Role.petnum offset");
_Static_assert(offsetof(struct Role,ldrnum)==212,"DECL Role.ldrnum offset");
_Static_assert(offsetof(struct Role,guardnum)==214,"DECL Role.guardnum offset");
_Static_assert(offsetof(struct Role,neminum)==216,"DECL Role.neminum offset");
_Static_assert(offsetof(struct Role,enemy1num)==218,"DECL Role.enemy1num offset");
_Static_assert(offsetof(struct Role,enemy2num)==220,"DECL Role.enemy2num offset");
_Static_assert(offsetof(struct Role,enemy1sym)==222,"DECL Role.enemy1sym offset");
_Static_assert(offsetof(struct Role,enemy2sym)==223,"DECL Role.enemy2sym offset");
_Static_assert(offsetof(struct Role,questarti)==224,"DECL Role.questarti offset");
_Static_assert(offsetof(struct Role,allow)==226,"DECL Role.allow offset");
_Static_assert(offsetof(struct Role,attrbase)==228,"DECL Role.attrbase offset");
_Static_assert(offsetof(struct Role,attrdist)==240,"DECL Role.attrdist offset");
_Static_assert(offsetof(struct Role,hpadv)==252,"DECL Role.hpadv offset");
_Static_assert(offsetof(struct Role,enadv)==264,"DECL Role.enadv offset");
_Static_assert(offsetof(struct Role,xlev)==276,"DECL Role.xlev offset");
_Static_assert(offsetof(struct Role,initrecord)==278,"DECL Role.initrecord offset");
_Static_assert(offsetof(struct Role,spelbase)==280,"DECL Role.spelbase offset");
_Static_assert(offsetof(struct Role,spelheal)==284,"DECL Role.spelheal offset");
_Static_assert(offsetof(struct Role,spelshld)==288,"DECL Role.spelshld offset");
_Static_assert(offsetof(struct Role,spelarmr)==292,"DECL Role.spelarmr offset");
_Static_assert(offsetof(struct Role,spelstat)==296,"DECL Role.spelstat offset");
_Static_assert(offsetof(struct Role,spelspec)==300,"DECL Role.spelspec offset");
_Static_assert(offsetof(struct Role,spelsbon)==304,"DECL Role.spelsbon offset");
_Static_assert(sizeof(struct RoleAdvance)==12,"DECL RoleAdvance size");
_Static_assert(offsetof(struct RoleAdvance,infix)==0,"DECL RoleAdvance.infix offset");
_Static_assert(offsetof(struct RoleAdvance,inrnd)==2,"DECL RoleAdvance.inrnd offset");
_Static_assert(offsetof(struct RoleAdvance,lofix)==4,"DECL RoleAdvance.lofix offset");
_Static_assert(offsetof(struct RoleAdvance,lornd)==6,"DECL RoleAdvance.lornd offset");
_Static_assert(offsetof(struct RoleAdvance,hifix)==8,"DECL RoleAdvance.hifix offset");
_Static_assert(offsetof(struct RoleAdvance,hirnd)==10,"DECL RoleAdvance.hirnd offset");
_Static_assert(sizeof(struct RoleName)==16,"DECL RoleName size");
_Static_assert(offsetof(struct RoleName,m)==0,"DECL RoleName.m offset");
_Static_assert(offsetof(struct RoleName,f)==8,"DECL RoleName.f offset");
_Static_assert(sizeof(struct accessibility_data)==16,"DECL accessibility_data size");
_Static_assert(offsetof(struct accessibility_data,accessiblemsg)==0,"DECL accessibility_data.accessiblemsg offset");
_Static_assert(offsetof(struct accessibility_data,msg_loc)==2,"DECL accessibility_data.msg_loc offset");
_Static_assert(offsetof(struct accessibility_data,mon_notices)==6,"DECL accessibility_data.mon_notices offset");
_Static_assert(offsetof(struct accessibility_data,mon_notices_blocked)==8,"DECL accessibility_data.mon_notices_blocked offset");
_Static_assert(offsetof(struct accessibility_data,mon_movement)==12,"DECL accessibility_data.mon_movement offset");
_Static_assert(offsetof(struct accessibility_data,glyph_updates)==13,"DECL accessibility_data.glyph_updates offset");
_Static_assert(sizeof(struct achievement_tracking)==20,"DECL achievement_tracking size");
_Static_assert(offsetof(struct achievement_tracking,mines_prize_oid)==0,"DECL achievement_tracking.mines_prize_oid offset");
_Static_assert(offsetof(struct achievement_tracking,soko_prize_oid)==4,"DECL achievement_tracking.soko_prize_oid offset");
_Static_assert(offsetof(struct achievement_tracking,castle_prize_old)==8,"DECL achievement_tracking.castle_prize_old offset");
_Static_assert(offsetof(struct achievement_tracking,mines_prize_otyp)==12,"DECL achievement_tracking.mines_prize_otyp offset");
_Static_assert(offsetof(struct achievement_tracking,soko_prize_otyp)==14,"DECL achievement_tracking.soko_prize_otyp offset");
_Static_assert(offsetof(struct achievement_tracking,castle_prize_otyp)==16,"DECL achievement_tracking.castle_prize_otyp offset");
_Static_assert(offsetof(struct achievement_tracking,minetn_reached)==18,"DECL achievement_tracking.minetn_reached offset");
_Static_assert(sizeof(struct align)==12,"DECL align size");
_Static_assert(offsetof(struct align,type)==0,"DECL align.type offset");
_Static_assert(offsetof(struct align,record)==4,"DECL align.record offset");
_Static_assert(offsetof(struct align,abuse)==8,"DECL align.abuse offset");
_Static_assert(sizeof(__typeof__(((lev_region*)0)->inarea))==8,"DECL anonymous_880_5 size");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->inarea),x1)==0,"DECL anonymous_880_5.x1 offset");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->inarea),y1)==2,"DECL anonymous_880_5.y1 offset");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->inarea),x2)==4,"DECL anonymous_880_5.x2 offset");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->inarea),y2)==6,"DECL anonymous_880_5.y2 offset");
_Static_assert(sizeof(__typeof__(((lev_region*)0)->delarea))==8,"DECL anonymous_883_5 size");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->delarea),x1)==0,"DECL anonymous_883_5.x1 offset");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->delarea),y1)==2,"DECL anonymous_883_5.y1 offset");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->delarea),x2)==4,"DECL anonymous_883_5.x2 offset");
_Static_assert(offsetof(__typeof__(((lev_region*)0)->delarea),y2)==6,"DECL anonymous_883_5.y2 offset");
_Static_assert(sizeof(union any)==8,"DECL any size");
_Static_assert(offsetof(union any,a_void)==0,"DECL any.a_void offset");
_Static_assert(offsetof(union any,a_obj)==0,"DECL any.a_obj offset");
_Static_assert(offsetof(union any,a_monst)==0,"DECL any.a_monst offset");
_Static_assert(offsetof(union any,a_int)==0,"DECL any.a_int offset");
_Static_assert(offsetof(union any,a_xint16)==0,"DECL any.a_xint16 offset");
_Static_assert(offsetof(union any,a_xint8)==0,"DECL any.a_xint8 offset");
_Static_assert(offsetof(union any,a_char)==0,"DECL any.a_char offset");
_Static_assert(offsetof(union any,a_schar)==0,"DECL any.a_schar offset");
_Static_assert(offsetof(union any,a_uchar)==0,"DECL any.a_uchar offset");
_Static_assert(offsetof(union any,a_uint)==0,"DECL any.a_uint offset");
_Static_assert(offsetof(union any,a_long)==0,"DECL any.a_long offset");
_Static_assert(offsetof(union any,a_ulong)==0,"DECL any.a_ulong offset");
_Static_assert(offsetof(union any,a_coordxy)==0,"DECL any.a_coordxy offset");
_Static_assert(offsetof(union any,a_iptr)==0,"DECL any.a_iptr offset");
_Static_assert(offsetof(union any,a_xint16ptr)==0,"DECL any.a_xint16ptr offset");
_Static_assert(offsetof(union any,a_xint8ptr)==0,"DECL any.a_xint8ptr offset");
_Static_assert(offsetof(union any,a_lptr)==0,"DECL any.a_lptr offset");
_Static_assert(offsetof(union any,a_coordxyptr)==0,"DECL any.a_coordxyptr offset");
_Static_assert(offsetof(union any,a_ulptr)==0,"DECL any.a_ulptr offset");
_Static_assert(offsetof(union any,a_uptr)==0,"DECL any.a_uptr offset");
_Static_assert(offsetof(union any,a_string)==0,"DECL any.a_string offset");
_Static_assert(offsetof(union any,a_nfunc)==0,"DECL any.a_nfunc offset");
_Static_assert(offsetof(union any,a_mask32)==0,"DECL any.a_mask32 offset");
_Static_assert(offsetof(union any,a_int64)==0,"DECL any.a_int64 offset");
_Static_assert(offsetof(union any,a_uint64)==0,"DECL any.a_uint64 offset");
_Static_assert(sizeof(struct attribs)==6,"DECL attribs size");
_Static_assert(offsetof(struct attribs,a)==0,"DECL attribs.a offset");
_Static_assert(sizeof(struct book_info)==16,"DECL book_info size");
_Static_assert(offsetof(struct book_info,book)==0,"DECL book_info.book offset");
_Static_assert(offsetof(struct book_info,o_id)==8,"DECL book_info.o_id offset");
_Static_assert(offsetof(struct book_info,delay)==12,"DECL book_info.delay offset");
_Static_assert(sizeof(struct c_color_names)==88,"DECL c_color_names size");
_Static_assert(offsetof(struct c_color_names,c_black)==0,"DECL c_color_names.c_black offset");
_Static_assert(offsetof(struct c_color_names,c_amber)==8,"DECL c_color_names.c_amber offset");
_Static_assert(offsetof(struct c_color_names,c_golden)==16,"DECL c_color_names.c_golden offset");
_Static_assert(offsetof(struct c_color_names,c_light_blue)==24,"DECL c_color_names.c_light_blue offset");
_Static_assert(offsetof(struct c_color_names,c_red)==32,"DECL c_color_names.c_red offset");
_Static_assert(offsetof(struct c_color_names,c_green)==40,"DECL c_color_names.c_green offset");
_Static_assert(offsetof(struct c_color_names,c_silver)==48,"DECL c_color_names.c_silver offset");
_Static_assert(offsetof(struct c_color_names,c_blue)==56,"DECL c_color_names.c_blue offset");
_Static_assert(offsetof(struct c_color_names,c_purple)==64,"DECL c_color_names.c_purple offset");
_Static_assert(offsetof(struct c_color_names,c_white)==72,"DECL c_color_names.c_white offset");
_Static_assert(offsetof(struct c_color_names,c_orange)==80,"DECL c_color_names.c_orange offset");
_Static_assert(sizeof(struct c_common_strings)==112,"DECL c_common_strings size");
_Static_assert(offsetof(struct c_common_strings,c_nothing_happens)==0,"DECL c_common_strings.c_nothing_happens offset");
_Static_assert(offsetof(struct c_common_strings,c_nothing_seems_to_happen)==8,"DECL c_common_strings.c_nothing_seems_to_happen offset");
_Static_assert(offsetof(struct c_common_strings,c_thats_enough_tries)==16,"DECL c_common_strings.c_thats_enough_tries offset");
_Static_assert(offsetof(struct c_common_strings,c_silly_thing_to)==24,"DECL c_common_strings.c_silly_thing_to offset");
_Static_assert(offsetof(struct c_common_strings,c_shudder_for_moment)==32,"DECL c_common_strings.c_shudder_for_moment offset");
_Static_assert(offsetof(struct c_common_strings,c_something)==40,"DECL c_common_strings.c_something offset");
_Static_assert(offsetof(struct c_common_strings,c_Something)==48,"DECL c_common_strings.c_Something offset");
_Static_assert(offsetof(struct c_common_strings,c_You_can_move_again)==56,"DECL c_common_strings.c_You_can_move_again offset");
_Static_assert(offsetof(struct c_common_strings,c_Never_mind)==64,"DECL c_common_strings.c_Never_mind offset");
_Static_assert(offsetof(struct c_common_strings,c_vision_clears)==72,"DECL c_common_strings.c_vision_clears offset");
_Static_assert(offsetof(struct c_common_strings,c_the_your)==80,"DECL c_common_strings.c_the_your offset");
_Static_assert(offsetof(struct c_common_strings,c_fakename)==96,"DECL c_common_strings.c_fakename offset");
_Static_assert(sizeof(struct classic_representation)==8,"DECL classic_representation size");
_Static_assert(offsetof(struct classic_representation,color)==0,"DECL classic_representation.color offset");
_Static_assert(offsetof(struct classic_representation,symidx)==4,"DECL classic_representation.symidx offset");
_Static_assert(sizeof(struct cmd)==80,"DECL cmd size");
_Static_assert(offsetof(struct cmd,serialno)==0,"DECL cmd.serialno offset");
_Static_assert(offsetof(struct cmd,num_pad)==4,"DECL cmd.num_pad offset");
_Static_assert(offsetof(struct cmd,pcHack_compat)==5,"DECL cmd.pcHack_compat offset");
_Static_assert(offsetof(struct cmd,phone_layout)==6,"DECL cmd.phone_layout offset");
_Static_assert(offsetof(struct cmd,swap_yz)==7,"DECL cmd.swap_yz offset");
_Static_assert(offsetof(struct cmd,dirchars)==8,"DECL cmd.dirchars offset");
_Static_assert(offsetof(struct cmd,alphadirchars)==16,"DECL cmd.alphadirchars offset");
_Static_assert(offsetof(struct cmd,cmdbinds)==24,"DECL cmd.cmdbinds offset");
_Static_assert(offsetof(struct cmd,mousebtn)==32,"DECL cmd.mousebtn offset");
_Static_assert(offsetof(struct cmd,spkeys)==48,"DECL cmd.spkeys offset");
_Static_assert(offsetof(struct cmd,extcmd_char)==77,"DECL cmd.extcmd_char offset");
_Static_assert(sizeof(struct color_and_attr)==8,"DECL color_and_attr size");
_Static_assert(offsetof(struct color_and_attr,color)==0,"DECL color_and_attr.color offset");
_Static_assert(offsetof(struct color_and_attr,attr)==4,"DECL color_and_attr.attr offset");
_Static_assert(sizeof(struct const_globals)==320,"DECL const_globals size");
_Static_assert(offsetof(struct const_globals,zeroobj)==0,"DECL const_globals.zeroobj offset");
_Static_assert(offsetof(struct const_globals,zeromonst)==112,"DECL const_globals.zeromonst offset");
_Static_assert(offsetof(struct const_globals,zeroany)==304,"DECL const_globals.zeroany offset");
_Static_assert(offsetof(struct const_globals,zeroNhRect)==312,"DECL const_globals.zeroNhRect offset");
_Static_assert(sizeof(struct context_info)==704,"DECL context_info size");
_Static_assert(offsetof(struct context_info,ident)==0,"DECL context_info.ident offset");
_Static_assert(offsetof(struct context_info,no_of_wizards)==4,"DECL context_info.no_of_wizards offset");
_Static_assert(offsetof(struct context_info,run)==8,"DECL context_info.run offset");
_Static_assert(offsetof(struct context_info,startingpet_mid)==12,"DECL context_info.startingpet_mid offset");
_Static_assert(offsetof(struct context_info,current_fruit)==16,"DECL context_info.current_fruit offset");
_Static_assert(offsetof(struct context_info,mysteryforce)==20,"DECL context_info.mysteryforce offset");
_Static_assert(offsetof(struct context_info,rndencode)==24,"DECL context_info.rndencode offset");
_Static_assert(offsetof(struct context_info,startingpet_typ)==28,"DECL context_info.startingpet_typ offset");
_Static_assert(offsetof(struct context_info,warnlevel)==32,"DECL context_info.warnlevel offset");
_Static_assert(offsetof(struct context_info,next_attrib_check)==40,"DECL context_info.next_attrib_check offset");
_Static_assert(offsetof(struct context_info,seer_turn)==48,"DECL context_info.seer_turn offset");
_Static_assert(offsetof(struct context_info,snickersnee_turn)==56,"DECL context_info.snickersnee_turn offset");
_Static_assert(offsetof(struct context_info,stethoscope_seq)==64,"DECL context_info.stethoscope_seq offset");
_Static_assert(offsetof(struct context_info,travel)==72,"DECL context_info.travel offset");
_Static_assert(offsetof(struct context_info,travel1)==73,"DECL context_info.travel1 offset");
_Static_assert(offsetof(struct context_info,forcefight)==74,"DECL context_info.forcefight offset");
_Static_assert(offsetof(struct context_info,nopick)==75,"DECL context_info.nopick offset");
_Static_assert(offsetof(struct context_info,made_amulet)==76,"DECL context_info.made_amulet offset");
_Static_assert(offsetof(struct context_info,mon_moving)==77,"DECL context_info.mon_moving offset");
_Static_assert(offsetof(struct context_info,move)==78,"DECL context_info.move offset");
_Static_assert(offsetof(struct context_info,mv)==79,"DECL context_info.mv offset");
_Static_assert(offsetof(struct context_info,bypasses)==80,"DECL context_info.bypasses offset");
_Static_assert(offsetof(struct context_info,door_opened)==81,"DECL context_info.door_opened offset");
_Static_assert(offsetof(struct context_info,resume_wish)==82,"DECL context_info.resume_wish offset");
_Static_assert(offsetof(struct context_info,tips)==88,"DECL context_info.tips offset");
_Static_assert(offsetof(struct context_info,digging)==96,"DECL context_info.digging offset");
_Static_assert(offsetof(struct context_info,victual)==128,"DECL context_info.victual offset");
_Static_assert(offsetof(struct context_info,engraving)==160,"DECL context_info.engraving offset");
_Static_assert(offsetof(struct context_info,tin)==448,"DECL context_info.tin offset");
_Static_assert(offsetof(struct context_info,spbook)==472,"DECL context_info.spbook offset");
_Static_assert(offsetof(struct context_info,takeoff)==488,"DECL context_info.takeoff offset");
_Static_assert(offsetof(struct context_info,warntype)==544,"DECL context_info.warntype offset");
_Static_assert(offsetof(struct context_info,polearm)==576,"DECL context_info.polearm offset");
_Static_assert(offsetof(struct context_info,objsplit)==592,"DECL context_info.objsplit offset");
_Static_assert(offsetof(struct context_info,tribute)==600,"DECL context_info.tribute offset");
_Static_assert(offsetof(struct context_info,novel)==616,"DECL context_info.novel offset");
_Static_assert(offsetof(struct context_info,achieveo)==656,"DECL context_info.achieveo offset");
_Static_assert(offsetof(struct context_info,lifelist)==680,"DECL context_info.lifelist offset");
_Static_assert(offsetof(struct context_info,jingle)==696,"DECL context_info.jingle offset");
_Static_assert(sizeof(struct d_flags)==4,"DECL d_flags size");
_Static_assert(sizeof(struct d_level)==4,"DECL d_level size");
_Static_assert(offsetof(struct d_level,dnum)==0,"DECL d_level.dnum offset");
_Static_assert(offsetof(struct d_level,dlevel)==2,"DECL d_level.dlevel offset");
_Static_assert(sizeof(struct debug_flags)==2,"DECL debug_flags size");
_Static_assert(offsetof(struct debug_flags,test)==0,"DECL debug_flags.test offset");
_Static_assert(offsetof(struct debug_flags,ttystatus)==1,"DECL debug_flags.ttystatus offset");
_Static_assert(sizeof(struct dest_area)==16,"DECL dest_area size");
_Static_assert(offsetof(struct dest_area,lx)==0,"DECL dest_area.lx offset");
_Static_assert(offsetof(struct dest_area,ly)==2,"DECL dest_area.ly offset");
_Static_assert(offsetof(struct dest_area,hx)==4,"DECL dest_area.hx offset");
_Static_assert(offsetof(struct dest_area,hy)==6,"DECL dest_area.hy offset");
_Static_assert(offsetof(struct dest_area,nlx)==8,"DECL dest_area.nlx offset");
_Static_assert(offsetof(struct dest_area,nly)==10,"DECL dest_area.nly offset");
_Static_assert(offsetof(struct dest_area,nhx)==12,"DECL dest_area.nhx offset");
_Static_assert(offsetof(struct dest_area,nhy)==14,"DECL dest_area.nhy offset");
_Static_assert(sizeof(struct dgn_topology)==114,"DECL dgn_topology size");
_Static_assert(offsetof(struct dgn_topology,d_oracle_level)==0,"DECL dgn_topology.d_oracle_level offset");
_Static_assert(offsetof(struct dgn_topology,d_bigroom_level)==4,"DECL dgn_topology.d_bigroom_level offset");
_Static_assert(offsetof(struct dgn_topology,d_rogue_level)==8,"DECL dgn_topology.d_rogue_level offset");
_Static_assert(offsetof(struct dgn_topology,d_medusa_level)==12,"DECL dgn_topology.d_medusa_level offset");
_Static_assert(offsetof(struct dgn_topology,d_stronghold_level)==16,"DECL dgn_topology.d_stronghold_level offset");
_Static_assert(offsetof(struct dgn_topology,d_valley_level)==20,"DECL dgn_topology.d_valley_level offset");
_Static_assert(offsetof(struct dgn_topology,d_wiz1_level)==24,"DECL dgn_topology.d_wiz1_level offset");
_Static_assert(offsetof(struct dgn_topology,d_wiz2_level)==28,"DECL dgn_topology.d_wiz2_level offset");
_Static_assert(offsetof(struct dgn_topology,d_wiz3_level)==32,"DECL dgn_topology.d_wiz3_level offset");
_Static_assert(offsetof(struct dgn_topology,d_juiblex_level)==36,"DECL dgn_topology.d_juiblex_level offset");
_Static_assert(offsetof(struct dgn_topology,d_orcus_level)==40,"DECL dgn_topology.d_orcus_level offset");
_Static_assert(offsetof(struct dgn_topology,d_baalzebub_level)==44,"DECL dgn_topology.d_baalzebub_level offset");
_Static_assert(offsetof(struct dgn_topology,d_asmodeus_level)==48,"DECL dgn_topology.d_asmodeus_level offset");
_Static_assert(offsetof(struct dgn_topology,d_portal_level)==52,"DECL dgn_topology.d_portal_level offset");
_Static_assert(offsetof(struct dgn_topology,d_sanctum_level)==56,"DECL dgn_topology.d_sanctum_level offset");
_Static_assert(offsetof(struct dgn_topology,d_earth_level)==60,"DECL dgn_topology.d_earth_level offset");
_Static_assert(offsetof(struct dgn_topology,d_water_level)==64,"DECL dgn_topology.d_water_level offset");
_Static_assert(offsetof(struct dgn_topology,d_fire_level)==68,"DECL dgn_topology.d_fire_level offset");
_Static_assert(offsetof(struct dgn_topology,d_air_level)==72,"DECL dgn_topology.d_air_level offset");
_Static_assert(offsetof(struct dgn_topology,d_astral_level)==76,"DECL dgn_topology.d_astral_level offset");
_Static_assert(offsetof(struct dgn_topology,d_tower_dnum)==80,"DECL dgn_topology.d_tower_dnum offset");
_Static_assert(offsetof(struct dgn_topology,d_sokoban_dnum)==82,"DECL dgn_topology.d_sokoban_dnum offset");
_Static_assert(offsetof(struct dgn_topology,d_mines_dnum)==84,"DECL dgn_topology.d_mines_dnum offset");
_Static_assert(offsetof(struct dgn_topology,d_quest_dnum)==86,"DECL dgn_topology.d_quest_dnum offset");
_Static_assert(offsetof(struct dgn_topology,d_tutorial_dnum)==88,"DECL dgn_topology.d_tutorial_dnum offset");
_Static_assert(offsetof(struct dgn_topology,d_qstart_level)==90,"DECL dgn_topology.d_qstart_level offset");
_Static_assert(offsetof(struct dgn_topology,d_qlocate_level)==94,"DECL dgn_topology.d_qlocate_level offset");
_Static_assert(offsetof(struct dgn_topology,d_nemesis_level)==98,"DECL dgn_topology.d_nemesis_level offset");
_Static_assert(offsetof(struct dgn_topology,d_knox_level)==102,"DECL dgn_topology.d_knox_level offset");
_Static_assert(offsetof(struct dgn_topology,d_mineend_level)==106,"DECL dgn_topology.d_mineend_level offset");
_Static_assert(offsetof(struct dgn_topology,d_sokoend_level)==110,"DECL dgn_topology.d_sokoend_level offset");
_Static_assert(sizeof(struct dig_info)==32,"DECL dig_info size");
_Static_assert(offsetof(struct dig_info,effort)==0,"DECL dig_info.effort offset");
_Static_assert(offsetof(struct dig_info,level)==4,"DECL dig_info.level offset");
_Static_assert(offsetof(struct dig_info,pos)==8,"DECL dig_info.pos offset");
_Static_assert(offsetof(struct dig_info,lastdigtime)==16,"DECL dig_info.lastdigtime offset");
_Static_assert(offsetof(struct dig_info,down)==24,"DECL dig_info.down offset");
_Static_assert(offsetof(struct dig_info,chew)==25,"DECL dig_info.chew offset");
_Static_assert(offsetof(struct dig_info,warned)==26,"DECL dig_info.warned offset");
_Static_assert(offsetof(struct dig_info,quiet)==27,"DECL dig_info.quiet offset");
_Static_assert(sizeof(struct display_hints)==3,"DECL display_hints size");
_Static_assert(offsetof(struct display_hints,botl)==0,"DECL display_hints.botl offset");
_Static_assert(offsetof(struct display_hints,botlx)==1,"DECL display_hints.botlx offset");
_Static_assert(offsetof(struct display_hints,time_botl)==2,"DECL display_hints.time_botl offset");
_Static_assert(sizeof(dlevel_t)==40376,"DECL dlevel_t size");
_Static_assert(offsetof(dlevel_t,locations)==0,"DECL dlevel_t.locations offset");
_Static_assert(offsetof(dlevel_t,objects)==13440,"DECL dlevel_t.objects offset");
_Static_assert(offsetof(dlevel_t,monsters)==26880,"DECL dlevel_t.monsters offset");
_Static_assert(offsetof(dlevel_t,objlist)==40320,"DECL dlevel_t.objlist offset");
_Static_assert(offsetof(dlevel_t,buriedobjlist)==40328,"DECL dlevel_t.buriedobjlist offset");
_Static_assert(offsetof(dlevel_t,monlist)==40336,"DECL dlevel_t.monlist offset");
_Static_assert(offsetof(dlevel_t,damagelist)==40344,"DECL dlevel_t.damagelist offset");
_Static_assert(offsetof(dlevel_t,bonesinfo)==40352,"DECL dlevel_t.bonesinfo offset");
_Static_assert(offsetof(dlevel_t,flags)==40360,"DECL dlevel_t.flags offset");
_Static_assert(sizeof(struct dungeon)==92,"DECL dungeon size");
_Static_assert(offsetof(struct dungeon,dname)==0,"DECL dungeon.dname offset");
_Static_assert(offsetof(struct dungeon,proto)==24,"DECL dungeon.proto offset");
_Static_assert(offsetof(struct dungeon,fill_lvl)==39,"DECL dungeon.fill_lvl offset");
_Static_assert(offsetof(struct dungeon,themerms)==54,"DECL dungeon.themerms offset");
_Static_assert(offsetof(struct dungeon,boneid)==69,"DECL dungeon.boneid offset");
_Static_assert(offsetof(struct dungeon,flags)==72,"DECL dungeon.flags offset");
_Static_assert(offsetof(struct dungeon,entry_lev)==76,"DECL dungeon.entry_lev offset");
_Static_assert(offsetof(struct dungeon,num_dunlevs)==78,"DECL dungeon.num_dunlevs offset");
_Static_assert(offsetof(struct dungeon,dunlev_ureached)==80,"DECL dungeon.dunlev_ureached offset");
_Static_assert(offsetof(struct dungeon,ledger_start)==84,"DECL dungeon.ledger_start offset");
_Static_assert(offsetof(struct dungeon,depth_start)==88,"DECL dungeon.depth_start offset");
_Static_assert(sizeof(struct engrave_info)==288,"DECL engrave_info size");
_Static_assert(offsetof(struct engrave_info,text)==0,"DECL engrave_info.text offset");
_Static_assert(offsetof(struct engrave_info,nextc)==256,"DECL engrave_info.nextc offset");
_Static_assert(offsetof(struct engrave_info,stylus)==264,"DECL engrave_info.stylus offset");
_Static_assert(offsetof(struct engrave_info,type)==272,"DECL engrave_info.type offset");
_Static_assert(offsetof(struct engrave_info,pos)==274,"DECL engrave_info.pos offset");
_Static_assert(offsetof(struct engrave_info,actionct)==280,"DECL engrave_info.actionct offset");
_Static_assert(sizeof(struct entity)==24,"DECL entity size");
_Static_assert(offsetof(struct entity,emon)==0,"DECL entity.emon offset");
_Static_assert(offsetof(struct entity,edata)==8,"DECL entity.edata offset");
_Static_assert(offsetof(struct entity,ex)==16,"DECL entity.ex offset");
_Static_assert(offsetof(struct entity,ey)==20,"DECL entity.ey offset");
_Static_assert(sizeof(struct flag)==208,"DECL flag size");
_Static_assert(offsetof(struct flag,acoustics)==0,"DECL flag.acoustics offset");
_Static_assert(offsetof(struct flag,armorstatus)==1,"DECL flag.armorstatus offset");
_Static_assert(offsetof(struct flag,autodig)==2,"DECL flag.autodig offset");
_Static_assert(offsetof(struct flag,autoquiver)==3,"DECL flag.autoquiver offset");
_Static_assert(offsetof(struct flag,autoopen)==4,"DECL flag.autoopen offset");
_Static_assert(offsetof(struct flag,beginner)==5,"DECL flag.beginner offset");
_Static_assert(offsetof(struct flag,biff)==6,"DECL flag.biff offset");
_Static_assert(offsetof(struct flag,bones)==7,"DECL flag.bones offset");
_Static_assert(offsetof(struct flag,confirm)==8,"DECL flag.confirm offset");
_Static_assert(offsetof(struct flag,dark_room)==9,"DECL flag.dark_room offset");
_Static_assert(offsetof(struct flag,debug)==10,"DECL flag.debug offset");
_Static_assert(offsetof(struct flag,end_own)==11,"DECL flag.end_own offset");
_Static_assert(offsetof(struct flag,explore)==12,"DECL flag.explore offset");
_Static_assert(offsetof(struct flag,female)==13,"DECL flag.female offset");
_Static_assert(offsetof(struct flag,friday13)==14,"DECL flag.friday13 offset");
_Static_assert(offsetof(struct flag,goldX)==15,"DECL flag.goldX offset");
_Static_assert(offsetof(struct flag,help)==16,"DECL flag.help offset");
_Static_assert(offsetof(struct flag,tips)==17,"DECL flag.tips offset");
_Static_assert(offsetof(struct flag,tutorial)==18,"DECL flag.tutorial offset");
_Static_assert(offsetof(struct flag,ignintr)==19,"DECL flag.ignintr offset");
_Static_assert(offsetof(struct flag,implicit_uncursed)==20,"DECL flag.implicit_uncursed offset");
_Static_assert(offsetof(struct flag,ins_chkpt)==21,"DECL flag.ins_chkpt offset");
_Static_assert(offsetof(struct flag,invlet_constant)==22,"DECL flag.invlet_constant offset");
_Static_assert(offsetof(struct flag,legacy)==23,"DECL flag.legacy offset");
_Static_assert(offsetof(struct flag,lit_corridor)==24,"DECL flag.lit_corridor offset");
_Static_assert(offsetof(struct flag,mention_decor)==25,"DECL flag.mention_decor offset");
_Static_assert(offsetof(struct flag,mention_walls)==26,"DECL flag.mention_walls offset");
_Static_assert(offsetof(struct flag,nap)==27,"DECL flag.nap offset");
_Static_assert(offsetof(struct flag,nopick_dropped)==28,"DECL flag.nopick_dropped offset");
_Static_assert(offsetof(struct flag,null)==29,"DECL flag.null offset");
_Static_assert(offsetof(struct flag,pickup)==30,"DECL flag.pickup offset");
_Static_assert(offsetof(struct flag,pickup_stolen)==31,"DECL flag.pickup_stolen offset");
_Static_assert(offsetof(struct flag,pickup_thrown)==32,"DECL flag.pickup_thrown offset");
_Static_assert(offsetof(struct flag,pushweapon)==33,"DECL flag.pushweapon offset");
_Static_assert(offsetof(struct flag,quick_farsight)==34,"DECL flag.quick_farsight offset");
_Static_assert(offsetof(struct flag,rest_on_space)==35,"DECL flag.rest_on_space offset");
_Static_assert(offsetof(struct flag,safe_dog)==36,"DECL flag.safe_dog offset");
_Static_assert(offsetof(struct flag,safe_wait)==37,"DECL flag.safe_wait offset");
_Static_assert(offsetof(struct flag,showexp)==38,"DECL flag.showexp offset");
_Static_assert(offsetof(struct flag,showscore)==39,"DECL flag.showscore offset");
_Static_assert(offsetof(struct flag,showvers)==40,"DECL flag.showvers offset");
_Static_assert(offsetof(struct flag,silent)==41,"DECL flag.silent offset");
_Static_assert(offsetof(struct flag,sortpack)==42,"DECL flag.sortpack offset");
_Static_assert(offsetof(struct flag,sparkle)==43,"DECL flag.sparkle offset");
_Static_assert(offsetof(struct flag,standout)==44,"DECL flag.standout offset");
_Static_assert(offsetof(struct flag,terrainstatus)==45,"DECL flag.terrainstatus offset");
_Static_assert(offsetof(struct flag,time)==46,"DECL flag.time offset");
_Static_assert(offsetof(struct flag,tombstone)==47,"DECL flag.tombstone offset");
_Static_assert(offsetof(struct flag,verbose)==48,"DECL flag.verbose offset");
_Static_assert(offsetof(struct flag,weaponstatus)==49,"DECL flag.weaponstatus offset");
_Static_assert(offsetof(struct flag,end_top)==52,"DECL flag.end_top offset");
_Static_assert(offsetof(struct flag,end_around)==56,"DECL flag.end_around offset");
_Static_assert(offsetof(struct flag,autounlock)==60,"DECL flag.autounlock offset");
_Static_assert(offsetof(struct flag,moonphase)==64,"DECL flag.moonphase offset");
_Static_assert(offsetof(struct flag,suppress_alert)==72,"DECL flag.suppress_alert offset");
_Static_assert(offsetof(struct flag,paranoia_bits)==80,"DECL flag.paranoia_bits offset");
_Static_assert(offsetof(struct flag,versinfo)==84,"DECL flag.versinfo offset");
_Static_assert(offsetof(struct flag,pickup_burden)==88,"DECL flag.pickup_burden offset");
_Static_assert(offsetof(struct flag,pile_limit)==92,"DECL flag.pile_limit offset");
_Static_assert(offsetof(struct flag,discosort)==96,"DECL flag.discosort offset");
_Static_assert(offsetof(struct flag,sortloot)==97,"DECL flag.sortloot offset");
_Static_assert(offsetof(struct flag,vanq_sortmode)==98,"DECL flag.vanq_sortmode offset");
_Static_assert(offsetof(struct flag,inv_order)==99,"DECL flag.inv_order offset");
_Static_assert(offsetof(struct flag,pickup_types)==117,"DECL flag.pickup_types offset");
_Static_assert(offsetof(struct flag,end_disclose)==135,"DECL flag.end_disclose offset");
_Static_assert(offsetof(struct flag,menu_style)==142,"DECL flag.menu_style offset");
_Static_assert(offsetof(struct flag,made_fruit)==143,"DECL flag.made_fruit offset");
_Static_assert(offsetof(struct flag,initrole)==144,"DECL flag.initrole offset");
_Static_assert(offsetof(struct flag,initrace)==148,"DECL flag.initrace offset");
_Static_assert(offsetof(struct flag,initgend)==152,"DECL flag.initgend offset");
_Static_assert(offsetof(struct flag,initalign)==156,"DECL flag.initalign offset");
_Static_assert(offsetof(struct flag,randomall)==160,"DECL flag.randomall offset");
_Static_assert(offsetof(struct flag,pantheon)==164,"DECL flag.pantheon offset");
_Static_assert(offsetof(struct flag,lootabc)==168,"DECL flag.lootabc offset");
_Static_assert(offsetof(struct flag,showrace)==169,"DECL flag.showrace offset");
_Static_assert(offsetof(struct flag,travelcmd)==170,"DECL flag.travelcmd offset");
_Static_assert(offsetof(struct flag,runmode)==172,"DECL flag.runmode offset");
_Static_assert(offsetof(struct flag,reserved1)==176,"DECL flag.reserved1 offset");
_Static_assert(offsetof(struct flag,reserved2)==180,"DECL flag.reserved2 offset");
_Static_assert(offsetof(struct flag,reserved3)==184,"DECL flag.reserved3 offset");
_Static_assert(offsetof(struct flag,reserved4)==188,"DECL flag.reserved4 offset");
_Static_assert(offsetof(struct flag,reserved5)==192,"DECL flag.reserved5 offset");
_Static_assert(offsetof(struct flag,reserved6)==196,"DECL flag.reserved6 offset");
_Static_assert(offsetof(struct flag,reserved7)==200,"DECL flag.reserved7 offset");
_Static_assert(offsetof(struct flag,reserved8)==204,"DECL flag.reserved8 offset");
_Static_assert(sizeof(gbuf_entry)==56,"DECL gbuf_entry size");
_Static_assert(offsetof(gbuf_entry,gnew)==0,"DECL gbuf_entry.gnew offset");
_Static_assert(offsetof(gbuf_entry,glyphinfo)==8,"DECL gbuf_entry.glyphinfo offset");
_Static_assert(sizeof(struct glyph_map_entry)==32,"DECL glyph_map_entry size");
_Static_assert(offsetof(struct glyph_map_entry,glyphflags)==0,"DECL glyph_map_entry.glyphflags offset");
_Static_assert(offsetof(struct glyph_map_entry,sym)==4,"DECL glyph_map_entry.sym offset");
_Static_assert(offsetof(struct glyph_map_entry,customcolor)==12,"DECL glyph_map_entry.customcolor offset");
_Static_assert(offsetof(struct glyph_map_entry,color256idx)==16,"DECL glyph_map_entry.color256idx offset");
_Static_assert(offsetof(struct glyph_map_entry,tileidx)==18,"DECL glyph_map_entry.tileidx offset");
_Static_assert(offsetof(struct glyph_map_entry,u)==24,"DECL glyph_map_entry.u offset");
_Static_assert(sizeof(struct glyphinfo)==48,"DECL glyphinfo size");
_Static_assert(offsetof(struct glyphinfo,glyph)==0,"DECL glyphinfo.glyph offset");
_Static_assert(offsetof(struct glyphinfo,ttychar)==4,"DECL glyphinfo.ttychar offset");
_Static_assert(offsetof(struct glyphinfo,framecolor)==8,"DECL glyphinfo.framecolor offset");
_Static_assert(offsetof(struct glyphinfo,gm)==16,"DECL glyphinfo.gm offset");
_Static_assert(sizeof(struct h2o_ctx)==12,"DECL h2o_ctx size");
_Static_assert(offsetof(struct h2o_ctx,dkn_boom)==0,"DECL h2o_ctx.dkn_boom offset");
_Static_assert(offsetof(struct h2o_ctx,unk_boom)==4,"DECL h2o_ctx.unk_boom offset");
_Static_assert(offsetof(struct h2o_ctx,ctx_valid)==8,"DECL h2o_ctx.ctx_valid offset");
_Static_assert(sizeof(struct instance_flags)==424,"DECL instance_flags size");
_Static_assert(offsetof(struct instance_flags,defer_plname)==0,"DECL instance_flags.defer_plname offset");
_Static_assert(offsetof(struct instance_flags,fuzzerpending)==1,"DECL instance_flags.fuzzerpending offset");
_Static_assert(offsetof(struct instance_flags,herecmd_menu)==2,"DECL instance_flags.herecmd_menu offset");
_Static_assert(offsetof(struct instance_flags,idlecheckpoint)==3,"DECL instance_flags.idlecheckpoint offset");
_Static_assert(offsetof(struct instance_flags,invis_goldsym)==4,"DECL instance_flags.invis_goldsym offset");
_Static_assert(offsetof(struct instance_flags,in_lua)==5,"DECL instance_flags.in_lua offset");
_Static_assert(offsetof(struct instance_flags,lua_testing)==6,"DECL instance_flags.lua_testing offset");
_Static_assert(offsetof(struct instance_flags,term_gone)==7,"DECL instance_flags.term_gone offset");
_Static_assert(offsetof(struct instance_flags,nofollowers)==8,"DECL instance_flags.nofollowers offset");
_Static_assert(offsetof(struct instance_flags,partly_eaten_hack)==9,"DECL instance_flags.partly_eaten_hack offset");
_Static_assert(offsetof(struct instance_flags,query_menu)==10,"DECL instance_flags.query_menu offset");
_Static_assert(offsetof(struct instance_flags,remember_getpos)==11,"DECL instance_flags.remember_getpos offset");
_Static_assert(offsetof(struct instance_flags,sad_feeling)==12,"DECL instance_flags.sad_feeling offset");
_Static_assert(offsetof(struct instance_flags,showdamage)==13,"DECL instance_flags.showdamage offset");
_Static_assert(offsetof(struct instance_flags,pending_customizations)==14,"DECL instance_flags.pending_customizations offset");
_Static_assert(offsetof(struct instance_flags,debug_fuzzer)==15,"DECL instance_flags.debug_fuzzer offset");
_Static_assert(offsetof(struct instance_flags,at_midnight)==16,"DECL instance_flags.at_midnight offset");
_Static_assert(offsetof(struct instance_flags,at_night)==20,"DECL instance_flags.at_night offset");
_Static_assert(offsetof(struct instance_flags,failing_untrap)==24,"DECL instance_flags.failing_untrap offset");
_Static_assert(offsetof(struct instance_flags,getdir_click)==28,"DECL instance_flags.getdir_click offset");
_Static_assert(offsetof(struct instance_flags,getloc_filter)==32,"DECL instance_flags.getloc_filter offset");
_Static_assert(offsetof(struct instance_flags,in_lava_effects)==36,"DECL instance_flags.in_lava_effects offset");
_Static_assert(offsetof(struct instance_flags,last_msg)==40,"DECL instance_flags.last_msg offset");
_Static_assert(offsetof(struct instance_flags,menuobjsyms)==44,"DECL instance_flags.menuobjsyms offset");
_Static_assert(offsetof(struct instance_flags,override_ID)==48,"DECL instance_flags.override_ID offset");
_Static_assert(offsetof(struct instance_flags,parse_config_file_src)==52,"DECL instance_flags.parse_config_file_src offset");
_Static_assert(offsetof(struct instance_flags,purge_monsters)==56,"DECL instance_flags.purge_monsters offset");
_Static_assert(offsetof(struct instance_flags,raw_printed)==60,"DECL instance_flags.raw_printed offset");
_Static_assert(offsetof(struct instance_flags,suppress_price)==64,"DECL instance_flags.suppress_price offset");
_Static_assert(offsetof(struct instance_flags,terrainmode)==68,"DECL instance_flags.terrainmode offset");
_Static_assert(offsetof(struct instance_flags,bgcolors)==72,"DECL instance_flags.bgcolors offset");
_Static_assert(offsetof(struct instance_flags,getloc_moveskip)==73,"DECL instance_flags.getloc_moveskip offset");
_Static_assert(offsetof(struct instance_flags,getloc_travelmode)==74,"DECL instance_flags.getloc_travelmode offset");
_Static_assert(offsetof(struct instance_flags,getloc_usemenu)==75,"DECL instance_flags.getloc_usemenu offset");
_Static_assert(offsetof(struct instance_flags,travelcc)==76,"DECL instance_flags.travelcc offset");
_Static_assert(offsetof(struct instance_flags,trav_debug)==80,"DECL instance_flags.trav_debug offset");
_Static_assert(offsetof(struct instance_flags,window_inited)==81,"DECL instance_flags.window_inited offset");
_Static_assert(offsetof(struct instance_flags,vision_inited)==82,"DECL instance_flags.vision_inited offset");
_Static_assert(offsetof(struct instance_flags,sanity_check)==83,"DECL instance_flags.sanity_check offset");
_Static_assert(offsetof(struct instance_flags,sanity_no_check)==84,"DECL instance_flags.sanity_no_check offset");
_Static_assert(offsetof(struct instance_flags,debug_overwrite_stairs)==85,"DECL instance_flags.debug_overwrite_stairs offset");
_Static_assert(offsetof(struct instance_flags,debug_mongen)==86,"DECL instance_flags.debug_mongen offset");
_Static_assert(offsetof(struct instance_flags,debug_hunger)==87,"DECL instance_flags.debug_hunger offset");
_Static_assert(offsetof(struct instance_flags,debug_prevent_pline)==88,"DECL instance_flags.debug_prevent_pline offset");
_Static_assert(offsetof(struct instance_flags,mon_polycontrol)==89,"DECL instance_flags.mon_polycontrol offset");
_Static_assert(offsetof(struct instance_flags,mon_telecontrol)==90,"DECL instance_flags.mon_telecontrol offset");
_Static_assert(offsetof(struct instance_flags,in_dumplog)==91,"DECL instance_flags.in_dumplog offset");
_Static_assert(offsetof(struct instance_flags,in_parse)==92,"DECL instance_flags.in_parse offset");
_Static_assert(offsetof(struct instance_flags,initoptions_noterminate)==93,"DECL instance_flags.initoptions_noterminate offset");
_Static_assert(offsetof(struct instance_flags,msg_history)==96,"DECL instance_flags.msg_history offset");
_Static_assert(offsetof(struct instance_flags,getpos_coords)==100,"DECL instance_flags.getpos_coords offset");
_Static_assert(offsetof(struct instance_flags,menuinvertmode)==104,"DECL instance_flags.menuinvertmode offset");
_Static_assert(offsetof(struct instance_flags,terrain_typ)==108,"DECL instance_flags.terrain_typ offset");
_Static_assert(offsetof(struct instance_flags,menu_headings)==112,"DECL instance_flags.menu_headings offset");
_Static_assert(offsetof(struct instance_flags,colorcount)==120,"DECL instance_flags.colorcount offset");
_Static_assert(offsetof(struct instance_flags,use_truecolor)==124,"DECL instance_flags.use_truecolor offset");
_Static_assert(offsetof(struct instance_flags,altmeta)==125,"DECL instance_flags.altmeta offset");
_Static_assert(offsetof(struct instance_flags,autodescribe)==126,"DECL instance_flags.autodescribe offset");
_Static_assert(offsetof(struct instance_flags,cbreak)==127,"DECL instance_flags.cbreak offset");
_Static_assert(offsetof(struct instance_flags,deferred_X)==128,"DECL instance_flags.deferred_X offset");
_Static_assert(offsetof(struct instance_flags,defer_decor)==129,"DECL instance_flags.defer_decor offset");
_Static_assert(offsetof(struct instance_flags,echo)==130,"DECL instance_flags.echo offset");
_Static_assert(offsetof(struct instance_flags,force_invmenu)==131,"DECL instance_flags.force_invmenu offset");
_Static_assert(offsetof(struct instance_flags,hilite_pile)==132,"DECL instance_flags.hilite_pile offset");
_Static_assert(offsetof(struct instance_flags,menu_head_objsym)==133,"DECL instance_flags.menu_head_objsym offset");
_Static_assert(offsetof(struct instance_flags,menu_overlay)==134,"DECL instance_flags.menu_overlay offset");
_Static_assert(offsetof(struct instance_flags,menu_requested)==135,"DECL instance_flags.menu_requested offset");
_Static_assert(offsetof(struct instance_flags,menu_tab_sep)==136,"DECL instance_flags.menu_tab_sep offset");
_Static_assert(offsetof(struct instance_flags,news)==137,"DECL instance_flags.news offset");
_Static_assert(offsetof(struct instance_flags,num_pad)==138,"DECL instance_flags.num_pad offset");
_Static_assert(offsetof(struct instance_flags,perm_invent)==139,"DECL instance_flags.perm_invent offset");
_Static_assert(offsetof(struct instance_flags,perm_invent_pending)==140,"DECL instance_flags.perm_invent_pending offset");
_Static_assert(offsetof(struct instance_flags,pricequotes)==141,"DECL instance_flags.pricequotes offset");
_Static_assert(offsetof(struct instance_flags,renameallowed)==142,"DECL instance_flags.renameallowed offset");
_Static_assert(offsetof(struct instance_flags,renameinprogress)==143,"DECL instance_flags.renameinprogress offset");
_Static_assert(offsetof(struct instance_flags,sounds)==144,"DECL instance_flags.sounds offset");
_Static_assert(offsetof(struct instance_flags,status_updates)==145,"DECL instance_flags.status_updates offset");
_Static_assert(offsetof(struct instance_flags,toptenwin)==146,"DECL instance_flags.toptenwin offset");
_Static_assert(offsetof(struct instance_flags,tux_penalty)==147,"DECL instance_flags.tux_penalty offset");
_Static_assert(offsetof(struct instance_flags,use_background_glyph)==148,"DECL instance_flags.use_background_glyph offset");
_Static_assert(offsetof(struct instance_flags,use_menu_color)==149,"DECL instance_flags.use_menu_color offset");
_Static_assert(offsetof(struct instance_flags,use_menu_glyphs)==150,"DECL instance_flags.use_menu_glyphs offset");
_Static_assert(offsetof(struct instance_flags,hilite_delta)==152,"DECL instance_flags.hilite_delta offset");
_Static_assert(offsetof(struct instance_flags,unhilite_deadline)==160,"DECL instance_flags.unhilite_deadline offset");
_Static_assert(offsetof(struct instance_flags,voices)==168,"DECL instance_flags.voices offset");
_Static_assert(offsetof(struct instance_flags,zerocomp)==169,"DECL instance_flags.zerocomp offset");
_Static_assert(offsetof(struct instance_flags,rlecomp)==170,"DECL instance_flags.rlecomp offset");
_Static_assert(offsetof(struct instance_flags,ice_rating)==171,"DECL instance_flags.ice_rating offset");
_Static_assert(offsetof(struct instance_flags,prev_decor)==172,"DECL instance_flags.prev_decor offset");
_Static_assert(offsetof(struct instance_flags,num_pad_mode)==173,"DECL instance_flags.num_pad_mode offset");
_Static_assert(offsetof(struct instance_flags,perminv_mode)==174,"DECL instance_flags.perminv_mode offset");
_Static_assert(offsetof(struct instance_flags,bouldersym)==175,"DECL instance_flags.bouldersym offset");
_Static_assert(offsetof(struct instance_flags,prevmsg_window)==176,"DECL instance_flags.prevmsg_window offset");
_Static_assert(offsetof(struct instance_flags,extmenu)==177,"DECL instance_flags.extmenu offset");
_Static_assert(offsetof(struct instance_flags,cmdassist)==178,"DECL instance_flags.cmdassist offset");
_Static_assert(offsetof(struct instance_flags,fireassist)==179,"DECL instance_flags.fireassist offset");
_Static_assert(offsetof(struct instance_flags,wizweight)==180,"DECL instance_flags.wizweight offset");
_Static_assert(offsetof(struct instance_flags,wizmgender)==181,"DECL instance_flags.wizmgender offset");
_Static_assert(offsetof(struct instance_flags,customcolors)==182,"DECL instance_flags.customcolors offset");
_Static_assert(offsetof(struct instance_flags,customsymbols)==183,"DECL instance_flags.customsymbols offset");
_Static_assert(offsetof(struct instance_flags,wc_color)==184,"DECL instance_flags.wc_color offset");
_Static_assert(offsetof(struct instance_flags,wc_hilite_pet)==185,"DECL instance_flags.wc_hilite_pet offset");
_Static_assert(offsetof(struct instance_flags,wc_ascii_map)==186,"DECL instance_flags.wc_ascii_map offset");
_Static_assert(offsetof(struct instance_flags,wc_tiled_map)==187,"DECL instance_flags.wc_tiled_map offset");
_Static_assert(offsetof(struct instance_flags,wc_preload_tiles)==188,"DECL instance_flags.wc_preload_tiles offset");
_Static_assert(offsetof(struct instance_flags,wc_tile_width)==192,"DECL instance_flags.wc_tile_width offset");
_Static_assert(offsetof(struct instance_flags,wc_tile_height)==196,"DECL instance_flags.wc_tile_height offset");
_Static_assert(offsetof(struct instance_flags,wc_tile_file)==200,"DECL instance_flags.wc_tile_file offset");
_Static_assert(offsetof(struct instance_flags,wc_inverse)==208,"DECL instance_flags.wc_inverse offset");
_Static_assert(offsetof(struct instance_flags,wc_align_status)==212,"DECL instance_flags.wc_align_status offset");
_Static_assert(offsetof(struct instance_flags,wc_align_message)==216,"DECL instance_flags.wc_align_message offset");
_Static_assert(offsetof(struct instance_flags,wc_vary_msgcount)==220,"DECL instance_flags.wc_vary_msgcount offset");
_Static_assert(offsetof(struct instance_flags,wcolors)==224,"DECL instance_flags.wcolors offset");
_Static_assert(offsetof(struct instance_flags,wc_font_map)==288,"DECL instance_flags.wc_font_map offset");
_Static_assert(offsetof(struct instance_flags,wc_font_message)==296,"DECL instance_flags.wc_font_message offset");
_Static_assert(offsetof(struct instance_flags,wc_font_status)==304,"DECL instance_flags.wc_font_status offset");
_Static_assert(offsetof(struct instance_flags,wc_font_menu)==312,"DECL instance_flags.wc_font_menu offset");
_Static_assert(offsetof(struct instance_flags,wc_font_text)==320,"DECL instance_flags.wc_font_text offset");
_Static_assert(offsetof(struct instance_flags,wc_fontsiz_map)==328,"DECL instance_flags.wc_fontsiz_map offset");
_Static_assert(offsetof(struct instance_flags,wc_fontsiz_message)==332,"DECL instance_flags.wc_fontsiz_message offset");
_Static_assert(offsetof(struct instance_flags,wc_fontsiz_status)==336,"DECL instance_flags.wc_fontsiz_status offset");
_Static_assert(offsetof(struct instance_flags,wc_fontsiz_menu)==340,"DECL instance_flags.wc_fontsiz_menu offset");
_Static_assert(offsetof(struct instance_flags,wc_fontsiz_text)==344,"DECL instance_flags.wc_fontsiz_text offset");
_Static_assert(offsetof(struct instance_flags,wc_scroll_amount)==348,"DECL instance_flags.wc_scroll_amount offset");
_Static_assert(offsetof(struct instance_flags,wc_scroll_margin)==352,"DECL instance_flags.wc_scroll_margin offset");
_Static_assert(offsetof(struct instance_flags,wc_map_mode)==356,"DECL instance_flags.wc_map_mode offset");
_Static_assert(offsetof(struct instance_flags,wc_player_selection)==360,"DECL instance_flags.wc_player_selection offset");
_Static_assert(offsetof(struct instance_flags,wc_splash_screen)==364,"DECL instance_flags.wc_splash_screen offset");
_Static_assert(offsetof(struct instance_flags,wc_popup_dialog)==365,"DECL instance_flags.wc_popup_dialog offset");
_Static_assert(offsetof(struct instance_flags,wc_eight_bit_input)==366,"DECL instance_flags.wc_eight_bit_input offset");
_Static_assert(offsetof(struct instance_flags,wc2_fullscreen)==367,"DECL instance_flags.wc2_fullscreen offset");
_Static_assert(offsetof(struct instance_flags,wc2_softkeyboard)==368,"DECL instance_flags.wc2_softkeyboard offset");
_Static_assert(offsetof(struct instance_flags,wc2_wraptext)==369,"DECL instance_flags.wc2_wraptext offset");
_Static_assert(offsetof(struct instance_flags,wc2_selectsaved)==370,"DECL instance_flags.wc2_selectsaved offset");
_Static_assert(offsetof(struct instance_flags,wc2_darkgray)==371,"DECL instance_flags.wc2_darkgray offset");
_Static_assert(offsetof(struct instance_flags,wc2_hitpointbar)==372,"DECL instance_flags.wc2_hitpointbar offset");
_Static_assert(offsetof(struct instance_flags,wc2_guicolor)==373,"DECL instance_flags.wc2_guicolor offset");
_Static_assert(offsetof(struct instance_flags,wc_mouse_support)==376,"DECL instance_flags.wc_mouse_support offset");
_Static_assert(offsetof(struct instance_flags,wc2_term_cols)==380,"DECL instance_flags.wc2_term_cols offset");
_Static_assert(offsetof(struct instance_flags,wc2_term_rows)==384,"DECL instance_flags.wc2_term_rows offset");
_Static_assert(offsetof(struct instance_flags,wc2_statuslines)==388,"DECL instance_flags.wc2_statuslines offset");
_Static_assert(offsetof(struct instance_flags,wc2_windowborders)==392,"DECL instance_flags.wc2_windowborders offset");
_Static_assert(offsetof(struct instance_flags,wc2_petattr)==396,"DECL instance_flags.wc2_petattr offset");
_Static_assert(offsetof(struct instance_flags,debug)==401,"DECL instance_flags.debug offset");
_Static_assert(offsetof(struct instance_flags,windowtype_locked)==403,"DECL instance_flags.windowtype_locked offset");
_Static_assert(offsetof(struct instance_flags,windowtype_deferred)==404,"DECL instance_flags.windowtype_deferred offset");
_Static_assert(offsetof(struct instance_flags,returning_missile)==408,"DECL instance_flags.returning_missile offset");
_Static_assert(offsetof(struct instance_flags,wiz_error_flag)==416,"DECL instance_flags.wiz_error_flag offset");
_Static_assert(offsetof(struct instance_flags,explore_error_flag)==417,"DECL instance_flags.explore_error_flag offset");
_Static_assert(offsetof(struct instance_flags,obsolete)==418,"DECL instance_flags.obsolete offset");
_Static_assert(sizeof(struct instance_globals_a)==280,"DECL instance_globals_a size");
_Static_assert(offsetof(struct instance_globals_a,afternmv)==0,"DECL instance_globals_a.afternmv offset");
_Static_assert(offsetof(struct instance_globals_a,already_found_flag)==8,"DECL instance_globals_a.already_found_flag offset");
_Static_assert(offsetof(struct instance_globals_a,at_ladder)==12,"DECL instance_globals_a.at_ladder offset");
_Static_assert(offsetof(struct instance_globals_a,apelist)==16,"DECL instance_globals_a.apelist offset");
_Static_assert(offsetof(struct instance_globals_a,amulets)==24,"DECL instance_globals_a.amulets offset");
_Static_assert(offsetof(struct instance_globals_a,animal_list)==232,"DECL instance_globals_a.animal_list offset");
_Static_assert(offsetof(struct instance_globals_a,animal_list_count)==240,"DECL instance_globals_a.animal_list_count offset");
_Static_assert(offsetof(struct instance_globals_a,A_first_hint)==244,"DECL instance_globals_a.A_first_hint offset");
_Static_assert(offsetof(struct instance_globals_a,A_second_hint)==248,"DECL instance_globals_a.A_second_hint offset");
_Static_assert(offsetof(struct instance_globals_a,abort_looting)==252,"DECL instance_globals_a.abort_looting offset");
_Static_assert(offsetof(struct instance_globals_a,auto_credit)==253,"DECL instance_globals_a.auto_credit offset");
_Static_assert(offsetof(struct instance_globals_a,active_soundlib)==256,"DECL instance_globals_a.active_soundlib offset");
_Static_assert(offsetof(struct instance_globals_a,acid_ctx)==260,"DECL instance_globals_a.acid_ctx offset");
_Static_assert(offsetof(struct instance_globals_a,havestate)==272,"DECL instance_globals_a.havestate offset");
_Static_assert(sizeof(struct instance_globals_b)==4872,"DECL instance_globals_b size");
_Static_assert(offsetof(struct instance_globals_b,blstats)==0,"DECL instance_globals_b.blstats offset");
_Static_assert(offsetof(struct instance_globals_b,blinit)==4752,"DECL instance_globals_b.blinit offset");
_Static_assert(offsetof(struct instance_globals_b,bl_hilite_moves)==4760,"DECL instance_globals_b.bl_hilite_moves offset");
_Static_assert(offsetof(struct instance_globals_b,bhitpos)==4768,"DECL instance_globals_b.bhitpos offset");
_Static_assert(offsetof(struct instance_globals_b,billobjs)==4776,"DECL instance_globals_b.billobjs offset");
_Static_assert(offsetof(struct instance_globals_b,bones)==4784,"DECL instance_globals_b.bones offset");
_Static_assert(offsetof(struct instance_globals_b,bldrpush_oid)==4800,"DECL instance_globals_b.bldrpush_oid offset");
_Static_assert(offsetof(struct instance_globals_b,bldrpushtime)==4808,"DECL instance_globals_b.bldrpushtime offset");
_Static_assert(offsetof(struct instance_globals_b,bughack)==4816,"DECL instance_globals_b.bughack offset");
_Static_assert(offsetof(struct instance_globals_b,bucx_filter)==4848,"DECL instance_globals_b.bucx_filter offset");
_Static_assert(offsetof(struct instance_globals_b,buzzer)==4856,"DECL instance_globals_b.buzzer offset");
_Static_assert(offsetof(struct instance_globals_b,bot_disabled)==4864,"DECL instance_globals_b.bot_disabled offset");
_Static_assert(offsetof(struct instance_globals_b,havestate)==4865,"DECL instance_globals_b.havestate offset");
_Static_assert(sizeof(struct instance_globals_c)==584,"DECL instance_globals_c size");
_Static_assert(offsetof(struct instance_globals_c,command_queue)==0,"DECL instance_globals_c.command_queue offset");
_Static_assert(offsetof(struct instance_globals_c,cond_hilites)==16,"DECL instance_globals_c.cond_hilites offset");
_Static_assert(offsetof(struct instance_globals_c,condmenu_sortorder)==208,"DECL instance_globals_c.condmenu_sortorder offset");
_Static_assert(offsetof(struct instance_globals_c,Cmd)==216,"DECL instance_globals_c.Cmd offset");
_Static_assert(offsetof(struct instance_globals_c,clicklook_cc)==296,"DECL instance_globals_c.clicklook_cc offset");
_Static_assert(offsetof(struct instance_globals_c,chosen_windowtype)==300,"DECL instance_globals_c.chosen_windowtype offset");
_Static_assert(offsetof(struct instance_globals_c,cmd_key)==316,"DECL instance_globals_c.cmd_key offset");
_Static_assert(offsetof(struct instance_globals_c,cmd_bind)==320,"DECL instance_globals_c.cmd_bind offset");
_Static_assert(offsetof(struct instance_globals_c,command_count)==328,"DECL instance_globals_c.command_count offset");
_Static_assert(offsetof(struct instance_globals_c,current_wand)==336,"DECL instance_globals_c.current_wand offset");
_Static_assert(offsetof(struct instance_globals_c,catname)==344,"DECL instance_globals_c.catname offset");
_Static_assert(offsetof(struct instance_globals_c,crash_email)==408,"DECL instance_globals_c.crash_email offset");
_Static_assert(offsetof(struct instance_globals_c,crash_name)==416,"DECL instance_globals_c.crash_name offset");
_Static_assert(offsetof(struct instance_globals_c,crash_urlmax)==424,"DECL instance_globals_c.crash_urlmax offset");
_Static_assert(offsetof(struct instance_globals_c,currentgraphics)==428,"DECL instance_globals_c.currentgraphics offset");
_Static_assert(offsetof(struct instance_globals_c,cmdline_rcfile)==432,"DECL instance_globals_c.cmdline_rcfile offset");
_Static_assert(offsetof(struct instance_globals_c,config_section_chosen)==440,"DECL instance_globals_c.config_section_chosen offset");
_Static_assert(offsetof(struct instance_globals_c,config_section_current)==448,"DECL instance_globals_c.config_section_current offset");
_Static_assert(offsetof(struct instance_globals_c,chosen_symset_start)==456,"DECL instance_globals_c.chosen_symset_start offset");
_Static_assert(offsetof(struct instance_globals_c,chosen_symset_end)==457,"DECL instance_globals_c.chosen_symset_end offset");
_Static_assert(offsetof(struct instance_globals_c,cached_pickinv_win)==460,"DECL instance_globals_c.cached_pickinv_win offset");
_Static_assert(offsetof(struct instance_globals_c,core_invent_state)==464,"DECL instance_globals_c.core_invent_state offset");
_Static_assert(offsetof(struct instance_globals_c,cmdline_windowsys)==472,"DECL instance_globals_c.cmdline_windowsys offset");
_Static_assert(offsetof(struct instance_globals_c,color_colorings)==480,"DECL instance_globals_c.color_colorings offset");
_Static_assert(offsetof(struct instance_globals_c,current_container)==488,"DECL instance_globals_c.current_container offset");
_Static_assert(offsetof(struct instance_globals_c,class_filter)==496,"DECL instance_globals_c.class_filter offset");
_Static_assert(offsetof(struct instance_globals_c,cvt_buf)==497,"DECL instance_globals_c.cvt_buf offset");
_Static_assert(offsetof(struct instance_globals_c,chosen_soundlib)==564,"DECL instance_globals_c.chosen_soundlib offset");
_Static_assert(offsetof(struct instance_globals_c,coder)==568,"DECL instance_globals_c.coder offset");
_Static_assert(offsetof(struct instance_globals_c,corpsenm_digested)==576,"DECL instance_globals_c.corpsenm_digested offset");
_Static_assert(offsetof(struct instance_globals_c,converted_savefile_loaded)==578,"DECL instance_globals_c.converted_savefile_loaded offset");
_Static_assert(offsetof(struct instance_globals_c,havestate)==579,"DECL instance_globals_c.havestate offset");
_Static_assert(sizeof(struct instance_globals_d)==168,"DECL instance_globals_d size");
_Static_assert(offsetof(struct instance_globals_d,doorindex)==0,"DECL instance_globals_d.doorindex offset");
_Static_assert(offsetof(struct instance_globals_d,done_money)==8,"DECL instance_globals_d.done_money offset");
_Static_assert(offsetof(struct instance_globals_d,domove_attempting)==16,"DECL instance_globals_d.domove_attempting offset");
_Static_assert(offsetof(struct instance_globals_d,domove_succeeded)==24,"DECL instance_globals_d.domove_succeeded offset");
_Static_assert(offsetof(struct instance_globals_d,defer_see_monsters)==32,"DECL instance_globals_d.defer_see_monsters offset");
_Static_assert(offsetof(struct instance_globals_d,did_dig_msg)==33,"DECL instance_globals_d.did_dig_msg offset");
_Static_assert(offsetof(struct instance_globals_d,dfr_pre_msg)==40,"DECL instance_globals_d.dfr_pre_msg offset");
_Static_assert(offsetof(struct instance_globals_d,dfr_post_msg)==48,"DECL instance_globals_d.dfr_post_msg offset");
_Static_assert(offsetof(struct instance_globals_d,did_nothing_flag)==56,"DECL instance_globals_d.did_nothing_flag offset");
_Static_assert(offsetof(struct instance_globals_d,dogname)==60,"DECL instance_globals_d.dogname offset");
_Static_assert(offsetof(struct instance_globals_d,done_seq)==128,"DECL instance_globals_d.done_seq offset");
_Static_assert(offsetof(struct instance_globals_d,disintegested)==136,"DECL instance_globals_d.disintegested offset");
_Static_assert(offsetof(struct instance_globals_d,distantname)==140,"DECL instance_globals_d.distantname offset");
_Static_assert(offsetof(struct instance_globals_d,decor_fumble_override)==144,"DECL instance_globals_d.decor_fumble_override offset");
_Static_assert(offsetof(struct instance_globals_d,decor_levitate_override)==145,"DECL instance_globals_d.decor_levitate_override offset");
_Static_assert(offsetof(struct instance_globals_d,deferred_showpaths)==146,"DECL instance_globals_d.deferred_showpaths offset");
_Static_assert(offsetof(struct instance_globals_d,deferred_showpaths_dir)==152,"DECL instance_globals_d.deferred_showpaths_dir offset");
_Static_assert(offsetof(struct instance_globals_d,havestate)==160,"DECL instance_globals_d.havestate offset");
_Static_assert(sizeof(struct instance_globals_e)==40,"DECL instance_globals_e size");
_Static_assert(offsetof(struct instance_globals_e,en_win)==0,"DECL instance_globals_e.en_win offset");
_Static_assert(offsetof(struct instance_globals_e,en_via_menu)==4,"DECL instance_globals_e.en_via_menu offset");
_Static_assert(offsetof(struct instance_globals_e,ext_tlist)==8,"DECL instance_globals_e.ext_tlist offset");
_Static_assert(offsetof(struct instance_globals_e,eatmbuf)==16,"DECL instance_globals_e.eatmbuf offset");
_Static_assert(offsetof(struct instance_globals_e,ebubbles)==24,"DECL instance_globals_e.ebubbles offset");
_Static_assert(offsetof(struct instance_globals_e,early_raw_messages)==32,"DECL instance_globals_e.early_raw_messages offset");
_Static_assert(offsetof(struct instance_globals_e,havestate)==36,"DECL instance_globals_e.havestate offset");
_Static_assert(sizeof(struct instance_globals_f)==144,"DECL instance_globals_f size");
_Static_assert(offsetof(struct instance_globals_f,ftrap)==0,"DECL instance_globals_f.ftrap offset");
_Static_assert(offsetof(struct instance_globals_f,fqn_prefix)==8,"DECL instance_globals_f.fqn_prefix offset");
_Static_assert(offsetof(struct instance_globals_f,ffruit)==88,"DECL instance_globals_f.ffruit offset");
_Static_assert(offsetof(struct instance_globals_f,force_save_hs)==96,"DECL instance_globals_f.force_save_hs offset");
_Static_assert(offsetof(struct instance_globals_f,far_noise)==97,"DECL instance_globals_f.far_noise offset");
_Static_assert(offsetof(struct instance_globals_f,false_rumor_size)==104,"DECL instance_globals_f.false_rumor_size offset");
_Static_assert(offsetof(struct instance_globals_f,false_rumor_start)==112,"DECL instance_globals_f.false_rumor_start offset");
_Static_assert(offsetof(struct instance_globals_f,false_rumor_end)==120,"DECL instance_globals_f.false_rumor_end offset");
_Static_assert(offsetof(struct instance_globals_f,followmsg)==128,"DECL instance_globals_f.followmsg offset");
_Static_assert(offsetof(struct instance_globals_f,havestate)==136,"DECL instance_globals_f.havestate offset");
_Static_assert(sizeof(struct instance_globals_g)==95000,"DECL instance_globals_g size");
_Static_assert(offsetof(struct instance_globals_g,gbuf)==0,"DECL instance_globals_g.gbuf offset");
_Static_assert(offsetof(struct instance_globals_g,gbuf_start)==94080,"DECL instance_globals_g.gbuf_start offset");
_Static_assert(offsetof(struct instance_globals_g,gbuf_stop)==94122,"DECL instance_globals_g.gbuf_stop offset");
_Static_assert(offsetof(struct instance_globals_g,getposx)==94164,"DECL instance_globals_g.getposx offset");
_Static_assert(offsetof(struct instance_globals_g,getposy)==94166,"DECL instance_globals_g.getposy offset");
_Static_assert(offsetof(struct instance_globals_g,gloc_filter_map)==94168,"DECL instance_globals_g.gloc_filter_map offset");
_Static_assert(offsetof(struct instance_globals_g,gloc_filter_floodfill_match_glyph)==94176,"DECL instance_globals_g.gloc_filter_floodfill_match_glyph offset");
_Static_assert(offsetof(struct instance_globals_g,gtyp)==94180,"DECL instance_globals_g.gtyp offset");
_Static_assert(offsetof(struct instance_globals_g,gx)==94182,"DECL instance_globals_g.gx offset");
_Static_assert(offsetof(struct instance_globals_g,gy)==94184,"DECL instance_globals_g.gy offset");
_Static_assert(offsetof(struct instance_globals_g,gate_str)==94192,"DECL instance_globals_g.gate_str offset");
_Static_assert(offsetof(struct instance_globals_g,gems)==94200,"DECL instance_globals_g.gems offset");
_Static_assert(offsetof(struct instance_globals_g,glyph_reset_timestamp)==94568,"DECL instance_globals_g.glyph_reset_timestamp offset");
_Static_assert(offsetof(struct instance_globals_g,gmst_stored)==94576,"DECL instance_globals_g.gmst_stored offset");
_Static_assert(offsetof(struct instance_globals_g,gmst_moves)==94584,"DECL instance_globals_g.gmst_moves offset");
_Static_assert(offsetof(struct instance_globals_g,gmst_invent)==94592,"DECL instance_globals_g.gmst_invent offset");
_Static_assert(offsetof(struct instance_globals_g,gmst_ubak)==94600,"DECL instance_globals_g.gmst_ubak offset");
_Static_assert(offsetof(struct instance_globals_g,gmst_disco)==94608,"DECL instance_globals_g.gmst_disco offset");
_Static_assert(offsetof(struct instance_globals_g,gmst_mvitals)==94616,"DECL instance_globals_g.gmst_mvitals offset");
_Static_assert(offsetof(struct instance_globals_g,gmst_spl_book)==94624,"DECL instance_globals_g.gmst_spl_book offset");
_Static_assert(offsetof(struct instance_globals_g,gamelog)==94968,"DECL instance_globals_g.gamelog offset");
_Static_assert(offsetof(struct instance_globals_g,gas_cloud_diss_within)==94976,"DECL instance_globals_g.gas_cloud_diss_within offset");
_Static_assert(offsetof(struct instance_globals_g,gas_cloud_diss_seen)==94980,"DECL instance_globals_g.gas_cloud_diss_seen offset");
_Static_assert(offsetof(struct instance_globals_g,glyphmap_perlevel_flags)==94984,"DECL instance_globals_g.glyphmap_perlevel_flags offset");
_Static_assert(offsetof(struct instance_globals_g,havestate)==94992,"DECL instance_globals_g.havestate offset");
_Static_assert(sizeof(struct instance_globals_h)==104,"DECL instance_globals_h size");
_Static_assert(offsetof(struct instance_globals_h,hname)==0,"DECL instance_globals_h.hname offset");
_Static_assert(offsetof(struct instance_globals_h,hero_seq)==8,"DECL instance_globals_h.hero_seq offset");
_Static_assert(offsetof(struct instance_globals_h,horsename)==16,"DECL instance_globals_h.horsename offset");
_Static_assert(offsetof(struct instance_globals_h,hitmsg_mid)==80,"DECL instance_globals_h.hitmsg_mid offset");
_Static_assert(offsetof(struct instance_globals_h,hitmsg_prev)==88,"DECL instance_globals_h.hitmsg_prev offset");
_Static_assert(offsetof(struct instance_globals_h,havestate)==96,"DECL instance_globals_h.havestate offset");
_Static_assert(sizeof(struct instance_globals_i)==72,"DECL instance_globals_i size");
_Static_assert(offsetof(struct instance_globals_i,in_doagain)==0,"DECL instance_globals_i.in_doagain offset");
_Static_assert(offsetof(struct instance_globals_i,in_mklev)==4,"DECL instance_globals_i.in_mklev offset");
_Static_assert(offsetof(struct instance_globals_i,in_steed_dismounting)==5,"DECL instance_globals_i.in_steed_dismounting offset");
_Static_assert(offsetof(struct instance_globals_i,invent)==8,"DECL instance_globals_i.invent offset");
_Static_assert(offsetof(struct instance_globals_i,initial_don)==16,"DECL instance_globals_i.initial_don offset");
_Static_assert(offsetof(struct instance_globals_i,invbuf)==24,"DECL instance_globals_i.invbuf offset");
_Static_assert(offsetof(struct instance_globals_i,invbufsiz)==32,"DECL instance_globals_i.invbufsiz offset");
_Static_assert(offsetof(struct instance_globals_i,item_action_in_progress)==36,"DECL instance_globals_i.item_action_in_progress offset");
_Static_assert(offsetof(struct instance_globals_i,in_sync_perminvent)==40,"DECL instance_globals_i.in_sync_perminvent offset");
_Static_assert(offsetof(struct instance_globals_i,itermonarr)==48,"DECL instance_globals_i.itermonarr offset");
_Static_assert(offsetof(struct instance_globals_i,id_map)==56,"DECL instance_globals_i.id_map offset");
_Static_assert(offsetof(struct instance_globals_i,in_mk_themerooms)==64,"DECL instance_globals_i.in_mk_themerooms offset");
_Static_assert(offsetof(struct instance_globals_i,havestate)==65,"DECL instance_globals_i.havestate offset");
_Static_assert(sizeof(struct instance_globals_j)==8,"DECL instance_globals_j size");
_Static_assert(offsetof(struct instance_globals_j,jumping_is_magic)==0,"DECL instance_globals_j.jumping_is_magic offset");
_Static_assert(offsetof(struct instance_globals_j,havestate)==4,"DECL instance_globals_j.havestate offset");
_Static_assert(sizeof(struct instance_globals_k)==24,"DECL instance_globals_k size");
_Static_assert(offsetof(struct instance_globals_k,kickedloc)==0,"DECL instance_globals_k.kickedloc offset");
_Static_assert(offsetof(struct instance_globals_k,kickedobj)==8,"DECL instance_globals_k.kickedobj offset");
_Static_assert(offsetof(struct instance_globals_k,known)==16,"DECL instance_globals_k.known offset");
_Static_assert(offsetof(struct instance_globals_k,havestate)==17,"DECL instance_globals_k.havestate offset");
_Static_assert(sizeof(struct instance_globals_l)==696,"DECL instance_globals_l size");
_Static_assert(offsetof(struct instance_globals_l,last_command_count)==0,"DECL instance_globals_l.last_command_count offset");
_Static_assert(offsetof(struct instance_globals_l,locknum)==8,"DECL instance_globals_l.locknum offset");
_Static_assert(offsetof(struct instance_globals_l,lockptr)==12,"DECL instance_globals_l.lockptr offset");
_Static_assert(offsetof(struct instance_globals_l,lock)==16,"DECL instance_globals_l.lock offset");
_Static_assert(offsetof(struct instance_globals_l,lastinvnr)==64,"DECL instance_globals_l.lastinvnr offset");
_Static_assert(offsetof(struct instance_globals_l,light_base)==72,"DECL instance_globals_l.light_base offset");
_Static_assert(offsetof(struct instance_globals_l,luathemes)==80,"DECL instance_globals_l.luathemes offset");
_Static_assert(offsetof(struct instance_globals_l,last_hider)==208,"DECL instance_globals_l.last_hider offset");
_Static_assert(offsetof(struct instance_globals_l,luacore)==216,"DECL instance_globals_l.luacore offset");
_Static_assert(offsetof(struct instance_globals_l,lua_warnbuf)==224,"DECL instance_globals_l.lua_warnbuf offset");
_Static_assert(offsetof(struct instance_globals_l,loglua)==480,"DECL instance_globals_l.loglua offset");
_Static_assert(offsetof(struct instance_globals_l,lua_sid)==484,"DECL instance_globals_l.lua_sid offset");
_Static_assert(offsetof(struct instance_globals_l,loot_reset_justpicked)==488,"DECL instance_globals_l.loot_reset_justpicked offset");
_Static_assert(offsetof(struct instance_globals_l,looseball)==496,"DECL instance_globals_l.looseball offset");
_Static_assert(offsetof(struct instance_globals_l,loosechain)==504,"DECL instance_globals_l.loosechain offset");
_Static_assert(offsetof(struct instance_globals_l,lev_message)==512,"DECL instance_globals_l.lev_message offset");
_Static_assert(offsetof(struct instance_globals_l,lregions)==520,"DECL instance_globals_l.lregions offset");
_Static_assert(offsetof(struct instance_globals_l,launchplace)==528,"DECL instance_globals_l.launchplace offset");
_Static_assert(offsetof(struct instance_globals_l,last_winchoice)==544,"DECL instance_globals_l.last_winchoice offset");
_Static_assert(offsetof(struct instance_globals_l,lua_ver)==552,"DECL instance_globals_l.lua_ver offset");
_Static_assert(offsetof(struct instance_globals_l,lua_copyright)==572,"DECL instance_globals_l.lua_copyright offset");
_Static_assert(offsetof(struct instance_globals_l,havestate)==692,"DECL instance_globals_l.havestate offset");
_Static_assert(sizeof(struct instance_globals_m)==384,"DECL instance_globals_m size");
_Static_assert(offsetof(struct instance_globals_m,mkot_trap_warn_count)==0,"DECL instance_globals_m.mkot_trap_warn_count offset");
_Static_assert(offsetof(struct instance_globals_m,mrank_sz)==4,"DECL instance_globals_m.mrank_sz offset");
_Static_assert(offsetof(struct instance_globals_m,multi)==8,"DECL instance_globals_m.multi offset");
_Static_assert(offsetof(struct instance_globals_m,multi_reason)==16,"DECL instance_globals_m.multi_reason offset");
_Static_assert(offsetof(struct instance_globals_m,multireasonbuf)==24,"DECL instance_globals_m.multireasonbuf offset");
_Static_assert(offsetof(struct instance_globals_m,m_shot)==152,"DECL instance_globals_m.m_shot offset");
_Static_assert(offsetof(struct instance_globals_m,mrg_to_wielded)==164,"DECL instance_globals_m.mrg_to_wielded offset");
_Static_assert(offsetof(struct instance_globals_m,menu_colorings)==168,"DECL instance_globals_m.menu_colorings offset");
_Static_assert(offsetof(struct instance_globals_m,migrating_objs)==176,"DECL instance_globals_m.migrating_objs offset");
_Static_assert(offsetof(struct instance_globals_m,mydogs)==184,"DECL instance_globals_m.mydogs offset");
_Static_assert(offsetof(struct instance_globals_m,migrating_mons)==192,"DECL instance_globals_m.migrating_mons offset");
_Static_assert(offsetof(struct instance_globals_m,maploc)==200,"DECL instance_globals_m.maploc offset");
_Static_assert(offsetof(struct instance_globals_m,mswallower)==208,"DECL instance_globals_m.mswallower offset");
_Static_assert(offsetof(struct instance_globals_m,mhitu_dieroll)==216,"DECL instance_globals_m.mhitu_dieroll offset");
_Static_assert(offsetof(struct instance_globals_m,made_branch)==220,"DECL instance_globals_m.made_branch offset");
_Static_assert(offsetof(struct instance_globals_m,min_rx)==222,"DECL instance_globals_m.min_rx offset");
_Static_assert(offsetof(struct instance_globals_m,max_rx)==224,"DECL instance_globals_m.max_rx offset");
_Static_assert(offsetof(struct instance_globals_m,min_ry)==226,"DECL instance_globals_m.min_ry offset");
_Static_assert(offsetof(struct instance_globals_m,max_ry)==228,"DECL instance_globals_m.max_ry offset");
_Static_assert(offsetof(struct instance_globals_m,mkcorpstat_norevive)==230,"DECL instance_globals_m.mkcorpstat_norevive offset");
_Static_assert(offsetof(struct instance_globals_m,mesg_given)==232,"DECL instance_globals_m.mesg_given offset");
_Static_assert(offsetof(struct instance_globals_m,mtarget)==240,"DECL instance_globals_m.mtarget offset");
_Static_assert(offsetof(struct instance_globals_m,marcher)==248,"DECL instance_globals_m.marcher offset");
_Static_assert(offsetof(struct instance_globals_m,m_using)==256,"DECL instance_globals_m.m_using offset");
_Static_assert(offsetof(struct instance_globals_m,m)==264,"DECL instance_globals_m.m offset");
_Static_assert(offsetof(struct instance_globals_m,mapped_menu_cmds)==304,"DECL instance_globals_m.mapped_menu_cmds offset");
_Static_assert(offsetof(struct instance_globals_m,mapped_menu_op)==337,"DECL instance_globals_m.mapped_menu_op offset");
_Static_assert(offsetof(struct instance_globals_m,max_regions)==372,"DECL instance_globals_m.max_regions offset");
_Static_assert(offsetof(struct instance_globals_m,mentioned_water)==376,"DECL instance_globals_m.mentioned_water offset");
_Static_assert(offsetof(struct instance_globals_m,havestate)==377,"DECL instance_globals_m.havestate offset");
_Static_assert(sizeof(struct instance_globals_n)==152,"DECL instance_globals_n size");
_Static_assert(offsetof(struct instance_globals_n,now_or_before_idx)==0,"DECL instance_globals_n.now_or_before_idx offset");
_Static_assert(offsetof(struct instance_globals_n,nomovemsg)==8,"DECL instance_globals_n.nomovemsg offset");
_Static_assert(offsetof(struct instance_globals_n,nsubroom)==16,"DECL instance_globals_n.nsubroom offset");
_Static_assert(offsetof(struct instance_globals_n,nowhere)==20,"DECL instance_globals_n.nowhere offset");
_Static_assert(offsetof(struct instance_globals_n,nesting)==28,"DECL instance_globals_n.nesting offset");
_Static_assert(offsetof(struct instance_globals_n,no_sound_notified)==32,"DECL instance_globals_n.no_sound_notified offset");
_Static_assert(offsetof(struct instance_globals_n,noisetime)==40,"DECL instance_globals_n.noisetime offset");
_Static_assert(offsetof(struct instance_globals_n,new_locations)==48,"DECL instance_globals_n.new_locations offset");
_Static_assert(offsetof(struct instance_globals_n,n_loc_filled)==56,"DECL instance_globals_n.n_loc_filled offset");
_Static_assert(offsetof(struct instance_globals_n,n_menu_mapped)==60,"DECL instance_globals_n.n_menu_mapped offset");
_Static_assert(offsetof(struct instance_globals_n,notonhead)==62,"DECL instance_globals_n.notonhead offset");
_Static_assert(offsetof(struct instance_globals_n,nambuf)==63,"DECL instance_globals_n.nambuf offset");
_Static_assert(offsetof(struct instance_globals_n,n_ids_mapped)==128,"DECL instance_globals_n.n_ids_mapped offset");
_Static_assert(offsetof(struct instance_globals_n,num_lregions)==132,"DECL instance_globals_n.num_lregions offset");
_Static_assert(offsetof(struct instance_globals_n,nocreate)==136,"DECL instance_globals_n.nocreate offset");
_Static_assert(offsetof(struct instance_globals_n,nocreate2)==138,"DECL instance_globals_n.nocreate2 offset");
_Static_assert(offsetof(struct instance_globals_n,nocreate3)==140,"DECL instance_globals_n.nocreate3 offset");
_Static_assert(offsetof(struct instance_globals_n,nocreate4)==142,"DECL instance_globals_n.nocreate4 offset");
_Static_assert(offsetof(struct instance_globals_n,havestate)==144,"DECL instance_globals_n.havestate offset");
_Static_assert(sizeof(struct instance_globals_o)==560,"DECL instance_globals_o size");
_Static_assert(offsetof(struct instance_globals_o,objs_deleted)==0,"DECL instance_globals_o.objs_deleted offset");
_Static_assert(offsetof(struct instance_globals_o,occupants)==8,"DECL instance_globals_o.occupants offset");
_Static_assert(offsetof(struct instance_globals_o,occupation)==56,"DECL instance_globals_o.occupation offset");
_Static_assert(offsetof(struct instance_globals_o,occtime)==64,"DECL instance_globals_o.occtime offset");
_Static_assert(offsetof(struct instance_globals_o,otg_temp)==68,"DECL instance_globals_o.otg_temp offset");
_Static_assert(offsetof(struct instance_globals_o,otg_otmp)==72,"DECL instance_globals_o.otg_otmp offset");
_Static_assert(offsetof(struct instance_globals_o,occtxt)==80,"DECL instance_globals_o.occtxt offset");
_Static_assert(offsetof(struct instance_globals_o,ov_primary_syms)==88,"DECL instance_globals_o.ov_primary_syms offset");
_Static_assert(offsetof(struct instance_globals_o,ov_rogue_syms)==284,"DECL instance_globals_o.ov_rogue_syms offset");
_Static_assert(offsetof(struct instance_globals_o,only)==480,"DECL instance_globals_o.only offset");
_Static_assert(offsetof(struct instance_globals_o,oclass_prob_totals)==484,"DECL instance_globals_o.oclass_prob_totals offset");
_Static_assert(offsetof(struct instance_globals_o,opt_phase)==520,"DECL instance_globals_o.opt_phase offset");
_Static_assert(offsetof(struct instance_globals_o,opt_initial)==524,"DECL instance_globals_o.opt_initial offset");
_Static_assert(offsetof(struct instance_globals_o,opt_from_file)==525,"DECL instance_globals_o.opt_from_file offset");
_Static_assert(offsetof(struct instance_globals_o,opt_need_redraw)==526,"DECL instance_globals_o.opt_need_redraw offset");
_Static_assert(offsetof(struct instance_globals_o,opt_need_glyph_reset)==527,"DECL instance_globals_o.opt_need_glyph_reset offset");
_Static_assert(offsetof(struct instance_globals_o,opt_need_promptstyle)==528,"DECL instance_globals_o.opt_need_promptstyle offset");
_Static_assert(offsetof(struct instance_globals_o,opt_reset_customcolors)==529,"DECL instance_globals_o.opt_reset_customcolors offset");
_Static_assert(offsetof(struct instance_globals_o,opt_reset_customsymbols)==530,"DECL instance_globals_o.opt_reset_customsymbols offset");
_Static_assert(offsetof(struct instance_globals_o,opt_update_basic_palette)==531,"DECL instance_globals_o.opt_update_basic_palette offset");
_Static_assert(offsetof(struct instance_globals_o,opt_symset_changed)==532,"DECL instance_globals_o.opt_symset_changed offset");
_Static_assert(offsetof(struct instance_globals_o,oldcap)==536,"DECL instance_globals_o.oldcap offset");
_Static_assert(offsetof(struct instance_globals_o,oldfruit)==544,"DECL instance_globals_o.oldfruit offset");
_Static_assert(offsetof(struct instance_globals_o,oracle_flg)==552,"DECL instance_globals_o.oracle_flg offset");
_Static_assert(offsetof(struct instance_globals_o,override_confirmation)==556,"DECL instance_globals_o.override_confirmation offset");
_Static_assert(offsetof(struct instance_globals_o,obj_zapped)==557,"DECL instance_globals_o.obj_zapped offset");
_Static_assert(offsetof(struct instance_globals_o,havestate)==558,"DECL instance_globals_o.havestate offset");
_Static_assert(sizeof(struct instance_globals_p)==536,"DECL instance_globals_p size");
_Static_assert(offsetof(struct instance_globals_p,polearm_range_min)==0,"DECL instance_globals_p.polearm_range_min offset");
_Static_assert(offsetof(struct instance_globals_p,polearm_range_max)==4,"DECL instance_globals_p.polearm_range_max offset");
_Static_assert(offsetof(struct instance_globals_p,plnamelen)==8,"DECL instance_globals_p.plnamelen offset");
_Static_assert(offsetof(struct instance_globals_p,pl_race)==12,"DECL instance_globals_p.pl_race offset");
_Static_assert(offsetof(struct instance_globals_p,plinemsg_types)==16,"DECL instance_globals_p.plinemsg_types offset");
_Static_assert(offsetof(struct instance_globals_p,petname_used)==24,"DECL instance_globals_p.petname_used offset");
_Static_assert(offsetof(struct instance_globals_p,preferred_pet)==28,"DECL instance_globals_p.preferred_pet offset");
_Static_assert(offsetof(struct instance_globals_p,primary_syms)==29,"DECL instance_globals_p.primary_syms offset");
_Static_assert(offsetof(struct instance_globals_p,perm_invent_toggling_direction)==228,"DECL instance_globals_p.perm_invent_toggling_direction offset");
_Static_assert(offsetof(struct instance_globals_p,picked_filter)==232,"DECL instance_globals_p.picked_filter offset");
_Static_assert(offsetof(struct instance_globals_p,pickup_encumbrance)==236,"DECL instance_globals_p.pickup_encumbrance offset");
_Static_assert(offsetof(struct instance_globals_p,pline_flags)==240,"DECL instance_globals_p.pline_flags offset");
_Static_assert(offsetof(struct instance_globals_p,prevmsg)==244,"DECL instance_globals_p.prevmsg offset");
_Static_assert(offsetof(struct instance_globals_p,potion_nothing)==500,"DECL instance_globals_p.potion_nothing offset");
_Static_assert(offsetof(struct instance_globals_p,potion_unkn)==504,"DECL instance_globals_p.potion_unkn offset");
_Static_assert(offsetof(struct instance_globals_p,p_aligntyp)==508,"DECL instance_globals_p.p_aligntyp offset");
_Static_assert(offsetof(struct instance_globals_p,p_trouble)==512,"DECL instance_globals_p.p_trouble offset");
_Static_assert(offsetof(struct instance_globals_p,p_type)==516,"DECL instance_globals_p.p_type offset");
_Static_assert(offsetof(struct instance_globals_p,propellor)==520,"DECL instance_globals_p.propellor offset");
_Static_assert(offsetof(struct instance_globals_p,poly_zapped)==528,"DECL instance_globals_p.poly_zapped offset");
_Static_assert(offsetof(struct instance_globals_p,havestate)==532,"DECL instance_globals_p.havestate offset");
_Static_assert(sizeof(struct instance_globals_q)==1,"DECL instance_globals_q size");
_Static_assert(offsetof(struct instance_globals_q,havestate)==0,"DECL instance_globals_q.havestate offset");
_Static_assert(sizeof(struct instance_globals_r)==408,"DECL instance_globals_r size");
_Static_assert(offsetof(struct instance_globals_r,rogue_syms)==0,"DECL instance_globals_r.rogue_syms offset");
_Static_assert(offsetof(struct instance_globals_r,r)==196,"DECL instance_globals_r.r offset");
_Static_assert(offsetof(struct instance_globals_r,ransacked)==340,"DECL instance_globals_r.ransacked offset");
_Static_assert(offsetof(struct instance_globals_r,regions)==344,"DECL instance_globals_r.regions offset");
_Static_assert(offsetof(struct instance_globals_r,rip)==352,"DECL instance_globals_r.rip offset");
_Static_assert(offsetof(struct instance_globals_r,role_pa)==360,"DECL instance_globals_r.role_pa offset");
_Static_assert(offsetof(struct instance_globals_r,role_post_attribs)==364,"DECL instance_globals_r.role_post_attribs offset");
_Static_assert(offsetof(struct instance_globals_r,rfilter)==366,"DECL instance_globals_r.rfilter offset");
_Static_assert(offsetof(struct instance_globals_r,repo)==384,"DECL instance_globals_r.repo offset");
_Static_assert(offsetof(struct instance_globals_r,havestate)==400,"DECL instance_globals_r.havestate offset");
_Static_assert(sizeof(struct instance_globals_s)==1408,"DECL instance_globals_s size");
_Static_assert(offsetof(struct instance_globals_s,spec_dbon_applies)==0,"DECL instance_globals_s.spec_dbon_applies offset");
_Static_assert(offsetof(struct instance_globals_s,stairs)==8,"DECL instance_globals_s.stairs offset");
_Static_assert(offsetof(struct instance_globals_s,smeq)==16,"DECL instance_globals_s.smeq offset");
_Static_assert(offsetof(struct instance_globals_s,stoned)==180,"DECL instance_globals_s.stoned offset");
_Static_assert(offsetof(struct instance_globals_s,subrooms)==184,"DECL instance_globals_s.subrooms offset");
_Static_assert(offsetof(struct instance_globals_s,save_dlevel)==192,"DECL instance_globals_s.save_dlevel offset");
_Static_assert(offsetof(struct instance_globals_s,symset)==200,"DECL instance_globals_s.symset offset");
_Static_assert(offsetof(struct instance_globals_s,sym_customizations)==280,"DECL instance_globals_s.sym_customizations offset");
_Static_assert(offsetof(struct instance_globals_s,showsyms)==664,"DECL instance_globals_s.showsyms offset");
_Static_assert(offsetof(struct instance_globals_s,symset_count)==860,"DECL instance_globals_s.symset_count offset");
_Static_assert(offsetof(struct instance_globals_s,symset_which_set)==864,"DECL instance_globals_s.symset_which_set offset");
_Static_assert(offsetof(struct instance_globals_s,SAVEF)==868,"DECL instance_globals_s.SAVEF offset");
_Static_assert(offsetof(struct instance_globals_s,sortlootmode)==924,"DECL instance_globals_s.sortlootmode offset");
_Static_assert(offsetof(struct instance_globals_s,skipdrin)==928,"DECL instance_globals_s.skipdrin offset");
_Static_assert(offsetof(struct instance_globals_s,somebody_can_move)==929,"DECL instance_globals_s.somebody_can_move offset");
_Static_assert(offsetof(struct instance_globals_s,symset_list)==936,"DECL instance_globals_s.symset_list offset");
_Static_assert(offsetof(struct instance_globals_s,save_menucolors)==944,"DECL instance_globals_s.save_menucolors offset");
_Static_assert(offsetof(struct instance_globals_s,save_colorings)==952,"DECL instance_globals_s.save_colorings offset");
_Static_assert(offsetof(struct instance_globals_s,simple_options_help)==960,"DECL instance_globals_s.simple_options_help offset");
_Static_assert(offsetof(struct instance_globals_s,sellobj_first)==961,"DECL instance_globals_s.sellobj_first offset");
_Static_assert(offsetof(struct instance_globals_s,shop_filter)==962,"DECL instance_globals_s.shop_filter offset");
_Static_assert(offsetof(struct instance_globals_s,saved_pline_index)==964,"DECL instance_globals_s.saved_pline_index offset");
_Static_assert(offsetof(struct instance_globals_s,saved_plines)==968,"DECL instance_globals_s.saved_plines offset");
_Static_assert(offsetof(struct instance_globals_s,sex_change_ok)==1368,"DECL instance_globals_s.sex_change_ok offset");
_Static_assert(offsetof(struct instance_globals_s,sell_response)==1372,"DECL instance_globals_s.sell_response offset");
_Static_assert(offsetof(struct instance_globals_s,sell_how)==1376,"DECL instance_globals_s.sell_how offset");
_Static_assert(offsetof(struct instance_globals_s,spl_sortmode)==1380,"DECL instance_globals_s.spl_sortmode offset");
_Static_assert(offsetof(struct instance_globals_s,spl_orderindx)==1384,"DECL instance_globals_s.spl_orderindx offset");
_Static_assert(offsetof(struct instance_globals_s,stealoid)==1392,"DECL instance_globals_s.stealoid offset");
_Static_assert(offsetof(struct instance_globals_s,stealmid)==1396,"DECL instance_globals_s.stealmid offset");
_Static_assert(offsetof(struct instance_globals_s,seethru)==1400,"DECL instance_globals_s.seethru offset");
_Static_assert(offsetof(struct instance_globals_s,havestate)==1404,"DECL instance_globals_s.havestate offset");
_Static_assert(sizeof(struct instance_globals_saved_b)==96,"DECL instance_globals_saved_b size");
_Static_assert(offsetof(struct instance_globals_saved_b,branches)==0,"DECL instance_globals_saved_b.branches offset");
_Static_assert(offsetof(struct instance_globals_saved_b,bbubbles)==8,"DECL instance_globals_saved_b.bbubbles offset");
_Static_assert(offsetof(struct instance_globals_saved_b,bases)==16,"DECL instance_globals_saved_b.bases offset");
_Static_assert(sizeof(struct instance_globals_saved_c)==704,"DECL instance_globals_saved_c size");
_Static_assert(offsetof(struct instance_globals_saved_c,context)==0,"DECL instance_globals_saved_c.context offset");
_Static_assert(sizeof(struct instance_globals_saved_d)==2584,"DECL instance_globals_saved_d size");
_Static_assert(offsetof(struct instance_globals_saved_d,dungeons)==0,"DECL instance_globals_saved_d.dungeons offset");
_Static_assert(offsetof(struct instance_globals_saved_d,dungeon_topology)==1472,"DECL instance_globals_saved_d.dungeon_topology offset");
_Static_assert(offsetof(struct instance_globals_saved_d,dndest)==1586,"DECL instance_globals_saved_d.dndest offset");
_Static_assert(offsetof(struct instance_globals_saved_d,doors)==1608,"DECL instance_globals_saved_d.doors offset");
_Static_assert(offsetof(struct instance_globals_saved_d,doors_alloc)==1616,"DECL instance_globals_saved_d.doors_alloc offset");
_Static_assert(offsetof(struct instance_globals_saved_d,disco)==1620,"DECL instance_globals_saved_d.disco offset");
_Static_assert(sizeof(struct instance_globals_saved_e)==8,"DECL instance_globals_saved_e size");
_Static_assert(offsetof(struct instance_globals_saved_e,exclusion_zones)==0,"DECL instance_globals_saved_e.exclusion_zones offset");
_Static_assert(sizeof(struct instance_globals_saved_h)==4,"DECL instance_globals_saved_h size");
_Static_assert(offsetof(struct instance_globals_saved_h,hackpid)==0,"DECL instance_globals_saved_h.hackpid offset");
_Static_assert(sizeof(struct instance_globals_saved_i)==4,"DECL instance_globals_saved_i size");
_Static_assert(offsetof(struct instance_globals_saved_i,inv_pos)==0,"DECL instance_globals_saved_i.inv_pos offset");
_Static_assert(sizeof(struct instance_globals_saved_k)==272,"DECL instance_globals_saved_k size");
_Static_assert(offsetof(struct instance_globals_saved_k,killer)==0,"DECL instance_globals_saved_k.killer offset");
_Static_assert(sizeof(struct instance_globals_saved_l)==42568,"DECL instance_globals_saved_l size");
_Static_assert(offsetof(struct instance_globals_saved_l,lastseentyp)==0,"DECL instance_globals_saved_l.lastseentyp offset");
_Static_assert(offsetof(struct instance_globals_saved_l,level)==1680,"DECL instance_globals_saved_l.level offset");
_Static_assert(offsetof(struct instance_globals_saved_l,level_info)==42056,"DECL instance_globals_saved_l.level_info offset");
_Static_assert(sizeof(struct instance_globals_saved_m)==1552,"DECL instance_globals_saved_m size");
_Static_assert(offsetof(struct instance_globals_saved_m,mapseenchn)==0,"DECL instance_globals_saved_m.mapseenchn offset");
_Static_assert(offsetof(struct instance_globals_saved_m,moves)==8,"DECL instance_globals_saved_m.moves offset");
_Static_assert(offsetof(struct instance_globals_saved_m,mvitals)==16,"DECL instance_globals_saved_m.mvitals offset");
_Static_assert(sizeof(struct instance_globals_saved_n)==52,"DECL instance_globals_saved_n size");
_Static_assert(offsetof(struct instance_globals_saved_n,n_dgns)==0,"DECL instance_globals_saved_n.n_dgns offset");
_Static_assert(offsetof(struct instance_globals_saved_n,nhuuid)==4,"DECL instance_globals_saved_n.nhuuid offset");
_Static_assert(offsetof(struct instance_globals_saved_n,nroom)==44,"DECL instance_globals_saved_n.nroom offset");
_Static_assert(offsetof(struct instance_globals_saved_n,n_regions)==48,"DECL instance_globals_saved_n.n_regions offset");
_Static_assert(sizeof(struct instance_globals_saved_o)==24,"DECL instance_globals_saved_o size");
_Static_assert(offsetof(struct instance_globals_saved_o,oracle_cnt)==0,"DECL instance_globals_saved_o.oracle_cnt offset");
_Static_assert(offsetof(struct instance_globals_saved_o,oracle_loc)==8,"DECL instance_globals_saved_o.oracle_loc offset");
_Static_assert(offsetof(struct instance_globals_saved_o,omoves)==16,"DECL instance_globals_saved_o.omoves offset");
_Static_assert(sizeof(struct instance_globals_saved_p)==96,"DECL instance_globals_saved_p size");
_Static_assert(offsetof(struct instance_globals_saved_p,plname)==0,"DECL instance_globals_saved_p.plname offset");
_Static_assert(offsetof(struct instance_globals_saved_p,pl_character)==32,"DECL instance_globals_saved_p.pl_character offset");
_Static_assert(offsetof(struct instance_globals_saved_p,pl_fruit)==64,"DECL instance_globals_saved_p.pl_fruit offset");
_Static_assert(sizeof(struct instance_globals_saved_q)==8,"DECL instance_globals_saved_q size");
_Static_assert(offsetof(struct instance_globals_saved_q,quest_status)==0,"DECL instance_globals_saved_q.quest_status offset");
_Static_assert(sizeof(struct instance_globals_saved_r)==18368,"DECL instance_globals_saved_r size");
_Static_assert(offsetof(struct instance_globals_saved_r,rooms)==0,"DECL instance_globals_saved_r.rooms offset");
_Static_assert(sizeof(struct instance_globals_saved_s)==352,"DECL instance_globals_saved_s size");
_Static_assert(offsetof(struct instance_globals_saved_s,spl_book)==0,"DECL instance_globals_saved_s.spl_book offset");
_Static_assert(offsetof(struct instance_globals_saved_s,sp_levchn)==344,"DECL instance_globals_saved_s.sp_levchn offset");
_Static_assert(sizeof(struct instance_globals_saved_t)==16,"DECL instance_globals_saved_t size");
_Static_assert(offsetof(struct instance_globals_saved_t,tune)==0,"DECL instance_globals_saved_t.tune offset");
_Static_assert(offsetof(struct instance_globals_saved_t,timer_id)==8,"DECL instance_globals_saved_t.timer_id offset");
_Static_assert(sizeof(struct instance_globals_saved_u)==16,"DECL instance_globals_saved_u size");
_Static_assert(offsetof(struct instance_globals_saved_u,updest)==0,"DECL instance_globals_saved_u.updest offset");
_Static_assert(sizeof(struct instance_globals_saved_w)==16,"DECL instance_globals_saved_w size");
_Static_assert(offsetof(struct instance_globals_saved_w,wreserve)==0,"DECL instance_globals_saved_w.wreserve offset");
_Static_assert(offsetof(struct instance_globals_saved_w,wtreserved)==8,"DECL instance_globals_saved_w.wtreserved offset");
_Static_assert(sizeof(struct instance_globals_saved_x)==8,"DECL instance_globals_saved_x size");
_Static_assert(offsetof(struct instance_globals_saved_x,xmin)==0,"DECL instance_globals_saved_x.xmin offset");
_Static_assert(offsetof(struct instance_globals_saved_x,xmax)==4,"DECL instance_globals_saved_x.xmax offset");
_Static_assert(sizeof(struct instance_globals_saved_y)==8,"DECL instance_globals_saved_y size");
_Static_assert(offsetof(struct instance_globals_saved_y,ymin)==0,"DECL instance_globals_saved_y.ymin offset");
_Static_assert(offsetof(struct instance_globals_saved_y,ymax)==4,"DECL instance_globals_saved_y.ymax offset");
_Static_assert(sizeof(struct instance_globals_t)==456,"DECL instance_globals_t size");
_Static_assert(offsetof(struct instance_globals_t,trapinfo)==0,"DECL instance_globals_t.trapinfo offset");
_Static_assert(offsetof(struct instance_globals_t,tbx)==24,"DECL instance_globals_t.tbx offset");
_Static_assert(offsetof(struct instance_globals_t,tby)==25,"DECL instance_globals_t.tby offset");
_Static_assert(offsetof(struct instance_globals_t,toplines)==26,"DECL instance_globals_t.toplines offset");
_Static_assert(offsetof(struct instance_globals_t,thrownobj)==328,"DECL instance_globals_t.thrownobj offset");
_Static_assert(offsetof(struct instance_globals_t,tc_gbl_data)==336,"DECL instance_globals_t.tc_gbl_data offset");
_Static_assert(offsetof(struct instance_globals_t,tmp_anything)==360,"DECL instance_globals_t.tmp_anything offset");
_Static_assert(offsetof(struct instance_globals_t,travelmap)==368,"DECL instance_globals_t.travelmap offset");
_Static_assert(offsetof(struct instance_globals_t,this_type)==376,"DECL instance_globals_t.this_type offset");
_Static_assert(offsetof(struct instance_globals_t,this_title)==384,"DECL instance_globals_t.this_title offset");
_Static_assert(offsetof(struct instance_globals_t,trapx)==392,"DECL instance_globals_t.trapx offset");
_Static_assert(offsetof(struct instance_globals_t,trapy)==394,"DECL instance_globals_t.trapy offset");
_Static_assert(offsetof(struct instance_globals_t,true_rumor_size)==400,"DECL instance_globals_t.true_rumor_size offset");
_Static_assert(offsetof(struct instance_globals_t,true_rumor_start)==408,"DECL instance_globals_t.true_rumor_start offset");
_Static_assert(offsetof(struct instance_globals_t,true_rumor_end)==416,"DECL instance_globals_t.true_rumor_end offset");
_Static_assert(offsetof(struct instance_globals_t,themeroom_failed)==424,"DECL instance_globals_t.themeroom_failed offset");
_Static_assert(offsetof(struct instance_globals_t,timer_base)==432,"DECL instance_globals_t.timer_base offset");
_Static_assert(offsetof(struct instance_globals_t,toptenwin)==440,"DECL instance_globals_t.toptenwin offset");
_Static_assert(offsetof(struct instance_globals_t,twohits)==444,"DECL instance_globals_t.twohits offset");
_Static_assert(offsetof(struct instance_globals_t,havestate)==448,"DECL instance_globals_t.havestate offset");
_Static_assert(sizeof(struct instance_globals_u)==440,"DECL instance_globals_u size");
_Static_assert(offsetof(struct instance_globals_u,update_all)==0,"DECL instance_globals_u.update_all offset");
_Static_assert(offsetof(struct instance_globals_u,unweapon)==1,"DECL instance_globals_u.unweapon offset");
_Static_assert(offsetof(struct instance_globals_u,urole)==8,"DECL instance_globals_u.urole offset");
_Static_assert(offsetof(struct instance_globals_u,urace)==320,"DECL instance_globals_u.urace offset");
_Static_assert(offsetof(struct instance_globals_u,uz_save)==432,"DECL instance_globals_u.uz_save offset");
_Static_assert(offsetof(struct instance_globals_u,havestate)==436,"DECL instance_globals_u.havestate offset");
_Static_assert(sizeof(struct instance_globals_v)==200,"DECL instance_globals_v size");
_Static_assert(offsetof(struct instance_globals_v,valset)==0,"DECL instance_globals_v.valset offset");
_Static_assert(offsetof(struct instance_globals_v,valuables)==32,"DECL instance_globals_v.valuables offset");
_Static_assert(offsetof(struct instance_globals_v,vis)==80,"DECL instance_globals_v.vis offset");
_Static_assert(offsetof(struct instance_globals_v,vault_x)==82,"DECL instance_globals_v.vault_x offset");
_Static_assert(offsetof(struct instance_globals_v,vault_y)==84,"DECL instance_globals_v.vault_y offset");
_Static_assert(offsetof(struct instance_globals_v,vamp_rise_msg)==86,"DECL instance_globals_v.vamp_rise_msg offset");
_Static_assert(offsetof(struct instance_globals_v,val_for_n_or_more)==88,"DECL instance_globals_v.val_for_n_or_more offset");
_Static_assert(offsetof(struct instance_globals_v,valid_menu_classes)==96,"DECL instance_globals_v.valid_menu_classes offset");
_Static_assert(offsetof(struct instance_globals_v,viz_array)==120,"DECL instance_globals_v.viz_array offset");
_Static_assert(offsetof(struct instance_globals_v,viz_rmin)==128,"DECL instance_globals_v.viz_rmin offset");
_Static_assert(offsetof(struct instance_globals_v,viz_rmax)==136,"DECL instance_globals_v.viz_rmax offset");
_Static_assert(offsetof(struct instance_globals_v,vision_full_recalc)==144,"DECL instance_globals_v.vision_full_recalc offset");
_Static_assert(offsetof(struct instance_globals_v,voice)==152,"DECL instance_globals_v.voice offset");
_Static_assert(offsetof(struct instance_globals_v,havestate)==192,"DECL instance_globals_v.havestate offset");
_Static_assert(sizeof(struct instance_globals_w)==192,"DECL instance_globals_w size");
_Static_assert(offsetof(struct instance_globals_w,warn_obj_cnt)==0,"DECL instance_globals_w.warn_obj_cnt offset");
_Static_assert(offsetof(struct instance_globals_w,wailmsg)==8,"DECL instance_globals_w.wailmsg offset");
_Static_assert(offsetof(struct instance_globals_w,wasinwater)==16,"DECL instance_globals_w.wasinwater offset");
_Static_assert(offsetof(struct instance_globals_w,warnsyms)==17,"DECL instance_globals_w.warnsyms offset");
_Static_assert(offsetof(struct instance_globals_w,wizkit)==23,"DECL instance_globals_w.wizkit offset");
_Static_assert(offsetof(struct instance_globals_w,wc)==152,"DECL instance_globals_w.wc offset");
_Static_assert(offsetof(struct instance_globals_w,wportal)==160,"DECL instance_globals_w.wportal offset");
_Static_assert(offsetof(struct instance_globals_w,wsettings)==168,"DECL instance_globals_w.wsettings offset");
_Static_assert(offsetof(struct instance_globals_w,were_changes)==176,"DECL instance_globals_w.were_changes offset");
_Static_assert(offsetof(struct instance_globals_w,havestate)==184,"DECL instance_globals_w.havestate offset");
_Static_assert(sizeof(struct instance_globals_x)==56,"DECL instance_globals_x size");
_Static_assert(offsetof(struct instance_globals_x,x_maze_max)==0,"DECL instance_globals_x.x_maze_max offset");
_Static_assert(offsetof(struct instance_globals_x,xlock)==8,"DECL instance_globals_x.xlock offset");
_Static_assert(offsetof(struct instance_globals_x,xnamep)==40,"DECL instance_globals_x.xnamep offset");
_Static_assert(offsetof(struct instance_globals_x,xstart)==48,"DECL instance_globals_x.xstart offset");
_Static_assert(offsetof(struct instance_globals_x,xsize)==50,"DECL instance_globals_x.xsize offset");
_Static_assert(offsetof(struct instance_globals_x,havestate)==52,"DECL instance_globals_x.havestate offset");
_Static_assert(sizeof(struct instance_globals_y)==224,"DECL instance_globals_y size");
_Static_assert(offsetof(struct instance_globals_y,y_maze_max)==0,"DECL instance_globals_y.y_maze_max offset");
_Static_assert(offsetof(struct instance_globals_y,youmonst)==8,"DECL instance_globals_y.youmonst offset");
_Static_assert(offsetof(struct instance_globals_y,you_buf)==200,"DECL instance_globals_y.you_buf offset");
_Static_assert(offsetof(struct instance_globals_y,you_buf_siz)==208,"DECL instance_globals_y.you_buf_siz offset");
_Static_assert(offsetof(struct instance_globals_y,ystart)==212,"DECL instance_globals_y.ystart offset");
_Static_assert(offsetof(struct instance_globals_y,ysize)==214,"DECL instance_globals_y.ysize offset");
_Static_assert(offsetof(struct instance_globals_y,havestate)==216,"DECL instance_globals_y.havestate offset");
_Static_assert(sizeof(struct instance_globals_z)==3,"DECL instance_globals_z size");
_Static_assert(offsetof(struct instance_globals_z,zombify)==0,"DECL instance_globals_z.zombify offset");
_Static_assert(offsetof(struct instance_globals_z,zap_oseen)==1,"DECL instance_globals_z.zap_oseen offset");
_Static_assert(offsetof(struct instance_globals_z,havestate)==2,"DECL instance_globals_z.havestate offset");
_Static_assert(sizeof(struct istat_s)==88,"DECL istat_s size");
_Static_assert(offsetof(struct istat_s,fldname)==0,"DECL istat_s.fldname offset");
_Static_assert(offsetof(struct istat_s,fldfmt)==8,"DECL istat_s.fldfmt offset");
_Static_assert(offsetof(struct istat_s,time)==16,"DECL istat_s.time offset");
_Static_assert(offsetof(struct istat_s,chg)==24,"DECL istat_s.chg offset");
_Static_assert(offsetof(struct istat_s,percent_matters)==25,"DECL istat_s.percent_matters offset");
_Static_assert(offsetof(struct istat_s,percent_value)==26,"DECL istat_s.percent_value offset");
_Static_assert(offsetof(struct istat_s,anytype)==28,"DECL istat_s.anytype offset");
_Static_assert(offsetof(struct istat_s,a)==32,"DECL istat_s.a offset");
_Static_assert(offsetof(struct istat_s,rawval)==40,"DECL istat_s.rawval offset");
_Static_assert(offsetof(struct istat_s,val)==48,"DECL istat_s.val offset");
_Static_assert(offsetof(struct istat_s,valwidth)==56,"DECL istat_s.valwidth offset");
_Static_assert(offsetof(struct istat_s,idxmax)==60,"DECL istat_s.idxmax offset");
_Static_assert(offsetof(struct istat_s,fld)==64,"DECL istat_s.fld offset");
_Static_assert(offsetof(struct istat_s,hilite_rule)==72,"DECL istat_s.hilite_rule offset");
_Static_assert(offsetof(struct istat_s,thresholds)==80,"DECL istat_s.thresholds offset");
_Static_assert(sizeof(struct kinfo)==272,"DECL kinfo size");
_Static_assert(offsetof(struct kinfo,next)==0,"DECL kinfo.next offset");
_Static_assert(offsetof(struct kinfo,id)==8,"DECL kinfo.id offset");
_Static_assert(offsetof(struct kinfo,format)==12,"DECL kinfo.format offset");
_Static_assert(offsetof(struct kinfo,name)==16,"DECL kinfo.name offset");
_Static_assert(sizeof(struct launchplace)==16,"DECL launchplace size");
_Static_assert(offsetof(struct launchplace,obj)==0,"DECL launchplace.obj offset");
_Static_assert(offsetof(struct launchplace,x)==8,"DECL launchplace.x offset");
_Static_assert(offsetof(struct launchplace,y)==10,"DECL launchplace.y offset");
_Static_assert(sizeof(lev_region)==32,"DECL lev_region size");
_Static_assert(offsetof(lev_region,inarea)==0,"DECL lev_region.inarea offset");
_Static_assert(offsetof(lev_region,delarea)==8,"DECL lev_region.delarea offset");
_Static_assert(offsetof(lev_region,in_islev)==16,"DECL lev_region.in_islev offset");
_Static_assert(offsetof(lev_region,del_islev)==17,"DECL lev_region.del_islev offset");
_Static_assert(offsetof(lev_region,rtype)==18,"DECL lev_region.rtype offset");
_Static_assert(offsetof(lev_region,padding)==20,"DECL lev_region.padding offset");
_Static_assert(offsetof(lev_region,rname)==24,"DECL lev_region.rname offset");
_Static_assert(sizeof(struct levelflags)==16,"DECL levelflags size");
_Static_assert(offsetof(struct levelflags,nfountains)==0,"DECL levelflags.nfountains offset");
_Static_assert(offsetof(struct levelflags,nsinks)==1,"DECL levelflags.nsinks offset");
_Static_assert(offsetof(struct levelflags,temperature)==6,"DECL levelflags.temperature offset");
_Static_assert(offsetof(struct levelflags,stasis_until)==8,"DECL levelflags.stasis_until offset");
_Static_assert(sizeof(struct lifelists)==16,"DECL lifelists size");
_Static_assert(offsetof(struct lifelists,total_seen_upclose)==0,"DECL lifelists.total_seen_upclose offset");
_Static_assert(offsetof(struct lifelists,total_photographed)==8,"DECL lifelists.total_photographed offset");
_Static_assert(sizeof(struct linfo)==1,"DECL linfo size");
_Static_assert(offsetof(struct linfo,flags)==0,"DECL linfo.flags offset");
_Static_assert(sizeof(struct mkroom)==224,"DECL mkroom size");
_Static_assert(offsetof(struct mkroom,lx)==0,"DECL mkroom.lx offset");
_Static_assert(offsetof(struct mkroom,hx)==2,"DECL mkroom.hx offset");
_Static_assert(offsetof(struct mkroom,ly)==4,"DECL mkroom.ly offset");
_Static_assert(offsetof(struct mkroom,hy)==6,"DECL mkroom.hy offset");
_Static_assert(offsetof(struct mkroom,rtype)==8,"DECL mkroom.rtype offset");
_Static_assert(offsetof(struct mkroom,orig_rtype)==9,"DECL mkroom.orig_rtype offset");
_Static_assert(offsetof(struct mkroom,rlit)==10,"DECL mkroom.rlit offset");
_Static_assert(offsetof(struct mkroom,needfill)==11,"DECL mkroom.needfill offset");
_Static_assert(offsetof(struct mkroom,needjoining)==12,"DECL mkroom.needjoining offset");
_Static_assert(offsetof(struct mkroom,doorct)==13,"DECL mkroom.doorct offset");
_Static_assert(offsetof(struct mkroom,fdoor)==16,"DECL mkroom.fdoor offset");
_Static_assert(offsetof(struct mkroom,nsubrooms)==20,"DECL mkroom.nsubrooms offset");
_Static_assert(offsetof(struct mkroom,irregular)==21,"DECL mkroom.irregular offset");
_Static_assert(offsetof(struct mkroom,roomnoidx)==22,"DECL mkroom.roomnoidx offset");
_Static_assert(offsetof(struct mkroom,sbrooms)==24,"DECL mkroom.sbrooms offset");
_Static_assert(offsetof(struct mkroom,resident)==216,"DECL mkroom.resident offset");
_Static_assert(sizeof(struct monst)==192,"DECL monst size");
_Static_assert(offsetof(struct monst,nmon)==0,"DECL monst.nmon offset");
_Static_assert(offsetof(struct monst,data)==8,"DECL monst.data offset");
_Static_assert(offsetof(struct monst,m_id)==16,"DECL monst.m_id offset");
_Static_assert(offsetof(struct monst,mnum)==20,"DECL monst.mnum offset");
_Static_assert(offsetof(struct monst,cham)==22,"DECL monst.cham offset");
_Static_assert(offsetof(struct monst,movement)==24,"DECL monst.movement offset");
_Static_assert(offsetof(struct monst,m_lev)==26,"DECL monst.m_lev offset");
_Static_assert(offsetof(struct monst,malign)==27,"DECL monst.malign offset");
_Static_assert(offsetof(struct monst,mx)==28,"DECL monst.mx offset");
_Static_assert(offsetof(struct monst,my)==30,"DECL monst.my offset");
_Static_assert(offsetof(struct monst,mux)==32,"DECL monst.mux offset");
_Static_assert(offsetof(struct monst,muy)==34,"DECL monst.muy offset");
_Static_assert(offsetof(struct monst,mtrack)==36,"DECL monst.mtrack offset");
_Static_assert(offsetof(struct monst,mhp)==52,"DECL monst.mhp offset");
_Static_assert(offsetof(struct monst,mhpmax)==56,"DECL monst.mhpmax offset");
_Static_assert(offsetof(struct monst,mappearance)==60,"DECL monst.mappearance offset");
_Static_assert(offsetof(struct monst,m_ap_type)==64,"DECL monst.m_ap_type offset");
_Static_assert(offsetof(struct monst,mtame)==65,"DECL monst.mtame offset");
_Static_assert(offsetof(struct monst,mintrinsics)==66,"DECL monst.mintrinsics offset");
_Static_assert(offsetof(struct monst,mextrinsics)==68,"DECL monst.mextrinsics offset");
_Static_assert(offsetof(struct monst,seen_resistance)==72,"DECL monst.seen_resistance offset");
_Static_assert(offsetof(struct monst,mspec_used)==80,"DECL monst.mspec_used offset");
_Static_assert(offsetof(struct monst,mstrategy)==96,"DECL monst.mstrategy offset");
_Static_assert(offsetof(struct monst,mgoal)==104,"DECL monst.mgoal offset");
_Static_assert(offsetof(struct monst,mtrapseen)==112,"DECL monst.mtrapseen offset");
_Static_assert(offsetof(struct monst,mlstmv)==120,"DECL monst.mlstmv offset");
_Static_assert(offsetof(struct monst,mstate)==128,"DECL monst.mstate offset");
_Static_assert(offsetof(struct monst,migflags)==136,"DECL monst.migflags offset");
_Static_assert(offsetof(struct monst,mspare1)==144,"DECL monst.mspare1 offset");
_Static_assert(offsetof(struct monst,minvent)==152,"DECL monst.minvent offset");
_Static_assert(offsetof(struct monst,mw)==160,"DECL monst.mw offset");
_Static_assert(offsetof(struct monst,misc_worn_check)==168,"DECL monst.misc_worn_check offset");
_Static_assert(offsetof(struct monst,weapon_check)==176,"DECL monst.weapon_check offset");
_Static_assert(offsetof(struct monst,meating)==180,"DECL monst.meating offset");
_Static_assert(offsetof(struct monst,mextra)==184,"DECL monst.mextra offset");
_Static_assert(sizeof(struct multishot)==12,"DECL multishot size");
_Static_assert(offsetof(struct multishot,n)==0,"DECL multishot.n offset");
_Static_assert(offsetof(struct multishot,i)==4,"DECL multishot.i offset");
_Static_assert(offsetof(struct multishot,o)==8,"DECL multishot.o offset");
_Static_assert(offsetof(struct multishot,s)==10,"DECL multishot.s offset");
_Static_assert(sizeof(struct musable)==40,"DECL musable size");
_Static_assert(offsetof(struct musable,offensive)==0,"DECL musable.offensive offset");
_Static_assert(offsetof(struct musable,defensive)==8,"DECL musable.defensive offset");
_Static_assert(offsetof(struct musable,misc)==16,"DECL musable.misc offset");
_Static_assert(offsetof(struct musable,has_offense)==24,"DECL musable.has_offense offset");
_Static_assert(offsetof(struct musable,has_defense)==28,"DECL musable.has_defense offset");
_Static_assert(offsetof(struct musable,has_misc)==32,"DECL musable.has_misc offset");
_Static_assert(sizeof(struct mvitals)==4,"DECL mvitals size");
_Static_assert(offsetof(struct mvitals,born)==0,"DECL mvitals.born offset");
_Static_assert(offsetof(struct mvitals,died)==1,"DECL mvitals.died offset");
_Static_assert(offsetof(struct mvitals,mvflags)==2,"DECL mvitals.mvflags offset");
_Static_assert(sizeof(struct nhcoord)==4,"DECL nhcoord size");
_Static_assert(offsetof(struct nhcoord,x)==0,"DECL nhcoord.x offset");
_Static_assert(offsetof(struct nhcoord,y)==2,"DECL nhcoord.y offset");
_Static_assert(sizeof(struct nhrect)==8,"DECL nhrect size");
_Static_assert(offsetof(struct nhrect,lx)==0,"DECL nhrect.lx offset");
_Static_assert(offsetof(struct nhrect,ly)==2,"DECL nhrect.ly offset");
_Static_assert(offsetof(struct nhrect,hx)==4,"DECL nhrect.hx offset");
_Static_assert(offsetof(struct nhrect,hy)==6,"DECL nhrect.hy offset");
_Static_assert(sizeof(struct novel_tracking)==40,"DECL novel_tracking size");
_Static_assert(offsetof(struct novel_tracking,id)==0,"DECL novel_tracking.id offset");
_Static_assert(offsetof(struct novel_tracking,count)==4,"DECL novel_tracking.count offset");
_Static_assert(offsetof(struct novel_tracking,pasg)==8,"DECL novel_tracking.pasg offset");
_Static_assert(sizeof(struct obj)==112,"DECL obj size");
_Static_assert(offsetof(struct obj,nobj)==0,"DECL obj.nobj offset");
_Static_assert(offsetof(struct obj,v)==8,"DECL obj.v offset");
_Static_assert(offsetof(struct obj,cobj)==16,"DECL obj.cobj offset");
_Static_assert(offsetof(struct obj,o_id)==24,"DECL obj.o_id offset");
_Static_assert(offsetof(struct obj,ox)==28,"DECL obj.ox offset");
_Static_assert(offsetof(struct obj,oy)==30,"DECL obj.oy offset");
_Static_assert(offsetof(struct obj,otyp)==32,"DECL obj.otyp offset");
_Static_assert(offsetof(struct obj,owt)==36,"DECL obj.owt offset");
_Static_assert(offsetof(struct obj,quan)==40,"DECL obj.quan offset");
_Static_assert(offsetof(struct obj,spe)==48,"DECL obj.spe offset");
_Static_assert(offsetof(struct obj,oclass)==49,"DECL obj.oclass offset");
_Static_assert(offsetof(struct obj,invlet)==50,"DECL obj.invlet offset");
_Static_assert(offsetof(struct obj,oartifact)==51,"DECL obj.oartifact offset");
_Static_assert(offsetof(struct obj,where)==52,"DECL obj.where offset");
_Static_assert(offsetof(struct obj,timed)==54,"DECL obj.timed offset");
_Static_assert(offsetof(struct obj,corpsenm)==64,"DECL obj.corpsenm offset");
_Static_assert(offsetof(struct obj,usecount)==68,"DECL obj.usecount offset");
_Static_assert(offsetof(struct obj,oeaten)==72,"DECL obj.oeaten offset");
_Static_assert(offsetof(struct obj,age)==80,"DECL obj.age offset");
_Static_assert(offsetof(struct obj,owornmask)==88,"DECL obj.owornmask offset");
_Static_assert(offsetof(struct obj,lua_ref_cnt)==96,"DECL obj.lua_ref_cnt offset");
_Static_assert(offsetof(struct obj,omigr_from_dnum)==100,"DECL obj.omigr_from_dnum offset");
_Static_assert(offsetof(struct obj,omigr_from_dlevel)==102,"DECL obj.omigr_from_dlevel offset");
_Static_assert(offsetof(struct obj,oextra)==104,"DECL obj.oextra offset");
_Static_assert(sizeof(struct obj_split)==8,"DECL obj_split size");
_Static_assert(offsetof(struct obj_split,parent_oid)==0,"DECL obj_split.parent_oid offset");
_Static_assert(offsetof(struct obj_split,child_oid)==4,"DECL obj_split.child_oid offset");
_Static_assert(sizeof(struct polearm_info)==16,"DECL polearm_info size");
_Static_assert(offsetof(struct polearm_info,hitmon)==0,"DECL polearm_info.hitmon offset");
_Static_assert(offsetof(struct polearm_info,m_id)==8,"DECL polearm_info.m_id offset");
_Static_assert(sizeof(struct prop)==24,"DECL prop size");
_Static_assert(offsetof(struct prop,extrinsic)==0,"DECL prop.extrinsic offset");
_Static_assert(offsetof(struct prop,blocked)==8,"DECL prop.blocked offset");
_Static_assert(offsetof(struct prop,intrinsic)==16,"DECL prop.intrinsic offset");
_Static_assert(sizeof(struct q_score)==8,"DECL q_score size");
_Static_assert(offsetof(struct q_score,leader_m_id)==4,"DECL q_score.leader_m_id offset");
_Static_assert(sizeof(struct repo)==16,"DECL repo size");
_Static_assert(offsetof(struct repo,shopkeeper)==0,"DECL repo.shopkeeper offset");
_Static_assert(offsetof(struct repo,location)==8,"DECL repo.location offset");
_Static_assert(sizeof(struct rm)==8,"DECL rm size");
_Static_assert(offsetof(struct rm,glyph)==0,"DECL rm.glyph offset");
_Static_assert(offsetof(struct rm,typ)==4,"DECL rm.typ offset");
_Static_assert(offsetof(struct rm,seenv)==5,"DECL rm.seenv offset");
_Static_assert(sizeof(struct rogueroom)==16,"DECL rogueroom size");
_Static_assert(offsetof(struct rogueroom,rlx)==0,"DECL rogueroom.rlx offset");
_Static_assert(offsetof(struct rogueroom,rly)==2,"DECL rogueroom.rly offset");
_Static_assert(offsetof(struct rogueroom,dx)==4,"DECL rogueroom.dx offset");
_Static_assert(offsetof(struct rogueroom,dy)==6,"DECL rogueroom.dy offset");
_Static_assert(offsetof(struct rogueroom,real)==8,"DECL rogueroom.real offset");
_Static_assert(offsetof(struct rogueroom,doortable)==9,"DECL rogueroom.doortable offset");
_Static_assert(offsetof(struct rogueroom,nroom)==12,"DECL rogueroom.nroom offset");
_Static_assert(sizeof(struct role_filter)==16,"DECL role_filter size");
_Static_assert(offsetof(struct role_filter,roles)==0,"DECL role_filter.roles offset");
_Static_assert(offsetof(struct role_filter,mask)==14,"DECL role_filter.mask offset");
_Static_assert(sizeof(struct sinfo)==120,"DECL sinfo size");
_Static_assert(offsetof(struct sinfo,gameover)==0,"DECL sinfo.gameover offset");
_Static_assert(offsetof(struct sinfo,stopprint)==4,"DECL sinfo.stopprint offset");
_Static_assert(offsetof(struct sinfo,done_hup)==8,"DECL sinfo.done_hup offset");
_Static_assert(offsetof(struct sinfo,preserve_locks)==12,"DECL sinfo.preserve_locks offset");
_Static_assert(offsetof(struct sinfo,something_worth_saving)==16,"DECL sinfo.something_worth_saving offset");
_Static_assert(offsetof(struct sinfo,panicking)==20,"DECL sinfo.panicking offset");
_Static_assert(offsetof(struct sinfo,exiting)==24,"DECL sinfo.exiting offset");
_Static_assert(offsetof(struct sinfo,saving)==28,"DECL sinfo.saving offset");
_Static_assert(offsetof(struct sinfo,restoring)==32,"DECL sinfo.restoring offset");
_Static_assert(offsetof(struct sinfo,freeingdata)==36,"DECL sinfo.freeingdata offset");
_Static_assert(offsetof(struct sinfo,in_getlev)==40,"DECL sinfo.in_getlev offset");
_Static_assert(offsetof(struct sinfo,in_moveloop)==44,"DECL sinfo.in_moveloop offset");
_Static_assert(offsetof(struct sinfo,in_impossible)==48,"DECL sinfo.in_impossible offset");
_Static_assert(offsetof(struct sinfo,in_docrt)==52,"DECL sinfo.in_docrt offset");
_Static_assert(offsetof(struct sinfo,in_self_recover)==56,"DECL sinfo.in_self_recover offset");
_Static_assert(offsetof(struct sinfo,in_checkpoint)==60,"DECL sinfo.in_checkpoint offset");
_Static_assert(offsetof(struct sinfo,in_parseoptions)==64,"DECL sinfo.in_parseoptions offset");
_Static_assert(offsetof(struct sinfo,in_role_selection)==68,"DECL sinfo.in_role_selection offset");
_Static_assert(offsetof(struct sinfo,in_getlin)==72,"DECL sinfo.in_getlin offset");
_Static_assert(offsetof(struct sinfo,in_sanity_check)==76,"DECL sinfo.in_sanity_check offset");
_Static_assert(offsetof(struct sinfo,config_error_ready)==80,"DECL sinfo.config_error_ready offset");
_Static_assert(offsetof(struct sinfo,beyond_savefile_load)==84,"DECL sinfo.beyond_savefile_load offset");
_Static_assert(offsetof(struct sinfo,savefile_completed)==88,"DECL sinfo.savefile_completed offset");
_Static_assert(offsetof(struct sinfo,reading_bonesfile)==92,"DECL sinfo.reading_bonesfile offset");
_Static_assert(offsetof(struct sinfo,in_paniclog)==96,"DECL sinfo.in_paniclog offset");
_Static_assert(offsetof(struct sinfo,wizkit_wishing)==100,"DECL sinfo.wizkit_wishing offset");
_Static_assert(offsetof(struct sinfo,input_state)==104,"DECL sinfo.input_state offset");
_Static_assert(offsetof(struct sinfo,early_options)==108,"DECL sinfo.early_options offset");
_Static_assert(offsetof(struct sinfo,resize_pending)==112,"DECL sinfo.resize_pending offset");
_Static_assert(offsetof(struct sinfo,getting_char)==116,"DECL sinfo.getting_char offset");
_Static_assert(sizeof(struct skills)==6,"DECL skills size");
_Static_assert(offsetof(struct skills,skill)==0,"DECL skills.skill offset");
_Static_assert(offsetof(struct skills,max_skill)==2,"DECL skills.max_skill offset");
_Static_assert(offsetof(struct skills,advance)==4,"DECL skills.advance offset");
_Static_assert(sizeof(struct sound_voice)==40,"DECL sound_voice size");
_Static_assert(offsetof(struct sound_voice,serialno)==0,"DECL sound_voice.serialno offset");
_Static_assert(offsetof(struct sound_voice,gender)==4,"DECL sound_voice.gender offset");
_Static_assert(offsetof(struct sound_voice,tone)==8,"DECL sound_voice.tone offset");
_Static_assert(offsetof(struct sound_voice,volume)==12,"DECL sound_voice.volume offset");
_Static_assert(offsetof(struct sound_voice,moreinfo)==16,"DECL sound_voice.moreinfo offset");
_Static_assert(offsetof(struct sound_voice,mon)==24,"DECL sound_voice.mon offset");
_Static_assert(offsetof(struct sound_voice,nameid)==32,"DECL sound_voice.nameid offset");
_Static_assert(sizeof(struct spell)==8,"DECL spell size");
_Static_assert(offsetof(struct spell,sp_id)==0,"DECL spell.sp_id offset");
_Static_assert(offsetof(struct spell,sp_lev)==2,"DECL spell.sp_lev offset");
_Static_assert(offsetof(struct spell,sp_know)==4,"DECL spell.sp_know offset");
_Static_assert(sizeof(union str_or_len)==8,"DECL str_or_len size");
_Static_assert(offsetof(union str_or_len,str)==0,"DECL str_or_len.str offset");
_Static_assert(offsetof(union str_or_len,len)==0,"DECL str_or_len.len offset");
_Static_assert(sizeof(struct symset_customization)==32,"DECL symset_customization size");
_Static_assert(offsetof(struct symset_customization,customization_name)==0,"DECL symset_customization.customization_name offset");
_Static_assert(offsetof(struct symset_customization,count)==8,"DECL symset_customization.count offset");
_Static_assert(offsetof(struct symset_customization,custtype)==12,"DECL symset_customization.custtype offset");
_Static_assert(offsetof(struct symset_customization,details)==16,"DECL symset_customization.details offset");
_Static_assert(offsetof(struct symset_customization,details_end)==24,"DECL symset_customization.details_end offset");
_Static_assert(sizeof(struct symsetentry)==40,"DECL symsetentry size");
_Static_assert(offsetof(struct symsetentry,next)==0,"DECL symsetentry.next offset");
_Static_assert(offsetof(struct symsetentry,name)==8,"DECL symsetentry.name offset");
_Static_assert(offsetof(struct symsetentry,desc)==16,"DECL symsetentry.desc offset");
_Static_assert(offsetof(struct symsetentry,idx)==24,"DECL symsetentry.idx offset");
_Static_assert(offsetof(struct symsetentry,handling)==28,"DECL symsetentry.handling offset");
_Static_assert(sizeof(struct takeoff_info)==56,"DECL takeoff_info size");
_Static_assert(offsetof(struct takeoff_info,mask)==0,"DECL takeoff_info.mask offset");
_Static_assert(offsetof(struct takeoff_info,what)==8,"DECL takeoff_info.what offset");
_Static_assert(offsetof(struct takeoff_info,delay)==16,"DECL takeoff_info.delay offset");
_Static_assert(offsetof(struct takeoff_info,cancelled_don)==20,"DECL takeoff_info.cancelled_don offset");
_Static_assert(offsetof(struct takeoff_info,disrobing)==21,"DECL takeoff_info.disrobing offset");
_Static_assert(sizeof(struct tc_gbl_data)==24,"DECL tc_gbl_data size");
_Static_assert(offsetof(struct tc_gbl_data,tc_AS)==0,"DECL tc_gbl_data.tc_AS offset");
_Static_assert(offsetof(struct tc_gbl_data,tc_AE)==8,"DECL tc_gbl_data.tc_AE offset");
_Static_assert(offsetof(struct tc_gbl_data,tc_LI)==16,"DECL tc_gbl_data.tc_LI offset");
_Static_assert(offsetof(struct tc_gbl_data,tc_CO)==20,"DECL tc_gbl_data.tc_CO offset");
_Static_assert(sizeof(struct tin_info)==24,"DECL tin_info size");
_Static_assert(offsetof(struct tin_info,tin)==0,"DECL tin_info.tin offset");
_Static_assert(offsetof(struct tin_info,o_id)==8,"DECL tin_info.o_id offset");
_Static_assert(offsetof(struct tin_info,usedtime)==12,"DECL tin_info.usedtime offset");
_Static_assert(offsetof(struct tin_info,reqtime)==16,"DECL tin_info.reqtime offset");
_Static_assert(sizeof(struct trapinfo)==24,"DECL trapinfo size");
_Static_assert(offsetof(struct trapinfo,tobj)==0,"DECL trapinfo.tobj offset");
_Static_assert(offsetof(struct trapinfo,tx)==8,"DECL trapinfo.tx offset");
_Static_assert(offsetof(struct trapinfo,ty)==10,"DECL trapinfo.ty offset");
_Static_assert(offsetof(struct trapinfo,time_needed)==12,"DECL trapinfo.time_needed offset");
_Static_assert(offsetof(struct trapinfo,force_bungle)==16,"DECL trapinfo.force_bungle offset");
_Static_assert(sizeof(struct tribute_info)==16,"DECL tribute_info size");
_Static_assert(offsetof(struct tribute_info,tributesz)==0,"DECL tribute_info.tributesz offset");
_Static_assert(offsetof(struct tribute_info,enabled)==8,"DECL tribute_info.enabled offset");
_Static_assert(sizeof(struct u_conduct)==144,"DECL u_conduct size");
_Static_assert(offsetof(struct u_conduct,unvegetarian)==0,"DECL u_conduct.unvegetarian offset");
_Static_assert(offsetof(struct u_conduct,unvegan)==8,"DECL u_conduct.unvegan offset");
_Static_assert(offsetof(struct u_conduct,food)==16,"DECL u_conduct.food offset");
_Static_assert(offsetof(struct u_conduct,gnostic)==24,"DECL u_conduct.gnostic offset");
_Static_assert(offsetof(struct u_conduct,weaphit)==32,"DECL u_conduct.weaphit offset");
_Static_assert(offsetof(struct u_conduct,killer)==40,"DECL u_conduct.killer offset");
_Static_assert(offsetof(struct u_conduct,literate)==48,"DECL u_conduct.literate offset");
_Static_assert(offsetof(struct u_conduct,polypiles)==56,"DECL u_conduct.polypiles offset");
_Static_assert(offsetof(struct u_conduct,polyselfs)==64,"DECL u_conduct.polyselfs offset");
_Static_assert(offsetof(struct u_conduct,wishes)==72,"DECL u_conduct.wishes offset");
_Static_assert(offsetof(struct u_conduct,wisharti)==80,"DECL u_conduct.wisharti offset");
_Static_assert(offsetof(struct u_conduct,hf_reserved1)==88,"DECL u_conduct.hf_reserved1 offset");
_Static_assert(offsetof(struct u_conduct,sokocheat)==96,"DECL u_conduct.sokocheat offset");
_Static_assert(offsetof(struct u_conduct,pets)==104,"DECL u_conduct.pets offset");
_Static_assert(offsetof(struct u_conduct,reserved1)==112,"DECL u_conduct.reserved1 offset");
_Static_assert(offsetof(struct u_conduct,reserved2)==120,"DECL u_conduct.reserved2 offset");
_Static_assert(offsetof(struct u_conduct,reserved3)==128,"DECL u_conduct.reserved3 offset");
_Static_assert(offsetof(struct u_conduct,reserved4)==136,"DECL u_conduct.reserved4 offset");
_Static_assert(sizeof(struct u_event)==4,"DECL u_event size");
_Static_assert(sizeof(struct u_have)==4,"DECL u_have size");
_Static_assert(sizeof(struct u_realtime)==24,"DECL u_realtime size");
_Static_assert(offsetof(struct u_realtime,realtime)==0,"DECL u_realtime.realtime offset");
_Static_assert(offsetof(struct u_realtime,start_timing)==8,"DECL u_realtime.start_timing offset");
_Static_assert(offsetof(struct u_realtime,finish_time)==16,"DECL u_realtime.finish_time offset");
_Static_assert(sizeof(struct u_roleplay)==24,"DECL u_roleplay size");
_Static_assert(offsetof(struct u_roleplay,blind)==0,"DECL u_roleplay.blind offset");
_Static_assert(offsetof(struct u_roleplay,nudist)==1,"DECL u_roleplay.nudist offset");
_Static_assert(offsetof(struct u_roleplay,deaf)==2,"DECL u_roleplay.deaf offset");
_Static_assert(offsetof(struct u_roleplay,pauper)==3,"DECL u_roleplay.pauper offset");
_Static_assert(offsetof(struct u_roleplay,reroll)==4,"DECL u_roleplay.reroll offset");
_Static_assert(offsetof(struct u_roleplay,reserved1)==5,"DECL u_roleplay.reserved1 offset");
_Static_assert(offsetof(struct u_roleplay,reserved2)==6,"DECL u_roleplay.reserved2 offset");
_Static_assert(offsetof(struct u_roleplay,reserved3)==7,"DECL u_roleplay.reserved3 offset");
_Static_assert(offsetof(struct u_roleplay,numbones)==8,"DECL u_roleplay.numbones offset");
_Static_assert(offsetof(struct u_roleplay,numrerolls)==16,"DECL u_roleplay.numrerolls offset");
_Static_assert(sizeof(struct val_list)==16,"DECL val_list size");
_Static_assert(offsetof(struct val_list,list)==0,"DECL val_list.list offset");
_Static_assert(offsetof(struct val_list,size)==8,"DECL val_list.size offset");
_Static_assert(sizeof(struct valuable_data)==16,"DECL valuable_data size");
_Static_assert(offsetof(struct valuable_data,count)==0,"DECL valuable_data.count offset");
_Static_assert(offsetof(struct valuable_data,typ)==8,"DECL valuable_data.typ offset");
_Static_assert(sizeof(struct victual_info)==32,"DECL victual_info size");
_Static_assert(offsetof(struct victual_info,piece)==0,"DECL victual_info.piece offset");
_Static_assert(offsetof(struct victual_info,o_id)==8,"DECL victual_info.o_id offset");
_Static_assert(offsetof(struct victual_info,usedtime)==12,"DECL victual_info.usedtime offset");
_Static_assert(offsetof(struct victual_info,reqtime)==16,"DECL victual_info.reqtime offset");
_Static_assert(offsetof(struct victual_info,nmod)==20,"DECL victual_info.nmod offset");
_Static_assert(sizeof(union vptrs)==8,"DECL vptrs size");
_Static_assert(offsetof(union vptrs,v_nexthere)==0,"DECL vptrs.v_nexthere offset");
_Static_assert(offsetof(union vptrs,v_ocontainer)==0,"DECL vptrs.v_ocontainer offset");
_Static_assert(offsetof(union vptrs,v_ocarry)==0,"DECL vptrs.v_ocarry offset");
_Static_assert(sizeof(struct warntype_info)==32,"DECL warntype_info size");
_Static_assert(offsetof(struct warntype_info,obj)==0,"DECL warntype_info.obj offset");
_Static_assert(offsetof(struct warntype_info,polyd)==8,"DECL warntype_info.polyd offset");
_Static_assert(offsetof(struct warntype_info,species)==16,"DECL warntype_info.species offset");
_Static_assert(offsetof(struct warntype_info,speciesidx)==24,"DECL warntype_info.speciesidx offset");
_Static_assert(sizeof(struct win_settings)==8,"DECL win_settings size");
_Static_assert(offsetof(struct win_settings,wdmode)==0,"DECL win_settings.wdmode offset");
_Static_assert(offsetof(struct win_settings,map_frame_color)==4,"DECL win_settings.map_frame_color offset");
_Static_assert(sizeof(struct windowcolors_struct)==16,"DECL windowcolors_struct size");
_Static_assert(offsetof(struct windowcolors_struct,fg)==0,"DECL windowcolors_struct.fg offset");
_Static_assert(offsetof(struct windowcolors_struct,bg)==8,"DECL windowcolors_struct.bg offset");
_Static_assert(sizeof(struct xlock_s)==32,"DECL xlock_s size");
_Static_assert(offsetof(struct xlock_s,door)==0,"DECL xlock_s.door offset");
_Static_assert(offsetof(struct xlock_s,box)==8,"DECL xlock_s.box offset");
_Static_assert(offsetof(struct xlock_s,picktyp)==16,"DECL xlock_s.picktyp offset");
_Static_assert(offsetof(struct xlock_s,chance)==20,"DECL xlock_s.chance offset");
_Static_assert(offsetof(struct xlock_s,usedtime)==24,"DECL xlock_s.usedtime offset");
_Static_assert(offsetof(struct xlock_s,magic_key)==28,"DECL xlock_s.magic_key offset");
_Static_assert(sizeof(struct you)==2760,"DECL you size");
_Static_assert(offsetof(struct you,ux)==0,"DECL you.ux offset");
_Static_assert(offsetof(struct you,uy)==2,"DECL you.uy offset");
_Static_assert(offsetof(struct you,dx)==4,"DECL you.dx offset");
_Static_assert(offsetof(struct you,dy)==8,"DECL you.dy offset");
_Static_assert(offsetof(struct you,dz)==12,"DECL you.dz offset");
_Static_assert(offsetof(struct you,tx)==16,"DECL you.tx offset");
_Static_assert(offsetof(struct you,ty)==18,"DECL you.ty offset");
_Static_assert(offsetof(struct you,ux0)==20,"DECL you.ux0 offset");
_Static_assert(offsetof(struct you,uy0)==22,"DECL you.uy0 offset");
_Static_assert(offsetof(struct you,uz)==24,"DECL you.uz offset");
_Static_assert(offsetof(struct you,uz0)==28,"DECL you.uz0 offset");
_Static_assert(offsetof(struct you,utolev)==32,"DECL you.utolev offset");
_Static_assert(offsetof(struct you,utotype)==36,"DECL you.utotype offset");
_Static_assert(offsetof(struct you,ucamefrom)==38,"DECL you.ucamefrom offset");
_Static_assert(offsetof(struct you,umoved)==42,"DECL you.umoved offset");
_Static_assert(offsetof(struct you,last_str_turn)==44,"DECL you.last_str_turn offset");
_Static_assert(offsetof(struct you,ulevel)==48,"DECL you.ulevel offset");
_Static_assert(offsetof(struct you,ulevelmax)==52,"DECL you.ulevelmax offset");
_Static_assert(offsetof(struct you,ulevelpeak)==56,"DECL you.ulevelpeak offset");
_Static_assert(offsetof(struct you,utrap)==60,"DECL you.utrap offset");
_Static_assert(offsetof(struct you,utraptype)==64,"DECL you.utraptype offset");
_Static_assert(offsetof(struct you,urooms)==68,"DECL you.urooms offset");
_Static_assert(offsetof(struct you,urooms0)==73,"DECL you.urooms0 offset");
_Static_assert(offsetof(struct you,uentered)==78,"DECL you.uentered offset");
_Static_assert(offsetof(struct you,ushops)==83,"DECL you.ushops offset");
_Static_assert(offsetof(struct you,ushops0)==88,"DECL you.ushops0 offset");
_Static_assert(offsetof(struct you,ushops_entered)==93,"DECL you.ushops_entered offset");
_Static_assert(offsetof(struct you,ushops_left)==98,"DECL you.ushops_left offset");
_Static_assert(offsetof(struct you,uhunger)==104,"DECL you.uhunger offset");
_Static_assert(offsetof(struct you,uhs)==108,"DECL you.uhs offset");
_Static_assert(offsetof(struct you,uprops)==112,"DECL you.uprops offset");
_Static_assert(offsetof(struct you,umconf)==1768,"DECL you.umconf offset");
_Static_assert(offsetof(struct you,nv_range)==1776,"DECL you.nv_range offset");
_Static_assert(offsetof(struct you,xray_range)==1780,"DECL you.xray_range offset");
_Static_assert(offsetof(struct you,unblind_telepat_range)==1784,"DECL you.unblind_telepat_range offset");
_Static_assert(offsetof(struct you,bglyph)==1788,"DECL you.bglyph offset");
_Static_assert(offsetof(struct you,cglyph)==1792,"DECL you.cglyph offset");
_Static_assert(offsetof(struct you,bc_order)==1796,"DECL you.bc_order offset");
_Static_assert(offsetof(struct you,bc_felt)==1800,"DECL you.bc_felt offset");
_Static_assert(offsetof(struct you,umonster)==1804,"DECL you.umonster offset");
_Static_assert(offsetof(struct you,umonnum)==1808,"DECL you.umonnum offset");
_Static_assert(offsetof(struct you,mh)==1812,"DECL you.mh offset");
_Static_assert(offsetof(struct you,mhmax)==1816,"DECL you.mhmax offset");
_Static_assert(offsetof(struct you,mtimedone)==1820,"DECL you.mtimedone offset");
_Static_assert(offsetof(struct you,macurr)==1824,"DECL you.macurr offset");
_Static_assert(offsetof(struct you,mamax)==1830,"DECL you.mamax offset");
_Static_assert(offsetof(struct you,ulycn)==1836,"DECL you.ulycn offset");
_Static_assert(offsetof(struct you,ucreamed)==1840,"DECL you.ucreamed offset");
_Static_assert(offsetof(struct you,uswldtim)==1844,"DECL you.uswldtim offset");
_Static_assert(offsetof(struct you,udg_cnt)==1852,"DECL you.udg_cnt offset");
_Static_assert(offsetof(struct you,uevent)==1856,"DECL you.uevent offset");
_Static_assert(offsetof(struct you,uhave)==1860,"DECL you.uhave offset");
_Static_assert(offsetof(struct you,uconduct)==1864,"DECL you.uconduct offset");
_Static_assert(offsetof(struct you,uroleplay)==2008,"DECL you.uroleplay offset");
_Static_assert(offsetof(struct you,acurr)==2032,"DECL you.acurr offset");
_Static_assert(offsetof(struct you,aexe)==2038,"DECL you.aexe offset");
_Static_assert(offsetof(struct you,abon)==2044,"DECL you.abon offset");
_Static_assert(offsetof(struct you,amax)==2050,"DECL you.amax offset");
_Static_assert(offsetof(struct you,atemp)==2056,"DECL you.atemp offset");
_Static_assert(offsetof(struct you,atime)==2062,"DECL you.atime offset");
_Static_assert(offsetof(struct you,ualign)==2068,"DECL you.ualign offset");
_Static_assert(offsetof(struct you,ualignbase)==2080,"DECL you.ualignbase offset");
_Static_assert(offsetof(struct you,uluck)==2082,"DECL you.uluck offset");
_Static_assert(offsetof(struct you,moreluck)==2083,"DECL you.moreluck offset");
_Static_assert(offsetof(struct you,uhitinc)==2084,"DECL you.uhitinc offset");
_Static_assert(offsetof(struct you,udaminc)==2085,"DECL you.udaminc offset");
_Static_assert(offsetof(struct you,uac)==2086,"DECL you.uac offset");
_Static_assert(offsetof(struct you,uspellprot)==2087,"DECL you.uspellprot offset");
_Static_assert(offsetof(struct you,usptime)==2088,"DECL you.usptime offset");
_Static_assert(offsetof(struct you,uspmtime)==2089,"DECL you.uspmtime offset");
_Static_assert(offsetof(struct you,uhp)==2092,"DECL you.uhp offset");
_Static_assert(offsetof(struct you,uhpmax)==2096,"DECL you.uhpmax offset");
_Static_assert(offsetof(struct you,uhppeak)==2100,"DECL you.uhppeak offset");
_Static_assert(offsetof(struct you,uen)==2104,"DECL you.uen offset");
_Static_assert(offsetof(struct you,uenmax)==2108,"DECL you.uenmax offset");
_Static_assert(offsetof(struct you,uenpeak)==2112,"DECL you.uenpeak offset");
_Static_assert(offsetof(struct you,uhpinc)==2116,"DECL you.uhpinc offset");
_Static_assert(offsetof(struct you,ueninc)==2176,"DECL you.ueninc offset");
_Static_assert(offsetof(struct you,ugangr)==2236,"DECL you.ugangr offset");
_Static_assert(offsetof(struct you,ugifts)==2240,"DECL you.ugifts offset");
_Static_assert(offsetof(struct you,ublessed)==2244,"DECL you.ublessed offset");
_Static_assert(offsetof(struct you,ublesscnt)==2248,"DECL you.ublesscnt offset");
_Static_assert(offsetof(struct you,umoney0)==2256,"DECL you.umoney0 offset");
_Static_assert(offsetof(struct you,uspare1)==2264,"DECL you.uspare1 offset");
_Static_assert(offsetof(struct you,uexp)==2272,"DECL you.uexp offset");
_Static_assert(offsetof(struct you,urexp)==2280,"DECL you.urexp offset");
_Static_assert(offsetof(struct you,ucleansed)==2288,"DECL you.ucleansed offset");
_Static_assert(offsetof(struct you,usleep)==2296,"DECL you.usleep offset");
_Static_assert(offsetof(struct you,uinvault)==2304,"DECL you.uinvault offset");
_Static_assert(offsetof(struct you,ustuck)==2312,"DECL you.ustuck offset");
_Static_assert(offsetof(struct you,usteed)==2320,"DECL you.usteed offset");
_Static_assert(offsetof(struct you,ustuck_mid)==2328,"DECL you.ustuck_mid offset");
_Static_assert(offsetof(struct you,usteed_mid)==2332,"DECL you.usteed_mid offset");
_Static_assert(offsetof(struct you,ugallop)==2336,"DECL you.ugallop offset");
_Static_assert(offsetof(struct you,urideturns)==2344,"DECL you.urideturns offset");
_Static_assert(offsetof(struct you,umortality)==2348,"DECL you.umortality offset");
_Static_assert(offsetof(struct you,ugrave_arise)==2352,"DECL you.ugrave_arise offset");
_Static_assert(offsetof(struct you,weapon_slots)==2356,"DECL you.weapon_slots offset");
_Static_assert(offsetof(struct you,skills_advanced)==2360,"DECL you.skills_advanced offset");
_Static_assert(offsetof(struct you,skill_record)==2364,"DECL you.skill_record offset");
_Static_assert(offsetof(struct you,weapon_skills)==2484,"DECL you.weapon_skills offset");
_Static_assert(offsetof(struct you,twoweap)==2712,"DECL you.twoweap offset");
_Static_assert(offsetof(struct you,mcham)==2714,"DECL you.mcham offset");
_Static_assert(offsetof(struct you,umovement)==2716,"DECL you.umovement offset");
_Static_assert(offsetof(struct you,uachieved)==2718,"DECL you.uachieved offset");
_Static_assert(offsetof(struct you,umonst)==2752,"DECL you.umonst offset");
static const struct {const char*name;uint64_t value;} decl_layout[]={
{"pointerSize",(uint64_t)(sizeof(void*))},
{"longSize",(uint64_t)(sizeof(long))},
{"intSize",(uint64_t)(sizeof(int))},
{"charSigned",(uint64_t)(((char)-1<0))},
{"littleEndian",(uint64_t)((__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__))},
{"WIN_ERR",(uint64_t)(WIN_ERR)},
{"MAXNROFROOMS",(uint64_t)(MAXNROFROOMS)},
{"size_nhcb_name",(uint64_t)(sizeof(nhcb_name))},
{"align_nhcb_name",(uint64_t)(__alignof__(nhcb_name))},
{"size_nhcb_counts",(uint64_t)(sizeof(nhcb_counts))},
{"align_nhcb_counts",(uint64_t)(__alignof__(nhcb_counts))},
{"size_c_color_names",(uint64_t)(sizeof(c_color_names))},
{"align_c_color_names",(uint64_t)(__alignof__(c_color_names))},
{"size_c_obj_colors",(uint64_t)(sizeof(c_obj_colors))},
{"align_c_obj_colors",(uint64_t)(__alignof__(c_obj_colors))},
{"size_c_common_strings",(uint64_t)(sizeof(c_common_strings))},
{"align_c_common_strings",(uint64_t)(__alignof__(c_common_strings))},
{"size_disclosure_options",(uint64_t)(sizeof(disclosure_options))},
{"align_disclosure_options",(uint64_t)(__alignof__(disclosure_options))},
{"size_emptystr",(uint64_t)(sizeof(emptystr))},
{"align_emptystr",(uint64_t)(__alignof__(emptystr))},
{"size_flags",(uint64_t)(sizeof(flags))},
{"align_flags",(uint64_t)(__alignof__(flags))},
{"size_hexdd",(uint64_t)(sizeof(hexdd))},
{"align_hexdd",(uint64_t)(__alignof__(hexdd))},
{"size_xdir",(uint64_t)(sizeof(xdir))},
{"align_xdir",(uint64_t)(__alignof__(xdir))},
{"size_ydir",(uint64_t)(sizeof(ydir))},
{"align_ydir",(uint64_t)(__alignof__(ydir))},
{"size_zdir",(uint64_t)(sizeof(zdir))},
{"align_zdir",(uint64_t)(__alignof__(zdir))},
{"size_dirs_ord",(uint64_t)(sizeof(dirs_ord))},
{"align_dirs_ord",(uint64_t)(__alignof__(dirs_ord))},
{"size_has_strong_rngseed",(uint64_t)(sizeof(has_strong_rngseed))},
{"align_has_strong_rngseed",(uint64_t)(__alignof__(has_strong_rngseed))},
{"size_head_engr",(uint64_t)(sizeof(head_engr))},
{"align_head_engr",(uint64_t)(__alignof__(head_engr))},
{"size_iflags",(uint64_t)(sizeof(iflags))},
{"align_iflags",(uint64_t)(__alignof__(iflags))},
{"size_a11y",(uint64_t)(sizeof(a11y))},
{"align_a11y",(uint64_t)(__alignof__(a11y))},
{"size_materialnm",(uint64_t)(sizeof(materialnm))},
{"align_materialnm",(uint64_t)(__alignof__(materialnm))},
{"size_quitchars",(uint64_t)(sizeof(quitchars))},
{"align_quitchars",(uint64_t)(__alignof__(quitchars))},
{"size_shield_static",(uint64_t)(sizeof(shield_static))},
{"align_shield_static",(uint64_t)(__alignof__(shield_static))},
{"size_u",(uint64_t)(sizeof(u))},
{"align_u",(uint64_t)(__alignof__(u))},
{"size_ubirthday",(uint64_t)(sizeof(ubirthday))},
{"align_ubirthday",(uint64_t)(__alignof__(ubirthday))},
{"size_urealtime",(uint64_t)(sizeof(urealtime))},
{"align_urealtime",(uint64_t)(__alignof__(urealtime))},
{"size_uwep",(uint64_t)(sizeof(uwep))},
{"align_uwep",(uint64_t)(__alignof__(uwep))},
{"size_uarm",(uint64_t)(sizeof(uarm))},
{"align_uarm",(uint64_t)(__alignof__(uarm))},
{"size_uswapwep",(uint64_t)(sizeof(uswapwep))},
{"align_uswapwep",(uint64_t)(__alignof__(uswapwep))},
{"size_uquiver",(uint64_t)(sizeof(uquiver))},
{"align_uquiver",(uint64_t)(__alignof__(uquiver))},
{"size_uarmu",(uint64_t)(sizeof(uarmu))},
{"align_uarmu",(uint64_t)(__alignof__(uarmu))},
{"size_uskin",(uint64_t)(sizeof(uskin))},
{"align_uskin",(uint64_t)(__alignof__(uskin))},
{"size_uarmc",(uint64_t)(sizeof(uarmc))},
{"align_uarmc",(uint64_t)(__alignof__(uarmc))},
{"size_uarmh",(uint64_t)(sizeof(uarmh))},
{"align_uarmh",(uint64_t)(__alignof__(uarmh))},
{"size_uarms",(uint64_t)(sizeof(uarms))},
{"align_uarms",(uint64_t)(__alignof__(uarms))},
{"size_uarmg",(uint64_t)(sizeof(uarmg))},
{"align_uarmg",(uint64_t)(__alignof__(uarmg))},
{"size_uarmf",(uint64_t)(sizeof(uarmf))},
{"align_uarmf",(uint64_t)(__alignof__(uarmf))},
{"size_uamul",(uint64_t)(sizeof(uamul))},
{"align_uamul",(uint64_t)(__alignof__(uamul))},
{"size_uright",(uint64_t)(sizeof(uright))},
{"align_uright",(uint64_t)(__alignof__(uright))},
{"size_uleft",(uint64_t)(sizeof(uleft))},
{"align_uleft",(uint64_t)(__alignof__(uleft))},
{"size_ublindf",(uint64_t)(sizeof(ublindf))},
{"align_ublindf",(uint64_t)(__alignof__(ublindf))},
{"size_uchain",(uint64_t)(sizeof(uchain))},
{"align_uchain",(uint64_t)(__alignof__(uchain))},
{"size_uball",(uint64_t)(sizeof(uball))},
{"align_uball",(uint64_t)(__alignof__(uball))},
{"size_vowels",(uint64_t)(sizeof(vowels))},
{"align_vowels",(uint64_t)(__alignof__(vowels))},
{"size_WIN_MESSAGE",(uint64_t)(sizeof(WIN_MESSAGE))},
{"align_WIN_MESSAGE",(uint64_t)(__alignof__(WIN_MESSAGE))},
{"size_WIN_STATUS",(uint64_t)(sizeof(WIN_STATUS))},
{"align_WIN_STATUS",(uint64_t)(__alignof__(WIN_STATUS))},
{"size_WIN_MAP",(uint64_t)(sizeof(WIN_MAP))},
{"align_WIN_MAP",(uint64_t)(__alignof__(WIN_MAP))},
{"size_WIN_INVEN",(uint64_t)(sizeof(WIN_INVEN))},
{"align_WIN_INVEN",(uint64_t)(__alignof__(WIN_INVEN))},
{"size_ynchars",(uint64_t)(sizeof(ynchars))},
{"align_ynchars",(uint64_t)(__alignof__(ynchars))},
{"size_ynqchars",(uint64_t)(sizeof(ynqchars))},
{"align_ynqchars",(uint64_t)(__alignof__(ynqchars))},
{"size_ynaqchars",(uint64_t)(sizeof(ynaqchars))},
{"align_ynaqchars",(uint64_t)(__alignof__(ynaqchars))},
{"size_ynNaqchars",(uint64_t)(sizeof(ynNaqchars))},
{"align_ynNaqchars",(uint64_t)(__alignof__(ynNaqchars))},
{"size_rightleftchars",(uint64_t)(sizeof(rightleftchars))},
{"align_rightleftchars",(uint64_t)(__alignof__(rightleftchars))},
{"size_hidespinchars",(uint64_t)(sizeof(hidespinchars))},
{"align_hidespinchars",(uint64_t)(__alignof__(hidespinchars))},
{"size_yn_number",(uint64_t)(sizeof(yn_number))},
{"align_yn_number",(uint64_t)(__alignof__(yn_number))},
{"size_ARGV0",(uint64_t)(sizeof(ARGV0))},
{"align_ARGV0",(uint64_t)(__alignof__(ARGV0))},
{"size_urole_init_data",(uint64_t)(sizeof(teleport_decl_private_urole_init_data))},
{"align_urole_init_data",(uint64_t)(__alignof__(teleport_decl_private_urole_init_data))},
{"size_urace_init_data",(uint64_t)(sizeof(teleport_decl_private_urace_init_data))},
{"align_urace_init_data",(uint64_t)(__alignof__(teleport_decl_private_urace_init_data))},
{"size_disp",(uint64_t)(sizeof(disp))},
{"align_disp",(uint64_t)(__alignof__(disp))},
{"size_g_init_a",(uint64_t)(sizeof(teleport_decl_private_g_init_a))},
{"align_g_init_a",(uint64_t)(__alignof__(teleport_decl_private_g_init_a))},
{"size_g_init_b",(uint64_t)(sizeof(teleport_decl_private_g_init_b))},
{"align_g_init_b",(uint64_t)(__alignof__(teleport_decl_private_g_init_b))},
{"size_g_init_c",(uint64_t)(sizeof(teleport_decl_private_g_init_c))},
{"align_g_init_c",(uint64_t)(__alignof__(teleport_decl_private_g_init_c))},
{"size_g_init_d",(uint64_t)(sizeof(teleport_decl_private_g_init_d))},
{"align_g_init_d",(uint64_t)(__alignof__(teleport_decl_private_g_init_d))},
{"size_g_init_e",(uint64_t)(sizeof(teleport_decl_private_g_init_e))},
{"align_g_init_e",(uint64_t)(__alignof__(teleport_decl_private_g_init_e))},
{"size_g_init_f",(uint64_t)(sizeof(teleport_decl_private_g_init_f))},
{"align_g_init_f",(uint64_t)(__alignof__(teleport_decl_private_g_init_f))},
{"size_g_init_g",(uint64_t)(sizeof(teleport_decl_private_g_init_g))},
{"align_g_init_g",(uint64_t)(__alignof__(teleport_decl_private_g_init_g))},
{"size_g_init_h",(uint64_t)(sizeof(teleport_decl_private_g_init_h))},
{"align_g_init_h",(uint64_t)(__alignof__(teleport_decl_private_g_init_h))},
{"size_g_init_i",(uint64_t)(sizeof(teleport_decl_private_g_init_i))},
{"align_g_init_i",(uint64_t)(__alignof__(teleport_decl_private_g_init_i))},
{"size_g_init_j",(uint64_t)(sizeof(teleport_decl_private_g_init_j))},
{"align_g_init_j",(uint64_t)(__alignof__(teleport_decl_private_g_init_j))},
{"size_g_init_k",(uint64_t)(sizeof(teleport_decl_private_g_init_k))},
{"align_g_init_k",(uint64_t)(__alignof__(teleport_decl_private_g_init_k))},
{"size_g_init_l",(uint64_t)(sizeof(teleport_decl_private_g_init_l))},
{"align_g_init_l",(uint64_t)(__alignof__(teleport_decl_private_g_init_l))},
{"size_g_init_m",(uint64_t)(sizeof(teleport_decl_private_g_init_m))},
{"align_g_init_m",(uint64_t)(__alignof__(teleport_decl_private_g_init_m))},
{"size_g_init_n",(uint64_t)(sizeof(teleport_decl_private_g_init_n))},
{"align_g_init_n",(uint64_t)(__alignof__(teleport_decl_private_g_init_n))},
{"size_g_init_o",(uint64_t)(sizeof(teleport_decl_private_g_init_o))},
{"align_g_init_o",(uint64_t)(__alignof__(teleport_decl_private_g_init_o))},
{"size_g_init_p",(uint64_t)(sizeof(teleport_decl_private_g_init_p))},
{"align_g_init_p",(uint64_t)(__alignof__(teleport_decl_private_g_init_p))},
{"size_g_init_q",(uint64_t)(sizeof(teleport_decl_private_g_init_q))},
{"align_g_init_q",(uint64_t)(__alignof__(teleport_decl_private_g_init_q))},
{"size_g_init_r",(uint64_t)(sizeof(teleport_decl_private_g_init_r))},
{"align_g_init_r",(uint64_t)(__alignof__(teleport_decl_private_g_init_r))},
{"size_g_init_s",(uint64_t)(sizeof(teleport_decl_private_g_init_s))},
{"align_g_init_s",(uint64_t)(__alignof__(teleport_decl_private_g_init_s))},
{"size_g_init_t",(uint64_t)(sizeof(teleport_decl_private_g_init_t))},
{"align_g_init_t",(uint64_t)(__alignof__(teleport_decl_private_g_init_t))},
{"size_g_init_u",(uint64_t)(sizeof(teleport_decl_private_g_init_u))},
{"align_g_init_u",(uint64_t)(__alignof__(teleport_decl_private_g_init_u))},
{"size_g_init_v",(uint64_t)(sizeof(teleport_decl_private_g_init_v))},
{"align_g_init_v",(uint64_t)(__alignof__(teleport_decl_private_g_init_v))},
{"size_g_init_w",(uint64_t)(sizeof(teleport_decl_private_g_init_w))},
{"align_g_init_w",(uint64_t)(__alignof__(teleport_decl_private_g_init_w))},
{"size_g_init_x",(uint64_t)(sizeof(teleport_decl_private_g_init_x))},
{"align_g_init_x",(uint64_t)(__alignof__(teleport_decl_private_g_init_x))},
{"size_g_init_y",(uint64_t)(sizeof(teleport_decl_private_g_init_y))},
{"align_g_init_y",(uint64_t)(__alignof__(teleport_decl_private_g_init_y))},
{"size_g_init_z",(uint64_t)(sizeof(teleport_decl_private_g_init_z))},
{"align_g_init_z",(uint64_t)(__alignof__(teleport_decl_private_g_init_z))},
{"size_init_svb",(uint64_t)(sizeof(teleport_decl_private_init_svb))},
{"align_init_svb",(uint64_t)(__alignof__(teleport_decl_private_init_svb))},
{"size_init_svc",(uint64_t)(sizeof(teleport_decl_private_init_svc))},
{"align_init_svc",(uint64_t)(__alignof__(teleport_decl_private_init_svc))},
{"size_init_svd",(uint64_t)(sizeof(teleport_decl_private_init_svd))},
{"align_init_svd",(uint64_t)(__alignof__(teleport_decl_private_init_svd))},
{"size_init_sve",(uint64_t)(sizeof(teleport_decl_private_init_sve))},
{"align_init_sve",(uint64_t)(__alignof__(teleport_decl_private_init_sve))},
{"size_init_svh",(uint64_t)(sizeof(teleport_decl_private_init_svh))},
{"align_init_svh",(uint64_t)(__alignof__(teleport_decl_private_init_svh))},
{"size_init_svi",(uint64_t)(sizeof(teleport_decl_private_init_svi))},
{"align_init_svi",(uint64_t)(__alignof__(teleport_decl_private_init_svi))},
{"size_init_svk",(uint64_t)(sizeof(teleport_decl_private_init_svk))},
{"align_init_svk",(uint64_t)(__alignof__(teleport_decl_private_init_svk))},
{"size_init_svl",(uint64_t)(sizeof(teleport_decl_private_init_svl))},
{"align_init_svl",(uint64_t)(__alignof__(teleport_decl_private_init_svl))},
{"size_init_svm",(uint64_t)(sizeof(teleport_decl_private_init_svm))},
{"align_init_svm",(uint64_t)(__alignof__(teleport_decl_private_init_svm))},
{"size_init_svn",(uint64_t)(sizeof(teleport_decl_private_init_svn))},
{"align_init_svn",(uint64_t)(__alignof__(teleport_decl_private_init_svn))},
{"size_init_svo",(uint64_t)(sizeof(teleport_decl_private_init_svo))},
{"align_init_svo",(uint64_t)(__alignof__(teleport_decl_private_init_svo))},
{"size_init_svp",(uint64_t)(sizeof(teleport_decl_private_init_svp))},
{"align_init_svp",(uint64_t)(__alignof__(teleport_decl_private_init_svp))},
{"size_init_svq",(uint64_t)(sizeof(teleport_decl_private_init_svq))},
{"align_init_svq",(uint64_t)(__alignof__(teleport_decl_private_init_svq))},
{"size_init_svr",(uint64_t)(sizeof(teleport_decl_private_init_svr))},
{"align_init_svr",(uint64_t)(__alignof__(teleport_decl_private_init_svr))},
{"size_init_svs",(uint64_t)(sizeof(teleport_decl_private_init_svs))},
{"align_init_svs",(uint64_t)(__alignof__(teleport_decl_private_init_svs))},
{"size_init_svt",(uint64_t)(sizeof(teleport_decl_private_init_svt))},
{"align_init_svt",(uint64_t)(__alignof__(teleport_decl_private_init_svt))},
{"size_init_svu",(uint64_t)(sizeof(teleport_decl_private_init_svu))},
{"align_init_svu",(uint64_t)(__alignof__(teleport_decl_private_init_svu))},
{"size_init_svx",(uint64_t)(sizeof(teleport_decl_private_init_svx))},
{"align_init_svx",(uint64_t)(__alignof__(teleport_decl_private_init_svx))},
{"size_init_svw",(uint64_t)(sizeof(teleport_decl_private_init_svw))},
{"align_init_svw",(uint64_t)(__alignof__(teleport_decl_private_init_svw))},
{"size_init_svy",(uint64_t)(sizeof(teleport_decl_private_init_svy))},
{"align_init_svy",(uint64_t)(__alignof__(teleport_decl_private_init_svy))},
{"size_init_program_state",(uint64_t)(sizeof(teleport_decl_private_init_program_state))},
{"align_init_program_state",(uint64_t)(__alignof__(teleport_decl_private_init_program_state))},
{"size_ga",(uint64_t)(sizeof(ga))},
{"align_ga",(uint64_t)(__alignof__(ga))},
{"size_gb",(uint64_t)(sizeof(gb))},
{"align_gb",(uint64_t)(__alignof__(gb))},
{"size_gc",(uint64_t)(sizeof(gc))},
{"align_gc",(uint64_t)(__alignof__(gc))},
{"size_gd",(uint64_t)(sizeof(gd))},
{"align_gd",(uint64_t)(__alignof__(gd))},
{"size_ge",(uint64_t)(sizeof(ge))},
{"align_ge",(uint64_t)(__alignof__(ge))},
{"size_gf",(uint64_t)(sizeof(gf))},
{"align_gf",(uint64_t)(__alignof__(gf))},
{"size_gg",(uint64_t)(sizeof(gg))},
{"align_gg",(uint64_t)(__alignof__(gg))},
{"size_gh",(uint64_t)(sizeof(gh))},
{"align_gh",(uint64_t)(__alignof__(gh))},
{"size_gi",(uint64_t)(sizeof(gi))},
{"align_gi",(uint64_t)(__alignof__(gi))},
{"size_gj",(uint64_t)(sizeof(gj))},
{"align_gj",(uint64_t)(__alignof__(gj))},
{"size_gk",(uint64_t)(sizeof(gk))},
{"align_gk",(uint64_t)(__alignof__(gk))},
{"size_gl",(uint64_t)(sizeof(gl))},
{"align_gl",(uint64_t)(__alignof__(gl))},
{"size_gm",(uint64_t)(sizeof(gm))},
{"align_gm",(uint64_t)(__alignof__(gm))},
{"size_gn",(uint64_t)(sizeof(gn))},
{"align_gn",(uint64_t)(__alignof__(gn))},
{"size_go",(uint64_t)(sizeof(go))},
{"align_go",(uint64_t)(__alignof__(go))},
{"size_gp",(uint64_t)(sizeof(gp))},
{"align_gp",(uint64_t)(__alignof__(gp))},
{"size_gq",(uint64_t)(sizeof(gq))},
{"align_gq",(uint64_t)(__alignof__(gq))},
{"size_gr",(uint64_t)(sizeof(gr))},
{"align_gr",(uint64_t)(__alignof__(gr))},
{"size_gs",(uint64_t)(sizeof(gs))},
{"align_gs",(uint64_t)(__alignof__(gs))},
{"size_gt",(uint64_t)(sizeof(gt))},
{"align_gt",(uint64_t)(__alignof__(gt))},
{"size_gu",(uint64_t)(sizeof(gu))},
{"align_gu",(uint64_t)(__alignof__(gu))},
{"size_gv",(uint64_t)(sizeof(gv))},
{"align_gv",(uint64_t)(__alignof__(gv))},
{"size_gw",(uint64_t)(sizeof(gw))},
{"align_gw",(uint64_t)(__alignof__(gw))},
{"size_gx",(uint64_t)(sizeof(gx))},
{"align_gx",(uint64_t)(__alignof__(gx))},
{"size_gy",(uint64_t)(sizeof(gy))},
{"align_gy",(uint64_t)(__alignof__(gy))},
{"size_gz",(uint64_t)(sizeof(gz))},
{"align_gz",(uint64_t)(__alignof__(gz))},
{"size_svb",(uint64_t)(sizeof(svb))},
{"align_svb",(uint64_t)(__alignof__(svb))},
{"size_svc",(uint64_t)(sizeof(svc))},
{"align_svc",(uint64_t)(__alignof__(svc))},
{"size_svd",(uint64_t)(sizeof(svd))},
{"align_svd",(uint64_t)(__alignof__(svd))},
{"size_sve",(uint64_t)(sizeof(sve))},
{"align_sve",(uint64_t)(__alignof__(sve))},
{"size_svh",(uint64_t)(sizeof(svh))},
{"align_svh",(uint64_t)(__alignof__(svh))},
{"size_svi",(uint64_t)(sizeof(svi))},
{"align_svi",(uint64_t)(__alignof__(svi))},
{"size_svk",(uint64_t)(sizeof(svk))},
{"align_svk",(uint64_t)(__alignof__(svk))},
{"size_svl",(uint64_t)(sizeof(svl))},
{"align_svl",(uint64_t)(__alignof__(svl))},
{"size_svm",(uint64_t)(sizeof(svm))},
{"align_svm",(uint64_t)(__alignof__(svm))},
{"size_svn",(uint64_t)(sizeof(svn))},
{"align_svn",(uint64_t)(__alignof__(svn))},
{"size_svo",(uint64_t)(sizeof(svo))},
{"align_svo",(uint64_t)(__alignof__(svo))},
{"size_svp",(uint64_t)(sizeof(svp))},
{"align_svp",(uint64_t)(__alignof__(svp))},
{"size_svq",(uint64_t)(sizeof(svq))},
{"align_svq",(uint64_t)(__alignof__(svq))},
{"size_svr",(uint64_t)(sizeof(svr))},
{"align_svr",(uint64_t)(__alignof__(svr))},
{"size_svs",(uint64_t)(sizeof(svs))},
{"align_svs",(uint64_t)(__alignof__(svs))},
{"size_svt",(uint64_t)(sizeof(svt))},
{"align_svt",(uint64_t)(__alignof__(svt))},
{"size_svu",(uint64_t)(sizeof(svu))},
{"align_svu",(uint64_t)(__alignof__(svu))},
{"size_svw",(uint64_t)(sizeof(svw))},
{"align_svw",(uint64_t)(__alignof__(svw))},
{"size_svx",(uint64_t)(sizeof(svx))},
{"align_svx",(uint64_t)(__alignof__(svx))},
{"size_svy",(uint64_t)(sizeof(svy))},
{"align_svy",(uint64_t)(__alignof__(svy))},
{"size_program_state",(uint64_t)(sizeof(program_state))},
{"align_program_state",(uint64_t)(__alignof__(program_state))},
{"size_cg",(uint64_t)(sizeof(cg))},
{"align_cg",(uint64_t)(__alignof__(cg))},
{"size_hands_obj",(uint64_t)(sizeof(hands_obj))},
{"align_hands_obj",(uint64_t)(__alignof__(hands_obj))},
{"size_Race",(uint64_t)(sizeof(struct Race))},
{"align_Race",(uint64_t)(__alignof__(struct Race))},
{"offset_Race_noun",(uint64_t)(offsetof(struct Race,noun))},
{"width_Race_noun",(uint64_t)(sizeof(((struct Race*)0)->noun))},
{"offset_Race_adj",(uint64_t)(offsetof(struct Race,adj))},
{"width_Race_adj",(uint64_t)(sizeof(((struct Race*)0)->adj))},
{"offset_Race_coll",(uint64_t)(offsetof(struct Race,coll))},
{"width_Race_coll",(uint64_t)(sizeof(((struct Race*)0)->coll))},
{"offset_Race_filecode",(uint64_t)(offsetof(struct Race,filecode))},
{"width_Race_filecode",(uint64_t)(sizeof(((struct Race*)0)->filecode))},
{"offset_Race_individual",(uint64_t)(offsetof(struct Race,individual))},
{"width_Race_individual",(uint64_t)(sizeof(((struct Race*)0)->individual))},
{"offset_Race_mnum",(uint64_t)(offsetof(struct Race,mnum))},
{"width_Race_mnum",(uint64_t)(sizeof(((struct Race*)0)->mnum))},
{"offset_Race_mummynum",(uint64_t)(offsetof(struct Race,mummynum))},
{"width_Race_mummynum",(uint64_t)(sizeof(((struct Race*)0)->mummynum))},
{"offset_Race_zombienum",(uint64_t)(offsetof(struct Race,zombienum))},
{"width_Race_zombienum",(uint64_t)(sizeof(((struct Race*)0)->zombienum))},
{"offset_Race_allow",(uint64_t)(offsetof(struct Race,allow))},
{"width_Race_allow",(uint64_t)(sizeof(((struct Race*)0)->allow))},
{"offset_Race_selfmask",(uint64_t)(offsetof(struct Race,selfmask))},
{"width_Race_selfmask",(uint64_t)(sizeof(((struct Race*)0)->selfmask))},
{"offset_Race_lovemask",(uint64_t)(offsetof(struct Race,lovemask))},
{"width_Race_lovemask",(uint64_t)(sizeof(((struct Race*)0)->lovemask))},
{"offset_Race_hatemask",(uint64_t)(offsetof(struct Race,hatemask))},
{"width_Race_hatemask",(uint64_t)(sizeof(((struct Race*)0)->hatemask))},
{"offset_Race_attrmin",(uint64_t)(offsetof(struct Race,attrmin))},
{"width_Race_attrmin",(uint64_t)(sizeof(((struct Race*)0)->attrmin))},
{"offset_Race_attrmax",(uint64_t)(offsetof(struct Race,attrmax))},
{"width_Race_attrmax",(uint64_t)(sizeof(((struct Race*)0)->attrmax))},
{"offset_Race_hpadv",(uint64_t)(offsetof(struct Race,hpadv))},
{"width_Race_hpadv",(uint64_t)(sizeof(((struct Race*)0)->hpadv))},
{"offset_Race_enadv",(uint64_t)(offsetof(struct Race,enadv))},
{"width_Race_enadv",(uint64_t)(sizeof(((struct Race*)0)->enadv))},
{"size_Role",(uint64_t)(sizeof(struct Role))},
{"align_Role",(uint64_t)(__alignof__(struct Role))},
{"offset_Role_name",(uint64_t)(offsetof(struct Role,name))},
{"width_Role_name",(uint64_t)(sizeof(((struct Role*)0)->name))},
{"offset_Role_rank",(uint64_t)(offsetof(struct Role,rank))},
{"width_Role_rank",(uint64_t)(sizeof(((struct Role*)0)->rank))},
{"offset_Role_lgod",(uint64_t)(offsetof(struct Role,lgod))},
{"width_Role_lgod",(uint64_t)(sizeof(((struct Role*)0)->lgod))},
{"offset_Role_ngod",(uint64_t)(offsetof(struct Role,ngod))},
{"width_Role_ngod",(uint64_t)(sizeof(((struct Role*)0)->ngod))},
{"offset_Role_cgod",(uint64_t)(offsetof(struct Role,cgod))},
{"width_Role_cgod",(uint64_t)(sizeof(((struct Role*)0)->cgod))},
{"offset_Role_filecode",(uint64_t)(offsetof(struct Role,filecode))},
{"width_Role_filecode",(uint64_t)(sizeof(((struct Role*)0)->filecode))},
{"offset_Role_homebase",(uint64_t)(offsetof(struct Role,homebase))},
{"width_Role_homebase",(uint64_t)(sizeof(((struct Role*)0)->homebase))},
{"offset_Role_intermed",(uint64_t)(offsetof(struct Role,intermed))},
{"width_Role_intermed",(uint64_t)(sizeof(((struct Role*)0)->intermed))},
{"offset_Role_mnum",(uint64_t)(offsetof(struct Role,mnum))},
{"width_Role_mnum",(uint64_t)(sizeof(((struct Role*)0)->mnum))},
{"offset_Role_petnum",(uint64_t)(offsetof(struct Role,petnum))},
{"width_Role_petnum",(uint64_t)(sizeof(((struct Role*)0)->petnum))},
{"offset_Role_ldrnum",(uint64_t)(offsetof(struct Role,ldrnum))},
{"width_Role_ldrnum",(uint64_t)(sizeof(((struct Role*)0)->ldrnum))},
{"offset_Role_guardnum",(uint64_t)(offsetof(struct Role,guardnum))},
{"width_Role_guardnum",(uint64_t)(sizeof(((struct Role*)0)->guardnum))},
{"offset_Role_neminum",(uint64_t)(offsetof(struct Role,neminum))},
{"width_Role_neminum",(uint64_t)(sizeof(((struct Role*)0)->neminum))},
{"offset_Role_enemy1num",(uint64_t)(offsetof(struct Role,enemy1num))},
{"width_Role_enemy1num",(uint64_t)(sizeof(((struct Role*)0)->enemy1num))},
{"offset_Role_enemy2num",(uint64_t)(offsetof(struct Role,enemy2num))},
{"width_Role_enemy2num",(uint64_t)(sizeof(((struct Role*)0)->enemy2num))},
{"offset_Role_enemy1sym",(uint64_t)(offsetof(struct Role,enemy1sym))},
{"width_Role_enemy1sym",(uint64_t)(sizeof(((struct Role*)0)->enemy1sym))},
{"offset_Role_enemy2sym",(uint64_t)(offsetof(struct Role,enemy2sym))},
{"width_Role_enemy2sym",(uint64_t)(sizeof(((struct Role*)0)->enemy2sym))},
{"offset_Role_questarti",(uint64_t)(offsetof(struct Role,questarti))},
{"width_Role_questarti",(uint64_t)(sizeof(((struct Role*)0)->questarti))},
{"offset_Role_allow",(uint64_t)(offsetof(struct Role,allow))},
{"width_Role_allow",(uint64_t)(sizeof(((struct Role*)0)->allow))},
{"offset_Role_attrbase",(uint64_t)(offsetof(struct Role,attrbase))},
{"width_Role_attrbase",(uint64_t)(sizeof(((struct Role*)0)->attrbase))},
{"offset_Role_attrdist",(uint64_t)(offsetof(struct Role,attrdist))},
{"width_Role_attrdist",(uint64_t)(sizeof(((struct Role*)0)->attrdist))},
{"offset_Role_hpadv",(uint64_t)(offsetof(struct Role,hpadv))},
{"width_Role_hpadv",(uint64_t)(sizeof(((struct Role*)0)->hpadv))},
{"offset_Role_enadv",(uint64_t)(offsetof(struct Role,enadv))},
{"width_Role_enadv",(uint64_t)(sizeof(((struct Role*)0)->enadv))},
{"offset_Role_xlev",(uint64_t)(offsetof(struct Role,xlev))},
{"width_Role_xlev",(uint64_t)(sizeof(((struct Role*)0)->xlev))},
{"offset_Role_initrecord",(uint64_t)(offsetof(struct Role,initrecord))},
{"width_Role_initrecord",(uint64_t)(sizeof(((struct Role*)0)->initrecord))},
{"offset_Role_spelbase",(uint64_t)(offsetof(struct Role,spelbase))},
{"width_Role_spelbase",(uint64_t)(sizeof(((struct Role*)0)->spelbase))},
{"offset_Role_spelheal",(uint64_t)(offsetof(struct Role,spelheal))},
{"width_Role_spelheal",(uint64_t)(sizeof(((struct Role*)0)->spelheal))},
{"offset_Role_spelshld",(uint64_t)(offsetof(struct Role,spelshld))},
{"width_Role_spelshld",(uint64_t)(sizeof(((struct Role*)0)->spelshld))},
{"offset_Role_spelarmr",(uint64_t)(offsetof(struct Role,spelarmr))},
{"width_Role_spelarmr",(uint64_t)(sizeof(((struct Role*)0)->spelarmr))},
{"offset_Role_spelstat",(uint64_t)(offsetof(struct Role,spelstat))},
{"width_Role_spelstat",(uint64_t)(sizeof(((struct Role*)0)->spelstat))},
{"offset_Role_spelspec",(uint64_t)(offsetof(struct Role,spelspec))},
{"width_Role_spelspec",(uint64_t)(sizeof(((struct Role*)0)->spelspec))},
{"offset_Role_spelsbon",(uint64_t)(offsetof(struct Role,spelsbon))},
{"width_Role_spelsbon",(uint64_t)(sizeof(((struct Role*)0)->spelsbon))},
{"size_RoleAdvance",(uint64_t)(sizeof(struct RoleAdvance))},
{"align_RoleAdvance",(uint64_t)(__alignof__(struct RoleAdvance))},
{"offset_RoleAdvance_infix",(uint64_t)(offsetof(struct RoleAdvance,infix))},
{"width_RoleAdvance_infix",(uint64_t)(sizeof(((struct RoleAdvance*)0)->infix))},
{"offset_RoleAdvance_inrnd",(uint64_t)(offsetof(struct RoleAdvance,inrnd))},
{"width_RoleAdvance_inrnd",(uint64_t)(sizeof(((struct RoleAdvance*)0)->inrnd))},
{"offset_RoleAdvance_lofix",(uint64_t)(offsetof(struct RoleAdvance,lofix))},
{"width_RoleAdvance_lofix",(uint64_t)(sizeof(((struct RoleAdvance*)0)->lofix))},
{"offset_RoleAdvance_lornd",(uint64_t)(offsetof(struct RoleAdvance,lornd))},
{"width_RoleAdvance_lornd",(uint64_t)(sizeof(((struct RoleAdvance*)0)->lornd))},
{"offset_RoleAdvance_hifix",(uint64_t)(offsetof(struct RoleAdvance,hifix))},
{"width_RoleAdvance_hifix",(uint64_t)(sizeof(((struct RoleAdvance*)0)->hifix))},
{"offset_RoleAdvance_hirnd",(uint64_t)(offsetof(struct RoleAdvance,hirnd))},
{"width_RoleAdvance_hirnd",(uint64_t)(sizeof(((struct RoleAdvance*)0)->hirnd))},
{"size_RoleName",(uint64_t)(sizeof(struct RoleName))},
{"align_RoleName",(uint64_t)(__alignof__(struct RoleName))},
{"offset_RoleName_m",(uint64_t)(offsetof(struct RoleName,m))},
{"width_RoleName_m",(uint64_t)(sizeof(((struct RoleName*)0)->m))},
{"offset_RoleName_f",(uint64_t)(offsetof(struct RoleName,f))},
{"width_RoleName_f",(uint64_t)(sizeof(((struct RoleName*)0)->f))},
{"size_accessibility_data",(uint64_t)(sizeof(struct accessibility_data))},
{"align_accessibility_data",(uint64_t)(__alignof__(struct accessibility_data))},
{"offset_accessibility_data_accessiblemsg",(uint64_t)(offsetof(struct accessibility_data,accessiblemsg))},
{"width_accessibility_data_accessiblemsg",(uint64_t)(sizeof(((struct accessibility_data*)0)->accessiblemsg))},
{"offset_accessibility_data_msg_loc",(uint64_t)(offsetof(struct accessibility_data,msg_loc))},
{"width_accessibility_data_msg_loc",(uint64_t)(sizeof(((struct accessibility_data*)0)->msg_loc))},
{"offset_accessibility_data_mon_notices",(uint64_t)(offsetof(struct accessibility_data,mon_notices))},
{"width_accessibility_data_mon_notices",(uint64_t)(sizeof(((struct accessibility_data*)0)->mon_notices))},
{"offset_accessibility_data_mon_notices_blocked",(uint64_t)(offsetof(struct accessibility_data,mon_notices_blocked))},
{"width_accessibility_data_mon_notices_blocked",(uint64_t)(sizeof(((struct accessibility_data*)0)->mon_notices_blocked))},
{"offset_accessibility_data_mon_movement",(uint64_t)(offsetof(struct accessibility_data,mon_movement))},
{"width_accessibility_data_mon_movement",(uint64_t)(sizeof(((struct accessibility_data*)0)->mon_movement))},
{"offset_accessibility_data_glyph_updates",(uint64_t)(offsetof(struct accessibility_data,glyph_updates))},
{"width_accessibility_data_glyph_updates",(uint64_t)(sizeof(((struct accessibility_data*)0)->glyph_updates))},
{"size_achievement_tracking",(uint64_t)(sizeof(struct achievement_tracking))},
{"align_achievement_tracking",(uint64_t)(__alignof__(struct achievement_tracking))},
{"offset_achievement_tracking_mines_prize_oid",(uint64_t)(offsetof(struct achievement_tracking,mines_prize_oid))},
{"width_achievement_tracking_mines_prize_oid",(uint64_t)(sizeof(((struct achievement_tracking*)0)->mines_prize_oid))},
{"offset_achievement_tracking_soko_prize_oid",(uint64_t)(offsetof(struct achievement_tracking,soko_prize_oid))},
{"width_achievement_tracking_soko_prize_oid",(uint64_t)(sizeof(((struct achievement_tracking*)0)->soko_prize_oid))},
{"offset_achievement_tracking_castle_prize_old",(uint64_t)(offsetof(struct achievement_tracking,castle_prize_old))},
{"width_achievement_tracking_castle_prize_old",(uint64_t)(sizeof(((struct achievement_tracking*)0)->castle_prize_old))},
{"offset_achievement_tracking_mines_prize_otyp",(uint64_t)(offsetof(struct achievement_tracking,mines_prize_otyp))},
{"width_achievement_tracking_mines_prize_otyp",(uint64_t)(sizeof(((struct achievement_tracking*)0)->mines_prize_otyp))},
{"offset_achievement_tracking_soko_prize_otyp",(uint64_t)(offsetof(struct achievement_tracking,soko_prize_otyp))},
{"width_achievement_tracking_soko_prize_otyp",(uint64_t)(sizeof(((struct achievement_tracking*)0)->soko_prize_otyp))},
{"offset_achievement_tracking_castle_prize_otyp",(uint64_t)(offsetof(struct achievement_tracking,castle_prize_otyp))},
{"width_achievement_tracking_castle_prize_otyp",(uint64_t)(sizeof(((struct achievement_tracking*)0)->castle_prize_otyp))},
{"offset_achievement_tracking_minetn_reached",(uint64_t)(offsetof(struct achievement_tracking,minetn_reached))},
{"width_achievement_tracking_minetn_reached",(uint64_t)(sizeof(((struct achievement_tracking*)0)->minetn_reached))},
{"size_align",(uint64_t)(sizeof(struct align))},
{"align_align",(uint64_t)(__alignof__(struct align))},
{"offset_align_type",(uint64_t)(offsetof(struct align,type))},
{"width_align_type",(uint64_t)(sizeof(((struct align*)0)->type))},
{"offset_align_record",(uint64_t)(offsetof(struct align,record))},
{"width_align_record",(uint64_t)(sizeof(((struct align*)0)->record))},
{"offset_align_abuse",(uint64_t)(offsetof(struct align,abuse))},
{"width_align_abuse",(uint64_t)(sizeof(((struct align*)0)->abuse))},
{"size_anonymous_880_5",(uint64_t)(sizeof(__typeof__(((lev_region*)0)->inarea)))},
{"align_anonymous_880_5",(uint64_t)(__alignof__(__typeof__(((lev_region*)0)->inarea)))},
{"offset_anonymous_880_5_x1",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->inarea),x1))},
{"width_anonymous_880_5_x1",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->inarea)*)0)->x1))},
{"offset_anonymous_880_5_y1",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->inarea),y1))},
{"width_anonymous_880_5_y1",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->inarea)*)0)->y1))},
{"offset_anonymous_880_5_x2",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->inarea),x2))},
{"width_anonymous_880_5_x2",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->inarea)*)0)->x2))},
{"offset_anonymous_880_5_y2",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->inarea),y2))},
{"width_anonymous_880_5_y2",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->inarea)*)0)->y2))},
{"size_anonymous_883_5",(uint64_t)(sizeof(__typeof__(((lev_region*)0)->delarea)))},
{"align_anonymous_883_5",(uint64_t)(__alignof__(__typeof__(((lev_region*)0)->delarea)))},
{"offset_anonymous_883_5_x1",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->delarea),x1))},
{"width_anonymous_883_5_x1",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->delarea)*)0)->x1))},
{"offset_anonymous_883_5_y1",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->delarea),y1))},
{"width_anonymous_883_5_y1",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->delarea)*)0)->y1))},
{"offset_anonymous_883_5_x2",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->delarea),x2))},
{"width_anonymous_883_5_x2",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->delarea)*)0)->x2))},
{"offset_anonymous_883_5_y2",(uint64_t)(offsetof(__typeof__(((lev_region*)0)->delarea),y2))},
{"width_anonymous_883_5_y2",(uint64_t)(sizeof(((__typeof__(((lev_region*)0)->delarea)*)0)->y2))},
{"size_any",(uint64_t)(sizeof(union any))},
{"align_any",(uint64_t)(__alignof__(union any))},
{"offset_any_a_void",(uint64_t)(offsetof(union any,a_void))},
{"width_any_a_void",(uint64_t)(sizeof(((union any*)0)->a_void))},
{"offset_any_a_obj",(uint64_t)(offsetof(union any,a_obj))},
{"width_any_a_obj",(uint64_t)(sizeof(((union any*)0)->a_obj))},
{"offset_any_a_monst",(uint64_t)(offsetof(union any,a_monst))},
{"width_any_a_monst",(uint64_t)(sizeof(((union any*)0)->a_monst))},
{"offset_any_a_int",(uint64_t)(offsetof(union any,a_int))},
{"width_any_a_int",(uint64_t)(sizeof(((union any*)0)->a_int))},
{"offset_any_a_xint16",(uint64_t)(offsetof(union any,a_xint16))},
{"width_any_a_xint16",(uint64_t)(sizeof(((union any*)0)->a_xint16))},
{"offset_any_a_xint8",(uint64_t)(offsetof(union any,a_xint8))},
{"width_any_a_xint8",(uint64_t)(sizeof(((union any*)0)->a_xint8))},
{"offset_any_a_char",(uint64_t)(offsetof(union any,a_char))},
{"width_any_a_char",(uint64_t)(sizeof(((union any*)0)->a_char))},
{"offset_any_a_schar",(uint64_t)(offsetof(union any,a_schar))},
{"width_any_a_schar",(uint64_t)(sizeof(((union any*)0)->a_schar))},
{"offset_any_a_uchar",(uint64_t)(offsetof(union any,a_uchar))},
{"width_any_a_uchar",(uint64_t)(sizeof(((union any*)0)->a_uchar))},
{"offset_any_a_uint",(uint64_t)(offsetof(union any,a_uint))},
{"width_any_a_uint",(uint64_t)(sizeof(((union any*)0)->a_uint))},
{"offset_any_a_long",(uint64_t)(offsetof(union any,a_long))},
{"width_any_a_long",(uint64_t)(sizeof(((union any*)0)->a_long))},
{"offset_any_a_ulong",(uint64_t)(offsetof(union any,a_ulong))},
{"width_any_a_ulong",(uint64_t)(sizeof(((union any*)0)->a_ulong))},
{"offset_any_a_coordxy",(uint64_t)(offsetof(union any,a_coordxy))},
{"width_any_a_coordxy",(uint64_t)(sizeof(((union any*)0)->a_coordxy))},
{"offset_any_a_iptr",(uint64_t)(offsetof(union any,a_iptr))},
{"width_any_a_iptr",(uint64_t)(sizeof(((union any*)0)->a_iptr))},
{"offset_any_a_xint16ptr",(uint64_t)(offsetof(union any,a_xint16ptr))},
{"width_any_a_xint16ptr",(uint64_t)(sizeof(((union any*)0)->a_xint16ptr))},
{"offset_any_a_xint8ptr",(uint64_t)(offsetof(union any,a_xint8ptr))},
{"width_any_a_xint8ptr",(uint64_t)(sizeof(((union any*)0)->a_xint8ptr))},
{"offset_any_a_lptr",(uint64_t)(offsetof(union any,a_lptr))},
{"width_any_a_lptr",(uint64_t)(sizeof(((union any*)0)->a_lptr))},
{"offset_any_a_coordxyptr",(uint64_t)(offsetof(union any,a_coordxyptr))},
{"width_any_a_coordxyptr",(uint64_t)(sizeof(((union any*)0)->a_coordxyptr))},
{"offset_any_a_ulptr",(uint64_t)(offsetof(union any,a_ulptr))},
{"width_any_a_ulptr",(uint64_t)(sizeof(((union any*)0)->a_ulptr))},
{"offset_any_a_uptr",(uint64_t)(offsetof(union any,a_uptr))},
{"width_any_a_uptr",(uint64_t)(sizeof(((union any*)0)->a_uptr))},
{"offset_any_a_string",(uint64_t)(offsetof(union any,a_string))},
{"width_any_a_string",(uint64_t)(sizeof(((union any*)0)->a_string))},
{"offset_any_a_nfunc",(uint64_t)(offsetof(union any,a_nfunc))},
{"width_any_a_nfunc",(uint64_t)(sizeof(((union any*)0)->a_nfunc))},
{"offset_any_a_mask32",(uint64_t)(offsetof(union any,a_mask32))},
{"width_any_a_mask32",(uint64_t)(sizeof(((union any*)0)->a_mask32))},
{"offset_any_a_int64",(uint64_t)(offsetof(union any,a_int64))},
{"width_any_a_int64",(uint64_t)(sizeof(((union any*)0)->a_int64))},
{"offset_any_a_uint64",(uint64_t)(offsetof(union any,a_uint64))},
{"width_any_a_uint64",(uint64_t)(sizeof(((union any*)0)->a_uint64))},
{"size_attribs",(uint64_t)(sizeof(struct attribs))},
{"align_attribs",(uint64_t)(__alignof__(struct attribs))},
{"offset_attribs_a",(uint64_t)(offsetof(struct attribs,a))},
{"width_attribs_a",(uint64_t)(sizeof(((struct attribs*)0)->a))},
{"size_book_info",(uint64_t)(sizeof(struct book_info))},
{"align_book_info",(uint64_t)(__alignof__(struct book_info))},
{"offset_book_info_book",(uint64_t)(offsetof(struct book_info,book))},
{"width_book_info_book",(uint64_t)(sizeof(((struct book_info*)0)->book))},
{"offset_book_info_o_id",(uint64_t)(offsetof(struct book_info,o_id))},
{"width_book_info_o_id",(uint64_t)(sizeof(((struct book_info*)0)->o_id))},
{"offset_book_info_delay",(uint64_t)(offsetof(struct book_info,delay))},
{"width_book_info_delay",(uint64_t)(sizeof(((struct book_info*)0)->delay))},
{"size_c_color_names",(uint64_t)(sizeof(struct c_color_names))},
{"align_c_color_names",(uint64_t)(__alignof__(struct c_color_names))},
{"offset_c_color_names_c_black",(uint64_t)(offsetof(struct c_color_names,c_black))},
{"width_c_color_names_c_black",(uint64_t)(sizeof(((struct c_color_names*)0)->c_black))},
{"offset_c_color_names_c_amber",(uint64_t)(offsetof(struct c_color_names,c_amber))},
{"width_c_color_names_c_amber",(uint64_t)(sizeof(((struct c_color_names*)0)->c_amber))},
{"offset_c_color_names_c_golden",(uint64_t)(offsetof(struct c_color_names,c_golden))},
{"width_c_color_names_c_golden",(uint64_t)(sizeof(((struct c_color_names*)0)->c_golden))},
{"offset_c_color_names_c_light_blue",(uint64_t)(offsetof(struct c_color_names,c_light_blue))},
{"width_c_color_names_c_light_blue",(uint64_t)(sizeof(((struct c_color_names*)0)->c_light_blue))},
{"offset_c_color_names_c_red",(uint64_t)(offsetof(struct c_color_names,c_red))},
{"width_c_color_names_c_red",(uint64_t)(sizeof(((struct c_color_names*)0)->c_red))},
{"offset_c_color_names_c_green",(uint64_t)(offsetof(struct c_color_names,c_green))},
{"width_c_color_names_c_green",(uint64_t)(sizeof(((struct c_color_names*)0)->c_green))},
{"offset_c_color_names_c_silver",(uint64_t)(offsetof(struct c_color_names,c_silver))},
{"width_c_color_names_c_silver",(uint64_t)(sizeof(((struct c_color_names*)0)->c_silver))},
{"offset_c_color_names_c_blue",(uint64_t)(offsetof(struct c_color_names,c_blue))},
{"width_c_color_names_c_blue",(uint64_t)(sizeof(((struct c_color_names*)0)->c_blue))},
{"offset_c_color_names_c_purple",(uint64_t)(offsetof(struct c_color_names,c_purple))},
{"width_c_color_names_c_purple",(uint64_t)(sizeof(((struct c_color_names*)0)->c_purple))},
{"offset_c_color_names_c_white",(uint64_t)(offsetof(struct c_color_names,c_white))},
{"width_c_color_names_c_white",(uint64_t)(sizeof(((struct c_color_names*)0)->c_white))},
{"offset_c_color_names_c_orange",(uint64_t)(offsetof(struct c_color_names,c_orange))},
{"width_c_color_names_c_orange",(uint64_t)(sizeof(((struct c_color_names*)0)->c_orange))},
{"size_c_common_strings",(uint64_t)(sizeof(struct c_common_strings))},
{"align_c_common_strings",(uint64_t)(__alignof__(struct c_common_strings))},
{"offset_c_common_strings_c_nothing_happens",(uint64_t)(offsetof(struct c_common_strings,c_nothing_happens))},
{"width_c_common_strings_c_nothing_happens",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_nothing_happens))},
{"offset_c_common_strings_c_nothing_seems_to_happen",(uint64_t)(offsetof(struct c_common_strings,c_nothing_seems_to_happen))},
{"width_c_common_strings_c_nothing_seems_to_happen",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_nothing_seems_to_happen))},
{"offset_c_common_strings_c_thats_enough_tries",(uint64_t)(offsetof(struct c_common_strings,c_thats_enough_tries))},
{"width_c_common_strings_c_thats_enough_tries",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_thats_enough_tries))},
{"offset_c_common_strings_c_silly_thing_to",(uint64_t)(offsetof(struct c_common_strings,c_silly_thing_to))},
{"width_c_common_strings_c_silly_thing_to",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_silly_thing_to))},
{"offset_c_common_strings_c_shudder_for_moment",(uint64_t)(offsetof(struct c_common_strings,c_shudder_for_moment))},
{"width_c_common_strings_c_shudder_for_moment",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_shudder_for_moment))},
{"offset_c_common_strings_c_something",(uint64_t)(offsetof(struct c_common_strings,c_something))},
{"width_c_common_strings_c_something",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_something))},
{"offset_c_common_strings_c_Something",(uint64_t)(offsetof(struct c_common_strings,c_Something))},
{"width_c_common_strings_c_Something",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_Something))},
{"offset_c_common_strings_c_You_can_move_again",(uint64_t)(offsetof(struct c_common_strings,c_You_can_move_again))},
{"width_c_common_strings_c_You_can_move_again",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_You_can_move_again))},
{"offset_c_common_strings_c_Never_mind",(uint64_t)(offsetof(struct c_common_strings,c_Never_mind))},
{"width_c_common_strings_c_Never_mind",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_Never_mind))},
{"offset_c_common_strings_c_vision_clears",(uint64_t)(offsetof(struct c_common_strings,c_vision_clears))},
{"width_c_common_strings_c_vision_clears",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_vision_clears))},
{"offset_c_common_strings_c_the_your",(uint64_t)(offsetof(struct c_common_strings,c_the_your))},
{"width_c_common_strings_c_the_your",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_the_your))},
{"offset_c_common_strings_c_fakename",(uint64_t)(offsetof(struct c_common_strings,c_fakename))},
{"width_c_common_strings_c_fakename",(uint64_t)(sizeof(((struct c_common_strings*)0)->c_fakename))},
{"size_classic_representation",(uint64_t)(sizeof(struct classic_representation))},
{"align_classic_representation",(uint64_t)(__alignof__(struct classic_representation))},
{"offset_classic_representation_color",(uint64_t)(offsetof(struct classic_representation,color))},
{"width_classic_representation_color",(uint64_t)(sizeof(((struct classic_representation*)0)->color))},
{"offset_classic_representation_symidx",(uint64_t)(offsetof(struct classic_representation,symidx))},
{"width_classic_representation_symidx",(uint64_t)(sizeof(((struct classic_representation*)0)->symidx))},
{"size_cmd",(uint64_t)(sizeof(struct cmd))},
{"align_cmd",(uint64_t)(__alignof__(struct cmd))},
{"offset_cmd_serialno",(uint64_t)(offsetof(struct cmd,serialno))},
{"width_cmd_serialno",(uint64_t)(sizeof(((struct cmd*)0)->serialno))},
{"offset_cmd_num_pad",(uint64_t)(offsetof(struct cmd,num_pad))},
{"width_cmd_num_pad",(uint64_t)(sizeof(((struct cmd*)0)->num_pad))},
{"offset_cmd_pcHack_compat",(uint64_t)(offsetof(struct cmd,pcHack_compat))},
{"width_cmd_pcHack_compat",(uint64_t)(sizeof(((struct cmd*)0)->pcHack_compat))},
{"offset_cmd_phone_layout",(uint64_t)(offsetof(struct cmd,phone_layout))},
{"width_cmd_phone_layout",(uint64_t)(sizeof(((struct cmd*)0)->phone_layout))},
{"offset_cmd_swap_yz",(uint64_t)(offsetof(struct cmd,swap_yz))},
{"width_cmd_swap_yz",(uint64_t)(sizeof(((struct cmd*)0)->swap_yz))},
{"offset_cmd_dirchars",(uint64_t)(offsetof(struct cmd,dirchars))},
{"width_cmd_dirchars",(uint64_t)(sizeof(((struct cmd*)0)->dirchars))},
{"offset_cmd_alphadirchars",(uint64_t)(offsetof(struct cmd,alphadirchars))},
{"width_cmd_alphadirchars",(uint64_t)(sizeof(((struct cmd*)0)->alphadirchars))},
{"offset_cmd_cmdbinds",(uint64_t)(offsetof(struct cmd,cmdbinds))},
{"width_cmd_cmdbinds",(uint64_t)(sizeof(((struct cmd*)0)->cmdbinds))},
{"offset_cmd_mousebtn",(uint64_t)(offsetof(struct cmd,mousebtn))},
{"width_cmd_mousebtn",(uint64_t)(sizeof(((struct cmd*)0)->mousebtn))},
{"offset_cmd_spkeys",(uint64_t)(offsetof(struct cmd,spkeys))},
{"width_cmd_spkeys",(uint64_t)(sizeof(((struct cmd*)0)->spkeys))},
{"offset_cmd_extcmd_char",(uint64_t)(offsetof(struct cmd,extcmd_char))},
{"width_cmd_extcmd_char",(uint64_t)(sizeof(((struct cmd*)0)->extcmd_char))},
{"size_color_and_attr",(uint64_t)(sizeof(struct color_and_attr))},
{"align_color_and_attr",(uint64_t)(__alignof__(struct color_and_attr))},
{"offset_color_and_attr_color",(uint64_t)(offsetof(struct color_and_attr,color))},
{"width_color_and_attr_color",(uint64_t)(sizeof(((struct color_and_attr*)0)->color))},
{"offset_color_and_attr_attr",(uint64_t)(offsetof(struct color_and_attr,attr))},
{"width_color_and_attr_attr",(uint64_t)(sizeof(((struct color_and_attr*)0)->attr))},
{"size_const_globals",(uint64_t)(sizeof(struct const_globals))},
{"align_const_globals",(uint64_t)(__alignof__(struct const_globals))},
{"offset_const_globals_zeroobj",(uint64_t)(offsetof(struct const_globals,zeroobj))},
{"width_const_globals_zeroobj",(uint64_t)(sizeof(((struct const_globals*)0)->zeroobj))},
{"offset_const_globals_zeromonst",(uint64_t)(offsetof(struct const_globals,zeromonst))},
{"width_const_globals_zeromonst",(uint64_t)(sizeof(((struct const_globals*)0)->zeromonst))},
{"offset_const_globals_zeroany",(uint64_t)(offsetof(struct const_globals,zeroany))},
{"width_const_globals_zeroany",(uint64_t)(sizeof(((struct const_globals*)0)->zeroany))},
{"offset_const_globals_zeroNhRect",(uint64_t)(offsetof(struct const_globals,zeroNhRect))},
{"width_const_globals_zeroNhRect",(uint64_t)(sizeof(((struct const_globals*)0)->zeroNhRect))},
{"size_context_info",(uint64_t)(sizeof(struct context_info))},
{"align_context_info",(uint64_t)(__alignof__(struct context_info))},
{"offset_context_info_ident",(uint64_t)(offsetof(struct context_info,ident))},
{"width_context_info_ident",(uint64_t)(sizeof(((struct context_info*)0)->ident))},
{"offset_context_info_no_of_wizards",(uint64_t)(offsetof(struct context_info,no_of_wizards))},
{"width_context_info_no_of_wizards",(uint64_t)(sizeof(((struct context_info*)0)->no_of_wizards))},
{"offset_context_info_run",(uint64_t)(offsetof(struct context_info,run))},
{"width_context_info_run",(uint64_t)(sizeof(((struct context_info*)0)->run))},
{"offset_context_info_startingpet_mid",(uint64_t)(offsetof(struct context_info,startingpet_mid))},
{"width_context_info_startingpet_mid",(uint64_t)(sizeof(((struct context_info*)0)->startingpet_mid))},
{"offset_context_info_current_fruit",(uint64_t)(offsetof(struct context_info,current_fruit))},
{"width_context_info_current_fruit",(uint64_t)(sizeof(((struct context_info*)0)->current_fruit))},
{"offset_context_info_mysteryforce",(uint64_t)(offsetof(struct context_info,mysteryforce))},
{"width_context_info_mysteryforce",(uint64_t)(sizeof(((struct context_info*)0)->mysteryforce))},
{"offset_context_info_rndencode",(uint64_t)(offsetof(struct context_info,rndencode))},
{"width_context_info_rndencode",(uint64_t)(sizeof(((struct context_info*)0)->rndencode))},
{"offset_context_info_startingpet_typ",(uint64_t)(offsetof(struct context_info,startingpet_typ))},
{"width_context_info_startingpet_typ",(uint64_t)(sizeof(((struct context_info*)0)->startingpet_typ))},
{"offset_context_info_warnlevel",(uint64_t)(offsetof(struct context_info,warnlevel))},
{"width_context_info_warnlevel",(uint64_t)(sizeof(((struct context_info*)0)->warnlevel))},
{"offset_context_info_next_attrib_check",(uint64_t)(offsetof(struct context_info,next_attrib_check))},
{"width_context_info_next_attrib_check",(uint64_t)(sizeof(((struct context_info*)0)->next_attrib_check))},
{"offset_context_info_seer_turn",(uint64_t)(offsetof(struct context_info,seer_turn))},
{"width_context_info_seer_turn",(uint64_t)(sizeof(((struct context_info*)0)->seer_turn))},
{"offset_context_info_snickersnee_turn",(uint64_t)(offsetof(struct context_info,snickersnee_turn))},
{"width_context_info_snickersnee_turn",(uint64_t)(sizeof(((struct context_info*)0)->snickersnee_turn))},
{"offset_context_info_stethoscope_seq",(uint64_t)(offsetof(struct context_info,stethoscope_seq))},
{"width_context_info_stethoscope_seq",(uint64_t)(sizeof(((struct context_info*)0)->stethoscope_seq))},
{"offset_context_info_travel",(uint64_t)(offsetof(struct context_info,travel))},
{"width_context_info_travel",(uint64_t)(sizeof(((struct context_info*)0)->travel))},
{"offset_context_info_travel1",(uint64_t)(offsetof(struct context_info,travel1))},
{"width_context_info_travel1",(uint64_t)(sizeof(((struct context_info*)0)->travel1))},
{"offset_context_info_forcefight",(uint64_t)(offsetof(struct context_info,forcefight))},
{"width_context_info_forcefight",(uint64_t)(sizeof(((struct context_info*)0)->forcefight))},
{"offset_context_info_nopick",(uint64_t)(offsetof(struct context_info,nopick))},
{"width_context_info_nopick",(uint64_t)(sizeof(((struct context_info*)0)->nopick))},
{"offset_context_info_made_amulet",(uint64_t)(offsetof(struct context_info,made_amulet))},
{"width_context_info_made_amulet",(uint64_t)(sizeof(((struct context_info*)0)->made_amulet))},
{"offset_context_info_mon_moving",(uint64_t)(offsetof(struct context_info,mon_moving))},
{"width_context_info_mon_moving",(uint64_t)(sizeof(((struct context_info*)0)->mon_moving))},
{"offset_context_info_move",(uint64_t)(offsetof(struct context_info,move))},
{"width_context_info_move",(uint64_t)(sizeof(((struct context_info*)0)->move))},
{"offset_context_info_mv",(uint64_t)(offsetof(struct context_info,mv))},
{"width_context_info_mv",(uint64_t)(sizeof(((struct context_info*)0)->mv))},
{"offset_context_info_bypasses",(uint64_t)(offsetof(struct context_info,bypasses))},
{"width_context_info_bypasses",(uint64_t)(sizeof(((struct context_info*)0)->bypasses))},
{"offset_context_info_door_opened",(uint64_t)(offsetof(struct context_info,door_opened))},
{"width_context_info_door_opened",(uint64_t)(sizeof(((struct context_info*)0)->door_opened))},
{"offset_context_info_resume_wish",(uint64_t)(offsetof(struct context_info,resume_wish))},
{"width_context_info_resume_wish",(uint64_t)(sizeof(((struct context_info*)0)->resume_wish))},
{"offset_context_info_tips",(uint64_t)(offsetof(struct context_info,tips))},
{"width_context_info_tips",(uint64_t)(sizeof(((struct context_info*)0)->tips))},
{"offset_context_info_digging",(uint64_t)(offsetof(struct context_info,digging))},
{"width_context_info_digging",(uint64_t)(sizeof(((struct context_info*)0)->digging))},
{"offset_context_info_victual",(uint64_t)(offsetof(struct context_info,victual))},
{"width_context_info_victual",(uint64_t)(sizeof(((struct context_info*)0)->victual))},
{"offset_context_info_engraving",(uint64_t)(offsetof(struct context_info,engraving))},
{"width_context_info_engraving",(uint64_t)(sizeof(((struct context_info*)0)->engraving))},
{"offset_context_info_tin",(uint64_t)(offsetof(struct context_info,tin))},
{"width_context_info_tin",(uint64_t)(sizeof(((struct context_info*)0)->tin))},
{"offset_context_info_spbook",(uint64_t)(offsetof(struct context_info,spbook))},
{"width_context_info_spbook",(uint64_t)(sizeof(((struct context_info*)0)->spbook))},
{"offset_context_info_takeoff",(uint64_t)(offsetof(struct context_info,takeoff))},
{"width_context_info_takeoff",(uint64_t)(sizeof(((struct context_info*)0)->takeoff))},
{"offset_context_info_warntype",(uint64_t)(offsetof(struct context_info,warntype))},
{"width_context_info_warntype",(uint64_t)(sizeof(((struct context_info*)0)->warntype))},
{"offset_context_info_polearm",(uint64_t)(offsetof(struct context_info,polearm))},
{"width_context_info_polearm",(uint64_t)(sizeof(((struct context_info*)0)->polearm))},
{"offset_context_info_objsplit",(uint64_t)(offsetof(struct context_info,objsplit))},
{"width_context_info_objsplit",(uint64_t)(sizeof(((struct context_info*)0)->objsplit))},
{"offset_context_info_tribute",(uint64_t)(offsetof(struct context_info,tribute))},
{"width_context_info_tribute",(uint64_t)(sizeof(((struct context_info*)0)->tribute))},
{"offset_context_info_novel",(uint64_t)(offsetof(struct context_info,novel))},
{"width_context_info_novel",(uint64_t)(sizeof(((struct context_info*)0)->novel))},
{"offset_context_info_achieveo",(uint64_t)(offsetof(struct context_info,achieveo))},
{"width_context_info_achieveo",(uint64_t)(sizeof(((struct context_info*)0)->achieveo))},
{"offset_context_info_lifelist",(uint64_t)(offsetof(struct context_info,lifelist))},
{"width_context_info_lifelist",(uint64_t)(sizeof(((struct context_info*)0)->lifelist))},
{"offset_context_info_jingle",(uint64_t)(offsetof(struct context_info,jingle))},
{"width_context_info_jingle",(uint64_t)(sizeof(((struct context_info*)0)->jingle))},
{"size_d_flags",(uint64_t)(sizeof(struct d_flags))},
{"align_d_flags",(uint64_t)(__alignof__(struct d_flags))},
{"size_d_level",(uint64_t)(sizeof(struct d_level))},
{"align_d_level",(uint64_t)(__alignof__(struct d_level))},
{"offset_d_level_dnum",(uint64_t)(offsetof(struct d_level,dnum))},
{"width_d_level_dnum",(uint64_t)(sizeof(((struct d_level*)0)->dnum))},
{"offset_d_level_dlevel",(uint64_t)(offsetof(struct d_level,dlevel))},
{"width_d_level_dlevel",(uint64_t)(sizeof(((struct d_level*)0)->dlevel))},
{"size_debug_flags",(uint64_t)(sizeof(struct debug_flags))},
{"align_debug_flags",(uint64_t)(__alignof__(struct debug_flags))},
{"offset_debug_flags_test",(uint64_t)(offsetof(struct debug_flags,test))},
{"width_debug_flags_test",(uint64_t)(sizeof(((struct debug_flags*)0)->test))},
{"offset_debug_flags_ttystatus",(uint64_t)(offsetof(struct debug_flags,ttystatus))},
{"width_debug_flags_ttystatus",(uint64_t)(sizeof(((struct debug_flags*)0)->ttystatus))},
{"size_dest_area",(uint64_t)(sizeof(struct dest_area))},
{"align_dest_area",(uint64_t)(__alignof__(struct dest_area))},
{"offset_dest_area_lx",(uint64_t)(offsetof(struct dest_area,lx))},
{"width_dest_area_lx",(uint64_t)(sizeof(((struct dest_area*)0)->lx))},
{"offset_dest_area_ly",(uint64_t)(offsetof(struct dest_area,ly))},
{"width_dest_area_ly",(uint64_t)(sizeof(((struct dest_area*)0)->ly))},
{"offset_dest_area_hx",(uint64_t)(offsetof(struct dest_area,hx))},
{"width_dest_area_hx",(uint64_t)(sizeof(((struct dest_area*)0)->hx))},
{"offset_dest_area_hy",(uint64_t)(offsetof(struct dest_area,hy))},
{"width_dest_area_hy",(uint64_t)(sizeof(((struct dest_area*)0)->hy))},
{"offset_dest_area_nlx",(uint64_t)(offsetof(struct dest_area,nlx))},
{"width_dest_area_nlx",(uint64_t)(sizeof(((struct dest_area*)0)->nlx))},
{"offset_dest_area_nly",(uint64_t)(offsetof(struct dest_area,nly))},
{"width_dest_area_nly",(uint64_t)(sizeof(((struct dest_area*)0)->nly))},
{"offset_dest_area_nhx",(uint64_t)(offsetof(struct dest_area,nhx))},
{"width_dest_area_nhx",(uint64_t)(sizeof(((struct dest_area*)0)->nhx))},
{"offset_dest_area_nhy",(uint64_t)(offsetof(struct dest_area,nhy))},
{"width_dest_area_nhy",(uint64_t)(sizeof(((struct dest_area*)0)->nhy))},
{"size_dgn_topology",(uint64_t)(sizeof(struct dgn_topology))},
{"align_dgn_topology",(uint64_t)(__alignof__(struct dgn_topology))},
{"offset_dgn_topology_d_oracle_level",(uint64_t)(offsetof(struct dgn_topology,d_oracle_level))},
{"width_dgn_topology_d_oracle_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_oracle_level))},
{"offset_dgn_topology_d_bigroom_level",(uint64_t)(offsetof(struct dgn_topology,d_bigroom_level))},
{"width_dgn_topology_d_bigroom_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_bigroom_level))},
{"offset_dgn_topology_d_rogue_level",(uint64_t)(offsetof(struct dgn_topology,d_rogue_level))},
{"width_dgn_topology_d_rogue_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_rogue_level))},
{"offset_dgn_topology_d_medusa_level",(uint64_t)(offsetof(struct dgn_topology,d_medusa_level))},
{"width_dgn_topology_d_medusa_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_medusa_level))},
{"offset_dgn_topology_d_stronghold_level",(uint64_t)(offsetof(struct dgn_topology,d_stronghold_level))},
{"width_dgn_topology_d_stronghold_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_stronghold_level))},
{"offset_dgn_topology_d_valley_level",(uint64_t)(offsetof(struct dgn_topology,d_valley_level))},
{"width_dgn_topology_d_valley_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_valley_level))},
{"offset_dgn_topology_d_wiz1_level",(uint64_t)(offsetof(struct dgn_topology,d_wiz1_level))},
{"width_dgn_topology_d_wiz1_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_wiz1_level))},
{"offset_dgn_topology_d_wiz2_level",(uint64_t)(offsetof(struct dgn_topology,d_wiz2_level))},
{"width_dgn_topology_d_wiz2_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_wiz2_level))},
{"offset_dgn_topology_d_wiz3_level",(uint64_t)(offsetof(struct dgn_topology,d_wiz3_level))},
{"width_dgn_topology_d_wiz3_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_wiz3_level))},
{"offset_dgn_topology_d_juiblex_level",(uint64_t)(offsetof(struct dgn_topology,d_juiblex_level))},
{"width_dgn_topology_d_juiblex_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_juiblex_level))},
{"offset_dgn_topology_d_orcus_level",(uint64_t)(offsetof(struct dgn_topology,d_orcus_level))},
{"width_dgn_topology_d_orcus_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_orcus_level))},
{"offset_dgn_topology_d_baalzebub_level",(uint64_t)(offsetof(struct dgn_topology,d_baalzebub_level))},
{"width_dgn_topology_d_baalzebub_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_baalzebub_level))},
{"offset_dgn_topology_d_asmodeus_level",(uint64_t)(offsetof(struct dgn_topology,d_asmodeus_level))},
{"width_dgn_topology_d_asmodeus_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_asmodeus_level))},
{"offset_dgn_topology_d_portal_level",(uint64_t)(offsetof(struct dgn_topology,d_portal_level))},
{"width_dgn_topology_d_portal_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_portal_level))},
{"offset_dgn_topology_d_sanctum_level",(uint64_t)(offsetof(struct dgn_topology,d_sanctum_level))},
{"width_dgn_topology_d_sanctum_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_sanctum_level))},
{"offset_dgn_topology_d_earth_level",(uint64_t)(offsetof(struct dgn_topology,d_earth_level))},
{"width_dgn_topology_d_earth_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_earth_level))},
{"offset_dgn_topology_d_water_level",(uint64_t)(offsetof(struct dgn_topology,d_water_level))},
{"width_dgn_topology_d_water_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_water_level))},
{"offset_dgn_topology_d_fire_level",(uint64_t)(offsetof(struct dgn_topology,d_fire_level))},
{"width_dgn_topology_d_fire_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_fire_level))},
{"offset_dgn_topology_d_air_level",(uint64_t)(offsetof(struct dgn_topology,d_air_level))},
{"width_dgn_topology_d_air_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_air_level))},
{"offset_dgn_topology_d_astral_level",(uint64_t)(offsetof(struct dgn_topology,d_astral_level))},
{"width_dgn_topology_d_astral_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_astral_level))},
{"offset_dgn_topology_d_tower_dnum",(uint64_t)(offsetof(struct dgn_topology,d_tower_dnum))},
{"width_dgn_topology_d_tower_dnum",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_tower_dnum))},
{"offset_dgn_topology_d_sokoban_dnum",(uint64_t)(offsetof(struct dgn_topology,d_sokoban_dnum))},
{"width_dgn_topology_d_sokoban_dnum",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_sokoban_dnum))},
{"offset_dgn_topology_d_mines_dnum",(uint64_t)(offsetof(struct dgn_topology,d_mines_dnum))},
{"width_dgn_topology_d_mines_dnum",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_mines_dnum))},
{"offset_dgn_topology_d_quest_dnum",(uint64_t)(offsetof(struct dgn_topology,d_quest_dnum))},
{"width_dgn_topology_d_quest_dnum",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_quest_dnum))},
{"offset_dgn_topology_d_tutorial_dnum",(uint64_t)(offsetof(struct dgn_topology,d_tutorial_dnum))},
{"width_dgn_topology_d_tutorial_dnum",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_tutorial_dnum))},
{"offset_dgn_topology_d_qstart_level",(uint64_t)(offsetof(struct dgn_topology,d_qstart_level))},
{"width_dgn_topology_d_qstart_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_qstart_level))},
{"offset_dgn_topology_d_qlocate_level",(uint64_t)(offsetof(struct dgn_topology,d_qlocate_level))},
{"width_dgn_topology_d_qlocate_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_qlocate_level))},
{"offset_dgn_topology_d_nemesis_level",(uint64_t)(offsetof(struct dgn_topology,d_nemesis_level))},
{"width_dgn_topology_d_nemesis_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_nemesis_level))},
{"offset_dgn_topology_d_knox_level",(uint64_t)(offsetof(struct dgn_topology,d_knox_level))},
{"width_dgn_topology_d_knox_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_knox_level))},
{"offset_dgn_topology_d_mineend_level",(uint64_t)(offsetof(struct dgn_topology,d_mineend_level))},
{"width_dgn_topology_d_mineend_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_mineend_level))},
{"offset_dgn_topology_d_sokoend_level",(uint64_t)(offsetof(struct dgn_topology,d_sokoend_level))},
{"width_dgn_topology_d_sokoend_level",(uint64_t)(sizeof(((struct dgn_topology*)0)->d_sokoend_level))},
{"size_dig_info",(uint64_t)(sizeof(struct dig_info))},
{"align_dig_info",(uint64_t)(__alignof__(struct dig_info))},
{"offset_dig_info_effort",(uint64_t)(offsetof(struct dig_info,effort))},
{"width_dig_info_effort",(uint64_t)(sizeof(((struct dig_info*)0)->effort))},
{"offset_dig_info_level",(uint64_t)(offsetof(struct dig_info,level))},
{"width_dig_info_level",(uint64_t)(sizeof(((struct dig_info*)0)->level))},
{"offset_dig_info_pos",(uint64_t)(offsetof(struct dig_info,pos))},
{"width_dig_info_pos",(uint64_t)(sizeof(((struct dig_info*)0)->pos))},
{"offset_dig_info_lastdigtime",(uint64_t)(offsetof(struct dig_info,lastdigtime))},
{"width_dig_info_lastdigtime",(uint64_t)(sizeof(((struct dig_info*)0)->lastdigtime))},
{"offset_dig_info_down",(uint64_t)(offsetof(struct dig_info,down))},
{"width_dig_info_down",(uint64_t)(sizeof(((struct dig_info*)0)->down))},
{"offset_dig_info_chew",(uint64_t)(offsetof(struct dig_info,chew))},
{"width_dig_info_chew",(uint64_t)(sizeof(((struct dig_info*)0)->chew))},
{"offset_dig_info_warned",(uint64_t)(offsetof(struct dig_info,warned))},
{"width_dig_info_warned",(uint64_t)(sizeof(((struct dig_info*)0)->warned))},
{"offset_dig_info_quiet",(uint64_t)(offsetof(struct dig_info,quiet))},
{"width_dig_info_quiet",(uint64_t)(sizeof(((struct dig_info*)0)->quiet))},
{"size_display_hints",(uint64_t)(sizeof(struct display_hints))},
{"align_display_hints",(uint64_t)(__alignof__(struct display_hints))},
{"offset_display_hints_botl",(uint64_t)(offsetof(struct display_hints,botl))},
{"width_display_hints_botl",(uint64_t)(sizeof(((struct display_hints*)0)->botl))},
{"offset_display_hints_botlx",(uint64_t)(offsetof(struct display_hints,botlx))},
{"width_display_hints_botlx",(uint64_t)(sizeof(((struct display_hints*)0)->botlx))},
{"offset_display_hints_time_botl",(uint64_t)(offsetof(struct display_hints,time_botl))},
{"width_display_hints_time_botl",(uint64_t)(sizeof(((struct display_hints*)0)->time_botl))},
{"size_dlevel_t",(uint64_t)(sizeof(dlevel_t))},
{"align_dlevel_t",(uint64_t)(__alignof__(dlevel_t))},
{"offset_dlevel_t_locations",(uint64_t)(offsetof(dlevel_t,locations))},
{"width_dlevel_t_locations",(uint64_t)(sizeof(((dlevel_t*)0)->locations))},
{"offset_dlevel_t_objects",(uint64_t)(offsetof(dlevel_t,objects))},
{"width_dlevel_t_objects",(uint64_t)(sizeof(((dlevel_t*)0)->objects))},
{"offset_dlevel_t_monsters",(uint64_t)(offsetof(dlevel_t,monsters))},
{"width_dlevel_t_monsters",(uint64_t)(sizeof(((dlevel_t*)0)->monsters))},
{"offset_dlevel_t_objlist",(uint64_t)(offsetof(dlevel_t,objlist))},
{"width_dlevel_t_objlist",(uint64_t)(sizeof(((dlevel_t*)0)->objlist))},
{"offset_dlevel_t_buriedobjlist",(uint64_t)(offsetof(dlevel_t,buriedobjlist))},
{"width_dlevel_t_buriedobjlist",(uint64_t)(sizeof(((dlevel_t*)0)->buriedobjlist))},
{"offset_dlevel_t_monlist",(uint64_t)(offsetof(dlevel_t,monlist))},
{"width_dlevel_t_monlist",(uint64_t)(sizeof(((dlevel_t*)0)->monlist))},
{"offset_dlevel_t_damagelist",(uint64_t)(offsetof(dlevel_t,damagelist))},
{"width_dlevel_t_damagelist",(uint64_t)(sizeof(((dlevel_t*)0)->damagelist))},
{"offset_dlevel_t_bonesinfo",(uint64_t)(offsetof(dlevel_t,bonesinfo))},
{"width_dlevel_t_bonesinfo",(uint64_t)(sizeof(((dlevel_t*)0)->bonesinfo))},
{"offset_dlevel_t_flags",(uint64_t)(offsetof(dlevel_t,flags))},
{"width_dlevel_t_flags",(uint64_t)(sizeof(((dlevel_t*)0)->flags))},
{"size_dungeon",(uint64_t)(sizeof(struct dungeon))},
{"align_dungeon",(uint64_t)(__alignof__(struct dungeon))},
{"offset_dungeon_dname",(uint64_t)(offsetof(struct dungeon,dname))},
{"width_dungeon_dname",(uint64_t)(sizeof(((struct dungeon*)0)->dname))},
{"offset_dungeon_proto",(uint64_t)(offsetof(struct dungeon,proto))},
{"width_dungeon_proto",(uint64_t)(sizeof(((struct dungeon*)0)->proto))},
{"offset_dungeon_fill_lvl",(uint64_t)(offsetof(struct dungeon,fill_lvl))},
{"width_dungeon_fill_lvl",(uint64_t)(sizeof(((struct dungeon*)0)->fill_lvl))},
{"offset_dungeon_themerms",(uint64_t)(offsetof(struct dungeon,themerms))},
{"width_dungeon_themerms",(uint64_t)(sizeof(((struct dungeon*)0)->themerms))},
{"offset_dungeon_boneid",(uint64_t)(offsetof(struct dungeon,boneid))},
{"width_dungeon_boneid",(uint64_t)(sizeof(((struct dungeon*)0)->boneid))},
{"offset_dungeon_flags",(uint64_t)(offsetof(struct dungeon,flags))},
{"width_dungeon_flags",(uint64_t)(sizeof(((struct dungeon*)0)->flags))},
{"offset_dungeon_entry_lev",(uint64_t)(offsetof(struct dungeon,entry_lev))},
{"width_dungeon_entry_lev",(uint64_t)(sizeof(((struct dungeon*)0)->entry_lev))},
{"offset_dungeon_num_dunlevs",(uint64_t)(offsetof(struct dungeon,num_dunlevs))},
{"width_dungeon_num_dunlevs",(uint64_t)(sizeof(((struct dungeon*)0)->num_dunlevs))},
{"offset_dungeon_dunlev_ureached",(uint64_t)(offsetof(struct dungeon,dunlev_ureached))},
{"width_dungeon_dunlev_ureached",(uint64_t)(sizeof(((struct dungeon*)0)->dunlev_ureached))},
{"offset_dungeon_ledger_start",(uint64_t)(offsetof(struct dungeon,ledger_start))},
{"width_dungeon_ledger_start",(uint64_t)(sizeof(((struct dungeon*)0)->ledger_start))},
{"offset_dungeon_depth_start",(uint64_t)(offsetof(struct dungeon,depth_start))},
{"width_dungeon_depth_start",(uint64_t)(sizeof(((struct dungeon*)0)->depth_start))},
{"size_engrave_info",(uint64_t)(sizeof(struct engrave_info))},
{"align_engrave_info",(uint64_t)(__alignof__(struct engrave_info))},
{"offset_engrave_info_text",(uint64_t)(offsetof(struct engrave_info,text))},
{"width_engrave_info_text",(uint64_t)(sizeof(((struct engrave_info*)0)->text))},
{"offset_engrave_info_nextc",(uint64_t)(offsetof(struct engrave_info,nextc))},
{"width_engrave_info_nextc",(uint64_t)(sizeof(((struct engrave_info*)0)->nextc))},
{"offset_engrave_info_stylus",(uint64_t)(offsetof(struct engrave_info,stylus))},
{"width_engrave_info_stylus",(uint64_t)(sizeof(((struct engrave_info*)0)->stylus))},
{"offset_engrave_info_type",(uint64_t)(offsetof(struct engrave_info,type))},
{"width_engrave_info_type",(uint64_t)(sizeof(((struct engrave_info*)0)->type))},
{"offset_engrave_info_pos",(uint64_t)(offsetof(struct engrave_info,pos))},
{"width_engrave_info_pos",(uint64_t)(sizeof(((struct engrave_info*)0)->pos))},
{"offset_engrave_info_actionct",(uint64_t)(offsetof(struct engrave_info,actionct))},
{"width_engrave_info_actionct",(uint64_t)(sizeof(((struct engrave_info*)0)->actionct))},
{"size_entity",(uint64_t)(sizeof(struct entity))},
{"align_entity",(uint64_t)(__alignof__(struct entity))},
{"offset_entity_emon",(uint64_t)(offsetof(struct entity,emon))},
{"width_entity_emon",(uint64_t)(sizeof(((struct entity*)0)->emon))},
{"offset_entity_edata",(uint64_t)(offsetof(struct entity,edata))},
{"width_entity_edata",(uint64_t)(sizeof(((struct entity*)0)->edata))},
{"offset_entity_ex",(uint64_t)(offsetof(struct entity,ex))},
{"width_entity_ex",(uint64_t)(sizeof(((struct entity*)0)->ex))},
{"offset_entity_ey",(uint64_t)(offsetof(struct entity,ey))},
{"width_entity_ey",(uint64_t)(sizeof(((struct entity*)0)->ey))},
{"size_flag",(uint64_t)(sizeof(struct flag))},
{"align_flag",(uint64_t)(__alignof__(struct flag))},
{"offset_flag_acoustics",(uint64_t)(offsetof(struct flag,acoustics))},
{"width_flag_acoustics",(uint64_t)(sizeof(((struct flag*)0)->acoustics))},
{"offset_flag_armorstatus",(uint64_t)(offsetof(struct flag,armorstatus))},
{"width_flag_armorstatus",(uint64_t)(sizeof(((struct flag*)0)->armorstatus))},
{"offset_flag_autodig",(uint64_t)(offsetof(struct flag,autodig))},
{"width_flag_autodig",(uint64_t)(sizeof(((struct flag*)0)->autodig))},
{"offset_flag_autoquiver",(uint64_t)(offsetof(struct flag,autoquiver))},
{"width_flag_autoquiver",(uint64_t)(sizeof(((struct flag*)0)->autoquiver))},
{"offset_flag_autoopen",(uint64_t)(offsetof(struct flag,autoopen))},
{"width_flag_autoopen",(uint64_t)(sizeof(((struct flag*)0)->autoopen))},
{"offset_flag_beginner",(uint64_t)(offsetof(struct flag,beginner))},
{"width_flag_beginner",(uint64_t)(sizeof(((struct flag*)0)->beginner))},
{"offset_flag_biff",(uint64_t)(offsetof(struct flag,biff))},
{"width_flag_biff",(uint64_t)(sizeof(((struct flag*)0)->biff))},
{"offset_flag_bones",(uint64_t)(offsetof(struct flag,bones))},
{"width_flag_bones",(uint64_t)(sizeof(((struct flag*)0)->bones))},
{"offset_flag_confirm",(uint64_t)(offsetof(struct flag,confirm))},
{"width_flag_confirm",(uint64_t)(sizeof(((struct flag*)0)->confirm))},
{"offset_flag_dark_room",(uint64_t)(offsetof(struct flag,dark_room))},
{"width_flag_dark_room",(uint64_t)(sizeof(((struct flag*)0)->dark_room))},
{"offset_flag_debug",(uint64_t)(offsetof(struct flag,debug))},
{"width_flag_debug",(uint64_t)(sizeof(((struct flag*)0)->debug))},
{"offset_flag_end_own",(uint64_t)(offsetof(struct flag,end_own))},
{"width_flag_end_own",(uint64_t)(sizeof(((struct flag*)0)->end_own))},
{"offset_flag_explore",(uint64_t)(offsetof(struct flag,explore))},
{"width_flag_explore",(uint64_t)(sizeof(((struct flag*)0)->explore))},
{"offset_flag_female",(uint64_t)(offsetof(struct flag,female))},
{"width_flag_female",(uint64_t)(sizeof(((struct flag*)0)->female))},
{"offset_flag_friday13",(uint64_t)(offsetof(struct flag,friday13))},
{"width_flag_friday13",(uint64_t)(sizeof(((struct flag*)0)->friday13))},
{"offset_flag_goldX",(uint64_t)(offsetof(struct flag,goldX))},
{"width_flag_goldX",(uint64_t)(sizeof(((struct flag*)0)->goldX))},
{"offset_flag_help",(uint64_t)(offsetof(struct flag,help))},
{"width_flag_help",(uint64_t)(sizeof(((struct flag*)0)->help))},
{"offset_flag_tips",(uint64_t)(offsetof(struct flag,tips))},
{"width_flag_tips",(uint64_t)(sizeof(((struct flag*)0)->tips))},
{"offset_flag_tutorial",(uint64_t)(offsetof(struct flag,tutorial))},
{"width_flag_tutorial",(uint64_t)(sizeof(((struct flag*)0)->tutorial))},
{"offset_flag_ignintr",(uint64_t)(offsetof(struct flag,ignintr))},
{"width_flag_ignintr",(uint64_t)(sizeof(((struct flag*)0)->ignintr))},
{"offset_flag_implicit_uncursed",(uint64_t)(offsetof(struct flag,implicit_uncursed))},
{"width_flag_implicit_uncursed",(uint64_t)(sizeof(((struct flag*)0)->implicit_uncursed))},
{"offset_flag_ins_chkpt",(uint64_t)(offsetof(struct flag,ins_chkpt))},
{"width_flag_ins_chkpt",(uint64_t)(sizeof(((struct flag*)0)->ins_chkpt))},
{"offset_flag_invlet_constant",(uint64_t)(offsetof(struct flag,invlet_constant))},
{"width_flag_invlet_constant",(uint64_t)(sizeof(((struct flag*)0)->invlet_constant))},
{"offset_flag_legacy",(uint64_t)(offsetof(struct flag,legacy))},
{"width_flag_legacy",(uint64_t)(sizeof(((struct flag*)0)->legacy))},
{"offset_flag_lit_corridor",(uint64_t)(offsetof(struct flag,lit_corridor))},
{"width_flag_lit_corridor",(uint64_t)(sizeof(((struct flag*)0)->lit_corridor))},
{"offset_flag_mention_decor",(uint64_t)(offsetof(struct flag,mention_decor))},
{"width_flag_mention_decor",(uint64_t)(sizeof(((struct flag*)0)->mention_decor))},
{"offset_flag_mention_walls",(uint64_t)(offsetof(struct flag,mention_walls))},
{"width_flag_mention_walls",(uint64_t)(sizeof(((struct flag*)0)->mention_walls))},
{"offset_flag_nap",(uint64_t)(offsetof(struct flag,nap))},
{"width_flag_nap",(uint64_t)(sizeof(((struct flag*)0)->nap))},
{"offset_flag_nopick_dropped",(uint64_t)(offsetof(struct flag,nopick_dropped))},
{"width_flag_nopick_dropped",(uint64_t)(sizeof(((struct flag*)0)->nopick_dropped))},
{"offset_flag_null",(uint64_t)(offsetof(struct flag,null))},
{"width_flag_null",(uint64_t)(sizeof(((struct flag*)0)->null))},
{"offset_flag_pickup",(uint64_t)(offsetof(struct flag,pickup))},
{"width_flag_pickup",(uint64_t)(sizeof(((struct flag*)0)->pickup))},
{"offset_flag_pickup_stolen",(uint64_t)(offsetof(struct flag,pickup_stolen))},
{"width_flag_pickup_stolen",(uint64_t)(sizeof(((struct flag*)0)->pickup_stolen))},
{"offset_flag_pickup_thrown",(uint64_t)(offsetof(struct flag,pickup_thrown))},
{"width_flag_pickup_thrown",(uint64_t)(sizeof(((struct flag*)0)->pickup_thrown))},
{"offset_flag_pushweapon",(uint64_t)(offsetof(struct flag,pushweapon))},
{"width_flag_pushweapon",(uint64_t)(sizeof(((struct flag*)0)->pushweapon))},
{"offset_flag_quick_farsight",(uint64_t)(offsetof(struct flag,quick_farsight))},
{"width_flag_quick_farsight",(uint64_t)(sizeof(((struct flag*)0)->quick_farsight))},
{"offset_flag_rest_on_space",(uint64_t)(offsetof(struct flag,rest_on_space))},
{"width_flag_rest_on_space",(uint64_t)(sizeof(((struct flag*)0)->rest_on_space))},
{"offset_flag_safe_dog",(uint64_t)(offsetof(struct flag,safe_dog))},
{"width_flag_safe_dog",(uint64_t)(sizeof(((struct flag*)0)->safe_dog))},
{"offset_flag_safe_wait",(uint64_t)(offsetof(struct flag,safe_wait))},
{"width_flag_safe_wait",(uint64_t)(sizeof(((struct flag*)0)->safe_wait))},
{"offset_flag_showexp",(uint64_t)(offsetof(struct flag,showexp))},
{"width_flag_showexp",(uint64_t)(sizeof(((struct flag*)0)->showexp))},
{"offset_flag_showscore",(uint64_t)(offsetof(struct flag,showscore))},
{"width_flag_showscore",(uint64_t)(sizeof(((struct flag*)0)->showscore))},
{"offset_flag_showvers",(uint64_t)(offsetof(struct flag,showvers))},
{"width_flag_showvers",(uint64_t)(sizeof(((struct flag*)0)->showvers))},
{"offset_flag_silent",(uint64_t)(offsetof(struct flag,silent))},
{"width_flag_silent",(uint64_t)(sizeof(((struct flag*)0)->silent))},
{"offset_flag_sortpack",(uint64_t)(offsetof(struct flag,sortpack))},
{"width_flag_sortpack",(uint64_t)(sizeof(((struct flag*)0)->sortpack))},
{"offset_flag_sparkle",(uint64_t)(offsetof(struct flag,sparkle))},
{"width_flag_sparkle",(uint64_t)(sizeof(((struct flag*)0)->sparkle))},
{"offset_flag_standout",(uint64_t)(offsetof(struct flag,standout))},
{"width_flag_standout",(uint64_t)(sizeof(((struct flag*)0)->standout))},
{"offset_flag_terrainstatus",(uint64_t)(offsetof(struct flag,terrainstatus))},
{"width_flag_terrainstatus",(uint64_t)(sizeof(((struct flag*)0)->terrainstatus))},
{"offset_flag_time",(uint64_t)(offsetof(struct flag,time))},
{"width_flag_time",(uint64_t)(sizeof(((struct flag*)0)->time))},
{"offset_flag_tombstone",(uint64_t)(offsetof(struct flag,tombstone))},
{"width_flag_tombstone",(uint64_t)(sizeof(((struct flag*)0)->tombstone))},
{"offset_flag_verbose",(uint64_t)(offsetof(struct flag,verbose))},
{"width_flag_verbose",(uint64_t)(sizeof(((struct flag*)0)->verbose))},
{"offset_flag_weaponstatus",(uint64_t)(offsetof(struct flag,weaponstatus))},
{"width_flag_weaponstatus",(uint64_t)(sizeof(((struct flag*)0)->weaponstatus))},
{"offset_flag_end_top",(uint64_t)(offsetof(struct flag,end_top))},
{"width_flag_end_top",(uint64_t)(sizeof(((struct flag*)0)->end_top))},
{"offset_flag_end_around",(uint64_t)(offsetof(struct flag,end_around))},
{"width_flag_end_around",(uint64_t)(sizeof(((struct flag*)0)->end_around))},
{"offset_flag_autounlock",(uint64_t)(offsetof(struct flag,autounlock))},
{"width_flag_autounlock",(uint64_t)(sizeof(((struct flag*)0)->autounlock))},
{"offset_flag_moonphase",(uint64_t)(offsetof(struct flag,moonphase))},
{"width_flag_moonphase",(uint64_t)(sizeof(((struct flag*)0)->moonphase))},
{"offset_flag_suppress_alert",(uint64_t)(offsetof(struct flag,suppress_alert))},
{"width_flag_suppress_alert",(uint64_t)(sizeof(((struct flag*)0)->suppress_alert))},
{"offset_flag_paranoia_bits",(uint64_t)(offsetof(struct flag,paranoia_bits))},
{"width_flag_paranoia_bits",(uint64_t)(sizeof(((struct flag*)0)->paranoia_bits))},
{"offset_flag_versinfo",(uint64_t)(offsetof(struct flag,versinfo))},
{"width_flag_versinfo",(uint64_t)(sizeof(((struct flag*)0)->versinfo))},
{"offset_flag_pickup_burden",(uint64_t)(offsetof(struct flag,pickup_burden))},
{"width_flag_pickup_burden",(uint64_t)(sizeof(((struct flag*)0)->pickup_burden))},
{"offset_flag_pile_limit",(uint64_t)(offsetof(struct flag,pile_limit))},
{"width_flag_pile_limit",(uint64_t)(sizeof(((struct flag*)0)->pile_limit))},
{"offset_flag_discosort",(uint64_t)(offsetof(struct flag,discosort))},
{"width_flag_discosort",(uint64_t)(sizeof(((struct flag*)0)->discosort))},
{"offset_flag_sortloot",(uint64_t)(offsetof(struct flag,sortloot))},
{"width_flag_sortloot",(uint64_t)(sizeof(((struct flag*)0)->sortloot))},
{"offset_flag_vanq_sortmode",(uint64_t)(offsetof(struct flag,vanq_sortmode))},
{"width_flag_vanq_sortmode",(uint64_t)(sizeof(((struct flag*)0)->vanq_sortmode))},
{"offset_flag_inv_order",(uint64_t)(offsetof(struct flag,inv_order))},
{"width_flag_inv_order",(uint64_t)(sizeof(((struct flag*)0)->inv_order))},
{"offset_flag_pickup_types",(uint64_t)(offsetof(struct flag,pickup_types))},
{"width_flag_pickup_types",(uint64_t)(sizeof(((struct flag*)0)->pickup_types))},
{"offset_flag_end_disclose",(uint64_t)(offsetof(struct flag,end_disclose))},
{"width_flag_end_disclose",(uint64_t)(sizeof(((struct flag*)0)->end_disclose))},
{"offset_flag_menu_style",(uint64_t)(offsetof(struct flag,menu_style))},
{"width_flag_menu_style",(uint64_t)(sizeof(((struct flag*)0)->menu_style))},
{"offset_flag_made_fruit",(uint64_t)(offsetof(struct flag,made_fruit))},
{"width_flag_made_fruit",(uint64_t)(sizeof(((struct flag*)0)->made_fruit))},
{"offset_flag_initrole",(uint64_t)(offsetof(struct flag,initrole))},
{"width_flag_initrole",(uint64_t)(sizeof(((struct flag*)0)->initrole))},
{"offset_flag_initrace",(uint64_t)(offsetof(struct flag,initrace))},
{"width_flag_initrace",(uint64_t)(sizeof(((struct flag*)0)->initrace))},
{"offset_flag_initgend",(uint64_t)(offsetof(struct flag,initgend))},
{"width_flag_initgend",(uint64_t)(sizeof(((struct flag*)0)->initgend))},
{"offset_flag_initalign",(uint64_t)(offsetof(struct flag,initalign))},
{"width_flag_initalign",(uint64_t)(sizeof(((struct flag*)0)->initalign))},
{"offset_flag_randomall",(uint64_t)(offsetof(struct flag,randomall))},
{"width_flag_randomall",(uint64_t)(sizeof(((struct flag*)0)->randomall))},
{"offset_flag_pantheon",(uint64_t)(offsetof(struct flag,pantheon))},
{"width_flag_pantheon",(uint64_t)(sizeof(((struct flag*)0)->pantheon))},
{"offset_flag_lootabc",(uint64_t)(offsetof(struct flag,lootabc))},
{"width_flag_lootabc",(uint64_t)(sizeof(((struct flag*)0)->lootabc))},
{"offset_flag_showrace",(uint64_t)(offsetof(struct flag,showrace))},
{"width_flag_showrace",(uint64_t)(sizeof(((struct flag*)0)->showrace))},
{"offset_flag_travelcmd",(uint64_t)(offsetof(struct flag,travelcmd))},
{"width_flag_travelcmd",(uint64_t)(sizeof(((struct flag*)0)->travelcmd))},
{"offset_flag_runmode",(uint64_t)(offsetof(struct flag,runmode))},
{"width_flag_runmode",(uint64_t)(sizeof(((struct flag*)0)->runmode))},
{"offset_flag_reserved1",(uint64_t)(offsetof(struct flag,reserved1))},
{"width_flag_reserved1",(uint64_t)(sizeof(((struct flag*)0)->reserved1))},
{"offset_flag_reserved2",(uint64_t)(offsetof(struct flag,reserved2))},
{"width_flag_reserved2",(uint64_t)(sizeof(((struct flag*)0)->reserved2))},
{"offset_flag_reserved3",(uint64_t)(offsetof(struct flag,reserved3))},
{"width_flag_reserved3",(uint64_t)(sizeof(((struct flag*)0)->reserved3))},
{"offset_flag_reserved4",(uint64_t)(offsetof(struct flag,reserved4))},
{"width_flag_reserved4",(uint64_t)(sizeof(((struct flag*)0)->reserved4))},
{"offset_flag_reserved5",(uint64_t)(offsetof(struct flag,reserved5))},
{"width_flag_reserved5",(uint64_t)(sizeof(((struct flag*)0)->reserved5))},
{"offset_flag_reserved6",(uint64_t)(offsetof(struct flag,reserved6))},
{"width_flag_reserved6",(uint64_t)(sizeof(((struct flag*)0)->reserved6))},
{"offset_flag_reserved7",(uint64_t)(offsetof(struct flag,reserved7))},
{"width_flag_reserved7",(uint64_t)(sizeof(((struct flag*)0)->reserved7))},
{"offset_flag_reserved8",(uint64_t)(offsetof(struct flag,reserved8))},
{"width_flag_reserved8",(uint64_t)(sizeof(((struct flag*)0)->reserved8))},
{"size_gbuf_entry",(uint64_t)(sizeof(gbuf_entry))},
{"align_gbuf_entry",(uint64_t)(__alignof__(gbuf_entry))},
{"offset_gbuf_entry_gnew",(uint64_t)(offsetof(gbuf_entry,gnew))},
{"width_gbuf_entry_gnew",(uint64_t)(sizeof(((gbuf_entry*)0)->gnew))},
{"offset_gbuf_entry_glyphinfo",(uint64_t)(offsetof(gbuf_entry,glyphinfo))},
{"width_gbuf_entry_glyphinfo",(uint64_t)(sizeof(((gbuf_entry*)0)->glyphinfo))},
{"size_glyph_map_entry",(uint64_t)(sizeof(struct glyph_map_entry))},
{"align_glyph_map_entry",(uint64_t)(__alignof__(struct glyph_map_entry))},
{"offset_glyph_map_entry_glyphflags",(uint64_t)(offsetof(struct glyph_map_entry,glyphflags))},
{"width_glyph_map_entry_glyphflags",(uint64_t)(sizeof(((struct glyph_map_entry*)0)->glyphflags))},
{"offset_glyph_map_entry_sym",(uint64_t)(offsetof(struct glyph_map_entry,sym))},
{"width_glyph_map_entry_sym",(uint64_t)(sizeof(((struct glyph_map_entry*)0)->sym))},
{"offset_glyph_map_entry_customcolor",(uint64_t)(offsetof(struct glyph_map_entry,customcolor))},
{"width_glyph_map_entry_customcolor",(uint64_t)(sizeof(((struct glyph_map_entry*)0)->customcolor))},
{"offset_glyph_map_entry_color256idx",(uint64_t)(offsetof(struct glyph_map_entry,color256idx))},
{"width_glyph_map_entry_color256idx",(uint64_t)(sizeof(((struct glyph_map_entry*)0)->color256idx))},
{"offset_glyph_map_entry_tileidx",(uint64_t)(offsetof(struct glyph_map_entry,tileidx))},
{"width_glyph_map_entry_tileidx",(uint64_t)(sizeof(((struct glyph_map_entry*)0)->tileidx))},
{"offset_glyph_map_entry_u",(uint64_t)(offsetof(struct glyph_map_entry,u))},
{"width_glyph_map_entry_u",(uint64_t)(sizeof(((struct glyph_map_entry*)0)->u))},
{"size_glyphinfo",(uint64_t)(sizeof(struct glyphinfo))},
{"align_glyphinfo",(uint64_t)(__alignof__(struct glyphinfo))},
{"offset_glyphinfo_glyph",(uint64_t)(offsetof(struct glyphinfo,glyph))},
{"width_glyphinfo_glyph",(uint64_t)(sizeof(((struct glyphinfo*)0)->glyph))},
{"offset_glyphinfo_ttychar",(uint64_t)(offsetof(struct glyphinfo,ttychar))},
{"width_glyphinfo_ttychar",(uint64_t)(sizeof(((struct glyphinfo*)0)->ttychar))},
{"offset_glyphinfo_framecolor",(uint64_t)(offsetof(struct glyphinfo,framecolor))},
{"width_glyphinfo_framecolor",(uint64_t)(sizeof(((struct glyphinfo*)0)->framecolor))},
{"offset_glyphinfo_gm",(uint64_t)(offsetof(struct glyphinfo,gm))},
{"width_glyphinfo_gm",(uint64_t)(sizeof(((struct glyphinfo*)0)->gm))},
{"size_h2o_ctx",(uint64_t)(sizeof(struct h2o_ctx))},
{"align_h2o_ctx",(uint64_t)(__alignof__(struct h2o_ctx))},
{"offset_h2o_ctx_dkn_boom",(uint64_t)(offsetof(struct h2o_ctx,dkn_boom))},
{"width_h2o_ctx_dkn_boom",(uint64_t)(sizeof(((struct h2o_ctx*)0)->dkn_boom))},
{"offset_h2o_ctx_unk_boom",(uint64_t)(offsetof(struct h2o_ctx,unk_boom))},
{"width_h2o_ctx_unk_boom",(uint64_t)(sizeof(((struct h2o_ctx*)0)->unk_boom))},
{"offset_h2o_ctx_ctx_valid",(uint64_t)(offsetof(struct h2o_ctx,ctx_valid))},
{"width_h2o_ctx_ctx_valid",(uint64_t)(sizeof(((struct h2o_ctx*)0)->ctx_valid))},
{"size_instance_flags",(uint64_t)(sizeof(struct instance_flags))},
{"align_instance_flags",(uint64_t)(__alignof__(struct instance_flags))},
{"offset_instance_flags_defer_plname",(uint64_t)(offsetof(struct instance_flags,defer_plname))},
{"width_instance_flags_defer_plname",(uint64_t)(sizeof(((struct instance_flags*)0)->defer_plname))},
{"offset_instance_flags_fuzzerpending",(uint64_t)(offsetof(struct instance_flags,fuzzerpending))},
{"width_instance_flags_fuzzerpending",(uint64_t)(sizeof(((struct instance_flags*)0)->fuzzerpending))},
{"offset_instance_flags_herecmd_menu",(uint64_t)(offsetof(struct instance_flags,herecmd_menu))},
{"width_instance_flags_herecmd_menu",(uint64_t)(sizeof(((struct instance_flags*)0)->herecmd_menu))},
{"offset_instance_flags_idlecheckpoint",(uint64_t)(offsetof(struct instance_flags,idlecheckpoint))},
{"width_instance_flags_idlecheckpoint",(uint64_t)(sizeof(((struct instance_flags*)0)->idlecheckpoint))},
{"offset_instance_flags_invis_goldsym",(uint64_t)(offsetof(struct instance_flags,invis_goldsym))},
{"width_instance_flags_invis_goldsym",(uint64_t)(sizeof(((struct instance_flags*)0)->invis_goldsym))},
{"offset_instance_flags_in_lua",(uint64_t)(offsetof(struct instance_flags,in_lua))},
{"width_instance_flags_in_lua",(uint64_t)(sizeof(((struct instance_flags*)0)->in_lua))},
{"offset_instance_flags_lua_testing",(uint64_t)(offsetof(struct instance_flags,lua_testing))},
{"width_instance_flags_lua_testing",(uint64_t)(sizeof(((struct instance_flags*)0)->lua_testing))},
{"offset_instance_flags_term_gone",(uint64_t)(offsetof(struct instance_flags,term_gone))},
{"width_instance_flags_term_gone",(uint64_t)(sizeof(((struct instance_flags*)0)->term_gone))},
{"offset_instance_flags_nofollowers",(uint64_t)(offsetof(struct instance_flags,nofollowers))},
{"width_instance_flags_nofollowers",(uint64_t)(sizeof(((struct instance_flags*)0)->nofollowers))},
{"offset_instance_flags_partly_eaten_hack",(uint64_t)(offsetof(struct instance_flags,partly_eaten_hack))},
{"width_instance_flags_partly_eaten_hack",(uint64_t)(sizeof(((struct instance_flags*)0)->partly_eaten_hack))},
{"offset_instance_flags_query_menu",(uint64_t)(offsetof(struct instance_flags,query_menu))},
{"width_instance_flags_query_menu",(uint64_t)(sizeof(((struct instance_flags*)0)->query_menu))},
{"offset_instance_flags_remember_getpos",(uint64_t)(offsetof(struct instance_flags,remember_getpos))},
{"width_instance_flags_remember_getpos",(uint64_t)(sizeof(((struct instance_flags*)0)->remember_getpos))},
{"offset_instance_flags_sad_feeling",(uint64_t)(offsetof(struct instance_flags,sad_feeling))},
{"width_instance_flags_sad_feeling",(uint64_t)(sizeof(((struct instance_flags*)0)->sad_feeling))},
{"offset_instance_flags_showdamage",(uint64_t)(offsetof(struct instance_flags,showdamage))},
{"width_instance_flags_showdamage",(uint64_t)(sizeof(((struct instance_flags*)0)->showdamage))},
{"offset_instance_flags_pending_customizations",(uint64_t)(offsetof(struct instance_flags,pending_customizations))},
{"width_instance_flags_pending_customizations",(uint64_t)(sizeof(((struct instance_flags*)0)->pending_customizations))},
{"offset_instance_flags_debug_fuzzer",(uint64_t)(offsetof(struct instance_flags,debug_fuzzer))},
{"width_instance_flags_debug_fuzzer",(uint64_t)(sizeof(((struct instance_flags*)0)->debug_fuzzer))},
{"offset_instance_flags_at_midnight",(uint64_t)(offsetof(struct instance_flags,at_midnight))},
{"width_instance_flags_at_midnight",(uint64_t)(sizeof(((struct instance_flags*)0)->at_midnight))},
{"offset_instance_flags_at_night",(uint64_t)(offsetof(struct instance_flags,at_night))},
{"width_instance_flags_at_night",(uint64_t)(sizeof(((struct instance_flags*)0)->at_night))},
{"offset_instance_flags_failing_untrap",(uint64_t)(offsetof(struct instance_flags,failing_untrap))},
{"width_instance_flags_failing_untrap",(uint64_t)(sizeof(((struct instance_flags*)0)->failing_untrap))},
{"offset_instance_flags_getdir_click",(uint64_t)(offsetof(struct instance_flags,getdir_click))},
{"width_instance_flags_getdir_click",(uint64_t)(sizeof(((struct instance_flags*)0)->getdir_click))},
{"offset_instance_flags_getloc_filter",(uint64_t)(offsetof(struct instance_flags,getloc_filter))},
{"width_instance_flags_getloc_filter",(uint64_t)(sizeof(((struct instance_flags*)0)->getloc_filter))},
{"offset_instance_flags_in_lava_effects",(uint64_t)(offsetof(struct instance_flags,in_lava_effects))},
{"width_instance_flags_in_lava_effects",(uint64_t)(sizeof(((struct instance_flags*)0)->in_lava_effects))},
{"offset_instance_flags_last_msg",(uint64_t)(offsetof(struct instance_flags,last_msg))},
{"width_instance_flags_last_msg",(uint64_t)(sizeof(((struct instance_flags*)0)->last_msg))},
{"offset_instance_flags_menuobjsyms",(uint64_t)(offsetof(struct instance_flags,menuobjsyms))},
{"width_instance_flags_menuobjsyms",(uint64_t)(sizeof(((struct instance_flags*)0)->menuobjsyms))},
{"offset_instance_flags_override_ID",(uint64_t)(offsetof(struct instance_flags,override_ID))},
{"width_instance_flags_override_ID",(uint64_t)(sizeof(((struct instance_flags*)0)->override_ID))},
{"offset_instance_flags_parse_config_file_src",(uint64_t)(offsetof(struct instance_flags,parse_config_file_src))},
{"width_instance_flags_parse_config_file_src",(uint64_t)(sizeof(((struct instance_flags*)0)->parse_config_file_src))},
{"offset_instance_flags_purge_monsters",(uint64_t)(offsetof(struct instance_flags,purge_monsters))},
{"width_instance_flags_purge_monsters",(uint64_t)(sizeof(((struct instance_flags*)0)->purge_monsters))},
{"offset_instance_flags_raw_printed",(uint64_t)(offsetof(struct instance_flags,raw_printed))},
{"width_instance_flags_raw_printed",(uint64_t)(sizeof(((struct instance_flags*)0)->raw_printed))},
{"offset_instance_flags_suppress_price",(uint64_t)(offsetof(struct instance_flags,suppress_price))},
{"width_instance_flags_suppress_price",(uint64_t)(sizeof(((struct instance_flags*)0)->suppress_price))},
{"offset_instance_flags_terrainmode",(uint64_t)(offsetof(struct instance_flags,terrainmode))},
{"width_instance_flags_terrainmode",(uint64_t)(sizeof(((struct instance_flags*)0)->terrainmode))},
{"offset_instance_flags_bgcolors",(uint64_t)(offsetof(struct instance_flags,bgcolors))},
{"width_instance_flags_bgcolors",(uint64_t)(sizeof(((struct instance_flags*)0)->bgcolors))},
{"offset_instance_flags_getloc_moveskip",(uint64_t)(offsetof(struct instance_flags,getloc_moveskip))},
{"width_instance_flags_getloc_moveskip",(uint64_t)(sizeof(((struct instance_flags*)0)->getloc_moveskip))},
{"offset_instance_flags_getloc_travelmode",(uint64_t)(offsetof(struct instance_flags,getloc_travelmode))},
{"width_instance_flags_getloc_travelmode",(uint64_t)(sizeof(((struct instance_flags*)0)->getloc_travelmode))},
{"offset_instance_flags_getloc_usemenu",(uint64_t)(offsetof(struct instance_flags,getloc_usemenu))},
{"width_instance_flags_getloc_usemenu",(uint64_t)(sizeof(((struct instance_flags*)0)->getloc_usemenu))},
{"offset_instance_flags_travelcc",(uint64_t)(offsetof(struct instance_flags,travelcc))},
{"width_instance_flags_travelcc",(uint64_t)(sizeof(((struct instance_flags*)0)->travelcc))},
{"offset_instance_flags_trav_debug",(uint64_t)(offsetof(struct instance_flags,trav_debug))},
{"width_instance_flags_trav_debug",(uint64_t)(sizeof(((struct instance_flags*)0)->trav_debug))},
{"offset_instance_flags_window_inited",(uint64_t)(offsetof(struct instance_flags,window_inited))},
{"width_instance_flags_window_inited",(uint64_t)(sizeof(((struct instance_flags*)0)->window_inited))},
{"offset_instance_flags_vision_inited",(uint64_t)(offsetof(struct instance_flags,vision_inited))},
{"width_instance_flags_vision_inited",(uint64_t)(sizeof(((struct instance_flags*)0)->vision_inited))},
{"offset_instance_flags_sanity_check",(uint64_t)(offsetof(struct instance_flags,sanity_check))},
{"width_instance_flags_sanity_check",(uint64_t)(sizeof(((struct instance_flags*)0)->sanity_check))},
{"offset_instance_flags_sanity_no_check",(uint64_t)(offsetof(struct instance_flags,sanity_no_check))},
{"width_instance_flags_sanity_no_check",(uint64_t)(sizeof(((struct instance_flags*)0)->sanity_no_check))},
{"offset_instance_flags_debug_overwrite_stairs",(uint64_t)(offsetof(struct instance_flags,debug_overwrite_stairs))},
{"width_instance_flags_debug_overwrite_stairs",(uint64_t)(sizeof(((struct instance_flags*)0)->debug_overwrite_stairs))},
{"offset_instance_flags_debug_mongen",(uint64_t)(offsetof(struct instance_flags,debug_mongen))},
{"width_instance_flags_debug_mongen",(uint64_t)(sizeof(((struct instance_flags*)0)->debug_mongen))},
{"offset_instance_flags_debug_hunger",(uint64_t)(offsetof(struct instance_flags,debug_hunger))},
{"width_instance_flags_debug_hunger",(uint64_t)(sizeof(((struct instance_flags*)0)->debug_hunger))},
{"offset_instance_flags_debug_prevent_pline",(uint64_t)(offsetof(struct instance_flags,debug_prevent_pline))},
{"width_instance_flags_debug_prevent_pline",(uint64_t)(sizeof(((struct instance_flags*)0)->debug_prevent_pline))},
{"offset_instance_flags_mon_polycontrol",(uint64_t)(offsetof(struct instance_flags,mon_polycontrol))},
{"width_instance_flags_mon_polycontrol",(uint64_t)(sizeof(((struct instance_flags*)0)->mon_polycontrol))},
{"offset_instance_flags_mon_telecontrol",(uint64_t)(offsetof(struct instance_flags,mon_telecontrol))},
{"width_instance_flags_mon_telecontrol",(uint64_t)(sizeof(((struct instance_flags*)0)->mon_telecontrol))},
{"offset_instance_flags_in_dumplog",(uint64_t)(offsetof(struct instance_flags,in_dumplog))},
{"width_instance_flags_in_dumplog",(uint64_t)(sizeof(((struct instance_flags*)0)->in_dumplog))},
{"offset_instance_flags_in_parse",(uint64_t)(offsetof(struct instance_flags,in_parse))},
{"width_instance_flags_in_parse",(uint64_t)(sizeof(((struct instance_flags*)0)->in_parse))},
{"offset_instance_flags_initoptions_noterminate",(uint64_t)(offsetof(struct instance_flags,initoptions_noterminate))},
{"width_instance_flags_initoptions_noterminate",(uint64_t)(sizeof(((struct instance_flags*)0)->initoptions_noterminate))},
{"offset_instance_flags_msg_history",(uint64_t)(offsetof(struct instance_flags,msg_history))},
{"width_instance_flags_msg_history",(uint64_t)(sizeof(((struct instance_flags*)0)->msg_history))},
{"offset_instance_flags_getpos_coords",(uint64_t)(offsetof(struct instance_flags,getpos_coords))},
{"width_instance_flags_getpos_coords",(uint64_t)(sizeof(((struct instance_flags*)0)->getpos_coords))},
{"offset_instance_flags_menuinvertmode",(uint64_t)(offsetof(struct instance_flags,menuinvertmode))},
{"width_instance_flags_menuinvertmode",(uint64_t)(sizeof(((struct instance_flags*)0)->menuinvertmode))},
{"offset_instance_flags_terrain_typ",(uint64_t)(offsetof(struct instance_flags,terrain_typ))},
{"width_instance_flags_terrain_typ",(uint64_t)(sizeof(((struct instance_flags*)0)->terrain_typ))},
{"offset_instance_flags_menu_headings",(uint64_t)(offsetof(struct instance_flags,menu_headings))},
{"width_instance_flags_menu_headings",(uint64_t)(sizeof(((struct instance_flags*)0)->menu_headings))},
{"offset_instance_flags_colorcount",(uint64_t)(offsetof(struct instance_flags,colorcount))},
{"width_instance_flags_colorcount",(uint64_t)(sizeof(((struct instance_flags*)0)->colorcount))},
{"offset_instance_flags_use_truecolor",(uint64_t)(offsetof(struct instance_flags,use_truecolor))},
{"width_instance_flags_use_truecolor",(uint64_t)(sizeof(((struct instance_flags*)0)->use_truecolor))},
{"offset_instance_flags_altmeta",(uint64_t)(offsetof(struct instance_flags,altmeta))},
{"width_instance_flags_altmeta",(uint64_t)(sizeof(((struct instance_flags*)0)->altmeta))},
{"offset_instance_flags_autodescribe",(uint64_t)(offsetof(struct instance_flags,autodescribe))},
{"width_instance_flags_autodescribe",(uint64_t)(sizeof(((struct instance_flags*)0)->autodescribe))},
{"offset_instance_flags_cbreak",(uint64_t)(offsetof(struct instance_flags,cbreak))},
{"width_instance_flags_cbreak",(uint64_t)(sizeof(((struct instance_flags*)0)->cbreak))},
{"offset_instance_flags_deferred_X",(uint64_t)(offsetof(struct instance_flags,deferred_X))},
{"width_instance_flags_deferred_X",(uint64_t)(sizeof(((struct instance_flags*)0)->deferred_X))},
{"offset_instance_flags_defer_decor",(uint64_t)(offsetof(struct instance_flags,defer_decor))},
{"width_instance_flags_defer_decor",(uint64_t)(sizeof(((struct instance_flags*)0)->defer_decor))},
{"offset_instance_flags_echo",(uint64_t)(offsetof(struct instance_flags,echo))},
{"width_instance_flags_echo",(uint64_t)(sizeof(((struct instance_flags*)0)->echo))},
{"offset_instance_flags_force_invmenu",(uint64_t)(offsetof(struct instance_flags,force_invmenu))},
{"width_instance_flags_force_invmenu",(uint64_t)(sizeof(((struct instance_flags*)0)->force_invmenu))},
{"offset_instance_flags_hilite_pile",(uint64_t)(offsetof(struct instance_flags,hilite_pile))},
{"width_instance_flags_hilite_pile",(uint64_t)(sizeof(((struct instance_flags*)0)->hilite_pile))},
{"offset_instance_flags_menu_head_objsym",(uint64_t)(offsetof(struct instance_flags,menu_head_objsym))},
{"width_instance_flags_menu_head_objsym",(uint64_t)(sizeof(((struct instance_flags*)0)->menu_head_objsym))},
{"offset_instance_flags_menu_overlay",(uint64_t)(offsetof(struct instance_flags,menu_overlay))},
{"width_instance_flags_menu_overlay",(uint64_t)(sizeof(((struct instance_flags*)0)->menu_overlay))},
{"offset_instance_flags_menu_requested",(uint64_t)(offsetof(struct instance_flags,menu_requested))},
{"width_instance_flags_menu_requested",(uint64_t)(sizeof(((struct instance_flags*)0)->menu_requested))},
{"offset_instance_flags_menu_tab_sep",(uint64_t)(offsetof(struct instance_flags,menu_tab_sep))},
{"width_instance_flags_menu_tab_sep",(uint64_t)(sizeof(((struct instance_flags*)0)->menu_tab_sep))},
{"offset_instance_flags_news",(uint64_t)(offsetof(struct instance_flags,news))},
{"width_instance_flags_news",(uint64_t)(sizeof(((struct instance_flags*)0)->news))},
{"offset_instance_flags_num_pad",(uint64_t)(offsetof(struct instance_flags,num_pad))},
{"width_instance_flags_num_pad",(uint64_t)(sizeof(((struct instance_flags*)0)->num_pad))},
{"offset_instance_flags_perm_invent",(uint64_t)(offsetof(struct instance_flags,perm_invent))},
{"width_instance_flags_perm_invent",(uint64_t)(sizeof(((struct instance_flags*)0)->perm_invent))},
{"offset_instance_flags_perm_invent_pending",(uint64_t)(offsetof(struct instance_flags,perm_invent_pending))},
{"width_instance_flags_perm_invent_pending",(uint64_t)(sizeof(((struct instance_flags*)0)->perm_invent_pending))},
{"offset_instance_flags_pricequotes",(uint64_t)(offsetof(struct instance_flags,pricequotes))},
{"width_instance_flags_pricequotes",(uint64_t)(sizeof(((struct instance_flags*)0)->pricequotes))},
{"offset_instance_flags_renameallowed",(uint64_t)(offsetof(struct instance_flags,renameallowed))},
{"width_instance_flags_renameallowed",(uint64_t)(sizeof(((struct instance_flags*)0)->renameallowed))},
{"offset_instance_flags_renameinprogress",(uint64_t)(offsetof(struct instance_flags,renameinprogress))},
{"width_instance_flags_renameinprogress",(uint64_t)(sizeof(((struct instance_flags*)0)->renameinprogress))},
{"offset_instance_flags_sounds",(uint64_t)(offsetof(struct instance_flags,sounds))},
{"width_instance_flags_sounds",(uint64_t)(sizeof(((struct instance_flags*)0)->sounds))},
{"offset_instance_flags_status_updates",(uint64_t)(offsetof(struct instance_flags,status_updates))},
{"width_instance_flags_status_updates",(uint64_t)(sizeof(((struct instance_flags*)0)->status_updates))},
{"offset_instance_flags_toptenwin",(uint64_t)(offsetof(struct instance_flags,toptenwin))},
{"width_instance_flags_toptenwin",(uint64_t)(sizeof(((struct instance_flags*)0)->toptenwin))},
{"offset_instance_flags_tux_penalty",(uint64_t)(offsetof(struct instance_flags,tux_penalty))},
{"width_instance_flags_tux_penalty",(uint64_t)(sizeof(((struct instance_flags*)0)->tux_penalty))},
{"offset_instance_flags_use_background_glyph",(uint64_t)(offsetof(struct instance_flags,use_background_glyph))},
{"width_instance_flags_use_background_glyph",(uint64_t)(sizeof(((struct instance_flags*)0)->use_background_glyph))},
{"offset_instance_flags_use_menu_color",(uint64_t)(offsetof(struct instance_flags,use_menu_color))},
{"width_instance_flags_use_menu_color",(uint64_t)(sizeof(((struct instance_flags*)0)->use_menu_color))},
{"offset_instance_flags_use_menu_glyphs",(uint64_t)(offsetof(struct instance_flags,use_menu_glyphs))},
{"width_instance_flags_use_menu_glyphs",(uint64_t)(sizeof(((struct instance_flags*)0)->use_menu_glyphs))},
{"offset_instance_flags_hilite_delta",(uint64_t)(offsetof(struct instance_flags,hilite_delta))},
{"width_instance_flags_hilite_delta",(uint64_t)(sizeof(((struct instance_flags*)0)->hilite_delta))},
{"offset_instance_flags_unhilite_deadline",(uint64_t)(offsetof(struct instance_flags,unhilite_deadline))},
{"width_instance_flags_unhilite_deadline",(uint64_t)(sizeof(((struct instance_flags*)0)->unhilite_deadline))},
{"offset_instance_flags_voices",(uint64_t)(offsetof(struct instance_flags,voices))},
{"width_instance_flags_voices",(uint64_t)(sizeof(((struct instance_flags*)0)->voices))},
{"offset_instance_flags_zerocomp",(uint64_t)(offsetof(struct instance_flags,zerocomp))},
{"width_instance_flags_zerocomp",(uint64_t)(sizeof(((struct instance_flags*)0)->zerocomp))},
{"offset_instance_flags_rlecomp",(uint64_t)(offsetof(struct instance_flags,rlecomp))},
{"width_instance_flags_rlecomp",(uint64_t)(sizeof(((struct instance_flags*)0)->rlecomp))},
{"offset_instance_flags_ice_rating",(uint64_t)(offsetof(struct instance_flags,ice_rating))},
{"width_instance_flags_ice_rating",(uint64_t)(sizeof(((struct instance_flags*)0)->ice_rating))},
{"offset_instance_flags_prev_decor",(uint64_t)(offsetof(struct instance_flags,prev_decor))},
{"width_instance_flags_prev_decor",(uint64_t)(sizeof(((struct instance_flags*)0)->prev_decor))},
{"offset_instance_flags_num_pad_mode",(uint64_t)(offsetof(struct instance_flags,num_pad_mode))},
{"width_instance_flags_num_pad_mode",(uint64_t)(sizeof(((struct instance_flags*)0)->num_pad_mode))},
{"offset_instance_flags_perminv_mode",(uint64_t)(offsetof(struct instance_flags,perminv_mode))},
{"width_instance_flags_perminv_mode",(uint64_t)(sizeof(((struct instance_flags*)0)->perminv_mode))},
{"offset_instance_flags_bouldersym",(uint64_t)(offsetof(struct instance_flags,bouldersym))},
{"width_instance_flags_bouldersym",(uint64_t)(sizeof(((struct instance_flags*)0)->bouldersym))},
{"offset_instance_flags_prevmsg_window",(uint64_t)(offsetof(struct instance_flags,prevmsg_window))},
{"width_instance_flags_prevmsg_window",(uint64_t)(sizeof(((struct instance_flags*)0)->prevmsg_window))},
{"offset_instance_flags_extmenu",(uint64_t)(offsetof(struct instance_flags,extmenu))},
{"width_instance_flags_extmenu",(uint64_t)(sizeof(((struct instance_flags*)0)->extmenu))},
{"offset_instance_flags_cmdassist",(uint64_t)(offsetof(struct instance_flags,cmdassist))},
{"width_instance_flags_cmdassist",(uint64_t)(sizeof(((struct instance_flags*)0)->cmdassist))},
{"offset_instance_flags_fireassist",(uint64_t)(offsetof(struct instance_flags,fireassist))},
{"width_instance_flags_fireassist",(uint64_t)(sizeof(((struct instance_flags*)0)->fireassist))},
{"offset_instance_flags_wizweight",(uint64_t)(offsetof(struct instance_flags,wizweight))},
{"width_instance_flags_wizweight",(uint64_t)(sizeof(((struct instance_flags*)0)->wizweight))},
{"offset_instance_flags_wizmgender",(uint64_t)(offsetof(struct instance_flags,wizmgender))},
{"width_instance_flags_wizmgender",(uint64_t)(sizeof(((struct instance_flags*)0)->wizmgender))},
{"offset_instance_flags_customcolors",(uint64_t)(offsetof(struct instance_flags,customcolors))},
{"width_instance_flags_customcolors",(uint64_t)(sizeof(((struct instance_flags*)0)->customcolors))},
{"offset_instance_flags_customsymbols",(uint64_t)(offsetof(struct instance_flags,customsymbols))},
{"width_instance_flags_customsymbols",(uint64_t)(sizeof(((struct instance_flags*)0)->customsymbols))},
{"offset_instance_flags_wc_color",(uint64_t)(offsetof(struct instance_flags,wc_color))},
{"width_instance_flags_wc_color",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_color))},
{"offset_instance_flags_wc_hilite_pet",(uint64_t)(offsetof(struct instance_flags,wc_hilite_pet))},
{"width_instance_flags_wc_hilite_pet",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_hilite_pet))},
{"offset_instance_flags_wc_ascii_map",(uint64_t)(offsetof(struct instance_flags,wc_ascii_map))},
{"width_instance_flags_wc_ascii_map",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_ascii_map))},
{"offset_instance_flags_wc_tiled_map",(uint64_t)(offsetof(struct instance_flags,wc_tiled_map))},
{"width_instance_flags_wc_tiled_map",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_tiled_map))},
{"offset_instance_flags_wc_preload_tiles",(uint64_t)(offsetof(struct instance_flags,wc_preload_tiles))},
{"width_instance_flags_wc_preload_tiles",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_preload_tiles))},
{"offset_instance_flags_wc_tile_width",(uint64_t)(offsetof(struct instance_flags,wc_tile_width))},
{"width_instance_flags_wc_tile_width",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_tile_width))},
{"offset_instance_flags_wc_tile_height",(uint64_t)(offsetof(struct instance_flags,wc_tile_height))},
{"width_instance_flags_wc_tile_height",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_tile_height))},
{"offset_instance_flags_wc_tile_file",(uint64_t)(offsetof(struct instance_flags,wc_tile_file))},
{"width_instance_flags_wc_tile_file",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_tile_file))},
{"offset_instance_flags_wc_inverse",(uint64_t)(offsetof(struct instance_flags,wc_inverse))},
{"width_instance_flags_wc_inverse",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_inverse))},
{"offset_instance_flags_wc_align_status",(uint64_t)(offsetof(struct instance_flags,wc_align_status))},
{"width_instance_flags_wc_align_status",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_align_status))},
{"offset_instance_flags_wc_align_message",(uint64_t)(offsetof(struct instance_flags,wc_align_message))},
{"width_instance_flags_wc_align_message",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_align_message))},
{"offset_instance_flags_wc_vary_msgcount",(uint64_t)(offsetof(struct instance_flags,wc_vary_msgcount))},
{"width_instance_flags_wc_vary_msgcount",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_vary_msgcount))},
{"offset_instance_flags_wcolors",(uint64_t)(offsetof(struct instance_flags,wcolors))},
{"width_instance_flags_wcolors",(uint64_t)(sizeof(((struct instance_flags*)0)->wcolors))},
{"offset_instance_flags_wc_font_map",(uint64_t)(offsetof(struct instance_flags,wc_font_map))},
{"width_instance_flags_wc_font_map",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_font_map))},
{"offset_instance_flags_wc_font_message",(uint64_t)(offsetof(struct instance_flags,wc_font_message))},
{"width_instance_flags_wc_font_message",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_font_message))},
{"offset_instance_flags_wc_font_status",(uint64_t)(offsetof(struct instance_flags,wc_font_status))},
{"width_instance_flags_wc_font_status",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_font_status))},
{"offset_instance_flags_wc_font_menu",(uint64_t)(offsetof(struct instance_flags,wc_font_menu))},
{"width_instance_flags_wc_font_menu",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_font_menu))},
{"offset_instance_flags_wc_font_text",(uint64_t)(offsetof(struct instance_flags,wc_font_text))},
{"width_instance_flags_wc_font_text",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_font_text))},
{"offset_instance_flags_wc_fontsiz_map",(uint64_t)(offsetof(struct instance_flags,wc_fontsiz_map))},
{"width_instance_flags_wc_fontsiz_map",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_fontsiz_map))},
{"offset_instance_flags_wc_fontsiz_message",(uint64_t)(offsetof(struct instance_flags,wc_fontsiz_message))},
{"width_instance_flags_wc_fontsiz_message",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_fontsiz_message))},
{"offset_instance_flags_wc_fontsiz_status",(uint64_t)(offsetof(struct instance_flags,wc_fontsiz_status))},
{"width_instance_flags_wc_fontsiz_status",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_fontsiz_status))},
{"offset_instance_flags_wc_fontsiz_menu",(uint64_t)(offsetof(struct instance_flags,wc_fontsiz_menu))},
{"width_instance_flags_wc_fontsiz_menu",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_fontsiz_menu))},
{"offset_instance_flags_wc_fontsiz_text",(uint64_t)(offsetof(struct instance_flags,wc_fontsiz_text))},
{"width_instance_flags_wc_fontsiz_text",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_fontsiz_text))},
{"offset_instance_flags_wc_scroll_amount",(uint64_t)(offsetof(struct instance_flags,wc_scroll_amount))},
{"width_instance_flags_wc_scroll_amount",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_scroll_amount))},
{"offset_instance_flags_wc_scroll_margin",(uint64_t)(offsetof(struct instance_flags,wc_scroll_margin))},
{"width_instance_flags_wc_scroll_margin",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_scroll_margin))},
{"offset_instance_flags_wc_map_mode",(uint64_t)(offsetof(struct instance_flags,wc_map_mode))},
{"width_instance_flags_wc_map_mode",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_map_mode))},
{"offset_instance_flags_wc_player_selection",(uint64_t)(offsetof(struct instance_flags,wc_player_selection))},
{"width_instance_flags_wc_player_selection",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_player_selection))},
{"offset_instance_flags_wc_splash_screen",(uint64_t)(offsetof(struct instance_flags,wc_splash_screen))},
{"width_instance_flags_wc_splash_screen",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_splash_screen))},
{"offset_instance_flags_wc_popup_dialog",(uint64_t)(offsetof(struct instance_flags,wc_popup_dialog))},
{"width_instance_flags_wc_popup_dialog",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_popup_dialog))},
{"offset_instance_flags_wc_eight_bit_input",(uint64_t)(offsetof(struct instance_flags,wc_eight_bit_input))},
{"width_instance_flags_wc_eight_bit_input",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_eight_bit_input))},
{"offset_instance_flags_wc2_fullscreen",(uint64_t)(offsetof(struct instance_flags,wc2_fullscreen))},
{"width_instance_flags_wc2_fullscreen",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_fullscreen))},
{"offset_instance_flags_wc2_softkeyboard",(uint64_t)(offsetof(struct instance_flags,wc2_softkeyboard))},
{"width_instance_flags_wc2_softkeyboard",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_softkeyboard))},
{"offset_instance_flags_wc2_wraptext",(uint64_t)(offsetof(struct instance_flags,wc2_wraptext))},
{"width_instance_flags_wc2_wraptext",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_wraptext))},
{"offset_instance_flags_wc2_selectsaved",(uint64_t)(offsetof(struct instance_flags,wc2_selectsaved))},
{"width_instance_flags_wc2_selectsaved",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_selectsaved))},
{"offset_instance_flags_wc2_darkgray",(uint64_t)(offsetof(struct instance_flags,wc2_darkgray))},
{"width_instance_flags_wc2_darkgray",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_darkgray))},
{"offset_instance_flags_wc2_hitpointbar",(uint64_t)(offsetof(struct instance_flags,wc2_hitpointbar))},
{"width_instance_flags_wc2_hitpointbar",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_hitpointbar))},
{"offset_instance_flags_wc2_guicolor",(uint64_t)(offsetof(struct instance_flags,wc2_guicolor))},
{"width_instance_flags_wc2_guicolor",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_guicolor))},
{"offset_instance_flags_wc_mouse_support",(uint64_t)(offsetof(struct instance_flags,wc_mouse_support))},
{"width_instance_flags_wc_mouse_support",(uint64_t)(sizeof(((struct instance_flags*)0)->wc_mouse_support))},
{"offset_instance_flags_wc2_term_cols",(uint64_t)(offsetof(struct instance_flags,wc2_term_cols))},
{"width_instance_flags_wc2_term_cols",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_term_cols))},
{"offset_instance_flags_wc2_term_rows",(uint64_t)(offsetof(struct instance_flags,wc2_term_rows))},
{"width_instance_flags_wc2_term_rows",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_term_rows))},
{"offset_instance_flags_wc2_statuslines",(uint64_t)(offsetof(struct instance_flags,wc2_statuslines))},
{"width_instance_flags_wc2_statuslines",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_statuslines))},
{"offset_instance_flags_wc2_windowborders",(uint64_t)(offsetof(struct instance_flags,wc2_windowborders))},
{"width_instance_flags_wc2_windowborders",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_windowborders))},
{"offset_instance_flags_wc2_petattr",(uint64_t)(offsetof(struct instance_flags,wc2_petattr))},
{"width_instance_flags_wc2_petattr",(uint64_t)(sizeof(((struct instance_flags*)0)->wc2_petattr))},
{"offset_instance_flags_debug",(uint64_t)(offsetof(struct instance_flags,debug))},
{"width_instance_flags_debug",(uint64_t)(sizeof(((struct instance_flags*)0)->debug))},
{"offset_instance_flags_windowtype_locked",(uint64_t)(offsetof(struct instance_flags,windowtype_locked))},
{"width_instance_flags_windowtype_locked",(uint64_t)(sizeof(((struct instance_flags*)0)->windowtype_locked))},
{"offset_instance_flags_windowtype_deferred",(uint64_t)(offsetof(struct instance_flags,windowtype_deferred))},
{"width_instance_flags_windowtype_deferred",(uint64_t)(sizeof(((struct instance_flags*)0)->windowtype_deferred))},
{"offset_instance_flags_returning_missile",(uint64_t)(offsetof(struct instance_flags,returning_missile))},
{"width_instance_flags_returning_missile",(uint64_t)(sizeof(((struct instance_flags*)0)->returning_missile))},
{"offset_instance_flags_wiz_error_flag",(uint64_t)(offsetof(struct instance_flags,wiz_error_flag))},
{"width_instance_flags_wiz_error_flag",(uint64_t)(sizeof(((struct instance_flags*)0)->wiz_error_flag))},
{"offset_instance_flags_explore_error_flag",(uint64_t)(offsetof(struct instance_flags,explore_error_flag))},
{"width_instance_flags_explore_error_flag",(uint64_t)(sizeof(((struct instance_flags*)0)->explore_error_flag))},
{"offset_instance_flags_obsolete",(uint64_t)(offsetof(struct instance_flags,obsolete))},
{"width_instance_flags_obsolete",(uint64_t)(sizeof(((struct instance_flags*)0)->obsolete))},
{"size_instance_globals_a",(uint64_t)(sizeof(struct instance_globals_a))},
{"align_instance_globals_a",(uint64_t)(__alignof__(struct instance_globals_a))},
{"offset_instance_globals_a_afternmv",(uint64_t)(offsetof(struct instance_globals_a,afternmv))},
{"width_instance_globals_a_afternmv",(uint64_t)(sizeof(((struct instance_globals_a*)0)->afternmv))},
{"offset_instance_globals_a_already_found_flag",(uint64_t)(offsetof(struct instance_globals_a,already_found_flag))},
{"width_instance_globals_a_already_found_flag",(uint64_t)(sizeof(((struct instance_globals_a*)0)->already_found_flag))},
{"offset_instance_globals_a_at_ladder",(uint64_t)(offsetof(struct instance_globals_a,at_ladder))},
{"width_instance_globals_a_at_ladder",(uint64_t)(sizeof(((struct instance_globals_a*)0)->at_ladder))},
{"offset_instance_globals_a_apelist",(uint64_t)(offsetof(struct instance_globals_a,apelist))},
{"width_instance_globals_a_apelist",(uint64_t)(sizeof(((struct instance_globals_a*)0)->apelist))},
{"offset_instance_globals_a_amulets",(uint64_t)(offsetof(struct instance_globals_a,amulets))},
{"width_instance_globals_a_amulets",(uint64_t)(sizeof(((struct instance_globals_a*)0)->amulets))},
{"offset_instance_globals_a_animal_list",(uint64_t)(offsetof(struct instance_globals_a,animal_list))},
{"width_instance_globals_a_animal_list",(uint64_t)(sizeof(((struct instance_globals_a*)0)->animal_list))},
{"offset_instance_globals_a_animal_list_count",(uint64_t)(offsetof(struct instance_globals_a,animal_list_count))},
{"width_instance_globals_a_animal_list_count",(uint64_t)(sizeof(((struct instance_globals_a*)0)->animal_list_count))},
{"offset_instance_globals_a_A_first_hint",(uint64_t)(offsetof(struct instance_globals_a,A_first_hint))},
{"width_instance_globals_a_A_first_hint",(uint64_t)(sizeof(((struct instance_globals_a*)0)->A_first_hint))},
{"offset_instance_globals_a_A_second_hint",(uint64_t)(offsetof(struct instance_globals_a,A_second_hint))},
{"width_instance_globals_a_A_second_hint",(uint64_t)(sizeof(((struct instance_globals_a*)0)->A_second_hint))},
{"offset_instance_globals_a_abort_looting",(uint64_t)(offsetof(struct instance_globals_a,abort_looting))},
{"width_instance_globals_a_abort_looting",(uint64_t)(sizeof(((struct instance_globals_a*)0)->abort_looting))},
{"offset_instance_globals_a_auto_credit",(uint64_t)(offsetof(struct instance_globals_a,auto_credit))},
{"width_instance_globals_a_auto_credit",(uint64_t)(sizeof(((struct instance_globals_a*)0)->auto_credit))},
{"offset_instance_globals_a_active_soundlib",(uint64_t)(offsetof(struct instance_globals_a,active_soundlib))},
{"width_instance_globals_a_active_soundlib",(uint64_t)(sizeof(((struct instance_globals_a*)0)->active_soundlib))},
{"offset_instance_globals_a_acid_ctx",(uint64_t)(offsetof(struct instance_globals_a,acid_ctx))},
{"width_instance_globals_a_acid_ctx",(uint64_t)(sizeof(((struct instance_globals_a*)0)->acid_ctx))},
{"offset_instance_globals_a_havestate",(uint64_t)(offsetof(struct instance_globals_a,havestate))},
{"width_instance_globals_a_havestate",(uint64_t)(sizeof(((struct instance_globals_a*)0)->havestate))},
{"size_instance_globals_b",(uint64_t)(sizeof(struct instance_globals_b))},
{"align_instance_globals_b",(uint64_t)(__alignof__(struct instance_globals_b))},
{"offset_instance_globals_b_blstats",(uint64_t)(offsetof(struct instance_globals_b,blstats))},
{"width_instance_globals_b_blstats",(uint64_t)(sizeof(((struct instance_globals_b*)0)->blstats))},
{"offset_instance_globals_b_blinit",(uint64_t)(offsetof(struct instance_globals_b,blinit))},
{"width_instance_globals_b_blinit",(uint64_t)(sizeof(((struct instance_globals_b*)0)->blinit))},
{"offset_instance_globals_b_bl_hilite_moves",(uint64_t)(offsetof(struct instance_globals_b,bl_hilite_moves))},
{"width_instance_globals_b_bl_hilite_moves",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bl_hilite_moves))},
{"offset_instance_globals_b_bhitpos",(uint64_t)(offsetof(struct instance_globals_b,bhitpos))},
{"width_instance_globals_b_bhitpos",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bhitpos))},
{"offset_instance_globals_b_billobjs",(uint64_t)(offsetof(struct instance_globals_b,billobjs))},
{"width_instance_globals_b_billobjs",(uint64_t)(sizeof(((struct instance_globals_b*)0)->billobjs))},
{"offset_instance_globals_b_bones",(uint64_t)(offsetof(struct instance_globals_b,bones))},
{"width_instance_globals_b_bones",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bones))},
{"offset_instance_globals_b_bldrpush_oid",(uint64_t)(offsetof(struct instance_globals_b,bldrpush_oid))},
{"width_instance_globals_b_bldrpush_oid",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bldrpush_oid))},
{"offset_instance_globals_b_bldrpushtime",(uint64_t)(offsetof(struct instance_globals_b,bldrpushtime))},
{"width_instance_globals_b_bldrpushtime",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bldrpushtime))},
{"offset_instance_globals_b_bughack",(uint64_t)(offsetof(struct instance_globals_b,bughack))},
{"width_instance_globals_b_bughack",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bughack))},
{"offset_instance_globals_b_bucx_filter",(uint64_t)(offsetof(struct instance_globals_b,bucx_filter))},
{"width_instance_globals_b_bucx_filter",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bucx_filter))},
{"offset_instance_globals_b_buzzer",(uint64_t)(offsetof(struct instance_globals_b,buzzer))},
{"width_instance_globals_b_buzzer",(uint64_t)(sizeof(((struct instance_globals_b*)0)->buzzer))},
{"offset_instance_globals_b_bot_disabled",(uint64_t)(offsetof(struct instance_globals_b,bot_disabled))},
{"width_instance_globals_b_bot_disabled",(uint64_t)(sizeof(((struct instance_globals_b*)0)->bot_disabled))},
{"offset_instance_globals_b_havestate",(uint64_t)(offsetof(struct instance_globals_b,havestate))},
{"width_instance_globals_b_havestate",(uint64_t)(sizeof(((struct instance_globals_b*)0)->havestate))},
{"size_instance_globals_c",(uint64_t)(sizeof(struct instance_globals_c))},
{"align_instance_globals_c",(uint64_t)(__alignof__(struct instance_globals_c))},
{"offset_instance_globals_c_command_queue",(uint64_t)(offsetof(struct instance_globals_c,command_queue))},
{"width_instance_globals_c_command_queue",(uint64_t)(sizeof(((struct instance_globals_c*)0)->command_queue))},
{"offset_instance_globals_c_cond_hilites",(uint64_t)(offsetof(struct instance_globals_c,cond_hilites))},
{"width_instance_globals_c_cond_hilites",(uint64_t)(sizeof(((struct instance_globals_c*)0)->cond_hilites))},
{"offset_instance_globals_c_condmenu_sortorder",(uint64_t)(offsetof(struct instance_globals_c,condmenu_sortorder))},
{"width_instance_globals_c_condmenu_sortorder",(uint64_t)(sizeof(((struct instance_globals_c*)0)->condmenu_sortorder))},
{"offset_instance_globals_c_Cmd",(uint64_t)(offsetof(struct instance_globals_c,Cmd))},
{"width_instance_globals_c_Cmd",(uint64_t)(sizeof(((struct instance_globals_c*)0)->Cmd))},
{"offset_instance_globals_c_clicklook_cc",(uint64_t)(offsetof(struct instance_globals_c,clicklook_cc))},
{"width_instance_globals_c_clicklook_cc",(uint64_t)(sizeof(((struct instance_globals_c*)0)->clicklook_cc))},
{"offset_instance_globals_c_chosen_windowtype",(uint64_t)(offsetof(struct instance_globals_c,chosen_windowtype))},
{"width_instance_globals_c_chosen_windowtype",(uint64_t)(sizeof(((struct instance_globals_c*)0)->chosen_windowtype))},
{"offset_instance_globals_c_cmd_key",(uint64_t)(offsetof(struct instance_globals_c,cmd_key))},
{"width_instance_globals_c_cmd_key",(uint64_t)(sizeof(((struct instance_globals_c*)0)->cmd_key))},
{"offset_instance_globals_c_cmd_bind",(uint64_t)(offsetof(struct instance_globals_c,cmd_bind))},
{"width_instance_globals_c_cmd_bind",(uint64_t)(sizeof(((struct instance_globals_c*)0)->cmd_bind))},
{"offset_instance_globals_c_command_count",(uint64_t)(offsetof(struct instance_globals_c,command_count))},
{"width_instance_globals_c_command_count",(uint64_t)(sizeof(((struct instance_globals_c*)0)->command_count))},
{"offset_instance_globals_c_current_wand",(uint64_t)(offsetof(struct instance_globals_c,current_wand))},
{"width_instance_globals_c_current_wand",(uint64_t)(sizeof(((struct instance_globals_c*)0)->current_wand))},
{"offset_instance_globals_c_catname",(uint64_t)(offsetof(struct instance_globals_c,catname))},
{"width_instance_globals_c_catname",(uint64_t)(sizeof(((struct instance_globals_c*)0)->catname))},
{"offset_instance_globals_c_crash_email",(uint64_t)(offsetof(struct instance_globals_c,crash_email))},
{"width_instance_globals_c_crash_email",(uint64_t)(sizeof(((struct instance_globals_c*)0)->crash_email))},
{"offset_instance_globals_c_crash_name",(uint64_t)(offsetof(struct instance_globals_c,crash_name))},
{"width_instance_globals_c_crash_name",(uint64_t)(sizeof(((struct instance_globals_c*)0)->crash_name))},
{"offset_instance_globals_c_crash_urlmax",(uint64_t)(offsetof(struct instance_globals_c,crash_urlmax))},
{"width_instance_globals_c_crash_urlmax",(uint64_t)(sizeof(((struct instance_globals_c*)0)->crash_urlmax))},
{"offset_instance_globals_c_currentgraphics",(uint64_t)(offsetof(struct instance_globals_c,currentgraphics))},
{"width_instance_globals_c_currentgraphics",(uint64_t)(sizeof(((struct instance_globals_c*)0)->currentgraphics))},
{"offset_instance_globals_c_cmdline_rcfile",(uint64_t)(offsetof(struct instance_globals_c,cmdline_rcfile))},
{"width_instance_globals_c_cmdline_rcfile",(uint64_t)(sizeof(((struct instance_globals_c*)0)->cmdline_rcfile))},
{"offset_instance_globals_c_config_section_chosen",(uint64_t)(offsetof(struct instance_globals_c,config_section_chosen))},
{"width_instance_globals_c_config_section_chosen",(uint64_t)(sizeof(((struct instance_globals_c*)0)->config_section_chosen))},
{"offset_instance_globals_c_config_section_current",(uint64_t)(offsetof(struct instance_globals_c,config_section_current))},
{"width_instance_globals_c_config_section_current",(uint64_t)(sizeof(((struct instance_globals_c*)0)->config_section_current))},
{"offset_instance_globals_c_chosen_symset_start",(uint64_t)(offsetof(struct instance_globals_c,chosen_symset_start))},
{"width_instance_globals_c_chosen_symset_start",(uint64_t)(sizeof(((struct instance_globals_c*)0)->chosen_symset_start))},
{"offset_instance_globals_c_chosen_symset_end",(uint64_t)(offsetof(struct instance_globals_c,chosen_symset_end))},
{"width_instance_globals_c_chosen_symset_end",(uint64_t)(sizeof(((struct instance_globals_c*)0)->chosen_symset_end))},
{"offset_instance_globals_c_cached_pickinv_win",(uint64_t)(offsetof(struct instance_globals_c,cached_pickinv_win))},
{"width_instance_globals_c_cached_pickinv_win",(uint64_t)(sizeof(((struct instance_globals_c*)0)->cached_pickinv_win))},
{"offset_instance_globals_c_core_invent_state",(uint64_t)(offsetof(struct instance_globals_c,core_invent_state))},
{"width_instance_globals_c_core_invent_state",(uint64_t)(sizeof(((struct instance_globals_c*)0)->core_invent_state))},
{"offset_instance_globals_c_cmdline_windowsys",(uint64_t)(offsetof(struct instance_globals_c,cmdline_windowsys))},
{"width_instance_globals_c_cmdline_windowsys",(uint64_t)(sizeof(((struct instance_globals_c*)0)->cmdline_windowsys))},
{"offset_instance_globals_c_color_colorings",(uint64_t)(offsetof(struct instance_globals_c,color_colorings))},
{"width_instance_globals_c_color_colorings",(uint64_t)(sizeof(((struct instance_globals_c*)0)->color_colorings))},
{"offset_instance_globals_c_current_container",(uint64_t)(offsetof(struct instance_globals_c,current_container))},
{"width_instance_globals_c_current_container",(uint64_t)(sizeof(((struct instance_globals_c*)0)->current_container))},
{"offset_instance_globals_c_class_filter",(uint64_t)(offsetof(struct instance_globals_c,class_filter))},
{"width_instance_globals_c_class_filter",(uint64_t)(sizeof(((struct instance_globals_c*)0)->class_filter))},
{"offset_instance_globals_c_cvt_buf",(uint64_t)(offsetof(struct instance_globals_c,cvt_buf))},
{"width_instance_globals_c_cvt_buf",(uint64_t)(sizeof(((struct instance_globals_c*)0)->cvt_buf))},
{"offset_instance_globals_c_chosen_soundlib",(uint64_t)(offsetof(struct instance_globals_c,chosen_soundlib))},
{"width_instance_globals_c_chosen_soundlib",(uint64_t)(sizeof(((struct instance_globals_c*)0)->chosen_soundlib))},
{"offset_instance_globals_c_coder",(uint64_t)(offsetof(struct instance_globals_c,coder))},
{"width_instance_globals_c_coder",(uint64_t)(sizeof(((struct instance_globals_c*)0)->coder))},
{"offset_instance_globals_c_corpsenm_digested",(uint64_t)(offsetof(struct instance_globals_c,corpsenm_digested))},
{"width_instance_globals_c_corpsenm_digested",(uint64_t)(sizeof(((struct instance_globals_c*)0)->corpsenm_digested))},
{"offset_instance_globals_c_converted_savefile_loaded",(uint64_t)(offsetof(struct instance_globals_c,converted_savefile_loaded))},
{"width_instance_globals_c_converted_savefile_loaded",(uint64_t)(sizeof(((struct instance_globals_c*)0)->converted_savefile_loaded))},
{"offset_instance_globals_c_havestate",(uint64_t)(offsetof(struct instance_globals_c,havestate))},
{"width_instance_globals_c_havestate",(uint64_t)(sizeof(((struct instance_globals_c*)0)->havestate))},
{"size_instance_globals_d",(uint64_t)(sizeof(struct instance_globals_d))},
{"align_instance_globals_d",(uint64_t)(__alignof__(struct instance_globals_d))},
{"offset_instance_globals_d_doorindex",(uint64_t)(offsetof(struct instance_globals_d,doorindex))},
{"width_instance_globals_d_doorindex",(uint64_t)(sizeof(((struct instance_globals_d*)0)->doorindex))},
{"offset_instance_globals_d_done_money",(uint64_t)(offsetof(struct instance_globals_d,done_money))},
{"width_instance_globals_d_done_money",(uint64_t)(sizeof(((struct instance_globals_d*)0)->done_money))},
{"offset_instance_globals_d_domove_attempting",(uint64_t)(offsetof(struct instance_globals_d,domove_attempting))},
{"width_instance_globals_d_domove_attempting",(uint64_t)(sizeof(((struct instance_globals_d*)0)->domove_attempting))},
{"offset_instance_globals_d_domove_succeeded",(uint64_t)(offsetof(struct instance_globals_d,domove_succeeded))},
{"width_instance_globals_d_domove_succeeded",(uint64_t)(sizeof(((struct instance_globals_d*)0)->domove_succeeded))},
{"offset_instance_globals_d_defer_see_monsters",(uint64_t)(offsetof(struct instance_globals_d,defer_see_monsters))},
{"width_instance_globals_d_defer_see_monsters",(uint64_t)(sizeof(((struct instance_globals_d*)0)->defer_see_monsters))},
{"offset_instance_globals_d_did_dig_msg",(uint64_t)(offsetof(struct instance_globals_d,did_dig_msg))},
{"width_instance_globals_d_did_dig_msg",(uint64_t)(sizeof(((struct instance_globals_d*)0)->did_dig_msg))},
{"offset_instance_globals_d_dfr_pre_msg",(uint64_t)(offsetof(struct instance_globals_d,dfr_pre_msg))},
{"width_instance_globals_d_dfr_pre_msg",(uint64_t)(sizeof(((struct instance_globals_d*)0)->dfr_pre_msg))},
{"offset_instance_globals_d_dfr_post_msg",(uint64_t)(offsetof(struct instance_globals_d,dfr_post_msg))},
{"width_instance_globals_d_dfr_post_msg",(uint64_t)(sizeof(((struct instance_globals_d*)0)->dfr_post_msg))},
{"offset_instance_globals_d_did_nothing_flag",(uint64_t)(offsetof(struct instance_globals_d,did_nothing_flag))},
{"width_instance_globals_d_did_nothing_flag",(uint64_t)(sizeof(((struct instance_globals_d*)0)->did_nothing_flag))},
{"offset_instance_globals_d_dogname",(uint64_t)(offsetof(struct instance_globals_d,dogname))},
{"width_instance_globals_d_dogname",(uint64_t)(sizeof(((struct instance_globals_d*)0)->dogname))},
{"offset_instance_globals_d_done_seq",(uint64_t)(offsetof(struct instance_globals_d,done_seq))},
{"width_instance_globals_d_done_seq",(uint64_t)(sizeof(((struct instance_globals_d*)0)->done_seq))},
{"offset_instance_globals_d_disintegested",(uint64_t)(offsetof(struct instance_globals_d,disintegested))},
{"width_instance_globals_d_disintegested",(uint64_t)(sizeof(((struct instance_globals_d*)0)->disintegested))},
{"offset_instance_globals_d_distantname",(uint64_t)(offsetof(struct instance_globals_d,distantname))},
{"width_instance_globals_d_distantname",(uint64_t)(sizeof(((struct instance_globals_d*)0)->distantname))},
{"offset_instance_globals_d_decor_fumble_override",(uint64_t)(offsetof(struct instance_globals_d,decor_fumble_override))},
{"width_instance_globals_d_decor_fumble_override",(uint64_t)(sizeof(((struct instance_globals_d*)0)->decor_fumble_override))},
{"offset_instance_globals_d_decor_levitate_override",(uint64_t)(offsetof(struct instance_globals_d,decor_levitate_override))},
{"width_instance_globals_d_decor_levitate_override",(uint64_t)(sizeof(((struct instance_globals_d*)0)->decor_levitate_override))},
{"offset_instance_globals_d_deferred_showpaths",(uint64_t)(offsetof(struct instance_globals_d,deferred_showpaths))},
{"width_instance_globals_d_deferred_showpaths",(uint64_t)(sizeof(((struct instance_globals_d*)0)->deferred_showpaths))},
{"offset_instance_globals_d_deferred_showpaths_dir",(uint64_t)(offsetof(struct instance_globals_d,deferred_showpaths_dir))},
{"width_instance_globals_d_deferred_showpaths_dir",(uint64_t)(sizeof(((struct instance_globals_d*)0)->deferred_showpaths_dir))},
{"offset_instance_globals_d_havestate",(uint64_t)(offsetof(struct instance_globals_d,havestate))},
{"width_instance_globals_d_havestate",(uint64_t)(sizeof(((struct instance_globals_d*)0)->havestate))},
{"size_instance_globals_e",(uint64_t)(sizeof(struct instance_globals_e))},
{"align_instance_globals_e",(uint64_t)(__alignof__(struct instance_globals_e))},
{"offset_instance_globals_e_en_win",(uint64_t)(offsetof(struct instance_globals_e,en_win))},
{"width_instance_globals_e_en_win",(uint64_t)(sizeof(((struct instance_globals_e*)0)->en_win))},
{"offset_instance_globals_e_en_via_menu",(uint64_t)(offsetof(struct instance_globals_e,en_via_menu))},
{"width_instance_globals_e_en_via_menu",(uint64_t)(sizeof(((struct instance_globals_e*)0)->en_via_menu))},
{"offset_instance_globals_e_ext_tlist",(uint64_t)(offsetof(struct instance_globals_e,ext_tlist))},
{"width_instance_globals_e_ext_tlist",(uint64_t)(sizeof(((struct instance_globals_e*)0)->ext_tlist))},
{"offset_instance_globals_e_eatmbuf",(uint64_t)(offsetof(struct instance_globals_e,eatmbuf))},
{"width_instance_globals_e_eatmbuf",(uint64_t)(sizeof(((struct instance_globals_e*)0)->eatmbuf))},
{"offset_instance_globals_e_ebubbles",(uint64_t)(offsetof(struct instance_globals_e,ebubbles))},
{"width_instance_globals_e_ebubbles",(uint64_t)(sizeof(((struct instance_globals_e*)0)->ebubbles))},
{"offset_instance_globals_e_early_raw_messages",(uint64_t)(offsetof(struct instance_globals_e,early_raw_messages))},
{"width_instance_globals_e_early_raw_messages",(uint64_t)(sizeof(((struct instance_globals_e*)0)->early_raw_messages))},
{"offset_instance_globals_e_havestate",(uint64_t)(offsetof(struct instance_globals_e,havestate))},
{"width_instance_globals_e_havestate",(uint64_t)(sizeof(((struct instance_globals_e*)0)->havestate))},
{"size_instance_globals_f",(uint64_t)(sizeof(struct instance_globals_f))},
{"align_instance_globals_f",(uint64_t)(__alignof__(struct instance_globals_f))},
{"offset_instance_globals_f_ftrap",(uint64_t)(offsetof(struct instance_globals_f,ftrap))},
{"width_instance_globals_f_ftrap",(uint64_t)(sizeof(((struct instance_globals_f*)0)->ftrap))},
{"offset_instance_globals_f_fqn_prefix",(uint64_t)(offsetof(struct instance_globals_f,fqn_prefix))},
{"width_instance_globals_f_fqn_prefix",(uint64_t)(sizeof(((struct instance_globals_f*)0)->fqn_prefix))},
{"offset_instance_globals_f_ffruit",(uint64_t)(offsetof(struct instance_globals_f,ffruit))},
{"width_instance_globals_f_ffruit",(uint64_t)(sizeof(((struct instance_globals_f*)0)->ffruit))},
{"offset_instance_globals_f_force_save_hs",(uint64_t)(offsetof(struct instance_globals_f,force_save_hs))},
{"width_instance_globals_f_force_save_hs",(uint64_t)(sizeof(((struct instance_globals_f*)0)->force_save_hs))},
{"offset_instance_globals_f_far_noise",(uint64_t)(offsetof(struct instance_globals_f,far_noise))},
{"width_instance_globals_f_far_noise",(uint64_t)(sizeof(((struct instance_globals_f*)0)->far_noise))},
{"offset_instance_globals_f_false_rumor_size",(uint64_t)(offsetof(struct instance_globals_f,false_rumor_size))},
{"width_instance_globals_f_false_rumor_size",(uint64_t)(sizeof(((struct instance_globals_f*)0)->false_rumor_size))},
{"offset_instance_globals_f_false_rumor_start",(uint64_t)(offsetof(struct instance_globals_f,false_rumor_start))},
{"width_instance_globals_f_false_rumor_start",(uint64_t)(sizeof(((struct instance_globals_f*)0)->false_rumor_start))},
{"offset_instance_globals_f_false_rumor_end",(uint64_t)(offsetof(struct instance_globals_f,false_rumor_end))},
{"width_instance_globals_f_false_rumor_end",(uint64_t)(sizeof(((struct instance_globals_f*)0)->false_rumor_end))},
{"offset_instance_globals_f_followmsg",(uint64_t)(offsetof(struct instance_globals_f,followmsg))},
{"width_instance_globals_f_followmsg",(uint64_t)(sizeof(((struct instance_globals_f*)0)->followmsg))},
{"offset_instance_globals_f_havestate",(uint64_t)(offsetof(struct instance_globals_f,havestate))},
{"width_instance_globals_f_havestate",(uint64_t)(sizeof(((struct instance_globals_f*)0)->havestate))},
{"size_instance_globals_g",(uint64_t)(sizeof(struct instance_globals_g))},
{"align_instance_globals_g",(uint64_t)(__alignof__(struct instance_globals_g))},
{"offset_instance_globals_g_gbuf",(uint64_t)(offsetof(struct instance_globals_g,gbuf))},
{"width_instance_globals_g_gbuf",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gbuf))},
{"offset_instance_globals_g_gbuf_start",(uint64_t)(offsetof(struct instance_globals_g,gbuf_start))},
{"width_instance_globals_g_gbuf_start",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gbuf_start))},
{"offset_instance_globals_g_gbuf_stop",(uint64_t)(offsetof(struct instance_globals_g,gbuf_stop))},
{"width_instance_globals_g_gbuf_stop",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gbuf_stop))},
{"offset_instance_globals_g_getposx",(uint64_t)(offsetof(struct instance_globals_g,getposx))},
{"width_instance_globals_g_getposx",(uint64_t)(sizeof(((struct instance_globals_g*)0)->getposx))},
{"offset_instance_globals_g_getposy",(uint64_t)(offsetof(struct instance_globals_g,getposy))},
{"width_instance_globals_g_getposy",(uint64_t)(sizeof(((struct instance_globals_g*)0)->getposy))},
{"offset_instance_globals_g_gloc_filter_map",(uint64_t)(offsetof(struct instance_globals_g,gloc_filter_map))},
{"width_instance_globals_g_gloc_filter_map",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gloc_filter_map))},
{"offset_instance_globals_g_gloc_filter_floodfill_match_glyph",(uint64_t)(offsetof(struct instance_globals_g,gloc_filter_floodfill_match_glyph))},
{"width_instance_globals_g_gloc_filter_floodfill_match_glyph",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gloc_filter_floodfill_match_glyph))},
{"offset_instance_globals_g_gtyp",(uint64_t)(offsetof(struct instance_globals_g,gtyp))},
{"width_instance_globals_g_gtyp",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gtyp))},
{"offset_instance_globals_g_gx",(uint64_t)(offsetof(struct instance_globals_g,gx))},
{"width_instance_globals_g_gx",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gx))},
{"offset_instance_globals_g_gy",(uint64_t)(offsetof(struct instance_globals_g,gy))},
{"width_instance_globals_g_gy",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gy))},
{"offset_instance_globals_g_gate_str",(uint64_t)(offsetof(struct instance_globals_g,gate_str))},
{"width_instance_globals_g_gate_str",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gate_str))},
{"offset_instance_globals_g_gems",(uint64_t)(offsetof(struct instance_globals_g,gems))},
{"width_instance_globals_g_gems",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gems))},
{"offset_instance_globals_g_glyph_reset_timestamp",(uint64_t)(offsetof(struct instance_globals_g,glyph_reset_timestamp))},
{"width_instance_globals_g_glyph_reset_timestamp",(uint64_t)(sizeof(((struct instance_globals_g*)0)->glyph_reset_timestamp))},
{"offset_instance_globals_g_gmst_stored",(uint64_t)(offsetof(struct instance_globals_g,gmst_stored))},
{"width_instance_globals_g_gmst_stored",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gmst_stored))},
{"offset_instance_globals_g_gmst_moves",(uint64_t)(offsetof(struct instance_globals_g,gmst_moves))},
{"width_instance_globals_g_gmst_moves",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gmst_moves))},
{"offset_instance_globals_g_gmst_invent",(uint64_t)(offsetof(struct instance_globals_g,gmst_invent))},
{"width_instance_globals_g_gmst_invent",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gmst_invent))},
{"offset_instance_globals_g_gmst_ubak",(uint64_t)(offsetof(struct instance_globals_g,gmst_ubak))},
{"width_instance_globals_g_gmst_ubak",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gmst_ubak))},
{"offset_instance_globals_g_gmst_disco",(uint64_t)(offsetof(struct instance_globals_g,gmst_disco))},
{"width_instance_globals_g_gmst_disco",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gmst_disco))},
{"offset_instance_globals_g_gmst_mvitals",(uint64_t)(offsetof(struct instance_globals_g,gmst_mvitals))},
{"width_instance_globals_g_gmst_mvitals",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gmst_mvitals))},
{"offset_instance_globals_g_gmst_spl_book",(uint64_t)(offsetof(struct instance_globals_g,gmst_spl_book))},
{"width_instance_globals_g_gmst_spl_book",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gmst_spl_book))},
{"offset_instance_globals_g_gamelog",(uint64_t)(offsetof(struct instance_globals_g,gamelog))},
{"width_instance_globals_g_gamelog",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gamelog))},
{"offset_instance_globals_g_gas_cloud_diss_within",(uint64_t)(offsetof(struct instance_globals_g,gas_cloud_diss_within))},
{"width_instance_globals_g_gas_cloud_diss_within",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gas_cloud_diss_within))},
{"offset_instance_globals_g_gas_cloud_diss_seen",(uint64_t)(offsetof(struct instance_globals_g,gas_cloud_diss_seen))},
{"width_instance_globals_g_gas_cloud_diss_seen",(uint64_t)(sizeof(((struct instance_globals_g*)0)->gas_cloud_diss_seen))},
{"offset_instance_globals_g_glyphmap_perlevel_flags",(uint64_t)(offsetof(struct instance_globals_g,glyphmap_perlevel_flags))},
{"width_instance_globals_g_glyphmap_perlevel_flags",(uint64_t)(sizeof(((struct instance_globals_g*)0)->glyphmap_perlevel_flags))},
{"offset_instance_globals_g_havestate",(uint64_t)(offsetof(struct instance_globals_g,havestate))},
{"width_instance_globals_g_havestate",(uint64_t)(sizeof(((struct instance_globals_g*)0)->havestate))},
{"size_instance_globals_h",(uint64_t)(sizeof(struct instance_globals_h))},
{"align_instance_globals_h",(uint64_t)(__alignof__(struct instance_globals_h))},
{"offset_instance_globals_h_hname",(uint64_t)(offsetof(struct instance_globals_h,hname))},
{"width_instance_globals_h_hname",(uint64_t)(sizeof(((struct instance_globals_h*)0)->hname))},
{"offset_instance_globals_h_hero_seq",(uint64_t)(offsetof(struct instance_globals_h,hero_seq))},
{"width_instance_globals_h_hero_seq",(uint64_t)(sizeof(((struct instance_globals_h*)0)->hero_seq))},
{"offset_instance_globals_h_horsename",(uint64_t)(offsetof(struct instance_globals_h,horsename))},
{"width_instance_globals_h_horsename",(uint64_t)(sizeof(((struct instance_globals_h*)0)->horsename))},
{"offset_instance_globals_h_hitmsg_mid",(uint64_t)(offsetof(struct instance_globals_h,hitmsg_mid))},
{"width_instance_globals_h_hitmsg_mid",(uint64_t)(sizeof(((struct instance_globals_h*)0)->hitmsg_mid))},
{"offset_instance_globals_h_hitmsg_prev",(uint64_t)(offsetof(struct instance_globals_h,hitmsg_prev))},
{"width_instance_globals_h_hitmsg_prev",(uint64_t)(sizeof(((struct instance_globals_h*)0)->hitmsg_prev))},
{"offset_instance_globals_h_havestate",(uint64_t)(offsetof(struct instance_globals_h,havestate))},
{"width_instance_globals_h_havestate",(uint64_t)(sizeof(((struct instance_globals_h*)0)->havestate))},
{"size_instance_globals_i",(uint64_t)(sizeof(struct instance_globals_i))},
{"align_instance_globals_i",(uint64_t)(__alignof__(struct instance_globals_i))},
{"offset_instance_globals_i_in_doagain",(uint64_t)(offsetof(struct instance_globals_i,in_doagain))},
{"width_instance_globals_i_in_doagain",(uint64_t)(sizeof(((struct instance_globals_i*)0)->in_doagain))},
{"offset_instance_globals_i_in_mklev",(uint64_t)(offsetof(struct instance_globals_i,in_mklev))},
{"width_instance_globals_i_in_mklev",(uint64_t)(sizeof(((struct instance_globals_i*)0)->in_mklev))},
{"offset_instance_globals_i_in_steed_dismounting",(uint64_t)(offsetof(struct instance_globals_i,in_steed_dismounting))},
{"width_instance_globals_i_in_steed_dismounting",(uint64_t)(sizeof(((struct instance_globals_i*)0)->in_steed_dismounting))},
{"offset_instance_globals_i_invent",(uint64_t)(offsetof(struct instance_globals_i,invent))},
{"width_instance_globals_i_invent",(uint64_t)(sizeof(((struct instance_globals_i*)0)->invent))},
{"offset_instance_globals_i_initial_don",(uint64_t)(offsetof(struct instance_globals_i,initial_don))},
{"width_instance_globals_i_initial_don",(uint64_t)(sizeof(((struct instance_globals_i*)0)->initial_don))},
{"offset_instance_globals_i_invbuf",(uint64_t)(offsetof(struct instance_globals_i,invbuf))},
{"width_instance_globals_i_invbuf",(uint64_t)(sizeof(((struct instance_globals_i*)0)->invbuf))},
{"offset_instance_globals_i_invbufsiz",(uint64_t)(offsetof(struct instance_globals_i,invbufsiz))},
{"width_instance_globals_i_invbufsiz",(uint64_t)(sizeof(((struct instance_globals_i*)0)->invbufsiz))},
{"offset_instance_globals_i_item_action_in_progress",(uint64_t)(offsetof(struct instance_globals_i,item_action_in_progress))},
{"width_instance_globals_i_item_action_in_progress",(uint64_t)(sizeof(((struct instance_globals_i*)0)->item_action_in_progress))},
{"offset_instance_globals_i_in_sync_perminvent",(uint64_t)(offsetof(struct instance_globals_i,in_sync_perminvent))},
{"width_instance_globals_i_in_sync_perminvent",(uint64_t)(sizeof(((struct instance_globals_i*)0)->in_sync_perminvent))},
{"offset_instance_globals_i_itermonarr",(uint64_t)(offsetof(struct instance_globals_i,itermonarr))},
{"width_instance_globals_i_itermonarr",(uint64_t)(sizeof(((struct instance_globals_i*)0)->itermonarr))},
{"offset_instance_globals_i_id_map",(uint64_t)(offsetof(struct instance_globals_i,id_map))},
{"width_instance_globals_i_id_map",(uint64_t)(sizeof(((struct instance_globals_i*)0)->id_map))},
{"offset_instance_globals_i_in_mk_themerooms",(uint64_t)(offsetof(struct instance_globals_i,in_mk_themerooms))},
{"width_instance_globals_i_in_mk_themerooms",(uint64_t)(sizeof(((struct instance_globals_i*)0)->in_mk_themerooms))},
{"offset_instance_globals_i_havestate",(uint64_t)(offsetof(struct instance_globals_i,havestate))},
{"width_instance_globals_i_havestate",(uint64_t)(sizeof(((struct instance_globals_i*)0)->havestate))},
{"size_instance_globals_j",(uint64_t)(sizeof(struct instance_globals_j))},
{"align_instance_globals_j",(uint64_t)(__alignof__(struct instance_globals_j))},
{"offset_instance_globals_j_jumping_is_magic",(uint64_t)(offsetof(struct instance_globals_j,jumping_is_magic))},
{"width_instance_globals_j_jumping_is_magic",(uint64_t)(sizeof(((struct instance_globals_j*)0)->jumping_is_magic))},
{"offset_instance_globals_j_havestate",(uint64_t)(offsetof(struct instance_globals_j,havestate))},
{"width_instance_globals_j_havestate",(uint64_t)(sizeof(((struct instance_globals_j*)0)->havestate))},
{"size_instance_globals_k",(uint64_t)(sizeof(struct instance_globals_k))},
{"align_instance_globals_k",(uint64_t)(__alignof__(struct instance_globals_k))},
{"offset_instance_globals_k_kickedloc",(uint64_t)(offsetof(struct instance_globals_k,kickedloc))},
{"width_instance_globals_k_kickedloc",(uint64_t)(sizeof(((struct instance_globals_k*)0)->kickedloc))},
{"offset_instance_globals_k_kickedobj",(uint64_t)(offsetof(struct instance_globals_k,kickedobj))},
{"width_instance_globals_k_kickedobj",(uint64_t)(sizeof(((struct instance_globals_k*)0)->kickedobj))},
{"offset_instance_globals_k_known",(uint64_t)(offsetof(struct instance_globals_k,known))},
{"width_instance_globals_k_known",(uint64_t)(sizeof(((struct instance_globals_k*)0)->known))},
{"offset_instance_globals_k_havestate",(uint64_t)(offsetof(struct instance_globals_k,havestate))},
{"width_instance_globals_k_havestate",(uint64_t)(sizeof(((struct instance_globals_k*)0)->havestate))},
{"size_instance_globals_l",(uint64_t)(sizeof(struct instance_globals_l))},
{"align_instance_globals_l",(uint64_t)(__alignof__(struct instance_globals_l))},
{"offset_instance_globals_l_last_command_count",(uint64_t)(offsetof(struct instance_globals_l,last_command_count))},
{"width_instance_globals_l_last_command_count",(uint64_t)(sizeof(((struct instance_globals_l*)0)->last_command_count))},
{"offset_instance_globals_l_locknum",(uint64_t)(offsetof(struct instance_globals_l,locknum))},
{"width_instance_globals_l_locknum",(uint64_t)(sizeof(((struct instance_globals_l*)0)->locknum))},
{"offset_instance_globals_l_lockptr",(uint64_t)(offsetof(struct instance_globals_l,lockptr))},
{"width_instance_globals_l_lockptr",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lockptr))},
{"offset_instance_globals_l_lock",(uint64_t)(offsetof(struct instance_globals_l,lock))},
{"width_instance_globals_l_lock",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lock))},
{"offset_instance_globals_l_lastinvnr",(uint64_t)(offsetof(struct instance_globals_l,lastinvnr))},
{"width_instance_globals_l_lastinvnr",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lastinvnr))},
{"offset_instance_globals_l_light_base",(uint64_t)(offsetof(struct instance_globals_l,light_base))},
{"width_instance_globals_l_light_base",(uint64_t)(sizeof(((struct instance_globals_l*)0)->light_base))},
{"offset_instance_globals_l_luathemes",(uint64_t)(offsetof(struct instance_globals_l,luathemes))},
{"width_instance_globals_l_luathemes",(uint64_t)(sizeof(((struct instance_globals_l*)0)->luathemes))},
{"offset_instance_globals_l_last_hider",(uint64_t)(offsetof(struct instance_globals_l,last_hider))},
{"width_instance_globals_l_last_hider",(uint64_t)(sizeof(((struct instance_globals_l*)0)->last_hider))},
{"offset_instance_globals_l_luacore",(uint64_t)(offsetof(struct instance_globals_l,luacore))},
{"width_instance_globals_l_luacore",(uint64_t)(sizeof(((struct instance_globals_l*)0)->luacore))},
{"offset_instance_globals_l_lua_warnbuf",(uint64_t)(offsetof(struct instance_globals_l,lua_warnbuf))},
{"width_instance_globals_l_lua_warnbuf",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lua_warnbuf))},
{"offset_instance_globals_l_loglua",(uint64_t)(offsetof(struct instance_globals_l,loglua))},
{"width_instance_globals_l_loglua",(uint64_t)(sizeof(((struct instance_globals_l*)0)->loglua))},
{"offset_instance_globals_l_lua_sid",(uint64_t)(offsetof(struct instance_globals_l,lua_sid))},
{"width_instance_globals_l_lua_sid",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lua_sid))},
{"offset_instance_globals_l_loot_reset_justpicked",(uint64_t)(offsetof(struct instance_globals_l,loot_reset_justpicked))},
{"width_instance_globals_l_loot_reset_justpicked",(uint64_t)(sizeof(((struct instance_globals_l*)0)->loot_reset_justpicked))},
{"offset_instance_globals_l_looseball",(uint64_t)(offsetof(struct instance_globals_l,looseball))},
{"width_instance_globals_l_looseball",(uint64_t)(sizeof(((struct instance_globals_l*)0)->looseball))},
{"offset_instance_globals_l_loosechain",(uint64_t)(offsetof(struct instance_globals_l,loosechain))},
{"width_instance_globals_l_loosechain",(uint64_t)(sizeof(((struct instance_globals_l*)0)->loosechain))},
{"offset_instance_globals_l_lev_message",(uint64_t)(offsetof(struct instance_globals_l,lev_message))},
{"width_instance_globals_l_lev_message",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lev_message))},
{"offset_instance_globals_l_lregions",(uint64_t)(offsetof(struct instance_globals_l,lregions))},
{"width_instance_globals_l_lregions",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lregions))},
{"offset_instance_globals_l_launchplace",(uint64_t)(offsetof(struct instance_globals_l,launchplace))},
{"width_instance_globals_l_launchplace",(uint64_t)(sizeof(((struct instance_globals_l*)0)->launchplace))},
{"offset_instance_globals_l_last_winchoice",(uint64_t)(offsetof(struct instance_globals_l,last_winchoice))},
{"width_instance_globals_l_last_winchoice",(uint64_t)(sizeof(((struct instance_globals_l*)0)->last_winchoice))},
{"offset_instance_globals_l_lua_ver",(uint64_t)(offsetof(struct instance_globals_l,lua_ver))},
{"width_instance_globals_l_lua_ver",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lua_ver))},
{"offset_instance_globals_l_lua_copyright",(uint64_t)(offsetof(struct instance_globals_l,lua_copyright))},
{"width_instance_globals_l_lua_copyright",(uint64_t)(sizeof(((struct instance_globals_l*)0)->lua_copyright))},
{"offset_instance_globals_l_havestate",(uint64_t)(offsetof(struct instance_globals_l,havestate))},
{"width_instance_globals_l_havestate",(uint64_t)(sizeof(((struct instance_globals_l*)0)->havestate))},
{"size_instance_globals_m",(uint64_t)(sizeof(struct instance_globals_m))},
{"align_instance_globals_m",(uint64_t)(__alignof__(struct instance_globals_m))},
{"offset_instance_globals_m_mkot_trap_warn_count",(uint64_t)(offsetof(struct instance_globals_m,mkot_trap_warn_count))},
{"width_instance_globals_m_mkot_trap_warn_count",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mkot_trap_warn_count))},
{"offset_instance_globals_m_mrank_sz",(uint64_t)(offsetof(struct instance_globals_m,mrank_sz))},
{"width_instance_globals_m_mrank_sz",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mrank_sz))},
{"offset_instance_globals_m_multi",(uint64_t)(offsetof(struct instance_globals_m,multi))},
{"width_instance_globals_m_multi",(uint64_t)(sizeof(((struct instance_globals_m*)0)->multi))},
{"offset_instance_globals_m_multi_reason",(uint64_t)(offsetof(struct instance_globals_m,multi_reason))},
{"width_instance_globals_m_multi_reason",(uint64_t)(sizeof(((struct instance_globals_m*)0)->multi_reason))},
{"offset_instance_globals_m_multireasonbuf",(uint64_t)(offsetof(struct instance_globals_m,multireasonbuf))},
{"width_instance_globals_m_multireasonbuf",(uint64_t)(sizeof(((struct instance_globals_m*)0)->multireasonbuf))},
{"offset_instance_globals_m_m_shot",(uint64_t)(offsetof(struct instance_globals_m,m_shot))},
{"width_instance_globals_m_m_shot",(uint64_t)(sizeof(((struct instance_globals_m*)0)->m_shot))},
{"offset_instance_globals_m_mrg_to_wielded",(uint64_t)(offsetof(struct instance_globals_m,mrg_to_wielded))},
{"width_instance_globals_m_mrg_to_wielded",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mrg_to_wielded))},
{"offset_instance_globals_m_menu_colorings",(uint64_t)(offsetof(struct instance_globals_m,menu_colorings))},
{"width_instance_globals_m_menu_colorings",(uint64_t)(sizeof(((struct instance_globals_m*)0)->menu_colorings))},
{"offset_instance_globals_m_migrating_objs",(uint64_t)(offsetof(struct instance_globals_m,migrating_objs))},
{"width_instance_globals_m_migrating_objs",(uint64_t)(sizeof(((struct instance_globals_m*)0)->migrating_objs))},
{"offset_instance_globals_m_mydogs",(uint64_t)(offsetof(struct instance_globals_m,mydogs))},
{"width_instance_globals_m_mydogs",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mydogs))},
{"offset_instance_globals_m_migrating_mons",(uint64_t)(offsetof(struct instance_globals_m,migrating_mons))},
{"width_instance_globals_m_migrating_mons",(uint64_t)(sizeof(((struct instance_globals_m*)0)->migrating_mons))},
{"offset_instance_globals_m_maploc",(uint64_t)(offsetof(struct instance_globals_m,maploc))},
{"width_instance_globals_m_maploc",(uint64_t)(sizeof(((struct instance_globals_m*)0)->maploc))},
{"offset_instance_globals_m_mswallower",(uint64_t)(offsetof(struct instance_globals_m,mswallower))},
{"width_instance_globals_m_mswallower",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mswallower))},
{"offset_instance_globals_m_mhitu_dieroll",(uint64_t)(offsetof(struct instance_globals_m,mhitu_dieroll))},
{"width_instance_globals_m_mhitu_dieroll",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mhitu_dieroll))},
{"offset_instance_globals_m_made_branch",(uint64_t)(offsetof(struct instance_globals_m,made_branch))},
{"width_instance_globals_m_made_branch",(uint64_t)(sizeof(((struct instance_globals_m*)0)->made_branch))},
{"offset_instance_globals_m_min_rx",(uint64_t)(offsetof(struct instance_globals_m,min_rx))},
{"width_instance_globals_m_min_rx",(uint64_t)(sizeof(((struct instance_globals_m*)0)->min_rx))},
{"offset_instance_globals_m_max_rx",(uint64_t)(offsetof(struct instance_globals_m,max_rx))},
{"width_instance_globals_m_max_rx",(uint64_t)(sizeof(((struct instance_globals_m*)0)->max_rx))},
{"offset_instance_globals_m_min_ry",(uint64_t)(offsetof(struct instance_globals_m,min_ry))},
{"width_instance_globals_m_min_ry",(uint64_t)(sizeof(((struct instance_globals_m*)0)->min_ry))},
{"offset_instance_globals_m_max_ry",(uint64_t)(offsetof(struct instance_globals_m,max_ry))},
{"width_instance_globals_m_max_ry",(uint64_t)(sizeof(((struct instance_globals_m*)0)->max_ry))},
{"offset_instance_globals_m_mkcorpstat_norevive",(uint64_t)(offsetof(struct instance_globals_m,mkcorpstat_norevive))},
{"width_instance_globals_m_mkcorpstat_norevive",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mkcorpstat_norevive))},
{"offset_instance_globals_m_mesg_given",(uint64_t)(offsetof(struct instance_globals_m,mesg_given))},
{"width_instance_globals_m_mesg_given",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mesg_given))},
{"offset_instance_globals_m_mtarget",(uint64_t)(offsetof(struct instance_globals_m,mtarget))},
{"width_instance_globals_m_mtarget",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mtarget))},
{"offset_instance_globals_m_marcher",(uint64_t)(offsetof(struct instance_globals_m,marcher))},
{"width_instance_globals_m_marcher",(uint64_t)(sizeof(((struct instance_globals_m*)0)->marcher))},
{"offset_instance_globals_m_m_using",(uint64_t)(offsetof(struct instance_globals_m,m_using))},
{"width_instance_globals_m_m_using",(uint64_t)(sizeof(((struct instance_globals_m*)0)->m_using))},
{"offset_instance_globals_m_m",(uint64_t)(offsetof(struct instance_globals_m,m))},
{"width_instance_globals_m_m",(uint64_t)(sizeof(((struct instance_globals_m*)0)->m))},
{"offset_instance_globals_m_mapped_menu_cmds",(uint64_t)(offsetof(struct instance_globals_m,mapped_menu_cmds))},
{"width_instance_globals_m_mapped_menu_cmds",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mapped_menu_cmds))},
{"offset_instance_globals_m_mapped_menu_op",(uint64_t)(offsetof(struct instance_globals_m,mapped_menu_op))},
{"width_instance_globals_m_mapped_menu_op",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mapped_menu_op))},
{"offset_instance_globals_m_max_regions",(uint64_t)(offsetof(struct instance_globals_m,max_regions))},
{"width_instance_globals_m_max_regions",(uint64_t)(sizeof(((struct instance_globals_m*)0)->max_regions))},
{"offset_instance_globals_m_mentioned_water",(uint64_t)(offsetof(struct instance_globals_m,mentioned_water))},
{"width_instance_globals_m_mentioned_water",(uint64_t)(sizeof(((struct instance_globals_m*)0)->mentioned_water))},
{"offset_instance_globals_m_havestate",(uint64_t)(offsetof(struct instance_globals_m,havestate))},
{"width_instance_globals_m_havestate",(uint64_t)(sizeof(((struct instance_globals_m*)0)->havestate))},
{"size_instance_globals_n",(uint64_t)(sizeof(struct instance_globals_n))},
{"align_instance_globals_n",(uint64_t)(__alignof__(struct instance_globals_n))},
{"offset_instance_globals_n_now_or_before_idx",(uint64_t)(offsetof(struct instance_globals_n,now_or_before_idx))},
{"width_instance_globals_n_now_or_before_idx",(uint64_t)(sizeof(((struct instance_globals_n*)0)->now_or_before_idx))},
{"offset_instance_globals_n_nomovemsg",(uint64_t)(offsetof(struct instance_globals_n,nomovemsg))},
{"width_instance_globals_n_nomovemsg",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nomovemsg))},
{"offset_instance_globals_n_nsubroom",(uint64_t)(offsetof(struct instance_globals_n,nsubroom))},
{"width_instance_globals_n_nsubroom",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nsubroom))},
{"offset_instance_globals_n_nowhere",(uint64_t)(offsetof(struct instance_globals_n,nowhere))},
{"width_instance_globals_n_nowhere",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nowhere))},
{"offset_instance_globals_n_nesting",(uint64_t)(offsetof(struct instance_globals_n,nesting))},
{"width_instance_globals_n_nesting",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nesting))},
{"offset_instance_globals_n_no_sound_notified",(uint64_t)(offsetof(struct instance_globals_n,no_sound_notified))},
{"width_instance_globals_n_no_sound_notified",(uint64_t)(sizeof(((struct instance_globals_n*)0)->no_sound_notified))},
{"offset_instance_globals_n_noisetime",(uint64_t)(offsetof(struct instance_globals_n,noisetime))},
{"width_instance_globals_n_noisetime",(uint64_t)(sizeof(((struct instance_globals_n*)0)->noisetime))},
{"offset_instance_globals_n_new_locations",(uint64_t)(offsetof(struct instance_globals_n,new_locations))},
{"width_instance_globals_n_new_locations",(uint64_t)(sizeof(((struct instance_globals_n*)0)->new_locations))},
{"offset_instance_globals_n_n_loc_filled",(uint64_t)(offsetof(struct instance_globals_n,n_loc_filled))},
{"width_instance_globals_n_n_loc_filled",(uint64_t)(sizeof(((struct instance_globals_n*)0)->n_loc_filled))},
{"offset_instance_globals_n_n_menu_mapped",(uint64_t)(offsetof(struct instance_globals_n,n_menu_mapped))},
{"width_instance_globals_n_n_menu_mapped",(uint64_t)(sizeof(((struct instance_globals_n*)0)->n_menu_mapped))},
{"offset_instance_globals_n_notonhead",(uint64_t)(offsetof(struct instance_globals_n,notonhead))},
{"width_instance_globals_n_notonhead",(uint64_t)(sizeof(((struct instance_globals_n*)0)->notonhead))},
{"offset_instance_globals_n_nambuf",(uint64_t)(offsetof(struct instance_globals_n,nambuf))},
{"width_instance_globals_n_nambuf",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nambuf))},
{"offset_instance_globals_n_n_ids_mapped",(uint64_t)(offsetof(struct instance_globals_n,n_ids_mapped))},
{"width_instance_globals_n_n_ids_mapped",(uint64_t)(sizeof(((struct instance_globals_n*)0)->n_ids_mapped))},
{"offset_instance_globals_n_num_lregions",(uint64_t)(offsetof(struct instance_globals_n,num_lregions))},
{"width_instance_globals_n_num_lregions",(uint64_t)(sizeof(((struct instance_globals_n*)0)->num_lregions))},
{"offset_instance_globals_n_nocreate",(uint64_t)(offsetof(struct instance_globals_n,nocreate))},
{"width_instance_globals_n_nocreate",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nocreate))},
{"offset_instance_globals_n_nocreate2",(uint64_t)(offsetof(struct instance_globals_n,nocreate2))},
{"width_instance_globals_n_nocreate2",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nocreate2))},
{"offset_instance_globals_n_nocreate3",(uint64_t)(offsetof(struct instance_globals_n,nocreate3))},
{"width_instance_globals_n_nocreate3",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nocreate3))},
{"offset_instance_globals_n_nocreate4",(uint64_t)(offsetof(struct instance_globals_n,nocreate4))},
{"width_instance_globals_n_nocreate4",(uint64_t)(sizeof(((struct instance_globals_n*)0)->nocreate4))},
{"offset_instance_globals_n_havestate",(uint64_t)(offsetof(struct instance_globals_n,havestate))},
{"width_instance_globals_n_havestate",(uint64_t)(sizeof(((struct instance_globals_n*)0)->havestate))},
{"size_instance_globals_o",(uint64_t)(sizeof(struct instance_globals_o))},
{"align_instance_globals_o",(uint64_t)(__alignof__(struct instance_globals_o))},
{"offset_instance_globals_o_objs_deleted",(uint64_t)(offsetof(struct instance_globals_o,objs_deleted))},
{"width_instance_globals_o_objs_deleted",(uint64_t)(sizeof(((struct instance_globals_o*)0)->objs_deleted))},
{"offset_instance_globals_o_occupants",(uint64_t)(offsetof(struct instance_globals_o,occupants))},
{"width_instance_globals_o_occupants",(uint64_t)(sizeof(((struct instance_globals_o*)0)->occupants))},
{"offset_instance_globals_o_occupation",(uint64_t)(offsetof(struct instance_globals_o,occupation))},
{"width_instance_globals_o_occupation",(uint64_t)(sizeof(((struct instance_globals_o*)0)->occupation))},
{"offset_instance_globals_o_occtime",(uint64_t)(offsetof(struct instance_globals_o,occtime))},
{"width_instance_globals_o_occtime",(uint64_t)(sizeof(((struct instance_globals_o*)0)->occtime))},
{"offset_instance_globals_o_otg_temp",(uint64_t)(offsetof(struct instance_globals_o,otg_temp))},
{"width_instance_globals_o_otg_temp",(uint64_t)(sizeof(((struct instance_globals_o*)0)->otg_temp))},
{"offset_instance_globals_o_otg_otmp",(uint64_t)(offsetof(struct instance_globals_o,otg_otmp))},
{"width_instance_globals_o_otg_otmp",(uint64_t)(sizeof(((struct instance_globals_o*)0)->otg_otmp))},
{"offset_instance_globals_o_occtxt",(uint64_t)(offsetof(struct instance_globals_o,occtxt))},
{"width_instance_globals_o_occtxt",(uint64_t)(sizeof(((struct instance_globals_o*)0)->occtxt))},
{"offset_instance_globals_o_ov_primary_syms",(uint64_t)(offsetof(struct instance_globals_o,ov_primary_syms))},
{"width_instance_globals_o_ov_primary_syms",(uint64_t)(sizeof(((struct instance_globals_o*)0)->ov_primary_syms))},
{"offset_instance_globals_o_ov_rogue_syms",(uint64_t)(offsetof(struct instance_globals_o,ov_rogue_syms))},
{"width_instance_globals_o_ov_rogue_syms",(uint64_t)(sizeof(((struct instance_globals_o*)0)->ov_rogue_syms))},
{"offset_instance_globals_o_only",(uint64_t)(offsetof(struct instance_globals_o,only))},
{"width_instance_globals_o_only",(uint64_t)(sizeof(((struct instance_globals_o*)0)->only))},
{"offset_instance_globals_o_oclass_prob_totals",(uint64_t)(offsetof(struct instance_globals_o,oclass_prob_totals))},
{"width_instance_globals_o_oclass_prob_totals",(uint64_t)(sizeof(((struct instance_globals_o*)0)->oclass_prob_totals))},
{"offset_instance_globals_o_opt_phase",(uint64_t)(offsetof(struct instance_globals_o,opt_phase))},
{"width_instance_globals_o_opt_phase",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_phase))},
{"offset_instance_globals_o_opt_initial",(uint64_t)(offsetof(struct instance_globals_o,opt_initial))},
{"width_instance_globals_o_opt_initial",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_initial))},
{"offset_instance_globals_o_opt_from_file",(uint64_t)(offsetof(struct instance_globals_o,opt_from_file))},
{"width_instance_globals_o_opt_from_file",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_from_file))},
{"offset_instance_globals_o_opt_need_redraw",(uint64_t)(offsetof(struct instance_globals_o,opt_need_redraw))},
{"width_instance_globals_o_opt_need_redraw",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_need_redraw))},
{"offset_instance_globals_o_opt_need_glyph_reset",(uint64_t)(offsetof(struct instance_globals_o,opt_need_glyph_reset))},
{"width_instance_globals_o_opt_need_glyph_reset",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_need_glyph_reset))},
{"offset_instance_globals_o_opt_need_promptstyle",(uint64_t)(offsetof(struct instance_globals_o,opt_need_promptstyle))},
{"width_instance_globals_o_opt_need_promptstyle",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_need_promptstyle))},
{"offset_instance_globals_o_opt_reset_customcolors",(uint64_t)(offsetof(struct instance_globals_o,opt_reset_customcolors))},
{"width_instance_globals_o_opt_reset_customcolors",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_reset_customcolors))},
{"offset_instance_globals_o_opt_reset_customsymbols",(uint64_t)(offsetof(struct instance_globals_o,opt_reset_customsymbols))},
{"width_instance_globals_o_opt_reset_customsymbols",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_reset_customsymbols))},
{"offset_instance_globals_o_opt_update_basic_palette",(uint64_t)(offsetof(struct instance_globals_o,opt_update_basic_palette))},
{"width_instance_globals_o_opt_update_basic_palette",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_update_basic_palette))},
{"offset_instance_globals_o_opt_symset_changed",(uint64_t)(offsetof(struct instance_globals_o,opt_symset_changed))},
{"width_instance_globals_o_opt_symset_changed",(uint64_t)(sizeof(((struct instance_globals_o*)0)->opt_symset_changed))},
{"offset_instance_globals_o_oldcap",(uint64_t)(offsetof(struct instance_globals_o,oldcap))},
{"width_instance_globals_o_oldcap",(uint64_t)(sizeof(((struct instance_globals_o*)0)->oldcap))},
{"offset_instance_globals_o_oldfruit",(uint64_t)(offsetof(struct instance_globals_o,oldfruit))},
{"width_instance_globals_o_oldfruit",(uint64_t)(sizeof(((struct instance_globals_o*)0)->oldfruit))},
{"offset_instance_globals_o_oracle_flg",(uint64_t)(offsetof(struct instance_globals_o,oracle_flg))},
{"width_instance_globals_o_oracle_flg",(uint64_t)(sizeof(((struct instance_globals_o*)0)->oracle_flg))},
{"offset_instance_globals_o_override_confirmation",(uint64_t)(offsetof(struct instance_globals_o,override_confirmation))},
{"width_instance_globals_o_override_confirmation",(uint64_t)(sizeof(((struct instance_globals_o*)0)->override_confirmation))},
{"offset_instance_globals_o_obj_zapped",(uint64_t)(offsetof(struct instance_globals_o,obj_zapped))},
{"width_instance_globals_o_obj_zapped",(uint64_t)(sizeof(((struct instance_globals_o*)0)->obj_zapped))},
{"offset_instance_globals_o_havestate",(uint64_t)(offsetof(struct instance_globals_o,havestate))},
{"width_instance_globals_o_havestate",(uint64_t)(sizeof(((struct instance_globals_o*)0)->havestate))},
{"size_instance_globals_p",(uint64_t)(sizeof(struct instance_globals_p))},
{"align_instance_globals_p",(uint64_t)(__alignof__(struct instance_globals_p))},
{"offset_instance_globals_p_polearm_range_min",(uint64_t)(offsetof(struct instance_globals_p,polearm_range_min))},
{"width_instance_globals_p_polearm_range_min",(uint64_t)(sizeof(((struct instance_globals_p*)0)->polearm_range_min))},
{"offset_instance_globals_p_polearm_range_max",(uint64_t)(offsetof(struct instance_globals_p,polearm_range_max))},
{"width_instance_globals_p_polearm_range_max",(uint64_t)(sizeof(((struct instance_globals_p*)0)->polearm_range_max))},
{"offset_instance_globals_p_plnamelen",(uint64_t)(offsetof(struct instance_globals_p,plnamelen))},
{"width_instance_globals_p_plnamelen",(uint64_t)(sizeof(((struct instance_globals_p*)0)->plnamelen))},
{"offset_instance_globals_p_pl_race",(uint64_t)(offsetof(struct instance_globals_p,pl_race))},
{"width_instance_globals_p_pl_race",(uint64_t)(sizeof(((struct instance_globals_p*)0)->pl_race))},
{"offset_instance_globals_p_plinemsg_types",(uint64_t)(offsetof(struct instance_globals_p,plinemsg_types))},
{"width_instance_globals_p_plinemsg_types",(uint64_t)(sizeof(((struct instance_globals_p*)0)->plinemsg_types))},
{"offset_instance_globals_p_petname_used",(uint64_t)(offsetof(struct instance_globals_p,petname_used))},
{"width_instance_globals_p_petname_used",(uint64_t)(sizeof(((struct instance_globals_p*)0)->petname_used))},
{"offset_instance_globals_p_preferred_pet",(uint64_t)(offsetof(struct instance_globals_p,preferred_pet))},
{"width_instance_globals_p_preferred_pet",(uint64_t)(sizeof(((struct instance_globals_p*)0)->preferred_pet))},
{"offset_instance_globals_p_primary_syms",(uint64_t)(offsetof(struct instance_globals_p,primary_syms))},
{"width_instance_globals_p_primary_syms",(uint64_t)(sizeof(((struct instance_globals_p*)0)->primary_syms))},
{"offset_instance_globals_p_perm_invent_toggling_direction",(uint64_t)(offsetof(struct instance_globals_p,perm_invent_toggling_direction))},
{"width_instance_globals_p_perm_invent_toggling_direction",(uint64_t)(sizeof(((struct instance_globals_p*)0)->perm_invent_toggling_direction))},
{"offset_instance_globals_p_picked_filter",(uint64_t)(offsetof(struct instance_globals_p,picked_filter))},
{"width_instance_globals_p_picked_filter",(uint64_t)(sizeof(((struct instance_globals_p*)0)->picked_filter))},
{"offset_instance_globals_p_pickup_encumbrance",(uint64_t)(offsetof(struct instance_globals_p,pickup_encumbrance))},
{"width_instance_globals_p_pickup_encumbrance",(uint64_t)(sizeof(((struct instance_globals_p*)0)->pickup_encumbrance))},
{"offset_instance_globals_p_pline_flags",(uint64_t)(offsetof(struct instance_globals_p,pline_flags))},
{"width_instance_globals_p_pline_flags",(uint64_t)(sizeof(((struct instance_globals_p*)0)->pline_flags))},
{"offset_instance_globals_p_prevmsg",(uint64_t)(offsetof(struct instance_globals_p,prevmsg))},
{"width_instance_globals_p_prevmsg",(uint64_t)(sizeof(((struct instance_globals_p*)0)->prevmsg))},
{"offset_instance_globals_p_potion_nothing",(uint64_t)(offsetof(struct instance_globals_p,potion_nothing))},
{"width_instance_globals_p_potion_nothing",(uint64_t)(sizeof(((struct instance_globals_p*)0)->potion_nothing))},
{"offset_instance_globals_p_potion_unkn",(uint64_t)(offsetof(struct instance_globals_p,potion_unkn))},
{"width_instance_globals_p_potion_unkn",(uint64_t)(sizeof(((struct instance_globals_p*)0)->potion_unkn))},
{"offset_instance_globals_p_p_aligntyp",(uint64_t)(offsetof(struct instance_globals_p,p_aligntyp))},
{"width_instance_globals_p_p_aligntyp",(uint64_t)(sizeof(((struct instance_globals_p*)0)->p_aligntyp))},
{"offset_instance_globals_p_p_trouble",(uint64_t)(offsetof(struct instance_globals_p,p_trouble))},
{"width_instance_globals_p_p_trouble",(uint64_t)(sizeof(((struct instance_globals_p*)0)->p_trouble))},
{"offset_instance_globals_p_p_type",(uint64_t)(offsetof(struct instance_globals_p,p_type))},
{"width_instance_globals_p_p_type",(uint64_t)(sizeof(((struct instance_globals_p*)0)->p_type))},
{"offset_instance_globals_p_propellor",(uint64_t)(offsetof(struct instance_globals_p,propellor))},
{"width_instance_globals_p_propellor",(uint64_t)(sizeof(((struct instance_globals_p*)0)->propellor))},
{"offset_instance_globals_p_poly_zapped",(uint64_t)(offsetof(struct instance_globals_p,poly_zapped))},
{"width_instance_globals_p_poly_zapped",(uint64_t)(sizeof(((struct instance_globals_p*)0)->poly_zapped))},
{"offset_instance_globals_p_havestate",(uint64_t)(offsetof(struct instance_globals_p,havestate))},
{"width_instance_globals_p_havestate",(uint64_t)(sizeof(((struct instance_globals_p*)0)->havestate))},
{"size_instance_globals_q",(uint64_t)(sizeof(struct instance_globals_q))},
{"align_instance_globals_q",(uint64_t)(__alignof__(struct instance_globals_q))},
{"offset_instance_globals_q_havestate",(uint64_t)(offsetof(struct instance_globals_q,havestate))},
{"width_instance_globals_q_havestate",(uint64_t)(sizeof(((struct instance_globals_q*)0)->havestate))},
{"size_instance_globals_r",(uint64_t)(sizeof(struct instance_globals_r))},
{"align_instance_globals_r",(uint64_t)(__alignof__(struct instance_globals_r))},
{"offset_instance_globals_r_rogue_syms",(uint64_t)(offsetof(struct instance_globals_r,rogue_syms))},
{"width_instance_globals_r_rogue_syms",(uint64_t)(sizeof(((struct instance_globals_r*)0)->rogue_syms))},
{"offset_instance_globals_r_r",(uint64_t)(offsetof(struct instance_globals_r,r))},
{"width_instance_globals_r_r",(uint64_t)(sizeof(((struct instance_globals_r*)0)->r))},
{"offset_instance_globals_r_ransacked",(uint64_t)(offsetof(struct instance_globals_r,ransacked))},
{"width_instance_globals_r_ransacked",(uint64_t)(sizeof(((struct instance_globals_r*)0)->ransacked))},
{"offset_instance_globals_r_regions",(uint64_t)(offsetof(struct instance_globals_r,regions))},
{"width_instance_globals_r_regions",(uint64_t)(sizeof(((struct instance_globals_r*)0)->regions))},
{"offset_instance_globals_r_rip",(uint64_t)(offsetof(struct instance_globals_r,rip))},
{"width_instance_globals_r_rip",(uint64_t)(sizeof(((struct instance_globals_r*)0)->rip))},
{"offset_instance_globals_r_role_pa",(uint64_t)(offsetof(struct instance_globals_r,role_pa))},
{"width_instance_globals_r_role_pa",(uint64_t)(sizeof(((struct instance_globals_r*)0)->role_pa))},
{"offset_instance_globals_r_role_post_attribs",(uint64_t)(offsetof(struct instance_globals_r,role_post_attribs))},
{"width_instance_globals_r_role_post_attribs",(uint64_t)(sizeof(((struct instance_globals_r*)0)->role_post_attribs))},
{"offset_instance_globals_r_rfilter",(uint64_t)(offsetof(struct instance_globals_r,rfilter))},
{"width_instance_globals_r_rfilter",(uint64_t)(sizeof(((struct instance_globals_r*)0)->rfilter))},
{"offset_instance_globals_r_repo",(uint64_t)(offsetof(struct instance_globals_r,repo))},
{"width_instance_globals_r_repo",(uint64_t)(sizeof(((struct instance_globals_r*)0)->repo))},
{"offset_instance_globals_r_havestate",(uint64_t)(offsetof(struct instance_globals_r,havestate))},
{"width_instance_globals_r_havestate",(uint64_t)(sizeof(((struct instance_globals_r*)0)->havestate))},
{"size_instance_globals_s",(uint64_t)(sizeof(struct instance_globals_s))},
{"align_instance_globals_s",(uint64_t)(__alignof__(struct instance_globals_s))},
{"offset_instance_globals_s_spec_dbon_applies",(uint64_t)(offsetof(struct instance_globals_s,spec_dbon_applies))},
{"width_instance_globals_s_spec_dbon_applies",(uint64_t)(sizeof(((struct instance_globals_s*)0)->spec_dbon_applies))},
{"offset_instance_globals_s_stairs",(uint64_t)(offsetof(struct instance_globals_s,stairs))},
{"width_instance_globals_s_stairs",(uint64_t)(sizeof(((struct instance_globals_s*)0)->stairs))},
{"offset_instance_globals_s_smeq",(uint64_t)(offsetof(struct instance_globals_s,smeq))},
{"width_instance_globals_s_smeq",(uint64_t)(sizeof(((struct instance_globals_s*)0)->smeq))},
{"offset_instance_globals_s_stoned",(uint64_t)(offsetof(struct instance_globals_s,stoned))},
{"width_instance_globals_s_stoned",(uint64_t)(sizeof(((struct instance_globals_s*)0)->stoned))},
{"offset_instance_globals_s_subrooms",(uint64_t)(offsetof(struct instance_globals_s,subrooms))},
{"width_instance_globals_s_subrooms",(uint64_t)(sizeof(((struct instance_globals_s*)0)->subrooms))},
{"offset_instance_globals_s_save_dlevel",(uint64_t)(offsetof(struct instance_globals_s,save_dlevel))},
{"width_instance_globals_s_save_dlevel",(uint64_t)(sizeof(((struct instance_globals_s*)0)->save_dlevel))},
{"offset_instance_globals_s_symset",(uint64_t)(offsetof(struct instance_globals_s,symset))},
{"width_instance_globals_s_symset",(uint64_t)(sizeof(((struct instance_globals_s*)0)->symset))},
{"offset_instance_globals_s_sym_customizations",(uint64_t)(offsetof(struct instance_globals_s,sym_customizations))},
{"width_instance_globals_s_sym_customizations",(uint64_t)(sizeof(((struct instance_globals_s*)0)->sym_customizations))},
{"offset_instance_globals_s_showsyms",(uint64_t)(offsetof(struct instance_globals_s,showsyms))},
{"width_instance_globals_s_showsyms",(uint64_t)(sizeof(((struct instance_globals_s*)0)->showsyms))},
{"offset_instance_globals_s_symset_count",(uint64_t)(offsetof(struct instance_globals_s,symset_count))},
{"width_instance_globals_s_symset_count",(uint64_t)(sizeof(((struct instance_globals_s*)0)->symset_count))},
{"offset_instance_globals_s_symset_which_set",(uint64_t)(offsetof(struct instance_globals_s,symset_which_set))},
{"width_instance_globals_s_symset_which_set",(uint64_t)(sizeof(((struct instance_globals_s*)0)->symset_which_set))},
{"offset_instance_globals_s_SAVEF",(uint64_t)(offsetof(struct instance_globals_s,SAVEF))},
{"width_instance_globals_s_SAVEF",(uint64_t)(sizeof(((struct instance_globals_s*)0)->SAVEF))},
{"offset_instance_globals_s_sortlootmode",(uint64_t)(offsetof(struct instance_globals_s,sortlootmode))},
{"width_instance_globals_s_sortlootmode",(uint64_t)(sizeof(((struct instance_globals_s*)0)->sortlootmode))},
{"offset_instance_globals_s_skipdrin",(uint64_t)(offsetof(struct instance_globals_s,skipdrin))},
{"width_instance_globals_s_skipdrin",(uint64_t)(sizeof(((struct instance_globals_s*)0)->skipdrin))},
{"offset_instance_globals_s_somebody_can_move",(uint64_t)(offsetof(struct instance_globals_s,somebody_can_move))},
{"width_instance_globals_s_somebody_can_move",(uint64_t)(sizeof(((struct instance_globals_s*)0)->somebody_can_move))},
{"offset_instance_globals_s_symset_list",(uint64_t)(offsetof(struct instance_globals_s,symset_list))},
{"width_instance_globals_s_symset_list",(uint64_t)(sizeof(((struct instance_globals_s*)0)->symset_list))},
{"offset_instance_globals_s_save_menucolors",(uint64_t)(offsetof(struct instance_globals_s,save_menucolors))},
{"width_instance_globals_s_save_menucolors",(uint64_t)(sizeof(((struct instance_globals_s*)0)->save_menucolors))},
{"offset_instance_globals_s_save_colorings",(uint64_t)(offsetof(struct instance_globals_s,save_colorings))},
{"width_instance_globals_s_save_colorings",(uint64_t)(sizeof(((struct instance_globals_s*)0)->save_colorings))},
{"offset_instance_globals_s_simple_options_help",(uint64_t)(offsetof(struct instance_globals_s,simple_options_help))},
{"width_instance_globals_s_simple_options_help",(uint64_t)(sizeof(((struct instance_globals_s*)0)->simple_options_help))},
{"offset_instance_globals_s_sellobj_first",(uint64_t)(offsetof(struct instance_globals_s,sellobj_first))},
{"width_instance_globals_s_sellobj_first",(uint64_t)(sizeof(((struct instance_globals_s*)0)->sellobj_first))},
{"offset_instance_globals_s_shop_filter",(uint64_t)(offsetof(struct instance_globals_s,shop_filter))},
{"width_instance_globals_s_shop_filter",(uint64_t)(sizeof(((struct instance_globals_s*)0)->shop_filter))},
{"offset_instance_globals_s_saved_pline_index",(uint64_t)(offsetof(struct instance_globals_s,saved_pline_index))},
{"width_instance_globals_s_saved_pline_index",(uint64_t)(sizeof(((struct instance_globals_s*)0)->saved_pline_index))},
{"offset_instance_globals_s_saved_plines",(uint64_t)(offsetof(struct instance_globals_s,saved_plines))},
{"width_instance_globals_s_saved_plines",(uint64_t)(sizeof(((struct instance_globals_s*)0)->saved_plines))},
{"offset_instance_globals_s_sex_change_ok",(uint64_t)(offsetof(struct instance_globals_s,sex_change_ok))},
{"width_instance_globals_s_sex_change_ok",(uint64_t)(sizeof(((struct instance_globals_s*)0)->sex_change_ok))},
{"offset_instance_globals_s_sell_response",(uint64_t)(offsetof(struct instance_globals_s,sell_response))},
{"width_instance_globals_s_sell_response",(uint64_t)(sizeof(((struct instance_globals_s*)0)->sell_response))},
{"offset_instance_globals_s_sell_how",(uint64_t)(offsetof(struct instance_globals_s,sell_how))},
{"width_instance_globals_s_sell_how",(uint64_t)(sizeof(((struct instance_globals_s*)0)->sell_how))},
{"offset_instance_globals_s_spl_sortmode",(uint64_t)(offsetof(struct instance_globals_s,spl_sortmode))},
{"width_instance_globals_s_spl_sortmode",(uint64_t)(sizeof(((struct instance_globals_s*)0)->spl_sortmode))},
{"offset_instance_globals_s_spl_orderindx",(uint64_t)(offsetof(struct instance_globals_s,spl_orderindx))},
{"width_instance_globals_s_spl_orderindx",(uint64_t)(sizeof(((struct instance_globals_s*)0)->spl_orderindx))},
{"offset_instance_globals_s_stealoid",(uint64_t)(offsetof(struct instance_globals_s,stealoid))},
{"width_instance_globals_s_stealoid",(uint64_t)(sizeof(((struct instance_globals_s*)0)->stealoid))},
{"offset_instance_globals_s_stealmid",(uint64_t)(offsetof(struct instance_globals_s,stealmid))},
{"width_instance_globals_s_stealmid",(uint64_t)(sizeof(((struct instance_globals_s*)0)->stealmid))},
{"offset_instance_globals_s_seethru",(uint64_t)(offsetof(struct instance_globals_s,seethru))},
{"width_instance_globals_s_seethru",(uint64_t)(sizeof(((struct instance_globals_s*)0)->seethru))},
{"offset_instance_globals_s_havestate",(uint64_t)(offsetof(struct instance_globals_s,havestate))},
{"width_instance_globals_s_havestate",(uint64_t)(sizeof(((struct instance_globals_s*)0)->havestate))},
{"size_instance_globals_saved_b",(uint64_t)(sizeof(struct instance_globals_saved_b))},
{"align_instance_globals_saved_b",(uint64_t)(__alignof__(struct instance_globals_saved_b))},
{"offset_instance_globals_saved_b_branches",(uint64_t)(offsetof(struct instance_globals_saved_b,branches))},
{"width_instance_globals_saved_b_branches",(uint64_t)(sizeof(((struct instance_globals_saved_b*)0)->branches))},
{"offset_instance_globals_saved_b_bbubbles",(uint64_t)(offsetof(struct instance_globals_saved_b,bbubbles))},
{"width_instance_globals_saved_b_bbubbles",(uint64_t)(sizeof(((struct instance_globals_saved_b*)0)->bbubbles))},
{"offset_instance_globals_saved_b_bases",(uint64_t)(offsetof(struct instance_globals_saved_b,bases))},
{"width_instance_globals_saved_b_bases",(uint64_t)(sizeof(((struct instance_globals_saved_b*)0)->bases))},
{"size_instance_globals_saved_c",(uint64_t)(sizeof(struct instance_globals_saved_c))},
{"align_instance_globals_saved_c",(uint64_t)(__alignof__(struct instance_globals_saved_c))},
{"offset_instance_globals_saved_c_context",(uint64_t)(offsetof(struct instance_globals_saved_c,context))},
{"width_instance_globals_saved_c_context",(uint64_t)(sizeof(((struct instance_globals_saved_c*)0)->context))},
{"size_instance_globals_saved_d",(uint64_t)(sizeof(struct instance_globals_saved_d))},
{"align_instance_globals_saved_d",(uint64_t)(__alignof__(struct instance_globals_saved_d))},
{"offset_instance_globals_saved_d_dungeons",(uint64_t)(offsetof(struct instance_globals_saved_d,dungeons))},
{"width_instance_globals_saved_d_dungeons",(uint64_t)(sizeof(((struct instance_globals_saved_d*)0)->dungeons))},
{"offset_instance_globals_saved_d_dungeon_topology",(uint64_t)(offsetof(struct instance_globals_saved_d,dungeon_topology))},
{"width_instance_globals_saved_d_dungeon_topology",(uint64_t)(sizeof(((struct instance_globals_saved_d*)0)->dungeon_topology))},
{"offset_instance_globals_saved_d_dndest",(uint64_t)(offsetof(struct instance_globals_saved_d,dndest))},
{"width_instance_globals_saved_d_dndest",(uint64_t)(sizeof(((struct instance_globals_saved_d*)0)->dndest))},
{"offset_instance_globals_saved_d_doors",(uint64_t)(offsetof(struct instance_globals_saved_d,doors))},
{"width_instance_globals_saved_d_doors",(uint64_t)(sizeof(((struct instance_globals_saved_d*)0)->doors))},
{"offset_instance_globals_saved_d_doors_alloc",(uint64_t)(offsetof(struct instance_globals_saved_d,doors_alloc))},
{"width_instance_globals_saved_d_doors_alloc",(uint64_t)(sizeof(((struct instance_globals_saved_d*)0)->doors_alloc))},
{"offset_instance_globals_saved_d_disco",(uint64_t)(offsetof(struct instance_globals_saved_d,disco))},
{"width_instance_globals_saved_d_disco",(uint64_t)(sizeof(((struct instance_globals_saved_d*)0)->disco))},
{"size_instance_globals_saved_e",(uint64_t)(sizeof(struct instance_globals_saved_e))},
{"align_instance_globals_saved_e",(uint64_t)(__alignof__(struct instance_globals_saved_e))},
{"offset_instance_globals_saved_e_exclusion_zones",(uint64_t)(offsetof(struct instance_globals_saved_e,exclusion_zones))},
{"width_instance_globals_saved_e_exclusion_zones",(uint64_t)(sizeof(((struct instance_globals_saved_e*)0)->exclusion_zones))},
{"size_instance_globals_saved_h",(uint64_t)(sizeof(struct instance_globals_saved_h))},
{"align_instance_globals_saved_h",(uint64_t)(__alignof__(struct instance_globals_saved_h))},
{"offset_instance_globals_saved_h_hackpid",(uint64_t)(offsetof(struct instance_globals_saved_h,hackpid))},
{"width_instance_globals_saved_h_hackpid",(uint64_t)(sizeof(((struct instance_globals_saved_h*)0)->hackpid))},
{"size_instance_globals_saved_i",(uint64_t)(sizeof(struct instance_globals_saved_i))},
{"align_instance_globals_saved_i",(uint64_t)(__alignof__(struct instance_globals_saved_i))},
{"offset_instance_globals_saved_i_inv_pos",(uint64_t)(offsetof(struct instance_globals_saved_i,inv_pos))},
{"width_instance_globals_saved_i_inv_pos",(uint64_t)(sizeof(((struct instance_globals_saved_i*)0)->inv_pos))},
{"size_instance_globals_saved_k",(uint64_t)(sizeof(struct instance_globals_saved_k))},
{"align_instance_globals_saved_k",(uint64_t)(__alignof__(struct instance_globals_saved_k))},
{"offset_instance_globals_saved_k_killer",(uint64_t)(offsetof(struct instance_globals_saved_k,killer))},
{"width_instance_globals_saved_k_killer",(uint64_t)(sizeof(((struct instance_globals_saved_k*)0)->killer))},
{"size_instance_globals_saved_l",(uint64_t)(sizeof(struct instance_globals_saved_l))},
{"align_instance_globals_saved_l",(uint64_t)(__alignof__(struct instance_globals_saved_l))},
{"offset_instance_globals_saved_l_lastseentyp",(uint64_t)(offsetof(struct instance_globals_saved_l,lastseentyp))},
{"width_instance_globals_saved_l_lastseentyp",(uint64_t)(sizeof(((struct instance_globals_saved_l*)0)->lastseentyp))},
{"offset_instance_globals_saved_l_level",(uint64_t)(offsetof(struct instance_globals_saved_l,level))},
{"width_instance_globals_saved_l_level",(uint64_t)(sizeof(((struct instance_globals_saved_l*)0)->level))},
{"offset_instance_globals_saved_l_level_info",(uint64_t)(offsetof(struct instance_globals_saved_l,level_info))},
{"width_instance_globals_saved_l_level_info",(uint64_t)(sizeof(((struct instance_globals_saved_l*)0)->level_info))},
{"size_instance_globals_saved_m",(uint64_t)(sizeof(struct instance_globals_saved_m))},
{"align_instance_globals_saved_m",(uint64_t)(__alignof__(struct instance_globals_saved_m))},
{"offset_instance_globals_saved_m_mapseenchn",(uint64_t)(offsetof(struct instance_globals_saved_m,mapseenchn))},
{"width_instance_globals_saved_m_mapseenchn",(uint64_t)(sizeof(((struct instance_globals_saved_m*)0)->mapseenchn))},
{"offset_instance_globals_saved_m_moves",(uint64_t)(offsetof(struct instance_globals_saved_m,moves))},
{"width_instance_globals_saved_m_moves",(uint64_t)(sizeof(((struct instance_globals_saved_m*)0)->moves))},
{"offset_instance_globals_saved_m_mvitals",(uint64_t)(offsetof(struct instance_globals_saved_m,mvitals))},
{"width_instance_globals_saved_m_mvitals",(uint64_t)(sizeof(((struct instance_globals_saved_m*)0)->mvitals))},
{"size_instance_globals_saved_n",(uint64_t)(sizeof(struct instance_globals_saved_n))},
{"align_instance_globals_saved_n",(uint64_t)(__alignof__(struct instance_globals_saved_n))},
{"offset_instance_globals_saved_n_n_dgns",(uint64_t)(offsetof(struct instance_globals_saved_n,n_dgns))},
{"width_instance_globals_saved_n_n_dgns",(uint64_t)(sizeof(((struct instance_globals_saved_n*)0)->n_dgns))},
{"offset_instance_globals_saved_n_nhuuid",(uint64_t)(offsetof(struct instance_globals_saved_n,nhuuid))},
{"width_instance_globals_saved_n_nhuuid",(uint64_t)(sizeof(((struct instance_globals_saved_n*)0)->nhuuid))},
{"offset_instance_globals_saved_n_nroom",(uint64_t)(offsetof(struct instance_globals_saved_n,nroom))},
{"width_instance_globals_saved_n_nroom",(uint64_t)(sizeof(((struct instance_globals_saved_n*)0)->nroom))},
{"offset_instance_globals_saved_n_n_regions",(uint64_t)(offsetof(struct instance_globals_saved_n,n_regions))},
{"width_instance_globals_saved_n_n_regions",(uint64_t)(sizeof(((struct instance_globals_saved_n*)0)->n_regions))},
{"size_instance_globals_saved_o",(uint64_t)(sizeof(struct instance_globals_saved_o))},
{"align_instance_globals_saved_o",(uint64_t)(__alignof__(struct instance_globals_saved_o))},
{"offset_instance_globals_saved_o_oracle_cnt",(uint64_t)(offsetof(struct instance_globals_saved_o,oracle_cnt))},
{"width_instance_globals_saved_o_oracle_cnt",(uint64_t)(sizeof(((struct instance_globals_saved_o*)0)->oracle_cnt))},
{"offset_instance_globals_saved_o_oracle_loc",(uint64_t)(offsetof(struct instance_globals_saved_o,oracle_loc))},
{"width_instance_globals_saved_o_oracle_loc",(uint64_t)(sizeof(((struct instance_globals_saved_o*)0)->oracle_loc))},
{"offset_instance_globals_saved_o_omoves",(uint64_t)(offsetof(struct instance_globals_saved_o,omoves))},
{"width_instance_globals_saved_o_omoves",(uint64_t)(sizeof(((struct instance_globals_saved_o*)0)->omoves))},
{"size_instance_globals_saved_p",(uint64_t)(sizeof(struct instance_globals_saved_p))},
{"align_instance_globals_saved_p",(uint64_t)(__alignof__(struct instance_globals_saved_p))},
{"offset_instance_globals_saved_p_plname",(uint64_t)(offsetof(struct instance_globals_saved_p,plname))},
{"width_instance_globals_saved_p_plname",(uint64_t)(sizeof(((struct instance_globals_saved_p*)0)->plname))},
{"offset_instance_globals_saved_p_pl_character",(uint64_t)(offsetof(struct instance_globals_saved_p,pl_character))},
{"width_instance_globals_saved_p_pl_character",(uint64_t)(sizeof(((struct instance_globals_saved_p*)0)->pl_character))},
{"offset_instance_globals_saved_p_pl_fruit",(uint64_t)(offsetof(struct instance_globals_saved_p,pl_fruit))},
{"width_instance_globals_saved_p_pl_fruit",(uint64_t)(sizeof(((struct instance_globals_saved_p*)0)->pl_fruit))},
{"size_instance_globals_saved_q",(uint64_t)(sizeof(struct instance_globals_saved_q))},
{"align_instance_globals_saved_q",(uint64_t)(__alignof__(struct instance_globals_saved_q))},
{"offset_instance_globals_saved_q_quest_status",(uint64_t)(offsetof(struct instance_globals_saved_q,quest_status))},
{"width_instance_globals_saved_q_quest_status",(uint64_t)(sizeof(((struct instance_globals_saved_q*)0)->quest_status))},
{"size_instance_globals_saved_r",(uint64_t)(sizeof(struct instance_globals_saved_r))},
{"align_instance_globals_saved_r",(uint64_t)(__alignof__(struct instance_globals_saved_r))},
{"offset_instance_globals_saved_r_rooms",(uint64_t)(offsetof(struct instance_globals_saved_r,rooms))},
{"width_instance_globals_saved_r_rooms",(uint64_t)(sizeof(((struct instance_globals_saved_r*)0)->rooms))},
{"size_instance_globals_saved_s",(uint64_t)(sizeof(struct instance_globals_saved_s))},
{"align_instance_globals_saved_s",(uint64_t)(__alignof__(struct instance_globals_saved_s))},
{"offset_instance_globals_saved_s_spl_book",(uint64_t)(offsetof(struct instance_globals_saved_s,spl_book))},
{"width_instance_globals_saved_s_spl_book",(uint64_t)(sizeof(((struct instance_globals_saved_s*)0)->spl_book))},
{"offset_instance_globals_saved_s_sp_levchn",(uint64_t)(offsetof(struct instance_globals_saved_s,sp_levchn))},
{"width_instance_globals_saved_s_sp_levchn",(uint64_t)(sizeof(((struct instance_globals_saved_s*)0)->sp_levchn))},
{"size_instance_globals_saved_t",(uint64_t)(sizeof(struct instance_globals_saved_t))},
{"align_instance_globals_saved_t",(uint64_t)(__alignof__(struct instance_globals_saved_t))},
{"offset_instance_globals_saved_t_tune",(uint64_t)(offsetof(struct instance_globals_saved_t,tune))},
{"width_instance_globals_saved_t_tune",(uint64_t)(sizeof(((struct instance_globals_saved_t*)0)->tune))},
{"offset_instance_globals_saved_t_timer_id",(uint64_t)(offsetof(struct instance_globals_saved_t,timer_id))},
{"width_instance_globals_saved_t_timer_id",(uint64_t)(sizeof(((struct instance_globals_saved_t*)0)->timer_id))},
{"size_instance_globals_saved_u",(uint64_t)(sizeof(struct instance_globals_saved_u))},
{"align_instance_globals_saved_u",(uint64_t)(__alignof__(struct instance_globals_saved_u))},
{"offset_instance_globals_saved_u_updest",(uint64_t)(offsetof(struct instance_globals_saved_u,updest))},
{"width_instance_globals_saved_u_updest",(uint64_t)(sizeof(((struct instance_globals_saved_u*)0)->updest))},
{"size_instance_globals_saved_w",(uint64_t)(sizeof(struct instance_globals_saved_w))},
{"align_instance_globals_saved_w",(uint64_t)(__alignof__(struct instance_globals_saved_w))},
{"offset_instance_globals_saved_w_wreserve",(uint64_t)(offsetof(struct instance_globals_saved_w,wreserve))},
{"width_instance_globals_saved_w_wreserve",(uint64_t)(sizeof(((struct instance_globals_saved_w*)0)->wreserve))},
{"offset_instance_globals_saved_w_wtreserved",(uint64_t)(offsetof(struct instance_globals_saved_w,wtreserved))},
{"width_instance_globals_saved_w_wtreserved",(uint64_t)(sizeof(((struct instance_globals_saved_w*)0)->wtreserved))},
{"size_instance_globals_saved_x",(uint64_t)(sizeof(struct instance_globals_saved_x))},
{"align_instance_globals_saved_x",(uint64_t)(__alignof__(struct instance_globals_saved_x))},
{"offset_instance_globals_saved_x_xmin",(uint64_t)(offsetof(struct instance_globals_saved_x,xmin))},
{"width_instance_globals_saved_x_xmin",(uint64_t)(sizeof(((struct instance_globals_saved_x*)0)->xmin))},
{"offset_instance_globals_saved_x_xmax",(uint64_t)(offsetof(struct instance_globals_saved_x,xmax))},
{"width_instance_globals_saved_x_xmax",(uint64_t)(sizeof(((struct instance_globals_saved_x*)0)->xmax))},
{"size_instance_globals_saved_y",(uint64_t)(sizeof(struct instance_globals_saved_y))},
{"align_instance_globals_saved_y",(uint64_t)(__alignof__(struct instance_globals_saved_y))},
{"offset_instance_globals_saved_y_ymin",(uint64_t)(offsetof(struct instance_globals_saved_y,ymin))},
{"width_instance_globals_saved_y_ymin",(uint64_t)(sizeof(((struct instance_globals_saved_y*)0)->ymin))},
{"offset_instance_globals_saved_y_ymax",(uint64_t)(offsetof(struct instance_globals_saved_y,ymax))},
{"width_instance_globals_saved_y_ymax",(uint64_t)(sizeof(((struct instance_globals_saved_y*)0)->ymax))},
{"size_instance_globals_t",(uint64_t)(sizeof(struct instance_globals_t))},
{"align_instance_globals_t",(uint64_t)(__alignof__(struct instance_globals_t))},
{"offset_instance_globals_t_trapinfo",(uint64_t)(offsetof(struct instance_globals_t,trapinfo))},
{"width_instance_globals_t_trapinfo",(uint64_t)(sizeof(((struct instance_globals_t*)0)->trapinfo))},
{"offset_instance_globals_t_tbx",(uint64_t)(offsetof(struct instance_globals_t,tbx))},
{"width_instance_globals_t_tbx",(uint64_t)(sizeof(((struct instance_globals_t*)0)->tbx))},
{"offset_instance_globals_t_tby",(uint64_t)(offsetof(struct instance_globals_t,tby))},
{"width_instance_globals_t_tby",(uint64_t)(sizeof(((struct instance_globals_t*)0)->tby))},
{"offset_instance_globals_t_toplines",(uint64_t)(offsetof(struct instance_globals_t,toplines))},
{"width_instance_globals_t_toplines",(uint64_t)(sizeof(((struct instance_globals_t*)0)->toplines))},
{"offset_instance_globals_t_thrownobj",(uint64_t)(offsetof(struct instance_globals_t,thrownobj))},
{"width_instance_globals_t_thrownobj",(uint64_t)(sizeof(((struct instance_globals_t*)0)->thrownobj))},
{"offset_instance_globals_t_tc_gbl_data",(uint64_t)(offsetof(struct instance_globals_t,tc_gbl_data))},
{"width_instance_globals_t_tc_gbl_data",(uint64_t)(sizeof(((struct instance_globals_t*)0)->tc_gbl_data))},
{"offset_instance_globals_t_tmp_anything",(uint64_t)(offsetof(struct instance_globals_t,tmp_anything))},
{"width_instance_globals_t_tmp_anything",(uint64_t)(sizeof(((struct instance_globals_t*)0)->tmp_anything))},
{"offset_instance_globals_t_travelmap",(uint64_t)(offsetof(struct instance_globals_t,travelmap))},
{"width_instance_globals_t_travelmap",(uint64_t)(sizeof(((struct instance_globals_t*)0)->travelmap))},
{"offset_instance_globals_t_this_type",(uint64_t)(offsetof(struct instance_globals_t,this_type))},
{"width_instance_globals_t_this_type",(uint64_t)(sizeof(((struct instance_globals_t*)0)->this_type))},
{"offset_instance_globals_t_this_title",(uint64_t)(offsetof(struct instance_globals_t,this_title))},
{"width_instance_globals_t_this_title",(uint64_t)(sizeof(((struct instance_globals_t*)0)->this_title))},
{"offset_instance_globals_t_trapx",(uint64_t)(offsetof(struct instance_globals_t,trapx))},
{"width_instance_globals_t_trapx",(uint64_t)(sizeof(((struct instance_globals_t*)0)->trapx))},
{"offset_instance_globals_t_trapy",(uint64_t)(offsetof(struct instance_globals_t,trapy))},
{"width_instance_globals_t_trapy",(uint64_t)(sizeof(((struct instance_globals_t*)0)->trapy))},
{"offset_instance_globals_t_true_rumor_size",(uint64_t)(offsetof(struct instance_globals_t,true_rumor_size))},
{"width_instance_globals_t_true_rumor_size",(uint64_t)(sizeof(((struct instance_globals_t*)0)->true_rumor_size))},
{"offset_instance_globals_t_true_rumor_start",(uint64_t)(offsetof(struct instance_globals_t,true_rumor_start))},
{"width_instance_globals_t_true_rumor_start",(uint64_t)(sizeof(((struct instance_globals_t*)0)->true_rumor_start))},
{"offset_instance_globals_t_true_rumor_end",(uint64_t)(offsetof(struct instance_globals_t,true_rumor_end))},
{"width_instance_globals_t_true_rumor_end",(uint64_t)(sizeof(((struct instance_globals_t*)0)->true_rumor_end))},
{"offset_instance_globals_t_themeroom_failed",(uint64_t)(offsetof(struct instance_globals_t,themeroom_failed))},
{"width_instance_globals_t_themeroom_failed",(uint64_t)(sizeof(((struct instance_globals_t*)0)->themeroom_failed))},
{"offset_instance_globals_t_timer_base",(uint64_t)(offsetof(struct instance_globals_t,timer_base))},
{"width_instance_globals_t_timer_base",(uint64_t)(sizeof(((struct instance_globals_t*)0)->timer_base))},
{"offset_instance_globals_t_toptenwin",(uint64_t)(offsetof(struct instance_globals_t,toptenwin))},
{"width_instance_globals_t_toptenwin",(uint64_t)(sizeof(((struct instance_globals_t*)0)->toptenwin))},
{"offset_instance_globals_t_twohits",(uint64_t)(offsetof(struct instance_globals_t,twohits))},
{"width_instance_globals_t_twohits",(uint64_t)(sizeof(((struct instance_globals_t*)0)->twohits))},
{"offset_instance_globals_t_havestate",(uint64_t)(offsetof(struct instance_globals_t,havestate))},
{"width_instance_globals_t_havestate",(uint64_t)(sizeof(((struct instance_globals_t*)0)->havestate))},
{"size_instance_globals_u",(uint64_t)(sizeof(struct instance_globals_u))},
{"align_instance_globals_u",(uint64_t)(__alignof__(struct instance_globals_u))},
{"offset_instance_globals_u_update_all",(uint64_t)(offsetof(struct instance_globals_u,update_all))},
{"width_instance_globals_u_update_all",(uint64_t)(sizeof(((struct instance_globals_u*)0)->update_all))},
{"offset_instance_globals_u_unweapon",(uint64_t)(offsetof(struct instance_globals_u,unweapon))},
{"width_instance_globals_u_unweapon",(uint64_t)(sizeof(((struct instance_globals_u*)0)->unweapon))},
{"offset_instance_globals_u_urole",(uint64_t)(offsetof(struct instance_globals_u,urole))},
{"width_instance_globals_u_urole",(uint64_t)(sizeof(((struct instance_globals_u*)0)->urole))},
{"offset_instance_globals_u_urace",(uint64_t)(offsetof(struct instance_globals_u,urace))},
{"width_instance_globals_u_urace",(uint64_t)(sizeof(((struct instance_globals_u*)0)->urace))},
{"offset_instance_globals_u_uz_save",(uint64_t)(offsetof(struct instance_globals_u,uz_save))},
{"width_instance_globals_u_uz_save",(uint64_t)(sizeof(((struct instance_globals_u*)0)->uz_save))},
{"offset_instance_globals_u_havestate",(uint64_t)(offsetof(struct instance_globals_u,havestate))},
{"width_instance_globals_u_havestate",(uint64_t)(sizeof(((struct instance_globals_u*)0)->havestate))},
{"size_instance_globals_v",(uint64_t)(sizeof(struct instance_globals_v))},
{"align_instance_globals_v",(uint64_t)(__alignof__(struct instance_globals_v))},
{"offset_instance_globals_v_valset",(uint64_t)(offsetof(struct instance_globals_v,valset))},
{"width_instance_globals_v_valset",(uint64_t)(sizeof(((struct instance_globals_v*)0)->valset))},
{"offset_instance_globals_v_valuables",(uint64_t)(offsetof(struct instance_globals_v,valuables))},
{"width_instance_globals_v_valuables",(uint64_t)(sizeof(((struct instance_globals_v*)0)->valuables))},
{"offset_instance_globals_v_vis",(uint64_t)(offsetof(struct instance_globals_v,vis))},
{"width_instance_globals_v_vis",(uint64_t)(sizeof(((struct instance_globals_v*)0)->vis))},
{"offset_instance_globals_v_vault_x",(uint64_t)(offsetof(struct instance_globals_v,vault_x))},
{"width_instance_globals_v_vault_x",(uint64_t)(sizeof(((struct instance_globals_v*)0)->vault_x))},
{"offset_instance_globals_v_vault_y",(uint64_t)(offsetof(struct instance_globals_v,vault_y))},
{"width_instance_globals_v_vault_y",(uint64_t)(sizeof(((struct instance_globals_v*)0)->vault_y))},
{"offset_instance_globals_v_vamp_rise_msg",(uint64_t)(offsetof(struct instance_globals_v,vamp_rise_msg))},
{"width_instance_globals_v_vamp_rise_msg",(uint64_t)(sizeof(((struct instance_globals_v*)0)->vamp_rise_msg))},
{"offset_instance_globals_v_val_for_n_or_more",(uint64_t)(offsetof(struct instance_globals_v,val_for_n_or_more))},
{"width_instance_globals_v_val_for_n_or_more",(uint64_t)(sizeof(((struct instance_globals_v*)0)->val_for_n_or_more))},
{"offset_instance_globals_v_valid_menu_classes",(uint64_t)(offsetof(struct instance_globals_v,valid_menu_classes))},
{"width_instance_globals_v_valid_menu_classes",(uint64_t)(sizeof(((struct instance_globals_v*)0)->valid_menu_classes))},
{"offset_instance_globals_v_viz_array",(uint64_t)(offsetof(struct instance_globals_v,viz_array))},
{"width_instance_globals_v_viz_array",(uint64_t)(sizeof(((struct instance_globals_v*)0)->viz_array))},
{"offset_instance_globals_v_viz_rmin",(uint64_t)(offsetof(struct instance_globals_v,viz_rmin))},
{"width_instance_globals_v_viz_rmin",(uint64_t)(sizeof(((struct instance_globals_v*)0)->viz_rmin))},
{"offset_instance_globals_v_viz_rmax",(uint64_t)(offsetof(struct instance_globals_v,viz_rmax))},
{"width_instance_globals_v_viz_rmax",(uint64_t)(sizeof(((struct instance_globals_v*)0)->viz_rmax))},
{"offset_instance_globals_v_vision_full_recalc",(uint64_t)(offsetof(struct instance_globals_v,vision_full_recalc))},
{"width_instance_globals_v_vision_full_recalc",(uint64_t)(sizeof(((struct instance_globals_v*)0)->vision_full_recalc))},
{"offset_instance_globals_v_voice",(uint64_t)(offsetof(struct instance_globals_v,voice))},
{"width_instance_globals_v_voice",(uint64_t)(sizeof(((struct instance_globals_v*)0)->voice))},
{"offset_instance_globals_v_havestate",(uint64_t)(offsetof(struct instance_globals_v,havestate))},
{"width_instance_globals_v_havestate",(uint64_t)(sizeof(((struct instance_globals_v*)0)->havestate))},
{"size_instance_globals_w",(uint64_t)(sizeof(struct instance_globals_w))},
{"align_instance_globals_w",(uint64_t)(__alignof__(struct instance_globals_w))},
{"offset_instance_globals_w_warn_obj_cnt",(uint64_t)(offsetof(struct instance_globals_w,warn_obj_cnt))},
{"width_instance_globals_w_warn_obj_cnt",(uint64_t)(sizeof(((struct instance_globals_w*)0)->warn_obj_cnt))},
{"offset_instance_globals_w_wailmsg",(uint64_t)(offsetof(struct instance_globals_w,wailmsg))},
{"width_instance_globals_w_wailmsg",(uint64_t)(sizeof(((struct instance_globals_w*)0)->wailmsg))},
{"offset_instance_globals_w_wasinwater",(uint64_t)(offsetof(struct instance_globals_w,wasinwater))},
{"width_instance_globals_w_wasinwater",(uint64_t)(sizeof(((struct instance_globals_w*)0)->wasinwater))},
{"offset_instance_globals_w_warnsyms",(uint64_t)(offsetof(struct instance_globals_w,warnsyms))},
{"width_instance_globals_w_warnsyms",(uint64_t)(sizeof(((struct instance_globals_w*)0)->warnsyms))},
{"offset_instance_globals_w_wizkit",(uint64_t)(offsetof(struct instance_globals_w,wizkit))},
{"width_instance_globals_w_wizkit",(uint64_t)(sizeof(((struct instance_globals_w*)0)->wizkit))},
{"offset_instance_globals_w_wc",(uint64_t)(offsetof(struct instance_globals_w,wc))},
{"width_instance_globals_w_wc",(uint64_t)(sizeof(((struct instance_globals_w*)0)->wc))},
{"offset_instance_globals_w_wportal",(uint64_t)(offsetof(struct instance_globals_w,wportal))},
{"width_instance_globals_w_wportal",(uint64_t)(sizeof(((struct instance_globals_w*)0)->wportal))},
{"offset_instance_globals_w_wsettings",(uint64_t)(offsetof(struct instance_globals_w,wsettings))},
{"width_instance_globals_w_wsettings",(uint64_t)(sizeof(((struct instance_globals_w*)0)->wsettings))},
{"offset_instance_globals_w_were_changes",(uint64_t)(offsetof(struct instance_globals_w,were_changes))},
{"width_instance_globals_w_were_changes",(uint64_t)(sizeof(((struct instance_globals_w*)0)->were_changes))},
{"offset_instance_globals_w_havestate",(uint64_t)(offsetof(struct instance_globals_w,havestate))},
{"width_instance_globals_w_havestate",(uint64_t)(sizeof(((struct instance_globals_w*)0)->havestate))},
{"size_instance_globals_x",(uint64_t)(sizeof(struct instance_globals_x))},
{"align_instance_globals_x",(uint64_t)(__alignof__(struct instance_globals_x))},
{"offset_instance_globals_x_x_maze_max",(uint64_t)(offsetof(struct instance_globals_x,x_maze_max))},
{"width_instance_globals_x_x_maze_max",(uint64_t)(sizeof(((struct instance_globals_x*)0)->x_maze_max))},
{"offset_instance_globals_x_xlock",(uint64_t)(offsetof(struct instance_globals_x,xlock))},
{"width_instance_globals_x_xlock",(uint64_t)(sizeof(((struct instance_globals_x*)0)->xlock))},
{"offset_instance_globals_x_xnamep",(uint64_t)(offsetof(struct instance_globals_x,xnamep))},
{"width_instance_globals_x_xnamep",(uint64_t)(sizeof(((struct instance_globals_x*)0)->xnamep))},
{"offset_instance_globals_x_xstart",(uint64_t)(offsetof(struct instance_globals_x,xstart))},
{"width_instance_globals_x_xstart",(uint64_t)(sizeof(((struct instance_globals_x*)0)->xstart))},
{"offset_instance_globals_x_xsize",(uint64_t)(offsetof(struct instance_globals_x,xsize))},
{"width_instance_globals_x_xsize",(uint64_t)(sizeof(((struct instance_globals_x*)0)->xsize))},
{"offset_instance_globals_x_havestate",(uint64_t)(offsetof(struct instance_globals_x,havestate))},
{"width_instance_globals_x_havestate",(uint64_t)(sizeof(((struct instance_globals_x*)0)->havestate))},
{"size_instance_globals_y",(uint64_t)(sizeof(struct instance_globals_y))},
{"align_instance_globals_y",(uint64_t)(__alignof__(struct instance_globals_y))},
{"offset_instance_globals_y_y_maze_max",(uint64_t)(offsetof(struct instance_globals_y,y_maze_max))},
{"width_instance_globals_y_y_maze_max",(uint64_t)(sizeof(((struct instance_globals_y*)0)->y_maze_max))},
{"offset_instance_globals_y_youmonst",(uint64_t)(offsetof(struct instance_globals_y,youmonst))},
{"width_instance_globals_y_youmonst",(uint64_t)(sizeof(((struct instance_globals_y*)0)->youmonst))},
{"offset_instance_globals_y_you_buf",(uint64_t)(offsetof(struct instance_globals_y,you_buf))},
{"width_instance_globals_y_you_buf",(uint64_t)(sizeof(((struct instance_globals_y*)0)->you_buf))},
{"offset_instance_globals_y_you_buf_siz",(uint64_t)(offsetof(struct instance_globals_y,you_buf_siz))},
{"width_instance_globals_y_you_buf_siz",(uint64_t)(sizeof(((struct instance_globals_y*)0)->you_buf_siz))},
{"offset_instance_globals_y_ystart",(uint64_t)(offsetof(struct instance_globals_y,ystart))},
{"width_instance_globals_y_ystart",(uint64_t)(sizeof(((struct instance_globals_y*)0)->ystart))},
{"offset_instance_globals_y_ysize",(uint64_t)(offsetof(struct instance_globals_y,ysize))},
{"width_instance_globals_y_ysize",(uint64_t)(sizeof(((struct instance_globals_y*)0)->ysize))},
{"offset_instance_globals_y_havestate",(uint64_t)(offsetof(struct instance_globals_y,havestate))},
{"width_instance_globals_y_havestate",(uint64_t)(sizeof(((struct instance_globals_y*)0)->havestate))},
{"size_instance_globals_z",(uint64_t)(sizeof(struct instance_globals_z))},
{"align_instance_globals_z",(uint64_t)(__alignof__(struct instance_globals_z))},
{"offset_instance_globals_z_zombify",(uint64_t)(offsetof(struct instance_globals_z,zombify))},
{"width_instance_globals_z_zombify",(uint64_t)(sizeof(((struct instance_globals_z*)0)->zombify))},
{"offset_instance_globals_z_zap_oseen",(uint64_t)(offsetof(struct instance_globals_z,zap_oseen))},
{"width_instance_globals_z_zap_oseen",(uint64_t)(sizeof(((struct instance_globals_z*)0)->zap_oseen))},
{"offset_instance_globals_z_havestate",(uint64_t)(offsetof(struct instance_globals_z,havestate))},
{"width_instance_globals_z_havestate",(uint64_t)(sizeof(((struct instance_globals_z*)0)->havestate))},
{"size_istat_s",(uint64_t)(sizeof(struct istat_s))},
{"align_istat_s",(uint64_t)(__alignof__(struct istat_s))},
{"offset_istat_s_fldname",(uint64_t)(offsetof(struct istat_s,fldname))},
{"width_istat_s_fldname",(uint64_t)(sizeof(((struct istat_s*)0)->fldname))},
{"offset_istat_s_fldfmt",(uint64_t)(offsetof(struct istat_s,fldfmt))},
{"width_istat_s_fldfmt",(uint64_t)(sizeof(((struct istat_s*)0)->fldfmt))},
{"offset_istat_s_time",(uint64_t)(offsetof(struct istat_s,time))},
{"width_istat_s_time",(uint64_t)(sizeof(((struct istat_s*)0)->time))},
{"offset_istat_s_chg",(uint64_t)(offsetof(struct istat_s,chg))},
{"width_istat_s_chg",(uint64_t)(sizeof(((struct istat_s*)0)->chg))},
{"offset_istat_s_percent_matters",(uint64_t)(offsetof(struct istat_s,percent_matters))},
{"width_istat_s_percent_matters",(uint64_t)(sizeof(((struct istat_s*)0)->percent_matters))},
{"offset_istat_s_percent_value",(uint64_t)(offsetof(struct istat_s,percent_value))},
{"width_istat_s_percent_value",(uint64_t)(sizeof(((struct istat_s*)0)->percent_value))},
{"offset_istat_s_anytype",(uint64_t)(offsetof(struct istat_s,anytype))},
{"width_istat_s_anytype",(uint64_t)(sizeof(((struct istat_s*)0)->anytype))},
{"offset_istat_s_a",(uint64_t)(offsetof(struct istat_s,a))},
{"width_istat_s_a",(uint64_t)(sizeof(((struct istat_s*)0)->a))},
{"offset_istat_s_rawval",(uint64_t)(offsetof(struct istat_s,rawval))},
{"width_istat_s_rawval",(uint64_t)(sizeof(((struct istat_s*)0)->rawval))},
{"offset_istat_s_val",(uint64_t)(offsetof(struct istat_s,val))},
{"width_istat_s_val",(uint64_t)(sizeof(((struct istat_s*)0)->val))},
{"offset_istat_s_valwidth",(uint64_t)(offsetof(struct istat_s,valwidth))},
{"width_istat_s_valwidth",(uint64_t)(sizeof(((struct istat_s*)0)->valwidth))},
{"offset_istat_s_idxmax",(uint64_t)(offsetof(struct istat_s,idxmax))},
{"width_istat_s_idxmax",(uint64_t)(sizeof(((struct istat_s*)0)->idxmax))},
{"offset_istat_s_fld",(uint64_t)(offsetof(struct istat_s,fld))},
{"width_istat_s_fld",(uint64_t)(sizeof(((struct istat_s*)0)->fld))},
{"offset_istat_s_hilite_rule",(uint64_t)(offsetof(struct istat_s,hilite_rule))},
{"width_istat_s_hilite_rule",(uint64_t)(sizeof(((struct istat_s*)0)->hilite_rule))},
{"offset_istat_s_thresholds",(uint64_t)(offsetof(struct istat_s,thresholds))},
{"width_istat_s_thresholds",(uint64_t)(sizeof(((struct istat_s*)0)->thresholds))},
{"size_kinfo",(uint64_t)(sizeof(struct kinfo))},
{"align_kinfo",(uint64_t)(__alignof__(struct kinfo))},
{"offset_kinfo_next",(uint64_t)(offsetof(struct kinfo,next))},
{"width_kinfo_next",(uint64_t)(sizeof(((struct kinfo*)0)->next))},
{"offset_kinfo_id",(uint64_t)(offsetof(struct kinfo,id))},
{"width_kinfo_id",(uint64_t)(sizeof(((struct kinfo*)0)->id))},
{"offset_kinfo_format",(uint64_t)(offsetof(struct kinfo,format))},
{"width_kinfo_format",(uint64_t)(sizeof(((struct kinfo*)0)->format))},
{"offset_kinfo_name",(uint64_t)(offsetof(struct kinfo,name))},
{"width_kinfo_name",(uint64_t)(sizeof(((struct kinfo*)0)->name))},
{"size_launchplace",(uint64_t)(sizeof(struct launchplace))},
{"align_launchplace",(uint64_t)(__alignof__(struct launchplace))},
{"offset_launchplace_obj",(uint64_t)(offsetof(struct launchplace,obj))},
{"width_launchplace_obj",(uint64_t)(sizeof(((struct launchplace*)0)->obj))},
{"offset_launchplace_x",(uint64_t)(offsetof(struct launchplace,x))},
{"width_launchplace_x",(uint64_t)(sizeof(((struct launchplace*)0)->x))},
{"offset_launchplace_y",(uint64_t)(offsetof(struct launchplace,y))},
{"width_launchplace_y",(uint64_t)(sizeof(((struct launchplace*)0)->y))},
{"size_lev_region",(uint64_t)(sizeof(lev_region))},
{"align_lev_region",(uint64_t)(__alignof__(lev_region))},
{"offset_lev_region_inarea",(uint64_t)(offsetof(lev_region,inarea))},
{"width_lev_region_inarea",(uint64_t)(sizeof(((lev_region*)0)->inarea))},
{"offset_lev_region_delarea",(uint64_t)(offsetof(lev_region,delarea))},
{"width_lev_region_delarea",(uint64_t)(sizeof(((lev_region*)0)->delarea))},
{"offset_lev_region_in_islev",(uint64_t)(offsetof(lev_region,in_islev))},
{"width_lev_region_in_islev",(uint64_t)(sizeof(((lev_region*)0)->in_islev))},
{"offset_lev_region_del_islev",(uint64_t)(offsetof(lev_region,del_islev))},
{"width_lev_region_del_islev",(uint64_t)(sizeof(((lev_region*)0)->del_islev))},
{"offset_lev_region_rtype",(uint64_t)(offsetof(lev_region,rtype))},
{"width_lev_region_rtype",(uint64_t)(sizeof(((lev_region*)0)->rtype))},
{"offset_lev_region_padding",(uint64_t)(offsetof(lev_region,padding))},
{"width_lev_region_padding",(uint64_t)(sizeof(((lev_region*)0)->padding))},
{"offset_lev_region_rname",(uint64_t)(offsetof(lev_region,rname))},
{"width_lev_region_rname",(uint64_t)(sizeof(((lev_region*)0)->rname))},
{"size_levelflags",(uint64_t)(sizeof(struct levelflags))},
{"align_levelflags",(uint64_t)(__alignof__(struct levelflags))},
{"offset_levelflags_nfountains",(uint64_t)(offsetof(struct levelflags,nfountains))},
{"width_levelflags_nfountains",(uint64_t)(sizeof(((struct levelflags*)0)->nfountains))},
{"offset_levelflags_nsinks",(uint64_t)(offsetof(struct levelflags,nsinks))},
{"width_levelflags_nsinks",(uint64_t)(sizeof(((struct levelflags*)0)->nsinks))},
{"offset_levelflags_temperature",(uint64_t)(offsetof(struct levelflags,temperature))},
{"width_levelflags_temperature",(uint64_t)(sizeof(((struct levelflags*)0)->temperature))},
{"offset_levelflags_stasis_until",(uint64_t)(offsetof(struct levelflags,stasis_until))},
{"width_levelflags_stasis_until",(uint64_t)(sizeof(((struct levelflags*)0)->stasis_until))},
{"size_lifelists",(uint64_t)(sizeof(struct lifelists))},
{"align_lifelists",(uint64_t)(__alignof__(struct lifelists))},
{"offset_lifelists_total_seen_upclose",(uint64_t)(offsetof(struct lifelists,total_seen_upclose))},
{"width_lifelists_total_seen_upclose",(uint64_t)(sizeof(((struct lifelists*)0)->total_seen_upclose))},
{"offset_lifelists_total_photographed",(uint64_t)(offsetof(struct lifelists,total_photographed))},
{"width_lifelists_total_photographed",(uint64_t)(sizeof(((struct lifelists*)0)->total_photographed))},
{"size_linfo",(uint64_t)(sizeof(struct linfo))},
{"align_linfo",(uint64_t)(__alignof__(struct linfo))},
{"offset_linfo_flags",(uint64_t)(offsetof(struct linfo,flags))},
{"width_linfo_flags",(uint64_t)(sizeof(((struct linfo*)0)->flags))},
{"size_mkroom",(uint64_t)(sizeof(struct mkroom))},
{"align_mkroom",(uint64_t)(__alignof__(struct mkroom))},
{"offset_mkroom_lx",(uint64_t)(offsetof(struct mkroom,lx))},
{"width_mkroom_lx",(uint64_t)(sizeof(((struct mkroom*)0)->lx))},
{"offset_mkroom_hx",(uint64_t)(offsetof(struct mkroom,hx))},
{"width_mkroom_hx",(uint64_t)(sizeof(((struct mkroom*)0)->hx))},
{"offset_mkroom_ly",(uint64_t)(offsetof(struct mkroom,ly))},
{"width_mkroom_ly",(uint64_t)(sizeof(((struct mkroom*)0)->ly))},
{"offset_mkroom_hy",(uint64_t)(offsetof(struct mkroom,hy))},
{"width_mkroom_hy",(uint64_t)(sizeof(((struct mkroom*)0)->hy))},
{"offset_mkroom_rtype",(uint64_t)(offsetof(struct mkroom,rtype))},
{"width_mkroom_rtype",(uint64_t)(sizeof(((struct mkroom*)0)->rtype))},
{"offset_mkroom_orig_rtype",(uint64_t)(offsetof(struct mkroom,orig_rtype))},
{"width_mkroom_orig_rtype",(uint64_t)(sizeof(((struct mkroom*)0)->orig_rtype))},
{"offset_mkroom_rlit",(uint64_t)(offsetof(struct mkroom,rlit))},
{"width_mkroom_rlit",(uint64_t)(sizeof(((struct mkroom*)0)->rlit))},
{"offset_mkroom_needfill",(uint64_t)(offsetof(struct mkroom,needfill))},
{"width_mkroom_needfill",(uint64_t)(sizeof(((struct mkroom*)0)->needfill))},
{"offset_mkroom_needjoining",(uint64_t)(offsetof(struct mkroom,needjoining))},
{"width_mkroom_needjoining",(uint64_t)(sizeof(((struct mkroom*)0)->needjoining))},
{"offset_mkroom_doorct",(uint64_t)(offsetof(struct mkroom,doorct))},
{"width_mkroom_doorct",(uint64_t)(sizeof(((struct mkroom*)0)->doorct))},
{"offset_mkroom_fdoor",(uint64_t)(offsetof(struct mkroom,fdoor))},
{"width_mkroom_fdoor",(uint64_t)(sizeof(((struct mkroom*)0)->fdoor))},
{"offset_mkroom_nsubrooms",(uint64_t)(offsetof(struct mkroom,nsubrooms))},
{"width_mkroom_nsubrooms",(uint64_t)(sizeof(((struct mkroom*)0)->nsubrooms))},
{"offset_mkroom_irregular",(uint64_t)(offsetof(struct mkroom,irregular))},
{"width_mkroom_irregular",(uint64_t)(sizeof(((struct mkroom*)0)->irregular))},
{"offset_mkroom_roomnoidx",(uint64_t)(offsetof(struct mkroom,roomnoidx))},
{"width_mkroom_roomnoidx",(uint64_t)(sizeof(((struct mkroom*)0)->roomnoidx))},
{"offset_mkroom_sbrooms",(uint64_t)(offsetof(struct mkroom,sbrooms))},
{"width_mkroom_sbrooms",(uint64_t)(sizeof(((struct mkroom*)0)->sbrooms))},
{"offset_mkroom_resident",(uint64_t)(offsetof(struct mkroom,resident))},
{"width_mkroom_resident",(uint64_t)(sizeof(((struct mkroom*)0)->resident))},
{"size_monst",(uint64_t)(sizeof(struct monst))},
{"align_monst",(uint64_t)(__alignof__(struct monst))},
{"offset_monst_nmon",(uint64_t)(offsetof(struct monst,nmon))},
{"width_monst_nmon",(uint64_t)(sizeof(((struct monst*)0)->nmon))},
{"offset_monst_data",(uint64_t)(offsetof(struct monst,data))},
{"width_monst_data",(uint64_t)(sizeof(((struct monst*)0)->data))},
{"offset_monst_m_id",(uint64_t)(offsetof(struct monst,m_id))},
{"width_monst_m_id",(uint64_t)(sizeof(((struct monst*)0)->m_id))},
{"offset_monst_mnum",(uint64_t)(offsetof(struct monst,mnum))},
{"width_monst_mnum",(uint64_t)(sizeof(((struct monst*)0)->mnum))},
{"offset_monst_cham",(uint64_t)(offsetof(struct monst,cham))},
{"width_monst_cham",(uint64_t)(sizeof(((struct monst*)0)->cham))},
{"offset_monst_movement",(uint64_t)(offsetof(struct monst,movement))},
{"width_monst_movement",(uint64_t)(sizeof(((struct monst*)0)->movement))},
{"offset_monst_m_lev",(uint64_t)(offsetof(struct monst,m_lev))},
{"width_monst_m_lev",(uint64_t)(sizeof(((struct monst*)0)->m_lev))},
{"offset_monst_malign",(uint64_t)(offsetof(struct monst,malign))},
{"width_monst_malign",(uint64_t)(sizeof(((struct monst*)0)->malign))},
{"offset_monst_mx",(uint64_t)(offsetof(struct monst,mx))},
{"width_monst_mx",(uint64_t)(sizeof(((struct monst*)0)->mx))},
{"offset_monst_my",(uint64_t)(offsetof(struct monst,my))},
{"width_monst_my",(uint64_t)(sizeof(((struct monst*)0)->my))},
{"offset_monst_mux",(uint64_t)(offsetof(struct monst,mux))},
{"width_monst_mux",(uint64_t)(sizeof(((struct monst*)0)->mux))},
{"offset_monst_muy",(uint64_t)(offsetof(struct monst,muy))},
{"width_monst_muy",(uint64_t)(sizeof(((struct monst*)0)->muy))},
{"offset_monst_mtrack",(uint64_t)(offsetof(struct monst,mtrack))},
{"width_monst_mtrack",(uint64_t)(sizeof(((struct monst*)0)->mtrack))},
{"offset_monst_mhp",(uint64_t)(offsetof(struct monst,mhp))},
{"width_monst_mhp",(uint64_t)(sizeof(((struct monst*)0)->mhp))},
{"offset_monst_mhpmax",(uint64_t)(offsetof(struct monst,mhpmax))},
{"width_monst_mhpmax",(uint64_t)(sizeof(((struct monst*)0)->mhpmax))},
{"offset_monst_mappearance",(uint64_t)(offsetof(struct monst,mappearance))},
{"width_monst_mappearance",(uint64_t)(sizeof(((struct monst*)0)->mappearance))},
{"offset_monst_m_ap_type",(uint64_t)(offsetof(struct monst,m_ap_type))},
{"width_monst_m_ap_type",(uint64_t)(sizeof(((struct monst*)0)->m_ap_type))},
{"offset_monst_mtame",(uint64_t)(offsetof(struct monst,mtame))},
{"width_monst_mtame",(uint64_t)(sizeof(((struct monst*)0)->mtame))},
{"offset_monst_mintrinsics",(uint64_t)(offsetof(struct monst,mintrinsics))},
{"width_monst_mintrinsics",(uint64_t)(sizeof(((struct monst*)0)->mintrinsics))},
{"offset_monst_mextrinsics",(uint64_t)(offsetof(struct monst,mextrinsics))},
{"width_monst_mextrinsics",(uint64_t)(sizeof(((struct monst*)0)->mextrinsics))},
{"offset_monst_seen_resistance",(uint64_t)(offsetof(struct monst,seen_resistance))},
{"width_monst_seen_resistance",(uint64_t)(sizeof(((struct monst*)0)->seen_resistance))},
{"offset_monst_mspec_used",(uint64_t)(offsetof(struct monst,mspec_used))},
{"width_monst_mspec_used",(uint64_t)(sizeof(((struct monst*)0)->mspec_used))},
{"offset_monst_mstrategy",(uint64_t)(offsetof(struct monst,mstrategy))},
{"width_monst_mstrategy",(uint64_t)(sizeof(((struct monst*)0)->mstrategy))},
{"offset_monst_mgoal",(uint64_t)(offsetof(struct monst,mgoal))},
{"width_monst_mgoal",(uint64_t)(sizeof(((struct monst*)0)->mgoal))},
{"offset_monst_mtrapseen",(uint64_t)(offsetof(struct monst,mtrapseen))},
{"width_monst_mtrapseen",(uint64_t)(sizeof(((struct monst*)0)->mtrapseen))},
{"offset_monst_mlstmv",(uint64_t)(offsetof(struct monst,mlstmv))},
{"width_monst_mlstmv",(uint64_t)(sizeof(((struct monst*)0)->mlstmv))},
{"offset_monst_mstate",(uint64_t)(offsetof(struct monst,mstate))},
{"width_monst_mstate",(uint64_t)(sizeof(((struct monst*)0)->mstate))},
{"offset_monst_migflags",(uint64_t)(offsetof(struct monst,migflags))},
{"width_monst_migflags",(uint64_t)(sizeof(((struct monst*)0)->migflags))},
{"offset_monst_mspare1",(uint64_t)(offsetof(struct monst,mspare1))},
{"width_monst_mspare1",(uint64_t)(sizeof(((struct monst*)0)->mspare1))},
{"offset_monst_minvent",(uint64_t)(offsetof(struct monst,minvent))},
{"width_monst_minvent",(uint64_t)(sizeof(((struct monst*)0)->minvent))},
{"offset_monst_mw",(uint64_t)(offsetof(struct monst,mw))},
{"width_monst_mw",(uint64_t)(sizeof(((struct monst*)0)->mw))},
{"offset_monst_misc_worn_check",(uint64_t)(offsetof(struct monst,misc_worn_check))},
{"width_monst_misc_worn_check",(uint64_t)(sizeof(((struct monst*)0)->misc_worn_check))},
{"offset_monst_weapon_check",(uint64_t)(offsetof(struct monst,weapon_check))},
{"width_monst_weapon_check",(uint64_t)(sizeof(((struct monst*)0)->weapon_check))},
{"offset_monst_meating",(uint64_t)(offsetof(struct monst,meating))},
{"width_monst_meating",(uint64_t)(sizeof(((struct monst*)0)->meating))},
{"offset_monst_mextra",(uint64_t)(offsetof(struct monst,mextra))},
{"width_monst_mextra",(uint64_t)(sizeof(((struct monst*)0)->mextra))},
{"size_multishot",(uint64_t)(sizeof(struct multishot))},
{"align_multishot",(uint64_t)(__alignof__(struct multishot))},
{"offset_multishot_n",(uint64_t)(offsetof(struct multishot,n))},
{"width_multishot_n",(uint64_t)(sizeof(((struct multishot*)0)->n))},
{"offset_multishot_i",(uint64_t)(offsetof(struct multishot,i))},
{"width_multishot_i",(uint64_t)(sizeof(((struct multishot*)0)->i))},
{"offset_multishot_o",(uint64_t)(offsetof(struct multishot,o))},
{"width_multishot_o",(uint64_t)(sizeof(((struct multishot*)0)->o))},
{"offset_multishot_s",(uint64_t)(offsetof(struct multishot,s))},
{"width_multishot_s",(uint64_t)(sizeof(((struct multishot*)0)->s))},
{"size_musable",(uint64_t)(sizeof(struct musable))},
{"align_musable",(uint64_t)(__alignof__(struct musable))},
{"offset_musable_offensive",(uint64_t)(offsetof(struct musable,offensive))},
{"width_musable_offensive",(uint64_t)(sizeof(((struct musable*)0)->offensive))},
{"offset_musable_defensive",(uint64_t)(offsetof(struct musable,defensive))},
{"width_musable_defensive",(uint64_t)(sizeof(((struct musable*)0)->defensive))},
{"offset_musable_misc",(uint64_t)(offsetof(struct musable,misc))},
{"width_musable_misc",(uint64_t)(sizeof(((struct musable*)0)->misc))},
{"offset_musable_has_offense",(uint64_t)(offsetof(struct musable,has_offense))},
{"width_musable_has_offense",(uint64_t)(sizeof(((struct musable*)0)->has_offense))},
{"offset_musable_has_defense",(uint64_t)(offsetof(struct musable,has_defense))},
{"width_musable_has_defense",(uint64_t)(sizeof(((struct musable*)0)->has_defense))},
{"offset_musable_has_misc",(uint64_t)(offsetof(struct musable,has_misc))},
{"width_musable_has_misc",(uint64_t)(sizeof(((struct musable*)0)->has_misc))},
{"size_mvitals",(uint64_t)(sizeof(struct mvitals))},
{"align_mvitals",(uint64_t)(__alignof__(struct mvitals))},
{"offset_mvitals_born",(uint64_t)(offsetof(struct mvitals,born))},
{"width_mvitals_born",(uint64_t)(sizeof(((struct mvitals*)0)->born))},
{"offset_mvitals_died",(uint64_t)(offsetof(struct mvitals,died))},
{"width_mvitals_died",(uint64_t)(sizeof(((struct mvitals*)0)->died))},
{"offset_mvitals_mvflags",(uint64_t)(offsetof(struct mvitals,mvflags))},
{"width_mvitals_mvflags",(uint64_t)(sizeof(((struct mvitals*)0)->mvflags))},
{"size_nhcoord",(uint64_t)(sizeof(struct nhcoord))},
{"align_nhcoord",(uint64_t)(__alignof__(struct nhcoord))},
{"offset_nhcoord_x",(uint64_t)(offsetof(struct nhcoord,x))},
{"width_nhcoord_x",(uint64_t)(sizeof(((struct nhcoord*)0)->x))},
{"offset_nhcoord_y",(uint64_t)(offsetof(struct nhcoord,y))},
{"width_nhcoord_y",(uint64_t)(sizeof(((struct nhcoord*)0)->y))},
{"size_nhrect",(uint64_t)(sizeof(struct nhrect))},
{"align_nhrect",(uint64_t)(__alignof__(struct nhrect))},
{"offset_nhrect_lx",(uint64_t)(offsetof(struct nhrect,lx))},
{"width_nhrect_lx",(uint64_t)(sizeof(((struct nhrect*)0)->lx))},
{"offset_nhrect_ly",(uint64_t)(offsetof(struct nhrect,ly))},
{"width_nhrect_ly",(uint64_t)(sizeof(((struct nhrect*)0)->ly))},
{"offset_nhrect_hx",(uint64_t)(offsetof(struct nhrect,hx))},
{"width_nhrect_hx",(uint64_t)(sizeof(((struct nhrect*)0)->hx))},
{"offset_nhrect_hy",(uint64_t)(offsetof(struct nhrect,hy))},
{"width_nhrect_hy",(uint64_t)(sizeof(((struct nhrect*)0)->hy))},
{"size_novel_tracking",(uint64_t)(sizeof(struct novel_tracking))},
{"align_novel_tracking",(uint64_t)(__alignof__(struct novel_tracking))},
{"offset_novel_tracking_id",(uint64_t)(offsetof(struct novel_tracking,id))},
{"width_novel_tracking_id",(uint64_t)(sizeof(((struct novel_tracking*)0)->id))},
{"offset_novel_tracking_count",(uint64_t)(offsetof(struct novel_tracking,count))},
{"width_novel_tracking_count",(uint64_t)(sizeof(((struct novel_tracking*)0)->count))},
{"offset_novel_tracking_pasg",(uint64_t)(offsetof(struct novel_tracking,pasg))},
{"width_novel_tracking_pasg",(uint64_t)(sizeof(((struct novel_tracking*)0)->pasg))},
{"size_obj",(uint64_t)(sizeof(struct obj))},
{"align_obj",(uint64_t)(__alignof__(struct obj))},
{"offset_obj_nobj",(uint64_t)(offsetof(struct obj,nobj))},
{"width_obj_nobj",(uint64_t)(sizeof(((struct obj*)0)->nobj))},
{"offset_obj_v",(uint64_t)(offsetof(struct obj,v))},
{"width_obj_v",(uint64_t)(sizeof(((struct obj*)0)->v))},
{"offset_obj_cobj",(uint64_t)(offsetof(struct obj,cobj))},
{"width_obj_cobj",(uint64_t)(sizeof(((struct obj*)0)->cobj))},
{"offset_obj_o_id",(uint64_t)(offsetof(struct obj,o_id))},
{"width_obj_o_id",(uint64_t)(sizeof(((struct obj*)0)->o_id))},
{"offset_obj_ox",(uint64_t)(offsetof(struct obj,ox))},
{"width_obj_ox",(uint64_t)(sizeof(((struct obj*)0)->ox))},
{"offset_obj_oy",(uint64_t)(offsetof(struct obj,oy))},
{"width_obj_oy",(uint64_t)(sizeof(((struct obj*)0)->oy))},
{"offset_obj_otyp",(uint64_t)(offsetof(struct obj,otyp))},
{"width_obj_otyp",(uint64_t)(sizeof(((struct obj*)0)->otyp))},
{"offset_obj_owt",(uint64_t)(offsetof(struct obj,owt))},
{"width_obj_owt",(uint64_t)(sizeof(((struct obj*)0)->owt))},
{"offset_obj_quan",(uint64_t)(offsetof(struct obj,quan))},
{"width_obj_quan",(uint64_t)(sizeof(((struct obj*)0)->quan))},
{"offset_obj_spe",(uint64_t)(offsetof(struct obj,spe))},
{"width_obj_spe",(uint64_t)(sizeof(((struct obj*)0)->spe))},
{"offset_obj_oclass",(uint64_t)(offsetof(struct obj,oclass))},
{"width_obj_oclass",(uint64_t)(sizeof(((struct obj*)0)->oclass))},
{"offset_obj_invlet",(uint64_t)(offsetof(struct obj,invlet))},
{"width_obj_invlet",(uint64_t)(sizeof(((struct obj*)0)->invlet))},
{"offset_obj_oartifact",(uint64_t)(offsetof(struct obj,oartifact))},
{"width_obj_oartifact",(uint64_t)(sizeof(((struct obj*)0)->oartifact))},
{"offset_obj_where",(uint64_t)(offsetof(struct obj,where))},
{"width_obj_where",(uint64_t)(sizeof(((struct obj*)0)->where))},
{"offset_obj_timed",(uint64_t)(offsetof(struct obj,timed))},
{"width_obj_timed",(uint64_t)(sizeof(((struct obj*)0)->timed))},
{"offset_obj_corpsenm",(uint64_t)(offsetof(struct obj,corpsenm))},
{"width_obj_corpsenm",(uint64_t)(sizeof(((struct obj*)0)->corpsenm))},
{"offset_obj_usecount",(uint64_t)(offsetof(struct obj,usecount))},
{"width_obj_usecount",(uint64_t)(sizeof(((struct obj*)0)->usecount))},
{"offset_obj_oeaten",(uint64_t)(offsetof(struct obj,oeaten))},
{"width_obj_oeaten",(uint64_t)(sizeof(((struct obj*)0)->oeaten))},
{"offset_obj_age",(uint64_t)(offsetof(struct obj,age))},
{"width_obj_age",(uint64_t)(sizeof(((struct obj*)0)->age))},
{"offset_obj_owornmask",(uint64_t)(offsetof(struct obj,owornmask))},
{"width_obj_owornmask",(uint64_t)(sizeof(((struct obj*)0)->owornmask))},
{"offset_obj_lua_ref_cnt",(uint64_t)(offsetof(struct obj,lua_ref_cnt))},
{"width_obj_lua_ref_cnt",(uint64_t)(sizeof(((struct obj*)0)->lua_ref_cnt))},
{"offset_obj_omigr_from_dnum",(uint64_t)(offsetof(struct obj,omigr_from_dnum))},
{"width_obj_omigr_from_dnum",(uint64_t)(sizeof(((struct obj*)0)->omigr_from_dnum))},
{"offset_obj_omigr_from_dlevel",(uint64_t)(offsetof(struct obj,omigr_from_dlevel))},
{"width_obj_omigr_from_dlevel",(uint64_t)(sizeof(((struct obj*)0)->omigr_from_dlevel))},
{"offset_obj_oextra",(uint64_t)(offsetof(struct obj,oextra))},
{"width_obj_oextra",(uint64_t)(sizeof(((struct obj*)0)->oextra))},
{"size_obj_split",(uint64_t)(sizeof(struct obj_split))},
{"align_obj_split",(uint64_t)(__alignof__(struct obj_split))},
{"offset_obj_split_parent_oid",(uint64_t)(offsetof(struct obj_split,parent_oid))},
{"width_obj_split_parent_oid",(uint64_t)(sizeof(((struct obj_split*)0)->parent_oid))},
{"offset_obj_split_child_oid",(uint64_t)(offsetof(struct obj_split,child_oid))},
{"width_obj_split_child_oid",(uint64_t)(sizeof(((struct obj_split*)0)->child_oid))},
{"size_polearm_info",(uint64_t)(sizeof(struct polearm_info))},
{"align_polearm_info",(uint64_t)(__alignof__(struct polearm_info))},
{"offset_polearm_info_hitmon",(uint64_t)(offsetof(struct polearm_info,hitmon))},
{"width_polearm_info_hitmon",(uint64_t)(sizeof(((struct polearm_info*)0)->hitmon))},
{"offset_polearm_info_m_id",(uint64_t)(offsetof(struct polearm_info,m_id))},
{"width_polearm_info_m_id",(uint64_t)(sizeof(((struct polearm_info*)0)->m_id))},
{"size_prop",(uint64_t)(sizeof(struct prop))},
{"align_prop",(uint64_t)(__alignof__(struct prop))},
{"offset_prop_extrinsic",(uint64_t)(offsetof(struct prop,extrinsic))},
{"width_prop_extrinsic",(uint64_t)(sizeof(((struct prop*)0)->extrinsic))},
{"offset_prop_blocked",(uint64_t)(offsetof(struct prop,blocked))},
{"width_prop_blocked",(uint64_t)(sizeof(((struct prop*)0)->blocked))},
{"offset_prop_intrinsic",(uint64_t)(offsetof(struct prop,intrinsic))},
{"width_prop_intrinsic",(uint64_t)(sizeof(((struct prop*)0)->intrinsic))},
{"size_q_score",(uint64_t)(sizeof(struct q_score))},
{"align_q_score",(uint64_t)(__alignof__(struct q_score))},
{"offset_q_score_leader_m_id",(uint64_t)(offsetof(struct q_score,leader_m_id))},
{"width_q_score_leader_m_id",(uint64_t)(sizeof(((struct q_score*)0)->leader_m_id))},
{"size_repo",(uint64_t)(sizeof(struct repo))},
{"align_repo",(uint64_t)(__alignof__(struct repo))},
{"offset_repo_shopkeeper",(uint64_t)(offsetof(struct repo,shopkeeper))},
{"width_repo_shopkeeper",(uint64_t)(sizeof(((struct repo*)0)->shopkeeper))},
{"offset_repo_location",(uint64_t)(offsetof(struct repo,location))},
{"width_repo_location",(uint64_t)(sizeof(((struct repo*)0)->location))},
{"size_rm",(uint64_t)(sizeof(struct rm))},
{"align_rm",(uint64_t)(__alignof__(struct rm))},
{"offset_rm_glyph",(uint64_t)(offsetof(struct rm,glyph))},
{"width_rm_glyph",(uint64_t)(sizeof(((struct rm*)0)->glyph))},
{"offset_rm_typ",(uint64_t)(offsetof(struct rm,typ))},
{"width_rm_typ",(uint64_t)(sizeof(((struct rm*)0)->typ))},
{"offset_rm_seenv",(uint64_t)(offsetof(struct rm,seenv))},
{"width_rm_seenv",(uint64_t)(sizeof(((struct rm*)0)->seenv))},
{"size_rogueroom",(uint64_t)(sizeof(struct rogueroom))},
{"align_rogueroom",(uint64_t)(__alignof__(struct rogueroom))},
{"offset_rogueroom_rlx",(uint64_t)(offsetof(struct rogueroom,rlx))},
{"width_rogueroom_rlx",(uint64_t)(sizeof(((struct rogueroom*)0)->rlx))},
{"offset_rogueroom_rly",(uint64_t)(offsetof(struct rogueroom,rly))},
{"width_rogueroom_rly",(uint64_t)(sizeof(((struct rogueroom*)0)->rly))},
{"offset_rogueroom_dx",(uint64_t)(offsetof(struct rogueroom,dx))},
{"width_rogueroom_dx",(uint64_t)(sizeof(((struct rogueroom*)0)->dx))},
{"offset_rogueroom_dy",(uint64_t)(offsetof(struct rogueroom,dy))},
{"width_rogueroom_dy",(uint64_t)(sizeof(((struct rogueroom*)0)->dy))},
{"offset_rogueroom_real",(uint64_t)(offsetof(struct rogueroom,real))},
{"width_rogueroom_real",(uint64_t)(sizeof(((struct rogueroom*)0)->real))},
{"offset_rogueroom_doortable",(uint64_t)(offsetof(struct rogueroom,doortable))},
{"width_rogueroom_doortable",(uint64_t)(sizeof(((struct rogueroom*)0)->doortable))},
{"offset_rogueroom_nroom",(uint64_t)(offsetof(struct rogueroom,nroom))},
{"width_rogueroom_nroom",(uint64_t)(sizeof(((struct rogueroom*)0)->nroom))},
{"size_role_filter",(uint64_t)(sizeof(struct role_filter))},
{"align_role_filter",(uint64_t)(__alignof__(struct role_filter))},
{"offset_role_filter_roles",(uint64_t)(offsetof(struct role_filter,roles))},
{"width_role_filter_roles",(uint64_t)(sizeof(((struct role_filter*)0)->roles))},
{"offset_role_filter_mask",(uint64_t)(offsetof(struct role_filter,mask))},
{"width_role_filter_mask",(uint64_t)(sizeof(((struct role_filter*)0)->mask))},
{"size_sinfo",(uint64_t)(sizeof(struct sinfo))},
{"align_sinfo",(uint64_t)(__alignof__(struct sinfo))},
{"offset_sinfo_gameover",(uint64_t)(offsetof(struct sinfo,gameover))},
{"width_sinfo_gameover",(uint64_t)(sizeof(((struct sinfo*)0)->gameover))},
{"offset_sinfo_stopprint",(uint64_t)(offsetof(struct sinfo,stopprint))},
{"width_sinfo_stopprint",(uint64_t)(sizeof(((struct sinfo*)0)->stopprint))},
{"offset_sinfo_done_hup",(uint64_t)(offsetof(struct sinfo,done_hup))},
{"width_sinfo_done_hup",(uint64_t)(sizeof(((struct sinfo*)0)->done_hup))},
{"offset_sinfo_preserve_locks",(uint64_t)(offsetof(struct sinfo,preserve_locks))},
{"width_sinfo_preserve_locks",(uint64_t)(sizeof(((struct sinfo*)0)->preserve_locks))},
{"offset_sinfo_something_worth_saving",(uint64_t)(offsetof(struct sinfo,something_worth_saving))},
{"width_sinfo_something_worth_saving",(uint64_t)(sizeof(((struct sinfo*)0)->something_worth_saving))},
{"offset_sinfo_panicking",(uint64_t)(offsetof(struct sinfo,panicking))},
{"width_sinfo_panicking",(uint64_t)(sizeof(((struct sinfo*)0)->panicking))},
{"offset_sinfo_exiting",(uint64_t)(offsetof(struct sinfo,exiting))},
{"width_sinfo_exiting",(uint64_t)(sizeof(((struct sinfo*)0)->exiting))},
{"offset_sinfo_saving",(uint64_t)(offsetof(struct sinfo,saving))},
{"width_sinfo_saving",(uint64_t)(sizeof(((struct sinfo*)0)->saving))},
{"offset_sinfo_restoring",(uint64_t)(offsetof(struct sinfo,restoring))},
{"width_sinfo_restoring",(uint64_t)(sizeof(((struct sinfo*)0)->restoring))},
{"offset_sinfo_freeingdata",(uint64_t)(offsetof(struct sinfo,freeingdata))},
{"width_sinfo_freeingdata",(uint64_t)(sizeof(((struct sinfo*)0)->freeingdata))},
{"offset_sinfo_in_getlev",(uint64_t)(offsetof(struct sinfo,in_getlev))},
{"width_sinfo_in_getlev",(uint64_t)(sizeof(((struct sinfo*)0)->in_getlev))},
{"offset_sinfo_in_moveloop",(uint64_t)(offsetof(struct sinfo,in_moveloop))},
{"width_sinfo_in_moveloop",(uint64_t)(sizeof(((struct sinfo*)0)->in_moveloop))},
{"offset_sinfo_in_impossible",(uint64_t)(offsetof(struct sinfo,in_impossible))},
{"width_sinfo_in_impossible",(uint64_t)(sizeof(((struct sinfo*)0)->in_impossible))},
{"offset_sinfo_in_docrt",(uint64_t)(offsetof(struct sinfo,in_docrt))},
{"width_sinfo_in_docrt",(uint64_t)(sizeof(((struct sinfo*)0)->in_docrt))},
{"offset_sinfo_in_self_recover",(uint64_t)(offsetof(struct sinfo,in_self_recover))},
{"width_sinfo_in_self_recover",(uint64_t)(sizeof(((struct sinfo*)0)->in_self_recover))},
{"offset_sinfo_in_checkpoint",(uint64_t)(offsetof(struct sinfo,in_checkpoint))},
{"width_sinfo_in_checkpoint",(uint64_t)(sizeof(((struct sinfo*)0)->in_checkpoint))},
{"offset_sinfo_in_parseoptions",(uint64_t)(offsetof(struct sinfo,in_parseoptions))},
{"width_sinfo_in_parseoptions",(uint64_t)(sizeof(((struct sinfo*)0)->in_parseoptions))},
{"offset_sinfo_in_role_selection",(uint64_t)(offsetof(struct sinfo,in_role_selection))},
{"width_sinfo_in_role_selection",(uint64_t)(sizeof(((struct sinfo*)0)->in_role_selection))},
{"offset_sinfo_in_getlin",(uint64_t)(offsetof(struct sinfo,in_getlin))},
{"width_sinfo_in_getlin",(uint64_t)(sizeof(((struct sinfo*)0)->in_getlin))},
{"offset_sinfo_in_sanity_check",(uint64_t)(offsetof(struct sinfo,in_sanity_check))},
{"width_sinfo_in_sanity_check",(uint64_t)(sizeof(((struct sinfo*)0)->in_sanity_check))},
{"offset_sinfo_config_error_ready",(uint64_t)(offsetof(struct sinfo,config_error_ready))},
{"width_sinfo_config_error_ready",(uint64_t)(sizeof(((struct sinfo*)0)->config_error_ready))},
{"offset_sinfo_beyond_savefile_load",(uint64_t)(offsetof(struct sinfo,beyond_savefile_load))},
{"width_sinfo_beyond_savefile_load",(uint64_t)(sizeof(((struct sinfo*)0)->beyond_savefile_load))},
{"offset_sinfo_savefile_completed",(uint64_t)(offsetof(struct sinfo,savefile_completed))},
{"width_sinfo_savefile_completed",(uint64_t)(sizeof(((struct sinfo*)0)->savefile_completed))},
{"offset_sinfo_reading_bonesfile",(uint64_t)(offsetof(struct sinfo,reading_bonesfile))},
{"width_sinfo_reading_bonesfile",(uint64_t)(sizeof(((struct sinfo*)0)->reading_bonesfile))},
{"offset_sinfo_in_paniclog",(uint64_t)(offsetof(struct sinfo,in_paniclog))},
{"width_sinfo_in_paniclog",(uint64_t)(sizeof(((struct sinfo*)0)->in_paniclog))},
{"offset_sinfo_wizkit_wishing",(uint64_t)(offsetof(struct sinfo,wizkit_wishing))},
{"width_sinfo_wizkit_wishing",(uint64_t)(sizeof(((struct sinfo*)0)->wizkit_wishing))},
{"offset_sinfo_input_state",(uint64_t)(offsetof(struct sinfo,input_state))},
{"width_sinfo_input_state",(uint64_t)(sizeof(((struct sinfo*)0)->input_state))},
{"offset_sinfo_early_options",(uint64_t)(offsetof(struct sinfo,early_options))},
{"width_sinfo_early_options",(uint64_t)(sizeof(((struct sinfo*)0)->early_options))},
{"offset_sinfo_resize_pending",(uint64_t)(offsetof(struct sinfo,resize_pending))},
{"width_sinfo_resize_pending",(uint64_t)(sizeof(((struct sinfo*)0)->resize_pending))},
{"offset_sinfo_getting_char",(uint64_t)(offsetof(struct sinfo,getting_char))},
{"width_sinfo_getting_char",(uint64_t)(sizeof(((struct sinfo*)0)->getting_char))},
{"size_skills",(uint64_t)(sizeof(struct skills))},
{"align_skills",(uint64_t)(__alignof__(struct skills))},
{"offset_skills_skill",(uint64_t)(offsetof(struct skills,skill))},
{"width_skills_skill",(uint64_t)(sizeof(((struct skills*)0)->skill))},
{"offset_skills_max_skill",(uint64_t)(offsetof(struct skills,max_skill))},
{"width_skills_max_skill",(uint64_t)(sizeof(((struct skills*)0)->max_skill))},
{"offset_skills_advance",(uint64_t)(offsetof(struct skills,advance))},
{"width_skills_advance",(uint64_t)(sizeof(((struct skills*)0)->advance))},
{"size_sound_voice",(uint64_t)(sizeof(struct sound_voice))},
{"align_sound_voice",(uint64_t)(__alignof__(struct sound_voice))},
{"offset_sound_voice_serialno",(uint64_t)(offsetof(struct sound_voice,serialno))},
{"width_sound_voice_serialno",(uint64_t)(sizeof(((struct sound_voice*)0)->serialno))},
{"offset_sound_voice_gender",(uint64_t)(offsetof(struct sound_voice,gender))},
{"width_sound_voice_gender",(uint64_t)(sizeof(((struct sound_voice*)0)->gender))},
{"offset_sound_voice_tone",(uint64_t)(offsetof(struct sound_voice,tone))},
{"width_sound_voice_tone",(uint64_t)(sizeof(((struct sound_voice*)0)->tone))},
{"offset_sound_voice_volume",(uint64_t)(offsetof(struct sound_voice,volume))},
{"width_sound_voice_volume",(uint64_t)(sizeof(((struct sound_voice*)0)->volume))},
{"offset_sound_voice_moreinfo",(uint64_t)(offsetof(struct sound_voice,moreinfo))},
{"width_sound_voice_moreinfo",(uint64_t)(sizeof(((struct sound_voice*)0)->moreinfo))},
{"offset_sound_voice_mon",(uint64_t)(offsetof(struct sound_voice,mon))},
{"width_sound_voice_mon",(uint64_t)(sizeof(((struct sound_voice*)0)->mon))},
{"offset_sound_voice_nameid",(uint64_t)(offsetof(struct sound_voice,nameid))},
{"width_sound_voice_nameid",(uint64_t)(sizeof(((struct sound_voice*)0)->nameid))},
{"size_spell",(uint64_t)(sizeof(struct spell))},
{"align_spell",(uint64_t)(__alignof__(struct spell))},
{"offset_spell_sp_id",(uint64_t)(offsetof(struct spell,sp_id))},
{"width_spell_sp_id",(uint64_t)(sizeof(((struct spell*)0)->sp_id))},
{"offset_spell_sp_lev",(uint64_t)(offsetof(struct spell,sp_lev))},
{"width_spell_sp_lev",(uint64_t)(sizeof(((struct spell*)0)->sp_lev))},
{"offset_spell_sp_know",(uint64_t)(offsetof(struct spell,sp_know))},
{"width_spell_sp_know",(uint64_t)(sizeof(((struct spell*)0)->sp_know))},
{"size_str_or_len",(uint64_t)(sizeof(union str_or_len))},
{"align_str_or_len",(uint64_t)(__alignof__(union str_or_len))},
{"offset_str_or_len_str",(uint64_t)(offsetof(union str_or_len,str))},
{"width_str_or_len_str",(uint64_t)(sizeof(((union str_or_len*)0)->str))},
{"offset_str_or_len_len",(uint64_t)(offsetof(union str_or_len,len))},
{"width_str_or_len_len",(uint64_t)(sizeof(((union str_or_len*)0)->len))},
{"size_symset_customization",(uint64_t)(sizeof(struct symset_customization))},
{"align_symset_customization",(uint64_t)(__alignof__(struct symset_customization))},
{"offset_symset_customization_customization_name",(uint64_t)(offsetof(struct symset_customization,customization_name))},
{"width_symset_customization_customization_name",(uint64_t)(sizeof(((struct symset_customization*)0)->customization_name))},
{"offset_symset_customization_count",(uint64_t)(offsetof(struct symset_customization,count))},
{"width_symset_customization_count",(uint64_t)(sizeof(((struct symset_customization*)0)->count))},
{"offset_symset_customization_custtype",(uint64_t)(offsetof(struct symset_customization,custtype))},
{"width_symset_customization_custtype",(uint64_t)(sizeof(((struct symset_customization*)0)->custtype))},
{"offset_symset_customization_details",(uint64_t)(offsetof(struct symset_customization,details))},
{"width_symset_customization_details",(uint64_t)(sizeof(((struct symset_customization*)0)->details))},
{"offset_symset_customization_details_end",(uint64_t)(offsetof(struct symset_customization,details_end))},
{"width_symset_customization_details_end",(uint64_t)(sizeof(((struct symset_customization*)0)->details_end))},
{"size_symsetentry",(uint64_t)(sizeof(struct symsetentry))},
{"align_symsetentry",(uint64_t)(__alignof__(struct symsetentry))},
{"offset_symsetentry_next",(uint64_t)(offsetof(struct symsetentry,next))},
{"width_symsetentry_next",(uint64_t)(sizeof(((struct symsetentry*)0)->next))},
{"offset_symsetentry_name",(uint64_t)(offsetof(struct symsetentry,name))},
{"width_symsetentry_name",(uint64_t)(sizeof(((struct symsetentry*)0)->name))},
{"offset_symsetentry_desc",(uint64_t)(offsetof(struct symsetentry,desc))},
{"width_symsetentry_desc",(uint64_t)(sizeof(((struct symsetentry*)0)->desc))},
{"offset_symsetentry_idx",(uint64_t)(offsetof(struct symsetentry,idx))},
{"width_symsetentry_idx",(uint64_t)(sizeof(((struct symsetentry*)0)->idx))},
{"offset_symsetentry_handling",(uint64_t)(offsetof(struct symsetentry,handling))},
{"width_symsetentry_handling",(uint64_t)(sizeof(((struct symsetentry*)0)->handling))},
{"size_takeoff_info",(uint64_t)(sizeof(struct takeoff_info))},
{"align_takeoff_info",(uint64_t)(__alignof__(struct takeoff_info))},
{"offset_takeoff_info_mask",(uint64_t)(offsetof(struct takeoff_info,mask))},
{"width_takeoff_info_mask",(uint64_t)(sizeof(((struct takeoff_info*)0)->mask))},
{"offset_takeoff_info_what",(uint64_t)(offsetof(struct takeoff_info,what))},
{"width_takeoff_info_what",(uint64_t)(sizeof(((struct takeoff_info*)0)->what))},
{"offset_takeoff_info_delay",(uint64_t)(offsetof(struct takeoff_info,delay))},
{"width_takeoff_info_delay",(uint64_t)(sizeof(((struct takeoff_info*)0)->delay))},
{"offset_takeoff_info_cancelled_don",(uint64_t)(offsetof(struct takeoff_info,cancelled_don))},
{"width_takeoff_info_cancelled_don",(uint64_t)(sizeof(((struct takeoff_info*)0)->cancelled_don))},
{"offset_takeoff_info_disrobing",(uint64_t)(offsetof(struct takeoff_info,disrobing))},
{"width_takeoff_info_disrobing",(uint64_t)(sizeof(((struct takeoff_info*)0)->disrobing))},
{"size_tc_gbl_data",(uint64_t)(sizeof(struct tc_gbl_data))},
{"align_tc_gbl_data",(uint64_t)(__alignof__(struct tc_gbl_data))},
{"offset_tc_gbl_data_tc_AS",(uint64_t)(offsetof(struct tc_gbl_data,tc_AS))},
{"width_tc_gbl_data_tc_AS",(uint64_t)(sizeof(((struct tc_gbl_data*)0)->tc_AS))},
{"offset_tc_gbl_data_tc_AE",(uint64_t)(offsetof(struct tc_gbl_data,tc_AE))},
{"width_tc_gbl_data_tc_AE",(uint64_t)(sizeof(((struct tc_gbl_data*)0)->tc_AE))},
{"offset_tc_gbl_data_tc_LI",(uint64_t)(offsetof(struct tc_gbl_data,tc_LI))},
{"width_tc_gbl_data_tc_LI",(uint64_t)(sizeof(((struct tc_gbl_data*)0)->tc_LI))},
{"offset_tc_gbl_data_tc_CO",(uint64_t)(offsetof(struct tc_gbl_data,tc_CO))},
{"width_tc_gbl_data_tc_CO",(uint64_t)(sizeof(((struct tc_gbl_data*)0)->tc_CO))},
{"size_tin_info",(uint64_t)(sizeof(struct tin_info))},
{"align_tin_info",(uint64_t)(__alignof__(struct tin_info))},
{"offset_tin_info_tin",(uint64_t)(offsetof(struct tin_info,tin))},
{"width_tin_info_tin",(uint64_t)(sizeof(((struct tin_info*)0)->tin))},
{"offset_tin_info_o_id",(uint64_t)(offsetof(struct tin_info,o_id))},
{"width_tin_info_o_id",(uint64_t)(sizeof(((struct tin_info*)0)->o_id))},
{"offset_tin_info_usedtime",(uint64_t)(offsetof(struct tin_info,usedtime))},
{"width_tin_info_usedtime",(uint64_t)(sizeof(((struct tin_info*)0)->usedtime))},
{"offset_tin_info_reqtime",(uint64_t)(offsetof(struct tin_info,reqtime))},
{"width_tin_info_reqtime",(uint64_t)(sizeof(((struct tin_info*)0)->reqtime))},
{"size_trapinfo",(uint64_t)(sizeof(struct trapinfo))},
{"align_trapinfo",(uint64_t)(__alignof__(struct trapinfo))},
{"offset_trapinfo_tobj",(uint64_t)(offsetof(struct trapinfo,tobj))},
{"width_trapinfo_tobj",(uint64_t)(sizeof(((struct trapinfo*)0)->tobj))},
{"offset_trapinfo_tx",(uint64_t)(offsetof(struct trapinfo,tx))},
{"width_trapinfo_tx",(uint64_t)(sizeof(((struct trapinfo*)0)->tx))},
{"offset_trapinfo_ty",(uint64_t)(offsetof(struct trapinfo,ty))},
{"width_trapinfo_ty",(uint64_t)(sizeof(((struct trapinfo*)0)->ty))},
{"offset_trapinfo_time_needed",(uint64_t)(offsetof(struct trapinfo,time_needed))},
{"width_trapinfo_time_needed",(uint64_t)(sizeof(((struct trapinfo*)0)->time_needed))},
{"offset_trapinfo_force_bungle",(uint64_t)(offsetof(struct trapinfo,force_bungle))},
{"width_trapinfo_force_bungle",(uint64_t)(sizeof(((struct trapinfo*)0)->force_bungle))},
{"size_tribute_info",(uint64_t)(sizeof(struct tribute_info))},
{"align_tribute_info",(uint64_t)(__alignof__(struct tribute_info))},
{"offset_tribute_info_tributesz",(uint64_t)(offsetof(struct tribute_info,tributesz))},
{"width_tribute_info_tributesz",(uint64_t)(sizeof(((struct tribute_info*)0)->tributesz))},
{"offset_tribute_info_enabled",(uint64_t)(offsetof(struct tribute_info,enabled))},
{"width_tribute_info_enabled",(uint64_t)(sizeof(((struct tribute_info*)0)->enabled))},
{"size_u_conduct",(uint64_t)(sizeof(struct u_conduct))},
{"align_u_conduct",(uint64_t)(__alignof__(struct u_conduct))},
{"offset_u_conduct_unvegetarian",(uint64_t)(offsetof(struct u_conduct,unvegetarian))},
{"width_u_conduct_unvegetarian",(uint64_t)(sizeof(((struct u_conduct*)0)->unvegetarian))},
{"offset_u_conduct_unvegan",(uint64_t)(offsetof(struct u_conduct,unvegan))},
{"width_u_conduct_unvegan",(uint64_t)(sizeof(((struct u_conduct*)0)->unvegan))},
{"offset_u_conduct_food",(uint64_t)(offsetof(struct u_conduct,food))},
{"width_u_conduct_food",(uint64_t)(sizeof(((struct u_conduct*)0)->food))},
{"offset_u_conduct_gnostic",(uint64_t)(offsetof(struct u_conduct,gnostic))},
{"width_u_conduct_gnostic",(uint64_t)(sizeof(((struct u_conduct*)0)->gnostic))},
{"offset_u_conduct_weaphit",(uint64_t)(offsetof(struct u_conduct,weaphit))},
{"width_u_conduct_weaphit",(uint64_t)(sizeof(((struct u_conduct*)0)->weaphit))},
{"offset_u_conduct_killer",(uint64_t)(offsetof(struct u_conduct,killer))},
{"width_u_conduct_killer",(uint64_t)(sizeof(((struct u_conduct*)0)->killer))},
{"offset_u_conduct_literate",(uint64_t)(offsetof(struct u_conduct,literate))},
{"width_u_conduct_literate",(uint64_t)(sizeof(((struct u_conduct*)0)->literate))},
{"offset_u_conduct_polypiles",(uint64_t)(offsetof(struct u_conduct,polypiles))},
{"width_u_conduct_polypiles",(uint64_t)(sizeof(((struct u_conduct*)0)->polypiles))},
{"offset_u_conduct_polyselfs",(uint64_t)(offsetof(struct u_conduct,polyselfs))},
{"width_u_conduct_polyselfs",(uint64_t)(sizeof(((struct u_conduct*)0)->polyselfs))},
{"offset_u_conduct_wishes",(uint64_t)(offsetof(struct u_conduct,wishes))},
{"width_u_conduct_wishes",(uint64_t)(sizeof(((struct u_conduct*)0)->wishes))},
{"offset_u_conduct_wisharti",(uint64_t)(offsetof(struct u_conduct,wisharti))},
{"width_u_conduct_wisharti",(uint64_t)(sizeof(((struct u_conduct*)0)->wisharti))},
{"offset_u_conduct_hf_reserved1",(uint64_t)(offsetof(struct u_conduct,hf_reserved1))},
{"width_u_conduct_hf_reserved1",(uint64_t)(sizeof(((struct u_conduct*)0)->hf_reserved1))},
{"offset_u_conduct_sokocheat",(uint64_t)(offsetof(struct u_conduct,sokocheat))},
{"width_u_conduct_sokocheat",(uint64_t)(sizeof(((struct u_conduct*)0)->sokocheat))},
{"offset_u_conduct_pets",(uint64_t)(offsetof(struct u_conduct,pets))},
{"width_u_conduct_pets",(uint64_t)(sizeof(((struct u_conduct*)0)->pets))},
{"offset_u_conduct_reserved1",(uint64_t)(offsetof(struct u_conduct,reserved1))},
{"width_u_conduct_reserved1",(uint64_t)(sizeof(((struct u_conduct*)0)->reserved1))},
{"offset_u_conduct_reserved2",(uint64_t)(offsetof(struct u_conduct,reserved2))},
{"width_u_conduct_reserved2",(uint64_t)(sizeof(((struct u_conduct*)0)->reserved2))},
{"offset_u_conduct_reserved3",(uint64_t)(offsetof(struct u_conduct,reserved3))},
{"width_u_conduct_reserved3",(uint64_t)(sizeof(((struct u_conduct*)0)->reserved3))},
{"offset_u_conduct_reserved4",(uint64_t)(offsetof(struct u_conduct,reserved4))},
{"width_u_conduct_reserved4",(uint64_t)(sizeof(((struct u_conduct*)0)->reserved4))},
{"size_u_event",(uint64_t)(sizeof(struct u_event))},
{"align_u_event",(uint64_t)(__alignof__(struct u_event))},
{"size_u_have",(uint64_t)(sizeof(struct u_have))},
{"align_u_have",(uint64_t)(__alignof__(struct u_have))},
{"size_u_realtime",(uint64_t)(sizeof(struct u_realtime))},
{"align_u_realtime",(uint64_t)(__alignof__(struct u_realtime))},
{"offset_u_realtime_realtime",(uint64_t)(offsetof(struct u_realtime,realtime))},
{"width_u_realtime_realtime",(uint64_t)(sizeof(((struct u_realtime*)0)->realtime))},
{"offset_u_realtime_start_timing",(uint64_t)(offsetof(struct u_realtime,start_timing))},
{"width_u_realtime_start_timing",(uint64_t)(sizeof(((struct u_realtime*)0)->start_timing))},
{"offset_u_realtime_finish_time",(uint64_t)(offsetof(struct u_realtime,finish_time))},
{"width_u_realtime_finish_time",(uint64_t)(sizeof(((struct u_realtime*)0)->finish_time))},
{"size_u_roleplay",(uint64_t)(sizeof(struct u_roleplay))},
{"align_u_roleplay",(uint64_t)(__alignof__(struct u_roleplay))},
{"offset_u_roleplay_blind",(uint64_t)(offsetof(struct u_roleplay,blind))},
{"width_u_roleplay_blind",(uint64_t)(sizeof(((struct u_roleplay*)0)->blind))},
{"offset_u_roleplay_nudist",(uint64_t)(offsetof(struct u_roleplay,nudist))},
{"width_u_roleplay_nudist",(uint64_t)(sizeof(((struct u_roleplay*)0)->nudist))},
{"offset_u_roleplay_deaf",(uint64_t)(offsetof(struct u_roleplay,deaf))},
{"width_u_roleplay_deaf",(uint64_t)(sizeof(((struct u_roleplay*)0)->deaf))},
{"offset_u_roleplay_pauper",(uint64_t)(offsetof(struct u_roleplay,pauper))},
{"width_u_roleplay_pauper",(uint64_t)(sizeof(((struct u_roleplay*)0)->pauper))},
{"offset_u_roleplay_reroll",(uint64_t)(offsetof(struct u_roleplay,reroll))},
{"width_u_roleplay_reroll",(uint64_t)(sizeof(((struct u_roleplay*)0)->reroll))},
{"offset_u_roleplay_reserved1",(uint64_t)(offsetof(struct u_roleplay,reserved1))},
{"width_u_roleplay_reserved1",(uint64_t)(sizeof(((struct u_roleplay*)0)->reserved1))},
{"offset_u_roleplay_reserved2",(uint64_t)(offsetof(struct u_roleplay,reserved2))},
{"width_u_roleplay_reserved2",(uint64_t)(sizeof(((struct u_roleplay*)0)->reserved2))},
{"offset_u_roleplay_reserved3",(uint64_t)(offsetof(struct u_roleplay,reserved3))},
{"width_u_roleplay_reserved3",(uint64_t)(sizeof(((struct u_roleplay*)0)->reserved3))},
{"offset_u_roleplay_numbones",(uint64_t)(offsetof(struct u_roleplay,numbones))},
{"width_u_roleplay_numbones",(uint64_t)(sizeof(((struct u_roleplay*)0)->numbones))},
{"offset_u_roleplay_numrerolls",(uint64_t)(offsetof(struct u_roleplay,numrerolls))},
{"width_u_roleplay_numrerolls",(uint64_t)(sizeof(((struct u_roleplay*)0)->numrerolls))},
{"size_val_list",(uint64_t)(sizeof(struct val_list))},
{"align_val_list",(uint64_t)(__alignof__(struct val_list))},
{"offset_val_list_list",(uint64_t)(offsetof(struct val_list,list))},
{"width_val_list_list",(uint64_t)(sizeof(((struct val_list*)0)->list))},
{"offset_val_list_size",(uint64_t)(offsetof(struct val_list,size))},
{"width_val_list_size",(uint64_t)(sizeof(((struct val_list*)0)->size))},
{"size_valuable_data",(uint64_t)(sizeof(struct valuable_data))},
{"align_valuable_data",(uint64_t)(__alignof__(struct valuable_data))},
{"offset_valuable_data_count",(uint64_t)(offsetof(struct valuable_data,count))},
{"width_valuable_data_count",(uint64_t)(sizeof(((struct valuable_data*)0)->count))},
{"offset_valuable_data_typ",(uint64_t)(offsetof(struct valuable_data,typ))},
{"width_valuable_data_typ",(uint64_t)(sizeof(((struct valuable_data*)0)->typ))},
{"size_victual_info",(uint64_t)(sizeof(struct victual_info))},
{"align_victual_info",(uint64_t)(__alignof__(struct victual_info))},
{"offset_victual_info_piece",(uint64_t)(offsetof(struct victual_info,piece))},
{"width_victual_info_piece",(uint64_t)(sizeof(((struct victual_info*)0)->piece))},
{"offset_victual_info_o_id",(uint64_t)(offsetof(struct victual_info,o_id))},
{"width_victual_info_o_id",(uint64_t)(sizeof(((struct victual_info*)0)->o_id))},
{"offset_victual_info_usedtime",(uint64_t)(offsetof(struct victual_info,usedtime))},
{"width_victual_info_usedtime",(uint64_t)(sizeof(((struct victual_info*)0)->usedtime))},
{"offset_victual_info_reqtime",(uint64_t)(offsetof(struct victual_info,reqtime))},
{"width_victual_info_reqtime",(uint64_t)(sizeof(((struct victual_info*)0)->reqtime))},
{"offset_victual_info_nmod",(uint64_t)(offsetof(struct victual_info,nmod))},
{"width_victual_info_nmod",(uint64_t)(sizeof(((struct victual_info*)0)->nmod))},
{"size_vptrs",(uint64_t)(sizeof(union vptrs))},
{"align_vptrs",(uint64_t)(__alignof__(union vptrs))},
{"offset_vptrs_v_nexthere",(uint64_t)(offsetof(union vptrs,v_nexthere))},
{"width_vptrs_v_nexthere",(uint64_t)(sizeof(((union vptrs*)0)->v_nexthere))},
{"offset_vptrs_v_ocontainer",(uint64_t)(offsetof(union vptrs,v_ocontainer))},
{"width_vptrs_v_ocontainer",(uint64_t)(sizeof(((union vptrs*)0)->v_ocontainer))},
{"offset_vptrs_v_ocarry",(uint64_t)(offsetof(union vptrs,v_ocarry))},
{"width_vptrs_v_ocarry",(uint64_t)(sizeof(((union vptrs*)0)->v_ocarry))},
{"size_warntype_info",(uint64_t)(sizeof(struct warntype_info))},
{"align_warntype_info",(uint64_t)(__alignof__(struct warntype_info))},
{"offset_warntype_info_obj",(uint64_t)(offsetof(struct warntype_info,obj))},
{"width_warntype_info_obj",(uint64_t)(sizeof(((struct warntype_info*)0)->obj))},
{"offset_warntype_info_polyd",(uint64_t)(offsetof(struct warntype_info,polyd))},
{"width_warntype_info_polyd",(uint64_t)(sizeof(((struct warntype_info*)0)->polyd))},
{"offset_warntype_info_species",(uint64_t)(offsetof(struct warntype_info,species))},
{"width_warntype_info_species",(uint64_t)(sizeof(((struct warntype_info*)0)->species))},
{"offset_warntype_info_speciesidx",(uint64_t)(offsetof(struct warntype_info,speciesidx))},
{"width_warntype_info_speciesidx",(uint64_t)(sizeof(((struct warntype_info*)0)->speciesidx))},
{"size_win_settings",(uint64_t)(sizeof(struct win_settings))},
{"align_win_settings",(uint64_t)(__alignof__(struct win_settings))},
{"offset_win_settings_wdmode",(uint64_t)(offsetof(struct win_settings,wdmode))},
{"width_win_settings_wdmode",(uint64_t)(sizeof(((struct win_settings*)0)->wdmode))},
{"offset_win_settings_map_frame_color",(uint64_t)(offsetof(struct win_settings,map_frame_color))},
{"width_win_settings_map_frame_color",(uint64_t)(sizeof(((struct win_settings*)0)->map_frame_color))},
{"size_windowcolors_struct",(uint64_t)(sizeof(struct windowcolors_struct))},
{"align_windowcolors_struct",(uint64_t)(__alignof__(struct windowcolors_struct))},
{"offset_windowcolors_struct_fg",(uint64_t)(offsetof(struct windowcolors_struct,fg))},
{"width_windowcolors_struct_fg",(uint64_t)(sizeof(((struct windowcolors_struct*)0)->fg))},
{"offset_windowcolors_struct_bg",(uint64_t)(offsetof(struct windowcolors_struct,bg))},
{"width_windowcolors_struct_bg",(uint64_t)(sizeof(((struct windowcolors_struct*)0)->bg))},
{"size_xlock_s",(uint64_t)(sizeof(struct xlock_s))},
{"align_xlock_s",(uint64_t)(__alignof__(struct xlock_s))},
{"offset_xlock_s_door",(uint64_t)(offsetof(struct xlock_s,door))},
{"width_xlock_s_door",(uint64_t)(sizeof(((struct xlock_s*)0)->door))},
{"offset_xlock_s_box",(uint64_t)(offsetof(struct xlock_s,box))},
{"width_xlock_s_box",(uint64_t)(sizeof(((struct xlock_s*)0)->box))},
{"offset_xlock_s_picktyp",(uint64_t)(offsetof(struct xlock_s,picktyp))},
{"width_xlock_s_picktyp",(uint64_t)(sizeof(((struct xlock_s*)0)->picktyp))},
{"offset_xlock_s_chance",(uint64_t)(offsetof(struct xlock_s,chance))},
{"width_xlock_s_chance",(uint64_t)(sizeof(((struct xlock_s*)0)->chance))},
{"offset_xlock_s_usedtime",(uint64_t)(offsetof(struct xlock_s,usedtime))},
{"width_xlock_s_usedtime",(uint64_t)(sizeof(((struct xlock_s*)0)->usedtime))},
{"offset_xlock_s_magic_key",(uint64_t)(offsetof(struct xlock_s,magic_key))},
{"width_xlock_s_magic_key",(uint64_t)(sizeof(((struct xlock_s*)0)->magic_key))},
{"size_you",(uint64_t)(sizeof(struct you))},
{"align_you",(uint64_t)(__alignof__(struct you))},
{"offset_you_ux",(uint64_t)(offsetof(struct you,ux))},
{"width_you_ux",(uint64_t)(sizeof(((struct you*)0)->ux))},
{"offset_you_uy",(uint64_t)(offsetof(struct you,uy))},
{"width_you_uy",(uint64_t)(sizeof(((struct you*)0)->uy))},
{"offset_you_dx",(uint64_t)(offsetof(struct you,dx))},
{"width_you_dx",(uint64_t)(sizeof(((struct you*)0)->dx))},
{"offset_you_dy",(uint64_t)(offsetof(struct you,dy))},
{"width_you_dy",(uint64_t)(sizeof(((struct you*)0)->dy))},
{"offset_you_dz",(uint64_t)(offsetof(struct you,dz))},
{"width_you_dz",(uint64_t)(sizeof(((struct you*)0)->dz))},
{"offset_you_tx",(uint64_t)(offsetof(struct you,tx))},
{"width_you_tx",(uint64_t)(sizeof(((struct you*)0)->tx))},
{"offset_you_ty",(uint64_t)(offsetof(struct you,ty))},
{"width_you_ty",(uint64_t)(sizeof(((struct you*)0)->ty))},
{"offset_you_ux0",(uint64_t)(offsetof(struct you,ux0))},
{"width_you_ux0",(uint64_t)(sizeof(((struct you*)0)->ux0))},
{"offset_you_uy0",(uint64_t)(offsetof(struct you,uy0))},
{"width_you_uy0",(uint64_t)(sizeof(((struct you*)0)->uy0))},
{"offset_you_uz",(uint64_t)(offsetof(struct you,uz))},
{"width_you_uz",(uint64_t)(sizeof(((struct you*)0)->uz))},
{"offset_you_uz0",(uint64_t)(offsetof(struct you,uz0))},
{"width_you_uz0",(uint64_t)(sizeof(((struct you*)0)->uz0))},
{"offset_you_utolev",(uint64_t)(offsetof(struct you,utolev))},
{"width_you_utolev",(uint64_t)(sizeof(((struct you*)0)->utolev))},
{"offset_you_utotype",(uint64_t)(offsetof(struct you,utotype))},
{"width_you_utotype",(uint64_t)(sizeof(((struct you*)0)->utotype))},
{"offset_you_ucamefrom",(uint64_t)(offsetof(struct you,ucamefrom))},
{"width_you_ucamefrom",(uint64_t)(sizeof(((struct you*)0)->ucamefrom))},
{"offset_you_umoved",(uint64_t)(offsetof(struct you,umoved))},
{"width_you_umoved",(uint64_t)(sizeof(((struct you*)0)->umoved))},
{"offset_you_last_str_turn",(uint64_t)(offsetof(struct you,last_str_turn))},
{"width_you_last_str_turn",(uint64_t)(sizeof(((struct you*)0)->last_str_turn))},
{"offset_you_ulevel",(uint64_t)(offsetof(struct you,ulevel))},
{"width_you_ulevel",(uint64_t)(sizeof(((struct you*)0)->ulevel))},
{"offset_you_ulevelmax",(uint64_t)(offsetof(struct you,ulevelmax))},
{"width_you_ulevelmax",(uint64_t)(sizeof(((struct you*)0)->ulevelmax))},
{"offset_you_ulevelpeak",(uint64_t)(offsetof(struct you,ulevelpeak))},
{"width_you_ulevelpeak",(uint64_t)(sizeof(((struct you*)0)->ulevelpeak))},
{"offset_you_utrap",(uint64_t)(offsetof(struct you,utrap))},
{"width_you_utrap",(uint64_t)(sizeof(((struct you*)0)->utrap))},
{"offset_you_utraptype",(uint64_t)(offsetof(struct you,utraptype))},
{"width_you_utraptype",(uint64_t)(sizeof(((struct you*)0)->utraptype))},
{"offset_you_urooms",(uint64_t)(offsetof(struct you,urooms))},
{"width_you_urooms",(uint64_t)(sizeof(((struct you*)0)->urooms))},
{"offset_you_urooms0",(uint64_t)(offsetof(struct you,urooms0))},
{"width_you_urooms0",(uint64_t)(sizeof(((struct you*)0)->urooms0))},
{"offset_you_uentered",(uint64_t)(offsetof(struct you,uentered))},
{"width_you_uentered",(uint64_t)(sizeof(((struct you*)0)->uentered))},
{"offset_you_ushops",(uint64_t)(offsetof(struct you,ushops))},
{"width_you_ushops",(uint64_t)(sizeof(((struct you*)0)->ushops))},
{"offset_you_ushops0",(uint64_t)(offsetof(struct you,ushops0))},
{"width_you_ushops0",(uint64_t)(sizeof(((struct you*)0)->ushops0))},
{"offset_you_ushops_entered",(uint64_t)(offsetof(struct you,ushops_entered))},
{"width_you_ushops_entered",(uint64_t)(sizeof(((struct you*)0)->ushops_entered))},
{"offset_you_ushops_left",(uint64_t)(offsetof(struct you,ushops_left))},
{"width_you_ushops_left",(uint64_t)(sizeof(((struct you*)0)->ushops_left))},
{"offset_you_uhunger",(uint64_t)(offsetof(struct you,uhunger))},
{"width_you_uhunger",(uint64_t)(sizeof(((struct you*)0)->uhunger))},
{"offset_you_uhs",(uint64_t)(offsetof(struct you,uhs))},
{"width_you_uhs",(uint64_t)(sizeof(((struct you*)0)->uhs))},
{"offset_you_uprops",(uint64_t)(offsetof(struct you,uprops))},
{"width_you_uprops",(uint64_t)(sizeof(((struct you*)0)->uprops))},
{"offset_you_umconf",(uint64_t)(offsetof(struct you,umconf))},
{"width_you_umconf",(uint64_t)(sizeof(((struct you*)0)->umconf))},
{"offset_you_nv_range",(uint64_t)(offsetof(struct you,nv_range))},
{"width_you_nv_range",(uint64_t)(sizeof(((struct you*)0)->nv_range))},
{"offset_you_xray_range",(uint64_t)(offsetof(struct you,xray_range))},
{"width_you_xray_range",(uint64_t)(sizeof(((struct you*)0)->xray_range))},
{"offset_you_unblind_telepat_range",(uint64_t)(offsetof(struct you,unblind_telepat_range))},
{"width_you_unblind_telepat_range",(uint64_t)(sizeof(((struct you*)0)->unblind_telepat_range))},
{"offset_you_bglyph",(uint64_t)(offsetof(struct you,bglyph))},
{"width_you_bglyph",(uint64_t)(sizeof(((struct you*)0)->bglyph))},
{"offset_you_cglyph",(uint64_t)(offsetof(struct you,cglyph))},
{"width_you_cglyph",(uint64_t)(sizeof(((struct you*)0)->cglyph))},
{"offset_you_bc_order",(uint64_t)(offsetof(struct you,bc_order))},
{"width_you_bc_order",(uint64_t)(sizeof(((struct you*)0)->bc_order))},
{"offset_you_bc_felt",(uint64_t)(offsetof(struct you,bc_felt))},
{"width_you_bc_felt",(uint64_t)(sizeof(((struct you*)0)->bc_felt))},
{"offset_you_umonster",(uint64_t)(offsetof(struct you,umonster))},
{"width_you_umonster",(uint64_t)(sizeof(((struct you*)0)->umonster))},
{"offset_you_umonnum",(uint64_t)(offsetof(struct you,umonnum))},
{"width_you_umonnum",(uint64_t)(sizeof(((struct you*)0)->umonnum))},
{"offset_you_mh",(uint64_t)(offsetof(struct you,mh))},
{"width_you_mh",(uint64_t)(sizeof(((struct you*)0)->mh))},
{"offset_you_mhmax",(uint64_t)(offsetof(struct you,mhmax))},
{"width_you_mhmax",(uint64_t)(sizeof(((struct you*)0)->mhmax))},
{"offset_you_mtimedone",(uint64_t)(offsetof(struct you,mtimedone))},
{"width_you_mtimedone",(uint64_t)(sizeof(((struct you*)0)->mtimedone))},
{"offset_you_macurr",(uint64_t)(offsetof(struct you,macurr))},
{"width_you_macurr",(uint64_t)(sizeof(((struct you*)0)->macurr))},
{"offset_you_mamax",(uint64_t)(offsetof(struct you,mamax))},
{"width_you_mamax",(uint64_t)(sizeof(((struct you*)0)->mamax))},
{"offset_you_ulycn",(uint64_t)(offsetof(struct you,ulycn))},
{"width_you_ulycn",(uint64_t)(sizeof(((struct you*)0)->ulycn))},
{"offset_you_ucreamed",(uint64_t)(offsetof(struct you,ucreamed))},
{"width_you_ucreamed",(uint64_t)(sizeof(((struct you*)0)->ucreamed))},
{"offset_you_uswldtim",(uint64_t)(offsetof(struct you,uswldtim))},
{"width_you_uswldtim",(uint64_t)(sizeof(((struct you*)0)->uswldtim))},
{"offset_you_udg_cnt",(uint64_t)(offsetof(struct you,udg_cnt))},
{"width_you_udg_cnt",(uint64_t)(sizeof(((struct you*)0)->udg_cnt))},
{"offset_you_uevent",(uint64_t)(offsetof(struct you,uevent))},
{"width_you_uevent",(uint64_t)(sizeof(((struct you*)0)->uevent))},
{"offset_you_uhave",(uint64_t)(offsetof(struct you,uhave))},
{"width_you_uhave",(uint64_t)(sizeof(((struct you*)0)->uhave))},
{"offset_you_uconduct",(uint64_t)(offsetof(struct you,uconduct))},
{"width_you_uconduct",(uint64_t)(sizeof(((struct you*)0)->uconduct))},
{"offset_you_uroleplay",(uint64_t)(offsetof(struct you,uroleplay))},
{"width_you_uroleplay",(uint64_t)(sizeof(((struct you*)0)->uroleplay))},
{"offset_you_acurr",(uint64_t)(offsetof(struct you,acurr))},
{"width_you_acurr",(uint64_t)(sizeof(((struct you*)0)->acurr))},
{"offset_you_aexe",(uint64_t)(offsetof(struct you,aexe))},
{"width_you_aexe",(uint64_t)(sizeof(((struct you*)0)->aexe))},
{"offset_you_abon",(uint64_t)(offsetof(struct you,abon))},
{"width_you_abon",(uint64_t)(sizeof(((struct you*)0)->abon))},
{"offset_you_amax",(uint64_t)(offsetof(struct you,amax))},
{"width_you_amax",(uint64_t)(sizeof(((struct you*)0)->amax))},
{"offset_you_atemp",(uint64_t)(offsetof(struct you,atemp))},
{"width_you_atemp",(uint64_t)(sizeof(((struct you*)0)->atemp))},
{"offset_you_atime",(uint64_t)(offsetof(struct you,atime))},
{"width_you_atime",(uint64_t)(sizeof(((struct you*)0)->atime))},
{"offset_you_ualign",(uint64_t)(offsetof(struct you,ualign))},
{"width_you_ualign",(uint64_t)(sizeof(((struct you*)0)->ualign))},
{"offset_you_ualignbase",(uint64_t)(offsetof(struct you,ualignbase))},
{"width_you_ualignbase",(uint64_t)(sizeof(((struct you*)0)->ualignbase))},
{"offset_you_uluck",(uint64_t)(offsetof(struct you,uluck))},
{"width_you_uluck",(uint64_t)(sizeof(((struct you*)0)->uluck))},
{"offset_you_moreluck",(uint64_t)(offsetof(struct you,moreluck))},
{"width_you_moreluck",(uint64_t)(sizeof(((struct you*)0)->moreluck))},
{"offset_you_uhitinc",(uint64_t)(offsetof(struct you,uhitinc))},
{"width_you_uhitinc",(uint64_t)(sizeof(((struct you*)0)->uhitinc))},
{"offset_you_udaminc",(uint64_t)(offsetof(struct you,udaminc))},
{"width_you_udaminc",(uint64_t)(sizeof(((struct you*)0)->udaminc))},
{"offset_you_uac",(uint64_t)(offsetof(struct you,uac))},
{"width_you_uac",(uint64_t)(sizeof(((struct you*)0)->uac))},
{"offset_you_uspellprot",(uint64_t)(offsetof(struct you,uspellprot))},
{"width_you_uspellprot",(uint64_t)(sizeof(((struct you*)0)->uspellprot))},
{"offset_you_usptime",(uint64_t)(offsetof(struct you,usptime))},
{"width_you_usptime",(uint64_t)(sizeof(((struct you*)0)->usptime))},
{"offset_you_uspmtime",(uint64_t)(offsetof(struct you,uspmtime))},
{"width_you_uspmtime",(uint64_t)(sizeof(((struct you*)0)->uspmtime))},
{"offset_you_uhp",(uint64_t)(offsetof(struct you,uhp))},
{"width_you_uhp",(uint64_t)(sizeof(((struct you*)0)->uhp))},
{"offset_you_uhpmax",(uint64_t)(offsetof(struct you,uhpmax))},
{"width_you_uhpmax",(uint64_t)(sizeof(((struct you*)0)->uhpmax))},
{"offset_you_uhppeak",(uint64_t)(offsetof(struct you,uhppeak))},
{"width_you_uhppeak",(uint64_t)(sizeof(((struct you*)0)->uhppeak))},
{"offset_you_uen",(uint64_t)(offsetof(struct you,uen))},
{"width_you_uen",(uint64_t)(sizeof(((struct you*)0)->uen))},
{"offset_you_uenmax",(uint64_t)(offsetof(struct you,uenmax))},
{"width_you_uenmax",(uint64_t)(sizeof(((struct you*)0)->uenmax))},
{"offset_you_uenpeak",(uint64_t)(offsetof(struct you,uenpeak))},
{"width_you_uenpeak",(uint64_t)(sizeof(((struct you*)0)->uenpeak))},
{"offset_you_uhpinc",(uint64_t)(offsetof(struct you,uhpinc))},
{"width_you_uhpinc",(uint64_t)(sizeof(((struct you*)0)->uhpinc))},
{"offset_you_ueninc",(uint64_t)(offsetof(struct you,ueninc))},
{"width_you_ueninc",(uint64_t)(sizeof(((struct you*)0)->ueninc))},
{"offset_you_ugangr",(uint64_t)(offsetof(struct you,ugangr))},
{"width_you_ugangr",(uint64_t)(sizeof(((struct you*)0)->ugangr))},
{"offset_you_ugifts",(uint64_t)(offsetof(struct you,ugifts))},
{"width_you_ugifts",(uint64_t)(sizeof(((struct you*)0)->ugifts))},
{"offset_you_ublessed",(uint64_t)(offsetof(struct you,ublessed))},
{"width_you_ublessed",(uint64_t)(sizeof(((struct you*)0)->ublessed))},
{"offset_you_ublesscnt",(uint64_t)(offsetof(struct you,ublesscnt))},
{"width_you_ublesscnt",(uint64_t)(sizeof(((struct you*)0)->ublesscnt))},
{"offset_you_umoney0",(uint64_t)(offsetof(struct you,umoney0))},
{"width_you_umoney0",(uint64_t)(sizeof(((struct you*)0)->umoney0))},
{"offset_you_uspare1",(uint64_t)(offsetof(struct you,uspare1))},
{"width_you_uspare1",(uint64_t)(sizeof(((struct you*)0)->uspare1))},
{"offset_you_uexp",(uint64_t)(offsetof(struct you,uexp))},
{"width_you_uexp",(uint64_t)(sizeof(((struct you*)0)->uexp))},
{"offset_you_urexp",(uint64_t)(offsetof(struct you,urexp))},
{"width_you_urexp",(uint64_t)(sizeof(((struct you*)0)->urexp))},
{"offset_you_ucleansed",(uint64_t)(offsetof(struct you,ucleansed))},
{"width_you_ucleansed",(uint64_t)(sizeof(((struct you*)0)->ucleansed))},
{"offset_you_usleep",(uint64_t)(offsetof(struct you,usleep))},
{"width_you_usleep",(uint64_t)(sizeof(((struct you*)0)->usleep))},
{"offset_you_uinvault",(uint64_t)(offsetof(struct you,uinvault))},
{"width_you_uinvault",(uint64_t)(sizeof(((struct you*)0)->uinvault))},
{"offset_you_ustuck",(uint64_t)(offsetof(struct you,ustuck))},
{"width_you_ustuck",(uint64_t)(sizeof(((struct you*)0)->ustuck))},
{"offset_you_usteed",(uint64_t)(offsetof(struct you,usteed))},
{"width_you_usteed",(uint64_t)(sizeof(((struct you*)0)->usteed))},
{"offset_you_ustuck_mid",(uint64_t)(offsetof(struct you,ustuck_mid))},
{"width_you_ustuck_mid",(uint64_t)(sizeof(((struct you*)0)->ustuck_mid))},
{"offset_you_usteed_mid",(uint64_t)(offsetof(struct you,usteed_mid))},
{"width_you_usteed_mid",(uint64_t)(sizeof(((struct you*)0)->usteed_mid))},
{"offset_you_ugallop",(uint64_t)(offsetof(struct you,ugallop))},
{"width_you_ugallop",(uint64_t)(sizeof(((struct you*)0)->ugallop))},
{"offset_you_urideturns",(uint64_t)(offsetof(struct you,urideturns))},
{"width_you_urideturns",(uint64_t)(sizeof(((struct you*)0)->urideturns))},
{"offset_you_umortality",(uint64_t)(offsetof(struct you,umortality))},
{"width_you_umortality",(uint64_t)(sizeof(((struct you*)0)->umortality))},
{"offset_you_ugrave_arise",(uint64_t)(offsetof(struct you,ugrave_arise))},
{"width_you_ugrave_arise",(uint64_t)(sizeof(((struct you*)0)->ugrave_arise))},
{"offset_you_weapon_slots",(uint64_t)(offsetof(struct you,weapon_slots))},
{"width_you_weapon_slots",(uint64_t)(sizeof(((struct you*)0)->weapon_slots))},
{"offset_you_skills_advanced",(uint64_t)(offsetof(struct you,skills_advanced))},
{"width_you_skills_advanced",(uint64_t)(sizeof(((struct you*)0)->skills_advanced))},
{"offset_you_skill_record",(uint64_t)(offsetof(struct you,skill_record))},
{"width_you_skill_record",(uint64_t)(sizeof(((struct you*)0)->skill_record))},
{"offset_you_weapon_skills",(uint64_t)(offsetof(struct you,weapon_skills))},
{"width_you_weapon_skills",(uint64_t)(sizeof(((struct you*)0)->weapon_skills))},
{"offset_you_twoweap",(uint64_t)(offsetof(struct you,twoweap))},
{"width_you_twoweap",(uint64_t)(sizeof(((struct you*)0)->twoweap))},
{"offset_you_mcham",(uint64_t)(offsetof(struct you,mcham))},
{"width_you_mcham",(uint64_t)(sizeof(((struct you*)0)->mcham))},
{"offset_you_umovement",(uint64_t)(offsetof(struct you,umovement))},
{"width_you_umovement",(uint64_t)(sizeof(((struct you*)0)->umovement))},
{"offset_you_uachieved",(uint64_t)(offsetof(struct you,uachieved))},
{"width_you_uachieved",(uint64_t)(sizeof(((struct you*)0)->uachieved))},
{"offset_you_umonst",(uint64_t)(offsetof(struct you,umonst))},
{"width_you_umonst",(uint64_t)(sizeof(((struct you*)0)->umonst))},
};
int teleport_decl_layout_count(void){return sizeof decl_layout/sizeof decl_layout[0];}
const char*teleport_decl_layout_name(int i){return decl_layout[i].name;}
uint64_t teleport_decl_layout_value(int i){return decl_layout[i].value;}
static char decl_literals[DECL_LITERAL_CAPACITY];
char*teleport_decl_literal_storage(void){return decl_literals;}
size_t teleport_decl_literal_capacity(void){return sizeof decl_literals;}
void teleport_decl_raw_printf(const char*format,const char*name){raw_printf(format,name);}
#include <stdlib.h>
void teleport_decl_exit(int code){exit(code);}
