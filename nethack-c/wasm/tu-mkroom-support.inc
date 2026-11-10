/* MKROOM ABI only: live storage addresses, packed fields and original calls. */
extern const struct shclass shtypes[];
void *teleport_mkroom_global(int i){switch(i){case 0:return &svr;case 1:return &svn;case 2:return &gs;case 3:return &gn;case 4:return &svl;case 5:return &svd;case 6:return &svm;case 7:return &u;case 8:return &flags;case 9:return (void*)shtypes;case 10:return (void*)def_oc_syms;default:return mons;}}
long teleport_mkroom_birthday(void){return (long)ubirthday;}
void *teleport_mkroom_shrine(void){static coord buf;return &buf;}
unsigned teleport_mkroom_terrain_bit(int x,int y,int i){switch(i){case 0:return levl[x][y].lit;case 1:return levl[x][y].roomno;case 2:return levl[x][y].edge;default:return levl[x][y].altarmask;}}
void teleport_mkroom_set_terrain_bit(int x,int y,int i,unsigned v){switch(i){case 0:levl[x][y].lit=v;break;case 1:levl[x][y].roomno=v;break;case 2:levl[x][y].edge=v;break;default:levl[x][y].altarmask=v;}}
unsigned teleport_mkroom_level_bit(int i){switch(i){case 0:return svl.level.flags.is_maze_lev;case 1:return svl.level.flags.has_court;case 2:return svl.level.flags.has_barracks;case 3:return svl.level.flags.has_zoo;case 4:return svl.level.flags.has_morgue;case 5:return svl.level.flags.has_swamp;case 6:return svl.level.flags.has_beehive;case 7:return svl.level.flags.has_temple;default:return svl.level.flags.graveyard;}}
void teleport_mkroom_set_level_bit(int i,unsigned v){switch(i){case 0:svl.level.flags.is_maze_lev=v;break;case 1:svl.level.flags.has_court=v;break;case 2:svl.level.flags.has_barracks=v;break;case 3:svl.level.flags.has_zoo=v;break;case 4:svl.level.flags.has_morgue=v;break;case 5:svl.level.flags.has_swamp=v;break;case 6:svl.level.flags.has_beehive=v;break;case 7:svl.level.flags.has_temple=v;break;default:svl.level.flags.graveyard=v;}}
unsigned teleport_mkroom_monster_bit(struct monst*m,int i){return i?m->mpeaceful:m->msleeping;}
void teleport_mkroom_set_monster_bit(struct monst*m,int i,unsigned v){if(i)m->mpeaceful=v;else m->msleeping=v;}
int teleport_mkroom_rn2(int n,int line,const char *caller){if(rng_log_enabled())rng_log_set_caller("mkroom.c",line,caller);return (rn2)(n);}
int teleport_mkroom_rnd(int n,int line,const char *caller){if(rng_log_enabled())rng_log_set_caller("mkroom.c",line,caller);return (rnd)(n);}
void teleport_mkroom_impossible(const char *format,int value){impossible(format,value);}
void teleport_mkroom_sfo_room(NHFILE*f,struct mkroom*r,const char*tag){Sfo_mkroom(f,r,tag);}
void teleport_mkroom_sfi_room(NHFILE*f,struct mkroom*r,const char*tag){Sfi_mkroom(f,r,tag);}
void teleport_mkroom_sfo_int(NHFILE*f,int*r,const char*tag){Sfo_int(f,r,tag);}
void teleport_mkroom_sfi_int(NHFILE*f,int*r,const char*tag){Sfi_int(f,r,tag);}
static char teleport_mkroom_literals[TELEPORT_MKROOM_LITERAL_CAPACITY];
void *teleport_mkroom_literal_storage(void){return teleport_mkroom_literals;}
size_t teleport_mkroom_literal_capacity(void){return sizeof teleport_mkroom_literals;}
