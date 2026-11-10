/* BONES typed field/global/dependency ABI only; no bones decisions here. */
#include "hack.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bones-source-data.h"
void *teleport_bones_global(int index){switch(index){
case 0: return (void*)(&u);
case 1: return (void*)(&flags);
case 2: return (void*)(&iflags);
case 3: return (void*)(&program_state);
case 4: return (void*)(&gs);
case 5: return (void*)(&gf);
case 6: return (void*)(&gi);
case 7: return (void*)(&gu);
case 8: return (void*)(&svp);
case 9: return (void*)(&svn);
case 10: return (void*)(&gb);
case 11: return (void*)(&svl.level);
case 12: return (void*)(mons);
case 13: return (void*)(objects);
case 14: return (void*)(svr.rooms);
case 15: return (void*)(svd.dungeons);
case 16: return (void*)(roles);
case 17: return (void*)(races);
case 18: return (void*)(genders);
case 19: return (void*)(aligns);
case 20: return (void*)(levl);
case 21: return (void*)(svl.lastseentyp);
case 22: return (void*)(&oracle_level);
case 23: return (void*)(&uball);
case 24: return (void*)(&svc.context.achieveo.mines_prize_oid);
case 25: return (void*)(&svc.context.achieveo.soko_prize_oid);
case 26: return (void*)(&windowprocs.wp_id);
default: abort();}}
uint64_t teleport_bones_read(int kind,void *at,int field){switch(kind){
case 0: { struct obj *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->nobj);
case 1: return (uint64_t)(uintptr_t)(p->cobj);
case 2: return (uint64_t)(uintptr_t)(p->ocontainer);
case 3: return (uint64_t)(uintptr_t)(p->oextra);
case 4: return (uint64_t)(uintptr_t)(p->in_use);
case 5: return (uint64_t)(uintptr_t)(p->oartifact);
case 6: return (uint64_t)(uintptr_t)(p->otyp);
case 7: return (uint64_t)(uintptr_t)(p->oclass);
case 8: return (uint64_t)(uintptr_t)(p->oeaten);
case 9: return (uint64_t)(uintptr_t)(p->where);
case 10: return (uint64_t)(uintptr_t)(p->no_charge);
case 11: return (uint64_t)(uintptr_t)(p->known);
case 12: return (uint64_t)(uintptr_t)(p->dknown);
case 13: return (uint64_t)(uintptr_t)(p->bknown);
case 14: return (uint64_t)(uintptr_t)(p->rknown);
case 15: return (uint64_t)(uintptr_t)(p->lknown);
case 16: return (uint64_t)(uintptr_t)(p->cknown);
case 17: return (uint64_t)(uintptr_t)(p->tknown);
case 18: return (uint64_t)(uintptr_t)(p->invlet);
case 19: return (uint64_t)(uintptr_t)(p->how_lost);
case 20: return (uint64_t)(uintptr_t)(p->corpsenm);
case 21: return (uint64_t)(uintptr_t)(p->spe);
case 22: return (uint64_t)(uintptr_t)(p->nomerge);
case 23: return (uint64_t)(uintptr_t)(p->lamplit);
case 24: return (uint64_t)(uintptr_t)(p->age);
case 25: return (uint64_t)(uintptr_t)(p->quan);
case 26: return (uint64_t)(uintptr_t)(p->owt);
case 27: return (uint64_t)(uintptr_t)(p->owornmask);
case 28: return (uint64_t)(uintptr_t)(p->ghostly);
case 29: return (uint64_t)(uintptr_t)(p->o_id);
default:abort();}}
case 1: { struct monst *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->nmon);
case 1: return (uint64_t)(uintptr_t)(p->data);
case 2: return (uint64_t)(uintptr_t)(p->minvent);
case 3: return (uint64_t)(uintptr_t)(p->mextra);
case 4: return (uint64_t)(uintptr_t)(p->m_id);
case 5: return (uint64_t)(uintptr_t)(p->mx);
case 6: return (uint64_t)(uintptr_t)(p->my);
case 7: return (uint64_t)(uintptr_t)(p->iswiz);
case 8: return (uint64_t)(uintptr_t)(p->cham);
case 9: return (uint64_t)(uintptr_t)(p->mpeaceful);
case 10: return (uint64_t)(uintptr_t)(p->m_lev);
case 11: return (uint64_t)(uintptr_t)(p->mhp);
case 12: return (uint64_t)(uintptr_t)(p->mhpmax);
case 13: return (uint64_t)(uintptr_t)(p->female);
case 14: return (uint64_t)(uintptr_t)(p->msleeping);
case 15: return (uint64_t)(uintptr_t)(p->mlstmv);
case 16: return (uint64_t)(uintptr_t)(p->mtame);
case 17: return (uint64_t)(uintptr_t)(p->seen_resistance);
default:abort();}}
case 2: { struct permonst *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->mlet);
case 1: return (uint64_t)(uintptr_t)(p->msound);
case 2: return (uint64_t)(uintptr_t)(p->geno);
case 3: return (uint64_t)(uintptr_t)(p->mflags2);
case 4: return (uint64_t)(uintptr_t)(p->pmnames);
default:abort();}}
case 3: { struct oextra *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->oname);
case 1: return (uint64_t)(uintptr_t)(p->omonst);
default:abort();}}
case 4: { struct mextra *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->mgivenname);
case 1: return (uint64_t)(uintptr_t)(p->ebones);
default:abort();}}
case 5: { struct ebones *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->parentmid);
case 1: return (uint64_t)(uintptr_t)(p->role);
case 2: return (uint64_t)(uintptr_t)(p->race);
case 3: return (uint64_t)(uintptr_t)(&p->oldalign);
case 4: return (uint64_t)(uintptr_t)(p->deathlevel);
case 5: return (uint64_t)(uintptr_t)(p->luck);
case 6: return (uint64_t)(uintptr_t)(p->mnum);
case 7: return (uint64_t)(uintptr_t)(p->female);
case 8: return (uint64_t)(uintptr_t)(p->demigod);
case 9: return (uint64_t)(uintptr_t)(p->crowned);
default:abort();}}
case 6: { struct fruit *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->nextf);
case 1: return (uint64_t)(uintptr_t)(p->fid);
default:abort();}}
case 7: { struct trap *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->ntrap);
case 1: return (uint64_t)(uintptr_t)(p->ttyp);
case 2: return (uint64_t)(uintptr_t)(p->madeby_u);
case 3: return (uint64_t)(uintptr_t)(p->tseen);
default:abort();}}
case 8: { d_level *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->dnum);
case 1: return (uint64_t)(uintptr_t)(p->dlevel);
default:abort();}}
case 9: { dungeon *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->boneid);
default:abort();}}
case 10: { s_level *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->boneid);
default:abort();}}
case 11: { struct mkroom *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->rtype);
case 1: return (uint64_t)(uintptr_t)(p->orig_rtype);
case 2: return (uint64_t)(uintptr_t)(p->lx);
case 3: return (uint64_t)(uintptr_t)(p->hx);
case 4: return (uint64_t)(uintptr_t)(p->ly);
case 5: return (uint64_t)(uintptr_t)(p->hy);
default:abort();}}
case 12: { struct rm *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->roomno);
case 1: return (uint64_t)(uintptr_t)(p->seenv);
case 2: return (uint64_t)(uintptr_t)(p->waslit);
case 3: return (uint64_t)(uintptr_t)(p->glyph);
default:abort();}}
case 13: { struct cemetery *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->next);
case 1: return (uint64_t)(uintptr_t)(p->who);
case 2: return (uint64_t)(uintptr_t)(p->how);
case 3: return (uint64_t)(uintptr_t)(p->when);
case 4: return (uint64_t)(uintptr_t)(p->frpx);
case 5: return (uint64_t)(uintptr_t)(p->frpy);
case 6: return (uint64_t)(uintptr_t)(p->bonesknown);
default:abort();}}
case 14: { align *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->type);
case 1: return (uint64_t)(uintptr_t)(p->record);
case 2: return (uint64_t)(uintptr_t)(p->abuse);
default:abort();}}
case 15: { coord *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->x);
case 1: return (uint64_t)(uintptr_t)(p->y);
default:abort();}}
case 16: { struct you *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->twoweap);
case 1: return (uint64_t)(uintptr_t)(p->ux);
case 2: return (uint64_t)(uintptr_t)(p->uy);
case 3: return (uint64_t)(uintptr_t)(p->ux0);
case 4: return (uint64_t)(uintptr_t)(p->uy0);
case 5: return (uint64_t)(uintptr_t)(&p->uz);
case 6: return (uint64_t)(uintptr_t)(p->usteed);
case 7: return (uint64_t)(uintptr_t)(p->uswallow);
case 8: return (uint64_t)(uintptr_t)(p->ugrave_arise);
case 9: return (uint64_t)(uintptr_t)(p->umonnum);
case 10: return (uint64_t)(uintptr_t)(p->ulevel);
case 11: return (uint64_t)(uintptr_t)(p->uhpmax);
case 12: return (uint64_t)(uintptr_t)(&p->ualign);
case 13: return (uint64_t)(uintptr_t)(p->uluck);
case 14: return (uint64_t)(uintptr_t)(&p->uevent);
case 15: return (uint64_t)(uintptr_t)(&p->uroleplay);
case 16: return (uint64_t)(uintptr_t)(p->uhandedness);
default:abort();}}
case 17: { struct u_event *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->udemigod);
case 1: return (uint64_t)(uintptr_t)(p->uhand_of_elbereth);
default:abort();}}
case 18: { struct u_roleplay *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->numbones);
default:abort();}}
case 19: { struct Role *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(&p->name);
case 1: return (uint64_t)(uintptr_t)(p->filecode);
case 2: return (uint64_t)(uintptr_t)(p->mnum);
default:abort();}}
case 20: { struct RoleName *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->m);
default:abort();}}
case 21: { struct Race *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->noun);
case 1: return (uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 22: { struct Gender *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 23: { struct Align *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->filecode);
default:abort();}}
case 24: { NHFILE *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->mode);
case 1: return (uint64_t)(uintptr_t)(p->fd);
case 2: return (uint64_t)(uintptr_t)(p->structlevel);
case 3: return (uint64_t)(uintptr_t)(p->fieldlevel);
case 4: return (uint64_t)(uintptr_t)(p->fpdef);
case 5: return (uint64_t)(uintptr_t)(&p->style);
default:abort();}}
case 25: { struct fieldlevel_content *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->deflt);
default:abort();}}
case 26: { __typeof__(flags) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->bones);
case 1: return (uint64_t)(uintptr_t)(p->debug);
case 2: return (uint64_t)(uintptr_t)(p->explore);
case 3: return (uint64_t)(uintptr_t)(p->female);
default:abort();}}
case 27: { __typeof__(iflags) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->wc_eight_bit_input);
default:abort();}}
case 28: { __typeof__(program_state) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->reading_bonesfile);
default:abort();}}
case 29: { __typeof__(gs) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(&p->save_dlevel);
default:abort();}}
case 30: { __typeof__(gf) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->ftrap);
case 1: return (uint64_t)(uintptr_t)(p->ffruit);
default:abort();}}
case 31: { __typeof__(gi) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->invent);
case 1: return (uint64_t)(uintptr_t)(p->in_mklev);
default:abort();}}
case 32: { __typeof__(gu) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(&p->urole);
case 1: return (uint64_t)(uintptr_t)(&p->urace);
default:abort();}}
case 33: { __typeof__(svp) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->plname);
default:abort();}}
case 34: { __typeof__(svn) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->nhuuid);
default:abort();}}
case 35: { __typeof__(gb) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->bones);
default:abort();}}
case 36: { __typeof__(svl.level) *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->buriedobjlist);
case 1: return (uint64_t)(uintptr_t)(p->bonesinfo);
case 2: return (uint64_t)(uintptr_t)(&p->flags);
case 3: return (uint64_t)(uintptr_t)(p->monlist);
case 4: return (uint64_t)(uintptr_t)(p->objlist);
default:abort();}}
case 37: { struct levelflags *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->wizard_bones);
default:abort();}}
case 38: { struct objclass *p=at;switch(field){
case 0: return (uint64_t)(uintptr_t)(p->oc_uses_known);
default:abort();}}
default:abort();}}
void teleport_bones_write(int kind,void *at,int field,uint64_t value){switch(kind){
case 0: { struct obj *p=at;switch(field){
case 0: p->nobj=(void*)(uintptr_t)value;return;
case 1: p->cobj=(void*)(uintptr_t)value;return;
case 2: p->ocontainer=(void*)(uintptr_t)value;return;
case 3: p->oextra=(void*)(uintptr_t)value;return;
case 4: p->in_use=value;return;
case 5: p->oartifact=value;return;
case 6: p->otyp=value;return;
case 7: p->oclass=value;return;
case 8: p->oeaten=value;return;
case 9: p->where=value;return;
case 10: p->no_charge=value;return;
case 11: p->known=value;return;
case 12: p->dknown=value;return;
case 13: p->bknown=value;return;
case 14: p->rknown=value;return;
case 15: p->lknown=value;return;
case 16: p->cknown=value;return;
case 17: p->tknown=value;return;
case 18: p->invlet=value;return;
case 19: p->how_lost=value;return;
case 20: p->corpsenm=value;return;
case 21: p->spe=value;return;
case 22: p->nomerge=value;return;
case 23: p->lamplit=value;return;
case 24: p->age=value;return;
case 25: p->quan=value;return;
case 26: p->owt=value;return;
case 27: p->owornmask=value;return;
case 28: p->ghostly=value;return;
case 29: p->o_id=value;return;
default:abort();}}
case 1: { struct monst *p=at;switch(field){
case 0: p->nmon=(void*)(uintptr_t)value;return;
case 1: p->data=(void*)(uintptr_t)value;return;
case 2: p->minvent=(void*)(uintptr_t)value;return;
case 3: p->mextra=(void*)(uintptr_t)value;return;
case 4: p->m_id=value;return;
case 5: p->mx=value;return;
case 6: p->my=value;return;
case 7: p->iswiz=value;return;
case 8: p->cham=value;return;
case 9: p->mpeaceful=value;return;
case 10: p->m_lev=value;return;
case 11: p->mhp=value;return;
case 12: p->mhpmax=value;return;
case 13: p->female=value;return;
case 14: p->msleeping=value;return;
case 15: p->mlstmv=value;return;
case 16: p->mtame=value;return;
case 17: p->seen_resistance=value;return;
default:abort();}}
case 3: { struct oextra *p=at;switch(field){
case 0: p->oname=(void*)(uintptr_t)value;return;
case 1: p->omonst=(void*)(uintptr_t)value;return;
default:abort();}}
case 4: { struct mextra *p=at;switch(field){
case 0: p->mgivenname=(void*)(uintptr_t)value;return;
case 1: p->ebones=(void*)(uintptr_t)value;return;
default:abort();}}
case 5: { struct ebones *p=at;switch(field){
case 0: p->parentmid=value;return;
case 1: p->role=value;return;
case 2: p->race=value;return;
case 4: p->deathlevel=value;return;
case 5: p->luck=value;return;
case 6: p->mnum=value;return;
case 7: p->female=value;return;
case 8: p->demigod=value;return;
case 9: p->crowned=value;return;
default:abort();}}
case 6: { struct fruit *p=at;switch(field){
case 0: p->nextf=(void*)(uintptr_t)value;return;
case 1: p->fid=value;return;
default:abort();}}
case 7: { struct trap *p=at;switch(field){
case 0: p->ntrap=(void*)(uintptr_t)value;return;
case 1: p->ttyp=value;return;
case 2: p->madeby_u=value;return;
case 3: p->tseen=value;return;
default:abort();}}
case 8: { d_level *p=at;switch(field){
case 0: p->dnum=value;return;
case 1: p->dlevel=value;return;
default:abort();}}
case 11: { struct mkroom *p=at;switch(field){
case 0: p->rtype=value;return;
case 1: p->orig_rtype=value;return;
case 2: p->lx=value;return;
case 3: p->hx=value;return;
case 4: p->ly=value;return;
case 5: p->hy=value;return;
default:abort();}}
case 12: { struct rm *p=at;switch(field){
case 0: p->roomno=value;return;
case 1: p->seenv=value;return;
case 2: p->waslit=value;return;
case 3: p->glyph=value;return;
default:abort();}}
case 13: { struct cemetery *p=at;switch(field){
case 0: p->next=(void*)(uintptr_t)value;return;
case 4: p->frpx=value;return;
case 5: p->frpy=value;return;
case 6: p->bonesknown=value;return;
default:abort();}}
case 14: { align *p=at;switch(field){
case 0: p->type=value;return;
case 1: p->record=value;return;
case 2: p->abuse=value;return;
default:abort();}}
case 15: { coord *p=at;switch(field){
case 0: p->x=value;return;
case 1: p->y=value;return;
default:abort();}}
case 16: { struct you *p=at;switch(field){
case 0: p->twoweap=value;return;
case 1: p->ux=value;return;
case 2: p->uy=value;return;
case 3: p->ux0=value;return;
case 4: p->uy0=value;return;
case 6: p->usteed=(void*)(uintptr_t)value;return;
case 7: p->uswallow=value;return;
case 8: p->ugrave_arise=value;return;
case 9: p->umonnum=value;return;
case 10: p->ulevel=value;return;
case 11: p->uhpmax=value;return;
case 13: p->uluck=value;return;
case 16: p->uhandedness=value;return;
default:abort();}}
case 17: { struct u_event *p=at;switch(field){
case 0: p->udemigod=value;return;
case 1: p->uhand_of_elbereth=value;return;
default:abort();}}
case 18: { struct u_roleplay *p=at;switch(field){
case 0: p->numbones=value;return;
default:abort();}}
case 24: { NHFILE *p=at;switch(field){
case 0: p->mode=value;return;
case 1: p->fd=value;return;
case 2: p->structlevel=value;return;
case 3: p->fieldlevel=value;return;
case 4: p->fpdef=(void*)(uintptr_t)value;return;
default:abort();}}
case 25: { struct fieldlevel_content *p=at;switch(field){
case 0: p->deflt=value;return;
default:abort();}}
case 26: { __typeof__(flags) *p=at;switch(field){
case 0: p->bones=value;return;
case 1: p->debug=value;return;
case 2: p->explore=value;return;
case 3: p->female=value;return;
default:abort();}}
case 27: { __typeof__(iflags) *p=at;switch(field){
case 0: p->wc_eight_bit_input=value;return;
default:abort();}}
case 28: { __typeof__(program_state) *p=at;switch(field){
case 0: p->reading_bonesfile=value;return;
default:abort();}}
case 29: { __typeof__(gs) *p=at;switch(field){
default:abort();}}
case 30: { __typeof__(gf) *p=at;switch(field){
case 0: p->ftrap=(void*)(uintptr_t)value;return;
case 1: p->ffruit=(void*)(uintptr_t)value;return;
default:abort();}}
case 31: { __typeof__(gi) *p=at;switch(field){
case 0: p->invent=(void*)(uintptr_t)value;return;
case 1: p->in_mklev=value;return;
default:abort();}}
case 32: { __typeof__(gu) *p=at;switch(field){
default:abort();}}
case 33: { __typeof__(svp) *p=at;switch(field){
default:abort();}}
case 34: { __typeof__(svn) *p=at;switch(field){
default:abort();}}
case 35: { __typeof__(gb) *p=at;switch(field){
default:abort();}}
case 36: { __typeof__(svl.level) *p=at;switch(field){
case 0: p->buriedobjlist=(void*)(uintptr_t)value;return;
case 1: p->bonesinfo=(void*)(uintptr_t)value;return;
case 3: p->monlist=(void*)(uintptr_t)value;return;
case 4: p->objlist=(void*)(uintptr_t)value;return;
default:abort();}}
case 37: { struct levelflags *p=at;switch(field){
case 0: p->wizard_bones=value;return;
default:abort();}}
default:abort();}}
void teleport_bones_copy(void *to,const void *from,size_t n){memcpy(to,from,n);}
extern void teleport_bones_remove_mon_callback(struct monst*);
void (*teleport_bones_callback_pointer(void))(struct monst*) {return teleport_bones_remove_mon_callback;}
void teleport_bones_rng_caller(int site){
static const int lines[]={247,290,296,377,645};
static const char *const callers[]={"give_to_nearby_mon","drop_upon_death","drop_upon_death","can_make_bones","getbones"};
if(site<0||site>=5)abort();if(rng_log_enabled())rng_log_set_caller("bones.c",lines[site],callers[site]);}
int teleport_bones_rn2_value(int n){return (rn2)(n);}
char teleport_bones_y_n(const char *q){return y_n(q);}
void teleport_bones_format2(char*out,const char*fmt,const char*a,const char*b){Sprintf(out,fmt,a,b);}
void teleport_bones_format5(char*out,const char*fmt,const char*a,const char*b,const char*c,const char*d,const char*e){Sprintf(out,fmt,a,b,c,d,e);}
void teleport_bones_pline0(const char*fmt){pline("%s",fmt);}
void teleport_bones_pline1(const char*fmt,const char*a){pline(fmt,a);}
void teleport_bones_you(const char*fmt,const char*a,const char*b){You(fmt,a,b);}
void teleport_bones_debug1(const char*fmt,const char*a){debugpline1(fmt,a);}
void teleport_bones_debug2(const char*fmt,unsigned a,unsigned b){debugpline2(fmt,a,b);}
static char teleport_bones_literals[TELEPORT_BONES_LITERAL_CAPACITY];
char *teleport_bones_literal_storage(void){return teleport_bones_literals;}
size_t teleport_bones_literal_capacity(void){return sizeof teleport_bones_literals;}

struct monst *teleport_bones_monster_at(coordxy x,coordxy y){return m_at(x,y);}
