// Live-main ownership and direct-dispatch checks, beyond isolated provider tests.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {enableMonsterLifecycle} from '../js/nethack/monster-lifecycle.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
const reference='.cache/full-original-c-v1';
const input=JSON.parse(fs.readFileSync(reference+'/scenarios/death.json'));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
let runtime;
const result=runStandaloneProgram(reference+'/assets',{...input,keys:input.keys.slice(0,256),observeRuntime:r=>{runtime=r;}});
assert.deepEqual(result.status,{kind:'input-exhausted'});
const {environment}=runtime,owner=nativeStateFor(environment);
assert.equal(owner.depth,0,'input exhaustion publishes the entire connected native graph');
assert.equal(owner.dirty.size,0);
for(const name of ['movemon','mcalcdistress','healmon','mfndpos','dochugw','m_move']){
 assert.ok(owner.functions.has(name),name+' has native dispatch');
 assert.equal(owner.functions.get(name).nativeState,owner,name+' uses the common native owner');
}
const lifecycle=enableMonsterLifecycle(environment,layouts);
let monsters=0;
for(const[key,monster]of owner.records){
 if(!key.startsWith('struct monst:'))continue;
 assert.equal(lifecycle.context.monster(monster.address),monster,'lifecycle keeps the shared identity');
 for(const provider of owner.providers){const read=provider.get('struct monst');if(read)assert.equal(read(monster.address),monster,'movement and lifecycle retain the same object');}
 // Includes retained dead/freed records: live fields must still read their byte
 // backing outside native execution, matching the established view contract.
 const hp=environment.memory.view.getInt32(Number(monster.address)+layouts.mon.mon_mhp,true);
 assert.equal(monster.mhp,hp);monsters++;
}
assert.ok(monsters>0);assert.ok(owner.hits>0);
console.log(JSON.stringify({passed:true,monsters,nativeFunctions:owner.functions.size,nativeFields:owner.fields,cachedReads:owner.hits,legacyBoundaries:owner.boundaries,moves:result.state.moves}));
