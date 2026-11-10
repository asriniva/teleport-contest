/* Typed mirror of configured private source record; no algorithms/data values. */
#ifndef TELEPORT_TOPTEN_TYPES_H
#define TELEPORT_TOPTEN_TYPES_H
struct teleport_toptenentry {
    struct teleport_toptenentry *tt_next;
    long points;
    int deathdnum, deathlev;
    int maxlvl, hp, maxhp, deaths;
    int ver_major, ver_minor, patchlevel;
    long deathdate, birthdate;
    int uid;
    char plrole[4],plrace[4],plgend[4],plalign[4],name[11],death[101];
};
#endif
