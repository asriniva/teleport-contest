/* Test-only access to actual source-private RESTORE entries; no policy copies. */
#include "restore.c"
void recovery_add_id(unsigned gid,unsigned nid){add_id_mapping(gid,nid);}
void recovery_clear_ids(void){clear_id_mapping();}
struct obj *recovery_restobjchn(NHFILE *f,boolean frozen){return restobjchn(f,frozen);}
struct monst *recovery_restmonchn(NHFILE *f){return restmonchn(f);}
const void *recovery_bucket(void){return gi.id_map;}
unsigned recovery_id_count(void){return gn.n_ids_mapped;}
unsigned recovery_bucket_width(void){return N_PER_BUCKET;}
size_t recovery_bucket_size(void){return sizeof(struct bucket);}
const struct permonst *recovery_mons(void){return mons;}
void recovery_seed(unsigned long seed){init_isaac64(seed,rn2);init_isaac64(seed,rn2_on_display_rng);}
