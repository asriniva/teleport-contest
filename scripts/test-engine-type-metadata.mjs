import {parseCPrototype} from '../js/c-runtime/prototypes.js';
import {checkAllRecordFieldTypes} from './check-all-record-field-types.mjs';
import {checkAbiFieldTables} from './check-abi-field-tables.mjs';
// Audit configured production ABI declarations, including nested callback types.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createCTypes,withNetHackEnums} from '../js/nethack/c-types.js';
import {enableApply} from '../js/nethack/apply.js';
import {createNativeAbiCaster} from '../js/nethack/native/execution.js';
import records from '../js/nethack/records.json' with {type:'json'};
const env=createStandaloneEnvironment(),metadata=withNetHackEnums(records),types=new Set();
let prototypes=0,nestedCallbacks=0,structured=0,files=0;
function split(s){let depth=0,start=0,out=[];for(let i=0;i<s.length;i++){if(s[i]==='(')depth++;else if(s[i]===')')depth--;else if(s[i]===','&&!depth){out.push(s.slice(start,i).trim());start=i+1;}assert.ok(depth>=0,'balanced prototype '+s);}assert.equal(depth,0,'balanced prototype '+s);out.push(s.slice(start).trim());return out.filter(t=>t&&t!=='void');}
const callbackTypes=new Set();
function checkType(t,where){
 t=t.trim();if(t==='void'||t==='...')return;
 const canonical=env.ctypes.canonical(t).replace(/(\))\s+[A-Za-z_]\w*$/,'$1'),fp=/^([^()]+?)\s*\(\s*\*\s*\)\s*\(/.test(canonical);
 if(fp){nestedCallbacks++;if(!callbackTypes.has(canonical)){callbackTypes.add(canonical);const row=parseCPrototype(canonical);checkType(row.result,where);row.parameters.forEach(t=>checkType(t,where));}return;}
 types.add(t);assert.doesNotThrow(()=>env.ctypes.size(t),where+': '+t);
}

function prototype(p,where){const row=parseCPrototype(p);prototypes++;checkType(row.result,where);row.parameters.forEach(t=>checkType(t,where));}
const maps=new Set(['public','dependencies','functionTypes','functions']);
function walk(v,where,key=''){
 if(!v||typeof v!=='object')return;
 if(typeof v.prototype==='string')prototype(v.prototype,where+'.prototype');
 if(typeof v.result==='string'&&Array.isArray(v.parameters)){structured++;checkType(v.result,where);v.parameters.forEach(t=>checkType(t,where));}
 for(const [k,x]of Object.entries(v)){
  if(typeof x==='string'&&maps.has(key)&&x.includes('('))prototype(x,where+'.'+k);
  else if(k==='ctype'&&typeof x==='string'&&/\(\*\)/.test(x))checkType(x,where+'.ctype');
  else if(k!=='prototype')walk(x,where+'.'+k,k);
 }
}
walk(JSON.parse(fs.readFileSync('js/nethack/public-functions.json')),'public-functions.json');
for(const file of fs.readdirSync('js/nethack').filter(f=>f.endsWith('-abi.json')||f==='address-ports.json').sort()){files++;walk(JSON.parse(fs.readFileSync('js/nethack/'+file)),file);}
// Both shared runtime creation and legacy direct type environments must see all
// measured enums. Test sign boundaries and storage without inventing layouts.
const direct=createCTypes(env.memory,records,env.bitfields),at=env.memory.malloc(8);
for(const [name,layout]of Object.entries(metadata.enums)){
 const expected=layout.signed?'int':'unsigned int';assert.equal(layout.size,4);assert.equal(env.ctypes.abiType(name),expected);assert.equal(direct.abiType(name),expected);
 for(const value of [-1,0,2147483647,2147483648,4294967295]){env.ctypes.store(name,at,value);assert.equal(env.ctypes.load(name,at),layout.signed?value|0:value>>>0);const cast=createNativeAbiCaster(env.ctypes,env.transport,env.address);assert.equal(cast(name)(value),layout.signed?value|0:value>>>0);}
}
assert.equal(Object.keys(metadata.enums).length,128);assert.ok(prototypes>5000);assert.ok(nestedCallbacks>100);
assert.throws(()=>withNetHackEnums({...records,enums:{...records.enums,'enum bhit_call_types':{size:8,signed:true}}}),/Conflicting measured C enum/);
assert.throws(()=>env.ctypes.size('enum nonexistent'),/Unmeasured C enum/);
// Exercise the actual APPLY conversion wrapper (fixture callbacks bypass it).
const L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
env.enableDecl(L.decl);env.enableMonst(L.monst);const seen=[];let callbacks=0;
env.register('type-metadata-probe',{bhit(...args){seen.push(args);for(const fp of args.slice(4,6))if(fp)env.functions.indirect(fp,'ipp',0,0);return 0;}});
const apply=enableApply(env,L);
assert.equal(apply.services.bhit(1,0,80,L.apply.FLASHED_LIGHT,0,0,0),0);
assert.deepEqual(seen.pop(),[1,0,80,L.apply.FLASHED_LIGHT,0,0,0]);
const fp=env.functions.functionPointer(()=>{callbacks++;return 0;},'ipp');apply.services.bhit(1,0,80,4294967295,fp,fp,at);
assert.deepEqual(seen.pop(),[1,0,80,4294967295,Number(fp),Number(fp),at]);assert.equal(callbacks,2);
const fieldTables=checkAbiFieldTables(),recordTypes=checkAllRecordFieldTypes(env);
console.log('PASS '+JSON.stringify({recordFieldTypes:recordTypes.fields,recordTypes:recordTypes.records,abiFieldTables:fieldTables.tables,abiFieldNames:fieldTables.fields,files,prototypes,structured,nestedCallbacks,distinctTypes:types.size,enums:128,productionApplyCalls:2}));
