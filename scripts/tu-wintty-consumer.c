/* Test-only optimized external consumer: observe the actual native catalogue
 * before the first window-port function, including its full byte layout. */
#include "hack.h"
#include "wintty.h"
#include <stdint.h>
static struct window_procs startup_catalogue;
__attribute__((constructor)) static void capture_wintty_catalogue(void)
{
    memcpy(&startup_catalogue, &tty_procs, sizeof startup_catalogue);
}
const void *probe_startup_catalogue(void) { return &startup_catalogue; }
void *probe_live_catalogue(void) { return &tty_procs; }
void probe_mutate_catalogue(int which, unsigned long value)
{
    if (which == 0)
        tty_procs.wincap2 = value;
    else if (which == 1)
        tty_procs.has_color[0] = (boolean) value;
}
void probe_more(const char *s) { strncpy(defmorestr, s, 8); defmorestr[8] = 0; }
