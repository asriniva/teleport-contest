#include "hack.h"
static void *ids[4096]; static unsigned sizes[4096], nalloc, nfree, free_calls; static unsigned freed[4096];
long *utility_alloc(unsigned size) { long *p=alloc(size);ids[++nalloc]=p;sizes[nalloc]=size;return p; }
void utility_free(void *p) { ++free_calls; for(unsigned i=1;i<=nalloc;i++)if(ids[i]==p){freed[++nfree]=i;break;}free(p); }
unsigned utility_log(int key,int index){return key==0?nalloc:key==1?nfree:key==2?sizes[index]:key==4?free_calls:freed[index];}
uintptr_t utility_allocation(unsigned index) { return (uintptr_t)ids[index]; }
