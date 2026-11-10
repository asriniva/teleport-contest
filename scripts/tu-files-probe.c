/* FILES controlled foreign world. Real libc filesystem/stdio; original files.c only in reference. */
#include "hack.h"
#include "tu-files-layout.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <errno.h>
#include <emscripten.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
__typeof__(gl) gl;
__typeof__(svl) svl;
__typeof__(program_state) program_state;
__typeof__(svn) svn;
__typeof__(sysopt) sysopt;
__typeof__(ubirthday) ubirthday;
__typeof__(svd) svd;
__typeof__(gu) gu;
__typeof__(gb) gb;
__typeof__(flags) flags;
__typeof__(gs) gs;
__typeof__(svp) svp;
__typeof__(windowprocs) windowprocs;
__typeof__(iflags) iflags;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(gn) gn;
__typeof__(gw) gw;
__typeof__(hands_obj) hands_obj;
__typeof__(gi) gi;
__typeof__(gc) gc;
__typeof__(gd) gd;
__typeof__(gh) gh;
__typeof__(svc) svc;
__typeof__(u) u;
__typeof__(svm) svm;
const struct Gender genders[3]={{.filecode="Mal"},{.filecode="Fem"},{.filecode="Ntr"}};
const struct Align aligns[4]={{.filecode="Law"},{.filecode="Neu"},{.filecode="Cha"},{.filecode="Una"}};

static char buffers[8][8192],environment[8][512],config_name[1024];static d_level levelcell;static struct obj objectcell;static s_level specialcell;static NHFILE filecell;static char*pointercell[4];static void*allocations[8192];static size_t allocation_sizes[8192];static int nalloc;
static long opts[256];static char tracebuf[2097152],snap[2097152];static int tracepos,draws,callerline,reenter;static unsigned rngstate;static const char*callerfile,*callerowner;static long automatic_sp;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);va_end(ap);if(tracepos>=sizeof tracebuf-8192)abort();}
EM_JS(void,fixture_throw,(int kind),{throw new Error('FILES controlled '+kind);});
static void callback(void){if(opts[33])iflags.last_msg=opts[34];if(opts[30]){opts[30]=0;emscripten_resize_heap(emscripten_get_heap_size()+16777216);}if(opts[31]){opts[31]=0;fixture_throw(31);}if(opts[32]&&!reenter){reenter=1;logmsg("reentry:%s;",nh_basename("nested/source.c",FALSE));reenter=0;}}
static void backend_void(void){logmsg("sync;");callback();}
static void backend_clear(winid w){logmsg("clear:%d;",w);callback();}
static void backend_raw(const char*s){logmsg("raw:%s;",s);callback();}
static winid backend_create(int t){logmsg("create:%d;",t);callback();return opts[35]?-1:17;}
static void backend_destroy(winid w){logmsg("destroy:%d;",w);callback();}
static void backend_display(winid w,boolean b){logmsg("display:%d/%d;",w,b);callback();}
static void backend_put(winid w,int a,const char*s){if(opts[36]){long sp=emscripten_stack_get_current();if(!automatic_sp)automatic_sp=sp;logmsg("stack:%ld;",sp-automatic_sp);}logmsg("put:%d/%d:%s;",w,a,s);callback();}
static void backend_history(const char*s,boolean b){logmsg("history:%d:%s;",b,s);callback();}
static void vlog(const char*name,const char*f,va_list ap){logmsg("%s:",name);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);logmsg(";");callback();}
void pline(const char*f,...){va_list ap;va_start(ap,f);vlog("pline",f,ap);va_end(ap);}
void raw_printf(const char*f,...){va_list ap;va_start(ap,f);vlog("raw_printf",f,ap);va_end(ap);}
void impossible(const char*f,...){va_list ap;va_start(ap,f);vlog("impossible",f,ap);va_end(ap);}
void You_feel(const char*f,...){va_list ap;va_start(ap,f);vlog("You_feel",f,ap);va_end(ap);}
void config_error_add(const char*f,...){va_list ap;va_start(ap,f);vlog("config_error",f,ap);va_end(ap);}
static void*newallocation(unsigned n){if(nalloc>=8192)abort();void*p=malloc(n);allocations[nalloc]=p;allocation_sizes[nalloc++]=n;logmsg("alloc:%u;",n);return p;}
void more(void){logmsg("more;");callback();}
int teleport_compress_file(const char*filename,const char*cfn,int uncomp){logmsg("codec:%s:%s:%d;",filename,cfn,uncomp);callback();if(opts[20])return opts[20];FILE*in=fopen(uncomp?cfn:filename,"rb");if(!in)return 1;FILE*out=fopen(uncomp?filename:cfn,"wb");if(!out){fclose(in);return 1;}int c;while((c=fgetc(in))!=EOF)fputc(c,out);fclose(in);fclose(out);return 0;}
void (*teleport_native_signal(int sig,void(*fn)(int)))(int){logmsg("signal:%d/%d;",sig,fn==SIG_IGN);return SIG_DFL;}
void sethanguphandler(void(*fn)(int)){logmsg("hangup:%d;",fn==SIG_IGN);}
unsigned int sleep(unsigned int n){logmsg("sleep:%u;",n);callback();return 0;}
int __wrap_sscanf(const char*text,const char*format,...){if(opts[36]){long sp=emscripten_stack_get_current();if(!automatic_sp)automatic_sp=sp;logmsg("scan-stack:%ld;",sp-automatic_sp);}va_list ap;va_start(ap,format);int n=vsscanf(text,format,ap);va_end(ap);return n;}
int __real_fcntl(int,int,...);
int __wrap_fcntl(int fd,int cmd,...){va_list ap;va_start(ap,cmd);struct flock*p=va_arg(ap,struct flock*);va_end(ap);logmsg("fcntl:%d/%d:%d/%d/%lld/%lld;",fd,cmd,p->l_type,p->l_whence,p->l_start,p->l_len);callback();if(opts[40]>0){opts[40]--;errno=EAGAIN;return -1;}return __real_fcntl(fd,cmd,p);}

long * alloc(unsigned int a0){return newallocation(a0);}
boolean close_check(int a0){logmsg("close_check:%d;",a0);return opts[0];}
void bclose(int a0){logmsg("bclose:%d;",a0);close(a0);}
xint16 maxledgerno(void){logmsg("maxledgerno;");return opts[1];}
boolean In_quest(d_level * a0){logmsg("In_quest:%d/%d;",a0->dnum,a0->dlevel);return opts[2];}
s_level * Is_special(d_level * a0){logmsg("Is_special:%d/%d;",a0->dnum,a0->dlevel);return opts[3]?&specialcell:0;}
void regularize(char * a0){logmsg("regularize:%s;",a0);for(char*p=a0;*p;p++)if(*p=='/'||*p=='.'||*p==' ') *p='_';}
void sfo_char(NHFILE * a0,char * a1,const char * a2,int a3){logmsg("sfo_char:%s/%d:",a2,a3);for(int i=0;i<a3;i++)logmsg("%02x",(unsigned char)a1[i]);logmsg(";");}
int validate(NHFILE * a0,const char * a1,boolean a2){logmsg("validate:%s/%d;",a1,a2);callback();return opts[4];}
void get_plname_from_file(NHFILE * a0,char * a1,boolean a2){logmsg("get_plname:%d;",a2);int n=read(a0->fd,a1,31);if(n<0)n=0;a1[n]=0;callback();}
char * nh_getenv(const char * a0){logmsg("getenv:%s;",a0);const char*keys[]={"NETHACKDIR","HACKDIR","HOME","WIZKIT","NETHACKSYMBOLS"};for(int i=0;i<5;i++)if(!strcmp(a0,keys[i]))return environment[i][0]?environment[i]:0;return 0;}
void observe_object(struct obj * a0){logmsg("observe:%d;",a0->otyp);callback();}
int inv_cnt(boolean a0){logmsg("inv_cnt:%d;",a0);return opts[5];}
struct obj * merge_choice(struct obj * a0,struct obj * a1){logmsg("merge_choice:%d;",a1->otyp);return opts[6]?&objectcell:0;}
void add_to_migration(struct obj * a0){logmsg("migrate:%d;",a0->otyp);callback();}
struct obj * addinv(struct obj * a0){logmsg("addinv:%d;",a0->otyp);callback();return a0;}
struct obj * readobjnam(char * a0,struct obj * a1){logmsg("readobjnam:%s;",a0);callback();return opts[7]==1?0:opts[7]==2?&hands_obj:&objectcell;}
void wish_history_add(char * a0){logmsg("wish:%s;",a0);callback();}
void config_error_init(boolean a0,const char * a1,boolean a2){logmsg("config_init:%d/%s/%d;",a0,a1,a2);}
int config_error_done(void){logmsg("config_done;");return 0;}
boolean parse_conf_file(FILE * a0,boolean (*a1)(char *)){logmsg("parse;");char line[1024];boolean result=TRUE;while(fgets(line,sizeof line,a0)){strip_newline(line);if(!a1(line))result=FALSE;}return result;}
boolean proc_symset_line(char * a0){logmsg("symline:%s;",a0);if(opts[8])gc.chosen_symset_start=TRUE;if(opts[9])gc.chosen_symset_end=TRUE;return TRUE;}
void clear_symsetentry(int a0,boolean a1){logmsg("clear_symset:%d/%d;",a0,a1);gs.symset[a0].name=0;}
time_t getnow(void){logmsg("getnow:%ld;",opts[10]);return opts[10];}
char * version_string(char * a0,size_t a1){snprintf(a0,a1,"controlled-version");return a0;}
long yyyymmdd(time_t a0){logmsg("date:%ld;",a0);return opts[11];}
long hhmmss(time_t a0){logmsg("clock:%ld;",a0);return opts[12];}
void freedynamicdata(void){logmsg("freedynamicdata;");callback();}
void l_nhcore_done(void){logmsg("core_done;");callback();}
void after_opt_showpaths(const char * a0){logmsg("after_paths:%s;",a0?a0:"NULL");fixture_throw(91);__builtin_unreachable();}
void nh_terminate(int a0){logmsg("terminate:%d;",a0);fixture_throw(90);__builtin_unreachable();}
void set_configfile_name(const char * a0){logmsg("set_config:%s;",a0);snprintf(config_name,sizeof config_name,"%s",a0);}
char * get_configfile(void){return config_name;}
const char * get_default_configfile(void){return ".nethackrc";}
boolean rng_log_enabled(void){return !opts[13];}
void rng_log_set_caller(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerowner=a2;}
int (rn2)(int a0){if(a0<=0){logmsg("BADRNG:%d;",a0);fixture_throw(92);}rngstate=rngstate*1664525U+1013904223U;int n=(int)((rngstate>>1)%(unsigned)a0);draws++;logmsg("rn2:%s:%d:%s:%d=%d;",callerfile?callerfile:"",callerline,callerowner?callerowner:"",a0,n);callback();return n;}
long timet_to_seconds(time_t a0){logmsg("seconds:%ld;",a0);return a0;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/files.c"
#define TELEPORT_FILES_ORIGINAL_INCLUDED
#define TELEPORT_FILES_VALIDATE_ORIGINAL
struct nh_file * teleport_files_new_nhfile(void){return new_nhfile();}
void teleport_files_free_nhfile(NHFILE * a0){free_nhfile(a0);}
struct nh_file * teleport_files_viable_nhfile(NHFILE * a0){return viable_nhfile(a0);}
int teleport_files_strcmp_wrap(const void * a0,const void * a1){return strcmp_wrap(a0,a1);}
char * teleport_files_set_bonesfile_name(char * a0,d_level * a1){return set_bonesfile_name(a0,a1);}
char * teleport_files_set_bonestemp_name(void){return set_bonestemp_name();}
void teleport_files_redirect(const char * a0,const char * a1,FILE * a2,boolean a3){redirect(a0,a1,a2,a3);}
void teleport_files_docompress_file(const char * a0,boolean a1){docompress_file(a0,a1);}
struct nh_file * teleport_files_problematic_savefile(int a0,const char * a1){return problematic_savefile(a0,a1);}
int teleport_files_doconvert_file(const char * a0,int a1,boolean a2){return doconvert_file(a0,a1,a2);}
signed char teleport_files_make_converted_name(const char * a0){return make_converted_name(a0);}
struct _IO_FILE * teleport_files_fopen_wizkit_file(void){return fopen_wizkit_file();}
void teleport_files_wizkit_addinv(struct obj * a0){wizkit_addinv(a0);}
struct _IO_FILE * teleport_files_fopen_sym_file(void){return fopen_sym_file();}
int teleport_files_choose_passage(int a0,unsigned int a1){return choose_passage(a0,a1);}
#else
extern struct nh_file * teleport_files_new_nhfile(void);
extern void teleport_files_free_nhfile(NHFILE * a0);
extern struct nh_file * teleport_files_viable_nhfile(NHFILE * a0);
extern int teleport_files_strcmp_wrap(const void * a0,const void * a1);
extern char * teleport_files_set_bonesfile_name(char * a0,d_level * a1);
extern char * teleport_files_set_bonestemp_name(void);
extern void teleport_files_redirect(const char * a0,const char * a1,FILE * a2,boolean a3);
extern void teleport_files_docompress_file(const char * a0,boolean a1);
extern struct nh_file * teleport_files_problematic_savefile(int a0,const char * a1);
extern int teleport_files_doconvert_file(const char * a0,int a1,boolean a2);
extern signed char teleport_files_make_converted_name(const char * a0);
extern struct _IO_FILE * teleport_files_fopen_wizkit_file(void);
extern void teleport_files_wizkit_addinv(struct obj * a0);
extern struct _IO_FILE * teleport_files_fopen_sym_file(void);
extern int teleport_files_choose_passage(int a0,unsigned int a1);
#endif
#include "../nethack-c/wasm/tu-fragments/files-support.c"
long probe_call(int which,const long*a){switch(which){
case 0:return(long)nh_basename((const char *)a[0],(boolean)a[1]);
case 1:return(long)fname_encode((const char *)a[0],(char)a[1],(char *)a[2],(char *)a[3],(int)a[4]);
case 2:return(long)fname_decode((char)a[0],(char *)a[1],(char *)a[2],(int)a[3]);
case 3:return(long)fqname((const char *)a[0],(int)a[1],(int)a[2]);
case 4:return(long)validate_prefix_locations((char *)a[0]);
case 5:return(long)fopen_datafile((const char *)a[0],(const char *)a[1],(int)a[2]);
case 6:init_nhfile((NHFILE *)a[0]);return 0;
case 7:return(long)teleport_files_new_nhfile();
case 8:teleport_files_free_nhfile((NHFILE *)a[0]);return 0;
case 9:close_nhfile((NHFILE *)a[0]);return 0;
case 10:rewind_nhfile((NHFILE *)a[0]);return 0;
case 11:return(long)teleport_files_viable_nhfile((NHFILE *)a[0]);
case 12:return(long)nhclose((int)a[0]);
case 13:set_levelfile_name((char *)a[0],(int)a[1]);return 0;
case 14:return(long)create_levelfile((int)a[0],(char *)a[1]);
case 15:return(long)open_levelfile((int)a[0],(char *)a[1]);
case 16:delete_levelfile((int)a[0]);return 0;
case 17:clearlocks();return 0;
case 18:return(long)teleport_files_strcmp_wrap((const void *)a[0],(const void *)a[1]);
case 19:return(long)teleport_files_set_bonesfile_name((char *)a[0],(d_level *)a[1]);
case 20:return(long)teleport_files_set_bonestemp_name();
case 21:return(long)create_bonesfile((d_level *)a[0],(char **)a[1],(char *)a[2]);
case 22:commit_bonesfile((d_level *)a[0]);return 0;
case 23:return(long)open_bonesfile((d_level *)a[0],(char **)a[1]);
case 24:return(long)delete_bonesfile((d_level *)a[0]);
case 25:compress_bonesfile();return 0;
case 26:set_savefile_name((boolean)a[0]);return 0;
case 27:save_savefile_name((NHFILE *)a[0]);return 0;
case 28:set_error_savefile();return 0;
case 29:return(long)create_savefile();
case 30:return(long)open_savefile();
case 31:return(long)delete_savefile();
case 32:return(long)restore_saved_game();
case 33:return(long)get_freeing_nhfile();
case 34:return(long)check_panic_save();
case 35:return(long)plname_from_file((const char *)a[0],(boolean)a[1]);
case 36:return(long)get_saved_games();
case 37:free_saved_games((char **)a[0]);return 0;
case 38:teleport_files_redirect((const char *)a[0],(const char *)a[1],(FILE *)a[2],(boolean)a[3]);return 0;
case 39:teleport_files_docompress_file((const char *)a[0],(boolean)a[1]);return 0;
case 40:nh_compress((const char *)a[0]);return 0;
case 41:nh_uncompress((const char *)a[0]);return 0;
case 42:return(long)teleport_files_problematic_savefile((int)a[0],(const char *)a[1]);
case 43:return(long)teleport_files_doconvert_file((const char *)a[0],(int)a[1],(boolean)a[2]);
case 44:nh_sfconvert((const char *)a[0]);return 0;
case 45:nh_sfunconvert((const char *)a[0]);return 0;
case 46:return(long)teleport_files_make_converted_name((const char *)a[0]);
case 47:return(long)delete_convertedfile((const char *)a[0]);
case 48:free_convert_filenames();return 0;
case 49:return(long)contains_directory((const char *)a[0]);
case 50:return(long)lock_file((const char *)a[0],(int)a[1],(int)a[2]);
case 51:unlock_file((const char *)a[0]);return 0;
case 52:return(long)teleport_files_fopen_wizkit_file();
case 53:teleport_files_wizkit_addinv((struct obj *)a[0]);return 0;
case 54:return(long)proc_wizkit_line((char *)a[0]);
case 55:read_wizkit();return 0;
case 56:return(long)teleport_files_fopen_sym_file();
case 57:return(long)read_sym_file((int)a[0]);
case 58:check_recordfile((const char *)a[0]);return 0;
case 59:paniclog((const char *)a[0],(const char *)a[1]);return 0;
case 60:testinglog((const char *)a[0],(const char *)a[1],(const char *)a[2]);return 0;
case 61:do_deferred_showpaths((int)a[0]);return 0;
case 62:return(long)debugcore((const char *)a[0],(boolean)a[1]);
case 63:reveal_paths((int)a[0]);return 0;
case 64:return(long)teleport_files_choose_passage((int)a[0],(unsigned int)a[1]);
case 65:return(long)read_tribute((const char *)a[0],(const char *)a[1],(int)a[2],(char *)a[3],(int)a[4],(unsigned int)a[5]);
case 66:return(long)Death_quote((char *)a[0],(int)a[1]);
case 67:livelog_add((long)a[0],(const char *)a[1]);return 0;
default:abort();}}

void probe_reset(unsigned seed){free_convert_filenames();

memset((void*)&gl,0,sizeof gl);
memset((void*)&svl,0,sizeof svl);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&svn,0,sizeof svn);
memset((void*)&sysopt,0,sizeof sysopt);
memset((void*)&ubirthday,0,sizeof ubirthday);
memset((void*)&svd,0,sizeof svd);
memset((void*)&gu,0,sizeof gu);
memset((void*)&gb,0,sizeof gb);
memset((void*)&flags,0,sizeof flags);
memset((void*)&gs,0,sizeof gs);
memset((void*)&svp,0,sizeof svp);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&gn,0,sizeof gn);
memset((void*)&gw,0,sizeof gw);
memset((void*)&hands_obj,0,sizeof hands_obj);
memset((void*)&gi,0,sizeof gi);
memset((void*)&gc,0,sizeof gc);
memset((void*)&gd,0,sizeof gd);
memset((void*)&gh,0,sizeof gh);
memset((void*)&svc,0,sizeof svc);
memset((void*)&u,0,sizeof u);
memset((void*)&svm,0,sizeof svm);

 memset(buffers,0,sizeof buffers);memset(environment,0,sizeof environment);memset(&levelcell,0,sizeof levelcell);memset(&objectcell,0,sizeof objectcell);memset(&filecell,0,sizeof filecell);memset(pointercell,0,sizeof pointercell);memset(opts,0,sizeof opts);tracepos=draws=0;tracebuf[0]=0;errno=0;rngstate=seed;callerfile=callerowner=0;callerline=0;automatic_sp=0;
 strcpy(gl.lock,"level.0");strcpy(gs.SAVEF,"save/0Tester");strcpy(svp.plname,"Tester");gu.urole.filecode="Wiz";gu.urace.filecode="Hum";gu.urole.mnum=PM_WIZARD;svd.dungeons[0].boneid='D';specialcell.boneid='S';u.ualign.type=0;gh.hname="NetHack";gd.deferred_showpaths_dir=".";sysopt.livelog=0xff;opts[10]=1700000000L;opts[11]=20261110;opts[12]=123456;filecell.fd=-1;filecell.structlevel=TRUE;objectcell.otyp=LONG_SWORD;objectcell.oclass=WEAPON_CLASS;objectcell.quan=1;levelcell.dlevel=3;sysopt.saveformat[0]=historical;sysopt.bonesformat[0]=historical;WIN_MESSAGE=9;
 windowprocs.win_raw_print=backend_raw;windowprocs.win_wait_synch=backend_void;windowprocs.win_mark_synch=backend_void;windowprocs.win_clear_nhwindow=backend_clear;windowprocs.win_create_nhwindow=backend_create;windowprocs.win_destroy_nhwindow=backend_destroy;windowprocs.win_display_nhwindow=backend_display;windowprocs.win_putstr=backend_put;windowprocs.win_putmsghistory=backend_history;windowprocs.wp_id=wp_tty;
}
void probe_clear(void){tracepos=0;tracebuf[0]=0;}
void probe_option(int k,long v){opts[k]=v;}
void probe_attach(NHFILE*p,int kind,const char*name,const char*mode){if(kind==0){p->fpdef=fopen(name,mode);p->structlevel=FALSE;p->fieldlevel=TRUE;}else if(kind==1)p->fd=open(name,O_RDWR|O_CREAT,0600);else if(kind==2)p->fplog=fopen(name,mode);else p->fpdebug=fopen(name,mode);if(kind==0&&p->fpdef)fseek(p->fpdef,3,SEEK_SET);else if(kind==1&&p->fd>=0)lseek(p->fd,3,SEEK_SET);}
long probe_position(const NHFILE*p){return p->structlevel&&p->fd>=0?(long)lseek(p->fd,0,SEEK_CUR):p->fpdef?(long)ftell(p->fpdef):-999;}
struct fixture_observation { void*pointer;long scalar;unsigned char padding[8]; };static struct fixture_observation observation;
void*probe_observe(uint64_t p,long scalar){observation.pointer=(void*)(uintptr_t)p;observation.scalar=scalar;memset(observation.padding,0xa5,8);return &observation;}
size_t probe_offset(int i){return i==0?offsetof(struct fixture_observation,pointer):i==1?offsetof(struct fixture_observation,scalar):offsetof(struct fixture_observation,padding);}

void probe_buffer(int k,const char*s){snprintf(buffers[k],sizeof buffers[k],"%s",s);}
void probe_env(int k,const char*s){snprintf(environment[k],sizeof environment[k],"%s",s);}
void*probe_pointer(int kind,int i){switch(kind){case 0:return buffers[i];case 1:return &filecell;case 2:return &levelcell;case 3:return &objectcell;case 4:return &pointercell[i];case 5:return &hands_obj;case 6:return &specialcell;case 7:return &pointercell[i];default:abort();}}
void probe_open(int kind,const char*name,const char*mode){if(kind==0){filecell.fpdef=fopen(name,mode);filecell.structlevel=FALSE;filecell.fieldlevel=TRUE;}else if(kind==1)filecell.fd=open(name,O_RDWR|O_CREAT,0600);else if(kind==2)filecell.fplog=fopen(name,mode);else filecell.fpdebug=fopen(name,mode);}
void probe_record(int kind,int field,long value){void*p=kind==0?(void*)&filecell:kind==1?(void*)&objectcell:kind==2?(void*)&levelcell:0;int k=kind==0?30:kind==1?32:6;teleport_files_write(k,p,field,value);}
uint64_t probe_read(int kind,void*p,int field){return teleport_files_read(kind,p,field);}
void probe_close_stream(FILE*p){if(p)fclose(p);}
void*probe_address(int kind,void*p,int field){return teleport_files_address(kind,p,field);}
void probe_write(int kind,void*p,int field,long value){teleport_files_write(kind,p,field,value);}
const char*probe_trace(void){return tracebuf;}
long probe_stack(void){return emscripten_stack_get_current();}

int probe_uid(void){return getuid();}
const char*probe_snapshot(void){snprintf(snap,sizeof snap,"lock:%s;bones:%s;save:%s;plname:%s;nest:%d;flags:%d/%d/%d;context:%u/%d;msg:%d;object:%d/%d/%d/%d/%ld/%ld;state:%d/%d/%d;counts:%d/%d;level:%d/%d;",gl.lock,gb.bones,gs.SAVEF,svp.plname,gn.nesting,flags.debug,flags.explore,flags.female,svc.context.novel.id,svc.context.novel.count,iflags.last_msg,objectcell.bknown,objectcell.ox,objectcell.oy,objectcell.oclass,objectcell.quan,objectcell.owornmask,program_state.in_paniclog,program_state.wizkit_wishing,program_state.done_hup,draws,gs.symset_count,levelcell.dnum,levelcell.dlevel);size_t n=strlen(snap);for(int i=0;i<30;i++)n+=snprintf(snap+n,sizeof snap-n,"%d,",svc.context.novel.pasg[i]);n+=snprintf(snap+n,sizeof snap-n,";buffers:");for(int j=0;j<8;j++)n+=snprintf(snap+n,sizeof snap-n,"%s|",buffers[j]);return snap;}
const char*probe_nhfile(const NHFILE*p){if(!p)return "NULL";snprintf(snap,sizeof snap,"NHFILE:%d/%d/%d/%d/%d/%d/%d/%d/%ld/%ld/%d/%d/%d/%d/%d/%d/%d;",p->fd,p->mode,p->ftype,p->fnidx,p->structlevel,p->fieldlevel,p->addinfo,p->bendian,p->rcount,p->wcount,p->eof,p->style.deflt,p->style.binary,!!p->fpdef,!!p->fplog,!!p->fpdebug,!!p->nhfpconvert);return snap;}
long probe_global(int kind){return(long)teleport_files_global(kind);}
long probe_layout(int index){return(long)teleport_files_layout(index);}

