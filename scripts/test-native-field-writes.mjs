// Actual native field mutations against the pinned prior game-field writers.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {compileNativeFieldPlans,createNativeAddressFields} from '../js/nethack/native/address-fields.js';
import {createScalarAdapter,createImmutableFieldMetadata} from '../js/c-runtime/adapter-factories.js';
const baseCommit='4e1b4d7';
let source=execFileSync('git',['show',baseCommit+':js/nethack/native/address-fields.js'],{encoding:'utf8'});
for(const name of ['state-bridge','address-state'])source=source.replace("'./"+name+".js'",JSON.stringify(new URL('../js/nethack/native/'+name+'.js',import.meta.url).href));
const prior=await import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
const game=createStandaloneEnvironment(),owner=nativeStateFor(game),metadata=JSON.parse(fs.readFileSync('js/nethack/address-ports.json')).ports;
const values=[0,-0,1,-1,127,128,255,256,32768,65536,2**31,2**32,2**53-1,2**53,Number.MAX_VALUE,-Number.MAX_VALUE,0n,-1n,2n**80n+3n,0xa5abcdef12345678n,'17','1.0','bad',true,false,null,undefined,NaN,Infinity,-Infinity,1.5,Symbol('field')];
let fields=0,checks=0;
const result=fn=>{try{return {value:fn()};}catch(e){return {error:e.constructor.name};}};
for(const [name,{schema}]of Object.entries(metadata)){
 const make=(api)=>{const plans=api.compileNativeFieldPlans(game,schema),services={nativeOwner:owner,nativeModuleName:name,nativeFieldPlans:plans,heap:()=>game.memory.HEAPU8};const {env,decode}=createScalarAdapter(services,{},schema,game.address,{profile:'cached-fields',errors:['scalar ','cell ','field '],fieldMetadata:createImmutableFieldMetadata(schema)});return {plans,fields:api.createNativeAddressFields(env,services,schema,decode,game.address)};};
 const a=make({compileNativeFieldPlans,createNativeAddressFields}),b=make(prior);let id=0;
 for(const [kind,row]of Object.values(schema.schema).entries()){
  const bytes=game.ctypes.size(row.ctype),p=game.memory.calloc(1,bytes),q=game.memory.calloc(1,bytes);
  for(const [index,f]of row.fields.entries()){
   const fieldId=id++;if(!a.plans[kind][index].nativeWrite)continue;fields++;
   for(const value of values){
    game.memory.HEAPU8.fill(165,p,p+bytes);game.memory.HEAPU8.fill(165,q,q+bytes);
    const expected=result(()=>b.fields.writers[fieldId](q,value)),actual=result(()=>a.fields.writers[fieldId](p,value));
    assert.deepEqual(actual,expected,name+'.'+f.name+' result '+String(value));
    assert.deepEqual(game.memory.readBytes(p,bytes),game.memory.readBytes(q,bytes),name+'.'+f.name+' bytes '+String(value));checks++;
   }
   for(const mode of ['primitive','valueOf','getter','failure']){
    const run=(api,at)=>{const trace=[];let value;
     if(mode==='primitive')value={[Symbol.toPrimitive](hint){trace.push(hint);return 255;}};
     if(mode==='valueOf')value={valueOf(){trace.push('valueOf');return 17;}};
     if(mode==='getter')value={get [Symbol.toPrimitive](){trace.push('get primitive');return hint=>{trace.push(hint);return 65537n;};}};
     if(mode==='failure')value={[Symbol.toPrimitive](){trace.push('failure');throw new RangeError('coercion failure');}};
     game.memory.HEAPU8.fill(165,at,at+bytes);const outcome=result(()=>api.fields.writers[fieldId](at,value));if(!outcome.error){assert.ok(outcome.value===value,'assignment returns original object');delete outcome.value;}return {trace,outcome,bytes:game.memory.readBytes(at,bytes)};
    };
    assert.deepEqual(run(a,p),run(b,q),name+'.'+f.name+' '+mode);checks++;
   }
  }
  game.memory.free(p);game.memory.free(q);
 }
}
console.log(JSON.stringify({passed:true,baseCommit,ports:Object.keys(metadata).length,fields,checks,actualPriorWriters:true,assignmentRhs:true,coercionOrder:true,exactBytes:true,scope:'Synthetic correctness against pinned prior writers; no baseline timing or CPU profiling.'}));
