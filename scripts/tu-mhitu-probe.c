/* Controlled configured MHITU original-C/JS typed state and dependency oracle. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-mhitu-layout.h"
__typeof__(gy) gy;
__typeof__(u) u;
__typeof__(gh) gh;
__typeof__(flags) flags;
__typeof__(objects) objects;
__typeof__(uwep) uwep;
__typeof__(gv) gv;
__typeof__(disp) disp;
__typeof__(mons) mons={[0]={.pmidx=0},[1]={.pmidx=1},[2]={.pmidx=2},[3]={.pmidx=3},[4]={.pmidx=4},[5]={.pmidx=5},[6]={.pmidx=6},[7]={.pmidx=7},[8]={.pmidx=8},[9]={.pmidx=9},[10]={.pmidx=10},[11]={.pmidx=11},[12]={.pmidx=12},[13]={.pmidx=13},[14]={.pmidx=14},[15]={.pmidx=15},[16]={.pmidx=16},[17]={.pmidx=17},[18]={.pmidx=18},[19]={.pmidx=19},[20]={.pmidx=20},[21]={.pmidx=21},[22]={.pmidx=22},[23]={.pmidx=23},[24]={.pmidx=24},[25]={.pmidx=25},[26]={.pmidx=26},[27]={.pmidx=27},[28]={.pmidx=28},[29]={.pmidx=29},[30]={.pmidx=30},[31]={.pmidx=31},[32]={.pmidx=32},[33]={.pmidx=33},[34]={.pmidx=34},[35]={.pmidx=35},[36]={.pmidx=36},[37]={.pmidx=37},[38]={.pmidx=38},[39]={.pmidx=39},[40]={.pmidx=40},[41]={.pmidx=41},[42]={.pmidx=42},[43]={.pmidx=43},[44]={.pmidx=44},[45]={.pmidx=45},[46]={.pmidx=46},[47]={.pmidx=47},[48]={.pmidx=48},[49]={.pmidx=49},[50]={.pmidx=50},[51]={.pmidx=51},[52]={.pmidx=52},[53]={.pmidx=53},[54]={.pmidx=54},[55]={.pmidx=55},[56]={.pmidx=56},[57]={.pmidx=57},[58]={.pmidx=58},[59]={.pmidx=59},[60]={.pmidx=60},[61]={.pmidx=61},[62]={.pmidx=62},[63]={.pmidx=63},[64]={.pmidx=64},[65]={.pmidx=65},[66]={.pmidx=66},[67]={.pmidx=67},[68]={.pmidx=68},[69]={.pmidx=69},[70]={.pmidx=70},[71]={.pmidx=71},[72]={.pmidx=72},[73]={.pmidx=73},[74]={.pmidx=74},[75]={.pmidx=75},[76]={.pmidx=76},[77]={.pmidx=77},[78]={.pmidx=78},[79]={.pmidx=79},[80]={.pmidx=80},[81]={.pmidx=81},[82]={.pmidx=82},[83]={.pmidx=83},[84]={.pmidx=84},[85]={.pmidx=85},[86]={.pmidx=86},[87]={.pmidx=87},[88]={.pmidx=88},[89]={.pmidx=89},[90]={.pmidx=90},[91]={.pmidx=91},[92]={.pmidx=92},[93]={.pmidx=93},[94]={.pmidx=94},[95]={.pmidx=95},[96]={.pmidx=96},[97]={.pmidx=97},[98]={.pmidx=98},[99]={.pmidx=99},[100]={.pmidx=100},[101]={.pmidx=101},[102]={.pmidx=102},[103]={.pmidx=103},[104]={.pmidx=104},[105]={.pmidx=105},[106]={.pmidx=106},[107]={.pmidx=107},[108]={.pmidx=108},[109]={.pmidx=109},[110]={.pmidx=110},[111]={.pmidx=111},[112]={.pmidx=112},[113]={.pmidx=113},[114]={.pmidx=114},[115]={.pmidx=115},[116]={.pmidx=116},[117]={.pmidx=117},[118]={.pmidx=118},[119]={.pmidx=119},[120]={.pmidx=120},[121]={.pmidx=121},[122]={.pmidx=122},[123]={.pmidx=123},[124]={.pmidx=124},[125]={.pmidx=125},[126]={.pmidx=126},[127]={.pmidx=127},[128]={.pmidx=128},[129]={.pmidx=129},[130]={.pmidx=130},[131]={.pmidx=131},[132]={.pmidx=132},[133]={.pmidx=133},[134]={.pmidx=134},[135]={.pmidx=135},[136]={.pmidx=136},[137]={.pmidx=137},[138]={.pmidx=138},[139]={.pmidx=139},[140]={.pmidx=140},[141]={.pmidx=141},[142]={.pmidx=142},[143]={.pmidx=143},[144]={.pmidx=144},[145]={.pmidx=145},[146]={.pmidx=146},[147]={.pmidx=147},[148]={.pmidx=148},[149]={.pmidx=149},[150]={.pmidx=150},[151]={.pmidx=151},[152]={.pmidx=152},[153]={.pmidx=153},[154]={.pmidx=154},[155]={.pmidx=155},[156]={.pmidx=156},[157]={.pmidx=157},[158]={.pmidx=158},[159]={.pmidx=159},[160]={.pmidx=160},[161]={.pmidx=161},[162]={.pmidx=162},[163]={.pmidx=163},[164]={.pmidx=164},[165]={.pmidx=165},[166]={.pmidx=166},[167]={.pmidx=167},[168]={.pmidx=168},[169]={.pmidx=169},[170]={.pmidx=170},[171]={.pmidx=171},[172]={.pmidx=172},[173]={.pmidx=173},[174]={.pmidx=174},[175]={.pmidx=175},[176]={.pmidx=176},[177]={.pmidx=177},[178]={.pmidx=178},[179]={.pmidx=179},[180]={.pmidx=180},[181]={.pmidx=181},[182]={.pmidx=182},[183]={.pmidx=183},[184]={.pmidx=184},[185]={.pmidx=185},[186]={.pmidx=186},[187]={.pmidx=187},[188]={.pmidx=188},[189]={.pmidx=189},[190]={.pmidx=190},[191]={.pmidx=191},[192]={.pmidx=192},[193]={.pmidx=193},[194]={.pmidx=194},[195]={.pmidx=195},[196]={.pmidx=196},[197]={.pmidx=197},[198]={.pmidx=198},[199]={.pmidx=199},[200]={.pmidx=200},[201]={.pmidx=201},[202]={.pmidx=202},[203]={.pmidx=203},[204]={.pmidx=204},[205]={.pmidx=205},[206]={.pmidx=206},[207]={.pmidx=207},[208]={.pmidx=208},[209]={.pmidx=209},[210]={.pmidx=210},[211]={.pmidx=211},[212]={.pmidx=212},[213]={.pmidx=213},[214]={.pmidx=214},[215]={.pmidx=215},[216]={.pmidx=216},[217]={.pmidx=217},[218]={.pmidx=218},[219]={.pmidx=219},[220]={.pmidx=220},[221]={.pmidx=221},[222]={.pmidx=222},[223]={.pmidx=223},[224]={.pmidx=224},[225]={.pmidx=225},[226]={.pmidx=226},[227]={.pmidx=227},[228]={.pmidx=228},[229]={.pmidx=229},[230]={.pmidx=230},[231]={.pmidx=231},[232]={.pmidx=232},[233]={.pmidx=233},[234]={.pmidx=234},[235]={.pmidx=235},[236]={.pmidx=236},[237]={.pmidx=237},[238]={.pmidx=238},[239]={.pmidx=239},[240]={.pmidx=240},[241]={.pmidx=241},[242]={.pmidx=242},[243]={.pmidx=243},[244]={.pmidx=244},[245]={.pmidx=245},[246]={.pmidx=246},[247]={.pmidx=247},[248]={.pmidx=248},[249]={.pmidx=249},[250]={.pmidx=250},[251]={.pmidx=251},[252]={.pmidx=252},[253]={.pmidx=253},[254]={.pmidx=254},[255]={.pmidx=255},[256]={.pmidx=256},[257]={.pmidx=257},[258]={.pmidx=258},[259]={.pmidx=259},[260]={.pmidx=260},[261]={.pmidx=261},[262]={.pmidx=262},[263]={.pmidx=263},[264]={.pmidx=264},[265]={.pmidx=265},[266]={.pmidx=266},[267]={.pmidx=267},[268]={.pmidx=268},[269]={.pmidx=269},[270]={.pmidx=270},[271]={.pmidx=271},[272]={.pmidx=272},[273]={.pmidx=273},[274]={.pmidx=274},[275]={.pmidx=275},[276]={.pmidx=276},[277]={.pmidx=277},[278]={.pmidx=278},[279]={.pmidx=279},[280]={.pmidx=280},[281]={.pmidx=281},[282]={.pmidx=282},[283]={.pmidx=283},[284]={.pmidx=284},[285]={.pmidx=285},[286]={.pmidx=286},[287]={.pmidx=287},[288]={.pmidx=288},[289]={.pmidx=289},[290]={.pmidx=290},[291]={.pmidx=291},[292]={.pmidx=292},[293]={.pmidx=293},[294]={.pmidx=294},[295]={.pmidx=295},[296]={.pmidx=296},[297]={.pmidx=297},[298]={.pmidx=298},[299]={.pmidx=299},[300]={.pmidx=300},[301]={.pmidx=301},[302]={.pmidx=302},[303]={.pmidx=303},[304]={.pmidx=304},[305]={.pmidx=305},[306]={.pmidx=306},[307]={.pmidx=307},[308]={.pmidx=308},[309]={.pmidx=309},[310]={.pmidx=310},[311]={.pmidx=311},[312]={.pmidx=312},[313]={.pmidx=313},[314]={.pmidx=314},[315]={.pmidx=315},[316]={.pmidx=316},[317]={.pmidx=317},[318]={.pmidx=318},[319]={.pmidx=319},[320]={.pmidx=320},[321]={.pmidx=321},[322]={.pmidx=322},[323]={.pmidx=323},[324]={.pmidx=324},[325]={.pmidx=325},[326]={.pmidx=326},[327]={.pmidx=327},[328]={.pmidx=328},[329]={.pmidx=329},[330]={.pmidx=330},[331]={.pmidx=331},[332]={.pmidx=332},[333]={.pmidx=333},[334]={.pmidx=334},[335]={.pmidx=335},[336]={.pmidx=336},[337]={.pmidx=337},[338]={.pmidx=338},[339]={.pmidx=339},[340]={.pmidx=340},[341]={.pmidx=341},[342]={.pmidx=342},[343]={.pmidx=343},[344]={.pmidx=344},[345]={.pmidx=345},[346]={.pmidx=346},[347]={.pmidx=347},[348]={.pmidx=348},[349]={.pmidx=349},[350]={.pmidx=350},[351]={.pmidx=351},[352]={.pmidx=352},[353]={.pmidx=353},[354]={.pmidx=354},[355]={.pmidx=355},[356]={.pmidx=356},[357]={.pmidx=357},[358]={.pmidx=358},[359]={.pmidx=359},[360]={.pmidx=360},[361]={.pmidx=361},[362]={.pmidx=362},[363]={.pmidx=363},[364]={.pmidx=364},[365]={.pmidx=365},[366]={.pmidx=366},[367]={.pmidx=367},[368]={.pmidx=368},[369]={.pmidx=369},[370]={.pmidx=370},[371]={.pmidx=371},[372]={.pmidx=372},[373]={.pmidx=373},[374]={.pmidx=374},[375]={.pmidx=375},[376]={.pmidx=376},[377]={.pmidx=377},[378]={.pmidx=378},[379]={.pmidx=379},[380]={.pmidx=380},[381]={.pmidx=381},[382]={.pmidx=382},[383]={.pmidx=383}};
__typeof__(sysopt) sysopt;
__typeof__(gb) gb;
__typeof__(gn) gn;
__typeof__(svl) svl;
__typeof__(svp) svp;
__typeof__(gm) gm;
__typeof__(gs) gs;
__typeof__(svd) svd;
__typeof__(svm) svm;
__typeof__(uarmc) uarmc;
__typeof__(uarm) uarm;
__typeof__(uarmu) uarmu;
__typeof__(uarmh) uarmh;
__typeof__(gi) gi;
__typeof__(gu) gu;
__typeof__(uball) uball;
__typeof__(windowprocs) windowprocs;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(uchain) uchain;
__typeof__(svk) svk;
__typeof__(uarmg) uarmg;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(uarmf) uarmf;
__typeof__(uarms) uarms;
const struct Gender genders[4]={{.adj="male",.he="he",.him="him",.his="his"},{.adj="female",.he="she",.him="her",.his="her"},{.adj="neuter",.he="it",.him="it",.his="its"},{.adj="plural",.he="they",.him="them",.his="their"}};
const struct c_common_strings c_common_strings={.c_something="something",.c_Something="Something",.c_vision_clears="Your vision clears."};
const char ynchars[]="yn";
const struct attack c_sa_no[NATTK]={{AT_CLAW,AD_PHYS,1,3},{AT_CLAW,AD_PHYS,1,3},{AT_BITE,AD_DRLI,2,6}};
static struct permonst *pmcopies[4];static struct obj objpool[16];static struct monst mpool[8];static struct trap trap;static struct attack alt[8];static int prev[8];static boolean outputs[8];
static char tracebuf[524288],statebuf[4194304],input[2048],labelbuf[16][64];static int tracepos,seed,opts[320],reentered;static void*growth;
static seenV vis[ROWNO][COLNO],*visrows[ROWNO];
static void append(const char*fmt,...){if(tracepos>sizeof tracebuf-4096)abort();va_list ap;va_start(ap,fmt);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);}
static uint64_t canonical(uint64_t);
static int mid(struct monst*m){if(!m)return -1;if(m==&gy.youmonst)return 98;for(int i=0;i<8;i++)if(m==&mpool[i])return i;return 99;}
static int oid(struct obj*o){if(!o)return -1;for(int i=0;i<16;i++)if(o==&objpool[i])return i;return 99;}
static void grow(void){if(opts[50]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}}
boolean rng_log_enabled(void){return opts[49];}
void rng_log_set_caller(const char*file,int line,const char*fn){append("site:%s:%d:%s;",file,line,fn);grow();if(opts[51]){u.ulevel=opts[51];append("ulevel:%d;",u.ulevel);}if(opts[54]){mpool[0].m_lev=opts[54];append("mlev:%d;",mpool[0].m_lev);}if(opts[55]){alt[0].damn=opts[55];alt[0].damd=opts[56];append("attackdice:%d:%d;",alt[0].damn,alt[0].damd);}if(opts[57]){u.uac=opts[57];append("uac:%d;",u.uac);}if(opts[52]&&!reentered){reentered=1;u_slow_down();append("reentered;");}}
static int random_(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;return (unsigned)seed%n;}
int (rn2)(int n){int v=random_(n);append("rn2:%d:%d;",n,v);return v;}
int (rnd)(int n){int v=random_(n)+1;append("rnd:%d:%d;",n,v);return v;}
int (rnl)(int n){int v=random_(n);append("rnl:%d:%d;",n,v);return v;}
int (d)(int n,int x){int v=0;for(int i=0;i<n;i++)v+=random_(x)+1;append("d:%d:%d:%d;",n,x,v);return v;}
static void message(const char*kind,const char*fmt,va_list ap){char b[2048];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",kind,b);grow();}
void (pline)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("pline",fmt,ap);va_end(ap);}
void (You)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You",fmt,ap);va_end(ap);}
void (Your)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("Your",fmt,ap);va_end(ap);}
void (You_feel)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You_feel",fmt,ap);va_end(ap);}
void (You_cant)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You_cant",fmt,ap);va_end(ap);}
void (You_hear)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You_hear",fmt,ap);va_end(ap);}
void (urgent_pline)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("urgent_pline",fmt,ap);va_end(ap);}
void (pline_The)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("pline_The",fmt,ap);va_end(ap);}
void (impossible)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("impossible",fmt,ap);va_end(ap);}
void (verbalize)(const char*fmt,...){va_list ap;va_start(ap,fmt);message("verbalize",fmt,ap);va_end(ap);}
void pline_mon(struct monst*m,const char*fmt,...){append("mon:%d;",mid(m));va_list ap;va_start(ap,fmt);message("pline_mon",fmt,ap);va_end(ap);}
void set_ustuck(struct monst*m){append("set_ustuck:%d;",mid(m));u.ustuck=m;}
void reset_utrap(boolean n){append("reset_utrap:%d;",n);u.utrap=u.utraptype=0;}
void incr_itimeout(long*p,int n){append("timeout:%ld:%d;",*p,n);*p=(*p&~TIMEOUT)|((*p+n)&TIMEOUT);}
char yn_function(const char*q,const char*c,char def,boolean isyn){append("yn:%s:%s:%d:%d;",q,c,def,isyn);return opts[5]?opts[5]:def;}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
int dist2(coordxy x,coordxy y,coordxy a,coordxy b){return (x-a)*(x-a)+(y-b)*(y-b);}
boolean enexto(coord*out,coordxy x,coordxy y,struct permonst*p){append("enexto:%d:%d;",x,y);out->x=x+1;out->y=y+1;return opts[23];}
boolean monnear(struct monst*m,coordxy x,coordxy y){int n=dist2(m->mx,m->my,x,y);return n<3;}
struct attack*dmgtype_fromattack(struct permonst*p,int d,int a){for(int i=0;i<NATTK;i++)if(p->mattk[i].adtyp==d&&p->mattk[i].aatyp==a)return &p->mattk[i];return 0;}
boolean dmgtype(struct permonst*p,int d){for(int i=0;i<NATTK;i++)if(p->mattk[i].adtyp==d)return TRUE;return FALSE;}
struct attack*attacktype_fordmg(struct permonst*p,int a,int d){for(int i=0;i<NATTK;i++)if(p->mattk[i].aatyp==a&&(d==AD_ANY||p->mattk[i].adtyp==d))return &p->mattk[i];return 0;}
void make_sick(long n,const char*why,boolean talk,int mask){append("sick:%ld:%s:%d:%d;",n,why,talk,mask);u.uprops[SICK].intrinsic=n;}
void make_blinded(long n,boolean talk){append("blinded:%ld:%d;",n,talk);u.uprops[BLINDED].intrinsic=n;}
void make_stunned(long n,boolean talk){append("stunned:%ld:%d;",n,talk);u.uprops[STUNNED].intrinsic=n;}
void make_confused(long n,boolean talk){append("confused:%ld:%d;",n,talk);u.uprops[CONFUSION].intrinsic=n;}
void nomul(int n){append("nomul:%d;",n);gm.multi=n;}
void done(int how){append("done:%d:%s;",how,svk.killer.name);}
void losehp(int n,const char*why,schar fmt){append("losehp:%d:%s:%d;",n,why,fmt);u.uhp-=n;}
void newsym(coordxy x,coordxy y){append("newsym:%d:%d;",x,y);}
void setworn(struct obj*o,long mask){append("setworn:%d:%ld;",oid(o),mask);if(o)o->owornmask=mask;}
struct trap*t_at(coordxy x,coordxy y){return opts[11]?&trap:0;}
int were_summon(struct permonst*p,boolean you,int*n,char*out){append("were_summon:%d;",you);*n=opts[15];if(out)strcpy(out,"friends");return opts[16];}
void display_(winid w,boolean b){append("display:%d:%d;",w,b);}
char*safe_qbuf(char*out,const char*pre,const char*post,struct obj*o,char*(*name)(struct obj*),char*(*altname)(struct obj*),const char*last){append("safe_qbuf:%d:%d:%d;",oid(o),name==xname,altname==simpleonames);snprintf(out,QBUFSZ,"%s%s%s",pre,name(o),post);return out;}
void mhitm_adtyping(struct monst*m,struct attack*a,struct monst*def,struct mhitm_data*out){append("adtyping:%d:%d:%d:%d;",mid(m),a->adtyp,mid(def),out->damage);out->hitflags=opts[18];out->done=opts[19];out->permdmg=opts[20];}
boolean mhitm_knockback(struct monst*m,struct monst*def,struct attack*a,int*flags,boolean weapon){append("knockback:%d:%d:%d:%d;",mid(m),mid(def),*flags,weapon);*flags|=opts[21];return opts[22];}
char*Monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*Some_Monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*mon_nam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*Amonnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*m_monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*noit_Monnam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*noit_mon_nam(struct monst*m){return labelbuf[mid(m)<8&&mid(m)>=0?mid(m):8];}
char*simpleonames(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
char*xname(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
char*yname(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
char*doname(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*suit_simple_name(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*cloak_simple_name(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*helm_simple_name(struct obj*o){return labelbuf[oid(o)<16&&oid(o)>=0?oid(o):0];}
const char*pmname(struct permonst*p,int g){return "form";}
char*an(const char*s){return (char*)s;}char*the(const char*s){return (char*)s;}char*s_suffix(const char*s){return (char*)s;}char*makeplural(const char*s){return (char*)s;}
char*vtense(const char*s,const char*v){return (char*)v;}const char*stagger(const struct permonst*p,const char*v){return v;}
const char*hliquid(const char*s){return s;}const char*ceiling(coordxy x,coordxy y){return "ceiling";}
const char*body_part(int i){return "body";}const char*growl_sound(struct monst*m){return "growl";}const char*mimic_obj_name(struct monst*m){return "thing";}
char*upstart(char*s){return s;}
schar acurr(int a){return u.acurr.a[a];}
long yyyymmdd(time_t now){return 20260401;}int getyear(void){return 2026;}
signed char (In_hell)(d_level * a0){append("dependency:In_hell:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[64];}
int (Mgender)(struct monst * a0){append("dependency:Mgender:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[65];}
signed char (Resists_Elem)(struct monst * a0,int a1){append("dependency:Resists_Elem:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[66];}
void (Ring_gone)(struct obj * a0){append("dependency:Ring_gone:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (Ring_on)(struct obj * a0){append("dependency:Ring_on:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (acid_damage)(struct obj * a0){append("dependency:acid_damage:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (adjalign)(int a0){append("dependency:adjalign:%d;",(int)a0);}
signed char (adjattrib)(int a0,int a1,int a2){append("dependency:adjattrib:%d:%d:%d;",(int)a0,(int)a1,(int)a2);return opts[67];}
long (attk_protection)(int a0){append("dependency:attk_protection:%d;",(int)a0);return opts[68];}
void (bot)(void){append("dependency:bot;");}
int (breamu)(struct monst * a0,struct attack * a1){append("dependency:breamu:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[69];}
void (burn_away_slime)(void){append("dependency:burn_away_slime;");}
signed char (burnarmor)(struct monst * a0){append("dependency:burnarmor:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[70];}
int (buzzmu)(struct monst * a0,struct attack * a1){append("dependency:buzzmu:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[71];}
signed char (can_blnd)(struct monst * a0,struct monst * a1,uchar a2,struct obj * a3){append("dependency:can_blnd:%llu:%llu:%d:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1),(int)a2,(unsigned long long)canonical((uintptr_t)a3));return opts[72];}
int (canseemon)(struct monst * a0){append("dependency:canseemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[73];}
int (castmu)(struct monst * a0,struct attack * a1,boolean a2,boolean a3){append("dependency:castmu:%llu:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1),(int)a2,(int)a3);return opts[74];}
struct monst * (christen_monst)(struct monst * a0,const char * a1){append("dependency:christen_monst:%llu:%s;",(unsigned long long)canonical((uintptr_t)a0),a1?a1:"(null)");return opts[75]?(struct monst *)&mpool[1]:0;}
const char * (currency)(long a0){append("dependency:currency:%llu;",(unsigned long long)a0);return opts[76]?(const char *)&input:0;}
unsigned long (cvt_adtyp_to_mseenres)(uchar a0){append("dependency:cvt_adtyp_to_mseenres:%d;",(int)a0);return opts[77];}
signed char (defended)(struct monst * a0,int a1){append("dependency:defended:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[78];}
int (destroy_items)(struct monst * a0,int a1,int a2){append("dependency:destroy_items:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return opts[79];}
void (discover_object)(int a0,boolean a1,boolean a2,boolean a3){append("dependency:discover_object:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3);}
void (dismount_steed)(int a0){append("dependency:dismount_steed:%d;",(int)a0);}
void (done_in_by)(struct monst * a0,int a1){append("dependency:done_in_by:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (drain_en)(int a0,boolean a1){append("dependency:drain_en:%d:%d;",(int)a0,(int)a1);}
signed char (drain_item)(struct obj * a0,boolean a1){append("dependency:drain_item:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[80];}
signed char (engulf_target)(struct monst * a0,struct monst * a1){append("dependency:engulf_target:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[81];}
void (erode_armor)(struct monst * a0,int a1){append("dependency:erode_armor:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (exercise)(int a0,boolean a1){append("dependency:exercise:%d:%d;",(int)a0,(int)a1);}
signed char (failed_grab)(struct monst * a0,struct monst * a1,struct attack * a2){append("dependency:failed_grab:%llu:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1),(unsigned long long)canonical((uintptr_t)a2));return opts[82];}
int (find_mac)(struct monst * a0){append("dependency:find_mac:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[83];}
signed char (find_offensive)(struct monst * a0){append("dependency:find_offensive:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[84];}
void (flush_screen)(int a0){append("dependency:flush_screen:%d;",(int)a0);}
void (freeinv)(struct obj * a0){append("dependency:freeinv:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (gender)(struct monst * a0){append("dependency:gender:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[85];}
int (get_atkdam_type)(int a0){append("dependency:get_atkdam_type:%d;",(int)a0);return opts[86];}
void (golemeffects)(struct monst * a0,int a1,int a2){append("dependency:golemeffects:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);}
signed char (hard_helmet)(struct obj * a0){append("dependency:hard_helmet:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[87];}
int (hitval)(struct obj * a0,struct monst * a1){append("dependency:hitval:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[88];}
void (ignite_items)(struct obj * a0){append("dependency:ignite_items:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (initedog)(struct monst * a0,boolean a1){append("dependency:initedog:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
signed char (is_art)(struct obj * a0,int a1){append("dependency:is_art:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[89];}
signed char (is_fainted)(void){append("dependency:is_fainted;");return opts[90];}
signed char (is_home_elemental)(struct permonst * a0){append("dependency:is_home_elemental:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[91];}
signed char (is_pool)(coordxy a0,coordxy a1){append("dependency:is_pool:%d:%d;",(int)a0,(int)a1);return opts[92];}
signed char (is_quest_artifact)(struct obj * a0){append("dependency:is_quest_artifact:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[93];}
signed char (is_waterwall)(coordxy a0,coordxy a1){append("dependency:is_waterwall:%d:%d;",(int)a0,(int)a1);return opts[94];}
void (killed)(struct monst * a0){append("dependency:killed:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (losexp)(const char * a0){append("dependency:losexp:%s;",a0?a0:"(null)");}
signed char (make_hallucinated)(long a0,boolean a1,long a2){append("dependency:make_hallucinated:%llu:%d:%llu;",(unsigned long long)a0,(int)a1,(unsigned long long)a2);return opts[95];}
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("dependency:makemon:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3);return opts[96]?(struct monst *)&mpool[1]:0;}
void (map_invisible)(coordxy a0,coordxy a1){append("dependency:map_invisible:%d:%d;",(int)a0,(int)a1);}
int (mattackm)(struct monst * a0,struct monst * a1){append("dependency:mattackm:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[97];}
int (midnight)(void){append("dependency:midnight;");return opts[98];}
void (minstapetrify)(struct monst * a0,boolean a1){append("dependency:minstapetrify:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
int (minuhpmax)(int a0){append("dependency:minuhpmax:%d;",(int)a0);return opts[99];}
void (mnexto)(struct monst * a0,unsigned int a1){append("dependency:mnexto:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (mon_explodes)(struct monst * a0,struct attack * a1){append("dependency:mon_explodes:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));}
signed char (mon_hates_blessings)(struct monst * a0){append("dependency:mon_hates_blessings:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[100];}
signed char (mon_reflects)(struct monst * a0,const char * a1){append("dependency:mon_reflects:%llu:%s;",(unsigned long long)canonical((uintptr_t)a0),a1?a1:"(null)");return opts[101];}
void (mon_to_stone)(struct monst * a0){append("dependency:mon_to_stone:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (mon_visible)(struct monst * a0){append("dependency:mon_visible:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[102];}
int (mon_wield_item)(struct monst * a0){append("dependency:mon_wield_item:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[103];}
void (mondead)(struct monst * a0){append("dependency:mondead:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
long (money2mon)(struct monst * a0,long a1){append("dependency:money2mon:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)a1);return opts[104];}
long (money_cnt)(struct obj * a0){append("dependency:money_cnt:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[105];}
void (monstseesu)(unsigned long a0){append("dependency:monstseesu:%llu;",(unsigned long long)a0);}
void (monstunseesu)(unsigned long a0){append("dependency:monstunseesu:%llu;",(unsigned long long)a0);}
int (mpickobj)(struct monst * a0,struct obj * a1){append("dependency:mpickobj:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[106];}
int (msummon)(struct monst * a0){append("dependency:msummon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[107];}
void (new_were)(struct monst * a0){append("dependency:new_were:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (night)(void){append("dependency:night;");return opts[108];}
int (number_leashed)(void){append("dependency:number_leashed;");return opts[109];}
void (observe_object)(struct obj * a0){append("dependency:observe_object:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (paralyze_monst)(struct monst * a0,int a1){append("dependency:paralyze_monst:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (place_monster)(struct monst * a0,coordxy a1,coordxy a2){append("dependency:place_monster:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);}
void (placebc)(void){append("dependency:placebc;");}
void (pluslvl)(boolean a0){append("dependency:pluslvl:%d;",(int)a0);}
int (poly_gender)(void){append("dependency:poly_gender;");return opts[110];}
signed char (poly_when_stoned)(struct permonst * a0){append("dependency:poly_when_stoned:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[111];}
int (polymon)(int a0){append("dependency:polymon:%d;",(int)a0);return opts[112];}
void (prinv)(const char * a0,struct obj * a1,long a2){append("dependency:prinv:%s:%llu:%llu;",a0?a0:"(null)",(unsigned long long)canonical((uintptr_t)a1),(unsigned long long)a2);}
int (pronoun_gender)(struct monst * a0,unsigned int a1){append("dependency:pronoun_gender:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[113];}
signed char (protects)(struct obj * a0,boolean a1){append("dependency:protects:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[114];}
void (rehumanize)(void){append("dependency:rehumanize;");}
void (remove_worn_item)(struct obj * a0,boolean a1){append("dependency:remove_worn_item:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (reset_occupations)(void){append("dependency:reset_occupations;");}
signed char (resists_blnd)(struct monst * a0){append("dependency:resists_blnd:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[115];}
signed char (resists_drli)(struct monst * a0){append("dependency:resists_drli:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[116];}
signed char (rloc)(struct monst * a0,unsigned int a1){append("dependency:rloc:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return opts[117];}
int (sensemon)(struct monst * a0){append("dependency:sensemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[118];}
void (set_apparxy)(struct monst * a0){append("dependency:set_apparxy:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (set_msg_xy)(coordxy a0,coordxy a1){append("dependency:set_msg_xy:%d:%d;",(int)a0,(int)a1);}
void (shieldeff)(coordxy a0,coordxy a1){append("dependency:shieldeff:%d:%d;",(int)a0,(int)a1);}
void (showdamage)(int a0){append("dependency:showdamage:%d;",(int)a0);}
signed char (snuff_lit)(struct obj * a0){append("dependency:snuff_lit:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[119];}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){append("dependency:sobj_at:%d:%d:%d;",(int)a0,(int)a1,(int)a2);return opts[120]?(struct obj *)&objpool[1]:0;}
int (spitmu)(struct monst * a0,struct attack * a1){append("dependency:spitmu:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[121];}
struct monst * (split_mon)(struct monst * a0,struct monst * a1){append("dependency:split_mon:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return opts[122]?(struct monst *)&mpool[1]:0;}
void (spoteffects)(boolean a0){append("dependency:spoteffects:%d;",(int)a0);}
signed char (sticks)(struct permonst * a0){append("dependency:sticks:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[123];}
int (stop_donning)(struct obj * a0){append("dependency:stop_donning:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[124];}
void (stop_occupation)(void){append("dependency:stop_occupation;");}
void (swallowed)(int a0){append("dependency:swallowed:%d;",(int)a0);}
signed char (tele_restrict)(struct monst * a0){append("dependency:tele_restrict:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[125];}
void (teleds)(coordxy a0,coordxy a1,int a2){append("dependency:teleds:%d:%d:%d;",(int)a0,(int)a1,(int)a2);}
void (thrwmu)(struct monst * a0){append("dependency:thrwmu:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (tp_sensemon)(struct monst * a0){append("dependency:tp_sensemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[126];}
struct obj * (u_carried_gloves)(void){append("dependency:u_carried_gloves;");return opts[127]?(struct obj *)&objpool[1]:0;}
void (ugolemeffects)(int a0,int a1){append("dependency:ugolemeffects:%d:%d;",(int)a0,(int)a1);}
signed char (um_dist)(coordxy a0,coordxy a1,xint16 a2){append("dependency:um_dist:%d:%d:%d;",(int)a0,(int)a1,(int)a2);return opts[128];}
signed char (unconscious)(void){append("dependency:unconscious;");return opts[129];}
void (unleash_all)(void){append("dependency:unleash_all;");}
void (unmul)(const char * a0){append("dependency:unmul:%s;",a0?a0:"(null)");}
void (unplacebc)(void){append("dependency:unplacebc;");}
signed char (unresponsive)(void){append("dependency:unresponsive;");return opts[130];}
void (unstuck)(struct monst * a0){append("dependency:unstuck:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (update_inventory)(void){append("dependency:update_inventory;");}
signed char (ureflects)(const char * a0,const char * a1){append("dependency:ureflects:%s:%s;",a0?a0:"(null)",a1?a1:"(null)");return opts[131];}
int (use_offensive)(struct monst * a0){append("dependency:use_offensive:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[132];}
void (vision_recalc)(int a0){append("dependency:vision_recalc:%d;",(int)a0);}
void (wake_nearto)(coordxy a0,coordxy a1,int a2){append("dependency:wake_nearto:%d:%d:%d;",(int)a0,(int)a1,(int)a2);}
int (welded)(struct obj * a0){append("dependency:welded:%llu;",(unsigned long long)canonical((uintptr_t)a0));return opts[133];}
struct obj * (which_armor)(struct monst * a0,long a1){append("dependency:which_armor:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)a1);return opts[134]?(struct obj *)&objpool[1]:0;}
void (worm_move)(struct monst * a0){append("dependency:worm_move:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (xkilled)(struct monst * a0,int a1){append("dependency:xkilled:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}

#ifdef HYBRID_MHITU
extern void hitmsg(struct monst * mtmp,struct attack * mattk);
extern void teleport_mhitu_missmu(struct monst * mtmp,boolean nearmiss,struct attack * mattk);
#define missmu teleport_mhitu_missmu
extern const char * mswings_verb(struct obj * mwep,boolean bash);
extern void teleport_mhitu_mswings(struct monst * mtmp,struct obj * otemp,boolean bash);
#define mswings teleport_mhitu_mswings
extern const char * mpoisons_subj(struct monst * mtmp,struct attack * mattk);
extern void u_slow_down();
extern void teleport_mhitu_wildmiss(struct monst * mtmp,struct attack * mattk);
#define wildmiss teleport_mhitu_wildmiss
extern void expels(struct monst * mtmp,struct permonst * mdat,boolean message);
extern struct attack * getmattk(struct monst * magr,struct monst * mdef,int indx,int * prev_result,struct attack * alt_attk_buf);
extern void teleport_mhitu_calc_mattacku_vars(struct monst * mtmp,boolean * ranged,boolean * range2,boolean * foundyou,boolean * youseeit);
#define calc_mattacku_vars teleport_mhitu_calc_mattacku_vars
extern boolean mtrapped_in_pit(struct monst * mtmp);
extern int mattacku(struct monst * mtmp);
extern void teleport_mhitu_summonmu(struct monst * mtmp,boolean youseeit);
#define summonmu teleport_mhitu_summonmu
extern boolean diseasemu(struct permonst * mdat);
extern boolean u_slip_free(struct monst * mtmp,struct attack * mattk);
extern int magic_negation(struct monst * mon);
extern int teleport_mhitu_hitmu(struct monst * mtmp,struct attack * mattk);
#define hitmu teleport_mhitu_hitmu
extern boolean gulp_blnd_check();
extern int teleport_mhitu_gulpmu(struct monst * mtmp,struct attack * mattk);
#define gulpmu teleport_mhitu_gulpmu
extern int teleport_mhitu_explmu(struct monst * mtmp,struct attack * mattk,boolean ufound);
#define explmu teleport_mhitu_explmu
extern int gazemu(struct monst * mtmp,struct attack * mattk);
extern void mdamageu(struct monst * mtmp,int n);
extern int could_seduce(struct monst * magr,struct monst * mdef,struct attack * mattk);
extern int doseduce(struct monst * mon);
extern void teleport_mhitu_mayberem(struct monst * mon,const char * seducer,struct obj * obj,const char * str);
#define mayberem teleport_mhitu_mayberem
extern int teleport_mhitu_assess_dmg(struct monst * mtmp,int tmp);
#define assess_dmg teleport_mhitu_assess_dmg
extern boolean mon_avoiding_this_attack(struct monst * mtmp,int attkidx);
extern boolean ranged_attk_available(struct monst * mtmp);
extern int teleport_mhitu_passiveum(struct permonst * olduasmon,struct monst * mtmp,struct attack * mattk);
#define passiveum teleport_mhitu_passiveum
extern struct monst * cloneu();
#else
#include "../.cache/wasm64-build/tree/src/mhitu.c"
#endif
static uint64_t canonical(uint64_t value){
#define REGION(v,id) if(value>=(uintptr_t)&(v)&&value<(uintptr_t)&(v)+sizeof(v))return ((uint64_t)(id)<<48)+(value-(uintptr_t)&(v))
REGION(mons,1);REGION(objpool,2);REGION(mpool,3);REGION(u,4);REGION(gy.youmonst,5);REGION(trap,6);REGION(input,7);REGION(labelbuf,8);REGION(gu,9);for(int i=0;i<4;i++)if(pmcopies[i]&&value>=(uintptr_t)pmcopies[i]&&value<(uintptr_t)pmcopies[i]+sizeof *pmcopies[i])return ((uint64_t)12<<48)+i*sizeof *pmcopies[i]+value-(uintptr_t)pmcopies[i];REGION(visrows,13);REGION(vis,14);REGION(alt,15);REGION(prev,16);REGION(outputs,17);
#undef REGION
return value;}
static void typed_pointer(unsigned char*out,const void*base,const void*field){uint64_t v;memcpy(&v,field,8);v=canonical(v);memcpy(out+((const unsigned char*)field-(const unsigned char*)base),&v,8);}
static void typed_text_pointer(unsigned char*out,const void*base,const void*field){const unsigned char*p;memcpy(&p,field,8);uint64_t v=0;if(p){v=1469598103934665603ULL;for(;*p;p++){v^=*p;v*=1099511628211ULL;}}memcpy(out+((const unsigned char*)field-(const unsigned char*)base),&v,8);}
static void normalize_sysopt_s(unsigned char*,const void*,const struct sysopt_s*);
static void normalize_d_level(unsigned char*,const void*,const struct d_level*);
static void normalize_align(unsigned char*,const void*,const struct align*);
static void normalize_nhcoord(unsigned char*,const void*,const struct nhcoord*);
static void normalize_flag(unsigned char*,const void*,const struct flag*);
static void normalize_trap(unsigned char*,const void*,const struct trap*);
static void normalize_window_procs(unsigned char*,const void*,const struct window_procs*);
static void normalize_attribs(unsigned char*,const void*,const struct attribs*);
static void normalize_obj(unsigned char*,const void*,const struct obj*);
static void normalize_objclass(unsigned char*,const void*,const struct objclass*);
static void normalize_attack(unsigned char*,const void*,const struct attack*);
static void normalize_permonst(unsigned char*,const void*,const struct permonst*);
static void normalize_prop(unsigned char*,const void*,const struct prop*);
static void normalize_monst(unsigned char*,const void*,const struct monst*);
static void normalize_mhitm_data(unsigned char*,const void*,const struct mhitm_data*);
static void normalize_display_hints(unsigned char*,const void*,const struct display_hints*);
static void normalize_rm(unsigned char*,const void*,const struct rm*);
static void normalize_instance_globals_b(unsigned char*,const void*,const struct instance_globals_b*);
static void normalize_c_common_strings(unsigned char*,const void*,const struct c_common_strings*);
static void normalize_u_roleplay(unsigned char*,const void*,const struct u_roleplay*);
static void normalize_Role(unsigned char*,const void*,const struct Role*);
static void normalize_dgn_topology(unsigned char*,const void*,const struct dgn_topology*);
static void normalize_instance_globals_h(unsigned char*,const void*,const struct instance_globals_h*);
static void normalize_Gender(unsigned char*,const void*,const struct Gender*);
static void normalize_instance_globals_i(unsigned char*,const void*,const struct instance_globals_i*);
static void normalize_you(unsigned char*,const void*,const struct you*);
static void normalize_instance_globals_m(unsigned char*,const void*,const struct instance_globals_m*);
static void normalize_dlevel_t(unsigned char*,const void*,const dlevel_t*);
static void normalize_instance_globals_n(unsigned char*,const void*,const struct instance_globals_n*);
static void normalize_kinfo(unsigned char*,const void*,const struct kinfo*);
static void normalize_mvitals(unsigned char*,const void*,const struct mvitals*);
static void normalize_instance_globals_s(unsigned char*,const void*,const struct instance_globals_s*);
static void normalize_instance_globals_u(unsigned char*,const void*,const struct instance_globals_u*);
static void normalize_instance_globals_v(unsigned char*,const void*,const struct instance_globals_v*);
static void normalize_instance_globals_y(unsigned char*,const void*,const struct instance_globals_y*);
static void normalize_instance_globals_saved_d(unsigned char*,const void*,const struct instance_globals_saved_d*);
static void normalize_instance_globals_saved_k(unsigned char*,const void*,const struct instance_globals_saved_k*);
static void normalize_instance_globals_saved_l(unsigned char*,const void*,const struct instance_globals_saved_l*);
static void normalize_instance_globals_saved_m(unsigned char*,const void*,const struct instance_globals_saved_m*);
static void normalize_instance_globals_saved_p(unsigned char*,const void*,const struct instance_globals_saved_p*);
static void normalize_sysopt_s(unsigned char*out,const void*base,const struct sysopt_s*p){}
static void normalize_d_level(unsigned char*out,const void*base,const struct d_level*p){}
static void normalize_align(unsigned char*out,const void*base,const struct align*p){}
static void normalize_nhcoord(unsigned char*out,const void*base,const struct nhcoord*p){}
static void normalize_flag(unsigned char*out,const void*base,const struct flag*p){}
static void normalize_trap(unsigned char*out,const void*base,const struct trap*p){}
static void normalize_window_procs(unsigned char*out,const void*base,const struct window_procs*p){typed_pointer(out,base,&p->win_display_nhwindow);}
static void normalize_attribs(unsigned char*out,const void*base,const struct attribs*p){}
static void normalize_obj(unsigned char*out,const void*base,const struct obj*p){typed_pointer(out,base,&p->nobj);}
static void normalize_objclass(unsigned char*out,const void*base,const struct objclass*p){}
static void normalize_attack(unsigned char*out,const void*base,const struct attack*p){}
static void normalize_permonst(unsigned char*out,const void*base,const struct permonst*p){for(int i0=0;i0<3;i0++){typed_pointer(out,base,&p->pmnames[i0]);}for(int i0=0;i0<6;i0++){normalize_attack(out,base,&p->mattk[i0]);}}
static void normalize_prop(unsigned char*out,const void*base,const struct prop*p){}
static void normalize_monst(unsigned char*out,const void*base,const struct monst*p){typed_pointer(out,base,&p->data);typed_pointer(out,base,&p->minvent);typed_pointer(out,base,&p->mw);}
static void normalize_mhitm_data(unsigned char*out,const void*base,const struct mhitm_data*p){}
static void normalize_display_hints(unsigned char*out,const void*base,const struct display_hints*p){}
static void normalize_rm(unsigned char*out,const void*base,const struct rm*p){}
static void normalize_instance_globals_b(unsigned char*out,const void*base,const struct instance_globals_b*p){normalize_nhcoord(out,base,&p->bhitpos);}
static void normalize_c_common_strings(unsigned char*out,const void*base,const struct c_common_strings*p){typed_text_pointer(out,base,&p->c_something);typed_text_pointer(out,base,&p->c_Something);typed_text_pointer(out,base,&p->c_vision_clears);}
static void normalize_u_roleplay(unsigned char*out,const void*base,const struct u_roleplay*p){}
static void normalize_Role(unsigned char*out,const void*base,const struct Role*p){}
static void normalize_dgn_topology(unsigned char*out,const void*base,const struct dgn_topology*p){normalize_d_level(out,base,&p->d_rogue_level);}
static void normalize_instance_globals_h(unsigned char*out,const void*base,const struct instance_globals_h*p){typed_pointer(out,base,&p->hitmsg_prev);}
static void normalize_Gender(unsigned char*out,const void*base,const struct Gender*p){typed_text_pointer(out,base,&p->he);typed_text_pointer(out,base,&p->him);typed_text_pointer(out,base,&p->his);}
static void normalize_instance_globals_i(unsigned char*out,const void*base,const struct instance_globals_i*p){typed_pointer(out,base,&p->invent);}
static void normalize_you(unsigned char*out,const void*base,const struct you*p){normalize_d_level(out,base,&p->uz);for(int i0=0;i0<69;i0++){normalize_prop(out,base,&p->uprops[i0]);}normalize_u_roleplay(out,base,&p->uroleplay);normalize_align(out,base,&p->ualign);typed_pointer(out,base,&p->ustuck);typed_pointer(out,base,&p->usteed);}
static void normalize_instance_globals_m(unsigned char*out,const void*base,const struct instance_globals_m*p){typed_pointer(out,base,&p->mswallower);}
static void normalize_dlevel_t(unsigned char*out,const void*base,const dlevel_t*p){for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){typed_pointer(out,base,&p->objects[i0][i1]);}}for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){typed_pointer(out,base,&p->monsters[i0][i1]);}}}
static void normalize_instance_globals_n(unsigned char*out,const void*base,const struct instance_globals_n*p){typed_text_pointer(out,base,&p->nomovemsg);}
static void normalize_kinfo(unsigned char*out,const void*base,const struct kinfo*p){}
static void normalize_mvitals(unsigned char*out,const void*base,const struct mvitals*p){}
static void normalize_instance_globals_s(unsigned char*out,const void*base,const struct instance_globals_s*p){}
static void normalize_instance_globals_u(unsigned char*out,const void*base,const struct instance_globals_u*p){normalize_Role(out,base,&p->urole);}
static void normalize_instance_globals_v(unsigned char*out,const void*base,const struct instance_globals_v*p){typed_pointer(out,base,&p->viz_array);}
static void normalize_instance_globals_y(unsigned char*out,const void*base,const struct instance_globals_y*p){normalize_monst(out,base,&p->youmonst);}
static void normalize_instance_globals_saved_d(unsigned char*out,const void*base,const struct instance_globals_saved_d*p){normalize_dgn_topology(out,base,&p->dungeon_topology);}
static void normalize_instance_globals_saved_k(unsigned char*out,const void*base,const struct instance_globals_saved_k*p){normalize_kinfo(out,base,&p->killer);}
static void normalize_instance_globals_saved_l(unsigned char*out,const void*base,const struct instance_globals_saved_l*p){normalize_dlevel_t(out,base,&p->level);}
static void normalize_instance_globals_saved_m(unsigned char*out,const void*base,const struct instance_globals_saved_m*p){for(int i0=0;i0<383;i0++){normalize_mvitals(out,base,&p->mvitals[i0]);}}
static void normalize_instance_globals_saved_p(unsigned char*out,const void*base,const struct instance_globals_saved_p*p){}
static void dump(char**out,const void*data,size_t n,void(*norm)(unsigned char*,const void*,const void*)){unsigned char bytes[n];memcpy(bytes,data,n);if(norm)norm(bytes,data,data);static const char hex[]="0123456789abcdef";for(size_t i=0;i<n;i++){*(*out)++=hex[bytes[i]>>4];*(*out)++=hex[bytes[i]&15];}}
const char*probe_snapshot(void){char*out=statebuf;
#define DUMP(v,t) dump(&out,&(v),sizeof(v),(void(*)(unsigned char*,const void*,const void*))normalize_##t)
DUMP(u,you);DUMP(gy.youmonst,monst);for(int i=0;i<16;i++)DUMP(objpool[i],obj);for(int i=0;i<8;i++)DUMP(mpool[i],monst);DUMP(trap,trap);DUMP(disp,display_hints);
DUMP(gh,instance_globals_h);
DUMP(flags,flag);
DUMP(gv,instance_globals_v);
DUMP(sysopt,sysopt_s);
DUMP(gb,instance_globals_b);
DUMP(gn,instance_globals_n);
DUMP(svl,instance_globals_saved_l);
DUMP(svp,instance_globals_saved_p);
DUMP(gm,instance_globals_m);
DUMP(gs,instance_globals_s);
DUMP(svd,instance_globals_saved_d);
DUMP(svm,instance_globals_saved_m);
DUMP(gi,instance_globals_i);
DUMP(gu,instance_globals_u);
DUMP(svk,instance_globals_saved_k);
dump(&out,alt,sizeof alt,0);dump(&out,prev,sizeof prev,0);dump(&out,outputs,sizeof outputs,0);
#undef DUMP
out+=sprintf(out,";equip:%d,%d,%d,%d,%d,%d,%d,%d,%d;",oid(uwep),oid(uarm),oid(uarmc),oid(uarmu),oid(uarmh),oid(uarmg),oid(uarms),oid(uarmf),oid(uleft));*out=0;return statebuf;}
void probe_reset(void){
memset((void*)&gy,0,sizeof gy);
memset((void*)&u,0,sizeof u);
memset((void*)&gh,0,sizeof gh);
memset((void*)&flags,0,sizeof flags);
memset((void*)&objects,0,sizeof objects);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&gv,0,sizeof gv);
memset((void*)&disp,0,sizeof disp);
memset((void*)&sysopt,0,sizeof sysopt);
memset((void*)&gb,0,sizeof gb);
memset((void*)&gn,0,sizeof gn);
memset((void*)&svl,0,sizeof svl);
memset((void*)&svp,0,sizeof svp);
memset((void*)&gm,0,sizeof gm);
memset((void*)&gs,0,sizeof gs);
memset((void*)&svd,0,sizeof svd);
memset((void*)&svm,0,sizeof svm);
memset((void*)&uarmc,0,sizeof uarmc);
memset((void*)&uarm,0,sizeof uarm);
memset((void*)&uarmu,0,sizeof uarmu);
memset((void*)&uarmh,0,sizeof uarmh);
memset((void*)&gi,0,sizeof gi);
memset((void*)&gu,0,sizeof gu);
memset((void*)&uball,0,sizeof uball);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&svk,0,sizeof svk);
memset((void*)&uarmg,0,sizeof uarmg);
memset((void*)&uleft,0,sizeof uleft);
memset((void*)&uright,0,sizeof uright);
memset((void*)&uarmf,0,sizeof uarmf);
memset((void*)&uarms,0,sizeof uarms);
memset(objpool,0,sizeof objpool);memset(mpool,0,sizeof mpool);memset(&trap,0,sizeof trap);memset(alt,0,sizeof alt);memset(prev,0,sizeof prev);memset(outputs,0x55,sizeof outputs);memset(opts,0,sizeof opts);memset(input,0,sizeof input);memset(vis,0,sizeof vis);tracepos=0;tracebuf[0]=0;seed=1;reentered=0;if(growth){free(growth);growth=0;}
for(int y=0;y<ROWNO;y++){visrows[y]=vis[y];for(int x=0;x<COLNO;x++)svl.level.locations[x][y].typ=ROOM;}gv.viz_array=visrows;
for(int i=0;i<4;i++){if(pmcopies[i])free(pmcopies[i]);pmcopies[i]=0;}
for(int i=0;i<NUMMONS+1;i++){memset(&mons[i].pmnames,0,sizeof mons[i].pmnames);memset(&mons[i].mlet,0,sizeof mons[i].mlet);memset(&mons[i].mlevel,0,sizeof mons[i].mlevel);memset(&mons[i].mmove,0,sizeof mons[i].mmove);memset(&mons[i].ac,0,sizeof mons[i].ac);memset(&mons[i].mr,0,sizeof mons[i].mr);memset(&mons[i].maligntyp,0,sizeof mons[i].maligntyp);memset(&mons[i].geno,0,sizeof mons[i].geno);memset(&mons[i].mattk,0,sizeof mons[i].mattk);memset(&mons[i].cwt,0,sizeof mons[i].cwt);memset(&mons[i].cnutrit,0,sizeof mons[i].cnutrit);memset(&mons[i].msound,0,sizeof mons[i].msound);memset(&mons[i].msize,0,sizeof mons[i].msize);memset(&mons[i].mresists,0,sizeof mons[i].mresists);memset(&mons[i].mconveys,0,sizeof mons[i].mconveys);memset(&mons[i].mflags1,0,sizeof mons[i].mflags1);memset(&mons[i].mflags2,0,sizeof mons[i].mflags2);memset(&mons[i].mflags3,0,sizeof mons[i].mflags3);memset(&mons[i].difficulty,0,sizeof mons[i].difficulty);memset(&mons[i].mcolor,0,sizeof mons[i].mcolor);mons[i].mlevel=5;mons[i].msize=MZ_MEDIUM;mons[i].mlet=S_HUMAN;mons[i].mattk[0].aatyp=AT_WEAP;mons[i].mattk[0].adtyp=AD_PHYS;mons[i].mattk[0].damn=2;mons[i].mattk[0].damd=6;mons[i].mflags1=M1_HUMANOID;}
u.ux=20;u.uy=10;u.uz.dnum=1;u.uz.dlevel=3;u.ulevel=u.ulevelmax=10;u.uhp=u.uhpmax=40;u.uen=u.uenmax=30;u.mh=u.mhmax=50;u.umonnum=u.umonster=PM_HUMAN;u.ulycn=NON_PM;for(int i=0;i<A_MAX;i++)u.acurr.a[i]=u.amax.a[i]=12;
gu.urole.mnum=PM_ARCHEOLOGIST;gu.urace.mnum=PM_HUMAN;
gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mnum=PM_HUMAN;gy.youmonst.cham=NON_PM;gy.youmonst.m_id=1;gy.youmonst.mcansee=gy.youmonst.mcanmove=1;
for(int i=0;i<16;i++){objpool[i].otyp=LONG_SWORD;objpool[i].oclass=WEAPON_CLASS;objpool[i].quan=1;snprintf(labelbuf[i],sizeof labelbuf[i],"name%d",i);}
for(int i=0;i<8;i++){mpool[i].data=&mons[PM_HUMAN];mpool[i].mnum=PM_HUMAN;mpool[i].m_id=100+i;mpool[i].mx=21+i;mpool[i].my=10;mpool[i].mux=u.ux;mpool[i].muy=u.uy;mpool[i].mhp=mpool[i].mhpmax=20;mpool[i].m_lev=5;mpool[i].mcansee=mpool[i].mcanmove=1;mpool[i].cham=NON_PM;}
windowprocs.win_display_nhwindow=display_;sysopt.seduce=1;opts[18]=M_ATTK_HIT;
#ifndef HYBRID_MHITU
mon_currwep=0;
#endif
}
void probe_attributes(int i,int v){u.acurr.a[i]=v;}
void probe_option(int i,int v){if(i<0||i>=320)abort();opts[i]=v;if(i==48)seed=v;}
void probe_equipment(int k,int i){struct obj*o=i<0?0:&objpool[i];switch(k){case 0:uwep=o;break;case 1:uarm=o;break;case 2:uarmc=o;break;case 3:uarmu=o;break;case 4:uarmh=o;break;case 5:uarmg=o;break;case 6:uarms=o;break;case 7:uarmf=o;break;case 8:uleft=o;break;case 9:uright=o;break;case 10:uball=o;break;case 11:uchain=o;break;}}
void*probe_pointer(int k,int i){switch(k){case 0:return &mpool[i];case 1:return &objpool[i];case 2:return &mons[i];case 3:return &objects[i];case 4:return &trap;case 5:return input;case 6:return &gy.youmonst;case 8:return pmcopies[i];case 9:return &alt[i];case 10:return &prev[i];case 11:return &outputs[i];default:abort();}}
void probe_copy_permonst(int target,int source){if(pmcopies[target])free(pmcopies[target]);pmcopies[target]=malloc(sizeof *pmcopies[target]);if(!pmcopies[target])abort();memcpy(pmcopies[target],&mons[source],sizeof *pmcopies[target]);}
void probe_vision(int mask){for(int y=0;y<ROWNO;y++)for(int x=0;x<COLNO;x++)vis[y][x]=mask;}
const char*probe_trace(void){return tracebuf;}uint64_t probe_canonical(uintptr_t p){return canonical(p);}
#ifndef HYBRID_MHITU
uintptr_t probe_static(void){return canonical((uintptr_t)mon_currwep);}
#endif
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return sizeof mhitu_layout/sizeof mhitu_layout[0];}
const char*probe_layout_name(int i){return mhitu_layout[i].name;}
uint64_t probe_layout_value(int i){return mhitu_layout[i].value;}
void probe_call_hitmsg(struct monst * mtmp,struct attack * mattk){hitmsg(mtmp,mattk);}
void probe_call_missmu(struct monst * mtmp,boolean nearmiss,struct attack * mattk){missmu(mtmp,nearmiss,mattk);}
const char * probe_call_mswings_verb(struct obj * mwep,boolean bash){return mswings_verb(mwep,bash);}
void probe_call_mswings(struct monst * mtmp,struct obj * otemp,boolean bash){mswings(mtmp,otemp,bash);}
const char * probe_call_mpoisons_subj(struct monst * mtmp,struct attack * mattk){return mpoisons_subj(mtmp,mattk);}
void probe_call_u_slow_down(){u_slow_down();}
void probe_call_wildmiss(struct monst * mtmp,struct attack * mattk){wildmiss(mtmp,mattk);}
void probe_call_expels(struct monst * mtmp,struct permonst * mdat,boolean message){expels(mtmp,mdat,message);}
struct attack * probe_call_getmattk(struct monst * magr,struct monst * mdef,int indx,int * prev_result,struct attack * alt_attk_buf){return getmattk(magr,mdef,indx,prev_result,alt_attk_buf);}
void probe_call_calc_mattacku_vars(struct monst * mtmp,boolean * ranged,boolean * range2,boolean * foundyou,boolean * youseeit){calc_mattacku_vars(mtmp,ranged,range2,foundyou,youseeit);}
boolean probe_call_mtrapped_in_pit(struct monst * mtmp){return mtrapped_in_pit(mtmp);}
int probe_call_mattacku(struct monst * mtmp){return mattacku(mtmp);}
void probe_call_summonmu(struct monst * mtmp,boolean youseeit){summonmu(mtmp,youseeit);}
boolean probe_call_diseasemu(struct permonst * mdat){return diseasemu(mdat);}
boolean probe_call_u_slip_free(struct monst * mtmp,struct attack * mattk){return u_slip_free(mtmp,mattk);}
int probe_call_magic_negation(struct monst * mon){return magic_negation(mon);}
int probe_call_hitmu(struct monst * mtmp,struct attack * mattk){return hitmu(mtmp,mattk);}
boolean probe_call_gulp_blnd_check(){return gulp_blnd_check();}
int probe_call_gulpmu(struct monst * mtmp,struct attack * mattk){return gulpmu(mtmp,mattk);}
int probe_call_explmu(struct monst * mtmp,struct attack * mattk,boolean ufound){return explmu(mtmp,mattk,ufound);}
int probe_call_gazemu(struct monst * mtmp,struct attack * mattk){return gazemu(mtmp,mattk);}
void probe_call_mdamageu(struct monst * mtmp,int n){mdamageu(mtmp,n);}
int probe_call_could_seduce(struct monst * magr,struct monst * mdef,struct attack * mattk){return could_seduce(magr,mdef,mattk);}
int probe_call_doseduce(struct monst * mon){return doseduce(mon);}
void probe_call_mayberem(struct monst * mon,const char * seducer,struct obj * obj,const char * str){mayberem(mon,seducer,obj,str);}
int probe_call_assess_dmg(struct monst * mtmp,int tmp){return assess_dmg(mtmp,tmp);}
boolean probe_call_mon_avoiding_this_attack(struct monst * mtmp,int attkidx){return mon_avoiding_this_attack(mtmp,attkidx);}
boolean probe_call_ranged_attk_available(struct monst * mtmp){return ranged_attk_available(mtmp);}
int probe_call_passiveum(struct permonst * olduasmon,struct monst * mtmp,struct attack * mattk){return passiveum(olduasmon,mtmp,mattk);}
struct monst * probe_call_cloneu(){return cloneu();}
