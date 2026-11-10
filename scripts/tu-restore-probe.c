/* Controlled external RESTORE boundaries. Actual original restoration code is
 * compiled unchanged in reference mode; actual typed records and native malloc
 * backing are shared with hybrid mode. Serializer inputs are scripted bytes,
 * not alternative reconstruction algorithms. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "../nethack-c/wasm/tu-restore-types.h"
#include <emscripten/stack.h>
#undef free
extern void free(void*);
__typeof__(flags) flags;
__typeof__(iflags) iflags;
__typeof__(nul_glyphinfo) nul_glyphinfo;
__typeof__(restoreinfo) restoreinfo;
__typeof__(uwep) uwep;
__typeof__(uchain) uchain;
__typeof__(uball) uball;
__typeof__(u) u;
__typeof__(ubirthday) ubirthday;
__typeof__(urealtime) urealtime;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(gb) gb;
__typeof__(gc) gc;
__typeof__(gd) gd;
__typeof__(ge) ge;
__typeof__(gf) gf;
__typeof__(gh) gh;
__typeof__(gi) gi;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(go) go;
__typeof__(gs) gs;
__typeof__(gu) gu;
__typeof__(gv) gv;
__typeof__(gy) gy;
__typeof__(svc) svc;
__typeof__(svd) svd;
__typeof__(svk) svk;
__typeof__(svl) svl;
__typeof__(svm) svm;
__typeof__(svn) svn;
__typeof__(svo) svo;
__typeof__(svp) svp;
__typeof__(svq) svq;
__typeof__(svr) svr;
__typeof__(svs) svs;
__typeof__(svu) svu;
__typeof__(svw) svw;
__typeof__(program_state) program_state;
__typeof__(cg) cg;
__typeof__(sysopt) sysopt;
__typeof__(windowprocs) windowprocs;
extern void*teleport_restore_global(int);extern void teleport_restore_write(int,void*,int,uint64_t);
static NHFILE file,created;static void*last_result;
static struct {void*p;size_t n;int live;} allocations[8192];static int na,nfree;
static char tracebuf[4194304],snapbuf[4194304],texts[32][1024];static int ti;
static struct {char tag[100];long value;int used;} input[16384];static int ninput,input_found;
static struct {int kind,index,used;} records[1024];static int nrecord;
static long opts[32];static unsigned nextid;static void*grown;static int grow_at,reenter_at,reentered,serialcount;
static struct obj *templates_obj;static struct monst *templates_mon;
static char saved_names[8][PL_NSIZ_PLUS];static int nsaved;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);int n=vsnprintf(tracebuf+ti,sizeof tracebuf-ti,fmt,ap);va_end(ap);if(n<0||ti+n>sizeof tracebuf-1)abort();ti+=n;}
static void*allocate(size_t n){if(na>=8192)abort();void*p=malloc(n?n:1);if(!p)abort();memset(p,0xa5,n);allocations[na++]=(typeof(allocations[0])){p,n,1};append("alloc:%zu;",n);return p;}
long *alloc(unsigned n){return allocate(n);}
void teleport_probe_free(void*p){if(!p)return;for(int i=0;i<na;i++)if(allocations[i].p==p&&allocations[i].live){append("free:%d;",i);allocations[i].live=0;nfree++;free(p);return;}abort();}
static uint64_t normalized(uint64_t v);
static void callback(void){serialcount++;if(grow_at&&serialcount==grow_at){grown=malloc(48*1024*1024);if(!grown)abort();append("growth;");}if(reenter_at&&serialcount==reenter_at&&!reentered){long t=17;reentered=1;moves_to_relative_time(&t);append("reentry:%ld;",t);}}
static long take(const char*tag,long otherwise){input_found=0;for(int i=0;i<ninput;i++)if(!input[i].used&&!strcmp(input[i].tag,tag)){input[i].used=1;input_found=1;return input[i].value;}return otherwise;}
void probe_feed(const char*tag,long value){if(ninput>=16384)abort();snprintf(input[ninput].tag,sizeof input[ninput].tag,"%s",tag);input[ninput].value=value;input[ninput++].used=0;}
void probe_record(int kind,int index){records[nrecord++]=(typeof(records[0])){kind,index,0};}
void probe_text(int index,const char*value){snprintf(texts[index],sizeof texts[index],"%s",value);}
static void *source(int kind,int index);
static size_t sizes(int kind);
static void bytes(void*p,size_t n){unsigned char*b=p;for(size_t i=0;i<n;){if(i+8<=n&&((uintptr_t)p+i)%8==0){uint64_t v;memcpy(&v,b+i,8);v=normalized(v);for(int j=0;j<8;j++)append("%02x",(unsigned)((v>>(8*j))&255));i+=8;}else append("%02x",b[i++]);}}
static void serial(int kind,NHFILE*f,void*p,const char*tag){void*from=0;for(int i=0;i<nrecord;i++)if(!records[i].used&&records[i].kind==kind){records[i].used=1;from=source(kind,records[i].index);break;}if(from)memcpy(p,from,sizes(kind));else memset(p,0,sizes(kind));append("read:%s:%zu:",tag,sizes(kind));bytes(p,sizes(kind));append(";");f->rcount+=sizes(kind);callback();}
void panic(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);fprintf(stderr,"unexpected panic:%s\n",b);abort();}
void impossible(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("impossible:%s;",b);}
void pline(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);iflags.last_msg=700;}
void You(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("You:%s;",b);}
boolean debugcore(const char*name,boolean wild){const char*p=strrchr(name,'/');append("debug:%s:%d;",p?p+1:name,wild);return opts[20];}
unsigned next_ident(void){append("nextid:%u;",nextid);return nextid++;}
uid_t getuid(void){return 0xfedcba98U;}
time_t getnow(void){return 9007199254740997LL;}
time_t time_from_yyyymmddhhmmss(char*s){append("time:%s;",s);return 9007199254740999LL;}
void useup(struct obj*o){append("useup:%u;",o->o_id);struct obj**p=&gi.invent;while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;teleport_probe_free(o);}
void place_object(struct obj*o,coordxy x,coordxy y){append("place:%u:%d:%d;",o->o_id,x,y);o->where=OBJ_FLOOR;o->nobj=fobj;fobj=o;o->ox=x;o->oy=y;o->nexthere=svl.level.objects[x][y];svl.level.objects[x][y]=o;}
void setworn(struct obj*o,long mask){append("worn:%u:%lx;",o?o->o_id:0,(unsigned long)mask);if(mask&W_BALL)uball=o;if(mask&W_CHAIN)uchain=o;}
void setuwep(struct obj*o){append("setuwep:%u;",o?o->o_id:0);uwep=o;}
void set_ustuck(struct monst*m){append("stuck:%u;",m?m->m_id:0);u.ustuck=m;}
void place_monster(struct monst*m,coordxy x,coordxy y){append("place_mon:%u:%d:%d;",m->m_id,x,y);svl.level.monsters[x][y]=m;}
NHFILE*create_levelfile(int lev,char*why){append("create_level:%d;",lev);return &created;}
NHFILE*get_freeing_nhfile(void){created.mode=FREEING;append("freefile;");return &created;}
void close_nhfile(NHFILE*f){append("close:%d;",f==&file?0:1);}
int fruitadd(char*name,struct fruit*f){append("fruitadd:%s;",name);return opts[2];}
char*xname(struct obj*o){append("xname:%u;",o->o_id);return "an object";}
static void clipwin(int x,int y){append("clip:%d:%d;",x,y);}
static winid createwin(int t){append("createwin:%d;",t);return 17;}
static void clearwin(winid w){append("clear:%d;",w);}static void displaywin(winid w,boolean b){append("display:%d:%d;",w,b);}static void destroywin(winid w){append("destroy:%d;",w);}static void waitwin(void){append("wait;");}
static void putwin(winid w,int a,const char*s){append("put:%d:%d:%s;",w,a,s);}static void history(const char*s,boolean b){append("history:%s:%d;",s?s:"(null)",b);}
static void startwin(winid w,unsigned long f){append("start:%d:%lu;",w,f);}static void endwin(winid w,const char*s){append("end:%d:%s;",w,s?s:"(null)");}
static void addwin(winid w,const glyph_info*g,const anything*a,char ch,char group,int attr,int color,const char*s,unsigned f){append("menu:%d:%d:%d:%d:%d:%s:%u;",w,a?a->a_int:0,ch,group,attr,s,f);}
static int selectwin(winid w,int how,menu_item**p){append("select:%d:%d;",w,how);if(opts[3]<=0){*p=0;return opts[3];}*p=allocate(sizeof**p);memset(*p,0,sizeof**p);(*p)->item.a_int=opts[4];return 1;}
char**get_saved_games(void){append("saved:%d;",nsaved);char**out=allocate((nsaved+1)*sizeof*out);for(int i=0;i<nsaved;i++){out[i]=allocate(PL_NSIZ_PLUS);memcpy(out[i],saved_names[i],PL_NSIZ_PLUS);}out[nsaved]=0;return out;}
void free_saved_games(char**v){append("free_saved;");if(v){for(int i=0;v[i];i++)teleport_probe_free(v[i]);teleport_probe_free(v);}}
const char*copyright_banner_line(int n){static const char*texts[]={"","A","B","C","D"};return texts[n];}
static struct monst records_0[8];
static struct permonst records_1[8];
static struct obj records_2[8];
static union vptrs records_3[8];
static struct oextra records_4[8];
static struct mextra records_5[8];
static struct egd records_6[8];
static struct epri records_7[8];
static struct eshk records_8[8];
static struct emin records_9[8];
static struct edog records_10[8];
static struct ebones records_11[8];
static struct dgn_topology records_12[8];
static struct d_level records_13[8];
static struct window_procs records_14[8];
static struct instance_globals_o records_15[8];
static struct fruit records_16[8];
static struct mi records_17[8];
static union any records_18[8];
static struct damage records_19[8];
static struct sinfo records_20[8];
static dlevel_t records_21[8];
static struct rm records_22[8];
static struct cemetery records_23[8];
static struct levelflags records_24[8];
static struct instance_globals_saved_s records_25[8];
static struct spell records_26[8];
static struct s_level records_27[8];
static struct instance_globals_saved_n records_28[8];
static struct instance_globals_c records_29[8];
static struct nh_file records_30[8];
static struct instance_globals_i records_31[8];
static struct teleport_restore_bucket records_32[8];
static __typeof__(((struct teleport_restore_bucket*)0)->map[0]) records_33[8];
static struct instance_globals_v records_34[8];
static struct instance_globals_u records_35[8];
static struct stairway records_36[8];
static struct context_info records_37[8];
static struct dig_info records_38[8];
static struct victual_info records_39[8];
static struct tin_info records_40[8];
static struct book_info records_41[8];
static struct warntype_info records_42[8];
static struct polearm_info records_43[8];
static struct instance_globals_n records_44[8];
static struct instance_globals_saved_u records_45[8];
static struct dest_area records_46[8];
static struct instance_globals_saved_d records_47[8];
static struct nhcoord records_48[8];
static struct trap records_49[8];
static struct instance_globals_m records_50[8];
static struct u_realtime records_51[8];
static struct instance_globals_f records_52[8];
static struct you records_53[8];
static struct align records_54[8];
static struct instance_globals_e records_55[8];
static struct instance_flags records_56[8];
static struct mkroom records_57[8];
static struct branch records_58[8];
static struct instance_globals_saved_r records_59[8];
static struct const_globals records_60[8];
static struct instance_globals_y records_61[8];
static struct instance_globals_saved_c records_62[8];
static struct instance_globals_d records_63[8];
static struct instance_globals_s records_64[8];
static struct sysopt_s records_65[8];
static struct flag records_66[8];
static struct instance_globals_b records_67[8];
static struct instance_globals_saved_q records_68[8];
static struct q_score records_69[8];
static struct instance_globals_saved_k records_70[8];
static struct kinfo records_71[8];
static struct instance_globals_saved_p records_72[8];
static struct restore_info records_73[8];
static struct instance_globals_saved_l records_74[8];
static struct instance_globals_saved_w records_75[8];
static struct instance_globals_saved_m records_76[8];
static struct mvitals records_77[8];
static struct instance_globals_h records_78[8];
static struct gamelog_line records_79[8];
static struct instance_globals_saved_o records_80[8];
static struct glyphinfo records_81[8];
static size_t sizes(int kind){switch(kind){
case 0:return sizeof(struct monst);
case 1:return sizeof(struct permonst);
case 2:return sizeof(struct obj);
case 3:return sizeof(union vptrs);
case 4:return sizeof(struct oextra);
case 5:return sizeof(struct mextra);
case 6:return sizeof(struct egd);
case 7:return sizeof(struct epri);
case 8:return sizeof(struct eshk);
case 9:return sizeof(struct emin);
case 10:return sizeof(struct edog);
case 11:return sizeof(struct ebones);
case 12:return sizeof(struct dgn_topology);
case 13:return sizeof(struct d_level);
case 14:return sizeof(struct window_procs);
case 15:return sizeof(struct instance_globals_o);
case 16:return sizeof(struct fruit);
case 17:return sizeof(struct mi);
case 18:return sizeof(union any);
case 19:return sizeof(struct damage);
case 20:return sizeof(struct sinfo);
case 21:return sizeof(dlevel_t);
case 22:return sizeof(struct rm);
case 23:return sizeof(struct cemetery);
case 24:return sizeof(struct levelflags);
case 25:return sizeof(struct instance_globals_saved_s);
case 26:return sizeof(struct spell);
case 27:return sizeof(struct s_level);
case 28:return sizeof(struct instance_globals_saved_n);
case 29:return sizeof(struct instance_globals_c);
case 30:return sizeof(struct nh_file);
case 31:return sizeof(struct instance_globals_i);
case 32:return sizeof(struct teleport_restore_bucket);
case 33:return sizeof(__typeof__(((struct teleport_restore_bucket*)0)->map[0]));
case 34:return sizeof(struct instance_globals_v);
case 35:return sizeof(struct instance_globals_u);
case 36:return sizeof(struct stairway);
case 37:return sizeof(struct context_info);
case 38:return sizeof(struct dig_info);
case 39:return sizeof(struct victual_info);
case 40:return sizeof(struct tin_info);
case 41:return sizeof(struct book_info);
case 42:return sizeof(struct warntype_info);
case 43:return sizeof(struct polearm_info);
case 44:return sizeof(struct instance_globals_n);
case 45:return sizeof(struct instance_globals_saved_u);
case 46:return sizeof(struct dest_area);
case 47:return sizeof(struct instance_globals_saved_d);
case 48:return sizeof(struct nhcoord);
case 49:return sizeof(struct trap);
case 50:return sizeof(struct instance_globals_m);
case 51:return sizeof(struct u_realtime);
case 52:return sizeof(struct instance_globals_f);
case 53:return sizeof(struct you);
case 54:return sizeof(struct align);
case 55:return sizeof(struct instance_globals_e);
case 56:return sizeof(struct instance_flags);
case 57:return sizeof(struct mkroom);
case 58:return sizeof(struct branch);
case 59:return sizeof(struct instance_globals_saved_r);
case 60:return sizeof(struct const_globals);
case 61:return sizeof(struct instance_globals_y);
case 62:return sizeof(struct instance_globals_saved_c);
case 63:return sizeof(struct instance_globals_d);
case 64:return sizeof(struct instance_globals_s);
case 65:return sizeof(struct sysopt_s);
case 66:return sizeof(struct flag);
case 67:return sizeof(struct instance_globals_b);
case 68:return sizeof(struct instance_globals_saved_q);
case 69:return sizeof(struct q_score);
case 70:return sizeof(struct instance_globals_saved_k);
case 71:return sizeof(struct kinfo);
case 72:return sizeof(struct instance_globals_saved_p);
case 73:return sizeof(struct restore_info);
case 74:return sizeof(struct instance_globals_saved_l);
case 75:return sizeof(struct instance_globals_saved_w);
case 76:return sizeof(struct instance_globals_saved_m);
case 77:return sizeof(struct mvitals);
case 78:return sizeof(struct instance_globals_h);
case 79:return sizeof(struct gamelog_line);
case 80:return sizeof(struct instance_globals_saved_o);
case 81:return sizeof(struct glyphinfo);
default:abort();}}
static void*source(int kind,int index){switch(kind){
case 0:return &records_0[index];
case 1:return &records_1[index];
case 2:return &records_2[index];
case 3:return &records_3[index];
case 4:return &records_4[index];
case 5:return &records_5[index];
case 6:return &records_6[index];
case 7:return &records_7[index];
case 8:return &records_8[index];
case 9:return &records_9[index];
case 10:return &records_10[index];
case 11:return &records_11[index];
case 12:return &records_12[index];
case 13:return &records_13[index];
case 14:return &records_14[index];
case 15:return &records_15[index];
case 16:return &records_16[index];
case 17:return &records_17[index];
case 18:return &records_18[index];
case 19:return &records_19[index];
case 20:return &records_20[index];
case 21:return &records_21[index];
case 22:return &records_22[index];
case 23:return &records_23[index];
case 24:return &records_24[index];
case 25:return &records_25[index];
case 26:return &records_26[index];
case 27:return &records_27[index];
case 28:return &records_28[index];
case 29:return &records_29[index];
case 30:return &records_30[index];
case 31:return &records_31[index];
case 32:return &records_32[index];
case 33:return &records_33[index];
case 34:return &records_34[index];
case 35:return &records_35[index];
case 36:return &records_36[index];
case 37:return &records_37[index];
case 38:return &records_38[index];
case 39:return &records_39[index];
case 40:return &records_40[index];
case 41:return &records_41[index];
case 42:return &records_42[index];
case 43:return &records_43[index];
case 44:return &records_44[index];
case 45:return &records_45[index];
case 46:return &records_46[index];
case 47:return &records_47[index];
case 48:return &records_48[index];
case 49:return &records_49[index];
case 50:return &records_50[index];
case 51:return &records_51[index];
case 52:return &records_52[index];
case 53:return &records_53[index];
case 54:return &records_54[index];
case 55:return &records_55[index];
case 56:return &records_56[index];
case 57:return &records_57[index];
case 58:return &records_58[index];
case 59:return &records_59[index];
case 60:return &records_60[index];
case 61:return &records_61[index];
case 62:return &records_62[index];
case 63:return &records_63[index];
case 64:return &records_64[index];
case 65:return &records_65[index];
case 66:return &records_66[index];
case 67:return &records_67[index];
case 68:return &records_68[index];
case 69:return &records_69[index];
case 70:return &records_70[index];
case 71:return &records_71[index];
case 72:return &records_72[index];
case 73:return &records_73[index];
case 74:return &records_74[index];
case 75:return &records_75[index];
case 76:return &records_76[index];
case 77:return &records_77[index];
case 78:return &records_78[index];
case 79:return &records_79[index];
case 80:return &records_80[index];
case 81:return &records_81[index];
default:abort();}}
struct oextra*newoextra(void){struct oextra*p=allocate(sizeof*p);memset(p,0,sizeof*p);return p;}
struct mextra*newmextra(void){struct mextra*p=allocate(sizeof*p);memset(p,0,sizeof*p);return p;}
void newegd(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->egd=allocate(sizeof*m->mextra->egd);memset(m->mextra->egd,0,sizeof*m->mextra->egd);}
void newepri(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->epri=allocate(sizeof*m->mextra->epri);memset(m->mextra->epri,0,sizeof*m->mextra->epri);}
void neweshk(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->eshk=allocate(sizeof*m->mextra->eshk);memset(m->mextra->eshk,0,sizeof*m->mextra->eshk);}
void newemin(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->emin=allocate(sizeof*m->mextra->emin);memset(m->mextra->emin,0,sizeof*m->mextra->emin);}
void newedog(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->edog=allocate(sizeof*m->mextra->edog);memset(m->mextra->edog,0,sizeof*m->mextra->edog);}
void newebones(struct monst*m){if(!m->mextra)m->mextra=newmextra();m->mextra->ebones=allocate(sizeof*m->mextra->ebones);memset(m->mextra->ebones,0,sizeof*m->mextra->ebones);}
void new_oname(struct obj*o,int n){if(!o->oextra)o->oextra=newoextra();o->oextra->oname=allocate(n);}void new_mgivenname(struct monst*m,int n){if(!m->mextra)m->mextra=newmextra();m->mextra->mgivenname=allocate(n);}void newomid(struct obj*o){if(!o->oextra)o->oextra=newoextra();}void newomonst(struct obj*o){if(!o->oextra)o->oextra=newoextra();o->oextra->omonst=allocate(sizeof(struct monst));}void new_omailcmd(struct obj*o,const char*s){o->oextra->omailcmd=allocate(strlen(s)+1);strcpy(o->oextra->omailcmd,s);}void free_omid(struct obj*o){o->oextra->omid=0;}
branch * (Is_branchlev)(d_level * a0){append("dep:Is_branchlev;");append("level:a0:");bytes(a0,sizeof*a0);append(";");return opts[6]?source(58,0):0;}
void (sfi_cemetery)(NHFILE * a0,struct cemetery * a1,const char * a2){serial(23,a0,a1,a2);}
void (sfi_char)(NHFILE * a0,char * a1,const char * a2,int a3){long slot=take(a2,0);memcpy(a1,texts[slot],a3);append("chars:%s:%d:",a2,a3);bytes(a1,a3);append(";");a0->rcount+=a3;callback();}
void (sfi_context_info)(NHFILE * a0,struct context_info * a1,const char * a2){serial(37,a0,a1,a2);}
void (sfi_damage)(NHFILE * a0,struct damage * a1,const char * a2){serial(19,a0,a1,a2);}
void (sfi_dest_area)(NHFILE * a0,struct dest_area * a1,const char * a2){serial(46,a0,a1,a2);}
void (sfi_ebones)(NHFILE * a0,struct ebones * a1,const char * a2){serial(11,a0,a1,a2);}
void (sfi_edog)(NHFILE * a0,struct edog * a1,const char * a2){serial(10,a0,a1,a2);}
void (sfi_egd)(NHFILE * a0,struct egd * a1,const char * a2){serial(6,a0,a1,a2);}
void (sfi_emin)(NHFILE * a0,struct emin * a1,const char * a2){serial(9,a0,a1,a2);}
void (sfi_epri)(NHFILE * a0,struct epri * a1,const char * a2){serial(7,a0,a1,a2);}
void (sfi_eshk)(NHFILE * a0,struct eshk * a1,const char * a2){serial(8,a0,a1,a2);}
void (sfi_flag)(NHFILE * a0,struct flag * a1,const char * a2){serial(66,a0,a1,a2);}
void (sfi_fruit)(NHFILE * a0,struct fruit * a1,const char * a2){serial(16,a0,a1,a2);}
void (sfi_gamelog_line)(NHFILE * a0,struct gamelog_line * a1,const char * a2){serial(79,a0,a1,a2);}
void (sfi_int)(NHFILE * a0,int * a1,const char * a2){long fallback=(!strcmp(a2,"obj-obj_length")||!strcmp(a2,"monst-monst_length")||!strcmp(a2,"stairs-staircount")||!strcmp(a2,"gamelog-length")||!strcmp(a2,"msghistory-length"))?-1:0;if(!strcmp(a2,"plname-size"))fallback=PL_NSIZ_PLUS;if(!strcmp(a2,"gamestate-uid"))fallback=getuid();*a1=take(a2,fallback);append("scalar:%s:%ld;",a2,(long)*a1);a0->rcount+=sizeof*a1;if(!strcmp(a2,"gamestate-level_number"))a0->eof=!input_found;callback();}
void (sfi_int32)(NHFILE * a0,int32 * a1,const char * a2){long fallback=0;if(!strcmp(a2,"plname-size"))fallback=PL_NSIZ_PLUS;if(!strcmp(a2,"gamestate-uid"))fallback=getuid();*a1=take(a2,fallback);append("scalar:%s:%ld;",a2,(long)*a1);a0->rcount+=sizeof*a1;if(!strcmp(a2,"gamestate-level_number"))a0->eof=!input_found;callback();}
void (sfi_levelflags)(NHFILE * a0,struct levelflags * a1,const char * a2){serial(24,a0,a1,a2);}
void (sfi_long)(NHFILE * a0,long * a1,const char * a2){long fallback=0;if(!strcmp(a2,"plname-size"))fallback=PL_NSIZ_PLUS;if(!strcmp(a2,"gamestate-uid"))fallback=getuid();*a1=take(a2,fallback);append("scalar:%s:%ld;",a2,(long)*a1);a0->rcount+=sizeof*a1;if(!strcmp(a2,"gamestate-level_number"))a0->eof=!input_found;callback();}
void (sfi_monst)(NHFILE * a0,struct monst * a1,const char * a2){serial(0,a0,a1,a2);}
void (sfi_mvitals)(NHFILE * a0,struct mvitals * a1,const char * a2){serial(77,a0,a1,a2);}
void (sfi_nhcoord)(NHFILE * a0,struct nhcoord * a1,const char * a2){serial(48,a0,a1,a2);}
void (sfi_obj)(NHFILE * a0,struct obj * a1,const char * a2){serial(2,a0,a1,a2);}
void (sfi_q_score)(NHFILE * a0,struct q_score * a1,const char * a2){serial(69,a0,a1,a2);}
void (sfi_rm)(NHFILE * a0,struct rm * a1,const char * a2){serial(22,a0,a1,a2);}
void (sfi_s_level)(NHFILE * a0,struct s_level * a1,const char * a2){serial(27,a0,a1,a2);}
void (sfi_schar)(NHFILE * a0,schar * a1,const char * a2){long fallback=0;if(!strcmp(a2,"plname-size"))fallback=PL_NSIZ_PLUS;if(!strcmp(a2,"gamestate-uid"))fallback=getuid();*a1=take(a2,fallback);append("scalar:%s:%ld;",a2,(long)*a1);a0->rcount+=sizeof*a1;if(!strcmp(a2,"gamestate-level_number"))a0->eof=!input_found;callback();}
void (sfi_spell)(NHFILE * a0,struct spell * a1,const char * a2){serial(26,a0,a1,a2);}
void (sfi_stairway)(NHFILE * a0,struct stairway * a1,const char * a2){serial(36,a0,a1,a2);}
void (sfi_trap)(NHFILE * a0,struct trap * a1,const char * a2){serial(49,a0,a1,a2);}
void (sfi_ulong)(NHFILE * a0,ulong * a1,const char * a2){long fallback=0;if(!strcmp(a2,"plname-size"))fallback=PL_NSIZ_PLUS;if(!strcmp(a2,"gamestate-uid"))fallback=getuid();*a1=take(a2,fallback);append("scalar:%s:%ld;",a2,(long)*a1);a0->rcount+=sizeof*a1;if(!strcmp(a2,"gamestate-level_number"))a0->eof=!input_found;callback();}
void (sfi_unsigned)(NHFILE * a0,unsigned int * a1,const char * a2){long fallback=0;if(!strcmp(a2,"plname-size"))fallback=PL_NSIZ_PLUS;if(!strcmp(a2,"gamestate-uid"))fallback=getuid();*a1=take(a2,fallback);append("scalar:%s:%ld;",a2,(long)*a1);a0->rcount+=sizeof*a1;if(!strcmp(a2,"gamestate-level_number"))a0->eof=!input_found;callback();}
void (sfi_xint8)(NHFILE * a0,xint8 * a1,const char * a2){long fallback=0;if(!strcmp(a2,"plname-size"))fallback=PL_NSIZ_PLUS;if(!strcmp(a2,"gamestate-uid"))fallback=getuid();*a1=take(a2,fallback);append("scalar:%s:%ld;",a2,(long)*a1);a0->rcount+=sizeof*a1;if(!strcmp(a2,"gamestate-level_number"))a0->eof=!input_found;callback();}
void (sfi_you)(NHFILE * a0,struct you * a1,const char * a2){serial(53,a0,a1,a2);}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){addwin(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
void (add_menu_str)(winid a0,const char * a1){append("menu_str:%d:%s;",a0,a1);}
void (adj_erinys)(unsigned int a0){append("dep:adj_erinys;");append("arg:a0:%llu;",(unsigned long long)a0);}
void (assign_graphics)(int a0){append("dep:assign_graphics;");append("arg:a0:%lld;",(long long)a0);}
void (bufon)(int a0){append("dep:bufon;");append("arg:a0:%lld;",(long long)a0);}
void (check_special_room)(boolean a0){append("dep:check_special_room;");append("arg:a0:%lld;",(long long)a0);}
int (delete_savefile)(void){append("dep:delete_savefile;");return opts[5];}
void (deltrap)(struct trap * a0){append("dep:deltrap;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (docrt)(void){append("dep:docrt;");}
void (done)(int a0){append("dep:done;");append("arg:a0:%lld;",(long long)a0);}
void (gamelog_add)(long a0,long a1,const char * a2){append("dep:gamelog_add;");append("arg:a0:%lld;",(long long)a0);append("arg:a1:%lld;",(long long)a1);append("arg:a2:%s;",a2?a2:"(null)");}
void (hide_monst)(struct monst * a0){append("dep:hide_monst;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
signed char (hideunder)(struct monst * a0){append("dep:hideunder;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));return opts[5];}
void (init_oclass_probs)(void){append("dep:init_oclass_probs;");}
short (ledger_no)(d_level * a0){append("dep:ledger_no;");append("level:a0:");bytes(a0,sizeof*a0);append(";");return opts[5];}
void (load_exclusions)(NHFILE * a0){append("dep:load_exclusions;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (max_rank_sz)(void){append("dep:max_rank_sz;");}
void (mazexy)(coord * a0){append("dep:mazexy;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (mon_catchup_elapsed_time)(struct monst * a0,long a1){append("dep:mon_catchup_elapsed_time;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%lld;",(long long)a1);}
signed char (peace_minded)(struct permonst * a0){append("dep:peace_minded;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));return opts[5];}
void (place_wsegs)(struct monst * a0,struct monst * a1){append("dep:place_wsegs;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%llx;",(unsigned long long)normalized((uintptr_t)a1));}
signed char (propagate)(int a0,boolean a1,boolean a2){append("dep:propagate;");append("arg:a0:%lld;",(long long)a0);append("arg:a1:%lld;",(long long)a1);append("arg:a2:%lld;",(long long)a2);return opts[5];}
void (reglyph_darkroom)(void){append("dep:reglyph_darkroom;");}
void (relink_light_sources)(boolean a0){append("dep:relink_light_sources;");append("arg:a0:%lld;",(long long)a0);}
void (relink_timers)(boolean a0){append("dep:relink_timers;");append("arg:a0:%lld;",(long long)a0);}
void (reset_glyphmap)(enum glyphmap_change_triggers a0){append("dep:reset_glyphmap;");append("arg:a0:%lld;",(long long)a0);}
void (rest_engravings)(NHFILE * a0){append("dep:rest_engravings;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (rest_regions)(NHFILE * a0){append("dep:rest_regions;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (rest_rooms)(NHFILE * a0){append("dep:rest_rooms;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (rest_track)(NHFILE * a0){append("dep:rest_track;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (rest_worm)(NHFILE * a0){append("dep:rest_worm;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restnames)(NHFILE * a0){append("dep:restnames;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_artifacts)(NHFILE * a0){append("dep:restore_artifacts;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_cham)(struct monst * a0){append("dep:restore_cham;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_dungeon)(NHFILE * a0){append("dep:restore_dungeon;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_killers)(NHFILE * a0){append("dep:restore_killers;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_light_sources)(NHFILE * a0){append("dep:restore_light_sources;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_luadata)(NHFILE * a0){append("dep:restore_luadata;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_oracles)(NHFILE * a0){append("dep:restore_oracles;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restore_timers)(NHFILE * a0,int a1,long a2){append("dep:restore_timers;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%lld;",(long long)a1);append("arg:a2:%lld;",(long long)a2);}
void (restore_waterlevel)(NHFILE * a0){append("dep:restore_waterlevel;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (restpriest)(struct monst * a0,boolean a1){append("dep:restpriest;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%lld;",(long long)a1);}
void (restshk)(struct monst * a0,boolean a1){append("dep:restshk;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%lld;",(long long)a1);}
void (rewind_nhfile)(NHFILE * a0){append("dep:rewind_nhfile;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));a0->eof=0;}
void (role_init)(void){append("dep:role_init;");}
void (run_timers)(void){append("dep:run_timers;");}
void (savelev)(NHFILE * a0,xint8 a1){append("dep:savelev;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%lld;",(long long)a1);}
void (savestateinlock)(void){append("dep:savestateinlock;");}
int (select_menu)(winid a0,int a1,menu_item ** a2){return selectwin(a0,a1,a2);}
void (set_malign)(struct monst * a0){append("dep:set_malign;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));}
void (set_playmode)(void){append("dep:set_playmode;");}
void (set_residency)(struct monst * a0,boolean a1){append("dep:set_residency;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%lld;",(long long)a1);}
void (set_uasmon)(void){append("dep:set_uasmon;");}
void (stairway_add)(coordxy a0,coordxy a1,boolean a2,boolean a3,d_level * a4){append("dep:stairway_add;");append("arg:a0:%lld;",(long long)a0);append("arg:a1:%lld;",(long long)a1);append("arg:a2:%lld;",(long long)a2);append("arg:a3:%lld;",(long long)a3);append("level:a4:");bytes(a4,sizeof*a4);append(";");if(opts[7]){stairway*p=source(36,7);memset(p,0,sizeof*p);p->sx=a0;p->sy=a1;p->up=a2;p->isladder=a3;p->tolev=*a4;gs.stairs=p;}}
stairway * (stairway_at)(coordxy a0,coordxy a1){append("dep:stairway_at;");append("arg:a0:%lld;",(long long)a0);append("arg:a1:%lld;",(long long)a1);return opts[7]?source(36,7):0;}
void (stairway_free_all)(void){append("dep:stairway_free_all;");}
int (validate)(NHFILE * a0,const char * a1,boolean a2){append("dep:validate;");append("arg:a0:%llx;",(unsigned long long)normalized((uintptr_t)a0));append("arg:a1:%s;",a1?a1:"(null)");append("arg:a2:%lld;",(long long)a2);return opts[5];}
void (vision_reset)(void){append("dep:vision_reset;");}
void (welcome)(boolean a0){append("dep:welcome;");append("arg:a0:%lld;",(long long)a0);}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}void assign_level(d_level*a,d_level*b){*a=*b;}int (rnd)(int n){append("rng:rnd:%d;",n);return 1;}boolean rng_log_enabled(void){return opts[21];}void rng_log_set_caller(const char*f,int n,const char*fn){const char*p=strrchr(f,'/');append("caller:%s:%d:%s;",p?p+1:f,n,fn);}
#ifdef TELEPORT_REFERENCE_TU
#define free teleport_probe_free
#include "../.cache/wasm64-build/tree/src/restore.c"
#undef free
#define TELEPORT_RESTORE_REFERENCE_LAYOUT
_Static_assert(sizeof(struct bucket)==sizeof(struct teleport_restore_bucket),"bucket sizeof");
_Static_assert(offsetof(struct bucket,next)==offsetof(struct teleport_restore_bucket,next),"bucket next offset");
_Static_assert(offsetof(struct bucket,map)==offsetof(struct teleport_restore_bucket,map),"bucket map offset");
#else
extern void teleport_restore_test_find_lev_obj();
#define find_lev_obj teleport_restore_test_find_lev_obj
extern void inven_inuse(boolean quietly);
extern void teleport_restore_test_restlevchn(NHFILE * nhfp);
#define restlevchn teleport_restore_test_restlevchn
extern void teleport_restore_test_restdamage(NHFILE * nhfp);
#define restdamage teleport_restore_test_restdamage
extern void teleport_restore_test_restobj(NHFILE * nhfp,struct obj * otmp);
#define restobj teleport_restore_test_restobj
extern struct obj * teleport_restore_test_restobjchn(NHFILE * nhfp,boolean frozen);
#define restobjchn teleport_restore_test_restobjchn
extern void teleport_restore_test_restmon(NHFILE * nhfp,struct monst * mtmp);
#define restmon teleport_restore_test_restmon
extern struct monst * teleport_restore_test_restmonchn(NHFILE * nhfp);
#define restmonchn teleport_restore_test_restmonchn
extern struct fruit * teleport_restore_test_loadfruitchn(NHFILE * nhfp);
#define loadfruitchn teleport_restore_test_loadfruitchn
extern void teleport_restore_test_freefruitchn(struct fruit * flist);
#define freefruitchn teleport_restore_test_freefruitchn
extern void teleport_restore_test_ghostfruit(struct obj * otmp);
#define ghostfruit teleport_restore_test_ghostfruit
extern boolean teleport_restore_test_restgamestate(NHFILE * nhfp);
#define restgamestate teleport_restore_test_restgamestate
extern void teleport_restore_test_restlevelstate();
#define restlevelstate teleport_restore_test_restlevelstate
extern int teleport_restore_test_restlevelfile(xint8 ltmp);
#define restlevelfile teleport_restore_test_restlevelfile
extern int dorecover(NHFILE * nhfp);
extern void teleport_restore_test_rest_stairs(NHFILE * nhfp);
#define rest_stairs teleport_restore_test_rest_stairs
extern void restcemetery(NHFILE * nhfp,struct cemetery ** cemeteryaddr);
extern void teleport_restore_test_rest_levl(NHFILE * nhfp);
#define rest_levl teleport_restore_test_rest_levl
extern void trickery(char * reason);
extern void getlev(NHFILE * nhfp,int pid,xint8 lev);
extern void rest_adjust_levelflags();
extern void moves_to_relative_time(long * timestamp);
extern void relative_time_to_moves(long * timestamp);
extern void get_plname_from_file(NHFILE * nhfp,char * outbuf,boolean name_only);
extern void teleport_restore_test_rest_bubbles(NHFILE * nhfp);
#define rest_bubbles teleport_restore_test_rest_bubbles
extern void teleport_restore_test_restore_gamelog(NHFILE * nhfp);
#define restore_gamelog teleport_restore_test_restore_gamelog
extern void teleport_restore_test_restore_msghistory(NHFILE * nhfp);
#define restore_msghistory teleport_restore_test_restore_msghistory
extern void teleport_restore_test_clear_id_mapping();
#define clear_id_mapping teleport_restore_test_clear_id_mapping
extern void teleport_restore_test_add_id_mapping(unsigned int gid,unsigned int nid);
#define add_id_mapping teleport_restore_test_add_id_mapping
extern boolean lookup_id_mapping(unsigned int gid,unsigned int * nidp);
extern void teleport_restore_test_reset_oattached_mids(boolean ghostly);
#define reset_oattached_mids teleport_restore_test_reset_oattached_mids
extern int restore_menu(winid bannerwin);
#endif
#include "tu-restore-layout.h"
static uint64_t normalized(uint64_t v){if(v>=(uintptr_t)&file&&v<(uintptr_t)&file+sizeof file)return ((uint64_t)500<<48)+(v-(uintptr_t)&file);if(v>=(uintptr_t)&created&&v<(uintptr_t)&created+sizeof created)return ((uint64_t)501<<48)+(v-(uintptr_t)&created);for(int i=0;i<na;i++)if(allocations[i].live&&v>=(uintptr_t)allocations[i].p&&v<(uintptr_t)allocations[i].p+allocations[i].n)return ((uint64_t)(i+1)<<48)+(v-(uintptr_t)allocations[i].p);
if(v>=(uintptr_t)records_0&&v<(uintptr_t)records_0+sizeof records_0)return ((uint64_t)100<<48)+(v-(uintptr_t)records_0);
if(v>=(uintptr_t)records_1&&v<(uintptr_t)records_1+sizeof records_1)return ((uint64_t)101<<48)+(v-(uintptr_t)records_1);
if(v>=(uintptr_t)records_2&&v<(uintptr_t)records_2+sizeof records_2)return ((uint64_t)102<<48)+(v-(uintptr_t)records_2);
if(v>=(uintptr_t)records_3&&v<(uintptr_t)records_3+sizeof records_3)return ((uint64_t)103<<48)+(v-(uintptr_t)records_3);
if(v>=(uintptr_t)records_4&&v<(uintptr_t)records_4+sizeof records_4)return ((uint64_t)104<<48)+(v-(uintptr_t)records_4);
if(v>=(uintptr_t)records_5&&v<(uintptr_t)records_5+sizeof records_5)return ((uint64_t)105<<48)+(v-(uintptr_t)records_5);
if(v>=(uintptr_t)records_6&&v<(uintptr_t)records_6+sizeof records_6)return ((uint64_t)106<<48)+(v-(uintptr_t)records_6);
if(v>=(uintptr_t)records_7&&v<(uintptr_t)records_7+sizeof records_7)return ((uint64_t)107<<48)+(v-(uintptr_t)records_7);
if(v>=(uintptr_t)records_8&&v<(uintptr_t)records_8+sizeof records_8)return ((uint64_t)108<<48)+(v-(uintptr_t)records_8);
if(v>=(uintptr_t)records_9&&v<(uintptr_t)records_9+sizeof records_9)return ((uint64_t)109<<48)+(v-(uintptr_t)records_9);
if(v>=(uintptr_t)records_10&&v<(uintptr_t)records_10+sizeof records_10)return ((uint64_t)110<<48)+(v-(uintptr_t)records_10);
if(v>=(uintptr_t)records_11&&v<(uintptr_t)records_11+sizeof records_11)return ((uint64_t)111<<48)+(v-(uintptr_t)records_11);
if(v>=(uintptr_t)records_12&&v<(uintptr_t)records_12+sizeof records_12)return ((uint64_t)112<<48)+(v-(uintptr_t)records_12);
if(v>=(uintptr_t)records_13&&v<(uintptr_t)records_13+sizeof records_13)return ((uint64_t)113<<48)+(v-(uintptr_t)records_13);
if(v>=(uintptr_t)records_14&&v<(uintptr_t)records_14+sizeof records_14)return ((uint64_t)114<<48)+(v-(uintptr_t)records_14);
if(v>=(uintptr_t)records_15&&v<(uintptr_t)records_15+sizeof records_15)return ((uint64_t)115<<48)+(v-(uintptr_t)records_15);
if(v>=(uintptr_t)records_16&&v<(uintptr_t)records_16+sizeof records_16)return ((uint64_t)116<<48)+(v-(uintptr_t)records_16);
if(v>=(uintptr_t)records_17&&v<(uintptr_t)records_17+sizeof records_17)return ((uint64_t)117<<48)+(v-(uintptr_t)records_17);
if(v>=(uintptr_t)records_18&&v<(uintptr_t)records_18+sizeof records_18)return ((uint64_t)118<<48)+(v-(uintptr_t)records_18);
if(v>=(uintptr_t)records_19&&v<(uintptr_t)records_19+sizeof records_19)return ((uint64_t)119<<48)+(v-(uintptr_t)records_19);
if(v>=(uintptr_t)records_20&&v<(uintptr_t)records_20+sizeof records_20)return ((uint64_t)120<<48)+(v-(uintptr_t)records_20);
if(v>=(uintptr_t)records_21&&v<(uintptr_t)records_21+sizeof records_21)return ((uint64_t)121<<48)+(v-(uintptr_t)records_21);
if(v>=(uintptr_t)records_22&&v<(uintptr_t)records_22+sizeof records_22)return ((uint64_t)122<<48)+(v-(uintptr_t)records_22);
if(v>=(uintptr_t)records_23&&v<(uintptr_t)records_23+sizeof records_23)return ((uint64_t)123<<48)+(v-(uintptr_t)records_23);
if(v>=(uintptr_t)records_24&&v<(uintptr_t)records_24+sizeof records_24)return ((uint64_t)124<<48)+(v-(uintptr_t)records_24);
if(v>=(uintptr_t)records_25&&v<(uintptr_t)records_25+sizeof records_25)return ((uint64_t)125<<48)+(v-(uintptr_t)records_25);
if(v>=(uintptr_t)records_26&&v<(uintptr_t)records_26+sizeof records_26)return ((uint64_t)126<<48)+(v-(uintptr_t)records_26);
if(v>=(uintptr_t)records_27&&v<(uintptr_t)records_27+sizeof records_27)return ((uint64_t)127<<48)+(v-(uintptr_t)records_27);
if(v>=(uintptr_t)records_28&&v<(uintptr_t)records_28+sizeof records_28)return ((uint64_t)128<<48)+(v-(uintptr_t)records_28);
if(v>=(uintptr_t)records_29&&v<(uintptr_t)records_29+sizeof records_29)return ((uint64_t)129<<48)+(v-(uintptr_t)records_29);
if(v>=(uintptr_t)records_30&&v<(uintptr_t)records_30+sizeof records_30)return ((uint64_t)130<<48)+(v-(uintptr_t)records_30);
if(v>=(uintptr_t)records_31&&v<(uintptr_t)records_31+sizeof records_31)return ((uint64_t)131<<48)+(v-(uintptr_t)records_31);
if(v>=(uintptr_t)records_32&&v<(uintptr_t)records_32+sizeof records_32)return ((uint64_t)132<<48)+(v-(uintptr_t)records_32);
if(v>=(uintptr_t)records_33&&v<(uintptr_t)records_33+sizeof records_33)return ((uint64_t)133<<48)+(v-(uintptr_t)records_33);
if(v>=(uintptr_t)records_34&&v<(uintptr_t)records_34+sizeof records_34)return ((uint64_t)134<<48)+(v-(uintptr_t)records_34);
if(v>=(uintptr_t)records_35&&v<(uintptr_t)records_35+sizeof records_35)return ((uint64_t)135<<48)+(v-(uintptr_t)records_35);
if(v>=(uintptr_t)records_36&&v<(uintptr_t)records_36+sizeof records_36)return ((uint64_t)136<<48)+(v-(uintptr_t)records_36);
if(v>=(uintptr_t)records_37&&v<(uintptr_t)records_37+sizeof records_37)return ((uint64_t)137<<48)+(v-(uintptr_t)records_37);
if(v>=(uintptr_t)records_38&&v<(uintptr_t)records_38+sizeof records_38)return ((uint64_t)138<<48)+(v-(uintptr_t)records_38);
if(v>=(uintptr_t)records_39&&v<(uintptr_t)records_39+sizeof records_39)return ((uint64_t)139<<48)+(v-(uintptr_t)records_39);
if(v>=(uintptr_t)records_40&&v<(uintptr_t)records_40+sizeof records_40)return ((uint64_t)140<<48)+(v-(uintptr_t)records_40);
if(v>=(uintptr_t)records_41&&v<(uintptr_t)records_41+sizeof records_41)return ((uint64_t)141<<48)+(v-(uintptr_t)records_41);
if(v>=(uintptr_t)records_42&&v<(uintptr_t)records_42+sizeof records_42)return ((uint64_t)142<<48)+(v-(uintptr_t)records_42);
if(v>=(uintptr_t)records_43&&v<(uintptr_t)records_43+sizeof records_43)return ((uint64_t)143<<48)+(v-(uintptr_t)records_43);
if(v>=(uintptr_t)records_44&&v<(uintptr_t)records_44+sizeof records_44)return ((uint64_t)144<<48)+(v-(uintptr_t)records_44);
if(v>=(uintptr_t)records_45&&v<(uintptr_t)records_45+sizeof records_45)return ((uint64_t)145<<48)+(v-(uintptr_t)records_45);
if(v>=(uintptr_t)records_46&&v<(uintptr_t)records_46+sizeof records_46)return ((uint64_t)146<<48)+(v-(uintptr_t)records_46);
if(v>=(uintptr_t)records_47&&v<(uintptr_t)records_47+sizeof records_47)return ((uint64_t)147<<48)+(v-(uintptr_t)records_47);
if(v>=(uintptr_t)records_48&&v<(uintptr_t)records_48+sizeof records_48)return ((uint64_t)148<<48)+(v-(uintptr_t)records_48);
if(v>=(uintptr_t)records_49&&v<(uintptr_t)records_49+sizeof records_49)return ((uint64_t)149<<48)+(v-(uintptr_t)records_49);
if(v>=(uintptr_t)records_50&&v<(uintptr_t)records_50+sizeof records_50)return ((uint64_t)150<<48)+(v-(uintptr_t)records_50);
if(v>=(uintptr_t)records_51&&v<(uintptr_t)records_51+sizeof records_51)return ((uint64_t)151<<48)+(v-(uintptr_t)records_51);
if(v>=(uintptr_t)records_52&&v<(uintptr_t)records_52+sizeof records_52)return ((uint64_t)152<<48)+(v-(uintptr_t)records_52);
if(v>=(uintptr_t)records_53&&v<(uintptr_t)records_53+sizeof records_53)return ((uint64_t)153<<48)+(v-(uintptr_t)records_53);
if(v>=(uintptr_t)records_54&&v<(uintptr_t)records_54+sizeof records_54)return ((uint64_t)154<<48)+(v-(uintptr_t)records_54);
if(v>=(uintptr_t)records_55&&v<(uintptr_t)records_55+sizeof records_55)return ((uint64_t)155<<48)+(v-(uintptr_t)records_55);
if(v>=(uintptr_t)records_56&&v<(uintptr_t)records_56+sizeof records_56)return ((uint64_t)156<<48)+(v-(uintptr_t)records_56);
if(v>=(uintptr_t)records_57&&v<(uintptr_t)records_57+sizeof records_57)return ((uint64_t)157<<48)+(v-(uintptr_t)records_57);
if(v>=(uintptr_t)records_58&&v<(uintptr_t)records_58+sizeof records_58)return ((uint64_t)158<<48)+(v-(uintptr_t)records_58);
if(v>=(uintptr_t)records_59&&v<(uintptr_t)records_59+sizeof records_59)return ((uint64_t)159<<48)+(v-(uintptr_t)records_59);
if(v>=(uintptr_t)records_60&&v<(uintptr_t)records_60+sizeof records_60)return ((uint64_t)160<<48)+(v-(uintptr_t)records_60);
if(v>=(uintptr_t)records_61&&v<(uintptr_t)records_61+sizeof records_61)return ((uint64_t)161<<48)+(v-(uintptr_t)records_61);
if(v>=(uintptr_t)records_62&&v<(uintptr_t)records_62+sizeof records_62)return ((uint64_t)162<<48)+(v-(uintptr_t)records_62);
if(v>=(uintptr_t)records_63&&v<(uintptr_t)records_63+sizeof records_63)return ((uint64_t)163<<48)+(v-(uintptr_t)records_63);
if(v>=(uintptr_t)records_64&&v<(uintptr_t)records_64+sizeof records_64)return ((uint64_t)164<<48)+(v-(uintptr_t)records_64);
if(v>=(uintptr_t)records_65&&v<(uintptr_t)records_65+sizeof records_65)return ((uint64_t)165<<48)+(v-(uintptr_t)records_65);
if(v>=(uintptr_t)records_66&&v<(uintptr_t)records_66+sizeof records_66)return ((uint64_t)166<<48)+(v-(uintptr_t)records_66);
if(v>=(uintptr_t)records_67&&v<(uintptr_t)records_67+sizeof records_67)return ((uint64_t)167<<48)+(v-(uintptr_t)records_67);
if(v>=(uintptr_t)records_68&&v<(uintptr_t)records_68+sizeof records_68)return ((uint64_t)168<<48)+(v-(uintptr_t)records_68);
if(v>=(uintptr_t)records_69&&v<(uintptr_t)records_69+sizeof records_69)return ((uint64_t)169<<48)+(v-(uintptr_t)records_69);
if(v>=(uintptr_t)records_70&&v<(uintptr_t)records_70+sizeof records_70)return ((uint64_t)170<<48)+(v-(uintptr_t)records_70);
if(v>=(uintptr_t)records_71&&v<(uintptr_t)records_71+sizeof records_71)return ((uint64_t)171<<48)+(v-(uintptr_t)records_71);
if(v>=(uintptr_t)records_72&&v<(uintptr_t)records_72+sizeof records_72)return ((uint64_t)172<<48)+(v-(uintptr_t)records_72);
if(v>=(uintptr_t)records_73&&v<(uintptr_t)records_73+sizeof records_73)return ((uint64_t)173<<48)+(v-(uintptr_t)records_73);
if(v>=(uintptr_t)records_74&&v<(uintptr_t)records_74+sizeof records_74)return ((uint64_t)174<<48)+(v-(uintptr_t)records_74);
if(v>=(uintptr_t)records_75&&v<(uintptr_t)records_75+sizeof records_75)return ((uint64_t)175<<48)+(v-(uintptr_t)records_75);
if(v>=(uintptr_t)records_76&&v<(uintptr_t)records_76+sizeof records_76)return ((uint64_t)176<<48)+(v-(uintptr_t)records_76);
if(v>=(uintptr_t)records_77&&v<(uintptr_t)records_77+sizeof records_77)return ((uint64_t)177<<48)+(v-(uintptr_t)records_77);
if(v>=(uintptr_t)records_78&&v<(uintptr_t)records_78+sizeof records_78)return ((uint64_t)178<<48)+(v-(uintptr_t)records_78);
if(v>=(uintptr_t)records_79&&v<(uintptr_t)records_79+sizeof records_79)return ((uint64_t)179<<48)+(v-(uintptr_t)records_79);
if(v>=(uintptr_t)records_80&&v<(uintptr_t)records_80+sizeof records_80)return ((uint64_t)180<<48)+(v-(uintptr_t)records_80);
if(v>=(uintptr_t)records_81&&v<(uintptr_t)records_81+sizeof records_81)return ((uint64_t)181<<48)+(v-(uintptr_t)records_81);
if(v>=(uintptr_t)&flags&&v<(uintptr_t)&flags+sizeof flags)return ((uint64_t)300<<48)+(v-(uintptr_t)&flags);
if(v>=(uintptr_t)&iflags&&v<(uintptr_t)&iflags+sizeof iflags)return ((uint64_t)301<<48)+(v-(uintptr_t)&iflags);
if(v>=(uintptr_t)&mons&&v<(uintptr_t)&mons+sizeof mons)return ((uint64_t)302<<48)+(v-(uintptr_t)&mons);
if(v>=(uintptr_t)&nul_glyphinfo&&v<(uintptr_t)&nul_glyphinfo+sizeof nul_glyphinfo)return ((uint64_t)303<<48)+(v-(uintptr_t)&nul_glyphinfo);
if(v>=(uintptr_t)&restoreinfo&&v<(uintptr_t)&restoreinfo+sizeof restoreinfo)return ((uint64_t)304<<48)+(v-(uintptr_t)&restoreinfo);
if(v>=(uintptr_t)&uwep&&v<(uintptr_t)&uwep+sizeof uwep)return ((uint64_t)305<<48)+(v-(uintptr_t)&uwep);
if(v>=(uintptr_t)&uchain&&v<(uintptr_t)&uchain+sizeof uchain)return ((uint64_t)306<<48)+(v-(uintptr_t)&uchain);
if(v>=(uintptr_t)&uball&&v<(uintptr_t)&uball+sizeof uball)return ((uint64_t)307<<48)+(v-(uintptr_t)&uball);
if(v>=(uintptr_t)&u&&v<(uintptr_t)&u+sizeof u)return ((uint64_t)308<<48)+(v-(uintptr_t)&u);
if(v>=(uintptr_t)&ubirthday&&v<(uintptr_t)&ubirthday+sizeof ubirthday)return ((uint64_t)309<<48)+(v-(uintptr_t)&ubirthday);
if(v>=(uintptr_t)&urealtime&&v<(uintptr_t)&urealtime+sizeof urealtime)return ((uint64_t)310<<48)+(v-(uintptr_t)&urealtime);
if(v>=(uintptr_t)&WIN_MESSAGE&&v<(uintptr_t)&WIN_MESSAGE+sizeof WIN_MESSAGE)return ((uint64_t)311<<48)+(v-(uintptr_t)&WIN_MESSAGE);
if(v>=(uintptr_t)&gb&&v<(uintptr_t)&gb+sizeof gb)return ((uint64_t)312<<48)+(v-(uintptr_t)&gb);
if(v>=(uintptr_t)&gc&&v<(uintptr_t)&gc+sizeof gc)return ((uint64_t)313<<48)+(v-(uintptr_t)&gc);
if(v>=(uintptr_t)&gd&&v<(uintptr_t)&gd+sizeof gd)return ((uint64_t)314<<48)+(v-(uintptr_t)&gd);
if(v>=(uintptr_t)&ge&&v<(uintptr_t)&ge+sizeof ge)return ((uint64_t)315<<48)+(v-(uintptr_t)&ge);
if(v>=(uintptr_t)&gf&&v<(uintptr_t)&gf+sizeof gf)return ((uint64_t)316<<48)+(v-(uintptr_t)&gf);
if(v>=(uintptr_t)&gh&&v<(uintptr_t)&gh+sizeof gh)return ((uint64_t)317<<48)+(v-(uintptr_t)&gh);
if(v>=(uintptr_t)&gi&&v<(uintptr_t)&gi+sizeof gi)return ((uint64_t)318<<48)+(v-(uintptr_t)&gi);
if(v>=(uintptr_t)&gm&&v<(uintptr_t)&gm+sizeof gm)return ((uint64_t)319<<48)+(v-(uintptr_t)&gm);
if(v>=(uintptr_t)&gn&&v<(uintptr_t)&gn+sizeof gn)return ((uint64_t)320<<48)+(v-(uintptr_t)&gn);
if(v>=(uintptr_t)&go&&v<(uintptr_t)&go+sizeof go)return ((uint64_t)321<<48)+(v-(uintptr_t)&go);
if(v>=(uintptr_t)&gs&&v<(uintptr_t)&gs+sizeof gs)return ((uint64_t)322<<48)+(v-(uintptr_t)&gs);
if(v>=(uintptr_t)&gu&&v<(uintptr_t)&gu+sizeof gu)return ((uint64_t)323<<48)+(v-(uintptr_t)&gu);
if(v>=(uintptr_t)&gv&&v<(uintptr_t)&gv+sizeof gv)return ((uint64_t)324<<48)+(v-(uintptr_t)&gv);
if(v>=(uintptr_t)&gy&&v<(uintptr_t)&gy+sizeof gy)return ((uint64_t)325<<48)+(v-(uintptr_t)&gy);
if(v>=(uintptr_t)&svc&&v<(uintptr_t)&svc+sizeof svc)return ((uint64_t)326<<48)+(v-(uintptr_t)&svc);
if(v>=(uintptr_t)&svd&&v<(uintptr_t)&svd+sizeof svd)return ((uint64_t)327<<48)+(v-(uintptr_t)&svd);
if(v>=(uintptr_t)&svk&&v<(uintptr_t)&svk+sizeof svk)return ((uint64_t)328<<48)+(v-(uintptr_t)&svk);
if(v>=(uintptr_t)&svl&&v<(uintptr_t)&svl+sizeof svl)return ((uint64_t)329<<48)+(v-(uintptr_t)&svl);
if(v>=(uintptr_t)&svm&&v<(uintptr_t)&svm+sizeof svm)return ((uint64_t)330<<48)+(v-(uintptr_t)&svm);
if(v>=(uintptr_t)&svn&&v<(uintptr_t)&svn+sizeof svn)return ((uint64_t)331<<48)+(v-(uintptr_t)&svn);
if(v>=(uintptr_t)&svo&&v<(uintptr_t)&svo+sizeof svo)return ((uint64_t)332<<48)+(v-(uintptr_t)&svo);
if(v>=(uintptr_t)&svp&&v<(uintptr_t)&svp+sizeof svp)return ((uint64_t)333<<48)+(v-(uintptr_t)&svp);
if(v>=(uintptr_t)&svq&&v<(uintptr_t)&svq+sizeof svq)return ((uint64_t)334<<48)+(v-(uintptr_t)&svq);
if(v>=(uintptr_t)&svr&&v<(uintptr_t)&svr+sizeof svr)return ((uint64_t)335<<48)+(v-(uintptr_t)&svr);
if(v>=(uintptr_t)&svs&&v<(uintptr_t)&svs+sizeof svs)return ((uint64_t)336<<48)+(v-(uintptr_t)&svs);
if(v>=(uintptr_t)&svu&&v<(uintptr_t)&svu+sizeof svu)return ((uint64_t)337<<48)+(v-(uintptr_t)&svu);
if(v>=(uintptr_t)&svw&&v<(uintptr_t)&svw+sizeof svw)return ((uint64_t)338<<48)+(v-(uintptr_t)&svw);
if(v>=(uintptr_t)&program_state&&v<(uintptr_t)&program_state+sizeof program_state)return ((uint64_t)339<<48)+(v-(uintptr_t)&program_state);
if(v>=(uintptr_t)&cg&&v<(uintptr_t)&cg+sizeof cg)return ((uint64_t)340<<48)+(v-(uintptr_t)&cg);
if(v>=(uintptr_t)&sysopt&&v<(uintptr_t)&sysopt+sizeof sysopt)return ((uint64_t)341<<48)+(v-(uintptr_t)&sysopt);
if(v>=(uintptr_t)&windowprocs&&v<(uintptr_t)&windowprocs+sizeof windowprocs)return ((uint64_t)342<<48)+(v-(uintptr_t)&windowprocs);
return v;}
void probe_reset(void){for(int i=0;i<na;i++)if(allocations[i].live)free(allocations[i].p);if(grown)free(grown);na=nfree=ninput=nrecord=serialcount=reentered=0;last_result=0;grown=0;grow_at=reenter_at=0;memset(opts,0,sizeof opts);memset(input,0,sizeof input);memset(records,0,sizeof records);memset(&file,0,sizeof file);memset(&created,0,sizeof created);memset(texts,0,sizeof texts);memset(saved_names,0,sizeof saved_names);nsaved=0;
memset((void*)&flags,0,sizeof flags);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&nul_glyphinfo,0,sizeof nul_glyphinfo);
memset((void*)&restoreinfo,0,sizeof restoreinfo);
memset((void*)&uwep,0,sizeof uwep);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&uball,0,sizeof uball);
memset((void*)&u,0,sizeof u);
memset((void*)&ubirthday,0,sizeof ubirthday);
memset((void*)&urealtime,0,sizeof urealtime);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&gb,0,sizeof gb);
memset((void*)&gc,0,sizeof gc);
memset((void*)&gd,0,sizeof gd);
memset((void*)&ge,0,sizeof ge);
memset((void*)&gf,0,sizeof gf);
memset((void*)&gh,0,sizeof gh);
memset((void*)&gi,0,sizeof gi);
memset((void*)&gm,0,sizeof gm);
memset((void*)&gn,0,sizeof gn);
memset((void*)&go,0,sizeof go);
memset((void*)&gs,0,sizeof gs);
memset((void*)&gu,0,sizeof gu);
memset((void*)&gv,0,sizeof gv);
memset((void*)&gy,0,sizeof gy);
memset((void*)&svc,0,sizeof svc);
memset((void*)&svd,0,sizeof svd);
memset((void*)&svk,0,sizeof svk);
memset((void*)&svl,0,sizeof svl);
memset((void*)&svm,0,sizeof svm);
memset((void*)&svn,0,sizeof svn);
memset((void*)&svo,0,sizeof svo);
memset((void*)&svp,0,sizeof svp);
memset((void*)&svq,0,sizeof svq);
memset((void*)&svr,0,sizeof svr);
memset((void*)&svs,0,sizeof svs);
memset((void*)&svu,0,sizeof svu);
memset((void*)&svw,0,sizeof svw);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&cg,0,sizeof cg);
memset((void*)&sysopt,0,sizeof sysopt);
memset((void*)&windowprocs,0,sizeof windowprocs);
memset(records_0,0,sizeof records_0);
memset(records_1,0,sizeof records_1);
memset(records_2,0,sizeof records_2);
memset(records_3,0,sizeof records_3);
memset(records_4,0,sizeof records_4);
memset(records_5,0,sizeof records_5);
memset(records_6,0,sizeof records_6);
memset(records_7,0,sizeof records_7);
memset(records_8,0,sizeof records_8);
memset(records_9,0,sizeof records_9);
memset(records_10,0,sizeof records_10);
memset(records_11,0,sizeof records_11);
memset(records_12,0,sizeof records_12);
memset(records_13,0,sizeof records_13);
memset(records_14,0,sizeof records_14);
memset(records_15,0,sizeof records_15);
memset(records_16,0,sizeof records_16);
memset(records_17,0,sizeof records_17);
memset(records_18,0,sizeof records_18);
memset(records_19,0,sizeof records_19);
memset(records_20,0,sizeof records_20);
memset(records_21,0,sizeof records_21);
memset(records_22,0,sizeof records_22);
memset(records_23,0,sizeof records_23);
memset(records_24,0,sizeof records_24);
memset(records_25,0,sizeof records_25);
memset(records_26,0,sizeof records_26);
memset(records_27,0,sizeof records_27);
memset(records_28,0,sizeof records_28);
memset(records_29,0,sizeof records_29);
memset(records_30,0,sizeof records_30);
memset(records_31,0,sizeof records_31);
memset(records_32,0,sizeof records_32);
memset(records_33,0,sizeof records_33);
memset(records_34,0,sizeof records_34);
memset(records_35,0,sizeof records_35);
memset(records_36,0,sizeof records_36);
memset(records_37,0,sizeof records_37);
memset(records_38,0,sizeof records_38);
memset(records_39,0,sizeof records_39);
memset(records_40,0,sizeof records_40);
memset(records_41,0,sizeof records_41);
memset(records_42,0,sizeof records_42);
memset(records_43,0,sizeof records_43);
memset(records_44,0,sizeof records_44);
memset(records_45,0,sizeof records_45);
memset(records_46,0,sizeof records_46);
memset(records_47,0,sizeof records_47);
memset(records_48,0,sizeof records_48);
memset(records_49,0,sizeof records_49);
memset(records_50,0,sizeof records_50);
memset(records_51,0,sizeof records_51);
memset(records_52,0,sizeof records_52);
memset(records_53,0,sizeof records_53);
memset(records_54,0,sizeof records_54);
memset(records_55,0,sizeof records_55);
memset(records_56,0,sizeof records_56);
memset(records_57,0,sizeof records_57);
memset(records_58,0,sizeof records_58);
memset(records_59,0,sizeof records_59);
memset(records_60,0,sizeof records_60);
memset(records_61,0,sizeof records_61);
memset(records_62,0,sizeof records_62);
memset(records_63,0,sizeof records_63);
memset(records_64,0,sizeof records_64);
memset(records_65,0,sizeof records_65);
memset(records_66,0,sizeof records_66);
memset(records_67,0,sizeof records_67);
memset(records_68,0,sizeof records_68);
memset(records_69,0,sizeof records_69);
memset(records_70,0,sizeof records_70);
memset(records_71,0,sizeof records_71);
memset(records_72,0,sizeof records_72);
memset(records_73,0,sizeof records_73);
memset(records_74,0,sizeof records_74);
memset(records_75,0,sizeof records_75);
memset(records_76,0,sizeof records_76);
memset(records_77,0,sizeof records_77);
memset(records_78,0,sizeof records_78);
memset(records_79,0,sizeof records_79);
memset(records_80,0,sizeof records_80);
memset(records_81,0,sizeof records_81);
for(int i=0;i<8;i++){records_0[i].mhp=records_0[i].mhpmax=100;}monst_globals_init();objects_globals_init();u.uhp=u.uhpmax=100;u.uz.dnum=2;u.uz.dlevel=7;u.umonnum=u.umonster=PM_HUMAN;svm.moves=9007199254741001LL;svo.omoves=9007199254740000LL;u.ulycn=NON_PM;sysopt.check_save_uid=0;WIN_MESSAGE=7;nextid=8000;windowprocs.win_create_nhwindow=createwin;windowprocs.win_clear_nhwindow=clearwin;windowprocs.win_display_nhwindow=displaywin;windowprocs.win_destroy_nhwindow=destroywin;windowprocs.win_wait_synch=waitwin;windowprocs.win_cliparound=clipwin;windowprocs.win_putstr=putwin;windowprocs.win_putmsghistory=history;windowprocs.win_start_menu=startwin;windowprocs.win_end_menu=endwin;windowprocs.win_add_menu=addwin;windowprocs.win_select_menu=selectwin;ti=0;tracebuf[0]=0;}
void probe_option(int n,long v){opts[n]=v;}void probe_callbacks(int growth,int reentry){grow_at=growth;reenter_at=reentry;}
void *probe_pointer(int kind,int index){return source(kind,index);}void *probe_file(void){return &file;}void*probe_global(int n){return teleport_restore_global(n);}
void probe_set(int kind,int index,int field,uint64_t value){teleport_restore_write(kind,source(kind,index),field,value);}
void probe_link(int which,int kind,int index){void*p=source(kind,index);switch(which){case 0:gi.invent=p;break;case 1:fobj=p;break;case 2:fmon=p;break;case 3:go.oldfruit=p;break;case 4:gf.ffruit=p;break;default:abort();}}
const char*probe_trace(void){return tracebuf;}int probe_frees(void){return nfree;}uintptr_t probe_stack(void){return emscripten_stack_get_current();}
const char*probe_snapshot(void){int old=ti;char*hold=malloc(ti+1);memcpy(hold,tracebuf,ti+1);ti=0;for(int i=0;i<na;i++){append("a%d:%zu:%d:",i,allocations[i].n,allocations[i].live);if(allocations[i].live)bytes(allocations[i].p,allocations[i].n);append(";");}
append("g:flags:");bytes((void*)&flags,sizeof flags);append(";");
append("g:iflags:");bytes((void*)&iflags,sizeof iflags);append(";");
append("g:restoreinfo:");bytes((void*)&restoreinfo,sizeof restoreinfo);append(";");
append("g:uwep:");bytes((void*)&uwep,sizeof uwep);append(";");
append("g:uchain:");bytes((void*)&uchain,sizeof uchain);append(";");
append("g:uball:");bytes((void*)&uball,sizeof uball);append(";");
append("g:u:");bytes((void*)&u,sizeof u);append(";");
append("g:ubirthday:");bytes((void*)&ubirthday,sizeof ubirthday);append(";");
append("g:urealtime:");bytes((void*)&urealtime,sizeof urealtime);append(";");
append("g:WIN_MESSAGE:");bytes((void*)&WIN_MESSAGE,sizeof WIN_MESSAGE);append(";");
append("g:gb:");bytes((void*)&gb,sizeof gb);append(";");
append("g:gc:");bytes((void*)&gc,sizeof gc);append(";");
append("g:gd:");bytes((void*)&gd,sizeof gd);append(";");
append("g:ge:");bytes((void*)&ge,sizeof ge);append(";");
append("g:gf:");bytes((void*)&gf,sizeof gf);append(";");
append("g:gh:");bytes((void*)&gh,sizeof gh);append(";");
append("g:gi:");bytes((void*)&gi,sizeof gi);append(";");
append("g:gm:");bytes((void*)&gm,sizeof gm);append(";");
append("g:gn:");bytes((void*)&gn,sizeof gn);append(";");
append("g:go:");bytes((void*)&go,sizeof go);append(";");
append("g:gs:");bytes((void*)&gs,sizeof gs);append(";");
append("g:gu:");bytes((void*)&gu,sizeof gu);append(";");
append("g:gv:");bytes((void*)&gv,sizeof gv);append(";");
append("g:gy:");bytes((void*)&gy,sizeof gy);append(";");
append("g:svc:");bytes((void*)&svc,sizeof svc);append(";");
append("g:svd:");bytes((void*)&svd,sizeof svd);append(";");
append("g:svk:");bytes((void*)&svk,sizeof svk);append(";");
append("g:svl:");bytes((void*)&svl,sizeof svl);append(";");
append("g:svm:");bytes((void*)&svm,sizeof svm);append(";");
append("g:svn:");bytes((void*)&svn,sizeof svn);append(";");
append("g:svo:");bytes((void*)&svo,sizeof svo);append(";");
append("g:svp:");bytes((void*)&svp,sizeof svp);append(";");
append("g:svq:");bytes((void*)&svq,sizeof svq);append(";");
append("g:svr:");bytes((void*)&svr,sizeof svr);append(";");
append("g:svs:");bytes((void*)&svs,sizeof svs);append(";");
append("g:svu:");bytes((void*)&svu,sizeof svu);append(";");
append("g:svw:");bytes((void*)&svw,sizeof svw);append(";");
append("g:program_state:");bytes((void*)&program_state,sizeof program_state);append(";");
append("g:cg:");bytes((void*)&cg,sizeof cg);append(";");
append("g:sysopt:");bytes((void*)&sysopt,sizeof sysopt);append(";");
append("file:");bytes(&file,sizeof file);append(";created:");bytes(&created,sizeof created);append(";");snprintf(snapbuf,sizeof snapbuf,"%s",tracebuf);memcpy(tracebuf,hold,old+1);ti=old;free(hold);return snapbuf;}
long probe_action(int op,int a,int b,int c){switch(op){case 0:find_lev_obj();return 0;case 1:inven_inuse(a);return 0;case 2:restlevchn(&file);return 0;case 3:restdamage(&file);return 0;case 4:restobj(&file,source(2,b));return 0;case 5:last_result=restobjchn(&file,b);return (long)normalized((uintptr_t)last_result);case 6:restmon(&file,source(0,b));return 0;case 7:last_result=restmonchn(&file);return (long)normalized((uintptr_t)last_result);case 8:last_result=loadfruitchn(&file);return (long)normalized((uintptr_t)last_result);case 9:freefruitchn(last_result);last_result=0;return 0;case 10:ghostfruit(source(2,a));return 0;case 11:return restgamestate(&file);case 12:restlevelstate();return 0;case 13:return restlevelfile(a);case 14:return dorecover(&file);case 15:rest_stairs(&file);return 0;case 16:restcemetery(&file,&svl.level.bonesinfo);return 0;case 17:rest_levl(&file);return 0;case 18:trickery(texts[0]);return 0;case 19:getlev(&file,b,c);return 0;case 20:rest_adjust_levelflags();return 0;case 21:moves_to_relative_time(&svo.omoves);return 0;case 22:relative_time_to_moves(&svo.omoves);return 0;case 23:get_plname_from_file(&file,texts[0],c);return 0;case 24:rest_bubbles(&file);return 0;case 25:restore_gamelog(&file);return 0;case 26:restore_msghistory(&file);return 0;case 27:clear_id_mapping();return 0;case 28:add_id_mapping(a,b);return 0;case 29:return lookup_id_mapping(a,&nextid);case 30:reset_oattached_mids(a);return 0;case 31:return restore_menu(a);default:abort();}}
int probe_kind_count(void){return 82;}const char*probe_kind_name(int k){static const char*names[]={"monst","permonst","obj","vptrs","oextra","mextra","egd","epri","eshk","emin","edog","ebones","dgn_topology","d_level","window_procs","instance_globals_o","fruit","mi","any","damage","sinfo","dlevel_t","rm","cemetery","levelflags","instance_globals_saved_s","spell","s_level","instance_globals_saved_n","instance_globals_c","nh_file","instance_globals_i","bucket","restore_id_pair","instance_globals_v","instance_globals_u","stairway","context_info","dig_info","victual_info","tin_info","book_info","warntype_info","polearm_info","instance_globals_n","instance_globals_saved_u","dest_area","instance_globals_saved_d","nhcoord","trap","instance_globals_m","u_realtime","instance_globals_f","you","align","instance_globals_e","instance_flags","mkroom","branch","instance_globals_saved_r","const_globals","instance_globals_y","instance_globals_saved_c","instance_globals_d","instance_globals_s","sysopt_s","flag","instance_globals_b","instance_globals_saved_q","q_score","instance_globals_saved_k","kinfo","instance_globals_saved_p","restore_info","instance_globals_saved_l","instance_globals_saved_w","instance_globals_saved_m","mvitals","instance_globals_h","gamelog_line","instance_globals_saved_o","glyphinfo"};return names[k];}int probe_field_count(int k){switch(k){case 0:return 17;case 1:return 5;case 2:return 15;case 3:return 3;case 4:return 3;case 5:return 8;case 6:return 0;case 7:return 0;case 8:return 0;case 9:return 0;case 10:return 3;case 11:return 0;case 12:return 4;case 13:return 2;case 14:return 10;case 15:return 1;case 16:return 3;case 17:return 1;case 18:return 1;case 19:return 2;case 20:return 4;case 21:return 9;case 22:return 1;case 23:return 1;case 24:return 1;case 25:return 2;case 26:return 0;case 27:return 1;case 28:return 2;case 29:return 1;case 30:return 4;case 31:return 2;case 32:return 2;case 33:return 2;case 34:return 1;case 35:return 1;case 36:return 7;case 37:return 7;case 38:return 1;case 39:return 2;case 40:return 2;case 41:return 2;case 42:return 2;case 43:return 2;case 44:return 1;case 45:return 1;case 46:return 0;case 47:return 4;case 48:return 2;case 49:return 4;case 50:return 2;case 51:return 2;case 52:return 2;case 53:return 14;case 54:return 2;case 55:return 1;case 56:return 4;case 57:return 2;case 58:return 3;case 59:return 1;case 60:return 2;case 61:return 1;case 62:return 1;case 63:return 2;case 64:return 1;case 65:return 1;case 66:return 2;case 67:return 1;case 68:return 1;case 69:return 0;case 70:return 1;case 71:return 1;case 72:return 3;case 73:return 1;case 74:return 2;case 75:return 2;case 76:return 2;case 77:return 0;case 78:return 1;case 79:return 2;case 80:return 1;case 81:return 0;default:abort();}}
const char*probe_field_name(int k,int f){switch(k){case 0:{static const char*names[]={"nmon","data","m_id","mnum","cham","mx","my","mhpmax","mtame","mundetected","mpeaceful","isshk","ispriest","wormno","minvent","mw","mextra"};return names[f];}case 1:{static const char*names[]={"pmidx","mlet","maligntyp","mflags1","mflags2"};return names[f];}case 2:{static const char*names[]={"nobj","v","cobj","o_id","ox","oy","otyp","spe","where","in_use","bypass","age","owornmask","lua_ref_cnt","oextra"};return names[f];}case 3:{static const char*names[]={"v_nexthere","v_ocontainer","v_ocarry"};return names[f];}case 4:{static const char*names[]={"oname","omonst","omid"};return names[f];}case 5:{static const char*names[]={"mgivenname","egd","epri","eshk","emin","edog","ebones","mcorpsenm"};return names[f];}case 6:{static const char*names[]={};return names[f];}case 7:{static const char*names[]={};return names[f];}case 8:{static const char*names[]={};return names[f];}case 9:{static const char*names[]={};return names[f];}case 10:{static const char*names[]={"droptime","apport","hungrytime"};return names[f];}case 11:{static const char*names[]={};return names[f];}case 12:{static const char*names[]={"d_rogue_level","d_medusa_level","d_stronghold_level","d_wiz1_level"};return names[f];}case 13:{static const char*names[]={"dnum","dlevel"};return names[f];}case 14:{static const char*names[]={"win_create_nhwindow","win_clear_nhwindow","win_display_nhwindow","win_destroy_nhwindow","win_putstr","win_start_menu","win_end_menu","win_wait_synch","win_cliparound","win_putmsghistory"};return names[f];}case 15:{static const char*names[]={"oldfruit"};return names[f];}case 16:{static const char*names[]={"fname","fid","nextf"};return names[f];}case 17:{static const char*names[]={"item"};return names[f];}case 18:{static const char*names[]={"a_int"};return names[f];}case 19:{static const char*names[]={"next","when"};return names[f];}case 20:{static const char*names[]={"something_worth_saving","restoring","in_getlev","beyond_savefile_load"};return names[f];}case 21:{static const char*names[]={"locations","objects","monsters","objlist","buriedobjlist","monlist","damagelist","bonesinfo","flags"};return names[f];}case 22:{static const char*names[]={"typ"};return names[f];}case 23:{static const char*names[]={"next"};return names[f];}case 24:{static const char*names[]={"stasis_until"};return names[f];}case 25:{static const char*names[]={"spl_book","sp_levchn"};return names[f];}case 26:{static const char*names[]={};return names[f];}case 27:{static const char*names[]={"next"};return names[f];}case 28:{static const char*names[]={"nhuuid","nroom"};return names[f];}case 29:{static const char*names[]={"converted_savefile_loaded"};return names[f];}case 30:{static const char*names[]={"fd","mode","ftype","eof"};return names[f];}case 31:{static const char*names[]={"invent","id_map"};return names[f];}case 32:{static const char*names[]={"next","map"};return names[f];}case 33:{static const char*names[]={"gid","nid"};return names[f];}case 34:{static const char*names[]={"vision_full_recalc"};return names[f];}case 35:{static const char*names[]={"unweapon"};return names[f];}case 36:{static const char*names[]={"sx","sy","tolev","up","isladder","u_traversed","next"};return names[f];}case 37:{static const char*names[]={"seer_turn","digging","victual","tin","spbook","warntype","polearm"};return names[f];}case 38:{static const char*names[]={"lastdigtime"};return names[f];}case 39:{static const char*names[]={"piece","o_id"};return names[f];}case 40:{static const char*names[]={"tin","o_id"};return names[f];}case 41:{static const char*names[]={"book","o_id"};return names[f];}case 42:{static const char*names[]={"species","speciesidx"};return names[f];}case 43:{static const char*names[]={"hitmon","m_id"};return names[f];}case 44:{static const char*names[]={"n_ids_mapped"};return names[f];}case 45:{static const char*names[]={"updest"};return names[f];}case 46:{static const char*names[]={};return names[f];}case 47:{static const char*names[]={"dungeon_topology","dndest","doors","doors_alloc"};return names[f];}case 48:{static const char*names[]={"x","y"};return names[f];}case 49:{static const char*names[]={"ntrap","tx","dst","ttyp"};return names[f];}case 50:{static const char*names[]={"migrating_objs","migrating_mons"};return names[f];}case 51:{static const char*names[]={"realtime","start_timing"};return names[f];}case 52:{static const char*names[]={"ftrap","ffruit"};return names[f];}case 53:{static const char*names[]={"ux","uy","uz","uz0","umonster","umonnum","mh","ualign","uhp","ustuck","usteed","ustuck_mid","usteed_mid","mcham"};return names[f];}case 54:{static const char*names[]={"type","abuse"};return names[f];}case 55:{static const char*names[]={"early_raw_messages"};return names[f];}case 56:{static const char*names[]={"last_msg","deferred_X","perm_invent","explore_error_flag"};return names[f];}case 57:{static const char*names[]={"doorct","fdoor"};return names[f];}case 58:{static const char*names[]={"type","end1","end2"};return names[f];}case 59:{static const char*names[]={"rooms"};return names[f];}case 60:{static const char*names[]={"zeromonst","zeroany"};return names[f];}case 61:{static const char*names[]={"youmonst"};return names[f];}case 62:{static const char*names[]={"context"};return names[f];}case 63:{static const char*names[]={"doorindex","defer_see_monsters"};return names[f];}case 64:{static const char*names[]={"stairs"};return names[f];}case 65:{static const char*names[]={"check_save_uid"};return names[f];}case 66:{static const char*names[]={"debug","explore"};return names[f];}case 67:{static const char*names[]={"billobjs"};return names[f];}case 68:{static const char*names[]={"quest_status"};return names[f];}case 69:{static const char*names[]={};return names[f];}case 70:{static const char*names[]={"killer"};return names[f];}case 71:{static const char*names[]={"name"};return names[f];}case 72:{static const char*names[]={"plname","pl_character","pl_fruit"};return names[f];}case 73:{static const char*names[]={"mread_flags"};return names[f];}case 74:{static const char*names[]={"lastseentyp","level"};return names[f];}case 75:{static const char*names[]={"wreserve","wtreserved"};return names[f];}case 76:{static const char*names[]={"moves","mvitals"};return names[f];}case 77:{static const char*names[]={};return names[f];}case 78:{static const char*names[]={"hero_seq"};return names[f];}case 79:{static const char*names[]={"turn","flags"};return names[f];}case 80:{static const char*names[]={"omoves"};return names[f];}case 81:{static const char*names[]={};return names[f];}default:abort();}}
size_t probe_context_size(void){return sizeof(struct obj);}int probe_layout_count(void){return SIZE(teleport_restore_layout);}const char*probe_layout_name(int i){return teleport_restore_layout[i].name;}size_t probe_layout_value(int i){return teleport_restore_layout[i].value;}
void probe_world(int key,long value){switch(key){case 0:svm.moves=value;break;case 1:svo.omoves=value;break;case 2:file.ftype=value;break;case 3:program_state.restoring=value;break;case 4:sysopt.check_save_uid=value;break;case 5:flags.debug=value;break;case 6:flags.explore=value;break;case 7:u.uz.dnum=value;break;case 8:u.uz.dlevel=value;break;case 9:iflags.perm_invent=value;break;case 10:iflags.explore_error_flag=value;break;case 11:svc.context.victual.o_id=value;break;case 12:svc.context.tin.o_id=value;break;case 13:svc.context.spbook.o_id=value;break;case 14:svc.context.polearm.m_id=value;break;case 15:nextid=value;break;case 16:file.mode=value;break;case 17:gn.n_ids_mapped=value;break;case 18:gc.converted_savefile_loaded=value;break;case 19:u.usteed_mid=value;break;case 20:u.ustuck_mid=value;break;case 21:svc.context.seer_turn=value;break;case 22:iflags.last_msg=value;break;case 23:svd.dungeon_topology.d_rogue_level.dnum=value;break;case 24:svd.dungeon_topology.d_rogue_level.dlevel=value;break;default:abort();}}
uint64_t probe_value(int key){switch(key){case 0:return nextid;case 1:return svm.moves;case 2:return svo.omoves;case 3:return gn.n_ids_mapped;case 4:return normalized((uintptr_t)gi.id_map);case 5:return normalized((uintptr_t)svs.sp_levchn);case 6:return normalized((uintptr_t)svl.level.damagelist);case 7:return normalized((uintptr_t)gi.invent);case 8:return normalized((uintptr_t)fmon);case 9:return normalized((uintptr_t)fobj);case 10:return normalized((uintptr_t)svl.level.bonesinfo);case 11:return u.uhp;case 12:return program_state.restoring;case 13:return normalized((uintptr_t)svc.context.victual.piece);case 14:return gf.ftrap?gf.ftrap->dst.dlevel:0;case 15:return gf.ftrap?gf.ftrap->dst.dnum:0;case 17:return svc.context.seer_turn;case 18:return flags.explore;case 19:return iflags.perm_invent;case 20:return iflags.last_msg;case 16:return ((stairway*)source(36,7))->u_traversed;default:abort();}}
void *probe_buffer(int index){return texts[index];}
void probe_saved(int index,const char*name,int mode){if(index<0||index>7)abort();memset(saved_names[index],0,PL_NSIZ_PLUS);snprintf(saved_names[index],PL_NSIZ_PLUS-1,"%s-Wiz-Hum-Mal-Neu",name);saved_names[index][PL_NSIZ_PLUS-1]=mode;if(index>=nsaved)nsaved=index+1;}

void probe_use_result(int key){switch(key){case 0:gi.invent=last_result;break;case 1:fobj=last_result;break;case 2:fmon=last_result;break;case 3:gf.ffruit=last_result;break;case 4:go.oldfruit=last_result;break;default:abort();}}
