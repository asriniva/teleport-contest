#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
extern unsigned long md_ignored_features(void);
extern char *version_id_string(char *,size_t,const char *),*bannerc_string(char *,size_t,const char *);
static char probe_trace_storage[131072],output[4096],word_input[8192],callback_text[3][2048];
static int word_length,nested_callbacks,populate_count,release_count;
void panic(const char *format,...) {abort();}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(probe_trace_storage+strlen(probe_trace_storage),sizeof probe_trace_storage-strlen(probe_trace_storage),format,ap);va_end(ap);}
void nh_snprintf(const char *func,int line,char *str,size_t size,const char *format,...){va_list ap,copy;char rendered[4096];int n;va_start(ap,format);va_copy(copy,ap);vsnprintf(rendered,sizeof rendered,format,copy);va_end(copy);n=vsnprintf(str,size,format,ap);va_end(ap);append("snprintf:%s:%d:%lu:%s;",func,line,(unsigned long)size,rendered);if(n<0||(size_t)n>=size)str[size-1]=0;}
void populate_nomakedefs(struct version_info *v){append("populate:%lu:%lu:%lu;",v->incarnation,v->feature_set,v->entity_count);populate_count++;if(nested_callbacks){mdlib_version_string(callback_text[0],"/");version_id_string(callback_text[1],sizeof callback_text[1],"nested-build");bannerc_string(callback_text[2],sizeof callback_text[2],"nested-build");append("callbacks:%s:%s:%s;",callback_text[0],callback_text[1],callback_text[2]);}}
void free_nomakedefs(void){append("free-date;");release_count++;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/mdlib.c"
#define PRIVATE(name) name
#else
extern void teleport_mdlib_test_make_version(void),teleport_mdlib_test_build_options(void),teleport_mdlib_test_build_savebones_compat_string(void),teleport_mdlib_test_opt_out_words(char *,int *);
extern int teleport_mdlib_test_count_and_validate_winopts(void),teleport_mdlib_test_count_and_validate_soundlibopts(void);
#define PRIVATE(name) teleport_mdlib_test_##name
#endif
#include "tu-mdlib-layout.h"
void probe_reset(void){probe_trace_storage[0]=0;memset(output,0xa5,sizeof output);memset(word_input,0xa5,sizeof word_input);memset(callback_text,0xa5,sizeof callback_text);word_length=0;nested_callbacks=populate_count=release_count=0;}
void probe_reference_reset(void){
#ifdef TELEPORT_REFERENCE_TU
release_runtime_info();memset(optbuf,0,sizeof optbuf);memset(save_bones_compat_buf,0,sizeof save_bones_compat_buf);memset(&version,0,sizeof version);date_via_env=0;memset(opttext,0,sizeof opttext);idxopttext=done_runtime_opt_init_once=0;{int i;for(i=0;i<SIZE(window_opts);i++)window_opts[i].valid=i<SIZE(window_opts)-1;for(i=0;i<SIZE(soundlib_opts);i++)soundlib_opts[i].valid=FALSE;}
#endif
}
void probe_clear(void){probe_trace_storage[0]=0;}
void probe_nested(int yes){nested_callbacks=yes;}
const char *probe_trace(void){return probe_trace_storage;}
void *probe_output(void){return output;}
size_t probe_output_size(void){return sizeof output;}
void *probe_words_pointer(void){return word_input;}
size_t probe_words_size(void){return sizeof word_input;}
int probe_word_length(void){return word_length;}
void probe_words(const char *text,int length){strcpy(word_input,text);word_length=length;PRIVATE(opt_out_words)(word_input,&word_length);}
unsigned long probe_ignored(void){return md_ignored_features();}
int probe_version_string(const char *delimiter){return mdlib_version_string(output+16,delimiter)==output+16;}
int probe_version_id(size_t capacity,const char *date){return version_id_string(output+16,capacity,date)==output+16;}
int probe_banner(size_t capacity,const char *date){return bannerc_string(output+16,capacity,date)==output+16;}
void probe_make_version(void){PRIVATE(make_version)();}
void probe_build(void){PRIVATE(build_options)();}
void probe_compat(void){PRIVATE(build_savebones_compat_string)();}
int probe_validate(int sound){return sound?PRIVATE(count_and_validate_soundlibopts)():PRIVATE(count_and_validate_winopts)();}
void probe_init(void){runtime_info_init();}
void probe_release(void){release_runtime_info();}
const char *probe_next(int *context){return do_runtime_info(context);}
int probe_calls(int n){return n?release_count:populate_count;}
int probe_scalar(int n){
#ifdef TELEPORT_REFERENCE_TU
return n==0?idxopttext:n==1?done_runtime_opt_init_once:date_via_env;
#else
return 0;
#endif
}
unsigned long probe_version_field(int n){
#ifdef TELEPORT_REFERENCE_TU
return n==0?version.incarnation:n==1?version.feature_set:version.entity_count;
#else
return 0;
#endif
}
void probe_set_scalar(int n,int value){
#ifdef TELEPORT_REFERENCE_TU
if(n==0)idxopttext=value;else if(n==1)done_runtime_opt_init_once=value;else date_via_env=value;
#endif
}
void *probe_buffer(int n){
#ifdef TELEPORT_REFERENCE_TU
return n==0?(void*)optbuf:n==1?(void*)&version:(void*)save_bones_compat_buf;
#else
return NULL;
#endif
}
const char *probe_opt(int n){
#ifdef TELEPORT_REFERENCE_TU
return opttext[n];
#else
return NULL;
#endif
}
int probe_table_count(int kind){
#ifdef TELEPORT_REFERENCE_TU
switch(kind){case 0:return SIZE(artifact_names);case 1:return SIZE(build_opts);case 2:return SIZE(window_opts);case 3:return SIZE(soundlib_opts);default:return 1;}
#else
return 0;
#endif
}
const char *probe_table_string(int kind,int index,int field){
#ifdef TELEPORT_REFERENCE_TU
switch(kind){case 0:return artifact_names[index];case 1:return build_opts[index];case 2:return field?window_opts[index].name:window_opts[index].id;case 3:return field?soundlib_opts[index].Url:soundlib_opts[index].text_id;default:return opt_indent;}
#else
return NULL;
#endif
}
int probe_table_value(int kind,int index,int field){
#ifdef TELEPORT_REFERENCE_TU
if(kind==2)return window_opts[index].valid;if(kind==3)return field?soundlib_opts[index].valid:soundlib_opts[index].id;
#endif
return 0;
}
void probe_valid(int kind,int index,int value){
#ifdef TELEPORT_REFERENCE_TU
if(kind==2)window_opts[index].valid=value;else soundlib_opts[index].valid=value;
#endif
}
size_t probe_stack(void){return emscripten_stack_get_current();}
