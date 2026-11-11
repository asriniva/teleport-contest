/* Original WORM alone, exposing observation/fixture inputs, never policy. */
#include "worm.c"
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>

const void *probe_worm_segment(int head, int slot)
{ if(slot<0||slot>=MAX_NUM_WORMS)abort();return head?wheads[slot]:wtails[slot]; }
long probe_worm_time(int slot)
{ if(slot<0||slot>=MAX_NUM_WORMS)abort();return wgrowtime[slot]; }
void probe_worm_set_time(int slot,long value)
{ if(slot<0||slot>=MAX_NUM_WORMS)abort();wgrowtime[slot]=value; }
/* Source construction uses original MAKEMON and all its real dependencies. */
struct monst *probe_worm_create(void)
{ return makemon(&mons[PM_LONG_WORM],0,0,MM_NOMSG); }
static NHFILE worm_file;
static int worm_open,worm_input;
NHFILE *probe_worm_file(int mode,int input)
{
 if(worm_open)abort();
 memset(&worm_file,0,sizeof worm_file);
 worm_file.mode=mode;worm_file.structlevel=TRUE;worm_file.fnidx=historical;
 worm_file.fd=open("/worm-save",input?O_RDONLY:(O_WRONLY|O_CREAT|O_TRUNC),0600);
 if(worm_file.fd<0)abort();worm_open=1;worm_input=input;
 return &worm_file;
}
void probe_worm_file_close(void)
{ if(worm_open){if(worm_input)close(worm_file.fd);else bclose(worm_file.fd);worm_open=0;} }
void probe_worm_move_head(struct monst *mon,coordxy x,coordxy y)
{ remove_monster(mon->mx,mon->my);place_monster(mon,x,y); }
