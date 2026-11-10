/* ROLE storage/packed fields and native ABI calls only. */

void*teleport_role_storage(int i){switch(i){case 0:return (void*)roles;case 1:return (void*)races;case 2:return (void*)genders;default:return (void*)aligns;}}
void*teleport_role_global(int i){switch(i){
case 0:return &gu;
case 1:return &gr;
case 2:return &svp;
case 3:return &gp;
case 4:return &sysopt;
case 5:return &program_state;
case 6:return &flags;
case 7:return &iflags;
case 8:return &cg;
case 9:return (void*)mons;
case 10:return &svq;
case 11:return (void*)objects;
default:return NULL;}}
unsigned teleport_role_quest_bit(int i){switch(i){case 0:return svq.quest_status.ldrgend;case 1:return svq.quest_status.nemgend;default:return svq.quest_status.godgend;}}
void teleport_role_set_quest_bit(int i,unsigned v){switch(i){case 0:svq.quest_status.ldrgend=v;break;case 1:svq.quest_status.nemgend=v;break;default:svq.quest_status.godgend=v;break;}}
int teleport_role_rn2(int n,int line,const char*fn){if(rng_log_enabled())rng_log_set_caller("role.c",line,fn);return(rn2)(n);}
void teleport_role_sprintf(char*out,const char*fmt,const char*a,const char*b,const char*c,const char*d,const char*e){Sprintf(out,fmt,a,b,c,d,e);}
void teleport_role_impossible(const char*fmt,int n){impossible(fmt,n);}
void teleport_role_panic(const char*fmt){panic(fmt);}
void teleport_role_pline(const char*fmt){pline(fmt);}
void teleport_role_free(void*p){free(p);}
winid teleport_role_create_window(int kind){return create_nhwindow(kind);}
void teleport_role_start_menu(winid w,unsigned long flags){start_menu(w,flags);}
void teleport_role_end_menu(winid w,const char*s){end_menu(w,s);}
void teleport_role_destroy_window(winid w){destroy_nhwindow(w);}
void teleport_role_putstr(winid w,int attr,const char*s){putstr(w,attr,s);}
void teleport_role_add_menu_str(winid w,const char*s){add_menu_str(w,s);}
void teleport_role_askname(void){askname();}
const glyph_info*teleport_role_nul_glyph(void){return &nul_glyphinfo;}
void teleport_role_assert(int ok,int index){if(ok)return;switch(index){case 0:__assert_fail("IndexOkT(rolenum, roles)","role.c",1543,"root_plselection_prompt");break;case 1:__assert_fail("IndexOkT(r, roles)","role.c",1739,"role_selection_prolog");break;case 2:__assert_fail("IndexOkT(c, races)","role.c",1758,"role_selection_prolog");break;case 3:__assert_fail("which == RS_ROLE || r == ROLE_NONE || r == ROLE_RANDOM || IndexOkT(r, roles)","role.c",1777,"role_selection_prolog");break;case 4:__assert_fail("which == RS_RACE || c == ROLE_NONE || c == ROLE_RANDOM || IndexOkT(c, races)","role.c",1794,"role_selection_prolog");break;}}
unsigned teleport_role_strlen(const char*s,int index){switch(index){case 0:return Strlen_(s,"str2role",756);case 1:return Strlen_(s,"str2race",822);case 2:return Strlen_(s,"str2gend",889);case 3:return Strlen_(s,"str2align",952);case 4:return Strlen_(s,"build_plselection_prompt",1601);case 5:return Strlen_(s,"plnamesuffix",1680);default:return 0;}}
static char teleport_role_literals[TELEPORT_ROLE_LITERAL_CAPACITY];
void*teleport_role_literal_storage(void){return teleport_role_literals;}
size_t teleport_role_literal_capacity(void){return sizeof teleport_role_literals;}
