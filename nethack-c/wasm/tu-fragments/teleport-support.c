/* Typed header/field/dependency ABI only. TELEPORT source algorithms/data remain JS. */
#include "../../../scripts/tu-teleport-layout.h"
#include <stdint.h>
#include <string.h>
#include "teleport-source-data.h"
long teleport_teleport_record_get(int kind,int field,void*p){switch(kind){
case 0:{struct monst*v=p;switch(field){
case 0:return(long)(intptr_t)v->nmon;
case 1:return(long)(intptr_t)v->data;
case 2:return(long)v->mx;
case 3:return(long)v->my;
case 4:return(long)v->wormno;
case 5:return(long)v->m_id;
case 6:return(long)v->mtame;
case 7:return(long)v->mstate;
case 8:return(long)v->mleashed;
case 9:return(long)v->iswiz;
case 10:return(long)v->isshk;
case 11:return(long)v->ispriest;
case 12:return(long)v->mpeaceful;
case 13:return(long)(intptr_t)v->minvent;
case 14:return(long)v->mstrategy;
case 15:return(long)v->mconf;
case 16:return(long)v->mtrapped;
case 17:return(long)v->mhp;
case 18:return(long)v->m_ap_type;
}}break;
case 1:{struct permonst*v=p;switch(field){
case 0:return(long)v->mlet;
case 1:return(long)v->mflags1;
case 2:return(long)v->mflags2;
case 3:return(long)v->mflags3;
case 4:return(long)v->geno;
case 5:return(long)(intptr_t)v->pmnames;
case 6:return(long)v->msound;
}}break;
case 2:{struct obj*v=p;switch(field){
case 0:return(long)v->cursed;
case 1:return(long)v->blessed;
case 2:return(long)v->where;
case 3:return(long)v->ox;
case 4:return(long)v->oy;
case 5:return(long)v->oerodeproof;
case 6:return(long)v->otyp;
case 7:return(long)(intptr_t)v->nobj;
case 8:return(long)v->no_charge;
case 9:return(long)v->unpaid;
case 10:return(long)v->corpsenm;
}}break;
case 3:{struct trap*v=p;switch(field){
case 0:return(long)v->ttyp;
case 1:return(long)v->once;
case 2:return(long)v->tseen;
case 3:return(long)(intptr_t)&v->teledest;
case 4:return(long)(intptr_t)&v->dst;
}}break;
case 4:{coord*v=p;switch(field){
case 0:return(long)v->x;
case 1:return(long)v->y;
}}break;
case 5:{d_level*v=p;switch(field){
case 0:return(long)v->dnum;
case 1:return(long)v->dlevel;
}}break;
case 6:{stairway*v=p;switch(field){
case 0:return(long)(intptr_t)v->next;
case 1:return(long)v->sx;
case 2:return(long)v->sy;
case 3:return(long)v->isladder;
case 4:return(long)v->up;
case 5:return(long)(intptr_t)&v->tolev;
}}break;
case 7:{menu_item*v=p;switch(field){
case 0:return(long)(intptr_t)&v->item;
case 1:return(long)v->count;
}}break;
case 8:{anything*v=p;switch(field){
case 0:return(long)v->a_int;
}}break;
case 9:{struct eshk*v=p;switch(field){
case 0:return(long)v->shoproom;
}}break;
case 10:{struct epri*v=p;switch(field){
case 0:return(long)v->shroom;
}}break;
case 11:{dungeon*v=p;switch(field){
case 0:return(long)v->depth_start;
case 1:return(long)v->num_dunlevs;
case 2:return(long)v->dunlev_ureached;
case 3:return(long)v->flags.unconnected;
}}break;
case 12:{struct objclass*v=p;switch(field){
case 0:return(long)v->oc_level;
}}break;
case 13:{struct rm*v=p;switch(field){
case 0:return(long)v->typ;
case 1:return(long)v->roomno;
}}break;
}return 0;}
void teleport_teleport_record_set(int kind,int field,void*p,long value){switch(kind){
case 0:{struct monst*v=p;switch(field){
case 0:v->nmon=(void*)(intptr_t)value;return;
case 1:v->data=(void*)(intptr_t)value;return;
case 2:v->mx=value;return;
case 3:v->my=value;return;
case 4:v->wormno=value;return;
case 5:v->m_id=value;return;
case 6:v->mtame=value;return;
case 7:v->mstate=value;return;
case 8:v->mleashed=value;return;
case 9:v->iswiz=value;return;
case 10:v->isshk=value;return;
case 11:v->ispriest=value;return;
case 12:v->mpeaceful=value;return;
case 13:v->minvent=(void*)(intptr_t)value;return;
case 14:v->mstrategy=value;return;
case 15:v->mconf=value;return;
case 16:v->mtrapped=value;return;
case 17:v->mhp=value;return;
case 18:v->m_ap_type=value;return;
}}break;
case 1:{struct permonst*v=p;switch(field){
case 0:v->mlet=value;return;
case 1:v->mflags1=value;return;
case 2:v->mflags2=value;return;
case 3:v->mflags3=value;return;
case 4:v->geno=value;return;
case 6:v->msound=value;return;
}}break;
case 2:{struct obj*v=p;switch(field){
case 0:v->cursed=value;return;
case 1:v->blessed=value;return;
case 2:v->where=value;return;
case 3:v->ox=value;return;
case 4:v->oy=value;return;
case 5:v->oerodeproof=value;return;
case 6:v->otyp=value;return;
case 7:v->nobj=(void*)(intptr_t)value;return;
case 8:v->no_charge=value;return;
case 9:v->unpaid=value;return;
case 10:v->corpsenm=value;return;
}}break;
case 3:{struct trap*v=p;switch(field){
case 0:v->ttyp=value;return;
case 1:v->once=value;return;
case 2:v->tseen=value;return;
}}break;
case 4:{coord*v=p;switch(field){
case 0:v->x=value;return;
case 1:v->y=value;return;
}}break;
case 5:{d_level*v=p;switch(field){
case 0:v->dnum=value;return;
case 1:v->dlevel=value;return;
}}break;
case 6:{stairway*v=p;switch(field){
case 0:v->next=(void*)(intptr_t)value;return;
case 1:v->sx=value;return;
case 2:v->sy=value;return;
case 3:v->isladder=value;return;
case 4:v->up=value;return;
}}break;
case 7:{menu_item*v=p;switch(field){
case 1:v->count=value;return;
}}break;
case 8:{anything*v=p;switch(field){
case 0:v->a_int=value;return;
}}break;
case 9:{struct eshk*v=p;switch(field){
case 0:v->shoproom=value;return;
}}break;
case 10:{struct epri*v=p;switch(field){
case 0:v->shroom=value;return;
}}break;
case 11:{dungeon*v=p;switch(field){
case 0:v->depth_start=value;return;
case 1:v->num_dunlevs=value;return;
case 2:v->dunlev_ureached=value;return;
case 3:v->flags.unconnected=value;return;
}}break;
case 12:{struct objclass*v=p;switch(field){
case 0:v->oc_level=value;return;
}}break;
case 13:{struct rm*v=p;switch(field){
case 0:v->typ=value;return;
case 1:v->roomno=value;return;
}}break;
}}
long teleport_teleport_get(int i){switch(i){
case 0:return(long)ETeleportation;
case 1:return(long)HConfusion;
case 2:return(long)HStun;
case 3:return(long)HTeleportation;
case 4:return(long)WIN_MESSAGE;
case 5:return(long)disp.botl;
case 6:return(long)flags.verbose;
case 7:return(long)gi.in_mklev;
case 8:return(long)(intptr_t)gi.invent;
case 9:return(long)(intptr_t)go.occupation;
case 10:return(long)gv.vision_full_recalc;
case 11:return(long)iflags.debug_fuzzer;
case 12:return(long)iflags.last_msg;
case 13:return(long)iflags.menu_requested;
case 14:return(long)iflags.mon_telecontrol;
case 15:return(long)svd.dndest.hx;
case 16:return(long)svd.dndest.hy;
case 17:return(long)svd.dndest.lx;
case 18:return(long)svd.dndest.ly;
case 19:return(long)svd.dndest.nhx;
case 20:return(long)svd.dndest.nhy;
case 21:return(long)svd.dndest.nlx;
case 22:return(long)svd.dndest.nly;
case 23:return(long)svk.killer.format;
case 24:return(long)(intptr_t)svk.killer.name;
case 25:return(long)svl.level.flags.noteleport;
case 26:return(long)svl.level.flags.stasis_until;
case 27:return(long)svm.moves;
case 28:return(long)svn.n_dgns;
case 29:return(long)svu.updest.hx;
case 30:return(long)svu.updest.hy;
case 31:return(long)svu.updest.lx;
case 32:return(long)svu.updest.ly;
case 33:return(long)svu.updest.nhx;
case 34:return(long)svu.updest.nhy;
case 35:return(long)svu.updest.nlx;
case 36:return(long)svu.updest.nly;
case 37:return(long)u.uen;
case 38:return(long)u.uevent.invoked;
case 39:return(long)u.uhave.amulet;
case 40:return(long)u.uhunger;
case 41:return(long)u.ulevel;
case 42:return(long)u.umonster;
case 43:return(long)(intptr_t)u.urooms;
case 44:return(long)(intptr_t)u.ushops;
case 45:return(long)(intptr_t)u.ushops0;
case 46:return(long)u.uswallow;
case 47:return(long)u.utrap;
case 48:return(long)u.utraptype;
case 49:return(long)u.ux;
case 50:return(long)u.ux0;
case 51:return(long)u.uy;
case 52:return(long)u.uy0;
}return 0;}
void teleport_teleport_set(int i,long value){switch(i){
case 0:ETeleportation=value;return;
case 1:HConfusion=value;return;
case 2:HStun=value;return;
case 3:HTeleportation=value;return;
case 4:WIN_MESSAGE=value;return;
case 5:disp.botl=value;return;
case 6:flags.verbose=value;return;
case 7:gi.in_mklev=value;return;
case 8:gi.invent=(void*)(intptr_t)value;return;
case 9:go.occupation=(void*)(intptr_t)value;return;
case 10:gv.vision_full_recalc=value;return;
case 11:iflags.debug_fuzzer=value;return;
case 12:iflags.last_msg=value;return;
case 13:iflags.menu_requested=value;return;
case 14:iflags.mon_telecontrol=value;return;
case 15:svd.dndest.hx=value;return;
case 16:svd.dndest.hy=value;return;
case 17:svd.dndest.lx=value;return;
case 18:svd.dndest.ly=value;return;
case 19:svd.dndest.nhx=value;return;
case 20:svd.dndest.nhy=value;return;
case 21:svd.dndest.nlx=value;return;
case 22:svd.dndest.nly=value;return;
case 23:svk.killer.format=value;return;
case 25:svl.level.flags.noteleport=value;return;
case 26:svl.level.flags.stasis_until=value;return;
case 27:svm.moves=value;return;
case 28:svn.n_dgns=value;return;
case 29:svu.updest.hx=value;return;
case 30:svu.updest.hy=value;return;
case 31:svu.updest.lx=value;return;
case 32:svu.updest.ly=value;return;
case 33:svu.updest.nhx=value;return;
case 34:svu.updest.nhy=value;return;
case 35:svu.updest.nlx=value;return;
case 36:svu.updest.nly=value;return;
case 37:u.uen=value;return;
case 38:u.uevent.invoked=value;return;
case 39:u.uhave.amulet=value;return;
case 40:u.uhunger=value;return;
case 41:u.ulevel=value;return;
case 42:u.umonster=value;return;
case 46:u.uswallow=value;return;
case 47:u.utrap=value;return;
case 48:u.utraptype=value;return;
case 49:u.ux=value;return;
case 50:u.ux0=value;return;
case 51:u.uy=value;return;
case 52:u.uy0=value;return;
}}
void*teleport_teleport_address(int i){switch(i){
case 0:return(void*)&gy.youmonst;
case 1:return(void*)&cg.zeroany;
case 2:return(void*)&cg.zeromonst;
case 3:return(void*)gc.current_wand;
case 4:return(void*)u.ustuck;
case 5:return(void*)u.usteed;
case 6:return(void*)gs.stairs;
case 7:return(void*)&iflags.travelcc;
case 8:return(void*)&u.uz;
case 9:return(void*)&u.uz0;
case 10:return(void*)&u.ucamefrom;
case 11:return(void*)&astral_level;
case 12:return(void*)&medusa_level;
case 13:return(void*)&mineend_level;
case 14:return(void*)&qlocate_level;
case 15:return(void*)&qstart_level;
case 16:return(void*)&sanctum_level;
case 17:return(void*)&valley_level;
case 18:return(void*)&nul_glyphinfo;
case 19:return(void*)shudder_for_moment;
case 20:return(void*)uball;
case 21:return(void*)uchain;
case 22:return(void*)uarmf;
case 23:return(void*)fmon;
}return 0;}
long teleport_teleport_hero(int i){switch(i){case 0:return !!(Amphibious);case 1:return !!(Antimagic);case 2:return !!(Blind);case 3:return !!(Blinded);case 4:return !!(Confusion);case 5:return !!(Fire_resistance);case 6:return !!(Flying);case 7:return !!(Hallucination);case 8:return !!(Inhell);case 9:return !!(Levitation);case 10:return !!(Passes_walls);case 11:return !!(Punished);case 12:return !!(Stunned);case 13:return !!(Swimming);case 14:return !!(Teleport_control);case 15:return !!(Teleportation);case 16:return !!(Upolyd);case 17:return !!(Wwalking);case 18:return !!(wizard);}return 0;}
void*teleport_teleport_array(int k,int x,int y){switch(k){case 0:return &mons[x];case 1:return &objects[x];case 2:return &svd.dungeons[x];case 3:return &levl[x][y];}return 0;}
void*teleport_teleport_mat(coordxy x,coordxy y){return m_at(x,y);}
void teleport_teleport_remove_monster(coordxy x,coordxy y){remove_monster(x,y);}
void*teleport_teleport_pmname(struct permonst*p,int i){return(void*)p->pmnames[i];}
void*teleport_teleport_eshk(struct monst*p){return ESHK(p);}
void*teleport_teleport_epri(struct monst*p){return EPRI(p);}
void teleport_teleport_copy(void*out,const void*in,size_t n){memcpy(out,in,n);}
int teleport_teleport_filter(void*p,coordxy x,coordxy y){return((boolean(*)(coordxy,coordxy))p)(x,y);}
#ifndef TELEPORT_TELEPORT_VALIDATE_SOURCE
extern boolean teleport_teleport_callback_m_blocks_teleporting(struct monst*);
#endif
void*teleport_teleport_blocker(void){
#ifdef TELEPORT_TELEPORT_VALIDATE_SOURCE
return(void*)m_blocks_teleporting;
#else
return(void*)teleport_teleport_callback_m_blocks_teleporting;
#endif
}
int teleport_teleport_dep_ACURR(int a){return ACURR(a);}
char * teleport_teleport_dep_Amonnam(struct monst * a0){return Amonnam(a0);}
int teleport_teleport_dep_DEADMONSTER(struct monst* p){return DEADMONSTER(p);}
int teleport_teleport_dep_IS_ALTAR(int n){return IS_ALTAR(n);}
boolean teleport_teleport_dep_In_W_tower(coordxy a0,coordxy a1,d_level * a2){return In_W_tower(a0,a1,a2);}
int teleport_teleport_dep_In_endgame(d_level* p){return In_endgame(p);}
boolean teleport_teleport_dep_In_hell(d_level * a0){return In_hell(a0);}
boolean teleport_teleport_dep_In_mines(d_level * a0){return In_mines(a0);}
boolean teleport_teleport_dep_In_quest(d_level * a0){return In_quest(a0);}
int teleport_teleport_dep_In_sokoban(d_level* p){return In_sokoban(p);}
int teleport_teleport_dep_In_tutorial(d_level* p){return In_tutorial(p);}
boolean teleport_teleport_dep_Is_botlevel(d_level * a0){return Is_botlevel(a0);}
int teleport_teleport_dep_Is_stronghold(d_level* p){return Is_stronghold(p);}
int teleport_teleport_dep_Is_waterlevel(d_level* p){return Is_waterlevel(p);}
int teleport_teleport_dep_MON_AT(coordxy x,coordxy y){return MON_AT(x,y);}
char * teleport_teleport_dep_Monnam(struct monst * a0){return Monnam(a0);}
boolean teleport_teleport_dep_On_W_tower_level(d_level * a0){return On_W_tower_level(a0);}
int teleport_teleport_dep_Role_if(int n){return Role_if(n);}
char * teleport_teleport_dep_Strcat(char *restrict a0,const char *restrict a1){return strcat(a0,a1);}
char * teleport_teleport_dep_Strcpy(char *restrict a0,const char *restrict a1){return strcpy(a0,a1);}
int teleport_teleport_dep_ZAP_POS(int n){return ZAP_POS(n);}
boolean teleport_teleport_dep_accessible(coordxy a0,coordxy a1){return accessible(a0,a1);}
void teleport_teleport_dep_add_menu(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){add_menu(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
struct obj * teleport_teleport_dep_addinv(struct obj * a0){return addinv(a0);}
void teleport_teleport_dep_addtobill(struct obj * a0,boolean a1,boolean a2,boolean a3){addtobill(a0,a1,a2,a3);}
int teleport_teleport_dep_amorphous(struct permonst* p){return amorphous(p);}
void teleport_teleport_dep_assign_level(d_level * a0,d_level * a1){assign_level(a0,a1);}
int teleport_teleport_dep_atoi(const char * a0){return atoi(a0);}
void teleport_teleport_dep_buried_ball_to_punishment(void){buried_ball_to_punishment();}
int teleport_teleport_dep_can_teleport(struct permonst* p){return can_teleport(p);}
int teleport_teleport_dep_canseemon(struct monst * a0){return canseemon(a0);}
int teleport_teleport_dep_canspotmon(struct monst* p){return canspotmon(p);}
int teleport_teleport_dep_carried(struct obj* p){return carried(p);}
boolean teleport_teleport_dep_check_capacity(const char * a0){return check_capacity(a0);}
void teleport_teleport_dep_check_special_room(boolean a0){check_special_room(a0);}
d_level * teleport_teleport_dep_clamp_hole_destination(d_level * a0){return clamp_hole_destination(a0);}
boolean teleport_teleport_dep_closed_door(coordxy a0,coordxy a1){return closed_door(a0,a1);}
int teleport_teleport_dep_control_teleport(struct permonst* p){return control_teleport(p);}
boolean teleport_teleport_dep_costly_adjacent(struct monst * a0,coordxy a1,coordxy a2){return costly_adjacent(a0,a1,a2);}
boolean teleport_teleport_dep_costly_spot(coordxy a0,coordxy a1){return costly_spot(a0,a1);}
int teleport_teleport_dep_couldsee(coordxy x,coordxy y){return couldsee(x,y);}
winid teleport_teleport_dep_create_nhwindow(int a0){return create_nhwindow(a0);}
void teleport_teleport_dep_deltrap(struct trap * a0){deltrap(a0);}
schar teleport_teleport_dep_depth(d_level * a0){return depth(a0);}
void teleport_teleport_dep_destroy_nhwindow(winid a0){destroy_nhwindow(a0);}
boolean teleport_teleport_dep_digit(char a0){return digit(a0);}
void teleport_teleport_dep_display_nhwindow(winid a0,boolean a1){display_nhwindow(a0,a1);}
int teleport_teleport_dep_distmin(coordxy a0,coordxy a1,coordxy a2,coordxy a3){return distmin(a0,a1,a2,a3);}
int teleport_teleport_dep_distu(coordxy x,coordxy y){return distu(x,y);}
int teleport_teleport_dep_dochugw(struct monst * a0,boolean a1){return dochugw(a0,a1);}
void teleport_teleport_dep_docrt(void){docrt();}
void teleport_teleport_dep_done(int a0){done(a0);}
boolean teleport_teleport_dep_drag_ball(coordxy a0,coordxy a1,int * a2,coordxy * a3,coordxy * a4,coordxy * a5,coordxy * a6,boolean * a7,boolean a8){return drag_ball(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_teleport_dep_dunlev_reached(d_level* p){return dunlev_reached(p);}
xint16 teleport_teleport_dep_dunlevs_in_dungeon(d_level * a0){return dunlevs_in_dungeon(a0);}
void teleport_teleport_dep_end_menu(winid a0,const char* a1){end_menu(a0,a1);}
int teleport_teleport_dep_engulfing_u(struct monst* p){return engulfing_u(p);}
char * teleport_teleport_dep_eos(char * a0){return eos(a0);}
void teleport_teleport_dep_exercise(int a0,boolean a1){exercise(a0,a1);}
void teleport_teleport_dep_fill_pit(coordxy a0,coordxy a1){fill_pit(a0,a1);}
void teleport_teleport_dep_find_hell(d_level * a0){find_hell(a0);}
struct monst * teleport_teleport_dep_find_objowner(struct obj * a0,coordxy a1,coordxy a2){return find_objowner(a0,a1,a2);}
struct monst * teleport_teleport_dep_findgd(void){return findgd();}
boolean teleport_teleport_dep_flooreffects(struct obj * a0,coordxy a1,coordxy a2,const char * a3){return flooreffects(a0,a1,a2,a3);}
void teleport_teleport_dep_free(void * a0){free(a0);}
struct monst * teleport_teleport_dep_get_iter_mons(boolean (*a0)(struct monst *)){return get_iter_mons(a0);}
void teleport_teleport_dep_get_level(d_level * a0,int a1){get_level(a0,a1);}
struct obj * teleport_teleport_dep_get_mleash(struct monst * a0){return get_mleash(a0);}
void teleport_teleport_dep_getlin(const char * a0,char * a1){getlin(a0,a1);}
int teleport_teleport_dep_getpos(coord * a0,boolean a1,const char * a2){return getpos(a0,a1,a2);}
int teleport_teleport_dep_haseyes(struct permonst* p){return haseyes(p);}
boolean teleport_teleport_dep_hideunder(struct monst * a0){return hideunder(a0);}
boolean teleport_teleport_dep_in_out_region(coordxy a0,coordxy a1){return in_out_region(a0,a1);}
char * teleport_teleport_dep_in_rooms(coordxy a0,coordxy a1,int a2){return in_rooms(a0,a1,a2);}
int teleport_teleport_dep_inhishop(struct monst * a0){return inhishop(a0);}
boolean teleport_teleport_dep_inhistemple(struct monst * a0){return inhistemple(a0);}
void teleport_teleport_dep_invocation_message(void){invocation_message();}
int teleport_teleport_dep_is_covetous(struct permonst* p){return is_covetous(p);}
int teleport_teleport_dep_is_dlord(struct permonst* p){return is_dlord(p);}
int teleport_teleport_dep_is_dprince(struct permonst* p){return is_dprince(p);}
boolean teleport_teleport_dep_is_exclusion_zone(xint16 a0,coordxy a1,coordxy a2){return is_exclusion_zone(a0,a1,a2);}
int teleport_teleport_dep_is_hole(int n){return is_hole(n);}
boolean teleport_teleport_dep_is_home_elemental(struct permonst * a0){return is_home_elemental(a0);}
boolean teleport_teleport_dep_is_lava(coordxy a0,coordxy a1){return is_lava(a0,a1);}
int teleport_teleport_dep_is_pit(int n){return is_pit(n);}
boolean teleport_teleport_dep_is_pool(coordxy a0,coordxy a1){return is_pool(a0,a1);}
int teleport_teleport_dep_is_rider(struct permonst* p){return is_rider(p);}
int teleport_teleport_dep_is_silent(struct permonst* p){return is_silent(p);}
int teleport_teleport_dep_is_swimmer(struct permonst* p){return is_swimmer(p);}
boolean teleport_teleport_dep_is_waterwall(coordxy a0,coordxy a1){return is_waterwall(a0,a1);}
int teleport_teleport_dep_is_xport(int n){return is_xport(n);}
int teleport_teleport_dep_isok(coordxy a0,coordxy a1){return isok(a0,a1);}
int teleport_teleport_dep_known_spell(short a0){return known_spell(a0);}
void teleport_teleport_dep_learnscroll(struct obj * a0){learnscroll(a0);}
xint16 teleport_teleport_dep_ledger_no(d_level * a0){return ledger_no(a0);}
schar teleport_teleport_dep_lev_by_name(const char * a0){return lev_by_name(a0);}
int teleport_teleport_dep_likes_lava(struct permonst* p){return likes_lava(p);}
boolean teleport_teleport_dep_m_in_air(struct monst * a0){return m_in_air(a0);}
void teleport_teleport_dep_m_into_limbo(struct monst * a0){m_into_limbo(a0);}
int teleport_teleport_dep_m_next2u(struct monst* p){return m_next2u(p);}
void teleport_teleport_dep_m_unleash(struct monst * a0,boolean a1){m_unleash(a0,a1);}
void teleport_teleport_dep_make_angry_shk(struct monst * a0,coordxy a1,coordxy a2){make_angry_shk(a0,a1,a2);}
void teleport_teleport_dep_make_blinded(long a0,boolean a1){make_blinded(a0,a1);}
void teleport_teleport_dep_make_confused(long a0,boolean a1){make_confused(a0,a1);}
void teleport_teleport_dep_make_stunned(long a0,boolean a1){make_stunned(a0,a1);}
boolean teleport_teleport_dep_may_passwall(coordxy a0,coordxy a1){return may_passwall(a0,a1);}
void teleport_teleport_dep_maybe_unhide_at(coordxy a0,coordxy a1){maybe_unhide_at(a0,a1);}
void teleport_teleport_dep_migrate_to_level(struct monst * a0,xint16 a1,xint16 a2,coord * a3){migrate_to_level(a0,a1,a2,a3);}
int teleport_teleport_dep_mintrap(struct monst * a0,unsigned int a1){return mintrap(a0,a1);}
struct obj * teleport_teleport_dep_mksobj(int a0,boolean a1,boolean a2){return mksobj(a0,a1,a2);}
int teleport_teleport_dep_mon_has_amulet(struct monst * a0){return mon_has_amulet(a0);}
char * teleport_teleport_dep_mon_nam(struct monst * a0){return mon_nam(a0);}
int teleport_teleport_dep_mon_offmap(struct monst* p){return mon_offmap(p);}
void teleport_teleport_dep_mon_track_clear(struct monst * a0){mon_track_clear(a0);}
void teleport_teleport_dep_morehungry(int a0){morehungry(a0);}
void teleport_teleport_dep_move_bc(int a0,int a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5){move_bc(a0,a1,a2,a3,a4,a5);}
int teleport_teleport_dep_near_capacity(void){return near_capacity();}
void teleport_teleport_dep_newsym(coordxy a0,coordxy a1){newsym(a0,a1);}
boolean teleport_teleport_dep_next_to_u(void){return next_to_u();}
char * teleport_teleport_dep_noit_mon_nam(struct monst * a0){return noit_mon_nam(a0);}
void teleport_teleport_dep_nomul(int a0){nomul(a0);}
void teleport_teleport_dep_notice_all_mons(boolean a0){notice_all_mons(a0);}
void teleport_teleport_dep_obj_extract_self(struct obj * a0){obj_extract_self(a0);}
boolean teleport_teleport_dep_on_level(d_level * a0,d_level * a1){return on_level(a0,a1);}
boolean teleport_teleport_dep_onscary(coordxy a0,coordxy a1,struct monst * a2){return onscary(a0,a1,a2);}
boolean teleport_teleport_dep_onshopbill(struct obj * a0,struct monst * a1,boolean a2){return onshopbill(a0,a1,a2);}
int teleport_teleport_dep_passes_walls(struct permonst* p){return passes_walls(p);}
void teleport_teleport_dep_place_monster(struct monst * a0,coordxy a1,coordxy a2){place_monster(a0,a1,a2);}
void teleport_teleport_dep_place_object(struct obj * a0,coordxy a1,coordxy a2){place_object(a0,a1,a2);}
void teleport_teleport_dep_place_worm_tail_randomly(struct monst * a0,coordxy a1,coordxy a2){place_worm_tail_randomly(a0,a1,a2);}
void teleport_teleport_dep_placebc(void){placebc();}
schar teleport_teleport_dep_print_dungeon(boolean a0,schar * a1,xint16 * a2){return print_dungeon(a0,a1,a2);}
void teleport_teleport_dep_prinv(const char * a0,struct obj * a1,long a2){prinv(a0,a1,a2);}
void teleport_teleport_dep_remove_worm(struct monst * a0){remove_worm(a0);}
void teleport_teleport_dep_reset_utrap(boolean a0){reset_utrap(a0);}
boolean teleport_teleport_dep_revive_corpse(struct obj * a0){return revive_corpse(a0);}
void teleport_teleport_dep_schedule_goto(d_level * a0,int a1,const char * a2,const char * a3){schedule_goto(a0,a1,a2,a3);}
struct mkroom * teleport_teleport_dep_search_special(schar a0){return search_special(a0);}
void teleport_teleport_dep_see_monsters(void){see_monsters();}
void teleport_teleport_dep_seetrap(struct trap * a0){seetrap(a0);}
int teleport_teleport_dep_select_menu(winid a0,int a1,menu_item ** a2){return select_menu(a0,a1,a2);}
struct engr * teleport_teleport_dep_sengr_at(const char * a0,coordxy a1,coordxy a2,boolean a3){return sengr_at(a0,a1,a2,a3);}
int teleport_teleport_dep_sensemon(struct monst * a0){return sensemon(a0);}
void teleport_teleport_dep_set_apparxy(struct monst * a0){set_apparxy(a0);}
void teleport_teleport_dep_set_mon_data(struct monst * a0,struct permonst * a1){set_mon_data(a0,a1);}
void teleport_teleport_dep_set_msg_xy(coordxy a0,coordxy a1){set_msg_xy(a0,a1);}
void teleport_teleport_dep_set_ustuck(struct monst * a0){set_ustuck(a0);}
void teleport_teleport_dep_settrack(void){settrack();}
void teleport_teleport_dep_shieldeff(coordxy a0,coordxy a1){shieldeff(a0,a1);}
boolean teleport_teleport_dep_single_level_branch(d_level * a0){return single_level_branch(a0);}
struct obj * teleport_teleport_dep_sobj_at(int a0,coordxy a1,coordxy a2){return sobj_at(a0,a1,a2);}
boolean teleport_teleport_dep_somexyspace(struct mkroom * a0,coord * a1){return somexyspace(a0,a1);}
int teleport_teleport_dep_spelleffects(int a0,boolean a1,boolean a2){return spelleffects(a0,a1,a2);}
void teleport_teleport_dep_spoteffects(boolean a0){spoteffects(a0);}
void teleport_teleport_dep_start_menu(winid a0,unsigned long a1){start_menu(a0,a1);}
long teleport_teleport_dep_stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){return stolen_value(a0,a1,a2,a3,a4);}
char * teleport_teleport_dep_strchr(const char * a0,int a1){return strchr(a0,a1);}
int teleport_teleport_dep_strcmp(const char * a0,const char * a1){return strcmp(a0,a1);}
void teleport_teleport_dep_subfrombill(struct obj * a0,struct monst * a1){subfrombill(a0,a1);}
const char * teleport_teleport_dep_surface(coordxy a0,coordxy a1){return surface(a0,a1);}
void teleport_teleport_dep_switch_terrain(void){switch_terrain();}
struct trap * teleport_teleport_dep_t_at(coordxy a0,coordxy a1){return t_at(a0,a1);}
int teleport_teleport_dep_throws_rocks(struct permonst* p){return throws_rocks(p);}
int teleport_teleport_dep_tport_spell(int a0){return tport_spell(a0);}
int teleport_teleport_dep_u_at(coordxy x,coordxy y){return u_at(x,y);}
void teleport_teleport_dep_u_left_shop(char * a0,boolean a1){u_left_shop(a0,a1);}
const char * teleport_teleport_dep_u_locomotion(const char * a0){return u_locomotion(a0);}
void teleport_teleport_dep_u_on_newpos(coordxy a0,coordxy a1){u_on_newpos(a0,a1);}
const char* teleport_teleport_dep_uhis(void){return uhis();}
void teleport_teleport_dep_uleftvault(struct monst * a0){uleftvault(a0);}
boolean teleport_teleport_dep_unconscious(void){return unconscious();}
int teleport_teleport_dep_unique_corpstat(struct permonst* p){return unique_corpstat(p);}
void teleport_teleport_dep_unplacebc(void){unplacebc();}
void teleport_teleport_dep_unstuck(struct monst * a0){unstuck(a0);}
void teleport_teleport_dep_update_monster_region(struct monst * a0){update_monster_region(a0);}
void teleport_teleport_dep_update_player_regions(void){update_player_regions();}
char teleport_teleport_dep_vault_occupied(char * a0){return vault_occupied(a0);}
void teleport_teleport_dep_vision_recalc(int a0){vision_recalc(a0);}
int teleport_teleport_dep_within_bounded_area(coordxy x,coordxy y,coordxy lx,coordxy ly,coordxy hx,coordxy hy){return within_bounded_area(x,y,lx,ly,hx,hy);}
char teleport_teleport_dep_y_n(const char* s){return y_n(s);}
void teleport_teleport_dep_yelp(struct monst * a0){yelp(a0);}
char teleport_teleport_dep_ynq(const char* s){return ynq(s);}
void teleport_teleport_notice_off(void){notice_mon_off();}
void teleport_teleport_notice_on(void){notice_mon_on();}
void teleport_teleport_setvoice(void*p,int a,int b,int c){SetVoice(p,a,b,c);}
void teleport_teleport_makeknown(int n){makeknown(n);}
void teleport_teleport_rng_caller(int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("teleport.c",line,fn);}
int teleport_teleport_rn2(int n){return(rn2)(n);}
int teleport_teleport_rnd(int n){return(rnd)(n);}
int teleport_teleport_rnl(int n){return(rnl)(n);}
void teleport_teleport_format(char*out,const char*f,const char*a,const char*b){Sprintf(out,f,a,b);}
void teleport_teleport_pline(const char*f,const char*a,const char*b,const char*c,const char*d){pline(f,a,b,c,d);}
void teleport_teleport_You(const char*f,const char*a,const char*b,const char*c,const char*d){You(f,a,b,c,d);}
void teleport_teleport_You_cant(const char*f,const char*a,const char*b,const char*c,const char*d){You_cant(f,a,b,c,d);}
void teleport_teleport_You_feel(const char*f,const char*a,const char*b,const char*c,const char*d){You_feel(f,a,b,c,d);}
void teleport_teleport_Your(const char*f,const char*a,const char*b,const char*c,const char*d){Your(f,a,b,c,d);}
void teleport_teleport_verbalize(const char*f,const char*a,const char*b,const char*c,const char*d){verbalize(f,a,b,c,d);}
void teleport_teleport_impossible(const char*f,const char*a,const char*b,const char*c,const char*d){impossible(f,a,b,c,d);}
void teleport_teleport_impossible_int(const char*f,int n){impossible(f,n);}
void teleport_teleport_you1(const char*s){You1(s);}
void teleport_teleport_pline_mon(struct monst*p,const char*f,const char*a,const char*b){pline_mon(p,f,a,b);}
int teleport_teleport_debug_enabled(void){return showdebug(TELEPORT_SOURCE_FILE); }
void teleport_teleport_debug0(const char*s){pline("%s",s);}
void teleport_teleport_debug_ints(const char*s,int a,int b,int c,int d){pline(s,a,b,c,d);}
void teleport_teleport_debug_fail(const char*s,const char*a,int b,int c,unsigned long d){pline(s,a,b,c,d);}
static char teleport_teleport_literals[3131];
void*teleport_teleport_literal_storage(void){return teleport_teleport_literals;}
size_t teleport_teleport_literal_capacity(void){return sizeof teleport_teleport_literals;}
_Static_assert(sizeof(coordxy)==2 && sizeof(boolean)==1 && sizeof(mmflags_nht)==4,"TELEPORT scalar widths changed");
_Static_assert(ROWNO==21 && COLNO==80,"TELEPORT map dimensions changed");
