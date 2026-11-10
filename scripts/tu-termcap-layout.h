#ifndef TELEPORT_TERMCAP_LAYOUT_H
#define TELEPORT_TERMCAP_LAYOUT_H
#include "hack.h"
#include "wintty.h"
#include "tcap.h"
#include <stdint.h>
#include <stddef.h>
#include "../nethack-c/wasm/tu-fragments/termcap-source-data.h"
#ifdef SFCTOOL
#error Review changed TERMCAP configured profile
#endif
struct termcap_meta {const char*name;uint64_t value;};
#define TERMCAP_META(k,v) {#k,(uint64_t)(v)}
static const struct termcap_meta termcap_layout[]={
TERMCAP_META(pointerSize,sizeof(void*)),TERMCAP_META(longSize,sizeof(long)),TERMCAP_META(intSize,sizeof(int)),TERMCAP_META(charSigned,((char)-1<0)),TERMCAP_META(littleEndian,__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__),
TERMCAP_META(ATR_BLINK,ATR_BLINK),
TERMCAP_META(constwidth_ATR_BLINK,sizeof(ATR_BLINK)),
TERMCAP_META(constsigned_ATR_BLINK,((__typeof__(ATR_BLINK))-1)<0),
TERMCAP_META(ATR_BOLD,ATR_BOLD),
TERMCAP_META(constwidth_ATR_BOLD,sizeof(ATR_BOLD)),
TERMCAP_META(constsigned_ATR_BOLD,((__typeof__(ATR_BOLD))-1)<0),
TERMCAP_META(ATR_DIM,ATR_DIM),
TERMCAP_META(constwidth_ATR_DIM,sizeof(ATR_DIM)),
TERMCAP_META(constsigned_ATR_DIM,((__typeof__(ATR_DIM))-1)<0),
TERMCAP_META(ATR_INVERSE,ATR_INVERSE),
TERMCAP_META(constwidth_ATR_INVERSE,sizeof(ATR_INVERSE)),
TERMCAP_META(constsigned_ATR_INVERSE,((__typeof__(ATR_INVERSE))-1)<0),
TERMCAP_META(ATR_ITALIC,ATR_ITALIC),
TERMCAP_META(constwidth_ATR_ITALIC,sizeof(ATR_ITALIC)),
TERMCAP_META(constsigned_ATR_ITALIC,((__typeof__(ATR_ITALIC))-1)<0),
TERMCAP_META(ATR_ULINE,ATR_ULINE),
TERMCAP_META(constwidth_ATR_ULINE,sizeof(ATR_ULINE)),
TERMCAP_META(constsigned_ATR_ULINE,((__typeof__(ATR_ULINE))-1)<0),
TERMCAP_META(BRIGHT,BRIGHT),
TERMCAP_META(constwidth_BRIGHT,sizeof(BRIGHT)),
TERMCAP_META(constsigned_BRIGHT,((__typeof__(BRIGHT))-1)<0),
TERMCAP_META(BUFSZ,BUFSZ),
TERMCAP_META(constwidth_BUFSZ,sizeof(BUFSZ)),
TERMCAP_META(constsigned_BUFSZ,((__typeof__(BUFSZ))-1)<0),
TERMCAP_META(CLR_BLACK,CLR_BLACK),
TERMCAP_META(constwidth_CLR_BLACK,sizeof(CLR_BLACK)),
TERMCAP_META(constsigned_CLR_BLACK,((__typeof__(CLR_BLACK))-1)<0),
TERMCAP_META(CLR_BLUE,CLR_BLUE),
TERMCAP_META(constwidth_CLR_BLUE,sizeof(CLR_BLUE)),
TERMCAP_META(constsigned_CLR_BLUE,((__typeof__(CLR_BLUE))-1)<0),
TERMCAP_META(CLR_BRIGHT_BLUE,CLR_BRIGHT_BLUE),
TERMCAP_META(constwidth_CLR_BRIGHT_BLUE,sizeof(CLR_BRIGHT_BLUE)),
TERMCAP_META(constsigned_CLR_BRIGHT_BLUE,((__typeof__(CLR_BRIGHT_BLUE))-1)<0),
TERMCAP_META(CLR_BRIGHT_CYAN,CLR_BRIGHT_CYAN),
TERMCAP_META(constwidth_CLR_BRIGHT_CYAN,sizeof(CLR_BRIGHT_CYAN)),
TERMCAP_META(constsigned_CLR_BRIGHT_CYAN,((__typeof__(CLR_BRIGHT_CYAN))-1)<0),
TERMCAP_META(CLR_BRIGHT_GREEN,CLR_BRIGHT_GREEN),
TERMCAP_META(constwidth_CLR_BRIGHT_GREEN,sizeof(CLR_BRIGHT_GREEN)),
TERMCAP_META(constsigned_CLR_BRIGHT_GREEN,((__typeof__(CLR_BRIGHT_GREEN))-1)<0),
TERMCAP_META(CLR_BRIGHT_MAGENTA,CLR_BRIGHT_MAGENTA),
TERMCAP_META(constwidth_CLR_BRIGHT_MAGENTA,sizeof(CLR_BRIGHT_MAGENTA)),
TERMCAP_META(constsigned_CLR_BRIGHT_MAGENTA,((__typeof__(CLR_BRIGHT_MAGENTA))-1)<0),
TERMCAP_META(CLR_BROWN,CLR_BROWN),
TERMCAP_META(constwidth_CLR_BROWN,sizeof(CLR_BROWN)),
TERMCAP_META(constsigned_CLR_BROWN,((__typeof__(CLR_BROWN))-1)<0),
TERMCAP_META(CLR_CYAN,CLR_CYAN),
TERMCAP_META(constwidth_CLR_CYAN,sizeof(CLR_CYAN)),
TERMCAP_META(constsigned_CLR_CYAN,((__typeof__(CLR_CYAN))-1)<0),
TERMCAP_META(CLR_GRAY,CLR_GRAY),
TERMCAP_META(constwidth_CLR_GRAY,sizeof(CLR_GRAY)),
TERMCAP_META(constsigned_CLR_GRAY,((__typeof__(CLR_GRAY))-1)<0),
TERMCAP_META(CLR_GREEN,CLR_GREEN),
TERMCAP_META(constwidth_CLR_GREEN,sizeof(CLR_GREEN)),
TERMCAP_META(constsigned_CLR_GREEN,((__typeof__(CLR_GREEN))-1)<0),
TERMCAP_META(CLR_MAGENTA,CLR_MAGENTA),
TERMCAP_META(constwidth_CLR_MAGENTA,sizeof(CLR_MAGENTA)),
TERMCAP_META(constsigned_CLR_MAGENTA,((__typeof__(CLR_MAGENTA))-1)<0),
TERMCAP_META(CLR_MAX,CLR_MAX),
TERMCAP_META(constwidth_CLR_MAX,sizeof(CLR_MAX)),
TERMCAP_META(constsigned_CLR_MAX,((__typeof__(CLR_MAX))-1)<0),
TERMCAP_META(CLR_ORANGE,CLR_ORANGE),
TERMCAP_META(constwidth_CLR_ORANGE,sizeof(CLR_ORANGE)),
TERMCAP_META(constsigned_CLR_ORANGE,((__typeof__(CLR_ORANGE))-1)<0),
TERMCAP_META(CLR_RED,CLR_RED),
TERMCAP_META(constwidth_CLR_RED,sizeof(CLR_RED)),
TERMCAP_META(constsigned_CLR_RED,((__typeof__(CLR_RED))-1)<0),
TERMCAP_META(CLR_WHITE,CLR_WHITE),
TERMCAP_META(constwidth_CLR_WHITE,sizeof(CLR_WHITE)),
TERMCAP_META(constsigned_CLR_WHITE,((__typeof__(CLR_WHITE))-1)<0),
TERMCAP_META(CLR_YELLOW,CLR_YELLOW),
TERMCAP_META(constwidth_CLR_YELLOW,sizeof(CLR_YELLOW)),
TERMCAP_META(constsigned_CLR_YELLOW,((__typeof__(CLR_YELLOW))-1)<0),
TERMCAP_META(COLNO,COLNO),
TERMCAP_META(constwidth_COLNO,sizeof(COLNO)),
TERMCAP_META(constsigned_COLNO,((__typeof__(COLNO))-1)<0),
TERMCAP_META(COLOR_BLACK,COLOR_BLACK),
TERMCAP_META(constwidth_COLOR_BLACK,sizeof(COLOR_BLACK)),
TERMCAP_META(constsigned_COLOR_BLACK,((__typeof__(COLOR_BLACK))-1)<0),
TERMCAP_META(COLOR_BLUE,COLOR_BLUE),
TERMCAP_META(constwidth_COLOR_BLUE,sizeof(COLOR_BLUE)),
TERMCAP_META(constsigned_COLOR_BLUE,((__typeof__(COLOR_BLUE))-1)<0),
TERMCAP_META(COLOR_CYAN,COLOR_CYAN),
TERMCAP_META(constwidth_COLOR_CYAN,sizeof(COLOR_CYAN)),
TERMCAP_META(constsigned_COLOR_CYAN,((__typeof__(COLOR_CYAN))-1)<0),
TERMCAP_META(COLOR_GREEN,COLOR_GREEN),
TERMCAP_META(constwidth_COLOR_GREEN,sizeof(COLOR_GREEN)),
TERMCAP_META(constsigned_COLOR_GREEN,((__typeof__(COLOR_GREEN))-1)<0),
TERMCAP_META(COLOR_MAGENTA,COLOR_MAGENTA),
TERMCAP_META(constwidth_COLOR_MAGENTA,sizeof(COLOR_MAGENTA)),
TERMCAP_META(constsigned_COLOR_MAGENTA,((__typeof__(COLOR_MAGENTA))-1)<0),
TERMCAP_META(COLOR_RED,COLOR_RED),
TERMCAP_META(constwidth_COLOR_RED,sizeof(COLOR_RED)),
TERMCAP_META(constsigned_COLOR_RED,((__typeof__(COLOR_RED))-1)<0),
TERMCAP_META(COLOR_WHITE,COLOR_WHITE),
TERMCAP_META(constwidth_COLOR_WHITE,sizeof(COLOR_WHITE)),
TERMCAP_META(constsigned_COLOR_WHITE,((__typeof__(COLOR_WHITE))-1)<0),
TERMCAP_META(COLOR_YELLOW,COLOR_YELLOW),
TERMCAP_META(constwidth_COLOR_YELLOW,sizeof(COLOR_YELLOW)),
TERMCAP_META(constsigned_COLOR_YELLOW,((__typeof__(COLOR_YELLOW))-1)<0),
TERMCAP_META(HL_BLINK,HL_BLINK),
TERMCAP_META(constwidth_HL_BLINK,sizeof(HL_BLINK)),
TERMCAP_META(constsigned_HL_BLINK,((__typeof__(HL_BLINK))-1)<0),
TERMCAP_META(HL_BOLD,HL_BOLD),
TERMCAP_META(constwidth_HL_BOLD,sizeof(HL_BOLD)),
TERMCAP_META(constsigned_HL_BOLD,((__typeof__(HL_BOLD))-1)<0),
TERMCAP_META(HL_DIM,HL_DIM),
TERMCAP_META(constwidth_HL_DIM,sizeof(HL_DIM)),
TERMCAP_META(constsigned_HL_DIM,((__typeof__(HL_DIM))-1)<0),
TERMCAP_META(HL_ULINE,HL_ULINE),
TERMCAP_META(constwidth_HL_ULINE,sizeof(HL_ULINE)),
TERMCAP_META(constsigned_HL_ULINE,((__typeof__(HL_ULINE))-1)<0),
TERMCAP_META(H_DEC,H_DEC),
TERMCAP_META(constwidth_H_DEC,sizeof(H_DEC)),
TERMCAP_META(constsigned_H_DEC,((__typeof__(H_DEC))-1)<0),
TERMCAP_META(LONG_MAX,LONG_MAX),
TERMCAP_META(constwidth_LONG_MAX,sizeof(LONG_MAX)),
TERMCAP_META(constsigned_LONG_MAX,((__typeof__(LONG_MAX))-1)<0),
TERMCAP_META(NO_COLOR,NO_COLOR),
TERMCAP_META(constwidth_NO_COLOR,sizeof(NO_COLOR)),
TERMCAP_META(constsigned_NO_COLOR,((__typeof__(NO_COLOR))-1)<0),
TERMCAP_META(QBUFSZ,QBUFSZ),
TERMCAP_META(constwidth_QBUFSZ,sizeof(QBUFSZ)),
TERMCAP_META(constsigned_QBUFSZ,((__typeof__(QBUFSZ))-1)<0),
TERMCAP_META(ROWNO,ROWNO),
TERMCAP_META(constwidth_ROWNO,sizeof(ROWNO)),
TERMCAP_META(constsigned_ROWNO,((__typeof__(ROWNO))-1)<0),
TERMCAP_META(flagSize,sizeof(struct flag)),
TERMCAP_META(width_flag_null,sizeof(((struct flag*)0)->null)),
TERMCAP_META(width_flag_silent,sizeof(((struct flag*)0)->silent)),
TERMCAP_META(tc_gbl_dataSize,sizeof(struct tc_gbl_data)),
TERMCAP_META(width_tc_gbl_data_tc_CO,sizeof(((struct tc_gbl_data*)0)->tc_CO)),
TERMCAP_META(width_tc_gbl_data_tc_LI,sizeof(((struct tc_gbl_data*)0)->tc_LI)),
TERMCAP_META(width_tc_gbl_data_tc_AS,sizeof(((struct tc_gbl_data*)0)->tc_AS)),
TERMCAP_META(width_tc_gbl_data_tc_AE,sizeof(((struct tc_gbl_data*)0)->tc_AE)),
TERMCAP_META(instance_globals_tSize,sizeof(struct instance_globals_t)),
TERMCAP_META(width_instance_globals_t_tc_gbl_data,sizeof(((struct instance_globals_t*)0)->tc_gbl_data)),
TERMCAP_META(tc_lcl_dataSize,sizeof(struct tc_lcl_data)),
TERMCAP_META(width_tc_lcl_data_tc_ND,sizeof(((struct tc_lcl_data*)0)->tc_ND)),
TERMCAP_META(width_tc_lcl_data_tc_ul_hack,sizeof(((struct tc_lcl_data*)0)->tc_ul_hack)),
TERMCAP_META(width_tc_lcl_data_tc_CM,sizeof(((struct tc_lcl_data*)0)->tc_CM)),
TERMCAP_META(width_tc_lcl_data_tc_US,sizeof(((struct tc_lcl_data*)0)->tc_US)),
TERMCAP_META(width_tc_lcl_data_tc_UE,sizeof(((struct tc_lcl_data*)0)->tc_UE)),
TERMCAP_META(width_tc_lcl_data_tc_HI,sizeof(((struct tc_lcl_data*)0)->tc_HI)),
TERMCAP_META(width_tc_lcl_data_tc_HE,sizeof(((struct tc_lcl_data*)0)->tc_HE)),
TERMCAP_META(width_tc_lcl_data_tc_CD,sizeof(((struct tc_lcl_data*)0)->tc_CD)),
TERMCAP_META(symsetentrySize,sizeof(struct symsetentry)),
TERMCAP_META(width_symsetentry_handling,sizeof(((struct symsetentry*)0)->handling)),
TERMCAP_META(instance_globals_sSize,sizeof(struct instance_globals_s)),
TERMCAP_META(width_instance_globals_s_symset,sizeof(((struct instance_globals_s*)0)->symset)),
TERMCAP_META(instance_globals_cSize,sizeof(struct instance_globals_c)),
TERMCAP_META(width_instance_globals_c_currentgraphics,sizeof(((struct instance_globals_c*)0)->currentgraphics)),
TERMCAP_META(width_instance_globals_c_Cmd,sizeof(((struct instance_globals_c*)0)->Cmd)),
TERMCAP_META(cmdSize,sizeof(struct cmd)),
TERMCAP_META(width_cmd_num_pad,sizeof(((struct cmd*)0)->num_pad)),
TERMCAP_META(DisplayDescSize,sizeof(struct DisplayDesc)),
TERMCAP_META(width_DisplayDesc_cury,sizeof(((struct DisplayDesc*)0)->cury)),
TERMCAP_META(width_DisplayDesc_curx,sizeof(((struct DisplayDesc*)0)->curx)),
TERMCAP_META(nomux_cellSize,sizeof(nomux_cell)),
TERMCAP_META(width_nomux_cell_ch,sizeof(((nomux_cell*)0)->ch)),
TERMCAP_META(width_nomux_cell_fg,sizeof(((nomux_cell*)0)->fg)),
TERMCAP_META(width_nomux_cell_attr,sizeof(((nomux_cell*)0)->attr)),
TERMCAP_META(width_nomux_cell_decgfx,sizeof(((nomux_cell*)0)->decgfx)),
TERMCAP_META(instance_flagsSize,sizeof(struct instance_flags)),
TERMCAP_META(width_instance_flags_wc2_darkgray,sizeof(((struct instance_flags*)0)->wc2_darkgray)),
TERMCAP_META(width_instance_flags_debug_fuzzer,sizeof(((struct instance_flags*)0)->debug_fuzzer)),
TERMCAP_META(width_instance_flags_colorcount,sizeof(((struct instance_flags*)0)->colorcount)),
TERMCAP_META(ti_map_entrySize,sizeof(TELEPORT_TERMCAP_TI_MAP_TYPE)),
TERMCAP_META(width_ti_map_entry_nh_color,sizeof(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->nh_color)),
TERMCAP_META(width_ti_map_entry_nh_bright_color,sizeof(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->nh_bright_color)),
TERMCAP_META(width_ti_map_entry_ti_color,sizeof(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->ti_color)),
};
#undef TERMCAP_META
_Static_assert(sizeof(((struct flag*)0)->null)==1,"TERMCAP flag.null width");
_Static_assert((((__typeof__(((struct flag*)0)->null))-1)<0)==1,"TERMCAP flag.null sign");
_Static_assert(sizeof(((struct flag*)0)->silent)==1,"TERMCAP flag.silent width");
_Static_assert((((__typeof__(((struct flag*)0)->silent))-1)<0)==1,"TERMCAP flag.silent sign");
_Static_assert(sizeof(((struct tc_gbl_data*)0)->tc_CO)==4,"TERMCAP tc_gbl_data.tc_CO width");
_Static_assert((((__typeof__(((struct tc_gbl_data*)0)->tc_CO))-1)<0)==1,"TERMCAP tc_gbl_data.tc_CO sign");
_Static_assert(sizeof(((struct tc_gbl_data*)0)->tc_LI)==4,"TERMCAP tc_gbl_data.tc_LI width");
_Static_assert((((__typeof__(((struct tc_gbl_data*)0)->tc_LI))-1)<0)==1,"TERMCAP tc_gbl_data.tc_LI sign");
_Static_assert(sizeof(((struct tc_lcl_data*)0)->tc_ul_hack)==1,"TERMCAP tc_lcl_data.tc_ul_hack width");
_Static_assert((((__typeof__(((struct tc_lcl_data*)0)->tc_ul_hack))-1)<0)==1,"TERMCAP tc_lcl_data.tc_ul_hack sign");
_Static_assert(sizeof(((struct symsetentry*)0)->handling)==4,"TERMCAP symsetentry.handling width");
_Static_assert((((__typeof__(((struct symsetentry*)0)->handling))-1)<0)==0,"TERMCAP symsetentry.handling sign");
_Static_assert(sizeof(((struct instance_globals_c*)0)->currentgraphics)==4,"TERMCAP instance_globals_c.currentgraphics width");
_Static_assert((((__typeof__(((struct instance_globals_c*)0)->currentgraphics))-1)<0)==1,"TERMCAP instance_globals_c.currentgraphics sign");
_Static_assert(sizeof(((struct cmd*)0)->num_pad)==1,"TERMCAP cmd.num_pad width");
_Static_assert((((__typeof__(((struct cmd*)0)->num_pad))-1)<0)==1,"TERMCAP cmd.num_pad sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->cury)==2,"TERMCAP DisplayDesc.cury width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->cury))-1)<0)==1,"TERMCAP DisplayDesc.cury sign");
_Static_assert(sizeof(((struct DisplayDesc*)0)->curx)==2,"TERMCAP DisplayDesc.curx width");
_Static_assert((((__typeof__(((struct DisplayDesc*)0)->curx))-1)<0)==1,"TERMCAP DisplayDesc.curx sign");
_Static_assert(sizeof(((nomux_cell*)0)->ch)==1,"TERMCAP nomux_cell.ch width");
_Static_assert((((__typeof__(((nomux_cell*)0)->ch))-1)<0)==1,"TERMCAP nomux_cell.ch sign");
_Static_assert(sizeof(((nomux_cell*)0)->fg)==1,"TERMCAP nomux_cell.fg width");
_Static_assert((((__typeof__(((nomux_cell*)0)->fg))-1)<0)==0,"TERMCAP nomux_cell.fg sign");
_Static_assert(sizeof(((nomux_cell*)0)->attr)==1,"TERMCAP nomux_cell.attr width");
_Static_assert((((__typeof__(((nomux_cell*)0)->attr))-1)<0)==0,"TERMCAP nomux_cell.attr sign");
_Static_assert(sizeof(((nomux_cell*)0)->decgfx)==1,"TERMCAP nomux_cell.decgfx width");
_Static_assert((((__typeof__(((nomux_cell*)0)->decgfx))-1)<0)==0,"TERMCAP nomux_cell.decgfx sign");
_Static_assert(sizeof(((struct instance_flags*)0)->wc2_darkgray)==1,"TERMCAP instance_flags.wc2_darkgray width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->wc2_darkgray))-1)<0)==1,"TERMCAP instance_flags.wc2_darkgray sign");
_Static_assert(sizeof(((struct instance_flags*)0)->debug_fuzzer)==1,"TERMCAP instance_flags.debug_fuzzer width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->debug_fuzzer))-1)<0)==1,"TERMCAP instance_flags.debug_fuzzer sign");
_Static_assert(sizeof(((struct instance_flags*)0)->colorcount)==4,"TERMCAP instance_flags.colorcount width");
_Static_assert((((__typeof__(((struct instance_flags*)0)->colorcount))-1)<0)==0,"TERMCAP instance_flags.colorcount sign");
_Static_assert(sizeof(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->nh_color)==4,"TERMCAP ti_map_entry.nh_color width");
_Static_assert((((__typeof__(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->nh_color))-1)<0)==1,"TERMCAP ti_map_entry.nh_color sign");
_Static_assert(sizeof(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->nh_bright_color)==4,"TERMCAP ti_map_entry.nh_bright_color width");
_Static_assert((((__typeof__(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->nh_bright_color))-1)<0)==1,"TERMCAP ti_map_entry.nh_bright_color sign");
_Static_assert(sizeof(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->ti_color)==4,"TERMCAP ti_map_entry.ti_color width");
_Static_assert((((__typeof__(((TELEPORT_TERMCAP_TI_MAP_TYPE*)0)->ti_color))-1)<0)==1,"TERMCAP ti_map_entry.ti_color sign");
#endif
