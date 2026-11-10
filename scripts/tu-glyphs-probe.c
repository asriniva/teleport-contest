/* Real external catalogues/Unicode/color/libc dependencies and controlled
 * configuration/UI/allocator diagnostics. No original GLYPHS body in hybrid. */
#include "hack.h"
#include "tu-glyphs-layout.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <emscripten.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef free
extern void free(void*);
__typeof__(gg)gg;__typeof__(gs)gs;__typeof__(iflags)iflags;__typeof__(gc)gc;__typeof__(windowprocs)windowprocs;__typeof__(u)u;__typeof__(flags)flags;
glyph_map glyphmap[MAX_GLYPH];
const char hexdd[33]="00112233445566778899aAbBcCdDeEfF";
#include "../.cache/wasm64-build/tree/src/objects.c"
#include "../.cache/wasm64-build/tree/src/monst.c"
#include "../nethack-c/wasm/tu-fragments/glyphs-fixture-data.h"
static char tracebuf[8388608],snapshotbuf[8388608],dumpbuf[8388608],input[4096];
static int tracepos,dumppos,opts[24],allocs,frees,dups,nformats,callback_count;static size_t totalbytes;static void*growth;
struct allocation {void*p;unsigned size;int live;};static struct allocation allocations[4*MAX_GLYPH+1024];
static int allocation_index(void*p){int i;for(i=allocs-1;i>=0;i--)if(allocations[i].p==p&&allocations[i].live)return i+1;return 0;}
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);va_end(ap);}
EM_JS(void,fixture_throw,(int why),{throw new Error('GLYPHS fixture exit '+why);});
static void callback(void);
long*alloc(unsigned n){void*p=malloc(n);if(!p)abort();if(allocs>=SIZE(allocations))abort();allocations[allocs++]=(struct allocation){p,n,1};totalbytes+=n;if(opts[0])logmsg("alloc:%u;",n);callback();return p;}
char*dupstr(const char*s){unsigned n=strlen(s)+1;char*p=(char*)alloc(n);memcpy(p,s,n);dups++;if(opts[0])logmsg("dup:%s;",s);return p;}
void teleport_probe_free(void*p){if(p){int i=allocation_index(p);if(!i)abort();allocations[i-1].live=0;frees++;if(opts[0])logmsg("free:%d;",i);free(p);}}
#define free teleport_probe_free
void panic(const char*f,...){logmsg("panic:%s;",f);fixture_throw(1);__builtin_unreachable();}
void impossible(const char*f,...){logmsg("impossible:%s;",f);fixture_throw(2);}
void __assert_fail(const char*e,const char*f,int line,const char*fn){const char*p=strrchr(f,'/');logmsg("assert:%s:%s:%d:%s;",e,p?p+1:f,line,fn);fixture_throw(3);__builtin_unreachable();}
void config_error_add(const char*f,...){va_list ap;va_start(ap,f);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,f,ap);va_end(ap);logmsg(";");callback();}
int teleport_probe_fprintf(FILE*fp,const char*f,...){va_list ap;int n;(void)fp;va_start(ap,f);n=vsnprintf(dumpbuf+dumppos,sizeof dumpbuf-dumppos,f,ap);va_end(ap);dumppos+=n;return n;}
void wizcustom_callback(winid win,int glyphnum,char*id){callback_count++;if(opts[2])logmsg("wiz:%d:%d:%s;",win,glyphnum,id);callback();}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/glyphs.c"
#define TELEPORT_GLYPHS_VALIDATE_SOURCE 1
#else
#define find_struct teleport_glyphs_find
#define glyphid_cache_t teleport_glyphs_cache
extern void teleport_glyphs_to_custom_callback(int,struct find_struct*);
#define to_custom_symset_entry_callback teleport_glyphs_to_custom_callback
extern char *teleport_glyphs_test_fix_glyphname(char*);
#define fix_glyphname teleport_glyphs_test_fix_glyphname
extern int teleport_glyphs_test_glyph_find_core(const char*,struct find_struct*);
#define glyph_find_core teleport_glyphs_test_glyph_find_core
extern void teleport_glyphs_test_init_glyph_cache(void);
#define init_glyph_cache teleport_glyphs_test_init_glyph_cache
extern void teleport_glyphs_test_add_glyph_to_cache(int,const char*);
#define add_glyph_to_cache teleport_glyphs_test_add_glyph_to_cache
extern int teleport_glyphs_test_find_glyph_in_cache(const char*);
#define find_glyph_in_cache teleport_glyphs_test_find_glyph_in_cache
extern char *teleport_glyphs_test_find_glyphid_in_cache_by_glyphnum(int);
#define find_glyphid_in_cache_by_glyphnum teleport_glyphs_test_find_glyphid_in_cache_by_glyphnum
extern uint32 teleport_glyphs_test_glyph_hash(const char*);
#define glyph_hash teleport_glyphs_test_glyph_hash
extern void teleport_glyphs_test_shuffle_customizations(void);
#define shuffle_customizations teleport_glyphs_test_shuffle_customizations
extern int teleport_glyphs_test_parse_id(const char*,struct find_struct*);
#define parse_id teleport_glyphs_test_parse_id
#endif
#include "../nethack-c/wasm/tu-fragments/glyphs-support.c"
static int callback_depth;
static void callback(void){if(opts[3]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}if(opts[4]&&!callback_depth){opts[4]=0;callback_depth++;logmsg("reentry:%u;",glyph_hash("ABCxyz"));callback_depth--;}if(opts[5])fixture_throw(5);}
static void fixture_find_callback(int glyph,struct find_struct*find){callback_count++;logmsg("found:%d:%u:%d;",glyph,(unsigned)find->findtype,find->val);if(find->extraval)*find->extraval=glyph;callback();}
static struct find_struct request;static int extra;
void probe_clear(void){tracepos=dumppos=0;tracebuf[0]=dumpbuf[0]=0;}
void probe_reset(void){int i;free_glyphid_cache();purge_all_custom_entries();free_all_glyphmap_u();if(growth){
#undef free
free(growth);
#define free teleport_probe_free
growth=0;}for(i=0;i<allocs;i++)if(allocations[i].live){
#undef free
free(allocations[i].p);
#define free teleport_probe_free
}memset(allocations,0,sizeof allocations);allocs=frees=dups=nformats=callback_count=0;totalbytes=0;memset(&gs,0,sizeof gs);memset(&gc,0,sizeof gc);memset(&iflags,0,sizeof iflags);memset(glyphmap,0,sizeof glyphmap);memset(opts,0,sizeof opts);memset(&request,0,sizeof request);extra=-99;objects_globals_init();monst_globals_init();iflags.customsymbols=iflags.customcolors=TRUE;gs.symset[0].name="primary";gs.symset[1].name="rogue";gs.symset[0].handling=gs.symset[1].handling=H_UTF8;probe_clear();}
char*probe_input(void){return input;}
void probe_option(int i,int v){opts[i]=v;}
void probe_symset(int i,int named,int utf){gs.symset_which_set=i;gs.symset[i].name=named?(i?"rogue":"primary"):0;gs.symset[i].handling=utf?H_UTF8:H_UNK;}
void probe_flags(int colors,int symbols,int pending,int which){iflags.customcolors=colors;iflags.customsymbols=symbols;iflags.pending_customizations=pending;gc.currentgraphics=which;}
void probe_request(int type,int val,int reserved_type){memset(&request,0,sizeof request);request.findtype=type;request.val=val;request.callback=fixture_find_callback;request.extraval=&extra;request.restype=reserved_type;request.reserved=(void*)1;}
void probe_description(int typ,int desc){objects[typ].oc_descr_idx=desc;}
void probe_glyph(int index,uint32 color,uint16 idx,uint32 code,const char*text){glyphmap[index].customcolor=color;glyphmap[index].color256idx=idx;if(code)set_map_u(&glyphmap[index],code,(const uint8*)text);}
void probe_custom(int type,int set,int glyph,uint32 color){if(type==custom_ureps)add_custom_urep_entry(set?"rogue":"primary",glyph,color,(const uint8*)input,set);else add_custom_nhcolor_entry(set?"rogue":"primary",glyph,color,set);}
long probe_call(int action,int x,int y){switch(action){case 0:return glyph_to_cmap(x);case 1:return glyph_hash(input);case 2:fix_glyphname(input);break;case 3:return glyphrep_to_custom_map_entries(input,&extra);case 4:return match_glyph(input);case 5:return glyphrep(input);case 6:fill_glyphid_cache();break;case 7:free_glyphid_cache();break;case 8:return find_glyph_in_cache(input);case 9:{char*p=find_glyphid_in_cache_by_glyphnum(x);return p?(strcpy(input,p),1):0;}case 10:init_glyph_cache();break;case 11:add_glyph_to_cache(x,input);break;case 12:return glyphid_cache_status();case 13:apply_customizations(x,y);break;case 14:maybe_shuffle_customizations();break;case 15:shuffle_customizations();break;case 16:return allocation_index(find_matching_customization(input,x,y));case 17:purge_all_custom_entries();break;case 18:purge_custom_entries(x);break;case 19:dump_all_glyphids((FILE*)1);break;case 20:wizcustom_glyphids(x);break;case 21:return parse_id(x?input:0,&request);case 22:return glyph_find_core(input,&request);case 23:clear_all_glyphmap_colors();break;case 24:reset_customcolors();break;case 25:to_custom_symset_entry_callback(x,&request);break;}return 0;}
void probe_color(uint32 color){request.color=color;request.unicode_val=input;}
char*probe_trace(void){return tracebuf;}char*probe_dump(void){return dumpbuf;}
char*probe_snapshot(void){char*p=snapshotbuf;int i,j,k;
#define APP(...) p+=sprintf(p,__VA_ARGS__)
APP("alloc:%d/%d/%d/%zu;format:%d;callbacks:%d;extra:%d;request:%u/%d/%d/%d/%u/%u;flags:%d/%d/%d/%d;",allocs,frees,dups,totalbytes,nformats,callback_count,extra,(unsigned)request.findtype,request.val,request.loadsyms_offset,request.loadsyms_count,request.color,(unsigned)request.restype,iflags.customcolors,iflags.customsymbols,iflags.pending_customizations,gc.currentgraphics);
for(i=0;i<NUM_GRAPHICS+1;i++)for(j=0;j<custom_count;j++){struct symset_customization*c=&gs.sym_customizations[i][j];struct customization_detail*q;APP("c%d/%d:%d:%d:%s:",i,j,c->custtype,c->count,c->customization_name?c->customization_name:"");for(q=c->details;q;q=q->next){APP("%d/%d/%d/",allocation_index(q),allocation_index(q->next),q==c->details_end);if(c->custtype==custom_ureps)APP("%d/U%u/%s,",q->content.urep.glyphidx,q->content.urep.u.utf32ch,q->content.urep.u.utf8str?(char*)q->content.urep.u.utf8str:"");else if(c->custtype==custom_nhcolor)APP("%d/C%u,",q->content.ccolor.glyphidx,q->content.ccolor.nhcolor);else APP("S%u,",q->content.sym.val);}APP(";");}
APP("maps:");for(k=0;k<MAX_GLYPH;k++)if(glyphmap[k].customcolor||glyphmap[k].color256idx||glyphmap[k].u){APP("%d/%u/%u/",k,glyphmap[k].customcolor,glyphmap[k].color256idx);if(glyphmap[k].u)APP("%d/U%u/%s;",allocation_index(glyphmap[k].u),glyphmap[k].u->utf32ch,glyphmap[k].u->utf8str?(char*)glyphmap[k].u->utf8str:"");else APP("0;");}return snapshotbuf;
#undef APP
}
long probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return SIZE(teleport_glyphs_layout);}
const char*probe_layout_name(int i){return teleport_glyphs_layout[i].name;}
long probe_layout_value(int i){return teleport_glyphs_layout[i].value;}
int probe_loadsyms_count(void){return SIZE(loadsyms);}
const char*probe_loadsyms_name(int i){return loadsyms[i].name;}
int probe_loadsyms_range(int i){return loadsyms[i].range;}
/* Optimized typed storage witness: C reads bytes written by JS; no const mirror. */
long probe_private(int slot,int field){
#ifdef TELEPORT_REFERENCE_TU
 const struct find_struct*p=slot==0?&glyphcache_find:slot==1?&to_custom_symbol_find:&zero_find;
#else
 const struct teleport_glyphs_find*p=teleport_glyphs_find_backing(slot);
#endif
 return field==0?p->val:field==1?p->color:field==2?p->findtype:field==3?p->restype:!!p->callback;
}
long probe_backing(int slot,int field,long value){void*p=teleport_glyphs_find_backing(slot);teleport_glyphs_set(0,field,p,value);return teleport_glyphs_get(0,field,p);}
