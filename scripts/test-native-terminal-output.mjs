// Actual production termcap ownership, callback routing and dependency state.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {callTermcap} from '../js/nethack/bindings/termcap.js';
import {createLibraryBindings} from '../js/c-runtime/library-bindings.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const {environment:e}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const local=e.start('termcap').environment,native=local.nativeTputs;
let output=[],entries=0,checks=0;
const call=e.call;e.call=(module,name,...args)=>{if(module==='termcap'&&name==='xputc')entries++;return call(module,name,...args);};
local.putchar=byte=>{output.push(byte);return byte;};
const run=(text,direct,pointer)=>{
 local.nativeTputs=direct?native:undefined;output=[];entries=0;
 e.call('termcap','xputs',pointer?e.services.literal(text):text);
 return {bytes:[...output],entries};
};
// Prepare the binding while the native capability is present.
run('',true,false);
const cases=['','plain\n\r\t\x1b[0m',Array.from({length:255},(_,i)=>String.fromCharCode(i+1)).join(''),'abc\0ignored','a$<1>b$<2.5*>c$<3/>d','$<1.2.3>$$<1>tail'];
for(const text of cases)for(const pointer of [false,true]){
 const legacy=run(text,false,pointer),direct=run(text,true,pointer);
 assert.deepEqual(direct.bytes,legacy.bytes);assert.equal(direct.entries,0);
 assert.equal(legacy.entries,legacy.bytes.length);checks+=3;
}
local.nativeTputs=native;
assert.throws(()=>e.call('termcap','xputs','ok\0\u0100'),/explicit UTF-8/);checks++;
// Replacing tputs on the primary owner must remain visible.
const originalTputs=local.tputs;let supplied;
local.tputs=(text,lines,callback)=>{supplied=[text,lines,callback];return 19;};
e.call('termcap','xputs',e.services.literal('override'));
assert.equal(supplied[1],1);assert.equal(typeof supplied[2],'bigint');checks+=2;
local.tputs=originalTputs;
// Foreign scoped provider inheriting the native capability stays on compatibility.
const foreign=Object.create(local);foreign.tputs=(text,lines,callback)=>{supplied=[text,lines,callback];throw Error('foreign provider');};
assert.throws(()=>callTermcap(foreign,layouts.termcap,'xputs',e.services.literal('foreign')),/foreign provider/);
assert.equal(typeof supplied[2],'bigint');checks+=2;
assert.deepEqual(run('restored',true,false),{bytes:[114,101,115,116,111,114,101,100],entries:0});checks++;
// Synchronous nesting and exceptions must restore providers and real stack cursors.
let nested=false;output=[];const position=e.transport.stackPosition();
local.putchar=byte=>{output.push(byte);if(!nested){nested=true;assert.throws(()=>callTermcap(foreign,layouts.termcap,'xputs',e.services.literal('nested')),/foreign provider/);e.call('termcap','xputs','!');}return byte;};
e.call('termcap','xputs','ab');assert.deepEqual(output,[97,33,98]);assert.equal(e.transport.stackPosition(),position);checks+=2;
local.putchar=()=>{throw Error('sink failure');};
assert.throws(()=>e.call('termcap','xputs','x'),/sink failure/);assert.equal(e.transport.stackPosition(),position);checks+=2;
local.putchar=byte=>{output.push(byte);return byte;};
assert.deepEqual(run('ok',true,false).bytes,[111,107]);checks++;
// A foreign provider must also be safe when it creates the cached environment.
const {environment:cold}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const coldLocal=cold.start('termcap').environment,coldForeign=Object.create(coldLocal);
let foreignCalls=0,coldEntries=0,coldBytes=[];
coldForeign.tputs=()=>{foreignCalls++;return 0;};
callTermcap(coldForeign,layouts.termcap,'xputs',cold.services.literal('cold foreign'));
assert.equal(foreignCalls,1);checks++;
const coldCall=cold.call;cold.call=(module,name,...args)=>{if(module==='termcap'&&name==='xputc')coldEntries++;return coldCall(module,name,...args);};
coldLocal.putchar=byte=>{coldBytes.push(byte);return byte;};
cold.call('termcap','xputs','cold native');
assert.deepEqual(coldBytes,[99,111,108,100,32,110,97,116,105,118,101]);assert.equal(coldEntries,0);checks+=2;
// Stack character arrays have an address but need not coerce to a number.
// Background color is an actual source path through such a temporary view.
for(const color of [-9,-1,0,1,4,7,8,15,2**32+4]){
 output=[];entries=0;e.call('termcap','term_start_bgcolor',color);
 const narrowed=color|0,expected='\x1b['+((narrowed%8)+40)+'m';
 assert.deepEqual(output,[...expected].map(c=>c.charCodeAt(0)));assert.equal(entries,0);checks+=2;
}
// Library API uses the same parser/counters for pointer and direct callback modes.
const runtime=createLibraryBindings(),services=e.services;
for(const text of cases){
 const a=[],b=[];const id=e.functions.functionPointer(byte=>{a.push(byte);return byte;},'ii');
 runtime.tputs(services,e.services.literal(text),3,id);
 runtime.tputsNative(services,text,3,byte=>{b.push(byte);return byte;});
 assert.deepEqual(a,b);checks++;
}
const carrierBytes=[];runtime.tputsNative(services,{address:e.services.literal('carrier')},1,b=>{carrierBytes.push(b);return b;});assert.deepEqual(carrierBytes,[99,97,114,114,105,101,114]);checks++;
console.log(JSON.stringify({passed:true,checks,scope:'Production termcap native bytes, every nonzero byte, NUL, padding, pointer/string input, zero per-byte binding entries, primary/foreign provider overrides, nested error restoration and stack cursor preservation. Full recording equivalence is separate.'}));
