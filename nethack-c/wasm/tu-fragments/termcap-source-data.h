#ifndef TELEPORT_TERMCAP_SOURCE_DATA_H
#define TELEPORT_TERMCAP_SOURCE_DATA_H
#define TERMCAP_LITERAL_CAPACITY 1496
#define TERMCAP_SOURCE_SHA256 "bed864170a5747cf1e04585be62412c498f36ac9f261ac835b8a3df84a763b0e"
#ifdef TELEPORT_REFERENCE_TU
#define TELEPORT_TERMCAP_TI_MAP_TYPE __typeof__(ti_map[0])
#else
struct teleport_termcap_ti_map_entry {int ti_color, nh_color, nh_bright_color;};
#define TELEPORT_TERMCAP_TI_MAP_TYPE struct teleport_termcap_ti_map_entry
#endif
#endif
