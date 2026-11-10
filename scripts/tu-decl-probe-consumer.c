/* This TU contains no DECL source include or initializer values. Compile separately without LTO. */
#include "hack.h"
#include <stdint.h>
static uint64_t initial[64],current[64];static int ran;
static uint64_t hash(const char*s){uint64_t h=1469598103934665603ULL;if(!s)return 0;while(*s)h=(h^(unsigned char)*s++)*1099511628211ULL;return h;}
static void capture(uint64_t*out){int i,n=0;uint64_t h;for(i=0;i<10;i++)out[n++]=(uint64_t)(int64_t)xdir[i];for(i=0;i<10;i++)out[n++]=(uint64_t)(int64_t)ydir[i];for(i=0;i<10;i++)out[n++]=(uint64_t)(int64_t)zdir[i];for(i=0;i<8;i++)out[n++]=(uint64_t)(int64_t)dirs_ord[i];
h=0;for(i=0;i<NUM_NHCB;i++)h=h*31+hash(nhcb_name[i]);out[n++]=h;
h=0;for(i=0;i<16;i++)h=h*31+hash(c_obj_colors[i]);out[n++]=h;
h=0;for(i=0;i<22;i++)h=h*31+hash(materialnm[i]);out[n++]=h;
out[n++]=hash(hexdd);out[n++]=hash(disclosure_options);out[n++]=hash(vowels);out[n++]=hash(quitchars);out[n++]=hash(ynchars);out[n++]=hash(c_color_names.c_black);out[n++]=hash(c_common_strings.c_nothing_happens);
out[n++]=&hands_obj!=&cg.zeroobj;out[n++]=sizeof cg;out[n++]=cg.zeroobj.otyp;out[n++]=cg.zeromonst.mhp;out[n++]=shield_static[0];out[n++]=shield_static[20];out[n++]=WIN_MESSAGE;out[n++]=program_state.gameover;}
__attribute__((constructor)) static void foreign_before_source(void){capture(initial);ran++;}
int probe_ctor_ran(void){return ran;}
uint64_t probe_foreign(int which,int n){capture(current);return which?current[n]:initial[n];}
