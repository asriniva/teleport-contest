#include "hack.h"
#include "dlb.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef fopen
#undef fclose
#undef fseek
#undef fgets
#undef ftell
#undef free
extern FILE *fopen(const char *,const char *);
extern int fclose(FILE *),fseek(FILE *,long,int);
extern char *fgets(char *,int,FILE *);
extern long ftell(FILE *);
extern void free(void *);
struct you u;
__typeof__(gi) gi;
__typeof__(gt) gt;
__typeof__(gf) gf;
__typeof__(svo) svo;
__typeof__(go) go;
__typeof__(gm) gm;
__typeof__(disp) disp;
__typeof__(program_state) program_state;
__typeof__(iflags) iflags;
__typeof__(flags) flags;
__typeof__(windowprocs) windowprocs;
winid WIN_MESSAGE=3;
const char ynchars[]="yn",ynqchars[]="ynq",bogon_codes[]="-_+|=";
static const char *filenames[]={RUMORFILE,ORACLEFILE,BOGUSMONFILE,ENGRAVEFILE,EPITAPHFILE,"generic"};
static struct monst oracle;
static struct obj coin;
static FILE *files[256],*current;
static int closed[256],file_count,free_count,borrowed_free,opts[24],random_values[1024],random_length,random_index,yn_count;
static unsigned random_state;
static long wallet;
static char tracebuf[1048576],statebuf[65536],output[8192],caller[128];
static unsigned char saved[8192];
static size_t saved_size,restore_position;
static NHFILE savefile;
static winid checkwin;
static void *growth;
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
void nhassert_failed(const char *expression,const char *filepath,int line){const char *base=strrchr(filepath,'/');append("nhassert:%s:%s:%d;",expression,base?base+1:filepath,line);}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(There) MSG(verbalize)
void impossible(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append("impossible:%d:%s;",program_state.something_worth_saving,b);}
static int fileid(FILE *f){int i;for(i=0;i<file_count;i++)if(files[i]==f&&!closed[i])return i;return -1;}
FILE *teleport_probe_fopen(const char *name,const char *mode){int i;FILE *f;for(i=0;i<6;i++)if(!strcmp(name,filenames[i])&&(opts[0]&(1<<i))){append("open-fail:%s:%s;",name,mode);return NULL;}f=fopen(name,mode);if(f){if(file_count>=256)abort();files[file_count]=f;closed[file_count]=0;append("open:%s:%s:%d;",name,mode,file_count++);}else append("open-fail:%s:%s;",name,mode);return f;}
int teleport_probe_fclose(FILE *f){int id=fileid(f);append("close:%d:%ld;",id,ftell(f));if(id>=0)closed[id]=1;return fclose(f);}
int teleport_probe_fseek(FILE *f,long off,int whence){int id=fileid(f),v=fseek(f,off,whence);append("seek:%d:%ld:%d:%d:%ld;",id,off,whence,v,ftell(f));return v;}
char *teleport_probe_fgets(char *out,int size,FILE *f){char *v=fgets(out,size,f);append("gets:%d:%d:%d:%ld;",fileid(f),size,v!=NULL,ftell(f));if(opts[12]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew;");}return v;}
long teleport_probe_ftell(FILE *f){long p=ftell(f);append("tell:%d:%ld;",fileid(f),p);return p;}
void teleport_probe_free(void *p){int i,j;for(i=0;i<=NUMMONS;i++)for(j=0;j<NUM_MGENDERS;j++)if(p&&p==mons[i].pmnames[j])borrowed_free++;append("free:%d;",borrowed_free);free_count++;if(borrowed_free)abort();free(p);}
boolean rng_log_enabled(void){return opts[1];}
void rng_log_set_caller(const char *file,int line,const char *fn){const char *p=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:file,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
static int alt_rng(int n){int v=draw(n);append("alternate:%d:%d;",n,v);return v;}
void exercise(int attr,boolean inc){append("exercise:%d:%d;",attr,inc);if(opts[11]){opts[11]=0;append("nested-cap:%d;",CapitalMon("Archon"));}}
static winid create_window(int type){append("create:%d;",type);return opts[7]?WIN_ERR:19;}
static void put_window(winid win,int attr,const char *s){append("put:%d:%d:%s;",win,attr,s);}
static void display_window(winid win,boolean b){append("display:%d:%d;",win,b);}
static void destroy_window(winid win){append("destroy:%d;",win);}
boolean is_fainted(void){append("fainted;");return opts[2];}
long money_cnt(struct obj *o){append("money:%ld;",wallet);return wallet;}
char *Monnam(struct monst *m){return "Oracle";}
const char *currency(long n){append("currency:%ld;",n);return "gold pieces";}
char yn_function(const char *q,const char *choices,char def,boolean save){append("yn:%s:%s:%d:%d;",q,choices,def,save);return yn_count++?opts[4]:opts[3];}
long money2mon(struct monst *m,long n){append("pay:%ld;",n);wallet-=n;return n;}
void record_achievement(schar a){append("achievement:%d;",a);}
void more_experienced(int xp,int score){append("experience:%d:%d;",xp,score);u.uexp+=xp;}
void newexplevel(void){append("newlevel;");}
boolean the_unique_pm(struct permonst *p){return opts[13];}
boolean bogon_is_pname(char code){return code&&strchr("-+=",code)?TRUE:FALSE;}
boolean debugcore(const char *s,boolean wildcard){append("debug:%s:%d;",s,wildcard);return opts[10];}
void sfo_unsigned(NHFILE *f,unsigned *v,const char *name){append("sfo-u:%s:%u;",name,*v);memcpy(saved+saved_size,v,sizeof *v);saved_size+=sizeof *v;}
void sfo_ulong(NHFILE *f,unsigned long *v,const char *name){append("sfo-l:%s:%lu;",name,*v);memcpy(saved+saved_size,v,sizeof *v);saved_size+=sizeof *v;}
void sfi_unsigned(NHFILE *f,unsigned *v,const char *name){if(restore_position+sizeof *v>saved_size)abort();memcpy(v,saved+restore_position,sizeof *v);restore_position+=sizeof *v;append("sfi-u:%s:%u;",name,*v);}
void sfi_ulong(NHFILE *f,unsigned long *v,const char *name){if(restore_position+sizeof *v>saved_size)abort();memcpy(v,saved+restore_position,sizeof *v);restore_position+=sizeof *v;append("sfi-l:%s:%lu;",name,*v);}
#ifdef TELEPORT_REFERENCE_TU
#define fopen teleport_probe_fopen
#define fclose teleport_probe_fclose
#define fseek teleport_probe_fseek
#define fgets teleport_probe_fgets
#define ftell teleport_probe_ftell
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/rumors.c"
#undef fopen
#undef fclose
#undef fseek
#undef fgets
#undef ftell
#undef free
#else
extern void teleport_rumors_test_unpad(char*),teleport_rumors_test_init(FILE*),teleport_rumors_test_oracles(FILE*),teleport_rumors_test_others(const char*,const char*,winid*),teleport_rumors_test_couldnt(const char*),teleport_rumors_test_caps(void);
extern unsigned teleport_rumors_test_cap_count(int);
extern const char **teleport_rumors_test_cap_pointer(void);
extern char *teleport_rumors_test_line(FILE*,char*,unsigned,uintptr_t,long,long,unsigned);
#endif
#include "tu-rumors-layout.h"
void probe_reset(unsigned seed){int i;free_CapMons();if(svo.oracle_loc)free(svo.oracle_loc);for(i=0;i<file_count;i++)if(!closed[i])fclose(files[i]);if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&gi,0,sizeof gi);memset(&gt,0,sizeof gt);memset(&gf,0,sizeof gf);memset(&svo,0,sizeof svo);memset(&go,0,sizeof go);memset(&gm,0,sizeof gm);memset(&disp,0,sizeof disp);memset(&program_state,0,sizeof program_state);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(opts,0,sizeof opts);opts[1]=1;wallet=0;opts[3]=opts[4]='q';monst_globals_init();objects_globals_init();u.ulevel=10;oracle.mpeaceful=1;gi.invent=&coin;random_state=seed;random_length=random_index=yn_count=0;file_count=free_count=borrowed_free=0;current=NULL;saved_size=restore_position=0;checkwin=WIN_ERR;memset(output,0xa5,sizeof output);output[0]=0;tracebuf[0]=caller[0]=0;windowprocs.win_create_nhwindow=create_window;windowprocs.win_putstr=put_window;windowprocs.win_display_nhwindow=display_window;windowprocs.win_destroy_nhwindow=destroy_window;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int i,int v){opts[i]=v;if(i==5)wallet=v;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_file(int id,const char *bytes,unsigned size,int encrypt_from){FILE *f=fopen(filenames[id],"wb");unsigned pos=0,line=0;if(!f)abort();while(pos<size){unsigned end=pos;char buf[16384],enc[16384];while(end<size&&bytes[end]!='\n')end++;if(end<size)end++;if(end-pos>=sizeof buf)abort();memcpy(buf,bytes+pos,end-pos);buf[end-pos]=0;if(encrypt_from>=0&&(int)line>=encrypt_from&&strcmp(buf,"---\n"))xcrypt(buf,enc);else memcpy(enc,buf,end-pos+1);fwrite(enc,1,end-pos,f);pos=end;line++;}fclose(f);}
void probe_remove(int id){remove(filenames[id]);}
int probe_open(int id){current=teleport_probe_fopen(filenames[id],"r");return current!=NULL;}
void probe_close(void){if(current&&fileid(current)>=0)teleport_probe_fclose(current);current=NULL;}
long probe_position(void){return current&&fileid(current)>=0?ftell(current):-1;}
int probe_action(int op,int a,int b,long start,long end,unsigned pad,const char *text){switch(op){case 0:getrumor(a,output,b);break;case 1:rumor_check();break;case 2:get_rnd_text(filenames[a],output,b?alt_rng:rn2,pad);break;case 3:outrumor(a,b);break;case 4:savefile.mode=a;saved_size=0;save_oracles(&savefile);break;case 5:restore_oracles(&savefile);break;case 6:outoracle(a,b);break;case 7:return doconsult(a?&oracle:NULL);case 8:return CapitalMon(text);case 9:free_CapMons();break;case 10:strncpy(output,text,sizeof output);output[sizeof output-1]=0;
#ifdef TELEPORT_REFERENCE_TU
unpadline(output);
#else
teleport_rumors_test_unpad(output);
#endif
break;case 11:
#ifdef TELEPORT_REFERENCE_TU
init_rumors(current);
#else
teleport_rumors_test_init(current);
#endif
break;case 12:
#ifdef TELEPORT_REFERENCE_TU
get_rnd_line(current,output,a,b?alt_rng:rn2,start,end,pad);
#else
teleport_rumors_test_line(current,output,a,(uintptr_t)(b?alt_rng:rn2),start,end,pad);
#endif
break;case 13:
#ifdef TELEPORT_REFERENCE_TU
init_oracles(current);
#else
teleport_rumors_test_oracles(current);
#endif
break;case 14:
#ifdef TELEPORT_REFERENCE_TU
others_check(text,filenames[a],&checkwin);
#else
teleport_rumors_test_others(text,filenames[a],&checkwin);
#endif
break;case 15:
#ifdef TELEPORT_REFERENCE_TU
couldnt_open_file(filenames[a]);
#else
teleport_rumors_test_couldnt(filenames[a]);
#endif
break;case 16:
#ifdef TELEPORT_REFERENCE_TU
init_CapMons();
#else
teleport_rumors_test_caps();
#endif
break;}return 0;}
const char *probe_output(void){return output;}
size_t probe_output_size(void){return sizeof output;}
unsigned probe_cap_count(int field){
#ifdef TELEPORT_REFERENCE_TU
return field==0?CapMonstCnt:field==1?CapBogonCnt:CapMonSiz;
#else
return teleport_rumors_test_cap_count(field);
#endif
}
const void *probe_cap_pointer(void){
#ifdef TELEPORT_REFERENCE_TU
return CapMons;
#else
return teleport_rumors_test_cap_pointer();
#endif
}
const char *probe_cap_name(unsigned n){
#ifdef TELEPORT_REFERENCE_TU
return CapMons?CapMons[n]:NULL;
#else
const char **p=teleport_rumors_test_cap_pointer();return p?p[n]:NULL;
#endif
}
uintptr_t probe_rng_pointer_id(int which){return (uintptr_t)(which?alt_rng:rn2);}
void *probe_saved_pointer(void){return saved;}
size_t probe_saved_size(void){return saved_size;}
void probe_restore_position(unsigned n){restore_position=n;}
void probe_hero(int key,long v){switch(key){case 0:u.ulevel=v;break;case 1:u.uevent.major_oracle=v;break;case 2:u.uevent.minor_oracle=v;break;case 3:gi.in_mklev=v;break;case 4:program_state.something_worth_saving=v;break;case 5:iflags.debug_fuzzer=v;break;case 6:wizard=v;break;case 7:oracle.mpeaceful=v;break;case 8:gm.multi=v;break;case 9:wallet=v;break;}}
void probe_prop(int p,int field,long v){if(field==0)u.uprops[p].intrinsic=v;else if(field==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
size_t probe_stack(void){return emscripten_stack_get_current();}
int probe_free_count(void){return free_count;}
int probe_open_count(void){return file_count;}
const char *probe_snapshot(void){char *p=statebuf;unsigned i;p+=sprintf(p,"rumor:%ld:%lu:%ld:%ld:%lu:%ld;oracle:%d:%u:",gt.true_rumor_size,gt.true_rumor_start,gt.true_rumor_end,gf.false_rumor_size,gf.false_rumor_start,gf.false_rumor_end,go.oracle_flg,svo.oracle_cnt);for(i=0;i<svo.oracle_cnt;i++)p+=sprintf(p,"%lu,",svo.oracle_loc[i]);p+=sprintf(p,";hero:%d:%d:%d:%ld:%ld:%d:%d:%d:%d:%d:%ld;files:",u.ulevel,u.uevent.major_oracle,u.uevent.minor_oracle,u.uexp,gm.multi,disp.botl,program_state.something_worth_saving,free_count,borrowed_free,checkwin,wallet);for(i=0;i<(unsigned)file_count;i++)p+=sprintf(p,"%d,%ld/",closed[i],closed[i]?-1:ftell(files[i]));return statebuf;}
