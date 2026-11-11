#include "standalone-monster-creation-probe.c"
#include STANDALONE_MAKEMON_SOURCE
static coord positions[ROWNO*(COLNO-1)];
int probe_position_debug(void){
#ifdef DEBUG
 return 1;
#else
 return 0;
#endif
}
void probe_position_cell(int x,int y,int type,int flags){levl[x][y].typ=type;levl[x][y].flags=flags;}
int probe_position_good(int type,int x,int y,unsigned flags){struct monst mon=cg.zeromonst;mon.data=&mons[type];return goodpos(x,y,&mon,flags);}
int probe_position_near(int type,int x,int y,unsigned flags){return enexto_core(&positions[0],x,y,&mons[type],flags);}
int probe_position_collect(int x,int y,int radius,unsigned flags){return collect_coords(positions,x,y,radius,flags,NULL);}
void *probe_position_coords(void){return positions;}
void *probe_position_engr(int type,long when,int text){static const char*texts[]={"Elbereth","elbereth","Elbereth test",""};if(type<0)del_engr_at(10,10);else make_engr_at(10,10,texts[text],NULL,when,type);return head_engr;}
void probe_position_exclusion(int on,int type){static struct exclusion_zone zone;memset(&zone,0,sizeof zone);zone.zonetype=type;zone.lx=zone.ly=9;zone.hx=zone.hy=11;sve.exclusion_zones=on?&zone:NULL;}
void probe_position_object(int on){static struct obj boulder;memset(&boulder,0,sizeof boulder);boulder.otyp=BOULDER;svl.level.objects[10][10]=on?&boulder:NULL;}
int probe_position_debug_match(int wizard_mode,int pattern,int file,int wild){
 static const char*patterns[]={"","*","teleport.c","mon.c teleport.c","nope.c","tele*.c"};
 static const char*files[]={"/src/teleport.c","teleport.js","teleport.c",""};
 boolean saved=flags.debug;char*old=sysopt.debugfiles;flags.debug=wizard_mode;sysopt.debugfiles=(char*)patterns[pattern];int r=debugcore(files[file],wild);flags.debug=saved;sysopt.debugfiles=old;return r;
}
void *probe_position_spawn(int type,int x,int y,unsigned flags){return makemon(type<0?NULL:&mons[type],x,y,flags);}
void probe_position_group(int n,unsigned flags){struct monst*m=svl.level.monlist;m_initgrp(m,m->mx,m->my,n,flags);}
void probe_position_dispose_group(void){while(svl.level.monlist){struct monst*m=svl.level.monlist;svl.level.monlist=m->nmon;m->nmon=NULL;svl.level.monsters[m->mx][m->my]=NULL;discard_minvent(m,FALSE);if(emits_light(m->data))del_light_source(LS_MONSTER,monst_to_any(m));dealloc_monst(m);}dobjsfree();}
