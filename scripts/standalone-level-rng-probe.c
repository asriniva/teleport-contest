/* Include RND before hack.h so its original logging-macro guard applies. */
#include "rnd.c"
extern void probe_startup_init(unsigned long);
void probe_level_init(unsigned long seed){probe_startup_init(seed);init_isaac64(seed,(rn2_on_display_rng));}
void *probe_level_rng_pointer(int which){return which?(void*)(rn2_on_display_rng):(void*)(rn2);}
void probe_level_reseed(int which){reseed_random(which?(rn2_on_display_rng):(rn2));}
const void *probe_level_rng_state(int which){return &rnglist[which].rng_state;}
int probe_level_rng_initialized(int which){return rnglist[which].init;}
unsigned long probe_level_rng_layout(int op){const unsigned long values[]={sizeof(isaac64_ctx),offsetof(isaac64_ctx,n),offsetof(isaac64_ctx,r),offsetof(isaac64_ctx,m),offsetof(isaac64_ctx,a),offsetof(isaac64_ctx,b),offsetof(isaac64_ctx,c)};return values[op];}
