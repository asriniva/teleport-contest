#include "hack.h"
#include "mail.h"
#include <pwd.h>
#include <sys/stat.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef free
extern void free(void *);
__typeof__(u) u;
__typeof__(gs) gs;
__typeof__(gv) gv;
__typeof__(svl) svl;
__typeof__(svm) svm;
__typeof__(svp) svp;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(windowprocs) windowprocs;
winid WIN_MESSAGE;
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind"};
struct permonst mons[NUMMONS+1];
static struct monst monsters[4];
static struct obj mail_object;
static stairway stairways[3];
static coord coordinates[2];
static struct mail_info info;
static seenV visibility[ROWNO][COLNO], *visibility_rows[ROWNO];
static char trace[262144],snapshot[16384],mailenv[256],readerenv[256],username[256]="recorder";
static int opts[16],rng_count,rng_seed=1,free_count,probe_active,exit_status;
static long stat_time=1,stat_size=1;
static jmp_buf exit_capture;
static void *growth;
static struct passwd account;
static void append(const char *format,...)
{va_list ap;va_start(ap,format);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),format,ap);va_end(ap);}
static void callback(int stage)
{
    if(opts[10]==stage){opts[10]=0;ck_server_admin_msg();append("reenter:%d;",stage);}
    if(opts[11]==stage&&!growth){opts[11]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}
    if(opts[12]==stage){opts[12]=0;u.uroleplay.deaf=!u.uroleplay.deaf;append("deaf:%d;",u.uroleplay.deaf);}
}
void panic(const char *format,...){(void)format;abort();}
void teleport_probe_free(void *ptr){free_count++;append("free;");free(ptr);}
char *nh_getenv(const char *name)
{append("env:%s;",name);callback(1);if(!strcmp(name,"MAIL"))return opts[0]?mailenv:NULL;if(!strcmp(name,"MAILREADER"))return opts[1]?readerenv:NULL;return NULL;}
int teleport_probe_stat(const char *path,struct stat *out)
{
    append("stat:%s;",path);callback(2);if(opts[2])return -1;
    memset(out,0xa5,sizeof *out);out->st_mtime=stat_time;out->st_size=stat_size;return 0;
}
uid_t teleport_probe_getuid(void){append("uid;");callback(3);return 12345;}
struct passwd *teleport_probe_getpwuid(uid_t uid){append("passwd:%u;",uid);callback(4);account.pw_name=username;return &account;}
int teleport_probe_execl(const char *path,const char *arg0,char *end)
{append("execl:%s:%d:%d;",path,path==arg0,end==NULL);callback(12);return -1;}
int child(int mode){append("child:%d;",mode);callback(11);return opts[3];}
void nh_terminate(int status){append("terminate:%d;",status);exit_status=status;if(!probe_active)abort();longjmp(exit_capture,1);}
boolean debugcore(const char *file,boolean wildcards){(void)file;(void)wildcards;return (boolean)opts[4];}
void pline(const char *format,...)
{char out[1024];va_list ap;va_start(ap,format);vsnprintf(out,sizeof out,format,ap);va_end(ap);append("pline:%s;",out);iflags.last_msg=999;callback(5);}
void verbalize(const char *format,...)
{char out[1024];va_list ap;va_start(ap,format);vsnprintf(out,sizeof out,format,ap);va_end(ap);append("voice:%s;",out);callback(6);}
int (rn2)(int bound){unsigned n=(unsigned)rng_seed;rng_seed=(int)(n*1664525U+1013904223U);rng_count++;append("rn2:%d;",bound);return (int)((unsigned)rng_seed%(unsigned)bound);}
boolean rng_log_enabled(void){return (boolean)opts[5];}
void rng_log_set_caller(const char *file,int line,const char *func){const char *name=strrchr(file,'/');append("rng:%s:%d:%s;",name?name+1:file,line,func);}
int isok(coordxy x,coordxy y){return (x>=1&&x<COLNO&&y>=0&&y<ROWNO);}
boolean accessible(coordxy x,coordxy y){return (boolean)(!opts[6]&&svl.level.locations[x][y].typ>DBWALL);}
boolean enexto(coord *out,coordxy x,coordxy y,struct permonst *pm)
{append("enexto:%d:%d:%d;",x,y,pm==&mons[PM_MAIL_DAEMON]);callback(7);if(opts[7])return FALSE;out->x=(coordxy)(x+1);out->y=y;return TRUE;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);callback(8);}
void place_monster(struct monst *mon,coordxy x,coordxy y)
{append("place:%ld:%d:%d;",(long)(mon-monsters),x,y);mon->mx=x;mon->my=y;svl.level.monsters[x][y]=mon;callback(9);}
void flush_screen(int cursor){append("flush:%d;",cursor);}
static void delay(void){append("delay;");callback(10);}
static void display(winid win,boolean blocking){append("display:%d:%d;",win,blocking);callback(13);}
struct monst *makemon(struct permonst *pm,coordxy x,coordxy y,mmflags_nht flags_)
{append("makemon:%d:%d:%d:%lu;",pm==&mons[PM_MAIL_DAEMON],x,y,(unsigned long)flags_);if(opts[8])return NULL;place_monster(&monsters[0],x,y);if(opts[9]&1){monsters[1].mx=u.ux-1;monsters[1].my=u.uy-1;svl.level.monsters[u.ux-1][u.uy-1]=&monsters[1];}return &monsters[0];}
const char *Hello(struct monst *mon){append("hello:%ld;",(long)(mon-monsters));return "Hello";}
struct obj *mksobj(int typ,boolean init,boolean artif)
{append("mksobj:%d:%d:%d;",typ,init,artif);memset(&mail_object,0,sizeof mail_object);mail_object.otyp=typ;return &mail_object;}
struct obj *oname(struct obj *obj,const char *name,unsigned flags_){append("oname:%d:%s:%u;",obj==&mail_object,name,flags_);return obj;}
void new_omailcmd(struct obj *obj,const char *cmd){append("command:%d:%s;",obj==&mail_object,cmd);}
struct obj *hold_another_object(struct obj *obj,const char *drop,const char *arg,const char *hold)
{append("hold:%d:%s:%d:%d;",obj==&mail_object,drop,arg==NULL,hold==NULL);callback(14);if(opts[9]&2){monsters[1].mx=stairways[0].sx;monsters[1].my=stairways[0].sy;svl.level.monsters[monsters[1].mx][monsters[1].my]=&monsters[1];}return obj;}
void mongone(struct monst *mon){int x,y;append("gone:%d:%d;",mon->mx,mon->my);for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)if(svl.level.monsters[x][y]==mon)svl.level.monsters[x][y]=NULL;}
#ifdef TELEPORT_REFERENCE_TU
#define stat(a,b) teleport_probe_stat(a,b)
#define getuid() teleport_probe_getuid()
#define getpwuid(a) teleport_probe_getpwuid(a)
#define execl(a,b,c) teleport_probe_execl(a,b,c)
#define free teleport_probe_free
#include "../nethack-c/upstream/src/mail.c"
#undef free
#undef stat
#undef getuid
#undef getpwuid
#undef execl
#else
extern boolean teleport_mail_test_start(coord*);
extern boolean teleport_mail_test_stop(coord*,coord*);
extern boolean teleport_mail_test_rush(struct monst*,int,int);
extern void teleport_mail_test_new(struct mail_info*);
extern long teleport_mail_test_state(int);
extern void teleport_mail_test_reset(void);
#define md_start teleport_mail_test_start
#define md_stop teleport_mail_test_stop
#define md_rush teleport_mail_test_rush
#define newmail teleport_mail_test_new
#endif
#include "tu-mail-layout.h"
int probe_layout_count(void){return SIZE(mail_layout);}
const char *probe_layout_name(int i){return mail_layout[i].name;}
size_t probe_layout_value(int i){return mail_layout[i].value;}
int probe_string_count(void){return 2;}
const char *probe_string_name(int i){return i==0?"MAILPATH":"DEF_MAILREADER";}
const char *probe_string_value(int i){return i==0?MAILPATH:DEF_MAILREADER;}
static long private_state(int index)
{
#ifdef TELEPORT_REFERENCE_TU
    return index==0?(long)mailbox:index==1?laststattime:index==2?(long)&omstat:(long)&nmstat;
#else
    return teleport_mail_test_state(index);
#endif
}
void probe_reset(void)
{
    int x,y;
    free_maildata();
#ifdef TELEPORT_REFERENCE_TU
    memset(&omstat,0,sizeof omstat);memset(&nmstat,0,sizeof nmstat);laststattime=0;
#else
    teleport_mail_test_reset();
#endif
    if(growth){free(growth);growth=NULL;}
    memset(&u,0,sizeof u);memset(&gs,0,sizeof gs);memset(&gv,0,sizeof gv);memset(&svl,0,sizeof svl);
    memset(&svm,0,sizeof svm);memset(&svp,0,sizeof svp);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);
    memset(opts,0,sizeof opts);memset(monsters,0,sizeof monsters);memset(stairways,0,sizeof stairways);memset(coordinates,0,sizeof coordinates);memset(&info,0,sizeof info);
    memset(visibility,0,sizeof visibility);for(y=0;y<ROWNO;y++)visibility_rows[y]=visibility[y];gv.viz_array=visibility_rows;
    for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)svl.level.locations[x][y].typ=ROOM;
    u.ux=10;u.uy=10;u.uz.dnum=1;flags.biff=TRUE;svm.moves=100;strcpy(svp.plname,"Recorder");iflags.last_msg=17;
    windowprocs.win_delay_output=delay;windowprocs.win_display_nhwindow=display;WIN_MESSAGE=42;
    trace[0]=0;free_count=0;rng_count=0;rng_seed=1;stat_time=1;stat_size=1;exit_status=-1;
    strcpy(mailenv,"/fixture/mailbox");strcpy(readerenv,"/fixture/reader");strcpy(username,"recorder");
}
void probe_option(int index,int value){opts[index]=value;}
void probe_env(int index,const char *text){strcpy(index==0?mailenv:index==1?readerenv:username,text);}
void probe_stat(long mtime,long size){stat_time=mtime;stat_size=size;}
void probe_moves(long value){svm.moves=value;}
void probe_hero(int x,int y,int swallow,int deaf){u.ux=(coordxy)x;u.uy=(coordxy)y;u.uswallow=swallow;u.uroleplay.deaf=deaf;}
void probe_prop(int index,long intrinsic,long extrinsic,long blocked){u.uprops[index].intrinsic=intrinsic;u.uprops[index].extrinsic=extrinsic;u.uprops[index].blocked=blocked;}
void probe_flags(int biff,int fuzzer){flags.biff=(boolean)biff;iflags.debug_fuzzer=(boolean)fuzzer;}
void probe_cell(int x,int y,int typ,int vis,int mon){svl.level.locations[x][y].typ=(schar)typ;visibility[y][x]=(seenV)vis;svl.level.monsters[x][y]=mon<0?NULL:&monsters[mon];}
void probe_row(int row,int min,int max){gv.viz_rmin[row]=(coordxy)min;gv.viz_rmax[row]=(coordxy)max;}
void probe_stairs(int index,int x,int y,int dnum,int next){stairways[index].sx=(coordxy)x;stairways[index].sy=(coordxy)y;stairways[index].tolev.dnum=(xint16)dnum;stairways[index].next=next<0?NULL:&stairways[next];gs.stairs=&stairways[0];}
void probe_mon(int index,int x,int y){monsters[index].mx=(coordxy)x;monsters[index].my=(coordxy)y;}
void probe_coord(int index,int x,int y){coordinates[index].x=(coordxy)x;coordinates[index].y=(coordxy)y;}
void probe_info(int typ,const char *display_text,const char *name,const char *cmd){info.message_typ=typ;info.display_txt=display_text;info.object_nam=name;info.response_cmd=cmd;}
int probe_action(int op,int a,int b)
{
    int result=0;probe_active=1;
    if(!setjmp(exit_capture))switch(op){case 0:free_maildata();break;case 1:getmailstatus();break;case 2:result=md_start(&coordinates[0]);break;case 3:result=md_stop(&coordinates[0],&coordinates[1]);break;case 4:result=md_rush(&monsters[0],a,b);break;case 5:newmail(&info);break;case 6:ckmailstatus();break;case 7:ck_server_admin_msg();break;case 8:readmail(NULL);break;case 9:result=md_stop(&coordinates[0],&coordinates[0]);break;}
    else result=-1;
    probe_active=0;return result;
}
const char *probe_trace(void){return trace;}
void probe_clear(void){trace[0]=0;}
const char *probe_snapshot(void)
{
    int x,y,i;char *p=snapshot;struct stat *old=(struct stat*)private_state(2),*now=(struct stat*)private_state(3);
    p+=sprintf(p,"mail:%s;last:%ld;old:%lld:%lld;new:%lld:%lld;coord:%d:%d:%d:%d;rng:%d:%d;free:%d;exit:%d;lastmsg:%d;deaf:%d;mons:",(char*)private_state(0)?(char*)private_state(0):"<NULL>",private_state(1),(long long)old->st_mtime,(long long)old->st_size,(long long)now->st_mtime,(long long)now->st_size,coordinates[0].x,coordinates[0].y,coordinates[1].x,coordinates[1].y,rng_count,rng_seed,free_count,exit_status,iflags.last_msg,u.uroleplay.deaf);
    for(i=0;i<4;i++)p+=sprintf(p,"%d:%d,",monsters[i].mx,monsters[i].my);
    for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)if(svl.level.monsters[x][y])p+=sprintf(p,"%d:%d:%ld,",x,y,(long)(svl.level.monsters[x][y]-monsters));
    return snapshot;
}
uintptr_t probe_pointer(int kind){return kind==0?(uintptr_t)coordinates:kind==1?(uintptr_t)monsters:kind==2?(uintptr_t)&info:(uintptr_t)private_state(kind==3?2:3);}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
