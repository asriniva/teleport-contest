import {layoutSourceSha} from './nethack-layout.mjs';
// Connected original-C witnesses for shared RNG identity and selection memory.
import fs from 'node:fs';import path from 'node:path';import assert from 'node:assert/strict';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const directory=path.resolve(process.env.STANDALONE_LEVEL_STARTUP_ORACLE||'.cache/standalone-level-startup-v9');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const decl=JSON.parse(fs.readFileSync('js/nethack/decl-storage.json')).globals;
function setup(seed){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log',NETHACK_FIXED_DATETIME:'20260102030405'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/nethack/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);env.enableLuaSandbox(layouts);env.enableDisplayStartup(layouts);
env.enableLevelStartup(layouts);return env;
}
let comparisons=0;
for(const seed of [0n,1n,0xffffffffffffffffn]){
 const env=setup(seed),errors=[],ref=await factory({printErr:s=>errors.push(s)});ref._probe_level_init(seed);
 const state=env.state('rnd');
 const offsets=Array.from({length:7},(_,i)=>Number(ref._probe_level_rng_layout(i)));
 function compareRng(label){for(let which=0;which<2;which++){
  const c=Buffer.from(ref.HEAPU8.slice(Number(ref._probe_level_rng_state(which)),Number(ref._probe_level_rng_state(which))+offsets[0])),j=state.rnglist[which].rng_state;
  assert.equal(j.n,Number(c.readBigUInt64LE(offsets[1])),label+' n');
  for(const [key,index,count]of [['r',2,256],['m',3,256],['a',4,1],['b',5,1],['c',6,1]])for(let i=0;i<count;i++)assert.equal(count===1?j[key]:j[key][i],c.readBigUInt64LE(offsets[index]+8*i),label+' '+which+':'+key+':'+i);
  assert.equal(state.rnglist[which].init,ref._probe_level_rng_initialized(which));comparisons+=517;
 }}
 function setenv(name,value){const a=BigInt(ref._malloc(BigInt(name.length+1))),b=BigInt(ref._malloc(BigInt(value.length+1)));ref.HEAPU8.set(Buffer.from(name+'\0'),Number(a));ref.HEAPU8.set(Buffer.from(value+'\0'),Number(b));ref._setenv(a,b,1);ref._free(a);ref._free(b);env.setEnvironment(name,value);}
 compareRng('initial');setenv('NETHACK_SEED','123456789');
 for(const strong of [0,1,0]){
  env.services.has_strong_rngseed=strong;ref.HEAPU8[Number(ref._probe_decl_global(decl.findIndex(r=>r.name==='has_strong_rngseed')))]=strong;
  for(let which=0;which<2;which++){
   const name=which?'rn2_on_display_rng':'rn2',fn=env.functionPointer(name,'ii');assert.equal(fn,env.functionPointer(name,'ii'));
   env.services.reseed_random(Number(fn));ref._probe_level_reseed(which);compareRng('reseed '+strong+':'+which);
   for(const n of [1,2,3,17,256,2147483647]){assert.equal(env.resolve(name)(n),ref['_'+name](n));comparisons++;}compareRng('draw');
  }
 }
 assert.equal(env.services.sys_random_seed(),BigInt.asUintN(64,ref._sys_random_seed()));comparisons++;
 const L=layouts.selvar,sel=env.services.selection_new(),csel=BigInt(ref._selection_new());
 function compareSelection(label,p=sel,q=csel){
  const j=Buffer.from(env.memory.readBytes(p,L.selectionSize)),c=Buffer.from(ref.HEAPU8.slice(Number(q),Number(q)+L.selectionSize)),jp=Number(j.readBigUInt64LE(L.sel_map)),cp=Number(c.readBigUInt64LE(L.sel_map));
  for(const [field,size]of [['sel_wid',4],['sel_hei',4],['sel_bounds_dirty',1],['sel_bounds',L.rectSize]])assert.deepEqual(j.subarray(L[field],L[field]+size),c.subarray(L[field],L[field]+size),label+' '+field);assert.equal(Boolean(jp),Boolean(cp),label+' map presence');
  assert.deepEqual(Buffer.from(env.memory.readBytes(jp,L.COLNO*L.ROWNO+1)),Buffer.from(ref.HEAPU8.slice(cp,cp+L.COLNO*L.ROWNO+1)),label+' map');comparisons+=6;
 }
 function both(name,args){env.resolve(name)(sel,...args);ref['_'+name](csel,...args);compareSelection(name);compareRng(name);}
 compareSelection('new');both('selection_clear',[0]);
 for(const [x,y,v]of [[1,1,1],[20,10,2],[79,20,1],[-1,0,1],[80,21,1],[65537,65537,3]]){
  env.services.selection_setpoint(x,y,sel,v);ref._selection_setpoint(x<<16>>16,y<<16>>16,csel,v);assert.equal(env.services.selection_getpoint(x,y,sel),ref._selection_getpoint(x<<16>>16,y<<16>>16,csel));comparisons++;compareSelection('setpoint');
 }
 env.services.selection_do_line(2,3,40,17,sel);ref._selection_do_line(2,3,40,17,csel);compareSelection('line');
 env.services.selection_do_randline(4,4,60,18,4,3,sel);ref._selection_do_randline(4,4,60,18,4,3,csel);compareSelection('random line');compareRng('random line');
 both('selection_do_ellipse',[20,10,9,5,1]);both('selection_do_grow',[15]);
 const cloned=env.services.selection_clone(sel),ccloned=BigInt(ref._selection_clone(csel));compareSelection('clone',cloned,ccloned);
 const filtered=env.services.selection_filter_percent(sel,43),cfiltered=BigInt(ref._selection_filter_percent(csel,43));compareSelection('percent',filtered,cfiltered);compareRng('percent');
 for(const [p,q]of [[sel,csel],[cloned,ccloned],[filtered,cfiltered]]){env.services.selection_free(p,1);ref._selection_free(q,1);}
}
console.log('PASS: '+comparisons+' original-C shared RNG-state and selection comparisons; level closure and full-game recording remain pending.');
