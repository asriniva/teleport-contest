// Configured first-pass C/hybrid test. Native/game/public parity are separate gates.
import assert from 'node:assert/strict';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {createAllmainBridge} from '../js/nethack/bindings/allmain.js';
import {C} from '../js/c-runtime/context.js';
const directory=resolve(process.env.ALLMAIN_PROBE_DIR??'.cache/tu-probes');
const refFactory=(await import(pathToFileURL(resolve(directory,'allmain-reference.mjs')))).default;
const jsFactory=(await import(pathToFileURL(resolve(directory,'allmain-hybrid.mjs')))).default;
const text=(m,at)=>{at=Number(at);let end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.subarray(at,end)).toString('latin1');};
const layouts=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
let modules,L,bridge,fields,observe,lifetime,beforeWelcome,comparisons=0,scenario='initial';
const dispatch=(services,name,...args)=>{const wrapped=observe||lifetime?Object.assign(Object.create(services),{get_nh_event(){observe?.(C);return services.get_nh_event();},getnow(){if(lifetime)beforeWelcome=services.stackSave();return services.getnow();},notice_all_mons(...args){if(lifetime){assert.equal(services.stackSave(),beforeWelcome,'welcome releases its original local buffer before later newgame callbacks');comparisons++;}return services.notice_all_mons(...args);}}):services;return bridge(wrapped,name,...args);};
async function pair(){const a=await refFactory();L=layouts(a);bridge??=createAllmainBridge(L);const b=await jsFactory({nethackPorted:{allmain:dispatch}});assert.deepEqual(layouts(b),L);comparisons++;modules=[a,b];fields=Object.fromEntries(Array.from({length:a._probe_fields()},(_,i)=>[text(a,a._probe_field_name(i)),i]));reset();}
await pair();
function reset(seed=1){modules.forEach(m=>m._probe_reset(seed));}
function compare(){const states=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));for(const key of['state','trace'])if(states[0][key]!==states[1][key]){let p=0;while(states[0][key][p]===states[1][key][p]&&p<states[0][key].length)p++;console.error(scenario,key,'difference',p,JSON.stringify(states[0][key].slice(Math.max(0,p-80),p+180)),JSON.stringify(states[1][key].slice(Math.max(0,p-80),p+180)));}assert.deepEqual(states[1],states[0],scenario);assert.equal(C,undefined);comparisons++;}
function call(name,...args){const stacks=modules.map(m=>m._probe_stack());const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],scenario+' return');modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i],scenario+' stack'));compare();return result[0];}
const field=(name,v)=>{assert.notEqual(fields[name],undefined,name);return call('field',fields[name],BigInt(v));},option=(i,v)=>call('option',i,v),invoke=(a,v=0)=>call('call',a,v);
const property=(i,h=1n,e=0n,b=0n)=>call('prop',modules[0]._probe_prop_id(i),h,e,b);
// Full source inventory, including startup/menu/newgame and the finite wrappers.
for(const action of[0,1,2,3,4,5,7,8,9,10,11,12,13]){scenario='basic '+action;reset();invoke(action);}
// Actual libc difftime retains signed64 input values before producing double.
for(const [a,b]of[[0n,0n],[1n,0n],[-1n,0n],[2147483648n,-2147483649n],[9007199254740997n,9007199254740996n],[-9007199254740997n,-9007199254740996n],[(1n<<63n)-1n,(1n<<63n)-2n]]){
 scenario='time '+a+'/'+b;call('time',1,a,b);if(a>-(1n<<63n)&&a<(1n<<63n)-1024n)call('time',0,a,0n);
}
for(const resuming of[0,1])for(const moon of[0,1,4])for(const friday of[0,1]){
 scenario='preamble';reset();option(0,moon);option(1,friday);field('iflags.deferred_X',1);field('iflags.fuzzerpending',1);field('iflags.perm_invent',1);field('gd.defer_see_monsters',1);invoke(1,resuming);
}
for(const move of[1,3,7,11,12,13,23,127,-1])for(const wt of[0,1,2,3,4,5,99])for(const fast of[0,1,2]){
 scenario=`movement ${move}/${wt}/${fast}`;reset();call('poly',0,move,L.S_EEL);if(fast)property(0,fast===1?0x04000000n:1n);invoke(2,wt);
}
for(const steed of[0,1])for(const moved of[0,1]){scenario='mounted';reset();call('steed',steed);field('u.umoved',moved);option(3,17);invoke(2,3);}
for(const wizard of[0,1])for(const level of[1,5,14,30])for(const wt of[0,2,4])for(const energy of[0,1])for(const turn of[0n,1n,20n,21n,2147483648n,9007199254740997n]){
 scenario=`Pw ${wizard}/${level}/${wt}/${energy}/${turn}`;reset();call('role',wizard);field('u.ulevel',level);field('svm.moves',turn);if(energy)property(13);if(level%2)property(14,0n,1n);field('gm.multi',9);invoke(7,wt);
}
for(const poly of[0,1])for(const regen of[0,1])for(const sleepy of[0,1])for(const moved of[0,1])for(const wt of[0,2,4])for(const hp of[0,1,9,14,15]){
 scenario=`HP ${poly}/${regen}/${sleepy}/${moved}/${wt}/${hp}`;reset(hp+7);call('poly',poly,12,L.S_EEL);field(poly?'u.mh':'u.uhp',hp);field('u.umoved',moved);field('svm.moves',20);if(regen)property(15);if(sleepy){property(17);field('u.usleep',1);option(13,1);}invoke(8,wt);
}
for(const occupation of[0,1])for(const meal of[0,1])for(const multi of[-3n,0n,8n,9007199254740997n]){scenario='occupation';reset();call('occupation',occupation);option(6,meal);field('gm.multi',multi);invoke(9);}
for(const caps of[0n,0x4000n,0x8000n,0xc000n,(1n<<63n)|0xc000n])for(const splash of[0,1])for(const fail of[0,1]){
 scenario='windows';reset();call('caps',caps);field('iflags.wc_splash_screen',splash);option(18,fail);invoke(10);
}
for(const fresh of[0,1])for(const female of[0,1])for(const original of[0,1])for(const roleFemale of[0,1])for(const adrift of[-1,0,1]){
 scenario='welcome';reset();call('sex',female,original,roleFemale);field('u.ualign.type',adrift);invoke(12,fresh);
}
for(const found of[0,1])for(const yes of[0,1]){scenario='tutorial';reset();option(8,found);option(7,yes);invoke(5);}
for(const seed of[1,47,12558])for(const moved of[0,1])for(const multi of[-3n,-1n,0n,1n,7n,9n]){
 scenario=`core ${seed}/${moved}/${multi}`;reset(seed);field('svc.context.move',moved);field('gm.multi',multi);field('u.umoved',1);field('iflags.pending_customizations',1);field('svc.context.bypasses',1);field('iflags.sanity_check',1);field('svc.context.resume_wish',1);field('iflags.hilite_delta',1);field('svm.moves',77);invoke(4);invoke(4);
}
for(const flag of[0,1])for(const keep of[0,1])for(const nearby of[0,1]){scenario='occupation core';reset();call('occupation',flag);option(14,keep);option(5,nearby);invoke(4);}
for(const callbackBound of[0,1])for(const demi of[0,1]){scenario='RNG bound callback';reset();option(25,callbackBound);field('u.uevent.udemigod',demi);call('roll',0);invoke(3);field('svc.context.move',1);property(4);property(5);field('u.ulycn',L.PM_WIZARD);invoke(4);}
for(const legacy of[0,1])for(const reroll of[0,2])for(const pauper of[0,1]){
 scenario='newgame';reset();field('flags.legacy',legacy);field('u.uroleplay.reroll',1);field('u.uroleplay.pauper',pauper);option(17,reroll);call('clock',9007199254740997n);invoke(11);
}
for(const callback of[20,21]){scenario='growth/reentry '+callback;reset();option(callback,1);field('gm.multi',12);const sizes=modules.map(m=>m.HEAPU8.byteLength);invoke(1);if(callback===20)modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>sizes[i]));}
// Signed-short movement storage narrows after addition, before the next comparison.
for(const amount of[32760,32767,-32768,-7]){scenario='short movement '+amount;reset();field('u.umovement',amount);invoke(2,0);}
for(const count of[9007199254740997n,-9007199254740997n,(1n<<63n)-1n,-(1n<<63n)]){
 scenario='long multi '+count;reset();field('gm.multi',count);field('gc.command_count',count);invoke(4);
}
for(const hallu of[0,1])for(const genocide of[0,1]){scenario='polymorphed welcome';reset();call('poly',1,12,L.S_EEL);option(16,genocide);if(hallu)property(2);invoke(12,0);}
scenario='Lua callback ABI';reset();call('lua',1);invoke(4);
for(const [move,water,buried,amulet]of[[1,1,0,1],[1,0,1,0],[0,0,0,1]]){
 scenario='mainloop senses';reset();field('svc.context.move',move);field('u.uburied',buried);field('u.uhave.amulet',amulet);field('u.uevent.amulet_wish',0);field('u.utrap',1);field('u.utraptype',L.TT_LAVA);field('svc.context.seer_turn',0);if(water)property(9);property(2);invoke(4);
}
// Typedef-based signed and unsigned64 views are observed inside actual C callbacks.
for(const value of[9007199254740997n,-9007199254740997n,(1n<<63n)-1n,-(1n<<63n)]){
 scenario='typed callback64 '+value;reset();field('iflags.hilite_delta',value);field('u.usleep',value);field('svc.context.tribute.tributesz',BigInt.asUintN(64,value));
 observe=env=>{assert.equal(env.iflags.hilite_delta,value);assert.equal(env.u.usleep,value);assert.equal(env.svc.context.tribute.tributesz,BigInt.asUintN(64,value));comparisons+=3;};invoke(4);observe=undefined;
}
scenario='internal welcome stack lifetime';reset();lifetime=true;invoke(11);lifetime=false;
// Independent raw-snapshot witness: the duplicate flags field prints full long64.
for(const value of[2147483648n,-2147483649n,9007199254740997n,-9007199254740997n]){
 scenario='raw sleep snapshot64 '+value;reset();field('u.usleep',value);
 for(const m of modules){assert.ok(text(m,m._probe_snapshot()).includes(';flags:0/0/'+value+'/0;'),'raw snapshot retains signed long u.usleep '+value);comparisons++;}
}
// Infinite moveloop remains infinite in source; a controlled event callback exits.
scenario='moveloop controlled callback exit';reset();option(22,3);modules.forEach(m=>assert.throws(()=>m._probe_call(6,0),/ALLMAIN fixture exit 22/));assert.equal(C,undefined);compare();
scenario='billion-turn cap';reset();field('svc.context.move',1);field('svm.moves',999999999n);modules.forEach(m=>assert.throws(()=>m._probe_call(4,0),new RegExp('ALLMAIN fixture exit '+L.ESCAPED)));assert.equal(C,undefined);compare();
// Module isolation of the two original file-scope mutable mainloop values.
const old=modules;await pair();scenario='second Module';invoke(1);field('svc.context.move',1);invoke(4);modules=old;reset(83);scenario='original Module reused';invoke(1);field('svc.context.move',1);invoke(4);
console.log(`ALLMAIN: ${comparisons} configured Emscripten-C/JS comparisons passed; native/game/public gates pending.`);
