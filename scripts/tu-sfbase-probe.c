/* Controlled callback worlds for original SFBASE and its imported JS replacement.
 * Callback bodies are dependencies, not replacements for any SFBASE algorithm. */
#include "hack.h"
#include "sfprocs.h"
#include "tu-sfbase-layout.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
void sfo_arti_info(NHFILE * nhfp,struct arti_info * d_arti_info,const char * myname);
void sfi_arti_info(NHFILE * nhfp,struct arti_info * d_arti_info,const char * myname);
void sfo_nhrect(NHFILE * nhfp,struct nhrect * d_nhrect,const char * myname);
void sfi_nhrect(NHFILE * nhfp,struct nhrect * d_nhrect,const char * myname);
void sfo_branch(NHFILE * nhfp,struct branch * d_branch,const char * myname);
void sfi_branch(NHFILE * nhfp,struct branch * d_branch,const char * myname);
void sfo_bubble(NHFILE * nhfp,struct bubble * d_bubble,const char * myname);
void sfi_bubble(NHFILE * nhfp,struct bubble * d_bubble,const char * myname);
void sfo_cemetery(NHFILE * nhfp,struct cemetery * d_cemetery,const char * myname);
void sfi_cemetery(NHFILE * nhfp,struct cemetery * d_cemetery,const char * myname);
void sfo_context_info(NHFILE * nhfp,struct context_info * d_context_info,const char * myname);
void sfi_context_info(NHFILE * nhfp,struct context_info * d_context_info,const char * myname);
void sfo_nhcoord(NHFILE * nhfp,struct nhcoord * d_nhcoord,const char * myname);
void sfi_nhcoord(NHFILE * nhfp,struct nhcoord * d_nhcoord,const char * myname);
void sfo_damage(NHFILE * nhfp,struct damage * d_damage,const char * myname);
void sfi_damage(NHFILE * nhfp,struct damage * d_damage,const char * myname);
void sfo_dest_area(NHFILE * nhfp,struct dest_area * d_dest_area,const char * myname);
void sfi_dest_area(NHFILE * nhfp,struct dest_area * d_dest_area,const char * myname);
void sfo_dgn_topology(NHFILE * nhfp,struct dgn_topology * d_dgn_topology,const char * myname);
void sfi_dgn_topology(NHFILE * nhfp,struct dgn_topology * d_dgn_topology,const char * myname);
void sfo_dungeon(NHFILE * nhfp,struct dungeon * d_dungeon,const char * myname);
void sfi_dungeon(NHFILE * nhfp,struct dungeon * d_dungeon,const char * myname);
void sfo_d_level(NHFILE * nhfp,struct d_level * d_d_level,const char * myname);
void sfi_d_level(NHFILE * nhfp,struct d_level * d_d_level,const char * myname);
void sfo_ebones(NHFILE * nhfp,struct ebones * d_ebones,const char * myname);
void sfi_ebones(NHFILE * nhfp,struct ebones * d_ebones,const char * myname);
void sfo_edog(NHFILE * nhfp,struct edog * d_edog,const char * myname);
void sfi_edog(NHFILE * nhfp,struct edog * d_edog,const char * myname);
void sfo_egd(NHFILE * nhfp,struct egd * d_egd,const char * myname);
void sfi_egd(NHFILE * nhfp,struct egd * d_egd,const char * myname);
void sfo_emin(NHFILE * nhfp,struct emin * d_emin,const char * myname);
void sfi_emin(NHFILE * nhfp,struct emin * d_emin,const char * myname);
void sfo_engr(NHFILE * nhfp,struct engr * d_engr,const char * myname);
void sfi_engr(NHFILE * nhfp,struct engr * d_engr,const char * myname);
void sfo_epri(NHFILE * nhfp,struct epri * d_epri,const char * myname);
void sfi_epri(NHFILE * nhfp,struct epri * d_epri,const char * myname);
void sfo_eshk(NHFILE * nhfp,struct eshk * d_eshk,const char * myname);
void sfi_eshk(NHFILE * nhfp,struct eshk * d_eshk,const char * myname);
void sfo_fe(NHFILE * nhfp,struct fe * d_fe,const char * myname);
void sfi_fe(NHFILE * nhfp,struct fe * d_fe,const char * myname);
void sfo_flag(NHFILE * nhfp,struct flag * d_flag,const char * myname);
void sfi_flag(NHFILE * nhfp,struct flag * d_flag,const char * myname);
void sfo_fruit(NHFILE * nhfp,struct fruit * d_fruit,const char * myname);
void sfi_fruit(NHFILE * nhfp,struct fruit * d_fruit,const char * myname);
void sfo_gamelog_line(NHFILE * nhfp,struct gamelog_line * d_gamelog_line,const char * myname);
void sfi_gamelog_line(NHFILE * nhfp,struct gamelog_line * d_gamelog_line,const char * myname);
void sfo_kinfo(NHFILE * nhfp,struct kinfo * d_kinfo,const char * myname);
void sfi_kinfo(NHFILE * nhfp,struct kinfo * d_kinfo,const char * myname);
void sfo_levelflags(NHFILE * nhfp,struct levelflags * d_levelflags,const char * myname);
void sfi_levelflags(NHFILE * nhfp,struct levelflags * d_levelflags,const char * myname);
void sfo_ls_t(NHFILE * nhfp,struct ls_t * d_ls_t,const char * myname);
void sfi_ls_t(NHFILE * nhfp,struct ls_t * d_ls_t,const char * myname);
void sfo_linfo(NHFILE * nhfp,struct linfo * d_linfo,const char * myname);
void sfi_linfo(NHFILE * nhfp,struct linfo * d_linfo,const char * myname);
void sfo_mapseen_feat(NHFILE * nhfp,struct mapseen_feat * d_mapseen_feat,const char * myname);
void sfi_mapseen_feat(NHFILE * nhfp,struct mapseen_feat * d_mapseen_feat,const char * myname);
void sfo_mapseen_flags(NHFILE * nhfp,struct mapseen_flags * d_mapseen_flags,const char * myname);
void sfi_mapseen_flags(NHFILE * nhfp,struct mapseen_flags * d_mapseen_flags,const char * myname);
void sfo_mapseen_rooms(NHFILE * nhfp,struct mapseen_rooms * d_mapseen_rooms,const char * myname);
void sfi_mapseen_rooms(NHFILE * nhfp,struct mapseen_rooms * d_mapseen_rooms,const char * myname);
void sfo_mkroom(NHFILE * nhfp,struct mkroom * d_mkroom,const char * myname);
void sfi_mkroom(NHFILE * nhfp,struct mkroom * d_mkroom,const char * myname);
void sfo_monst(NHFILE * nhfp,struct monst * d_monst,const char * myname);
void sfi_monst(NHFILE * nhfp,struct monst * d_monst,const char * myname);
void sfo_mvitals(NHFILE * nhfp,struct mvitals * d_mvitals,const char * myname);
void sfi_mvitals(NHFILE * nhfp,struct mvitals * d_mvitals,const char * myname);
void sfo_obj(NHFILE * nhfp,struct obj * d_obj,const char * myname);
void sfi_obj(NHFILE * nhfp,struct obj * d_obj,const char * myname);
void sfo_objclass(NHFILE * nhfp,struct objclass * d_objclass,const char * myname);
void sfi_objclass(NHFILE * nhfp,struct objclass * d_objclass,const char * myname);
void sfo_q_score(NHFILE * nhfp,struct q_score * d_q_score,const char * myname);
void sfi_q_score(NHFILE * nhfp,struct q_score * d_q_score,const char * myname);
void sfo_rm(NHFILE * nhfp,struct rm * d_rm,const char * myname);
void sfi_rm(NHFILE * nhfp,struct rm * d_rm,const char * myname);
void sfo_spell(NHFILE * nhfp,struct spell * d_spell,const char * myname);
void sfi_spell(NHFILE * nhfp,struct spell * d_spell,const char * myname);
void sfo_stairway(NHFILE * nhfp,struct stairway * d_stairway,const char * myname);
void sfi_stairway(NHFILE * nhfp,struct stairway * d_stairway,const char * myname);
void sfo_s_level(NHFILE * nhfp,struct s_level * d_s_level,const char * myname);
void sfi_s_level(NHFILE * nhfp,struct s_level * d_s_level,const char * myname);
void sfo_trap(NHFILE * nhfp,struct trap * d_trap,const char * myname);
void sfi_trap(NHFILE * nhfp,struct trap * d_trap,const char * myname);
void sfo_you(NHFILE * nhfp,struct you * d_you,const char * myname);
void sfi_you(NHFILE * nhfp,struct you * d_you,const char * myname);
void sfo_any(NHFILE * nhfp,union any * d_any,const char * myname);
void sfi_any(NHFILE * nhfp,union any * d_any,const char * myname);
void sfo_aligntyp(NHFILE * nhfp,aligntyp * d_aligntyp,const char * myname);
void sfi_aligntyp(NHFILE * nhfp,aligntyp * d_aligntyp,const char * myname);
void sfo_boolean(NHFILE * nhfp,boolean * d_boolean,const char * myname);
void sfi_boolean(NHFILE * nhfp,boolean * d_boolean,const char * myname);
void sfo_coordxy(NHFILE * nhfp,coordxy * d_coordxy,const char * myname);
void sfi_coordxy(NHFILE * nhfp,coordxy * d_coordxy,const char * myname);
void sfo_int(NHFILE * nhfp,int * d_int,const char * myname);
void sfi_int(NHFILE * nhfp,int * d_int,const char * myname);
void sfo_int16(NHFILE * nhfp,int16 * d_int16,const char * myname);
void sfi_int16(NHFILE * nhfp,int16 * d_int16,const char * myname);
void sfo_int32(NHFILE * nhfp,int32 * d_int32,const char * myname);
void sfi_int32(NHFILE * nhfp,int32 * d_int32,const char * myname);
void sfo_int64(NHFILE * nhfp,int64 * d_int64,const char * myname);
void sfi_int64(NHFILE * nhfp,int64 * d_int64,const char * myname);
void sfo_long(NHFILE * nhfp,long * d_long,const char * myname);
void sfi_long(NHFILE * nhfp,long * d_long,const char * myname);
void sfo_schar(NHFILE * nhfp,schar * d_schar,const char * myname);
void sfi_schar(NHFILE * nhfp,schar * d_schar,const char * myname);
void sfo_short(NHFILE * nhfp,short * d_short,const char * myname);
void sfi_short(NHFILE * nhfp,short * d_short,const char * myname);
void sfo_size_t(NHFILE * nhfp,size_t * d_size_t,const char * myname);
void sfi_size_t(NHFILE * nhfp,size_t * d_size_t,const char * myname);
void sfo_time_t(NHFILE * nhfp,time_t * d_time_t,const char * myname);
void sfi_time_t(NHFILE * nhfp,time_t * d_time_t,const char * myname);
void sfo_uchar(NHFILE * nhfp,uchar * d_uchar,const char * myname);
void sfi_uchar(NHFILE * nhfp,uchar * d_uchar,const char * myname);
void sfo_uint16(NHFILE * nhfp,uint16 * d_uint16,const char * myname);
void sfi_uint16(NHFILE * nhfp,uint16 * d_uint16,const char * myname);
void sfo_uint32(NHFILE * nhfp,uint32 * d_uint32,const char * myname);
void sfi_uint32(NHFILE * nhfp,uint32 * d_uint32,const char * myname);
void sfo_uint64(NHFILE * nhfp,uint64 * d_uint64,const char * myname);
void sfi_uint64(NHFILE * nhfp,uint64 * d_uint64,const char * myname);
void sfo_ulong(NHFILE * nhfp,ulong * d_ulong,const char * myname);
void sfi_ulong(NHFILE * nhfp,ulong * d_ulong,const char * myname);
void sfo_unsigned(NHFILE * nhfp,unsigned int * d_unsigned,const char * myname);
void sfi_unsigned(NHFILE * nhfp,unsigned int * d_unsigned,const char * myname);
void sfo_ushort(NHFILE * nhfp,ushort * d_ushort,const char * myname);
void sfi_ushort(NHFILE * nhfp,ushort * d_ushort,const char * myname);
void sfo_xint16(NHFILE * nhfp,xint16 * d_xint16,const char * myname);
void sfi_xint16(NHFILE * nhfp,xint16 * d_xint16,const char * myname);
void sfo_xint8(NHFILE * nhfp,xint8 * d_xint8,const char * myname);
void sfi_xint8(NHFILE * nhfp,xint8 * d_xint8,const char * myname);
void sfo_bitfield(NHFILE * nhfp,uint8_t * d_bitfield,const char * myname,int bfsz);
void sfi_bitfield(NHFILE * nhfp,uint8_t * d_bitfield,const char * myname,int bfsz);
void sfo_char(NHFILE * nhfp,char * d_char,const char * myname,int cnt);
void sfi_char(NHFILE * nhfp,char * d_char,const char * myname,int cnt);
void sfo_genericptr(NHFILE * nhfp,void ** d_genericptr,const char * myname);
void sfi_genericptr(NHFILE * nhfp,void ** d_genericptr,const char * myname);
void sfo_version_info(NHFILE * nhfp,struct version_info * d_version_info,const char * myname);
void sfi_version_info(NHFILE * nhfp,struct version_info * d_version_info,const char * myname);
void sf_log(NHFILE * nhfp,const char * t1,size_t sz,int cnt,char * txtvalue);
char * sfvalue_char(char * a,int n);
char * sfvalue_boolean(boolean * a);
char * sfvalue_schar(schar * a);
char * sfvalue_aligntyp(aligntyp * a);
char * sfvalue_any(anything * a);
char * sfvalue_genericptr(void * a);
char * sfvalue_int16(int16 * a);
char * sfvalue_int32(int32 * a);
char * sfvalue_int64(int64 * a);
char * sfvalue_uchar(uchar * a);
char * sfvalue_uint16(uint16 * a);
char * sfvalue_uint32(uint32 * a);
char * sfvalue_uint64(uint64 * a);
char * sfvalue_size_t(size_t * a);
char * sfvalue_time_t(time_t * a);
char * sfvalue_short(short * a);
char * sfvalue_ushort(ushort * a);
char * sfvalue_int(int * a);
char * sfvalue_unsigned(unsigned int * a);
char * sfvalue_long(long * a);
char * sfvalue_ulong(ulong * a);
char * sfvalue_xint8(xint8 * a);
char * sfvalue_xint16(xint16 * a);
char * sfvalue_bitfield(uint8 * a);
char * bitfield_dump(uint8 * a);
char * complex_dump(uchar * a);
void sf_init(void);
void sf_setprocs(int idx,struct sf_structlevel_procs * sfi,struct sf_structlevel_procs * sfo);
void sf_setflprocs(int idx,struct sf_fieldlevel_procs * flsfi,struct sf_fieldlevel_procs * flsfo);
void norm_ptrs_any(union any * d_any);
void norm_ptrs_align(struct align * d_align);
void norm_ptrs_arti_info(struct arti_info * d_arti_info);
void norm_ptrs_attribs(struct attribs * d_attribs);
void norm_ptrs_bill_x(struct bill_x * d_bill_x);
void norm_ptrs_branch(struct branch * d_branch);
void norm_ptrs_bubble(struct bubble * d_bubble);
void norm_ptrs_cemetery(struct cemetery * d_cemetery);
void norm_ptrs_context_info(struct context_info * d_context_info);
void norm_ptrs_achievement_tracking(struct achievement_tracking * d_achievement_tracking);
void norm_ptrs_book_info(struct book_info * d_book_info);
void norm_ptrs_dig_info(struct dig_info * d_dig_info);
void norm_ptrs_engrave_info(struct engrave_info * d_engrave_info);
void norm_ptrs_obj_split(struct obj_split * d_obj_split);
void norm_ptrs_polearm_info(struct polearm_info * d_polearm_info);
void norm_ptrs_takeoff_info(struct takeoff_info * d_takeoff_info);
void norm_ptrs_tin_info(struct tin_info * d_tin_info);
void norm_ptrs_tribute_info(struct tribute_info * d_tribute_info);
void norm_ptrs_victual_info(struct victual_info * d_victual_info);
void norm_ptrs_warntype_info(struct warntype_info * d_warntype_info);
void norm_ptrs_d_flags(struct d_flags * d_d_flags);
void norm_ptrs_d_level(struct d_level * d_d_level);
void norm_ptrs_damage(struct damage * d_damage);
void norm_ptrs_dest_area(struct dest_area * d_dest_area);
void norm_ptrs_dgn_topology(struct dgn_topology * d_dgn_topology);
void norm_ptrs_dungeon(struct dungeon * d_dungeon);
void norm_ptrs_ebones(struct ebones * d_ebones);
void norm_ptrs_edog(struct edog * d_edog);
void norm_ptrs_egd(struct egd * d_egd);
void norm_ptrs_emin(struct emin * d_emin);
void norm_ptrs_engr(struct engr * d_engr);
void norm_ptrs_epri(struct epri * d_epri);
void norm_ptrs_eshk(struct eshk * d_eshk);
void norm_ptrs_fakecorridor(struct fakecorridor * d_fakecorridor);
void norm_ptrs_fe(struct fe * d_fe);
void norm_ptrs_flag(struct flag * d_flag);
void norm_ptrs_fruit(struct fruit * d_fruit);
void norm_ptrs_gamelog_line(struct gamelog_line * d_gamelog_line);
void norm_ptrs_kinfo(struct kinfo * d_kinfo);
void norm_ptrs_levelflags(struct levelflags * d_levelflags);
void norm_ptrs_linfo(struct linfo * d_linfo);
void norm_ptrs_ls_t(struct ls_t * d_ls_t);
void norm_ptrs_mapseen_feat(struct mapseen_feat * d_mapseen_feat);
void norm_ptrs_mapseen_flags(struct mapseen_flags * d_mapseen_flags);
void norm_ptrs_mapseen_rooms(struct mapseen_rooms * d_mapseen_rooms);
void norm_ptrs_mapseen(struct mapseen * d_mapseen);
void norm_ptrs_mextra(struct mextra * d_mextra);
void norm_ptrs_mkroom(struct mkroom * d_mkroom);
void norm_ptrs_monst(struct monst * d_monst);
void norm_ptrs_mvitals(struct mvitals * d_mvitals);
void norm_ptrs_nhcoord(struct nhcoord * d_nhcoord);
void norm_ptrs_nhrect(struct nhrect * d_nhrect);
void norm_ptrs_novel_tracking(struct novel_tracking * d_novel_tracking);
void norm_ptrs_obj(struct obj * d_obj);
void norm_ptrs_objclass(struct objclass * d_objclass);
void norm_ptrs_oextra(struct oextra * d_oextra);
void norm_ptrs_prop(struct prop * d_prop);
void norm_ptrs_q_score(struct q_score * d_q_score);
void norm_ptrs_rm(struct rm * d_rm);
void norm_ptrs_s_level(struct s_level * d_s_level);
void norm_ptrs_skills(struct skills * d_skills);
void norm_ptrs_spell(struct spell * d_spell);
void norm_ptrs_stairway(struct stairway * d_stairway);
void norm_ptrs_trap(struct trap * d_trap);
void norm_ptrs_u_conduct(struct u_conduct * d_u_conduct);
void norm_ptrs_u_event(struct u_event * d_u_event);
void norm_ptrs_u_have(struct u_have * d_u_have);
void norm_ptrs_u_realtime(struct u_realtime * d_u_realtime);
void norm_ptrs_u_roleplay(struct u_roleplay * d_u_roleplay);
void norm_ptrs_version_info(struct version_info * d_version_info);
void norm_ptrs_vlaunchinfo(union vlaunchinfo * d_vlaunchinfo);
void norm_ptrs_vptrs(union vptrs * d_vptrs);
void norm_ptrs_you(struct you * d_you);

static NHFILE files[3];static FILE *logs[3],*streams[3];
static unsigned char data[32768];static int opts[16],reentered;static void *growth;
static char tracebuf[131072],logbuf[131072],snapshotbuf[2048];
static void append(const char*format,...){va_list ap;va_start(ap,format);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),format,ap);va_end(ap);}
static int file_index(NHFILE*f){for(int i=0;i<3;i++)if(f==&files[i])return i;return -1;}
static int log_index(FILE*f){if(!f)return -1;for(int i=0;i<3;i++)if(f==logs[i])return i;return -2;}
void panic(const char*fmt,...){abort();}
void impossible(const char*fmt,...){abort();}
static void callback(int kind,int input,int field,int variant,NHFILE*f,void*bytes,const char*name,int count,size_t width){
 int i=file_index(f);size_t n=width*(size_t)count;if(n>sizeof data)abort();
 append("cb:%d:%d:%d:%d:f%d:%d:%d:%d:%ld:%ld:%s:%d:%lu;",kind,input,field,variant,i,f->mode,f->eof,log_index(f->fplog),f->rcount,f->wcount,name,count,(unsigned long)n);
 if(opts[5]&&!growth){growth=malloc(emscripten_get_heap_size()+32UL*1024*1024);if(!growth)abort();append("growth;");}
 if(opts[4]&&!reentered){reentered=1;int64 value=INT64_C(-9007199254740997);append("reenter:%s;",sfvalue_int64(&value));}
 if(opts[0]>0&&n>(size_t)opts[0])n=(size_t)opts[0];
 if(input){size_t got=fread(bytes,1,n,streams[i]);f->rcount+=got;if(got<n)f->eof=1;}else{size_t put=fwrite(bytes,1,n,streams[i]);f->wcount+=put;}
 if(opts[1])f->eof=1;if(opts[2])f->mode=opts[2];if(opts[3])f->fplog=opts[3]==1?0:logs[(i+1)%3];
}
static void fixture_000_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_arti_info(NHFILE*f,struct arti_info*p,const char*name){callback(0,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_nhrect(NHFILE*f,struct nhrect*p,const char*name){callback(1,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_branch(NHFILE*f,struct branch*p,const char*name){callback(2,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_branch(NHFILE*f,struct branch*p,const char*name){callback(2,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_branch(NHFILE*f,struct branch*p,const char*name){callback(2,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_branch(NHFILE*f,struct branch*p,const char*name){callback(2,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_branch(NHFILE*f,struct branch*p,const char*name){callback(2,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_branch(NHFILE*f,struct branch*p,const char*name){callback(2,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_branch(NHFILE*f,struct branch*p,const char*name){callback(2,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_branch(NHFILE*f,struct branch*p,const char*name){callback(2,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_bubble(NHFILE*f,struct bubble*p,const char*name){callback(3,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_cemetery(NHFILE*f,struct cemetery*p,const char*name){callback(4,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_context_info(NHFILE*f,struct context_info*p,const char*name){callback(5,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_nhcoord(NHFILE*f,struct nhcoord*p,const char*name){callback(6,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_damage(NHFILE*f,struct damage*p,const char*name){callback(7,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_damage(NHFILE*f,struct damage*p,const char*name){callback(7,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_damage(NHFILE*f,struct damage*p,const char*name){callback(7,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_damage(NHFILE*f,struct damage*p,const char*name){callback(7,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_damage(NHFILE*f,struct damage*p,const char*name){callback(7,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_damage(NHFILE*f,struct damage*p,const char*name){callback(7,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_damage(NHFILE*f,struct damage*p,const char*name){callback(7,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_damage(NHFILE*f,struct damage*p,const char*name){callback(7,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_dest_area(NHFILE*f,struct dest_area*p,const char*name){callback(8,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_dgn_topology(NHFILE*f,struct dgn_topology*p,const char*name){callback(9,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_dungeon(NHFILE*f,struct dungeon*p,const char*name){callback(10,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_d_level(NHFILE*f,struct d_level*p,const char*name){callback(11,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_ebones(NHFILE*f,struct ebones*p,const char*name){callback(12,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_edog(NHFILE*f,struct edog*p,const char*name){callback(13,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_edog(NHFILE*f,struct edog*p,const char*name){callback(13,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_edog(NHFILE*f,struct edog*p,const char*name){callback(13,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_edog(NHFILE*f,struct edog*p,const char*name){callback(13,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_edog(NHFILE*f,struct edog*p,const char*name){callback(13,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_edog(NHFILE*f,struct edog*p,const char*name){callback(13,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_edog(NHFILE*f,struct edog*p,const char*name){callback(13,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_edog(NHFILE*f,struct edog*p,const char*name){callback(13,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_egd(NHFILE*f,struct egd*p,const char*name){callback(14,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_egd(NHFILE*f,struct egd*p,const char*name){callback(14,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_egd(NHFILE*f,struct egd*p,const char*name){callback(14,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_egd(NHFILE*f,struct egd*p,const char*name){callback(14,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_egd(NHFILE*f,struct egd*p,const char*name){callback(14,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_egd(NHFILE*f,struct egd*p,const char*name){callback(14,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_egd(NHFILE*f,struct egd*p,const char*name){callback(14,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_egd(NHFILE*f,struct egd*p,const char*name){callback(14,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_emin(NHFILE*f,struct emin*p,const char*name){callback(15,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_emin(NHFILE*f,struct emin*p,const char*name){callback(15,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_emin(NHFILE*f,struct emin*p,const char*name){callback(15,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_emin(NHFILE*f,struct emin*p,const char*name){callback(15,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_emin(NHFILE*f,struct emin*p,const char*name){callback(15,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_emin(NHFILE*f,struct emin*p,const char*name){callback(15,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_emin(NHFILE*f,struct emin*p,const char*name){callback(15,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_emin(NHFILE*f,struct emin*p,const char*name){callback(15,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_engr(NHFILE*f,struct engr*p,const char*name){callback(16,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_engr(NHFILE*f,struct engr*p,const char*name){callback(16,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_engr(NHFILE*f,struct engr*p,const char*name){callback(16,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_engr(NHFILE*f,struct engr*p,const char*name){callback(16,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_engr(NHFILE*f,struct engr*p,const char*name){callback(16,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_engr(NHFILE*f,struct engr*p,const char*name){callback(16,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_engr(NHFILE*f,struct engr*p,const char*name){callback(16,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_engr(NHFILE*f,struct engr*p,const char*name){callback(16,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_epri(NHFILE*f,struct epri*p,const char*name){callback(17,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_epri(NHFILE*f,struct epri*p,const char*name){callback(17,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_epri(NHFILE*f,struct epri*p,const char*name){callback(17,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_epri(NHFILE*f,struct epri*p,const char*name){callback(17,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_epri(NHFILE*f,struct epri*p,const char*name){callback(17,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_epri(NHFILE*f,struct epri*p,const char*name){callback(17,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_epri(NHFILE*f,struct epri*p,const char*name){callback(17,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_epri(NHFILE*f,struct epri*p,const char*name){callback(17,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_eshk(NHFILE*f,struct eshk*p,const char*name){callback(18,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_fe(NHFILE*f,struct fe*p,const char*name){callback(19,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_fe(NHFILE*f,struct fe*p,const char*name){callback(19,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_fe(NHFILE*f,struct fe*p,const char*name){callback(19,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_fe(NHFILE*f,struct fe*p,const char*name){callback(19,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_fe(NHFILE*f,struct fe*p,const char*name){callback(19,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_fe(NHFILE*f,struct fe*p,const char*name){callback(19,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_fe(NHFILE*f,struct fe*p,const char*name){callback(19,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_fe(NHFILE*f,struct fe*p,const char*name){callback(19,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_flag(NHFILE*f,struct flag*p,const char*name){callback(20,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_flag(NHFILE*f,struct flag*p,const char*name){callback(20,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_flag(NHFILE*f,struct flag*p,const char*name){callback(20,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_flag(NHFILE*f,struct flag*p,const char*name){callback(20,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_flag(NHFILE*f,struct flag*p,const char*name){callback(20,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_flag(NHFILE*f,struct flag*p,const char*name){callback(20,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_flag(NHFILE*f,struct flag*p,const char*name){callback(20,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_flag(NHFILE*f,struct flag*p,const char*name){callback(20,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_fruit(NHFILE*f,struct fruit*p,const char*name){callback(21,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_gamelog_line(NHFILE*f,struct gamelog_line*p,const char*name){callback(22,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_kinfo(NHFILE*f,struct kinfo*p,const char*name){callback(23,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_levelflags(NHFILE*f,struct levelflags*p,const char*name){callback(24,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_ls_t(NHFILE*f,struct ls_t*p,const char*name){callback(25,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_linfo(NHFILE*f,struct linfo*p,const char*name){callback(26,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_mapseen_feat(NHFILE*f,struct mapseen_feat*p,const char*name){callback(27,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_mapseen_flags(NHFILE*f,struct mapseen_flags*p,const char*name){callback(28,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_mapseen_rooms(NHFILE*f,struct mapseen_rooms*p,const char*name){callback(29,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_mkroom(NHFILE*f,struct mkroom*p,const char*name){callback(30,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_monst(NHFILE*f,struct monst*p,const char*name){callback(31,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_monst(NHFILE*f,struct monst*p,const char*name){callback(31,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_monst(NHFILE*f,struct monst*p,const char*name){callback(31,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_monst(NHFILE*f,struct monst*p,const char*name){callback(31,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_monst(NHFILE*f,struct monst*p,const char*name){callback(31,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_monst(NHFILE*f,struct monst*p,const char*name){callback(31,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_monst(NHFILE*f,struct monst*p,const char*name){callback(31,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_monst(NHFILE*f,struct monst*p,const char*name){callback(31,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_mvitals(NHFILE*f,struct mvitals*p,const char*name){callback(32,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_obj(NHFILE*f,struct obj*p,const char*name){callback(33,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_obj(NHFILE*f,struct obj*p,const char*name){callback(33,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_obj(NHFILE*f,struct obj*p,const char*name){callback(33,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_obj(NHFILE*f,struct obj*p,const char*name){callback(33,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_obj(NHFILE*f,struct obj*p,const char*name){callback(33,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_obj(NHFILE*f,struct obj*p,const char*name){callback(33,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_obj(NHFILE*f,struct obj*p,const char*name){callback(33,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_obj(NHFILE*f,struct obj*p,const char*name){callback(33,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_objclass(NHFILE*f,struct objclass*p,const char*name){callback(34,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_q_score(NHFILE*f,struct q_score*p,const char*name){callback(35,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_rm(NHFILE*f,struct rm*p,const char*name){callback(36,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_rm(NHFILE*f,struct rm*p,const char*name){callback(36,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_rm(NHFILE*f,struct rm*p,const char*name){callback(36,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_rm(NHFILE*f,struct rm*p,const char*name){callback(36,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_rm(NHFILE*f,struct rm*p,const char*name){callback(36,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_rm(NHFILE*f,struct rm*p,const char*name){callback(36,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_rm(NHFILE*f,struct rm*p,const char*name){callback(36,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_rm(NHFILE*f,struct rm*p,const char*name){callback(36,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_spell(NHFILE*f,struct spell*p,const char*name){callback(37,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_spell(NHFILE*f,struct spell*p,const char*name){callback(37,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_spell(NHFILE*f,struct spell*p,const char*name){callback(37,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_spell(NHFILE*f,struct spell*p,const char*name){callback(37,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_spell(NHFILE*f,struct spell*p,const char*name){callback(37,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_spell(NHFILE*f,struct spell*p,const char*name){callback(37,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_spell(NHFILE*f,struct spell*p,const char*name){callback(37,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_spell(NHFILE*f,struct spell*p,const char*name){callback(37,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_stairway(NHFILE*f,struct stairway*p,const char*name){callback(38,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_s_level(NHFILE*f,struct s_level*p,const char*name){callback(39,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_trap(NHFILE*f,struct trap*p,const char*name){callback(40,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_trap(NHFILE*f,struct trap*p,const char*name){callback(40,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_trap(NHFILE*f,struct trap*p,const char*name){callback(40,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_trap(NHFILE*f,struct trap*p,const char*name){callback(40,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_trap(NHFILE*f,struct trap*p,const char*name){callback(40,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_trap(NHFILE*f,struct trap*p,const char*name){callback(40,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_trap(NHFILE*f,struct trap*p,const char*name){callback(40,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_trap(NHFILE*f,struct trap*p,const char*name){callback(40,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_you(NHFILE*f,struct you*p,const char*name){callback(41,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_you(NHFILE*f,struct you*p,const char*name){callback(41,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_you(NHFILE*f,struct you*p,const char*name){callback(41,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_you(NHFILE*f,struct you*p,const char*name){callback(41,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_you(NHFILE*f,struct you*p,const char*name){callback(41,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_you(NHFILE*f,struct you*p,const char*name){callback(41,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_you(NHFILE*f,struct you*p,const char*name){callback(41,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_you(NHFILE*f,struct you*p,const char*name){callback(41,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_any(NHFILE*f,union any*p,const char*name){callback(42,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_any(NHFILE*f,union any*p,const char*name){callback(42,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_any(NHFILE*f,union any*p,const char*name){callback(42,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_any(NHFILE*f,union any*p,const char*name){callback(42,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_any(NHFILE*f,union any*p,const char*name){callback(42,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_any(NHFILE*f,union any*p,const char*name){callback(42,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_any(NHFILE*f,union any*p,const char*name){callback(42,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_any(NHFILE*f,union any*p,const char*name){callback(42,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_aligntyp(NHFILE*f,aligntyp*p,const char*name){callback(43,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_boolean(NHFILE*f,boolean*p,const char*name){callback(44,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_boolean(NHFILE*f,boolean*p,const char*name){callback(44,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_boolean(NHFILE*f,boolean*p,const char*name){callback(44,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_boolean(NHFILE*f,boolean*p,const char*name){callback(44,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_boolean(NHFILE*f,boolean*p,const char*name){callback(44,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_boolean(NHFILE*f,boolean*p,const char*name){callback(44,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_boolean(NHFILE*f,boolean*p,const char*name){callback(44,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_boolean(NHFILE*f,boolean*p,const char*name){callback(44,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_coordxy(NHFILE*f,coordxy*p,const char*name){callback(45,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_int(NHFILE*f,int*p,const char*name){callback(46,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_int(NHFILE*f,int*p,const char*name){callback(46,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_int(NHFILE*f,int*p,const char*name){callback(46,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_int(NHFILE*f,int*p,const char*name){callback(46,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_int(NHFILE*f,int*p,const char*name){callback(46,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_int(NHFILE*f,int*p,const char*name){callback(46,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_int(NHFILE*f,int*p,const char*name){callback(46,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_int(NHFILE*f,int*p,const char*name){callback(46,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_int16(NHFILE*f,int16*p,const char*name){callback(47,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_int16(NHFILE*f,int16*p,const char*name){callback(47,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_int16(NHFILE*f,int16*p,const char*name){callback(47,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_int16(NHFILE*f,int16*p,const char*name){callback(47,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_int16(NHFILE*f,int16*p,const char*name){callback(47,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_int16(NHFILE*f,int16*p,const char*name){callback(47,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_int16(NHFILE*f,int16*p,const char*name){callback(47,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_int16(NHFILE*f,int16*p,const char*name){callback(47,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_int32(NHFILE*f,int32*p,const char*name){callback(48,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_int32(NHFILE*f,int32*p,const char*name){callback(48,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_int32(NHFILE*f,int32*p,const char*name){callback(48,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_int32(NHFILE*f,int32*p,const char*name){callback(48,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_int32(NHFILE*f,int32*p,const char*name){callback(48,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_int32(NHFILE*f,int32*p,const char*name){callback(48,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_int32(NHFILE*f,int32*p,const char*name){callback(48,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_int32(NHFILE*f,int32*p,const char*name){callback(48,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_int64(NHFILE*f,int64*p,const char*name){callback(49,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_int64(NHFILE*f,int64*p,const char*name){callback(49,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_int64(NHFILE*f,int64*p,const char*name){callback(49,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_int64(NHFILE*f,int64*p,const char*name){callback(49,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_int64(NHFILE*f,int64*p,const char*name){callback(49,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_int64(NHFILE*f,int64*p,const char*name){callback(49,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_int64(NHFILE*f,int64*p,const char*name){callback(49,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_int64(NHFILE*f,int64*p,const char*name){callback(49,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_long(NHFILE*f,long*p,const char*name){callback(50,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_long(NHFILE*f,long*p,const char*name){callback(50,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_long(NHFILE*f,long*p,const char*name){callback(50,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_long(NHFILE*f,long*p,const char*name){callback(50,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_long(NHFILE*f,long*p,const char*name){callback(50,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_long(NHFILE*f,long*p,const char*name){callback(50,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_long(NHFILE*f,long*p,const char*name){callback(50,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_long(NHFILE*f,long*p,const char*name){callback(50,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_schar(NHFILE*f,schar*p,const char*name){callback(51,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_schar(NHFILE*f,schar*p,const char*name){callback(51,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_schar(NHFILE*f,schar*p,const char*name){callback(51,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_schar(NHFILE*f,schar*p,const char*name){callback(51,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_schar(NHFILE*f,schar*p,const char*name){callback(51,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_schar(NHFILE*f,schar*p,const char*name){callback(51,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_schar(NHFILE*f,schar*p,const char*name){callback(51,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_schar(NHFILE*f,schar*p,const char*name){callback(51,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_short(NHFILE*f,short*p,const char*name){callback(52,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_short(NHFILE*f,short*p,const char*name){callback(52,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_short(NHFILE*f,short*p,const char*name){callback(52,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_short(NHFILE*f,short*p,const char*name){callback(52,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_short(NHFILE*f,short*p,const char*name){callback(52,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_short(NHFILE*f,short*p,const char*name){callback(52,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_short(NHFILE*f,short*p,const char*name){callback(52,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_short(NHFILE*f,short*p,const char*name){callback(52,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_size_t(NHFILE*f,size_t*p,const char*name){callback(53,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_size_t(NHFILE*f,size_t*p,const char*name){callback(53,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_size_t(NHFILE*f,size_t*p,const char*name){callback(53,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_size_t(NHFILE*f,size_t*p,const char*name){callback(53,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_size_t(NHFILE*f,size_t*p,const char*name){callback(53,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_size_t(NHFILE*f,size_t*p,const char*name){callback(53,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_size_t(NHFILE*f,size_t*p,const char*name){callback(53,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_size_t(NHFILE*f,size_t*p,const char*name){callback(53,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_time_t(NHFILE*f,time_t*p,const char*name){callback(54,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_time_t(NHFILE*f,time_t*p,const char*name){callback(54,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_time_t(NHFILE*f,time_t*p,const char*name){callback(54,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_time_t(NHFILE*f,time_t*p,const char*name){callback(54,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_time_t(NHFILE*f,time_t*p,const char*name){callback(54,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_time_t(NHFILE*f,time_t*p,const char*name){callback(54,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_time_t(NHFILE*f,time_t*p,const char*name){callback(54,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_time_t(NHFILE*f,time_t*p,const char*name){callback(54,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_uchar(NHFILE*f,uchar*p,const char*name){callback(55,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_uchar(NHFILE*f,uchar*p,const char*name){callback(55,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_uchar(NHFILE*f,uchar*p,const char*name){callback(55,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_uchar(NHFILE*f,uchar*p,const char*name){callback(55,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_uchar(NHFILE*f,uchar*p,const char*name){callback(55,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_uchar(NHFILE*f,uchar*p,const char*name){callback(55,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_uchar(NHFILE*f,uchar*p,const char*name){callback(55,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_uchar(NHFILE*f,uchar*p,const char*name){callback(55,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_uint16(NHFILE*f,uint16*p,const char*name){callback(56,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_uint16(NHFILE*f,uint16*p,const char*name){callback(56,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_uint16(NHFILE*f,uint16*p,const char*name){callback(56,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_uint16(NHFILE*f,uint16*p,const char*name){callback(56,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_uint16(NHFILE*f,uint16*p,const char*name){callback(56,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_uint16(NHFILE*f,uint16*p,const char*name){callback(56,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_uint16(NHFILE*f,uint16*p,const char*name){callback(56,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_uint16(NHFILE*f,uint16*p,const char*name){callback(56,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_uint32(NHFILE*f,uint32*p,const char*name){callback(57,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_uint32(NHFILE*f,uint32*p,const char*name){callback(57,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_uint32(NHFILE*f,uint32*p,const char*name){callback(57,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_uint32(NHFILE*f,uint32*p,const char*name){callback(57,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_uint32(NHFILE*f,uint32*p,const char*name){callback(57,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_uint32(NHFILE*f,uint32*p,const char*name){callback(57,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_uint32(NHFILE*f,uint32*p,const char*name){callback(57,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_uint32(NHFILE*f,uint32*p,const char*name){callback(57,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_uint64(NHFILE*f,uint64*p,const char*name){callback(58,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_uint64(NHFILE*f,uint64*p,const char*name){callback(58,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_uint64(NHFILE*f,uint64*p,const char*name){callback(58,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_uint64(NHFILE*f,uint64*p,const char*name){callback(58,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_uint64(NHFILE*f,uint64*p,const char*name){callback(58,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_uint64(NHFILE*f,uint64*p,const char*name){callback(58,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_uint64(NHFILE*f,uint64*p,const char*name){callback(58,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_uint64(NHFILE*f,uint64*p,const char*name){callback(58,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_ulong(NHFILE*f,ulong*p,const char*name){callback(59,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_ulong(NHFILE*f,ulong*p,const char*name){callback(59,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_ulong(NHFILE*f,ulong*p,const char*name){callback(59,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_ulong(NHFILE*f,ulong*p,const char*name){callback(59,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_ulong(NHFILE*f,ulong*p,const char*name){callback(59,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_ulong(NHFILE*f,ulong*p,const char*name){callback(59,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_ulong(NHFILE*f,ulong*p,const char*name){callback(59,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_ulong(NHFILE*f,ulong*p,const char*name){callback(59,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_unsigned(NHFILE*f,unsigned*p,const char*name){callback(60,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_ushort(NHFILE*f,ushort*p,const char*name){callback(61,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_ushort(NHFILE*f,ushort*p,const char*name){callback(61,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_ushort(NHFILE*f,ushort*p,const char*name){callback(61,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_ushort(NHFILE*f,ushort*p,const char*name){callback(61,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_ushort(NHFILE*f,ushort*p,const char*name){callback(61,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_ushort(NHFILE*f,ushort*p,const char*name){callback(61,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_ushort(NHFILE*f,ushort*p,const char*name){callback(61,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_ushort(NHFILE*f,ushort*p,const char*name){callback(61,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_xint16(NHFILE*f,xint16*p,const char*name){callback(62,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_xint16(NHFILE*f,xint16*p,const char*name){callback(62,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_xint16(NHFILE*f,xint16*p,const char*name){callback(62,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_xint16(NHFILE*f,xint16*p,const char*name){callback(62,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_xint16(NHFILE*f,xint16*p,const char*name){callback(62,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_xint16(NHFILE*f,xint16*p,const char*name){callback(62,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_xint16(NHFILE*f,xint16*p,const char*name){callback(62,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_xint16(NHFILE*f,xint16*p,const char*name){callback(62,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_xint8(NHFILE*f,xint8*p,const char*name){callback(63,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_xint8(NHFILE*f,xint8*p,const char*name){callback(63,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_xint8(NHFILE*f,xint8*p,const char*name){callback(63,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_xint8(NHFILE*f,xint8*p,const char*name){callback(63,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_xint8(NHFILE*f,xint8*p,const char*name){callback(63,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_xint8(NHFILE*f,xint8*p,const char*name){callback(63,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_xint8(NHFILE*f,xint8*p,const char*name){callback(63,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_xint8(NHFILE*f,xint8*p,const char*name){callback(63,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,0,0,0,f,p,name,count,1);}
static void fixture_001_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,0,0,1,f,p,name,count,1);}
static void fixture_010_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,0,1,0,f,p,name,count,1);}
static void fixture_011_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,0,1,1,f,p,name,count,1);}
static void fixture_100_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,1,0,0,f,p,name,count,1);}
static void fixture_101_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,1,0,1,f,p,name,count,1);}
static void fixture_110_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,1,1,0,f,p,name,count,1);}
static void fixture_111_bitfield(NHFILE*f,uint8_t*p,const char*name,int count){callback(64,1,1,1,f,p,name,count,1);}
static void fixture_000_char(NHFILE*f,char*p,const char*name,int count){callback(65,0,0,0,f,p,name,count,sizeof *p);}
static void fixture_001_char(NHFILE*f,char*p,const char*name,int count){callback(65,0,0,1,f,p,name,count,sizeof *p);}
static void fixture_010_char(NHFILE*f,char*p,const char*name,int count){callback(65,0,1,0,f,p,name,count,sizeof *p);}
static void fixture_011_char(NHFILE*f,char*p,const char*name,int count){callback(65,0,1,1,f,p,name,count,sizeof *p);}
static void fixture_100_char(NHFILE*f,char*p,const char*name,int count){callback(65,1,0,0,f,p,name,count,sizeof *p);}
static void fixture_101_char(NHFILE*f,char*p,const char*name,int count){callback(65,1,0,1,f,p,name,count,sizeof *p);}
static void fixture_110_char(NHFILE*f,char*p,const char*name,int count){callback(65,1,1,0,f,p,name,count,sizeof *p);}
static void fixture_111_char(NHFILE*f,char*p,const char*name,int count){callback(65,1,1,1,f,p,name,count,sizeof *p);}
static void fixture_000_genericptr(NHFILE*f,void **p,const char*name){callback(66,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_genericptr(NHFILE*f,void **p,const char*name){callback(66,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_genericptr(NHFILE*f,void **p,const char*name){callback(66,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_genericptr(NHFILE*f,void **p,const char*name){callback(66,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_genericptr(NHFILE*f,void **p,const char*name){callback(66,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_genericptr(NHFILE*f,void **p,const char*name){callback(66,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_genericptr(NHFILE*f,void **p,const char*name){callback(66,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_genericptr(NHFILE*f,void **p,const char*name){callback(66,1,1,1,f,p,name,1,sizeof *p);}
static void fixture_000_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,0,0,0,f,p,name,1,sizeof *p);}
static void fixture_001_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,0,0,1,f,p,name,1,sizeof *p);}
static void fixture_010_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,0,1,0,f,p,name,1,sizeof *p);}
static void fixture_011_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,0,1,1,f,p,name,1,sizeof *p);}
static void fixture_100_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,1,0,0,f,p,name,1,sizeof *p);}
static void fixture_101_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,1,0,1,f,p,name,1,sizeof *p);}
static void fixture_110_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,1,1,0,f,p,name,1,sizeof *p);}
static void fixture_111_version_info(NHFILE*f,struct version_info*p,const char*name){callback(67,1,1,1,f,p,name,1,sizeof *p);}
struct sf_structlevel_procs historical_sfo_procs={.ext="fixture000",.fn={
.sf_arti_info=fixture_000_arti_info,
.sf_nhrect=fixture_000_nhrect,
.sf_branch=fixture_000_branch,
.sf_bubble=fixture_000_bubble,
.sf_cemetery=fixture_000_cemetery,
.sf_context_info=fixture_000_context_info,
.sf_nhcoord=fixture_000_nhcoord,
.sf_damage=fixture_000_damage,
.sf_dest_area=fixture_000_dest_area,
.sf_dgn_topology=fixture_000_dgn_topology,
.sf_dungeon=fixture_000_dungeon,
.sf_d_level=fixture_000_d_level,
.sf_ebones=fixture_000_ebones,
.sf_edog=fixture_000_edog,
.sf_egd=fixture_000_egd,
.sf_emin=fixture_000_emin,
.sf_engr=fixture_000_engr,
.sf_epri=fixture_000_epri,
.sf_eshk=fixture_000_eshk,
.sf_fe=fixture_000_fe,
.sf_flag=fixture_000_flag,
.sf_fruit=fixture_000_fruit,
.sf_gamelog_line=fixture_000_gamelog_line,
.sf_kinfo=fixture_000_kinfo,
.sf_levelflags=fixture_000_levelflags,
.sf_ls_t=fixture_000_ls_t,
.sf_linfo=fixture_000_linfo,
.sf_mapseen_feat=fixture_000_mapseen_feat,
.sf_mapseen_flags=fixture_000_mapseen_flags,
.sf_mapseen_rooms=fixture_000_mapseen_rooms,
.sf_mkroom=fixture_000_mkroom,
.sf_monst=fixture_000_monst,
.sf_mvitals=fixture_000_mvitals,
.sf_obj=fixture_000_obj,
.sf_objclass=fixture_000_objclass,
.sf_q_score=fixture_000_q_score,
.sf_rm=fixture_000_rm,
.sf_spell=fixture_000_spell,
.sf_stairway=fixture_000_stairway,
.sf_s_level=fixture_000_s_level,
.sf_trap=fixture_000_trap,
.sf_you=fixture_000_you,
.sf_any=fixture_000_any,
.sf_aligntyp=fixture_000_aligntyp,
.sf_boolean=fixture_000_boolean,
.sf_coordxy=fixture_000_coordxy,
.sf_int=fixture_000_int,
.sf_int16=fixture_000_int16,
.sf_int32=fixture_000_int32,
.sf_int64=fixture_000_int64,
.sf_long=fixture_000_long,
.sf_schar=fixture_000_schar,
.sf_short=fixture_000_short,
.sf_size_t=fixture_000_size_t,
.sf_time_t=fixture_000_time_t,
.sf_uchar=fixture_000_uchar,
.sf_uint16=fixture_000_uint16,
.sf_uint32=fixture_000_uint32,
.sf_uint64=fixture_000_uint64,
.sf_ulong=fixture_000_ulong,
.sf_unsigned=fixture_000_unsigned,
.sf_ushort=fixture_000_ushort,
.sf_xint16=fixture_000_xint16,
.sf_xint8=fixture_000_xint8,
.sf_bitfield=fixture_000_bitfield,
.sf_char=fixture_000_char,
.sf_genericptr=fixture_000_genericptr,
.sf_version_info=fixture_000_version_info,
}};
struct sf_structlevel_procs fixture_001_table={.ext="fixture001",.fn={
.sf_arti_info=fixture_001_arti_info,
.sf_nhrect=fixture_001_nhrect,
.sf_branch=fixture_001_branch,
.sf_bubble=fixture_001_bubble,
.sf_cemetery=fixture_001_cemetery,
.sf_context_info=fixture_001_context_info,
.sf_nhcoord=fixture_001_nhcoord,
.sf_damage=fixture_001_damage,
.sf_dest_area=fixture_001_dest_area,
.sf_dgn_topology=fixture_001_dgn_topology,
.sf_dungeon=fixture_001_dungeon,
.sf_d_level=fixture_001_d_level,
.sf_ebones=fixture_001_ebones,
.sf_edog=fixture_001_edog,
.sf_egd=fixture_001_egd,
.sf_emin=fixture_001_emin,
.sf_engr=fixture_001_engr,
.sf_epri=fixture_001_epri,
.sf_eshk=fixture_001_eshk,
.sf_fe=fixture_001_fe,
.sf_flag=fixture_001_flag,
.sf_fruit=fixture_001_fruit,
.sf_gamelog_line=fixture_001_gamelog_line,
.sf_kinfo=fixture_001_kinfo,
.sf_levelflags=fixture_001_levelflags,
.sf_ls_t=fixture_001_ls_t,
.sf_linfo=fixture_001_linfo,
.sf_mapseen_feat=fixture_001_mapseen_feat,
.sf_mapseen_flags=fixture_001_mapseen_flags,
.sf_mapseen_rooms=fixture_001_mapseen_rooms,
.sf_mkroom=fixture_001_mkroom,
.sf_monst=fixture_001_monst,
.sf_mvitals=fixture_001_mvitals,
.sf_obj=fixture_001_obj,
.sf_objclass=fixture_001_objclass,
.sf_q_score=fixture_001_q_score,
.sf_rm=fixture_001_rm,
.sf_spell=fixture_001_spell,
.sf_stairway=fixture_001_stairway,
.sf_s_level=fixture_001_s_level,
.sf_trap=fixture_001_trap,
.sf_you=fixture_001_you,
.sf_any=fixture_001_any,
.sf_aligntyp=fixture_001_aligntyp,
.sf_boolean=fixture_001_boolean,
.sf_coordxy=fixture_001_coordxy,
.sf_int=fixture_001_int,
.sf_int16=fixture_001_int16,
.sf_int32=fixture_001_int32,
.sf_int64=fixture_001_int64,
.sf_long=fixture_001_long,
.sf_schar=fixture_001_schar,
.sf_short=fixture_001_short,
.sf_size_t=fixture_001_size_t,
.sf_time_t=fixture_001_time_t,
.sf_uchar=fixture_001_uchar,
.sf_uint16=fixture_001_uint16,
.sf_uint32=fixture_001_uint32,
.sf_uint64=fixture_001_uint64,
.sf_ulong=fixture_001_ulong,
.sf_unsigned=fixture_001_unsigned,
.sf_ushort=fixture_001_ushort,
.sf_xint16=fixture_001_xint16,
.sf_xint8=fixture_001_xint8,
.sf_bitfield=fixture_001_bitfield,
.sf_char=fixture_001_char,
.sf_genericptr=fixture_001_genericptr,
.sf_version_info=fixture_001_version_info,
}};
struct sf_structlevel_procs historical_sfi_procs={.ext="fixture100",.fn={
.sf_arti_info=fixture_100_arti_info,
.sf_nhrect=fixture_100_nhrect,
.sf_branch=fixture_100_branch,
.sf_bubble=fixture_100_bubble,
.sf_cemetery=fixture_100_cemetery,
.sf_context_info=fixture_100_context_info,
.sf_nhcoord=fixture_100_nhcoord,
.sf_damage=fixture_100_damage,
.sf_dest_area=fixture_100_dest_area,
.sf_dgn_topology=fixture_100_dgn_topology,
.sf_dungeon=fixture_100_dungeon,
.sf_d_level=fixture_100_d_level,
.sf_ebones=fixture_100_ebones,
.sf_edog=fixture_100_edog,
.sf_egd=fixture_100_egd,
.sf_emin=fixture_100_emin,
.sf_engr=fixture_100_engr,
.sf_epri=fixture_100_epri,
.sf_eshk=fixture_100_eshk,
.sf_fe=fixture_100_fe,
.sf_flag=fixture_100_flag,
.sf_fruit=fixture_100_fruit,
.sf_gamelog_line=fixture_100_gamelog_line,
.sf_kinfo=fixture_100_kinfo,
.sf_levelflags=fixture_100_levelflags,
.sf_ls_t=fixture_100_ls_t,
.sf_linfo=fixture_100_linfo,
.sf_mapseen_feat=fixture_100_mapseen_feat,
.sf_mapseen_flags=fixture_100_mapseen_flags,
.sf_mapseen_rooms=fixture_100_mapseen_rooms,
.sf_mkroom=fixture_100_mkroom,
.sf_monst=fixture_100_monst,
.sf_mvitals=fixture_100_mvitals,
.sf_obj=fixture_100_obj,
.sf_objclass=fixture_100_objclass,
.sf_q_score=fixture_100_q_score,
.sf_rm=fixture_100_rm,
.sf_spell=fixture_100_spell,
.sf_stairway=fixture_100_stairway,
.sf_s_level=fixture_100_s_level,
.sf_trap=fixture_100_trap,
.sf_you=fixture_100_you,
.sf_any=fixture_100_any,
.sf_aligntyp=fixture_100_aligntyp,
.sf_boolean=fixture_100_boolean,
.sf_coordxy=fixture_100_coordxy,
.sf_int=fixture_100_int,
.sf_int16=fixture_100_int16,
.sf_int32=fixture_100_int32,
.sf_int64=fixture_100_int64,
.sf_long=fixture_100_long,
.sf_schar=fixture_100_schar,
.sf_short=fixture_100_short,
.sf_size_t=fixture_100_size_t,
.sf_time_t=fixture_100_time_t,
.sf_uchar=fixture_100_uchar,
.sf_uint16=fixture_100_uint16,
.sf_uint32=fixture_100_uint32,
.sf_uint64=fixture_100_uint64,
.sf_ulong=fixture_100_ulong,
.sf_unsigned=fixture_100_unsigned,
.sf_ushort=fixture_100_ushort,
.sf_xint16=fixture_100_xint16,
.sf_xint8=fixture_100_xint8,
.sf_bitfield=fixture_100_bitfield,
.sf_char=fixture_100_char,
.sf_genericptr=fixture_100_genericptr,
.sf_version_info=fixture_100_version_info,
}};
struct sf_structlevel_procs fixture_101_table={.ext="fixture101",.fn={
.sf_arti_info=fixture_101_arti_info,
.sf_nhrect=fixture_101_nhrect,
.sf_branch=fixture_101_branch,
.sf_bubble=fixture_101_bubble,
.sf_cemetery=fixture_101_cemetery,
.sf_context_info=fixture_101_context_info,
.sf_nhcoord=fixture_101_nhcoord,
.sf_damage=fixture_101_damage,
.sf_dest_area=fixture_101_dest_area,
.sf_dgn_topology=fixture_101_dgn_topology,
.sf_dungeon=fixture_101_dungeon,
.sf_d_level=fixture_101_d_level,
.sf_ebones=fixture_101_ebones,
.sf_edog=fixture_101_edog,
.sf_egd=fixture_101_egd,
.sf_emin=fixture_101_emin,
.sf_engr=fixture_101_engr,
.sf_epri=fixture_101_epri,
.sf_eshk=fixture_101_eshk,
.sf_fe=fixture_101_fe,
.sf_flag=fixture_101_flag,
.sf_fruit=fixture_101_fruit,
.sf_gamelog_line=fixture_101_gamelog_line,
.sf_kinfo=fixture_101_kinfo,
.sf_levelflags=fixture_101_levelflags,
.sf_ls_t=fixture_101_ls_t,
.sf_linfo=fixture_101_linfo,
.sf_mapseen_feat=fixture_101_mapseen_feat,
.sf_mapseen_flags=fixture_101_mapseen_flags,
.sf_mapseen_rooms=fixture_101_mapseen_rooms,
.sf_mkroom=fixture_101_mkroom,
.sf_monst=fixture_101_monst,
.sf_mvitals=fixture_101_mvitals,
.sf_obj=fixture_101_obj,
.sf_objclass=fixture_101_objclass,
.sf_q_score=fixture_101_q_score,
.sf_rm=fixture_101_rm,
.sf_spell=fixture_101_spell,
.sf_stairway=fixture_101_stairway,
.sf_s_level=fixture_101_s_level,
.sf_trap=fixture_101_trap,
.sf_you=fixture_101_you,
.sf_any=fixture_101_any,
.sf_aligntyp=fixture_101_aligntyp,
.sf_boolean=fixture_101_boolean,
.sf_coordxy=fixture_101_coordxy,
.sf_int=fixture_101_int,
.sf_int16=fixture_101_int16,
.sf_int32=fixture_101_int32,
.sf_int64=fixture_101_int64,
.sf_long=fixture_101_long,
.sf_schar=fixture_101_schar,
.sf_short=fixture_101_short,
.sf_size_t=fixture_101_size_t,
.sf_time_t=fixture_101_time_t,
.sf_uchar=fixture_101_uchar,
.sf_uint16=fixture_101_uint16,
.sf_uint32=fixture_101_uint32,
.sf_uint64=fixture_101_uint64,
.sf_ulong=fixture_101_ulong,
.sf_unsigned=fixture_101_unsigned,
.sf_ushort=fixture_101_ushort,
.sf_xint16=fixture_101_xint16,
.sf_xint8=fixture_101_xint8,
.sf_bitfield=fixture_101_bitfield,
.sf_char=fixture_101_char,
.sf_genericptr=fixture_101_genericptr,
.sf_version_info=fixture_101_version_info,
}};
struct sf_fieldlevel_procs fixture_010_table={.ext="fixture010",.fn_x={
.sf_arti_info=fixture_010_arti_info,
.sf_nhrect=fixture_010_nhrect,
.sf_branch=fixture_010_branch,
.sf_bubble=fixture_010_bubble,
.sf_cemetery=fixture_010_cemetery,
.sf_context_info=fixture_010_context_info,
.sf_nhcoord=fixture_010_nhcoord,
.sf_damage=fixture_010_damage,
.sf_dest_area=fixture_010_dest_area,
.sf_dgn_topology=fixture_010_dgn_topology,
.sf_dungeon=fixture_010_dungeon,
.sf_d_level=fixture_010_d_level,
.sf_ebones=fixture_010_ebones,
.sf_edog=fixture_010_edog,
.sf_egd=fixture_010_egd,
.sf_emin=fixture_010_emin,
.sf_engr=fixture_010_engr,
.sf_epri=fixture_010_epri,
.sf_eshk=fixture_010_eshk,
.sf_fe=fixture_010_fe,
.sf_flag=fixture_010_flag,
.sf_fruit=fixture_010_fruit,
.sf_gamelog_line=fixture_010_gamelog_line,
.sf_kinfo=fixture_010_kinfo,
.sf_levelflags=fixture_010_levelflags,
.sf_ls_t=fixture_010_ls_t,
.sf_linfo=fixture_010_linfo,
.sf_mapseen_feat=fixture_010_mapseen_feat,
.sf_mapseen_flags=fixture_010_mapseen_flags,
.sf_mapseen_rooms=fixture_010_mapseen_rooms,
.sf_mkroom=fixture_010_mkroom,
.sf_monst=fixture_010_monst,
.sf_mvitals=fixture_010_mvitals,
.sf_obj=fixture_010_obj,
.sf_objclass=fixture_010_objclass,
.sf_q_score=fixture_010_q_score,
.sf_rm=fixture_010_rm,
.sf_spell=fixture_010_spell,
.sf_stairway=fixture_010_stairway,
.sf_s_level=fixture_010_s_level,
.sf_trap=fixture_010_trap,
.sf_you=fixture_010_you,
.sf_any=fixture_010_any,
.sf_aligntyp=fixture_010_aligntyp,
.sf_boolean=fixture_010_boolean,
.sf_coordxy=fixture_010_coordxy,
.sf_int=fixture_010_int,
.sf_int16=fixture_010_int16,
.sf_int32=fixture_010_int32,
.sf_int64=fixture_010_int64,
.sf_long=fixture_010_long,
.sf_schar=fixture_010_schar,
.sf_short=fixture_010_short,
.sf_size_t=fixture_010_size_t,
.sf_time_t=fixture_010_time_t,
.sf_uchar=fixture_010_uchar,
.sf_uint16=fixture_010_uint16,
.sf_uint32=fixture_010_uint32,
.sf_uint64=fixture_010_uint64,
.sf_ulong=fixture_010_ulong,
.sf_unsigned=fixture_010_unsigned,
.sf_ushort=fixture_010_ushort,
.sf_xint16=fixture_010_xint16,
.sf_xint8=fixture_010_xint8,
.sf_bitfield=fixture_010_bitfield,
.sf_char=fixture_010_char,
.sf_genericptr=fixture_010_genericptr,
.sf_version_info=fixture_010_version_info,
}};
struct sf_fieldlevel_procs fixture_011_table={.ext="fixture011",.fn_x={
.sf_arti_info=fixture_011_arti_info,
.sf_nhrect=fixture_011_nhrect,
.sf_branch=fixture_011_branch,
.sf_bubble=fixture_011_bubble,
.sf_cemetery=fixture_011_cemetery,
.sf_context_info=fixture_011_context_info,
.sf_nhcoord=fixture_011_nhcoord,
.sf_damage=fixture_011_damage,
.sf_dest_area=fixture_011_dest_area,
.sf_dgn_topology=fixture_011_dgn_topology,
.sf_dungeon=fixture_011_dungeon,
.sf_d_level=fixture_011_d_level,
.sf_ebones=fixture_011_ebones,
.sf_edog=fixture_011_edog,
.sf_egd=fixture_011_egd,
.sf_emin=fixture_011_emin,
.sf_engr=fixture_011_engr,
.sf_epri=fixture_011_epri,
.sf_eshk=fixture_011_eshk,
.sf_fe=fixture_011_fe,
.sf_flag=fixture_011_flag,
.sf_fruit=fixture_011_fruit,
.sf_gamelog_line=fixture_011_gamelog_line,
.sf_kinfo=fixture_011_kinfo,
.sf_levelflags=fixture_011_levelflags,
.sf_ls_t=fixture_011_ls_t,
.sf_linfo=fixture_011_linfo,
.sf_mapseen_feat=fixture_011_mapseen_feat,
.sf_mapseen_flags=fixture_011_mapseen_flags,
.sf_mapseen_rooms=fixture_011_mapseen_rooms,
.sf_mkroom=fixture_011_mkroom,
.sf_monst=fixture_011_monst,
.sf_mvitals=fixture_011_mvitals,
.sf_obj=fixture_011_obj,
.sf_objclass=fixture_011_objclass,
.sf_q_score=fixture_011_q_score,
.sf_rm=fixture_011_rm,
.sf_spell=fixture_011_spell,
.sf_stairway=fixture_011_stairway,
.sf_s_level=fixture_011_s_level,
.sf_trap=fixture_011_trap,
.sf_you=fixture_011_you,
.sf_any=fixture_011_any,
.sf_aligntyp=fixture_011_aligntyp,
.sf_boolean=fixture_011_boolean,
.sf_coordxy=fixture_011_coordxy,
.sf_int=fixture_011_int,
.sf_int16=fixture_011_int16,
.sf_int32=fixture_011_int32,
.sf_int64=fixture_011_int64,
.sf_long=fixture_011_long,
.sf_schar=fixture_011_schar,
.sf_short=fixture_011_short,
.sf_size_t=fixture_011_size_t,
.sf_time_t=fixture_011_time_t,
.sf_uchar=fixture_011_uchar,
.sf_uint16=fixture_011_uint16,
.sf_uint32=fixture_011_uint32,
.sf_uint64=fixture_011_uint64,
.sf_ulong=fixture_011_ulong,
.sf_unsigned=fixture_011_unsigned,
.sf_ushort=fixture_011_ushort,
.sf_xint16=fixture_011_xint16,
.sf_xint8=fixture_011_xint8,
.sf_bitfield=fixture_011_bitfield,
.sf_char=fixture_011_char,
.sf_genericptr=fixture_011_genericptr,
.sf_version_info=fixture_011_version_info,
}};
struct sf_fieldlevel_procs fixture_110_table={.ext="fixture110",.fn_x={
.sf_arti_info=fixture_110_arti_info,
.sf_nhrect=fixture_110_nhrect,
.sf_branch=fixture_110_branch,
.sf_bubble=fixture_110_bubble,
.sf_cemetery=fixture_110_cemetery,
.sf_context_info=fixture_110_context_info,
.sf_nhcoord=fixture_110_nhcoord,
.sf_damage=fixture_110_damage,
.sf_dest_area=fixture_110_dest_area,
.sf_dgn_topology=fixture_110_dgn_topology,
.sf_dungeon=fixture_110_dungeon,
.sf_d_level=fixture_110_d_level,
.sf_ebones=fixture_110_ebones,
.sf_edog=fixture_110_edog,
.sf_egd=fixture_110_egd,
.sf_emin=fixture_110_emin,
.sf_engr=fixture_110_engr,
.sf_epri=fixture_110_epri,
.sf_eshk=fixture_110_eshk,
.sf_fe=fixture_110_fe,
.sf_flag=fixture_110_flag,
.sf_fruit=fixture_110_fruit,
.sf_gamelog_line=fixture_110_gamelog_line,
.sf_kinfo=fixture_110_kinfo,
.sf_levelflags=fixture_110_levelflags,
.sf_ls_t=fixture_110_ls_t,
.sf_linfo=fixture_110_linfo,
.sf_mapseen_feat=fixture_110_mapseen_feat,
.sf_mapseen_flags=fixture_110_mapseen_flags,
.sf_mapseen_rooms=fixture_110_mapseen_rooms,
.sf_mkroom=fixture_110_mkroom,
.sf_monst=fixture_110_monst,
.sf_mvitals=fixture_110_mvitals,
.sf_obj=fixture_110_obj,
.sf_objclass=fixture_110_objclass,
.sf_q_score=fixture_110_q_score,
.sf_rm=fixture_110_rm,
.sf_spell=fixture_110_spell,
.sf_stairway=fixture_110_stairway,
.sf_s_level=fixture_110_s_level,
.sf_trap=fixture_110_trap,
.sf_you=fixture_110_you,
.sf_any=fixture_110_any,
.sf_aligntyp=fixture_110_aligntyp,
.sf_boolean=fixture_110_boolean,
.sf_coordxy=fixture_110_coordxy,
.sf_int=fixture_110_int,
.sf_int16=fixture_110_int16,
.sf_int32=fixture_110_int32,
.sf_int64=fixture_110_int64,
.sf_long=fixture_110_long,
.sf_schar=fixture_110_schar,
.sf_short=fixture_110_short,
.sf_size_t=fixture_110_size_t,
.sf_time_t=fixture_110_time_t,
.sf_uchar=fixture_110_uchar,
.sf_uint16=fixture_110_uint16,
.sf_uint32=fixture_110_uint32,
.sf_uint64=fixture_110_uint64,
.sf_ulong=fixture_110_ulong,
.sf_unsigned=fixture_110_unsigned,
.sf_ushort=fixture_110_ushort,
.sf_xint16=fixture_110_xint16,
.sf_xint8=fixture_110_xint8,
.sf_bitfield=fixture_110_bitfield,
.sf_char=fixture_110_char,
.sf_genericptr=fixture_110_genericptr,
.sf_version_info=fixture_110_version_info,
}};
struct sf_fieldlevel_procs fixture_111_table={.ext="fixture111",.fn_x={
.sf_arti_info=fixture_111_arti_info,
.sf_nhrect=fixture_111_nhrect,
.sf_branch=fixture_111_branch,
.sf_bubble=fixture_111_bubble,
.sf_cemetery=fixture_111_cemetery,
.sf_context_info=fixture_111_context_info,
.sf_nhcoord=fixture_111_nhcoord,
.sf_damage=fixture_111_damage,
.sf_dest_area=fixture_111_dest_area,
.sf_dgn_topology=fixture_111_dgn_topology,
.sf_dungeon=fixture_111_dungeon,
.sf_d_level=fixture_111_d_level,
.sf_ebones=fixture_111_ebones,
.sf_edog=fixture_111_edog,
.sf_egd=fixture_111_egd,
.sf_emin=fixture_111_emin,
.sf_engr=fixture_111_engr,
.sf_epri=fixture_111_epri,
.sf_eshk=fixture_111_eshk,
.sf_fe=fixture_111_fe,
.sf_flag=fixture_111_flag,
.sf_fruit=fixture_111_fruit,
.sf_gamelog_line=fixture_111_gamelog_line,
.sf_kinfo=fixture_111_kinfo,
.sf_levelflags=fixture_111_levelflags,
.sf_ls_t=fixture_111_ls_t,
.sf_linfo=fixture_111_linfo,
.sf_mapseen_feat=fixture_111_mapseen_feat,
.sf_mapseen_flags=fixture_111_mapseen_flags,
.sf_mapseen_rooms=fixture_111_mapseen_rooms,
.sf_mkroom=fixture_111_mkroom,
.sf_monst=fixture_111_monst,
.sf_mvitals=fixture_111_mvitals,
.sf_obj=fixture_111_obj,
.sf_objclass=fixture_111_objclass,
.sf_q_score=fixture_111_q_score,
.sf_rm=fixture_111_rm,
.sf_spell=fixture_111_spell,
.sf_stairway=fixture_111_stairway,
.sf_s_level=fixture_111_s_level,
.sf_trap=fixture_111_trap,
.sf_you=fixture_111_you,
.sf_any=fixture_111_any,
.sf_aligntyp=fixture_111_aligntyp,
.sf_boolean=fixture_111_boolean,
.sf_coordxy=fixture_111_coordxy,
.sf_int=fixture_111_int,
.sf_int16=fixture_111_int16,
.sf_int32=fixture_111_int32,
.sf_int64=fixture_111_int64,
.sf_long=fixture_111_long,
.sf_schar=fixture_111_schar,
.sf_short=fixture_111_short,
.sf_size_t=fixture_111_size_t,
.sf_time_t=fixture_111_time_t,
.sf_uchar=fixture_111_uchar,
.sf_uint16=fixture_111_uint16,
.sf_uint32=fixture_111_uint32,
.sf_uint64=fixture_111_uint64,
.sf_ulong=fixture_111_ulong,
.sf_unsigned=fixture_111_unsigned,
.sf_ushort=fixture_111_ushort,
.sf_xint16=fixture_111_xint16,
.sf_xint8=fixture_111_xint8,
.sf_bitfield=fixture_111_bitfield,
.sf_char=fixture_111_char,
.sf_genericptr=fixture_111_genericptr,
.sf_version_info=fixture_111_version_info,
}};

void probe_reset(void){
 for(int i=0;i<3;i++){if(logs[i])fclose(logs[i]);if(streams[i])fclose(streams[i]);logs[i]=tmpfile();streams[i]=tmpfile();if(!logs[i]||!streams[i])abort();}
 if(growth){free(growth);growth=0;}memset(files,0,sizeof files);memset(opts,0,sizeof opts);memset(data,0,sizeof data);tracebuf[0]=0;reentered=0;
 for(int i=0;i<3;i++){files[i].fnidx=historical;files[i].structlevel=1;files[i].fplog=logs[i];files[i].fpdef=streams[i];files[i].mode=WRITING;}
 sf_init();sf_setflprocs(exportascii,&fixture_110_table,&fixture_010_table);
}
void probe_option(int index,int value){opts[index]=value;}
void probe_file(int i,int field,int64 value){NHFILE*f=&files[i];switch(field){case 0:f->mode=value;break;case 1:f->structlevel=value;f->fnidx=value?historical:exportascii;break;case 2:f->eof=value;break;case 3:f->fplog=value?logs[i]:0;break;case 4:f->nhfpconvert=value<0?0:&files[value];break;case 5:f->rcount=value;break;case 6:f->wcount=value;break;case 7:f->fnidx=value;break;default:abort();}}
void*probe_pointer(int kind,int index){switch(kind){case 0:return data+index;case 1:return &files[index];case 2:return logs[index];case 3:return &historical_sfo_procs;case 4:return &historical_sfi_procs;case 5:return &fixture_010_table;case 6:return &fixture_110_table;default:abort();}}
void probe_input(int index,int n){if(n<0||n>sizeof data)abort();fwrite(data,1,n,streams[index]);fflush(streams[index]);rewind(streams[index]);}
void probe_close_log(int index){fflush(logs[index]);close(fileno(logs[index]));}
const char*probe_logs(int index){FILE*f=logs[index];fflush(f);long pos=ftell(f);if(pos<0){logbuf[0]=0;return logbuf;}rewind(f);size_t n=fread(logbuf,1,sizeof logbuf-1,f);logbuf[n]=0;fseek(f,pos,SEEK_SET);return logbuf;}
const char*probe_trace(void){return tracebuf;}
const char*probe_snapshot(void){char*p=snapshotbuf;for(int i=0;i<3;i++){NHFILE*f=&files[i];p+=sprintf(p,"f%d:%d,%d,%d,%d,%d,%ld,%ld,%d,%ld,%d;",i,f->mode,f->fnidx,f->structlevel,f->eof,log_index(f->fplog),f->rcount,f->wcount,file_index(f->nhfpconvert),ftell(streams[i]),ferror(logs[i]));}return snapshotbuf;}
void probe_table(int op,int index){switch(op){case 0:sf_init();break;case 1:sf_setprocs(index,&historical_sfi_procs,&historical_sfo_procs);break;case 2:sf_setprocs(index,&fixture_101_table,&fixture_001_table);break;case 3:sf_setflprocs(index,&fixture_111_table,&fixture_011_table);break;default:abort();}}
void probe_action(int which,int file,int offset,const char*tag,int count){switch(which){
case 0:sfo_arti_info(&files[file],(struct arti_info*)(data+offset),tag);return;
case 1:sfi_arti_info(&files[file],(struct arti_info*)(data+offset),tag);return;
case 2:sfo_nhrect(&files[file],(struct nhrect*)(data+offset),tag);return;
case 3:sfi_nhrect(&files[file],(struct nhrect*)(data+offset),tag);return;
case 4:sfo_branch(&files[file],(struct branch*)(data+offset),tag);return;
case 5:sfi_branch(&files[file],(struct branch*)(data+offset),tag);return;
case 6:sfo_bubble(&files[file],(struct bubble*)(data+offset),tag);return;
case 7:sfi_bubble(&files[file],(struct bubble*)(data+offset),tag);return;
case 8:sfo_cemetery(&files[file],(struct cemetery*)(data+offset),tag);return;
case 9:sfi_cemetery(&files[file],(struct cemetery*)(data+offset),tag);return;
case 10:sfo_context_info(&files[file],(struct context_info*)(data+offset),tag);return;
case 11:sfi_context_info(&files[file],(struct context_info*)(data+offset),tag);return;
case 12:sfo_nhcoord(&files[file],(struct nhcoord*)(data+offset),tag);return;
case 13:sfi_nhcoord(&files[file],(struct nhcoord*)(data+offset),tag);return;
case 14:sfo_damage(&files[file],(struct damage*)(data+offset),tag);return;
case 15:sfi_damage(&files[file],(struct damage*)(data+offset),tag);return;
case 16:sfo_dest_area(&files[file],(struct dest_area*)(data+offset),tag);return;
case 17:sfi_dest_area(&files[file],(struct dest_area*)(data+offset),tag);return;
case 18:sfo_dgn_topology(&files[file],(struct dgn_topology*)(data+offset),tag);return;
case 19:sfi_dgn_topology(&files[file],(struct dgn_topology*)(data+offset),tag);return;
case 20:sfo_dungeon(&files[file],(struct dungeon*)(data+offset),tag);return;
case 21:sfi_dungeon(&files[file],(struct dungeon*)(data+offset),tag);return;
case 22:sfo_d_level(&files[file],(struct d_level*)(data+offset),tag);return;
case 23:sfi_d_level(&files[file],(struct d_level*)(data+offset),tag);return;
case 24:sfo_ebones(&files[file],(struct ebones*)(data+offset),tag);return;
case 25:sfi_ebones(&files[file],(struct ebones*)(data+offset),tag);return;
case 26:sfo_edog(&files[file],(struct edog*)(data+offset),tag);return;
case 27:sfi_edog(&files[file],(struct edog*)(data+offset),tag);return;
case 28:sfo_egd(&files[file],(struct egd*)(data+offset),tag);return;
case 29:sfi_egd(&files[file],(struct egd*)(data+offset),tag);return;
case 30:sfo_emin(&files[file],(struct emin*)(data+offset),tag);return;
case 31:sfi_emin(&files[file],(struct emin*)(data+offset),tag);return;
case 32:sfo_engr(&files[file],(struct engr*)(data+offset),tag);return;
case 33:sfi_engr(&files[file],(struct engr*)(data+offset),tag);return;
case 34:sfo_epri(&files[file],(struct epri*)(data+offset),tag);return;
case 35:sfi_epri(&files[file],(struct epri*)(data+offset),tag);return;
case 36:sfo_eshk(&files[file],(struct eshk*)(data+offset),tag);return;
case 37:sfi_eshk(&files[file],(struct eshk*)(data+offset),tag);return;
case 38:sfo_fe(&files[file],(struct fe*)(data+offset),tag);return;
case 39:sfi_fe(&files[file],(struct fe*)(data+offset),tag);return;
case 40:sfo_flag(&files[file],(struct flag*)(data+offset),tag);return;
case 41:sfi_flag(&files[file],(struct flag*)(data+offset),tag);return;
case 42:sfo_fruit(&files[file],(struct fruit*)(data+offset),tag);return;
case 43:sfi_fruit(&files[file],(struct fruit*)(data+offset),tag);return;
case 44:sfo_gamelog_line(&files[file],(struct gamelog_line*)(data+offset),tag);return;
case 45:sfi_gamelog_line(&files[file],(struct gamelog_line*)(data+offset),tag);return;
case 46:sfo_kinfo(&files[file],(struct kinfo*)(data+offset),tag);return;
case 47:sfi_kinfo(&files[file],(struct kinfo*)(data+offset),tag);return;
case 48:sfo_levelflags(&files[file],(struct levelflags*)(data+offset),tag);return;
case 49:sfi_levelflags(&files[file],(struct levelflags*)(data+offset),tag);return;
case 50:sfo_ls_t(&files[file],(struct ls_t*)(data+offset),tag);return;
case 51:sfi_ls_t(&files[file],(struct ls_t*)(data+offset),tag);return;
case 52:sfo_linfo(&files[file],(struct linfo*)(data+offset),tag);return;
case 53:sfi_linfo(&files[file],(struct linfo*)(data+offset),tag);return;
case 54:sfo_mapseen_feat(&files[file],(struct mapseen_feat*)(data+offset),tag);return;
case 55:sfi_mapseen_feat(&files[file],(struct mapseen_feat*)(data+offset),tag);return;
case 56:sfo_mapseen_flags(&files[file],(struct mapseen_flags*)(data+offset),tag);return;
case 57:sfi_mapseen_flags(&files[file],(struct mapseen_flags*)(data+offset),tag);return;
case 58:sfo_mapseen_rooms(&files[file],(struct mapseen_rooms*)(data+offset),tag);return;
case 59:sfi_mapseen_rooms(&files[file],(struct mapseen_rooms*)(data+offset),tag);return;
case 60:sfo_mkroom(&files[file],(struct mkroom*)(data+offset),tag);return;
case 61:sfi_mkroom(&files[file],(struct mkroom*)(data+offset),tag);return;
case 62:sfo_monst(&files[file],(struct monst*)(data+offset),tag);return;
case 63:sfi_monst(&files[file],(struct monst*)(data+offset),tag);return;
case 64:sfo_mvitals(&files[file],(struct mvitals*)(data+offset),tag);return;
case 65:sfi_mvitals(&files[file],(struct mvitals*)(data+offset),tag);return;
case 66:sfo_obj(&files[file],(struct obj*)(data+offset),tag);return;
case 67:sfi_obj(&files[file],(struct obj*)(data+offset),tag);return;
case 68:sfo_objclass(&files[file],(struct objclass*)(data+offset),tag);return;
case 69:sfi_objclass(&files[file],(struct objclass*)(data+offset),tag);return;
case 70:sfo_q_score(&files[file],(struct q_score*)(data+offset),tag);return;
case 71:sfi_q_score(&files[file],(struct q_score*)(data+offset),tag);return;
case 72:sfo_rm(&files[file],(struct rm*)(data+offset),tag);return;
case 73:sfi_rm(&files[file],(struct rm*)(data+offset),tag);return;
case 74:sfo_spell(&files[file],(struct spell*)(data+offset),tag);return;
case 75:sfi_spell(&files[file],(struct spell*)(data+offset),tag);return;
case 76:sfo_stairway(&files[file],(struct stairway*)(data+offset),tag);return;
case 77:sfi_stairway(&files[file],(struct stairway*)(data+offset),tag);return;
case 78:sfo_s_level(&files[file],(struct s_level*)(data+offset),tag);return;
case 79:sfi_s_level(&files[file],(struct s_level*)(data+offset),tag);return;
case 80:sfo_trap(&files[file],(struct trap*)(data+offset),tag);return;
case 81:sfi_trap(&files[file],(struct trap*)(data+offset),tag);return;
case 82:sfo_you(&files[file],(struct you*)(data+offset),tag);return;
case 83:sfi_you(&files[file],(struct you*)(data+offset),tag);return;
case 84:sfo_any(&files[file],(union any*)(data+offset),tag);return;
case 85:sfi_any(&files[file],(union any*)(data+offset),tag);return;
case 86:sfo_aligntyp(&files[file],(aligntyp*)(data+offset),tag);return;
case 87:sfi_aligntyp(&files[file],(aligntyp*)(data+offset),tag);return;
case 88:sfo_boolean(&files[file],(boolean*)(data+offset),tag);return;
case 89:sfi_boolean(&files[file],(boolean*)(data+offset),tag);return;
case 90:sfo_coordxy(&files[file],(coordxy*)(data+offset),tag);return;
case 91:sfi_coordxy(&files[file],(coordxy*)(data+offset),tag);return;
case 92:sfo_int(&files[file],(int*)(data+offset),tag);return;
case 93:sfi_int(&files[file],(int*)(data+offset),tag);return;
case 94:sfo_int16(&files[file],(int16*)(data+offset),tag);return;
case 95:sfi_int16(&files[file],(int16*)(data+offset),tag);return;
case 96:sfo_int32(&files[file],(int32*)(data+offset),tag);return;
case 97:sfi_int32(&files[file],(int32*)(data+offset),tag);return;
case 98:sfo_int64(&files[file],(int64*)(data+offset),tag);return;
case 99:sfi_int64(&files[file],(int64*)(data+offset),tag);return;
case 100:sfo_long(&files[file],(long*)(data+offset),tag);return;
case 101:sfi_long(&files[file],(long*)(data+offset),tag);return;
case 102:sfo_schar(&files[file],(schar*)(data+offset),tag);return;
case 103:sfi_schar(&files[file],(schar*)(data+offset),tag);return;
case 104:sfo_short(&files[file],(short*)(data+offset),tag);return;
case 105:sfi_short(&files[file],(short*)(data+offset),tag);return;
case 106:sfo_size_t(&files[file],(size_t*)(data+offset),tag);return;
case 107:sfi_size_t(&files[file],(size_t*)(data+offset),tag);return;
case 108:sfo_time_t(&files[file],(time_t*)(data+offset),tag);return;
case 109:sfi_time_t(&files[file],(time_t*)(data+offset),tag);return;
case 110:sfo_uchar(&files[file],(uchar*)(data+offset),tag);return;
case 111:sfi_uchar(&files[file],(uchar*)(data+offset),tag);return;
case 112:sfo_uint16(&files[file],(uint16*)(data+offset),tag);return;
case 113:sfi_uint16(&files[file],(uint16*)(data+offset),tag);return;
case 114:sfo_uint32(&files[file],(uint32*)(data+offset),tag);return;
case 115:sfi_uint32(&files[file],(uint32*)(data+offset),tag);return;
case 116:sfo_uint64(&files[file],(uint64*)(data+offset),tag);return;
case 117:sfi_uint64(&files[file],(uint64*)(data+offset),tag);return;
case 118:sfo_ulong(&files[file],(ulong*)(data+offset),tag);return;
case 119:sfi_ulong(&files[file],(ulong*)(data+offset),tag);return;
case 120:sfo_unsigned(&files[file],(unsigned*)(data+offset),tag);return;
case 121:sfi_unsigned(&files[file],(unsigned*)(data+offset),tag);return;
case 122:sfo_ushort(&files[file],(ushort*)(data+offset),tag);return;
case 123:sfi_ushort(&files[file],(ushort*)(data+offset),tag);return;
case 124:sfo_xint16(&files[file],(xint16*)(data+offset),tag);return;
case 125:sfi_xint16(&files[file],(xint16*)(data+offset),tag);return;
case 126:sfo_xint8(&files[file],(xint8*)(data+offset),tag);return;
case 127:sfi_xint8(&files[file],(xint8*)(data+offset),tag);return;
case 128:sfo_bitfield(&files[file],(uint8_t*)(data+offset),tag,count);return;
case 129:sfi_bitfield(&files[file],(uint8_t*)(data+offset),tag,count);return;
case 130:sfo_char(&files[file],(char*)(data+offset),tag,count);return;
case 131:sfi_char(&files[file],(char*)(data+offset),tag,count);return;
case 132:sfo_genericptr(&files[file],(void **)(data+offset),tag);return;
case 133:sfi_genericptr(&files[file],(void **)(data+offset),tag);return;
case 134:sfo_version_info(&files[file],(struct version_info*)(data+offset),tag);return;
case 135:sfi_version_info(&files[file],(struct version_info*)(data+offset),tag);return;
default:abort();}}
char*probe_value(int which,int offset,int count){switch(which){
case 0:return sfvalue_char((char *)(offset<0?0:data+offset),count);
case 1:return sfvalue_boolean((boolean *)(offset<0?0:data+offset));
case 2:return sfvalue_schar((schar *)(offset<0?0:data+offset));
case 3:return sfvalue_aligntyp((aligntyp *)(offset<0?0:data+offset));
case 4:return sfvalue_any((anything *)(offset<0?0:data+offset));
case 5:return sfvalue_genericptr((void *)(offset<0?0:data+offset));
case 6:return sfvalue_int16((int16 *)(offset<0?0:data+offset));
case 7:return sfvalue_int32((int32 *)(offset<0?0:data+offset));
case 8:return sfvalue_int64((int64 *)(offset<0?0:data+offset));
case 9:return sfvalue_uchar((uchar *)(offset<0?0:data+offset));
case 10:return sfvalue_uint16((uint16 *)(offset<0?0:data+offset));
case 11:return sfvalue_uint32((uint32 *)(offset<0?0:data+offset));
case 12:return sfvalue_uint64((uint64 *)(offset<0?0:data+offset));
case 13:return sfvalue_size_t((size_t *)(offset<0?0:data+offset));
case 14:return sfvalue_time_t((time_t *)(offset<0?0:data+offset));
case 15:return sfvalue_short((short *)(offset<0?0:data+offset));
case 16:return sfvalue_ushort((ushort *)(offset<0?0:data+offset));
case 17:return sfvalue_int((int *)(offset<0?0:data+offset));
case 18:return sfvalue_unsigned((unsigned int *)(offset<0?0:data+offset));
case 19:return sfvalue_long((long *)(offset<0?0:data+offset));
case 20:return sfvalue_ulong((ulong *)(offset<0?0:data+offset));
case 21:return sfvalue_xint8((xint8 *)(offset<0?0:data+offset));
case 22:return sfvalue_xint16((xint16 *)(offset<0?0:data+offset));
case 23:return sfvalue_bitfield((uint8 *)(offset<0?0:data+offset));
case 24:return bitfield_dump((uint8 *)(offset<0?0:data+offset));
case 25:return complex_dump((uchar *)(offset<0?0:data+offset));
default:abort();}}
void probe_norm(int which){switch(which){
case 0:norm_ptrs_any((union any *)data);return;
case 1:norm_ptrs_align((struct align *)data);return;
case 2:norm_ptrs_arti_info((struct arti_info *)data);return;
case 3:norm_ptrs_attribs((struct attribs *)data);return;
case 4:norm_ptrs_bill_x((struct bill_x *)data);return;
case 5:norm_ptrs_branch((struct branch *)data);return;
case 6:norm_ptrs_bubble((struct bubble *)data);return;
case 7:norm_ptrs_cemetery((struct cemetery *)data);return;
case 8:norm_ptrs_context_info((struct context_info *)data);return;
case 9:norm_ptrs_achievement_tracking((struct achievement_tracking *)data);return;
case 10:norm_ptrs_book_info((struct book_info *)data);return;
case 11:norm_ptrs_dig_info((struct dig_info *)data);return;
case 12:norm_ptrs_engrave_info((struct engrave_info *)data);return;
case 13:norm_ptrs_obj_split((struct obj_split *)data);return;
case 14:norm_ptrs_polearm_info((struct polearm_info *)data);return;
case 15:norm_ptrs_takeoff_info((struct takeoff_info *)data);return;
case 16:norm_ptrs_tin_info((struct tin_info *)data);return;
case 17:norm_ptrs_tribute_info((struct tribute_info *)data);return;
case 18:norm_ptrs_victual_info((struct victual_info *)data);return;
case 19:norm_ptrs_warntype_info((struct warntype_info *)data);return;
case 20:norm_ptrs_d_flags((struct d_flags *)data);return;
case 21:norm_ptrs_d_level((struct d_level *)data);return;
case 22:norm_ptrs_damage((struct damage *)data);return;
case 23:norm_ptrs_dest_area((struct dest_area *)data);return;
case 24:norm_ptrs_dgn_topology((struct dgn_topology *)data);return;
case 25:norm_ptrs_dungeon((struct dungeon *)data);return;
case 26:norm_ptrs_ebones((struct ebones *)data);return;
case 27:norm_ptrs_edog((struct edog *)data);return;
case 28:norm_ptrs_egd((struct egd *)data);return;
case 29:norm_ptrs_emin((struct emin *)data);return;
case 30:norm_ptrs_engr((struct engr *)data);return;
case 31:norm_ptrs_epri((struct epri *)data);return;
case 32:norm_ptrs_eshk((struct eshk *)data);return;
case 33:norm_ptrs_fakecorridor((struct fakecorridor *)data);return;
case 34:norm_ptrs_fe((struct fe *)data);return;
case 35:norm_ptrs_flag((struct flag *)data);return;
case 36:norm_ptrs_fruit((struct fruit *)data);return;
case 37:norm_ptrs_gamelog_line((struct gamelog_line *)data);return;
case 38:norm_ptrs_kinfo((struct kinfo *)data);return;
case 39:norm_ptrs_levelflags((struct levelflags *)data);return;
case 40:norm_ptrs_linfo((struct linfo *)data);return;
case 41:norm_ptrs_ls_t((struct ls_t *)data);return;
case 42:norm_ptrs_mapseen_feat((struct mapseen_feat *)data);return;
case 43:norm_ptrs_mapseen_flags((struct mapseen_flags *)data);return;
case 44:norm_ptrs_mapseen_rooms((struct mapseen_rooms *)data);return;
case 45:norm_ptrs_mapseen((struct mapseen *)data);return;
case 46:norm_ptrs_mextra((struct mextra *)data);return;
case 47:norm_ptrs_mkroom((struct mkroom *)data);return;
case 48:norm_ptrs_monst((struct monst *)data);return;
case 49:norm_ptrs_mvitals((struct mvitals *)data);return;
case 50:norm_ptrs_nhcoord((struct nhcoord *)data);return;
case 51:norm_ptrs_nhrect((struct nhrect *)data);return;
case 52:norm_ptrs_novel_tracking((struct novel_tracking *)data);return;
case 53:norm_ptrs_obj((struct obj *)data);return;
case 54:norm_ptrs_objclass((struct objclass *)data);return;
case 55:norm_ptrs_oextra((struct oextra *)data);return;
case 56:norm_ptrs_prop((struct prop *)data);return;
case 57:norm_ptrs_q_score((struct q_score *)data);return;
case 58:norm_ptrs_rm((struct rm *)data);return;
case 59:norm_ptrs_s_level((struct s_level *)data);return;
case 60:norm_ptrs_skills((struct skills *)data);return;
case 61:norm_ptrs_spell((struct spell *)data);return;
case 62:norm_ptrs_stairway((struct stairway *)data);return;
case 63:norm_ptrs_trap((struct trap *)data);return;
case 64:norm_ptrs_u_conduct((struct u_conduct *)data);return;
case 65:norm_ptrs_u_event((struct u_event *)data);return;
case 66:norm_ptrs_u_have((struct u_have *)data);return;
case 67:norm_ptrs_u_realtime((struct u_realtime *)data);return;
case 68:norm_ptrs_u_roleplay((struct u_roleplay *)data);return;
case 69:norm_ptrs_version_info((struct version_info *)data);return;
case 70:norm_ptrs_vlaunchinfo((union vlaunchinfo *)data);return;
case 71:norm_ptrs_vptrs((union vptrs *)data);return;
case 72:norm_ptrs_you((struct you *)data);return;
default:abort();}}
void probe_log(int file,size_t size,int count,const char*tag,const char*text){sf_log(&files[file],tag,size,count,(char*)text);}
int probe_layout_count(void){return SIZE(sfbase_layout);}
const char*probe_layout_name(int index){return sfbase_layout[index].name;}
size_t probe_layout_value(int index){return sfbase_layout[index].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
static const char*const probe_serial_names[]={"sfo_arti_info","sfi_arti_info","sfo_nhrect","sfi_nhrect","sfo_branch","sfi_branch","sfo_bubble","sfi_bubble","sfo_cemetery","sfi_cemetery","sfo_context_info","sfi_context_info","sfo_nhcoord","sfi_nhcoord","sfo_damage","sfi_damage","sfo_dest_area","sfi_dest_area","sfo_dgn_topology","sfi_dgn_topology","sfo_dungeon","sfi_dungeon","sfo_d_level","sfi_d_level","sfo_ebones","sfi_ebones","sfo_edog","sfi_edog","sfo_egd","sfi_egd","sfo_emin","sfi_emin","sfo_engr","sfi_engr","sfo_epri","sfi_epri","sfo_eshk","sfi_eshk","sfo_fe","sfi_fe","sfo_flag","sfi_flag","sfo_fruit","sfi_fruit","sfo_gamelog_line","sfi_gamelog_line","sfo_kinfo","sfi_kinfo","sfo_levelflags","sfi_levelflags","sfo_ls_t","sfi_ls_t","sfo_linfo","sfi_linfo","sfo_mapseen_feat","sfi_mapseen_feat","sfo_mapseen_flags","sfi_mapseen_flags","sfo_mapseen_rooms","sfi_mapseen_rooms","sfo_mkroom","sfi_mkroom","sfo_monst","sfi_monst","sfo_mvitals","sfi_mvitals","sfo_obj","sfi_obj","sfo_objclass","sfi_objclass","sfo_q_score","sfi_q_score","sfo_rm","sfi_rm","sfo_spell","sfi_spell","sfo_stairway","sfi_stairway","sfo_s_level","sfi_s_level","sfo_trap","sfi_trap","sfo_you","sfi_you","sfo_any","sfi_any","sfo_aligntyp","sfi_aligntyp","sfo_boolean","sfi_boolean","sfo_coordxy","sfi_coordxy","sfo_int","sfi_int","sfo_int16","sfi_int16","sfo_int32","sfi_int32","sfo_int64","sfi_int64","sfo_long","sfi_long","sfo_schar","sfi_schar","sfo_short","sfi_short","sfo_size_t","sfi_size_t","sfo_time_t","sfi_time_t","sfo_uchar","sfi_uchar","sfo_uint16","sfi_uint16","sfo_uint32","sfi_uint32","sfo_uint64","sfi_uint64","sfo_ulong","sfi_ulong","sfo_unsigned","sfi_unsigned","sfo_ushort","sfi_ushort","sfo_xint16","sfi_xint16","sfo_xint8","sfi_xint8","sfo_bitfield","sfi_bitfield","sfo_char","sfi_char","sfo_genericptr","sfi_genericptr","sfo_version_info","sfi_version_info"};
int probe_serial_count(void){return SIZE(probe_serial_names);}
const char*probe_serial_name(int i){return probe_serial_names[i];}
static const char*const probe_values_names[]={"sfvalue_char","sfvalue_boolean","sfvalue_schar","sfvalue_aligntyp","sfvalue_any","sfvalue_genericptr","sfvalue_int16","sfvalue_int32","sfvalue_int64","sfvalue_uchar","sfvalue_uint16","sfvalue_uint32","sfvalue_uint64","sfvalue_size_t","sfvalue_time_t","sfvalue_short","sfvalue_ushort","sfvalue_int","sfvalue_unsigned","sfvalue_long","sfvalue_ulong","sfvalue_xint8","sfvalue_xint16","sfvalue_bitfield","bitfield_dump","complex_dump"};
int probe_values_count(void){return SIZE(probe_values_names);}
const char*probe_values_name(int i){return probe_values_names[i];}
static const char*const probe_norms_names[]={"norm_ptrs_any","norm_ptrs_align","norm_ptrs_arti_info","norm_ptrs_attribs","norm_ptrs_bill_x","norm_ptrs_branch","norm_ptrs_bubble","norm_ptrs_cemetery","norm_ptrs_context_info","norm_ptrs_achievement_tracking","norm_ptrs_book_info","norm_ptrs_dig_info","norm_ptrs_engrave_info","norm_ptrs_obj_split","norm_ptrs_polearm_info","norm_ptrs_takeoff_info","norm_ptrs_tin_info","norm_ptrs_tribute_info","norm_ptrs_victual_info","norm_ptrs_warntype_info","norm_ptrs_d_flags","norm_ptrs_d_level","norm_ptrs_damage","norm_ptrs_dest_area","norm_ptrs_dgn_topology","norm_ptrs_dungeon","norm_ptrs_ebones","norm_ptrs_edog","norm_ptrs_egd","norm_ptrs_emin","norm_ptrs_engr","norm_ptrs_epri","norm_ptrs_eshk","norm_ptrs_fakecorridor","norm_ptrs_fe","norm_ptrs_flag","norm_ptrs_fruit","norm_ptrs_gamelog_line","norm_ptrs_kinfo","norm_ptrs_levelflags","norm_ptrs_linfo","norm_ptrs_ls_t","norm_ptrs_mapseen_feat","norm_ptrs_mapseen_flags","norm_ptrs_mapseen_rooms","norm_ptrs_mapseen","norm_ptrs_mextra","norm_ptrs_mkroom","norm_ptrs_monst","norm_ptrs_mvitals","norm_ptrs_nhcoord","norm_ptrs_nhrect","norm_ptrs_novel_tracking","norm_ptrs_obj","norm_ptrs_objclass","norm_ptrs_oextra","norm_ptrs_prop","norm_ptrs_q_score","norm_ptrs_rm","norm_ptrs_s_level","norm_ptrs_skills","norm_ptrs_spell","norm_ptrs_stairway","norm_ptrs_trap","norm_ptrs_u_conduct","norm_ptrs_u_event","norm_ptrs_u_have","norm_ptrs_u_realtime","norm_ptrs_u_roleplay","norm_ptrs_version_info","norm_ptrs_vlaunchinfo","norm_ptrs_vptrs","norm_ptrs_you"};
int probe_norms_count(void){return SIZE(probe_norms_names);}
const char*probe_norms_name(int i){return probe_norms_names[i];}
