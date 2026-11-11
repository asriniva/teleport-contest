#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
_Static_assert(CHAR_BIT==8,"STRIPBS char bit width");
_Static_assert(sizeof(void*)==8,"STRIPBS pointer width");
_Static_assert(sizeof(size_t)==8,"STRIPBS size_t width");
size_t teleport_stripbs_fread(void*p,size_t size,size_t count,FILE*stream){return fread(p,size,count,stream);}
int teleport_stripbs_fputc(int ch,FILE*stream){return fputc(ch,stream);}
int teleport_stripbs_fflush(FILE*stream){return fflush(stream);}
int teleport_stripbs_fclose(FILE*stream){return fclose(stream);}
FILE*teleport_stripbs_stdin(void){return stdin;}
FILE*teleport_stripbs_stdout(void){return stdout;}
int teleport_stripbs_errno(void){return errno;}
int teleport_stripbs_metadata(int i){switch(i){case 0:return EOF;case 1:return EXIT_FAILURE;case 2:return EXIT_SUCCESS;case 3:return (char)-1<0;case 4:return sizeof(char);case 5:return sizeof(void*);case 6:return sizeof(size_t);}return -1;}
