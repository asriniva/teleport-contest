import {DataView,assertStackRestored,memoryCheckpoint,assertMemoryGrowth,referenceBackend,referenceLabel} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/sfstruct-reference.mjs';
import hybridFactory from '../.cache/tu-probes/sfstruct-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
import * as sfstruct from '../js/ported/sfstruct.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.sfstruct,runtime=createPortedRuntime(layouts);
const modules=[await referenceBackend('sfstruct',emscriptenReferenceFactory)(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function bytes(m,p,n){return Array.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
function snapshot(m){return {sticky:Array.from({length:5},(_,i)=>Number(BigInt.asIntN(64,m._probe_state(0,i)))),buffered:Array.from({length:5},(_,i)=>Number(m._probe_state(1,i))),files:Array.from({length:5},(_,i)=>!!m._probe_state(2,i)),flags:m._probe_flags_value(),eof:m._probe_eof(),panic:m._probe_panic_code(),trace:text(m,m._probe_trace())};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(name,...args){if(name==='seek')args[1]=BigInt(args[1]);const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],name+':'+args);comparisons++;check();return values[0];}
const reset=()=>call('reset'),opt=(k,v)=>call('option',k,v),open=(slot=0,mode=0)=>call('open',slot,mode),fill=n=>call('fill',n),flags=(f=0,b=0,r=0,h=0,e=0)=>call('flags',f,b,r,h,e),io=(op,slot=0,count=0)=>call('io',op,slot,count),serial=(input,index,slot=0,count=0,table=0)=>call('serial',input,index,slot,count,table),trace=()=>text(modules[0],modules[0]._probe_trace());
function compareData(n=256){assert.deepEqual(bytes(modules[1],modules[1]._probe_buffer(),n),bytes(modules[0],modules[0]._probe_buffer(),n));comparisons++;}
function saved(slot=0){const counts=modules.map(m=>m._probe_read_file(slot));assert.equal(counts[1],counts[0]);const a=modules.map((m,i)=>bytes(m,m._probe_saved(),counts[i]));assert.deepEqual(a[1],a[0]);comparisons++;return a[0];}
const src=readFileSync(new URL('../.cache/wasm64-build/tree/src/sfstruct.c',import.meta.url),'utf8'),macros=readFileSync(new URL('../.cache/wasm64-build/tree/include/sfmacros.h',import.meta.url),'utf8');
const initializer=src.slice(src.indexOf('struct sf_structlevel_procs historical_sfo_procs'),src.indexOf('struct sf_structlevel_procs historical_sfi_procs'));
const order=[...initializer.matchAll(/historical_sfo_(\w+)/g)].map(m=>m[1]).filter(n=>n!=='procs'),complex=new Set([...macros.matchAll(/^SF_C\(\w+,\s*(\w+)\)/gm)].map(m=>m[1]));complex.add('version_info');
assert.equal(order.length,68);assert.equal(Object.keys(sfstruct.historical_sfo_procs.fn).length,68);assert.equal(Object.keys(sfstruct.historical_sfi_procs.fn).length,68);
for(const input of [0,1]){const table=input?sfstruct.historical_sfi_procs:sfstruct.historical_sfo_procs;assert.equal(table.ext,'');for(const [i,fn]of Object.values(table.fn).entries())assert.equal(fn.name,(input?'historical_sfi_':'historical_sfo_')+order[i]);}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=text(m,m._probe_layout_name(i));assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),L[key],key);}
assert.equal(L.MAXFD,5);assert.equal(L.pointerSize,8);assert.equal(L.nhf_eof>=0,true);
for(const m of modules){const at=Number(m._probe_restore());assert.equal(text(m,new DataView(m.HEAPU8.buffer).getBigUint64(at+L.restore_name,true)),'externalcomp');for(let i=0;i<68;i++)for(const input of [0,1])assert.notEqual(m._probe_proc(input,i),0n);}
// Every native function boundary is tested directly and through its real C table.
for(const [index,type]of order.entries())for(const input of [0,1])for(const table of [0,1]){
 reset();open();fill(17+index);opt(8,0x5a);const size=type==='char'?19:L['type_'+type+'_size'];assert.ok(Number.isSafeInteger(size)&&size>0&&size<65536,type);
 const original=bytes(modules[0],modules[0]._probe_buffer(),size+16),expected=original.slice(0,size);if(complex.has(type))expected[0]^=0x5a;
 if(input){call('seed_file',0,size);fill(165);flags(1,0,0,0,1);}
 const stable=modules.map(m=>m._probe_proc(input,index));assert.equal(serial(input,index,0,type==='char'?19:77,table),0n);
 if(input){compareData(size+16);assert.deepEqual(bytes(modules[0],modules[0]._probe_buffer(),size),expected);assert.equal(modules[0]._probe_eof(),1);assert.equal(modules[0]._probe_flags_value(),1);}
 else{assert.deepEqual(saved(),expected);compareData(size+16);assert.deepEqual(bytes(modules[0],modules[0]._probe_buffer(),size),expected);}
 assert.equal(trace().includes('norm:'+type+';'),complex.has(type));modules.forEach((m,i)=>assert.equal(m._probe_proc(input,index),stable[i]));
}
// SF_X bitfield ignores bflen; char honors cnt and has no prior-eof guard.
for(const type of ['char','bitfield'])for(const count of [0,1,2,31])for(const input of [0,1]){reset();open();fill(23);if(input){call('seed_file',0,64);fill(165);flags(1);}const index=order.indexOf(type);serial(input,index,0,count,1);if(!input)assert.equal(saved().length,type==='char'?count:1);compareData(96);}
// Full and short reads preserve untouched destination bytes and EOF semantics.
for(const index of [order.indexOf('int'),order.indexOf('genericptr_t'),order.indexOf('char'),order.indexOf('mkroom')])for(const available of [0,1,3]){
 reset();open();fill(51);const source=bytes(modules[0],modules[0]._probe_buffer(),available);call('seed_file',0,available);fill(165);flags(1);serial(1,index,0,8,0);compareData(128);assert.equal(modules[0]._probe_flags_value(),-1);assert.equal(modules[0]._probe_eof(),1);assert.deepEqual(bytes(modules[0],modules[0]._probe_buffer(),available),source);}
// The actual five descriptor slots and original unknown-close registration quirk.
reset();for(let i=0;i<6;i++){open(i);fill(i);io(5,i,3);}assert.deepEqual(snapshot(modules[0]).sticky,Array.from({length:5},(_,i)=>modules[0]._probe_fd(i)));assert.ok(trace().includes('impossible:fd not in list'));assert.equal(saved(5).length,0);
reset();open();assert.equal(io(0),0n);io(3);assert.equal(io(0),1n);assert.ok(!trace().includes('close:'));io(3);assert.ok(trace().includes('close:0;'));assert.equal(io(0),0n);
reset();open();io(4);assert.equal(io(0),1n);io(3);
// Buffered/unbuffered toggles reuse the FILE and preserve actual file bytes.
reset();open();fill(9);const first=bytes(modules[0],modules[0]._probe_buffer(),10);io(1);const files=modules.map(m=>m._probe_state(2,0));io(5,0,10);io(2);fill(7);const second=bytes(modules[0],modules[0]._probe_buffer(),7);io(5,0,7);io(1);modules.forEach((m,i)=>assert.equal(m._probe_state(2,0),files[i]));io(5,0,7);io(4);assert.deepEqual(saved(),first.concat(second,second));io(3);assert.deepEqual(snapshot(modules[0]).sticky,[-1,-1,-1,-1,-1]);assert.ok(trace().includes('fclose:0;'));
// Source diagnostics and panic/termination paths keep native formatting and scope.
for(const which of ['double','fdopen','flush','write','fwrite','hangup']){
 reset();open();if(which==='double'){io(1);io(1);}else if(which==='fdopen'){opt(5,1);io(1);}else if(which==='flush'){io(1);opt(7,1);io(4);opt(7,0);}else if(which==='fwrite'){io(1);opt(6,1);io(5,0,9);}else{opt(3,1);if(which==='hangup')flags(0,0,0,1);io(5,0,9);}assert.equal(modules[0]._probe_panic_code(),which==='hangup'?2:1);assert.ok(trace().includes(which==='hangup'?'terminate:':'panic:'));}
for(const mode of ['ordinary','bones','return','restore']){reset();open();fill(5);call('seed_file',0,1);fill(165);flags(mode==='return'?1:0,mode==='bones'?1:0,mode==='restore'?1:0);io(6,0,8);compareData(16);if(mode==='bones'||mode==='return'){assert.equal(modules[0]._probe_flags_value(),-1);assert.equal(modules[0]._probe_panic_code(),0);}else{assert.equal(modules[0]._probe_panic_code(),mode==='restore'?3:1);assert.ok(trace().includes('display:17:1;'));if(mode==='restore')assert.ok(trace().includes('nhclose:0;delete-save;error:Error restoring old game.;'));}}
// A read returning -1 takes the unsigned32 conversion before signed diagnostic.
reset();open();opt(1,1);flags(1);io(6,0,4);assert.equal(modules[0]._probe_flags_value(),-1);compareData(16);
reset();open();io(5,0,0);assert.equal(io(0),1n);assert.ok(!trace().includes('write:'));io(8);
// Real external callbacks can reenter source and grow native/Wasm allocation.
for(const stage of [1,2,3,4,5,6,7,8]){
 reset();open();fill(27);opt(20,stage);opt(21,stage);const before=modules.map(memoryCheckpoint);
 if(stage===1){call('seed_file',0,8);flags(1);io(6,0,8);}else if(stage===2)io(5,0,8);else if(stage===3)io(1);else if(stage===4){io(1);io(5,0,8);}else if(stage===5){io(1);io(4);}else if(stage===6){io(1);io(3);}else if(stage===7){io(5,0,0);io(3);}else serial(0,order.indexOf('mkroom'),0,0,1);
 assert.ok(trace().includes(`grow:${stage};`));assert.ok(trace().includes('nested:'));modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));compareData(128);
}
reset();open();fill(13);opt(22,1);opt(23,1);io(6,0,9);assert.equal(modules[0]._probe_flags_value(),-1);assert.equal(modules[0]._probe_panic_code(),0);
reset();open();fill(1);for(let i=0;i<100;i++){io(1);io(5,0,2);io(2);}io(3);
// Actual JS execution in another Module shares no descriptor tracking or tables.
reset();open();io(5,0,3);const savedPrimary=modules.map(snapshot),other=await hybridFactory({nethackPorted:runtime});other._probe_reset();other._probe_open(0,0);other._probe_io(1,0,0);assert.equal(other._probe_state(1,0),1n);modules.forEach((m,i)=>assert.deepEqual(snapshot(m),savedPrimary[i]));check();
console.log(`SFSTRUCT: ${comparisons} ${referenceLabel}/hybrid serializers, native bytes, IO state, errors and callback comparisons checked.`);
