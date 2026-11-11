/* Original MDLIB owner alone; these helpers only observe its actual storage. */
#include "mdlib.c"
#include <stdlib.h>

extern struct nomakedefs_s nomakedefs;

const void *probe_runtime_info_storage(int which)
{
    switch (which) {
    case 0: return optbuf;
    case 1: return &version;
    case 2: return save_bones_compat_buf;
    case 3: return opttext;
    default: abort();
    }
}

size_t probe_runtime_info_storage_size(int which)
{
    switch (which) {
    case 0: return sizeof optbuf;
    case 1: return sizeof version;
    case 2: return sizeof save_bones_compat_buf;
    case 3: return sizeof opttext;
    default: abort();
    }
}

int probe_runtime_info_scalar(int which)
{
    switch (which) {
    case 0: return idxopttext;
    case 1: return done_runtime_opt_init_once;
    case 2: return date_via_env;
    case 3: return MAXOPT;
    default: abort();
    }
}

const char *probe_runtime_info_option(int index)
{
    if (index < 0 || index >= MAXOPT)
        abort();
    return opttext[index];
}

const void *probe_runtime_info_nomakedefs(void)
{
    return &nomakedefs;
}

const char *probe_runtime_info_build_date_time(void)
{
    return __DATE__ " " __TIME__;
}

int probe_runtime_info_table_count(int kind)
{
    switch (kind) {
    case 0: return SIZE(artifact_names);
    case 1: return SIZE(build_opts);
    case 2: return SIZE(window_opts);
    case 3: return SIZE(soundlib_opts);
    case 4: return 1; /* The original opt_indent string. */
    default: abort();
    }
}

const char *probe_runtime_info_table_text(int kind, int index, int field)
{
    if (index < 0 || index >= probe_runtime_info_table_count(kind))
        abort();
    switch (kind) {
    case 0: if (!field) return artifact_names[index]; break;
    case 1: if (!field) return build_opts[index]; break;
    case 2:
        if (!field) return window_opts[index].id;
        if (field == 1) return window_opts[index].name;
        break;
    case 3:
        if (!field) return soundlib_opts[index].text_id;
        if (field == 1) return soundlib_opts[index].Url;
        break;
    case 4: if (!field) return opt_indent; break;
    }
    abort();
}

int probe_runtime_info_table_value(int kind, int index, int field)
{
    if (index < 0 || index >= probe_runtime_info_table_count(kind))
        abort();
    if (kind == 2 && !field)
        return window_opts[index].valid;
    if (kind == 3) {
        if (!field) return soundlib_opts[index].id;
        if (field == 1) return soundlib_opts[index].valid;
    }
    abort();
}
