/* Compare the actual terminfo APIs used by NetHack, native versus wasm64. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <term.h>

static void emit(const char *label, const char *s) {
    printf("%s=", label);
    if (!s) printf("NULL");
    else for (; *s; ++s) printf("%02x", (unsigned char)*s);
    puts("");
}
static int emit_hex(int c) { printf("%02x", (unsigned char)c); return c; }
int main(void) {
    char buf[4096];
    if (tgetent(buf, "xterm-256color") != 1) return 1;
    const char *strings[] = {"pc", "le", "ho", "nd", "ce", "up", "xd", "cm",
        "so", "se", "us", "ue", "ZH", "ZR", "ti", "te", "eA", "ks", "ke",
        "mr", "mb", "md", "mh", "me", "vi", "ve", "Ic", "as", "ae", "cd",
        "cl", "AF", "Sf", NULL};
    for (int i = 0; strings[i]; ++i) emit(strings[i], tgetstr((char *)strings[i], NULL));
    const char *numbers[] = {"co", "li", "sg", "Co", NULL};
    for (int i = 0; numbers[i]; ++i) printf("%s=%d\n", numbers[i], tgetnum((char *)numbers[i]));
    printf("os=%d\nul=%d\n", tgetflag("os"), tgetflag("ul"));
    char label[64];
    for (int color = 0; color < 256; ++color) {
        snprintf(label, sizeof label, "color-%d", color);
        /* NetHack passes int, not long, to this varargs API. Test that ABI. */
        emit(label, tparm(tgetstr("AF", NULL), color));
    }
    for (int row = 0; row < 24; ++row) {
        snprintf(label, sizeof label, "cursor-%d", row);
        emit(label, tgoto(tgetstr("cm", NULL), row * 3, row));
    }
    emit("rgb", tparm(tgetstr("Ic", NULL), 15L, 120L, 340L, 560L));
    printf("tputs="); tputs(tgetstr("cl", NULL), 24, emit_hex); puts("");
    /* Unknown terminals must fail, never silently fall back to ANSI. */
    printf("unknown=%d\n", tgetent(buf, "teleport-no-such-terminal"));
    return 0;
}
