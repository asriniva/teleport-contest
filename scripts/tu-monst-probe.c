#include "hack.h"
#include <string.h>
#include <emscripten/stack.h>
#include "tu-monst-layout.h"
extern const struct attack c_sa_yes[NATTK],c_sa_no[NATTK];
static const char *field_names[]={"pmidx","mlet","mlevel","mmove","ac","mr","maligntyp","geno","cwt","cnutrit","msound","msize","mresists","mconveys","mflags1","mflags2","mflags3","difficulty","mcolor"};
static const unsigned char field_unsigned[]={0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1};
static char name_empty[]="",name_one[]="fixture name",name_two[]="second fixture name";
void probe_init(void){monst_globals_init();}
int probe_count(void){return NUMMONS+1;}
int probe_field_count(void){return SIZE(field_names);}
const char *probe_field_name(int f){return field_names[f];}
int probe_field_kind(int f){return field_unsigned[f];}
unsigned long probe_value(int row,int f){struct permonst *m=&mons[row];switch(f){
case 0:return (unsigned long)m->pmidx;
case 1:return (unsigned long)m->mlet;
case 2:return (unsigned long)m->mlevel;
case 3:return (unsigned long)m->mmove;
case 4:return (unsigned long)m->ac;
case 5:return (unsigned long)m->mr;
case 6:return (unsigned long)m->maligntyp;
case 7:return (unsigned long)m->geno;
case 8:return (unsigned long)m->cwt;
case 9:return (unsigned long)m->cnutrit;
case 10:return (unsigned long)m->msound;
case 11:return (unsigned long)m->msize;
case 12:return (unsigned long)m->mresists;
case 13:return (unsigned long)m->mconveys;
case 14:return (unsigned long)m->mflags1;
case 15:return (unsigned long)m->mflags2;
case 16:return (unsigned long)m->mflags3;
case 17:return (unsigned long)m->difficulty;
case 18:return (unsigned long)m->mcolor;
default:return 0;}}
const char *probe_name(int row,int gender){return mons[row].pmnames[gender];}
static unsigned get_attack(const struct attack *a,int field){switch(field){case 0:return a->aatyp;case 1:return a->adtyp;case 2:return a->damn;default:return a->damd;}}
unsigned probe_attack(int row,int attack,int field){return get_attack(&mons[row].mattk[attack],field);}
unsigned probe_constant_attack(int which,int attack,int field){return get_attack(which?&c_sa_yes[attack]:&c_sa_no[attack],field);}
const void *probe_constants(int which){return which?c_sa_yes:c_sa_no;}
void *probe_monsters(void){return mons;}
void probe_poison(unsigned seed){size_t i;unsigned char *p=(unsigned char *)mons;for(i=0;i<sizeof mons;i++){seed=seed*1664525U+1013904223U;p[i]=seed>>24;}}
void probe_mutate(int row,int field,unsigned long value){struct permonst *m=&mons[row];switch(field){
case 0:{enum monnums index=(enum monnums)value;memcpy((void *)&m->pmidx,&index,sizeof index);break;}
case 1:m->mlet=value;break;
case 2:m->mlevel=value;break;
case 3:m->mmove=value;break;
case 4:m->ac=value;break;
case 5:m->mr=value;break;
case 6:m->maligntyp=value;break;
case 7:m->geno=value;break;
case 8:m->cwt=value;break;
case 9:m->cnutrit=value;break;
case 10:m->msound=value;break;
case 11:m->msize=value;break;
case 12:m->mresists=value;break;
case 13:m->mconveys=value;break;
case 14:m->mflags1=value;break;
case 15:m->mflags2=value;break;
case 16:m->mflags3=value;break;
case 17:m->difficulty=value;break;
case 18:m->mcolor=value;break;
}}
void probe_mutate_attack(int row,int attack,int field,unsigned value){struct attack *a=&mons[row].mattk[attack];switch(field){case 0:a->aatyp=value;break;case 1:a->adtyp=value;break;case 2:a->damn=value;break;case 3:a->damd=value;break;}}
void probe_names(int row,int mode){mons[row].pmnames[0]=mode?name_empty:NULL;mons[row].pmnames[1]=mode?name_one:NULL;mons[row].pmnames[2]=mode==2?name_one:mode?name_two:NULL;}
size_t probe_stack(void){return emscripten_stack_get_current();}
