/* Actual original OBJNAM against JS; foreign game dependencies controlled. */
#include "hack.h"
#include "artifact.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include "tu-objnam-layout.h"
__typeof__(gu) gu;
__typeof__(program_state) program_state;
__typeof__(iflags) iflags;
__typeof__(u) u;
__typeof__(gv) gv;
__typeof__(gd) gd;
__typeof__(svp) svp;
__typeof__(gf) gf;
__typeof__(gx) gx;
__typeof__(flags) flags;
__typeof__(gm) gm;
__typeof__(uskin) uskin;
__typeof__(uarmg) uarmg;
__typeof__(svm) svm;
__typeof__(uwep) uwep;
__typeof__(gw) gw;
__typeof__(svb) svb;
__typeof__(svl) svl;
__typeof__(svd) svd;
__typeof__(svc) svc;
__typeof__(disp) disp;
__typeof__(windowprocs) windowprocs;__typeof__(gy)gy;
const struct const_globals cg={0};
const char vowels[]="aeiouAEIOU",ynchars[]="yn";
struct obj hands_obj;
const struct c_common_strings c_common_strings={.c_something="something",.c_Never_mind="Never mind."};
const struct Gender genders[]={{.adj="male",.he="he"},{.adj="female",.he="she"},{.adj="neuter",.he="it"},{.adj="plural",.he="they"}};
static struct obj items[8];static struct oextra extras[8];static struct monst monsters[4];static struct fruit fruits[8];
static struct teleport_objnam__readobjnam_data wishdata;
static char buffers[8][4096],trace[262144],result[8192],snap[65536];
static int integers[16],opts[256];static unsigned rng=1;static void *growth;static uintptr_t returned;
static const char *const alt_words[]={"deer","orc",0};
static struct trap fixture_trap;static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long oid(const struct obj*p){return !p?-1:p==&hands_obj?-2:p>=items&&p<items+8?p-items:-3;}
static void callback(int stage){if(opts[240]==stage){opts[240]=0;append("nested:%s;",an("orange"));}if(opts[241]==stage&&!growth){opts[241]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char*fmt,...){fprintf(stderr,"OBJNAM controlled panic: %s\n",fmt);abort();}
void impossible(const char*fmt,...){char b[8192];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void pline(const char*fmt,...){char b[8192];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);callback(1);}
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file,int line,const char*fn){append("caller:%s:%d:%s;",file,line,fn);}
int (rn2)(int n){rng=rng*1664525U+1013904223U;append("rn2:%d;",n);return n?(int)(rng%(unsigned)n):0;}
int (rnd)(int n){return 1+(rn2)(n);}
boolean get_obj_location(struct obj * a0,coordxy * a1,coordxy * a2,int a3){*a1=a0->ox;*a2=a0->oy;append("location:%ld:%u;",oid(a0),a3);callback(2);return opts[12];}
void observe_object(struct obj * a0){append("observe:%ld;",oid(a0));a0->dknown=1;callback(4);}
void find_artifact(struct obj * a0){append("artifact:%ld;",oid(a0));callback(3);}
boolean permapoisoned(struct obj * a0){append("permapoisoned;");return (boolean)opts[33];}
const char * obj_pmname(struct obj * a0){return mons[a0->corpsenm>=0?a0->corpsenm:PM_NEWT].pmnames[NEUTRAL];}
void tin_details(struct obj * a0,int a1,char * a2){append("tin_details;");}
void paniclog(const char * a0,const char * a1){append("paniclog;");}
char * tshirt_text(struct obj * a0,char * a1){append("tshirt_text;");return "tshirt_text";}
char * apron_text(struct obj * a0,char * a1){append("apron_text;");return "apron_text";}
const char * candy_wrapper_text(struct obj * a0){append("candy_wrapper_text;");return "candy_wrapper_text";}
char * hawaiian_motif(struct obj * a0,char * a1){append("hawaiian_motif;");return "hawaiian_motif";}
boolean is_flammable(struct obj * a0){append("is_flammable;");return (boolean)opts[41];}
boolean is_rottable(struct obj * a0){append("is_rottable;");return (boolean)opts[42];}
const char * artifact_name(const char * a0,short * a1,boolean a2){if(opts[10]){if(a1)*a1=opts[11];return "Sting";}return 0;}
long count_contents(struct obj * a0,boolean a1,boolean a2,boolean a3,boolean a4){return opts[13];}
boolean doffing(struct obj * a0){append("doffing;");return (boolean)opts[45];}
boolean donning(struct obj * a0){append("donning;");return (boolean)opts[46];}
boolean artifact_light(struct obj * a0){append("artifact_light;");return (boolean)opts[47];}
const char * arti_light_description(struct obj * a0){return "brightly";}
struct monst * find_mid(unsigned int a0,unsigned int a1){return opts[16]?&monsters[0]:0;}
char * noit_mon_nam(struct monst * a0){append("noit_mon_nam;");return "noit_mon_nam";}
const char * mon_pmname(struct monst * a0){return a0->data->pmnames[NEUTRAL];}
long peek_timer(short a0,union any * a1){append("peek_timer;");return (long)opts[52];}
const char * body_part(int a0){return "hand";}
const char * glow_verb(int a0,boolean a1){return "glowing";}
const char * glow_color(int a0){return "blue";}
boolean is_unpaid(struct obj * a0){append("is_unpaid;");return (boolean)opts[56];}
long unpaid_cost(struct obj * a0,uchar a1){append("unpaid_cost;");return (long)opts[57];}
const char * currency(long a0){return a0==1?"zorkmid":"zorkmids";}
void record_price_quote(int a0,unsigned long a1,boolean a2){append("record_price_quote;");}
long get_cost_of_shop_item(struct obj * a0,int * a1){if(a1)*a1=17;return opts[14];}
void append_price_quote(char * a0,char ** a1,int a2){append("quote:%s:%d;",a0,a2);strcat(*a1," priced");}
boolean undiscovered_artifact(xint16 a0){append("undiscovered_artifact;");return (boolean)opts[62];}
boolean CapitalMon(const char * a0){return opts[18];}
char * shk_your(char * a0,struct obj * a1){strcpy(a0,"your ");return a0;}
const char * artiname(int a0){append("artiname;");return "artiname";}
const char * trapname(int a0,boolean a1){switch(a0){case PIT:return "pit";case BEAR_TRAP:return "bear trap";default:return "fixture trap";}}
boolean Can_fall_thru(d_level * a0){append("Can_fall_thru;");return (boolean)opts[67];}
struct trap * maketrap(coordxy a0,coordxy a1,int a2){fixture_trap.ttyp=a2;fixture_trap.tx=a0;fixture_trap.ty=a1;return &fixture_trap;}
void del_engr_at(coordxy a0,coordxy a1){append("del_engr_at;");}
const char * waterbody_name(coordxy a0,coordxy a1){return "water";}
void water_damage_chain(struct obj * a0,boolean a1){append("water_damage_chain;");}
boolean pooleffects(boolean a0){append("pooleffects;");return (boolean)opts[72];}
int fire_damage_chain(struct obj * a0,boolean a1,boolean a2,coordxy a3,coordxy a4){append("fire_damage_chain;");return (int)opts[73];}
void start_melt_ice_timeout(coordxy a0,coordxy a1,long a2){append("start_melt_ice_timeout;");}
char * ice_descr(coordxy a0,coordxy a1,char * a2){return "ice";}
const char * align_str(aligntyp a0){append("align_str;");return "align_str";}
void make_grave(coordxy a0,coordxy a1,const char * a2){append("make_grave;");}
boolean on_level(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
int isok(coordxy a0,coordxy a1){append("isok;");return (int)opts[79];}
void fix_wall_spines(coordxy a0,coordxy a1,coordxy a2,coordxy a3){append("fix_wall_spines;");}
boolean is_pool_or_lava(coordxy a0,coordxy a1){append("is_pool_or_lava;");return (boolean)opts[81];}
void count_level_features(){append("count_level_features;");}
struct trap * t_at(coordxy a0,coordxy a1){append("t_at;");return 0;}
void deltrap(struct trap * a0){append("deltrap;");}
void feel_newsym(coordxy a0,coordxy a1){append("feel_newsym;");}
boolean is_pool(coordxy a0,coordxy a1){append("is_pool;");return (boolean)opts[86];}
void set_uinwater(int a0){u.uinwater=a0;}
void docrt(){append("docrt;");}
boolean is_lava(coordxy a0,coordxy a1){append("is_lava;");return (boolean)opts[89];}
void reset_utrap(boolean a0){append("reset_utrap;");}
void recalc_block_point(coordxy a0,coordxy a1){append("recalc_block_point;");}
boolean is_ice(coordxy a0,coordxy a1){append("is_ice;");return (boolean)opts[92];}
void spot_stop_timers(coordxy a0,coordxy a1,short a2){append("spot_stop_timers;");}
void switch_terrain(){append("switch_terrain;");}
int abs(int a0){append("abs;");return (int)opts[95];}
int name_to_mon(const char * a0,int * a1){return NON_PM;}
int tin_variety_txt(char * a0,int * a1){append("tin_variety_txt;");if(a1)*a1=opts[97]?opts[98]:-1;return opts[97];}
int name_to_monplus(const char * a0,const char ** a1,int * a2){if(a1)*a1=0;if(a2)*a2=NEUTRAL;return NON_PM;}
struct obj * mksobj(int a0,boolean a1,boolean a2){items[7]=cg.zeroobj;items[7].otyp=a0;items[7].oclass=objects[a0].oc_class;items[7].quan=1;return &items[7];}
int weight(struct obj * a0){return 10;}
struct obj * mkobj(int a0,boolean a1){items[7]=cg.zeroobj;items[7].otyp=ROCK;items[7].oclass=a0;items[7].quan=1;return &items[7];}
char yn_function(const char * a0,const char * a1,char a2,boolean a3){append("yn:%s:%s:%d;",a0,a1,a2);return opts[17]?opts[17]:a2;}
void place_object(struct obj * a0,coordxy a1,coordxy a2){a0->ox=a1;a0->oy=a2;append("place:%ld:%d:%d;",oid(a0),a1,a2);}
void begin_burn(struct obj * a0,boolean a1){append("burn:%ld:%d;",oid(a0),a1);a0->lamplit=1;}
void obj_extract_self(struct obj * a0){append("extract:%ld;",oid(a0));}
int counter_were(int a0){return NON_PM;}
boolean dead_species(int a0,boolean a1){return 0;}
int genus(int a0,int a1){append("genus;");return (int)opts[108];}
void set_corpsenm(struct obj * a0,int a1){append("corpsenm:%ld:%d;",oid(a0),a1);a0->corpsenm=a1;}
int zombie_form(struct permonst * a0){return NON_PM;}
anything * obj_to_any(struct obj * a0){static anything a;a.a_obj=a0;return &a;}
boolean start_timer(long a0,short a1,short a2,union any * a3){append("start_timer;");return (boolean)opts[112];}
int can_be_hatched(int a0){return opts[15];}
void delete_contents(struct obj * a0){append("delete_contents;");}
void curse(struct obj * a0){a0->cursed=1;a0->blessed=0;}
void set_tin_variety(struct obj * a0,int a1){append("tin:%ld:%d;",oid(a0),a1);a0->spe=a1;}
const char * lookup_novel(const char * a0,int * a1){if(a1)*a1=1;return "The Colour of Magic";}
struct obj * oname(struct obj * a0,const char * a1,unsigned int a2){append("oname:%ld:%s;",oid(a0),a1);a0->oextra=&extras[7];a0->oextra->oname=(char*)a1;return a0;}
boolean is_quest_artifact(struct obj * a0){append("is_quest_artifact;");return (boolean)opts[119];}
int nartifact_exist(){append("nartifact_exist;");return (int)opts[120];}
const char * safe_oname(struct obj * a0){return a0->oextra&&a0->oextra->oname?a0->oextra->oname:"unnamed";}
void artifact_exists(struct obj * a0,const char * a1,boolean a2,unsigned int a3){append("artifact_exists:%ld:%s:%d:%u;",oid(a0),a1,a2,a3);}
void obfree(struct obj * a0,struct obj * a1){append("obfree:%ld;",oid(a0));}
unsigned int obj_nutrition(struct obj * a0){return 100;}
void consume_oeaten(struct obj * a0,int a1){append("consume_oeaten;");}
boolean hard_helmet(struct obj * a0){append("hard_helmet;");return (boolean)opts[126];}
#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/objnam.c"
_Static_assert(sizeof(struct _readobjnam_data)==sizeof(struct teleport_objnam__readobjnam_data),"OBJNAM private record size");
_Static_assert(offsetof(struct _readobjnam_data,bp)==offsetof(struct teleport_objnam__readobjnam_data,bp),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,flags)==offsetof(struct teleport_objnam__readobjnam_data,flags),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,blessed)==offsetof(struct teleport_objnam__readobjnam_data,blessed),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,doorless)==offsetof(struct teleport_objnam__readobjnam_data,doorless),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,locked)==offsetof(struct teleport_objnam__readobjnam_data,locked),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,closed)==offsetof(struct teleport_objnam__readobjnam_data,closed),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,open)==offsetof(struct teleport_objnam__readobjnam_data,open),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,broken)==offsetof(struct teleport_objnam__readobjnam_data,broken),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,trapped)==offsetof(struct teleport_objnam__readobjnam_data,trapped),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,otmp)==offsetof(struct teleport_objnam__readobjnam_data,otmp),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,cnt)==offsetof(struct teleport_objnam__readobjnam_data,cnt),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,spe)==offsetof(struct teleport_objnam__readobjnam_data,spe),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,spesgn)==offsetof(struct teleport_objnam__readobjnam_data,spesgn),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,typ)==offsetof(struct teleport_objnam__readobjnam_data,typ),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,very)==offsetof(struct teleport_objnam__readobjnam_data,very),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,rechrg)==offsetof(struct teleport_objnam__readobjnam_data,rechrg),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,uncursed)==offsetof(struct teleport_objnam__readobjnam_data,uncursed),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,iscursed)==offsetof(struct teleport_objnam__readobjnam_data,iscursed),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,ispoisoned)==offsetof(struct teleport_objnam__readobjnam_data,ispoisoned),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,isgreased)==offsetof(struct teleport_objnam__readobjnam_data,isgreased),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,eroded)==offsetof(struct teleport_objnam__readobjnam_data,eroded),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,eroded2)==offsetof(struct teleport_objnam__readobjnam_data,eroded2),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,erodeproof)==offsetof(struct teleport_objnam__readobjnam_data,erodeproof),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,halfeaten)==offsetof(struct teleport_objnam__readobjnam_data,halfeaten),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,islit)==offsetof(struct teleport_objnam__readobjnam_data,islit),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,unlabeled)==offsetof(struct teleport_objnam__readobjnam_data,unlabeled),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,ishistoric)==offsetof(struct teleport_objnam__readobjnam_data,ishistoric),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,isdiluted)==offsetof(struct teleport_objnam__readobjnam_data,isdiluted),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,unlocked)==offsetof(struct teleport_objnam__readobjnam_data,unlocked),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,real)==offsetof(struct teleport_objnam__readobjnam_data,real),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,fake)==offsetof(struct teleport_objnam__readobjnam_data,fake),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,tvariety)==offsetof(struct teleport_objnam__readobjnam_data,tvariety),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,mgend)==offsetof(struct teleport_objnam__readobjnam_data,mgend),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,mntmp)==offsetof(struct teleport_objnam__readobjnam_data,mntmp),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,contents)==offsetof(struct teleport_objnam__readobjnam_data,contents),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,oclass)==offsetof(struct teleport_objnam__readobjnam_data,oclass),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,actualn)==offsetof(struct teleport_objnam__readobjnam_data,actualn),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,dn)==offsetof(struct teleport_objnam__readobjnam_data,dn),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,un)==offsetof(struct teleport_objnam__readobjnam_data,un),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,wetness)==offsetof(struct teleport_objnam__readobjnam_data,wetness),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,gsize)==offsetof(struct teleport_objnam__readobjnam_data,gsize),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,zombify)==offsetof(struct teleport_objnam__readobjnam_data,zombify),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,origbp)==offsetof(struct teleport_objnam__readobjnam_data,origbp),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,p)==offsetof(struct teleport_objnam__readobjnam_data,p),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,name)==offsetof(struct teleport_objnam__readobjnam_data,name),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,ftype)==offsetof(struct teleport_objnam__readobjnam_data,ftype),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,globbuf)==offsetof(struct teleport_objnam__readobjnam_data,globbuf),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,fruitbuf)==offsetof(struct teleport_objnam__readobjnam_data,fruitbuf),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,tmp)==offsetof(struct teleport_objnam__readobjnam_data,tmp),"OBJNAM private record field");
_Static_assert(offsetof(struct _readobjnam_data,tinv)==offsetof(struct teleport_objnam__readobjnam_data,tinv),"OBJNAM private record field");
_Static_assert(sizeof(struct Jitem)==sizeof(struct teleport_objnam_Jitem),"OBJNAM private record size");
_Static_assert(offsetof(struct Jitem,item)==offsetof(struct teleport_objnam_Jitem,item),"OBJNAM private record field");
_Static_assert(offsetof(struct Jitem,name)==offsetof(struct teleport_objnam_Jitem,name),"OBJNAM private record field");
_Static_assert(sizeof(struct sing_plur)==sizeof(struct teleport_objnam_sing_plur),"OBJNAM private record size");
_Static_assert(offsetof(struct sing_plur,sing)==offsetof(struct teleport_objnam_sing_plur,sing),"OBJNAM private record field");
_Static_assert(offsetof(struct sing_plur,plur)==offsetof(struct teleport_objnam_sing_plur,plur),"OBJNAM private record field");
_Static_assert(sizeof(struct o_range)==sizeof(struct teleport_objnam_o_range),"OBJNAM private record size");
_Static_assert(offsetof(struct o_range,name)==offsetof(struct teleport_objnam_o_range,name),"OBJNAM private record field");
_Static_assert(offsetof(struct o_range,oclass)==offsetof(struct teleport_objnam_o_range,oclass),"OBJNAM private record field");
_Static_assert(offsetof(struct o_range,f_o_range)==offsetof(struct teleport_objnam_o_range,f_o_range),"OBJNAM private record field");
_Static_assert(offsetof(struct o_range,l_o_range)==offsetof(struct teleport_objnam_o_range,l_o_range),"OBJNAM private record field");
_Static_assert(sizeof(struct alt_spellings)==sizeof(struct teleport_objnam_alt_spellings),"OBJNAM private record size");
_Static_assert(offsetof(struct alt_spellings,sp)==offsetof(struct teleport_objnam_alt_spellings,sp),"OBJNAM private record field");
_Static_assert(offsetof(struct alt_spellings,ob)==offsetof(struct teleport_objnam_alt_spellings,ob),"OBJNAM private record field");
#else
#define _readobjnam_data teleport_objnam__readobjnam_data
#define Jitem teleport_objnam_Jitem
#define sing_plur teleport_objnam_sing_plur
#define o_range teleport_objnam_o_range
#define alt_spellings teleport_objnam_alt_spellings
extern void *teleport_objnam_storage(int);
extern int teleport_objnam_test_state(int,int,int);
extern char * teleport_objnam_test_strprepend(char *,const char *);
#define strprepend teleport_objnam_test_strprepend
extern char * teleport_objnam_test_nextobuf();
#define nextobuf teleport_objnam_test_nextobuf
extern void teleport_objnam_test_releaseobuf(char *);
#define releaseobuf teleport_objnam_test_releaseobuf
extern void teleport_objnam_test_xcalled(char *,int,const char *,const char *);
#define xcalled teleport_objnam_test_xcalled
extern char * teleport_objnam_test_xname_flags(struct obj *,unsigned int);
#define xname_flags teleport_objnam_test_xname_flags
extern char * teleport_objnam_test_minimal_xname(struct obj *);
#define minimal_xname teleport_objnam_test_minimal_xname
extern void teleport_objnam_test_add_erosion_words(struct obj *,char *);
#define add_erosion_words teleport_objnam_test_add_erosion_words
extern char * teleport_objnam_test_doname_base(struct obj *,unsigned int);
#define doname_base teleport_objnam_test_doname_base
extern boolean teleport_objnam_test_singplur_lookup(char *,char *,boolean,const char *const *);
#define singplur_lookup teleport_objnam_test_singplur_lookup
extern char * teleport_objnam_test_singplur_compound(char *);
#define singplur_compound teleport_objnam_test_singplur_compound
extern boolean teleport_objnam_test_ch_ksound(const char *);
#define ch_ksound teleport_objnam_test_ch_ksound
extern boolean teleport_objnam_test_badman(const char *,boolean);
#define badman teleport_objnam_test_badman
extern boolean teleport_objnam_test_wishymatch(const char *,const char *,boolean);
#define wishymatch teleport_objnam_test_wishymatch
extern short teleport_objnam_test_rnd_otyp_by_wpnskill(schar);
#define rnd_otyp_by_wpnskill teleport_objnam_test_rnd_otyp_by_wpnskill
extern short teleport_objnam_test_rnd_otyp_by_namedesc(const char *,char,int);
#define rnd_otyp_by_namedesc teleport_objnam_test_rnd_otyp_by_namedesc
extern void teleport_objnam_test_set_wallprop_from_str(char *);
#define set_wallprop_from_str teleport_objnam_test_set_wallprop_from_str
extern struct obj * teleport_objnam_test_wizterrainwish(struct teleport_objnam__readobjnam_data *);
#define wizterrainwish teleport_objnam_test_wizterrainwish
extern void teleport_objnam_test_dbterrainmesg(const char *,coordxy,coordxy);
#define dbterrainmesg teleport_objnam_test_dbterrainmesg
extern void teleport_objnam_test_readobjnam_init(char *,struct teleport_objnam__readobjnam_data *);
#define readobjnam_init teleport_objnam_test_readobjnam_init
extern int teleport_objnam_test_readobjnam_preparse(struct teleport_objnam__readobjnam_data *);
#define readobjnam_preparse teleport_objnam_test_readobjnam_preparse
extern void teleport_objnam_test_readobjnam_parse_charges(struct teleport_objnam__readobjnam_data *);
#define readobjnam_parse_charges teleport_objnam_test_readobjnam_parse_charges
extern int teleport_objnam_test_readobjnam_postparse1(struct teleport_objnam__readobjnam_data *);
#define readobjnam_postparse1 teleport_objnam_test_readobjnam_postparse1
extern int teleport_objnam_test_readobjnam_postparse2(struct teleport_objnam__readobjnam_data *);
#define readobjnam_postparse2 teleport_objnam_test_readobjnam_postparse2
extern int teleport_objnam_test_readobjnam_postparse3(struct teleport_objnam__readobjnam_data *);
#define readobjnam_postparse3 teleport_objnam_test_readobjnam_postparse3
#endif
unsigned probe_layout_count(void){return SIZE(objnam_layout);}
const char *probe_layout_name(unsigned i){return objnam_layout[i].name;}
size_t probe_layout_value(unsigned i){return objnam_layout[i].value;}
size_t probe_stack(void){return emscripten_stack_get_current();}
void *probe_pool(void){
#ifdef TELEPORT_REFERENCE_TU
return obufs;
#else
return teleport_objnam_storage(0);
#endif
}
const char *probe_catalogue(int i,int which){return which?OBJ_DESCR(objects[i]):OBJ_NAME(objects[i]);}
void *probe_pm(int i){return &mons[i];}void *probe_mon(int i){return &monsters[i];}void *probe_buffer(int i){return buffers[i];}void *probe_obj(int i){return &items[i];}void *probe_ints(void){return integers;}void *probe_data(void){return &wishdata;}void *probe_alt(void){return (void*)alt_words;}
const char *probe_trace(void){return trace;}const char *probe_result(void){return result;}uintptr_t probe_return(void){return returned;}
void probe_option(int i,int v){opts[i]=v;}void probe_seed(unsigned v){rng=v;}
void probe_clear(void){trace[0]=result[0]=0;returned=0;}
void probe_property(int i,long intrinsic,long extrinsic,long blocked){u.uprops[i].intrinsic=intrinsic;u.uprops[i].extrinsic=extrinsic;u.uprops[i].blocked=blocked;}
void probe_item(int i,int typ,long quantity,int spe){items[i].otyp=typ;items[i].oclass=objects[typ].oc_class;items[i].quan=quantity;items[i].spe=spe;}
void probe_bits(int i,unsigned bits){struct obj *o=&items[i];o->known=!!(bits&1);o->dknown=!!(bits&2);o->bknown=!!(bits&4);o->blessed=!!(bits&8);o->cursed=!!(bits&16);o->greased=!!(bits&32);o->rknown=!!(bits&64);o->lamplit=!!(bits&128);o->cknown=!!(bits&256);o->lknown=!!(bits&512);o->otrapped=!!(bits&1024);o->tknown=!!(bits&2048);}
void probe_name(int i,int which,const char *s){if(which){objects[items[i].otyp].oc_uname=(char*)s;}else{items[i].oextra=&extras[i];extras[i].oname=(char*)s;}}
void probe_class(int typ,int known){objects[typ].oc_name_known=known;}
void probe_form(int pm){gy.youmonst.data=&mons[pm];u.umonnum=pm;}
void probe_scalar(int i,long value){switch(i){case 13:gm.m_shot.n=value;gm.m_shot.o=items[0].otyp;gm.m_shot.i=2;break;case 14:monsters[0].m_ap_type=M_AP_OBJECT;monsters[0].mappearance=value;break;case 0:flags.debug=value;break;case 1:iflags.override_ID=value;break;case 2:flags.implicit_uncursed=value;break;case 3:u.twoweap=value;break;case 4:items[0].corpsenm=value;break;case 5:items[0].owornmask=value;break;case 6:items[0].oartifact=value;break;case 7:items[0].oeaten=value;break;case 8:items[0].oeroded=value;break;case 9:items[0].oeroded2=value;break;case 10:items[0].oerodeproof=value;break;case 11:items[0].opoisoned=value;break;case 12:program_state.gameover=value;break;}}
void probe_fruit(int i,int id,const char *name,int next){fruits[i].fid=id;strcpy(fruits[i].fname,name);fruits[i].nextf=next<0?0:&fruits[next];gf.ffruit=&fruits[0];}
uintptr_t probe_callback(int i){switch(i){case 0:return(uintptr_t)xname;case 1:return(uintptr_t)cxname;case 2:return(uintptr_t)doname;case 3:return(uintptr_t)simpleonames;case 4:return(uintptr_t)minimal_xname;default:return 0;}}
void probe_reset(void){
 objects_globals_init();monst_globals_init();for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=objects[i].oc_descr_idx=i;}for(int i=0;i<MAXOCLASSES;i++)svb.bases[i]=0;for(int i=NUM_OBJECTS-1;i>0;i--)if(objects[i].oc_class>0&&objects[i].oc_class<MAXOCLASSES)svb.bases[(unsigned char)objects[i].oc_class]=i;memset(items,0,sizeof items);memset(extras,0,sizeof extras);memset(monsters,0,sizeof monsters);memset(fruits,0,sizeof fruits);memset(&wishdata,0,sizeof wishdata);memset(opts,0,sizeof opts);memset(integers,0,sizeof integers);memset(buffers,0,sizeof buffers);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(&svl,0,sizeof svl);memset(&gf,0,sizeof gf);memset(&gx,0,sizeof gx);memset(&gd,0,sizeof gd);
 for(int y=0;y<ROWNO;y++){visrows[y]=visibility[y];for(int x=0;x<COLNO;x++)visibility[y][x]=IN_SIGHT|COULD_SEE;}gv.viz_array=visrows;if(growth){free(growth);growth=0;}for(int i=0;i<8;i++){items[i].otyp=LONG_SWORD;items[i].oclass=WEAPON_CLASS;items[i].quan=1;items[i].o_id=i+1;items[i].corpsenm=PM_NEWT;items[i].ox=10;items[i].oy=8;}monsters[0].data=&mons[PM_LONG_WORM];monsters[0].mhp=10;u.ux=10;u.uy=8;u.ulevel=10;u.umonster=u.umonnum=PM_HUMAN;u.uz.dnum=0;u.uz.dlevel=1;gy.youmonst.data=&mons[PM_HUMAN];gu.urole.mnum=PM_ARCHEOLOGIST;strcpy(svp.pl_fruit,"slice of pizza");svm.moves=100;for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;opts[12]=1;rng=1;
#ifdef TELEPORT_REFERENCE_TU
 obufidx=0;memset(obufs,0,sizeof obufs);
#else
 teleport_objnam_test_state(0,1,0);memset(teleport_objnam_storage(0),0,12*BUFSZ);
#endif
 probe_clear();}
static void append_snapshot(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(snap+strlen(snap),sizeof snap-strlen(snap),fmt,ap);va_end(ap);}
static long char_alias(const char*p){if(!p)return-1;uintptr_t q=(uintptr_t)p;for(int i=0;i<8;i++)if(q>=(uintptr_t)buffers[i]&&q<(uintptr_t)buffers[i]+4096)return i*4096+(q-(uintptr_t)buffers[i]);if(q>=(uintptr_t)wishdata.globbuf&&q<(uintptr_t)wishdata.globbuf+BUFSZ)return 100000+(q-(uintptr_t)wishdata.globbuf);if(q>=(uintptr_t)wishdata.fruitbuf&&q<(uintptr_t)wishdata.fruitbuf+BUFSZ)return 200000+(q-(uintptr_t)wishdata.fruitbuf);return-2;}
const char *probe_snapshot(void){snprintf(snap,sizeof snap,"rng%u;distant%d;xnameoff%d;wish:%d,%d,%d,%d,%d,%d,%d,%d;",rng,gd.distantname,gx.xnamep?1:0,wishdata.typ,wishdata.cnt,wishdata.spe,wishdata.oclass,wishdata.blessed,wishdata.iscursed,wishdata.eroded,wishdata.contents);for(int i=0;i<8;i++){char b[1024];snprintf(b,sizeof b,"o%d:%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%ld,%s;",i,items[i].otyp,items[i].quan,items[i].spe,items[i].known,items[i].dknown,items[i].bknown,items[i].blessed,items[i].cursed,items[i].rknown,items[i].corpsenm,items[i].lamplit,items[i].owt,items[i].owornmask,items[i].oextra&&items[i].oextra->oname?items[i].oextra->oname:"[NULL]");strcat(snap,b);}append_snapshot("d.bp:%ld:%s;",char_alias(wishdata.bp),wishdata.bp?wishdata.bp:"[NULL]");append_snapshot("d.flags:%lld;",(long long)wishdata.flags);append_snapshot("d.blessed:%lld;",(long long)wishdata.blessed);append_snapshot("d.doorless:%lld;",(long long)wishdata.doorless);append_snapshot("d.locked:%lld;",(long long)wishdata.locked);append_snapshot("d.closed:%lld;",(long long)wishdata.closed);append_snapshot("d.open:%lld;",(long long)wishdata.open);append_snapshot("d.broken:%lld;",(long long)wishdata.broken);append_snapshot("d.trapped:%lld;",(long long)wishdata.trapped);append_snapshot("d.otmp:%ld;",oid(wishdata.otmp));append_snapshot("d.cnt:%lld;",(long long)wishdata.cnt);append_snapshot("d.spe:%lld;",(long long)wishdata.spe);append_snapshot("d.spesgn:%lld;",(long long)wishdata.spesgn);append_snapshot("d.typ:%lld;",(long long)wishdata.typ);append_snapshot("d.very:%lld;",(long long)wishdata.very);append_snapshot("d.rechrg:%lld;",(long long)wishdata.rechrg);append_snapshot("d.uncursed:%lld;",(long long)wishdata.uncursed);append_snapshot("d.iscursed:%lld;",(long long)wishdata.iscursed);append_snapshot("d.ispoisoned:%lld;",(long long)wishdata.ispoisoned);append_snapshot("d.isgreased:%lld;",(long long)wishdata.isgreased);append_snapshot("d.eroded:%lld;",(long long)wishdata.eroded);append_snapshot("d.eroded2:%lld;",(long long)wishdata.eroded2);append_snapshot("d.erodeproof:%lld;",(long long)wishdata.erodeproof);append_snapshot("d.halfeaten:%lld;",(long long)wishdata.halfeaten);append_snapshot("d.islit:%lld;",(long long)wishdata.islit);append_snapshot("d.unlabeled:%lld;",(long long)wishdata.unlabeled);append_snapshot("d.ishistoric:%lld;",(long long)wishdata.ishistoric);append_snapshot("d.isdiluted:%lld;",(long long)wishdata.isdiluted);append_snapshot("d.unlocked:%lld;",(long long)wishdata.unlocked);append_snapshot("d.real:%lld;",(long long)wishdata.real);append_snapshot("d.fake:%lld;",(long long)wishdata.fake);append_snapshot("d.tvariety:%lld;",(long long)wishdata.tvariety);append_snapshot("d.mgend:%lld;",(long long)wishdata.mgend);append_snapshot("d.mntmp:%lld;",(long long)wishdata.mntmp);append_snapshot("d.contents:%lld;",(long long)wishdata.contents);append_snapshot("d.oclass:%lld;",(long long)wishdata.oclass);append_snapshot("d.actualn:%ld:%s;",char_alias(wishdata.actualn),wishdata.actualn?wishdata.actualn:"[NULL]");append_snapshot("d.dn:%ld:%s;",char_alias(wishdata.dn),wishdata.dn?wishdata.dn:"[NULL]");append_snapshot("d.un:%ld:%s;",char_alias(wishdata.un),wishdata.un?wishdata.un:"[NULL]");append_snapshot("d.wetness:%lld;",(long long)wishdata.wetness);append_snapshot("d.gsize:%lld;",(long long)wishdata.gsize);append_snapshot("d.zombify:%lld;",(long long)wishdata.zombify);append_snapshot("d.origbp:%ld:%s;",char_alias(wishdata.origbp),wishdata.origbp?wishdata.origbp:"[NULL]");append_snapshot("d.p:%ld:%s;",char_alias(wishdata.p),wishdata.p?wishdata.p:"[NULL]");append_snapshot("d.name:%ld:%s;",char_alias(wishdata.name),wishdata.name?wishdata.name:"[NULL]");append_snapshot("d.ftype:%lld;",(long long)wishdata.ftype);append_snapshot("d.globbuf:%s;",wishdata.globbuf);append_snapshot("d.fruitbuf:%s;",wishdata.fruitbuf);append_snapshot("d.tmp:%lld;",(long long)wishdata.tmp);append_snapshot("d.tinv:%lld;",(long long)wishdata.tinv);for(int i=0;i<8;i++){append_snapshot("o%d.oartifact:%lld;",i,(long long)items[i].oartifact);append_snapshot("o%d.oextra:%d;",i,!!items[i].oextra);append_snapshot("o%d.o_id:%lld;",i,(long long)items[i].o_id);append_snapshot("o%d.otyp:%lld;",i,(long long)items[i].otyp);append_snapshot("o%d.corpsenm:%lld;",i,(long long)items[i].corpsenm);append_snapshot("o%d.quan:%lld;",i,(long long)items[i].quan);append_snapshot("o%d.known:%lld;",i,(long long)items[i].known);append_snapshot("o%d.bknown:%lld;",i,(long long)items[i].bknown);append_snapshot("o%d.dknown:%lld;",i,(long long)items[i].dknown);append_snapshot("o%d.oclass:%lld;",i,(long long)items[i].oclass);append_snapshot("o%d.otrapped:%lld;",i,(long long)items[i].otrapped);append_snapshot("o%d.spe:%lld;",i,(long long)items[i].spe);append_snapshot("o%d.oeaten:%lld;",i,(long long)items[i].oeaten);append_snapshot("o%d.globby:%lld;",i,(long long)items[i].globby);append_snapshot("o%d.owt:%lld;",i,(long long)items[i].owt);append_snapshot("o%d.oeroded:%lld;",i,(long long)items[i].oeroded);append_snapshot("o%d.blessed:%lld;",i,(long long)items[i].blessed);append_snapshot("o%d.cursed:%lld;",i,(long long)items[i].cursed);append_snapshot("o%d.rknown:%lld;",i,(long long)items[i].rknown);append_snapshot("o%d.oeroded2:%lld;",i,(long long)items[i].oeroded2);append_snapshot("o%d.oerodeproof:%lld;",i,(long long)items[i].oerodeproof);append_snapshot("o%d.cknown:%lld;",i,(long long)items[i].cknown);append_snapshot("o%d.lknown:%lld;",i,(long long)items[i].lknown);append_snapshot("o%d.cobj:%ld;",i,oid(items[i].cobj));append_snapshot("o%d.tknown:%lld;",i,(long long)items[i].tknown);append_snapshot("o%d.obroken:%lld;",i,(long long)items[i].obroken);append_snapshot("o%d.olocked:%lld;",i,(long long)items[i].olocked);append_snapshot("o%d.greased:%lld;",i,(long long)items[i].greased);append_snapshot("o%d.owornmask:%lld;",i,(long long)items[i].owornmask);append_snapshot("o%d.lamplit:%lld;",i,(long long)items[i].lamplit);append_snapshot("o%d.age:%lld;",i,(long long)items[i].age);append_snapshot("o%d.recharged:%lld;",i,(long long)items[i].recharged);append_snapshot("o%d.unpaid:%lld;",i,(long long)items[i].unpaid);append_snapshot("o%d.where:%lld;",i,(long long)items[i].where);append_snapshot("o%d.no_charge:%lld;",i,(long long)items[i].no_charge);}append_snapshot("terrain:%d,%u,%u,%u,%u,%d,%d;hero:%u,%u,%u;class:%u:%s;",levl[u.ux][u.uy].typ,levl[u.ux][u.uy].flags,levl[u.ux][u.uy].horizontal,levl[u.ux][u.uy].lit,levl[u.ux][u.uy].icedpool,svl.level.flags.nfountains,svl.level.flags.nsinks,u.uinwater,u.utrap,u.utraptype,objects[items[0].otyp].oc_name_known,objects[items[0].otyp].oc_uname?objects[items[0].otyp].oc_uname:"[NULL]");return snap;}
void probe_poison(int i){memset(&items[i],0xa5,sizeof items[i]);items[i].nobj=0;memset(&items[i].v,0,sizeof items[i].v);items[i].cobj=0;items[i].o_id=0;items[i].ox=0;items[i].oy=0;items[i].otyp=0;items[i].owt=0;items[i].quan=0;items[i].spe=0;items[i].oclass=0;items[i].invlet=0;items[i].oartifact=0;items[i].where=0;items[i].timed=0;items[i].cursed=0;items[i].blessed=0;items[i].unpaid=0;items[i].no_charge=0;items[i].recharged=0;items[i].lamplit=0;items[i].known=0;items[i].dknown=0;items[i].bknown=0;items[i].rknown=0;items[i].cknown=0;items[i].lknown=0;items[i].tknown=0;items[i].nomerge=0;items[i].oeroded=0;items[i].oeroded2=0;items[i].oerodeproof=0;items[i].olocked=0;items[i].obroken=0;items[i].otrapped=0;items[i].globby=0;items[i].greased=0;items[i].in_use=0;items[i].bypass=0;items[i].pickup_prev=0;items[i].ghostly=0;items[i].how_lost=0;items[i].named_how=0;items[i].corpsenm=0;items[i].usecount=0;items[i].oeaten=0;items[i].age=0;items[i].owornmask=0;items[i].lua_ref_cnt=0;items[i].omigr_from_dnum=0;items[i].omigr_from_dlevel=0;items[i].oextra=0;items[i].otyp=LONG_SWORD;items[i].oclass=WEAPON_CLASS;items[i].quan=1;items[i].corpsenm=PM_NEWT;}
uintptr_t probe_invoke(int id,uintptr_t a0,uintptr_t a1,uintptr_t a2,uintptr_t a3,uintptr_t a4,uintptr_t a5,uintptr_t a6,uintptr_t a7){probe_clear();switch(id){
case 0:{char * r=strprepend((char *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 1:{char * r=nextobuf();returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 2:{releaseobuf((char *)a0);strcpy(result,"void");returned=0;break;}
case 3:{maybereleaseobuf((char *)a0);strcpy(result,"void");returned=0;break;}
case 4:{char * r=obj_typename((int)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 5:{char * r=simple_typename((int)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 6:{char * r=safe_typename((int)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 7:{boolean r=obj_is_pname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 8:{char * r=distant_name((struct obj *)a0,(char *(*)(struct obj *))a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 9:{char * r=fruitname((boolean)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 10:{struct fruit * r=fruit_from_indx((int)a0);returned=(uintptr_t)r;if(r)snprintf(result,sizeof result,"fruit:%d:%s",r->fid,r->fname);else strcpy(result,"[NULL]");break;}
case 11:{struct fruit * r=fruit_from_name((const char *)a0,(boolean)a1,(int *)a2);returned=(uintptr_t)r;if(r)snprintf(result,sizeof result,"fruit:%d:%s",r->fid,r->fname);else strcpy(result,"[NULL]");break;}
case 12:{reorder_fruit((boolean)a0);strcpy(result,"void");returned=0;break;}
case 13:{xcalled((char *)a0,(int)a1,(const char *)a2,(const char *)a3);strcpy(result,"void");returned=0;break;}
case 14:{char * r=xname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 15:{char * r=xname_flags((struct obj *)a0,(unsigned int)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 16:{char * r=minimal_xname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 17:{char * r=mshot_xname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 18:{boolean r=the_unique_obj((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 19:{boolean r=the_unique_pm((struct permonst *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 20:{add_erosion_words((struct obj *)a0,(char *)a1);strcpy(result,"void");returned=0;break;}
case 21:{boolean r=erosion_matters((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 22:{char * r=doname_base((struct obj *)a0,(unsigned int)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 23:{char * r=doname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 24:{char * r=doname_with_price((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 25:{char * r=doname_vague_quan((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 26:{boolean r=not_fully_identified((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 27:{char * r=corpse_xname((struct obj *)a0,(const char *)a1,(unsigned int)a2);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 28:{char * r=cxname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 29:{char * r=cxname_singular((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 30:{char * r=killer_xname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 31:{char * r=short_oname((struct obj *)a0,(char *(*)(struct obj *))a1,(char *(*)(struct obj *))a2,(unsigned int)a3);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 32:{const char * r=singular((struct obj *)a0,(char *(*)(struct obj *))a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 33:{char * r=just_an((char *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 34:{char * r=an((const char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 35:{char * r=An((const char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 36:{char * r=the((const char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 37:{char * r=The((const char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 38:{char * r=aobjnam((struct obj *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 39:{char * r=yobjnam((struct obj *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 40:{char * r=Yobjnam2((struct obj *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 41:{char * r=Tobjnam((struct obj *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 42:{char * r=Doname2((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 43:{char * r=paydoname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 44:{char * r=yname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 45:{char * r=Yname2((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 46:{char * r=ysimple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 47:{char * r=Ysimple_name2((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 48:{char * r=simpleonames((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 49:{char * r=ansimpleoname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 50:{char * r=thesimpleoname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 51:{char * r=actualoname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 52:{char * r=bare_artifactname((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 53:{char * r=otense((struct obj *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 54:{char * r=vtense((const char *)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 55:{boolean r=singplur_lookup((char *)a0,(char *)a1,(boolean)a2,(const char *const *)a3);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 56:{char * r=singplur_compound((char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 57:{char * r=makeplural((const char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 58:{char * r=makesingular((const char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 59:{boolean r=ch_ksound((const char *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 60:{boolean r=badman((const char *)a0,(boolean)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 61:{boolean r=wishymatch((const char *)a0,(const char *)a1,(boolean)a2);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 62:{short r=rnd_otyp_by_wpnskill((schar)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 63:{short r=rnd_otyp_by_namedesc((const char *)a0,(char)a1,(int)a2);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 64:{int r=shiny_obj((char)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 65:{set_wallprop_from_str((char *)a0);strcpy(result,"void");returned=0;break;}
case 66:{struct obj * r=wizterrainwish((struct _readobjnam_data *)a0);returned=(uintptr_t)r;if(r)snprintf(result,sizeof result,"obj:%ld:%d:%ld:%d",oid(r),r->otyp,r->quan,r->spe);else strcpy(result,"[NULL]");break;}
case 67:{dbterrainmesg((const char *)a0,(coordxy)a1,(coordxy)a2);strcpy(result,"void");returned=0;break;}
case 68:{readobjnam_init((char *)a0,(struct _readobjnam_data *)a1);strcpy(result,"void");returned=0;break;}
case 69:{int r=readobjnam_preparse((struct _readobjnam_data *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 70:{readobjnam_parse_charges((struct _readobjnam_data *)a0);strcpy(result,"void");returned=0;break;}
case 71:{int r=readobjnam_postparse1((struct _readobjnam_data *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 72:{int r=readobjnam_postparse2((struct _readobjnam_data *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 73:{int r=readobjnam_postparse3((struct _readobjnam_data *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 74:{struct obj * r=readobjnam((char *)a0,(struct obj *)a1);returned=(uintptr_t)r;if(r)snprintf(result,sizeof result,"obj:%ld:%d:%ld:%d",oid(r),r->otyp,r->quan,r->spe);else strcpy(result,"[NULL]");break;}
case 75:{int r=rnd_class((int)a0,(int)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%ld",(long)r);break;}
case 76:{const char * r=Japanese_item_name((int)a0,(const char *)a1);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 77:{const char * r=armor_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 78:{const char * r=suit_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 79:{const char * r=cloak_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 80:{const char * r=helm_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 81:{const char * r=gloves_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 82:{const char * r=boots_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 83:{const char * r=shield_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 84:{const char * r=shirt_simple_name((struct obj *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 85:{const char * r=mimic_obj_name((struct monst *)a0);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
case 86:{char * r=safe_qbuf((char *)a0,(const char *)a1,(const char *)a2,(struct obj *)a3,(char *(*)(struct obj *))a4,(char *(*)(struct obj *))a5,(const char *)a6);returned=(uintptr_t)r;snprintf(result,sizeof result,"%s",r?r:"[NULL]");break;}
}return returned;}
