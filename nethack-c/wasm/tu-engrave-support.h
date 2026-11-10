#ifndef TELEPORT_ENGRAVE_SUPPORT_H
#define TELEPORT_ENGRAVE_SUPPORT_H
#include "hack.h"
struct teleport_engrave_context {
    boolean dengr;    /* TRUE if we wipe out the current engraving */
    boolean doblind;  /* TRUE if engraving blinds the player */
    boolean doknown;  /* TRUE if we identify the stylus */
    boolean eow;      /* TRUE if we are overwriting oep */
    boolean jello;    /* TRUE if we are engraving in slime */
    boolean ptext;    /* TRUE if we must prompt for engrave text */
    boolean teleengr; /* TRUE if we move the old engraving */
    boolean zapwand;  /* TRUE if we remove a wand charge */
    boolean disprefresh; /* TRUE if the display needs a refresh */
    boolean frosted;  /* TRUE if engraving on ice */
    boolean adding;   /* TRUE if adding to existing engraving */

    int ret;          /* doengrave return value */
    int type;         /* Type of engraving made */
    int oetype;       /* will be set to type of current engraving */

    struct obj *otmp; /* Object selected with which to engrave */
    struct engr* oep; /* The current engraving */

    char buf[BUFSZ];          /* Buffer for final/poly engraving text */
    char ebuf[BUFSZ];         /* Buffer for initial engraving text */
    char fbuf[BUFSZ];         /* Buffer for "your fingers" */
    char qbuf[QBUFSZ];        /* Buffer for query text */
    char post_engr_text[BUFSZ]; /* Text displayed after engraving prompt */
    char *writer;      /* text of item used for writing */
    const char *everb; /* Present tense of engraving type */
    const char *eloc;  /* Where the engraving is (ie dust/floor/...) */

    size_t len;          /* # of nonspace chars of new engraving text */
};
#endif
