/* DUNGEON ABI/header/native dependency transport and zero backing only. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include "dgn_file.h"
#include "dlb.h"
struct proto_dungeon {
    struct tmpdungeon tmpdungeon[MAXDUNGEON];
    struct tmplevel tmplevel[LEV_LIMIT];
    s_level *final_lev[LEV_LIMIT]; /* corresponding level pointers */
    struct tmpbranch tmpbranch[BRANCH_LIMIT];

    int start;  /* starting index of current dungeon sp levels */
    int n_levs; /* number of tmplevel entries */
    int n_brs;  /* number of tmpbranch entries */
};
struct lchoice {
    int idx;
    schar lev[MAXLINFO];
    schar playerlev[MAXLINFO];
    xint16 dgn[MAXLINFO];
    char menuletter;
};
struct level_map {
    const char *lev_name;
    d_level *lev_spec;
};
extern const struct shclass shtypes[];
_Static_assert(sizeof(void*)==8 && sizeof(long)==8 && sizeof(size_t)==8,"DUNGEON memory64 LP64 ABI");
_Static_assert(sizeof(int)==4 && sizeof(coordxy)==2 && (coordxy)-1<0 && sizeof(boolean)==1 && (boolean)-1<0 && (char)-1<0,"DUNGEON signed native scalar ABI");
void*teleport_dungeon_global(int index){switch(index){
case 0:return(void*)&svd;
case 1:return(void*)&svn;
case 2:return(void*)&stderr;
case 3:return(void*)&svs;
case 4:return(void*)&svb;
case 5:return(void*)&svt;
case 6:return(void*)&svl;
case 7:return(void*)&svi;
case 8:return(void*)&svm;
case 9:return(void*)&flags;
case 10:return(void*)&emptystr;
case 11:return(void*)&iflags;
case 12:return(void*)&gu;
case 13:return(void*)&WIN_MAP;
case 14:return(void*)&windowprocs;
case 15:return(void*)&u;
case 16:return(void*)&svu;
case 17:return(void*)&cg;
case 18:return(void*)&nul_glyphinfo;
case 19:return(void*)&gf;
case 20:return(void*)&sve;
case 21:return(void*)&svq;
case 22:return(void*)&svr;
case 23:return(void*)&vowels;
case 24:return(void*)&shtypes;
default:abort();}}
uint64_t teleport_dungeon_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(dlevel_t));
case 6:return(uint64_t)(sizeof(struct Race));
case 7:return(uint64_t)(sizeof(struct Role));
case 8:return(uint64_t)(sizeof(struct align));
case 9:return(uint64_t)(sizeof(struct branch));
case 10:return(uint64_t)(sizeof(struct cemetery));
case 11:return(uint64_t)(sizeof(struct const_globals));
case 12:return(uint64_t)(sizeof(struct couple));
case 13:return(uint64_t)(sizeof(struct d_flags));
case 14:return(uint64_t)(sizeof(struct d_level));
case 15:return(uint64_t)(sizeof(struct dest_area));
case 16:return(uint64_t)(sizeof(struct dgn_topology));
case 17:return(uint64_t)(sizeof(struct dungeon));
case 18:return(uint64_t)(sizeof(struct exclusion_zone));
case 19:return(uint64_t)(sizeof(struct flag));
case 20:return(uint64_t)(sizeof(struct instance_flags));
case 21:return(uint64_t)(sizeof(struct instance_globals_f));
case 22:return(uint64_t)(sizeof(struct instance_globals_saved_b));
case 23:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 24:return(uint64_t)(sizeof(struct instance_globals_saved_e));
case 25:return(uint64_t)(sizeof(struct instance_globals_saved_i));
case 26:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 27:return(uint64_t)(sizeof(struct instance_globals_saved_m));
case 28:return(uint64_t)(sizeof(struct instance_globals_saved_n));
case 29:return(uint64_t)(sizeof(struct instance_globals_saved_q));
case 30:return(uint64_t)(sizeof(struct instance_globals_saved_r));
case 31:return(uint64_t)(sizeof(struct instance_globals_saved_s));
case 32:return(uint64_t)(sizeof(struct instance_globals_saved_t));
case 33:return(uint64_t)(sizeof(struct instance_globals_saved_u));
case 34:return(uint64_t)(sizeof(struct instance_globals_u));
case 35:return(uint64_t)(sizeof(struct lchoice));
case 36:return(uint64_t)(sizeof(struct level_map));
case 37:return(uint64_t)(sizeof(struct levelflags));
case 38:return(uint64_t)(sizeof(struct linfo));
case 39:return(uint64_t)(sizeof(struct mapseen));
case 40:return(uint64_t)(sizeof(struct mapseen_feat));
case 41:return(uint64_t)(sizeof(struct mapseen_flags));
case 42:return(uint64_t)(sizeof(struct mapseen_rooms));
case 43:return(uint64_t)(sizeof(struct mi));
case 44:return(uint64_t)(sizeof(struct mkroom));
case 45:return(uint64_t)(sizeof(struct monst));
case 46:return(uint64_t)(sizeof(struct nh_file));
case 47:return(uint64_t)(sizeof(struct nhcoord));
case 48:return(uint64_t)(sizeof(struct nhl_sandbox_info));
case 49:return(uint64_t)(sizeof(struct obj));
case 50:return(uint64_t)(sizeof(struct permonst));
case 51:return(uint64_t)(sizeof(struct prop));
case 52:return(uint64_t)(sizeof(struct proto_dungeon));
case 53:return(uint64_t)(sizeof(struct q_score));
case 54:return(uint64_t)(sizeof(struct rm));
case 55:return(uint64_t)(sizeof(struct s_level));
case 56:return(uint64_t)(sizeof(struct shclass));
case 57:return(uint64_t)(sizeof(struct stairway));
case 58:return(uint64_t)(sizeof(struct tmpbranch));
case 59:return(uint64_t)(sizeof(struct tmpdungeon));
case 60:return(uint64_t)(sizeof(struct tmplevel));
case 61:return(uint64_t)(sizeof(struct trap));
case 62:return(uint64_t)(sizeof(struct u_event));
case 63:return(uint64_t)(sizeof(struct u_have));
case 64:return(uint64_t)(sizeof(struct window_procs));
case 65:return(uint64_t)(sizeof(struct you));
case 66:return(uint64_t)(sizeof(union any));
case 67:return(uint64_t)(AGGRAVATE_MONSTER);
case 68:return(uint64_t)(AIR);
case 69:return(uint64_t)(ALTAR);
case 70:return(uint64_t)(ASCENDED);
case 71:return(uint64_t)(BLINDED);
case 72:return(uint64_t)(CLOUD);
case 73:return(uint64_t)(CORR);
case 74:return(uint64_t)(DBWALL);
case 75:return(uint64_t)(DELPHI);
case 76:return(uint64_t)(DOOR);
case 77:return(uint64_t)(DRAWBRIDGE_DOWN);
case 78:return(uint64_t)(DRAWBRIDGE_UP);
case 79:return(uint64_t)(ESCAPED);
case 80:return(uint64_t)(FLYING);
case 81:return(uint64_t)(FOOT);
case 82:return(uint64_t)(FOUNTAIN);
case 83:return(uint64_t)(GRAVE);
case 84:return(uint64_t)(HALLUC);
case 85:return(uint64_t)(HALLUC_RES);
case 86:return(uint64_t)(LEVITATION);
case 87:return(uint64_t)(LR_DOWNTELE);
case 88:return(uint64_t)(LR_UPTELE);
case 89:return(uint64_t)(MAGIC_PORTAL);
case 90:return(uint64_t)(MAX_TYPE);
case 91:return(uint64_t)(M_AP_FURNITURE);
case 92:return(uint64_t)(PM_DWARF);
case 93:return(uint64_t)(ROOM);
case 94:return(uint64_t)(SDOOR);
case 95:return(uint64_t)(SHOPBASE);
case 96:return(uint64_t)(SINK);
case 97:return(uint64_t)(TEMPLE);
case 98:return(uint64_t)(THRONE);
case 99:return(uint64_t)(TREE);
case 100:return(uint64_t)(VAULT);
case 101:return(uint64_t)(VIBRATING_SQUARE);
default:abort();}}
uint64_t teleport_dungeon_read(int kind,void*at,int field){switch(kind){
case 0:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 2:{struct align*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->a_int);
default:abort();}}
case 4:{struct branch*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->next);
case 1:return(uint64_t)(uintptr_t)(p->id);
case 2:return(uint64_t)(uintptr_t)(p->type);
case 3:return(uint64_t)(uintptr_t)(&p->end1);
case 4:return(uint64_t)(uintptr_t)(&p->end2);
case 5:return(uint64_t)(uintptr_t)(p->end1_up);
default:abort();}}
case 5:{struct cemetery*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->next);
case 1:return(uint64_t)(uintptr_t)(&p->who);
case 2:return(uint64_t)(uintptr_t)(&p->how);
case 3:return(uint64_t)(uintptr_t)(p->frpx);
case 4:return(uint64_t)(uintptr_t)(p->frpy);
case 5:return(uint64_t)(uintptr_t)(p->bonesknown);
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->zeroany);
default:abort();}}
case 7:{struct couple*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->base);
case 1:return(uint64_t)(uintptr_t)(p->rand);
default:abort();}}
case 8:{struct d_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->town);
case 1:return(uint64_t)(uintptr_t)(p->hellish);
case 2:return(uint64_t)(uintptr_t)(p->maze_like);
case 3:return(uint64_t)(uintptr_t)(p->rogue_like);
case 4:return(uint64_t)(uintptr_t)(p->align);
case 5:return(uint64_t)(uintptr_t)(p->unconnected);
default:abort();}}
case 9:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 10:{struct dest_area*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lx);
case 1:return(uint64_t)(uintptr_t)(p->ly);
case 2:return(uint64_t)(uintptr_t)(p->hx);
case 3:return(uint64_t)(uintptr_t)(p->hy);
case 4:return(uint64_t)(uintptr_t)(p->nlx);
case 5:return(uint64_t)(uintptr_t)(p->nly);
case 6:return(uint64_t)(uintptr_t)(p->nhx);
case 7:return(uint64_t)(uintptr_t)(p->nhy);
default:abort();}}
case 11:{struct dgn_topology*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_oracle_level);
case 1:return(uint64_t)(uintptr_t)(&p->d_bigroom_level);
case 2:return(uint64_t)(uintptr_t)(&p->d_rogue_level);
case 3:return(uint64_t)(uintptr_t)(&p->d_medusa_level);
case 4:return(uint64_t)(uintptr_t)(&p->d_stronghold_level);
case 5:return(uint64_t)(uintptr_t)(&p->d_valley_level);
case 6:return(uint64_t)(uintptr_t)(&p->d_wiz1_level);
case 7:return(uint64_t)(uintptr_t)(&p->d_wiz2_level);
case 8:return(uint64_t)(uintptr_t)(&p->d_wiz3_level);
case 9:return(uint64_t)(uintptr_t)(&p->d_juiblex_level);
case 10:return(uint64_t)(uintptr_t)(&p->d_orcus_level);
case 11:return(uint64_t)(uintptr_t)(&p->d_baalzebub_level);
case 12:return(uint64_t)(uintptr_t)(&p->d_asmodeus_level);
case 13:return(uint64_t)(uintptr_t)(&p->d_portal_level);
case 14:return(uint64_t)(uintptr_t)(&p->d_sanctum_level);
case 15:return(uint64_t)(uintptr_t)(&p->d_earth_level);
case 16:return(uint64_t)(uintptr_t)(&p->d_water_level);
case 17:return(uint64_t)(uintptr_t)(&p->d_fire_level);
case 18:return(uint64_t)(uintptr_t)(&p->d_air_level);
case 19:return(uint64_t)(uintptr_t)(&p->d_astral_level);
case 20:return(uint64_t)(uintptr_t)(p->d_tower_dnum);
case 21:return(uint64_t)(uintptr_t)(p->d_sokoban_dnum);
case 22:return(uint64_t)(uintptr_t)(p->d_mines_dnum);
case 23:return(uint64_t)(uintptr_t)(p->d_quest_dnum);
case 24:return(uint64_t)(uintptr_t)(p->d_tutorial_dnum);
case 25:return(uint64_t)(uintptr_t)(&p->d_qstart_level);
case 26:return(uint64_t)(uintptr_t)(&p->d_qlocate_level);
case 27:return(uint64_t)(uintptr_t)(&p->d_nemesis_level);
case 28:return(uint64_t)(uintptr_t)(&p->d_knox_level);
case 29:return(uint64_t)(uintptr_t)(&p->d_mineend_level);
case 30:return(uint64_t)(uintptr_t)(&p->d_sokoend_level);
default:abort();}}
case 12:{dlevel_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->locations);
case 1:return(uint64_t)(uintptr_t)(&p->monsters);
case 2:return(uint64_t)(uintptr_t)(p->buriedobjlist);
case 3:return(uint64_t)(uintptr_t)(p->bonesinfo);
case 4:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 13:{struct dungeon*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dname);
case 1:return(uint64_t)(uintptr_t)(&p->proto);
case 2:return(uint64_t)(uintptr_t)(&p->fill_lvl);
case 3:return(uint64_t)(uintptr_t)(&p->themerms);
case 4:return(uint64_t)(uintptr_t)(p->boneid);
case 5:return(uint64_t)(uintptr_t)(&p->flags);
case 6:return(uint64_t)(uintptr_t)(p->entry_lev);
case 7:return(uint64_t)(uintptr_t)(p->num_dunlevs);
case 8:return(uint64_t)(uintptr_t)(p->dunlev_ureached);
case 9:return(uint64_t)(uintptr_t)(p->ledger_start);
case 10:return(uint64_t)(uintptr_t)(p->depth_start);
default:abort();}}
case 14:{struct exclusion_zone*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->zonetype);
case 1:return(uint64_t)(uintptr_t)(p->lx);
case 2:return(uint64_t)(uintptr_t)(p->ly);
case 3:return(uint64_t)(uintptr_t)(p->hx);
case 4:return(uint64_t)(uintptr_t)(p->hy);
case 5:return(uint64_t)(uintptr_t)(p->next);
default:abort();}}
case 15:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
default:abort();}}
case 16:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
case 1:return(uint64_t)(uintptr_t)(p->window_inited);
case 2:return(uint64_t)(uintptr_t)(p->terrain_typ);
case 3:return(uint64_t)(uintptr_t)(p->menu_requested);
default:abort();}}
case 17:{struct instance_globals_f*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ftrap);
default:abort();}}
case 18:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->branches);
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeons);
case 1:return(uint64_t)(uintptr_t)(&p->dungeon_topology);
case 2:return(uint64_t)(uintptr_t)(&p->dndest);
default:abort();}}
case 20:{struct instance_globals_saved_e*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->exclusion_zones);
default:abort();}}
case 21:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->inv_pos);
default:abort();}}
case 22:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->lastseentyp);
case 1:return(uint64_t)(uintptr_t)(&p->level);
case 2:return(uint64_t)(uintptr_t)(&p->level_info);
default:abort();}}
case 23:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mapseenchn);
default:abort();}}
case 24:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->n_dgns);
default:abort();}}
case 25:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->quest_status);
default:abort();}}
case 26:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->rooms);
default:abort();}}
case 27:{struct instance_globals_saved_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sp_levchn);
default:abort();}}
case 28:{struct instance_globals_saved_t*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->tune);
default:abort();}}
case 29:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->updest);
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
case 1:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 31:{struct lchoice*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->idx);
case 1:return(uint64_t)(uintptr_t)(&p->lev);
case 2:return(uint64_t)(uintptr_t)(&p->playerlev);
case 3:return(uint64_t)(uintptr_t)(&p->dgn);
case 4:return(uint64_t)(uintptr_t)(p->menuletter);
default:abort();}}
case 32:{struct level_map*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->lev_name);
case 1:return(uint64_t)(uintptr_t)(p->lev_spec);
default:abort();}}
case 33:{struct levelflags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hardfloor);
case 1:return(uint64_t)(uintptr_t)(p->sokoban_rules);
default:abort();}}
case 34:{struct linfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 35:{struct mapseen*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->next);
case 1:return(uint64_t)(uintptr_t)(p->br);
case 2:return(uint64_t)(uintptr_t)(&p->lev);
case 3:return(uint64_t)(uintptr_t)(&p->feat);
case 4:return(uint64_t)(uintptr_t)(&p->flags);
case 5:return(uint64_t)(uintptr_t)(p->custom);
case 6:return(uint64_t)(uintptr_t)(p->custom_lth);
case 7:return(uint64_t)(uintptr_t)(&p->msrooms);
case 8:return(uint64_t)(uintptr_t)(p->final_resting_place);
default:abort();}}
case 36:{struct mapseen_feat*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nfount);
case 1:return(uint64_t)(uintptr_t)(p->nsink);
case 2:return(uint64_t)(uintptr_t)(p->naltar);
case 3:return(uint64_t)(uintptr_t)(p->nthrone);
case 4:return(uint64_t)(uintptr_t)(p->ngrave);
case 5:return(uint64_t)(uintptr_t)(p->ntree);
case 6:return(uint64_t)(uintptr_t)(p->nshop);
case 7:return(uint64_t)(uintptr_t)(p->ntemple);
case 8:return(uint64_t)(uintptr_t)(p->msalign);
case 9:return(uint64_t)(uintptr_t)(p->shoptype);
default:abort();}}
case 37:{struct mapseen_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->notreachable);
case 1:return(uint64_t)(uintptr_t)(p->forgot);
case 2:return(uint64_t)(uintptr_t)(p->knownbones);
case 3:return(uint64_t)(uintptr_t)(p->oracle);
case 4:return(uint64_t)(uintptr_t)(p->sokosolved);
case 5:return(uint64_t)(uintptr_t)(p->bigroom);
case 6:return(uint64_t)(uintptr_t)(p->castle);
case 7:return(uint64_t)(uintptr_t)(p->castletune);
case 8:return(uint64_t)(uintptr_t)(p->valley);
case 9:return(uint64_t)(uintptr_t)(p->msanctum);
case 10:return(uint64_t)(uintptr_t)(p->ludios);
case 11:return(uint64_t)(uintptr_t)(p->roguelevel);
case 12:return(uint64_t)(uintptr_t)(p->quest_summons);
case 13:return(uint64_t)(uintptr_t)(p->questing);
case 14:return(uint64_t)(uintptr_t)(p->vibrating_square);
default:abort();}}
case 38:{struct mapseen_rooms*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->seen);
case 1:return(uint64_t)(uintptr_t)(p->untended);
default:abort();}}
case 39:{struct mi*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->item);
default:abort();}}
case 40:{struct mkroom*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->rtype);
case 1:return(uint64_t)(uintptr_t)(p->orig_rtype);
default:abort();}}
case 41:{struct monst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->data);
case 1:return(uint64_t)(uintptr_t)(p->mx);
case 2:return(uint64_t)(uintptr_t)(p->my);
case 3:return(uint64_t)(uintptr_t)(p->mappearance);
case 4:return(uint64_t)(uintptr_t)(p->m_ap_type);
default:abort();}}
case 42:{struct nh_file*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mode);
default:abort();}}
case 43:{struct nhcoord*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->x);
case 1:return(uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 44:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->flags);
case 1:return(uint64_t)(uintptr_t)(p->memlimit);
case 2:return(uint64_t)(uintptr_t)(p->steps);
case 3:return(uint64_t)(uintptr_t)(p->perpcall);
default:abort();}}
case 45:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nobj);
case 1:return(uint64_t)(uintptr_t)(p->ox);
case 2:return(uint64_t)(uintptr_t)(p->oy);
default:abort();}}
case 46:{struct permonst*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->mflags1);
default:abort();}}
case 47:{struct prop*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->extrinsic);
case 1:return(uint64_t)(uintptr_t)(p->blocked);
case 2:return(uint64_t)(uintptr_t)(p->intrinsic);
default:abort();}}
case 48:{struct proto_dungeon*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->tmpdungeon);
case 1:return(uint64_t)(uintptr_t)(&p->tmplevel);
case 2:return(uint64_t)(uintptr_t)(&p->final_lev);
case 3:return(uint64_t)(uintptr_t)(&p->tmpbranch);
case 4:return(uint64_t)(uintptr_t)(p->start);
case 5:return(uint64_t)(uintptr_t)(p->n_levs);
case 6:return(uint64_t)(uintptr_t)(p->n_brs);
default:abort();}}
case 49:{struct q_score*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->got_quest);
case 1:return(uint64_t)(uintptr_t)(p->leader_is_dead);
default:abort();}}
case 50:{struct rm*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->typ);
case 1:return(uint64_t)(uintptr_t)(p->seenv);
case 2:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 51:{struct s_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->next);
case 1:return(uint64_t)(uintptr_t)(&p->dlevel);
case 2:return(uint64_t)(uintptr_t)(&p->proto);
case 3:return(uint64_t)(uintptr_t)(p->boneid);
case 4:return(uint64_t)(uintptr_t)(p->rndlevs);
case 5:return(uint64_t)(uintptr_t)(&p->flags);
default:abort();}}
case 52:{struct shclass*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->annotation);
default:abort();}}
case 53:{struct stairway*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->tolev);
case 1:return(uint64_t)(uintptr_t)(p->up);
case 2:return(uint64_t)(uintptr_t)(p->u_traversed);
default:abort();}}
case 54:{struct tmpbranch*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(&p->lev);
case 2:return(uint64_t)(uintptr_t)(p->chain);
case 3:return(uint64_t)(uintptr_t)(p->type);
case 4:return(uint64_t)(uintptr_t)(p->up);
default:abort();}}
case 55:{struct tmpdungeon*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->protoname);
case 2:return(uint64_t)(uintptr_t)(&p->lev);
case 3:return(uint64_t)(uintptr_t)(p->flags);
case 4:return(uint64_t)(uintptr_t)(p->chance);
case 5:return(uint64_t)(uintptr_t)(p->levels);
case 6:return(uint64_t)(uintptr_t)(p->branches);
case 7:return(uint64_t)(uintptr_t)(p->entry_lev);
case 8:return(uint64_t)(uintptr_t)(p->boneschar);
case 9:return(uint64_t)(uintptr_t)(p->align);
default:abort();}}
case 56:{struct tmplevel*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->chainlvl);
case 2:return(uint64_t)(uintptr_t)(&p->lev);
case 3:return(uint64_t)(uintptr_t)(p->chance);
case 4:return(uint64_t)(uintptr_t)(p->rndlevs);
case 5:return(uint64_t)(uintptr_t)(p->chain);
case 6:return(uint64_t)(uintptr_t)(p->flags);
case 7:return(uint64_t)(uintptr_t)(p->boneschar);
default:abort();}}
case 57:{struct trap*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ntrap);
case 1:return(uint64_t)(uintptr_t)(p->tx);
case 2:return(uint64_t)(uintptr_t)(p->ty);
case 3:return(uint64_t)(uintptr_t)(p->ttyp);
case 4:return(uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 58:{struct u_event*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->qcalled);
case 1:return(uint64_t)(uintptr_t)(p->qexpelled);
case 2:return(uint64_t)(uintptr_t)(p->qcompleted);
case 3:return(uint64_t)(uintptr_t)(p->uheard_tune);
default:abort();}}
case 59:{struct u_have*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->amulet);
default:abort();}}
case 60:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 1:return(uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 2:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 3:return(uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 4:return(uint64_t)(uintptr_t)(p->win_putstr);
case 5:return(uint64_t)(uintptr_t)(p->win_start_menu);
case 6:return(uint64_t)(uintptr_t)(p->win_end_menu);
case 7:return(uint64_t)(uintptr_t)(p->win_cliparound);
default:abort();}}
case 61:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ux);
case 1:return(uint64_t)(uintptr_t)(p->uy);
case 2:return(uint64_t)(uintptr_t)(p->ux0);
case 3:return(uint64_t)(uintptr_t)(p->uy0);
case 4:return(uint64_t)(uintptr_t)(&p->uz);
case 5:return(uint64_t)(uintptr_t)(&p->uz0);
case 6:return(uint64_t)(uintptr_t)(p->ulevel);
case 7:return(uint64_t)(uintptr_t)(&p->urooms);
case 8:return(uint64_t)(uintptr_t)(&p->uprops);
case 9:return(uint64_t)(uintptr_t)(p->umonster);
case 10:return(uint64_t)(uintptr_t)(p->umonnum);
case 11:return(uint64_t)(uintptr_t)(p->uswallow);
case 12:return(uint64_t)(uintptr_t)(p->uinwater);
case 13:return(uint64_t)(uintptr_t)(p->uundetected);
case 14:return(uint64_t)(uintptr_t)(&p->uevent);
case 15:return(uint64_t)(uintptr_t)(&p->uhave);
case 16:return(uint64_t)(uintptr_t)(&p->ualign);
case 17:return(uint64_t)(uintptr_t)(p->ustuck);
case 18:return(uint64_t)(uintptr_t)(p->usteed);
default:abort();}}
default:abort();}}
void teleport_dungeon_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Race*p=at;switch(field){
case 0:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:p->filecode=(__typeof__(p->filecode))value;return;
default:abort();}}
case 2:{struct align*p=at;switch(field){
case 0:p->type=(__typeof__(p->type))value;return;
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:p->a_int=(__typeof__(p->a_int))value;return;
default:abort();}}
case 4:{struct branch*p=at;switch(field){
case 0:p->next=(__typeof__(p->next))value;return;
case 1:p->id=(__typeof__(p->id))value;return;
case 2:p->type=(__typeof__(p->type))value;return;
case 5:p->end1_up=(__typeof__(p->end1_up))value;return;
default:abort();}}
case 5:{struct cemetery*p=at;switch(field){
case 0:p->next=(__typeof__(p->next))value;return;
case 3:p->frpx=(__typeof__(p->frpx))value;return;
case 4:p->frpy=(__typeof__(p->frpy))value;return;
case 5:p->bonesknown=(__typeof__(p->bonesknown))value;return;
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
default:abort();}}
case 7:{struct couple*p=at;switch(field){
case 0:p->base=(__typeof__(p->base))value;return;
case 1:p->rand=(__typeof__(p->rand))value;return;
default:abort();}}
case 8:{struct d_flags*p=at;switch(field){
case 0:p->town=(unsigned int)value;return;
case 1:p->hellish=(unsigned int)value;return;
case 2:p->maze_like=(unsigned int)value;return;
case 3:p->rogue_like=(unsigned int)value;return;
case 4:p->align=(unsigned int)value;return;
case 5:p->unconnected=(unsigned int)value;return;
default:abort();}}
case 9:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 10:{struct dest_area*p=at;switch(field){
case 0:p->lx=(__typeof__(p->lx))value;return;
case 1:p->ly=(__typeof__(p->ly))value;return;
case 2:p->hx=(__typeof__(p->hx))value;return;
case 3:p->hy=(__typeof__(p->hy))value;return;
case 4:p->nlx=(__typeof__(p->nlx))value;return;
case 5:p->nly=(__typeof__(p->nly))value;return;
case 6:p->nhx=(__typeof__(p->nhx))value;return;
case 7:p->nhy=(__typeof__(p->nhy))value;return;
default:abort();}}
case 11:{struct dgn_topology*p=at;switch(field){
case 20:p->d_tower_dnum=(__typeof__(p->d_tower_dnum))value;return;
case 21:p->d_sokoban_dnum=(__typeof__(p->d_sokoban_dnum))value;return;
case 22:p->d_mines_dnum=(__typeof__(p->d_mines_dnum))value;return;
case 23:p->d_quest_dnum=(__typeof__(p->d_quest_dnum))value;return;
case 24:p->d_tutorial_dnum=(__typeof__(p->d_tutorial_dnum))value;return;
default:abort();}}
case 12:{dlevel_t*p=at;switch(field){
case 2:p->buriedobjlist=(__typeof__(p->buriedobjlist))value;return;
case 3:p->bonesinfo=(__typeof__(p->bonesinfo))value;return;
default:abort();}}
case 13:{struct dungeon*p=at;switch(field){
case 4:p->boneid=(__typeof__(p->boneid))value;return;
case 6:p->entry_lev=(__typeof__(p->entry_lev))value;return;
case 7:p->num_dunlevs=(__typeof__(p->num_dunlevs))value;return;
case 8:p->dunlev_ureached=(__typeof__(p->dunlev_ureached))value;return;
case 9:p->ledger_start=(__typeof__(p->ledger_start))value;return;
case 10:p->depth_start=(__typeof__(p->depth_start))value;return;
default:abort();}}
case 14:{struct exclusion_zone*p=at;switch(field){
case 0:p->zonetype=(__typeof__(p->zonetype))value;return;
case 1:p->lx=(__typeof__(p->lx))value;return;
case 2:p->ly=(__typeof__(p->ly))value;return;
case 3:p->hx=(__typeof__(p->hx))value;return;
case 4:p->hy=(__typeof__(p->hy))value;return;
case 5:p->next=(__typeof__(p->next))value;return;
default:abort();}}
case 15:{struct flag*p=at;switch(field){
case 0:p->debug=(__typeof__(p->debug))value;return;
default:abort();}}
case 16:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(__typeof__(p->last_msg))value;return;
case 1:p->window_inited=(__typeof__(p->window_inited))value;return;
case 2:p->terrain_typ=(__typeof__(p->terrain_typ))value;return;
case 3:p->menu_requested=(__typeof__(p->menu_requested))value;return;
default:abort();}}
case 17:{struct instance_globals_f*p=at;switch(field){
case 0:p->ftrap=(__typeof__(p->ftrap))value;return;
default:abort();}}
case 18:{struct instance_globals_saved_b*p=at;switch(field){
case 0:p->branches=(__typeof__(p->branches))value;return;
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 20:{struct instance_globals_saved_e*p=at;switch(field){
case 0:p->exclusion_zones=(__typeof__(p->exclusion_zones))value;return;
default:abort();}}
case 21:{struct instance_globals_saved_i*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 23:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->mapseenchn=(__typeof__(p->mapseenchn))value;return;
default:abort();}}
case 24:{struct instance_globals_saved_n*p=at;switch(field){
case 0:p->n_dgns=(__typeof__(p->n_dgns))value;return;
default:abort();}}
case 25:{struct instance_globals_saved_q*p=at;switch(field){
default:abort();}}
case 26:{struct instance_globals_saved_r*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_saved_s*p=at;switch(field){
case 0:p->sp_levchn=(__typeof__(p->sp_levchn))value;return;
default:abort();}}
case 28:{struct instance_globals_saved_t*p=at;switch(field){
default:abort();}}
case 29:{struct instance_globals_saved_u*p=at;switch(field){
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 31:{struct lchoice*p=at;switch(field){
case 0:p->idx=(__typeof__(p->idx))value;return;
case 4:p->menuletter=(__typeof__(p->menuletter))value;return;
default:abort();}}
case 32:{struct level_map*p=at;switch(field){
case 0:p->lev_name=(__typeof__(p->lev_name))value;return;
case 1:p->lev_spec=(__typeof__(p->lev_spec))value;return;
default:abort();}}
case 33:{struct levelflags*p=at;switch(field){
case 0:p->hardfloor=(unsigned int)value;return;
case 1:p->sokoban_rules=(unsigned int)value;return;
default:abort();}}
case 34:{struct linfo*p=at;switch(field){
case 0:p->flags=(__typeof__(p->flags))value;return;
default:abort();}}
case 35:{struct mapseen*p=at;switch(field){
case 0:p->next=(__typeof__(p->next))value;return;
case 1:p->br=(__typeof__(p->br))value;return;
case 5:p->custom=(__typeof__(p->custom))value;return;
case 6:p->custom_lth=(__typeof__(p->custom_lth))value;return;
case 8:p->final_resting_place=(__typeof__(p->final_resting_place))value;return;
default:abort();}}
case 36:{struct mapseen_feat*p=at;switch(field){
case 0:p->nfount=(unsigned int)value;return;
case 1:p->nsink=(unsigned int)value;return;
case 2:p->naltar=(unsigned int)value;return;
case 3:p->nthrone=(unsigned int)value;return;
case 4:p->ngrave=(unsigned int)value;return;
case 5:p->ntree=(unsigned int)value;return;
case 6:p->nshop=(unsigned int)value;return;
case 7:p->ntemple=(unsigned int)value;return;
case 8:p->msalign=(unsigned int)value;return;
case 9:p->shoptype=(unsigned int)value;return;
default:abort();}}
case 37:{struct mapseen_flags*p=at;switch(field){
case 0:p->notreachable=(unsigned int)value;return;
case 1:p->forgot=(unsigned int)value;return;
case 2:p->knownbones=(unsigned int)value;return;
case 3:p->oracle=(unsigned int)value;return;
case 4:p->sokosolved=(unsigned int)value;return;
case 5:p->bigroom=(unsigned int)value;return;
case 6:p->castle=(unsigned int)value;return;
case 7:p->castletune=(unsigned int)value;return;
case 8:p->valley=(unsigned int)value;return;
case 9:p->msanctum=(unsigned int)value;return;
case 10:p->ludios=(unsigned int)value;return;
case 11:p->roguelevel=(unsigned int)value;return;
case 12:p->quest_summons=(unsigned int)value;return;
case 13:p->questing=(unsigned int)value;return;
case 14:p->vibrating_square=(unsigned int)value;return;
default:abort();}}
case 38:{struct mapseen_rooms*p=at;switch(field){
case 0:p->seen=(unsigned int)value;return;
case 1:p->untended=(unsigned int)value;return;
default:abort();}}
case 39:{struct mi*p=at;switch(field){
default:abort();}}
case 40:{struct mkroom*p=at;switch(field){
case 0:p->rtype=(__typeof__(p->rtype))value;return;
case 1:p->orig_rtype=(__typeof__(p->orig_rtype))value;return;
default:abort();}}
case 41:{struct monst*p=at;switch(field){
case 0:p->data=(__typeof__(p->data))value;return;
case 1:p->mx=(__typeof__(p->mx))value;return;
case 2:p->my=(__typeof__(p->my))value;return;
case 3:p->mappearance=(__typeof__(p->mappearance))value;return;
case 4:p->m_ap_type=(__typeof__(p->m_ap_type))value;return;
default:abort();}}
case 42:{struct nh_file*p=at;switch(field){
case 0:p->mode=(__typeof__(p->mode))value;return;
default:abort();}}
case 43:{struct nhcoord*p=at;switch(field){
case 0:p->x=(__typeof__(p->x))value;return;
case 1:p->y=(__typeof__(p->y))value;return;
default:abort();}}
case 44:{struct nhl_sandbox_info*p=at;switch(field){
case 0:p->flags=(__typeof__(p->flags))value;return;
case 1:p->memlimit=(__typeof__(p->memlimit))value;return;
case 2:p->steps=(__typeof__(p->steps))value;return;
case 3:p->perpcall=(__typeof__(p->perpcall))value;return;
default:abort();}}
case 45:{struct obj*p=at;switch(field){
case 0:p->nobj=(__typeof__(p->nobj))value;return;
case 1:p->ox=(__typeof__(p->ox))value;return;
case 2:p->oy=(__typeof__(p->oy))value;return;
default:abort();}}
case 46:{struct permonst*p=at;switch(field){
case 0:p->mflags1=(__typeof__(p->mflags1))value;return;
default:abort();}}
case 47:{struct prop*p=at;switch(field){
case 0:p->extrinsic=(__typeof__(p->extrinsic))value;return;
case 1:p->blocked=(__typeof__(p->blocked))value;return;
case 2:p->intrinsic=(__typeof__(p->intrinsic))value;return;
default:abort();}}
case 48:{struct proto_dungeon*p=at;switch(field){
case 4:p->start=(__typeof__(p->start))value;return;
case 5:p->n_levs=(__typeof__(p->n_levs))value;return;
case 6:p->n_brs=(__typeof__(p->n_brs))value;return;
default:abort();}}
case 49:{struct q_score*p=at;switch(field){
case 0:p->got_quest=(unsigned int)value;return;
case 1:p->leader_is_dead=(unsigned int)value;return;
default:abort();}}
case 50:{struct rm*p=at;switch(field){
case 0:p->typ=(__typeof__(p->typ))value;return;
case 1:p->seenv=(__typeof__(p->seenv))value;return;
case 2:p->flags=(unsigned int)value;return;
default:abort();}}
case 51:{struct s_level*p=at;switch(field){
case 0:p->next=(__typeof__(p->next))value;return;
case 3:p->boneid=(__typeof__(p->boneid))value;return;
case 4:p->rndlevs=(__typeof__(p->rndlevs))value;return;
default:abort();}}
case 52:{struct shclass*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->annotation=(__typeof__(p->annotation))value;return;
default:abort();}}
case 53:{struct stairway*p=at;switch(field){
case 1:p->up=(__typeof__(p->up))value;return;
case 2:p->u_traversed=(__typeof__(p->u_traversed))value;return;
default:abort();}}
case 54:{struct tmpbranch*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 2:p->chain=(__typeof__(p->chain))value;return;
case 3:p->type=(__typeof__(p->type))value;return;
case 4:p->up=(__typeof__(p->up))value;return;
default:abort();}}
case 55:{struct tmpdungeon*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->protoname=(__typeof__(p->protoname))value;return;
case 3:p->flags=(__typeof__(p->flags))value;return;
case 4:p->chance=(__typeof__(p->chance))value;return;
case 5:p->levels=(__typeof__(p->levels))value;return;
case 6:p->branches=(__typeof__(p->branches))value;return;
case 7:p->entry_lev=(__typeof__(p->entry_lev))value;return;
case 8:p->boneschar=(__typeof__(p->boneschar))value;return;
case 9:p->align=(__typeof__(p->align))value;return;
default:abort();}}
case 56:{struct tmplevel*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->chainlvl=(__typeof__(p->chainlvl))value;return;
case 3:p->chance=(__typeof__(p->chance))value;return;
case 4:p->rndlevs=(__typeof__(p->rndlevs))value;return;
case 5:p->chain=(__typeof__(p->chain))value;return;
case 6:p->flags=(__typeof__(p->flags))value;return;
case 7:p->boneschar=(__typeof__(p->boneschar))value;return;
default:abort();}}
case 57:{struct trap*p=at;switch(field){
case 0:p->ntrap=(__typeof__(p->ntrap))value;return;
case 1:p->tx=(__typeof__(p->tx))value;return;
case 2:p->ty=(__typeof__(p->ty))value;return;
case 3:p->ttyp=(unsigned int)value;return;
case 4:p->tseen=(unsigned int)value;return;
default:abort();}}
case 58:{struct u_event*p=at;switch(field){
case 0:p->qcalled=(unsigned int)value;return;
case 1:p->qexpelled=(unsigned int)value;return;
case 2:p->qcompleted=(unsigned int)value;return;
case 3:p->uheard_tune=(unsigned int)value;return;
default:abort();}}
case 59:{struct u_have*p=at;switch(field){
case 0:p->amulet=(unsigned int)value;return;
default:abort();}}
case 60:{struct window_procs*p=at;switch(field){
case 0:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))value;return;
case 1:p->win_clear_nhwindow=(__typeof__(p->win_clear_nhwindow))value;return;
case 2:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 3:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))value;return;
case 4:p->win_putstr=(__typeof__(p->win_putstr))value;return;
case 5:p->win_start_menu=(__typeof__(p->win_start_menu))value;return;
case 6:p->win_end_menu=(__typeof__(p->win_end_menu))value;return;
case 7:p->win_cliparound=(__typeof__(p->win_cliparound))value;return;
default:abort();}}
case 61:{struct you*p=at;switch(field){
case 0:p->ux=(__typeof__(p->ux))value;return;
case 1:p->uy=(__typeof__(p->uy))value;return;
case 2:p->ux0=(__typeof__(p->ux0))value;return;
case 3:p->uy0=(__typeof__(p->uy0))value;return;
case 6:p->ulevel=(__typeof__(p->ulevel))value;return;
case 9:p->umonster=(__typeof__(p->umonster))value;return;
case 10:p->umonnum=(__typeof__(p->umonnum))value;return;
case 11:p->uswallow=(unsigned int)value;return;
case 12:p->uinwater=(unsigned int)value;return;
case 13:p->uundetected=(unsigned int)value;return;
case 17:p->ustuck=(__typeof__(p->ustuck))value;return;
case 18:p->usteed=(__typeof__(p->usteed))value;return;
default:abort();}}
default:abort();}}
void* teleport_dungeon_address(int kind,void*at,int field){switch(kind){
case 0:{struct Race*p=at;switch(field){
case 0:return(void*)&p->mnum;
default:abort();}}
case 1:{struct Role*p=at;switch(field){
case 0:return(void*)&p->filecode;
default:abort();}}
case 2:{struct align*p=at;switch(field){
case 0:return(void*)&p->type;
default:abort();}}
case 3:{union any*p=at;switch(field){
case 0:return(void*)&p->a_int;
default:abort();}}
case 4:{struct branch*p=at;switch(field){
case 0:return(void*)&p->next;
case 1:return(void*)&p->id;
case 2:return(void*)&p->type;
case 3:return(void*)&p->end1;
case 4:return(void*)&p->end2;
case 5:return(void*)&p->end1_up;
default:abort();}}
case 5:{struct cemetery*p=at;switch(field){
case 0:return(void*)&p->next;
case 1:return(void*)&p->who;
case 2:return(void*)&p->how;
case 3:return(void*)&p->frpx;
case 4:return(void*)&p->frpy;
case 5:return(void*)&p->bonesknown;
default:abort();}}
case 6:{struct const_globals*p=at;switch(field){
case 0:return(void*)&p->zeroany;
default:abort();}}
case 7:{struct couple*p=at;switch(field){
case 0:return(void*)&p->base;
case 1:return(void*)&p->rand;
default:abort();}}
case 8:{struct d_flags*p=at;switch(field){
default:abort();}}
case 9:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 10:{struct dest_area*p=at;switch(field){
case 0:return(void*)&p->lx;
case 1:return(void*)&p->ly;
case 2:return(void*)&p->hx;
case 3:return(void*)&p->hy;
case 4:return(void*)&p->nlx;
case 5:return(void*)&p->nly;
case 6:return(void*)&p->nhx;
case 7:return(void*)&p->nhy;
default:abort();}}
case 11:{struct dgn_topology*p=at;switch(field){
case 0:return(void*)&p->d_oracle_level;
case 1:return(void*)&p->d_bigroom_level;
case 2:return(void*)&p->d_rogue_level;
case 3:return(void*)&p->d_medusa_level;
case 4:return(void*)&p->d_stronghold_level;
case 5:return(void*)&p->d_valley_level;
case 6:return(void*)&p->d_wiz1_level;
case 7:return(void*)&p->d_wiz2_level;
case 8:return(void*)&p->d_wiz3_level;
case 9:return(void*)&p->d_juiblex_level;
case 10:return(void*)&p->d_orcus_level;
case 11:return(void*)&p->d_baalzebub_level;
case 12:return(void*)&p->d_asmodeus_level;
case 13:return(void*)&p->d_portal_level;
case 14:return(void*)&p->d_sanctum_level;
case 15:return(void*)&p->d_earth_level;
case 16:return(void*)&p->d_water_level;
case 17:return(void*)&p->d_fire_level;
case 18:return(void*)&p->d_air_level;
case 19:return(void*)&p->d_astral_level;
case 20:return(void*)&p->d_tower_dnum;
case 21:return(void*)&p->d_sokoban_dnum;
case 22:return(void*)&p->d_mines_dnum;
case 23:return(void*)&p->d_quest_dnum;
case 24:return(void*)&p->d_tutorial_dnum;
case 25:return(void*)&p->d_qstart_level;
case 26:return(void*)&p->d_qlocate_level;
case 27:return(void*)&p->d_nemesis_level;
case 28:return(void*)&p->d_knox_level;
case 29:return(void*)&p->d_mineend_level;
case 30:return(void*)&p->d_sokoend_level;
default:abort();}}
case 12:{dlevel_t*p=at;switch(field){
case 0:return(void*)&p->locations;
case 1:return(void*)&p->monsters;
case 2:return(void*)&p->buriedobjlist;
case 3:return(void*)&p->bonesinfo;
case 4:return(void*)&p->flags;
default:abort();}}
case 13:{struct dungeon*p=at;switch(field){
case 0:return(void*)&p->dname;
case 1:return(void*)&p->proto;
case 2:return(void*)&p->fill_lvl;
case 3:return(void*)&p->themerms;
case 4:return(void*)&p->boneid;
case 5:return(void*)&p->flags;
case 6:return(void*)&p->entry_lev;
case 7:return(void*)&p->num_dunlevs;
case 8:return(void*)&p->dunlev_ureached;
case 9:return(void*)&p->ledger_start;
case 10:return(void*)&p->depth_start;
default:abort();}}
case 14:{struct exclusion_zone*p=at;switch(field){
case 0:return(void*)&p->zonetype;
case 1:return(void*)&p->lx;
case 2:return(void*)&p->ly;
case 3:return(void*)&p->hx;
case 4:return(void*)&p->hy;
case 5:return(void*)&p->next;
default:abort();}}
case 15:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
default:abort();}}
case 16:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
case 1:return(void*)&p->window_inited;
case 2:return(void*)&p->terrain_typ;
case 3:return(void*)&p->menu_requested;
default:abort();}}
case 17:{struct instance_globals_f*p=at;switch(field){
case 0:return(void*)&p->ftrap;
default:abort();}}
case 18:{struct instance_globals_saved_b*p=at;switch(field){
case 0:return(void*)&p->branches;
default:abort();}}
case 19:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeons;
case 1:return(void*)&p->dungeon_topology;
case 2:return(void*)&p->dndest;
default:abort();}}
case 20:{struct instance_globals_saved_e*p=at;switch(field){
case 0:return(void*)&p->exclusion_zones;
default:abort();}}
case 21:{struct instance_globals_saved_i*p=at;switch(field){
case 0:return(void*)&p->inv_pos;
default:abort();}}
case 22:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->lastseentyp;
case 1:return(void*)&p->level;
case 2:return(void*)&p->level_info;
default:abort();}}
case 23:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->mapseenchn;
default:abort();}}
case 24:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(void*)&p->n_dgns;
default:abort();}}
case 25:{struct instance_globals_saved_q*p=at;switch(field){
case 0:return(void*)&p->quest_status;
default:abort();}}
case 26:{struct instance_globals_saved_r*p=at;switch(field){
case 0:return(void*)&p->rooms;
default:abort();}}
case 27:{struct instance_globals_saved_s*p=at;switch(field){
case 0:return(void*)&p->sp_levchn;
default:abort();}}
case 28:{struct instance_globals_saved_t*p=at;switch(field){
case 0:return(void*)&p->tune;
default:abort();}}
case 29:{struct instance_globals_saved_u*p=at;switch(field){
case 0:return(void*)&p->updest;
default:abort();}}
case 30:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
case 1:return(void*)&p->urace;
default:abort();}}
case 31:{struct lchoice*p=at;switch(field){
case 0:return(void*)&p->idx;
case 1:return(void*)&p->lev;
case 2:return(void*)&p->playerlev;
case 3:return(void*)&p->dgn;
case 4:return(void*)&p->menuletter;
default:abort();}}
case 32:{struct level_map*p=at;switch(field){
case 0:return(void*)&p->lev_name;
case 1:return(void*)&p->lev_spec;
default:abort();}}
case 33:{struct levelflags*p=at;switch(field){
default:abort();}}
case 34:{struct linfo*p=at;switch(field){
case 0:return(void*)&p->flags;
default:abort();}}
case 35:{struct mapseen*p=at;switch(field){
case 0:return(void*)&p->next;
case 1:return(void*)&p->br;
case 2:return(void*)&p->lev;
case 3:return(void*)&p->feat;
case 4:return(void*)&p->flags;
case 5:return(void*)&p->custom;
case 6:return(void*)&p->custom_lth;
case 7:return(void*)&p->msrooms;
case 8:return(void*)&p->final_resting_place;
default:abort();}}
case 36:{struct mapseen_feat*p=at;switch(field){
default:abort();}}
case 37:{struct mapseen_flags*p=at;switch(field){
default:abort();}}
case 38:{struct mapseen_rooms*p=at;switch(field){
default:abort();}}
case 39:{struct mi*p=at;switch(field){
case 0:return(void*)&p->item;
default:abort();}}
case 40:{struct mkroom*p=at;switch(field){
case 0:return(void*)&p->rtype;
case 1:return(void*)&p->orig_rtype;
default:abort();}}
case 41:{struct monst*p=at;switch(field){
case 0:return(void*)&p->data;
case 1:return(void*)&p->mx;
case 2:return(void*)&p->my;
case 3:return(void*)&p->mappearance;
case 4:return(void*)&p->m_ap_type;
default:abort();}}
case 42:{struct nh_file*p=at;switch(field){
case 0:return(void*)&p->mode;
default:abort();}}
case 43:{struct nhcoord*p=at;switch(field){
case 0:return(void*)&p->x;
case 1:return(void*)&p->y;
default:abort();}}
case 44:{struct nhl_sandbox_info*p=at;switch(field){
case 0:return(void*)&p->flags;
case 1:return(void*)&p->memlimit;
case 2:return(void*)&p->steps;
case 3:return(void*)&p->perpcall;
default:abort();}}
case 45:{struct obj*p=at;switch(field){
case 0:return(void*)&p->nobj;
case 1:return(void*)&p->ox;
case 2:return(void*)&p->oy;
default:abort();}}
case 46:{struct permonst*p=at;switch(field){
case 0:return(void*)&p->mflags1;
default:abort();}}
case 47:{struct prop*p=at;switch(field){
case 0:return(void*)&p->extrinsic;
case 1:return(void*)&p->blocked;
case 2:return(void*)&p->intrinsic;
default:abort();}}
case 48:{struct proto_dungeon*p=at;switch(field){
case 0:return(void*)&p->tmpdungeon;
case 1:return(void*)&p->tmplevel;
case 2:return(void*)&p->final_lev;
case 3:return(void*)&p->tmpbranch;
case 4:return(void*)&p->start;
case 5:return(void*)&p->n_levs;
case 6:return(void*)&p->n_brs;
default:abort();}}
case 49:{struct q_score*p=at;switch(field){
default:abort();}}
case 50:{struct rm*p=at;switch(field){
case 0:return(void*)&p->typ;
case 1:return(void*)&p->seenv;
default:abort();}}
case 51:{struct s_level*p=at;switch(field){
case 0:return(void*)&p->next;
case 1:return(void*)&p->dlevel;
case 2:return(void*)&p->proto;
case 3:return(void*)&p->boneid;
case 4:return(void*)&p->rndlevs;
case 5:return(void*)&p->flags;
default:abort();}}
case 52:{struct shclass*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->annotation;
default:abort();}}
case 53:{struct stairway*p=at;switch(field){
case 0:return(void*)&p->tolev;
case 1:return(void*)&p->up;
case 2:return(void*)&p->u_traversed;
default:abort();}}
case 54:{struct tmpbranch*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->lev;
case 2:return(void*)&p->chain;
case 3:return(void*)&p->type;
case 4:return(void*)&p->up;
default:abort();}}
case 55:{struct tmpdungeon*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->protoname;
case 2:return(void*)&p->lev;
case 3:return(void*)&p->flags;
case 4:return(void*)&p->chance;
case 5:return(void*)&p->levels;
case 6:return(void*)&p->branches;
case 7:return(void*)&p->entry_lev;
case 8:return(void*)&p->boneschar;
case 9:return(void*)&p->align;
default:abort();}}
case 56:{struct tmplevel*p=at;switch(field){
case 0:return(void*)&p->name;
case 1:return(void*)&p->chainlvl;
case 2:return(void*)&p->lev;
case 3:return(void*)&p->chance;
case 4:return(void*)&p->rndlevs;
case 5:return(void*)&p->chain;
case 6:return(void*)&p->flags;
case 7:return(void*)&p->boneschar;
default:abort();}}
case 57:{struct trap*p=at;switch(field){
case 0:return(void*)&p->ntrap;
case 1:return(void*)&p->tx;
case 2:return(void*)&p->ty;
default:abort();}}
case 58:{struct u_event*p=at;switch(field){
default:abort();}}
case 59:{struct u_have*p=at;switch(field){
default:abort();}}
case 60:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->win_create_nhwindow;
case 1:return(void*)&p->win_clear_nhwindow;
case 2:return(void*)&p->win_display_nhwindow;
case 3:return(void*)&p->win_destroy_nhwindow;
case 4:return(void*)&p->win_putstr;
case 5:return(void*)&p->win_start_menu;
case 6:return(void*)&p->win_end_menu;
case 7:return(void*)&p->win_cliparound;
default:abort();}}
case 61:{struct you*p=at;switch(field){
case 0:return(void*)&p->ux;
case 1:return(void*)&p->uy;
case 2:return(void*)&p->ux0;
case 3:return(void*)&p->uy0;
case 4:return(void*)&p->uz;
case 5:return(void*)&p->uz0;
case 6:return(void*)&p->ulevel;
case 7:return(void*)&p->urooms;
case 8:return(void*)&p->uprops;
case 9:return(void*)&p->umonster;
case 10:return(void*)&p->umonnum;
case 14:return(void*)&p->uevent;
case 15:return(void*)&p->uhave;
case 16:return(void*)&p->ualign;
case 17:return(void*)&p->ustuck;
case 18:return(void*)&p->usteed;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
int teleport_dungeon_var0(struct _IO_FILE * a0,char * a1,int a2,char * a3,char * a4){return (fprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var1(struct _IO_FILE * a0,char * a1,int a2,int a3){return (fprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var2(struct _IO_FILE * a0,char * a1,int a2,int a3){return (fprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var3(struct _IO_FILE * a0,char * a1,char * a2,char * a3,char * a4){return (fprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var4(struct _IO_FILE * a0,char * a1){return (fprintf)(a0,a1);}
int teleport_dungeon_var5(struct _IO_FILE * a0,char * a1,char * a2,int a3){return (fprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var6(struct _IO_FILE * a0,char * a1,int a2,int a3){return (fprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var7(struct _IO_FILE * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (fprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var8(struct _IO_FILE * a0,char * a1){return (fprintf)(a0,a1);}
int teleport_dungeon_var9(struct _IO_FILE * a0,char * a1,int a2,char * a3,int a4,int a5,int a6,int a7,char * a8){return (fprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_dungeon_var10(struct _IO_FILE * a0,char * a1){return (fprintf)(a0,a1);}
void teleport_dungeon_var11(char * a0,int a1){(panic)(a0,a1);}
void teleport_dungeon_var12(char * a0,char * a1){(panic)(a0,a1);}
void teleport_dungeon_var13(char * a0,char * a1){(panic)(a0,a1);}
void teleport_dungeon_var14(char * a0){(panic)(a0);}
void teleport_dungeon_var15(char * a0){(panic)(a0);}
void teleport_dungeon_var16(char * a0){(panic)(a0);}
void teleport_dungeon_var17(char * a0){(impossible)(a0);}
void teleport_dungeon_var18(char * a0){(panic)(a0);}
void teleport_dungeon_var19(char * a0){(panic)(a0);}
void teleport_dungeon_var20(char * a0,int a1){(impossible)(a0,a1);}
void teleport_dungeon_var21(char * a0){(impossible)(a0);}
void teleport_dungeon_var22(char * a0,int a1,char * a2,int a3,int a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_dungeon_var23(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dungeon_var24(char * a0,int a1,char * a2){(pline)(a0,a1,a2);}
void teleport_dungeon_var25(char * a0,char * a1,char * a2){(panic)(a0,a1,a2);}
void teleport_dungeon_var26(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
void teleport_dungeon_var27(char * a0){(panic)(a0);}
void teleport_dungeon_var28(char * a0,int a1,char * a2,int a3,int a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_dungeon_var29(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dungeon_var30(char * a0,char * a1,char * a2){(panic)(a0,a1,a2);}
void teleport_dungeon_var31(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
void teleport_dungeon_var32(char * a0){(panic)(a0);}
void teleport_dungeon_var33(char * a0,int a1,char * a2,int a3,int a4){(pline)(a0,a1,a2,a3,a4);}
void teleport_dungeon_var34(char * a0,char * a1){(pline)(a0,a1);}
void teleport_dungeon_var35(char * a0,int a1){(panic)(a0,a1);}
void teleport_dungeon_var36(char * a0,int a1){(panic)(a0,a1);}
int teleport_dungeon_var37(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_dungeon_var38(char * a0,char * a1){(panic)(a0,a1);}
int teleport_dungeon_var39(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_dungeon_var40(char * a0,char * a1){(panic)(a0,a1);}
void teleport_dungeon_var41(char * a0){(panic)(a0);}
void teleport_dungeon_var42(char * a0){(panic)(a0);}
void teleport_dungeon_var43(char * a0,int a1){(panic)(a0,a1);}
void teleport_dungeon_var44(char * a0){(panic)(a0);}
void teleport_dungeon_var45(char * a0,int a1,int a2){(pline)(a0,a1,a2);}
void teleport_dungeon_var46(char * a0,int a1){(panic)(a0,a1);}
void teleport_dungeon_var47(char * a0,int a1){(impossible)(a0,a1);}
void teleport_dungeon_var48(char * a0,char * a1){(You)(a0,a1);}
void teleport_dungeon_var49(char * a0){(panic)(a0);}
void teleport_dungeon_var50(char * a0,char * a1){(panic)(a0,a1);}
void teleport_dungeon_var51(char * a0){(impossible)(a0);}
int teleport_dungeon_var52(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var53(char * a0,char * a1,int a2,char * a3,char * a4,int a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_dungeon_var54(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,int a7,int a8){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
void teleport_dungeon_var55(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,int a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
int teleport_dungeon_var56(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var57(char * a0,char * a1,int a2,char * a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var58(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var59(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var60(char * a0,char * a1,int a2,int a3,int a4,int a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var61(char * a0,char * a1,int a2,int a3,int a4,int a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_dungeon_var62(char * a0){(impossible)(a0);}
void teleport_dungeon_var63(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
void teleport_dungeon_var64(char * a0,char * a1){(You)(a0,a1);}
int teleport_dungeon_var65(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_dungeon_var66(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var67(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var68(char * a0,char * a1,char * a2,long a3,long a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var69(char * a0,char * a1,long a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var70(char * a0,char * a1,char * a2,long a3,long a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var71(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_dungeon_var72(char * a0,char * a1,char * a2,long a3,long a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var73(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var74(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var75(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_dungeon_var76(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5){(nh_snprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var77(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var78(char * a0,char * a1,char * a2,int a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var79(char * a0,char * a1,char * a2,int a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var80(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var81(char * a0,char * a1,char * a2,int a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var82(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var83(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var84(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var85(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var86(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var87(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5,char * a6,char * a7,char * a8){return (sprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_dungeon_var88(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var89(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var90(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var91(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var92(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var93(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var94(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var95(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5){return (sprintf)(a0,a1,a2,a3,a4,a5);}
int teleport_dungeon_var96(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var97(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var98(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var99(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var100(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var101(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var102(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var103(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
void teleport_dungeon_var104(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6);}
int teleport_dungeon_var105(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var106(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var107(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var108(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_dungeon_var109(char * a0,char * a1,char * a2,char * a3,char * a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_dungeon_var110(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_dungeon_var111(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_dungeon_var112(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,char * a7,int a8){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_dungeon_var113(char * a0,char * a1,char * a2,char * a3,char * a4,char * a5,int a6){return (sprintf)(a0,a1,a2,a3,a4,a5,a6);}
void teleport_dungeon_indirect0(void (*fn)(winid),int a0){fn(a0);}
void teleport_dungeon_indirect1(void (*fn)(int, int),int a0,int a1){fn(a0,a1);}
void teleport_dungeon_indirect2(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
int teleport_dungeon_indirect3(winid (*fn)(int),int a0){return fn(a0);}
void teleport_dungeon_indirect4(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
void teleport_dungeon_indirect5(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect6(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect7(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_dungeon_indirect8(void (*fn)(winid),int a0){fn(a0);}
void teleport_dungeon_indirect9(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect10(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect11(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect12(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect13(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect14(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect15(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect16(void (*fn)(winid, boolean),int a0,signed char a1){fn(a0,a1);}
void teleport_dungeon_indirect17(void (*fn)(winid),int a0){fn(a0);}
void teleport_dungeon_indirect18(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect19(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
void teleport_dungeon_indirect20(void (*fn)(winid, int, const char *),int a0,int a1,char * a2){fn(a0,a1,a2);}
int teleport_dungeon_indirect21(winid (*fn)(int),int a0){return fn(a0);}
void teleport_dungeon_indirect22(void (*fn)(winid, unsigned long),int a0,unsigned long a1){fn(a0,a1);}
void teleport_dungeon_indirect23(void (*fn)(winid, const char *),int a0,char * a1){fn(a0,a1);}
void teleport_dungeon_indirect24(void (*fn)(winid),int a0){fn(a0);}
void teleport_dungeon_dynamic0_panic(char * a0,int a1,int a2){(panic)(a0,a1,a2);}
void teleport_dungeon_dynamic0_impossible(char * a0,int a1,int a2){(impossible)(a0,a1,a2);}
uintptr_t teleport_dungeon_owned_pointer(int i){switch(i){
default:abort();}}
uintptr_t teleport_dungeon_native_pointer(int i){switch(i){
default:abort();}}
#pragma clang diagnostic pop
void teleport_dungeon_free(void*p){(free)(p);}
static char dungeon_literals[4435];
char*teleport_dungeon_literal_storage(void){return dungeon_literals;}
size_t teleport_dungeon_literal_capacity(void){return sizeof dungeon_literals;}
static int dungeon_backing_0;
static struct level_map dungeon_backing_1[27];
static char * dungeon_backing_2[6];
static int dungeon_backing_3[6];
static char * dungeon_backing_4[6];
static int dungeon_backing_5[6];
static char * dungeon_backing_6[3];
static int dungeon_backing_7[3];
static char * dungeon_backing_8[5];
static int dungeon_backing_9[5];
void*teleport_dungeon_storage(int i){switch(i){
case 0:return &dungeon_backing_0;
case 1:return &dungeon_backing_1;
case 2:return &dungeon_backing_2;
case 3:return &dungeon_backing_3;
case 4:return &dungeon_backing_4;
case 5:return &dungeon_backing_5;
case 6:return &dungeon_backing_6;
case 7:return &dungeon_backing_7;
case 8:return &dungeon_backing_8;
case 9:return &dungeon_backing_9;
default:abort();}}
