/* External IO/normalizer fixture boundaries; original SFSTRUCT algorithms unchanged. */
#include "hack.h"
#include "sfprocs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef read
#undef write
#undef fdopen
#undef fwrite
#undef fflush
#undef fclose
#undef close
extern ssize_t read(int,void*,size_t),write(int,const void*,size_t);
extern FILE *fdopen(int,const char*);
extern size_t fwrite(const void*,size_t,size_t,FILE*);
extern int fflush(FILE*),fclose(FILE*),close(int);
__typeof__(program_state) program_state;
__typeof__(windowprocs) windowprocs;
winid WIN_MESSAGE=17;
static NHFILE nhfile;
static unsigned char data[65536],saved[65536];
static int fds[16],opts[32],panic_code,armed;
static jmp_buf checkpoint;
static char tracebuf[262144],panictext[BUFSZ];
static void *growth;
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
static int fileid(int fd){for(int i=0;i<16;i++)if(fds[i]==fd)return i;return -1;}
static void callback(int stage){if(opts[20]==stage){opts[20]=0;append("nested:%d;",close_check(nhfile.fd));}if(opts[21]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();append("grow:%d;",stage);}if(opts[22]==stage){opts[22]=0;restoreinfo.mread_flags=opts[23];append("flags:%d;",opts[23]);}}
void panic(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(panictext,sizeof panictext,fmt,ap);va_end(ap);append("panic:%s;",panictext);panic_code=1;if(armed)longjmp(checkpoint,1);abort();}
void impossible(const char *fmt,...){char b[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void pline(const char *fmt,...){char b[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);}
void error(const char *fmt,...){char b[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("error:%s;",b);panic_code=3;if(armed)longjmp(checkpoint,1);abort();}
void nh_terminate(int status){append("terminate:%d;",status);panic_code=2;if(armed)longjmp(checkpoint,1);abort();}
static void display(winid win,boolean block){append("display:%d:%d;",win,block);}
int delete_savefile(void){append("delete-save;");return 1;}
int nhclose(int fd){append("nhclose:%d;",fileid(fd));return close(fd);}
ssize_t teleport_probe_read(int fd,void *p,size_t n){append("read:%d:%lu;",fileid(fd),(unsigned long)n);callback(1);if(opts[1])return opts[1]==1?-1:0;size_t take=opts[2]&&n>(size_t)opts[2]?(size_t)opts[2]:n;return read(fd,p,take);}
ssize_t teleport_probe_write(int fd,const void *p,size_t n){append("write:%d:%lu;",fileid(fd),(unsigned long)n);callback(2);if(opts[3])return opts[3]==1?-1:0;size_t take=opts[4]&&n>(size_t)opts[4]?(size_t)opts[4]:n;return write(fd,p,take);}
FILE *teleport_probe_fdopen(int fd,const char *mode){append("fdopen:%d:%s;",fileid(fd),mode);callback(3);return opts[5]?NULL:fdopen(fd,mode);}
size_t teleport_probe_fwrite(const void *p,size_t size,size_t count,FILE *fp){append("fwrite:%d:%lu:%lu;",fileid(fileno(fp)),(unsigned long)size,(unsigned long)count);callback(4);return opts[6]?0:fwrite(p,size,count,fp);}
int teleport_probe_fflush(FILE *fp){append("fflush:%d;",fileid(fileno(fp)));callback(5);return opts[7]?EOF:fflush(fp);}
int teleport_probe_fclose(FILE *fp){int fd=fileno(fp);append("fclose:%d;",fileid(fd));callback(6);int r=fclose(fp);return r;}
int teleport_probe_close(int fd){append("close:%d;",fileid(fd));callback(7);return close(fd);}
void norm_ptrs_arti_info(struct arti_info *p){append("norm:arti_info;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_nhrect(struct nhrect *p){append("norm:nhrect;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_branch(struct branch *p){append("norm:branch;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_bubble(struct bubble *p){append("norm:bubble;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_cemetery(struct cemetery *p){append("norm:cemetery;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_context_info(struct context_info *p){append("norm:context_info;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_nhcoord(struct nhcoord *p){append("norm:nhcoord;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_damage(struct damage *p){append("norm:damage;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_dest_area(struct dest_area *p){append("norm:dest_area;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_dgn_topology(struct dgn_topology *p){append("norm:dgn_topology;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_dungeon(struct dungeon *p){append("norm:dungeon;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_d_level(struct d_level *p){append("norm:d_level;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_ebones(struct ebones *p){append("norm:ebones;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_edog(struct edog *p){append("norm:edog;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_egd(struct egd *p){append("norm:egd;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_emin(struct emin *p){append("norm:emin;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_engr(struct engr *p){append("norm:engr;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_epri(struct epri *p){append("norm:epri;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_eshk(struct eshk *p){append("norm:eshk;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_fe(struct fe *p){append("norm:fe;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_flag(struct flag *p){append("norm:flag;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_fruit(struct fruit *p){append("norm:fruit;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_gamelog_line(struct gamelog_line *p){append("norm:gamelog_line;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_kinfo(struct kinfo *p){append("norm:kinfo;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_levelflags(struct levelflags *p){append("norm:levelflags;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_ls_t(struct ls_t *p){append("norm:ls_t;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_linfo(struct linfo *p){append("norm:linfo;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_mapseen_feat(struct mapseen_feat *p){append("norm:mapseen_feat;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_mapseen_flags(struct mapseen_flags *p){append("norm:mapseen_flags;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_mapseen_rooms(struct mapseen_rooms *p){append("norm:mapseen_rooms;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_mkroom(struct mkroom *p){append("norm:mkroom;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_monst(struct monst *p){append("norm:monst;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_mvitals(struct mvitals *p){append("norm:mvitals;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_obj(struct obj *p){append("norm:obj;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_objclass(struct objclass *p){append("norm:objclass;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_q_score(struct q_score *p){append("norm:q_score;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_rm(struct rm *p){append("norm:rm;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_spell(struct spell *p){append("norm:spell;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_stairway(struct stairway *p){append("norm:stairway;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_s_level(struct s_level *p){append("norm:s_level;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_trap(struct trap *p){append("norm:trap;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_you(struct you *p){append("norm:you;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_any(union any *p){append("norm:any;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
void norm_ptrs_version_info(struct version_info *p){append("norm:version_info;");if(opts[8])((unsigned char*)p)[0]^=opts[8];callback(8);}
#define read teleport_probe_read
#define write teleport_probe_write
#define fdopen teleport_probe_fdopen
#define fwrite teleport_probe_fwrite
#define fflush teleport_probe_fflush
#define fclose teleport_probe_fclose
#define close teleport_probe_close
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/sfstruct.c"
#else
extern int teleport_sfstruct_test_getidx(int,int);
extern void teleport_sfstruct_test_read_error(void);
extern uintptr_t teleport_sfstruct_test_state(int,int);
#define getidx teleport_sfstruct_test_getidx
#define sfstruct_read_error teleport_sfstruct_test_read_error
#endif
#undef read
#undef write
#undef fdopen
#undef fwrite
#undef fflush
#undef fclose
#undef close
#include "tu-sfstruct-layout.h"
static uintptr_t state(int field,int index){
#ifdef TELEPORT_REFERENCE_TU
return field==0?(uintptr_t)(long)bw_sticky[index]:field==1?(uintptr_t)(long)bw_buffered[index]:(uintptr_t)bw_FILE[index];
#else
return teleport_sfstruct_test_state(field,index);
#endif
}
void probe_reset(void){
 static int first=1;if(!first){for(int i=0;i<5;i++){int fd=(int)state(0,i);if(fd>=0){opts[7]=0;bclose(fd);}}for(int i=0;i<16;i++)if(fds[i]>=0)close(fds[i]);}first=0;
 for(int i=0;i<16;i++)fds[i]=-1;free(growth);growth=NULL;memset(opts,0,sizeof opts);memset(&program_state,0,sizeof program_state);memset(&nhfile,0,sizeof nhfile);memset((void*)&windowprocs,0,sizeof windowprocs);windowprocs.win_display_nhwindow=display;restoreinfo.mread_flags=0;memset(data,0xa5,sizeof data);tracebuf[0]=panictext[0]=0;panic_code=armed=0;
}
void probe_option(int key,int value){opts[key]=value;}
int probe_open(int slot,int mode){char name[64];sprintf(name,"/sfstruct-%d.bin",slot);if(fds[slot]>=0)close(fds[slot]);fds[slot]=open(name,mode?O_RDONLY:O_RDWR|O_CREAT|O_TRUNC,0600);return fds[slot];}
void probe_seed_file(int slot,unsigned count){if(count>sizeof data)abort();write(fds[slot],data,count);lseek(fds[slot],0,SEEK_SET);}
void probe_seek(int slot,long offset){lseek(fds[slot],offset,SEEK_SET);}
int probe_fd(int slot){return fds[slot];}
uintptr_t probe_state(int field,int index){return state(field,index);}
void *probe_buffer(void){return data;}
unsigned probe_capacity(void){return sizeof data;}
void probe_fill(unsigned seed){for(size_t i=0;i<sizeof data;i++)data[i]=(unsigned char)(seed+i*29);}
void probe_flags(int flags,int bones,int restoring,int hup,int eof){restoreinfo.mread_flags=flags;program_state.reading_bonesfile=bones;program_state.restoring=restoring;program_state.done_hup=hup;nhfile.eof=eof;}
long probe_io(int op,int slot,unsigned count){int fd=slot<0?-1:fds[slot];long result=0;nhfile.fd=fd;panic_code=0;armed=1;if(setjmp(checkpoint)==0)switch(op){case 0:result=close_check(fd);break;case 1:bufon(fd);break;case 2:bufoff(fd);break;case 3:bclose(fd);break;case 4:bflush(fd);break;case 5:bwrite(fd,data,count);break;case 6:mread(fd,data,count);break;case 7:result=getidx(fd,count);break;case 8:sfstruct_read_error();break;}armed=0;return result;}
long probe_serial(int input,int index,int slot,int count,int table){nhfile.fd=fds[slot];panic_code=0;armed=1;if(setjmp(checkpoint)==0)switch(index){
case 0:if(input){if(table)historical_sfi_procs.fn.sf_arti_info(&nhfile,(struct arti_info*)data,"probe-arti_info");else historical_sfi_arti_info(&nhfile,(struct arti_info*)data,"probe-arti_info");}else{if(table)historical_sfo_procs.fn.sf_arti_info(&nhfile,(struct arti_info*)data,"probe-arti_info");else historical_sfo_arti_info(&nhfile,(struct arti_info*)data,"probe-arti_info");}break;
case 1:if(input){if(table)historical_sfi_procs.fn.sf_nhrect(&nhfile,(struct nhrect*)data,"probe-nhrect");else historical_sfi_nhrect(&nhfile,(struct nhrect*)data,"probe-nhrect");}else{if(table)historical_sfo_procs.fn.sf_nhrect(&nhfile,(struct nhrect*)data,"probe-nhrect");else historical_sfo_nhrect(&nhfile,(struct nhrect*)data,"probe-nhrect");}break;
case 2:if(input){if(table)historical_sfi_procs.fn.sf_branch(&nhfile,(struct branch*)data,"probe-branch");else historical_sfi_branch(&nhfile,(struct branch*)data,"probe-branch");}else{if(table)historical_sfo_procs.fn.sf_branch(&nhfile,(struct branch*)data,"probe-branch");else historical_sfo_branch(&nhfile,(struct branch*)data,"probe-branch");}break;
case 3:if(input){if(table)historical_sfi_procs.fn.sf_bubble(&nhfile,(struct bubble*)data,"probe-bubble");else historical_sfi_bubble(&nhfile,(struct bubble*)data,"probe-bubble");}else{if(table)historical_sfo_procs.fn.sf_bubble(&nhfile,(struct bubble*)data,"probe-bubble");else historical_sfo_bubble(&nhfile,(struct bubble*)data,"probe-bubble");}break;
case 4:if(input){if(table)historical_sfi_procs.fn.sf_cemetery(&nhfile,(struct cemetery*)data,"probe-cemetery");else historical_sfi_cemetery(&nhfile,(struct cemetery*)data,"probe-cemetery");}else{if(table)historical_sfo_procs.fn.sf_cemetery(&nhfile,(struct cemetery*)data,"probe-cemetery");else historical_sfo_cemetery(&nhfile,(struct cemetery*)data,"probe-cemetery");}break;
case 5:if(input){if(table)historical_sfi_procs.fn.sf_context_info(&nhfile,(struct context_info*)data,"probe-context_info");else historical_sfi_context_info(&nhfile,(struct context_info*)data,"probe-context_info");}else{if(table)historical_sfo_procs.fn.sf_context_info(&nhfile,(struct context_info*)data,"probe-context_info");else historical_sfo_context_info(&nhfile,(struct context_info*)data,"probe-context_info");}break;
case 6:if(input){if(table)historical_sfi_procs.fn.sf_nhcoord(&nhfile,(struct nhcoord*)data,"probe-nhcoord");else historical_sfi_nhcoord(&nhfile,(struct nhcoord*)data,"probe-nhcoord");}else{if(table)historical_sfo_procs.fn.sf_nhcoord(&nhfile,(struct nhcoord*)data,"probe-nhcoord");else historical_sfo_nhcoord(&nhfile,(struct nhcoord*)data,"probe-nhcoord");}break;
case 7:if(input){if(table)historical_sfi_procs.fn.sf_damage(&nhfile,(struct damage*)data,"probe-damage");else historical_sfi_damage(&nhfile,(struct damage*)data,"probe-damage");}else{if(table)historical_sfo_procs.fn.sf_damage(&nhfile,(struct damage*)data,"probe-damage");else historical_sfo_damage(&nhfile,(struct damage*)data,"probe-damage");}break;
case 8:if(input){if(table)historical_sfi_procs.fn.sf_dest_area(&nhfile,(struct dest_area*)data,"probe-dest_area");else historical_sfi_dest_area(&nhfile,(struct dest_area*)data,"probe-dest_area");}else{if(table)historical_sfo_procs.fn.sf_dest_area(&nhfile,(struct dest_area*)data,"probe-dest_area");else historical_sfo_dest_area(&nhfile,(struct dest_area*)data,"probe-dest_area");}break;
case 9:if(input){if(table)historical_sfi_procs.fn.sf_dgn_topology(&nhfile,(struct dgn_topology*)data,"probe-dgn_topology");else historical_sfi_dgn_topology(&nhfile,(struct dgn_topology*)data,"probe-dgn_topology");}else{if(table)historical_sfo_procs.fn.sf_dgn_topology(&nhfile,(struct dgn_topology*)data,"probe-dgn_topology");else historical_sfo_dgn_topology(&nhfile,(struct dgn_topology*)data,"probe-dgn_topology");}break;
case 10:if(input){if(table)historical_sfi_procs.fn.sf_dungeon(&nhfile,(struct dungeon*)data,"probe-dungeon");else historical_sfi_dungeon(&nhfile,(struct dungeon*)data,"probe-dungeon");}else{if(table)historical_sfo_procs.fn.sf_dungeon(&nhfile,(struct dungeon*)data,"probe-dungeon");else historical_sfo_dungeon(&nhfile,(struct dungeon*)data,"probe-dungeon");}break;
case 11:if(input){if(table)historical_sfi_procs.fn.sf_d_level(&nhfile,(struct d_level*)data,"probe-d_level");else historical_sfi_d_level(&nhfile,(struct d_level*)data,"probe-d_level");}else{if(table)historical_sfo_procs.fn.sf_d_level(&nhfile,(struct d_level*)data,"probe-d_level");else historical_sfo_d_level(&nhfile,(struct d_level*)data,"probe-d_level");}break;
case 12:if(input){if(table)historical_sfi_procs.fn.sf_ebones(&nhfile,(struct ebones*)data,"probe-ebones");else historical_sfi_ebones(&nhfile,(struct ebones*)data,"probe-ebones");}else{if(table)historical_sfo_procs.fn.sf_ebones(&nhfile,(struct ebones*)data,"probe-ebones");else historical_sfo_ebones(&nhfile,(struct ebones*)data,"probe-ebones");}break;
case 13:if(input){if(table)historical_sfi_procs.fn.sf_edog(&nhfile,(struct edog*)data,"probe-edog");else historical_sfi_edog(&nhfile,(struct edog*)data,"probe-edog");}else{if(table)historical_sfo_procs.fn.sf_edog(&nhfile,(struct edog*)data,"probe-edog");else historical_sfo_edog(&nhfile,(struct edog*)data,"probe-edog");}break;
case 14:if(input){if(table)historical_sfi_procs.fn.sf_egd(&nhfile,(struct egd*)data,"probe-egd");else historical_sfi_egd(&nhfile,(struct egd*)data,"probe-egd");}else{if(table)historical_sfo_procs.fn.sf_egd(&nhfile,(struct egd*)data,"probe-egd");else historical_sfo_egd(&nhfile,(struct egd*)data,"probe-egd");}break;
case 15:if(input){if(table)historical_sfi_procs.fn.sf_emin(&nhfile,(struct emin*)data,"probe-emin");else historical_sfi_emin(&nhfile,(struct emin*)data,"probe-emin");}else{if(table)historical_sfo_procs.fn.sf_emin(&nhfile,(struct emin*)data,"probe-emin");else historical_sfo_emin(&nhfile,(struct emin*)data,"probe-emin");}break;
case 16:if(input){if(table)historical_sfi_procs.fn.sf_engr(&nhfile,(struct engr*)data,"probe-engr");else historical_sfi_engr(&nhfile,(struct engr*)data,"probe-engr");}else{if(table)historical_sfo_procs.fn.sf_engr(&nhfile,(struct engr*)data,"probe-engr");else historical_sfo_engr(&nhfile,(struct engr*)data,"probe-engr");}break;
case 17:if(input){if(table)historical_sfi_procs.fn.sf_epri(&nhfile,(struct epri*)data,"probe-epri");else historical_sfi_epri(&nhfile,(struct epri*)data,"probe-epri");}else{if(table)historical_sfo_procs.fn.sf_epri(&nhfile,(struct epri*)data,"probe-epri");else historical_sfo_epri(&nhfile,(struct epri*)data,"probe-epri");}break;
case 18:if(input){if(table)historical_sfi_procs.fn.sf_eshk(&nhfile,(struct eshk*)data,"probe-eshk");else historical_sfi_eshk(&nhfile,(struct eshk*)data,"probe-eshk");}else{if(table)historical_sfo_procs.fn.sf_eshk(&nhfile,(struct eshk*)data,"probe-eshk");else historical_sfo_eshk(&nhfile,(struct eshk*)data,"probe-eshk");}break;
case 19:if(input){if(table)historical_sfi_procs.fn.sf_fe(&nhfile,(struct fe*)data,"probe-fe");else historical_sfi_fe(&nhfile,(struct fe*)data,"probe-fe");}else{if(table)historical_sfo_procs.fn.sf_fe(&nhfile,(struct fe*)data,"probe-fe");else historical_sfo_fe(&nhfile,(struct fe*)data,"probe-fe");}break;
case 20:if(input){if(table)historical_sfi_procs.fn.sf_flag(&nhfile,(struct flag*)data,"probe-flag");else historical_sfi_flag(&nhfile,(struct flag*)data,"probe-flag");}else{if(table)historical_sfo_procs.fn.sf_flag(&nhfile,(struct flag*)data,"probe-flag");else historical_sfo_flag(&nhfile,(struct flag*)data,"probe-flag");}break;
case 21:if(input){if(table)historical_sfi_procs.fn.sf_fruit(&nhfile,(struct fruit*)data,"probe-fruit");else historical_sfi_fruit(&nhfile,(struct fruit*)data,"probe-fruit");}else{if(table)historical_sfo_procs.fn.sf_fruit(&nhfile,(struct fruit*)data,"probe-fruit");else historical_sfo_fruit(&nhfile,(struct fruit*)data,"probe-fruit");}break;
case 22:if(input){if(table)historical_sfi_procs.fn.sf_gamelog_line(&nhfile,(struct gamelog_line*)data,"probe-gamelog_line");else historical_sfi_gamelog_line(&nhfile,(struct gamelog_line*)data,"probe-gamelog_line");}else{if(table)historical_sfo_procs.fn.sf_gamelog_line(&nhfile,(struct gamelog_line*)data,"probe-gamelog_line");else historical_sfo_gamelog_line(&nhfile,(struct gamelog_line*)data,"probe-gamelog_line");}break;
case 23:if(input){if(table)historical_sfi_procs.fn.sf_kinfo(&nhfile,(struct kinfo*)data,"probe-kinfo");else historical_sfi_kinfo(&nhfile,(struct kinfo*)data,"probe-kinfo");}else{if(table)historical_sfo_procs.fn.sf_kinfo(&nhfile,(struct kinfo*)data,"probe-kinfo");else historical_sfo_kinfo(&nhfile,(struct kinfo*)data,"probe-kinfo");}break;
case 24:if(input){if(table)historical_sfi_procs.fn.sf_levelflags(&nhfile,(struct levelflags*)data,"probe-levelflags");else historical_sfi_levelflags(&nhfile,(struct levelflags*)data,"probe-levelflags");}else{if(table)historical_sfo_procs.fn.sf_levelflags(&nhfile,(struct levelflags*)data,"probe-levelflags");else historical_sfo_levelflags(&nhfile,(struct levelflags*)data,"probe-levelflags");}break;
case 25:if(input){if(table)historical_sfi_procs.fn.sf_ls_t(&nhfile,(struct ls_t*)data,"probe-ls_t");else historical_sfi_ls_t(&nhfile,(struct ls_t*)data,"probe-ls_t");}else{if(table)historical_sfo_procs.fn.sf_ls_t(&nhfile,(struct ls_t*)data,"probe-ls_t");else historical_sfo_ls_t(&nhfile,(struct ls_t*)data,"probe-ls_t");}break;
case 26:if(input){if(table)historical_sfi_procs.fn.sf_linfo(&nhfile,(struct linfo*)data,"probe-linfo");else historical_sfi_linfo(&nhfile,(struct linfo*)data,"probe-linfo");}else{if(table)historical_sfo_procs.fn.sf_linfo(&nhfile,(struct linfo*)data,"probe-linfo");else historical_sfo_linfo(&nhfile,(struct linfo*)data,"probe-linfo");}break;
case 27:if(input){if(table)historical_sfi_procs.fn.sf_mapseen_feat(&nhfile,(struct mapseen_feat*)data,"probe-mapseen_feat");else historical_sfi_mapseen_feat(&nhfile,(struct mapseen_feat*)data,"probe-mapseen_feat");}else{if(table)historical_sfo_procs.fn.sf_mapseen_feat(&nhfile,(struct mapseen_feat*)data,"probe-mapseen_feat");else historical_sfo_mapseen_feat(&nhfile,(struct mapseen_feat*)data,"probe-mapseen_feat");}break;
case 28:if(input){if(table)historical_sfi_procs.fn.sf_mapseen_flags(&nhfile,(struct mapseen_flags*)data,"probe-mapseen_flags");else historical_sfi_mapseen_flags(&nhfile,(struct mapseen_flags*)data,"probe-mapseen_flags");}else{if(table)historical_sfo_procs.fn.sf_mapseen_flags(&nhfile,(struct mapseen_flags*)data,"probe-mapseen_flags");else historical_sfo_mapseen_flags(&nhfile,(struct mapseen_flags*)data,"probe-mapseen_flags");}break;
case 29:if(input){if(table)historical_sfi_procs.fn.sf_mapseen_rooms(&nhfile,(struct mapseen_rooms*)data,"probe-mapseen_rooms");else historical_sfi_mapseen_rooms(&nhfile,(struct mapseen_rooms*)data,"probe-mapseen_rooms");}else{if(table)historical_sfo_procs.fn.sf_mapseen_rooms(&nhfile,(struct mapseen_rooms*)data,"probe-mapseen_rooms");else historical_sfo_mapseen_rooms(&nhfile,(struct mapseen_rooms*)data,"probe-mapseen_rooms");}break;
case 30:if(input){if(table)historical_sfi_procs.fn.sf_mkroom(&nhfile,(struct mkroom*)data,"probe-mkroom");else historical_sfi_mkroom(&nhfile,(struct mkroom*)data,"probe-mkroom");}else{if(table)historical_sfo_procs.fn.sf_mkroom(&nhfile,(struct mkroom*)data,"probe-mkroom");else historical_sfo_mkroom(&nhfile,(struct mkroom*)data,"probe-mkroom");}break;
case 31:if(input){if(table)historical_sfi_procs.fn.sf_monst(&nhfile,(struct monst*)data,"probe-monst");else historical_sfi_monst(&nhfile,(struct monst*)data,"probe-monst");}else{if(table)historical_sfo_procs.fn.sf_monst(&nhfile,(struct monst*)data,"probe-monst");else historical_sfo_monst(&nhfile,(struct monst*)data,"probe-monst");}break;
case 32:if(input){if(table)historical_sfi_procs.fn.sf_mvitals(&nhfile,(struct mvitals*)data,"probe-mvitals");else historical_sfi_mvitals(&nhfile,(struct mvitals*)data,"probe-mvitals");}else{if(table)historical_sfo_procs.fn.sf_mvitals(&nhfile,(struct mvitals*)data,"probe-mvitals");else historical_sfo_mvitals(&nhfile,(struct mvitals*)data,"probe-mvitals");}break;
case 33:if(input){if(table)historical_sfi_procs.fn.sf_obj(&nhfile,(struct obj*)data,"probe-obj");else historical_sfi_obj(&nhfile,(struct obj*)data,"probe-obj");}else{if(table)historical_sfo_procs.fn.sf_obj(&nhfile,(struct obj*)data,"probe-obj");else historical_sfo_obj(&nhfile,(struct obj*)data,"probe-obj");}break;
case 34:if(input){if(table)historical_sfi_procs.fn.sf_objclass(&nhfile,(struct objclass*)data,"probe-objclass");else historical_sfi_objclass(&nhfile,(struct objclass*)data,"probe-objclass");}else{if(table)historical_sfo_procs.fn.sf_objclass(&nhfile,(struct objclass*)data,"probe-objclass");else historical_sfo_objclass(&nhfile,(struct objclass*)data,"probe-objclass");}break;
case 35:if(input){if(table)historical_sfi_procs.fn.sf_q_score(&nhfile,(struct q_score*)data,"probe-q_score");else historical_sfi_q_score(&nhfile,(struct q_score*)data,"probe-q_score");}else{if(table)historical_sfo_procs.fn.sf_q_score(&nhfile,(struct q_score*)data,"probe-q_score");else historical_sfo_q_score(&nhfile,(struct q_score*)data,"probe-q_score");}break;
case 36:if(input){if(table)historical_sfi_procs.fn.sf_rm(&nhfile,(struct rm*)data,"probe-rm");else historical_sfi_rm(&nhfile,(struct rm*)data,"probe-rm");}else{if(table)historical_sfo_procs.fn.sf_rm(&nhfile,(struct rm*)data,"probe-rm");else historical_sfo_rm(&nhfile,(struct rm*)data,"probe-rm");}break;
case 37:if(input){if(table)historical_sfi_procs.fn.sf_spell(&nhfile,(struct spell*)data,"probe-spell");else historical_sfi_spell(&nhfile,(struct spell*)data,"probe-spell");}else{if(table)historical_sfo_procs.fn.sf_spell(&nhfile,(struct spell*)data,"probe-spell");else historical_sfo_spell(&nhfile,(struct spell*)data,"probe-spell");}break;
case 38:if(input){if(table)historical_sfi_procs.fn.sf_stairway(&nhfile,(struct stairway*)data,"probe-stairway");else historical_sfi_stairway(&nhfile,(struct stairway*)data,"probe-stairway");}else{if(table)historical_sfo_procs.fn.sf_stairway(&nhfile,(struct stairway*)data,"probe-stairway");else historical_sfo_stairway(&nhfile,(struct stairway*)data,"probe-stairway");}break;
case 39:if(input){if(table)historical_sfi_procs.fn.sf_s_level(&nhfile,(struct s_level*)data,"probe-s_level");else historical_sfi_s_level(&nhfile,(struct s_level*)data,"probe-s_level");}else{if(table)historical_sfo_procs.fn.sf_s_level(&nhfile,(struct s_level*)data,"probe-s_level");else historical_sfo_s_level(&nhfile,(struct s_level*)data,"probe-s_level");}break;
case 40:if(input){if(table)historical_sfi_procs.fn.sf_trap(&nhfile,(struct trap*)data,"probe-trap");else historical_sfi_trap(&nhfile,(struct trap*)data,"probe-trap");}else{if(table)historical_sfo_procs.fn.sf_trap(&nhfile,(struct trap*)data,"probe-trap");else historical_sfo_trap(&nhfile,(struct trap*)data,"probe-trap");}break;
case 41:if(input){if(table)historical_sfi_procs.fn.sf_version_info(&nhfile,(struct version_info*)data,"probe-version_info");else historical_sfi_version_info(&nhfile,(struct version_info*)data,"probe-version_info");}else{if(table)historical_sfo_procs.fn.sf_version_info(&nhfile,(struct version_info*)data,"probe-version_info");else historical_sfo_version_info(&nhfile,(struct version_info*)data,"probe-version_info");}break;
case 42:if(input){if(table)historical_sfi_procs.fn.sf_you(&nhfile,(struct you*)data,"probe-you");else historical_sfi_you(&nhfile,(struct you*)data,"probe-you");}else{if(table)historical_sfo_procs.fn.sf_you(&nhfile,(struct you*)data,"probe-you");else historical_sfo_you(&nhfile,(struct you*)data,"probe-you");}break;
case 43:if(input){if(table)historical_sfi_procs.fn.sf_any(&nhfile,(union any*)data,"probe-any");else historical_sfi_any(&nhfile,(union any*)data,"probe-any");}else{if(table)historical_sfo_procs.fn.sf_any(&nhfile,(union any*)data,"probe-any");else historical_sfo_any(&nhfile,(union any*)data,"probe-any");}break;
case 44:if(input){if(table)historical_sfi_procs.fn.sf_aligntyp(&nhfile,(aligntyp*)data,"probe-aligntyp");else historical_sfi_aligntyp(&nhfile,(aligntyp*)data,"probe-aligntyp");}else{if(table)historical_sfo_procs.fn.sf_aligntyp(&nhfile,(aligntyp*)data,"probe-aligntyp");else historical_sfo_aligntyp(&nhfile,(aligntyp*)data,"probe-aligntyp");}break;
case 45:if(input){if(table)historical_sfi_procs.fn.sf_boolean(&nhfile,(boolean*)data,"probe-boolean");else historical_sfi_boolean(&nhfile,(boolean*)data,"probe-boolean");}else{if(table)historical_sfo_procs.fn.sf_boolean(&nhfile,(boolean*)data,"probe-boolean");else historical_sfo_boolean(&nhfile,(boolean*)data,"probe-boolean");}break;
case 46:if(input){if(table)historical_sfi_procs.fn.sf_coordxy(&nhfile,(coordxy*)data,"probe-coordxy");else historical_sfi_coordxy(&nhfile,(coordxy*)data,"probe-coordxy");}else{if(table)historical_sfo_procs.fn.sf_coordxy(&nhfile,(coordxy*)data,"probe-coordxy");else historical_sfo_coordxy(&nhfile,(coordxy*)data,"probe-coordxy");}break;
case 47:if(input){if(table)historical_sfi_procs.fn.sf_genericptr(&nhfile,(genericptr_t*)data,"probe-genericptr_t");else historical_sfi_genericptr_t(&nhfile,(genericptr_t*)data,"probe-genericptr_t");}else{if(table)historical_sfo_procs.fn.sf_genericptr(&nhfile,(genericptr_t*)data,"probe-genericptr_t");else historical_sfo_genericptr_t(&nhfile,(genericptr_t*)data,"probe-genericptr_t");}break;
case 48:if(input){if(table)historical_sfi_procs.fn.sf_int(&nhfile,(int*)data,"probe-int");else historical_sfi_int(&nhfile,(int*)data,"probe-int");}else{if(table)historical_sfo_procs.fn.sf_int(&nhfile,(int*)data,"probe-int");else historical_sfo_int(&nhfile,(int*)data,"probe-int");}break;
case 49:if(input){if(table)historical_sfi_procs.fn.sf_int16(&nhfile,(int16*)data,"probe-int16");else historical_sfi_int16(&nhfile,(int16*)data,"probe-int16");}else{if(table)historical_sfo_procs.fn.sf_int16(&nhfile,(int16*)data,"probe-int16");else historical_sfo_int16(&nhfile,(int16*)data,"probe-int16");}break;
case 50:if(input){if(table)historical_sfi_procs.fn.sf_int32(&nhfile,(int32*)data,"probe-int32");else historical_sfi_int32(&nhfile,(int32*)data,"probe-int32");}else{if(table)historical_sfo_procs.fn.sf_int32(&nhfile,(int32*)data,"probe-int32");else historical_sfo_int32(&nhfile,(int32*)data,"probe-int32");}break;
case 51:if(input){if(table)historical_sfi_procs.fn.sf_int64(&nhfile,(int64*)data,"probe-int64");else historical_sfi_int64(&nhfile,(int64*)data,"probe-int64");}else{if(table)historical_sfo_procs.fn.sf_int64(&nhfile,(int64*)data,"probe-int64");else historical_sfo_int64(&nhfile,(int64*)data,"probe-int64");}break;
case 52:if(input){if(table)historical_sfi_procs.fn.sf_long(&nhfile,(long*)data,"probe-long");else historical_sfi_long(&nhfile,(long*)data,"probe-long");}else{if(table)historical_sfo_procs.fn.sf_long(&nhfile,(long*)data,"probe-long");else historical_sfo_long(&nhfile,(long*)data,"probe-long");}break;
case 53:if(input){if(table)historical_sfi_procs.fn.sf_schar(&nhfile,(schar*)data,"probe-schar");else historical_sfi_schar(&nhfile,(schar*)data,"probe-schar");}else{if(table)historical_sfo_procs.fn.sf_schar(&nhfile,(schar*)data,"probe-schar");else historical_sfo_schar(&nhfile,(schar*)data,"probe-schar");}break;
case 54:if(input){if(table)historical_sfi_procs.fn.sf_short(&nhfile,(short*)data,"probe-short");else historical_sfi_short(&nhfile,(short*)data,"probe-short");}else{if(table)historical_sfo_procs.fn.sf_short(&nhfile,(short*)data,"probe-short");else historical_sfo_short(&nhfile,(short*)data,"probe-short");}break;
case 55:if(input){if(table)historical_sfi_procs.fn.sf_size_t(&nhfile,(size_t*)data,"probe-size_t");else historical_sfi_size_t(&nhfile,(size_t*)data,"probe-size_t");}else{if(table)historical_sfo_procs.fn.sf_size_t(&nhfile,(size_t*)data,"probe-size_t");else historical_sfo_size_t(&nhfile,(size_t*)data,"probe-size_t");}break;
case 56:if(input){if(table)historical_sfi_procs.fn.sf_time_t(&nhfile,(time_t*)data,"probe-time_t");else historical_sfi_time_t(&nhfile,(time_t*)data,"probe-time_t");}else{if(table)historical_sfo_procs.fn.sf_time_t(&nhfile,(time_t*)data,"probe-time_t");else historical_sfo_time_t(&nhfile,(time_t*)data,"probe-time_t");}break;
case 57:if(input){if(table)historical_sfi_procs.fn.sf_uchar(&nhfile,(uchar*)data,"probe-uchar");else historical_sfi_uchar(&nhfile,(uchar*)data,"probe-uchar");}else{if(table)historical_sfo_procs.fn.sf_uchar(&nhfile,(uchar*)data,"probe-uchar");else historical_sfo_uchar(&nhfile,(uchar*)data,"probe-uchar");}break;
case 58:if(input){if(table)historical_sfi_procs.fn.sf_uint16(&nhfile,(uint16*)data,"probe-uint16");else historical_sfi_uint16(&nhfile,(uint16*)data,"probe-uint16");}else{if(table)historical_sfo_procs.fn.sf_uint16(&nhfile,(uint16*)data,"probe-uint16");else historical_sfo_uint16(&nhfile,(uint16*)data,"probe-uint16");}break;
case 59:if(input){if(table)historical_sfi_procs.fn.sf_uint32(&nhfile,(uint32*)data,"probe-uint32");else historical_sfi_uint32(&nhfile,(uint32*)data,"probe-uint32");}else{if(table)historical_sfo_procs.fn.sf_uint32(&nhfile,(uint32*)data,"probe-uint32");else historical_sfo_uint32(&nhfile,(uint32*)data,"probe-uint32");}break;
case 60:if(input){if(table)historical_sfi_procs.fn.sf_uint64(&nhfile,(uint64*)data,"probe-uint64");else historical_sfi_uint64(&nhfile,(uint64*)data,"probe-uint64");}else{if(table)historical_sfo_procs.fn.sf_uint64(&nhfile,(uint64*)data,"probe-uint64");else historical_sfo_uint64(&nhfile,(uint64*)data,"probe-uint64");}break;
case 61:if(input){if(table)historical_sfi_procs.fn.sf_ulong(&nhfile,(ulong*)data,"probe-ulong");else historical_sfi_ulong(&nhfile,(ulong*)data,"probe-ulong");}else{if(table)historical_sfo_procs.fn.sf_ulong(&nhfile,(ulong*)data,"probe-ulong");else historical_sfo_ulong(&nhfile,(ulong*)data,"probe-ulong");}break;
case 62:if(input){if(table)historical_sfi_procs.fn.sf_unsigned(&nhfile,(unsigned*)data,"probe-unsigned");else historical_sfi_unsigned(&nhfile,(unsigned*)data,"probe-unsigned");}else{if(table)historical_sfo_procs.fn.sf_unsigned(&nhfile,(unsigned*)data,"probe-unsigned");else historical_sfo_unsigned(&nhfile,(unsigned*)data,"probe-unsigned");}break;
case 63:if(input){if(table)historical_sfi_procs.fn.sf_ushort(&nhfile,(ushort*)data,"probe-ushort");else historical_sfi_ushort(&nhfile,(ushort*)data,"probe-ushort");}else{if(table)historical_sfo_procs.fn.sf_ushort(&nhfile,(ushort*)data,"probe-ushort");else historical_sfo_ushort(&nhfile,(ushort*)data,"probe-ushort");}break;
case 64:if(input){if(table)historical_sfi_procs.fn.sf_xint16(&nhfile,(xint16*)data,"probe-xint16");else historical_sfi_xint16(&nhfile,(xint16*)data,"probe-xint16");}else{if(table)historical_sfo_procs.fn.sf_xint16(&nhfile,(xint16*)data,"probe-xint16");else historical_sfo_xint16(&nhfile,(xint16*)data,"probe-xint16");}break;
case 65:if(input){if(table)historical_sfi_procs.fn.sf_xint8(&nhfile,(xint8*)data,"probe-xint8");else historical_sfi_xint8(&nhfile,(xint8*)data,"probe-xint8");}else{if(table)historical_sfo_procs.fn.sf_xint8(&nhfile,(xint8*)data,"probe-xint8");else historical_sfo_xint8(&nhfile,(xint8*)data,"probe-xint8");}break;
case 66:if(input){if(table)historical_sfi_procs.fn.sf_char(&nhfile,(char*)data,"probe-char",count);else historical_sfi_char(&nhfile,(char*)data,"probe-char",count);}else{if(table)historical_sfo_procs.fn.sf_char(&nhfile,(char*)data,"probe-char",count);else historical_sfo_char(&nhfile,(char*)data,"probe-char",count);}break;
case 67:if(input){if(table)historical_sfi_procs.fn.sf_bitfield(&nhfile,(uint8_t*)data,"probe-bitfield",count);else historical_sfi_bitfield(&nhfile,(uint8_t*)data,"probe-bitfield",count);}else{if(table)historical_sfo_procs.fn.sf_bitfield(&nhfile,(uint8_t*)data,"probe-bitfield",count);else historical_sfo_bitfield(&nhfile,(uint8_t*)data,"probe-bitfield",count);}break;
}armed=0;return panic_code;}
int probe_flags_value(void){return restoreinfo.mread_flags;}
int probe_eof(void){return nhfile.eof;}
int probe_panic_code(void){return panic_code;}
const char *probe_trace(void){return tracebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
void *probe_restore(void){return &restoreinfo;}
uintptr_t probe_proc(int input,int index){switch(index){
case 0:return input?(uintptr_t)historical_sfi_procs.fn.sf_arti_info:(uintptr_t)historical_sfo_procs.fn.sf_arti_info;
case 1:return input?(uintptr_t)historical_sfi_procs.fn.sf_nhrect:(uintptr_t)historical_sfo_procs.fn.sf_nhrect;
case 2:return input?(uintptr_t)historical_sfi_procs.fn.sf_branch:(uintptr_t)historical_sfo_procs.fn.sf_branch;
case 3:return input?(uintptr_t)historical_sfi_procs.fn.sf_bubble:(uintptr_t)historical_sfo_procs.fn.sf_bubble;
case 4:return input?(uintptr_t)historical_sfi_procs.fn.sf_cemetery:(uintptr_t)historical_sfo_procs.fn.sf_cemetery;
case 5:return input?(uintptr_t)historical_sfi_procs.fn.sf_context_info:(uintptr_t)historical_sfo_procs.fn.sf_context_info;
case 6:return input?(uintptr_t)historical_sfi_procs.fn.sf_nhcoord:(uintptr_t)historical_sfo_procs.fn.sf_nhcoord;
case 7:return input?(uintptr_t)historical_sfi_procs.fn.sf_damage:(uintptr_t)historical_sfo_procs.fn.sf_damage;
case 8:return input?(uintptr_t)historical_sfi_procs.fn.sf_dest_area:(uintptr_t)historical_sfo_procs.fn.sf_dest_area;
case 9:return input?(uintptr_t)historical_sfi_procs.fn.sf_dgn_topology:(uintptr_t)historical_sfo_procs.fn.sf_dgn_topology;
case 10:return input?(uintptr_t)historical_sfi_procs.fn.sf_dungeon:(uintptr_t)historical_sfo_procs.fn.sf_dungeon;
case 11:return input?(uintptr_t)historical_sfi_procs.fn.sf_d_level:(uintptr_t)historical_sfo_procs.fn.sf_d_level;
case 12:return input?(uintptr_t)historical_sfi_procs.fn.sf_ebones:(uintptr_t)historical_sfo_procs.fn.sf_ebones;
case 13:return input?(uintptr_t)historical_sfi_procs.fn.sf_edog:(uintptr_t)historical_sfo_procs.fn.sf_edog;
case 14:return input?(uintptr_t)historical_sfi_procs.fn.sf_egd:(uintptr_t)historical_sfo_procs.fn.sf_egd;
case 15:return input?(uintptr_t)historical_sfi_procs.fn.sf_emin:(uintptr_t)historical_sfo_procs.fn.sf_emin;
case 16:return input?(uintptr_t)historical_sfi_procs.fn.sf_engr:(uintptr_t)historical_sfo_procs.fn.sf_engr;
case 17:return input?(uintptr_t)historical_sfi_procs.fn.sf_epri:(uintptr_t)historical_sfo_procs.fn.sf_epri;
case 18:return input?(uintptr_t)historical_sfi_procs.fn.sf_eshk:(uintptr_t)historical_sfo_procs.fn.sf_eshk;
case 19:return input?(uintptr_t)historical_sfi_procs.fn.sf_fe:(uintptr_t)historical_sfo_procs.fn.sf_fe;
case 20:return input?(uintptr_t)historical_sfi_procs.fn.sf_flag:(uintptr_t)historical_sfo_procs.fn.sf_flag;
case 21:return input?(uintptr_t)historical_sfi_procs.fn.sf_fruit:(uintptr_t)historical_sfo_procs.fn.sf_fruit;
case 22:return input?(uintptr_t)historical_sfi_procs.fn.sf_gamelog_line:(uintptr_t)historical_sfo_procs.fn.sf_gamelog_line;
case 23:return input?(uintptr_t)historical_sfi_procs.fn.sf_kinfo:(uintptr_t)historical_sfo_procs.fn.sf_kinfo;
case 24:return input?(uintptr_t)historical_sfi_procs.fn.sf_levelflags:(uintptr_t)historical_sfo_procs.fn.sf_levelflags;
case 25:return input?(uintptr_t)historical_sfi_procs.fn.sf_ls_t:(uintptr_t)historical_sfo_procs.fn.sf_ls_t;
case 26:return input?(uintptr_t)historical_sfi_procs.fn.sf_linfo:(uintptr_t)historical_sfo_procs.fn.sf_linfo;
case 27:return input?(uintptr_t)historical_sfi_procs.fn.sf_mapseen_feat:(uintptr_t)historical_sfo_procs.fn.sf_mapseen_feat;
case 28:return input?(uintptr_t)historical_sfi_procs.fn.sf_mapseen_flags:(uintptr_t)historical_sfo_procs.fn.sf_mapseen_flags;
case 29:return input?(uintptr_t)historical_sfi_procs.fn.sf_mapseen_rooms:(uintptr_t)historical_sfo_procs.fn.sf_mapseen_rooms;
case 30:return input?(uintptr_t)historical_sfi_procs.fn.sf_mkroom:(uintptr_t)historical_sfo_procs.fn.sf_mkroom;
case 31:return input?(uintptr_t)historical_sfi_procs.fn.sf_monst:(uintptr_t)historical_sfo_procs.fn.sf_monst;
case 32:return input?(uintptr_t)historical_sfi_procs.fn.sf_mvitals:(uintptr_t)historical_sfo_procs.fn.sf_mvitals;
case 33:return input?(uintptr_t)historical_sfi_procs.fn.sf_obj:(uintptr_t)historical_sfo_procs.fn.sf_obj;
case 34:return input?(uintptr_t)historical_sfi_procs.fn.sf_objclass:(uintptr_t)historical_sfo_procs.fn.sf_objclass;
case 35:return input?(uintptr_t)historical_sfi_procs.fn.sf_q_score:(uintptr_t)historical_sfo_procs.fn.sf_q_score;
case 36:return input?(uintptr_t)historical_sfi_procs.fn.sf_rm:(uintptr_t)historical_sfo_procs.fn.sf_rm;
case 37:return input?(uintptr_t)historical_sfi_procs.fn.sf_spell:(uintptr_t)historical_sfo_procs.fn.sf_spell;
case 38:return input?(uintptr_t)historical_sfi_procs.fn.sf_stairway:(uintptr_t)historical_sfo_procs.fn.sf_stairway;
case 39:return input?(uintptr_t)historical_sfi_procs.fn.sf_s_level:(uintptr_t)historical_sfo_procs.fn.sf_s_level;
case 40:return input?(uintptr_t)historical_sfi_procs.fn.sf_trap:(uintptr_t)historical_sfo_procs.fn.sf_trap;
case 41:return input?(uintptr_t)historical_sfi_procs.fn.sf_version_info:(uintptr_t)historical_sfo_procs.fn.sf_version_info;
case 42:return input?(uintptr_t)historical_sfi_procs.fn.sf_you:(uintptr_t)historical_sfo_procs.fn.sf_you;
case 43:return input?(uintptr_t)historical_sfi_procs.fn.sf_any:(uintptr_t)historical_sfo_procs.fn.sf_any;
case 44:return input?(uintptr_t)historical_sfi_procs.fn.sf_aligntyp:(uintptr_t)historical_sfo_procs.fn.sf_aligntyp;
case 45:return input?(uintptr_t)historical_sfi_procs.fn.sf_boolean:(uintptr_t)historical_sfo_procs.fn.sf_boolean;
case 46:return input?(uintptr_t)historical_sfi_procs.fn.sf_coordxy:(uintptr_t)historical_sfo_procs.fn.sf_coordxy;
case 47:return input?(uintptr_t)historical_sfi_procs.fn.sf_genericptr:(uintptr_t)historical_sfo_procs.fn.sf_genericptr;
case 48:return input?(uintptr_t)historical_sfi_procs.fn.sf_int:(uintptr_t)historical_sfo_procs.fn.sf_int;
case 49:return input?(uintptr_t)historical_sfi_procs.fn.sf_int16:(uintptr_t)historical_sfo_procs.fn.sf_int16;
case 50:return input?(uintptr_t)historical_sfi_procs.fn.sf_int32:(uintptr_t)historical_sfo_procs.fn.sf_int32;
case 51:return input?(uintptr_t)historical_sfi_procs.fn.sf_int64:(uintptr_t)historical_sfo_procs.fn.sf_int64;
case 52:return input?(uintptr_t)historical_sfi_procs.fn.sf_long:(uintptr_t)historical_sfo_procs.fn.sf_long;
case 53:return input?(uintptr_t)historical_sfi_procs.fn.sf_schar:(uintptr_t)historical_sfo_procs.fn.sf_schar;
case 54:return input?(uintptr_t)historical_sfi_procs.fn.sf_short:(uintptr_t)historical_sfo_procs.fn.sf_short;
case 55:return input?(uintptr_t)historical_sfi_procs.fn.sf_size_t:(uintptr_t)historical_sfo_procs.fn.sf_size_t;
case 56:return input?(uintptr_t)historical_sfi_procs.fn.sf_time_t:(uintptr_t)historical_sfo_procs.fn.sf_time_t;
case 57:return input?(uintptr_t)historical_sfi_procs.fn.sf_uchar:(uintptr_t)historical_sfo_procs.fn.sf_uchar;
case 58:return input?(uintptr_t)historical_sfi_procs.fn.sf_uint16:(uintptr_t)historical_sfo_procs.fn.sf_uint16;
case 59:return input?(uintptr_t)historical_sfi_procs.fn.sf_uint32:(uintptr_t)historical_sfo_procs.fn.sf_uint32;
case 60:return input?(uintptr_t)historical_sfi_procs.fn.sf_uint64:(uintptr_t)historical_sfo_procs.fn.sf_uint64;
case 61:return input?(uintptr_t)historical_sfi_procs.fn.sf_ulong:(uintptr_t)historical_sfo_procs.fn.sf_ulong;
case 62:return input?(uintptr_t)historical_sfi_procs.fn.sf_unsigned:(uintptr_t)historical_sfo_procs.fn.sf_unsigned;
case 63:return input?(uintptr_t)historical_sfi_procs.fn.sf_ushort:(uintptr_t)historical_sfo_procs.fn.sf_ushort;
case 64:return input?(uintptr_t)historical_sfi_procs.fn.sf_xint16:(uintptr_t)historical_sfo_procs.fn.sf_xint16;
case 65:return input?(uintptr_t)historical_sfi_procs.fn.sf_xint8:(uintptr_t)historical_sfo_procs.fn.sf_xint8;
case 66:return input?(uintptr_t)historical_sfi_procs.fn.sf_char:(uintptr_t)historical_sfo_procs.fn.sf_char;
case 67:return input?(uintptr_t)historical_sfi_procs.fn.sf_bitfield:(uintptr_t)historical_sfo_procs.fn.sf_bitfield;
}return 0;}
unsigned probe_saved_size(int slot){int fd=open("/dev/null",O_RDONLY);if(fd>=0)close(fd);return (unsigned)lseek(fds[slot],0,SEEK_END);}
unsigned probe_read_file(int slot){char name[64];sprintf(name,"/sfstruct-%d.bin",slot);int fd=open(name,O_RDONLY);ssize_t n=read(fd,saved,sizeof saved);close(fd);return n<0?0:(unsigned)n;}
void *probe_saved(void){return saved;}
