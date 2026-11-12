// Native C transport versus independently calibrated native JS transport on
// actual SDK libc, plus direct SDK C regex. No game policy is involved.
import fs from 'node:fs';import assert from 'node:assert/strict';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createTerminalDevices} from '../js/nethack/unix-terminal.js';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
const file=process.argv[process.argv.indexOf('--reference')+1];const {default:factory}=await import(pathToFileURL(file)),c=await factory(),raw=await factory();
const layouts=JSON.parse(fs.readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),env=createStandaloneEnvironment();env.enableStdio();
const d=createTerminalDevices(env,layouts),native=createNativeTerminal(),t=env.transport;
const service={moduleKey:env,heap:()=>env.memory.HEAPU8,stackSave:t.stackSave,stackRestore:t.stackRestore,stackAlloc:n=>{const p=t.stackAlloc(n);env.memory.memset(p,0,n);return p;},...d,signal:(s,h)=>BigInt(raw._full_sdk_signal(s,BigInt(h)))};
const p=env.memory.malloc(128);let checks=0;
assert.equal(Number(c._full_abi_native_size()),72);
for(const fill of [0,0xa5,0xff])for(const fd of [0,1,2,99])for(const [op,action]of [[0,0],[2,0],...[-1,0,1,2,3].map(a=>[1,a])]){
 const cp=Number(c._full_abi_buffer(fill));env.memory.memset(p,fill,128);env.libc.errno=73;c._full_abi_errno(73);
 const expected=c._full_abi_op(op,fd,action),actual=op===0?native(service,'tcgetattr',fd,p):op===1?native(service,'tcsetattr',fd,action,p):native(service,'ioctl',fd,0x40087468,p);
 assert.equal(actual,expected,`native op${op} fd${fd} action${action}`);assert.equal(env.libc.errno,c._full_abi_errno(73));assert.deepEqual(env.memory.readBytes(p,128),c.HEAPU8.slice(cp,cp+128));checks+=3;
}
for(const sig of [1,2,3,7,15,29,30,31])for(const fn of [1n,0n,1n,1n,0n]){assert.equal(BigInt(c._full_abi_signal(sig,fn)),BigInt(native(service,'signal',sig,fn)),'native signal '+sig);checks++;}
function str(m,s){const p=BigInt(m._malloc(BigInt(Buffer.byteLength(s)+1)));m.HEAPU8.set(Buffer.from(s+'\0'),Number(p));return p;}
for(const pattern of ['gold (pieces|coins)$','^foo.*bar$','a+','[','a|b','[^x]+','^a$'])for(const text of ['gold coins','foobar','foo\nbar','aaa','x','b','a\nb'])for(const flags of [5,9]){
 const a=str(c,pattern),b=str(c,text),mapped=(flags&~12)|((flags&4)?8:0)|((flags&8)?4:0);
 assert.equal(c._full_abi_regex(a,b,flags),c._full_sdk_regex(a,b,mapped),'native regex ABI '+pattern);c._free(a);c._free(b);checks++;
}
console.log('PASS: '+checks+' C native ABI/real SDK comparisons; terminal/signal conversions and opaque C TRE regex.');
