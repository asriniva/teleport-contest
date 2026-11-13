import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
const nativeExecution=process.env.NATIVE_MONDATA_FIXTURE==='1',nativeServices=new WeakMap();
function monsterDataServices(s){if(!nativeExecution)return s;let local=nativeServices.get(s);if(!local){local=nativeFixtureServices(s,{}).services;nativeServices.set(s,local);}return local;}
import './pure-js-probes/deny-wasm.mjs';
import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('mondata', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/mondata-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('mondata',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
import * as core from '../js/ported/mondata.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.mondata,runtime=createPortedRuntime(layouts);
const componentMondata=runtime.mondata;runtime.mondata=(s,n,...args)=>componentMondata(monsterDataServices(s),n,...args);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
const text=(m,p)=>{if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');};
const snap=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()});
function check(){assert.deepEqual(snap(modules[1]),snap(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){if(['set_monster','object'].includes(name))args[2]=BigInt(args[2]);if(['hero','permonst'].includes(name))args[1]=BigInt(args[1]);if(name==='prop')args[2]=BigInt(args[2]);const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],name+':'+args);comparisons++;check();return r[0];}
function act(op,pm=L.PM_HUMAN,a=0,b=0,v=0n){return Number(call('action',op,pm,a,b,BigInt(v)));}
function fast(op,pm=L.PM_HUMAN,a=0,b=0,v=0n){const r=modules.map(m=>m._probe_action(op,pm,a,b,BigInt(v)));assert.equal(r[1],r[0],`${op}:${pm}:${a}:${b}`);comparisons++;return Number(r[0]);}
const reset=(s=1)=>call('reset',s),opt=(k,v)=>call('option',k,v),mon=(i,k,v)=>call('set_monster',i,k,v),hero=(k,v)=>call('hero',k,v),prop=(p,k,v)=>call('prop',p,k,v),obj=(i,k,v)=>call('object',i,k,v),equip=(k,i)=>call('equip',k,i),attack=(s,k,v)=>call('attack',s,k,v),pmfield=(k,v)=>call('permonst',k,v);
const state=()=>text(modules[0],modules[0]._probe_snapshot()),trace=()=>text(modules[0],modules[0]._probe_trace());
function input(s){modules.forEach(m=>{const b=Buffer.from(s+'\0','latin1'),p=Number(m._malloc(BigInt(b.length)));m.HEAPU8.set(b,p);m._probe_input(BigInt(p));m._free(p);});check();}
function rng(v){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),v.length).set(v);m._probe_rng_length(v.length);});check();}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['NUMMONS','NATTK','PM_HUMAN','PM_LICH','PM_GRAY_DRAGON','PM_RAVEN','PM_GHOST','PM_HORNED_DEVIL','PM_BAT','PM_STONE_GOLEM','NON_PM','AT_ANY','AD_ANY','AT_NONE','AT_BOOM','AT_CLAW','AT_BITE','AT_WEAP','AT_SPIT','AT_ENGL','AT_GAZE','AT_MAGC','AT_EXPL','AT_TUCH','AT_STNG','AT_BREA','AT_HUGS','AD_PHYS','AD_FIRE','AD_COLD','AD_ACID','AD_ELEC','AD_DRLI','AD_BLND','AD_RBRE','FIRE_RES','STONE_RES','ANTIMAGIC','DRAIN_RES','BLND_RES','BLINDED','HALLUC','HALLUC_RES','STRANGLED','INVIS','NO_TRAP','ALL_TRAPS','PIT','G_GENOD','CREAM_PIE','BLINDING_VENOM','POT_BLINDNESS','HELMET','GRAY_DRAGON_SCALES','ALCHEMY_SMOCK','LONG_SWORD','ART_EXCALIBUR'];for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);
for(const k of ['W_ARM','W_ARMH','W_ARMC','W_WEP','W_SWAPWEP','M1_FLY','M2_STRONG','INTRINSIC'])assert.ok(L[k]!==undefined,k);
// Direct native private data supplies the independent catalogue oracle, including its sentinel.
assert.equal(core.grownups.length,modules[0]._probe_table_count(0));for(let i=0;i<core.grownups.length;i++)for(let j=0;j<2;j++){const key=core.grownups[i][j];assert.equal(typeof key==='string'?L[key]:key,Number(modules[0]._probe_table(0,i,j)));comparisons++;}
for(const [i,name]of ['levitate','flys','flyl','slither','ooze','immobile','crawl'].entries()){assert.equal(core[name].length,modules[0]._probe_table_count(i+1));for(let j=0;j<4;j++){assert.equal(core[name][j],text(modules[0],modules[0]._probe_table(i+1,j,0)));comparisons++;}}

// Every configured monster row drives pure predicates, strength arithmetic, attack scans and string classifiers.
const predicates=[3,4,12,13,14,16,18,20,24,25,26,27,28,29,48];
reset();for(let p=0;p<L.NUMMONS;p++){for(const op of predicates)fast(op,p);for(const type of [L.AT_NONE,L.AT_CLAW,L.AT_BITE,L.AT_WEAP,L.AT_BREA,L.AT_MAGC,255]){fast(1,p,type,L.AD_ANY);fast(2,p,type);}for(const damage of [L.AD_PHYS,L.AD_FIRE,L.AD_COLD,L.AD_BLND,255]){fast(30,p,damage,L.AT_ANY);fast(31,p,damage);}check();}
// All species pairs, not just named examples, exercise progression and broad same-race grouping.
reset();for(let p=0;p<L.NUMMONS;p++){for(let q=0;q<L.NUMMONS;q++)fast(33,p,q);fast(40,p);fast(41,p);check();}
for(let p=0;p<L.NUMMONS;p++){reset();mon(0,0,p);for(const op of [7,8,9,10,15,17,19,21,22,23,37,39,43])act(op,p);for(const op of [44,45]){input('walk');act(op,p);input('Walk');act(op,p);modules.forEach(m=>{const result=m._probe_pointer(6,0);if(text(m,result)==='Walk')assert.equal(result,m._probe_pointer(3,0));});}attack(-1,0,L.AT_HUGS);act(46,p);act(47,p);}
reset();mon(1,0,L.PM_GRAY_DRAGON);for(let p=0;p<L.NUMMONS;p++){mon(0,0,p);act(32,p);}
// Exact native interior-pointer identity, including duplicate attacks and absent/ANY matches.
reset();for(let i=0;i<L.NATTK;i++){attack(i,0,L.AT_NONE);attack(i,1,L.AD_PHYS);}attack(2,0,L.AT_CLAW);attack(3,0,L.AT_CLAW);attack(2,1,L.AD_FIRE);const idx=act(1,-1,L.AT_CLAW,L.AD_ANY);assert.equal(idx,2);modules.forEach(m=>assert.equal(Number(m._probe_pointer(6,0)),Number(m._probe_pointer(0,-1))+L.pm_mattk+2*L.attackSize));assert.equal(act(30,-1,L.AD_FIRE,L.AT_ANY),2);assert.equal(act(1,-1,L.AT_WEAP,L.AD_ANY),-1);
// Compound assignment stores through signed short after multiplication, before division.
for(const movement of [-32768,-30001,-1,0,1,30001,32767])for(const who of [0,3]){reset();mon(who,0,L.PM_BAT);mon(who,1,movement);if(who===3)hero(0,movement);pmfield(0,10);act(0,-1,who);const old=Number(new DataView(modules[0].HEAPU8.buffer).getInt8(Number(modules[0]._probe_pointer(0,L.PM_BAT))+L.pm_mmove));const expected=Math.trunc(((movement*10)<<16>>16)/old);assert.ok(state().includes(who===3?`u:${L.PM_HUMAN}:${L.PM_HUMAN}:${expected}:`:`;m:${L.PM_HUMAN}:${expected}:`));}

// Equipment and resistance handlers scan real linked inventories and complete source-created dragon armor.
for(const who of [0,3])for(const property of [L.FIRE_RES,L.STONE_RES,L.ANTIMAGIC,L.DRAIN_RES,L.BLND_RES])for(const mode of [0,1,2,3,4,5]){reset();mon(who,0,L.PM_HUMAN);if(mode===1){if(who===3)prop(property,0,1);else mon(who,16,255);}if(mode===2){obj(0,2,1);opt(1,1);opt(2,property===L.FIRE_RES?L.AD_FIRE:L.AD_BLND);equip(who===3?0:3,0);}if(mode>=3){obj(0,0,mode===5?L.ALCHEMY_SMOCK:L.GRAY_DRAGON_SCALES);obj(0,1,mode===5?BigInt(L.W_ARMC):BigInt(L.W_ARM));obj(0,6,property);if(who===3)obj(0,5,0);else obj(0,4,0);if(mode===4){obj(0,2,1);opt(3,1);opt(2,L.AD_FIRE);}}act(6,L.PM_HUMAN,who,property);act(5,L.PM_HUMAN,who,L.AD_FIRE);}
reset();mon(0,0,L.PM_GRAY_DRAGON);opt(1,1);opt(2,L.AD_FIRE);act(5,L.PM_GRAY_DRAGON,0,L.AD_FIRE);assert.ok(trace().includes('fakearmor:'));
for(const who of [0,3])for(const type of [L.CREAM_PIE,L.BLINDING_VENOM,L.POT_BLINDNESS,L.LONG_SWORD])for(const attackType of [L.AT_WEAP,L.AT_SPIT,L.AT_CLAW,L.AT_ENGL,L.AT_GAZE,L.AT_TUCH,L.AT_STNG])for(const protectedMode of [0,1,2]){reset();obj(0,0,type);opt(19,attackType);opt(20,0);if(protectedMode===1){if(who===3)equip(2,1);else mon(who,4,0);}if(protectedMode===2){obj(1,0,L.HELMET);obj(1,1,BigInt(L.W_ARMH));obj(0,3,1);if(who===3)obj(0,5,0);else obj(0,4,0);opt(4,1);}act(11,L.PM_HUMAN,-1,who);}
reset();mon(0,0,L.PM_RAVEN);mon(1,0,L.PM_RAVEN);opt(19,L.AT_CLAW);assert.equal(act(11,L.PM_RAVEN,0,1),0);
for(const who of [0,3]){reset();mon(who,0,L.PM_HUMAN);prop(L.STRANGLED,0,1);act(21,L.PM_HUMAN,who);act(22,L.PM_HUMAN,who);hero(9,1);assert.equal(act(39,L.PM_HUMAN,0),1);obj(0,2,L.ART_EXCALIBUR);equip(0,0);assert.equal(act(24,L.PM_HUMAN),1);}

// Follower exceptions use populated native tame/wizard/equipment state, not only catalogue flags.
reset();assert.equal(act(39),0);mon(0,10,1);assert.equal(act(39),1);mon(0,10,0);mon(0,8,1);opt(6,1);assert.equal(act(39),0);opt(6,0);assert.equal(act(39),1);mon(0,8,0);opt(5,1);assert.equal(act(39),1);opt(5,0);mon(0,0,-1);pmfield(4,BigInt(L.M2_STALK));mon(0,9,1);assert.equal(act(39),0);hero(7,1);assert.equal(act(39),1);

// Name parsers operate on native input buffers and return exact suffix pointers and optional gender cells.
const source=readFileSync(new URL('../.cache/wasm64-build/tree/src/mondata.c',import.meta.url),'utf8');
const strip=s=>s.replace(/\/\*[\s\S]*?\*\//g,'');const alternatives=strip(source).match(/static const struct alt_spl names\[\] = \{([\s\S]*?)\n        \};/);assert.ok(alternatives,'actual local names initializer');const alternativeNames=[...alternatives[1].matchAll(/\{\s*"([^"]+)"/g)].map(x=>x[1]);assert.ok(alternativeNames.length>40);
const names=[...alternativeNames,'a human','an ettin zombie corpse','the giant ant','vortices','wolves','zombies',"wizard of Yendor's corpse",'not a monster','a','', 'high priestess corpse','succubi','grey dragon corpse'];
for(const name of names)for(const gender of [-1,0,1,2])for(const nullable of [0,1]){reset();input(name);hero(16,gender);opt(16,nullable);opt(17,nullable);act(34);act(35);}
reset();input('a fixture rank corpse');opt(15,L.PM_HUMAN);opt(14,6);assert.equal(act(35),L.PM_HUMAN);assert.ok(state().includes('parse:-1:-1:8;'));
// All native gendered names plus a suffix ensure longest-match and remainder behavior across the entire catalogue.
for(let p=0;p<L.NUMMONS;p++){reset();const m=modules[0],base=Number(m._probe_pointer(0,p)),v=new DataView(m.HEAPU8.buffer);for(let g=0;g<3;g++){const name=text(m,v.getBigUint64(base+L.pm_pmnames+g*L.pointerSize,true));if(name){input(name+' corpse');hero(16,-1);act(35);}}}
for(const name of ['','a','I',']','~','an','the','or','other','or other','long','long worm','demon','devil','bug','fish','dragon','ant','giant ants','vortex','floating eye','human'])for(const pointer of [0,1]){reset();input(name);opt(16,pointer);act(36);}
reset();opt(21,1);assert.equal(act(36),0);
// Hallucinatory pronouns, raceptr role/race distinction and all grownup pairs.
for(const who of [0,3])for(const flags of [0,1,2,3,255])for(const visible of [0,1]){reset();opt(7,visible);mon(who,7,1);prop(L.HALLUC,0,1);rng([3]);act(37,L.PM_HUMAN,who);act(38,L.PM_HUMAN,who,flags);}
for(const row of core.grownups.slice(0,-1)){reset();const [a,b]=row.map(k=>typeof k==='string'?L[k]:k);assert.equal(act(42,a,b),1);}
reset();assert.equal(act(42,L.PM_HUMAN,L.PM_HUMAN),1);assert.equal(act(42,L.PM_HUMAN,L.PM_LICH),0);assert.ok(Number.isSafeInteger(L.PM_ELF));const letter=p=>new DataView(modules[0].HEAPU8.buffer).getUint8(Number(modules[0]._probe_pointer(0,p))+L.pm_mlet);assert.equal(letter(L.PM_HUMAN),letter(L.PM_ELF));assert.equal(act(42,L.PM_HUMAN,L.PM_ELF),0);
reset();hero(8,L.PM_LICH);assert.equal(act(43,L.PM_HUMAN,3),L.PM_LICH);hero(1,L.PM_BAT);assert.equal(act(43,L.PM_HUMAN,3),L.PM_HUMAN);

// Raw signed8 trap knowledge casts intentionally retain -128 and zero out high-only low-byte-empty masks.
for(const mask of [0n,1n,0x7fn,0x80n,0xffn,0x100n,1n<<60n,-1n]){reset();mon(0,14,mask);const low=Number(BigInt.asIntN(8,mask));assert.equal(act(55,L.PM_HUMAN,0,L.ALL_TRAPS),low);assert.equal(act(55,L.PM_HUMAN,0,L.NO_TRAP),low?0:1);for(const trapType of [L.PIT,1,32,63]){act(56,L.PM_HUMAN,0,trapType);assert.equal(act(55,L.PM_HUMAN,0,trapType),1);}act(56,L.PM_HUMAN,0,L.NO_TRAP);assert.equal(act(55,L.PM_HUMAN,0,L.ALL_TRAPS),0);act(56,L.PM_HUMAN,0,L.ALL_TRAPS);assert.equal(act(55,L.PM_HUMAN,0,L.ALL_TRAPS),-1);}
for(const lit of [0,1])for(const clear of [0,1])for(const type of [L.PM_HUMAN,L.PM_BAT,L.PM_GHOST]){reset();hero(11,10);hero(12,10);hero(13,L.PIT);hero(14,lit);opt(12,clear);mon(0,0,type);mon(0,18,12);act(57);}
for(const mask of [0n,1n<<60n,(1n<<64n)-1n]){reset();act(51,L.PM_HUMAN,0,0,mask);act(52,L.PM_HUMAN,0,0,mask);}
for(let property=L.FIRE_RES;property<=L.STONE_RES;property++){reset();prop(property,0,BigInt(L.INTRINSIC));act(53,L.PM_HUMAN);assert.equal(new DataView(modules[0].HEAPU8.buffer).getUint16(Number(modules[0]._probe_pointer(1,0))+L.mon_mintrinsics,true),1<<(property-L.FIRE_RES));}
for(const cha of [3,12,25])for(const level of [1,10,50])for(const roll of [0,18,19]){reset();opt(11,cha);mon(0,13,level);rng([roll]);act(54);}
for(let damage=0;damage<256;damage++){reset();act(49,L.PM_HUMAN,damage);act(50,L.PM_HUMAN,damage);rng([7]);act(58,L.PM_HUMAN,damage);}

// Controlled native callbacks cause actual growth and reenter source predicates without replacing policy.
for(let stage=1;stage<=10;stage++){reset();opt(30,stage);opt(31,stage);const before=modules.map(m=>allocationMetric(m));if(stage===1){rng([0]);act(54);}else if(stage===2){obj(0,2,1);equip(3,0);act(5,L.PM_HUMAN,0,L.AD_FIRE);}else if(stage===3){obj(0,2,1);obj(0,4,0);act(10);}else if(stage===4)act(5,L.PM_HUMAN,0,L.AD_FIRE);else if(stage===5){obj(0,0,L.BLINDING_VENOM);obj(1,0,L.HELMET);obj(1,1,BigInt(L.W_ARMH));obj(0,3,1);obj(0,4,0);opt(19,L.AT_SPIT);opt(20,0);act(11,L.PM_HUMAN,-1,0);}else if(stage===6)act(38,L.PM_HUMAN,0,0);else if(stage===7)act(54);else if(stage===8){hero(11,10);hero(12,10);hero(13,L.PIT);act(57);}else if(stage===9){input('not a species');act(35);}else{input('dogs');act(36);}assert.ok(trace().includes(`grow:${stage};`),`growth${stage}`);assert.ok(trace().includes('nested:'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));}
reset();opt(0,0);rng([0]);act(54);assert.ok(trace().includes('@;'));
reset();mon(0,14,0x80);const held=snap(modules[1]),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(9);other._probe_action(56,L.PM_HUMAN,0,L.ALL_TRAPS,0n);assert.equal(other._probe_action(55,L.PM_HUMAN,0,L.ALL_TRAPS,0n),-1n);other._probe_action(0,L.PM_BAT,0,0,0n);assert.deepEqual(snap(modules[1]),held);comparisons+=2;check();
console.log(`MONDATA ${referenceLabel}/pure-JS differential: ${comparisons} comparisons checked`);
