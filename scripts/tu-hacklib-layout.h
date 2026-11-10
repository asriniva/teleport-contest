/* Native widths and constants only; hacklib algorithms and data remain JavaScript. */
#include "hack.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
struct teleport_hacklib_index { size_t idx; };
_Static_assert(sizeof(void*)==8 && sizeof(size_t)==8 && (size_t)-1>0,"memory64 size_t");
_Static_assert(sizeof(int)==4 && (int)-1<0,"signed int32");
_Static_assert(sizeof(char)==1 && (char)-1<0,"signed char8");
_Static_assert(sizeof(coordxy)==2 && (coordxy)-1<0,"signed coord16");
_Static_assert(sizeof(boolean)==1 && (boolean)-1<0,"signed boolean8");
_Static_assert(sizeof(ssize_t)==8 && (ssize_t)-1<0,"signed ssize64");
#ifdef STRNCMPI
#error Review configured native STRNCMPI replacement
#endif
#ifdef STRSTRI
#error Review configured native STRSTRI replacement
#endif
#ifndef MACOS
#error Review configured copy_bytes RETTYPE
#endif
struct hacklib_meta {const char *name;size_t value;};
#define HACKLIB_META(k,v) {#k,(size_t)(v)}
static const struct hacklib_meta hacklib_layout[]={
HACKLIB_META(pointerSize,sizeof(void*)),HACKLIB_META(sizeSize,sizeof(size_t)),
HACKLIB_META(ssizeSize,sizeof(ssize_t)),HACKLIB_META(intSize,sizeof(int)),
HACKLIB_META(shortSize,sizeof(short)),HACKLIB_META(longSize,sizeof(long)),
HACKLIB_META(longLongSize,sizeof(long long)),HACKLIB_META(charSize,sizeof(char)),
HACKLIB_META(booleanSize,sizeof(boolean)),HACKLIB_META(coordSize,sizeof(coordxy)),
HACKLIB_META(qsortIndexSize,sizeof(struct teleport_hacklib_index)),
HACKLIB_META(qsortIndexIdx,offsetof(struct teleport_hacklib_index,idx)),
HACKLIB_META(qsortIndexIdxSize,sizeof(((struct teleport_hacklib_index*)0)->idx)),
HACKLIB_META(BUFSZ,BUFSZ),HACKLIB_META(BUFSIZ,BUFSIZ),
HACKLIB_META(LARGEST_INT,LARGEST_INT),HACKLIB_META(VISCTRL_NBUF,5),
HACKLIB_META(TABSIZ,0x20),HACKLIB_META(MAX_D,5),
HACKLIB_META(config_MACOS,1),HACKLIB_META(config_STRNCMPI,0),HACKLIB_META(config_STRSTRI,0)
};
size_t probe_context_size(void){return sizeof(struct teleport_hacklib_index);}
size_t probe_layout_count(void){return sizeof hacklib_layout/sizeof hacklib_layout[0];}
const char *probe_layout_name(int i){return hacklib_layout[i].name;}
size_t probe_layout_value(int i){return hacklib_layout[i].value;}
