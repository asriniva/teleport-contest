import {execFileSync} from 'node:child_process';
const BASE='ec9917ff365eb631b51269fb728cb16c28fc5fb6';
let source=execFileSync('git',['show',BASE+':js/c-runtime/types.js'],{encoding:'utf8'});
source=source.replace("'./memory.js'",JSON.stringify(new URL('../js/c-runtime/memory.js',import.meta.url).href));
const {createCTypes:baseline}=await import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
import {createCTypes as candidate} from '../js/c-runtime/types.js';
import assert from 'node:assert/strict';
import fs from 'node:fs';
const types=['char','signed char','unsigned char','short','unsigned short','int','unsigned int','unsigned','long','unsigned long','long long','unsigned long long','float','double','const int','volatile unsigned short','char*','int[4]','enum t','record','bad','toString','__proto__'];
const inputs=[0,1,3,-1,0.5,1n,'4',{address:4},Number.MAX_SAFE_INTEGER,Infinity,NaN];
const result=fn=>{try{return{value:fn()};}catch(e){return{error:e.name,message:e.message};}};
let checks=0;
function fixture(make){
 const trace=[],buffer=new ArrayBuffer(32),view=new DataView(buffer);view.setUint32(4,0xfedcba98,true);
 const tracked=new Proxy(view,{get(o,k){trace.push(['method',k]);const value=Reflect.get(o,k,o);return typeof value==='function'?value.bind(o):value;}});
 const memory={bounds(at,n){trace.push(['bounds',at,n]);if(at<0||at+n>32)throw new RangeError('fake bounds');},get view(){trace.push('view');return tracked;}};
 const metadata={aliases:{integer:'int'},records:{record:{size:4,fields:{}}},enums:{'enum t':{size:4,signed:1}}};
 const api=make(memory,metadata,{});return{api,trace,metadata};
}
for(const type of [...types,'integer'])for(const input of inputs){const a=fixture(baseline),b=fixture(candidate);for(let repeat=0;repeat<4;repeat++){assert.deepEqual(result(()=>a.api.load(type,input)),result(()=>b.api.load(type,input)));assert.deepEqual(a.trace,b.trace);checks+=2;}}
for(const signed of [0,1])for(const size of [1,2,4,8]){const a=fixture(baseline),b=fixture(candidate);for(const f of[a,b])f.metadata.enums['enum t']={size,signed};assert.deepEqual(result(()=>a.api.load('enum t',4)),result(()=>b.api.load('enum t',4)));assert.deepEqual(a.trace,b.trace);checks+=2;}
for(const preAlias of[false,true]){
 const a=fixture(baseline),b=fixture(candidate);
 for(const f of[a,b]){f.metadata.aliases.alias='int';if(preAlias)f.metadata.aliases.int='long';}
 for(let step=0;step<5;step++){
  if(step===1)for(const f of[a,b]){f.metadata.aliases.alias='char';f.metadata.aliases.int='double';}
  assert.deepEqual(result(()=>a.api.load('alias',4)),result(()=>b.api.load('alias',4)));assert.deepEqual(a.trace,b.trace);checks+=2;
 }
}
{
 const a=fixture(baseline),b=fixture(candidate);
 for(let step=0;step<5;step++){
  for(const f of[a,b])f.metadata.enums['enum t']={size:step%2?1:4,signed:step%2};
  assert.deepEqual(result(()=>a.api.load('enum t',4)),result(()=>b.api.load('enum t',4)));assert.deepEqual(a.trace,b.trace);checks+=2;
 }
}
// Unknown size must never become a plan; original size() deliberately misses undefined.
{
 const a=fixture(baseline),b=fixture(candidate);
 for(const f of[a,b]){f.metadata.aliases.int='record';f.metadata.records.record.size=undefined;}
 for(let step=0;step<3;step++){
  if(step===1)for(const f of[a,b])f.metadata.records.record.size=4;
  assert.deepEqual(result(()=>a.api.load('integer',4)),result(()=>b.api.load('integer',4)));assert.deepEqual(a.trace,b.trace);checks+=2;
 }
}
const output={checks,scope:'Production candidate vs immutable ec9917ff365eb631b51269fb728cb16c28fc5fb6; scalar load-plan output/error and live-view/method/bounds ordering comparisons; no native acceptance.'};fs.writeFileSync(new URL('../.cache/load-plan-contracts.json',import.meta.url),JSON.stringify(output,null,2)+'\n');console.log(output);
