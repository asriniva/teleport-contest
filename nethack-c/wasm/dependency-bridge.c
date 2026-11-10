/* ABI-only bridge for the experimental JS dependency build. NetHack's tty
 * source and ncurses headers are unchanged. Its tparm calls use numeric
 * parameters; fetch their wasm64 vararg slots into an explicit long array. */
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

short ospeed;
char PC;
char *BC;
char *UP;

extern char *teleport_js_tparm(const char *, const long *);
extern const char *teleport_js_tputs(const char *, int);

/* Process capability/padding syntax in JS once, then retain an independent
 * byte buffer while C callbacks run. Callbacks may reenter tputs/tparm or
 * grow linear memory; numeric C pointers remain valid across memory growth.
 * ncurses ignores callback return values and returns OK for a valid string. */
int tputs(const char *value, int lines, int (*outc)(int))
{
    const char *prepared = teleport_js_tputs(value, lines);
    if (!prepared) return -1;
    size_t length = strlen(prepared);
    char *stable = malloc(length + 1);
    if (!stable) return -1;
    memcpy(stable, prepared, length + 1);
    for (size_t i = 0; i < length; ++i) (void) outc(stable[i]);
    free(stable);
    return 0;
}

char *tparm(const char *format, ...)
{
    long parameters[9] = {0};
    int count = 0, implicit = 0;
    const char *p;
    va_list arguments;
    if (!format) return NULL;
    for (p = format; *p; ++p) {
        if (*p != '%' || !*++p) continue;
        if (*p == '%') continue;
        if (*p == 'p' && p[1] >= '1' && p[1] <= '9') {
            int parameter = *++p - '0';
            if (parameter > count) count = parameter;
        } else if (*p == '\'' && p[1] && p[2] == '\'') {
            p += 2;
        } else if (*p == '{') {
            while (p[1] && p[1] != '}') ++p;
            if (p[1]) ++p;
        } else if (*p == 'P' || *p == 'g') {
            if (p[1]) ++p;
        } else if (*p == 'd' || *p == 'o' || *p == 'x'
                   || *p == 'X' || *p == 'c' || *p == 's') {
            ++implicit;
        }
    }
    if (!count) count = implicit > 9 ? 9 : implicit;
    va_start(arguments, format);
    for (int i = 0; i < count; ++i) parameters[i] = va_arg(arguments, long);
    va_end(arguments);
    return teleport_js_tparm(format, parameters);
}

#ifdef TELEPORT_JS_REGEX
/* Strong ABI forwarders prevent libc.a from supplying the TRE algorithms.
 * The regex_t layout and the caller's nhregex error field remain unchanged. */
#include <regex.h>
extern int teleport_js_regcomp(regex_t *, const char *, int);
extern int teleport_js_regexec(const regex_t *, const char *, size_t, regmatch_t *, int);
extern size_t teleport_js_regerror(int, const regex_t *, char *, size_t);
extern void teleport_js_regfree(regex_t *);
int regcomp(regex_t *restrict re, const char *restrict pattern, int flags)
{ return teleport_js_regcomp(re, pattern, flags); }
int regexec(const regex_t *restrict re, const char *restrict text, size_t count,
            regmatch_t *restrict matches, int flags)
{ return teleport_js_regexec(re, text, count, matches, flags); }
size_t regerror(int code, const regex_t *restrict re, char *restrict output, size_t size)
{ return teleport_js_regerror(code, re, output, size); }
void regfree(regex_t *re) { teleport_js_regfree(re); }
#endif
