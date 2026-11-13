import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {installNativeIntegerCasts,createNativeAbiCaster,installNativeDependency} from '../js/nethack/native/execution.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {createNativeDescriptorViews} from '../js/nethack/native/descriptor-state.js';
const game=createStandaloneEnvironment(),{transport,ctypes}=game;
const original=Object.fromEntries(['int','uint','short','ushort','char','uchar','boolean'].map(name=>[name,name==='boolean'?transport.char:transport[name]]));
const env={...original};installNativeIntegerCasts(env);
const values=[0,-0,-1,127,128,255,256,32767,32768,65535,65536,2147483647,2147483648,4294967295,4294967296,-4294967297,Number.MAX_SAFE_INTEGER,1e100,1.5,-1.5,NaN,Infinity,-Infinity,0n,-1n,2n**100n+3n,'17','bad',true,false,null,undefined];
const result=fn=>{try{return{value:fn()};}catch(e){return{error:e.constructor};}};
let checks=0;
for(const[name,fn]of Object.entries(original))for(const value of values){assert.deepEqual(result(()=>env[name](value)),result(()=>fn(value)),name+' '+String(value));checks++;}
const pointer=v=>typeof v==='string'?game.services.literal(v):game.address(v),cast=createNativeAbiCaster(ctypes,transport,pointer);
const legacy=(source,v)=>{const type=ctypes.canonical(source);if(type.includes('*'))return pointer(v);if(type==='void')return undefined;if(type==='char'||type==='signed char')return transport.char(v);if(type==='unsigned char')return transport.uchar(v);if(type==='short')return transport.short(v);if(type==='unsigned short')return transport.ushort(v);if(type==='unsigned int')return transport.uint(v);if(ctypes.size(type)===8)return type.startsWith('unsigned')?transport.ulong(v):transport.long(v);return transport.int(v);};
for(const type of ['void','int','unsigned int','char','unsigned char','short','unsigned short','coordxy','boolean','long','unsigned long','char *','struct monst *']){
 const fn=cast(type);assert.equal(fn,cast(type));
 for(const value of values){assert.deepEqual(result(()=>fn(value)),result(()=>legacy(type,value)),type+' '+String(value));checks++;}
}
const owner=nativeStateFor(game),local={},object={address:16};let fallback=0;
installNativeDependency(local,'move','engine_move',owner,()=>++fallback);
assert.equal(local.move(),1);
const direct=v=>v;direct.nativeState=owner;owner.functions.set('engine_move',direct);
assert.equal(local.move,direct);assert.equal(local.move(object),object,'native calls retain stable object identity');
const child=Object.create(local);child.move=()=>23;assert.equal(child.move(),23);assert.equal(local.move,direct,'context helper overrides do not mutate dependency ownership');
const foreign=v=>v;foreign.nativeState={};owner.functions.set('engine_move',foreign);assert.equal(local.move(),2,'another game cannot enter this native state');
const type='struct window_procs',row=ctypes.record(type),field='win_display_nhwindow',at=game.memory.calloc(1,row.size),offset=row.fields[field].offset;
const raw=v=>BigInt.asUintN(64,BigInt(v?.address??v??0));
const views=createNativeDescriptorViews({owner,schemas:{window_procs:{ctype:type,fields:[{name:field,d:{f:true}}]}},records:{window_procs:row},memory:()=>owner.nativeArena.view,addr:game.address,raw,decode:(_d,v)=>text=>({pointer:v,text}),decorate(){},decodedFunctions:true});
const windows=views('window_procs',at),opaque=0xa5abcdef12345678n;
windows[field]=opaque;assert.equal(game.memory.view.getBigUint64(at+offset,true),opaque);
assert.deepEqual(windows[field]('callback text'),{pointer:opaque,text:'callback text'});
assert.notEqual(windows[field],windows[field],'decoded callbacks retain the original per-read projection');
game.memory.grow(game.memory.buffer.byteLength+1);assert.deepEqual(windows[field]('after growth'),{pointer:opaque,text:'after growth'});
console.log(JSON.stringify({passed:true,checks,nativeArguments:true,dependencyReplacement:true,contextOverrides:true,foreignOwnerIsolation:true,decodedCallbacks:true}));
