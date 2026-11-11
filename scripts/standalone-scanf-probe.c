#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
union slot { long long ll; long l; int i; short h; signed char c; unsigned char bytes[128]; void *p; };
static union slot slots[16];
static unsigned char line[128];
FILE *scanf_open(int mode) { return mode == 2 ? stdin : fopen("/scanf-input", mode == 1 ? "w" : "r"); }
int scanf_close(FILE *f) { return f == stdin ? 0 : fclose(f); }
void scanf_break_fd(FILE *f) { close(fileno(f)); }
int scanf_run(FILE *f, const char *format, int sentinel) {
    memset(slots, 0xa5, sizeof slots); errno = sentinel;
    return fscanf(f, format, (void *)&slots[0], (void *)&slots[1], (void *)&slots[2], (void *)&slots[3],
                  (void *)&slots[4], (void *)&slots[5], (void *)&slots[6], (void *)&slots[7],
                  (void *)&slots[8], (void *)&slots[9], (void *)&slots[10], (void *)&slots[11], (void *)&slots[12], (void *)&slots[13], (void *)&slots[14], (void *)&slots[15]);
}
int scanf_string(const char *input, const char *format, int sentinel) {
    memset(slots, 0xa5, sizeof slots); errno = sentinel;
    return sscanf(input, format, (void *)&slots[0], (void *)&slots[1], (void *)&slots[2], (void *)&slots[3],
                  (void *)&slots[4], (void *)&slots[5], (void *)&slots[6], (void *)&slots[7],
                  (void *)&slots[8], (void *)&slots[9], (void *)&slots[10], (void *)&slots[11], (void *)&slots[12], (void *)&slots[13], (void *)&slots[14], (void *)&slots[15]);
}
int scanf_errno(void) { return errno; }
uintptr_t scanf_outputs(void) { return (uintptr_t)slots; }
int scanf_getc(FILE *f) { return fgetc(f); }
int scanf_unget(FILE *f, int c) { return ungetc(c, f); }
int scanf_flags(FILE *f) { return !!feof(f) | (!!ferror(f) << 1); }
long scanf_position(FILE *f) { return ftell(f); }
int scanf_getline(FILE *f, int n) { memset(line, 0xa5, sizeof line); return fgets((char *)line, n, f) != NULL; }
uintptr_t scanf_line(void) { return (uintptr_t)line; }
long scanf_constant(int i) { switch(i) { case 0:return EINVAL;case 1:return ERANGE;case 2:return sizeof(long);case 3:return sizeof(void *);case 4:return EOF;case 5:return sizeof(union slot);default:return -1; } }
