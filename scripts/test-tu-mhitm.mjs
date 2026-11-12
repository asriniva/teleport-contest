import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
// First-pass EmC comparison: original TU vs imported JS; native parity pending.
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callMhitm} from '../js/nethack/bindings/mhitm.js';
import {C,R,T} from '../js/c-runtime/context.js';
const dir=resolve(process.env.TELEPORT_MHITM_PROBE_DIR??'.cache/tu-probes');
const path=kind=>pathToFileURL(resolve(dir,(process.env.TELEPORT_MHITM_PROBE_DIR?'':'mhitm-')+kind+'.mjs'));
const {default:rf}=await loadFixture("mhitm",path('reference')),{default:hf}=await loadFixture("mhitm",path('hybrid'));
const reference=await rf();
function text(m,p){p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
const L={};for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
for(const m of readFileSync(new URL(import.meta.url),'utf8').matchAll(/L\.([A-Z][A-Z_0-9]+)\b/g))assert.ok(m[1] in L,'Missing fixture constant '+m[1]);
const runtime={mhitm:(services,name,...args)=>callMhitm(services,L,name,...args)};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context='';
function snapshot(m){return{state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())};}
function call(name,...args){let vals=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(vals[1],vals[0],context+':'+name);assert.deepEqual(snapshot(modules[1]),snapshot(reference),context+':'+name);for(let i=0;i<2;i++)assert.equal(modules[i]._probe_stack(),stacks[i]);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;return vals[0];}
const reset=()=>call('reset'),opt=(k,v)=>call('option',k,v),field=(index,key,value)=>call('field',index,key,BigInt(value)),act=(op,a=0,b=1,c=-1,e=0)=>call('action',op,a,b,c,e),attack=(type,damage,n=1,sides=4)=>call('attack',0,type,damage,n,sides),form=(index,pm,type,damage,n=1,sides=4)=>call('form',index,pm,type,damage,n,sides),state=()=>snapshot(reference).state,trace=()=>snapshot(reference).trace;
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
reset();assert.notEqual(call('catalogue',L.PM_HUMAN,0),0n);assert.equal(call('catalogue',L.PM_HUMAN,3),BigInt(L.AT_WEAP));assert.notEqual(call('catalogue',L.DAGGER,5),0n);
reset();attack(L.AT_GAZE,L.AD_STON,0,0);act(12);assert.match(trace(),/dice:0:0;/);assert.doesNotMatch(trace(),/rn2:0;/);
// Armor protection exact long values and low-byte boolean/status stores.
for(let a=-2;a<=260;a++){reset();act(21,a);}
for(const amt of [-1,0,1,2,126,127,128,255,256,257,65535]){reset();field(0,13,(1n<<63n)-1n);field(0,20,17);act(14,0,1,-1,amt);}
for(const amt of [-10,0,1,125,127,128,256])for(const how of [-1,0,255,256,257])for(const resistant of [0,1]){reset();opt(3,resistant?(1<<L.SLEEP_RES):0);field(0,10,2);act(15,0,1,amt,how);}
// Sleep and paralysis release hero holds only through source sleeping path.
for(const swallow of [0,1])for(const asleep of [0,1])for(const sticky of [0,1]){reset();call('hero',swallow,0,-1,0n,0,0);field(0,3,asleep);opt(26,sticky);act(16);}
// Noise cadence, signed64 subtraction and deafness; original source message trace.
for(const distance of [1,6])for(const deaf of [0,1])for(const moves of [0n,10n,11n,9223372036854775807n]){reset();call('mon',0,L.PM_HUMAN,distance,1,40,0n);call('hero',0,-1,-1,0n,deaf,0);call('global',2,moves);attack(L.AT_EXPL,L.AD_PHYS);act(0);act(0);}
// Reveal both monsters, visible/nonvisible, mimics and undetected states.
for(const visible of [0,1])for(const maptype of [0,L.M_AP_OBJECT])for(const sense of [0,1]){reset();call('global',0,BigInt(visible));field(0,15,maptype);field(1,2,1);opt(1,sense);attack(L.AT_CLAW,L.AD_PHYS);act(1);act(2);}
// Native addressable attack/mhitm_data records and interior hitflags pointer.
const physical=[L.AT_CLAW,L.AT_KICK,L.AT_BITE,L.AT_STNG,L.AT_TUCH,L.AT_BUTT,L.AT_TENT,L.AT_HUGS,L.AT_WEAP];
for(const type of physical)for(const mode of [0,1,2,3])for(const visible of [0,1]){context=JSON.stringify({type,mode,visible});reset();call('global',0,BigInt(visible));attack(type,L.AD_PHYS);opt(0,1);if(mode){opt(11,1);opt(12,mode===1?0:7);opt(13,mode===2?L.M_ATTK_AGR_DIED:0);opt(14,mode===3?1:0);}act(7,0,1,-1,17);assert.match(trace(),/knock:0:1:.*:1;/);}
for(const flags of [0,L.M_ATTK_HIT,L.M_ATTK_DEF_DIED,L.M_ATTK_AGR_DIED,L.M_ATTK_HIT|L.M_ATTK_DEF_DIED]){reset();attack(L.AT_CLAW,L.AD_PHYS);opt(44,1);opt(45,flags);act(12,0,1,-1,9);}
// Actual data-dependent petrification protection and lifesaving branches.
for(const type of [L.AT_CLAW,L.AT_BITE,L.AT_HUGS,L.AT_GAZE])for(const worn of [0n,BigInt(L.W_ARMG),BigInt(L.W_ARMC)|BigInt(L.W_ARMG),1n<<60n])for(const save of [0,1]){reset();call('mon',0,L.PM_HUMAN,10,10,40,worn);call('mon',1,L.PM_COCKATRICE,11,10,40,0n);attack(type,L.AD_PHYS);opt(10,save);act(12,0,1,-1,4);}
// Damage/death, digestion special forms, native grow_up and zombie flags.
for(const pm of [L.PM_HUMAN,L.PM_GREEN_SLIME,L.PM_WRAITH,L.PM_NURSE,L.PM_MEDUSA])for(const ad of [L.AD_PHYS,L.AD_DGST])for(const save of [0,1]){reset();call('mon',1,pm,11,10,1,0n);attack(L.AT_ENGL,ad,2,8);opt(10,save);opt(11,1);opt(12,30);act(12,0,1,-1,13);}
// Failed grabs retain exact local buffer aliases and ordinary hits proceed.
for(const ad of [L.AD_PHYS,L.AD_WRAP,L.AD_STCK,L.AD_DGST])for(const tail of [0,1])for(const who of [0,3]){reset();call('global',5,BigInt(tail));attack(L.AT_HUGS,ad);act(6,who);}
// Engulf geometry/terrain and full grid restoration, including death outcomes.
for(const terrain of [L.ROOM,L.STONE,L.TREE,L.IRONBARS])for(const pm of [L.PM_HUMAN,L.PM_AIR_ELEMENTAL,L.PM_FIRE_ELEMENTAL]){reset();call('mon',0,pm,10,10,40,0n);call('terrain',11,10,terrain);attack(L.AT_ENGL,L.AD_DGST);act(9);act(10);}
for(const damage of [0,3,100])for(const agrdead of [0,L.M_ATTK_AGR_DIED])for(const good of [0,1]){reset();attack(L.AT_ENGL,L.AD_DGST);opt(11,1);opt(12,damage);opt(13,agrdead);opt(36,good);act(10);}
// Gaze cancellation/Archon blind exception/Medusa reflections and explosion life.
for(const pm of [L.PM_HUMAN,L.PM_ARCHON,L.PM_MEDUSA])for(const cancelled of [0,1])for(const reflected of [0,1]){reset();call('mon',0,pm,10,10,40,0n);attack(L.AT_GAZE,pm===L.PM_ARCHON?L.AD_BLND:L.AD_STON);field(0,0,cancelled);opt(8,reflected);act(8);}
for(const ad of [L.AD_PHYS,L.AD_FIRE,L.AD_COLD,L.AD_ELEC])for(const save of [0,1])for(const cancelled of [0,1]){reset();attack(L.AT_EXPL,ad);opt(10,save);field(0,0,cancelled);field(0,8,1);field(0,17,1);act(11);}
// Passive goto skips the live-only response, but still applies acid and death.
for(const ad of [L.AD_ACID,L.AD_ENCH,L.AD_PLYS,L.AD_COLD,L.AD_STUN,L.AD_FIRE,L.AD_ELEC,L.AD_PHYS])for(const hit of [0,1])for(const dead of [0,L.M_ATTK_DEF_DIED])for(const seed of [1,2,7]){context=JSON.stringify({ad,hit,dead,seed});reset();call('seed',seed);form(1,L.PM_HUMAN,L.AT_NONE,ad,2,4);opt(0,1);act(19,0,1,hit,dead);}
// Floating eye identity-dependent view/reflection path uses actual original table.
for(const reflection of [0,1]){reset();call('mon',1,L.PM_FLOATING_EYE,11,10,40,0n);opt(8,reflection);act(19,0,1,1,0);}
// Monster polymorph source branches retain scalar return and native effects.
for(const which of [1,3])for(const magic of [0,1])for(const changed of [0,1]){reset();opt(15,magic);opt(9,changed);call('prop',L.ANTIMAGIC,BigInt(magic),0n,0n);act(13,0,which,-1,7);}
for(const pm of [L.PM_HUMAN,L.PM_MEDUSA,L.PM_FIRE_ELEMENTAL,L.PM_STEAM_VORTEX]){reset();call('mon',0,pm,10,10,40,0n);act(17,0,1,0);}
for(const typ of [L.DAGGER,L.SILVER_SABER,L.SPEAR])for(const blind of [0,1]){reset();call('item',0,typ,0,0,2n);call('hero',0,-1,-1,0n,0,blind);act(18,0,1,0);attack(L.AT_WEAP,L.AD_PHYS);opt(23,1);act(7,0,1,0,12);}
for(const used of [0,19,20,100])for(const message of [0,1]){reset();opt(35,1);field(0,14,used);act(20,0,1,-1,message);}
// Full attack-loop local arrays, native alt-attack writes, return attacks/displace.
for(const pm of [L.PM_HUMAN,L.PM_GRID_BUG,L.PM_ARCHON,L.PM_MEDUSA,L.PM_FIRE_ELEMENTAL])for(const visible of [0,1]){reset();call('mon',0,pm,10,10,50,0n);call('global',0,BigInt(visible));opt(0,1);act(5);act(3);}
for(const seed of [1,2,7,17]){reset();call('seed',seed);act(4);}
for(const nullarg of [0,1]){reset();act(4,nullarg?-1:0,nullarg?1:-1);act(5,nullarg?-1:0,nullarg?1:-1);}
// Multi-slot result-array flow, hug prerequisite, and alternate attack storage.
for(const seed of [1,2,7,42])for(const fail of [0,1]){
 reset();call('seed',seed);form(0,L.PM_HUMAN,L.AT_CLAW,L.AD_PHYS,1,3);call('form_attack',0,1,L.AT_CLAW,L.AD_PHYS,1,3);call('form_attack',0,2,L.AT_HUGS,L.AD_WRAP,1,4);opt(40,fail?-30:100);act(5);assert.match(trace(),/get:0:1:2:/);
}
// Source booleans use signed-byte stores, including noncanonical callback writes.
for(const done of [-128,127,128,255,256,257]){reset();attack(L.AT_CLAW,L.AD_PHYS);opt(11,1);opt(12,7);opt(13,L.M_ATTK_HIT);opt(14,done);act(12);}
// Normal compatibility/seduction, artifact message suppression and live alias names.
for(const compat of [0,1,2])for(const sight of [0,1]){reset();opt(7,compat);field(1,6,sight);attack(L.AT_BITE,L.AD_PHYS);act(7);}
// Every controlled callback stage can reenter an original function and grow memory.
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13,14]){reset();const before=modules.map(m=>m.HEAPU8.byteLength);opt(50,stage);opt(51,stage);attack(L.AT_CLAW,L.AD_PHYS);opt(42,1);if(stage===2){opt(35,1);act(20,0,1,-1,1);}else if(stage===4){field(1,2,1);act(1);}else if(stage===3){call('global',0,0n);act(0);}else if(stage===7){call('mon',0,L.PM_ARCHON,10,10,40,0n);attack(L.AT_GAZE,L.AD_BLND);act(8);}else if(stage===9){act(4);}else if(stage===10||stage===11){field(1,22,1);act(12);}else if(stage===12){opt(9,1);act(13,0,1,-1,5);}else if(stage===13){call('mon',0,L.PM_MEDUSA,10,10,40,0n);attack(L.AT_GAZE,L.AD_STON);opt(8,1);act(8);}else if(stage===14){form(1,L.PM_HUMAN,L.AT_NONE,L.AD_CORR,2,4);act(17,1,0,0);}else act(5);assert.match(trace(),new RegExp('nested:'),'callback stage '+stage);assert.match(trace(),new RegExp('grow:'+stage+';'));modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>before[i],'actual growth at callback '+stage));}
// Same dispatcher serves two independent real hybrid Modules without state leakage.
const other=await hf({nethackPorted:runtime});other._probe_reset();other._probe_field(0,14,18n);other._probe_option(35,1);other._probe_action(20,0,1,-1,1);assert.match(text(other,other._probe_snapshot()),/rng:2;/);assert.equal(C,undefined);
console.log(`MHITM first-pass EmC: ${comparisons} exact comparisons passed; 22 original functions; native parity pending.`);
