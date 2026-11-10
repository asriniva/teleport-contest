#ifndef TELEPORT_MAIL_LAYOUT_H
#define TELEPORT_MAIL_LAYOUT_H
#include "hack.h"
#include "mail.h"
#include "../nethack-c/wasm/tu-mail-support.h"
#include <stddef.h>
#include <sys/stat.h>
#include <pwd.h>
struct mail_meta {const char *name;size_t value;};
#define MAIL_META(k,v) {#k,(size_t)(v)}
static const struct mail_meta mail_layout[]={
MAIL_META(pointerSize,sizeof(void*)),
MAIL_META(longSize,sizeof(long)),
MAIL_META(timeSize,sizeof(time_t)),
MAIL_META(uidSize,sizeof(uid_t)),
MAIL_META(statSize,sizeof(struct stat)),
MAIL_META(coordSize,sizeof(coord)),
MAIL_META(monsterSize,sizeof(struct monst)),
MAIL_META(permonstSize,sizeof(struct permonst)),
MAIL_META(stairsSize,sizeof(stairway)),
MAIL_META(propSize,sizeof(struct prop)),
MAIL_META(rmSize,sizeof(struct rm)),
MAIL_META(mailInfoSize,sizeof(struct mail_info)),
MAIL_META(SeenSize,sizeof(seenV)),
MAIL_META(MAILPATH_SIZE,sizeof MAILPATH),
MAIL_META(coord_x,offsetof(coord,x)),
MAIL_META(coord_x_size,sizeof(((coord*)0)->x)),
MAIL_META(coord_y,offsetof(coord,y)),
MAIL_META(coord_y_size,sizeof(((coord*)0)->y)),
MAIL_META(mon_mx,offsetof(struct monst,mx)),
MAIL_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
MAIL_META(mon_my,offsetof(struct monst,my)),
MAIL_META(mon_my_size,sizeof(((struct monst*)0)->my)),
MAIL_META(u_ux,offsetof(struct you,ux)),
MAIL_META(u_ux_size,sizeof(((struct you*)0)->ux)),
MAIL_META(u_uy,offsetof(struct you,uy)),
MAIL_META(u_uy_size,sizeof(((struct you*)0)->uy)),
MAIL_META(u_uz,offsetof(struct you,uz)),
MAIL_META(u_uz_size,sizeof(((struct you*)0)->uz)),
MAIL_META(u_uprops,offsetof(struct you,uprops)),
MAIL_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
MAIL_META(lev_dnum,offsetof(d_level,dnum)),
MAIL_META(lev_dnum_size,sizeof(((d_level*)0)->dnum)),
MAIL_META(stairs_sx,offsetof(stairway,sx)),
MAIL_META(stairs_sx_size,sizeof(((stairway*)0)->sx)),
MAIL_META(stairs_sy,offsetof(stairway,sy)),
MAIL_META(stairs_sy_size,sizeof(((stairway*)0)->sy)),
MAIL_META(stairs_tolev,offsetof(stairway,tolev)),
MAIL_META(stairs_tolev_size,sizeof(((stairway*)0)->tolev)),
MAIL_META(stairs_next,offsetof(stairway,next)),
MAIL_META(stairs_next_size,sizeof(((stairway*)0)->next)),
MAIL_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
MAIL_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
MAIL_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
MAIL_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
MAIL_META(prop_blocked,offsetof(struct prop,blocked)),
MAIL_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
MAIL_META(info_message_typ,offsetof(struct mail_info,message_typ)),
MAIL_META(info_message_typ_size,sizeof(((struct mail_info*)0)->message_typ)),
MAIL_META(info_display_txt,offsetof(struct mail_info,display_txt)),
MAIL_META(info_display_txt_size,sizeof(((struct mail_info*)0)->display_txt)),
MAIL_META(info_object_nam,offsetof(struct mail_info,object_nam)),
MAIL_META(info_object_nam_size,sizeof(((struct mail_info*)0)->object_nam)),
MAIL_META(info_response_cmd,offsetof(struct mail_info,response_cmd)),
MAIL_META(info_response_cmd_size,sizeof(((struct mail_info*)0)->response_cmd)),
MAIL_META(passwd_pw_name,offsetof(struct passwd,pw_name)),
MAIL_META(passwd_pw_name_size,sizeof(((struct passwd*)0)->pw_name)),
MAIL_META(stat_st_mtime,offsetof(struct stat,st_mtime)),
MAIL_META(stat_st_mtime_size,sizeof(((struct stat*)0)->st_mtime)),
MAIL_META(stat_st_size,offsetof(struct stat,st_size)),
MAIL_META(stat_st_size_size,sizeof(((struct stat*)0)->st_size)),
MAIL_META(rm_typ,offsetof(struct rm,typ)),
MAIL_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
MAIL_META(stairs,offsetof(__typeof__(gs),stairs)),
MAIL_META(stairs_size,sizeof(gs.stairs)),
MAIL_META(vizArray,offsetof(__typeof__(gv),viz_array)),
MAIL_META(vizArray_size,sizeof(gv.viz_array)),
MAIL_META(rmin,offsetof(__typeof__(gv),viz_rmin)),
MAIL_META(rmin_size,sizeof(gv.viz_rmin)),
MAIL_META(rmax,offsetof(__typeof__(gv),viz_rmax)),
MAIL_META(rmax_size,sizeof(gv.viz_rmax)),
MAIL_META(monsters,offsetof(__typeof__(svl),level.monsters)),
MAIL_META(monsters_size,sizeof(svl.level.monsters)),
MAIL_META(locations,offsetof(__typeof__(svl),level.locations)),
MAIL_META(locations_size,sizeof(svl.level.locations)),
MAIL_META(moves,offsetof(__typeof__(svm),moves)),
MAIL_META(moves_size,sizeof(svm.moves)),
MAIL_META(plname,offsetof(__typeof__(svp),plname)),
MAIL_META(plname_size,sizeof(svp.plname)),
MAIL_META(biff,offsetof(__typeof__(flags),biff)),
MAIL_META(biff_size,sizeof(flags.biff)),
MAIL_META(last_msg,offsetof(__typeof__(iflags),last_msg)),
MAIL_META(last_msg_size,sizeof(iflags.last_msg)),
MAIL_META(debug_fuzzer,offsetof(__typeof__(iflags),debug_fuzzer)),
MAIL_META(debug_fuzzer_size,sizeof(iflags.debug_fuzzer)),
MAIL_META(COLNO,COLNO),
MAIL_META(ROWNO,ROWNO),
MAIL_META(PM_MAIL_DAEMON,PM_MAIL_DAEMON),
MAIL_META(SCR_MAIL,SCR_MAIL),
MAIL_META(DBWALL,DBWALL),
MAIL_META(BLINDED,BLINDED),
MAIL_META(TELEPAT,TELEPAT),
MAIL_META(DEAF,DEAF),
MAIL_META(MSG_OTHER,MSG_OTHER),
MAIL_META(MSG_MAIL,MSG_MAIL),
MAIL_META(MSG_CALL,MSG_CALL),
MAIL_META(MAILCKFREQ,MAILCKFREQ),
MAIL_META(NO_MM_FLAGS,NO_MM_FLAGS),
MAIL_META(ONAME_NO_FLAGS,ONAME_NO_FLAGS),
MAIL_META(EXIT_FAILURE,EXIT_FAILURE),
MAIL_META(BUFSZ,BUFSZ),
};
_Static_assert(sizeof(seenV)==1,"MAIL vision bytes");
_Static_assert(sizeof(iflags.last_msg)==4 && sizeof(flags.biff)==1 && sizeof(iflags.debug_fuzzer)==1,"MAIL flags");
_Static_assert(sizeof(time_t)==8 && sizeof(long)==8,"MAIL time ABI");
_Static_assert(sizeof(((struct stat*)0)->st_mtime)==8 && sizeof(((struct stat*)0)->st_size)==8,"MAIL stat ABI");
_Static_assert(((__typeof__(((struct stat*)0)->st_mtime))-1)<0,"MAIL signed mtime");
_Static_assert(((__typeof__(((struct stat*)0)->st_size))-1)<0,"MAIL signed size");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && sizeof(((coord*)0)->x)==2,"MAIL coordinates");
_Static_assert(sizeof(((d_level*)0)->dnum)==2 && ((__typeof__(((d_level*)0)->dnum))-1)<0,"MAIL dnum");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && ((__typeof__(((struct rm*)0)->typ))-1)<0,"MAIL terrain");
_Static_assert(sizeof(gv.viz_rmin[0])==2 && ((__typeof__(gv.viz_rmin[0]))-1)<0,"MAIL row limits");
#if !defined(MAIL) || !defined(UNIX) || !defined(MAILPATH) || !defined(DEF_MAILREADER) || defined(SIMPLE_MAIL) || defined(SERVER_ADMIN_MSG) || defined(PERMANENT_MAILBOX)
#error Review changed MAIL configuration
#endif
#undef MAIL_META
#endif
