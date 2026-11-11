/* Observe the pinned SDK's passwd/process boundaries; no game policies. */
#include <pwd.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
static struct passwd *last;
uintptr_t probe_getpwuid(unsigned uid){last=getpwuid(uid);return(uintptr_t)last;}
uintptr_t probe_passwd_text(int i){if(!last)return 0;switch(i){case 0:return(uintptr_t)last->pw_name;case 1:return(uintptr_t)last->pw_passwd;case 2:return(uintptr_t)last->pw_gecos;case 3:return(uintptr_t)last->pw_dir;case 4:return(uintptr_t)last->pw_shell;default:return 0;}}
unsigned probe_passwd_number(int i){return last?(i?last->pw_gid:last->pw_uid):0;}
unsigned long probe_passwd_layout(int i){unsigned long a[]={sizeof(struct passwd),offsetof(struct passwd,pw_name),offsetof(struct passwd,pw_passwd),offsetof(struct passwd,pw_uid),offsetof(struct passwd,pw_gid),offsetof(struct passwd,pw_gecos),offsetof(struct passwd,pw_dir),offsetof(struct passwd,pw_shell),sizeof(uid_t),sizeof(gid_t)};return a[i];}
int probe_errno(int value){int old=errno;errno=value;return old;}
int probe_fork(void){return fork();}
int probe_execl(const char *path){return execl(path,path,(char*)0);}
unsigned probe_getuid(void){return getuid();}
