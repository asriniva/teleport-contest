/* Controlled world effects; actual C catalogues, structs, callbacks and formatting. */
#include "hack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <emscripten/stack.h>
#include "tu-sounds-layout.h"
struct you u;__typeof__(svl) svl;__typeof__(svr) svr;__typeof__(svc) svc;__typeof__(svq) svq;__typeof__(gu) gu;__typeof__(gy) gy;__typeof__(gi) gi;__typeof__(ga) ga;__typeof__(gc) gc;__typeof__(gn) gn;__typeof__(gm) gm;__typeof__(svd) svd;__typeof__(svm) svm;__typeof__(gv) gv;
struct flag flags;struct instance_flags iflags;__typeof__(sysopt) sysopt;struct obj*uwep,*uarm,*uarmc,*uarmh,*uarms,*uarmg,*uarmf,*uarmu;
__typeof__(c_common_strings) c_common_strings={.c_nothing_happens="Nothing happens."};
const struct Gender genders[]={{"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"group","they","them","their","Grp",0}};
static struct monst monsters[8];static struct obj items[16];static struct mextra extras[8];static struct edog dogs[8];static struct emin minions[8];static struct epri priests[8];static struct trap fixture_trap;static char tracebuf[262144],caller[128],input[8192],output[8192];static int options[64],rolls[1024],roll_count,roll_idx;static unsigned random_state;static seenV visual[ROWNO][COLNO];static seenV*visual_rows[ROWNO];static int glyphs[COLNO][ROWNO];static void*growth;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}static int mid(struct monst*m){return m?(int)(m-monsters):-1;}static int oid(struct obj*o){return o?(int)(o-items):-1;}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);vfprintf(stderr,fmt,ap);va_end(ap);abort();}
static void message(const char*kind,const char*fmt,va_list ap){char b[BUFSZ*2];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",kind,b);}
void pline(const char*fmt,...){va_list ap;va_start(ap,fmt);message("pline",fmt,ap);va_end(ap);}void You(const char*fmt,...){va_list ap;va_start(ap,fmt);message("You",fmt,ap);va_end(ap);}void You_hear(const char*fmt,...){va_list ap;va_start(ap,fmt);message("hear",fmt,ap);va_end(ap);}void Your(const char*fmt,...){va_list ap;va_start(ap,fmt);message("Your",fmt,ap);va_end(ap);}void You_cant(const char*fmt,...){va_list ap;va_start(ap,fmt);message("cant",fmt,ap);va_end(ap);}void verbalize(const char*fmt,...){va_list ap;va_start(ap,fmt);message("verbal",fmt,ap);va_end(ap);}void pline_The(const char*fmt,...){va_list ap;va_start(ap,fmt);message("The",fmt,ap);va_end(ap);}
void impossible(const char*fmt,...){va_list ap;va_start(ap,fmt);message("impossible",fmt,ap);va_end(ap);}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*file,int line,const char*fn){const char*b=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:file,line,fn);}
int(rn2)(int n){int v;if(n<=0)return 0;if(roll_idx<roll_count)v=(unsigned)rolls[roll_idx]%(unsigned)n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}roll_idx++;append("rng:%d:%d@%s;",n,v,caller);return v;}
struct monst*get_iter_mons(boolean(*fn)(struct monst*)){struct monst*m;append("iterate;");for(m=fmon;m;m=m->nmon){append("candidate:%d;",mid(m));if(fn(m))return m;}return NULL;}
static void fixture_init(void){append("soundinit;");}static void fixture_exit(const char*reason){append("soundexit:%s;",reason);}
boolean Death_quote(char*out,int size){append("deathquote:%d;",size);if(options[1])strcpy(out,"A FIXTURE QUOTE");return options[1];}
char*Monnam(struct monst*m){static char b[BUFSZ];snprintf(b,sizeof b,"Monster%d",mid(m));return b;}char*mon_nam(struct monst*m){return Monnam(m);}
char*an(const char*s){static char b[BUFSZ];snprintf(b,sizeof b,"a %s",s);return b;}const char*body_part(int part){return part==BLOOD?"blood":part==HAIR?"hair":"head";}
int canseemon(struct monst*m){append("see:%d;",mid(m));return options[2];}int sensemon(struct monst*m){append("sense:%d;",mid(m));return options[3];}
int could_seduce(struct monst*a,struct monst*b,struct attack*c){append("seduce:%d;",mid(a));return options[4];}
const char*currency(long amount){append("currency:%ld;",amount);return "zorkmids";}
int cursed(struct obj*o){append("cursed:%d;",oid(o));o->bknown=1;return o->cursed;}
struct obj*g_at(coordxy x,coordxy y){append("gold:%d:%d;",x,y);return options[5]?&items[0]:NULL;}
boolean gd_sound(void){append("gdsound;");return options[6];}int genus(int pm,int mode){append("genus:%d:%d;",pm,mode);return options[7];}
int getdir(const char*prompt){append("getdir:%s;",prompt);if(options[30]&&!growth)growth=malloc(32*1024*1024);return options[0];}
int glyph_at(coordxy x,coordxy y){append("glyph:%d:%d;",x,y);return glyphs[x][y];}
const char*halu_gname(aligntyp a){append("god:%d;",a);return "Fixturegod";}
const char*helm_simple_name(struct obj*o){append("helmet:%d;",oid(o));return "helmet";}
boolean inhistemple(struct monst*m){append("temple:%d;",mid(m));return options[8];}
int isok(coordxy x,coordxy y){return x>0&&x<COLNO&&y>=0&&y<ROWNO;}
int midnight(void){append("midnight;");return options[9];}int night(void){append("night;");return options[10];}
aligntyp mon_aligntyp(struct monst*m){append("align:%d;",mid(m));return options[11];}
long money_cnt(struct obj*o){append("money:%d;",oid(o));return options[12];}
void noisy_shop(struct mkroom*r){append("shopnoise:%ld;",(long)(r-svr.rooms));}void nomul(int count){append("nomul:%d;",count);gm.multi=count;}
const char*noveltitle(int*index){append("novel:%d;",*index);(*index)++;return options[13]?"Snuff":"Fixture Novel";}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
boolean p_coaligned(struct monst*m){append("coaligned:%d;",mid(m));return options[14];}
const char*pmname(struct permonst*p,int gender){append("pmname:%d:%d;",(int)(p-mons),gender);return p->pmnames[NEUTRAL];}
int poly_gender(void){append("gender;");return options[15];}int pronoun_gender(struct monst*m,unsigned flags_){append("pronoun:%d:%u;",mid(m),flags_);return options[16];}
char*rndmonnam(char*s){append("rndname;");return "hallucinatory critter";}
boolean same_race(struct permonst*a,struct permonst*b){append("race:%d:%d;",(int)(a-mons),(int)(b-mons));return a->mlet==b->mlet;}
struct mkroom*search_special(schar type){append("search:%d;",type);return options[17]?&svr.rooms[0]:NULL;}
struct obj*shop_object(coordxy x,coordxy y){append("shopobject:%d:%d;",x,y);return options[18]?&items[0]:NULL;}
struct trap*t_at(coordxy x,coordxy y){append("trap:%d:%d;",x,y);return options[19]?&fixture_trap:NULL;}
char temple_occupied(char*s){append("occupied:%d;",(int)*s);return options[20];}char vault_occupied(char*s){append("vault:%d;",(int)*s);return options[21];}
boolean tended_shop(struct mkroom*r){append("tended:%ld;",(long)(r-svr.rooms));return options[22];}
struct obj*u_have_novel(void){append("have_novel;");return options[23]?&items[1]:NULL;}
char*vtense(const char*subject,const char*verb){static char b[BUFSZ];snprintf(b,sizeof b,"%ss",verb);return b;}
void wake_nearto(coordxy x,coordxy y,int distance){append("wake:%d:%d:%d;",x,y,distance);}
struct obj*which_armor(struct monst*m,long mask){append("armor:%d:%ld;",mid(m),mask);return options[24]?&items[2]:NULL;}
boolean accessible(coordxy a0,coordxy a1){append("accessible;");return 0;}
void aggravate(void){append("aggravate;");}
void cuss(struct monst * a0){append("cuss;");}
int demon_talk(struct monst * a0){append("demon_talk;");return 0;}
int doconsult(struct monst * a0){append("doconsult;");return 0;}
int doseduce(struct monst * a0){append("doseduce;");return 0;}
void map_invisible(coordxy a0,coordxy a1){append("map_invisible;");}
void mplayer_talk(struct monst * a0){append("mplayer_talk;");}
void price_quote(struct obj * a0){append("price_quote;");}
void priest_talk(struct monst * a0){append("priest_talk;");}
void quest_chat(struct monst * a0){append("quest_chat;");}
void shk_chat(struct monst * a0){append("shk_chat;");}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/sounds.c"
#define PRIVATE(n) n
static struct sound_procs*source_procs(void){return &nosound_procs;}
#else
extern int teleport_sounds_test_mon_in_room(struct monst*,int),teleport_sounds_test_dochat(void);
extern boolean teleport_sounds_test_throne_mon_sound(struct monst*),teleport_sounds_test_beehive_mon_sound(struct monst*),teleport_sounds_test_morgue_mon_sound(struct monst*),teleport_sounds_test_zoo_mon_sound(struct monst*),teleport_sounds_test_temple_priest_sound(struct monst*),teleport_sounds_test_oracle_sound(struct monst*),teleport_sounds_test_mon_is_gecko(struct monst*);
extern struct monst*teleport_sounds_test_responsive_mon_at(int,int);
extern void*teleport_sounds_test_nosound(void);
#define PRIVATE(n) teleport_sounds_test_##n
static struct sound_procs*source_procs(void){return teleport_sounds_test_nosound();}
#endif
static struct sound_procs initial_source;static int source_saved;
void probe_reset(unsigned seed){int x,y;if(growth){free(growth);growth=NULL;}objects_globals_init();monst_globals_init();memset(&u,0,sizeof u);memset(&svl,0,sizeof svl);memset(&svr,0,sizeof svr);memset(&svc,0,sizeof svc);memset(&svq,0,sizeof svq);memset(&gu,0,sizeof gu);memset(&gy,0,sizeof gy);memset(&gi,0,sizeof gi);memset(&ga,0,sizeof ga);memset(&gc,0,sizeof gc);memset(&gn,0,sizeof gn);memset(&gm,0,sizeof gm);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&svm,0,sizeof svm);memset(&svd,0,sizeof svd);memset(&sysopt,0,sizeof sysopt);memset(monsters,0,sizeof monsters);memset(items,0,sizeof items);memset(extras,0,sizeof extras);memset(dogs,0,sizeof dogs);memset(priests,0,sizeof priests);memset(minions,0,sizeof minions);memset(options,0,sizeof options);memset(&fixture_trap,0,sizeof fixture_trap);u.ux=10;u.uy=8;u.dx=1;u.uz.dnum=1;u.uz.dlevel=5;u.umonnum=u.umonster=PM_HUMAN;gu.urole.guardnum=PM_HUMAN;gu.urole.mnum=PM_WIZARD;gu.urace.mnum=PM_HUMAN;gu.urace.noun="human";gu.urace.individual.m="man";gu.urace.individual.f="woman";flags.acoustics=1;options[0]=1;options[7]=PM_HUMAN;options[8]=1;options[11]=A_LAWFUL;options[14]=1;options[22]=1;svm.moves=1000;gy.youmonst.data=&mons[PM_HUMAN];for(x=0;x<8;x++){struct monst*m=&monsters[x];m->data=&mons[PM_HUMAN];m->m_id=100+x;m->mx=11+x;m->my=8;m->mhp=m->mhpmax=20;m->mcanmove=m->mcansee=1;m->mextra=&extras[x];extras[x].edog=&dogs[x];extras[x].epri=&priests[x];extras[x].emin=&minions[x];dogs[x].hungrytime=1000;priests[x].shroom=ROOMOFFSET;priests[x].shrpos.x=15;priests[x].shrpos.y=9;priests[x].shralign=A_LAWFUL;minions[x].min_align=A_LAWFUL;}for(x=0;x<16;x++){items[x].otyp=HELMET;items[x].oclass=ARMOR_CLASS;items[x].quan=1;items[x].novelidx=0;}for(y=0;y<ROWNO;y++){visual_rows[y]=visual[y];for(x=0;x<COLNO;x++){visual[y][x]=IN_SIGHT|COULD_SEE;levl[x][y].typ=ROOM;levl[x][y].roomno=ROOMOFFSET;glyphs[x][y]=GLYPH_MON_MALE_OFF+PM_HUMAN;svl.lastseentyp[x][y]=ROOM;}}gv.viz_array=visual_rows;svr.rooms[0].lx=3;svr.rooms[0].hx=5;svr.rooms[0].ly=4;svr.rooms[0].hy=6;svr.rooms[0].rtype=COURT;astral_level.dnum=3;astral_level.dlevel=1;sanctum_level.dnum=4;sanctum_level.dlevel=1;oracle_level.dnum=1;oracle_level.dlevel=7;uwep=uarm=uarmc=uarmh=uarms=uarmg=uarmf=uarmu=NULL;assign_soundlib(soundlib_nosound);if(!source_saved){memcpy(&initial_source,source_procs(),sizeof initial_source);source_saved=1;}memcpy(source_procs(),&initial_source,sizeof initial_source);memset(&soundprocs,0,sizeof soundprocs);memset(input,0,sizeof input);memset(output,0xa5,sizeof output);output[0]=0;tracebuf[0]=caller[0]=0;random_state=seed;roll_count=roll_idx=0;}
void probe_option(int i,int v){options[i]=v;}
void probe_input(const char*s){strcpy(input,s);}void probe_output(const char*s){memset(output,0xa5,sizeof output);strcpy(output,s);}
void probe_mon(int i,int k,long v){struct monst*m=&monsters[i];switch(k){case 0:m->data=&mons[v];break;case 1:m->msleeping=v;break;case 2:m->mcanmove=v;break;case 3:m->mcansee=v;break;case 4:m->mpeaceful=v;break;case 5:m->mtame=v;break;case 6:m->mcan=v;break;case 7:m->mconf=v;break;case 8:m->mflee=v;break;case 9:m->mstun=v;break;case 10:m->mtrapped=v;break;case 11:m->mundetected=v;break;case 12:m->ispriest=v;break;case 13:m->isshk=v;break;case 14:m->isminion=v;break;case 15:m->meating=v;break;case 16:m->mhp=v;break;case 17:m->mhpmax=v;break;case 18:m->female=v;break;case 19:m->mstrategy=v;break;case 20:m->m_ap_type=v;break;case 21:m->mx=v;break;case 22:m->my=v;break;case 23:EDOG(m)->hungrytime=v;break;case 24:EMIN(m)->renegade=v;break;case 25:m->nmon=v<0?NULL:&monsters[v];break;default:m->m_id=v;}}
void probe_pm(int index,int msound,int mlet){mons[index].msound=msound;mons[index].mlet=mlet;}
void probe_hero(int k,long v){switch(k){case 0:HDeaf=v;break;case 1:u.uroleplay.deaf=v;break;case 2:HBlinded=v;break;case 3:EBlinded=v;break;case 4:BBlinded=v;break;case 5:HHallucination=v;break;case 6:HHalluc_resistance=v;break;case 7:HInvis=v;break;case 8:BInvis=v;break;case 9:Strangled=v;break;case 10:HConflict=v;break;case 11:u.uinwater=v;break;case 12:u.uswallow=v;break;case 13:u.umonnum=v;gy.youmonst.data=&mons[v];break;case 14:flags.female=v;break;case 15:flags.moonphase=v;break;case 16:flags.acoustics=v;break;case 17:u.usteed=v<0?NULL:&monsters[v];break;case 18:u.dx=v;break;case 19:u.dy=v;break;case 20:u.dz=v;break;case 21:svc.context.run=v;break;case 22:svm.moves=v;break;case 23:svq.quest_status.leader_m_id=v;break;case 24:sysopt.seduce=v;break;case 25:ga.active_soundlib=v;break;default:gc.chosen_soundlib=v;}}
void probe_equipment(int slot,int index){struct obj*o=index<0?NULL:&items[index];switch(slot){case 0:uwep=o;break;case 1:uarm=o;break;case 2:uarmc=o;break;case 3:uarmh=o;break;case 4:uarms=o;break;case 5:uarmg=o;break;case 6:uarmf=o;break;default:uarmu=o;}}
void probe_object(int i,int typ,int cursed_,int known){items[i].otyp=typ;items[i].oclass=objects[typ].oc_class;items[i].cursed=cursed_;items[i].bknown=known;}
void probe_cell(int x,int y,int typ,int roomno,int glyph,int visibility){levl[x][y].typ=typ;levl[x][y].roomno=roomno;glyphs[x][y]=glyph;visual[y][x]=visibility;}
void probe_grid(int kind,int x,int y,int index){if(kind==0)svl.level.monsters[x][y]=index<0?NULL:&monsters[index];else svl.level.objects[x][y]=index<0?NULL:&items[index];}
void probe_chain(int i,int next){fmon=i<0?NULL:&monsters[i];if(i>=0)monsters[i].nmon=next<0?NULL:&monsters[next];}
void probe_room(int type){svr.rooms[0].rtype=type;}
void probe_level_flag(int i,unsigned v){switch(i){case 0:svl.level.flags.nfountains=v;break;case 1:svl.level.flags.nsinks=v;break;case 2:svl.level.flags.has_court=v;break;case 3:svl.level.flags.has_swamp=v;break;case 4:svl.level.flags.has_vault=v;break;case 5:svl.level.flags.has_beehive=v;break;case 6:svl.level.flags.has_morgue=v;break;case 7:svl.level.flags.has_barracks=v;break;case 8:svl.level.flags.has_zoo=v;break;case 9:svl.level.flags.has_shop=v;break;default:svl.level.flags.has_temple=v;}}
void probe_level(int dnum,int dlevel){u.uz.dnum=dnum;u.uz.dlevel=dlevel;}
void probe_sound(int kind,int mode){struct sound_procs*p=kind?source_procs():&soundprocs;if(mode==0)memset(p,0,sizeof *p);else if(mode==1){memset(p,0x5a,sizeof *p);p->soundname="poisoned";p->soundlib_id=soundlib_nosound;p->sound_exit_nhsound=fixture_exit;p->sound_init_nhsound=fixture_init;}else if(mode==2){p->sound_exit_nhsound=fixture_exit;p->sound_init_nhsound=fixture_init;}else p->soundname="nosound,aliases";}
uint64_t probe_callback(int which){return (uintptr_t)(which?(void*)fixture_exit:(void*)fixture_init);}
int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){roll_count=n;}int probe_rng_count(void){return roll_idx;}unsigned probe_rng_state(void){return random_state;}
const char*probe_trace(void){return tracebuf;}void probe_clear_trace(void){tracebuf[0]=caller[0]=0;}
void*probe_pointer(int k,int i){switch(k){case 0:return input;case 1:return output;case 2:return &monsters[i];case 3:return &items[i];case 4:return &soundprocs;case 5:return source_procs();default:return &fixture_trap;}}
long probe_scalar(int i){switch(i){case 0:return iflags.last_msg;case 1:return svc.context.run;case 2:return gm.multi;case 3:return svc.context.tribute.Deathnotice;case 4:return fixture_trap.tseen;case 5:return items[0].bknown;case 6:return items[1].novelidx;case 7:return items[2].bknown;case 8:return ga.active_soundlib;case 9:return gc.chosen_soundlib;case 10:return svl.level.flags.has_vault;case 11:return svl.level.flags.has_shop;default:return monsters[i-12].mstrategy;}}
const char*probe_reason(void){return gm.multi_reason;}const char*probe_nomove(void){return gn.nomovemsg;}
const char*probe_table_string(int i){
#ifdef TELEPORT_REFERENCE_TU
return h_sounds[i];
#else
return NULL;
#endif
}
long probe_action(int op,int a,int b,uint64_t size){struct monst*m=&monsters[a>=0&&a<8?a:0];const char*s=NULL;char*ret;switch(op){case 0:return PRIVATE(mon_in_room)(m,b);case 1:return PRIVATE(throne_mon_sound)(m);case 2:return PRIVATE(beehive_mon_sound)(m);case 3:return PRIVATE(morgue_mon_sound)(m);case 4:return PRIVATE(zoo_mon_sound)(m);case 5:return PRIVATE(temple_priest_sound)(m);case 6:return PRIVATE(oracle_sound)(m);case 7:dosounds();break;case 8:s=growl_sound(m);break;case 9:growl(m);break;case 10:yelp(m);break;case 11:whimper(m);break;case 12:beg(m);break;case 13:s=maybe_gasp(m);break;case 14:s=cry_sound(m);break;case 15:return PRIVATE(mon_is_gecko)(m);case 16:return domonnoise(m);case 17:return dotalk();case 18:return PRIVATE(dochat)();case 19:return mid(PRIVATE(responsive_mon_at)(a,b));case 20:return tiphat();case 21:activate_chosen_soundlib();break;case 22:assign_soundlib(a);break;case 23:get_soundlib_name(output,a);break;case 24:return soundlib_id_from_opt(input);case 25:ret=base_soundname_to_filename(input,b?NULL:output,size,a);return ret?ret-output:-1;case 26:set_voice(m,1,2,3);break;default:sound_speak(input);break;}if(s)strcpy(output,s);return s?1:0;}
size_t probe_stack(void){return emscripten_stack_get_current();}
