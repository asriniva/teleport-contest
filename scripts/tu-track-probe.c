#include "hack.h"
#include "../nethack-c/wasm/tu-support.h"
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

struct you u;
struct obj *uleft, *uright;
static struct obj left_obj, right_obj;
static NHFILE file;
static unsigned char stream[8192];
static size_t stream_len, stream_pos;
static char trace[8192], panic_message[256];
static jmp_buf panic_jump;
static int panic_guard;

/* Isolated serializer dependency: record exact ordered types/tags/bytes for
 * original-C and hybrid calls. The game keeps its actual C serializers. */
static void transfer(void *pointer, size_t size, const char *type,
                     const char *tag, int reading)
{
    size_t used = strlen(trace);
    snprintf(trace + used, sizeof(trace) - used, "%s:%s:%s;", reading ? "in" : "out", type, tag);
    if (reading) {
        if (stream_pos + size > stream_len) abort();
        memcpy(pointer, stream + stream_pos, size);
        stream_pos += size;
    } else {
        if (stream_len + size > sizeof stream) abort();
        memcpy(stream + stream_len, pointer, size);
        stream_len += size;
    }
}
void sfo_int(NHFILE *fp, int *p, const char *tag) { transfer(p, sizeof *p, "int", tag, 0); }
void sfi_int(NHFILE *fp, int *p, const char *tag) { transfer(p, sizeof *p, "int", tag, 1); }
void sfo_nhcoord(NHFILE *fp, coord *p, const char *tag) { transfer(p, sizeof *p, "coord", tag, 0); }
void sfi_nhcoord(NHFILE *fp, coord *p, const char *tag) { transfer(p, sizeof *p, "coord", tag, 1); }
void panic(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(panic_message, sizeof panic_message, format, args);
    va_end(args);
    if (!panic_guard) abort();
    longjmp(panic_jump, 1);
}

#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/track.c"
#endif

size_t probe_context_size(void) { return sizeof(struct teleport_track_state); }
size_t probe_offset_utcnt(void) { return offsetof(struct teleport_track_state, utcnt); }
size_t probe_offset_utpnt(void) { return offsetof(struct teleport_track_state, utpnt); }
size_t probe_offset_utrack(void) { return offsetof(struct teleport_track_state, utrack); }
size_t probe_offset_x(void) { return offsetof(coord, x); }
size_t probe_offset_y(void) { return offsetof(coord, y); }
size_t probe_offset_ux(void) { return offsetof(struct you, ux); }
size_t probe_offset_uy(void) { return offsetof(struct you, uy); }
size_t probe_offset_otyp(void) { return offsetof(struct obj, otyp); }
int probe_coord_size(void) { return sizeof(coord); }
int probe_coordxy_size(void) { return sizeof(coordxy); }
int probe_int_size(void) { return sizeof(int); }
int probe_otyp_size(void) { return sizeof(left_obj.otyp); }
int probe_utsz(void) { return TELEPORT_TRACK_UTSZ; }
int probe_stealth(void) { return RIN_STEALTH; }
int probe_writing(void) { return WRITING; }
int probe_freeing(void) { return FREEING; }
int probe_counting(void) { return COUNTING; }
void probe_init(void) { initrack(); }
void probe_hero(coordxy x, coordxy y, int left, int right)
{
    u.ux = x; u.uy = y;
    left_obj.otyp = left; right_obj.otyp = right;
    uleft = left < 0 ? NULL : &left_obj;
    uright = right < 0 ? NULL : &right_obj;
}
void probe_set(void) { settrack(); }
coord *probe_get(coordxy x, coordxy y) { return gettrack(x, y); }
boolean probe_has(coordxy x, coordxy y) { return hastrack(x, y); }
void probe_save(int mode)
{
    file.mode = mode;
    stream_len = stream_pos = 0;
    trace[0] = '\0';
    save_track(&file);
}
int probe_rest(void)
{
    file.mode = 0;
    stream_pos = 0;
    trace[0] = panic_message[0] = '\0';
    panic_guard = 1;
    if (setjmp(panic_jump)) { panic_guard = 0; return -1; }
    rest_track(&file);
    panic_guard = 0;
    return 0;
}
void probe_corrupt_counts(int count, int point)
{
    memcpy(stream, &count, sizeof count);
    memcpy(stream + sizeof count, &point, sizeof point);
    if (stream_len < 2 * sizeof(int)) stream_len = 2 * sizeof(int);
}
const unsigned char *probe_stream(void) { return stream; }
size_t probe_stream_size(void) { return stream_len; }
const char *probe_trace(void) { return trace; }
const char *probe_panic_message(void) { return panic_message; }
int probe_count(void) {
#ifdef TELEPORT_REFERENCE_TU
    return utcnt;
#else
    return ((struct teleport_track_state *) teleport_track_state_pointer())->utcnt;
#endif
}
int probe_point(void) {
#ifdef TELEPORT_REFERENCE_TU
    return utpnt;
#else
    return ((struct teleport_track_state *) teleport_track_state_pointer())->utpnt;
#endif
}
coord *probe_data(void) {
#ifdef TELEPORT_REFERENCE_TU
    return utrack;
#else
    return ((struct teleport_track_state *) teleport_track_state_pointer())->utrack;
#endif
}
