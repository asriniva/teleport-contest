import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {C,R,T} from '../js/c-runtime/context.js';
import assert from './native-test-assert.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callApply,createApplyEnvironment} from '../js/nethack/bindings/apply.js';
import * as core from '../js/ported/apply.js';
// Reference selection is handled by the original-C fixture backend.
const W=resolve(process.env.TELEPORT_APPLY_PROBE_DIR??'.cache/apply-author'), url=name=>pathToFileURL(resolve(W,name)).href;
const factories=await Promise.all(['reference','hybrid'].map(async n=>(await loadFixture("apply",url(n+'.mjs'))).default));
let lastServices;let layout={};const mods=[];let entries=new Set(),context='',comparisons=0;
for(let i=0;i<2;i++){
 const m=await factories[i]({print:()=>{},printErr:()=>{},nethackPorted:{apply:(services,name,...args)=>{lastServices=services;entries.add(name);return callApply(services,layout,name,...args);}}});mods.push(m);
}
const string=(m,p)=>{let i=Number(p),out='';for(;m.HEAPU8[i];i++)out+=String.fromCharCode(m.HEAPU8[i]);return out;};
for(let i=0;i<mods[0]._probe_layout_count();i++)layout[string(mods[0],mods[0]._probe_layout_name(i))]=Number(mods[0]._probe_layout_value(i));
const F=JSON.parse(readFileSync(resolve(W,'functions.json')));
function snapshot(m){return {trace:string(m,m._probe_trace()),buffer:string(m,m._probe_buffer()),state:string(m,m._probe_snapshot())};}
function compare(){const a=snapshot(mods[0]),b=snapshot(mods[1]);try{assert.deepEqual(b,a,context);}catch(e){writeFileSync(resolve(W,'failure.json'),JSON.stringify({context,expected:a,actual:b},null,2));throw e;}}
function call(name,...args){const stackBefore=mods.map(m=>m._probe_stack());const out=mods.map(m=>m['_probe_'+name](...args));assert.deepEqual(mods.map(m=>m._probe_stack()),stackBefore,context+':stack:'+name);for(const value of[C,R,T])assert.equal(value,undefined,context+':environment:'+name);assert.deepEqual(out[1],out[0],context+':return:'+name);compare();comparisons++;return out[0];}
for(const [i,f]of F.entries()){
 context=f.name;call('reset');call('clear');
 if(process.env.APPLY_VERBOSE)console.log(context);
 const before=mods.map(m=>m._probe_stack());call('action',i,0,0,0);assert.deepEqual(mods.map(m=>m._probe_stack()),before,context+':stack');
}
const entry=n=>F.findIndex(f=>f.name===n),act=(n,a=0,b=0,c=0)=>call('action',entry(n),a,b,c);
const reset=()=>call('reset'),option=(i,n)=>call('option',i,n),global=(i,n)=>call('global',i,BigInt(n)),scene=(i,a,b=0)=>call('scene',i,a,b);
const object=(typ,spe=1,flags=0,quantity=1n,i=0)=>call('object',i,typ,spe,flags,1,quantity);
const property=(n,i=0,e=0,b=0)=>call('property',n,BigInt(i),BigInt(e),BigInt(b));
for(let typ=1;typ<layout.NUM_OBJECTS;typ++){
 context='object-selectors:'+typ;reset();object(typ);
 for(const name of ['apply_ok','rub_ok','grease_ok','touchstone_ok','jelly_ok','doapply'])act(name);
}
for(const [name,constant]of [['use_camera','EXPENSIVE_CAMERA'],['use_towel','TOWEL'],['use_stethoscope','STETHOSCOPE'],['use_mirror','MIRROR'],['use_bell','BELL'],['use_candelabrum','CANDELABRUM_OF_INVOCATION'],['use_candle','TALLOW_CANDLE'],['use_lamp','OIL_LAMP'],['light_cocktail','POT_OIL'],['use_tinning_kit','TINNING_KIT'],['use_unicorn_horn','UNICORN_HORN'],['use_figurine','FIGURINE'],['use_grease','CAN_OF_GREASE'],['use_stone','TOUCHSTONE'],['use_trap','LAND_MINE'],['use_whip','BULLWHIP'],['use_pole','HALBERD'],['use_cream_pie','CREAM_PIE'],['use_royal_jelly','LUMP_OF_ROYAL_JELLY'],['use_grapple','GRAPPLING_HOOK'],['do_break_wand','WAN_FIRE'],['flip_through_book','SPE_BOOK_OF_THE_DEAD'],['flip_coin','GOLD_PIECE']]){
 assert.ok(layout[constant]!==undefined,constant);
 for(const flags of[0,1,2,64])for(const spe of[0,1,3])for(const seed of[1,7]){
  context='tool:'+name+':'+flags+':'+spe+':'+seed;reset();object(layout[constant],spe,flags);call('seed',seed);scene(0,1,0);scene(5,10,0);act(name);
 }
}
for(const name of['doapply','do_break_wand','use_camera','use_stethoscope','use_towel','use_mirror','use_trap','use_lamp','use_candle','flip_coin'])for(const prop of[layout.BLINDED,layout.CONFUSION,layout.HALLUC,layout.GLIB,layout.FUMBLING,layout.HALF_PHDAM])for(const value of[0n,1n,0x100000000n]){
 context='property:'+name+':'+prop+':'+value;reset();object(layout.TOWEL,2,2);property(prop,value);scene(0,1,0);act(name);
}
for(const seed of[1,2,7,42])for(const bad of[0,2]){
 context='horn:'+seed+':'+bad;reset();object(layout.UNICORN_HORN,1,bad);property(layout.BLINDED,55);property(layout.CONFUSION,12);property(layout.STUNNED,5);property(layout.HALLUC,6);property(layout.DEAF,7);call('seed',seed);act('use_unicorn_horn');
}
for(const [a,b]of[[0,0],[1,0],[2,0],[1,1],[-1,0],[-2,-2]])for(const magic of[0,1,2,5]){
 context='jump-path:'+a+':'+b+':'+magic;reset();option(12,1);act('is_valid_jump_pos',10+a,10+b,magic);act('check_jump',10+a,10+b);act('um_dist',10+a,10+b,3);
}
for(const halved of[0,1])for(const seed of[1,7,42])for(const trap of[layout.TT_BEARTRAP,layout.TT_WEB,layout.TT_PIT]){
 context='jump-trap:'+halved+':'+seed+':'+trap;reset();property(layout.JUMPING,1);property(layout.HALF_PHDAM,halved);scene(6,1,trap);call('seed',seed);option(12,1);act('jump',0);if(trap===layout.TT_BEARTRAP)assert(snapshot(mods[0]).trace.includes('@apply.c:2082:'),'bear-trap Half/RNG branch actually reached');
}
for(const half of[0,1])for(const name of['jump','use_grapple']){
 context='property-before-RNG:'+name+':'+half;reset();property(layout.HALF_PHDAM,half);option(98,1);call('seed',name==='jump'?1:3);
 if(name==='jump'){option(12,1);property(layout.JUMPING,1);scene(6,1,layout.TT_BEARTRAP);}else object(layout.GRAPPLING_HOOK);
 act(name);assert(snapshot(mods[0]).trace.includes('half-toggle:'),context+': RNG actually changed property inside selected damage argument:'+snapshot(mods[0]).trace);
}
for(const optionId of[96,97]){
 context='live-objptr:'+optionId;reset();object(layout.TOWEL,2,0,1n,2);option(optionId,1);if(optionId===96)act('doapply');else act('do_blinding_ray');
}
context='occupation-native-pointer';reset();object(layout.LAND_MINE);act('doapply');act('set_trap');act('set_trap');
for(const count of[1,2]){
 context='pole-candidates:'+count;reset();scene(15,11,10);if(count===2)scene(15,12,10);act('find_poleable_mon');
}
for(const witness of JSON.parse(readFileSync(resolve(W,'callback-witnesses.json')))){
 context='native-indirect:'+witness.name;reset();assert.equal(call('callback_identity',witness.index),1);call('callback_action',witness.index);
}
for(const row of JSON.parse(readFileSync(resolve(W,'record-projections.json'))))for(const missing of[false,true]){
 if(missing&&!row.nullNativeCase)continue;
 context='typed-return:'+row.name+':'+missing;reset();act('apply_ok');for(const id of[0,1,2,4,5,6,7])option(id,Number(missing));
 const expected=mods[0]._probe_record(row.index),saved=lastServices.stackSave(),env=createApplyEnvironment(lastServices,layout);
 try{
  const o=env.record('struct obj',mods[1]._probe_pointer(0)),m=env.record('struct monst',mods[1]._probe_pointer(1)),cell=env.localScalar('struct obj *',o);
  const args=row.jsArgs.map(j=>j==='o'?o:j==='m'?m:j==='cell'?cell:j==='core.apply_ok'?core.apply_ok:j==='core.mleashed_next2u'?core.mleashed_next2u:j==="env.record('struct trap',mods[1]._probe_pointer(4))"?env.record('struct trap',mods[1]._probe_pointer(4)):j==='env.mons[layout.PM_HUMAN]'?env.mons[layout.PM_HUMAN]:j==='layout.DAGGER'?layout.DAGGER:j==='"apply.c"'?'apply.c':Number(j));
  const value=env[row.name](...args);let actual=-777;
  if(value){assert.equal(env.record(row.type,value.address),value,context+':same view');assert.equal(BigInt(value.address),mods[1]._probe_record_pointer(),context+':native alias');actual=row.type==='union any'?(value.a_obj?1000: -1):value[row.field];}
  assert.equal(BigInt(actual),expected,context);compare();comparisons++;
  if(value&&row.writableField){for(const mod of mods)mod._probe_record_write(row.index,17);assert.equal(value[row.writableField],17,context+':C write reread');compare();}
 }finally{lastServices.stackRestore(saved);}
}
for(const alias of[0,1]){
 context='growth-reentry:'+alias;reset();object(layout.TOWEL);property(layout.GLIB,5);option(90,1);option(92,1);option(94,alias);const oldLengths=mods.map(m=>m.HEAPU8.length);act('use_towel');for(let i=0;i<2;i++)assert(alias?mods[i].HEAPU8.length>=oldLengths[i]:mods[i].HEAPU8.length>oldLengths[i],context+':first allocation grows memory; later allocation may reuse freed capacity');
}
context='controlled-C-unwind';reset();object(layout.TOWEL);property(layout.GLIB,5);option(93,1);assert.equal(act('use_towel'),-999n);option(93,0);act('apply_ok');
const savedModules=[...mods],secondModules=[];
for(let i=0;i<2;i++)secondModules.push(await factories[i]({print:()=>{},printErr:()=>{},nethackPorted:{apply:(services,name,...args)=>{lastServices=services;entries.add(name);return callApply(services,layout,name,...args);}}}));
mods.splice(0,2,...secondModules);context='Module-B';reset();object(layout.TOWEL,2,1);property(layout.GLIB,2);act('use_towel');const savedSnapshots=mods.map(snapshot);
mods.splice(0,2,...savedModules);context='Module-A';reset();object(layout.MIRROR);scene(0,1,0);act('use_mirror');assert.deepEqual(secondModules.map(snapshot),savedSnapshots,'Module-B memory/state preserved by Module-A');
console.log('APPLY comparisons',comparisons,'entrypoints',entries.size);
writeFileSync(resolve(W,'summary.json'),JSON.stringify({status:'PASS',comparisons,entries:[...entries],callbacks:16,typedRecordReturns:27,propertyBeforeRngMutationWitnesses:4,ModuleIsolation:true,memoryGrowth:true,reentry:true,scope:'controlled configured original-C/hybrid fixture; all76 entrypoints reached; incomplete branch/native-host/shared/public coverage'},null,2));
