#ifndef TELEPORT_RESTORE_TYPES_H
#define TELEPORT_RESTORE_TYPES_H
/* ABI-only layout of the original private bucket; original policy stays JS. */
struct teleport_restore_bucket {
    struct teleport_restore_bucket *next;
    struct { unsigned gid; unsigned nid; } map[64];
};
#ifdef TELEPORT_RESTORE_REFERENCE_LAYOUT
_Static_assert(sizeof(struct bucket)==sizeof(struct teleport_restore_bucket),"restore bucket size");
_Static_assert(offsetof(struct bucket,next)==offsetof(struct teleport_restore_bucket,next),"restore bucket next");
_Static_assert(offsetof(struct bucket,map)==offsetof(struct teleport_restore_bucket,map),"restore bucket map");
#endif
#endif
