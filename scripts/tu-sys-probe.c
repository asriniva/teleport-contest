#include "hack.h"
#include <stddef.h>
#include <stdlib.h>

__typeof__(gc) gc;
void panic(const char *format, ...) { abort(); }

/* Descriptor metadata comes from the same configured C headers as the game. */
struct field { const char *name; size_t offset, size; int kind; };
#define FIELD(name, kind) { #name, offsetof(struct sysopt_s, name), sizeof(sysopt.name), kind }
static const struct field fields[] = {
    FIELD(support, 0), FIELD(recover, 0), FIELD(wizards, 0),
    FIELD(fmtd_wizard_list, 0), FIELD(explorers, 0), FIELD(shellers, 0),
    FIELD(genericusers, 0), FIELD(debugfiles, 0), FIELD(msghandler, 0),
#ifdef DUMPLOG
    FIELD(dumplogfile, 0),
#endif
    FIELD(env_dbgfl, 1), FIELD(maxplayers, 1), FIELD(seduce, 1),
    FIELD(check_save_uid, 1), FIELD(check_plname, 1), FIELD(bones_pools, 1),
    FIELD(livelog, 2), FIELD(persmax, 1), FIELD(pers_is_uid, 1),
    FIELD(entrymax, 1), FIELD(pointsmin, 1), FIELD(tt_oname_maxrank, 1),
    FIELD(gdbpath, 0), FIELD(greppath, 0), FIELD(crashreporturl, 0),
    FIELD(panictrace_gdb, 1), FIELD(panictrace_libc, 1),
    FIELD(saveformat, 3), FIELD(bonesformat, 3), FIELD(accessibility, 1),
#ifdef WIN32
    FIELD(portable_device_paths, 1),
#endif
    FIELD(hideusage, 1)
};
static const struct field gcfields[] = {
#ifdef CRASHREPORT
    { "crash_email", offsetof(__typeof__(gc), crash_email), sizeof(gc.crash_email), 0 },
    { "crash_name", offsetof(__typeof__(gc), crash_name), sizeof(gc.crash_name), 0 },
#endif
    { NULL, 0, 0, 0 }
};
struct constant { const char *name; int value; };
static const struct constant constants[] = {
#ifdef SYSCF
    { "SYSCF", 1 },
#else
    { "SYSCF", 0 },
#endif
#ifdef DEBUGFILES
    { "DEBUGFILES_DEFINED", 1 },
#else
    { "DEBUGFILES_DEFINED", 0 },
#endif
#ifdef DUMPLOG
    { "DUMPLOG", 1 },
#else
    { "DUMPLOG", 0 },
#endif
#ifdef PANICTRACE
    { "PANICTRACE", 1 },
#else
    { "PANICTRACE", 0 },
#endif
#ifdef PANICTRACE_LIBC
    { "PANICTRACE_LIBC", 1 },
#else
    { "PANICTRACE_LIBC", 0 },
#endif
#ifdef WIN32
    { "WIN32", 1 },
#else
    { "WIN32", 0 },
#endif
#ifdef CRASHREPORT
    { "CRASHREPORT", 1 },
#else
    { "CRASHREPORT", 0 },
#endif
    { "NH_DEVEL_STATUS", NH_DEVEL_STATUS }, { "NH_STATUS_RELEASED", NH_STATUS_RELEASED },
    { "PERSMAX", PERSMAX }, { "ENTRYMAX", ENTRYMAX }, { "POINTSMIN", POINTSMIN },
    { "PERS_IS_UID", PERS_IS_UID }, { "historical", historical }
};
struct string_constant { const char *name, *value; };
static const struct string_constant strings[] = {
#ifdef WIZARD_NAME
    { "WIZARD_NAME", WIZARD_NAME },
#else
    { "WIZARD_NAME", NULL },
#endif
#ifdef DEBUGFILES
    { "DEBUGFILES", DEBUGFILES },
#else
    { "DEBUGFILES", NULL },
#endif
#ifdef GDBPATH
    { "GDBPATH", GDBPATH },
#else
    { "GDBPATH", NULL },
#endif
#ifdef GREPPATH
    { "GREPPATH", GREPPATH }
#else
    { "GREPPATH", NULL }
#endif
};
size_t probe_context_size(void) { return sizeof sysopt; }
int probe_field_count(void) { return SIZE(fields); }
const char *probe_field_name(int i) { return fields[i].name; }
size_t probe_field_offset(int i) { return fields[i].offset; }
size_t probe_field_size(int i) { return fields[i].size; }
int probe_field_kind(int i) { return fields[i].kind; }
int probe_gc_field_count(void) { return SIZE(gcfields) - 1; }
const char *probe_gc_field_name(int i) { return gcfields[i].name; }
size_t probe_gc_field_offset(int i) { return gcfields[i].offset; }
size_t probe_gc_field_size(int i) { return gcfields[i].size; }
int probe_config_count(void) { return SIZE(constants); }
const char *probe_config_name(int i) { return constants[i].name; }
int probe_config_value(int i) { return constants[i].value; }
int probe_string_count(void) { return SIZE(strings); }
const char *probe_string_name(int i) { return strings[i].name; }
const char *probe_string_value(int i) { return strings[i].value; }
long probe_ll_none(void) { return LL_NONE; }
int probe_int_size(void) { return sizeof(int); }
void *probe_sys_pointer(void) { return &sysopt; }
void *probe_gc_pointer(void) { return &gc; }
void probe_init(void) { sys_early_init(); }
void probe_release(void) { sysopt_release(); }
void probe_seduce(int value) { sysopt_seduce_set(value); }
void probe_env(const char *value)
{
    if (value) setenv("DEBUGFILES", value, 1); else unsetenv("DEBUGFILES");
}
void probe_populate(int seed)
{
    int i, j;
    /* Existing source initialization intentionally orphans some pointers.
     * This bounded, short-lived test process accepts those same leaks rather
     * than adding cleanup behavior that could mask a port discrepancy. */
    sysopt_release();
    memset(&sysopt, 0, sizeof sysopt);
    for (i = 0; i < SIZE(fields); i++) {
        char *p = (char *) &sysopt + fields[i].offset;
        switch (fields[i].kind) {
        case 0: *(char **) p = dupstr(fields[i].name); break;
        case 1: *(int *) p = -1000 - seed - i; break;
        case 2: *(long *) p = -123456789012345L - seed; break;
        case 3:
            for (j = 0; j < fields[i].size / sizeof(int); j++)
                ((int *) p)[j] = -2000 - seed - 10 * i - j;
            break;
        }
    }
    for (i = 0; i < SIZE(gcfields) - 1; i++)
        *(char **) ((char *) &gc + gcfields[i].offset) = dupstr(gcfields[i].name);
}
