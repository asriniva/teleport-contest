import './pure-js-probes/deny-wasm.mjs';
import fs from 'node:fs';import assert from 'node:assert/strict';
import {createProbe,createReference} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
import {C,R,T} from '../js/c-runtime/context.js';
const reference=await createReference('zap'),actual=await createProbe('zap'),modules=[reference,actual];
const text=(m,p)=>{p=Number(p);if(!p)return null;let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');};
const raw={};for(let i=0;i<reference._probe_layout_count();i++)raw[text(reference,reference._probe_layout_name(i))]=reference._probe_layout_value(i);
const L={};for(const[k,v]of Object.entries(raw))L[k]=raw['constwidth_'+k]===8n?(raw['constsigned_'+k]?BigInt.asIntN(64,v):BigInt.asUintN(64,v)):Number(BigInt.asIntN(64,v));
// Reuse the existing action-index definition, and independently verify the
// selected index against its native C dispatch source before invoking it.
const definition=fs.readFileSync('scripts/test-tu-zap.mjs','utf8'),names=JSON.parse(definition.match(/const names=(\[[^\n;]+\]);/)[1]),entry=names.indexOf('zhitu');
assert.ok(entry>=0);assert.ok(fs.readFileSync('scripts/tu-zap-probe.c','utf8').includes('case '+entry+':{zhitu('));
const properties=['ANTIMAGIC','FIRE_RES','COLD_RES','SHOCK_RES','SLEEP_RES','DISINT_RES','POISON_RES','ACID_RES'];
const masks=[[0n,0n,0n],[1n,0n,0n],[0n,1n,0n],[0n,1n,1n],[0x20000000000001n,0n,0n]];
function snapshot(m){const view=new FixtureDataView(m.HEAPU8.buffer),at=Number(m._probe_ints());return{result:text(m,m._probe_result()),trace:text(m,m._probe_trace()),state:text(m,m._probe_snapshot()),integers:Array.from({length:8},(_,i)=>view.getInt32(at+i*4,true)),buffers:Array.from({length:3},(_,i)=>text(m,m._probe_buffer(i)))};}
let cases=0;
for(const element of [0,1,2,3,5,7])for(const source of [0,10,20,-30])for(const property of properties)for(const mask of masks)for(const seed of [1,2,7,32]){
 assert.ok(Number.isInteger(L[property]),property);const type=source<0?source-element:source+element,ndice=seed&1?3:1;
 const stacks=modules.map(m=>m._probe_stack());
 for(const m of modules){
  m._probe_reset();m._probe_seed(seed);m._probe_option(0,1);m._probe_property(L[property],...mask);
  const p=Number(m._probe_buffer(0));m.HEAPU8.set(Buffer.from('controlled beam\0'),p);
  m._probe_invoke(entry,...[type,ndice,p,10,10,0,0,0,0].map(BigInt));
 }
 const label=[type,property,mask.map(String).join(','),seed,ndice].join(':');
 assert.deepEqual(snapshot(actual),snapshot(reference),label+' declared complete fixture result/state/trace/properties/buffers');
 assert.deepEqual(modules.map(m=>m._probe_stack()),stacks,label+' stack');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);cases++;
}
assert.equal(cases,3840);console.log('PASS:3840 original-C/pure-JS ZAP nonfatal beam/property cases over6 elements,4 encoded source classes,8 properties,5 masks and4 seeds; declared complete fixture snapshot/trace and restored stacks. Fatal death/poison paths are not claimed.');
