#include "hack.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef free
extern void free(void *);
__typeof__(gc) gc;
__typeof__(gd) gd;
__typeof__(gh) gh;
__typeof__(program_state) program_state;
__typeof__(iflags) iflags;
__typeof__(windowprocs) windowprocs;
const char *ARGV0;
/* Keep the real match_optname/length_without_val dependency. The unrelated
 * original initoptions entry is renamed only to supply the controlled callback
 * below; neither the original EARLYARG nor the dependency algorithm is edited. */
#define initoptions teleport_earlyarg_unused_initoptions
#include "../nethack-c/upstream/src/options.c"
#undef initoptions

static jmp_buf termination;
static char trace[262144],snapshot[65536],option_name[256]="-windowtype";
static int probe_active,status,exit_status,argc_value,original_argc,callback_stage,grow_stage;
static char *argbuf[64],*owned_args[64],**argv_value=argbuf,*hackdir_value;
static char *result;
static void *growth;
static int free_count;
static void append(const char *format,...)
{
    va_list ap;va_start(ap,format);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),format,ap);va_end(ap);
}
static void callback(int stage)
{
    if(callback_stage==stage){callback_stage=0;append("nested:%d;",argcheck(0,NULL,ARG_DEBUG));}
    if(grow_stage==stage&&!growth){grow_stage=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}
}
void panic(const char *format,...){(void)format;abort();}
void teleport_probe_free(void *value){free_count++;append("free;");free(value);}
void config_error_init(boolean from_file,const char *name,boolean secure)
{ append("config-init:%d:%s:%d;",from_file,name,secure);callback(1); }
int config_error_done(void){append("config-done;");callback(2);return 0;}
void config_error_add(const char *format,...)
{ char text[1024];va_list ap;va_start(ap,format);vsnprintf(text,sizeof text,format,ap);va_end(ap);append("config:%s;",text);callback(3); }
void nh_terminate(int code){exit_status=code;append("terminate:%d;",code);if(!probe_active)abort();longjmp(termination,1);}
void error(const char *format,...)
{ char text[1024];va_list ap;va_start(ap,format);vsnprintf(text,sizeof text,format,ap);va_end(ap);append("error:%s;",text);if(!probe_active)abort();longjmp(termination,2); }
void chdirx(const char *dir,boolean required){append("chdir:%s:%d;",dir?dir:"<NULL>",required);callback(4);}
void genl_display_file(const char *name,boolean complain){append("display:%s:%d;",name,complain);callback(5);}
void initoptions(void){append("initoptions:%d;",iflags.initoptions_noterminate);callback(6);}
void panictrace_setsignals(boolean on){append("signals:%d;",on);}
boolean whoami(void){append("whoami;");return TRUE;}
void prscore(int argc,char **argv)
{ int i;append("scores:%d;",argc);for(i=0;i<argc;i++)append("score-arg:%s;",argv[i]);callback(7); }
void early_version_info(boolean copy){append("version:%d;",copy);callback(8);}
void dump_version_info(void){append("version-dump;");}
void dump_mongen(void){append("mongen;");}
void dump_weights(void){append("weights;");}
void crashreport_bidshow(void){append("bidshow;");}
void dump_all_glyphids(FILE *stream){append("glyphids:%d;",stream==stdout);callback(9);}
static void fixture_raw_print(const char *text){append("line:%s\n",text);callback(10);}
void raw_printf(const char *format,...)
{ char text[2048];va_list ap;va_start(ap,format);vsnprintf(text,sizeof text,format,ap);va_end(ap);fixture_raw_print(text); }
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../nethack-c/upstream/src/earlyarg.c"
#undef free
#else
extern char *teleport_earlyarg_test_lopt(char*,int,const char*,const char*,int*,char***);
extern void teleport_earlyarg_test_consume(int,int*,char***);
extern void teleport_earlyarg_test_consume_two(int,int*,char***);
extern void teleport_earlyarg_test_terminate(void);
extern void teleport_earlyarg_test_usage(const char*);
extern void teleport_earlyarg_test_scores(int,char**,const char*);
extern void teleport_earlyarg_test_debug(char*);
extern void teleport_earlyarg_test_enums(void);
extern void *teleport_earlyarg_storage(int);
#define lopt teleport_earlyarg_test_lopt
#define consume_arg teleport_earlyarg_test_consume
#define consume_two_args teleport_earlyarg_test_consume_two
#define opt_terminate teleport_earlyarg_test_terminate
#define opt_usage teleport_earlyarg_test_usage
#define scores_only teleport_earlyarg_test_scores
#define debug_fields teleport_earlyarg_test_debug
#define dump_enums teleport_earlyarg_test_enums
#define ArgVal_novalue ((char*)teleport_earlyarg_storage(2))
#endif
#include "tu-earlyarg-layout.h"
#include "../nethack-c/wasm/tu-earlyarg-support.h"
void probe_reset(int count)
{
    int i;for(i=0;i<64;i++){free(owned_args[i]);owned_args[i]=NULL;argbuf[i]=NULL;}
    free(gc.cmdline_rcfile);free(gc.cmdline_windowsys);free(growth);growth=NULL;
    memset(&gc,0,sizeof gc);memset(&gd,0,sizeof gd);memset(&gh,0,sizeof gh);
    memset(&program_state,0,sizeof program_state);memset(&iflags,0,sizeof iflags);
    argc_value=original_argc=count;argv_value=argbuf;hackdir_value=NULL;result=NULL;
    status=exit_status=callback_stage=grow_stage=free_count=0;trace[0]=0;
    gh.hname="fixture-nethack";ARGV0="before";program_state.early_options=7;
    windowprocs.win_raw_print=fixture_raw_print;
}
void probe_arg(int index,const char *text)
{ size_t size=strlen(text)+1;free(owned_args[index]);owned_args[index]=malloc(size);memcpy(owned_args[index],text,size);argbuf[index]=owned_args[index]; }
void probe_directory(int index){hackdir_value=index<0?NULL:argbuf[index];}
void probe_option_name(const char *text){strcpy(option_name,text);}
void probe_preset(int kind){if(kind&1)gc.cmdline_windowsys=dupstr("old-windows");if(kind&2)gc.cmdline_rcfile=dupstr("old-rc");}
void probe_callback(int stage,int grow){callback_stage=stage;grow_stage=grow;}
int probe_action(int op,int argument,int shift)
{
    probe_active=1;result=NULL;status=setjmp(termination);
    if(status){probe_active=0;return -status;}
    switch(op){
    case 0:early_options(&argc_value,&argv_value,&hackdir_value);break;
    case 1:argument=argcheck(argc_value,argv_value,argument);probe_active=0;return argument;
    case 2:debug_fields(argv_value[argument]);break;
    case 3:result=lopt(argv_value[0]+shift,argument,option_name,argv_value[0],&argc_value,&argv_value);break;
    case 4:consume_arg(argument,&argc_value,&argv_value);break;
    case 5:consume_two_args(argument,&argc_value,&argv_value);break;
    case 6:opt_usage(hackdir_value);break;
    case 7:after_opt_showpaths(hackdir_value);break;
    case 8:scores_only(argc_value,argv_value,hackdir_value);break;
    case 9:opt_terminate();break;
    case 10:dump_enums();break;
    case 11:dump_glyphids();break;
    }
    probe_active=0;return 0;
}
const char *probe_trace(void){return trace;}
const char *probe_snapshot(void)
{
    int i;char *p=snapshot;
    p+=sprintf(p,"argc:%d;argv:%ld;state:%d:%d:%d:%d:%d:%d:%d;strings:%s:%s:%s:%s:%s;status:%d:%d;frees:%d;args:",argc_value,(long)(argv_value-argbuf),program_state.early_options,gd.deferred_showpaths,iflags.initoptions_noterminate,iflags.debug.test,iflags.debug.ttystatus,iflags.fuzzerpending,gd.deferred_showpaths_dir==hackdir_value,gc.cmdline_rcfile?gc.cmdline_rcfile:"<NULL>",gc.cmdline_windowsys?gc.cmdline_windowsys:"<NULL>",hackdir_value?hackdir_value:"<NULL>",gd.deferred_showpaths_dir?gd.deferred_showpaths_dir:"<NULL>",ARGV0?ARGV0:"<NULL>",status,exit_status,free_count);
    for(i=0;i<original_argc;i++)p+=sprintf(p,"[%s]",argbuf[i]?argbuf[i]:"<NULL>");
    return snapshot;
}
char *probe_result(void){return result;}
int probe_result_alias(void)
{
    int i;if(!result)return -1;if(result==ArgVal_novalue)return -2;
    for(i=0;i<64;i++)if(owned_args[i]&&(uintptr_t)result>=(uintptr_t)owned_args[i]&&(uintptr_t)result<=(uintptr_t)owned_args[i]+strlen(owned_args[i]))return i*10000+(int)(result-owned_args[i]);
    return -3;
}
char *probe_pointer(int index)
{ return index==0?ArgVal_novalue:index==1?gc.cmdline_rcfile:index==2?gc.cmdline_windowsys:index==3?hackdir_value:index>=4&&index<68?argbuf[index-4]:NULL; }
void probe_mutate(int index,int offset,int value){probe_pointer(index)[offset]=(char)value;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
#ifdef TELEPORT_REFERENCE_TU
static const struct enum_dump *probe_catalogues[]={monsdump,objdump,defsym_cmap_dump,defsym_mon_syms_dump,defsym_mon_defchars_dump,objclass_defchars_dump,objclass_classes_dump,objclass_syms_dump,arti_enum_dump,mcastu_enum_dump};
static const int probe_catalogue_sizes[]={SIZE(monsdump),SIZE(objdump),SIZE(defsym_cmap_dump),SIZE(defsym_mon_syms_dump),SIZE(defsym_mon_defchars_dump),SIZE(objclass_defchars_dump),SIZE(objclass_classes_dump),SIZE(objclass_syms_dump),SIZE(arti_enum_dump),SIZE(mcastu_enum_dump)};
int probe_table_count(int table){return probe_catalogue_sizes[table];}
const char *probe_table_name(int table,int row){return probe_catalogues[table][row].nm;}
int probe_table_value(int table,int row){return probe_catalogues[table][row].val;}
#else
int probe_table_count(int table){return table==0?TELEPORT_EARLYARG_MONSDUMP_COUNT:table==1?TELEPORT_EARLYARG_OBJDUMP_COUNT:0;}
const char *probe_table_name(int table,int row){return ((struct enum_dump*)teleport_earlyarg_storage(table))[row].nm;}
int probe_table_value(int table,int row){return ((struct enum_dump*)teleport_earlyarg_storage(table))[row].val;}
#endif

int probe_arg_origin(int slot) { int i;for(i=0;i<64;i++)if(argbuf[slot]==owned_args[i]&&owned_args[i])return i;return -1; }

/* Test-only native writes to the original externally visible mutable arrays. */
#ifdef TELEPORT_REFERENCE_TU
static struct enum_dump *probe_external_table(int table) { return table ? objdump : monsdump; }
#else
static struct enum_dump *probe_external_table(int table) { return teleport_earlyarg_storage(table); }
#endif
void probe_table_set_value(int table,int row,int value) { probe_external_table(table)[row].val=value; }
void probe_table_set_name(int table,int row,const char *value) { probe_external_table(table)[row].nm=value; }
