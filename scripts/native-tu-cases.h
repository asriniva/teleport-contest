/* Native/Wasm behavioral cases. This file is included AFTER the existing
 * isolated probe, so every case uses its actual C types and fixture callbacks.
 * Print values/content, never process addresses or host-specific struct padding.
 */
#include <stdio.h>
#include <stdint.h>
#undef putchar
#undef fflush
extern int putchar(int);
extern int fflush(FILE *);
static void oracle_number(long long value) { printf("n:%lld\n", value); }
static void oracle_unsigned(unsigned long long value) { printf("u:%llu\n", value); }
static void oracle_text(const char *value) {
    if (!value) { puts("null"); return; }
    fputs("s:", stdout);
    for (; *value; ++value) printf("%02x", (unsigned char)*value);
    putchar('\n');
}
static void oracle_bytes(const void *data, size_t size) {
    const unsigned char *p = data;
    fputs("b:", stdout);
    for (size_t i = 0; i < size; ++i) printf("%02x", p[i]);
    putchar('\n');
}
#if ORACLE_CALENDAR
time_t teleport_oracle_time(time_t *out) { time_t fixed=1768478400L; if(out)*out=fixed; return fixed; }
#endif
#if ORACLE_IOCTL && defined(TELEPORT_NATIVE_ORACLE)
struct sysopt_s sysopt;
#endif
#if ORACLE_GETLINE && defined(TELEPORT_NATIVE_ORACLE)
char erase_char, kill_char;
#endif
#if ORACLE_VERSION && defined(TELEPORT_NATIVE_ORACLE)
struct nomakedefs_s nomakedefs;
/* Same controlled regex-identifier dependency as the existing version probe. */
const char regex_id[11]={0};
#endif
#if ORACLE_UNIXTTY
static void oracle_tty_trace(void) {
    char normalized[8192]; const char *p=probe_trace(); char *out=normalized;
    while(*p) {
        if(!strncmp(p,"disable:0:",10)) {
            char *end; long value=strtol(p+10,&end,10);
            if(value != _PC_VDISABLE || *end!=';') abort();
            memcpy(out,"disable:0:VDISABLE;",18);out+=18;p=end+1;
        } else *out++=*p++;
    }
    *out=0;oracle_text(normalized);
}
#endif
void probe_native_oracle(void) {
#if ORACLE_ISAAC64
    isaac64_ctx ctx;
    unsigned char seed[256];
    for (int i=0;i<256;i++) seed[i]=(unsigned char)(i*37);
    for(int n=0;n<=256;n+=32) {
        probe_init(&ctx,seed,n);
        for(int i=0;i<600;i++) oracle_unsigned(probe_next(&ctx));
        probe_reseed(&ctx,seed,256-n);
        for(int i=1;i<200;i++) oracle_unsigned(probe_bounded(&ctx,(uint64_t)i*i*i+1));
    }
#elif ORACLE_NHMD4
    NHMD4_CTX ctx; unsigned char input[1024], digest[16];
    for(int i=0;i<1024;i++) input[i]=(unsigned char)(i*37);
    for(int n=0;n<=1024;n+=7) {
        probe_init(&ctx); probe_update(&ctx,input,n/2);probe_update(&ctx,input+n/2,n-n/2);
        probe_final(&ctx,digest); oracle_bytes(digest,16);
    }
#elif ORACLE_STRUTIL
    strbuf_t buffer; char input[1024];
    probe_init(&buffer);
    for(int n=0;n<1000;n+=31) {
        memset(input,'a'+n%26,n); input[n]=0;
        probe_append(&buffer,input); oracle_text(buffer.str); oracle_number(buffer.len);
    }
    probe_append(&buffer,"\nlast\n");probe_crlf(&buffer);oracle_text(buffer.str);probe_empty(&buffer);
    const char *patterns[]={"","*","?","a*","*b","a?b","**a**","*a*b*"};
    const char *texts[]={"","a","A","ab","aBc","aaab","xyz"};
    for(int p=0;p<8;p++)for(int t=0;t<7;t++)for(int ci=0;ci<2;ci++)oracle_number(probe_match(patterns[p],texts[t],ci));
#elif ORACLE_RECT
    NhRect whole={0,0,COLNO-1,ROWNO-1}, cut={10,4,20,12};
    probe_seed(17);probe_init();probe_split(&whole,&cut);
    for(int i=0;i<100;i++) { NhRect *r=probe_random(); oracle_number(r!=NULL); if(r){oracle_number(r->lx);oracle_number(r->ly);oracle_number(r->hx);oracle_number(r->hy);} }
    oracle_number(probe_rng_count());oracle_text(probe_rng_caller());probe_free();
#elif ORACLE_TRACK
    probe_init();
    for(int i=0;i<100;i++){probe_hero(1+i%70,1+i%19,-1,-1);probe_set();}
    for(int x=1;x<75;x++)for(int y=1;y<20;y++){coord *c=probe_get(x,y);oracle_number(probe_has(x,y));oracle_number(c!=NULL);if(c){oracle_number(c->x);oracle_number(c->y);}}
    probe_save(WRITING);oracle_bytes(probe_stream(),probe_stream_size());oracle_number(probe_rest());oracle_number(probe_count());oracle_number(probe_point());
    probe_corrupt_counts(-1,-1);oracle_number(probe_rest());oracle_text(probe_panic_message());
#elif ORACLE_CALENDAR
    const long dates[]={0,1,-1,951782400L,1768478400L,2147483647L,4102444800L};
    for(int i=0;i<7;i++){oracle_number(probe_date(dates[i]));oracle_number(probe_time(dates[i]));oracle_text(probe_format(dates[i]));}
    const char *strings[]={"20260115120000","20000229000000","20260613123456","bad","","20260230010203"};
    for(int i=0;i<6;i++)oracle_number(probe_parse((char *)strings[i]));
    puts("recording-specific");
    probe_set_env("NETHACK_FIXED_DATETIME","20261113000000");
    oracle_number(probe_now());oracle_number(probe_year());oracle_number(probe_moon());oracle_number(probe_friday());oracle_number(probe_night());oracle_number(probe_midnight());
#elif ORACLE_STAIRS
    probe_init();probe_hero(0,2,0);
    for(int i=0;i<8;i++)probe_add(10+i,5+i,i%2,i%3==0,i%2,1+i);
    for(int x=9;x<20;x++)for(int y=4;y<15;y++){oracle_number(probe_on(x,y));oracle_number(probe_ladder(x,y));oracle_number(probe_on_up(x,y));oracle_number(probe_on_down(x,y));}
    for(stairway *st=probe_head();st;st=st->next){oracle_number(st->sx);oracle_number(st->sy);oracle_number(probe_known(st));oracle_text(probe_describe(st,0));oracle_text(probe_describe(st,1));}
    probe_free();
#elif ORACLE_SYS
    for(int k=0;k<3;k++) {
        probe_env(k==0?NULL:k==1?"all":"foo.c");probe_populate(k);probe_init();probe_seduce(k%2);
        for(int i=0;i<probe_field_count();i++) {
            char *q=(char*)probe_sys_pointer()+probe_field_offset(i);
            /* The host enables execinfo panic traces; Emscripten does not.
             * Check each configured branch, including preservation when absent. */
            if(!strcmp(probe_field_name(i),"panictrace_libc")) {
#if defined(PANICTRACE) && defined(PANICTRACE_LIBC)
                oracle_number(*(int*)q == (NH_DEVEL_STATUS != NH_STATUS_RELEASED ? 2 : 0));
#else
                oracle_number(*(int*)q == -1000-k-i);
#endif
                continue;
            }
            switch(probe_field_kind(i)){case 0:oracle_text(*(char**)q);break;case 1:oracle_number(*(int*)q);break;case 2:oracle_number(*(long*)q);break;case 3:for(size_t j=0;j<probe_field_size(i)/sizeof(int);j++)oracle_number(((int*)q)[j]);break;}
        }
        probe_release();
    }
#elif ORACLE_RIP
    const char *names[]={"Ada","a name that is much longer than the tombstone"};
    for(int n=0;n<2;n++)for(int h=0;h<4;h++) {
        probe_inputs(names[n],123456789L,"killed by a particularly persistent newt",20261109L);probe_run(3,h,1768478400L);
        oracle_number(probe_line_count());for(int i=0;i<probe_line_count();i++){oracle_number(probe_line_attribute(i));oracle_number(probe_line_dump(i));oracle_text(probe_line_text(i));}
        oracle_number(probe_killer_calls());oracle_number(probe_date_argument());
    }
#elif ORACLE_DATE
    probe_env("NETHACK_REAL_BUILD_DATE",NULL);
    for(int k=0;k<3;k++){
        probe_inputs(0x05000000UL+k,0x12345678UL,0x23456789UL,123UL,"native oracle");probe_populate();
        for(int i=0;i<probe_field_count();i++) {char *q=(char*)probe_pointer()+probe_field_offset(i);if(probe_field_kind(i)==0)oracle_text(*(char**)q);else oracle_unsigned(*(unsigned long*)q);}
        oracle_text(probe_trace());probe_release();
    }
#elif ORACLE_ALLOC
    const long long values[]={-2147483649LL,-2147483648LL,-1,0,1,2147483647LL,2147483648LL};
    for(int i=0;i<7;i++){oracle_number(probe_signed(values[i],"oracle.c",77));oracle_number(probe_signed_result());oracle_text(probe_panic_message());}
    for(int i=0;i<7;i++){oracle_number(probe_unsigned((unsigned long long)values[i],"oracle.c",88));oracle_unsigned(probe_unsigned_result());oracle_text(probe_panic_message());}
    for(int n=0;n<4;n++){oracle_number(probe_alloc(16+n,0));oracle_number(probe_requested());oracle_number(probe_result()!=NULL);free(probe_result());oracle_number(probe_alloc(16+n,1));oracle_text(probe_panic_message());}
#elif ORACLE_UTF8MAP
    const char *texts[]={"","A","é","水","😀","U+0041","U+1F600","not unicode"};
    for(int i=0;i<8;i++)oracle_number(probe_unicode(texts[i]));
    probe_reset(0,1);
    for(int i=0;i<8;i++){oracle_number(probe_set(i,0x2600+i,(const uint8*)"☀"));oracle_unsigned(probe_map_code(i));oracle_text((const char*)probe_map_text(i));}
    probe_free();probe_cleanup();oracle_text(probe_trace());
#elif ORACLE_DRAWING
    for(int t=0;t<5;t++)for(int i=0;i<probe_table_count(t);i++) {oracle_number(probe_table_symbol(t,i));oracle_text(probe_table_name(t,i));oracle_text(probe_table_explanation(t,i));oracle_number(probe_table_color(t,i));}
    for(int i=0;i<256;i++){oracle_number(probe_object(i));oracle_number(probe_monclass(i));oracle_number(probe_furniture(i));}
#elif ORACLE_POSIXREGEX
    const char *patterns[]={"a+","^abc$","[a-z]+","a.*b","(","["};
    const char *texts[]={"","abc","AA","aab","xabz","123"};
    for(int p=0;p<6;p++){struct nhregex *r=probe_init();int ok=probe_compile(patterns[p],r);oracle_number(ok);if(ok)for(int t=0;t<6;t++)oracle_number(probe_match(texts[t],r));probe_free(r);}
#elif ORACLE_RND
    probe_env("NETHACK_RNGLOG",NULL);probe_env("NETHACK_SEED",NULL);
    for(int seed=1;seed<5;seed++){
        probe_seed(seed,1);probe_init(seed,0);probe_init(seed+1,1);
        for(int luck=-3;luck<=3;luck++){probe_hero(luck,0,15);for(int i=1;i<30;i++){oracle_number(probe_rn2(i));oracle_number(probe_display(i));oracle_number(probe_rnd(i));oracle_number(probe_rnl(i));oracle_number(probe_dice(3,i));oracle_number(probe_rne(i));oracle_number(probe_rnz(i*10));}}
    }
#elif ORACLE_IOCTL
    probe_options(0,0,0,1,0);probe_shellers("oracle");
    struct termios *input=probe_input_pointer();input->c_lflag=ECHO|ICANON;input->c_cc[VINTR]=3;input->c_cc[VERASE]=127;
    probe_get();probe_set();probe_windows();
    struct termios *saved=probe_termio_pointer(), *output=probe_output_pointer();
    oracle_number(saved->c_cc[VINTR]);oracle_number(saved->c_cc[VERASE]);oracle_number(!!(output->c_lflag&ECHO));oracle_number(!!(output->c_lflag&ICANON));oracle_text(probe_trace());
#elif ORACLE_UNIXTTY
    probe_env("NOMUX_MARKERS",NULL);probe_options(0,0,13,-1,1,0);probe_iflags(0,0,0);probe_chars(127,3,21);
    probe_get();probe_set("restored");probe_on();probe_off();probe_fast();probe_fixup();
    oracle_number(probe_erase());oracle_number(probe_intr());oracle_number(probe_kill());oracle_number(probe_echo());oracle_number(probe_cbreak());oracle_tty_trace();
#elif ORACLE_WERE
    const int pairs[]={PM_WEREWOLF,PM_HUMAN_WEREWOLF,PM_WEREJACKAL,PM_HUMAN_WEREJACKAL,PM_WERERAT,PM_HUMAN_WERERAT};
    for(int i=0;i<6;i++)for(int hp=1;hp<111;hp+=27){probe_reset();probe_mon(pairs[i],hp,100,1,0,7,0,i%2);probe_new();oracle_number(probe_counter(pairs[i]));oracle_number(probe_mon_pm());oracle_number(probe_mon_hp());oracle_number(probe_mon_sleep());oracle_number(probe_mon_move());oracle_number(probe_mon_frozen());oracle_text(probe_trace());}
    for(int i=0;i<6;i++){probe_reset();oracle_number(probe_summon(pairs[i],i%2,1));oracle_number(probe_summoned_count());oracle_text(probe_trace());}
#elif ORACLE_EXTRALEV
    for(int seed=1;seed<5;seed++){probe_reset(seed);probe_make();oracle_number(probe_nroom());for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++){oracle_number(probe_typ(x,y));oracle_number(probe_door(x,y));}oracle_number(probe_rng_count());oracle_text(probe_trace());}
#elif ORACLE_MPLAYER
    for(int seed=1;seed<6;seed++){probe_reset(seed);probe_name(PM_ARCHEOLOGIST,seed*5);oracle_text(probe_name_result());probe_make(PM_WIZARD,10,10,seed%2);oracle_number(probe_result());oracle_number(probe_monster_count());for(int i=0;i<probe_monster_count();i++){oracle_number(probe_mon_pm(i));oracle_number(probe_mon_hp(i));oracle_number(probe_mon_level(i));oracle_text(probe_mon_name(i));}oracle_number(probe_object_count());for(int i=0;i<probe_object_count();i++)oracle_number(probe_object_quantity(i));oracle_text(probe_trace());}
#elif ORACLE_EXPER
    for(int lev=1;lev<=30;lev++){probe_reset(lev);oracle_number(probe_threshold(lev));probe_hero(lev,lev,lev,1000,2000,0);oracle_number(probe_energy_modifier(17));oracle_number(probe_power());probe_victim(lev,12,'a',0,0,0,0);oracle_number(probe_experience(1));oracle_number(probe_random_experience(0));oracle_text(probe_trace());}
#elif ORACLE_MKMAP
    for(int seed=1;seed<4;seed++){probe_reset(seed);probe_make(STONE,ROOM,1,1,0,1,0);for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)for(int f=0;f<4;f++)oracle_number(probe_cell_field(x,y,f));oracle_number(probe_rng_count());oracle_text(probe_trace());probe_cleanup();}
#elif ORACLE_GETLINE
    const char *inputs[]={"abc\n","abc\177d\n","\033","\n"};
    for(int k=0;k<4;k++){probe_reset();int *in=probe_input_pointer();int n=0;for(const char *p=inputs[k];*p;p++)in[n++]=(unsigned char)*p;probe_input_length(n);probe_line("Native oracle?");oracle_text((const char*)probe_snapshot_pointer(4));oracle_text(probe_trace());for(int i=0;i<5;i++)oracle_number(probe_scalar(i));}
#elif ORACLE_WRITE
    const int types[]={SCR_ENCHANT_ARMOR,SCR_IDENTIFY,SCR_BLANK_PAPER,SPE_MAGIC_MISSILE,SPE_BLANK_PAPER};
    for(int k=0;k<5;k++){probe_reset(17+k);oracle_number(probe_cost(types[k],k<3?SCROLL_CLASS:SPBOOK_CLASS));oracle_number(probe_ok(types[k],k<3?SCROLL_CLASS:SPBOOK_CLASS,0));probe_pen(100,1,0,0);probe_paper(SCR_BLANK_PAPER,1,1,0,0);probe_input("identify");oracle_number(probe_write());oracle_number(probe_literate());oracle_text(probe_trace());}
#elif ORACLE_MDLIB
    probe_reset();
    const char *delims[]={""," ","::"};
    for(int i=0;i<3;i++){oracle_number(probe_version_string(delims[i]));oracle_text(probe_output());oracle_number(probe_version_id(256,"May  2 2026"));oracle_text(probe_output());}
    probe_make_version();probe_init();int ctx=0;const char *line;while((line=probe_next(&ctx)))oracle_text(line);probe_release();oracle_text(probe_trace());
#elif ORACLE_QUEST
    for(int k=0;k<6;k++){probe_reset(17+k);probe_alignment(A_LAWFUL,A_LAWFUL,A_LAWFUL,20,15);probe_action(k,0);for(int i=0;i<12;i++)oracle_number(probe_qget(i));oracle_unsigned(probe_strategy());oracle_text(probe_trace());}
#elif ORACLE_MINION
    for(int k=0;k<5;k++){probe_reset(17+k);oracle_number(probe_action(0,0));oracle_number(probe_action(4,A_CHAOTIC));oracle_number(probe_action(5,A_LAWFUL));oracle_number(probe_action(7,0));oracle_text(probe_trace());}
#elif ORACLE_IACTIONS
    for(int k=0;k<3;k++){probe_reset();probe_item(k==0?DAGGER:k==1?SCR_IDENTIFY:POT_HEALING,1,0,1,1,0,0,0,0,0,'a');probe_select(0,0,0);oracle_number(probe_run());oracle_number(probe_menu_count());for(int i=0;i<probe_menu_count();i++){oracle_number(probe_menu_action(i));oracle_number(probe_menu_letter(i));oracle_text(probe_menu_text(i));}oracle_text(probe_trace());}
#elif ORACLE_SELVAR
    for(int seed=1;seed<4;seed++){probe_reset(seed);probe_new(0);probe_line(0,2,3,30,15);probe_ellipse(0,25,10,6,4,1);probe_grow(0,0);probe_clone(0,1);probe_filter(0,1,50);for(int s=0;s<2;s++)for(int x=0;x<COLNO;x++)for(int y=0;y<ROWNO;y++)oracle_number(probe_get(s,x,y));oracle_number(probe_rndcoord(0,1));oracle_number(probe_rng_count());oracle_text(probe_trace());probe_free(0,1);probe_free(1,1);}
#elif ORACLE_OBJECTS
    probe_init();for(int row=0;row<probe_count();row++){for(int f=0;f<probe_field_count();f++)oracle_unsigned(probe_value(row,f));for(int f=0;f<3;f++)oracle_text(probe_string(row,f));}
    probe_mutate(17,20,123);probe_init();oracle_unsigned(probe_value(17,20));
#elif ORACLE_MONST
    probe_init();for(int row=0;row<probe_count();row++){for(int f=0;f<probe_field_count();f++)oracle_unsigned(probe_value(row,f));for(int g=0;g<3;g++)oracle_text(probe_name(row,g));for(int a=0;a<NATTK;a++)for(int f=0;f<4;f++)oracle_unsigned(probe_attack(row,a,f));}
#elif ORACLE_STEAL
    for(int k=0;k<8;k++){probe_reset(k+1);probe_obj(0,GOLD_PIECE,1000,OBJ_INVENT);probe_inventory(0);probe_mon(0,PM_LEPRECHAUN);oracle_number(probe_action(0,0,0,k*1000,0));oracle_number(probe_action(2,0,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_SIT
    const int terrain[]={ROOM,POOL,SINK,ALTAR,THRONE,ICE};
    for(int k=0;k<6;k++){probe_reset(17+k);probe_terrain(10,10,terrain[k],0);oracle_number(probe_action(1,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_FOUNTAIN
    for(int k=0;k<8;k++){probe_reset(17+k);probe_terrain(12,12,FOUNTAIN,0,k%2);oracle_number(probe_action(9,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_SHKNAM
    probe_reset(17);
    for(int i=0;i<probe_table_count();i++){oracle_text(probe_table_string(i,0));oracle_text(probe_table_string(i,1));for(int f=0;f<3;f++)oracle_number(probe_table_value(i,f,0));}
    for(int n=0;n<11;n++)for(int i=0;i<probe_list_count(n);i++)oracle_text(probe_list_name(n,i));
    probe_room(0,10,5,20,12,0,0,0,SHOPBASE);oracle_number(probe_action(0,0,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());
#elif ORACLE_RUMORS
    const char *names[]={"The Oracle","a shopkeeper","Izchak","the Wizard of Yendor","an elf","Death"};
    for(int k=0;k<6;k++){probe_reset(17+k);oracle_number(probe_action(8,0,0,0,0,0,names[k]));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_MUSIC
    for(int k=0;k<7;k++){probe_reset(17+k);probe_add_monster(0,PM_SOLDIER,12,10);probe_add_monster(1,PM_WATER_MOCCASIN,11,11);probe_add_monster(2,PM_WOOD_NYMPH,10,12);oracle_number(probe_action(k,k==0||k==5?0:100,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_VERSION
    for(int op=0;op<4;op++){probe_reset();oracle_unsigned(probe_action(op,0,256,"native oracle",0));oracle_text((char*)probe_output());oracle_text(probe_snapshot());oracle_text(probe_trace());}
    const char *versions[]={"5.0.0","3.6.7","1.2.3","bad","5.0"};for(int i=0;i<5;i++){probe_reset();oracle_unsigned(probe_action(8,0,256,versions[i],0));oracle_text(probe_trace());}
#elif ORACLE_COLORATT
    const char *colors[]={"red","bright blue","orange","default","#abcdef","invalid"};
    for(int k=0;k<6;k++){probe_reset();oracle_number(probe_action(2,0,0,0,0,colors[k]));oracle_number(probe_action(1,0,0,0,0,""));oracle_text((char*)probe_output());oracle_text(probe_snapshot());oracle_text(probe_trace());}
    for(int k=0;k<256;k++)oracle_number(probe_action(23,k,0,0,0,""));
#elif ORACLE_PRIEST
    for(int k=0;k<3;k++){probe_reset(17+k);probe_add_monster(0,PM_ALIGNED_CLERIC,12,10);oracle_number(probe_action(0,0,0,0,0,0,0,0));oracle_number(probe_action(8,0,0,0,0,0,0,0));oracle_number(probe_action(9,0,k%2,0,0,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_LIGHT
    for(int k=0;k<3;k++){probe_reset();probe_object(0,0,TALLOW_CANDLE);probe_object(0,2,k+1);oracle_number(probe_action(25,0,0,0,0,0));oracle_number(probe_action(20,0,0,0,0,0));oracle_number(probe_action(18,0,0,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_LOCK
    const int masks[]={D_ISOPEN,D_CLOSED,D_LOCKED,D_BROKEN,D_NODOOR};
    for(int k=0;k<5;k++){probe_reset(17+k);probe_terrain(11,10,DOOR,masks[k]);oracle_number(probe_action(14,11,10,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_STEED
    for(int k=0;k<4;k++){probe_reset(17+k);oracle_number(probe_action(1,0,0,0,0));oracle_number(probe_action(4,0,0,0,0));oracle_number(probe_action(9,0,k%2,k/2,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_WIZARD
    for(int k=0;k<6;k++){probe_reset(17+k);oracle_number(probe_action(1,0,0,0,0));oracle_number(probe_action(2,0,0,0,0));oracle_number(probe_action(12,0,0,0,0));oracle_number(probe_action(15,0,k%2,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_WORM
    for(int k=0;k<5;k++){probe_reset(17+k);oracle_number(probe_action(0,0,0,0,0,0));oracle_number(probe_action(1,0,k,0,0,0));oracle_number(probe_action(19,0,0,0,0,0));oracle_number(probe_action(24,0,0,20,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_O_INIT
    for(int k=0;k<3;k++){probe_reset(17+k);oracle_number(probe_action(3,0,0,0,0));oracle_number(probe_action(12,SCR_IDENTIFY,1,1,1));oracle_number(probe_action(18,SCR_IDENTIFY,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_BALL
    for(int k=0;k<3;k++){probe_reset(17+k);probe_setup_floor(k%2,10,10,10,10);oracle_number(probe_action(6,0,0,0,0,0,0));oracle_number(probe_action(3,0,0,0,0,0,0));oracle_number(probe_action(2,0,0,0,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_MCASTU
    for(int k=0;k<8;k++){probe_reset(17+k);oracle_number(probe_action(5,0,k,0));oracle_number(probe_action(17,k*2,0,0));oracle_number(probe_action(18,k*2,0,0));oracle_number(probe_action(2,1,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_DBRIDGE
    const int terrain[]={ROOM,POOL,MOAT,LAVAPOOL,ICE,DRAWBRIDGE_UP,DRAWBRIDGE_DOWN};
    for(int k=0;k<7;k++){probe_reset(17+k);probe_terrain(12,10,0,terrain[k]);for(int op=0;op<6;op++)oracle_number(probe_action(op,12,10,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_MONDATA
    probe_reset(17);
    for(int pm=0;pm<NUMMONS;pm++)for(int op=0;op<44;op++)if(op==3||op==4||op==12||op==13||op==14||op==16||op==18||op==20||op==24||op==25||op==26||op==27||op==28||op==29||op==40||op==41)oracle_number(probe_action(op,pm,0,0,0));
    const char *names[]={"newt","red dragon","giant ant","Wizard of Yendor","elves","nonsense"};for(int i=0;i<6;i++){probe_input(names[i]);oracle_number(probe_action(34,0,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
#elif ORACLE_HACKLIB
    probe_reset();
    for(int c=0;c<256;c++)for(int op=2;op<=5;op++)oracle_number(probe_action(op,c,0,0,0,0));
    const char *words[]={"", "hello WORLD", "  alpha\t beta  ","a\nb\r\n","tip","you","glass"};
    for(int i=0;i<7;i++)for(int op=6;op<=14;op++){probe_reset();probe_input(0,words[i]);oracle_number(probe_action(op,0,0,0,0,0));oracle_text((const char*)probe_pointer(1,0));oracle_bytes(buffers[0]+16,40);}
    for(int c=0;c<256;c++){probe_action(27,c,0,0,0,0);oracle_text(result);}
    for(int i=0;i<7;i++){probe_reset();probe_input(0,words[i]);if(i) {probe_action(22,0,0,0,0,0);oracle_text(result);}probe_action(23,0,0,0,0,0);oracle_text(result);}
    int unicode[]={-1,0,127,128,2047,2048,0xd800,0xffff,0x10000,0x10ffff,0x110000};
    for(int i=0;i<11;i++){probe_reset();oracle_number(probe_action(45,unicode[i],0,0,0,8));oracle_bytes(buffers[0]+16,8);}
    /* Exercise original public queries in both implementations; the private
       native dm inspector is used only by the separate JS data oracle. */
    {const int sizes[][5]={{2,4,4,8,4},{2,4,4,8,8},{2,4,8,8,8},{2,8,8,8,8},{3,7,9,13,7}};
     for(int selector=-1;selector<=1;selector++){probe_action(48,selector,0,0,0,0);oracle_text(result);for(int i=0;i<5;i++){probe_alloc_option(5,sizes[i][4]);probe_action(49,selector,sizes[i][0],sizes[i][1],sizes[i][2],sizes[i][3]);oracle_text(result);}}}
    /* libc qsort comparator order differs by platform: final stable records and
       cleanup, rather than libc's internal comparison schedule, are the oracle. */
    for(int mode=0;mode<4;mode++){probe_reset();for(int i=0;i<8;i++){sortbuf[16+i*8]=(unsigned char)((7-i)%3);sortbuf[17+i*8]=(unsigned char)i;}probe_sort_action(8,8,mode,0);oracle_bytes(sortbuf+16,64);oracle_number(alloc_calls);oracle_number(free_calls);}
    for(int mask=1;mask<=3;mask++){probe_reset();probe_alloc_option(0,mask);probe_sort_action(3,8,0,0);oracle_number(alloc_calls);oracle_number(free_calls);oracle_bytes(sortbuf+16,24);}
    {FILE *in=tmpfile(),*out=tmpfile();for(int i=0;i<BUFSIZ+7;i++)fputc(i&255,in);fflush(in);rewind(in);oracle_number(probe_fd_action(fileno(in),fileno(out)));rewind(out);int c;while((c=fgetc(out))!=EOF)oracle_number(c);fclose(in);fclose(out);}
#elif ORACLE_WORN
    /* Public behavior and stable fixture identities, never reference-only tables. */
    for(int typ=0;typ<NUM_OBJECTS;typ++){probe_reset(1);probe_object(0,0,typ);oracle_number(probe_action(7,0,0,0,0));}
    {const long masks[]={W_ARM,W_ARMC,W_ARMH,W_ARMS,W_ARMG,W_ARMF,W_ARMU,W_RINGL,W_RINGR,W_WEP,W_SWAPWEP,W_QUIVER,W_AMUL,W_TOOL,W_BALL,W_CHAIN};
     for(int i=0;i<16;i++){probe_reset(1);probe_link(0,0);probe_object(0,12,OBJ_INVENT);probe_action(1,0,0,0,masks[i]);oracle_number(probe_action(4,0,0,0,masks[i]));oracle_number(probe_action(5,0,0,0,masks[i]));probe_action(0,0,0,0,0);oracle_text(probe_snapshot());probe_action(2,0,0,0,0);probe_action(3,0,0,0,0);oracle_text(probe_snapshot());}}
    for(int cat=-1;cat<=10;cat++){probe_reset(1);oracle_number(probe_action(6,0,cat,0,0));}
    for(int speed=-4;speed<=2;speed++){probe_reset(1);probe_action(9,0,0,0,0);probe_action(10,0,speed,-1,0);oracle_text(probe_snapshot());oracle_text(probe_trace());}
    probe_reset(1);probe_object(0,0,ALCHEMY_SMOCK);probe_object(0,12,OBJ_MINVENT);probe_object(0,13,0);probe_object(0,1,W_ARMC);probe_set_monster(0,1,0);probe_set_monster(0,2,W_ARMC);probe_action(11,0,0,1,0);probe_action(11,0,0,0,0);oracle_text(probe_snapshot());
    for(int creation=0;creation<2;creation++){probe_reset(1);probe_object(0,0,SPEED_BOOTS);probe_object(0,12,OBJ_MINVENT);probe_object(0,13,0);probe_set_monster(0,1,0);probe_action(14,0,creation,0,W_ARMF);oracle_number(probe_action(12,0,0,0,0));oracle_number(probe_action(15,0,0,0,W_ARMF));oracle_number(probe_action(24,0,0,0,0));probe_action(13,0,creation,0,0);oracle_text(probe_snapshot());oracle_text(probe_trace());}
    probe_reset(1);probe_object(0,4,1);probe_object(0,5,2);probe_object(0,6,1);probe_object(1,6,1);probe_object(2,6,1);probe_link(0,0);probe_action(17,0,0,0,0);probe_action(19,0,0,0,0);probe_action(20,0,1,0,0);oracle_number(probe_action(21,0,0,0,0));probe_loot(0,3);probe_loot(1,1);probe_loot(2,-1);oracle_number(probe_action(22,0,0,0,0));probe_action(18,0,0,0,0);oracle_text(probe_snapshot());
    probe_reset(1);probe_set_monster(0,0,PM_HOBBIT);probe_object(0,0,ELVEN_CLOAK);oracle_number(probe_action(25,0,0,0,0));probe_object(0,12,OBJ_MINVENT);probe_object(0,13,0);probe_set_monster(0,1,0);probe_action(16,0,0,1,0);oracle_text(probe_snapshot());
    probe_reset(1);probe_object(0,12,OBJ_MINVENT);probe_object(0,13,0);probe_object(0,1,W_ARMH);probe_set_monster(0,1,0);probe_set_monster(0,2,W_ARMH);probe_action(26,0,0,1,0);oracle_text(probe_snapshot());
    probe_reset(1);probe_link(0,0);probe_object(0,12,OBJ_INVENT);probe_action(1,0,0,0,W_ARMH);probe_action(8,0,0,0,0);oracle_text(probe_trace());
    probe_reset(1);probe_set_monster(0,0,PM_STONE_GOLEM);probe_action(23,0,1,0,0);oracle_text(probe_snapshot());oracle_text(probe_trace());
#elif ORACLE_WIELD
    /* Actual public/private source entries, stable fixture identities only. */
    for(int type=0;type<NUM_OBJECTS;type++){probe_reset(1);probe_object(0,0,type);oracle_number(probe_action(6,0,0,0,0));oracle_number(probe_action(7,0,0,0,0));probe_action(0,0,0,0,0);oracle_text(probe_snapshot());probe_action(18,0,0,0,0);}
    for(int op=0;op<26;op++){probe_reset(1);probe_object(0,0,LONG_SWORD);probe_object(1,0,DAGGER);probe_object(0,12,OBJ_INVENT);probe_object(1,12,OBJ_INVENT);probe_object(0,4,1);probe_link(0,0);probe_set_monster(8,0,PM_MARILITH);probe_option(19,0);
        if(op==1){probe_object(0,0,CORPSE);probe_object(0,16,PM_COCKATRICE);}
        if(op==14||op==15||op==17||op==21){probe_action(0,0,0,0,0);probe_action(5,1,0,0,0);}
        if(op==15||op==21)probe_hero(1,1);
        if(op>=18&&op<=20)probe_action(op==18?0:op==19?5:4,0,0,0,0);
        if(op==22||op==23||op==24||op==25){probe_action(0,0,0,0,0);probe_object(0,7,1);}
        oracle_number(probe_action(op,0,op==22?1:0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
    for(int op=9;op<=11;op+=2)for(int child=0;child<2;child++){probe_reset(1);probe_object(0,0,LONG_SWORD);probe_object(0,3,7);probe_object(0,12,OBJ_INVENT);probe_link(0,0);if(child)probe_action(op==9?0:4,0,0,0,0);probe_option(19,0);probe_option(20,2);oracle_number(probe_action(op,0,0,0,0));oracle_text(probe_snapshot());oracle_text(probe_trace());}
    for(int type=0;type<2;type++){probe_reset(1);probe_object(0,0,type?CRYSKNIFE:WORM_TOOTH);probe_object(0,3,9007199254740993L);probe_action(0,0,0,0,0);oracle_number(probe_action(22,-1,type?-1:1,0,0));oracle_text(probe_snapshot());}
    probe_reset(1);probe_object(0,0,LONG_SWORD);probe_object(0,1,(long)(1UL<<63)|W_WEP);probe_action(24,0,0,0,0);oracle_text(probe_snapshot());
#else
#error Native behavior case is required for every registered TU
#endif
    fflush(stdout);
}
#ifdef TELEPORT_NATIVE_ORACLE
int main(void) { probe_native_oracle(); return 0; }
#endif
