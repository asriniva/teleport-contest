/* Typed ABI/header/dependency access only: no original GETPOS algorithms. */
#include "hack.h"
extern const char what_is_a_location[];
DISABLE_WARNING_FORMAT_NONLITERAL
const void*teleport_getpos_global(int i){switch(i){case 0:return &u;case 1:return &levl[0][0];case 2:return &gg;case 3:return &gw.wsettings.map_frame_color;case 4:return &iflags;case 5:return gc.Cmd.spkeys;case 6:return gs.showsyms;case 7:return defsyms;case 8:return &gi.in_doagain;case 10:return &cg.zeroany;case 11:return &nul_glyphinfo;case 12:return quitchars;case 13:return what_is_a_location;default:return 0;}}
int teleport_getpos_flag(int i){switch(i){case 0:return flags.help;case 1:return flags.verbose;case 2:return svl.level.flags.hero_memory;case 3:return WIN_MAP;case 4:return WIN_MESSAGE;default:return 0;}}
static char teleport_getpos_buf[30],teleport_getpos_screen_fmt[16];
void*teleport_getpos_static_buffer(int i){return i?teleport_getpos_screen_fmt:teleport_getpos_buf;}
int teleport_getpos_trap_bit(struct trap*t,int i){return i?t->tseen:t->ttyp;}
int teleport_getpos_cansee(coordxy x,coordxy y){return !!cansee(x,y);}
int teleport_getpos_glyph_macro(int i,int g){switch(i){case 0:return !!glyph_is_cmap(g);case 1:return !!glyph_is_monster(g);case 2:return !!glyph_is_object(g);case 3:return !!glyph_is_nothing(g);case 4:return !!glyph_is_unexplored(g);case 5:return !!is_cmap_room(g);case 6:return !!is_cmap_furniture(g);case 7:return !!is_cmap_wall(g);case 8:return !!is_cmap_corr(g);case 9:return !!is_cmap_water(g);case 10:return !!is_cmap_lava(g);case 11:return !!is_cmap_door(g);case 12:return !!is_cmap_drawbridge(g);case 13:return !!is_cmap_trap(g);case 14:return !!is_cmap_engraving(g);default:return 0;}}
void teleport_getpos_call_hilite(void(*f)(boolean),boolean b){f(b);}
boolean teleport_getpos_call_valid(boolean(*f)(coordxy,coordxy),coordxy x,coordxy y){return f(x,y);}
void*teleport_getpos_command_token(int i){switch(i){case 0:return do_move_west;case 1:return do_move_south;case 2:return do_move_north;case 3:return do_move_east;case 4:return do_run_west;case 5:return do_run_south;case 6:return do_run_north;case 7:return do_run_east;case 8:return do_run;case 9:return do_rush;default:return 0;}}
char teleport_getpos_cmd_from_func(int(*f)(void)){return cmd_from_func(f);}
int teleport_getpos_screen_description(const coord*p,boolean b,int s,char*buf,const char**first,struct permonst**pm){return do_screen_description(*p,b,s,buf,first,pm);}
/* Stable C callback adapters reach the original JS function boundaries. */
extern int teleport_getpos_cmp_coord_distu(const void*,const void*);
extern int teleport_getpos_gloc_filter_floodfill_matcharea(coordxy,coordxy);
void teleport_getpos_qsort(void*p,size_t n,size_t z){qsort(p,n,z,teleport_getpos_cmp_coord_distu);}
void teleport_getpos_set_floodfill_callback(void){set_selection_floodfillchk(teleport_getpos_gloc_filter_floodfill_matcharea);}
winid teleport_getpos_create_window(int t){return create_nhwindow(t);}
void teleport_getpos_putstr(winid w,int a,const char*s){putstr(w,a,s);}
void teleport_getpos_display_window(winid w,boolean b){display_nhwindow(w,b);}
void teleport_getpos_destroy_window(winid w){destroy_nhwindow(w);}
void teleport_getpos_clear_window(winid w){clear_nhwindow(w);}
void teleport_getpos_start_menu(winid w,unsigned long b){start_menu(w,b);}
void teleport_getpos_end_menu(winid w,const char*s){end_menu(w,s);}
void teleport_getpos_curs(winid w,int x,int y){curs(w,x,y);}
void teleport_getpos_cliparound(int x,int y){cliparound(x,y);}
void teleport_getpos_free(void*p){free(p);}
/* Actual native varargs with fixed typed shapes used by this source file. */
#define GETPOS_ABI_STR(v) ((const char*)(uintptr_t)(v))
#define GETPOS_ABI_INT(v) ((int)(v))
#define GETPOS_ABI_FORMAT(...) do{if(kind)nh_snprintf(caller?"getpos_menu":"getpos_help",line,out,cap,fmt,##__VA_ARGS__);else sprintf(out,fmt,##__VA_ARGS__);}while(0)
void teleport_getpos_format(int kind,int caller,int line,char*out,size_t cap,const char*fmt,int shape,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){switch(shape){case 0:GETPOS_ABI_FORMAT((char*)0);break;case 1:GETPOS_ABI_FORMAT(GETPOS_ABI_STR(a));break;case 2:GETPOS_ABI_FORMAT(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b));break;case 3:GETPOS_ABI_FORMAT(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b),GETPOS_ABI_STR(c));break;case 4:GETPOS_ABI_FORMAT(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b),GETPOS_ABI_STR(c),GETPOS_ABI_STR(d));break;case 5:GETPOS_ABI_FORMAT(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b),GETPOS_ABI_STR(c),GETPOS_ABI_STR(d),GETPOS_ABI_STR(e));break;case 6:GETPOS_ABI_FORMAT(GETPOS_ABI_INT(a));break;case 7:GETPOS_ABI_FORMAT(GETPOS_ABI_INT(a),GETPOS_ABI_INT(b));break;case 8:GETPOS_ABI_FORMAT(GETPOS_ABI_INT(a),GETPOS_ABI_STR(b));break;case 9:GETPOS_ABI_FORMAT(GETPOS_ABI_INT(a),GETPOS_ABI_STR(b),GETPOS_ABI_STR(c));break;}}
#define GETPOS_ABI_MESSAGE(...) do{if(kind==0)pline(fmt,##__VA_ARGS__);else if(kind==1)You(fmt,##__VA_ARGS__);else custompline(flags,fmt,##__VA_ARGS__);}while(0)
void teleport_getpos_message(int kind,unsigned flags,const char*fmt,int shape,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){switch(shape){case 0:GETPOS_ABI_MESSAGE((char*)0);break;case 1:GETPOS_ABI_MESSAGE(GETPOS_ABI_STR(a));break;case 2:GETPOS_ABI_MESSAGE(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b));break;case 3:GETPOS_ABI_MESSAGE(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b),GETPOS_ABI_STR(c));break;case 4:GETPOS_ABI_MESSAGE(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b),GETPOS_ABI_STR(c),GETPOS_ABI_STR(d));break;case 5:GETPOS_ABI_MESSAGE(GETPOS_ABI_STR(a),GETPOS_ABI_STR(b),GETPOS_ABI_STR(c),GETPOS_ABI_STR(d),GETPOS_ABI_STR(e));break;case 6:GETPOS_ABI_MESSAGE(GETPOS_ABI_INT(a));break;}}

int teleport_getpos_monnum_to_glyph(int n,int g){return monnum_to_glyph(n,g);}
int teleport_getpos_objnum_to_glyph(int n){return objnum_to_glyph(n);}
#undef GETPOS_ABI_STR
#undef GETPOS_ABI_INT
#undef GETPOS_ABI_FORMAT
#undef GETPOS_ABI_MESSAGE
RESTORE_WARNING_FORMAT_NONLITERAL

static char teleport_getpos_literals[2272];
void*teleport_getpos_literal_storage(void){return teleport_getpos_literals;}
size_t teleport_getpos_literal_capacity(void){return sizeof teleport_getpos_literals;}
