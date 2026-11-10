/* EARLYARG ABI/storage only. Option parsing and catalogue data live in JS. */
#include "hack.h"
#include "tu-earlyarg-support.h"
#ifndef TELEPORT_REFERENCE_EARLYARG
struct enum_dump monsdump[TELEPORT_EARLYARG_MONSDUMP_COUNT];
struct enum_dump objdump[TELEPORT_EARLYARG_OBJDUMP_COUNT];
#else
extern struct enum_dump monsdump[], objdump[];
#endif
static char teleport_earlyarg_novalue[10];
void *teleport_earlyarg_storage(int index)
{ return index == 0 ? (void *) monsdump : index == 1 ? (void *) objdump : (void *) teleport_earlyarg_novalue; }
void *teleport_earlyarg_global(int index)
{
    switch(index) { case 0:return &gc;case 1:return &gd;case 2:return &gh;
    case 3:return &program_state;case 4:return &iflags;case 5:return &ARGV0;default:return 0; }
}
const char *teleport_earlyarg_usagehelp(void) { return USAGEHELP; }
FILE *teleport_earlyarg_stdout(void) { return stdout; }
void teleport_earlyarg_config_error(const char *format,const char *arg) { config_error_add(format,arg); }
void teleport_earlyarg_error(const char *format) { error(format); }
void teleport_earlyarg_free(void *pointer) { free(pointer); }
void teleport_earlyarg_raw_print(const char *text) { raw_print(text); }
void teleport_earlyarg_raw_p(const char *format,const char *arg) { raw_printf(format,arg); }
void teleport_earlyarg_raw_pp(const char *format,const char *a,const char *b) { raw_printf(format,a,b); }
void teleport_earlyarg_raw_pipip(const char *format,const char *a,int width,const char *b,int value,const char *c)
{ raw_printf(format,a,width,b,value,c); }
void teleport_earlyarg_snprintf(char *buffer,size_t size,const char *format,int value)
{ nh_snprintf(TELEPORT_EARLYARG_SNPRINTF_FUNCTION,TELEPORT_EARLYARG_SNPRINTF_LINE,buffer,size,format,value); }
#ifdef TELEPORT_EARLYARG_LITERAL_CAPACITY
static char teleport_earlyarg_literals[TELEPORT_EARLYARG_LITERAL_CAPACITY];
void *teleport_earlyarg_literal_storage(void) { return teleport_earlyarg_literals; }
size_t teleport_earlyarg_literal_capacity(void) { return sizeof teleport_earlyarg_literals; }
#endif
