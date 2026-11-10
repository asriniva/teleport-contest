#include "hack.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <emscripten/stack.h>
#include <emscripten.h>
#include "tu-report-layout.h"

__typeof__(gc) gc;
__typeof__(gs) gs;
struct sysopt_s sysopt;
__typeof__(windowprocs) windowprocs;
static char trace_storage[131072], output[32768], input[16384], messages[50][512];
static int options[16], position;
static void append(const char *format, ...) {
    va_list ap; va_start(ap,format);
    vsnprintf(trace_storage+strlen(trace_storage),sizeof trace_storage-strlen(trace_storage),format,ap);
    va_end(ap);
}
static void raw(const char *text) { append("raw:%s;", text); }
void panic(const char *format, ...) { abort(); }
void pline(const char *format, ...) { va_list ap;char buf[1024];va_start(ap,format);vsnprintf(buf,sizeof buf,format,ap);va_end(ap);append("pline:%s;",buf); }
void NH_abort(char *why) { append("abort:%d;", why!=NULL); }
char *version_string(char *out,size_t size) { snprintf(out,size,"5.0.0-test");append("version:%zu;",size);return out; }
char *getversionstring(char *out,size_t size) { snprintf(out,size,"git fixture /#+");append("git:%zu;",size);return out; }
ssize_t teleport_probe_readlink(const char *path,char *out,size_t size) { const char *value="/fixture/nethack";append("readlink:%s:%zu;",path,size);if(options[0]<0)return -1;memcpy(out,value,strlen(value));return strlen(value); }
int teleport_probe_open(const char *path,int flags,...) { append("open:%s:%d;",path,flags);position=0;return options[1]<0?-1:9; }
ssize_t teleport_probe_read(int fd,void *out,size_t size) { int n;append("read:%d:%zu;",fd,size);if(options[2]<0)return -1;n=options[3]-position;if(n>(int)size)n=size;if(n<0)n=0;memcpy(out,input+position,n);position+=n;return n; }
ssize_t teleport_probe_write(int fd,const void *in,size_t size) { append("write:%d:%zu:%.*s;",fd,size,(int)size,(const char*)in);return size; }
int teleport_probe_close(int fd) { append("close:%d;",fd);return 0; }
pid_t teleport_probe_fork(void) { append("fork;");return options[4]; }
int teleport_probe_execve(const char *path,char *const *argv,char *const *env) { snprintf(output,sizeof output,"%s",argv[1]);append("exec:%s:%s;",path,argv[0]);errno=ENOENT;return -1; }
pid_t teleport_probe_waitpid(pid_t pid,int *status,int flags) { append("wait:%d:%d;",pid,flags);*status=options[5];return pid; }
void (*teleport_probe_signal(int sig,void (*handler)(int)))(int) { append("signal:%d:%d;",sig,handler!=NULL);return NULL; }
/* Throw after recording exit so the child's otherwise-unreachable return is
 * tested without terminating Node or the oracle process. */
EM_JS(void, teleport_report_probe_throw_exit, (int status), { throw new Error('REPORT fixture exit ' + status); });
void teleport_probe_exit(int status) { append("exit:%d;",status);teleport_report_probe_throw_exit(status);__builtin_unreachable(); }

#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/report.c"
_Static_assert(sizeof bid == sizeof(((struct teleport_report_storage *) 0)->bid),
               "REPORT bid backing must match the original private array");
_Static_assert(sizeof url == sizeof(((struct teleport_report_storage *) 0)->url),
               "REPORT URL backing must match the original private array");
#endif
#include "../nethack-c/wasm/tu-fragments/report.support.c"

void probe_reset(void) { int i;memset(&gc,0,sizeof gc);memset(&gs,0,sizeof gs);memset(&sysopt,0,sizeof sysopt);memset(options,0,sizeof options);memset(input,0,sizeof input);memset(output,0,sizeof output);memset(messages,0,sizeof messages);trace_storage[0]=0;gc.crash_urlmax=-1;gs.saved_pline_index=1;windowprocs.win_raw_print=raw;options[4]=42;for(i=0;i<16384;i++)input[i]=(char)(i*73+19); }
void probe_option(int key,int value) { if(key>=0&&key<16)options[key]=value; }
void probe_config(const char *url,const char *name,const char *email,int maximum) {sysopt.crashreporturl=(char*)url;gc.crash_name=(char*)name;gc.crash_email=(char*)email;gc.crash_urlmax=maximum;}
void probe_message(int slot,const char *text) {if(slot>=0&&slot<50){if(text){snprintf(messages[slot],sizeof messages[slot],"%s",text);gs.saved_plines[slot]=messages[slot];}else gs.saved_plines[slot]=NULL;}}
void probe_index(unsigned index) {gs.saved_pline_index=index;}
void probe_init(void) {crashreport_init(0,NULL);}
void probe_bidshow(void) {crashreport_bidshow();}
int probe_encode(const char *in,char **out,int *remaining,char *mark) {return swr_add_uricoded(in,out,remaining,mark);}
int probe_submit(int cos,const char *msg,const char *why) {return submit_web_report(cos,msg,why);}
int probe_bug(void) {return dobugreport();}
int probe_libc(void) {return NH_panictrace_libc();}
int probe_gdb(void) {return NH_panictrace_gdb();}
const char *probe_saved(int lineno) {return get_saved_pline(lineno);}
void probe_handler(void) {panictrace_handler(0);}
void probe_signals(int set) {panictrace_setsignals((boolean)set);}
const char *probe_trace(void) {return trace_storage;}
const char *probe_output(void) {return output;}
void probe_clear(void) {trace_storage[0]=0;}
size_t probe_stack(void) {return emscripten_stack_get_current();}
size_t probe_context_size(void) {return sizeof sysopt;}
int probe_layout_count(void) {return SIZE(report_layout);}
const char *probe_layout_name(int i) {return report_layout[i].name;}
size_t probe_layout_value(int i) {return report_layout[i].value;}
const char *probe_crashreport(void) {return CRASHREPORT;}
const char *probe_devteam(void) {return DEVTEAM_URL;}
