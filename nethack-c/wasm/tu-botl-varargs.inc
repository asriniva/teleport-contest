
/* Fixed C variadic ABI shapes: original format engines remain native. */
uint64_t teleport_botl_format_0(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);}
uint64_t teleport_botl_format_1(uint64_t a0,uint64_t a1){return (uint64_t)(uintptr_t) ((int(*)(char*,const char*,...))sprintf)((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);}
uint64_t teleport_botl_format_2(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_botl_format_3(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(int)a3,(int)a4,(int)a5,(int)a6,(int)a7);}
uint64_t teleport_botl_format_4(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2);}
uint64_t teleport_botl_format_5(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(long)a3);}
uint64_t teleport_botl_format_6(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(int)a3,(int)a4,(int)a5,(int)a6);}
uint64_t teleport_botl_format_7(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2,(long)a3);}
uint64_t teleport_botl_format_8(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(long)a2);}
uint64_t teleport_botl_format_9(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2);}
uint64_t teleport_botl_format_10(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7,uint64_t a8,uint64_t a9,uint64_t a10){nh_snprintf((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(char *)(uintptr_t)a5,(char *)(uintptr_t)a6,(char *)(uintptr_t)a7,(char *)(uintptr_t)a8,(char *)(uintptr_t)a9,(char *)(uintptr_t)a10);return 0;}
uint64_t teleport_botl_format_11(uint64_t a0,uint64_t a1,uint64_t a2){panic((const char *)(uintptr_t)a0,(unsigned int)a1,(int)a2);return 0;}
uint64_t teleport_botl_format_12(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(int)a3);}
uint64_t teleport_botl_format_13(uint64_t a0){((void(*)(const char*,...))panic)((const char *)(uintptr_t)a0);return 0;}
uint64_t teleport_botl_format_14(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_botl_format_15(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(char *)(uintptr_t)a2,(const char *)(uintptr_t)a3);}
uint64_t teleport_botl_format_16(uint64_t a0){((void(*)(const char*,...))impossible)((const char *)(uintptr_t)a0);return 0;}
uint64_t teleport_botl_format_17(uint64_t a0,uint64_t a1,uint64_t a2){panic((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);return 0;}
uint64_t teleport_botl_format_18(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned long)a2);}
uint64_t teleport_botl_format_19(uint64_t a0,uint64_t a1,uint64_t a2){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(unsigned int)a2);}
uint64_t teleport_botl_format_20(uint64_t a0,uint64_t a1,uint64_t a2){impossible((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);return 0;}
uint64_t teleport_botl_format_21(uint64_t a0,uint64_t a1){config_error_add((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);return 0;}
uint64_t teleport_botl_format_22(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){config_error_add((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3,(char *)(uintptr_t)a4,(const char *)(uintptr_t)a5);return 0;}
uint64_t teleport_botl_format_23(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){config_error_add((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(long)a3,(const char *)(uintptr_t)a4);return 0;}
uint64_t teleport_botl_format_24(uint64_t a0,uint64_t a1){config_error_add((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return 0;}
uint64_t teleport_botl_format_25(uint64_t a0,uint64_t a1,uint64_t a2){config_error_add((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(int)a2);return 0;}
uint64_t teleport_botl_format_26(uint64_t a0,uint64_t a1,uint64_t a2){config_error_add((const char *)(uintptr_t)a0,(int)a1,(int)a2);return 0;}
uint64_t teleport_botl_format_27(uint64_t a0){((void(*)(const char*,...))config_error_add)((const char *)(uintptr_t)a0);return 0;}
uint64_t teleport_botl_format_28(uint64_t a0,uint64_t a1){config_error_add((const char *)(uintptr_t)a0,(int)a1);return 0;}
uint64_t teleport_botl_format_29(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6){nh_snprintf((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(char *)(uintptr_t)a5,(char *)(uintptr_t)a6);return 0;}
uint64_t teleport_botl_format_30(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3);}
uint64_t teleport_botl_format_31(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){nh_snprintf((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(const char *)(uintptr_t)a5,(char *)(uintptr_t)a6,(char *)(uintptr_t)a7);return 0;}
uint64_t teleport_botl_format_32(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3);}
uint64_t teleport_botl_format_33(uint64_t a0){((void(*)(const char*,...))pline)((const char *)(uintptr_t)a0);return 0;}
uint64_t teleport_botl_format_34(uint64_t a0,uint64_t a1){pline((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1);return 0;}
uint64_t teleport_botl_format_35(uint64_t a0,uint64_t a1){pline((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1);return 0;}
uint64_t teleport_botl_format_36(uint64_t a0,uint64_t a1,uint64_t a2){pline((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(int)a2);return 0;}
uint64_t teleport_botl_format_37(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){pline((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(int)a3,(const char *)(uintptr_t)a4);return 0;}
uint64_t teleport_botl_format_38(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4){pline((const char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(long)a3,(const char *)(uintptr_t)a4);return 0;}
uint64_t teleport_botl_format_39(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){return (uint64_t)(uintptr_t) sprintf((char *)(uintptr_t)a0,(const char *)(uintptr_t)a1,(const char *)(uintptr_t)a2,(char *)(uintptr_t)a3,(char *)(uintptr_t)a4,(char *)(uintptr_t)a5);}
uint64_t teleport_botl_format_40(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5){nh_snprintf((const char *)(uintptr_t)a0,(int)a1,(char *)(uintptr_t)a2,(unsigned long)a3,(const char *)(uintptr_t)a4,(char *)(uintptr_t)a5);return 0;}
uint64_t teleport_botl_format_41(uint64_t a0,uint64_t a1,uint64_t a2){pline((const char *)(uintptr_t)a0,(char *)(uintptr_t)a1,(char *)(uintptr_t)a2);return 0;}

int teleport_botl_callback_cond_cmp(const void*,const void*);
int teleport_botl_callback_menualpha_cmp(const void*,const void*);
int teleport_botl_native_cond_cmp(const void*a,const void*b){return teleport_botl_callback_cond_cmp(a,b);}
int teleport_botl_native_menualpha_cmp(const void*a,const void*b){return teleport_botl_callback_menualpha_cmp(a,b);}
uintptr_t teleport_botl_callback_pointer(int i){return(uintptr_t)(i?teleport_botl_native_menualpha_cmp:teleport_botl_native_cond_cmp);}
void teleport_botl_qsort(void*b,size_t n,size_t z,uintptr_t fn){qsort(b,n,z,(int(*)(const void*,const void*))fn);}
void teleport_botl_free(void*p){free(p);}
void teleport_botl_plain(const char*s){pline1(s);}
void teleport_botl_curs(winid w,int x,int y){curs(w,x,y);}
void teleport_botl_putstr(winid w,int a,const char*s){putstr(w,a,s);}
void teleport_botl_putmixed(winid w,int a,const char*s){putmixed(w,a,s);}
winid teleport_botl_create_nhwindow(int t){return create_nhwindow(t);}
void teleport_botl_start_menu(winid w,unsigned long b){start_menu(w,b);}
void teleport_botl_end_menu(winid w,const char*s){end_menu(w,s);}
void teleport_botl_destroy_nhwindow(winid w){destroy_nhwindow(w);}
void teleport_botl_display_nhwindow(winid w,boolean b){display_nhwindow(w,b);}
void teleport_botl_status_init(void){(*windowprocs.win_status_init)();}
void teleport_botl_status_finish(void){(*windowprocs.win_status_finish)();}
void teleport_botl_status_enablefield(int i,const char*n,const char*f,boolean b){status_enablefield(i,n,f,b);}
void teleport_botl_status_update(int f,void*p,int c,int pc,int clr,unsigned long*m){status_update(f,p,c,pc,clr,m);}
