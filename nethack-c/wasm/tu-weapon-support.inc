/* WEAPON ABI only. Source policy/data are authoritative in JS. */
#include "hack.h"
static struct throw_and_return_weapon teleport_weapon_arwep[1];
static char teleport_weapon_kebabable[6];
size_t teleport_weapon_storage_count(int index) { return index?SIZE(teleport_weapon_kebabable):SIZE(teleport_weapon_arwep); }
void *teleport_weapon_storage(int index) { return index? (void*)teleport_weapon_kebabable:(void*)teleport_weapon_arwep; }
const void *teleport_weapon_global(int index)
{
 switch(index){case 0:return &u;case 1:return objects;case 2:return obj_descr;
 case 3:return mons;case 4:return &gy;case 5:return &gp;case 6:return &gu;
 case 7:return &gi;case 8:return &iflags;case 9:return &svc;case 10:return &cg;
 case 11:return &flags;case 12:return &gv;case 13:return (void*)genders;case 14:return (void*)def_oc_syms;default:return 0;}
}
void *teleport_weapon_equipment(int index) { return index==0?uleft:index==1?uright:index==2?uwep:uswapwep; }
void *teleport_weapon_hands(void) { return &hands_obj; }
const glyph_info *teleport_weapon_nul_glyphinfo(void) { return &nul_glyphinfo; }
unsigned teleport_weapon_object_bit(struct obj *obj,int index)
{switch(index){case 0:return obj->globby;case 1:return obj->blessed;case 2:return obj->lamplit;case 3:return obj->dknown;case 4:return obj->cursed;case 5:return obj->bknown;case 6:return obj->oeroded;default:return obj->oeroded2;}}
void teleport_weapon_set_object_bit(struct obj *obj,int index,unsigned value)
{switch(index){case 0:obj->globby=value;break;case 1:obj->blessed=value;break;case 2:obj->lamplit=value;break;case 3:obj->dknown=value;break;case 4:obj->cursed=value;break;case 5:obj->bknown=value;break;case 6:obj->oeroded=value;break;default:obj->oeroded2=value;break;}}
unsigned teleport_weapon_class_bit(struct objclass *obj,int index) { return index==0?obj->oc_material:obj->oc_bimanual; }
unsigned teleport_weapon_tethered(struct throw_and_return_weapon *record) { return record->tethered; }
void teleport_weapon_set_tethered(struct throw_and_return_weapon *record,unsigned value) { record->tethered=value; }
void teleport_weapon_free(void *ptr) { free(ptr); }
char *teleport_weapon_distant_name(struct obj *obj) { return distant_name(obj,doname); }
winid teleport_weapon_create(int type) { return create_nhwindow(type); }
void teleport_weapon_start(winid win,unsigned long flags_) { start_menu(win,flags_); }
void teleport_weapon_end(winid win,const char *prompt) { end_menu(win,prompt); }
void teleport_weapon_destroy(winid win) { destroy_nhwindow(win); }
char teleport_weapon_y_n(const char *prompt) { return y_n(prompt); }
int teleport_weapon_rng(int bound,int dice,int line,const char *caller)
{ if(rng_log_enabled())rng_log_set_caller("weapon.c",line,caller);return dice?(d)(dice,bound):(rn2)(bound); }
int teleport_weapon_rnd(int bound,int line,const char *caller)
{ if(rng_log_enabled())rng_log_set_caller("weapon.c",line,caller);return (rnd)(bound); }
unsigned teleport_weapon_strlen(const char *text) { return Strlen_(text,"add_skills_to_menu",TELEPORT_WEAPON_STRLEN_LINE); }
void teleport_weapon_pline(const char *fmt,const char *a,const char *b,const char *c,const char *d_) { pline(fmt,a,b,c,d_); }
void teleport_weapon_You(const char *fmt,const char *a,const char *b) { You(fmt,a,b); }
void teleport_weapon_Your(const char *fmt,const char *a,const char *b,const char *c,const char *d_) { Your(fmt,a,b,c,d_); }
void teleport_weapon_You_feel(const char *fmt,const char *a) { You_feel(fmt,a); }
void teleport_weapon_pline_mon(struct monst *mon,const char *fmt,const char *a,const char *b) { pline_mon(mon,fmt,a,b); }
void teleport_weapon_pline_mon_ppi(struct monst *mon,const char *fmt,const char *a,const char *b,int c) { pline_mon(mon,fmt,a,b,c); }
void teleport_weapon_impossible_i(const char *fmt,int value) { impossible(fmt,value); }
void teleport_weapon_impossible_p(const char *fmt,const char *value) { impossible(fmt,value); }
void teleport_weapon_impossible_ip(const char *fmt,int value,const char *text) { impossible(fmt,value,text); }
void teleport_weapon_panic(const char *fmt,int value) { panic(fmt,value); }
void teleport_weapon_sprintf_p(char *out,const char *fmt,const char *a) { Sprintf(out,fmt,a); }
void teleport_weapon_sprintf_pp(char *out,const char *fmt,const char *a,const char *b) { Sprintf(out,fmt,a,b); }
void teleport_weapon_sprintf_ppp(char *out,const char *fmt,const char *a,const char *b,const char *c) { Sprintf(out,fmt,a,b,c); }
void teleport_weapon_sprintf_ip(char *out,const char *fmt,int a,const char *b) { Sprintf(out,fmt,a,b); }
static const int teleport_weapon_snprintf_lines[]=TELEPORT_WEAPON_SNPRINTF_LINES;
void teleport_weapon_snprintf0(char *out,size_t size,const char *fmt,const char *a,int b,const char *c,const char *d_,int e,int f)
{nh_snprintf("add_skills_to_menu",teleport_weapon_snprintf_lines[0],out,size,fmt,a,b,c,d_,e,f);}
void teleport_weapon_snprintf1(char *out,size_t size,const char *fmt,const char *a,const char *b,const char *c,int d_,int e)
{nh_snprintf("add_skills_to_menu",teleport_weapon_snprintf_lines[1],out,size,fmt,a,b,c,d_,e);}
void teleport_weapon_snprintf2(char *out,size_t size,const char *fmt,const char *a,int b,const char *c,const char *d_)
{nh_snprintf("add_skills_to_menu",teleport_weapon_snprintf_lines[2],out,size,fmt,a,b,c,d_);}
void teleport_weapon_snprintf3(char *out,size_t size,const char *fmt,const char *a,const char *b,const char *c)
{nh_snprintf("add_skills_to_menu",teleport_weapon_snprintf_lines[3],out,size,fmt,a,b,c);}
#ifdef TELEPORT_WEAPON_LITERAL_CAPACITY
static char teleport_weapon_literals[TELEPORT_WEAPON_LITERAL_CAPACITY + sizeof "s"];
void *teleport_weapon_literal_storage(void) { return teleport_weapon_literals; }
size_t teleport_weapon_literal_capacity(void) { return sizeof teleport_weapon_literals; }
#endif
