// Strict architectural acceptance: actual main input through final turn output.
// Test-only loader counters leave production and frozen sources unchanged.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {registerHooks} from 'node:module';
const reference='.cache/full-original-c-v1',input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  nl.Fyy '};
const intervals=[];let current,reads=0;
const count=(kind,name,size=0)=>{if(!current)return;const row=current[kind]??={calls:0,bytes:0,names:{}};row.calls++;row.bytes+=Number(size);row.names[name]=(row.names[name]??0)+1;};
globalThis.__nativeOrdinaryTurnCounter=count;
const touched=[];
const hooks=registerHooks({load(url,context,next){const result=next(url,context);let source=typeof result.source==='string'?result.source:Buffer.from(result.source??'').toString();const original=source;
 if(url.endsWith('/js/c-runtime/context.js')){const before='export function withCEnvironment(environment, callback, ...args) {';assert.equal(source.split(before).length,2);source=source.replace(before,before+"\n globalThis.__nativeOrdinaryTurnCounter?.('cContext',callback.name||'<anonymous>');");}
 if(url.endsWith('/js/c-runtime/linker.js')){const before='return transport.scoped(()=>withEnvironment(entry.environment,callback,...';assert.equal(source.split(before).length,2);source=source.replace(before,"globalThis.__nativeOrdinaryTurnCounter?.('genericCall',name+'.'+fn);\n        "+before);}
 if(url.endsWith('/js/c-runtime/heap.js')){const before='malloc(size) {';assert.equal(source.split(before).length,2);source=source.replace(before,before+"\n globalThis.__nativeOrdinaryTurnCounter?.('heapAllocation',new Error().stack.split('\\n').slice(2,5).join(' | '),size);");}
 if(url.endsWith('/js/c-runtime/memory.js')){const before='stackAlloc(n){';assert.equal(source.split(before).length,2);source=source.replace(before,before+"globalThis.__nativeOrdinaryTurnCounter?.('stackAllocation','stackAlloc',n);");}
 if(url.endsWith('/js/nethack/native/state-bridge.js')){const before='boundary(fn,...args) {';assert.equal(source.split(before).length,2);source=source.replace(before,before+"globalThis.__nativeOrdinaryTurnCounter?.('stateBoundary',fn.name||'<anonymous>');");}
 if(source!==original){touched.push(url);return{...result,source};}return result;
}});
try{
 const {runFullOriginalC}=await import('./full-original-c-run.mjs'),{runStandaloneProgram}=await import('./run-standalone-program.mjs');
 const expected=await runFullOriginalC(reference,input);
 const actual=runStandaloneProgram(reference+'/assets',{...input,observeRuntime:({environment})=>{const entry=environment.start('terminal-key-input'),read=entry.namespace.teleport_getch;
  entry.namespace.teleport_getch=()=>{current=undefined;const index=reads++;const result=read();if(index>=3){current={keyIndex:index,key:input.keys[index]};intervals.push(current);}return result;};
 }});
 current=undefined;
 for(const key of ['status','state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(actual[key],expected[key],key+' original-C equivalence');
 const {encodeRecorderScreen}=await import('../js/wasm-replay-support.js');
 assert.deepEqual(actual.frames,expected.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})), 'exact normalized recorder frames');
 assert.equal(expected.snapshots[4].state.x,expected.snapshots[3].state.x+1,'actual walk advances position');
 assert.equal(BigInt(expected.snapshots[5].state.moves),BigInt(expected.snapshots[4].state.moves)+1n,'actual wait advances the turn');
 assert.match(expected.rngLog,/@ hitum\(uhitm.c:/,'actual hero attack executes');
 assert.ok(BigInt(expected.state.moves)>BigInt(expected.snapshots[5].state.moves),'attack turn finishes after prompt output');
 const cases=[['walk',3,4],['wait',4,5],['attack',5,input.keys.length]].map(([kind,start,end])=>{const rows=intervals.filter(r=>r.keyIndex>=start&&r.keyIndex<end),totals={};for(const row of rows)for(const [key,value]of Object.entries(row)){if(!value?.names)continue;const out=totals[key]??={calls:0,bytes:0,names:{}};out.calls+=value.calls;out.bytes+=value.bytes;for(const [name,count]of Object.entries(value.names))out.names[name]=(out.names[name]??0)+count;}return{kind,totals};});
 const passed=cases.every(c=>!c.totals.cContext?.calls&&!c.totals.genericCall?.calls&&!c.totals.heapAllocation?.calls);
 const evidence={passed,originalCEquivalent:true,input,cases,instrumentedModules:touched,scope:'Real initial walk, wait and forced attack; input through pending output and next read. C malloc includes this runtime\'s C-stack allocations. Counters are architectural acceptance, not CPU or timing samples.'};
 fs.mkdirSync('.cache/native-ordinary-turns',{recursive:true});fs.writeFileSync('.cache/native-ordinary-turns/evidence.json',JSON.stringify(evidence,null,2)+'\n');
 console.log(JSON.stringify({passed,originalCEquivalent:true,cases:cases.map(c=>({kind:c.kind,...Object.fromEntries(Object.entries(c.totals).map(([k,v])=>[k,v.calls]))}))},null,2));
 if(!process.argv.includes('--report'))assert.ok(passed,'ordinary turns still enter generic C execution or allocate C heap storage');
}finally{hooks.deregister();delete globalThis.__nativeOrdinaryTurnCounter;}
