import './pure-js-probes/deny-wasm.mjs';
import {DataView,Int32Array,assertStackRestored,allocationMetric,referenceBackend,referenceLabel} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/worn-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('worn',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
import * as core from '../js/ported/worn.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.worn,runtime=createPortedRuntime(layouts),referenceFactory=referenceBackend('worn',emscriptenReferenceFactory);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function normalized(m,s){const labels=new Map();for(let i=0;i<32;i++){const p=BigInt(m._probe_pointer(0,i));if(p)labels.set('0x'+p.toString(16),`<obj${i}>`);}return s.replace(/0x[0-9a-f]+/gi,token=>labels.get(token.toLowerCase())??token);}
function snapshot(m){return{state:text(m,m._probe_snapshot()),trace:normalized(m,text(m,m._probe_trace())),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count(),frees:m._probe_free_count()};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(name,...args){const field={object:2,set_monster:2,hero:1,prop:2,action:4}[name];if(field!==undefined)args[field]=BigInt(args[field]);const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],name+':'+args);comparisons++;check();return values[0];}
const reset=(seed=1)=>call('reset',seed),opt=(k,v)=>call('option',k,v),obj=(i,k,v)=>call('object',i,k,v),mon=(i,k,v)=>call('set_monster',i,k,v),hero=(k,v)=>call('hero',k,v),prop=(p,k,v)=>call('prop',p,k,v),cls=(typ,k,v)=>call('class',typ,k,v),equip=(k,i)=>call('equip',k,i),link=(k,i)=>call('link',k,i),loot=(k,i)=>call('loot',k,i),act=(op,i=0,a=0,b=0,mask=0n)=>call('action',op,i,a,b,mask);
const mask=k=>BigInt(L[k]),state=()=>text(modules[0],modules[0]._probe_snapshot()),trace=()=>normalized(modules[0],text(modules[0],modules[0]._probe_trace()));
function fields(prefix,m=modules[0]){return text(m,m._probe_snapshot()).split(';').find(s=>s.startsWith(prefix+':')).split(':').slice(1);}
function rng(values){for(const m of modules){new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);}check();}
function inventory(items,owner=0){items.forEach((i,j)=>{obj(i,4,j+1<items.length?items[j+1]:-1);obj(i,12,L.OBJ_MINVENT);obj(i,13,owner);});mon(owner,1,items[0]??-1);}
function worn(i,type,slot,owner=0){obj(i,0,type);obj(i,1,mask(slot));mon(owner,2,BigInt(fields('m'+owner)[1])|mask(slot));}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['NUM_OBJECTS','NUMMONS','TELEPAT','INVIS','CLAIRVOYANT','BLINDED','FAST','FIRE_RES','POISON_RES','ACID_RES','SEE_INVIS','STONE_RES','PM_HUMAN','PM_HOBBIT','PM_MONK','PM_WIZARD','PM_GNOME','PM_KOBOLD','PM_SKELETON','PM_GHOST','PM_FOG_CLOUD','PM_IRON_GOLEM','PM_MINOTAUR','PM_MARILITH','PM_PLAINS_CENTAUR','PM_HORSE','PM_COCKATRICE','PM_GRAY_DRAGON','PM_LONG_WORM','HELMET','DUNCE_CAP','HELM_OF_OPPOSITE_ALIGNMENT','CORNUTHAUM','MUMMY_WRAPPING','ALCHEMY_SMOCK','SPEED_BOOTS','LEATHER_GLOVES','ELVEN_CLOAK','ELVEN_MITHRIL_COAT','PLATE_MAIL','HAWAIIAN_SHIRT','GRAY_DRAGON_SCALES','GRAY_DRAGON_SCALE_MAIL','AMULET_OF_GUARDING','AMULET_OF_LIFE_SAVING','AMULET_OF_REFLECTION','SADDLE','LONG_SWORD','TWO_HANDED_SWORD','MAGIC_MARKER','ART_EYES_OF_THE_OVERWORLD','OBJ_MINVENT','OBJ_FREE','OBJ_INVENT','OBJ_FLOOR','MFAST','MSLOW','AC_MAX','DISMOUNT_FELL','BOLT_LIM'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);
for(const k of ['W_ARM','W_ARMC','W_ARMH','W_ARMS','W_ARMG','W_ARMF','W_ARMU','W_RINGL','W_RINGR','W_WEP','W_SWAPWEP','W_QUIVER','W_AMUL','W_TOOL','W_BALL','W_CHAIN','W_SADDLE','W_ART','I_SPECIAL'])assert.ok(L[k]!==undefined,k);
// Independent original table order, text, sentinel and pointer-to-slot aliases.
assert.equal(core.worn.length,modules[0]._probe_worn_table_count());
for(let i=0;i<core.worn.length;i++){const row=core.worn[i];assert.equal(BigInt(row.w_mask?L[row.w_mask]:0),BigInt.asUintN(64,modules[0]._probe_worn_mask(i)));assert.equal(row.w_what||null,text(modules[0],modules[0]._probe_worn_what(i)));assert.equal(BigInt(modules[0]._probe_worn_cell(i)),i===16?0n:BigInt(modules[0]._probe_pointer(2,i)));comparisons++;}
const masks=['W_ARM','W_ARMC','W_ARMH','W_ARMS','W_ARMG','W_ARMF','W_ARMU','W_RINGL','W_RINGR','W_WEP','W_SWAPWEP','W_QUIVER','W_AMUL','W_TOOL','W_BALL','W_CHAIN'];
// The entire native object catalogue drives wear-slot classification.
for(let typ=0;typ<L.NUM_OBJECTS;typ++){obj(0,0,typ);act(7);}
for(const cat of [-2147483648,-1,0,1,2,3,4,5,6,7,8,255,2147483647])act(6,0,cat);
for(const key of masks){act(5,0,0,0,mask(key));act(5,0,0,0,mask(key)|(1n<<60n));}act(5,0,0,0,mask('W_ARM')|mask('W_ARMH'));
for(const slot of [0,2,7,8,9,10,11,12,13,14,15]){
 reset();obj(0,0,slot===9?L.LONG_SWORD:L.HELMET);cls(slot===9?L.LONG_SWORD:L.HELMET,0,L.TELEPAT);hero(2,1);hero(5,1);hero(6,1);link(0,0);obj(0,12,L.OBJ_INVENT);
 act(1,0,0,0,mask(masks[slot]));assert.equal(act(4,0,0,0,mask(masks[slot])),0n);assert.equal(fields('equip')[0].split(',')[slot],'0');
 assert.equal(fields('hero')[0],String(L.BOLT_LIM*L.BOLT_LIM));
 if(slot===10||slot===11)for(const m of modules)assert.equal(new DataView(m.HEAPU8.buffer).getBigInt64(Number(m._probe_pointer(6,0))+L.TELEPAT*L.propSize+L.prop_extrinsic,true),0n);
 act(2);assert.equal(act(4,0,0,0,mask(masks[slot])),-1n);assert.equal(fields('hero')[0],'-1');
}
reset();obj(0,0,L.MAGIC_MARKER);cls(L.MAGIC_MARKER,0,L.TELEPAT);act(1,0,0,0,mask('W_WEP'));assert.equal(fields('hero')[0],String(L.BOLT_LIM*L.BOLT_LIM));
// Recalc counts worn properties directly even when wielded tool grants none.
modules.forEach(m=>{const p=Number(m._probe_pointer(6,0))+L.TELEPAT*L.propSize+L.prop_extrinsic;assert.equal(new DataView(m.HEAPU8.buffer).getBigInt64(p,true),0n);});
reset();prop(L.TELEPAT,1,mask('W_ART'));act(0);assert.equal(fields('hero')[0],String(L.BOLT_LIM*L.BOLT_LIM));
reset();obj(0,0,L.GRAY_DRAGON_SCALES);act(1,0,0,0,mask('W_ARM')|mask('I_SPECIAL'));assert.equal(fields('equip')[0].split(',')[16],'0');assert.equal(fields('equip')[0].split(',')[0],'-1');
reset();equip(9,0);equip(10,0);obj(0,1,mask('W_WEP')|mask('W_SWAPWEP'));hero(1,-1);act(2);assert.equal(fields('hero')[1],'0');assert.equal(fields('equip')[0].split(',')[9],'-1');act(2,-1);act(3);
for(const role of [L.PM_MONK,L.PM_HUMAN]){reset();hero(0,role);hero(10,-7);act(1,0,0,0,mask('W_ARM'));assert.equal(fields('hero')[5],role===L.PM_MONK?'1':'0');act(2);assert.equal(fields('hero')[5],'0');}
for(const [type,slot,role]of [[L.MUMMY_WRAPPING,1,L.PM_HUMAN],[L.CORNUTHAUM,2,L.PM_HUMAN],[L.CORNUTHAUM,2,L.PM_WIZARD],[L.HELMET,13,L.PM_HUMAN]]){reset();hero(0,role);obj(0,0,type);if(slot===13)obj(0,8,L.ART_EYES_OF_THE_OVERWORLD);act(1,0,0,0,mask(masks[slot]));act(2);}
reset();equip(2,0);obj(0,1,0);act(8);assert.ok(trace().includes('not found in invent'));link(0,0);act(8);assert.ok(trace().includes('bit not set'));obj(0,1,mask('W_ARMH')|mask('W_ARMF'));act(8);assert.ok(trace().includes('wrong bit'));obj(0,1,mask('W_ARMH'));act(8);obj(0,4,1);obj(1,1,mask('W_ARMH'));act(8);assert.ok(trace().includes('mask'));
// which_armor's hero path reads the live equipment slot, unlike minvent scans.
reset();for(let slot=0;slot<7;slot++){equip(slot,slot);assert.equal(act(15,8,0,0,mask(masks[slot])),BigInt(slot));}assert.equal(act(15,8,0,0,mask('W_AMUL')),-1n);assert.ok(trace().includes('bad flag in which_armor'));
// Clearing a worn slot must retain unrelated bits across the full native long.
reset();const highBit=1n<<63n;obj(0,1,highBit|mask('W_ARMH'));cls(L.HELMET,0,L.TELEPAT);equip(2,0);prop(L.TELEPAT,1,highBit|mask('W_ARMH'));
function exactHighMasks(expected){for(const m of modules){const view=new DataView(m.HEAPU8.buffer);assert.equal(view.getBigUint64(Number(m._probe_pointer(0,0))+L.obj_owornmask,true),expected);assert.equal(view.getBigUint64(Number(m._probe_pointer(6,0))+L.TELEPAT*L.propSize+L.prop_extrinsic,true),expected);}}
exactHighMasks(highBit|mask('W_ARMH'));assert.equal(act(4,0,0,0,highBit|mask('W_ARMH')),0n);act(2);exactHighMasks(highBit);
// Packed invisibility and speed flags, including noncanonical C booleans.
for(const potion of [-1,0,1,128,256,257])for(const blocked of [0,1])for(const worm of [0,1]){reset();mon(0,10,blocked);mon(0,11,worm);act(9,0,potion);assert.equal(fields('m0')[9],String((potion<<24>>24)?0:1));}
for(const speed of [0,L.MFAST,L.MSLOW,3])for(const adjust of [-5,-4,-3,-2,-1,0,1,2,3])for(const wornBoots of [0,1]){reset();mon(0,6,speed);mon(0,7,speed);if(wornBoots){inventory([0]);worn(0,L.SPEED_BOOTS,'W_ARMF');}act(10,0,adjust,0);if(wornBoots)assert.equal(fields('m0')[7],String(L.MFAST));}
for(const visible of [0,1])for(const sleep of [0,1])for(const frozen of [0,1]){reset();opt(1,visible);mon(0,12,sleep);mon(0,14,frozen);act(10,0,1,0);assert.equal(trace().includes('learn:'),!!(visible&&!sleep&&!frozen));}
// Goto-again: both smock properties are removed independently, retaining any
// second worn source. No-property wrapping still reaches maybe_blocks.
for(const on of [0,1,256,257])for(const extra of [0,1])for(const silently of [0,1,-1]){reset();inventory(extra?[0,1]:[0]);worn(0,L.ALCHEMY_SMOCK,'W_ARMC');if(extra){worn(1,L.LEATHER_GLOVES,'W_ARMG');cls(L.LEATHER_GLOVES,0,L.ACID_RES);}mon(0,2,mask('W_ARMC')|mask('W_ARMG'));act(11,0,0,1,silently);act(11,0,0,on,silently);}
for(const kind of [L.MUMMY_WRAPPING,L.SPEED_BOOTS,L.HELMET])for(const on of [0,1]){reset();inventory([0]);obj(0,0,kind);if(kind===L.HELMET)cls(kind,0,0);mon(0,9,1);act(11,0,0,on,0);}
reset();inventory([0]);worn(0,L.SADDLE,'W_SADDLE');hero(7,0);act(11,0,0,0,0);assert.ok(trace().includes(`dismount:${L.DISMOUNT_FELL}:0;`));assert.equal(fields('hero')[8],'-1');
// Armor bonus, erosion, signed spe and the positive/negative AC cap.
for(const spe of [-128,-1,0,127])for(const erosion of [0,1,3]){reset();inventory([0,1]);worn(0,L.PLATE_MAIL,'W_ARM');worn(1,L.AMULET_OF_GUARDING,'W_AMUL');obj(0,2,spe);obj(0,10,erosion);act(12);}
for(const ac of [-128,127]){reset();inventory([0]);worn(0,L.PLATE_MAIL,'W_ARM');cls(L.PLATE_MAIL,1,ac);obj(0,2,ac);assert.ok(Math.abs(Number(act(12)))<=L.AC_MAX);}
// Goto-outer_break: life-saving/reflection wins without scanning later armor.
for(const type of [L.AMULET_OF_GUARDING,L.AMULET_OF_LIFE_SAVING,L.AMULET_OF_REFLECTION])for(const creation of [0,1,256]){reset();inventory([0,1]);obj(0,0,L.AMULET_OF_GUARDING);obj(1,0,type);act(14,0,creation,0,mask('W_AMUL'));assert.equal(act(15,0,0,0,mask('W_AMUL')),type===L.AMULET_OF_GUARDING?0n:1n);}
for(const type of [L.SPEED_BOOTS,L.DUNCE_CAP,L.HELM_OF_OPPOSITE_ALIGNMENT,L.MUMMY_WRAPPING,L.ELVEN_MITHRIL_COAT])for(const creation of [0,1])for(const cursed of [0,1]){reset();inventory([0,1]);obj(0,0,type);obj(1,0,type);obj(1,2,3);obj(0,7,cursed);const slot=type===L.SPEED_BOOTS?'W_ARMF':type===L.MUMMY_WRAPPING?'W_ARMC':type===L.ELVEN_MITHRIL_COAT?'W_ARM':'W_ARMH';obj(0,1,mask(slot));mon(0,2,mask(slot));act(14,0,creation,0,mask(slot));assert.equal(act(15,0,0,0,mask(slot)),cursed?0n:1n);}
for(const priest of [0,1])for(const minion of [0,1]){reset();inventory([0]);obj(0,0,L.HELM_OF_OPPOSITE_ALIGNMENT);mon(0,15,priest);mon(0,16,minion);act(14,0,1,0,mask('W_ARMH'));assert.equal(act(15,0,0,0,mask('W_ARMH')),priest||minion?-1n:0n);}
for(const pm of [L.PM_HUMAN,L.PM_HOBBIT,L.PM_GNOME,L.PM_KOBOLD,L.PM_SKELETON,L.PM_GHOST,L.PM_FOG_CLOUD,L.PM_MINOTAUR,L.PM_MARILITH,L.PM_PLAINS_CENTAUR,L.PM_HORSE])for(const creation of [0,1]){reset();mon(0,0,pm);inventory([0,1,2]);obj(0,0,L.SPEED_BOOTS);obj(1,0,L.ELVEN_CLOAK);obj(2,0,L.ELVEN_MITHRIL_COAT);act(13,0,creation);}
reset();inventory([0]);obj(0,0,L.DUNCE_CAP);act(14,0,0,0,mask('W_ARMH'));assert.equal(fields('o0')[10],'1');assert.ok(trace().includes('curse:0;'));
reset();inventory([0]);obj(0,0,L.HELMET);obj(0,8,L.ART_EYES_OF_THE_OVERWORLD);opt(3,1);act(14,0,0,0,mask('W_ARMH'));assert.ok(trace().includes('begin:0:0;'));assert.equal(fields('o0')[11],'1');
for(const visible of [0,1])for(const location of [0,1]){reset();opt(1,visible);opt(7,location);inventory([0]);obj(0,8,L.ART_EYES_OF_THE_OVERWORLD);opt(3,1);act(14,0,0,0,mask('W_ARMH'));assert.equal(trace().includes('Something begins to shine'),!!(!visible&&location));}
// Bypass recursion spans every real global chain, dead versus live monsters,
// migrating followers, contents, floating ball/chain and corpse extra fields.
reset();for(let i=0;i<16;i++)obj(i,6,1);for(let k=0;k<6;k++)link(k,k);obj(0,5,6);obj(6,5,7);mon(0,1,8);mon(1,1,9);mon(2,1,10);mon(3,1,11);mon(0,4,1);mon(1,5,0);link(6,0);link(7,2);link(8,3);mon(0,0,L.PM_LONG_WORM);mon(0,18,L.PM_LONG_WORM);equip(14,12);equip(15,13);hero(11,1);act(18);assert.equal(fields('o9')[9],'1');for(const i of [0,1,2,3,4,5,6,7,8,10,11,12,13])assert.equal(fields('o'+i)[9],'0');assert.equal(fields('m0')[18],'-1');assert.equal(fields('hero')[7],'0');
reset();obj(0,4,1);obj(1,4,2);obj(0,5,3);obj(3,6,1);act(17);assert.equal(fields('o3')[9],'0');act(20,0,-1);assert.equal(act(21),-1n);act(20,0,256);assert.equal(act(21),0n);assert.equal(act(21),1n);assert.equal(act(21),2n);assert.equal(act(21),-1n);act(17,-1);act(20,-1,1);
reset();obj(0,4,1);loot(0,2);loot(1,1);loot(2,0);loot(3,-1);assert.equal(act(22),1n);assert.equal(act(22),0n);assert.equal(act(22),-1n);
// True ownership transfer/free, worn light before mask clearing, dead guards,
// and native callback round trips into original extract_from_minvent.
for(const extras of [0,1,256,257])for(const silently of [0,1])for(const dead of [0,1]){reset();inventory([0,1]);worn(0,L.LONG_SWORD,'W_WEP');mon(0,3,0);if(dead)mon(0,5,0);act(26,0,0,extras,silently);assert.equal(fields('o0')[4],String(L.OBJ_FREE));assert.equal(fields('m0')[2],'1');assert.ok(trace().includes('weapon-gone:0;'));}
reset();obj(0,12,L.OBJ_INVENT);act(26,0,0,1);assert.ok(trace().includes('not in minvent'));
for(const poly of [0,1,-1,256]){reset();inventory([0]);worn(0,L.HELMET,'W_ARMH');act(16,0,0,poly);assert.equal(fields('o0')[4],String(L.OBJ_FLOOR));assert.equal(fields('o0')[9],(poly<<24>>24)?'1':'0');}
for(const pm of [L.PM_IRON_GOLEM,L.PM_GHOST,L.PM_FOG_CLOUD,L.PM_HOBBIT,L.PM_MINOTAUR,L.PM_MARILITH,L.PM_PLAINS_CENTAUR,L.PM_GRAY_DRAGON])for(const artifact of [0,1])for(const poly of [0,1]){reset();mon(0,0,pm);inventory([0,1,2,3,4,5,6]);for(const[i,type,slot]of [[0,L.GRAY_DRAGON_SCALES,'W_ARM'],[1,L.ELVEN_CLOAK,'W_ARMC'],[2,L.HAWAIIAN_SHIRT,'W_ARMU'],[3,L.HELMET,'W_ARMH'],[4,L.LEATHER_GLOVES,'W_ARMG'],[5,L.SPEED_BOOTS,'W_ARMF'],[6,L.SADDLE,'W_SADDLE']])worn(i,type,slot);if(artifact)obj(1,8,L.ART_EYES_OF_THE_OVERWORLD);opt(4,0);act(23,0,poly);}
reset();mon(0,0,L.PM_IRON_GOLEM);inventory([0]);worn(0,L.PLATE_MAIL,'W_ARM');act(23);assert.equal(call('free_count'),1);assert.ok(state().includes('o0:freed'));equip(0,32);act(3);assert.equal(fields('equip')[0].split(',')[0],'-1');
for(const pronoun of [0,1,2,3]){reset();opt(6,pronoun);mon(0,0,L.PM_IRON_GOLEM);inventory([0]);worn(0,L.PLATE_MAIL,'W_ARM');act(23);assert.ok(trace().includes('breaks out of'));}

reset();mon(0,0,L.PM_IRON_GOLEM);inventory([0]);worn(0,L.PLATE_MAIL,'W_ARM');loot(0,0);act(23);loot(1,1);loot(2,-1);loot(0,32);assert.equal(act(22,1),1n);
for(const stone of [0,1])for(const roll of [0,1]){reset();mon(0,0,L.PM_COCKATRICE);hero(7,0);opt(4,0);opt(5,0);if(stone)prop(L.STONE_RES,1,1);rng([roll]);act(23);assert.equal(trace().includes('petrify:'),!!(!stone&&roll));assert.equal(modules[0]._probe_rng_count(),stone?0:1);assert.equal(fields('hero')[8],'-1');}
for(const pm of [L.PM_HUMAN,L.PM_HOBBIT])for(let typ=0;typ<L.NUM_OBJECTS;typ++){mon(0,0,pm);obj(0,0,typ);act(25,0,0);}
for(const speed of [0,L.MFAST,L.MSLOW])for(const type of [L.HELMET,L.SPEED_BOOTS]){reset();mon(0,6,speed);obj(0,0,type);assert.equal(act(24,0,0),type===L.SPEED_BOOTS&&speed!==L.MFAST?20n:0n);act(24,0,-1);}
// Callback replacement is observed by the final recalc through actual slot
// lvalues. Heap growth/reentry exercise fresh views at twelve native boundaries.
reset();obj(0,0,L.HELMET);obj(1,0,L.HELMET);cls(L.HELMET,0,L.TELEPAT);opt(32,3);opt(33,2);opt(34,1);act(1,0,0,0,mask('W_ARMH'));assert.equal(fields('equip')[0].split(',')[2],'1');assert.equal(fields('hero')[0],String(L.BOLT_LIM*L.BOLT_LIM));
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13]){reset();opt(30,stage);opt(31,stage);const before=modules.map(allocationMetric);
 if(stage===1){equip(2,0);obj(0,1,mask('W_ARMH'));act(2);}
 else if(stage===2){obj(0,8,L.ART_EYES_OF_THE_OVERWORLD);act(1,0,0,0,mask('W_ARMH'));}
 else if(stage===3)act(1,0,0,0,mask('W_ARMH'));
 else if(stage===4){equip(2,0);obj(0,1,mask('W_ARMH'));act(2);}
 else if(stage===5)act(10,0,1,0);
 else if(stage===6)act(9,0,0);
 else if(stage===7){inventory([0]);act(26,0,0,1);}
 else if(stage===8){inventory([0]);act(16,0,0);}
 else if(stage===9){mon(0,0,L.PM_IRON_GOLEM);inventory([0]);worn(0,L.PLATE_MAIL,'W_ARM');act(23);}
 else if(stage===10||stage===12){inventory([0]);obj(0,8,L.ART_EYES_OF_THE_OVERWORLD);opt(3,1);act(14,0,0,0,mask('W_ARMH'));}
 else if(stage===11){inventory([0]);worn(0,L.SADDLE,'W_SADDLE');hero(7,0);act(11,0,0,0);}
 else act(10,0,1,0);
 assert.ok(trace().includes(`grow:${stage};`),`growth ${stage}`);assert.ok(trace().includes('nested:'));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>before[i]));
}
reset();inventory([0]);obj(0,0,L.SPEED_BOOTS);for(let i=0;i<120;i++)act(13,0,1);
reset();opt(0,0);mon(0,0,L.PM_COCKATRICE);hero(7,0);opt(4,0);rng([1]);act(23);assert.ok(trace().includes('rnl:3:1@;'));
// Same runtime, a second actual module, and a real JS equipment update.
reset();obj(0,0,L.HELMET);act(1,0,0,0,mask('W_ARMH'));const saved=modules.map(snapshot),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(7);other._probe_action(1,0,0,0,mask('W_ARMH'));assert.ok(text(other,other._probe_snapshot()).includes('equip:-1,-1,0,'));modules.forEach((m,i)=>assert.deepEqual(snapshot(m),saved[i]));check();
console.log(`WORN: ${comparisons} ${referenceLabel}/pure-JS full state, equipment, armor, ownership, callbacks and RNG comparisons checked.`);
