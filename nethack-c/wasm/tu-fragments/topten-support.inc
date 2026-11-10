/* Typed fields/header/native dependency/varargs ABI only; no TOPTEN algorithms. */
#include "hack.h"
#include "topten-types.h"
static struct teleport_toptenentry teleport_topten_zero,teleport_topten_buffer;
void*teleport_topten_storage(int i){return i?&teleport_topten_buffer:&teleport_topten_zero;}
const void*teleport_topten_global(int i){switch(i){case 0:return &u;case 1:return &gm;case 2:return svk.killer.name;case 3:return &svk.killer.format;case 4:return &gt.toptenwin;case 5:return &iflags.toptenwin;case 6:return &program_state;case 7:return &sysopt;case 8:return &gu.urole;case 9:return &gu.urace;case 10:return genders;case 11:return aligns;case 12:return svp.plname;case 13:return &ubirthday;case 14:return &urealtime.realtime;case 15:return &urealtime.finish_time;case 16:return &svm.moves;case 17:return &flags;case 18:return &gi.invent;case 19:return &astral_level;case 20:return &knox_level;case 21:return &wiz1_level;case 22:return svd.dungeons;case 23:return &gh.hname;case 24:return roles;default:return 0;}}
const char*teleport_topten_path(int i){return i==0?RECORD:i==1?LOGFILE:XLOGFILE;}
int teleport_topten_female(void){return flags.female;}
int teleport_topten_monster_female(struct monst*m){return m->female;}
void teleport_topten_set_monster_female(struct monst*m,unsigned n){m->female=n;}
void teleport_topten_free(void*p){free(p);}
int teleport_topten_close(FILE*f){return fclose(f);}
winid teleport_topten_create_window(int type){return create_nhwindow(type);}
void teleport_topten_display_window(winid w,boolean b){display_nhwindow(w,b);}
void teleport_topten_destroy_window(winid w){destroy_nhwindow(w);}
void teleport_topten_putstr(winid w,int a,const char*s){putstr(w,a,s);}
void teleport_topten_raw_print(const char*s){raw_print(s);}
void teleport_topten_raw_print_bold(const char*s){raw_print_bold(s);}
int teleport_topten_scan(int kind,void*input,const char*fmt,const void*const*args){if(kind)return sscanf((char*)input,fmt,args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8],args[9],args[10],args[11],args[12]);return fscanf((FILE*)input,fmt,args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8],args[9],args[10],args[11],args[12]);}
static const char*const teleport_topten_callers[]={"get_rnd_toptenentry","tt_doppel"};
int teleport_topten_rng(int kind,int n,int base,int line,int caller){if(rng_log_enabled())rng_log_set_caller("topten.c",line,teleport_topten_callers[caller]);switch(kind){case 0:return(rnd)(n);case 1:return(rn2)(n);default:return(rn2)(n)+base;}}

unsigned teleport_topten_Strlen(const char*s,int line,int fn){static const char*const names[]={"formatkiller","outentry","prscore"};return Strlen_(s,names[fn],line);}



/* Source-derived typed printf shapes. */
#define TOPTEN_ABI_OUTPUT(...) do{switch(kind){case 0:sprintf((char*)target,fmt,##__VA_ARGS__);break;case 1:fprintf((FILE*)target,fmt,##__VA_ARGS__);break;case 2:raw_printf(fmt,##__VA_ARGS__);break;case 3:impossible(fmt,##__VA_ARGS__);break;case 4:nh_snprintf("outentry",line,(char*)target,cap,fmt,##__VA_ARGS__);break;}}while(0)
void teleport_topten_output(int kind,int shape,void*target,size_t cap,int line,const char*fmt,const uint64_t*args){switch(shape){
case 0:TOPTEN_ABI_OUTPUT((char*)0);break;
case 1:TOPTEN_ABI_OUTPUT(((int)args[0]));break;
case 2:TOPTEN_ABI_OUTPUT(((const char*)(uintptr_t)args[0]));break;
case 3:TOPTEN_ABI_OUTPUT(((int)args[0]),((int)args[1]),((int)args[2]),((long)args[3]),((int)args[4]),((int)args[5]),((int)args[6]),((int)args[7]),((int)args[8]),((int)args[9]),((long)args[10]),((long)args[11]),((int)args[12]));break;
case 4:TOPTEN_ABI_OUTPUT(((int)args[0]),((int)args[1]));break;
case 5:TOPTEN_ABI_OUTPUT(((const char*)(uintptr_t)args[0]),((const char*)(uintptr_t)args[1]),((const char*)(uintptr_t)args[2]),((const char*)(uintptr_t)args[3]));break;
case 6:TOPTEN_ABI_OUTPUT(((const char*)(uintptr_t)args[0]),((const char*)(uintptr_t)args[1]));break;
case 7:TOPTEN_ABI_OUTPUT(((int)args[0]),((int)args[1]),((int)args[2]));break;
case 8:TOPTEN_ABI_OUTPUT(((int)args[0]),((long)args[1]),((int)args[2]),((int)args[3]),((int)args[4]),((int)args[5]));break;
case 9:TOPTEN_ABI_OUTPUT(((int)args[0]),((int)args[1]),((int)args[2]),((int)args[3]),((int)args[4]),((int)args[5]));break;
case 10:TOPTEN_ABI_OUTPUT(((int)args[0]),((int)args[1]),((int)args[2]),((long)args[3]),((int)args[4]),((long)args[5]),((int)args[6]),((int)args[7]));break;
case 11:TOPTEN_ABI_OUTPUT(((int)args[0]),((const char*)(uintptr_t)args[1]),((int)args[2]),((const char*)(uintptr_t)args[3]),((int)args[4]),((const char*)(uintptr_t)args[5]),((int)args[6]),((const char*)(uintptr_t)args[7]));break;
case 12:TOPTEN_ABI_OUTPUT(((const char*)(uintptr_t)args[0]),((int)args[1]),((const char*)(uintptr_t)args[2]),((int)args[3]),((const char*)(uintptr_t)args[4]));break;
case 13:TOPTEN_ABI_OUTPUT(((int)args[0]),((const char*)(uintptr_t)args[1]));break;
case 14:TOPTEN_ABI_OUTPUT(((int)args[0]),((long)args[1]),((int)args[2]),((long)args[3]),((int)args[4]),((long)args[5]));break;
case 15:TOPTEN_ABI_OUTPUT(((int)args[0]),((const char*)(uintptr_t)args[1]),((int)args[2]),((const char*)(uintptr_t)args[3]));break;
case 16:TOPTEN_ABI_OUTPUT(((int)args[0]),((long)args[1]));break;
case 17:TOPTEN_ABI_OUTPUT(((long)args[0]));break;
case 18:TOPTEN_ABI_OUTPUT(((int)args[0]),((const char*)(uintptr_t)args[1]),((int)args[2]));break;
case 19:TOPTEN_ABI_OUTPUT(((long)args[0]),((const char*)(uintptr_t)args[1]));break;
case 20:TOPTEN_ABI_OUTPUT(((const char*)(uintptr_t)args[0]),((int)args[1]));break;
}}
#undef TOPTEN_ABI_OUTPUT
static char teleport_topten_literals[2636];
void*teleport_topten_literal_storage(void){return teleport_topten_literals;}
size_t teleport_topten_literal_capacity(void){return sizeof teleport_topten_literals;}
