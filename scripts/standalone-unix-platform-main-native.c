/* Rename only the original platform entry, preserving its complete body. */
#define main probe_unix_platform_main
#define getlock probe_unix_platform_getlock_observer
#include "unixmain.c"
#undef main
#undef getlock
#include <setjmp.h>
static jmp_buf platform_lock_boundary;
static int observing_platform_lock;
extern void getlock(void);
void probe_unix_platform_getlock_observer(void)
{
 getlock();
 if(observing_platform_lock)longjmp(platform_lock_boundary,1);
}
int probe_unix_platform_through_lock(int argc,char **argv)
{
 int observed=setjmp(platform_lock_boundary);
 if(observed){observing_platform_lock=0;return observed;}
 observing_platform_lock=1;
 probe_unix_platform_main(argc,argv);
 observing_platform_lock=0;
 return 0;
}
