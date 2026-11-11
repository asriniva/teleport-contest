/* Original configured sound owner, without any source storage replacement. */
#include "sounds.c"
const void *probe_status_sound(int i){return i?&nosound_procs:&soundprocs;}
