#include "hack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>

void panic(const char *format, ...) { abort(); }
struct field { const char *name; size_t offset, size; int kind; };
#define FIELD(name, kind) { #name, offsetof(struct nomakedefs_s, name), sizeof(nomakedefs.name), kind }
static const struct field fields[] = {
    FIELD(build_date, 0), FIELD(copyright_banner_c, 0), FIELD(git_sha, 0),
    FIELD(git_branch, 0), FIELD(git_prefix, 0), FIELD(version_string, 0), FIELD(version_id, 0),
    FIELD(version_number, 1), FIELD(version_features, 1), FIELD(ignored_features, 1),
    FIELD(version_sanity1, 1), FIELD(build_time, 1)
};
static struct version_info fixture_version;
static unsigned long fixture_ignored;
static char helper_text[BUFSZ], trace[4096];

/* These external version-string builders are controlled identically for C
 * and JS probes. The game continues to use its real native implementations. */
unsigned long md_ignored_features(void)
{
    strcat(trace, "ignored;"); return fixture_ignored;
}
char *mdlib_version_string(char *buffer, const char *delimiter)
{
    snprintf(trace + strlen(trace), sizeof(trace) - strlen(trace), "version:%s;", delimiter);
    snprintf(buffer, BUFSZ, "v%s%s", delimiter, helper_text); return buffer;
}
char *version_id_string(char *buffer, size_t size, const char *date)
{
    snprintf(trace + strlen(trace), sizeof(trace) - strlen(trace), "id:%zu:%s;", size, date);
    snprintf(buffer, size, "id[%s]:%s", date, helper_text); return buffer;
}
char *bannerc_string(char *buffer, size_t size, const char *date)
{
    snprintf(trace + strlen(trace), sizeof(trace) - strlen(trace), "banner:%zu:%s;", size, date);
    snprintf(buffer, size, "banner[%s]:%s", date, helper_text); return buffer;
}
size_t probe_context_size(void) { return sizeof(nomakedefs); }
int probe_field_count(void) { return SIZE(fields); }
const char *probe_field_name(int i) { return fields[i].name; }
size_t probe_field_offset(int i) { return fields[i].offset; }
size_t probe_field_size(int i) { return fields[i].size; }
int probe_field_kind(int i) { return fields[i].kind; }
size_t probe_version_size(void) { return sizeof(struct version_info); }
size_t probe_offset_incarnation(void) { return offsetof(struct version_info, incarnation); }
size_t probe_offset_feature_set(void) { return offsetof(struct version_info, feature_set); }
size_t probe_offset_entity_count(void) { return offsetof(struct version_info, entity_count); }
int probe_int_size(void) { return sizeof(int); }
int probe_long_size(void) { return sizeof(long); }
int probe_time_size(void) { return sizeof(time_t); }
int probe_bufsz(void) { return BUFSZ; }
const char *probe_build_date_time(void) { return __DATE__ " " __TIME__; }
const char *probe_git_sha(void) {
#ifdef NETHACK_GIT_SHA
    return NETHACK_GIT_SHA;
#else
    return NULL;
#endif
}
const char *probe_git_branch(void) {
#ifdef NETHACK_GIT_BRANCH
    return NETHACK_GIT_BRANCH;
#else
    return NULL;
#endif
}
const char *probe_git_prefix(void) {
#ifdef NETHACK_GIT_PREFIX
    return NETHACK_GIT_PREFIX;
#else
    return NULL;
#endif
}
void *probe_pointer(void) { return &nomakedefs; }
int probe_env(const char *name, const char *value)
{
    return value ? setenv(name, value, 1) : unsetenv(name);
}
void probe_inputs(unsigned long incarnation, unsigned long features,
                  unsigned long entities, unsigned long ignored, const char *text)
{
    fixture_version.incarnation = incarnation;
    fixture_version.feature_set = features;
    fixture_version.entity_count = entities;
    fixture_ignored = ignored;
    strncpy(helper_text, text, sizeof(helper_text) - 1);
    helper_text[sizeof(helper_text) - 1] = '\0';
}
void probe_populate(void)
{
    trace[0] = '\0';
    populate_nomakedefs(&fixture_version);
}
void probe_release(void) { free_nomakedefs(); }
const char *probe_trace(void) { return trace; }
size_t probe_stack(void) { return emscripten_stack_get_current(); }
