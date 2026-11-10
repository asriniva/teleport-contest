/* Typed memory, header macros, RNG provenance and varargs ABI only.
 * No explode.c function or source-file algorithm is retained here. */
#include "hack.h"
#include <stdarg.h>
const void *teleport_explode_global(int i) {
 switch(i){case 0:return &u;case 1:return &gy.youmonst;case 2:return &svl.level.locations;
 case 3:return &svl.level.objects;case 4:return &svl.level.monsters;case 5:return &svk.killer.format;
 case 6:return &svk.killer.name;case 7:return &svc.context.mon_moving;case 8:return &gi.invent;
 case 9:return &gm.multi;case 10:return &gb.bhitpos;case 11:return &gt.thrownobj;
 case 12:return &flags.sparkle;case 13:return &flags.verbose;case 14:return &iflags.last_msg;
 case 15:return &objects;case 16:return xdir;case 17:return ydir;case 18:return shield_static;
 case 19:return &uball;case 20:return &uchain;default:return 0;}
}
int teleport_explode_hero_flag(int i){switch(i){
 case 0:return !!Antimagic;case 1:return !!Fire_resistance;case 2:return !!Cold_resistance;
 case 3:return !!Disint_resistance;case 4:return !!Shock_resistance;case 5:return !!Poison_resistance;
 case 6:return !!Acid_resistance;case 7:return !!Hallucination;case 8:return !!Deaf;
 case 9:return !!Invulnerable;case 10:return !!Upolyd;case 11:return Role_switch;
 case 12:return u.uswallow;case 13:return u.uundetected;case 14:return !!Half_physical_damage;
 case 15:return disp.botl;default:return 0;}}
void teleport_explode_set_botl(int v){disp.botl=v;}
int teleport_explode_object_bit(struct obj *o,int i){switch(i){case 0:return o->odiluted;case 1:return o->lamplit;case 2:return o->how_lost;default:return 0;}}
void teleport_explode_set_object_bit(struct obj *o,int i,unsigned v){switch(i){case 0:o->odiluted=v;break;case 1:o->lamplit=v;break;case 2:o->how_lost=v;break;}}
int teleport_explode_monster_bit(struct monst *m,int i){(void)i;return m->mtrapped;}
void teleport_explode_set_monster_bit(struct monst *m,int i,unsigned v){(void)i;m->mtrapped=v;}
int teleport_explode_trap_type(struct trap *t){return t->ttyp;}
int teleport_explode_monster_macro(struct monst *m,int i){switch(i){
 case 0:return resists_fire(m);case 1:return resists_cold(m);case 2:return resists_disint(m);
 case 3:return resists_elec(m);case 4:return resists_poison(m);case 5:return resists_acid(m);
 case 6:return is_vampshifter(m);default:return 0;}}
int teleport_explode_permonst_macro(struct permonst *p,int i){switch(i){
 case 0:return nonliving(p);case 1:return is_demon(p);case 2:return digests(p);
 case 3:return completelyburns(p);case 4:return bigmonst(p);case 5:return hides_under(p);default:return 0;}}
int teleport_explode_display_macro(int i,int a,int b){switch(i){
 case 0:return cansee(a,b);case 1:return explosion_to_glyph(a,b);case 2:return cmap_to_glyph(a);
 default:return 0;}}
void teleport_explode_delay(void){nh_delay_output();}
void teleport_explode_monstseesu_ad(uchar adtyp){monstseesu_ad(adtyp);}
void teleport_explode_monstunseesu_ad(uchar adtyp){monstunseesu_ad(adtyp);}
const char *teleport_explode_pronoun(int possessive){return possessive?uhis():uhim();}
static const char *const teleport_explode_callers[]={"scatter","splatter_burning_oil","mon_explodes"};
int teleport_explode_rn2(int bound,int line,int caller){if(rng_log_enabled())rng_log_set_caller("explode.c",line,teleport_explode_callers[caller]);return(rn2)(bound);}
int teleport_explode_rnd(int bound,int line,int caller){if(rng_log_enabled())rng_log_set_caller("explode.c",line,teleport_explode_callers[caller]);return(rnd)(bound);}
int teleport_explode_d(int count,int sides,int line,int caller){if(rng_log_enabled())rng_log_set_caller("explode.c",line,teleport_explode_callers[caller]);return(d)(count,sides);}
void teleport_explode_pline(const char*f,const char*a,const char*b){pline(f,a,b);}
void teleport_explode_pline_The(const char*f,const char*a){pline_The(f,a);}
void teleport_explode_You(const char*f,const char*a){You(f,a);}
void teleport_explode_You_hear(const char*f){You_hear(f, (char *) 0);}
void teleport_explode_impossible(const char*f,int a,int b,int c,int d){impossible(f,a,b,c,d);}
char *teleport_explode_sprintf(char*out,const char*f,const char*a){Sprintf(out,f,a);return out;}
void teleport_explode_snprintf(char*out,size_t size,const char*f,const char*a,const char*b,const char*c,int line){nh_snprintf("explode",line,out,size,f,a,b,c);}
static char teleport_explode_literals[945];
void *teleport_explode_literal_storage(void){return teleport_explode_literals;}
size_t teleport_explode_literal_capacity(void){return sizeof teleport_explode_literals;}

int teleport_explode_object_class_bit(int type,int i){return i?objects[type].oc_material:objects[type].oc_dir;}
