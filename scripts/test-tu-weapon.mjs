import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
const nativeWeaponServices=new WeakMap();
function weaponServices(s){if(process.env.NATIVE_WEAPON_FIXTURE!=='1')return s;let local=nativeWeaponServices.get(s);if(!local){local=nativeFixtureServices(s,{}).services;local.nativeWeaponTypes=s.moduleKey.environment.ctypes;nativeWeaponServices.set(s,local);}return local;}
import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
// EmC-first original C against imported JS. Native parity is a follow-up;
// controlled dependencies are described in the integration plan.
import assert from './native-test-assert.mjs';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import { callWeapon } from '../js/nethack/bindings/weapon.js';
import * as core from '../js/ported/weapon.js';
import { C,R,T } from '../js/c-runtime/context.js';
const dir=resolve(process.env.TELEPORT_WEAPON_PROBE_DIR??'.cache/tu-probes');
const {default:rf}=await loadFixture("weapon",pathToFileURL(resolve(dir,process.env.TELEPORT_WEAPON_PROBE_DIR?'reference.mjs':'weapon-reference.mjs')));
const {default:hf}=await loadFixture("weapon",pathToFileURL(resolve(dir,process.env.TELEPORT_WEAPON_PROBE_DIR?'hybrid.mjs':'weapon-hybrid.mjs')));
const reference=await rf();
function text(m,p){p=Number(p);if(!p)return null;let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
const L={};for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
const runtime={weapon:(services,name,...args)=>callWeapon(weaponServices(services),L,name,...args)};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context="";
function snapshot(m){return{trace:text(m,m._probe_trace()),state:text(m,m._probe_snapshot()),output:text(m,m._probe_output())};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(name,...args){const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],name+'('+args.join(',')+') '+context+' '+text(reference,reference._probe_snapshot()).slice(0,250));check();return r[0];}
function reset(){call('reset');}
function action(op,a=0,b=0,c=0,mask=0n){return call('action',op,a,b,c,BigInt(mask));}
function item(typ,index=0,spe=0){call('item',index,typ,L.NON_PM,L.OBJ_INVENT,spe);}
function field(index,key,value){call('item_field',index,key,BigInt(value));}
function monster(pm,wield=-1,check=L.NEED_HTH_WEAPON,worn=0n){call('mon',0,pm,wield,check,BigInt(worn));}
function trace(){return text(reference,reference._probe_trace());}
function output(){return text(reference,reference._probe_output());}
function state(){return text(reference,reference._probe_snapshot());}
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
const names=['skill_names_indices','odd_skill_names','barehands_or_martial','kebabable','rwep','pwep','arwep','hwep','skill_ranges'];
const val=value=>typeof value==='string'?L[value]:value;
for(const[table,name]of names.entries()){
 const rows=core[name];assert.equal(reference._probe_table_count(table),rows.length);
 rows.forEach((row,i)=>{
  if(table===1||table===2)assert.equal(text(reference,reference._probe_table_text(table,i)),row);
  else if(table===6)for(const[k,key]of ['otyp','range','tethered'].entries())assert.equal(reference._probe_table_value(table,i,k),val(row[key]));
  else if(table===8){assert.equal(reference._probe_table_value(table,i,0),L[row.first]);assert.equal(reference._probe_table_value(table,i,1),L[row.last]);assert.equal(text(reference,reference._probe_table_text(table,i)),row.name);}
  else assert.equal(reference._probe_table_value(table,i,0),val(row));
 });
}
// All skill-name alternatives and exact skill level strings.
for(let skill=0;skill<L.P_NUM_SKILLS;skill++)for(const role of [L.PM_ARCHEOLOGIST,L.PM_MONK,L.PM_SAMURAI]){
 reset();call('hero',10,role,-1,0,0);action(0,skill);action(20,skill);
 for(const level of [0,1,2,3,4,5,6,9]){call('skill',skill,level,6,0);action(19,skill);}
}
for(const typ of [L.CORPSE,L.TIN,L.EGG,L.STATUE,L.BOULDER,L.TOWEL,L.TIN_OPENER,L.ROCK,L.FLINT,L.DAGGER,L.ARROW,L.CROSSBOW_BOLT,L.GRAPPLING_HOOK,L.DWARVISH_MATTOCK,L.CREAM_PIE]){reset();item(typ);action(1);action(34);}
reset();item(L.CREAM_PIE);field(0,11,1);action(1);assert.equal(output(),'glob');assert.equal(action(34,-1),L.P_BARE_HANDED_COMBAT);
// Every damage-case die, plus blessing/silver/light/artifact and erosion edges.
const damageTypes=[L.CREAM_PIE,L.IRON_CHAIN,L.CROSSBOW_BOLT,L.MORNING_STAR,L.FLAIL,L.ACID_VENOM,L.BATTLE_AXE,L.TSURUGI,L.DWARVISH_MATTOCK,L.MACE,L.SILVER_MACE,L.WAR_HAMMER,L.BILL_GUISARME,L.HEAVY_IRON_BALL,L.TRIDENT,L.PICK_AXE,L.AXE,L.SPEAR,L.DAGGER];
for(const typ of damageTypes)for(const pm of [L.PM_HUMAN,L.PM_RED_DRAGON,L.PM_SHADE,L.PM_WOOD_GOLEM,L.PM_GREMLIN,L.PM_XORN,L.PM_GIANT_EEL])for(const mode of [0,1]){
 context=JSON.stringify({typ,pm,mode});reset();item(typ,0,mode?3:-3);monster(pm);call('option',0,1);
 if(mode){for(const i of [1,2,3,7])call('option',i,1);call('option',4,5);call('option',5,25);call('option',6,1);field(0,3,1);field(0,4,1);field(0,6,1);field(0,7,2);field(0,2,1000);}
 action(2);action(3);
}
// Monster type + material selection and unusually weighted iron ball.
for(const weight of [0,480,640,1000,1600]){reset();item(L.HEAVY_IRON_BALL);field(0,2,weight);call('option',0,1);action(3);}
for(const pm of [L.PM_HUMAN,L.PM_GIANT_EEL,L.PM_XORN,L.PM_EARTH_ELEMENTAL]){reset();item(L.TRIDENT);monster(pm);for(const pool of [0,1]){call('option',3,pool);action(2);}}
// Silver long mask output, nullable pointer, multiple armor precedence, rings.
for(const mask of [BigInt(L.W_ARMC)|BigInt(L.W_ARM)|BigInt(L.W_ARMU),BigInt(L.W_ARMG)|BigInt(L.W_RINGL)|BigInt(L.W_RINGR),BigInt(L.W_RINGL),BigInt(L.W_RINGR),0n])for(const attacker of [0,1])for(const out of [0,1]){
 reset();item(L.SILVER_MACE,0);call('inventory',0,0);field(0,1,mask);field(0,4,1);call('option',1,1);call('option',2,1);call('option',0,1);call('equipment',0,0);call('equipment',1,0);action(4,attacker,out,0,mask);action(5,0,0,0,mask);
}
reset();item(L.SILVER_MACE);field(0,1,1n<<60n);call('inventory',0,0);call('option',2,1);action(4,1,1,0,1n<<60n);assert.match(state(),/silver:1152921504606846976;/);
// Original private return record has stable native address/typed consumer.
for(const typ of [L.AKLYS,L.DAGGER]){reset();item(typ);action(7);if(typ===L.AKLYS){modules.forEach(m=>{assert.equal(m._probe_arw(0),L.AKLYS);assert.equal(m._probe_arw(1),L.AKLYS_RANGE);assert.equal(m._probe_arw(2),1);});const pointers=modules.map(m=>m._probe_pointer(4));action(7);modules.forEach((m,i)=>assert.equal(m._probe_pointer(4),pointers[i]));}}
reset();item(L.SILVER_MACE);field(0,1,BigInt(L.W_ARMC));call('inventory',0,0);call('option',2,1);action(4,1,2,0,BigInt(L.W_ARMC));
// Weapon selection with real source ordering, petrifying corpse/egg filters,
// hands sentinel, launchers, welded conflicts, artifacts and ability gates.
for(const typ of core.rwep.map(val)){reset();item(typ);call('inventory',0,0);action(9);action(6,typ);action(8);}
for(const typ of core.hwep.map(val)){reset();item(typ);call('inventory',0,0);action(10);}
for(const pm of [L.PM_HUMAN,L.PM_BALROG,L.PM_COCKATRICE])for(const typs of [[L.CORPSE,L.EGG],[L.DART,L.DAGGER],[L.ARROW,L.BOW],[L.LOADSTONE,L.ROCK],[L.AKLYS,L.DAGGER],[L.HALBERD,L.PICK_AXE]])for(const safe of [0,1]){
 reset();item(typs[0],0);item(typs[1],1);call('next',0,1);call('inventory',0,0);monster(pm);call('option',8,safe);call('equipment',2,0);action(8);action(10);
}
for(const pm of [L.PM_HUMAN,L.PM_RED_DRAGON,L.PM_HILL_GIANT]){
 reset();item(L.TOUCHSTONE);item(L.SLING,1);call('next',0,1);call('inventory',0,0);monster(pm);action(8);
 reset();item(L.BOULDER);call('inventory',0,0);monster(pm);action(8);
}
reset();item(L.CORPSE);call('item',0,L.CORPSE,L.PM_COCKATRICE,L.OBJ_MINVENT,0);call('inventory',0,0);assert.equal(action(6,L.CORPSE),0);
for(const request of [L.NO_WEAPON_WANTED,L.NEED_HTH_WEAPON,L.NEED_RANGED_WEAPON,L.NEED_PICK_AXE,L.NEED_AXE,L.NEED_PICK_OR_AXE,99])for(const cursed of [0,1])for(const seen of [0,1]){
 reset();item(L.DAGGER,0);item(L.PICK_AXE,1);item(L.AXE,2);call('next',0,1);call('next',1,2);call('inventory',0,0);monster(L.PM_HUMAN,cursed?0:-1,request);field(0,1,BigInt(L.W_WEP));field(0,5,cursed);call('option',11,seen);action(12);
}
reset();item(L.PICK_AXE);field(0,5,1);call('inventory',0,0);monster(L.PM_HUMAN,-1,L.NEED_PICK_AXE);action(12);assert.equal(state().split('items:')[1].split(',')[0].split('/')[6],'1');assert.match(trace(),/itself/);
reset();item(L.DAGGER);field(0,3,1);call('option',7,1);call('inventory',0,0);monster(L.PM_HUMAN);assert.equal(action(12),1);assert.match(trace(),/begin:/);action(39,0);assert.match(trace(),/end:/);
for(const attack of [0,1])for(const drop of [0,1]){reset();item(L.DAGGER);call('inventory',0,0);monster(L.PM_HUMAN,0);field(0,1,BigInt(L.W_WEP));call('option',10,attack);call('option',12,drop);action(11,1);action(13);}
// Strength/dexterity thresholds, polymorph and towel clipping/ownership.
for(const strength of [3,5,6,7,8,15,16,17,18,19,67,68,93,108,117,118,125])for(const dex of [3,4,5,6,7,8,13,14,18]){reset();call('option',14,strength);call('option',15,dex);action(14);action(15);}
reset();call('hero',1,L.PM_MONK,L.PM_RED_DRAGON,0,0);action(14);action(15);
for(const spe of [0,1,2,3,6,7])for(const amount of [-12,-3,-1,0,1,3,8,12])for(const where of [L.OBJ_INVENT,L.OBJ_MINVENT]){
 reset();call('item',0,L.TOWEL,L.NON_PM,where,spe);call('equipment',2,0);action(17,0,amount,1);action(18,0,amount,1);action(16,0,amount);
}
// Skill progression, ushort practice wrap, slot/record width, and all menus.
for(let skill=1;skill<L.P_NUM_SKILLS;skill++)for(const level of [0,1,2,3,4,5,6]){
 reset();call('skill',skill,level,Math.min(6,level+1),level*level*20);call('counts',3,0);action(21,skill);action(22,skill);action(23,skill);action(24,skill);action(29,skill);action(30,skill,1);
}
for(const wizard of [0,1])for(const tabs of [0,1])for(const speedy of [0,1]){
 reset();call('skill',L.P_DAGGER,1,4,100);call('skill',L.P_ATTACK_SPELL,2,4,100);call('skill',L.P_BARE_HANDED_COMBAT,6,6,1000);call('counts',3,0);call('menu',wizard,tabs,1,L.P_DAGGER);call('option',19,speedy);action(26,1,speedy);action(27);action(28);assert.match(trace(),/menu:/);assert.match(trace(),/any:5a5a5a5a/);
}
reset();call('skill',L.P_DAGGER,1,4,65535);action(30,L.P_DAGGER,2);assert.match(state(),/1:4:1,/);
reset();call('skill',L.P_DAGGER,1,4,1000);call('counts',3,0);action(25,L.P_DAGGER);action(31,2);action(32,4);
reset();call('skill',L.P_DAGGER,3,4,1000);call('skill',L.P_AXE,2,4,1000);call('counts',0,3);call('record',0,L.P_DAGGER);call('record',1,L.P_AXE);call('record',2,L.P_DAGGER);call('option',0,1);action(33,3);assert.match(trace(),/caller:weapon.c:1489:drain_weapon_skill/);
for(const role of [L.PM_HEALER,L.PM_MONK,L.PM_CLERIC,L.PM_WIZARD,L.PM_ARCHEOLOGIST]){
 reset();item(L.DAGGER);call('inventory',-1,0);call('hero',10,role,-1,0,0);call('matrix',0,L.P_DAGGER,4);call('matrix',1,L.P_BARE_HANDED_COMBAT,6);call('matrix',2,L.P_NONE,0);call('role',L.PM_PONY,L.SPE_FORCE_BOLT,0);action(38);assert.match(trace(),/books/);
}
for(const skill of [L.P_DAGGER,L.P_TWO_WEAPON_COMBAT,L.P_BARE_HANDED_COMBAT])for(const level of [0,1,2,3,4,5,6,10])for(const steed of [0,1]){
 reset();item(L.DAGGER);call('equipment',2,0);call('hero',10,L.PM_MONK,-1,steed,skill===L.P_TWO_WEAPON_COMBAT?1:0);call('skill',L.P_DAGGER,level,6,0);call('skill',L.P_TWO_WEAPON_COMBAT,level,6,0);call('skill',L.P_BARE_HANDED_COMBAT,level,6,0);call('skill',L.P_RIDING,level,6,0);action(36,skill===L.P_BARE_HANDED_COMBAT?-1:0);action(37,skill===L.P_BARE_HANDED_COMBAT?-1:0);action(35);
}
// Record rollback and the original defined noreturn invariant diagnostics.
reset();call('skill',L.P_DAGGER,2,4,100);call('counts',0,1);call('record',0,L.P_DAGGER);action(32,1);assert.match(state(),/slots:0;advanced:0;/);
for(const op of [32,33]){reset();call('skill',L.P_DAGGER,1,4,100);call('counts',0,1);call('record',0,L.P_DAGGER);assert.equal(action(op,1),-999);assert.match(trace(),/panic:/);}
reset();action(39,-1);
reset();call('skill',L.P_DAGGER,1,4,100);call('counts',2,0);call('option',22,3);action(25,L.P_DAGGER);assert.match(trace(),/slot-change/);
// Actual native callbacks can reenter and grow while original buffers/menus/
// inventory references are live. Choose explicit reachable path per stage.
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13,14]){
 reset();item(L.DAGGER);call('inventory',0,0);monster(L.PM_HUMAN);call('option',20,stage);call('option',21,stage);const before=modules.map(m=>m.HEAPU8.buffer.byteLength);
 if(stage===1||stage===2||stage===7){field(0,3,1);call('option',7,1);action(12);}
 else if(stage===3)action(0,L.P_DAGGER);
 else if(stage===4){field(0,3,1);action(2);}
 else if(stage===5)action(8);
 else if(stage===6){monster(L.PM_HUMAN,0);call('option',10,1);action(11);}
 else if(stage===8){field(0,6,1);call('option',7,1);action(39,0);}
 else if(stage===9)action(38);
 else if(stage===10){item(L.TOWEL);action(17,0,3,1);}
 else {call('skill',L.P_DAGGER,1,4,100);call('counts',2,0);action(28);}
 assert.match(trace(),new RegExp('nested:'+L.P_BARE_HANDED_COMBAT+';'));assert.match(trace(),new RegExp('grow:'+stage+';'));modules.forEach((m,i)=>assert.ok(m.HEAPU8.buffer.byteLength>before[i]));
}
reset();item(L.AKLYS);action(7);const saved=snapshot(modules[1]),ptr=modules[1]._probe_pointer(4);const independent=await hf({nethackPorted:runtime});independent._probe_reset();independent._probe_item(0,L.AKLYS,L.NON_PM,L.OBJ_INVENT,0);independent._probe_action(7,0,0,0,0n);assert.deepEqual(snapshot(modules[1]),saved);assert.equal(modules[1]._probe_pointer(4),ptr);
console.log(`WEAPON: ${comparisons} Emscripten-C/pure-JS damage, selection, skill/table, menu, lifetime, callbacks and growth comparisons checked.`);
