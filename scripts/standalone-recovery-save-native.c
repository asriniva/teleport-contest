/* Test-only calls into actual private SAVE policies, one original TU. */
#include "save.c"
void recovery_saveobjchn(NHFILE *f,struct obj **head){saveobjchn(f,head);}
void recovery_savemonchn(NHFILE *f,struct monst *head){savemonchn(f,head);}
struct obj *recovery_newobj(void){return newobj();}
struct monst *recovery_newmonst(void){return newmonst();}
