#include "abi.h"
#include <stddef.h>
static struct utility_tilemap utility_map[MAX_GLYPH];
static struct tiles_used *utility_list[2500];
static char utility_name[BUFSZ];
void *tm_storage(int i){switch(i){case 0:return utility_map;case 1:return utility_list;case 2:return utility_name;case 3:return mons;case 4:return obj_descr;case 5:return (void*)defsyms;}return 0;}
FILE *tm_stderr(void){return stderr;}
long tm_layout(int i){static const long v[]={BUFSZ,NUMMONS,NUM_OBJECTS,MAX_GLYPH,MAXPCHARS+1,sizeof(void*),sizeof(int),sizeof(struct permonst),offsetof(struct permonst,pmnames),sizeof(struct objdescr),offsetof(struct objdescr,oc_name),offsetof(struct objdescr,oc_descr),sizeof(struct symdef),offsetof(struct symdef,explanation),sizeof(struct utility_tilemap),offsetof(struct utility_tilemap,tilenum),sizeof(struct tiles_used),offsetof(struct tiles_used,tilenum),offsetof(struct tiles_used,src),offsetof(struct tiles_used,file_entry),offsetof(struct tiles_used,tilenam),offsetof(struct tiles_used,references),sizeof(((struct tiles_used*)0)->tilenam),sizeof(((struct tiles_used*)0)->references),MON_GLYPH,OBJ_GLYPH,OTH_GLYPH,MALE,FEMALE,NEUTRAL,S_stone,main_walls,mines_walls,S_vwall,S_trwall,S_ndoor,S_brdnladder,S_altar,altar_unaligned,altar_other,S_grave,S_arrow_trap,MAXTCHARS,NUM_ZAP,S_digbeam,S_goodpos,S_sw_tl,S_sw_br,expl_dark,expl_frosty,S_expl_tl,S_expl_br,WARNCOUNT,sokoban_walls,TRUE,FALSE,EXIT_FAILURE};return i>=0&&i<sizeof(v)/sizeof(v[0])?v[i]:-1;}
int tm_sprintf0(char*p,const char*f){return sprintf(p,f);}
int tm_sprintfp(char*p,const char*f,const char*a){return sprintf(p,f,a);}
int tm_sprintfpp(char*p,const char*f,const char*a,const char*b){return sprintf(p,f,a,b);}
int tm_sprintfi(char*p,const char*f,int a){return sprintf(p,f,a);}
int tm_sprintfii(char*p,const char*f,int a,int b){return sprintf(p,f,a,b);}
int tm_sprintfpii(char*p,const char*f,const char*a,int b,int c){return sprintf(p,f,a,b,c);}
void tm_snprintf0(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("tilename",211,out,size,fmt,a0,a1);}
void tm_snprintf1(char*out,size_t size,const char*fmt,const char* a0){nh_snprintf("tilename",213,out,size,fmt,a0);}
void tm_snprintf2(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("tilename",221,out,size,fmt,a0,a1);}
void tm_snprintf3(char*out,size_t size,const char*fmt,const char* a0){nh_snprintf("tilename",223,out,size,fmt,a0);}
void tm_snprintf4(char*out,size_t size,const char*fmt,int a0){nh_snprintf("acceptable_tilename",1469,out,size,fmt,a0);}
void tm_snprintf5(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("add_tileref",1506,out,size,fmt,a0,a1);}
void tm_snprintf6(char*out,size_t size,const char*fmt,const char* a0,const char* a1,int a2){nh_snprintf("add_tileref",1517,out,size,fmt,a0,a1,a2);}
void tm_snprintf7(char*out,size_t size,const char*fmt,int a0){nh_snprintf("add_tileref",1518,out,size,fmt,a0);}
void tm_snprintf8(char*out,size_t size,const char*fmt,const char* a0,const char* a1){nh_snprintf("add_tileref",1523,out,size,fmt,a0,a1);}
int tm_print0(FILE*p,const char*f){return fprintf(p,f);}
int tm_printp(FILE*p,const char*f,const char*a){return fprintf(p,f,a);}
int tm_printz(FILE*p,const char*f,size_t n){return fprintf(p,f,n);}
int tm_printlist(FILE*p,const char*f,int a,const char*b,int c,const char*d,const char*e){return fprintf(p,f,a,b,c,d,e);}
void tm_exit(int n){exit(n);}
