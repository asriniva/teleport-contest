// Staged configured EmC first-pass gate. Native and production promotion remain
// pending; this suite cannot silently count as a native-C pass.
import assert from 'node:assert/strict';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import * as vault from '../js/ported/vault.js';
import { createVaultEnvironment } from '../js/nethack/bindings/vault.js';
import { withCEnvironment,C } from '../js/c-runtime/context.js';
if(process.env.TELEPORT_NATIVE_TESTS==='1')throw new Error('VAULT native oracle pending; this staged suite compares configured Emscripten C only.');
const dir=resolve(process.env.TELEPORT_VAULT_PROBE_DIR??'.cache/tu-probes');
const refFactory=(await import(pathToFileURL(resolve(dir,'vault-reference.mjs')))).default;
const hybridFactory=(await import(pathToFileURL(resolve(dir,'vault-hybrid.mjs')))).default;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(p,e)).toString('latin1');};
const layout=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
const reference=await refFactory(),L=layout(reference),envs=new WeakMap();
const getEnv=s=>{let e=envs.get(s.moduleKey);if(!e){e=createVaultEnvironment(s,L);envs.set(s.moduleKey,e);}return e;};
const runtime={vault(services,name,...args){const e=getEnv(services);if(['newegd','free_egd','clear_fcorr','restfakecorr','parkguard','grddead','in_fcorridor','uleftvault','find_guard_dest','wallify_vault','gd_mv_monaway','gd_pick_corridor_gold','gd_move_cleanup','gd_letknow','gd_move'].includes(name))args[0]=e.monster(args[0]);if(name==='move_gold')args[0]=e.object(args[0]);if(name==='vault_occupied')args[0]=e.address(args[0]);if(name==='find_guard_dest'){args[1]=e.coordPointer(args[1]);args[2]=e.coordPointer(args[2]);}const r=withCEnvironment(e,vault[name],...args);return r?.address??r??0;}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());assert.deepEqual(layout(hybrid),L);let comparisons=1,scenario='initial';
const snap=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
function check(){assert.deepEqual(snap(hybrid),snap(reference),scenario);assert.equal(C,undefined);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));comparisons++;}
function call(name,...args){if(name==='option'||name==='prop')args[1]=BigInt(args[1]);if(['set_monster','object'].includes(name))args[2]=BigInt(args[2]);const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],scenario+':'+name+':'+args);comparisons++;check();return result[0];}
const reset=(s=1)=>call('reset',s),opt=(k,v)=>call('option',k,v),mon=(i,k,v)=>call('set_monster',i,k,v),egd=(i,k,v)=>call('egd',i,k,v),cell=(x,y,k,v)=>call('cell',x,y,k,v),obj=(i,k,v)=>call('object',i,k,v),act=(op,id=0,a=0,b=0,c=0)=>call('action',op,id,a,b,c);
const trace=()=>text(reference,reference._probe_trace());
function answer(value){modules.forEach(m=>m.HEAPU8.set(Buffer.from(value+'\0'),Number(m._probe_answer())));check();}
function rolls(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function guard(id=0,placed=true){mon(id,0,1);mon(id,8,1);if(placed)mon(id,10,1);}
function corridor(id=0,count=2){egd(id,0,0);egd(id,1,count);for(let i=0;i<count;i++){call('corridor',id,i,8+i,8,L.STONE,0xff);cell(8+i,8,0,L.CORR);}}
// Allocation/free retains mextra ownership, parent ID and idempotence.
scenario='extension lifecycle';reset();act(0,3);act(0,3);act(1,3);act(1,3);act(0,3);assert.ok(trace().includes('alloc:'));
// Complete restoration snapshots include terrain flags, visibility, traps and
// every fakecorr record, retaining the original refusal/force/message behavior.
for(const force of[0,1])for(const dead of[0,1])for(const visible of[0,1,3])for(const silence of[0,1]){scenario='clear corridor';reset();guard();corridor();opt(104,silence);mon(0,3,dead?0:50);cell(8,8,4,visible);cell(9,8,4,visible);call('trap',0,8,8);act(2,0,force);}
for(const tame of[0,1])for(const blocked of[0,1]){scenario='corridor occupant';reset();guard();corridor();mon(1,4,8);mon(1,5,8);mon(1,6,tame);mon(1,10,1);opt(5,blocked);act(2,0,1);}
scenario='guard blocks corridor';reset();guard();corridor();mon(0,4,8);mon(0,5,8);mon(0,10,1);act(2,0,1);
for(const x of[1,9,78])for(const y of[0,10,20]){scenario='blackout bounds';reset();act(3,0,x,y);}
for(const done of[0,1]){scenario='restore and park';reset();guard();corridor();egd(0,2,done);opt(114,0);act(5,0);act(4,0);}
for(const blocked of[0,1]){scenario='dead guard cleanup';reset();guard();corridor();if(blocked){mon(1,0,1);mon(1,4,8);mon(1,5,8);mon(1,10,1);}act(6,0);}
scenario='membership';reset();corridor();for(const [x,y]of[[8,8],[9,8],[10,8],[0,0]])act(7,0,x,y);
for(const migrating of[0,1])for(const parked of[0,1])for(const done of[0,1]){scenario='find guard list transfer';reset();mon(0,0,1);mon(0,4,parked?0:9);egd(0,2,done);mon(0,3,0);mon(0,migrating?9:8,1);act(8);}
for(const vault of[0,1]){scenario='occupancy summon and sound';reset();opt(102,vault);act(10);act(9);act(23);guard();act(9);act(23);}
for(const coins of[0,1])for(const distant of[0,1]){scenario='teleport out of vault';reset();guard();corridor();opt(102,0);if(coins){obj(0,8,0);obj(0,1,12);}opt(100,distant?25:10);act(11,0);}
// The radius jump must abandon the rest of an unsuitable ring and continue
// outward; an all-stone map produces the original diagnostic/teleport path.
for(const badAdjacent of[0,1])for(const candidate of[0,1]){scenario='guard destination';reset();if(badAdjacent)cell(14,10,0,L.ROOM);if(!candidate)cell(15,10,0,L.STONE);act(12,-1);}
for(const age of[0,28,29,30,44])for(const deaths of[0,1,2,49,50]){scenario='summon cadence';reset(5);opt(103,age);opt(111,deaths);rolls([0]);act(13);}
// Guard arrival dialogue: real C makemon callback calls JS newegd on demand;
// map breach, naming, deception, hidden gold, deafness and mimic exits retain
// their source ordering and exact printf argument types.
for(const name of['Player','Croesus','Kroisos','Creosote','stranger',''])for(const deaf of[0,1]){scenario='arrival dialogue';reset();opt(103,29);answer(name);if(deaf)call('prop',L.DEAF,1);act(13);}
for(const mode of[0,1,2,3,4,5,6]){scenario='arrival inability';reset();opt(103,29);if(mode===0)opt(105,1);if(mode===1)opt(106,1);if(mode===2){opt(107,L.M_AP_OBJECT);opt(108,L.ROCK);}if(mode===3)call('prop',L.STRANGLED,1);if(mode===4)opt(109,L.MS_SILENT);if(mode===5)opt(110,-1);if(mode===6)opt(6,1);act(13);}
for(const known of[0,1])for(const hidden of[0,1]){scenario='arrival gold';reset();opt(103,29);obj(0,8,0);obj(0,0,hidden?L.LARGE_BOX:L.GOLD_PIECE);obj(0,1,123);if(hidden){obj(0,7,1);obj(0,5,known);obj(1,1,17);}act(13);}
scenario='move gold';reset(11);act(25,0,0,9,9);act(14,0,0,0);
for(const rock of[L.ROCK,L.BOULDER,L.GOLD_PIECE])for(const visibility of[0,L.IN_SIGHT]){scenario='wall repair';reset();guard();obj(0,0,rock);act(25,0,0,9,9);call('trap',0,9,9);cell(9,9,0,L.CORR);cell(9,9,4,visibility);act(15,0);}
for(const fail of[0,1]){scenario='move blocking monster';reset();guard();mon(1,4,14);mon(1,5,10);mon(1,10,1);opt(5,fail);act(16,0,14,10);}
for(const target of[[10,10],[9,10],[14,10]])for(const shown of[0,1]){scenario='corridor gold pickup';reset();guard();const [x,y]=target;act(25,0,0,x,y);cell(x,y,4,shown?L.IN_SIGHT:0);act(17,0,x,y);}
for(const semidead of[0,1])for(const seen of[0,1]){scenario='move cleanup';reset();guard();corridor();act(18,0,semidead,seen);}
for(const visible of[0,1])for(const carryingWhistle of[0,1]){scenario='notice hostile guard';reset();guard();cell(9,10,4,visible?L.IN_SIGHT:0);if(carryingWhistle){obj(0,0,L.TIN_WHISTLE);mon(0,6,0);}act(19,0);}
for(const warning of[0,3,6,7])for(const gold of[0,1])for(const distant of[0,1]){scenario='guard movement warnings';reset(9);guard();egd(0,1,1);call('corridor',0,0,9,10,L.VWALL,0);egd(0,4,warning);if(gold)obj(0,8,0);if(distant)opt(100,11);act(20,0);}
for(const hostile of[0,1])for(const inVault of[0,1])for(const count of[0,1,2,3]){scenario='guard carve and cleanup';reset(11);guard();corridor(0,count);mon(0,1,hostile?0:1);opt(102,inVault);act(20,0);}
for(const witness of[1,2]){scenario='guard witness';reset();guard();egd(0,3,witness);act(20,0);}
for(const peaceful of[0,1])for(const inVault of[0,1])for(const silent of[0,1]){scenario='pay gold and remove guard';reset(93);guard();mon(0,1,peaceful);opt(103,inVault);obj(0,8,0);obj(0,1,(1n<<53n)+3n);act(21,0,silent);}
for(const known of[0,1])for(const evenUnknown of[0,1])for(const quantity of[1n,(1n<<53n)+7n,9223372036854775807n]){scenario='hidden gold';reset();obj(0,0,L.LARGE_BOX);obj(0,5,known);obj(0,7,1);obj(0,8,0);obj(1,1,quantity);act(22,0,evenUnknown);}
for(const activity of[0,1,2,3,0xffffffff])for(const seeing of[0,1]){scenario='watching';reset();guard();mon(0,2,seeing);act(24,0,activity);}
scenario='growth and nested scopes';reset();guard();corridor();cell(9,9,0,L.CORR);opt(30,1);opt(31,1);const oldBuffers=modules.map(m=>m.HEAPU8.buffer);act(15,0);assert.ok(trace().includes('growth;'));assert.ok(trace().includes('reentry:'));modules.forEach((m,i)=>assert.notEqual(m.HEAPU8.buffer,oldBuffers[i]));
// These conversions are source-defined widths: m_id -> unsigned parentmid,
// signed coordxy destinations, signed terrain -> unsigned local typ, and
// uchar corridor flags -> the terrain's five-bit flag field.
for(const id of[0x7fffffff,0x80000000,0xffffffff]){scenario='unsigned parent ID';reset();mon(3,11,id);act(0,3);act(1,3);act(0,3);assert.ok(snap(reference).state.includes('e:'+id+':'));}
for(const goal of[32767,32768,65535]){scenario='signed destination coordinate';reset();guard();egd(0,9,goal);egd(0,10,10);act(20,0);}
for(const terrain of[0x7f,0x80,0xff]){scenario='signed terrain to uchar local';reset();opt(102,0);opt(100,8);mon(0,4,8);egd(0,7,8);guard();cell(7,10,0,terrain);act(20,0);}
scenario='destination ring abandonment';reset();cell(5,10,0,L.CORR);cell(6,10,0,L.ROOM);act(12,-1);assert.ok(trace().includes('tele;'));
scenario='movement forward proceed jump';reset();opt(102,0);opt(100,8);mon(0,4,8);egd(0,7,8);guard();cell(7,10,0,L.SCORR);act(20,0);
scenario='movement destination retry jump';reset();guard();egd(0,9,9);egd(0,10,10);act(20,0);
// A second module must use its own typed environment and keep both retained
// aliases and globals independent of mutations in the first module.
scenario='module isolation';const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(77);other._probe_action(0,3,0,0,0);const otherState=snap(other);reset();guard();corridor();act(2,0,1);assert.deepEqual(snap(other),otherState);assert.equal(C,undefined);comparisons++;
// Throwing through a real C -> JS dependency must unwind both environment and
// binding stack scope even after stateful work. A thrown JS exception bypasses
// the outer C fixture return: inspect the binding-entry stack, then explicitly
// release that test-owned C frame; this is not foreign-C exception unwinding.
scenario='dependency throw cleanup';reset();guard();cell(9,9,0,L.CORR);
let throwingEnv,throwServices,bindingStack;const throwingRuntime={vault(services,name,...args){throwServices=services;bindingStack=services.stackSave();throwingEnv=getEnv(services);const saved=throwingEnv.newsym;throwingEnv.newsym=()=>{throw new Error('fixture dependency throw');};try{return runtime.vault(services,name,...args);}finally{throwingEnv.newsym=saved;}}};
const throwing=await hybridFactory({nethackPorted:throwingRuntime});throwing._probe_reset(9);throwing._probe_cell(9,9,0,L.CORR);const throwStack=throwing._probe_stack();assert.throws(()=>throwing._probe_action(15,0,0,0,0),/fixture dependency throw/);assert.equal(C,undefined);assert.equal(throwing._probe_stack(),BigInt(bindingStack));throwServices.stackRestore(Number(throwStack));assert.equal(throwing._probe_stack(),throwStack);comparisons++;
console.log(`VAULT: ${comparisons} configured Emscripten-C/JS comparisons passed; native and production promotion pending.`);
