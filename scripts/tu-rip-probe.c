#include "hack.h"
#include <stddef.h>
#include <stdlib.h>
#include <emscripten/stack.h>

__typeof__(gr) gr;
__typeof__(gd) gd;
__typeof__(svp) svp;
__typeof__(windowprocs) windowprocs;
static char killer_text[BUFSZ];
static long fixture_date;
static time_t date_argument;
static int killer_how, killer_format, killer_calls, date_calls;
static unsigned killer_size;
struct output_line { winid window; int attribute, dump, live; char text[BUFSZ]; };
static struct output_line output[64];
static int line_count;
void panic(const char *format, ...) { abort(); }

/* External death wording/date/window dependencies are controlled identically
 * for both builds. Production keeps actual formatkiller/calendar/window code. */
void formatkiller(char *buffer, unsigned size, int how, boolean format)
{
    killer_how = how; killer_format = format; killer_size = size; killer_calls++;
    if (size) { strncpy(buffer, killer_text, size - 1); buffer[size - 1] = '\0'; }
}
long yyyymmdd(time_t when)
{
    date_argument = when; date_calls++; return fixture_date;
}
static void capture(winid window, int attribute, const char *text, int dump)
{
    struct output_line *line;
    if (line_count >= SIZE(output)) abort();
    line = &output[line_count++];
    line->window = window; line->attribute = attribute; line->dump = dump;
    line->live = gr.rip != NULL;
    strncpy(line->text, text, sizeof(line->text) - 1);
    line->text[sizeof(line->text) - 1] = '\0';
}
static void capture_putstr(winid window, int attribute, const char *text)
{
    capture(window, attribute, text, 0);
}
#ifdef DUMPLOG
void dump_forward_putstr(winid window, int attribute, const char *text, int no_forward)
{
    capture(window, attribute, text, no_forward ? 1 : 2);
}
#endif
size_t probe_context_size(void) { return sizeof(char *); }
int probe_bufsz(void) { return BUFSZ; }
int probe_plname_size(void) { return sizeof(svp.plname); }
int probe_long_size(void) { return sizeof(long); }
int probe_time_size(void) { return sizeof(time_t); }
int probe_dumplog(void) {
#ifdef DUMPLOG
    return 1;
#else
    return 0;
#endif
}
int probe_dedication(void) {
#ifdef NH320_DEDICATION
    return 1;
#else
    return 0;
#endif
}
void probe_inputs(const char *name, long money, const char *death, long date)
{
    strncpy(svp.plname, name, sizeof(svp.plname) - 1);
    svp.plname[sizeof(svp.plname) - 1] = '\0';
    gd.done_money = money;
    strncpy(killer_text, death, sizeof(killer_text) - 1);
    killer_text[sizeof(killer_text) - 1] = '\0';
    fixture_date = date;
}
void probe_run(int window, int how, time_t when)
{
    line_count = killer_calls = date_calls = 0;
    windowprocs.win_putstr = capture_putstr;
    genl_outrip(window, how, when);
}
char **probe_head(void) { return gr.rip; }
int probe_line_count(void) { return line_count; }
int probe_line_window(int index) { return output[index].window; }
int probe_line_attribute(int index) { return output[index].attribute; }
int probe_line_dump(int index) { return output[index].dump; }
int probe_line_live(int index) { return output[index].live; }
const char *probe_line_text(int index) { return output[index].text; }
int probe_killer_how(void) { return killer_how; }
int probe_killer_format(void) { return killer_format; }
int probe_killer_calls(void) { return killer_calls; }
unsigned probe_killer_size(void) { return killer_size; }
int probe_date_calls(void) { return date_calls; }
time_t probe_date_argument(void) { return date_argument; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
