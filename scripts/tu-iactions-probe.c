#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#ifdef free
#undef free
#endif
extern void free(void *);
struct you u;
__typeof__(gy) gy;
__typeof__(cg) cg={.zeroany={.a_ulong=0x5a5a5a5a5a5a5a5aUL}};
__typeof__(svl) svl;
__typeof__(windowprocs) windowprocs;
struct obj *uwep,*uswapwep,*uquiver,*uamul,*uleft,*uright,*ublindf,*uarms;
const glyph_info nul_glyphinfo={0};
static struct obj item,other,carried,contents;
static struct oextra extra;
static struct monst shopper;
static struct permonst player;
static char fixture_oname[64],uname[64],name_output[BUFSZ+32],call_output[BUFSZ+32],probe_trace_storage[262144];
static int options[14],menu_count,selected_freed,selection_action;
static menu_item *selection_live;
static void *callback_allocation;
static long selection_count;
static anything menu_any[128];
static char menu_letters[128],menu_text[128][BUFSZ];
static void nested_queue(void);
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(probe_trace_storage+strlen(probe_trace_storage),sizeof probe_trace_storage-strlen(probe_trace_storage),format,ap);va_end(ap);}
void panic(const char *format,...){abort();}
void teleport_probe_assert_fail(const char *expr,const char *file,int line,const char *func){fprintf(stderr,"assert:%s:%s:%d:%s\n",expr,file,line,func);abort();}
void impossible(const char *format,...){char b[BUFSZ];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("impossible:%s;",b);}
void teleport_probe_free(void *p){if(p==selection_live){append("free-selection;");selected_freed++;selection_live=NULL;}free(p);}
static winid create_window(int type){append("create:%d;",type);return 19;}
static void start_window(winid win,unsigned long behavior){append("start:%d:%lu;",win,behavior);}
static void destroy_window(winid win){append("destroy:%d;",win);}
static void end_window(winid win,const char *text){append("end:%d:%s;",win,text);}
void add_menu(winid win,const glyph_info *glyph,const anything *id,char let,char group,int attr,int color,const char *text,unsigned flags){if(menu_count>=128)abort();append("menu:%d:%d:%d:%u:%u:%d:%d:%u:%s;",win,glyph==&nul_glyphinfo,id->a_int,(unsigned char)let,(unsigned char)group,attr,color,flags,text);menu_any[menu_count]=*id;menu_letters[menu_count]=let;strcpy(menu_text[menu_count],text);menu_count++;if(options[12]){options[12]=0;nested_queue();}}
int select_menu(winid win,int how,menu_item **out){int i;append("select:%d:%d:%d;",win,how,options[4]);*out=NULL;if(options[4]>0){selection_live=malloc(options[4]*sizeof *selection_live);for(i=0;i<options[4];i++){memset(&selection_live[i],0,sizeof *selection_live);selection_live[i].item.a_int=selection_action;selection_live[i].count=selection_count;}*out=selection_live;}return options[4];}
int name_ok(struct obj *o){append("name-ok;");return options[0];}
int call_ok(struct obj *o){append("call-ok;");return options[1];}
boolean the_unique_obj(struct obj *o){append("unique;");return options[2];}
char *simpleonames(struct obj *o){append("simple:%d;",o==&item);return (char *)(OBJ_NAME(objects[o->otyp])?OBJ_NAME(objects[o->otyp]):"fixture object");}
char *cxname(struct obj *o){append("cxname;");return (char *)(OBJ_NAME(objects[o->otyp])?OBJ_NAME(objects[o->otyp]):"fixture object");}
char *makeplural(const char *s){static char b[BUFSZ];append("plural:%s;",s);snprintf(b,sizeof b,"%ss",s);return b;}
char *the(const char *s){static char b[BUFSZ];append("the:%s;",s);snprintf(b,sizeof b,"the %s",s);return b;}
char *an(const char *s){static char b[BUFSZ];append("an:%s;",s);snprintf(b,sizeof b,"a %s",s);return b;}
boolean is_edible(struct obj *o){append("edible;");return options[3]>=0?options[3]:o->oclass==FOOD_CLASS;}
const char *surface(coordxy x,coordxy y){append("surface:%d:%d;",x,y);return "floor";}
boolean check_invent_gold(const char *s){append("gold:%s;",s);return options[5];}
char *in_rooms(coordxy x,coordxy y,int type){static char b[2]={'Q',0};append("rooms:%d:%d:%d;",x,y,type);b[0]=options[13]?(char)128:'Q';if(options[13]&&!callback_allocation){callback_allocation=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!callback_allocation)abort();append("grew-in-rooms;");}return b;}
struct monst *shop_keeper(char room){append("shop:%d;",room);return options[6]?&shopper:NULL;}
int inhishop(struct monst *m){append("inshop;");return options[7];}
const char *body_part(int part){append("body:%d;",part);return part==FINGER?"finger":"hand";}
long armcat_to_wornmask(int category){append("armcat:%d;",category);return W_ARM;}
struct obj *wearmask_to_obj(long mask){append("worn:%ld;",mask);return options[8]?&other:NULL;}
const char *armor_simple_name(struct obj *o){append("armorname;");return "armor";}
boolean ia_checkfile(struct obj *o){append("checkfile;");return options[9];}
boolean undiscovered_artifact(xint16 artifact){append("undiscovered:%d;",artifact);return options[10];}
int dowield(void){return 1;}
int remarm_swapwep(void){return 2;}
int dowieldquiver(void){return 3;}
int donull(void){return 4;}
int doapply(void){return 5;}
int dip_into(void){return 6;}
int docallcmd(void){return 7;}
int dodrop(void){return 8;}
int do_reqmenu(void){return 9;}
int doeat(void){return 10;}
int doengrave(void){return 11;}
int dofire(void){return 12;}
int doorganize(void){return 13;}
int adjust_split(void){return 14;}
int dosacrifice(void){return 15;}
int dopay(void){return 16;}
int dodrink(void){return 17;}
int doread(void){return 18;}
int dorub(void){return 19;}
int dothrow(void){return 20;}
int ia_dotakeoff(void){return 21;}
int dotip(void){return 22;}
int doinvoke(void){return 23;}
int dowear(void){return 24;}
int doswapweapon(void){return 25;}
int dotwoweapon(void){return 26;}
int dozap(void){return 27;}
int dowhatis(void){return 28;}
void cmdq_add_ec(int queue,int(*function)(void)){const char *name="UNKNOWN";if(function==dowield)name="dowield";if(function==remarm_swapwep)name="remarm_swapwep";if(function==dowieldquiver)name="dowieldquiver";if(function==donull)name="donull";if(function==doapply)name="doapply";if(function==dip_into)name="dip_into";if(function==docallcmd)name="docallcmd";if(function==dodrop)name="dodrop";if(function==do_reqmenu)name="do_reqmenu";if(function==doeat)name="doeat";if(function==doengrave)name="doengrave";if(function==dofire)name="dofire";if(function==doorganize)name="doorganize";if(function==adjust_split)name="adjust_split";if(function==dosacrifice)name="dosacrifice";if(function==dopay)name="dopay";if(function==dodrink)name="dodrink";if(function==doread)name="doread";if(function==dorub)name="dorub";if(function==dothrow)name="dothrow";if(function==ia_dotakeoff)name="ia_dotakeoff";if(function==dotip)name="dotip";if(function==doinvoke)name="doinvoke";if(function==dowear)name="dowear";if(function==doswapweapon)name="doswapweapon";if(function==dotwoweapon)name="dotwoweapon";if(function==dozap)name="dozap";if(function==dowhatis)name="dowhatis";append("command:%d:%s;",queue,name);if(!strcmp(name,"UNKNOWN"))abort();}
void cmdq_add_key(int queue,char key){append("key:%d:%u;",queue,(unsigned char)key);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/iactions.c"
#undef free
#define NAMING item_naming_classification
#define IA_READING item_reading_classification
#define ADDMENU ia_addmenu
#define PUSHKEYS itemactions_pushkeys
#else
extern boolean teleport_iactions_test_naming(struct obj *,char *,char *);
extern int teleport_iactions_test_reading(struct obj *,char *);
extern void teleport_iactions_test_addmenu(winid,int,char,const char *),teleport_iactions_test_pushkeys(struct obj *,int);
#define NAMING teleport_iactions_test_naming
#define IA_READING teleport_iactions_test_reading
#define ADDMENU teleport_iactions_test_addmenu
#define PUSHKEYS teleport_iactions_test_pushkeys
#endif
#include "tu-iactions-layout.h"
static void nested_queue(void){PUSHKEYS(&other,IA_DROP_OBJ);}
void probe_reset(void){int i;if(callback_allocation)free(callback_allocation);callback_allocation=NULL;if(selection_live)free(selection_live);selection_live=NULL;objects_globals_init();monst_globals_init();memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset((void*)&windowprocs,0,sizeof windowprocs);memset(&item,0,sizeof item);memset(&other,0,sizeof other);memset(&carried,0,sizeof carried);memset(&contents,0,sizeof contents);memset(&extra,0,sizeof extra);memcpy(&player,&mons[PM_HUMAN],sizeof player);gy.youmonst.data=&player;u.ux=10;u.uy=12;item.otyp=DAGGER;item.oclass=WEAPON_CLASS;item.quan=1;item.invlet='a';other.otyp=LONG_SWORD;other.oclass=WEAPON_CLASS;other.quan=1;other.invlet='b';carried.otyp=CANDELABRUM_OF_INVOCATION;memset(options,0,sizeof options);options[0]=options[1]=GETOBJ_SUGGEST;options[3]=-1;options[9]=1;selection_action=0;selection_count=1;menu_count=selected_freed=0;memset(menu_any,0,sizeof menu_any);memset(menu_letters,0,sizeof menu_letters);memset(menu_text,0,sizeof menu_text);memset(name_output,0xa5,sizeof name_output);memset(call_output,0xa5,sizeof call_output);fixture_oname[0]=uname[0]=probe_trace_storage[0]=0;uwep=uswapwep=uquiver=uamul=uleft=uright=ublindf=uarms=NULL;for(i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=objects[i].oc_descr_idx=i;objects[i].oc_uname=NULL;}windowprocs.win_create_nhwindow=create_window;windowprocs.win_start_menu=start_window;windowprocs.win_end_menu=end_window;windowprocs.win_destroy_nhwindow=destroy_window;}
void probe_clear(void){probe_trace_storage[0]=0;menu_count=0;}
const char *probe_trace(void){return probe_trace_storage;}
void probe_item(int typ,long quantity,long worn,int known,int dknown,int lit,int unpaid,int cknown,int artifact,int spe,int invlet){item.otyp=typ;item.oclass=objects[typ].oc_class;item.quan=quantity;item.owornmask=worn;item.known=known;item.dknown=dknown;item.lamplit=lit;item.unpaid=unpaid;item.cknown=cknown;item.oartifact=artifact;item.spe=spe;item.invlet=invlet;}
void probe_class(int oclass){item.oclass=oclass;}
void probe_known(int value){objects[item.otyp].oc_name_known=value;}
void probe_option(int n,int value){options[n]=value;}
void probe_names(int named,int called){item.oextra=named?&extra:NULL;extra.oname=named>=2?fixture_oname:NULL;strcpy(fixture_oname,named==3?"Named":"");strcpy(uname,called==2?"Called":"");objects[item.otyp].oc_uname=called?uname:NULL;}
void probe_contents(int present){item.cobj=present?&contents:NULL;}
void probe_equipment(int slot,int which,int typ){struct obj **p=slot==0?&uwep:slot==1?&uswapwep:slot==2?&uquiver:slot==3?&uamul:slot==4?&uleft:slot==5?&uright:slot==6?&ublindf:&uarms;other.otyp=typ;other.oclass=objects[typ].oc_class;*p=which==0?NULL:which==1?&item:&other;}
void probe_hero(int altar,int swallowed,int twoweap,int nohands,int small,int twoattacks){levl[u.ux][u.uy].typ=altar?ALTAR:ROOM;u.uswallow=swallowed;u.twoweap=twoweap;player.mflags1=nohands?M1_NOHANDS:0;player.msize=small?MZ_TINY:MZ_HUMAN;player.mattk[0].aatyp=twoattacks?AT_WEAP:AT_CLAW;player.mattk[1].aatyp=twoattacks?AT_WEAP:AT_CLAW;player.mattk[2].aatyp=AT_NONE;}
void probe_candelabrum(int present,int candles){carried.spe=candles;options[11]=present;}
struct obj *carrying(int type){append("carrying:%d;",type);return options[11]?&carried:NULL;}
void probe_select(int count,int action,long quantity){options[4]=count;selection_action=action;selection_count=quantity;}
int probe_naming(void){return NAMING(&item,name_output,call_output);}
int probe_reading(void){return IA_READING(&item,name_output);}
void probe_add(int action,int letter,const char *text){ADDMENU(19,action,letter,text);}
void probe_push(int action){PUSHKEYS(&item,action);}
int probe_run(void){return itemactions(&item);}
int probe_menu_count(void){return menu_count;}
int probe_menu_action(int n){return menu_any[n].a_int;}
int probe_menu_letter(int n){return (unsigned char)menu_letters[n];}
const char *probe_menu_text(int n){return menu_text[n];}
void *probe_menu_any(int n){return &menu_any[n];}
size_t probe_any_size(void){return sizeof(anything);}
void *probe_output(int n){return n?call_output:name_output;}
size_t probe_output_size(void){return sizeof name_output;}
int probe_freed(void){return selected_freed;}
int probe_live(void){return selection_live!=NULL;}
const char *probe_name(int type){return OBJ_NAME(objects[type]);}
int probe_class_of(int type){return objects[type].oc_class;}
size_t probe_stack(void){return emscripten_stack_get_current();}
