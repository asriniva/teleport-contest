import {connectNativeDungeonWindows,dungeonWindowFields} from '../js/nethack/native/dungeon-window-callbacks.js';
// Every measured window slot, live byte replacement and opaque fallback.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {parse} from 'acorn';
import metadata from '../js/nethack/address-ports.json' with {type:'json'};
import {connectNativeDisplayWindows,displayWindowFields} from '../js/nethack/native/display-window-callbacks.js';
import abi from '../js/nethack/window-abi.json' with {type:'json'};
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {createNativeWindowCallbacks} from '../js/nethack/native/window-callbacks.js';
const environment=createStandaloneEnvironment(),{ctypes,memory,functions}=environment,owner=nativeStateFor(environment);
const table=environment.allocateGlobal('windowprocs',ctypes.size('struct window_procs'));
let resolutions=0,fallbacks=0,checks=0;
const resolve=functions.typedCallback,indirect=functions.indirect;
functions.typedCallback=(...args)=>{resolutions++;return resolve(...args);};
functions.indirect=(...args)=>{fallbacks++;return indirect(...args);};
const slots=createNativeWindowCallbacks(environment,owner),fields=ctypes.record('struct window_procs').fields;
const code=raw=>{const type=ctypes.canonical(raw);return type.includes('*')?'p':type==='void'?'v':type==='float'?'f':type==='double'?'d':ctypes.size(type)===8?'j':'i';};
for(const [name,type]of Object.entries(abi.windows.callbacks)){
 const match=type.match(/^(.*?)\s*\(\*\)\s*\((.*)\)$/),parameters=match[2].split(',').map(t=>t.trim()).filter(t=>t&&t!=='void');
 const sig=[match[1],...parameters].map(code).join(''),args=parameters.map((_,i)=>i+1),at=table+fields[name].offset;
 const set=fn=>{const token=functions.functionPointer(fn,sig);memory.view.setBigUint64(at,token,true);return token;};
 const call=()=>slots.invoke(name,sig,...args),before=resolutions;
 let calls=0;
 const first=(...actual)=>{assert.deepEqual(actual,args);calls++;return 37;};first.nativeState=owner;first.nativeDirect=true;
 const token=set(first),live=memory.live.size,oldFallbacks=fallbacks;
 assert.equal(call(),37);assert.equal(call(),37);assert.equal(calls,2);
 assert.equal(resolutions,before+1,'unchanged slot resolves once '+name);
 assert.equal(fallbacks,oldFallbacks,'game native identity is called directly '+name);
 assert.equal(memory.live.size,live,'steady dispatch allocates no C bytes '+name);checks+=7;
 const foreign=(...actual)=>{assert.deepEqual(actual,args);return 41;};foreign.nativeDirect=true;foreign.nativeState={};
 set(foreign);assert.equal(call(),41);assert.equal(fallbacks,oldFallbacks+1,'other game remains a boundary '+name);checks+=2;
 const legacy=(...actual)=>{assert.deepEqual(actual,args);return 43;};set(legacy);assert.equal(call(),43);assert.equal(fallbacks,oldFallbacks+2);checks+=2;
 // Unknown, null and wrong-signature tokens must not execute stale state.
 for(const bad of [0n,987654321n,functions.functionPointer(first,sig==='v'?'vi':'v')]){
  memory.view.setBigUint64(at,bad,true);assert.throws(call,/Unknown or incompatible C callback/);checks++;
 }
 memory.view.setBigUint64(at,token,true);assert.equal(call(),37);checks++;
 assert.throws(()=>slots.invoke(name,sig==='v'?'vi':'v',...args),/Incompatible native window callback/);checks++;
 // A callback can replace its own slot and reenter it synchronously.
 const replacement=()=>47;replacement.nativeState=owner;replacement.nativeDirect=true;
 const reentrant=()=>{set(replacement);return call()+1;};reentrant.nativeState=owner;reentrant.nativeDirect=true;
 set(reentrant);assert.equal(call(),48);assert.equal(call(),47);checks+=2;
 const throwing=()=>{throw Error('native callback failure');};throwing.nativeState=owner;throwing.nativeDirect=true;set(throwing);
 assert.throws(call,/native callback failure/);set(first);assert.equal(call(),37);checks+=2;
 memory.grow(memory.buffer.byteLength+1);assert.equal(call(),37,'same function survives arena growth');checks++;
}
assert.throws(()=>slots.invoke('win_typo','v'),/Unknown native window callback/);checks++;
// A captured token must keep the callback selected before argument evaluation,
// even when the installed table changes before dispatch.
const capturedField='win_delay_output',capturedAt=table+fields[capturedField].offset;
const captured=()=>51;captured.nativeState=owner;captured.nativeDirect=true;
const later=()=>53;later.nativeState=owner;later.nativeDirect=true;
const capturedToken=functions.functionPointer(captured,'v'),laterToken=functions.functionPointer(later,'v');
memory.view.setBigUint64(capturedAt,laterToken,true);
assert.equal(slots.invokeCaptured(capturedField,'v',capturedToken),51);assert.equal(slots.invoke(capturedField,'v'),53);checks+=2;
const schema=metadata.ports.display.schema,services={};let legacy=0;
for(const row of schema.callbackCalls)services['indirect'+row.site]=()=>{legacy++;return 59;};
connectNativeDisplayWindows(environment,services,schema);
assert.equal(services.indirect0(capturedToken),59);assert.equal(legacy,1);checks+=2;
environment.nativeWindowCallbacks=slots;
for(const [site,name]of displayWindowFields.entries()){
 const row=schema.callbackCalls[site],sig=[row.ret,...row.types].map(code).join(''),args=row.types.map((_,i)=>i+1);
 const fn=(...actual)=>{assert.deepEqual(actual,args);return 61;};fn.nativeState=owner;fn.nativeDirect=true;
 const token=functions.functionPointer(fn,sig);
 assert.equal(services['indirect'+site](token,...args),61);checks++;
}
assert.equal(legacy,1,'connected display no longer enters fallback');checks++;
assert.throws(()=>connectNativeDisplayWindows(environment,services,{callbackCalls:schema.callbackCalls.slice(1)}),/Review native display window sites/);checks++;
const changed=structuredClone(schema);changed.callbackCalls[3].types[0]='long';
assert.throws(()=>connectNativeDisplayWindows(environment,services,changed),/Review native display window ABI 3/);checks++;
// Guard every compiler call site against its actual source field, rather than
// inferring the field from a signature shared by several callbacks.
for(const source of ['js/ported/display.js','js/nethack/native/address/display.js']){
 const ast=parse(fs.readFileSync(source,'utf8'),{ecmaVersion:'latest',sourceType:'module'}),seen=new Set();
 function visit(n){if(!n||typeof n!=='object')return;if(Array.isArray(n)){n.forEach(visit);return;}
  if(n.type==='CallExpression'&&n.callee.object?.name==='C'&&n.callee.property?.name==='indirect'){
   const site=n.arguments[0].value,read=n.arguments[1];
   assert.equal(read.callee.property.name,'display_read_window_procs_'+displayWindowFields[site]);
   assert.equal(read.arguments[0].object.name,'C');assert.equal(read.arguments[0].property.name,'windowprocs');seen.add(site);checks+=3;
  }
  for(const [key,value]of Object.entries(n))if(!['start','end','loc'].includes(key))visit(value);
 }visit(ast);assert.deepEqual([...seen].sort((a,b)=>a-b),displayWindowFields.map((_,i)=>i));checks++;
}
const dungeonSchema=metadata.ports.dungeon.schema,dungeonServices={};
for(const row of dungeonSchema.callbackCalls)dungeonServices['indirect'+row.site]=()=>{throw Error('dungeon fallback reached');};
connectNativeDungeonWindows(environment,dungeonServices,dungeonSchema);
for(const [site,name]of dungeonWindowFields.entries()){
 const row=dungeonSchema.callbackCalls[site],sig=[row.ret,...row.types].map(code).join(''),args=row.types.map((_,i)=>i+1);
 const fn=(...actual)=>{assert.deepEqual(actual,args);return 67;};fn.nativeState=owner;fn.nativeDirect=true;
 assert.equal(dungeonServices['indirect'+site](functions.functionPointer(fn,sig),...args),67);checks++;
}
const dungeonFields=Object.entries(dungeonSchema.schema).flatMap(([kind,row])=>row.fields.map(f=>({kind,field:f.name})));
for(const source of ['js/ported/dungeon.js','js/nethack/native/address/dungeon.js']){
 const ast=parse(fs.readFileSync(source,'utf8'),{ecmaVersion:'latest',sourceType:'module'}),seen=new Set();
 function visit(n){if(!n||typeof n!=='object')return;if(Array.isArray(n)){n.forEach(visit);return;}
  if(n.type==='CallExpression'&&n.callee.object?.name==='C'&&n.callee.property?.name==='indirect'){
   const site=n.arguments[0].value,read=n.arguments[1];let field;
   if(read.type==='MemberExpression'){assert.equal(read.property.name,'value');assert.equal(read.object.callee.property.name,'field');assert.equal(read.object.arguments[1].value,'window_procs');field=read.object.arguments[2].value;}
   else{const index=Number(read.callee.name.match(/^R(\d+)$/)[1]);assert.equal(dungeonFields[index].kind,'window_procs');field=dungeonFields[index].field;}
   assert.equal(field,dungeonWindowFields[site]);seen.add(site);checks++;
  }
  for(const [key,value]of Object.entries(n))if(!['start','end','loc'].includes(key))visit(value);
 }visit(ast);assert.deepEqual([...seen].sort((a,b)=>a-b),dungeonWindowFields.map((_,i)=>i));checks++;
}
console.log(JSON.stringify({passed:true,callbacks:Object.keys(abi.windows.callbacks).length,checks,resolutions,foreignDispatches:fallbacks}));
