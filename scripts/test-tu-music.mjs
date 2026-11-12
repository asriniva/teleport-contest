import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('music', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/music-reference.mjs';
import hybridFactory from '../.cache/tu-probes/music-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.music,runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
const longs={hero:1,monster_field:2,prop:2};
function call(name,...args){args=args.map((v,i)=>longs[name]===i?BigInt(v):v);const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],`${name}:${args}`);check();comparisons++;return out[0];}
function reset(seed=1){call('reset',seed);}
function rng(v){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),v.length).set(v);m._probe_rng_length(v.length);});check();}
function str(name,s){modules.forEach(m=>{const bytes=Buffer.from(s+'\0','latin1'),p=Number(m._malloc(BigInt(bytes.length)));m.HEAPU8.set(bytes,p);m['_probe_'+name](BigInt(p));m._free(p);});check();}
function action(op,a=0,b=0,c=0){return call('action',op,a,b,c);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function fields(prefix){return text(modules[0],modules[0]._probe_snapshot()).split(';').find(s=>s.startsWith(prefix+':')).split(':').slice(1);}
function monster(i,pm,x=11+i,y=10){call('add_monster',i,pm,x,y);}
function mf(i,k,v){call('monster_field',i,k,v);}
function prop(p,k=0,v=1n){call('prop',p,k,v);}
function instr(t,s=3){call('object',t,s);}
function hero(k,v){call('hero',k,v);}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['BUFSZ','PM_HUMAN','PM_SOLDIER','PM_GUARD','PM_GARTER_SNAKE','PM_WATER_NYMPH','PM_GHOUL','PM_MEDUSA','PM_ROCK_PIERCER','PM_ANGEL','PM_SHOPKEEPER','WOODEN_FLUTE','MAGIC_FLUTE','TOOLED_HORN','FIRE_HORN','FROST_HORN','BUGLE','WOODEN_HARP','MAGIC_HARP','LEATHER_DRUM','DRUM_OF_EARTHQUAKE','BELL','ROOM','STONE','POOL','PIT','TT_PIT','TT_BURIEDBALL','LEVITATION','FLYING','FUMBLING','HALF_PHDAM','BLINDED','STUNNED','CONFUSION','HALLUC','HALLUC_RES','DEAF','UNCHANGING','FOUNTAIN','SINK','ALTAR','GRAVE','THRONE','SCORR','CORR','SDOOR','DOOR','D_CLOSED','D_NODOOR','DRAWBRIDGE_UP','DRAWBRIDGE_DOWN','AM_SANCTUM','ECMD_OK','ECMD_TIME','PM_ARCHEOLOGIST'];for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);assert.equal(typeof L.STRAT_WAITMASK,'string');
// Monster wake/scare branches preserve unrelated64bit strategy flags.
for(const pm of [L.PM_HUMAN,L.PM_GHOUL,L.PM_ANGEL,L.PM_MEDUSA])for(const scary of [0,1,256])for(const resistance of [0,1]){reset();monster(0,pm);call('option',1,resistance);mf(0,5,(1n<<63n)|1n);action(0,0,scary);assert.equal(fields('mon0')[4],'0');assert.equal(fields('mon0')[5],'1');assert.equal(fields('mon0')[6],'0');}
reset();monster(0,L.PM_HUMAN);mf(0,5,BigInt(L.STRAT_WAITMASK)| (1n<<60n));action(0,0,1);assert.equal(BigInt(fields('mon0')[13]),1n<<60n);assert.ok(!trace().includes('resist:'));
reset();monster(0,L.PM_MEDUSA);action(0,0,1);assert.ok((BigInt(fields('mon0')[13])&BigInt(L.STRAT_WAITMASK))!==0n);assert.match(trace(),/resist:1/);
for(const distance of [0,1,2,3,9,10,-1,0x7fffffff]){reset();monster(0,L.PM_HUMAN,10,10);monster(1,L.PM_HUMAN,11,10);monster(2,L.PM_HUMAN,13,10);monster(3,L.PM_HUMAN,9,10);mf(3,0,0);action(1,distance);}
for(const accepted of [0,1]){reset();call('option',3,accepted);monster(0,L.PM_HUMAN);monster(1,L.PM_HUMAN,15,10);monster(2,L.PM_HUMAN,11,11);mf(2,0,0);rng(Array(50).fill(0));action(2,25);assert.equal(trace().includes('slept:1'),!!accepted);}
for(const visible of [0,1])for(const hidden of [0,1])for(const peaceful of [0,1]){reset();call('option',24,visible);monster(0,L.PM_GARTER_SNAKE);mf(0,4,hidden);mf(0,1,peaceful);monster(1,L.PM_WATER_NYMPH,12,10);monster(2,L.PM_GARTER_SNAKE,13,10);mf(2,3,0);action(3,10);assert.equal(fields('mon0')[7],'1');assert.equal(fields('mon0')[8],'0');assert.equal(fields('mon0')[9],'0');action(4,10);assert.equal(fields('mon1')[7],'1');assert.equal(fields('mon1')[4],'0');}
for(const deaf of [0,1])for(const heroBugler of [0,1]){reset();hero(7,deaf);monster(0,L.PM_HUMAN);monster(1,L.PM_SOLDIER,50,10);monster(2,L.PM_SOLDIER,51,10);mf(2,2,3);mf(2,1,1);monster(3,L.PM_GUARD,52,10);call('option',24,0);action(5,heroBugler?-1:0);assert.equal(fields('mon1')[4],'0');assert.equal(fields('mon1')[7],'0');assert.equal(fields('mon2')[7],'1');assert.equal(fields('mon3')[4],'1');assert.equal(trace().includes('Norep:'),!deaf);}
for(const swallowed of [0,1])for(const resistant of [0,1]){reset();monster(0,L.PM_HUMAN,10,10);monster(1,L.PM_SHOPKEEPER,11,10);mf(1,7,1);hero(5,swallowed);call('option',1,resistant);action(6,2);assert.equal(trace().includes('tame:1'),!resistant);assert.equal(trace().includes('tame:2'),!swallowed);}
reset();monster(0,L.PM_HUMAN);monster(1,L.PM_HUMAN,12,10);call('option',4,1);action(6,10);assert.match(trace(),/tame:2/); // saved nmon survives native callback mutation.
// Pits: real trap storage, boulder extraction, liquid deletion/requery and deaths.
reset();call('option',5,1);action(7,10,10);assert.ok(!trace().includes('fill:'));
reset();monster(0,L.PM_HUMAN);mf(0,6,1);call('option',6,1);action(7,11,10);assert.equal(fields('mon0')[10],'0');assert.match(trace(),/extract-boulder;flooreffects:/);
for(const deleted of [0,1])for(const dead of [0,1]){reset();monster(0,L.PM_HUMAN);call('option',7,L.POOL);call('option',8,deleted);call('option',9,dead);action(7,11,10);assert.equal(trace().includes('mself:'),!deleted);}
for(const pm of [L.PM_HUMAN,L.PM_ANGEL,L.PM_ROCK_PIERCER])for(const trapped of [0,1])for(const touchDeath of [0,1]){reset();monster(0,pm);mf(0,6,trapped);mf(0,0,1);call('option',10,touchDeath);rng([0]);action(7,11,10);if(pm===L.PM_HUMAN&&!touchDeath)assert.match(trace(),/killed:1/);}
for(const see of [0,1]){reset();monster(0,L.PM_HUMAN,10,10);hero(17,see?2:0);mf(0,0,1);action(7,10,10);}
for(const old of [0,1])for(const lev of [0,1])for(const blocked of [0,1]){reset();if(lev)prop(L.LEVITATION);if(blocked)prop(L.LEVITATION,2);action(7,10,10,old);assert.equal(trace().includes('losehp:'),!lev||!!blocked);}
reset();hero(3,3);hero(4,L.TT_BURIEDBALL);prop(L.LEVITATION);action(7,10,10);assert.match(trace(),/reset-utrap:1/);assert.equal(fields('hero')[4],'0');
for(const blocked of [0,1]){reset();monster(0,L.PM_ANGEL,12,10);hero(16,1);if(blocked)prop(L.FLYING,2);action(7,10,10);assert.equal(trace().includes('losehp:'),!!blocked);}
for(const fumbling of [0,1])for(const dex of [7,8])for(const arch of [0,1])for(const polymorph of [0,1]){reset();hero(3,5);hero(4,L.TT_PIT);if(fumbling)prop(L.FUMBLING);if(polymorph)hero(12,L.PM_GARTER_SNAKE);if(!arch)hero(13,L.PM_HUMAN);call('option',11,dex);rng([1,1,0,0,0,0]);action(7,10,10,1);assert.match(trace(),/jostled around/);}
reset();prop(L.HALF_PHDAM);rng([5,5]);action(7,10,10);assert.match(trace(),/losehp:3:/);reset();action(7,12,10);assert.match(trace(),/newsym:12:10/);
// Every earthquake terrain arm; high altar survives, door state/order and force cap.
for(const terrain of [L.FOUNTAIN,L.SINK,L.ALTAR,L.GRAVE,L.THRONE,L.SCORR,L.CORR,L.ROOM,L.SDOOR,L.DOOR,L.STONE])for(const door of [L.D_NODOOR,L.D_CLOSED]){reset();call('terrain',10,10,terrain,door);call('option',13,1);rng(Array(100).fill(0));action(8,0);if(terrain===L.DOOR&&door!==L.D_NODOOR)assert.match(trace(),/recalc:10:10;newsym:10:10;/);if(terrain===L.SCORR)assert.match(trace(),/unblock:10:10/);}
reset();call('terrain',10,10,L.ROOM,0);call('trap',10,10,L.PIT);hero(3,5);hero(4,L.TT_PIT);rng(Array(20).fill(0));action(8,0);assert.match(trace(),/jostled around/);
reset();call('terrain',10,10,L.ALTAR,0);call('option',12,L.AM_SANCTUM);action(8,0);assert.ok(!trace().includes('maketrap:'));
for(const force of [1,13,14]){reset(6);hero(0,1);hero(1,0);monster(0,L.PM_ROCK_PIERCER,1,0);mf(0,4,1);mf(0,8,1);call('terrain',1,0,L.ROOM,0);action(8,force);assert.match(trace(),/wakeup:1:1/);assert.match(trace(),/seemimic:1/);}
for(const destination of [[5,9,'astral plane'],[5,8,'plane'],[6,7,'sanctum'],[8,1,'puzzle'],[1,2,'dungeon']]){reset();hero(14,destination[0]);hero(15,destination[1]);action(9);assert.equal(text(modules[0],modules[0]._probe_pointer(5)),destination[2]);}
reset();call('option',14,1);action(9);assert.equal(text(modules[0],modules[0]._probe_pointer(5)),'tower');
// All instruments, impaired/deaf modes, charge fallbacks and directions.
const instruments=[L.WOODEN_FLUTE,L.MAGIC_FLUTE,L.TOOLED_HORN,L.FIRE_HORN,L.FROST_HORN,L.BUGLE,L.WOODEN_HARP,L.MAGIC_HARP,L.LEATHER_DRUM,L.DRUM_OF_EARTHQUAKE];
for(const typ of instruments)for(const charges of [-1,0,2])for(const mode of [0,1,2,3,4,7]){reset(typ+mode+4);instr(typ,charges);hero(2,28);if(mode&1)prop(L.STUNNED);if(mode&2)prop(L.CONFUSION);if(mode&4)prop(L.HALLUC);hero(7,mode===7);monster(0,L.PM_GARTER_SNAKE);monster(1,L.PM_WATER_NYMPH,12,10);hero(9,1);action(10);if(charges>0&&mode===0&&[L.MAGIC_FLUTE,L.FIRE_HORN,L.FROST_HORN,L.MAGIC_HARP,L.DRUM_OF_EARTHQUAKE].includes(typ))assert.equal(fields('hero').at(-1),'1');}
for(const typ of [L.FIRE_HORN,L.FROST_HORN])for(const cancel of [0,1])for(const self of [0,1])for(const damage of [0,7]){reset();instr(typ);call('option',15,!cancel);call('option',16,damage);hero(9,self?0:1);action(10);assert.equal(trace().includes('getdir:'),true);assert.equal(trace().includes('known:'),!cancel);if(!cancel&&!self)assert.match(trace(),/ubuzz:.*:1;/);}
reset();instr(L.BELL);assert.equal(action(10),0);assert.match(trace(),/weird instrument/);
reset();instr(L.LEATHER_DRUM);prop(L.DEAF,0,(1n<<53n)+7n);action(10);assert.ok(!trace().includes('timeout:'));
reset();instr(L.WOODEN_FLUTE);prop(L.HALLUC);prop(L.HALLUC_RES);action(10);assert.match(trace(),/You:start playing/);
reset();rng([4,0,1,2,3,4]);assert.equal(action(11),0);const first=fields('hero')[10];assert.equal(first,'ABCDE');prop(L.UNCHANGING);const calls=call('rng_count');assert.equal(action(11),1);assert.equal(call('rng_count'),calls);assert.equal(fields('hero')[10],first);prop(L.UNCHANGING,0,0);action(11);
// Public play guards, passtune input zero-padding and full hint matching behavior.
reset();assert.equal(action(12),L.ECMD_TIME);assert.match(trace(),/You:start playing/);
reset();hero(6,1);assert.equal(action(12),L.ECMD_OK);assert.match(trace(),/underwater/);
for(const typ of [L.WOODEN_FLUTE,L.MAGIC_FLUTE,L.TOOLED_HORN,L.FROST_HORN,L.FIRE_HORN,L.BUGLE]){reset();instr(typ);call('option',17,0);assert.equal(action(12),L.ECMD_OK);assert.match(trace(),/incapable/);}
for(const cancel of [0,1]){reset();call('option',18,'q'.charCodeAt(0));assert.equal(action(12),L.ECMD_OK);assert.match(trace(),/Never mind/);}
for(const notes of ['', 'A','AB','AAAAA','EDCBA','ABCDE','ABCDEF','a h c d e','  a b c d e  ','\x1b'])for(const deaf of [0,1]){reset();hero(14,9);hero(15,2);hero(7,deaf);call('terrain',9,9,L.DRAWBRIDGE_UP,0);call('option',18,'n'.charCodeAt(0));str('input',notes);action(12);if(deaf)assert.ok(!trace().includes('You_hear:'));if(notes==='ABCDEF'&&!deaf){assert.equal(fields('hero')[6],'2');assert.match(trace(),/5 gears turn/);}if(notes==='\x1b')assert.match(trace(),/Never mind/);}
for(const bridge of [L.DRAWBRIDGE_DOWN,L.DRAWBRIDGE_UP]){reset();hero(14,9);hero(15,2);hero(8,2);call('option',18,'n'.charCodeAt(0));call('option',19,'y'.charCodeAt(0));call('option',20,1);call('option',21,12);call('option',22,11);call('terrain',12,11,bridge,0);action(12);assert.equal(fields('hero')[6],'2');assert.match(trace(),bridge===L.DRAWBRIDGE_DOWN?/closebridge:12:11/:/openbridge:12:11/);}
reset();hero(8,2);call('option',18,'n'.charCodeAt(0));call('option',19,'q'.charCodeAt(0));assert.equal(action(12),L.ECMD_OK);
for(const typ of [...instruments,L.BELL]){reset();instr(typ);assert.equal(action(13),L.ins_no_instrument);}
// Real native callbacks reenter a public function and grow memory mid-call.
reset();monster(0,L.PM_HUMAN);mf(0,5,1);call('option',30,1);call('option',31,1);const sizes=modules.map(m=>allocationMetric(m));action(0,0,1);assert.match(trace(),/nested;/);assert.match(trace(),/grew;/);modules.forEach((m,i)=>assert.ok(allocationMetric(m)>sizes[i]));
reset();call('option',31,1);instr(L.FIRE_HORN);hero(9,1);action(10);assert.match(trace(),/grew;/);assert.match(trace(),/ubuzz:.*:1;/);
reset();call('option',0,0);monster(0,L.PM_HUMAN);action(2,3);assert.match(trace(),/@;/);
// Actual native song context and private startup state remain isolated per Module.
reset();rng([0,6]);action(11);const before=snapshot(modules[1]),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(1);assert.deepEqual(snapshot(modules[1]),before);other._probe_action(11,0,0,0);assert.deepEqual(snapshot(modules[1]),before);check();
console.log(`MUSIC: ${comparisons} ${referenceLabel}/hybrid monster, pit, quake, instrument, tune, state and RNG-site comparisons checked.`);
