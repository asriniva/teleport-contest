/* Controlled world/qtext sources; Lua and native table-option accessors are real. */
#include "hack.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include "tu-questpgr-layout.h"
__typeof__(gu) gu;__typeof__(gn) gn;__typeof__(gi) gi;__typeof__(svl) svl;__typeof__(gm) gm;__typeof__(svq) svq;__typeof__(gc) gc;__typeof__(svp) svp;__typeof__(svd) svd;__typeof__(svm) svm;__typeof__(gl) gl;
struct you u;struct flag flags;struct instance_flags iflags;__typeof__(program_state) program_state;__typeof__(windowprocs) windowprocs;
const struct Gender genders[]={ {"male","he","him","his","Mal",0},{"female","she","her","her","Fem",0},{"neuter","it","it","its","Ntr",0},{"plural","they","them","their","Plr",0} };
static int game_free_count;
#ifdef free
#undef free
#endif
extern void free(void*);
void teleport_probe_free(void*p){if(p)game_free_count++;free(p);}
#define free teleport_probe_free
static char tracebuf[262144],caller[100],input[16384],output[16384],qsource[32768];static int opts[16],rolls[256],roll_count,roll_idx;static unsigned random_state;static struct obj items[32];static struct monst monsters[8];static void*growth;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);vfprintf(stderr,fmt,ap);va_end(ap);abort();}
void impossible(const char*fmt,...){char buf[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(buf,sizeof buf,fmt,ap);va_end(ap);append("impossible:%s;",buf);}
void pline(const char*fmt,...){char buf[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(buf,sizeof buf,fmt,ap);va_end(ap);append("pline:%s;",buf);if(opts[5]){opts[5]=0;com_pager("nested");}}
boolean rng_log_enabled(void){return TRUE;}
void rng_log_set_caller(const char*file,int line,const char*fn){const char*b=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:file,line,fn);}
int (rn2)(int n){int v;if(n<=0)abort();if(roll_idx<roll_count)v=(unsigned)rolls[roll_idx]%(unsigned)n;else{random_state=random_state*1664525U+1013904223U;v=(random_state>>8)%(unsigned)n;}roll_idx++;append("rn2:%d:%d@%s;",n,v,caller);return v;}
struct permonst*mkclass(char sym,int flags_){append("class:%d:%d;",sym,flags_);return opts[3]?NULL:&mons[PM_SOLDIER];}
static winid wincreate(int type){append("create:%d;",type);return 17;}
static void fixture_putstr(winid w,int attr,const char*s){append("put:%d:%d:%s;",w,attr,s);if(opts[5]){opts[5]=0;com_pager("nested");}}
static void windisplay(winid w,boolean b){append("display:%d:%d;",w,b);}
static void windestroy(winid w){append("destroy:%d;",w);}
static void winhistory(const char*s,boolean restoring){append("history:%d:%s;",restoring,s);}
lua_State*nhl_init(nhl_sandbox_info*sbi){append("init:%u:%u:%u:%u;",sbi->flags,sbi->memlimit,sbi->steps,sbi->perpcall);if(opts[0])return NULL;if(opts[4]&&!growth)growth=malloc(32*1024*1024);return luaL_newstate();}
boolean nhl_loadlua(lua_State*L,const char*fname){int r;append("load:%s;",fname);if(opts[1])return FALSE;r=luaL_loadbuffer(L,qsource,strlen(qsource),"fixture quest.lua");if(!r)r=lua_pcall(L,0,0,0);if(r)panic("fixture lua error: %s",lua_tostring(L,-1));return TRUE;}
void nhl_done(lua_State*L){append("done:%d;",L!=NULL);if(L)lua_close(L);}
void livelog_printf(long category,const char*fmt,...){(void)category;(void)fmt;}
/* Controlled naming dependencies; distinct native rotating buffers retain pointer semantics. */
static char namebuf[8][BUFSZ];static int nameindex;
static char*nextname(void){return namebuf[(nameindex++)%8];}
const char*rank_of(int level,short role,boolean female){char*b=nextname();snprintf(b,BUFSZ,"rank%d-%d-%d",level,role,female);return b;}
const char*artiname(int artifact){(void)artifact;return opts[2]?"Eyes of the Overworld":"Orb of Detection";}
const char*align_str(aligntyp type){return type>0?"lawful":type<0?"chaotic":"neutral";}
const char*align_gname(aligntyp type){return type>0?"Lawgod":type<0?"Chaosgod":"Balancegod";}
const char*align_gtitle(aligntyp type){return type>0?"Goddess":type<0?"Fiend":"Divinity";}
char*the(const char*s){char*b=nextname();snprintf(b,BUFSZ,"the %s",s);return b;}
char*an(const char*s){char*b=nextname();snprintf(b,BUFSZ,"%s %s",strchr("aeiouAEIOU",*s)?"an":"a",s);return b;}
char*An(const char*s){char*b=an(s);*b=highc(*b);return b;}
char*makeplural(const char*s){char*b=nextname();snprintf(b,BUFSZ,"%ss",s);return b;}
char*makesingular(const char*s){char*b=nextname();size_t n=strlen(s);strcpy(b,s);if(n&&b[n-1]=='s')b[n-1]=0;return b;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/questpgr.c"
#define PRIVATE(n) n
#else
extern const char*teleport_questpgr_test_intermed(void),*teleport_questpgr_test_neminame(void),*teleport_questpgr_test_guardname(void),*teleport_questpgr_test_homebase(void);
extern struct obj*teleport_questpgr_test_find_qarti(struct obj*);
extern void teleport_questpgr_test_qtext_pronoun(char,char),teleport_questpgr_test_convert_arg(char),teleport_questpgr_test_convert_line(char*,char*),teleport_questpgr_test_deliver_by_pline(const char*),teleport_questpgr_test_deliver_by_window(const char*,int);
extern boolean teleport_questpgr_test_skip_pager(boolean),teleport_questpgr_test_com_pager_core(const char*,const char*,boolean,char**);
#define PRIVATE(n) teleport_questpgr_test_##n
#endif
void probe_reset(unsigned seed){int i;if(growth){free(growth);growth=NULL;}monst_globals_init();memset(&gu,0,sizeof gu);memset(&gn,0,sizeof gn);memset(&gi,0,sizeof gi);memset(&svl,0,sizeof svl);memset(&gm,0,sizeof gm);memset(&svq,0,sizeof svq);memset(&gc,0,sizeof gc);memset(&svp,0,sizeof svp);memset(&svd,0,sizeof svd);memset(&svm,0,sizeof svm);memset(&gl,0,sizeof gl);memset(&u,0,sizeof u);memset(&flags,0,sizeof flags);memset(&program_state,0,sizeof program_state);memset(items,0,sizeof items);memset(monsters,0,sizeof monsters);memset(opts,0,sizeof opts);memset((void*)&windowprocs,0,sizeof windowprocs);windowprocs.win_create_nhwindow=wincreate;windowprocs.win_putstr=fixture_putstr;windowprocs.win_display_nhwindow=windisplay;windowprocs.win_destroy_nhwindow=windestroy;windowprocs.win_putmsghistory=winhistory;gu.urole.name.m="Explorer";gu.urole.name.f="Adventuress";gu.urole.filecode="Arc";gu.urole.homebase="the Home";gu.urole.intermed="the Cavern";gu.urole.questarti=ART_ORB_OF_DETECTION;gu.urole.ldrnum=PM_HUMAN;gu.urole.neminum=PM_WIZARD_OF_YENDOR;gu.urole.guardnum=PM_SOLDIER;gu.urole.enemy1num=PM_GIANT_ANT;gu.urole.enemy2num=PM_SOLDIER;gu.urole.enemy1sym=S_ANT;gu.urole.enemy2sym=S_HUMAN;gu.urole.mnum=PM_HUMAN;strcpy(svp.plname,"Alice");strcpy(svd.dungeons[0].dname,"Dungeons of Doom");u.ulevel=15;u.ualignbase[A_ORIGINAL]=A_NEUTRAL;u.ualign.type=A_CHAOTIC;svq.quest_status.godgend=1;svq.quest_status.ldrgend=0;svq.quest_status.nemgend=2;for(i=0;i<SIZE(items);i++)items[i].oartifact=0;for(i=0;i<SIZE(monsters);i++){monsters[i].mhp=10;monsters[i].data=&mons[PM_HUMAN];}strcpy(qsource,"questtext={common={hello={text='Hello %p'}},Arc={hello={text='Greetings %p'}}}");tracebuf[0]=caller[0]=input[0]=output[0]=0;random_state=seed;roll_count=roll_idx=nameindex=game_free_count=0;}
void probe_option(int i,int v){opts[i]=v;}
void probe_source(const char*s){strcpy(qsource,s);}
void probe_input(const char*s){strcpy(input,s);}
void probe_gender(int god,int leader,int nem){svq.quest_status.godgend=god;svq.quest_status.ldrgend=leader;svq.quest_status.nemgend=nem;}
void probe_hero(int k,long v){switch(k){case 0:flags.female=v;break;case 1:u.ulevel=v;break;case 2:u.ualignbase[A_ORIGINAL]=v;break;case 3:u.ualign.type=v;break;case 4:HBlinded=v;break;case 5:EBlinded=v;break;case 6:BBlinded=v;break;case 7:program_state.wizkit_wishing=v;break;case 8:gu.urole.enemy1num=v;break;case 9:gu.urole.enemy2num=v;break;case 10:svm.mvitals[gu.urole.enemy1num].mvflags=v;break;default:svm.mvitals[gu.urole.enemy2num].mvflags=v;}}
void probe_object(int i,int art,int next,int child){items[i].oartifact=art;items[i].nobj=next<0?NULL:&items[next];items[i].cobj=child<0?NULL:&items[child];}
void probe_chain(int k,int index){struct obj*o=index<0?NULL:&items[index];switch(k){case 0:gi.invent=o;break;case 1:fobj=o;break;case 2:monsters[0].minvent=o;fmon=&monsters[0];break;case 3:monsters[1].minvent=o;gm.migrating_mons=&monsters[1];break;case 4:gm.migrating_objs=o;break;default:svl.level.buriedobjlist=o;}}
void probe_dead(int i,int hp){monsters[i].mhp=hp;}
void probe_level_message(const char*s){gl.lev_message=dupstr(s);}
int*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){roll_count=n;}int probe_rng_count(void){return roll_idx;}unsigned probe_rng_state(void){return random_state;}
const char*probe_trace(void){return tracebuf;}void probe_clear_trace(void){tracebuf[0]=caller[0]=0;}
void*probe_pointer(int k,int i){switch(k){case 0:return input;case 1:return output;case 2:return gc.cvt_buf;case 3:return gn.nambuf;case 4:return &items[i];case 5:return &monsters[i];default:return gl.lev_message;}}
long probe_action(int op,int a,int b,int c){const char*s=NULL;struct obj*o;struct permonst*p;char*raw=NULL;switch(op){case 0:return quest_info(a);case 1:s=ldrname();break;case 2:s=PRIVATE(intermed)();break;case 3:return is_quest_artifact(&items[a]);case 4:o=PRIVATE(find_qarti)(a<0?NULL:&items[a]);return o?(long)(o-items):-1;case 5:o=find_quest_artifact(a);return o?(long)(o-items):-1;case 6:s=PRIVATE(neminame)();break;case 7:s=PRIVATE(guardname)();break;case 8:s=PRIVATE(homebase)();break;case 9:return stinky_nemesis(&monsters[0]);case 10:PRIVATE(qtext_pronoun)(a,b);break;case 11:PRIVATE(convert_arg)(a);break;case 12:PRIVATE(convert_line)(input,output);break;case 13:PRIVATE(deliver_by_pline)(input);break;case 14:PRIVATE(deliver_by_window)(input,a);break;case 15:return PRIVATE(skip_pager)(a);case 16:{int ok=PRIVATE(com_pager_core)(a?"Arc":"common",input,b,c?&raw:NULL);if(raw){strcpy(output,raw);free(raw);}return ok;}case 17:com_pager(input);break;case 18:qt_pager(input);break;case 19:p=qt_montype();return p?monsndx(p):-1;default:deliver_splev_message();}if(s)strcpy(output,s);return 0;}
int probe_free_count(void){return game_free_count;}
size_t probe_stack(void){return emscripten_stack_get_current();}
