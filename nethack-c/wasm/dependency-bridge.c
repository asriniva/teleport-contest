/* ABI-only bridge for the experimental JS dependency build. NetHack's tty
 * source and ncurses headers are unchanged. Its tparm calls use numeric
 * parameters; fetch their wasm64 vararg slots into an explicit long array. */
#include <stdarg.h>
#include <stddef.h>

short ospeed;
char PC;
char *BC;
char *UP;

extern char *teleport_js_tparm(const char *, const long *);

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
