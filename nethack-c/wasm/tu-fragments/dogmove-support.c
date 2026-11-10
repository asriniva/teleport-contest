/* DOGMOVE typed field/global/dependency/backing only; no pet algorithms. */
#include "hack.h"
#include "mfndpos.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "dogmove-source-data.h"
#ifndef MAIL_STRUCTURES
#error Review DOGMOVE MAIL_STRUCTURES configuration
#endif
#ifdef SFCTOOL
#error Review DOGMOVE SFCTOOL configuration
#endif
/* Compiler guards: typed ABI only, no source algorithms. */
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(int)==4,"DOGMOVE memory64 ABI");
_Static_assert(sizeof(boolean)==1 && (boolean)-1<0,"DOGMOVE signed boolean");
_Static_assert(sizeof(coordxy)==2 && (coordxy)-1<0,"DOGMOVE signed coordxy");
_Static_assert(sizeof(seenV)==1,"DOGMOVE seenV byte");
_Static_assert(sizeof(((struct d_level*)0)->dnum)==2 && (((__typeof__(((struct d_level*)0)->dnum))-1<0)==1),"DOGMOVE d_level.dnum width/sign");
_Static_assert(sizeof(((struct d_level*)0)->dlevel)==2 && (((__typeof__(((struct d_level*)0)->dlevel))-1<0)==1),"DOGMOVE d_level.dlevel width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->x)==2 && (((__typeof__(((struct nhcoord*)0)->x))-1<0)==1),"DOGMOVE nhcoord.x width/sign");
_Static_assert(sizeof(((struct nhcoord*)0)->y)==2 && (((__typeof__(((struct nhcoord*)0)->y))-1<0)==1),"DOGMOVE nhcoord.y width/sign");
_Static_assert(sizeof(((struct flag*)0)->verbose)==1 && (((__typeof__(((struct flag*)0)->verbose))-1<0)==1),"DOGMOVE flag.verbose width/sign");
_Static_assert(sizeof(((struct trap*)0)->tx)==2 && (((__typeof__(((struct trap*)0)->tx))-1<0)==1),"DOGMOVE trap.tx width/sign");
_Static_assert(sizeof(((struct trap*)0)->ty)==2 && (((__typeof__(((struct trap*)0)->ty))-1<0)==1),"DOGMOVE trap.ty width/sign");
_Static_assert(sizeof(((struct obj*)0)->o_id)==4 && (((__typeof__(((struct obj*)0)->o_id))-1<0)==0),"DOGMOVE obj.o_id width/sign");
_Static_assert(sizeof(((struct obj*)0)->ox)==2 && (((__typeof__(((struct obj*)0)->ox))-1<0)==1),"DOGMOVE obj.ox width/sign");
_Static_assert(sizeof(((struct obj*)0)->oy)==2 && (((__typeof__(((struct obj*)0)->oy))-1<0)==1),"DOGMOVE obj.oy width/sign");
_Static_assert(sizeof(((struct obj*)0)->otyp)==2 && (((__typeof__(((struct obj*)0)->otyp))-1<0)==1),"DOGMOVE obj.otyp width/sign");
_Static_assert(sizeof(((struct obj*)0)->owt)==4 && (((__typeof__(((struct obj*)0)->owt))-1<0)==0),"DOGMOVE obj.owt width/sign");
_Static_assert(sizeof(((struct obj*)0)->quan)==8 && (((__typeof__(((struct obj*)0)->quan))-1<0)==1),"DOGMOVE obj.quan width/sign");
_Static_assert(sizeof(((struct obj*)0)->oclass)==1 && (((__typeof__(((struct obj*)0)->oclass))-1<0)==1),"DOGMOVE obj.oclass width/sign");
_Static_assert(sizeof(((struct obj*)0)->invlet)==1 && (((__typeof__(((struct obj*)0)->invlet))-1<0)==1),"DOGMOVE obj.invlet width/sign");
_Static_assert(sizeof(((struct obj*)0)->oartifact)==1 && (((__typeof__(((struct obj*)0)->oartifact))-1<0)==1),"DOGMOVE obj.oartifact width/sign");
_Static_assert(sizeof(((struct obj*)0)->corpsenm)==4 && (((__typeof__(((struct obj*)0)->corpsenm))-1<0)==1),"DOGMOVE obj.corpsenm width/sign");
_Static_assert(sizeof(((struct obj*)0)->oeaten)==4 && (((__typeof__(((struct obj*)0)->oeaten))-1<0)==0),"DOGMOVE obj.oeaten width/sign");
_Static_assert(sizeof(((struct obj*)0)->owornmask)==8 && (((__typeof__(((struct obj*)0)->owornmask))-1<0)==1),"DOGMOVE obj.owornmask width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_name_idx)==2 && (((__typeof__(((struct objclass*)0)->oc_name_idx))-1<0)==1),"DOGMOVE objclass.oc_name_idx width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_descr_idx)==2 && (((__typeof__(((struct objclass*)0)->oc_descr_idx))-1<0)==1),"DOGMOVE objclass.oc_descr_idx width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_subtyp)==1 && (((__typeof__(((struct objclass*)0)->oc_subtyp))-1<0)==1),"DOGMOVE objclass.oc_subtyp width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_delay)==1 && (((__typeof__(((struct objclass*)0)->oc_delay))-1<0)==1),"DOGMOVE objclass.oc_delay width/sign");
_Static_assert(sizeof(((struct objclass*)0)->oc_nutrition)==2 && (((__typeof__(((struct objclass*)0)->oc_nutrition))-1<0)==0),"DOGMOVE objclass.oc_nutrition width/sign");
_Static_assert(sizeof(((struct attack*)0)->aatyp)==1 && (((__typeof__(((struct attack*)0)->aatyp))-1<0)==0),"DOGMOVE attack.aatyp width/sign");
_Static_assert(sizeof(((struct permonst*)0)->pmidx)==4 && (((__typeof__(((struct permonst*)0)->pmidx))-1<0)==1),"DOGMOVE permonst.pmidx width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlet)==1 && (((__typeof__(((struct permonst*)0)->mlet))-1<0)==1),"DOGMOVE permonst.mlet width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mlevel)==1 && (((__typeof__(((struct permonst*)0)->mlevel))-1<0)==1),"DOGMOVE permonst.mlevel width/sign");
_Static_assert(sizeof(((struct permonst*)0)->cwt)==4 && (((__typeof__(((struct permonst*)0)->cwt))-1<0)==0),"DOGMOVE permonst.cwt width/sign");
_Static_assert(sizeof(((struct permonst*)0)->cnutrit)==2 && (((__typeof__(((struct permonst*)0)->cnutrit))-1<0)==0),"DOGMOVE permonst.cnutrit width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msound)==1 && (((__typeof__(((struct permonst*)0)->msound))-1<0)==0),"DOGMOVE permonst.msound width/sign");
_Static_assert(sizeof(((struct permonst*)0)->msize)==1 && (((__typeof__(((struct permonst*)0)->msize))-1<0)==0),"DOGMOVE permonst.msize width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags1)==8 && (((__typeof__(((struct permonst*)0)->mflags1))-1<0)==0),"DOGMOVE permonst.mflags1 width/sign");
_Static_assert(sizeof(((struct permonst*)0)->mflags2)==8 && (((__typeof__(((struct permonst*)0)->mflags2))-1<0)==0),"DOGMOVE permonst.mflags2 width/sign");
_Static_assert(sizeof(((struct prop*)0)->extrinsic)==8 && (((__typeof__(((struct prop*)0)->extrinsic))-1<0)==1),"DOGMOVE prop.extrinsic width/sign");
_Static_assert(sizeof(((struct prop*)0)->intrinsic)==8 && (((__typeof__(((struct prop*)0)->intrinsic))-1<0)==1),"DOGMOVE prop.intrinsic width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_id)==4 && (((__typeof__(((struct monst*)0)->m_id))-1<0)==0),"DOGMOVE monst.m_id width/sign");
_Static_assert(sizeof(((struct monst*)0)->cham)==2 && (((__typeof__(((struct monst*)0)->cham))-1<0)==1),"DOGMOVE monst.cham width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_lev)==1 && (((__typeof__(((struct monst*)0)->m_lev))-1<0)==0),"DOGMOVE monst.m_lev width/sign");
_Static_assert(sizeof(((struct monst*)0)->mx)==2 && (((__typeof__(((struct monst*)0)->mx))-1<0)==1),"DOGMOVE monst.mx width/sign");
_Static_assert(sizeof(((struct monst*)0)->my)==2 && (((__typeof__(((struct monst*)0)->my))-1<0)==1),"DOGMOVE monst.my width/sign");
_Static_assert(sizeof(((struct monst*)0)->mux)==2 && (((__typeof__(((struct monst*)0)->mux))-1<0)==1),"DOGMOVE monst.mux width/sign");
_Static_assert(sizeof(((struct monst*)0)->muy)==2 && (((__typeof__(((struct monst*)0)->muy))-1<0)==1),"DOGMOVE monst.muy width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhp)==4 && (((__typeof__(((struct monst*)0)->mhp))-1<0)==1),"DOGMOVE monst.mhp width/sign");
_Static_assert(sizeof(((struct monst*)0)->mhpmax)==4 && (((__typeof__(((struct monst*)0)->mhpmax))-1<0)==1),"DOGMOVE monst.mhpmax width/sign");
_Static_assert(sizeof(((struct monst*)0)->mappearance)==4 && (((__typeof__(((struct monst*)0)->mappearance))-1<0)==0),"DOGMOVE monst.mappearance width/sign");
_Static_assert(sizeof(((struct monst*)0)->m_ap_type)==1 && (((__typeof__(((struct monst*)0)->m_ap_type))-1<0)==0),"DOGMOVE monst.m_ap_type width/sign");
_Static_assert(sizeof(((struct monst*)0)->mtame)==1 && (((__typeof__(((struct monst*)0)->mtame))-1<0)==1),"DOGMOVE monst.mtame width/sign");
_Static_assert(sizeof(((struct monst*)0)->mlstmv)==8 && (((__typeof__(((struct monst*)0)->mlstmv))-1<0)==1),"DOGMOVE monst.mlstmv width/sign");
_Static_assert(sizeof(((struct monst*)0)->mstate)==8 && (((__typeof__(((struct monst*)0)->mstate))-1<0)==1),"DOGMOVE monst.mstate width/sign");
_Static_assert(sizeof(((struct monst*)0)->weapon_check)==2 && (((__typeof__(((struct monst*)0)->weapon_check))-1<0)==1),"DOGMOVE monst.weapon_check width/sign");
_Static_assert(sizeof(((struct monst*)0)->meating)==4 && (((__typeof__(((struct monst*)0)->meating))-1<0)==1),"DOGMOVE monst.meating width/sign");
_Static_assert(sizeof(((struct epri*)0)->shralign)==1 && (((__typeof__(((struct epri*)0)->shralign))-1<0)==1),"DOGMOVE epri.shralign width/sign");
_Static_assert(sizeof(((struct achievement_tracking*)0)->mines_prize_oid)==4 && (((__typeof__(((struct achievement_tracking*)0)->mines_prize_oid))-1<0)==0),"DOGMOVE achievement_tracking.mines_prize_oid width/sign");
_Static_assert(sizeof(((struct achievement_tracking*)0)->soko_prize_oid)==4 && (((__typeof__(((struct achievement_tracking*)0)->soko_prize_oid))-1<0)==0),"DOGMOVE achievement_tracking.soko_prize_oid width/sign");
_Static_assert(sizeof(((struct rm*)0)->glyph)==4 && (((__typeof__(((struct rm*)0)->glyph))-1<0)==1),"DOGMOVE rm.glyph width/sign");
_Static_assert(sizeof(((struct rm*)0)->typ)==1 && (((__typeof__(((struct rm*)0)->typ))-1<0)==1),"DOGMOVE rm.typ width/sign");
_Static_assert(sizeof(((struct emin*)0)->min_align)==1 && (((__typeof__(((struct emin*)0)->min_align))-1<0)==1),"DOGMOVE emin.min_align width/sign");
_Static_assert(sizeof(((struct edog*)0)->parentmid)==4 && (((__typeof__(((struct edog*)0)->parentmid))-1<0)==0),"DOGMOVE edog.parentmid width/sign");
_Static_assert(sizeof(((struct edog*)0)->droptime)==8 && (((__typeof__(((struct edog*)0)->droptime))-1<0)==1),"DOGMOVE edog.droptime width/sign");
_Static_assert(sizeof(((struct edog*)0)->dropdist)==4 && (((__typeof__(((struct edog*)0)->dropdist))-1<0)==0),"DOGMOVE edog.dropdist width/sign");
_Static_assert(sizeof(((struct edog*)0)->apport)==4 && (((__typeof__(((struct edog*)0)->apport))-1<0)==1),"DOGMOVE edog.apport width/sign");
_Static_assert(sizeof(((struct edog*)0)->whistletime)==8 && (((__typeof__(((struct edog*)0)->whistletime))-1<0)==1),"DOGMOVE edog.whistletime width/sign");
_Static_assert(sizeof(((struct edog*)0)->hungrytime)==8 && (((__typeof__(((struct edog*)0)->hungrytime))-1<0)==1),"DOGMOVE edog.hungrytime width/sign");
_Static_assert(sizeof(((struct edog*)0)->mhpmax_penalty)==4 && (((__typeof__(((struct edog*)0)->mhpmax_penalty))-1<0)==1),"DOGMOVE edog.mhpmax_penalty width/sign");
_Static_assert(sizeof(((struct u_roleplay*)0)->deaf)==1 && (((__typeof__(((struct u_roleplay*)0)->deaf))-1<0)==1),"DOGMOVE u_roleplay.deaf width/sign");
_Static_assert(sizeof(((struct instance_flags*)0)->suppress_price)==4 && (((__typeof__(((struct instance_flags*)0)->suppress_price))-1<0)==1),"DOGMOVE instance_flags.suppress_price width/sign");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gtyp)==2 && (((__typeof__(((struct instance_globals_g*)0)->gtyp))-1<0)==1),"DOGMOVE instance_globals_g.gtyp width/sign");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gx)==2 && (((__typeof__(((struct instance_globals_g*)0)->gx))-1<0)==1),"DOGMOVE instance_globals_g.gx width/sign");
_Static_assert(sizeof(((struct instance_globals_g*)0)->gy)==2 && (((__typeof__(((struct instance_globals_g*)0)->gy))-1<0)==1),"DOGMOVE instance_globals_g.gy width/sign");
_Static_assert(sizeof(((struct you*)0)->ux)==2 && (((__typeof__(((struct you*)0)->ux))-1<0)==1),"DOGMOVE you.ux width/sign");
_Static_assert(sizeof(((struct you*)0)->uy)==2 && (((__typeof__(((struct you*)0)->uy))-1<0)==1),"DOGMOVE you.uy width/sign");
_Static_assert(sizeof(((struct you*)0)->ulevel)==4 && (((__typeof__(((struct you*)0)->ulevel))-1<0)==1),"DOGMOVE you.ulevel width/sign");
_Static_assert(sizeof(((struct instance_globals_n*)0)->notonhead)==1 && (((__typeof__(((struct instance_globals_n*)0)->notonhead))-1<0)==1),"DOGMOVE instance_globals_n.notonhead width/sign");
_Static_assert(sizeof(((struct instance_globals_saved_m*)0)->moves)==8 && (((__typeof__(((struct instance_globals_saved_m*)0)->moves))-1<0)==1),"DOGMOVE instance_globals_saved_m.moves width/sign");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Mgender),int (*)(struct monst *)),"DOGMOVE dependency Mgender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Monnam),char *(*)(struct monst *)),"DOGMOVE dependency Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&On_stairs),boolean (*)(coordxy, coordxy)),"DOGMOVE dependency On_stairs");
_Static_assert(__builtin_types_compatible_p(__typeof__(&Resists_Elem),boolean (*)(struct monst *, int)),"DOGMOVE dependency Resists_Elem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strcpy),char *(*)(char *, const char *)),"DOGMOVE dependency strcpy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&an),char *(*)(const char *)),"DOGMOVE dependency an");
_Static_assert(__builtin_types_compatible_p(__typeof__(&attacktype),boolean (*)(struct permonst *, int)),"DOGMOVE dependency attacktype");
_Static_assert(__builtin_types_compatible_p(__typeof__(&bee_eat_jelly),int (*)(struct monst *, struct obj *)),"DOGMOVE dependency bee_eat_jelly");
_Static_assert(__builtin_types_compatible_p(__typeof__(&beg),void (*)(struct monst *)),"DOGMOVE dependency beg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&can_carry),int (*)(struct monst *, struct obj *)),"DOGMOVE dependency can_carry");
_Static_assert(__builtin_types_compatible_p(__typeof__(&canseemon),int (*)(struct monst *)),"DOGMOVE dependency canseemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&check_gear_next_turn),void (*)(struct monst *)),"DOGMOVE dependency check_gear_next_turn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&clear_path),boolean (*)(int, int, int, int)),"DOGMOVE dependency clear_path");
_Static_assert(__builtin_types_compatible_p(__typeof__(&costly_alteration),void (*)(struct obj *, int)),"DOGMOVE dependency costly_alteration");
_Static_assert(__builtin_types_compatible_p(__typeof__(&currency),const char *(*)(long)),"DOGMOVE dependency currency");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dirtocoord),void (*)(coord *, int)),"DOGMOVE dependency dirtocoord");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dismount_steed),void (*)(int)),"DOGMOVE dependency dismount_steed");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dist2),int (*)(coordxy, coordxy, coordxy, coordxy)),"DOGMOVE dependency dist2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&distant_name),char *(*)(struct obj *, char *(*)(struct obj *))),"DOGMOVE dependency distant_name");
_Static_assert(__builtin_types_compatible_p(__typeof__(&distmin),int (*)(coordxy, coordxy, coordxy, coordxy)),"DOGMOVE dependency distmin");
_Static_assert(__builtin_types_compatible_p(__typeof__(&dogfood),int (*)(struct monst *, struct obj *)),"DOGMOVE dependency dogfood");
_Static_assert(__builtin_types_compatible_p(__typeof__(&domonnoise),int (*)(struct monst *)),"DOGMOVE dependency domonnoise");
_Static_assert(__builtin_types_compatible_p(__typeof__(&eaten_stat),int (*)(int, struct obj *)),"DOGMOVE dependency eaten_stat");
_Static_assert(__builtin_types_compatible_p(__typeof__(&gettrack),coord *(*)(coordxy, coordxy)),"DOGMOVE dependency gettrack");
_Static_assert(__builtin_types_compatible_p(__typeof__(&glyph_at),int (*)(coordxy, coordxy)),"DOGMOVE dependency glyph_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&goodpos),boolean (*)(coordxy, coordxy, struct monst *, mmflags_nht)),"DOGMOVE dependency goodpos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_lava),boolean (*)(coordxy, coordxy)),"DOGMOVE dependency is_lava");
_Static_assert(__builtin_types_compatible_p(__typeof__(&is_pool),boolean (*)(coordxy, coordxy)),"DOGMOVE dependency is_pool");
_Static_assert(__builtin_types_compatible_p(__typeof__(&isok),int (*)(coordxy, coordxy)),"DOGMOVE dependency isok");
_Static_assert(__builtin_types_compatible_p(__typeof__(&locomotion),const char *(*)(const struct permonst *, const char *)),"DOGMOVE dependency locomotion");
_Static_assert(__builtin_types_compatible_p(__typeof__(&lose_guardian_angel),void (*)(struct monst *)),"DOGMOVE dependency lose_guardian_angel");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_avoid_kicked_loc),boolean (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency m_avoid_kicked_loc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_avoid_soko_push_loc),boolean (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency m_avoid_soko_push_loc");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_consume_obj),void (*)(struct monst *, struct obj *)),"DOGMOVE dependency m_consume_obj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_digweapon_check),boolean (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency m_digweapon_check");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_in_out_region),boolean (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency m_in_out_region");
_Static_assert(__builtin_types_compatible_p(__typeof__(&m_unleash),void (*)(struct monst *, boolean)),"DOGMOVE dependency m_unleash");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mattackm),int (*)(struct monst *, struct monst *)),"DOGMOVE dependency mattackm");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mattacku),int (*)(struct monst *)),"DOGMOVE dependency mattacku");
_Static_assert(__builtin_types_compatible_p(__typeof__(&max_passive_dmg),int (*)(struct monst *, struct monst *)),"DOGMOVE dependency max_passive_dmg");
_Static_assert(__builtin_types_compatible_p(__typeof__(&may_dig),boolean (*)(coordxy, coordxy)),"DOGMOVE dependency may_dig");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mdisplacem),int (*)(struct monst *, struct monst *, boolean)),"DOGMOVE dependency mdisplacem");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mfndpos),int (*)(struct monst *, struct mfndposdata *, long)),"DOGMOVE dependency mfndpos");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_allowflags),long (*)(struct monst *)),"DOGMOVE dependency mon_allowflags");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_reflects),boolean (*)(struct monst *, const char *)),"DOGMOVE dependency mon_reflects");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_track_add),void (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency mon_track_add");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_visible),int (*)(struct monst *)),"DOGMOVE dependency mon_visible");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mon_wield_item),int (*)(struct monst *)),"DOGMOVE dependency mon_wield_item");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mondied),void (*)(struct monst *)),"DOGMOVE dependency mondied");
_Static_assert(__builtin_types_compatible_p(__typeof__(&monnear),boolean (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency monnear");
_Static_assert(__builtin_types_compatible_p(__typeof__(&mpickobj),int (*)(struct monst *, struct obj *)),"DOGMOVE dependency mpickobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&newsym),void (*)(coordxy, coordxy)),"DOGMOVE dependency newsym");
_Static_assert(__builtin_types_compatible_p(__typeof__(&noit_Monnam),char *(*)(struct monst *)),"DOGMOVE dependency noit_Monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&obj_extract_self),void (*)(struct obj *)),"DOGMOVE dependency obj_extract_self");
_Static_assert(__builtin_types_compatible_p(__typeof__(&on_level),boolean (*)(d_level *, d_level *)),"DOGMOVE dependency on_level");
_Static_assert(__builtin_types_compatible_p(__typeof__(&onscary),boolean (*)(coordxy, coordxy, struct monst *)),"DOGMOVE dependency onscary");
_Static_assert(__builtin_types_compatible_p(__typeof__(&place_monster),void (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency place_monster");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pmname),const char *(*)(struct permonst *, int)),"DOGMOVE dependency pmname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&pronoun_gender),int (*)(struct monst *, unsigned int)),"DOGMOVE dependency pronoun_gender");
_Static_assert(__builtin_types_compatible_p(__typeof__(&relobj),void (*)(struct monst *, int, boolean)),"DOGMOVE dependency relobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&resist_conflict),boolean (*)(struct monst *)),"DOGMOVE dependency resist_conflict");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sensemon),int (*)(struct monst *)),"DOGMOVE dependency sensemon");
_Static_assert(__builtin_types_compatible_p(__typeof__(&set_apparxy),void (*)(struct monst *)),"DOGMOVE dependency set_apparxy");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sgn),int (*)(int)),"DOGMOVE dependency sgn");
_Static_assert(__builtin_types_compatible_p(__typeof__(&should_displace),boolean (*)(struct monst *, const struct mfndposdata *, coordxy, coordxy)),"DOGMOVE dependency should_displace");
_Static_assert(__builtin_types_compatible_p(__typeof__(&sobj_at),struct obj *(*)(int, coordxy, coordxy)),"DOGMOVE dependency sobj_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&splitobj),struct obj *(*)(struct obj *, long)),"DOGMOVE dependency splitobj");
_Static_assert(__builtin_types_compatible_p(__typeof__(&stop_occupation),void (*)(void)),"DOGMOVE dependency stop_occupation");
_Static_assert(__builtin_types_compatible_p(__typeof__(&strchr),char *(*)(const char *, int)),"DOGMOVE dependency strchr");
_Static_assert(__builtin_types_compatible_p(__typeof__(&t_at),struct trap *(*)(coordxy, coordxy)),"DOGMOVE dependency t_at");
_Static_assert(__builtin_types_compatible_p(__typeof__(&undesirable_disp),boolean (*)(struct monst *, coordxy, coordxy)),"DOGMOVE dependency undesirable_disp");
_Static_assert(__builtin_types_compatible_p(__typeof__(&unpaid_cost),long (*)(struct obj *, uchar)),"DOGMOVE dependency unpaid_cost");
_Static_assert(__builtin_types_compatible_p(__typeof__(&vtense),char *(*)(const char *, const char *)),"DOGMOVE dependency vtense");
_Static_assert(__builtin_types_compatible_p(__typeof__(&which_armor),struct obj *(*)(struct monst *, long)),"DOGMOVE dependency which_armor");
_Static_assert(__builtin_types_compatible_p(__typeof__(&whimper),void (*)(struct monst *)),"DOGMOVE dependency whimper");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xname),char *(*)(struct obj *)),"DOGMOVE dependency xname");
_Static_assert(__builtin_types_compatible_p(__typeof__(&xytodir),int (*)(int, int)),"DOGMOVE dependency xytodir");
_Static_assert(__builtin_types_compatible_p(__typeof__(&y_monnam),char *(*)(struct monst *)),"DOGMOVE dependency y_monnam");
_Static_assert(__builtin_types_compatible_p(__typeof__(&do_clear_area),void (*)(coordxy, coordxy, int, void (*)(coordxy, coordxy, void *), genericptr_t)),"DOGMOVE dependency do_clear_area");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rn2),int (*)(int)),"DOGMOVE dependency rn2");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rnd),int (*)(int)),"DOGMOVE dependency rnd");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_enabled),boolean (*)(void)),"DOGMOVE dependency rng_log_enabled");
_Static_assert(__builtin_types_compatible_p(__typeof__(&rng_log_set_caller),void (*)(const char *, int, const char *)),"DOGMOVE dependency rng_log_set_caller");
_Static_assert(__builtin_types_compatible_p(__typeof__(&doname),char *(*)(struct obj *)),"DOGMOVE dependency doname");
static struct obj dogmove_dummy;
static char dogmove_nofetch[DOGMOVE_NOFETCH_COUNT];
void*teleport_dogmove_global(int index){switch(index){
case 0:return (void*)&cg;
case 1:return (void*)&objects;
case 2:return (void*)&svl;
case 3:return (void*)&mons;
case 4:return (void*)&svm;
case 5:return (void*)&iflags;
case 6:return (void*)&u;
case 7:return (void*)&gv;
case 8:return (void*)&flags;
case 9:return (void*)&svc;
case 10:return (void*)&gg;
case 11:return (void*)&gi;
case 12:return (void*)&gf;
case 13:return (void*)&gy;
case 14:return (void*)&svd;
case 15:return (void*)&gb;
case 16:return (void*)&gn;
case 17:return (void*)&genders;
case 18:return (void*)&c_common_strings;
case 19:return (void*)&defsyms;
case 20:return (void*)&obj_descr;
case 21:return (void*)&windowprocs;
case 22:return (void*)&WIN_MAP;
case 23:return &dogmove_dummy;
case 24:return dogmove_nofetch;
default:abort();}}
uint64_t teleport_dogmove_read(int kind,void*at,int field){switch(kind){
case 0:{struct d_level*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->dnum);
case 1:return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 1:{struct nhcoord*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->x);
case 1:return (uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 2:{union vptrs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->v_nexthere);
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->verbose);
default:abort();}}
case 4:{struct trap*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ntrap);
case 1:return (uint64_t)(uintptr_t)(p->tx);
case 2:return (uint64_t)(uintptr_t)(p->ty);
case 3:return (uint64_t)(uintptr_t)(p->ttyp);
case 4:return (uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 5:{struct window_procs*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->win_display_nhwindow);
default:abort();}}
case 6:{struct symdef*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->explanation);
default:abort();}}
case 7:{struct obj*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->nobj);
case 1:return (uint64_t)(uintptr_t)(&p->v);
case 2:return (uint64_t)(uintptr_t)(p->o_id);
case 3:return (uint64_t)(uintptr_t)(p->ox);
case 4:return (uint64_t)(uintptr_t)(p->oy);
case 5:return (uint64_t)(uintptr_t)(p->otyp);
case 6:return (uint64_t)(uintptr_t)(p->owt);
case 7:return (uint64_t)(uintptr_t)(p->quan);
case 8:return (uint64_t)(uintptr_t)(p->oclass);
case 9:return (uint64_t)(uintptr_t)(p->invlet);
case 10:return (uint64_t)(uintptr_t)(p->oartifact);
case 11:return (uint64_t)(uintptr_t)(p->cursed);
case 12:return (uint64_t)(uintptr_t)(p->unpaid);
case 13:return (uint64_t)(uintptr_t)(p->oerodeproof);
case 14:return (uint64_t)(uintptr_t)(p->corpsenm);
case 15:return (uint64_t)(uintptr_t)(p->oeaten);
case 16:return (uint64_t)(uintptr_t)(p->owornmask);
default:abort();}}
case 8:{struct objclass*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_name_idx);
case 1:return (uint64_t)(uintptr_t)(p->oc_descr_idx);
case 2:return (uint64_t)(uintptr_t)(p->oc_subtyp);
case 3:return (uint64_t)(uintptr_t)(p->oc_delay);
case 4:return (uint64_t)(uintptr_t)(p->oc_nutrition);
default:abort();}}
case 9:{struct mfndposdata*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->poss);
case 1:return (uint64_t)(uintptr_t)(&p->info);
default:abort();}}
case 10:{struct attack*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->aatyp);
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->pmidx);
case 1:return (uint64_t)(uintptr_t)(p->mlet);
case 2:return (uint64_t)(uintptr_t)(p->mlevel);
case 3:return (uint64_t)(uintptr_t)(&p->mattk);
case 4:return (uint64_t)(uintptr_t)(p->cwt);
case 5:return (uint64_t)(uintptr_t)(p->cnutrit);
case 6:return (uint64_t)(uintptr_t)(p->msound);
case 7:return (uint64_t)(uintptr_t)(p->msize);
case 8:return (uint64_t)(uintptr_t)(p->mflags1);
case 9:return (uint64_t)(uintptr_t)(p->mflags2);
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->extrinsic);
case 1:return (uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->data);
case 1:return (uint64_t)(uintptr_t)(p->m_id);
case 2:return (uint64_t)(uintptr_t)(p->cham);
case 3:return (uint64_t)(uintptr_t)(p->m_lev);
case 4:return (uint64_t)(uintptr_t)(p->mx);
case 5:return (uint64_t)(uintptr_t)(p->my);
case 6:return (uint64_t)(uintptr_t)(p->mux);
case 7:return (uint64_t)(uintptr_t)(p->muy);
case 8:return (uint64_t)(uintptr_t)(&p->mtrack);
case 9:return (uint64_t)(uintptr_t)(p->mhp);
case 10:return (uint64_t)(uintptr_t)(p->mhpmax);
case 11:return (uint64_t)(uintptr_t)(p->mappearance);
case 12:return (uint64_t)(uintptr_t)(p->m_ap_type);
case 13:return (uint64_t)(uintptr_t)(p->mtame);
case 14:return (uint64_t)(uintptr_t)(p->minvis);
case 15:return (uint64_t)(uintptr_t)(p->mundetected);
case 16:return (uint64_t)(uintptr_t)(p->mcansee);
case 17:return (uint64_t)(uintptr_t)(p->mflee);
case 18:return (uint64_t)(uintptr_t)(p->mfleetim);
case 19:return (uint64_t)(uintptr_t)(p->msleeping);
case 20:return (uint64_t)(uintptr_t)(p->mstun);
case 21:return (uint64_t)(uintptr_t)(p->mcanmove);
case 22:return (uint64_t)(uintptr_t)(p->mconf);
case 23:return (uint64_t)(uintptr_t)(p->mpeaceful);
case 24:return (uint64_t)(uintptr_t)(p->mleashed);
case 25:return (uint64_t)(uintptr_t)(p->isminion);
case 26:return (uint64_t)(uintptr_t)(p->ispriest);
case 27:return (uint64_t)(uintptr_t)(p->mlstmv);
case 28:return (uint64_t)(uintptr_t)(p->mstate);
case 29:return (uint64_t)(uintptr_t)(p->minvent);
case 30:return (uint64_t)(uintptr_t)(p->mw);
case 31:return (uint64_t)(uintptr_t)(p->weapon_check);
case 32:return (uint64_t)(uintptr_t)(p->meating);
case 33:return (uint64_t)(uintptr_t)(p->mextra);
default:abort();}}
case 14:{struct epri*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->shralign);
default:abort();}}
case 15:{struct achievement_tracking*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->mines_prize_oid);
case 1:return (uint64_t)(uintptr_t)(p->soko_prize_oid);
default:abort();}}
case 16:{struct objdescr*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->oc_name);
case 1:return (uint64_t)(uintptr_t)(p->oc_descr);
default:abort();}}
case 17:{struct context_info*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->achieveo);
default:abort();}}
case 18:{struct rm*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->glyph);
case 1:return (uint64_t)(uintptr_t)(p->typ);
case 2:return (uint64_t)(uintptr_t)(p->flags);
case 3:return (uint64_t)(uintptr_t)(p->lit);
default:abort();}}
case 19:{struct instance_globals_b*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->bhitpos);
default:abort();}}
case 20:{struct emin*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->min_align);
default:abort();}}
case 21:{struct edog*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->parentmid);
case 1:return (uint64_t)(uintptr_t)(p->droptime);
case 2:return (uint64_t)(uintptr_t)(p->dropdist);
case 3:return (uint64_t)(uintptr_t)(p->apport);
case 4:return (uint64_t)(uintptr_t)(p->whistletime);
case 5:return (uint64_t)(uintptr_t)(p->hungrytime);
case 6:return (uint64_t)(uintptr_t)(&p->ogoal);
case 7:return (uint64_t)(uintptr_t)(p->mhpmax_penalty);
default:abort();}}
case 22:{struct c_common_strings*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->c_something);
default:abort();}}
case 23:{struct u_roleplay*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->deaf);
default:abort();}}
case 24:{struct mextra*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->epri);
case 1:return (uint64_t)(uintptr_t)(p->emin);
case 2:return (uint64_t)(uintptr_t)(p->edog);
default:abort();}}
case 25:{struct dgn_topology*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->d_rogue_level);
case 1:return (uint64_t)(uintptr_t)(&p->d_qstart_level);
default:abort();}}
case 26:{struct instance_flags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->suppress_price);
default:abort();}}
case 27:{struct instance_globals_f*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 28:{struct instance_globals_g*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->gtyp);
case 1:return (uint64_t)(uintptr_t)(p->gx);
case 2:return (uint64_t)(uintptr_t)(p->gy);
default:abort();}}
case 29:{struct Gender*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->his);
default:abort();}}
case 30:{struct instance_globals_i*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 31:{struct you*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->ux);
case 1:return (uint64_t)(uintptr_t)(p->uy);
case 2:return (uint64_t)(uintptr_t)(&p->uz);
case 3:return (uint64_t)(uintptr_t)(p->ulevel);
case 4:return (uint64_t)(uintptr_t)(&p->uprops);
case 5:return (uint64_t)(uintptr_t)(p->uinwater);
case 6:return (uint64_t)(uintptr_t)(&p->uroleplay);
case 7:return (uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
case 32:{struct levelflags*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->hero_memory);
default:abort();}}
case 33:{dlevel_t*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->locations);
case 1:return (uint64_t)(uintptr_t)(&p->objects);
case 2:return (uint64_t)(uintptr_t)(&p->monsters);
case 3:return (uint64_t)(uintptr_t)(p->objlist);
case 4:return (uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 34:{struct instance_globals_n*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->notonhead);
default:abort();}}
case 35:{struct instance_globals_v*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->viz_array);
default:abort();}}
case 36:{struct instance_globals_y*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->youmonst);
default:abort();}}
case 37:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 38:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->dungeon_topology);
default:abort();}}
case 39:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->level);
default:abort();}}
case 40:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(p->moves);
default:abort();}}
case 41:{struct const_globals*p=at;switch(field){
case 0:return (uint64_t)(uintptr_t)(&p->zeroobj);
default:abort();}}
default:abort();}}
void teleport_dogmove_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct d_level*p=at;switch(field){
case 0:p->dnum=value;return;
case 1:p->dlevel=value;return;
default:abort();}}
case 1:{struct nhcoord*p=at;switch(field){
case 0:p->x=value;return;
case 1:p->y=value;return;
default:abort();}}
case 2:{union vptrs*p=at;switch(field){
case 0:p->v_nexthere=(void*)(uintptr_t)value;return;
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:p->verbose=value;return;
default:abort();}}
case 4:{struct trap*p=at;switch(field){
case 0:p->ntrap=(void*)(uintptr_t)value;return;
case 1:p->tx=value;return;
case 2:p->ty=value;return;
case 3:p->ttyp=value;return;
case 4:p->tseen=value;return;
default:abort();}}
case 5:{struct window_procs*p=at;switch(field){
case 0:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))(uintptr_t)value;return;
default:abort();}}
case 6:{struct symdef*p=at;switch(field){
default:abort();}}
case 7:{struct obj*p=at;switch(field){
case 0:p->nobj=(void*)(uintptr_t)value;return;
case 1:memmove(&p->v,(void*)(uintptr_t)value,sizeof p->v);return;
case 2:p->o_id=value;return;
case 3:p->ox=value;return;
case 4:p->oy=value;return;
case 5:p->otyp=value;return;
case 6:p->owt=value;return;
case 7:p->quan=value;return;
case 8:p->oclass=value;return;
case 9:p->invlet=value;return;
case 10:p->oartifact=value;return;
case 11:p->cursed=value;return;
case 12:p->unpaid=value;return;
case 13:p->oerodeproof=value;return;
case 14:p->corpsenm=value;return;
case 15:p->oeaten=value;return;
case 16:p->owornmask=value;return;
default:abort();}}
case 8:{struct objclass*p=at;switch(field){
case 0:p->oc_name_idx=value;return;
case 1:p->oc_descr_idx=value;return;
case 2:p->oc_subtyp=value;return;
case 3:p->oc_delay=value;return;
case 4:p->oc_nutrition=value;return;
default:abort();}}
case 9:{struct mfndposdata*p=at;switch(field){
default:abort();}}
case 10:{struct attack*p=at;switch(field){
case 0:p->aatyp=value;return;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 1:p->mlet=value;return;
case 2:p->mlevel=value;return;
case 4:p->cwt=value;return;
case 5:p->cnutrit=value;return;
case 6:p->msound=value;return;
case 7:p->msize=value;return;
case 8:p->mflags1=value;return;
case 9:p->mflags2=value;return;
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:p->extrinsic=value;return;
case 1:p->intrinsic=value;return;
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:p->data=(void*)(uintptr_t)value;return;
case 1:p->m_id=value;return;
case 2:p->cham=value;return;
case 3:p->m_lev=value;return;
case 4:p->mx=value;return;
case 5:p->my=value;return;
case 6:p->mux=value;return;
case 7:p->muy=value;return;
case 9:p->mhp=value;return;
case 10:p->mhpmax=value;return;
case 11:p->mappearance=value;return;
case 12:p->m_ap_type=value;return;
case 13:p->mtame=value;return;
case 14:p->minvis=value;return;
case 15:p->mundetected=value;return;
case 16:p->mcansee=value;return;
case 17:p->mflee=value;return;
case 18:p->mfleetim=value;return;
case 19:p->msleeping=value;return;
case 20:p->mstun=value;return;
case 21:p->mcanmove=value;return;
case 22:p->mconf=value;return;
case 23:p->mpeaceful=value;return;
case 24:p->mleashed=value;return;
case 25:p->isminion=value;return;
case 26:p->ispriest=value;return;
case 27:p->mlstmv=value;return;
case 28:p->mstate=value;return;
case 29:p->minvent=(void*)(uintptr_t)value;return;
case 30:p->mw=(void*)(uintptr_t)value;return;
case 31:p->weapon_check=value;return;
case 32:p->meating=value;return;
case 33:p->mextra=(void*)(uintptr_t)value;return;
default:abort();}}
case 14:{struct epri*p=at;switch(field){
case 0:p->shralign=value;return;
default:abort();}}
case 15:{struct achievement_tracking*p=at;switch(field){
case 0:p->mines_prize_oid=value;return;
case 1:p->soko_prize_oid=value;return;
default:abort();}}
case 16:{struct objdescr*p=at;switch(field){
default:abort();}}
case 17:{struct context_info*p=at;switch(field){
case 0:memmove(&p->achieveo,(void*)(uintptr_t)value,sizeof p->achieveo);return;
default:abort();}}
case 18:{struct rm*p=at;switch(field){
case 0:p->glyph=value;return;
case 1:p->typ=value;return;
case 2:p->flags=value;return;
case 3:p->lit=value;return;
default:abort();}}
case 19:{struct instance_globals_b*p=at;switch(field){
case 0:memmove(&p->bhitpos,(void*)(uintptr_t)value,sizeof p->bhitpos);return;
default:abort();}}
case 20:{struct emin*p=at;switch(field){
case 0:p->min_align=value;return;
default:abort();}}
case 21:{struct edog*p=at;switch(field){
case 0:p->parentmid=value;return;
case 1:p->droptime=value;return;
case 2:p->dropdist=value;return;
case 3:p->apport=value;return;
case 4:p->whistletime=value;return;
case 5:p->hungrytime=value;return;
case 6:memmove(&p->ogoal,(void*)(uintptr_t)value,sizeof p->ogoal);return;
case 7:p->mhpmax_penalty=value;return;
default:abort();}}
case 22:{struct c_common_strings*p=at;switch(field){
default:abort();}}
case 23:{struct u_roleplay*p=at;switch(field){
case 0:p->deaf=value;return;
default:abort();}}
case 24:{struct mextra*p=at;switch(field){
case 0:p->epri=(void*)(uintptr_t)value;return;
case 1:p->emin=(void*)(uintptr_t)value;return;
case 2:p->edog=(void*)(uintptr_t)value;return;
default:abort();}}
case 25:{struct dgn_topology*p=at;switch(field){
case 0:memmove(&p->d_rogue_level,(void*)(uintptr_t)value,sizeof p->d_rogue_level);return;
case 1:memmove(&p->d_qstart_level,(void*)(uintptr_t)value,sizeof p->d_qstart_level);return;
default:abort();}}
case 26:{struct instance_flags*p=at;switch(field){
case 0:p->suppress_price=value;return;
default:abort();}}
case 27:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(void*)(uintptr_t)value;return;
default:abort();}}
case 28:{struct instance_globals_g*p=at;switch(field){
case 0:p->gtyp=value;return;
case 1:p->gx=value;return;
case 2:p->gy=value;return;
default:abort();}}
case 29:{struct Gender*p=at;switch(field){
default:abort();}}
case 30:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(void*)(uintptr_t)value;return;
default:abort();}}
case 31:{struct you*p=at;switch(field){
case 0:p->ux=value;return;
case 1:p->uy=value;return;
case 2:memmove(&p->uz,(void*)(uintptr_t)value,sizeof p->uz);return;
case 3:p->ulevel=value;return;
case 5:p->uinwater=value;return;
case 6:memmove(&p->uroleplay,(void*)(uintptr_t)value,sizeof p->uroleplay);return;
case 7:p->usteed=(void*)(uintptr_t)value;return;
default:abort();}}
case 32:{struct levelflags*p=at;switch(field){
case 0:p->hero_memory=value;return;
default:abort();}}
case 33:{dlevel_t*p=at;switch(field){
case 3:p->objlist=(void*)(uintptr_t)value;return;
case 4:memmove(&p->flags,(void*)(uintptr_t)value,sizeof p->flags);return;
default:abort();}}
case 34:{struct instance_globals_n*p=at;switch(field){
case 0:p->notonhead=value;return;
default:abort();}}
case 35:{struct instance_globals_v*p=at;switch(field){
case 0:p->viz_array=(void*)(uintptr_t)value;return;
default:abort();}}
case 36:{struct instance_globals_y*p=at;switch(field){
case 0:memmove(&p->youmonst,(void*)(uintptr_t)value,sizeof p->youmonst);return;
default:abort();}}
case 37:{struct instance_globals_saved_c*p=at;switch(field){
case 0:memmove(&p->context,(void*)(uintptr_t)value,sizeof p->context);return;
default:abort();}}
case 38:{struct instance_globals_saved_d*p=at;switch(field){
case 0:memmove(&p->dungeon_topology,(void*)(uintptr_t)value,sizeof p->dungeon_topology);return;
default:abort();}}
case 39:{struct instance_globals_saved_l*p=at;switch(field){
case 0:memmove(&p->level,(void*)(uintptr_t)value,sizeof p->level);return;
default:abort();}}
case 40:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=value;return;
default:abort();}}
case 41:{struct const_globals*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_dogmove_address(int kind,void*at,int field){switch(kind){
case 0:{struct d_level*p=at;switch(field){
case 0:return (void*)&p->dnum;
case 1:return (void*)&p->dlevel;
default:abort();}}
case 1:{struct nhcoord*p=at;switch(field){
case 0:return (void*)&p->x;
case 1:return (void*)&p->y;
default:abort();}}
case 2:{union vptrs*p=at;switch(field){
case 0:return (void*)&p->v_nexthere;
default:abort();}}
case 3:{struct flag*p=at;switch(field){
case 0:return (void*)&p->verbose;
default:abort();}}
case 4:{struct trap*p=at;switch(field){
case 0:return (void*)&p->ntrap;
case 1:return (void*)&p->tx;
case 2:return (void*)&p->ty;
default:abort();}}
case 5:{struct window_procs*p=at;switch(field){
case 0:return (void*)&p->win_display_nhwindow;
default:abort();}}
case 6:{struct symdef*p=at;switch(field){
case 0:return (void*)&p->explanation;
default:abort();}}
case 7:{struct obj*p=at;switch(field){
case 0:return (void*)&p->nobj;
case 1:return (void*)&p->v;
case 2:return (void*)&p->o_id;
case 3:return (void*)&p->ox;
case 4:return (void*)&p->oy;
case 5:return (void*)&p->otyp;
case 6:return (void*)&p->owt;
case 7:return (void*)&p->quan;
case 8:return (void*)&p->oclass;
case 9:return (void*)&p->invlet;
case 10:return (void*)&p->oartifact;
case 14:return (void*)&p->corpsenm;
case 15:return (void*)&p->oeaten;
case 16:return (void*)&p->owornmask;
default:abort();}}
case 8:{struct objclass*p=at;switch(field){
case 0:return (void*)&p->oc_name_idx;
case 1:return (void*)&p->oc_descr_idx;
case 2:return (void*)&p->oc_subtyp;
case 3:return (void*)&p->oc_delay;
case 4:return (void*)&p->oc_nutrition;
default:abort();}}
case 9:{struct mfndposdata*p=at;switch(field){
case 0:return (void*)&p->poss;
case 1:return (void*)&p->info;
default:abort();}}
case 10:{struct attack*p=at;switch(field){
case 0:return (void*)&p->aatyp;
default:abort();}}
case 11:{struct permonst*p=at;switch(field){
case 0:return (void*)&p->pmidx;
case 1:return (void*)&p->mlet;
case 2:return (void*)&p->mlevel;
case 3:return (void*)&p->mattk;
case 4:return (void*)&p->cwt;
case 5:return (void*)&p->cnutrit;
case 6:return (void*)&p->msound;
case 7:return (void*)&p->msize;
case 8:return (void*)&p->mflags1;
case 9:return (void*)&p->mflags2;
default:abort();}}
case 12:{struct prop*p=at;switch(field){
case 0:return (void*)&p->extrinsic;
case 1:return (void*)&p->intrinsic;
default:abort();}}
case 13:{struct monst*p=at;switch(field){
case 0:return (void*)&p->data;
case 1:return (void*)&p->m_id;
case 2:return (void*)&p->cham;
case 3:return (void*)&p->m_lev;
case 4:return (void*)&p->mx;
case 5:return (void*)&p->my;
case 6:return (void*)&p->mux;
case 7:return (void*)&p->muy;
case 8:return (void*)&p->mtrack;
case 9:return (void*)&p->mhp;
case 10:return (void*)&p->mhpmax;
case 11:return (void*)&p->mappearance;
case 12:return (void*)&p->m_ap_type;
case 13:return (void*)&p->mtame;
case 27:return (void*)&p->mlstmv;
case 28:return (void*)&p->mstate;
case 29:return (void*)&p->minvent;
case 30:return (void*)&p->mw;
case 31:return (void*)&p->weapon_check;
case 32:return (void*)&p->meating;
case 33:return (void*)&p->mextra;
default:abort();}}
case 14:{struct epri*p=at;switch(field){
case 0:return (void*)&p->shralign;
default:abort();}}
case 15:{struct achievement_tracking*p=at;switch(field){
case 0:return (void*)&p->mines_prize_oid;
case 1:return (void*)&p->soko_prize_oid;
default:abort();}}
case 16:{struct objdescr*p=at;switch(field){
case 0:return (void*)&p->oc_name;
case 1:return (void*)&p->oc_descr;
default:abort();}}
case 17:{struct context_info*p=at;switch(field){
case 0:return (void*)&p->achieveo;
default:abort();}}
case 18:{struct rm*p=at;switch(field){
case 0:return (void*)&p->glyph;
case 1:return (void*)&p->typ;
default:abort();}}
case 19:{struct instance_globals_b*p=at;switch(field){
case 0:return (void*)&p->bhitpos;
default:abort();}}
case 20:{struct emin*p=at;switch(field){
case 0:return (void*)&p->min_align;
default:abort();}}
case 21:{struct edog*p=at;switch(field){
case 0:return (void*)&p->parentmid;
case 1:return (void*)&p->droptime;
case 2:return (void*)&p->dropdist;
case 3:return (void*)&p->apport;
case 4:return (void*)&p->whistletime;
case 5:return (void*)&p->hungrytime;
case 6:return (void*)&p->ogoal;
case 7:return (void*)&p->mhpmax_penalty;
default:abort();}}
case 22:{struct c_common_strings*p=at;switch(field){
case 0:return (void*)&p->c_something;
default:abort();}}
case 23:{struct u_roleplay*p=at;switch(field){
case 0:return (void*)&p->deaf;
default:abort();}}
case 24:{struct mextra*p=at;switch(field){
case 0:return (void*)&p->epri;
case 1:return (void*)&p->emin;
case 2:return (void*)&p->edog;
default:abort();}}
case 25:{struct dgn_topology*p=at;switch(field){
case 0:return (void*)&p->d_rogue_level;
case 1:return (void*)&p->d_qstart_level;
default:abort();}}
case 26:{struct instance_flags*p=at;switch(field){
case 0:return (void*)&p->suppress_price;
default:abort();}}
case 27:{struct instance_globals_f*p=at;switch(field){
case 0:return (void*)&p->ftrap;
default:abort();}}
case 28:{struct instance_globals_g*p=at;switch(field){
case 0:return (void*)&p->gtyp;
case 1:return (void*)&p->gx;
case 2:return (void*)&p->gy;
default:abort();}}
case 29:{struct Gender*p=at;switch(field){
case 0:return (void*)&p->his;
default:abort();}}
case 30:{struct instance_globals_i*p=at;switch(field){
case 0:return (void*)&p->invent;
default:abort();}}
case 31:{struct you*p=at;switch(field){
case 0:return (void*)&p->ux;
case 1:return (void*)&p->uy;
case 2:return (void*)&p->uz;
case 3:return (void*)&p->ulevel;
case 4:return (void*)&p->uprops;
case 6:return (void*)&p->uroleplay;
case 7:return (void*)&p->usteed;
default:abort();}}
case 32:{struct levelflags*p=at;switch(field){
default:abort();}}
case 33:{dlevel_t*p=at;switch(field){
case 0:return (void*)&p->locations;
case 1:return (void*)&p->objects;
case 2:return (void*)&p->monsters;
case 3:return (void*)&p->objlist;
case 4:return (void*)&p->flags;
default:abort();}}
case 34:{struct instance_globals_n*p=at;switch(field){
case 0:return (void*)&p->notonhead;
default:abort();}}
case 35:{struct instance_globals_v*p=at;switch(field){
case 0:return (void*)&p->viz_array;
default:abort();}}
case 36:{struct instance_globals_y*p=at;switch(field){
case 0:return (void*)&p->youmonst;
default:abort();}}
case 37:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return (void*)&p->context;
default:abort();}}
case 38:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return (void*)&p->dungeon_topology;
default:abort();}}
case 39:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return (void*)&p->level;
default:abort();}}
case 40:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return (void*)&p->moves;
default:abort();}}
case 41:{struct const_globals*p=at;switch(field){
case 0:return (void*)&p->zeroobj;
default:abort();}}
default:abort();}}
static char dogmove_literals[DOGMOVE_LITERAL_CAPACITY];
char*teleport_dogmove_literal_storage(void){return dogmove_literals;}
size_t teleport_dogmove_literal_capacity(void){return sizeof dogmove_literals;}
void teleport_dogmove_rng_caller(int site){if(site<0||site>=DOGMOVE_RNG_COUNT)abort();if(rng_log_enabled())rng_log_set_caller(DOGMOVE_SOURCE_FILE,dogmove_rng_lines[site],dogmove_rng_functions[site]);}
int teleport_dogmove_rn2_value(int n){return (rn2)(n);}
int teleport_dogmove_rnd_value(int n){return (rnd)(n);}
extern void teleport_dogmove_wantdoor_callback(coordxy,coordxy,genericptr_t);
void(*teleport_dogmove_callback_pointer(void))(coordxy,coordxy,genericptr_t){return teleport_dogmove_wantdoor_callback;}
char*(*teleport_dogmove_doname_pointer(void))(struct obj*){return doname;}
void teleport_dogmove_display(int win,boolean block){display_nhwindow(win,block);}
void teleport_dogmove_assert(void){__assert_fail("edog->apport > 0",DOGMOVE_SOURCE_FILE,DOGMOVE_ASSERT_LINE,"dog_invent");}
void teleport_dogmove_pline_mon1(struct monst*m,const char*fmt,const char*a0){pline_mon(m,fmt,a0);}
void teleport_dogmove_pline_mon2(struct monst*m,const char*fmt,const char*a0,const char*a1){pline_mon(m,fmt,a0,a1);}
void teleport_dogmove_pline_mon3(struct monst*m,const char*fmt,const char*a0,const char*a1,const char*a2){pline_mon(m,fmt,a0,a1,a2);}
void teleport_dogmove_pline_mon4(struct monst*m,const char*fmt,const char*a0,const char*a1,const char*a2,const char*a3){pline_mon(m,fmt,a0,a1,a2,a3);}
void teleport_dogmove_you2(const char*fmt,const char*a0,const char*a1){You(fmt,a0,a1);}
void teleport_dogmove_you4(const char*fmt,const char*a0,const char*a1,const char*a2,const char*a3){You(fmt,a0,a1,a2,a3);}
void teleport_dogmove_pline2(const char*fmt,const char*a,const char*b){pline(fmt,a,b);}
void teleport_dogmove_price(const char*fmt,const char*a,long n,const char*b){pline(fmt,a,n,b);}
void teleport_dogmove_pline_xy(coordxy x,coordxy y,const char*fmt,const char*a,const char*b){pline_xy(x,y,fmt,a,b);}
void teleport_dogmove_your(const char*fmt){Your("%s",fmt);}
void teleport_dogmove_feel(const char*fmt,const char*a){You_feel(fmt,a);}
void teleport_dogmove_impossible0(const char*fmt){impossible("%s",fmt);}
void teleport_dogmove_impossible7(const char*fmt,int a,int b,long c,long d,int e,unsigned f,unsigned g){impossible(fmt,a,b,c,d,e,f,g);}
