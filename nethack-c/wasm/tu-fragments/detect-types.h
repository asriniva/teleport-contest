#ifndef TELEPORT_DETECT_TYPES_H
#define TELEPORT_DETECT_TYPES_H
#include "hack.h"
struct crystalballlevels {const char*what;d_level*where;};
struct found_things {
    coord ft_cc; /* for passing extra info to detect_obj_traps() */
    uchar num_sdoors;
    uchar num_scorrs;
    uchar num_traps;
    uchar num_mons;
    uchar num_invis;
    uchar num_cleared_invis;
    uchar num_kept_invis;
};
#endif
