import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
// Private actual configured original-C versus JS READ; foreign world controlled.
import assert from './native-test-assert.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callRead,createReadEnvironment} from '../js/nethack/bindings/read.js';
import * as core from '../js/ported/read.js';
import {C,R,T} from '../js/c-runtime/context.js';
// Reference selection is handled by the original-C fixture backend.
const directory=resolve(process.env.TELEPORT_READ_PROBE_DIR??'.cache/read-author');
const {default:rf}=await loadFixture("read",pathToFileURL(resolve(directory,'reference.mjs')));
const {default:hf}=await loadFixture("read",pathToFileURL(resolve(directory,'hybrid.mjs')));
const original=await rf(),layout={};
const text=(m,p)=>{let at=Number(p);if(!at)return null;let end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.subarray(at,end)).toString('latin1');};
for(let i=0;i<original._probe_layout_count();i++)layout[text(original,original._probe_layout_name(i))]=Number(original._probe_layout_value(i));
assert.ok(Number.isInteger(layout.NUM_OBJECTS)&&layout.NUM_OBJECTS>400,'actual configured object catalogue extent');
const entered=new Set();let lastServices;
const runtime={read:(services,name,...args)=>{lastServices=services;entered.add(name);return callRead(services,layout,name,...args);}};
const modules=[original,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());
let comparisons=0,context='initial';
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),buffer:text(m,m._probe_buffer())});
function check(){
 const actual=snapshot(modules[1]),expected=snapshot(modules[0]);
 if(JSON.stringify(actual)!==JSON.stringify(expected)){
  writeFileSync(resolve(directory,'failure-'+Date.now()+'.json'),JSON.stringify({context,actual,expected},null,2));
  for(const k of Object.keys(actual))if(actual[k]!==expected[k]){let i=0;while(actual[k][i]===expected[k][i])i++;console.error(context,k,'firstdiff',i,actual[k].slice(i,i+160),expected[k].slice(i,i+160));}
 }
 assert.deepEqual(actual,expected,context);
 for(let i=0;i<2;i++)assert.equal(modules[i]._probe_stack(),stacks[i],context+':stack');
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;
}
function call(name,...args){const results=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(results[1],results[0],context+':'+name);check();return results[0];}
const reset=()=>call('reset'),action=(op,a=0,b=0,c=0)=>call('action',op,a,b,c),option=(n,v)=>call('option',n,v),global=(n,v)=>call('global',n,BigInt(v));
const object=(typ,spe=0,flags=0,oid=1,quantity=1n,i=0)=>call('object',i,typ,spe,flags,oid,quantity);
const cases=JSON.parse(readFileSync(resolve(directory,'inventory.json'),'utf8')).functions;
for(let i=0;i<cases.length;i++){
 context='entry:'+cases[i].name;reset();
 if(cases[i].name==='set_lit')action(i,10,10,1);
 else if(cases[i].name==='valid_cloud_pos'||cases[i].name==='can_center_cloud')action(i,10,10);
 else action(i);
}
for(const oid of[0,1,2,7,31,2147483647,2147483648,4294967295])for(const birthday of[0n,1n,-1n,2147483648n,9007199254740993n])for(const name of['tshirt_text','hawaiian_motif','hawaiian_design','apron_text']){
 context='text:'+name+':'+oid+':'+birthday;reset();object(layout.T_SHIRT??1,0,0,oid);global(0,birthday);action(cases.findIndex(f=>f.name===name));
}
const entry=name=>cases.findIndex(f=>f.name===name);
for(const oid of[1,7,4294967295])for(const erosion of[1,3,12,15])for(const name of['tshirt_text','apron_text']){
 context='eroded:'+name+':'+oid+':'+erosion;reset();object(layout.T_SHIRT,0,erosion<<2,oid);action(entry(name));
}
for(const typ of[layout.WAN_WISHING,layout.WAN_FIRE,layout.WAN_NOTHING,layout.RIN_ADORNMENT,layout.MAGIC_MARKER,layout.BRASS_LANTERN,layout.OIL_LAMP,layout.CRYSTAL_BALL,layout.MAGIC_FLUTE,layout.BAG_OF_TRICKS,layout.DAGGER])for(const blessing of[-1,0,1])for(const seed of[1,2,7,42]){
 context='recharge:'+typ+':'+blessing+':'+seed;reset();object(typ,0,64);call('seed',seed);action(entry('charge_ok'));action(entry('recharge'),blessing);
}
for(const typ of[layout.SCR_ENCHANT_ARMOR,layout.SCR_DESTROY_ARMOR,layout.SCR_CONFUSE_MONSTER,layout.SCR_SCARE_MONSTER,layout.SCR_REMOVE_CURSE,layout.SCR_CREATE_MONSTER,layout.SCR_ENCHANT_WEAPON,layout.SCR_TAMING,layout.SCR_GENOCIDE,layout.SCR_LIGHT,layout.SCR_CHARGING,layout.SCR_AMNESIA,layout.SCR_FIRE,layout.SCR_EARTH,layout.SCR_PUNISHMENT,layout.SCR_STINKING_CLOUD,layout.SCR_BLANK_PAPER,layout.SCR_TELEPORTATION,layout.SCR_GOLD_DETECTION,layout.SCR_FOOD_DETECTION,layout.SCR_IDENTIFY,layout.SCR_MAGIC_MAPPING,layout.SCR_MAIL])for(const blessing of[0,1,2])for(const confused of[0,1]){
 context='scroll:'+typ+':'+blessing+':'+confused;reset();object(typ,0,blessing|64);global(3,confused);action(entry('seffects'));
}
for(const typ of[layout.T_SHIRT,layout.HAWAIIAN_SHIRT,layout.ALCHEMY_SMOCK,layout.CANDY_BAR,layout.CREDIT_CARD,layout.MAGIC_MARKER,layout.CAN_OF_GREASE,layout.FORTUNE_COOKIE,layout.DUNCE_CAP,layout.SCR_BLANK_PAPER,layout.SCR_MAIL])for(const verbose of[0,1])for(const blind of[0,1])for(const oid of[1,2,7,2147483647,4294967295]){
 if(typ===layout.CREDIT_CARD&&Math.abs(Number(BigInt.asIntN(32,BigInt(oid))))>Math.trunc(2147483647/7))continue; // original signed-int product would overflow
 context='read:'+typ+':'+verbose+':'+blind+':'+oid;reset();object(typ,1,64,oid);global(1,verbose);global(4,blind);action(entry('doread'));
}
function input(value){
 for(const m of modules){const bytes=Buffer.from(value+'\0','latin1'),p=m._malloc(BigInt(bytes.length));m.HEAPU8.set(bytes,Number(p));m._probe_input(BigInt(p));m._free(p);}
 check();
}
for(const value of['human','2 female human','3 tame saddled sleeping invisible hidden orc','male human','peaceful human','hostile human','*','random','0 human','99999 human'])for(const unmatched of[0,1]){
 context='parse:'+value+':'+unmatched;reset();global(2,1);option(4,unmatched);option(6,unmatched);input(value);action(entry('create_particular_parse'));
}
for(const missing of[0,1])for(const name of['doread','seffect_enchant_armor','seffect_destroy_armor','seffect_create_monster','seffect_light','seffect_charging']){
 context='record-return:'+name+':'+missing;reset();option(0,missing);option(1,missing);option(2,missing);object(layout.SCR_ENCHANT_ARMOR,0,1|64);action(entry(name));
}
for(const value of['2 female human','3 tame hidden orc','*'])for(const mode of[0,1])for(const missing of[0,1]){
 context='create-return:'+value+':'+mode+':'+missing;reset();global(2,1);option(4,mode);option(6,mode);option(7,missing);option(2,missing);input(value);action(entry('create_particular_parse'));action(entry('create_particular_creation'));
}
for(const missing of[0,1]){
 context='which-armor-return:'+missing;reset();call('scenario',1,1,0);call('scenario',0,1,0);option(1,missing);object(layout.SCR_REMOVE_CURSE,0,1);action(entry('seffect_remove_curse'));
}
for(const typed of[layout.LEATHER_ARMOR,layout.RED_DRAGON_SCALES,layout.ELVEN_MITHRIL_COAT,layout.HELM_OF_OPPOSITE_ALIGNMENT])for(const spe of[-128,-99,-1,0,3,7,99,127])for(const flags of[0,1,2]){
 context='armor:'+typed+':'+spe+':'+flags;reset();object(layout.SCR_ENCHANT_ARMOR,0,flags);object(typed,spe,0,3,1n,2);call('scenario',6,1,0);action(entry('seffect_enchant_armor'));
}
for(const response of[0,1])for(const name of cases.map(f=>f.name).filter(n=>n.startsWith('seffect_'))){
 context='foreign-response:'+name+':'+response;reset();option(3,response);object(layout.SCR_ENCHANT_ARMOR,0,1|64);action(entry(name));
}
context='foreign-native-callback:any_worn_armor_ok';reset();option(3,2);object(layout.SCR_DESTROY_ARMOR,0,1|64);action(entry('seffect_destroy_armor'));
for(let typ=1;typ<layout.NUM_OBJECTS;typ++){
 context='object-class:'+typ;reset();object(typ,0,64);action(entry('read_ok'));action(entry('charge_ok'));
}
for(const typ of[layout.WAN_WISHING,layout.WAN_FIRE,layout.WAN_NOTHING])for(const recharged of[0,1,3,6,7])for(const spe of[-128,-1,0,3,15,99,127])for(const seed of[1,7]){
 context='wand-width:'+typ+':'+recharged+':'+spe+':'+seed;reset();object(typ,spe,0);global(8,recharged);call('seed',seed);action(entry('recharge'),1);
}
for(let species=0;species<layout.NUMMONS;species++)for(const revive of[0,1]){
 context='revival:'+species+':'+revive;reset();action(entry('cant_revive'),species,revive);
}
for(const on of[0,1])for(const blessed of[0,1]){
 context='lit-gremlin:'+on+':'+blessed;reset();object(layout.SCR_LIGHT,0,blessed);call('scenario',2,layout.PM_GREMLIN,0);action(entry('litroom'),on);
}
for(const alias of[0,1]){
 context='native-growth-reentry:'+alias;reset();object(layout.T_SHIRT,0,0,7);option(90,1);option(91,1);option(92,1);option(94,alias);action(entry('doread'));action(entry('cap_spe'));
}
context='controlled-C-unwind';reset();object(layout.SCR_LIGHT);option(93,1);assert.equal(action(entry('p_glow1')),-999n);option(93,0);action(entry('cap_spe'));
// Binding-only C/JS projection matrix. mkobj/mksobj are declared NONNULL;
// their NULL rows are not legal C return cases and are deliberately absent.
const projectionNames=['getobj','makemon','mkclass','mkobj','mksobj','rndmonst','some_armor','which_armor'];
for(let kind=0;kind<projectionNames.length;kind++)for(const missing of[0,1]){
 if(missing&&(kind===3||kind===4))continue;
 context='typed-projection:'+projectionNames[kind]+':'+missing;reset();action(entry('cap_spe'));option(0,missing);option(1,missing);option(2,missing);option(7,missing);option(8,missing);
 const expected=original._probe_projection(kind),env=createReadEnvironment(lastServices,layout),saved=lastServices.stackSave();let value;
 try{
  if(kind===0)value=env.getobj('read',core.read_ok,layout.GETOBJ_PROMPT);
  if(kind===1)value=env.makemon(env.mons[layout.PM_HUMAN],10,10,layout.MM_NOGRP);
  if(kind===2)value=env.mkclass(layout.S_ORC,0);
  if(kind===3)value=env.mkobj(layout.WEAPON_CLASS,0);
  if(kind===4)value=env.mksobj(layout.DAGGER,1,0);
  if(kind===5)value=env.rndmonst();
  if(kind===6)value=env.some_armor(env.gy.youmonst);
  if(kind===7)value=env.which_armor(env.record('struct monst',modules[1]._probe_pointer(0)),layout.W_ARMH);
  if(value){assert.equal(typeof value.address,'number',context+':typed view');assert.equal(env.record(value.nativeType,value.address),value,context+':alias identity');}
 }finally{lastServices.stackRestore(saved);}
 const field=value?(kind===1?value.mhp:kind===2||kind===5?value.pmidx:value.otyp):-777;
 assert.equal(BigInt(field),expected,context);check();
 if(value){
  assert.equal(BigInt(value.address),modules[1]._probe_projected_pointer(kind),context+':actual native pointer alias');
  if(kind!==2&&kind!==5){call('projection_write',kind,17);assert.equal(kind===1?value.mhp:value.spe,17,context+':C write reread through live JS view');}
 }
}
assert.deepEqual([...entered].sort(),Object.entries(core).filter(([,v])=>typeof v==='function').map(([name])=>name).sort(),'all62configuredentrypoints reached');
writeFileSync(resolve(directory,'summary.json'),JSON.stringify({status:'PASS',comparisons,entered:[...entered].sort(),reference:'actual configured memory64 original C',typedReturnMatrix:projectionNames.map(name=>({name,positiveAlias:true,nullNativeCase:!['mkobj','mksobj'].includes(name),nonnullAttribute:['mkobj','mksobj'].includes(name)})),bindingProjectionCases:14,scope:'controlled private fixture; incomplete branch/native-host/shared/public coverage; mkobj/mksobj NULL forbidden by original NONNULL contract'},null,2));
console.log(`READ PASS ${comparisons} original C/pure-JS comparisons; ${entered.size} entrypoints reached.`);
