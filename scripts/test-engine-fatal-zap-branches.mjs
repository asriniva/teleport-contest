// Fatal beams and the direct poison handler use real MAIN termination; no
// returning death stub or recording. Poison tests ATTRIB, not its ZAP caller.
import fs from 'node:fs';import assert from 'node:assert/strict';
import {gzipSync} from 'node:zlib';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory='.cache/full-original-c-v1',records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
assert.ok(process.argv.slice(2).length<=1&&process.argv.slice(2).every(arg=>['--disintegration','--poison'].includes(arg)),'unknown fatal-zap option');
const disintegration=process.argv.includes('--disintegration'),poison=process.argv.includes('--poison'),beamType=disintegration?24:4,scenario=poison?'poison':disintegration?'disintegration':'death-ray';
const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n',maxInputBoundaries:1024};
let native,actual,busy=false,prepared=false;const steps={c:[],js:[]},attempts={c:0,js:0};
function pure(fn){const names=['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'],saved=names.map(n=>Object.getOwnPropertyDescriptor(globalThis,n)),deny=()=>{throw Error('Forbidden implementation capability');};for(const name of names)Object.defineProperty(globalThis,name,{configurable:true,value:name==='WebAssembly'?new Proxy({},{get:deny}):deny});try{return fn();}finally{names.forEach((n,i)=>saved[i]?Object.defineProperty(globalThis,n,saved[i]):delete globalThis[n]);}}
function setup(kind,runtime){
 const env=runtime.environment,module=runtime.module,heap=()=>env?env.memory.HEAPU8:module.HEAPU8;
 let u;if(env)u=env.requireGlobal('u');else for(let i=0;i<module._full_global_count();i++){let p=Number(module._full_global_name(i)),end=p;while(heap()[end])end++;if(Buffer.from(heap().slice(p,end)).toString()==='u')u=Number(module._full_global_address(i));}
 assert.ok(u,'actual MAIN hero');const v=new DataView(heap().buffer),x=v.getInt16(u+records.you.fields.ux.offset,true),y=v.getInt16(u+records.you.fields.uy.offset,true);
 steps[kind].push({label:'genuine MAIN startup',world:worldGraph(runtime)});
 if(poison){v.setInt32(u+records.you.fields.uhp.offset,1,true);steps[kind].push({label:'controlled wounded hero',world:worldGraph(runtime)});}
 const literal=value=>{if(env)return env.services.literal(value);const bytes=Buffer.from(value+'\0'),p=Number(module._malloc(BigInt(bytes.length)));heap().set(bytes,p);return BigInt(p);};
 const reason=poison?literal('blast'):null,killer=poison?literal('blast of poison gas'):null;
 for(let i=0;i<8;i++){
  attempts[kind]++;
  if(poison){if(env)pure(()=>env.resolve('poisoned')(reason,0,killer,1,0));else module._poisoned(reason,0,killer,1,0);}
  else if(env)pure(()=>env.resolve('buzz')(beamType,1,x,y,0,0));else module._buzz(beamType,1,x,y,0,0);
  steps[kind].push({label:'survived original '+scenario+' call '+i,world:worldGraph(runtime)});
 }
}
const c=await runFullOriginalC(directory,{...input,observeRuntime:r=>native=r,authorKey({consumed}){
 if(busy)return 27;if(consumed<3)return input.keys.charCodeAt(consumed);
 if(!prepared){prepared=true;busy=true;try{setup('c',native);}finally{busy=false;}}return undefined;
}});
assert.deepEqual(c.status,{kind:'exited',code:0},'actual native death and termination completed');
prepared=false;busy=false;
const j=runStandaloneProgram(directory+'/assets',{...input,keys:c.input.keys,observeRuntime:r=>{
 actual=r;const keyOwner=r.environment.start('terminal-key-input'),read=keyOwner.namespace.teleport_getch;let inputs=0;
 keyOwner.namespace.teleport_getch=(...args)=>{if(busy)return read(...args);if(inputs++===3&&!prepared){prepared=true;busy=true;try{setup('js',actual);}finally{busy=false;}}return read(...args);};
}});
assert.deepEqual(j.status,c.status,'pure JS scenario completed');assert.deepEqual(steps.js,steps.c,'every surviving step complete native world');
for(const name of ['consumed','state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(j[name],c[name],'complete '+name);
// C authors the API trigger inside its input observer; JS intercepts just
// before its input observer. The C-only trigger consumes no key. Require that
// exact single boundary and compare every actual consumed input boundary.
assert.equal(c.snapshots.length,j.snapshots.length+1);
assert.equal(c.snapshots[3].keyIndex,3);assert.equal(c.snapshots[3].frameIndex,4);
assert.deepEqual(j.snapshots,[...c.snapshots.slice(0,3),...c.snapshots.slice(4)],'all consumed input boundaries; sole author-only trigger excluded explicitly');
assert.deepEqual(actual.program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'every real terminal boundary');
assert.deepEqual(Object.keys(j.files).sort(),Object.keys(c.files).sort(),'complete surviving file path set');
for(const [path,file]of Object.entries(c.files))assert.equal(j.files[path].bytes,file.bytes,path+' complete persisted bytes');
// The reference lazy-file loader gives existing files0777, whereas the JS
// asset snapshot preserves disk modes. Those initial profiles differ before
// gameplay; this test compares every persisted byte, not mode equivalence.
assert.deepEqual(attempts.js,attempts.c,'same fatal ray attempt');assert.ok(attempts.c>0&&attempts.c<=8);
assert.match(Buffer.from(c.stdout,'base64').toString(),poison?/poison/:disintegration?/disintegrat/:/death ray/,'actual native death cause in terminal output');
if(poison)assert.ok(c.state.hp<1,'original fatal poison actually kills the wounded hero');
fs.mkdirSync('.cache/fatal-zap-production-branches',{recursive:true});fs.writeFileSync('.cache/fatal-zap-production-branches/'+scenario+'.json.gz',gzipSync(JSON.stringify({c,j,steps,attempts,entry:poison?'poisoned':'buzz',beamType:poison?null:beamType,recorderRun:false})));
console.log('PASS: original-C / pure-JS MAIN fatal '+scenario+' path and termination, surviving worlds, consumed input boundaries, RNG logs, TTY and frames; '+attempts.c+' source calls.');
