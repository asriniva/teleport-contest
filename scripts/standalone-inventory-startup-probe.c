/* Observe configured original header expressions; no replacement policy. */
#include "hack.h"
int probe_inventory_macro(struct obj *obj,int index){switch(index){
case 0:return is_pole(obj);
case 1:return is_launcher(obj);
case 2:return is_ammo(obj);
case 3:return is_spear(obj);
case 4:return Is_container(obj);
case 5:return is_graystone(obj);
case 6:return is_shield(obj);
case 7:return is_helmet(obj);
case 8:return is_gloves(obj);
case 9:return is_shirt(obj);
case 10:return is_cloak(obj);
case 11:return is_boots(obj);
case 12:return is_suit(obj);
case 13:return is_weptool(obj);
case 14:return is_missile(obj);
case 15:return bimanual(obj);
default:return 0;}}
