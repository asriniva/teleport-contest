/* Real game owners; these wrappers supply inputs/observe state only. */
#include "standalone-item-naming-probe.c"
static struct monst *created;
static unsigned char vision_cells[ROWNO][COLNO];
static unsigned char *vision_rows[ROWNO];
void probe_monster_prepare(void){
 probe_species_config(10,5,AM_NONE,0,0,0);svm.moves=1L;
 gi.in_mklev=TRUE;svl.level.flags.rndmongen=TRUE;
 u.ux=40;u.uy=10;u.ualign.type=A_NEUTRAL;u.ualign.record=10;
 gu.urace.mnum=PM_HUMAN;gu.urace.hatemask=M2_ORC;gu.urace.lovemask=M2_HUMAN;
 for(int y=0;y<ROWNO;y++)vision_rows[y]=vision_cells[y];gv.viz_array=vision_rows;
 for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;
}
void *probe_monster_create(int type,int x,int y,unsigned flags){if(created)abort();return created=makemon(type>=0?&mons[type]:NULL,x,y,flags);}
void *probe_monster_global(int op){switch(op){case 0:return &svl;case 1:return &svm;case 2:return &svq;case 3:return &gu;case 4:return &gi;case 5:return &svc;case 6:return &gl;case 7:return &gv;case 8:return mons;}return NULL;}
void probe_monster_dispose(void){
 if(!created)return;
 /* Input graph teardown only: production callers must remove map/list owners
  * through the appropriate world policy before dealloc_monst. */
 if(created->nmon)abort();
 discard_minvent(created,FALSE);dobjsfree();
 if(emits_light(created->data))del_light_source(LS_MONSTER,monst_to_any(created));
 svl.level.monsters[created->mx][created->my]=NULL;svl.level.monlist=NULL;
 dealloc_monst(created);created=NULL;
}
long probe_monster_op(int op,int type,int a,int b){switch(op){
 case 0:return propagate(type,a,b);case 1:return mbirth_limit(type);
 case 2:return adj_lev(&mons[type]);case 3:return peace_minded(&mons[type]);
 case 4:set_malign(created);break;case 5:return monhp_per_lvl(created);
 case 6:newmonhp(created,type);break;
 }return 0;}
