import './pure-js-probes/deny-wasm.mjs';
import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('wizard', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/wizard-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('wizard',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
import * as wizard from '../js/ported/wizard.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.wizard,runtime=createPortedRuntime(layouts);
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
function flag(k){return BigInt(L[k]);}
function stair(i,x,y,up=1,ladder=0,dnum=1,next=-1){call('stair',i,x,y,up,ladder,dnum,next);}
function pmfield(pm,name,value){modules.forEach(m=>{const p=Number(m._probe_pointer(2,pm))+L['pm_'+name],n=L['pm_'+name+'_size'],v=new DataView(m.HEAPU8.buffer);if(n===8)v.setBigUint64(p,BigInt.asUintN(64,BigInt(value)),true);else if(n===4)v.setUint32(p,Number(value),true);else if(n===2)v.setUint16(p,Number(value),true);else v.setUint8(p,Number(value));});check();}
function ground(type=L.AMULET_OF_YENDOR,index=0,x=5,y=6){obj(index,0,type);obj(index,2,x);obj(index,3,y);obj(index,5,1);obj(index,9,L.OBJ_FLOOR);}
function healthy(){reset();mf(8,1);}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['NUMMONS','PM_WIZARD_OF_YENDOR','PM_MASTER_LICH','PM_ARCH_LICH','PM_ARCHON','PM_HUMAN','PM_ANGEL','PM_HORNED_DEVIL','PM_MASTER_MIND_FLAYER','PM_MIND_FLAYER','PM_RED_DRAGON','PM_BABY_RED_DRAGON','PM_GUARDIAN_NAGA','PM_GUARDIAN_NAGA_HATCHLING','PM_FLOATING_EYE','PM_COCKATRICE','AMULET_OF_YENDOR','FAKE_AMULET_OF_YENDOR','BELL_OF_OPENING','CANDELABRUM_OF_INVOCATION','SPE_BOOK_OF_THE_DEAD','ROCK','OBJ_FREE','OBJ_FLOOR','OBJ_MINVENT','ART_ORB_OF_DETECTION','MAGIC_PORTAL','PIT','G_GENOD','G_HELL','G_NOHELL','DEAF','BLINDED','PROT_FROM_SHAPE_CHANGERS','AT_MAGC','S_DEMON','S_ANGEL','NATTK','M_AP_MONSTER','LARGEST_INT','ROWNO','COLNO'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);
for(const k of ['M3_WANTSAMUL','M3_WANTSBELL','M3_WANTSCAND','M3_WANTSBOOK','M3_WANTSARTI','STRAT_NONE','STRAT_HEAL','STRAT_PLAYER','STRAT_GROUND','STRAT_MONSTR','STRAT_WAITFORU','STRAT_APPEARMSG','STRAT_WAITMASK','STRAT_GOAL','STRAT_STRATMASK'])assert.doesNotThrow(()=>BigInt(L[k]),k);

// Every original table entry is read from native C and compared with the authoritative JS data.
const tableNames=['nasties','wizapp','random_insult','random_malediction'];
const originalTables=tableNames.map((name,t)=>{assert.ok(Array.isArray(wizard[name]),name);const m=modules[0],count=m._probe_table_count(t),base=Number(m._probe_table_pointer(t));assert.ok(base>0&&count>0,name);assert.equal(wizard[name].length,count);const v=new DataView(m.HEAPU8.buffer),out=[];for(let i=0;i<count;i++){const actual=t<2?v.getInt32(base+i*4,true):text(m,v.getBigUint64(base+i*L.pointerSize,true));const entry=wizard[name][i],expected=t<2?L[entry]:entry;assert.notEqual(expected,undefined,`${name}[${i}]`);assert.equal(actual,expected,`${name}[${i}]`);out.push(actual);comparisons++;}return out;});
const nastyIndex=pm=>originalTables[0].indexOf(pm);
const maskNames=['M3_WANTSAMUL','M3_WANTSBELL','M3_WANTSCAND','M3_WANTSBOOK','M3_WANTSARTI'];
const artifactTypes=[L.AMULET_OF_YENDOR,L.BELL_OF_OPENING,L.CANDELABRUM_OF_INVOCATION,L.SPE_BOOK_OF_THE_DEAD,0];

// Possession and target priorities distinguish hero, floor, other monsters, and protected Amulet holders.
for(let n=0;n<5;n++){reset();const mask=Number(flag(maskNames[n])),type=artifactTypes[n];assert.equal(act(3,0,mask),BigInt(type));assert.equal(act(7,0,mask),0n);hero(2+n,1);assert.equal(act(7,0,mask),1n);assert.equal(act(8,0,mask),flag('STRAT_PLAYER')|BigInt(mask));assert.deepEqual(fields('m0').slice(7,9),['10','10']);hero(2+n,0);ground(type||L.ROCK);if(!type)obj(0,1,L.ART_ORB_OF_DETECTION);assert.equal(act(6,0,type),0n);assert.equal(act(8,0,mask),flag('STRAT_GROUND')|BigInt(mask));assert.deepEqual(fields('m0').slice(7,9),['5','6']);obj(0,5,0);obj(0,8,1);mf(8,1,1);mf(10,0,1);assert.equal(act(5,0,type),1n);assert.equal(act(8,0,mask),flag('STRAT_MONSTR')|BigInt(mask));obj(0,8,0);assert.equal(act(4,0,type),1n);assert.equal(act(8,0,mask),flag('STRAT_NONE'));assert.deepEqual(fields('m0').slice(7,9),['0','0']);assert.equal(act(2),1n);}
for(const type of [L.ROCK,L.FAKE_AMULET_OF_YENDOR,L.AMULET_OF_YENDOR]){reset();obj(0,0,type);obj(0,8,0);act(1);act(2);}
reset();obj(0,1,L.ART_ORB_OF_DETECTION);obj(0,8,0);assert.equal(act(4,0,65536),1n);
for(const protectedBy of ['wizard','temple','ordinary']){healthy();obj(0,0,L.AMULET_OF_YENDOR);obj(0,8,1);mf(7,1);mf(10,protectedBy==='wizard',1);opt(8,protectedBy==='temple');const out=act(8,0,Number(flag('M3_WANTSAMUL')));assert.equal(out,protectedBy==='ordinary'?flag('STRAT_MONSTR')|flag('M3_WANTSAMUL'):0n);}
reset();ground(L.ROCK);obj(0,1,L.ART_ORB_OF_DETECTION);assert.equal(act(8,0,-1),-1n);assert.deepEqual(fields('m0').slice(7,9),['5','6']);
reset();mf(0,L.PM_HUMAN);mf(20,13);mf(21,14);act(8,0,Number(flag('M3_WANTSBOOK')));assert.deepEqual(fields('m0').slice(7,9),['13','14']);
for(const species of [L.PM_WIZARD_OF_YENDOR,L.PM_MASTER_LICH,L.PM_HUMAN])for(const hp of [-11,-1,0,1,9,10,19,20,29,30,31,715827882]){reset();mf(0,species);mf(1,hp);mf(2,hp>30?2147483647:30);act(9);}
for(const invoked of [0,1])for(const madeAmulet of [0,1]){reset();hero(7,invoked);hero(14,madeAmulet);for(let n=0;n<5;n++)hero(2+n,1);const chosen=madeAmulet?'M3_WANTSAMUL':invoked?'M3_WANTSARTI':'M3_WANTSBOOK';assert.equal(act(9),flag('STRAT_PLAYER')|flag(chosen));}
for(const restriction of ['shop','temple']){reset();mf(restriction==='shop'?11:12,1);opt(restriction==='shop'?9:8,1);assert.equal(act(9),0n);}

// Real original stairway query plus target-owned fallback ordering; output aliases remain native coord pointers.
for(const direction of [-1,0,1,256,257])for(const builds of [0,1]){reset();opt(10,builds);stair(0,4,5,1,0,1,1);stair(1,6,7,0,0);act(10,0,direction);}
for(const kind of ['matching','ladder','branch','opposite','opposite-ladder','absent']){reset();const up=kind==='opposite'||kind==='opposite-ladder'?0:1;if(kind!=='absent')stair(0,4,5,up,kind.includes('ladder')||kind==='ladder'?1:0,kind==='branch'?2:1);act(10,0,0);assert.deepEqual(fields('spot'),kind==='absent'?['-99','-99']:['4','5']);}
reset();stair(0,4,5,0,0,2,1);stair(1,6,7,0,1,1);act(10,0,0);assert.deepEqual(fields('spot'),['4','5']);

// Tactics preserve full strategy high bits, move restrictions, expulsion, healing, and true object ownership.
reset();hero(14,1);hero(2,1);mf(5,(1n<<63n)|flag('STRAT_WAITMASK')|flag('STRAT_APPEARMSG')|flag('M3_WANTSBOOK'));act(11);assert.equal(BigInt(fields('m0')[6]),flag('STRAT_WAITMASK')|flag('STRAT_APPEARMSG')|flag('STRAT_PLAYER')|flag('M3_WANTSAMUL'));
for(const kind of ['stairs','stairs-fail','blocked','tower','no-stairs-wizard','healing','swallow','harass','flee']){healthy();if(kind==='harass'||kind==='flee')mf(1,30);else mf(1,5);if(kind==='stairs'||kind==='stairs-fail'||kind==='blocked'||kind==='healing'||kind==='swallow')stair(0,kind==='healing'?40:25,10,1);if(kind==='stairs-fail')opt(5,0);if(kind==='blocked')opt(6,1);if(kind==='tower')opt(7,2);if(kind==='swallow'){hero(9,1);hero(10,0);}if(kind==='flee')mf(17,1);rng([0,0,0]);act(11);if(kind==='healing')assert.ok(trace().includes('heal:0:'));if(kind==='swallow')assert.ok(trace().includes('expel:0:'));}
for(const kind of ['floor','standing','blocked-floor','other-holder','player','noport-far','noport-near','move-fail']){healthy();hero(14,1);ground();if(kind==='standing'){mf(3,5);mf(4,6);}if(kind==='blocked-floor'){mf(3,5,1);mf(4,6,1);mf(26,1,1);}if(kind==='other-holder'){obj(0,5,0);obj(0,8,1);mf(7,1);mf(10,0,1);}if(kind==='player'){obj(0,5,0);hero(2,1);}if(kind.startsWith('noport')){opt(6,1);if(kind==='noport-near'){mf(3,5);mf(4,7);}}if(kind==='move-fail'){hero(2,1);opt(5,0);}rng([0]);const out=act(11);if(kind==='floor'){assert.equal(out,1n);assert.equal(fields('heads')[2],'-1');assert.equal(fields('m0')[9],'0');assert.equal(fields('o0')[6],'0');}}

// Aggravation respects tower partitions, death, immobility and bitwise unsigned-long masks.
for(const tower of [0,1,2]){healthy();mf(7,1);mf(3,35,1);mf(5,(1n<<63n)|flag('STRAT_WAITFORU')|flag('STRAT_APPEARMSG'),1);mf(13,1,1);mf(14,0,1);mf(15,7,1);opt(7,tower);act(12);rng([0]);act(13);if(tower!==1)assert.equal(BigInt(fields('m1')[6]),1n<<63n);}
healthy();mf(1,0);mf(5,flag('STRAT_WAITFORU'));assert.equal(act(12),0n);
for(const worn of [6,7])for(const distance of [1,8,12,13]){healthy();obj(0,0,L.AMULET_OF_YENDOR);obj(0,worn,1);hero(19,L.MAGIC_PORTAL);hero(20,10+distance);hero(21,10);hero(22,1);hero(13,1);mf(13,1);rng([0,0]);act(0);assert.equal(fields('m0')[14],'0');if(distance<=12)assert.ok(trace().includes('Object0 feel'));}
healthy();obj(0,0,L.AMULET_OF_YENDOR);obj(0,6,1);hero(0,20);hero(19,L.PIT);hero(23,1);hero(22,1);rng([0]);act(0);assert.ok(trace().includes("Object0 feel warm."));

// Clone appearance, fake Amulet, and wizard population bookkeeping are observable independently.
for(const amulet of [0,1])for(const protectedShape of [0,1]){reset();hero(2,amulet);if(protectedShape)prop(L.PROT_FROM_SHAPE_CHANGERS,0,1);rng([1,0]);act(14);assert.equal(fields('hero')[4],'1');assert.equal(fields('m8')[11],'1');assert.equal(fields('m8')[17],'0');assert.equal(fields('m8')[26],String(protectedShape?0:L.M_AP_MONSTER));assert.equal(fields('m8')[27],String(protectedShape?0:originalTables[1][amulet?1:0]));if(!amulet)assert.ok(trace().includes('object:16:'));}
reset();opt(1,1);act(14);assert.equal(fields('hero')[4],'0');
for(const flags of [0,L.G_GENOD])for(const cap of [0,1,15,40])for(let n=0;n<originalTables[0].length;n++){reset();call('vital',originalTables[0][n],flags);rng([n,n]);act(15,0,cap);}
reset();opt(21,L.PM_BABY_RED_DRAGON);rng([nastyIndex(L.PM_RED_DRAGON)]);assert.equal(act(15,0,1),BigInt(L.PM_RED_DRAGON));
reset();opt(21,L.PM_GUARDIAN_NAGA_HATCHLING);rng([nastyIndex(L.PM_GUARDIAN_NAGA)]);assert.equal(act(15,0,1),BigInt(L.PM_GUARDIAN_NAGA));
reset();hero(16,6);hero(17,7);const lowerNasty=nastyIndex(L.PM_COCKATRICE);assert.ok(lowerNasty>=0);rng([lowerNasty,1]);act(15,0,0);assert.equal(modules[0]._probe_rng_count(),2);assert.equal((trace().match(/rn2:44:/g)||[]).length,2);assert.ok(trace().includes('wizard.c:551:pick_nasty'));

// Retry goto consumes ten attempts on each of twenty j iterations; no monster is constructed.
reset();mf(0,L.PM_HUMAN);opt(15,1);rng([1,0,...Array(200).fill(1)]);assert.equal(act(16),0n);assert.equal(fields('hero')[17],'0');assert.equal((trace().match(/rn2:44:/g)||[]).length,200);
// Group members count in the returned census even though the direct creation cap is ten.
reset();hero(12,30);opt(3,2);rng([1,9,...Array(30).fill(0)]);assert.equal(act(16,-1),30n);assert.equal(fields('hero')[17],'10');
for(const kind of ['normal','hell','failed','fallback','fallback-spell','opposite','no-location','nested']){reset();hero(12,3);if(kind==='hell')hero(16,7);if(kind==='failed')opt(1,1);if(kind==='fallback'){opt(1,2);opt(2,L.PM_HUMAN);}if(kind==='fallback-spell'){mf(0,L.PM_ARCHON);opt(1,2);opt(2,L.PM_ARCHON);opt(15,1);}if(kind==='opposite'){mf(0,L.PM_HORNED_DEVIL);opt(1,2);opt(2,L.PM_ANGEL);}if(kind==='no-location')opt(4,0);if(kind==='nested')opt(34,1);rng(kind==='hell'?[0]:Array(300).fill(1));act(16,kind==='normal'||kind==='hell'||kind==='nested'?-1:0);if(kind==='hell')assert.ok(trace().includes('summon:-1;'));if(kind==='nested')assert.ok(trace().includes('nested-nasty-end:'));if(kind==='fallback-spell'||kind==='opposite')assert.ok(trace().includes('unmake:'));}

// Resurrection dereferences and mutates actual C pointer-to-link slots, including native arrival mutation.
reset();act(17);assert.equal(fields('hero')[4],'1');assert.equal(fields('m8')[22],'1');assert.ok(trace().includes('couldst kill me'));
for(const kind of ['first','second','helpless-first','amulet-first','limbo','native-prepend','sleep','sleep-long','frozen','not-elapsed','deaf']){reset();hero(13,1);mf(9,1);mf(7,1);mf(19,0);mf(19,0,1);if(kind==='second')mf(10,0);if(kind==='helpless-first'){mf(13,1);mf(19,99);}if(kind==='amulet-first'){obj(0,0,L.AMULET_OF_YENDOR);obj(0,8,0);}if(kind==='limbo')opt(12,1);if(kind==='native-prepend')opt(14,1);if(kind==='sleep')mf(13,1);if(kind==='sleep-long'){mf(13,1);hero(15,(1n<<53n)+1n);}if(kind==='frozen'){mf(14,0);mf(15,1);}if(kind==='not-elapsed'){mf(19,100);mf(19,100,1);}if(kind==='deaf')hero(18,1);rng([1,1]);act(17);if(kind==='second'||kind==='helpless-first'||kind==='amulet-first'){assert.equal(fields('heads')[1],'0');assert.equal(fields('m0')[10],'-1');assert.ok(trace().includes('arrive:1:-1'));}if(kind==='native-prepend')assert.equal(fields('heads')[1],'7');if(kind==='limbo')assert.ok(!trace().includes('malign:'));if(kind==='deaf')assert.ok(!trace().includes('voice booms'));}

// Harassment and insults preserve all table text and source argument evaluation/RNG order.
for(const astral of [0,1])for(let n=0;n<6;n++){reset();if(astral){hero(16,8);hero(17,9);}rng([n,...Array(128).fill(1)]);act(18);}
for(const already of [0,1]){reset();hero(13,2);hero(8,already);hero(24,123);rng([249]);act(19);assert.equal(fields('hero')[4],'1');assert.equal(fields('hero')[3],already?'123':'299');}
reset();hero(13,0);rng([0]);act(19);assert.equal(fields('hero')[4],'4294967295');
for(const kind of ['laugh','amulet','hero-near-death','wizard-near-death','malediction','deaf','role-deaf','minion','renegade','demon']){reset();if(kind==='amulet')hero(2,1);if(kind==='hero-near-death')hero(11,4);if(kind==='wizard-near-death')mf(1,4);if(kind==='deaf')prop(L.DEAF,0,(1n<<53n)+1n);if(kind==='role-deaf')hero(18,1);if(kind==='minion'||kind==='renegade'){mf(0,L.PM_ANGEL);mf(10,0);mf(24,1);if(kind==='renegade')mf(25,1);}if(kind==='demon'){mf(0,L.PM_HORNED_DEVIL);mf(10,0);}const values={laugh:[0],amulet:[1,0,2],'hero-near-death':[1,0,1,2],'wizard-near-death':[1,0,1],malediction:[1,2,3]}[kind]||[1,2,3];rng(values);act(20);if(kind==='deaf'||kind==='role-deaf')assert.equal(modules[0]._probe_rng_count(),0);if(kind==='minion')assert.ok(trace().includes('pager:angel_cuss;'));}

// Growth/native callbacks include live object transfer, mutable migration links and nested RNG-consuming summons.
for(const stage of [1,2,3,4,5,6,7,8,9,10,11]){reset();opt(30,stage);opt(31,stage);const before=modules.map(m=>allocationMetric(m));if(stage===1)act(14);else if(stage===2){hero(14,1);hero(2,1);act(11);}else if(stage===3){mf(1,5);stair(0,40,10);rng([0]);act(11);}else if(stage===4||stage===5){hero(14,1);ground();act(11);}else if(stage===6){hero(16,7);rng([0]);act(16,-1);}else if(stage===7){hero(12,3);rng(Array(128).fill(1));act(16);}else if(stage===8||stage===9){hero(13,1);mf(9,1);mf(19,0);act(17);}else if(stage===10){rng([2]);act(18);}else{mf(10,0);mf(0,L.PM_HORNED_DEVIL);rng([1]);act(20);}assert.ok(trace().includes(`grew:${stage};`),`growth ${stage}`);assert.ok(trace().includes('nested-aggravate:'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));}
reset();opt(0,0);rng([0]);act(20);assert.ok(trace().includes('@;'));
healthy();mf(5,1n<<63n);const held=snapshot(modules[1]);const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(77);other._probe_action(14,0,0,0,0);assert.equal(fields('hero',other)[4],'1');other._probe_hero(13,1n);other._probe_action(19,0,0,0,0);assert.equal(fields('hero',other)[4],'0');assert.equal(fields('hero',other)[12],'1');assert.deepEqual(snapshot(modules[1]),held);comparisons+=4;check();
console.log(`WIZARD ${referenceLabel}/pure-JS differential: ${comparisons} comparisons checked`);
