import './pure-js-probes/deny-wasm.mjs';
import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('write', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/write-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('write',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),layout=layouts.write;
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:createPortedRuntime(layouts)})],stacks=modules.map(m=>m._probe_stack());
let comparisons=0;
function bytes(m,p,n){p=Number(p);if(n===undefined){if(!p)return null;let e=p;while(m.HEAPU8[e])e++;n=e-p;}return Buffer.from(m.HEAPU8.slice(p,p+n));}
function snapshot(m){return {storage:Array.from({length:4},(_,i)=>bytes(m,m._probe_snapshot_pointer(i),Number(m._probe_snapshot_size(i)))),scalars:Array.from({length:3},(_,i)=>m._probe_scalar(i)),literate:m._probe_literate(),random:m._probe_rng_state()>>>0,count:m._probe_rng_count(),knowledge:Array.from({length:layout.NUM_OBJECTS},(_,i)=>[m._probe_known(i),m._probe_encountered(i)]),trace:bytes(m,m._probe_trace()).toString('hex')};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],`${name}(${args})`);state();comparisons++;return values[0];}
function textCall(name,text,...args){const results=modules.map(m=>{let p=0;if(text!==null){const b=Buffer.isBuffer(text)?text:Buffer.from(text);p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;}const result=m['_probe_'+name](...args,BigInt(p));if(p)m._free(p);return result;});assert.deepEqual(results[1],results[0]);state();comparisons++;return results[0];}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function name(typ){return bytes(modules[0],modules[0]._probe_name(typ))?.toString();}
function descr(typ){return bytes(modules[0],modules[0]._probe_descr(typ))?.toString();}
function object(typ,known=1,encountered=1,uname=null){textCall('object',uname,typ,known,encountered);}
function objectField(index,field){const m=modules[0],at=Number(m._probe_snapshot_pointer(index))+layout['obj_'+field],size=layout['obj_'+field+'_size'];return new DataView(m.HEAPU8.buffer)[`getInt${size*8}`](at,true);}
function prepare(typ,known=1,encountered=1){reset();const book=modules[0]._probe_class(typ)===layout.SPBOOK_CLASS;call('paper',book?layout.SPE_BLANK_PAPER:layout.SCR_BLANK_PAPER,1,1,0,0);object(typ,known,encountered);textCall('input',name(typ));rng([0,0,0,0]);}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=bytes(m,m._probe_layout_name(i)).toString();assert.equal(Number(m._probe_layout_value(i)),layout[key],key);}
const scrolls=[],books=[];for(let i=0;i<layout.NUM_OBJECTS;i++){const cls=modules[0]._probe_class(i);if(cls===layout.SCROLL_CLASS)scrolls.push(i);if(cls===layout.SPBOOK_CLASS)books.push(i);}
assert.ok(scrolls.length>20&&books.length>20);
// Every real scroll and spellbook cost and description is obtained from the
// original C master table; no hand-maintained list of labels or costs.
for(const typ of [...scrolls,...books]){call('cost',typ,modules[0]._probe_class(typ));call('ok',typ,modules[0]._probe_class(typ),0);}
for(const typ of books)if(descr(typ)!==undefined){assert.equal(call('description',typ),1);}
for(const cls of [0,layout.TOOL_CLASS,layout.SCROLL_CLASS,layout.SPBOOK_CLASS,255])for(const nullobj of [0,1])call('ok',layout.SCR_BLANK_PAPER,cls,nullobj);
for(const typ of [...scrolls,...books])if(typ>=layout.MAXOCLASSES&&name(typ)){prepare(typ);call('write');}
// Reachability assertions independently establish that the fixture initialized
// names/class bases correctly and reached real success, failure and dry paths.
prepare(layout.SCR_IDENTIFY);assert.equal(call('write'),layout.ECMD_TIME);assert.equal(call('scalar',0),1);assert.equal(call('scalar',1),0);assert.equal(call('scalar',2),1);assert.equal(objectField(0,'spe'),93);assert.equal(call('literate'),1n);assert.equal(objectField(2,'otyp'),layout.SCR_IDENTIFY);
prepare(layout.SCR_IDENTIFY,0,0);rng([0,1]);call('write');assert.equal(call('scalar',0),1);assert.equal(call('scalar',1),1);assert.equal(call('scalar',2),0);assert.equal(call('literate'),1n);
prepare(layout.SCR_IDENTIFY);call('pen',6,1,0,0);call('write');assert.equal(call('scalar',0),0);assert.equal(call('scalar',1),1);assert.equal(call('scalar',2),0);assert.equal(objectField(0,'spe'),6);
prepare(layout.SCR_IDENTIFY);object(layout.SCR_FIRE);call('descr_index',layout.SCR_IDENTIFY,layout.SCR_FIRE);call('descr_index',layout.SCR_FIRE,layout.SCR_IDENTIFY);textCall('input',descr(layout.SCR_IDENTIFY));call('write');assert.equal(objectField(2,'otyp'),layout.SCR_IDENTIFY);
for(const intrinsic of [0n,1n]){prepare(layout.SPE_NOVEL);call('properties',0,0,0,1,layout.PM_ARCHEOLOGIST);call('property',layout.HALLUC_RES,intrinsic,1n-intrinsic,0n);rng([0,1]);call('write');assert.ok(bytes(modules[0],modules[0]._probe_trace()).toString().includes('really lame fan-fiction'));}
// Explicit object-selection and early hero-condition paths.
for(const [hands,glib,blind] of [[1,0,0],[0,1,0],[1,1,1]]){reset();call('properties',hands,glib,blind,0,layout.PM_ARCHEOLOGIST);call('write');}
reset();call('option',0,1);call('write');
for(const typ of [layout.SCR_IDENTIFY,layout.SPE_NOVEL,layout.SPE_BLANK_PAPER,layout.SCR_BLANK_PAPER])for(const dknown of [0,1]){reset();call('paper',typ,dknown,1,0,0);call('properties',0,0,1,0,layout.PM_ARCHEOLOGIST);textCall('input','identify');call('write');}
for(const [intrinsic,extrinsic,blocked] of [[1n,0n,0n],[0n,1n,0n],[1n,1n,1n]]){prepare(layout.SCR_IDENTIFY);call('property',layout.BLINDED,intrinsic,extrinsic,blocked);call('write');}
for(const text of ['', '\x1b','unknown spell','  scroll  of identify  ','SCROLL OF IDENTIFY','spellbook of identify','enchant armour']){prepare(layout.SCR_IDENTIFY);object(layout.SCR_ENCHANT_ARMOR);textCall('input',text);call('write');}
// Description, assigned-name and deferred real-name matching.  Multiple names
// exercise reservoir replacement and the known-real-type exclusion.
for(const rolls of [[0,0,0],[0,1,0],[0,1,2]]){prepare(layout.SCR_IDENTIFY,0,0);object(layout.SCR_LIGHT,0,1,'identify');object(layout.SCR_FIRE,0,1,'identify');object(layout.SCR_EARTH,0,1,'identify');rng(rolls.concat(0,0));call('write');}
prepare(layout.SCR_IDENTIFY,0,0);object(layout.SCR_LIGHT,1,1,'identify');call('write');
for(const typ of [layout.SCR_IDENTIFY,layout.SPE_FORCE_BOLT])for(const known of [0,1])for(const encountered of [0,1]){prepare(typ,known,encountered);textCall('input',descr(typ));call('write');}
prepare(layout.SPE_FORCE_BOLT,0,0);object(layout.SPE_FORCE_BOLT,0,1,'custom spell');textCall('input','custom spell');call('write');
for(const fanfic of [0,1])for(const tearup of [0,1])for(const halluc of [0,1]){prepare(layout.SPE_NOVEL);call('properties',0,0,0,halluc,layout.PM_ARCHEOLOGIST);rng([fanfic,tearup]);call('write');}
for(const typ of [layout.SCR_IDENTIFY,layout.SPE_FORCE_BOLT])for(const charges of [-128,-1,0,6,7,8,13,14,127])for(const roll of [0,100]){prepare(typ);call('pen',charges,1,0,0);rng([roll,0]);call('write');}
for(const penCurse of [-1,0,1])for(const paperCurse of [-1,0,1])for(const known of [0,1])for(const paperKnown of [0,1]){prepare(layout.SCR_IDENTIFY);call('pen',100,known,penCurse>0,penCurse<0);call('paper',layout.SCR_BLANK_PAPER,1,paperKnown,paperCurse>0,paperCurse<0);call('write');}
for(const typ of [layout.SCR_IDENTIFY,layout.SPE_FORCE_BOLT])for(const knowledge of [layout.spe_Unknown,layout.spe_Fresh,layout.spe_GoingStale])for(const role of [layout.PM_ARCHEOLOGIST,layout.PM_WIZARD])for(const luck of [0,1]){prepare(typ,0,0);call('properties',0,0,0,0,role);call('option',1,knowledge);rng([0,luck,1]);call('write');}
for(const encountered of [0,1]){prepare(layout.SCR_IDENTIFY,0,encountered);textCall('input',descr(layout.SCR_IDENTIFY));rng([0,1]);call('write');}
for(const level of [-2147483648,2147483647]){prepare(layout.SCR_IDENTIFY,0,0);call('hero',0n,level);textCall('input',descr(layout.SCR_IDENTIFY));rng([0,1]);call('write');assert.ok(bytes(modules[0],modules[0]._probe_trace()).toString().includes('wipe:'));}
for(const known of [0,1])for(const firstLuck of [0,1])for(const blindLuck of [0,1]){prepare(layout.SCR_IDENTIFY,known,0);call('properties',0,0,1,0,layout.PM_ARCHEOLOGIST);rng(known?[0,blindLuck]:[0,firstLuck,blindLuck]);call('write');}
for(const literate of [0n,1n,9007199254740993n,9223372036854775807n]){prepare(layout.SCR_IDENTIFY);call('hero',literate,30);call('write');}
prepare(layout.SCR_IDENTIFY);call('option',2,1);call('write');
prepare(layout.SCR_IDENTIFY,0,0);call('option',4,0);rng([0,1]);call('write');
reset();const saved=snapshot(modules[0]);modules[1]._probe_pen(1,0,0,1);assert.deepEqual(snapshot(modules[0]),saved);reset();
const allocated=modules.map(m=>m._malloc(40n*1024n*1024n));assert.ok(allocated.every(Boolean));object(layout.SPE_FORCE_BOLT);call('paper',layout.SPE_BLANK_PAPER,1,1,0,0);textCall('input',name(layout.SPE_FORCE_BOLT));rng([0]);call('write');modules.forEach((m,i)=>m._free(allocated[i]));state();
console.log(`WRITE: ${comparisons} ${referenceLabel}/pure-JS costs, selection, naming, ink, knowledge, conduct and callback/RNG-trace comparisons checked.`);
