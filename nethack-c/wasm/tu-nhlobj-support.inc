/* NHLOBJ ABI only: actual fields, zero registration buffers and callbacks. */
static luaL_Reg teleport_nhlobj_methods[16],teleport_nhlobj_meta[2];
void*teleport_nhlobj_storage(int i){return i?(void*)teleport_nhlobj_meta:(void*)teleport_nhlobj_methods;}
void*teleport_nhlobj_global(int i){switch(i){case 0:return objects;case 1:return (void*)obj_descr;case 2:return mons;case 3:return materialnm;case 4:return (void*)def_oc_syms;case 5:return &svl;default:return &hands_obj;}}
unsigned teleport_nhlobj_object_bit(struct obj*o,int i){switch(i){case 0:return o->cursed;case 1:return o->blessed;case 2:return o->unpaid;case 3:return o->no_charge;case 4:return o->known;case 5:return o->dknown;case 6:return o->bknown;case 7:return o->rknown;case 8:return o->tknown;case 9:return o->odiluted;case 10:return o->oeroded;case 11:return o->oeroded2;case 12:return o->oerodeproof;case 13:return o->olocked;case 14:return o->obroken;case 15:return o->opoisoned;case 16:return o->otrapped;case 17:return o->recharged;case 18:return o->lamplit;case 19:return o->globby;case 20:return o->greased;case 21:return o->nomerge;case 22:return o->how_lost;case 23:return o->in_use;case 24:return o->bypass;case 25:return o->cknown;case 26:return o->lknown;default:return 0;}}
void teleport_nhlobj_set_object_bit(struct obj*o,int i,unsigned v){switch(i){case 0:o->cursed=v;break;case 1:o->blessed=v;break;case 2:o->unpaid=v;break;case 3:o->no_charge=v;break;case 4:o->known=v;break;case 5:o->dknown=v;break;case 6:o->bknown=v;break;case 7:o->rknown=v;break;case 8:o->tknown=v;break;case 9:o->odiluted=v;break;case 10:o->oeroded=v;break;case 11:o->oeroded2=v;break;case 12:o->oerodeproof=v;break;case 13:o->olocked=v;break;case 14:o->obroken=v;break;case 15:o->opoisoned=v;break;case 16:o->otrapped=v;break;case 17:o->recharged=v;break;case 18:o->lamplit=v;break;case 19:o->globby=v;break;case 20:o->greased=v;break;case 21:o->nomerge=v;break;case 22:o->how_lost=v;break;case 23:o->in_use=v;break;case 24:o->bypass=v;break;case 25:o->cknown=v;break;case 26:o->lknown=v;break;default:break;}}
unsigned teleport_nhlobj_class_bit(struct objclass*o,int i){switch(i){case 0:return o->oc_name_known;case 1:return o->oc_merge;case 2:return o->oc_uses_known;case 3:return o->oc_encountered;case 4:return o->oc_magic;case 5:return o->oc_charged;case 6:return o->oc_unique;case 7:return o->oc_nowish;case 8:return o->oc_big;case 9:return o->oc_tough;case 10:return o->oc_dir;case 11:return o->oc_material;default:return 0;}}
extern int teleport_nhlobj_callback_l_obj_new_readobjnam(lua_State*);
static int teleport_nhlobj_cb_0(lua_State*L){return teleport_nhlobj_callback_l_obj_new_readobjnam(L);}
extern int teleport_nhlobj_callback_l_obj_isnull(lua_State*);
static int teleport_nhlobj_cb_1(lua_State*L){return teleport_nhlobj_callback_l_obj_isnull(L);}
extern int teleport_nhlobj_callback_l_obj_at(lua_State*);
static int teleport_nhlobj_cb_2(lua_State*L){return teleport_nhlobj_callback_l_obj_at(L);}
extern int teleport_nhlobj_callback_l_obj_nextobj(lua_State*);
static int teleport_nhlobj_cb_3(lua_State*L){return teleport_nhlobj_callback_l_obj_nextobj(L);}
extern int teleport_nhlobj_callback_l_obj_to_table(lua_State*);
static int teleport_nhlobj_cb_4(lua_State*L){return teleport_nhlobj_callback_l_obj_to_table(L);}
extern int teleport_nhlobj_callback_l_obj_objects_to_table(lua_State*);
static int teleport_nhlobj_cb_5(lua_State*L){return teleport_nhlobj_callback_l_obj_objects_to_table(L);}
extern int teleport_nhlobj_callback_l_obj_placeobj(lua_State*);
static int teleport_nhlobj_cb_6(lua_State*L){return teleport_nhlobj_callback_l_obj_placeobj(L);}
extern int teleport_nhlobj_callback_l_obj_container(lua_State*);
static int teleport_nhlobj_cb_7(lua_State*L){return teleport_nhlobj_callback_l_obj_container(L);}
extern int teleport_nhlobj_callback_l_obj_getcontents(lua_State*);
static int teleport_nhlobj_cb_8(lua_State*L){return teleport_nhlobj_callback_l_obj_getcontents(L);}
extern int teleport_nhlobj_callback_l_obj_add_to_container(lua_State*);
static int teleport_nhlobj_cb_9(lua_State*L){return teleport_nhlobj_callback_l_obj_add_to_container(L);}
extern int teleport_nhlobj_callback_l_obj_timer_has(lua_State*);
static int teleport_nhlobj_cb_10(lua_State*L){return teleport_nhlobj_callback_l_obj_timer_has(L);}
extern int teleport_nhlobj_callback_l_obj_timer_peek(lua_State*);
static int teleport_nhlobj_cb_11(lua_State*L){return teleport_nhlobj_callback_l_obj_timer_peek(L);}
extern int teleport_nhlobj_callback_l_obj_timer_stop(lua_State*);
static int teleport_nhlobj_cb_12(lua_State*L){return teleport_nhlobj_callback_l_obj_timer_stop(L);}
extern int teleport_nhlobj_callback_l_obj_timer_start(lua_State*);
static int teleport_nhlobj_cb_13(lua_State*L){return teleport_nhlobj_callback_l_obj_timer_start(L);}
extern int teleport_nhlobj_callback_l_obj_bury(lua_State*);
static int teleport_nhlobj_cb_14(lua_State*L){return teleport_nhlobj_callback_l_obj_bury(L);}
extern int teleport_nhlobj_callback_l_obj_gc(lua_State*);
static int teleport_nhlobj_cb_15(lua_State*L){return teleport_nhlobj_callback_l_obj_gc(L);}
uint64_t teleport_nhlobj_callback_pointer(int i){switch(i){case 0:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_0;case 1:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_1;case 2:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_2;case 3:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_3;case 4:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_4;case 5:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_5;case 6:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_6;case 7:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_7;case 8:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_8;case 9:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_9;case 10:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_10;case 11:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_11;case 12:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_12;case 13:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_13;case 14:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_14;case 15:return(uint64_t)(uintptr_t)teleport_nhlobj_cb_15;default:return 0;}}
void teleport_nhlobj_sprintf(char*out,const char*fmt,const char*s){Sprintf(out,fmt,s);}
static char teleport_nhlobj_literals[TELEPORT_NHLOBJ_LITERAL_CAPACITY];
void*teleport_nhlobj_literal_storage(void){return teleport_nhlobj_literals;}
size_t teleport_nhlobj_literal_capacity(void){return sizeof teleport_nhlobj_literals;}
