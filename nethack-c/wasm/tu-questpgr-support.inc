/* QUESTPGR ABI only: storage, packed fields, native macros and typed varargs. */
void *teleport_questpgr_global(int i){switch(i){case 0:return &gu;case 1:return &gn;case 2:return &gi;case 3:return &svl;case 4:return &gm;case 5:return &svq;case 6:return &gc;case 7:return &svp;case 8:return &svd;case 9:return &u;case 10:return &flags;case 11:return &program_state;case 12:return (void*)genders;case 13:return mons;case 14:return &svm;default:return &gl;}}
unsigned teleport_questpgr_quest_bit(int i){switch(i){case 0:return svq.quest_status.godgend;case 1:return svq.quest_status.ldrgend;default:return svq.quest_status.nemgend;}}
int teleport_questpgr_rn2(int n,int line,const char*caller){if(rng_log_enabled())rng_log_set_caller("questpgr.c",line,caller);return (rn2)(n);}
void teleport_questpgr_sprintf_pp(char*out,const char*fmt,const char*a,const char*b){Sprintf(out,fmt,a,b);}
void teleport_questpgr_sprintf_ip(char*out,const char*fmt,int n,const char*a){Sprintf(out,fmt,n,a);}
void teleport_questpgr_impossible_p(const char*fmt,const char*a,const char*b,const char*c,const char*d){impossible(fmt,a,b,c,d);}
void teleport_questpgr_impossible_i(const char*fmt,int n){impossible(fmt,n);}
void teleport_questpgr_free(void*p){free(p);}
void teleport_questpgr_pline(const char*fmt,const char*text){pline(fmt,text);}
void teleport_questpgr_panic(const char*fmt){panic(fmt);}
winid teleport_questpgr_create(int type){return create_nhwindow(type);}
void teleport_questpgr_putstr(winid w,int attr,const char*text){putstr(w,attr,text);}
void teleport_questpgr_display(winid w,boolean block){display_nhwindow(w,block);}
void teleport_questpgr_destroy(winid w){destroy_nhwindow(w);}
void teleport_questpgr_history(const char*msg,boolean restoring){putmsghistory(msg,restoring);}
const char *teleport_questpgr_lua_checkstring(lua_State*L,int index){return luaL_checkstring(L,index);}
lua_Integer teleport_questpgr_lua_integer(lua_State*L,int index){return lua_tointeger(L,index);}
static char teleport_questpgr_literals[TELEPORT_QUESTPGR_LITERAL_CAPACITY];
void *teleport_questpgr_literal_storage(void){return teleport_questpgr_literals;}
size_t teleport_questpgr_literal_capacity(void){return sizeof teleport_questpgr_literals;}
