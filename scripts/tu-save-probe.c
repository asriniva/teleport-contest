/* Controlled SAVE dependency fixture; no SAVE algorithm is implemented here.
 * C original and imported JavaScript receive identical typed world records.
 * Callback traces include full serialized bytes, canonicalizing only typed fixture pointer
 * addresses only. Files, serializers and ownership dependencies are controlled. */
#include "hack.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-save-layout.h"
extern int options_set_window_colors_flag;
__typeof__(windowprocs) windowprocs;
__typeof__(WIN_MESSAGE) WIN_MESSAGE;
__typeof__(gm) gm;
__typeof__(program_state) program_state;
__typeof__(u) u;
__typeof__(soundprocs) soundprocs;
__typeof__(a11y) a11y;
__typeof__(iflags) iflags;
__typeof__(gs) gs;
__typeof__(flags) flags;
__typeof__(gl) gl;
__typeof__(uball) uball;
__typeof__(uchain) uchain;
__typeof__(gu) gu;
__typeof__(svl) svl;
__typeof__(svk) svk;
__typeof__(svh) svh;
__typeof__(gg) gg;
__typeof__(svn) svn;
__typeof__(svm) svm;
__typeof__(svc) svc;
__typeof__(urealtime) urealtime;
__typeof__(svw) svw;
__typeof__(ubirthday) ubirthday;
__typeof__(gi) gi;
__typeof__(svq) svq;
__typeof__(svs) svs;
__typeof__(svp) svp;
__typeof__(gh) gh;
__typeof__(go) go;
__typeof__(svu) svu;
__typeof__(svd) svd;
__typeof__(gf) gf;
__typeof__(gb) gb;
__typeof__(svr) svr;
__typeof__(options_set_window_colors_flag) options_set_window_colors_flag;
const struct Gender genders[4]={{.filecode="Mal"},{.filecode="Fem"},{.filecode="Ntr"}};
const struct Align aligns[4]={{.filecode="Law"},{.filecode="Neu"},{.filecode="Cha"},{.filecode="Una"}};
const char ynchars[]="yn";
static NHFILE file,freefile;
static struct obj objpool[8];static struct oextra oextras[8];
static struct monst monsters[4];static struct mextra mextras[4];static struct edog dogs[4];
static struct egd guards[4];static struct epri priests[4];static struct eshk shops[4];static struct emin minions[4];static struct ebones bones[4];
static struct permonst species[4];static struct trap traps[4];static struct fruit fruits[4];
static struct cemetery cemeteries[4];static struct damage damages[4];static stairway stairs[4];static s_level levels[4];static struct gamelog_line logs[4];static coord doors[4];
static char input[2048],tracebuf[2097152],statebuf[16384],names[8][64];static int opts[32],reentered;static void*growth;
static void append(const char*fmt,...){size_t n=strlen(tracebuf);if(n>sizeof tracebuf-8192)abort();va_list ap;va_start(ap,fmt);vsnprintf(tracebuf+n,sizeof tracebuf-n,fmt,ap);va_end(ap);}
static uint64_t canonical(uint64_t value){
#define REGION(v,id) if(value>=(uintptr_t)&(v)&&value<(uintptr_t)&(v)+sizeof(v))return ((uint64_t)(id)<<48)+(value-(uintptr_t)&(v))
 REGION(objpool,1);REGION(oextras,2);REGION(monsters,3);REGION(mextras,4);REGION(dogs,5);REGION(species,6);REGION(traps,7);REGION(fruits,8);REGION(cemeteries,9);REGION(damages,10);REGION(stairs,11);REGION(levels,12);REGION(logs,13);REGION(names,14);REGION(guards,15);REGION(priests,16);REGION(shops,17);REGION(minions,18);REGION(bones,19);REGION(doors,20);REGION(file,21);
#undef REGION
 return value;}
/* Only compiler-typed pointer fields are canonicalized. Every scalar,
 * padding byte and other serialized byte remains unchanged. Normalization does
 * not follow pointers; it preserves alias offsets within each fixture region. */
static void typed_pointer(unsigned char*out,const void*base,const void*field){uint64_t value;memcpy(&value,field,8);value=canonical(value);memcpy(out+((const unsigned char*)field-(const unsigned char*)base),&value,8);}
static void normalize_stairway(unsigned char*,const void*,const struct stairway*);
static void normalize_q_score(unsigned char*,const void*,const struct q_score*);
static void normalize_d_level(unsigned char*,const void*,const struct d_level*);
static void normalize_align(unsigned char*,const void*,const struct align*);
static void normalize_nhcoord(unsigned char*,const void*,const struct nhcoord*);
static void normalize_mkroom(unsigned char*,const void*,const struct mkroom*);
static void normalize_spell(unsigned char*,const void*,const struct spell*);
static void normalize_flag(unsigned char*,const void*,const struct flag*);
static void normalize_trap(unsigned char*,const void*,const struct trap*);
static void normalize_window_procs(unsigned char*,const void*,const struct window_procs*);
static void normalize_dig_info(unsigned char*,const void*,const struct dig_info*);
static void normalize_sound_procs(unsigned char*,const void*,const struct sound_procs*);
static void normalize_oextra(unsigned char*,const void*,const struct oextra*);
static void normalize_s_level(unsigned char*,const void*,const struct s_level*);
static void normalize_tin_info(unsigned char*,const void*,const struct tin_info*);
static void normalize_book_info(unsigned char*,const void*,const struct book_info*);
static void normalize_obj(unsigned char*,const void*,const struct obj*);
static void normalize_victual_info(unsigned char*,const void*,const struct victual_info*);
static void normalize_dest_area(unsigned char*,const void*,const struct dest_area*);
static void normalize_permonst(unsigned char*,const void*,const struct permonst*);
static void normalize_egd(unsigned char*,const void*,const struct egd*);
static void normalize_polearm_info(unsigned char*,const void*,const struct polearm_info*);
static void normalize_monst(unsigned char*,const void*,const struct monst*);
static void normalize_epri(unsigned char*,const void*,const struct epri*);
static void normalize_eshk(unsigned char*,const void*,const struct eshk*);
static void normalize_context_info(unsigned char*,const void*,const struct context_info*);
static void normalize_rm(unsigned char*,const void*,const struct rm*);
static void normalize_fruit(unsigned char*,const void*,const struct fruit*);
static void normalize_instance_globals_b(unsigned char*,const void*,const struct instance_globals_b*);
static void normalize_emin(unsigned char*,const void*,const struct emin*);
static void normalize_u_realtime(unsigned char*,const void*,const struct u_realtime*);
static void normalize_edog(unsigned char*,const void*,const struct edog*);
static void normalize_linfo(unsigned char*,const void*,const struct linfo*);
static void normalize_ebones(unsigned char*,const void*,const struct ebones*);
static void normalize_mextra(unsigned char*,const void*,const struct mextra*);
static void normalize_Role(unsigned char*,const void*,const struct Role*);
static void normalize_accessibility_data(unsigned char*,const void*,const struct accessibility_data*);
static void normalize_dgn_topology(unsigned char*,const void*,const struct dgn_topology*);
static void normalize_instance_flags(unsigned char*,const void*,const struct instance_flags*);
static void normalize_instance_globals_f(unsigned char*,const void*,const struct instance_globals_f*);
static void normalize_Race(unsigned char*,const void*,const struct Race*);
static void normalize_instance_globals_g(unsigned char*,const void*,const struct instance_globals_g*);
static void normalize_instance_globals_h(unsigned char*,const void*,const struct instance_globals_h*);
static void normalize_Gender(unsigned char*,const void*,const struct Gender*);
static void normalize_instance_globals_i(unsigned char*,const void*,const struct instance_globals_i*);
static void normalize_instance_globals_l(unsigned char*,const void*,const struct instance_globals_l*);
static void normalize_Align(unsigned char*,const void*,const struct Align*);
static void normalize_damage(unsigned char*,const void*,const struct damage*);
static void normalize_cemetery(unsigned char*,const void*,const struct cemetery*);
static void normalize_you(unsigned char*,const void*,const struct you*);
static void normalize_gamelog_line(unsigned char*,const void*,const struct gamelog_line*);
static void normalize_levelflags(unsigned char*,const void*,const struct levelflags*);
static void normalize_instance_globals_m(unsigned char*,const void*,const struct instance_globals_m*);
static void normalize_dlevel_t(unsigned char*,const void*,const dlevel_t*);
static void normalize_instance_globals_o(unsigned char*,const void*,const struct instance_globals_o*);
static void normalize_kinfo(unsigned char*,const void*,const struct kinfo*);
static void normalize_mvitals(unsigned char*,const void*,const struct mvitals*);
static void normalize_instance_globals_s(unsigned char*,const void*,const struct instance_globals_s*);
static void normalize_sinfo(unsigned char*,const void*,const struct sinfo*);
static void normalize_instance_globals_u(unsigned char*,const void*,const struct instance_globals_u*);
static void normalize_instance_globals_saved_c(unsigned char*,const void*,const struct instance_globals_saved_c*);
static void normalize_instance_globals_saved_d(unsigned char*,const void*,const struct instance_globals_saved_d*);
static void normalize_instance_globals_saved_h(unsigned char*,const void*,const struct instance_globals_saved_h*);
static void normalize_instance_globals_saved_k(unsigned char*,const void*,const struct instance_globals_saved_k*);
static void normalize_instance_globals_saved_l(unsigned char*,const void*,const struct instance_globals_saved_l*);
static void normalize_instance_globals_saved_m(unsigned char*,const void*,const struct instance_globals_saved_m*);
static void normalize_instance_globals_saved_n(unsigned char*,const void*,const struct instance_globals_saved_n*);
static void normalize_nh_file(unsigned char*,const void*,const struct nh_file*);
static void normalize_instance_globals_saved_p(unsigned char*,const void*,const struct instance_globals_saved_p*);
static void normalize_instance_globals_saved_q(unsigned char*,const void*,const struct instance_globals_saved_q*);
static void normalize_instance_globals_saved_r(unsigned char*,const void*,const struct instance_globals_saved_r*);
static void normalize_instance_globals_saved_s(unsigned char*,const void*,const struct instance_globals_saved_s*);
static void normalize_instance_globals_saved_u(unsigned char*,const void*,const struct instance_globals_saved_u*);
static void normalize_instance_globals_saved_w(unsigned char*,const void*,const struct instance_globals_saved_w*);
static void normalize_stairway(unsigned char*out,const void*base,const struct stairway*p){normalize_d_level(out,base,&p->tolev);typed_pointer(out,base,&p->next);}
static void normalize_q_score(unsigned char*out,const void*base,const struct q_score*p){}
static void normalize_d_level(unsigned char*out,const void*base,const struct d_level*p){}
static void normalize_align(unsigned char*out,const void*base,const struct align*p){}
static void normalize_nhcoord(unsigned char*out,const void*base,const struct nhcoord*p){}
static void normalize_mkroom(unsigned char*out,const void*base,const struct mkroom*p){}
static void normalize_spell(unsigned char*out,const void*base,const struct spell*p){}
static void normalize_flag(unsigned char*out,const void*base,const struct flag*p){}
static void normalize_trap(unsigned char*out,const void*base,const struct trap*p){typed_pointer(out,base,&p->ntrap);normalize_d_level(out,base,&p->dst);}
static void normalize_window_procs(unsigned char*out,const void*base,const struct window_procs*p){typed_pointer(out,base,&p->win_exit_nhwindows);typed_pointer(out,base,&p->win_clear_nhwindow);typed_pointer(out,base,&p->win_display_nhwindow);typed_pointer(out,base,&p->win_mark_synch);typed_pointer(out,base,&p->win_getmsghistory);}
static void normalize_dig_info(unsigned char*out,const void*base,const struct dig_info*p){}
static void normalize_sound_procs(unsigned char*out,const void*base,const struct sound_procs*p){typed_pointer(out,base,&p->sound_exit_nhsound);}
static void normalize_oextra(unsigned char*out,const void*base,const struct oextra*p){typed_pointer(out,base,&p->oname);typed_pointer(out,base,&p->omonst);typed_pointer(out,base,&p->omailcmd);}
static void normalize_s_level(unsigned char*out,const void*base,const struct s_level*p){typed_pointer(out,base,&p->next);}
static void normalize_tin_info(unsigned char*out,const void*base,const struct tin_info*p){typed_pointer(out,base,&p->tin);}
static void normalize_book_info(unsigned char*out,const void*base,const struct book_info*p){typed_pointer(out,base,&p->book);}
static void normalize_obj(unsigned char*out,const void*base,const struct obj*p){typed_pointer(out,base,&p->nobj);typed_pointer(out,base,&p->cobj);typed_pointer(out,base,&p->oextra);}
static void normalize_victual_info(unsigned char*out,const void*base,const struct victual_info*p){typed_pointer(out,base,&p->piece);}
static void normalize_dest_area(unsigned char*out,const void*base,const struct dest_area*p){}
static void normalize_permonst(unsigned char*out,const void*base,const struct permonst*p){}
static void normalize_egd(unsigned char*out,const void*base,const struct egd*p){}
static void normalize_polearm_info(unsigned char*out,const void*base,const struct polearm_info*p){typed_pointer(out,base,&p->hitmon);}
static void normalize_monst(unsigned char*out,const void*base,const struct monst*p){typed_pointer(out,base,&p->nmon);typed_pointer(out,base,&p->data);typed_pointer(out,base,&p->minvent);typed_pointer(out,base,&p->mextra);}
static void normalize_epri(unsigned char*out,const void*base,const struct epri*p){}
static void normalize_eshk(unsigned char*out,const void*base,const struct eshk*p){}
static void normalize_context_info(unsigned char*out,const void*base,const struct context_info*p){normalize_dig_info(out,base,&p->digging);normalize_victual_info(out,base,&p->victual);normalize_tin_info(out,base,&p->tin);normalize_book_info(out,base,&p->spbook);normalize_polearm_info(out,base,&p->polearm);}
static void normalize_rm(unsigned char*out,const void*base,const struct rm*p){}
static void normalize_fruit(unsigned char*out,const void*base,const struct fruit*p){typed_pointer(out,base,&p->nextf);}
static void normalize_instance_globals_b(unsigned char*out,const void*base,const struct instance_globals_b*p){typed_pointer(out,base,&p->billobjs);}
static void normalize_emin(unsigned char*out,const void*base,const struct emin*p){}
static void normalize_u_realtime(unsigned char*out,const void*base,const struct u_realtime*p){}
static void normalize_edog(unsigned char*out,const void*base,const struct edog*p){}
static void normalize_linfo(unsigned char*out,const void*base,const struct linfo*p){}
static void normalize_ebones(unsigned char*out,const void*base,const struct ebones*p){}
static void normalize_mextra(unsigned char*out,const void*base,const struct mextra*p){typed_pointer(out,base,&p->mgivenname);typed_pointer(out,base,&p->egd);typed_pointer(out,base,&p->epri);typed_pointer(out,base,&p->eshk);typed_pointer(out,base,&p->emin);typed_pointer(out,base,&p->edog);typed_pointer(out,base,&p->ebones);}
static void normalize_Role(unsigned char*out,const void*base,const struct Role*p){typed_pointer(out,base,&p->filecode);}
static void normalize_accessibility_data(unsigned char*out,const void*base,const struct accessibility_data*p){}
static void normalize_dgn_topology(unsigned char*out,const void*base,const struct dgn_topology*p){normalize_d_level(out,base,&p->d_water_level);normalize_d_level(out,base,&p->d_air_level);}
static void normalize_instance_flags(unsigned char*out,const void*base,const struct instance_flags*p){typed_pointer(out,base,&p->wc_tile_file);typed_pointer(out,base,&p->wc_font_map);typed_pointer(out,base,&p->wc_font_message);typed_pointer(out,base,&p->wc_font_status);typed_pointer(out,base,&p->wc_font_menu);typed_pointer(out,base,&p->wc_font_text);}
static void normalize_instance_globals_f(unsigned char*out,const void*base,const struct instance_globals_f*p){typed_pointer(out,base,&p->ftrap);typed_pointer(out,base,&p->ffruit);}
static void normalize_Race(unsigned char*out,const void*base,const struct Race*p){typed_pointer(out,base,&p->filecode);}
static void normalize_instance_globals_g(unsigned char*out,const void*base,const struct instance_globals_g*p){typed_pointer(out,base,&p->gamelog);}
static void normalize_instance_globals_h(unsigned char*out,const void*base,const struct instance_globals_h*p){}
static void normalize_Gender(unsigned char*out,const void*base,const struct Gender*p){typed_pointer(out,base,&p->filecode);}
static void normalize_instance_globals_i(unsigned char*out,const void*base,const struct instance_globals_i*p){typed_pointer(out,base,&p->invent);}
static void normalize_instance_globals_l(unsigned char*out,const void*base,const struct instance_globals_l*p){typed_pointer(out,base,&p->looseball);typed_pointer(out,base,&p->loosechain);}
static void normalize_Align(unsigned char*out,const void*base,const struct Align*p){typed_pointer(out,base,&p->filecode);}
static void normalize_damage(unsigned char*out,const void*base,const struct damage*p){typed_pointer(out,base,&p->next);}
static void normalize_cemetery(unsigned char*out,const void*base,const struct cemetery*p){typed_pointer(out,base,&p->next);}
static void normalize_you(unsigned char*out,const void*base,const struct you*p){normalize_d_level(out,base,&p->uz);normalize_align(out,base,&p->ualign);typed_pointer(out,base,&p->ustuck);typed_pointer(out,base,&p->usteed);}
static void normalize_gamelog_line(unsigned char*out,const void*base,const struct gamelog_line*p){typed_pointer(out,base,&p->text);typed_pointer(out,base,&p->next);}
static void normalize_levelflags(unsigned char*out,const void*base,const struct levelflags*p){}
static void normalize_instance_globals_m(unsigned char*out,const void*base,const struct instance_globals_m*p){typed_pointer(out,base,&p->migrating_objs);typed_pointer(out,base,&p->mydogs);typed_pointer(out,base,&p->migrating_mons);}
static void normalize_dlevel_t(unsigned char*out,const void*base,const dlevel_t*p){for(int i0=0;i0<80;i0++){for(int i1=0;i1<21;i1++){normalize_rm(out,base,&p->locations[i0][i1]);}}typed_pointer(out,base,&p->objlist);typed_pointer(out,base,&p->buriedobjlist);typed_pointer(out,base,&p->monlist);typed_pointer(out,base,&p->damagelist);typed_pointer(out,base,&p->bonesinfo);normalize_levelflags(out,base,&p->flags);}
static void normalize_instance_globals_o(unsigned char*out,const void*base,const struct instance_globals_o*p){typed_pointer(out,base,&p->objs_deleted);}
static void normalize_kinfo(unsigned char*out,const void*base,const struct kinfo*p){}
static void normalize_mvitals(unsigned char*out,const void*base,const struct mvitals*p){}
static void normalize_instance_globals_s(unsigned char*out,const void*base,const struct instance_globals_s*p){typed_pointer(out,base,&p->stairs);}
static void normalize_sinfo(unsigned char*out,const void*base,const struct sinfo*p){}
static void normalize_instance_globals_u(unsigned char*out,const void*base,const struct instance_globals_u*p){normalize_Role(out,base,&p->urole);normalize_Race(out,base,&p->urace);normalize_d_level(out,base,&p->uz_save);}
static void normalize_instance_globals_saved_c(unsigned char*out,const void*base,const struct instance_globals_saved_c*p){normalize_context_info(out,base,&p->context);}
static void normalize_instance_globals_saved_d(unsigned char*out,const void*base,const struct instance_globals_saved_d*p){normalize_dgn_topology(out,base,&p->dungeon_topology);normalize_dest_area(out,base,&p->dndest);typed_pointer(out,base,&p->doors);}
static void normalize_instance_globals_saved_h(unsigned char*out,const void*base,const struct instance_globals_saved_h*p){}
static void normalize_instance_globals_saved_k(unsigned char*out,const void*base,const struct instance_globals_saved_k*p){normalize_kinfo(out,base,&p->killer);}
static void normalize_instance_globals_saved_l(unsigned char*out,const void*base,const struct instance_globals_saved_l*p){normalize_dlevel_t(out,base,&p->level);for(int i0=0;i0<512;i0++){normalize_linfo(out,base,&p->level_info[i0]);}}
static void normalize_instance_globals_saved_m(unsigned char*out,const void*base,const struct instance_globals_saved_m*p){for(int i0=0;i0<383;i0++){normalize_mvitals(out,base,&p->mvitals[i0]);}}
static void normalize_instance_globals_saved_n(unsigned char*out,const void*base,const struct instance_globals_saved_n*p){}
static void normalize_nh_file(unsigned char*out,const void*base,const struct nh_file*p){typed_pointer(out,base,&p->fplog);}
static void normalize_instance_globals_saved_p(unsigned char*out,const void*base,const struct instance_globals_saved_p*p){}
static void normalize_instance_globals_saved_q(unsigned char*out,const void*base,const struct instance_globals_saved_q*p){normalize_q_score(out,base,&p->quest_status);}
static void normalize_instance_globals_saved_r(unsigned char*out,const void*base,const struct instance_globals_saved_r*p){for(int i0=0;i0<82;i0++){normalize_mkroom(out,base,&p->rooms[i0]);}}
static void normalize_instance_globals_saved_s(unsigned char*out,const void*base,const struct instance_globals_saved_s*p){for(int i0=0;i0<43;i0++){normalize_spell(out,base,&p->spl_book[i0]);}typed_pointer(out,base,&p->sp_levchn);}
static void normalize_instance_globals_saved_u(unsigned char*out,const void*base,const struct instance_globals_saved_u*p){normalize_dest_area(out,base,&p->updest);}
static void normalize_instance_globals_saved_w(unsigned char*out,const void*base,const struct instance_globals_saved_w*p){}
static void normalize_bytes(const char*type,unsigned char*out,const void*base){
if(!strcmp(type,"sfo_stairway"))normalize_stairway(out,base,base);
if(!strcmp(type,"sfo_q_score"))normalize_q_score(out,base,base);
if(!strcmp(type,"sfo_d_level"))normalize_d_level(out,base,base);
if(!strcmp(type,"sfo_align"))normalize_align(out,base,base);
if(!strcmp(type,"sfo_nhcoord"))normalize_nhcoord(out,base,base);
if(!strcmp(type,"sfo_mkroom"))normalize_mkroom(out,base,base);
if(!strcmp(type,"sfo_spell"))normalize_spell(out,base,base);
if(!strcmp(type,"sfo_flag"))normalize_flag(out,base,base);
if(!strcmp(type,"sfo_trap"))normalize_trap(out,base,base);
if(!strcmp(type,"sfo_window_procs"))normalize_window_procs(out,base,base);
if(!strcmp(type,"sfo_dig_info"))normalize_dig_info(out,base,base);
if(!strcmp(type,"sfo_sound_procs"))normalize_sound_procs(out,base,base);
if(!strcmp(type,"sfo_oextra"))normalize_oextra(out,base,base);
if(!strcmp(type,"sfo_s_level"))normalize_s_level(out,base,base);
if(!strcmp(type,"sfo_tin_info"))normalize_tin_info(out,base,base);
if(!strcmp(type,"sfo_book_info"))normalize_book_info(out,base,base);
if(!strcmp(type,"sfo_obj"))normalize_obj(out,base,base);
if(!strcmp(type,"sfo_victual_info"))normalize_victual_info(out,base,base);
if(!strcmp(type,"sfo_dest_area"))normalize_dest_area(out,base,base);
if(!strcmp(type,"sfo_permonst"))normalize_permonst(out,base,base);
if(!strcmp(type,"sfo_egd"))normalize_egd(out,base,base);
if(!strcmp(type,"sfo_polearm_info"))normalize_polearm_info(out,base,base);
if(!strcmp(type,"sfo_monst"))normalize_monst(out,base,base);
if(!strcmp(type,"sfo_epri"))normalize_epri(out,base,base);
if(!strcmp(type,"sfo_eshk"))normalize_eshk(out,base,base);
if(!strcmp(type,"sfo_context_info"))normalize_context_info(out,base,base);
if(!strcmp(type,"sfo_rm"))normalize_rm(out,base,base);
if(!strcmp(type,"sfo_fruit"))normalize_fruit(out,base,base);
if(!strcmp(type,"sfo_instance_globals_b"))normalize_instance_globals_b(out,base,base);
if(!strcmp(type,"sfo_emin"))normalize_emin(out,base,base);
if(!strcmp(type,"sfo_u_realtime"))normalize_u_realtime(out,base,base);
if(!strcmp(type,"sfo_edog"))normalize_edog(out,base,base);
if(!strcmp(type,"sfo_linfo"))normalize_linfo(out,base,base);
if(!strcmp(type,"sfo_ebones"))normalize_ebones(out,base,base);
if(!strcmp(type,"sfo_mextra"))normalize_mextra(out,base,base);
if(!strcmp(type,"sfo_Role"))normalize_Role(out,base,base);
if(!strcmp(type,"sfo_accessibility_data"))normalize_accessibility_data(out,base,base);
if(!strcmp(type,"sfo_dgn_topology"))normalize_dgn_topology(out,base,base);
if(!strcmp(type,"sfo_instance_flags"))normalize_instance_flags(out,base,base);
if(!strcmp(type,"sfo_instance_globals_f"))normalize_instance_globals_f(out,base,base);
if(!strcmp(type,"sfo_Race"))normalize_Race(out,base,base);
if(!strcmp(type,"sfo_instance_globals_g"))normalize_instance_globals_g(out,base,base);
if(!strcmp(type,"sfo_instance_globals_h"))normalize_instance_globals_h(out,base,base);
if(!strcmp(type,"sfo_Gender"))normalize_Gender(out,base,base);
if(!strcmp(type,"sfo_instance_globals_i"))normalize_instance_globals_i(out,base,base);
if(!strcmp(type,"sfo_instance_globals_l"))normalize_instance_globals_l(out,base,base);
if(!strcmp(type,"sfo_Align"))normalize_Align(out,base,base);
if(!strcmp(type,"sfo_damage"))normalize_damage(out,base,base);
if(!strcmp(type,"sfo_cemetery"))normalize_cemetery(out,base,base);
if(!strcmp(type,"sfo_you"))normalize_you(out,base,base);
if(!strcmp(type,"sfo_gamelog_line"))normalize_gamelog_line(out,base,base);
if(!strcmp(type,"sfo_levelflags"))normalize_levelflags(out,base,base);
if(!strcmp(type,"sfo_instance_globals_m"))normalize_instance_globals_m(out,base,base);
if(!strcmp(type,"sfo_dlevel_t"))normalize_dlevel_t(out,base,base);
if(!strcmp(type,"sfo_instance_globals_o"))normalize_instance_globals_o(out,base,base);
if(!strcmp(type,"sfo_kinfo"))normalize_kinfo(out,base,base);
if(!strcmp(type,"sfo_mvitals"))normalize_mvitals(out,base,base);
if(!strcmp(type,"sfo_instance_globals_s"))normalize_instance_globals_s(out,base,base);
if(!strcmp(type,"sfo_sinfo"))normalize_sinfo(out,base,base);
if(!strcmp(type,"sfo_instance_globals_u"))normalize_instance_globals_u(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_c"))normalize_instance_globals_saved_c(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_d"))normalize_instance_globals_saved_d(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_h"))normalize_instance_globals_saved_h(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_k"))normalize_instance_globals_saved_k(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_l"))normalize_instance_globals_saved_l(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_m"))normalize_instance_globals_saved_m(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_n"))normalize_instance_globals_saved_n(out,base,base);
if(!strcmp(type,"sfo_nh_file"))normalize_nh_file(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_p"))normalize_instance_globals_saved_p(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_q"))normalize_instance_globals_saved_q(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_r"))normalize_instance_globals_saved_r(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_s"))normalize_instance_globals_saved_s(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_u"))normalize_instance_globals_saved_u(out,base,base);
if(!strcmp(type,"sfo_instance_globals_saved_w"))normalize_instance_globals_saved_w(out,base,base);
}
static void serial(const char*type,NHFILE*f,void*p,const char*tag,size_t n){append("%s:%s:%zu:",type,tag,n);unsigned char data[n?n:1];memcpy(data,p,n);normalize_bytes(type,data,p);for(size_t i=0;i<n;i++)append("%02x",data[i]);append(";");f->wcount+=(long)n;
 if(opts[29]&&!strcmp(tag,"gamelog-length")&&*(int*)p>=0){*(int*)p=opts[29];append("outref:%d;",*(int*)p);}
 if(opts[26]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}
 if(opts[27]&&!reentered){reentered=1;savefruitchn(&freefile);append("reentered;");}
 if(opts[28]){f->mode=opts[28];append("mode:%d;",f->mode);}
}
static int oid(struct obj*p){return p?(int)(p-objpool):-1;}static int mid(struct monst*p){return p?(int)(p-monsters):-1;}
void pline(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("pline:%s;",b);}
void There(const char*fmt,...){char b[1024];va_list ap;va_start(ap,fmt);vsnprintf(b,sizeof b,fmt,ap);va_end(ap);append("there:%s;",b);}
void panic(const char*fmt,...){abort();}void impossible(const char*fmt,...){abort();}
boolean debugcore(const char*f,boolean wild){return opts[25];}
char yn_function(const char*q,const char*c,char d,boolean save){append("yn:%s:%s:%d:%d;",q,c,d,save);return opts[0];}
static void clearwin(winid w){append("clear:%d;",w);}static void displaywin(winid w,boolean b){append("display:%d:%d;",w,b);}static void exitwin(const char*s){append("exit:%s;",s);}static void synch(void){append("synch;");}
static char*msghistory(boolean init){static int next;if(init)next=0;char*p=next==0?names[0]:next==1?names[1]:next==2?input:0;next++;return p;}
void free(void*p){append("free:%llu;",(unsigned long long)canonical((uintptr_t)p));}
void dealloc_obj(struct obj*p){append("dealloc_obj:%d:%d:%d:%d:%d:%ld:%d;",oid(p),p->where,p->timed,p->lamplit,p->leashmon,p->owornmask,program_state.freeingdata);}
void dealloc_monst(struct monst*p){append("dealloc_monst:%d:%d;",mid(p),p->nmon==0);}
void setworn(struct obj*p,long mask){append("setworn:%d:%ld;",oid(p),mask);if(mask&W_BALL)uball=0;if(mask&W_CHAIN)uchain=0;}
void allunworn(void){append("allunworn;");uball=uchain=0;}
void moves_to_relative_time(long*p){append("relative:%ld;",*p);*p-=svm.moves;}
void relative_time_to_moves(long*p){append("absolute:%ld;",*p);*p+=svm.moves;}
time_t getnow(void){return 9007199254740997LL;}
long timet_delta(time_t a,time_t b){append("delta:%lld:%lld;",a,b);return (long)(a-b);}
char*yyyymmddhhmmss(time_t t){static char result[80];snprintf(result,sizeof result,"%lld",t);append("date:%lld;",t);return result;}
unsigned Strlen_(const char*s,const char*f,int line){append("strlen:%s:%d;",f,line);return strlen(s);}
void nh_snprintf(const char*f,int line,char*out,size_t n,const char*fmt,...){append("snprintf:%s:%d;",f,line);va_list ap;va_start(ap,fmt);vsnprintf(out,n,fmt,ap);va_end(ap);}
uid_t getuid(void){return 0xfedcba98U;}
xint16 ledger_no(d_level*l){append("ledger:%d:%d;",l->dnum,l->dlevel);return l->dlevel;}
xint16 maxledgerno(void){return opts[1];}
NHFILE*get_freeing_nhfile(void){append("freefile;");freefile.mode=FREEING;return &freefile;}
NHFILE*create_savefile(void){append("create_save;");return opts[2]?&file:0;}
NHFILE*open_savefile(void){append("open_save;");return opts[3]?&file:0;}
NHFILE*open_levelfile(int lev,char*why){append("open_level:%d;",lev);strcpy(why,"fixture file unavailable");return opts[4]?&file:0;}
NHFILE*create_levelfile(int lev,char*why){append("create_level:%d;",lev);strcpy(why,"fixture create unavailable");return opts[5]?&file:0;}
const char*fqname(const char*n,int prefix,int which){append("fqname:%s:%d:%d;",n,prefix,which);return (char*)n;}
void sfi_int(NHFILE*f,int*p,const char*tag){append("read:%s:%d;",tag,opts[6]);*p=opts[6];}
void sethanguphandler(void(*cb)(int)){append("hangup:%llu;",(unsigned long long)(uintptr_t)cb);}
void (sfo_cemetery)(NHFILE * a0,struct cemetery * a1,const char * a2){serial("sfo_cemetery",a0,a1,a2,sizeof *a1);}
void (sfo_char)(NHFILE * a0,char * a1,const char * a2,int a3){serial("sfo_char",a0,a1,a2,a3);}
void (sfo_context_info)(NHFILE * a0,struct context_info * a1,const char * a2){serial("sfo_context_info",a0,a1,a2,sizeof *a1);}
void (sfo_damage)(NHFILE * a0,struct damage * a1,const char * a2){serial("sfo_damage",a0,a1,a2,sizeof *a1);}
void (sfo_dest_area)(NHFILE * a0,struct dest_area * a1,const char * a2){serial("sfo_dest_area",a0,a1,a2,sizeof *a1);}
void (sfo_ebones)(NHFILE * a0,struct ebones * a1,const char * a2){serial("sfo_ebones",a0,a1,a2,sizeof *a1);}
void (sfo_edog)(NHFILE * a0,struct edog * a1,const char * a2){serial("sfo_edog",a0,a1,a2,sizeof *a1);}
void (sfo_egd)(NHFILE * a0,struct egd * a1,const char * a2){serial("sfo_egd",a0,a1,a2,sizeof *a1);}
void (sfo_emin)(NHFILE * a0,struct emin * a1,const char * a2){serial("sfo_emin",a0,a1,a2,sizeof *a1);}
void (sfo_epri)(NHFILE * a0,struct epri * a1,const char * a2){serial("sfo_epri",a0,a1,a2,sizeof *a1);}
void (sfo_eshk)(NHFILE * a0,struct eshk * a1,const char * a2){serial("sfo_eshk",a0,a1,a2,sizeof *a1);}
void (sfo_flag)(NHFILE * a0,struct flag * a1,const char * a2){serial("sfo_flag",a0,a1,a2,sizeof *a1);}
void (sfo_fruit)(NHFILE * a0,struct fruit * a1,const char * a2){serial("sfo_fruit",a0,a1,a2,sizeof *a1);}
void (sfo_gamelog_line)(NHFILE * a0,struct gamelog_line * a1,const char * a2){serial("sfo_gamelog_line",a0,a1,a2,sizeof *a1);}
void (sfo_int)(NHFILE * a0,int * a1,const char * a2){serial("sfo_int",a0,a1,a2,sizeof *a1);}
void (sfo_int32)(NHFILE * a0,int32 * a1,const char * a2){serial("sfo_int32",a0,a1,a2,sizeof *a1);}
void (sfo_levelflags)(NHFILE * a0,struct levelflags * a1,const char * a2){serial("sfo_levelflags",a0,a1,a2,sizeof *a1);}
void (sfo_long)(NHFILE * a0,long * a1,const char * a2){serial("sfo_long",a0,a1,a2,sizeof *a1);}
void (sfo_monst)(NHFILE * a0,struct monst * a1,const char * a2){serial("sfo_monst",a0,a1,a2,sizeof *a1);}
void (sfo_mvitals)(NHFILE * a0,struct mvitals * a1,const char * a2){serial("sfo_mvitals",a0,a1,a2,sizeof *a1);}
void (sfo_nhcoord)(NHFILE * a0,struct nhcoord * a1,const char * a2){serial("sfo_nhcoord",a0,a1,a2,sizeof *a1);}
void (sfo_obj)(NHFILE * a0,struct obj * a1,const char * a2){serial("sfo_obj",a0,a1,a2,sizeof *a1);}
void (sfo_q_score)(NHFILE * a0,struct q_score * a1,const char * a2){serial("sfo_q_score",a0,a1,a2,sizeof *a1);}
void (sfo_rm)(NHFILE * a0,struct rm * a1,const char * a2){serial("sfo_rm",a0,a1,a2,sizeof *a1);}
void (sfo_s_level)(NHFILE * a0,struct s_level * a1,const char * a2){serial("sfo_s_level",a0,a1,a2,sizeof *a1);}
void (sfo_schar)(NHFILE * a0,schar * a1,const char * a2){serial("sfo_schar",a0,a1,a2,sizeof *a1);}
void (sfo_spell)(NHFILE * a0,struct spell * a1,const char * a2){serial("sfo_spell",a0,a1,a2,sizeof *a1);}
void (sfo_stairway)(NHFILE * a0,struct stairway * a1,const char * a2){serial("sfo_stairway",a0,a1,a2,sizeof *a1);}
void (sfo_trap)(NHFILE * a0,struct trap * a1,const char * a2){serial("sfo_trap",a0,a1,a2,sizeof *a1);}
void (sfo_ulong)(NHFILE * a0,ulong * a1,const char * a2){serial("sfo_ulong",a0,a1,a2,sizeof *a1);}
void (sfo_unsigned)(NHFILE * a0,unsigned int * a1,const char * a2){serial("sfo_unsigned",a0,a1,a2,sizeof *a1);}
void (sfo_xint8)(NHFILE * a0,xint8 * a1,const char * a2){serial("sfo_xint8",a0,a1,a2,sizeof *a1);}
void (sfo_you)(NHFILE * a0,struct you * a1,const char * a2){serial("sfo_you",a0,a1,a2,sizeof *a1);}
void (alloc_itermonarr)(unsigned int a0){append("dependency:alloc_itermonarr;");}
void (bflush)(int a0){append("dependency:bflush;");}
void (bufoff)(int a0){append("dependency:bufoff;");}
void (bufon)(int a0){append("dependency:bufon;");}
void (change_luck)(schar a0){append("dependency:change_luck;");}
void (clear_level_structures)(void){append("dependency:clear_level_structures;");}
void (close_nhfile)(NHFILE * a0){append("dependency:close_nhfile;");}
void (cmdbind_freeall)(void){append("dependency:cmdbind_freeall;");}
void (cmdq_clear)(int a0){append("dependency:cmdq_clear;");}
void (delete_levelfile)(int a0){append("dependency:delete_levelfile;");}
int (delete_savefile)(void){append("dependency:delete_savefile;");return 0;}
void (dmonsfree)(void){append("dependency:dmonsfree;");}
void (dobjsfree)(void){append("dependency:dobjsfree;");}
void (docrt)(void){append("dependency:docrt;");}
void (done)(int a0){append("dependency:done;");}
void (done_object_cleanup)(void){append("dependency:done_object_cleanup;");}
void (dumplogfreemessages)(void){append("dependency:dumplogfreemessages;");}
void (forget_temple_entry)(struct monst * a0){append("dependency:forget_temple_entry;");}
void (free_CapMons)(void){append("dependency:free_CapMons;");}
void (free_autopickup_exceptions)(void){append("dependency:free_autopickup_exceptions;");}
void (free_convert_filenames)(void){append("dependency:free_convert_filenames;");}
void (free_glyphid_cache)(void){append("dependency:free_glyphid_cache;");}
void (free_invbuf)(void){append("dependency:free_invbuf;");}
void (free_luathemes)(enum lua_theme_group a0){append("dependency:free_luathemes;");}
void (free_maildata)(void){append("dependency:free_maildata;");}
void (free_menu_coloring)(void){append("dependency:free_menu_coloring;");}
void (free_nhuuid)(void){append("dependency:free_nhuuid;");}
void (free_rect)(void){append("dependency:free_rect;");}
void (free_symsets)(void){append("dependency:free_symsets;");}
void (free_tutorial)(void){append("dependency:free_tutorial;");}
void (free_youbuf)(void){append("dependency:free_youbuf;");}
void (freeroleoptvals)(void){append("dependency:freeroleoptvals;");}
void (getlev)(NHFILE * a0,int a1,xint8 a2){append("dependency:getlev;");}
signed char (glyphid_cache_status)(void){append("dependency:glyphid_cache_status;");return 0;}
void (mon_animal_list)(boolean a0){append("dependency:mon_animal_list;");}
void (msgtype_free)(void){append("dependency:msgtype_free;");}
void (nh_compress)(const char * a0){append("dependency:nh_compress;");}
void (nh_sfconvert)(const char * a0){append("dependency:nh_sfconvert;");}
void (nh_terminate)(int a0){append("dependency:nh_terminate;");abort();}
void (nh_uncompress)(const char * a0){append("dependency:nh_uncompress;");}
void (nomul)(int a0){append("dependency:nomul;");}
void (options_free_window_colors)(void){append("dependency:options_free_window_colors;");}
void (purge_all_custom_entries)(void){append("dependency:purge_all_custom_entries;");}
void (release_runtime_info)(void){append("dependency:release_runtime_info;");}
void (rest_adjust_levelflags)(void){append("dependency:rest_adjust_levelflags;");}
void (save_artifacts)(NHFILE * a0){append("dependency:save_artifacts;");}
void (save_dungeon)(NHFILE * a0,boolean a1,boolean a2){append("dependency:save_dungeon;");}
void (save_engravings)(NHFILE * a0){append("dependency:save_engravings;");}
void (save_exclusions)(NHFILE * a0){append("dependency:save_exclusions;");}
void (save_killers)(NHFILE * a0){append("dependency:save_killers;");}
void (save_light_sources)(NHFILE * a0,int a1){append("dependency:save_light_sources;");}
void (save_luadata)(NHFILE * a0){append("dependency:save_luadata;");}
void (save_oracles)(NHFILE * a0){append("dependency:save_oracles;");}
void (save_regions)(NHFILE * a0){append("dependency:save_regions;");}
void (save_rooms)(NHFILE * a0){append("dependency:save_rooms;");}
void (save_savefile_name)(NHFILE * a0){append("dependency:save_savefile_name;");}
void (save_timers)(NHFILE * a0,int a1){append("dependency:save_timers;");}
void (save_track)(NHFILE * a0){append("dependency:save_track;");}
void (save_waterlevel)(NHFILE * a0){append("dependency:save_waterlevel;");}
void (save_worm)(NHFILE * a0){append("dependency:save_worm;");}
void (savedsym_free)(void){append("dependency:savedsym_free;");}
void (savenames)(NHFILE * a0){append("dependency:savenames;");}
void (set_ustuck)(struct monst * a0){append("dependency:set_ustuck;");}
void (status_finish)(void){append("dependency:status_finish;");}
void (store_version)(NHFILE * a0){append("dependency:store_version;");}
void (sysopt_release)(void){append("dependency:sysopt_release;");}
void (tmp_at)(coordxy a0,coordxy a1){append("tmp_at:%d:%d;",(int)a0,(int)a1);}
void (vision_recalc)(int a0){append("dependency:vision_recalc;");}
void (wish_history_flush)(void){append("dependency:wish_history_flush;");}
#ifdef HYBRID_SAVE
extern int dosave();
extern int dosave0();
extern void teleport_save_save_gamelog(NHFILE * nhfp);
#define save_gamelog teleport_save_save_gamelog
extern void teleport_save_savegamestate(NHFILE * nhfp);
#define savegamestate teleport_save_savegamestate
extern boolean tricked_fileremoved(NHFILE * nhfp,char * whynot);
extern void savestateinlock();
extern void savelev(NHFILE * nhfp,xint8 lev);
extern void teleport_save_savelev_core(NHFILE * nhfp,xint8 lev);
#define savelev_core teleport_save_savelev_core
extern void save_adjust_levelflags();
extern void teleport_save_savelevl(NHFILE * nhfp);
#define savelevl teleport_save_savelevl
extern void teleport_save_save_bubbles(NHFILE * nhfp,xint8 lev);
#define save_bubbles teleport_save_save_bubbles
extern void savecemetery(NHFILE * nhfp,struct cemetery ** cemeteryaddr);
extern void teleport_save_savedamage(NHFILE * nhfp);
#define savedamage teleport_save_savedamage
extern void teleport_save_save_stairs(NHFILE * nhfp);
#define save_stairs teleport_save_save_stairs
extern void teleport_save_save_bc(NHFILE * nhfp);
#define save_bc teleport_save_save_bc
extern void teleport_save_saveobj(NHFILE * nhfp,struct obj * otmp);
#define saveobj teleport_save_saveobj
extern void teleport_save_saveobjchn(NHFILE * nhfp,struct obj ** obj_p);
#define saveobjchn teleport_save_saveobjchn
extern void teleport_save_savemon(NHFILE * nhfp,struct monst * mtmp);
#define savemon teleport_save_savemon
extern void teleport_save_savemonchn(NHFILE * nhfp,struct monst * mtmp);
#define savemonchn teleport_save_savemonchn
extern void teleport_save_savetrapchn(NHFILE * nhfp,struct trap * trap);
#define savetrapchn teleport_save_savetrapchn
extern void savefruitchn(NHFILE * nhfp);
extern void teleport_save_savelevchn(NHFILE * nhfp);
#define savelevchn teleport_save_savelevchn
extern void store_plname_in_file(NHFILE * nhfp);
extern void teleport_save_save_msghistory(NHFILE * nhfp);
#define save_msghistory teleport_save_save_msghistory
extern void free_dungeons();
extern void freedynamicdata();
#else
#include "../.cache/wasm64-build/tree/src/save.c"
#endif
void probe_reset(void){
memset((void*)&windowprocs,0,sizeof windowprocs);
memset((void*)&WIN_MESSAGE,0,sizeof WIN_MESSAGE);
memset((void*)&gm,0,sizeof gm);
memset((void*)&program_state,0,sizeof program_state);
memset((void*)&u,0,sizeof u);
memset((void*)&soundprocs,0,sizeof soundprocs);
memset((void*)&a11y,0,sizeof a11y);
memset((void*)&iflags,0,sizeof iflags);
memset((void*)&gs,0,sizeof gs);
memset((void*)&flags,0,sizeof flags);
memset((void*)&gl,0,sizeof gl);
memset((void*)&uball,0,sizeof uball);
memset((void*)&uchain,0,sizeof uchain);
memset((void*)&gu,0,sizeof gu);
memset((void*)&svl,0,sizeof svl);
memset((void*)&svk,0,sizeof svk);
memset((void*)&svh,0,sizeof svh);
memset((void*)&gg,0,sizeof gg);
memset((void*)&svn,0,sizeof svn);
memset((void*)&svm,0,sizeof svm);
memset((void*)&svc,0,sizeof svc);
memset((void*)&urealtime,0,sizeof urealtime);
memset((void*)&svw,0,sizeof svw);
memset((void*)&ubirthday,0,sizeof ubirthday);
memset((void*)&gi,0,sizeof gi);
memset((void*)&svq,0,sizeof svq);
memset((void*)&svs,0,sizeof svs);
memset((void*)&svp,0,sizeof svp);
memset((void*)&gh,0,sizeof gh);
memset((void*)&go,0,sizeof go);
memset((void*)&svu,0,sizeof svu);
memset((void*)&svd,0,sizeof svd);
memset((void*)&gf,0,sizeof gf);
memset((void*)&gb,0,sizeof gb);
memset((void*)&svr,0,sizeof svr);
memset((void*)&options_set_window_colors_flag,0,sizeof options_set_window_colors_flag);
memset(&file,0,sizeof file);memset(&freefile,0,sizeof freefile);memset(objpool,0,sizeof objpool);memset(oextras,0,sizeof oextras);memset(monsters,0,sizeof monsters);memset(mextras,0,sizeof mextras);memset(dogs,0,sizeof dogs);memset(species,0,sizeof species);memset(traps,0,sizeof traps);memset(fruits,0,sizeof fruits);memset(cemeteries,0,sizeof cemeteries);memset(damages,0,sizeof damages);memset(stairs,0,sizeof stairs);memset(levels,0,sizeof levels);memset(logs,0,sizeof logs);memset(names,0,sizeof names);memset(opts,0,sizeof opts);memset(input,0,sizeof input);memset(guards,0,sizeof guards);memset(priests,0,sizeof priests);memset(shops,0,sizeof shops);memset(minions,0,sizeof minions);memset(bones,0,sizeof bones);
 tracebuf[0]=0;growth=0;reentered=0;file.mode=WRITING;freefile.mode=FREEING;file.fd=7;u.uz.dnum=2;u.uz.dlevel=7;svm.moves=9007199254741001L;svh.hackpid=42;ubirthday=2147483648LL;urealtime.start_timing=9007199254740000LL;urealtime.realtime=-9007199254740997L;
 gu.urole.filecode="Wiz";gu.urace.filecode="Hum";u.ualign.type=0;strcpy(svp.plname,"Test-Hero");strcpy(names[0],"alpha");strcpy(names[1],"beta");strcpy(input,"third");
 for(int i=0;i<8;i++){objpool[i].o_id=100+i;objpool[i].where=OBJ_FLOOR;objpool[i].timed=3;objpool[i].lamplit=1;objpool[i].owornmask=0x10000000000L;objpool[i].corpsenm=7;snprintf(names[i],sizeof names[i],"object%d",i);oextras[i].oname=names[i];oextras[i].omailcmd=names[i];oextras[i].omid=400+i;}
 for(int i=0;i<4;i++){monsters[i].m_id=200+i;monsters[i].data=&species[i];monsters[i].mtemplit=1;mextras[i].mgivenname=names[i];mextras[i].mcorpsenm=50+i;dogs[i].droptime=svm.moves-20;dogs[i].hungrytime=svm.moves+30;fruits[i].fid=i-1;traps[i].dst=u.uz;traps[i].dst.dlevel=10+i;stairs[i].tolev=traps[i].dst;logs[i].text=names[i];}
 windowprocs.win_clear_nhwindow=clearwin;windowprocs.win_display_nhwindow=displaywin;windowprocs.win_exit_nhwindows=exitwin;windowprocs.win_mark_synch=synch;windowprocs.win_getmsghistory=msghistory;opts[0]='n';opts[1]=0;opts[6]=42;
}
void probe_option(int i,int v){opts[i]=v;}
void*probe_pointer(int k,int i){switch(k){case 0:return &file;case 1:return &objpool[i];case 2:return &monsters[i];case 3:return &oextras[i];case 4:return &mextras[i];case 5:return &traps[i];case 6:return &fruits[i];case 7:return &cemeteries[i];case 8:return &damages[i];case 9:return &stairs[i];case 10:return &levels[i];case 11:return &logs[i];case 12:return input;case 13:return &dogs[i];case 14:return &guards[i];case 15:return &priests[i];case 16:return &shops[i];case 17:return &minions[i];case 18:return &bones[i];case 19:return &species[i];default:abort();}}
const char*probe_trace(void){return tracebuf;}
const char*probe_snapshot(void){snprintf(statebuf,sizeof statebuf,"saving:%d notices:%d free:%d worth:%d uz:%d,%d saved:%d,%d inv:%d migrate:%d mons:%d lists:%d%d%d%d%d%d%d realtime:%lld,%lld,%ld ctx:%u,%u,%u,%u stuck:%u,%u;",program_state.saving,a11y.mon_notices_blocked,program_state.freeingdata,program_state.something_worth_saving,u.uz.dnum,u.uz.dlevel,gu.uz_save.dnum,gu.uz_save.dlevel,oid(gi.invent),oid(gm.migrating_objs),mid(gm.migrating_mons),gf.ffruit!=0,gf.ftrap!=0,gs.stairs!=0,svl.level.bonesinfo!=0,svl.level.damagelist!=0,svs.sp_levchn!=0,gg.gamelog!=0,urealtime.start_timing,urealtime.finish_time,urealtime.realtime,svc.context.victual.o_id,svc.context.tin.o_id,svc.context.spbook.o_id,svc.context.polearm.m_id,u.ustuck_mid,u.usteed_mid);return statebuf;}
int probe_action(int op,int i){switch(op){
case 0:return dosave();case 1:return dosave0();case 2:save_gamelog(&file);break;case 3:savegamestate(&file);break;case 4:return tricked_fileremoved(opts[7]?&file:0,input);case 5:savestateinlock();break;
case 6:savelev(&file,i);break;case 7:savelev_core(&file,i);break;case 8:save_adjust_levelflags();break;case 9:savelevl(&file);break;case 10:save_bubbles(&file,i);break;case 11:savecemetery(&file,&svl.level.bonesinfo);break;
case 12:savedamage(&file);break;case 13:save_stairs(&file);break;case 14:save_bc(&file);break;case 15:saveobj(&file,&objpool[i]);break;case 16:saveobjchn(&file,&gi.invent);break;case 17:savemon(&file,&monsters[i]);break;case 18:savemonchn(&file,gm.migrating_mons);break;
case 19:savetrapchn(&file,gf.ftrap);break;case 20:savefruitchn(&file);break;case 21:savelevchn(&file);break;case 22:store_plname_in_file(&file);break;case 23:save_msghistory(&file);break;case 24:free_dungeons();break;case 25:freedynamicdata();break;default:abort();}return 0;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return sizeof save_layout/sizeof save_layout[0];}
const char*probe_layout_name(int i){return save_layout[i].name;}
size_t probe_layout_value(int i){return save_layout[i].value;}

int probe_disp_freemem(void){return DISP_FREEMEM;}
