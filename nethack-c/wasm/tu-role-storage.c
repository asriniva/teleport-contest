/* Zero-only ROLE backing, deliberately separate from all native readers.
 * JavaScript owns the original catalogue initializers. No LTO is used.
 */
#include "hack.h"
#ifdef TELEPORT_PORT_ROLE_STORAGE
const struct Role roles[NUM_ROLES + 1];
const struct Race races[NUM_RACES + 1];
const struct Gender genders[4];
const struct Align aligns[4];
#endif
