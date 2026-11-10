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
extern const struct shclass shtypes[];
struct you u;
__typeof__(svb) svb;
__typeof__(svc) svc;
__typeof__(svl) svl;
__typeof__(svd) svd;
__typeof__(svr) svr;
__typeof__(gd) gd;
__typeof__(flags) flags;
__typeof__(program_state) program_state;
__typeof__(windowprocs) windowprocs;
winid WIN_MESSAGE=3;
time_t ubirthday;
static struct monst monsters[64];
static struct obj item,generated;
static s_level special;
static int options[24],random_values[512],random_length,random_index,free_count,created;
static unsigned random_state;
static size_t callback_stack;
static coordxy output_x,output_y;
static coord doors[256];
static char tracebuf[524288],statebuf[2097152],caller[128],output[BUFSZ],monname[BUFSZ];
static void *growth;
static int mid(struct monst *m){return m?(int)(m-monsters)+1:0;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(impossible)
void teleport_probe_free(void *p){int i;for(i=0;i<64;i++)if(monsters[i].mextra&&ESHK(&monsters[i])==p){append("free-eshk:%d;",i);free_count++;break;}free(p);}
boolean rng_log_enabled(void){return options[0];}
void rng_log_set_caller(const char *file,int line,const char *fn){const char *p=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:file,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;return v;}
int (rn2)(int n){int v=draw(n);if(options[21])v=n-1;append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;if(options[21])v=1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
struct mextra *newmextra(void){struct mextra *p=(struct mextra *)alloc(sizeof *p);memset(p,0,sizeof *p);append("new-extra;");return p;}
struct obj *mksobj_at(int type,coordxy x,coordxy y,boolean init,boolean art){append("mksobj:%d:%d:%d:%d:%d;",type,x,y,init,art);if(options[20]){size_t sp=emscripten_stack_get_current();if(!callback_stack)callback_stack=sp;append("callback-stack:%ld;",(long)(sp-callback_stack));}if(options[1])return NULL;memset(&generated,0,sizeof generated);generated.otyp=type;generated.oclass=objects[type].oc_class;return &generated;}
struct obj *mkobj_at(char cls,coordxy x,coordxy y,boolean init){append("mkobj:%d:%d:%d:%d;",cls,x,y,init);memset(&generated,0,sizeof generated);generated.oclass=cls;return &generated;}
void set_tin_variety(struct obj *o,int variety){append("tin:%d;",variety);o->spe=1;}
schar depth(d_level *l){append("depth:%d:%d;",l->dnum,l->dlevel);return options[2];}
struct permonst *mkclass(char symbol,int flags){append("class:%d:%d;",symbol,flags);return options[3]?NULL:&mons[PM_SMALL_MIMIC];}
struct monst *makemon(struct permonst *p,coordxy x,coordxy y,mmflags_nht f){struct monst *m;append("make:%d:%d:%d:%lu;",p->pmidx,x,y,(unsigned long)f);if(options[4])return NULL;m=&monsters[created++];m->data=p;m->mx=x;m->my=y;m->mhp=20;if(f&MM_ESHK)neweshk(m);if(options[17]){options[17]=0;append("nested-new;");neweshk(&monsters[63]);}if(options[18]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew;");}svl.level.monsters[x][y]=m;return m;}
boolean In_mines(d_level *l){append("mines:%d:%d;",l->dnum,l->dlevel);return l->dnum==mines_dnum;}
s_level *Is_special(d_level *l){append("special:%d:%d;",l->dnum,l->dlevel);return options[5]?&special:NULL;}
xint16 ledger_no(d_level *l){append("ledger:%d:%d;",l->dnum,l->dlevel);return options[6];}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
boolean rloc(struct monst *m,unsigned flags){append("rloc:%d:%u;",mid(m),flags);return TRUE;}
void set_malign(struct monst *m){append("malign:%d;",mid(m));}
void mon_learns_traps(struct monst *m,int traps){append("traps:%d:%d;",mid(m),traps);}
void assign_level(d_level *to,d_level *from){append("level:%d:%d;",from->dnum,from->dlevel);*to=*from;}
void mkmonmoney(struct monst *m,long n){append("money:%d:%ld;",mid(m),n);}
struct obj *mongets(struct monst *m,int type){append("mongets:%d:%d;",mid(m),type);return &generated;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
void cvt_sdoor_to_door(struct rm *r){append("convert-door;");r->typ=DOOR;}
char inside_shop(coordxy x,coordxy y){append("inside:%d:%d;",x,y);return options[7];}
void make_engr_at(coordxy x,coordxy y,const char *text,const char *a,long when,int type){append("engrave:%d:%d:%s:%d:%ld:%d;",x,y,text,a!=NULL,when,type);}
char *in_rooms(coordxy x,coordxy y,int type){append("rooms:%d:%d:%d;",x,y,type);return options[8]?"Q":"";}
boolean on_level(d_level *a,d_level *b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
struct monst *shop_keeper(char room){append("keeper:%d;",room);return &monsters[0];}
void mongone(struct monst *m){append("gone:%d;",mid(m));m->mhp=0;}
char *noit_mon_nam(struct monst *m){append("noit:%d:%d;",mid(m),m->isshk);snprintf(monname,sizeof monname,"lowercase fallback");return monname;}
boolean in_town(coordxy x,coordxy y){append("town:%d:%d;",x,y);return options[9];}
static void display_window(winid w,boolean b){append("display:%d:%d;",w,b);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/shknam.c"
#undef free
#else
extern boolean teleport_shknam_test_stockpos(struct mkroom *,int,int,int,int),teleport_shknam_test_veggy(struct obj *,int);
extern int teleport_shknam_test_veg(void),teleport_shknam_test_door(struct mkroom *,coordxy *,coordxy *),teleport_shknam_test_init(const struct shclass *,struct mkroom *);
extern void teleport_shknam_test_mkveggy(int,int),teleport_shknam_test_mkshobj(const struct shclass *,int,int,boolean),teleport_shknam_test_names(struct monst *,const char *const *);
#endif
#include "tu-shknam-layout.h"
static const char *const prefix_names[]={"_Female","|Male","=Neutral","-Personal","+Other",NULL};
static const char *const same_names[]={"=Same",NULL};
static const char *const izchak_names[]={"Izchak",NULL};
static const char *const lowercase_names[]={"lowercase",NULL};
static const char *const *list(int i){
#ifdef TELEPORT_REFERENCE_TU
const char *const *lists[]={shkliquors,shkbooks,shkarmors,shkwands,shkrings,shkfoods,shkweapons,shktools,shklight,shkgeneral,shkhealthfoods};if(i<11)return lists[i];
#else
static const int shops[]={3,2,1,7,6,5,4,8,11,0,10};if(i<11)return shtypes[shops[i]].shknms;
#endif
return i==11?prefix_names:i==12?same_names:i==13?izchak_names:lowercase_names;}
void probe_reset(unsigned seed){int i;for(i=0;i<64;i++)if(monsters[i].mextra){if(ESHK(&monsters[i]))free(ESHK(&monsters[i]));free(monsters[i].mextra);}if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&svb,0,sizeof svb);memset(&svc,0,sizeof svc);memset(&svl,0,sizeof svl);memset(&svd,0,sizeof svd);memset(&svr,0,sizeof svr);memset(&gd,0,sizeof gd);memset(&flags,0,sizeof flags);memset(&program_state,0,sizeof program_state);memset(monsters,0,sizeof monsters);memset(&item,0,sizeof item);memset(&generated,0,sizeof generated);memset(&special,0,sizeof special);memset(options,0,sizeof options);options[0]=1;monst_globals_init();objects_globals_init();for(i=0;i<NUM_OBJECTS;i++){int c=objects[i].oc_class;objects[i].oc_name_idx=i;objects[i].oc_descr_idx=i;if(i>=MAXOCLASSES&&!svb.bases[c])svb.bases[c]=i;}for(i=0;i<64;i++){monsters[i].m_id=100+i;monsters[i].data=&mons[PM_SHOPKEEPER];monsters[i].mhp=20;if(i<63)monsters[i].nmon=&monsters[i+1];}fmon=monsters;u.uz.dnum=0;u.uz.dlevel=5;mines_dnum=2;svd.doors=doors;memset(doors,0,sizeof doors);orcus_level.dnum=9;orcus_level.dlevel=9;ubirthday=1777723200;random_length=random_index=free_count=created=0;callback_stack=0;random_state=seed;tracebuf[0]=caller[0]=output[0]=monname[0]=0;output_x=output_y=-77;windowprocs.win_display_nhwindow=display_window;}
const char *probe_trace(void){return tracebuf;}
void probe_option(int i,int value){options[i]=value;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
int probe_table_count(void){int i=0;while(shtypes[i].name&&i<100)i++;return i+1;}
const char *probe_table_string(int row,int field){return field?shtypes[row].annotation:shtypes[row].name;}
int probe_table_value(int row,int field,int slot){const struct shclass *s=&shtypes[row];int i;switch(field){case 0:return s->symb;case 1:return s->prob;case 2:return s->shdist;case 3:return s->iprobs[slot].iprob;case 4:return s->iprobs[slot].itype;default:if(!s->shknms)return -1;for(i=0;i<11;i++)if(s->shknms==list(i))return i;return 99;}}
int probe_list_count(int n){int i=0;const char *const *p=list(n);if(!p)return 0;while(p[i])i++;return i;}
const char *probe_list_name(int n,int i){return list(n)[i];}
const void *probe_list_pointer(int n){return list(n);}
void probe_obj(int type,int species,int spe){memset(&item,0,sizeof item);item.otyp=type;item.oclass=objects[type].oc_class;item.corpsenm=species;item.spe=spe;}
void probe_obit(int field,int value){if(field==0)item.oclass=value;else if(field==1)objects[item.otyp].oc_prob=value;else if(field==2)item.corpsenm=value;else item.spe=value;}
void probe_mon(int i,int pm){monsters[i].data=&mons[pm];}
void probe_mbit(int i,int field,long value){struct monst *m=&monsters[i];switch(field){case 0:m->female=value;break;case 1:m->isshk=value;break;case 2:m->mpeaceful=value;break;case 3:m->msleeping=value;break;case 4:m->m_id=value;break;case 5:m->mhp=value;break;}}
void probe_name(int n,const char *s){if(!monsters[n].mextra||!ESHK(&monsters[n]))neweshk(&monsters[n]);strncpy(ESHK(&monsters[n])->shknam,s,PL_NSIZ);ESHK(&monsters[n])->shknam[PL_NSIZ-1]=0;}
void probe_hero(int key,long value){switch(key){case 0:ubirthday=value;break;case 1:u.uz.dnum=value;break;case 2:u.uz.dlevel=value;break;case 3:special.flags.town=value;break;case 4:svc.context.tribute.enabled=value;break;case 5:svc.context.tribute.bookstock=value;break;case 6:program_state.gameover=value;break;case 7:wizard=value;break;case 8:orcus_level.dnum=value?u.uz.dnum:9;orcus_level.dlevel=value?u.uz.dlevel:9;break;}}
void probe_prop(int p,int field,long value){if(field==0)u.uprops[p].intrinsic=value;else if(field==1)u.uprops[p].extrinsic=value;else u.uprops[p].blocked=value;}
void probe_room(int i,int lx,int ly,int hx,int hy,int doorct,int fdoor,int irregular,int rtype){struct mkroom *r=&svr.rooms[i];r->lx=lx;r->ly=ly;r->hx=hx;r->hy=hy;r->doorct=doorct;r->fdoor=fdoor;r->irregular=irregular;r->rtype=rtype;}
void probe_door(int i,int x,int y){svd.doors[i].x=x;svd.doors[i].y=y;}
void probe_cell(int x,int y,int type,int mask,int edge,int roomno,int monster){levl[x][y].typ=type;levl[x][y].doormask=mask;levl[x][y].edge=edge;levl[x][y].roomno=roomno;svl.level.monsters[x][y]=monster<0?NULL:&monsters[monster];}
int probe_action(int op,int a,int b,int c,int d){struct mkroom *r=&svr.rooms[a];switch(op){case 0:
#ifdef TELEPORT_REFERENCE_TU
return veggy_item(b?&item:NULL,c);
#else
return teleport_shknam_test_veggy(b?&item:NULL,c);
#endif
case 1:
#ifdef TELEPORT_REFERENCE_TU
return shkveg();
#else
return teleport_shknam_test_veg();
#endif
case 2:
#ifdef TELEPORT_REFERENCE_TU
mkveggy_at(a,b);
#else
teleport_shknam_test_mkveggy(a,b);
#endif
break;case 3:
#ifdef TELEPORT_REFERENCE_TU
mkshobj_at(&shtypes[a],b,c,d);
#else
teleport_shknam_test_mkshobj(&shtypes[a],b,c,d);
#endif
break;case 4:
#ifdef TELEPORT_REFERENCE_TU
nameshk(&monsters[a],list(b));
#else
teleport_shknam_test_names(&monsters[a],list(b));
#endif
break;case 5:neweshk(&monsters[a]);break;case 6:free_eshk(&monsters[a]);break;case 7:
#ifdef TELEPORT_REFERENCE_TU
return good_shopdoor(r,&output_x,&output_y);
#else
return teleport_shknam_test_door(r,&output_x,&output_y);
#endif
case 8:
#ifdef TELEPORT_REFERENCE_TU
return shkinit(&shtypes[b],r);
#else
return teleport_shknam_test_init(&shtypes[b],r);
#endif
case 9:
#ifdef TELEPORT_REFERENCE_TU
return stock_room_goodpos(r,b,c,d,options[19]);
#else
return teleport_shknam_test_stockpos(r,b,c,d,options[19]);
#endif
case 10:stock_room(b,r);break;case 11:return saleable(&monsters[a],&item);case 12:return get_shop_item(a);case 13:strcpy(output,Shknam(&monsters[a]));break;case 14:strcpy(output,shkname(&monsters[a]));break;case 15:return shkname_is_pname(&monsters[a]);case 16:return is_izchak(&monsters[a],b);}return 0;}
void *probe_pointer(int n){return &monsters[n];}
void *probe_extra_pointer(int n){return monsters[n].mextra?ESHK(&monsters[n]):NULL;}
size_t probe_extra_size(void){return sizeof(struct eshk);}
void probe_extra_poison(int n,int byte){memset(ESHK(&monsters[n]),byte,sizeof(struct eshk));}
int probe_free_count(void){return free_count;}
const char *probe_output(void){return output;}
size_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){char *p=statebuf;int i,x,y;size_t j;p+=sprintf(p,"globals:%d:%d:%d:%d:%d:%d:%d:%d:%d;",free_count,output_x,output_y,svl.level.flags.has_shop,svc.context.tribute.enabled,svc.context.tribute.bookstock,item.otyp,item.corpsenm,item.spe);for(i=0;i<64;i++){struct monst *m=&monsters[i];p+=sprintf(p,"m%d:%u:%d:%d:%d:%d:%d:%d:%d:%d:",i,m->m_id,m->mhp,m->female,m->isshk,m->mpeaceful,m->msleeping,m->mx,m->my,m->mextra!=NULL);if(m->mextra&&ESHK(m)){unsigned char data[sizeof(struct eshk)];memcpy(data,ESHK(m),sizeof data);memset(data+offsetof(struct eshk,bill_p),0,sizeof ESHK(m)->bill_p);for(j=0;j<sizeof data;j++)p+=sprintf(p,"%02x",data[j]);}p+=sprintf(p,";");}for(i=0;i<4;i++){struct mkroom *r=&svr.rooms[i];p+=sprintf(p,"r%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;",i,r->lx,r->ly,r->hx,r->hy,r->doorct,r->fdoor,r->irregular,r->rtype,mid(r->resident));}p+=sprintf(p,"map:");for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)if(levl[x][y].typ||levl[x][y].flags||levl[x][y].roomno||levl[x][y].edge||svl.level.monsters[x][y])p+=sprintf(p,"%d,%d,%d,%d,%d,%d,%d/",x,y,levl[x][y].typ,levl[x][y].doormask,levl[x][y].roomno,levl[x][y].edge,mid(svl.level.monsters[x][y]));p+=sprintf(p,"generated:%d:%d:%d;",generated.otyp,generated.oclass,generated.spe);return statebuf;}
