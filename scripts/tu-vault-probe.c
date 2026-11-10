/* Controlled dependency fixture. Original vault algorithms are included only
 * in reference mode; the hybrid has no original source-TU C implementation. */
#include "hack.h"
#include <emscripten/heap.h>
#include <emscripten/stack.h>
#include <stdarg.h>
#include <stdlib.h>
#undef free
extern void free(void*);
__typeof__(u) u;__typeof__(gm) gm;__typeof__(gi) gi;__typeof__(gy) gy;__typeof__(svl) svl;__typeof__(svr) svr;__typeof__(svm) svm;__typeof__(svp) svp;__typeof__(svc) svc;__typeof__(gv) gv;__typeof__(flags) flags;__typeof__(iflags) iflags;__typeof__(program_state) program_state;
struct obj*uball;struct objclass objects[NUM_OBJECTS+1];struct permonst mons[NUMMONS+1];
const struct Gender genders[]={{"male","he","him","his",0,0},{"female","she","her","her",0,0},{"neuter","it","it","its",0,0}};
static struct monst monsters[4];static struct obj nodes[24];static struct trap traps[8];static int trap_live[8];
static seenV visibility[ROWNO][COLNO];static seenV*rows[ROWNO];
static char tracebuf[262144],snapshotbuf[131072],caller[128],answer[BUFSZ];
static int opts[40],rolls[4096],roll_count,roll_pos,alloc_count,free_count,extra_count;static unsigned rng_state;static void*growth;
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static int mid(struct monst*m){return !m?-1:m==&gy.youmonst?9:(m>=monsters&&m<monsters+4)?(int)(m-monsters):8;}
static int oid(struct obj*o){return !o?-1:(o>=nodes&&o<nodes+24)?(int)(o-nodes):99;}
static void callback(void){if(opts[30]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}if(opts[31]){opts[31]=0;logmsg("reentry:%d;",gd_sound());}}
void teleport_probe_free(void*p){if(p){free_count++;logmsg("free;");}free(p);}
#define free teleport_probe_free
static void message(const char*tag,const char*f,va_list ap){logmsg("%s:",tag);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);logmsg(";");iflags.last_msg++;callback();}
void panic(const char*f,...){abort();}void impossible(const char*f,...){va_list ap;va_start(ap,f);message("impossible",f,ap);va_end(ap);}
void pline(const char*f,...){va_list ap;va_start(ap,f);message("msg",f,ap);va_end(ap);}void pline_The(const char*f,...){va_list ap;va_start(ap,f);message("The",f,ap);va_end(ap);}
void You(const char*f,...){va_list ap;va_start(ap,f);message("You",f,ap);va_end(ap);}void Your(const char*f,...){va_list ap;va_start(ap,f);message("Your",f,ap);va_end(ap);}
void You_hear(const char*f,...){va_list ap;va_start(ap,f);message("hear",f,ap);va_end(ap);}void You_see(const char*f,...){va_list ap;va_start(ap,f);message("see",f,ap);va_end(ap);}void verbalize(const char*f,...){va_list ap;va_start(ap,f);message("say",f,ap);va_end(ap);}
boolean debugcore(const char*f,boolean b){(void)f;if(opts[0])logmsg("debug:%d;",b);return opts[0];}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*f,int line,const char*fn){const char*p=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:f,line,fn);}
int(rn2)(int n){unsigned v;if(n<=0)abort();rng_state=rng_state*1664525U+1013904223U;v=(unsigned)(roll_pos<roll_count?rolls[roll_pos]:rng_state)%n;roll_pos++;logmsg("rng:%d:%u@%s;",n,v,caller);return v;}
long*alloc(unsigned n){alloc_count++;logmsg("alloc:%u;",n);void*p=malloc(n);if(!p)abort();return p;}
struct mextra*newmextra(void){extra_count++;logmsg("extra;");return calloc(1,sizeof(struct mextra));}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}void assign_level(d_level*a,d_level*b){*a=*b;}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
int canseemon(struct monst*m){(void)m;return opts[1];}int sensemon(struct monst*m){(void)m;return opts[2];}int mon_visible(struct monst*m){(void)m;return opts[3];}
int Mgender(struct monst*m){return m->female?FEMALE:MALE;}int pronoun_gender(struct monst*m,unsigned f){(void)m;(void)f;return opts[4];}
char*Monnam(struct monst*m){return mid(m)==0?"The guard":"The monster";}char*Some_Monnam(struct monst*m){return Monnam(m);}char*noit_Monnam(struct monst*m){return Monnam(m);}char*noit_mon_nam(struct monst*m){return mid(m)==0?"the guard":"the monster";}
const char*pmname(struct permonst*p,int g){(void)p;(void)g;return "guard";}const char*mimic_obj_name(struct monst*m){(void)m;return "box";}
char*makeplural(const char*s){static char buf[BUFSZ];snprintf(buf,sizeof buf,"%ss",s);return buf;}char*an(const char*s){static char buf[BUFSZ];snprintf(buf,sizeof buf,"a %s",s);return buf;}char*simpleonames(struct obj*o){(void)o;return "boulder";}
void unset_seenv(struct rm*r,coordxy x,coordxy y,coordxy xx,coordxy yy){r->seenv=0;logmsg("unsee:%d:%d:%d:%d;",x,y,xx,yy);}
void yelp(struct monst*m){logmsg("yelp:%d;",mid(m));}
void newsym(coordxy x,coordxy y){logmsg("newsym:%d:%d:%d;",x,y,gv.viz_array[y][x]);callback();}
void del_engr_at(coordxy x,coordxy y){logmsg("engr:%d:%d;",x,y);}void map_invisible(coordxy x,coordxy y){logmsg("invisible:%d:%d;",x,y);}
void map_location(coordxy x,coordxy y,int mode){logmsg("map:%d:%d:%d;",x,y,mode);}
void recalc_block_point(coordxy x,coordxy y){logmsg("reblock:%d:%d;",x,y);}void block_point(int x,int y){logmsg("block:%d:%d;",x,y);}void unblock_point(int x,int y){logmsg("unblock:%d:%d;",x,y);}
void xy_set_wall_state(coordxy x,coordxy y){logmsg("wall:%d:%d;",x,y);levl[x][y].wall_info=3;}
void spot_stop_timers(coordxy x,coordxy y,short k){logmsg("timers:%d:%d:%d;",x,y,k);}
void place_monster(struct monst*m,coordxy x,coordxy y){logmsg("monplace:%d:%d:%d;",mid(m),x,y);m->mx=x;m->my=y;svl.level.monsters[x][y]=m;}
void m_into_limbo(struct monst*m){logmsg("limbo:%d;",mid(m));if(isok(m->mx,m->my))svl.level.monsters[m->mx][m->my]=0;m->mx=m->my=0;}
boolean rloc(struct monst*m,unsigned f){logmsg("rloc:%d:%u;",mid(m),f);if(opts[5])return FALSE;if(isok(m->mx,m->my))svl.level.monsters[m->mx][m->my]=0;place_monster(m,30,10);return TRUE;}
void mnexto(struct monst*m,unsigned f){logmsg("mnexto:%d:%u;",mid(m),f);if(isok(m->mx,m->my))svl.level.monsters[m->mx][m->my]=0;place_monster(m,u.ux+1,u.uy);}
void mongone(struct monst*m){struct monst**p=&fmon;logmsg("mongone:%d;",mid(m));if(svl.level.monsters[m->mx][m->my]==m)svl.level.monsters[m->mx][m->my]=0;while(*p&&*p!=m)p=&(*p)->nmon;if(*p)*p=m->nmon;m->nmon=0;m->mhp=0;}
void relobj(struct monst*m,int mode,boolean b){logmsg("relobj:%d:%d:%d;",mid(m),mode,b);m->minvent=0;}
void mon_track_clear(struct monst*m){logmsg("track:%d;",mid(m));}
struct monst*makemon(struct permonst*p,coordxy x,coordxy y,mmflags_nht f){logmsg("makemon:%d:%d:%u;",x,y,f);if(opts[6])return 0;struct monst*m=&monsters[0];m->data=p;m->mhp=m->mhpmax=50;m->nmon=fmon;fmon=m;if(!m->mextra||!EGD(m))newegd(m);place_monster(m,x,y);return m;}
void set_malign(struct monst*m){logmsg("malign:%d;",mid(m));}void setmangry(struct monst*m,boolean b){logmsg("angry:%d:%d;",mid(m),b);m->mpeaceful=0;}
void reset_faint(void){logmsg("resetfaint;");}boolean is_fainted(void){return opts[7];}
void stop_occupation(void){logmsg("stop;");}void nomul(int n){logmsg("nomul:%d;",n);gm.multi=n;}void unmul(const char*s){logmsg("unmul:%s;",s?s:"(null)");}
void getlin(const char*q,char*out){logmsg("getlin:%s;",q);strcpy(out,answer);}
char*mungspaces(char*s){char*p=s;while(*p==' ')p++;if(p!=s)memmove(s,p,strlen(p)+1);return s;}
int strncmpi(const char*a,const char*b,int n){while(n--&&*a&&lowc(*a)==lowc(*b))a++,b++;return(unsigned char)lowc(*a)-(unsigned char)lowc(*b);}char lowc(char c){return c>='A'&&c<='Z'?c+32:c;}
int mon_wield_item(struct monst*m){logmsg("wield:%d;",mid(m));return 1;}
void adjalign(int n){logmsg("align:%d;",n);u.ualign.record+=n;}
void tele(void){logmsg("tele;");}
boolean um_dist(coordxy x,coordxy y,xint16 n){return dist2(x,y,u.ux,u.uy)>n*n;}
int dist2(coordxy x,coordxy y,coordxy xx,coordxy yy){return(x-xx)*(x-xx)+(y-yy)*(y-yy);}
char*in_rooms(coordxy x,coordxy y,int type){(void)type;static char room[2];room[0]=x>=10&&x<=11&&y>=10&&y<=11?ROOMOFFSET:0;room[1]=0;return room;}
boolean sticks(struct permonst*p){(void)p;return opts[8];}
boolean enexto(coord*out,coordxy x,coordxy y,struct permonst*p){(void)p;logmsg("enexto:%d:%d;",x,y);if(opts[9])return FALSE;out->x=x+1;out->y=y;return TRUE;}
struct trap*t_at(coordxy x,coordxy y){int i;for(i=0;i<8;i++)if(trap_live[i]&&traps[i].tx==x&&traps[i].ty==y)return &traps[i];return 0;}
void deltrap(struct trap*t){logmsg("deltrap:%d;",(int)(t-traps));trap_live[t-traps]=0;}
void remove_object(struct obj*o){struct obj**p=&svl.level.objects[o->ox][o->oy];logmsg("remove:%d;",oid(o));while(*p&&*p!=o)p=&(*p)->nexthere;if(*p)*p=o->nexthere;o->nexthere=0;o->where=OBJ_FREE;}
void freeinv(struct obj*o){struct obj**p=&gi.invent;logmsg("freeinv:%d;",oid(o));while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;o->nobj=0;o->where=OBJ_FREE;}
void obj_extract_self(struct obj*o){logmsg("extract:%d;",oid(o));if(o->where==OBJ_FLOOR)remove_object(o);else if(o->where==OBJ_INVENT)freeinv(o);else if(o->where==OBJ_MINVENT){int i;for(i=0;i<4;i++){struct obj**p=&monsters[i].minvent;while(*p&&*p!=o)p=&(*p)->nobj;if(*p){*p=o->nobj;break;}}o->nobj=0;o->where=OBJ_FREE;}}
void place_object(struct obj*o,coordxy x,coordxy y){logmsg("objplace:%d:%d:%d;",oid(o),x,y);o->ox=x;o->oy=y;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;o->where=OBJ_FLOOR;}
void stackobj(struct obj*o){logmsg("stack:%d;",oid(o));}void obfree(struct obj*o,struct obj*merge){logmsg("obfree:%d:%d;",oid(o),oid(merge));o->otyp=0;o->quan=0;}
struct obj*sobj_at(int typ,coordxy x,coordxy y){struct obj*o;for(o=svl.level.objects[x][y];o;o=o->nexthere)if(o->otyp==typ)return o;return 0;}struct obj*g_at(coordxy x,coordxy y){return sobj_at(GOLD_PIECE,x,y);}
void fracture_rock(struct obj*o){logmsg("fracture:%d;",oid(o));o->otyp=ROCK;}
int add_to_minv(struct monst*m,struct obj*o){logmsg("minv:%d:%d;",mid(m),oid(o));o->where=OBJ_MINVENT;o->nobj=m->minvent;m->minvent=o;return 0;}
void mpickgold(struct monst*m){struct obj*o;logmsg("pickgold:%d;",mid(m));while((o=g_at(m->mx,m->my))!=0){obj_extract_self(o);add_to_minv(m,o);}newsym(m->mx,m->my);}
long money_cnt(struct obj*o){long v=0;for(;o;o=o->nobj)if(o->otyp==GOLD_PIECE)v+=o->quan;return v;}
long contained_gold(struct obj*o,boolean unknown){logmsg("contained:%d:%d;",oid(o),unknown);return money_cnt(o->cobj);}
const char*currency(long amount){return amount==1?"gold piece":"gold pieces";}
void make_grave(coordxy x,coordxy y,const char*s){logmsg("grave:%d:%d:%s;",x,y,s);}
struct obj*m_carrying(struct monst*m,int type){struct obj*o;for(o=m->minvent;o;o=o->nobj)if(o->otyp==type)return o;return 0;}
char*x_monnam(struct monst*m,int a,const char*s,int b,boolean c){(void)m;(void)a;(void)b;(void)c;static char buf[100];snprintf(buf,sizeof buf,"an %s guard",s);return buf;}
char*upstart(char*s){if(*s>='a'&&*s<='z')*s-=32;return s;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/vault.c"
#else
extern boolean teleport_vault_test_clear_fcorr(struct monst*,boolean),teleport_vault_test_in_fcorridor(struct monst*,coordxy,coordxy),teleport_vault_test_find_guard_dest(struct monst*,coordxy*,coordxy*);
extern void teleport_vault_test_blackout(coordxy,coordxy),teleport_vault_test_restfakecorr(struct monst*),teleport_vault_test_parkguard(struct monst*),teleport_vault_test_move_gold(struct obj*,int),teleport_vault_test_wallify_vault(struct monst*),teleport_vault_test_gd_mv_monaway(struct monst*,int,int),teleport_vault_test_gd_pick_corridor_gold(struct monst*,int,int),teleport_vault_test_gd_letknow(struct monst*);
extern int teleport_vault_test_gd_move_cleanup(struct monst*,boolean,boolean);
#define clear_fcorr teleport_vault_test_clear_fcorr
#define in_fcorridor teleport_vault_test_in_fcorridor
#define find_guard_dest teleport_vault_test_find_guard_dest
#define blackout teleport_vault_test_blackout
#define restfakecorr teleport_vault_test_restfakecorr
#define parkguard teleport_vault_test_parkguard
#define move_gold teleport_vault_test_move_gold
#define wallify_vault teleport_vault_test_wallify_vault
#define gd_mv_monaway teleport_vault_test_gd_mv_monaway
#define gd_pick_corridor_gold teleport_vault_test_gd_pick_corridor_gold
#define gd_move_cleanup teleport_vault_test_gd_move_cleanup
#define gd_letknow teleport_vault_test_gd_letknow
#endif
#include "tu-vault-layout.h"
static coordxy destination[2];
void probe_reset(unsigned seed){int i,x,y;for(i=0;i<4;i++){if(monsters[i].mextra){if(EGD(&monsters[i]))free(EGD(&monsters[i]));free(monsters[i].mextra);}}if(growth)free(growth);growth=0;memset(monsters,0,sizeof monsters);memset(nodes,0,sizeof nodes);memset(&u,0,sizeof u);memset(&gm,0,sizeof gm);memset(&gi,0,sizeof gi);memset(&gy,0,sizeof gy);memset(&svl,0,sizeof svl);memset(&svr,0,sizeof svr);memset(&svm,0,sizeof svm);memset(&svp,0,sizeof svp);memset(&svc,0,sizeof svc);memset(&gv,0,sizeof gv);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(opts,0,sizeof opts);memset(trap_live,0,sizeof trap_live);memset(visibility,0,sizeof visibility);for(y=0;y<ROWNO;y++)rows[y]=visibility[y];gv.viz_array=rows;u.ux=u.uy=10;u.uz.dnum=1;u.uz.dlevel=2;u.uhp=u.mh=100;u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];mons[PM_HUMAN].msound=1;mons[PM_GUARD].msound=1;u.urooms[0]=ROOMOFFSET;svr.rooms[0].lx=svr.rooms[0].ly=10;svr.rooms[0].hx=svr.rooms[0].hy=11;svr.rooms[0].rtype=VAULT;for(i=0;i<4;i++){struct monst*m=&monsters[i];m->m_id=100+i;m->data=&mons[PM_GUARD];m->mhp=m->mhpmax=50;m->mpeaceful=m->mcansee=1;m->mx=9+i;m->my=10;if(i<3){m->mextra=calloc(1,sizeof(struct mextra));EGD(m)=calloc(1,sizeof(struct egd));EGD(m)->parentmid=m->m_id;EGD(m)->gdlevel=u.uz;EGD(m)->gdx=15;EGD(m)->gdy=10;EGD(m)->ogx=m->mx;EGD(m)->ogy=m->my;}}uball=0;opts[1]=opts[3]=1;strcpy(svp.plname,"Player");strcpy(answer,"Player");for(i=0;i<24;i++){nodes[i].otyp=GOLD_PIECE;nodes[i].quan=1;nodes[i].ox=nodes[i].oy=10;}objects[GOLD_PIECE].oc_class=COIN_CLASS;objects[ROCK].oc_class=GEM_CLASS;for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++){levl[x][y].typ=STONE;levl[x][y].lit=levl[x][y].waslit=1;levl[x][y].seenv=255;}for(x=9;x<=12;x++)for(y=9;y<=12;y++)levl[x][y].typ=(x==9||x==12)?VWALL:(y==9||y==12)?HWALL:ROOM;levl[15][10].typ=CORR;destination[0]=destination[1]=-9;alloc_count=free_count=extra_count=0;roll_count=roll_pos=0;rng_state=seed;tracebuf[0]=caller[0]=0;}
void probe_option(int k,long v){switch(k){case 100:u.ux=v;break;case 101:u.uy=v;break;case 102:u.urooms[0]=v?ROOMOFFSET:0;break;case 103:u.uinvault=v;break;case 104:program_state.stopprint=v;break;case 105:u.uswallow=v;break;case 106:u.uundetected=v;break;case 107:gy.youmonst.m_ap_type=v;break;case 108:gy.youmonst.mappearance=v;break;case 109:mons[PM_HUMAN].msound=v;break;case 110:gm.multi=v;break;case 111:svm.mvitals[PM_GUARD].died=v;break;case 112:svm.mvitals[PM_CROESUS].died=v;break;case 113:u.ualign.type=v;break;case 114:svc.context.polearm.hitmon=v<0?0:&monsters[v];break;case 115:uball=v<0?0:&nodes[v];break;case 116:flags.female=v;break;case 117:iflags.last_msg=v;break;case 118:u.uhp=v;break;case 119:u.umonnum=v?PM_RED_DRAGON:PM_HUMAN;break;default:opts[k]=v;break;}}
void probe_set_monster(int id,int key,long v){struct monst*m=&monsters[id];switch(key){case 0:m->isgd=v;break;case 1:m->mpeaceful=v;break;case 2:m->mcansee=v;break;case 3:m->mhp=v;break;case 4:m->mx=v;break;case 5:m->my=v;break;case 6:m->mtame=v;break;case 7:m->nmon=v<0?0:&monsters[v];break;case 8:if(v)fmon=m;else fmon=0;break;case 9:if(v)gm.migrating_mons=m;else gm.migrating_mons=0;break;case 10:svl.level.monsters[m->mx][m->my]=v?m:0;break;case 11:m->m_id=v;break;}}
void probe_egd(int id,int key,int v){struct egd*e=EGD(&monsters[id]);switch(key){case 0:e->fcbeg=v;break;case 1:e->fcend=v;break;case 2:e->gddone=v;break;case 3:e->witness=v;break;case 4:e->warncnt=v;break;case 5:e->dropgoldcnt=v;break;case 6:e->vroom=v;break;case 7:e->ogx=v;break;case 8:e->ogy=v;break;case 9:e->gdx=v;break;case 10:e->gdy=v;break;case 11:e->gdlevel.dnum=v;break;}}
void probe_corridor(int id,int index,int x,int y,int typ,int flags){struct fakecorridor*f=&EGD(&monsters[id])->fakecorr[index];f->fx=x;f->fy=y;f->ftyp=typ;f->flags=flags;}
void probe_cell(int x,int y,int key,int v){switch(key){case 0:levl[x][y].typ=v;break;case 1:levl[x][y].flags=v;break;case 2:levl[x][y].lit=v;break;case 3:levl[x][y].waslit=v;break;case 4:visibility[y][x]=v;break;}}
void probe_object(int id,int key,long v){struct obj*o=&nodes[id];switch(key){case 0:o->otyp=v;break;case 1:o->quan=v;break;case 2:o->ox=v;break;case 3:o->oy=v;break;case 4:o->where=v;break;case 5:o->cknown=v;break;case 6:o->nobj=v<0?0:&nodes[v];break;case 7:o->cobj=v<0?0:&nodes[v];break;case 8:gi.invent=v<0?0:&nodes[v];break;}}
void probe_trap(int i,int x,int y){traps[i].tx=x;traps[i].ty=y;trap_live[i]=1;}
void probe_prop(int p,long v){u.uprops[p].intrinsic=v;}
int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){roll_count=n;roll_pos=0;}char*probe_answer(void){return answer;}
long probe_action(int op,int id,int a,int b,int c){struct monst*m=id<0?0:&monsters[id];switch(op){case 0:newegd(m);break;case 1:free_egd(m);break;case 2:return clear_fcorr(m,a);case 3:blackout(a,b);break;case 4:restfakecorr(m);break;case 5:parkguard(m);break;case 6:return grddead(m);case 7:return in_fcorridor(m,a,b);case 8:{struct monst*p=findgd();return mid(p);}case 9:vault_summon_gd();break;case 10:return vault_occupied(u.urooms);case 11:uleftvault(m);break;case 12:return find_guard_dest(m,&destination[0],&destination[1]);case 13:invault();break;case 14:move_gold(&nodes[a],b);break;case 15:wallify_vault(m);break;case 16:gd_mv_monaway(m,a,b);break;case 17:gd_pick_corridor_gold(m,a,b);break;case 18:return gd_move_cleanup(m,a,b);case 19:gd_letknow(m);break;case 20:return gd_move(m);case 21:paygd(a);break;case 22:return hidden_gold(a);case 23:return gd_sound();case 24:vault_gd_watching(a);break;case 25:place_object(&nodes[a],b,c);break;}return 0;}
const char*probe_trace(void){return tracebuf;}
const char*probe_snapshot(void){int i,j,x,y;char*p=snapshotbuf;p+=sprintf(p,"u:%d:%d:%d:%d:%d;global:%d:%d:%d:%d:%d:%d;memory:%d:%d:%d;rng:%u:%d;dest:%d:%d;",u.ux,u.uy,u.uinvault,u.ualign.record,gv.vision_full_recalc,mid(fmon),mid(gm.migrating_mons),mid(svc.context.polearm.hitmon),oid(gi.invent),iflags.last_msg,program_state.stopprint,alloc_count,free_count,extra_count,rng_state,roll_pos,destination[0],destination[1]);for(i=0;i<4;i++){struct monst*m=&monsters[i];p+=sprintf(p,"m%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d;",i,m->mx,m->my,m->mux,m->muy,m->mhp,m->isgd,m->mpeaceful,m->weapon_check,mid(m->nmon),oid(m->minvent));if(m->mextra){p+=sprintf(p,"extra;");if(EGD(m)){struct egd*e=EGD(m);p+=sprintf(p,"e:%u:%d:%d:%d:%d:%d:%d:%d:%d:%d:%u:%u;",e->parentmid,e->fcbeg,e->fcend,e->vroom,e->gdx,e->gdy,e->ogx,e->ogy,e->warncnt,e->dropgoldcnt,e->gddone,e->witness);for(j=0;j<FCSIZ;j++)p+=sprintf(p,"f:%d:%d:%d:%u;",e->fakecorr[j].fx,e->fakecorr[j].fy,e->fakecorr[j].ftyp,e->fakecorr[j].flags);}}}for(i=0;i<24;i++){struct obj*o=&nodes[i];p+=sprintf(p,"o%d:%d:%d:%d:%ld:%d:%d:%d:%d;",i,o->otyp,o->ox,o->oy,o->quan,o->where,o->cknown,oid(o->nobj),oid(o->cobj));}for(x=0;x<COLNO;x++)for(y=0;y<ROWNO;y++)p+=sprintf(p,"g:%d:%u:%u:%u:%u:%u:%d:%d;",levl[x][y].typ,levl[x][y].flags,levl[x][y].lit,levl[x][y].waslit,levl[x][y].seenv,visibility[y][x],mid(svl.level.monsters[x][y]),oid(svl.level.objects[x][y]));for(i=0;i<8;i++)p+=sprintf(p,"t:%d;",trap_live[i]);return snapshotbuf;}
uintptr_t probe_stack(void){return(uintptr_t)emscripten_stack_get_current();}
