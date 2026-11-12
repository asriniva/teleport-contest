import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
// Actual configured C ZAP versus imported JavaScript; controlled foreign deps.
import assert from './native-test-assert.mjs';
import fs from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import * as core from '../js/ported/zap.js';
import {callZap,initializeZap,zapState,createZapEnvironment} from '../js/nethack/bindings/zap.js';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
// Original C reference is available through the isolated reference process.
const custom=process.env.TELEPORT_ZAP_PROBE_DIR,dir=resolve(custom??'.cache/tu-probes');
const file=k=>pathToFileURL(resolve(dir,(custom?'':'zap-')+k+'.mjs'));
const {default:referenceFactory}=await loadFixture("zap",file('reference'));
const {default:hybridFactory}=await loadFixture("zap",file('hybrid'));
const reference=await referenceFactory();
function text(m,p){p=Number(p);if(!p)return null;let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
const raw={};for(let i=0;i<reference._probe_layout_count();i++)raw[text(reference,reference._probe_layout_name(i))]=reference._probe_layout_value(i);
const L={};for(const[k,v]of Object.entries(raw))L[k]=raw['constwidth_'+k]===8n?(raw['constsigned_'+k]?BigInt.asIntN(64,v):BigInt.asUintN(64,v)):Number(BigInt.asIntN(64,v));
for(const [,name]of fs.readFileSync(new URL(import.meta.url),'utf8').matchAll(/\bL\.([A-Z][A-Z_0-9]*)/g))assert.notEqual(L[name],undefined,'Actual compiled fixture constant '+name);
const lastServices=new WeakMap(),contexts=new WeakMap();
const runtime={zap(s,n,...a){
 lastServices.set(s.moduleKey,s);const cfg=contexts.get(s.moduleKey);if(!cfg)return callZap(s,L,n,...a);
 const nested=(cfg.depth??0)>0,tag=nested?'nested':cfg.tag;cfg.depth=(cfg.depth??0)+1;
 const facade=new Proxy(s,{get(t,k,r){const v=Reflect.get(t,k,r);if(['rn2','getobj','update_inventory'].includes(k))return(...args)=>{cfg.events.push(tag+':'+k);return v(...args);};return v;}});
 try{return callZap(facade,L,n,...a);}finally{cfg.depth--;}
},zapState(s){return zapState(s);},initializeZap(s){lastServices.set(s.moduleKey,s);return initializeZap(s,L);}};
const hybrid=await hybridFactory({nethackPorted:runtime});
const modules=[reference,hybrid],stack=modules.map(m=>m._probe_stack());let comparisons=0;const seen=new Set();
const names=["zaptype", "learnwand", "bhitm", "release_hold", "probe_objchain", "probe_monster", "get_obj_location", "get_mon_location", "montraits", "get_container_location", "zombie_can_dig", "revive", "revive_egg", "unturn_dead", "unturn_you", "cancel_item", "blank_novel", "drain_item", "obj_resists", "obj_shudders", "polyuse", "create_polymon", "do_osshock", "obj_unpolyable", "poly_obj", "stone_to_flesh_obj", "bhito", "bhitpile", "zappable", "do_enlightenment_effect", "zapnodir", "backfire", "zap_ok", "dozap", "boxlock_invent", "zapyourself", "ubreatheu", "lightdamage", "flashburn", "zap_steed", "cancel_monst", "zap_updown", "zapsetup", "zapwrapup", "weffects", "spell_damage_bonus", "spell_hit_bonus", "exclam", "hit", "miss", "skiprange", "maybe_explode_trap", "zap_map", "bhit", "boomhit", "zhitm", "zhitu", "burn_floor_objects", "bounce_dir", "zap_hit", "disintegrate_mon", "ubuzz", "buzz", "dobuzz", "melt_ice", "start_melt_ice_timeout", "melt_ice_away", "zap_over_floor", "mon_spell_hits_spot", "fracture_rock", "break_statue", "destroyable", "adtyp_to_prop", "u_adtyp_resistance_obj", "inventory_resistance_check", "item_what", "maybe_destroy_item", "destroy_items", "resist", "wishcmdassist", "wish_history_add", "wish_history_flush", "wish_history_menu", "makewish", "flash_str"];
function write(m,i,s){const p=Number(m._probe_buffer(i));m.HEAPU8.fill(0,p,p+4096);m.HEAPU8.set(Buffer.from(s+'\0','latin1'),p);return BigInt(p);}
function both(fn){modules.forEach(fn);}function reset(){both(m=>m._probe_reset());}function run(name,args=()=>[],label=''){
 seen.add(name);const values=modules.map((m,i)=>{const a=args(m,i).map(x=>BigInt(x??0));while(a.length<9)a.push(0n);try{m._probe_invoke(names.indexOf(name),...a);}catch(e){console.error('ZAP entry',name,label,'module',i);throw e;}return [text(m,m._probe_result()),text(m,m._probe_trace()),text(m,m._probe_snapshot()),(()=>{const v=new FixtureDataView(m.HEAPU8.buffer),p=Number(m._probe_ints()),out=Array.from({length:8},(_,j)=>v.getInt32(p+j*4,true));if(name==='bhit'||name==='zhitm'){const token=v.getBigUint64(p,true);const logical=token===0n?-1:Array.from({length:8},(_,j)=>m._probe_obj(j)).indexOf(token);assert.ok(logical>=0||token===0n,'Native output is NULL or one actual fixture object');out.splice(0,2,'object:'+logical);}return out;})(),Array.from({length:3},(_,j)=>text(m,m._probe_buffer(j)))];});
 assert.deepEqual(values[1],values[0],name+' '+label);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stack[i],name+' stack'));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;return values[0][0];}
// Native C consumer sees the authoritative table during startup, before a source call.
for(let i=0;i<7;i++)for(let j=0;j<3;j++){assert.equal(text(hybrid,hybrid._probe_destroy(i,j)),text(reference,reference._probe_destroy(i,j)));assert.equal(text(hybrid,hybrid._probe_destroy(i,j)),core.destroy_strings[i][j]);}
for(let i=0;i<7;i++)for(const quantity of [1n,2n]){assert.equal(text(hybrid,hybrid._probe_consumer(i,quantity)),text(reference,reference._probe_consumer(i,quantity)));assert.equal(text(hybrid,hybrid._probe_consumer(i,quantity)),core.destroy_strings[i][quantity>1n?1:0]);}
for(const type of [-39,-35,-30,-29,-20,-10,-1,0,1,7,9,10,20,29]){reset();run('zaptype',()=>[type]);reset();run('flash_str',()=>[type,1]);}
for(let n=0;n<50;n++){reset();run('zap_hit',()=>[n-20,0]);}
for(const typ of [L.WAN_STRIKING,L.WAN_FIRE,L.WAN_COLD,L.LONG_SWORD]){reset();both(m=>m._probe_item(0,typ,1n,0));run('learnwand',m=>[m._probe_obj(0)]);reset();both(m=>m._probe_item(0,typ,1n,0));run('zap_ok',m=>[m._probe_obj(0)]);}
for(const damage of [0,1,2,3,4,5,6,7,8,9,10]){reset();run('adtyp_to_prop',()=>[damage]);}
for(const range of [0,1,4,5,10,30]){reset();run('skiprange',m=>[range,m._probe_ints(),m._probe_ints()+4n]);}
console.log('ZAP initial',comparisons,'exact comparisons; remaining',names.filter(n=>!seen.has(n)).join(','));
for(const where of [L.OBJ_FREE,L.OBJ_INVENT,L.OBJ_FLOOR,L.OBJ_BURIED,L.OBJ_MINVENT,L.OBJ_CONTAINED])for(const flags of [0,1,2,3]){
 reset();both(m=>m._probe_link(0,-1,where,12,13));run('get_obj_location',m=>[m._probe_obj(0),m._probe_ints(),m._probe_ints()+2n,flags],where+':'+flags);
 reset();both(m=>m._probe_link(0,-1,where,12,13));run('get_container_location',m=>[m._probe_obj(0),m._probe_ints(),m._probe_ints()+4n],where+'');
}
for(const flags of [0,1,2,3]){reset();run('get_mon_location',m=>[m._probe_mon(0),m._probe_ints(),m._probe_ints()+2n,flags]);}
for(const fn of ['release_hold','unturn_you','do_enlightenment_effect','zapsetup','zapwrapup','dozap']){reset();run(fn);}
for(const fn of ['probe_objchain','cancel_item','drain_item','obj_shudders','obj_unpolyable','stone_to_flesh_obj','zappable','backfire','boxlock_invent','zap_steed','zap_updown','fracture_rock','break_statue']){
 for(const typ of [L.LONG_SWORD,L.WAN_STRIKING,L.WAN_FIRE,L.ROCK,L.CORPSE,L.SPE_BLANK_PAPER].filter(x=>x!==undefined)){
  reset();both(m=>{m._probe_item(0,typ,1n,3);if(fn==='zap_steed')m._probe_scalar(21,1n);});run(fn,m=>[m._probe_obj(0),0],String(typ));
 }
}
reset();both(m=>m._probe_item(0,L.SPE_BLANK_PAPER,1n,0));run('blank_novel',m=>[m._probe_obj(0)]);
for(const fn of ['probe_monster','unturn_dead']){reset();run(fn,m=>[m._probe_mon(0)]);}
for(const ordinary of [0,1]){reset();run('montraits',m=>[m._probe_obj(0),m._probe_buffer(0),ordinary]);reset();run('revive',m=>[m._probe_obj(0),ordinary]);}
reset();run('revive_egg',m=>[m._probe_obj(0)]);
for(const typ of [L.LONG_SWORD,L.WAN_FIRE,L.WAN_COLD,L.CORPSE])for(const percent of [0,50,100]){reset();both(m=>m._probe_item(0,typ,1n,0));run('obj_resists',m=>[m._probe_obj(0),percent,percent]);}
for(const type of [0,1,2,3,4,5,6,7,8,9,10,20]){reset();run('exclam',()=>[type]);reset();run('spell_damage_bonus',()=>[type]);reset();run('spell_hit_bonus',()=>[type]);reset();run('item_what',()=>[type]);reset();run('u_adtyp_resistance_obj',()=>[type]);reset();run('inventory_resistance_check',()=>[type]);}
for(const reason of ['beam','blast','']){reset();run('hit',m=>[write(m,0,reason),m._probe_mon(0),write(m,1,'!')]);reset();run('miss',m=>[write(m,0,reason),m._probe_mon(0)]);}
for(const x of [0,1,10,78,79])for(const y of [0,10,20]){reset();run('zombie_can_dig',()=>[x,y]);}
for(const value of [0n,1n,50n,1000n,9007199254740993n])for(const hero of [0,1]){reset();run('flashburn',()=>[value,hero]);}
for(const dmg of [0,1,2,3,4,5,6,7,8]){reset();run('destroyable',m=>[m._probe_obj(0),dmg]);reset();run('destroy_items',m=>[m._probe_mon(0),dmg,0]);}
for(const material of [0,1,2,3]){reset();run('polyuse',m=>[m._probe_obj(0),material,0]);reset();run('create_polymon',m=>[m._probe_obj(0),material]);}
console.log('ZAP broad',comparisons,'exact; remaining',names.filter(n=>!seen.has(n)).join(','));
const wandTypes=[L.WAN_STRIKING,L.WAN_FIRE,L.WAN_COLD,L.WAN_LIGHTNING,L.WAN_LIGHT,L.WAN_SECRET_DOOR_DETECTION,L.WAN_ENLIGHTENMENT,L.WAN_CREATE_MONSTER,L.WAN_WISHING,L.WAN_NOTHING,L.WAN_CANCELLATION,L.WAN_POLYMORPH,L.WAN_OPENING,L.WAN_LOCKING,L.WAN_UNDEAD_TURNING,L.WAN_MAKE_INVISIBLE,L.WAN_SPEED_MONSTER,L.WAN_SLOW_MONSTER,L.WAN_SLEEP,L.WAN_MAGIC_MISSILE,L.WAN_DIGGING,L.SPE_STONE_TO_FLESH].filter(x=>x!==undefined);
for(const typ of wandTypes){
 for(const fn of ['bhitm','bhito','zapnodir','zapyourself','lightdamage','weffects']){
  reset();both(m=>{m._probe_option(0,1);m._probe_item(0,L.ROCK,1n,0);m._probe_link(0,-1,L.OBJ_FLOOR,10,10);m._probe_item(1,typ,1n,5);m._probe_scalar(1,1n);for(const prop of [L.ANTIMAGIC,L.FIRE_RES,L.COLD_RES,L.SHOCK_RES,L.SLEEP_RES,L.DISINT_RES,L.POISON_RES,L.ACID_RES,L.STONE_RES].filter(x=>x!==undefined))m._probe_property(prop,1n,0n,0n);});
  run(fn,m=>fn==='bhitm'?[m._probe_mon(0),m._probe_obj(1)]:fn==='bhito'?[m._probe_obj(0),m._probe_obj(1)]:[m._probe_obj(1),1,5],String(typ));
 }
}
for(const fn of ['do_osshock','poly_obj']){reset();run(fn,m=>[m._probe_obj(0),L.ROCK]);}
for(const self of [0,1])for(const cancelled of [0,1]){reset();run('cancel_monst',m=>[m._probe_mon(0),m._probe_obj(0),self,0,cancelled]);}
for(const fn of ['wishcmdassist','wish_history_add','wish_history_menu','wish_history_flush','makewish']){
 reset();both(m=>m._probe_scalar(0,1n));run(fn,m=>fn==='wishcmdassist'?[3]:fn==='wish_history_add'?[write(m,0,'long sword')]:fn==='wish_history_menu'?[write(m,0,'existing')]:fn==='makewish'?(write(m,6,'nothing'),[]):[]);
}
console.log('ZAP effects',comparisons,'exact; remaining',names.filter(n=>!seen.has(n)).join(','));
for(const type of [0,1,2,3,4,5,6,7,10,11,12,20,21,22,-30,-31,-32]){
 reset();both(m=>{m._probe_option(0,1);new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(m._probe_ints()),0n,true);});run('zhitm',m=>[m._probe_mon(0),type,1,m._probe_ints()],String(type));
 if(![4,14,-34].includes(type)){reset();both(m=>{m._probe_option(0,1);for(const prop of [L.ANTIMAGIC,L.FIRE_RES,L.COLD_RES,L.SHOCK_RES,L.SLEEP_RES,L.DISINT_RES,L.POISON_RES,L.ACID_RES].filter(x=>x!==undefined))m._probe_property(prop,1n,0n,0n);});run('zhitu',m=>[type,1,write(m,0,'beam'),10,10],String(type));}
 reset();both(m=>m._probe_option(0,1));run('dobuzz',()=>[type,1,10,10,1,0,1,1,0],String(type));
}
for(const type of [0,1,2,5,10,20]){reset();run('buzz',()=>[type,1,10,10,1,0]);reset();run('ubuzz',()=>[type,1]);}
for(const terrain of [L.ROOM,L.STONE,L.IRONBARS,L.DOOR,L.ICE,L.POOL,L.LAVAPOOL].filter(x=>x!==undefined))for(const type of [0,1,2,4,5,7,20,21,22,24]){
 reset();both(m=>m._probe_map(12,10,terrain,0));run('zap_over_floor',m=>[12,10,type,m._probe_ints(),1,0],terrain+':'+type);
}
for(const fn of ['zap_map','maybe_explode_trap'])for(const type of [L.WAN_FIRE,L.WAN_COLD,L.WAN_CANCELLATION,L.WAN_STRIKING]){reset();both(m=>m._probe_item(0,type,1n,0));run(fn,m=>fn==='zap_map'?[12,10,m._probe_obj(0)]:[0,m._probe_obj(0),m._probe_ints()]);}
for(const dir of [[1,0],[0,1],[-1,0],[1,1]])for(const range of [0,1,5,20]){
 reset();both(m=>{new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(m._probe_ints()),m._probe_obj(0),true);m._probe_item(0,L.WAN_STRIKING,1n,0);});run('bhit',m=>[...dir,range,L.ZAPPED_WAND,m._probe_callback(0),m._probe_callback(1),m._probe_ints()],dir+':'+range);
 reset();both(m=>m._probe_map(12,10,L.STONE,0));run('bounce_dir',m=>{const p=m._probe_ints();const v=new FixtureDataView(m.HEAPU8.buffer);v.setInt32(Number(p),dir[0],true);v.setInt32(Number(p)+4,dir[1],true);return[12,10,p,p+4n,range];});
}
for(const haveObject of [0,1]){reset();both(m=>{m._probe_grid(10,10,haveObject?0:-1,-1);m._probe_link(0,-1,L.OBJ_FLOOR,10,10);});run('bhitpile',m=>[m._probe_obj(1),m._probe_callback(1),10,10,0]);}
reset();run('boomhit',m=>[m._probe_obj(0),1,0]);
reset();run('ubreatheu',m=>{const p=write(m,0,'');m.HEAPU8[Number(p)+L.struct_attack_adtyp]=L.AD_FIRE;m.HEAPU8[Number(p)+L.struct_attack_damn]=6;m.HEAPU8[Number(p)+L.struct_attack_damd]=6;return[p];});
for(const typ of [L.POT_WATER,L.POT_HEALING,L.SCR_IDENTIFY,L.WAN_FIRE,L.LONG_SWORD].filter(x=>x!==undefined))for(const damage of [L.AD_FIRE,L.AD_COLD,L.AD_ELEC].filter(x=>x!==undefined)){
 reset();both(m=>m._probe_item(0,typ,3n,0));if(run('destroyable',m=>[m._probe_obj(0),damage])!=='1')continue;run('maybe_destroy_item',m=>[m._probe_mon(0),m._probe_obj(0),damage],typ+':'+damage);
}
reset();run('burn_floor_objects',()=>[10,10,1,1]);
reset();run('disintegrate_mon',m=>[m._probe_mon(0),0,write(m,0,'beam')]);
for(const type of [L.AD_FIRE,L.AD_COLD,L.AD_ELEC]){reset();run('mon_spell_hits_spot',m=>[m._probe_mon(0),type,12,10]);}
for(const n of [0,1,20,50]){reset();run('resist',m=>[m._probe_mon(0),L.WAND_CLASS,n,0]);}
for(const fn of ['melt_ice','melt_ice_away','start_melt_ice_timeout']){reset();both(m=>{m._probe_map(12,10,L.ICE,0);new FixtureDataView(m.HEAPU8.buffer).setBigInt64(Number(m._probe_any()),(12n<<16n)|10n,true);});run(fn,m=>fn==='melt_ice'?[12,10,write(m,0,'ice melts')]:fn==='start_melt_ice_timeout'?[12,10,50]:[m._probe_any(),0]);}
console.log('ZAP entries',comparisons,'exact; remaining',names.filter(n=>!seen.has(n)).join(','));
// All configured native wand rows, varied charge state, real wide quantities,
// protected self effects and live target/world pointers.
for(let typ=0;typ<L.NUM_OBJECTS;typ++)if(reference._probe_type_class(typ)===L.WAND_CLASS){
 for(const spe of [-1,0,1,5])for(const fn of ['bhitm','bhito','zapyourself','cancel_item','zappable']){
  reset();both(m=>{m._probe_option(0,1);m._probe_item(0,L.ROCK,1n,0);m._probe_link(0,-1,L.OBJ_FLOOR,10,10);m._probe_grid(10,10,0,-1);m._probe_grid(11,10,-1,0);m._probe_item(1,typ,9007199254740993n,spe);for(const prop of [L.ANTIMAGIC,L.FIRE_RES,L.COLD_RES,L.SHOCK_RES,L.SLEEP_RES,L.DISINT_RES,L.POISON_RES,L.ACID_RES,L.STONE_RES])m._probe_property(prop,1n,0n,0n);});
  run(fn,m=>fn==='bhitm'?[m._probe_mon(0),m._probe_obj(1)]:fn==='bhito'?[m._probe_obj(0),m._probe_obj(1)]:[m._probe_obj(1),1],'native wand '+typ+' charge '+spe);
 }
}
// Output cells can alias one another; preserve original sequential native writes.
for(const flags of [0,1,2,3]){
 reset();both(m=>m._probe_link(0,-1,L.OBJ_FLOOR,12,13));run('get_obj_location',m=>[m._probe_obj(0),m._probe_ints(),m._probe_ints(),flags],'aliased coordinate outputs');
 reset();run('get_mon_location',m=>[m._probe_mon(0),m._probe_ints(),m._probe_ints(),flags],'aliased coordinate outputs');
 reset();run('get_container_location',m=>[m._probe_obj(0),m._probe_ints(),m._probe_ints()],'aliased int outputs');
}
// Real CMD bounds, corners, solid obstacles and mounted-target redirection.
for(const [x,y,dx,dy] of [[1,1,-1,0],[78,10,1,0],[12,1,0,-1],[12,19,0,1],[10,10,1,1]])for(const terrain of [L.STONE,L.DOOR,L.IRONBARS,L.ROOM]){
 reset();both(m=>{m._probe_map(x+dx,y+dy,terrain,L.D_CLOSED??0);m._probe_option(0,1);});run('dobuzz',()=>[1,2,x,y,dx,dy,1,1,0],'bounded bounce '+terrain);
}
for(const mounted of [0,1])for(const seed of [1,2,3,4,5,8,12]){
 reset();both(m=>{m._probe_seed(seed);m._probe_option(0,1);m._probe_scalar(21,BigInt(mounted));m._probe_scalar(32,BigInt.asIntN(64,0xfedcba9876543210n));m._probe_scalar(33,BigInt.asIntN(64,0x923456789abcdef0n));});run('dobuzz',()=>[0,1,9,10,1,0,1,1,0],'hero/mounted target '+mounted+':'+seed);
}
// Real original WORN traversal exercises the local descriptor array and both
// destruction passes. The external item removal dependencies stay controlled.
for(const hero of [0,1])for(const damage of [1,4,5,9,10,25,100,1000]){
 reset();both(m=>{for(let i=0;i<8;i++){m._probe_item(i,i%2?L.POT_WATER:L.SCR_IDENTIFY,3n,0);m._probe_link(i,i===7?-1:i+1,hero?L.OBJ_INVENT:L.OBJ_MINVENT,10,10);}m._probe_scalar(hero?28:27,0n);m._probe_option(0,1);});
 run('destroy_items',m=>[m._probe_mon(hero?-1:0),L.AD_FIRE,damage],'linked inventory '+hero+':'+damage);
}
// Debug history owns real native-allocated strings, keeps the original prefix
// duplicate behavior and wrap index, and frees them through actual libc.
reset();both(m=>m._probe_scalar(0,1n));run('wish_history_flush');
for(let i=0;i<27;i++){
 run('wish_history_add',m=>[write(m,0,'wish '+String(i).padStart(3,'0'))]);
 assert.equal(hybrid._probe_history(-1),reference._probe_history(-1));
 for(let j=0;j<20;j++)assert.equal(text(hybrid,hybrid._probe_history(j)),text(reference,reference._probe_history(j)));
}
run('wish_history_add',m=>[write(m,0,'wish 026')],'duplicate');
run('wish_history_flush');for(let j=0;j<20;j++){assert.equal(hybrid._probe_history(j),0n);assert.equal(reference._probe_history(j),0n);}
assert.equal(hybrid._probe_history(-1),0n);
console.log('ZAP aliases/history',comparisons,'exact comparisons');
function option(m,name,value){const id=m._probe_option_id(write(m,7,name));assert.ok(id>=0,'Known controlled dependency '+name);m._probe_option(id,value);}
for(const assigned of [0,1])for(const match of [0,1]){reset();both(m=>{m._probe_level(0,assigned,match);m._probe_map(11,10,L.STONE,0);});run('dobuzz',()=>[0,2,10,10,1,0,1,1,0],'assigned Air level '+assigned+':'+match);if(assigned&&match)assert.ok(text(reference,reference._probe_trace()).includes('vanishes into the aether'),'Actual native assigned-level bounce branch');}
// Each of the six original bhit_done transfers gets a positive native witness.
for(const kind of ['shop','flash','invisible','thrown','monster_callback','ship']){
 reset();both(m=>{m._probe_item(0,kind==='shop'?L.PICK_AXE:L.WAN_STRIKING,1n,0);m._probe_link(0,-1,L.OBJ_FREE,10,10);m._probe_grid(11,10,-1,kind==='ship'?-1:0);m._probe_option(11,1);new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(m._probe_ints()),m._probe_obj(0),true);if(kind==='shop'){option(m,'inside_shop',1);m._probe_option(14,1);}if(kind==='ship')option(m,'ship_object',1);});
 const weapon=kind==='flash'?L.FLASHED_LIGHT:kind==='invisible'?L.INVIS_BEAM:kind==='ship'?L.KICKED_WEAPON:kind==='thrown'||kind==='shop'?L.THROWN_WEAPON:L.ZAPPED_WAND;
 run('bhit',m=>[1,0,4,weapon,m._probe_callback(0),kind==='ship'?0:m._probe_callback(1),m._probe_ints()],kind+' forward exit');
 const trace=text(reference,reference._probe_trace());if(kind==='shop')assert.ok(trace.includes('shkcatch;'));if(kind==='monster_callback')assert.ok(trace.includes('cbmon:0:0;'));if(kind==='ship')assert.ok(trace.includes('ship_object;'));
}
// Both original wish retry labels, terminal interruption, positive menu output
// and hallucinated static output are exercised on valid source call edges.
for(const input of ['help','invalid description','nothing','terrain']){
 reset();both(m=>{m._probe_scalar(0,1n);m._probe_scalar(23,1n);m._probe_option(0,1);if(input==='invalid description')m._probe_option(10,1);write(m,6,input);});
 run('makewish',()=>[],input);const tr=text(reference,reference._probe_trace());
 if(input==='help')assert.equal((tr.match(/getlin:/g)??[]).length,2,'Help actually re-enters original retry label');
 if(input==='invalid description')assert.equal((tr.match(/getlin:/g)??[]).length,5,'Invalid text retries exactly the original five times');
}
reset();both(m=>{m._probe_scalar(0,1n);m._probe_scalar(24,1n);write(m,6,'nothing');});run('makewish',()=>[],'terminal interruption');
reset();both(m=>m._probe_scalar(0,1n));run('wish_history_flush');for(let i=0;i<20;i++)run('wish_history_add',m=>[write(m,0,'choice '+String(i).padStart(3,'0'))]);
for(const choice of [1,5,20]){both(m=>m._probe_option(13,choice));run('wish_history_menu',m=>[write(m,0,'old value')],'selected '+choice);assert.notEqual(text(reference,reference._probe_buffer(0)),'old value','Actual native positive pick writes the output buffer');}
run('wish_history_flush');
for(const nohallu of [0,1]){reset();both(m=>m._probe_property(L.HALLUC,1n,0n,0n));run('flash_str',()=>[21,nohallu],'hallucination '+nohallu);}
for(const value of [49n,50n,1999n,2000n,9007199254740993n]){reset();run('start_melt_ice_timeout',()=>[12,10,value],'native long narrowing '+value);}
// Returned static buffers retain their native identity and overwrite on reuse.
reset();run('flash_str',()=>[0,1]);const flashPointers=modules.map(m=>m._probe_return());run('flash_str',()=>[1,1]);modules.forEach((m,i)=>assert.equal(m._probe_return(),flashPointers[i]));
// Mutable cached service facades are fresh; overriding one does not poison its
// canonical Module packet or any later factory call.
reset();run('zaptype',()=>[-35]);const first=lastServices.get(hybrid),canonicalRn2=first.rn2;
first.rn2=()=>15;run('zaptype',()=>[-35]);const next=lastServices.get(hybrid);
assert.notEqual(first,next);assert.equal(Object.getPrototypeOf(first),Object.getPrototypeOf(next));assert.equal(next.rn2,canonicalRn2);assert.ok(Object.hasOwn(first,'rn2'));assert.ok(!Object.hasOwn(next,'rn2'));
let firstCalls=0,nextCalls=0;first.rn2=(...a)=>{firstCalls++;return canonicalRn2(...a);};next.rn2=(...a)=>{nextCalls++;return canonicalRn2(...a);};
callZap(first,L,'zap_hit',0,0);callZap(next,L,'zap_hit',0,0);assert.equal(firstCalls,1);assert.equal(nextCalls,1);
// Native getobj calls the actual private selector and then a second source
// function while the original import remains suspended; heap really grows.
const cfg={tag:'first',events:[],depth:0};contexts.set(hybrid,cfg);
for(const tag of ['first','second']){cfg.tag=tag;reset();run('zap_hit',()=>[0,0],tag+' service context');}
assert.ok(cfg.events.includes('first:rn2'));assert.ok(cfg.events.includes('second:rn2'));
reset();both(m=>{m._probe_item(0,L.WAN_STRIKING,1n,4);m._probe_option(1,1);m._probe_option(1000,2);m._probe_option(1001,2);});
const heapBefore=modules.map(m=>m.HEAPU8.buffer.byteLength);cfg.events=[];run('dozap',()=>[],'native selector, nested source, growth');
assert.ok(cfg.events.includes('nested:rn2'));assert.ok(cfg.events.slice(cfg.events.lastIndexOf('nested:rn2')+1).includes('second:update_inventory'),'Outer service facade restored after nested native callback');
modules.forEach((m,i)=>assert.ok(m.HEAPU8.buffer.byteLength>heapBefore[i],'Actual memory growth '+i));contexts.delete(hybrid);
const services=lastServices.get(hybrid),savedStack=hybrid._probe_stack(),sentinel={rectState:{marker:'R'},trackState:{marker:'T'}};
const throwing=new Proxy(services,{get(t,k,r){if(k==='rn2')return()=>{throw Error('ZAP dependency exception witness');};return Reflect.get(t,k,r);}});
withCEnvironment(sentinel,()=>{assert.throws(()=>callZap(throwing,L,'zap_hit',0,0),/ZAP dependency exception witness/);assert.equal(C,sentinel);assert.equal(R,sentinel.rectState);assert.equal(T,sentinel.trackState);});
assert.equal(hybrid._probe_stack(),savedStack);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
let fail=true;const retryLayout=new Proxy(L,{get(t,k,r){if(k==='struct_obj_size'&&fail){fail=false;throw Error('ZAP constructor failure witness');}return Reflect.get(t,k,r);}});
assert.throws(()=>callZap(services,retryLayout,'zaptype',-35),/ZAP constructor failure witness/);assert.equal(callZap(services,retryLayout,'zaptype',-35),5);assert.equal(hybrid._probe_stack(),savedStack);
assert.notEqual(createZapEnvironment(services,L,zapState(services)),createZapEnvironment(services,L,zapState(services)),'Direct constructors remain fresh');
let reads=0;const otherLayout={...L};Object.defineProperty(otherLayout,'BUFSZ',{enumerable:true,get(){reads++;return L.BUFSZ;}});callZap(services,otherLayout,'zaptype',-35);const after=reads;callZap(services,otherLayout,'zaptype',-35);assert.equal(reads,after,'Same immutable layout identity reuses environment');assert.ok(after>0);
const second=await hybridFactory({nethackPorted:runtime});second._probe_reset();const secondServices=lastServices.get(second);assert.notEqual(secondServices.moduleKey,services.moduleKey);assert.notEqual(Object.getPrototypeOf(secondServices),Object.getPrototypeOf(services));
const originalIndex=zapState(services).wish_history_idx;callZap(secondServices,L,'wish_history_add',write(second,0,'independent history'));assert.equal(zapState(services).wish_history_idx,originalIndex);
modules[1]=second;stack[1]=second._probe_stack();reset();both(m=>{m._probe_item(0,L.WAN_STRIKING,1n,4);m._probe_option(1,1);m._probe_option(1000,2);m._probe_option(1001,2);});const secondBefore=second.HEAPU8.buffer.byteLength;run('dozap',()=>[],'second actual Module growth/reentry');assert.ok(second.HEAPU8.buffer.byteLength>secondBefore);modules[1]=hybrid;stack[1]=hybrid._probe_stack();
assert.deepEqual(names.filter(n=>!seen.has(n)),[],'All85 original source functions exercised');
console.log(`ZAP: ${comparisons} exact EmC comparisons, all85functions; startup21cells/optimizedexternconsumer, original WORN traversal, aliases/history, six beam exits, actual native callback/growth, fresh service facades/current-context restoration, constructor retry and two Modules pass.`);
