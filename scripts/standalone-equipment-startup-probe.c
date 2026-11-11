/* Observation boundary after original newgame activates equipment and skills. */
#include "hack.h"
#include <stdlib.h>
extern const seenV seenv_matrix[3][3];
#include <stdio.h>
void __wrap_com_pager(const char *message UNUSED){fflush(stdout);fputs("Observed C boundary: com_pager\n",stderr);abort();}
const void *probe_first_display_matrix(void){return seenv_matrix;}
