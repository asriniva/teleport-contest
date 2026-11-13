import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';import fs from 'node:fs';
import {createReference} from './pure-js-fixtures/load.mjs';
import createCalendar from './pure-js-probes/calendar.mjs';
import {withCEnvironment,C,R,T} from '../js/c-runtime/context.js';
import {time_from_yyyymmddhhmmss} from '../js/ported/calendar.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
// Both runtimes must start in the same explicit zone. The isolated C worker
// otherwise inherits the host zone while a bare standalone instance uses UTC.
process.env.TZ='UTC';
const modules=[await createReference('calendar'),await createCalendar(layouts)];let comparisons=0;
function allocate(m,value){const data=Buffer.from(value+'\0'),p=m._malloc(BigInt(data.length));m.HEAPU8.set(data,Number(p));return p;}
function set(name,value){for(const m of modules){const key=allocate(m,name),p=value===null?0n:allocate(m,value);assert.equal(m._probe_set_env(BigInt(key),BigInt(p)),0);m._free(key);if(p)m._free(p);}}
const stacks=modules.map(m=>m._probe_stack());
for(const year of Array.from({length:19},(_,i)=>2000+i))for(const suffix of ['0101000000','0331120000','0731235959','1231120000']){
 set('NETHACK_FIXED_DATETIME',year+suffix);
 const values=modules.map(m=>m._probe_moon());assert.equal(values[1],values[0],'moon '+year+suffix);assert.ok(values[0]>=0&&values[0]<=7);comparisons++;
}
// The special epact25/metonic17 case is included as2011.
assert.ok(Array.from({length:19},(_,i)=>2000+i).some(year=>{const g=(year-1900)%19+1;return (11*g+18)%30===25&&g>11;}));
set('NETHACK_FIXED_DATETIME',null);
for(const epoch of ['',null,'0','1777723200']){
 set('NETHACK_RECORDING_EPOCH',epoch);
 const values=modules.map(m=>{const p=allocate(m,'20300102030405');try{return m._probe_parse(BigInt(p));}finally{m._free(p);}});
 assert.equal(values[1],values[0],'parse epoch '+JSON.stringify(epoch));comparisons++;
}
assert.deepEqual(modules.map(m=>m._probe_stack()),stacks);
// A localtime failure is a controlled JS provider failure; avoid claiming
// native libc will return null for this ordinary timestamp.
const heap=new Uint8Array(256);heap.set(Buffer.from('20300102030405\0'),1);let next=64;const events=[];
assert.equal(withCEnvironment({HEAP8:new Int8Array(heap.buffer),HEAPU8:heap,stackAlloc:n=>{const p=next;next+=n;return p;},strlen:()=>14,time:()=>0n,nh_getenv:()=>0,localtime:timestamp=>{events.push(timestamp);return null;},tmCopy:()=>assert.fail('null localtime must not copy'),mktime:()=>assert.fail('null localtime must not convert')},()=>time_from_yyyymmddhhmmss(1)),0n);
assert.deepEqual(events,[0n]);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);assert.equal(comparisons,80);
// The isolated reference profile has no recording-clock parser patch, and its
// standalone fixture intentionally hides that variable too. Cover the ported
// parser's inherited clock adaptation as an explicit dependency contract.
for(const epoch of ['', '1777723200']){
 heap.set(Buffer.from(epoch+'\0'),32);next=64;const events=[];
 const value=withCEnvironment({HEAP8:new Int8Array(heap.buffer),HEAPU8:heap,stackAlloc:n=>{const p=next;next+=n;return p;},strlen:()=>14,time:()=>9n,nh_getenv:name=>{assert.equal(name,'NETHACK_RECORDING_EPOCH');return 32;},strtoll:(p,end,base)=>{assert.deepEqual([p,end,base],[32,0,10]);events.push('epoch');return 1777723200n;},localtime:timestamp=>{events.push(timestamp);return{tm_isdst:1};},tmCopy:tm=>({...tm}),atoi:p=>{let end=p;while(heap[end])end++;return Number(Buffer.from(heap.slice(p,end)).toString());},mktime:tm=>{assert.deepEqual(tm,{tm_isdst:1,tm_year:130,tm_mon:0,tm_mday:2,tm_hour:3,tm_min:4,tm_sec:5});events.push('mktime');return 123n;}},()=>time_from_yyyymmddhhmmss(1));
 assert.equal(value,123n);assert.deepEqual(events,epoch?['epoch',1777723200n,'mktime']:[9n,'mktime']);
}
console.log('PASS:80 original-C/pure-JS calendar cases across a complete Metonic cycle and fixture epochs;3 explicit localtime/recording-clock provider contracts.');
