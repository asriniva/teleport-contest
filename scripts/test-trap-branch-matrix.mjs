import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import path from 'node:path';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import {loadFixture} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
import {callTrap} from '../js/nethack/bindings/trap.js';
import {trapSchema as schema} from '../js/ported/trap.js';
import {C,R,T} from '../js/c-runtime/context.js';
const factory=async kind=>(await loadFixture('trap',pathToFileURL(path.resolve('.cache/trap-author/probe-'+kind+'.mjs')))).default;
const reference=await (await factory('reference'))(),implementation=await (await factory('hybrid'))({nethackPorted:{trap:(services,name,...args)=>callTrap(services,name,...args)}});
const modules=[reference,implementation],globals=Object.keys(schema.foreignGlobals);
const field=(record,name)=>{const row=schema.records[record].fields.find(f=>f.name===name);assert.ok(row,record+'.'+name);return row;};
const global=(m,name)=>m._probe_global(globals.indexOf(name));
const properties=['FIRE_RES','SLEEP_RES','ANTIMAGIC','UNCHANGING','LEVITATION','FLYING','HALF_PHDAM'];
const species=['PM_AIR_ELEMENTAL','PM_FIRE_ELEMENTAL','PM_FIRE_VORTEX','PM_IRON_GOLEM','PM_GREMLIN','PM_GELATINOUS_CUBE','PM_STONE_GOLEM','PM_FOG_CLOUD'];
for(const name of species)assert.ok(name in schema.constants,'configured C species '+name);
const header=fs.readFileSync('.cache/wasm64-build/tree/include/hack.h','utf8');
const flags=['FORCETRAP','NOWEBMSG','FORCEBUNGLE','RECURSIVETRAP','TOOKPLUNGE','VIASITTING','FAILEDUNTRAP','HURTLING'].map(name=>{
 const match=header.match(new RegExp('^#define\\s+'+name+'\\s+0x([0-9a-f]+)U\\b','m'));assert.ok(match,'configured C flag '+name);return parseInt(match[1],16);
});
flags.push(flags.reduce((combined,value)=>combined|value,0));
const propertyField=field('you','uprops'),propertyRecord=propertyField.type.of.record;
const propertyAt=(base,name)=>Number(base)+propertyField.offset+schema.constants[name]*schema.records[propertyRecord].size;
function text(m,p){let at=Number(p),end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(at,end)).toString('latin1');}
function read(m,at,record,name){
 const f=field(record,name),p=Number(at)+f.offset;
 if(f.bits!==null){let raw=0n;for(let i=0;i<Math.ceil((f.bitOffset+f.bits)/8);i++)raw|=BigInt(m.HEAPU8[p+i])<<BigInt(i*8);return Number(raw>>BigInt(f.bitOffset)&((1n<<BigInt(f.bits))-1n));}
 const names={i8:'getInt8',u8:'getUint8',i16:'getInt16',u16:'getUint16',i32:'getInt32',u32:'getUint32',i64:'getBigInt64',u64:'getBigUint64'};
 assert.ok(names[f.type],record+'.'+name+' scalar');return new FixtureDataView(m.HEAPU8.buffer)[names[f.type]](p,true);
}
function writeBits(m,pointer,record,name,value){
 const f=field(record,name),at=Number(pointer)+f.offset;assert.notEqual(f.bits,null);
 let raw=0n;const bytes=Math.ceil((f.bitOffset+f.bits)/8);
 for(let i=0;i<bytes;i++)raw|=BigInt(m.HEAPU8[at+i])<<BigInt(i*8);
 const mask=((1n<<BigInt(f.bits))-1n)<<BigInt(f.bitOffset);raw=(raw&~mask)|(BigInt(value)<<BigInt(f.bitOffset)&mask);
 for(let i=0;i<bytes;i++)m.HEAPU8[at+i]=Number(raw>>BigInt(i*8)&255n);
}
const setTrapType=(m,value)=>writeBits(m,m._probe_trap(0),'trap','ttyp',value);
function snapshot(m){
 const fields=(at,record,names)=>names.map(name=>read(m,at,record,name));
 return {
  hero:fields(global(m,'u'),'you',['ux','uy','utrap','utraptype','uhp','uhpmax','uen','uenmax','ucreamed']),
  objects:Array.from({length:3},(_,i)=>fields(m._probe_object(i),'obj',['otyp','quan','spe','greased','oeroded','oeroded2','in_use','owornmask'])),
  traps:Array.from({length:3},(_,i)=>m._probe_trap_live(i)?fields(m._probe_trap(i),'trap',['tx','ty','ttyp','tseen','once','madeby_u']):'freed'),
  monster:fields(m._probe_mon_pointer(0),'monst',['mhp','mhpmax','mtrapped','msleeping','mcanmove','mfrozen']),
  monsterSpecies:read(m,new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_mon_pointer(0))+field('monst','data').offset,true),'permonst','pmidx'),
  properties:properties.map(name=>fields(propertyAt(global(m,'u'),name),propertyRecord,['intrinsic','extrinsic','blocked'])),
  trace:text(m,m._probe_trace()),
 };
}
const effects={arrow_trap:'ARROW_TRAP',dart_trap:'DART_TRAP',rocktrap:'ROCKTRAP',sqky_board:'SQKY_BOARD',bear_trap:'BEAR_TRAP',slp_gas_trap:'SLP_GAS_TRAP',rust_trap:'RUST_TRAP',fire_trap:'FIRE_TRAP',pit:'PIT',hole:'HOLE',telep_trap:'TELEP_TRAP',level_telep:'LEVEL_TELEP',web:'WEB',statue_trap:'STATUE_TRAP',magic_trap:'MAGIC_TRAP',anti_magic:'ANTI_MAGIC',poly_trap:'POLY_TRAP',landmine:'LANDMINE',rolling_boulder_trap:'ROLLING_BOULDER_TRAP',magic_portal:'MAGIC_PORTAL',vibrating_square:'VIBRATING_SQUARE'};
let cases=0;
function compare(effect,constant,hero,seed,property,propertyState,trflags=0,form,entry,trapped=0,seen=0){
 const type=typeof constant==='number'?constant:schema.constants[constant];assert.ok(Number.isInteger(type)&&type>=0&&type<32,String(constant));
 const name=entry??'trapeffect_'+effect,label=name+':type='+type+':hero='+hero+':seed='+seed+':property='+(property??'none')+':state='+JSON.stringify(propertyState??[])+':flags='+trflags+':species='+(form??'default')+':trapped='+trapped+':seen='+seen;
 for(const m of modules){
  m._probe_setup();m._probe_option(499,1);m._probe_seed(seed);setTrapType(m,type);
  if(entry){writeBits(m,m._probe_mon_pointer(0),'monst','mcanmove',1);writeBits(m,m._probe_mon_pointer(0),'monst','mtrapped',trapped);writeBits(m,m._probe_trap(0),'trap','tseen',seen);}
  if(property){
   assert.ok(property in schema.constants,property);const at=propertyAt(global(m,'u'),property);
   for(const [index,key]of ['intrinsic','extrinsic','blocked'].entries())new FixtureDataView(m.HEAPU8.buffer).setBigInt64(at+field(propertyRecord,key).offset,BigInt(propertyState[index]),true);
  }
  if(form)new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(m._probe_mon_pointer(0))+field('monst','data').offset,m._probe_catalogue(1,schema.constants[form]),true);
  m._probe_clear();
 }
 const stacks=modules.map(m=>m._probe_stack());
 const values=modules.map(m=>entry==='dotrap'?m._probe_call_dotrap(m._probe_trap(0),trflags):entry==='mintrap'?m._probe_call_mintrap(m._probe_mon_pointer(0),trflags):m['_probe_call_'+name](hero?m._probe_hero():m._probe_mon_pointer(0),m._probe_trap(0),trflags));
 assert.equal(values[1],values[0],label+' return');assert.deepEqual(snapshot(implementation),snapshot(reference),label+' configured scalar state and complete trace');
 assert.deepEqual(modules.map(m=>m._probe_stack()),stacks,label+' restored stacks');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);cases++;
}
const dispatchOnly=process.argv.includes('--dispatch-only');for(const arg of process.argv.slice(2))assert.equal(arg,'--dispatch-only','unknown trap matrix argument');
if(!dispatchOnly)for(const [effect,constant]of Object.entries(effects)){
 for(const hero of [false,true])for(let seed=0;seed<16;seed++)compare(effect,constant,hero,seed);
 for(const property of properties)for(const state of [[1,0,0],[0,1,0],[1,0,1],[0,1,1]])for(const seed of [0,1,7,15])compare(effect,constant,true,seed,property,state);
 for(const hero of [false,true])for(const seed of [0,7])for(const flag of flags)compare(effect,constant,hero,seed,undefined,undefined,flag);
 for(const form of species)for(const seed of [0,1,7,15])compare(effect,constant,false,seed,undefined,undefined,0,form);
}
assert.equal(cases,dispatchOnly?0:4452);const baseline=cases;
if(!dispatchOnly)console.log('PASS: TRAP '+cases+' original-C/pure-JS comparisons across21 effects, hero/monster subjects,16 baseline seeds,7 intrinsic/extrinsic/blocked properties,8 trap flags plus union and8 catalogue-backed monster forms; scalar/property/species state, complete per-case trace, returns, stacks and contexts.');
for(let type=0;type<32;type++)for(const hero of [false,true])for(const seed of [0,1,7,15])for(const flag of [0,flags[0],flags[3]])compare('selector',type,hero,seed,undefined,undefined,flag,undefined,'trapeffect_selector');
const valid=[...Object.values(effects),'SPIKED_PIT','TRAPDOOR'];assert.equal(new Set(valid.map(name=>schema.constants[name])).size,23);
for(const type of valid)for(const seen of [0,1])for(const seed of [0,1,7,15])for(const flag of [0,flags[0],flags[2],flags[5]])compare('hero-entry',type,true,seed,undefined,undefined,flag,undefined,'dotrap',0,seen);
for(let type=0;type<32;type++)for(const trapped of [0,1])for(const seen of [0,1])for(const seed of [0,1,7,15])compare('monster-entry',type,false,seed,undefined,undefined,0,undefined,'mintrap',trapped,seen);
assert.equal(cases-baseline,2016);console.log('PASS: TRAP2016 additional original-C/pure-JS selector/hero-entry/monster-entry cases, including32 type encodings,23 valid trap types, seen/unseen/trapped states, selected force flags and4 seeds; declared scalar/property/species state, complete traces and restored contexts/stacks. Unknown encodings are explicit native diagnostic cases.');
const entryBaseline=cases;
for(const type of valid)for(const property of properties)for(const state of [[1,0,0],[0,1,0],[1,0,1],[0,1,1]])for(const seed of [0,7])for(const flag of [0,flags[0],flags[2],flags[5]])compare('hero-entry-property',type,true,seed,property,state,flag,undefined,'dotrap');
const forms=Object.keys(schema.constants).filter(name=>name.startsWith('PM_')).sort();assert.equal(forms.length,46,'review configured trap catalogue additions');
for(const type of valid)for(const form of forms)for(const trapped of [0,1])for(const seed of [0,7])compare('monster-entry-species',type,false,seed,undefined,undefined,0,form,'mintrap',trapped);
assert.equal(cases-entryBaseline,9384);console.log('PASS: TRAP9384 additional original-C/pure-JS entry cases:5152 hero property/force combinations and4232 monster cases across all46 species named by the configured trap source,23 trap types, trapped/free states and2 seeds; complete declared snapshots/traces and restored stacks/contexts.');
