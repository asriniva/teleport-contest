#include "hack.h"
#include "mfndpos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#undef free
extern void free(void*);
struct you u;
__typeof__(svl) svl;
__typeof__(svr) svr;
__typeof__(svm) svm;
__typeof__(svd) svd;
__typeof__(gi) gi;
__typeof__(flags) flags;
__typeof__(program_state) program_state;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(gc) gc;
__typeof__(gb) gb;
__typeof__(gt) gt;
__typeof__(gv) gv;
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
const schar xdir[]={-1,-1,0,1,1,1,0,-1},ydir[]={0,-1,-1,-1,0,1,1,1};
static struct monst monsters[24];
static struct obj objects_pool[32],hero_coin,priest_coin,wand;
static int opts[40],random_values[4096],random_length,random_index,made_count,object_count,free_count,location_calls;
static unsigned random_state;
static struct mfndposdata candidates;
static char tracebuf[2097152],statebuf[131072],caller[128],output[BUFSZ],inputbuf[BUFSZ];
static long cash,priest_cash,offer;
static seenV vision[ROWNO][COLNO],*vision_rows[ROWNO];
static void *growth;
static int mid(struct monst *m){return m?(int)(m-monsters):-1;}
static void append(const char *f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
void panic(const char *f,...){abort();}
#define MSG(fn) void fn(const char *f,...){char b[BUFSZ*3];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append(#fn ":%s;",b);}
MSG(pline) MSG(You) MSG(Your) MSG(You_feel) MSG(verbalize) MSG(impossible)
void livelog_printf(long mask,const char *f,...){char b[BUFSZ*2];va_list a;va_start(a,f);vsnprintf(b,sizeof b,f,a);va_end(a);append("livelog:%ld:%s;",mask,b);}
boolean rng_log_enabled(void){return opts[0];}
void rng_log_set_caller(const char *f,int line,const char *fn){const char *b=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:f,line,fn);}
static int draw(int n){int v;if(n<=0)abort();if(random_index<random_length)v=random_values[random_index]%n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}random_index++;return v;}
int (rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);return v;}
int (rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);return v;}
int (d)(int n,int x){int i,v=n;for(i=0;i<n;i++)v+=draw(x);append("d:%d:%d:%d@%s;",n,x,v,caller);return v;}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("nested-temple:%d;",temple_occupied(u.urooms));}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("grew:%d;",stage);}}
void teleport_probe_free(void *p){free_count++;callback(6);free(p);}
struct mextra *newmextra(void){struct mextra *m=calloc(1,sizeof *m);append("newextra;");callback(1);return m;}
void newemin(struct monst *m){if(!m->mextra)m->mextra=newmextra();if(!EMIN(m)){EMIN(m)=calloc(1,sizeof *EMIN(m));EMIN(m)->parentmid=m->m_id;}append("newemin:%d;",mid(m));}
long mon_allowflags(struct monst *m){append("allow:%d;",mid(m));return (long)0x8000000000200000UL;}
int mfndpos(struct monst *m,struct mfndposdata *out,long allow){append("mfndpos:%d:%ld:%d;",mid(m),allow,candidates.cnt);memcpy(out,&candidates,sizeof *out);callback(2);return candidates.cnt;}
void m_break_boulder(struct monst *m,coordxy x,coordxy y){append("boulder:%d:%d:%d;",mid(m),x,y);}
int m_move_aggress(struct monst *m,coordxy x,coordxy y){append("aggress:%d:%d:%d;",mid(m),x,y);return opts[1];}
void place_monster(struct monst *m,coordxy x,coordxy y){append("place:%d:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;svl.level.monsters[x][y]=m;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
int inhishop(struct monst *m){append("inshop:%d;",mid(m));return opts[2];}
void check_special_room(boolean b){append("special-room:%d;",b);}
char *in_rooms(coordxy x,coordxy y,int typ){static char room[2];append("inrooms:%d:%d:%d;",x,y,typ);room[0]=opts[3];room[1]=0;callback(8);return room;}
boolean on_level(d_level *a,d_level *b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
void assign_level(d_level *a,d_level *b){append("assign:%d:%d;",b->dnum,b->dlevel);*a=*b;}
boolean resist_conflict(struct monst *m){append("resist-conflict:%d;",mid(m));return opts[4];}
boolean monnear(struct monst *m,coordxy x,coordxy y){append("monnear:%d:%d:%d;",mid(m),x,y);return opts[5];}
int mattacku(struct monst *m){append("attacku:%d;",mid(m));return 1;}
boolean pm_good_location(coordxy x,coordxy y,struct permonst *p){append("goodloc:%d:%d:%d;",x,y,monsndx(p));return location_calls++>=opts[6];}
boolean rloc(struct monst *m,unsigned f){append("rloc:%d:%u;",mid(m),f);svl.level.monsters[m->mx][m->my]=NULL;m->mx=30;m->my=10;svl.level.monsters[30][10]=m;return TRUE;}
struct monst *makemon(struct permonst *p,coordxy x,coordxy y,mmflags_nht f){struct monst *m;append("makemon:%d:%d:%d:%lu;",monsndx(p),x,y,(unsigned long)f);if(opts[7])return NULL;if(made_count>=24)abort();m=&monsters[made_count++];memset(m,0,sizeof *m);m->data=p;m->m_id=100+mid(m);m->mx=x;m->my=y;m->mhp=m->mhpmax=20;m->mcanmove=m->mcansee=1;m->minvent=&priest_coin;m->nmon=fmon;fmon=m;svl.level.monsters[x][y]=m;if(f&MM_EPRI)newepri(m);if(f&MM_EMIN)newemin(m);callback(3);return m;}
void mon_learns_traps(struct monst *m,int traps){append("learn:%d:%d;",mid(m),traps);}
void set_malign(struct monst *m){append("malign:%d:%d;",mid(m),m->mpeaceful);}
struct obj *mongets(struct monst *m,int type){append("mongets:%d:%d;",mid(m),type);objects_pool[0].otyp=type;return &objects_pool[0];}
struct obj *mkobj(int cls,boolean init){struct obj *o;if(object_count>=32)abort();o=&objects_pool[object_count++];memset(o,0,sizeof *o);o->otyp=SPE_FORCE_BOLT;o->oclass=SPBOOK_CLASS;append("mkobj:%d:%d:%d;",cls,init,object_count);return o;}
int mpickobj(struct monst *m,struct obj *o){append("mpick:%d:%d;",mid(m),o?(int)(o-objects_pool):-1);return 1;}
struct obj *which_armor(struct monst *m,long mask){append("armor:%d:%ld;",mid(m),mask);return opts[8]?NULL:&objects_pool[31];}
void curse(struct obj *o){append("curse;");o->cursed=1;o->blessed=0;}
void uncurse(struct obj *o){append("uncurse;");o->cursed=0;}
const char *mon_pmname(struct monst *m){append("pmname:%d;",mid(m));return m->data->pmnames[m->female&&m->data->pmnames[FEMALE]?FEMALE:m->data->pmnames[MALE]?MALE:NEUTRAL];}
char *rndmonnam(char *code){append("rndname;");*code=opts[9];return "Bogusname";}
boolean bogon_is_pname(char c){return c&&strchr("-+=",c)?TRUE:FALSE;}
char *just_an(char *b,const char *s){append("article:%s;",s);strcpy(b,strchr("AEIOUaeiou",*s)?"an ":"a ");return b;}
const char *halu_gname(aligntyp a){append("godname:%d;",a);return a==A_NONE?"Moloch":a>0?"Law":a<0?"Chaos":"Neutral";}
char *Monnam(struct monst *m){append("Monnam:%d:%d;",mid(m),m->ispriest);callback(7);return "Fixture priest";}
char *mon_nam(struct monst *m){append("mon_nam:%d;",mid(m));return "fixture priest";}
int pronoun_gender(struct monst *m,unsigned flags){append("pronoun:%d:%u;",mid(m),flags);return opts[10]?3:m->female?1:0;}
int canseemon(struct monst *m){append("cansee:%d;",mid(m));return opts[11];}
int sensemon(struct monst *m){append("sense:%d;",mid(m));return opts[12];}
void record_achievement(schar a){append("achievement:%d;",a);}
void mapseen_temple(struct monst *m){append("mapseen:%d;",mid(m));}
const char *body_part(int p){return "spine";}
void nomul(int n){append("nomul:%d;",n);gm.multi=n;}
long money_cnt(struct obj *o){long n=o==gi.invent?cash:o==&priest_coin?priest_cash:0;append("money:%ld;",n);return n;}
const char *currency(long n){append("currency:%ld;",n);return "gold pieces";}
void money2u(struct monst *m,long n){append("money2u:%d:%ld;",mid(m),n);cash+=n;priest_cash-=n;}
void exercise(int a,boolean b){append("exercise:%d:%d;",a,b);}
long bribe(struct monst *m,const char *q){append("bribe:%d:%s:%ld;",mid(m),q,offer);cash-=offer;priest_cash+=offer;callback(4);return offer;}
void adjalign(int n){append("adjalign:%d;",n);u.ualign.record+=n;}
void incr_itimeout(long *p,int n){append("timeout:%ld:%d;",*p,n);*p+=n;}
boolean linedup(coordxy x1,coordxy y1,coordxy x2,coordxy y2,int flags){append("line:%d:%d:%d:%d:%d;",x1,y1,x2,y2,flags);gt.tbx=x1-x2;gt.tby=y1-y2;return opts[13];}
const char *a_gname_at(coordxy x,coordxy y){append("altarname:%d:%d;",x,y);return "A god";}
void buzz(int type,int n,coordxy x,coordxy y,int dx,int dy){append("buzz:%d:%d:%d:%d:%d:%d:%d:%d;",type,n,x,y,dx,dy,gc.current_wand==NULL,gb.buzzer==NULL);callback(5);}
void wakeup(struct monst *m,boolean via){append("wakeup:%d:%d;",mid(m),via);m->msleeping=0;}
void setmangry(struct monst *m,boolean via){append("angry:%d:%d;",mid(m),via);m->mpeaceful=0;}
void mongone(struct monst *m){append("gone:%d;",mid(m));m->mhp=0;svl.level.monsters[m->mx][m->my]=NULL;}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/priest.c"
#undef free
#else
extern boolean teleport_priest_test_histemple(struct monst*,coordxy,coordxy),teleport_priest_test_shrine(struct monst*);
#define histemple_at teleport_priest_test_histemple
#define has_shrine teleport_priest_test_shrine
#endif
#include "tu-priest-layout.h"
void probe_reset(unsigned seed){int i,x,y;for(i=0;i<24;i++)if(monsters[i].mextra){if(EPRI(&monsters[i]))free(EPRI(&monsters[i]));if(EMIN(&monsters[i]))free(EMIN(&monsters[i]));if(ESHK(&monsters[i]))free(ESHK(&monsters[i]));free(monsters[i].mextra);}if(growth)free(growth);growth=NULL;memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&svr,0,sizeof svr);memset(&svm,0,sizeof svm);memset(&svd,0,sizeof svd);memset(&gi,0,sizeof gi);memset(&flags,0,sizeof flags);memset(&program_state,0,sizeof program_state);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&gc,0,sizeof gc);memset(&gb,0,sizeof gb);memset(&gt,0,sizeof gt);memset(&gv,0,sizeof gv);memset(monsters,0,sizeof monsters);memset(objects_pool,0,sizeof objects_pool);memset(&candidates,0,sizeof candidates);memset(opts,0,sizeof opts);opts[0]=opts[11]=opts[13]=1;opts[3]=ROOMOFFSET;monst_globals_init();objects_globals_init();u.ux=u.uy=10;u.ulevel=u.ulevelpeak=10;u.ualign.type=A_LAWFUL;u.ualign.record=10;u.uz.dnum=1;u.uz.dlevel=2;u.urooms[0]=ROOMOFFSET;u.urooms[1]=0;gi.invent=&hero_coin;svr.rooms[0].rtype=TEMPLE;svr.rooms[0].lx=5;svr.rooms[0].hx=15;svr.rooms[0].ly=5;svr.rooms[0].hy=15;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=ROOM;vision[y][x]=IN_SIGHT|COULD_SEE;}for(y=0;y<ROWNO;y++)vision_rows[y]=vision[y];gv.viz_array=vision_rows;levl[12][10].typ=ALTAR;levl[12][10].altarmask=AM_SHRINE|AM_LAWFUL;sanctum_level.dnum=4;sanctum_level.dlevel=5;astral_level.dnum=6;astral_level.dlevel=7;svm.moves=100;cash=priest_cash=offer=0;made_count=object_count=free_count=location_calls=random_length=random_index=0;random_state=seed;output[0]=inputbuf[0]=tracebuf[0]=caller[0]=0;gc.current_wand=&wand;gb.buzzer=&monsters[23];}
const char *probe_trace(void){return tracebuf;}
void probe_option(int k,int v){opts[k]=v;}
int *probe_rng_pointer(void){return random_values;}
void probe_rng_length(int n){random_length=n;random_index=0;}
int probe_rng_count(void){return random_index;}
unsigned probe_rng_state(void){return random_state;}
void probe_add_monster(int index,int pm,int x,int y){struct monst *m=&monsters[index];m->data=&mons[pm];m->m_id=100+index;m->mx=x;m->my=y;m->mhp=m->mhpmax=20;m->mcanmove=m->mcansee=m->mpeaceful=1;m->minvent=&priest_coin;m->nmon=NULL;if(index)monsters[index-1].nmon=m;else fmon=m;svl.level.monsters[x][y]=m;if(made_count<=index)made_count=index+1;}
void probe_monster_field(int i,int k,unsigned long v){struct monst *m=&monsters[i];switch(k){case 0:m->m_id=v;break;case 1:m->mhp=v;break;case 2:m->ispriest=v;break;case 3:m->isminion=v;break;case 4:m->isshk=v;if(v){if(!m->mextra)m->mextra=newmextra();if(!ESHK(m))ESHK(m)=calloc(1,sizeof *ESHK(m));}break;case 5:m->mpeaceful=v;break;case 6:m->mconf=v;break;case 7:m->mcansee=v;break;case 8:m->msleeping=v;break;case 9:m->mcanmove=v;break;case 10:m->mfrozen=v;break;case 11:m->mflee=v;break;case 12:m->female=v;break;case 13:m->minvis=v;break;case 14:m->mtame=v;break;case 15:ESHK(m)->following=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:u.ux=v;break;case 1:u.uy=v;break;case 2:u.ualign.type=v;break;case 3:u.ualign.record=v;break;case 4:u.ulevelpeak=v;break;case 5:u.uconduct.gnostic=v;break;case 6:u.ublessed=v;break;case 7:u.ucleansed=v;break;case 8:u.uz.dnum=v;break;case 9:u.uz.dlevel=v;break;case 10:u.uroleplay.deaf=v;break;case 11:flags.debug=v;break;case 12:flags.verbose=v;break;case 13:program_state.gameover=v;break;case 14:cash=v;break;case 15:priest_cash=v;break;case 16:offer=v;break;case 17:svm.mvitals[PM_GHOST].born=v;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_epri(int i,int k,long v){struct monst *m=&monsters[i];if(!m->mextra)m->mextra=newmextra();if(!EPRI(m)){EPRI(m)=calloc(1,sizeof *EPRI(m));EPRI(m)->parentmid=m->m_id;}switch(k){case 0:EPRI(m)->shralign=v;break;case 1:EPRI(m)->shroom=v;break;case 2:EPRI(m)->shrpos.x=v;break;case 3:EPRI(m)->shrpos.y=v;break;case 4:EPRI(m)->shrlevel.dnum=v;break;case 5:EPRI(m)->shrlevel.dlevel=v;break;case 6:EPRI(m)->cheapskate_count=v;break;case 7:EPRI(m)->intone_time=v;break;case 8:EPRI(m)->enter_time=v;break;case 9:EPRI(m)->hostile_time=v;break;case 10:EPRI(m)->peaceful_time=v;break;}}
void probe_emin(int i,int align,int renegade){newemin(&monsters[i]);EMIN(&monsters[i])->min_align=align;EMIN(&monsters[i])->renegade=renegade;}
void probe_moves(long n){svm.moves=n;}
struct mfndposdata *probe_candidates_pointer(void){return &candidates;}
void probe_candidates_count(int n){candidates.cnt=n;}
void probe_room(int i,int type,int lx,int hx,int ly,int hy){svr.rooms[i].rtype=type;svr.rooms[i].lx=lx;svr.rooms[i].hx=hx;svr.rooms[i].ly=ly;svr.rooms[i].hy=hy;}
void probe_terrain(int x,int y,int type,int mask){levl[x][y].typ=type;levl[x][y].altarmask=mask;}
void probe_input(int k,const char *s){if(k==0)strncpy(u.urooms,s,sizeof u.urooms-1);else strncpy(u.urooms0,s,sizeof u.urooms0-1);}
long probe_action(int op,int index,int a,int b,int c,int d,int e,int f){struct monst *m=index<0?NULL:&monsters[index],*result=NULL;switch(op){case 0:newepri(m);break;case 1:free_epri(m);break;case 2:return move_special(m,a,b,c,d,m->mx,m->my,e,f);case 3:return temple_occupied(u.urooms);case 4:return histemple_at(m,a,b);case 5:return inhistemple(m);case 6:return pri_move(m);case 7:priestini(&u.uz,&svr.rooms[a],b,c,d);break;case 8:return mon_aligntyp(m);case 9:{char *p=priestname(m,a,b,output);append("returned:%d;",p==output);break;}case 10:return p_coaligned(m);case 11:return has_shrine(m);case 12:result=findpriest(a);return result?mid(result):-1;case 13:intemple(a);break;case 14:forget_temple_entry(m);break;case 15:priest_talk(m);break;case 16:result=mk_roamer(&mons[a],b,c,d,e);return result?mid(result):-1;case 17:reset_hostility(m);break;case 18:return in_your_sanctuary(m,a,b);case 19:ghod_hitsu(m);break;case 20:angry_priest();break;case 21:clearpriests();break;case 22:restpriest(m,a);break;}return 0;}
void *probe_pointer(int id,int index){struct monst *m=&monsters[index];switch(id){case 0:return m;case 1:return m->mextra;case 2:return m->mextra?EPRI(m):NULL;case 3:return m->mextra?EMIN(m):NULL;case 4:return &u;case 5:return output;case 6:return objects_pool;case 7:return &candidates;case 8:return &svr;case 9:return levl;}return NULL;}
int probe_free_count(void){return free_count;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char *probe_snapshot(void){char *p=statebuf;int i,j;p+=sprintf(p,"hero:%d:%d:%ld:%ld:%ld:%d:%ld:%ld:%ld:%ld:%d:%d:%s:%s;",u.ualign.type,u.ualign.record,u.uconduct.gnostic,cash,priest_cash,u.ublessed,u.ucleansed,svm.moves,gm.multi,HClairvoyant,gc.current_wand==&wand,gb.buzzer==&monsters[23],gm.multi_reason?gm.multi_reason:"",gn.nomovemsg?gn.nomovemsg:"");for(i=0;i<24;i++){struct monst *m=&monsters[i];p+=sprintf(p,"m%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%u:%d:%d:",i,m->data?monsndx(m->data):-1,m->mx,m->my,m->mhp,m->ispriest,m->isminion,m->isshk,m->mpeaceful,m->msleeping,m->mcanmove,m->mfrozen,m->mtame,m->mflee,m->m_id,m->nmon?mid(m->nmon):-1,m->mextra!=NULL);if(m->mextra&&EPRI(m)){unsigned char *r=(unsigned char*)EPRI(m);for(j=0;j<sizeof *EPRI(m);j++)p+=sprintf(p,"%02x",r[j]);}p+=sprintf(p,"/");if(m->mextra&&EMIN(m)){unsigned char *r=(unsigned char*)EMIN(m);for(j=0;j<sizeof *EMIN(m);j++)p+=sprintf(p,"%02x",r[j]);}p+=sprintf(p,";");}p+=sprintf(p,"free:%d;props:",free_count);for(i=0;i<sizeof u.uprops;i++)p+=sprintf(p,"%02x",((unsigned char*)u.uprops)[i]);p+=sprintf(p,";robe:%d:%d;",objects_pool[31].cursed,objects_pool[31].blessed);return statebuf;}
