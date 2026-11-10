import {assertStackRestored,allocationMetric,referenceBackend,referenceLabel,memoryCheckpoint,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/hacklib-reference.mjs';
import hybridFactory from '../.cache/tu-probes/hacklib-hybrid.mjs';
import {createPortedRuntime} from '../js/ported/wasm-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
import * as core from '../js/ported/hacklib.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.hacklib,runtime=createPortedRuntime(layouts),referenceFactory=referenceBackend('hacklib',emscriptenReferenceFactory),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function checkedTrace(m){return text(m,m._probe_trace());}
function check(){assert.equal(text(modules[1],modules[1]._probe_snapshot()),text(modules[0],modules[0]._probe_snapshot()));assert.equal(checkedTrace(modules[1]),checkedTrace(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(name,...args){const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],name);comparisons++;check();return r[0];}
const reset=()=>call('reset'),opt=(k,v)=>call('alloc_option',k,v),act=(op,a=0,b=0,c=0,d=0,n=0)=>Number(call('action',op,a,b,c,d,BigInt(n)));
function input(i,s){for(const m of modules){const b=Buffer.from(s+'\0','latin1'),p=Number(m._malloc(BigInt(b.length)));m.HEAPU8.set(b,p);m._probe_input(i,BigInt(p));m._free(BigInt(p));}check();}
const output=()=>text(modules[0],modules[0]._probe_pointer(2,0));
function bytes(m,k=0,i=0,n=2048){const p=Number(m._probe_pointer(k,i));return Buffer.from(m.HEAPU8.slice(p,p+n));}
function resultBytes(n){const a=modules.map(m=>{const p=Number(m._probe_pointer(1,0));return Buffer.from(m.HEAPU8.slice(p,p+n));});assert.deepEqual(a[1],a[0]);comparisons++;return a[0];}
reset();for(const m of modules)for(let i=0;i<Number(m._probe_layout_count());i++){const k=text(m,m._probe_layout_name(i));assert.equal(Number(m._probe_layout_value(i)),L[k],k);}
assert.equal(core.dm.length,modules[0]._probe_table_count());for(let i=0;i<core.dm.length;i++){for(let j=0;j<5;j++){const x=core.dm[i].sz[j];assert.equal(typeof x==='string'?L[x]:x,Number(modules[0]._probe_table(i,j)));comparisons++;}for(const[j,k]of [[5,'datamodel'],[6,'dmplatform']]){assert.equal(core.dm[i][k],text(modules[0],modules[0]._probe_table(i,j)));comparisons++;}}
// Signed char promotions, every byte, and actual native return widths.
for(let c=0;c<256;c++)for(const op of [2,3,4,5,20])act(op,c,c^32);for(const c of [-2147483648,-257,-129,-128,-1,256,511,2147483647])for(const op of [2,3,4,5,20])act(op,c,65);
const strings=['','a','ABC xyz','  a\t b  ','a\nb\r\n','\t\t','a\r\nb\nTAIL','\xe1\xc1z','one-two three','its'];
for(const op of [6,7,8,9,10,11,12,13,14,17,25,26,29])for(const s of strings){reset();input(0,s);act(op);}reset();act(8,1);assert.equal(Number(modules[0]._probe_pointer(1,0)),0);
for(const s of ['','a','Cat','ABC','x\ny'])for(const t of ['','a','A','Cat','xyz','x\n']){reset();input(0,s);input(1,t);for(const op of [15,16,40,41,46])act(op,5);for(const b of [0,1,128,256])act(15,b);}
for(const s of ['a','you','it','bus','BUS','glass','horse']){reset();input(0,s);act(22);resultBytes(L.BUFSZ);}
for(const s of ['','tip','vie','slither','grease','turn on','take off','mix with','snow','play']){reset();input(0,s);act(23);resultBytes(L.BUFSZ);}
for(const c of [0,1,9,10,27,31,32,64,127,128,129,159,160,255,...Array.from({length:12},(_,i)=>i)]){act(27,c);resultBytes(5);}
// All five visctrl slots cycle while their returned pointers remain native aliases.
const rings=modules.map(()=>[]);for(let i=0;i<10;i++){act(27,65+i);modules.forEach((m,j)=>rings[j].push(m._probe_pointer(1,0)));}for(const ring of rings)for(let i=0;i<5;i++)assert.equal(ring[i],ring[i+5]);
for(const i of [-2147483648,-113,-112,-111,-21,-1,0,1,2,3,4,11,12,13,21,101,2147483647]){act(33,i);act(34,i);resultBytes(13);act(35,i);}
for(const s of ['Hello world','AbC\x81\xfe',''])for(const a of [0,1,2,5,20]){reset();input(0,'aBc');input(1,s);act(19,a);reset();input(0,'aBc');input(1,s);act(21);reset();input(1,s);act(24);}
reset();input(0,'ABC');opt(6,1);act(21);assert.equal(output(),'ABC');
for(const c of [0,32,65,128,255]){reset();input(0,'xy');act(18,c);}
for(const op of [28,30,31,32,42])for(const s of ['','abc abc','a-b_C','abcdef','aaa'])for(const t of ['a','abc','x']){reset();input(0,s);input(1,t);input(2,op===42?'_- ':'ZZ');act(op,op===32?t.length:2,1);}
for(const count of [127,128,129,255,256]){reset();input(0,'a'.repeat(count)+'B');input(1,'a'.repeat(count)+'b');act(41);}
for(const args of [[0,0,3,4],[32767,0,-1,0],[-32768,0,0,0],[65536,1,0,2],[-30000,2,30000,3]])for(const op of [36,37,39])act(op,...args);
for(const n of [-2147483648,-1,0,1,2,3,4,15,16,17,2147395600,2147483647])act(38,n);
for(const n of [0,1,2,0x12345,-1,0x7fffffff])for(const pair of [[0,1],[1,20],[10,30],[3,3]])act(43,n,...pair);
for(const n of [1,2,5,16,64,256])for(const a of [0,1,3]){reset();input(1,'abcdefgh');act(44,a,4,-1,0,n);}reset();input(1,'abc');act(44,0,-12,-1,0,256);assert.ok(bytes(modules[0]).subarray(16).toString('latin1').includes('9007199254740993'));
for(const n of [0,1,4,5,8])for(const u of [-2147483648,-1,0,1,127,128,2047,2048,0xd7ff,0xd800,0xdfff,0xe000,0xffff,0x10000,0x10ffff,0x110000,2147483647]){reset();act(45,u,0,0,0,n);if(n<5)assert.equal(bytes(modules[0])[16],0);}
for(const ret of [0,1,-1]){act(48,ret);for(const row of core.dm){const sz=row.sz.map(x=>typeof x==='string'?L[x]:x);opt(5,sz[4]);act(49,ret,sz[0],sz[1],sz[2],sz[3]);}opt(5,7);act(49,ret,3,7,9,13);}
// Native deterministic sort, exact callback sequence, stability, allocator failure cleanup.
function sortRecords(keys,size=8,offset=16){call('sort_setup',size,offset);for(const m of modules){const p=Number(m._probe_pointer(3,0))+offset;keys.forEach((k,i)=>{m.HEAPU8.fill(0x70+i,p+i*size,p+(i+1)*size);m.HEAPU8[p+i*size]=k;});}check();}
for(const size of [1,3,8,17])for(const mode of [0,1,2,3]){reset();const keys=[3,1,3,2,1,0];sortRecords(keys,size);call('sort_action',6n,BigInt(size),mode,0);assert.equal(modules[0]._probe_alloc_count(0),2);assert.equal(modules[0]._probe_alloc_count(1),2);const p=bytes(modules[0],3,0,8192);assert.deepEqual(keys.map((_,i)=>p[16+i*size]),mode===1?[3,3,2,1,1,0]:mode===2?keys:[0,1,1,2,3,3]);act(0,0,1);}
for(const mask of [1,2,3]){reset();sortRecords([2,1]);opt(0,mask);call('sort_action',2n,8n,0,0);assert.equal(modules[0]._probe_alloc_count(0),2);assert.equal(modules[0]._probe_alloc_count(1),mask===3?0:1);assert.equal(bytes(modules[0],3)[16],2);}
for(const [count,size,mode,nullbase]of [[0n,8n,0,0],[1n,8n,0,0],[2n,0n,0,0],[2n,8n,99,0],[2n,8n,0,1],[(1n<<63n),8n,99,0]]){reset();call('sort_action',count,size,mode,nullbase);assert.equal(modules[0]._probe_alloc_count(0),0);}
for(const kind of [1,2,3]){reset();sortRecords([4,2,3,1]);opt(30,kind);opt(31,kind);const before=modules.map(memoryCheckpoint);call('sort_action',4n,8n,0,0);modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));assert.ok(text(modules[0],modules[0]._probe_trace()).includes('nested:fixture'));
}
// Native file descriptors, including empty EOF, partial final block and OS errors.
for(const size of [0,1,L.BUFSIZ-1,L.BUFSIZ,L.BUFSIZ+1,2*L.BUFSIZ+7]){reset();const data=Uint8Array.from({length:size},(_,i)=>i*37);const handles=modules.map(m=>{m.FS.writeFile('/hacklib-in',data);m.FS.writeFile('/hacklib-out',new Uint8Array());return[m.FS.open('/hacklib-in','r'),m.FS.open('/hacklib-out','w')];});const values=modules.map((m,i)=>m._probe_fd_action(handles[i][0].fd,handles[i][1].fd));assert.equal(values[0],1);assert.equal(values[1],values[0]);assert.equal(text(modules[1],modules[1]._probe_io_trace()),text(modules[0],modules[0]._probe_io_trace()));modules.forEach((m,i)=>{handles[i].forEach(h=>m.FS.close(h));assert.deepEqual(Buffer.from(m.FS.readFile('/hacklib-out')),Buffer.from(data));});check();}
reset();assert.equal(call('fd_action',-1,-1),0);for(const m of modules){
 // Ordinary invalid descriptors retain the real platform errno: Darwin EBADF9,
 // Emscripten musl EBADF8. No cross-platform errno rewriting is performed.
 assert.equal(text(m,m._probe_io_trace()),`read:${L.BUFSIZ}:-1:${m.nativeC?9:8};`);
}
// Native device callbacks deliberately return short transfers and errors. The
// actual libc read/write path, not a JS copy implementation, observes them.
for(const mode of ['short-read','partial-write','read-error','write-error']){
 reset();const outputs=[],devices=[];
 modules.forEach((m,i)=>{let pos=0;const dev=m.FS.makedev(91,i+1),out=[];outputs.push(out);m.FS.registerDevice(dev,{open(){},close(){},read(stream,buffer,offset,length){if(mode==='read-error')throw new m.FS.ErrnoError(29);const amount=Math.min(length,mode==='short-read'?3:7-pos);if(amount<=0)return 0;for(let j=0;j<amount;j++)buffer[offset+j]=++pos;return amount;},write(stream,buffer,offset,length){if(mode==='write-error')throw new m.FS.ErrnoError(29);const amount=mode==='partial-write'?Math.max(0,length-1):length;for(let j=0;j<amount;j++)out.push(buffer[offset+j]);return amount;}});const path='/hacklib-device-'+i;m.FS.mkdev(path,dev);devices.push(m.FS.open(path,'r+'));});
 const returns=modules.map((m,i)=>m._probe_fd_action(devices[i].fd,devices[i].fd));assert.equal(returns[1],returns[0]);assert.equal(returns[0],mode==='short-read'?1:0);assert.deepEqual(outputs[1],outputs[0]);assert.equal(text(modules[1],modules[1]._probe_io_trace()),text(modules[0],modules[0]._probe_io_trace()));if(mode==='short-read')assert.deepEqual(outputs[0],[1,2,3]);modules.forEach((m,i)=>{m.FS.close(devices[i]);m.FS.unlink('/hacklib-device-'+i);});check();
}
// Distinct suffix buffers and stable per-function addresses survive later calls.
reset();input(0,'horse');act(22);const suffixPointers=modules.map(m=>m._probe_pointer(1,0));input(0,'turn off');act(23);modules.forEach((m,i)=>assert.notEqual(m._probe_pointer(1,0),suffixPointers[i]));input(0,'cat');act(22);modules.forEach((m,i)=>assert.equal(m._probe_pointer(1,0),suffixPointers[i]));assert.equal(output(),"cat's");
// One runtime serves two actual Wasm modules; execute JS in the second and preserve the first.
reset();input(0,'primary');act(22);const first=modules.map(m=>text(m,m._probe_snapshot()));const other=await hybridFactory({nethackPorted:runtime});other._probe_reset();const p=Number(other._malloc(16n));other.HEAPU8.set(Buffer.from('secondary\0'),p);other._probe_input(0,BigInt(p));other._probe_action(22,0,0,0,0,0n);assert.equal(text(other,other._probe_pointer(2,0)),"secondary's");other._free(BigInt(p));modules.forEach((m,i)=>assert.equal(text(m,m._probe_snapshot()),first[i]));check();
console.log(`hacklib: ${comparisons} ${referenceLabel}/JS comparisons checked`);
