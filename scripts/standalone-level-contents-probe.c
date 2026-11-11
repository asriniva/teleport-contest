/* Connected source trap creation and room query fixtures. */
#include "standalone-level-startup-probe.c"
void *probe_contents_trap(int x,int y,int type){return maketrap((coordxy)x,(coordxy)y,type);}
void *probe_contents_traps(void){return gf.ftrap;}
int probe_contents_room_query(int op,int index,int x,int y){struct mkroom *r=&svr.rooms[index];switch(op){case 0:return has_dnstairs(r);case 1:return has_upstairs(r);case 2:return inside_room(r,(coordxy)x,(coordxy)y);case 3:return somex(r);case 4:return somey(r);}abort();}

#include "tu-trap-layout.h"
unsigned long probe_contents_layout_count(void){return sizeof teleport_trap_layout/sizeof *teleport_trap_layout;}
const char *probe_contents_layout_name(unsigned long i){return teleport_trap_layout[i].name;}
unsigned long probe_contents_layout_value(unsigned long i){return teleport_trap_layout[i].value;}

/* Original Unix main calls this owner before newgame. */
#include "vision.c"
const void *probe_vision_storage(int i){switch(i){case 0:return &could_see;case 1:return &cs_rows0;case 2:return &cs_rows1;case 3:return &cs_rmin0;case 4:return &cs_rmax0;case 5:return &cs_rmin1;case 6:return &cs_rmax1;case 7:return &viz_clear;case 8:return &viz_clear_rows;case 9:return &left_ptrs;case 10:return &right_ptrs;case 11:return &start_row;case 12:return &start_col;case 13:return &step;case 14:return &cs_rows;case 15:return &cs_left;case 16:return &cs_right;case 17:return &vis_func;case 18:return &varg;case 20:return &circle_data;case 21:return &circle_start;}return NULL;}
unsigned long probe_vision_storage_size(int i){switch(i){case 0:return sizeof(could_see);case 1:return sizeof(cs_rows0);case 2:return sizeof(cs_rows1);case 3:return sizeof(cs_rmin0);case 4:return sizeof(cs_rmax0);case 5:return sizeof(cs_rmin1);case 6:return sizeof(cs_rmax1);case 7:return sizeof(viz_clear);case 8:return sizeof(viz_clear_rows);case 9:return sizeof(left_ptrs);case 10:return sizeof(right_ptrs);case 11:return sizeof(start_row);case 12:return sizeof(start_col);case 13:return sizeof(step);case 14:return sizeof(cs_rows);case 15:return sizeof(cs_left);case 16:return sizeof(cs_right);case 17:return sizeof(vis_func);case 18:return sizeof(varg);case 20:return sizeof(circle_data);case 21:return sizeof(circle_start);case 19:return sizeof(coordxy[COLNO+1]);}return 0;}
