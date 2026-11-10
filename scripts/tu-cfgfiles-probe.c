/* CFGFILES controlled dependency fixture. Original libc/stdio/heap/varargs; no config parser fallback. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <emscripten.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(flags) flags;
__typeof__(windowprocs) windowprocs;
__typeof__(gc) gc;
__typeof__(iflags) iflags;
__typeof__(svp) svp;
__typeof__(gd) gd;
__typeof__(sysopt) sysopt;
__typeof__(go) go;
__typeof__(gw) gw;
__typeof__(program_state) program_state;
__typeof__(gn) gn;
static char tracebuf[131072],statebuf[131072],input[8192],scratch[8192];static size_t traceused;static int result=1,rngvalue=0,query=1,callbacks=0,reentrant=0,grow=0,optioncalls=0,longoutput=0;static unsigned int seed=1;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);traceused+=vsnprintf(tracebuf+traceused,sizeof tracebuf-traceused,fmt,ap);va_end(ap);}
static void wait_fixture(void){append("wait;");}
static void*allocs[1024];static unsigned alloc_sizes[1024],alloc_count;static int alloc_live[1024];void __real_free(void*);void __wrap_free(void*p){for(unsigned i=alloc_count;i>0;i--)if(allocs[i-1]==p&&alloc_live[i-1]){append("free:%u:%u;",i-1,alloc_sizes[i-1]);alloc_live[i-1]=0;break;}__real_free(p);}
static long*fixture_alloc(unsigned n){void*p=malloc(n);if(!p)abort();if(alloc_count>=1024)abort();allocs[alloc_count]=p;alloc_sizes[alloc_count]=n;alloc_live[alloc_count]=1;append("alloc:%u:%u;",alloc_count,n);alloc_count++;memset(p,0xa5,n);return p;}
boolean (paranoid_query)(boolean a0,const char * a1){append("query:%d:%s;",a0,a1);return query;}
void (strbuf_init)(strbuf_t * a0){memset(a0,0,sizeof *a0);}
void (all_options_strbuf)(strbuf_t * a0){a0->str=(char*)fixture_alloc(longoutput?8193:64);if(longoutput){memset(a0->str,88,8192);a0->str[8192]=0;}else strcpy(a0->str,"OPTIONS=fixture\nNAME=fixture\n");}
void (strbuf_empty)(strbuf_t * a0){if(a0->str)free(a0->str);a0->str=0;}
const char * (fqname)(const char * a0,int a1,int a2){append("fqname:%s:%d:%d;",a0,a1,a2);return a0;}
char * (nh_getenv)(const char * a0){append("getenv:%s;",a0);return getenv(a0);}
boolean (rng_log_enabled)(void){return 1;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("rng:%s:%d:%s;",strrchr(a0,'/')?strrchr(a0,'/')+1:a0,a1,a2);}
int (rn2)(int a0){if(a0<=0)abort();seed=seed*1664525u+1013904223u;int v=rngvalue>=0?rngvalue%a0:(int)(seed%(unsigned)a0);append("rn2:%d:%d;",a0,v);return v;}
char * (trimspaces)(char * a0){char*p=a0;while(*p==' '||*p=='\t')p++;char*e=p+strlen(p);while(e>p&&(e[-1]==' '||e[-1]=='\t'))*--e=0;return p;}
char * (dupstr)(const char * a0){char*p=(char*)fixture_alloc((unsigned)strlen(a0)+1);strcpy(p,a0);return p;}
boolean (debugcore)(const char * a0,boolean a1){append("debug:%s:%d;",a0,a1);return 0;}
boolean (parseoptions)(char * a0,boolean a1,boolean a2){append("options:%s:%d:%d;",a0,a1,a2);optioncalls++;if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentrant){reentrant=0;config_error_init(0,"nested",0);config_erradd("nested error");config_error_done();}return result;}
int (add_autopickup_exception)(const char * a0){append("autopick:%s;",a0);return result;}
boolean (parsebindings)(char * a0){append("bindings:%s;",a0);return result;}
void (parseautocomplete)(char * a0,boolean a1){append("autocomplete:%s:%d;",a0,a1);}
boolean (msgtype_parse_add)(char * a0){append("msgtype:%s;",a0);return result;}
int (str2role)(const char * a0){append("role:%s;",a0);return result;}
char * (build_english_list)(char * a0){append("english:%s;",a0);char*p=(char*)fixture_alloc((unsigned)strlen(a0)+1);strcpy(p,a0);return p;}
void (sysopt_seduce_set)(int a0){append("seduce:%d;",a0);}
boolean (file_exists)(const char * a0){append("exists:%s;",a0);return result;}
boolean (add_menu_coloring)(char * a0){append("menucolor:%s;",a0);return result;}
boolean (parse_status_hl1)(char * a0,boolean a1){append("status:%s:%d;",a0,a1);return result;}
void (assign_warnings)(uchar * a0){append("warnings:");for(int i=0;i<WARNCOUNT;i++)append("%u,",a0[i]);append(";");}
boolean (parsesymbols)(char * a0,int a1){append("symbols:%s:%d;",a0,a1);return result;}
void (switch_symbols)(int a0){append("switch:%d;",a0);}
char * (mungspaces)(char * a0){char*s=a0,*d=a0;int space=0;while(*s==' '||*s=='\t')s++;while(*s){if(*s==' '||*s=='\t'){space=1;}else{if(space&&d>a0)*d++=' ';*d++=*s;space=0;}s++;}*d=0;return a0;}
boolean (match_optname)(const char * a0,const char * a1,int a2,boolean a3){int n=0;while(a0[n]&&a0[n]!='='&&a0[n]!=':'&&a0[n]!=' ')n++;return n>=a2&&n<=(int)strlen(a1)&&!strncasecmp(a0,a1,(size_t)n);}
long * (alloc)(unsigned int a0){return fixture_alloc(a0);}
void (lua_createtable)(lua_State * a0,int a1,int a2){append("lua_table:%d:%d;",a1,a2);if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentrant){reentrant=0;config_error_init(0,"Lua nested",0);config_erradd("new Lua message");config_error_done();}}
void (lua_pushinteger)(lua_State * a0,lua_Integer a1){append("lua_integer:%lld;",(long long)a1);}
void (nhl_add_table_entry_int)(lua_State * a0,const char * a1,lua_Integer a2){append("lua_int:%s:%lld;",a1,(long long)a2);}
void (nhl_add_table_entry_str)(lua_State * a0,const char * a1,const char * a2){append("lua_str:%s:%s;",a1,a2);}
void (lua_settable)(lua_State * a0,int a1){append("lua_set:%d;",a1);}
const char * (c_eos)(const char * a0){return a0+strlen(a0);}
void (reset_duplicate_opt_detection)(void){append("duplicate_reset;");}
char * (eos)(char * a0){return a0+strlen(a0);}
void (allopt_array_init)(void){append("allopt_init;");}
void (disregard_all_options)(void){append("disregard_all;");}
void (heed_this_option)(enum opt a0){append("heed:%d;",a0);}
void (heed_all_options)(void){append("heed_all;");}
void (disregard_this_option)(enum opt a0){append("disregard:%d;",a0);}
void (do_deferred_showpaths)(int a0){append("showpaths:%d;",a0);abort();}
void pline(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);}
void raw_printf(const char*fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("raw:%s;",b);}
void nh_snprintf(const char*fn,int line,char*out,size_t len,const char*fmt,...){append("snprintf:%s:%d;",fn,line);va_list ap;va_start(ap,fmt);int n=vsnprintf(out,len,fmt,ap);va_end(ap);(void)n;}
#ifdef HYBRID_CFGFILES
#include "../nethack-c/wasm/tu-fragments/cfgfiles-types.h"
extern FILE * teleport_cfgfiles_fopen_config_file(const char * filename,int src);
#define fopen_config_file teleport_cfgfiles_fopen_config_file
extern int teleport_cfgfiles_get_uchars(char * bufp,uchar * list,boolean modlist,int size,const char * name);
#define get_uchars teleport_cfgfiles_get_uchars
extern char * teleport_cfgfiles_choose_random_part(char * str,char sep);
#define choose_random_part teleport_cfgfiles_choose_random_part
extern void teleport_cfgfiles_free_config_sections(void);
#define free_config_sections teleport_cfgfiles_free_config_sections
extern char * teleport_cfgfiles_is_config_section(char * str);
#define is_config_section teleport_cfgfiles_is_config_section
extern boolean teleport_cfgfiles_handle_config_section(char * buf);
#define handle_config_section teleport_cfgfiles_handle_config_section
extern char * teleport_cfgfiles_find_optparam(char * buf);
#define find_optparam teleport_cfgfiles_find_optparam
extern boolean teleport_cfgfiles_cnf_line_OPTIONS(char * origbuf);
#define cnf_line_OPTIONS teleport_cfgfiles_cnf_line_OPTIONS
extern boolean teleport_cfgfiles_cnf_line_AUTOPICKUP_EXCEPTION(char * bufp);
#define cnf_line_AUTOPICKUP_EXCEPTION teleport_cfgfiles_cnf_line_AUTOPICKUP_EXCEPTION
extern boolean teleport_cfgfiles_cnf_line_BINDINGS(char * bufp);
#define cnf_line_BINDINGS teleport_cfgfiles_cnf_line_BINDINGS
extern boolean teleport_cfgfiles_cnf_line_AUTOCOMPLETE(char * bufp);
#define cnf_line_AUTOCOMPLETE teleport_cfgfiles_cnf_line_AUTOCOMPLETE
extern boolean teleport_cfgfiles_cnf_line_MSGTYPE(char * bufp);
#define cnf_line_MSGTYPE teleport_cfgfiles_cnf_line_MSGTYPE
extern boolean teleport_cfgfiles_cnf_line_HACKDIR(char * bufp);
#define cnf_line_HACKDIR teleport_cfgfiles_cnf_line_HACKDIR
extern boolean teleport_cfgfiles_cnf_line_LEVELDIR(char * bufp);
#define cnf_line_LEVELDIR teleport_cfgfiles_cnf_line_LEVELDIR
extern boolean teleport_cfgfiles_cnf_line_SAVEDIR(char * bufp);
#define cnf_line_SAVEDIR teleport_cfgfiles_cnf_line_SAVEDIR
extern boolean teleport_cfgfiles_cnf_line_BONESDIR(char * bufp);
#define cnf_line_BONESDIR teleport_cfgfiles_cnf_line_BONESDIR
extern boolean teleport_cfgfiles_cnf_line_DATADIR(char * bufp);
#define cnf_line_DATADIR teleport_cfgfiles_cnf_line_DATADIR
extern boolean teleport_cfgfiles_cnf_line_SCOREDIR(char * bufp);
#define cnf_line_SCOREDIR teleport_cfgfiles_cnf_line_SCOREDIR
extern boolean teleport_cfgfiles_cnf_line_LOCKDIR(char * bufp);
#define cnf_line_LOCKDIR teleport_cfgfiles_cnf_line_LOCKDIR
extern boolean teleport_cfgfiles_cnf_line_CONFIGDIR(char * bufp);
#define cnf_line_CONFIGDIR teleport_cfgfiles_cnf_line_CONFIGDIR
extern boolean teleport_cfgfiles_cnf_line_TROUBLEDIR(char * bufp);
#define cnf_line_TROUBLEDIR teleport_cfgfiles_cnf_line_TROUBLEDIR
extern boolean teleport_cfgfiles_cnf_line_NAME(char * bufp);
#define cnf_line_NAME teleport_cfgfiles_cnf_line_NAME
extern boolean teleport_cfgfiles_cnf_line_ROLE(char * bufp);
#define cnf_line_ROLE teleport_cfgfiles_cnf_line_ROLE
extern boolean teleport_cfgfiles_cnf_line_dogname(char * bufp);
#define cnf_line_dogname teleport_cfgfiles_cnf_line_dogname
extern boolean teleport_cfgfiles_cnf_line_catname(char * bufp);
#define cnf_line_catname teleport_cfgfiles_cnf_line_catname
extern boolean teleport_cfgfiles_cnf_line_WIZARDS(char * bufp);
#define cnf_line_WIZARDS teleport_cfgfiles_cnf_line_WIZARDS
extern boolean teleport_cfgfiles_cnf_line_SHELLERS(char * bufp);
#define cnf_line_SHELLERS teleport_cfgfiles_cnf_line_SHELLERS
extern boolean teleport_cfgfiles_cnf_line_MSGHANDLER(char * bufp);
#define cnf_line_MSGHANDLER teleport_cfgfiles_cnf_line_MSGHANDLER
extern boolean teleport_cfgfiles_cnf_line_EXPLORERS(char * bufp);
#define cnf_line_EXPLORERS teleport_cfgfiles_cnf_line_EXPLORERS
extern boolean teleport_cfgfiles_cnf_line_DEBUGFILES(char * bufp);
#define cnf_line_DEBUGFILES teleport_cfgfiles_cnf_line_DEBUGFILES
extern boolean teleport_cfgfiles_cnf_line_DUMPLOGFILE(char * bufp);
#define cnf_line_DUMPLOGFILE teleport_cfgfiles_cnf_line_DUMPLOGFILE
extern boolean teleport_cfgfiles_cnf_line_GENERICUSERS(char * bufp);
#define cnf_line_GENERICUSERS teleport_cfgfiles_cnf_line_GENERICUSERS
extern boolean teleport_cfgfiles_cnf_line_BONES_POOLS(char * bufp);
#define cnf_line_BONES_POOLS teleport_cfgfiles_cnf_line_BONES_POOLS
extern boolean teleport_cfgfiles_cnf_line_SUPPORT(char * bufp);
#define cnf_line_SUPPORT teleport_cfgfiles_cnf_line_SUPPORT
extern boolean teleport_cfgfiles_cnf_line_RECOVER(char * bufp);
#define cnf_line_RECOVER teleport_cfgfiles_cnf_line_RECOVER
extern boolean teleport_cfgfiles_cnf_line_CHECK_SAVE_UID(char * bufp);
#define cnf_line_CHECK_SAVE_UID teleport_cfgfiles_cnf_line_CHECK_SAVE_UID
extern boolean teleport_cfgfiles_cnf_line_CHECK_PLNAME(char * bufp);
#define cnf_line_CHECK_PLNAME teleport_cfgfiles_cnf_line_CHECK_PLNAME
extern boolean teleport_cfgfiles_cnf_line_SEDUCE(char * bufp);
#define cnf_line_SEDUCE teleport_cfgfiles_cnf_line_SEDUCE
extern boolean teleport_cfgfiles_cnf_line_HIDEUSAGE(char * bufp);
#define cnf_line_HIDEUSAGE teleport_cfgfiles_cnf_line_HIDEUSAGE
extern boolean teleport_cfgfiles_cnf_line_MAXPLAYERS(char * bufp);
#define cnf_line_MAXPLAYERS teleport_cfgfiles_cnf_line_MAXPLAYERS
extern boolean teleport_cfgfiles_cnf_line_PERSMAX(char * bufp);
#define cnf_line_PERSMAX teleport_cfgfiles_cnf_line_PERSMAX
extern boolean teleport_cfgfiles_cnf_line_PERS_IS_UID(char * bufp);
#define cnf_line_PERS_IS_UID teleport_cfgfiles_cnf_line_PERS_IS_UID
extern boolean teleport_cfgfiles_cnf_line_ENTRYMAX(char * bufp);
#define cnf_line_ENTRYMAX teleport_cfgfiles_cnf_line_ENTRYMAX
extern boolean teleport_cfgfiles_cnf_line_POINTSMIN(char * bufp);
#define cnf_line_POINTSMIN teleport_cfgfiles_cnf_line_POINTSMIN
extern boolean teleport_cfgfiles_cnf_line_MAX_STATUENAME_RANK(char * bufp);
#define cnf_line_MAX_STATUENAME_RANK teleport_cfgfiles_cnf_line_MAX_STATUENAME_RANK
extern boolean teleport_cfgfiles_cnf_line_LIVELOG(char * bufp);
#define cnf_line_LIVELOG teleport_cfgfiles_cnf_line_LIVELOG
extern boolean teleport_cfgfiles_cnf_line_PANICTRACE_LIBC(char * bufp);
#define cnf_line_PANICTRACE_LIBC teleport_cfgfiles_cnf_line_PANICTRACE_LIBC
extern boolean teleport_cfgfiles_cnf_line_PANICTRACE_GDB(char * bufp);
#define cnf_line_PANICTRACE_GDB teleport_cfgfiles_cnf_line_PANICTRACE_GDB
extern boolean teleport_cfgfiles_cnf_line_GDBPATH(char * bufp);
#define cnf_line_GDBPATH teleport_cfgfiles_cnf_line_GDBPATH
extern boolean teleport_cfgfiles_cnf_line_GREPPATH(char * bufp);
#define cnf_line_GREPPATH teleport_cfgfiles_cnf_line_GREPPATH
extern boolean teleport_cfgfiles_cnf_line_CRASHREPORTURL(char * bufp);
#define cnf_line_CRASHREPORTURL teleport_cfgfiles_cnf_line_CRASHREPORTURL
extern boolean teleport_cfgfiles_cnf_line_ACCESSIBILITY(char * bufp);
#define cnf_line_ACCESSIBILITY teleport_cfgfiles_cnf_line_ACCESSIBILITY
extern boolean teleport_cfgfiles_cnf_line_PORTABLE_DEVICE_PATHS(char * bufp);
#define cnf_line_PORTABLE_DEVICE_PATHS teleport_cfgfiles_cnf_line_PORTABLE_DEVICE_PATHS
extern boolean teleport_cfgfiles_cnf_line_BOULDER(char * bufp);
#define cnf_line_BOULDER teleport_cfgfiles_cnf_line_BOULDER
extern boolean teleport_cfgfiles_cnf_line_MENUCOLOR(char * bufp);
#define cnf_line_MENUCOLOR teleport_cfgfiles_cnf_line_MENUCOLOR
extern boolean teleport_cfgfiles_cnf_line_HILITE_STATUS(char * bufp);
#define cnf_line_HILITE_STATUS teleport_cfgfiles_cnf_line_HILITE_STATUS
extern boolean teleport_cfgfiles_cnf_line_WARNINGS(char * bufp);
#define cnf_line_WARNINGS teleport_cfgfiles_cnf_line_WARNINGS
extern boolean teleport_cfgfiles_cnf_line_ROGUESYMBOLS(char * bufp);
#define cnf_line_ROGUESYMBOLS teleport_cfgfiles_cnf_line_ROGUESYMBOLS
extern boolean teleport_cfgfiles_cnf_line_SYMBOLS(char * bufp);
#define cnf_line_SYMBOLS teleport_cfgfiles_cnf_line_SYMBOLS
extern boolean teleport_cfgfiles_cnf_line_WIZKIT(char * bufp);
#define cnf_line_WIZKIT teleport_cfgfiles_cnf_line_WIZKIT
extern boolean teleport_cfgfiles_cnf_line_QT_TILEWIDTH(char * bufp);
#define cnf_line_QT_TILEWIDTH teleport_cfgfiles_cnf_line_QT_TILEWIDTH
extern boolean teleport_cfgfiles_cnf_line_QT_TILEHEIGHT(char * bufp);
#define cnf_line_QT_TILEHEIGHT teleport_cfgfiles_cnf_line_QT_TILEHEIGHT
extern boolean teleport_cfgfiles_cnf_line_QT_FONTSIZE(char * bufp);
#define cnf_line_QT_FONTSIZE teleport_cfgfiles_cnf_line_QT_FONTSIZE
extern boolean teleport_cfgfiles_cnf_line_QT_COMPACT(char * bufp);
#define cnf_line_QT_COMPACT teleport_cfgfiles_cnf_line_QT_COMPACT
extern boolean teleport_cfgfiles_config_error_nextline(const char * line);
#define config_error_nextline teleport_cfgfiles_config_error_nextline
extern void teleport_cfgfiles_cnf_parser_init(struct _cnf_parser_state * parser);
#define cnf_parser_init teleport_cfgfiles_cnf_parser_init
extern void teleport_cfgfiles_cnf_parser_done(struct _cnf_parser_state * parser);
#define cnf_parser_done teleport_cfgfiles_cnf_parser_done
extern void teleport_cfgfiles_parse_conf_buf(struct _cnf_parser_state * p,boolean (*proc)(char *));
#define parse_conf_buf teleport_cfgfiles_parse_conf_buf
extern void teleport_cfgfiles_vconfig_error_add(const char * str,va_list the_args);
#define vconfig_error_add teleport_cfgfiles_vconfig_error_add
EM_JS(uint64_t,cfgfiles_private,(int index),{return BigInt(Module["nethackPorted"].cfgfilesPrivate(Module,index));});
#else
#include "../.cache/wasm64-build/tree/src/cfgfiles.c"
#define TELEPORT_CFGFILES_TYPES_H
#endif
#include "tu-cfgfiles-layout.h"
uint64_t probe_private(int index){
#ifdef HYBRID_CFGFILES
return cfgfiles_private(index);
#else
if(index>=100&&index<159)return disregarded_config_lines[index-100];switch(index){case 0:return ignore_errors_on_unmatched;case 1:return ignore_statement_errors;case 2:return(uintptr_t)configfile;case 3:return(uintptr_t)default_configfile;case 4:return(uintptr_t)config_error_data;case 5:return(uintptr_t)config_error_msg;default:abort();}
#endif
}
static void cfg_fixture_vformat(const char*fmt,...){va_list ap;va_start(ap,fmt);vconfig_error_add(fmt,ap);va_end(ap);}
void probe_vformat(const char*fmt,const char*s,int n,int64_t l,uint64_t z,unsigned u){cfg_fixture_vformat(fmt,s,n,(long)l,(size_t)z,u);}
FILE*probe_open(const char*name){return fopen(name,"r");}
void probe_close(FILE*fp){fclose(fp);}
int probe_layout_count(void){return sizeof cfgfiles_layout/sizeof cfgfiles_layout[0];}
const char*probe_layout_name(int i){return cfgfiles_layout[i].name;}
int64_t probe_layout_value(int i){return(int64_t)cfgfiles_layout[i].value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}
void probe_clear_trace(void){traceused=0;tracebuf[0]=0;}
char*probe_input(const char*s){if(s){strncpy(input,s,sizeof input-1);input[sizeof input-1]=0;}return input;}
char*probe_scratch(void){return scratch;}
const char*probe_contents(const char*path){FILE*fp=fopen(path,"r");if(!fp)return 0;size_t n=fread(scratch,1,sizeof scratch-1,fp);scratch[n]=0;fclose(fp);return scratch;}
int probe_file(const char*path,const char*data){FILE*fp=fopen(path,"w");if(!fp)return -1;int n=(int)fwrite(data,1,strlen(data),fp);fclose(fp);return n;}
void probe_option(int key,int value){switch(key){case 0:result=value;break;case 1:rngvalue=value;break;case 2:query=value;break;case 3:grow=value;break;case 4:reentrant=value;break;case 5:iflags.parse_config_file_src=value;break;case 6:iflags.in_lua=value;break;case 7:gn.no_sound_notified=value;break;case 8:flags.suppress_alert=value;break;case 9:longoutput=value;break;default:abort();}}
const char*probe_snapshot(void){char*out=statebuf;out+=sprintf(out,"flags:%llu:%d;state:%d:%d:%d:%d;name:%s;dog:%s;cat:%s;wiz:%s;phase:%d;",(unsigned long long)flags.suppress_alert,flags.initrole,program_state.config_error_ready,iflags.parse_config_file_src,iflags.in_lua,gn.no_sound_notified,svp.plname,gd.dogname,gc.catname,gw.wizkit,go.opt_phase);
out+=sprintf(out,"sections:%s:%s;",gc.config_section_chosen?gc.config_section_chosen:"NULL",gc.config_section_current?gc.config_section_current:"NULL");
out+=sprintf(out,"support:%s;",sysopt.support?sysopt.support:"NULL");
out+=sprintf(out,"recover:%s;",sysopt.recover?sysopt.recover:"NULL");
out+=sprintf(out,"wizards:%s;",sysopt.wizards?sysopt.wizards:"NULL");
out+=sprintf(out,"fmtd_wizard_list:%s;",sysopt.fmtd_wizard_list?sysopt.fmtd_wizard_list:"NULL");
out+=sprintf(out,"explorers:%s;",sysopt.explorers?sysopt.explorers:"NULL");
out+=sprintf(out,"shellers:%s;",sysopt.shellers?sysopt.shellers:"NULL");
out+=sprintf(out,"genericusers:%s;",sysopt.genericusers?sysopt.genericusers:"NULL");
out+=sprintf(out,"debugfiles:%s;",sysopt.debugfiles?sysopt.debugfiles:"NULL");
out+=sprintf(out,"msghandler:%s;",sysopt.msghandler?sysopt.msghandler:"NULL");
out+=sprintf(out,"env_dbgfl:%lld;",(long long)sysopt.env_dbgfl);
out+=sprintf(out,"maxplayers:%lld;",(long long)sysopt.maxplayers);
out+=sprintf(out,"seduce:%lld;",(long long)sysopt.seduce);
out+=sprintf(out,"check_save_uid:%lld;",(long long)sysopt.check_save_uid);
out+=sprintf(out,"check_plname:%lld;",(long long)sysopt.check_plname);
out+=sprintf(out,"bones_pools:%lld;",(long long)sysopt.bones_pools);
out+=sprintf(out,"livelog:%lld;",(long long)sysopt.livelog);
out+=sprintf(out,"persmax:%lld;",(long long)sysopt.persmax);
out+=sprintf(out,"pers_is_uid:%lld;",(long long)sysopt.pers_is_uid);
out+=sprintf(out,"entrymax:%lld;",(long long)sysopt.entrymax);
out+=sprintf(out,"pointsmin:%lld;",(long long)sysopt.pointsmin);
out+=sprintf(out,"tt_oname_maxrank:%lld;",(long long)sysopt.tt_oname_maxrank);
out+=sprintf(out,"gdbpath:%s;",sysopt.gdbpath?sysopt.gdbpath:"NULL");
out+=sprintf(out,"greppath:%s;",sysopt.greppath?sysopt.greppath:"NULL");
out+=sprintf(out,"crashreporturl:%s;",sysopt.crashreporturl?sysopt.crashreporturl:"NULL");
out+=sprintf(out,"panictrace_gdb:%lld;",(long long)sysopt.panictrace_gdb);
out+=sprintf(out,"panictrace_libc:%lld;",(long long)sysopt.panictrace_libc);
out+=sprintf(out,"accessibility:%lld;",(long long)sysopt.accessibility);
out+=sprintf(out,"hideusage:%lld;",(long long)sysopt.hideusage);
out+=sprintf(out,"private:%llu:%llu;config:%s;default:%s;",(unsigned long long)probe_private(0),(unsigned long long)probe_private(1),(char*)(uintptr_t)probe_private(2),(char*)(uintptr_t)probe_private(3));for(int i=0;i<59;i++)out+=sprintf(out,"%llu,",(unsigned long long)probe_private(100+i));
struct _config_error_frame*f=(void*)(uintptr_t)probe_private(4);for(;f;f=f->next)out+=sprintf(out,"frame:%d:%d:%d:%d:%d:%s:%s;",f->line_num,f->num_errors,f->origline_shown,f->fromfile,f->secure,f->origline,f->source);
struct _config_error_errmsg*m=(void*)(uintptr_t)probe_private(5);for(;m;m=m->next)out+=sprintf(out,"error:%d:%s;",m->line_num,m->errormsg);
out+=sprintf(out,"counts:%d:%d;",callbacks,optioncalls);*out=0;return statebuf;}
static boolean fixture_callback(char*buf){callbacks++;append("callback:%s;",buf);if(grow){grow=0;emscripten_resize_heap(emscripten_get_heap_size()+65536);}if(reentrant){reentrant=0;parse_conf_str("INNER=ok\n",parse_config_line);}return result;}
uintptr_t probe_callback(void){return(uintptr_t)fixture_callback;}
uint64_t probe_action(int op,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){switch(op){
case 0:return(uint64_t)(uintptr_t)get_configfile();
case 1:return(uint64_t)(uintptr_t)get_default_configfile();
case 2:return(uint64_t)(uintptr_t)do_write_config_file();
case 3:set_configfile_name((const char *)(uintptr_t)a);return 0;
case 4:return(uint64_t)(uintptr_t)fopen_config_file((const char *)(uintptr_t)a,(int)(uintptr_t)b);
case 5:return(uint64_t)(uintptr_t)get_uchars((char *)(uintptr_t)a,(uchar *)(uintptr_t)b,(boolean)(uintptr_t)c,(int)(uintptr_t)d,(const char *)(uintptr_t)e);
case 6:return(uint64_t)(uintptr_t)choose_random_part((char *)(uintptr_t)a,(char)(uintptr_t)b);
case 7:free_config_sections();return 0;
case 8:return(uint64_t)(uintptr_t)is_config_section((char *)(uintptr_t)a);
case 9:return(uint64_t)(uintptr_t)handle_config_section((char *)(uintptr_t)a);
case 10:return(uint64_t)(uintptr_t)find_optparam((char *)(uintptr_t)a);
case 11:return(uint64_t)(uintptr_t)cnf_line_OPTIONS((char *)(uintptr_t)a);
case 12:return(uint64_t)(uintptr_t)cnf_line_AUTOPICKUP_EXCEPTION((char *)(uintptr_t)a);
case 13:return(uint64_t)(uintptr_t)cnf_line_BINDINGS((char *)(uintptr_t)a);
case 14:return(uint64_t)(uintptr_t)cnf_line_AUTOCOMPLETE((char *)(uintptr_t)a);
case 15:return(uint64_t)(uintptr_t)cnf_line_MSGTYPE((char *)(uintptr_t)a);
case 16:return(uint64_t)(uintptr_t)cnf_line_HACKDIR((char *)(uintptr_t)a);
case 17:return(uint64_t)(uintptr_t)cnf_line_LEVELDIR((char *)(uintptr_t)a);
case 18:return(uint64_t)(uintptr_t)cnf_line_SAVEDIR((char *)(uintptr_t)a);
case 19:return(uint64_t)(uintptr_t)cnf_line_BONESDIR((char *)(uintptr_t)a);
case 20:return(uint64_t)(uintptr_t)cnf_line_DATADIR((char *)(uintptr_t)a);
case 21:return(uint64_t)(uintptr_t)cnf_line_SCOREDIR((char *)(uintptr_t)a);
case 22:return(uint64_t)(uintptr_t)cnf_line_LOCKDIR((char *)(uintptr_t)a);
case 23:return(uint64_t)(uintptr_t)cnf_line_CONFIGDIR((char *)(uintptr_t)a);
case 24:return(uint64_t)(uintptr_t)cnf_line_TROUBLEDIR((char *)(uintptr_t)a);
case 25:return(uint64_t)(uintptr_t)cnf_line_NAME((char *)(uintptr_t)a);
case 26:return(uint64_t)(uintptr_t)cnf_line_ROLE((char *)(uintptr_t)a);
case 27:return(uint64_t)(uintptr_t)cnf_line_dogname((char *)(uintptr_t)a);
case 28:return(uint64_t)(uintptr_t)cnf_line_catname((char *)(uintptr_t)a);
case 29:return(uint64_t)(uintptr_t)cnf_line_WIZARDS((char *)(uintptr_t)a);
case 30:return(uint64_t)(uintptr_t)cnf_line_SHELLERS((char *)(uintptr_t)a);
case 31:return(uint64_t)(uintptr_t)cnf_line_MSGHANDLER((char *)(uintptr_t)a);
case 32:return(uint64_t)(uintptr_t)cnf_line_EXPLORERS((char *)(uintptr_t)a);
case 33:return(uint64_t)(uintptr_t)cnf_line_DEBUGFILES((char *)(uintptr_t)a);
case 34:return(uint64_t)(uintptr_t)cnf_line_DUMPLOGFILE((char *)(uintptr_t)a);
case 35:return(uint64_t)(uintptr_t)cnf_line_GENERICUSERS((char *)(uintptr_t)a);
case 36:return(uint64_t)(uintptr_t)cnf_line_BONES_POOLS((char *)(uintptr_t)a);
case 37:return(uint64_t)(uintptr_t)cnf_line_SUPPORT((char *)(uintptr_t)a);
case 38:return(uint64_t)(uintptr_t)cnf_line_RECOVER((char *)(uintptr_t)a);
case 39:return(uint64_t)(uintptr_t)cnf_line_CHECK_SAVE_UID((char *)(uintptr_t)a);
case 40:return(uint64_t)(uintptr_t)cnf_line_CHECK_PLNAME((char *)(uintptr_t)a);
case 41:return(uint64_t)(uintptr_t)cnf_line_SEDUCE((char *)(uintptr_t)a);
case 42:return(uint64_t)(uintptr_t)cnf_line_HIDEUSAGE((char *)(uintptr_t)a);
case 43:return(uint64_t)(uintptr_t)cnf_line_MAXPLAYERS((char *)(uintptr_t)a);
case 44:return(uint64_t)(uintptr_t)cnf_line_PERSMAX((char *)(uintptr_t)a);
case 45:return(uint64_t)(uintptr_t)cnf_line_PERS_IS_UID((char *)(uintptr_t)a);
case 46:return(uint64_t)(uintptr_t)cnf_line_ENTRYMAX((char *)(uintptr_t)a);
case 47:return(uint64_t)(uintptr_t)cnf_line_POINTSMIN((char *)(uintptr_t)a);
case 48:return(uint64_t)(uintptr_t)cnf_line_MAX_STATUENAME_RANK((char *)(uintptr_t)a);
case 49:return(uint64_t)(uintptr_t)cnf_line_LIVELOG((char *)(uintptr_t)a);
case 50:return(uint64_t)(uintptr_t)cnf_line_PANICTRACE_LIBC((char *)(uintptr_t)a);
case 51:return(uint64_t)(uintptr_t)cnf_line_PANICTRACE_GDB((char *)(uintptr_t)a);
case 52:return(uint64_t)(uintptr_t)cnf_line_GDBPATH((char *)(uintptr_t)a);
case 53:return(uint64_t)(uintptr_t)cnf_line_GREPPATH((char *)(uintptr_t)a);
case 54:return(uint64_t)(uintptr_t)cnf_line_CRASHREPORTURL((char *)(uintptr_t)a);
case 55:return(uint64_t)(uintptr_t)cnf_line_ACCESSIBILITY((char *)(uintptr_t)a);
case 56:return(uint64_t)(uintptr_t)cnf_line_PORTABLE_DEVICE_PATHS((char *)(uintptr_t)a);
case 57:return(uint64_t)(uintptr_t)cnf_line_BOULDER((char *)(uintptr_t)a);
case 58:return(uint64_t)(uintptr_t)cnf_line_MENUCOLOR((char *)(uintptr_t)a);
case 59:return(uint64_t)(uintptr_t)cnf_line_HILITE_STATUS((char *)(uintptr_t)a);
case 60:return(uint64_t)(uintptr_t)cnf_line_WARNINGS((char *)(uintptr_t)a);
case 61:return(uint64_t)(uintptr_t)cnf_line_ROGUESYMBOLS((char *)(uintptr_t)a);
case 62:return(uint64_t)(uintptr_t)cnf_line_SYMBOLS((char *)(uintptr_t)a);
case 63:return(uint64_t)(uintptr_t)cnf_line_WIZKIT((char *)(uintptr_t)a);
case 64:return(uint64_t)(uintptr_t)cnf_line_QT_TILEWIDTH((char *)(uintptr_t)a);
case 65:return(uint64_t)(uintptr_t)cnf_line_QT_TILEHEIGHT((char *)(uintptr_t)a);
case 66:return(uint64_t)(uintptr_t)cnf_line_QT_FONTSIZE((char *)(uintptr_t)a);
case 67:return(uint64_t)(uintptr_t)cnf_line_QT_COMPACT((char *)(uintptr_t)a);
case 68:return(uint64_t)(uintptr_t)parse_config_line((char *)(uintptr_t)a);
case 69:config_error_init((boolean)(uintptr_t)a,(const char *)(uintptr_t)b,(boolean)(uintptr_t)c);return 0;
case 70:return(uint64_t)(uintptr_t)config_error_nextline((const char *)(uintptr_t)a);
case 71:return(uint64_t)(uintptr_t)l_get_config_errors((lua_State *)(uintptr_t)a);
case 72:config_erradd((const char *)(uintptr_t)a);return 0;
case 73:return(uint64_t)(uintptr_t)config_error_done();
case 74:return(uint64_t)(uintptr_t)read_config_file((const char *)(uintptr_t)a,(int)(uintptr_t)b);
case 75:cnf_parser_init((struct _cnf_parser_state *)(uintptr_t)a);return 0;
case 76:cnf_parser_done((struct _cnf_parser_state *)(uintptr_t)a);return 0;
case 77:parse_conf_buf((struct _cnf_parser_state *)(uintptr_t)a,(boolean (*)(char *))(uintptr_t)b);return 0;
case 78:return(uint64_t)(uintptr_t)parse_conf_str((const char *)(uintptr_t)a,(boolean (*)(char *))(uintptr_t)b);
case 79:return(uint64_t)(uintptr_t)parse_conf_file((FILE *)(uintptr_t)a,(boolean (*)(char *))(uintptr_t)b);
case 80:config_error_add((const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(int)c,(long)9007199254741001LL,(size_t)9007199254741003ULL,(unsigned)0xfedcba98);return 0;
case 81:vconfig_error_add((const char *)(uintptr_t)a,(va_list)(uintptr_t)b);return 0;
case 82:rcfile();return 0;
case 83:rcfile_interface_options();return 0;
case 84:heed_all_config_statements();return 0;
case 85:disregard_all_config_statements();return 0;
case 86:heed_this_config_statement((int)(uintptr_t)a);return 0;
case 87:disregard_this_config_statement((int)(uintptr_t)a);return 0;
case 88:clear_ignore_errors_on_unmatched();return 0;
case 89:set_ignore_errors_on_unmatched();return 0;
case 90:return(uint64_t)(uintptr_t)config_unmatched_ignored();
case 91:assure_syscf_file();return 0;
default:abort();}}
void probe_reset(void){traceused=0;tracebuf[0]=0;result=1;rngvalue=0;query=1;callbacks=0;reentrant=0;grow=0;optioncalls=0;longoutput=0;seed=1;memset(input,0,sizeof input);memset(scratch,0,sizeof scratch);
memset((void*)&flags,0,sizeof flags);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gc,0,sizeof gc);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&svp,0,sizeof svp);
memset((void*)&gd,0,sizeof gd);
memset((void*)&sysopt,0,sizeof sysopt);
memset((void*)&go,0,sizeof go);
memset((void*)&gw,0,sizeof gw);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&gn,0,sizeof gn);
windowprocs.win_wait_synch=wait_fixture;get_configfile()[0]=0;heed_all_config_statements();clear_ignore_errors_on_unmatched();flags.suppress_alert=~0UL;}
const char*probe_table_name(int row){
#ifdef HYBRID_CFGFILES
return 0;
#else
return config_line_stmt[row].name;
#endif
}
int probe_table_value(int row,int col){
#ifdef HYBRID_CFGFILES
return -1;
#else
switch(col){case 0:return config_line_stmt[row].len;case 1:return config_line_stmt[row].syscnf_only;case 2:return config_line_stmt[row].origbuf;case 3:
if(config_line_stmt[row].fn==cnf_line_OPTIONS)return 11;
if(config_line_stmt[row].fn==cnf_line_AUTOPICKUP_EXCEPTION)return 12;
if(config_line_stmt[row].fn==cnf_line_BINDINGS)return 13;
if(config_line_stmt[row].fn==cnf_line_AUTOCOMPLETE)return 14;
if(config_line_stmt[row].fn==cnf_line_MSGTYPE)return 15;
if(config_line_stmt[row].fn==cnf_line_HACKDIR)return 16;
if(config_line_stmt[row].fn==cnf_line_LEVELDIR)return 17;
if(config_line_stmt[row].fn==cnf_line_SAVEDIR)return 18;
if(config_line_stmt[row].fn==cnf_line_BONESDIR)return 19;
if(config_line_stmt[row].fn==cnf_line_DATADIR)return 20;
if(config_line_stmt[row].fn==cnf_line_SCOREDIR)return 21;
if(config_line_stmt[row].fn==cnf_line_LOCKDIR)return 22;
if(config_line_stmt[row].fn==cnf_line_CONFIGDIR)return 23;
if(config_line_stmt[row].fn==cnf_line_TROUBLEDIR)return 24;
if(config_line_stmt[row].fn==cnf_line_NAME)return 25;
if(config_line_stmt[row].fn==cnf_line_ROLE)return 26;
if(config_line_stmt[row].fn==cnf_line_dogname)return 27;
if(config_line_stmt[row].fn==cnf_line_catname)return 28;
if(config_line_stmt[row].fn==cnf_line_WIZARDS)return 29;
if(config_line_stmt[row].fn==cnf_line_SHELLERS)return 30;
if(config_line_stmt[row].fn==cnf_line_MSGHANDLER)return 31;
if(config_line_stmt[row].fn==cnf_line_EXPLORERS)return 32;
if(config_line_stmt[row].fn==cnf_line_DEBUGFILES)return 33;
if(config_line_stmt[row].fn==cnf_line_DUMPLOGFILE)return 34;
if(config_line_stmt[row].fn==cnf_line_GENERICUSERS)return 35;
if(config_line_stmt[row].fn==cnf_line_BONES_POOLS)return 36;
if(config_line_stmt[row].fn==cnf_line_SUPPORT)return 37;
if(config_line_stmt[row].fn==cnf_line_RECOVER)return 38;
if(config_line_stmt[row].fn==cnf_line_CHECK_SAVE_UID)return 39;
if(config_line_stmt[row].fn==cnf_line_CHECK_PLNAME)return 40;
if(config_line_stmt[row].fn==cnf_line_SEDUCE)return 41;
if(config_line_stmt[row].fn==cnf_line_HIDEUSAGE)return 42;
if(config_line_stmt[row].fn==cnf_line_MAXPLAYERS)return 43;
if(config_line_stmt[row].fn==cnf_line_PERSMAX)return 44;
if(config_line_stmt[row].fn==cnf_line_PERS_IS_UID)return 45;
if(config_line_stmt[row].fn==cnf_line_ENTRYMAX)return 46;
if(config_line_stmt[row].fn==cnf_line_POINTSMIN)return 47;
if(config_line_stmt[row].fn==cnf_line_MAX_STATUENAME_RANK)return 48;
if(config_line_stmt[row].fn==cnf_line_LIVELOG)return 49;
if(config_line_stmt[row].fn==cnf_line_PANICTRACE_LIBC)return 50;
if(config_line_stmt[row].fn==cnf_line_PANICTRACE_GDB)return 51;
if(config_line_stmt[row].fn==cnf_line_GDBPATH)return 52;
if(config_line_stmt[row].fn==cnf_line_GREPPATH)return 53;
if(config_line_stmt[row].fn==cnf_line_CRASHREPORTURL)return 54;
if(config_line_stmt[row].fn==cnf_line_ACCESSIBILITY)return 55;
if(config_line_stmt[row].fn==cnf_line_PORTABLE_DEVICE_PATHS)return 56;
if(config_line_stmt[row].fn==cnf_line_BOULDER)return 57;
if(config_line_stmt[row].fn==cnf_line_MENUCOLOR)return 58;
if(config_line_stmt[row].fn==cnf_line_HILITE_STATUS)return 59;
if(config_line_stmt[row].fn==cnf_line_WARNINGS)return 60;
if(config_line_stmt[row].fn==cnf_line_ROGUESYMBOLS)return 61;
if(config_line_stmt[row].fn==cnf_line_SYMBOLS)return 62;
if(config_line_stmt[row].fn==cnf_line_WIZKIT)return 63;
if(config_line_stmt[row].fn==cnf_line_QT_TILEWIDTH)return 64;
if(config_line_stmt[row].fn==cnf_line_QT_TILEHEIGHT)return 65;
if(config_line_stmt[row].fn==cnf_line_QT_FONTSIZE)return 66;
if(config_line_stmt[row].fn==cnf_line_QT_COMPACT)return 67;
abort();default:abort();}
#endif
}
