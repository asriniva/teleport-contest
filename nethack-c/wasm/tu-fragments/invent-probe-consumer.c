/* Independent optimized foreign WINDOWS state. Fixture only, no INVENT policies. */
#include "hack.h"
win_request_info zerowri;
void invent_foreign_wri(long flags,int marker){memset(&zerowri,marker,sizeof zerowri);zerowri.tocore.tocore_flags=flags;}
void invent_foreign_copy(unsigned char*out){memcpy(out,&zerowri,sizeof zerowri);}
