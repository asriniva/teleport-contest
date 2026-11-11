#include "hack.h"
#include <stddef.h>
#include <stdint.h>
/* Bounded allocation-ID observation belongs only to the paired test build. */
#ifdef UTILITY_SFCTOOL_TEST_OBSERVERS
extern long *utility_alloc(unsigned);
extern void utility_free(void *);
extern unsigned utility_log(int,int);
#else
long *utility_alloc(unsigned size) { return alloc(size); }
void utility_free(void *p) { free(p); }
#endif
#ifdef REFERENCE_SFCTOOL
#define alloc utility_alloc
#define free utility_free
#include UTILITY_SFCTOOL_SOURCE
#undef alloc
#undef free
#else
char *unconverted_filename, *converted_filename;
char plname[PL_NSIZ_PLUS];
struct version_info vers_info;
int renidx;
enum saveformats convertstyle;
boolean chosen_unconvert, explicit_option;
const char *thisdatamodel;
static char srclogfilenm[BUFSZ], dstlogfilenm[BUFSZ];
extern int utility_main_js(int,char**);
int main(int argc,char**argv){return utility_main_js(argc,argv);}
extern int process_savefile(const char*,enum saveformats,char*,enum saveformats,boolean);
extern NHFILE *open_srcfile(const char*,enum saveformats);
extern NHFILE *create_dstfile(char*,enum saveformats);
extern void my_sf_init(void);
extern void read_sysconf(void);
extern const char * briefname(const char *);
extern const char * style_to_text(enum saveformats);
extern int delete_savefile(void);
extern int util_strncmpi(const char *, const char *, size_t);
extern char * nh_getenv(const char *);
extern void new_mgivenname(struct monst *, int);
extern void free_mgivenname(struct monst *);
extern void newegd(struct monst *);
extern void free_egd(struct monst *);
extern void newepri(struct monst *);
extern void free_epri(struct monst *);
extern void neweshk(struct monst *);
extern void free_eshk(struct monst *);
extern void newemin(struct monst *);
extern void free_emin(struct monst *);
extern void newedog(struct monst *);
extern void free_edog(struct monst *);
extern void newebones(struct monst *);
extern void free_ebones(struct monst *);
extern void init_mextra(struct mextra *);
extern struct mextra * newmextra(void);
extern void newomonst(struct obj *);
extern void free_omonst(struct obj *);
extern void newomid(struct obj *);
extern void free_omid(struct obj *);
extern void new_omailcmd(struct obj *, const char *);
extern void free_omailcmd(struct obj *);
extern void init_oextra(struct oextra *);
extern struct oextra * newoextra(void);
extern void dealloc_mextra(struct monst *);
extern void dealloc_monst(struct monst *);
extern void new_oname(struct obj *, int);
extern void free_oname(struct obj *);
extern int length_without_val(const char *, int);
extern boolean match_optname(const char *, const char *, int, boolean);

#endif
size_t utility_layout(int i) { static const size_t v[]={sizeof(struct monst),sizeof(struct obj),sizeof(struct mextra),sizeof(struct oextra),sizeof(struct egd),sizeof(struct epri),sizeof(struct eshk),sizeof(struct emin),sizeof(struct edog),sizeof(struct ebones),NON_PM,BUFSZ,historical,exportascii,invalid,offsetof(struct monst,mextra),offsetof(struct obj,oextra),offsetof(struct mextra,mgivenname),offsetof(struct mextra,egd),offsetof(struct mextra,epri),offsetof(struct mextra,eshk),offsetof(struct mextra,emin),offsetof(struct mextra,edog),offsetof(struct mextra,ebones),offsetof(struct mextra,mcorpsenm),offsetof(struct oextra,oname),offsetof(struct oextra,omonst),offsetof(struct oextra,omailcmd),offsetof(struct oextra,omid),offsetof(struct eshk,bill_p)};return v[i];}
static struct monst mon;static struct obj obj;
void *utility_root(int which){return which?(void*)&obj:(void*)&mon;}
void utility_monflag(struct monst*m,int i,int value){switch(i){case 0:m->isgd=value;break;case 1:m->ispriest=value;break;case 2:m->isshk=value;break;case 3:m->isminion=value;break;case 4:m->mtame=value;}}
int utility_monflag_get(struct monst*m,int i){switch(i){case 0:return m->isgd;case 1:return m->ispriest;case 2:return m->isshk;case 3:return m->isminion;default:return m->mtame;}}
void utility_memory(int op,void*p,size_t n){if(op)memset(p,0xa5,n);else memset(p,0,n);}
void*utility_memset(void*p,int c,size_t n){return memset(p,c,n);}
char*utility_dupstr(const char*s){return dupstr(s);}
void*utility_newmonst(void){return newmonst();}
char*utility_strchr(const char*s,int c){return strchr(s,c);}
char*utility_strrchr(const char*s,int c){return strrchr(s,c);}
size_t utility_strlen(const char*s){return strlen(s);}
int utility_strncmpi(const char*a,const char*b,int n){return strncmpi(a,b,n);}
int utility_isspace(int c){return isspace(c);}
char*utility_getenv(const char*s){return getenv(s);}
uintptr_t utility_call(int op,uintptr_t a,uintptr_t b,uintptr_t c,uintptr_t d) {switch(op){
case 0: return (uintptr_t)briefname((const char*)a);
case 1: return (uintptr_t)style_to_text((enum saveformats)a);
case 2: return (uintptr_t)delete_savefile();
case 3: return (uintptr_t)util_strncmpi((const char*)a,(const char*)b,(size_t)c);
case 4: return (uintptr_t)nh_getenv((const char*)a);
case 5: new_mgivenname((struct monst*)a,(int)b);return 0;
case 6: free_mgivenname((struct monst*)a);return 0;
case 7: newegd((struct monst*)a);return 0;
case 8: free_egd((struct monst*)a);return 0;
case 9: newepri((struct monst*)a);return 0;
case 10: free_epri((struct monst*)a);return 0;
case 11: neweshk((struct monst*)a);return 0;
case 12: free_eshk((struct monst*)a);return 0;
case 13: newemin((struct monst*)a);return 0;
case 14: free_emin((struct monst*)a);return 0;
case 15: newedog((struct monst*)a);return 0;
case 16: free_edog((struct monst*)a);return 0;
case 17: newebones((struct monst*)a);return 0;
case 18: free_ebones((struct monst*)a);return 0;
case 19: init_mextra((struct mextra*)a);return 0;
case 20: return (uintptr_t)newmextra();
case 21: newomonst((struct obj*)a);return 0;
case 22: free_omonst((struct obj*)a);return 0;
case 23: newomid((struct obj*)a);return 0;
case 24: free_omid((struct obj*)a);return 0;
case 25: new_omailcmd((struct obj*)a,(const char*)b);return 0;
case 26: free_omailcmd((struct obj*)a);return 0;
case 27: init_oextra((struct oextra*)a);return 0;
case 28: return (uintptr_t)newoextra();
case 29: dealloc_mextra((struct monst*)a);return 0;
case 30: dealloc_monst((struct monst*)a);return 0;
case 31: new_oname((struct obj*)a,(int)b);return 0;
case 32: free_oname((struct obj*)a);return 0;
case 33: return (uintptr_t)length_without_val((const char*)a,(int)b);
case 34: return (uintptr_t)match_optname((const char*)a,(const char*)b,(int)c,(boolean)d);
default:return 0;} }

#ifndef REFERENCE_SFCTOOL
extern void utility_vararg_js(int,const char*,va_list);
void raw_printf(const char*line,...){va_list a;va_start(a,line);utility_vararg_js(0,line,a);va_end(a);}
void error(const char*s,...){va_list a;va_start(a,s);utility_vararg_js(1,s,a);va_end(a);abort();}
void pline(const char*s,...){va_list a;va_start(a,s);utility_vararg_js(2,s,a);va_end(a);}
void impossible(const char*s,...){va_list a;va_start(a,s);utility_vararg_js(3,s,a);va_end(a);}
extern void regularize(char*);
extern void chdirx(const char*,boolean);
extern void done1(int);
extern void utility_usage_js(int,char**);
#define usage utility_usage_js
#endif
FILE*utility_stdout(void){return stdout;}
FILE*utility_stderr(void){return stderr;}
int utility_vfprintf(FILE*f,const char*s,va_list a){return vfprintf(f,s,a);}
int utility_vprintf(const char*s,va_list a){return vprintf(s,a);}
void utility_va_end(va_list a){va_end(a);}
int utility_fprintf(FILE*f,const char*fmt,const char*a,const char*b,const char*c){return fprintf(f,fmt,a,b,c);}
void utility_error(const char*s,const char*d){error(s,d);}
void utility_exit(int status){exit(status);}
void utility_perror(const char*s){perror(s);}
int utility_chdir(const char*s){return chdir(s);}
uintptr_t utility_signal(int n,uintptr_t p){return(uintptr_t)signal(n,(void(*)(int))p);}
uintptr_t utility_signal_pointer(int which){return which?(uintptr_t)done1:(uintptr_t)SIG_IGN;}
void utility_set_ignintr(int n){flags.ignintr=n;}
int utility_get_ignintr(void){return flags.ignintr;}
void utility_extra_call(int op,const char*text,int number){switch(op){
case 0:regularize((char*)text);break;
case 1:raw_printf("str=%s int=%d long=%ld double=%.2f %%\n",text,number,-9007199254740993L,1.25);break;
case 2:pline("str=%s int=%d long=%ld double=%.2f %%\n",text,number,-9007199254740993L,1.25);break;
case 3:error("str=%s int=%d long=%ld double=%.2f %%\n",text,number,-9007199254740993L,1.25);break;
case 4:impossible("str=%s int=%d long=%ld double=%.2f %%\n",text,number,-9007199254740993L,1.25);break;
case 5:nh_terminate(number);break;
case 6:chdirx(text,number);break;
case 7:done1(number);break;
case 8:{char*argv[]={(char*)text,0};usage(1,argv);break;}
}}
void utility_flush(void){fflush(stdout);fflush(stderr);}
const char*utility_constant(int which){switch(which){case 0:return HACKDIR;default:return COMPRESS_EXTENSION;}}
int utility_scalar(int which){static const int a[]={EXIT_SUCCESS,EXIT_FAILURE,SIGINT};return a[which];}
void utility_streams(void){freopen("/stdout","w+",stdout);freopen("/stderr","w+",stderr);}
int utility_setenv(const char*a,const char*b){return setenv(a,b,1);}

#include <fcntl.h>
#ifndef O_BINARY
#define O_BINARY 0
#endif
#include "sfprocs.h"
extern struct sf_structlevel_procs zerosfoprocs, zerosfiprocs;
extern NHFILE*new_nhfile(void);
extern void free_nhfile(NHFILE*);
extern uchar cscbuf[];
void *utility_global(int key){switch(key){
case 0:return &unconverted_filename;case 1:return &converted_filename;case 2:return plname;case 3:return &vers_info;case 4:return &renidx;case 5:return &convertstyle;case 6:return &chosen_unconvert;case 7:return &explicit_option;case 8:return &thisdatamodel;case 9:return srclogfilenm;case 10:return dstlogfilenm;case 11:return &svm;case 12:return &iflags;case 13:return &restoreinfo;case 14:return cscbuf;case 15:return sfoprocs;case 16:return sfiprocs;case 17:return sfoflprocs;case 18:return sfiflprocs;case 19:return &zerosfoprocs;case 20:return &zerosfiprocs;case 21:return &historical_sfo_procs;case 22:return &historical_sfi_procs;case 23:return &exportascii_sfo_procs;case 24:return &exportascii_sfi_procs;}return 0;}
size_t utility_full_layout(int key){static const size_t a[]={
sizeof(NHFILE),offsetof(NHFILE,fd),sizeof(((NHFILE*)0)->fd),offsetof(NHFILE,mode),sizeof(((NHFILE*)0)->mode),offsetof(NHFILE,ftype),sizeof(((NHFILE*)0)->ftype),offsetof(NHFILE,fnidx),sizeof(((NHFILE*)0)->fnidx),offsetof(NHFILE,rcount),sizeof(((NHFILE*)0)->rcount),offsetof(NHFILE,structlevel),sizeof(((NHFILE*)0)->structlevel),offsetof(NHFILE,fieldlevel),sizeof(((NHFILE*)0)->fieldlevel),offsetof(NHFILE,addinfo),sizeof(((NHFILE*)0)->addinfo),offsetof(NHFILE,eof),sizeof(((NHFILE*)0)->eof),offsetof(NHFILE,fpdef),sizeof(((NHFILE*)0)->fpdef),offsetof(NHFILE,nhfpconvert),sizeof(((NHFILE*)0)->nhfpconvert),offsetof(struct instance_globals_saved_m,moves),offsetof(struct instance_flags,initoptions_noterminate),offsetof(struct restore_info,mread_flags),sizeof(((struct restore_info*)0)->mread_flags),sizeof(struct sf_structlevel_procs),sizeof(struct sf_fieldlevel_procs),NUM_SAVEFORMATS,READING,WRITING,NHF_SAVEFILE,SAVEPREFIX,O_RDONLY,O_BINARY,FCMASK,UNCONVERTING,CONVERTING,SF_UPTODATE,SF_CRITICAL_BYTE_COUNT_MISMATCH,SF_OUTDATED,SF_DM_IL32LLP64_ON_ILP32LL64,VERSION_MAJOR,VERSION_MINOR,PATCHLEVEL,EDITLEVEL,set_in_sysconf,sizeof(struct version_info),PL_NSIZ_PLUS,0};if(key<0)return SIZE(a);if(key==SIZE(a)-1)return get_critical_size_count();return a[key];}
int utility_full_call(int op,const char*a,char*b,int c,int d,int e){switch(op){case 0:return main(c,(char**)a);case 1:return process_savefile(a,c,b,d,e);case 2:my_sf_init();return 0;case 3:read_sysconf();return 0;}return -1;}
NHFILE*utility_file_call(int op,const char*a,int style){return op?create_dstfile((char*)a,style):open_srcfile(a,style);}
void utility_close_nhfile(NHFILE*p){close_nhfile(p);}
void utility_free_nhfile(NHFILE*p){free_nhfile(p);}
NHFILE*utility_new_nhfile(void){return new_nhfile();}
void utility_decl_globals_init(void){decl_globals_init();}
void utility_memcpy(void*a,const void*b,size_t n){memcpy(a,b,n);}
int utility_open(const char*a,int f,int n){return open(a,f,n);}
int utility_creat(const char*a,int f){return creat(a,f);}
FILE*utility_fopen(const char*a,const char*b){return fopen(a,b);}
int utility_fclose(FILE*a){return fclose(a);}
int utility_unlink(const char*a){return unlink(a);}
int utility_rename(const char*a,const char*b){return rename(a,b);}
const char*utility_fqname(const char*a,int b,int c){return fqname(a,b,c);}
void utility_nh_compress(const char*a){nh_compress(a);}
void utility_nh_uncompress(const char*a){nh_uncompress(a);}
const char*utility_datamodel(int a){return datamodel(a);}
void utility_runtime_info_init(void){runtime_info_init();}
void utility_assure_syscf_file(void){assure_syscf_file();}
void utility_config_error_init(boolean a,const char*b,boolean c){config_error_init(a,b,c);}
boolean utility_read_config_file(const char*a,int b){return read_config_file(a,b);}
boolean utility_config_error_done(void){return config_error_done();}
int utility_strcmp(const char*a,const char*b){return strcmp(a,b);}
int utility_contains_directory(const char*s){return contains_directory(s);}
char*utility_strcpy(char*a,const char*b){return strcpy(a,b);}
char*utility_strcat(char*a,const char*b){return strcat(a,b);}
char*utility_eos(char*a){return eos(a);}
int utility_snprintf(char*out,size_t n,const char*fmt,void*args){va_list a;memcpy(&a,&args,sizeof a);return vsnprintf(out,n,fmt,a);}
int utility_format(FILE*f,const char*fmt,void*args){va_list a;memcpy(&a,&args,sizeof a);return vfprintf(f,fmt,a);}
void utility_nh_snprintf(const char*f,int line,char*out,size_t n,const char*fmt,const char*a,const char*b,const char*c,const char*d){nh_snprintf(f,line,out,n,fmt,a,b,c,d);}
int utility_validate(NHFILE*f,const char*n,boolean b){return validate(f,n,b);}
const char*utility_what_datamodel(int format,int a,int b,int c,int d,int e){return what_datamodel_is_this(format,a,b,c,d,e);}
void utility_rewind_nhfile(NHFILE*f){rewind_nhfile(f);}
void utility_sfi_char(NHFILE*f,char*a,const char*n,int z){Sfi_char(f,a,n,z);}
void utility_sfi_uchar(NHFILE*f,uchar*a,const char*n){Sfi_uchar(f,a,n);}
void utility_sfi_xint8(NHFILE*f,xint8*a,const char*n){Sfi_xint8(f,a,n);}
void utility_sfi_version_info(NHFILE*f,struct version_info*a,const char*n){Sfi_version_info(f,a,n);}
void utility_store_critical_bytes(NHFILE*f){store_critical_bytes(f);}
void utility_get_plname(NHFILE*f,char*a,boolean b){get_plname_from_file(f,a,b);}
void utility_getlev(NHFILE*f,int pid,xint8 lev){getlev(f,pid,lev);}
int utility_restgamestate(NHFILE*f){return restgamestate(f);}
const char*utility_suffix(int i){
#ifdef REFERENCE_SFCTOOL
return rensuffixes[i];
#else
return 0;
#endif
}
void utility_make_header(const char*path,int fieldlevel){
 my_sf_init();NHFILE*f=new_nhfile();f->structlevel=!fieldlevel;f->fieldlevel=fieldlevel;f->fnidx=fieldlevel?exportascii:historical;f->mode=WRITING;
 if(fieldlevel)f->fpdef=fopen(path,"w+");else f->fd=creat(path,FCMASK);
 store_critical_bytes(f);Sfo_version_info(f,&vers_info,"version_info");close_nhfile(f);
}


_Static_assert(sizeof(void*)==8 && sizeof(size_t)==8 && sizeof(long)==8,"actual MEMORY64 profile");
_Static_assert(sizeof(((struct mextra*)0)->mcorpsenm)==4 && sizeof(((struct oextra*)0)->omid)==4,"helper scalar widths");
_Static_assert(sizeof(((NHFILE*)0)->rcount)==8 && sizeof(((NHFILE*)0)->structlevel)==1,"NHFILE scalar widths");
_Static_assert(_Generic((enum saveformats)0,unsigned int:1,default:0),"configured unsigned saveformats enum");
