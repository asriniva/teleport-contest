import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {CMemory} from '../js/services/c-memory.js';
import {createMemoryServices} from '../js/standalone/memory-services.js';
import {createFunctions,CExit} from '../js/standalone/functions.js';
import * as canonical from '../js/isaac64.js';
import {C,R,T} from '../js/ported/c-runtime.js';

const memory=new CMemory({initialBytes:256,maximumBytes:1024*1024}),s=createMemoryServices(memory);
s.defineRecord('pair',{size:16,fields:{x:{offset:0,type:'Int16'},flags:{offset:2,type:'Uint16',bits:3,shift:5},ptr:{offset:8,type:'ptr'}}});
const at=memory.calloc(2,16),a=s.record('pair',at),b=s.record('pair',at+16);
a.x=65535;assert.equal(a.x,-1);s.write('Uint16',at+2,65535);a.flags=2;
assert.equal(s.read('Uint16',at+2),65535-(7<<5)+(2<<5));a.ptr=b;
s.array('pair',at,2)[1]=a;assert.equal(b.x,-1);assert.equal(b.ptr,at+16);
memory.malloc(9000);assert.equal(a.x,-1);a.x=7;assert.equal(s.read('Int16',at),7);
const live=memory.live.size;
assert.throws(()=>s.scoped(()=>{s.stackAlloc(55);s.scoped(()=>{});s.scoped(()=>{s.stackAlloc(22);});throw new Error('unwind');}),/unwind/);
assert.equal(memory.live.size,live);
assert.throws(()=>s.stackRestore({index:0}),/Invalid/);
const foreign=createMemoryServices(memory).stackSave();assert.throws(()=>s.stackRestore(foreign),/Invalid/);
const f=createFunctions(),g=createFunctions(),fn=x=>x+1,id=f.functionPointer(fn,'ii');
assert.equal(f.functionPointer(fn,'ii'),id);assert.equal(f.indirect(id,'ii',7),8);
assert.throws(()=>f.indirect(id,'vi',1),/incompatible/);assert.throws(()=>g.indirect(id,'ii',1),/incompatible/);
assert.equal(f.withJumpScope(scope=>f.longjmp(scope,0)),1);
assert.throws(()=>f.withJumpScope(()=>{throw new Error('real');}),/real/);
assert.throws(()=>f.exit(7),e=>e instanceof CExit&&e.status===7);
const runtime=createStandaloneEnvironment({initialBytes:1024,maximumBytes:1024*1024});
for(const length of [0,1,7,8,2048,2100]) {
    const seed=Uint8Array.from({length},(_,i)=>i*37&255),expected=canonical.isaac64_init(seed),actual=runtime.createIsaac(seed);
    for(let i=0;i<600;i++)assert.equal(actual.next(),canonical.isaac64_next_uint64(expected));
    runtime.memory.malloc(5000);actual.reseed(seed);canonical.isaac64_reseed(expected,seed);
    for(let i=0;i<270;i++)assert.equal(actual.next(),canonical.isaac64_next_uint64(expected));
}
runtime.register('nested',{outer:()=>runtime.call('inner','inner'),throws:()=>{throw new Error('restore');}});
runtime.register('inner',{inner:()=>C.moduleKey});
assert.equal(runtime.call('nested','outer'),runtime.services.moduleKey);
assert.throws(()=>runtime.call('nested','throws'),/restore/);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);

const root=process.env.STANDALONE_REFERENCE_ROOT;
if(!root)throw new Error('STANDALONE_REFERENCE_ROOT must point to existing original C development probes');
const layouts=JSON.parse(fs.readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),layout=layouts.rect;
const {default:factory}=await import(pathToFileURL(root+'/.cache/tu-probes/rect-reference.mjs'));
const original=await factory();
assert.equal(original._probe_context_size(),BigInt(layout.size));
for(const key of ['lx','ly','hx','hy'])assert.equal(original['_probe_offset_'+key](),BigInt(layout[key]));
let random=0;const state=runtime.enableRect(layout,{rn2:n=>{random=(Math.imul(random,1664525)+1013904223)>>>0;return random%n;},impossible:()=>{}});
const fields=['lx','ly','hx','hy'];
const values=v=>fields.map(k=>v[k]);
const read=p=>fields.map(k=>new DataView(original.HEAPU8.buffer).getInt16(Number(p)+layout[k],true));
let comparisons=0;
function compare(){assert.equal(state.rect_cnt,original._probe_count());assert.equal(state.n_rects,original._probe_capacity());for(let i=0;i<state.rect_cnt;i++)assert.deepEqual(values(state.rect[i]),read(Number(original._probe_data())+i*layout.size));assert.equal(C,undefined);assert.equal(R,undefined);comparisons++;}
function box(v){const p=runtime.memory.calloc(1,layout.size),q=original._malloc(BigInt(layout.size)),r=runtime.record('NhRect',p);fields.forEach((k,i)=>{r[k]=v[i];new DataView(original.HEAPU8.buffer).setInt16(Number(q)+layout[k],v[i],true);});return{p,r,q};}
for(let trial=0;trial<70;trial++) {
    random=trial+1;original._probe_seed(random);runtime.call('rect','init_rect');original._probe_init();compare();
    for(let step=0;step<30&&state.rect_cnt;step++) {
        const selected=runtime.call('rect','rnd_rect'),native=original._probe_random();
        assert.deepEqual(values(selected),read(native));
        const [lx,ly,hx,hy]=values(selected),x=lx+(trial*7+step*3)%(hx-lx+1),y=ly+(trial*3+step*5)%(hy-ly+1);
        const cut=box([x,y,Math.min(hx,x+2+trial%5),Math.min(hy,y+1+step%3)]);
        runtime.call('rect','split_rects',selected,cut.r);original._probe_split(BigInt(native),BigInt(cut.q));compare();
        runtime.memory.free(cut.p);original._free(BigInt(cut.q));
    }
}
runtime.call('rect','free_rect');original._probe_free();compare();
console.log(`PASS: standalone memory/layout/stack/identity/unwinding, canonical ISAAC, and ${comparisons} original-C rectangle states.`);
