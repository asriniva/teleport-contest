#ifndef TELEPORT_CFGFILES_LAYOUT_H
#define TELEPORT_CFGFILES_LAYOUT_H
#include "../nethack-c/wasm/tu-fragments/cfgfiles-types.h"
#include <stddef.h>
#include <errno.h>
struct cfgfiles_meta {const char*name;uint64_t value;};
#define CFG_META(n,v) {n,(uint64_t)(v)}
static const struct cfgfiles_meta cfgfiles_layout[]={
CFG_META("EIO",EIO),CFG_META("pointerSize",sizeof(void*)),CFG_META("longSize",sizeof(long)),CFG_META("vaListSize",sizeof(va_list)),CFG_META("intSize",sizeof(int)),CFG_META("charSigned",(char)-1<0),CFG_META("littleEndian",__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__),
CFG_META("size:struct _cnf_parser_state",sizeof(struct _cnf_parser_state)),
CFG_META("size:struct _config_error_errmsg",sizeof(struct _config_error_errmsg)),
CFG_META("size:struct _config_error_frame",sizeof(struct _config_error_frame)),
CFG_META("size:struct flag",sizeof(struct flag)),
CFG_META("size:struct instance_flags",sizeof(struct instance_flags)),
CFG_META("size:struct instance_globals_c",sizeof(struct instance_globals_c)),
CFG_META("size:struct instance_globals_d",sizeof(struct instance_globals_d)),
CFG_META("size:struct instance_globals_n",sizeof(struct instance_globals_n)),
CFG_META("size:struct instance_globals_o",sizeof(struct instance_globals_o)),
CFG_META("size:struct instance_globals_saved_p",sizeof(struct instance_globals_saved_p)),
CFG_META("size:struct instance_globals_w",sizeof(struct instance_globals_w)),
CFG_META("size:struct match_config_line_stmt",sizeof(struct match_config_line_stmt)),
CFG_META("size:struct sinfo",sizeof(struct sinfo)),
CFG_META("size:struct strbuf",sizeof(struct strbuf)),
CFG_META("size:struct sysopt_s",sizeof(struct sysopt_s)),
CFG_META("size:struct window_procs",sizeof(struct window_procs)),
CFG_META("MAXMCLASSES",MAXMCLASSES),
CFG_META("MAXOCLASSES",MAXOCLASSES),
CFG_META("MAXPCHARS",MAXPCHARS),
CFG_META("PRIMARYSET",PRIMARYSET),
CFG_META("ROGUESET",ROGUESET),
CFG_META("SYM_BOULDER",SYM_BOULDER),
CFG_META("environ_opt",environ_opt),
CFG_META("opt_soundlib",opt_soundlib),
CFG_META("opt_windowtype",opt_windowtype),
CFG_META("rc_file_opt",rc_file_opt),
CFG_META("set_in_config",set_in_config),
CFG_META("set_in_sysconf",set_in_sysconf),
};
#undef CFG_META
#endif
