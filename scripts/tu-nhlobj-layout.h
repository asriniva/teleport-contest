/* NHLOBJ independent compiler field/ABI layout. */
#ifndef TELEPORT_NHLOBJ_LAYOUT_H
#define TELEPORT_NHLOBJ_LAYOUT_H
#include "hack.h"
#include <stddef.h>
struct teleport_nhlobj_userdata {int state;struct obj*obj;};
#ifdef TELEPORT_NHLOBJ_VALIDATE_SOURCE
_Static_assert(sizeof(struct _lua_obj)==sizeof(struct teleport_nhlobj_userdata),"actual userdata size");
_Static_assert(offsetof(struct _lua_obj,state)==offsetof(struct teleport_nhlobj_userdata,state),"actual userdata state");
_Static_assert(offsetof(struct _lua_obj,obj)==offsetof(struct teleport_nhlobj_userdata,obj),"actual userdata object");
#endif
#define NHLOBJ_META(k,v) {#k,(size_t)(v)}
static const struct {const char*name;size_t value;} nhlobj_layout[]={
NHLOBJ_META(pointerSize,sizeof(void*)),
NHLOBJ_META(intSize,sizeof(int)),
NHLOBJ_META(longSize,sizeof(long)),
NHLOBJ_META(luaIntegerSize,sizeof(lua_Integer)),
NHLOBJ_META(luaNumberSize,sizeof(lua_Number)),
NHLOBJ_META(luaIntegerSigned,((lua_Integer)-1<0)),
NHLOBJ_META(floorObjects,offsetof(__typeof__(svl),level.objects)),
NHLOBJ_META(fobj,offsetof(__typeof__(svl),level.objlist)),
NHLOBJ_META(methodCount,16),
NHLOBJ_META(metaCount,2),
NHLOBJ_META(userdataSize,sizeof(struct teleport_nhlobj_userdata)),
NHLOBJ_META(userdata_state,offsetof(struct teleport_nhlobj_userdata,state)),
NHLOBJ_META(userdata_state_size,sizeof(((struct teleport_nhlobj_userdata*)0)->state)),
NHLOBJ_META(userdata_obj,offsetof(struct teleport_nhlobj_userdata,obj)),
NHLOBJ_META(userdata_obj_size,sizeof(((struct teleport_nhlobj_userdata*)0)->obj)),
NHLOBJ_META(objSize,sizeof(struct obj)),
NHLOBJ_META(obj_nobj,offsetof(struct obj,nobj)),
NHLOBJ_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
NHLOBJ_META(obj_nexthere,offsetof(struct obj,nexthere)),
NHLOBJ_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
NHLOBJ_META(obj_cobj,offsetof(struct obj,cobj)),
NHLOBJ_META(obj_cobj_size,sizeof(((struct obj*)0)->cobj)),
NHLOBJ_META(obj_ocontainer,offsetof(struct obj,ocontainer)),
NHLOBJ_META(obj_ocontainer_size,sizeof(((struct obj*)0)->ocontainer)),
NHLOBJ_META(obj_oextra,offsetof(struct obj,oextra)),
NHLOBJ_META(obj_oextra_size,sizeof(((struct obj*)0)->oextra)),
NHLOBJ_META(obj_o_id,offsetof(struct obj,o_id)),
NHLOBJ_META(obj_o_id_size,sizeof(((struct obj*)0)->o_id)),
NHLOBJ_META(obj_ox,offsetof(struct obj,ox)),
NHLOBJ_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
NHLOBJ_META(obj_oy,offsetof(struct obj,oy)),
NHLOBJ_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
NHLOBJ_META(obj_otyp,offsetof(struct obj,otyp)),
NHLOBJ_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
NHLOBJ_META(obj_owt,offsetof(struct obj,owt)),
NHLOBJ_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
NHLOBJ_META(obj_quan,offsetof(struct obj,quan)),
NHLOBJ_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
NHLOBJ_META(obj_spe,offsetof(struct obj,spe)),
NHLOBJ_META(obj_spe_size,sizeof(((struct obj*)0)->spe)),
NHLOBJ_META(obj_oclass,offsetof(struct obj,oclass)),
NHLOBJ_META(obj_oclass_size,sizeof(((struct obj*)0)->oclass)),
NHLOBJ_META(obj_invlet,offsetof(struct obj,invlet)),
NHLOBJ_META(obj_invlet_size,sizeof(((struct obj*)0)->invlet)),
NHLOBJ_META(obj_where,offsetof(struct obj,where)),
NHLOBJ_META(obj_where_size,sizeof(((struct obj*)0)->where)),
NHLOBJ_META(obj_corpsenm,offsetof(struct obj,corpsenm)),
NHLOBJ_META(obj_corpsenm_size,sizeof(((struct obj*)0)->corpsenm)),
NHLOBJ_META(obj_usecount,offsetof(struct obj,usecount)),
NHLOBJ_META(obj_usecount_size,sizeof(((struct obj*)0)->usecount)),
NHLOBJ_META(obj_oeaten,offsetof(struct obj,oeaten)),
NHLOBJ_META(obj_oeaten_size,sizeof(((struct obj*)0)->oeaten)),
NHLOBJ_META(obj_age,offsetof(struct obj,age)),
NHLOBJ_META(obj_age_size,sizeof(((struct obj*)0)->age)),
NHLOBJ_META(obj_owornmask,offsetof(struct obj,owornmask)),
NHLOBJ_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
NHLOBJ_META(obj_lua_ref_cnt,offsetof(struct obj,lua_ref_cnt)),
NHLOBJ_META(obj_lua_ref_cnt_size,sizeof(((struct obj*)0)->lua_ref_cnt)),
NHLOBJ_META(extraSize,sizeof(struct oextra)),
NHLOBJ_META(extra_oname,offsetof(struct oextra,oname)),
NHLOBJ_META(extra_oname_size,sizeof(((struct oextra*)0)->oname)),
NHLOBJ_META(clsSize,sizeof(struct objclass)),
NHLOBJ_META(cls_oc_name_idx,offsetof(struct objclass,oc_name_idx)),
NHLOBJ_META(cls_oc_name_idx_size,sizeof(((struct objclass*)0)->oc_name_idx)),
NHLOBJ_META(cls_oc_descr_idx,offsetof(struct objclass,oc_descr_idx)),
NHLOBJ_META(cls_oc_descr_idx_size,sizeof(((struct objclass*)0)->oc_descr_idx)),
NHLOBJ_META(cls_oc_uname,offsetof(struct objclass,oc_uname)),
NHLOBJ_META(cls_oc_uname_size,sizeof(((struct objclass*)0)->oc_uname)),
NHLOBJ_META(cls_oc_oprop,offsetof(struct objclass,oc_oprop)),
NHLOBJ_META(cls_oc_oprop_size,sizeof(((struct objclass*)0)->oc_oprop)),
NHLOBJ_META(cls_oc_class,offsetof(struct objclass,oc_class)),
NHLOBJ_META(cls_oc_class_size,sizeof(((struct objclass*)0)->oc_class)),
NHLOBJ_META(cls_oc_delay,offsetof(struct objclass,oc_delay)),
NHLOBJ_META(cls_oc_delay_size,sizeof(((struct objclass*)0)->oc_delay)),
NHLOBJ_META(cls_oc_color,offsetof(struct objclass,oc_color)),
NHLOBJ_META(cls_oc_color_size,sizeof(((struct objclass*)0)->oc_color)),
NHLOBJ_META(cls_oc_prob,offsetof(struct objclass,oc_prob)),
NHLOBJ_META(cls_oc_prob_size,sizeof(((struct objclass*)0)->oc_prob)),
NHLOBJ_META(cls_oc_weight,offsetof(struct objclass,oc_weight)),
NHLOBJ_META(cls_oc_weight_size,sizeof(((struct objclass*)0)->oc_weight)),
NHLOBJ_META(cls_oc_cost,offsetof(struct objclass,oc_cost)),
NHLOBJ_META(cls_oc_cost_size,sizeof(((struct objclass*)0)->oc_cost)),
NHLOBJ_META(cls_oc_wsdam,offsetof(struct objclass,oc_wsdam)),
NHLOBJ_META(cls_oc_wsdam_size,sizeof(((struct objclass*)0)->oc_wsdam)),
NHLOBJ_META(cls_oc_wldam,offsetof(struct objclass,oc_wldam)),
NHLOBJ_META(cls_oc_wldam_size,sizeof(((struct objclass*)0)->oc_wldam)),
NHLOBJ_META(cls_oc_nutrition,offsetof(struct objclass,oc_nutrition)),
NHLOBJ_META(cls_oc_nutrition_size,sizeof(((struct objclass*)0)->oc_nutrition)),
NHLOBJ_META(cls_oc_skill,offsetof(struct objclass,oc_skill)),
NHLOBJ_META(cls_oc_skill_size,sizeof(((struct objclass*)0)->oc_skill)),
NHLOBJ_META(descrSize,sizeof(struct objdescr)),
NHLOBJ_META(descr_oc_name,offsetof(struct objdescr,oc_name)),
NHLOBJ_META(descr_oc_name_size,sizeof(((struct objdescr*)0)->oc_name)),
NHLOBJ_META(descr_oc_descr,offsetof(struct objdescr,oc_descr)),
NHLOBJ_META(descr_oc_descr_size,sizeof(((struct objdescr*)0)->oc_descr)),
NHLOBJ_META(pmSize,sizeof(struct permonst)),
NHLOBJ_META(pm_pmnames,offsetof(struct permonst,pmnames)),
NHLOBJ_META(pm_pmnames_size,sizeof(((struct permonst*)0)->pmnames)),
NHLOBJ_META(classsymSize,sizeof(struct class_sym)),
NHLOBJ_META(classsym_sym,offsetof(struct class_sym,sym)),
NHLOBJ_META(classsym_sym_size,sizeof(((struct class_sym*)0)->sym)),
NHLOBJ_META(coordSize,sizeof(coord)),
NHLOBJ_META(coord_x,offsetof(coord,x)),
NHLOBJ_META(coord_x_size,sizeof(((coord*)0)->x)),
NHLOBJ_META(coord_y,offsetof(coord,y)),
NHLOBJ_META(coord_y_size,sizeof(((coord*)0)->y)),
NHLOBJ_META(regSize,sizeof(luaL_Reg)),
NHLOBJ_META(reg_name,offsetof(luaL_Reg,name)),
NHLOBJ_META(reg_name_size,sizeof(((luaL_Reg*)0)->name)),
NHLOBJ_META(reg_func,offsetof(luaL_Reg,func)),
NHLOBJ_META(reg_func_size,sizeof(((luaL_Reg*)0)->func)),
NHLOBJ_META(BAG_OF_TRICKS,BAG_OF_TRICKS),
NHLOBJ_META(CHEST,CHEST),
NHLOBJ_META(FIRST_OBJECT,FIRST_OBJECT),
NHLOBJ_META(ROT_ORGANIC,ROT_ORGANIC),
NHLOBJ_META(ARROW,ARROW),
NHLOBJ_META(SHRINK_GLOB,SHRINK_GLOB),
NHLOBJ_META(OBJ_LUAFREE,OBJ_LUAFREE),
NHLOBJ_META(LUA_VERSION_NUM,LUA_VERSION_NUM),
NHLOBJ_META(LUA_OK,LUA_OK),
NHLOBJ_META(TOOL_CLASS,TOOL_CLASS),
NHLOBJ_META(FIGURINE,FIGURINE),
NHLOBJ_META(CORPSE,CORPSE),
NHLOBJ_META(CORPSTAT_HISTORIC,CORPSTAT_HISTORIC),
NHLOBJ_META(POTION_CLASS,POTION_CLASS),
NHLOBJ_META(LUA_TNUMBER,LUA_TNUMBER),
NHLOBJ_META(CORPSTAT_MALE,CORPSTAT_MALE),
NHLOBJ_META(BURN_OBJECT,BURN_OBJECT),
NHLOBJ_META(OBJ_FREE,OBJ_FREE),
NHLOBJ_META(PM_GHOST,PM_GHOST),
NHLOBJ_META(ROCK,ROCK),
NHLOBJ_META(EGG,EGG),
NHLOBJ_META(MAXOCLASSES,MAXOCLASSES),
NHLOBJ_META(WEAPON_CLASS,WEAPON_CLASS),
NHLOBJ_META(P_BOW,P_BOW),
NHLOBJ_META(ROWNO,ROWNO),
NHLOBJ_META(COLNO,COLNO),
NHLOBJ_META(LUA_TTABLE,LUA_TTABLE),
NHLOBJ_META(P_SHURIKEN,P_SHURIKEN),
NHLOBJ_META(OBJ_INVENT,OBJ_INVENT),
NHLOBJ_META(LUA_REGISTRYINDEX,LUA_REGISTRYINDEX),
NHLOBJ_META(ZOMBIFY_MON,ZOMBIFY_MON),
NHLOBJ_META(ROT_CORPSE,ROT_CORPSE),
NHLOBJ_META(REVIVE_MON,REVIVE_MON),
NHLOBJ_META(NUM_TIME_FUNCS,NUM_TIME_FUNCS),
NHLOBJ_META(TIN,TIN),
NHLOBJ_META(NUM_OBJECTS,NUM_OBJECTS),
NHLOBJ_META(LARGE_BOX,LARGE_BOX),
NHLOBJ_META(NUMMONS,NUMMONS),
NHLOBJ_META(FIG_TRANSFORM,FIG_TRANSFORM),
NHLOBJ_META(DAGGER,DAGGER),
NHLOBJ_META(LUA_TUSERDATA,LUA_TUSERDATA),
NHLOBJ_META(HATCH_EGG,HATCH_EGG),
NHLOBJ_META(CORPSTAT_FEMALE,CORPSTAT_FEMALE),
NHLOBJ_META(BUFSZ,BUFSZ),
NHLOBJ_META(LUA_TSTRING,LUA_TSTRING),
NHLOBJ_META(OBJ_FLOOR,OBJ_FLOOR),
NHLOBJ_META(POT_HEALING,POT_HEALING),
NHLOBJ_META(LUAL_NUMSIZES,LUAL_NUMSIZES),
NHLOBJ_META(PM_HUMAN,PM_HUMAN),
NHLOBJ_META(STATUE,STATUE),
NHLOBJ_META(NON_PM,NON_PM),
NHLOBJ_META(RANDOM_CLASS,RANDOM_CLASS),
NHLOBJ_META(TIMER_OBJECT,TIMER_OBJECT),
NHLOBJ_META(NEUTRAL,NEUTRAL),
NHLOBJ_META(OBJ_CONTAINED,OBJ_CONTAINED),
};
_Static_assert(sizeof(((struct teleport_nhlobj_userdata*)0)->state)==4,"userdata_state width");
_Static_assert(((__typeof__(((struct teleport_nhlobj_userdata*)0)->state))-1 < 0),"userdata_state signedness");
_Static_assert(sizeof(((struct teleport_nhlobj_userdata*)0)->obj)==8,"userdata_obj pointer width");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"obj_nobj pointer width");
_Static_assert(sizeof(((struct obj*)0)->nexthere)==8,"obj_nexthere pointer width");
_Static_assert(sizeof(((struct obj*)0)->cobj)==8,"obj_cobj pointer width");
_Static_assert(sizeof(((struct obj*)0)->ocontainer)==8,"obj_ocontainer pointer width");
_Static_assert(sizeof(((struct obj*)0)->oextra)==8,"obj_oextra pointer width");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4,"obj_o_id width");
_Static_assert(((__typeof__(((struct obj*)0)->o_id))-1 > 0),"obj_o_id signedness");
_Static_assert(sizeof(((struct obj*)0)->ox)==2,"obj_ox width");
_Static_assert(((__typeof__(((struct obj*)0)->ox))-1 < 0),"obj_ox signedness");
_Static_assert(sizeof(((struct obj*)0)->oy)==2,"obj_oy width");
_Static_assert(((__typeof__(((struct obj*)0)->oy))-1 < 0),"obj_oy signedness");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2,"obj_otyp width");
_Static_assert(((__typeof__(((struct obj*)0)->otyp))-1 < 0),"obj_otyp signedness");
_Static_assert(sizeof(((struct obj*)0)->owt)==4,"obj_owt width");
_Static_assert(((__typeof__(((struct obj*)0)->owt))-1 > 0),"obj_owt signedness");
_Static_assert(sizeof(((struct obj*)0)->quan)==8,"obj_quan width");
_Static_assert(((__typeof__(((struct obj*)0)->quan))-1 < 0),"obj_quan signedness");
_Static_assert(sizeof(((struct obj*)0)->spe)==1,"obj_spe width");
_Static_assert(((__typeof__(((struct obj*)0)->spe))-1 < 0),"obj_spe signedness");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1,"obj_oclass width");
_Static_assert(((__typeof__(((struct obj*)0)->oclass))-1 < 0),"obj_oclass signedness");
_Static_assert(sizeof(((struct obj*)0)->invlet)==1,"obj_invlet width");
_Static_assert(((__typeof__(((struct obj*)0)->invlet))-1 < 0),"obj_invlet signedness");
_Static_assert(sizeof(((struct obj*)0)->where)==1,"obj_where width");
_Static_assert(((__typeof__(((struct obj*)0)->where))-1 < 0),"obj_where signedness");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4,"obj_corpsenm width");
_Static_assert(((__typeof__(((struct obj*)0)->corpsenm))-1 < 0),"obj_corpsenm signedness");
_Static_assert(sizeof(((struct obj*)0)->usecount)==4,"obj_usecount width");
_Static_assert(((__typeof__(((struct obj*)0)->usecount))-1 < 0),"obj_usecount signedness");
_Static_assert(sizeof(((struct obj*)0)->oeaten)==4,"obj_oeaten width");
_Static_assert(((__typeof__(((struct obj*)0)->oeaten))-1 > 0),"obj_oeaten signedness");
_Static_assert(sizeof(((struct obj*)0)->age)==8,"obj_age width");
_Static_assert(((__typeof__(((struct obj*)0)->age))-1 < 0),"obj_age signedness");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8,"obj_owornmask width");
_Static_assert(((__typeof__(((struct obj*)0)->owornmask))-1 < 0),"obj_owornmask signedness");
_Static_assert(sizeof(((struct obj*)0)->lua_ref_cnt)==4,"obj_lua_ref_cnt width");
_Static_assert(((__typeof__(((struct obj*)0)->lua_ref_cnt))-1 > 0),"obj_lua_ref_cnt signedness");
_Static_assert(sizeof(((struct oextra*)0)->oname)==8,"extra_oname pointer width");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2,"cls_oc_name_idx width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_name_idx))-1 < 0),"cls_oc_name_idx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_descr_idx)==2,"cls_oc_descr_idx width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_descr_idx))-1 < 0),"cls_oc_descr_idx signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_uname)==8,"cls_oc_uname pointer width");
_Static_assert(sizeof(((struct objclass*)0)->oc_oprop)==1,"cls_oc_oprop width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_oprop))-1 > 0),"cls_oc_oprop signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_class)==1,"cls_oc_class width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_class))-1 < 0),"cls_oc_class signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_delay)==1,"cls_oc_delay width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_delay))-1 < 0),"cls_oc_delay signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_color)==1,"cls_oc_color width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_color))-1 > 0),"cls_oc_color signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_prob)==2,"cls_oc_prob width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_prob))-1 < 0),"cls_oc_prob signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_weight)==4,"cls_oc_weight width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_weight))-1 > 0),"cls_oc_weight signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_cost)==2,"cls_oc_cost width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_cost))-1 < 0),"cls_oc_cost signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_wsdam)==1,"cls_oc_wsdam width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_wsdam))-1 < 0),"cls_oc_wsdam signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_wldam)==1,"cls_oc_wldam width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_wldam))-1 < 0),"cls_oc_wldam signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_nutrition)==2,"cls_oc_nutrition width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_nutrition))-1 > 0),"cls_oc_nutrition signedness");
_Static_assert(sizeof(((struct objclass*)0)->oc_skill)==1,"cls_oc_skill width");
_Static_assert(((__typeof__(((struct objclass*)0)->oc_skill))-1 < 0),"cls_oc_skill signedness");
_Static_assert(sizeof(((struct objdescr*)0)->oc_name)==8,"descr_oc_name pointer width");
_Static_assert(sizeof(((struct objdescr*)0)->oc_descr)==8,"descr_oc_descr pointer width");
_Static_assert(sizeof(((struct class_sym*)0)->sym)==1,"classsym_sym width");
_Static_assert(((__typeof__(((struct class_sym*)0)->sym))-1 < 0),"classsym_sym signedness");
_Static_assert(sizeof(((coord*)0)->x)==2,"coord_x width");
_Static_assert(((__typeof__(((coord*)0)->x))-1 < 0),"coord_x signedness");
_Static_assert(sizeof(((coord*)0)->y)==2,"coord_y width");
_Static_assert(((__typeof__(((coord*)0)->y))-1 < 0),"coord_y signedness");
_Static_assert(sizeof(((luaL_Reg*)0)->name)==8,"reg_name pointer width");
_Static_assert(sizeof(((luaL_Reg*)0)->func)==8,"reg_func pointer width");
size_t probe_context_size(void){return sizeof(struct teleport_nhlobj_userdata);}
int probe_layout_count(void){return sizeof nhlobj_layout/sizeof nhlobj_layout[0];}
const char*probe_layout_name(int i){return nhlobj_layout[i].name;}
size_t probe_layout_value(int i){return nhlobj_layout[i].value;}
#endif
