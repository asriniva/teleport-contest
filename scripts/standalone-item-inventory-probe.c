/* Original-C group; these wrappers only configure inputs/expose results. */
#include "standalone-object-state-probe.c"
#include <emscripten/heap.h>
__typeof__(svl) svl;
/* windows.c's original zerowri initializer has only zero fields. */
win_request_info zerowri={0};
#include STANDALONE_MKOBJ_SOURCE
#include STANDALONE_INVENT_SOURCE
static struct obj *items[128];
static int updates;
static int grow_once;
static void inventory_update(int arg){if(arg)abort();updates++;if(grow_once){size_t n=emscripten_get_heap_size()+16777216;void*p=malloc(n);if(!p)abort();memset(p,165,n);free(p);grow_once=0;}}
void probe_item_force_growth(void){grow_once=1;}
void probe_item_prepare(void){monst_globals_init();svc.context.ident=2;svc.context.current_fruit=19;windowprocs.win_update_inventory=inventory_update;}
void *probe_item_create(int i,int type,int init,int arti){if(items[i])abort();return items[i]=mksobj(type,init,arti);}
void *probe_item_at(int i){return items[i];}
void *probe_item_global(int i){switch(i){case 0:return &gi;case 1:return &go;case 2:return &gl;case 3:return &svc;case 4:return &flags;case 5:return &disp;case 6:return &program_state;case 7:return &iflags;case 8:return &u;}return NULL;}
long probe_item_action(int op,int i,int j){switch(op){
 case 0:return (long)addinv(items[i]);case 1:return (long)addinv_nomerge(items[i]);
 case 2:freeinv(items[i]);break;case 3:dealloc_obj_real(items[i]);items[i]=NULL;break;
 case 4:return mergable(items[i],items[j]);case 5:return merged(&items[i],&items[j]);
 case 6:return (long)addinv_before(items[i],items[j]);case 7:return (long)currency(0L);
 case 8:return count_unpaid(gi.invent);case 9:assigninvlet(items[i]);break;case 10:reorder_invent();break;
 case 11:return (long)carrying(i);case 12:return (long)mkobj(i,FALSE);
 }return 0;}
void probe_item_flush(void){struct obj *o;for(o=go.objs_deleted;o;o=o->nobj)for(int i=0;i<128;i++)if(items[i]==o)items[i]=NULL;dobjsfree();}
int probe_item_updates(void){return updates;}
