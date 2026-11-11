/* Independent optimized fixture consumers: no original UNIXMAIN algorithms. */
#include <pwd.h>
#include <stdint.h>
#include <signal.h>
uint64_t probe_passwd_uid(const struct passwd *p){return p->pw_uid;}
uint64_t probe_passwd_gid(const struct passwd *p){return p->pw_gid;}
char *probe_passwd_string(const struct passwd *p,int i){switch(i){case 0:return p->pw_name;case 1:return p->pw_passwd;case 2:return p->pw_gecos;case 3:return p->pw_dir;case 4:return p->pw_shell;default:return 0;}}
void probe_passwd_set(struct passwd *p,char *name,uint32_t uid,uint32_t gid){p->pw_name=name;p->pw_uid=uid;p->pw_gid=gid;}
uint64_t probe_sigaction_size(void){return sizeof(struct sigaction);}
uint64_t probe_sigaction_flags(const struct sigaction *p){return p->sa_flags;}
