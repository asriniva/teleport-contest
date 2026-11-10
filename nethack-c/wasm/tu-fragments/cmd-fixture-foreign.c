/* Separate optimized foreign reader: no LTO, no CMD function invoked. */
#include "cmd-types.h"
#include <string.h>
static unsigned long observed[7];static char observed_text[128];
__attribute__((constructor))static void observe_public(void){
 observed[0]=extcmdlist[0].key;observed[1]=!!extcmdlist[0].ef_funct;
 observed[2]=extcmdlist[169].flags;observed[3]=!!extcmdlist[170].ef_txt;
 observed[4]=levltyp[0]?strlen(levltyp[0]):0;observed[5]=unavailcmd[0];observed[6]=unavailcmd[25];
 if(extcmdlist[0].ef_txt)strncpy(observed_text,extcmdlist[0].ef_txt,sizeof observed_text-1);
}
unsigned long probe_ctor(int i){return observed[i];}const char*probe_ctor_text(void){return observed_text;}

/* Opaque separate-TU callback mutates original while observing by-value copy. */
int cmd_fixture_copy_observer(const coord*copy,coord*original){if(original){original->x=77;original->y=78;}return copy->x*256+copy->y;}
