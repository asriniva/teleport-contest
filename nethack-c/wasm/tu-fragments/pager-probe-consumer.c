/* Separate optimized extern-only public array reader, like GETPOS. */
#include "hack.h"
extern const char what_is_a_location[30];
unsigned long teleport_pager_consumer(char*out){unsigned long h=1469598103934665603UL;for(int i=0;i<30;i++){out[i]=what_is_a_location[i];h^=(unsigned char)out[i];h*=1099511628211UL;}return h;}
