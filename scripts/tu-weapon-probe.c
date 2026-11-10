#include "hack.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef free
extern void free(void*);
__typeof__(u) u;__typeof__(gy) gy;__typeof__(gp) gp;__typeof__(gu) gu;__typeof__(gi) gi;__typeof__(iflags) iflags;__typeof__(svc) svc;__typeof__(flags) flags;__typeof__(gv) gv;__typeof__(windowprocs) windowprocs;
const struct const_globals cg={.zeroany={.a_ulong=0x5a5a5a5a5a5a5a5aUL}};
const glyph_info nul_glyphinfo={0};
const struct Gender genders[]={{.his="his"},{.his="her"},{.his="its"}};
struct obj *uleft,*uright,*uwep,*uswapwep;
struct obj hands_obj;
const char ynchars[]="yn";
static struct obj items[8];static struct monst victims[2];static struct def_skill matrix[P_NUM_SKILLS+1];
static int opts[32],rng_count,rng_seed=1,free_count,pick_count,panic_status,probe_active;
static long silver_output;
static char trace[262144],snapshot[65536],output[BUFSZ];
static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void *growth;
static jmp_buf panic_capture;
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long oid(const struct obj *obj){return obj==&hands_obj?-2:obj?obj-items:-1;}
static long mid(const struct monst *mon){return mon==&gy.youmonst?-2:mon?mon-victims:-1;}
static void callback(int stage){if(opts[20]==stage){opts[20]=0;append("nested:%d;",weapon_type(NULL));}if(opts[21]==stage&&!growth){opts[21]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}if(opts[22]==stage){opts[22]=0;u.weapon_slots++;append("slot-change;");}}
void panic(const char *fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("panic:%s;",b);panic_status=1;if(!probe_active)abort();longjmp(panic_capture,1);}
void impossible(const char *fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void teleport_probe_free(void *ptr){free_count++;append("free;");free(ptr);}
void pline(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);callback(1);}
void pline_mon(struct monst *mon,const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("mon:%ld:%s;",mid(mon),b);callback(2);}
#define MESSAGE(name) void name(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#name ":%s;",b);callback(3);}
MESSAGE(You) MESSAGE(Your) MESSAGE(You_feel)
boolean rng_log_enabled(void){return (boolean)opts[0];}
void rng_log_set_caller(const char *file,int line,const char *fn){const char *p=strrchr(file,'/');append("caller:%s:%d:%s;",p?p+1:file,line,fn);}
int (rn2)(int bound){rng_seed=(int)((unsigned)rng_seed*1664525U+1013904223U);rng_count++;append("rn2:%d;",bound);return (int)((unsigned)rng_seed%(unsigned)bound);}
int (rnd)(int bound){rng_seed=(int)((unsigned)rng_seed*1664525U+1013904223U);rng_count++;append("rnd:%d;",bound);return (int)((unsigned)rng_seed%(unsigned)bound)+1;}
int (d)(int n,int sides){int i,result=0;append("dice:%d:%d;",n,sides);for(i=0;i<n;i++)result+=(rnd)(sides);return result;}
boolean handle_tip(int tip){append("tip:%d;",tip);return FALSE;}
boolean mon_hates_blessings(struct monst *mon){(void)mon;return (boolean)opts[1];}
boolean mon_hates_silver(struct monst *mon){(void)mon;return (boolean)opts[2];}
boolean is_pool(coordxy x,coordxy y){(void)x;(void)y;return (boolean)opts[3];}
int spec_abon(struct obj *obj,struct monst *mon){append("abon:%ld:%ld;",oid(obj),mid(mon));callback(4);return opts[4];}
int spec_dbon(struct obj *obj,struct monst *mon,int damage){append("dbon:%ld:%ld:%d;",oid(obj),mid(mon),damage);return opts[5];}
boolean shade_glare(struct obj *obj){(void)obj;return (boolean)opts[6];}
boolean artifact_light(struct obj *obj){return (boolean)(obj&&opts[7]);}
boolean can_touch_safely(struct monst *mon,struct obj *obj){append("touch:%ld:%ld;",mid(mon),oid(obj));callback(5);return (boolean)!opts[8];}
int touch_artifact(struct obj *obj,struct monst *mon){append("artifact:%ld:%ld;",oid(obj),mid(mon));return !opts[8];}
boolean mwelded(struct obj *obj){return (boolean)(obj&&obj->cursed&&(obj->owornmask&W_WEP));}
boolean Resists_Elem(struct monst *mon,int element){(void)mon;(void)element;return (boolean)opts[9];}
struct obj *which_armor(struct monst *mon,long mask){struct obj *obj;append("armor:%ld:%ld;",mid(mon),mask);for(obj=mon->minvent;obj;obj=obj->nobj)if(obj->owornmask&mask)return obj;return NULL;}
struct obj *m_carrying(struct monst *mon,int typ){struct obj *obj;for(obj=mon->minvent;obj;obj=obj->nobj)if(obj->otyp==typ)return obj;return NULL;}
boolean is_art(struct obj *obj,int artifact){return (boolean)(obj&&obj->oartifact==artifact);}
boolean attacktype(struct permonst *pm,int typ){(void)pm;(void)typ;return (boolean)!opts[10];}
int canseemon(struct monst *mon){(void)mon;return !opts[11];}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
void obj_extract_self(struct obj *obj){append("extract:%ld;",oid(obj));callback(6);}
boolean flooreffects(struct obj *obj,coordxy x,coordxy y,const char *verb){append("floor:%ld:%d:%d:%s;",oid(obj),x,y,verb);return (boolean)opts[12];}
void bypass_obj(struct obj *obj){append("bypass:%ld;",oid(obj));}
void place_object(struct obj *obj,coordxy x,coordxy y){append("place:%ld:%d:%d;",oid(obj),x,y);obj->where=OBJ_FLOOR;}
void stackobj(struct obj *obj){append("stack:%ld;",oid(obj));}
void begin_burn(struct obj *obj,boolean timer){append("begin:%ld:%d;",oid(obj),timer);obj->lamplit=1;callback(7);}
void end_burn(struct obj *obj,boolean timer){append("end:%ld:%d;",oid(obj),timer);obj->lamplit=0;callback(8);}
int pronoun_gender(struct monst *mon,unsigned flags_){(void)mon;(void)flags_;return opts[13]%3;}
schar acurr(int attr){append("acurr:%d;",attr);return (schar)(attr==A_STR?opts[14]:opts[15]);}
int adj_lev(struct permonst *pm){append("level:%d;",pm->pmidx);return opts[16];}
boolean undiscovered_artifact(xint16 artifact){(void)artifact;return (boolean)opts[17];}
int spell_skilltype(int typ){append("spell:%d;",typ);return opts[18];}
void skill_based_spellbook_id(void){append("books; ");callback(9);}
void update_inventory(void){append("inventory;");callback(10);}
char *makesingular(const char *text){return (char*)text;}
char *makeplural(const char *text){return (char*)text;}
char *The(const char *text){return (char*)text;}
char *the(const char *text){return (char*)text;}
char *vtense(const char *name,const char *verb){(void)name;return (char*)verb;}
char *xname(struct obj *obj){(void)obj;return "fixture weapon";}
char *doname(struct obj *obj){(void)obj;return "a fixture weapon";}
char *Yname2(struct obj *obj){(void)obj;return "Your fixture weapon";}
char *Yobjnam2(struct obj *obj,const char *verb){(void)obj;(void)verb;return "Your towel";}
char *Tobjnam(struct obj *obj,const char *verb){(void)obj;(void)verb;return "The weapon";}
char *mon_nam(struct monst *mon){(void)mon;return "the monster";}
char *Monnam(struct monst *mon){(void)mon;return "The monster";}
const char *mbodypart(struct monst *mon,int part){(void)mon;(void)part;return "hand";}
const char *arti_light_description(struct obj *obj){(void)obj;return "brightly";}
char *otense(struct obj *obj,const char *verb){(void)obj;return (char*)verb;}
char *distant_name(struct obj *obj,char *(*callback_)(struct obj*)){append("distant:%d;",callback_==doname);return callback_(obj);}
static winid create(int type){append("create:%d;",type);callback(11);return 42;}
static void start(winid win,unsigned long flags_){append("start:%d:%lu;",win,flags_);}
static void end(winid win,const char *prompt){append("endmenu:%d:%s;",win,prompt);callback(12);}
static void destroy(winid win){append("destroy:%d;",win);}
char yn_function(const char *prompt,const char *choices,char def,boolean literal){(void)literal;append("yn:%s:%s:%d;",prompt,choices,def);return opts[19]?'y':'n';}
void add_menu_heading(winid win,const char *heading){append("heading:%d:%s;",win,heading);}
void add_menu_str(winid win,const char *value){append("menu-str:%d:%s;",win,value);}
void add_menu(winid win,const glyph_info *glyph,const anything *any,char accel,char group,int attr,int color,const char *text,unsigned flags_){append("menu:%d:%d:%d:%d:%d:%d:%u:%s:%d;",win,any->a_int,accel,group,attr,color,flags_,text,glyph==&nul_glyphinfo);append("any:%lx;",any->a_ulong);callback(13);}
int select_menu(winid win,int how,menu_item **selected){append("select:%d:%d;",win,how);callback(14);if(how==PICK_ONE&&pick_count<opts[23]){*selected=malloc(sizeof **selected);memset(*selected,0,sizeof **selected);(*selected)[0].item.a_int=opts[24]+1;pick_count++;return 1;}*selected=NULL;return 0;}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../nethack-c/upstream/src/weapon.c"
#undef free
#else
extern void teleport_weapon_test_give_may_advance_msg(int skill);
#define give_may_advance_msg teleport_weapon_test_give_may_advance_msg
extern struct obj * teleport_weapon_test_oselect(struct monst *mtmp, int type);
#define oselect teleport_weapon_test_oselect
extern void teleport_weapon_test_finish_towel_change(struct obj *obj, int newspe);
#define finish_towel_change teleport_weapon_test_finish_towel_change
extern int teleport_weapon_test_slots_required(int skill);
#define slots_required teleport_weapon_test_slots_required
extern boolean teleport_weapon_test_could_advance(int skill);
#define could_advance teleport_weapon_test_could_advance
extern boolean teleport_weapon_test_peaked_skill(int skill);
#define peaked_skill teleport_weapon_test_peaked_skill
extern void teleport_weapon_test_skill_advance(int skill);
#define skill_advance teleport_weapon_test_skill_advance
extern void teleport_weapon_test_add_skills_to_menu(winid win, boolean selectable, boolean speedy);
#define add_skills_to_menu teleport_weapon_test_add_skills_to_menu
#endif
#include "tu-weapon-layout.h"
int probe_layout_count(void){return SIZE(weapon_layout);}
const char *probe_layout_name(int i){return weapon_layout[i].name;}
size_t probe_layout_value(int i){return weapon_layout[i].value;}
void probe_reset(void)
{
 int i;objects_globals_init();monst_globals_init();if(growth){free(growth);growth=NULL;}
 memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&gp,0,sizeof gp);memset(&gu,0,sizeof gu);memset(&gi,0,sizeof gi);memset(&iflags,0,sizeof iflags);memset(&svc,0,sizeof svc);memset(&flags,0,sizeof flags);memset(&gv,0,sizeof gv);
 memset(items,0,sizeof items);memset(victims,0,sizeof victims);memset(matrix,0,sizeof matrix);memset(opts,0,sizeof opts);
 for(i=0;i<ROWNO;i++){visrows[i]=visibility[i];memset(visibility[i],3,sizeof visibility[i]);}gv.viz_array=visrows;
 for(i=0;i<8;i++){items[i].otyp=DAGGER;items[i].oclass=WEAPON_CLASS;items[i].quan=1;items[i].corpsenm=NON_PM;}
 for(i=0;i<2;i++){victims[i].data=&mons[PM_HUMAN];victims[i].mx=10;victims[i].my=10;victims[i].mux=12;victims[i].muy=10;victims[i].weapon_check=NEED_HTH_WEAPON;}
 gy.youmonst.data=&mons[PM_HUMAN];u.umonnum=u.umonster=PM_HUMAN;u.ulevel=10;u.ux=u.uy=10;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urole.petnum=NON_PM;gu.urole.spelspec=SPE_FORCE_BOLT;
 windowprocs.win_create_nhwindow=create;windowprocs.win_start_menu=start;windowprocs.win_end_menu=end;windowprocs.win_destroy_nhwindow=destroy;
 uleft=uright=uwep=uswapwep=NULL;opts[14]=opts[15]=10;opts[16]=8;opts[18]=P_ATTACK_SPELL;
 trace[0]=output[0]=0;free_count=pick_count=rng_count=panic_status=0;rng_seed=1;silver_output=-123;
}
void probe_option(int index,int value){opts[index]=value;}
void probe_item(int index,int typ,int corpsenm,int where,int spe)
{items[index].otyp=(short)typ;items[index].oclass=objects[typ].oc_class;items[index].corpsenm=corpsenm;items[index].where=(xint8)where;items[index].spe=(schar)spe;}
void probe_item_field(int index,int field,long value)
{struct obj *o=&items[index];switch(field){case 0:o->quan=value;break;case 1:o->owornmask=value;break;case 2:o->owt=(unsigned)value;break;case 3:o->oartifact=(char)value;break;case 4:o->blessed=(unsigned)value;break;case 5:o->cursed=(unsigned)value;break;case 6:o->lamplit=(unsigned)value;break;case 7:o->oeroded=(unsigned)value;break;case 8:o->oeroded2=(unsigned)value;break;case 9:o->dknown=(unsigned)value;break;case 10:o->bknown=(unsigned)value;break;case 11:o->globby=(unsigned)value;break;}}
void probe_next(int index,int next){items[index].nobj=next<0?NULL:&items[next];}
void probe_inventory(int mon,int first){if(mon<0)gi.invent=first<0?NULL:&items[first];else victims[mon].minvent=first<0?NULL:&items[first];}
void probe_mon(int index,int pm,int wielded,int check,long worn){victims[index].data=&mons[pm];victims[index].mw=wielded<0?NULL:&items[wielded];victims[index].weapon_check=(xint16)check;victims[index].misc_worn_check=worn;}
void probe_position(int index,int x,int y,int tx,int ty){victims[index].mx=(coordxy)x;victims[index].my=(coordxy)y;victims[index].mux=(coordxy)tx;victims[index].muy=(coordxy)ty;}
void probe_equipment(int slot,int index){struct obj *obj=index<0?NULL:&items[index];switch(slot){case 0:uleft=obj;break;case 1:uright=obj;break;case 2:uwep=obj;break;case 3:uswapwep=obj;break;}}
void probe_hero(int level,int role,int poly,int steed,int twoweap){u.ulevel=level;gu.urole.mnum=(short)role;u.umonnum=poly<0?u.umonster:poly;u.usteed=steed?&victims[0]:NULL;u.twoweap=(boolean)twoweap;}
void probe_skill(int index,int current,int max,int practice){u.weapon_skills[index].skill=(xint16)current;u.weapon_skills[index].max_skill=(xint16)max;u.weapon_skills[index].advance=(unsigned short)practice;}
void probe_record(int index,int skill){u.skill_record[index]=(xint16)skill;}
void probe_counts(int slots,int advanced){u.weapon_slots=slots;u.skills_advanced=advanced;}
void probe_menu(int wizard_,int tabs,int picks,int skill){wizard=(boolean)wizard_;iflags.menu_tab_sep=(boolean)tabs;opts[23]=picks;opts[24]=skill;}
void probe_matrix(int index,int skill,int max){matrix[index].skill=(xint16)skill;matrix[index].skmax=(xint16)max;}
void probe_role(int pet,int spell,int pauper){gu.urole.petnum=(short)pet;gu.urole.spelspec=spell;u.uroleplay.pauper=(boolean)pauper;}
void probe_class(int typ,int field,int value){switch(field){case 0:objects[typ].oc_skill=(schar)value;break;case 1:objects[typ].oc_hitbon=(schar)value;break;case 2:objects[typ].oc_wldam=(schar)value;break;case 3:objects[typ].oc_wsdam=(schar)value;break;case 4:objects[typ].oc_material=(unsigned)value;break;case 5:objects[typ].oc_bimanual=(unsigned)value;break;}}
static const struct throw_and_return_weapon *return_record;
int probe_action(int op,int a,int b,int c,long mask)
{
 int result=0;const char *text=NULL;struct obj *obj=NULL;probe_active=1;output[0]=0;
 if(!setjmp(panic_capture))switch(op){
 case 0:give_may_advance_msg(a);break;case 1:text=weapon_descr(a<0?NULL:&items[a]);break;
 case 2:result=hitval(&items[a],&victims[0]);break;case 3:result=dmgval(&items[a],&victims[0]);break;
 case 4:result=special_dmgval(a?&victims[0]:&gy.youmonst,&victims[1],mask,b==2?&items[0].owornmask:b?&silver_output:NULL);break;
 case 5:silver_sears(NULL,&victims[1],mask);break;case 6:obj=oselect(&victims[0],a);break;
 case 7:return_record=autoreturn_weapon(&items[a]);result=return_record?1:0;break;
 case 8:obj=select_rwep(&victims[0]);break;case 9:result=monmightthrowwep(&items[a]);break;
 case 10:obj=select_hwep(&victims[0]);break;case 11:possibly_unwield(&victims[0],(boolean)a);break;
 case 12:result=mon_wield_item(&victims[0]);break;case 13:mwepgone(&victims[0]);break;
 case 14:result=abon();break;case 15:result=dbon();break;case 16:finish_towel_change(&items[a],b);break;
 case 17:wet_a_towel(&items[a],b,(boolean)c);break;case 18:dry_a_towel(&items[a],b,(boolean)c);break;
 case 19:text=skill_level_name(a,output);break;case 20:text=skill_name(a);break;case 21:result=slots_required(a);break;
 case 22:result=can_advance(a,(boolean)b);break;case 23:result=could_advance(a);break;case 24:result=peaked_skill(a);break;
 case 25:skill_advance(a);break;case 26:add_skills_to_menu(42,(boolean)a,(boolean)b);break;
 case 27:show_skills();break;case 28:result=enhance_weapon_skill();break;case 29:unrestrict_weapon_skill(a);break;
 case 30:use_skill(a,b);break;case 31:add_weapon_skill(a);break;case 32:lose_weapon_skill(a);break;
 case 33:drain_weapon_skill(a);break;case 34:result=weapon_type(a<0?NULL:&items[a]);break;case 35:result=uwep_skill_type();break;
 case 36:result=weapon_hit_bonus(a<0?NULL:&items[a]);break;case 37:result=weapon_dam_bonus(a<0?NULL:&items[a]);break;
 case 38:skill_init(matrix);break;case 39:setmnotwielded(&victims[0],a<0?NULL:&items[a]);break;
 }
 else result=-999;
 probe_active=0;if(text&&text!=output)snprintf(output,sizeof output,"%s",text);if(op==6||op==8||op==10)result=(int)oid(obj);return result;
}
const char *probe_trace(void){return trace;}
const char *probe_output(void){return output;}
void probe_clear(void){trace[0]=0;}
const char *probe_snapshot(void)
{int i;char *p=snapshot;p+=sprintf(p,"slots:%d;advanced:%d;tip:%lu;unweapon:%d;propellor:%ld;silver:%ld;rng:%d:%d;free:%d;panic:%d;items:",u.weapon_slots,u.skills_advanced,svc.context.tips,gu.unweapon,oid(gp.propellor),silver_output,rng_count,rng_seed,free_count,panic_status);
 for(i=0;i<8;i++)p+=sprintf(p,"%d/%d/%d/%ld/%u/%ld/%d/%d/%d/%d/%d/%d,",items[i].otyp,items[i].oclass,items[i].spe,items[i].quan,items[i].owt,items[i].owornmask,items[i].bknown,items[i].lamplit,items[i].blessed,items[i].cursed,items[i].oeroded,items[i].oeroded2);
 p+=sprintf(p,"mon:%ld:%d:%ld;skills:",oid(victims[0].mw),victims[0].weapon_check,victims[0].misc_worn_check);
 for(i=0;i<P_NUM_SKILLS;i++)p+=sprintf(p,"%d:%d:%u,",P_SKILL(i),P_MAX_SKILL(i),P_ADVANCE(i));p+=sprintf(p,"records:");for(i=0;i<P_SKILL_LIMIT;i++)p+=sprintf(p,"%d,",u.skill_record[i]);return snapshot;}
uintptr_t probe_pointer(int kind){return kind==0?(uintptr_t)items:kind==1?(uintptr_t)victims:kind==2?(uintptr_t)&silver_output:kind==3?(uintptr_t)output:(uintptr_t)return_record;}
int probe_arw(int field){return !return_record?-1:field==0?return_record->otyp:field==1?return_record->range:return_record->tethered;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
#ifdef TELEPORT_REFERENCE_TU
int probe_table_count(int table){switch(table){case 0:return SIZE(skill_names_indices);case 1:return SIZE(odd_skill_names);case 2:return SIZE(barehands_or_martial);case 3:return SIZE(kebabable);case 4:return SIZE(rwep);case 5:return SIZE(pwep);case 6:return SIZE(arwep);case 7:return SIZE(hwep);default:return SIZE(skill_ranges);}}
int probe_table_value(int table,int row,int field){switch(table){case 0:return skill_names_indices[row];case 3:return kebabable[row];case 4:return rwep[row];case 5:return pwep[row];case 6:return field==0?arwep[row].otyp:field==1?arwep[row].range:arwep[row].tethered;case 7:return hwep[row];case 8:return field?skill_ranges[row].last:skill_ranges[row].first;default:return 0;}}
const char *probe_table_text(int table,int row){return table==1?odd_skill_names[row]:table==2?barehands_or_martial[row]:table==8?skill_ranges[row].name:NULL;}
#else
int probe_table_count(int table){(void)table;return 0;}int probe_table_value(int table,int row,int field){(void)table;(void)row;(void)field;return 0;}const char *probe_table_text(int table,int row){(void)table;(void)row;return NULL;}
#endif
