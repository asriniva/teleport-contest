// Production TRAP owner plus byte-boundary component checks; no coverage claim for all gameplay branches.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {enableTrap} from '../js/nethack/trap.js';
import {trapSchema as schema} from '../js/ported/trap.js';
import {createTrapEnvironment} from '../js/nethack/bindings/trap.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));let runtime,checks=0;
const eq=(a,b,s)=>{assert.deepEqual(a,b,s);checks++;};
const result=runStandaloneProgram('.cache/full-original-c-v1/assets',{seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n',observeRuntime:r=>{runtime=r;}});
eq(result.status.kind,'input-exhausted','genuine MAIN startup');
const env=runtime.environment,owner=nativeStateFor(env),graph=enableTrap(env,layouts),C=graph.context,{memory,transport}=env;
eq(enableTrap(env,layouts),graph,'one production owner');
const old=createTrapEnvironment({heap:()=>memory.HEAPU8,literal:env.services.literal,stackAlloc:transport.stackAlloc,global:i=>env.requireGlobal(Object.keys(schema.foreignGlobals)[i]),functionPointer:C.functionPointer},{initialized:true});
const observe=fn=>{try{return {value:fn()};}catch(e){return {error:e.constructor.name};}};
const values=[0,1,-1,127,128,255,256,65537,4294967297,-4294967297,1.75,NaN,Infinity,undefined,null,'17',true,2n**80n+7n,Symbol('invalid')];
for(const type of ['i8','u8','i16','u16','i32','u32','i64','u64','f32','f64'])for(const value of values)eq(observe(()=>C.nativeCast(type)(value)),observe(()=>old.cast(type,value)),'cast '+type+' '+String(value));
for(const type of ['i8','u8','i16','u16','i32','u32','i64','u64'])for(const op of ['+','-','*','/','%','&','|','^','<<','>>'])for(const [a,b]of [[0,0],[17,3],[-17,3],[4294967295,7],[65537,-1],[2n**63n-1n,2n]])eq(observe(()=>C.nativeBinary(type,op)(a,b)),observe(()=>old.binary(type,op,a,b)),'binary '+type+op);
let fields=0;
for(const [kind,row]of Object.entries(schema.records)){
 const at=memory.calloc(1,row.size),reference=memory.calloc(1,row.size);
 try{for(const f of row.fields){const plan=C.nativeField(kind,f.name);fields++;if(typeof f.type==='object'&&!f.type.pointer){eq(env.address(plan.address(at)),at+f.offset,'aggregate address '+kind+'.'+f.name);continue;}
  const candidates=f.type.pointer?[0]:f.bits!==null?[0,1,-1,257,undefined,NaN]:[0,1,-1,257,65537,4294967297];
  for(const value of candidates){const expected=observe(()=>f.bits!==null?old.setBit(reference+f.offset,f.bitOffset,f.bits,value):old.write(reference+f.offset,f.type,value)),actual=observe(()=>plan.write(at,value));if(f.type.pointer&&actual.value)actual.value=env.address(actual.value);eq(actual,expected,'field write '+kind+'.'+f.name);eq(Buffer.from(memory.HEAPU8.slice(at,at+row.size)),Buffer.from(memory.HEAPU8.slice(reference,reference+row.size)),'all field bytes '+kind+'.'+f.name);const v=plan.read(at);eq(f.type.pointer?env.address(v):v,f.bits!==null?old.bit(reference+f.offset,f.bitOffset,f.bits):old.read(reference+f.offset,f.type),'field read '+kind+'.'+f.name);}
 }}finally{memory.free(at);memory.free(reference);}
}
let tables=0;
for(const [name,def]of Object.entries(schema.data)){
 const ref=C.data(name),size=old.sizeof(def.type),at=memory.calloc(1,size);
 try{old.initialize(at,def.type,def.initial);
  if(ref.root.at===undefined){
   for(const leaf of ref.root.leaves.values()){
    if([...ref.root.leaves.values()].some(other=>other!==leaf&&other.offset<leaf.offset+old.sizeof(leaf.type)&&leaf.offset<other.offset+old.sizeof(other.type)))continue;
    const value=C.read(C.offset(ref,leaf.offset,1),leaf.type);
    eq(leaf.type.pointer?env.address(value):value,old.read(at+leaf.offset,leaf.type),'native leaf before packing '+name);
    eq(ref.root.at,undefined,'lookup does not pack table '+name);
   }
   const leaf=[...ref.root.leaves.values()].find(leaf=>typeof leaf.type==='string'&&![...ref.root.leaves.values()].some(other=>other!==leaf&&other.offset<leaf.offset+old.sizeof(leaf.type)&&leaf.offset<other.offset+old.sizeof(other.type)));
   if(leaf){C.write(C.offset(ref,leaf.offset,1),leaf.type,17);old.write(at+leaf.offset,leaf.type,17);eq(ref.root.at,undefined,'unaliased table write remains native '+name);}
  }
  eq(Buffer.from(memory.HEAPU8.slice(ref.address,ref.address+size)),Buffer.from(memory.HEAPU8.slice(at,at+size)),'complete lazy materialization '+name);tables++;}finally{memory.free(at);}
}
for(const [name,entry]of Object.entries(graph.entries)){eq(entry.nativeState===owner,true,'entry owner '+name);eq(typeof entry.nativeValuesEntry,'function','fixed native value entry '+name);}
const evidence={passed:true,checks,records:Object.keys(schema.records).length,fields,tables,entries:Object.keys(graph.entries).length,scope:'Actual production MAIN owner and all TRAP schema fields against the existing byte helper: signed/unsigned casts, integer operators, packed bits, aggregate addresses, complete initialized static-table bytes, fixed entry ownership. Scratch record states are component fixtures, not natural gameplay; recordings and original-C action tests are separate.'};fs.mkdirSync('.cache/native-trap-context',{recursive:true});fs.writeFileSync('.cache/native-trap-context/evidence.json',JSON.stringify(evidence,null,2));console.log(JSON.stringify(evidence));
