#include "hack.h"
#include <stdint.h>
uintptr_t probe_call(char *s) { regularize(s); return (uintptr_t) s; }
int probe_char_signed(void) { return (char) 255 < 0; }
int probe_profile(int key) {
    switch(key) {
#ifdef PC_LOCKING
    case 0: return 1;
#endif
#ifdef __EMX__
    case 1: return 1;
#endif
#ifdef OS2
    case 2: return 1;
#endif
    default: return 0;
    }
}
