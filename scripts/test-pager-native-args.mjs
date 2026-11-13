// Exercise the actual private converters from predecessor/current source bytes.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {execFileSync} from 'node:child_process';
import {setupMonsterData} from './monster-data-view-harness.mjs';
const base=process.env.PAGER_CALLBACK_BASE??'3b6db96',file='js/nethack/pager-lookup.js';
const before=execFileSync('git',['show',base+':'+file],{encoding:'utf8'}),after=fs.readFileSync(file,'utf8');
const x=setupMonsterData(),{env,views,mon,species}=x;
function converter(source){const match=source.match(/const nativeArg=([\s\S]*?);\n const locate=/);assert.ok(match);return Function('ctypes','transport','views','address','return '+match[1])(env.ctypes,env.transport,views,env.address);}
const a=converter(before),b=converter(after),metadata=JSON.parse(fs.readFileSync('js/nethack/pager-target-abi.json'));
const types=[...new Set([...Object.values(metadata.helperParameters).flat(),'struct monst *','struct permonst *','struct attack *','struct unknown *','unknown','const short','enum monnums'])];
const values=[0,1,-1,255,256,32768,2**32,1.5,NaN,Infinity,0n,-1n,2n**63n,mon.address,mon,{address:species[0].address},undefined,null];
let checks=0;const run=(fn,t,v)=>{try{return{value:fn(t,v)};}catch(e){return{error:e.name,message:e.message};}};
for(const grow of[false,true]){
 if(grow)assert.ok(env.memory.grow(env.memory.buffer.byteLength+1));
 for(const t of types)for(const v of values){assert.deepEqual(run(b,t,v),run(a,t,v),t+' '+String(v));checks++;}
}
// Explicit pointer/view identity and narrow unexpected-error propagation.
assert.equal(b('struct monst *',mon),views.record('struct monst',mon.address));checks++;
const arbitrary={address:123};assert.equal(b('char *',arbitrary),arbitrary);checks++;
const record=env.ctypes.record,isRecord=env.ctypes.isRecord;
env.ctypes.record=()=>{throw Error('unrelated metadata failure');};
env.ctypes.isRecord=()=>true;
assert.deepEqual(run(b,'struct monst *',mon),run(a,'struct monst *',mon));checks++;
env.ctypes.record=record;env.ctypes.isRecord=isRecord;
console.log(JSON.stringify({status:'PASS',checks,types:types.length,base,heapGrowth:true,actualSourceConverters:true}));
