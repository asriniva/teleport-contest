/* MAIL typed ABI only: no mailbox/delivery/movement policy. */
#include "tu-mail-support.h"
static struct stat teleport_mail_stats[2];
void *teleport_mail_storage(int index) { return &teleport_mail_stats[index]; }
void *teleport_mail_global(int index)
{
    switch(index){case 0:return &u;case 1:return &gs;case 2:return &gv;
    case 3:return &svl;case 4:return &svm;case 5:return &svp;case 6:return &flags;
    case 7:return &iflags;case 8:return mons;default:return 0;}
}
int teleport_mail_hero_bit(int index) { return index==0?u.uswallow:u.uroleplay.deaf; }
int teleport_mail_win_message(void) { return WIN_MESSAGE; }
const char *teleport_mail_never_mind(void) { return Never_mind; }
const char *teleport_mail_config_string(int index) { return index==0?MAILPATH:DEF_MAILREADER; }
#ifdef TELEPORT_MAIL_PROBE
extern int teleport_probe_stat(const char *,struct stat *);
extern uid_t teleport_probe_getuid(void);
extern struct passwd *teleport_probe_getpwuid(uid_t);
extern int teleport_probe_execl(const char *,const char *,char *);
#endif
int teleport_mail_stat(const char *path,struct stat *out)
{
#ifdef TELEPORT_MAIL_PROBE
    return teleport_probe_stat(path,out);
#else
    return stat(path,out);
#endif
}
uid_t teleport_mail_getuid(void)
{
#ifdef TELEPORT_MAIL_PROBE
    return teleport_probe_getuid();
#else
    return getuid();
#endif
}
struct passwd *teleport_mail_getpwuid(uid_t uid)
{
#ifdef TELEPORT_MAIL_PROBE
    return teleport_probe_getpwuid(uid);
#else
    return getpwuid(uid);
#endif
}
int teleport_mail_execl(const char *path,const char *arg0,char *end)
{
#ifdef TELEPORT_MAIL_PROBE
    return teleport_probe_execl(path,arg0,end);
#else
    return execl(path,arg0,end);
#endif
}
void teleport_mail_free(void *ptr) { free(ptr); }
void teleport_mail_delay(void) { nh_delay_output(); }
void teleport_mail_display(winid win,boolean blocking) { display_nhwindow(win,blocking); }
void teleport_mail_pline0(const char *format) { pline(format); }
void teleport_mail_pline1(const char *format,const char *arg) { pline(format,arg); }
void teleport_mail_pline_ipi(const char *format,int a,const char *b,int c) { pline(format,a,b,c); }
void teleport_mail_verbalize(const char *format,const char *a,const char *b,const char *c) { verbalize(format,a,b,c); }
int teleport_mail_rn2(int bound,int site)
{
    static const int lines[]={261,340};
    static const char *const callers[]={"md_stop","md_rush"};
    if(rng_log_enabled())rng_log_set_caller("mail.c",lines[site],callers[site]);
    return (rn2)(bound);
}
#ifdef TELEPORT_MAIL_LITERAL_CAPACITY
static char teleport_mail_literals[TELEPORT_MAIL_LITERAL_CAPACITY+sizeof MAILPATH+sizeof DEF_MAILREADER+sizeof "%s"];
void *teleport_mail_literal_storage(void) { return teleport_mail_literals; }
size_t teleport_mail_literal_capacity(void) { return sizeof teleport_mail_literals; }
#endif
