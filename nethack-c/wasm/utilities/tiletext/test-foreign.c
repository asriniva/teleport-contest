/* Separate native consumer of original public mutable tiletext backing. */
#include "config.h"
#include "tile.h"
int utility_tile_foreign_read(int which,int channel,int index){switch(which){case 0:return ColorMap[channel][index];case 1:return MainColorMap[channel][index];case 2:return colorsinmap;case 3:return colorsinmainmap;default:abort();}}
