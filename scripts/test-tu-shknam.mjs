import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('shknam', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/shknam-reference.mjs';
import hybridFactory from '../.cache/tu-probes/shknam-hybrid.mjs';
import {createPortedRuntime} from '../js/ported/wasm-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.shknam,runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(p===0n||p===0)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),output:text(m,m._probe_output()),count:m._probe_rng_count(),rng:m._probe_rng_state()>>>0};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
const longs={mbit:[2],hero:[1],prop:[2]};
function call(name,...args){args=args.map((v,i)=>longs[name]?.includes(i)?BigInt(v):v);const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],`${name}(${args})`);check();comparisons++;return r[0];}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function act(op,a=0,b=0,c=0,d=0){return call('action',op,a,b,c,d);}
function name(i,s){modules.forEach(m=>{const bytes=Buffer.from(s+'\0','latin1'),p=Number(m._malloc(BigInt(bytes.length)));m.HEAPU8.set(bytes,p);m._probe_name(i,BigInt(p));m._free(p);});check();}
function fields(key){return text(modules[0],modules[0]._probe_snapshot()).split(';').find(s=>s.startsWith(key+':')).split(':').slice(1);}
function mon(i,f){return BigInt(fields('m'+i)[f]);}
function globals(i){return BigInt(fields('globals')[i]);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function out(){return text(modules[0],modules[0]._probe_output());}
function extra(m,i){const p=Number(m._probe_extra_pointer(i));return p?Buffer.from(m.HEAPU8.slice(p,p+Number(m._probe_extra_size()))):null;}
function cell(x,y){return fields('map').join(':').split('/').filter(Boolean).map(s=>s.split(',').map(Number)).find(a=>a[0]===x&&a[1]===y);}
function room(irregular=0,doorx=1,doory=3,type=L.SHOPBASE){call('room',0,2,2,5,5,1,0,irregular,type);call('door',0,doorx,doory);for(let x=2;x<=5;x++)for(let y=2;y<=5;y++)call('cell',x,y,L.ROOM,0,0,L.ROOMOFFSET,-1);call('cell',doorx,doory,L.DOOR,L.D_NODOOR,0,0,-1);}
// Inspect every table and private name-list entry before any source function.
const tableCount=modules[0]._probe_table_count();assert.equal(modules[1]._probe_table_count(),tableCount);assert.ok(tableCount>1);for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),raw=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,raw).toString():Number(BigInt.asIntN(64,raw)),L[k],k);}
for(let row=0;row<tableCount;row++){for(let f=0;f<2;f++)assert.equal(text(modules[1],modules[1]._probe_table_string(row,f)),text(modules[0],modules[0]._probe_table_string(row,f)));for(let f=0;f<6;f++)for(let slot=0;slot<9;slot++)assert.equal(modules[1]._probe_table_value(row,f,slot),modules[0]._probe_table_value(row,f,slot));comparisons++;}
for(let list=0;list<11;list++){const count=modules[0]._probe_list_count(list);assert.equal(modules[1]._probe_list_count(list),count);for(let i=0;i<=count;i++){assert.equal(text(modules[1],modules[1]._probe_list_name(list,i)),text(modules[0],modules[0]._probe_list_name(list,i)));comparisons++;}}
function catalogueAliases(m){const pointers=[];for(let row=0;row<tableCount;row++)for(let f=0;f<2;f++)pointers.push(m._probe_table_string(row,f));for(let list=0;list<11;list++){pointers.push(m._probe_list_pointer(list));for(let i=0;i<=m._probe_list_count(list);i++)pointers.push(m._probe_list_name(list,i));}const seen=new Map();return pointers.map(p=>{if(p===0n)return -1;const k=p.toString();if(!seen.has(k))seen.set(k,seen.size);return seen.get(k);});}
assert.deepEqual(catalogueAliases(modules[1]),catalogueAliases(modules[0]));comparisons++;
reset();for(const k of ['NUM_OBJECTS','MAXOCLASSES','SHOPBASE','ROOMOFFSET','ROOM','DOOR','SDOOR','D_NODOOR','D_ISOPEN','D_LOCKED','D_TRAPPED','HALLUC','TIN','CORPSE','EGG','PM_LICHEN','PM_HUMAN','PM_SHOPKEEPER','PM_SMALL_MIMIC','SPE_NOVEL'])assert.ok(Number.isSafeInteger(L[k]),k);
// Actual native allocation lifecycle: reuse clears all bytes and parent ids,
// free releases only eshk, preserves mextra, and repeated free is a no-op.
act(6);assert.equal(call('free_count'),0);act(5);const pointers=modules.map(m=>m._probe_extra_pointer(0));modules.forEach(m=>m._probe_extra_poison(0,0xa5));call('mbit',0,4,0xffffffffn);act(5);modules.forEach((m,i)=>assert.equal(m._probe_extra_pointer(0),pointers[i]));modules.forEach(m=>{const b=extra(m,0);const nonzero=b.reduce((a,v)=>a+(v!==0),0);assert.equal(nonzero,4);});call('mbit',0,1,1);act(6);assert.equal(call('free_count'),1);assert.equal(mon(0,3),0n);modules.forEach(m=>assert.equal(m._probe_extra_pointer(0),0n));act(6);assert.equal(call('free_count'),1);act(5);modules.forEach(m=>assert.notEqual(m._probe_extra_pointer(0),0n));assert.equal((trace().match(/new-extra;/g)||[]).length,1);assert.equal(call('free_count'),1);act(6);assert.equal(call('free_count'),2);
// Every catalogue type plus actual tin/corpse payload variants.
for(let type=0;type<L.NUM_OBJECTS;type++){reset();call('obj',type,L.PM_LICHEN,0);act(0,0,0,type);act(0,0,1,type);}
for(const type of [L.TIN,L.CORPSE])for(const pm of [L.NON_PM,L.PM_LICHEN,L.PM_HUMAN,L.NUMMONS])for(const spe of [0,1,2,-1]){reset();call('obj',type,pm,spe);const actual=act(0,0,1,0);if(type===L.TIN&&pm===L.NON_PM)assert.equal(actual,spe===1?1:0);}
reset();rng([0]);const first=act(1);assert.equal(act(0,0,0,first),1);const bound=Number(trace().match(/rnd:(\d+):/)[1]);let tinRoll=-1;for(let roll=0;roll<bound;roll++){reset();rng([roll]);const type=act(1);if(type===L.TIN)tinRoll=roll;assert.equal(act(0,0,0,type),1);}assert.ok(tinRoll>=0);reset();rng([tinRoll]);act(2,4,5);assert.match(trace(),/tin:/);reset();call('option',1,1);rng([tinRoll]);act(2,4,5);assert.ok(!trace().includes('tin:'));
// Each shop's weighted type thresholds, including negative explicit items.
for(let shop=0;shop<tableCount-1;shop++)for(let roll=0;roll<100;roll++){reset();rng([roll]);const selected=act(12,shop);assert.ok(selected!==0||shop===0);}
for(const roll of [0,25,50,99]){reset();rng([roll]);act(2,4,5);assert.match(trace(),/mksobj:/);}
for(let shop=0;shop<tableCount-1;shop++)for(const special of [0,1,256]){reset();call('option',2,0);rng([99,0]);act(3,shop,4,5,special);const name=text(modules[0],modules[0]._probe_table_string(shop,0));if((special&255)&&(name==='rare books'||name==='second-hand bookstore')){assert.equal(globals(5),1n);assert.match(trace(),new RegExp('mksobj:'+L.SPE_NOVEL+':'));}}
for(const fail of [0,1])for(const mkclassFail of [0,1]){reset();call('option',2,10);call('option',3,mkclassFail);call('option',4,fail);rng([0,0]);act(3,0,4,5,0);if(!fail&&!mkclassFail)assert.match(trace(),/make:/);else assert.match(trace(),/mkobj:/);}
// All standard lists, signed64 birthday conversion and uint32 monster ids.
for(let list=0;list<11;list++)for(const birthday of [0n,1n,-1n,1777723200n,(1n<<53n)+1n,(1n<<63n)-1n,-(1n<<63n)]){reset();act(5);call('hero',0,birthday);rng(Array(60).fill(0));act(4,0,list);call('mbit',0,1,1);act(14);assert.ok(out().length>0);}
for(const id of [0n,1n,100n,0xffffffffn]){reset();act(5);call('mbit',0,4,id);call('hero',0,0);act(4,0,9);}
for(let wanted=0;wanted<5;wanted++){reset();act(5);call('hero',0,0);call('mbit',0,4,wanted);act(4,0,11);call('mbit',0,1,1);act(14);assert.equal(out(),['Female','Male','Neutral','Personal','Other'][wanted]);assert.equal(mon(0,2),wanted===0||wanted===3?1n:0n);assert.equal(act(15),wanted>=2?1:0);}
reset();act(5);call('hero',1,2);call('hero',3,1);call('option',5,1);act(4,0,8);call('mbit',0,1,1);act(14);assert.equal(out(),'Izchak');assert.equal(call('rng_count'),0);
// Collisions force fallback lists and eventually the original50-try cap.
reset();act(5);call('hero',0,0);call('mbit',0,4,0);let n=1;for(const list of [12,9])for(let i=0;i<modules[0]._probe_list_count(list);i++){name(n,text(modules[0],modules[0]._probe_list_name(list,i)));call('mbit',n,1,1);n++;}for(const fallback of ['+Dirk','-Lucrezia']){name(n,fallback);call('mbit',n,1,1);n++;}rng(Array(100).fill(0));act(4,0,12);const collisionCalls=call('rng_count');assert.ok(collisionCalls>=45&&collisionCalls<=50);call('mbit',0,1,1);act(14);assert.ok(out()==='Dirk'||out()==='Lucrezia');
for(const halluc of [0,1])for(const over of [0,1]){reset();name(0,'+Izchak');call('mbit',0,1,1);call('option',9,1);if(halluc)call('prop',L.HALLUC,0,1);call('hero',6,over);rng([0,0]);act(14);assert.equal(act(16,0,0),halluc?0:1);assert.equal(act(16,0,1),1);}
reset();act(14);assert.match(trace(),/not a shopkeeper/);reset();name(0,'lowercase');call('mbit',0,1,1);act(13);assert.equal(out(),'Lowercase');
// Door placement, bounds, irregular edge masks and no-door outcomes.
for(const [x,y] of [[1,3],[6,3],[3,1],[3,6],[3,3]]){reset();room(0,x,y);const door=act(7);assert.equal(door,x===3&&y===3?-1:0);}
for(const irregular of [0,1])for(const edge of [0,1]){reset();room(irregular);call('cell',2,3,L.ROOM,0,edge,L.ROOMOFFSET,-1);const result=act(7);assert.equal(result,irregular&&edge?-1:0);}
reset();call('room',0,2,2,5,5,0,0,0,L.SHOPBASE);assert.equal(act(7),-1);assert.equal(act(8),-1);call('hero',7,1);assert.equal(act(8),-1);assert.match(trace(),/Where is shopdoor/);assert.match(trace(),/display:/);
for(const irregular of [0,1])for(const terrain of [L.ROOM,L.CORR])for(const edge of [0,1]){reset();room(irregular);call('cell',3,3,terrain,0,edge,L.ROOMOFFSET,-1);call('option',19,3);assert.equal(act(9,0,L.ROOMOFFSET,0,3),terrain===L.ROOM&&(!irregular||!edge)?1:0);}
// Successful initialization, special equipment, blocked maker, exact room state.
for(let shop=0;shop<tableCount-1;shop++){reset();room(0,1,3,L.SHOPBASE+shop);rng(Array(50).fill(0));assert.equal(act(8,0,shop),0);assert.equal(mon(0,3),1n);assert.equal(mon(0,4),1n);assert.equal(mon(0,5),0n);assert.equal(fields('r0')[8],'1');}
reset();room();call('option',4,1);assert.equal(act(8),-1);
for(const mask of [L.D_NODOOR,L.D_LOCKED,L.D_TRAPPED])for(const secret of [0,1])for(const tribute of [0,1]){reset();room(0,1,3,L.SHOPBASE+9);call('cell',1,3,secret?L.SDOOR:L.DOOR,mask,0,0,-1);call('hero',4,tribute);rng(Array(100).fill(99));act(10,0,9);assert.equal(globals(3),1n);if(mask===L.D_NODOOR)assert.equal(cell(1,3)[3],L.D_ISOPEN);if(mask===L.D_TRAPPED)assert.equal(cell(1,3)[3],L.D_LOCKED);if(tribute){assert.equal(globals(5),1n);assert.equal((trace().match(new RegExp('mksobj:'+L.SPE_NOVEL+':','g'))||[]).length,1);}}
reset();room();call('hero',8,1);rng(Array(100).fill(99));act(10,0,0);assert.match(trace(),/gone:1/);assert.equal(mon(0,1),0n);
// Native makemon reenters neweshk and expands memory before shkinit writes it.
reset();room();call('option',17,1);call('option',18,1);rng(Array(50).fill(0));const sizes=modules.map(m=>allocationMetric(m));act(8);modules.forEach((m,i)=>assert.ok(allocationMetric(m)>sizes[i]));assert.match(trace(),/nested-new;.*grew;/);assert.equal(mon(0,3),1n);modules.forEach(m=>assert.ok(m._probe_extra_pointer(63)!==0n));
// Hundreds of nested vegetarian generation calls must release each scratch
// frame before the next item, rather than accumulating a megabyte of C stack.
reset();call('room',0,2,2,40,18,1,0,0,L.SHOPBASE+10);call('door',0,1,3);for(let x=2;x<=40;x++)for(let y=2;y<=18;y++)modules.forEach(m=>m._probe_cell(x,y,L.ROOM,0,0,L.ROOMOFFSET,-1));check();call('cell',1,3,L.DOOR,L.D_NODOOR,0,0,-1);call('option',20,1);call('option',21,1);act(10,0,10);const deltas=[...trace().matchAll(/callback-stack:(-?\d+);/g)].map(m=>Number(m[1]));assert.ok(deltas.length>600);assert.ok(deltas.every(d=>d===0));
// Saleability across every shop/catalogue type, including custom food payloads.
for(let shop=0;shop<tableCount-1;shop++){reset();name(0,'shopkeeper');call('mbit',0,1,1);modules.forEach(m=>{const p=Number(m._probe_extra_pointer(0));new DataView(m.HEAPU8.buffer).setInt32(p+L.eshk_shoptype,L.SHOPBASE+shop,true);});for(let type=0;type<L.NUM_OBJECTS;type+=7){call('obj',type,L.PM_LICHEN,0);act(11);}}
reset();call('option',0,0);rng([0]);act(12);const saved=snapshot(modules[0]);modules[1]._probe_hero(0,1n);assert.deepEqual(snapshot(modules[0]),saved);reset();
console.log(`SHKNAM: ${comparisons} ${referenceLabel}/hybrid shop catalogue, names, stock, geometry, allocation and RNG-site comparisons checked.`);
