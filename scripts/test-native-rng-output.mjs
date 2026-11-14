import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createNativeRngOutput,installNativeRngCaller,recordNativeRngCaller} from '../js/nethack/native/rng-output.js';
let checks=0;
function fixture(){const writes=[],e=createStandaloneEnvironment();const io=e.enableStdio({stdout:bytes=>writes.push([...bytes])}),s=e.services;
 const array=v=>v instanceof Uint8Array?String.fromCharCode(...v.subarray(0,v.indexOf(0)<0?v.length:v.indexOf(0))):v;
 const fprintf=(p,f,...a)=>s.fprintf(p,f,...a.map(array)),snprintf=(b,n,f,...a)=>{const value=e.libc.format(f,...a),bytes=Uint8Array.from(value.slice(0,Number(n)-1),c=>c.charCodeAt(0));b.set(bytes);b[bytes.length]=0;return value.length;};
 return {e,s,io,writes,fprintf,snprintf,native:createNativeRngOutput({memory:e.memory,stdio:s,libc:e.libc,ownedOutput:io,ownedFormat:e.libc.format,fprintf,snprintf})};}
const a=fixture(),b=fixture();
const shapes=[['%d %s(%s) = %d @ %s(%s:%d)\n',[1,'rn2',new Uint8Array([50,53,54,0]),17,'movemon','mon.c',400]],['%d %s(%s) = %d @ %s:%d\n',[1,'d','2,6',3,'mon.c',400]],['%d %s(%s) = %d\n',[1,'rnd','6',5]],['%d ~drn2(%d) = %d',[2,16,15]],[' @ %s(%s:%d)',['display','display.c',17]],[' @ %s:%d',['file',17]],['%x',[255]]];
const outcome=fn=>{try{return {value:fn()};}catch(error){return {error:error.constructor.name};}};
for(const [shape,args]of shapes){assert.deepEqual(outcome(()=>b.native.fprintf(b.io.stdout,shape,...args)),outcome(()=>a.fprintf(a.io.stdout,shape,...args)));a.io.fflush(a.io.stdout);b.io.fflush(b.io.stdout);assert.deepEqual(b.writes,a.writes);checks+=2;}
const integers=[0,-0,1,-1,2**31,2**32-1,2**32+123,2n**80n+7n,'17',true,1.5,NaN,undefined];
for(const value of integers)for(const length of [0,1,2,8,32,64])for(const capacity of [-1,0,1,2,5,32,64,1.5,NaN,Infinity])for(const shape of ['%d','%d,%d']){
 const x=new Uint8Array(length).fill(165),y=x.slice(),args=shape==='%d'?[value]:[value,-3];
 assert.deepEqual(outcome(()=>b.native.snprintf(y,capacity,shape,...args)),outcome(()=>a.snprintf(x,capacity,shape,...args)),shape+' capacity/coercion');assert.deepEqual(y,x,'exact argument bytes');checks+=2;
}
for(const value of ['','plain','a\0ignored','\xff','\u0100',0,0n,undefined]){
 const shape='%d %s(%s) = %d\n',args=[1,'rn2',value,17];assert.deepEqual(outcome(()=>b.native.fprintf(b.io.stdout,shape,...args)),outcome(()=>a.fprintf(a.io.stdout,shape,...args)));a.io.fflush(a.io.stdout);b.io.fflush(b.io.stdout);assert.deepEqual(b.writes,a.writes);checks+=2;
}
const longestA=new Uint8Array(64),longestB=new Uint8Array(64);assert.equal(b.native.snprintf(longestB,64,'%d,%d',-2147483648,-2147483648),a.snprintf(longestA,64,'%d,%d',-2147483648,-2147483648));assert.deepEqual(longestB,longestA);checks+=2;
const closedA=fixture(),closedB=fixture();closedA.io.fclose(closedA.io.stdout);closedB.io.fclose(closedB.io.stdout);assert.equal(closedB.native.fprintf(closedB.io.stdout,shapes[0][0],...shapes[0][1]),closedA.fprintf(closedA.io.stdout,shapes[0][0],...shapes[0][1]));checks++;
const pa=a.e.memory.cstring('live'),pb=b.e.memory.cstring('live');
for(const ch of [65,255,0]){a.e.memory.HEAPU8[pa]=ch;b.e.memory.HEAPU8[pb]=ch;const shape=' @ %s:%d';assert.equal(b.native.fprintf(b.io.stdout,shape,pb,17),a.fprintf(a.io.stdout,shape,pa,17));a.io.fflush(a.io.stdout);b.io.fflush(b.io.stdout);assert.deepEqual(b.writes,a.writes);checks+=2;}
let selected=0;const original=b.s.fprintf;b.s.fprintf=()=>{selected++;return 37;};assert.equal(b.native.fprintf(b.io.stdout,shapes[0][0],...shapes[0][1]),37);assert.equal(selected,1);b.s.fprintf=original;checks+=2;
// Replacements before installation and on the underlying FILE API also keep
// the original provider path, rather than merely matching a captured override.
let earlyCalls=0;const canonicalPrintf=b.io.fprintf,originalRootPrintf=b.s.fprintf;
b.s.fprintf=()=>{earlyCalls++;return 71;};
const early=createNativeRngOutput({memory:b.e.memory,stdio:b.s,libc:b.e.libc,ownedOutput:b.io,ownedFormat:b.e.libc.format,fprintf:b.fprintf,snprintf:b.snprintf});
assert.equal(early.fprintf(b.io.stdout,shapes[0][0],...shapes[0][1]),71);assert.equal(earlyCalls,1);b.s.fprintf=originalRootPrintf;checks+=2;
let sinkCalls=0;const originalSink=b.io.fputs;b.io.fputs=()=>{sinkCalls++;return 0;};
b.native.fprintf(b.io.stdout,shapes[0][0],...shapes[0][1]);assert.equal(sinkCalls,1);b.io.fputs=originalSink;checks++;
const canonicalFormat=b.e.libc.format;let formatCalls=0;b.e.libc.format=(...args)=>{formatCalls++;return canonicalFormat(...args);};
const changed=createNativeRngOutput({memory:b.e.memory,stdio:b.s,libc:b.e.libc,ownedOutput:b.io,ownedFormat:canonicalFormat,fprintf:b.fprintf,snprintf:b.snprintf});
changed.fprintf(b.io.stdout,shapes[0][0],...shapes[0][1]);assert.equal(formatCalls,1);b.e.libc.format=canonicalFormat;checks++;
const seen=[],services={literal:value=>{seen.push(['literal',value]);return 99;},rng_log_set_caller:(...args)=>seen.push(['legacy',...args])};
installNativeRngCaller(services,(...args)=>seen.push(['native',...args]));recordNativeRngCaller(services,'file',1,'function');assert.deepEqual(seen,[['native','file',1,'function']]);checks++;
seen.length=0;recordNativeRngCaller(services,'',1,'');assert.deepEqual(seen,[['literal',''],['literal',''],['native',99,1,99]]);checks++;
assert.throws(()=>recordNativeRngCaller(services,'file\0\u0100',1,'function'),/explicit UTF-8/);checks++;
const foreign=Object.create(services);seen.length=0;recordNativeRngCaller(foreign,'file',1,'function');assert.deepEqual(seen,[['literal','file'],['literal','function'],['legacy',99,1,99]]);checks++;
seen.length=0;services.rng_log_set_caller=(...args)=>seen.push(['override',...args]);recordNativeRngCaller(services,'file',1,'function');assert.deepEqual(seen,[['literal','file'],['literal','function'],['override',99,1,99]]);checks++;
console.log(JSON.stringify({passed:true,checks,scope:'All logger shapes versus existing formatter, signed narrowing/coercions, exact snprintf bytes/capacity errors, NUL/high bytes/live pointer mutation, identical FILE sink fragments, provider overrides, owned caller metadata and foreign fallback. Generator policy and recording equivalence are separate.'}));
