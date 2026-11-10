/* Zero-only VISION circle backing, compiled separately from every reader.
 * JavaScript owns both initializers; no LTO. */
#include "hack.h"
#ifdef TELEPORT_PORT_VISION_STORAGE
const coordxy circle_data[137];
const coordxy circle_start[16];
#endif
