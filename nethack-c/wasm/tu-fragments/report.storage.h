#ifndef TELEPORT_REPORT_STORAGE_H
#define TELEPORT_REPORT_STORAGE_H
/* Zero-only ABI backing for report.c's original private byte arrays. */
struct teleport_report_storage {
    char bid[40];
    char url[8192];
};
#endif
