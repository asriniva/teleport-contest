import './pure-js-probes/deny-wasm.mjs';
import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('getline', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/getline-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('getline',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),layout=layouts.getline;
const runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){p=Number(p);if(n===undefined){let e=p;while(m.HEAPU8[e])e++;n=e-p;}return Buffer.from(m.HEAPU8.slice(p,p+n));}
function snapshot(m){return {storage:Array.from({length:5},(_,i)=>bytes(m,m._probe_snapshot_pointer(i),Number(m._probe_snapshot_size(i)))),scalars:Array.from({length:6},(_,i)=>m._probe_scalar(i)),trace:bytes(m,m._probe_trace()).toString('hex')};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));if(runtime.getlineState)assert.equal(Number(runtime.getlineState.suppress_history),modules[0]._probe_history());assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],`${name}(${args})`);state();comparisons++;return values[0];}
function textCall(name,text,...args){const values=modules.map(m=>{let p=0;if(text!==null){const data=Buffer.isBuffer(text)?text:Buffer.from(text);p=m._malloc(BigInt(data.length+1));m.HEAPU8.set(data,Number(p));m.HEAPU8[Number(p)+data.length]=0;}const result=m['_probe_'+name](BigInt(p),...args);if(p)m._free(p);return result;});assert.deepEqual(values[1],values[0]);state();comparisons++;return values[0];}
function input(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_input_pointer()),values.length).set(values);m._probe_input_length(values.length);});state();}
function reset(){call('reset');}
function line(keys,query='Name?',hook){reset();input(keys);if(hook===undefined)textCall('line',query);else textCall('hooked',query,hook);}
function answer(){return bytes(modules[0],modules[0]._probe_snapshot_pointer(4));}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=bytes(m,m._probe_layout_name(i)).toString();assert.equal(Number(m._probe_layout_value(i)),layout[key],key);}
for(const keys of [[10],[13],[97,98,99,10],[8,97,98,8,99,10],[97,98,21,99,10],[97,98,127,99,10],[97,27,98,10],[27],[97,27,27],[-1],[97,-1],[0,1,9,97,10],[128,129,254,10],[255]])line(keys);
line([97,98,10]);assert.equal(answer().toString(),'ab');
line([...Array(100).fill(97),10]);assert.equal(answer().length,layout.COLNO);
for(const erase of [8,127,64,-128]){reset();call('option',8,erase);input([97,98,erase&255,99,10]);textCall('line','Erase?');}
for(const kill of [21,64,127]){reset();call('option',9,kill);input([97,98,kill,99,10]);textCall('line','Kill?');}
for(const mode of ['s','c','f','r'])for(const count of [1,2,3]){reset();call('option',0,mode.charCodeAt(0));input([97,...Array(count).fill(16),98,10]);textCall('line','History?');}
for(const top of [0,layout.TOPLINE_NEED_MORE])for(const stopped of [0,layout.WIN_STOP]){reset();call('option',4,top);call('option',5,stopped);call('option',14,2);input([97,10]);textCall('line','Prompt?');}
for(const interrupt of [1,2,3]){reset();call('option',7,interrupt);input([97,98,99,10]);textCall('line','Interrupt?');}
reset();textCall('default','previous');input([10]);textCall('line','Default?');assert.equal(answer().length,layout.EDIT_GETLIN?8:0);
// Completion leaves the insertion cursor before the suggested suffix.  These
// inputs exercise replacement, failed guesses, erase, kill and ESC restart.
for(const keys of [[99,10],[99,111,10],[99,122,10],[99,8,112,10],[99,21,112,10],[99,27,112,10],[97,100,10],[102,111,111,10]])line(keys,'#',1);
for(const prefix of ['', 'a','ad','adjust','c','ca','co','p','foo','none']){reset();textCall('default',prefix);call('hook');}
for(const doagain of [0,1])for(const keys of [[99,10],[99,97,115,116,10],[97,10],[102,111,111,10],[120,10],[10],[27],[32,99,97,115,116,32,10],Array(70).fill(120).concat(10)]){reset();call('option',3,doagain);input(keys);call('ext');}
for(const value of [-1,0,4,123]){reset();call('option',2,1);call('option',13,value);input([]);assert.equal(call('ext'),value);}
// Public getlin resets history suppression after an extended-command prompt.
reset();input([112,10]);call('ext');input([97,10]);textCall('line','Next?');
// xwait uses int input, unlike pgetchar's signed char.  In particular strchr
// converts its search byte, while dismiss_more is promoted from plain char.
for(const cbreak of [0,1])for(const allowed of [null,'z',''])for(const keys of [[10],[13],[27,10],[120,122,10],[-1],[256,10],[128,10]]){reset();call('option',1,cbreak);input(keys);textCall('wait',allowed);}
for(const dismiss of [10,13,32,128,255]){reset();call('option',10,dismiss);input([dismiss,10]);textCall('wait',null);}
for(const keys of [[120,10],[27],[13]]){reset();call('option',11,0);input(keys);textCall('wait',null);}
reset();call('option',12,1);input([]);textCall('wait',null);
// Repeated completion callbacks must release their temporary native frame.
// A 16-byte allocation retained per callback would exceed a 64KiB C stack.
reset();input(Array.from({length:6000},()=>[99,8]).flat().concat(10));textCall('hooked','#',1);assert.equal(answer().length,0);
reset();const saved=snapshot(modules[0]);modules[1]._probe_option(10,33);assert.deepEqual(snapshot(modules[0]),saved);reset();
const allocations=modules.map(m=>m._malloc(40n*1024n*1024n));assert.ok(allocations.every(Boolean));input([99,111,10]);textCall('hooked','#',1);input([10]);textCall('wait',null);modules.forEach((m,i)=>m._free(allocations[i]));state();
console.log(`GETLINE: ${comparisons} ${referenceLabel}/pure-JS input, completion, prompt-state, history, wait and callback-trace comparisons checked.`);
