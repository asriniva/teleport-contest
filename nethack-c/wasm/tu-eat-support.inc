/* EAT ABI only: zero storage addresses, packed fields, typed native calls. */
#include <stdint.h>
#include <assert.h>
extern const char*const hu_stat[7];
extern char teleport_eat_msgbuf[BUFSZ];
extern struct victual_info teleport_eat_zero_victual;
void*teleport_eat_storage(int i){switch(i){case 0:return(void*)hu_stat;case 1:return teleport_eat_msgbuf;case 2:return &teleport_eat_zero_victual;default:return NULL;}}
void*teleport_eat_global(int i){switch(i){case 0:return &u;case 1:return &svc;case 2:return &svm;case 3:return &svl;case 4:return &gy;case 5:return &gv;case 6:return &gm;case 7:return &gn;case 8:return &gi;case 9:return &gp;case 10:return &gu;case 11:return &svd;case 12:return &flags;case 13:return &iflags;case 14:return &disp;case 15:return mons;case 16:return objects;case 17:return (void*)genders;case 18:return (void*)obj_descr;case 19:return (void*)&cg;case 20:return &ge;case 21:return &ga;case 22:return &go;case 23:return &gc;case 24:return &gf;case 25:return &svk;default:return NULL;}}
struct obj*teleport_eat_equipment(int i){switch(i){case 0:return uwep;case 1:return uarm;case 2:return uarmg;case 3:return uarmh;case 4:return uarmf;case 5:return uarmc;case 6:return uarmu;case 7:return ublindf;case 8:return uamul;case 9:return uswapwep;case 10:return uball;case 11:return uchain;case 12:return uleft;case 13:return uright;case 14:return uquiver;default:return NULL;}}
unsigned teleport_eat_bit(int type,void*ptr,int i){switch(type){
case 0:{struct monst*o=ptr;switch(i){case 0:return o->isminion;case 1:return o->mconf;default:return 0;}}
case 1:{struct you*o=ptr;switch(i){case 0:return o->mfemale;case 1:return o->uedibility;case 2:return o->uinvulnerable;case 3:return o->usick_type;case 4:return o->uswallow;default:return 0;}}
case 2:{struct obj*o=ptr;switch(i){case 0:return o->bknown;case 1:return o->blessed;case 2:return o->cknown;case 3:return o->cursed;case 4:return o->dknown;case 5:return o->globby;case 6:return o->in_use;case 7:return o->known;case 8:return o->no_charge;case 9:return o->oeroded;case 10:return o->oerodeproof;case 11:return o->otrapped;case 12:return o->rknown;case 13:return o->unpaid;default:return 0;}}
case 3:{struct objclass*o=ptr;switch(i){case 0:return o->oc_charged;case 1:return o->oc_material;case 2:return o->oc_unique;default:return 0;}}
case 4:{struct rm*o=ptr;switch(i){case 0:return o->flags;default:return 0;}}
case 5:{struct u_have*o=ptr;switch(i){case 0:return o->amulet;default:return 0;}}
case 6:{struct victual_info*o=ptr;switch(i){case 0:return o->canchoke;case 1:return o->doreset;case 2:return o->eating;case 3:return o->fullwarn;default:return 0;}}
case 7:{struct trap*o=ptr;switch(i){case 0:return o->ttyp;case 1:return o->tseen;default:return 0;}}default:return 0;}}
void teleport_eat_set_bit(int type,void*ptr,int i,unsigned v){switch(type){
case 0:{struct monst*o=ptr;switch(i){case 0:o->isminion=v;break;case 1:o->mconf=v;break;default:break;}break;}
case 1:{struct you*o=ptr;switch(i){case 0:o->mfemale=v;break;case 1:o->uedibility=v;break;case 2:o->uinvulnerable=v;break;case 3:o->usick_type=v;break;case 4:o->uswallow=v;break;default:break;}break;}
case 2:{struct obj*o=ptr;switch(i){case 0:o->bknown=v;break;case 1:o->blessed=v;break;case 2:o->cknown=v;break;case 3:o->cursed=v;break;case 4:o->dknown=v;break;case 5:o->globby=v;break;case 6:o->in_use=v;break;case 7:o->known=v;break;case 8:o->no_charge=v;break;case 9:o->oeroded=v;break;case 10:o->oerodeproof=v;break;case 11:o->otrapped=v;break;case 12:o->rknown=v;break;case 13:o->unpaid=v;break;default:break;}break;}
case 3:{struct objclass*o=ptr;switch(i){case 0:o->oc_charged=v;break;case 1:o->oc_material=v;break;case 2:o->oc_unique=v;break;default:break;}break;}
case 4:{struct rm*o=ptr;switch(i){case 0:o->flags=v;break;default:break;}break;}
case 5:{struct u_have*o=ptr;switch(i){case 0:o->amulet=v;break;default:break;}break;}
case 6:{struct victual_info*o=ptr;switch(i){case 0:o->canchoke=v;break;case 1:o->doreset=v;break;case 2:o->eating=v;break;case 3:o->fullwarn=v;break;default:break;}break;}
case 7:{struct trap*o=ptr;switch(i){case 0:o->ttyp=v;break;case 1:o->tseen=v;break;default:break;}break;}default:break;}}
const char*teleport_eat_common(int i){switch(i){case 0:return nothing_happens;case 1:return nothing_seems_to_happen;case 2:return Something;case 3:return vision_clears;case 4:return You_can_move_again;case 5:return something;case 6:return (const char*)the_your;case 7:return ynchars;case 8:return ynqchars;default:return NULL;}}
const char*teleport_eat_color(int i){switch(i){case 0:return NH_BLACK;case 1:return NH_ORANGE;case 2:return NH_LIGHT_BLUE;case 3:return NH_AMBER;case 4:return NH_RED;case 5:return NH_GREEN;default:return NULL;}}
void*teleport_eat_hands(void){return &hands_obj;}
void teleport_eat_free(void*p){free(p);}
void teleport_eat_display(winid w,boolean b){display_nhwindow(w,b);}
winid teleport_eat_win_message(void){return WIN_MESSAGE;}
winid teleport_eat_win_map(void){return WIN_MAP;}
void teleport_eat_assert(int condition,int site){if(!condition){const char*expr=site==0?"nut > 0":"ismnum(mnum)";const char*fn=site==0?"adj_victual_nutrition":"eatcorpse";int line=site==0?344:1865;
#ifdef __APPLE__
__assert_rtn(fn,"eat.c",line,expr);
#else
__assert_fail(expr,"eat.c",line,fn);
#endif
}}
unsigned teleport_eat_Strlen(const char*s,int site){return Strlen_(s,"eatmupdate",site==0?203:204);}
char teleport_eat_y_n(const char*q){return y_n(q);}
char teleport_eat_ynq(const char*q){return ynq(q);}
extern int teleport_eat_select_tinopen(struct obj*),teleport_eat_select_eat(struct obj*),teleport_eat_select_offer(struct obj*),teleport_eat_select_tin(struct obj*);
struct obj*teleport_eat_getobj(const char*q,int cb,unsigned flags){int(*fn[])(struct obj*)={teleport_eat_select_tinopen,teleport_eat_select_eat,teleport_eat_select_offer,teleport_eat_select_tin};return getobj(q,fn[cb],flags);}
const char*teleport_eat_singular(struct obj*o){return singular(o,xname);}
char*teleport_eat_safe_qbuf(char*b,const char*p,const char*s,struct obj*o,const char*last){return safe_qbuf(b,p,s,o,doname,ansimpleoname,last);}
extern void teleport_eat_callback_garlic(struct monst*);
void teleport_eat_iter_mons(void){iter_mons(teleport_eat_callback_garlic);}
extern int teleport_eat_callback_eatmdone(void);
static int teleport_eat_after_eatmdone(void){return teleport_eat_callback_eatmdone();}
extern int teleport_eat_callback_eatfood(void);
static int teleport_eat_after_eatfood(void){return teleport_eat_callback_eatfood();}
extern int teleport_eat_callback_opentin(void);
static int teleport_eat_after_opentin(void){return teleport_eat_callback_opentin();}
extern int teleport_eat_callback_unfaint(void);
static int teleport_eat_after_unfaint(void){return teleport_eat_callback_unfaint();}
uintptr_t teleport_eat_callback_pointer(int i){switch(i){case 0:return(uintptr_t)teleport_eat_after_eatmdone;case 1:return(uintptr_t)teleport_eat_after_eatfood;case 2:return(uintptr_t)teleport_eat_after_opentin;case 3:return(uintptr_t)teleport_eat_after_unfaint;case 4:return(uintptr_t)Hear_again;case 5:return(uintptr_t)Finish_digestion;default:return 0;}}
uintptr_t teleport_eat_command_pointer(void){return(uintptr_t)donull;}
void teleport_eat_set_occupation(uintptr_t p,const char*s,cmdcount_nht n){set_occupation((int(*)(void))p,s,n);}
static const char*teleport_eat_rng_callers[]={"choke","eat_brains","maybe_cannibal","should_givit","temp_givit","givit","eye_of_newt_buzz","cpostfx","corpse_intrinsic","set_tin_variety","tin_variety","consume_tin","start_tin","Hear_again","rottenfood","eatcorpse","fprefx","bounded_increase","eataccessory","fpostfx","doeat_nonfood","doeat","gethungry","newuhs"};
#undef rn2
#undef rnd
#undef rnl
#undef d
int teleport_eat_rng(int kind,int n,int z,int line,int caller){if(rng_log_enabled())rng_log_set_caller("eat.c",line,teleport_eat_rng_callers[caller]);switch(kind){case 0:return rn2(n);case 1:return rnd(n);case 2:return rnl(n);default:return d(n,z);}}
void teleport_eat_message(int family,long category,int shape,const char*fmt,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){switch(shape){
case 0:switch(family){case 0:pline(fmt);break;case 1:pline_The(fmt);break;case 2:You(fmt);break;case 3:You_feel(fmt);break;case 4:Your(fmt);break;case 5:You_hear(fmt);break;case 6:You_cant(fmt);break;case 7:verbalize(fmt);break;case 8:impossible(fmt);break;case 9:livelog_printf(category,fmt);break;}break;
case 1:switch(family){case 0:pline(fmt,(int)(uintptr_t)a);break;case 1:pline_The(fmt,(int)(uintptr_t)a);break;case 2:You(fmt,(int)(uintptr_t)a);break;case 3:You_feel(fmt,(int)(uintptr_t)a);break;case 4:Your(fmt,(int)(uintptr_t)a);break;case 5:You_hear(fmt,(int)(uintptr_t)a);break;case 6:You_cant(fmt,(int)(uintptr_t)a);break;case 7:verbalize(fmt,(int)(uintptr_t)a);break;case 8:impossible(fmt,(int)(uintptr_t)a);break;case 9:livelog_printf(category,fmt,(int)(uintptr_t)a);break;}break;
case 2:switch(family){case 0:pline(fmt,(long)(uintptr_t)a);break;case 1:pline_The(fmt,(long)(uintptr_t)a);break;case 2:You(fmt,(long)(uintptr_t)a);break;case 3:You_feel(fmt,(long)(uintptr_t)a);break;case 4:Your(fmt,(long)(uintptr_t)a);break;case 5:You_hear(fmt,(long)(uintptr_t)a);break;case 6:You_cant(fmt,(long)(uintptr_t)a);break;case 7:verbalize(fmt,(long)(uintptr_t)a);break;case 8:impossible(fmt,(long)(uintptr_t)a);break;case 9:livelog_printf(category,fmt,(long)(uintptr_t)a);break;}break;
case 3:switch(family){case 0:pline(fmt,(const char*)(uintptr_t)a);break;case 1:pline_The(fmt,(const char*)(uintptr_t)a);break;case 2:You(fmt,(const char*)(uintptr_t)a);break;case 3:You_feel(fmt,(const char*)(uintptr_t)a);break;case 4:Your(fmt,(const char*)(uintptr_t)a);break;case 5:You_hear(fmt,(const char*)(uintptr_t)a);break;case 6:You_cant(fmt,(const char*)(uintptr_t)a);break;case 7:verbalize(fmt,(const char*)(uintptr_t)a);break;case 8:impossible(fmt,(const char*)(uintptr_t)a);break;case 9:livelog_printf(category,fmt,(const char*)(uintptr_t)a);break;}break;
case 4:switch(family){case 0:pline(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 1:pline_The(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 2:You(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 3:You_feel(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 4:Your(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 5:You_hear(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 6:You_cant(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 7:verbalize(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 8:impossible(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;case 9:livelog_printf(category,fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;}break;
case 5:switch(family){case 0:pline(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 1:pline_The(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 2:You(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 3:You_feel(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 4:Your(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 5:You_hear(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 6:You_cant(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 7:verbalize(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 8:impossible(fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;case 9:livelog_printf(category,fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;}break;
case 6:switch(family){case 0:pline(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 1:pline_The(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 2:You(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 3:You_feel(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 4:Your(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 5:You_hear(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 6:You_cant(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 7:verbalize(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 8:impossible(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;case 9:livelog_printf(category,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;}break;
case 7:switch(family){case 0:pline(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 1:pline_The(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 2:You(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 3:You_feel(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 4:Your(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 5:You_hear(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 6:You_cant(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 7:verbalize(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 8:impossible(fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;case 9:livelog_printf(category,fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;}break;
case 8:switch(family){case 0:pline(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 1:pline_The(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 2:You(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 3:You_feel(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 4:Your(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 5:You_hear(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 6:You_cant(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 7:verbalize(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 8:impossible(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;case 9:livelog_printf(category,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;}break;
case 9:switch(family){case 0:pline(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 1:pline_The(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 2:You(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 3:You_feel(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 4:Your(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 5:You_hear(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 6:You_cant(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 7:verbalize(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 8:impossible(fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;case 9:livelog_printf(category,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;}break;
default:abort();}}
static char teleport_eat_literals[TELEPORT_EAT_LITERAL_CAPACITY];
void*teleport_eat_literal_storage(void){return teleport_eat_literals;}
size_t teleport_eat_literal_capacity(void){return sizeof teleport_eat_literals;}
static const int teleport_eat_format_lines[]={2675,2679,2686,2690,2694,2698,2701,2703,2707,2717,2722,2727};
static const char*teleport_eat_format_functions[]={"edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts","edibility_prompts"};
void teleport_eat_format(int site,void*out,size_t n,int shape,const char*fmt,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){switch(shape){
case 0:if(site<0)sprintf(out,fmt);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt);break;
case 1:if(site<0)sprintf(out,fmt,(int)(uintptr_t)a);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(int)(uintptr_t)a);break;
case 2:if(site<0)sprintf(out,fmt,(long)(uintptr_t)a);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(long)(uintptr_t)a);break;
case 3:if(site<0)sprintf(out,fmt,(const char*)(uintptr_t)a);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(const char*)(uintptr_t)a);break;
case 4:if(site<0)sprintf(out,fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(int)(uintptr_t)a,(int)(uintptr_t)b);break;
case 5:if(site<0)sprintf(out,fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(long)(uintptr_t)a,(long)(uintptr_t)b);break;
case 6:if(site<0)sprintf(out,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b);break;
case 7:if(site<0)sprintf(out,fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(int)(uintptr_t)a,(int)(uintptr_t)b,(int)(uintptr_t)c);break;
case 8:if(site<0)sprintf(out,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c);break;
case 9:if(site<0)sprintf(out,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);else nh_snprintf(teleport_eat_format_functions[site],teleport_eat_format_lines[site],out,n,fmt,(const char*)(uintptr_t)a,(const char*)(uintptr_t)b,(const char*)(uintptr_t)c,(const char*)(uintptr_t)d,(int)(uintptr_t)e);break;
default:abort();}}
