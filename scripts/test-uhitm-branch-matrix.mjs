// Extra deterministic branch inputs, always checked against original C.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import {pathToFileURL} from 'node:url';
import {loadFixture} from './pure-js-fixtures/load.mjs';
import {callUhitm} from '../js/nethack/bindings/uhitm.js';
const directory=path.resolve('.cache/uhitm-author'),functions=JSON.parse(fs.readFileSync(path.join(directory,'functions.json'))),layout={};
const refFactory=(await loadFixture('uhitm',pathToFileURL(path.resolve('.cache/tu-probes/uhitm/reference.mjs')))).default;
const jsFactory=(await loadFixture('uhitm',pathToFileURL(path.join(directory,'hybrid.mjs')))).default;
const ref=await refFactory({print(){},printErr(){}}),js=await jsFactory({print(){},printErr(){},nethackPorted:{uhitm:(services,name,...args)=>callUhitm(services,layout,name,...args)}});
function text(m,p){let at=Number(p),end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(at,end)).toString('latin1');}
for(let i=0;i<ref._probe_layout_count();i++)layout[text(ref,ref._probe_layout_name(i))]=Number(ref._probe_layout_value(i));
const read=m=>({trace:text(m,m._probe_trace()),buffer:text(m,m._probe_buffer()),state:text(m,m._probe_snapshot())});
const seeds=Number(process.env.UHITM_BRANCH_SEEDS??32);assert.ok(Number.isSafeInteger(seeds)&&seeds>0&&seeds<=1024);
let cases=0;
for(let seed=1;seed<=seeds;seed++)for(const[index,fn]of functions.entries()){
 const label=fn.name+':seed='+seed;
 for(const m of [ref,js]){m._probe_reset();m._probe_clear();m._probe_seed(seed);}
 const stacks=[ref,js].map(m=>m._probe_stack()),a=ref._probe_action(index,0,0,0),b=js._probe_action(index,0,0,0);
 assert.equal(b,a,label+' return');assert.deepEqual(read(js),read(ref),label+' full state/trace/buffer');assert.deepEqual([ref,js].map(m=>m._probe_stack()),stacks,label+' restored stacks');cases++;
}
console.log('PASS: UHITM '+cases+' deterministic original-C/pure-JS branch-input cases across '+functions.length+' routines and '+seeds+' seeds; production window dispatch has its separate regression.');
const original=fs.readFileSync('.cache/wasm64-build/tree/src/uhitm.c','utf8');
const effects=[...new Set([...original.matchAll(/case (AD_\w+): (mhitm_ad_\w+)\(/g)].map(match=>match[1]))];
const species=['PM_HUMAN','PM_IRON_GOLEM','PM_PAPER_GOLEM','PM_CLAY_GOLEM','PM_GREEN_SLIME','PM_COCKATRICE','PM_BLACK_PUDDING','PM_RED_DRAGON','PM_DEATH','PM_FAMINE','PM_PESTILENCE'];
const dispatch=functions.findIndex(fn=>fn.name==='mhitm_adtyping');assert.ok(dispatch>=0);assert.ok(effects.length>20);
let effectCases=0;
for(const effect of effects)for(const pm of species)for(const role of [0,1,2])for(const seed of [2,3,11,31]){
 assert.ok(Number.isInteger(layout[effect]),effect);assert.ok(Number.isInteger(layout[pm]),pm);
 for(const m of [ref,js]){m._probe_reset();m._probe_clear();m._probe_seed(seed);m._probe_scene(2,layout[pm],0);m._probe_scene(1,layout.AT_CLAW,layout[effect]);m._probe_option(40,role);m._probe_option(3,1);}
 const label=[effect,pm,role,seed].join(':'),stacks=[ref,js].map(m=>m._probe_stack());
 const a=ref._probe_action(dispatch,0,0,0),b=js._probe_action(dispatch,0,0,0);
 assert.equal(b,a,label+' return');assert.deepEqual(read(js),read(ref),label+' declared full state/trace/buffer');assert.deepEqual([ref,js].map(m=>m._probe_stack()),stacks,label+' restored stacks');effectCases++;
}
console.log('PASS: UHITM '+effectCases+' additional damage-dispatch comparisons across '+effects.length+' original C handled damage types,11 defender species,3 roles and4 seeds.');
const properties=['ANTIMAGIC','COLD_RES','CONFUSION','DRAIN_RES','FIRE_RES','FREE_ACTION','HALF_PHDAM','HALLUC_RES','POISON_RES','SHOCK_RES','SLEEP_RES','SLIMED','STONE_RES','STUNNED','UNCHANGING'];
let propertyCases=0;
for(const effect of effects)for(const name of properties)for(const role of [0,1,2])for(const values of [[1n,0n,0n],[0n,1n,0n],[0n,1n,1n],[0x20000000000001n,0n,0n]]){
 assert.ok(Number.isInteger(layout[name]),name);
 for(const m of [ref,js]){m._probe_reset();m._probe_clear();m._probe_seed(11);m._probe_scene(1,layout.AT_CLAW,layout[effect]);m._probe_option(40,role);m._probe_option(3,1);m._probe_property(layout[name],...values);}
 const label=[effect,name,role,values.map(String).join(',')].join(':'),stacks=[ref,js].map(m=>m._probe_stack());
 const a=ref._probe_action(dispatch,0,0,0),b=js._probe_action(dispatch,0,0,0);
 assert.equal(b,a,label+' return');assert.deepEqual(read(js),read(ref),label+' declared fixture state/trace/buffer');assert.deepEqual([ref,js].map(m=>m._probe_stack()),stacks,label+' restored stacks');propertyCases++;
}
assert.equal(propertyCases,effects.length*15*3*4);
console.log('PASS: UHITM '+propertyCases+' additional damage/property comparisons over15 intrinsic/extrinsic/blocked/high-bit properties and3 roles; complete declared fixture snapshots, not full-world acceptance.');
