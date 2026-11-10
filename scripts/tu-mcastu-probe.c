/* Controlled external boundaries for differential execution of the original mcastu TU. */
#include "hack.h"
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/heap.h>
#include <emscripten/stack.h>
struct you u; __typeof__(gy)gy;__typeof__(svm)svm;__typeof__(svc)svc;__typeof__(svk)svk;__typeof__(gi)gi;__typeof__(gm)gm;__typeof__(gn)gn;__typeof__(gb)gb;__typeof__(gt)gt;__typeof__(gv)gv;__typeof__(iflags)iflags;
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
static struct monst caster,spawned[40];static struct attack attack;static int opts[40],rolls[8192],nr,ri,nspawn;static unsigned seed;static char tracebuf[262144],statebuf[65536],output[BUFSZ],caller[128];static seenV vision[ROWNO][COLNO],*rows[ROWNO];static void*growth;
static void append(const char*f,...){va_list a;va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);}
static int mid(struct monst*m){return !m?-1:m==&caster?0:m==&gy.youmonst?1:(m>=spawned&&m<spawned+40)?2+(int)(m-spawned):99;}
static void callback(int stage){if(opts[30]==stage){opts[30]=0;append("reenter:%s;",death_inflicted_by(output,"nested",&caster));}if(opts[31]==stage&&!growth){growth=malloc(emscripten_get_heap_size()+16777216);if(!growth)abort();append("grow:%d;",stage);}}
void panic(const char*f,...){abort();}
#define MSG(fn) void fn(const char*f,...){va_list a;append(#fn ":");va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);append(";");}
MSG(impossible) MSG(pline) MSG(pline_The) MSG(You) MSG(Your) MSG(You_feel) MSG(You_hear) MSG(Norep) MSG(verbalize)
void pline_mon(struct monst*m,const char*f,...){va_list a;append("monmsg:%d:",mid(m));va_start(a,f);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),f,a);va_end(a);append(";");}
boolean rng_log_enabled(void){return opts[0];}void rng_log_set_caller(const char*f,int l,const char*fn){append("");snprintf(caller,sizeof caller,"%s:%d",fn,l);}
static int draw(int n){int v;if(n<=0)abort();seed=1664525U*seed+1013904223U;v=(unsigned)(ri<nr?rolls[ri]:seed)%n;ri++;return v;}
int(rn2)(int n){int v=draw(n);append("rn2:%d:%d@%s;",n,v,caller);callback(1);return v;}int(rnd)(int n){int v=draw(n)+1;append("rnd:%d:%d@%s;",n,v,caller);callback(1);return v;}int(d)(int n,int sides){int i,total=0;for(i=0;i<n;i++)total+=draw(sides)+1;append("dice:%d:%d:%d@%s;",n,sides,total,caller);callback(1);return total;}
int canseemon(struct monst*m){append("see:%d;",mid(m));return opts[1]&&!m->minvis;}int sensemon(struct monst*m){return opts[2];}int tp_sensemon(struct monst*m){return opts[3];}
boolean is_waterwall(coordxy x,coordxy y){append("water:%d:%d;",x,y);return opts[4];}
const char*pmname(struct permonst*p,int g){return p->pmnames[g]?p->pmnames[g]:p->pmnames[NEUTRAL]?p->pmnames[NEUTRAL]:p->pmnames[MALE];}int Mgender(struct monst*m){return m->female?FEMALE:MALE;}int pronoun_gender(struct monst*m,unsigned f){return opts[5];}
char*mon_nam(struct monst*m){return "caster";}char*Monnam(struct monst*m){return "Caster";}char*noit_Monnam(struct monst*m){return "Caster";}
const char*body_part(int p){return p==HEAD?"head":"eye";}const char*flash_str(int n,boolean b){return "fixture ray";}
void set_msg_xy(coordxy x,coordxy y){append("msgxy:%d:%d;",x,y);}void nomul(int n){append("nomul:%d;",n);gm.multi=n;}
void shieldeff(coordxy x,coordxy y){append("shield:%d:%d;",x,y);callback(2);}void monstseesu(unsigned long m){append("seen:%lu;",m);caster.seen_resistance|=m;}void monstunseesu(unsigned long m){append("unseen:%lu;",m);caster.seen_resistance&=~m;}unsigned long cvt_adtyp_to_mseenres(uchar n){return opts[6];}
void mdamageu(struct monst*m,int d){append("damage:%d:%d;",mid(m),d);u.uhp-=d;callback(3);}void losehp(int n,const char*s,schar k){append("hp:%d:%s:%d;",n,s,k);u.uhp-=n;callback(3);}int healmon(struct monst*m,int n,int o){append("heal:%d:%d:%d;",mid(m),n,o);m->mhp+=n;if(m->mhp>m->mhpmax)m->mhp=m->mhpmax;callback(4);return n;}
void rehumanize(void){append("rehumanize;");u.umonnum=u.umonster=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];}void done(int n){append("done:%d;",n);}int minuhpmax(int n){return n;}void setuhpmax(int n,boolean b){append("maxhp:%d:%d;",n,b);u.uhpmax=n;if(u.uhp>n)u.uhp=n;}int adjuhploss(int n,int old){append("adj:%d:%d;",n,old);return n-(old-u.uhp);}void losestr(int n,const char*s,schar k){append("strength:%d:%s:%d;",n,s,k);callback(5);}
void clonewiz(void){append("clone;");svc.context.no_of_wizards++;}int nasty(struct monst*m){append("nasty:%d;",mid(m));callback(6);return opts[7];}int destroy_arm(void){append("destroyarm;");callback(7);return opts[8];}
void mon_set_minvis(struct monst*m,boolean b){append("invis:%d:%d;",mid(m),b);m->minvis=1;callback(8);}void map_invisible(coordxy x,coordxy y){append("mapinvis:%d:%d;",x,y);}
void make_stunned(long n,boolean b){append("stun:%ld:%d;",n,b);u.uprops[STUNNED].intrinsic=n;callback(9);}void make_blinded(long n,boolean b){append("blind:%ld:%d;",n,b);u.uprops[BLINDED].intrinsic=n;callback(9);}void make_confused(long n,boolean b){append("confuse:%ld:%d;",n,b);u.uprops[CONFUSION].intrinsic=n;callback(9);}schar acurr(int n){append("attribute:%d;",n);return opts[9];}
void burn_away_slime(void){append("slime;");}boolean burnarmor(struct monst*m){append("burnarmor:%d;",mid(m));callback(10);return opts[10];}int destroy_items(struct monst*m,int a,int d){append("items:%d:%d:%d;",mid(m),a,d);callback(11);return opts[11];}void ignite_items(struct obj*o){append("ignite:%d;",o!=0);}void mon_spell_hits_spot(struct monst*m,int a,coordxy x,coordxy y){append("spot:%d:%d:%d:%d;",mid(m),a,x,y);callback(12);}boolean ureflects(const char*f,const char*s){append("reflect:%s:%s;",f,s);return opts[12];}boolean flashburn(long n,boolean b){append("flashburn:%ld:%d;",n,b);callback(13);return opts[13];}
struct permonst*mkclass(char c,int f){append("mkclass:%d:%d;",c,f);if(opts[14]==2||(opts[14]==1&&c==S_ANT))return 0;return &mons[c==S_ANT?PM_GIANT_ANT:PM_WATER_MOCCASIN];}int monster_census(boolean b){append("census:%d:%d;",b,nspawn);return opts[15]?0:nspawn;}
boolean enexto(coord*p,coordxy x,coordxy y,struct permonst*pm){append("next:%d:%d:%d;",x,y,pm->pmidx);p->x=x+1;p->y=y;if(opts[16])return FALSE;callback(14);return TRUE;}
struct monst*makemon(struct permonst*p,coordxy x,coordxy y,mmflags_nht f){struct monst*m;append("make:%d:%d:%d:%lu;",p->pmidx,x,y,(unsigned long)f);if(opts[17]||nspawn>=40)return 0;m=&spawned[nspawn++];memset(m,0,sizeof*m);m->data=p;m->mx=x;m->my=y;m->msleeping=m->mpeaceful=m->mtame=1;callback(15);return m;}void set_malign(struct monst*m){append("malign:%d;",mid(m));}
char*bogusmon(char*b,char*c){strcpy(b,"fixture beast");return b;}
void mon_adjust_speed(struct monst*m,int n,struct obj*o){append("speed:%d:%d:%d;",mid(m),n,o!=0);m->permspeed=MFAST;}void aggravate(void){append("aggravate;");}void rndcurse(void){append("rndcurse;");}boolean has_aggravatables(struct monst*m){append("aggravatables;");return opts[19];}boolean lined_up(struct monst*m){append("lined:%d;",mid(m));return opts[20];}void buzz(int a,int n,coordxy x,coordxy y,int dx,int dy){append("buzz:%d:%d:%d:%d:%d:%d:%d;",a,n,x,y,dx,dy,mid(gb.buzzer));callback(16);}

/* Naming/awareness are controlled external boundaries, not spell implementations. */
const struct c_common_strings c_common_strings={.c_vision_clears="vision quickly clears."};
boolean unconscious(void){append("unconscious;");return opts[22];}boolean is_fainted(void){append("fainted;");return opts[23];}boolean debugcore(const char*f,boolean b){const char*p=strrchr(f,'/');append("debug:%s:%d;",p?p+1:f,b);return opts[24];}
boolean the_unique_pm(struct permonst*p){if(type_is_pname(p))return FALSE;if(p==&mons[PM_HIGH_CLERIC]||p==&mons[PM_LONG_WORM_TAIL])return FALSE;return p==&mons[PM_WIZARD_OF_YENDOR]||(p->geno&G_UNIQ)!=0;}
char*an(const char*s){static char b[8][BUFSZ];static unsigned i;char*p=b[i++%8];snprintf(p,BUFSZ,"%s %s",strchr("aeiouAEIOU",s[0])?"an":"a",s);return p;}
char*makeplural(const char*s){static char b[8][BUFSZ];static unsigned i;char*p=b[i++%8];snprintf(p,BUFSZ,"%ss",s);return p;}char*makesingular(const char*s){static char b[8][BUFSZ];static unsigned i;char*p=b[i++%8];strcpy(p,s);if(strlen(p)&&p[strlen(p)-1]=='s')p[strlen(p)-1]=0;return p;}char*vtense(const char*s,const char*v){return (char*)v;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/mcastu.c"
#else
extern void teleport_mcastu_test_cursetxt(struct monst*,boolean);
#define cursetxt teleport_mcastu_test_cursetxt
extern int teleport_mcastu_test_choose_monster_spell(struct monst*,int);
#define choose_monster_spell teleport_mcastu_test_choose_monster_spell
extern int teleport_mcastu_test_m_cure_self(struct monst*,int);
#define m_cure_self teleport_mcastu_test_m_cure_self
extern void teleport_mcastu_test_mcast_destroy_armor(void);
#define mcast_destroy_armor teleport_mcastu_test_mcast_destroy_armor
extern void teleport_mcastu_test_mcast_stun_you(int);
#define mcast_stun_you teleport_mcastu_test_mcast_stun_you
extern int teleport_mcastu_test_mcast_geyser(int);
#define mcast_geyser teleport_mcastu_test_mcast_geyser
extern int teleport_mcastu_test_mcast_psi_bolt(int);
#define mcast_psi_bolt teleport_mcastu_test_mcast_psi_bolt
extern int teleport_mcastu_test_mcast_open_wounds(int);
#define mcast_open_wounds teleport_mcastu_test_mcast_open_wounds
extern void teleport_mcastu_test_mcast_blind_you(void);
#define mcast_blind_you teleport_mcastu_test_mcast_blind_you
extern int teleport_mcastu_test_mcast_paralyze(struct monst*);
#define mcast_paralyze teleport_mcastu_test_mcast_paralyze
extern void teleport_mcastu_test_mcast_spell(struct monst*,int,int);
#define mcast_spell teleport_mcastu_test_mcast_spell
extern boolean teleport_mcastu_test_is_undirected_spell(int);
#define is_undirected_spell teleport_mcastu_test_is_undirected_spell
extern boolean teleport_mcastu_test_spell_would_be_useless(struct monst*,int);
#define spell_would_be_useless teleport_mcastu_test_spell_would_be_useless
extern void teleport_mcastu_test_mcast_death_touch(struct monst*);
#define mcast_death_touch teleport_mcastu_test_mcast_death_touch
extern void teleport_mcastu_test_mcast_clone_wiz(struct monst*);
#define mcast_clone_wiz teleport_mcastu_test_mcast_clone_wiz
extern void teleport_mcastu_test_mcast_summon_mons(struct monst*);
#define mcast_summon_mons teleport_mcastu_test_mcast_summon_mons
extern void teleport_mcastu_test_mcast_disappear(struct monst*);
#define mcast_disappear teleport_mcastu_test_mcast_disappear
extern void teleport_mcastu_test_mcast_insects(struct monst*);
#define mcast_insects teleport_mcastu_test_mcast_insects
extern void teleport_mcastu_test_mcast_confuse_you(struct monst*);
#define mcast_confuse_you teleport_mcastu_test_mcast_confuse_you
extern void teleport_mcastu_test_mcast_weaken_you(struct monst*,int);
#define mcast_weaken_you teleport_mcastu_test_mcast_weaken_you
extern int teleport_mcastu_test_mcast_fire_pillar(struct monst*,int);
#define mcast_fire_pillar teleport_mcastu_test_mcast_fire_pillar
extern int teleport_mcastu_test_mcast_lightning(struct monst*,int);
#define mcast_lightning teleport_mcastu_test_mcast_lightning
#endif
#include "tu-mcastu-layout.h"
void probe_reset(unsigned s){int x,y;if(growth)free(growth);growth=0;memset(&u,0,sizeof u);memset(&gy,0,sizeof gy);memset(&svm,0,sizeof svm);memset(&svc,0,sizeof svc);memset(&svk,0,sizeof svk);memset(&gm,0,sizeof gm);memset(&gn,0,sizeof gn);memset(&gb,0,sizeof gb);memset(&gt,0,sizeof gt);memset(&gv,0,sizeof gv);memset(&iflags,0,sizeof iflags);memset(&caster,0,sizeof caster);memset(spawned,0,sizeof spawned);memset(&attack,0,sizeof attack);memset(opts,0,sizeof opts);objects_globals_init();monst_globals_init();u.ux=u.uy=10;u.umonnum=u.umonster=PM_HUMAN;u.uhp=u.uhpmax=200;gy.youmonst.data=&mons[PM_HUMAN];caster.data=&mons[PM_LICH];caster.mx=caster.my=12;caster.mux=caster.muy=10;caster.m_lev=25;caster.mhp=20;caster.mhpmax=40;caster.cham=NON_PM;caster.mcansee=1;attack.adtyp=AD_SPEL;attack.damn=2;attack.damd=6;opts[0]=opts[1]=opts[18]=opts[19]=opts[20]=1;opts[9]=14;svc.context.no_of_wizards=1;gt.tbx=2;gt.tby=-3;for(y=0;y<ROWNO;y++){rows[y]=vision[y];for(x=0;x<COLNO;x++)vision[y][x]=COULD_SEE|IN_SIGHT;}gv.viz_array=rows;seed=s;ri=nr=nspawn=0;output[0]=tracebuf[0]=caller[0]=0;}
void probe_option(int k,int v){int x,y;opts[k]=v;if(k==21)for(y=0;y<ROWNO;y++)for(x=0;x<COLNO;x++)vision[y][x]=v;}
int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nr=n;ri=0;}int probe_rng_count(void){return ri;}unsigned probe_rng_state(void){return seed;}const char*probe_trace(void){return tracebuf;}
void probe_set_monster(int k,long v){switch(k){case 0:caster.m_lev=v;break;case 1:caster.mhp=v;break;case 2:caster.mhpmax=v;break;case 3:caster.mcan=v;break;case 4:caster.mconf=v;break;case 5:caster.iswiz=v;break;case 6:caster.minvis=v;break;case 7:caster.invis_blkd=v;break;case 8:caster.mpeaceful=v;break;case 9:caster.permspeed=v;break;case 10:caster.mspec_used=v;break;case 11:caster.seen_resistance=v;break;case 12:caster.mux=v;break;case 13:caster.muy=v;break;case 14:caster.data=&mons[v];break;case 15:caster.cham=v;break;case 16:caster.female=v;break;}}
void probe_hero(int k,long v){switch(k){case 0:gy.youmonst.data=&mons[v];break;case 1:u.umonnum=v;break;case 2:u.uhp=v;break;case 3:u.uhpmax=v;break;case 4:u.mh=v;break;case 5:u.uundetected=v;break;case 6:u.uroleplay.deaf=v;break;case 7:svm.moves=v;break;case 8:gm.multi=v;break;case 9:svc.context.no_of_wizards=v;break;case 10:gy.youmonst.m_ap_type=v;break;case 11:gy.youmonst.mappearance=v;break;}}
void probe_prop(int p,int k,long v){if(k==0)u.uprops[p].intrinsic=v;else if(k==1)u.uprops[p].extrinsic=v;else u.uprops[p].blocked=v;}
void probe_attack(int k,int v){if(k==0)attack.adtyp=v;else if(k==1)attack.damn=v;else attack.damd=v;}
void*probe_pointer(int k){if(k==0)return &caster;if(k==1)return &attack;if(k==2)return output;return &u;}
long probe_action(int op,int a,int b,int c){switch(op){case 0:return castmu(&caster,&attack,a,b);case 1:touch_of_death(&caster);break;case 2:death_inflicted_by(output,"fixture death",a?&caster:0);break;case 3:return buzzmu(&caster,&attack);case 4:cursetxt(&caster,a);break;case 5:return choose_monster_spell(&caster,a);case 6:return m_cure_self(&caster,a);case 7:mcast_death_touch(&caster);break;case 8:mcast_clone_wiz(&caster);break;case 9:mcast_summon_mons(&caster);break;case 10:mcast_destroy_armor();break;case 11:mcast_weaken_you(&caster,a);break;case 12:mcast_disappear(&caster);break;case 13:mcast_stun_you(a);break;case 14:return mcast_geyser(a);case 15:return mcast_fire_pillar(&caster,a);case 16:return mcast_lightning(&caster,a);case 17:return mcast_psi_bolt(a);case 18:return mcast_open_wounds(a);case 19:mcast_insects(&caster);break;case 20:mcast_blind_you();break;case 21:return mcast_paralyze(&caster);case 22:mcast_confuse_you(&caster);break;case 23:mcast_spell(&caster,a,b);break;case 24:return is_undirected_spell(a);case 25:return spell_would_be_useless(&caster,a);}return 0;}
int probe_table_count(int t){
#ifdef TELEPORT_REFERENCE_TU
return t==0?SIZE(mcast_data):t==1?SIZE(mon_cleric_spells):SIZE(mon_wizard_spells);
#else
return 0;
#endif
}int probe_table(int t,int i,int f){
#ifdef TELEPORT_REFERENCE_TU
if(t==0)return f?mcast_data[i].flags:mcast_data[i].level;if(t==1)return mon_cleric_spells[i];return mon_wizard_spells[i];
#else
return 0;
#endif
}
const char*probe_snapshot(void){char*p=statebuf;int i;p+=sprintf(p,"m:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%lu;u:%d:%d:%d:%d:%ld:%s:%u:%d;out:%s;props:",caster.m_lev,caster.mhp,caster.mhpmax,caster.mcan,caster.mconf,caster.iswiz,caster.minvis,caster.invis_blkd,caster.mpeaceful,caster.permspeed,caster.mspec_used,caster.seen_resistance,u.uhp,u.uhpmax,u.mh,u.umonnum,gm.multi,gm.multi_reason?gm.multi_reason:"<NULL>",svc.context.no_of_wizards,mid(gb.buzzer),output);for(i=0;i<sizeof u.uprops;i++)p+=sprintf(p,"%02x",((unsigned char*)u.uprops)[i]);p+=sprintf(p,";lastmsg:%d;",iflags.last_msg);p+=sprintf(p,";killer:%d:%s;spawn:%d:",svk.killer.format,svk.killer.name,nspawn);for(i=0;i<nspawn;i++)p+=sprintf(p,"%d:%d:%d:%d:%d:%d;",spawned[i].data->pmidx,spawned[i].mx,spawned[i].my,spawned[i].mpeaceful,spawned[i].msleeping,spawned[i].mtame);return statebuf;}
uintptr_t probe_stack(void){return (uintptr_t)emscripten_stack_get_current();}
