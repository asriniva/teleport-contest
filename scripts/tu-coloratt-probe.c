#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef free
extern void free(void*);
__typeof__(cg) cg={.zeroany={0}};
__typeof__(gm) gm;
__typeof__(gc) gc;
__typeof__(gs) gs;
__typeof__(iflags) iflags;
__typeof__(windowprocs) windowprocs;
const glyph_info nul_glyphinfo={0};
const char hexdd[]="00112233445566778899aAbBcCdDeEfF";
static color_attr ca;
static glyph_map glyph;
static struct nethack_color custom;
static int opts[40],picks_values[32],picks_length,pick_call,free_count,picks_free_count;
static menu_item *picks_live[32];
static int live_count;
static char tracebuf[1048576],statebuf[65536],output[8192];
static uint32 closest=0xaabbccddU;
static uint16 closest_index=0xabcd;
static const char *last_string;
static void *growth;
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("nested-count:%d;",count_menucolors());}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}}
void config_error_add(const char *f,...){char b[BUFSZ*4];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append("config:%s;",b);callback(4);}
void impossible(const char *f,...){append("impossible;");}
void teleport_probe_free(void *p){int i;for(i=0;i<live_count;i++)if(p==picks_live[i]){picks_live[i]=NULL;picks_free_count++;append("free-picks;");break;}free_count++;callback(3);free(p);}
static winid create_window(int typ){append("create:%d;",typ);return 19;}
static void start_window(winid w,unsigned long b){append("start:%d:%lu;",w,b);}
static void end_window(winid w,const char *s){append("end:%d:%s;",w,s);}
static void destroy_window(winid w){append("destroy:%d;",w);}
void add_menu(winid w,const glyph_info *g,const anything *id,char let,char group,int attr,int color,const char *s,unsigned flags){int i;append("menu:%d:%d:%d:%d:%d:%d:%d:%u:%s:",w,g==&nul_glyphinfo,id->a_int,let,group,attr,color,flags,s);for(i=0;i<sizeof *id;i++)append("%02x",((const unsigned char*)id)[i]);append(";");callback(1);}
int select_menu(winid w,int how,menu_item **out){int i,call=pick_call++,count=opts[call?2:1];append("select:%d:%d:%d;",w,how,count);*out=NULL;if(count>0){menu_item *p=malloc(count*sizeof *p);if(!p||live_count>=32)abort();memset(p,0,count*sizeof *p);for(i=0;i<count;i++){p[i].item.a_int=picks_values[(call?16:0)+i];p[i].count=((long)1<<53)+i;}picks_live[live_count++]=p;*out=p;}callback(2);return count;}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/coloratt.c"
#undef free
#else
struct color_names{const char *name;int color;};
struct attr_names{const char *name;int attr;};
struct color_256_row{int index;uint32 value;};
extern void *teleport_coloratt_storage(int);
#define colornames ((const struct color_names*)teleport_coloratt_storage(1))
#define attrnames ((const struct attr_names*)teleport_coloratt_storage(2))
#define color_256_definitions ((const struct color_256_row*)teleport_coloratt_storage(3))
#endif
#include "tu-coloratt-layout.h"
void probe_reset(void){int i;if(opts[33])basic_menu_colors(FALSE);free_menu_coloring();for(i=0;i<live_count;i++)if(picks_live[i])free(picks_live[i]);if(growth)free(growth);growth=NULL;memset(&gm,0,sizeof gm);memset(&gc,0,sizeof gc);memset(&gs,0,sizeof gs);memset(&iflags,0,sizeof iflags);memset(&ca,0,sizeof ca);memset(&glyph,0,sizeof glyph);memset(&custom,0,sizeof custom);memset(opts,0,sizeof opts);opts[1]=opts[2]=-1;memset(picks_values,0,sizeof picks_values);picks_length=pick_call=free_count=picks_free_count=live_count=0;closest=0xaabbccddU;closest_index=0xabcd;last_string=NULL;memset(output,0xa5,sizeof output);output[0]=0;windowprocs.win_create_nhwindow=create_window;windowprocs.win_start_menu=start_window;windowprocs.win_end_menu=end_window;windowprocs.win_destroy_nhwindow=destroy_window;tracebuf[0]=0;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;if(k==3)ca.color=v;if(k==4)ca.attr=v;if(k==5)iflags.use_menu_color=v;if(k==6)custom.colortyp=v;if(k==7)custom.tableindex=v;if(k==8)custom.r=v;if(k==9)custom.g=v;if(k==10)custom.b=v;}
int *probe_picks_pointer(void){return picks_values;}
void probe_picks_length(int n){picks_length=n;}
long probe_action(int op,int a,int b,uint32 x,uint32 y,const char *s){int r=0;switch(op){case 0:return colortable_to_int32(a<0?&custom:&colortable[a]);case 1:last_string=color_attr_to_str(&ca);strcpy(output,last_string);break;case 2:r=color_attr_parse_str(&ca,(char*)s);break;case 3:r=query_color_attr(&ca,s);break;case 4:last_string=attr2attrname(a);if(last_string)strcpy(output,last_string);else strcpy(output,"<NULL>");break;case 5:last_string=clr2colorname(a);if(last_string)strcpy(output,last_string);else strcpy(output,"<NULL>");break;case 6:r=match_str2clr((char*)s,a);break;case 7:r=match_str2attr(s,a);break;case 8:r=query_attr(s,a);break;case 9:r=query_color(s,a);break;case 10:basic_menu_colors(a);opts[33]=a?1:0;break;case 11:r=add_menu_coloring_parsed(s,a,b);break;case 12:r=add_menu_coloring((char*)s);break;case 13:free_menu_coloring();break;case 14:free_one_menu_coloring(a);break;case 15:r=count_menucolors();break;case 16:return check_enhanced_colors((char*)s);case 17:last_string=wc_color_name((int32)x);strcpy(output,last_string);break;case 18:r=onlyhexdigits(s);break;case 19:return rgbstr_to_int32(s);case 20:r=set_map_customcolor(a?&glyph:NULL,x);break;case 21:return color_distance(x,y);case 22:r=closest_color(x,a?&closest:NULL,b?&closest_index:NULL);break;case 23:return get_nhcolor_from_256_index(a);}return r;}
char *probe_output(void){return output;}
size_t probe_output_size(void){return sizeof output;}
void *probe_pointer(int id){switch(id){case 0:return (void*)colortable;case 1:return (void*)colornames;case 2:return (void*)attrnames;case 3:return (void*)color_256_definitions;case 4:return &ca;case 5:return &glyph;case 6:return &custom;case 7:return (void*)last_string;}return NULL;}
int probe_table_count(int table){switch(table){
#ifdef TELEPORT_REFERENCE_TU
case 0:return SIZE(colortable);case 1:return SIZE(colornames);case 2:return SIZE(attrnames);case 3:return SIZE(color_256_definitions);
#else
case 0:return 155;case 1:return 27;case 2:return 11;case 3:return 240;
#endif
}return 0;}
const char *probe_table_name(int table,int row){if(table==0)return colortable[row].name;if(table==1)return colornames[row].name;if(table==2)return attrnames[row].name;return NULL;}
unsigned long probe_table_value(int table,int row,int field){if(table==0){const struct nethack_color *c=&colortable[row];switch(field){case 0:return c->colortyp;case 1:return c->tableindex;case 2:return c->rgbindex;case 3:return c->r;case 4:return c->g;case 5:return c->b;}}if(table==1)return colornames[row].color;if(table==2)return attrnames[row].attr;if(table==3)return field?color_256_definitions[row].value:color_256_definitions[row].index;return 0;}
int probe_regex_match(int index,const char *s){struct menucoloring *m=gm.menu_colorings;while(m&&index--)m=m->next;return m?regex_match(s,m->match):-1;}
int probe_free_count(void){return free_count;}
int probe_picks_free_count(void){return picks_free_count;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
static char *list_snapshot(char *p,struct menucoloring *m){for(;m;m=m->next)p+=sprintf(p,"[%s:%d:%d:%d]",m->origstr,m->color,m->attr,m->match!=NULL);return p;}
const char *probe_snapshot(void){char *p=statebuf;int i;p+=sprintf(p,"state:%d:%d:%u:%u:%d:%d:%d:%d:%d;menu:",ca.color,ca.attr,closest,closest_index,iflags.use_menu_color,gs.save_menucolors,free_count,picks_free_count,gs.save_colorings?gs.save_colorings==gm.menu_colorings?1:gs.save_colorings==gc.color_colorings?2:3:0);p=list_snapshot(p,gm.menu_colorings);p+=sprintf(p,";alternate:");p=list_snapshot(p,gc.color_colorings);p+=sprintf(p,";glyph:");for(i=0;i<sizeof glyph;i++)p+=sprintf(p,"%02x",((unsigned char*)&glyph)[i]);return statebuf;}
