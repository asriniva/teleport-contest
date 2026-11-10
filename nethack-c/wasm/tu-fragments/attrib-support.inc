/* Typed fields/header macros/varargs only; no ATTRIB function or table policy. */
#include "hack.h"
#include <assert.h>
struct teleport_attrib_innate {schar ulevel;long *ability;const char *gainstr,*losestr;};
/* Source-derived row count is validated by attrib metadata checker. */
static struct teleport_attrib_innate teleport_attrib_tables[62];
const char *teleport_attrib_names[6] __asm__("attrname");
void *teleport_attrib_table_storage(void){return teleport_attrib_tables;}
size_t teleport_attrib_table_count(void){return sizeof teleport_attrib_tables/sizeof teleport_attrib_tables[0];}
void *teleport_attrib_attrname_storage(void){return teleport_attrib_names;}
static char teleport_attrib_fromwhat[BUFSZ];
void *teleport_attrib_fromwhat_buffer(void){return teleport_attrib_fromwhat;}
const void *teleport_attrib_global(int i){switch(i){case 0:return &u;case 1:return &gu.urole;case 2:return &gu.urace;case 3:return &gy.youmonst;case 4:return &gi.invent;case 5:return &svm.moves;case 6:return &gm.multi;case 7:return &svc.context.next_attrib_check;case 8:return &svk.killer.format;case 9:return svk.killer.name;case 10:return &flags.initalign;case 11:return &flags.verbose;case 12:return &program_state.in_moveloop;case 14:return mons;case 15:return aligns;default:return 0;}}
struct permonst *teleport_attrib_hero_data(void){return gy.youmonst.data;}
long teleport_attrib_flag(int i){switch(i){case 0:return !!Fixed_abil;case 1:return !!Poison_resistance;case 2:return !!Half_gas_damage;case 3:return !!Wounded_legs;case 4:return !!Upolyd;case 5:return !!Hallucination;case 6:return !!Confusion;case 7:return !!Sick;case 8:return !!Vomiting;case 9:return !!Fumbling;case 10:return !!Blindfolded_only;case 11:return !!Very_fast;case 12:return !!wizard;case 13:return HClairvoyant;case 14:return BClairvoyant;case 15:return HRegeneration;case 16:return HStun;case 17:return HBlnd_resist;case 18:return HFast;case 19:return EFast;case 20:return HBlinded;case 21:return EBlinded;case 22:return BBlinded;case 23:return BlindedTimeout;default:return 0;}}
int teleport_attrib_botl(void){return disp.botl;}void teleport_attrib_set_botl(int v){disp.botl=v;}
int teleport_attrib_roleplay_bit(int i){return i?u.uroleplay.deaf:u.uroleplay.blind;}
int teleport_attrib_object_bit(struct obj*o,int i){switch(i){case 0:return o->cursed;case 1:return o->blessed;case 2:return o->dknown;default:return 0;}}
int teleport_attrib_object_name_known(int i){return objects[i].oc_name_known;}
int teleport_attrib_pm_macro(struct permonst*p,int i){return i?type_is_pname(p):haseyes(p);}
int teleport_attrib_wield_art(int i){return !!u_wield_art(i);}
int teleport_attrib_astral(d_level*d){return !!Is_astralevel(d);}
struct obj*teleport_attrib_equipment(int i){switch(i){case 0:return uarmh;case 1:return uarmg;case 2:return uarmf;case 3:return uarmc;case 4:return ublindf;default:return 0;}}
void teleport_attrib_assert(int test){if(!test)__assert_fail("chridx >= 0 && chridx < A_MAX","attrib.c",1204,"acurr");}
static const char*const teleport_attrib_callers[]={"adjattrib","gainstr","losestr","poisoned","exercise","exerchk","rnd_attr","redist_attr","vary_init_attr","newhp","uchangealign"};
int teleport_attrib_rn2(int n,int line,int caller){if(rng_log_enabled())rng_log_set_caller("attrib.c",line,teleport_attrib_callers[caller]);return(rn2)(n);}
int teleport_attrib_rnd(int n,int line,int caller){if(rng_log_enabled())rng_log_set_caller("attrib.c",line,teleport_attrib_callers[caller]);return(rnd)(n);}
int teleport_attrib_rn1(int n,int base,int line,int caller){if(rng_log_enabled())rng_log_set_caller("attrib.c",line,teleport_attrib_callers[caller]);return(rn2)(n)+base;}
int teleport_attrib_d(int n,int sides,int line,int caller){if(rng_log_enabled())rng_log_set_caller("attrib.c",line,teleport_attrib_callers[caller]);return(d)(n,sides);}
void teleport_attrib_message(int kind,const char*f,const char*a,const char*b,const char*c){switch(kind){case 0:pline(f,a,b,c);break;case 1:pline_The(f,a,b,c);break;case 2:You(f,a,b,c);break;case 3:Your(f,a,b,c);break;case 4:You_feel(f,a,b,c);break;}}
void teleport_attrib_message_char(int kind,const char*f,const char*a,int c){switch(kind){case 2:You(f,a,c);break;case 3:Your(f,a,c);break;case 4:You_feel(f,a,c);break;}}
void teleport_attrib_impossible(const char*f,int a,int b){impossible(f,a,b);}
char*teleport_attrib_sprintf(char*out,const char*f,const char*a){Sprintf(out,f,a);return out;}
void teleport_attrib_livelog(long flags,const char*f,const char*a){livelog_printf(flags,f,a);}
void teleport_attrib_debug0(const char*f){if(debugcore("attrib.c",TRUE)){int saved=iflags.last_msg;pline(f,(char*)0);iflags.last_msg=saved;}}
void teleport_attrib_debug1_int(const char*f,int a){if(debugcore("attrib.c",TRUE)){int saved=iflags.last_msg;pline(f,a);iflags.last_msg=saved;}}
void teleport_attrib_debug1_long(const char*f,long a){if(debugcore("attrib.c",TRUE)){int saved=iflags.last_msg;pline(f,a);iflags.last_msg=saved;}}
void teleport_attrib_debug2(const char*f,const char*a,int b){if(debugcore("attrib.c",TRUE)){int saved=iflags.last_msg;pline(f,a,b);iflags.last_msg=saved;}}
void teleport_attrib_debug3(const char*f,const char*a,const char*b,int c){if(debugcore("attrib.c",TRUE)){int saved=iflags.last_msg;pline(f,a,b,c);iflags.last_msg=saved;}}
static char teleport_attrib_literals[1650];void*teleport_attrib_literal_storage(void){return teleport_attrib_literals;}size_t teleport_attrib_literal_capacity(void){return sizeof teleport_attrib_literals;}

const char*teleport_attrib_something(void){return something;}
