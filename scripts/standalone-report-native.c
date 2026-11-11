/* Actual REPORT owner alone; observers expose original private byte arrays. */
#include "report.c"
#include <stdlib.h>
const void *probe_report_storage(int index)
{
    switch (index) {
    case 0: return bid;
    case 1: return url;
    default: abort();
    }
}
size_t probe_report_storage_size(int index)
{
    switch (index) {
    case 0: return sizeof bid;
    case 1: return sizeof url;
    default: abort();
    }
}
