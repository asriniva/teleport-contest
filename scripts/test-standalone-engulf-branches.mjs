// Real MAIN-created worlds and original combat APIs; no recorded session input.
import fs from 'node:fs';import assert from 'node:assert/strict';
import {gzipSync} from 'node:zlib';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory='.cache/full-original-c-v1',layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};
let native,actual,busy=false,prepared=false,delays=0;const steps={c:[],js:[]},engulfEvents=[];
function pure(fn){const names=['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'],saved=names.map(n=>Object.getOwnPropertyDescriptor(globalThis,n)),deny=()=>{throw Error('Forbidden implementation capability');};for(const name of names)Object.defineProperty(globalThis,name,{configurable:true,value:name==='WebAssembly'?new Proxy({},{get:deny}):deny});try{return fn();}finally{names.forEach((n,i)=>saved[i]?Object.defineProperty(globalThis,n,saved[i]):delete globalThis[n]);}}
function setup(kind,runtime){
 const env=runtime.environment,module=runtime.module,heap=()=>env?env.memory.HEAPU8:module.HEAPU8,view=()=>new DataView(heap().buffer),globals={};
 if(module){const text=p=>{p=Number(p);let end=p;while(heap()[end])end++;return Buffer.from(heap().slice(p,end)).toString();};for(let i=0;i<module._full_global_count();i++)globals[text(module._full_global_name(i))]=Number(module._full_global_address(i));}
 const root=name=>env?env.requireGlobal(name):globals[name];
 const read=(type,p,name)=>{const field=records[type].fields[name];return /\bcoordxy\b/.test(field.ctype)?view().getInt16(p+field.offset,true):view().getInt32(p+field.offset,true);};
 const call=(name,...args)=>env?pure(()=>env.services[name](...args)):module['_'+name](...args);
 const snapshot=label=>steps[kind].push({label,world:worldGraph(runtime)});
 snapshot('genuine MAIN startup');
 assert.equal(call('polymon',layouts.monst.PM_PURPLE_WORM),1,'original purple-worm polymorph');
 snapshot('source polymon');
 const u=root('u'),x=read('you',u,'ux'),y=read('you',u,'uy');
 let position;for(const[dx,dy]of[[1,0],[-1,0],[0,1],[0,-1],[1,1],[-1,-1],[1,-1],[-1,1]]){
  if(call('goodpos',x+dx,y+dy,env?0:0n,0)){position=[x+dx,y+dy];break;}
 }
 assert.ok(position,'source adjacent monster position');
 const directions=new Map([["1,0",'l'],["-1,0",'h'],["0,1",'j'],["0,-1",'k'],["1,1",'n'],["-1,-1",'y'],["1,-1",'u'],["-1,1",'b']]);
 assert.equal(call('movecmd',directions.get([position[0]-x,position[1]-y].join(',')).charCodeAt(0),layouts.cmd.MV_WALK),1,'source direction selection');
 let mons=root('mons');
 if(module){const head=root('svl')+records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.monlist.offset,mon=Number(view().getBigUint64(head,true));assert.ok(mon);const data=Number(view().getBigUint64(mon+records.monst.fields.data.offset,true));mons=data-read('permonst',data,'pmidx')*records.permonst.size;}
 const target=Number(call('makemon',env?mons+layouts.monst.PM_TROLL*records.permonst.size:BigInt(mons+layouts.monst.PM_TROLL*records.permonst.size),...position,layouts.makemon.MM_ANGRY));
 assert.ok(target,'source-created hostile troll');snapshot('source makemon');
 let attempts=0;
 const owner=env?pure(()=>env.enableUhitm(layouts)):null,delay=owner?.context.nh_delay_output,you=owner?.context.You;
 if(owner){owner.context.nh_delay_output=(...args)=>{delays++;engulfEvents.push('delay');return delay(...args);};owner.context.You=(...args)=>{if(args[0]==='%s %s%s!'&&args[1]==='swallow'&&args[3]===' whole')engulfEvents.push('swallow');return you(...args);};}
 try{
  // A real miss may occur; keep the deterministic sequence and stop when the
  // original combat kills the target, with bounded attempts and positive text.
  while(attempts<8){call('do_attack',env?target:BigInt(target));attempts++;const dead=read('monst',target,'mhp')<=0;call('dmonsfree');snapshot('source do_attack/dmonsfree '+attempts);if(dead)break;}
 }finally{if(owner){owner.context.nh_delay_output=delay;owner.context.You=you;}}
 steps[kind].push({position,attempts});
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
assert.deepEqual(j.status,c.status,'pure JS scenario completed');assert.deepEqual(steps.js,steps.c,'every setup/attack complete native world');
for(const name of ['state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(j[name],c[name],'complete '+name);
assert.deepEqual(actual.program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'every real terminal boundary');
fs.mkdirSync('.cache/engulf-production-branches',{recursive:true});fs.writeFileSync('.cache/engulf-production-branches/evidence.json.gz',gzipSync(JSON.stringify({c,j,steps,delays,engulfEvents,recorderRun:false})));
assert.match(c.rngLog,/@ gulpum\(uhitm\.c:/,'original C enters gulpum');
assert.deepEqual(engulfEvents,['swallow','delay','delay'],'real source message then both production delays');assert.equal(delays,2);
console.log('PASS: genuine original-C / pure-JS MAIN engulf attack worlds, both RNG logs, TTY and frames; '+delays+' production delay dispatches.');
