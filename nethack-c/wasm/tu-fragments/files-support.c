/* FILES typed field/header/dependency/storage transport only. Source algorithms remain JS. */
#include "../../../scripts/tu-files-layout.h"
#include <stdlib.h>
/* Typed FILES foreign-service forwarding; compression policy remains in JS. */
extern int teleport_compress_file(const char *, const char *, int);
int teleport_files_compress_file(const char *filename, const char *compressed, int unpack)
{
    return teleport_compress_file(filename, compressed, unpack);
}
#ifndef TELEPORT_FILES_ORIGINAL_INCLUDED
struct sfstatus_to_msg { int sfstatus; const char *msg; };
#endif
_Static_assert(sizeof(void*)==8&&sizeof(long)==8&&sizeof(size_t)==8,"Review FILES LP64");
_Static_assert(sizeof(boolean)==1&&(boolean)-1<0&&sizeof(xint8)==1&&(xint8)-1<0&&sizeof(coordxy)==2&&(char)-1<0,"Review FILES scalar widths");
void*teleport_files_global(int index){switch(index){
case 0:return(void*)&gl;
case 1:return(void*)&svl;
case 2:return(void*)&program_state;
case 3:return(void*)&svn;
case 4:return(void*)&sysopt;
case 5:return(void*)&ubirthday;
case 6:return(void*)&svd;
case 7:return(void*)&gu;
case 8:return(void*)&gb;
case 9:return(void*)&flags;
case 10:return(void*)&gs;
case 11:return(void*)&svp;
case 12:return(void*)&stderr;
case 13:return(void*)&windowprocs;
case 14:return(void*)&iflags;
case 15:return(void*)&WIN_MESSAGE;
case 16:return(void*)&gn;
case 17:return(void*)&gw;
case 18:return(void*)&hands_obj;
case 19:return(void*)&gi;
case 20:return(void*)&gc;
case 21:return(void*)&gd;
case 22:return(void*)&gh;
case 23:return(void*)&svc;
case 24:return(void*)&u;
case 25:return(void*)&genders;
case 26:return(void*)&aligns;
case 27:return(void*)&svm;
default:abort();}}
uint64_t teleport_files_layout(int index){switch(index){
case 0:return(uint64_t)(sizeof(void*));
case 1:return(uint64_t)(sizeof(long));
case 2:return(uint64_t)(sizeof(int));
case 3:return(uint64_t)((char)-1<0);
case 4:return(uint64_t)(__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__);
case 5:return(uint64_t)(sizeof(struct Align));
case 6:return(uint64_t)(sizeof(struct Gender));
case 7:return(uint64_t)(sizeof(struct Race));
case 8:return(uint64_t)(sizeof(struct Role));
case 9:return(uint64_t)(sizeof(struct align));
case 10:return(uint64_t)(sizeof(struct context_info));
case 11:return(uint64_t)(sizeof(struct d_level));
case 12:return(uint64_t)(sizeof(struct dirent));
case 13:return(uint64_t)(sizeof(struct dungeon));
case 14:return(uint64_t)(sizeof(struct fieldlevel_content));
case 15:return(uint64_t)(sizeof(struct flag));
case 16:return(uint64_t)(sizeof(struct flock));
case 17:return(uint64_t)(sizeof(struct instance_flags));
case 18:return(uint64_t)(sizeof(struct instance_globals_b));
case 19:return(uint64_t)(sizeof(struct instance_globals_c));
case 20:return(uint64_t)(sizeof(struct instance_globals_d));
case 21:return(uint64_t)(sizeof(struct instance_globals_h));
case 22:return(uint64_t)(sizeof(struct instance_globals_i));
case 23:return(uint64_t)(sizeof(struct instance_globals_l));
case 24:return(uint64_t)(sizeof(struct instance_globals_n));
case 25:return(uint64_t)(sizeof(struct instance_globals_s));
case 26:return(uint64_t)(sizeof(struct instance_globals_saved_c));
case 27:return(uint64_t)(sizeof(struct instance_globals_saved_d));
case 28:return(uint64_t)(sizeof(struct instance_globals_saved_l));
case 29:return(uint64_t)(sizeof(struct instance_globals_saved_m));
case 30:return(uint64_t)(sizeof(struct instance_globals_saved_n));
case 31:return(uint64_t)(sizeof(struct instance_globals_saved_p));
case 32:return(uint64_t)(sizeof(struct instance_globals_u));
case 33:return(uint64_t)(sizeof(struct instance_globals_w));
case 34:return(uint64_t)(sizeof(struct linfo));
case 35:return(uint64_t)(sizeof(struct nh_file));
case 36:return(uint64_t)(sizeof(struct novel_tracking));
case 37:return(uint64_t)(sizeof(struct obj));
case 38:return(uint64_t)(sizeof(struct s_level));
case 39:return(uint64_t)(sizeof(struct sfstatus_to_msg));
case 40:return(uint64_t)(sizeof(struct sinfo));
case 41:return(uint64_t)(sizeof(struct symsetentry));
case 42:return(uint64_t)(sizeof(struct sysopt_s));
case 43:return(uint64_t)(sizeof(struct window_procs));
case 44:return(uint64_t)(sizeof(struct you));
case 45:return(uint64_t)(COIN_CLASS);
case 46:return(uint64_t)(PM_CLERIC);
case 47:return(uint64_t)(exportascii);
case 48:return(uint64_t)(historical);
case 49:return(uint64_t)(invlet_basic);
case 50:return(uint64_t)(wp_tty);
default:abort();}}
uint64_t teleport_files_read(int kind,void*at,int field){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 1:{struct Gender*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 2:{struct Race*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->filecode);
case 1:return(uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 4:{struct align*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->type);
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->novel);
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->dnum);
case 1:return(uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 7:{struct dirent*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->d_name);
default:abort();}}
case 8:{struct dungeon*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->boneid);
default:abort();}}
case 9:{struct fieldlevel_content*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deflt);
case 1:return(uint64_t)(uintptr_t)(p->binary);
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debug);
case 1:return(uint64_t)(uintptr_t)(p->explore);
case 2:return(uint64_t)(uintptr_t)(p->female);
default:abort();}}
case 11:{struct flock*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->l_type);
case 1:return(uint64_t)(uintptr_t)(p->l_whence);
case 2:return(uint64_t)(uintptr_t)(p->l_start);
case 3:return(uint64_t)(uintptr_t)(p->l_len);
case 4:return(uint64_t)(uintptr_t)(p->l_pid);
default:abort();}}
case 12:{struct instance_flags*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->last_msg);
case 1:return(uint64_t)(uintptr_t)(p->window_inited);
default:abort();}}
case 13:{struct instance_globals_b*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->bones);
default:abort();}}
case 14:{struct instance_globals_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->chosen_symset_start);
case 1:return(uint64_t)(uintptr_t)(p->chosen_symset_end);
default:abort();}}
case 15:{struct instance_globals_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->deferred_showpaths);
case 1:return(uint64_t)(uintptr_t)(p->deferred_showpaths_dir);
default:abort();}}
case 16:{struct instance_globals_h*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->hname);
default:abort();}}
case 17:{struct instance_globals_i*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->invent);
default:abort();}}
case 18:{struct instance_globals_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->lock);
default:abort();}}
case 19:{struct instance_globals_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->nesting);
default:abort();}}
case 20:{struct instance_globals_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->symset);
case 1:return(uint64_t)(uintptr_t)(p->symset_count);
case 2:return(uint64_t)(uintptr_t)(p->symset_which_set);
case 3:return(uint64_t)(uintptr_t)(&p->SAVEF);
default:abort();}}
case 21:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->context);
default:abort();}}
case 22:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->dungeons);
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->level_info);
default:abort();}}
case 24:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->moves);
default:abort();}}
case 25:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->n_dgns);
default:abort();}}
case 26:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->plname);
default:abort();}}
case 27:{struct instance_globals_u*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->urole);
case 1:return(uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 28:{struct instance_globals_w*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->wizkit);
default:abort();}}
case 29:{struct linfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->flags);
default:abort();}}
case 30:{struct nh_file*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->fd);
case 1:return(uint64_t)(uintptr_t)(p->mode);
case 2:return(uint64_t)(uintptr_t)(p->ftype);
case 3:return(uint64_t)(uintptr_t)(p->fnidx);
case 4:return(uint64_t)(uintptr_t)(p->rcount);
case 5:return(uint64_t)(uintptr_t)(p->wcount);
case 6:return(uint64_t)(uintptr_t)(p->structlevel);
case 7:return(uint64_t)(uintptr_t)(p->fieldlevel);
case 8:return(uint64_t)(uintptr_t)(p->addinfo);
case 9:return(uint64_t)(uintptr_t)(p->eof);
case 10:return(uint64_t)(uintptr_t)(p->bendian);
case 11:return(uint64_t)(uintptr_t)(p->fpdef);
case 12:return(uint64_t)(uintptr_t)(p->fplog);
case 13:return(uint64_t)(uintptr_t)(p->fpdebug);
case 14:return(uint64_t)(uintptr_t)(&p->style);
case 15:return(uint64_t)(uintptr_t)(p->nhfpconvert);
default:abort();}}
case 31:{struct novel_tracking*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->id);
case 1:return(uint64_t)(uintptr_t)(p->count);
case 2:return(uint64_t)(uintptr_t)(&p->pasg);
default:abort();}}
case 32:{struct obj*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->ox);
case 1:return(uint64_t)(uintptr_t)(p->oy);
case 2:return(uint64_t)(uintptr_t)(p->oclass);
case 3:return(uint64_t)(uintptr_t)(p->bknown);
case 4:return(uint64_t)(uintptr_t)(p->owornmask);
default:abort();}}
case 33:{struct s_level*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->boneid);
default:abort();}}
case 34:{struct sfstatus_to_msg*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->sfstatus);
case 1:return(uint64_t)(uintptr_t)(p->msg);
default:abort();}}
case 35:{struct sinfo*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->done_hup);
case 1:return(uint64_t)(uintptr_t)(p->preserve_locks);
case 2:return(uint64_t)(uintptr_t)(p->in_self_recover);
case 3:return(uint64_t)(uintptr_t)(p->in_paniclog);
case 4:return(uint64_t)(uintptr_t)(p->wizkit_wishing);
default:abort();}}
case 36:{struct symsetentry*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->name);
case 1:return(uint64_t)(uintptr_t)(p->explicitly);
default:abort();}}
case 37:{struct sysopt_s*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->debugfiles);
case 1:return(uint64_t)(uintptr_t)(p->bones_pools);
case 2:return(uint64_t)(uintptr_t)(p->livelog);
case 3:return(uint64_t)(uintptr_t)(&p->bonesformat);
default:abort();}}
case 38:{struct window_procs*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(p->wp_id);
case 1:return(uint64_t)(uintptr_t)(p->win_create_nhwindow);
case 2:return(uint64_t)(uintptr_t)(p->win_clear_nhwindow);
case 3:return(uint64_t)(uintptr_t)(p->win_display_nhwindow);
case 4:return(uint64_t)(uintptr_t)(p->win_destroy_nhwindow);
case 5:return(uint64_t)(uintptr_t)(p->win_putstr);
case 6:return(uint64_t)(uintptr_t)(p->win_mark_synch);
case 7:return(uint64_t)(uintptr_t)(p->win_wait_synch);
case 8:return(uint64_t)(uintptr_t)(p->win_raw_print);
case 9:return(uint64_t)(uintptr_t)(p->win_putmsghistory);
default:abort();}}
case 39:{struct you*p=at;switch(field){
case 0:return(uint64_t)(uintptr_t)(&p->ualign);
default:abort();}}
default:abort();}}
void teleport_files_write(int kind,void*at,int field,uint64_t value){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:p->filecode=(__typeof__(p->filecode))value;return;
default:abort();}}
case 1:{struct Gender*p=at;switch(field){
case 0:p->filecode=(__typeof__(p->filecode))value;return;
default:abort();}}
case 2:{struct Race*p=at;switch(field){
case 0:p->filecode=(__typeof__(p->filecode))value;return;
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:p->filecode=(__typeof__(p->filecode))value;return;
case 1:p->mnum=(__typeof__(p->mnum))value;return;
default:abort();}}
case 4:{struct align*p=at;switch(field){
case 0:p->type=(__typeof__(p->type))value;return;
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:p->dnum=(__typeof__(p->dnum))value;return;
case 1:p->dlevel=(__typeof__(p->dlevel))value;return;
default:abort();}}
case 7:{struct dirent*p=at;switch(field){
default:abort();}}
case 8:{struct dungeon*p=at;switch(field){
case 0:p->boneid=(__typeof__(p->boneid))value;return;
default:abort();}}
case 9:{struct fieldlevel_content*p=at;switch(field){
case 0:p->deflt=(__typeof__(p->deflt))value;return;
case 1:p->binary=(__typeof__(p->binary))value;return;
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:p->debug=(__typeof__(p->debug))value;return;
case 1:p->explore=(__typeof__(p->explore))value;return;
case 2:p->female=(__typeof__(p->female))value;return;
default:abort();}}
case 11:{struct flock*p=at;switch(field){
case 0:p->l_type=(__typeof__(p->l_type))value;return;
case 1:p->l_whence=(__typeof__(p->l_whence))value;return;
case 2:p->l_start=(__typeof__(p->l_start))value;return;
case 3:p->l_len=(__typeof__(p->l_len))value;return;
case 4:p->l_pid=(__typeof__(p->l_pid))value;return;
default:abort();}}
case 12:{struct instance_flags*p=at;switch(field){
case 0:p->last_msg=(__typeof__(p->last_msg))value;return;
case 1:p->window_inited=(__typeof__(p->window_inited))value;return;
default:abort();}}
case 13:{struct instance_globals_b*p=at;switch(field){
default:abort();}}
case 14:{struct instance_globals_c*p=at;switch(field){
case 0:p->chosen_symset_start=(__typeof__(p->chosen_symset_start))value;return;
case 1:p->chosen_symset_end=(__typeof__(p->chosen_symset_end))value;return;
default:abort();}}
case 15:{struct instance_globals_d*p=at;switch(field){
case 0:p->deferred_showpaths=(__typeof__(p->deferred_showpaths))value;return;
case 1:p->deferred_showpaths_dir=(__typeof__(p->deferred_showpaths_dir))value;return;
default:abort();}}
case 16:{struct instance_globals_h*p=at;switch(field){
case 0:p->hname=(__typeof__(p->hname))value;return;
default:abort();}}
case 17:{struct instance_globals_i*p=at;switch(field){
case 0:p->invent=(__typeof__(p->invent))value;return;
default:abort();}}
case 18:{struct instance_globals_l*p=at;switch(field){
default:abort();}}
case 19:{struct instance_globals_n*p=at;switch(field){
case 0:p->nesting=(__typeof__(p->nesting))value;return;
default:abort();}}
case 20:{struct instance_globals_s*p=at;switch(field){
case 1:p->symset_count=(__typeof__(p->symset_count))value;return;
case 2:p->symset_which_set=(__typeof__(p->symset_which_set))value;return;
default:abort();}}
case 21:{struct instance_globals_saved_c*p=at;switch(field){
default:abort();}}
case 22:{struct instance_globals_saved_d*p=at;switch(field){
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
default:abort();}}
case 24:{struct instance_globals_saved_m*p=at;switch(field){
case 0:p->moves=(__typeof__(p->moves))value;return;
default:abort();}}
case 25:{struct instance_globals_saved_n*p=at;switch(field){
case 0:p->n_dgns=(__typeof__(p->n_dgns))value;return;
default:abort();}}
case 26:{struct instance_globals_saved_p*p=at;switch(field){
default:abort();}}
case 27:{struct instance_globals_u*p=at;switch(field){
default:abort();}}
case 28:{struct instance_globals_w*p=at;switch(field){
default:abort();}}
case 29:{struct linfo*p=at;switch(field){
case 0:p->flags=(__typeof__(p->flags))value;return;
default:abort();}}
case 30:{struct nh_file*p=at;switch(field){
case 0:p->fd=(__typeof__(p->fd))value;return;
case 1:p->mode=(__typeof__(p->mode))value;return;
case 2:p->ftype=(__typeof__(p->ftype))value;return;
case 3:p->fnidx=(__typeof__(p->fnidx))value;return;
case 4:p->rcount=(__typeof__(p->rcount))value;return;
case 5:p->wcount=(__typeof__(p->wcount))value;return;
case 6:p->structlevel=(__typeof__(p->structlevel))value;return;
case 7:p->fieldlevel=(__typeof__(p->fieldlevel))value;return;
case 8:p->addinfo=(__typeof__(p->addinfo))value;return;
case 9:p->eof=(__typeof__(p->eof))value;return;
case 10:p->bendian=(__typeof__(p->bendian))value;return;
case 11:p->fpdef=(__typeof__(p->fpdef))value;return;
case 12:p->fplog=(__typeof__(p->fplog))value;return;
case 13:p->fpdebug=(__typeof__(p->fpdebug))value;return;
case 15:p->nhfpconvert=(__typeof__(p->nhfpconvert))value;return;
default:abort();}}
case 31:{struct novel_tracking*p=at;switch(field){
case 0:p->id=(__typeof__(p->id))value;return;
case 1:p->count=(__typeof__(p->count))value;return;
default:abort();}}
case 32:{struct obj*p=at;switch(field){
case 0:p->ox=(__typeof__(p->ox))value;return;
case 1:p->oy=(__typeof__(p->oy))value;return;
case 2:p->oclass=(__typeof__(p->oclass))value;return;
case 3:p->bknown=(unsigned int)value;return;
case 4:p->owornmask=(__typeof__(p->owornmask))value;return;
default:abort();}}
case 33:{struct s_level*p=at;switch(field){
case 0:p->boneid=(__typeof__(p->boneid))value;return;
default:abort();}}
case 34:{struct sfstatus_to_msg*p=at;switch(field){
case 0:p->sfstatus=(__typeof__(p->sfstatus))value;return;
case 1:p->msg=(__typeof__(p->msg))value;return;
default:abort();}}
case 35:{struct sinfo*p=at;switch(field){
case 0:p->done_hup=(__typeof__(p->done_hup))value;return;
case 1:p->preserve_locks=(__typeof__(p->preserve_locks))value;return;
case 2:p->in_self_recover=(__typeof__(p->in_self_recover))value;return;
case 3:p->in_paniclog=(__typeof__(p->in_paniclog))value;return;
case 4:p->wizkit_wishing=(__typeof__(p->wizkit_wishing))value;return;
default:abort();}}
case 36:{struct symsetentry*p=at;switch(field){
case 0:p->name=(__typeof__(p->name))value;return;
case 1:p->explicitly=(unsigned int)value;return;
default:abort();}}
case 37:{struct sysopt_s*p=at;switch(field){
case 0:p->debugfiles=(__typeof__(p->debugfiles))value;return;
case 1:p->bones_pools=(__typeof__(p->bones_pools))value;return;
case 2:p->livelog=(__typeof__(p->livelog))value;return;
default:abort();}}
case 38:{struct window_procs*p=at;switch(field){
case 0:p->wp_id=(__typeof__(p->wp_id))value;return;
case 1:p->win_create_nhwindow=(__typeof__(p->win_create_nhwindow))value;return;
case 2:p->win_clear_nhwindow=(__typeof__(p->win_clear_nhwindow))value;return;
case 3:p->win_display_nhwindow=(__typeof__(p->win_display_nhwindow))value;return;
case 4:p->win_destroy_nhwindow=(__typeof__(p->win_destroy_nhwindow))value;return;
case 5:p->win_putstr=(__typeof__(p->win_putstr))value;return;
case 6:p->win_mark_synch=(__typeof__(p->win_mark_synch))value;return;
case 7:p->win_wait_synch=(__typeof__(p->win_wait_synch))value;return;
case 8:p->win_raw_print=(__typeof__(p->win_raw_print))value;return;
case 9:p->win_putmsghistory=(__typeof__(p->win_putmsghistory))value;return;
default:abort();}}
case 39:{struct you*p=at;switch(field){
default:abort();}}
default:abort();}}
void* teleport_files_address(int kind,void*at,int field){switch(kind){
case 0:{struct Align*p=at;switch(field){
case 0:return(void*)&p->filecode;
default:abort();}}
case 1:{struct Gender*p=at;switch(field){
case 0:return(void*)&p->filecode;
default:abort();}}
case 2:{struct Race*p=at;switch(field){
case 0:return(void*)&p->filecode;
default:abort();}}
case 3:{struct Role*p=at;switch(field){
case 0:return(void*)&p->filecode;
case 1:return(void*)&p->mnum;
default:abort();}}
case 4:{struct align*p=at;switch(field){
case 0:return(void*)&p->type;
default:abort();}}
case 5:{struct context_info*p=at;switch(field){
case 0:return(void*)&p->novel;
default:abort();}}
case 6:{struct d_level*p=at;switch(field){
case 0:return(void*)&p->dnum;
case 1:return(void*)&p->dlevel;
default:abort();}}
case 7:{struct dirent*p=at;switch(field){
case 0:return(void*)&p->d_name;
default:abort();}}
case 8:{struct dungeon*p=at;switch(field){
case 0:return(void*)&p->boneid;
default:abort();}}
case 9:{struct fieldlevel_content*p=at;switch(field){
case 0:return(void*)&p->deflt;
case 1:return(void*)&p->binary;
default:abort();}}
case 10:{struct flag*p=at;switch(field){
case 0:return(void*)&p->debug;
case 1:return(void*)&p->explore;
case 2:return(void*)&p->female;
default:abort();}}
case 11:{struct flock*p=at;switch(field){
case 0:return(void*)&p->l_type;
case 1:return(void*)&p->l_whence;
case 2:return(void*)&p->l_start;
case 3:return(void*)&p->l_len;
case 4:return(void*)&p->l_pid;
default:abort();}}
case 12:{struct instance_flags*p=at;switch(field){
case 0:return(void*)&p->last_msg;
case 1:return(void*)&p->window_inited;
default:abort();}}
case 13:{struct instance_globals_b*p=at;switch(field){
case 0:return(void*)&p->bones;
default:abort();}}
case 14:{struct instance_globals_c*p=at;switch(field){
case 0:return(void*)&p->chosen_symset_start;
case 1:return(void*)&p->chosen_symset_end;
default:abort();}}
case 15:{struct instance_globals_d*p=at;switch(field){
case 0:return(void*)&p->deferred_showpaths;
case 1:return(void*)&p->deferred_showpaths_dir;
default:abort();}}
case 16:{struct instance_globals_h*p=at;switch(field){
case 0:return(void*)&p->hname;
default:abort();}}
case 17:{struct instance_globals_i*p=at;switch(field){
case 0:return(void*)&p->invent;
default:abort();}}
case 18:{struct instance_globals_l*p=at;switch(field){
case 0:return(void*)&p->lock;
default:abort();}}
case 19:{struct instance_globals_n*p=at;switch(field){
case 0:return(void*)&p->nesting;
default:abort();}}
case 20:{struct instance_globals_s*p=at;switch(field){
case 0:return(void*)&p->symset;
case 1:return(void*)&p->symset_count;
case 2:return(void*)&p->symset_which_set;
case 3:return(void*)&p->SAVEF;
default:abort();}}
case 21:{struct instance_globals_saved_c*p=at;switch(field){
case 0:return(void*)&p->context;
default:abort();}}
case 22:{struct instance_globals_saved_d*p=at;switch(field){
case 0:return(void*)&p->dungeons;
default:abort();}}
case 23:{struct instance_globals_saved_l*p=at;switch(field){
case 0:return(void*)&p->level_info;
default:abort();}}
case 24:{struct instance_globals_saved_m*p=at;switch(field){
case 0:return(void*)&p->moves;
default:abort();}}
case 25:{struct instance_globals_saved_n*p=at;switch(field){
case 0:return(void*)&p->n_dgns;
default:abort();}}
case 26:{struct instance_globals_saved_p*p=at;switch(field){
case 0:return(void*)&p->plname;
default:abort();}}
case 27:{struct instance_globals_u*p=at;switch(field){
case 0:return(void*)&p->urole;
case 1:return(void*)&p->urace;
default:abort();}}
case 28:{struct instance_globals_w*p=at;switch(field){
case 0:return(void*)&p->wizkit;
default:abort();}}
case 29:{struct linfo*p=at;switch(field){
case 0:return(void*)&p->flags;
default:abort();}}
case 30:{struct nh_file*p=at;switch(field){
case 0:return(void*)&p->fd;
case 1:return(void*)&p->mode;
case 2:return(void*)&p->ftype;
case 3:return(void*)&p->fnidx;
case 4:return(void*)&p->rcount;
case 5:return(void*)&p->wcount;
case 6:return(void*)&p->structlevel;
case 7:return(void*)&p->fieldlevel;
case 8:return(void*)&p->addinfo;
case 9:return(void*)&p->eof;
case 10:return(void*)&p->bendian;
case 11:return(void*)&p->fpdef;
case 12:return(void*)&p->fplog;
case 13:return(void*)&p->fpdebug;
case 14:return(void*)&p->style;
case 15:return(void*)&p->nhfpconvert;
default:abort();}}
case 31:{struct novel_tracking*p=at;switch(field){
case 0:return(void*)&p->id;
case 1:return(void*)&p->count;
case 2:return(void*)&p->pasg;
default:abort();}}
case 32:{struct obj*p=at;switch(field){
case 0:return(void*)&p->ox;
case 1:return(void*)&p->oy;
case 2:return(void*)&p->oclass;
case 4:return(void*)&p->owornmask;
default:abort();}}
case 33:{struct s_level*p=at;switch(field){
case 0:return(void*)&p->boneid;
default:abort();}}
case 34:{struct sfstatus_to_msg*p=at;switch(field){
case 0:return(void*)&p->sfstatus;
case 1:return(void*)&p->msg;
default:abort();}}
case 35:{struct sinfo*p=at;switch(field){
case 0:return(void*)&p->done_hup;
case 1:return(void*)&p->preserve_locks;
case 2:return(void*)&p->in_self_recover;
case 3:return(void*)&p->in_paniclog;
case 4:return(void*)&p->wizkit_wishing;
default:abort();}}
case 36:{struct symsetentry*p=at;switch(field){
case 0:return(void*)&p->name;
default:abort();}}
case 37:{struct sysopt_s*p=at;switch(field){
case 0:return(void*)&p->debugfiles;
case 1:return(void*)&p->bones_pools;
case 2:return(void*)&p->livelog;
case 3:return(void*)&p->bonesformat;
default:abort();}}
case 38:{struct window_procs*p=at;switch(field){
case 0:return(void*)&p->wp_id;
case 1:return(void*)&p->win_create_nhwindow;
case 2:return(void*)&p->win_clear_nhwindow;
case 3:return(void*)&p->win_display_nhwindow;
case 4:return(void*)&p->win_destroy_nhwindow;
case 5:return(void*)&p->win_putstr;
case 6:return(void*)&p->win_mark_synch;
case 7:return(void*)&p->win_wait_synch;
case 8:return(void*)&p->win_raw_print;
case 9:return(void*)&p->win_putmsghistory;
default:abort();}}
case 39:{struct you*p=at;switch(field){
case 0:return(void*)&p->ualign;
default:abort();}}
default:abort();}}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#pragma clang diagnostic ignored "-Wformat-nonliteral"
int teleport_files_var0(char * a0,char * a1,int a2,int a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_files_var1(char * a0,char * a1,int a2,int a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_files_var2(char * a0){(impossible)(a0);}
void teleport_files_var3(char * a0){(impossible)(a0);}
int teleport_files_var4(struct _IO_FILE * a0,char * a1){return (fprintf)(a0,a1);}
int teleport_files_var5(struct _IO_FILE * a0,char * a1){return (fprintf)(a0,a1);}
int teleport_files_var6(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_files_var7(char * a0,char * a1,char * a2,int a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_files_var8(char * a0,int a1,int a2){return (open)(a0,a1,a2);}
int teleport_files_var9(char * a0,char * a1,char * a2,int a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
int teleport_files_var10(char * a0,char * a1,unsigned int a2){return (sprintf)(a0,a1,a2);}
int teleport_files_var11(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_files_var12(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_files_var13(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
int teleport_files_var14(char * a0,char * a1){return (sprintf)(a0,a1);}
int teleport_files_var15(char * a0,char * a1,char * a2,char * a3,int a4){return (sprintf)(a0,a1,a2,a3,a4);}
void teleport_files_var16(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
int teleport_files_var17(char * a0,int a1,int a2){return (open)(a0,a1,a2);}
int teleport_files_var18(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_files_var19(char * a0,int a1,int a2){return (open)(a0,a1,a2);}
int teleport_files_var20(char * a0,char * a1,int * a2,char * a3){return (sscanf)(a0,a1,a2,a3);}
int teleport_files_var21(char * a0,char * a1,int a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
int teleport_files_var22(struct _IO_FILE * a0,char * a1,char * a2,char * a3,int a4,char * a5){return (fprintf)(a0,a1,a2,a3,a4,a5);}
void teleport_files_var23(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_files_var24(char * a0,char * a1,char * a2,char * a3){(raw_printf)(a0,a1,a2,a3);}
void teleport_files_var25(char * a0,int a1,char * a2,unsigned long a3,char * a4,char * a5,char * a6,char * a7){(nh_snprintf)(a0,a1,a2,a3,a4,a5,a6,a7);}
void teleport_files_var26(char * a0){(impossible)(a0);}
int teleport_files_var27(char * a0,int a1){return (open)(a0,a1);}
void teleport_files_var28(char * a0,char * a1){(raw_printf)(a0,a1);}
int teleport_files_var29(int a0,int a1,struct flock * a2){return (fcntl)(a0,a1,a2);}
void teleport_files_var30(char * a0,char * a1,int a2){(raw_printf)(a0,a1,a2);}
void teleport_files_var31(char * a0,char * a1){(raw_printf)(a0,a1);}
int teleport_files_var32(int a0,int a1,struct flock * a2){return (fcntl)(a0,a1,a2);}
void teleport_files_var33(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_files_var34(char * a0,char * a1,int a2){(raw_printf)(a0,a1,a2);}
void teleport_files_var35(char * a0,char * a1,int a2){(raw_printf)(a0,a1,a2);}
int teleport_files_var36(char * a0,char * a1,char * a2,char * a3){return (sprintf)(a0,a1,a2,a3);}
void teleport_files_var37(char * a0,char * a1,int a2){(raw_printf)(a0,a1,a2);}
void teleport_files_var38(char * a0,char * a1){(config_error_add)(a0,a1);}
void teleport_files_var39(char * a0,char * a1){(config_error_add)(a0,a1);}
int teleport_files_var40(char * a0,int a1,int a2){return (open)(a0,a1,a2);}
int teleport_files_var41(char * a0,int a1,int a2){return (open)(a0,a1,a2);}
void teleport_files_var42(char * a0,char * a1){(raw_printf)(a0,a1);}
int teleport_files_var43(struct _IO_FILE * a0,char * a1,char * a2,long a3,long a4,int a5,int a6,char * a7,char * a8){return (fprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8);}
int teleport_files_var44(struct _IO_FILE * a0,char * a1,char * a2,char * a3){return (fprintf)(a0,a1,a2,a3);}
void teleport_files_var45(char * a0,char * a1,char * a2,char * a3){(raw_printf)(a0,a1,a2,a3);}
void teleport_files_var46(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_files_var47(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_files_var48(char * a0,char * a1,char * a2){(raw_printf)(a0,a1,a2);}
void teleport_files_var49(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_files_var50(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_files_var51(char * a0,char * a1){(raw_printf)(a0,a1);}
void teleport_files_var52(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_files_var53(char * a0,char * a1,char * a2,int a3){(pline)(a0,a1,a2,a3);}
void teleport_files_var54(char * a0){(You_feel)(a0);}
void teleport_files_var55(char * a0,int a1){(pline)(a0,a1);}
int teleport_files_var56(char * a0,char * a1,char * a2){return (sprintf)(a0,a1,a2);}
int teleport_files_var57(char * a0,char * a1,int a2){return (sprintf)(a0,a1,a2);}
void teleport_files_var58(char * a0,char * a1,char * a2){(pline)(a0,a1,a2);}
void teleport_files_var59(char * a0){(pline)(a0);}
int teleport_files_var60(struct _IO_FILE * a0,char * a1,long a2,char * a3,char * a4,char * a5,char * a6,char * a7,long a8,long a9,long a10,char * a11){return (fprintf)(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);}
void teleport_files_cb0(void (*fn)(void)){fn();}
void teleport_files_cb1(void (*fn)(winid),winid a0){fn(a0);}
void teleport_files_cb2(void (*fn)(const char *),const char * a0){fn(a0);}
void teleport_files_cb3(void (*fn)(void)){fn();}
void teleport_files_cb4(void (*fn)(void)){fn();}
void teleport_files_cb5(void (*fn)(void)){fn();}
void teleport_files_cb6(void (*fn)(void)){fn();}
void teleport_files_cb7(void (*fn)(const char *),const char * a0){fn(a0);}
void teleport_files_cb8(void (*fn)(const char *),const char * a0){fn(a0);}
winid teleport_files_cb9(winid (*fn)(int),int a0){return fn(a0);}
void teleport_files_cb10(void (*fn)(winid, int, const char *),winid a0,int a1,const char * a2){fn(a0,a1,a2);}
void teleport_files_cb11(void (*fn)(winid, boolean),winid a0,boolean a1){fn(a0,a1);}
void teleport_files_cb12(void (*fn)(const char *, boolean),const char * a0,boolean a1){fn(a0,a1);}
void teleport_files_cb13(void (*fn)(winid),winid a0){fn(a0);}
#pragma clang diagnostic pop
static char files_literals[2145];
char*teleport_files_literal_storage(void){return files_literals;}
size_t teleport_files_literal_capacity(void){return sizeof files_literals;}
static char files_backing_0[80];
static char files_backing_1[17];
static char files_backing_2[17];
static int files_backing_3;
static struct sfstatus_to_msg files_backing_4[10];
static signed char files_backing_5;
static char * files_backing_6;
static char * files_backing_7;
static int files_backing_8;
static struct flock files_backing_9;
void*teleport_files_storage(int i){switch(i){
case 0:return &files_backing_0;
case 1:return &files_backing_1;
case 2:return &files_backing_2;
case 3:return &files_backing_3;
case 4:return &files_backing_4;
case 5:return &files_backing_5;
case 6:return &files_backing_6;
case 7:return &files_backing_7;
case 8:return &files_backing_8;
case 9:return &files_backing_9;
default:abort();}}
extern int teleport_files_strcmp_wrap(const void * a0,const void * a1);
extern boolean proc_wizkit_line(char*);
void*teleport_files_function(int i){switch(i){
case 0:return(void*)proc_symset_line;
case 1:return(void*)proc_wizkit_line;
case 2:return(void*)teleport_files_strcmp_wrap;
default:abort();}}
#ifdef TELEPORT_FILES_VALIDATE_ORIGINAL
_Static_assert(sizeof bei==sizeof files_backing_3,"FILES private backing size");
_Static_assert(sizeof sf2msg==sizeof files_backing_4,"FILES private backing size");
_Static_assert(sizeof cvtinit==sizeof files_backing_5,"FILES private backing size");
_Static_assert(sizeof unconverted_filename==sizeof files_backing_6,"FILES private backing size");
_Static_assert(sizeof converted_filename==sizeof files_backing_7,"FILES private backing size");
_Static_assert(sizeof lockfd==sizeof files_backing_8,"FILES private backing size");
_Static_assert(sizeof sflock==sizeof files_backing_9,"FILES private backing size");
_Static_assert(sizeof svc.context.novel.pasg==30&&sizeof svc.context.novel.pasg[0]==1&&(xint8)-1<0,"FILES original MAXPASSAGES/signed slots");
#endif
