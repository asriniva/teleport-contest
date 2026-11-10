/* Controlled DOTHROW native dependency world, not a complete game. */
#include "hack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <errno.h>
static char namebuf[256]="fixture",pronoun[16]="they";
__typeof__(objects) objects;
__typeof__(svc) svc;
__typeof__(uquiver) uquiver;
__typeof__(uwep) uwep;
__typeof__(gy) gy;
__typeof__(u) u;
__typeof__(uarmg) uarmg;
struct permonst mons[384]={{.pmidx=0},{.pmidx=1},{.pmidx=2},{.pmidx=3},{.pmidx=4},{.pmidx=5},{.pmidx=6},{.pmidx=7},{.pmidx=8},{.pmidx=9},{.pmidx=10},{.pmidx=11},{.pmidx=12},{.pmidx=13},{.pmidx=14},{.pmidx=15},{.pmidx=16},{.pmidx=17},{.pmidx=18},{.pmidx=19},{.pmidx=20},{.pmidx=21},{.pmidx=22},{.pmidx=23},{.pmidx=24},{.pmidx=25},{.pmidx=26},{.pmidx=27},{.pmidx=28},{.pmidx=29},{.pmidx=30},{.pmidx=31},{.pmidx=32},{.pmidx=33},{.pmidx=34},{.pmidx=35},{.pmidx=36},{.pmidx=37},{.pmidx=38},{.pmidx=39},{.pmidx=40},{.pmidx=41},{.pmidx=42},{.pmidx=43},{.pmidx=44},{.pmidx=45},{.pmidx=46},{.pmidx=47},{.pmidx=48},{.pmidx=49},{.pmidx=50},{.pmidx=51},{.pmidx=52},{.pmidx=53},{.pmidx=54},{.pmidx=55},{.pmidx=56},{.pmidx=57},{.pmidx=58},{.pmidx=59},{.pmidx=60},{.pmidx=61},{.pmidx=62},{.pmidx=63},{.pmidx=64},{.pmidx=65},{.pmidx=66},{.pmidx=67},{.pmidx=68},{.pmidx=69},{.pmidx=70},{.pmidx=71},{.pmidx=72},{.pmidx=73},{.pmidx=74},{.pmidx=75},{.pmidx=76},{.pmidx=77},{.pmidx=78},{.pmidx=79},{.pmidx=80},{.pmidx=81},{.pmidx=82},{.pmidx=83},{.pmidx=84},{.pmidx=85},{.pmidx=86},{.pmidx=87},{.pmidx=88},{.pmidx=89},{.pmidx=90},{.pmidx=91},{.pmidx=92},{.pmidx=93},{.pmidx=94},{.pmidx=95},{.pmidx=96},{.pmidx=97},{.pmidx=98},{.pmidx=99},{.pmidx=100},{.pmidx=101},{.pmidx=102},{.pmidx=103},{.pmidx=104},{.pmidx=105},{.pmidx=106},{.pmidx=107},{.pmidx=108},{.pmidx=109},{.pmidx=110},{.pmidx=111},{.pmidx=112},{.pmidx=113},{.pmidx=114},{.pmidx=115},{.pmidx=116},{.pmidx=117},{.pmidx=118},{.pmidx=119},{.pmidx=120},{.pmidx=121},{.pmidx=122},{.pmidx=123},{.pmidx=124},{.pmidx=125},{.pmidx=126},{.pmidx=127},{.pmidx=128},{.pmidx=129},{.pmidx=130},{.pmidx=131},{.pmidx=132},{.pmidx=133},{.pmidx=134},{.pmidx=135},{.pmidx=136},{.pmidx=137},{.pmidx=138},{.pmidx=139},{.pmidx=140},{.pmidx=141},{.pmidx=142},{.pmidx=143},{.pmidx=144},{.pmidx=145},{.pmidx=146},{.pmidx=147},{.pmidx=148},{.pmidx=149},{.pmidx=150},{.pmidx=151},{.pmidx=152},{.pmidx=153},{.pmidx=154},{.pmidx=155},{.pmidx=156},{.pmidx=157},{.pmidx=158},{.pmidx=159},{.pmidx=160},{.pmidx=161},{.pmidx=162},{.pmidx=163},{.pmidx=164},{.pmidx=165},{.pmidx=166},{.pmidx=167},{.pmidx=168},{.pmidx=169},{.pmidx=170},{.pmidx=171},{.pmidx=172},{.pmidx=173},{.pmidx=174},{.pmidx=175},{.pmidx=176},{.pmidx=177},{.pmidx=178},{.pmidx=179},{.pmidx=180},{.pmidx=181},{.pmidx=182},{.pmidx=183},{.pmidx=184},{.pmidx=185},{.pmidx=186},{.pmidx=187},{.pmidx=188},{.pmidx=189},{.pmidx=190},{.pmidx=191},{.pmidx=192},{.pmidx=193},{.pmidx=194},{.pmidx=195},{.pmidx=196},{.pmidx=197},{.pmidx=198},{.pmidx=199},{.pmidx=200},{.pmidx=201},{.pmidx=202},{.pmidx=203},{.pmidx=204},{.pmidx=205},{.pmidx=206},{.pmidx=207},{.pmidx=208},{.pmidx=209},{.pmidx=210},{.pmidx=211},{.pmidx=212},{.pmidx=213},{.pmidx=214},{.pmidx=215},{.pmidx=216},{.pmidx=217},{.pmidx=218},{.pmidx=219},{.pmidx=220},{.pmidx=221},{.pmidx=222},{.pmidx=223},{.pmidx=224},{.pmidx=225},{.pmidx=226},{.pmidx=227},{.pmidx=228},{.pmidx=229},{.pmidx=230},{.pmidx=231},{.pmidx=232},{.pmidx=233},{.pmidx=234},{.pmidx=235},{.pmidx=236},{.pmidx=237},{.pmidx=238},{.pmidx=239},{.pmidx=240},{.pmidx=241},{.pmidx=242},{.pmidx=243},{.pmidx=244},{.pmidx=245},{.pmidx=246},{.pmidx=247},{.pmidx=248},{.pmidx=249},{.pmidx=250},{.pmidx=251},{.pmidx=252},{.pmidx=253},{.pmidx=254},{.pmidx=255},{.pmidx=256},{.pmidx=257},{.pmidx=258},{.pmidx=259},{.pmidx=260},{.pmidx=261},{.pmidx=262},{.pmidx=263},{.pmidx=264},{.pmidx=265},{.pmidx=266},{.pmidx=267},{.pmidx=268},{.pmidx=269},{.pmidx=270},{.pmidx=271},{.pmidx=272},{.pmidx=273},{.pmidx=274},{.pmidx=275},{.pmidx=276},{.pmidx=277},{.pmidx=278},{.pmidx=279},{.pmidx=280},{.pmidx=281},{.pmidx=282},{.pmidx=283},{.pmidx=284},{.pmidx=285},{.pmidx=286},{.pmidx=287},{.pmidx=288},{.pmidx=289},{.pmidx=290},{.pmidx=291},{.pmidx=292},{.pmidx=293},{.pmidx=294},{.pmidx=295},{.pmidx=296},{.pmidx=297},{.pmidx=298},{.pmidx=299},{.pmidx=300},{.pmidx=301},{.pmidx=302},{.pmidx=303},{.pmidx=304},{.pmidx=305},{.pmidx=306},{.pmidx=307},{.pmidx=308},{.pmidx=309},{.pmidx=310},{.pmidx=311},{.pmidx=312},{.pmidx=313},{.pmidx=314},{.pmidx=315},{.pmidx=316},{.pmidx=317},{.pmidx=318},{.pmidx=319},{.pmidx=320},{.pmidx=321},{.pmidx=322},{.pmidx=323},{.pmidx=324},{.pmidx=325},{.pmidx=326},{.pmidx=327},{.pmidx=328},{.pmidx=329},{.pmidx=330},{.pmidx=331},{.pmidx=332},{.pmidx=333},{.pmidx=334},{.pmidx=335},{.pmidx=336},{.pmidx=337},{.pmidx=338},{.pmidx=339},{.pmidx=340},{.pmidx=341},{.pmidx=342},{.pmidx=343},{.pmidx=344},{.pmidx=345},{.pmidx=346},{.pmidx=347},{.pmidx=348},{.pmidx=349},{.pmidx=350},{.pmidx=351},{.pmidx=352},{.pmidx=353},{.pmidx=354},{.pmidx=355},{.pmidx=356},{.pmidx=357},{.pmidx=358},{.pmidx=359},{.pmidx=360},{.pmidx=361},{.pmidx=362},{.pmidx=363},{.pmidx=364},{.pmidx=365},{.pmidx=366},{.pmidx=367},{.pmidx=368},{.pmidx=369},{.pmidx=370},{.pmidx=371},{.pmidx=372},{.pmidx=373},{.pmidx=374},{.pmidx=375},{.pmidx=376},{.pmidx=377},{.pmidx=378},{.pmidx=379},{.pmidx=380},{.pmidx=381},{.pmidx=382},{.pmidx=383}};
__typeof__(svk) svk;
__typeof__(gu) gu;
__typeof__(gm) gm;
__typeof__(gc) gc;
__typeof__(uswapwep) uswapwep;
__typeof__(gi) gi;
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(svl) svl;
const struct Gender genders[3]={{.him=pronoun},{.him=pronoun},{.him=pronoun}};
__typeof__(uarmu) uarmu;
__typeof__(uarm) uarm;
__typeof__(uarmc) uarmc;
__typeof__(uball) uball;
__typeof__(svd) svd;
__typeof__(windowprocs) windowprocs;
__typeof__(gn) gn;
__typeof__(gt) gt;
__typeof__(uarmh) uarmh;
const struct c_common_strings c_common_strings={.c_something=namebuf,.c_Something=namebuf,.c_vision_clears=namebuf};
__typeof__(gb) gb;
__typeof__(go) go;
__typeof__(uchain) uchain;
__typeof__(gv) gv;
__typeof__(gk) gk;
__typeof__(svq) svq;
__typeof__(ublindf) ublindf;
__typeof__(gh) gh;

static char tracebuf[4194304];static size_t traceused;static uint32_t seed=1;static int draws,callerline,options[128],errorcode,predicatecalls;static const char*callerfile,*callerfn;static jmp_buf panicframe;
static struct obj opool[512];static struct monst mpool[128];static struct trap tpool[64];static struct eshk testeshk;static struct mextra testmextra;static int no,nm,nt;
static coord ccoord[2];static int scalar=10;static char literal[256],roomsbuf[8];_Alignas(16)static unsigned char scratch[8192];
static struct throw_and_return_weapon returning;static int(*queue[64])(void);static int nq;
static void*allocations[1024];static size_t allocsizes[1024];static int nalloc;
static void logfmt(const char*f,...){va_list ap;va_start(ap,f);int n=vsnprintf(tracebuf+traceused,sizeof(tracebuf)-traceused,f,ap);va_end(ap);if(n>0)traceused+=(size_t)n;if(traceused>=sizeof(tracebuf))abort();}
static void fpidentity(uintptr_t);static void ptrlog(const void*p){if(!p){logfmt("0");return;}

if((uintptr_t)p>=(uintptr_t)&objects&&(uintptr_t)p<(uintptr_t)&objects+sizeof objects){logfmt("G0+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&objects));return;}
if((uintptr_t)p>=(uintptr_t)&svc&&(uintptr_t)p<(uintptr_t)&svc+sizeof svc){logfmt("G1+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svc));return;}
if((uintptr_t)p>=(uintptr_t)&uquiver&&(uintptr_t)p<(uintptr_t)&uquiver+sizeof uquiver){logfmt("G2+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uquiver));return;}
if((uintptr_t)p>=(uintptr_t)&uwep&&(uintptr_t)p<(uintptr_t)&uwep+sizeof uwep){logfmt("G3+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uwep));return;}
if((uintptr_t)p>=(uintptr_t)&gy&&(uintptr_t)p<(uintptr_t)&gy+sizeof gy){logfmt("G4+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gy));return;}
if((uintptr_t)p>=(uintptr_t)&u&&(uintptr_t)p<(uintptr_t)&u+sizeof u){logfmt("G5+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&u));return;}
if((uintptr_t)p>=(uintptr_t)&uarmg&&(uintptr_t)p<(uintptr_t)&uarmg+sizeof uarmg){logfmt("G6+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uarmg));return;}
if((uintptr_t)p>=(uintptr_t)&mons&&(uintptr_t)p<(uintptr_t)&mons+sizeof mons){logfmt("G7+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mons));return;}
if((uintptr_t)p>=(uintptr_t)&svk&&(uintptr_t)p<(uintptr_t)&svk+sizeof svk){logfmt("G8+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svk));return;}
if((uintptr_t)p>=(uintptr_t)&gu&&(uintptr_t)p<(uintptr_t)&gu+sizeof gu){logfmt("G9+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gu));return;}
if((uintptr_t)p>=(uintptr_t)&gm&&(uintptr_t)p<(uintptr_t)&gm+sizeof gm){logfmt("G10+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gm));return;}
if((uintptr_t)p>=(uintptr_t)&gc&&(uintptr_t)p<(uintptr_t)&gc+sizeof gc){logfmt("G11+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gc));return;}
if((uintptr_t)p>=(uintptr_t)&uswapwep&&(uintptr_t)p<(uintptr_t)&uswapwep+sizeof uswapwep){logfmt("G12+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uswapwep));return;}
if((uintptr_t)p>=(uintptr_t)&gi&&(uintptr_t)p<(uintptr_t)&gi+sizeof gi){logfmt("G13+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gi));return;}
if((uintptr_t)p>=(uintptr_t)&flags&&(uintptr_t)p<(uintptr_t)&flags+sizeof flags){logfmt("G14+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&flags));return;}
if((uintptr_t)p>=(uintptr_t)&iflags&&(uintptr_t)p<(uintptr_t)&iflags+sizeof iflags){logfmt("G15+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&iflags));return;}
if((uintptr_t)p>=(uintptr_t)&svl&&(uintptr_t)p<(uintptr_t)&svl+sizeof svl){logfmt("G16+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svl));return;}
if((uintptr_t)p>=(uintptr_t)&genders&&(uintptr_t)p<(uintptr_t)&genders+sizeof genders){logfmt("G17+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&genders));return;}
if((uintptr_t)p>=(uintptr_t)&uarmu&&(uintptr_t)p<(uintptr_t)&uarmu+sizeof uarmu){logfmt("G18+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uarmu));return;}
if((uintptr_t)p>=(uintptr_t)&uarm&&(uintptr_t)p<(uintptr_t)&uarm+sizeof uarm){logfmt("G19+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uarm));return;}
if((uintptr_t)p>=(uintptr_t)&uarmc&&(uintptr_t)p<(uintptr_t)&uarmc+sizeof uarmc){logfmt("G20+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uarmc));return;}
if((uintptr_t)p>=(uintptr_t)&uball&&(uintptr_t)p<(uintptr_t)&uball+sizeof uball){logfmt("G21+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uball));return;}
if((uintptr_t)p>=(uintptr_t)&svd&&(uintptr_t)p<(uintptr_t)&svd+sizeof svd){logfmt("G22+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svd));return;}
if((uintptr_t)p>=(uintptr_t)&windowprocs&&(uintptr_t)p<(uintptr_t)&windowprocs+sizeof windowprocs){logfmt("G23+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&windowprocs));return;}
if((uintptr_t)p>=(uintptr_t)&gn&&(uintptr_t)p<(uintptr_t)&gn+sizeof gn){logfmt("G24+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gn));return;}
if((uintptr_t)p>=(uintptr_t)&gt&&(uintptr_t)p<(uintptr_t)&gt+sizeof gt){logfmt("G25+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gt));return;}
if((uintptr_t)p>=(uintptr_t)&uarmh&&(uintptr_t)p<(uintptr_t)&uarmh+sizeof uarmh){logfmt("G26+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uarmh));return;}
if((uintptr_t)p>=(uintptr_t)&c_common_strings&&(uintptr_t)p<(uintptr_t)&c_common_strings+sizeof c_common_strings){logfmt("G27+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&c_common_strings));return;}
if((uintptr_t)p>=(uintptr_t)&gb&&(uintptr_t)p<(uintptr_t)&gb+sizeof gb){logfmt("G28+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gb));return;}
if((uintptr_t)p>=(uintptr_t)&go&&(uintptr_t)p<(uintptr_t)&go+sizeof go){logfmt("G29+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&go));return;}
if((uintptr_t)p>=(uintptr_t)&uchain&&(uintptr_t)p<(uintptr_t)&uchain+sizeof uchain){logfmt("G30+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&uchain));return;}
if((uintptr_t)p>=(uintptr_t)&gv&&(uintptr_t)p<(uintptr_t)&gv+sizeof gv){logfmt("G31+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gv));return;}
if((uintptr_t)p>=(uintptr_t)&gk&&(uintptr_t)p<(uintptr_t)&gk+sizeof gk){logfmt("G32+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gk));return;}
if((uintptr_t)p>=(uintptr_t)&svq&&(uintptr_t)p<(uintptr_t)&svq+sizeof svq){logfmt("G33+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&svq));return;}
if((uintptr_t)p>=(uintptr_t)&ublindf&&(uintptr_t)p<(uintptr_t)&ublindf+sizeof ublindf){logfmt("G34+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ublindf));return;}
if((uintptr_t)p>=(uintptr_t)&gh&&(uintptr_t)p<(uintptr_t)&gh+sizeof gh){logfmt("G35+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&gh));return;}
if((uintptr_t)p>=(uintptr_t)&opool&&(uintptr_t)p<(uintptr_t)&opool+sizeof opool){logfmt("opool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&opool));return;}
if((uintptr_t)p>=(uintptr_t)&mpool&&(uintptr_t)p<(uintptr_t)&mpool+sizeof mpool){logfmt("mpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&mpool));return;}
if((uintptr_t)p>=(uintptr_t)&tpool&&(uintptr_t)p<(uintptr_t)&tpool+sizeof tpool){logfmt("tpool+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&tpool));return;}
if((uintptr_t)p>=(uintptr_t)&testeshk&&(uintptr_t)p<(uintptr_t)&testeshk+sizeof testeshk){logfmt("testeshk+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&testeshk));return;}
if((uintptr_t)p>=(uintptr_t)&testmextra&&(uintptr_t)p<(uintptr_t)&testmextra+sizeof testmextra){logfmt("testmextra+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&testmextra));return;}
if((uintptr_t)p>=(uintptr_t)&ccoord&&(uintptr_t)p<(uintptr_t)&ccoord+sizeof ccoord){logfmt("ccoord+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&ccoord));return;}
if((uintptr_t)p>=(uintptr_t)&scalar&&(uintptr_t)p<(uintptr_t)&scalar+sizeof scalar){logfmt("scalar+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&scalar));return;}
if((uintptr_t)p>=(uintptr_t)&literal&&(uintptr_t)p<(uintptr_t)&literal+sizeof literal){logfmt("literal+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&literal));return;}
if((uintptr_t)p>=(uintptr_t)&roomsbuf&&(uintptr_t)p<(uintptr_t)&roomsbuf+sizeof roomsbuf){logfmt("roomsbuf+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&roomsbuf));return;}
if((uintptr_t)p>=(uintptr_t)&scratch&&(uintptr_t)p<(uintptr_t)&scratch+sizeof scratch){logfmt("scratch+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&scratch));return;}
if((uintptr_t)p>=(uintptr_t)&returning&&(uintptr_t)p<(uintptr_t)&returning+sizeof returning){logfmt("returning+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&returning));return;}
if((uintptr_t)p>=(uintptr_t)&namebuf&&(uintptr_t)p<(uintptr_t)&namebuf+sizeof namebuf){logfmt("namebuf+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&namebuf));return;}
if((uintptr_t)p>=(uintptr_t)&pronoun&&(uintptr_t)p<(uintptr_t)&pronoun+sizeof pronoun){logfmt("pronoun+%llu",(unsigned long long)((uintptr_t)p-(uintptr_t)&pronoun));return;}

for(int i=0;i<nalloc;i++)if(allocations[i]&&(uintptr_t)p>=(uintptr_t)allocations[i]&&(uintptr_t)p<(uintptr_t)allocations[i]+allocsizes[i]){logfmt("A%d+%llu",i,(unsigned long long)((uintptr_t)p-(uintptr_t)allocations[i]));return;}logfmt("UNKNOWN:%llu",(unsigned long long)(uintptr_t)p);}
void*__real_malloc(size_t);void __real_free(void*);void*__wrap_malloc(size_t n){if(nalloc==1024)abort();void*p=__real_malloc(n);if(p)memset(p,0,n);allocations[nalloc]=p;allocsizes[nalloc++]=n;return p;}
void __wrap_free(void*p){logfmt("free(");ptrlog(p);logfmt(")\n");for(int i=0;i<nalloc;i++)if(allocations[i]==p)allocations[i]=0;__real_free(p);}
static int roll(const char*n,int bound){if(bound<=0){logfmt("BADRNG %d\n",bound);longjmp(panicframe,2);}seed=seed*1664525U+1013904223U;int v=seed%(unsigned)bound;draws++;logfmt("%s[%s:%d:%s](%d)=%d\n",n,callerfile?callerfile:"",callerline,callerfn?callerfn:"",bound,v);return v;}
static struct obj*fixture_newobj(int typ){if(no==512)abort();struct obj*o=&opool[no++];memset(o,0,sizeof*o);o->o_id=no;o->otyp=typ;o->oclass=objects[typ].oc_class;o->quan=1;o->where=OBJ_FREE;return o;}
static void fixture_delete(struct obj*o){if(!o)return;for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)if(svl.level.objects[x][y]==o)svl.level.objects[x][y]=0;if(gt.thrownobj==o)gt.thrownobj=0;o->where=OBJ_DELETED;}
static boolean fixture_predicate(void*arg,coordxy x,coordxy y){predicatecalls++;logfmt("predicate(INT:%d,%d,%d)\n",*(int*)arg,x,y);return !options[20]||predicatecalls<options[20];}
static void fixture_delay(void){logfmt("window.delay()\n");}

int getdir(const char * a0){logfmt("getdir(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");if(options[47]){svc.context.objsplit.parent_oid=123456;svc.context.objsplit.child_oid=987654;}return !options[0];}
boolean canletgo(struct obj * a0,const char * a1){logfmt("canletgo(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");return !options[1];}
boolean is_art(struct obj * a0,int a1){logfmt("is_art(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return a0&&a0->oartifact==a1;}
char * xname(struct obj * a0){logfmt("xname(");ptrlog(a0);logfmt(")\n");return namebuf;}
char * The(const char * a0){logfmt("The(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return(char*)a0;}
schar acurr(int a0){logfmt("acurr(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return options[6]?options[6]:18;}
void u_wipe_engr(int a0){logfmt("u_wipe_engr(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
char * corpse_xname(struct obj * a0,const char * a1,unsigned int a2){logfmt("corpse_xname(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return namebuf;}
const char * body_part(int a0){logfmt("body_part(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return namebuf;}
char * makeplural(const char * a0){logfmt("makeplural(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return(char*)a0;}
char * killer_xname(struct obj * a0){logfmt("killer_xname(");ptrlog(a0);logfmt(")\n");return namebuf;}
void instapetrify(const char * a0){logfmt("instapetrify(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");longjmp(panicframe,4);}
int welded(struct obj * a0){logfmt("welded(");ptrlog(a0);logfmt(")\n");return options[3];}
void weldmsg(struct obj * a0){logfmt("weldmsg(");ptrlog(a0);logfmt(")\n");}
void dry_a_towel(struct obj * a0,int a1,boolean a2){logfmt("dry_a_towel(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
int weapon_type(struct obj * a0){logfmt("weapon_type(");ptrlog(a0);logfmt(")\n");return a0?abs(objects[a0->otyp].oc_skill):P_NONE;}
boolean is_quest_artifact(struct obj * a0){logfmt("is_quest_artifact(");ptrlog(a0);logfmt(")\n");return options[41];}
schar acurrstr(void){logfmt("acurrstr(");logfmt(")\n");return options[6]?options[6]:18;}
boolean (rng_log_enabled)(void){return TRUE;}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){callerfile=a0;callerline=a1;callerfn=a2;}
int (rnd)(int a0){return roll("rnd",a0)+1;}
const char * singular(struct obj * a0,char *(*a1)(struct obj *)){logfmt("singular(");ptrlog(a0);logfmt(",");fpidentity((uintptr_t)a1);logfmt(")\n");if(a1!=(xname))abort();return a1(a0);}
void __assert_fail(const char * a0,const char * a1,int a2,const char * a3){logfmt("__assert_fail(");logfmt("%s",a0?a0:"<null>");logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%s",a3?a3:"<null>");logfmt(")\n");longjmp(panicframe,3);}
struct obj * splitobj(struct obj * a0,long a1){logfmt("splitobj(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");struct obj*o=fixture_newobj(a0->otyp);*o=*a0;o->o_id=no;o->quan=a1;a0->quan-=a1;svc.context.objsplit.parent_oid=a0->o_id;svc.context.objsplit.child_oid=o->o_id;return o;}
void remove_worn_item(struct obj * a0,boolean a1){logfmt("remove_worn_item(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");a0->owornmask=0;if(uwep==a0)uwep=0;if(uquiver==a0)uquiver=0;}
void freeinv(struct obj * a0){logfmt("freeinv(");ptrlog(a0);logfmt(")\n");a0->where=OBJ_FREE;if(gi.invent==a0)gi.invent=a0->nobj;}
void encumber_msg(void){logfmt("encumber_msg(");logfmt(")\n");}
struct obj * unsplitobj(struct obj * a0){logfmt("unsplitobj(");ptrlog(a0);logfmt(")\n");logfmt("split_context=%u,%u\n",svc.context.objsplit.parent_oid,svc.context.objsplit.child_oid);if(options[7])return 0;if(a0!=&opool[0])opool[0].quan+=a0->quan;svc.context.objsplit.parent_oid=svc.context.objsplit.child_oid=0;return &opool[0];}
boolean check_capacity(const char * a0){logfmt("check_capacity(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return options[4];}
struct obj * getobj(const char * a0,int (*a1)(struct obj *),unsigned int a2){logfmt("getobj(");logfmt("%s",a0?a0:"<null>");logfmt(",");fpidentity((uintptr_t)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");int result=a1(options[5]?0:&opool[0]);logfmt("getobj.callback=%d\n",result);return options[5]?0:&opool[0];}
void setuqwep(struct obj * a0){logfmt("setuqwep(");ptrlog(a0);logfmt(")\n");uquiver=a0;if(a0)a0->owornmask|=W_QUIVER;}
int use_pole(struct obj * a0,boolean a1){logfmt("use_pole(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return ECMD_TIME;}
int use_whip(struct obj * a0){logfmt("use_whip(");ptrlog(a0);logfmt(")\n");return ECMD_TIME;}
void cmdq_add_ec(int a0,int (*a1)(void)){logfmt("cmdq_add_ec(");logfmt("%llu",(unsigned long long)a0);logfmt(",");fpidentity((uintptr_t)a1);logfmt(")\n");if(nq==64)abort();queue[nq++]=a1;}
void prinv(const char * a0,struct obj * a1,long a2){logfmt("prinv(");logfmt("%s",a0?a0:"<null>");logfmt(",");ptrlog(a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
int doquiver_core(const char * a0){logfmt("doquiver_core(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");if(!options[8])uquiver=&opool[0];return options[8]?ECMD_CANCEL:ECMD_OK;}
boolean could_pole_mon(void){logfmt("could_pole_mon(");logfmt(")\n");return 0;}
void cmdq_add_key(int a0,char a1){logfmt("cmdq_add_key(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
const char * ordin(int a0){logfmt("ordin(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return namebuf;}
void dropy(struct obj * a0){logfmt("dropy(");ptrlog(a0);logfmt(")\n");place_object(a0,u.ux,u.uy);}
void doaltarobj(struct obj * a0){logfmt("doaltarobj(");ptrlog(a0);logfmt(")\n");}
const char * surface(coordxy a0,coordxy a1){logfmt("surface(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return namebuf;}
struct trap * t_at(coordxy a0,coordxy a1){logfmt("t_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[2]&&tpool[0].tx==a0&&tpool[0].ty==a1?&tpool[0]:0;}
char * Doname2(struct obj * a0){logfmt("Doname2(");ptrlog(a0);logfmt(")\n");return namebuf;}
char * otense(struct obj * a0,const char * a1){logfmt("otense(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");return(char*)a1;}
boolean ship_object(struct obj * a0,coordxy a1,coordxy a2,boolean a3){logfmt("ship_object(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");if(options[34])fixture_delete(a0);return options[34];}
void dropz(struct obj * a0,boolean a1){logfmt("dropz(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");place_object(a0,u.ux,u.uy);}
int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
boolean in_out_region(coordxy a0,coordxy a1){logfmt("in_out_region(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return !options[11];}
boolean may_passwall(coordxy a0,coordxy a1){logfmt("may_passwall(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return !options[12];}
boolean closed_door(coordxy a0,coordxy a1){logfmt("closed_door(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&levl[a0][a1].typ==DOOR&&(levl[a0][a1].doormask&D_CLOSED);}
struct obj * sobj_at(int a0,coordxy a1,coordxy a2){logfmt("sobj_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");for(int i=0;i<no;i++)if(opool[i].otyp==a0&&opool[i].ox==a1&&opool[i].oy==a2&&opool[i].where==OBJ_FLOOR)return &opool[i];return 0;}
boolean bad_rock(struct permonst * a0,coordxy a1,coordxy a2){logfmt("bad_rock(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return options[12];}
int inv_weight(void){logfmt("inv_weight(");logfmt(")\n");return options[13];}
int weight_cap(void){logfmt("weight_cap(");logfmt(")\n");return 1000;}
void losehp(int a0,const char * a1,schar a2){logfmt("losehp(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");u.uhp-=a0;}
void wake_nearto(coordxy a0,coordxy a1,int a2){logfmt("wake_nearto(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
int glyph_at(coordxy a0,coordxy a1){logfmt("glyph_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return 0;}
char * x_monnam(struct monst * a0,int a1,const char * a2,int a3,boolean a4){logfmt("x_monnam(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");return namebuf;}
int pronoun_gender(struct monst * a0,unsigned int a1){logfmt("pronoun_gender(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return 0;}
void wakeup(struct monst * a0,boolean a1){logfmt("wakeup(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
int canseemon(struct monst * a0){logfmt("canseemon(");ptrlog(a0);logfmt(")\n");return !options[15];}
int sensemon(struct monst * a0){logfmt("sensemon(");ptrlog(a0);logfmt(")\n");return options[16];}
void map_invisible(coordxy a0,coordxy a1){logfmt("map_invisible(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void setmangry(struct monst * a0,boolean a1){logfmt("setmangry(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
const char * pmname(struct permonst * a0,int a1){logfmt("pmname(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return namebuf;}
char * an(const char * a0){logfmt("an(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return(char*)a0;}
struct obj * which_armor(struct monst * a0,long a1){logfmt("which_armor(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[17]?&opool[1]:0;}
void minstapetrify(struct monst * a0,boolean a1){logfmt("minstapetrify(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
boolean drag_ball(coordxy a0,coordxy a1,int * a2,coordxy * a3,coordxy * a4,coordxy * a5,coordxy * a6,boolean * a7,boolean a8){logfmt("drag_ball(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("OUT:int");logfmt(",");logfmt("OUT:short");logfmt(",");logfmt("OUT:short");logfmt(",");logfmt("OUT:short");logfmt(",");logfmt("OUT:short");logfmt(",");logfmt("OUT:signed char");logfmt(",");logfmt("%llu",(unsigned long long)a8);logfmt(")\n");*a2=0;*a3=a0;*a4=a1;*a5=a0;*a6=a1;*a7=0;return !options[18];}
void move_bc(int a0,int a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5){logfmt("move_bc(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(",");logfmt("%llu",(unsigned long long)a5);logfmt(")\n");}
void u_on_newpos(coordxy a0,coordxy a1){logfmt("u_on_newpos(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");u.ux=a0;u.uy=a1;}
void newsym(coordxy a0,coordxy a1){logfmt("newsym(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void vision_recalc(int a0){logfmt("vision_recalc(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
void flush_screen(int a0){logfmt("flush_screen(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
void switch_terrain(void){logfmt("switch_terrain(");logfmt(")\n");}
void check_special_room(boolean a0){logfmt("check_special_room(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
boolean is_pool(coordxy a0,coordxy a1){logfmt("is_pool(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&(levl[a0][a1].typ==POOL||levl[a0][a1].typ==MOAT||levl[a0][a1].typ==WATER);}
boolean is_waterwall(coordxy a0,coordxy a1){logfmt("is_waterwall(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[19];}
boolean on_level(d_level * a0,d_level * a1){logfmt("on_level(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
boolean drown(void){logfmt("drown(");logfmt(")\n");return 0;}
boolean is_moat(coordxy a0,coordxy a1){logfmt("is_moat(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&levl[a0][a1].typ==MOAT;}
boolean is_lava(coordxy a0,coordxy a1){logfmt("is_lava(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return isok(a0,a1)&&levl[a0][a1].typ==LAVAPOOL;}
void dotrap(struct trap * a0,unsigned int a1){logfmt("dotrap(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
const char * trapname(int a0,boolean a1){logfmt("trapname(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return namebuf;}
boolean goodpos(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){logfmt("goodpos(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");ptrlog(a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return !options[10];}
boolean m_in_out_region(struct monst * a0,coordxy a1,coordxy a2){logfmt("m_in_out_region(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return !options[11];}
void place_monster(struct monst * a0,coordxy a1,coordxy a2){logfmt("place_monster(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");a0->mx=a1;a0->my=a2;svl.level.monsters[a1][a2]=a0;}
void set_apparxy(struct monst * a0){logfmt("set_apparxy(");ptrlog(a0);logfmt(")\n");}
int mintrap(struct monst * a0,unsigned int a1){logfmt("mintrap(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[21];}
char * Monnam(struct monst * a0){logfmt("Monnam(");ptrlog(a0);logfmt(")\n");return namebuf;}
char * a_monnam(struct monst * a0){logfmt("a_monnam(");ptrlog(a0);logfmt(")\n");return namebuf;}
char * Some_Monnam(struct monst * a0){logfmt("Some_Monnam(");ptrlog(a0);logfmt(")\n");return namebuf;}
void stop_occupation(void){logfmt("stop_occupation(");logfmt(")\n");}
void nomul(int a0){logfmt("nomul(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
const char * hliquid(const char * a0){logfmt("hliquid(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return namebuf;}
int sgn(int a0){logfmt("sgn(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return(a0>0)-(a0<0);}
void seemimic(struct monst * a0){logfmt("seemimic(");ptrlog(a0);logfmt(")\n");}
int minliquid(struct monst * a0){logfmt("minliquid(");ptrlog(a0);logfmt(")\n");return options[21];}
struct monst * shop_keeper(char a0){logfmt("shop_keeper(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return options[9]?&mpool[0]:0;}
boolean costly_spot(coordxy a0,coordxy a1){logfmt("costly_spot(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[9];}
char * in_rooms(coordxy a0,coordxy a1,int a2){logfmt("in_rooms(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");roomsbuf[0]=options[9]?ROOMOFFSET:0;roomsbuf[1]=0;return roomsbuf;}
boolean is_unpaid(struct obj * a0){logfmt("is_unpaid(");ptrlog(a0);logfmt(")\n");return a0->unpaid;}
long stolen_value(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){logfmt("stolen_value(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");return options[9]?INT64_C(0x20000000000001):0;}
long contained_gold(struct obj * a0,boolean a1){logfmt("contained_gold(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return INT64_C(0x40000000000003);}
void subfrombill(struct obj * a0,struct monst * a1){logfmt("subfrombill(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");}
void donate_gold(long a0,struct monst * a1,boolean a2){logfmt("donate_gold(");logfmt("%llu",(unsigned long long)a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
void sellobj(struct obj * a0,coordxy a1,coordxy a2){logfmt("sellobj(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
boolean has_ceiling(d_level * a0){logfmt("has_ceiling(");ptrlog(a0);logfmt(")\n");return !options[22];}
const char * ceiling(coordxy a0,coordxy a1){logfmt("ceiling(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return namebuf;}
void potionhit(struct monst * a0,struct obj * a1,int a2){logfmt("potionhit(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
boolean can_blnd(struct monst * a0,struct monst * a1,uchar a2,struct obj * a3){logfmt("can_blnd(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");ptrlog(a3);logfmt(")\n");return options[23];}
boolean poly_when_stoned(struct permonst * a0){logfmt("poly_when_stoned(");ptrlog(a0);logfmt(")\n");return options[24];}
int polymon(int a0){logfmt("polymon(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return options[24];}
const char * helm_simple_name(struct obj * a0){logfmt("helm_simple_name(");ptrlog(a0);logfmt(")\n");return namebuf;}
void make_blinded(long a0,boolean a1){logfmt("make_blinded(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");u.uprops[BLINDED].intrinsic=a0;}
boolean hard_helmet(struct obj * a0){logfmt("hard_helmet(");ptrlog(a0);logfmt(")\n");return a0!=0;}
boolean hates_silver(struct permonst * a0){logfmt("hates_silver(");ptrlog(a0);logfmt(")\n");return options[25];}
int dmgval(struct obj * a0,struct monst * a1){logfmt("dmgval(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return options[26];}
int (rn2)(int a0){return roll("rn2",a0);}
boolean artifact_hit(struct monst * a0,struct monst * a1,struct obj * a2,int * a3,int a4){logfmt("artifact_hit(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");ptrlog(a2);logfmt(",");logfmt("INT:%d",*a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(")\n");*a3+=options[27];return options[27]!=0;}
boolean mon_hates_blessings(struct monst * a0){logfmt("mon_hates_blessings(");ptrlog(a0);logfmt(")\n");return 0;}
char * thesimpleoname(struct obj * a0){logfmt("thesimpleoname(");ptrlog(a0);logfmt(")\n");return namebuf;}
void hit(const char * a0,struct monst * a1,const char * a2){logfmt("hit(");logfmt("%s",a0?a0:"<null>");logfmt(",");ptrlog(a1);logfmt(",");logfmt("%s",a2?a2:"<null>");logfmt(")\n");}
void done(int a0){logfmt("done(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");longjmp(panicframe,5);}
int (rn2_on_display_rng)(int a0){return roll("display_rng",a0);}
void tmp_at(coordxy a0,coordxy a1){logfmt("tmp_at(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
int mpickobj(struct monst * a0,struct obj * a1){logfmt("mpickobj(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");a1->where=OBJ_MINVENT;a1->nobj=a0->minvent;a0->minvent=a1;gt.thrownobj=0;return 0;}
boolean snuff_candle(struct obj * a0){logfmt("snuff_candle(");ptrlog(a0);logfmt(")\n");return 0;}
char inside_shop(coordxy a0,coordxy a1){logfmt("inside_shop(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return options[9]?ROOMOFFSET:0;}
void hot_pursuit(struct monst * a0){logfmt("hot_pursuit(");ptrlog(a0);logfmt(")\n");}
const struct throw_and_return_weapon * autoreturn_weapon(struct obj * a0){logfmt("autoreturn_weapon(");ptrlog(a0);logfmt(")\n");if(!options[28])return 0;returning.otyp=a0->otyp;returning.range=16;returning.tethered=options[28]==2;return &returning;}
char * Tobjnam(struct obj * a0,const char * a1){logfmt("Tobjnam(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");return namebuf;}
int calc_capacity(int a0){logfmt("calc_capacity(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return options[14];}
char * the(const char * a0){logfmt("the(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return(char*)a0;}
void exercise(int a0,boolean a1){logfmt("exercise(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
struct monst * boomhit(struct obj * a0,int a1,int a2){logfmt("boomhit(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return options[31]?&gy.youmonst:options[30]?&mpool[0]:0;}
const char * skill_name(int a0){logfmt("skill_name(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return namebuf;}
const char * weapon_descr(struct obj * a0){logfmt("weapon_descr(");ptrlog(a0);logfmt(")\n");return namebuf;}
int isqrt(int a0){logfmt("isqrt(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");int n=0;while((n+1)*(n+1)<=a0)n++;return n;}
struct monst * bhit(int a0,int a1,int a2,enum bhit_call_types a3,int (*a4)(struct monst *, struct obj *),int (*a5)(struct obj *, struct obj *),struct obj ** a6){logfmt("bhit(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");ptrlog(a4);logfmt(",");ptrlog(a5);logfmt(",");logfmt("OBJ**:");ptrlog(*a6);logfmt(")\n");gb.bhitpos.x=u.ux+a0*2;gb.bhitpos.y=u.uy+a1*2;if(options[29]==1){fixture_delete(*a6);*a6=0;}else if(options[29]==2)*a6=&opool[1];return options[30]?&mpool[0]:0;}
struct obj * addinv_before(struct obj * a0,struct obj * a1){logfmt("addinv_before(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");if(options[32]){fixture_delete(a0);return &opool[1];}a0->nobj=gi.invent;gi.invent=a0;a0->where=OBJ_INVENT;return a0;}
void setuwep(struct obj * a0){logfmt("setuwep(");ptrlog(a0);logfmt(")\n");uwep=a0;if(a0)a0->owornmask|=W_WEP;}
void set_twoweap(boolean a0){logfmt("set_twoweap(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");u.twoweap=a0;}
boolean is_flammable(struct obj * a0){logfmt("is_flammable(");ptrlog(a0);logfmt(")\n");return 0;}
int weight(struct obj * a0){logfmt("weight(");ptrlog(a0);logfmt(")\n");return(int)(a0->quan*2);}
boolean flooreffects(struct obj * a0,coordxy a1,coordxy a2,const char * a3){logfmt("flooreffects(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%s",a3?a3:"<null>");logfmt(")\n");if(options[33])fixture_delete(a0);return options[33];}
void obj_no_longer_held(struct obj * a0){logfmt("obj_no_longer_held(");ptrlog(a0);logfmt(")\n");}
void place_object(struct obj * a0,coordxy a1,coordxy a2){logfmt("place_object(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");a0->ox=a1;a0->oy=a2;a0->where=OBJ_FLOOR;a0->nexthere=svl.level.objects[a1][a2];svl.level.objects[a1][a2]=a0;}
void container_impact_dmg(struct obj * a0,coordxy a1,coordxy a2){logfmt("container_impact_dmg(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
void impact_disturbs_zombies(struct obj * a0,boolean a1){logfmt("impact_disturbs_zombies(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
void stackobj(struct obj * a0){logfmt("stackobj(");ptrlog(a0);logfmt(")\n");}
void drop_ball(coordxy a0,coordxy a1){logfmt("drop_ball(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");}
boolean obj_sheds_light(struct obj * a0){logfmt("obj_sheds_light(");ptrlog(a0);logfmt(")\n");return options[44];}
void setuswapwep(struct obj * a0){logfmt("setuswapwep(");ptrlog(a0);logfmt(")\n");uswapwep=a0;if(a0)a0->owornmask|=W_SWAPWEP;}
int hitval(struct obj * a0,struct monst * a1){logfmt("hitval(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return options[40];}
char * mshot_xname(struct obj * a0){logfmt("mshot_xname(");ptrlog(a0);logfmt(")\n");return namebuf;}
void miss(const char * a0,struct monst * a1){logfmt("miss(");logfmt("%s",a0?a0:"<null>");logfmt(",");ptrlog(a1);logfmt(")\n");}
int (rnl)(int a0){return roll("rnl",a0);}
int find_mac(struct monst * a0){logfmt("find_mac(");ptrlog(a0);logfmt(")\n");return options[39];}
int distmin(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logfmt("distmin(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");int x=abs(a0-a2),y=abs(a1-a3);return x>y?x:y;}
void fully_identify_obj(struct obj * a0){logfmt("fully_identify_obj(");ptrlog(a0);logfmt(")\n");}
char * s_suffix(const char * a0){logfmt("s_suffix(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return(char*)a0;}
const char * align_gname(aligntyp a0){logfmt("align_gname(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");return namebuf;}
boolean monnear(struct monst * a0,coordxy a1,coordxy a2){logfmt("monnear(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return 0;}
void finish_quest(struct obj * a0){logfmt("finish_quest(");ptrlog(a0);logfmt(")\n");}
struct obj * addinv(struct obj * a0){logfmt("addinv(");ptrlog(a0);logfmt(")\n");a0->nobj=gi.invent;gi.invent=a0;a0->where=OBJ_INVENT;return a0;}
int weapon_hit_bonus(struct obj * a0){logfmt("weapon_hit_bonus(");ptrlog(a0);logfmt(")\n");return 0;}
int spec_abon(struct obj * a0,struct monst * a1){logfmt("spec_abon(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return 0;}
boolean hmon(struct monst * a0,struct obj * a1,int a2,int a3){logfmt("hmon(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return options[38];}
void cutworm(struct monst * a0,coordxy a1,coordxy a2,boolean a3){logfmt("cutworm(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");}
void obfree(struct obj * a0,struct obj * a1){logfmt("obfree(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");fixture_delete(a0);}
void passive_obj(struct monst * a0,struct obj * a1,struct attack * a2){logfmt("passive_obj(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");ptrlog(a2);logfmt(")\n");}
int dogfood(struct monst * a0,struct obj * a1){logfmt("dogfood(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return options[36];}
boolean tamedog(struct monst * a0,struct obj * a1,boolean a2){logfmt("tamedog(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return options[37];}
void delobj(struct obj * a0){logfmt("delobj(");ptrlog(a0);logfmt(")\n");fixture_delete(a0);}
struct attack * dmgtype_fromattack(struct permonst * a0,int a1,int a2){logfmt("dmgtype_fromattack(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return 0;}
char * mon_nam(struct monst * a0){logfmt("mon_nam(");ptrlog(a0);logfmt(")\n");return namebuf;}
void change_luck(schar a0){logfmt("change_luck(");logfmt("%llu",(unsigned long long)a0);logfmt(")\n");}
boolean tele_restrict(struct monst * a0){logfmt("tele_restrict(");ptrlog(a0);logfmt(")\n");return options[42];}
boolean rloc(struct monst * a0,unsigned int a1){logfmt("rloc(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(")\n");return !options[43];}
struct monst * makemon(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){logfmt("makemon(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");if(options[46])return 0;if(nm==128)abort();struct monst*m=&mpool[nm++];memset(m,0,sizeof*m);m->data=a0;m->mx=a1;m->my=a2;return m;}
char * rndmonnam(char * a0){logfmt("rndmonnam(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return namebuf;}
char * An(const char * a0){logfmt("An(");logfmt("%s",a0?a0:"<null>");logfmt(")\n");return(char*)a0;}
void set_malign(struct monst * a0){logfmt("set_malign(");ptrlog(a0);logfmt(")\n");}
const char * armor_simple_name(struct obj * a0){logfmt("armor_simple_name(");ptrlog(a0);logfmt(")\n");return namebuf;}
int erode_obj(struct obj * a0,const char * a1,int a2,int a3){logfmt("erode_obj(");ptrlog(a0);logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return options[45];}
void explode_oil(struct obj * a0,coordxy a1,coordxy a2){logfmt("explode_oil(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
int dist2(coordxy a0,coordxy a1,coordxy a2,coordxy a3){logfmt("dist2(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(")\n");return(a0-a2)*(a0-a2)+(a1-a3)*(a1-a3);}
char * vtense(const char * a0,const char * a1){logfmt("vtense(");logfmt("%s",a0?a0:"<null>");logfmt(",");logfmt("%s",a1?a1:"<null>");logfmt(")\n");return(char*)a1;}
void potionbreathe(struct obj * a0){logfmt("potionbreathe(");ptrlog(a0);logfmt(")\n");}
void make_angry_shk(struct monst * a0,coordxy a1,coordxy a2){logfmt("make_angry_shk(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");}
int (d)(int a0,int a1){int n=0;for(int i=0;i<a0;i++)n+=roll("d",a1)+1;return n;}
void explode(coordxy a0,coordxy a1,int a2,int a3,char a4,int a5){logfmt("explode(");logfmt("%llu",(unsigned long long)a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(",");logfmt("%llu",(unsigned long long)a3);logfmt(",");logfmt("%llu",(unsigned long long)a4);logfmt(",");logfmt("%llu",(unsigned long long)a5);logfmt(")\n");}
boolean obj_resists(struct obj * a0,int a1,int a2){logfmt("obj_resists(");ptrlog(a0);logfmt(",");logfmt("%llu",(unsigned long long)a1);logfmt(",");logfmt("%llu",(unsigned long long)a2);logfmt(")\n");return options[35];}
int add_to_minv(struct monst * a0,struct obj * a1){logfmt("add_to_minv(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");a1->where=OBJ_MINVENT;a1->nobj=a0->minvent;a0->minvent=a1;return 0;}
boolean ghitm(struct monst * a0,struct obj * a1){logfmt("ghitm(");ptrlog(a0);logfmt(",");ptrlog(a1);logfmt(")\n");return options[38];}
int doswapweapon(void){logfmt("doswapweapon()\n");struct obj*t=uwep;uwep=uswapwep;uswapwep=t;return ECMD_OK;}
int dowield(void){logfmt("dowield()\n");uwep=&opool[1];return ECMD_OK;}
void Norep(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("Norep:%s\n",b);}
void You(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You:%s\n",b);}
void You_cant(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You_cant:%s\n",b);}
void You_feel(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You_feel:%s\n",b);}
void You_hear(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("You_hear:%s\n",b);}
void Your(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("Your:%s\n",b);}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("impossible:%s\n",b);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline:%s\n",b);}
void pline_The(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("pline_The:%s\n",b);}
void verbalize(const char*fmt,...){va_list ap;va_start(ap,fmt);char b[2048];vsnprintf(b,sizeof b,fmt,ap);va_end(ap);logfmt("verbalize:%s\n",b);}
void nh_snprintf(const char*f,int line,char*b,size_t n,const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(b,n,fmt,ap);va_end(ap);logfmt("nh_snprintf[%s:%d]:%s\n",f,line,b);}
#ifdef HYBRID_DOTHROW
extern int multishot_class_bonus(int a0,struct obj * a1,struct obj * a2);
extern int teleport_dothrow_throw_obj(struct obj * a0,int a1);
extern boolean teleport_dothrow_ok_to_throw(int * a0);
extern int teleport_dothrow_throw_ok(struct obj * a0);
extern int dothrow(void);
extern void teleport_dothrow_autoquiver(void);
extern struct obj * teleport_dothrow_find_launcher(struct obj * a0);
extern int dofire(void);
extern void endmultishot(boolean a0);
extern void hitfloor(struct obj * a0,boolean a1);
extern boolean walk_path(coord * a0,coord * a1,boolean (*a2)(genericptr_t, coordxy, coordxy),genericptr_t a3);
extern boolean hurtle_jump(genericptr_t a0,coordxy a1,coordxy a2);
extern boolean hurtle_step(genericptr_t a0,coordxy a1,coordxy a2);
extern boolean will_hurtle(struct monst * a0,coordxy a1,coordxy a2);
extern boolean teleport_dothrow_mhurtle_step(genericptr_t a0,coordxy a1,coordxy a2);
extern void hurtle(int a0,int a1,int a2,boolean a3);
extern void mhurtle(struct monst * a0,int a1,int a2,int a3);
extern void teleport_dothrow_check_shop_obj(struct obj * a0,coordxy a1,coordxy a2,boolean a3);
extern boolean harmless_missile(struct obj * a0);
extern boolean teleport_dothrow_toss_up(struct obj * a0,boolean a1);
extern boolean throwing_weapon(struct obj * a0);
extern void teleport_dothrow_sho_obj_return_to_u(struct obj * a0);
extern void teleport_dothrow_throwit_return(boolean a0);
extern void teleport_dothrow_swallowit(struct obj * a0);
extern boolean throwit_mon_hit(struct obj * a0,struct monst * a1);
extern void throwit(struct obj * a0,long a1,boolean a2,struct obj * a3);
extern struct obj * teleport_dothrow_return_throw_to_inv(struct obj * a0,long a1,boolean a2,struct obj * a3);
extern int omon_adj(struct monst * a0,struct obj * a1,boolean a2);
extern void teleport_dothrow_tmiss(struct obj * a0,struct monst * a1,boolean a2);
extern boolean should_mulch_missile(struct obj * a0);
extern int thitmonst(struct monst * a0,struct obj * a1);
extern int teleport_dothrow_gem_accept(struct monst * a0,struct obj * a1);
extern int hero_breaks(struct obj * a0,coordxy a1,coordxy a2,unsigned int a3);
extern int breaks(struct obj * a0,coordxy a1,coordxy a2);
extern void release_camera_demon(struct obj * a0,coordxy a1,coordxy a2);
extern int breakobj(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4);
extern boolean breaktest(struct obj * a0);
extern void teleport_dothrow_breakmsg(struct obj * a0,boolean a1);
extern int teleport_dothrow_throw_gold(struct obj * a0);
#else
#define teleport_dothrow_throw_obj throw_obj
#define teleport_dothrow_ok_to_throw ok_to_throw
#define teleport_dothrow_throw_ok throw_ok
#define teleport_dothrow_autoquiver autoquiver
#define teleport_dothrow_find_launcher find_launcher
#define teleport_dothrow_mhurtle_step mhurtle_step
#define teleport_dothrow_check_shop_obj check_shop_obj
#define teleport_dothrow_toss_up toss_up
#define teleport_dothrow_sho_obj_return_to_u sho_obj_return_to_u
#define teleport_dothrow_throwit_return throwit_return
#define teleport_dothrow_swallowit swallowit
#define teleport_dothrow_return_throw_to_inv return_throw_to_inv
#define teleport_dothrow_tmiss tmiss
#define teleport_dothrow_gem_accept gem_accept
#define teleport_dothrow_breakmsg breakmsg
#define teleport_dothrow_throw_gold throw_gold
#include "/Users/arj/Desktop/nethack_comp/teleport-contest/.cache/wasm64-build/tree/src/dothrow.c"
#endif
uintptr_t probe_identity(int i){switch(i){
case 0:return(uintptr_t)(fixture_predicate);
case 1:return(uintptr_t)(fixture_delay);
case 2:return(uintptr_t)(teleport_dothrow_throw_ok);
case 3:return(uintptr_t)(dofire);
case 4:return(uintptr_t)(hurtle_step);
case 5:return(uintptr_t)(teleport_dothrow_mhurtle_step);
case 6:return(uintptr_t)(xname);
case 7:return(uintptr_t)(doswapweapon);
case 8:return(uintptr_t)(dowield);
default:abort();}}
static void fpidentity(uintptr_t p){
if(p==(uintptr_t)(fixture_predicate)){logfmt("fixture_predicate");return;}
if(p==(uintptr_t)(fixture_delay)){logfmt("fixture_delay");return;}
if(p==(uintptr_t)(teleport_dothrow_throw_ok)){logfmt("throw_ok");return;}
if(p==(uintptr_t)(dofire)){logfmt("dofire");return;}
if(p==(uintptr_t)(hurtle_step)){logfmt("hurtle_step");return;}
if(p==(uintptr_t)(teleport_dothrow_mhurtle_step)){logfmt("mhurtle_step");return;}
if(p==(uintptr_t)(xname)){logfmt("xname");return;}
if(p==(uintptr_t)(doswapweapon)){logfmt("doswapweapon");return;}
if(p==(uintptr_t)(dowield)){logfmt("dowield");return;}
logfmt("UNKNOWN_FUNCTION:%llu",(unsigned long long)p);}
int probe_queue_count(void){return nq;}int probe_queue_identity(int i){for(int j=0;j<9;j++)if((uintptr_t)queue[i]==probe_identity(j))return j;return -1;}int probe_queue_run(int i){int j=setjmp(panicframe);if(j){errorcode=j;return-999;}return queue[i]();}
int64_t probe_action(int i,int64_t a0,int64_t a1,int64_t a2,int64_t a3,int64_t a4,int64_t a5,int64_t a6,int64_t a7,int64_t a8,int64_t a9){errorcode=0;int jump=setjmp(panicframe);if(jump){errorcode=jump;return -999;}switch(i){
case 0:return(int64_t)multishot_class_bonus((int)a0,(struct obj *)a1,(struct obj *)a2);
case 1:return(int64_t)teleport_dothrow_throw_obj((struct obj *)a0,(int)a1);
case 2:return(int64_t)teleport_dothrow_ok_to_throw((int *)a0);
case 3:return(int64_t)teleport_dothrow_throw_ok((struct obj *)a0);
case 4:return(int64_t)dothrow();
case 5:teleport_dothrow_autoquiver();return 0;
case 6:return(int64_t)teleport_dothrow_find_launcher((struct obj *)a0);
case 7:return(int64_t)dofire();
case 8:endmultishot((boolean)a0);return 0;
case 9:hitfloor((struct obj *)a0,(boolean)a1);return 0;
case 10:return(int64_t)walk_path((coord *)a0,(coord *)a1,(boolean (*)(genericptr_t, coordxy, coordxy))a2,(genericptr_t)a3);
case 11:return(int64_t)hurtle_jump((genericptr_t)a0,(coordxy)a1,(coordxy)a2);
case 12:return(int64_t)hurtle_step((genericptr_t)a0,(coordxy)a1,(coordxy)a2);
case 13:return(int64_t)will_hurtle((struct monst *)a0,(coordxy)a1,(coordxy)a2);
case 14:return(int64_t)teleport_dothrow_mhurtle_step((genericptr_t)a0,(coordxy)a1,(coordxy)a2);
case 15:hurtle((int)a0,(int)a1,(int)a2,(boolean)a3);return 0;
case 16:mhurtle((struct monst *)a0,(int)a1,(int)a2,(int)a3);return 0;
case 17:teleport_dothrow_check_shop_obj((struct obj *)a0,(coordxy)a1,(coordxy)a2,(boolean)a3);return 0;
case 18:return(int64_t)harmless_missile((struct obj *)a0);
case 19:return(int64_t)teleport_dothrow_toss_up((struct obj *)a0,(boolean)a1);
case 20:return(int64_t)throwing_weapon((struct obj *)a0);
case 21:teleport_dothrow_sho_obj_return_to_u((struct obj *)a0);return 0;
case 22:teleport_dothrow_throwit_return((boolean)a0);return 0;
case 23:teleport_dothrow_swallowit((struct obj *)a0);return 0;
case 24:return(int64_t)throwit_mon_hit((struct obj *)a0,(struct monst *)a1);
case 25:throwit((struct obj *)a0,(long)a1,(boolean)a2,(struct obj *)a3);return 0;
case 26:return(int64_t)teleport_dothrow_return_throw_to_inv((struct obj *)a0,(long)a1,(boolean)a2,(struct obj *)a3);
case 27:return(int64_t)omon_adj((struct monst *)a0,(struct obj *)a1,(boolean)a2);
case 28:teleport_dothrow_tmiss((struct obj *)a0,(struct monst *)a1,(boolean)a2);return 0;
case 29:return(int64_t)should_mulch_missile((struct obj *)a0);
case 30:return(int64_t)thitmonst((struct monst *)a0,(struct obj *)a1);
case 31:return(int64_t)teleport_dothrow_gem_accept((struct monst *)a0,(struct obj *)a1);
case 32:return(int64_t)hero_breaks((struct obj *)a0,(coordxy)a1,(coordxy)a2,(unsigned int)a3);
case 33:return(int64_t)breaks((struct obj *)a0,(coordxy)a1,(coordxy)a2);
case 34:release_camera_demon((struct obj *)a0,(coordxy)a1,(coordxy)a2);return 0;
case 35:return(int64_t)breakobj((struct obj *)a0,(coordxy)a1,(coordxy)a2,(boolean)a3,(boolean)a4);
case 36:return(int64_t)breaktest((struct obj *)a0);
case 37:teleport_dothrow_breakmsg((struct obj *)a0,(boolean)a1);return 0;
case 38:return(int64_t)teleport_dothrow_throw_gold((struct obj *)a0);
default:abort();}}

const char*probe_trace(void){return tracebuf;}void probe_clear(void){traceused=0;tracebuf[0]=0;}int probe_draws(void){return draws;}int probe_error(void){return errorcode;}int probe_errno(void){return errno;}
void probe_seed(uint32_t n){seed=n;draws=0;}void probe_option(int i,int v){options[i]=v;}
void*probe_pointer(int i){switch(i){case 0:return &ccoord[0];case 1:return &ccoord[1];case 2:return literal;case 3:return namebuf;case 4:return opool;case 5:return mpool;case 6:return tpool;case 7:return &testeshk;case 8:return &testmextra;case 9:return &returning;case 10:return scratch;case 11:return &scalar;case 12:return pronoun;default:return 0;}}
void*probe_grid(void){return levl;}void probe_coord(int i,int x,int y){ccoord[i].x=x;ccoord[i].y=y;}
void probe_map(int x,int y,int typ,int bits){memset(&levl[x][y],0,sizeof levl[x][y]);levl[x][y].typ=typ;levl[x][y].lit=bits&1;levl[x][y].horizontal=(bits>>1)&1;levl[x][y].flags=(bits>>2)&31;}
int probe_count(int i){return i==0?no:i==1?nm:i==2?nt:i==3?nalloc:0;}void*probe_alloc_pointer(int i){return allocations[i];}size_t probe_alloc_size(int i){return allocsizes[i];}
void*probe_growth(void){return __real_malloc(50000000);}
void probe_reset(void){for(int i=0;i<nalloc;i++)if(allocations[i])__real_free(allocations[i]);nalloc=0;memset(options,0,sizeof options);memset(opool,0,sizeof opool);memset(mpool,0,sizeof mpool);memset(tpool,0,sizeof tpool);no=nm=nt=0;predicatecalls=nq=0;

memset((void*)&objects,0,sizeof objects);
memset((void*)&svc,0,sizeof svc);
memset((void*)&uquiver,0,sizeof uquiver);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&gy,0,sizeof gy);
memset((void*)&u,0,sizeof u);
memset((void*)&uarmg,0,sizeof uarmg);
memset((void*)&svk,0,sizeof svk);
memset((void*)&gu,0,sizeof gu);
memset((void*)&gm,0,sizeof gm);
memset((void*)&gc,0,sizeof gc);
memset((void*)&uswapwep,0,sizeof uswapwep);
memset((void*)&gi,0,sizeof gi);
memset((void*)&flags,0,sizeof flags);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&svl,0,sizeof svl);
memset((void*)&uarmu,0,sizeof uarmu);
memset((void*)&uarm,0,sizeof uarm);
memset((void*)&uarmc,0,sizeof uarmc);
memset((void*)&uball,0,sizeof uball);
memset((void*)&svd,0,sizeof svd);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&gn,0,sizeof gn);
memset((void*)&gt,0,sizeof gt);
memset((void*)&uarmh,0,sizeof uarmh);
memset((void*)&gb,0,sizeof gb);
memset((void*)&go,0,sizeof go);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&gv,0,sizeof gv);
memset((void*)&gk,0,sizeof gk);
memset((void*)&svq,0,sizeof svq);
memset((void*)&ublindf,0,sizeof ublindf);
memset((void*)&gh,0,sizeof gh);

memset(&testeshk,0,sizeof testeshk);memset(&testmextra,0,sizeof testmextra);testmextra.eshk=&testeshk;memset(&returning,0,sizeof returning);memset(scratch,0,sizeof scratch);memset(ccoord,0,sizeof ccoord);scalar=10;
for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_class=WEAPON_CLASS;objects[i].oc_prob=1;objects[i].oc_skill=P_DAGGER;}objects[ARROW].oc_skill=-P_BOW;objects[BOW].oc_skill=P_BOW;
struct obj*o=fixture_newobj(ARROW);o->quan=10;o->dknown=o->bknown=1;o->where=OBJ_INVENT;o->ox=45;o->oy=10;o->owt=5;gi.invent=o;
o=fixture_newobj(BOW);o->quan=1;o->dknown=o->bknown=1;o->where=OBJ_INVENT;o->owt=30;opool[0].nobj=o;
nm=1;mpool[0].m_id=1;mpool[0].data=&mons[PM_ORC];mpool[0].mx=45;mpool[0].my=10;mpool[0].mhp=mpool[0].mhpmax=20;mpool[0].mcanmove=1;mpool[0].mextra=&testmextra;
nt=1;tpool[0].tx=43;tpool[0].ty=10;tpool[0].ttyp=PIT;
u.ux=40;u.uy=10;u.uz.dlevel=3;u.dx=1;u.dy=u.dz=0;u.uhp=u.uhpmax=50;u.ulevel=5;u.uen=u.uenmax=20;gy.youmonst.data=&mons[PM_HUMAN];gy.youmonst.mx=40;gy.youmonst.my=10;gy.youmonst.mhp=50;
windowprocs.win_delay_output=fixture_delay;for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)levl[x][y].typ=ROOM;
seed=1;draws=0;callerfile=callerfn=0;callerline=0;errorcode=0;errno=0;strcpy(literal,"");strcpy(namebuf,"fixture");probe_clear();}
size_t probe_global_size(int i){switch(i){

case 0:return sizeof objects;
case 1:return sizeof svc;
case 2:return sizeof uquiver;
case 3:return sizeof uwep;
case 4:return sizeof gy;
case 5:return sizeof u;
case 6:return sizeof uarmg;
case 7:return sizeof mons;
case 8:return sizeof svk;
case 9:return sizeof gu;
case 10:return sizeof gm;
case 11:return sizeof gc;
case 12:return sizeof uswapwep;
case 13:return sizeof gi;
case 14:return sizeof flags;
case 15:return sizeof iflags;
case 16:return sizeof svl;
case 17:return sizeof genders;
case 18:return sizeof uarmu;
case 19:return sizeof uarm;
case 20:return sizeof uarmc;
case 21:return sizeof uball;
case 22:return sizeof svd;
case 23:return sizeof windowprocs;
case 24:return sizeof gn;
case 25:return sizeof gt;
case 26:return sizeof uarmh;
case 27:return sizeof c_common_strings;
case 28:return sizeof gb;
case 29:return sizeof go;
case 30:return sizeof uchain;
case 31:return sizeof gv;
case 32:return sizeof gk;
case 33:return sizeof svq;
case 34:return sizeof ublindf;
case 35:return sizeof gh;
default:abort();}}
size_t probe_pointer_offset(int k,int i){switch(k){case 0:switch(i){case 0:return offsetof(struct obj,nobj);case 1:return offsetof(struct obj,v);case 2:return offsetof(struct obj,cobj);case 3:return offsetof(struct obj,oextra);}break;case 1:switch(i){case 0:return offsetof(struct monst,nmon);case 1:return offsetof(struct monst,data);case 2:return offsetof(struct monst,minvent);case 3:return offsetof(struct monst,mw);case 4:return offsetof(struct monst,mextra);}break;case 2:return offsetof(struct trap,ntrap);}abort();}
int64_t probe_constant(int i){switch(i){
case 0:return(int64_t)(AKLYS);
case 1:return(int64_t)(ARMOR_CLASS);
case 2:return(int64_t)(ARROW);
case 3:return(int64_t)(ART_MJOLLNIR);
case 4:return(int64_t)(BLINDING_VENOM);
case 5:return(int64_t)(BOOMERANG);
case 6:return(int64_t)(BOULDER);
case 7:return(int64_t)(BOW);
case 8:return(int64_t)(BRK_FROM_INV);
case 9:return(int64_t)(BRK_KNOWN2BREAK);
case 10:return(int64_t)(BRK_KNOWN2NOTBREAK);
case 11:return(int64_t)(BULLWHIP);
case 12:return(int64_t)(COIN_CLASS);
case 13:return(int64_t)(CORPSE);
case 14:return(int64_t)(CREAM_PIE);
case 15:return(int64_t)(DAGGER);
case 16:return(int64_t)(DIAMOND);
case 17:return(int64_t)(DOOR);
case 18:return(int64_t)(D_CLOSED);
case 19:return(int64_t)(ECMD_CANCEL);
case 20:return(int64_t)(ECMD_OK);
case 21:return(int64_t)(ECMD_TIME);
case 22:return(int64_t)(EGG);
case 23:return(int64_t)(EXPENSIVE_CAMERA);
case 24:return(int64_t)(FILL_NORMAL);
case 25:return(int64_t)(FOOD_CLASS);
case 26:return(int64_t)(GEMSTONE);
case 27:return(int64_t)(GEM_CLASS);
case 28:return(int64_t)(GLASS);
case 29:return(int64_t)(GOLD_PIECE);
case 30:return(int64_t)(HWALL);
case 31:return(int64_t)(LANCE);
case 32:return(int64_t)(LAVAPOOL);
case 33:return(int64_t)(MINERAL);
case 34:return(int64_t)(MIRROR);
case 35:return(int64_t)(MOAT);
case 36:return(int64_t)(OBJ_FLOOR);
case 37:return(int64_t)(OBJ_FREE);
case 38:return(int64_t)(OBJ_INVENT);
case 39:return(int64_t)(OBJ_MINVENT);
case 40:return(int64_t)(PM_CAVE_DWELLER);
case 41:return(int64_t)(PM_GIANT_SPIDER);
case 42:return(int64_t)(PM_HUMAN);
case 43:return(int64_t)(PM_MONK);
case 44:return(int64_t)(PM_NINJA);
case 45:return(int64_t)(PM_ORC);
case 46:return(int64_t)(PM_PYROLISK);
case 47:return(int64_t)(PM_RANGER);
case 48:return(int64_t)(PM_ROGUE);
case 49:return(int64_t)(PM_SAMURAI);
case 50:return(int64_t)(PM_STONE_GOLEM);
case 51:return(int64_t)(PM_VALKYRIE);
case 52:return(int64_t)(PM_WHITE_UNICORN);
case 53:return(int64_t)(POOL);
case 54:return(int64_t)(POTION_CLASS);
case 55:return(int64_t)(POT_OIL);
case 56:return(int64_t)(POT_WATER);
case 57:return(int64_t)(P_BOW);
case 58:return(int64_t)(P_DAGGER);
case 59:return(int64_t)(P_DART);
case 60:return(int64_t)(P_SHURIKEN);
case 61:return(int64_t)(P_SLING);
case 62:return(int64_t)(P_SPEAR);
case 63:return(int64_t)(ROCK);
case 64:return(int64_t)(ROOM);
case 65:return(int64_t)(SPEAR);
case 66:return(int64_t)(STATUE);
case 67:return(int64_t)(STONE);
case 68:return(int64_t)(TOOL_CLASS);
case 69:return(int64_t)(WATER);
case 70:return(int64_t)(WEAPON_CLASS);
case 71:return(int64_t)(W_QUIVER);
case 72:return(int64_t)(W_SWAPWEP);
case 73:return(int64_t)(W_WEP);
case 74:return(int64_t)(YA);
case 75:return(int64_t)(YUMI);
default:abort();}}
const char*probe_source_literal(int i){switch(i){case 0:return "";case 1:return " accepts your gift.";case 2:return " but doesn't hurt.";case 3:return " currents";case 4:return " entrails";case 5:return " graciously";case 6:return " gratefully";case 7:return " hesitatingly";case 8:return " into a thousand pieces";case 9:return " is not interested in your junk.";case 10:return "%s";case 11:return "%s %d %s.";case 12:return "%s %s %s back to you.";case 13:return "%s %s the %s, then falls back on top of your %s.";case 14:return "%s %s the %s.";case 15:return "%s %s.";case 16:return "%s as you throw it!";case 17:return "%s back to you, landing %s your %s.";case 18:return "%s back toward you, hitting your %s!";case 19:return "%s bumps into %s.";case 20:return "%s bumps into you.";case 21:return "%s catches %s.";case 22:return "%s catches and drops %s.";case 23:return "%s does not protect you.";case 24:return "%s doesn't budge!";case 25:return "%s fails to protect you.";case 26:return "%s hits the %s.";case 27:return "%s in the opposite direction.";case 28:return "%s into %s%s.";case 29:return "%s is released!";case 30:return "%s lands %s your %s.";case 31:return "%s must be wielded before it can be thrown.";case 32:return "%s part in this is finished.";case 33:return "%s shatter!";case 34:return "%s shatter%s%s!";case 35:return "%s snatches up %s.";case 36:return "%s the %s and returns to your hand!";case 37:return "%s to return!";case 38:return "%s to your hand!";case 39:return "%s your %s!";case 40:return "%s!";case 41:return "%sget forcefully wedged into a crevice.";case 42:return "Fortunately, you are wearing %s!";case 43:return "Fortunately, you are wearing a hard helmet.";case 44:return "It blinds you!";case 45:return "It doesn't hurt.";case 46:return "It's too heavy.";case 47:return "Ouch!";case 48:return "Plop!";case 49:return "Splash!";case 50:return "Splat!";case 51:return "The ground vibrates as you pass it.";case 52:return "The picture-painting demon";case 53:return "Unfortunately, you are wearing %s.";case 54:return "Unknown type of gloves (%d)";case 55:return "We will guard it in case it is ever needed again, %s forbid.";case 56:return "What a mess!";case 57:return "You aren't wielding %s, so you throw your %s by %s.";case 58:return "You move over %s.";case 59:return "You move over some lava.";case 60:return "You ready:";case 61:return "You've got it all over your %s!";case 62:return "a tug from the iron ball.";case 63:return "almost hits";case 64:return "and all your belongings ";case 65:return "are anchored by the %s.";case 66:return "are physically incapable of throwing or shooting anything.";case 67:return "at";case 68:return "being hit by %s";case 69:return "beneath";case 70:return "breaking odd object (%d)?";case 71:return "breakobj";case 72:return "bump into %s.";case 73:return "bump into a %s.  Ouch!";case 74:return "bumping into %s";case 75:return "bumping into a boulder";case 76:return "bumping into a closed door";case 77:return "bumping into a door frame";case 78:return "bumping into a tree";case 79:return "bumping into a wall";case 80:return "buried ball";case 81:return "cannot throw an object at yourself.";case 82:return "cannot throw gold at yourself.";case 83:return "come to an abrupt halt!";case 84:return "crash into some iron bars.  Ouch!";case 85:return "crashing into iron bars";case 86:return "dothrow.c";case 87:return "edge of the hole";case 88:return "edge of the pit";case 89:return "elementary physics";case 90:return "fail";case 91:return "fall";case 92:return "falling object";case 93:return "find %s by bumping into %s.";case 94:return "fire";case 95:return "firing";case 96:return "flies up into";case 97:return "float";case 98:return "fly";case 99:return "gem_accept";case 100:return "gold disappears into %s.";case 101:return "gold hits the %s, then falls back on top of your %s.";case 102:return "gold hits the %s.";case 103:return "hands";case 104:return "have no ammunition readied.";case 105:return "have nothing appropriate for your quiver.";case 106:return "have so little stamina, %s drops from your grasp.";case 107:return "hit";case 108:return "hit the door frame!";case 109:return "hits";case 110:return "hurtle";case 111:return "hurtle_step";case 112:return "hurtling";case 113:return "lava";case 114:return "mhurtle_step";case 115:return "misfire";case 116:return "miss";case 117:return "moat";case 118:return "moving through the air";case 119:return "obj != NULL";case 120:return "omon_adj";case 121:return "pass right over %s.";case 122:return "pool";case 123:return "release_camera_demon";case 124:return "return";case 125:return "s";case 126:return "shoot";case 127:return "shot";case 128:return "should_mulch_missile";case 129:return "silver sears you!";case 130:return "slip";case 131:return "smack into something!";case 132:return "smell a peculiar odor...";case 133:return "stop %s after the %d%s %s.";case 134:return "strike";case 135:return "the spirits holding you back.";case 136:return "thitmonst";case 137:return "throw";case 138:return "throw %s with your bare %s.";case 139:return "throw or shoot without hands.";case 140:return "throw_obj";case 141:return "throwing";case 142:return "throwing %s bare-handed";case 143:return "throwit";case 144:return "tmiss";case 145:return "toss";case 146:return "toss_up";case 147:return "tosses";case 148:return "touching the edge of the universe";case 149:return "trap";case 150:return "trap door";case 151:return "turn to stone.";case 152:return "vanish";case 153:return "water";case 154:return "web";case 155:return "wedging into a narrow crevice";default:abort();}}
