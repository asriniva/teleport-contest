/* Controlled menus/world boundaries; original C catalogues, libc and hacklib. */
#include "hack.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <emscripten/stack.h>
__typeof__(gu) gu;__typeof__(gr) gr;__typeof__(svp) svp;__typeof__(gp) gp;__typeof__(svq) svq;__typeof__(sysopt) sysopt;__typeof__(program_state) program_state;
struct flag flags;struct instance_flags iflags;__typeof__(windowprocs) windowprocs;const __typeof__(cg) cg={0};
const glyph_info nul_glyphinfo={0};
static struct monst mon;static char tracebuf[262144],caller[128],input[4096],output[4096],names[256],generic[256];static int rolls[1024],nroll,rollindex,pick_n[128],pick_a[128],pick_b[128],pickindex,entries,freed;static unsigned seed;static char answer;static void*growth;
static anything entry_ids[256];static char entry_labels[256][BUFSZ];
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
void panic(const char*fmt,...){va_list ap;va_start(ap,fmt);vfprintf(stderr,fmt,ap);va_end(ap);abort();}
void impossible(const char*fmt,...){char b[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void pline(const char*fmt,...){char b[BUFSZ];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);}
boolean rng_log_enabled(void){return TRUE;}void rng_log_set_caller(const char*file,int line,const char*fn){const char*b=strrchr(file,'/');snprintf(caller,sizeof caller,"%s:%d:%s",b?b+1:file,line,fn);}
int(rn2)(int n){int v;if(n<=0)return 0;if(rollindex<nroll)v=(unsigned)rolls[rollindex]%(unsigned)n;else{seed=seed*1664525U+1013904223U;v=(seed>>8)%(unsigned)n;}rollindex++;append("rng:%d:%d@%s;",n,v,caller);return v;}
int rn2_on_display_rng(int n){char saved[128];int v;strcpy(saved,caller);strcpy(caller,"display");v=(rn2)(n);strcpy(caller,saved);return v;}
const char*align_gtitle(aligntyp a){append("gtitle:%d;",a);return a==A_NEUTRAL?"goddess":"god";}
void nh_terminate(int code){append("terminate:%d;",code);abort();}
#ifdef free
#undef free
#endif
extern void free(void*);
void teleport_probe_free(void*p){if(p)freed++;free(p);}
#define free teleport_probe_free
static winid create_window(int type){append("create:%d;",type);return 7;}
static void start_window(winid win,unsigned long behavior){append("start:%d:%lu;",win,behavior);entries=0;}
static void end_window(winid win,const char*s){append("end:%d:%s;",win,s?s:"NULL");}
static void destroy_window(winid win){append("destroy:%d;",win);}
static void put_window(winid win,int attr,const char*s){append("put:%d:%d:%s;",win,attr,s);}
static void ask_window(void){append("ask:%s;",names);strcpy(svp.plname,names);if(growth==(void*)1){growth=malloc(32*1024*1024);}}
void add_menu(winid w,const glyph_info*g,const anything*any,char a,char b,int attr,int color,const char*s,unsigned f){uintptr_t raw=any?(uintptr_t)any->a_void:0;append("add:%d:",w);int isstring=0,i;for(i=0;i<NUM_ROLES;i++)if(raw==(uintptr_t)roles[i].name.m)isstring=1;for(i=0;i<NUM_RACES;i++)if(raw==(uintptr_t)races[i].noun)isstring=1;for(i=0;i<ROLE_GENDERS;i++)if(raw==(uintptr_t)genders[i].adj)isstring=1;for(i=0;i<ROLE_ALIGNS;i++)if(raw==(uintptr_t)aligns[i].adj)isstring=1;if(isstring)append("s:%s",any->a_string);else append("i:%d",any?any->a_int:0);append(":%d:%d:%d:%d:%u:%s;",a,b,attr,color,f,s);if(entries<256){entry_ids[entries]=any?*any:cg.zeroany;snprintf(entry_labels[entries],BUFSZ,"%s",s);entries++;}}
void add_menu_str(winid w,const char*s){append("str:%d:%s;",w,s);}
char*an(const char*s){static char b[BUFSZ];snprintf(b,sizeof b,"a %s",s);return b;}
int select_menu(winid w,int how,menu_item**selected){int n=pick_n[pickindex],values[2]={pick_a[pickindex],pick_b[pickindex]},i;append("select:%d:%d:%d;",w,how,n);pickindex++;if(n<=0){*selected=NULL;return n;}*selected=malloc(n*sizeof **selected);memset(*selected,0,n*sizeof **selected);for(i=0;i<n;i++){int v=values[i%2];if(v<=-1000){int j=-1000-v;if(j>=0&&j<entries)(*selected)[i].item=entry_ids[j];}else (*selected)[i].item.a_int=v;(*selected)[i].count=-1;}return n;}
char yn_function(const char*prompt,const char*choices,char def,boolean history){append("yn:%s:%s:%d:%d;",prompt,choices?choices:"NULL",def,history);return answer;}
#ifdef TELEPORT_REFERENCE_TU
#include "../.cache/wasm64-build/tree/src/role.c"
#else
extern int teleport_role_test_randrole_filtered(void);
#define randrole_filtered teleport_role_test_randrole_filtered
extern char* teleport_role_test_promptsep(char*,int);
#define promptsep teleport_role_test_promptsep
extern int teleport_role_test_role_gendercount(int);
#define role_gendercount teleport_role_test_role_gendercount
extern int teleport_role_test_race_alignmentcount(int);
#define race_alignmentcount teleport_role_test_race_alignmentcount
extern boolean teleport_role_test_reset_role_filtering(void);
#define reset_role_filtering teleport_role_test_reset_role_filtering
extern int teleport_role_test_maybe_skip_seps(int,int);
#define maybe_skip_seps teleport_role_test_maybe_skip_seps
extern int teleport_role_test_plsel_startmenu(int,int);
#define plsel_startmenu teleport_role_test_plsel_startmenu
extern void teleport_role_test_setup_rolemenu(int,int,int,int,int);
#define setup_rolemenu teleport_role_test_setup_rolemenu
extern void teleport_role_test_setup_racemenu(int,int,int,int,int);
#define setup_racemenu teleport_role_test_setup_racemenu
extern void teleport_role_test_setup_gendmenu(int,int,int,int,int);
#define setup_gendmenu teleport_role_test_setup_gendmenu
extern void teleport_role_test_setup_algnmenu(int,int,int,int,int);
#define setup_algnmenu teleport_role_test_setup_algnmenu
#endif
#include "tu-role-layout.h"
void probe_reset(unsigned s){if(growth&&(growth!=(void*)1))free(growth);growth=NULL;memset(&gu,0,sizeof gu);memset(&gr,0,sizeof gr);memset(&svp,0,sizeof svp);memset(&gp,0,sizeof gp);memset(&svq,0,sizeof svq);memset(&sysopt,0,sizeof sysopt);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);memset(&program_state,0,sizeof program_state);memset(&mon,0,sizeof mon);objects_globals_init();monst_globals_init();flags.initrole=flags.initrace=flags.initgend=flags.initalign=ROLE_NONE;flags.pantheon=-1;strcpy(svp.plname,"Hero");strcpy(names,"Renamed");input[0]=0;memset(output,0xa5,sizeof output);output[0]=0;generic[0]=0;answer='a';memset(pick_n,0,sizeof pick_n);memset(pick_a,0,sizeof pick_a);memset(pick_b,0,sizeof pick_b);windowprocs.win_create_nhwindow=create_window;windowprocs.win_start_menu=start_window;windowprocs.win_end_menu=end_window;windowprocs.win_destroy_nhwindow=destroy_window;windowprocs.win_putstr=put_window;windowprocs.win_askname=ask_window;seed=s;nroll=rollindex=pickindex=entries=freed=0;tracebuf[0]=caller[0]=0;}
void probe_input(const char*s){strcpy(input,s);}void probe_output(const char*s){strcpy(output,s);}void probe_name(const char*s){strcpy(svp.plname,s);}void probe_generic(const char*s){strcpy(generic,s);sysopt.genericusers=generic;}void probe_newname(const char*s){strcpy(names,s);}
void probe_pick(int i,int n,int a,int b){pick_n[i]=n;pick_a[i]=a;pick_b[i]=b;}void probe_answer(int c){answer=c;}
void probe_field(int k,int v){switch(k){case 0:flags.initrole=v;break;case 1:flags.initrace=v;break;case 2:flags.initgend=v;break;case 3:flags.initalign=v;break;case 4:flags.pantheon=v;break;case 5:flags.female=v;break;case 6:flags.randomall=v;break;case 7:iflags.renameallowed=v;break;case 8:iflags.defer_plname=v;break;case 9:gp.plnamelen=v;break;case 10:mon.data=&mons[v];break;case 11:gr.rfilter.mask=v;break;case 12:program_state.in_role_selection=v;break;case 13:growth=(void*)1;break;}}
int probe_value(int k){switch(k){case 0:return flags.initrole;case 1:return flags.initrace;case 2:return flags.initgend;case 3:return flags.initalign;case 4:return flags.pantheon;case 5:return flags.female;case 6:return gr.rfilter.mask;case 7:return gr.role_post_attribs;case 8:return program_state.in_role_selection;case 9:return iflags.renameinprogress;case 10:return gp.plnamelen;case 11:return svq.quest_status.ldrgend;case 12:return svq.quest_status.nemgend;case 13:return svq.quest_status.godgend;case 14:return freed;case 15:return pickindex;default:return gr.rfilter.roles[k-16];}}
void*probe_pointer(int k,int i){switch(k){case 0:return input;case 1:return output;case 2:return svp.plname;case 3:return svp.pl_character;case 4:return &roles[i];case 5:return &races[i];case 6:return &genders[i];case 7:return &aligns[i];case 8:return &gu.urole;case 9:return &gu.urace;case 10:return &mons[i];default:return &gr;}}
const char*probe_trace(void){return tracebuf;}void*probe_rng_pointer(void){return rolls;}void probe_rng_length(int n){nroll=n;rollindex=0;}int probe_rng_count(void){return rollindex;}unsigned probe_rng_state(void){return seed;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
long probe_action(int op,int a,int b,int c,int d,int e,int f){const char*p=NULL;switch(op){case 0:return validrole(a);case 1:return randrole(a);case 2:return randrole_filtered();case 3:return str2role(input);case 4:return validrace(a,b);case 5:return randrace(a);case 6:return str2race(input);case 7:return validgend(a,b,c);case 8:return randgend(a,b);case 9:return str2gend(input);case 10:return validalign(a,b,c);case 11:return randalign(a,b);case 12:return str2align(input);case 13:return ok_role(a,b,c,d);case 14:return pick_role(a,b,c,d);case 15:return ok_race(a,b,c,d);case 16:return pick_race(a,b,c,d);case 17:return ok_gend(a,b,c,d);case 18:return pick_gend(a,b,c,d);case 19:return ok_align(a,b,c,d);case 20:return pick_align(a,b,c,d);case 21:rigid_role_checks();break;case 22:return setrolefilter(input);case 23:return gotrolefilter();case 24:p=rolefilterstring(output,a);break;case 25:clearrolefilter(a);break;case 26:p=promptsep(output,a);break;case 27:return role_gendercount(a);case 28:return race_alignmentcount(a);case 29:p=root_plselection_prompt(output,a,b,c,d,e);break;case 30:p=build_plselection_prompt(output,a,b,c,d,e);break;case 31:plnamesuffix();break;case 32:role_selection_prolog(a,b);break;case 33:role_menu_extra(a,b,c);break;case 34:role_init();break;case 35:p=Hello(a?&mon:NULL);break;case 36:p=Goodbye();break;case 37:{const struct Race*r=character_race(a);return r?r-races:-1;}case 38:genl_player_selection();break;case 39:return genl_player_setup(a);case 40:return reset_role_filtering();case 41:return maybe_skip_seps(a,b);case 42:return plsel_startmenu(a,b);case 43:setup_rolemenu(a,b,c,d,e);break;case 44:setup_racemenu(a,b,c,d,e);break;case 45:setup_gendmenu(a,b,c,d,e);break;case 46:setup_algnmenu(a,b,c,d,e);break;case 47:switch(a){case 0:return str2role(NULL);case 1:return str2race(NULL);case 2:return str2gend(NULL);default:return str2align(NULL);}case 48:p=root_plselection_prompt(NULL,a,b,c,d,e);break;}if(p){if((uintptr_t)p>=(uintptr_t)output&&(uintptr_t)p<(uintptr_t)(output+sizeof output))return p-output;strcpy(input,p);return -2;}return 0;}
