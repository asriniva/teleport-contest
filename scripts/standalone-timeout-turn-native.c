/* Original TIMEOUT owner alone. Observers never replace an event or queue. */
#include "timeout.c"
#include <stdlib.h>
const void *probe_timeout_turn_table(int index,int cleanup)
{
    if(index<0||index>=SIZE(timeout_funcs))abort();
    return cleanup?(const void *)timeout_funcs[index].cleanup:(const void *)timeout_funcs[index].f;
}
const char *probe_timeout_turn_name(int index)
{
    if(index<0||index>=SIZE(timeout_funcs))abort();
    return timeout_funcs[index].name;
}
void probe_timeout_turn_step(long when){svm.moves=when;nh_timeout();fflush(stdout);}
