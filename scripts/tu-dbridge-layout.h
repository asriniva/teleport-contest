/* Native data layout and constants; drawbridge algorithms stay in dbridge.js. */
#include "hack.h"
#include <stddef.h>
struct dbridge_meta {const char*name;size_t value;};
#define DBRIDGE_META(k,v) {#k,(size_t)(v)}
static const struct dbridge_meta dbridge_layout[] = {
DBRIDGE_META(pointerSize,sizeof(void*)),
DBRIDGE_META(longSize,sizeof(long)),
DBRIDGE_META(intSize,sizeof(int)),
DBRIDGE_META(coordSize,sizeof(coordxy)),
DBRIDGE_META(booleanSize,sizeof(boolean)),
DBRIDGE_META(entitySize,sizeof(struct entity)),
DBRIDGE_META(monsterSize,sizeof(struct monst)),
DBRIDGE_META(permonstSize,sizeof(struct permonst)),
DBRIDGE_META(objectSize,sizeof(struct obj)),
DBRIDGE_META(rmSize,sizeof(struct rm)),
DBRIDGE_META(propSize,sizeof(struct prop)),
DBRIDGE_META(coordStructSize,sizeof(coord)),
DBRIDGE_META(levelSize,sizeof(d_level)),
DBRIDGE_META(genderSize,sizeof(struct Gender)),
DBRIDGE_META(phraseSize,80),
DBRIDGE_META(entity_emon,offsetof(struct entity,emon)),
DBRIDGE_META(entity_emon_size,sizeof(((struct entity*)0)->emon)),
DBRIDGE_META(entity_edata,offsetof(struct entity,edata)),
DBRIDGE_META(entity_edata_size,sizeof(((struct entity*)0)->edata)),
DBRIDGE_META(entity_ex,offsetof(struct entity,ex)),
DBRIDGE_META(entity_ex_size,sizeof(((struct entity*)0)->ex)),
DBRIDGE_META(entity_ey,offsetof(struct entity,ey)),
DBRIDGE_META(entity_ey_size,sizeof(((struct entity*)0)->ey)),
DBRIDGE_META(mon_data,offsetof(struct monst,data)),
DBRIDGE_META(mon_data_size,sizeof(((struct monst*)0)->data)),
DBRIDGE_META(mon_mx,offsetof(struct monst,mx)),
DBRIDGE_META(mon_mx_size,sizeof(((struct monst*)0)->mx)),
DBRIDGE_META(mon_my,offsetof(struct monst,my)),
DBRIDGE_META(mon_my_size,sizeof(((struct monst*)0)->my)),
DBRIDGE_META(mon_mhp,offsetof(struct monst,mhp)),
DBRIDGE_META(mon_mhp_size,sizeof(((struct monst*)0)->mhp)),
DBRIDGE_META(pm_mflags1,offsetof(struct permonst,mflags1)),
DBRIDGE_META(pm_mflags1_size,sizeof(((struct permonst*)0)->mflags1)),
DBRIDGE_META(pm_mlet,offsetof(struct permonst,mlet)),
DBRIDGE_META(pm_mlet_size,sizeof(((struct permonst*)0)->mlet)),
DBRIDGE_META(pm_mmove,offsetof(struct permonst,mmove)),
DBRIDGE_META(pm_mmove_size,sizeof(((struct permonst*)0)->mmove)),
DBRIDGE_META(obj_ox,offsetof(struct obj,ox)),
DBRIDGE_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
DBRIDGE_META(obj_oy,offsetof(struct obj,oy)),
DBRIDGE_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
DBRIDGE_META(rm_typ,offsetof(struct rm,typ)),
DBRIDGE_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
DBRIDGE_META(u_ux,offsetof(struct you,ux)),
DBRIDGE_META(u_ux_size,sizeof(((struct you*)0)->ux)),
DBRIDGE_META(u_uy,offsetof(struct you,uy)),
DBRIDGE_META(u_uy_size,sizeof(((struct you*)0)->uy)),
DBRIDGE_META(u_uz,offsetof(struct you,uz)),
DBRIDGE_META(u_uz_size,sizeof(((struct you*)0)->uz)),
DBRIDGE_META(u_uprops,offsetof(struct you,uprops)),
DBRIDGE_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
DBRIDGE_META(u_usteed,offsetof(struct you,usteed)),
DBRIDGE_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
DBRIDGE_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
DBRIDGE_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
DBRIDGE_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
DBRIDGE_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
DBRIDGE_META(prop_blocked,offsetof(struct prop,blocked)),
DBRIDGE_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
DBRIDGE_META(coord_x,offsetof(coord,x)),
DBRIDGE_META(coord_x_size,sizeof(((coord*)0)->x)),
DBRIDGE_META(coord_y,offsetof(coord,y)),
DBRIDGE_META(coord_y_size,sizeof(((coord*)0)->y)),
DBRIDGE_META(level_dnum,offsetof(d_level,dnum)),
DBRIDGE_META(level_dnum_size,sizeof(((d_level*)0)->dnum)),
DBRIDGE_META(level_dlevel,offsetof(d_level,dlevel)),
DBRIDGE_META(level_dlevel_size,sizeof(((d_level*)0)->dlevel)),
DBRIDGE_META(gender_he,offsetof(struct Gender,he)),
DBRIDGE_META(gender_he_size,sizeof(((struct Gender*)0)->he)),
DBRIDGE_META(occupants,(char*)&go.occupants-(char*)&go),
DBRIDGE_META(youmonst,(char*)&gy.youmonst-(char*)&gy),
DBRIDGE_META(locations,(char*)&svl.level.locations-(char*)&svl),
DBRIDGE_META(objects,(char*)&svl.level.objects-(char*)&svl),
DBRIDGE_META(monsters,(char*)&svl.level.monsters-(char*)&svl),
DBRIDGE_META(juiblex,(char*)&juiblex_level-(char*)&svd),
DBRIDGE_META(stronghold,(char*)&stronghold_level-(char*)&svd),
DBRIDGE_META(water,(char*)&water_level-(char*)&svd),
DBRIDGE_META(killerFormat,(char*)&svk.killer.format-(char*)&svk),
DBRIDGE_META(killerName,(char*)&svk.killer.name-(char*)&svk),
DBRIDGE_META(monMoving,(char*)&svc.context.mon_moving-(char*)&svc),
DBRIDGE_META(multi,(char*)&gm.multi-(char*)&gm),
DBRIDGE_META(vizArray,(char*)&gv.viz_array-(char*)&gv),
DBRIDGE_META(lastMsg,(char*)&iflags.last_msg-(char*)&iflags),
DBRIDGE_META(ENTITIES,ENTITIES),
DBRIDGE_META(POOL,POOL),
DBRIDGE_META(HWALL,HWALL),
DBRIDGE_META(MOAT,MOAT),
DBRIDGE_META(WATER,WATER),
DBRIDGE_META(LAVAPOOL,LAVAPOOL),
DBRIDGE_META(LAVAWALL,LAVAWALL),
DBRIDGE_META(DRAWBRIDGE_UP,DRAWBRIDGE_UP),
DBRIDGE_META(DRAWBRIDGE_DOWN,DRAWBRIDGE_DOWN),
DBRIDGE_META(DB_UNDER,DB_UNDER),
DBRIDGE_META(DB_LAVA,DB_LAVA),
DBRIDGE_META(DB_ICE,DB_ICE),
DBRIDGE_META(ICE,ICE),
DBRIDGE_META(DB_MOAT,DB_MOAT),
DBRIDGE_META(STONE,STONE),
DBRIDGE_META(DOOR,DOOR),
DBRIDGE_META(DBWALL,DBWALL),
DBRIDGE_META(DB_DIR,DB_DIR),
DBRIDGE_META(DB_WEST,DB_WEST),
DBRIDGE_META(DB_EAST,DB_EAST),
DBRIDGE_META(DB_SOUTH,DB_SOUTH),
DBRIDGE_META(DB_NORTH,DB_NORTH),
DBRIDGE_META(D_NODOOR,D_NODOOR),
DBRIDGE_META(W_NONDIGGABLE,W_NONDIGGABLE),
DBRIDGE_META(PM_LONG_WORM_TAIL,PM_LONG_WORM_TAIL),
DBRIDGE_META(XKILL_NOMSG,XKILL_NOMSG),
DBRIDGE_META(XKILL_NOCORPSE,XKILL_NOCORPSE),
DBRIDGE_META(XKILL_NOCONDUCT,XKILL_NOCONDUCT),
DBRIDGE_META(XKILL_GIVEMSG,XKILL_GIVEMSG),
DBRIDGE_META(AD_DGST,AD_DGST),
DBRIDGE_META(AD_PHYS,AD_PHYS),
DBRIDGE_META(DROWNING,DROWNING),
DBRIDGE_META(BURNING,BURNING),
DBRIDGE_META(CRUSHING,CRUSHING),
DBRIDGE_META(KILLED_BY_AN,KILLED_BY_AN),
DBRIDGE_META(NO_KILLER_PREFIX,NO_KILLER_PREFIX),
DBRIDGE_META(TELEDS_NO_FLAGS,TELEDS_NO_FLAGS),
DBRIDGE_META(BOULDER,BOULDER),
DBRIDGE_META(ROOM,ROOM),
DBRIDGE_META(ICED_MOAT,ICED_MOAT),
DBRIDGE_META(IRON_CHAIN,IRON_CHAIN),
DBRIDGE_META(MAY_HIT,MAY_HIT),
DBRIDGE_META(WWALKING,WWALKING),
DBRIDGE_META(MAGICAL_BREATHING,MAGICAL_BREATHING),
DBRIDGE_META(SWIMMING,SWIMMING),
DBRIDGE_META(FLYING,FLYING),
DBRIDGE_META(LEVITATION,LEVITATION),
DBRIDGE_META(PASSES_WALLS,PASSES_WALLS),
DBRIDGE_META(FUMBLING,FUMBLING),
DBRIDGE_META(CONFUSION,CONFUSION),
DBRIDGE_META(STUNNED,STUNNED),
DBRIDGE_META(HALLUC,HALLUC),
DBRIDGE_META(HALLUC_RES,HALLUC_RES),
DBRIDGE_META(DEAF,DEAF),
DBRIDGE_META(M1_FLY,M1_FLY),
DBRIDGE_META(M1_SWIM,M1_SWIM),
DBRIDGE_META(M1_BREATHLESS,M1_BREATHLESS),
DBRIDGE_META(M1_AMPHIBIOUS,M1_AMPHIBIOUS),
DBRIDGE_META(M1_WALLWALK,M1_WALLWALK),
DBRIDGE_META(S_GHOST,S_GHOST),
DBRIDGE_META(S_EYE,S_EYE),
DBRIDGE_META(S_LIGHT,S_LIGHT),
DBRIDGE_META(PM_FIRE_ELEMENTAL,PM_FIRE_ELEMENTAL),
DBRIDGE_META(PM_SALAMANDER,PM_SALAMANDER),
DBRIDGE_META(COLNO,COLNO),
DBRIDGE_META(ROWNO,ROWNO),
DBRIDGE_META(IN_SIGHT,IN_SIGHT),
DBRIDGE_META(PRONOUN_HALLU,PRONOUN_HALLU),
DBRIDGE_META(PM_HUMAN,PM_HUMAN),
DBRIDGE_META(PM_GHOST,PM_GHOST),
DBRIDGE_META(PM_LONG_WORM,PM_LONG_WORM),
DBRIDGE_META(PM_GIANT_BAT,PM_GIANT_BAT),
DBRIDGE_META(PM_GIANT_EEL,PM_GIANT_EEL),
DBRIDGE_META(PM_XORN,PM_XORN),
DBRIDGE_META(PM_FLOATING_EYE,PM_FLOATING_EYE),
#ifdef DEBUG
DBRIDGE_META(config_DEBUG,1),
#else
DBRIDGE_META(config_DEBUG,0),
#endif
#ifdef D_DEBUG
DBRIDGE_META(config_D_DEBUG,1),
#else
DBRIDGE_META(config_D_DEBUG,0),
#endif
#ifdef EXTRA_SANITY_CHECKS
DBRIDGE_META(config_EXTRA_SANITY_CHECKS,1),
#else
DBRIDGE_META(config_EXTRA_SANITY_CHECKS,0),
#endif
};
size_t probe_context_size(void){return sizeof(struct entity);}
int probe_layout_count(void){return (int)(sizeof dbridge_layout/sizeof dbridge_layout[0]);}
const char*probe_layout_name(int i){return dbridge_layout[i].name;}
size_t probe_layout_value(int i){return dbridge_layout[i].value;}
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0,"review DBRIDGE ABI");
_Static_assert(sizeof(((struct entity*)0)->emon)==8,"review DBRIDGE entity.emon");
_Static_assert(sizeof(((struct entity*)0)->edata)==8,"review DBRIDGE entity.edata");
_Static_assert(sizeof(((struct entity*)0)->ex)==4 && (((__typeof__(((struct entity*)0)->ex))-1<0)==1),"review DBRIDGE entity.ex");
_Static_assert(sizeof(((struct entity*)0)->ey)==4 && (((__typeof__(((struct entity*)0)->ey))-1<0)==1),"review DBRIDGE entity.ey");
_Static_assert(sizeof(((struct monst*)0)->data)==8,"review DBRIDGE mon.data");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"review DBRIDGE mon.mx");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"review DBRIDGE mon.my");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"review DBRIDGE mon.mhp");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"review DBRIDGE pm.mflags1");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"review DBRIDGE pm.mlet");
_Static_assert(sizeof(((struct permonst*)0)->mmove)==1 && (((__typeof__(((struct permonst*)0)->mmove))-1<0)==1),"review DBRIDGE pm.mmove");
_Static_assert(sizeof(((struct obj*)0)->ox)==2 && (((__typeof__(((struct obj*)0)->ox))-1<0)==1),"review DBRIDGE obj.ox");
_Static_assert(sizeof(((struct obj*)0)->oy)==2 && (((__typeof__(((struct obj*)0)->oy))-1<0)==1),"review DBRIDGE obj.oy");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"review DBRIDGE rm.typ");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"review DBRIDGE u.ux");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"review DBRIDGE u.uy");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"review DBRIDGE u.usteed");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"review DBRIDGE prop.intrinsic");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"review DBRIDGE prop.extrinsic");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"review DBRIDGE prop.blocked");
_Static_assert(sizeof(((coord*)0)->x)==2 && (((__typeof__(((coord*)0)->x))-1<0)==1),"review DBRIDGE coord.x");
_Static_assert(sizeof(((coord*)0)->y)==2 && (((__typeof__(((coord*)0)->y))-1<0)==1),"review DBRIDGE coord.y");
_Static_assert(sizeof(((d_level*)0)->dnum)==2 && (((__typeof__(((d_level*)0)->dnum))-1<0)==1),"review DBRIDGE level.dnum");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2 && (((__typeof__(((d_level*)0)->dlevel))-1<0)==1),"review DBRIDGE level.dlevel");
_Static_assert(sizeof(((struct Gender*)0)->he)==8,"review DBRIDGE gender.he");
_Static_assert(sizeof(svk.killer.format)==4 && (((__typeof__(svk.killer.format))-1<0)==1),"review DBRIDGE svk.killer.format");
_Static_assert(sizeof(svc.context.mon_moving)==1 && (((__typeof__(svc.context.mon_moving))-1<0)==1),"review DBRIDGE svc.context.mon_moving");
_Static_assert(sizeof(gm.multi)==8 && (((__typeof__(gm.multi))-1<0)==1),"review DBRIDGE gm.multi");
_Static_assert(sizeof(iflags.last_msg)==4 && (((__typeof__(iflags.last_msg))-1<0)==1),"review DBRIDGE iflags.last_msg");
