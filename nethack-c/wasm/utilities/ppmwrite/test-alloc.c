#include "config.h"
extern long*alloc(unsigned);
static unsigned allocations,frees;
static size_t alloc_sizes[4096];
static void*alloc_ptrs[4096];static int free_ids[4096];
long*teleport_ppm_alloc(unsigned n){long*p=alloc(n);if(allocations<4096){alloc_sizes[allocations]=n;alloc_ptrs[allocations]=p;}allocations++;return p;}
void teleport_ppm_free(void*p){if(frees<4096){free_ids[frees]=-1;for(unsigned i=0;i<allocations&&i<4096;i++)if(alloc_ptrs[i]==p){free_ids[frees]=i;break;}}frees++;free(p);}
int teleport_ppm_free_id(unsigned n){return n<frees&&n<4096?free_ids[n]:-2;}
unsigned teleport_ppm_allocations(void){return allocations;}
unsigned teleport_ppm_frees(void){return frees;}
size_t teleport_ppm_alloc_size(unsigned n){return n<allocations&&n<4096?alloc_sizes[n]:0;}
