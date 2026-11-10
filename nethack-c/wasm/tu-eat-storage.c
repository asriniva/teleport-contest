/* Zero-only EAT backing, separate from every native reader. JS owns all initializers. No LTO. */
#include "hack.h"
#ifdef TELEPORT_PORT_EAT_STORAGE
const char*const hu_stat[7];
char teleport_eat_msgbuf[BUFSZ];
struct victual_info teleport_eat_zero_victual;
#endif
