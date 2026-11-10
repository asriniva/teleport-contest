/* Independent optimized C consumer follows invent.c's `wri_info = zerowri`
 * and configured tty's external status-array accesses. No initial data mirror. */
#include "hack.h"
extern const char*status_fieldnm[MAXBLSTATS];extern const char*status_fieldfmt[MAXBLSTATS];
extern char*status_vals[MAXBLSTATS];extern boolean status_activefields[MAXBLSTATS];
void teleport_windows_consumer_copy(win_request_info*out){*out=zerowri;}
long teleport_windows_consumer_status(int which,int i){switch(which){case 0:return status_activefields[i];case 1:return status_vals[i]?strlen(status_vals[i]):-1;case 2:return status_fieldfmt[i]?strlen(status_fieldfmt[i]):-1;case 3:return status_fieldnm[i]?strlen(status_fieldnm[i]):-1;}return 0;}
