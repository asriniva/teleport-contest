/* Controlled path/lock/world/UI fixture; parsing and streams use actual libc. */
#include "hack.h"
#include "dlb.h"
#include "../nethack-c/wasm/tu-fragments/topten-types.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdlib.h>
#undef free
extern void free(void*);
__typeof__(ubirthday)ubirthday;__typeof__(urealtime)urealtime;__typeof__(u)u;__typeof__(gm)gm;__typeof__(svk)svk;__typeof__(gt)gt;__typeof__(iflags)iflags;__typeof__(program_state)program_state;__typeof__(sysopt)sysopt;__typeof__(gu)gu;__typeof__(svp)svp;__typeof__(svm)svm;__typeof__(flags)flags;__typeof__(gi)gi;__typeof__(svd)svd;__typeof__(gh)gh;__typeof__(windowprocs)windowprocs;
static char tracebuf[1048576],snapbuf[1048576],target_snapshot[65536],inputbuf[65536],filebuf[3][65536],names[4096],reasons[4096],scratch[4096],objname[100],monname[100];
static int opts[40],allocs,frees,open_count,close_count,windows,rolls[128],roll_count,roll_index,depth_of_callback,corpsenm_value;static unsigned rngstate;static void*growth;
static FILE*sourcefile,*targetfile,*open_files[16];static int fileids[16];static char argument_text[32][1024];static char*arguments[32];static int argument_count;
static struct obj node;static struct monst monster;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
void teleport_probe_free(void*p){if(p){frees++;logmsg("free;");}free(p);}
#define free teleport_probe_free
long*alloc(unsigned n){allocs++;logmsg("alloc:%u;",n);void*p=malloc(n);if(!p)abort();return p;}
static void callback(void){if(opts[30]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}if(opts[31]&&!depth_of_callback){depth_of_callback++;logmsg("reentry:%d;",observable_depth(&u.uz));depth_of_callback--;}}
void panic(const char*f,...){abort();}void impossible(const char*f,...){va_list ap;va_start(ap,f);logmsg("impossible:");vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");callback();}
static void raw_text(const char*s){logmsg("raw:%s;",s);callback();}static void raw_bold(const char*s){logmsg("bold:%s;",s);callback();}static void window_put(winid w,int a,const char*s){logmsg("put:%d:%d:%s;",w,a,s);callback();}static winid window_new(int t){logmsg("window:%d;",t);return ++windows;}static void window_show(winid w,boolean b){logmsg("display:%d:%d;",w,b);}static void window_destroy(winid w){logmsg("destroy:%d;",w);}
void raw_printf(const char*f,...){va_list ap;va_start(ap,f);logmsg("printf:");vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");callback();}
uid_t getuid(void){logmsg("uid:%u;",(unsigned)opts[0]);return opts[0];}
schar depth(d_level*l){logmsg("depth:%d:%d;",l->dnum,l->dlevel);return l->dlevel+opts[1];}xint16 deepest_lev_reached(boolean b){logmsg("deepest:%d;",b);return opts[2];}
long yyyymmdd(time_t t){logmsg("date:%ld;",(long)t);return 20000101L+(long)(t/86400);}
long timet_to_seconds(time_t t){return t;}
boolean lock_file(const char*n,int prefix,int tries){int id=!strcmp(n,RECORD)?0:!strcmp(n,LOGFILE)?1:2;logmsg("lock:%s:%d:%d;",n,prefix,tries);return !(opts[3]&(1<<id));}void unlock_file(const char*n){logmsg("unlock:%s;",n);}
FILE*fopen_datafile(const char*n,const char*mode,int prefix){int id=!strcmp(n,RECORD)?0:!strcmp(n,LOGFILE)?1:2;logmsg("open:%s:%s:%d;",n,mode,prefix);if(opts[4]&(1<<id))return 0;if(id==0&&mode[0]=='w'&&opts[5])return 0;FILE*f=tmpfile();if(!f)abort();if(mode[0]!='w'){fputs(filebuf[id],f);if(mode[0]=='a')fseek(f,0,SEEK_END);else rewind(f);}for(int i=0;i<16;i++)if(!open_files[i]){open_files[i]=f;fileids[i]=id;open_count++;return f;}abort();}
extern int __real_fclose(FILE*);
int __wrap_fclose(FILE*f){for(int i=0;i<16;i++)if(open_files[i]==f){fflush(f);fseek(f,0,SEEK_SET);size_t n=fread(filebuf[fileids[i]],1,sizeof filebuf[0]-1,f);filebuf[fileids[i]][n]=0;logmsg("close:%d;",fileids[i]);open_files[i]=0;close_count++;break;}return __real_fclose(f);}
void init_dungeons(void){logmsg("init_dungeons;");wiz1_level.dlevel=7;callback();}void free_dungeons(void){logmsg("free_dungeons;");}
char*an(const char*s){static char b[8192];snprintf(b,sizeof b,"a %s",s);return b;}
int num_genocides(void){return opts[6];}boolean sokoban_in_play(void){return opts[7];}
const char*rank_of(int lev,short role,boolean female){static char b[80];snprintf(b,sizeof b,"Rank %d %s",lev,female?"Lady":"Lord");logmsg("rank:%d:%d:%d;",lev,role,female);return b;}int rank_to_xlev(int rank){return rank*3;}
long money_cnt(struct obj*o){logmsg("money:%d;",o==&node);return opts[8]?(1L<<54)+3:0;}long hidden_gold(boolean b){logmsg("hidden:%d;",b);return opts[9]?(1L<<53)+5:0;}
int canseemon(struct monst*m){(void)m;return opts[10];}
void set_corpsenm(struct obj*o,int n){logmsg("corpsenm:%d;",n);corpsenm_value=n;o->corpsenm=n;}
struct obj*oname(struct obj*o,const char*n,unsigned f){logmsg("oname:%s:%u;",n,f);strcpy(objname,n);return o;}struct monst*christen_monst(struct monst*m,const char*n){logmsg("christen:%s;",n);strcpy(monname,n);return m;}
boolean rng_log_enabled(void){return TRUE;}static char origin[100];void rng_log_set_caller(const char*f,int line,const char*fn){const char*p=strrchr(f,'/');snprintf(origin,sizeof origin,"%s:%d:%s",p?p+1:f,line,fn);}
int(rn2)(int n){if(n<1)abort();rngstate=rngstate*1664525U+1013904223U;int v=(unsigned)(roll_index<roll_count?rolls[roll_index]:rngstate)%n;roll_index++;logmsg("rng:%d:%d@%s;",n,v,origin);return v;}int(rnd)(int n){return(rn2)(n)+1;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/topten.c"
#define TOPTEN_VALIDATE_REFERENCE
#else
extern void  teleport_topten_test_topten_print(const char *);
#define topten_print teleport_topten_test_topten_print
extern void  teleport_topten_test_topten_print_bold(const char *);
#define topten_print_bold teleport_topten_test_topten_print_bold
extern void  teleport_topten_test_discardexcess(FILE *);
#define discardexcess teleport_topten_test_discardexcess
extern void  teleport_topten_test_readentry(FILE *, struct teleport_toptenentry *);
#define readentry teleport_topten_test_readentry
extern void  teleport_topten_test_writeentry(FILE *, struct teleport_toptenentry *);
#define writeentry teleport_topten_test_writeentry
extern void  teleport_topten_test_writexlentry(FILE *, struct teleport_toptenentry *, int);
#define writexlentry teleport_topten_test_writexlentry
extern long  teleport_topten_test_encodexlogflags(void);
#define encodexlogflags teleport_topten_test_encodexlogflags
extern long  teleport_topten_test_encodeconduct(void);
#define encodeconduct teleport_topten_test_encodeconduct
extern long  teleport_topten_test_encodeachieve(boolean);
#define encodeachieve teleport_topten_test_encodeachieve
extern void  teleport_topten_test_add_achieveX(char *, const char *, boolean);
#define add_achieveX teleport_topten_test_add_achieveX
extern char * teleport_topten_test_encode_extended_achievements(char *);
#define encode_extended_achievements teleport_topten_test_encode_extended_achievements
extern char * teleport_topten_test_encode_extended_conducts(char *);
#define encode_extended_conducts teleport_topten_test_encode_extended_conducts
extern void  teleport_topten_test_free_ttlist(struct teleport_toptenentry *);
#define free_ttlist teleport_topten_test_free_ttlist
extern void  teleport_topten_test_outheader(void);
#define outheader teleport_topten_test_outheader
extern void  teleport_topten_test_outentry(int, struct teleport_toptenentry *, boolean);
#define outentry teleport_topten_test_outentry
extern int  teleport_topten_test_score_wanted(boolean, int, struct teleport_toptenentry *, int, const char **, int);
#define score_wanted teleport_topten_test_score_wanted
extern int  teleport_topten_test_classmon(char *);
#define classmon teleport_topten_test_classmon
#endif
#include "tu-topten-layout.h"
#ifdef TELEPORT_REFERENCE_TU
typedef struct toptenentry entry_t;
#else
typedef struct teleport_toptenentry entry_t;
#endif
static entry_t entries[4],*last_entry,*retained_entry;
static void init_entry(entry_t*e){memset(e,0,sizeof *e);e->points=123;e->ver_major=VERSION_MAJOR;e->ver_minor=VERSION_MINOR;e->patchlevel=PATCHLEVEL;e->deathdnum=0;e->deathlev=3;e->maxlvl=7;e->hp=4;e->maxhp=20;e->birthdate=20240101;e->deathdate=20241109;e->uid=42;strcpy(e->plrole,"Arc");strcpy(e->plrace,"Hum");strcpy(e->plgend,"Mal");strcpy(e->plalign,"Neu");strcpy(e->name,"Player");strcpy(e->death,"killed by a newt");}
void probe_reset(unsigned seed){int i;if(sourcefile)__real_fclose(sourcefile);if(targetfile)__real_fclose(targetfile);for(i=0;i<16;i++)if(open_files[i]){__real_fclose(open_files[i]);open_files[i]=0;}if(growth)free(growth);growth=0;memset(&u,0,sizeof u);memset(&gm,0,sizeof gm);memset(&svk,0,sizeof svk);memset(&gt,0,sizeof gt);memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(&sysopt,0,sizeof sysopt);memset(&gu,0,sizeof gu);memset(&svp,0,sizeof svp);memset(&svm,0,sizeof svm);memset(&flags,0,sizeof flags);memset(&gi,0,sizeof gi);memset(&svd,0,sizeof svd);memset(&gh,0,sizeof gh);memset(&node,0,sizeof node);memset(&monster,0,sizeof monster);memset(opts,0,sizeof opts);memset(filebuf,0,sizeof filebuf);memset(argument_text,0,sizeof argument_text);memset(arguments,0,sizeof arguments);memset(objname,0,sizeof objname);memset(monname,0,sizeof monname);memset(scratch,0,sizeof scratch);for(i=0;i<4;i++)init_entry(&entries[i]);windowprocs.win_raw_print=raw_text;windowprocs.win_raw_print_bold=raw_bold;windowprocs.win_putstr=window_put;windowprocs.win_create_nhwindow=window_new;windowprocs.win_display_nhwindow=window_show;windowprocs.win_destroy_nhwindow=window_destroy;u.urexp=777;u.uhp=8;u.uhpmax=30;u.umortality=2;u.uz.dnum=0;u.uz.dlevel=5;u.ualign.type=0;gu.urole=roles[0];gu.urace=races[0];ubirthday=86400;urealtime.finish_time=259200;urealtime.realtime=1024;svm.moves=1234;strcpy(svp.plname,"Player");strcpy(svk.killer.name,"a newt");svk.killer.format=KILLED_BY;gt.toptenwin=WIN_ERR;sysopt.persmax=2;sysopt.pointsmin=1;sysopt.entrymax=20;sysopt.tt_oname_maxrank=3;flags.end_top=10;flags.end_around=2;flags.bones=1;flags.initgend=0;gi.invent=&node;gh.hname="nethack";astral_level.dnum=7;knox_level.dnum=6;wiz1_level.dlevel=7;for(i=0;i<16;i++)snprintf(svd.dungeons[i].dname,sizeof svd.dungeons[i].dname,"Dungeon%d",i);opts[0]=42;opts[2]=9;opts[10]=1;allocs=frees=open_count=close_count=windows=roll_count=roll_index=depth_of_callback=0;rngstate=seed;argument_count=0;corpsenm_value=-1;last_entry=retained_entry=0;inputbuf[0]=names[0]=reasons[0]=origin[0]=tracebuf[0]=0;sourcefile=tmpfile();targetfile=tmpfile();if(!sourcefile||!targetfile)abort();}
void probe_load(void){rewind(sourcefile);fwrite(inputbuf,1,strlen(inputbuf),sourcefile);fflush(sourcefile);rewind(sourcefile);}
char*probe_input(void){return inputbuf;}char*probe_file(int id){return filebuf[id];}char*probe_text(int id){return id==0?names:id==1?reasons:scratch;}char*probe_argument(int id){arguments[id]=argument_text[id];return argument_text[id];}void probe_argc(int n){argument_count=n;}
void probe_option(int k,long v){switch(k){case 100:u.urexp=v;break;case 101:svk.killer.format=v;break;case 102:strcpy(svk.killer.name,names);break;case 103:gm.multi=v;break;case 104:gm.multi_reason=v?reasons:0;break;case 105:program_state.panicking=v;break;case 106:program_state.stopprint=v;break;case 107:program_state.done_hup=v;break;case 108:iflags.toptenwin=v;break;case 109:flags.debug=v;break;case 110:flags.explore=v;break;case 111:sysopt.persmax=v;break;case 112:sysopt.pointsmin=v;break;case 113:sysopt.entrymax=v;break;case 114:sysopt.pers_is_uid=v;break;case 115:flags.end_top=v;break;case 116:flags.end_around=v;break;case 117:flags.end_own=v;break;case 118:flags.female=v;break;case 119:flags.initgend=v;break;case 120:u.ualign.type=v;break;case 121:u.ualignbase[A_ORIGINAL]=v;break;case 122:ubirthday=v;break;case 123:urealtime.finish_time=v;break;case 124:urealtime.realtime=v;break;case 125:svm.moves=v;break;case 126:sysopt.tt_oname_maxrank=v;break;case 127:flags.bones=v;break;case 128:wiz1_level.dlevel=v;break;case 129:strcpy(svp.plname,names);break;default:opts[k]=v;break;}}
void probe_conduct(int k,long v){long*fields[]={&u.uconduct.food,&u.uconduct.unvegan,&u.uconduct.unvegetarian,&u.uconduct.gnostic,&u.uconduct.weaphit,&u.uconduct.killer,&u.uconduct.literate,&u.uconduct.polypiles,&u.uconduct.polyselfs,&u.uconduct.wishes,&u.uconduct.wisharti,&u.uconduct.sokocheat,&u.uconduct.pets,&u.uroleplay.numbones,&u.uroleplay.numrerolls};if(k<15)*fields[k]=v;else switch(k){case 15:u.uroleplay.reroll=v;break;case 16:u.uroleplay.blind=v;break;case 17:u.uroleplay.deaf=v;break;case 18:u.uroleplay.nudist=v;break;case 19:u.uroleplay.pauper=v;break;}}
void probe_achievement(int i,int v){u.uachieved[i]=v;}
void probe_entry(int id,int k,long v){entry_t*e=&entries[id];switch(k){case 0:e->points=v;break;case 1:e->deathdnum=v;break;case 2:e->deathlev=v;break;case 3:e->maxlvl=v;break;case 4:e->hp=v;break;case 5:e->maxhp=v;break;case 6:e->deaths=v;break;case 7:e->ver_major=v;break;case 8:e->ver_minor=v;break;case 9:e->patchlevel=v;break;case 10:e->birthdate=v;break;case 11:e->deathdate=v;break;case 12:e->uid=v;break;}}
char*probe_entry_text(int id,int k){entry_t*e=&entries[id];switch(k){case 0:return e->plrole;case 1:return e->plrace;case 2:return e->plgend;case 3:return e->plalign;case 4:return e->name;default:return e->death;}}
int*probe_rolls(void){return rolls;}void probe_roll_count(int n){roll_count=n;roll_index=0;}
long probe_action(int op,int a,int b,int c){entry_t*t,*p;switch(op){case 0:formatkiller(scratch,a,b,c);return 0;case 1:topten_print(names);return 0;case 2:topten_print_bold(names);return 0;case 3:return observable_depth(&u.uz);case 4:discardexcess(sourcefile);return 0;case 5:readentry(sourcefile,&entries[a]);return 0;case 6:writeentry(targetfile,&entries[a]);return 0;case 7:writexlentry(targetfile,&entries[a],b);return 0;case 8:return encodexlogflags();case 9:return encodeconduct();case 10:return encodeachieve(a);case 11:add_achieveX(scratch,names,a);return 0;case 12:encode_extended_achievements(scratch);return 0;case 13:encode_extended_conducts(scratch);return 0;case 14:p=t=(entry_t*)alloc(sizeof *t);for(int i=0;i<a;i++){*p=entries[0];p->tt_next=(entry_t*)alloc(sizeof *p);p=p->tt_next;}memset(p,0,sizeof *p);free_ttlist(t);return 0;case 15:topten(a,(time_t)b);return 0;case 16:outheader();return 0;case 17:outentry(a,&entries[b],c);return 0;case 18:return score_wanted(a,b,&entries[0],argument_count,(const char**)arguments,opts[0]);case 19:prscore(argument_count,arguments);return 0;case 20:return classmon(names);case 21:last_entry=(entry_t*)get_rnd_toptenentry();if(!retained_entry)retained_entry=last_entry;return!!last_entry;case 22:return tt_oname(a?&node:0)==&node;case 23:return tt_doppel(&monster);default:return-99;}}
const char*probe_trace(void){return tracebuf;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
static char*entry_snapshot(char*p,entry_t*e){p+=sprintf(p,"entry:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d:%ld:%ld:%d:",e->points,e->deathdnum,e->deathlev,e->maxlvl,e->hp,e->maxhp,e->deaths,e->ver_major,e->ver_minor,e->patchlevel,e->deathdate,e->birthdate,e->uid);const unsigned char*q=(void*)e;for(size_t i=sizeof e->tt_next;i<sizeof *e;i++)p+=sprintf(p,"%02x",q[i]);return p;}
const char*probe_snapshot(void){char*p=snapbuf;long pos=ftell(targetfile);fflush(targetfile);rewind(targetfile);size_t n=fread(target_snapshot,1,65535,targetfile);target_snapshot[n]=0;fseek(targetfile,pos,SEEK_SET);p+=sprintf(p,"memory:%d:%d:%d:%d;window:%d;input:%ld:%d:%d;target:%s;files:%s|%s|%s;output:%s;object:%d:%d:%s;monster:%u:%s;rng:%u:%d;",allocs,frees,open_count,close_count,gt.toptenwin,ftell(sourcefile),feof(sourcefile),ferror(sourcefile),target_snapshot,filebuf[0],filebuf[1],filebuf[2],scratch,node.spe,corpsenm_value,objname,monster.female,monname,rngstate,roll_index);for(int i=0;i<4;i++)p=entry_snapshot(p,&entries[i]);if(last_entry)p=entry_snapshot(p,last_entry);if(retained_entry)p=entry_snapshot(p,retained_entry);p+=sprintf(p,"argv:%d:",argument_count);for(int i=0;i<argument_count;i++)p+=sprintf(p,"%td:%s;",arguments[i]-argument_text[i],arguments[i]);p+=sprintf(p,"state:%ld:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;",u.urexp,program_state.stopprint,program_state.panicking,program_state.done_hup,iflags.toptenwin,flags.debug,flags.explore,sysopt.persmax,sysopt.entrymax,sysopt.pointsmin,wiz1_level.dlevel);return snapbuf;}

void probe_time_action(int how,time_t when){topten(how,when);}
