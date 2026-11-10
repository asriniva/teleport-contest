/* CFGFILES typed ABI/backing only; all config algorithms/tables remain JS. */
#include "cfgfiles-types.h"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(va_list)==8 && sizeof(size_t)==8,"CFGFILES memory64 long/pointer/va_list/size_t ABI");
_Static_assert(sizeof(int)==4 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"CFGFILES scalar ABI");
/* Configured source/field/dependency ABI guards; no algorithms. */
_Static_assert(sizeof(lua_Integer)==8 && (lua_Integer)-1<0,"CFGFILES Lua integer signed64");
_Static_assert((size_t)-1>0 && (long)-1<0 && __builtin_types_compatible_p(va_list,void*),"CFGFILES size_t/long/actual va_list");
_Static_assert(sizeof(((struct _cnf_parser_state*)0)->inbufsz)==4 && (((__typeof__(((struct _cnf_parser_state*)0)->inbufsz))-1<0)==0),"CFGFILES _cnf_parser_state.inbufsz width/sign");
_Static_assert(sizeof(((struct _cnf_parser_state*)0)->rv)==4 && (((__typeof__(((struct _cnf_parser_state*)0)->rv))-1<0)==1),"CFGFILES _cnf_parser_state.rv width/sign");
_Static_assert(sizeof(((struct _cnf_parser_state*)0)->skip)==1 && (((__typeof__(((struct _cnf_parser_state*)0)->skip))-1<0)==1),"CFGFILES _cnf_parser_state.skip width/sign");
_Static_assert(sizeof(((struct _cnf_parser_state*)0)->morelines)==1 && (((__typeof__(((struct _cnf_parser_state*)0)->morelines))-1<0)==1),"CFGFILES _cnf_parser_state.morelines width/sign");
_Static_assert(sizeof(((struct _cnf_parser_state*)0)->cont)==1 && (((__typeof__(((struct _cnf_parser_state*)0)->cont))-1<0)==1),"CFGFILES _cnf_parser_state.cont width/sign");
_Static_assert(sizeof(((struct _cnf_parser_state*)0)->pbreak)==1 && (((__typeof__(((struct _cnf_parser_state*)0)->pbreak))-1<0)==1),"CFGFILES _cnf_parser_state.pbreak width/sign");
_Static_assert(sizeof(((struct _config_error_errmsg*)0)->line_num)==4 && (((__typeof__(((struct _config_error_errmsg*)0)->line_num))-1<0)==1),"CFGFILES _config_error_errmsg.line_num width/sign");
_Static_assert(sizeof(((struct _config_error_frame*)0)->line_num)==4 && (((__typeof__(((struct _config_error_frame*)0)->line_num))-1<0)==1),"CFGFILES _config_error_frame.line_num width/sign");
_Static_assert(sizeof(((struct _config_error_frame*)0)->num_errors)==4 && (((__typeof__(((struct _config_error_frame*)0)->num_errors))-1<0)==1),"CFGFILES _config_error_frame.num_errors width/sign");
_Static_assert(sizeof(((struct _config_error_frame*)0)->origline_shown)==1 && (((__typeof__(((struct _config_error_frame*)0)->origline_shown))-1<0)==1),"CFGFILES _config_error_frame.origline_shown width/sign");
_Static_assert(sizeof(((struct _config_error_frame*)0)->fromfile)==1 && (((__typeof__(((struct _config_error_frame*)0)->fromfile))-1<0)==1),"CFGFILES _config_error_frame.fromfile width/sign");
_Static_assert(sizeof(((struct _config_error_frame*)0)->secure)==1 && (((__typeof__(((struct _config_error_frame*)0)->secure))-1<0)==1),"CFGFILES _config_error_frame.secure width/sign");
_Static_assert(sizeof(((struct flag*)0)->suppress_alert)==8 && (((__typeof__(((struct flag*)0)->suppress_alert))-1<0)==0),"CFGFILES flag.suppress_alert width/sign");
_Static_assert(sizeof(((struct flag*)0)->initrole)==4 && (((__typeof__(((struct flag*)0)->initrole))-1<0)==1),"CFGFILES flag.initrole width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->in_lua)==1 && (((__typeof__(((struct instance_flags*)0)->in_lua))-1<0)==1),"CFGFILES instance_flags.in_lua width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->last_msg)==4 && (((__typeof__(((struct instance_flags*)0)->last_msg))-1<0)==1),"CFGFILES instance_flags.last_msg width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->parse_config_file_src)==4 && (((__typeof__(((struct instance_flags*)0)->parse_config_file_src))-1<0)==1),"CFGFILES instance_flags.parse_config_file_src width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->window_inited)==1 && (((__typeof__(((struct instance_flags*)0)->window_inited))-1<0)==1),"CFGFILES instance_flags.window_inited width/sign");
_Static_assert(sizeof(((struct instance_globals_d*)0)->deferred_showpaths)==1 && (((__typeof__(((struct instance_globals_d*)0)->deferred_showpaths))-1<0)==1),"CFGFILES instance_globals_d.deferred_showpaths width/sign");
_Static_assert(sizeof(((struct instance_globals_n*)0)->no_sound_notified)==4 && (((__typeof__(((struct instance_globals_n*)0)->no_sound_notified))-1<0)==1),"CFGFILES instance_globals_n.no_sound_notified width/sign");
_Static_assert(sizeof(((struct sinfo*)0)->config_error_ready)==4 && (((__typeof__(((struct sinfo*)0)->config_error_ready))-1<0)==1),"CFGFILES sinfo.config_error_ready width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->env_dbgfl)==4 && (((__typeof__(((struct sysopt_s*)0)->env_dbgfl))-1<0)==1),"CFGFILES sysopt_s.env_dbgfl width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->maxplayers)==4 && (((__typeof__(((struct sysopt_s*)0)->maxplayers))-1<0)==1),"CFGFILES sysopt_s.maxplayers width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->seduce)==4 && (((__typeof__(((struct sysopt_s*)0)->seduce))-1<0)==1),"CFGFILES sysopt_s.seduce width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->check_save_uid)==4 && (((__typeof__(((struct sysopt_s*)0)->check_save_uid))-1<0)==1),"CFGFILES sysopt_s.check_save_uid width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->check_plname)==4 && (((__typeof__(((struct sysopt_s*)0)->check_plname))-1<0)==1),"CFGFILES sysopt_s.check_plname width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->bones_pools)==4 && (((__typeof__(((struct sysopt_s*)0)->bones_pools))-1<0)==1),"CFGFILES sysopt_s.bones_pools width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->livelog)==8 && (((__typeof__(((struct sysopt_s*)0)->livelog))-1<0)==1),"CFGFILES sysopt_s.livelog width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->persmax)==4 && (((__typeof__(((struct sysopt_s*)0)->persmax))-1<0)==1),"CFGFILES sysopt_s.persmax width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->pers_is_uid)==4 && (((__typeof__(((struct sysopt_s*)0)->pers_is_uid))-1<0)==1),"CFGFILES sysopt_s.pers_is_uid width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->entrymax)==4 && (((__typeof__(((struct sysopt_s*)0)->entrymax))-1<0)==1),"CFGFILES sysopt_s.entrymax width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->pointsmin)==4 && (((__typeof__(((struct sysopt_s*)0)->pointsmin))-1<0)==1),"CFGFILES sysopt_s.pointsmin width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->tt_oname_maxrank)==4 && (((__typeof__(((struct sysopt_s*)0)->tt_oname_maxrank))-1<0)==1),"CFGFILES sysopt_s.tt_oname_maxrank width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->panictrace_gdb)==4 && (((__typeof__(((struct sysopt_s*)0)->panictrace_gdb))-1<0)==1),"CFGFILES sysopt_s.panictrace_gdb width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->panictrace_libc)==4 && (((__typeof__(((struct sysopt_s*)0)->panictrace_libc))-1<0)==1),"CFGFILES sysopt_s.panictrace_libc width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->accessibility)==4 && (((__typeof__(((struct sysopt_s*)0)->accessibility))-1<0)==1),"CFGFILES sysopt_s.accessibility width/sign");
_Static_assert(sizeof(((struct sysopt_s*)0)->hideusage)==4 && (((__typeof__(((struct sysopt_s*)0)->hideusage))-1<0)==1),"CFGFILES sysopt_s.hideusage width/sign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&paranoid_query),boolean (*)(boolean, const char *)),"CFGFILES dependency paranoid_query");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fopen),FILE *(*)(const char *, const char *)),"CFGFILES dependency fopen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strbuf_init),void (*)(strbuf_t *)),"CFGFILES dependency strbuf_init");
_Static_assert(__builtin_types_compatible_p(__typeof__(&all_options_strbuf),void (*)(strbuf_t *)),"CFGFILES dependency all_options_strbuf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strlen),unsigned long (*)(const char *)),"CFGFILES dependency strlen");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fwrite),unsigned long (*)(const void *, unsigned long, unsigned long, FILE *)),"CFGFILES dependency fwrite");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fclose),int (*)(FILE *)),"CFGFILES dependency fclose");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strbuf_empty),void (*)(strbuf_t *)),"CFGFILES dependency strbuf_empty");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncpy),char *(*)(char *, const char *, unsigned long)),"CFGFILES dependency strncpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fqname),const char *(*)(const char *, int, int)),"CFGFILES dependency fqname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strncmp),int (*)(const char *, const char *, unsigned long)),"CFGFILES dependency strncmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_getenv),char *(*)(const char *)),"CFGFILES dependency nh_getenv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&access),int (*)(const char *, int)),"CFGFILES dependency access");
_Static_assert(__builtin_types_compatible_p(__typeof__(&__errno_location),int *(*)(void)),"CFGFILES dependency __errno_location");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char *(*)(char *, const char *)),"CFGFILES dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strerror),char *(*)(int)),"CFGFILES dependency strerror");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"CFGFILES dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *, int, const char *)),"CFGFILES dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"CFGFILES dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&free),void (*)(void *)),"CFGFILES dependency free");
_Static_assert(__builtin_types_compatible_p(__typeof__(&trimspaces),char *(*)(char *)),"CFGFILES dependency trimspaces");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strchr),char *(*)(const char *, int)),"CFGFILES dependency strchr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dupstr),char *(*)(const char *)),"CFGFILES dependency dupstr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&debugcore),boolean (*)(const char *, boolean)),"CFGFILES dependency debugcore");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcmp),int (*)(const char *, const char *)),"CFGFILES dependency strcmp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&parseoptions),boolean (*)(char *, boolean, boolean)),"CFGFILES dependency parseoptions");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_autopickup_exception),int (*)(const char *)),"CFGFILES dependency add_autopickup_exception");
_Static_assert(__builtin_types_compatible_p(__typeof__(&parsebindings),boolean (*)(char *)),"CFGFILES dependency parsebindings");
_Static_assert(__builtin_types_compatible_p(__typeof__(&parseautocomplete),void (*)(char *, boolean)),"CFGFILES dependency parseautocomplete");
_Static_assert(__builtin_types_compatible_p(__typeof__(&msgtype_parse_add),boolean (*)(char *)),"CFGFILES dependency msgtype_parse_add");
_Static_assert(__builtin_types_compatible_p(__typeof__(&str2role),int (*)(const char *)),"CFGFILES dependency str2role");
_Static_assert(__builtin_types_compatible_p(__typeof__(&build_english_list),char *(*)(char *)),"CFGFILES dependency build_english_list");
_Static_assert(__builtin_types_compatible_p(__typeof__(&atoi),int (*)(const char *)),"CFGFILES dependency atoi");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sysopt_seduce_set),void (*)(int)),"CFGFILES dependency sysopt_seduce_set");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strtol),long (*)(const char *, char **, int)),"CFGFILES dependency strtol");
_Static_assert(__builtin_types_compatible_p(__typeof__(&file_exists),boolean (*)(const char *)),"CFGFILES dependency file_exists");
_Static_assert(__builtin_types_compatible_p(__typeof__(&add_menu_coloring),boolean (*)(char *)),"CFGFILES dependency add_menu_coloring");
_Static_assert(__builtin_types_compatible_p(__typeof__(&parse_status_hl1),boolean (*)(char *, boolean)),"CFGFILES dependency parse_status_hl1");
_Static_assert(__builtin_types_compatible_p(__typeof__(&assign_warnings),void (*)(uchar *)),"CFGFILES dependency assign_warnings");
_Static_assert(__builtin_types_compatible_p(__typeof__(&parsesymbols),boolean (*)(char *, int)),"CFGFILES dependency parsesymbols");
_Static_assert(__builtin_types_compatible_p(__typeof__(&switch_symbols),void (*)(int)),"CFGFILES dependency switch_symbols");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mungspaces),char *(*)(char *)),"CFGFILES dependency mungspaces");
_Static_assert(__builtin_types_compatible_p(__typeof__(&match_optname),boolean (*)(const char *, const char *, int, boolean)),"CFGFILES dependency match_optname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&alloc),long *(*)(unsigned int)),"CFGFILES dependency alloc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lua_createtable),void (*)(lua_State *, int, int)),"CFGFILES dependency lua_createtable");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lua_pushinteger),void (*)(lua_State *, lua_Integer)),"CFGFILES dependency lua_pushinteger");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nhl_add_table_entry_int),void (*)(lua_State *, const char *, lua_Integer)),"CFGFILES dependency nhl_add_table_entry_int");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nhl_add_table_entry_str),void (*)(lua_State *, const char *, const char *)),"CFGFILES dependency nhl_add_table_entry_str");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lua_settable),void (*)(lua_State *, int)),"CFGFILES dependency lua_settable");
_Static_assert(__builtin_types_compatible_p(__typeof__(&c_eos),const char *(*)(const char *)),"CFGFILES dependency c_eos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&reset_duplicate_opt_detection),void (*)(void)),"CFGFILES dependency reset_duplicate_opt_detection");
_Static_assert(__builtin_types_compatible_p(__typeof__(&memset),void *(*)(void *, int, unsigned long)),"CFGFILES dependency memset");
_Static_assert(__builtin_types_compatible_p(__typeof__(&eos),char *(*)(char *)),"CFGFILES dependency eos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcat),char *(*)(char *, const char *)),"CFGFILES dependency strcat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&fgets),char *(*)(char *restrict, int, FILE *restrict)),"CFGFILES dependency fgets");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vsnprintf),int (*)(char *restrict, unsigned long, const char *restrict, __builtin_va_list)),"CFGFILES dependency vsnprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&getenv),char *(*)(const char *)),"CFGFILES dependency getenv");
_Static_assert(__builtin_types_compatible_p(__typeof__(&allopt_array_init),void (*)(void)),"CFGFILES dependency allopt_array_init");
_Static_assert(__builtin_types_compatible_p(__typeof__(&disregard_all_options),void (*)(void)),"CFGFILES dependency disregard_all_options");
_Static_assert(__builtin_types_compatible_p(__typeof__(&heed_this_option),void (*)(enum opt)),"CFGFILES dependency heed_this_option");
_Static_assert(__builtin_types_compatible_p(__typeof__(&heed_all_options),void (*)(void)),"CFGFILES dependency heed_all_options");
_Static_assert(__builtin_types_compatible_p(__typeof__(&disregard_this_option),void (*)(enum opt)),"CFGFILES dependency disregard_this_option");
_Static_assert(__builtin_types_compatible_p(__typeof__(&close),int (*)(int)),"CFGFILES dependency close");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_deferred_showpaths),void (*)(int)),"CFGFILES dependency do_deferred_showpaths");
_Static_assert(__builtin_types_compatible_p(__typeof__(&exit),void (*)(int)),"CFGFILES dependency exit");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pline),void (*)(const char *, ...)),"CFGFILES variadic pline");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sprintf),int (*)(char *restrict, const char *restrict, ...)),"CFGFILES variadic sprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&nh_snprintf),void (*)(const char *, int, char *, size_t, const char *, ...)),"CFGFILES variadic nh_snprintf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&raw_printf),void (*)(const char *, ...)),"CFGFILES variadic raw_printf");
_Static_assert(__builtin_types_compatible_p(__typeof__(&config_error_add),void (*)(const char *, ...)),"CFGFILES variadic config_error_add");
_Static_assert(__builtin_types_compatible_p(__typeof__(&open),int (*)(const char *, int, ...)),"CFGFILES variadic open");
static char cfgfiles_configfile[BUFSZ];
void*teleport_cfgfiles_global(int index){switch(index){
case 0:return(void*)&flags;
case 1:return(void*)&windowprocs;
case 2:return(void*)&gc;
case 3:return(void*)&iflags;
case 4:return(void*)&svp;
case 5:return(void*)&gd;
case 6:return(void*)&sysopt;
case 7:return(void*)&go;
case 8:return(void*)&gw;
case 9:return(void*)&program_state;
case 10:return(void*)&gn;
case 11:return cfgfiles_configfile;
default:abort();}}
uint64_t teleport_cfgfiles_read(int kind,void*at,int field){switch(kind){
case 0:{struct _cnf_parser_state*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->inbuf);
case 1:return(uint64_t)(uintptr_t)(p->inbufsz);
case 2:return(uint64_t)(uintptr_t)(p->rv);
case 3:return(uint64_t)(uintptr_t)(p->ep);
case 4:return(uint64_t)(uintptr_t)(p->buf);
case 5:return(uint64_t)(uintptr_t)(p->skip);
case 6:return(uint64_t)(uintptr_t)(p->morelines);
case 7:return(uint64_t)(uintptr_t)(p->cont);
case 8:return(uint64_t)(uintptr_t)(p->pbreak);
default:abort();}}
case 1:{struct _config_error_errmsg*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->line_num);
case 1:return(uint64_t)(uintptr_t)(p->errormsg);
case 2:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 2:{struct _config_error_frame*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->line_num);
case 1:return(uint64_t)(uintptr_t)(p->num_errors);
case 2:return(uint64_t)(uintptr_t)(p->origline_shown);
case 3:return(uint64_t)(uintptr_t)(p->fromfile);
case 4:return(uint64_t)(uintptr_t)(p->secure);
case 5:return(uint64_t)(uintptr_t)(&p->origline);
case 6:return(uint64_t)(uintptr_t)(&p->source);
case 7:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->suppress_alert);
case 1:return(uint64_t)(uintptr_t)(p->initrole);
default:abort();}}
case 4:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->in_lua);
case 1:return(uint64_t)(uintptr_t)(p->last_msg);
case 2:return(uint64_t)(uintptr_t)(p->parse_config_file_src);
case 3:return(uint64_t)(uintptr_t)(p->window_inited);
default:abort();}}
case 5:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->catname);
case 1:return(uint64_t)(uintptr_t)(p->cmdline_rcfile);
case 2:return(uint64_t)(uintptr_t)(p->config_section_chosen);
case 3:return(uint64_t)(uintptr_t)(p->config_section_current);
default:abort();}}
case 6:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dogname);
case 1:return(uint64_t)(uintptr_t)(p->deferred_showpaths);
default:abort();}}
case 7:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->no_sound_notified);
default:abort();}}
case 8:{struct instance_globals_o*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->ov_primary_syms);
case 1:return(uint64_t)(uintptr_t)(p->opt_phase);
default:abort();}}
case 9:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 10:{struct instance_globals_w*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->wizkit);
default:abort();}}
case 11:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->config_error_ready);
default:abort();}}
case 12:{struct strbuf*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->str);
default:abort();}}
case 13:{struct sysopt_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->support);
case 1:return(uint64_t)(uintptr_t)(p->recover);
case 2:return(uint64_t)(uintptr_t)(p->wizards);
case 3:return(uint64_t)(uintptr_t)(p->fmtd_wizard_list);
case 4:return(uint64_t)(uintptr_t)(p->explorers);
case 5:return(uint64_t)(uintptr_t)(p->shellers);
case 6:return(uint64_t)(uintptr_t)(p->genericusers);
case 7:return(uint64_t)(uintptr_t)(p->debugfiles);
case 8:return(uint64_t)(uintptr_t)(p->msghandler);
case 9:return(uint64_t)(uintptr_t)(p->env_dbgfl);
case 10:return(uint64_t)(uintptr_t)(p->maxplayers);
case 11:return(uint64_t)(uintptr_t)(p->seduce);
case 12:return(uint64_t)(uintptr_t)(p->check_save_uid);
case 13:return(uint64_t)(uintptr_t)(p->check_plname);
case 14:return(uint64_t)(uintptr_t)(p->bones_pools);
case 15:return(uint64_t)(uintptr_t)(p->livelog);
case 16:return(uint64_t)(uintptr_t)(p->persmax);
case 17:return(uint64_t)(uintptr_t)(p->pers_is_uid);
case 18:return(uint64_t)(uintptr_t)(p->entrymax);
case 19:return(uint64_t)(uintptr_t)(p->pointsmin);
case 20:return(uint64_t)(uintptr_t)(p->tt_oname_maxrank);
case 21:return(uint64_t)(uintptr_t)(p->gdbpath);
case 22:return(uint64_t)(uintptr_t)(p->greppath);
case 23:return(uint64_t)(uintptr_t)(p->crashreporturl);
case 24:return(uint64_t)(uintptr_t)(p->panictrace_gdb);
case 25:return(uint64_t)(uintptr_t)(p->panictrace_libc);
case 26:return(uint64_t)(uintptr_t)(p->accessibility);
case 27:return(uint64_t)(uintptr_t)(p->hideusage);
default:abort();}}
case 14:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_wait_synch);
default:abort();}}
default:abort();}}
void teleport_cfgfiles_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct _cnf_parser_state*p=at;switch(field){
case 0:p->inbuf=(__typeof__(p->inbuf))value;return;
case 1:p->inbufsz=(__typeof__(p->inbufsz))value;return;
case 2:p->rv=(__typeof__(p->rv))value;return;
case 3:p->ep=(__typeof__(p->ep))value;return;
case 4:p->buf=(__typeof__(p->buf))value;return;
case 5:p->skip=(__typeof__(p->skip))value;return;
case 6:p->morelines=(__typeof__(p->morelines))value;return;
case 7:p->cont=(__typeof__(p->cont))value;return;
case 8:p->pbreak=(__typeof__(p->pbreak))value;return;
default:abort();}}
case 1:{struct _config_error_errmsg*p=at;switch(field){
case 0:p->line_num=(__typeof__(p->line_num))value;return;
case 1:p->errormsg=(__typeof__(p->errormsg))value;return;
case 2:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 2:{struct _config_error_frame*p=at;switch(field){
case 0:p->line_num=(__typeof__(p->line_num))value;return;
case 1:p->num_errors=(__typeof__(p->num_errors))value;return;
case 2:p->origline_shown=(__typeof__(p->origline_shown))value;return;
case 3:p->fromfile=(__typeof__(p->fromfile))value;return;
case 4:p->secure=(__typeof__(p->secure))value;return;
case 7:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:p->suppress_alert=(__typeof__(p->suppress_alert))value;return;
case 1:p->initrole=(__typeof__(p->initrole))value;return;
default:abort();}}
case 4:{struct instance_flags*p=at;switch(field){
case 0:p->in_lua=(__typeof__(p->in_lua))value;return;
case 1:p->last_msg=(__typeof__(p->last_msg))value;return;
case 2:p->parse_config_file_src=(__typeof__(p->parse_config_file_src))value;return;
case 3:p->window_inited=(__typeof__(p->window_inited))value;return;
default:abort();}}
case 5:{struct instance_globals_c*p=at;switch(field){
case 1:p->cmdline_rcfile=(__typeof__(p->cmdline_rcfile))value;return;
case 2:p->config_section_chosen=(__typeof__(p->config_section_chosen))value;return;
case 3:p->config_section_current=(__typeof__(p->config_section_current))value;return;
default:abort();}}
case 6:{struct instance_globals_d*p=at;switch(field){
case 1:p->deferred_showpaths=(__typeof__(p->deferred_showpaths))value;return;
default:abort();}}
case 7:{struct instance_globals_n*p=at;switch(field){
case 0:p->no_sound_notified=(__typeof__(p->no_sound_notified))value;return;
default:abort();}}
case 8:{struct instance_globals_o*p=at;switch(field){
case 1:p->opt_phase=(__typeof__(p->opt_phase))value;return;
default:abort();}}
case 9:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 10:{struct instance_globals_w*p=at;switch(field){
default:abort();}}
case 11:{struct sinfo*p=at;switch(field){
case 0:p->config_error_ready=(__typeof__(p->config_error_ready))value;return;
default:abort();}}
case 12:{struct strbuf*p=at;switch(field){
case 0:p->str=(__typeof__(p->str))value;return;
default:abort();}}
case 13:{struct sysopt_s*p=at;switch(field){
case 0:p->support=(__typeof__(p->support))value;return;
case 1:p->recover=(__typeof__(p->recover))value;return;
case 2:p->wizards=(__typeof__(p->wizards))value;return;
case 3:p->fmtd_wizard_list=(__typeof__(p->fmtd_wizard_list))value;return;
case 4:p->explorers=(__typeof__(p->explorers))value;return;
case 5:p->shellers=(__typeof__(p->shellers))value;return;
case 6:p->genericusers=(__typeof__(p->genericusers))value;return;
case 7:p->debugfiles=(__typeof__(p->debugfiles))value;return;
case 8:p->msghandler=(__typeof__(p->msghandler))value;return;
case 9:p->env_dbgfl=(__typeof__(p->env_dbgfl))value;return;
case 10:p->maxplayers=(__typeof__(p->maxplayers))value;return;
case 11:p->seduce=(__typeof__(p->seduce))value;return;
case 12:p->check_save_uid=(__typeof__(p->check_save_uid))value;return;
case 13:p->check_plname=(__typeof__(p->check_plname))value;return;
case 14:p->bones_pools=(__typeof__(p->bones_pools))value;return;
case 15:p->livelog=(__typeof__(p->livelog))value;return;
case 16:p->persmax=(__typeof__(p->persmax))value;return;
case 17:p->pers_is_uid=(__typeof__(p->pers_is_uid))value;return;
case 18:p->entrymax=(__typeof__(p->entrymax))value;return;
case 19:p->pointsmin=(__typeof__(p->pointsmin))value;return;
case 20:p->tt_oname_maxrank=(__typeof__(p->tt_oname_maxrank))value;return;
case 21:p->gdbpath=(__typeof__(p->gdbpath))value;return;
case 22:p->greppath=(__typeof__(p->greppath))value;return;
case 23:p->crashreporturl=(__typeof__(p->crashreporturl))value;return;
case 24:p->panictrace_gdb=(__typeof__(p->panictrace_gdb))value;return;
case 25:p->panictrace_libc=(__typeof__(p->panictrace_libc))value;return;
case 26:p->accessibility=(__typeof__(p->accessibility))value;return;
case 27:p->hideusage=(__typeof__(p->hideusage))value;return;
default:abort();}}
case 14:{struct window_procs*p=at;switch(field){
case 0:p->win_wait_synch=(__typeof__(p->win_wait_synch))value;return;
default:abort();}}
default:abort();}}
void* teleport_cfgfiles_address(int kind,void*at,int field){switch(kind){
case 0:{struct _cnf_parser_state*p=at;switch(field){
case 0:return(void*)&p->inbuf;
case 1:return(void*)&p->inbufsz;
case 2:return(void*)&p->rv;
case 3:return(void*)&p->ep;
case 4:return(void*)&p->buf;
case 5:return(void*)&p->skip;
case 6:return(void*)&p->morelines;
case 7:return(void*)&p->cont;
case 8:return(void*)&p->pbreak;
default:abort();}}
case 1:{struct _config_error_errmsg*p=at;switch(field){
case 0:return(void*)&p->line_num;
case 1:return(void*)&p->errormsg;
case 2:return(void*)&p->next;
default:abort();}}
case 2:{struct _config_error_frame*p=at;switch(field){
case 0:return(void*)&p->line_num;
case 1:return(void*)&p->num_errors;
case 2:return(void*)&p->origline_shown;
case 3:return(void*)&p->fromfile;
case 4:return(void*)&p->secure;
case 5:return(void*)&p->origline;
case 6:return(void*)&p->source;
case 7:return(void*)&p->next;
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:return(void*)&p->suppress_alert;
case 1:return(void*)&p->initrole;
default:abort();}}
case 4:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->in_lua;
case 1:return(void*)&p->last_msg;
case 2:return(void*)&p->parse_config_file_src;
case 3:return(void*)&p->window_inited;
default:abort();}}
case 5:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->catname;
case 1:return(void*)&p->cmdline_rcfile;
case 2:return(void*)&p->config_section_chosen;
case 3:return(void*)&p->config_section_current;
default:abort();}}
case 6:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->dogname;
case 1:return(void*)&p->deferred_showpaths;
default:abort();}}
case 7:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->no_sound_notified;
default:abort();}}
case 8:{struct instance_globals_o*p=at;switch(field){
case 0:return(void*)&p->ov_primary_syms;
case 1:return(void*)&p->opt_phase;
default:abort();}}
case 9:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(void*)&p->plname;
default:abort();}}
case 10:{struct instance_globals_w*p=at;switch(field){
case 0:return(void*)&p->wizkit;
default:abort();}}
case 11:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->config_error_ready;
default:abort();}}
case 12:{struct strbuf*p=at;switch(field){
case 0:return(void*)&p->str;
default:abort();}}
case 13:{struct sysopt_s*p=at;switch(field){
case 0:return(void*)&p->support;
case 1:return(void*)&p->recover;
case 2:return(void*)&p->wizards;
case 3:return(void*)&p->fmtd_wizard_list;
case 4:return(void*)&p->explorers;
case 5:return(void*)&p->shellers;
case 6:return(void*)&p->genericusers;
case 7:return(void*)&p->debugfiles;
case 8:return(void*)&p->msghandler;
case 9:return(void*)&p->env_dbgfl;
case 10:return(void*)&p->maxplayers;
case 11:return(void*)&p->seduce;
case 12:return(void*)&p->check_save_uid;
case 13:return(void*)&p->check_plname;
case 14:return(void*)&p->bones_pools;
case 15:return(void*)&p->livelog;
case 16:return(void*)&p->persmax;
case 17:return(void*)&p->pers_is_uid;
case 18:return(void*)&p->entrymax;
case 19:return(void*)&p->pointsmin;
case 20:return(void*)&p->tt_oname_maxrank;
case 21:return(void*)&p->gdbpath;
case 22:return(void*)&p->greppath;
case 23:return(void*)&p->crashreporturl;
case 24:return(void*)&p->panictrace_gdb;
case 25:return(void*)&p->panictrace_libc;
case 26:return(void*)&p->accessibility;
case 27:return(void*)&p->hideusage;
default:abort();}}
case 14:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_wait_synch;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
void teleport_cfgfiles_var0(char * a0){(pline)(a0);}
void teleport_cfgfiles_var1(char * a0){(pline)(a0);}
void teleport_cfgfiles_var2(char * a0){(pline)(a0);}
void teleport_cfgfiles_var3(char * a0){(pline)(a0);}
int teleport_cfgfiles_var4(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_cfgfiles_var5(char * a0,unsigned long a1,unsigned long a2){(pline)(a0,a1,a2);}
void teleport_cfgfiles_var6(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_cfgfiles_var7(char * a0,char * a1,int a2){(raw_printf)(a0,a1,a2);}
void teleport_cfgfiles_var8(char * a0,char * a1,int a2){(raw_printf)(a0,a1,a2);}
int teleport_cfgfiles_var9(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_cfgfiles_var10(char * a0,char * a1,char * a2,int a3){(raw_printf)(a0,a1,a2,a3);}
void teleport_cfgfiles_var11(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_cfgfiles_var12(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_cfgfiles_var13(char * a0,char * a1){(pline)(a0,a1);}
void teleport_cfgfiles_var14(char * a0){(pline)(a0);}
void teleport_cfgfiles_var15(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var16(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var17(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var18(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var19(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var20(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var21(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var22(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var23(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var24(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var25(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var26(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var27(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var28(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_cfgfiles_var29(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_cfgfiles_var30(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var31(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var32(char * a0,char * a1,char * a2,char * a3){(pline)(a0,a1,a2,a3);}
void teleport_cfgfiles_var33(char * a0,char * a1){(pline)(a0,a1);}
int teleport_cfgfiles_var34(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_cfgfiles_var35(char * a0,char * a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_cfgfiles_var36(char * a0,int a1,char * a2,char * a3,char * a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_cfgfiles_var37(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var38(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var39(char * a0){(config_error_add)(a0);}
void teleport_cfgfiles_var40(char * a0,char * a1){(config_error_add)(a0,a1);}
int teleport_cfgfiles_var41(char * a0,int a1){return (open)(a0,a1);}
void teleport_cfgfiles_var42(char * a0){(raw_printf)(a0);}
#pragma clang diagnostic pop
void teleport_cfgfiles_free(void*p){(free)(p);}
boolean teleport_cfgfiles_call_proc(boolean(*fn)(char*),char*arg){return fn(arg);}
void teleport_cfgfiles_call_void(void(*fn)(void)){fn();}
boolean(*teleport_cfgfiles_parse_pointer(void))(char*){return parse_config_line;}
#include "cfgfiles-source-data.h"
static char cfgfiles_literals[CFGFILES_LITERAL_CAPACITY];
char*teleport_cfgfiles_literal_storage(void){return cfgfiles_literals;}
size_t teleport_cfgfiles_literal_capacity(void){return sizeof cfgfiles_literals;}
