#include <stdio.h>
#include <emscripten.h>
#include <stdint.h>
_Static_assert(sizeof(void *) == 8, "wasm64 pointers required");
_Static_assert(sizeof(long) == 8, "LP64 required for recorder parity");
EM_JS(int, teleport_getch, (void), {
    return Module.teleportReadKey();
});
EM_JS(void, teleport_capture, (const char *screen, int x, int y, int animation), {
    Module.teleportCapture(UTF8ToString(Number(screen)), x, y, animation);
});

/* macOS game features include the paste-buffer command. The Wasm build
 * stores its value in the module rather than launching /usr/bin/pbcopy. */
EM_JS(void, port_insert_pastebuf, (char *text), {
    var value = UTF8ToString(Number(text));
    Module.teleportClipboard = value.charCodeAt(value.length - 1) == 10
        ? value.slice(0, -1) : value;
});
