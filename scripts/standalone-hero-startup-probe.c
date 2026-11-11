/* Actual source owners, included to inspect their private initialization data. */
#include "standalone-dungeon-startup-probe.c"
#include "artifact.c"
#include "u_init.c"
void probe_hero_init(void){init_objects();role_init();init_dungeons();init_artifacts();u_init_misc();l_nhcore_init();}
const volatile void *probe_hero_global(int op){switch(op){case 0:return artilist;case 1:return artiexist;case 2:return artidisco;case 3:return &u;case 4:return &gy;case 5:return &gm;case 6:return &gw;case 7:return &ubirthday;case 8:return &urealtime;case 9:return &svl;}return NULL;}
unsigned long probe_hero_layout(int op){const unsigned long values[]={sizeof(struct trobj),offsetof(struct trobj,trotyp),offsetof(struct trobj,trspe),offsetof(struct trobj,trclass),offsetof(struct trobj,trquan_min),offsetof(struct trobj,trquan_max),offsetof(struct trobj,trbless),sizeof(struct inv_sub),offsetof(struct inv_sub,race_pm),offsetof(struct inv_sub,item_otyp),offsetof(struct inv_sub,subs_otyp)};return values[op];}

void probe_hero_roleplay(unsigned mask,long bones,long rerolls){u.uroleplay.blind=!!(mask&1);u.uroleplay.nudist=!!(mask&2);u.uroleplay.deaf=!!(mask&4);u.uroleplay.pauper=!!(mask&8);u.uroleplay.reroll=!!(mask&16);u.uroleplay.reserved1=!!(mask&32);u.uroleplay.reserved2=!!(mask&64);u.uroleplay.reserved3=!!(mask&128);u.uroleplay.numbones=bones;u.uroleplay.numrerolls=rerolls;}
