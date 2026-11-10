/* ENGRAVE typed native ABI only; no source engraving policies/data here. */
#include "tu-engrave-support.h"
const void *teleport_engrave_global(int index){switch(index){case 0:return &u;case 1:return &svm;case 2:return &svc;case 3:return &svl;case 4:return &gi;case 5:return &gm;case 6:return &gn;case 7:return &gy;case 8:return &iflags;case 9:return &flags;case 10:return &gu;case 11:return objects;case 12:return mons;case 13:return &svd;default:return 0;}}
void *teleport_engrave_head(void){return head_engr;}
void teleport_engrave_set_head(struct engr *ep){head_engr=ep;}
void *teleport_engrave_equipment(int index){return index==0?uwep:index==1?uarms:ublindf;}
void *teleport_engrave_hands(void){return &hands_obj;}
unsigned teleport_engrave_object_bit(struct obj *obj,int index){return index?obj->known:obj->cursed;}
void teleport_engrave_set_object_bit(struct obj *obj,int index,unsigned value){if(index)obj->known=value;else obj->cursed=value;}
unsigned teleport_engrave_class_bit(struct objclass *cls,int index){return index==0?cls->oc_name_known:index==1?cls->oc_tough:cls->oc_bimanual;}
unsigned teleport_engrave_engr_bit(struct engr *ep,int index){switch(index){case 0:return ep->guardobjects;case 1:return ep->nowipeout;case 2:return ep->eread;default:return ep->erevealed;}}
void teleport_engrave_set_engr_bit(struct engr *ep,int index,unsigned value){switch(index){case 0:ep->guardobjects=value;break;case 1:ep->nowipeout=value;break;case 2:ep->eread=value;break;default:ep->erevealed=value;break;}}
unsigned teleport_engrave_hero_bit(int index){return index==0?u.uswallow:index==1?u.uundetected:u.uroleplay.deaf;}
unsigned teleport_engrave_terrain_bit(struct rm *cell,int index){return index?cell->drawbridgemask:cell->disturbed;}
void teleport_engrave_set_terrain_bit(struct rm *cell,int index,unsigned value){if(index)cell->drawbridgemask=value;else cell->disturbed=value;}
const char *teleport_engrave_common_string(int index){return index==0?Something:index==1?Never_mind:index==2?vision_clears:ynqchars;}
static unsigned char teleport_engrave_encoded[9][21];
void *teleport_engrave_storage(int index){(void)index;return teleport_engrave_encoded;}
size_t teleport_engrave_storage_size(int index){(void)index;return sizeof teleport_engrave_encoded;}
static char teleport_engrave_literals[TELEPORT_ENGRAVE_LITERAL_CAPACITY+sizeof "%s"+sizeof ENGRAVEFILE+sizeof EPITAPHFILE];
void *teleport_engrave_literal_storage(void){return teleport_engrave_literals;}
size_t teleport_engrave_literal_capacity(void){return sizeof teleport_engrave_literals;}
void teleport_engrave_free(void *ptr){free(ptr);}
extern int teleport_engrave_callback_stylus_ok(struct obj*);
extern int teleport_engrave_callback_engrave(void);
static int teleport_engrave_stylus_trampoline(struct obj *obj){return teleport_engrave_callback_stylus_ok(obj);}
static int teleport_engrave_occupation_trampoline(void){return teleport_engrave_callback_engrave();}
struct obj *teleport_engrave_getobj(const char *prompt,unsigned flags_){return getobj(prompt,teleport_engrave_stylus_trampoline,flags_);}
void teleport_engrave_occupation(const char *text,cmdcount_nht xtime){set_occupation(teleport_engrave_occupation_trampoline,text,xtime);}
void teleport_engrave_getlin(const char *prompt,char *out){getlin(prompt,out);}
char *teleport_engrave_random_text(const char *file,char *out,unsigned pad){return get_rnd_text(file,out,(rn2),pad);}
int teleport_engrave_rng(int bound,int line,const char *caller){if(rng_log_enabled())rng_log_set_caller("engrave.c",line,caller);return (rn2)(bound);}
int teleport_engrave_rnd(int bound,int line,const char *caller){if(rng_log_enabled())rng_log_set_caller("engrave.c",line,caller);return (rnd)(bound);}
unsigned teleport_engrave_strlen(const char *text,int site){static const int lines[]=TELEPORT_ENGRAVE_STRLEN_LINES;static const char *const functions[]=TELEPORT_ENGRAVE_STRLEN_FUNCTIONS;return Strlen_(text,functions[site],lines[site]);}
void teleport_engrave_pline(const char *fmt,const char *a,const char *b,const char *c,const char *e){pline(fmt,a,b,c,e);}
void teleport_engrave_pline_i(const char *fmt,int n){pline(fmt,n);}
void teleport_engrave_You(const char *fmt,const char *a,const char *b,const char *c,const char *e){You(fmt,a,b,c,e);}
void teleport_engrave_Your(const char *fmt,const char *a){Your(fmt,a);}
void teleport_engrave_You_cant(const char *fmt,const char *a){You_cant(fmt,a);}
void teleport_engrave_You_see(const char *fmt){You_see(fmt);}
void teleport_engrave_There(const char *fmt){There(fmt);}
void teleport_engrave_pline_The(const char *fmt,const char *a){pline_The(fmt,a);}
void teleport_engrave_impossible(const char *fmt,const char *a){impossible(fmt,a);}
void teleport_engrave_impossible_ii(const char *fmt,int a,int b){impossible(fmt,a,b);}
void teleport_engrave_impossible_ip(const char *fmt,int a,const char *b){impossible(fmt,a,b);}
void teleport_engrave_sprintf(char *out,const char *fmt,const char *a,const char *b){Sprintf(out,fmt,a,b);}
void teleport_engrave_sprintf_long(char *out,const char *fmt,long n){Sprintf(out,fmt,n);}
void teleport_engrave_livelog(long mask,const char *fmt,const char *text){livelog_printf(mask,fmt,text);}
void teleport_engrave_sfo_unsigned(NHFILE *fp,unsigned *value,const char *tag){Sfo_unsigned(fp,value,tag);}
void teleport_engrave_sfi_unsigned(NHFILE *fp,unsigned *value,const char *tag){Sfi_unsigned(fp,value,tag);}
void teleport_engrave_sfo_engr(NHFILE *fp,struct engr *ep,const char *tag){Sfo_engr(fp,ep,tag);}
void teleport_engrave_sfi_engr(NHFILE *fp,struct engr *ep,const char *tag){Sfi_engr(fp,ep,tag);}
void teleport_engrave_sfo_char(NHFILE *fp,char *text,const char *tag,int n){Sfo_char(fp,text,tag,n);}
void teleport_engrave_sfi_char(NHFILE *fp,char *text,const char *tag,int n){Sfi_char(fp,text,tag,n);}
