#ifndef TELEPORT_CFGFILES_TYPES_H
#define TELEPORT_CFGFILES_TYPES_H
#include "hack.h"
typedef boolean (*config_line_stmt_func)(char*);
struct match_config_line_stmt {
    const char *name;
    int len;
    boolean syscnf_only;
    boolean origbuf;
    config_line_stmt_func fn;
};
struct _config_error_errmsg {
    int line_num;
    char *errormsg;
    struct _config_error_errmsg *next;
};
struct _config_error_frame {
    int line_num;
    int num_errors;
    boolean origline_shown;
    boolean fromfile;
    boolean secure;
    char origline[4 * BUFSZ];
    char source[BUFSZ];
    struct _config_error_frame *next;
};
struct _cnf_parser_state {
    char *inbuf;
    unsigned inbufsz;
    int rv;
    char *ep;
    char *buf;
    boolean skip, morelines;
    boolean cont;
    boolean pbreak;
};
#endif
