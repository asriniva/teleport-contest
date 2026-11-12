import assert from 'node:assert/strict';import fs from 'node:fs';import {execFileSync} from 'node:child_process';
let source=execFileSync('git',['show','ec9917ff365eb631b51269fb728cb16c28fc5fb6:js/c-runtime/types.js'],{encoding:'utf8'});source=source.replace("'./memory.js'",JSON.stringify(new URL('../js/c-runtime/memory.js',import.meta.url).href));
const {createCTypes:baseline}=await import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
import {createCTypes as candidate} from '../js/c-runtime/types.js';
let checks=0;const outcome=fn=>{try{return{value:fn()};}catch(e){return{error:e.name,message:e.message};}};
function make(factory){const trace=[],meta={aliases:{alias:'int'},records:{record:{size:undefined,fields:{}}},enums:{'enum E':{size:4,signed:1}}};let buffer=new ArrayBuffer(64),view=new DataView(buffer);view.setInt32(4,12345,true);let throwView=false;
 const memory={bounds(at,n){trace.push(['bounds',at,n]);if(at<0||at+n>64)throw new RangeError('bounds');},get view(){trace.push('view');if(throwView)throw new Error('view failure');return new Proxy(view,{get(v,k){trace.push(['method',k]);const method=Reflect.get(v,k,v);return typeof method==='function'?method.bind(v):method;}});}};
 const api=factory(memory,meta,{});return{api,meta,trace,setThrow(v){throwView=v;},replace(){buffer=new ArrayBuffer(64);view=new DataView(buffer);view.setInt32(4,54321,true);}};}
for(const mode of ['undefined-alias-size','view-failure','enum-replacement','view-replacement']){
 const a=make(baseline),b=make(candidate);
 for(let step=0;step<6;step++){
  let ta=4,tb=4,type='int';
  if(mode==='undefined-alias-size'){
   type='alias';if(step===0){ta={get address(){a.trace.push('address');a.meta.aliases.int='record';return 4;}};tb={get address(){b.trace.push('address');b.meta.aliases.int='record';return 4;}};}
   else for(const f of[a,b])f.meta.records.record.size=step%2?4:8;
  }
  if(mode==='view-failure'){for(const f of[a,b])f.setThrow(step===0||step===3);}
  if(mode==='enum-replacement'){type='enum E';for(const f of[a,b])f.meta.enums['enum E']=step===2?undefined:{size:step%2?1:4,signed:step%2};}
  if(mode==='view-replacement'&&step===2)for(const f of[a,b])f.replace();
  assert.deepEqual(outcome(()=>a.api.load(type,ta)),outcome(()=>b.api.load(type,tb)),mode+' '+step);assert.deepEqual(a.trace,b.trace,mode+' trace '+step);checks+=2;
 }
}
const result={checks,scope:'Pinned ec9917 vs actual production load-plan candidate: address-hook alias mutation, undefined-size reevaluation, repeated failures, enum replacement and view replacement.'};fs.writeFileSync(new URL('../.cache/load-plan-mutation-contracts.json',import.meta.url),JSON.stringify(result,null,2)+'\n');console.log(result);
