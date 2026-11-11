/* Inputs and read-only observations around original ENGRAVE/PLINE/TTY. */
#include "allmain.c"
#include <stdio.h>
static int preamble_at_boundary;
void probe_engraving_read_enable_preamble(int enable){preamble_at_boundary=enable;}
void probe_engraving_read_boundary(void){if(preamble_at_boundary)moveloop_preamble(FALSE);}
void probe_engraving_read_preamble(int resuming){moveloop_preamble((boolean)resuming);fflush(stdout);}
void probe_engraving_read_clear(void){clear_nhwindow(WIN_MESSAGE);fflush(stdout);}
void probe_engraving_read_input(int typ,int terrain,int blind,int levitate,
                               int run,int hallucinate,const char *actual,
                               const char *pristine)
{
    del_engr_at(10,10);
    u.ux=10;u.uy=10;u.uswallow=0;u.uundetected=0;u.ustuck=NULL;u.usteed=NULL;
    gy.youmonst.data=&mons[PM_HUMAN];
    HBlinded=blind;EBlinded=BBlinded=0;
    HLevitation=levitate;ELevitation=BLevitation=0;
    HFlying=EFlying=BFlying=0;
    HHallucination=hallucinate;HHalluc_resistance=EHalluc_resistance=0;
    levl[10][10].typ=terrain;levl[10][10].flags=0;
    svc.context.run=run;gm.multi=7;
    if(typ>=0)make_engr_at(10,10,actual,pristine,0L,typ);
}
void probe_engraving_read(void){read_engr_at(10,10);fflush(stdout);}
const void *probe_engraving_read_head(void){return head_engr;}
long probe_engraving_read_scalar(int which)
{
    switch(which){case 0:return svc.context.run;case 1:return gm.multi;
    case 2:return gs.saved_pline_index;case 3:return disp.botl;}
    return -1;
}
const char *probe_engraving_read_message(int index){return gs.saved_plines[index];}
