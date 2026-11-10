/* Controlled ATTRIB dependency fixture. Original source is included only in
 * reference mode; every hybrid original function is a JS import. */
#include "hack.h"
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include <stdarg.h>
#include <stdlib.h>
__typeof__(u) u;__typeof__(gu) gu;__typeof__(gi) gi;__typeof__(gy) gy;__typeof__(gm) gm;__typeof__(svc) svc;__typeof__(svm) svm;__typeof__(svk) svk;__typeof__(svd) svd;__typeof__(flags) flags;__typeof__(iflags) iflags;__typeof__(disp) disp;__typeof__(program_state) program_state;
struct obj *uarmh,*uarmg,*uarmf,*uarmc,*ublindf,*uwep;
struct objclass objects[NUM_OBJECTS+1];struct permonst mons[NUMMONS+1];
const struct Align aligns[]={{"law","lawful","Law",0,A_LAWFUL},{"balance","neutral","Neu",0,A_NEUTRAL},{"chaos","chaotic","Cha",0,A_CHAOTIC}};
const struct c_common_strings c_common_strings={.c_something="something"};
static struct obj nodes[12];static int opts[20],rolls[2048],roll_count,roll_pos;static unsigned rng_state;static void *growth;
static char tracebuf[131072],snapshotbuf[16384],caller[128],resultbuf[BUFSZ],input[2][BUFSZ];
static void logmsg(const char*f,...){va_list ap;va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);}
static void message(const char*tag,const char*f,va_list ap){logmsg("%s:",tag);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);logmsg(";");iflags.last_msg++;}
static void callback(void){if(opts[16]&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();logmsg("growth;");}if(opts[17]){opts[17]=0;logmsg("reentry:%d;",acurr(A_CON));}}
void panic(const char*f,...){abort();}
void impossible(const char*f,...){va_list ap;va_start(ap,f);message("impossible",f,ap);va_end(ap);}
void pline(const char*f,...){va_list ap;va_start(ap,f);message("msg",f,ap);va_end(ap);callback();}
void pline_The(const char*f,...){va_list ap;va_start(ap,f);message("The",f,ap);va_end(ap);callback();}
void You(const char*f,...){va_list ap;va_start(ap,f);message("You",f,ap);va_end(ap);callback();}
void Your(const char*f,...){va_list ap;va_start(ap,f);message("Your",f,ap);va_end(ap);callback();}
void You_feel(const char*f,...){va_list ap;va_start(ap,f);message("feel",f,ap);va_end(ap);callback();}
void livelog_printf(long flags,const char*f,...){va_list ap;logmsg("live:%ld:",flags);va_start(ap,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,ap);va_end(ap);logmsg(";");callback();}
boolean debugcore(const char*f,boolean b){(void)f;if(opts[0])logmsg("debug:%d;",b);return opts[0];}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*f,int line,const char*fn){const char*p=strrchr(f,'/');snprintf(caller,sizeof caller,"%s:%d:%s",p?p+1:f,line,fn);}
static int draw(int n){unsigned v;if(n<=0)abort();rng_state=rng_state*1664525U+1013904223U;v=(unsigned)(roll_pos<roll_count?rolls[roll_pos]:rng_state)%n;roll_pos++;logmsg("rng:%d:%d@%s;",n,v,caller);return v;}
int(rn2)(int n){return draw(n);}int(rnd)(int n){return draw(n)+1;}int(d)(int count,int sides){int total=0;while(count-->0)total+=draw(sides)+1;return total;}
void encumber_msg(void){logmsg("encumber;");callback();}
void losehp(int n,const char*s,schar f){logmsg("losehp:%d:%s:%d;",n,s,f);if(Upolyd){u.mh-=n;if(opts[1]&&u.mh<=0)u.umonnum=u.umonster;}else u.uhp-=n;callback();}
void done(int how){logmsg("done:%d;",how);}
void shieldeff(coordxy x,coordxy y){logmsg("shield:%d:%d;",x,y);}
int name_to_mon(const char*s,int*len){(void)len;logmsg("name:%s;",s);return opts[2];}
int strncmpi(const char*a,const char*b,int n){while(n--&&*a&&lowc(*a)==lowc(*b))a++,b++;return(unsigned char)lowc(*a)-(unsigned char)lowc(*b);}
char lowc(char c){return c>='A'&&c<='Z'?c+32:c;}
char*strstri(const char*a,const char*b){size_t n=strlen(b);for(;*a;a++)if(!strncmpi(a,b,n))return(char*)a;return 0;}
char*the(const char*s){static char buf[BUFSZ];snprintf(buf,sizeof buf,"the %s",s);return buf;}
boolean confers_luck(struct obj*o){return o->otyp==LUCKSTONE||o->oartifact;}
struct obj*carrying(int typ){struct obj*o;for(o=gi.invent;o;o=o->nobj)if(o->otyp==typ)return o;return 0;}
int sgn(int n){return(n>0)-(n<0);}
int near_capacity(void){logmsg("capacity:%d;",opts[3]);return opts[3];}
void see_monsters(void){logmsg("see_monsters;");callback();}
void add_weapon_skill(int n){logmsg("skill+:%d;",n);}void lose_weapon_skill(int n){logmsg("skill-:%d;",n);}
struct obj*what_gives(long*p){logmsg("what:%ld;",(p-&u.uprops[0].intrinsic)/(long)(sizeof(struct prop)/sizeof(long)));return opts[4]?&nodes[opts[4]-1]:0;}
char*bare_artifactname(struct obj*o){(void)o;return "Eyes of the Overworld";}
char*ysimple_name(struct obj*o){return opts[5]?"pair of boots":o->otyp==DUNCE_CAP?"dunce cap":"amulet of strangulation";}
const char*body_part(int p){(void)p;return "face";}
void copynchars(char*out,const char*in,int n){int i=0;while(i<n&&in[i]){out[i]=in[i];i++;}out[i]=0;}
boolean is_art(struct obj*o,int id){return o&&o->oartifact==id;}
schar uasmon_maxStr(void){return opts[6]?opts[6]:125;}
void adj_erinys(unsigned n){logmsg("erinys:%u;",n);}
void retouch_equipment(int n){logmsg("retouch:%d;",n);callback();}
void make_confused(long n,boolean b){logmsg("confused:%ld:%d;",n,b);HConfusion=n;}
void summon_furies(int n){logmsg("furies:%d;",n);}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/attrib.c"
#else
#include "tu-attrib-layout.h"
#define innate teleport_attrib_innate
extern void teleport_attrib_test_exerper(void),teleport_attrib_test_postadjabil(long*);
extern int teleport_attrib_test_rnd_attr(void),teleport_attrib_test_init_attr_role_redist(int,boolean),teleport_attrib_test_innately(long*);
extern const struct innate*teleport_attrib_test_role_abil(int),*teleport_attrib_test_check_innate_abil(long*,long);
#define exerper teleport_attrib_test_exerper
#define rnd_attr teleport_attrib_test_rnd_attr
#define init_attr_role_redist teleport_attrib_test_init_attr_role_redist
#define postadjabil teleport_attrib_test_postadjabil
#define role_abil teleport_attrib_test_role_abil
#define check_innate_abil teleport_attrib_test_check_innate_abil
#define innately teleport_attrib_test_innately
#endif
#ifdef TELEPORT_REFERENCE_TU
#include "tu-attrib-layout.h"
#endif
void probe_reset(unsigned seed){int i;if(growth)free(growth);growth=0;memset(&u,0,sizeof u);memset(&gu,0,sizeof gu);memset(&gi,0,sizeof gi);memset(&gy,0,sizeof gy);memset(&gm,0,sizeof gm);memset(&svc,0,sizeof svc);memset(&svm,0,sizeof svm);memset(&svk,0,sizeof svk);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&disp,0,sizeof disp);memset(&program_state,0,sizeof program_state);memset(nodes,0,sizeof nodes);memset(mons,0,sizeof mons);memset(objects,0,sizeof objects);memset(opts,0,sizeof opts);opts[2]=NON_PM;u.ux=u.uy=10;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;u.uhp=u.uhpmax=100;u.mh=u.mhmax=30;u.uhunger=500;u.ulevel=5;gy.youmonst.data=&mons[PM_HUMAN];gu.urole.mnum=PM_ARCHEOLOGIST;gu.urace.mnum=PM_HUMAN;gu.urole.xlev=10;gu.urole.hpadv.infix=10;gu.urole.hpadv.lofix=2;gu.urole.hpadv.hifix=1;for(i=0;i<A_MAX;i++){u.acurr.a[i]=10;u.amax.a[i]=18;gu.urole.attrbase[i]=10;gu.urole.attrdist[i]=i==A_CHA?20:16;gu.urace.attrmin[i]=3;gu.urace.attrmax[i]=i==A_STR?125:18;}flags.verbose=1;uarmh=uarmg=uarmf=uarmc=ublindf=uwep=0;rng_state=seed;roll_pos=roll_count=0;tracebuf[0]=caller[0]=resultbuf[0]=0;strcpy(input[0],"sting");strcpy(input[1],"snake");}
void probe_option(int k,long v){switch(k){case 100:u.ulevel=v;break;case 101:u.uhp=v;break;case 102:u.uhpmax=v;break;case 103:u.mh=v;break;case 104:u.mhmax=v;break;case 105:u.umonnum=v?PM_RED_DRAGON:PM_HUMAN;break;case 106:gu.urole.mnum=v;break;case 107:gu.urace.mnum=v;break;case 108:u.uluck=v;break;case 109:u.uhunger=v;break;case 110:u.uhs=v;break;case 111:svm.moves=v;break;case 112:svc.context.next_attrib_check=v;break;case 113:gm.multi=v;break;case 114:program_state.in_moveloop=v;break;case 115:flags.verbose=v;break;case 116:flags.debug=v;break;case 117:u.ulycn=v;break;case 118:gy.youmonst.data=&mons[v];break;case 119:mons[PM_HUMAN].mflags1=v;break;case 120:mons[PM_HUMAN].mlet=v;break;case 121:u.ucreamed=v;break;case 122:u.uroleplay.blind=v;break;case 123:u.uroleplay.deaf=v;break;case 124:u.ualign.type=v;break;case 125:u.ualign.record=v;break;case 126:u.ualign.abuse=v;break;case 127:gu.urole.xlev=v;break;case 128:flags.initalign=v;break;case 129:gu.urole.initrecord=v;break;case 130:u.usteed=v?&gy.youmonst:0;break;case 131:astral_level=u.uz;break;case 132:mons[v].geno=G_UNIQ;break;case 133:mons[v].mflags2=M2_PNAME;break;case 134:iflags.last_msg=v;break;default:opts[k]=v;break;}}
void probe_attr(int array,int index,int v){schar*p;switch(array){case 0:p=u.acurr.a;break;case 1:p=u.amax.a;break;case 2:p=u.abon.a;break;case 3:p=u.aexe.a;break;case 4:p=u.atemp.a;break;default:p=u.atime.a;break;}p[index]=v;}
void probe_role_array(int array,int index,int v){switch(array){case 0:gu.urole.attrbase[index]=v;break;case 1:gu.urole.attrdist[index]=v;break;case 2:gu.urace.attrmin[index]=v;break;case 3:gu.urace.attrmax[index]=v;break;}}
void probe_advance(int race,int field,int v){struct RoleAdvance*p=race?&gu.urace.hpadv:&gu.urole.hpadv;switch(field){case 0:p->infix=v;break;case 1:p->inrnd=v;break;case 2:p->lofix=v;break;case 3:p->lornd=v;break;case 4:p->hifix=v;break;case 5:p->hirnd=v;break;}}
void probe_prop(int index,int field,long v){if(field==0)u.uprops[index].intrinsic=v;else if(field==1)u.uprops[index].extrinsic=v;else u.uprops[index].blocked=v;}
void probe_object(int id,int field,long v){struct obj*o=&nodes[id];switch(field){case 0:o->otyp=v;break;case 1:o->quan=v;break;case 2:o->cursed=v;break;case 3:o->blessed=v;break;case 4:o->dknown=v;break;case 5:o->oartifact=v;break;case 6:o->spe=v;break;case 7:o->nobj=v<0?0:&nodes[v];break;case 8:gi.invent=v<0?0:&nodes[v];break;case 9:objects[o->otyp].oc_name_known=v;break;}}
void probe_equip(int which,int id){struct obj*o=id<0?0:&nodes[id];switch(which){case 0:uarmh=o;break;case 1:uarmg=o;break;case 2:uarmf=o;break;case 3:uarmc=o;break;case 4:ublindf=o;break;case 5:uwep=o;break;}}
int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){roll_count=n;roll_pos=0;}
char*probe_input(int i){return input[i];}
long probe_action(int op,int a,int b,int c){switch(op){case 0:return adjattrib(a,b,c);case 1:gainstr(a<0?0:&nodes[a],b,c);break;case 2:losestr(a,input[1],b);break;case 3:poison_strdmg(a,b,input[1],c);break;case 4:poisontell(a,b);break;case 5:poisoned(input[0],a,input[1],b,c);break;case 6:change_luck(a);break;case 7:return stone_luck(a);case 8:set_moreluck();break;case 9:restore_attrib();break;case 10:exercise(a,b);break;case 11:exerper();break;case 12:exerchk();break;case 13:return rnd_attr();case 14:return init_attr_role_redist(a,b);case 15:init_attr(a);break;case 16:redist_attr();break;case 17:vary_init_attr();break;case 18:postadjabil(&u.uprops[a].intrinsic);break;case 19:{const struct innate*p=role_abil(a);return p?p->ulevel:-1;}case 20:{const struct innate*p=check_innate_abil(&u.uprops[a].intrinsic,b?FROMRACE:FROMEXPER);return p?p->ulevel:-1;}case 21:return innately(&u.uprops[a].intrinsic);case 22:return is_innate(a);case 23:strcpy(resultbuf,from_what(a));break;case 24:adjabil(a,b);break;case 25:return newhp();case 26:return minuhpmax(a);case 27:setuhpmax(a,b);break;case 28:return adjuhploss(a,b);case 29:return acurr(a);case 30:return acurrstr();case 31:return extremeattr(a);case 32:adjalign(a);break;case 33:uchangealign(a,b);break;}return 0;}
extern const char*const attrname[6];
const char*probe_attrname(int i){return attrname[i];}
const char*probe_innate(int role,int row){static char buf[256];const struct innate*p=role_abil(role);if(!p)return "null";p+=row;snprintf(buf,sizeof buf,"%d:%ld:%s:%s",p->ulevel,p->ability?(p->ability-&u.uprops[0].intrinsic)/(long)(sizeof(struct prop)/sizeof(long)):-1L,p->gainstr?p->gainstr:"(null)",p->losestr?p->losestr:"(null)");return buf;}
const char*probe_trace(void){return tracebuf;}const char*probe_result(void){return resultbuf;}
const char*probe_snapshot(void){int i;char*p=snapshotbuf;p+=sprintf(p,"hp:%d:%d:%d:%d:%d;luck:%d:%d;align:%d:%d:%u:%d:%d;state:%d:%d:%ld:%u:%d;attr:",u.uhp,u.uhpmax,u.uhppeak,u.mh,u.mhmax,u.uluck,u.moreluck,u.ualign.type,u.ualign.record,u.ualign.abuse,u.ualignbase[0],u.ublessed,disp.botl,iflags.last_msg,svc.context.next_attrib_check,rng_state,roll_pos);for(i=0;i<A_MAX;i++)p+=sprintf(p,"%d:%d:%d:%d:%d:%d;",u.acurr.a[i],u.amax.a[i],u.abon.a[i],u.aexe.a[i],u.atemp.a[i],u.atime.a[i]);for(i=0;i<=LAST_PROP;i++)p+=sprintf(p,"p%d:%ld:%ld:%ld;",i,u.uprops[i].intrinsic,u.uprops[i].extrinsic,u.uprops[i].blocked);for(i=0;i<MAXULEV;i++)p+=sprintf(p,"h%d:%d;",i,u.uhpinc[i]);return snapshotbuf;}
uintptr_t probe_stack(void){return(uintptr_t)emscripten_stack_get_current();}
