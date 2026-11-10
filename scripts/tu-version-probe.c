#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(gh) gh;
__typeof__(gl) gl;
__typeof__(gc) gc;
__typeof__(windowprocs) windowprocs;
winid WIN_MESSAGE=3;
extern const char regex_id[11];
static NHFILE fixture_file;
static struct version_info fixture_version;
static int opts[40],mismatch;
static unsigned char iobuf[16384];
static unsigned io_size,io_position;
static char tracebuf[1048576],statebuf[32768],output[8192],strings[24][4096];
static void *growth;
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*4];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(raw_printf) MSG(impossible)
static winid create_window(int typ){append("create:%d;",typ);return opts[0]?WIN_ERR:19;}
static void put_window(winid w,int attr,const char *s){append("put:%d:%d:%s;",w,attr,s);}
static void display_window(winid w,boolean b){append("display:%d:%d;",w,b);}
static void destroy_window(winid w){append("destroy:%d;",w);}
static void raw_window(const char *s){append("raw:%s;",s);}
static void wait_window(void){append("wait;");}
static void callback(void){if(opts[30]){opts[30]=0;append("nested-begin;");doversion();append("nested-end;");}if(opts[31]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew;");}}
char *mdlib_version_string(char *b,const char *delimiter){append("mdlib:%s;",delimiter);strcpy(b,"5.0.7-fallback");callback();return b;}
const char *nh_basename(const char *s,boolean keep){const char *p;append("basename:%s:%d;",s,keep);p=strrchr(s,'/');return p?p+1:s;}
char *get_port_id(char *b){append("portid;");if(opts[1])return NULL;strcpy(b,strings[9]);return b;}
void port_insert_pastebuf(char *s){append("paste:%s;",s);callback();}
void runtime_info_init(void){append("runtime-init;");callback();}
void release_runtime_info(void){append("runtime-release;");}
const char *do_runtime_info(int *ctx){int i=(*ctx)++;append("runtime:%d;",i);callback();return i<opts[2]?strings[10+i]:NULL;}
const char *get_lua_version(void){append("lua-version;");strcpy(gl.lua_ver,"Lua live 5.4");strcpy(gl.lua_copyright,"Copyright live Lua");callback();return gl.lua_ver;}
const char *__real_datamodel(int);
const char *__wrap_datamodel(int i){const char *s=opts[3]==1?"ILP32LL64":opts[3]==2?"IL32LLP64":opts[3]==3?"I32LP64":opts[3]==4?"ILP64":NULL;append("datamodel:%d:%d;",i,opts[3]);return s?s:__real_datamodel(i);}
void bufon(int fd){append("bufon:%d;",fd);}
void bufoff(int fd){append("bufoff:%d;",fd);}
static void write_bytes(const void *p,unsigned n,const char *name){append("write:%s:%u:%u;",name,n,io_size);if(io_size+n>sizeof iobuf)abort();memcpy(iobuf+io_size,p,n);io_size+=n;callback();}
static void read_bytes(void *p,unsigned n,const char *name){unsigned amount=io_position<io_size?io_size-io_position:0;if(amount>n)amount=n;append("read:%s:%u:%u:%u;",name,n,io_position,amount);if(amount)memcpy(p,iobuf+io_position,amount);io_position+=amount;callback();}
void sfo_char(NHFILE *f,char *p,const char *s,int n){write_bytes(p,n,s);}
void sfo_uchar(NHFILE *f,uchar *p,const char *s){write_bytes(p,sizeof *p,s);}
void sfo_version_info(NHFILE *f,struct version_info *p,const char *s){write_bytes(p,sizeof *p,s);}
void sfi_char(NHFILE *f,char *p,const char *s,int n){read_bytes(p,n,s);}
void sfi_uchar(NHFILE *f,uchar *p,const char *s){read_bytes(p,sizeof *p,s);}
void sfi_version_info(NHFILE *f,struct version_info *p,const char *s){read_bytes(p,sizeof *p,s);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/version.c"
#else
struct critical_sizes_with_names{uchar ucsize;const char *nm;};
struct rt_opt{const char *token,*value;};
extern struct critical_sizes_with_names critical_sizes[80];
extern uchar cscbuf[80];
extern void *teleport_version_storage(int);
extern void teleport_version_test_insert(char*);
#define insert_rtoption teleport_version_test_insert
#endif
#include "tu-version-layout.h"
void probe_reset(void){if(growth)free(growth);growth=NULL;memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&gh,0,sizeof gh);memset(&gl,0,sizeof gl);memset(&gc,0,sizeof gc);memset(&fixture_file,0,sizeof fixture_file);memset(&fixture_version,0,sizeof fixture_version);memset(&nomakedefs,0,sizeof nomakedefs);memset(opts,0,sizeof opts);memset(strings,0,sizeof strings);memset(output,0xa5,sizeof output);output[0]=0;memset(iobuf,0xa5,sizeof iobuf);io_size=io_position=0;mismatch=12345;WIN_MESSAGE=3;strcpy(strings[0],"5.0.7");strcpy(strings[1],"NetHack 5.0.7 build date.");strcpy(strings[5],"Copyright native C.");strcpy(strings[6],"/usr/local/bin/NetHack");strcpy(strings[9],"fixture-port");nomakedefs.version_string=strings[0];nomakedefs.version_id=strings[1];nomakedefs.copyright_banner_c=strings[5];gh.hname=strings[6];nomakedefs.version_number=0x05000700UL;nomakedefs.version_features=0x12345678UL;nomakedefs.ignored_features=0x100UL;nomakedefs.version_sanity1=0x032101efUL;fixture_version.incarnation=nomakedefs.version_number;fixture_version.feature_set=nomakedefs.version_features;fixture_version.entity_count=nomakedefs.version_sanity1;fixture_file.fd=17;fixture_file.mode=WRITING;fixture_file.structlevel=1;flags.versinfo=VI_NAME|VI_NUMBER|VI_BRANCH;opts[2]=8;strcpy(strings[10],"");strcpy(strings[11],"    ignored program\n");strcpy(strings[12],"Features:\n");strcpy(strings[13],"  :PATMATCH: and :LUAVERSION:\n");strcpy(strings[14],"  :LUACOPYRIGHT:\n");strcpy(strings[15],"Windows:\n");strcpy(strings[16],"    tty\tand GUI\n");strcpy(strings[17],"");windowprocs.win_create_nhwindow=create_window;windowprocs.win_putstr=put_window;windowprocs.win_display_nhwindow=display_window;windowprocs.win_destroy_nhwindow=destroy_window;windowprocs.win_raw_print=raw_window;windowprocs.win_wait_synch=wait_window;tracebuf[0]=0;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;if(k==4)WIN_MESSAGE=v;if(k==5)iflags.menu_requested=v;if(k==6)flags.versinfo=v;}
void probe_nomake(int k,unsigned long v){switch(k){case 0:nomakedefs.version_number=v;break;case 1:nomakedefs.version_features=v;break;case 2:nomakedefs.ignored_features=v;break;case 3:nomakedefs.version_sanity1=v;break;case 4:nomakedefs.build_time=v;break;}}
void probe_string(int k,const char *value){if(value){strncpy(strings[k],value,sizeof strings[k]-1);strings[k][sizeof strings[k]-1]=0;}switch(k){case 0:nomakedefs.version_string=value?strings[k]:NULL;break;case 1:nomakedefs.version_id=value?strings[k]:NULL;break;case 2:nomakedefs.git_sha=value?strings[k]:NULL;break;case 3:nomakedefs.git_branch=value?strings[k]:NULL;break;case 4:nomakedefs.git_prefix=value?strings[k]:NULL;break;case 5:nomakedefs.copyright_banner_c=value?strings[k]:NULL;break;case 6:gh.hname=value?strings[k]:NULL;break;case 7:strncpy(gl.lua_ver,value?value:"",sizeof gl.lua_ver-1);gl.lua_ver[sizeof gl.lua_ver-1]=0;break;case 8:strncpy(gl.lua_copyright,value?value:"",sizeof gl.lua_copyright-1);gl.lua_copyright[sizeof gl.lua_copyright-1]=0;break;}}
void probe_version(int k,unsigned long v){if(k==0)fixture_version.incarnation=v;else if(k==1)fixture_version.feature_set=v;else fixture_version.entity_count=v;}
void probe_nhfile(int k,int v){switch(k){case 0:fixture_file.mode=v;break;case 1:fixture_file.structlevel=v;break;case 2:fixture_file.fieldlevel=v;break;case 3:fixture_file.fnidx=v;break;case 4:fixture_file.fd=v;break;}}
unsigned long probe_action(int op,unsigned long flagsarg,size_t size,const char *s,int b){char *p;switch(op){case 0:p=version_string(output,size);append("returned:%d;",p==output);break;case 1:p=getversionstring(output,size);append("returned:%d;",p==output);break;case 2:p=status_version(output,size,b);append("returned:%d;",p==output);break;case 3:return doversion();case 4:return doextversion();case 5:early_version_info(b);break;case 6:strcpy(output,s);insert_rtoption(output);break;case 7:return check_version(&fixture_version,s,b,flagsarg);case 8:return get_feature_notice_ver((char*)s);case 9:return get_current_feature_ver();case 10:p=(char*)copyright_banner_line(b);if(p)strcpy(output,p);else strcpy(output,"<NULL>");break;case 11:dump_version_info();break;case 12:store_version(&fixture_file);break;case 13:return get_critical_size_count();case 14:store_critical_bytes(&fixture_file);break;case 15:return uptodate(&fixture_file,s,flagsarg);case 16:return compare_critical_bytes(&fixture_file,b?&mismatch:NULL,flagsarg);case 17:return validate(&fixture_file,s,b);}return 0;}
char *probe_output(void){return output;}
size_t probe_output_size(void){return sizeof output;}
void *probe_pointer(int id){switch(id){case 0:return critical_sizes;case 1:return cscbuf;case 2:
#ifdef TELEPORT_REFERENCE_TU
return rt_opts;
#else
return teleport_version_storage(2);
#endif
case 3:return &fixture_version;case 4:return &fixture_file;case 5:return &gl;case 6:return &nomakedefs;}return NULL;}
int probe_table_count(void){return sizeof critical_sizes/sizeof critical_sizes[0];}
int probe_table_size(int n){return critical_sizes[n].ucsize;}
const char *probe_table_name(int n){return critical_sizes[n].nm;}
int probe_rt_count(void){return 3;}
const char *probe_rt_token(int n){struct rt_opt *r=probe_pointer(2);return r[n].token;}
const char *probe_rt_value(int n){struct rt_opt *r=probe_pointer(2);return r[n].value;}
unsigned char *probe_io_pointer(void){return iobuf;}
unsigned probe_io_size(void){return io_size;}
void probe_io_length(unsigned n){io_size=n;}
void probe_io_position(unsigned n){io_position=n;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){char *p=statebuf;unsigned i;p+=sprintf(p,"state:%d:%d:%u:%u:%lu:%lu:%lu;",gc.converted_savefile_loaded,mismatch,io_size,io_position,fixture_version.incarnation,fixture_version.feature_set,fixture_version.entity_count);p+=sprintf(p,"csc:");for(i=0;i<sizeof cscbuf;i++)p+=sprintf(p,"%02x",cscbuf[i]);p+=sprintf(p,";lua:%s:%s;nhfile:%d:%d:%d:%d:%d;",gl.lua_ver,gl.lua_copyright,fixture_file.mode,fixture_file.structlevel,fixture_file.fieldlevel,fixture_file.fnidx,fixture_file.fd);return statebuf;}
