/* Typed ABI only; all region geometry, list, lifecycle and damage policy is JS. */
#include "hack.h"
void *teleport_region_global(int i){switch(i){case 0:return &gr;case 1:return &gm;case 2:return &svn;case 3:return &svm;case 4:return &gg;case 5:return &u;case 6:return &gy;case 7:return &gi;case 8:return &svc;case 9:return &iflags;case 10:return (void*)&cg;case 11:return &svl;case 12:return mons;case 13:return &gv;}return 0;}
unsigned teleport_region_monster_bit(struct monst *m,int i){return i?m->mblinded:m->mcansee;}
void teleport_region_set_monster_bit(struct monst*m,int i,unsigned v){if(i)m->mblinded=v;else m->mcansee=v;}
unsigned teleport_region_hero_bit(int i){return i?u.uinwater:u.uswallow;}
void teleport_region_set_hero_bit(int i,unsigned v){if(i)u.uinwater=v;else u.uswallow=v;}
void *teleport_region_blindfold(void){return ublindf;}
const char *teleport_region_something(void){return Something;}
void teleport_region_free(void*p){free(p);}
void *teleport_region_string_alloc(size_t n){return malloc(n);}
void teleport_region_putstr(winid w,int a,const char*s){putstr(w,a,s);}
void teleport_region_message(int kind,const char *fmt,const char*a,const char*b){switch(kind){case 0:pline(fmt,a,b);break;case 1:pline_The(fmt,a,b);break;case 2:You(fmt,a,b);break;case 3:Your(fmt,a,b);break;case 4:You_see(fmt,a,b);break;case 5:You_feel(fmt,a,b);break;}}
void teleport_region_impossible(const char *fmt,const char*s,unsigned n){impossible(fmt,s,n);}
void teleport_region_impossible_int(const char *fmt,int n){impossible(fmt,n);}
void teleport_region_format_long(char*out,const char*fmt,long n){Sprintf(out,fmt,n);}
void teleport_region_format_int(char*out,const char*fmt,int n){Sprintf(out,fmt,n);}
void teleport_region_format_pp(char*out,const char*fmt,const char*a,const char*b){Sprintf(out,fmt,a,b);}
void teleport_region_format_piiii(char*out,const char*fmt,const char*a,int x,int y,int xx,int yy){Sprintf(out,fmt,a,x,y,xx,yy);}
void teleport_region_format_ll(char*out,const char*fmt,long a,long b){Sprintf(out,fmt,a,b);}
int teleport_region_rng(int kind,int a,int b,int caller,int line){const char*name=caller==0?"inside_gas_cloud":caller==1?"create_gas_cloud":"region_safety";if(rng_log_enabled())rng_log_set_caller("region.c",line,name);if(kind==0)return (rn2)(a);if(kind==1)return (rnd)(a);return (d)(a,b);}
#define TELEPORT_REGION_SF(T) void teleport_region_sfo_##T(NHFILE*f,void*p,const char*s){Sfo_##T(f,p,s);} void teleport_region_sfi_##T(NHFILE*f,void*p,const char*s){Sfi_##T(f,p,s);}
TELEPORT_REGION_SF(long)
TELEPORT_REGION_SF(int)
TELEPORT_REGION_SF(short)
TELEPORT_REGION_SF(unsigned)
TELEPORT_REGION_SF(boolean)
TELEPORT_REGION_SF(nhrect)
TELEPORT_REGION_SF(any)
#undef TELEPORT_REGION_SF
void teleport_region_sfo_char(NHFILE*f,void*p,const char*s,int n){Sfo_char(f,p,s,n);}
void teleport_region_sfi_char(NHFILE*f,void*p,const char*s,int n){Sfi_char(f,p,s,n);}

void teleport_region_pline1(const char*s){pline1(s);}
