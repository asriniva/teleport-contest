import {layoutSourceSha,currentLayoutPath} from './nethack-layout.mjs';
// Original MON assertion source sites against the pinned SDK abort implementation.
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(currentLayoutPath(p))).digest('hex'),abi=JSON.parse(fs.readFileSync('js/nethack/mon-abi.json')),directory='.cache/standalone-sdk-boundary-v5',receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));let checks=0;
for(const[p,h]of Object.entries(abi.sourceSha256))assert.equal(layoutSourceSha(p,h),h,p);
for(const[p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,p);
for(const[p,h]of Object.entries(receipt.artifactSha256))assert.equal(layoutSourceSha(directory+'/'+p,h),h,p);
const start=Object.fromEntries(Object.keys(abi.sourceSha256).map(p=>[p,sha(p)]));
const{createStandaloneProgram}=await import('../js/nethack/program.js'),{default:factory}=await import(pathToFileURL(process.cwd()+'/'+directory+'/reference.mjs')),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const pure=fn=>{const old=Object.getOwnPropertyDescriptor(globalThis,'WebAssembly');Object.defineProperty(globalThis,'WebAssembly',{configurable:true,value:new Proxy({},{get(){throw Error('Production Wasm forbidden');}})});try{return fn();}finally{Object.defineProperty(globalThis,'WebAssembly',old);}};
for(let i=0;i<abi.assertions.length;i++){
 const row=abi.assertions[i],errors=[],aborts=[],c=await factory({printErr:s=>errors.push(s),onAbort:s=>aborts.push(s)}),p=pure(()=>createStandaloneProgram({layouts,readKey(){throw Error('No gameplay input in assertion leaf test');}})),e=p.environment,owner=e.enableMonsterLifecycle(layouts);
 assert.ok(owner?.services,'existing canonical MON context');
 const before=p.stdio.captured(2).length;pure(()=>owner.services.assert(1,i));pure(()=>owner.services.assert(-1,i));assert.equal(p.stdio.captured(2).length,before,'successful native assertion emits nothing');checks++;
 const literal=s=>{const b=Buffer.from(s+'\0'),at=c._malloc(BigInt(b.length));c.HEAPU8.set(b,Number(at));return BigInt(at);};let a,b;
 try{c._sdk_assert(literal(row.expression),literal(row.file),row.line,literal(row.function));}catch(x){a=x;}
 try{pure(()=>owner.services.assert(0,i));}catch(x){b=x;}
 assert.ok(a&&b,'failed assertion stops');assert.equal(b.name,a.name);assert.equal(b.message,a.message,'source expression/file/line/function preserved');assert.equal(Buffer.from(p.stdio.captured(2)).toString(),errors.join('\n')+'\n','native SDK stderr');checks+=4;
}
assert.deepEqual(Object.fromEntries(Object.keys(start).map(p=>[p,sha(p)])),start,'source stable');
fs.mkdirSync('.cache/mon-assert',{recursive:true});fs.writeFileSync('.cache/mon-assert/evidence.json',JSON.stringify({checks,sites:abi.assertions,sourceSha256:start},null,2));console.log('PASS '+checks+' MON native assertion checks');
