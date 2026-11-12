/* Isolated OPTIONS oracle: original source only in reference; world/UI dependencies are controlled native callbacks. */
#include "hack.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <emscripten.h>
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/options.c"
#define TELEPORT_OPTIONS_ORIGINAL_INCLUDED
#define TELEPORT_OPTIONS_VALIDATE_ORIGINAL
#endif
#include "tu-options-layout.h"
#include "../nethack-c/wasm/tu-fragments/options-support.c"
#undef free
extern void free(void*);
#undef rn2
#undef rnd
#undef rn2_on_display_rng
__attribute__((weak)) struct accessibility_data a11y;
__attribute__((weak)) struct flag flags;
__attribute__((weak)) struct instance_flags iflags;
__attribute__((weak)) struct you u;
__attribute__((weak)) volatile struct window_procs windowprocs;
__attribute__((weak)) const struct const_globals cg;
__attribute__((weak)) const glyph_info nul_glyphinfo;
__attribute__((weak)) struct instance_globals_o go;
__attribute__((weak)) struct sinfo program_state;
__attribute__((weak)) struct instance_globals_c gc;
__attribute__((weak)) struct instance_globals_d gd;
__attribute__((weak)) struct instance_globals_h gh;
__attribute__((weak)) struct instance_globals_saved_d svd;
__attribute__((weak)) struct instance_globals_s gs;
__attribute__((weak)) struct instance_globals_saved_p svp;
__attribute__((weak)) struct instance_globals_p gp;
__attribute__((weak)) struct nomakedefs_s nomakedefs;
__attribute__((weak)) struct display_hints disp;
__attribute__((weak)) struct instance_globals_v gv;
__attribute__((weak)) winid WIN_INVEN;
__attribute__((weak)) struct instance_globals_a ga;
__attribute__((weak)) struct instance_globals_m gm;
__attribute__((weak)) struct instance_globals_w gw;
__attribute__((weak)) struct instance_globals_t gt;
__attribute__((weak)) struct instance_globals_n gn;
__attribute__((weak)) struct instance_globals_saved_b svb;
__attribute__((weak)) struct instance_globals_f gf;
__attribute__((weak)) struct instance_globals_saved_c svc;
__attribute__((weak)) struct condtests_t condtests[30];
__typeof__(gr) gr;
__typeof__(gu) gu;
const char disclosure_options[]="iavgco";
const char hexdd[33]="00112233445566778899aAbBcCdDeEfF";
const char quitchars[]=" \033\n\r",ynchars[]="yn",ynaqchars[]="ynaq";
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind.",.c_Something="Something"};
winid WIN_MESSAGE=7,WIN_MAP=8,WIN_STATUS=9;
const char *const known_handling[] = {
    "UNKNOWN", /* H_UNK  */
    "IBM",     /* H_IBM  */
    "DEC",     /* H_DEC  */
    "CURS",    /* H_CURS */
    "MAC",     /* H_MAC  -- pre-OSX MACgraphics */
    "UTF8",    /* H_UTF8 */
    (const char *) 0,
};
const char *const known_restrictions[] = {
    "primary", "rogue", (const char *) 0,
};
const struct symparse loadsyms[] = {
    { SYM_CONTROL, 0, "start" },
    { SYM_CONTROL, 0, "begin" },
    { SYM_CONTROL, 1, "finish" },
    { SYM_CONTROL, 2, "handling" },
    { SYM_CONTROL, 3, "description" },
    { SYM_CONTROL, 4, "color" },
    { SYM_CONTROL, 4, "colour" },
    { SYM_CONTROL, 5, "restrictions" },
#define PCHAR_PARSE
#include "defsym.h"
#undef PCHAR_PARSE
#define OBJCLASS_PARSE
#include "defsym.h"
#undef OBJCLASS_PARSE
#define MONSYMS_PARSE
#include "defsym.h"
#undef MONSYMS_PARSE
    { SYM_OTH, SYM_NOTHING + SYM_OFF_X, "S_nothing" },
    { SYM_OTH, SYM_UNEXPLORED + SYM_OFF_X, "S_unexplored" },
    { SYM_OTH, SYM_BOULDER + SYM_OFF_X, "S_boulder" },
    { SYM_OTH, SYM_INVISIBLE + SYM_OFF_X, "S_invisible" },
    { SYM_OTH, SYM_PET_OVERRIDE + SYM_OFF_X, "S_pet_override" },
    { SYM_OTH, SYM_HERO_OVERRIDE + SYM_OFF_X, "S_hero_override" },
    { SYM_INVALID, 0, (const char *) 0 } /* fence post */
};
const char *const vanqorders[NUM_VANQ_ORDER_MODES][3] = {
    { "t", "traditional: by monster level",
           "traditional: by monster level, by internal monster index" },
    { "d", "by monster difficulty rating",
           "by monster difficulty rating, by internal monster index" },
    { "a", "alphabetically, unique monsters separate",
           "alphabetically, first unique monsters, then others" },
    { "A", "alphabetically, unique monsters intermixed",
           "alphabetically, unique monsters and others intermixed" },
    { "C", "by monster class, high to low level in class",
           "by monster class, high to low level within class" },
    { "c", "by monster class, low to high level in class",
           "by monster class, low to high level within class" },
    { "n", "by count, high to low",
           "by count, high to low, by internal index within tied count" },
    { "z", "by count, low to high",
           "by count, low to high, by internal index within tied count" },
};

static char tracebuf[2097152],snap[2097152],buf[12][8192];static int ti,ni,select_values[256],select_n,select_i,input_n,input_i;static char input_values[128][BUFSZ];static int64_t opts[256];static unsigned char configured[256];static struct allopt_t baseline[OPTCOUNT+1];static int baseline_ready;static void*grown;static int free_count,callback_depth;static int64_t returns[256];static char replies[256][BUFSZ];static unsigned rngstate=1;static const char*rngfile,*rngfn;static int rngline;static uintptr_t lastptr;static struct fruit fruitcell;static strbuf_t stringbuf;static menu_item *last_selection;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);ti+=vsnprintf(tracebuf+ti,sizeof tracebuf-ti,f,ap);va_end(ap);if(ti>=sizeof tracebuf-8192)abort();}
EM_JS(void,fixture_throw,(void),{throw new Error('OPTIONS controlled callback');});
static void callback(void){if(opts[250]){opts[250]=0;grown=malloc(48*1024*1024);if(!grown)abort();memset(grown,0x5a,48*1024*1024);}if(opts[251]){opts[251]=0;fixture_throw();}if(opts[252]&&!callback_depth){callback_depth=1;logmsg("nested:%s;",get_option_value("autopickup",FALSE));callback_depth=0;}}
static void vlog(const char*n,const char*f,va_list ap){logmsg("%s:",n);ti+=vsnprintf(tracebuf+ti,sizeof tracebuf-ti,f,ap);logmsg(";");callback();}
void teleport_probe_free(void*p){if(p){free_count++;free(p);}}
void pline(const char*f,...){va_list ap;va_start(ap,f);vlog("pline",f,ap);va_end(ap);}
void You_cant(const char*f,...){va_list ap;va_start(ap,f);vlog("cant",f,ap);va_end(ap);}
void raw_printf(const char*f,...){va_list ap;va_start(ap,f);vlog("raw",f,ap);va_end(ap);}
void config_error_add(const char*f,...){va_list ap;va_start(ap,f);vlog("error",f,ap);va_end(ap);}
void impossible(const char*f,...){va_list ap;va_start(ap,f);vlog("impossible",f,ap);va_end(ap);}
void panic(const char*f,...){va_list ap;va_start(ap,f);vlog("panic",f,ap);va_end(ap);fixture_throw();__builtin_unreachable();}
void __assert_fail(const char*c,const char*f,int l,const char*fn){logmsg("assert:%s:%d:%s;",c,l,fn);fixture_throw();__builtin_unreachable();}
static winid create(int t){logmsg("create:%d;",t);callback();return 3;}
static void destroy(winid w){logmsg("destroy:%d;",w);callback();}
static void display(winid w,boolean b){logmsg("display:%d:%d;",w,b);callback();}
static void clear(winid w){logmsg("clear:%d;",w);callback();}
static void put(winid w,int a,const char*s){logmsg("put:%d:%d:%s;",w,a,s);callback();}
static void start(winid w,unsigned long b){logmsg("start:%d:%lu;",w,b);callback();}
static void end(winid w,const char*s){logmsg("end:%d:%s;",w,s?s:"NULL");callback();}
static void backend_curs(winid w,int x,int y){logmsg("curs:%d:%d:%d;",w,x,y);}
static void backend_file(const char*s,boolean b){logmsg("file:%s:%d;",s,b);callback();}
static void backend_pad(int n){logmsg("pad:%d;",n);callback();}
static void backend_preference(const char*s){logmsg("preference:%s;",s);callback();}
static void syncwin(void){logmsg("sync;");callback();}
void add_menu(winid w,const glyph_info*g,const anything*a,char c,char k,int attr,int color,const char*s,unsigned f){struct autopickup_exception*p=ga.apelist;int i=0;for(;p;p=p->next,i++)if(a&&a->a_void==p)break;if(p)logmsg("menu:%d:%d:%d:%d:%d:%u:ape%d:%s;",w,c,k,attr,color,f,i,s);else logmsg("menu:%d:%d:%d:%d:%d:%u:%016llx:%s;",w,c,k,attr,color,f,(unsigned long long)(a?a->a_ulong:0),s);callback();}
void add_menu_str(winid w,const char*s){logmsg("menustr:%d:%s;",w,s);callback();}
void add_menu_heading(winid w,const char*s){logmsg("heading:%d:%s;",w,s);callback();}
int select_menu(winid w,int how,menu_item**out){int value=select_i<select_n?select_values[select_i++]:0;boolean chosen=value>0||(opts[254]&&value<0);if(opts[254]&&value<0)opts[254]=0;logmsg("select:%d:%d:%d;",w,how,value);*out=0;if(chosen){*out=(menu_item*)alloc(sizeof(menu_item));memset(*out,0,sizeof(menu_item));(*out)->item.a_int=value;if(opts[253]&&how==PICK_ANY){struct autopickup_exception*p=ga.apelist;int i=value-1;while(p&&i--)p=p->next;(*out)->item.a_void=p;}(*out)->count=1;}callback();return chosen?1:value;}
void getlin(const char*q,char*out){const char*s=input_i<input_n?input_values[input_i++]:"\033";logmsg("getlin:%s:%s;",q,s);strcpy(out,s);callback();}
static int draw(int n){if(n<=0){logmsg("impossible:rn2:%d;",n);return 0;}rngstate=rngstate*1664525U+1013904223U;int v=rngstate%(unsigned)n;logmsg("rng:%s:%s:%d:%d:%d;",rngfile?rngfile:"",rngfn?rngfn:"",rngline,n,v);return v;}
int rn2(int n){return draw(n);}int rn2_on_display_rng(int n){return draw(n);}int rnd(int n){return draw(n)+1;}
int rn2_logged(int n){return draw(n);}int rnd_logged(int n){return draw(n)+1;}
boolean rng_log_enabled(void){return opts[240]?FALSE:TRUE;}void rng_log_set_caller(const char*f,int l,const char*n){rngfile=strrchr(f,'/');rngfile=rngfile?rngfile+1:f;rngline=l;rngfn=n;}
void init_random(int(*fn)(int)){logmsg("seed:%d;",fn==rn2?0:fn==rn2_on_display_rng?1:99);callback();}

__attribute__((weak)) char * get_configfile(void){logmsg("dep:get_configfile;");callback();
return "test.conf";
}
__attribute__((weak)) const char * nh_basename(const char * a0,boolean a1){logmsg("dep:nh_basename;");callback();
return a0;
}
__attribute__((weak)) boolean parsesymbols(char * a0,int a1){logmsg("dep:parsesymbols;");callback();
return (__typeof__((parsesymbols)(a0,a1)))returns[14];
}
__attribute__((weak)) void switch_symbols(int a0){logmsg("dep:switch_symbols;");callback();
}
__attribute__((weak)) void check_gold_symbol(void){logmsg("dep:check_gold_symbol;");callback();
}
__attribute__((weak)) boolean config_unmatched_ignored(void){logmsg("dep:config_unmatched_ignored;");callback();
return (__typeof__((config_unmatched_ignored)()))returns[17];
}
__attribute__((weak)) void sanitize_name(char * a0){logmsg("dep:sanitize_name;");callback();
}
__attribute__((weak)) char * visctrl(char a0){logmsg("dep:visctrl;");callback();
return replies[25][0]?replies[25]:0;
}
__attribute__((weak)) boolean on_level(d_level * a0,d_level * a1){logmsg("dep:on_level;");callback();
return (__typeof__((on_level)(a0,a1)))returns[26];
}
__attribute__((weak)) nhsym get_othersym(int a0,int a1){logmsg("dep:get_othersym;");callback();
return (__typeof__((get_othersym)(a0,a1)))returns[27];
}
__attribute__((weak)) int read_sym_file(int a0){logmsg("dep:read_sym_file;");callback();
return (__typeof__((read_sym_file)(a0)))returns[29];
}
__attribute__((weak)) void clear_symsetentry(int a0,boolean a1){logmsg("dep:clear_symsetentry;");callback();
}
__attribute__((weak)) struct fruit *fruit_from_name(const char*a0,boolean a1,int*a2){logmsg("dep:fruit_from_name;");callback();if(a2&&opts[247])*a2=(int)opts[248];return(struct fruit*)(uintptr_t)returns[34];}

__attribute__((weak)) int glyphrep_to_custom_map_entries(const char * a0,int * a1){logmsg("dep:glyphrep_to_custom_map_entries;");callback();
return (__typeof__((glyphrep_to_custom_map_entries)(a0,a1)))returns[36];
}
__attribute__((weak)) void clear_status_hilites(void){logmsg("dep:clear_status_hilites;");callback();
}
__attribute__((weak)) boolean parse_status_hl1(char * a0,boolean a1){logmsg("dep:parse_status_hl1;");callback();
return (__typeof__((parse_status_hl1)(a0,a1)))returns[38];
}
__attribute__((weak)) int count_status_hilites(void){logmsg("dep:count_status_hilites;");callback();
return (__typeof__((count_status_hilites)()))returns[39];
}
__attribute__((weak)) void assign_graphics(int a0){logmsg("dep:assign_graphics;");callback();
}
__attribute__((weak)) boolean color_attr_parse_str(color_attr * a0,char * a1){logmsg("dep:color_attr_parse_str;");callback();
return (__typeof__((color_attr_parse_str)(a0,a1)))returns[41];
}
__attribute__((weak)) char * color_attr_to_str(color_attr * a0){logmsg("dep:color_attr_to_str;");callback();
return replies[42][0]?replies[42]:0;
}
__attribute__((weak)) void reset_commands(boolean a0){logmsg("dep:reset_commands;");callback();
}
__attribute__((weak)) int match_str2attr(const char * a0,boolean a1){logmsg("dep:match_str2attr;");callback();
return (__typeof__((match_str2attr)(a0,a1)))returns[51];
}
__attribute__((weak)) const char * attr2attrname(int a0){logmsg("dep:attr2attrname;");callback();
return replies[52][0]?replies[52]:"fixture";
}
__attribute__((weak)) int choose_classes_menu(const char * a0,int a1,boolean a2,char * a3,char * a4){logmsg("dep:choose_classes_menu;");callback();
return (__typeof__((choose_classes_menu)(a0,a1,a2,a3,a4)))returns[54];
}
__attribute__((weak)) void get_soundlib_name(char * a0,int a1){logmsg("dep:get_soundlib_name;");callback();
if(a1>0)snprintf(a0,a1,"%s",replies[59][0]?replies[59]:"nosound");
}
__attribute__((weak)) enum soundlib_ids soundlib_id_from_opt(char * a0){logmsg("dep:soundlib_id_from_opt;");callback();
return (__typeof__((soundlib_id_from_opt)(a0)))returns[60];
}
__attribute__((weak)) void assign_soundlib(int a0){logmsg("dep:assign_soundlib;");callback();
}
__attribute__((weak)) void get_sortdisco(char * a0,boolean a1){logmsg("dep:get_sortdisco;");callback();
strcpy(a0,replies[62][0]?replies[62]:"o");
}
__attribute__((weak)) int choose_disco_sort(int a0){logmsg("dep:choose_disco_sort;");callback();
return (__typeof__((choose_disco_sort)(a0)))returns[63];
}
__attribute__((weak)) int set_vanq_order(boolean a0){logmsg("dep:set_vanq_order;");callback();
return (__typeof__((set_vanq_order)(a0)))returns[64];
}
__attribute__((weak)) void reset_status_hilites(void){logmsg("dep:reset_status_hilites;");callback();
}
__attribute__((weak)) boolean glyphid_cache_status(void){logmsg("dep:glyphid_cache_status;");callback();
return (__typeof__((glyphid_cache_status)()))returns[67];
}
__attribute__((weak)) void fill_glyphid_cache(void){logmsg("dep:fill_glyphid_cache;");callback();
}
__attribute__((weak)) void free_glyphid_cache(void){logmsg("dep:free_glyphid_cache;");callback();
}
__attribute__((weak)) char * status_version(char * a0,size_t a1,boolean a2){logmsg("dep:status_version;");callback();
strcpy(a0,"fixture");return a0;
}
__attribute__((weak)) void choose_windows(const char * a0){logmsg("dep:choose_windows;");callback();
}
__attribute__((weak)) void condopt(int a0,boolean * a1,boolean a2){logmsg("dep:condopt;");callback();
}
__attribute__((weak)) int parse_cond_option(boolean a0,char * a1){logmsg("dep:parse_cond_option;");callback();
return (__typeof__((parse_cond_option)(a0,a1)))returns[73];
}
__attribute__((weak)) boolean cond_menu(void){logmsg("dep:cond_menu;");callback();
return (__typeof__((cond_menu)()))returns[74];
}
__attribute__((weak)) void classify_terrain(void){logmsg("dep:classify_terrain;");callback();
}
__attribute__((weak)) void status_initialize(boolean a0){logmsg("dep:status_initialize;");callback();
}
__attribute__((weak)) void reassign(void){logmsg("dep:reassign;");callback();
}
__attribute__((weak)) void update_inventory(void){logmsg("dep:update_inventory;");callback();
}
__attribute__((weak)) void vision_recalc(int a0){logmsg("dep:vision_recalc;");callback();
}
__attribute__((weak)) void update_rest_on_space(void){logmsg("dep:update_rest_on_space;");callback();
}
__attribute__((weak)) boolean query_color_attr(color_attr * a0,const char * a1){logmsg("dep:query_color_attr;");callback();
return (__typeof__((query_color_attr)(a0,a1)))returns[81];
}
__attribute__((weak)) void adjust_menu_promptstyle(winid a0,color_attr * a1){logmsg("dep:adjust_menu_promptstyle;");callback();
}
__attribute__((weak)) int do_reqmenu(void){logmsg("dep:do_reqmenu;");callback();
return (__typeof__((do_reqmenu)()))returns[83];
}
__attribute__((weak)) char cmd_from_func(int (*a0)(void)){logmsg("dep:cmd_from_func;");callback();
return (__typeof__((cmd_from_func)(a0)))returns[84];
}
__attribute__((weak)) const char * cmdname_from_func(int (*a0)(void),char * a1,boolean a2){logmsg("dep:cmdname_from_func;");callback();
return replies[85][0]?replies[85]:"fixture";
}
__attribute__((weak)) int query_attr(const char * a0,int a1){logmsg("dep:query_attr;");callback();
return (__typeof__((query_attr)(a0,a1)))returns[87];
}
__attribute__((weak)) int do_symset(boolean a0){logmsg("dep:do_symset;");callback();
return (__typeof__((do_symset)(a0)))returns[88];
}
__attribute__((weak)) int count_menucolors(void){logmsg("dep:count_menucolors;");callback();
return (__typeof__((count_menucolors)()))returns[90];
}
__attribute__((weak)) int query_color(const char * a0,int a1){logmsg("dep:query_color;");callback();
return (__typeof__((query_color)(a0,a1)))returns[91];
}
__attribute__((weak)) boolean add_menu_coloring_parsed(const char * a0,int a1,int a2){logmsg("dep:add_menu_coloring_parsed;");callback();
return (__typeof__((add_menu_coloring_parsed)(a0,a1,a2)))returns[92];
}
__attribute__((weak)) const char * clr2colorname(int a0){logmsg("dep:clr2colorname;");callback();
return replies[93][0]?replies[93]:"fixture";
}
__attribute__((weak)) void free_one_menu_coloring(int a0){logmsg("dep:free_one_menu_coloring;");callback();
}
__attribute__((weak)) void assure_syscf_file(void){logmsg("dep:assure_syscf_file;");callback();
}
__attribute__((weak)) void config_error_init(boolean a0,const char * a1,boolean a2){logmsg("dep:config_error_init;");callback();
}
__attribute__((weak)) boolean read_config_file(const char * a0,int a1){logmsg("dep:read_config_file;");callback();
return (__typeof__((read_config_file)(a0,a1)))returns[99];
}
__attribute__((weak)) int config_error_done(void){logmsg("dep:config_error_done;");callback();
return (__typeof__((config_error_done)()))returns[100];
}
__attribute__((weak)) void nh_terminate(int a0){logmsg("dep:nh_terminate;");callback();
fixture_throw();__builtin_unreachable();
}
__attribute__((weak)) void do_deferred_showpaths(int a0){logmsg("dep:do_deferred_showpaths;");callback();
fixture_throw();__builtin_unreachable();
}
__attribute__((weak)) void sf_init(void){logmsg("dep:sf_init;");callback();
}
__attribute__((weak)) void init_ov_primary_symbols(void){logmsg("dep:init_ov_primary_symbols;");callback();
}
__attribute__((weak)) void init_ov_rogue_symbols(void){logmsg("dep:init_ov_rogue_symbols;");callback();
}
__attribute__((weak)) void init_symbols(void){logmsg("dep:init_symbols;");callback();
}
__attribute__((weak)) void init_rogue_symbols(void){logmsg("dep:init_rogue_symbols;");callback();
}
__attribute__((weak)) int load_symset(const char * a0,int a1){logmsg("dep:load_symset;");callback();
return (__typeof__((load_symset)(a0,a1)))returns[112];
}
__attribute__((weak)) void rcfile(void){logmsg("dep:rcfile;");callback();
}
__attribute__((weak)) void reglyph_darkroom(void){logmsg("dep:reglyph_darkroom;");callback();
}
__attribute__((weak)) void reset_glyphmap(enum glyphmap_change_triggers a0){logmsg("dep:reset_glyphmap;");callback();
}
__attribute__((weak)) void apply_customizations(enum graphics_sets a0,enum do_customizations a1){logmsg("dep:apply_customizations;");callback();
}
__attribute__((weak)) unsigned long get_feature_notice_ver(char * a0){logmsg("dep:get_feature_notice_ver;");callback();
return (__typeof__((get_feature_notice_ver)(a0)))returns[117];
}
__attribute__((weak)) unsigned long get_current_feature_ver(void){logmsg("dep:get_current_feature_ver;");callback();
return (__typeof__((get_current_feature_ver)()))returns[118];
}
__attribute__((weak)) boolean bind_mousebtn(int a0,const char * a1){logmsg("dep:bind_mousebtn;");callback();
return (__typeof__((bind_mousebtn)(a0,a1)))returns[119];
}
__attribute__((weak)) boolean bind_specialkey(uchar a0,const char * a1){logmsg("dep:bind_specialkey;");callback();
return (__typeof__((bind_specialkey)(a0,a1)))returns[120];
}
__attribute__((weak)) boolean bind_key(uchar a0,const char * a1,boolean a2){logmsg("dep:bind_key;");callback();
return (__typeof__((bind_key)(a0,a1,a2)))returns[121];
}
__attribute__((weak)) void clearrolefilter(int a0){logmsg("dep:clearrolefilter;");callback();
}
__attribute__((weak)) boolean setrolefilter(const char * a0){logmsg("dep:setrolefilter;");callback();
return (__typeof__((setrolefilter)(a0)))returns[129];
}
__attribute__((weak)) char * rolefilterstring(char * a0,int a1){logmsg("dep:rolefilterstring;");callback();
return replies[130][0]?replies[130]:"fixture";
}
__attribute__((weak)) char * makesingular(const char * a0){logmsg("dep:makesingular;");callback();
return replies[131][0]?replies[131]:"fixture";
}
__attribute__((weak)) int name_to_mon(const char * a0,int * a1){logmsg("dep:name_to_mon;");callback();
return (__typeof__((name_to_mon)(a0,a1)))returns[132];
}
__attribute__((weak)) int count_bind_keys(void){logmsg("dep:count_bind_keys;");callback();
return (__typeof__((count_bind_keys)()))returns[139];
}
__attribute__((weak)) void handler_rebind_keys(void){logmsg("dep:handler_rebind_keys;");callback();
}
__attribute__((weak)) int count_autocompletions(void){logmsg("dep:count_autocompletions;");callback();
return (__typeof__((count_autocompletions)()))returns[141];
}
__attribute__((weak)) void handler_change_autocompletions(void){logmsg("dep:handler_change_autocompletions;");callback();
}
__attribute__((weak)) boolean status_hilite_menu(void){logmsg("dep:status_hilite_menu;");callback();
return (__typeof__((status_hilite_menu)()))returns[143];
}
__attribute__((weak)) void flush_screen(int a0){logmsg("dep:flush_screen;");callback();
}
__attribute__((weak)) void reset_customcolors(void){logmsg("dep:reset_customcolors;");callback();
}
__attribute__((weak)) void reset_customsymbols(void){logmsg("dep:reset_customsymbols;");callback();
}
__attribute__((weak)) void docrt(void){logmsg("dep:docrt;");callback();
}
__attribute__((weak)) void bot(void){logmsg("dep:bot;");callback();
}
__attribute__((weak)) char * makeplural(const char * a0){logmsg("dep:makeplural;");callback();
return replies[150][0]?replies[150]:"fixture";
}
__attribute__((weak)) boolean opt_next_cond(int a0,char *a1){logmsg("dep:opt_next_cond;");callback();if(a0<0||a0>=opts[249])return FALSE;strcpy(a1,input_values[a0]);return TRUE;}

__attribute__((weak)) char * yyyymmddhhmmss(time_t a0){logmsg("dep:yyyymmddhhmmss;");callback();
return "20261110000000";
}
__attribute__((weak)) void get_changed_key_binds(strbuf_t * a0){logmsg("dep:get_changed_key_binds;");callback();
}
__attribute__((weak)) void savedsym_strbuf(strbuf_t * a0){logmsg("dep:savedsym_strbuf;");callback();
}
__attribute__((weak)) void all_options_autocomplete(strbuf_t * a0){logmsg("dep:all_options_autocomplete;");callback();
}
__attribute__((weak)) void all_options_statushilites(strbuf_t * a0){logmsg("dep:all_options_statushilites;");callback();
}
__attribute__((weak)) int32 check_enhanced_colors(char * a0){logmsg("dep:check_enhanced_colors;");callback();
return (__typeof__((check_enhanced_colors)(a0)))returns[161];
}
__attribute__((weak)) const char * wc_color_name(int32 a0){logmsg("dep:wc_color_name;");callback();
return replies[162][0]?replies[162]:"fixture";
}
__attribute__((weak)) boolean authorize_wizard_mode(void){logmsg("dep:authorize_wizard_mode;");callback();
return (__typeof__((authorize_wizard_mode)()))returns[163];
}
__attribute__((weak)) boolean authorize_explore_mode(void){logmsg("dep:authorize_explore_mode;");callback();
return (__typeof__((authorize_explore_mode)()))returns[164];
}
#ifndef TELEPORT_REFERENCE_TU
extern int teleport_options_test_check_misc_menu_command(char * opts,char * op);
extern int teleport_options_test_opt2roleopt(int roleopt);
extern char * teleport_options_test_getoptstr(int optidx,int ophase);
extern void teleport_options_test_saveoptstr(int optidx,const char * optstr);
extern void teleport_options_test_unsaveoptstr(int optidx,int ophase);
extern int teleport_options_test_petname_optfn(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_alignment(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_align_message(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_align_status(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_altkeyhandling(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_autounlock(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_boulder(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_catname(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_crash_email(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_crash_name(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_crash_urlmax(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_DECgraphics(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_disclose(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_dogname(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_dungeon(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_effects(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_map(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_menu(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_message(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_size_map(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_size_menu(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_size_message(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_size_status(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_size_text(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_status(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_font_text(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_fruit(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_gender(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_glyph(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_hilite_status(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_horsename(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_IBMgraphics(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_map_mode(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_shared_menu_optfn(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_deselect_all(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_deselect_page(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_first_page(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_invert_all(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_invert_page(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_last_page(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_next_page(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_previous_page(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_search(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_select_all(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_select_page(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_shift_left(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_shift_right(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_headings(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menu_objsyms(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menuinvertmode(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_menustyle(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_monsters(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_mouse_support(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_msg_window(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_msghistory(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_name(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_number_pad(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_objects(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_packorder(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_paranoid_confirmation(int optidx,int req,boolean opt_negated,char * opts,char * op);
extern int teleport_options_test_optfn_perminv_mode(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_petattr(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_pettype(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_pickup_burden(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_pickup_types(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_pile_limit(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_player_selection(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_playmode(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_race(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_roguesymset(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_role(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_runmode(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_scores(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_scroll_amount(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_scroll_margin(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_soundlib(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_sortdiscoveries(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_sortloot(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_sortvanquished(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_statushilites(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_statuslines(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_suppress_alert(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_symset(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_term_cols(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_term_rows(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_tile_file(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_tile_height(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_tile_width(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_traps(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_vary_msgcount(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_versinfo(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_warnings(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_whatis_coord(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_whatis_filter(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_windowborders(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_windowcolors(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_windowtype(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_pfxfn_cond_(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_pfxfn_font(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_spcfn_misc_menu_cmd(int midx,int req,boolean negated,char * opts,char * op);
extern boolean teleport_options_test_can_set_perm_invent(void);
extern int teleport_options_test_handler_menustyle(void);
extern int teleport_options_test_handler_align_misc(int optidx);
extern int teleport_options_test_handler_autounlock(int optidx);
extern int teleport_options_test_handler_disclose(void);
extern int teleport_options_test_handler_menu_headings(void);
extern int teleport_options_test_handler_menu_objsyms(void);
extern int teleport_options_test_handler_msg_window(void);
extern int teleport_options_test_handler_number_pad(void);
extern int teleport_options_test_handler_paranoid_confirmation(void);
extern int teleport_options_test_handler_perminv_mode(void);
extern int teleport_options_test_handler_pickup_burden(void);
extern int teleport_options_test_handler_pickup_types(void);
extern int teleport_options_test_handler_runmode(void);
extern int teleport_options_test_handler_petattr(void);
extern int teleport_options_test_handler_sortloot(void);
extern int teleport_options_test_handler_whatis_coord(void);
extern int teleport_options_test_handler_whatis_filter(void);
extern int teleport_options_test_handler_symset(int optidx);
extern int teleport_options_test_handler_autopickup_exception(void);
extern int teleport_options_test_handler_menu_colors(void);
extern int teleport_options_test_handler_msgtype(void);
extern int teleport_options_test_handler_versinfo(void);
extern int teleport_options_test_handler_windowborders(void);
extern char * teleport_options_test_string_for_opt(char * opts,boolean val_optional);
extern char * teleport_options_test_string_for_env_opt(const char * optname,char * opts,boolean val_optional);
extern void teleport_options_test_bad_negation(const char * optname,boolean with_parameter);
extern void teleport_options_test_determine_ambiguities(void);
extern int teleport_options_test_length_without_val(const char * user_string,int len);
extern boolean teleport_options_test_duplicate_opt_detection(int optidx);
extern void teleport_options_test_complain_about_duplicate(int optidx);
extern void teleport_options_test_rejectoption(const char * optname);
extern void teleport_options_test_nmcpy(char * dest,const char * src,int maxlen);
extern void teleport_options_test_escapes(const char * cp,char * tp);
extern void teleport_options_test_set_menuobjsyms_flags(int newobjsyms);
extern int teleport_options_test_change_inv_order(char * op);
extern boolean teleport_options_test_warning_opts(char * opts,const char * optype);
extern int teleport_options_test_feature_alert_opts(char * op,const char * optn);
extern const char * teleport_options_test_msgtype2name(int typ);
extern int teleport_options_test_query_msgtype(void);
extern boolean teleport_options_test_msgtype_add(int typ,char * pattern);
extern void teleport_options_test_free_one_msgtype(int idx);
extern int teleport_options_test_msgtype_count(void);
extern boolean teleport_options_test_test_regex_pattern(const char * str,const char * errmsg);
extern boolean teleport_options_test_parse_role_opt(int optidx,boolean negated,const char * fullname,char * opts,char ** opp);
extern char * teleport_options_test_get_cnf_role_opt(int optidx);
extern boolean teleport_options_test_illegal_menu_cmd_key(uchar c);
extern int teleport_options_test_optfn_o_autopickup_exceptions(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_o_bind_keys(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_o_autocomplete(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_o_menu_colors(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_o_message_types(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_o_status_cond(int optidx,int req,boolean negated,char * opts,char * op);
extern int teleport_options_test_optfn_o_status_hilites(int optidx,int req,boolean negated,char * opts,char * op);
extern unsigned int teleport_options_test_longest_option_name(int startpass,int endpass);
extern int teleport_options_test_doset_simple_menu(void);
extern const char * teleport_options_test_term_for_boolean(int idx,boolean * b);
extern void teleport_options_test_reset_needed_visuals(void);
extern void teleport_options_test_doset_add_menu(winid win,const char * option,const char * fmtstr,int idx,int indexoffset);
extern int teleport_options_test_count_cond(void);
extern int teleport_options_test_count_apes(void);
extern int teleport_options_test_handle_add_list_remove(const char * optname,int numtotal);
extern void teleport_options_test_remove_autopickup_exception(struct autopickup_exception * whichape);
extern void teleport_options_test_all_options_conds(strbuf_t * sbuf);
extern void teleport_options_test_all_options_menucolors(strbuf_t * sbuf);
extern void teleport_options_test_all_options_msgtypes(strbuf_t * sbuf);
extern void teleport_options_test_all_options_apes(strbuf_t * sbuf);
extern boolean teleport_options_test_is_wc_option(const char * optnam);
extern boolean teleport_options_test_wc_supported(const char * optnam);
extern boolean teleport_options_test_is_wc2_option(const char * optnam);
extern boolean teleport_options_test_wc2_supported(const char * optnam);
extern void teleport_options_test_wc_set_font_name(int opttype,char * fontname);
extern int teleport_options_test_wc_set_window_colors(char * op);
extern void teleport_options_test_enhance_menu_text(char * buf,size_t sz,int whichpass,boolean * bool_p,struct allopt_t * thisopt);
#endif
static const char*function_names[]={"ask_do_tutorial","parseoptions","check_misc_menu_command","opt2roleopt","getoptstr","saveoptstr","unsaveoptstr","freeroleoptvals","petname_optfn","optfn_alignment","optfn_align_message","optfn_align_status","optfn_altkeyhandling","optfn_autounlock","optfn_boulder","optfn_catname","optfn_crash_email","optfn_crash_name","optfn_crash_urlmax","optfn_DECgraphics","optfn_disclose","optfn_dogname","optfn_dungeon","optfn_effects","optfn_font_map","optfn_font_menu","optfn_font_message","optfn_font_size_map","optfn_font_size_menu","optfn_font_size_message","optfn_font_size_status","optfn_font_size_text","optfn_font_status","optfn_font_text","optfn_fruit","optfn_gender","optfn_glyph","optfn_hilite_status","optfn_horsename","optfn_IBMgraphics","optfn_map_mode","shared_menu_optfn","optfn_menu_deselect_all","optfn_menu_deselect_page","optfn_menu_first_page","optfn_menu_invert_all","optfn_menu_invert_page","optfn_menu_last_page","optfn_menu_next_page","optfn_menu_previous_page","optfn_menu_search","optfn_menu_select_all","optfn_menu_select_page","optfn_menu_shift_left","optfn_menu_shift_right","optfn_menu_headings","optfn_menu_objsyms","optfn_menuinvertmode","optfn_menustyle","optfn_monsters","optfn_mouse_support","optfn_msg_window","optfn_msghistory","optfn_name","optfn_number_pad","optfn_objects","optfn_packorder","optfn_paranoid_confirmation","optfn_perminv_mode","optfn_petattr","optfn_pettype","optfn_pickup_burden","optfn_pickup_types","optfn_pile_limit","optfn_player_selection","optfn_playmode","optfn_race","optfn_roguesymset","optfn_role","optfn_runmode","optfn_scores","optfn_scroll_amount","optfn_scroll_margin","optfn_soundlib","optfn_sortdiscoveries","optfn_sortloot","optfn_sortvanquished","optfn_statushilites","optfn_statuslines","optfn_suppress_alert","optfn_symset","optfn_term_cols","optfn_term_rows","optfn_tile_file","optfn_tile_height","optfn_tile_width","optfn_traps","optfn_vary_msgcount","optfn_versinfo","optfn_warnings","optfn_whatis_coord","optfn_whatis_filter","optfn_windowborders","optfn_windowcolors","optfn_windowtype","pfxfn_cond_","pfxfn_font","optfn_boolean","spcfn_misc_menu_cmd","can_set_perm_invent","handler_menustyle","handler_align_misc","handler_autounlock","handler_disclose","handler_menu_headings","handler_menu_objsyms","handler_msg_window","handler_number_pad","handler_paranoid_confirmation","handler_perminv_mode","handler_pickup_burden","handler_pickup_types","handler_runmode","handler_petattr","handler_sortloot","handler_whatis_coord","handler_whatis_filter","handler_symset","handler_autopickup_exception","handler_menu_colors","handler_msgtype","handler_versinfo","handler_windowborders","string_for_opt","string_for_env_opt","bad_negation","determine_ambiguities","length_without_val","match_optname","reset_duplicate_opt_detection","duplicate_opt_detection","complain_about_duplicate","rejectoption","nh_getenv","nmcpy","escapes","txt2key","initoptions","initoptions_init","initoptions_finish","allopt_array_init","set_menuobjsyms_flags","change_inv_order","warning_opts","assign_warnings","feature_alert_opts","parsebindings","msgtype2name","query_msgtype","msgtype_add","msgtype_free","free_one_msgtype","msgtype_type","hide_unhide_msgtypes","msgtype_count","msgtype_parse_add","test_regex_pattern","parse_role_opt","get_cnf_role_opt","illegal_menu_cmd_key","oc_to_str","add_menu_cmd_alias","get_menu_cmd_key","map_menu_cmd","collect_menu_keys","fruitadd","optfn_o_autopickup_exceptions","optfn_o_bind_keys","optfn_o_autocomplete","optfn_o_menu_colors","optfn_o_message_types","optfn_o_status_cond","optfn_o_status_hilites","get_option_value","longest_option_name","doset_simple_menu","doset_simple","term_for_boolean","doset","reset_needed_visuals","doset_add_menu","show_menu_controls","count_cond","count_apes","handle_add_list_remove","dotogglepickup","toggle_bool_option","add_autopickup_exception","remove_autopickup_exception","free_autopickup_exceptions","sym_val","option_help","all_options_conds","all_options_menucolors","all_options_msgtypes","all_options_apes","all_options_strbuf","next_opt","set_option_mod_status","set_wc_option_mod_status","is_wc_option","wc_supported","set_wc2_option_mod_status","is_wc2_option","wc2_supported","wc_set_font_name","wc_set_window_colors","options_free_window_colors","set_playmode","enhance_menu_text","heed_all_options","disregard_all_options","heed_this_option","disregard_this_option"};
int probe_function_count(void){return SIZE(function_names);}const char*probe_function_name(int i){return function_names[i];}
uint64_t probe_call(int i,uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){lastptr=0;switch(i){
case 0:lastptr=(uintptr_t)ask_do_tutorial();return lastptr;
case 1:lastptr=(uintptr_t)parseoptions((char *)(uintptr_t)a0,(boolean)(uintptr_t)a1,(boolean)(uintptr_t)a2);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 2:lastptr=(uintptr_t)check_misc_menu_command((char *)(uintptr_t)a0,(char *)(uintptr_t)a1);return lastptr;
#else
case 2:lastptr=(uintptr_t)teleport_options_test_check_misc_menu_command((char *)(uintptr_t)a0,(char *)(uintptr_t)a1);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 3:lastptr=(uintptr_t)opt2roleopt((int)(uintptr_t)a0);return lastptr;
#else
case 3:lastptr=(uintptr_t)teleport_options_test_opt2roleopt((int)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 4:lastptr=(uintptr_t)getoptstr((int)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#else
case 4:lastptr=(uintptr_t)teleport_options_test_getoptstr((int)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 5:saveoptstr((int)(uintptr_t)a0,(const char *)(uintptr_t)a1);return 0;
#else
case 5:teleport_options_test_saveoptstr((int)(uintptr_t)a0,(const char *)(uintptr_t)a1);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 6:unsaveoptstr((int)(uintptr_t)a0,(int)(uintptr_t)a1);return 0;
#else
case 6:teleport_options_test_unsaveoptstr((int)(uintptr_t)a0,(int)(uintptr_t)a1);return 0;
#endif
case 7:freeroleoptvals();return 0;
#ifdef TELEPORT_REFERENCE_TU
case 8:lastptr=(uintptr_t)petname_optfn((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 8:lastptr=(uintptr_t)teleport_options_test_petname_optfn((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 9:lastptr=(uintptr_t)optfn_alignment((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 9:lastptr=(uintptr_t)teleport_options_test_optfn_alignment((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 10:lastptr=(uintptr_t)optfn_align_message((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 10:lastptr=(uintptr_t)teleport_options_test_optfn_align_message((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 11:lastptr=(uintptr_t)optfn_align_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 11:lastptr=(uintptr_t)teleport_options_test_optfn_align_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 12:lastptr=(uintptr_t)optfn_altkeyhandling((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 12:lastptr=(uintptr_t)teleport_options_test_optfn_altkeyhandling((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 13:lastptr=(uintptr_t)optfn_autounlock((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 13:lastptr=(uintptr_t)teleport_options_test_optfn_autounlock((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 14:lastptr=(uintptr_t)optfn_boulder((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 14:lastptr=(uintptr_t)teleport_options_test_optfn_boulder((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 15:lastptr=(uintptr_t)optfn_catname((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 15:lastptr=(uintptr_t)teleport_options_test_optfn_catname((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 16:lastptr=(uintptr_t)optfn_crash_email((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 16:lastptr=(uintptr_t)teleport_options_test_optfn_crash_email((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 17:lastptr=(uintptr_t)optfn_crash_name((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 17:lastptr=(uintptr_t)teleport_options_test_optfn_crash_name((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 18:lastptr=(uintptr_t)optfn_crash_urlmax((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 18:lastptr=(uintptr_t)teleport_options_test_optfn_crash_urlmax((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 19:lastptr=(uintptr_t)optfn_DECgraphics((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 19:lastptr=(uintptr_t)teleport_options_test_optfn_DECgraphics((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 20:lastptr=(uintptr_t)optfn_disclose((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 20:lastptr=(uintptr_t)teleport_options_test_optfn_disclose((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 21:lastptr=(uintptr_t)optfn_dogname((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 21:lastptr=(uintptr_t)teleport_options_test_optfn_dogname((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 22:lastptr=(uintptr_t)optfn_dungeon((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 22:lastptr=(uintptr_t)teleport_options_test_optfn_dungeon((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 23:lastptr=(uintptr_t)optfn_effects((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 23:lastptr=(uintptr_t)teleport_options_test_optfn_effects((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 24:lastptr=(uintptr_t)optfn_font_map((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 24:lastptr=(uintptr_t)teleport_options_test_optfn_font_map((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 25:lastptr=(uintptr_t)optfn_font_menu((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 25:lastptr=(uintptr_t)teleport_options_test_optfn_font_menu((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 26:lastptr=(uintptr_t)optfn_font_message((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 26:lastptr=(uintptr_t)teleport_options_test_optfn_font_message((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 27:lastptr=(uintptr_t)optfn_font_size_map((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 27:lastptr=(uintptr_t)teleport_options_test_optfn_font_size_map((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 28:lastptr=(uintptr_t)optfn_font_size_menu((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 28:lastptr=(uintptr_t)teleport_options_test_optfn_font_size_menu((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 29:lastptr=(uintptr_t)optfn_font_size_message((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 29:lastptr=(uintptr_t)teleport_options_test_optfn_font_size_message((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 30:lastptr=(uintptr_t)optfn_font_size_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 30:lastptr=(uintptr_t)teleport_options_test_optfn_font_size_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 31:lastptr=(uintptr_t)optfn_font_size_text((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 31:lastptr=(uintptr_t)teleport_options_test_optfn_font_size_text((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 32:lastptr=(uintptr_t)optfn_font_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 32:lastptr=(uintptr_t)teleport_options_test_optfn_font_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 33:lastptr=(uintptr_t)optfn_font_text((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 33:lastptr=(uintptr_t)teleport_options_test_optfn_font_text((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 34:lastptr=(uintptr_t)optfn_fruit((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 34:lastptr=(uintptr_t)teleport_options_test_optfn_fruit((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 35:lastptr=(uintptr_t)optfn_gender((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 35:lastptr=(uintptr_t)teleport_options_test_optfn_gender((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 36:lastptr=(uintptr_t)optfn_glyph((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 36:lastptr=(uintptr_t)teleport_options_test_optfn_glyph((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 37:lastptr=(uintptr_t)optfn_hilite_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 37:lastptr=(uintptr_t)teleport_options_test_optfn_hilite_status((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 38:lastptr=(uintptr_t)optfn_horsename((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 38:lastptr=(uintptr_t)teleport_options_test_optfn_horsename((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 39:lastptr=(uintptr_t)optfn_IBMgraphics((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 39:lastptr=(uintptr_t)teleport_options_test_optfn_IBMgraphics((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 40:lastptr=(uintptr_t)optfn_map_mode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 40:lastptr=(uintptr_t)teleport_options_test_optfn_map_mode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 41:lastptr=(uintptr_t)shared_menu_optfn((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 41:lastptr=(uintptr_t)teleport_options_test_shared_menu_optfn((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 42:lastptr=(uintptr_t)optfn_menu_deselect_all((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 42:lastptr=(uintptr_t)teleport_options_test_optfn_menu_deselect_all((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 43:lastptr=(uintptr_t)optfn_menu_deselect_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 43:lastptr=(uintptr_t)teleport_options_test_optfn_menu_deselect_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 44:lastptr=(uintptr_t)optfn_menu_first_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 44:lastptr=(uintptr_t)teleport_options_test_optfn_menu_first_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 45:lastptr=(uintptr_t)optfn_menu_invert_all((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 45:lastptr=(uintptr_t)teleport_options_test_optfn_menu_invert_all((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 46:lastptr=(uintptr_t)optfn_menu_invert_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 46:lastptr=(uintptr_t)teleport_options_test_optfn_menu_invert_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 47:lastptr=(uintptr_t)optfn_menu_last_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 47:lastptr=(uintptr_t)teleport_options_test_optfn_menu_last_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 48:lastptr=(uintptr_t)optfn_menu_next_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 48:lastptr=(uintptr_t)teleport_options_test_optfn_menu_next_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 49:lastptr=(uintptr_t)optfn_menu_previous_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 49:lastptr=(uintptr_t)teleport_options_test_optfn_menu_previous_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 50:lastptr=(uintptr_t)optfn_menu_search((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 50:lastptr=(uintptr_t)teleport_options_test_optfn_menu_search((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 51:lastptr=(uintptr_t)optfn_menu_select_all((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 51:lastptr=(uintptr_t)teleport_options_test_optfn_menu_select_all((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 52:lastptr=(uintptr_t)optfn_menu_select_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 52:lastptr=(uintptr_t)teleport_options_test_optfn_menu_select_page((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 53:lastptr=(uintptr_t)optfn_menu_shift_left((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 53:lastptr=(uintptr_t)teleport_options_test_optfn_menu_shift_left((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 54:lastptr=(uintptr_t)optfn_menu_shift_right((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 54:lastptr=(uintptr_t)teleport_options_test_optfn_menu_shift_right((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 55:lastptr=(uintptr_t)optfn_menu_headings((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 55:lastptr=(uintptr_t)teleport_options_test_optfn_menu_headings((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 56:lastptr=(uintptr_t)optfn_menu_objsyms((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 56:lastptr=(uintptr_t)teleport_options_test_optfn_menu_objsyms((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 57:lastptr=(uintptr_t)optfn_menuinvertmode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 57:lastptr=(uintptr_t)teleport_options_test_optfn_menuinvertmode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 58:lastptr=(uintptr_t)optfn_menustyle((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 58:lastptr=(uintptr_t)teleport_options_test_optfn_menustyle((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 59:lastptr=(uintptr_t)optfn_monsters((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 59:lastptr=(uintptr_t)teleport_options_test_optfn_monsters((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 60:lastptr=(uintptr_t)optfn_mouse_support((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 60:lastptr=(uintptr_t)teleport_options_test_optfn_mouse_support((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 61:lastptr=(uintptr_t)optfn_msg_window((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 61:lastptr=(uintptr_t)teleport_options_test_optfn_msg_window((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 62:lastptr=(uintptr_t)optfn_msghistory((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 62:lastptr=(uintptr_t)teleport_options_test_optfn_msghistory((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 63:lastptr=(uintptr_t)optfn_name((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 63:lastptr=(uintptr_t)teleport_options_test_optfn_name((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 64:lastptr=(uintptr_t)optfn_number_pad((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 64:lastptr=(uintptr_t)teleport_options_test_optfn_number_pad((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 65:lastptr=(uintptr_t)optfn_objects((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 65:lastptr=(uintptr_t)teleport_options_test_optfn_objects((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 66:lastptr=(uintptr_t)optfn_packorder((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 66:lastptr=(uintptr_t)teleport_options_test_optfn_packorder((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 67:lastptr=(uintptr_t)optfn_paranoid_confirmation((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 67:lastptr=(uintptr_t)teleport_options_test_optfn_paranoid_confirmation((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 68:lastptr=(uintptr_t)optfn_perminv_mode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 68:lastptr=(uintptr_t)teleport_options_test_optfn_perminv_mode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 69:lastptr=(uintptr_t)optfn_petattr((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 69:lastptr=(uintptr_t)teleport_options_test_optfn_petattr((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 70:lastptr=(uintptr_t)optfn_pettype((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 70:lastptr=(uintptr_t)teleport_options_test_optfn_pettype((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 71:lastptr=(uintptr_t)optfn_pickup_burden((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 71:lastptr=(uintptr_t)teleport_options_test_optfn_pickup_burden((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 72:lastptr=(uintptr_t)optfn_pickup_types((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 72:lastptr=(uintptr_t)teleport_options_test_optfn_pickup_types((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 73:lastptr=(uintptr_t)optfn_pile_limit((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 73:lastptr=(uintptr_t)teleport_options_test_optfn_pile_limit((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 74:lastptr=(uintptr_t)optfn_player_selection((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 74:lastptr=(uintptr_t)teleport_options_test_optfn_player_selection((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 75:lastptr=(uintptr_t)optfn_playmode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 75:lastptr=(uintptr_t)teleport_options_test_optfn_playmode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 76:lastptr=(uintptr_t)optfn_race((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 76:lastptr=(uintptr_t)teleport_options_test_optfn_race((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 77:lastptr=(uintptr_t)optfn_roguesymset((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 77:lastptr=(uintptr_t)teleport_options_test_optfn_roguesymset((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 78:lastptr=(uintptr_t)optfn_role((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 78:lastptr=(uintptr_t)teleport_options_test_optfn_role((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 79:lastptr=(uintptr_t)optfn_runmode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 79:lastptr=(uintptr_t)teleport_options_test_optfn_runmode((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 80:lastptr=(uintptr_t)optfn_scores((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 80:lastptr=(uintptr_t)teleport_options_test_optfn_scores((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 81:lastptr=(uintptr_t)optfn_scroll_amount((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 81:lastptr=(uintptr_t)teleport_options_test_optfn_scroll_amount((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 82:lastptr=(uintptr_t)optfn_scroll_margin((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 82:lastptr=(uintptr_t)teleport_options_test_optfn_scroll_margin((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 83:lastptr=(uintptr_t)optfn_soundlib((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 83:lastptr=(uintptr_t)teleport_options_test_optfn_soundlib((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 84:lastptr=(uintptr_t)optfn_sortdiscoveries((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 84:lastptr=(uintptr_t)teleport_options_test_optfn_sortdiscoveries((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 85:lastptr=(uintptr_t)optfn_sortloot((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 85:lastptr=(uintptr_t)teleport_options_test_optfn_sortloot((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 86:lastptr=(uintptr_t)optfn_sortvanquished((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 86:lastptr=(uintptr_t)teleport_options_test_optfn_sortvanquished((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 87:lastptr=(uintptr_t)optfn_statushilites((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 87:lastptr=(uintptr_t)teleport_options_test_optfn_statushilites((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 88:lastptr=(uintptr_t)optfn_statuslines((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 88:lastptr=(uintptr_t)teleport_options_test_optfn_statuslines((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 89:lastptr=(uintptr_t)optfn_suppress_alert((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 89:lastptr=(uintptr_t)teleport_options_test_optfn_suppress_alert((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 90:lastptr=(uintptr_t)optfn_symset((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 90:lastptr=(uintptr_t)teleport_options_test_optfn_symset((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 91:lastptr=(uintptr_t)optfn_term_cols((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 91:lastptr=(uintptr_t)teleport_options_test_optfn_term_cols((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 92:lastptr=(uintptr_t)optfn_term_rows((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 92:lastptr=(uintptr_t)teleport_options_test_optfn_term_rows((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 93:lastptr=(uintptr_t)optfn_tile_file((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 93:lastptr=(uintptr_t)teleport_options_test_optfn_tile_file((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 94:lastptr=(uintptr_t)optfn_tile_height((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 94:lastptr=(uintptr_t)teleport_options_test_optfn_tile_height((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 95:lastptr=(uintptr_t)optfn_tile_width((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 95:lastptr=(uintptr_t)teleport_options_test_optfn_tile_width((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 96:lastptr=(uintptr_t)optfn_traps((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 96:lastptr=(uintptr_t)teleport_options_test_optfn_traps((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 97:lastptr=(uintptr_t)optfn_vary_msgcount((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 97:lastptr=(uintptr_t)teleport_options_test_optfn_vary_msgcount((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 98:lastptr=(uintptr_t)optfn_versinfo((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 98:lastptr=(uintptr_t)teleport_options_test_optfn_versinfo((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 99:lastptr=(uintptr_t)optfn_warnings((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 99:lastptr=(uintptr_t)teleport_options_test_optfn_warnings((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 100:lastptr=(uintptr_t)optfn_whatis_coord((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 100:lastptr=(uintptr_t)teleport_options_test_optfn_whatis_coord((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 101:lastptr=(uintptr_t)optfn_whatis_filter((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 101:lastptr=(uintptr_t)teleport_options_test_optfn_whatis_filter((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 102:lastptr=(uintptr_t)optfn_windowborders((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 102:lastptr=(uintptr_t)teleport_options_test_optfn_windowborders((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 103:lastptr=(uintptr_t)optfn_windowcolors((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 103:lastptr=(uintptr_t)teleport_options_test_optfn_windowcolors((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 104:lastptr=(uintptr_t)optfn_windowtype((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 104:lastptr=(uintptr_t)teleport_options_test_optfn_windowtype((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 105:lastptr=(uintptr_t)pfxfn_cond_((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 105:lastptr=(uintptr_t)teleport_options_test_pfxfn_cond_((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 106:lastptr=(uintptr_t)pfxfn_font((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 106:lastptr=(uintptr_t)teleport_options_test_pfxfn_font((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
case 107:lastptr=(uintptr_t)optfn_boolean((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 108:lastptr=(uintptr_t)spcfn_misc_menu_cmd((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 108:lastptr=(uintptr_t)teleport_options_test_spcfn_misc_menu_cmd((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 109:lastptr=(uintptr_t)can_set_perm_invent();return lastptr;
#else
case 109:lastptr=(uintptr_t)teleport_options_test_can_set_perm_invent();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 110:lastptr=(uintptr_t)handler_menustyle();return lastptr;
#else
case 110:lastptr=(uintptr_t)teleport_options_test_handler_menustyle();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 111:lastptr=(uintptr_t)handler_align_misc((int)(uintptr_t)a0);return lastptr;
#else
case 111:lastptr=(uintptr_t)teleport_options_test_handler_align_misc((int)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 112:lastptr=(uintptr_t)handler_autounlock((int)(uintptr_t)a0);return lastptr;
#else
case 112:lastptr=(uintptr_t)teleport_options_test_handler_autounlock((int)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 113:lastptr=(uintptr_t)handler_disclose();return lastptr;
#else
case 113:lastptr=(uintptr_t)teleport_options_test_handler_disclose();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 114:lastptr=(uintptr_t)handler_menu_headings();return lastptr;
#else
case 114:lastptr=(uintptr_t)teleport_options_test_handler_menu_headings();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 115:lastptr=(uintptr_t)handler_menu_objsyms();return lastptr;
#else
case 115:lastptr=(uintptr_t)teleport_options_test_handler_menu_objsyms();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 116:lastptr=(uintptr_t)handler_msg_window();return lastptr;
#else
case 116:lastptr=(uintptr_t)teleport_options_test_handler_msg_window();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 117:lastptr=(uintptr_t)handler_number_pad();return lastptr;
#else
case 117:lastptr=(uintptr_t)teleport_options_test_handler_number_pad();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 118:lastptr=(uintptr_t)handler_paranoid_confirmation();return lastptr;
#else
case 118:lastptr=(uintptr_t)teleport_options_test_handler_paranoid_confirmation();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 119:lastptr=(uintptr_t)handler_perminv_mode();return lastptr;
#else
case 119:lastptr=(uintptr_t)teleport_options_test_handler_perminv_mode();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 120:lastptr=(uintptr_t)handler_pickup_burden();return lastptr;
#else
case 120:lastptr=(uintptr_t)teleport_options_test_handler_pickup_burden();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 121:lastptr=(uintptr_t)handler_pickup_types();return lastptr;
#else
case 121:lastptr=(uintptr_t)teleport_options_test_handler_pickup_types();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 122:lastptr=(uintptr_t)handler_runmode();return lastptr;
#else
case 122:lastptr=(uintptr_t)teleport_options_test_handler_runmode();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 123:lastptr=(uintptr_t)handler_petattr();return lastptr;
#else
case 123:lastptr=(uintptr_t)teleport_options_test_handler_petattr();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 124:lastptr=(uintptr_t)handler_sortloot();return lastptr;
#else
case 124:lastptr=(uintptr_t)teleport_options_test_handler_sortloot();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 125:lastptr=(uintptr_t)handler_whatis_coord();return lastptr;
#else
case 125:lastptr=(uintptr_t)teleport_options_test_handler_whatis_coord();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 126:lastptr=(uintptr_t)handler_whatis_filter();return lastptr;
#else
case 126:lastptr=(uintptr_t)teleport_options_test_handler_whatis_filter();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 127:lastptr=(uintptr_t)handler_symset((int)(uintptr_t)a0);return lastptr;
#else
case 127:lastptr=(uintptr_t)teleport_options_test_handler_symset((int)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 128:lastptr=(uintptr_t)handler_autopickup_exception();return lastptr;
#else
case 128:lastptr=(uintptr_t)teleport_options_test_handler_autopickup_exception();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 129:lastptr=(uintptr_t)handler_menu_colors();return lastptr;
#else
case 129:lastptr=(uintptr_t)teleport_options_test_handler_menu_colors();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 130:lastptr=(uintptr_t)handler_msgtype();return lastptr;
#else
case 130:lastptr=(uintptr_t)teleport_options_test_handler_msgtype();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 131:lastptr=(uintptr_t)handler_versinfo();return lastptr;
#else
case 131:lastptr=(uintptr_t)teleport_options_test_handler_versinfo();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 132:lastptr=(uintptr_t)handler_windowborders();return lastptr;
#else
case 132:lastptr=(uintptr_t)teleport_options_test_handler_windowborders();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 133:lastptr=(uintptr_t)string_for_opt((char *)(uintptr_t)a0,(boolean)(uintptr_t)a1);return lastptr;
#else
case 133:lastptr=(uintptr_t)teleport_options_test_string_for_opt((char *)(uintptr_t)a0,(boolean)(uintptr_t)a1);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 134:lastptr=(uintptr_t)string_for_env_opt((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(boolean)(uintptr_t)a2);return lastptr;
#else
case 134:lastptr=(uintptr_t)teleport_options_test_string_for_env_opt((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(boolean)(uintptr_t)a2);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 135:bad_negation((const char *)(uintptr_t)a0,(boolean)(uintptr_t)a1);return 0;
#else
case 135:teleport_options_test_bad_negation((const char *)(uintptr_t)a0,(boolean)(uintptr_t)a1);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 136:determine_ambiguities();return 0;
#else
case 136:teleport_options_test_determine_ambiguities();return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 137:lastptr=(uintptr_t)length_without_val((const char *)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#else
case 137:lastptr=(uintptr_t)teleport_options_test_length_without_val((const char *)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#endif
case 138:lastptr=(uintptr_t)match_optname((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)(uintptr_t)a2,(boolean)(uintptr_t)a3);return lastptr;
case 139:reset_duplicate_opt_detection();return 0;
#ifdef TELEPORT_REFERENCE_TU
case 140:lastptr=(uintptr_t)duplicate_opt_detection((int)(uintptr_t)a0);return lastptr;
#else
case 140:lastptr=(uintptr_t)teleport_options_test_duplicate_opt_detection((int)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 141:complain_about_duplicate((int)(uintptr_t)a0);return 0;
#else
case 141:teleport_options_test_complain_about_duplicate((int)(uintptr_t)a0);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 142:rejectoption((const char *)(uintptr_t)a0);return 0;
#else
case 142:teleport_options_test_rejectoption((const char *)(uintptr_t)a0);return 0;
#endif
case 143:lastptr=(uintptr_t)nh_getenv((const char *)(uintptr_t)a0);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 144:nmcpy((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)(uintptr_t)a2);return 0;
#else
case 144:teleport_options_test_nmcpy((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)(uintptr_t)a2);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 145:escapes((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);return 0;
#else
case 145:teleport_options_test_escapes((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);return 0;
#endif
case 146:lastptr=(uintptr_t)txt2key((char *)(uintptr_t)a0);return lastptr;
case 147:initoptions();return 0;
case 148:initoptions_init();return 0;
case 149:initoptions_finish();return 0;
case 150:allopt_array_init();return 0;
#ifdef TELEPORT_REFERENCE_TU
case 151:set_menuobjsyms_flags((int)(uintptr_t)a0);return 0;
#else
case 151:teleport_options_test_set_menuobjsyms_flags((int)(uintptr_t)a0);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 152:lastptr=(uintptr_t)change_inv_order((char *)(uintptr_t)a0);return lastptr;
#else
case 152:lastptr=(uintptr_t)teleport_options_test_change_inv_order((char *)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 153:lastptr=(uintptr_t)warning_opts((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return lastptr;
#else
case 153:lastptr=(uintptr_t)teleport_options_test_warning_opts((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return lastptr;
#endif
case 154:assign_warnings((uchar *)(uintptr_t)a0);return 0;
#ifdef TELEPORT_REFERENCE_TU
case 155:lastptr=(uintptr_t)feature_alert_opts((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return lastptr;
#else
case 155:lastptr=(uintptr_t)teleport_options_test_feature_alert_opts((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return lastptr;
#endif
case 156:lastptr=(uintptr_t)parsebindings((char *)(uintptr_t)a0);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 157:lastptr=(uintptr_t)msgtype2name((int)(uintptr_t)a0);return lastptr;
#else
case 157:lastptr=(uintptr_t)teleport_options_test_msgtype2name((int)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 158:lastptr=(uintptr_t)query_msgtype();return lastptr;
#else
case 158:lastptr=(uintptr_t)teleport_options_test_query_msgtype();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 159:lastptr=(uintptr_t)msgtype_add((int)(uintptr_t)a0,(char *)(uintptr_t)a1);return lastptr;
#else
case 159:lastptr=(uintptr_t)teleport_options_test_msgtype_add((int)(uintptr_t)a0,(char *)(uintptr_t)a1);return lastptr;
#endif
case 160:msgtype_free();return 0;
#ifdef TELEPORT_REFERENCE_TU
case 161:free_one_msgtype((int)(uintptr_t)a0);return 0;
#else
case 161:teleport_options_test_free_one_msgtype((int)(uintptr_t)a0);return 0;
#endif
case 162:lastptr=(uintptr_t)msgtype_type((const char *)(uintptr_t)a0,(boolean)(uintptr_t)a1);return lastptr;
case 163:hide_unhide_msgtypes((boolean)(uintptr_t)a0,(int)(uintptr_t)a1);return 0;
#ifdef TELEPORT_REFERENCE_TU
case 164:lastptr=(uintptr_t)msgtype_count();return lastptr;
#else
case 164:lastptr=(uintptr_t)teleport_options_test_msgtype_count();return lastptr;
#endif
case 165:lastptr=(uintptr_t)msgtype_parse_add((char *)(uintptr_t)a0);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 166:lastptr=(uintptr_t)test_regex_pattern((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return lastptr;
#else
case 166:lastptr=(uintptr_t)teleport_options_test_test_regex_pattern((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 167:lastptr=(uintptr_t)parse_role_opt((int)(uintptr_t)a0,(boolean)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(char **)(uintptr_t)a4);return lastptr;
#else
case 167:lastptr=(uintptr_t)teleport_options_test_parse_role_opt((int)(uintptr_t)a0,(boolean)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(char **)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 168:lastptr=(uintptr_t)get_cnf_role_opt((int)(uintptr_t)a0);return lastptr;
#else
case 168:lastptr=(uintptr_t)teleport_options_test_get_cnf_role_opt((int)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 169:lastptr=(uintptr_t)illegal_menu_cmd_key((uchar)(uintptr_t)a0);return lastptr;
#else
case 169:lastptr=(uintptr_t)teleport_options_test_illegal_menu_cmd_key((uchar)(uintptr_t)a0);return lastptr;
#endif
case 170:oc_to_str((char *)(uintptr_t)a0,(char *)(uintptr_t)a1);return 0;
case 171:add_menu_cmd_alias((char)(uintptr_t)a0,(char)(uintptr_t)a1);return 0;
case 172:lastptr=(uintptr_t)get_menu_cmd_key((char)(uintptr_t)a0);return lastptr;
case 173:lastptr=(uintptr_t)map_menu_cmd((char)(uintptr_t)a0);return lastptr;
case 174:lastptr=(uintptr_t)collect_menu_keys((char *)(uintptr_t)a0,(unsigned int)(uintptr_t)a1,(boolean)(uintptr_t)a2);return lastptr;
case 175:lastptr=(uintptr_t)fruitadd((char *)(uintptr_t)a0,(struct fruit *)(uintptr_t)a1);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 176:lastptr=(uintptr_t)optfn_o_autopickup_exceptions((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 176:lastptr=(uintptr_t)teleport_options_test_optfn_o_autopickup_exceptions((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 177:lastptr=(uintptr_t)optfn_o_bind_keys((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 177:lastptr=(uintptr_t)teleport_options_test_optfn_o_bind_keys((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 178:lastptr=(uintptr_t)optfn_o_autocomplete((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 178:lastptr=(uintptr_t)teleport_options_test_optfn_o_autocomplete((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 179:lastptr=(uintptr_t)optfn_o_menu_colors((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 179:lastptr=(uintptr_t)teleport_options_test_optfn_o_menu_colors((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 180:lastptr=(uintptr_t)optfn_o_message_types((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 180:lastptr=(uintptr_t)teleport_options_test_optfn_o_message_types((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 181:lastptr=(uintptr_t)optfn_o_status_cond((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 181:lastptr=(uintptr_t)teleport_options_test_optfn_o_status_cond((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 182:lastptr=(uintptr_t)optfn_o_status_hilites((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#else
case 182:lastptr=(uintptr_t)teleport_options_test_optfn_o_status_hilites((int)(uintptr_t)a0,(int)(uintptr_t)a1,(boolean)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4);return lastptr;
#endif
case 183:lastptr=(uintptr_t)get_option_value((const char *)(uintptr_t)a0,(boolean)(uintptr_t)a1);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 184:lastptr=(uintptr_t)longest_option_name((int)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#else
case 184:lastptr=(uintptr_t)teleport_options_test_longest_option_name((int)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 185:lastptr=(uintptr_t)doset_simple_menu();return lastptr;
#else
case 185:lastptr=(uintptr_t)teleport_options_test_doset_simple_menu();return lastptr;
#endif
case 186:lastptr=(uintptr_t)doset_simple();return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 187:lastptr=(uintptr_t)term_for_boolean((int)(uintptr_t)a0,(boolean *)(uintptr_t)a1);return lastptr;
#else
case 187:lastptr=(uintptr_t)teleport_options_test_term_for_boolean((int)(uintptr_t)a0,(boolean *)(uintptr_t)a1);return lastptr;
#endif
case 188:lastptr=(uintptr_t)doset();return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 189:reset_needed_visuals();return 0;
#else
case 189:teleport_options_test_reset_needed_visuals();return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 190:doset_add_menu((winid)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)(uintptr_t)a3,(int)(uintptr_t)a4);return 0;
#else
case 190:teleport_options_test_doset_add_menu((winid)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)(uintptr_t)a3,(int)(uintptr_t)a4);return 0;
#endif
case 191:show_menu_controls((winid)(uintptr_t)a0,(boolean)(uintptr_t)a1);return 0;
#ifdef TELEPORT_REFERENCE_TU
case 192:lastptr=(uintptr_t)count_cond();return lastptr;
#else
case 192:lastptr=(uintptr_t)teleport_options_test_count_cond();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 193:lastptr=(uintptr_t)count_apes();return lastptr;
#else
case 193:lastptr=(uintptr_t)teleport_options_test_count_apes();return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 194:lastptr=(uintptr_t)handle_add_list_remove((const char *)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#else
case 194:lastptr=(uintptr_t)teleport_options_test_handle_add_list_remove((const char *)(uintptr_t)a0,(int)(uintptr_t)a1);return lastptr;
#endif
case 195:lastptr=(uintptr_t)dotogglepickup();return lastptr;
case 196:lastptr=(uintptr_t)toggle_bool_option((const char *)(uintptr_t)a0);return lastptr;
case 197:lastptr=(uintptr_t)add_autopickup_exception((const char *)(uintptr_t)a0);return lastptr;
#ifdef TELEPORT_REFERENCE_TU
case 198:remove_autopickup_exception((struct autopickup_exception *)(uintptr_t)a0);return 0;
#else
case 198:teleport_options_test_remove_autopickup_exception((struct autopickup_exception *)(uintptr_t)a0);return 0;
#endif
case 199:free_autopickup_exceptions();return 0;
case 200:lastptr=(uintptr_t)sym_val((const char *)(uintptr_t)a0);return lastptr;
case 201:option_help();return 0;
#ifdef TELEPORT_REFERENCE_TU
case 202:all_options_conds((strbuf_t *)(uintptr_t)a0);return 0;
#else
case 202:teleport_options_test_all_options_conds((strbuf_t *)(uintptr_t)a0);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 203:all_options_menucolors((strbuf_t *)(uintptr_t)a0);return 0;
#else
case 203:teleport_options_test_all_options_menucolors((strbuf_t *)(uintptr_t)a0);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 204:all_options_msgtypes((strbuf_t *)(uintptr_t)a0);return 0;
#else
case 204:teleport_options_test_all_options_msgtypes((strbuf_t *)(uintptr_t)a0);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 205:all_options_apes((strbuf_t *)(uintptr_t)a0);return 0;
#else
case 205:teleport_options_test_all_options_apes((strbuf_t *)(uintptr_t)a0);return 0;
#endif
case 206:all_options_strbuf((strbuf_t *)(uintptr_t)a0);return 0;
case 207:next_opt((winid)(uintptr_t)a0,(const char *)(uintptr_t)a1);return 0;
case 208:set_option_mod_status((const char *)(uintptr_t)a0,(int)(uintptr_t)a1);return 0;
case 209:set_wc_option_mod_status((unsigned long)(uintptr_t)a0,(int)(uintptr_t)a1);return 0;
#ifdef TELEPORT_REFERENCE_TU
case 210:lastptr=(uintptr_t)is_wc_option((const char *)(uintptr_t)a0);return lastptr;
#else
case 210:lastptr=(uintptr_t)teleport_options_test_is_wc_option((const char *)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 211:lastptr=(uintptr_t)wc_supported((const char *)(uintptr_t)a0);return lastptr;
#else
case 211:lastptr=(uintptr_t)teleport_options_test_wc_supported((const char *)(uintptr_t)a0);return lastptr;
#endif
case 212:set_wc2_option_mod_status((unsigned long)(uintptr_t)a0,(int)(uintptr_t)a1);return 0;
#ifdef TELEPORT_REFERENCE_TU
case 213:lastptr=(uintptr_t)is_wc2_option((const char *)(uintptr_t)a0);return lastptr;
#else
case 213:lastptr=(uintptr_t)teleport_options_test_is_wc2_option((const char *)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 214:lastptr=(uintptr_t)wc2_supported((const char *)(uintptr_t)a0);return lastptr;
#else
case 214:lastptr=(uintptr_t)teleport_options_test_wc2_supported((const char *)(uintptr_t)a0);return lastptr;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 215:wc_set_font_name((int)(uintptr_t)a0,(char *)(uintptr_t)a1);return 0;
#else
case 215:teleport_options_test_wc_set_font_name((int)(uintptr_t)a0,(char *)(uintptr_t)a1);return 0;
#endif
#ifdef TELEPORT_REFERENCE_TU
case 216:lastptr=(uintptr_t)wc_set_window_colors((char *)(uintptr_t)a0);return lastptr;
#else
case 216:lastptr=(uintptr_t)teleport_options_test_wc_set_window_colors((char *)(uintptr_t)a0);return lastptr;
#endif
case 217:options_free_window_colors();return 0;
case 218:set_playmode();return 0;
#ifdef TELEPORT_REFERENCE_TU
case 219:enhance_menu_text((char *)(uintptr_t)a0,(size_t)(uintptr_t)a1,(int)(uintptr_t)a2,(boolean *)(uintptr_t)a3,(struct allopt_t *)(uintptr_t)a4);return 0;
#else
case 219:teleport_options_test_enhance_menu_text((char *)(uintptr_t)a0,(size_t)(uintptr_t)a1,(int)(uintptr_t)a2,(boolean *)(uintptr_t)a3,(struct allopt_t *)(uintptr_t)a4);return 0;
#endif
case 220:heed_all_options();return 0;
case 221:disregard_all_options();return 0;
case 222:heed_this_option((enum opt)(uintptr_t)a0);return 0;
case 223:disregard_this_option((enum opt)(uintptr_t)a0);return 0;
default:abort();}}
static void*data_at(int which){switch(which){
case 0:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&allopt_init;
#else
return teleport_options_storage(0);
#endif
case 1:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&allopt;
#else
return teleport_options_storage(1);
#endif
case 2:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&empty_optstr;
#else
return teleport_options_storage(2);
#endif
case 3:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&duplicate;
#else
return teleport_options_storage(3);
#endif
case 4:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&using_alias;
#else
return teleport_options_storage(4);
#endif
case 5:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&give_opt_msg;
#else
return teleport_options_storage(5);
#endif
case 6:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&opt_set_in_config;
#else
return teleport_options_storage(6);
#endif
case 7:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&roleoptvals;
#else
return teleport_options_storage(7);
#endif
case 8:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&OptS_type;
#else
return teleport_options_storage(8);
#endif
case 9:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&def_inv_order;
#else
return teleport_options_storage(9);
#endif
case 10:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&none;
#else
return teleport_options_storage(10);
#endif
case 11:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&randomrole;
#else
return teleport_options_storage(11);
#endif
case 12:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&to_be_done;
#else
return teleport_options_storage(12);
#endif
case 13:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&defopt;
#else
return teleport_options_storage(13);
#endif
case 14:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&defbrief;
#else
return teleport_options_storage(14);
#endif
case 15:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&paranoia;
#else
return teleport_options_storage(15);
#endif
case 16:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&menutype;
#else
return teleport_options_storage(16);
#endif
case 17:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&msgwind;
#else
return teleport_options_storage(17);
#endif
case 18:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&unlocktypes;
#else
return teleport_options_storage(18);
#endif
case 19:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&burdentype;
#else
return teleport_options_storage(19);
#endif
case 20:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&runmodes;
#else
return teleport_options_storage(20);
#endif
case 21:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&sortltype;
#else
return teleport_options_storage(21);
#endif
case 22:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&perminv_modes;
#else
return teleport_options_storage(22);
#endif
case 23:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&objsymvals;
#else
return teleport_options_storage(23);
#endif
case 24:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&default_menu_cmd_info;
#else
return teleport_options_storage(24);
#endif
case 25:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&n_currently_set;
#else
return teleport_options_storage(25);
#endif
case 26:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&roleopt2opt;
#else
return teleport_options_storage(26);
#endif
case 34:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&wcnames;
#else
return teleport_options_storage(34);
#endif
case 35:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&wcshortnames;
#else
return teleport_options_storage(35);
#endif
case 43:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&msgtype_names;
#else
return teleport_options_storage(43);
#endif
case 59:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&opt_intro;
#else
return teleport_options_storage(59);
#endif
case 60:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&opt_epilog;
#else
return teleport_options_storage(60);
#endif
case 62:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&wc_options;
#else
return teleport_options_storage(62);
#endif
case 63:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&wc2_options;
#else
return teleport_options_storage(63);
#endif
case 64:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&fgp;
#else
return teleport_options_storage(64);
#endif
case 65:
#ifdef TELEPORT_REFERENCE_TU
return(void*)&bgp;
#else
return teleport_options_storage(65);
#endif
default:return teleport_options_storage(which);}}
uintptr_t probe_data(int i){return(uintptr_t)data_at(i);}
uintptr_t probe_buffer(int i){return(uintptr_t)buf[i];}
uintptr_t probe_global(int i){return(uintptr_t)teleport_options_global(i);}
uint64_t probe_layout(int i){return teleport_options_layout(i);}
uint64_t probe_read(int k,uint64_t p,int f){return teleport_options_read(k,(void*)(uintptr_t)p,f);}
void probe_write(int k,uint64_t p,int f,uint64_t v){teleport_options_write(k,(void*)(uintptr_t)p,f,v);}
uintptr_t probe_address(int k,uint64_t p,int f){return(uintptr_t)teleport_options_address(k,(void*)(uintptr_t)p,f);}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_trace(void){return tracebuf;}void probe_clear(void){ti=0;tracebuf[0]=0;}
uintptr_t probe_result(void){return lastptr;}
void probe_option(int i,int64_t v){opts[i]=v;}
void probe_return(int i,int64_t v){returns[i]=v;}
void probe_reply(int i,const char*s){strncpy(replies[i],s,BUFSZ-1);}
void probe_menu(int i,int v){if(i<0){select_n=select_i=0;return;}select_values[i]=v;if(select_n<=i)select_n=i+1;}
void probe_input(int i,const char*s){if(i<0){input_n=input_i=0;return;}strncpy(input_values[i],s,BUFSZ-1);if(input_n<=i)input_n=i+1;}

void probe_reset(void){
 if(!baseline_ready){objects_globals_init();monst_globals_init();}else{memcpy(data_at(1),baseline,sizeof baseline);}
 memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&u,0,sizeof u);memset(&go,0,sizeof go);memset(&program_state,0,sizeof program_state);memset((void*)&windowprocs,0,sizeof windowprocs);memset(&gc,0,sizeof gc);memset(&gs,0,sizeof gs);memset(&svp,0,sizeof svp);memset(&ga,0,sizeof ga);memset(&gm,0,sizeof gm);memset(&svc,0,sizeof svc);memset(&gf,0,sizeof gf);
 windowprocs.name="tty";windowprocs.wp_id=wp_tty;windowprocs.win_display_file=backend_file;windowprocs.win_number_pad=backend_pad;windowprocs.win_preference_update=backend_preference;windowprocs.win_create_nhwindow=create;windowprocs.win_destroy_nhwindow=destroy;windowprocs.win_clear_nhwindow=clear;windowprocs.win_display_nhwindow=display;windowprocs.win_putstr=put;windowprocs.win_start_menu=start;windowprocs.win_end_menu=end;windowprocs.win_curs=backend_curs;windowprocs.win_wait_synch=syncwin;windowprocs.win_mark_synch=syncwin;
 windowprocs.wincap=WC_COLOR|WC_HILITE_PET;windowprocs.wincap2=WC2_HITPOINTBAR|WC2_FLUSH_STATUS;
 flags.initrole=flags.initrace=flags.initgend=flags.initalign=ROLE_NONE;u.umonnum=u.umonster=PM_HUMAN;u.ulevel=1;u.ux=10;u.uy=8;u.uz.dnum=1;u.uz.dlevel=2;svp.plname[0]=0;strcpy(svp.pl_fruit,"slime mold");strcpy(flags.inv_order,"$)[%?+!=/(*`0_");go.opt_initial=TRUE;go.opt_phase=builtin_opt;
 if(grown){free(grown);grown=0;}memset(buf,0,sizeof buf);memset(opts,0,sizeof opts);memset(returns,0,sizeof returns);memset(replies,0,sizeof replies);strcpy(replies[42],"fixture");input_n=input_i=select_n=select_i=callback_depth=0;rngstate=1;rngline=0;rngfile=rngfn=0;lastptr=0;free_count=0;strbuf_empty(&stringbuf);strbuf_init(&stringbuf);probe_clear();
 if(!baseline_ready){allopt_array_init();memcpy(baseline,data_at(1),sizeof baseline);baseline_ready=1;probe_clear();}
}

uint64_t probe_sizes(int which){return which==0?sizeof(struct allopt_t):which==1?sizeof(anything):sizeof(menu_item);}
const char*probe_snapshot(void){ni=snprintf(snap,sizeof snap,"free:%d;phase:%d;initial:%d;flag:%d;wc:%d,%d,%d,%d;fruit:%s;name:%s;",free_count,go.opt_phase,go.opt_initial,options_set_window_colors_flag,wcolors_opt[0],wcolors_opt[1],wcolors_opt[2],wcolors_opt[3],svp.pl_fruit,svp.plname);struct allopt_t*t=data_at(1);for(int i=0;i<=OPTCOUNT;i++)ni+=snprintf(snap+ni,sizeof snap-ni,"%d:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;",i,t[i].minmatch,t[i].setwhere,t[i].opt_in_out,t[i].initval,t[i].has_handler,t[i].dupdetected,t[i].disregarded,t[i].addr?*t[i].addr:-1,t[i].negateok,t[i].valok);return snap;}

int probe_context_size(void){return sizeof(struct allopt_t);}
int probe_layout_count(void){return 412;}
const char*probe_layout_name(int i){static const char*const names[]={"pointerSize","longSize","intSize","charSigned","littleEndian","size:menu_cmd_t","size:struct Align","size:struct Gender","size:struct Race","size:struct Role","size:struct RoleName","size:struct accessibility_data","size:struct action","size:struct allopt_t","size:struct autopickup_exception","size:struct class_sym","size:struct cmd","size:struct color_and_attr","size:struct condtests_t","size:struct const_globals","size:struct context_info","size:struct d_level","size:struct dgn_topology","size:struct display_hints","size:struct flag","size:struct fruit","size:struct instance_flags","size:struct instance_globals_a","size:struct instance_globals_c","size:struct instance_globals_d","size:struct instance_globals_f","size:struct instance_globals_h","size:struct instance_globals_m","size:struct instance_globals_n","size:struct instance_globals_o","size:struct instance_globals_p","size:struct instance_globals_s","size:struct instance_globals_saved_b","size:struct instance_globals_saved_c","size:struct instance_globals_saved_d","size:struct instance_globals_saved_p","size:struct instance_globals_t","size:struct instance_globals_v","size:struct instance_globals_w","size:struct menucoloring","size:struct menuscrollinfo","size:struct mi","size:struct nhcoord","size:struct nomakedefs_s","size:struct objclass","size:struct objdescr","size:struct objsymopt","size:struct options_msgtype_name","size:struct paranoia_opts","size:struct plinemsg_type","size:struct sinfo","size:struct symdef","size:struct symsetentry","size:struct tc_gbl_data","size:struct teleport_options_action","size:struct teleport_options_menu_cmd_t","size:struct teleport_options_menuscrollinfo","size:struct teleport_options_objsymopt","size:struct teleport_options_options_msgtype_name","size:struct teleport_options_paranoia_opts","size:struct teleport_options_xtra_cntrls","size:struct u_roleplay","size:struct wc_Opt","size:struct window_procs","size:struct windowcolors_struct","size:struct xtra_cntrls","size:struct you","size:union any","AMULET_CLASS","ARMOR_CLASS","BALL_CLASS","BOULDER","BoolOpt","CHAIN_CLASS","COIN_CLASS","CONDITION_COUNT","CompOpt","EXT_ENCUMBER","FOOD_CLASS","GEM_CLASS","GFILTER_AREA","GFILTER_NONE","GFILTER_VIEW","GOLD_SYM","HVY_ENCUMBER","InvOptInUse","InvOptNone","InvOptOn","InvSparse","LOW_PM","MAP_OPTION","MAXMCLASSES","MAXOCLASSES","MAXPCHARS","MAX_ROLEOPT","MENU_OPTION","MESSAGE_OPTION","MOD_ENCUMBER","NUMMONS","NUM_GRAPHICS","No","OPTCOUNT","OVERLOADED","Off","On","OptS_Advanced","OptS_Behavior","OptS_General","OptS_Map","OptS_Status","OthrOpt","POTION_CLASS","PRIMARYSET","RING_CLASS","ROCK_CLASS","ROGUESET","RUN_CRAWL","RUN_LEAP","RUN_STEP","RUN_TPORT","SCROLL_CLASS","SLIME_MOLD","SLT_ENCUMBER","SPBOOK_CLASS","STATUS_OPTION","STONE","SYM_BOULDER","S_expl_br","S_stone","S_vbeam","S_water","TEXT_OPTION","TOOL_CLASS","TRAPNUM","Term_Excluded","Term_False","Term_Off","UNENCUMBERED","VANQ_MLVL_MNDX","VENOM_SYM","WAND_CLASS","WC_COUNT","WEAPON_CLASS","Yes","builtin_opt","cmdline_opt","do_custom_colors","do_custom_symbols","do_handler","do_init","do_set","environ_opt","get_cnf_val","get_val","gm_optionchange","num_opt_phases","num_terms","opt_BIOS","opt_DECgraphics","opt_IBMgraphics","opt_accessiblemsg","opt_acoustics","opt_align_message","opt_align_status","opt_alignment","opt_altkeyhandling","opt_altmeta","opt_armorstatus","opt_ascii_map","opt_autodescribe","opt_autodig","opt_autoopen","opt_autopickup","opt_autoquiver","opt_autounlock","opt_bgcolors","opt_blind","opt_bones","opt_boulder","opt_catname","opt_checkpoint","opt_cmdassist","opt_color","opt_confirm","opt_crash_email","opt_crash_name","opt_crash_urlmax","opt_customcolors","opt_customsymbols","opt_dark_room","opt_deaf","opt_debug_hunger","opt_debug_mongen","opt_debug_overwrite_stairs","opt_disclose","opt_dogname","opt_dropped_nopick","opt_dungeon","opt_effects","opt_eight_bit_tty","opt_extmenu","opt_female","opt_fireassist","opt_fixinv","opt_font_map","opt_font_menu","opt_font_message","opt_font_size_map","opt_font_size_menu","opt_font_size_message","opt_font_size_status","opt_font_size_text","opt_font_status","opt_font_text","opt_force_invmenu","opt_fruit","opt_fullscreen","opt_gender","opt_glyph","opt_goldX","opt_guicolor","opt_help","opt_herecmd_menu","opt_hilite_pet","opt_hilite_pile","opt_hilite_status","opt_hitpointbar","opt_horsename","opt_idlecheckpoint","opt_ignintr","opt_implicit_uncursed","opt_in","opt_legacy","opt_lit_corridor","opt_lootabc","opt_mail","opt_map_mode","opt_mention_decor","opt_mention_map","opt_mention_walls","opt_menu_deselect_all","opt_menu_deselect_page","opt_menu_first_page","opt_menu_headings","opt_menu_invert_all","opt_menu_invert_page","opt_menu_last_page","opt_menu_next_page","opt_menu_objsyms","opt_menu_overlay","opt_menu_previous_page","opt_menu_search","opt_menu_select_all","opt_menu_select_page","opt_menu_shift_left","opt_menu_shift_right","opt_menu_tab_sep","opt_menucolors","opt_menuinvertmode","opt_menustyle","opt_mon_movement","opt_monpolycontrol","opt_monsters","opt_montelecontrol","opt_mouse_support","opt_msg_window","opt_msghistory","opt_name","opt_news","opt_nudist","opt_null","opt_number_pad","opt_o_autocomplete","opt_o_autopickup_exceptions","opt_o_bind_keys","opt_o_menu_colors","opt_o_message_types","opt_o_status_cond","opt_o_status_hilites","opt_objects","opt_out","opt_packorder","opt_paranoid_confirmation","opt_pauper","opt_perm_invent","opt_perminv_mode","opt_petattr","opt_pettype","opt_pickup_burden","opt_pickup_stolen","opt_pickup_thrown","opt_pickup_types","opt_pile_limit","opt_player_selection","opt_playmode","opt_popup_dialog","opt_preload_tiles","opt_price_quotes","opt_pushweapon","opt_query_menu","opt_quick_farsight","opt_race","opt_rawio","opt_reroll","opt_rest_on_space","opt_roguesymset","opt_role","opt_runmode","opt_safe_pet","opt_safe_wait","opt_sanity_check","opt_scores","opt_scroll_amount","opt_scroll_margin","opt_selectsaved","opt_showdamage","opt_showexp","opt_showrace","opt_showscore","opt_showvers","opt_silent","opt_softkeyboard","opt_sortdiscoveries","opt_sortloot","opt_sortpack","opt_sortvanquished","opt_soundlib","opt_sounds","opt_sparkle","opt_splash_screen","opt_spot_monsters","opt_standout","opt_status_updates","opt_statushilites","opt_statuslines","opt_suppress_alert","opt_symset","opt_term_cols","opt_term_rows","opt_terrainstatus","opt_tile_file","opt_tile_height","opt_tile_width","opt_tiled_map","opt_time","opt_timed_delay","opt_tips","opt_tombstone","opt_toptenwin","opt_traps","opt_travel","opt_travel_debug","opt_tutorial","opt_use_darkgray","opt_use_inverse","opt_use_truecolor","opt_vary_msgcount","opt_verbose","opt_versinfo","opt_voices","opt_vt_sounddata","opt_vt_tiledata","opt_warnings","opt_weaponstatus","opt_whatis_coord","opt_whatis_filter","opt_whatis_menu","opt_whatis_moveskip","opt_windowborders","opt_windowcolors","opt_windowtype","opt_wizmgender","opt_wizweight","opt_wraptext","optn_err","optn_ok","optn_silenterr","pfx_cond_","pfx_font","play_opt","set_gameview","set_hidden","set_in_config","set_in_game","set_in_sysconf","set_wiznofuz","set_wizonly","syscf_opt","wcolor_menu","wcolor_message","wcolor_status","wcolor_text","wp_curses","wp_tty","enumSigned:OptSection","enumSigned:OptType","enumSigned:Y_N","enumSigned:menu_terminology_preference","enumSigned:opt","enumSigned:option_phases","enumSigned:optn_result","enumSigned:optset_restrictions","enumSigned:requests","enumSigned:soundlib_ids","enumSigned:symset_handling_types","enumSigned:window_option_types","enumSigned:wp_ids"};return names[i];}
uint64_t probe_layout_value(int i){return teleport_options_layout(i);}
uintptr_t probe_function_token(int i){switch(i){
case 0:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)do_reqmenu;
#else
return(uintptr_t)teleport_options_function(0);
#endif
case 1:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_DECgraphics;
#else
return(uintptr_t)teleport_options_function(1);
#endif
case 2:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_IBMgraphics;
#else
return(uintptr_t)teleport_options_function(2);
#endif
case 3:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_align_message;
#else
return(uintptr_t)teleport_options_function(3);
#endif
case 4:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_align_status;
#else
return(uintptr_t)teleport_options_function(4);
#endif
case 5:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_alignment;
#else
return(uintptr_t)teleport_options_function(5);
#endif
case 6:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_altkeyhandling;
#else
return(uintptr_t)teleport_options_function(6);
#endif
case 7:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_autounlock;
#else
return(uintptr_t)teleport_options_function(7);
#endif
case 8:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_boolean;
#else
return(uintptr_t)teleport_options_function(8);
#endif
case 9:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_boulder;
#else
return(uintptr_t)teleport_options_function(9);
#endif
case 10:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_catname;
#else
return(uintptr_t)teleport_options_function(10);
#endif
case 11:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_crash_email;
#else
return(uintptr_t)teleport_options_function(11);
#endif
case 12:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_crash_name;
#else
return(uintptr_t)teleport_options_function(12);
#endif
case 13:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_crash_urlmax;
#else
return(uintptr_t)teleport_options_function(13);
#endif
case 14:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_disclose;
#else
return(uintptr_t)teleport_options_function(14);
#endif
case 15:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_dogname;
#else
return(uintptr_t)teleport_options_function(15);
#endif
case 16:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_dungeon;
#else
return(uintptr_t)teleport_options_function(16);
#endif
case 17:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_effects;
#else
return(uintptr_t)teleport_options_function(17);
#endif
case 18:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_map;
#else
return(uintptr_t)teleport_options_function(18);
#endif
case 19:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_menu;
#else
return(uintptr_t)teleport_options_function(19);
#endif
case 20:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_message;
#else
return(uintptr_t)teleport_options_function(20);
#endif
case 21:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_size_map;
#else
return(uintptr_t)teleport_options_function(21);
#endif
case 22:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_size_menu;
#else
return(uintptr_t)teleport_options_function(22);
#endif
case 23:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_size_message;
#else
return(uintptr_t)teleport_options_function(23);
#endif
case 24:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_size_status;
#else
return(uintptr_t)teleport_options_function(24);
#endif
case 25:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_size_text;
#else
return(uintptr_t)teleport_options_function(25);
#endif
case 26:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_status;
#else
return(uintptr_t)teleport_options_function(26);
#endif
case 27:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_font_text;
#else
return(uintptr_t)teleport_options_function(27);
#endif
case 28:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_fruit;
#else
return(uintptr_t)teleport_options_function(28);
#endif
case 29:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_gender;
#else
return(uintptr_t)teleport_options_function(29);
#endif
case 30:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_glyph;
#else
return(uintptr_t)teleport_options_function(30);
#endif
case 31:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_hilite_status;
#else
return(uintptr_t)teleport_options_function(31);
#endif
case 32:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_horsename;
#else
return(uintptr_t)teleport_options_function(32);
#endif
case 33:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_map_mode;
#else
return(uintptr_t)teleport_options_function(33);
#endif
case 34:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_deselect_all;
#else
return(uintptr_t)teleport_options_function(34);
#endif
case 35:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_deselect_page;
#else
return(uintptr_t)teleport_options_function(35);
#endif
case 36:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_first_page;
#else
return(uintptr_t)teleport_options_function(36);
#endif
case 37:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_headings;
#else
return(uintptr_t)teleport_options_function(37);
#endif
case 38:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_invert_all;
#else
return(uintptr_t)teleport_options_function(38);
#endif
case 39:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_invert_page;
#else
return(uintptr_t)teleport_options_function(39);
#endif
case 40:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_last_page;
#else
return(uintptr_t)teleport_options_function(40);
#endif
case 41:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_next_page;
#else
return(uintptr_t)teleport_options_function(41);
#endif
case 42:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_objsyms;
#else
return(uintptr_t)teleport_options_function(42);
#endif
case 43:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_previous_page;
#else
return(uintptr_t)teleport_options_function(43);
#endif
case 44:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_search;
#else
return(uintptr_t)teleport_options_function(44);
#endif
case 45:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_select_all;
#else
return(uintptr_t)teleport_options_function(45);
#endif
case 46:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_select_page;
#else
return(uintptr_t)teleport_options_function(46);
#endif
case 47:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_shift_left;
#else
return(uintptr_t)teleport_options_function(47);
#endif
case 48:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menu_shift_right;
#else
return(uintptr_t)teleport_options_function(48);
#endif
case 49:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menuinvertmode;
#else
return(uintptr_t)teleport_options_function(49);
#endif
case 50:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_menustyle;
#else
return(uintptr_t)teleport_options_function(50);
#endif
case 51:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_monsters;
#else
return(uintptr_t)teleport_options_function(51);
#endif
case 52:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_mouse_support;
#else
return(uintptr_t)teleport_options_function(52);
#endif
case 53:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_msg_window;
#else
return(uintptr_t)teleport_options_function(53);
#endif
case 54:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_msghistory;
#else
return(uintptr_t)teleport_options_function(54);
#endif
case 55:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_name;
#else
return(uintptr_t)teleport_options_function(55);
#endif
case 56:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_number_pad;
#else
return(uintptr_t)teleport_options_function(56);
#endif
case 57:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_o_autocomplete;
#else
return(uintptr_t)teleport_options_function(57);
#endif
case 58:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_o_autopickup_exceptions;
#else
return(uintptr_t)teleport_options_function(58);
#endif
case 59:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_o_bind_keys;
#else
return(uintptr_t)teleport_options_function(59);
#endif
case 60:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_o_menu_colors;
#else
return(uintptr_t)teleport_options_function(60);
#endif
case 61:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_o_message_types;
#else
return(uintptr_t)teleport_options_function(61);
#endif
case 62:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_o_status_cond;
#else
return(uintptr_t)teleport_options_function(62);
#endif
case 63:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_o_status_hilites;
#else
return(uintptr_t)teleport_options_function(63);
#endif
case 64:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_objects;
#else
return(uintptr_t)teleport_options_function(64);
#endif
case 65:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_packorder;
#else
return(uintptr_t)teleport_options_function(65);
#endif
case 66:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_paranoid_confirmation;
#else
return(uintptr_t)teleport_options_function(66);
#endif
case 67:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_perminv_mode;
#else
return(uintptr_t)teleport_options_function(67);
#endif
case 68:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_petattr;
#else
return(uintptr_t)teleport_options_function(68);
#endif
case 69:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_pettype;
#else
return(uintptr_t)teleport_options_function(69);
#endif
case 70:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_pickup_burden;
#else
return(uintptr_t)teleport_options_function(70);
#endif
case 71:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_pickup_types;
#else
return(uintptr_t)teleport_options_function(71);
#endif
case 72:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_pile_limit;
#else
return(uintptr_t)teleport_options_function(72);
#endif
case 73:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_player_selection;
#else
return(uintptr_t)teleport_options_function(73);
#endif
case 74:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_playmode;
#else
return(uintptr_t)teleport_options_function(74);
#endif
case 75:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_race;
#else
return(uintptr_t)teleport_options_function(75);
#endif
case 76:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_roguesymset;
#else
return(uintptr_t)teleport_options_function(76);
#endif
case 77:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_role;
#else
return(uintptr_t)teleport_options_function(77);
#endif
case 78:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_runmode;
#else
return(uintptr_t)teleport_options_function(78);
#endif
case 79:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_scores;
#else
return(uintptr_t)teleport_options_function(79);
#endif
case 80:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_scroll_amount;
#else
return(uintptr_t)teleport_options_function(80);
#endif
case 81:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_scroll_margin;
#else
return(uintptr_t)teleport_options_function(81);
#endif
case 82:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_sortdiscoveries;
#else
return(uintptr_t)teleport_options_function(82);
#endif
case 83:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_sortloot;
#else
return(uintptr_t)teleport_options_function(83);
#endif
case 84:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_sortvanquished;
#else
return(uintptr_t)teleport_options_function(84);
#endif
case 85:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_soundlib;
#else
return(uintptr_t)teleport_options_function(85);
#endif
case 86:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_statushilites;
#else
return(uintptr_t)teleport_options_function(86);
#endif
case 87:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_statuslines;
#else
return(uintptr_t)teleport_options_function(87);
#endif
case 88:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_suppress_alert;
#else
return(uintptr_t)teleport_options_function(88);
#endif
case 89:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_symset;
#else
return(uintptr_t)teleport_options_function(89);
#endif
case 90:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_term_cols;
#else
return(uintptr_t)teleport_options_function(90);
#endif
case 91:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_term_rows;
#else
return(uintptr_t)teleport_options_function(91);
#endif
case 92:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_tile_file;
#else
return(uintptr_t)teleport_options_function(92);
#endif
case 93:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_tile_height;
#else
return(uintptr_t)teleport_options_function(93);
#endif
case 94:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_tile_width;
#else
return(uintptr_t)teleport_options_function(94);
#endif
case 95:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_traps;
#else
return(uintptr_t)teleport_options_function(95);
#endif
case 96:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_vary_msgcount;
#else
return(uintptr_t)teleport_options_function(96);
#endif
case 97:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_versinfo;
#else
return(uintptr_t)teleport_options_function(97);
#endif
case 98:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_warnings;
#else
return(uintptr_t)teleport_options_function(98);
#endif
case 99:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_whatis_coord;
#else
return(uintptr_t)teleport_options_function(99);
#endif
case 100:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_whatis_filter;
#else
return(uintptr_t)teleport_options_function(100);
#endif
case 101:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_windowborders;
#else
return(uintptr_t)teleport_options_function(101);
#endif
case 102:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_windowcolors;
#else
return(uintptr_t)teleport_options_function(102);
#endif
case 103:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)optfn_windowtype;
#else
return(uintptr_t)teleport_options_function(103);
#endif
case 104:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)pfxfn_cond_;
#else
return(uintptr_t)teleport_options_function(104);
#endif
case 105:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)pfxfn_font;
#else
return(uintptr_t)teleport_options_function(105);
#endif
case 106:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)rn2;
#else
return(uintptr_t)teleport_options_function(106);
#endif
case 107:
#ifdef TELEPORT_REFERENCE_TU
return(uintptr_t)rn2_on_display_rng;
#else
return(uintptr_t)teleport_options_function(107);
#endif
default:abort();}}

const unsigned char*probe_table_bytes(int which,int row){static unsigned char bytes[sizeof(struct allopt_t)];struct allopt_t*p=(struct allopt_t*)data_at(which)+row;memcpy(bytes,p,sizeof bytes);
#define ZERO_FIELD(f) memset(bytes+offsetof(struct allopt_t,f),0,sizeof p->f)
ZERO_FIELD(name);ZERO_FIELD(addr);ZERO_FIELD(optfn);ZERO_FIELD(alias);ZERO_FIELD(descr);ZERO_FIELD(prefixgw);
#undef ZERO_FIELD
return bytes;}
const char*probe_catalogue(void){static char out[256];snprintf(out,sizeof out,"%d:%d:%s:%s:%s",objects[SLIME_MOLD].oc_class==FOOD_CLASS,mons[PM_HUMAN].pmidx==PM_HUMAN,OBJ_NAME(objects[SLIME_MOLD]),mons[PM_HUMAN].pmnames[NEUTRAL],roles[0].name.m);return out;}
uintptr_t probe_stringbuf(void){return(uintptr_t)&stringbuf;}const char*probe_stringbuf_text(void){return stringbuf.str?stringbuf.str:"";}


#ifdef TELEPORT_REFERENCE_TU
_Static_assert(sizeof(struct paranoia_opts)==sizeof(struct teleport_options_paranoia_opts),"OPTIONS original paranoia_opts size");
_Static_assert(offsetof(struct paranoia_opts,flagmask)==offsetof(struct teleport_options_paranoia_opts,flagmask),"OPTIONS original paranoia_opts.flagmask offset");
_Static_assert(sizeof(((struct paranoia_opts*)0)->flagmask)==sizeof(((struct teleport_options_paranoia_opts*)0)->flagmask),"OPTIONS original paranoia_opts.flagmask width");
_Static_assert(offsetof(struct paranoia_opts,argname)==offsetof(struct teleport_options_paranoia_opts,argname),"OPTIONS original paranoia_opts.argname offset");
_Static_assert(sizeof(((struct paranoia_opts*)0)->argname)==sizeof(((struct teleport_options_paranoia_opts*)0)->argname),"OPTIONS original paranoia_opts.argname width");
_Static_assert(offsetof(struct paranoia_opts,argMinLen)==offsetof(struct teleport_options_paranoia_opts,argMinLen),"OPTIONS original paranoia_opts.argMinLen offset");
_Static_assert(sizeof(((struct paranoia_opts*)0)->argMinLen)==sizeof(((struct teleport_options_paranoia_opts*)0)->argMinLen),"OPTIONS original paranoia_opts.argMinLen width");
_Static_assert(offsetof(struct paranoia_opts,synonym)==offsetof(struct teleport_options_paranoia_opts,synonym),"OPTIONS original paranoia_opts.synonym offset");
_Static_assert(sizeof(((struct paranoia_opts*)0)->synonym)==sizeof(((struct teleport_options_paranoia_opts*)0)->synonym),"OPTIONS original paranoia_opts.synonym width");
_Static_assert(offsetof(struct paranoia_opts,synMinLen)==offsetof(struct teleport_options_paranoia_opts,synMinLen),"OPTIONS original paranoia_opts.synMinLen offset");
_Static_assert(sizeof(((struct paranoia_opts*)0)->synMinLen)==sizeof(((struct teleport_options_paranoia_opts*)0)->synMinLen),"OPTIONS original paranoia_opts.synMinLen width");
_Static_assert(offsetof(struct paranoia_opts,explain)==offsetof(struct teleport_options_paranoia_opts,explain),"OPTIONS original paranoia_opts.explain offset");
_Static_assert(sizeof(((struct paranoia_opts*)0)->explain)==sizeof(((struct teleport_options_paranoia_opts*)0)->explain),"OPTIONS original paranoia_opts.explain width");
_Static_assert(sizeof(struct objsymopt)==sizeof(struct teleport_options_objsymopt),"OPTIONS original objsymopt size");
_Static_assert(offsetof(struct objsymopt,num)==offsetof(struct teleport_options_objsymopt,num),"OPTIONS original objsymopt.num offset");
_Static_assert(sizeof(((struct objsymopt*)0)->num)==sizeof(((struct teleport_options_objsymopt*)0)->num),"OPTIONS original objsymopt.num width");
_Static_assert(offsetof(struct objsymopt,nam)==offsetof(struct teleport_options_objsymopt,nam),"OPTIONS original objsymopt.nam offset");
_Static_assert(sizeof(((struct objsymopt*)0)->nam)==sizeof(((struct teleport_options_objsymopt*)0)->nam),"OPTIONS original objsymopt.nam width");
_Static_assert(offsetof(struct objsymopt,descr)==offsetof(struct teleport_options_objsymopt,descr),"OPTIONS original objsymopt.descr offset");
_Static_assert(sizeof(((struct objsymopt*)0)->descr)==sizeof(((struct teleport_options_objsymopt*)0)->descr),"OPTIONS original objsymopt.descr width");
_Static_assert(sizeof(menu_cmd_t)==sizeof(struct teleport_options_menu_cmd_t),"OPTIONS original menu_cmd_t size");
_Static_assert(offsetof(menu_cmd_t,name)==offsetof(struct teleport_options_menu_cmd_t,name),"OPTIONS original menu_cmd_t.name offset");
_Static_assert(sizeof(((menu_cmd_t*)0)->name)==sizeof(((struct teleport_options_menu_cmd_t*)0)->name),"OPTIONS original menu_cmd_t.name width");
_Static_assert(offsetof(menu_cmd_t,cmd)==offsetof(struct teleport_options_menu_cmd_t,cmd),"OPTIONS original menu_cmd_t.cmd offset");
_Static_assert(sizeof(((menu_cmd_t*)0)->cmd)==sizeof(((struct teleport_options_menu_cmd_t*)0)->cmd),"OPTIONS original menu_cmd_t.cmd width");
_Static_assert(offsetof(menu_cmd_t,desc)==offsetof(struct teleport_options_menu_cmd_t,desc),"OPTIONS original menu_cmd_t.desc offset");
_Static_assert(sizeof(((menu_cmd_t*)0)->desc)==sizeof(((struct teleport_options_menu_cmd_t*)0)->desc),"OPTIONS original menu_cmd_t.desc width");
_Static_assert(sizeof(__typeof__(msgtype_names[0]))==sizeof(struct teleport_options_options_msgtype_name),"OPTIONS original options_msgtype_name size");
_Static_assert(offsetof(__typeof__(msgtype_names[0]),name)==offsetof(struct teleport_options_options_msgtype_name,name),"OPTIONS original options_msgtype_name.name offset");
_Static_assert(sizeof(((__typeof__(msgtype_names[0])*)0)->name)==sizeof(((struct teleport_options_options_msgtype_name*)0)->name),"OPTIONS original options_msgtype_name.name width");
_Static_assert(offsetof(__typeof__(msgtype_names[0]),msgtyp)==offsetof(struct teleport_options_options_msgtype_name,msgtyp),"OPTIONS original options_msgtype_name.msgtyp offset");
_Static_assert(sizeof(((__typeof__(msgtype_names[0])*)0)->msgtyp)==sizeof(((struct teleport_options_options_msgtype_name*)0)->msgtyp),"OPTIONS original options_msgtype_name.msgtyp width");
_Static_assert(offsetof(__typeof__(msgtype_names[0]),descr)==offsetof(struct teleport_options_options_msgtype_name,descr),"OPTIONS original options_msgtype_name.descr offset");
_Static_assert(sizeof(((__typeof__(msgtype_names[0])*)0)->descr)==sizeof(((struct teleport_options_options_msgtype_name*)0)->descr),"OPTIONS original options_msgtype_name.descr width");
#endif
