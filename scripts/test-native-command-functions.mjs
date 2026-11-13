import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {createNativeCommandFunctions} from '../js/nethack/native/command-functions.js';
import {createNativeCommandWindowDispatch} from '../js/nethack/native/command-window-callbacks.js';
import {createNativeWindowCallbacks} from '../js/nethack/native/window-callbacks.js';
import abi from '../js/nethack/window-abi.json' with {type:'json'};
const environment=createStandaloneEnvironment(),{functions,ctypes,memory}=environment,owner=nativeStateFor(environment);
const model=createNativeCommandFunctions(environment,owner);let checks=0,fallbacks=0,resolutions=0;
const indirect=functions.indirect,typed=functions.typedCallback;
functions.indirect=(...args)=>{fallbacks++;return indirect(...args);};functions.typedCallback=(...args)=>{resolutions++;return typed(...args);};
const native=()=>7;Object.assign(native,{nativeState:owner,nativeDirect:true});
environment.register('command-function-test',{native},environment.services);
const token=environment.functionPointer('native','i'),cell=model.view(token);
assert.equal(cell,model.view(Number(token)));assert.equal(cell.address,token);assert.equal(BigInt(cell),token);assert.ok(cell==token);assert.equal(model.view(0),0);checks+=5;
assert.equal(cell(),7);assert.equal(fallbacks,0,'cold native symbol starts its real module without generic dispatch');checks+=2;
const live=memory.live.size,oldResolutions=resolutions;
assert.equal(cell(),7);assert.equal(cell(),7);assert.equal(fallbacks,0,'initialized native body bypasses pointer dispatch');assert.equal(resolutions,oldResolutions,'function identity is stable');assert.equal(memory.live.size,live);checks+=5;
const entry=environment.start('command-function-test'),old=entry.namespace.native;
const next=()=>11;Object.assign(next,{nativeState:owner,nativeDirect:true});entry.namespace.native=next;assert.equal(cell(),11);checks++;
entry.namespace.native=()=>13;assert.equal(cell(),13);assert.equal(fallbacks,1,'live replacement by legacy body retains C boundary');checks+=2;
entry.namespace.native=old;assert.equal(cell(),7);checks++;
for(const signature of ['v','vi','ii','j']){const other=functions.functionPointer(native,signature),value=model.view(other);assert.equal(BigInt(value),other);assert.throws(()=>value(),/Unknown or incompatible C callback/);checks+=2;}
for(const value of [99999999n,1n<<63n]){const unknown=model.view(value);assert.equal(BigInt(unknown),value);assert.throws(()=>unknown(),/Unknown or incompatible C callback/);checks+=2;}
const foreign=()=>17;Object.assign(foreign,{nativeState:{},nativeDirect:true});const foreignToken=functions.functionPointer(foreign,'i');assert.equal(model.view(foreignToken)(),17);assert.equal(fallbacks,2);checks+=2;
const throwing=()=>{throw Error('command callback failure');};Object.assign(throwing,{nativeState:owner,nativeDirect:true});const throwingCell=model.view(functions.functionPointer(throwing,'i'));assert.throws(()=>throwingCell(),/command callback failure/);assert.equal(cell(),7);checks+=2;
// Explicit linker callback overrides must retain their custom behavior.
const overridden=environment.functionPointer('native-explicit','i',()=>19);assert.equal(model.view(overridden)(),19);assert.equal(fallbacks,3);checks+=2;
const table=environment.allocateGlobal('windowprocs',ctypes.size('struct window_procs'));
environment.nativeWindowCallbacks=createNativeWindowCallbacks(environment,owner);
const dispatch=createNativeCommandWindowDispatch(environment,owner);
for(const [field,type]of Object.entries(abi.windows.callbacks)){
 const match=type.match(/^(.*?)\s*\(\*\)\s*\((.*)\)$/),prototype=match[1]+' ('+match[2]+')',args=match[2]==='void'?[]:match[2].split(',').map((_,i)=>i+1);
 const code=t=>{t=ctypes.canonical(t);return t.includes('*')?'p':t==='void'?'v':t==='float'?'f':t==='double'?'d':ctypes.size(t)===8?'j':'i';};
 const sig=[match[1],...match[2].split(',').map(v=>v.trim()).filter(v=>v&&v!=='void')].map(code).join('');
 const callback=(...actual)=>{assert.deepEqual(actual,args);return 23;};Object.assign(callback,{nativeState:owner,nativeDirect:true});
 const id=functions.functionPointer(callback,sig),call=dispatch.bind(field,prototype),before=fallbacks;
 memory.view.setBigUint64(table+ctypes.record('struct window_procs').fields[field].offset,0n,true);
 assert.equal(call(id,...args),23,'captured token survives replacement '+field);assert.equal(fallbacks,before);checks+=2;
 assert.throws(()=>dispatch.bind(field,prototype==='void (void)'?'void (int)':'void (void)'),/Review CMD native window callback/);checks++;
}
assert.throws(()=>dispatch.bind('win_typo','void (void)'),/Review CMD native window callback/);checks++;
console.log(JSON.stringify({passed:true,checks,windowSignatures:46,stableFunctionIdentity:true,nativeDispatch:true,foreignFallback:true,liveReplacement:true}));
