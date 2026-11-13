// Live-main ownership and direct-dispatch checks, beyond isolated provider tests.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {enableMonsterLifecycle} from '../js/nethack/monster-lifecycle.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {callVision} from '../js/nethack/bindings/vision.js';
import {C,withCEnvironment} from '../js/c-runtime/context.js';
const reference='.cache/full-original-c-v1';
const input=JSON.parse(fs.readFileSync(reference+'/scenarios/death.json'));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
let runtime;
const result=runStandaloneProgram(reference+'/assets',{...input,keys:input.keys.slice(0,256),observeRuntime:r=>{runtime=r;}});
assert.deepEqual(result.status,{kind:'input-exhausted'});
const {environment}=runtime,owner=nativeStateFor(environment);
assert.equal(owner.depth,0,'input exhaustion publishes the entire connected native graph');
assert.equal(owner.dirty.size,0);
for(const name of ['movemon','mcalcdistress','healmon','mfndpos','dochugw','m_move','domove','lookaround','test_move','vision_recalc','clear_path','does_block','moveloop','moveloop_core','moveloop_preamble','stop_occupation','timet_to_seconds','timet_delta']){
 assert.ok(owner.functions.has(name),name+' has native dispatch');
 assert.equal(owner.functions.get(name).nativeState,owner,name+' uses the common native owner');
}
const lifecycle=enableMonsterLifecycle(environment,layouts);
const vision=callVision({moduleKey:environment},layouts.vision,'environment');
const hero=owner.records.get('struct you:'+environment.requireGlobal('u'));assert.ok(hero);
assert.equal(environment.transport.scoped(()=>hero),hero,'canonical records remain synchronous values across legacy scopes');
assert.equal(hero.table,undefined,'legacy table probes observe ordinary missing JS properties on complete records');
assert.equal(hero.then,undefined,'complete records are not promises');
owner.completeRecordTypes.delete('struct you');
try{assert.throws(()=>hero.table,/Unknown HACK record field/,'partial legacy projections retain their unknown-field guard');}
finally{owner.completeRecordTypes.add('struct you');}
const turn=environment.state('game-startup-context');
assert.equal(turn.u,hero,'turn loop consumes the canonical hero');
assert.equal(turn.movemon,owner.functions.get('movemon'),'turn dependencies call the native engine directly');
assert.equal(environment.services.moveloop_core.nativeEntry,owner.functions.get('moveloop_core'));
assert.equal(turn.u.uprops[1],owner.records.get('struct prop:'+turn.u.uprops[1].address));
const temporaryCount=environment.memory.live.size,scopeMarker={nativeTurnCaller:true};
withCEnvironment(scopeMarker,()=>{
 assert.throws(()=>turn.nativeTurn(()=>{assert.equal(C,scopeMarker,'native turn scopes do not switch the C environment');assert.equal(owner.depth,1);environment.transport.stackAlloc(32);throw Error('native turn cleanup');}),/native turn cleanup/);
 assert.equal(C,scopeMarker);
});
assert.equal(owner.depth,0);assert.equal(environment.memory.live.size,temporaryCount,'a completed or throwing turn frees its temporaries');
assert.equal(lifecycle.context.u,hero,'hero has one identity across native providers');
assert.equal(vision.u,hero,'visibility consumes the canonical hero');
assert.equal(vision.levl[hero.ux][hero.uy],lifecycle.context.levl[hero.ux][hero.uy],'visibility and movement use the same map cell');
const marker={nativeVisibilityCaller:true};
withCEnvironment(marker,()=>{owner.functions.get('get_viz_clear')(1,1);assert.equal(C,marker,'native visibility retains caller context');});
for(const provider of owner.providers){const read=provider.get('struct you');if(read)assert.equal(read(hero.address),hero);}
const recalc=vision.gv.vision_full_recalc;
owner.enter();
assert.equal(lifecycle.context.gv.vision_full_recalc,recalc);
vision.gv.vision_full_recalc=recalc?0:1;
assert.equal(lifecycle.context.gv.vision_full_recalc,recalc?0:1,'different global projections observe a native visibility write immediately');
lifecycle.context.gv.vision_full_recalc=recalc;
assert.equal(vision.gv.vision_full_recalc,recalc,'visibility sees a pending write through another native projection');
owner.leave();
let monsters=0;
for(const[key,monster]of owner.records){
 if(!key.startsWith('struct monst:'))continue;
 assert.equal(lifecycle.context.monster(monster.address),monster,'lifecycle keeps the shared identity');
 assert.equal(vision.view('monst',monster.address),monster,'visibility keeps the canonical monster');
 for(const provider of owner.providers){const read=provider.get('struct monst');if(read)assert.equal(read(monster.address),monster,'movement and lifecycle retain the same object');}
 // Includes retained dead/freed records: live fields must still read their byte
 // backing outside native execution, matching the established view contract.
 const hp=environment.memory.view.getInt32(Number(monster.address)+layouts.mon.mon_mhp,true);
 assert.equal(monster.mhp,hp);monsters++;
}
assert.ok(monsters>0);assert.ok(owner.nativeArena||owner.hits>0);
console.log(JSON.stringify({passed:true,monsters,nativeFunctions:owner.functions.size,nativeFields:owner.fields,nativeStorage:owner.nativeArena?'typed-arrays':'cached-fields',cachedReads:owner.hits,legacyBoundaries:owner.boundaries,moves:result.state.moves}));
