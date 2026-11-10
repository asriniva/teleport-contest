/* SPELL: storage, native field ABI, true dependencies and callback trampolines only. */
#include "hack.h"
#include <stdlib.h>
const void *teleport_spell_global(int i){switch(i){case 0:return &u;case 1:return &gy;case 2:return &svc;case 3:return &go;case 4:return &gm;case 5:return &gn;case 6:return &gi;case 7:return &svm;case 8:return &svs;case 9:return &gs;case 10:return &svb;case 11:return &gu;case 12:return &gb;case 13:return &cg;case 14:return &flags;case 15:return &iflags;case 16:return &disp;case 17:return mons;case 18:return objects;case 19:return obj_descr;case 20:return &svl;case 21:return &gv;case 22:return xdir;case 23:return ydir;case 24:return &svd;case 25:return genders;default:return 0;}}
void *teleport_spell_equipment(int i){switch(i){case 0:return uwep;case 1:return uarm;case 2:return uarmc;case 3:return uarmh;case 4:return uarmg;case 5:return uarmf;case 6:return uarms;case 7:return ublindf;default:return 0;}}
unsigned teleport_spell_monster_bit(struct monst *p,int i){switch(i){case 0:return p->mpeaceful;default:return 0;}}
void teleport_spell_set_monster_bit(struct monst *p,int i,unsigned v){switch(i){case 0:p->mpeaceful=v;break;}}
unsigned teleport_spell_object_bit(struct obj *p,int i){switch(i){case 0:return p->in_use;case 1:return p->blessed;case 2:return p->cursed;case 3:return p->known;case 4:return p->lamplit;default:return 0;}}
void teleport_spell_set_object_bit(struct obj *p,int i,unsigned v){switch(i){case 0:p->in_use=v;break;case 1:p->blessed=v;break;case 2:p->cursed=v;break;case 3:p->known=v;break;case 4:p->lamplit=v;break;}}
unsigned teleport_spell_class_bit(struct objclass *p,int i){switch(i){case 0:return p->oc_name_known;case 1:return p->oc_dir;case 2:return p->oc_material;default:return 0;}}
void teleport_spell_set_class_bit(struct objclass *p,int i,unsigned v){switch(i){case 0:p->oc_name_known=v;break;case 1:p->oc_dir=v;break;case 2:p->oc_material=v;break;}}
unsigned teleport_spell_terrain_bit(struct rm *p,int i){switch(i){case 0:return p->doormask;default:return 0;}}
void teleport_spell_set_terrain_bit(struct rm *p,int i,unsigned v){switch(i){case 0:p->doormask=v;break;}}
unsigned teleport_spell_hero_bit(int i){switch(i){case 0:return u.uhave.bell;case 1:return u.uhave.menorah;case 2:return u.uhave.amulet;case 3:return u.uevent.invoked;case 4:return u.uevent.udemigod;case 5:return u.uevent.read_tribute;case 6:return u.uroleplay.pauper;case 7:return u.uswallow;case 8:return u.uinwater;default:return 0;}}
void teleport_spell_set_hero_bit(int i,unsigned v){switch(i){case 0:u.uhave.bell=v;break;case 1:u.uhave.menorah=v;break;case 2:u.uhave.amulet=v;break;case 3:u.uevent.invoked=v;break;case 4:u.uevent.udemigod=v;break;case 5:u.uevent.read_tribute=v;break;case 6:u.uroleplay.pauper=v;break;case 7:u.uswallow=v;break;case 8:u.uinwater=v;break;}}
const char *teleport_spell_common_string(int i){switch(i){case 0:return Never_mind;case 1:return nothing_happens;case 2:return something;case 3:return quitchars;case 4:return NH_GOLDEN;default:return ynchars;}}
int teleport_spell_win_message(void){return WIN_MESSAGE;}
const void *teleport_spell_nul_glyphinfo(void){return &nul_glyphinfo;}
static char teleport_spell_literals[TELEPORT_SPELL_LITERAL_CAPACITY+sizeof "%s"];
void *teleport_spell_literal_storage(void){return teleport_spell_literals;}
size_t teleport_spell_literal_capacity(void){return sizeof teleport_spell_literals;}
void teleport_spell_free(void *p){free(p);}
extern int teleport_spell_callback_learn(void);
extern void teleport_spell_callback_deadbook_pacify_undead(struct monst*);
extern int teleport_spell_callback_spell_cmp(const void*,const void*);
extern void teleport_spell_callback_display_spell_target_positions(boolean);
extern boolean teleport_spell_callback_can_center_spell_location(coordxy,coordxy);
extern boolean teleport_spell_callback_spell_aim_step(uint64_t,coordxy,coordxy);
static int teleport_spell_learn(void){return teleport_spell_callback_learn();}
static int teleport_spell_compare(const void*a,const void*b){return teleport_spell_callback_spell_cmp(a,b);}
static void teleport_spell_pacify(struct monst*m){teleport_spell_callback_deadbook_pacify_undead(m);}
static void teleport_spell_show(boolean b){teleport_spell_callback_display_spell_target_positions(b);}
static boolean teleport_spell_center(coordxy x,coordxy y){return teleport_spell_callback_can_center_spell_location(x,y);}
static boolean teleport_spell_aim(genericptr_t arg,coordxy x,coordxy y){return teleport_spell_callback_spell_aim_step((uint64_t)(uintptr_t)arg,x,y);}
uintptr_t teleport_spell_callback_pointer(int i){(void)i;return (uintptr_t)teleport_spell_learn;}
void teleport_spell_iterate(void){iter_mons(teleport_spell_pacify);}
void teleport_spell_qsort(void *base,size_t count,size_t size){qsort(base,count,size,teleport_spell_compare);}
void teleport_spell_hilite(void){getpos_sethilite(teleport_spell_show,teleport_spell_center);}
boolean teleport_spell_walk(coord *a,coord*b,genericptr_t arg){return walk_path(a,b,teleport_spell_aim,arg);}
winid teleport_spell_create(int type){return create_nhwindow(type);}
void teleport_spell_destroy(winid w){destroy_nhwindow(w);}
void teleport_spell_start(winid w,unsigned long b){start_menu(w,b);}
void teleport_spell_end(winid w,const char*p){end_menu(w,p);}
void teleport_spell_clear(winid w){clear_nhwindow(w);}
void teleport_spell_delay(void){nh_delay_output();}
void teleport_spell_display(winid w,boolean b){display_nhwindow(w,b);}
int teleport_spell_rng(int n,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("spell.c",line,fn);return(rn2)(n);}
int teleport_spell_rnd(int n,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("spell.c",line,fn);return(rnd)(n);}
int teleport_spell_rnl(int n,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("spell.c",line,fn);return(rnl)(n);}
int teleport_spell_dice(int n,int x,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("spell.c",line,fn);return(d)(n,x);}
void teleport_spell_snprintf(char*out,size_t n,const char*fmt,const char*arg){nh_snprintf(TELEPORT_SPELL_SNPRINTF_FUNCTION,TELEPORT_SPELL_SNPRINTF_LINE,out,n,fmt,arg);}
void teleport_spell_pline_none(const char *fmt){pline(fmt);}
void teleport_spell_pline_p(const char *fmt,const char *a0){pline(fmt,a0);}
void teleport_spell_pline_pp(const char *fmt,const char *a0,const char *a1){pline(fmt,a0,a1);}
void teleport_spell_pline_The_none(const char *fmt){pline_The(fmt);}
void teleport_spell_pline_The_p(const char *fmt,const char *a0){pline_The(fmt,a0);}
void teleport_spell_pline_The_pp(const char *fmt,const char *a0,const char *a1){pline_The(fmt,a0,a1);}
void teleport_spell_You_none(const char *fmt){You(fmt);}
void teleport_spell_You_p(const char *fmt,const char *a0){You(fmt,a0);}
void teleport_spell_You_pi(const char *fmt,const char *a0,int a1){You(fmt,a0,a1);}
void teleport_spell_Your_none(const char *fmt){Your(fmt);}
void teleport_spell_Your_pp(const char *fmt,const char *a0,const char *a1){Your(fmt,a0,a1);}
void teleport_spell_You_feel_none(const char *fmt){You_feel(fmt);}
void teleport_spell_You_hear_none(const char *fmt){You_hear(fmt);}
int teleport_spell_Sprintf_none(char *out,const char *fmt){return sprintf(out,fmt);}
int teleport_spell_Sprintf_i(char *out,const char *fmt,int a0){return sprintf(out,fmt,a0);}
int teleport_spell_Sprintf_ii(char *out,const char *fmt,int a0,int a1){return sprintf(out,fmt,a0,a1);}
int teleport_spell_Sprintf_ip(char *out,const char *fmt,int a0,const char *a1){return sprintf(out,fmt,a0,a1);}
int teleport_spell_Sprintf_ll(char *out,const char *fmt,long a0,long a1){return sprintf(out,fmt,a0,a1);}
int teleport_spell_Sprintf_p(char *out,const char *fmt,const char *a0){return sprintf(out,fmt,a0);}
int teleport_spell_Sprintf_pipip(char *out,const char *fmt,const char *a0,int a1,const char *a2,int a3,const char *a4){return sprintf(out,fmt,a0,a1,a2,a3,a4);}
int teleport_spell_Sprintf_ppp(char *out,const char *fmt,const char *a0,const char *a1,const char *a2){return sprintf(out,fmt,a0,a1,a2);}
void teleport_spell_impossible_none(const char *fmt){impossible(fmt);}
void teleport_spell_impossible_p(const char *fmt,const char *a0){impossible(fmt,a0);}
void teleport_spell_impossible_i(const char *fmt,int a0){impossible(fmt,a0);}
void teleport_spell_impossible_ii(const char *fmt,int a0,int a1){impossible(fmt,a0,a1);}
void teleport_spell_livelog_printf_p(long category,const char *fmt,const char *a0){livelog_printf(category,fmt,a0);}
