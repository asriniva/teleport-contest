import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('worm', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/worm-reference.mjs';
import hybridFactory from '../.cache/tu-probes/worm-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.worm,runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
function normalize(m,s){const known=new Map();for(let i=0;i<8;i++)known.set(`0x${BigInt(m._probe_pointer(0,i)).toString(16)}`,`<mon${i}>`);return s.replace(/0x[0-9a-f]+/gi,token=>known.get(token.toLowerCase())??token);}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:normalize(m,text(m,m._probe_trace())),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count(),io:bytes(m,m._probe_pointer(2,0),m._probe_io_length()),position:m._probe_io_position(-1)};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const idx={hero:1,monster_field:2,prop:2,set_time:1}[name];if(idx!==undefined)args[idx]=BigInt(args[idx]);const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],`${name}:${args}`);comparisons++;check();return out[0];}
function reset(s=1){call('reset',s);}
function act(op,i=0,a=0,b=0,c=0,d=0){return call('action',op,i,a,b,c,d);}
function mf(k,v,i=0){call('monster_field',i,k,v);}
function hero(k,v){call('hero',k,v);}
function opt(k,v){call('option',k,v);}
function prop(p,k,v){call('prop',p,k,v);}
function time(slot,v){call('set_time',slot,v);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function fields(prefix,m=modules[0]){return text(m,m._probe_snapshot()).split(';').find(x=>x.startsWith(prefix+':')).split(':').slice(1);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function nodes(m,slot=1){const out=[];for(let i=0;;i++){const p=m._probe_node_pointer(slot,i);if(!p)break;out.push(Number(p));}return out;}
function setup(count=5){reset();mf(0,1);act(1,0,count);}
function geometry(coords,slot=1,owner=0){coords.forEach(([x,y],i)=>call('node',slot,i,x,y,owner));}
function linear(count=5){setup(count);geometry(Array.from({length:count+1},(_,i)=>[20-count+i,10]));mf(9,1);}
function mode(value){call('nhfile',0,value);}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['MAX_NUM_WORMS','COLNO','ROWNO','segmentSize','seg_nseg','seg_wx','seg_wy','PM_LONG_WORM','PM_LONG_WORM_TAIL','PM_HUMAN','NON_PM','MHPMAX','NORMAL_SPEED','HALLUC','HALLUC_RES','WRITING','COUNTING','FREEING','READING'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);

// Segment allocation includes a hidden head; count_wsegs deliberately reports chain length minus one.
for(const count of [-1,0,1,2,11,22,33,40]){setup(count);assert.equal(act(19),BigInt(Math.max(0,count)));assert.equal(act(18),BigInt(Math.max(0,count)*L.segmentSize));assert.equal(nodes(modules[0]).length,Math.max(0,count)+1);const before=modules.map(m=>nodes(m));act(6);assert.equal(modules[0]._probe_free_count(),Math.max(0,count)+1);assert.equal(fields('m0')[0],'0');assert.deepEqual(fields('w1'),['0','0','0']);modules.forEach((m,i)=>assert.ok(before[i].length>0));}
reset();for(let n=1;n<L.MAX_NUM_WORMS;n++){assert.equal(act(0),BigInt(n));mf(0,n);act(1,0,0);}assert.equal(act(0),0n);mode(L.FREEING);act(11);assert.equal(modules[0]._probe_free_count(),L.MAX_NUM_WORMS-1);assert.equal(act(0),1n);
for(const count of [-2,0,1,3])for(const display of [-1,0,1,256,257]){reset();assert.equal(act(20,0,count),count?1n:0n);modules.forEach(m=>{let p=Number(m._probe_pointer(6,0)),i=0;while(p){const v=new DataView(m.HEAPU8.buffer);v.setInt16(p+L.seg_wx,10+i,true);v.setInt16(p+L.seg_wy,10,true);p=Number(v.getBigUint64(p+L.seg_nseg,true));i++;}});check();act(2,0,display);assert.equal(modules[0]._probe_free_count(),count?Math.max(0,count)+1:0);if(count)assert.equal(trace().includes('newsym:'),!!(display<<24>>24));}

// Growth times retain signed long64 values; speed division and HP caps follow the original integer expression.
for(const count of [0,1,10,11,21,22,32,33,60])for(const level of [0,8,255]){setup(count);mf(5,level);mf(1,21);rng([0,0,0]);assert.equal(act(19),BigInt(count));act(4);assert.equal(act(19),BigInt(count+1));assert.equal(fields('w1')[0],'101');assert.ok(Number(fields('m0')[3])>=30);}
// Make the MHPMAX clamp and previous-peak fallback observable, not merely executed.
for(const [level,hp,max,expected] of [[255,499,499,499],[0,11,100,12],[0,20,100,20]]){setup(0);mf(5,level);mf(3,hp);mf(4,max);mf(1,21);rng([0,0,0]);act(4);assert.equal(fields('m0')[3],String(expected));assert.equal(fields('m0')[4],String(max));}
for(const speed of [-3,0,1,3,7,12,24]){setup(2);time(1,1);opt(1,speed);mf(1,21);rng([9,0,0]);act(4);assert.equal(BigInt(fields('w1')[0]),100n+BigInt(Math.trunc(11*L.NORMAL_SPEED/Math.max(speed,1))));}
setup(2);time(1,(1n<<53n)+1n);mf(1,21);act(4);assert.equal(act(19),2n);assert.equal(modules[0]._probe_free_count(),1);assert.equal(fields('w1')[0],String((1n<<53n)+1n));
setup(2);hero(2,(1n<<53n)+1n);time(1,-1n);rng([0,0,0]);act(4);assert.equal(BigInt(fields('w1')[0]),(1n<<53n)+9n);
for(const hp of [1,2,3,30]){setup(1);mf(3,hp);rng([1,1]);act(5);assert.ok(Number(fields('m0')[3])>=1);assert.equal(fields('m0')[4],'30');}
setup(1);act(3,0,1);assert.equal(act(19),0n);const frees=modules[0]._probe_free_count();act(3,0,1);assert.equal(modules[0]._probe_free_count(),frees);

// Attacks skip the hidden head, stop on death, and respect segment distance.
for(const dies of [0,1]){linear(3);hero(0,18);opt(2,dies);assert.equal(act(7),BigInt(dies));assert.equal((trace().match(/attack:/g)||[]).length,dies?1:3);}
linear(3);hero(0,1);assert.equal(act(7),0n);
for(const detection of [-1,0,1,256,257])for(const female of [0,1])for(const tame of [0,1]){linear(2);mf(6,female);mf(7,tame);act(9);act(10,0,detection);assert.equal((trace().match(/glyph:/g)||[]).length,2);}
linear(2);prop(L.HALLUC,0,1);rng([0,1,2]);act(10,0,1);assert.ok(trace().includes('display-rng:'));
linear(2);prop(L.HALLUC,0,1);prop(L.HALLUC_RES,0,1);act(10,0,1);assert.ok(!trace().includes('display-rng:'));

// Cutting transfers the existing malloc nodes; surviving halves have disjoint ownership and reset clone flags.
linear(5);const original=modules.map(m=>nodes(m));time(1,123n);rng([6,0,...Array(12).fill(0)]);act(8,0,17,10,1);assert.equal(fields('m0')[0],'1');assert.equal(fields('m1')[0],'2');assert.equal(fields('m1')[8],'0');assert.equal(fields('m0')[5],'6');assert.equal(fields('m1')[5],'6');assert.equal(fields('w1')[0],'123');assert.equal(fields('w2')[0],'0');modules.forEach((m,i)=>{const a=nodes(m,1),b=nodes(m,2);assert.equal(a.length,3);assert.equal(b.length,3);assert.equal(new Set([...a,...b]).size,6);assert.deepEqual([...a,...b].sort((x,y)=>x-y),original[i].sort((x,y)=>x-y));});comparisons++;
for(const kind of ['no-number','head','bad-roll','tail','missing','low-level','clone-fails','slots-full','mon-moving-hidden']){linear(5);if(kind==='no-number')mf(0,0);if(kind==='low-level')mf(5,2);if(kind==='clone-fails')opt(3,1);if(kind==='slots-full'){for(let n=2;n<L.MAX_NUM_WORMS;n++){mf(0,n,2);act(1,2,0);}}if(kind==='mon-moving-hidden'){hero(3,1);opt(7,0);opt(8,0);opt(3,1);}mf(3,31);rng(kind==='bad-roll'?[0]:[19,0,...Array(30).fill(0)]);act(8,0,kind==='head'?20:kind==='tail'?15:kind==='missing'?55:17,10,kind==='bad-roll'?0:1);if(kind==='clone-fails'||kind==='low-level'||kind==='slots-full')assert.equal(fields('m0')[3],'15');}
linear(3);rng([6,1]);act(8,0,18,10,256);assert.equal(modules[0]._probe_free_count(),0);

// Every node is observable through native coordinates/grid aliases, crossing tests and flipping.
linear(5);for(let x=15;x<=20;x++)assert.equal(act(23,0,x,10),BigInt(21-x));assert.equal(act(23,-1,15,10),0n);assert.equal(act(23,0,15,11),0n);
setup(2);geometry([[11,10],[12,11],[20,10]]);assert.equal(act(22,0,11,11,12,10),1n);assert.equal(act(22,0,12,10,11,11),1n);assert.equal(act(22,0,11,11,11,10),0n);assert.equal(act(22,0,1,1,9,9),0n);
setup(3);geometry([[11,10],[13,10],[12,11],[20,10]]);assert.equal(act(22,0,11,11,12,10),0n);
for(const limits of [[0,20],[32760,32767],[-32768,-32760]]){linear(2);act(24,0,...limits);act(25,0,...limits);act(26);}
linear(3);assert.equal(act(21),1n);hero(4,0);assert.equal(act(21),0n);
linear(3);act(16);assert.equal(modules[0]._probe_free_count(),0);modules.forEach(m=>assert.ok(nodes(m).every(p=>new DataView(m.HEAPU8.buffer).getInt16(p+L.seg_wx,true)===0)));comparisons++;
for(const steps of [0,1,2,100]){setup(5);opt(4,steps);act(17,0,20,10);assert.equal(act(19),BigInt(Math.min(5,steps)));assert.equal(modules[0]._probe_free_count(),Math.max(0,5-steps));}
setup(0);call('node',1,0,30,10,0);act(17,0,20,10);assert.ok(trace().includes('tail segment at'));
linear(3);act(13,0,-1);assert.ok(trace().includes('over another mon'));act(13,0,0);act(14);assert.ok(!trace().includes('mon ('));
linear(3);geometry([[17,10],[18,10],[19,10],[20,10]],1,1);act(13,0,1);act(14);assert.ok(!trace().includes('mon ('));
linear(2);call('node',1,0,18,10,1);act(14);assert.ok(normalize(modules[0],trace()).includes('mon (<mon1>) at seg location is not worm (<mon0>)'));
linear(2);modules.forEach(m=>new DataView(m.HEAPU8.buffer).setBigUint64(Number(m._probe_pointer(3,0))+(18*L.ROWNO+10)*L.pointerSize,0n,true));check();act(14);assert.ok(trace().includes('at seg location is not worm'));
reset();act(14,-1);assert.ok(trace().includes('null monster'));act(14);assert.ok(trace().includes('not a worm'));mf(0,1);act(14);assert.ok(trace().includes('without proper tail'));act(17,0,20,10);assert.ok(trace().includes('without a tail'));act(15);
setup(1);call('node',1,0,-1,10,-1);act(14);assert.ok(trace().includes('not isok'));mf(1,0);act(14);
linear(2);mf(10,1);act(6);assert.equal(fields('m0')[9],String(L.NON_PM));assert.equal(modules[0]._probe_free_count(),3);
reset();act(6);assert.ok(trace().includes('wormno is 0'));

linear(2);hero(0,18);mf(12,0xa5a5a5a500000001n);act(14);assert.ok(trace().includes('0xa5a5a5a500000001'));assert.ok(text(modules[0],modules[0]._probe_snapshot()).includes('rawa5a5a5a500000001'));

// Save/restore uses actual native typed addresses, bytes and frees, not a replacement file parser.
for(const flags of [0,L.COUNTING,L.WRITING,L.FREEING,L.WRITING|L.FREEING]){linear(3);time(1,(1n<<53n)+1n);mode(flags);act(11);if(flags&L.FREEING){assert.equal(modules[0]._probe_free_count(),4);assert.deepEqual(fields('w1'),['0','0','0']);}if(flags&L.WRITING||flags&L.COUNTING)assert.ok(modules[0]._probe_io_length()>0);}
linear(4);time(1,-((1n<<53n)+7n));mf(0,2,1);act(1,1,0);time(2,(1n<<53n)+9n);mode(L.WRITING|L.FREEING);act(11);assert.equal(modules[0]._probe_free_count(),6);mode(L.READING);act(12);assert.equal(act(19),4n);assert.equal(fields('w1')[0],String(-((1n<<53n)+7n)));assert.equal(fields('w2')[0],String((1n<<53n)+9n));assert.equal(modules[0]._probe_io_position(-1),modules[0]._probe_io_length());
// Sfo/Sfi mutate the addressed growth cell then reenter before returning: the live alias must already be visible.
for(const input of [0,1])for(const nested of [0,1]){linear(2);mf(1,21);if(input){mode(L.WRITING|L.FREEING);act(11);mode(L.READING);}else mode(L.WRITING);opt(20,2);opt(22,nested);const before=modules[0]._probe_free_count();act(input?12:11);assert.equal(fields('w1')[0],nested?'1107':'1100');assert.equal(act(19),2n);assert.equal(modules[0]._probe_free_count(),before+1);assert.ok(trace().includes(`after-alias:${nested?1107:1100};`));assert.equal(modules[0]._probe_rng_count(),0);if(nested){assert.ok(trace().includes('same-time-address:1;'));assert.ok(trace().includes('nested-time:1107;'));}}

// Growth/reentry preserves real lists, borrowed cells, map rows and allocator ownership across callbacks.
for(const stage of [1,2,3,4,5,6,7,8,9,10]){linear(3);opt(30,stage);opt(31,stage);const before=modules.map(m=>allocationMetric(m));if(stage===1)act(26);else if(stage===2){time(1,1);mf(1,21);act(4);}else if(stage===3){hero(0,18);act(7);}else if(stage===4){rng([19,0,...Array(30).fill(0)]);act(8,0,18,10,1);}else if(stage===5){act(16);act(17,0,20,10);}else if(stage===6)act(10,0,1);else if(stage===7)act(3,0,1);else if(stage===8||stage===10){mode(L.WRITING);act(11);}else{mode(L.WRITING|L.FREEING);act(11);mode(L.READING);act(12);}assert.ok(trace().includes(`grew:${stage};`),`growth stage ${stage}`);assert.ok(trace().includes('nested-slot:'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));}
setup(1);opt(0,0);mf(1,21);rng([0,0,0]);act(4);assert.ok(trace().includes('@;'));
linear(2);time(1,(1n<<53n)+3n);const held=snapshot(modules[1]);const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(77);other._probe_monster_field(0,0,1n);other._probe_action(1,0,2,0,0,0);assert.equal(other._probe_action(19,0,0,0,0,0),2n);other._probe_action(6,0,0,0,0,0);assert.equal(other._probe_free_count(),3);assert.deepEqual(snapshot(modules[1]),held);comparisons+=3;check();
console.log(`WORM ${referenceLabel}/hybrid differential: ${comparisons} comparisons checked`);
