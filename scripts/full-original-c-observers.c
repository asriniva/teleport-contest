/* Read-only observations; DECL and all game state are owned by original C. */
#include "decl.c"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
int full_global_count(void){return FULL_GLOBAL_COUNT;}
const char *full_global_name(int i){switch(i){
#include "full-global-names.inc"
default:abort();}}
const void *full_global_address(int i){switch(i){
#include "full-global-addresses.inc"
default:abort();}}
size_t full_global_size(int i){switch(i){
#include "full-global-sizes.inc"
default:abort();}}
long full_moves(void){return svm.moves;}
int full_hero_x(void){return u.ux;}
int full_hero_y(void){return u.uy;}
int full_hero_hp(void){return u.uhp;}
int full_hero_level(void){return u.ulevel;}
unsigned full_hero_inventory_id(void){return gi.invent?gi.invent->o_id:0;}
