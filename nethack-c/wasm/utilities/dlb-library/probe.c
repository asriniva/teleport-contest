#include "config.h"
#include "dlb.h"
#include <stdint.h>
extern void *utility_library_storage(void);
extern FILE *utility_fopen_datafile(const char*,const char*,int);
FILE *fopen_datafile(const char*p,const char*m,int prefix){return utility_fopen_datafile(p,m,prefix);}
#ifdef MIXED_LIBRARY
extern boolean teleport_library_test_readlibdir(library * lp);
extern boolean teleport_library_test_find_file(const char * name,library ** lib,long * startp,long * sizep);
extern boolean open_library(const char * lib_name,library * lp);
extern void close_library(library * lp);
extern boolean teleport_library_test_lib_dlb_init(void);
extern void teleport_library_test_lib_dlb_cleanup(void);
extern boolean teleport_library_test_lib_dlb_fopen(dlb * dp,const char * name,const char * mode);
extern int teleport_library_test_lib_dlb_fclose(dlb * dp);
extern int teleport_library_test_lib_dlb_fread(char * buf,int size,int quan,dlb * dp);
extern int teleport_library_test_lib_dlb_fseek(dlb * dp,long pos,int whence);
extern char * teleport_library_test_lib_dlb_fgets(char * buf,int len,dlb * dp);
extern int teleport_library_test_lib_dlb_fgetc(dlb * dp);
extern long teleport_library_test_lib_dlb_ftell(dlb * dp);
extern boolean dlb_init(void);
extern void dlb_cleanup(void);
extern dlb * dlb_fopen(const char * name,const char * mode);
extern int dlb_fclose(dlb * dp);
extern int dlb_fread(char * buf,int size,int quan,dlb * dp);
extern int dlb_fseek(dlb * dp,long pos,int whence);
extern char * dlb_fgets(char * buf,int len,dlb * dp);
extern int dlb_fgetc(dlb * dp);
extern long dlb_ftell(dlb * dp);
#else
#ifndef UTILITY_DLB_ORIGINAL_SOURCE
#error "Pass the explicit original source path from the utility build script"
#endif
#include UTILITY_DLB_ORIGINAL_SOURCE
#define teleport_library_test_readlibdir readlibdir
#define teleport_library_test_find_file find_file
#define teleport_library_test_lib_dlb_init lib_dlb_init
#define teleport_library_test_lib_dlb_cleanup lib_dlb_cleanup
#define teleport_library_test_lib_dlb_fopen lib_dlb_fopen
#define teleport_library_test_lib_dlb_fclose lib_dlb_fclose
#define teleport_library_test_lib_dlb_fread lib_dlb_fread
#define teleport_library_test_lib_dlb_fseek lib_dlb_fseek
#define teleport_library_test_lib_dlb_fgets lib_dlb_fgets
#define teleport_library_test_lib_dlb_fgetc lib_dlb_fgetc
#define teleport_library_test_lib_dlb_ftell lib_dlb_ftell
#endif
long long probe_action(int n,uintptr_t a0,uintptr_t a1,uintptr_t a2,uintptr_t a3){switch(n){
case 0:return (long long)teleport_library_test_readlibdir((library *)a0);
case 1:return (long long)teleport_library_test_find_file((const char *)a0,(library **)a1,(long *)a2,(long *)a3);
case 2:return (long long)open_library((const char *)a0,(library *)a1);
case 3:close_library((library *)a0);return 0;
case 4:return (long long)teleport_library_test_lib_dlb_init();
case 5:teleport_library_test_lib_dlb_cleanup();return 0;
case 6:return (long long)teleport_library_test_lib_dlb_fopen((dlb *)a0,(const char *)a1,(const char *)a2);
case 7:return (long long)teleport_library_test_lib_dlb_fclose((dlb *)a0);
case 8:return (long long)teleport_library_test_lib_dlb_fread((char *)a0,(int)a1,(int)a2,(dlb *)a3);
case 9:return (long long)teleport_library_test_lib_dlb_fseek((dlb *)a0,(long)a1,(int)a2);
case 10:return (long long)teleport_library_test_lib_dlb_fgets((char *)a0,(int)a1,(dlb *)a2);
case 11:return (long long)teleport_library_test_lib_dlb_fgetc((dlb *)a0);
case 12:return (long long)teleport_library_test_lib_dlb_ftell((dlb *)a0);
case 13:return (long long)dlb_init();
case 14:dlb_cleanup();return 0;
case 15:return (long long)dlb_fopen((const char *)a0,(const char *)a1);
case 16:return (long long)dlb_fclose((dlb *)a0);
case 17:return (long long)dlb_fread((char *)a0,(int)a1,(int)a2,(dlb *)a3);
case 18:return (long long)dlb_fseek((dlb *)a0,(long)a1,(int)a2);
case 19:return (long long)dlb_fgets((char *)a0,(int)a1,(dlb *)a2);
case 20:return (long long)dlb_fgetc((dlb *)a0);
case 21:return (long long)dlb_ftell((dlb *)a0);
}return -999;}
static library external_library;
static dlb external_handle;
static char bytes[4096];
static long outputs[4];
void *probe_pointer(int n){switch(n){case 0:return &external_library;case 1:return &external_handle;case 2:return bytes;case 3:return outputs;
#ifdef MIXED_LIBRARY
case 4:return utility_library_storage();
#else
case 4:return dlb_libs;
#endif
}return 0;}
