import {execFileSync} from 'node:child_process';
const BASE='819d16fb5bcb59c96065a3519aa643a117cfc601';
let source=execFileSync('git',['show',BASE+':js/c-runtime/types.js'],{encoding:'utf8'});
source=source.replace("'./memory.js'",JSON.stringify(new URL('../js/c-runtime/memory.js',import.meta.url).href));
const {createCTypes:baseline}=await import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
import {createCTypes as candidate} from '../js/c-runtime/types.js';
import {CMemory} from '../js/c-runtime/heap.js';
import assert from 'node:assert/strict';
import fs from 'node:fs';
const memory=new CMemory({initialBytes:1024}),p=memory.malloc(32);memory.view.setInt32(p,12345,true);
const metadata={records:{record:{size:4,fields:{x:{offset:0}}}},enums:{'enum t':{size:4,signed:true}}},a=baseline(memory,metadata,{}),b=candidate(memory,metadata,{});
const outcome=fn=>{try{return{value:fn()};}catch(e){return{error:e.name,message:e.message};}};
let checks=0,sink=0;
for(const type of ['int','unsigned int','char','unsigned short','long','float','double','const int','int*','enum t','record','bad','__proto__','toString'])for(const at of [p,-1,0,p+1,999999,1.5,Infinity,1n]){assert.deepEqual(outcome(()=>a.load(type,at)),outcome(()=>b.load(type,at)));checks++;}
const results=[];
for(const type of ['int','unsigned int','char','unsigned short','float','double','enum t','int*']){
 const samples={baseline:[],candidate:[]};
 for(let trial=0;trial<7;trial++)for(const name of trial%2?['candidate','baseline']:['baseline','candidate']){const fn=name==='baseline'?a:b,start=process.cpuUsage();for(let i=0;i<300000;i++)sink^=Number(fn.load(type,p));const cpu=process.cpuUsage(start);samples[name].push((cpu.user+cpu.system)/1000);}
 const median=x=>[...x].sort((a,b)=>a-b)[3];results.push({type,samples,ratio:median(samples.candidate)/median(samples.baseline)});
}
fs.writeFileSync(new URL('../.cache/scalar-call-load-benchmark.json',import.meta.url),JSON.stringify({checks,results,sink,scope:'Production candidate vs immutable819d16f; synthetic load benchmark; no native/recorder acceptance.'},null,2)+'\n');console.log(JSON.stringify({checks,results:results.map(({type,ratio})=>({type,ratio})),sink}));
