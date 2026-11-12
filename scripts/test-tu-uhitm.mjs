import {C,R,T} from '../js/c-runtime/context.js';
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callUhitm,createUhitmEnvironment} from '../js/nethack/bindings/uhitm.js';
import * as core from '../js/ported/uhitm.js';
if(process.env.TELEPORT_NATIVE_TESTS!=='0')throw Error('UHITM has no native reference fixture; set TELEPORT_NATIVE_TESTS=0 only for the explicit Emscripten diagnostic.');
const W=resolve(process.env.TELEPORT_UHITM_PROBE_DIR??'.cache/uhitm-author'), url=name=>pathToFileURL(resolve(W,name)).href;
const factories=await Promise.all(['reference','hybrid'].map(async n=>(await import(url(n+'.mjs'))).default));
let lastServices;let layout={};const mods=[];let entries=new Set(),context='',comparisons=0;
for(let i=0;i<2;i++){
 const m=await factories[i]({print:()=>{},printErr:()=>{},nethackPorted:{uhitm:(services,name,...args)=>{lastServices=services;entries.add(name);return callUhitm(services,layout,name,...args);}}});mods.push(m);
}
const string=(m,p)=>{let i=Number(p),out='';for(;m.HEAPU8[i];i++)out+=String.fromCharCode(m.HEAPU8[i]);return out;};
for(let i=0;i<mods[0]._probe_layout_count();i++)layout[string(mods[0],mods[0]._probe_layout_name(i))]=Number(mods[0]._probe_layout_value(i));
const F=JSON.parse(readFileSync(resolve(W,'functions.json')));
function snapshot(m){return {trace:string(m,m._probe_trace()),buffer:string(m,m._probe_buffer()),state:string(m,m._probe_snapshot())};}
function compare(){const a=snapshot(mods[0]),b=snapshot(mods[1]);try{assert.deepEqual(b,a,context);}catch(e){writeFileSync(resolve(W,'failure.json'),JSON.stringify({context,expected:a,actual:b},null,2));throw e;}}
function call(name,...args){const stackBefore=mods.map(m=>m._probe_stack());const out=mods.map(m=>m['_probe_'+name](...args));assert.deepEqual(mods.map(m=>m._probe_stack()),stackBefore,context+':stack:'+name);for(const value of[C,R,T])assert.equal(value,undefined,context+':environment:'+name);assert.deepEqual(out[1],out[0],context+':return:'+name);compare();comparisons++;return out[0];}
for(const [i,f]of F.entries()){
 context=f.name;call('reset');call('clear');
 if(process.env.UHITM_VERBOSE)console.log(context);
 const before=mods.map(m=>m._probe_stack());call('action',i,0,0,0);assert.deepEqual(mods.map(m=>m._probe_stack()),before,context+':stack');
}
const entry=n=>F.findIndex(f=>f.name===n),act=(n,a=0,b=0,c=0)=>call('action',entry(n),a,b,c);
const reset=()=>call('reset'),option=(i,n)=>call('option',i,n),global=(i,n)=>call('global',i,BigInt(n)),scene=(i,a,b=0)=>call('scene',i,a,b);
const object=(typ,spe=1,flags=0,quantity=1n,i=0)=>call('object',i,typ,spe,flags,1,quantity);
const property=(n,i=0,e=0,b=0)=>call('property',n,BigInt(i),BigInt(e),BigInt(b));

for(let typ=1;typ<layout.NUM_OBJECTS;typ++){
 context='all-object-hmon:'+typ;reset();object(typ,2,64);scene(7,layout.PM_HUMAN);call('seed',7);act('hmon_hitmon',0,10);
}
const effectTypes=new Map();
const original=readFileSync('.cache/wasm64-build/tree/src/uhitm.c','utf8');
for(const m of original.matchAll(/case (AD_\w+): (mhitm_ad_\w+)\(/g))effectTypes.set(m[2],layout[m[1]]);
for(const fname of F.map(f=>f.name).filter(n=>n.startsWith('mhitm_ad_')))for(const role of[0,1,2])for(const scalar of[0,1])for(const seed of[1,7]){
 context='effect:'+fname+':'+role+':'+scalar+':'+seed;reset();option(40,role);option(3,scalar);scene(1,layout.AT_CLAW,effectTypes.get(fname)??layout.AD_PHYS);call('seed',seed);act(fname);
}
for(const pm of[layout.PM_HUMAN,layout.PM_IRON_GOLEM,layout.PM_PAPER_GOLEM,layout.PM_CLAY_GOLEM,layout.PM_GREEN_SLIME,layout.PM_COCKATRICE,layout.PM_BLACK_PUDDING,layout.PM_RED_DRAGON,layout.PM_DEATH,layout.PM_FAMINE,layout.PM_PESTILENCE])for(const effect of[layout.AD_PHYS,layout.AD_FIRE,layout.AD_COLD,layout.AD_ELEC,layout.AD_STON,layout.AD_DRIN,layout.AD_DGST,layout.AD_POLY])for(const role of[0,1,2]){
 context='species:'+pm+':'+effect+':'+role;reset();scene(2,pm);scene(1,layout.AT_CLAW,effect);option(40,role);option(3,1);act('mhitm_adtyping');
}
for(const form of[layout.PM_HUMAN,layout.PM_KOBOLD,layout.PM_ORC,layout.PM_LICH,layout.PM_HOMUNCULUS,layout.PM_GIANT_EEL,layout.PM_ROPE_GOLEM])for(const weapon of[0,1])for(const seed of[1,7]){
 context='poly-form:'+form+':'+weapon+':'+seed;reset();scene(4,form);scene(13,weapon,0);scene(9,1);option(3,1);call('seed',seed);act('hmonas');
}
context='xname-C-callback';reset();option(3,1);object(layout.CREAM_PIE,1,64,2n);act('hmon_hitmon_misc_obj');assert(snapshot(mods[0]).trace.includes('singular_cb:1;'));
context='display-RNG-macro';reset();property(layout.HALLUC,1);act('start_engulf');
for(const i of[0,1,2]){context='callback:'+i;reset();assert.equal(call('callback_identity',i),1);call('callback_action',i);}
for(const dead of[0,1]){context='live-mptr:'+dead;reset();option(32,1);option(34,dead);act('mhurtle_to_doom',1);}
for(const changedWeapon of[0,1]){context='live-damage-cell:'+changedWeapon;reset();option(33,1);option(35,changedWeapon);scene(15,layout.ART_EXCALIBUR,100);act('hmon_hitmon_weapon_melee');assert(snapshot(mods[0]).trace.includes('artifact:'));}
context='persistent-digestion';reset();option(3,1);option(31,1);scene(1,layout.AT_ENGL,layout.AD_DGST);scene(4,layout.PM_PURPLE_WORM);act('gulpum');assert.equal(call('retained',0),1);assert.equal(call('retained',3),1);call('retained',2);call('retained',1);
assert.equal(typeof layout.DAGGER,'number');
for(const row of JSON.parse(readFileSync(resolve(W,'record-projections.json'))))for(const missing of[false,true]){
 if(missing&&!row.nullNativeCase)continue;
 context='typed-return:'+row.name+':'+missing;reset();act('disguised_as_mon');call('record_prepare');for(const id of[1,2,5,7])option(id,Number(missing));
 const expected=mods[0]._probe_record(row.index),saved=lastServices.stackSave(),env=createUhitmEnvironment(lastServices,layout);
 try{
  const o=env.record('struct obj',mods[1]._probe_pointer(0)),o2=env.record('struct obj',mods[1]._probe_pointer(8)),m=env.record('struct monst',mods[1]._probe_pointer(1)),m2=env.record('struct monst',mods[1]._probe_pointer(7)),cell=env.ref('int',mods[1]._probe_pointer(3)),alt=env.record('struct attack',mods[1]._probe_pointer(9));
  const bindings={o,o2,m,m2,cell,alt};const args=row.jsArgs.map(j=>j in bindings?bindings[j]:j.startsWith('layout.')?layout[j.slice(7)]:j==='env.mons[layout.PM_HUMAN]'?env.mons[layout.PM_HUMAN]:j==='BigInt(layout.W_ARM)'?BigInt(layout.W_ARM):j==='1n'?1n:j==='""'?'':Number(j));
  const value=env[row.name](...args);assert.equal(BigInt(value?value[row.field]:-777),expected,context);compare();comparisons++;
  if(value){assert.equal(env.record(row.type,value.address),value,context+':cached identity');assert.equal(BigInt(value.address),mods[1]._probe_record_pointer(),context+':actual native alias');if(row.writableField){for(const m of mods)m._probe_record_write(row.index,17);assert.equal(value[row.writableField],17,context+':C write reread');compare();}}
 }finally{lastServices.stackRestore(saved);}
}
for(const alias of[0,1]){
 context='growth-reentry:'+alias;reset();option(90,1);option(92,1);option(94,alias);const lengths=mods.map(m=>m.HEAPU8.length);act('light_hits_gremlin',3);for(let i=0;i<2;i++)assert(alias?mods[i].HEAPU8.length>=lengths[i]:mods[i].HEAPU8.length>lengths[i],context+':actual memory growth');assert(snapshot(mods[0]).trace.includes('reentry:'));
}
context='controlled-C-unwind';reset();option(93,1);assert.equal(act('light_hits_gremlin',3),-999n);option(93,0);act('disguised_as_mon');
const savedModules=[...mods],secondModules=[];
for(let i=0;i<2;i++)secondModules.push(await factories[i]({print:()=>{},printErr:()=>{},nethackPorted:{uhitm:(services,name,...args)=>{lastServices=services;entries.add(name);return callUhitm(services,layout,name,...args);}}}));
mods.splice(0,2,...secondModules);context='Module-B';reset();scene(9,1);option(3,1);act('hitum_cleave');act('light_hits_gremlin',5);const savedSnapshots=mods.map(snapshot);
mods.splice(0,2,...savedModules);context='Module-A';reset();act('dynamic_multi_reason');act('hitum_cleave');assert.deepEqual(secondModules.map(snapshot),savedSnapshots,'Module-B state preserved by Module-A');
for(const seed of[1,2,3,4,7]){context='char-stride-and-roomview:'+seed;reset();option(41,1);call('seed',seed);act('do_attack');}
context='char-stride-positive';reset();option(41,1);call('seed',7);act('do_attack');assert(snapshot(mods[0]).trace.includes('shoproom:1;'),'native second room reached through actual char* stride');
for(const prop of[layout.CONFUSION,layout.STUNNED,layout.HALF_PHDAM])for(const value of[0n,1n,0x100000000n,0x20000000000001n]){
 context='native-long-property:'+prop+':'+value;reset();property(prop,value);option(40,2);act('mhitm_ad_conf');act('mhitm_ad_stun');act('mhitm_ad_poly');
}
for(const attack of[layout.AT_CLAW,layout.AT_TUCH,layout.AT_MAGC,layout.AT_KICK,layout.AT_HUGS,layout.AT_ENGL,layout.AT_EXPL])for(const weapon of[0,1]){
 context='single-body-switch-join:'+attack+':'+weapon;reset();scene(1,attack,layout.AD_PHYS);scene(4,layout.PM_LICH);scene(13,weapon,0);scene(9,1);option(3,1);option(43,1);act('hmonas');
}
for(const weight of[0,1,99,100,0xffffff00,0xfffffff0,0xffffffff]){
 context='unsigned-weight:'+weight;reset();object(layout.TOWEL,1,64);scene(17,weight);act('hmon_hitmon_misc_obj');if(weight===0xfffffff0)assert(snapshot(mods[0]).trace.includes('uhitm.c:1369:hmon_hitmon_misc_obj')&&!snapshot(mods[0]).trace.includes('uhitm.c:1355:hmon_hitmon_misc_obj'),'native wrapped default weight reaches towel bonus without large-damage RNG');act('hmon_hitmon_poison');
}
context='live-minvent-pointer-reorder';reset();option(3,1);option(1,1);scene(18,1);scene(1,layout.AT_TUCH,layout.AD_SEDU);act('steal_it');
console.log('UHITM controlled comparisons',comparisons,'entrypoints',entries.size);
writeFileSync(resolve(W,'summary.json'),JSON.stringify({status:'PASS',comparisons,entries:[...entries],scope:'controlled configured original-C/hybrid directed entry/effect/weapon comparisons; incomplete branches/native-host/shared/public unverified'},null,2));
