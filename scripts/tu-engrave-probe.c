#include "hack.h"
#include "artifact.h"
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#undef free
extern void free(void*);
__typeof__(u)u;__typeof__(svm)svm;__typeof__(svc)svc;__typeof__(svl)svl;__typeof__(gi)gi;__typeof__(gm)gm;__typeof__(gn)gn;__typeof__(gy)gy;__typeof__(iflags)iflags;__typeof__(flags)flags;__typeof__(gu)gu;__typeof__(svd)svd;__typeof__(go)go;
struct engr *head_engr;struct obj *uwep,*uarms,*ublindf;struct obj hands_obj;
const struct const_globals cg={0};
const struct c_common_strings c_common_strings={.c_Something="Something",.c_Never_mind="Never mind.",.c_vision_clears="Your vision clears."};
const char ynqchars[]="ynq";
static struct obj items[4];static struct monst holder;static struct trap trap;
static int opts[64],rng_seed=1,rng_count,free_count;static void *growth;
static long stats[2];static unsigned char serialized[65536];static size_t savep,readp;
static NHFILE file;
static char trace[262144],snapshot[16384],input[BUFSZ],output[BUFSZ],scratch[BUFSZ],pristine[BUFSZ];
static int (*occupation)(void);
static void append(const char *fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),fmt,ap);va_end(ap);}
static long oid(const struct obj *o){return !o?-1:o==&hands_obj?-2:o-items;}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("nested:%d;",freehand());}if(opts[31]==stage&&!growth){opts[31]=0;growth=malloc(emscripten_get_heap_size()+8UL*1024*1024);if(!growth)abort();append("grow:%d;",stage);}if(opts[32]==stage){opts[32]=0;u.uprops[BLINDED].intrinsic=0;append("change:blind;");}}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
void panic(const char *fmt,...){(void)fmt;abort();}
void impossible(const char *fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void pline(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);iflags.last_msg++;callback(1);}
#define MESSAGE(name) void name(const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append(#name ":%s;",b);callback(2);}
MESSAGE(You) MESSAGE(Your) MESSAGE(You_cant) MESSAGE(You_see) MESSAGE(There) MESSAGE(pline_The)
void livelog_printf(long mask,const char *fmt,...){char b[2048];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("log:%ld:%s;",mask,b);}
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *file_,int line,const char *fn){const char *p=strrchr(file_,'/');append("caller:%s:%d:%s;",p?p+1:file_,line,fn);}
int (rn2)(int n){rng_seed=(int)((unsigned)rng_seed*1664525U+1013904223U);rng_count++;append("rn2:%d;",n);return n?(unsigned)rng_seed%(unsigned)n:0;}
int (rnd)(int n){return (rn2)(n)+1;}
boolean is_art(struct obj * a0,int a1){return (boolean)opts[14];}

void exercise(int a0,boolean a1){append("exercise:%ld:%ld;",(long)a0,(long)a1);callback(3);}

void sanitize_name(char * a0){append("sanitize_name:%s;",a0?a0:"NULL");callback(3);}

boolean is_pool(coordxy a0,coordxy a1){return (boolean)opts[7];}

boolean is_lava(coordxy a0,coordxy a1){return (boolean)opts[8];}

boolean is_pool_or_lava(coordxy a0,coordxy a1){return (boolean)opts[7];}

boolean is_ice(coordxy a0,coordxy a1){return (boolean)opts[6];}

schar db_under_typ(int a0){return opts[20]?ICE:ROOM;}

void map_engraving(struct engr * a0,int a1){append("map_engraving:%d:%ld;",!!a0,(long)a1);callback(3);}

void newsym(coordxy a0,coordxy a1){append("newsym:%ld:%ld;",(long)a0,(long)a1);callback(3);}

char * mon_nam(struct monst * a0){return "holder";}

boolean on_level(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}

void more_experienced(int a0,int a1){append("more_experienced:%ld:%ld;",(long)a0,(long)a1);callback(3);}

boolean debugcore(const char * a0,boolean a1){return (boolean)opts[16];}

void nomul(int a0){append("nomul:%ld;",(long)a0);callback(3);}

boolean check_capacity(const char * a0){return (boolean)opts[12];}

void update_inventory(void){append("update_inventory;");callback(3);}

void prinv(const char * a0,struct obj * a1,long a2){append("prinv:%s:%ld:%ld;",a0?a0:"NULL",oid(a1),(long)a2);callback(3);}

struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("makemon:%d:%ld:%ld:%ld;",!!a0,(long)a1,(long)a2,(long)a3);callback(3);return 0;}

void obj_extract_self(struct obj * a0){append("obj_extract_self:%ld;",oid(a0));callback(3);}

boolean attacktype(struct permonst * a0,int a1){return (boolean)opts[19];}

boolean resists_blnd(struct monst * a0){return (boolean)opts[13];}

boolean sticks(struct permonst * a0){return (boolean)opts[18];}

char * xname(struct obj * a0){return "stylus";}

char * doname(struct obj * a0){return "stylus";}

char * The(const char * a0){return (char*)a0;}

char * Yobjnam2(struct obj * a0,const char * a1){return "stylus";}

char * Tobjnam(struct obj * a0,const char * a1){return "stylus";}

char * otense(struct obj * a0,const char * a1){return "stylus";}

char * yname(struct obj * a0){return "stylus";}

char * Yname2(struct obj * a0){return "stylus";}

const char * body_part(int a0){return a0==FINGERTIP?"fingertip":"hand";}

void altar_wrath(coordxy a0,coordxy a1){append("altar_wrath:%ld:%ld;",(long)a0,(long)a1);callback(3);}

void wand_explode(struct obj * a0,int a1){append("wand_explode:%ld:%ld;",oid(a0),(long)a1);callback(3);}

void check_unpaid(struct obj * a0){append("check_unpaid:%ld;",oid(a0));callback(3);}

boolean goodpos(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){return (boolean)opts[17];}

struct trap * t_at(coordxy a0,coordxy a1){return opts[9]?&trap:NULL;}

boolean uteetering_at_seen_pit(struct trap * a0){return (boolean)opts[10];}

boolean uescaped_shaft(struct trap * a0){return (boolean)opts[11];}

void dry_a_towel(struct obj * a0,int a1,boolean a2){append("dry_a_towel:%ld:%ld:%ld;",oid(a0),(long)a1,(long)a2);callback(3);}

int welded(struct obj * a0){return (int)opts[5];}

void learnwand(struct obj * a0){if(opts[28])objects[a0->otyp].oc_name_known=1;append("learnwand:%ld;",oid(a0));callback(3);}

int zappable(struct obj * a0){return (int)opts[4];}

void zapnodir(struct obj * a0){append("zapnodir:%ld;",oid(a0));callback(3);}
char yn_function(const char *q,const char *choices,char def,boolean hist){append("yn:%s:%s:%d:%d;",q,choices,def,hist);callback(4);return opts[3];}
struct obj *getobj(const char *prompt,int(*selector)(struct obj*),unsigned flags_){int i;append("getobj:%s:%u:null%d",prompt,flags_,selector(NULL));for(i=0;i<4;i++)append(":%d",selector(&items[i]));append(";");callback(5);return opts[1]==-1?NULL:opts[1]==-2?&hands_obj:&items[opts[1]];}
void set_occupation(int(*fn)(void),const char *text,cmdcount_nht time){append("occupation:%s:%ld;",text,time);occupation=fn;go.occupation=fn;callback(6);}
void getlin(const char *prompt,char *out){append("getlin:%s;",prompt);callback(7);strcpy(out,input);}
struct obj *hold_another_object(struct obj *obj,const char *drop,const char *name,const char *arg){append("hold:%ld:%s:%s:%d;",oid(obj),drop,name,!!arg);callback(8);obj->nobj=gi.invent;gi.invent=obj;return obj;}
struct obj *splitobj(struct obj *obj,long amount){append("split:%ld:%ld;",oid(obj),amount);items[3]=*obj;items[3].quan=amount;obj->quan-=amount;callback(8);return &items[3];}
void make_blinded(long value,boolean talk){append("blinded:%ld:%d;",value,talk);u.uprops[BLINDED].intrinsic=value;callback(9);}
const char *surface(coordxy x,coordxy y){(void)x;(void)y;return opts[6]?"ice":"floor";}
const char *ceiling(coordxy x,coordxy y){(void)x;(void)y;return "ceiling";}
char *getrumor(int truth,char *out,boolean exclude){append("rumor:%d:%d;",truth,exclude);callback(10);strcpy(out,opts[21]?"":"A rumor.");return opts[22]?NULL:out;}
char *get_rnd_text(const char *file_,char *out,int(*rng)(int),unsigned pad){append("random:%s:%u:%d;",file_,pad,rng==(rn2));callback(10);strcpy(out,(rng(3)==1)?"A grave message.":"Readable writing.");return out;}
boolean set_levltyp(coordxy x,coordxy y,schar typ){append("levtyp:%d:%d:%d;",x,y,typ);if(opts[23])return FALSE;svl.level.locations[x][y].typ=typ;callback(11);return TRUE;}
void useup(struct obj *obj){append("useup:%ld;",oid(obj));if(gi.invent==obj)gi.invent=obj->nobj;callback(12);}
void teleport_probe_free(void *p){free_count++;append("free;");callback(13);free(p);}
void sfo_unsigned(NHFILE *fp,unsigned *p,const char *tag){(void)fp;append("sfo-u:%s:%u;",tag,*p);memcpy(serialized+savep,p,sizeof *p);savep+=sizeof *p;callback(14);}
void sfi_unsigned(NHFILE *fp,unsigned *p,const char *tag){(void)fp;memcpy(p,serialized+readp,sizeof *p);readp+=sizeof *p;append("sfi-u:%s:%u;",tag,*p);callback(14);}
void sfo_engr(NHFILE *fp,struct engr *ep,const char *tag){(void)fp;append("sfo-e:%s:%d:%d:%d:%ld:%u;",tag,ep->engr_x,ep->engr_y,ep->engr_type,ep->engr_time,ep->engr_alloc);memcpy(serialized+savep,ep,sizeof *ep);savep+=sizeof *ep;callback(15);if(opts[25])ep->engr_time+=3;}
void sfi_engr(NHFILE *fp,struct engr *ep,const char *tag){(void)fp;memcpy(ep,serialized+readp,sizeof *ep);readp+=sizeof *ep;append("sfi-e:%s:%d:%d:%d:%ld:%u;",tag,ep->engr_x,ep->engr_y,ep->engr_type,ep->engr_time,ep->engr_alloc);callback(15);}
void sfo_char(NHFILE *fp,char *p,const char *tag,int n){(void)fp;append("sfo-c:%s:%d:%s;",tag,n,p);memcpy(serialized+savep,p,n);savep+=n;callback(16);if(opts[26]&&n>1)p[0]='!';}
void sfi_char(NHFILE *fp,char *p,const char *tag,int n){(void)fp;memcpy(p,serialized+readp,n);readp+=n;append("sfi-c:%s:%d:%s;",tag,n,p);callback(16);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../nethack-c/upstream/src/engrave.c"
#undef free
#else
extern int teleport_engrave_test_stylus_ok(struct obj*);
extern boolean teleport_engrave_test_u_can_engrave(void);
extern void teleport_engrave_test_doengrave_ctx_init(void*);
extern void teleport_engrave_test_doengrave_sfx_item_WAN(void*);
extern boolean teleport_engrave_test_doengrave_sfx_item(void*);
extern void teleport_engrave_test_doengrave_ctx_verb(void*);
extern int teleport_engrave_test_engrave(void);
extern const char *teleport_engrave_test_blengr(void);
#define stylus_ok teleport_engrave_test_stylus_ok
#define u_can_engrave teleport_engrave_test_u_can_engrave
#define doengrave_ctx_init teleport_engrave_test_doengrave_ctx_init
#define doengrave_sfx_item_WAN teleport_engrave_test_doengrave_sfx_item_WAN
#define doengrave_sfx_item teleport_engrave_test_doengrave_sfx_item
#define doengrave_ctx_verb teleport_engrave_test_doengrave_ctx_verb
#define engrave teleport_engrave_test_engrave
#define blengr teleport_engrave_test_blengr
#endif
#include "tu-engrave-layout.h"
#ifdef TELEPORT_REFERENCE_TU
_Static_assert(sizeof(struct _doengrave_ctx)==sizeof(struct teleport_engrave_context),"Original context size");
#define CTXCHECK(f) _Static_assert(offsetof(struct _doengrave_ctx,f)==offsetof(struct teleport_engrave_context,f),"Original context "#f)
CTXCHECK(dengr);CTXCHECK(doblind);CTXCHECK(doknown);CTXCHECK(eow);CTXCHECK(jello);CTXCHECK(ptext);CTXCHECK(teleengr);CTXCHECK(zapwand);CTXCHECK(disprefresh);CTXCHECK(frosted);CTXCHECK(adding);CTXCHECK(ret);CTXCHECK(type);CTXCHECK(oetype);CTXCHECK(otmp);CTXCHECK(oep);CTXCHECK(buf);CTXCHECK(ebuf);CTXCHECK(fbuf);CTXCHECK(qbuf);CTXCHECK(post_engr_text);CTXCHECK(writer);CTXCHECK(everb);CTXCHECK(eloc);CTXCHECK(len);
#undef CTXCHECK
#endif
static struct teleport_engrave_context ctx;
unsigned probe_layout_count(void){return SIZE(engrave_layout);}
const char *probe_layout_name(unsigned i){return engrave_layout[i].name;}
size_t probe_layout_value(unsigned i){return engrave_layout[i].value;}
int probe_string_count(void){return 2;}
const char *probe_string_name(int i){return i?"EPITAPHFILE":"ENGRAVEFILE";}
const char *probe_string_value(int i){return i?EPITAPHFILE:ENGRAVEFILE;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_trace(void){return trace;}
const char *probe_output(void){return output;}
void probe_clear(void){*trace=0;}
void probe_option(int i,int value){opts[i]=value;}
void probe_input(const char *text){strcpy(input,text);}
void probe_reset(void){int i,x,y;struct engr *ep;while((ep=head_engr)!=NULL){head_engr=ep->nxt_engr;free(ep);}if(growth){free(growth);growth=NULL;}objects_globals_init();monst_globals_init();memset(&u,0,sizeof u);memset(&svc,0,sizeof svc);memset(&svl,0,sizeof svl);memset(&gi,0,sizeof gi);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&iflags,0,sizeof iflags);memset(&flags,0,sizeof flags);memset(&ctx,0,sizeof ctx);memset(opts,0,sizeof opts);memset(items,0,sizeof items);memset(&hands_obj,0,sizeof hands_obj);memset(&file,0,sizeof file);memset(&svd,0,sizeof svd);memset(&go,0,sizeof go);for(i=0;i<4;i++){items[i].otyp=DAGGER;items[i].oclass=WEAPON_CLASS;items[i].quan=1;items[i].spe=1;}hands_obj.oclass=RANDOM_CLASS;gy.youmonst.data=&mons[PM_HUMAN];holder.data=&mons[PM_PURPLE_WORM];gi.invent=&items[0];items[0].nobj=&items[1];items[1].nobj=&items[2];items[2].nobj=NULL;u.ux=u.uy=10;svm.moves=100;flags.verbose=1;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)svl.level.locations[x][y].typ=ROOM;opts[1]=-2;opts[3]='n';opts[4]=1;opts[17]=1;rng_seed=1;rng_count=free_count=0;savep=readp=0;occupation=NULL;uwep=uarms=ublindf=NULL;stats[0]=stats[1]=0;strcpy(input,"Elbereth");*output=*scratch=*pristine=*trace=0;ctx.everb="oldverb";ctx.eloc="oldloc";ctx.len=1152921504606846979UL;}
void probe_seed(int value){rng_seed=value;}
void probe_item(int i,int typ,int spe,long quantity,int artifact){items[i].otyp=typ;items[i].oclass=objects[typ].oc_class;items[i].spe=spe;items[i].quan=quantity;items[i].oartifact=artifact;}
void probe_item_bit(int i,int key,int value){switch(key){case 0:items[i].cursed=value;break;case 1:items[i].known=value;break;case 2:items[i].owornmask=value;break;}}
void probe_equipment(int key,int item){struct obj *obj=item<0?NULL:&items[item];if(key==0)uwep=obj;else if(key==1)uarms=obj;else ublindf=obj;}
void probe_hero(int pm,int swallow,int hidden,int mounted,int skill){gy.youmonst.data=&mons[pm];u.uswallow=swallow;u.ustuck=swallow?&holder:NULL;u.uundetected=hidden;u.usteed=mounted?&holder:NULL;u.weapon_skills[P_RIDING].skill=skill;}
void probe_prop(int p,long intr,long extr,long blocked){u.uprops[p].intrinsic=intr;u.uprops[p].extrinsic=extr;u.uprops[p].blocked=blocked;}
void probe_terrain(int x,int y,int typ,int disturbed){svl.level.locations[x][y].typ=typ;svl.level.locations[x][y].disturbed=disturbed;}
void probe_level(int key,int dnum,int level){d_level *l=key==0?&u.uz:key==1?&air_level:&water_level;l->dnum=dnum;l->dlevel=level;}
void probe_global(int key,long value){switch(key){case 0:svm.moves=value;break;case 1:gi.in_mklev=value;break;case 2:gm.multi=value;break;case 3:svc.context.run=value;break;case 4:iflags.last_msg=value;break;case 5:u.uroleplay.deaf=value;break;case 6:flags.verbose=value;break;}}
void probe_context(int key,long value){switch(key){case 0:ctx.otmp=value<0?&hands_obj:&items[value];break;case 1:ctx.oep=head_engr;break;case 2:ctx.type=value;break;case 3:ctx.oetype=value;break;case 4:ctx.adding=value;break;case 5:ctx.frosted=value;break;case 6:ctx.ret=value;break;case 7:ctx.len=value;break;}}
void probe_make(int x,int y,const char *text,const char *original,long time,int type){make_engr_at(x,y,text,original,time,type);}
static struct engr *node(int i){struct engr *ep=head_engr;while(ep&&i-->0)ep=ep->nxt_engr;return ep;}
void probe_engr_bit(int i,int bit,int value){struct engr *ep=node(i);switch(bit){case 0:ep->guardobjects=value;break;case 1:ep->nowipeout=value;break;case 2:ep->eread=value;break;case 3:ep->erevealed=value;break;}}
void probe_text(int i,int state,int skip,const char *text){struct engr *ep=node(i);ep->engr_txt[state]=engr_text_space(ep)+ep->engr_szeach*state+skip;strcpy(ep->engr_txt[state],text);}
long probe_action(int op,int a,int b,int c,long d){struct engr *ep;switch(op){case 0:random_engraving(output,pristine);break;case 1:strcpy(output,input);wipeout_text(output,a,(unsigned)d);break;case 2:return can_reach_floor(a);case 3:cant_reach_floor(u.ux,u.uy,a,b,c);break;case 4:return engr_at(a,b)!=NULL;case 5:return sengr_at(input,a,b,c)!=NULL;case 6:u_wipe_engr(a);break;case 7:wipe_engr_at(a,b,(xint16)c,(boolean)d);break;case 8:return engr_can_be_felt(node(a));case 9:read_engr_at(a,b);break;case 10:make_engr_at(a,b,input,NULL,d,c);break;case 11:del_engr_at(a,b);break;case 12:return freehand();case 13:return stylus_ok(a<0?NULL:&items[a]);case 14:return u_can_engrave();case 15:doengrave_ctx_init((void*)&ctx);break;case 16:doengrave_sfx_item_WAN((void*)&ctx);break;case 17:return doengrave_sfx_item((void*)&ctx);case 18:doengrave_ctx_verb((void*)&ctx);break;case 19:return doengrave();case 20:return engrave();case 21:sanitize_engravings();break;case 22:forget_engravings();break;case 23:engraving_sanity_check();break;case 24:file.mode=a;save_engravings(&file);break;case 25:readp=0;rest_engravings(&file);break;case 26:engr_stats("size %ld",output,opts[27]&&head_engr?&head_engr->engr_time:&stats[0],&stats[opts[24]?0:1]);break;case 27:del_engr(node(a));break;case 28:rloc_engr(node(a));break;case 29:make_grave(a,b,c?input:NULL);break;case 30:disturb_grave(a,b);break;case 31:see_engraving(node(a));break;case 32:feel_engraving(node(a));break;case 33:strcpy(output,blengr());break;case 34:return occupation?occupation():-7;case 35:ep=node(a);return ep?ep->engr_txt[b]-engr_text_space(ep):-1;}return 0;}
const char *probe_snapshot(void){char *p=snapshot;struct engr *ep;int i,n=0;for(ep=head_engr;ep;ep=ep->nxt_engr){p+=sprintf(p,"e%d:%d,%d,%d,%u,%u,%ld,%d%d%d%d;",n++,ep->engr_x,ep->engr_y,ep->engr_type,ep->engr_alloc,ep->engr_szeach,ep->engr_time,ep->guardobjects,ep->nowipeout,ep->eread,ep->erevealed);for(i=0;i<text_states;i++)p+=sprintf(p,"t%d@%ld:%s;",i,ep->engr_txt[i]-engr_text_space(ep),ep->engr_txt[i]);}p+=sprintf(p,"g:%ld,%ld,%ld,%d,%d,%d,%d,%ld;",svm.moves,gm.multi,u.uconduct.literate,svc.context.run,iflags.last_msg,gi.in_mklev,!!occupation,gn.nomovemsg?1L:0L);p+=sprintf(p,"occ:%d,%d,%d,%d,%s,%ld,%ld;",svc.context.engraving.actionct,svc.context.engraving.type,svc.context.engraving.pos.x,svc.context.engraving.pos.y,svc.context.engraving.text,svc.context.engraving.nextc?svc.context.engraving.nextc-svc.context.engraving.text:-1L,oid(svc.context.engraving.stylus));p+=sprintf(p,"ctx:%d%d%d%d%d%d%d%d%d%d%d,%d,%d,%d,%ld,%d,%lu,%s|%s|%s|%s|%s,%s,%s,%s;",ctx.dengr,ctx.doblind,ctx.doknown,ctx.eow,ctx.jello,ctx.ptext,ctx.teleengr,ctx.zapwand,ctx.disprefresh,ctx.frosted,ctx.adding,ctx.ret,ctx.type,ctx.oetype,oid(ctx.otmp),!!ctx.oep,ctx.len,ctx.buf,ctx.ebuf,ctx.fbuf,ctx.qbuf,ctx.post_engr_text,ctx.writer?ctx.writer:"NULL",ctx.everb?ctx.everb:"NULL",ctx.eloc?ctx.eloc:"NULL");for(i=0;i<4;i++)p+=sprintf(p,"o%d:%d,%d,%ld,%ld,%d%d;",i,items[i].otyp,items[i].spe,items[i].quan,items[i].owornmask,items[i].known,items[i].cursed);p+=sprintf(p,"stats:%ld:%ld;io:%lu:%lu;free:%d;rng:%d;",stats[0],stats[1],savep,readp,free_count,rng_count);return snapshot;}
int probe_table_count(int table){
#ifdef TELEPORT_REFERENCE_TU
 return table?SIZE(blind_writing):SIZE(rubouts);
#else
 (void)table;return 0;
#endif
}
int probe_table_width(void){
#ifdef TELEPORT_REFERENCE_TU
 return sizeof blind_writing[0];
#else
 return 0;
#endif
}
int probe_table_value(int table,int row,int col){
#ifdef TELEPORT_REFERENCE_TU
 return table?(unsigned char)blind_writing[row][col]:rubouts[row].wipefrom;
#else
 (void)table;(void)row;(void)col;return 0;
#endif
}
const char *probe_table_text(int row){
#ifdef TELEPORT_REFERENCE_TU
 return rubouts[row].wipeto;
#else
 (void)row;return NULL;
#endif
}
