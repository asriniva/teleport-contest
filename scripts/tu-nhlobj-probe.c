/* Real Lua5.4.8 VM/nhlua/sp_lev accessors; controlled external object/timer world. */
#include "hack.h"
#include "sp_lev.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
__typeof__(svl) svl;__typeof__(gc) gc;__typeof__(gx) gx;__typeof__(gy) gy;__typeof__(gl) gl;__typeof__(gt) gt;const __typeof__(cg) cg={0};
struct obj hands_obj;
/* External decl.c material vocabulary; no NHLOBJ policy/data duplicated here. */
const char*materialnm[]={"mysterious","liquid","wax","organic","flesh","paper","cloth","leather","wooden","bone","dragonhide","iron","metal","copper","silver","gold","platinum","mithril","plastic","glass","gemstone","stone"};
static lua_State*state;static struct obj*items[128];static struct obj saved[128];static int made,freed,merge_slot=-1,fixture_poisoned,bury_delete,extract_growth;static char tracebuf[262144],output[65536];static long timers[128][NUM_TIME_FUNCS];static struct sp_coder coder;static struct mkroom fixture_room;static void*growth;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
static int oid(struct obj*o){int i;if(!o)return -1;for(i=0;i<made;i++)if(items[i]==o)return i;return -2;}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);vfprintf(stderr,fmt,ap);va_end(ap);abort();}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(output,sizeof output,fmt,ap);va_end(ap);append("impossible:%s;",output);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(output,sizeof output,fmt,ap);va_end(ap);append("pline:%s;",output);}
void livelog_printf(long cat,const char*fmt,...){append("livelog:%ld;",cat);}
static struct obj*make_obj(int typ){struct obj*o;if(made>=128)panic("fixture object limit");o=malloc(sizeof *o);memset(o,0,sizeof *o);o->o_id=100+made;o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;o->where=OBJ_FREE;o->corpsenm=NON_PM;o->owt=objects[typ].oc_weight;items[made++]=o;return o;}
struct obj*mksobj(int typ,boolean init,boolean art){append("make:%d:%d:%d;",typ,init,art);return make_obj(typ);}struct obj*mkobj(int cls,boolean art){append("mkclass:%d:%d;",cls,art);return make_obj(cls==POTION_CLASS?POT_HEALING:ROCK);}
struct obj*readobjnam(char*s,struct obj*unused){append("wish:%s;",s);if(!strcmp(s,"hands"))return &hands_obj;if(!strcmp(s,"missing"))return NULL;return make_obj(!strcmp(s,"chest")?CHEST:!strcmp(s,"corpse")?CORPSE:!strcmp(s,"arrow")?ARROW:ROCK);}
void obj_extract_self(struct obj*o){struct obj**p;int i;append("extract:%d:%d;",oid(o),o->where);if(extract_growth&&!growth)growth=malloc(32*1024*1024);if(o->where==OBJ_CONTAINED){for(p=&o->ocontainer->cobj;*p;p=&(*p)->nobj)if(*p==o){*p=o->nobj;break;}}else if(o->where==OBJ_FLOOR){for(p=&fobj;*p;p=&(*p)->nobj)if(*p==o){*p=o->nobj;break;}for(p=&svl.level.objects[o->ox][o->oy];*p;p=&(*p)->nexthere)if(*p==o){*p=o->nexthere;break;}}o->nobj=NULL;o->nexthere=NULL;o->where=OBJ_FREE;(void)i;}
void dealloc_obj(struct obj*o){int i=oid(o);append("dealloc:%d:%u;",i,o->lua_ref_cnt);if(o->lua_ref_cnt){o->where=OBJ_LUAFREE;return;}if(i<0)panic("unknown object");saved[i]=*o;if(o->oextra){free(o->oextra->oname);free(o->oextra);}free(o);items[i]=NULL;freed++;}
struct obj*add_to_container(struct obj*box,struct obj*o){append("container:%d:%d;",oid(box),oid(o));if(merge_slot>=0){struct obj*t=items[merge_slot];t->quan+=o->quan;dealloc_obj(o);return t;}o->where=OBJ_CONTAINED;o->ocontainer=box;o->nobj=box->cobj;box->cobj=o;return o;}
struct obj*addinv(struct obj*o){append("inventory:%d;",oid(o));if(merge_slot>=0){struct obj*t=items[merge_slot];t->quan+=o->quan;dealloc_obj(o);return t;}o->where=OBJ_INVENT;return o;}
int weight(struct obj*o){struct obj*c;int n=objects[o->otyp].oc_weight;append("weight:%d;",oid(o));for(c=o->cobj;c;c=c->nobj)n+=c->owt;return n;}
void place_object(struct obj*o,coordxy x,coordxy y){append("place:%d:%d:%d;",oid(o),x,y);o->ox=x;o->oy=y;o->where=OBJ_FLOOR;o->nobj=fobj;fobj=o;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
boolean permapoisoned(struct obj*o){append("poison:%d;",oid(o));return fixture_poisoned;}
boolean obj_has_timer(struct obj*o,short t){append("has:%d:%d;",oid(o),t);return timers[oid(o)][t]!=0;}
long peek_timer(short t,anything*a){append("peek:%d:%d;",oid(a->a_obj),t);return timers[oid(a->a_obj)][t];}
long stop_timer(short t,anything*a){int i=oid(a->a_obj);long n=timers[i][t];append("stop:%d:%d;",i,t);timers[i][t]=0;return n;}
boolean start_timer(long when,short kind,short type,anything*a){int i=oid(a->a_obj);append("start:%d:%ld:%d:%d;",i,when,kind,type);timers[i][type]=when;return TRUE;}
void obj_stop_timers(struct obj*o){append("stopall:%d;",oid(o));memset(timers[oid(o)],0,sizeof timers[0]);}
struct obj*bury_an_obj(struct obj*o,boolean*gone){append("bury:%d:%d:%d;",oid(o),o->ox,o->oy);if(bury_delete){obj_extract_self(o);dealloc_obj(o);*gone=TRUE;return NULL;}*gone=FALSE;return o;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/nhlobj.c"
#define TELEPORT_NHLOBJ_VALIDATE_SOURCE 1
#endif
#include "tu-nhlobj-layout.h"
#ifndef TELEPORT_REFERENCE_TU
extern void* teleport_nhlobj_test_l_obj_check(lua_State*,int);
extern int teleport_nhlobj_test_l_obj_gc(lua_State*);
extern void* teleport_nhlobj_test_l_obj_push(lua_State*,struct obj*);
extern int teleport_nhlobj_test_l_obj_getcontents(lua_State*);
extern int teleport_nhlobj_test_l_obj_add_to_container(lua_State*);
extern int teleport_nhlobj_test_l_obj_objects_to_table(lua_State*);
extern int teleport_nhlobj_test_l_obj_to_table(lua_State*);
extern int teleport_nhlobj_test_l_obj_new_readobjnam(lua_State*);
extern int teleport_nhlobj_test_l_obj_at(lua_State*);
extern int teleport_nhlobj_test_l_obj_placeobj(lua_State*);
extern int teleport_nhlobj_test_l_obj_nextobj(lua_State*);
extern int teleport_nhlobj_test_l_obj_container(lua_State*);
extern int teleport_nhlobj_test_l_obj_isnull(lua_State*);
extern int teleport_nhlobj_test_l_obj_timer_has(lua_State*);
extern int teleport_nhlobj_test_l_obj_timer_peek(lua_State*);
extern int teleport_nhlobj_test_l_obj_timer_stop(lua_State*);
extern int teleport_nhlobj_test_l_obj_timer_start(lua_State*);
extern int teleport_nhlobj_test_l_obj_bury(lua_State*);
#endif
void probe_reset(void){int i;if(state){lua_close(state);state=NULL;}for(i=0;i<made;i++)if(items[i]){if(items[i]->oextra){free(items[i]->oextra->oname);free(items[i]->oextra);}free(items[i]);items[i]=NULL;}if(growth)free(growth);growth=NULL;memset(&svl,0,sizeof svl);memset(&gc,0,sizeof gc);memset(&gx,0,sizeof gx);memset(&gy,0,sizeof gy);memset(&gl,0,sizeof gl);memset(&gt,0,sizeof gt);memset(saved,0,sizeof saved);memset(timers,0,sizeof timers);made=freed=0;merge_slot=-1;fixture_poisoned=bury_delete=extract_growth=0;tracebuf[0]=output[0]=0;objects_globals_init();monst_globals_init();for(i=0;i<NUM_OBJECTS;i++)objects[i].oc_name_idx=objects[i].oc_descr_idx=i;state=luaL_newstate();luaL_openlibs(state);l_obj_register(state);lua_pushcfunction(state,nhl_obj_u_giveobj);lua_setglobal(state,"giveobj");}
int probe_eval(const char*text){int status;lua_settop(state,0);status=luaL_loadbuffer(state,text,strlen(text),"nhlobj-fixture");if(!status)status=lua_pcall(state,0,LUA_MULTRET,0);if(lua_gettop(state)&&lua_isstring(state,-1)){size_t n;const char*s=lua_tolstring(state,-1,&n);if(n>=sizeof output)n=sizeof output-1;memcpy(output,s,n);output[n]=0;}else output[0]=0;return status;}
void probe_option(int which,int value){switch(which){case 0:merge_slot=value;break;case 1:fixture_poisoned=value;break;case 2:bury_delete=value;break;case 3:extract_growth=value;break;case 4:gx.xstart=value;break;case 5:gy.ystart=value;break;case 6:memset(&coder,0,sizeof coder);memset(&fixture_room,0,sizeof fixture_room);fixture_room.lx=value;fixture_room.ly=value+1;coder.croom=&fixture_room;gc.coder=&coder;break;}}
void probe_push(int i,const char*name){nhl_push_obj(state,i<0?NULL:items[i]);lua_setglobal(state,name);}void probe_new(int type){make_obj(type);}void probe_collect(void){lua_gc(state,LUA_GCCOLLECT);}
int probe_count(int k){return k==0?made:k==1?freed:lua_gettop(state);}const char*probe_trace(void){return tracebuf;}const char*probe_output(void){return output;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
void*probe_object(int i){return items[i];}void*probe_state(void){return state;}

/* Independent fixture scalar observations and list identity. */
long probe_field(int slot,int field){struct obj*o=items[slot]?items[slot]:&saved[slot];switch(field){case 0:return o->o_id;case 1:return o->ox;case 2:return o->oy;case 3:return o->otyp;case 4:return o->owt;case 5:return o->quan;case 6:return o->spe;case 7:return o->oclass;case 8:return o->invlet;case 9:return o->where;case 10:return o->corpsenm;case 11:return o->usecount;case 12:return o->oeaten;case 13:return o->age;case 14:return o->owornmask;case 15:return o->lua_ref_cnt;default:return 0;}}
void probe_set(int slot,int field,long value){struct obj*o=items[slot];switch(field){case 0:o->o_id=value;break;case 1:o->ox=value;break;case 2:o->oy=value;break;case 3:o->otyp=value;break;case 4:o->owt=value;break;case 5:o->quan=value;break;case 6:o->spe=value;break;case 7:o->oclass=value;break;case 8:o->invlet=value;break;case 9:o->where=value;break;case 10:o->corpsenm=value;break;case 11:o->usecount=value;break;case 12:o->oeaten=value;break;case 13:o->age=value;break;case 14:o->owornmask=value;break;case 15:o->lua_ref_cnt=value;break;}}
void probe_bit(int slot,int field,int value){struct obj*o=items[slot];switch(field){case 0:o->cursed=value;break;case 1:o->blessed=value;break;case 2:o->unpaid=value;break;case 3:o->no_charge=value;break;case 4:o->known=value;break;case 5:o->dknown=value;break;case 6:o->bknown=value;break;case 7:o->rknown=value;break;case 8:o->tknown=value;break;case 9:o->odiluted=value;break;case 10:o->oeroded=value;break;case 11:o->oeroded2=value;break;case 12:o->oerodeproof=value;break;case 13:o->olocked=value;break;case 14:o->obroken=value;break;case 15:o->opoisoned=value;break;case 16:o->otrapped=value;break;case 17:o->recharged=value;break;case 18:o->lamplit=value;break;case 19:o->globby=value;break;case 20:o->greased=value;break;case 21:o->nomerge=value;break;case 22:o->how_lost=value;break;case 23:o->in_use=value;break;case 24:o->bypass=value;break;case 25:o->cknown=value;break;case 26:o->lknown=value;break;}}
int probe_link(int slot,int field){struct obj*o=items[slot];if(!o)return -3;switch(field){case 0:return oid(o->nobj);case 1:return oid(o->nexthere);case 2:return oid(o->cobj);case 3:return o->where==OBJ_CONTAINED?oid(o->ocontainer):-1;default:return -9;}}
void probe_name(int slot,const char*name){struct obj*o=items[slot];if(!o->oextra)o->oextra=calloc(1,sizeof *o->oextra);free(o->oextra->oname);o->oextra->oname=strdup(name);}
void probe_class(int typ,int which,int value){switch(which){case 0:objects[typ].oc_name_idx=value;break;case 1:objects[typ].oc_descr_idx=value;break;case 2:objects[typ].oc_name_known=value;break;}}
const char*probe_reg_name(int table,int index){
#ifdef TELEPORT_REFERENCE_TU
return (table?l_obj_meta:l_obj_methods)[index].name;
#else
extern void*teleport_nhlobj_storage(int);return ((luaL_Reg*)teleport_nhlobj_storage(table))[index].name;
#endif
}
int probe_reg_callback(int table,int index){lua_CFunction f;int i;
#ifdef TELEPORT_REFERENCE_TU
lua_CFunction callbacks[]={l_obj_new_readobjnam,l_obj_isnull,l_obj_at,l_obj_nextobj,l_obj_to_table,l_obj_objects_to_table,l_obj_placeobj,l_obj_container,l_obj_getcontents,l_obj_add_to_container,l_obj_timer_has,l_obj_timer_peek,l_obj_timer_stop,l_obj_timer_start,l_obj_bury,l_obj_gc};f=(table?l_obj_meta:l_obj_methods)[index].func;for(i=0;i<16;i++)if(f==callbacks[i])return i;
#else
extern void*teleport_nhlobj_storage(int);extern uintptr_t teleport_nhlobj_callback_pointer(int);f=((luaL_Reg*)teleport_nhlobj_storage(table))[index].func;for(i=0;i<16;i++)if((uintptr_t)f==teleport_nhlobj_callback_pointer(i))return i;
#endif
return f?-2:-1;}
void*probe_bytes(int i){return items[i]?items[i]:&saved[i];}
const char*probe_oname(int i){return items[i]&&items[i]->oextra?items[i]->oextra->oname:NULL;}
long probe_timer(int slot,int type){return timers[slot][type];}
void probe_release(int slot){dealloc_obj(items[slot]);}
