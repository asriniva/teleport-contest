int teleport_compress_file(const char *, const char *, int);
#ifdef __EMSCRIPTEN__
int codec_run(int unpack) {
    return teleport_compress_file("/plain", "/plain.Z", unpack);
}
#else
#include <stdlib.h>
int main(int argc, char **argv) {
    if (argc != 4) return 99;
    return teleport_compress_file(argv[2], argv[3], atoi(argv[1]));
}
#endif
