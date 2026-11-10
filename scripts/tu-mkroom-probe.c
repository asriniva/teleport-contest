#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include "tu-mkroom-layout.h"
__typeof__(svr) svr;__typeof__(svn) svn;__typeof__(gs) gs;__typeof__(gn) gn;__typeof__(svl) svl;__typeof__(svd) svd;__typeof__(svm) svm;struct you u;struct flag flags;time_t ubirthday;
/* Controlled dependency tables, not a mirror of MKROOM's squadprob. */
const struct shclass shtypes[]={ {.name="fixture general",.symb=RANDOM_CLASS,.prob=50}, {.name="fixture wand",.symb=WAND_CLASS,.prob=25}, {.name="fixture book",.symb=SPBOOK_CLASS,.prob=25}, {0} };
const struct class_sym def_oc_syms[MAXOCLASSES]={[WAND_CLASS]={.sym='/'},[SPBOOK_CLASS]={.sym='+'}};
static struct mkroom subrooms[(MAXNROFROOMS+1)*2];static coord doors[256];static stairway fixture_stairs[16];
static struct monst monsters[1024];static struct obj items[2048];static int monster_count,item_count;
static int options[32],random_values[2048],random_length,random_index;static unsigned random_state;
static char trace[1048576],caller[128],shoptype[BUFSZ];static NHFILE fixture_file;
static void *growth_block;
static unsigned char io[262144];static size_t io_length,io_position;
void panic(const char *format,...){abort();}
static void append(const char *format,...){va_list ap;va_start(ap,format);vsnprintf(trace+strlen(trace),sizeof trace-strlen(trace),format,ap);va_end(ap);}
void impossible(const char*format,...){char b[BUFSZ];va_list ap;va_start(ap,format);vsnprintf(b,sizeof b,format,ap);va_end(ap);append("impossible:%s;",b);}
boolean rng_log_enabled(void){return options[0];}
void rng_log_set_caller(const char*file,int line,const char*function){const char*b=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:file,line,function);}
static int draw(const char*kind,int n){int v;if(n<=0)return 0;if(random_index<random_length)v=(unsigned)random_values[random_index]%(unsigned)n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;append("%s:%d:%d@%s;",kind,n,v,caller);return v;}
int (rn2)(int n){return draw("rn2",n);}int (rnd)(int n){return draw("rnd",n)+1;}
char *nh_getenv(const char*name){append("getenv:%s;",name);return shoptype[0]?shoptype:NULL;}
xint16 level_difficulty(void){append("difficulty:%d;",options[1]);return options[1];}
void topologize(struct mkroom*r){append("topologize:%ld;",(long)(r-svr.rooms));}
void set_malign(struct monst*m){append("malign:%ld:%d;",(long)(m-monsters),m->mpeaceful);}
struct obj *mongets(struct monst*m,int typ){append("mongets:%ld:%d;",(long)(m-monsters),typ);return NULL;}
struct monst *makemon(struct permonst*p,coordxy x,coordxy y,mmflags_nht mm){struct monst*m;append("make:%d:%d:%d:%u;",p?monsndx(p):-1,x,y,mm);if(options[2])return NULL;if(monster_count>=SIZE(monsters))abort();m=&monsters[monster_count++];memset(m,0,sizeof *m);m->data=p?p:&mons[PM_HUMAN];m->mx=x;m->my=y;m->mpeaceful=options[3];return m;}
static struct obj *newitem(int type){struct obj*o;if(item_count>=SIZE(items))abort();o=&items[item_count++];memset(o,0,sizeof *o);o->otyp=type;o->quan=1;return o;}
struct obj *mksobj(int type,boolean init,boolean art){append("object:%d:%d:%d;",type,init,art);return newitem(type);}
struct obj *mksobj_at(int type,coordxy x,coordxy y,boolean init,boolean art){append("objectat:%d:%d:%d:%d:%d;",type,x,y,init,art);return newitem(type);}
struct obj *mkgold(long amount,coordxy x,coordxy y){struct obj*o;append("gold:%ld:%d:%d;",amount,x,y);o=newitem(GOLD_PIECE);o->quan=amount;return o;}
struct obj *mk_tt_object(int type,coordxy x,coordxy y){append("tt:%d:%d:%d;",type,x,y);return options[4]?NULL:newitem(type);}
struct obj *mkobj(int type,boolean art){append("mkobj:%d:%d;",type,art);return newitem(APPLE);}
struct obj *mkobj_at(char type,coordxy x,coordxy y,boolean art){append("mkobjat:%d:%d:%d:%d;",type,x,y,art);return newitem(APPLE);}
struct obj *add_to_container(struct obj*container,struct obj*o){append("container:%ld:%ld;",(long)(container-items),(long)(o-items));o->nobj=container->cobj;container->cobj=o;return o;}
int weight(struct obj*o){unsigned result=(unsigned)o->quan*3U+(unsigned)o->otyp;append("weight:%ld:%u;",(long)(o-items),result);return result;}
void make_grave(coordxy x,coordxy y,const char*text){append("grave:%d:%d:%d;",x,y,text!=NULL);}
boolean occupied(coordxy x,coordxy y){append("occupied:%d:%d;",x,y);return options[5];}
boolean enexto(coord*c,coordxy x,coordxy y,struct permonst*p){append("enexto:%d:%d:%d;",x,y,p?monsndx(p):-1);c->x=x+1;c->y=y+1;return !options[6];}
struct obj*sobj_at(int type,coordxy x,coordxy y){append("sobj:%d:%d:%d;",type,x,y);return options[7]?newitem(type):NULL;}
struct monst*revive(struct obj*o,boolean ghost){append("revive:%ld:%d;",(long)(o-items),ghost);return options[8]?&monsters[0]:NULL;}
struct permonst *mkclass(char sym,int flag){append("class:%d:%d;",sym,flag);return options[9]?NULL:&mons[PM_HUMAN];}
int ndemon(aligntyp alignment){append("ndemon:%d;",alignment);return options[10];}
static struct trap trap;
struct trap*t_at(coordxy x,coordxy y){append("trap:%d:%d;",x,y);return options[11]?&trap:NULL;}
void del_engr_at(coordxy x,coordxy y){append("engr:%d:%d;",x,y);}
unsigned induced_align(int chance){append("align:%d;",chance);return options[12];}
void priestini(d_level*l,struct mkroom*r,int x,int y,boolean sanctum){if(options[15]){options[15]=0;growth_block=malloc(40UL*1024*1024);if(!growth_block)abort();memset(growth_block,0x5a,40UL*1024*1024);append("growth:priest;");}append("priest:%d:%d:%ld:%d:%d:%d;",l->dnum,l->dlevel,(long)(r-svr.rooms),x,y,sanctum);r->resident=&monsters[0];}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
boolean In_hell(d_level*l){append("hell:%d:%d;",l->dnum,l->dlevel);return options[13];}
static long roomid(struct mkroom*r){uintptr_t p=(uintptr_t)r,base=(uintptr_t)svr.rooms,sub=(uintptr_t)subrooms;if(p>=base&&p<base+sizeof svr.rooms)return (long)((p-base)/sizeof *r);if(p>=sub&&p<sub+sizeof subrooms)return 1000+(long)((p-sub)/sizeof *r);return -1;}
void sfo_int(NHFILE*f,int*p,const char*tag){append("sfoint:%d:%s;",*p,tag);memcpy(io+io_length,p,sizeof *p);io_length+=sizeof *p;if(options[14])*p=options[14]-1;}
void sfi_int(NHFILE*f,int*p,const char*tag){memcpy(p,io+io_position,sizeof *p);io_position+=sizeof *p;append("sfiint:%d:%s;",*p,tag);}
void sfo_mkroom(NHFILE*f,struct mkroom*r,const char*tag){append("sforoom:%ld:%s:%d;",roomid(r),tag,r->nsubrooms);memcpy(io+io_length,r,sizeof *r);io_length+=sizeof *r;}
void sfi_mkroom(NHFILE*f,struct mkroom*r,const char*tag){memcpy(r,io+io_position,sizeof *r);io_position+=sizeof *r;append("sfiroom:%ld:%s:%d;",roomid(r),tag,r->nsubrooms);}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/mkroom.c"
#define PRIVATE(n) n
#else
extern boolean teleport_mkroom_test_isbig(struct mkroom*),teleport_mkroom_test_invalid_shop_shape(struct mkroom*);
extern void teleport_mkroom_test_mkshop(void),teleport_mkroom_test_mkzoo(int),teleport_mkroom_test_mk_zoo_thronemon(coordxy,coordxy),teleport_mkroom_test_mkswamp(void),teleport_mkroom_test_mktemple(void),teleport_mkroom_test_save_room(NHFILE*,struct mkroom*),teleport_mkroom_test_rest_room(NHFILE*,struct mkroom*);
extern struct mkroom*teleport_mkroom_test_pick_room(boolean);
extern struct permonst*teleport_mkroom_test_morguemon(void),*teleport_mkroom_test_squadmon(void);
extern coord*teleport_mkroom_test_shrine_pos(int);
#define PRIVATE(n) teleport_mkroom_test_##n
#endif
void probe_reset(unsigned seed){int i;if(growth_block){free(growth_block);growth_block=NULL;}objects_globals_init();monst_globals_init();memset(&svr,0,sizeof svr);memset(&svn,0,sizeof svn);memset(&gs,0,sizeof gs);memset(&gn,0,sizeof gn);memset(&svl,0,sizeof svl);memset(&svd,0,sizeof svd);memset(&svm,0,sizeof svm);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(subrooms,0,sizeof subrooms);memset(doors,0,sizeof doors);memset(fixture_stairs,0,sizeof fixture_stairs);memset(monsters,0,sizeof monsters);memset(items,0,sizeof items);memset(options,0,sizeof options);gs.subrooms=subrooms;svd.doors=doors;for(i=0;i<SIZE(svr.rooms);i++)svr.rooms[i].hx=-1;for(i=0;i<SIZE(subrooms);i++)subrooms[i].hx=-1;options[0]=1;options[1]=12;options[10]=NON_PM;options[12]=AM_LAWFUL;monster_count=item_count=0;random_state=seed;random_length=random_index=0;trace[0]=caller[0]=shoptype[0]=0;ubirthday=1777723200L;u.uz.dnum=1;u.uz.dlevel=4;astral_level.dnum=3;io_length=io_position=0;memset(&fixture_file,0,sizeof fixture_file);}
void probe_option(int i,int value){options[i]=value;}
void probe_birth(long value){ubirthday=value;}
void probe_shoptype(const char*s){flags.debug=s!=NULL;if(s)strcpy(shoptype,s);else shoptype[0]=0;}
void probe_room(int i,int lx,int ly,int hx,int hy,int type,int irregular,int doors_count){struct mkroom*r=&svr.rooms[i];memset(r,0,sizeof *r);r->lx=lx;r->ly=ly;r->hx=hx;r->hy=hy;r->rtype=type;r->orig_rtype=type;r->doorct=doors_count;r->fdoor=i;r->irregular=irregular;if(svn.nroom<=i)svn.nroom=i+1;svr.rooms[svn.nroom].hx=-1;doors[i].x=lx-1;doors[i].y=ly+1;}
void probe_subroom(int i,int parent,int lx,int ly,int hx,int hy){struct mkroom*r=&subrooms[i];memset(r,0,sizeof *r);r->lx=lx;r->ly=ly;r->hx=hx;r->hy=hy;svr.rooms[parent].sbrooms[(int)svr.rooms[parent].nsubrooms++]=r;if(gn.nsubroom<=i)gn.nsubroom=i+1;subrooms[gn.nsubroom].hx=-1;}
void probe_cell(int x,int y,int typ,int roomno,int edge){levl[x][y].typ=typ;levl[x][y].roomno=roomno;levl[x][y].edge=edge;}
void probe_grid(int typ,int roomno){int x,y;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=typ;levl[x][y].roomno=roomno;}}
void probe_stair(int i,int x,int y,int up){fixture_stairs[i].sx=x;fixture_stairs[i].sy=y;fixture_stairs[i].up=up;fixture_stairs[i].next=i?NULL:gs.stairs;gs.stairs=&fixture_stairs[i];}
void probe_vital(int i,int flags_value){svm.mvitals[i].mvflags=flags_value;}
void probe_maze(int value){svl.level.flags.is_maze_lev=value;}
int*probe_rng_pointer(void){return random_values;}void probe_rng_length(int n){random_length=n;}unsigned probe_rng_state(void){return random_state;}int probe_rng_count(void){return random_index;}
const char*probe_trace(void){return trace;}void probe_clear_trace(void){trace[0]=caller[0]=0;}
void*probe_pointer(int kind,int i){switch(kind){case 0:return &svr.rooms[i];case 1:return &subrooms[i];case 2:return &doors[i];case 3:return &fixture_file;case 4:return &levl[0][0];case 5:return io;case 7:return &monsters[i];default:return &items[i];}}
int probe_room_value(int sub,int i,int key){struct mkroom*r=sub?&subrooms[i]:&svr.rooms[i];switch(key){case 0:return r->lx;case 1:return r->hx;case 2:return r->ly;case 3:return r->hy;case 4:return r->rtype;case 5:return r->rlit;case 6:return r->needfill;case 7:return r->nsubrooms;case 8:return !r->resident?0:((uintptr_t)r->resident>=(uintptr_t)monsters&&(uintptr_t)r->resident<(uintptr_t)(monsters+SIZE(monsters)))?1+(int)(r->resident-monsters):-1;default:return roomid(r->sbrooms[key-9]);}}
int probe_count(int kind){return kind==0?svn.nroom:kind==1?gn.nsubroom:kind==2?monster_count:item_count;}
long probe_item(int i,int key){struct obj*o=&items[i];switch(key){case 0:return o->otyp;case 1:return o->quan;case 2:return o->owt;case 3:return o->spe;default:return o->cobj?(long)(o->cobj-items):-1;}}
int probe_monster_field(int i,int key){struct monst*m=&monsters[i];switch(key){case 0:return m->data?monsndx(m->data):-1;case 1:return m->mx;case 2:return m->my;case 3:return m->msleeping;default:return m->mpeaceful;}}
unsigned probe_level_flags(void){return svl.level.flags.has_court|(svl.level.flags.has_barracks<<1)|(svl.level.flags.has_zoo<<2)|(svl.level.flags.has_morgue<<3)|(svl.level.flags.has_swamp<<4)|(svl.level.flags.has_beehive<<5)|(svl.level.flags.has_temple<<6)|(svl.level.flags.graveyard<<7);}
size_t probe_io_length(void){return io_length;}size_t probe_io_position(void){return io_position;}void probe_rewind(void){io_position=0;}
void probe_poison_rooms(void){memset(svr.rooms,0xa5,sizeof svr.rooms);memset(subrooms,0xa5,sizeof subrooms);}
int probe_table(int i,int field){
#ifdef TELEPORT_REFERENCE_TU
 return field?squadprob[i].prob:squadprob[i].pm;
#else
 return 0;
#endif
}
long probe_action(int action,int a,int b,int c){struct mkroom*r=a>=0&&a<SIZE(svr.rooms)?&svr.rooms[a]:NULL;coord loc={b,c};struct permonst*p;switch(action){case 0:return PRIVATE(isbig)(r);case 1:do_mkroom(a);return 0;case 2:PRIVATE(mkshop)();return 0;case 3:return roomid(PRIVATE(pick_room)(a));case 4:PRIVATE(mkzoo)(a);return 0;case 5:PRIVATE(mk_zoo_thronemon)(a,b);return 0;case 6:fill_zoo(r);return 0;case 7:loc.x=8;loc.y=9;mkundead(&loc,b,c);return 0;case 8:p=PRIVATE(morguemon)();return p?monsndx(p):-1;case 9:p=antholemon();return p?monsndx(p):-1;case 10:PRIVATE(mkswamp)();return 0;case 11:{coord*q=PRIVATE(shrine_pos)(a);return ((long)(unsigned short)q->x<<16)|(unsigned short)q->y;}case 12:PRIVATE(mktemple)();return 0;case 13:return nexttodoor(a,b);case 14:return has_dnstairs(r);case 15:return has_upstairs(r);case 16:return somex(r);case 17:return somey(r);case 18:return inside_room(r,b,c);case 19:{int ok=somexy(r,&loc);return ((long)ok<<32)|((long)(unsigned short)loc.x<<16)|(unsigned short)loc.y;}case 20:{int ok=somexyspace(r,&loc);return ((long)ok<<32)|((long)(unsigned short)loc.x<<16)|(unsigned short)loc.y;}case 21:return roomid(search_special(a));case 22:p=courtmon();return p?monsndx(p):-1;case 23:p=PRIVATE(squadmon)();return p?monsndx(p):-1;case 24:PRIVATE(save_room)(&fixture_file,r);return 0;case 25:save_rooms(&fixture_file);return 0;case 26:PRIVATE(rest_room)(&fixture_file,r);return 0;case 27:rest_rooms(&fixture_file);return 0;case 28:return cmap_to_type(a);default:return PRIVATE(invalid_shop_shape)(r);}}
size_t probe_stack(void){return emscripten_stack_get_current();}
