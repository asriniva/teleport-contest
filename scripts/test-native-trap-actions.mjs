// Native WORN text boundary called on genuine initial worlds; component proof.
import {parse} from 'acorn';import {enableTrap} from '../js/nethack/trap.js';import {trapSchema as schema} from '../js/ported/trap.js';import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';import {runFullOriginalC} from './full-original-c-run.mjs';import {worldGraph} from './restoration-world-graph.mjs';import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const rawInput=' '.repeat(64),rawC=[],rawJS=[];let rawCI=0,rawJI=0;const runnerSource=fs.readFileSync('scripts/run-standalone-program.mjs','utf8'),runnerNeedle='createStandaloneProgram({layouts,runtime:',runnerPatched=runnerSource.replace(runnerNeedle,'createStandaloneProgram({layouts,stdio:{readStdin:input.readRawStdin},runtime:');assert.notEqual(runnerPatched,runnerSource);assert.equal(runnerSource.split(runnerNeedle).length,2);fs.writeFileSync('.cache/trap-actions-input-runner.mjs',runnerPatched);const{runStandaloneProgram}=await import('../.cache/trap-actions-input-runner.mjs');
const dir='.cache/full-original-c-v1',out='.cache/native-trap-actions',L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),R=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;fs.mkdirSync(out,{recursive:true});let checks=0;const eq=(a,b,s)=>{assert.deepEqual(a,b,s);checks++;},sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');// Complete original-C provenance is verified by runFullOriginalC.
let module,env,program;const stdout=[],stderr=[];const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  nll',readRawStdin:n=>{assert.ok(n>0);assert.ok(rawJI<rawInput.length,'declared JS raw stdin exhausted');const code=rawInput.charCodeAt(rawJI++);rawJS.push(code);return Uint8Array.of(code);}},c=await runFullOriginalC(dir,{...input,observeRuntime:r=>{module=r.module;const inputTTY=module.FS.getStream(0).tty;inputTTY.ops={...inputTTY.ops,get_char(){assert.ok(rawCI<rawInput.length,'declared native raw stdin exhausted');const code=rawInput.charCodeAt(rawCI++);rawC.push(code);return code;}};for(const[fd,out]of[[1,stdout],[2,stderr]]){const tty=module.FS.getStream(fd).tty,put=tty.ops.put_char;tty.ops={...tty.ops,put_char:(t,c)=>{if(c!==null)out.push(c);return put(t,c);}};}}}),j=runStandaloneProgram(dir+'/assets',{...input,observeRuntime:r=>{env=r.environment;program=r.program;}});for(const k of ['status','consumed','snapshots','state','rngLog','displayRngLog','stdout','stderr'])eq(j[k],c[k],'genuine startup '+k);const roots={};for(let i=0;i<module._full_global_count();i++){let p=Number(module._full_global_name(i)),end=p;while(module.HEAPU8[end])end++;roots[Buffer.from(module.HEAPU8.slice(p,end)).toString()]=Number(module._full_global_address(i));}
const rng=kind=>kind==='c'?[0,1].map(i=>Buffer.from(module.HEAPU8.slice(Number(module._full_rng_state(i)),Number(module._full_rng_state(i))+Number(module._full_rng_size()))).toString('hex')):env.state('rnd').rnglist.map(({rng_state:s})=>{const l=L.rnd,b=Buffer.alloc(l.size);b.writeBigUInt64LE(BigInt(s.n),l.n);for(const k of ['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(BigInt(s[k][i]),l[k]+8*i);for(const k of ['a','b','c'])b.writeBigUInt64LE(BigInt(s[k]),l[k]);return b.toString('hex');});
const steps=[],snap=label=>{const cw=worldGraph({module}),jw=worldGraph({environment:env});eq(jw,cw,label+' full world');eq(rng('js'),rng('c'),label+' both complete ISAAC');const logs={};for(const p of ['/rng.log','/rng-display.log']){const read=f=>{try{return Buffer.from(f()).toString();}catch{return null;}},a=read(()=>module.FS.readFile(p)),b=read(()=>env.filesystem.readFile(p));eq(b,a,label+' '+p);logs[p]=a;}steps.push({label,rng:rng('c'),world:cw,logs});};snap('genuine ready world');
const graph=enableTrap(env,L),owner=nativeStateFor(env),C=graph.context,views=owner.nativeRecords;
const scalarNames=new Set(['mintrap','unconscious','floor_trigger','count_traps','immune_to_trap','m_harmless_trap']);
function call(name,cargs=[],jargs=cargs){assert.equal(typeof module['_'+name],'function','real C public '+name);const a=module['_'+name](...cargs),b=env.resolve(name)(...jargs);if(scalarNames.has(name))eq(b,a,name+' scalar result');snap(name);return{c:a,j:b};}
const off=(type,name)=>R[type].fields[name].offset,cv=()=>new DataView(module.HEAPU8.buffer),hero=views.record('struct you',env.requireGlobal('u')),x=hero.ux,y=hero.uy;
// Source creates and links selected trap types on the hero's genuine floor cell.
// Only nonfatal, nonlevel-changing effects are requested on this ready world.
for(const name of ['BEAR_TRAP','WEB','SQKY_BOARD','RUST_TRAP']){
 const trap=call('maketrap',[x,y,schema.constants[name]]);assert.ok(trap.c&&trap.j,'source accepted hero trap '+name);
 const native=graph.entries.maketrap.nativeState;
 eq(native===owner,true,'actual trap entry uses shared owner');
 call('dotrap',[trap.c,0],[trap.j,0]);
 call('reset_utrap',[0]);
 call('deltrap',[trap.c],[trap.j]);
}
const monlist=off('instance_globals_saved_l','level')+off('dlevel_t','monlist'),cmon=cv().getBigUint64(roots.svl+monlist,true),jmon=env.memory.view.getBigUint64(env.requireGlobal('svl')+monlist,true);
assert.ok(cmon&&jmon,'genuine source-created monster');
const mx=cv().getInt16(Number(cmon)+off('monst','mx'),true),my=cv().getInt16(Number(cmon)+off('monst','my'),true);
for(const name of ['WEB','BEAR_TRAP','SQKY_BOARD','RUST_TRAP']){
 const trap=call('maketrap',[mx,my,schema.constants[name]]);
 call('immune_to_trap',[cmon,schema.constants[name]],[Number(jmon),schema.constants[name]]);
 call('m_harmless_trap',[cmon,trap.c],[Number(jmon),trap.j]);
 call('mintrap',[cmon,0],[Number(jmon),0]);
 call('deltrap',[trap.c],[trap.j]);
}
call('tty_wait_synch');
eq(rawJS,rawC,'exact raw input consumption');eq(Buffer.from(program.stdio.captured(1)),Buffer.from(stdout),'exact terminal bytes');eq(Buffer.from(program.stdio.captured(2)),Buffer.from(stderr),'exact stderr');eq(program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'exact frames');
const evidence={passed:true,checks,steps:steps.length,rawInput:rawC,referenceReceiptSha256:sha(dir+'/receipt.json'),testSha256:sha('scripts/test-native-trap-actions.mjs'),scope:'Actual MAIN hero and source-created monster; source trap creation/linking, hero effects/reset/deletion and monster immunity/harmlessness/effects/deletion for web, bear, squeaky-board and rust traps. Complete world graph, both ISAAC states and ordered logs at each action, plus terminal/input/frames compare with original C. Other effects, every tool/form/level-transition branch and hidden recordings are not claimed.'};fs.writeFileSync(out+'/evidence.json',JSON.stringify(evidence,null,2));console.log(JSON.stringify(evidence));
