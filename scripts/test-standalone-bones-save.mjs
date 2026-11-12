// Focused direct original savebones after genuine startup; eligibility is not tested here.
import assert from 'node:assert/strict';import fs from 'node:fs';import crypto from 'node:crypto';
import{runFullOriginalC}from'./full-original-c-run.mjs';import{runStandaloneProgram}from'./run-standalone-program.mjs';
import{C,R,T}from'../js/ported/c-runtime.js';
import{worldGraph}from'./restoration-world-graph.mjs';
const directory='.cache/full-original-c-v1',layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),abi=JSON.parse(fs.readFileSync('js/standalone/bones-services-abi.json')),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const[p,h]of Object.entries(abi.sourceSha256))assert.equal(sha(p),h,p);
let cr,jr;const input={keys:'  n',options:'OPTIONS=!news\n',timezone:'UTC'},c=await runFullOriginalC(directory,{...input,observeRuntime:r=>cr=r}),j=runStandaloneProgram(directory+'/assets',{...input,observeRuntime:r=>jr=r});
assert.equal(j.status.kind,'input-exhausted',JSON.stringify(j.status));assert.equal(c.status.kind,'input-exhausted');assert.deepEqual(j.state,c.state,'genuine startup source state');
function js(fn){const names=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=names.map(k=>Object.getOwnPropertyDescriptor(globalThis,k)),bad=()=>{throw new Error('Forbidden BONES production capability');};for(const k of names)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:bad}):bad});try{return fn();}finally{names.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);}}
const savedTZ=process.env.TZ;process.env.TZ='UTC';try{
 const env=jr.environment,ref=cr.module;
 js(()=>env.resolve('savebones')(layouts.end.STARVING,0n,0));ref._savebones(layouts.end.STARVING,0n,0n);
 const text=(side,name)=>side==='js'?Buffer.from(env.filesystem.readFile(name)).toString():new TextDecoder().decode(ref.FS.readFile(name));
 assert.equal(text('js','/rng.log'),text('c','/rng.log'),'all actual startup and source savebones RNG sites/draws');
 assert.deepEqual(worldGraph(jr),worldGraph(cr),'actual post-save named world graph including ghost and cemetery');
 const files=env.filesystem.exportSnapshot().entries.filter(r=>r.type==='file'&&/\/bon[^/]*$/.test(r.path));assert.equal(files.length,1,'real compressed bones file');
 const native=ref.FS.readFile(files[0].path),actual=Buffer.from(files[0].base64,'base64');assert.deepEqual([...actual.subarray(0,2)],[31,157]);assert.deepEqual([...native.subarray(0,2)],[31,157]);
 const evidence={focusedSourceSave:true,ordinaryDeathAccepted:false,binaryBonesAccepted:false,path:files[0].path,bytes:{c:native.length,js:actual.length},limitation:'Direct original savebones after real D1 startup, bypassing caller eligibility only in this focused test. Real deeper ordinary death and semantic bones producer/consumer proof remain required.'};fs.mkdirSync('.cache/standalone-bones-save',{recursive:true});fs.writeFileSync('.cache/standalone-bones-save/evidence.json',JSON.stringify(evidence,null,2));console.log('PASS '+JSON.stringify(evidence));
}finally{if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
