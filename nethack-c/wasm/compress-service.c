/* In-process Unix .Z service. NetHack owns file deletion and user prompts. */
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static jmp_buf codec_failure;
static _Noreturn void codec_exit(int status) {
    longjmp(codec_failure, status ? status : 1);
}

/* Keep the pinned source untouched. Its CLI is unused; codec errors return to
 * this service rather than terminating the game. stdlib is included above so
 * the exit macro cannot alter its declaration. */
#define main ncompress_cli_main
#define compress ncompress_encode
#define decompress ncompress_decode
#define exit codec_exit
#define UTIME_H
#include "vendor/ncompress/compress.c"
#undef exit
#undef main
#undef compress
#undef decompress

int teleport_compress_file(const char *filename, const char *compressed, int unpack) {
    const char *source = unpack ? compressed : filename;
    const char *destination = unpack ? filename : compressed;
    int input = open(source, O_RDONLY);
    if (input < 0) { perror(source); return 1; }
    int output = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (output < 0) { perror(destination); close(input); return 1; }

    // ncompress's CLI normally initializes this process-global state once.
    // Reset it for each library call, including compression after decompression.
    progname = "compress";
    ifname = (char *)source;
    ofname = (char *)destination;
    remove_ofname = 0;
    exit_code = 0;
    maxbits = BITS;
    quiet = 1;
    silent = 0;
    nomagic = 0;
    force = 0;
    bytes_in = bytes_out = 0;

    int status = setjmp(codec_failure);
    if (!status) {
        if (unpack) {
            unsigned char header[5];
            ssize_t length = read(input, header, sizeof header);
            if (length != 5 || header[0] != 0x1f || header[1] != 0x9d
                || (header[2] & 0x1f) < 9 || (header[2] & 0x1f) > BITS
                || lseek(input, 0, SEEK_SET) < 0) {
                fprintf(stderr, "%s: invalid or incomplete .Z header\n", source);
                status = 1;
            } else {
                ncompress_decode(input, output);
                status = exit_code;
            }
        } else {
            ncompress_encode(input, output);
            status = bytes_out >= bytes_in ? 2 : exit_code;
        }
    }
    if (close(input) < 0 && !status) status = 1;
    if (close(output) < 0 && !status) status = 1;
    return status;
}
