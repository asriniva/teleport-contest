/* Controlled BONES world fixture; original C and JS run against identical state.
 * Filesystem/save/world dependencies not used by focused cases remain controlled
 * zero-return witnesses; they are not a claim that save/getbones is covered. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-bones-layout.h"
struct you u;
__typeof__(gs) gs; __typeof__(gf) gf; __typeof__(gi) gi; __typeof__(gu) gu;
__typeof__(svd) svd; __typeof__(svr) svr; __typeof__(svl) svl; __typeof__(svp) svp;
__typeof__(svn) svn; __typeof__(gb) gb; __typeof__(svc) svc;
__typeof__(flags) flags; __typeof__(iflags) iflags;
__typeof__(program_state) program_state;
volatile struct window_procs windowprocs;
struct obj *uball;
struct permonst mons[NUMMONS+1]; struct objclass objects[NUM_OBJECTS+1];
const struct Role roles[NUM_ROLES+1]={{0}};
const struct Race races[NUM_RACES+1]={{0}};
const struct Gender genders[4]={{0}};
const struct Align aligns[4]={{0}};
const char ynchars[]="yn";
static struct obj pool[16];static struct monst mpool[8];static struct fruit fruitpool[4];
static struct trap trap_pool[4];static struct cemetery cemeterypool[4];
static struct oextra extras[16];static struct mextra mextras[8];
static char names[16][BUFSZ],input[2048],output[16384],tracebuf[16384];
static void *growth;
static int opts[32],seed,random_count;static s_level special;static branch branching;
static void append(const char*fmt,...){va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+strlen(tracebuf),sizeof tracebuf-strlen(tracebuf),fmt,ap);va_end(ap);}
static int oid(const struct obj *o){if(!o)return -1;for(int i=0;i<16;i++)if(o==&pool[i])return i;return 99;}
static int mid(const struct monst *m){if(!m)return -1;for(int i=0;i<8;i++)if(m==&mpool[i])return i;return 99;}
char yn_function(const char*q,const char*choices,char def,boolean save){append("yn:%s:%s:%d:%d;",q,choices,def,save);return opts[25];}
void panic(const char*fmt,...){abort();}
void impossible(const char*fmt,...){abort();}
void pline(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);}
void You(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("You:%s;",b);}
boolean debugcore(const char*file,boolean wild){return opts[24];}
boolean rng_log_enabled(void){return opts[23];}
void rng_log_set_caller(const char*file,int line,const char*fn){const char*p=strrchr(file,'/');append("site:%s:%d:%s;",p?p+1:file,line,fn);}
int (rn2)(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;int v=(unsigned)seed%n;random_count++;append("rn2:%d:%d;",n,v);return v;}
long *alloc(unsigned n){void*p=malloc(n);if(!p)abort();return p;}
struct mextra*newmextra(void){return calloc(1,sizeof(struct mextra));}
struct fruit*fruit_from_indx(int n){append("fruit:%d;",n);for(int i=0;i<4;i++)if(fruitpool[i].fid==n)return &fruitpool[i];return 0;}
xint16 ledger_no(d_level*l){append("ledger:%d:%d;",l->dnum,l->dlevel);return l->dlevel?opts[0]:0;}
xint16 maxledgerno(void){return opts[1];}
void assign_level(d_level*to,d_level*from){append("assign;%d:%d;",from->dnum,from->dlevel);*to=*from;}
s_level*Is_special(d_level*l){append("special;");return opts[2]?&special:0;}
boolean Is_botlevel(d_level*l){return opts[3];}
branch*Is_branchlev(d_level*l){return opts[4]?&branching:0;}
boolean In_hell(d_level*l){return opts[5];}
xint16 dunlevs_in_dungeon(d_level*l){return opts[6];}
schar depth(d_level*l){append("depth;");return opts[7];}
boolean on_level(d_level*a,d_level*b){return a->dnum==b->dnum&&a->dlevel==b->dlevel;}
int isok(coordxy x,coordxy y){return x>=1&&x<COLNO&&y>=0&&y<ROWNO;}
boolean attacktype(struct permonst*pm,int at){return opts[18];}
int can_carry(struct monst*m,struct obj*o){append("carry:%d:%d;",mid(m),oid(o));return opts[16];}
void obj_extract_self(struct obj*o){append("extract:%d;",oid(o));struct obj**p=&gi.invent;while(*p&&*p!=o)p=&(*p)->nobj;if(*p)*p=o->nobj;o->nobj=0;}
void dealloc_obj(struct obj*o){append("dealloc:%d;",oid(o));o->where=OBJ_DELETED;}
void obj_no_longer_held(struct obj*o){append("unheld:%d;",oid(o));}
boolean artifact_light(struct obj*o){return opts[17];}
boolean obj_is_burning(struct obj*o){return o->lamplit;}
void end_burn(struct obj*o,boolean timer){append("end-burn:%d:%d;",oid(o),timer);o->lamplit=0;}
void curse(struct obj*o){append("curse:%d;",oid(o));o->cursed=1;}
int weight(struct obj*o){append("weight:%d;",oid(o));return 7U*(unsigned)o->quan;}
int add_to_minv(struct monst*m,struct obj*o){append("minv:%d:%d;",mid(m),oid(o));o->nobj=m->minvent;m->minvent=o;return 0;}
struct obj*add_to_container(struct obj*c,struct obj*o){append("container:%d:%d;",oid(c),oid(o));o->nobj=c->cobj;c->cobj=o;return o;}
void place_object(struct obj*o,coordxy x,coordxy y){append("place:%d:%d:%d;",oid(o),x,y);o->ox=x;o->oy=y;o->where=OBJ_FLOOR;o->nobj=fobj;fobj=o;}
boolean exist_artifact(int typ,const char*name){append("exist:%d:%s;",typ,name);return opts[8];}
boolean is_quest_artifact(struct obj*o){return opts[9];}
const char*safe_oname(struct obj*o){return has_oname(o)?ONAME(o):"";}
void free_oname(struct obj*o){append("free-name:%d;",oid(o));o->oextra->oname=0;}
void artifact_exists(struct obj*o,const char*n,boolean on,unsigned flags){append("artifact:%d:%s:%d:%u;",oid(o),n,on,flags);}
void free_omonst(struct obj*o){append("free-omonst:%d;",oid(o));o->oextra->omonst=0;}
boolean cant_revive(int*n,boolean revival,struct obj*o){append("cant-revive:%d:%d:%d;",*n,revival,oid(o));if(opts[10])*n=PM_DOPPELGANGER;return opts[10];}
void set_corpsenm(struct obj*o,int n){append("corpse:%d:%d;",oid(o),n);o->corpsenm=n;}
boolean get_obj_location(struct obj*o,coordxy*x,coordxy*y,int flags){append("location:%d:%d;",oid(o),flags);if(opts[26]&&!growth){growth=malloc(emscripten_get_heap_size()+16UL*1024*1024);if(!growth)abort();append("growth;");}*x=o->ox;*y=o->oy;return opts[11];}
char inside_shop(coordxy x,coordxy y){return opts[12];}
char*in_rooms(coordxy x,coordxy y,int type){static char room[]={ROOMOFFSET,0};return opts[13]?room:room+1;}
boolean tended_shop(struct mkroom*r){return opts[14];}
char*xname(struct obj*o){append("xname:%d;",oid(o));return "bow";}
char*the(const char*s){return (char*)s;}
void iter_mons(void(*fn)(struct monst*)){for(struct monst*m=fmon,*next;m;m=next){next=m->nmon;fn(m);}}
/* Unexercised controlled dependency witness. */
struct monst * (christen_monst)(struct monst * a0,const char * a1){append("boundary:christen_monst;");return 0;}
/* Unexercised controlled dependency witness. */
void (clear_bypasses)(void){append("boundary:clear_bypasses;");}
/* Unexercised controlled dependency witness. */
void (close_nhfile)(NHFILE * a0){append("boundary:close_nhfile;");}
/* Unexercised controlled dependency witness. */
void (commit_bonesfile)(d_level * a0){append("boundary:commit_bonesfile;");}
/* Unexercised controlled dependency witness. */
void (compress_bonesfile)(void){append("boundary:compress_bonesfile;");}
/* Unexercised controlled dependency witness. */
NHFILE * (create_bonesfile)(d_level * a0,char ** a1,char * a2){append("boundary:create_bonesfile;");return 0;}
/* Unexercised controlled dependency witness. */
int (delete_bonesfile)(d_level * a0){append("boundary:delete_bonesfile;");return 0;}
/* Unexercised controlled dependency witness. */
void (dismount_steed)(int a0){append("boundary:dismount_steed;");}
/* Unexercised controlled dependency witness. */
void (dmonsfree)(void){append("boundary:dmonsfree;");}
/* Unexercised controlled dependency witness. */
boolean (enexto)(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){append("boundary:enexto;");return 0;}
/* Unexercised controlled dependency witness. */
void (fix_shop_damage)(void){append("boundary:fix_shop_damage;");}
/* Unexercised controlled dependency witness. */
void (forget_engravings)(void){append("boundary:forget_engravings;");}
/* Unexercised controlled dependency witness. */
void (formatkiller)(char * a0,unsigned int a1,int a2,boolean a3){append("boundary:formatkiller;");}
/* Unexercised controlled dependency witness. */
void (getlev)(NHFILE * a0,int a1,xint8 a2){append("boundary:getlev;");}
/* Unexercised controlled dependency witness. */
void (give_u_to_m_resistances)(struct monst * a0){append("boundary:give_u_to_m_resistances;");}
/* Unexercised controlled dependency witness. */
struct obj * (m_carrying)(struct monst * a0,int a1){append("boundary:m_carrying;");return 0;}
/* Unexercised controlled dependency witness. */
void (m_dowear)(struct monst * a0,boolean a1){append("boundary:m_dowear;");}
/* Unexercised controlled dependency witness. */
struct monst * (makemon)(struct permonst * a0,coordxy a1,coordxy a2,mmflags_nht a3){append("boundary:makemon;");return 0;}
/* Unexercised controlled dependency witness. */
struct obj * (mk_named_object)(int a0,struct permonst * a1,coordxy a2,coordxy a3,const char * a4){append("boundary:mk_named_object;");return 0;}
/* Unexercised controlled dependency witness. */
struct obj * (mongets)(struct monst * a0,int a1){append("boundary:mongets;");return 0;}
/* Unexercised controlled dependency witness. */
void (mongone)(struct monst * a0){append("boundary:mongone;");}
/* Unexercised controlled dependency witness. */
void (newsym)(coordxy a0,coordxy a1){append("boundary:newsym;");}
/* Unexercised controlled dependency witness. */
struct obj * (obj_attach_mid)(struct obj * a0,unsigned int a1){append("boundary:obj_attach_mid;");return 0;}
/* Unexercised controlled dependency witness. */
NHFILE * (open_bonesfile)(d_level * a0,char ** a1){append("boundary:open_bonesfile;");return 0;}
/* Unexercised controlled dependency witness. */
void (paniclog)(const char * a0,const char * a1){append("boundary:paniclog;");}
/* Unexercised controlled dependency witness. */
void (rloc_to)(struct monst * a0,coordxy a1,coordxy a2){append("boundary:rloc_to;");}
/* Unexercised controlled dependency witness. */
void (sanitize_engravings)(void){append("boundary:sanitize_engravings;");}
/* Unexercised controlled dependency witness. */
void (savefruitchn)(NHFILE * a0){append("boundary:savefruitchn;");}
/* Unexercised controlled dependency witness. */
void (savelev)(NHFILE * a0,xint8 a1){append("boundary:savelev;");}
/* Unexercised controlled dependency witness. */
void (sfi_char)(NHFILE * a0,char * a1,const char * a2,int a3){append("boundary:sfi_char;");}
/* Unexercised controlled dependency witness. */
void (sfo_char)(NHFILE * a0,char * a1,const char * a2,int a3){append("boundary:sfo_char;");}
/* Unexercised controlled dependency witness. */
void (store_version)(NHFILE * a0){append("boundary:store_version;");}
/* Unexercised controlled dependency witness. */
void (trickery)(char * a0){append("boundary:trickery;");}
/* Unexercised controlled dependency witness. */
void (unleash_all)(void){append("boundary:unleash_all;");}
/* Unexercised controlled dependency witness. */
void (unpunish)(void){append("boundary:unpunish;");}
/* Unexercised controlled dependency witness. */
void (update_mlstmv)(void){append("boundary:update_mlstmv;");}
/* Unexercised controlled dependency witness. */
int (validate)(NHFILE * a0,const char * a1,boolean a2){append("boundary:validate;");return 0;}
/* Unexercised controlled dependency witness. */
char * (yyyymmddhhmmss)(time_t a0){append("boundary:yyyymmddhhmmss:%lld;",(long long)a0);return "19700101000000";}

#ifdef HYBRID_BONES
extern boolean teleport_bones_no_bones_level(d_level*);
extern void teleport_bones_goodfruit(int);
extern void teleport_bones_resetobjs(struct obj*,boolean);
extern void teleport_bones_set_ghostly_objlist(struct obj*);
#define no_bones_level teleport_bones_no_bones_level
#define goodfruit teleport_bones_goodfruit
#define resetobjs teleport_bones_resetobjs
#define set_ghostly_objlist teleport_bones_set_ghostly_objlist
#else
#include "../.cache/wasm64-build/tree/src/bones.c"
#endif
void *probe_pointer(int kind,int index){switch(kind){case 0:return &pool[index];case 1:return &mpool[index];case 2:return &fruitpool[index];case 3:return &trap_pool[index];case 4:return &cemeterypool[index];case 5:return input;case 6:return &u;case 7:return &svl.level;default:abort();}}
void probe_reset(void){
 if(growth){free(growth);growth=0;}
 for(int i=0;i<8;i++)if(mpool[i].mextra&&mpool[i].mextra!=&mextras[i]){if(mpool[i].mextra->ebones)free(mpool[i].mextra->ebones);free(mpool[i].mextra);}
 memset(&u,0,sizeof u);memset(&gs,0,sizeof gs);memset(&gf,0,sizeof gf);memset(&gi,0,sizeof gi);memset(&svl,0,sizeof svl);memset(&svd,0,sizeof svd);memset(&flags,0,sizeof flags);memset(&iflags,0,sizeof iflags);
 memset(pool,0,sizeof pool);memset(mpool,0,sizeof mpool);memset(fruitpool,0,sizeof fruitpool);memset(trap_pool,0,sizeof trap_pool);memset(cemeterypool,0,sizeof cemeterypool);memset(extras,0,sizeof extras);memset(mextras,0,sizeof mextras);memset(objects,0,sizeof objects);memset(mons,0,sizeof mons);memset(opts,0,sizeof opts);
 tracebuf[0]=input[0]=0;seed=12345;random_count=0;windowprocs.wp_id=wp_tty;
 u.uz.dnum=0;u.uz.dlevel=3;u.ux=40;u.uy=10;flags.bones=1;opts[0]=3;opts[1]=50;opts[6]=20;opts[7]=12;opts[16]=1;svd.dungeons[0].boneid='D';
 for(int i=0;i<16;i++){pool[i].otyp=EGG;pool[i].quan=1;pool[i].o_id=100+i;pool[i].corpsenm=NON_PM;}
 for(int i=0;i<8;i++){mpool[i].m_id=10+i;mpool[i].data=&mons[0];mpool[i].cham=NON_PM;}
 for(int i=0;i<4;i++)fruitpool[i].fid=-i-1;
}
void probe_option(int index,int value){opts[index]=value;if(index==19)special.boneid=value;if(index==20)svd.dungeons[0].boneid=value;if(index==21)windowprocs.wp_id=value;if(index==22)seed=value;}
void probe_link(int kind,int index,int next){switch(kind){case 0:pool[index].nobj=next<0?0:&pool[next];break;case 1:gi.invent=next<0?0:&pool[next];break;case 2:pool[index].cobj=next<0?0:&pool[next];break;case 3:mpool[index].minvent=next<0?0:&pool[next];break;case 4:gf.ftrap=next<0?0:&trap_pool[next];break;case 5:trap_pool[index].ntrap=next<0?0:&trap_pool[next];break;case 6:svl.level.bonesinfo=next<0?0:&cemeterypool[next];break;case 7:cemeterypool[index].next=next<0?0:&cemeterypool[next];break;default:abort();}}
void probe_name(int index,int value){pool[index].oextra=&extras[index];snprintf(names[index],BUFSZ,"name-%d",index);extras[index].oname=value?names[index]:0;}
void probe_omonst(int index){pool[index].oextra=&extras[index];extras[index].omonst=&mpool[0];}
void probe_pm(int index,unsigned long flags,unsigned geno){mons[index].mflags2=flags;mons[index].geno=geno;}
void probe_known(int typ,int known){objects[typ].oc_uses_known=known;}
void probe_trap(int index,int type){trap_pool[index].ttyp=type;}
void probe_cemetery(int index,const char*who){strncpy(cemeterypool[index].who,who,sizeof cemeterypool[index].who-1);}
int probe_action(int op,int a,int b){switch(op){case 0:sanitize_name(input);return 0;case 1:return can_make_bones();case 2:return no_bones_level(&u.uz);case 3:goodfruit(a);return 0;case 4:resetobjs(a<0?0:&pool[a],b);return 0;case 5:set_ghostly_objlist(a<0?0:&pool[a]);return 0;case 6:fix_ghostly_obj(&pool[a]);return 0;case 7:newebones(&mpool[a]);return 0;case 8:free_ebones(&mpool[a]);return 0;case 9:return bones_include_name(input);case 10:drop_upon_death(a<0?0:&mpool[a],b<0?0:&pool[b],41,10);return 0;default:abort();}}
const char*probe_trace(void){return tracebuf;}
const char*probe_snapshot(void){char*p=output;p+=sprintf(p,"hero:%d,%d,%d,%d,%d,%d;inv:%d;floor:%d;random:%d;",u.twoweap,u.ux,u.uy,u.uz.dnum,u.uz.dlevel,flags.bones,oid(gi.invent),oid(fobj),random_count);
 for(int i=0;i<16;i++){struct obj*o=&pool[i];p+=sprintf(p,"o%d:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%ld,%ld,%u,%ld,%d,%d,%d,%d,%d,%d,%d,%d;",i,oid(o->nobj),oid(o->cobj),o->in_use,o->oartifact,o->otyp,o->oclass,o->where,o->no_charge,o->known,o->dknown,o->bknown,o->rknown,o->lknown,o->cknown,o->tknown,o->invlet,o->how_lost,o->corpsenm,o->age,o->quan,o->owt,o->owornmask,o->spe,o->nomerge,o->lamplit,o->ghostly,o->ox,o->oy,has_oname(o)?1:0,has_omonst(o)?1:0);}
 for(int i=0;i<8;i++){p+=sprintf(p,"m%d:%d,%u;",i,oid(mpool[i].minvent),has_ebones(&mpool[i])?EBONES(&mpool[i])->parentmid:0);}
 for(int i=0;i<4;i++)p+=sprintf(p,"f%d:%d;",i,fruitpool[i].fid);return output;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return SIZE(bones_layout);}
const char*probe_layout_name(int i){return bones_layout[i].name;}
size_t probe_layout_value(int i){return bones_layout[i].value;}

const char *probe_time_bridge(time_t when){return yyyymmddhhmmss(when);}
