import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
import {createArmorFieldPlans} from '../js/nethack/hero-equipment.js';
const nativeArmorServices=new WeakMap();
function armorServices(s){if(process.env.NATIVE_DO_WEAR_FIXTURE!=='1')return s;let local=nativeArmorServices.get(s);if(!local){local=nativeFixtureServices(s,{}).services;local.nativeFieldPlans=createArmorFieldPlans(s.moduleKey.environment);nativeArmorServices.set(s,local);}return local;}
import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("do_wear");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {referenceBackend,assertStackRestored,memoryCheckpoint,assertMemoryGrowth} from './native-test-backend.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {callDoWear,createDoWearEnvironment} from '../js/nethack/bindings/do_wear.js';
import * as core from '../js/ported/do_wear.js';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
const own=process.env.TELEPORT_DO_WEAR_AUTHOR==='1';
const ref=(await loadFixture("do_wear",own?'../.cache/do_wear-author/reference.mjs':'../.cache/tu-probes/do_wear-reference.mjs')).default;
const hyb=(await loadFixture("do_wear",own?'../.cache/do_wear-author/hybrid.mjs':'../.cache/tu-probes/do_wear-hybrid.mjs')).default;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');};
let reference=await referenceBackend('do_wear',ref)();const measured={};for(let i=0;i<reference._probe_layout_count();i++)measured[text(reference,reference._probe_layout_name(i))]=Number(BigInt.asIntN(64,reference._probe_layout_value(i)));
const L=own?measured:JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).do_wear;
if(own)writeFileSync(new URL('../.cache/do_wear-author/layout.json',import.meta.url),JSON.stringify(L,null,2));
for(const match of readFileSync(new URL('./test-tu-do_wear.mjs',import.meta.url),'utf8').matchAll(/\bL\.([A-Z]\w*)/g))assert.ok(Object.hasOwn(L,match[1]),'compiled fixture constant '+match[1]);
const constant=n=>{assert.ok(Object.hasOwn(L,'lo_'+n),n);let v=BigInt(L['lo_'+n])+(BigInt(L['hi_'+n])<<32n);if(L['csigned_'+n])v=BigInt.asIntN(64,v);return L['csize_'+n]===8?v:Number(v);};
const source=readFileSync(new URL('../js/ported/do_wear.js',import.meta.url),'utf8').replace(/\/\*[\s\S]*?\*\/|"(?:\\.|[^"\\])*"/g,'');
const externals=new Set([...source.matchAll(/\bC\.(\w+)/g)].map(m=>m[1]));const validated=new WeakSet();
function validate(s){if(validated.has(s.moduleKey))return;const e=createDoWearEnvironment(s,L);assert.deepEqual([...externals].filter(k=>!(k in e)),[],'all native/header bindings exist');validated.add(s.moduleKey);}
const servicesByModule=new Map();
const ported={callDoWear(s,n,...a){servicesByModule.set(s.moduleKey,s);validate(s);return callDoWear(armorServices(s),L,n,...a);}};
let modules=[reference,await hyb({nethackPorted:ported})],stacks=modules.map(m=>m._probe_stack()),comparisons=0;
const names=Array.from({length:79},(_,i)=>text(reference,reference._probe_function_name(i))),op=n=>{const i=names.indexOf(n);assert.ok(i>=0,n);return i;};
const deps=Object.fromEntries(Array.from({length:reference._probe_dep_count()},(_,i)=>[text(reference,reference._probe_dep_name(i)),i]));
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
function check(){const pair=modules.map(snapshot);if(pair[0].state!==pair[1].state||pair[0].trace!==pair[1].trace){writeFileSync(new URL('../.cache/do_wear-author/actual.json',import.meta.url),JSON.stringify(pair[1],null,2));writeFileSync(new URL('../.cache/do_wear-author/expected.json',import.meta.url),JSON.stringify(pair[0],null,2));}assert.deepEqual(pair[1],pair[0]);modules.forEach((m,i)=>assertStackRestored(m,stacks[i],m._probe_stack()));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(n,...a){const pair=modules.map(m=>m['_probe_'+n](...a));assert.deepEqual(pair[1],pair[0],n);comparisons++;return pair[0];}
const exercised=new Set();const act=(n,a=0,b=0,c=0,d=0)=>{exercised.add(n);const result=call('action',op(n),BigInt(a),BigInt(b),BigInt(c),BigInt(d));check();return result;};
const reset=(seed=1)=>{call('reset',seed);check();},hero=(k,v)=>call('hero',k,BigInt(v)),field=(i,k,v)=>call('objfield',i,k,BigInt(v)),item=(i,t,q=1)=>{assert.ok(Number.isSafeInteger(t),'actual compiled object type');return call('object',i,t,BigInt(q));},prop=(k,f,v)=>call('property',k,f,BigInt(v));
const option=(n,v)=>{assert.ok(Object.hasOwn(deps,n),n);return call('option',deps[n],v);};
const rolls=(...v)=>{call('roll',-1,0);v.forEach((r,i)=>call('roll',i,r));};const trace=()=>text(reference,reference._probe_trace());
function input(which,value){for(const m of modules){const p=m._malloc(BigInt(value.length+1));m.HEAPU8.set(Buffer.from(value+'\0','latin1'),Number(p));m._probe_text(which,BigInt(p));m._free(p);}comparisons++;}
const state=()=>text(reference,reference._probe_snapshot());
for(const[k,v]of Object.entries(measured))assert.equal(L[k],v,k);

// Initial typed-boundary smoke; broader branch matrices follow in this owned file.
reset();act('fingers_or_gloves',0);item(0,L.DAGGER);act('off_msg',0);act('count_worn_stuff',0,0);act('count_worn_stuff',0,1);act('find_ac');act('reset_remarm');act('cancel_don');act('any_worn_armor_ok',-1);act('count_worn_armor');
const equip=(slot,i)=>call('equipment',slot,i);
// Every armor on/off boundary operates on a real correctly classified object.
const armor=[['Boots',5,'LOW_BOOTS'],['Cloak',1,'ELVEN_CLOAK'],['Helmet',2,'HELMET'],['Gloves',4,'LEATHER_GLOVES'],['Shield',3,'SMALL_SHIELD'],['Shirt',6,'T_SHIRT'],['Armor',0,'LEATHER_ARMOR']];
for(const[name,slot,type]of armor)for(const initial of [0,1]){reset();item(0,L[type]);equip(slot,0);hero(1,initial);act(name+'_on');reset();item(0,L[type]);equip(slot,0);act(name+'_off');assert.ok(state().includes('slot:'+slot+',-1;'));}
for(const type of ['SPEED_BOOTS','WATER_WALKING_BOOTS','FUMBLE_BOOTS','LEVITATION_BOOTS','ELVEN_BOOTS'])for(const on of [0,1]){reset();item(0,L[type]);equip(5,0);rolls(0);act(on?'Boots_on':'Boots_off');}
for(const type of ['CLOAK_OF_PROTECTION','CLOAK_OF_INVISIBILITY','CLOAK_OF_DISPLACEMENT','OILSKIN_CLOAK','ELVEN_CLOAK','ALCHEMY_SMOCK','MUMMY_WRAPPING'])for(const on of [0,1]){reset();item(0,L[type]);equip(1,0);act(on?'Cloak_on':'Cloak_off');}
for(const type of ['CORNUTHAUM','DUNCE_CAP','HELM_OF_BRILLIANCE','HELM_OF_OPPOSITE_ALIGNMENT','HELM_OF_TELEPATHY','HELM_OF_CAUTION'])for(const on of [0,1]){reset();item(0,L[type]);equip(2,0);act(on?'Helmet_on':'Helmet_off');}
for(const type of ['GAUNTLETS_OF_FUMBLING','GAUNTLETS_OF_POWER','GAUNTLETS_OF_DEXTERITY'])for(const on of [0,1]){reset();item(0,L[type]);equip(4,0);field(0,6,3);rolls(0);act(on?'Gloves_on':'Gloves_off');}

for(const type of ['BLACK','BLUE','GREEN','RED','GOLD','ORANGE','YELLOW'])for(const suffix of ['SCALES','SCALE_MAIL'])for(const on of [0,1]){reset();item(0,L[type+'_DRAGON_'+suffix]);equip(0,0);act('dragon_armor_handling',0,on,1);}
const amulets=['AMULET_OF_ESP','AMULET_OF_LIFE_SAVING','AMULET_OF_STRANGULATION','AMULET_OF_RESTFUL_SLEEP','AMULET_VERSUS_POISON','AMULET_OF_CHANGE','AMULET_OF_UNCHANGING','AMULET_OF_REFLECTION','AMULET_OF_MAGICAL_BREATHING','AMULET_OF_GUARDING','AMULET_OF_FLYING','AMULET_OF_YENDOR'];
for(const type of amulets)for(const on of [0,1]){reset();item(0,L[type]);equip(12,0);rolls(0);act(on?'Amulet_on':'Amulet_off',0);if(type==='AMULET_OF_CHANGE'&&on){assert.ok(trace().includes('useup:0;'));assert.ok(state().includes('o:0:null;'));}}
const rings=['RIN_ADORNMENT','RIN_AGGRAVATE_MONSTER','RIN_COLD_RESISTANCE','RIN_CONFLICT','RIN_FIRE_RESISTANCE','RIN_FREE_ACTION','RIN_GAIN_CONSTITUTION','RIN_GAIN_STRENGTH','RIN_HUNGER','RIN_INCREASE_ACCURACY','RIN_INCREASE_DAMAGE','RIN_INVISIBILITY','RIN_LEVITATION','RIN_POISON_RESISTANCE','RIN_POLYMORPH','RIN_POLYMORPH_CONTROL','RIN_PROTECTION','RIN_PROTECTION_FROM_SHAPE_CHAN','RIN_REGENERATION','RIN_SEARCHING','RIN_SEE_INVISIBLE','RIN_SHOCK_RESISTANCE','RIN_SLOW_DIGESTION','RIN_STEALTH','RIN_SUSTAIN_ABILITY','RIN_TELEPORTATION','RIN_TELEPORT_CONTROL','RIN_WARNING'];
for(const type of rings)for(const slot of [7,8])for(const spe of [-128,0,127])for(const n of ['Ring_on','Ring_off','Ring_gone']){reset();item(0,L[type]);equip(slot,0);field(0,6,spe);act(n,0);if(n!=='Ring_on')assert.ok(state().includes('slot:'+slot+',-1;'));}
for(const type of [L.BLINDFOLD,L.LENSES,L.TOWEL])for(const n of ['Blindf_on','Blindf_off']){reset();item(0,type);if(n==='Blindf_off')equip(13,0);act(n,0);assert.ok(state().includes('slot:13,'+(n==='Blindf_off'?-1:0)+';'));}
for(const n of ['on_msg','learnring','adjust_attrib','adj_abon']){reset();item(0,L.RIN_GAIN_STRENGTH);field(0,5,1);act(n,0,L.A_STR,3);}
for(const n of ['toggle_stealth','toggle_displacement'])for(const on of [-128,0,1,128,256,257]){reset();item(0,L.ELVEN_BOOTS);act(n,0,0,on);}
reset();item(0,L.HELMET);act('hard_helmet',0);reset();item(0,L.CORPSE);field(0,11,L.PM_COCKATRICE);item(1,L.YELLOW_DRAGON_SCALES);act('wielding_corpse',0,1,1);
// Delayed don/doff identities use actual native function pointers.
reset();item(0,L.LEATHER_ARMOR);equip(0,0);act('Armor_gone');assert.ok(state().includes('slot:0,-1;'));
for(const gone of [0,1]){reset();item(0,L.RIN_STEALTH);equip(7,0);act('Ring_off_or_gone',0,gone);assert.ok(state().includes('slot:7,-1;'));}
reset();act('set_wear',-1);reset();for(const[name,slot,type]of armor){item(slot,L[type]);equip(slot,slot);}act('set_wear',-1);
for(const id of [0,7,26]){reset();item(0,L.LEATHER_ARMOR);equip(0,0);hero(12,id);assert.equal(act('donning',0),id===0||id===7?1n:0n);assert.equal(act('doffing',0),id===7?1n:0n);}
reset();item(0,L.LEATHER_ARMOR);equip(0,0);hero(12,0);hero(13,-((1n<<53n)+7n));act('cancel_doff',0,constant('W_ARM'));assert.ok(state().includes('globals:-1,'));
for(const id of [0,7]){reset();item(0,L.LEATHER_ARMOR);equip(0,0);hero(12,id);hero(13,-3);act('stop_donning',0);assert.ok(state().includes('globals:-1,'));}
for(const[name,slot,type]of armor){reset();item(0,L[type]);equip(slot,0);act('armoroff',0);if(trace().includes('nomul:')){const bytes=modules.map(m=>{const p=Number(m._probe_pointer(3,0));assert.ok(p>0);return [...m.HEAPU8.slice(p,p+60)];});assert.deepEqual(bytes[1],bytes[0]);call('after');check();}assert.ok(state().includes('slot:'+slot+',-1;'));}
reset();input(0,'armor');act('already_wearing',0);act('already_wearing2',0,0);
// Real writable mask and object-reference outputs through private/public callers.
for(const[type,slot]of [['HELMET',2],['LEATHER_ARMOR',0],['LEATHER_GLOVES',4],['LOW_BOOTS',5],['SMALL_SHIELD',3],['T_SHIRT',6],['ELVEN_CLOAK',1]]){reset();item(0,L[type]);assert.equal(act('canwearobj',0,0,1),1n);act('accessory_or_armor_on',0);assert.ok(state().includes('slot:'+slot+',0;'));}
for(const n of ['armor_or_accessory_off','dotakeoff','ia_dotakeoff','doremring','cursed','equip_ok','puton_ok','remove_ok','wear_ok','takeoff_ok','select_off','better_not_take_that_off']){reset();item(0,n==='doremring'?L.RIN_ADORNMENT:L.HELMET);if(['armor_or_accessory_off','dotakeoff','ia_dotakeoff','remove_ok','takeoff_ok','select_off'].includes(n))equip(2,0);act(n,0,1,0);}
for(const n of ['dowear','doputon']){reset();item(0,L.HELMET);act(n);assert.ok(trace().includes('getobj:'));}
reset();item(0,L.RIN_LEVITATION);equip(7,0);field(0,0,1);assert.equal(act('stuck_ring',0,L.RIN_LEVITATION),0n);reset();item(0,L.AMULET_OF_UNCHANGING);equip(12,0);assert.equal(act('unchanger'),0n);
reset();item(0,L.HELMET);equip(2,0);act('glibr');reset();act('some_armor',0);
for(const n of ['do_takeoff','take_off']){reset();item(0,L.HELMET);equip(2,0);hero(10,constant('W_ARMH'));act(n);}
for(const n of ['doddoremarm','menu_remarm','remarm_swapwep']){reset();item(0,L.HELMET);equip(2,0);hero(19,L.MENU_FULL);act(n,0);}
for(const n of ['wornarm_destroyed','disintegrate_arm','destroy_arm','obj_erode_type']){reset();item(0,L.HELMET);equip(2,0);rolls(0);act(n,0);if(n==='wornarm_destroyed'||n==='disintegrate_arm')assert.ok(trace().includes('dispose:0;'));}
for(const resist of [0,1,128,256,257]){reset();item(0,L.HELMET);option('obj_resists',resist);act('maybe_destroy_armor',0,-1,0);}
reset();item(0,L.LEATHER_ARMOR);equip(0,0);item(1,L.ELVEN_CLOAK);equip(1,1);assert.equal(act('inaccessible_equipment',0,0,0),1n);
// Original native private table is the oracle; the hybrid has no C mirror.
assert.equal(core.takeoff_order.length,15);
core.takeoff_order.forEach((symbol,i)=>assert.equal(reference._probe_table(i),BigInt(symbol?constant(symbol):0)));
comparisons+=15;
// Header logical operators produce C int 0/1; raw long masks stay full width.
const macroNames=['Blind_telepat','Fast','Very_fast','Breathless','Levitation','Flying','Swimming','Invis','Invisible','Unchanging','Blind','Unblind_telepat'];
for(const property of ['TELEPAT','FAST','MAGICAL_BREATHING','LEVITATION','FLYING','SWIMMING','INVIS','UNCHANGING','BLINDED'])for(const bits of [256n,1n<<40n,-1n,1n<<63n]){
    reset();prop(L[property],0,bits);prop(L[property],1,bits);
    const s=servicesByModule.get(modules[1]),env=callDoWear(s,L,'environment');
    macroNames.forEach((name,i)=>{assert.equal(BigInt(env[name]),reference._probe_macro(i),name+' '+property+' '+bits);comparisons++;});
    check();
}
// Heap-owned queued commands are copied before the original policy frees them.
for(const key of [45,120]){
    reset();item(0,L.DAGGER);equip(10,0);option('cmdq_pop',1);call('option',514,key);call('poison');
    const result=act('remarm_swapwep');
    assert.equal(result,BigInt(key===45?L.ECMD_TIME:L.ECMD_FAIL));
    assert.ok(trace().includes('free:command;'));assert.ok(state().includes('policyfree:1,0,1;'));
    assert.ok(state().includes('slot:10,'+(key===45?-1:0)+';'));
}
// Foreign obj** mutation changes the actual local before subsequent policy reads.
reset();item(0,L.HELMET);item(1,L.HELMET);call('option',511,2);act('accessory_or_armor_on',0);assert.ok(state().includes('slot:2,1;'));
reset();item(0,L.HELMET);call('option',511,-1);option('retouch_object',1);act('accessory_or_armor_on',0);assert.ok(state().includes('slot:2,-1;'));
// A native callback replaces an equipment cell while the JS function is active.
reset();item(0,L.HELM_OF_OPPOSITE_ALIGNMENT);equip(2,0);call('mutation',deps.uchangealign,2,-1);act('Helmet_on');assert.ok(trace().includes('mutate:2:-1;'));assert.ok(state().includes('slot:2,-1;'));
// Actual heap growth and nested native -> JS entry preserve a nonempty outer scope.
reset();item(0,L.HELMET);call('callback',deps.setworn,deps.setworn);const checkpoints=modules.map(memoryCheckpoint);
const outer={rectState:{marker:'rect'},trackState:{marker:'track'}};
for(const m of modules){const sp=m._probe_stack();withCEnvironment(outer,()=>{m._probe_action(op('accessory_or_armor_on'),0n,0n,0n,0n);assert.equal(C,outer);assert.equal(R,outer.rectState);assert.equal(T,outer.trackState);});assertStackRestored(m,sp,m._probe_stack());}
check();modules.forEach((m,i)=>assertMemoryGrowth(m,checkpoints[i]));assert.ok(trace().includes('growth:'));assert.ok(trace().includes('reentry:'));
// MOREWORN remains one statement inside the original cloak/suit/shirt else chain.
for(const [slot,type] of [[0,L.LEATHER_ARMOR],[1,L.ELVEN_CLOAK],[6,L.T_SHIRT]]){reset();item(0,type);equip(slot,0);act('count_worn_stuff',0,0);assert.equal(call('counter',0,0,0),1);}
// Mounted flying is supplied solely by the actual native species flags.
reset();call('set_monster',0,L.PM_AIR_ELEMENTAL);hero(7,0);
let currentEnv=callDoWear(servicesByModule.get(modules[1]),L,'environment');
assert.equal(BigInt(currentEnv.Flying),reference._probe_macro(5));assert.notEqual(reference._probe_macro(5),0n);
prop(L.FLYING,2,1);assert.equal(BigInt(currentEnv.Flying),reference._probe_macro(5));assert.equal(reference._probe_macro(5),0n);
// Both native menu allocations are really released after the original callback selection.
reset();item(0,L.HELMET);equip(2,0);hero(19,L.MENU_FULL);option('query_category',1);call('option',503,L.ALL_TYPES_SELECTED);option('query_objlist',1);option('is_worn',1);act('menu_remarm',0);
assert.ok(trace().includes('filter:1;'));assert.ok(state().includes('policyfree:2,2,0;'));
// Unknown high mask bits survive a normal armor-off operation.
reset();item(0,L.HELMET);equip(2,0);const high=1n<<63n;field(0,2,high|BigInt(constant('W_ARMH')));act('Helmet_off');
for(const m of modules){const p=Number(m._probe_pointer(1,0));assert.equal(new FixtureDataView(m.HEAPU8.buffer).getBigUint64(p,true),high);}
// A poisoned stack must not leak bytes into the original zero-object dummy.
reset();item(0,L.RIN_ADORNMENT);equip(7,0);item(1,L.LEATHER_GLOVES);equip(4,1);prop(L.GLIB,0,1);call('poison');act('select_off',0);assert.ok(trace().includes('dummyzero:1;'));
// Disabled logging leaves the actual RNG call and state behavior intact.
reset();item(0,L.GAUNTLETS_OF_FUMBLING);equip(4,0);rolls(0);call('option',500,1);act('Gloves_on');assert.ok(trace().includes('rnd:'));assert.ok(!trace().includes('caller:'));
// Repeated selection of one live item is a defined menu stress input. Each
// source callee owns its automatic scratch, even within a single native entry.
const stressSpans=[];
for(const count of [1,1000]){
    reset();item(0,L.RIN_ADORNMENT);equip(7,0);item(1,L.LEATHER_GLOVES);equip(4,1);prop(L.GLIB,0,1);hero(19,L.MENU_FULL);option('query_category',1);call('option',503,L.ALL_TYPES_SELECTED);option('query_objlist',count);option('is_worn',1);call('clear');act('menu_remarm',0);
    assert.equal((trace().match(/dummyzero:1;/g)||[]).length,count);stressSpans.push(modules.map(m=>m._probe_stack_span()));
}
for(let i=0;i<modules.length;i++)assert.ok(stressSpans[1][i]<=stressSpans[0][i]+128,'native callback stack depth is independent of menu length');
writeFileSync(new URL('../.cache/do_wear-author/stack-spans.json',import.meta.url),JSON.stringify(stressSpans));
// All four some_armor draws are reached with actual hero equipment, not an
// empty controlled monster inventory; zero draws select the last candidate.
reset();for(const [name,slot,type]of armor){item(slot,L[type]);equip(slot,slot);}rolls(0);assert.equal(act('some_armor',-2),3n);
for(const line of [2641,2644,2647,2650])assert.ok(trace().includes('caller:do_wear.c:'+line+':some_armor;'));
// Two Modules use one dispatcher but retain independent private counters/backing.
reset();item(0,L.HELMET);equip(2,0);item(1,L.LEATHER_GLOVES);equip(4,1);act('count_worn_stuff',0,0);const primary=snapshot(modules[1]);
const other=await hyb({nethackPorted:ported});other._probe_reset(1);other._probe_object(0,L.HELMET,1n);other._probe_equipment(2,0);assert.equal(other._probe_action(op('count_worn_stuff'),0n,0n,0n,0n),0n);
assert.equal(other._probe_counter(0,0,0),1);assert.equal(modules[1]._probe_counter(0,0,0),2);assert.deepEqual(snapshot(modules[1]),primary);comparisons++;
writeFileSync(new URL('../.cache/do_wear-author/entered.json',import.meta.url),JSON.stringify({entered:[...exercised],remaining:names.filter(n=>!exercised.has(n))},null,2));
assert.deepEqual(names.filter(n=>!exercised.has(n)),[],'all79 original functions entered');
console.log('DO_WEAR '+fixtureReferenceLabel+': '+comparisons+' comparisons passed; all79 original functions, live callbacks, ownership, native memory growth and per-Module isolation.');
