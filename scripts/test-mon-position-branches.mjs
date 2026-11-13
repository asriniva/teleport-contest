// Original mfndpos policy on native catalogues and controlled neighbouring cells.
import './pure-js-probes/deny-wasm.mjs';
import fs from 'node:fs';import assert from 'node:assert/strict';
import {createProbe,createReference} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
import {C,R,T} from '../js/c-runtime/context.js';
const L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')).mon,record=JSON.parse(fs.readFileSync('js/nethack/records.json')).records.monst;
const definition=fs.readFileSync('scripts/test-tu-mon.mjs','utf8'),names=JSON.parse(definition.match(/const names=(\[[^\n;]+?\]),returns=/)[1]),entry=names.indexOf('mfndpos');
assert.ok(entry>=0);assert.ok(fs.readFileSync('scripts/tu-mon-probe.c','utf8').includes('case '+entry+':return mfndpos(monsters[a],&fixture_mfp,c);'));
assert.equal(record.size,L.monSize);
assert.equal(L.mon_nmon_size,8,'configured native pointer width');
const flagNames=['ALLOW_BARS','ALLOW_DIG','ALLOW_M','ALLOW_MDISP','ALLOW_ROCK','ALLOW_SANCT','ALLOW_SSM','ALLOW_TM','ALLOW_TRAPS','ALLOW_U','ALLOW_WALL','BUSTDOOR','NOGARLIC','OPENDOOR','UNLOCKDOOR'];
const masks=[0n,BigInt(L.ALLOW_ALL),...flagNames.map(n=>{assert.ok(Number.isSafeInteger(L[n]),n);return BigInt(L[n]);}),0xffffffffn,0x8000000000000000n];
const neighbours=[[-1,-1],[0,-1],[1,-1],[-1,0],[1,0],[-1,1],[0,1],[1,1]];
const maps=[Array(8).fill('ROOM'),['STONE','TREE','IRONBARS','DOOR','POOL','LAVAPOOL','ROOM','ROOM'],['DOOR','DOOR','POOL','ROOM','IRONBARS','LAVAPOOL','TREE','STONE']];
assert.ok(process.argv.slice(2).every(arg=>arg==='--rooms-only'),'unknown position-matrix option');
const modes=process.argv.includes('--rooms-only')?[0]:[0,1,2];
for(const map of maps)for(const name of map)assert.ok(Number.isSafeInteger(L[name]),name);
for(const [name,field]of Object.entries(record.fields))if(field.ctype.includes('*'))assert.equal(L['mon_'+name+'_size'],8,name+' pointer width');
const modules=[await createReference('mon'),await createProbe('mon')];
function bytes(m,p,n){p=Number(p);return Buffer.from(m.HEAPU8.slice(p,p+n));}
function monster(m,index,pools){
 const p=Number(pools[index]),b=bytes(m,p,record.size),view=new FixtureDataView(m.HEAPU8.buffer),pointers={};
 for(const [name,field]of Object.entries(record.fields))if(field.ctype.includes('*')){
  const value=view.getBigUint64(p+field.offset,true),offset=value-pools[2];
  if(!value)pointers[name]=null;
  else if(value===pools[0]||value===pools[1])pointers[name]=['monster',pools.indexOf(value)];
  else if(offset>=0n&&offset<BigInt(L.NUMMONS*L.pmSize)&&offset%BigInt(L.pmSize)===0n)pointers[name]=['species',Number(offset/BigInt(L.pmSize))];
  else assert.fail(name+' unexpected pointer outside actual catalogue/monster pools');
  b.fill(0,field.offset,field.offset+8);
 }
 return{bytes:b,pointers};
}
function text(m,p){p=Number(p);let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString();}
function snapshot(m){const pools=[BigInt(m._probe_pointer(0,0)),BigInt(m._probe_pointer(0,1)),BigInt(m._probe_pointer(2,0))];return{positions:bytes(m,m._probe_pointer(17,0),L.mfpSize),monsters:[monster(m,0,pools),monster(m,1,pools)],trace:text(m,m._probe_trace()),grid:neighbours.map(([dx,dy])=>m._probe_grid_mon(10+dx,10+dy)),randomDraws:m._probe_count(2),aux:[0,1,2,3].map(i=>m._probe_aux(i))};}
let cases=0;
for(let species=0;species<L.NUMMONS;species++)for(const mode of modes)for(const mask of masks){
 const stacks=modules.map(m=>m._probe_stack()),results=[];
 for(const m of modules){
  m._probe_reset(species*3+mode+1);m._probe_new_mon(species);m._probe_new_mon(L.PM_GHOST);
  for(let i=0;i<neighbours.length;i++){const [dx,dy]=neighbours[i];m._probe_tile(10+dx,10+dy,L[maps[mode][i]],mode===2?L.D_LOCKED:L.D_CLOSED);}
  try{results.push(m._probe_run(entry,0,0,mask,0n,0n));}catch(error){error.message='species='+species+' terrain='+mode+' permissions='+mask+': '+error.message;throw error;}
 }
 const label=species+':'+mode+':'+mask;
 assert.equal(results[1],results[0],label+' source return');
 assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]),label+' all candidate coordinates/info bytes, monster scalar/bit bytes, neighbour identities, trace, RNG consumption and auxiliary outputs');
 assert.deepEqual(modules.map(m=>m._probe_stack()),stacks,label+' stack');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);cases++;
}
assert.equal(cases,L.NUMMONS*modes.length*masks.length);
console.log('PASS:'+cases+' original-C/pure-JS mfndpos cases; all'+L.NUMMONS+' native species, '+masks.length+' permission masks, terrain patterns '+modes.join(',')+'; complete declared fixture outputs, restored stacks/context. Raw pointer bytes are replaced by checked catalogue/monster identities.');
