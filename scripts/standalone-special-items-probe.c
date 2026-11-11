#include "standalone-timers-probe.c"
/* A valid explicit component-input map, not replacement dungeon policy. */
void probe_species_config(int level,int depth,int align,int temperature,int hell,int plane){
 svn.n_dgns=3;svd.dungeon_topology.d_quest_dnum=1;
 svd.dungeon_topology.d_astral_level.dnum=2;svd.dungeon_topology.d_astral_level.dlevel=5;
 svd.dungeon_topology.d_sanctum_level.dnum=0;svd.dungeon_topology.d_sanctum_level.dlevel=25;
 svd.dungeon_topology.d_air_level.dnum=2;svd.dungeon_topology.d_air_level.dlevel=1;
 svd.dungeon_topology.d_fire_level.dnum=2;svd.dungeon_topology.d_fire_level.dlevel=2;
 svd.dungeon_topology.d_water_level.dnum=2;svd.dungeon_topology.d_water_level.dlevel=3;
 svd.dungeon_topology.d_earth_level.dnum=2;svd.dungeon_topology.d_earth_level.dlevel=4;
 for(int i=0;i<3;i++){svd.dungeons[i].num_dunlevs=30;svd.dungeons[i].entry_lev=1;svd.dungeons[i].depth_start=1;svd.dungeons[i].flags.align=align;svd.dungeons[i].flags.hellish=hell;}
 u.ulevel=level;u.uz.dnum=plane?2:0;u.uz.dlevel=plane?plane:depth;svl.level.flags.temperature=temperature;
}
int probe_species_select(int low,int high){struct permonst *p=rndmonst_adj(low,high);return p?monsndx(p):NON_PM;}
int probe_species_biology(int op,int type,int flag){switch(op){case 0:return zombie_form(&mons[type]);case 1:return undead_to_corpse(type);case 2:return can_be_hatched(type);case 3:return dead_species(type,flag);case 4:return little_to_big(type);case 5:return big_to_little(type);}abort();}
void probe_special_dispose(void){obfree(items[0],NULL);items[0]=NULL;}
