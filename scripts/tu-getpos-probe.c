/* Controlled external dependency fixture; original getpos.c only in reference. */
#include "hack.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdlib.h>
#undef free
extern void free(void*);
__typeof__(svd)svd;__typeof__(u)u;__typeof__(gg)gg;__typeof__(gw)gw;__typeof__(gi)gi;__typeof__(gc)gc;__typeof__(gs)gs;__typeof__(cg)cg;__typeof__(gn)gn;__typeof__(svl)svl;__typeof__(gv)gv;__typeof__(iflags)iflags;__typeof__(flags)flags;__typeof__(windowprocs)windowprocs;
winid WIN_MAP,WIN_MESSAGE;
const char what_is_a_location[]="a location";
const char quitchars[]=" \r\n\033";
const glyph_info nul_glyphinfo={0};
const struct symdef defsyms[MAXPCHARS+1]={[S_tree]={'T',"tree",0},[S_upstair]={'<',"stairs",0},[S_dnstair]={'>',"stairs",0},[S_arrow_trap]={'^',"trap",0},[S_engroom]={'`',"engraving",0},[S_engrcorr]={'#',"engraving",0}};
static char tracebuf[1048576],snapbuf[262144],outbuf[BUFSZ],goalbuf[BUFSZ];
static int opts[32],allocs,frees,windows,input[4096][4],input_count,input_index,queue_count,queue_index,callback_depth;
static struct _cmd_queue queued[32];static int actual[COLNO][ROWNO],shown[COLNO][ROWNO];static seenV visible[ROWNO][COLNO],*rows[ROWNO];static struct trap trapnode;static int traplive;static void*growth;
static char*retained;static coord resultcc;static coord*resultarr;static int resultcount;static coordxy sx,sy;static unsigned long bytes;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
void teleport_probe_free(void*p){if(p){frees++;logmsg("free;");}free(p);}
#define free teleport_probe_free
long*alloc(unsigned n){allocs++;bytes+=n;logmsg("alloc:%u;",n);void*p=malloc(n);if(!p)abort();return p;}
static void callback(void){if(opts[30]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}if(opts[31]&&!callback_depth){callback_depth++;logmsg("reentry:%d;",mapxy_valid(3,4));callback_depth--;}}
void panic(const char*f,...){abort();}void impossible(const char*f,...){abort();}
static void message(const char*tag,const char*f,va_list ap){logmsg("%s:",tag);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);logmsg(";");callback();}
void pline(const char*f,...){va_list ap;va_start(ap,f);message("msg",f,ap);va_end(ap);}void You(const char*f,...){va_list ap;va_start(ap,f);message("You",f,ap);va_end(ap);}void custompline(unsigned f,const char*s,...){logmsg("custom:%u;",f);va_list ap;va_start(ap,s);message("custom",s,ap);va_end(ap);}
void nh_snprintf(const char*fn,int line,char*out,size_t n,const char*f,...){logmsg("snprintf:%s:%d;",fn,line);va_list ap;va_start(ap,f);vsnprintf(out,n,f,ap);va_end(ap);}
boolean In_mines(d_level*l){(void)l;return FALSE;}boolean In_hell(d_level*l){(void)l;return FALSE;}boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
static winid window_new(int t){logmsg("window:%d;",t);return ++windows;}static void window_put(winid w,int a,const char*s){logmsg("put:%d:%d:%s;",w,a,s);callback();}static void window_display(winid w,boolean b){logmsg("display:%d:%d;",w,b);}static void window_destroy(winid w){logmsg("destroy:%d;",w);}static void window_clear(winid w){logmsg("clear:%d;",w);}static void window_curs(winid w,int x,int y){logmsg("cursor:%d:%d:%d;",w,x,y);}static void window_clip(int x,int y){logmsg("clip:%d:%d;",x,y);}static void window_start(winid w,unsigned long b){logmsg("menu:%d:%lu;",w,b);}static void window_end(winid w,const char*s){logmsg("end:%d:%s;",w,s);}
void add_menu(winid w,const glyph_info*g,const anything*a,char x,char y,int atr,int clr,const char*s,unsigned f){logmsg("add:%d:%d:%d:%d:%d:%d:%u:%s;",w,a->a_int,x,y,atr,clr,f,s);callback();}
int select_menu(winid w,int mode,menu_item**p){logmsg("select:%d:%d;",w,mode);if(opts[1]<1){*p=0;return opts[1];}*p=calloc(1,sizeof(menu_item));(*p)->item.a_int=opts[1];(*p)->count=opts[2];return 1;}
void flush_screen(int x){logmsg("flush:%d;",x);}void lock_mouse_buttons(boolean x){logmsg("mouse:%d;",x);}void docrt_flags(int f){logmsg("redraw:%d;",f);callback();}boolean handle_tip(int t){logmsg("tip:%d;",t);return opts[3];}
boolean redraw_cmd(char c){return c==18;}
int do_move_west(void){return 0;}int do_move_south(void){return 0;}int do_move_north(void){return 0;}int do_move_east(void){return 0;}int do_run_west(void){return 0;}int do_run_south(void){return 0;}int do_run_north(void){return 0;}int do_run_east(void){return 0;}int do_run(void){return 0;}int do_rush(void){return 0;}
char cmd_from_func(int(*f)(void)){if(f==do_move_west)return'h';if(f==do_move_south)return'j';if(f==do_move_north)return'k';if(f==do_move_east)return'l';if(f==do_run_west)return'H';if(f==do_run_south)return'J';if(f==do_run_north)return'K';if(f==do_run_east)return'L';if(f==do_run)return'G';if(f==do_rush)return'g';return'?';}
int movecmd(char c,int mode){int dx=0,dy=0,r=0;if(mode==MV_WALK){switch(c){case'h':dx=-1;break;case'l':dx=1;break;case'j':dy=1;break;case'k':dy=-1;break;case'y':dx=dy=-1;break;case'u':dx=1;dy=-1;break;case'b':dx=-1;dy=1;break;case'n':dx=dy=1;break;default:return 0;}r=1;}else if(mode==MV_RUSH){switch(c){case'H':dx=-1;break;case'L':dx=1;break;case'J':dy=1;break;case'K':dy=-1;break;default:return 0;}r=1;}if(r){u.dx=dx;u.dy=dy;}return r;}
char readchar_poskey(coordxy*x,coordxy*y,int*i){if(input_index>=input_count)abort();int*n=input[input_index++];*x=n[1];*y=n[2];*i=n[3];logmsg("key:%d:%d:%d:%d;",(char)n[0],*x,*y,*i);callback();return n[0];}
struct _cmd_queue*cmdq_pop(void){if(queue_index>=queue_count)return 0;struct _cmd_queue*p=malloc(sizeof *p);*p=queued[queue_index++];logmsg("pop:%d:%d:%d:%d:%d;",p->typ,p->key,p->dirx,p->diry,p->dirz);return p;}
void cmdq_clear(int k){logmsg("qclear:%d;",k);queue_index=queue_count;}void cmdq_add_key(int k,char c){logmsg("qadd:%d:%d;",k,c);}
int glyph_at(coordxy x,coordxy y){return shown[x][y];}int back_to_glyph(coordxy x,coordxy y){return actual[x][y];}
boolean invocation_pos(coordxy x,coordxy y){return x==5&&y==5;}struct trap*t_at(coordxy x,coordxy y){return traplive&&x==5&&y==5?&trapnode:0;}
boolean is_valid_travelpt(coordxy x,coordxy y){return (x+y)%3!=0;}
int xytodir(int x,int y){if(x>=-1&&x<=1&&y>=-1&&y<=1&&(x||y))return (x+1)*3+y+1;return-1;}const char*directionname(int n){static const char*const names[]={"northwest","west","southwest","north","here","south","northeast","east","southeast"};return names[n];}
char*visctrl(char c){static char ring[16][8];static unsigned slot;char*s=ring[slot++%16];if((unsigned char)c<32)snprintf(s,8,"^%c",c+64);else if(c==127)strcpy(s,"^?");else snprintf(s,8,"%c",c);return s;}
char*an(const char*s){static char ring[8][BUFSZ];static unsigned slot;char*p=ring[slot++%8];snprintf(p,BUFSZ,"an %s",s);return p;}char*eos(char*s){return s+strlen(s);}char*strsubst(char*s,const char*old,const char*new){char*p=strstr(s,old);if(p){size_t n=strlen(new);memmove(p+n,p+strlen(old),strlen(p+strlen(old))+1);memcpy(p,new,n);}return s;}
int do_screen_description(coord c,boolean b,int sym,char*out,const char**first,struct permonst**pm){logmsg("describe:%d:%d:%d:%d;",c.x,c.y,b,sym);strcpy(out,"description scratch");*first=(c.x+c.y)%2?"an object":"a location";if(pm)*pm=0;callback();return !opts[4];}
struct selectionvar*selection_new(void){struct selectionvar*s=calloc(1,sizeof *s);s->wid=COLNO;s->hei=ROWNO;s->map=calloc(COLNO*ROWNO,1);logmsg("selnew;");return s;}
void selection_free(struct selectionvar*s,boolean f){logmsg("selfree:%d;",f);if(s){free(s->map);if(f)free(s);}}
void selection_setpoint(coordxy x,coordxy y,struct selectionvar*s,int v){if(x>=0&&x<s->wid&&y>=0&&y<s->hei)s->map[y*s->wid+x]=v;}
coordxy selection_getpoint(coordxy x,coordxy y,struct selectionvar*s){return s&&x>=0&&x<s->wid&&y>=0&&y<s->hei?s->map[y*s->wid+x]:0;}
void selection_force_newsyms(struct selectionvar*s){int n=0;for(int i=0;i<s->wid*s->hei;i++)n+=!!s->map[i];logmsg("selnewsym:%d;",n);callback();}
static int(*floodcheck)(coordxy,coordxy);void set_selection_floodfillchk(int(*f)(coordxy,coordxy)){floodcheck=f;logmsg("floodcb;");}
void selection_floodfill(struct selectionvar*s,coordxy x,coordxy y,boolean d){logmsg("flood:%d:%d:%d;",x,y,d);int change=1;selection_setpoint(x,y,s,1);while(change){change=0;for(int xx=1;xx<COLNO;xx++)for(int yy=0;yy<ROWNO;yy++)if(!selection_getpoint(xx,yy,s)&&floodcheck(xx,yy)&&(selection_getpoint(xx-1,yy,s)||selection_getpoint(xx+1,yy,s)||selection_getpoint(xx,yy-1,s)||selection_getpoint(xx,yy+1,s))){selection_setpoint(xx,yy,s,1);change=1;}}callback();}
static void highlight(boolean b){logmsg("hilite:%d;",b);callback();}static boolean valid_a(coordxy x,coordxy y){return(x+y)%7==0;}static boolean valid_b(coordxy x,coordxy y){return x>=3&&x<=7&&y>=3&&y<=7;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/getpos.c"
#else
extern void  teleport_getpos_test_getpos_toggle_hilite_state(void);
#define getpos_toggle_hilite_state teleport_getpos_test_getpos_toggle_hilite_state
extern void  teleport_getpos_test_getpos_getvalids_selection(struct selectionvar *, boolean (*)(coordxy, coordxy));
#define getpos_getvalids_selection teleport_getpos_test_getpos_getvalids_selection
extern void  teleport_getpos_test_getpos_help_keyxhelp(winid, const char *, const char *, int);
#define getpos_help_keyxhelp teleport_getpos_test_getpos_help_keyxhelp
extern void  teleport_getpos_test_getpos_help(boolean, const char *);
#define getpos_help teleport_getpos_test_getpos_help
extern int  teleport_getpos_cmp_coord_distu(const void *, const void *);
#define cmp_coord_distu teleport_getpos_cmp_coord_distu
extern int  teleport_getpos_test_gloc_filter_classify_glyph(int);
#define gloc_filter_classify_glyph teleport_getpos_test_gloc_filter_classify_glyph
extern int  teleport_getpos_gloc_filter_floodfill_matcharea(coordxy, coordxy);
#define gloc_filter_floodfill_matcharea teleport_getpos_gloc_filter_floodfill_matcharea
extern void  teleport_getpos_test_gloc_filter_floodfill(coordxy, coordxy);
#define gloc_filter_floodfill teleport_getpos_test_gloc_filter_floodfill
extern void  teleport_getpos_test_gloc_filter_init(void);
#define gloc_filter_init teleport_getpos_test_gloc_filter_init
extern void  teleport_getpos_test_gloc_filter_done(void);
#define gloc_filter_done teleport_getpos_test_gloc_filter_done
extern boolean  teleport_getpos_test_known_vibrating_square_at(coordxy, coordxy);
#define known_vibrating_square_at teleport_getpos_test_known_vibrating_square_at
extern void  teleport_getpos_test_gather_locs(coord **, int *, int);
#define gather_locs teleport_getpos_test_gather_locs
extern void  teleport_getpos_test_truncate_to_map(coordxy *, coordxy *, schar, schar);
#define truncate_to_map teleport_getpos_test_truncate_to_map
extern void  teleport_getpos_test_getpos_refresh(void);
#define getpos_refresh teleport_getpos_test_getpos_refresh
#endif
#include "tu-getpos-layout.h"
void probe_reset(void){int x,y;if(resultarr)free(resultarr);resultarr=0;if(gg.gloc_filter_map)selection_free(gg.gloc_filter_map,TRUE);if(growth)free(growth);growth=0;memset(&u,0,sizeof u);memset(&gg,0,sizeof gg);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(&gs,0,sizeof gs);memset(&gc,0,sizeof gc);memset(&gi,0,sizeof gi);memset(&svl,0,sizeof svl);memset(opts,0,sizeof opts);memset(queued,0,sizeof queued);memset(visible,0,sizeof visible);getpos_sethilite(0,0);WIN_MAP=1;WIN_MESSAGE=2;windowprocs.win_create_nhwindow=window_new;windowprocs.win_putstr=window_put;windowprocs.win_display_nhwindow=window_display;windowprocs.win_destroy_nhwindow=window_destroy;windowprocs.win_clear_nhwindow=window_clear;windowprocs.win_curs=window_curs;windowprocs.win_cliparound=window_clip;windowprocs.win_start_menu=window_start;windowprocs.win_end_menu=window_end;u.ux=10;u.uy=10;u.uz.dnum=1;u.uz.dlevel=2;u.dx=1;u.dy=-1;u.dz=1;iflags.getpos_coords=GPCOORDS_NONE;flags.help=1;svl.level.flags.hero_memory=1;for(y=0;y<ROWNO;y++)rows[y]=visible[y];gv.viz_array=rows;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){shown[x][y]=actual[x][y]=cmap_to_glyph(S_room);levl[x][y].typ=ROOM;levl[x][y].glyph=shown[x][y];levl[x][y].seenv=1;visible[y][x]=IN_SIGHT;}for(x=0;x<SYM_MAX;x++)gs.showsyms[x]=x%90+32;gc.Cmd.spkeys[NHKF_ESC]=27;gc.Cmd.spkeys[NHKF_GETPOS_PICK]='.';gc.Cmd.spkeys[NHKF_GETPOS_PICK_Q]=',';gc.Cmd.spkeys[NHKF_GETPOS_PICK_O]=';';gc.Cmd.spkeys[NHKF_GETPOS_PICK_V]=':';gc.Cmd.spkeys[NHKF_GETPOS_HELP]='?';gc.Cmd.spkeys[NHKF_GETPOS_SELF]='@';gc.Cmd.spkeys[NHKF_GETPOS_SHOWVALID]='v';gc.Cmd.spkeys[NHKF_GETPOS_AUTODESC]='a';gc.Cmd.spkeys[NHKF_GETPOS_LIMITVIEW]='f';gc.Cmd.spkeys[NHKF_GETPOS_MENU]='!';gc.Cmd.spkeys[NHKF_GETPOS_MOVESKIP]='s';static const int keys[]={NHKF_GETPOS_MON_NEXT,NHKF_GETPOS_MON_PREV,NHKF_GETPOS_OBJ_NEXT,NHKF_GETPOS_OBJ_PREV,NHKF_GETPOS_DOOR_NEXT,NHKF_GETPOS_DOOR_PREV,NHKF_GETPOS_UNEX_NEXT,NHKF_GETPOS_UNEX_PREV,NHKF_GETPOS_INTERESTING_NEXT,NHKF_GETPOS_INTERESTING_PREV,NHKF_GETPOS_VALID_NEXT,NHKF_GETPOS_VALID_PREV};for(x=0;x<12;x++)gc.Cmd.spkeys[keys[x]]="mMoOdDxXiIzZ"[x];resultcc.x=10;resultcc.y=10;resultcount=0;retained=0;sx=sy=0;input_count=input_index=queue_count=queue_index=0;allocs=frees=windows=callback_depth=bytes=0;traplive=0;opts[1]=2;outbuf[0]=0;strcpy(goalbuf,"desired location");tracebuf[0]=0;}
void probe_option(int k,int v){switch(k){case 100:iflags.bgcolors=v;break;case 101:iflags.getloc_filter=v;break;case 102:iflags.getloc_moveskip=v;break;case 103:iflags.getloc_travelmode=v;break;case 104:iflags.getloc_usemenu=v;break;case 105:iflags.getpos_coords=v;break;case 106:iflags.autodescribe=v;break;case 107:iflags.remember_getpos=v;break;case 108:iflags.terrainmode=v;break;case 109:iflags.cmdassist=v;break;case 110:flags.verbose=v;break;case 111:flags.help=v;break;case 112:gi.in_doagain=v;break;case 113:u.ux=v;break;case 114:u.uy=v;break;case 115:u.dx=v;break;case 116:u.dy=v;break;case 117:u.dz=v;break;case 118:resultcc.x=v;break;case 119:resultcc.y=v;break;case 120:traplive=v;trapnode.ttyp=VIBRATING_SQUARE;trapnode.tseen=1;break;case 121:gw.wsettings.map_frame_color=(unsigned)v;break;case 122:svl.level.flags.hero_memory=v;break;case 123:for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)shown[x][y]=v;break;default:opts[k]=v;break;}}
void probe_cell(int x,int y,int k,int v){switch(k){case 0:shown[x][y]=v;break;case 1:actual[x][y]=v;break;case 2:levl[x][y].glyph=v;break;case 3:levl[x][y].seenv=v;break;case 4:levl[x][y].typ=v;break;case 5:visible[y][x]=v;break;}}
void probe_input(int c,int x,int y,int b){if(input_count>=4096)abort();int*p=input[input_count++];p[0]=c;p[1]=x;p[2]=y;p[3]=b;}
void probe_queue(int typ,int key,int x,int y,int z){struct _cmd_queue*q=&queued[queue_count++];q->typ=typ;q->key=key;q->dirx=x;q->diry=y;q->dirz=z;}
char*probe_goal(void){return goalbuf;}
long probe_action(int op,int a,int b,int c){struct selectionvar*s;coord p={a,b},q={b,c};switch(op){case 0:getpos_sethilite(a?highlight:0,b==1?valid_a:b==2?valid_b:0);return 0;case 1:getpos_toggle_hilite_state();return 0;case 2:return mapxy_valid(a,b);case 3:s=selection_new();getpos_getvalids_selection(s,a==1?valid_a:a==2?valid_b:0);selection_force_newsyms(s);selection_free(s,TRUE);return 0;case 4:getpos_help_keyxhelp(4,"m","M",a);return 0;case 5:getpos_help(a,b==1?what_is_a_location:b==2?"a monster":goalbuf);return 0;case 6:return cmp_coord_distu(&p,&q);case 7:return gloc_filter_classify_glyph(a);case 8:return gloc_filter_floodfill_matcharea(a,b);case 9:if(!gg.gloc_filter_map)gg.gloc_filter_map=selection_new();gloc_filter_floodfill(a,b);return 0;case 10:gloc_filter_init();return 0;case 11:gloc_filter_done();return 0;case 12:return known_vibrating_square_at(a,b);case 13:return gather_locs_interesting(a,b,c);case 14:if(resultarr)free(resultarr);gather_locs(&resultarr,&resultcount,a);return resultcount;case 15:retained=dxdy_to_dist_descr(a,b,c);strcpy(outbuf,retained);return 0;case 16:coord_desc(a,b,outbuf,c);return 0;case 17:auto_describe(a,b);return 0;case 18:return getpos_menu(&resultcc,a);case 19:sx=resultcc.x;sy=resultcc.y;truncate_to_map(&sx,&sy,a,b);resultcc.x=sx;resultcc.y=sy;return 0;case 20:getpos_refresh();return 0;case 21:return getpos(&resultcc,a,b==1?what_is_a_location:b==2?0:goalbuf);default:return -99;}}
const char*probe_trace(void){return tracebuf;}const char*probe_result(void){return outbuf;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_snapshot(void){char*p=snapbuf;int x,y;p+=sprintf(p,"u:%d:%d:%d:%d:%d;pos:%d:%d:%d:%d;flags:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;frame:%u;memory:%d:%d:%lu;input:%d:%d;result:%s;arr:%d;",u.ux,u.uy,u.dx,u.dy,u.dz,resultcc.x,resultcc.y,gg.getposx,gg.getposy,iflags.bgcolors,iflags.getloc_filter,iflags.getloc_moveskip,iflags.getloc_travelmode,iflags.getloc_usemenu,iflags.getpos_coords,iflags.autodescribe,iflags.remember_getpos,iflags.terrainmode,iflags.cmdassist,gw.wsettings.map_frame_color,allocs,frees,bytes,input_index,queue_index,outbuf,resultcount);p+=sprintf(p,"retained:%s;",retained?retained:"");for(x=0;x<resultcount;x++)p+=sprintf(p,"c:%d:%d;",resultarr[x].x,resultarr[x].y);p+=sprintf(p,"filter:%d:%d;",!!gg.gloc_filter_map,gg.gloc_filter_floodfill_match_glyph);for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)p+=sprintf(p,"g:%d:%d:%d:%u:%d:%u:%d;",shown[x][y],actual[x][y],levl[x][y].glyph,levl[x][y].seenv,levl[x][y].typ,visible[y][x],selection_getpoint(x,y,gg.gloc_filter_map));return snapbuf;}

int probe_cmap(int sym){return cmap_to_glyph(sym);}

int probe_private_state(int k){
#ifdef TELEPORT_REFERENCE_TU
switch(k){case 0:return getpos_hilite_state;case 1:return defaultHiliteState;case 2:return!!getpos_hilitefunc;case 3:return!!getpos_getvalid;default:return-1;}
#else
return -99;
#endif
}
extern void __real_nh_deterministic_qsort(void*,size_t,size_t,int(*)(const void*,const void*));
static int(*compare_target)(const void*,const void*);
static int compare_log(const void*a,const void*b){const coord*x=a,*y=b;int r=compare_target(a,b);logmsg("cmp:%d:%d:%d:%d:%d;",x->x,x->y,y->x,y->y,r);return r;}
void __wrap_nh_deterministic_qsort(void*p,size_t n,size_t z,int(*f)(const void*,const void*)){compare_target=f;logmsg("sort:%zu:%zu;",n,z);__real_nh_deterministic_qsort(p,n,z,compare_log);}
