/* SFBASE typed ABI, zero-only external backing, and libc calls only. */
#include "hack.h"
#include "sfprocs.h"
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sfbase-source-data.h"
extern struct sf_structlevel_procs zerosfoprocs,zerosfiprocs;
extern struct sf_fieldlevel_procs zerosfoflprocs,zerosfiflprocs;
#ifndef SFBASE_REFERENCE
struct sf_structlevel_procs sfoprocs[NUM_SAVEFORMATS],sfiprocs[NUM_SAVEFORMATS],zerosfoprocs={0},zerosfiprocs={0};
struct sf_fieldlevel_procs sfoflprocs[NUM_SAVEFORMATS],sfiflprocs[NUM_SAVEFORMATS],zerosfoflprocs={0},zerosfiflprocs={0};
#endif
void *teleport_sfbase_global(int index){switch(index){
case 0:return (void*)(sfoprocs);
case 1:return (void*)(sfiprocs);
case 2:return (void*)(sfoflprocs);
case 3:return (void*)(sfiflprocs);
case 4:return (void*)(&zerosfoprocs);
case 5:return (void*)(&zerosfiprocs);
case 6:return (void*)(&zerosfoflprocs);
case 7:return (void*)(&zerosfiflprocs);
case 8:return (void*)(&historical_sfo_procs);
case 9:return (void*)(&historical_sfi_procs);
default:abort();}}
void teleport_sfbase_copy(void*to,const void*from,size_t n){memmove(to,from,n);}
static unsigned char sfbase_static_buffers[TELEPORT_SFBASE_BUFFER_BYTES];
char *teleport_sfbase_buffer(int index){switch(index){
case 0:return (char*)sfbase_static_buffers+0;
case 1:return (char*)sfbase_static_buffers+120;
case 2:return (char*)sfbase_static_buffers+140;
case 3:return (char*)sfbase_static_buffers+160;
case 4:return (char*)sfbase_static_buffers+180;
case 5:return (char*)sfbase_static_buffers+200;
case 6:return (char*)sfbase_static_buffers+220;
case 7:return (char*)sfbase_static_buffers+240;
case 8:return (char*)sfbase_static_buffers+260;
case 9:return (char*)sfbase_static_buffers+280;
case 10:return (char*)sfbase_static_buffers+300;
case 11:return (char*)sfbase_static_buffers+320;
case 12:return (char*)sfbase_static_buffers+340;
case 13:return (char*)sfbase_static_buffers+360;
case 14:return (char*)sfbase_static_buffers+380;
case 15:return (char*)sfbase_static_buffers+400;
case 16:return (char*)sfbase_static_buffers+420;
case 17:return (char*)sfbase_static_buffers+440;
case 18:return (char*)sfbase_static_buffers+460;
case 19:return (char*)sfbase_static_buffers+480;
case 20:return (char*)sfbase_static_buffers+500;
case 21:return (char*)sfbase_static_buffers+520;
case 22:return (char*)sfbase_static_buffers+540;
case 23:return (char*)sfbase_static_buffers+560;
case 24:return (char*)sfbase_static_buffers+580;
case 25:return (char*)sfbase_static_buffers+600;
default:abort();}}
const char *teleport_sfbase_pri(int index){switch(index){case 0:return PRId32;case 1:return PRId64;case 2:return PRIu32;case 3:return PRIu64;default:abort();}}
void teleport_sfbase_format_i32(int site,char*out,size_t n,const char*format,int value){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,value);}
void teleport_sfbase_format_u32(int site,char*out,size_t n,const char*format,unsigned value){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,value);}
void teleport_sfbase_format_i64(int site,char*out,size_t n,const char*format,int64_t value){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,value);}
void teleport_sfbase_format_u64(int site,char*out,size_t n,const char*format,uint64_t value){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,value);}
void teleport_sfbase_format_long(int site,char*out,size_t n,const char*format,long value){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,value);}
void teleport_sfbase_format_ulong(int site,char*out,size_t n,const char*format,unsigned long value){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,value);}
void teleport_sfbase_format_text(int site,char*out,size_t n,const char*format,const char*value){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,value);}
void teleport_sfbase_format_ten(int site,char*out,size_t n,const char*format,unsigned a,unsigned b,unsigned c,unsigned d,unsigned e,unsigned f,unsigned g,unsigned h,unsigned i,unsigned j){nh_snprintf(sfbase_site_names[site],sfbase_site_lines[site],out,n,format,a,b,c,d,e,f,g,h,i,j);}
int teleport_sfbase_fprintf(FILE*fp,const char*format,long count,const char*tag,size_t size,int n,const char*text){return fprintf(fp,format,count,tag,size,n,text);}
static char sfbase_literals[TELEPORT_SFBASE_LITERAL_BYTES];
char *teleport_sfbase_literal_storage(void){return sfbase_literals;}
size_t teleport_sfbase_literal_capacity(void){return sizeof sfbase_literals;}
