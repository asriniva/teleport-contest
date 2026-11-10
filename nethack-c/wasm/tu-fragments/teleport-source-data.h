/* Source-derived TELEPORT storage dimensions and actual configured ABI. */
#ifndef TELEPORT_TELEPORT_SOURCE_DATA_H
#define TELEPORT_TELEPORT_SOURCE_DATA_H
#define TELEPORT_SOURCE_FILE "teleport.c"
_Static_assert(ROWNO==21&&COLNO==80,"TELEPORT full-map buffer dimensions changed");
_Static_assert(sizeof(coordxy)==2&&sizeof(boolean)==1&&sizeof(mmflags_nht)==4,"TELEPORT configured scalar width changed");
_Static_assert(sizeof(coord)==2*sizeof(coordxy),"TELEPORT coordinate padding changed");
_Static_assert(sizeof u.urooms==5,"TELEPORT room snapshot buffer changed");
_Static_assert((char)-1<0,"TELEPORT char signedness changed");
_Static_assert(sizeof(long)==8&&sizeof(unsigned long)==8,"TELEPORT configured long width changed");
_Static_assert(sizeof(((struct trap*)0)->teledest)==sizeof(coord),"TELEPORT destination coordinate binding changed");
_Static_assert(offsetof(struct trap,teledest)==offsetof(struct trap,launch),"TELEPORT teledest macro no longer aliases launch");
_Static_assert(offsetof(struct objclass,oc_level)==offsetof(struct objclass,oc_oc2),"TELEPORT spell level macro alias changed");
#endif
