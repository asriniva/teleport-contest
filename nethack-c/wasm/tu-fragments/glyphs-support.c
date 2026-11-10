/* Typed records/globals/header macros/dependencies and zero-only ABI storage.
 * No GLYPHS algorithm, initializer catalogue, parser or cache fallback in C. */
#include "../../../scripts/tu-glyphs-layout.h"
#include <stdint.h>
extern const struct symparse loadsyms[];
extern glyph_map glyphmap[MAX_GLYPH];
extern struct enum_dump monsdump[];
#ifdef TELEPORT_GLYPHS_VALIDATE_SOURCE
 _Static_assert(res_nothing==0&&res_dump_glyphids==1&&res_fill_cache==2,"source result enum values changed");
 _Static_assert(find_nothing==0&&find_pm==1&&find_oc==2&&find_cmap==3&&find_glyph==4,"source find enum values changed");
 _Static_assert(sizeof nonzero_black==8,"source nonzero_black signed long width changed");
 typedef struct find_struct teleport_glyphs_actual_find;
 typedef struct glyphid_cache_t teleport_glyphs_actual_cache;
 _Static_assert(sizeof(struct find_struct)==sizeof(struct teleport_glyphs_find),"actual find_struct ABI changed");
 _Static_assert(sizeof(struct glyphid_cache_t)==sizeof(struct teleport_glyphs_cache),"actual glyph cache ABI changed");
_Static_assert(offsetof(struct find_struct,findtype)==offsetof(struct teleport_glyphs_find,findtype),"find_struct.findtype offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->findtype)==sizeof(((struct teleport_glyphs_find*)0)->findtype),"find_struct.findtype width changed");
_Static_assert(offsetof(struct find_struct,val)==offsetof(struct teleport_glyphs_find,val),"find_struct.val offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->val)==sizeof(((struct teleport_glyphs_find*)0)->val),"find_struct.val width changed");
_Static_assert(offsetof(struct find_struct,loadsyms_offset)==offsetof(struct teleport_glyphs_find,loadsyms_offset),"find_struct.loadsyms_offset offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->loadsyms_offset)==sizeof(((struct teleport_glyphs_find*)0)->loadsyms_offset),"find_struct.loadsyms_offset width changed");
_Static_assert(offsetof(struct find_struct,loadsyms_count)==offsetof(struct teleport_glyphs_find,loadsyms_count),"find_struct.loadsyms_count offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->loadsyms_count)==sizeof(((struct teleport_glyphs_find*)0)->loadsyms_count),"find_struct.loadsyms_count width changed");
_Static_assert(offsetof(struct find_struct,extraval)==offsetof(struct teleport_glyphs_find,extraval),"find_struct.extraval offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->extraval)==sizeof(((struct teleport_glyphs_find*)0)->extraval),"find_struct.extraval width changed");
_Static_assert(offsetof(struct find_struct,color)==offsetof(struct teleport_glyphs_find,color),"find_struct.color offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->color)==sizeof(((struct teleport_glyphs_find*)0)->color),"find_struct.color width changed");
_Static_assert(offsetof(struct find_struct,unicode_val)==offsetof(struct teleport_glyphs_find,unicode_val),"find_struct.unicode_val offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->unicode_val)==sizeof(((struct teleport_glyphs_find*)0)->unicode_val),"find_struct.unicode_val width changed");
_Static_assert(offsetof(struct find_struct,callback)==offsetof(struct teleport_glyphs_find,callback),"find_struct.callback offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->callback)==sizeof(((struct teleport_glyphs_find*)0)->callback),"find_struct.callback width changed");
_Static_assert(offsetof(struct find_struct,restype)==offsetof(struct teleport_glyphs_find,restype),"find_struct.restype offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->restype)==sizeof(((struct teleport_glyphs_find*)0)->restype),"find_struct.restype width changed");
_Static_assert(offsetof(struct find_struct,reserved)==offsetof(struct teleport_glyphs_find,reserved),"find_struct.reserved offset changed");
_Static_assert(sizeof(((struct find_struct*)0)->reserved)==sizeof(((struct teleport_glyphs_find*)0)->reserved),"find_struct.reserved width changed");
_Static_assert(offsetof(struct glyphid_cache_t,glyphnum)==offsetof(struct teleport_glyphs_cache,glyphnum),"glyphid_cache_t.glyphnum offset changed");
_Static_assert(sizeof(((struct glyphid_cache_t*)0)->glyphnum)==sizeof(((struct teleport_glyphs_cache*)0)->glyphnum),"glyphid_cache_t.glyphnum width changed");
_Static_assert(offsetof(struct glyphid_cache_t,id)==offsetof(struct teleport_glyphs_cache,id),"glyphid_cache_t.id offset changed");
_Static_assert(sizeof(((struct glyphid_cache_t*)0)->id)==sizeof(((struct teleport_glyphs_cache*)0)->id),"glyphid_cache_t.id width changed");
_Static_assert(((__typeof__(((struct find_struct*)0)->findtype))-1<0)==0,"source enum signedness changed");
_Static_assert(((__typeof__(((struct find_struct*)0)->restype))-1<0)==0,"source enum signedness changed");
#else
 typedef struct teleport_glyphs_find teleport_glyphs_actual_find;
 typedef struct teleport_glyphs_cache teleport_glyphs_actual_cache;
 extern void teleport_glyphs_to_custom_callback(int,struct teleport_glyphs_find*);
#endif
static teleport_glyphs_actual_find teleport_glyphs_find_storage[3];
void*teleport_glyphs_find_backing(int i){return &teleport_glyphs_find_storage[i];}
void*teleport_glyphs_callback_address(void){
#ifdef TELEPORT_GLYPHS_VALIDATE_SOURCE
 return(void*)to_custom_symset_entry_callback;
#else
 return(void*)teleport_glyphs_to_custom_callback;
#endif
}
void teleport_glyphs_callback(void*f,int glyph,void*what){((void(*)(int,teleport_glyphs_actual_find*))f)(glyph,what);}
long teleport_glyphs_get(int kind,int field,void*p){switch(kind){
case 0:{teleport_glyphs_actual_find*v=p;switch(field){
case 0:return(long)v->findtype;
case 1:return(long)v->val;
case 2:return(long)v->loadsyms_offset;
case 3:return(long)v->loadsyms_count;
case 4:return(long)(intptr_t)v->extraval;
case 5:return(long)v->color;
case 6:return(long)(intptr_t)v->unicode_val;
case 7:return(long)(intptr_t)v->callback;
case 8:return(long)v->restype;
case 9:return(long)(intptr_t)v->reserved;
}break;}
case 1:{teleport_glyphs_actual_cache*v=p;switch(field){
case 0:return(long)v->glyphnum;
case 1:return(long)(intptr_t)v->id;
}break;}
case 2:{struct customization_detail*v=p;switch(field){
case 0:return(long)(intptr_t)v->next;
case 1:return(long)v->content.urep.glyphidx;
case 2:return(long)v->content.urep.u.utf32ch;
case 3:return(long)(intptr_t)v->content.urep.u.utf8str;
case 4:return(long)v->content.ccolor.glyphidx;
case 5:return(long)v->content.ccolor.nhcolor;
case 6:return(long)(intptr_t)v->content.sym.symparse;
case 7:return(long)v->content.sym.val;
}break;}
case 3:{glyph_map*v=p;switch(field){
case 0:return(long)v->customcolor;
case 1:return(long)v->color256idx;
case 2:return(long)(intptr_t)v->u;
}break;}
case 4:{struct unicode_representation*v=p;switch(field){
case 0:return(long)v->utf32ch;
case 1:return(long)(intptr_t)v->utf8str;
}break;}
case 5:{struct symset_customization*v=p;switch(field){
case 0:return(long)(intptr_t)v->customization_name;
case 1:return(long)v->count;
case 2:return(long)v->custtype;
case 3:return(long)(intptr_t)v->details;
case 4:return(long)(intptr_t)v->details_end;
}break;}
case 6:{struct symsetentry*v=p;switch(field){
case 0:return(long)(intptr_t)v->name;
case 1:return(long)v->handling;
}break;}
case 7:{struct objclass*v=p;switch(field){
case 0:return(long)v->oc_descr_idx;
}break;}
case 8:{const struct symparse*v=p;switch(field){
case 0:return(long)v->range;
case 1:return(long)v->idx;
case 2:return(long)(intptr_t)v->name;
}break;}
case 9:{struct enum_dump*v=p;switch(field){
case 0:return(long)v->val;
case 1:return(long)(intptr_t)v->nm;
}break;}
case 10:{struct objdescr*v=p;switch(field){
case 0:return(long)(intptr_t)v->oc_name;
case 1:return(long)(intptr_t)v->oc_descr;
}break;}
case 11:{struct permonst*v=p;switch(field){
case 0:return(long)v->mlet;
}break;}
}return 0;}
void teleport_glyphs_set(int kind,int field,void*p,long value){switch(kind){
case 0:{teleport_glyphs_actual_find*v=p;switch(field){
case 0:v->findtype=value;return;
case 1:v->val=value;return;
case 2:v->loadsyms_offset=value;return;
case 3:v->loadsyms_count=value;return;
case 4:v->extraval=(void*)(intptr_t)value;return;
case 5:v->color=value;return;
case 6:v->unicode_val=(void*)(intptr_t)value;return;
case 7:v->callback=(void(*)(int,teleport_glyphs_actual_find*))(intptr_t)value;return;
case 8:v->restype=value;return;
case 9:v->reserved=(void*)(intptr_t)value;return;
}break;}
case 1:{teleport_glyphs_actual_cache*v=p;switch(field){
case 0:v->glyphnum=value;return;
case 1:v->id=(void*)(intptr_t)value;return;
}break;}
case 2:{struct customization_detail*v=p;switch(field){
case 0:v->next=(void*)(intptr_t)value;return;
case 1:v->content.urep.glyphidx=value;return;
case 2:v->content.urep.u.utf32ch=value;return;
case 3:v->content.urep.u.utf8str=(void*)(intptr_t)value;return;
case 4:v->content.ccolor.glyphidx=value;return;
case 5:v->content.ccolor.nhcolor=value;return;
case 6:v->content.sym.symparse=(void*)(intptr_t)value;return;
case 7:v->content.sym.val=value;return;
}break;}
case 3:{glyph_map*v=p;switch(field){
case 0:v->customcolor=value;return;
case 1:v->color256idx=value;return;
case 2:v->u=(void*)(intptr_t)value;return;
}break;}
case 4:{struct unicode_representation*v=p;switch(field){
case 0:v->utf32ch=value;return;
case 1:v->utf8str=(void*)(intptr_t)value;return;
}break;}
case 5:{struct symset_customization*v=p;switch(field){
case 0:v->customization_name=(void*)(intptr_t)value;return;
case 1:v->count=value;return;
case 2:v->custtype=value;return;
case 3:v->details=(void*)(intptr_t)value;return;
case 4:v->details_end=(void*)(intptr_t)value;return;
}break;}
case 6:{struct symsetentry*v=p;switch(field){
}break;}
case 7:{struct objclass*v=p;switch(field){
}break;}
case 8:{const struct symparse*v=p;switch(field){
}break;}
case 9:{struct enum_dump*v=p;switch(field){
}break;}
case 10:{struct objdescr*v=p;switch(field){
}break;}
case 11:{struct permonst*v=p;switch(field){
}break;}
}}
long teleport_glyphs_global(int i){switch(i){case 0:return gs.symset_which_set;case 1:return iflags.customsymbols;case 2:return iflags.customcolors;case 3:return iflags.pending_customizations;case 4:return gc.currentgraphics;}return 0;}
void teleport_glyphs_set_global(int i,long v){switch(i){case 0:gs.symset_which_set=v;break;case 1:iflags.customsymbols=v;break;case 2:iflags.customcolors=v;break;case 3:iflags.pending_customizations=v;break;case 4:gc.currentgraphics=v;break;}}
void*teleport_glyphs_element(int kind,int i,int j){switch(kind){case 0:return &glyphmap[i];case 1:return &gs.sym_customizations[i][j];case 2:return &gs.symset[i];case 3:return &objects[i];case 4:return(void*)&loadsyms[i];case 5:return &monsdump[i];case 6:return &obj_descr[i];case 7:return &mons[i];}return 0;}
int teleport_glyphs_header(int kind,int glyph){switch(kind){case 0:return glyph_is_body(glyph);case 1:return glyph_is_body_piletop(glyph);case 2:return glyph_is_cmap(glyph);case 3:return glyph_is_cmap_a(glyph);case 4:return glyph_is_cmap_altar(glyph);case 5:return glyph_is_cmap_b(glyph);case 6:return glyph_is_cmap_c(glyph);case 7:return glyph_is_cmap_gehennom(glyph);case 8:return glyph_is_cmap_knox(glyph);case 9:return glyph_is_cmap_main(glyph);case 10:return glyph_is_cmap_mines(glyph);case 11:return glyph_is_cmap_sokoban(glyph);case 12:return glyph_is_cmap_zap(glyph);case 13:return glyph_is_detected_female_monster(glyph);case 14:return glyph_is_detected_male_monster(glyph);case 15:return glyph_is_explosion(glyph);case 16:return glyph_is_fem_statue(glyph);case 17:return glyph_is_fem_statue_piletop(glyph);case 18:return glyph_is_female_pet(glyph);case 19:return glyph_is_invisible(glyph);case 20:return glyph_is_male_pet(glyph);case 21:return glyph_is_male_statue(glyph);case 22:return glyph_is_male_statue_piletop(glyph);case 23:return glyph_is_monster(glyph);case 24:return glyph_is_normal_female_monster(glyph);case 25:return glyph_is_normal_male_monster(glyph);case 26:return glyph_is_normal_piletop_obj(glyph);case 27:return glyph_is_nothing(glyph);case 28:return glyph_is_object(glyph);case 29:return glyph_is_ridden_female_monster(glyph);case 30:return glyph_is_ridden_male_monster(glyph);case 31:return glyph_is_statue(glyph);case 32:return glyph_is_swallow(glyph);case 33:return glyph_is_unexplored(glyph);case 34:return glyph_is_warning(glyph);case 35:return glyph_to_body_corpsenm(glyph);case 36:return glyph_to_explosion(glyph);case 37:return glyph_to_mon(glyph);case 38:return glyph_to_obj(glyph);case 39:return glyph_to_statue_corpsenm(glyph);case 40:return glyph_to_swallow(glyph);}return 0;}
void teleport_glyphs_assert(int b){if(!b)__assert_fail("idx >= 0 && idx < NUM_GRAPHICS","glyphs.c",66,"to_custom_symset_entry_callback");}
void teleport_glyphs_panic(const char*f){panic("%s",f);}
void teleport_glyphs_config_error(const char*f){config_error_add("%s",f);}
void teleport_glyphs_snprintf(const char*fn,int line,char*out,size_t size,const char*f,const char*a,const char*b){nh_snprintf(fn,line,out,size,f,a,b);}
void teleport_glyphs_snprintf_int(const char*fn,int line,char*out,size_t size,const char*f,const char*a,int b){nh_snprintf(fn,line,out,size,f,a,b);}
void teleport_glyphs_fprintf(FILE*fp,const char*f,int glyph,const char*id){(void)fprintf(fp,f,glyph,id);}
void teleport_glyphs_dep_free(void * a0){free(a0);}
void * teleport_glyphs_dep_memchr(const void * a0,int a1,size_t a2){return memchr(a0,a1,a2);}
int teleport_glyphs_dep_strcmp(const char * a0,const char * a1){return strcmp(a0,a1);}
char * teleport_glyphs_dep_dupstr(const char * a0){return dupstr(a0);}
long * teleport_glyphs_dep_alloc(unsigned int a0){return alloc(a0);}
int teleport_glyphs_dep_unicodeval_to_utf8str(int a0,uint8 * a1,size_t a2){return unicodeval_to_utf8str(a0,a1,a2);}
int32_t teleport_glyphs_dep_rgbstr_to_int32(const char * a0){return rgbstr_to_int32(a0);}
int teleport_glyphs_dep_add_custom_urep_entry(const char * a0,int a1,uint32 a2,const uint8 * a3,enum graphics_sets a4){return add_custom_urep_entry(a0,a1,a2,a3,a4);}
int teleport_glyphs_dep_set_map_customcolor(glyph_map * a0,uint32 a1){return set_map_customcolor(a0,a1);}
int teleport_glyphs_dep_unicode_val(const char * a0){return unicode_val(a0);}
int teleport_glyphs_dep_set_map_u(glyph_map * a0,uint32 a1,const uint8 * a2){return set_map_u(a0,a1,a2);}
void teleport_glyphs_dep_wizcustom_callback(winid a0,int a1,char * a2){wizcustom_callback(a0,a1,a2);}
void * teleport_glyphs_dep_memcpy(void * a0,const void * a1,size_t a2){return memcpy(a0,a1,a2);}
void * teleport_glyphs_dep_memset(void * a0,int a1,size_t a2){return memset(a0,a1,a2);}
char * teleport_glyphs_dep_strcpy(char * a0,const char * a1){return strcpy(a0,a1);}
char * teleport_glyphs_dep_strcat(char * a0,const char * a1){return strcat(a0,a1);}
static char teleport_glyphs_literals[909];
void*teleport_glyphs_literal_storage(void){return teleport_glyphs_literals;}
size_t teleport_glyphs_literal_capacity(void){return sizeof teleport_glyphs_literals;}

int teleport_glyphs_strcmpi(const char*a,const char*b){return strcmpi(a,b);}
