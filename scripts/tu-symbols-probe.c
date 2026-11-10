/* Actual Symbols TU with controlled native file/UI/glyph boundary callbacks. */
#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef malloc
#undef free
extern void *malloc(size_t);
extern void free(void*);
__typeof__(gs) gs;__typeof__(go) go;__typeof__(gp) gp;__typeof__(gr) gr;__typeof__(gc) gc;
struct you u;__typeof__(svd) svd;
const struct const_globals cg={.zeroany={.a_ulong=0xa5a5a5a500000000UL}};
__typeof__(windowprocs) windowprocs;
const glyph_info nul_glyphinfo={0};
static int opts[32],frees,reads,cache;
static char input[8192],tracebuf[262144],statebuf[65536];
static strbuf_t sbuf;
static void *growth,*freed[16384];static unsigned nfreed;
struct allocated {void*p;size_t size;}static allocated[16384];static unsigned nallocated;
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
static void callback(int stage){if(opts[20]==stage){opts[20]=0;append("nested:%u;",get_othersym(0,PRIMARYSET));}if(opts[21]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();append("grow:%d;",stage);}}
void *teleport_probe_malloc(size_t n){void *p=malloc(n);if(p){memset(p,0xa5,n);for(unsigned i=0;i<nfreed;i++)if(freed[i]==p)freed[i]=NULL;}if(nallocated<16384)allocated[nallocated++]=(struct allocated){p,n};return p;}
void teleport_probe_free(void *p){if(!p)return;size_t size=0;for(unsigned i=nallocated;i-->0;)if(allocated[i].p==p){size=allocated[i].size;break;}append("free:%lu;",(unsigned long)size);if(nfreed<16384)freed[nfreed++]=p;frees++;callback(9);free(p);}
static boolean dead(void*p){for(unsigned i=0;i<nfreed;i++)if(freed[i]==p)return TRUE;return FALSE;}
void panic(const char *fmt,...){abort();}
#define MSG(name) void name(const char *fmt,...){char b[BUFSZ*4];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#name ":%s;",b);}
MSG(config_error_add) MSG(pline) MSG(There)
void reset_glyphmap(enum glyphmap_change_triggers why){append("reset:%d;",why);callback(1);}
void free_all_glyphmap_u(void){append("free-unicode;");callback(2);}
void purge_custom_entries(enum graphics_sets set){append("purge:%d;",set);callback(3);}
void clear_all_glyphmap_colors(void){append("clear-colors;");callback(4);}
int match_glyph(char *s){append("match-glyph:%s;",s);callback(5);return opts[1];}
int sym_val(const char *s){append("sym-val:%s;",s);callback(6);return opts[2];}
int glyphrep_to_custom_map_entries(const char *s,int *out){append("glyphrep:%s:%d;",s,1);*out=opts[3];callback(7);return opts[4];}
void apply_customizations(enum graphics_sets set,enum do_customizations mode){append("apply:%d:%d;",set,mode);callback(8);}
boolean glyphid_cache_status(void){append("cache?:%d;",cache);return cache;}
void fill_glyphid_cache(void){append("fill-cache;");cache=1;}
void free_glyphid_cache(void){append("free-cache;");cache=0;}
boolean on_level(d_level *a,d_level *b){append("on-level:%d:%d:%d:%d;",a->dnum,a->dlevel,b->dnum,b->dlevel);return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
static void dec_callback(void){append("dec-callback;");callback(10);}
static void utf_callback(void){append("utf-callback;");callback(11);}
static winid make_window(int kind){append("create:%d;",kind);return 31;}
static void start_window(winid w,unsigned long flags){append("start:%d:%lu;",w,flags);}
void add_menu(winid w,const glyph_info *g,const anything *a,char ch,char group,int attr,int color,const char *s,unsigned flags){append("menu:%d:%d:%d:%d:%d:%d:%u:%s:bytes",w,a->a_int,ch,group,attr,color,flags,s);for(size_t i=0;i<sizeof *a;i++)append("%02x",((const unsigned char*)a)[i]);append(";");callback(12);}
static void end_window(winid w,const char *s){append("end:%d:%s;",w,s);}
int select_menu(winid w,int how,menu_item **out){append("select:%d:%d:%d;",w,how,opts[5]);if(opts[5]>0){*out=teleport_probe_malloc(opts[5]*sizeof **out);memset(*out,0,opts[5]*sizeof **out);(*out)[0].item.a_int=opts[6];if(opts[5]>1)(*out)[1].item.a_int=opts[7];}callback(13);return opts[5];}
static void destroy_window(winid w){append("destroy:%d;",w);}
static void preference(const char *s){append("preference:%s;",s);callback(14);}
int read_sym_file(int which){append("read-file:%d:%d;",which,++reads);if(!opts[0]||(opts[8]&&reads>=opts[8]))return 0;FILE *fp=fopen("/symbols-probe.txt","r");if(!fp)return 0;char line[BUFSZ];gc.chosen_symset_start=gc.chosen_symset_end=FALSE;while(fgets(line,sizeof line,fp))proc_symset_line(line);fclose(fp);callback(15);return opts[0];}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/symbols.c"
#undef free
#else
extern void teleport_symbols_test_add(const char*,const char*,int);
extern void *teleport_symbols_test_find(const char*,int);
#define savedsym_add teleport_symbols_test_add
#define savedsym_find teleport_symbols_test_find
#endif
#include "tu-symbols-layout.h"
static void cleanup(void){struct symsetentry *p=gs.symset_list,*n;while(p){n=p->next;free(p->name);free(p->desc);free(p);p=n;}gs.symset_list=NULL;for(int i=0;i<NUM_GRAPHICS;i++){free(gs.symset[i].name);free(gs.symset[i].desc);}struct teleport_saved_sym *q=(void*)saved_symbols,*r;if(q&&!dead(q))while(q){r=q->next;free(q->name);free(q->val);free(q);q=r;}saved_symbols=NULL;}
void probe_reset(void){static boolean first=TRUE;if(!first)cleanup();first=FALSE;free(growth);growth=NULL;if(sbuf.str&&sbuf.str!=sbuf.buf)free(sbuf.str);memset(&sbuf,0,sizeof sbuf);memset(&gs,0,sizeof gs);memset(&go,0,sizeof go);memset(&gp,0,sizeof gp);memset(&gr,0,sizeof gr);memset(&gc,0,sizeof gc);memset(&u,0,sizeof u);memset(&svd,0,sizeof svd);memset(opts,0,sizeof opts);memset(input,0,sizeof input);memset((void*)&windowprocs,0,sizeof windowprocs);windowprocs.win_create_nhwindow=make_window;windowprocs.win_start_menu=start_window;windowprocs.win_end_menu=end_window;windowprocs.win_destroy_nhwindow=destroy_window;windowprocs.win_preference_update=preference;decgraphics_mode_callback=dec_callback;utf8graphics_mode_callback=utf_callback;u.uz.dnum=1;u.uz.dlevel=2;rogue_level.dnum=3;rogue_level.dlevel=4;opts[0]=1;opts[1]=1;opts[2]=37;opts[3]=123;opts[4]=1;opts[5]=-1;frees=reads=cache=0;nfreed=0;tracebuf[0]=0;}
void probe_option(int k,int v){opts[k]=v;}
void probe_input(const char *s){memset(input,0,sizeof input);strncpy(input,s,sizeof input-1);}
void probe_file(const char *s){FILE *fp=fopen("/symbols-probe.txt","w");fputs(s,fp);fclose(fp);}
void probe_symset(int set,int field,const char *s,int value){switch(field){case 0:free(gs.symset[set].name);gs.symset[set].name=s?dupstr(s):NULL;break;case 1:free(gs.symset[set].desc);gs.symset[set].desc=s?dupstr(s):NULL;break;case 2:gs.symset[set].handling=value;break;case 3:gs.symset[set].nocolor=value;break;case 4:gs.symset[set].primary=value;break;case 5:gs.symset[set].rogue=value;break;case 6:gs.symset[set].explicitly=value;break;}}
void probe_global(int field,int value){switch(field){case 0:gc.currentgraphics=value;break;case 1:gc.chosen_symset_start=value;break;case 2:gc.chosen_symset_end=value;break;case 3:gs.symset_count=value;break;case 4:gs.symset_which_set=value;break;case 5:u.uz.dnum=value;break;case 6:u.uz.dlevel=value;break;case 7:decgraphics_mode_callback=value?dec_callback:NULL;break;case 8:utf8graphics_mode_callback=value?utf_callback:NULL;break;}}
void probe_symbol(int array,int index,int value){nhsym *p=array==0?gs.showsyms:array==1?gp.primary_syms:array==2?gr.rogue_syms:array==3?go.ov_primary_syms:go.ov_rogue_syms;p[index]=value;}
int probe_action(int op,int a,int b){const struct symparse *p;switch(op){case 0:init_symbols();break;case 1:init_showsyms();break;case 2:init_ov_rogue_symbols();break;case 3:init_ov_primary_symbols();break;case 4:return get_othersym(a,b);case 5:init_primary_symbols();break;case 6:init_rogue_symbols();break;case 7:assign_graphics(a);break;case 8:switch_symbols(a);break;case 9:update_ov_primary_symset(&loadsyms[a],b);break;case 10:update_ov_rogue_symset(&loadsyms[a],b);break;case 11:update_primary_symset(&loadsyms[a],b);break;case 12:update_rogue_symset(&loadsyms[a],b);break;case 13:clear_symsetentry(a,b);break;case 14:return symset_is_compatible(a,(unsigned long)(unsigned)b);case 15:return proc_symset_line(input);case 16:return parse_sym_line(input,a);case 17:set_symhandling(input,a);break;case 18:return load_symset(input,a);case 19:free_symsets();break;case 20:savedsym_free();break;case 21:return savedsym_find(input,a)!=NULL;case 22:savedsym_add(input,"value",a);break;case 23:savedsym_strbuf(&sbuf);break;case 24:return parsesymbols(input,a);case 25:p=match_sym(input);return p?(int)(p-loadsyms):-1;case 26:return do_symset(a);}return 0;}
unsigned long probe_compatible(int handling,unsigned long caps){return symset_is_compatible(handling,caps);}
void *probe_pointer(int kind,int i){switch(kind){case 0:return input;case 1:return (void*)&loadsyms[i];case 2:return &gs.symset[i];case 3:return &saved_symbols;case 4:return &sbuf;case 5:return (void*)known_handling;case 6:return (void*)known_restrictions;}return NULL;}
const char *probe_trace(void){return tracebuf;}
int probe_free_count(void){return frees;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_buffer(void){return sbuf.str;}
const char *probe_table_name(int table,int i){return table==0?known_handling[i]:table==1?known_restrictions[i]:loadsyms[i].name;}
int probe_table_field(int i,int field){return field?loadsyms[i].idx:loadsyms[i].range;}
const char *probe_snapshot(void){char *p=statebuf;p+=sprintf(p,"state:%d:%d:%d:%d:%d:%d:%d:%d:%d;",gc.currentgraphics,gc.chosen_symset_start,gc.chosen_symset_end,gs.symset_count,gs.symset_which_set,frees,reads,cache,saved_symbols!=NULL);for(int j=0;j<2;j++)p+=sprintf(p,"set%d:%s:%s:%d:%d:%d:%d:%d;",j,gs.symset[j].name?gs.symset[j].name:"<NULL>",gs.symset[j].desc?gs.symset[j].desc:"<NULL>",gs.symset[j].handling,gs.symset[j].nocolor,gs.symset[j].primary,gs.symset[j].rogue,gs.symset[j].explicitly);for(struct symsetentry *q=gs.symset_list;q;q=q->next)p+=sprintf(p,"list:%d:%s:%s:%d:%d:%d:%d:%d;",q->idx,q->name?q->name:"<NULL>",q->desc?q->desc:"<NULL>",q->handling,q->nocolor,q->primary,q->rogue,q->explicitly);struct teleport_saved_sym *q=(void*)saved_symbols;if(q&&dead(q))p+=sprintf(p,"saved:<freed>;");else for(;q;q=q->next)p+=sprintf(p,"saved:%d:%s:%s;",q->which_set,q->name,q->val);const nhsym *arrays[]={gs.showsyms,gp.primary_syms,gr.rogue_syms,go.ov_primary_syms,go.ov_rogue_syms};for(int j=0;j<5;j++){p+=sprintf(p,"a%d:",j);for(int i=0;i<SYM_MAX;i++)p+=sprintf(p,"%02x",arrays[j][i]);*p++=';';}*p=0;return statebuf;}
