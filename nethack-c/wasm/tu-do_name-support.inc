/* DO_NAME typed native fields, storage and original callback/varargs ABI only. */
#include "hack.h"
#include "artifact.h"
const void *teleport_do_name_global(int i){switch(i){case 0:return &u;case 1:return &gy;case 2:return &gi;case 3:return &gu;case 4:return &svp;case 5:return &flags;case 6:return &program_state;case 7:return &cg;case 8:return objects;case 9:return obj_descr;case 10:return mons;case 11:return genders;case 12:return &svl;case 13:return &gv;case 14:return &svd;default:return 0;}}
void *teleport_do_name_equipment(int i){return i?uswapwep:uwep;}
unsigned teleport_do_name_object_bit(struct obj *p,int i){switch(i){case 0:return p->dknown;case 1:return p->fromsink;case 2:return p->unpaid;case 3:return p->blessed;case 4:return p->cursed;case 5:return p->globby;case 6:return p->known;case 7:return p->odiluted;case 8:return p->opoisoned;default:return 0;}}
void teleport_do_name_set_object_bit(struct obj *p,int i,unsigned v){switch(i){case 0:p->dknown=v;break;case 1:p->fromsink=v;break;case 2:p->unpaid=v;break;case 3:p->blessed=v;break;case 4:p->cursed=v;break;case 5:p->globby=v;break;case 6:p->known=v;break;case 7:p->odiluted=v;break;case 8:p->opoisoned=v;break;}}
unsigned teleport_do_name_monster_bit(struct monst *p,int i){switch(i){case 0:return p->female;case 1:return p->isminion;case 2:return p->ispriest;case 3:return p->isshk;case 4:return p->mcan;case 5:return p->minvis;case 6:return p->mleashed;case 7:return p->mundetected;case 8:return p->mpeaceful;case 9:return p->msleeping;case 10:return p->mcanmove;default:return 0;}}
void teleport_do_name_set_monster_bit(struct monst *p,int i,unsigned v){switch(i){case 0:p->female=v;break;case 1:p->isminion=v;break;case 2:p->ispriest=v;break;case 3:p->isshk=v;break;case 4:p->mcan=v;break;case 5:p->minvis=v;break;case 6:p->mleashed=v;break;case 7:p->mundetected=v;break;case 8:p->mpeaceful=v;break;case 9:p->msleeping=v;break;case 10:p->mcanmove=v;break;}}
unsigned teleport_do_name_class_bit(struct objclass *p,int i){(void)i;return p->oc_name_known;}
unsigned teleport_do_name_hero_bit(int i){switch(i){case 0:return u.mfemale;case 1:return u.uswallow;case 2:return u.uundetected;default:return u.uroleplay.deaf;}}
static char teleport_do_name_buffers[5][BUFSZ],teleport_do_name_rndbuf[BUFSZ];
extern const char bogon_codes[];
#ifndef TELEPORT_REFERENCE_DO_NAME
const char bogon_codes[6]={0};
#endif
void *teleport_do_name_storage(int i){return i==0?(void*)teleport_do_name_buffers:i==1?(void*)teleport_do_name_rndbuf:(void*)bogon_codes;}
static char teleport_do_name_literals[TELEPORT_DO_NAME_LITERAL_CAPACITY+sizeof BOGUSMONFILE];
void *teleport_do_name_literal_storage(void){return teleport_do_name_literals;}
size_t teleport_do_name_literal_capacity(void){return sizeof teleport_do_name_literals;}
void teleport_do_name_free(void *p){free(p);}
int teleport_do_name_win_message(void){return WIN_MESSAGE;}
const char *teleport_do_name_common_string(int i){(void)i;return Never_mind;}
const glyph_info *teleport_do_name_nul_glyphinfo(void){return &nul_glyphinfo;}
const char *teleport_do_name_object_color(int i){return c_obj_colors[i];}
winid teleport_do_name_create(int type){return create_nhwindow(type);}
void teleport_do_name_start(winid win,unsigned long flags_){start_menu(win,flags_);}
void teleport_do_name_end(winid win,const char *prompt){end_menu(win,prompt);}
void teleport_do_name_display(winid win,boolean blocking){display_nhwindow(win,blocking);}
void teleport_do_name_destroy(winid win){destroy_nhwindow(win);}
void teleport_do_name_getlin(const char *prompt,char *out){getlin(prompt,out);}
struct obj *teleport_do_name_getobj(const char *prompt,int which,unsigned flags_){return getobj(prompt,which?call_ok:name_ok,flags_);}
extern char *teleport_do_name_callback_docall_xname(struct obj *);
static char *teleport_do_name_name_trampoline(struct obj *p){return teleport_do_name_callback_docall_xname(p);}
char *teleport_do_name_safe_qbuf(char *out,const char *prefix,const char *suffix,struct obj *obj,int which,const char *last){return safe_qbuf(out,prefix,suffix,obj,which?teleport_do_name_name_trampoline:xname,simpleonames,last);}
char *teleport_do_name_random_text(const char *file,char *out,unsigned pad){return get_rnd_text(file,out,rn2_on_display_rng,pad);}
int teleport_do_name_rng(int bound,int line,const char *caller){if(rng_log_enabled())rng_log_set_caller("do_name.c",line,caller);return (rn2)(bound);}
void teleport_do_name_pline(const char *fmt,const char *a,const char *b,const char *c,const char *e){pline(fmt,a,b,c,e);}
void teleport_do_name_You(const char *fmt,const char *a,const char *b,const char *c){You(fmt,a,b,c);}
void teleport_do_name_There(const char *fmt,const char *a){There(fmt,a);}
void teleport_do_name_verbalize(const char *fmt,const char *a,const char *b){verbalize(fmt,a,b);}
void teleport_do_name_impossible(const char *fmt,int a,int b){impossible(fmt,a,b);}
int teleport_do_name_sprintf_pp(char *out,const char *fmt,const char *a,const char *b){return sprintf(out,fmt,a,b);}
int teleport_do_name_sprintf_pii(char *out,const char *fmt,const char *a,int x,int y){return sprintf(out,fmt,a,x,y);}
int teleport_do_name_sprintf_ppii(char *out,const char *fmt,const char *a,const char *b,int x,int y){return sprintf(out,fmt,a,b,x,y);}
void teleport_do_name_livelog(long mask,const char *fmt,const char *a,const char *b){livelog_printf(mask,fmt,a,b);}
void teleport_do_name_assert(void){__assert_fail(TELEPORT_DO_NAME_ASSERT_CONDITION,"do_name.c",TELEPORT_DO_NAME_ASSERT_LINE,TELEPORT_DO_NAME_ASSERT_FUNCTION);}
