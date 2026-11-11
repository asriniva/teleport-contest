/* Original OPTIONS owner; no transport or policy replacement. */
#include "options.c"
const void *probe_banner_options_storage(int i){switch(i){case 0:return allopt_init;case 1:return allopt;case 2:return wc_options;case 3:return wc2_options;}return NULL;}

#include <stdint.h>
uintptr_t probe_banner_options_function(int i){switch(i){
#include "options-functions.inc"
}return 0;}
void probe_banner_options_copy(void){memcpy(allopt,allopt_init,sizeof allopt);}
