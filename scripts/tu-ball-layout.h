/* Compiler-owned layout only; all ball and chain policy stays in ball.js. */
#include "hack.h"
#include <stddef.h>
struct ball_meta {const char *name;size_t value;};
#define BALL_META(k,v) {#k,(size_t)(v)}
static const struct ball_meta ball_layout[] = {
BALL_META(pointerSize,sizeof(void*)),
BALL_META(longSize,sizeof(long)),
BALL_META(intSize,sizeof(int)),
BALL_META(coordSize,sizeof(coordxy)),
BALL_META(booleanSize,sizeof(boolean)),
BALL_META(objectSize,sizeof(struct obj)),
BALL_META(rmSize,sizeof(struct rm)),
BALL_META(propSize,sizeof(struct prop)),
BALL_META(levelSize,sizeof(d_level)),
BALL_META(obj_nobj,offsetof(struct obj,nobj)),
BALL_META(obj_nobj_size,sizeof(((struct obj*)0)->nobj)),
BALL_META(obj_nexthere,offsetof(struct obj,nexthere)),
BALL_META(obj_nexthere_size,sizeof(((struct obj*)0)->nexthere)),
BALL_META(obj_ox,offsetof(struct obj,ox)),
BALL_META(obj_ox_size,sizeof(((struct obj*)0)->ox)),
BALL_META(obj_oy,offsetof(struct obj,oy)),
BALL_META(obj_oy_size,sizeof(((struct obj*)0)->oy)),
BALL_META(obj_where,offsetof(struct obj,where)),
BALL_META(obj_where_size,sizeof(((struct obj*)0)->where)),
BALL_META(obj_otyp,offsetof(struct obj,otyp)),
BALL_META(obj_otyp_size,sizeof(((struct obj*)0)->otyp)),
BALL_META(obj_owt,offsetof(struct obj,owt)),
BALL_META(obj_owt_size,sizeof(((struct obj*)0)->owt)),
BALL_META(obj_quan,offsetof(struct obj,quan)),
BALL_META(obj_quan_size,sizeof(((struct obj*)0)->quan)),
BALL_META(obj_owornmask,offsetof(struct obj,owornmask)),
BALL_META(obj_owornmask_size,sizeof(((struct obj*)0)->owornmask)),
BALL_META(u_ux,offsetof(struct you,ux)),
BALL_META(u_ux_size,sizeof(((struct you*)0)->ux)),
BALL_META(u_uy,offsetof(struct you,uy)),
BALL_META(u_uy_size,sizeof(((struct you*)0)->uy)),
BALL_META(u_ux0,offsetof(struct you,ux0)),
BALL_META(u_ux0_size,sizeof(((struct you*)0)->ux0)),
BALL_META(u_uy0,offsetof(struct you,uy0)),
BALL_META(u_uy0_size,sizeof(((struct you*)0)->uy0)),
BALL_META(u_dx,offsetof(struct you,dx)),
BALL_META(u_dx_size,sizeof(((struct you*)0)->dx)),
BALL_META(u_dy,offsetof(struct you,dy)),
BALL_META(u_dy_size,sizeof(((struct you*)0)->dy)),
BALL_META(u_bglyph,offsetof(struct you,bglyph)),
BALL_META(u_bglyph_size,sizeof(((struct you*)0)->bglyph)),
BALL_META(u_cglyph,offsetof(struct you,cglyph)),
BALL_META(u_cglyph_size,sizeof(((struct you*)0)->cglyph)),
BALL_META(u_bc_order,offsetof(struct you,bc_order)),
BALL_META(u_bc_order_size,sizeof(((struct you*)0)->bc_order)),
BALL_META(u_bc_felt,offsetof(struct you,bc_felt)),
BALL_META(u_bc_felt_size,sizeof(((struct you*)0)->bc_felt)),
BALL_META(u_utrap,offsetof(struct you,utrap)),
BALL_META(u_utrap_size,sizeof(((struct you*)0)->utrap)),
BALL_META(u_utraptype,offsetof(struct you,utraptype)),
BALL_META(u_utraptype_size,sizeof(((struct you*)0)->utraptype)),
BALL_META(u_uluck,offsetof(struct you,uluck)),
BALL_META(u_uluck_size,sizeof(((struct you*)0)->uluck)),
BALL_META(u_moreluck,offsetof(struct you,moreluck)),
BALL_META(u_moreluck_size,sizeof(((struct you*)0)->moreluck)),
BALL_META(u_usteed,offsetof(struct you,usteed)),
BALL_META(u_usteed_size,sizeof(((struct you*)0)->usteed)),
BALL_META(u_uz,offsetof(struct you,uz)),
BALL_META(u_uz_size,sizeof(((struct you*)0)->uz)),
BALL_META(u_uprops,offsetof(struct you,uprops)),
BALL_META(u_uprops_size,sizeof(((struct you*)0)->uprops)),
BALL_META(rm_glyph,offsetof(struct rm,glyph)),
BALL_META(rm_glyph_size,sizeof(((struct rm*)0)->glyph)),
BALL_META(rm_typ,offsetof(struct rm,typ)),
BALL_META(rm_typ_size,sizeof(((struct rm*)0)->typ)),
BALL_META(prop_intrinsic,offsetof(struct prop,intrinsic)),
BALL_META(prop_intrinsic_size,sizeof(((struct prop*)0)->intrinsic)),
BALL_META(prop_extrinsic,offsetof(struct prop,extrinsic)),
BALL_META(prop_extrinsic_size,sizeof(((struct prop*)0)->extrinsic)),
BALL_META(prop_blocked,offsetof(struct prop,blocked)),
BALL_META(prop_blocked_size,sizeof(((struct prop*)0)->blocked)),
BALL_META(level_dnum,offsetof(d_level,dnum)),
BALL_META(level_dnum_size,sizeof(((d_level*)0)->dnum)),
BALL_META(level_dlevel,offsetof(d_level,dlevel)),
BALL_META(level_dlevel_size,sizeof(((d_level*)0)->dlevel)),
BALL_META(locations,(char*)&svl.level.locations-(char*)&svl),
BALL_META(objects,(char*)&svl.level.objects-(char*)&svl),
BALL_META(monsters,(char*)&svl.level.monsters-(char*)&svl),
BALL_META(waterLevel,(char*)&water_level-(char*)&svd),
BALL_META(invent,(char*)&gi.invent-(char*)&gi),
BALL_META(verbose,(char*)&flags.verbose-(char*)&flags),
BALL_META(visionRecalc,(char*)&gv.vision_full_recalc-(char*)&gv),
BALL_META(BC_BALL,BC_BALL),
BALL_META(BC_CHAIN,BC_CHAIN),
BALL_META(OBJ_FREE,OBJ_FREE),
BALL_META(OBJ_FLOOR,OBJ_FLOOR),
BALL_META(OBJ_INVENT,OBJ_INVENT),
BALL_META(HEAVY_IRON_BALL,HEAVY_IRON_BALL),
BALL_META(IRON_CHAIN,IRON_CHAIN),
BALL_META(W_BALL,W_BALL),
BALL_META(W_WEAPONS,W_WEAPONS),
BALL_META(W_CHAIN,W_CHAIN),
BALL_META(LEFT_SIDE,LEFT_SIDE),
BALL_META(RIGHT_SIDE,RIGHT_SIDE),
BALL_META(SLT_ENCUMBER,SLT_ENCUMBER),
BALL_META(POOL,POOL),
BALL_META(DOOR,DOOR),
BALL_META(STONE,STONE),
BALL_META(D_CLOSED,D_CLOSED),
BALL_META(D_LOCKED,D_LOCKED),
BALL_META(TT_INFLOOR,TT_INFLOOR),
BALL_META(TT_BURIEDBALL,TT_BURIEDBALL),
BALL_META(TT_PIT,TT_PIT),
BALL_META(TT_WEB,TT_WEB),
BALL_META(TT_LAVA,TT_LAVA),
BALL_META(TT_BEARTRAP,TT_BEARTRAP),
BALL_META(PIT,PIT),
BALL_META(SPIKED_PIT,SPIKED_PIT),
BALL_META(HOLE,HOLE),
BALL_META(TRAPDOOR,TRAPDOOR),
BALL_META(HEAD,HEAD),
BALL_META(LEG,LEG),
BALL_META(HMON_DRAGGED,HMON_DRAGGED),
BALL_META(A_STR,A_STR),
BALL_META(KILLED_BY,KILLED_BY),
BALL_META(KILLED_BY_AN,KILLED_BY_AN),
BALL_META(NO_KILLER_PREFIX,NO_KILLER_PREFIX),
BALL_META(BUFSZ,BUFSZ),
BALL_META(COLNO,COLNO),
BALL_META(ROWNO,ROWNO),
BALL_META(BLINDED,BLINDED),
BALL_META(LEVITATION,LEVITATION),
BALL_META(HALF_PHDAM,HALF_PHDAM),
BALL_META(override_restriction,override_restriction),
BALL_META(ROOM,ROOM),
BALL_META(MOAT,MOAT),
#ifdef BREADCRUMBS
BALL_META(config_BREADCRUMBS,1),
#else
BALL_META(config_BREADCRUMBS,0),
#endif
BALL_META(config_DEVELOPMENT_LOG,NH_DEVEL_STATUS != NH_STATUS_RELEASED),
};
size_t probe_context_size(void){return sizeof(struct obj);}
int probe_layout_count(void){return (int)(sizeof ball_layout/sizeof ball_layout[0]);}
const char*probe_layout_name(int i){return ball_layout[i].name;}
size_t probe_layout_value(int i){return ball_layout[i].value;}
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0,"review BALL ABI");
_Static_assert(sizeof(flags.verbose)==1 && (__typeof__(flags.verbose))-1<0,"review BALL verbose");
_Static_assert(sizeof(gv.vision_full_recalc)==1 && (__typeof__(gv.vision_full_recalc))-1<0,"review BALL vision flag");
_Static_assert(sizeof(gi.invent)==8,"review BALL inventory pointer");
_Static_assert(sizeof(((struct obj*)0)->nobj)==8,"review BALL pointer");
_Static_assert(sizeof(((struct obj*)0)->nexthere)==8,"review BALL pointer");
_Static_assert(sizeof(((struct obj*)0)->ox)==2 && (((__typeof__(((struct obj*)0)->ox))-1<0)==1),"review BALL obj.ox");
_Static_assert(sizeof(((struct obj*)0)->oy)==2 && (((__typeof__(((struct obj*)0)->oy))-1<0)==1),"review BALL obj.oy");
_Static_assert(sizeof(((struct obj*)0)->where)==1 && (((__typeof__(((struct obj*)0)->where))-1<0)==1),"review BALL obj.where");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"review BALL obj.otyp");
_Static_assert(sizeof(((struct obj*)0)->owt)==4 && (((__typeof__(((struct obj*)0)->owt))-1<0)==0),"review BALL obj.owt");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"review BALL obj.quan");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8 && (((__typeof__(((struct obj*)0)->owornmask))-1<0)==1),"review BALL obj.owornmask");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"review BALL u.ux");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"review BALL u.uy");
_Static_assert(sizeof(((struct you*)0)->ux0)==2 && (((__typeof__(((struct you*)0)->ux0))-1<0)==1),"review BALL u.ux0");
_Static_assert(sizeof(((struct you*)0)->uy0)==2 && (((__typeof__(((struct you*)0)->uy0))-1<0)==1),"review BALL u.uy0");
_Static_assert(sizeof(((struct you*)0)->dx)==4 && (((__typeof__(((struct you*)0)->dx))-1<0)==1),"review BALL u.dx");
_Static_assert(sizeof(((struct you*)0)->dy)==4 && (((__typeof__(((struct you*)0)->dy))-1<0)==1),"review BALL u.dy");
_Static_assert(sizeof(((struct you*)0)->bglyph)==4 && (((__typeof__(((struct you*)0)->bglyph))-1<0)==1),"review BALL u.bglyph");
_Static_assert(sizeof(((struct you*)0)->cglyph)==4 && (((__typeof__(((struct you*)0)->cglyph))-1<0)==1),"review BALL u.cglyph");
_Static_assert(sizeof(((struct you*)0)->bc_order)==4 && (((__typeof__(((struct you*)0)->bc_order))-1<0)==1),"review BALL u.bc_order");
_Static_assert(sizeof(((struct you*)0)->bc_felt)==4 && (((__typeof__(((struct you*)0)->bc_felt))-1<0)==1),"review BALL u.bc_felt");
_Static_assert(sizeof(((struct you*)0)->utrap)==4 && (((__typeof__(((struct you*)0)->utrap))-1<0)==0),"review BALL u.utrap");
_Static_assert(sizeof(((struct you*)0)->utraptype)==4 && (((__typeof__(((struct you*)0)->utraptype))-1<0)==0),"review BALL u.utraptype");
_Static_assert(sizeof(((struct you*)0)->uluck)==1 && (((__typeof__(((struct you*)0)->uluck))-1<0)==1),"review BALL u.uluck");
_Static_assert(sizeof(((struct you*)0)->moreluck)==1 && (((__typeof__(((struct you*)0)->moreluck))-1<0)==1),"review BALL u.moreluck");
_Static_assert(sizeof(((struct you*)0)->usteed)==8,"review BALL pointer");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4 && (((__typeof__(((struct rm*)0)->glyph))-1<0)==1),"review BALL rm.glyph");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"review BALL rm.typ");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"review BALL prop.intrinsic");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"review BALL prop.extrinsic");
_Static_assert(sizeof(((struct prop*)0)->blocked)==8 && (((__typeof__(((struct prop*)0)->blocked))-1<0)==1),"review BALL prop.blocked");
_Static_assert(sizeof(((d_level*)0)->dnum)==2 && (((__typeof__(((d_level*)0)->dnum))-1<0)==1),"review BALL level.dnum");
_Static_assert(sizeof(((d_level*)0)->dlevel)==2 && (((__typeof__(((d_level*)0)->dlevel))-1<0)==1),"review BALL level.dlevel");
