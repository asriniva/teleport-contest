import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {callSounds,createSoundsEnvironment} from '../js/nethack/bindings/sounds.js';
import {createNativeSounds} from '../js/nethack/native/sounds.js';
import * as source from '../js/ported/sounds.js';
import {withCEnvironment} from '../js/c-runtime/context.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.sounds;
const {environment:e}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}}),game=e.enableGameWindows(layouts),owner=nativeStateFor(e),views=owner.nativeRecords;
assert.equal(e.enableGameWindows(layouts),game);
let checks=1,events=[];
const local=Object.create(game.sound),foreign=Object.create(local);
Object.defineProperty(foreign,'nativeOwner',{value:undefined});
for(const name of ['You_hear','You','pline','pline_The','verbalize'])local[name]=(...args)=>{events.push([name,...args.map(v=>typeof v==='string'?v:typeof v==='number'||typeof v==='bigint'?v:v?.address)]);};
local.rn2=(n,line,caller)=>{events.push(['rn2',n,line,caller]);return 0;};
local.body_part=()=>e.services.literal('hair');local.inhistemple=()=>1;local.temple_occupied=()=>-1;local.canseemon=()=>0;local.cansee=()=>0;local.halu_gname=()=>e.services.literal('deity');
const namespace={...source},native=createSoundsEnvironment(local,L,{source:game.nosound},namespace),legacy=createSoundsEnvironment(foreign,L,{source:game.nosound});Object.assign(namespace,createNativeSounds(native));
const allocate=type=>views.record(type,e.memory.calloc(1,e.ctypes.size(type)));
const m=allocate('struct monst'),pm=allocate('struct permonst');m.data=pm;m.mx=1;m.my=1;m.mhp=10;
assert.equal(native.monster(m.address),m);assert.equal(native.permonst(pm.address),pm);assert.equal(native.u,views.record('struct you',e.requireGlobal('u')));assert.equal(native.levl,owner.spatial.cells);checks+=4;
owner.spatial.monsters[1][1]=m;assert.equal(native.m_at(1,1),m);checks++;
const object=allocate('struct obj');owner.spatial.objects[1][1]=object;assert.equal(native.vobj_at(1,1),object);assert.equal(native.object(object.address),object);checks+=2;
const predicates=['throne_mon_sound','beehive_mon_sound','morgue_mon_sound','zoo_mon_sound','temple_priest_sound','oracle_sound'];
for(const name of predicates){
 events=[];const a=withCEnvironment(legacy,source[name],legacy.monster(m.address)),expected=[...events];
 events=[];const b=namespace[name](m);assert.equal(b,a,name+' result');assert.deepEqual(events,expected,name+' ordered dependencies/RNG');checks+=2;
}
for(const [name,type,setup] of [
 ['throne_mon_sound',L.COURT,()=>{m.msleeping=1;}],
 ['zoo_mon_sound',L.ZOO,()=>{m.msleeping=1;}],
 ['beehive_mon_sound',L.BEEHIVE,()=>{pm.mlet=L.S_ANT;pm.mflags1=BigInt(L.M1_FLY);}],
 ['morgue_mon_sound',L.MORGUE,()=>{pm.mflags2=BigInt(L.M2_UNDEAD);}],
]){
 m.msleeping=0;pm.mflags1=pm.mflags2=0n;pm.mlet=0;native.levl[1][1].roomno=L.ROOMOFFSET;native.svr.rooms[0].rtype=type;setup();
 events=[];const a=withCEnvironment(legacy,source[name],legacy.monster(m.address)),expected=[...events];events=[];const b=namespace[name](m);
 assert.equal(b,1);assert.equal(b,a);assert.deepEqual(events,expected,name+' positive source/RNG path');assert.ok(events.some(row=>row[0]==='rn2'));checks+=4;
}
// Exercise the two remaining predicates through their positive branches too.
const mextra=allocate('struct mextra'),priest=allocate('struct epri');m.mextra=mextra;mextra.epri=priest;m.ispriest=1;m.mcanmove=1;m.msleeping=0;pm.msound=L.MS_HUMANOID;
for(const name of ['temple_priest_sound','oracle_sound']){
 if(name==='oracle_sound')m.data=native.mons[L.PM_ORACLE];
 events=[];const a=withCEnvironment(legacy,source[name],legacy.monster(m.address)),expected=[...events];events=[];const b=namespace[name](m);
 assert.equal(b,1);assert.equal(b,a);assert.deepEqual(events,expected,name+' positive source/RNG path');assert.ok(events.some(row=>row[0]==='rn2'));checks+=4;
}
// A provider inheriting native capabilities cannot acquire native ownership.
const alternate=Object.create(game.sound);alternate.terrainBit=()=>0;
native.levl[1][1].roomno=L.ROOMOFFSET;native.svr.rooms[0].rtype=L.COURT;
assert.equal(callSounds(alternate,L,'mon_in_room',m.address,L.COURT),0);
assert.equal(callSounds(game.sound,L,'mon_in_room',m.address,L.COURT),true);checks+=2;
const throwing=Object.create(alternate);throwing.terrainBit=()=>{throw Error('foreign field');};
const before=e.transport.stackPosition();assert.throws(()=>callSounds(throwing,L,'mon_in_room',m.address,L.COURT),/foreign field/);
assert.equal(e.transport.stackPosition(),before);assert.equal(callSounds(game.sound,L,'mon_in_room',m.address,L.COURT),true);checks+=3;
// MON owns traversal and snapshots nmon before invoking a callback. Dead actors
// are skipped, and a callback that mutates the current link cannot change that.
const second=allocate('struct monst'),third=allocate('struct monst');second.mhp=0;third.mhp=10;third.mx=2;third.my=2;
m.nmon=second;second.nmon=third;third.nmon=0;native.svl.level.monlist=m;
const seen=[],saved=owner.functions.get(predicates[0]);let indirect=0;
const rawIndirect=e.functions.indirect;e.functions.indirect=(...args)=>{indirect++;return rawIndirect(...args);};
const predicate=actor=>{seen.push(actor);if(actor===m)m.nmon=0;return actor===third?1:0;};Object.assign(predicate,{nativeState:owner,nativeDirect:true,nativeSignature:'ip'});owner.functions.set(predicates[0],predicate);
try{
 owner.enter();let result;try{result=native.get_iter_mons(namespace.throne_mon_sound);}finally{owner.leave();}
 assert.equal(result,third);assert.deepEqual(seen,[m,third]);assert.equal(indirect,0);checks+=3;
 // Numeric foreign callbacks retain checked dispatch and current live identity.
 m.nmon=second;seen.length=0;const id=e.functions.functionPointer(at=>predicate(views.record('struct monst',at)),'ip');
 result=(owner.functions.get('get_iter_mons').nativeValuesEntry)(id);
 assert.equal(result,third);assert.deepEqual(seen,[m,third]);assert.equal(indirect,2);checks+=3;
 const invalid=e.functions.functionPointer(()=>0,'vp');assert.throws(()=>(owner.functions.get('get_iter_mons').nativeValuesEntry)(invalid),/incompatible C callback/);checks++;
}finally{owner.functions.set(predicates[0],saved);e.functions.indirect=rawIndirect;}
console.log(JSON.stringify({passed:true,checks,predicates:6,positiveRngPaths:6,scope:'Actual production canonical hero/actor/object/map identity and occupancy; native versus retained source predicate results and ordered dependencies/RNG; MON traversal dead skips, prefetched next link under mutation, direct branded callback and numeric foreign signature validation. Full recordings are separate.'}));
