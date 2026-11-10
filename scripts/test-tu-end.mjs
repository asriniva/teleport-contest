// Configured original END differential; foreign world/UI/process effects controlled.
import assert from './native-test-assert.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callEnd} from '../js/ported/end-runtime.js';
import * as core from '../js/ported/end.js';
import {C,R,T} from '../js/ported/c-runtime.js';
if(process.env.TELEPORT_NATIVE_TESTS==='1')throw Error('END native-host gate is pending; this fixture is original configured EmC only.');
const dir=resolve(process.env.TELEPORT_END_PROBE_DIR??'.cache/end-author');
const {default:rf}=await import(pathToFileURL(resolve(dir,'reference.mjs'))),{default:hf}=await import(pathToFileURL(resolve(dir,'hybrid.mjs')));
const reference=await rf(),L={};
const text=(m,p)=>{let i=Number(p);if(!i)return null;let e=i;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(i,e)).toString('latin1');};
for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
for(const m of readFileSync(new URL(import.meta.url),'utf8').matchAll(/L\.([A-Z][A-Z_0-9]+)\b/g))assert.ok(m[1]in L,'Missing fixture END constant '+m[1]);
const entered=new Set();let thrownService=null;const syntheticError=new Error('END synthetic foreign callback failure');let exceptionRestored=false;
const runtime={end:(services,name,...args)=>{entered.add(name);const saved=services.stackSave();try{return callEnd(new Proxy(services,{get(target,key,receiver){if(['rectState','trackState'].includes(key))return target[key];if(!Reflect.has(target,key))throw Error('Missing END environment key '+String(key));if(key===thrownService)return()=>{throw syntheticError;};return Reflect.get(target,key,receiver);}}),L,name,...args);}catch(error){assert.equal(services.stackSave(),saved,'END binding stack restored before unwinding to foreign C');if(error===syntheticError)exceptionRestored=true;throw error;}}};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context='initial';
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),output:text(m,m._probe_output())});
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(reference),context);for(let i=0;i<2;i++)assert.equal(modules[i]._probe_stack(),stacks[i],context+':stack');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(name,...args){const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],context+':'+name);check();return out[0];}
function string(m,s,cb){const bytes=Buffer.from(s,'latin1'),p=m._malloc(BigInt(bytes.length+1));try{m.HEAPU8.set(bytes,Number(p));m.HEAPU8[Number(p)+bytes.length]=0;return cb(BigInt(p));}finally{m._free(p);}}
function strings(name,s,...args){for(const m of modules)string(m,s,p=>m['_probe_'+name](p,...args));check();}
const reset=()=>call('reset'),opt=(n,v)=>call('option',n,v),g=(n,v)=>call('global',n,BigInt(v)),input=s=>strings('input',s),act=(op,a=0,b=0,c=0,n=0n)=>call('action',op,a,b,c,BigInt(n)),prop=(i,h=0n,e=0n,b=0n)=>call('property',i,BigInt(h),BigInt(e),BigInt(b));
const item=(i,t,c=L.GEM_CLASS,q=1n,next=-1,child=-1)=>call('item',i,t,c,BigInt(q),next,child),invent=i=>call('inventory',i),mon=(pm,cham=L.NON_PM,bits=0)=>call('monster_setup',pm,cham,bits),reason=(s,mode=1)=>strings('reason',s,mode);
assert.equal(core.deaths.length,16);assert.equal(core.ends.length,16);assert.equal(core.death_fixups.length,2);
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
// Byte strings and true char** update; every list size/spacing path.
for(const s of ['', 'one','first second','first second third','  first\tsecond\nthird  ','\xff fourth','one\v two\fthree\rfour','alpha '.repeat(120)]){context='english:'+JSON.stringify(s);reset();input(s);act(25);act(26);act(27);}
// Every disclosure option/default and invalid category retain actual byte output aliases.
for(const values of ['nnnnnn','yyyyyy','aaaaaa','++++++','------','??????'])for(const cat of 'iavgcox'){context='query:'+values+cat;reset();strings('disclosure',values);act(7,cat.charCodeAt(0));}
for(const s of ['getting stoned','fainted from lack of food','unrelated reason'])for(const how of [L.STONING,L.STARVING,L.DIED]){context='fixup:'+s+how;reset();reason(s);g(9,-7);act(5,how);}
// Signal/quit cancellation and wizard paths without real host signal/process effects.
for(const ign of [0,1])for(const mult of [-7,0,9]){context='interrupt:'+ign+mult;reset();g(0,ign);g(9,mult);opt(1,0);act(0);act(2,1);act(3,2);}
for(const debug of [0,1])for(const answer of [110,113,121]){context='quit:'+debug+answer;reset();g(1,debug);opt(0,answer);opt(1,0);act(1);}
for(const answer of [110,121,113,97])for(const inventory of [0,1]){context='disclose:'+answer+inventory;reset();strings('disclosure','??????');opt(0,answer);if(inventory){item(0,L.FIRST_AMULET,L.AMULET_CLASS);invent(0);}act(9,L.DIED,0);}
// Life-saving has real property/global/alias writes and signed64 state.
for(const how of [L.DIED,L.CHOKING,L.GENOCIDED])for(const swallowed of [0,1])for(const hp of [0,80]){context='savelife:'+how+swallowed+hp;reset();g(6,hp);g(7,1);g(8,10);g(10,swallowed);prop(L.SICK,1n);prop(L.UNCHANGING,3n);act(10,how);}
for(const saved of [0,1])for(const how of [L.DIED,L.CHOKING,L.GENOCIDED,L.TRICKED]){context='done-survive:'+saved+how;reset();g(1,1);opt(1,0);prop(L.LIFESAVED,0n,BigInt(saved));call('equipment',0,0);input('killer');act(30,L.KILLED_BY_AN);act(16,how);}
// Recursive valuables collection and stable complete-native-record insertion sort.
for(const amount of [1n,2147483651n,9007199254740995n]){context='valuables:'+amount;reset();item(0,L.FIRST_AMULET,L.AMULET_CLASS,amount,1);item(1,L.FIRST_REAL_GEM,L.GEM_CLASS,2n,2);item(2,L.LAST_GLASS_GEM,L.GEM_CLASS,5n);invent(0);act(11);act(29);act(12);}
for(const count of [0,1]){context='artifact:'+count;reset();item(0,L.BELL_OF_OPENING,L.AMULET_CLASS,1n,1);item(1,L.CANDELABRUM_OF_INVOCATION,L.AMULET_CLASS);invent(0);g(16,9007199254740993n);act(14,count,7);}
// Limbo object cleanup retains ownership and original native locations.
for(const perm of [0,1])for(const accessible of [0,1]){context='cleanup:'+perm+accessible;reset();item(0,L.CORPSE);item(1,L.STATUE);item(2,L.FIRST_AMULET);call('equipment',2,0);call('equipment',3,1);call('equipment',1,2);g(15,perm);opt(25,accessible);act(13);}
// Fuzzer RNG sequencing is compared at original source locations.
for(const seed of [1,2,7,42,123456789])for(const seq of [0n,3n,103n]){context='fuzzer:'+seed+seq;reset();call('seed',seed);g(1,1);g(12,seq);g(13,0);act(15,L.DIED);}
// Killer records have actual allocated linked nodes and exact stream semantics.
context='killers';reset();for(let i=1;i<=4;i++){input('delayed '+i);act(20,i,i%3);}input('updated');act(20,2,17);for(let i=0;i<=5;i++)act(21,i);act(22,2);act(23,L.WRITING);act(23,L.FREEING);opt(13,42);opt(14,9);act(24);act(23,L.WRITING);act(23,L.FREEING);
// Serializer callbacks may write through the same killer record/linked-list aliases.
context='killer-write-alias';reset();input('aliased');act(20,7,2);opt(85,1);act(23,L.WRITING);assert.match(snapshot(reference).state,/!liased/);act(23,L.FREEING);opt(85,0);opt(86,4);opt(13,100);opt(14,8);act(24);act(23,L.WRITING);act(23,L.FREEING);
// Container traversal, original Loot iteration and live object flags.
for(const all of [0,1])for(const identified of [0,1])for(const empty of [0,1]){context='container:'+all+identified+empty;reset();item(0,L.LARGE_BOX,L.AMULET_CLASS,1n,3,empty?-1:1);item(1,L.FIRST_AMULET,L.AMULET_CLASS,2n,2);item(2,L.FIRST_REAL_GEM,L.GEM_CLASS);item(3,L.BAG_OF_TRICKS,L.AMULET_CLASS);invent(0);act(18,identified,all,1);}
// Full endgame orchestration: real exit captured by C protected fixture boundary.
for(const how of [L.DIED,L.STONING,L.BURNING,L.GENOCIDED,L.QUIT,L.ESCAPED,L.ASCENDED,L.PANICKED])for(const windows of [0,1]){context='really-done:'+how+windows;reset();g(3,windows);g(21,1);opt(1,1);item(0,L.FIRST_REAL_GEM,L.GEM_CLASS,2n);invent(0);g(16,9007199254740993n);opt(29,25);act(17,how);}
for(const pm of [L.PM_HUMAN,L.PM_GHOST,L.PM_GHOUL,L.PM_WRAITH])for(const bits of [0,1,2,4,8,16,128]){context='death-name:'+pm+bits;reset();mon(pm,L.NON_PM,bits);g(1,1);opt(1,0);reason('42:paralyzed by a ghoul',2);act(4,L.DIED);}
// Distinct real/camouflaged species use actual prepared monster catalogue fields.
for(const [pm,cham,bits]of [[L.PM_HUMAN,L.PM_VAMPIRE,0],[L.PM_GHOST,L.PM_HUMAN,0],[L.PM_HUMAN,L.NON_PM,32],[L.PM_WRAITH,L.NON_PM,0]]){context='shape:'+pm+cham+bits;reset();mon(pm,cham,bits);opt(1,1);act(4,L.DIED);}
for(const stage of [0,1]){context='growth-reentry:'+stage;reset();opt(90,1);opt(91,1);if(stage){mon(L.PM_GHOST,L.NON_PM,129);g(1,1);opt(1,0);act(4,L.DIED);}else{g(0,1);act(0);}for(const m of modules)assert.ok(m.HEAPU8.byteLength>33554432);}
// Native callbacks reread automatic buffers after growth/reentry and mutate live records.
context='callback-alias';reset();opt(90,1);opt(91,1);opt(92,1);item(0,L.BELL_OF_OPENING,L.AMULET_CLASS);invent(0);act(14,0,7);assert.match(snapshot(reference).trace,/alias-put:/);
// Inactive dump body and orderly shutdown preserve ordering; no real process exits.
context='teardown';reset();act(8,L.ASCENDED,0,0,9007199254740993n);act(19,7);assert.match(snapshot(reference).trace,/nomux_capture_write_input_boundary;.*l_nhcore_call;.*freedynamicdata;.*l_nhcore_done;.*exit:7;/);
// NH_abort's recursive static guard persists for each real Module; panic varargs are native.
context='panic';reset();g(3,1);g(19,2);opt(15,1);input('message');act(6,0,0,0,9007199254740993n);act(28);
// Distinct real Modules own independent cat/abort/constant/literal state.
const prior=snapshot(modules[1]);const separate=[await rf(),await hf({nethackPorted:runtime})];
for(const m of separate)m._probe_reset();
for(const m of separate){m._probe_option(1,0);m._probe_global(1,1n);m._probe_action(16,L.TRICKED,0,0,0n);}
assert.deepEqual(snapshot(separate[1]),snapshot(separate[0]));comparisons++;assert.deepEqual(snapshot(modules[1]),prior);
for(const m of separate){m._probe_global(3,1n);m._probe_option(15,1);string(m,'fresh panic',p=>m._probe_input(p));m._probe_action(6,0,0,0,9007199254740993n);}
assert.deepEqual(snapshot(separate[1]),snapshot(separate[0]));assert.match(snapshot(separate[0]).trace,/panic number 9007199254740993 string fresh panic/);assert.match(snapshot(separate[0]).trace,/abort;/);comparisons++;assert.deepEqual(snapshot(modules[1]),prior);assert.equal(C,undefined);
// The original per-Module cat static affects both score and final pet message.
for(const m of separate){m._probe_reset();m._probe_item(0,L.LARGE_BOX,L.AMULET_CLASS,1n,-1,1);m._probe_item(1,L.CORPSE,L.FOOD_CLASS,1n,-1,-1);m._probe_inventory(0);m._probe_global(30,1n);m._probe_option(1,1);m._probe_action(17,L.ESCAPED,0,0,0n);}
assert.deepEqual(snapshot(separate[1]),snapshot(separate[0]));assert.match(snapshot(separate[0]).trace,/Schroedinger's cat/);comparisons++;assert.deepEqual(snapshot(modules[1]),prior);
// Binding-only foreign JS exception witness; its interrupted outer C fixture is discarded.
const failing=await hf({nethackPorted:runtime});failing._probe_reset();failing._probe_global(3,1n);thrownService='raw_print';assert.throws(()=>failing._probe_action(6,0,0,0,123n),e=>e===syntheticError);thrownService=null;assert.equal(exceptionRestored,true);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
const expectedEntries=Object.keys(core).filter(name=>typeof core[name]==='function');assert.equal(expectedEntries.length,29);assert.deepEqual([...entered].sort(),expectedEntries.sort());
writeFileSync(resolve(dir,'summary.json'),JSON.stringify({configuredFunctions:29,entered:expectedEntries,exactComparisons:comparisons,bindingExceptionWitnesses:1,reference:'original prepared end.c with actual prepared objects.c/monst.c + libc',nativeHost:'pending',sharedGame:'pending',publicRecordings:'pending',branchCoverage:'not complete; entrypoint reachability only',fixtureScope:'controlled foreign world/naming/UI/serializers/process/signal/report dependencies; source structs, catalogue, libc, allocation and memory growth are real'},null,2)+'\n');
console.log(`END first-pass EmC: ${comparisons} exact C/hybrid comparisons passed plus1 binding-exception witness;29 original functions; native/shared/public parity pending.`);
