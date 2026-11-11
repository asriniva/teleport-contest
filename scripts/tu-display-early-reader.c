#include "hack.h"
extern const glyph_info nul_glyphinfo;
extern glyph_map glyphmap[9624];
extern const int zapcolors[8];
extern const int altarcolors[5];
extern const int explodecolors[7];
extern int wallcolors[5];
extern const seenV seenv_matrix[3][3];
extern glyph_map glyphmap[MAX_GLYPH];extern const seenV seenv_matrix[3][3];
extern void display_observe_startup(const void*,size_t);
__attribute__((constructor))static void display_early_reader(void){
display_observe_startup(&nul_glyphinfo,sizeof nul_glyphinfo);
display_observe_startup(&glyphmap,sizeof glyphmap);
display_observe_startup(&zapcolors,sizeof zapcolors);
display_observe_startup(&altarcolors,sizeof altarcolors);
display_observe_startup(&explodecolors,sizeof explodecolors);
display_observe_startup(&wallcolors,sizeof wallcolors);
display_observe_startup(&seenv_matrix,sizeof seenv_matrix);
}
