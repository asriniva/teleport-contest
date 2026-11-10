#ifndef TELEPORT_MKOBJ_TYPES_H
#define TELEPORT_MKOBJ_TYPES_H
#include "hack.h"
struct icp {
    int iprob;   /* probability of an item type */
    char iclass; /* item class */
};
enum obj_on_ice {
    NOT_ON_ICE = 0,
    SET_ON_ICE = 1,
    BURIED_UNDER_ICE = 2
};
#endif
