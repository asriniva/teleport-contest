/* Native backing, field ABI and actual dependencies; all symbols policy is JS. */
#include "tu-symbols-support.h"
#ifndef TELEPORT_REFERENCE_SYMBOLS
const char *const known_handling[7]={0};
const char *const known_restrictions[3]={0};
const struct symparse loadsyms[197]={0};
struct _savedsym *saved_symbols;
void (*decgraphics_mode_callback)(void)=0;
void (*utf8graphics_mode_callback)(void)=0;
#endif
extern const uchar def_r_oc_syms[MAXOCLASSES];
void *teleport_symbols_global(int index){switch(index){case 0:return &gs;case 1:return &go;case 2:return &gp;case 3:return &gr;case 4:return &gc;case 5:return (void*)&cg;case 6:return &u;case 7:return (void*)defsyms;case 8:return (void*)def_oc_syms;case 9:return (void*)def_monsyms;case 10:return (void*)def_warnsyms;case 11:return (void*)def_r_oc_syms;}return 0;}
void *teleport_symbols_storage(int index){switch(index){case 0:return (void*)loadsyms;case 1:return (void*)known_handling;case 2:return (void*)known_restrictions;case 3:return &saved_symbols;}return 0;}
uintptr_t teleport_symbols_callback(int index){return index?(uintptr_t)utf8graphics_mode_callback:(uintptr_t)decgraphics_mode_callback;}
void teleport_symbols_invoke(uintptr_t callback){((void(*)(void))callback)();}
unsigned teleport_symbols_bit(struct symsetentry *p,int i){switch(i){case 0:return p->nocolor;case 1:return p->primary;case 2:return p->rogue;case 3:return p->explicitly;}return 0;}
void teleport_symbols_set_bit(struct symsetentry *p,int i,unsigned v){switch(i){case 0:p->nocolor=v;break;case 1:p->primary=v;break;case 2:p->rogue=v;break;case 3:p->explicitly=v;break;}}
void *teleport_symbols_rogue_level(void){return &rogue_level;}
const char *teleport_symbols_file_name(void){return SYMBOLS;}
const glyph_info *teleport_symbols_nul_glyph(void){return &nul_glyphinfo;}
void *teleport_symbols_string_alloc(size_t n){return malloc(n);}
void teleport_symbols_free(void *p){free(p);}
winid teleport_symbols_create(int kind){return create_nhwindow(kind);}
void teleport_symbols_start(winid w,unsigned long behavior){start_menu(w,behavior);}
void teleport_symbols_end(winid w,const char *s){end_menu(w,s);}
void teleport_symbols_destroy(winid w){destroy_nhwindow(w);}
void teleport_symbols_preference(const char *s){preference_update(s);}
void teleport_symbols_format_i(char *out,const char *fmt,int n){Sprintf(out,fmt,n);}
void teleport_symbols_format_p(char *out,const char *fmt,const char *p){Sprintf(out,fmt,p);}
void teleport_symbols_format_pp(char *out,const char *fmt,const char *p,const char *q){Sprintf(out,fmt,p,q);}
void teleport_symbols_format_ppp(char *out,const char *fmt,const char *p,const char *q,const char *r){Sprintf(out,fmt,p,q,r);}
void teleport_symbols_snprintf(char *out,size_t n,const char *fmt,const char *p,const char *q){nh_snprintf("parsesymbols",836,out,n,fmt,p,q);}
void teleport_symbols_error(const char *s){config_error_add("%s",s);}
void teleport_symbols_There(const char *fmt,const char *s){There(fmt,s);}
void teleport_symbols_pline(const char *fmt,const char *s){pline(fmt,s);}

int teleport_symbols_strcmpi(const char *a,const char *b){return strcmpi(a,b);}
