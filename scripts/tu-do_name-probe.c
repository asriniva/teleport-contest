#include "hack.h"
#include "artifact.h"
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
/* Observe public naming data before any source naming entrypoint runs. */
extern const char bogon_codes[];
static unsigned char startup_bogon_codes[6];
__attribute__((constructor)) static void capture_startup_bogon_codes(void)
{
    memcpy(startup_bogon_codes, bogon_codes, sizeof startup_bogon_codes);
}
int probe_startup_bogon(int index) { return startup_bogon_codes[index]; }
__typeof__(u) u;__typeof__(gy) gy;__typeof__(gi) gi;__typeof__(gu) gu;__typeof__(svp) svp;__typeof__(flags) flags;__typeof__(program_state) program_state;__typeof__(svl) svl;__typeof__(gv) gv;__typeof__(svd) svd;__typeof__(iflags) iflags;
__typeof__(windowprocs) windowprocs;
struct obj *uwep,*uswapwep;winid WIN_MESSAGE=1;
const struct const_globals cg={0};
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind."};
const glyph_info nul_glyphinfo={0};
const struct Gender genders[]={{.he="he",.him="him",.his="his"},{.he="she",.him="her",.his="her"},{.he="it",.him="it",.his="its"},{.he="they",.him="them",.his="their"}};
const char *c_obj_colors[]={"black","red","green","brown","blue","magenta","cyan","gray","no color","orange","bright green","yellow","bright blue","bright magenta","bright cyan","white"};
static struct monst monsters[3];static struct obj items[3];
static int opts[64],seed=1;static void *growth;static char trace[65536],result[16384],snap[16384],buffers[8][BUFSZ],input[BUFSZ],randomtext[BUFSZ],rogueopts[BUFSZ];static union any menuany;
static seenV visibility[ROWNO][COLNO],*visrows[ROWNO];static struct _cmd_queue queued;
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long mid(const struct monst *p){return !p?-1:p==&gy.youmonst?-2:p>=monsters&&p<monsters+3?p-monsters:-3;}
static long oid(const struct obj *p){return !p?-1:p>=items&&p<items+3?p-items:-3;}
static void callback(int stage){if(opts[50]==stage){opts[50]=0;append("nested:%d;",name_ok(&items[0]));}if(opts[51]==stage&&!growth){opts[51]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char *fmt,...){(void)fmt;abort();}
void impossible(const char *fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
#define MSG(fn,stage) void fn(const char *fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#fn ":%s;",b);callback(stage);}
MSG(pline,1) MSG(You,2) MSG(There,3) MSG(verbalize,4)
void livelog_printf(long mask,const char *fmt,...){char b[4096];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("livelog:%ld:%s;",mask,b);callback(5);}
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file,int line,const char *fn){const char *p=strrchr(file,'/');append("caller:%s:%d:%s;",p?p+1:file,line,fn);}
int (rn2)(int n){seed=(int)((unsigned)seed*1664525U+1013904223U);append("rn2:%d;",n);return n?(unsigned)seed%(unsigned)n:0;}
int (rnd)(int n){return 1+(rn2)(n);}
int rn2_on_display_rng(int n){seed=(int)((unsigned)seed*1664525U+1013904223U);append("display:%d;",n);return n?(unsigned)seed%(unsigned)n:0;}
int rnd_on_display_rng(int n){return 1+rn2_on_display_rng(n);}
struct mextra *newmextra(void){struct mextra *p=malloc(sizeof *p);memset(p,0,sizeof *p);callback(6);return p;}
struct oextra *newoextra(void){struct oextra *p=malloc(sizeof *p);memset(p,0,sizeof *p);callback(6);return p;}
void getlin(const char *p,char *out){append("getlin:%s;",p);strcpy(out,input);callback(7);}
struct obj *getobj(const char *p,int(*fn)(struct obj*),unsigned f){append("getobj:%s:%u:%d:%d;",p,f,fn(NULL),fn(&items[0]));callback(8);return opts[5]<0?NULL:&items[opts[5]%3];}
char *safe_qbuf(char *out,const char *prefix,const char *suffix,struct obj *o,char*(*fn)(struct obj*),char*(*fn2)(struct obj*),const char *last){char pre[BUFSZ],name[BUFSZ];strcpy(pre,prefix?prefix:"");strcpy(name,fn(o));append("qbuf:%s:%s:%s:%s;",pre,name,fn2(o),last);snprintf(out,QBUFSZ,"%s%s%s",pre,name,suffix?suffix:"");callback(9);return out;}
char *get_rnd_text(const char *file,char *out,int(*rng)(int),unsigned pad){append("random:%s:%u:%d;",file,pad,rng(17));strcpy(out,randomtext);callback(10);return out;}
char * The(const char * a0){return (char*)a0;}
char * Ysimple_name2(struct obj * a0){return "Item";}
void alter_cost(struct obj * a0,long a1){append("cost:%ld:%ld;",oid(a0),a1);}
char * an(const char * a0){return (char*)a0;}
char * ansimpleoname(struct obj * a0){return "an item";}
void artifact_exists(struct obj * a0,const char * a1,boolean a2,unsigned a3){append("artifact:%ld:%s:%d:%u;",oid(a0),a1,a2,a3);if(opts[14])a0->oartifact=ART_STING;callback(12);}
const char * artifact_name(const char * a0,short * a1,boolean a2){if(opts[10]){*a1=opts[11];return "Sting";}return NULL;}
char * bare_artifactname(struct obj * a0){return "Sting";}
const char * beautiful(void){return "beautiful";}
const char * body_part(int a0){return "hand";}
int canseemon(struct monst * a0){return opts[1];}
struct obj * carrying(int a0){return opts[18]?&items[1]:NULL;}
void cmdq_clear(int a0){append("cmdclear:%d;",a0);}
struct _cmd_queue * cmdq_pop(void){if(!opts[19])return NULL;opts[19]=0;struct _cmd_queue *p=malloc(sizeof *p);*p=queued;return p;}
void dealloc_obj(struct obj * a0){append("dealloc:%ld;",oid(a0));}
void discover_object(int a0,boolean a1,boolean a2,boolean a3){append("discover:%d:%d:%d:%d;",a0,a1,a2,a3);}
int donamelevel(void){append("levelname;");return 0;}
boolean exist_artifact(int a0,const char * a1){return opts[13];}
void flush_screen(int a0){append("flush:%d;",a0);}
int getpos(coord * a0,boolean a1,const char * a2){append("getpos:%s;",a2);a0->x=opts[6];a0->y=opts[7];callback(13);return opts[8];}
int glyph_at(coordxy a0,coordxy a1){return opts[20];}
int isok(coordxy a0,coordxy a1){return a0>0&&a0<COLNO&&a1>=0&&a1<ROWNO;}
char * just_an(char * a0,const char * a1){strcpy(a0,"a");return a0;}
char * makeplural(const char * a0){return (char*)a0;}
char * nh_getenv(const char * a0){return !strcmp(a0,"ROGUEOPTS")&&opts[17]?rogueopts:NULL;}
boolean on_level(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
char * priestname(struct monst * a0,int a1,boolean a2,char * a3){append("priest:%ld:%d:%d:%ld:%u;",mid(a0),a1,a2,u.uprops[HALLUC_RES].extrinsic,a0->minvis);strcpy(a3,a1==ARTICLE_NONE?"priest of Test":"the priest of Test");callback(14);return a3;}
int pronoun_gender(struct monst * a0,unsigned a1){return opts[16]>=0?opts[16]:a0->female;}
const char * rank_of(int a0,short a1,boolean a2){return a2?"Student":"Novice";}
void rename_disco(void){append("renamedisco;");}
boolean restrict_name(struct obj * a0,const char * a1){return opts[12];}
int see_with_infrared(struct monst * a0){return opts[3];}
int sensemon(struct monst * a0){return opts[2];}
void set_artifact_intrinsic(struct obj * a0,boolean a1,long a2){append("intrinsic:%ld:%d:%ld;",oid(a0),a1,a2);}
char * shkname(struct monst * a0){return "Asidonhopo";}
char * simpleonames(struct obj * a0){return "item";}
void undiscover_object(int a0){append("undiscover:%d;",a0);}
boolean undiscovered_artifact(xint16 a0){return opts[15];}
void untwoweapon(void){append("untwoweap;");}
void update_inventory(void){append("inventory;");callback(15);}
char * vtense(const char * a0,const char * a1){return a1;}
void wipeout_text(char * a0,int a1,unsigned a2){append("wipe:%d:%u;",a1,a2);if(*a0)*a0=63;}
char * xname(struct obj * a0){static char b[BUFSZ];snprintf(b,sizeof b,"item%d",a0->otyp);append("xname:%d:%ld:%d:%d:%d:%d:%u:%d;",a0->otyp,a0->quan,a0->blessed,a0->cursed,a0->known,a0->spe,a0->owt,!!a0->oextra);callback(11);return b;}
static winid fixture_create(int type){append("create:%d;",type);return 4;}
static void fixture_start(winid win,unsigned long flags_){append("start:%d:%lu;",win,flags_);}
static void fixture_end(winid win,const char *prompt){append("end:%d:%s;",win,prompt);}
static void fixture_display(winid win,boolean blocking){append("display:%d:%d;",win,blocking);}
static void fixture_destroy(winid win){append("destroy:%d;",win);}
void add_menu(winid win,const glyph_info *g,const union any *any,char ch,char group,int attr,int color,const char *text,unsigned f){append("menu:%d:%d:%d:%d:%d:%d:%s:%u;",win,any->a_char,ch,group,attr,color,text,f);}
int select_menu(winid win,int how,menu_item **out){append("select:%d:%d;",win,how);callback(16);if(opts[21]<=0)return opts[21];*out=malloc(sizeof **out);memset(*out,0,sizeof **out);(*out)->item.a_char=opts[22];return 1;}
boolean object_from_map(int glyph,coordxy x,coordxy y,struct obj **out){append("frommap:%d:%d:%d;",glyph,x,y);*out=opts[23]<0?NULL:&items[opts[23]%3];callback(17);return opts[24];}
#ifdef TELEPORT_REFERENCE_TU
#include "../nethack-c/upstream/src/do_name.c"
#else
extern void teleport_do_name_test_do_mgivenname(void);
#define do_mgivenname teleport_do_name_test_do_mgivenname
extern void teleport_do_name_test_namefloorobj(void);
#define namefloorobj teleport_do_name_test_namefloorobj
extern void teleport_do_name_test_do_oname(struct obj *obj);
#define do_oname teleport_do_name_test_do_oname
extern char * teleport_do_name_test_docall_xname(struct obj *obj);
#define docall_xname teleport_do_name_test_docall_xname
extern boolean teleport_do_name_test_alreadynamed(struct monst *mtmp, char *monnambuf, char *usrbuf);
#define alreadynamed teleport_do_name_test_alreadynamed
extern char * teleport_do_name_test_nextmbuf(void);
#define nextmbuf teleport_do_name_test_nextmbuf
extern char * teleport_do_name_test_name_from_player(
    char *outbuf,       
    const char *prompt,
    const char *defres);
#define name_from_player teleport_do_name_test_name_from_player
#endif
#include "tu-do_name-layout.h"
unsigned probe_layout_count(void){return SIZE(do_name_layout);}const char *probe_layout_name(unsigned i){return do_name_layout[i].name;}size_t probe_layout_value(unsigned i){return do_name_layout[i].value;}
unsigned probe_string_count(void){return 1;}const char *probe_string_name(unsigned i){(void)i;return "BOGUSMONFILE";}const char *probe_string_value(unsigned i){(void)i;return BOGUSMONFILE;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
void probe_option(int i,int v){opts[i]=v;}
void probe_seed(int v){seed=v;}
const char *probe_trace(void){return trace;}const char *probe_result(void){return result;}
void probe_clear(void){trace[0]=result[0]=0;}
void probe_input(const char *s){strcpy(input,s);}void probe_random(const char *s){strcpy(randomtext,s);}void probe_rogue(const char *s){strcpy(rogueopts,s);}
void *probe_mon(int i){return i<0?NULL:i==3?&gy.youmonst:&monsters[i];}void *probe_obj(int i){return i<0?NULL:&items[i];}void *probe_pm(int i){return i<0?NULL:&mons[i];}void *probe_buffer(int i){return buffers[i];}
void *probe_name(int kind){return kind?ONAME(&items[0]):MGIVENNAME(&monsters[0]);}
static int integers[4];void *probe_int(int i,int v){integers[i]=v;return &integers[i];}int probe_intvalue(int i){return integers[i];}
void probe_reset(void){int i,j;windowprocs.win_create_nhwindow=fixture_create;windowprocs.win_start_menu=fixture_start;windowprocs.win_end_menu=fixture_end;windowprocs.win_display_nhwindow=fixture_display;windowprocs.win_destroy_nhwindow=fixture_destroy;for(i=0;i<3;i++){if(monsters[i].mextra){free_mgivenname(&monsters[i]);free(monsters[i].mextra);}if(items[i].oextra){free_oname(&items[i]);free(items[i].oextra);}}for(i=0;i<NUM_OBJECTS;i++)if(objects[i].oc_uname){free(objects[i].oc_uname);objects[i].oc_uname=NULL;}if(growth){free(growth);growth=NULL;}memset(&u,0,sizeof u);memset(monsters,0,sizeof monsters);memset(items,0,sizeof items);memset(opts,0,sizeof opts);memset(&svl,0,sizeof svl);memset(&flags,0,sizeof flags);memset(&program_state,0,sizeof program_state);memset(buffers,0,sizeof buffers);opts[1]=1;opts[5]=0;opts[6]=10;opts[7]=10;opts[16]=-1;seed=1;objects_globals_init();monst_globals_init();u.ux=10;u.uy=10;u.umonster=u.umonnum=PM_HUMAN;u.uz.dnum=0;u.uz.dlevel=1;astral_level.dnum=5;astral_level.dlevel=1;strcpy(svp.plname,"Player");gu.urole.name.m="Wizard";gu.urole.name.f="Witch";gu.urole.mnum=PM_WIZARD;for(i=0;i<3;i++){monsters[i].data=&mons[PM_HUMAN];monsters[i].cham=NON_PM;monsters[i].m_id=i+1;monsters[i].mx=10+i;monsters[i].my=10;monsters[i].mcanmove=1;monsters[i].m_lev=5;svl.level.monsters[10+i][10]=&monsters[i];items[i].otyp=DAGGER;items[i].oclass=WEAPON_CLASS;items[i].quan=1L;items[i].dknown=1;items[i].where=OBJ_INVENT;}gi.invent=uwep=&items[0];uswapwep=&items[1];gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mcanmove=1;for(i=0;i<ROWNO;i++){visrows[i]=visibility[i];for(j=0;j<COLNO;j++)visibility[i][j]=IN_SIGHT;}gv.viz_array=visrows;strcpy(input,"Alice");strcpy(randomtext,"-Bogus Person");strcpy(rogueopts,"name=Rogue,fruit=apple");trace[0]=result[0]=0;}
void probe_monset(int i,int pm,int field,long value){struct monst *m=i==3?&gy.youmonst:&monsters[i];if(pm>=0)m->data=&mons[pm];switch(field){case 0:m->female=value;break;case 1:m->mtame=value;break;case 2:m->minvis=value;break;case 3:m->ispriest=value;break;case 4:m->isminion=value;break;case 5:m->isshk=value;break;case 6:m->mcan=value;break;case 7:m->mleashed=value;break;case 8:m->mundetected=value;break;case 9:m->mpeaceful=value;break;case 10:m->msleeping=value;break;case 11:m->mcanmove=value;break;case 12:m->m_ap_type=value;break;case 13:m->mappearance=value;break;case 14:m->misc_worn_check=value;break;case 15:m->m_id=value;break;case 16:m->m_lev=value;break;case 17:m->cham=value;break;case 18:m->mx=value;break;}}
void probe_item(int i,int typ,long quan,int field,int value){struct obj *o=&items[i];o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=quan;switch(field){case 0:o->dknown=value;break;case 1:o->fromsink=value;break;case 2:o->unpaid=value;break;case 3:o->blessed=value;break;case 4:o->cursed=value;break;case 5:o->globby=value;break;case 6:o->known=value;break;case 7:o->odiluted=value;break;case 8:o->opoisoned=value;break;case 9:o->spe=value;break;case 10:o->corpsenm=value;break;case 11:o->where=value;break;case 12:o->oartifact=value;break;}}
void probe_property(int i,long a,long b,long c){u.uprops[i].intrinsic=a;u.uprops[i].extrinsic=b;u.uprops[i].blocked=c;}
void probe_global(int i,int v){switch(i){case 0:flags.female=v;break;case 1:flags.lootabc=v;break;case 2:program_state.gameover=v;break;case 3:u.uswallow=v;u.ustuck=v?&monsters[0]:NULL;break;case 4:u.usteed=v?&monsters[0]:NULL;break;case 5:u.uundetected=v;break;case 6:gi.invent=v?&items[0]:NULL;break;case 7:queued.typ=CMDQ_KEY;queued.key=v;opts[19]=1;break;case 8:objects[items[0].otyp].oc_name_known=v;break;case 9:u.umonnum=v;break;case 10:u.mfemale=v;break;case 11:u.uz.dnum=v;break;}}
uintptr_t probe_invoke(int op,uintptr_t a0,uintptr_t a1,uintptr_t a2,uintptr_t a3,uintptr_t a4){switch(op){
case 0:{char * r=nextmbuf();snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 1:{new_mgivenname((struct monst *)a0,(int)a1);strcpy(result,"void");return 0;}
case 2:{free_mgivenname((struct monst *)a0);strcpy(result,"void");return 0;}
case 3:{new_oname((struct obj *)a0,(int)a1);strcpy(result,"void");return 0;}
case 4:{free_oname((struct obj *)a0);strcpy(result,"void");return 0;}
case 5:{const char * r=safe_oname((struct obj *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 6:{char * r=name_from_player((char *)a0,(const char *)a1,(const char *)a2);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 7:{struct monst * r=christen_monst((struct monst *)a0,(const char *)a1);snprintf(result,sizeof result,"mon:%ld",mid(r));return (uintptr_t)r;}
case 8:{boolean r=alreadynamed((struct monst *)a0,(char *)a1,(char *)a2);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 9:{do_mgivenname();strcpy(result,"void");return 0;}
case 10:{do_oname((struct obj *)a0);strcpy(result,"void");return 0;}
case 11:{struct obj * r=oname((struct obj *)a0,(const char *)a1,(unsigned)a2);snprintf(result,sizeof result,"obj:%ld",oid(r));return (uintptr_t)r;}
case 12:{boolean r=objtyp_is_callable((int)a0);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 13:{int r=name_ok((struct obj *)a0);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 14:{int r=call_ok((struct obj *)a0);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 15:{int r=docallcmd();snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 16:{char * r=docall_xname((struct obj *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 17:{docall((struct obj *)a0);strcpy(result,"void");return 0;}
case 18:{namefloorobj();strcpy(result,"void");return 0;}
case 19:{const char * r=rndghostname();snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 20:{char * r=x_monnam((struct monst *)a0,(int)a1,(const char *)a2,(int)a3,(boolean)a4);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 21:{char * r=l_monnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 22:{char * r=mon_nam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 23:{char * r=noit_mon_nam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 24:{char * r=some_mon_nam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 25:{char * r=Monnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 26:{char * r=noit_Monnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 27:{char * r=Some_Monnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 28:{char * r=noname_monnam((struct monst *)a0,(int)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 29:{char * r=m_monnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 30:{char * r=y_monnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 31:{char * r=YMonnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 32:{char * r=Adjmonnam((struct monst *)a0,(const char *)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 33:{char * r=a_monnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 34:{char * r=Amonnam((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 35:{char * r=distant_monnam((struct monst *)a0,(int)a1,(char *)a2);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 36:{char * r=mon_nam_too((struct monst *)a0,(struct monst *)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 37:{char * r=monverbself((struct monst *)a0,(char *)a1,(const char *)a2,(const char *)a3);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 38:{char * r=minimal_monnam((struct monst *)a0,(boolean)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 39:{int r=Mgender((struct monst *)a0);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 40:{const char * r=pmname((struct permonst *)a0,(int)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 41:{const char * r=mon_pmname((struct monst *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 42:{const char * r=obj_pmname((struct obj *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 43:{char * r=bogusmon((char *)a0,(char *)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 44:{char * r=rndmonnam((char *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 45:{boolean r=bogon_is_pname((char)a0);snprintf(result,sizeof result,"%ld",(long)r);return (uintptr_t)r;}
case 46:{const char * r=roguename();snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 47:{const char * r=hcolor((const char *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 48:{const char * r=rndcolor();snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 49:{const char * r=hliquid((const char *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 50:{char * r=coyotename((struct monst *)a0,(char *)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 51:{char * r=rndorcname((char *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 52:{struct monst * r=christen_orc((struct monst *)a0,(const char *)a1,(const char *)a2);snprintf(result,sizeof result,"mon:%ld",mid(r));return (uintptr_t)r;}
case 53:{const char * r=noveltitle((int *)a0);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
case 54:{const char * r=lookup_novel((const char *)a0,(int *)a1);snprintf(result,sizeof result,"%s",r?r:"[NULL]");return (uintptr_t)r;}
default:abort();}}
const char *probe_snapshot(void){int i;char *p=snap;p+=sprintf(p,"lit:%ld;hallu:%ld;",u.uconduct.literate,u.uprops[HALLUC_RES].extrinsic);for(i=0;i<3;i++)p+=sprintf(p,"m%d:%u:%u:%s;o%d:%u:%u:%s;",i,monsters[i].minvis,monsters[i].female,has_mgivenname(&monsters[i])?MGIVENNAME(&monsters[i]):"[NULL]",i,items[i].oartifact,items[i].dknown,has_oname(&items[i])?ONAME(&items[i]):"[NULL]");for(i=0;i<NUM_OBJECTS;i++)if(objects[i].oc_uname)p+=sprintf(p,"call:%d:%s;",i,objects[i].oc_uname);return snap;}
unsigned probe_table_count(int t){
#ifdef TELEPORT_REFERENCE_TU
switch(t){case 0:return SIZE(ghostnames);case 1:return SIZE(hcolors);case 2:return SIZE(hliquids);case 3:return SIZE(coynames);default:return SIZE(sir_Terry_novels);}
#else
(void)t;return 0;
#endif
}
const char *probe_table_text(int t,int i){
#ifdef TELEPORT_REFERENCE_TU
switch(t){case 0:return ghostnames[i];case 1:return hcolors[i];case 2:return hliquids[i];case 3:return coynames[i];default:return sir_Terry_novels[i];}
#else
(void)t;(void)i;return NULL;
#endif
}
