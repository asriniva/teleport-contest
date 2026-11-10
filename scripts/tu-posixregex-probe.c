#include "hack.h"
#include "nhregex.h"
#include <stdlib.h>
#include <emscripten/stack.h>

void panic(const char *format, ...) { abort(); }
#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/sys/share/posixregex.c"
#endif
#include "tu-posixregex-layout.h"

extern const char regex_id[];
const char *probe_identifier(void) { return regex_id; }
struct nhregex *probe_init(void) { return regex_init(); }
int probe_compile(const char *pattern, struct nhregex *regex) { return regex_compile(pattern, regex); }
int probe_match(const char *text, struct nhregex *regex) { return regex_match(text, regex); }
char *probe_error(struct nhregex *regex, char *buffer) { return regex_error_desc(regex, buffer); }
int probe_err(struct nhregex *regex) { return regex->err; }
void probe_set_err(struct nhregex *regex, int err) { regex->err = err; }
void probe_free(struct nhregex *regex) { regex_free(regex); }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
