import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('steed', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/steed-reference.mjs';
import hybridFactory from '../.cache/tu-probes/steed-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.steed,runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const idx={object:2,hero:1,prop:2,monster_field:2}[name];if(idx!==undefined)args[idx]=BigInt(args[idx]);const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],`${name}:${args}`);comparisons++;check();return out[0];}
function reset(s=1){call('reset',s);}
function act(op,i=0,a=0,b=0,c=0){return call('action',op,i,a,b,c);}
function obj(i,k,v){call('object',i,k,v);}
function hero(k,v){call('hero',k,v);}
function mf(k,v,i=0){call('monster_field',i,k,v);}
function opt(k,v){call('option',k,v);}
function prop(p,k,v){call('prop',p,k,v);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function fields(prefix,m=modules[0]){return text(m,m._probe_snapshot()).split(';').find(x=>x.startsWith(prefix+':')).split(':').slice(1);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function saddled(){reset();act(3,0,0);}
function mounted(){saddled();mf(25,0);mf(20,10);hero(6,0);}
const reasons=['DISMOUNT_BYCHOICE','DISMOUNT_THROWN','DISMOUNT_KNOCKED','DISMOUNT_FELL','DISMOUNT_POLY','DISMOUNT_ENGULFED','DISMOUNT_BONES','DISMOUNT_GENERIC'];
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['NUMMONS','SADDLE','ROOM','STONE','PM_HUMAN','PM_PONY','PM_WARHORSE','PM_GIANT','PM_GRID_BUG','PM_GIANT_EEL','PM_BAT','PM_RED_DRAGON','PM_GHOST','PM_COCKATRICE','PM_STONE_GOLEM','PM_AMOROUS_DEMON','PM_LONG_WORM','PM_KNIGHT','PM_ROGUE','LEATHER_GLOVES','HIGH_BOOTS','LANCE','PLATE_MAIL','W_SADDLE','W_ARMG','W_ARTI','P_RIDING','P_UNSKILLED','P_BASIC','P_SKILLED','P_EXPERT','CONFUSION','FUMBLING','GLIB','HALLUC','HALLUC_RES','BLINDED','TELEPAT','WOUNDED_LEGS','LEVITATION','FLYING','STEALTH','STONE_RES','HALF_PHDAM','FROMOUTSIDE','I_SPECIAL','TT_PIT','TT_BEARTRAP','TT_WEB','PIT','VIBRATING_SQUARE','BOTH_SIDES','M_AP_FURNITURE','M_AP_OBJECT','MON_FLOOR','MON_MIGRATING','ECMD_OK','ECMD_TIME','ECMD_CANCEL',...reasons];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);

// Classifier input is the original private C dataset versus its JS-owned native representation.
act(1);const classifiers=modules.map(m=>Buffer.from(m.HEAPU8.slice(Number(m._probe_pointer(9,0)),Number(m._probe_pointer(9,0))+7)));
assert.deepEqual(classifiers[1],classifiers[0]);assert.equal(classifiers[0][6],0);comparisons++;
const classifierPointers=modules.map(m=>m._probe_pointer(9,0));
for(let species=0;species<=L.NUMMONS;species++){reset();mf(0,species);act(1);act(4);}
reset();assert.equal(act(1),1n);mf(0,L.PM_HUMAN);assert.equal(act(1),0n);
for(const form of [L.PM_HUMAN,L.PM_GIANT,L.PM_GRID_BUG,L.PM_GHOST])for(const tame of [-1,0,1,127])for(const underwater of [0,1]){reset();mf(4,tame);hero(11,form);hero(5,underwater);act(4);mf(0,L.PM_GIANT_EEL);act(4);}

// Actual inventory ownership, worn masks and the signed leash field survive saddle transfer.
for(const id of [1,0x7fffffff,0x80000000,0xffffffff]){reset();mf(1,id);obj(0,9,1);obj(0,10,1);obj(0,6,L.W_ARMG);assert.equal(act(2),BigInt(L.ECMD_TIME));assert.equal(fields('equipment')[0],'-1');assert.equal(fields('m0')[13],'0');assert.equal(fields('o0')[1],String(L.W_SADDLE));assert.equal(fields('o0')[2],String(id|0));assert.equal(fields('o0')[10],'0');assert.ok(trace().includes('freeinv:0;'));}
for(const supplied of [-1,0]){reset();act(3,0,supplied);assert.equal(fields('m0')[11],String(L.W_SADDLE));assert.equal(fields('o'+(supplied<0?8:0))[1],String(L.W_SADDLE));if(supplied<0)assert.ok(trace().includes('identify:8;'));act(3,0,1);assert.ok(trace().includes('orphaned'));}
reset();mf(0,L.PM_HUMAN);act(3,0,-1);assert.ok(!trace().includes('makeobj:'));act(3,0,0);assert.ok(trace().includes('orphaned'));
for(const kind of ['hands','swallow','water','cancel','self','bounds','absent','invisible','already','amorous','minion','shopkeeper','priest','guard','wizard','nosaddle']){reset();obj(0,9,1);if(kind==='hands')opt(1,0);if(kind==='swallow')hero(4,1);if(kind==='water')hero(5,1);if(kind==='cancel')opt(2,0);if(kind==='self')hero(2,0);if(kind==='bounds')hero(2,-20);if(kind==='absent')mf(25,0);if(kind==='invisible'){opt(5,0);opt(6,0);}if(kind==='already')mf(16,L.W_SADDLE);if(kind==='amorous')mf(0,L.PM_AMOROUS_DEMON);const bit={minion:5,shopkeeper:6,priest:7,guard:8,wizard:9}[kind];if(bit!==undefined)mf(bit,1);if(kind==='nosaddle')mf(0,L.PM_HUMAN);act(2);}
for(const skill of [0,L.P_UNSKILLED,L.P_BASIC,L.P_SKILLED,L.P_EXPERT])for(const tame of [0,1,5])for(const roll of [0,99]){reset();hero(15,skill);mf(4,tame);hero(10,1);mf(3,8);opt(3,11);opt(4,9);rng([roll]);act(2);}
for(const kind of ['knight','cursed','confused','fumbling','glib','gloves','boots']){reset();hero(10,1);mf(4,0);if(kind==='knight')hero(13,L.PM_KNIGHT);if(kind==='cursed')obj(0,1,1);if(kind==='confused')prop(L.CONFUSION,0,1);if(kind==='fumbling')prop(L.FUMBLING,0,1);if(kind==='glib')prop(L.GLIB,0,1);if(kind==='gloves'){obj(1,13,1);opt(9,1);}if(kind==='boots'){obj(1,14,1);opt(9,1);}rng([50]);act(2);}
for(const glove of [0,1])for(const resist of [0,1]){reset();mf(0,L.PM_COCKATRICE);if(glove)obj(1,13,1);if(resist)prop(L.STONE_RES,0,1);act(2);assert.equal(trace().includes('petrify:'),!glove&&!resist);}

// C integer division truncates even when an external signed-byte attribute is negative.
reset();hero(10,1);hero(15,L.P_BASIC);mf(4,0);mf(3,0);opt(3,25);opt(4,-9);rng([25]);act(2);assert.equal(fields('m0')[13],'0');

// Wake/sleep/paralysis and meal termination use real packed fields, including odd half-duration division.
for(const frozen of [0,1,2,3,4,5,126,127])for(const asleep of [0,1])for(const canMove of [0,1]){reset();mf(14,frozen);mf(15,asleep);mf(13,canMove);mf(22,19);rng([0,1]);act(11);assert.equal(fields('m0')[14],'0');}

// Successful mounting installs native ownership and removes the monster from the map.
saddled();rng([0]);assert.equal(act(6),1n);assert.equal(fields('hero')[4],'0');assert.equal(fields('hero')[0],'11');assert.equal(fields('hero')[18],'1');assert.ok(trace().includes('teleds:11:10:'));
mounted();act(0);assert.ok(trace().includes("aren't skilled enough"));assert.equal(act(6),0n);
for(const kind of ['hallucination','legs','poly-small','poly-giant','capacity','null','blind','hidden','furniture','object','tail','swallow','stuck','trap','punished','blocked','unsaddled','untame','minion','trapped','untame-leash','underwater','levitate','rust','confused','fumbling','glib','cursed','greased','slip']){saddled();if(kind==='hallucination')prop(L.HALLUC,0,1);if(kind==='legs')prop(L.WOUNDED_LEGS,0,3);if(kind==='poly-small')hero(11,L.PM_GRID_BUG);if(kind==='poly-giant')hero(11,L.PM_GIANT);if(kind==='capacity')opt(12,10);if(kind==='blind')prop(L.BLINDED,0,1);if(kind==='hidden')mf(10,1);if(kind==='furniture')mf(18,L.M_AP_FURNITURE);if(kind==='object')mf(18,L.M_AP_OBJECT);if(kind==='tail'){mf(0,L.PM_LONG_WORM);mf(20,12);}if(kind==='swallow')hero(4,1);if(kind==='stuck')hero(7,1);if(kind==='trap')hero(8,1);if(kind==='punished')obj(1,15,1);if(kind==='blocked')opt(13,0);if(kind==='unsaddled'){mf(17,-1);mf(16,0);}if(kind==='untame')mf(4,0);if(kind==='minion')mf(5,1);if(kind==='trapped'){mf(11,1);call('terrain',11,10,L.ROOM,L.PIT,1);}if(kind==='untame-leash'){mf(4,1);mf(12,1);}if(kind==='underwater')hero(5,1);if(kind==='levitate')prop(L.LEVITATION,0,1);if(kind==='rust'){obj(1,0,L.PLATE_MAIL);obj(1,4,1);obj(1,12,1);}if(kind==='confused')prop(L.CONFUSION,0,1);if(kind==='fumbling')prop(L.FUMBLING,0,1);if(kind==='glib')prop(L.GLIB,0,1);if(kind==='cursed')obj(0,1,1);if(kind==='greased')obj(0,2,1);if(kind==='slip'){hero(10,1);mf(4,2);rng([19,4]);}else rng([0]);act(6,kind==='null'?-1:0);}
for(const force of [-1,0,1,256,257]){saddled();hero(10,1);mf(4,2);prop(L.HALLUC,0,1);act(6,0,force);}
saddled();prop(L.HALLUC,0,1);prop(L.HALLUC_RES,0,1);rng([0]);assert.equal(act(6),1n);
saddled();prop(L.BLINDED,0,1);prop(L.TELEPAT,0,1);rng([0]);assert.equal(act(6),1n);
saddled();prop(L.WOUNDED_LEGS,0,1);prop(L.WOUNDED_LEGS,1,L.BOTH_SIDES);hero(14,1);assert.equal(act(6,0,1),1n);assert.ok(trace().includes('heal-legs:0:-1;'));
saddled();prop(L.LEVITATION,0,L.I_SPECIAL);rng([0]);assert.equal(act(6),1n);assert.ok(trace().includes('magically floats up'));
saddled();obj(1,0,L.LANCE);obj(1,11,1);hero(18,1);rng([0]);act(6);assert.equal(fields('hero')[16],'0');
saddled();prop(L.STEALTH,0,1);rng([0]);act(6);assert.ok(trace().includes("aren't stealthy anymore"));
for(const flying of [0,1])for(const blocked of [0,1]){saddled();if(flying)mf(0,L.PM_RED_DRAGON);prop(L.FLYING,0,flying);prop(L.FLYING,2,blocked);act(6,0,1);}

// Public ride entry and the riding timer exercise actual JS in both mounted states.
for(const wizard of [0,1])for(const choice of ['y','n']){saddled();hero(14,wizard);opt(7,choice.charCodeAt(0));rng([0]);act(5);assert.equal(fields('hero')[4],'0');}
reset();opt(2,0);assert.equal(act(5),BigInt(L.ECMD_CANCEL));
mounted();act(5);assert.equal(fields('hero')[4],'-1');
for(const turns of [0,98,99,100,2147483646]){mounted();hero(16,turns);act(7);if(turns>=99)assert.equal(fields('hero')[11],'0');}
reset();hero(16,99);act(7);assert.equal(fields('hero')[11],'99');
for(const frozen of [0,1,2,3,7])for(const asleep of [0,1])for(const roll of [0,1]){mounted();mf(13,frozen?0:1);mf(14,frozen);mf(15,asleep);rng([roll,0]);act(8);}
for(const tame of [0,1,2,20]){mounted();mf(4,tame);mf(12,1);hero(10,1);rng([19,0,0,0,0,0,0,0]);act(8);}
mounted();hero(17,(1n<<53n)+1n);rng([0,19]);act(8);assert.equal(fields('hero')[12],String((1n<<53n)+50n));
reset();act(8);

// Landing chooses real adjacent coordinates: known traps, boulders, fallback passes and preferred knock direction.
for(const reason of reasons.map(k=>L[k]))for(const impaired of [0,1])for(const blocked of [0,1]){mounted();if(impaired)prop(L.CONFUSION,0,1);if(blocked)opt(14,0);rng(Array(64).fill(0));act(9,0,reason,1);if(blocked)assert.deepEqual(fields('hero').slice(20,22),['12','10']);}
for(const traps of [0,1])for(const boulder of [0,1]){mounted();for(let x=9;x<=11;x++)for(let y=9;y<=11;y++)if(x!==10||y!==10)call('terrain',x,y,L.ROOM,traps?L.PIT:0,1);opt(15,boulder);rng(Array(64).fill(0));assert.equal(act(9,0,L.DISMOUNT_BYCHOICE,0),1n);}
mounted();opt(14,0);opt(16,0);assert.equal(act(9,0,L.DISMOUNT_FELL,1),0n);
mounted();hero(2,1);hero(3,0);rng([0]);act(9,0,L.DISMOUNT_KNOCKED,0);assert.deepEqual(fields('hero').slice(20,22),['11','10']);
mounted();hero(11,L.PM_GRID_BUG);rng(Array(64).fill(0));act(9,0,L.DISMOUNT_POLY,0);

// Dismount reasons retain source two-stage relocation, temporary NULL steed, damage, and stealth transitions.
for(const reason of reasons.map(k=>L[k])){mounted();rng(Array(64).fill(0));act(10,0,reason);assert.equal(fields('hero')[4],'-1');assert.ok(trace().includes('locomotion:fall:-1:0:0;'));if(reason!==L.DISMOUNT_BONES)assert.equal(fields('m0')[12],String(L.MON_FLOOR));}
mounted();obj(0,1,1);act(10,0,L.DISMOUNT_BYCHOICE);assert.equal(fields('hero')[4],'0');assert.equal(fields('o0')[8],'1');
mounted();opt(14,0);act(10,0,L.DISMOUNT_BYCHOICE);assert.equal(fields('hero')[4],'0');
for(const propName of ['FLYING','LEVITATION'])for(const blocked of [0,1]){mounted();prop(L[propName],0,1);prop(L[propName],2,blocked);rng(Array(64).fill(0));act(10,0,L.DISMOUNT_FELL);assert.equal(trace().includes('riding accident'),!!blocked);}
mounted();prop(L.WOUNDED_LEGS,0,(1n<<53n)+7n);rng(Array(64).fill(0));act(10,0,L.DISMOUNT_FELL);assert.ok(trace().includes('wound:'));
mounted();mf(0,L.PM_RED_DRAGON);rng(Array(64).fill(0));act(10,0,L.DISMOUNT_FELL);assert.ok(trace().includes('locomotion:fall:-1:0:0;'));assert.ok(trace().includes('riding accident'));
mounted();prop(L.STEALTH,0,1);prop(L.STEALTH,2,L.FROMOUTSIDE);act(10,0,L.DISMOUNT_GENERIC);assert.ok(trace().includes('seem less noisy'));
for(const trap of [L.TT_PIT,L.TT_BEARTRAP,L.TT_WEB]){mounted();hero(8,3);hero(9,trap);act(10,0,L.DISMOUNT_GENERIC);assert.equal(fields('m0')[9],'1');assert.ok(trace().includes('mintrap:0:'));}
for(const kind of ['dead','engulfer','stuck','swallow','water','lava','no-room','bones-fallback','name','hallucination','healed-legs','native-death']){mounted();let reason=L.DISMOUNT_GENERIC;if(kind==='dead')mf(2,0);if(kind==='engulfer'){mf(20,10,1);mf(25,1,1);hero(7,1);opt(17,2);reason=L.DISMOUNT_ENGULFED;}if(kind==='stuck')hero(7,1);if(kind==='swallow')hero(4,1);if(kind==='water')opt(20,1);if(kind==='lava')opt(21,1);if(kind==='no-room'){opt(14,0);opt(16,0);reason=L.DISMOUNT_THROWN;}if(kind==='bones-fallback'){opt(16,0);reason=L.DISMOUNT_BONES;}if(kind==='name'){mf(24,1);reason=L.DISMOUNT_BYCHOICE;}if(kind==='hallucination'){prop(L.HALLUC,0,1);reason=L.DISMOUNT_BYCHOICE;}if(kind==='healed-legs')prop(L.WOUNDED_LEGS,0,27);if(kind==='native-death')opt(32,8);rng(Array(64).fill(0));act(10,0,reason);if(kind==='water'||kind==='lava'){assert.equal(fields('m0')[4],'0');assert.ok(!trace().includes('teleds:'));assert.ok(trace().includes('align:-1'));}}
mounted();obj(1,0,L.LANCE);obj(1,11,1);act(10,0,L.DISMOUNT_GENERIC);assert.equal(fields('hero')[16],'1');
reset();act(10,0,L.DISMOUNT_GENERIC);

// Shape change, feeding and placement include diagnostics and native mstate/grid identities.
mounted();act(12,0,L.PM_WARHORSE);assert.ok(trace().includes('your new monster0'));mounted();act(12,0,L.PM_PONY);assert.ok(trace().includes('your monster0'));
mounted();mf(0,L.PM_HUMAN);act(12,0,L.PM_PONY);assert.equal(fields('hero')[4],'-1');
for(const feeding of [-1,0,1,256,257])for(const helpless of [0,1]){mounted();mf(22,4);if(helpless)mf(15,1);act(13,0,feeding);}
reset();act(13,0,1);
for(const kind of ['normal','invalid','self-overlap','overlap','steed','dismounting','dead','guard','dead-guard']){reset();let x=12,y=10;if(kind==='invalid'){x=-1;y=40;}if(kind==='self-overlap')x=11;if(kind==='overlap'){mf(20,12,1);mf(25,1,1);}if(kind==='steed')hero(6,0);if(kind==='dismounting'){hero(6,0);hero(19,1);}if(kind==='dead')mf(2,0);if(kind==='guard'||kind==='dead-guard'){mf(8,1);x=y=0;if(kind==='dead-guard')mf(2,0);}mf(23,(1n<<53n)+1n);act(14,0,x,y);}

// Growth and native reentry occur inside the source's live ownership and coordinate operations.
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13]){reset();opt(30,stage);opt(31,stage);const before=modules.map(m=>allocationMetric(m));if(stage===1){act(3,0,0);prop(L.WOUNDED_LEGS,0,1);hero(14,1);act(6,0,1);}else if(stage===2){obj(0,9,1);act(2);}else if(stage===3)act(3,0,-1);else if(stage===4||stage===5)act(3,0,0);else if(stage===6){act(3,0,0);act(6,0,1);}else if(stage===7||stage===8){act(3,0,0);act(6,0,1);}else{act(3,0,0);mf(25,0);mf(20,10);hero(6,0);if(stage===10){opt(14,0);act(10,0,L.DISMOUNT_POLY);}else if(stage===11){opt(20,1);act(10,0,L.DISMOUNT_GENERIC);}else if(stage===12){hero(8,3);hero(9,L.TT_PIT);act(10,0,L.DISMOUNT_GENERIC);}else act(10,0,L.DISMOUNT_GENERIC);}assert.ok(trace().includes(`grew:${stage};`),`growth stage ${stage}`);assert.ok(trace().includes('nested-ride:'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));}
reset();opt(0,0);act(2);assert.ok(trace().includes('rn2:100:')&&trace().includes('@;'));
modules.forEach((m,i)=>{assert.equal(m._probe_pointer(9,0),classifierPointers[i]);assert.deepEqual(Buffer.from(m.HEAPU8.slice(Number(m._probe_pointer(9,0)),Number(m._probe_pointer(9,0))+7)),classifiers[i]);});comparisons++;
saddled();act(6,0,1);const held=snapshot(modules[1]);
const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(77);other._probe_action(3,0,0,0,0);assert.equal(other._probe_action(6,0,1,0,0),1n);assert.equal(fields('hero',other)[4],'0');other._probe_action(10,0,L.DISMOUNT_GENERIC,0,0);assert.equal(fields('hero',other)[4],'-1');assert.deepEqual(snapshot(modules[1]),held);comparisons+=4;check();
console.log(`STEED ${referenceLabel}/hybrid differential: ${comparisons} comparisons checked`);
