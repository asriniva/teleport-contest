/* Observation boundary after original newgame renders its first screen. */
#include "hack.h"
#include <stdlib.h>
extern const seenV seenv_matrix[3][3];
#include <stdio.h>
void __wrap_u_init_skills_discoveries(void){fflush(stdout);fputs("Observed C boundary: u_init_skills_discoveries\n",stderr);abort();}
const void *probe_first_display_matrix(void){return seenv_matrix;}
