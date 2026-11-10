/* Controlled external world; unchanged dig.c is the reference policy. */
#include "hack.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
__typeof__(u) u;__typeof__(svc) svc;__typeof__(svm) svm;__typeof__(svl) svl;__typeof__(gy) gy;__typeof__(gd) gd;__typeof__(gv) gv;__typeof__(gm) gm;__typeof__(gn) gn;__typeof__(go) go;__typeof__(flags) flags;__typeof__(iflags) iflags;__typeof__(disp) disp;__typeof__(gu) gu;__typeof__(svd) svd;__typeof__(gt) gt;const __typeof__(cg) cg={0};
struct obj *uwep,*uarmf,*uarmh,*uball,*uchain;
const struct Gender genders[4]={{.his="his"},{.his="her"},{.his="its"},{.his="their"}};
const schar dirs_ord[N_DIRS]={DIR_W,DIR_N,DIR_E,DIR_S,DIR_NW,DIR_NE,DIR_SE,DIR_SW};
const schar xdir[N_DIRS_Z]={-1,-1,0,1,1,1,0,-1,0,0},ydir[N_DIRS_Z]={0,-1,-1,-1,0,1,1,1,0,0};
static struct obj*nodes[128];static struct obj saved[128];static struct monst*monsters[16];static struct trap trapdata[COLNO][ROWNO];static unsigned char trapactive[COLNO][ROWNO];static unsigned char vision[ROWNO][COLNO],*visionrows[ROWNO];static stairway stairs;static coord point;static boolean dealloced;static char msg[BUFSZ],tracebuf[1048576],caller[256];static int opts[128],rolls[4096],nr,ri,made,freed,nmon;static unsigned seed;static long ret[256],timer[128];static long timeout_value;static void*growth;
static int oid(struct obj*o){int i;if(!o)return-1;for(i=0;i<made;i++)if(nodes[i]==o)return i;return-2;}static int mid(struct monst*m){int i;if(!m)return-1;if(m==&gy.youmonst)return-2;for(i=0;i<nmon;i++)if(monsters[i]==m)return i;return-3;}
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static void callback(int n){if(opts[120]==n&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("grow:%d;",n);}}
void panic(const char*f,...){va_list ap;va_start(ap,f);vfprintf(stderr,f,ap);va_end(ap);fflush(stderr);abort();}
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char*f,int line,const char*fn){snprintf(caller,sizeof caller,"%s:%d:%s",f,line,fn);}
static int draw(int n){unsigned v;if(n<=0)panic("bad rng %d",n);seed=seed*1664525U+1013904223U;v=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;logmsg("rng:%d:%u@%s;",n,v,caller);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}int(rnl)(int n){return draw(n);}int(d)(int n,int z){int total=0;while(n--)total+=draw(z)+1;return total;}
boolean debugcore(const char*file,boolean yes){logmsg("debug:%s:%d;",file,yes);return opts[1];}
static void display(winid w,boolean b){logmsg("display:%d:%d;",w,b);}static void delay(void){logmsg("delay;");}__typeof__(windowprocs) windowprocs={.win_display_nhwindow=display,.win_delay_output=delay};winid WIN_MESSAGE=1;
void pline(const char*f,...){va_list ap;logmsg("pline:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void pline_The(const char*f,...){va_list ap;logmsg("pline_The:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void You(const char*f,...){va_list ap;logmsg("You:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void Your(const char*f,...){va_list ap;logmsg("Your:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void You_hear(const char*f,...){va_list ap;logmsg("You_hear:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void You_feel(const char*f,...){va_list ap;logmsg("You_feel:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void You_cant(const char*f,...){va_list ap;logmsg("You_cant:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void There(const char*f,...){va_list ap;logmsg("There:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void verbalize(const char*f,...){va_list ap;logmsg("verbalize:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}
void impossible(const char*f,...){va_list ap;logmsg("impossible:");va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");iflags.last_msg=0;}

static int foreign_occupation(void){return 314;}
void set_occupation(int(*fn)(void),const char*s,cmdcount_nht n){logmsg("occupation:%s:%ld;",s,n);go.occupation=fn;}
struct monst*get_iter_mons(boolean(*fn)(struct monst*)){int i;for(i=0;i<nmon;i++)if(fn(monsters[i]))return monsters[i];return NULL;}
int doapply(void){return 7;}void cmdq_add_ec(int k,int(*fn)(void)){logmsg("queue:%d:%d;",k,fn==doapply);}void cmdq_add_key(int k,char ch){logmsg("key:%d:%d;",k,ch);}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}void assign_level(d_level*a,d_level*b){*a=*b;}void get_level(d_level*a,int n){a->dnum=u.uz.dnum;a->dlevel=n;logmsg("getlevel:%d;",n);}
struct trap*t_at(coordxy x,coordxy y){logmsg("trap:%d:%d;",x,y);return isok(x,y)&&trapactive[x][y]?&trapdata[x][y]:NULL;}
struct trap*maketrap(coordxy x,coordxy y,int type){struct trap*t;logmsg("maketrap:%d:%d:%d;",x,y,type);if(opts[2])return NULL;t=&trapdata[x][y];memset(t,0,sizeof*t);trapactive[x][y]=1;t->tx=x;t->ty=y;t->ttyp=type;callback(1);return t;}
void deltrap(struct trap*t){int i;logmsg("deltrap:%d:%d;",t->tx,t->ty);for(i=0;i<N_DIRS;i++){coordxy x=t->tx+xdir[i],y=t->ty+ydir[i];if(isok(x,y)&&trapactive[x][y])trapdata[x][y].conjoined&=~(1<<DIR_180(i));}trapactive[t->tx][t->ty]=0;t->conjoined=0;callback(2);}boolean delfloortrap(struct trap*t){if(t)deltrap(t);return TRUE;}
static struct obj*new_fixture_obj(int type,int x,int y){struct obj*o;if(made>=128)panic("fixture object limit");o=calloc(1,sizeof*o);o->o_id=made+100;o->quan=1;o->otyp=type;o->oclass=objects[type].oc_class;o->corpsenm=NON_PM;o->where=OBJ_FREE;o->ox=x;o->oy=y;o->owt=objects[type].oc_weight;nodes[made++]=o;return o;}
void obj_extract_self(struct obj*o){struct obj**p;logmsg("extract:%d:%d;",oid(o),o->where);if(o->where==OBJ_FLOOR){for(p=&fobj;*p;p=&(*p)->nobj)if(*p==o){*p=o->nobj;break;}for(p=&svl.level.objects[o->ox][o->oy];*p;p=&(*p)->nexthere)if(*p==o){*p=o->nexthere;break;}}else if(o->where==OBJ_BURIED){for(p=&svl.level.buriedobjlist;*p;p=&(*p)->nobj)if(*p==o){*p=o->nobj;break;}}else if(o->where==OBJ_CONTAINED){for(p=&o->ocontainer->cobj;*p;p=&(*p)->nobj)if(*p==o){*p=o->nobj;break;}}o->nobj=o->nexthere=NULL;o->where=OBJ_FREE;callback(3);}
void place_object(struct obj*o,coordxy x,coordxy y){logmsg("place:%d:%d:%d;",oid(o),x,y);o->where=OBJ_FLOOR;o->ox=x;o->oy=y;o->nobj=fobj;fobj=o;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;callback(4);}
void add_to_buried(struct obj*o){logmsg("buried:%d;",oid(o));o->where=OBJ_BURIED;o->nobj=svl.level.buriedobjlist;svl.level.buriedobjlist=o;}
void obfree(struct obj*o,struct obj*merge){int i=oid(o);logmsg("free:%d:%d;",i,oid(merge));if(i<0)panic("unknown object");saved[i]=*o;nodes[i]=NULL;free(o);freed++;callback(5);}void delobj(struct obj*o){obj_extract_self(o);obfree(o,NULL);}void dropx(struct obj*o){if(o==uwep)uwep=NULL;obj_extract_self(o);place_object(o,u.ux,u.uy);}
struct obj*sobj_at(int type,coordxy x,coordxy y){struct obj*o;logmsg("sobj:%d:%d:%d;",type,x,y);if(!isok(x,y))return NULL;for(o=svl.level.objects[x][y];o;o=o->nexthere)if(o->otyp==type)return o;return NULL;}
struct obj*mksobj_at(int type,coordxy x,coordxy y,boolean init,boolean art){struct obj*o;logmsg("makeobj:%d:%d:%d:%d:%d;",type,x,y,init,art);o=new_fixture_obj(type,x,y);place_object(o,x,y);return o;}struct obj*mk_tt_object(int type,coordxy x,coordxy y){return mksobj_at(type,x,y,0,0);}struct obj*rnd_treefruit_at(coordxy x,coordxy y){return mksobj_at(APPLE,x,y,0,0);}
struct monst*makemon(struct permonst*p,coordxy x,coordxy y,mmflags_nht f){struct monst*m;logmsg("makemon:%d:%d:%d:%u;",p?p->pmidx:-1,x,y,f);if(opts[3])return NULL;if(nmon>=16)panic("fixture monster limit");m=calloc(1,sizeof*m);m->data=p?p:&mons[PM_HUMAN];m->mnum=m->data->pmidx;m->m_id=nmon+100;m->mx=x;m->my=y;m->mhp=100;monsters[nmon++]=m;if(isok(x,y))svl.level.monsters[x][y]=m;callback(6);return m;}
struct permonst*mkclass(char cls,int f){logmsg("mkclass:%d:%d;",cls,f);return &mons[opts[4]];}struct monst*shop_keeper(char roomno){logmsg("shop:%d;",roomno);return opts[5]>=0&&opts[5]<nmon?monsters[opts[5]]:NULL;}
boolean is_pool(coordxy x,coordxy y){return isok(x,y)&&(levl[x][y].typ==POOL||levl[x][y].typ==MOAT||levl[x][y].typ==WATER);}boolean is_moat(coordxy x,coordxy y){return isok(x,y)&&levl[x][y].typ==MOAT;}boolean is_lava(coordxy x,coordxy y){return isok(x,y)&&(levl[x][y].typ==LAVAPOOL||levl[x][y].typ==LAVAWALL);}boolean is_ice(coordxy x,coordxy y){return isok(x,y)&&levl[x][y].typ==ICE;}boolean is_pool_or_lava(coordxy x,coordxy y){return is_pool(x,y)||is_lava(x,y);}boolean closed_door(coordxy x,coordxy y){return isok(x,y)&&levl[x][y].typ==DOOR&&(levl[x][y].doormask&(D_CLOSED|D_LOCKED));}
char*in_rooms(coordxy x,coordxy y,int type){static char no[2]={0,0},shop[2]={ROOMOFFSET,0};logmsg("rooms:%d:%d:%d;",x,y,type);callback(7);return opts[6]?shop:no;}
boolean find_drawbridge(coordxy*x,coordxy*y){logmsg("bridge:%d:%d;",*x,*y);*x+=opts[7];*y+=opts[8];return opts[9];}int is_drawbridge_wall(coordxy x,coordxy y){return levl[x][y].typ==DBWALL?0:-1;}boolean is_db_wall(coordxy x,coordxy y){return is_drawbridge_wall(x,y)>=0;}void destroy_drawbridge(coordxy x,coordxy y){logmsg("destroybridge:%d:%d;",x,y);levl[x][y].typ=ROOM;}
const char*trapname(int type,boolean article){static char b[4][40];static int n;char*p=b[n++%4];snprintf(p,40,"trap%d",type);return p;}const char*surface(coordxy x,coordxy y){return levl[x][y].typ==STONE?"rock":"floor";}const char*ceiling(coordxy x,coordxy y){return"ceiling";}const char*hliquid(const char*s){return s;}
boolean obj_resists(struct obj*o,int a,int b){logmsg("resist:%d:%d:%d;",oid(o),a,b);return opts[10];}boolean start_timer(long when,short kind,short type,anything*a){logmsg("timer:%ld:%d:%d:%d;",when,kind,type,oid(a->a_obj));timer[oid(a->a_obj)]=when;a->a_obj->timed++;return TRUE;}long stop_timer(short type,anything*a){long n=timer[oid(a->a_obj)];logmsg("stoptimer:%d:%d;",type,oid(a->a_obj));timer[oid(a->a_obj)]=0;a->a_obj->timed=0;return n;}
void remove_worn_item(struct obj*o,boolean b){logmsg("removeworn:%d:%d;",oid(o),b);o->owornmask=0;}void setmnotwielded(struct monst*m,struct obj*o){logmsg("unwield:%d:%d;",mid(m),oid(o));m->mw=NULL;o->owornmask=0;}void set_utrap(unsigned t,unsigned type){logmsg("utrap:%u:%u;",t,type);u.utrap=t;u.utraptype=type;}void reset_utrap(boolean b){logmsg("resettrap:%d;",b);u.utrap=0;}
void losehp(int n,const char*s,schar k){logmsg("hp:%d:%s:%d;",n,s,k);u.uhp-=n;}void nomul(int n){logmsg("nomul:%d;",n);gm.multi=n;}
char cmd_from_dir(int dir,int mode){return "hykulnjb><"[dir];}int movecmd(char ch,int mode){const char*p=strchr("hykulnjb><",ch);int n=p?p-"hykulnjb><":-1;logmsg("movecmd:%d:%d;",ch,mode);if(n<0)return 0;u.dx=xdir[n];u.dy=ydir[n];u.dz=n==8?1:n==9?-1:0;return n<8;}int dxdy_moveok(void){return !opts[11];}int getdir(const char*s){logmsg("getdir:%s;",s);u.dx=opts[12];u.dy=opts[13];u.dz=opts[14];return opts[15];}
int canseemon(struct monst*m){logmsg("seemon:%d;",mid(m));return opts[16];}boolean conjoined_pits(struct trap*a,struct trap*b,boolean reset){logmsg("conjoined:%d:%d:%d;",a?a->tx:-1,b?b->tx:-1,reset);return opts[17];}void set_wounded_legs(long side,int turns){logmsg("legs:%ld:%d;",side,turns);}boolean next_to_u(void){return !opts[18];}
schar acurr(int attr){logmsg("attr:%d;",attr);return opts[20+attr];}schar acurrstr(void){logmsg("attrstr;");return opts[20];}boolean has_ceiling(d_level*l){return !opts[27];}boolean unconscious(void){logmsg("unconscious;");return opts[28];}boolean is_fainted(void){logmsg("fainted;");return opts[29];}

void unpunish(void){logmsg("unpunish;");uball=uchain=NULL;}void punish(struct obj*o){logmsg("punish:%d;",oid(o));uball=o;}
char * An(const char * a0){logmsg("An:%s:;",(a0?a0:"NULL"));return "An";}
boolean Can_dig_down(d_level * a0){logmsg("Can_dig_down:%d:;",a0!=NULL);return (boolean)ret[1];}
boolean Is_botlevel(d_level * a0){logmsg("Is_botlevel:%d:;",a0!=NULL);return (boolean)ret[2];}
char * Monnam(struct monst * a0){logmsg("Monnam:%d:;",mid(a0));return "Monnam";}
boolean On_ladder(coordxy a0,coordxy a1){logmsg("On_ladder:%d:%d:;",(int)a0,(int)a1);return (boolean)ret[4];}
boolean On_stairs(coordxy a0,coordxy a1){logmsg("On_stairs:%d:%d:;",(int)a0,(int)a1);return (boolean)ret[5];}
char * Yobjnam2(struct obj * a0,const char * a1){logmsg("Yobjnam2:%d:%s:;",oid(a0),(a1?a1:"NULL"));return "Yobjnam2";}
int abon(void){logmsg("abon:;");return (int)ret[7];}
void add_damage(coordxy a0,coordxy a1,long a2){logmsg("add_damage:%d:%d:%ld:;",(int)a0,(int)a1,(long)a2);}
void adjalign(int a0){logmsg("adjalign:%d:;",(int)a0);}
const char * align_str(aligntyp a0){logmsg("align_str:%d:;",(int)a0);return "align_str";}
void altar_wrath(coordxy a0,coordxy a1){logmsg("altar_wrath:%d:%d:;",(int)a0,(int)a1);}
int altarmask_at(coordxy a0,coordxy a1){logmsg("altarmask_at:%d:%d:;",(int)a0,(int)a1);return (int)ret[12];}
char * an(const char * a0){logmsg("an:%s:;",(a0?a0:"NULL"));return "an";}
boolean angry_guards(boolean a0){logmsg("angry_guards:%d:;",(int)a0);return (boolean)ret[14];}
void angry_priest(void){logmsg("angry_priest:;");}
void b_trapped(const char * a0,int a1){logmsg("b_trapped:%s:%d:;",(a0?a0:"NULL"),(int)a1);}
const char * body_part(int a0){logmsg("body_part:%d:;",(int)a0);return "body_part";}
boolean break_statue(struct obj * a0){logmsg("break_statue:%d:;",oid(a0));return (boolean)ret[18];}
void breaksink(coordxy a0,coordxy a1){logmsg("breaksink:%d:%d:;",(int)a0,(int)a1);}
boolean can_reach_floor(boolean a0){logmsg("can_reach_floor:%d:;",(int)a0);return (boolean)ret[20];}
void cant_reach_floor(coordxy a0,coordxy a1,boolean a2,boolean a3,boolean a4){logmsg("cant_reach_floor:%d:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4);}
void cnv_trap_obj(int a0,int a1,struct trap * a2,boolean a3){logmsg("cnv_trap_obj:%d:%d:%d:%d:;",(int)a0,(int)a1,a2!=NULL,(int)a3);}
char * corpse_xname(struct obj * a0,const char * a1,unsigned int a2){logmsg("corpse_xname:%d:%s:%d:;",oid(a0),(a1?a1:"NULL"),(int)a2);return "corpse_xname";}
boolean costly_spot(coordxy a0,coordxy a1){logmsg("costly_spot:%d:%d:;",(int)a0,(int)a1);return (boolean)ret[24];}
int count_wsegs(struct monst * a0){logmsg("count_wsegs:%d:;",mid(a0));return (int)ret[25];}
const char * currency(long a0){logmsg("currency:%ld:;",(long)a0);return "currency";}
void cvt_sdoor_to_door(struct rm * a0){logmsg("cvt_sdoor_to_door:%d:;",a0!=NULL);}
int dbon(void){logmsg("dbon:;");return (int)ret[28];}
void del_engr_at(coordxy a0,coordxy a1){logmsg("del_engr_at:%d:%d:;",(int)a0,(int)a1);}
schar depth(d_level * a0){logmsg("depth:%d:;",a0!=NULL);return (schar)ret[30];}
void desecrate_altar(boolean a0,aligntyp a1){logmsg("desecrate_altar:%d:%d:;",(int)a0,(int)a1);}
int dmgval(struct obj * a0,struct monst * a1){logmsg("dmgval:%d:%d:;",oid(a0),mid(a1));return (int)ret[32];}
boolean do_attack(struct monst * a0){logmsg("do_attack:%d:;",mid(a0));return (boolean)ret[33];}
int does_block(int a0,int a1,struct rm * a2){logmsg("does_block:%d:%d:%d:;",(int)a0,(int)a1,a2!=NULL);return (int)ret[34];}
void dogushforth(int a0){logmsg("dogushforth:%d:;",(int)a0);}
void dotrap(struct trap * a0,unsigned int a1){logmsg("dotrap:%d:%d:;",a0!=NULL,(int)a1);}
void dryup(coordxy a0,coordxy a1,boolean a2){logmsg("dryup:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);}
void end_burn(struct obj * a0,boolean a1){logmsg("end_burn:%d:%d:;",oid(a0),(int)a1);}
void exercise(int a0,boolean a1){logmsg("exercise:%d:%d:;",(int)a0,(int)a1);}
void expels(struct monst * a0,struct permonst * a1,boolean a2){logmsg("expels:%d:%d:%d:;",mid(a0),a1!=NULL,(int)a2);}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logmsg("explode:%d:%d:%d:%d:%d:%d:;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);}
void feel_newsym(coordxy a0,coordxy a1){logmsg("feel_newsym:%d:%d:;",(int)a0,(int)a1);}
void feeltrap(struct trap * a0){logmsg("feeltrap:%d:;",a0!=NULL);}
boolean fire_damage(struct obj * a0,boolean a1,coordxy a2,coordxy a3){logmsg("fire_damage:%d:%d:%d:%d:;",oid(a0),(int)a1,(int)a2,(int)a3);return (boolean)ret[44];}
int fire_damage_chain(struct obj * a0,boolean a1,boolean a2,coordxy a3,coordxy a4){logmsg("fire_damage_chain:%d:%d:%d:%d:%d:;",oid(a0),(int)a1,(int)a2,(int)a3,(int)a4);return (int)ret[45];}
void flush_screen(int a0){logmsg("flush_screen:%d:;",(int)a0);}
void fracture_rock(struct obj * a0){logmsg("fracture_rock:%d:;",oid(a0));}
void goto_level(d_level * a0,boolean a1,boolean a2,boolean a3){logmsg("goto_level:%d:%d:%d:%d:;",a0!=NULL,(int)a1,(int)a2,(int)a3);}
boolean hard_helmet(struct obj * a0){logmsg("hard_helmet:%d:;",oid(a0));return (boolean)ret[49];}
boolean hideunder(struct monst * a0){logmsg("hideunder:%d:;",mid(a0));return (boolean)ret[50];}
void impact_drop(struct obj * a0,coordxy a1,coordxy a2,xint16 a3){logmsg("impact_drop:%d:%d:%d:%d:;",oid(a0),(int)a1,(int)a2,(int)a3);}
boolean in_town(coordxy a0,coordxy a1){logmsg("in_town:%d:%d:;",(int)a0,(int)a1);return (boolean)ret[52];}
xint16 ledger_no(d_level * a0){logmsg("ledger_no:%d:;",a0!=NULL);return (xint16)ret[53];}
void make_angry_shk(struct monst * a0,coordxy a1,coordxy a2){logmsg("make_angry_shk:%d:%d:%d:;",mid(a0),(int)a1,(int)a2);}
boolean may_dig(coordxy a0,coordxy a1){logmsg("may_dig:%d:%d:;",(int)a0,(int)a1);return (boolean)ret[55];}
void maybe_unhide_at(coordxy a0,coordxy a1){logmsg("maybe_unhide_at:%d:%d:;",(int)a0,(int)a1);}
boolean mb_trapped(struct monst * a0,boolean a1){logmsg("mb_trapped:%d:%d:;",mid(a0),(int)a1);return (boolean)ret[57];}
const char * mbodypart(struct monst * a0,int a1){logmsg("mbodypart:%d:%d:;",mid(a0),(int)a1);return "mbodypart";}
void migrate_to_level(struct monst * a0,xint16 a1,xint16 a2,coord * a3){logmsg("migrate_to_level:%d:%d:%d:%d:;",mid(a0),(int)a1,(int)a2,a3!=NULL);}
int minliquid(struct monst * a0){logmsg("minliquid:%d:;",mid(a0));return (int)ret[60];}
int mintrap(struct monst * a0,unsigned int a1){logmsg("mintrap:%d:%d:;",mid(a0),(int)a1);return (int)ret[61];}
char * mon_nam(struct monst * a0){logmsg("mon_nam:%d:;",mid(a0));return "mon_nam";}
void newsym(coordxy a0,coordxy a1){logmsg("newsym:%d:%d:;",(int)a0,(int)a1);}
void o_unleash(struct obj * a0){logmsg("o_unleash:%d:;",oid(a0));}
void obj_ice_effects(coordxy a0,coordxy a1,boolean a2){logmsg("obj_ice_effects:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);}
char * otense(struct obj * a0,const char * a1){logmsg("otense:%d:%s:;",oid(a0),(a1?a1:"NULL"));return "otense";}
void pay_for_damage(const char * a0,boolean a1){logmsg("pay_for_damage:%s:%d:;",(a0?a0:"NULL"),(int)a1);}
int pickup(int a0){logmsg("pickup:%d:;",(int)a0);return (int)ret[68];}
boolean pooleffects(boolean a0){logmsg("pooleffects:%d:;",(int)a0);return (boolean)ret[69];}
void recalc_block_point(coordxy a0,coordxy a1){logmsg("recalc_block_point:%d:%d:;",(int)a0,(int)a1);}
boolean rloc(struct monst * a0,unsigned int a1){logmsg("rloc:%d:%d:;",mid(a0),(int)a1);return (boolean)ret[71];}
void seetrap(struct trap * a0){logmsg("seetrap:%d:;",a0!=NULL);}
char * shkname(struct monst * a0){logmsg("shkname:%d:;",mid(a0));return "shkname";}
void shopdig(int a0){logmsg("shopdig:%d:;",(int)a0);}
char * simpleonames(struct obj * a0){logmsg("simpleonames:%d:;",oid(a0));return "simpleonames";}
void spot_checks(coordxy a0,coordxy a1,schar a2){logmsg("spot_checks:%d:%d:%d:;",(int)a0,(int)a1,(int)a2);}
void spoteffects(boolean a0){logmsg("spoteffects:%d:;",(int)a0);}
void stackobj(struct obj * a0){logmsg("stackobj:%d:;",oid(a0));}
stairway * stairway_at(coordxy a0,coordxy a1){logmsg("stairway_at:%d:%d:;",(int)a0,(int)a1);return NULL;}
long stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logmsg("stolen_value:%d:%d:%d:%d:%d:;",oid(a0),(int)a1,(int)a2,(int)a3,(int)a4);return (long)ret[80];}
void stop_occupation(void){logmsg("stop_occupation:;");}
void switch_terrain(void){logmsg("switch_terrain:;");}
boolean teleport_pet(struct monst * a0,boolean a1){logmsg("teleport_pet:%d:%d:;",mid(a0),(int)a1);return (boolean)ret[83];}
char * the(const char * a0){logmsg("the:%s:;",(a0?a0:"NULL"));return "the";}
void tmp_at(coordxy a0,coordxy a1){logmsg("tmp_at:%d:%d:;",(int)a0,(int)a1);}
void u_wipe_engr(int a0){logmsg("u_wipe_engr:%d:;",(int)a0);}
boolean uescaped_shaft(struct trap * a0){logmsg("uescaped_shaft:%d:;",a0!=NULL);return (boolean)ret[87];}
void unblock_point(int a0,int a1){logmsg("unblock_point:%d:%d:;",(int)a0,(int)a1);}
void update_inventory(void){logmsg("update_inventory:;");}
boolean uteetering_at_seen_pit(struct trap * a0){logmsg("uteetering_at_seen_pit:%d:;",a0!=NULL);return (boolean)ret[90];}
void wake_nearby(boolean a0){logmsg("wake_nearby:%d:;",(int)a0);}
void water_damage_chain(struct obj * a0,boolean a1){logmsg("water_damage_chain:%d:%d:;",oid(a0),(int)a1);}
int welded(struct obj * a0){logmsg("welded:%d:;",oid(a0));return (int)ret[93];}
boolean wield_tool(struct obj * a0,const char * a1){logmsg("wield_tool:%d:%s:;",oid(a0),(a1?a1:"NULL"));return (boolean)ret[94];}
char * xname(struct obj * a0){logmsg("xname:%d:;",oid(a0));return "xname";}
char * yname(struct obj * a0){logmsg("yname:%d:;",oid(a0));return "yname";}
char * yobjnam(struct obj * a0,const char * a1){logmsg("yobjnam:%d:%s:;",oid(a0),(a1?a1:"NULL"));return "yobjnam";}

#ifdef TELEPORT_REFERENCE_TU
#include "dig.c"
#else
extern boolean teleport_dig_test_rm_waslit(void);
#define rm_waslit teleport_dig_test_rm_waslit
extern void teleport_dig_test_mkcavepos(coordxy x, coordxy y, int dist, boolean waslit, boolean rockit);
#define mkcavepos teleport_dig_test_mkcavepos
extern void teleport_dig_test_mkcavearea(boolean rockit);
#define mkcavearea teleport_dig_test_mkcavearea
extern boolean teleport_dig_test_pick_can_reach(struct obj *pick, coordxy x, coordxy y);
#define pick_can_reach teleport_dig_test_pick_can_reach
extern int teleport_dig_test_dig(void);
#define dig teleport_dig_test_dig
extern boolean teleport_dig_test_furniture_handled(coordxy x, coordxy y, boolean madeby_u);
#define furniture_handled teleport_dig_test_furniture_handled
extern void teleport_dig_test_dig_up_grave(coord *cc);
#define dig_up_grave teleport_dig_test_dig_up_grave
extern boolean teleport_dig_test_watchman_canseeu(struct monst *mtmp);
#define watchman_canseeu teleport_dig_test_watchman_canseeu
extern int teleport_dig_test_adj_pit_checks(coord *cc, char *msg);
#define adj_pit_checks teleport_dig_test_adj_pit_checks
extern void teleport_dig_test_pit_flow(struct trap *trap, schar filltyp);
#define pit_flow teleport_dig_test_pit_flow
#endif
#include "tu-dig-layout.h"

static struct monst*actor(int n){return n==-2?&gy.youmonst:n>=0&&n<nmon?monsters[n]:NULL;}
static int occupation_kind(void){
#ifdef TELEPORT_REFERENCE_TU
if(go.occupation==dig)return 1;
#else
extern uint64_t teleport_dig_callback_pointer(int);if((uint64_t)(uintptr_t)go.occupation==teleport_dig_callback_pointer(0))return 1;
#endif
return go.occupation==foreign_occupation?2:go.occupation?3:0;}
void probe_reset(unsigned initial_seed){int i,x,y;for(i=0;i<made;i++)free(nodes[i]);for(i=0;i<nmon;i++)free(monsters[i]);if(growth)free(growth);growth=NULL;memset(nodes,0,sizeof nodes);memset(monsters,0,sizeof monsters);memset(saved,0,sizeof saved);memset(timer,0,sizeof timer);memset(&u,0,sizeof u);memset(&svc,0,sizeof svc);memset(&svm,0,sizeof svm);memset(&svl,0,sizeof svl);memset(&gy,0,sizeof gy);memset(&gd,0,sizeof gd);memset(&gv,0,sizeof gv);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&go,0,sizeof go);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&gu,0,sizeof gu);memset(&svd,0,sizeof svd);memset(&gt,0,sizeof gt);memset(&point,0,sizeof point);memset(&stairs,0,sizeof stairs);memset(trapdata,0,sizeof trapdata);memset(trapactive,0,sizeof trapactive);memset(opts,0,sizeof opts);memset(ret,0,sizeof ret);memset(msg,0,sizeof msg);objects_globals_init();monst_globals_init();for(i=0;i<NUM_OBJECTS;i++)objects[i].oc_name_idx=objects[i].oc_descr_idx=i;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;levl[x][y].glyph=x*ROWNO+y;vision[y][x]=IN_SIGHT|COULD_SEE;}for(y=0;y<ROWNO;y++)visionrows[y]=vision[y];gv.viz_array=visionrows;u.ux=10;u.uy=10;u.uz.dnum=1;u.uz.dlevel=2;u.uhp=100;u.dx=1;svm.moves=100;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.m_id=1;gy.youmonst.mhp=100;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urace.mnum=PM_HUMAN;svc.context.digging.level=u.uz;svc.context.digging.pos.x=11;svc.context.digging.pos.y=10;point.x=10;point.y=10;air_level.dnum=9;air_level.dlevel=1;water_level.dnum=9;water_level.dlevel=2;earth_level.dnum=9;earth_level.dlevel=3;stronghold_level.dnum=9;stronghold_level.dlevel=4;valley_level.dnum=9;valley_level.dlevel=5;flags.verbose=1;opts[0]=1;opts[4]=PM_HUMAN;opts[5]=-1;opts[12]=1;opts[15]=1;opts[16]=1;for(i=20;i<26;i++)opts[i]=12;ri=nr=made=freed=nmon=0;seed=initial_seed;dealloced=0;timeout_value=0;uwep=uarmf=uarmh=uball=uchain=NULL;tracebuf[0]=caller[0]=0;}
void probe_option(int k,int v){opts[k]=v;}void probe_return(int k,long v){ret[k]=v;}int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nr=n;ri=0;}int probe_rng_count(void){return ri;}unsigned probe_rng_state(void){return seed;}const char*probe_trace(void){return tracebuf;}const char*probe_message(void){return msg;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
void probe_hero(int k,long value){switch(k){case 0:u.ux=value;break;case 1:u.uy=value;break;case 2:u.dx=value;break;case 3:u.dy=value;break;case 4:u.dz=value;break;case 5:u.utrap=value;break;case 6:u.utraptype=value;break;case 7:u.udaminc=value;break;case 8:u.uz.dnum=value;break;case 9:u.uz.dlevel=value;break;case 10:u.ualign.type=value;break;case 11:u.ualign.record=value;break;case 12:u.uswallow=value;break;case 13:u.uinwater=value;break;case 14:u.uundetected=value;break;case 15:gm.multi=value;break;case 16:svc.context.mon_moving=value;break;case 17:flags.verbose=value;break;case 18:flags.autodig=value;break;case 19:flags.female=value;break;case 20:iflags.last_msg=value;break;case 21:iflags.sanity_check=value;break;case 22:gd.did_dig_msg=value;break;case 23:gv.vision_full_recalc=value;break;case 24:u.ushops[0]=value;break;case 25:svm.moves=value;break;case 26:gu.urole.mnum=value;break;case 27:gu.urace.mnum=value;break;case 28:gy.youmonst.data=&mons[value];break;case 29:u.ustuck=actor(value);break;case 30:u.usteed=actor(value);break;case 31:u.uhp=value;break;}}
void probe_property(int id,int field,long value){if(field==0)u.uprops[id].intrinsic=value;else if(field==1)u.uprops[id].extrinsic=value;else u.uprops[id].blocked=value;}
void probe_digging(int field,long v){switch(field){case 0:svc.context.digging.effort=v;break;case 1:svc.context.digging.pos.x=v;break;case 2:svc.context.digging.pos.y=v;break;case 3:svc.context.digging.level.dnum=v;break;case 4:svc.context.digging.level.dlevel=v;break;case 5:svc.context.digging.lastdigtime=v;break;case 6:svc.context.digging.down=v;break;case 7:svc.context.digging.chew=v;break;case 8:svc.context.digging.warned=v;break;case 9:svc.context.digging.quiet=v;break;}}
void probe_level(int index,int dnum,int dlevel){d_level*ls[]={&air_level,&water_level,&earth_level,&stronghold_level,&valley_level};ls[index]->dnum=dnum;ls[index]->dlevel=dlevel;}
void probe_tile(int x,int y,int field,int value){switch(field){case 0:levl[x][y].typ=value;break;case 1:levl[x][y].flags=value;break;case 2:levl[x][y].horizontal=value;break;case 3:levl[x][y].lit=value;break;case 4:levl[x][y].waslit=value;break;case 5:levl[x][y].candig=value;break;case 6:levl[x][y].seenv=value;break;case 7:vision[y][x]=value;break;}}
void probe_level_flags(int field,int v){switch(field){case 0:svl.level.flags.arboreal=v;break;case 1:svl.level.flags.is_maze_lev=v;break;case 2:svl.level.flags.is_cavernous_lev=v;break;}}
int probe_new(int type,int x,int y){new_fixture_obj(type,x,y);return made-1;}
void probe_place(int slot,int where,int x,int y){struct obj*o=nodes[slot];if(o->where!=OBJ_FREE)obj_extract_self(o);if(where==OBJ_FLOOR)place_object(o,x,y);else if(where==OBJ_BURIED){o->ox=x;o->oy=y;add_to_buried(o);}else if(where==OBJ_CONTAINED){o->ocontainer=nodes[x];o->nobj=nodes[x]->cobj;nodes[x]->cobj=o;o->where=where;}else o->where=where;}
void probe_object(int slot,int field,long v){struct obj*o=nodes[slot];switch(field){case 0:o->otyp=v;o->oclass=objects[v].oc_class;break;case 1:o->spe=v;break;case 2:o->blessed=v;break;case 3:o->cursed=v;break;case 4:o->oeroded=v;break;case 5:o->oeroded2=v;break;case 6:o->lamplit=v;break;case 7:o->timed=v;break;case 8:o->no_charge=v;break;case 9:o->leashmon=v;break;case 10:o->age=v;break;case 11:o->owornmask=v;break;case 12:o->quan=v;break;case 13:o->invlet=v;break;case 14:o->ox=v;break;case 15:o->oy=v;break;case 16:o->where=v;break;case 17:o->ocarry=actor(v);break;}}
void probe_equipment(int index,int slot){struct obj*o=slot<0?NULL:nodes[slot];switch(index){case 0:uwep=o;break;case 1:uarmf=o;break;case 2:uarmh=o;break;case 3:uball=o;break;case 4:uchain=o;break;}}
int probe_new_monster(int type,int x,int y){makemon(&mons[type],x,y,0);return nmon-1;}void probe_mon_field(int slot,int field,int v){struct monst*m=actor(slot);switch(field){case 0:m->mcansee=v;break;case 1:m->mpeaceful=v;break;case 2:m->wormno=v;break;case 3:m->isshk=v;break;case 4:m->mundetected=v;break;case 5:m->mhp=v;break;case 6:m->data=&mons[v];break;case 7:m->mw=v>=0?nodes[v]:NULL;break;}}
void probe_trap(int x,int y,int type,int seen,int links){struct trap*t=&trapdata[x][y];memset(t,0,sizeof*t);t->tx=x;t->ty=y;t->ttyp=type;t->tseen=seen;t->conjoined=links;trapactive[x][y]=1;}
void probe_point(int x,int y){point.x=x;point.y=y;}void probe_timeout(long value){timeout_value=value;}
void probe_occupation(int kind,uint64_t raw){if(kind==0)go.occupation=NULL;else if(kind==2)go.occupation=foreign_occupation;else if(kind==3)go.occupation=(int(*)(void))(uintptr_t)raw;else{
#ifdef TELEPORT_REFERENCE_TU
go.occupation=dig;
#else
extern uint64_t teleport_dig_callback_pointer(int);go.occupation=(int(*)(void))(uintptr_t)teleport_dig_callback_pointer(0);
#endif
}}
long probe_occupation_call(void){return go.occupation?go.occupation():-99;}
long probe_action(int op,int a,int b,int c){anything arg;arg.a_obj=a>=0&&a<made?nodes[a]:NULL;switch(op){
case 0:return rm_waslit();
case 1:mkcavepos(a,b,c,opts[50],opts[51]);break;
case 2:mkcavearea(a);break;
case 3:return pick_can_reach(nodes[a],b,c);
case 4:return dig_typ(a<0?NULL:nodes[a],b,c);
case 5:return is_digging();
case 6:return dig_check(actor(a),b,c);
case 7:digcheck_fail_message(a,actor(b),point.x,point.y);break;
case 8:return dig();
case 9:return furniture_handled(a,b,c);
case 10:return holetime();
case 11:return fillholetyp(a,b,c);
case 12:digactualhole(a,b,actor(c),opts[52]);break;
case 13:liquid_flow(a,b,c,t_at(a,b),opts[54]?"Fixture flow of %s.":NULL);break;
case 14:return dighole(a,b,c?&point:NULL);
case 15:dig_up_grave(a?&point:NULL);break;
case 16:return use_pick_axe(nodes[a]);
case 17:return use_pick_axe2(nodes[a]);
case 18:return watchman_canseeu(actor(a));
case 19:watch_dig(actor(a),b,c,opts[53]);break;
case 20:return mdig_tunnel(actor(a));
case 21:draft_message(a);break;
case 22:zap_dig();break;
case 23:return adj_pit_checks(a?NULL:&point,msg);
case 24:pit_flow(t_at(a,b),c);break;
case 25:return oid(buried_ball(opts[55]?&svc.context.digging.pos:&point));
case 26:buried_ball_to_punishment();break;
case 27:buried_ball_to_freedom();break;
case 28:return oid(bury_an_obj(nodes[a],b==2?&svc.context.digging.down:b?NULL:&dealloced));
case 29:bury_objs(a,b);break;
case 30:unearth_objs(a,b);break;
case 31:rot_organic(&arg,timeout_value);break;
case 32:rot_corpse(&arg,timeout_value);break;
case 33:return wiz_debug_cmd_bury();
default:panic("bad action %d",op);}return 0;}

void*probe_pointer(int kind,int i){switch(kind){case 0:return &svc.context.digging;case 1:return levl;case 2:return &u;case 3:return nodes[i]?nodes[i]:&saved[i];case 4:return actor(i);case 5:return &point;case 6:return &dealloced;case 7:return &trapdata[i/ROWNO][i%ROWNO];case 8:return vision;default:return msg;}}
int probe_count(int k){return k==0?made:k==1?freed:nmon;}
long probe_scalar(int k){switch(k){case 0:return gd.did_dig_msg;case 1:return gv.vision_full_recalc;case 2:return iflags.last_msg;case 3:return disp.botl;case 4:return u.utrap;case 5:return u.utraptype;case 6:return u.uhp;case 7:return gm.multi;case 8:return occupation_kind();case 9:return oid(uball);case 10:return oid(uchain);case 11:return oid(uwep);case 12:return point.x;case 13:return point.y;case 14:return dealloced;case 15:return mid(u.ustuck);case 16:return mid(u.usteed);case 17:return u.uundetected;default:return 0;}}
long probe_timer(int i){return timer[i];}int probe_alive(int i){return nodes[i]!=NULL;}int probe_link(int i,int field){struct obj*o=nodes[i];if(!o)return-3;return oid(field==0?o->nobj:field==1?o->nexthere:o->cobj);}int probe_grid(int x,int y,int kind){if(kind==0)return oid(svl.level.objects[x][y]);if(kind==1)return mid(svl.level.monsters[x][y]);if(kind==2)return trapactive[x][y];return trapactive[x][y]?trapdata[x][y].conjoined:0;}
const char*probe_grid_state(void){static char out[131072];size_t len=0;int x,y;out[0]=0;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){if(svl.level.objects[x][y]||svl.level.monsters[x][y]||trapactive[x][y])len+=snprintf(out+len,sizeof out-len,"%d,%d:%d:%d:%d:%d:%d:%d:%d;",x,y,oid(svl.level.objects[x][y]),mid(svl.level.monsters[x][y]),trapactive[x][y],trapdata[x][y].ttyp,trapdata[x][y].tseen,trapdata[x][y].madeby_u,trapdata[x][y].conjoined);}return out;}
int probe_mon_identity(int i,int k){return k?oid(actor(i)->mw):actor(i)->data->pmidx;}
