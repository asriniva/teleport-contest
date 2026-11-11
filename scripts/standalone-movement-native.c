/* Original HACK owner; helpers supply inputs or observe source callbacks. */
#include "hack.c"
#include <stdint.h>
uintptr_t probe_movement_callback(int i){switch(i){
#include "movement-callbacks.inc"
}return 0;}
void probe_movement_room(int i,int lx,int hx,int ly,int hy,int type){memset(&svr.rooms[i],0,sizeof svr.rooms[i]);svr.rooms[i].lx=lx;svr.rooms[i].hx=hx;svr.rooms[i].ly=ly;svr.rooms[i].hy=hy;svr.rooms[i].rtype=type;}
void probe_movement_cell(int x,int y,int typ,int room,int edge){levl[x][y].typ=typ;levl[x][y].roomno=room;levl[x][y].edge=edge;}

void probe_movement_update(int newlev){move_update((boolean)newlev);}
