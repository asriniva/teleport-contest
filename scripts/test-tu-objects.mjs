import { assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('objects', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/objects-reference.mjs';
import hybridFactory from '../.cache/tu-probes/objects-hybrid.mjs';
import {createPortedRuntime} from '../js/ported/wasm-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.objects;
const runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function string(m,p){if(p===0n||p===0)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function bytes(m,p,size){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+size));}
function snapshot(m){const count=m._probe_count(),fields=m._probe_field_count(),alias=new Map(),strings=[],values=[];let next=0;for(let row=0;row<count;row++){values.push(Array.from({length:fields},(_,f)=>m._probe_value(row,f)));strings.push(Array.from({length:3},(_,f)=>{const p=m._probe_string(row,f);if(p===0n)return {value:null,alias:-1};const key=p.toString();if(!alias.has(key))alias.set(key,next++);return {value:string(m,p),alias:alias.get(key)};}));}const objects=bytes(m,m._probe_objects(),count*L.objectSize),descriptors=bytes(m,m._probe_descriptors(),count*L.descriptorSize);for(let row=0;row<count;row++){objects.fill(0,row*L.objectSize+L.oc_uname,row*L.objectSize+L.oc_uname+L.pointerSize);for(const field of ['oc_name','oc_descr'])descriptors.fill(0,row*L.descriptorSize+L[field],row*L.descriptorSize+L[field]+L.pointerSize);}return {values,strings,objects,descriptors};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function init(){modules.forEach(m=>m._probe_init());check();}
for(const m of modules){assert.equal(m._probe_count(),L.rowCount);assert.equal(m._probe_count(),L.NUM_OBJECTS+1);for(let i=0;i<m._probe_layout_count();i++){const k=string(m,m._probe_layout_name(i));assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),L[k],k);}}
const names=Array.from({length:modules[0]._probe_field_count()},(_,f)=>string(modules[0],modules[0]._probe_field_name(f)));
assert.equal(names.length,32);assert.equal(new Set(names).size,names.length);modules.forEach(m=>names.forEach((name,f)=>assert.equal(string(m,m._probe_field_name(f)),name)));
// C globals start zero; materializing private JS templates must not initialize
// the destinations before the original public initializer is invoked.
check();const uninitialized=snapshot(modules[0]);assert.ok(uninitialized.objects.every(b=>b===0));assert.ok(uninitialized.descriptors.every(b=>b===0));assert.ok(uninitialized.strings.every(row=>row.every(s=>s.value===null)));
init();const pointers=modules.map(m=>Array.from({length:L.rowCount},(_,row)=>Array.from({length:3},(_,f)=>m._probe_string(row,f))));
function stablePointers(){modules.forEach((m,i)=>{for(let row=0;row<L.rowCount;row++)for(let f=0;f<3;f++)assert.equal(m._probe_string(row,f),pointers[i][row][f]);});}
const oracle=snapshot(modules[0]);let negative=0,allOnes=0,nulls=0,nonempty=0;for(let row=0;row<L.rowCount;row++){for(let f=0;f<names.length;f++){const a=modules[0]._probe_value(row,f),b=modules[1]._probe_value(row,f);assert.equal(b,a,`row${row}.${names[f]}`);assert.equal(modules[1]._probe_field_kind(f),modules[0]._probe_field_kind(f));if(modules[0]._probe_field_kind(f)===0&&BigInt.asIntN(64,a)<0n)negative++;if(names[f].endsWith('_minseen')||names[f].endsWith('_maxseen'))if(BigInt.asUintN(64,a)===(1n<<64n)-1n)allOnes++;comparisons++;}for(let f=0;f<3;f++){const value=oracle.strings[row][f].value;if(value===null)nulls++;else if(value.length)nonempty++;assert.equal(string(modules[1],modules[1]._probe_string(row,f)),value,`row${row}.string${f}`);comparisons++;}}
assert.ok(negative>0,'native catalogue contains signed negative fields');assert.ok(allOnes>0,'native price sentinels retain all ulong bits');assert.ok(nulls>0&&nonempty>0);
// Includes the native catalogue terminator, without assuming its field values.
assert.deepEqual(snapshot(modules[1]).values[L.NUM_OBJECTS],oracle.values[L.NUM_OBJECTS]);
for(let repeat=0;repeat<3;repeat++){init();assert.deepEqual(snapshot(modules[0]),oracle);stablePointers();}
// Every actual field is mutable in the output table. Reset must restore the
// original immutable catalogue, including packed-bitfield neighbours/padding.
for(let row=0;row<L.rowCount;row++){for(let f=0;f<names.length;f++){const v=BigInt.asUintN(64,BigInt(row*97+f)*0x9e3779b97f4a7c15n);modules.forEach(m=>m._probe_mutate(row,f,v));}modules.forEach(m=>m._probe_strings(row,1+row%2));}check();assert.equal(snapshot(modules[0]).strings[0][0].value,'');assert.equal(snapshot(modules[0]).strings[0][2].value,'fixture user name');assert.notDeepEqual(snapshot(modules[0]),oracle);init();assert.deepEqual(snapshot(modules[0]),oracle);stablePointers();
// Poison every byte, including native padding and pointer slots; invoke init
// before any getters can dereference those deliberately invalid pointers.
for(const seed of [0,1,0xffffffff]){modules.forEach(m=>m._probe_poison(seed));init();assert.deepEqual(snapshot(modules[0]),oracle);stablePointers();}
// Two JS modules sharing one runtime must still allocate independent mutable
// output and templates, keyed by their actual native module identities.
const other=await hybridFactory({nethackPorted:runtime}),otherStack=other._probe_stack();other._probe_init();assert.deepEqual(snapshot(other),oracle);modules[1]._probe_strings(0,2);modules[1]._probe_mutate(0,0,65535n);assert.deepEqual(snapshot(other),oracle);assert.deepEqual(snapshot(modules[0]),oracle);modules[1]._probe_init();check();
const before=modules.map(m=>allocationMetric(m)),allocations=modules.map(m=>m._malloc(BigInt(allocationMetric(m)+16*1024*1024)));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));init();assert.deepEqual(snapshot(modules[0]),oracle);assert.deepEqual(snapshot(other),oracle);modules.forEach((m,i)=>m._free(allocations[i]));assertStackRestored(other, otherStack);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
console.log(`OBJECTS: ${comparisons} ${referenceLabel}/hybrid full-catalogue field, string, alias, padding and reinitialization comparisons checked.`);
