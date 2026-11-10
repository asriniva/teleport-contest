import assert from './native-test-assert.mjs';
import {DataView,assertStackRestored,memoryCheckpoint,assertMemoryGrowth,referenceBackend,referenceLabel} from './native-test-backend.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {callRegion} from '../js/ported/region-runtime.js';
import * as core from '../js/ported/region.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const own=process.env.TELEPORT_REGION_AUTHOR==='1';
const ref=(await import(own?'../.cache/region-author/reference.mjs':'../.cache/tu-probes/region-reference.mjs')).default,hyb=(await import(own?'../.cache/region-author/hybrid.mjs':'../.cache/tu-probes/region-hybrid.mjs')).default;
let reference=await referenceBackend('region',ref)();
const text=(m,p)=>{p=Number(p);let q=p;while(m.HEAPU8[q])q++;return Buffer.from(m.HEAPU8.slice(p,q)).toString('latin1');};
const measured={};for(let i=0;i<reference._probe_layout_count();i++)measured[text(reference,reference._probe_layout_name(i))]=Number(BigInt.asIntN(64,reference._probe_layout_value(i)));
const L=own?measured:JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).region;if(own)writeFileSync(new URL('../.cache/region-author/layout.json',import.meta.url),JSON.stringify(L,null,2));
const ported={callRegion:(services,name,...args)=>callRegion(services,L,name,...args)},modules=[reference,await hyb({nethackPorted:ported})],stacks=modules.map(m=>m._probe_stack());let checks=0;
const snap=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),frees:m._probe_free_count()});
function check(){assert.deepEqual(snap(modules[1]),snap(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));checks++;}
function call(fn,...args){const out=modules.map(m=>m['_probe_'+fn](...args));assert.deepEqual(out[1],out[0],fn+':'+args);checks++;check();return out[0];}
const reset=()=>call('reset'),rect=(i,a,b,c,d)=>call('rect',i,a,b,c,d),act=(op,a=0,b=0,c=0,d=0)=>Number(call('action',op,a,b,c,d)),field=(i,f,v)=>call('field',i,f,BigInt(v)),opt=(i,v)=>call('option',i,BigInt(v)),hero=(i,v)=>call('hero',i,BigInt(v)),mon=(i,f,v)=>call('set_monster',i,f,BigInt(v)),prop=(n,f,v)=>call('property',n,f,BigInt(v)),roll=v=>call('roll',v),trace=()=>text(reference,reference._probe_trace());
function messages(i,a,b){for(const m of modules){const p=[];for(const s of [a,b]){if(s===null){p.push(0n);continue;}const bytes=Buffer.from(s+'\0','latin1'),at=m._malloc(bytes.length);m.HEAPU8.set(bytes,Number(at));p.push(BigInt(at));}m._probe_messages(i,...p);for(const at of p)if(at)m._free(at);}check();}
function record(i=0){return text(reference,reference._probe_snapshot()).split(';').find(x=>x.startsWith('r'+i+':'));}
reset();assert.equal(act(2,0,0,0),0);act(7);for(const[k,v]of Object.entries(measured))assert.equal(L[k],v,k);assert.equal(core.callbacks.length,2);assert.equal(core.callbacks[0],core.inside_gas_cloud);assert.equal(core.callbacks[1],core.expire_gas_cloud);
// Geometry: exact disjoint rectangle unions, empty defaults and signed coord values.
for(const box of [[1,0,3,2],[10,10,10,10],[-5,-2,2,2],[7,9,3,4],[32767,-32768,32767,-32768]]){reset();rect(0,...box);act(0,0,1);for(const[x,y]of [[box[0],box[1]],[box[2],box[3]],[0,0],[10,10],[3,4]]){assert.equal(act(1,0,x,y),+(x>=box[0]&&x<=box[2]&&y>=box[1]&&y<=box[3]));act(2,0,x,y);}act(7);assert.equal(reference._probe_free_count(),2);}
reset();act(0);assert.ok(record().includes(':0:'));rect(0,8,8,9,9);rect(1,11,10,12,12);act(3,0,0);act(3,0,1);assert.equal(act(2,0,10,10),0);assert.equal(act(2,0,12,12),1);act(7);
// Membership capacity increases by five; duplicate long worms are permitted.
reset();rect(0,7,7,15,15);act(0,0,1);for(let i=0;i<13;i++)act(4,0,i);assert.ok(record().includes(':13:15:'));act(4,0,0);assert.ok(trace().includes('already in region'));mon(1,1,L.PM_LONG_WORM);act(4,0,1);for(let i=0;i<16;i++){act(6,0,i);if(i%2===0)act(5,0,i);}act(24);assert.ok(record().includes('mid:102')===false);act(7);
// A second native list allocation must copy every original region pointer.
reset();rect(0,1,1,2,2);for(let i=0;i<12;i++){act(0,i,1);field(i,12,500+i);act(8,i);}assert.ok(text(reference,reference._probe_snapshot()).startsWith('global:12:20:'));for(let i=0;i<12;i++)assert.ok(record(i).startsWith('r'+i+':1:'));act(9,5);assert.ok(text(reference,reference._probe_snapshot()).startsWith('global:11:20:'));act(10);assert.equal(reference._probe_free_count(),26);
// Active regions, visible blocking/unblocking, attach flags and messages.
for(const blind of [0,1]){reset();rect(0,9,9,11,11);act(0,0,1);field(0,2,1);field(0,12,1234);messages(0,'entered\x80','left');prop(L.BLINDED,0,blind);act(8);assert.equal(act(17),1);assert.equal(act(19,0,10,10),0);act(20,0,10,10);act(18);act(23);act(23,0,1);act(12,0,20,20);act(12,0,10,10);assert.ok(trace().includes('left'));assert.ok(trace().includes('entered'));hero(0,30);act(14);mon(0,3,10);mon(0,4,10);act(15);act(13,0,30,30);act(9);assert.equal(act(17),0);assert.ok(trace().includes('unblock:'));}
for(const attached of [0,1]){reset();rect(0,8,8,12,12);act(0,0,1);field(0,10,attached);field(0,11,1);act(8);act(12,0,30,20);act(13,0,30,20);act(14);act(15,0);act(10);}
// Source lifecycle: expiry thins thick clouds, finite TTL ages, negative TTL remains.
for(const ttl of [-1n,0n,1n,(1n<<53n)+31n])for(const damage of [0,4,5,11]){reset();rect(0,9,9,11,11);act(0,0,1);act(28,0,damage,0);field(0,0,ttl);act(27);act(16);act(11);if(ttl===0n&&damage>=5){assert.ok(record().includes(':1:'));assert.equal(act(16),Math.trunc(damage/2));}act(10);}
// Hero gas effects, resistance/blocked blindness/half damage and fog maintenance.
for(const poison of [0,1])for(const half of [0,1]){reset();act(0);field(0,1,9);prop(L.POISON_RES,0,poison);prop(L.HALF_PHDAM,0,half);roll(8);act(26);if(!poison)assert.ok(trace().includes('lose:'+(half?7:14)));else assert.ok(trace().includes('cough!'));act(7);}
reset();act(0);field(0,0,1);field(0,1,0);hero(3,L.PM_FOG_CLOUD);act(26);assert.ok(record().includes(':6:'));act(7);
for(const resist of [0,1])for(const lifesaved of [0,1])for(const blame of [0,1]){reset();act(0);field(0,1,9);field(0,3,blame?0:L.REG_NOT_HEROS);mon(0,2,1);opt(2,resist);opt(3,lifesaved);act(26,0,1);if(!resist)assert.ok(trace().includes(blame?'kill:1':'monkill:1'));act(7);}
// Both callback indices are genuinely dispatched through in/out region source.
for(const callback of [0,1]){reset();rect(0,8,8,12,12);act(0,0,1);field(0,1,0);for(const f of [4,5,6,7,8,9])field(0,f,callback);act(8);act(12,0,30,20);act(12,0,10,10);act(13,0,30,20);act(13,0,10,10);act(11);act(10);}
// Whole generated clouds: actual shuffled BFS RNG sequence and selection traversal.
for(const size of [-1,0,1,2,7,150,151])for(const bounded of [0,1]){reset();opt(4,bounded);opt(7,5);for(let i=0;i<800;i++)roll(i*13+7);act(29,0,10,10,size);assert.ok(record());act(31);act(32);act(10);}
reset();act(30,0,4);assert.ok(record().includes(':13:'));act(27);act(10);
// Danger/safety decisions, overlapping/permanent clouds and teleport fallback.
for(const count of [0,1,2])for(const teleport of [0,1]){reset();for(let i=0;i<count;i++){rect(0,9,9,11,11);act(0,i,1);act(28,i,4,0);field(i,0,i?0:-1);}opt(5,teleport);act(31);act(32);if(count&&teleport===0)assert.ok(trace().includes('able to breathe'));act(10);}
reset();opt(6,1);act(29,0,10,10,7);assert.ok(trace().includes('rng:rn2:'));assert.ok(!trace().includes('region.c:'));act(10);
// Native typed serialization: every field and full anything bytes, bones remapping,
// signed64 timestamp differences and all update/release mode combinations.
for(const mode of [0,L.COUNTING,L.WRITING,L.WRITING|L.FREEING,L.FREEING]){reset();rect(0,9,8,12,11);act(0,0,1);messages(0,'enter\x80','leave');field(0,0,(1n<<53n)+99n);field(0,1,7);act(4,0,0);act(4,0,1);act(8);act(21,0,mode);if(mode&L.WRITING){assert.ok(reference._probe_io_size()>0n);hero(2,105);act(22,0,L.NHF_BONESFILE);act(23);}act(10);}
for(const ghostly of [0,1]){reset();rect(0,1,1,2,2);act(0,0,1);field(0,0,1);act(8);act(21,0,L.WRITING);hero(2,1000);act(22,0,ghostly?L.NHF_BONESFILE:1);if(!ghostly)assert.equal(act(17),0);act(10);}
// Native callback reentry and actual heap growth retain fresh typed views.
for(const point of [1,2,3,4,5,6]){reset();reference=await referenceBackend('region',ref)();modules[0]=reference;modules[1]=await hyb({nethackPorted:ported});stacks.splice(0,stacks.length,...modules.map(m=>m._probe_stack()));reset();const before=modules.map(memoryCheckpoint);opt(20,point);opt(21,1);rect(0,9,9,11,11);act(0,0,1);field(0,2,1);act(8);if(point===2)act(9);if(point===4){field(0,1,4);act(26);}if(point>=5){act(21,0,L.WRITING);if(point===6)act(22,0,1);}assert.ok(trace().includes('grow:'+point));modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));act(10);}
// Second actual Module uses the same dispatcher object and executes region JS.
reset();rect(0,9,9,11,11);act(0,0,1);act(8);const primary=snap(modules[1]),other=await hyb({nethackPorted:ported});other._probe_reset();other._probe_rect(0,1,1,3,3);other._probe_action(0,0,1,0,0);other._probe_action(8,0,0,0,0);assert.equal(other._probe_action(2,0,2,2,0),1n);assert.deepEqual(snap(modules[1]),primary);other._probe_action(10,0,0,0,0);check();act(10);
console.log('REGION: '+checks+' '+referenceLabel+'/hybrid geometry, callbacks, serialization, ownership, growth and isolation comparisons passed.');
