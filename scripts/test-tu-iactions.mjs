import './pure-js-probes/deny-wasm.mjs';
import { assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('iactions', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/iactions-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('iactions',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import * as actions from '../js/ported/iactions.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),layout=layouts.iactions;
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:createPortedRuntime(layouts)})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){p=Number(p);if(n===undefined){if(!p)return null;let e=p;while(m.HEAPU8[e])e++;n=e-p;}return Buffer.from(m.HEAPU8.slice(p,p+n));}
function snapshot(m){return {rows:Array.from({length:m._probe_menu_count()},(_,i)=>({id:m._probe_menu_action(i),letter:m._probe_menu_letter(i),text:bytes(m,m._probe_menu_text(i)),anything:bytes(m,m._probe_menu_any(i),Number(m._probe_any_size()))})),output:[0,1].map(i=>bytes(m,m._probe_output(i),Number(m._probe_output_size()))),freed:m._probe_freed(),live:m._probe_live(),trace:bytes(m,m._probe_trace()).toString('hex')};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],`${name}(${args})`);state();comparisons++;return result[0];}
function reset(){call('reset');}
function item(type=layout.DAGGER,{quantity=1n,worn=0n,known=0,dknown=0,lit=0,unpaid=0,cknown=0,artifact=0,spe=0,letter=97}={}){call('item',type,quantity,worn,known,dknown,lit,unpaid,cknown,artifact,spe,letter);}
function trace(){return bytes(modules[0],modules[0]._probe_trace()).toString();}
function has(action){return snapshot(modules[0]).rows.some(row=>row.id===action);}
function add(action,letter,text){modules.forEach(m=>{const b=Buffer.from(text),p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;m._probe_add(action,letter,BigInt(p));m._free(p);});state();}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=bytes(m,m._probe_layout_name(i)).toString();assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),layout[key],key);}
for(const [key,value] of Object.entries(actions))if(key.startsWith('IA_'))assert.equal(value,layout[key],key);
for(const key of ['NUM_OBJECTS','MAXOCLASSES','DAGGER','LONG_SWORD','BOW','ARROW','IA_WHATIS_OBJ','ART_EYES_OF_THE_OVERWORLD'])assert.ok(Number.isSafeInteger(layout[key]),key);
// Exercise every configured real object against its actual class/skill/material
// table fields. Native callbacks retain naming, food and UI policy boundaries.
for(let typ=layout.MAXOCLASSES;typ<layout.NUM_OBJECTS;typ++){reset();item(typ);call('naming');call('reading');assert.equal(call('run'),layout.ECMD_OK);}
for(const named of [0,1,2,3])for(const called of [0,1,2])for(const quantity of [-1n,0n,1n,2n,9007199254740993n])for(const unique of [0,1]){reset();item(layout.DAGGER,{quantity});call('names',named,called);call('option',2,unique);assert.equal(call('naming'),1);}
for(const nameOk of [layout.GETOBJ_SUGGEST,layout.GETOBJ_DOWNPLAY,layout.GETOBJ_EXCLUDE])for(const callOk of [layout.GETOBJ_SUGGEST,layout.GETOBJ_DOWNPLAY,layout.GETOBJ_EXCLUDE]){reset();call('option',0,nameOk);call('option',1,callOk);call('naming');}
for(const discovered of [0,1]){reset();item(layout.LENSES,{artifact:layout.ART_EYES_OF_THE_OVERWORLD});call('option',10,discovered);call('naming');}
for(const type of [layout.FORTUNE_COOKIE,layout.T_SHIRT,layout.ALCHEMY_SMOCK,layout.HAWAIIAN_SHIRT,layout.SCR_BLANK_PAPER,layout.SCR_IDENTIFY,layout.SPE_NOVEL,layout.SPE_BLANK_PAPER,layout.SPE_BOOK_OF_THE_DEAD])for(const known of [0,1])for(const dknown of [0,1]){reset();item(type,{dknown});call('known',known);call('reading');}
// The whole anything union is copied from cg.zeroany before assigning a_int.
for(const action of [-2147483648,-1,0,layout.IA_WHATIS_OBJ,2147483647])for(const letter of [0,97,128,255]){reset();add(action,letter,'Fixture row');const data=snapshot(modules[0]).rows[0].anything;assert.equal(data.subarray(4).toString('hex'),'5a'.repeat(data.length-4));}
for(const action of [-1,...Array.from({length:layout.IA_WHATIS_OBJ+2},(_,i)=>i)])for(const slot of [-1,0,1,2]){reset();if(slot>=0)call('equipment',slot,1,layout.LONG_SWORD);call('push',action);}
for(const letter of [0,32,97,128,255]){reset();item(layout.DAGGER,{letter});call('push',layout.IA_WHATIS_OBJ);assert.ok(trace().includes(`key:${layout.CQ_CANNED}:${letter};`));}
// Selection is allocated by native select_menu, uses only the first selected
// row, and must be freed exactly once before queueing the chosen command.
for(const count of [-1,0,1,2])for(const action of [layout.IA_NONE,layout.IA_EAT_OBJ,layout.IA_WHATIS_OBJ,999]){reset();call('select',count,action,9007199254740993n);call('run');assert.equal(call('freed'),count>0?1:0);assert.equal(call('live'),0);if(count>0&&action===layout.IA_EAT_OBJ){assert.ok(trace().indexOf('free-selection;')<trace().indexOf('command:'));assert.ok(trace().includes('do_reqmenu'));assert.ok(trace().includes('doeat'));}}
for(const type of [layout.WAX_CANDLE,layout.TALLOW_CANDLE,layout.POT_OIL,layout.OIL_LAMP,layout.CANDELABRUM_OF_INVOCATION])for(const quantity of [1n,2n,9007199254740993n])for(const lit of [0,1])for(const carried of [0,1])for(const spe of [6,7]){reset();item(type,{quantity,lit});call('known',1);call('candelabrum',carried,spe);call('run');}
for(const type of [layout.BAG_OF_TRICKS,layout.HORN_OF_PLENTY,layout.SCR_BLANK_PAPER,layout.SPE_BLANK_PAPER,layout.SPE_BOOK_OF_THE_DEAD,layout.POT_OIL])for(const known of [0,1])for(const cknown of [0,1])for(const contents of [0,1])for(const spe of [-128,0,1]){reset();item(type,{cknown,spe});call('known',known);call('contents',contents);call('run');}
for(const type of [layout.CORPSE,layout.AMULET_OF_YENDOR,layout.FAKE_AMULET_OF_YENDOR])for(const altar of [0,1])for(const swallow of [0,1]){reset();item(type);call('hero',altar,swallow,0,0,0,0);call('run');assert.equal(has(layout.IA_SACRIFICE),Boolean(altar&&!swallow));}
for(const goldSlot of [0,1]){reset();item(layout.GOLD_PIECE,{quantity:2n});call('option',5,goldSlot);call('run');assert.equal(has(layout.IA_ADJUST_OBJ),Boolean(goldSlot));}
for(const shop of [0,1])for(const inside of [0,1])for(const unpaid of [0,1]){reset();item(layout.DAGGER,{unpaid});call('option',6,shop);call('option',7,inside);call('run');assert.equal(has(layout.IA_BUY_OBJ),Boolean(shop&&inside&&unpaid));}
for(const type of [layout.AMULET_OF_YENDOR,layout.MEAT_RING,layout.LENSES,layout.TOWEL,layout.DAGGER])for(const mask of [0n,BigInt(layout.W_AMUL),BigInt(layout.W_RING),BigInt(layout.W_TOOL),BigInt(layout.W_ARMOR)])for(const occupied of [0,1]){reset();item(type,{worn:mask});for(const slot of [3,4,5,6,7])call('equipment',slot,occupied?2:0,layout.LONG_SWORD);call('option',8,occupied);call('run');}
for(const type of [layout.ARROW,layout.DAGGER,layout.GOLD_PIECE,layout.TOWEL])for(const quantity of [0n,1n,2n,9007199254740993n,9223372036854775807n])for(const slot of [0,1,2])for(const launcher of [layout.BOW,layout.DAGGER]){reset();item(type,{quantity,spe:2});call('equipment',slot,1,layout.LONG_SWORD);if(slot!==0)call('equipment',0,2,launcher);call('run');}
for(const nohands of [0,1])for(const small of [0,1])for(const attacks of [0,1])for(const twoweap of [0,1])for(const shield of [0,1]){reset();item(layout.DAGGER);call('equipment',0,1,layout.LONG_SWORD);call('equipment',1,2,layout.LONG_SWORD);if(shield)call('equipment',7,2,layout.LONG_SWORD);call('hero',0,0,twoweap,nohands,small,attacks);call('run');}
reset();call('equipment',0,1,layout.LONG_SWORD);call('equipment',1,2,layout.LONG_SWORD);call('hero',0,0,0,0,0,1);call('run');assert.ok(has(layout.IA_TWOWEAPON));
reset();item(layout.ARROW,{quantity:9007199254740993n});call('equipment',2,1,layout.LONG_SWORD);call('equipment',0,2,layout.BOW);call('run');assert.ok(has(layout.IA_FIRE_OBJ));assert.ok(snapshot(modules[0]).rows.find(r=>r.id===layout.IA_FIRE_OBJ).text.toString().includes('Shoot'));
reset();call('select',1,layout.IA_WHATIS_OBJ,1n);call('run');assert.equal(call('freed'),1);assert.ok(trace().includes('dowhatis'));
reset();call('option',12,1);call('run');assert.ok(call('menu_count')>3);assert.ok(trace().includes('dodrop'));assert.ok(trace().includes(`key:${layout.CQ_CANNED}:98;`));
reset();item(layout.DAGGER,{unpaid:1});call('option',6,1);call('option',7,1);call('option',13,1);const callbackSizes=modules.map(m=>allocationMetric(m));call('run');modules.forEach((m,i)=>assert.ok(allocationMetric(m)>callbackSizes[i]));assert.ok(trace().includes('shop:-128;'));assert.ok(has(layout.IA_BUY_OBJ));
reset();const saved=snapshot(modules[0]);modules[1]._probe_push(layout.IA_EAT_OBJ);assert.deepEqual(snapshot(modules[0]),saved);reset();
const sizes=modules.map(m=>allocationMetric(m)),grown=modules.map(m=>m._malloc(BigInt(allocationMetric(m))+16n*1024n*1024n));assert.ok(grown.every(Boolean));modules.forEach((m,i)=>assert.ok(allocationMetric(m)>sizes[i]));item(layout.POT_OIL,{quantity:9007199254740993n});call('known',1);call('names',3,2);call('select',2,layout.IA_QUAFF_OBJ,9223372036854775807n);call('run');assert.equal(call('freed'),1);modules.forEach((m,i)=>m._free(grown[i]));state();
console.log(`IACTIONS: ${comparisons} ${referenceLabel}/pure-JS catalogue, naming, menu-union, selection ownership and command-queue comparisons checked.`);
