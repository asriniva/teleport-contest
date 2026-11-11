/* Original C policies, shared with the previous subsystem reference. */
#include "standalone-object-state-probe.c"
__typeof__(svl) svl;
/* An invalid-quantity diagnostic requests naming/UI, outside this group. */
char *simpleonames(struct obj *o){abort();}
#include STANDALONE_MKOBJ_SOURCE
static struct obj *records[8],*heads[4];
void probe_record_prepare(void){monst_globals_init();svc.context.current_fruit=19;}
void *probe_record_new(int i,short type,long quantity){
 if(records[i])abort();records[i]=malloc(sizeof *records[i]);if(!records[i])abort();
 return init_dummyobj(records[i],type,quantity);
}
void *probe_record_at(int i){return records[i];}
void *probe_record_head(int i){return &heads[i];}
const void *probe_record_global(int i){switch(i){case 0:return &svc.context;case 1:return &svl.level;case 2:return &cg;}return NULL;}
void probe_record_mail(int i,const char *s){new_omailcmd(records[i],s);}
long probe_record_op(int op,int i,int arg){struct obj *o=records[i];switch(op){
 case 0:o->oextra=newoextra();break;case 1:init_oextra(o->oextra);break;
 case 2:dealloc_oextra(o);break;case 3:newomonst(o);break;case 4:free_omonst(o);break;
 case 5:newomid(o);break;case 6:free_omid(o);break;case 7:free_omailcmd(o);break;
 case 8:return weight(o);case 9:container_weight(o);break;
 case 10:extract_nobj(o,&heads[arg]);break;case 11:extract_nexthere(o,&heads[arg]);break;
 case 12:add_to_buried(o);break;case 13:return bcsign(o);case 14:return next_ident();
 case 15:return is_flammable(o);case 16:return is_rottable(o);case 17:return is_treefruit(o);
 case 18:dealloc_obj_real(o);records[i]=NULL;break;
 }return 0;}
