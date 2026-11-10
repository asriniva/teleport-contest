/* PAGER typed/header/dependency ABI only; all source control/data are JS. */
#include "hack.h"
#include "dlb.h"
#include "../../../scripts/tu-pager-layout.h"
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
long teleport_pager_record_get(int kind,int field,void*p){switch(kind){
case 0:{struct monst*v=p;switch(field){case 0:return(long)v->data;case 1:return(long)v->mappearance;case 2:return(long)v->mundetected;case 3:return(long)v->mx;case 4:return(long)v->my;case 5:return(long)v->isshk;case 6:return(long)v->m_ap_type;case 7:return(long)v->mfrozen;case 8:return(long)v->mleashed;case 9:return(long)v->mpeaceful;case 10:return(long)v->msleeping;case 11:return(long)v->mstrategy;case 12:return(long)v->mtame;case 13:return(long)v->mtrapped;case 14:return(long)v->female;}}
case 1:{struct permonst*v=p;switch(field){case 0:return(long)v->mlet;case 1:return(long)v->mflags1;case 2:return(long)v->mflags2;case 3:return(long)v->pmnames;}}
case 2:{struct obj*v=p;switch(field){case 0:return(long)v->corpsenm;case 1:return(long)v->dknown;case 2:return(long)v->leashmon;case 3:return(long)v->no_charge;case 4:return(long)v->nobj;case 5:return(long)v->oclass;case 6:return(long)v->otyp;case 7:return(long)v->ox;case 8:return(long)v->oy;case 9:return(long)v->quan;case 10:return(long)v->spe;case 11:return(long)v->timed;case 12:return(long)v->where;case 13:return(long)v->invlet;}}
case 3:{struct trap*v=p;switch(field){case 0:return(long)v->ntrap;case 1:return(long)v->tx;case 2:return(long)v->ty;case 3:return(long)v->tseen;case 4:return(long)v->ttyp;case 5:return(long)v->madeby_u;}}
case 4:{coord*v=p;switch(field){case 0:return(long)v->x;case 1:return(long)v->y;}}
case 5:{d_level*v=p;switch(field){case 0:return(long)v->dnum;case 1:return(long)v->dlevel;}}
case 6:{menu_item*v=p;switch(field){case 0:return(long)&v->item;case 1:return(long)v->count;}}
case 7:{anything*v=p;switch(field){case 0:return(long)v->a_int;case 1:return(long)v->a_char;}}
case 8:{NhRegion*v=p;switch(field){case 0:return(long)v->glyph;}}
case 9:{struct engr*v=p;switch(field){case 0:return(long)v->eread;case 1:return(long)v->engr_x;case 2:return(long)v->engr_y;case 3:return(long)v->engr_txt;}}
case 10:{glyph_info*v=p;switch(field){case 0:return(long)v->glyph;case 1:return(long)v->ttychar;}}
case 11:{struct _cmd_queue*v=p;switch(field){case 0:return(long)v->typ;case 1:return(long)v->key;}}
case 12:{struct objclass*v=p;switch(field){case 0:return(long)v->oc_name_idx;case 1:return(long)v->oc_class;}}
case 13:{struct objdescr*v=p;switch(field){case 0:return(long)v->oc_name;case 1:return(long)v->oc_descr;}}
case 14:{struct rm*v=p;switch(field){case 0:return(long)v->typ;case 1:return(long)v->seenv;case 2:return(long)v->glyph;case 3:return(long)v->doormask;}}
case 15:{struct symdef*v=p;switch(field){case 0:return(long)v->sym;case 1:return(long)v->explanation;}}
case 16:{struct class_sym*v=p;switch(field){case 0:return(long)v->sym;case 1:return(long)v->explain;}}
}abort();}
void teleport_pager_record_set(int kind,int field,void*p,long value){switch(kind){
case 0:{struct monst*v=p;switch(field){case 0:v->data=(__typeof__(v->data))value;return;case 1:v->mappearance=value;return;case 2:v->mundetected=value;return;case 3:v->mx=value;return;case 4:v->my=value;return;case 5:v->isshk=value;return;case 6:v->m_ap_type=value;return;case 7:v->mfrozen=value;return;case 8:v->mleashed=value;return;case 9:v->mpeaceful=value;return;case 10:v->msleeping=value;return;case 11:v->mstrategy=value;return;case 12:v->mtame=value;return;case 13:v->mtrapped=value;return;case 14:v->female=value;return;}}
case 1:{struct permonst*v=p;switch(field){case 0:v->mlet=value;return;case 1:v->mflags1=value;return;case 2:v->mflags2=value;return;}}
case 2:{struct obj*v=p;switch(field){case 0:v->corpsenm=value;return;case 1:v->dknown=value;return;case 2:v->leashmon=value;return;case 3:v->no_charge=value;return;case 4:v->nobj=(__typeof__(v->nobj))value;return;case 5:v->oclass=value;return;case 6:v->otyp=value;return;case 7:v->ox=value;return;case 8:v->oy=value;return;case 9:v->quan=value;return;case 10:v->spe=value;return;case 11:v->timed=value;return;case 12:v->where=value;return;case 13:v->invlet=value;return;}}
case 3:{struct trap*v=p;switch(field){case 0:v->ntrap=(__typeof__(v->ntrap))value;return;case 1:v->tx=value;return;case 2:v->ty=value;return;case 3:v->tseen=value;return;case 4:v->ttyp=value;return;case 5:v->madeby_u=value;return;}}
case 4:{coord*v=p;switch(field){case 0:v->x=value;return;case 1:v->y=value;return;}}
case 5:{d_level*v=p;switch(field){case 0:v->dnum=value;return;case 1:v->dlevel=value;return;}}
case 6:{menu_item*v=p;switch(field){case 1:v->count=value;return;}}
case 7:{anything*v=p;switch(field){case 0:v->a_int=value;return;case 1:v->a_char=value;return;}}
case 8:{NhRegion*v=p;switch(field){case 0:v->glyph=value;return;}}
case 9:{struct engr*v=p;switch(field){case 0:v->eread=value;return;case 1:v->engr_x=value;return;case 2:v->engr_y=value;return;}}
case 10:{glyph_info*v=p;switch(field){case 0:v->glyph=value;return;case 1:v->ttychar=value;return;}}
case 11:{struct _cmd_queue*v=p;switch(field){case 0:v->typ=value;return;case 1:v->key=value;return;}}
case 12:{struct objclass*v=p;switch(field){case 0:v->oc_name_idx=value;return;case 1:v->oc_class=value;return;}}
case 13:{struct objdescr*v=p;switch(field){case 0:v->oc_name=(__typeof__(v->oc_name))value;return;case 1:v->oc_descr=(__typeof__(v->oc_descr))value;return;}}
case 14:{struct rm*v=p;switch(field){case 0:v->typ=value;return;case 1:v->seenv=value;return;case 2:v->glyph=value;return;case 3:v->doormask=value;return;}}
case 15:{struct symdef*v=p;switch(field){}}
case 16:{struct class_sym*v=p;switch(field){}}
}abort();}
long teleport_pager_get(int field){switch(field){case 0:return(long)EDetect_monsters;case 1:return(long)EHalluc_resistance;case 2:return(long)WIN_MESSAGE;case 3:return(long)flags.help;case 4:return(long)flags.lootabc;case 5:return(long)flags.showrace;case 6:return(long)flags.verbose;case 7:return(long)gd.decor_levitate_override;case 8:return(long)gf.ftrap;case 9:return(long)gi.invent;case 10:return(long)gu.urace.adj;case 11:return(long)iflags.altmeta;case 12:return(long)iflags.getpos_coords;case 13:return(long)iflags.ice_rating;case 14:return(long)iflags.save_uswallow;case 15:return(long)iflags.terrainmode;case 16:return(long)program_state.gameover;case 17:return(long)something;case 18:return(long)svc.context.current_fruit;case 19:return(long)svc.context.warntype.obj;case 20:return(long)svc.context.warntype.polyd;case 21:return(long)svl.level.buriedobjlist;case 22:return(long)svl.level.flags.hero_memory;case 23:return(long)svp.plname;case 24:return(long)sysopt.fmtd_wizard_list;case 25:return(long)sysopt.hideusage;case 26:return(long)sysopt.support;case 27:return(long)u.dx;case 28:return(long)u.dy;case 29:return(long)u.dz;case 30:return(long)u.umonnum;case 31:return(long)u.uswallow;case 32:return(long)u.utrap;case 33:return(long)u.uundetected;case 34:return(long)u.ux;case 35:return(long)u.uy;case 36:return(long)u.xray_range;}abort();}
void teleport_pager_set(int field,long value){switch(field){case 0:EDetect_monsters=value;return;case 1:EHalluc_resistance=value;return;case 2:WIN_MESSAGE=value;return;case 3:flags.help=value;return;case 4:flags.lootabc=value;return;case 5:flags.showrace=value;return;case 6:flags.verbose=value;return;case 7:gd.decor_levitate_override=value;return;case 8:gf.ftrap=(__typeof__(gf.ftrap))value;return;case 9:gi.invent=(__typeof__(gi.invent))value;return;case 11:iflags.altmeta=value;return;case 12:iflags.getpos_coords=value;return;case 13:iflags.ice_rating=value;return;case 14:iflags.save_uswallow=value;return;case 15:iflags.terrainmode=value;return;case 16:program_state.gameover=value;return;case 18:svc.context.current_fruit=value;return;case 19:svc.context.warntype.obj=value;return;case 20:svc.context.warntype.polyd=value;return;case 21:svl.level.buriedobjlist=(__typeof__(svl.level.buriedobjlist))value;return;case 22:svl.level.flags.hero_memory=value;return;case 24:sysopt.fmtd_wizard_list=(__typeof__(sysopt.fmtd_wizard_list))value;return;case 25:sysopt.hideusage=value;return;case 26:sysopt.support=(__typeof__(sysopt.support))value;return;case 27:u.dx=value;return;case 28:u.dy=value;return;case 29:u.dz=value;return;case 30:u.umonnum=value;return;case 31:u.uswallow=value;return;case 32:u.utrap=value;return;case 33:u.uundetected=value;return;case 34:u.ux=value;return;case 35:u.uy=value;return;case 36:u.xray_range=value;return;}abort();}
void*teleport_pager_address(int field){switch(field){case 0:return(void*)&gy.youmonst;case 1:return(void*)&cg.zeroany;case 2:return(void*)u.ustuck;case 3:return(void*)u.usteed;case 4:return(void*)&u.uz;case 5:return(void*)&qstart_level;case 6:return(void*)&nul_glyphinfo;case 7:return(void*)uball;}abort();}
long teleport_pager_hero(int field){switch(field){case 0:return(long)(Blind);case 1:return(long)(Detect_monsters);case 2:return(long)(Hallucination);case 3:return(long)(Infravision);case 4:return(long)(Inhell);case 5:return(long)(Invis);case 6:return(long)(Invisible);case 7:return(long)(Levitation);case 8:return(long)(Punished);case 9:return(long)(U_AP_TYPE);case 10:return(long)(Ugender);case 11:return(long)(Unblind_telepat);case 12:return(long)(Underwater);case 13:return(long)(Upolyd);case 14:return(long)(wizard);}abort();}
void*teleport_pager_array(int kind,int i,int j){switch(kind){case 0:return(void*)&mons[i];case 1:return(void*)&objects[i];case 2:return(void*)&obj_descr[i];case 3:return(void*)&levl[i][j];case 4:return(void*)&defsyms[i];case 5:return(void*)&def_warnsyms[i];case 6:return(void*)&def_monsyms[i];case 7:return(void*)&def_oc_syms[i];case 8:return(void*)&gs.showsyms[i];case 9:return(void*)&go.ov_primary_syms[i];case 10:return(void*)&go.ov_rogue_syms[i];case 11:return(void*)&gw.warnsyms[i];case 12:return(void*)&svl.lastseentyp[i][j];}abort();}
void*teleport_pager_mat(coordxy x,coordxy y){return m_at(x,y);}
void teleport_pager_copy(void*a,const void*b,size_t n){memcpy(a,b,n);}
const char*teleport_pager_chararray(int kind,void*p,int i){if(kind==1)return((struct permonst*)p)->pmnames[i];if(kind==9)return((struct engr*)p)->engr_txt[i];abort();}
extern const char what_is_a_location[];
static char teleport_pager_static_0[29];
static char teleport_pager_static_1[16];
static char teleport_pager_static_2[5];
static char teleport_pager_static_3[40];
static char teleport_pager_static_4[26];
static char teleport_pager_static_5[16];
static char teleport_pager_static_6[256];
void*teleport_pager_static(int kind){switch(kind){case 0:return teleport_pager_static_0;case 1:return teleport_pager_static_1;case 2:return teleport_pager_static_2;case 3:return teleport_pager_static_3;case 4:return teleport_pager_static_4;case 5:return teleport_pager_static_5;case 6:return teleport_pager_static_6;}abort();}
void*teleport_pager_public(void){return(void*)what_is_a_location;}
const char*teleport_pager_string_DATAFILE(void){return DATAFILE;}
const char*teleport_pager_string_DEBUGHELP(void){return DEBUGHELP;}
const char*teleport_pager_string_DEVTEAM_EMAIL(void){return DEVTEAM_EMAIL;}
const char*teleport_pager_string_DEVTEAM_URL(void){return DEVTEAM_URL;}
const char*teleport_pager_string_HELP(void){return HELP;}
const char*teleport_pager_string_HISTORY(void){return HISTORY;}
const char*teleport_pager_string_KEYHELP(void){return KEYHELP;}
const char*teleport_pager_string_LICENSE(void){return LICENSE;}
const char*teleport_pager_string_OPTIONFILE(void){return OPTIONFILE;}
const char*teleport_pager_string_OPTMENUHELP(void){return OPTMENUHELP;}
const char*teleport_pager_string_PORT_ID(void){return PORT_ID;}
const char*teleport_pager_string_SHELP(void){return SHELP;}
const char*teleport_pager_string_USAGEHELP(void){return USAGEHELP;}
int teleport_pager_dep_Amask2align(int a0){return Amask2align(a0);}
int teleport_pager_dep_IS_GRAVE(int a0){return IS_GRAVE(a0);}
int teleport_pager_dep_IS_TREE(int a0){return IS_TREE(a0);}
int teleport_pager_dep_IS_WALL(int a0){return IS_WALL(a0);}
int teleport_pager_dep_IS_WATERWALL(int a0){return IS_WATERWALL(a0);}
int teleport_pager_dep_Is_airlevel(d_level* a0){return Is_airlevel(a0);}
int teleport_pager_dep_Is_astralevel(d_level* a0){return Is_astralevel(a0);}
int teleport_pager_dep_Is_juiblex_level(d_level* a0){return Is_juiblex_level(a0);}
int teleport_pager_dep_Is_medusa_level(d_level* a0){return Is_medusa_level(a0);}
int teleport_pager_dep_Is_qstart(d_level* a0){return Is_qstart(a0);}
int teleport_pager_dep_Is_rogue_level(d_level* a0){return Is_rogue_level(a0);}
int teleport_pager_dep_Is_waterlevel(d_level* a0){return Is_waterlevel(a0);}
int teleport_pager_dep_MCORPSENM(struct monst* a0){return MCORPSENM(a0);}
int teleport_pager_dep_M_AP_FLAG(struct monst* a0){return M_AP_FLAG(a0);}
int teleport_pager_dep_M_AP_TYPE(struct monst* a0){return M_AP_TYPE(a0);}
int teleport_pager_dep_Mgender(struct monst * a0){return Mgender(a0);}
const char* teleport_pager_dep_OBJ_NAME(struct objclass a0){return OBJ_NAME(a0);}
int teleport_pager_dep_Race_if(int a0){return Race_if(a0);}
int teleport_pager_dep_Role_if(int a0){return Role_if(a0);}
int teleport_pager_dep_SURFACE_AT(coordxy a0,coordxy a1){return SURFACE_AT(a0,a1);}
char * teleport_pager_dep_Strcat(char *restrict a0,const char *restrict a1){return strcat(a0,a1);}
char * teleport_pager_dep_Strcpy(char *restrict a0,const char *restrict a1){return strcpy(a0,a1);}
int teleport_pager_dep_abs(int a0){return abs(a0);}
void teleport_pager_dep_add_menu(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){add_menu(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
void teleport_pager_dep_add_menu_str(winid a0,const char * a1){add_menu_str(a0,a1);}
const char * teleport_pager_dep_align_str(aligntyp a0){return align_str(a0);}
int teleport_pager_dep_altarmask_at(coordxy a0,coordxy a1){return altarmask_at(a0,a1);}
char * teleport_pager_dep_an(const char * a0){return an(a0);}
char * teleport_pager_dep_ansimpleoname(struct obj * a0){return ansimpleoname(a0);}
int teleport_pager_dep_cansee(coordxy a0,coordxy a1){return cansee(a0,a1);}
int teleport_pager_dep_canspotself(void){return canspotself();}
int teleport_pager_dep_ceiling_hider(struct permonst* a0){return ceiling_hider(a0);}
boolean teleport_pager_dep_closed_door(coordxy a0,coordxy a1){return closed_door(a0,a1);}
int teleport_pager_dep_cmap_to_glyph(int a0){return cmap_to_glyph(a0);}
char teleport_pager_dep_cmd_from_func(int (*a0)(void)){return cmd_from_func(a0);}
const char * teleport_pager_dep_cmdname_from_func(int (*a0)(void),char * a1,boolean a2){return cmdname_from_func(a0,a1,a2);}
void teleport_pager_dep_cmdq_clear(int a0){cmdq_clear(a0);}
struct _cmd_queue * teleport_pager_dep_cmdq_pop(void){return cmdq_pop();}
char * teleport_pager_dep_coord_desc(coordxy a0,coordxy a1,char * a2,char a3){return coord_desc(a0,a1,a2,a3);}
void teleport_pager_dep_copynchars(char * a0,const char * a1,int a2){copynchars(a0,a1,a2);}
boolean teleport_pager_dep_costly_spot(coordxy a0,coordxy a1){return costly_spot(a0,a1);}
int teleport_pager_dep_couldsee(coordxy a0,coordxy a1){return couldsee(a0,a1);}
char * teleport_pager_dep_coyotename(struct monst * a0,char * a1){return coyotename(a0,a1);}
winid teleport_pager_dep_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_pager_dep_dealloc_obj(struct obj * a0){dealloc_obj(a0);}
char * teleport_pager_dep_decode_mixed(char * a0,const char * a1){return decode_mixed(a0,a1);}
void teleport_pager_dep_destroy_nhwindow(winid a0){destroy_nhwindow(a0);}
int teleport_pager_dep_digests(struct permonst* a0){return digests(a0);}
boolean teleport_pager_dep_digit(char a0){return digit(a0);}
void teleport_pager_dep_display_file(const char* a0,boolean a1){display_file(a0,a1);}
char teleport_pager_dep_display_inventory(const char * a0,boolean a1){return display_inventory(a0,a1);}
void teleport_pager_dep_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
char * teleport_pager_dep_distant_monnam(struct monst * a0,int a1,char * a2){return distant_monnam(a0,a1,a2);}
char * teleport_pager_dep_distant_name(struct obj * a0,char *(*a1)(struct obj *)){return distant_name(a0,a1);}
int teleport_pager_dep_distu(coordxy a0,coordxy a1){return distu(a0,a1);}
int teleport_pager_dep_dlb_fclose(FILE * a0){return dlb_fclose(a0);}
char * teleport_pager_dep_dlb_fgets(char *restrict a0,int a1,FILE *restrict a2){return dlb_fgets(a0,a1,a2);}
FILE * teleport_pager_dep_dlb_fopen(const char *restrict a0,const char *restrict a1){return dlb_fopen(a0,a1);}
int teleport_pager_dep_dlb_fseek(FILE * a0,long a1,int a2){return dlb_fseek(a0,a1,a2);}
int teleport_pager_dep_doextlist(void){return doextlist();}
int teleport_pager_dep_doextversion(void){return doextversion();}
void teleport_pager_dep_dumplogmsg(const char * a0){dumplogmsg(a0);}
char * teleport_pager_dep_encglyph(int a0){return encglyph(a0);}
void teleport_pager_dep_end_menu(winid a0,const char* a1){end_menu(a0,a1);}
struct engr * teleport_pager_dep_engr_at(coordxy a0,coordxy a1){return engr_at(a0,a1);}
int teleport_pager_dep_engraving_to_glyph(struct engr* a0){return engraving_to_glyph(a0);}
char * teleport_pager_dep_eos(char * a0){return eos(a0);}
void teleport_pager_dep_free(void * a0){free(a0);}
struct fruit * teleport_pager_dep_fruit_from_name(const char * a0,boolean a1,int * a2){return fruit_from_name(a0,a1,a2);}
int teleport_pager_dep_getdir(const char * a0){return getdir(a0);}
void teleport_pager_dep_getlin(const char * a0,char * a1){getlin(a0,a1);}
int teleport_pager_dep_getpos(coord * a0,boolean a1,const char * a2){return getpos(a0,a1,a2);}
int teleport_pager_dep_glyph_at(coordxy a0,coordxy a1){return glyph_at(a0,a1);}
int teleport_pager_dep_glyph_is_body(int a0){return glyph_is_body(a0);}
int teleport_pager_dep_glyph_is_cmap(int a0){return glyph_is_cmap(a0);}
int teleport_pager_dep_glyph_is_invisible(int a0){return glyph_is_invisible(a0);}
int teleport_pager_dep_glyph_is_monster(int a0){return glyph_is_monster(a0);}
int teleport_pager_dep_glyph_is_nothing(int a0){return glyph_is_nothing(a0);}
int teleport_pager_dep_glyph_is_object(int a0){return glyph_is_object(a0);}
int teleport_pager_dep_glyph_is_statue(int a0){return glyph_is_statue(a0);}
int teleport_pager_dep_glyph_is_trap(int a0){return glyph_is_trap(a0);}
int teleport_pager_dep_glyph_is_unexplored(int a0){return glyph_is_unexplored(a0);}
int teleport_pager_dep_glyph_is_warning(int a0){return glyph_is_warning(a0);}
int teleport_pager_dep_glyph_to_body_corpsenm(int a0){return glyph_to_body_corpsenm(a0);}
int teleport_pager_dep_glyph_to_cmap(int a0){return glyph_to_cmap(a0);}
int teleport_pager_dep_glyph_to_obj(int a0){return glyph_to_obj(a0);}
int teleport_pager_dep_glyph_to_statue_corpsenm(int a0){return glyph_to_statue_corpsenm(a0);}
int teleport_pager_dep_glyph_to_trap(int a0){return glyph_to_trap(a0);}
int teleport_pager_dep_glyph_to_warning(int a0){return glyph_to_warning(a0);}
int teleport_pager_dep_has_mcorpsenm(struct monst* a0){return has_mcorpsenm(a0);}
int teleport_pager_dep_hides_under(struct permonst* a0){return hides_under(a0);}
const char * teleport_pager_dep_hliquid(const char * a0){return hliquid(a0);}
unsigned int teleport_pager_dep_howmonseen(struct monst * a0){return howmonseen(a0);}
void teleport_pager_dep_introff(void){introff();}
void teleport_pager_dep_intron(void){intron();}
int teleport_pager_dep_is_cmap_drawbridge(int a0){return is_cmap_drawbridge(a0);}
int teleport_pager_dep_is_cmap_engraving(int a0){return is_cmap_engraving(a0);}
int teleport_pager_dep_is_cmap_trap(int a0){return is_cmap_trap(a0);}
int teleport_pager_dep_is_drawbridge_wall(coordxy a0,coordxy a1){return is_drawbridge_wall(a0,a1);}
int teleport_pager_dep_is_hider(struct permonst* a0){return is_hider(a0);}
int teleport_pager_dep_is_hole(int a0){return is_hole(a0);}
boolean teleport_pager_dep_is_lava(coordxy a0,coordxy a1){return is_lava(a0,a1);}
int teleport_pager_dep_is_obj_mappear(struct monst* a0,unsigned a1){return is_obj_mappear(a0,a1);}
int teleport_pager_dep_is_orc(struct permonst* a0){return is_orc(a0);}
int teleport_pager_dep_is_pit(int a0){return is_pit(a0);}
boolean teleport_pager_dep_is_pool(coordxy a0,coordxy a1){return is_pool(a0,a1);}
boolean teleport_pager_dep_is_treefruit(struct obj * a0){return is_treefruit(a0);}
int teleport_pager_dep_isok(coordxy a0,coordxy a1){return isok(a0,a1);}
const char * teleport_pager_dep_key2extcmddesc(uchar a0){return key2extcmddesc(a0);}
char * teleport_pager_dep_key2txt(uchar a0,char * a1){return key2txt(a0,a1);}
char * teleport_pager_dep_lcase(char * a0){return lcase(a0);}
char * teleport_pager_dep_makeplural(const char * a0){return makeplural(a0);}
char * teleport_pager_dep_makesingular(const char * a0){return makesingular(a0);}
void teleport_pager_dep_map_glyphinfo(coordxy a0,coordxy a1,int a2,unsigned int a3,glyph_info * a4){map_glyphinfo(a0,a1,a2,a3,a4);}
void * teleport_pager_dep_memcpy(void *restrict a0,const void *restrict a1,size_t a2){return memcpy(a0,a1,a2);}
struct obj * teleport_pager_dep_mkobj(int a0,boolean a1){return mkobj(a0,a1);}
struct obj * teleport_pager_dep_mksobj(int a0,boolean a1,boolean a2){return mksobj(a0,a1,a2);}
char * teleport_pager_dep_mon_nam(struct monst * a0){return mon_nam(a0);}
int teleport_pager_dep_mon_to_glyph(struct monst* a0,int(*a1)(int)){return mon_to_glyph(u.ustuck,a1);}
char * teleport_pager_dep_mungspaces(char * a0){return mungspaces(a0);}
int teleport_pager_dep_next2u(coordxy a0,coordxy a1){return next2u(a0,a1);}
void teleport_pager_dep_obj_stop_timers(struct obj * a0){obj_stop_timers(a0);}
void teleport_pager_dep_observe_object(struct obj * a0){observe_object(a0);}
boolean teleport_pager_dep_ok_to_quest(void){return ok_to_quest();}
boolean teleport_pager_dep_on_level(d_level * a0,d_level * a1){return on_level(a0,a1);}
boolean teleport_pager_dep_pmatch(const char * a0,const char * a1){return pmatch(a0,a1);}
const char * teleport_pager_dep_pmname(struct permonst * a0,int a1){return pmname(a0,a1);}
void teleport_pager_dep_putmixed(winid a0,int a1,const char* a2){putmixed(a0,a1,a2);}
void teleport_pager_dep_putstr(winid a0,int a1,const char* a2){putstr(a0,a1,a2);}
char * teleport_pager_dep_rndmonnam(char * a0){return rndmonnam(a0);}
int teleport_pager_dep_select_menu(winid a0,int a1,menu_item ** a2){return select_menu(a0,a1,a2);}
int teleport_pager_dep_senseself(void){return senseself();}
void teleport_pager_dep_show_menu_controls(winid a0,boolean a1){show_menu_controls(a0,a1);}
char * teleport_pager_dep_simpleonames(struct obj * a0){return simpleonames(a0);}
const char * teleport_pager_dep_singular(struct obj * a0,char *(*a1)(struct obj *)){return singular(a0,a1);}
struct obj * teleport_pager_dep_sobj_at(int a0,coordxy a1,coordxy a2){return sobj_at(a0,a1,a2);}
long teleport_pager_dep_spot_time_left(coordxy a0,coordxy a1,short a2){return spot_time_left(a0,a1,a2);}
void teleport_pager_dep_start_menu(winid a0,unsigned long a1){start_menu(a0,a1);}
boolean teleport_pager_dep_sticks(struct permonst * a0){return sticks(a0);}
char * teleport_pager_dep_strchr(const char * a0,int a1){return strchr(a0,a1);}
int teleport_pager_dep_strcmp(const char * a0,const char * a1){return strcmp(a0,a1);}
int teleport_pager_dep_strcmpi(const char* a0,const char* a1){return strcmpi(a0,a1);}
char * teleport_pager_dep_strcpy(char *restrict a0,const char *restrict a1){return strcpy(a0,a1);}
char * teleport_pager_dep_strip_newline(char * a0){return strip_newline(a0);}
char * teleport_pager_dep_strkitten(char * a0,char a1){return strkitten(a0,a1);}
unsigned long teleport_pager_dep_strlen(const char * a0){return strlen(a0);}
char * teleport_pager_dep_strncat(char *restrict a0,const char *restrict a1,size_t a2){return strncat(a0,a1,a2);}
int teleport_pager_dep_strncmp(const char * a0,const char * a1,size_t a2){return strncmp(a0,a1,a2);}
int teleport_pager_dep_strncmpi(const char * a0,const char * a1,int a2){return strncmpi(a0,a1,a2);}
char * teleport_pager_dep_strstri(const char * a0,const char * a1){return strstri(a0,a1);}
char * teleport_pager_dep_strsubst(char * a0,const char * a1,const char * a2){return strsubst(a0,a1,a2);}
const char * teleport_pager_dep_surface(coordxy a0,coordxy a1){return surface(a0,a1);}
struct trap * teleport_pager_dep_t_at(coordxy a0,coordxy a1){return t_at(a0,a1);}
char * teleport_pager_dep_tabexpand(char * a0){return tabexpand(a0);}
char * teleport_pager_dep_the(const char * a0){return the(a0);}
char * teleport_pager_dep_trap_predicament(char * a0,int a1,boolean a2){return trap_predicament(a0,a1,a2);}
int teleport_pager_dep_trap_to_glyph(struct trap* a0){return trap_to_glyph(a0);}
const char * teleport_pager_dep_trapname(int a0,boolean a1){return trapname(a0,a1);}
boolean teleport_pager_dep_trapped_chest_at(int a0,coordxy a1,coordxy a2){return trapped_chest_at(a0,a1,a2);}
boolean teleport_pager_dep_trapped_door_at(int a0,coordxy a1,coordxy a2){return trapped_door_at(a0,a1,a2);}
int teleport_pager_dep_u_at(coordxy a0,coordxy a1){return u_at(a0,a1);}
char * teleport_pager_dep_upstart(char * a0){return upstart(a0);}
char * teleport_pager_dep_visctrl(char a0){return visctrl(a0);}
NhRegion * teleport_pager_dep_visible_region_at(coordxy a0,coordxy a1){return visible_region_at(a0,a1);}
char * teleport_pager_dep_y_monnam(struct monst * a0){return y_monnam(a0);}
char teleport_pager_dep_y_n(const char* a0){return y_n(a0);}
char teleport_pager_dep_yn_function(const char * a0,const char * a1,char a2,boolean a3){return yn_function(a0,a1,a2,a3);}
extern void teleport_pager_callback_docontact(void);
extern void teleport_pager_callback_dispfile_help(void);
extern void teleport_pager_callback_dispfile_shelp(void);
extern void teleport_pager_callback_dispfile_optionfile(void);
extern void teleport_pager_callback_dispfile_optmenu(void);
extern void teleport_pager_callback_dispfile_license(void);
extern void teleport_pager_callback_dispfile_debughelp(void);
extern void teleport_pager_callback_dispfile_usagehelp(void);
extern void teleport_pager_callback_hmenu_doextversion(void);
extern void teleport_pager_callback_hmenu_dohistory(void);
extern void teleport_pager_callback_hmenu_dowhatis(void);
extern void teleport_pager_callback_hmenu_dowhatdoes(void);
extern void teleport_pager_callback_hmenu_doextlist(void);
extern void teleport_pager_callback_domenucontrols(void);
void*teleport_pager_function(int kind){switch(kind){case 0:return(void*)xname;case 1:return(void*)doname_with_price;case 2:return(void*)doname_vague_quan;case 3:return(void*)rn2_on_display_rng;case 4:return(void*)doset;case 5:return(void*)do_reqmenu;case 6:return(void*)doset_simple;case 7:return(void*)option_help;case 8:return(void*)dokeylist;case 9:return(void*)teleport_pager_callback_docontact;case 10:return(void*)teleport_pager_callback_dispfile_help;case 11:return(void*)teleport_pager_callback_dispfile_shelp;case 12:return(void*)teleport_pager_callback_dispfile_optionfile;case 13:return(void*)teleport_pager_callback_dispfile_optmenu;case 14:return(void*)teleport_pager_callback_dispfile_license;case 15:return(void*)teleport_pager_callback_dispfile_debughelp;case 16:return(void*)teleport_pager_callback_dispfile_usagehelp;case 17:return(void*)teleport_pager_callback_hmenu_doextversion;case 18:return(void*)teleport_pager_callback_hmenu_dohistory;case 19:return(void*)teleport_pager_callback_hmenu_dowhatis;case 20:return(void*)teleport_pager_callback_hmenu_dowhatdoes;case 21:return(void*)teleport_pager_callback_hmenu_doextlist;case 22:return(void*)teleport_pager_callback_domenucontrols;}abort();}
void teleport_pager_call_help(void(*f)(void)){(*f)();}
static char teleport_pager_literals[5725];
void*teleport_pager_literal_storage(void){return teleport_pager_literals;}
size_t teleport_pager_literal_capacity(void){return sizeof teleport_pager_literals;}
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(coordxy)==2&&sizeof(boolean)==1&&sizeof(va_list)==8,"Review PAGER ABI");
