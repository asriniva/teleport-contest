#include "hack.h"
#include <string.h>
#include <emscripten/stack.h>
#include "tu-objects-layout.h"
static const char *field_names[]={"oc_name_idx","oc_descr_idx","oc_name_known","oc_merge","oc_uses_known","oc_encountered","oc_magic","oc_charged","oc_unique","oc_nowish","oc_big","oc_tough","oc_spare1","oc_dir","oc_material","oc_subtyp","oc_oprop","oc_class","oc_delay","oc_color","oc_prob","oc_weight","oc_cost","oc_wsdam","oc_wldam","oc_oc1","oc_oc2","oc_nutrition","oc_sell_minseen","oc_sell_maxseen","oc_buy_minseen","oc_buy_maxseen"};
static const unsigned char field_unsigned[]={0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,1,0,0,0,0,0,1,1,1,1,1};
static char user_name[]="fixture user name";
static char descriptor_name[]="";
static char descriptor_text[]="fixture description";
void probe_init(void){objects_globals_init();}
int probe_count(void){return NUM_OBJECTS+1;}
int probe_field_count(void){return SIZE(field_names);}
const char *probe_field_name(int f){return field_names[f];}
int probe_field_kind(int f){return field_unsigned[f];}
unsigned long probe_value(int row,int f){struct objclass *o=&objects[row];switch(f){
case 0:return (unsigned long)o->oc_name_idx;
case 1:return (unsigned long)o->oc_descr_idx;
case 2:return (unsigned long)o->oc_name_known;
case 3:return (unsigned long)o->oc_merge;
case 4:return (unsigned long)o->oc_uses_known;
case 5:return (unsigned long)o->oc_encountered;
case 6:return (unsigned long)o->oc_magic;
case 7:return (unsigned long)o->oc_charged;
case 8:return (unsigned long)o->oc_unique;
case 9:return (unsigned long)o->oc_nowish;
case 10:return (unsigned long)o->oc_big;
case 11:return (unsigned long)o->oc_tough;
case 12:return (unsigned long)o->oc_spare1;
case 13:return (unsigned long)o->oc_dir;
case 14:return (unsigned long)o->oc_material;
case 15:return (unsigned long)o->oc_subtyp;
case 16:return (unsigned long)o->oc_oprop;
case 17:return (unsigned long)o->oc_class;
case 18:return (unsigned long)o->oc_delay;
case 19:return (unsigned long)o->oc_color;
case 20:return (unsigned long)o->oc_prob;
case 21:return (unsigned long)o->oc_weight;
case 22:return (unsigned long)o->oc_cost;
case 23:return (unsigned long)o->oc_wsdam;
case 24:return (unsigned long)o->oc_wldam;
case 25:return (unsigned long)o->oc_oc1;
case 26:return (unsigned long)o->oc_oc2;
case 27:return (unsigned long)o->oc_nutrition;
case 28:return (unsigned long)o->oc_sell_minseen;
case 29:return (unsigned long)o->oc_sell_maxseen;
case 30:return (unsigned long)o->oc_buy_minseen;
case 31:return (unsigned long)o->oc_buy_maxseen;
default:return 0;}}
const char *probe_string(int row,int f){return f==0?obj_descr[row].oc_name:f==1?obj_descr[row].oc_descr:objects[row].oc_uname;}
void *probe_objects(void){return objects;}
void *probe_descriptors(void){return obj_descr;}
void probe_poison(unsigned seed){size_t i;unsigned char *p=(unsigned char *)objects;for(i=0;i<sizeof(struct objclass)*(NUM_OBJECTS+1);i++){seed=seed*1664525U+1013904223U;p[i]=seed>>24;}p=(unsigned char *)obj_descr;for(i=0;i<sizeof(struct objdescr)*(NUM_OBJECTS+1);i++){seed=seed*1664525U+1013904223U;p[i]=seed>>24;}}
void probe_mutate(int row,int f,unsigned long value){struct objclass *o=&objects[row];switch(f){
case 0:o->oc_name_idx=value;break;
case 1:o->oc_descr_idx=value;break;
case 2:o->oc_name_known=value;break;
case 3:o->oc_merge=value;break;
case 4:o->oc_uses_known=value;break;
case 5:o->oc_encountered=value;break;
case 6:o->oc_magic=value;break;
case 7:o->oc_charged=value;break;
case 8:o->oc_unique=value;break;
case 9:o->oc_nowish=value;break;
case 10:o->oc_big=value;break;
case 11:o->oc_tough=value;break;
case 12:o->oc_spare1=value;break;
case 13:o->oc_dir=value;break;
case 14:o->oc_material=value;break;
case 15:o->oc_subtyp=value;break;
case 16:o->oc_oprop=value;break;
case 17:o->oc_class=value;break;
case 18:o->oc_delay=value;break;
case 19:o->oc_color=value;break;
case 20:o->oc_prob=value;break;
case 21:o->oc_weight=value;break;
case 22:o->oc_cost=value;break;
case 23:o->oc_wsdam=value;break;
case 24:o->oc_wldam=value;break;
case 25:o->oc_oc1=value;break;
case 26:o->oc_oc2=value;break;
case 27:o->oc_nutrition=value;break;
case 28:o->oc_sell_minseen=value;break;
case 29:o->oc_sell_maxseen=value;break;
case 30:o->oc_buy_minseen=value;break;
case 31:o->oc_buy_maxseen=value;break;
}}
void probe_strings(int row,int mode){objects[row].oc_uname=mode?user_name:NULL;obj_descr[row].oc_name=mode?descriptor_name:NULL;obj_descr[row].oc_descr=mode==2?descriptor_name:mode?descriptor_text:NULL;}
size_t probe_stack(void){return emscripten_stack_get_current();}
