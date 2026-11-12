import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
import crypto from 'node:crypto';
import * as candidate from '../js/c-runtime/adapter-factories.js';
const baseCommit='32d7615adb8338891bc29c0f73638fbee3bab830',source=execFileSync('git',['show',baseCommit+':js/c-runtime/adapter-factories.js']);
let baselineSource=source.toString();
for(const name of ['adapter-memory.js','records.js'])baselineSource=baselineSource.replace("'./"+name+"'",JSON.stringify(new URL('../js/c-runtime/'+name,import.meta.url).href));
const baseline=await import('data:text/javascript;base64,'+Buffer.from(baselineSource).toString('base64'));
const sha=b=>crypto.createHash('sha256').update(b).digest('hex');
const sources={baseCommit,baselineFactorySha256:sha(source),candidateFactorySha256:sha(fs.readFileSync(new URL('../js/c-runtime/adapter-factories.js',import.meta.url)))};
let checks=0;
const outcome=fn=>{try{return{value:fn()};}catch(e){return{errorType:e.constructor.name,message:e.message,code:e.code};}};
const values=[0,-0,1,-1,127,128,255,256,32767,32768,65535,65536,2**31,2**32,2**53-1,2**53,Number.MAX_VALUE,-Number.MAX_VALUE,Number.MIN_VALUE,NaN,Infinity,-Infinity,1.5,-1.5,0n,255n,2n**100n,'17','1.0',true,null,undefined];
for(let exponent=-1074;exponent<=1023;exponent+=11)for(const v of [2**exponent,-(2**exponent),1.5*(2**exponent)])values.push(v);
const scenarios=[
  (trace,value)=>({d:{get p(){trace.push('p');return undefined;},get s(){trace.push('s');return false;},get a(){trace.push('a');return false;},get f(){trace.push('f');return false;},get t(){trace.push('t');return 'i8';}},v:value}),
  (trace,value)=>{let reads=0;return{d:{get t(){trace.push('t '+(++reads));return reads===1?'i8':'u32';}},v:value};},
  (trace,value)=>{let reads=0;return{d:{get t(){trace.push('t '+(++reads));return reads===1?{slice(i){trace.push('slice '+i);return{[Symbol.toPrimitive](hint){trace.push('bits '+hint);return 16;}};}}:{get 0(){trace.push('sign');return 'i';}};}},v:value};},
  trace=>({d:{get t(){trace.push('t');throw Object.assign(new TypeError('descriptor getter failed'),{code:'DESC'});}},v:1}),
  trace=>({d:{t:'i8'},v:{[Symbol.toPrimitive](hint){trace.push('value '+hint);return 255;}}}),
  trace=>({d:{t:'i8'},v:{[Symbol.toPrimitive](hint){trace.push('value '+hint);return 1.5;}}}),
  trace=>{const d={get t(){trace.push('t');return'i8';}};return{d,v:{[Symbol.toPrimitive](hint){trace.push('value '+hint);Object.defineProperty(d,'t',{value:'u32',configurable:true});return 255;}}};},
  trace=>({d:{t:'i32'},v:{get [Symbol.toPrimitive](){trace.push('get @@toPrimitive');throw Object.assign(new RangeError('value getter failed'),{code:'VALUE'});}}}),
  trace=>({d:{t:'u32'},v:new Proxy({valueOf(){trace.push('call valueOf');return 17;}},{get(o,k,r){trace.push('get '+String(k));return Reflect.get(o,k,r);}})}),
  (trace,value)=>({d:{get p(){trace.push('p');return 0;},get t(){throw Error('pointer precedence lost');}},v:value}),
  (trace,value)=>({d:{get p(){trace.push('p');return'record';},get t(){throw Error('pointer precedence lost');}},v:value}),
  (trace,value)=>({d:{get s(){trace.push('s');return'record';},get t(){throw Error('record precedence lost');}},v:value}),
  (trace,value)=>({d:{get f(){trace.push('f');return true;},get t(){throw Error('callback precedence lost');}},v:value}),
  (trace,value)=>({d:{get a(){trace.push('a');return[1];},get e(){trace.push('e');return{t:'i8'};},get t(){trace.push('t');return undefined;}},v:value}),
  (trace,value)=>({d:{get q(){trace.push('q');return{t:'i8'};},get t(){trace.push('t');return'i8';}},v:value}),
];
function run(library,scenario,value,pointerArrays) {
  const trace=[],pair=scenario(trace,value),v=pair.v,env=library.createDescriptorMemory({services:{},layout:{recordSize:8},addr:x=>{trace.push('addr');return Number(x);},raw:BigInt,memory:()=>new DataView(new ArrayBuffer(128)),cache:new Map(),view:(name,x)=>{trace.push('view '+name+' '+(x===v));return{view:name,original:x===v};},pointerArrays,decodeCallback:x=>{trace.push('callback '+(x===v));return'callback-result';}});
  const result=outcome(()=>{const r=env.decode(pair.d,v);if(r&&typeof r==='object')return{address:r.address,byteLength:r.byteLength,view:r.view,original:r.original};return r;});return{trace,result};
}
assert.equal(run(baseline,scenarios[6],0,false).result.value,-1,'Descriptor sign is selected before a value hook mutates its type');
assert.equal(run(candidate,scenarios[6],0,false).result.value,-1);checks+=2;
for(const pointerArrays of [false,true])for(const scenario of scenarios)for(const value of values) {
  assert.deepEqual(run(candidate,scenario,value,pointerArrays),run(baseline,scenario,value,pointerArrays),'descriptor getter/value trace');checks++;
}
// Explicitly retain all5 profiles' finite fractional truncation and enum rules.
const profiles=['signed-enum','cached-fields','declared-enum','address-cells','abi-globals'];
for(const profile of profiles)for(const signed of [0,1]) {
  const layout={'enumSigned:test':signed},schema={schema:{},globals:[]},services={heap:()=>new Uint8Array(128)},options={profile,errors:['scalar ','cell ','field '],address:Number,fieldMetadata:new Map()};
  const b=baseline.createScalarAdapter(services,layout,schema,Number,options),c=candidate.createScalarAdapter(services,layout,schema,Number,options);
  for(const sign of ['i','u'])for(const bits of [8,16,32,64])for(const value of values){assert.deepEqual(outcome(()=>c.env[sign+bits](value)),outcome(()=>b.env[sign+bits](value)));checks++;}
  for(const value of values){assert.deepEqual(outcome(()=>c.decode('enum test',value)),outcome(()=>b.decode('enum test',value)));checks++;}
}
// Numeric optimization assumes standard intrinsics. Overwriting global BigInt
// makes eliminating any BigInt call intentionally observable to that hook.
const builtin=BigInt,hookTrace=[];let monkeypatchCounterexample;
try {
  const hooked=v=>{hookTrace.push('BigInt');return builtin(v);};hooked.asIntN=builtin.asIntN;hooked.asUintN=builtin.asUintN;globalThis.BigInt=hooked;
  const make=lib=>lib.createDescriptorMemory({services:{},layout:{},addr:Number,raw:hooked,memory:()=>new DataView(new ArrayBuffer(64)),cache:new Map(),view:()=>0});
  hookTrace.length=0;const bv=make(baseline).decode({t:'i32'},17),bt=[...hookTrace];hookTrace.length=0;const cv=make(candidate).decode({t:'i32'},17),ct=[...hookTrace];
  assert.equal(bv,cv);assert.notDeepEqual(bt,ct);monkeypatchCounterexample={sameNumericResult:true,baselineTrace:bt,candidateTrace:ct};
}finally{globalThis.BigInt=builtin;}
const result={...sources,node:process.version,checks,ordinaryIntrinsicCounterexamples:0,monkeypatchCounterexample,scope:'Actual candidate vs pinned baseline synthetic descriptor getter/value coercion, huge Number, fractional profile and enum tests. Assumes ordinary JS intrinsics. This script supplies no native/recorder acceptance.'};
fs.writeFileSync(new URL('../.cache/numeric-guards-coercion-results.json',import.meta.url),JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(result,null,2));
