// Targeted actual-proxy CPU benchmark; no whole-game speed/deadline claim.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
import * as candidate from '../js/c-runtime/adapter-factories.js';
const root=process.cwd(),base='7732c2a2d8e09c38fd3215f2173490c424e8e9aa';
let before=execFileSync('git',['show',base+':js/c-runtime/adapter-factories.js'],{encoding:'utf8'});
for(const file of ['adapter-memory.js','records.js'])before=before.replaceAll("'./"+file+"'",JSON.stringify(pathToFileURL(path.join(root,'js/c-runtime',file)).href));
const baseline=await import('data:text/javascript;base64,'+Buffer.from(before).toString('base64'));
const names=['monst','obj','rm','you'],layout=Object.fromEntries(names.map(name=>[name+'Size',64]));
function setup(module){
 const memory=new DataView(new ArrayBuffer(16384)),cache=new Map(),recordTypes=new Map();
 for(let at=64;at<16384;at+=4)memory.setInt32(at,at*3,true);
 const view=module.createPrototypeDescriptorFactory({address:v=>Number(v?.address??v),cache,recordTypes,layout,errorPrefix:'unknown field '},name=>{
  const prototype={},fields=[{name:'value',offset:0},{name:'other',offset:4}];
  for(const field of fields)Object.defineProperty(prototype,field.name,{get(){return memory.getInt32(this.address+field.offset,true);},set(v){memory.setInt32(this.address+field.offset,v,true);}});
  // Same exported alias installer as real binding prototypes: the accessor
  // dynamically reads this.value, so it invokes the actual Proxy trap again.
  module.installAliasedFields(prototype,name,[{kind:name,key:'alias',path:['value'],writable:true}],true);
  return prototype;
 });
 const views=names.map((name,i)=>view(name,64+i*2048));
 for(const v of views)for(const k of ['0','00','1','2','03'])void v[k].value;
 return{views,memory,cache,recordTypes};
}
const variants={baseline:setup(baseline),candidate:setup(candidate)};
let sink=0;const iterations=100000;
function work(state,pattern,n){let sum=0;const views=state.views;
 if(pattern==='monoField')for(let i=0;i<n;i++)sum=(sum+views[0].value)|0;
 else if(pattern==='mixedFields')for(let i=0;i<n;i++){const v=views[i&3];sum=(sum+(i&4?v.value:v.other))|0;}
 else if(pattern==='aliases')for(let i=0;i<n;i++)sum=(sum+views[i&3].alias)|0;
 else if(pattern==='numericIndex')for(let i=0;i<n;i++)sum=(sum+views[i&3][String((i>>>2)&3)].value)|0;
 else if(pattern==='mixedKeys'){const keys=['value','alias','0','other','1','alias','03','value'];for(let i=0;i<n;i++){const value=views[i&3][keys[(i>>>2)&7]];sum=(sum+(typeof value==='number'?value:value.value))|0;}}
 sink^=sum;return sum;
}
const rows=[];
for(const pattern of ['monoField','mixedFields','aliases','numericIndex','mixedKeys']){
 assert.equal(work(variants.baseline,pattern,20000),work(variants.candidate,pattern,20000));const trials=[];
 for(let cycle=0;cycle<4;cycle++)for(const variant of ['baseline','candidate','candidate','baseline']){const start=process.cpuUsage();const checksum=work(variants[variant],pattern,iterations);const cpu=process.cpuUsage(start);trials.push({variant,cpuUs:cpu.user+cpu.system,checksum});}
 const total=variant=>trials.filter(t=>t.variant===variant).reduce((s,t)=>s+t.cpuUs,0);rows.push({pattern,ratio:total('candidate')/total('baseline'),trials});
}
const result={node:process.version,iterations,warmup:20000,cycles:4,sink,rows,scope:'Actual exported prototype factory, record-store, proxy traps and alias installer; synthetic live DataView-backed fields. Component only, not whole-game attribution.'};fs.mkdirSync(path.join(root,'.cache'),{recursive:true});fs.writeFileSync(path.join(root,'.cache/record-index-benchmark.json'),JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(rows.map(({pattern,ratio})=>({pattern,ratio})),null,2));
