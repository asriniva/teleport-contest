import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('steal', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/steal-reference.mjs';
import hybridFactory from '../.cache/tu-probes/steal-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.steal,runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),output:Buffer.from(m.HEAPU8.slice(Number(m._probe_output()),Number(m._probe_output())+L.BUFSZ+32)),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
const longs={obj:[2],obit:[2],mbit:[2],hero:[1],prop:[2],action:[3,4]};
function call(name,...args){args=args.map((v,i)=>longs[name]?.includes(i)?BigInt(v):v);const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],`${name}(${args})`);state();comparisons++;return values[0];}
function reset(seed=1){call('reset',seed);}
function str(name,value){modules.forEach(m=>{let p=0;if(value!==null){const b=Buffer.from(value+'\0','latin1');p=Number(m._malloc(BigInt(b.length)));m.HEAPU8.set(b,p);}m['_probe_'+name](BigInt(p));if(p)m._free(p);});state();}
function obj(i,type,quan=1n,where=L.OBJ_INVENT){call('obj',i,type,quan,where);}
function inv(indices){indices.forEach((i,n)=>call('next',i,indices[n+1]??-1,0));call('inventory',indices[0]??-1);}
function minv(indices,m=0){indices.forEach((i,n)=>call('next',i,indices[n+1]??-1,0));call('minvent',m,indices[0]??-1);}
function act(op,o=-1,a=0n,b=0n,m=0){return call('action',op,m,o,a,b);}
function equipment(slot,i,mask){call('equipment',slot,i);call('obit',i,7,mask);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function fields(prefix,index,m=modules[0]){const s=text(m,m._probe_snapshot()),entry=s.split(';').find(x=>x.startsWith(prefix+index+':'));return entry.split(':').slice(1);}
function of(i,f){return BigInt(fields('o',i)[f]);}
function mf(i,f){return BigInt(fields('m',i)[f]);}
function hero(f){return text(modules[0],modules[0]._probe_snapshot()).split(';')[0].split(':')[f+1];}
function trace(){return text(modules[0],modules[0]._probe_trace());}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i));assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),L[k],k);}
const required=['BUFSZ','GOLD_PIECE','LONG_SWORD','LEATHER_ARMOR','W_ARM','OBJ_INVENT','OBJ_MINVENT','OBJ_FREE','OBJ_FLOOR','OBJ_DELETED','PM_WOOD_NYMPH','PM_MONKEY','PM_LEPRECHAUN','PM_PURPLE_WORM','PM_COCKATRICE','PM_HUMAN','ART_ORB_OF_DETECTION','BLINDED','CONFLICT','ADORNED','LEVITATION','FLYING'];for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);
// Gold thresholds include i32-before-i64 narrowing and capped large balances.
for(const n of [-2147483649n,-1n,0n,1n,49n,50n,99n,100n,499n,500n,999n,1000n,4999n,5000n,9999n,10000n,2147483646n,2147483647n,1n<<53n,(1n<<63n)-1n]){reset(17);const v=act(0,-1,n);if(n>=0n)assert.ok(v>=0n&&v<=2147483647n);}
reset();assert.equal(act(1),0n);obj(0,L.LONG_SWORD);obj(1,L.GOLD_PIECE,50n);obj(2,L.GOLD_PIECE,80n);inv([0,1,2]);assert.equal(act(1,0),2n);assert.equal(act(1,2),3n);
// Floor coins, floor junk, carried coins, splitting and teleport restrictions.
for(const floor of [0n,25n,1000n])for(const gold of [0n,49n,500n])for(const restricted of [0,1]){reset(21);call('mon',0,L.PM_LEPRECHAUN);call('option',5,restricted);obj(0,L.LONG_SWORD,1n,L.OBJ_FLOOR);call('floor',0);if(floor){obj(1,L.GOLD_PIECE,floor,L.OBJ_FLOOR);call('next',0,1,1);}if(gold){obj(2,L.GOLD_PIECE,gold);inv([2]);}rng([0,0,0]);act(2);if(floor||gold)assert.ok(mf(0,1)>0n);}
reset();obj(0,L.GOLD_PIECE,1000n);inv([0]);rng([0]);act(2);assert.equal(of(0,5),500n);assert.equal(of(31,5),500n);assert.equal(of(31,7),BigInt(L.OBJ_MINVENT));assert.equal(hero(5),'1');
for(const steed of [-1,1])for(const prop of [0,L.LEVITATION,L.FLYING]){reset();obj(0,L.GOLD_PIECE,10n,L.OBJ_FLOOR);call('floor',0);call('hero',12,steed);if(prop)call('prop',prop,0,1);act(2);assert.match(trace(),/snatches some gold/);}
// Responsiveness distinguishes exact reason prefixes and sign of multi.
for(const multi of [-2147483648,-1,0,1,2147483647])for(const why of [null,'','frozen','frozen solid','Frozen','paralyzed','paralyzed by magic','paralyze','asleep'])for(const kind of [0,7,8]){reset();call('hero',0,multi);str('reason',why);if(kind)call('option',kind,1);const v=act(4);if(multi>=0)assert.equal(v,0n);}
reset();call('hero',0,-((1n<<53n)+1n));str('reason','paralyzed forever');assert.equal(act(4),1n);assert.equal(hero(0),'-9007199254740993');
reset();call('hero',20,1);call('hero',2,200);act(3);assert.equal(call('afternmv',0),99);assert.equal(call('afternmv',1),73);assert.equal(hero(2),'0');
// Every worn removal route, original in_use restoration and boolean narrowing.
const worn=[[0,L.LEATHER_ARMOR,L.W_ARM],[1,L.LEATHER_ARMOR,L.W_ARM],[2,L.CLOAK_OF_PROTECTION,L.W_ARMC],[3,L.LOW_BOOTS,L.W_ARMF],[4,L.LEATHER_GLOVES,L.W_ARMG],[5,L.HELMET,L.W_ARMH],[6,L.SMALL_SHIELD,L.W_ARMS],[7,L.HAWAIIAN_SHIRT,L.W_ARMU],[8,L.LONG_SWORD,L.W_WEP],[9,L.LONG_SWORD,L.W_SWAPWEP],[10,L.LONG_SWORD,L.W_QUIVER],[11,L.HEAVY_IRON_BALL,L.W_BALL],[12,L.IRON_CHAIN,L.W_CHAIN],[13,L.RIN_ADORNMENT,L.W_RINGL],[14,L.RIN_ADORNMENT,L.W_RINGR],[15,L.AMULET_OF_YENDOR,L.W_AMUL],[16,L.BLINDFOLD,L.W_TOOL]];
for(const [slot,type,mask] of worn)for(const inUse of [0,1])for(const unchain of [0,1,256]){reset();obj(0,type);equipment(slot,0,mask);call('obit',0,2,inUse);call('option',9,1);act(5,0,BigInt(unchain));assert.equal(of(0,11),BigInt(inUse));if(slot!==11&&slot!==12)assert.equal(of(0,6),0n);}
for(const mask of [0n,1n<<52n,BigInt(L.W_ARM|L.W_AMUL)]){reset();obj(0,L.LONG_SWORD);call('obit',0,7,mask);act(5,0,1n);}
for(const debug of [0,1]){reset();obj(0,L.LONG_SWORD,1n,L.OBJ_DELETED);call('obit',0,7,L.W_ARM);call('hero',17,123);call('option',31,debug);act(5,0,1n);assert.equal(hero(6),'123');assert.equal(trace().includes('simple:'),Boolean(debug));}
for(const desc of ['a robe (being worn)','an iron chain (attached to you)','the ring (on left hand)','a ring (on right hand)','a sword (alternate weapon; not wielded)','plain words','an \x80 item']){reset();obj(0,L.LONG_SWORD);equipment(8,0,L.W_WEP);str('description',desc);act(15,0);assert.match(trace(),/disarms/);}
// Theft selection, empty inventory, awareness, animal limits and redirects.
for(const near of [0,1])for(const animal of [0,1])for(const blindness of [0,1]){reset();call('option',4,near);call('mon',0,animal?L.PM_MONKEY:L.PM_WOOD_NYMPH);if(blindness)call('prop',L.BLINDED,0,1);act(6,-1,1n);}
reset();obj(0,L.HEAVY_IRON_BALL,1n,L.OBJ_FLOOR);obj(1,L.IRON_CHAIN,1n,L.OBJ_FLOOR);equipment(11,0,L.W_BALL);equipment(12,1,L.W_CHAIN);rng([1]);act(6,-1,1n);assert.equal(fields('e',11)[0],'0');assert.equal(of(1,7),BigInt(L.OBJ_DELETED));
reset();call('hero',14,1);call('hero',15,L.TT_BURIEDBALL);rng([0]);act(6,-1,1n);assert.equal(hero(12),'0');assert.match(trace(),/open-trap:/);
reset();obj(0,L.GOLD_PIECE,500n);inv([0]);assert.equal(act(6,-1,1n),1n);assert.match(trace(),/interested in gold/);
for(const item of [L.LONG_SWORD,L.APPLE,L.LEASH,L.BOULDER,L.CORPSE])for(const animal of [0,1])for(const seen of [0,1]){reset(77);obj(0,item);inv([0]);call('mon',0,animal?L.PM_MONKEY:L.PM_WOOD_NYMPH);call('option',1,seen);if(item===L.LEASH)call('obit',0,9,17);rng([0,0,0,0,0]);const v=act(6,-1,1n);if(item===L.LONG_SWORD){assert.equal(v,1n);assert.equal(of(0,7),BigInt(L.OBJ_MINVENT));assert.equal(mf(0,8),1n);}if(item===L.CORPSE&&!animal)assert.equal(v,-1n);}
for(const target of [0,1,2]){reset();for(let i=0;i<3;i++)obj(i,L.LONG_SWORD);inv([0,1,2]);rng([target]);act(6,-1,1n);assert.equal(of(target,7),BigInt(L.OBJ_MINVENT));}
for(const monkey of [0,1])for(const carrying of [0,1])for(const cursed of [0,1]){reset();obj(0,L.LEATHER_GLOVES);equipment(4,0,L.W_ARMG);inv([0]);call('mon',0,monkey?L.PM_MONKEY:L.PM_WOOD_NYMPH);call('option',13,carrying);call('obit',0,1,cursed);rng([0,0,0,0]);act(6,-1,1n);}
for(const pair of [[13,4],[4,8],[1,2],[7,2],[7,1]]){reset();for(let i=0;i<2;i++){const w=worn.find(x=>x[0]===pair[i]);obj(i,w[1]);equipment(w[0],i,w[2]);}inv([0,1]);rng([0]);act(6,-1,1n);assert.notEqual(of(0,7),BigInt(L.OBJ_MINVENT));}
for(const ring of [13,14]){reset();obj(0,L.RIN_ADORNMENT);equipment(ring,0,ring===13?L.W_RINGL:L.W_RINGR);inv([0]);call('prop',L.ADORNED,1,ring===13?L.LEFT_RING:L.RIGHT_RING);act(6,-1,1n);assert.equal(of(0,7),BigInt(L.OBJ_MINVENT));}
for(const busy of [0,-2])for(const female of [0,1])for(const cursed of [0,1]){reset();obj(0,L.LEATHER_ARMOR);equipment(1,0,L.W_ARM);inv([0]);call('hero',0,busy);call('hero',8,female);call('obit',0,1,cursed);rng([0]);act(6,-1,1n);assert.equal(call('afternmv',0),1);assert.equal(hero(1),'100');assert.equal(of(0,10),BigInt(cursed));call('afternmv',1);assert.equal(of(0,7),BigInt(L.OBJ_MINVENT));assert.equal(hero(1),'0');}
// A dead thief switches callbacks; stale ids and dead/polymorphed/distant thieves.
reset();obj(0,L.LEATHER_ARMOR);equipment(1,0,L.W_ARM);inv([0]);rng([0]);act(6,-1,1n);act(3);assert.equal(call('afternmv',0),2);call('afternmv',1);assert.equal(of(0,7),BigInt(L.OBJ_INVENT));assert.match(trace(),/finish taking off/);
for(const missing of [0,1,2,3,4,5]){reset();obj(0,L.LEATHER_ARMOR);inv([0]);call('hero',1,missing===0?0:100);call('hero',2,missing===1?0:missing===2?999:200);if(missing===3)call('mbit',0,5,0);if(missing===4)call('option',21,0);if(missing===5)call('mbit',0,7,70);act(13);assert.equal(hero(1),'0');assert.equal(hero(2),'0');}
reset();call('hero',1,777);act(14);assert.equal(hero(1),'0');
// Pickup ownership, merge, hidden knowledge, dropped/thrown bookkeeping and light.
for(const tame of [0,1])for(const seen of [0,1])for(const lost of [L.LOST_NONE,L.LOST_THROWN,L.LOST_DROPPED,L.LOST_STOLEN])for(const merge of [0,1]){reset();obj(0,L.LONG_SWORD,3n,L.OBJ_FREE);obj(1,L.LONG_SWORD,4n,L.OBJ_MINVENT);if(merge)minv([1]);call('mbit',0,4,tame);call('option',1,seen);call('option',6,merge);call('obit',0,4,lost);call('obit',0,3,1);call('hero',9,0);call('hero',10,0);assert.equal(act(7,0),BigInt(merge));assert.equal(of(0,12),0n);assert.equal(hero(9),'0');if(merge)assert.equal(of(1,5),7n);}
reset();assert.equal(act(7),1n);for(const slot of [11,12]){reset();obj(0,slot===11?L.HEAVY_IRON_BALL:L.IRON_CHAIN);equipment(slot,0,slot===11?L.W_BALL:L.W_CHAIN);assert.equal(act(7,0),0n);}
for(const held of [0,1])for(const engulf of [0,1]){reset();obj(0,L.LONG_SWORD,1n,L.OBJ_FREE);call('obit',0,0,1);call('option',1,0);call('option',15,1);call('option',20,engulf);if(held){call('hero',11,0);call('hero',21,1);}act(7,0);assert.equal(of(0,9),0n);if(engulf)assert.match(trace(),/snuff:/);}
for(const quantity of [(1n<<53n)+1n,(1n<<63n)-1n]){reset();obj(0,L.LONG_SWORD,quantity,L.OBJ_FREE);act(7,0);assert.equal(of(0,5),quantity);assert.equal(of(0,7),BigInt(L.OBJ_MINVENT));}
// Quest and invocation theft priority, fake exclusion, random choices and layered gear.
for(const property of [4,5,6,7])for(const wiz of [0,1]){reset();const types={4:[L.AMULET_OF_YENDOR,L.FAKE_AMULET_OF_YENDOR],5:[L.BELL_OF_OPENING,L.BELL],6:[L.SPE_BOOK_OF_THE_DEAD],7:[L.CANDELABRUM_OF_INVOCATION]}[property];types.forEach((t,i)=>obj(i,t));inv(types.map((_,i)=>i));call('hero',property,1);call('mbit',0,2,wiz);rng([1]);act(8);assert.ok(mf(0,1)>0n);}
for(const count of [0,1,2,3]){reset();for(let i=0;i<count;i++){obj(i,L.LONG_SWORD);call('obit',i,8,L.ART_ORB_OF_DETECTION+i);}inv(Array.from({length:count},(_,i)=>i));rng([1]);act(8);if(count)assert.ok(mf(0,1)>0n);}
for(const topology of ['shirt','ring']){reset();const slots=topology==='shirt'?[7,1,2]:[13,4,8,9];slots.forEach((slot,i)=>{const w=worn.find(x=>x[0]===slot);obj(i,w[1]);equipment(slot,i,w[2]);});inv(slots.map((_,i)=>i));call('obit',0,8,L.ART_ORB_OF_DETECTION);if(topology==='ring')call('hero',3,1);act(8);assert.equal(of(0,7),BigInt(L.OBJ_MINVENT));const order=[...trace().matchAll(/off:(\d+):/g)].map(x=>Number(x[1]));assert.deepEqual(order,topology==='shirt'?[3,2,1]:[4,3,2,1]);}
// Absorption early guards, carried/free cases, multiplicity and native visibility.
for(const cls of [0,1])for(const resist of [0,1])for(const touch of [0,1])for(const carried of [0,1])for(const see of [0,1]){reset();obj(0,cls?L.ROCK:L.LONG_SWORD,see?2n:1n,carried?L.OBJ_INVENT:L.OBJ_FREE);if(carried)inv([0]);call('option',16,resist);call('option',17,touch);call('option',3,see);act(9,0,30n,50n);if(!cls&&!resist&&touch)assert.equal(of(0,7),BigInt(L.OBJ_MINVENT));}
// Dropping maintains saved wear masks and handles shop saddle ownership/death.
for(const dead of [0,1])for(const tame of [0,1])for(const effects of [0,1])for(const verbose of [0,1]){reset();obj(0,L.SADDLE,1n,L.OBJ_MINVENT);call('obit',0,7,L.W_SADDLE);minv([0]);call('mbit',0,4,tame);call('mbit',0,5,dead?0:20);call('option',18,1);call('hero',18,17);call('option',19,effects);act(10,0,BigInt(verbose));assert.equal(mf(0,1),0n);assert.equal(of(0,7),BigInt(effects?L.OBJ_DELETED:L.OBJ_FLOOR));if(tame)assert.equal(of(0,12),1n);}
for(const migrating of [0,1]){reset();obj(0,L.LONG_SWORD,1n,L.OBJ_MINVENT);obj(1,L.AMULET_OF_YENDOR,1n,L.OBJ_MINVENT);obj(2,L.LONG_SWORD,1n,L.OBJ_MINVENT);call('obit',2,8,1);minv([0,1,2]);if(migrating)call('mbit',0,7,0);act(11);assert.equal(mf(0,1),1n);assert.equal(of(0,0),0n);}
for(const guard of [0,1])for(const pet of [0,1,256])for(const show of [0,1]){reset();obj(0,L.GOLD_PIECE,50n,L.OBJ_MINVENT);obj(1,L.LONG_SWORD,1n,L.OBJ_MINVENT);obj(2,L.LEATHER_ARMOR,1n,L.OBJ_MINVENT);call('obit',2,7,L.W_ARM);minv([0,1,2]);call('mbit',0,3,guard);act(12,-1,BigInt(show),BigInt(pet));if((pet&255)!==0)assert.equal(mf(0,1),3n);else assert.equal(mf(0,1),0n);if(guard)assert.equal(of(0,7),BigInt(L.OBJ_DELETED));}
// Native inventory callback reenters an imported function and grows memory.
reset();obj(0,L.LONG_SWORD,1n,L.OBJ_FREE);call('hero',0,-1);str('reason','frozen solid');call('option',29,1);call('option',30,1);call('option',15,1);call('option',20,1);const before=modules.map(m=>allocationMetric(m));act(7,0);modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));assert.match(trace(),/nested:1;grow;snuff:11:10;/);
reset();call('option',0,0);act(0,-1,99999n);const saved=snapshot(modules[0]);modules[1]._probe_hero(0,-5n);assert.deepEqual(snapshot(modules[0]),saved);reset();
console.log(`STEAL: ${comparisons} ${referenceLabel}/hybrid inventory, equipment, callback, ownership, gold and RNG-site comparisons checked.`);
