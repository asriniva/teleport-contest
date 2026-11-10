/* Development-only native oracle for the JS-owned service provider.
 * Link the original strutil/alloc/isaac64/nhmd4 C, not copied algorithms.
 * Input/output uses hex to retain byte strings and embedded NULs.
 */
#include "hack.h"
#include "isaac64.h"
#include "nhmd4.h"
#include <errno.h>
#include <inttypes.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef malloc
#undef realloc
extern void *malloc(size_t);
extern void *realloc(void *, size_t);
static int fail_malloc, fail_realloc, panic_guard;
static jmp_buf panic_jump;
static char panic_text[256];
void *js_probe_malloc(size_t size) { if (fail_malloc) { fail_malloc = 0; return NULL; } return malloc(size); }
void *js_probe_realloc(void *pointer, size_t size) { if (fail_realloc) { fail_realloc = 0; return NULL; } return realloc(pointer,size); }
void panic(const char *format, ...) {
    va_list ap; va_start(ap, format); vsnprintf(panic_text,sizeof panic_text,format,ap); va_end(ap);
    if (panic_guard) longjmp(panic_jump,1);
    fputs(panic_text,stderr); exit(97);
}
/* The source's ASCII lowc helper is the only hacklib dependency of strutil. */
char lowc(char c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; }
static unsigned char *unhex(const char *text, size_t *length) {
    *length = !text || !strcmp(text, "-") ? 0 : strlen(text) / 2;
    unsigned char *bytes = calloc(*length + 1, 1);
    for (size_t i = 0; i < *length; i++) {
        unsigned value; if (sscanf(text + i * 2, "%2x", &value) != 1) exit(98);
        bytes[i] = (unsigned char)value;
    }
    return bytes;
}
static void hex(const void *data, size_t length) {
    const unsigned char *bytes = data;
    for (size_t i = 0; i < length; i++) printf("%02x", bytes[i]);
}
int main(void) {
    char *line = NULL; size_t capacity = 0;
    strbuf_t buffer; memset(&buffer, 0, sizeof buffer); strbuf_init(&buffer);
    while (getline(&line, &capacity, stdin) >= 0) {
        char *op = strtok(line, " \r\n"), *a = strtok(NULL, " \r\n"), *b = strtok(NULL, " \r\n"), *c = strtok(NULL, " \r\n");
        if (!op) continue;
        size_t n = 0, m = 0; unsigned char *x = NULL, *y = NULL;
        if (*op == 'L') {
            printf("%zu,%zu,%zu,%zu,%zu,%d,%zu,%zu\n", sizeof(strbuf_t), offsetof(strbuf_t,len),
                   offsetof(strbuf_t,str), offsetof(strbuf_t,buf), sizeof buffer.buf,
                   LARGEST_INT, sizeof(isaac64_ctx), sizeof(NHMD4_CTX));
        } else if (*op == 'P') {
            x = unhex(b, &n); y = unhex(c, &m);
            printf("%d\n", atoi(a) ? pmatchi((char *)x,(char *)y) : pmatch((char *)x,(char *)y));
        } else if (*op == 'A' || *op == 'N' || *op == 'R' || *op == 'E') {
            if (*op == 'A') { x = unhex(a, &n); strbuf_append(&buffer, (char *)x); }
            if (*op == 'N') strbuf_nl_to_crlf(&buffer);
            if (*op == 'R') strbuf_reserve(&buffer, atoi(a));
            if (*op == 'E') strbuf_empty(&buffer);
            printf("%d,%d,", buffer.len, !buffer.str ? 0 : buffer.str == buffer.buf ? 1 : 2);
            if (buffer.str) hex(buffer.str, strlen(buffer.str));
            puts("");
        } else if (*op == 'D') {
            x = unhex(a, &n); size_t chunk = strtoul(b,NULL,10); if (!chunk) chunk = n ? n : 1;
            NHMD4_CTX context; memset(&context, 0, sizeof context); unsigned char digest[16];
            nhmd4_init(&context);
            for (size_t at = 0; at < n; at += chunk) nhmd4_update(&context,x+at,n-at<chunk?n-at:chunk);
            nhmd4_final(&context,digest); hex(digest,sizeof digest); putchar(','); hex(&context,sizeof context); puts("");
        } else if (*op == 'I') {
            x = unhex(a, &n); isaac64_ctx context; memset(&context,0,sizeof context);
            isaac64_init(&context,x,(int)n);
            for (int i = 0; i < atoi(b); i++) printf("%s%" PRIu64, i ? "," : "", isaac64_next_uint64(&context));
            putchar(';'); hex(&context,sizeof context); puts("");
        } else if (*op == 'T') {
            x = unhex(c,&n); char *end; errno = 0;
            if (atoi(b)) { unsigned long long v = strtoull((char *)x,&end,atoi(a)); printf("%llu",v); }
            else { long long v = strtoll((char *)x,&end,atoi(a)); printf("%lld",v); }
            printf(",%td,%s\n",end-(char *)x,errno == EINVAL ? "EINVAL" : errno == ERANGE ? "ERANGE" : errno == 0 ? "0" : "OTHER");
        } else if (*op == 'O') {
            int kind = atoi(a); char *retained = malloc(8); memcpy(retained,"retained",8);
            panic_guard = 1; panic_text[0] = 0;
            if (!setjmp(panic_jump)) {
                if (kind == 0) { fail_malloc = 1; (void)alloc(1025); }
                else if (kind == 1) { fail_realloc = 1; (void)re_alloc((long *)retained,1025); }
                else if (kind == 2) (void)FITSint_(2147483648LL,"runtime-test.c",12);
                else (void)FITSuint_(4294967296ULL,"runtime-test.c",12);
            }
            panic_guard = fail_malloc = fail_realloc = 0;
            hex(panic_text,strlen(panic_text)); puts(""); free(retained);
        } else if (*op == 'F') {
            int value = atoi(a); char output[128];
            snprintf(output,sizeof output,"%+08d|%#x|%#o|%.0d|%8.4d",value,(unsigned)value,(unsigned)value,0,value);
            hex(output,strlen(output)); puts("");
        } else return 99;
        free(x); free(y);
    }
    strbuf_empty(&buffer); free(line);
    return 0;
}
