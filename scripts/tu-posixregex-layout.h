#include "hack.h"
#include <regex.h>
#include <stddef.h>

/* The reference probe includes the original TU before this metadata header. */
#ifndef TELEPORT_REFERENCE_TU
struct nhregex {
    regex_t re;
    int err;
};
#endif

static const struct {
    const char *name;
    size_t value;
} posixregex_layout[] = {
    { "NhregexSize", sizeof(struct nhregex) },
    { "re", offsetof(struct nhregex, re) },
    { "err", offsetof(struct nhregex, err) },
    { "regexSize", sizeof(regex_t) },
    { "intSize", sizeof(int) },
    { "pointerSize", sizeof(void *) },
    { "BUFSZ", BUFSZ },
    { "REG_EXTENDED", REG_EXTENDED },
    { "REG_NOSUB", REG_NOSUB },
    { "REG_NOMATCH", REG_NOMATCH },
    { "identifierSize", sizeof "posixregex" },
    { "boolSize", sizeof(boolean) },
    { "boolSigned", (boolean) -1 < 0 },
};

size_t probe_context_size(void) { return sizeof(struct nhregex); }
int probe_layout_count(void)
{
    return sizeof posixregex_layout / sizeof posixregex_layout[0];
}
const char *probe_layout_name(int index) { return posixregex_layout[index].name; }
size_t probe_layout_value(int index) { return posixregex_layout[index].value; }
