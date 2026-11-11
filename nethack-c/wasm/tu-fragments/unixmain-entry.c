/* ABI-only entry shell: Emscripten emits callMain only for a wasm main export.
 * Every original unixmain.c statement and policy remains in JS. */
extern int teleport_unixmain_main(int argc, char **argv);
int main(int argc, char **argv) { return teleport_unixmain_main(argc, argv); }
