// Actual involuntary level-teleport policy on MAIN-created worlds; no recording.
import fs from 'node:fs';import assert from 'node:assert/strict';
import {gzipSync} from 'node:zlib';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory='.cache/full-original-c-v1',layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};
let native,actual,busy=false,prepared=false,shudders=0;const steps={c:[],js:[]};
function pure(fn){const names=['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'],saved=names.map(n=>Object.getOwnPropertyDescriptor(globalThis,n)),deny=()=>{throw Error('Forbidden implementation capability');};for(const name of names)Object.defineProperty(globalThis,name,{configurable:true,value:name==='WebAssembly'?new Proxy({},{get:deny}):deny});try{return fn();}finally{names.forEach((n,i)=>saved[i]?Object.defineProperty(globalThis,n,saved[i]):delete globalThis[n]);}}
function setup(kind,runtime){
 const env=runtime.environment,module=runtime.module,owner=env?.start('world-position').environment,original=owner?.You1;
 if(owner)owner.You1=(...args)=>{shudders++;return original(...args);};
 try{
  steps[kind].push({label:'genuine MAIN startup',world:worldGraph(runtime)});
  for(let i=0;i<8;i++){
   if(env)pure(()=>env.resolve('level_tele')());else module._level_tele();
   steps[kind].push({label:'source level_tele '+i,world:worldGraph(runtime)});
  }
 }finally{if(owner)owner.You1=original;}
}
const c=await runFullOriginalC(directory,{...input,observeRuntime:r=>native=r,authorKey({consumed}){
 if(busy)return 32;if(consumed<3)return input.keys.charCodeAt(consumed);
 if(!prepared){prepared=true;busy=true;try{setup('c',native);}finally{busy=false;}}return undefined;
}});
assert.deepEqual(c.status,{kind:'input-exhausted'},'native scenario completed');
prepared=false;busy=false;
const j=runStandaloneProgram(directory+'/assets',{...input,observeRuntime:r=>{
 actual=r;const keyOwner=r.environment.start('terminal-key-input'),read=keyOwner.namespace.teleport_getch;let inputs=0;
 keyOwner.namespace.teleport_getch=(...args)=>{if(busy)return 32;if(inputs++===3&&!prepared){prepared=true;busy=true;try{setup('js',actual);}finally{busy=false;}}return read(...args);};
}});
assert.deepEqual(j.status,c.status,'pure JS scenario completed');assert.deepEqual(steps.js,steps.c,'every source teleport complete native world');
for(const name of ['state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(j[name],c[name],'complete '+name);
assert.deepEqual(actual.program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'every real terminal boundary');
assert.ok(shudders>0,'source level_tele reaches the real You1 shudder branch');
fs.mkdirSync('.cache/teleport-production-branches',{recursive:true});fs.writeFileSync('.cache/teleport-production-branches/evidence.json.gz',gzipSync(JSON.stringify({c,j,steps,shudders,recorderRun:false})));
console.log('PASS:8 original-C / pure-JS MAIN level-teleport calls, full worlds/RNG logs/TTY/frames; '+shudders+' real You1 branches.');
