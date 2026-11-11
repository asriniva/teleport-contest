/* Original VERSION owner, included alone for private table observations. */
#include "version.c"
const void *probe_version_storage(int i){switch(i){case 0:return critical_sizes;case 1:return cscbuf;case 2:return rt_opts;case 3:return &nomakedefs;}return NULL;}
