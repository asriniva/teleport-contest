import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
const BASE='d9c2321e4799679f0b52c19722db6e2423119b07';
let source=execFileSync('git',['show',BASE+':js/c-runtime/adapter-factories.js'],{encoding:'utf8'});
source=source.replaceAll("'./adapter-memory.js'",JSON.stringify(new URL('../js/c-runtime/adapter-memory.js',import.meta.url).href)).replaceAll("'./records.js'",JSON.stringify(new URL('../js/c-runtime/records.js',import.meta.url).href));
const baseline=await import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
import * as candidate from '../js/c-runtime/adapter-factories.js';
const snapshot=schema=>new Map(Object.entries(schema.schema).map(([name,row],kind)=>[name,new Map(row.fields.map((field,index)=>[field.name,Object.freeze({kind,index,canonical:field.canonical})]))]));
const outcome=fn=>{try{return{value:fn()};}catch(e){return{error:e.constructor.name,message:e.message};}};
let checks=0;
function run(mod,owned){
 const trace=[],schema={schema:{R:{fields:[{name:'a',canonical:'int'},{name:'b',canonical:'unsigned char'},{name:'p',canonical:'void *'}]},S:{fields:[{name:'c',canonical:'long'}]}},globals:[]};
 const fieldMetadata=owned&&mod.createImmutableFieldMetadata?mod.createImmutableFieldMetadata(schema):snapshot(schema);
 const services={heap:()=>new Uint8Array(4096)},ids=new WeakMap();let id=0,env;
 let revision=0;
 Object.defineProperties(services,{
  read:{configurable:true,get(){trace.push('read lookup');return(kind,at,index)=>{trace.push(['read',kind,at,index,revision]);return kind*101+at+index+revision;};}},
  address:{configurable:true,get(){trace.push('address lookup');return(kind,at,index)=>{trace.push(['address',kind,at,index]);return at+index*8;};}},
  write:{configurable:true,get(){trace.push('write lookup');return(...args)=>{trace.push(['write',...args]);};}}
 });
 const ptr=value=>{trace.push(['ptr',typeof value]);return Number(value);};
 ({env}=mod.createScalarAdapter(services,{},schema,ptr,{profile:'cached-fields',errors:['scalar ','cell ','field '],fieldMetadata}));
 const get=(at,name='R',field='a')=>{const a=env.field(at,name,field);if(!ids.has(a))ids.set(a,++id);return a;};
 const view=a=>({id:ids.get(a),address:a.address,value:a.value,keys:Object.keys(a)});
 const values=[];
 values.push(view(get(64)),view(get(64)),view(get(72)),view(get(64)),view(get(0)),view(get(8)),view(get(0)));
 for(let i=0;i<140;i++)values.push(view(get(i*8)));
 values.push(view(get(64)),view(get(140*8)),view(get(140*8)),view(get(16,'R','b')));
 const held=get(64);held.value=-5;revision=100;values.push(view(held));
 // Live provider replacement must affect previously created accessors.
 Object.defineProperty(services,'read',{get(){trace.push('replacement read lookup');return(...args)=>{trace.push(['replacement read',...args]);return 91;};}});
 values.push(view(held));
 // Pointer coercion can reenter with another selector or create/evict entries
 // for the same selector before the outer call reads bucket.last/entries.
 for(const mode of ['same','other','evict','cold']){
  const pointer={valueOf(){trace.push('coerce '+mode);if(mode==='evict')for(let i=0;i<135;i++)get(2000+i*8);else if(mode==='other')get(88,'R','b');else if(mode==='cold')get(96,'S','c');else get(96);return 96;}};
  values.push(view(get(pointer,mode==='cold'?'S':'R',mode==='cold'?'c':'a')));
 }
 // Invalid selector error must precede pointer coercion, without a cache entry.
 let pointerCalls=0;const badPointer={valueOf(){pointerCalls++;throw new Error('pointer called');}};
 for(const [name,field]of [['Missing','a'],['R','Missing'],['R',Symbol('missing')],[{},{}]])values.push(outcome(()=>get(badPointer,name,field)));
 values.push(pointerCalls,outcome(()=>get(badPointer)));
 // Metadata helper is a construction-time snapshot, including frozen values.
 schema.schema.R.fields[0].canonical='long';schema.schema.R.fields.reverse();values.push(view(get(48)));
 if(!owned){fieldMetadata.get('R').set('a',Object.freeze({kind:1,index:0,canonical:'int'}));values.push(view(get(48)));fieldMetadata.delete('R');values.push(outcome(()=>get(badPointer)));}
 return{trace,values};
}
for(const owned of [false,true]){assert.deepEqual(run(candidate,owned),run(baseline,owned));checks++;}
const schema={schema:{A:{fields:[{name:'x',canonical:'int'},{name:'x',canonical:'short'},{name:NaN,canonical:'int'},{name:undefined,canonical:'int'}]}},globals:[]};
const frozen=candidate.createImmutableFieldMetadata(schema),plain=snapshot(schema);
assert.ok(Object.isFrozen(frozen));assert.ok(Object.isFrozen(frozen.get('A')));checks+=2;
for(const key of ['x',NaN,undefined,Symbol('x'),{}]){assert.deepEqual(frozen.get('A').get(key),plain.get('A').get(key));checks++;}
assert.ok(Object.isFrozen(frozen.get('A').get('x')));assert.equal(frozen.set,undefined);assert.equal(frozen.get('A').set,undefined);checks+=3;
// Factory construction must preserve original schema getter evaluation order.
function construction(make){const trace=[];const f={get name(){trace.push('name');return'x';},get canonical(){trace.push('canonical');return'int';}},row={get fields(){trace.push('fields');return[f];}},s={get schema(){trace.push('schema');return{get A(){trace.push('A');return row;}}}};make(s);return trace;}
assert.deepEqual(construction(candidate.createImmutableFieldMetadata),construction(snapshot));checks++;
// Adapter initialization uses the private snapshot without schema rereads;
// state must be adapter-local and never exposed through frozen metadata.
const immutableSchema={schema:{R:{fields:[{name:'a',canonical:'int'}]}},globals:[]};
const immutableMetadata=candidate.createImmutableFieldMetadata(immutableSchema);
Object.defineProperty(immutableSchema,'schema',{get(){throw new Error('schema reread');}});
const services={heap:()=>new Uint8Array(512),read:()=>19,address:(k,at)=>at,write(){}};
const make=()=>candidate.createScalarAdapter(services,{},immutableSchema,Number,{profile:'cached-fields',errors:['scalar ','cell ','field '],fieldMetadata:immutableMetadata}).env;
const one=make(),two=make();assert.notEqual(one.field(64,'R','a'),two.field(64,'R','a'));checks++;
assert.deepEqual(immutableMetadata.get('R').get('a'),{kind:0,index:0,canonical:'int'});checks++;
assert.equal(one.field(64,'R','a').value,19);checks++;
function proxiedFacade(mod){
 const trace=[];
 const wrapped=new Proxy(immutableMetadata,{get(target,key,receiver){trace.push('root '+String(key));return Reflect.get(target,key,receiver);}});
 const {env}=mod.createScalarAdapter(services,{},immutableSchema,Number,{profile:'cached-fields',errors:['scalar ','cell ','field '],fieldMetadata:wrapped});
 for(let i=0;i<3;i++)env.field(64,'R','a').value;
 return trace;
}
assert.deepEqual(proxiedFacade(candidate),proxiedFacade(baseline));checks++;
let actualFields=0;
for(const moduleName of ['display','invent']){
 const actualSchema=JSON.parse(execFileSync('git',['show',BASE+':js/nethack/bindings/'+moduleName+'.js'],{encoding:'utf8'}).match(/const schema=(.*);/)[1]);
 const values=mod=>{
  const metadata=mod.createImmutableFieldMetadata?mod.createImmutableFieldMetadata(actualSchema):snapshot(actualSchema);
  const svc={heap:()=>new Uint8Array(512),read:(kind,at,index)=>kind*71+at+index,address:(kind,at,index)=>kind*4096+at+index,write(){}};
  const {env}=mod.createScalarAdapter(svc,{},actualSchema,Number,{profile:'cached-fields',errors:['scalar ','cell ','field '],fieldMetadata:metadata});
  const rows=[];
  for(let round=0;round<3;round++)for(const[name,row]of Object.entries(actualSchema.schema))for(const field of row.fields){
   const cell=env.field(64+round*8,name,field.name);rows.push([cell.address,outcome(()=>cell.value)]);
  }
  return rows;
 };
 const expected=values(baseline);assert.deepEqual(values(candidate),expected);checks++;actualFields+=expected.length/3;
}
fs.writeFileSync(new URL('../.cache/immutable-selector-contracts.json',import.meta.url),JSON.stringify({checks,actualFields,actualFieldReads:actualFields*3,baseCommit:BASE,candidate:'current production source',scope:'Detailed trace/identity scenarios, not native or recorder validation.'},null,2)+'\n');console.log({checks,actualFields});
