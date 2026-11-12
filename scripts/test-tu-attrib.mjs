// Configured Emscripten-C first-pass gate. Native oracle and production/public
// mixed-link promotion are pending; no host-specific pass allowances exist.
import assert from 'node:assert/strict';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import * as attrib from '../js/ported/attrib.js';
import { createAttribEnvironment } from '../js/nethack/bindings/attrib.js';
import { withCEnvironment,C } from '../js/c-runtime/context.js';
if(process.env.TELEPORT_NATIVE_TESTS==='1')throw new Error('ATTRIB native oracle is pending; this staged gate compares configured Emscripten C only.');
const dir=resolve(process.env.TELEPORT_ATTRIB_PROBE_DIR??'.cache/tu-probes');
const refFactory=(await import(pathToFileURL(resolve(dir,'attrib-reference.mjs')))).default;
const hybridFactory=(await import(pathToFileURL(resolve(dir,'attrib-hybrid.mjs')))).default;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(p,e)).toString('latin1');};
const layout=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
const reference=await refFactory(),L=layout(reference),envs=new WeakMap();
const getEnv=s=>{let e=envs.get(s.moduleKey);if(!e){e=createAttribEnvironment(s,L,attrib);envs.set(s.moduleKey,e);}return e;};
const runtime={initializeAttrib:getEnv,attrib(services,name,...args){const e=getEnv(services);if(name==='gainstr')args[0]=e.object(args[0]);if(['postadjabil','check_innate_abil','innately'].includes(name))args[0]=e.longPointer(args[0]);const r=withCEnvironment(e,attrib[name],...args);return r?.address??r??0;}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());
assert.deepEqual(layout(hybrid),L);let comparisons=1,scenario='startup';
// Public C data must exist before the first original ATTRIB call or probe reset.
for(let i=0;i<6;i++){assert.equal(text(hybrid,hybrid._probe_attrname(i)),text(reference,reference._probe_attrname(i)));comparisons++;}
const snap=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),result:text(m,m._probe_result())});
function check(){assert.deepEqual(snap(hybrid),snap(reference),scenario);assert.equal(C,undefined);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));comparisons++;}
function call(name,...args){if(name==='option')args[1]=BigInt(args[1]);if(['prop','object'].includes(name))args[2]=BigInt(args[2]);const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],scenario+':'+name+':'+args);comparisons++;check();return result[0];}
const reset=(s=1)=>call('reset',s),opt=(k,v)=>call('option',k,v),attr=(a,i,v)=>call('attr',a,i,v),prop=(p,k,v)=>call('prop',p,k,v),obj=(id,k,v)=>call('object',id,k,v),act=(op,a=0,b=0,c=0)=>Number(call('action',op,a,b,c));
const trace=()=>text(reference,reference._probe_trace());
function input(i,s){modules.forEach(m=>m.HEAPU8.set(Buffer.from(s+'\0'),Number(m._probe_input(i))));check();}
function rolls(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
// Every original role table row, including the terminator and all string/long*
// fields, must match the compiler's static C initialization.
const roles=['PM_ARCHEOLOGIST','PM_BARBARIAN','PM_CAVE_DWELLER','PM_HEALER','PM_KNIGHT','PM_MONK','PM_CLERIC','PM_RANGER','PM_ROGUE','PM_SAMURAI','PM_TOURIST','PM_VALKYRIE','PM_WIZARD'];
const tables=['arc_abil','bar_abil','cav_abil','hea_abil','kni_abil','mon_abil','pri_abil','ran_abil','rog_abil','sam_abil','tou_abil','val_abil','wiz_abil'];
reset();for(let i=0;i<roles.length;i++)for(let row=0;row<attrib[tables[i]].length;row++){assert.equal(text(hybrid,hybrid._probe_innate(L[roles[i]],row)),text(reference,reference._probe_innate(L[roles[i]],row)));comparisons++;}
for(let index=0;index<6;index++)for(const base of[-128,2,3,6,10,18,25,118,125,127])for(const bonus of[-2,0,3]){scenario='current attributes';reset();attr(0,index,base);attr(2,index,bonus);act(29,index);act(30);act(31,index);}
for(let index=0;index<6;index++)for(const incr of[-50,-2,-1,0,1,2,20,127])for(const msg of[-1,0,1]){scenario='attribute adjustment';reset(73);attr(0,index,3);act(0,index,incr,msg);}
for(const equip of[0,1])for(const index of[0,1,2,4]){scenario='equipment overrides';reset();obj(0,0,equip?L.DUNCE_CAP:L.GAUNTLETS_OF_POWER);call('equip',equip?0:1,0);act(29,index);act(31,index);act(0,index,1,0);act(4,index,1);}
for(const base of[3,10,17,18,50,103,125])for(const cursed of[0,1]){scenario='strength gain';reset(7);attr(0,0,base);obj(0,2,cursed);act(1,0,0,1);}
for(const poly of[0,1])for(const base of[3,4,10])for(const loss of[1,3,9]){scenario='strength loss';reset(11);opt(105,poly);attr(0,0,base);act(2,loss,L.KILLED_BY);act(3,1,2,L.KILLED_BY);}
for(let index=0;index<6;index++)for(const exclaim of[0,1]){scenario='poison feedback';reset();act(4,index,exclaim);}
for(const reason of['sting','Orcus\'s sting','arrows','blast','gas cloud','poison dart'])for(const fatal of[0,1,6,10])for(const thrown of[0,1]){scenario='poisoning';reset(39);input(0,reason);act(5,L.A_CON,fatal,thrown);}
for(const luck of[-128,-14,-13,-1,0,1,13,14,127])for(const delta of[-128,-3,0,3,127]){scenario='luck width and clamping';reset();opt(108,luck);act(6,delta);}
for(const quantity of[1n,2n,4294967295n,(1n<<53n)+7n])for(const blessed of[0,1])for(const cursed of[0,1]){scenario='luckstone quantities';reset();obj(0,0,L.LUCKSTONE);obj(0,1,quantity);obj(0,2,cursed);obj(0,3,blessed);obj(0,8,0);act(7,0);act(7,1);act(8);}
for(let i=0;i<6;i++)for(const exercised of[-50,-3,-1,0,1,3,49,50])for(const inc of[0,1]){scenario='exercise';reset(5);attr(3,i,exercised);act(10,i,inc);}
for(const hunger of[-10,0,1,51,151,1001])for(const moves of[0,5,10,11,600])for(const capacity of[0,2,3,4]){scenario='periodic exercise';reset(3);opt(109,hunger);opt(111,moves);opt(3,capacity);act(11);}
for(const exercised of[-49,-3,1,25,49])for(const poly of[0,1])for(const multi of[0,1]){scenario='exercise check common tail';reset(17);opt(111,1000);opt(112,900);opt(113,multi);opt(105,poly);for(let i=0;i<6;i++)attr(3,i,exercised);act(12);}
for(const temporary of[-3,-1,1,3])for(const time of[0,1,2]){scenario='temporary recovery';reset();attr(4,0,temporary);attr(5,0,time);act(9);}
for(const points of[0,30,60,75,200]){scenario='initial distribution';reset(31);act(13);act(14,points-60,points>=60);act(15,points);act(16);act(17);}
// All innate reasons and role/race gain/loss thresholds retain exact long masks.
for(const role of roles)for(const race of['PM_HUMAN','PM_ELF','PM_ORC','PM_DWARF','PM_GNOME']){scenario='role/race abilities';reset();opt(106,L[role]);opt(107,L[race]);act(19,L[role]);for(const [oldlevel,newlevel]of[[0,1],[1,7],[7,20],[20,5]]){opt(100,newlevel);act(24,oldlevel,newlevel);}for(const p of[L.FAST,L.WARNING,L.SEARCHING,L.POISON_RES,L.INFRAVISION,L.SLEEP_RES,L.FIRE_RES,L.COLD_RES,L.SHOCK_RES,L.SEE_INVIS,L.TELEPORT_CONTROL]){act(18,p);act(20,p,0);act(20,p,1);act(21,p);act(22,p);}}
for(const mask of[0n,BigInt(L.FROMOUTSIDE),BigInt(L.FROMFORM),BigInt(L.FROMEXPER),BigInt(L.FROMRACE),(1n<<60n)|BigInt(L.FROMOUTSIDE)]){scenario='wide intrinsic masks';reset();prop(L.FIRE_RES,0,mask);act(21,L.FIRE_RES);act(22,L.FIRE_RES);opt(116,1);act(23,L.FIRE_RES);}
for(const level of[0,1,5,10,29,30,31])for(const con of[3,6,14,16,17,18,25]){scenario='HP progression';reset(91);opt(100,level);attr(0,L.A_CON,con);call('advance',0,1,4);call('advance',0,3,5);call('advance',1,5,6);act(25);act(26,-1);act(26,10);}
for(const poly of[0,1])for(const even of[0,1])for(const maximum of[1,20,150]){scenario='HP max and pending loss';reset();opt(105,poly);act(27,maximum,even);act(28,20,100);}
for(const old of[-100,0,100])for(const change of[-200,-7,0,7,200]){scenario='alignment';reset();opt(111,1000);opt(125,old);act(32,change);}
for(const old of[-1,0,1])for(const next of[-1,0,1])for(const reason of[L.A_CG_CONVERT,L.A_CG_HELM_ON,L.A_CG_HELM_OFF]){scenario='alignment change';reset(13);opt(124,old);act(33,next,reason);}

// Every from_what branch uses the original stable static buffer and overlapping
// string compaction, with source provenance priority unchanged.
for(const property of[L.BLINDED,L.DEAF,L.FAST,L.FIRE_RES,L.STRANGLED,L.INVIS,L.CLAIRVOYANT])for(const kind of[0,1,2,3,4,5]){scenario='property provenance';reset();opt(116,1);obj(0,0,L.DUNCE_CAP);obj(0,4,1);obj(0,9,1);call('equip',0,0);call('equip',2,0);call('equip',3,0);call('equip',4,0);if(kind===1)prop(property,0,L.FROMOUTSIDE);if(kind===2)prop(property,0,L.FROMFORM);if(kind===3){opt(4,1);opt(5,1);}if(kind===4){prop(property,1,property===L.FAST?L.W_ARMF:1);opt(4,1);}if(kind===5){prop(property,2,property===L.CLAIRVOYANT?L.W_ARMH:L.W_ARMC);obj(0,5,L.ART_EYES_OF_THE_OVERWORLD);}act(23,property);act(23,-property);}
scenario='blind from birth';reset();opt(116,1);opt(122,1);act(23,L.BLINDED);
scenario='blind goop';reset();opt(116,1);prop(L.BLINDED,0,5);opt(121,5);act(23,L.BLINDED);
for(const property of[L.DRAIN_RES,L.JUMPING,L.BLND_RES,L.BLINDED,L.FAST]){scenario='innate special cases';reset();opt(106,L.PM_KNIGHT);opt(117,L.PM_HUMAN);opt(119,L.M1_NOEYES);prop(property,0,L.FROMFORM);act(22,property);act(23,property);}
for(const reason of['blast','gas cloud','sting'])for(const resistant of[0,1]){scenario='poison resistance and towel';reset();obj(0,0,L.TOWEL);obj(0,6,1);call('equip',4,0);prop(L.POISON_RES,0,resistant);input(0,reason);rolls([8,3,1]);act(5,L.A_DEX,20,0);}
for(const initial of[-2147483648,-2147483647,2147483646,2147483647])for(const change of[-9,9]){scenario='alignment width limits';reset();opt(125,initial);opt(126,4294967290n);act(32,change);}
scenario='debug macros preserve message category';reset();opt(0,1);opt(134,55);opt(111,1000);opt(112,800);attr(3,L.A_WIS,10);act(10,L.A_STR,1);act(11);act(12);
scenario='heap growth and nested ATTRIB';reset();opt(16,1);opt(17,1);act(0,L.A_CON,1,0);assert.ok(trace().includes('growth;'));assert.ok(trace().includes('reentry:'));



for(const hungerState of[0x7fffffff,0x80000000,0xffffffff]){scenario='unsigned hunger field';reset();opt(110,hungerState);attr(4,L.A_STR,-1);attr(5,L.A_STR,1);act(9);}
// An ABI dependency exception must unwind both the synchronous C environment
// and the binding's Wasm stack scope; exercise state may already be mutated.

for(const maximum of[-60000,0,300,1199,1200,38400]){scenario='signed char HP limiter';reset();opt(100,30);opt(102,maximum);call('advance',0,4,100);act(25);}
for(const role of[-1,0,1,32767]){scenario='unknown role';reset();act(19,role);opt(106,role);act(24,0,20);}
scenario='dependency exception cleanup';reset();const env=envs.get(hybrid),savedFeel=env.You_feel;env.You_feel=()=>{throw new Error('controlled ATTRIB dependency failure');};assert.throws(()=>hybrid._probe_action(0,L.A_CON,1,0),/controlled ATTRIB dependency failure/);assert.equal(C,undefined);assert.equal(hybrid._probe_stack(),stacks[1]);env.You_feel=savedFeel;comparisons++;reset();
// One runtime may serve multiple modules; their table/property/string addresses
// and static from_what buffers must remain independent, including after growth.
const other=await hybridFactory({nethackPorted:runtime});for(let i=0;i<6;i++){assert.equal(text(other,other._probe_attrname(i)),attrib.attrname[i]);comparisons++;}
other._probe_reset(17);other._probe_option(116,1n);other._probe_prop(L.FIRE_RES,0,BigInt(L.FROMOUTSIDE));other._probe_action(23,L.FIRE_RES,0,0);const otherState=snap(other);reset(31);act(0,L.A_INT,1,0);assert.deepEqual(snap(other),otherState);assert.equal(C,undefined);comparisons++;

console.log(`ATTRIB: ${comparisons} configured Emscripten-C/JS comparisons passed; native and production promotion pending.`);
