#include "../common/abi.h"
#include <stddef.h>
#define NUM_INVIS_TILES 1
long gen_constant(int i){static const long v[]={CORPSE,EXIT_FAILURE,EXIT_SUCCESS,GLYPH_ALTAR_OFF,GLYPH_BODY_OFF,GLYPH_BODY_PILETOP_OFF,GLYPH_CMAP_A_OFF,GLYPH_CMAP_B_OFF,GLYPH_CMAP_C_OFF,GLYPH_CMAP_GEH_OFF,GLYPH_CMAP_KNOX_OFF,GLYPH_CMAP_MAIN_OFF,GLYPH_CMAP_MINES_OFF,GLYPH_CMAP_OFF,GLYPH_CMAP_SOKO_OFF,GLYPH_CMAP_STONE_OFF,GLYPH_DETECT_FEM_OFF,GLYPH_DETECT_MALE_OFF,GLYPH_DETECT_OFF,GLYPH_EXPLODE_DARK_OFF,GLYPH_EXPLODE_FIERY_OFF,GLYPH_EXPLODE_FROSTY_OFF,GLYPH_EXPLODE_MAGICAL_OFF,GLYPH_EXPLODE_MUDDY_OFF,GLYPH_EXPLODE_NOXIOUS_OFF,GLYPH_EXPLODE_OFF,GLYPH_EXPLODE_WET_OFF,GLYPH_INVISIBLE,GLYPH_INVIS_OFF,GLYPH_MON_FEM_OFF,GLYPH_MON_MALE_OFF,GLYPH_MON_OFF,GLYPH_NOTHING,GLYPH_NOTHING_OFF,GLYPH_OBJ_OFF,GLYPH_OBJ_PILETOP_OFF,GLYPH_PET_FEM_OFF,GLYPH_PET_MALE_OFF,GLYPH_PET_OFF,GLYPH_RIDDEN_FEM_OFF,GLYPH_RIDDEN_MALE_OFF,GLYPH_RIDDEN_OFF,GLYPH_STATUE_FEM_OFF,GLYPH_STATUE_FEM_PILETOP_OFF,GLYPH_STATUE_MALE_OFF,GLYPH_STATUE_MALE_PILETOP_OFF,GLYPH_STATUE_OFF,GLYPH_SWALLOW_OFF,GLYPH_UNEXPLORED_OFF,GLYPH_WARNING_OFF,GLYPH_ZAP_OFF,MAXEXPCHARS,MAXPCHARS,MAXTCHARS,MAX_GLYPH,MON_GLYPH,NEUTRAL,NO_GLYPH,NUMMONS,NUM_INVIS_TILES,NUM_OBJECTS,NUM_ZAP,OBJ_GLYPH,OTH_GLYPH,S_altar,S_arrow_trap,S_brdnladder,S_corr,S_digbeam,S_expl_br,S_expl_tl,S_goodpos,S_grave,S_ndoor,S_stone,S_sw_br,S_sw_tl,S_trwall,S_vwall,TERMINATOR,WARNCOUNT,altar_other,altar_unaligned,expl_dark,expl_frosty,generated,main_walls,mines_walls,monsters_file,objects_file,other_file,sokoban_walls};return i>=0&&i<sizeof(v)/sizeof(v[0])?v[i]:-1;}
long gen_layout(int i){static const long v[]={offsetof(struct utility_tilemap,name),sizeof(((struct utility_tilemap*)0)->name),offsetof(struct utility_tilemap,glyph)};return v[i];}
void gen_snprintf0(char*out,size_t size,const char*fmt,const char* a0){nh_snprintf("init_tilemap",709,out,size,fmt,a0);}
void gen_snprintf1(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",711,out,size,fmt,a0,a1);}
void gen_snprintf2(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",713,out,size,fmt,a0,a1);}
void gen_snprintf3(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",715,out,size,fmt,a0,a1);}
void gen_snprintf4(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",717,out,size,fmt,a0,a1);}
void gen_snprintf5(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",719,out,size,fmt,a0,a1);}
void gen_snprintf6(char*out,size_t size,const char*fmt,const char* a0){nh_snprintf("init_tilemap",742,out,size,fmt,a0);}
void gen_snprintf7(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",745,out,size,fmt,a0,a1);}
void gen_snprintf8(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",748,out,size,fmt,a0,a1);}
void gen_snprintf9(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",751,out,size,fmt,a0,a1);}
void gen_snprintf10(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",753,out,size,fmt,a0,a1);}
void gen_snprintf11(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("init_tilemap",756,out,size,fmt,a0,a1);}
void gen_snprintf12(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",806,out,size,fmt,a0,a1);}
void gen_snprintf13(char*out,size_t size,const char*fmt,const char* a0,const char* a1,int a2){nh_snprintf("init_tilemap",810,out,size,fmt,a0,a1,a2);}
void gen_snprintf14(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",844,out,size,fmt,a0,a1);}
void gen_snprintf15(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",865,out,size,fmt,a0,a1);}
void gen_snprintf16(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",896,out,size,fmt,a0,a1);}
void gen_snprintf17(char*out,size_t size,const char*fmt,const char* a0,const char* a1,int a2){nh_snprintf("init_tilemap",928,out,size,fmt,a0,a1,a2);}
void gen_snprintf18(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",958,out,size,fmt,a0,a1);}
void gen_snprintf19(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1018,out,size,fmt,a0,a1);}
void gen_snprintf20(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1047,out,size,fmt,a0,a1);}
void gen_snprintf21(char*out,size_t size,const char*fmt,const char* a0,const char* a1,int a2){nh_snprintf("init_tilemap",1087,out,size,fmt,a0,a1,a2);}
void gen_snprintf22(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1109,out,size,fmt,a0,a1);}
void gen_snprintf23(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1138,out,size,fmt,a0,a1);}
void gen_snprintf24(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1153,out,size,fmt,a0,a1);}
void gen_snprintf25(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1169,out,size,fmt,a0,a1);}
void gen_snprintf26(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1189,out,size,fmt,a0,a1);}
void gen_snprintf27(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1238,out,size,fmt,a0,a1);}
void gen_snprintf28(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1242,out,size,fmt,a0,a1);}
void gen_snprintf29(char*out,size_t size,const char*fmt,const char* a0,int a1){nh_snprintf("init_tilemap",1261,out,size,fmt,a0,a1);}
void gen_snprintf30(char*out,size_t size,const char*fmt,const char* a0){nh_snprintf("main",1337,out,size,fmt,a0);}
int gen_sprintf0(char*out,const char*fmt,const char* a0,int a1){return sprintf(out,fmt,a0,a1);}
int gen_sprintf1(char*out,const char*fmt,const char* a0,int a1){return sprintf(out,fmt,a0,a1);}
int gen_sprintf2(char*out,const char*fmt,const char* a0,int a1){return sprintf(out,fmt,a0,a1);}
int gen_sprintf3(char*out,const char*fmt,const char* a0,int a1){return sprintf(out,fmt,a0,a1);}
int gen_fprintf0(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf1(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf2(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf3(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf4(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf5(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf6(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf7(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf8(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf9(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf10(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf11(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf12(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf13(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf14(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf15(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf16(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf17(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf18(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf19(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf20(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf21(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf22(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf23(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf24(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf25(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf26(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf27(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf28(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf29(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf30(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf31(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf32(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf33(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf34(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf35(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf36(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf37(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf38(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf39(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf40(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf41(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf42(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf43(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf44(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf45(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf46(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf47(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf48(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf49(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf50(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf51(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf52(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf53(FILE*out,const char*fmt,const char* a0,int a1,int a2){return fprintf(out,fmt,a0,a1,a2);}
int gen_fprintf54(FILE*out,const char*fmt,const char* a0,int a1,int a2){return fprintf(out,fmt,a0,a1,a2);}
int gen_fprintf55(FILE*out,const char*fmt,const char* a0,const char* a1,int a2){return fprintf(out,fmt,a0,a1,a2);}
int gen_fprintf56(FILE*out,const char*fmt,const char* a0,int a1,int a2){return fprintf(out,fmt,a0,a1,a2);}
int gen_fprintf57(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf58(FILE*out,const char*fmt,const char* a0,int a1,int a2){return fprintf(out,fmt,a0,a1,a2);}
int gen_fprintf59(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf60(FILE*out,const char*fmt,const char* a0,int a1,int a2){return fprintf(out,fmt,a0,a1,a2);}
int gen_fprintf61(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf62(FILE*out,const char*fmt,int a0,int a1,const char* a2){return fprintf(out,fmt,a0,a1,a2);}
int gen_fprintf63(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf64(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf65(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf66(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf67(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf68(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf69(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf70(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf71(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf72(FILE*out,const char*fmt,int a0){return fprintf(out,fmt,a0);}
int gen_fprintf73(FILE*out,const char*fmt,const char* a0){return fprintf(out,fmt,a0);}
int gen_fprintf74(FILE*out,const char*fmt,const char* a0){return fprintf(out,fmt,a0);}
int gen_fprintf75(FILE*out,const char*fmt,const char* a0){return fprintf(out,fmt,a0);}
int gen_fprintf76(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf77(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf78(FILE*out,const char*fmt,const char* a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf79(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf80(FILE*out,const char*fmt,const char* a0,const char* a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf81(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf82(FILE*out,const char*fmt,const char* a0){return fprintf(out,fmt,a0);}
int gen_fprintf83(FILE*out,const char*fmt,const char* a0,const char* a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf84(FILE*out,const char*fmt,const char* a0,const char* a1,const char* a2,const char* a3){return fprintf(out,fmt,a0,a1,a2,a3);}
int gen_fprintf85(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf86(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf87(FILE*out,const char*fmt,int a0,int a1){return fprintf(out,fmt,a0,a1);}
int gen_fprintf88(FILE*out,const char*fmt,int a0,const char* a1,int a2,const char* a3,int a4,const char* a5){return fprintf(out,fmt,a0,a1,a2,a3,a4,a5);}
int gen_fprintf89(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf90(FILE*out,const char*fmt){return fprintf(out,fmt);}
int gen_fprintf91(FILE*out,const char*fmt){return fprintf(out,fmt);}
FILE*gen_fopen(const char*a,const char*b){return fopen(a,b);}
int gen_fclose(FILE*p){return fclose(p);}
void gen_perror(const char*p){perror(p);}
int gen_unlink(const char*p){return unlink(p);}
