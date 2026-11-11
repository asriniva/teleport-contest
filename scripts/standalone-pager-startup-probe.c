/* Observation boundary after original newgame runs its real legacy pager. */
#include "hack.h"
#include <stdlib.h>
extern const seenV seenv_matrix[3][3];
#include <stdio.h>
void __wrap_save_currentstate(void){fflush(stdout);fputs("Observed C boundary: save_currentstate\n",stderr);abort();}
const void *probe_first_display_matrix(void){return seenv_matrix;}
