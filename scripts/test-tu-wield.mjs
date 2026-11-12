import {DataView,Int32Array,assertStackRestored,memoryCheckpoint,assertMemoryGrowth,referenceBackend,referenceLabel} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/wield-reference.mjs';
import hybridFactory from '../.cache/tu-probes/wield-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
import * as core from '../js/ported/wield.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.wield,runtime=createPortedRuntime(layouts);
const modules=[await referenceBackend('wield',emscriptenReferenceFactory)(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count(),frees:m._probe_free_count()};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(name,...args){const at={object:2,set_monster:2,hero:1,prop:2,action:4}[name];if(at!==undefined)args[at]=BigInt(args[at]);const ret=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(ret[1],ret[0],`${name}:${args}`);comparisons++;check();return ret[0];}
const reset=(s=1)=>call('reset',s),opt=(k,v)=>call('option',k,v),obj=(i,k,v)=>call('object',i,k,v),hero=(k,v)=>call('hero',k,v),mon=(i,k,v)=>call('set_monster',i,k,v),prop=(p,k,v)=>call('prop',p,k,v),equip=(k,i)=>call('equip',k,i),link=(k,i)=>call('link',k,i),act=(op,i=0,a=0,b=0,v=0n)=>call('action',op,i,a,b,v),mask=k=>BigInt(L[k]);
function fields(k,m=modules[0]){return text(m,m._probe_snapshot()).split(';').find(s=>s.startsWith(k+':')).split(':').slice(1);}
const trace=()=>text(modules[0],modules[0]._probe_trace()),slots=()=>fields('equip')[0].split(',');
function rng(a){for(const m of modules){new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),a.length).set(a);m._probe_rng_length(a.length);}check();}
function inventory(items){items.forEach((i,j)=>{obj(i,4,items[j+1]??-1);obj(i,12,L.OBJ_INVENT);});link(0,items[0]??-1);}
function weapon(i,type=L.LONG_SWORD){obj(i,0,type);}
function slot(i,at,key){equip(at,i);if(i>=0)obj(i,1,mask(key));}
function dual(){weapon(0);weapon(1,L.DAGGER);mon(8,0,L.PM_MARILITH);slot(0,9,'W_WEP');slot(1,10,'W_SWAPWEP');inventory([0,1]);}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['NUM_OBJECTS','NUMMONS','PM_HUMAN','PM_DOG','PM_FOG_CLOUD','PM_MARILITH','PM_COCKATRICE','PM_CHICKATRICE','DAGGER','LONG_SWORD','TWO_HANDED_SWORD','BATTLE_AXE','BOW','ARROW','DART','GOLD_PIECE','MAGIC_MARKER','PICK_AXE','LANCE','LEATHER_GLOVES','SMALL_SHIELD','HELMET','AKLYS','TOWEL','TIN_OPENER','CORPSE','WORM_TOOTH','CRYSKNIFE','SCR_ENCHANT_WEAPON','ART_OGRESMASHER','ART_SUNSWORD','ART_MAGICBANE','ART_SNICKERSNEE','BLINDED','STONE_RES','GLIB','HALLUC','HALLUC_RES','OBJ_INVENT','OBJ_FREE','OBJ_FLOOR','ECMD_OK','ECMD_FAIL','ECMD_TIME','ECMD_CANCEL','GETOBJ_SUGGEST','GETOBJ_DOWNPLAY','GETOBJ_EXCLUDE'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);
for(const k of ['W_WEP','W_SWAPWEP','W_QUIVER','W_ARMG','W_ARMS','W_ARMOR','W_ACCESSORY','W_SADDLE'])assert.ok(L[k]!==undefined,k);
// The two immutable original strings remain in their original file scope.
const source=readFileSync(new URL('../.cache/wasm64-build/tree/src/wield.c',import.meta.url),'utf8');
for(const [i,name]of ['are_no_longer_twoweap','can_no_longer_twoweap'].entries()){const found=source.match(new RegExp(name+'\\[\\] = "([^"]+)"'));assert.ok(found);assert.equal(text(modules[0],modules[0]._probe_string(i)),found[1]);assert.equal(core[name],found[1]);}
// Every catalogue entry exercises both real selector functions. NULL is legal.
assert.equal(act(7,-1),BigInt(L.GETOBJ_SUGGEST));act(6,-1);
for(let type=0;type<L.NUM_OBJECTS;type++){obj(0,0,type);act(6);act(7);}
reset();weapon(0);slot(0,9,'W_WEP');assert.equal(act(6),BigInt(L.GETOBJ_DOWNPLAY));obj(0,3,2);assert.equal(act(6),BigInt(L.GETOBJ_SUGGEST));
reset();weapon(0,L.ARROW);weapon(1,L.BOW);assert.equal(act(6),BigInt(L.GETOBJ_DOWNPLAY));slot(1,9,'W_WEP');assert.equal(act(6),BigInt(L.GETOBJ_SUGGEST));
// All weapon catalogue types pass the actual slot/property classification path.
for(let type=0;type<L.NUM_OBJECTS;type++){reset();obj(0,0,type);act(0);assert.equal(slots()[9],'0');act(0);act(18);assert.equal(slots()[9],'-1');}
for(const pm of [L.PM_HUMAN,L.PM_DOG,L.PM_FOG_CLOUD]){reset();mon(8,0,pm);act(2);const p=modules.map(m=>text(m,m._probe_string(2)));assert.equal(p[0],p[1]);equip(4,0);assert.equal(act(2),0n);assert.equal(text(modules[0],modules[0]._probe_string(2)),'empty handed');}
for(const type of [L.CORPSE,L.DAGGER])for(const pm of [L.PM_HUMAN,L.PM_COCKATRICE,L.PM_CHICKATRICE])for(const glove of [0,1])for(const stone of [0,1]){reset();obj(0,0,type);obj(0,16,pm);if(glove)equip(4,1);if(stone)prop(L.STONE_RES,1,1);const danger=type===L.CORPSE&&pm!==L.PM_HUMAN&&!glove&&!stone;assert.equal(act(1),danger?1n:0n);assert.equal(trace().includes('petrify:'),danger);}
// Mounted polearms become proper melee weapons; Snickersnee bypasses it too.
for(const mounted of [0,1])for(const artifact of [0,L.ART_SNICKERSNEE]){reset();weapon(0,L.LANCE);if(mounted)hero(7,0);if(artifact)obj(0,8,artifact);act(0);assert.equal(fields('wield')[0],!mounted&&!artifact?'1':'0');}
// Empty, shield rejection, retouch refusal and replacement, weld, artifact light.
reset();assert.equal(act(3,-1),BigInt(L.ECMD_OK));weapon(0);act(0);assert.equal(act(3,-1),BigInt(L.ECMD_TIME));assert.equal(slots()[9],'-1');
reset();weapon(0,L.TWO_HANDED_SWORD);equip(3,1);assert.equal(act(3),BigInt(L.ECMD_FAIL));assert.equal(slots()[9],'-1');
for(const fail of [0,1])for(const replace of [-1,1]){if(!fail&&replace<0)continue;reset();weapon(0);weapon(1,L.DAGGER);opt(8,1);opt(9,replace);opt(10,fail?0:1);const ret=act(3);assert.equal(ret,BigInt(L.ECMD_TIME));assert.equal(slots()[9],fail?'-1':String(replace));assert.ok(trace().includes(`retouched:${replace};`));}
reset();weapon(0);obj(0,7,1);act(3);assert.equal(fields('o0')[15],'1');assert.ok(trace().includes('weld'));assert.equal(slots()[9],'0');
reset();weapon(0,L.AKLYS);act(3);assert.ok(trace().includes('secure the tether'));
for(const blind of [0,1]){reset();weapon(0);obj(0,8,L.ART_SUNSWORD);opt(3,1);if(blind)prop(L.BLINDED,0,1);act(3);assert.equal(fields('o0')[11],'1');act(18);assert.equal(fields('o0')[11],'0');assert.equal(trace().includes('to shine'),!blind);}
reset();weapon(0);obj(0,8,L.ART_OGRESMASHER);act(0);assert.equal(fields('hero')[6],'1');hero(13,0);act(0,-1);assert.equal(fields('hero')[6],'1');
reset();weapon(0);obj(0,19,1);opt(12,1);act(3);assert.ok(trace().includes('Merchant says'));
reset();weapon(0);hero(18,1);act(3);assert.equal(fields('hero')[6],'1');
// Source long mask is restored after transient naming, including its high bit.
reset();weapon(0);const high=(1n<<63n)|mask('W_WEP');obj(0,1,BigInt.asIntN(64,high));act(24);for(const m of modules){const p=Number(m._probe_pointer(0,0))+L.obj_owornmask;assert.equal(new DataView(m.HEAPU8.buffer).getBigUint64(p,true),high);}assert.equal(act(25),0n);obj(0,7,1);assert.equal(act(25),1n);slot(0,9,'W_WEP');assert.equal(act(23),1n);
// Native getobj runs NULL and actual object callbacks, then returns selections.
for(const op of [9,11,12])for(const selection of [-1,-2,0,1]){reset();inventory([0,1]);weapon(0);weapon(1,L.DAGGER);opt(19,selection);const ret=act(op);assert.ok(trace().includes('filter-null:'));assert.equal(ret,BigInt(selection===-1?L.ECMD_CANCEL:op===9&&selection>=0?L.ECMD_TIME:L.ECMD_OK));}
reset();mon(8,0,L.PM_FOG_CLOUD);opt(19,0);assert.equal(act(9),BigInt(L.ECMD_FAIL));assert.ok(!trace().includes('getobj:'));
// Each of the four labels is reached by a native stack split, with list identity.
for(const op of [9,11]){reset();inventory([0,1]);weapon(0);obj(0,3,9);if(op===9)slot(0,9,'W_WEP');else slot(0,11,'W_QUIVER');opt(19,0);opt(20,2);assert.equal(act(op),BigInt(op===9?L.ECMD_FAIL:L.ECMD_OK));assert.equal(fields('o0')[3],'9');assert.equal(fields('o20')[3],'0');assert.ok(trace().includes('unsplit:20:0;'));assert.ok(trace().includes(op===9?'already wielding':'already readied'));}
for(const op of [9,11]){reset();inventory([0,1]);weapon(0);obj(0,3,9);opt(19,0);opt(20,2);act(op);assert.equal(fields('o0')[3],'7');assert.equal(fields('o20')[3],'2');assert.equal(slots()[op===9?9:11],'20');assert.equal(fields('heads')[0],'20');assert.ok(trace().includes('freeinv:20;')&&trace().includes('addinv:20;'));}
reset();inventory([0]);weapon(0);obj(0,3,9);slot(0,9,'W_WEP');obj(0,7,1);opt(19,0);opt(20,2);act(9);assert.equal(fields('o0')[3],'9');assert.ok(trace().includes('reset-remarm;'));
reset();inventory([0]);obj(0,0,L.GOLD_PIECE);obj(0,3,9);opt(19,0);opt(20,2);act(11);assert.equal(fields('o0')[3],'9');assert.ok(trace().includes("can't ready only part"));
// Interactive stack splits from primary, alternate and quiver, all y/n/q paths.
for(const origin of [9,10,11])for(const answer of ['y','n','q'])for(const op of [9,11]){if(op===9&&origin!==11||op===11&&origin===11)continue;reset();inventory([0,1]);weapon(0);weapon(1,L.DAGGER);obj(0,3,7);slot(0,origin,origin===9?'W_WEP':origin===10?'W_SWAPWEP':'W_QUIVER');opt(19,0);opt(17,answer.charCodeAt(0));act(op);if(answer==='y'){assert.ok(trace().includes('split:0:'));assert.equal(slots()[op===9?9:11],'20');assert.equal(fields('o0')[3],op===9?'6':'1');}else assert.ok(!trace().includes('split:0:'));}
for(const op of [9,11])for(const wornmask of ['W_ARMOR','W_ACCESSORY','W_SADDLE']){reset();inventory([0]);opt(19,0);obj(0,1,mask(wornmask));act(op);assert.ok(trace().includes('cannot'));}
// Deliberate artifact/base-type stress: a singular weapon with the Eyes ID
// isolates is_plural from the separate pair_of(LENSES) rule. This is not a
// normally generated Eyes artifact, whose real lenses are always a pair.
for(const unknown of [0,1]){reset();inventory([0]);weapon(0);obj(0,8,L.ART_EYES_OF_THE_OVERWORLD);slot(0,11,'W_QUIVER');opt(19,0);opt(22,unknown);act(9);assert.ok(trace().includes(`undiscovered:${L.ART_EYES_OF_THE_OVERWORLD}:${unknown};`));assert.ok(trace().includes(unknown?'You have that readied.  Wield it instead?':'You have those readied.  Wield them instead?'));}
// Swap failures preserve old pointers; success swaps and pushweapon retains old.
for(const shield of [0,1]){reset();weapon(0);weapon(1,L.TWO_HANDED_SWORD);slot(0,9,'W_WEP');slot(1,10,'W_SWAPWEP');if(shield)equip(3,2);act(10);assert.equal(slots()[9],shield?'0':'1');assert.equal(slots()[10],shield?'1':'0');}
reset();inventory([0,1]);weapon(0);weapon(1,L.DAGGER);slot(0,9,'W_WEP');hero(15,1);opt(19,1);act(9);assert.equal(slots()[9],'1');assert.equal(slots()[10],'0');
for(const type of [L.DAGGER,L.PICK_AXE,L.MAGIC_MARKER,L.TWO_HANDED_SWORD])for(const blocked of [0,1]){reset();weapon(0,type);if(blocked)obj(0,1,mask('W_ARMOR'));act(13,0,blocked);assert.equal(slots()[9],blocked?'-1':'0');}
for(const mode of ['valid','empty','form','launcher','twohands','shield','artifact','cursed','glib']){reset();dual();if(mode==='empty')equip(10,-1);if(mode==='form')mon(8,0,L.PM_FOG_CLOUD);if(mode==='launcher')weapon(1,L.BOW);if(mode==='twohands')weapon(1,L.TWO_HANDED_SWORD);if(mode==='shield')equip(3,2);if(mode==='artifact')obj(1,8,L.ART_MAGICBANE);if(mode==='cursed')obj(1,7,1);if(mode==='glib')prop(L.GLIB,0,1);assert.equal(act(14),mode==='valid'?1n:0n);if(mode==='cursed'||mode==='glib'){assert.equal(fields('o1')[4],String(L.OBJ_FLOOR));assert.equal(slots()[10],'-1');}}
for(const existing of [0,1]){reset();dual();hero(1,existing);act(15);assert.equal(fields('o1')[4],String(L.OBJ_FLOOR));}
for(const b of [0,1,-1,128,256,257]){reset();hero(5,1);act(16,0,b);assert.equal(fields('hero')[1],String(b<<24>>24));act(21);assert.equal(fields('hero')[1],'0');}
for(const dex of [1,12,20])for(const roll of [0,19]){reset();dual();opt(15,dex);rng([roll]);assert.equal(act(17),BigInt(roll+1>dex?L.ECMD_TIME:L.ECMD_OK));assert.equal(fields('hero')[1],'1');assert.ok(trace().includes('rnd:20:'));act(17);assert.equal(fields('hero')[1],'0');}
for(const op of [18,19,20]){reset();weapon(0);act(op===18?0:op===19?5:4);act(op);assert.equal(slots()[op===18?9:op===19?10:11],'-1');act(op);}
// Enchantment transformation, signed char compound stores, cost and destruction.
// Read the native catalogue input, independently of the JS object dataset.
// WEAPON's fifth numeric argument after the description is its unit weight.
assert.equal(L.obj_owt_size,4);
const objectSource=readFileSync(new URL('../.cache/wasm64-build/tree/include/objects.h',import.meta.url),'utf8'),fusionWeights=new Map();
for(const [type,name]of [[L.WORM_TOOTH,'worm tooth'],[L.CRYSKNIFE,'crysknife']]){const row=objectSource.match(new RegExp('WEAPON\\("'+name+'",\\s*NoDes,\\s*\\d+,\\s*\\d+,\\s*\\d+,\\s*\\d+,\\s*(\\d+)'));assert.ok(row,'Original native WEAPON unit weight: '+name);fusionWeights.set(type,Number(row[1]));}
for(const type of [L.WORM_TOOTH,L.CRYSKNIFE])for(const quantity of [1n,9007199254740993n]){reset();weapon(0,type);obj(0,3,quantity);obj(0,7,1);obj(0,19,1);obj(1,0,L.SCR_ENCHANT_WEAPON);obj(1,17,1);slot(0,9,'W_WEP');act(22,1,type===L.WORM_TOOTH?1:-1);assert.equal(fields('o0')[0],String(type===L.WORM_TOOTH?L.CRYSKNIFE:L.WORM_TOOTH));assert.equal(fields('o0')[3],'1');
 const weights=modules.map(m=>new DataView(m.HEAPU8.buffer).getUint32(Number(m._probe_pointer(0,0))+L.obj_owt,true)),expected=quantity>1n?fusionWeights.get(type===L.WORM_TOOTH?L.CRYSKNIFE:L.WORM_TOOTH):0;
 assert.equal(weights[1],weights[0],'Native/JS transformed owt');assert.equal(weights[0],expected,'Original C transformed owt');assert.equal(weights[1],expected,'JS transformed owt');comparisons++;
}
for(const type of [L.TIN_OPENER,L.MAGIC_MARKER])for(const amount of [-1,0,1]){reset();weapon(0,type);obj(0,7,1);slot(0,9,'W_WEP');act(22,-1,amount);assert.ok(trace().includes('feeling:'));}
for(const spe of [-128,-7,-6,-5,0,5,6,7,127])for(const amount of [-2,-1,0,1,2,127])for(const roll of [0,1]){reset();weapon(0);obj(0,2,spe);obj(0,7,1);slot(0,9,'W_WEP');rng([roll,0]);act(22,-1,amount);const evaporate=(spe>5&&amount>=0||spe< -5&&amount<0)&&roll!==0;assert.equal(modules[0]._probe_free_count(),evaporate?1:0);if(!evaporate)assert.equal(fields('o0')[2],String((spe+amount)<<24>>24));}
for(const amount of [-1,1,2])for(const blind of [0,1]){reset();weapon(0);obj(0,8,L.ART_MAGICBANE);slot(0,9,'W_WEP');opt(21,1);if(blind)prop(L.BLINDED,0,1);act(22,-1,amount);if(amount<0)assert.equal(fields('o0')[2],'0');}
// Native calls can grow memory/reenter and alter equipment before source resumes.
for(const stage of [1,2,3,4,7,8,10,14,15,16,17,18]){reset();weapon(0);weapon(1,L.DAGGER);inventory([0,1]);opt(30,stage);opt(31,stage);const before=modules.map(memoryCheckpoint);
 if(stage===1||stage===4){slot(0,9,'W_WEP');act(18);}
 else if(stage===2){obj(0,8,L.ART_MAGICBANE);act(0);}
 else if(stage===7){act(8);}
 else if(stage===8){slot(0,10,'W_SWAPWEP');act(15);}
 else if(stage===10){obj(0,8,L.ART_SUNSWORD);opt(3,1);act(3);}
 else if(stage===16){obj(0,3,4);slot(0,11,'W_QUIVER');opt(19,0);act(9);}
 else if(stage===17){obj(0,3,4);slot(0,11,'W_QUIVER');opt(19,0);opt(17,121);act(9);}
 else if(stage===18){opt(19,0);act(9);}
 else act(stage===3?0:3);
 assert.ok(trace().includes(`grow:${stage};`));assert.ok(trace().includes('nested:'));modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));
}
reset();weapon(0);weapon(1,L.DAGGER);opt(32,3);opt(33,9);opt(34,1);act(0);assert.equal(slots()[9],'1');
reset();weapon(0);slot(0,9,'W_WEP');obj(0,7,1);opt(0,0);act(24);assert.ok(!trace().includes('@wield.c'));
reset();dual();opt(0,0);rng([0]);act(17);assert.ok(trace().includes('rnd:20:1@;'));
reset();weapon(0);act(0);for(let i=0;i<150;i++){act(3);act(5,1);act(10);}
reset();weapon(0);act(0);const saved=modules.map(snapshot),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(7);other._probe_object(1,0,BigInt(L.DAGGER));other._probe_action(0,1,0,0,0n);assert.equal(fields('equip',other)[0].split(',')[9],'1');modules.forEach((m,i)=>assert.deepEqual(snapshot(m),saved[i]));check();
console.log(`WIELD: ${comparisons} ${referenceLabel}/hybrid full state, callbacks, ownership, RNG and equipment comparisons checked.`);
