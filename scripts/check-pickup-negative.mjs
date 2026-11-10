// Deliberately wrong unique JS variants; original C, Wasm and test stay fixed.
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync,mkdirSync} from 'node:fs';
import {spawnSync} from 'node:child_process';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {createHash} from 'node:crypto';
const root=fileURLToPath(new URL('../',import.meta.url)),work=root+'.cache/pickup-first-pass/negative/';mkdirSync(work,{recursive:true});
const hash=p=>createHash('sha256').update(readFileSync(p)).digest('hex');
const pinned=['.cache/wasm64-build/tree/src/pickup.c','.cache/pickup-first-pass/pickup-reference.wasm','.cache/pickup-first-pass/pickup-hybrid.wasm','scripts/test-tu-pickup.mjs'].map(p=>[p,hash(root+p)]);
const core=readFileSync(root+'js/ported/pickup.js','utf8'),runtime=readFileSync(root+'js/ported/pickup-runtime.js','utf8');
const start=core.indexOf('export function allow_all('),end=core.indexOf('\n}',start);assert.ok(start>=0&&end>start);const wrong=core.slice(0,start)+core.slice(start,end).replace('return (C.i8(1))','return (C.i8(0))')+core.slice(end);assert.notEqual(wrong,core,'wrong source edit applied');
const oldPromotion=core.replace('(wt=C.i32(C.i64(wt)-','(wt=C.i32(wt-');assert.notEqual(oldPromotion,core);
const stale=runtime.slice(0,runtime.indexOf('export function callPickup('))+`export function callPickup(services,name,...args){
 let state=states.get(services.moduleKey);if(!state){state={env:createPickupEnvironment(services)};states.set(services.moduleKey,state);}Object.setPrototypeOf(state.env,services);
 const fn=pickup[name],stackFrame=services.stackSave();try{return withCEnvironment(state.env,fn,...args)??0;}finally{services.stackRestore(stackFrame);}
}\n`;
for(const [mode,source,adapter]of[['wrong-source',wrong,runtime],['stale-service-lifetime',core,stale],['old-compound-promotion',oldPromotion,runtime]]){
 const dir=work+mode+'/';mkdirSync(dir,{recursive:true});writeFileSync(dir+'pickup.mjs',source.replace("'./c-runtime.js'",JSON.stringify(pathToFileURL(root+'js/ported/c-runtime.js').href)));
 writeFileSync(dir+'pickup-runtime.mjs',adapter.replace("'./pickup.js'","'./pickup.mjs'").replace("'./c-runtime.js'",JSON.stringify(pathToFileURL(root+'js/ported/c-runtime.js').href)));
 const p=spawnSync(process.execPath,[root+'scripts/test-tu-pickup.mjs'],{cwd:root,env:{...process.env,PICKUP_RUNTIME:pathToFileURL(dir+'pickup-runtime.mjs').href},encoding:'utf8',maxBuffer:16*1024*1024});writeFileSync(dir+'result.log',p.stdout+p.stderr);assert.notEqual(p.status,0,mode+' must fail');assert.match(p.stdout+p.stderr,/AssertionError/,mode+' actual comparison assertion');
 if(mode==='old-compound-promotion'){assert.match(p.stdout+p.stderr,/Cannot mix BigInt/);assert.match(p.stdout+p.stderr,/carry_count/);assert.match(p.stdout+p.stderr,/pickup stack cleanup/);}
 for(const [path,sha]of pinned)assert.equal(hash(root+path),sha,'unchanged oracle/input '+path);console.log('PASS PICKUP actual AssertionError negative:',mode,'original C/Wasm/test unchanged');
}
