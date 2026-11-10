/* Controlled C callers and libc spies; hacklib algorithms remain in the TU. */
#define DETERMINISTIC_QSORT_IMPL
#include "hack.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <wchar.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef malloc
#undef free
#undef read
#undef write
extern void *malloc(size_t);
extern void free(void*);
extern ssize_t read(int,void*,size_t);
extern ssize_t write(int,const void*,size_t);
static unsigned char buffers[3][2048],sortbuf[8192];
static char output[2048],tracebuf[131072],statebuf[65536],iobuf[65536];
static const char *result;
static int opts[40],alloc_active,alloc_calls,free_calls,fail_mask,copy_active;
static void *allocated[3],*growth;
static size_t stride;static unsigned char *sortbase;
static struct {size_t idx;} indexargs[2];
static void append(char*buf,size_t cap,const char*f,...){va_list a;va_start(a,f);vsnprintf(buf+strlen(buf),cap-strlen(buf),f,a);va_end(a);}
#define TRACE(...) append(tracebuf,sizeof tracebuf,__VA_ARGS__)
#define IO(...) append(iobuf,sizeof iobuf,__VA_ARGS__)
#ifdef TELEPORT_NATIVE_HACKLIB_IO
extern void *teleport_native_malloc(size_t);
#define FIXTURE_GROW_ALLOC teleport_native_malloc
#else
#define FIXTURE_GROW_ALLOC malloc
#endif
static void callback(int kind){if(opts[30]==kind){opts[30]=0;TRACE("nested:%s;",s_suffix("fixture"));}if(opts[31]==kind&&!growth){growth=FIXTURE_GROW_ALLOC(emscripten_get_heap_size()+16777216);if(!growth)abort();TRACE("grow:%d;",kind);}}
void panic(const char*f,...){abort();}
void*teleport_probe_malloc(size_t n){void*p;if(!alloc_active)return malloc(n);alloc_calls++;TRACE("malloc:%d:%zu;",alloc_calls,n);if(fail_mask&(1<<(alloc_calls-1)))p=0;else p=malloc(n);if(alloc_calls<=2)allocated[alloc_calls]=p;callback(2);return p;}
void teleport_probe_free(void*p){if(alloc_active){int i,which=99;for(i=1;i<=2;i++)if(allocated[i]==p)which=i;free_calls++;TRACE("free:%d;",which);callback(3);}free(p);}
#ifdef TELEPORT_NATIVE_HACKLIB_IO
extern ssize_t teleport_native_hacklib_read(int,void*,size_t);
extern ssize_t teleport_native_hacklib_write(int,const void*,size_t);
#define FIXTURE_READ teleport_native_hacklib_read
#define FIXTURE_WRITE teleport_native_hacklib_write
#else
#define FIXTURE_READ read
#define FIXTURE_WRITE write
#endif
ssize_t teleport_probe_read(int fd,void*p,size_t n){ssize_t r=FIXTURE_READ(fd,p,n);int saved=errno;if(copy_active){IO("read:%zu:%ld:%d;",n,(long)r,r<0?saved:0);callback(4);}errno=saved;return r;}
ssize_t teleport_probe_write(int fd,const void*p,size_t n){ssize_t r=FIXTURE_WRITE(fd,p,n);int saved=errno;if(copy_active){IO("write:%zu:%ld:%d;",n,(long)r,r<0?saved:0);callback(5);}errno=saved;return r;}
static int compare_keys(const void*a,const void*b,int mode){int ka,kb,c;size_t ia=((const unsigned char*)a-sortbase)/stride,ib=((const unsigned char*)b-sortbase)/stride;if(opts[8]){memcpy(&ka,a,sizeof ka);memcpy(&kb,b,sizeof kb);}else{ka=*(const unsigned char*)a;kb=*(const unsigned char*)b;}c=mode==2?0:ka<kb?-1:ka>kb;TRACE("cmp:%d:%zu:%zu:%d:%d:%d;",mode,ia,ib,ka,kb,c);callback(1);return mode==1?-c:mode==3?(c<0?(-2147483647-1):c>0?2147483647:0):c;}
static int QSORTCALLBACK compare_ascending(const void*a,const void*b){return compare_keys(a,b,0);}static int QSORTCALLBACK compare_descending(const void*a,const void*b){return compare_keys(a,b,1);}static int QSORTCALLBACK compare_equal(const void*a,const void*b){return compare_keys(a,b,2);}static int QSORTCALLBACK compare_extreme(const void*a,const void*b){return compare_keys(a,b,3);}
static int(QSORTCALLBACK*comparator(int n))(const void*,const void*){switch(n){case 0:return compare_ascending;case 1:return compare_descending;case 2:return compare_equal;case 3:return compare_extreme;default:return 0;}}
#ifdef TELEPORT_REFERENCE_TU
#define malloc teleport_probe_malloc
#define free teleport_probe_free
#define read teleport_probe_read
#define write teleport_probe_write
#include "../.cache/wasm64-build/tree/src/hacklib.c"
#undef malloc
#undef free
#undef read
#undef write
#else
extern int teleport_hacklib_test_compare(const void*,const void*);
extern uintptr_t teleport_hacklib_test_qsort_state(int);
extern void teleport_hacklib_test_reset(void);
#define nh_qsort_idx_cmp teleport_hacklib_test_compare
#endif
#include "tu-hacklib-layout.h"
#ifdef TELEPORT_REFERENCE_TU
_Static_assert(sizeof(struct nh_qsort_index)==sizeof(struct teleport_hacklib_index),"index size");
_Static_assert(offsetof(struct nh_qsort_index,idx)==offsetof(struct teleport_hacklib_index,idx),"index offset");
_Static_assert(sizeof(((struct nh_qsort_index*)0)->idx)==sizeof(size_t),"index width");
#endif
uintptr_t probe_sort_state(int field){
#ifdef TELEPORT_REFERENCE_TU
return field==0?(uintptr_t)nh_qsort_base:field==1?nh_qsort_size:(uintptr_t)nh_qsort_cmp_fn;
#else
return teleport_hacklib_test_qsort_state(field);
#endif
}
void probe_reset(void){alloc_active=copy_active=0;if(growth)free(growth);growth=0;memset(buffers,0xa5,sizeof buffers);memset(sortbuf,0x5a,sizeof sortbuf);for(int i=0;i<3;i++)buffers[i][16]=0;memset(opts,0,sizeof opts);opts[0]=opts[1]=opts[2]=16;result=0;output[0]=tracebuf[0]=iobuf[0]=0;alloc_calls=free_calls=fail_mask=0;allocated[0]=allocated[1]=allocated[2]=0;sortbase=sortbuf+16;stride=8;indexargs[0].idx=0;indexargs[1].idx=1;
#ifdef TELEPORT_REFERENCE_TU
nh_qsort_base=0;nh_qsort_size=0;nh_qsort_cmp_fn=0;
#else
teleport_hacklib_test_reset();
#endif
}
void probe_input(int n,const char*s){strcpy((char*)buffers[n]+16,s);}void probe_alloc_option(int k,int v){if(k==0)fail_mask=v;else opts[k]=v;}int probe_alloc_count(int k){return k?free_calls:alloc_calls;}
uintptr_t probe_comparator_pointer(int n){return(uintptr_t)comparator(n);}
void probe_sort_setup(int size,int offset){stride=size;sortbase=sortbuf+offset;}
void probe_sort_action(size_t count,size_t size,int which,int nullbase){alloc_active=1;alloc_calls=free_calls=0;allocated[1]=allocated[2]=0;nh_deterministic_qsort(nullbase?0:sortbase,count,size,comparator(which));alloc_active=0;}
int probe_fd_action(int in,int out){int r;copy_active=1;r=copy_bytes(in,out);copy_active=0;return r;}const char*probe_io_trace(void){return iobuf;}
long probe_action(int op,int a,int b,int c,int d,size_t n){char*dst=(char*)buffers[0]+opts[0],*s=(char*)buffers[opts[6]?0:1]+opts[1],*t=(char*)buffers[opts[7]?0:2]+opts[2];switch(op){case 0:indexargs[0].idx=a;indexargs[1].idx=b;return nh_qsort_idx_cmp(&indexargs[0],&indexargs[1]);case 1:probe_sort_action(a,b,c,d);break;case 2:return digit(a);case 3:return letter(a);case 4:return highc(a);case 5:return lowc(a);case 6:result=lcase(dst);break;case 7:result=ucase(dst);break;case 8:result=upstart(a?0:dst);break;case 9:result=upwords(dst);break;case 10:result=mungspaces(dst);break;case 11:result=trimspaces(dst);break;case 12:result=strip_newline(dst);break;case 13:result=eos(dst);break;case 14:result=c_eos(dst);break;case 15:return str_start_is(dst,s,a);case 16:return str_end_is(dst,s);case 17:return str_lines_maxlen(dst);case 18:result=strkitten(dst,a);break;case 19:copynchars(dst,s,a);break;case 20:return chrcasecpy(a,b);case 21:result=strcasecpy(dst,s);break;case 22:result=s_suffix(dst);break;case 23:result=ing_suffix(dst);break;case 24:result=xcrypt(s,dst);break;case 25:return onlyspace(dst);case 26:result=tabexpand(dst);break;case 27:result=visctrl(a);break;case 28:result=stripchars(dst,s,t);break;case 29:result=stripdigits(dst);break;case 30:result=strsubst(dst,s,t);break;case 31:return strNsubst(dst,s,t,a);case 32:result=findword(dst,s,a,b);break;case 33:result=ordin(a);break;case 34:result=sitoa(a);break;case 35:return sgn(a);case 36:return distmin(a,b,c,d);case 37:return dist2(a,b,c,d);case 38:return isqrt(a);case 39:return online2(a,b,c,d);case 40:return strncmpi(dst,s,a);case 41:result=strstri(dst,s);break;case 42:return fuzzymatch(dst,s,t,a);case 43:return swapbits(a,b,c);case 44:if(a==0)nh_snprintf("fixture",456,dst,n,"%s:%d:%u:%ld:%llu:%zu:%.2f:%p",s,b,(unsigned)c,(long)0x20000000000001UL,~0ULL,(size_t)37,3.25,(void*)(uintptr_t)0x123456);else if(a==1)nh_snprintf("fixture",456,dst,n,"%.*s",b,s);else if(a==2)nh_snprintf("fixture",456,dst,n,"%lc",(wint_t)b);else nh_snprintf("fixture",456,dst,n,"%s",s);break;case 45:return unicodeval_to_utf8str(a,(uint8*)dst,n);case 46:return case_insensitive_comp(dst,s);case 47:return probe_fd_action(a,b);case 48:result=datamodel(a);break;case 49:result=what_datamodel_is_this(a,b,c,d,(int)n,opts[5]);break;}if(result)strcpy(output,result);else output[0]=0;return 0;}
void*probe_pointer(int k,int i){if(k==0)return buffers[i];if(k==1)return(void*)result;if(k==2)return output;if(k==3)return sortbuf;return indexargs;}
const char*probe_snapshot(void){char*p=statebuf;int i,j,kind=-1;uintptr_t base=probe_sort_state(0),cmp=probe_sort_state(2),raw=(uintptr_t)result;long offset=-1;for(i=0;i<3;i++)if(raw>=(uintptr_t)buffers[i]&&raw<(uintptr_t)(buffers[i]+sizeof buffers[i])){kind=i;offset=raw-(uintptr_t)buffers[i];}p+=sprintf(p,"result:%d:%ld:%s;sort:%ld:%lu:",kind,offset,output,base?(long)(base-(uintptr_t)sortbuf):-1L,(unsigned long)probe_sort_state(1));kind=-1;for(i=0;i<4;i++)if(cmp==(uintptr_t)comparator(i))kind=i;p+=sprintf(p,"%d;alloc:%d:%d;",kind,alloc_calls,free_calls);for(i=0;i<3;i++){p+=sprintf(p,"b%d:",i);for(j=0;j<sizeof buffers[i];j++)p+=sprintf(p,"%02x",buffers[i][j]);}p+=sprintf(p,"sortbytes:");for(i=0;i<sizeof sortbuf;i++)p+=sprintf(p,"%02x",sortbuf[i]);return statebuf;}
uintptr_t probe_stack(void){return(uintptr_t)emscripten_stack_get_current();}

const char*probe_trace(void){return tracebuf;}
int probe_table_count(void){
#ifdef TELEPORT_REFERENCE_TU
return SIZE(dm);
#else
return 0;
#endif
}
uintptr_t probe_table(int row,int field){
#ifdef TELEPORT_REFERENCE_TU
return field<5?(uintptr_t)dm[row].sz[field]:(uintptr_t)(field==5?dm[row].datamodel:dm[row].dmplatform);
#else
return 0;
#endif
}
