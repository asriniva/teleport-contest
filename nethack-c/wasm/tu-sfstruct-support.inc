/* Typed storage and native dependencies only; serialization policy is JS. */
#include "tu-sfstruct-support.h"
#ifndef TELEPORT_REFERENCE_SFSTRUCT
struct sf_structlevel_procs historical_sfo_procs, historical_sfi_procs;
struct restore_info restoreinfo;
#endif
void *teleport_sfstruct_restore(void){return &restoreinfo;}
void *teleport_sfstruct_program(void){return &program_state;}
void *teleport_sfstruct_table(int input){return input?(void*)&historical_sfi_procs:(void*)&historical_sfo_procs;}
uintptr_t teleport_sfstruct_callback(int input,int index){switch(index){
case 0:return input?(uintptr_t)historical_sfi_arti_info:(uintptr_t)historical_sfo_arti_info;
case 1:return input?(uintptr_t)historical_sfi_nhrect:(uintptr_t)historical_sfo_nhrect;
case 2:return input?(uintptr_t)historical_sfi_branch:(uintptr_t)historical_sfo_branch;
case 3:return input?(uintptr_t)historical_sfi_bubble:(uintptr_t)historical_sfo_bubble;
case 4:return input?(uintptr_t)historical_sfi_cemetery:(uintptr_t)historical_sfo_cemetery;
case 5:return input?(uintptr_t)historical_sfi_context_info:(uintptr_t)historical_sfo_context_info;
case 6:return input?(uintptr_t)historical_sfi_nhcoord:(uintptr_t)historical_sfo_nhcoord;
case 7:return input?(uintptr_t)historical_sfi_damage:(uintptr_t)historical_sfo_damage;
case 8:return input?(uintptr_t)historical_sfi_dest_area:(uintptr_t)historical_sfo_dest_area;
case 9:return input?(uintptr_t)historical_sfi_dgn_topology:(uintptr_t)historical_sfo_dgn_topology;
case 10:return input?(uintptr_t)historical_sfi_dungeon:(uintptr_t)historical_sfo_dungeon;
case 11:return input?(uintptr_t)historical_sfi_d_level:(uintptr_t)historical_sfo_d_level;
case 12:return input?(uintptr_t)historical_sfi_ebones:(uintptr_t)historical_sfo_ebones;
case 13:return input?(uintptr_t)historical_sfi_edog:(uintptr_t)historical_sfo_edog;
case 14:return input?(uintptr_t)historical_sfi_egd:(uintptr_t)historical_sfo_egd;
case 15:return input?(uintptr_t)historical_sfi_emin:(uintptr_t)historical_sfo_emin;
case 16:return input?(uintptr_t)historical_sfi_engr:(uintptr_t)historical_sfo_engr;
case 17:return input?(uintptr_t)historical_sfi_epri:(uintptr_t)historical_sfo_epri;
case 18:return input?(uintptr_t)historical_sfi_eshk:(uintptr_t)historical_sfo_eshk;
case 19:return input?(uintptr_t)historical_sfi_fe:(uintptr_t)historical_sfo_fe;
case 20:return input?(uintptr_t)historical_sfi_flag:(uintptr_t)historical_sfo_flag;
case 21:return input?(uintptr_t)historical_sfi_fruit:(uintptr_t)historical_sfo_fruit;
case 22:return input?(uintptr_t)historical_sfi_gamelog_line:(uintptr_t)historical_sfo_gamelog_line;
case 23:return input?(uintptr_t)historical_sfi_kinfo:(uintptr_t)historical_sfo_kinfo;
case 24:return input?(uintptr_t)historical_sfi_levelflags:(uintptr_t)historical_sfo_levelflags;
case 25:return input?(uintptr_t)historical_sfi_ls_t:(uintptr_t)historical_sfo_ls_t;
case 26:return input?(uintptr_t)historical_sfi_linfo:(uintptr_t)historical_sfo_linfo;
case 27:return input?(uintptr_t)historical_sfi_mapseen_feat:(uintptr_t)historical_sfo_mapseen_feat;
case 28:return input?(uintptr_t)historical_sfi_mapseen_flags:(uintptr_t)historical_sfo_mapseen_flags;
case 29:return input?(uintptr_t)historical_sfi_mapseen_rooms:(uintptr_t)historical_sfo_mapseen_rooms;
case 30:return input?(uintptr_t)historical_sfi_mkroom:(uintptr_t)historical_sfo_mkroom;
case 31:return input?(uintptr_t)historical_sfi_monst:(uintptr_t)historical_sfo_monst;
case 32:return input?(uintptr_t)historical_sfi_mvitals:(uintptr_t)historical_sfo_mvitals;
case 33:return input?(uintptr_t)historical_sfi_obj:(uintptr_t)historical_sfo_obj;
case 34:return input?(uintptr_t)historical_sfi_objclass:(uintptr_t)historical_sfo_objclass;
case 35:return input?(uintptr_t)historical_sfi_q_score:(uintptr_t)historical_sfo_q_score;
case 36:return input?(uintptr_t)historical_sfi_rm:(uintptr_t)historical_sfo_rm;
case 37:return input?(uintptr_t)historical_sfi_spell:(uintptr_t)historical_sfo_spell;
case 38:return input?(uintptr_t)historical_sfi_stairway:(uintptr_t)historical_sfo_stairway;
case 39:return input?(uintptr_t)historical_sfi_s_level:(uintptr_t)historical_sfo_s_level;
case 40:return input?(uintptr_t)historical_sfi_trap:(uintptr_t)historical_sfo_trap;
case 41:return input?(uintptr_t)historical_sfi_version_info:(uintptr_t)historical_sfo_version_info;
case 42:return input?(uintptr_t)historical_sfi_you:(uintptr_t)historical_sfo_you;
case 43:return input?(uintptr_t)historical_sfi_any:(uintptr_t)historical_sfo_any;
case 44:return input?(uintptr_t)historical_sfi_aligntyp:(uintptr_t)historical_sfo_aligntyp;
case 45:return input?(uintptr_t)historical_sfi_boolean:(uintptr_t)historical_sfo_boolean;
case 46:return input?(uintptr_t)historical_sfi_coordxy:(uintptr_t)historical_sfo_coordxy;
case 47:return input?(uintptr_t)historical_sfi_genericptr_t:(uintptr_t)historical_sfo_genericptr_t;
case 48:return input?(uintptr_t)historical_sfi_int:(uintptr_t)historical_sfo_int;
case 49:return input?(uintptr_t)historical_sfi_int16:(uintptr_t)historical_sfo_int16;
case 50:return input?(uintptr_t)historical_sfi_int32:(uintptr_t)historical_sfo_int32;
case 51:return input?(uintptr_t)historical_sfi_int64:(uintptr_t)historical_sfo_int64;
case 52:return input?(uintptr_t)historical_sfi_long:(uintptr_t)historical_sfo_long;
case 53:return input?(uintptr_t)historical_sfi_schar:(uintptr_t)historical_sfo_schar;
case 54:return input?(uintptr_t)historical_sfi_short:(uintptr_t)historical_sfo_short;
case 55:return input?(uintptr_t)historical_sfi_size_t:(uintptr_t)historical_sfo_size_t;
case 56:return input?(uintptr_t)historical_sfi_time_t:(uintptr_t)historical_sfo_time_t;
case 57:return input?(uintptr_t)historical_sfi_uchar:(uintptr_t)historical_sfo_uchar;
case 58:return input?(uintptr_t)historical_sfi_uint16:(uintptr_t)historical_sfo_uint16;
case 59:return input?(uintptr_t)historical_sfi_uint32:(uintptr_t)historical_sfo_uint32;
case 60:return input?(uintptr_t)historical_sfi_uint64:(uintptr_t)historical_sfo_uint64;
case 61:return input?(uintptr_t)historical_sfi_ulong:(uintptr_t)historical_sfo_ulong;
case 62:return input?(uintptr_t)historical_sfi_unsigned:(uintptr_t)historical_sfo_unsigned;
case 63:return input?(uintptr_t)historical_sfi_ushort:(uintptr_t)historical_sfo_ushort;
case 64:return input?(uintptr_t)historical_sfi_xint16:(uintptr_t)historical_sfo_xint16;
case 65:return input?(uintptr_t)historical_sfi_xint8:(uintptr_t)historical_sfo_xint8;
case 66:return input?(uintptr_t)historical_sfi_char:(uintptr_t)historical_sfo_char;
case 67:return input?(uintptr_t)historical_sfi_bitfield:(uintptr_t)historical_sfo_bitfield;
}return 0;}
void teleport_sfstruct_proc(int input,int index,uintptr_t callback){struct sf_structlevel_procs *p=input?&historical_sfi_procs:&historical_sfo_procs;switch(index){
case 0:p->fn.sf_arti_info=(__typeof__(p->fn.sf_arti_info))callback;break;
case 1:p->fn.sf_nhrect=(__typeof__(p->fn.sf_nhrect))callback;break;
case 2:p->fn.sf_branch=(__typeof__(p->fn.sf_branch))callback;break;
case 3:p->fn.sf_bubble=(__typeof__(p->fn.sf_bubble))callback;break;
case 4:p->fn.sf_cemetery=(__typeof__(p->fn.sf_cemetery))callback;break;
case 5:p->fn.sf_context_info=(__typeof__(p->fn.sf_context_info))callback;break;
case 6:p->fn.sf_nhcoord=(__typeof__(p->fn.sf_nhcoord))callback;break;
case 7:p->fn.sf_damage=(__typeof__(p->fn.sf_damage))callback;break;
case 8:p->fn.sf_dest_area=(__typeof__(p->fn.sf_dest_area))callback;break;
case 9:p->fn.sf_dgn_topology=(__typeof__(p->fn.sf_dgn_topology))callback;break;
case 10:p->fn.sf_dungeon=(__typeof__(p->fn.sf_dungeon))callback;break;
case 11:p->fn.sf_d_level=(__typeof__(p->fn.sf_d_level))callback;break;
case 12:p->fn.sf_ebones=(__typeof__(p->fn.sf_ebones))callback;break;
case 13:p->fn.sf_edog=(__typeof__(p->fn.sf_edog))callback;break;
case 14:p->fn.sf_egd=(__typeof__(p->fn.sf_egd))callback;break;
case 15:p->fn.sf_emin=(__typeof__(p->fn.sf_emin))callback;break;
case 16:p->fn.sf_engr=(__typeof__(p->fn.sf_engr))callback;break;
case 17:p->fn.sf_epri=(__typeof__(p->fn.sf_epri))callback;break;
case 18:p->fn.sf_eshk=(__typeof__(p->fn.sf_eshk))callback;break;
case 19:p->fn.sf_fe=(__typeof__(p->fn.sf_fe))callback;break;
case 20:p->fn.sf_flag=(__typeof__(p->fn.sf_flag))callback;break;
case 21:p->fn.sf_fruit=(__typeof__(p->fn.sf_fruit))callback;break;
case 22:p->fn.sf_gamelog_line=(__typeof__(p->fn.sf_gamelog_line))callback;break;
case 23:p->fn.sf_kinfo=(__typeof__(p->fn.sf_kinfo))callback;break;
case 24:p->fn.sf_levelflags=(__typeof__(p->fn.sf_levelflags))callback;break;
case 25:p->fn.sf_ls_t=(__typeof__(p->fn.sf_ls_t))callback;break;
case 26:p->fn.sf_linfo=(__typeof__(p->fn.sf_linfo))callback;break;
case 27:p->fn.sf_mapseen_feat=(__typeof__(p->fn.sf_mapseen_feat))callback;break;
case 28:p->fn.sf_mapseen_flags=(__typeof__(p->fn.sf_mapseen_flags))callback;break;
case 29:p->fn.sf_mapseen_rooms=(__typeof__(p->fn.sf_mapseen_rooms))callback;break;
case 30:p->fn.sf_mkroom=(__typeof__(p->fn.sf_mkroom))callback;break;
case 31:p->fn.sf_monst=(__typeof__(p->fn.sf_monst))callback;break;
case 32:p->fn.sf_mvitals=(__typeof__(p->fn.sf_mvitals))callback;break;
case 33:p->fn.sf_obj=(__typeof__(p->fn.sf_obj))callback;break;
case 34:p->fn.sf_objclass=(__typeof__(p->fn.sf_objclass))callback;break;
case 35:p->fn.sf_q_score=(__typeof__(p->fn.sf_q_score))callback;break;
case 36:p->fn.sf_rm=(__typeof__(p->fn.sf_rm))callback;break;
case 37:p->fn.sf_spell=(__typeof__(p->fn.sf_spell))callback;break;
case 38:p->fn.sf_stairway=(__typeof__(p->fn.sf_stairway))callback;break;
case 39:p->fn.sf_s_level=(__typeof__(p->fn.sf_s_level))callback;break;
case 40:p->fn.sf_trap=(__typeof__(p->fn.sf_trap))callback;break;
case 41:p->fn.sf_version_info=(__typeof__(p->fn.sf_version_info))callback;break;
case 42:p->fn.sf_you=(__typeof__(p->fn.sf_you))callback;break;
case 43:p->fn.sf_any=(__typeof__(p->fn.sf_any))callback;break;
case 44:p->fn.sf_aligntyp=(__typeof__(p->fn.sf_aligntyp))callback;break;
case 45:p->fn.sf_boolean=(__typeof__(p->fn.sf_boolean))callback;break;
case 46:p->fn.sf_coordxy=(__typeof__(p->fn.sf_coordxy))callback;break;
case 47:p->fn.sf_genericptr=(__typeof__(p->fn.sf_genericptr))callback;break;
case 48:p->fn.sf_int=(__typeof__(p->fn.sf_int))callback;break;
case 49:p->fn.sf_int16=(__typeof__(p->fn.sf_int16))callback;break;
case 50:p->fn.sf_int32=(__typeof__(p->fn.sf_int32))callback;break;
case 51:p->fn.sf_int64=(__typeof__(p->fn.sf_int64))callback;break;
case 52:p->fn.sf_long=(__typeof__(p->fn.sf_long))callback;break;
case 53:p->fn.sf_schar=(__typeof__(p->fn.sf_schar))callback;break;
case 54:p->fn.sf_short=(__typeof__(p->fn.sf_short))callback;break;
case 55:p->fn.sf_size_t=(__typeof__(p->fn.sf_size_t))callback;break;
case 56:p->fn.sf_time_t=(__typeof__(p->fn.sf_time_t))callback;break;
case 57:p->fn.sf_uchar=(__typeof__(p->fn.sf_uchar))callback;break;
case 58:p->fn.sf_uint16=(__typeof__(p->fn.sf_uint16))callback;break;
case 59:p->fn.sf_uint32=(__typeof__(p->fn.sf_uint32))callback;break;
case 60:p->fn.sf_uint64=(__typeof__(p->fn.sf_uint64))callback;break;
case 61:p->fn.sf_ulong=(__typeof__(p->fn.sf_ulong))callback;break;
case 62:p->fn.sf_unsigned=(__typeof__(p->fn.sf_unsigned))callback;break;
case 63:p->fn.sf_ushort=(__typeof__(p->fn.sf_ushort))callback;break;
case 64:p->fn.sf_xint16=(__typeof__(p->fn.sf_xint16))callback;break;
case 65:p->fn.sf_xint8=(__typeof__(p->fn.sf_xint8))callback;break;
case 66:p->fn.sf_char=(__typeof__(p->fn.sf_char))callback;break;
case 67:p->fn.sf_bitfield=(__typeof__(p->fn.sf_bitfield))callback;break;
}}
void teleport_sfstruct_ext(int input,const char *ext){(input?&historical_sfi_procs:&historical_sfo_procs)->ext=ext;}
void teleport_sfstruct_panic(int kind,unsigned num,int fd){switch(kind){case 0:panic("buffering already enabled");break;case 1:panic("buffering of file %d failed",fd);break;case 2:panic("flush of savefile failed!");break;case 3:panic("cannot write %u bytes to file #%d",num,fd);break;default:panic("Error reading level file.");break;}}
void teleport_sfstruct_impossible(int fd){impossible("fd not in list (%d)?",fd);}
void teleport_sfstruct_read_message(int rlen,unsigned len){pline("Read %d instead of %u bytes.",rlen,len);}
void teleport_sfstruct_display(void){display_nhwindow(WIN_MESSAGE,TRUE);}
void teleport_sfstruct_error(void){error("Error restoring old game.");}
extern void norm_ptrs_arti_info(struct arti_info *);
void teleport_sfstruct_norm_arti_info(void *p){norm_ptrs_arti_info((struct arti_info*)p);}
extern void norm_ptrs_nhrect(struct nhrect *);
void teleport_sfstruct_norm_nhrect(void *p){norm_ptrs_nhrect((struct nhrect*)p);}
extern void norm_ptrs_branch(struct branch *);
void teleport_sfstruct_norm_branch(void *p){norm_ptrs_branch((struct branch*)p);}
extern void norm_ptrs_bubble(struct bubble *);
void teleport_sfstruct_norm_bubble(void *p){norm_ptrs_bubble((struct bubble*)p);}
extern void norm_ptrs_cemetery(struct cemetery *);
void teleport_sfstruct_norm_cemetery(void *p){norm_ptrs_cemetery((struct cemetery*)p);}
extern void norm_ptrs_context_info(struct context_info *);
void teleport_sfstruct_norm_context_info(void *p){norm_ptrs_context_info((struct context_info*)p);}
extern void norm_ptrs_nhcoord(struct nhcoord *);
void teleport_sfstruct_norm_nhcoord(void *p){norm_ptrs_nhcoord((struct nhcoord*)p);}
extern void norm_ptrs_damage(struct damage *);
void teleport_sfstruct_norm_damage(void *p){norm_ptrs_damage((struct damage*)p);}
extern void norm_ptrs_dest_area(struct dest_area *);
void teleport_sfstruct_norm_dest_area(void *p){norm_ptrs_dest_area((struct dest_area*)p);}
extern void norm_ptrs_dgn_topology(struct dgn_topology *);
void teleport_sfstruct_norm_dgn_topology(void *p){norm_ptrs_dgn_topology((struct dgn_topology*)p);}
extern void norm_ptrs_dungeon(struct dungeon *);
void teleport_sfstruct_norm_dungeon(void *p){norm_ptrs_dungeon((struct dungeon*)p);}
extern void norm_ptrs_d_level(struct d_level *);
void teleport_sfstruct_norm_d_level(void *p){norm_ptrs_d_level((struct d_level*)p);}
extern void norm_ptrs_ebones(struct ebones *);
void teleport_sfstruct_norm_ebones(void *p){norm_ptrs_ebones((struct ebones*)p);}
extern void norm_ptrs_edog(struct edog *);
void teleport_sfstruct_norm_edog(void *p){norm_ptrs_edog((struct edog*)p);}
extern void norm_ptrs_egd(struct egd *);
void teleport_sfstruct_norm_egd(void *p){norm_ptrs_egd((struct egd*)p);}
extern void norm_ptrs_emin(struct emin *);
void teleport_sfstruct_norm_emin(void *p){norm_ptrs_emin((struct emin*)p);}
extern void norm_ptrs_engr(struct engr *);
void teleport_sfstruct_norm_engr(void *p){norm_ptrs_engr((struct engr*)p);}
extern void norm_ptrs_epri(struct epri *);
void teleport_sfstruct_norm_epri(void *p){norm_ptrs_epri((struct epri*)p);}
extern void norm_ptrs_eshk(struct eshk *);
void teleport_sfstruct_norm_eshk(void *p){norm_ptrs_eshk((struct eshk*)p);}
extern void norm_ptrs_fe(struct fe *);
void teleport_sfstruct_norm_fe(void *p){norm_ptrs_fe((struct fe*)p);}
extern void norm_ptrs_flag(struct flag *);
void teleport_sfstruct_norm_flag(void *p){norm_ptrs_flag((struct flag*)p);}
extern void norm_ptrs_fruit(struct fruit *);
void teleport_sfstruct_norm_fruit(void *p){norm_ptrs_fruit((struct fruit*)p);}
extern void norm_ptrs_gamelog_line(struct gamelog_line *);
void teleport_sfstruct_norm_gamelog_line(void *p){norm_ptrs_gamelog_line((struct gamelog_line*)p);}
extern void norm_ptrs_kinfo(struct kinfo *);
void teleport_sfstruct_norm_kinfo(void *p){norm_ptrs_kinfo((struct kinfo*)p);}
extern void norm_ptrs_levelflags(struct levelflags *);
void teleport_sfstruct_norm_levelflags(void *p){norm_ptrs_levelflags((struct levelflags*)p);}
extern void norm_ptrs_ls_t(struct ls_t *);
void teleport_sfstruct_norm_ls_t(void *p){norm_ptrs_ls_t((struct ls_t*)p);}
extern void norm_ptrs_linfo(struct linfo *);
void teleport_sfstruct_norm_linfo(void *p){norm_ptrs_linfo((struct linfo*)p);}
extern void norm_ptrs_mapseen_feat(struct mapseen_feat *);
void teleport_sfstruct_norm_mapseen_feat(void *p){norm_ptrs_mapseen_feat((struct mapseen_feat*)p);}
extern void norm_ptrs_mapseen_flags(struct mapseen_flags *);
void teleport_sfstruct_norm_mapseen_flags(void *p){norm_ptrs_mapseen_flags((struct mapseen_flags*)p);}
extern void norm_ptrs_mapseen_rooms(struct mapseen_rooms *);
void teleport_sfstruct_norm_mapseen_rooms(void *p){norm_ptrs_mapseen_rooms((struct mapseen_rooms*)p);}
extern void norm_ptrs_mkroom(struct mkroom *);
void teleport_sfstruct_norm_mkroom(void *p){norm_ptrs_mkroom((struct mkroom*)p);}
extern void norm_ptrs_monst(struct monst *);
void teleport_sfstruct_norm_monst(void *p){norm_ptrs_monst((struct monst*)p);}
extern void norm_ptrs_mvitals(struct mvitals *);
void teleport_sfstruct_norm_mvitals(void *p){norm_ptrs_mvitals((struct mvitals*)p);}
extern void norm_ptrs_obj(struct obj *);
void teleport_sfstruct_norm_obj(void *p){norm_ptrs_obj((struct obj*)p);}
extern void norm_ptrs_objclass(struct objclass *);
void teleport_sfstruct_norm_objclass(void *p){norm_ptrs_objclass((struct objclass*)p);}
extern void norm_ptrs_q_score(struct q_score *);
void teleport_sfstruct_norm_q_score(void *p){norm_ptrs_q_score((struct q_score*)p);}
extern void norm_ptrs_rm(struct rm *);
void teleport_sfstruct_norm_rm(void *p){norm_ptrs_rm((struct rm*)p);}
extern void norm_ptrs_spell(struct spell *);
void teleport_sfstruct_norm_spell(void *p){norm_ptrs_spell((struct spell*)p);}
extern void norm_ptrs_stairway(struct stairway *);
void teleport_sfstruct_norm_stairway(void *p){norm_ptrs_stairway((struct stairway*)p);}
extern void norm_ptrs_s_level(struct s_level *);
void teleport_sfstruct_norm_s_level(void *p){norm_ptrs_s_level((struct s_level*)p);}
extern void norm_ptrs_trap(struct trap *);
void teleport_sfstruct_norm_trap(void *p){norm_ptrs_trap((struct trap*)p);}
extern void norm_ptrs_you(struct you *);
void teleport_sfstruct_norm_you(void *p){norm_ptrs_you((struct you*)p);}
extern void norm_ptrs_any(union any *);
void teleport_sfstruct_norm_any(void *p){norm_ptrs_any((union any*)p);}
extern void norm_ptrs_version_info(struct version_info *);
void teleport_sfstruct_norm_version_info(void *p){norm_ptrs_version_info((struct version_info*)p);}

void *teleport_sfstruct_string_alloc(size_t size){return malloc(size);}

/* C relocations preserve actual native IO and test-only dependency spies. */
long teleport_sfstruct_read(int fd,void *buf,size_t len){return (long)read(fd,buf,len);}
long teleport_sfstruct_write(int fd,const void *buf,size_t len){return (long)write(fd,buf,len);}
FILE *teleport_sfstruct_fdopen(int fd,const char *mode){return fdopen(fd,mode);}
size_t teleport_sfstruct_fwrite(const void *buf,size_t size,size_t count,FILE *fp){return fwrite(buf,size,count,fp);}
int teleport_sfstruct_fflush(FILE *fp){return fflush(fp);}
int teleport_sfstruct_fclose(FILE *fp){return fclose(fp);}
int teleport_sfstruct_close(int fd){return close(fd);}
