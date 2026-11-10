#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-write-layout.h"
struct you u;
__typeof__(gu) gu;
__typeof__(gy) gy;
__typeof__(svb) svb;
__typeof__(svp) svp;
static struct permonst player;
static struct obj pen,paper,created;
static char input[BUFSZ],probe_trace_storage[65536],description[BUFSZ+32];
static char assigned_names[NUM_OBJECTS][BUFSZ];
static int options[8],random_values[128],random_length,random_index,used,freed,held;
static unsigned random_state;
static char caller[128];
void panic(const char *format,...) {abort();}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(probe_trace_storage+strlen(probe_trace_storage),sizeof probe_trace_storage-strlen(probe_trace_storage),format,ap);va_end(ap);}
static void message(const char *kind,const char *format,va_list ap){char text[BUFSZ*2];vsnprintf(text,sizeof text,format,ap);append("%s:%s;",kind,text);}
#define MESSAGE(name) void name(const char *format,...){va_list ap;va_start(ap,format);message(#name,format,ap);va_end(ap);}
MESSAGE(pline) MESSAGE(You) MESSAGE(Your) MESSAGE(You_cant) MESSAGE(There) MESSAGE(pline_The)
void impossible(const char *format,...){va_list ap;va_start(ap,format);message("impossible",format,ap);va_end(ap);}
void livelog_printf(long flags,const char *format,...){va_list ap;append("live:%ld;",flags);va_start(ap,format);message("log",format,ap);va_end(ap);}
boolean rng_log_enabled(void){return options[4];}
void rng_log_set_caller(const char *file,int line,const char *function){const char *base=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",base?base+1:file,line,function);}
static int draw(const char *kind,int bound){int v;if(bound<=0){impossible("%s(%d) attempted",kind,bound);return 0;}if(random_index<random_length)v=random_values[random_index]%bound;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)bound;}random_index++;append("%s:%d:%d@%s;",kind,bound,v,caller);return v;}
int (rn2)(int n){return draw("rn2",n);}
int (rnl)(int n){return draw("rnl",n);}
static int identity(struct obj *o){return !o?-1:o==&pen?0:o==&paper?1:o==&created?2:99;}
void dropx(struct obj *o){append("drop:%d;",identity(o));}
struct obj *getobj(const char *verb,int(*allow)(struct obj *),unsigned flags){append("getobj:%s:%u;",verb,flags);append("allow:%d:%d:%d;",allow(NULL),allow(&pen),allow(&paper));return options[0]?NULL:&paper;}
void getlin(const char *query,char *out){append("getlin:%s;",query);strcpy(out,input);}
void observe_object(struct obj *o){append("observe:%d:%d;",identity(o),o->dknown);o->dknown=1;objects[o->otyp].oc_encountered=1;}
void discover_object(int typ,boolean mark,boolean credit,boolean disclose){append("discover:%d:%d:%d:%d;",typ,mark,credit,disclose);if(mark)objects[typ].oc_name_known=1;}
void exercise(int attr,boolean good){append("exercise:%d:%d;",attr,good);}
struct obj *mksobj(int typ,boolean init,boolean art){append("make:%d:%d:%d;",typ,init,art);memset(&created,0,sizeof created);created.otyp=typ;created.oclass=objects[typ].oc_class;created.quan=9007199254740993L;created.spe=-7;return &created;}
void check_unpaid(struct obj *o){append("unpaid:%d;",identity(o));}
int bcsign(struct obj *o){append("bcsign:%d;",identity(o));return o->blessed?1:o->cursed?-1:0;}
void useup(struct obj *o){append("useup:%d;",identity(o));used++;}
void obfree(struct obj *o,struct obj *merge){append("free:%d:%d;",identity(o),identity(merge));freed++;}
void update_inventory(void){append("inventory;");}
int known_spell(short typ){append("spell:%d;",typ);return options[1];}
void wipeout_text(char *text,int count,unsigned seed){append("wipe:%s:%d:%u;",text,count,seed);if(*text)*text='?';}
struct obj *hold_another_object(struct obj *o,const char *drop,const char *dropname,const char *hold){append("hold:%d:%s:%s:%s;",identity(o),drop,dropname,hold?hold:"<null>");held++;return options[2]?NULL:o;}
const char *fingers_or_gloves(boolean gloves){append("fingers:%d;",gloves);return "fingers";}
char *Tobjnam(struct obj *o,const char *verb){append("Tobjnam:%d:%s;",identity(o),verb);return "Your marker slips";}
char *ysimple_name(struct obj *o){static char text[32];append("ysimple:%d;",identity(o));strcpy(text,"your marker");return text;}
char *an(const char *s){static char text[BUFSZ];append("an:%s;",s);snprintf(text,sizeof text,"a %s",s);return text;}
char *aobjnam(struct obj *o,const char *verb){append("aobjnam:%d:%s;",identity(o),verb);return "scroll slips";}
char *The(const char *s){static char text[BUFSZ];append("The:%s;",s);snprintf(text,sizeof text,"The %s",s);return text;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/write.c"
#define PRIVATE(name) name
#else
extern int teleport_write_test_cost(struct obj *),teleport_write_test_write_ok(struct obj *);
extern char *teleport_write_test_new_book_description(int,char *);
#define PRIVATE(name) teleport_write_test_##name
#endif
void probe_reset(unsigned seed){int i,c;monst_globals_init();objects_globals_init();memset(&u,0,sizeof u);memset(&gu,0,sizeof gu);memset(&gy,0,sizeof gy);memset(&svb,0,sizeof svb);memset(&svp,0,sizeof svp);memset(&pen,0,sizeof pen);memset(&paper,0,sizeof paper);memset(&created,0,sizeof created);memset(options,0,sizeof options);options[4]=1;memset(assigned_names,0,sizeof assigned_names);for(c=0;c<MAXOCLASSES+2;c++)svb.bases[c]=NUM_OBJECTS;for(i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=objects[i].oc_descr_idx=i;objects[i].oc_uname=NULL;objects[i].oc_encountered=0;c=objects[i].oc_class;if(i>=MAXOCLASSES && i<svb.bases[c])svb.bases[c]=i;}for(c=MAXOCLASSES;c>=0;c--)if(svb.bases[c]==NUM_OBJECTS)svb.bases[c]=svb.bases[c+1];memcpy(&player,&mons[PM_HUMAN],sizeof player);gy.youmonst.data=&player;gu.urole.mnum=PM_ARCHEOLOGIST;u.ulevel=5;strcpy(svp.plname,"Fixture Hero");pen.otyp=MAGIC_MARKER;pen.oclass=TOOL_CLASS;pen.spe=100;pen.bknown=1;paper.otyp=SCR_BLANK_PAPER;paper.oclass=SCROLL_CLASS;paper.quan=9007199254740993L;paper.dknown=paper.bknown=1;input[0]=caller[0]=probe_trace_storage[0]=0;random_state=seed;random_length=random_index=used=freed=held=0;memset(description,0xa5,sizeof description);description[0]=0;}
void probe_clear(void){probe_trace_storage[0]=0;}
const char *probe_trace(void){return probe_trace_storage;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_option(int n,int v){options[n]=v;}
void probe_properties(int nohand,int glib,int blind,int halluc,int role){player.mflags1=nohand?M1_NOHANDS:0;u.uprops[GLIB].intrinsic=glib;u.uprops[BLINDED].intrinsic=blind;u.uprops[HALLUC].intrinsic=halluc;gu.urole.mnum=role;}
void probe_property(int prop,long intrinsic,long extrinsic,long blocked){u.uprops[prop].intrinsic=intrinsic;u.uprops[prop].extrinsic=extrinsic;u.uprops[prop].blocked=blocked;}
void probe_hero(long literate,int level){u.uconduct.literate=literate;u.ulevel=level;}
long probe_literate(void){return u.uconduct.literate;}
void probe_paper(int typ,int dknown,int bknown,int blessed,int cursed){paper.otyp=typ;paper.oclass=objects[typ].oc_class;paper.dknown=dknown;paper.bknown=bknown;paper.blessed=blessed;paper.cursed=cursed;}
void probe_pen(int charges,int bknown,int blessed,int cursed){pen.spe=charges;pen.bknown=bknown;pen.blessed=blessed;pen.cursed=cursed;}
void probe_object(int typ,int known,int encountered,const char *uname){objects[typ].oc_name_known=known;objects[typ].oc_encountered=encountered;if(uname){strcpy(assigned_names[typ],uname);objects[typ].oc_uname=assigned_names[typ];}else objects[typ].oc_uname=NULL;}
void probe_descr_index(int typ,int index){objects[typ].oc_descr_idx=index;}
const char *probe_name(int typ){return OBJ_NAME(objects[typ]);}
const char *probe_descr(int typ){return OBJ_DESCR(objects[typ]);}
int probe_class(int typ){return objects[typ].oc_class;}
int probe_known(int typ){return objects[typ].oc_name_known;}
int probe_encountered(int typ){return objects[typ].oc_encountered;}
void probe_input(const char *s){strcpy(input,s);}
int probe_cost(int typ,int oclass){struct obj o;memset(&o,0,sizeof o);o.otyp=typ;o.oclass=oclass;return PRIVATE(cost)(&o);}
int probe_ok(int typ,int oclass,int nullobj){struct obj o;memset(&o,0,sizeof o);o.otyp=typ;o.oclass=oclass;return PRIVATE(write_ok)(nullobj?NULL:&o);}
int probe_write(void){return dowrite(&pen);}
int probe_description(int typ){return PRIVATE(new_book_description)(typ,description)==description;}
void *probe_snapshot_pointer(int n){switch(n){case 0:return &pen;case 1:return &paper;case 2:return &created;default:return description;}}
size_t probe_snapshot_size(int n){return n==3?sizeof description:sizeof(struct obj);}
int probe_scalar(int n){switch(n){case 0:return used;case 1:return freed;default:return held;}}
size_t probe_stack(void){return emscripten_stack_get_current();}
