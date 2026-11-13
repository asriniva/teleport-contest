// Actual original mfndpos on MAIN-created monsters beside controlled iron bars.
import fs from 'node:fs';import assert from 'node:assert/strict';
import {gzipSync} from 'node:zlib';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory='.cache/full-original-c-v1',layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};
let native,actual,busy=false,prepared=false;const steps={c:[],js:[]};
function pure(fn){const names=['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'],saved=names.map(n=>Object.getOwnPropertyDescriptor(globalThis,n)),deny=()=>{throw Error('Forbidden implementation capability');};for(const name of names)Object.defineProperty(globalThis,name,{configurable:true,value:name==='WebAssembly'?new Proxy({},{get:deny}):deny});try{return fn();}finally{names.forEach((n,i)=>saved[i]?Object.defineProperty(globalThis,n,saved[i]):delete globalThis[n]);}}
function setup(kind,runtime){
 const env=runtime.environment,module=runtime.module,heap=()=>env?env.memory.HEAPU8:module.HEAPU8,view=()=>new DataView(heap().buffer),globals={};
 if(module){const text=p=>{p=Number(p);let end=p;while(heap()[end])end++;return Buffer.from(heap().slice(p,end)).toString();};for(let i=0;i<module._full_global_count();i++)globals[text(module._full_global_name(i))]=Number(module._full_global_address(i));}
 const root=name=>env?env.requireGlobal(name):globals[name];
 const read=(type,p,name)=>{const field=records[type].fields[name];return /\bcoordxy\b/.test(field.ctype)?view().getInt16(p+field.offset,true):view().getInt32(p+field.offset,true);};
 const call=(name,...args)=>env?pure(()=>env.services[name](...args)):module['_'+name](...args);
 const snapshot=label=>steps[kind].push({label,world:worldGraph(runtime)});
 snapshot('genuine MAIN startup');
 const u=root('u'),x=read('you',u,'ux'),y=read('you',u,'uy');
 let position,bar;const monsterGrid=root('svl')+records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.monsters.offset;
 outer:for(const[dx,dy]of[[1,0],[-1,0],[0,1],[0,-1]]){
  const nx=x+dx,ny=y+dy;
  if(!(nx>1&&nx<78&&ny>0&&ny<19&&call('goodpos',nx,ny,env?0:0n,0)))continue;
  for(const [bx,by]of[[nx+1,ny],[nx,ny+1],[nx-1,ny],[nx,ny-1]]){
   if(bx>0&&bx<79&&by>0&&by<20&&(bx!==x||by!==y)&&!view().getBigUint64(monsterGrid+(bx*21+by)*8,true)){position=[nx,ny];bar=[bx,by];break outer;}
  }
 }
 assert.ok(position,'actual neighbouring monster position');
 let mons=root('mons');
 if(module){const head=root('svl')+records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.monlist.offset,mon=Number(view().getBigUint64(head,true));assert.ok(mon);const data=Number(view().getBigUint64(mon+records.monst.fields.data.offset,true));mons=data-read('permonst',data,'pmidx')*records.permonst.size;}
 const target=Number(call('makemon',env?mons+layouts.monst.PM_RUST_MONSTER*records.permonst.size:BigInt(mons+layouts.monst.PM_RUST_MONSTER*records.permonst.size),...position,layouts.makemon.MM_ANGRY));
 assert.ok(target,'source-created rust monster');snapshot('source makemon');
 const sourceFlags=BigInt(call('mon_allowflags',env?target:BigInt(target)));assert.ok(sourceFlags&BigInt(layouts.mon.ALLOW_BARS),'original permissions naturally allow the rust monster to enter bars');steps[kind].push({sourceFlags:String(sourceFlags)});
 const cell=root('svl')+records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.locations.offset+(bar[0]*21+bar[1])*records.rm.size;
 view().setInt8(cell+records.rm.fields.typ.offset,layouts.mon.IRONBARS);
 snapshot('controlled adjacent iron-bars terrain');
 const output=env?pure(()=>env.memory.calloc(1,layouts.mon.mfpSize)):Number(module._malloc(BigInt(layouts.mon.mfpSize)));
 heap().fill(0,output,output+layouts.mon.mfpSize);
 for(const nondiggable of [0,1])for(const flag of [0n,sourceFlags]){
  const field=records.rm.fields.flags,at=cell+field.offset,mask=((1<<field.bits)-1)<<field.shift;
  view().setUint8(at,(view().getUint8(at)&~mask)|((nondiggable?Number(layouts.mon.W_NONDIGGABLE):0)<<field.shift));
  const result=call('mfndpos',env?target:BigInt(target),env?output:BigInt(output),flag);
  const candidates=Array.from({length:view().getInt32(output+layouts.mon.mfp_cnt,true)},(_,i)=>[view().getInt16(output+layouts.mon.mfp_poss+i*4,true),view().getInt16(output+layouts.mon.mfp_poss+i*4+2,true)]);
  assert.equal(candidates.some(([x,y])=>x===bar[0]&&y===bar[1]),Boolean(flag&&!nondiggable),'actual bar candidate follows permissions and the nondiggable wall flag');
  steps[kind].push({nondiggable,flag:String(flag),result,positions:Buffer.from(heap().slice(output,output+layouts.mon.mfpSize)).toString('hex')});
  snapshot('source mfndpos '+nondiggable+':'+flag);
 }
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
assert.deepEqual(j.status,c.status,'pure JS scenario completed');assert.deepEqual(steps.js,steps.c,'every source setup/position result and complete native world');
for(const name of ['state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(j[name],c[name],'complete '+name);
assert.deepEqual(actual.program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'every real terminal boundary');
fs.mkdirSync('.cache/mon-position-production',{recursive:true});fs.writeFileSync('.cache/mon-position-production/evidence.json.gz',gzipSync(JSON.stringify({c,j,steps,recorderRun:false})));
console.log('PASS: actual original-C / pure-JS MAIN mfndpos with adjacent iron bars, source-derived rust-monster permissions clear/set and nondiggable flags, full candidate/info bytes, complete worlds, RNG logs, TTY and frames.');
