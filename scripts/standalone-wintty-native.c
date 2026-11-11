/* Include this original owner alone, retaining its translation-unit macros. */
#include "wintty.c"
#include <stdint.h>
uintptr_t probe_wintty_callback(int i){switch(i){
#include "wintty-callbacks.inc"
}return 0;}
const volatile void *probe_wintty_global(int i){switch(i){
#include "wintty-globals.inc"
}return NULL;}
unsigned long probe_wintty_owned_size(int i){switch(i){
#include "wintty-sizes.inc"
}return 0;}
