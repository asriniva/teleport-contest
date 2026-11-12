import './pure-js-probes/deny-wasm.mjs';
import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('lock', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/lock-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('lock',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.lock,runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const idx={object:2,hero:1,prop:2}[name];if(idx!==undefined)args[idx]=BigInt(args[idx]);const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],`${name}:${args}`);comparisons++;check();return r[0];}
function reset(s=1){call('reset',s);}
function act(op,a=0,b=0,c=0,d=0){return call('action',op,a,b,c,d);}
function obj(i,k,v){call('object',i,k,v);}
function hero(k,v){call('hero',k,v);}
function opt(k,v){call('option',k,v);}
function lock(k,v){call('xlock',k,v);}
function prop(p,k,v){call('prop',p,k,v);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function fields(prefix){return text(modules[0],modules[0]._probe_snapshot()).split(';').find(x=>x.startsWith(prefix+':')).split(':').slice(1);}
function output(){return text(modules[0],modules[0]._probe_pointer(5,0));}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function door(mask=L.D_LOCKED,type=L.DOOR){call('terrain',11,10,type,mask);}
function tool(type=L.SKELETON_KEY){obj(0,0,type);}
function box(i=1,locked=1){obj(i,4,locked);obj(i,17,1);}
function setupPick(mask=L.D_LOCKED){reset();door(mask);lock(1,1);lock(3,100);lock(4,L.SKELETON_KEY);call('occupation',0);}
function setupForce(type=L.DAGGER){reset();obj(0,0,type);obj(0,18,1);box();lock(0,1);lock(3,100);lock(4,type===L.DAGGER?1:0);call('occupation',1);}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['CHEST','LARGE_BOX','LOCK_PICK','CREDIT_CARD','SKELETON_KEY','ART_MASTER_KEY_OF_THIEVERY','ART_YENDORIAN_EXPRESS_CARD','ART_ORB_OF_DETECTION','DAGGER','LONG_SWORD','FLAIL','LANCE','PICK_AXE','BOULDER','ROCK','ROOM','DOOR','SDOOR','D_NODOOR','D_LOCKED','D_CLOSED','D_TRAPPED','D_ISOPEN','D_BROKEN','PM_HUMAN','PM_FLOATING_EYE','PM_GRID_BUG','PM_SMALL_MIMIC','PM_ORACLE','PM_ROGUE','PM_WIZARD','OBJ_FLOOR','OBJ_INVENT','OBJ_FREE','WAN_LOCKING','WAN_OPENING','WAN_POLYMORPH','WAN_STRIKING','SPE_WIZARD_LOCK','SPE_KNOCK','SPE_POLYMORPH','SPE_FORCE_BOLT','SCR_IDENTIFY','TALLOW_CANDLE','CARROT','MEATBALL','POT_HEALING','DIAMOND','ICE_BOX','CORPSE','TT_PIT','BLINDED','DEAF','CONFUSION','STUNNED','LEVITATION','PASSES_WALLS','PROT_FROM_SHAPE_CHANGERS','AUTOUNLOCK_APPLY_KEY','AUTOUNLOCK_UNTRAP','AUTOUNLOCK_KICK','ECMD_OK','ECMD_TIME','ECMD_CANCEL','M_AP_FURNITURE','M_AP_OBJECT','S_hcdoor'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);

// Native occupation identity includes an unrelated callback, and calls the real callback token.
for(const occupation of [-1,0,1,99]){reset();call('occupation',occupation);act(0);act(1,11,10);if(occupation===0){assert.deepEqual(fields('coord'),['11','10']);lock(1,1);assert.equal(act(1,11,10),1n);}else assert.deepEqual(fields('coord'),['0','0']);if(occupation===99)assert.equal(act(20),73n);}
// Returned locking strings alias unlocking strings at an actual native +2 address.
for(const target of ['door','chest','box']){reset();if(target==='door')lock(1,1);else{obj(1,0,target==='chest'?L.CHEST:L.LARGE_BOX);lock(0,1);obj(1,4,1);}lock(4,L.SKELETON_KEY);act(2);assert.equal(output(),`unlocking the ${target==='door'?'door':target}`);const before=modules.map(m=>Number(m._probe_pointer(7,0)));if(target==='door')door(L.D_CLOSED);else obj(1,4,0);act(2);assert.equal(output(),`locking the ${target}`);modules.forEach((m,i)=>assert.equal(Number(m._probe_pointer(7,0)),before[i]+2));comparisons+=2;}
for(const type of [L.LOCK_PICK,L.CREDIT_CARD,L.SKELETON_KEY]){reset();lock(4,type);act(2);assert.equal(output(),'picking the lock');}
for(const carried of [false,true])for(const container of [-1,1,2]){reset();lock(0,1);lock(2,37);obj(1,1,carried?L.OBJ_INVENT:L.OBJ_FLOOR);act(7,container);assert.equal(Number(fields('lock')[2]),container===1||container<0&&!carried?0:37);}
reset();lock(1,1);lock(2,7);act(7,-1);assert.equal(fields('lock')[1],'0');act(6);

// Inventory priorities use actual linked identities, including foreign quest artifacts.
for(const opening of [0,1])for(const types of [[L.CREDIT_CARD],[L.LOCK_PICK,L.CREDIT_CARD],[L.SKELETON_KEY,L.LOCK_PICK,L.CREDIT_CARD],[L.CREDIT_CARD,L.LOCK_PICK,L.SKELETON_KEY]]){reset();types.forEach((t,i)=>{obj(i,0,t);obj(i,13,i+1<types.length?i+1:-1);});obj(0,16,1);const expected=types.indexOf(L.SKELETON_KEY)>=0?types.indexOf(L.SKELETON_KEY):types.indexOf(L.LOCK_PICK)>=0?types.indexOf(L.LOCK_PICK):opening?0:-1;assert.equal(act(8,opening),BigInt(expected));}
for(const foreign of [0,1]){reset();tool();obj(1,0,L.SKELETON_KEY);obj(1,10,L.ART_MASTER_KEY_OF_THIEVERY);obj(0,13,1);obj(0,16,1);if(!foreign)opt(12,L.ART_MASTER_KEY_OF_THIEVERY);assert.equal(act(8,1),foreign?0n:1n);obj(0,0,L.ROCK);assert.equal(act(8,1),1n);}
reset();obj(0,0,L.CREDIT_CARD);obj(0,10,L.ART_YENDORIAN_EXPRESS_CARD);obj(0,16,1);assert.equal(act(8,0),-1n);assert.equal(act(8,1),0n);

// Direct occupation: moved targets, finite attempt counter, success, traps and magic disarming.
for(const mask of [L.D_NODOOR,L.D_ISOPEN,L.D_BROKEN,L.D_CLOSED,L.D_LOCKED,L.D_LOCKED|L.D_TRAPPED])for(const roll of [0,99]){setupPick(mask);lock(3,50);rng([roll]);act(20);}
setupPick();lock(3,0);assert.equal(act(20),1n);assert.equal(fields('lock')[2],'1');
for(const used of [49,50,2147483646]){setupPick();lock(2,used);rng([99]);act(3);}
setupPick();hero(2,-1);assert.equal(act(3),0n);assert.equal(fields('lock')[2],'0');
setupPick();hero(8,L.PM_FLOATING_EYE);act(3);assert.ok(trace().includes('give up'));
for(const boxTarget of [false,true])for(const choice of ['y','n']){setupPick(L.D_LOCKED|L.D_TRAPPED);if(boxTarget){lock(1,0);lock(0,1);obj(1,4,1);obj(1,7,1);}lock(5,1);opt(2,choice.charCodeAt(0));act(3);assert.equal(fields('lock')[3],'120');assert.ok(trace().includes(choice==='y'?'succeed in disarming':'stop unlocking'));}
for(const where of [L.OBJ_FLOOR,L.OBJ_INVENT])for(const x of [10,11]){setupPick();lock(1,0);lock(0,1);obj(1,1,where);obj(1,2,x);obj(1,4,1);act(3);}
setupPick();lock(1,0);lock(0,1);obj(1,4,1);obj(1,7,1);act(3);assert.equal(fields('o1')[4],'0');assert.ok(trace().includes('chest-trap:1'));
setupPick(L.D_LOCKED|L.D_TRAPPED);opt(17,65);act(3);assert.ok(trace().includes('damage:11:10:'));assert.equal(fields('lock')[2],'0');

// Chest contents are genuinely unlinked; non-destruction hides and restores cobj during billing.
reset();obj(1,15,2);obj(2,13,3);obj(1,4,1);act(4,1,0);assert.ok(trace().includes('contents=-1'));assert.equal(fields('o1')[12],'2');assert.equal(fields('o1')[4],'0');assert.equal(fields('o1')[5],'1');
for(const quantity of [1n,3n,(1n<<53n)+1n]){reset();hero(14,65);opt(18,1);opt(19,1);opt(20,23);obj(1,15,2);obj(2,13,3);obj(2,0,L.POT_HEALING);obj(2,11,quantity);obj(3,0,L.CORPSE);obj(3,11,2);obj(3,19,17);obj(1,0,L.ICE_BOX);hero(15,(1n<<53n)+91n);lock(0,1);rng([0,0]);act(4,1,1);assert.equal(fields('o1')[15],'1');assert.equal(fields('lock')[0],'-1');assert.ok(trace().includes('corpse-time:3:'));assert.ok(trace().includes('owe 69 gold pieces'));}
for(const type of [L.SCR_IDENTIFY,L.TALLOW_CANDLE,L.CARROT,L.MEATBALL,L.POT_HEALING,L.CHEST,L.DIAMOND])for(const blind of [0,1]){reset();obj(0,0,type);prop(L.BLINDED,0,blind?(1n<<53n)+7n:0n);prop(L.BLINDED,2,(1n<<53n)+9n);act(19);assert.equal(fields('hero')[6],String(blind?(1n<<53n)+7n:0n));assert.equal(fields('hero')[7],String((1n<<53n)+9n));}

// Forceability follows the real object catalogue, and forcing retains native weapon/box identities.
for(const type of [L.DAGGER,L.LONG_SWORD,L.FLAIL,L.LANCE,L.PICK_AXE,L.BOULDER,L.ROCK,L.CHEST]){reset();obj(0,0,type);obj(0,18,1);act(10);}
reset();assert.equal(act(10),0n);
for(const type of [L.DAGGER,L.BOULDER])for(const roll of [0,99]){setupForce(type);rng([0,roll,1]);act(20);}
setupForce();lock(3,0);rng([0,99]);assert.equal(act(5),1n);
setupForce();rng([999]);act(5);assert.equal(fields('heads')[1],'-1');assert.ok(trace().includes('broke!'));
for(const curse of [0,1]){setupForce();obj(0,9,curse);opt(21,1);rng([999,99]);act(5);}
for(const used of [49,50]){setupForce();lock(2,used);rng([0,99]);act(5);}
setupForce();obj(1,2,11);act(5);
setupForce();obj(0,18,0);act(5);
setupForce();hero(8,L.PM_FLOATING_EYE);act(5);

// Public picker/force entry paths initialize context and install real callback pointers.
for(const type of [L.SKELETON_KEY,L.LOCK_PICK,L.CREDIT_CARD])for(const role of [L.PM_HUMAN,L.PM_ROGUE]){reset();tool(type);hero(9,role);assert.equal(act(9,0,11,10,-1),1n);assert.equal(fields('occ')[0],'0');rng([0]);act(20);assert.ok(trace().includes('succeed in'));}
for(const type of [L.SKELETON_KEY,L.LOCK_PICK,L.CREDIT_CARD])for(const cursed of [0,1]){reset();tool(type);obj(1,9,cursed);box();assert.equal(act(9,0,10,10,1),1n);assert.equal(fields('lock')[0],'1');act(20);}
for(const choice of ['y','n','q'])for(const unlocked of [0,1]){reset();tool(L.CREDIT_CARD);box(1,!unlocked);opt(2,choice.charCodeAt(0));act(9,0,10,10,1);}
for(const kind of ['broken','unreachable','lava','pool','up','hands','swallow','invalid','cancel','untrap','apply','refuse-touch','null-tool']){reset();tool();box();if(kind==='broken')obj(1,5,1);if(kind==='unreachable')opt(6,0);if(kind==='lava')opt(8,1);if(kind==='pool')opt(7,1);if(kind==='up')hero(4,-1);if(kind==='hands')hero(8,L.PM_FLOATING_EYE);if(kind==='swallow')hero(5,1);if(kind==='invalid')tool(L.ROCK);if(kind==='cancel')opt(5,0);if(kind==='untrap'){hero(10,L.AUTOUNLOCK_UNTRAP);opt(14,1);}if(kind==='apply')hero(10,L.AUTOUNLOCK_APPLY_KEY);if(kind==='refuse-touch')opt(13,0);act(9,kind==='null-tool'?-1:0,kind==='up'||kind==='cancel'?0:10,10,1);}
for(const kind of ['resume','hands','swallow','unreachable']){reset();tool();lock(0,1);lock(2,7);lock(4,L.SKELETON_KEY);if(kind==='hands')hero(8,L.PM_FLOATING_EYE);if(kind==='swallow')hero(5,1);if(kind==='unreachable')opt(6,0);act(9,0,0,0,-1);}
for(const mask of [L.D_NODOOR,L.D_ISOPEN,L.D_BROKEN,L.D_CLOSED]){reset();tool(L.CREDIT_CARD);door(mask);act(9,0,11,10,-1);}
reset();tool();hero(6,1);hero(7,L.TT_PIT);act(9,0,11,10,-1);
reset();tool();door(0,L.ROOM);opt(16,1);act(9,0,11,10,-1);
for(const type of [L.DAGGER,L.BOULDER,L.CHEST])for(const choice of ['y','n','q']){reset();obj(0,0,type);obj(0,18,1);box();opt(2,choice.charCodeAt(0));act(11);if(type!==L.CHEST&&choice==='y'){assert.equal(fields('occ')[0],'1');rng([0,0,1]);act(20);}}
reset();setupForce();lock(2,4);assert.equal(act(11),BigInt(L.ECMD_TIME));assert.ok(trace().includes('resume your attempt'));
reset();hero(5,1);act(11);reset();obj(0,0,L.DAGGER);obj(0,18,1);opt(6,0);act(11);
reset();obj(0,0,L.DAGGER);obj(0,18,1);box(1,0);obj(2,17,1);obj(2,14,1);obj(2,5,1);act(11);

// Mimics and obstruction use real map/list references and native appearance bits.
for(const ap of [0,L.M_AP_FURNITURE,L.M_AP_OBJECT])for(const visible of [0,1])for(const quiet of [0,1]){reset();call('monster_field',0,1);call('monster_field',1,ap);opt(22,visible);opt(23,0);act(15,11,10,quiet);}
reset();obj(0,2,11);obj(0,17,1);assert.equal(act(15,11,10,0),1n);
for(const protect of [0,1]){reset();call('monster_field',0,1);call('monster_field',1,L.M_AP_FURNITURE);call('monster_field',2,L.S_hcdoor);prop(L.PROT_FROM_SHAPE_CHANGERS,0,protect);assert.equal(act(12,11,10),protect?0n:1n);}
for(const ap of [0,L.M_AP_FURNITURE,L.M_AP_OBJECT]){reset();tool(L.CREDIT_CARD);call('monster_field',0,1);call('monster_field',1,ap);call('monster_field',2,L.S_hcdoor);call('monster_field',3,1);act(9,0,11,10,-1);}

// Opening/closing cover terrain, strength, impairment, automatic kick and current-location loot.
for(const command of [13,16])for(const mask of [L.D_NODOOR,L.D_BROKEN,L.D_CLOSED,L.D_LOCKED,L.D_ISOPEN,L.D_CLOSED|L.D_TRAPPED])for(const roll of [0,24]){reset();door(mask);rng([roll]);act(command);}
reset();door(L.D_CLOSED);rng([0]);assert.equal(act(13),BigInt(L.ECMD_TIME));assert.ok(trace().includes('door opens.'));
reset();door(L.D_ISOPEN);rng([0]);assert.equal(act(16),BigInt(L.ECMD_TIME));assert.ok(trace().includes('door closes.'));
for(const command of [13,16])for(const kind of ['hands','pit','small','blind','confused','stunned','cancel','drawbridge','nothing','monster']){reset();door(command===13?L.D_CLOSED:L.D_ISOPEN);if(kind==='hands')hero(8,L.PM_FLOATING_EYE);if(kind==='pit'){hero(6,1);hero(7,L.TT_PIT);}if(kind==='small')hero(8,L.PM_GRID_BUG);if(kind==='blind')prop(L.BLINDED,0,1);if(kind==='confused')prop(L.CONFUSION,0,1);if(kind==='stunned')prop(L.STUNNED,0,1);if(kind==='cancel')opt(5,0);if(kind==='drawbridge')opt(9,1);if(kind==='nothing')door(0,L.ROOM);if(kind==='monster')call('monster_field',0,1);act(command);}
reset();opt(3,10);opt(4,10);assert.equal(act(13),37n);
reset();hero(2,0);act(16);prop(L.PASSES_WALLS,0,1);act(16);
reset();hero(2,-20);act(16);
reset();hero(10,L.AUTOUNLOCK_KICK);act(13);assert.ok(trace().includes('queue:'));
reset();tool();obj(0,16,1);hero(10,L.AUTOUNLOCK_APPLY_KEY);act(13);assert.equal(fields('occ')[0],'0');
reset();door(L.D_ISOPEN);hero(13,1);act(16);

// Box and door magic preserve exact ordinary/trapped/secret/rogue transitions and stop picking only on change.
for(const type of [L.WAN_LOCKING,L.WAN_OPENING,L.WAN_POLYMORPH,L.SPE_WIZARD_LOCK,L.SPE_KNOCK,L.SPE_POLYMORPH,L.ROCK])for(const locked of [0,1])for(const wizard of [false,true]){reset();obj(0,0,type);obj(1,4,locked);obj(1,5,1);lock(0,1);lock(2,5);if(wizard)hero(9,L.PM_WIZARD);act(17,1,0);}
for(const type of [L.WAN_LOCKING,L.WAN_OPENING,L.WAN_STRIKING,L.SPE_WIZARD_LOCK,L.SPE_KNOCK,L.SPE_FORCE_BOLT,L.ROCK])for(const terrain of [L.DOOR,L.SDOOR])for(const mask of [L.D_NODOOR,L.D_ISOPEN,L.D_BROKEN,L.D_CLOSED,L.D_LOCKED,L.D_LOCKED|L.D_TRAPPED]){setupPick(mask);door(mask,terrain);obj(0,0,type);obj(0,20,1);hero(11,1);opt(17,65);act(18,0,11,10);}
for(const kind of ['trap','object','hidden-object','mimic','monster','rogue','rogue-obstructed','unknownwand']){reset();obj(0,0,L.WAN_LOCKING);door(L.D_ISOPEN);if(kind==='trap')opt(24,1);if(kind==='object'||kind==='hidden-object'||kind==='rogue-obstructed'){obj(1,2,11);obj(1,17,1);}if(kind==='hidden-object')obj(0,20,0);if(kind==='mimic'||kind==='monster'){call('monster_field',0,1);if(kind==='mimic')call('monster_field',1,L.M_AP_FURNITURE);}if(kind.startsWith('rogue')){hero(17,2);hero(18,2);}act(18,0,11,10);}
for(const visible of [0,1])for(const trapped of [0,1])for(const deaf of [0,1]){reset();obj(0,0,L.WAN_STRIKING);door(L.D_LOCKED|(trapped?L.D_TRAPPED:0));call('monster_field',0,1);opt(22,visible);hero(12,deaf);hero(11,1);hero(16,1);act(18,0,11,10);}

// Native boolean parameters narrow to signed char before their control-flow tests.
for(const value of [-1,256,257]){reset();call('monster_field',0,1);act(15,11,10,value);reset();box();act(4,1,value);reset();obj(0,0,L.CREDIT_CARD);obj(0,16,1);act(8,value);}

// Source RNG logging can be disabled without changing the draws or callback identities.
setupPick();opt(0,0);rng([0]);act(3);assert.ok(trace().includes('rn2:100:0@;'));
for(const cause of [25,26]){reset();obj(0,0,L.WAN_STRIKING);door(L.D_CLOSED|L.D_TRAPPED);hero(11,1);hero(19,-((1n<<53n)+1n));opt(cause,1);act(18,0,11,10);assert.ok(!trace().includes('You see a door explode'));}
reset();tool();box();opt(7,1);hero(20,1);act(9,0,10,10,1);assert.equal(fields('occ')[0],'0');

// Real growth and native→JS callback reentry, with fresh heap views on return.
for(const stage of [1,2,3,4,5,6,7,8,9]){reset();opt(30,stage);opt(31,stage);const lengths=modules.map(m=>allocationMetric(m));if(stage===1||stage===2||stage===3||stage===4){tool();act(9,0,stage===3?0:11,10,-1);}else if(stage===5){lock(1,1);lock(3,100);lock(4,L.SKELETON_KEY);door(L.D_LOCKED|L.D_TRAPPED);act(3);}else if(stage===6||stage===7){obj(0,0,L.WAN_STRIKING);door(L.D_LOCKED|L.D_TRAPPED);opt(17,65);act(18,0,11,10);}else if(stage===8){box();act(4,1,0);}else{box();act(4,1,1);}assert.ok(trace().includes(`grew:${stage};`));assert.ok(trace().includes('nested-pick:'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>lengths[i]));}
reset();tool();act(9,0,11,10,-1);const held=snapshot(modules[1]);
const other=await hybridFactory({nethackPorted:runtime});
other._probe_reset(77);
other._probe_occupation(99);
assert.equal(other._probe_action(20,0,0,0,0),73n);
other._probe_object(0,0,BigInt(L.SKELETON_KEY));
assert.equal(other._probe_action(9,0,11,10,-1),1n);
assert.equal(other._probe_action(1,11,10,0,0),1n);
other._probe_xlock(3,100);
assert.equal(other._probe_action(20,0,0,0,0),0n);
const otherTerrain=text(other,other._probe_snapshot()).split(/heads:[^;]*;/)[1].split(';');
assert.equal(otherTerrain[11*L.ROWNO+10],`${L.DOOR},${L.D_CLOSED},0`);
assert.ok(text(other,other._probe_trace()).includes('You:succeed in unlocking the door.'));
assert.deepEqual(snapshot(modules[1]),held);
comparisons+=7;check();
console.log(`LOCK ${referenceLabel}/pure-JS differential: ${comparisons} comparisons checked`);
