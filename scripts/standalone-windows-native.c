/* Include this original owner alone, retaining its translation-unit macros. */
#include "windows.c"
#include <stdint.h>
uintptr_t probe_windows_callback(int i){switch(i){
#include "windows-callbacks.inc"
}return 0;}
const volatile void *probe_windows_storage(int i){switch(i){case 0:return &windowprocs;case 1:return winchoices;case 2:return &hup_procs;case 3:return &dumplog_windowprocs_backup;case 4:return &zerowri;case 6:return status_fieldnm;case 7:return status_fieldfmt;case 8:return status_vals;case 9:return status_activefields;}return NULL;}
