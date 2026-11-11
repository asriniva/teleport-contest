/* Original EAT included unchanged so observers can invoke source-private actions. */
#include "eat.c"
uintptr_t probe_eat_action(int action,struct obj *obj,int value){switch(action){
case 0:return(uintptr_t)touchfood(obj);case 1:start_eating(obj,(boolean)value);return 0;
case 2:return(uintptr_t)eatfood();case 3:return(uintptr_t)unfaint();
case 4:return(uintptr_t)eatmdone();case 5:done_eating((boolean)value);return 0;
case 6:return(uintptr_t)bite();default:abort();}}
int probe_eat_occupation(void){return go.occupation?(*go.occupation)():-1;}
uintptr_t probe_eat_callback(int i){switch(i){case 0:return(uintptr_t)eatmdone;case 1:return(uintptr_t)eatfood;case 2:return(uintptr_t)opentin;case 3:return(uintptr_t)unfaint;case 4:return(uintptr_t)Hear_again;case 5:return(uintptr_t)Finish_digestion;default:return 0;}}
int probe_eat_private(void){return getobj_else;}
