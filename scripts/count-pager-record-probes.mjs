// Diagnostic only: count caught record probes during real input-driven actions.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {enablePagerLookup} from '../js/nethack/pager-lookup.js';
const assets=process.argv[2];if(!assets)throw Error('Usage: count-pager-record-probes.mjs <assets>');
const layouts=JSON.parse(fs.readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),results=[];
for(const [name,keys]of [['local-look','  n:'],['farlook','  n;  l. '],['symbol','  n/?.\n'],['help','  n?b'+' '.repeat(10)]]){
 const failures=new Map();let calls=0;
 const result=runStandaloneProgram(assets,{seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys,observeRuntime({environment:env}){
  enablePagerLookup(env,layouts);const original=env.ctypes.record;
  env.ctypes.record=(type)=>{calls++;try{return original(type);}catch(error){if(error.stack.includes('nativeArg'))failures.set(type,(failures.get(type)??0)+1);throw error;}};
 }});
 assert.deepEqual(result.status,{kind:'input-exhausted'},name);
 results.push({name,recordCalls:calls,nativeArgFailures:Object.fromEntries(failures),totalFailures:[...failures.values()].reduce((n,v)=>n+v,0),frames:result.frames.length});
}
console.log(JSON.stringify({diagnosticOnly:true,results},null,2));
