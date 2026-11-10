#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef free
extern void free(void*);
__typeof__(svb) svb;
__typeof__(svd) svd;
__typeof__(go) go;
__typeof__(iflags) iflags;
__typeof__(flags) flags;
__typeof__(program_state) program_state;
struct you u;
__typeof__(cg) cg={.zeroobj={0},.zeroany={0}};
__typeof__(gu) gu;
__typeof__(svc) svc;
__typeof__(windowprocs) windowprocs;
const glyph_info nul_glyphinfo={0};
winid WIN_MESSAGE=7;
static struct obj obj;
static NHFILE nhfile;
static int opts[40],rolls[8192],nroll,rollidx,free_counts[5],pick_values[16],pick_count,pick_call,low,high,sort_active;
static unsigned seed;
static char tracebuf[4194304],statebuf[524288],caller[128],output[BUFSZ],typebuf[BUFSZ*4],type_override[BUFSZ*3],compare_a[BUFSZ*2],compare_b[BUFSZ*2];
static char *lines[NUM_OBJECTS],*compare_cells[2];
static menu_item *active_picks[32];
static int n_active;
static unsigned char io[262144];
static int io_len,io_pos;
static void *growth;
static const char *last_string;
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*3];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(impossible) MSG(raw_printf)
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *f,int line,const char *fn){const char *b=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(rollidx<nroll)v=rolls[rollidx]%(unsigned)n;else{seed=seed*1664525U+1013904223U;v=(seed>>8)%(unsigned)n;}rollidx++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
static void callback(int stage){if(opts[30]==stage){char b[BUFSZ];opts[30]=0;get_sortdisco(b,FALSE);append("nested-sort:%s;",b);}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}}
void teleport_probe_free(void *p){int i,kind=0;if(!p)return;for(i=0;i<NUM_OBJECTS;i++)if(objects[i].oc_uname==p){kind=1;break;}for(i=0;i<n_active;i++)if(active_picks[i]==p){kind=2;active_picks[i]=NULL;break;}if(sort_active)kind=4;else if(!kind)kind=3;free_counts[0]++;free_counts[kind]++;append("free:%d;",kind);callback(7);free(p);}
static int (*sort_compare)(const void*,const void*);
/* Test-only copied callback observations survive the source's subsequent free. */
static struct {size_t first,second;int result;} compare_records[8192];
static char compare_text[1048576];
static int compare_count;
static size_t compare_text_used;
extern void __real_nh_deterministic_qsort(void*,size_t,size_t,int(*)(const void*,const void*));
static int compare_proxy(const void *a,const void *b){int r,index;size_t first,second,n;const char *left,*right;callback(6);
    left=*(const char*const*)a;right=*(const char*const*)b;
    if(compare_count>=SIZE(compare_records))abort();index=compare_count++;
    first=compare_text_used;n=strlen(left)+1;if(n>sizeof compare_text-compare_text_used)abort();memcpy(compare_text+compare_text_used,left,n);compare_text_used+=n;
    second=compare_text_used;n=strlen(right)+1;if(n>sizeof compare_text-compare_text_used)abort();memcpy(compare_text+compare_text_used,right,n);compare_text_used+=n;
    r=sort_compare(a,b);compare_records[index].first=first;compare_records[index].second=second;compare_records[index].result=r;
    append("compare:%d;",r);return r;
}
void __wrap_nh_deterministic_qsort(void *base,size_t n,size_t size,int(*cmp)(const void*,const void*)){append("qsort:%zu:%zu;",n,size);sort_compare=cmp;sort_active=1;__real_nh_deterministic_qsort(base,n,size,compare_proxy);sort_active=0;}
xint16 ledger_no(d_level *d){append("ledger:%d:%d;",d->dnum,d->dlevel);return opts[1];}
xint16 maxledgerno(void){append("maxledger; ");return opts[2];}
static void wait_window(void){append("wait;");}
void exercise(int a,boolean b){append("exercise:%d:%d;",a,b);}
void gem_learned(int type){append("gem:%d;",type);callback(1);}
void update_inventory(void){append("inventory;");callback(2);}
const char *Japanese_item_name(int type,const char *actual){append("japanese:%d:%s;",type,actual?actual:"NULL");return opts[3]==type?"fixture Japanese name":NULL;}
char *obj_typename(int type){append("typename:%d;",type);if(type_override[0])strcpy(typebuf,type_override);else snprintf(typebuf,sizeof typebuf,"%s%s%s",OBJ_NAME(objects[type])?OBJ_NAME(objects[type]):"object",objects[type].oc_uname?" called ":"",objects[type].oc_uname?objects[type].oc_uname:"");callback(3);return typebuf;}
void append_price_quote(char *b,char **end,int type){append("price:%d:%ld;",type,(long)(*end-b));if(opts[4]&&strlen(b)+8<BUFSZ){strcat(*end," {gold}");*end+=7;}callback(4);}
void loot_classify(Loot *cookie,struct obj *o){int i;append("loot-object:");for(i=0;i<sizeof *o;i++)append("%02x",((unsigned char*)o)[i]);append(";loot-cookie:");for(i=0;i<sizeof *cookie;i++)append("%02x",((unsigned char*)cookie)[i]);append(";");cookie->orderclass=objects[o->otyp].oc_class+opts[5];cookie->subclass=opts[6];cookie->disco=opts[8];callback(5);}
char *let_to_name(char c,boolean unpaid,boolean blind){static char b[8][BUFSZ];static unsigned n;char *s=b[n++%8];append("class-name:%d:%d:%d;",c,unpaid,blind);snprintf(s,BUFSZ,"Class %d",c);return s;}
boolean objtyp_is_callable(int type){append("callable:%d;",type);return opts[9];}
void docall(struct obj *o){int i;append("docall-object:");for(i=0;i<sizeof *o;i++)append("%02x",((unsigned char*)o)[i]);append(";");callback(11);}
int disp_artifact_discoveries(winid w){append("artifacts:%d:%d;",w,opts[10]);return opts[10];}
void dump_artifact_info(winid w){append("artifact-dump:%d;",w);}
static winid create_window(int typ){append("create:%d;",typ);return 19;}
static void start_window(winid w,unsigned long f){append("start:%d:%lu;",w,f);}
static void end_window(winid w,const char *s){append("end:%d:%s;",w,s);}
static void destroy_window(winid w){append("destroy:%d;",w);}
static void display_window(winid w,boolean block){append("display:%d:%d;",w,block);}
static void clear_window(winid w){append("clear:%d;",w);}
static void put_window(winid w,int a,const char *s){append("put:%d:%d:%s;",w,a,s);callback(8);}
void add_menu(winid w,const glyph_info *g,const anything *id,char let,char group,int attr,int color,const char *s,unsigned f){int i;append("menu:%d:%d:%d:%d:%d:%d:%d:%u:%s:",w,g==&nul_glyphinfo,id->a_int,let,group,attr,color,f,s);for(i=0;i<sizeof *id;i++)append("%02x",((const unsigned char*)id)[i]);append(";");callback(9);}
void add_menu_heading(winid w,const char *s){append("heading:%d:%s;",w,s);}
void add_menu_str(winid w,const char *s){append("menu-string:%d:%s;",w,s);}
int select_menu(winid w,int how,menu_item **out){int i,n=opts[pick_call++?13:12];append("select:%d:%d:%d;",w,how,n);*out=NULL;if(n>0){menu_item *p=calloc(n,sizeof *p);if(n_active>=32)abort();for(i=0;i<n;i++){p[i].item.a_int=pick_values[i];p[i].count=(1L<<53)+i;}active_picks[n_active++]=p;*out=p;}callback(10);return n;}
char yn_function(const char *p,const char *choices,char def,boolean hist){append("yn:%s:%s:%d:%d;",p,choices,def,hist);return strstr(p,"Dump information")?opts[15]:opts[14];}
const char ynchars[]="yn";
static void write_bytes(void *p,size_t n,const char *s){if(io_pos+n>sizeof io)abort();memcpy(io+io_pos,p,n);io_pos+=n;if(io_pos>io_len)io_len=io_pos;append("out:%s:%zu;",s,n);callback(12);}
static void read_bytes(void *p,size_t n,const char *s){if(io_pos+n>io_len)abort();memcpy(p,io+io_pos,n);io_pos+=n;append("in:%s:%zu;",s,n);callback(13);}
#define SERIAL(name,type) void sfo_##name(NHFILE*f,type*p,const char*s){write_bytes(p,sizeof *p,s);} void sfi_##name(NHFILE*f,type*p,const char*s){read_bytes(p,sizeof *p,s);}
SERIAL(int,int) SERIAL(short,short) SERIAL(unsigned,unsigned) SERIAL(objclass,struct objclass)
void sfo_char(NHFILE*f,char*p,const char*s,int n){write_bytes(p,n,s);}
void sfi_char(NHFILE*f,char*p,const char*s,int n){read_bytes(p,n,s);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/o_init.c"
#undef free
#else
extern void teleport_o_init_test_gems(d_level*),teleport_o_init_test_colors(void),teleport_o_init_test_shuffle(int,int,boolean),teleport_o_init_test_all(void);
extern int teleport_o_init_test_cmp(const void*,const void*);
extern char *teleport_o_init_test_sortloot(int,char*),*teleport_o_init_test_typename(int),*teleport_o_init_test_class(char,char*);
extern void teleport_o_init_test_append(char*,int),teleport_o_init_test_uniq(int,char*),teleport_o_init_test_output(winid,char**,int,boolean);
#define setgemprobs teleport_o_init_test_gems
#define randomize_gem_colors teleport_o_init_test_colors
#define shuffle teleport_o_init_test_shuffle
#define shuffle_all teleport_o_init_test_all
#define discovered_cmp teleport_o_init_test_cmp
#define sortloot_descr teleport_o_init_test_sortloot
#define disco_typename teleport_o_init_test_typename
#define disco_append_typename teleport_o_init_test_append
#define disco_fmt_uniq teleport_o_init_test_uniq
#define disco_output_sorted teleport_o_init_test_output
#define oclass_to_name teleport_o_init_test_class
#endif
#include "tu-o_init-layout.h"
void probe_reset(unsigned s){int i;for(i=0;i<NUM_OBJECTS;i++)if(objects[i].oc_uname)free(objects[i].oc_uname);for(i=0;i<n_active;i++)if(active_picks[i])free(active_picks[i]);for(i=0;i<NUM_OBJECTS;i++)if(lines[i])free(lines[i]);if(growth)free(growth);growth=NULL;WIN_MESSAGE=7;memset(&svb,0,sizeof svb);memset(&svd,0,sizeof svd);memset(&go,0,sizeof go);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(&program_state,0,sizeof program_state);memset(&u,0,sizeof u);memset(&gu,0,sizeof gu);memset(&svc,0,sizeof svc);memset(&obj,0,sizeof obj);memset(&nhfile,0,sizeof nhfile);memset(opts,0,sizeof opts);memset(lines,0,sizeof lines);memset(free_counts,0,sizeof free_counts);objects_globals_init();monst_globals_init();opts[0]=1;opts[1]=0;opts[2]=50;opts[3]=-1;opts[9]=1;opts[12]=opts[13]=-1;opts[14]=opts[15]='n';u.uz.dnum=1;u.uz.dlevel=2;flags.discosort='o';for(i=1;i<MAXOCLASSES;i++)flags.inv_order[i-1]=i;flags.inv_order[MAXOCLASSES-1]=0;nhfile.mode=WRITING;windowprocs.win_create_nhwindow=create_window;windowprocs.win_start_menu=start_window;windowprocs.win_end_menu=end_window;windowprocs.win_destroy_nhwindow=destroy_window;windowprocs.win_display_nhwindow=display_window;windowprocs.win_clear_nhwindow=clear_window;windowprocs.win_putstr=put_window;windowprocs.win_wait_synch=wait_window;seed=s;nroll=rollidx=n_active=pick_call=pick_count=io_pos=io_len=sort_active=0;compare_count=0;compare_text_used=0;last_string=NULL;low=high=-99;output[0]=type_override[0]=compare_a[0]=compare_b[0]=tracebuf[0]=statebuf[0]=caller[0]=0;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;}
int *probe_rng_pointer(void){return rolls;}
void probe_rng_length(int n){nroll=n;rollidx=0;}
int probe_rng_count(void){return rollidx;}
unsigned probe_rng_state(void){return seed;}
void probe_record(int row,int field,long v){struct objclass *o=&objects[row];switch(field){case 0:o->oc_name_idx=v;break;case 1:o->oc_descr_idx=v;break;case 2:o->oc_prob=v;break;case 3:o->oc_name_known=v;break;case 4:o->oc_encountered=v;break;case 5:o->oc_magic=v;break;case 6:o->oc_unique=v;break;case 7:o->oc_tough=v;break;case 8:o->oc_material=v;break;case 9:o->oc_color=v;break;case 10:o->oc_dir=v;break;case 11:o->oc_class=v;break;case 12:o->oc_uses_known=v;break;case 13:o->oc_cost=v;break;case 14:o->oc_buy_minseen=v;break;}}
long probe_row_value(int row,int field){struct objclass *o=&objects[row];switch(field){case 0:return o->oc_name_idx;case 1:return o->oc_descr_idx;case 2:return o->oc_prob;case 3:return o->oc_name_known;case 4:return o->oc_encountered;case 5:return o->oc_magic;case 6:return o->oc_unique;case 7:return o->oc_tough;case 8:return o->oc_material;case 9:return o->oc_color;case 10:return o->oc_dir;case 11:return o->oc_class;case 12:return o->oc_uses_known;case 13:return o->oc_cost;case 14:return o->oc_buy_minseen;}return -999;}
void probe_object(int k,long v){switch(k){case 0:obj.otyp=v;obj.oclass=objects[v].oc_class;break;case 1:obj.dknown=v;break;case 2:obj.known=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:gu.urole.mnum=v;break;case 1:flags.discosort=v;break;case 2:flags.menu_style=v;break;case 3:iflags.menu_requested=v;break;case 4:iflags.menu_headings.attr=v;break;case 5:iflags.sanity_check=v;break;case 6:program_state.in_moveloop=v;break;case 7:program_state.gameover=v;break;case 8:flags.debug=v;break;case 9:svc.context.current_fruit=v;break;case 10:svd.disco[v]=0;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_set_uname(int row,const char *s){if(objects[row].oc_uname)free(objects[row].oc_uname);objects[row].oc_uname=s?dupstr(s):NULL;}
void probe_input(int kind,const char *s){switch(kind){case 0:strcpy(type_override,s);break;case 1:strcpy(output,s);break;case 2:strcpy(compare_a,s);break;case 3:strcpy(compare_b,s);break;}}
void probe_sorted(int n,const char *s){if(lines[n])free(lines[n]);lines[n]=s?dupstr(s):NULL;}
void probe_pick_input(int n,int v){pick_values[n]=v;}
void probe_nhfile(int k,int v){if(k==0)nhfile.mode=v;else if(k==1)nhfile.structlevel=v;else nhfile.fnidx=v;}
void probe_io_size(int n){io_len=n;io_pos=0;}
int probe_io_length(void){return io_len;}
int probe_io_position(int n){if(n>=0)io_pos=n;return io_pos;}
int probe_free_count(int kind){return free_counts[kind];}
void *probe_pointer(int k,int row){switch(k){case 0:return &objects[row];case 1:return &obj_descr[row];case 2:return output;case 3:return io;case 4:return &svb.bases[0];case 5:return &svd.disco[0];case 6:return &go.oclass_prob_totals[0];case 7:return &obj;case 8:return (void*)last_string;case 9:return lines;case 10:return &nhfile;}return NULL;}
long probe_action(int op,int a,int b,int c,int d){switch(op){case 0:setgemprobs(a?&u.uz:NULL);break;case 1:randomize_gem_colors();break;case 2:shuffle(a,b,c);break;case 3:init_objects();break;case 4:init_oclass_probs();break;case 5:obj_shuffle_range(a,&low,&high);break;case 6:shuffle_all();break;case 7:return objdescr_is(a<0?NULL:&obj,compare_a);case 8:oinit();break;case 9:io_pos=io_len=0;savenames(&nhfile);break;case 10:io_pos=0;restnames(&nhfile);break;case 11:observe_object(&obj);break;case 12:discover_object(a,b,c,d);break;case 13:undiscover_object(a);break;case 14:return interesting_to_discover(a);case 15:compare_cells[0]=compare_a;compare_cells[1]=compare_b;return discovered_cmp(&compare_cells[0],&compare_cells[1]);case 16:last_string=sortloot_descr(a,output);break;case 17:return choose_disco_sort(a);case 18:last_string=disco_typename(a);strcpy(output,last_string);break;case 19:disco_append_typename(output,a);break;case 20:disco_fmt_uniq(a,output);break;case 21:disco_output_sorted(19,lines,a,b);break;case 22:return dodiscovered();case 23:last_string=oclass_to_name(a,output);break;case 24:return doclassdisco();case 25:rename_disco();break;case 26:get_sortdisco(output,a);break;}return 0;}
const void *probe_table_pointer(int t){
#ifdef TELEPORT_REFERENCE_TU
if(t==0)return uniq_objs;if(t==1)return disco_order_let;if(t==2)return disco_orders_descr;
#endif
return NULL;}
int probe_table_count(int t){
#ifdef TELEPORT_REFERENCE_TU
if(t==0)return SIZE(uniq_objs);if(t==1)return sizeof disco_order_let;if(t==2)return SIZE(disco_orders_descr);
#endif
return 0;}
const char *probe_snapshot(void){int i,j;char *p=statebuf;p+=sprintf(p,"state:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;out:%s;counts:%d:%d:%d:%d:%d;",flags.discosort,flags.menu_style,iflags.menu_requested,program_state.in_moveloop,program_state.gameover,low,high,obj.dknown,obj.known,pick_call,output,free_counts[0],free_counts[1],free_counts[2],free_counts[3],free_counts[4]);for(i=0;i<MAXOCLASSES+2;i++)p+=sprintf(p,"b:%d;",svb.bases[i]);for(i=0;i<MAXOCLASSES;i++)p+=sprintf(p,"prob:%d;",go.oclass_prob_totals[i]);for(i=0;i<NUM_OBJECTS;i++){unsigned char raw[sizeof(struct objclass)];uintptr_t present=objects[i].oc_uname!=NULL;memcpy(raw,&objects[i],sizeof raw);memcpy(raw+offsetof(struct objclass,oc_uname),&present,sizeof present);p+=sprintf(p,"r%d:%d:",i,svd.disco[i]);for(j=0;j<sizeof raw;j++)p+=sprintf(p,"%02x",raw[j]);p+=sprintf(p,":%s;",objects[i].oc_uname?objects[i].oc_uname:"<NULL>");}p+=sprintf(p,"lines:");for(i=0;i<32;i++)p+=sprintf(p,"%d,",lines[i]!=NULL);return statebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}

int probe_compare_count(void){return compare_count;}
const char *probe_compare_text(int index,int side){return compare_text+(side?compare_records[index].second:compare_records[index].first);}
int probe_compare_result(int index){return compare_records[index].result;}
int probe_compare_again(int index){const char *left=probe_compare_text(index,0),*right=probe_compare_text(index,1);return sort_compare(&left,&right);}
