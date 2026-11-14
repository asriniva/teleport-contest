import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createNativeRecordViews} from '../js/nethack/native/record-views.js';
import {nativeStateLinksFor} from '../js/nethack/native/state-links.js';
function game(){const env=createStandaloneEnvironment(),views=createNativeRecordViews(env);return {env,views,links:nativeStateLinksFor(env)};}
const a=game(),b=game(),{env,views,links}=a,at=env.memory.calloc(1,env.ctypes.size('struct monst')),mon=views.record('struct monst',at),otherAt=env.memory.calloc(1,env.ctypes.size('struct monst')),other=views.record('struct monst',otherAt);
const ref=links.record(mon,'nmon');assert.equal(links.record(mon,'nmon'),ref);assert.equal(ref.value,0);ref.value=other;assert.equal(mon.nmon,other);assert.equal(ref.value,other);assert.ok(links.owns(ref));assert.equal(b.links.owns(ref),false);assert.equal(links.owns({value:mon}),false);
const address=ref.address;assert.equal(env.memory.view.getBigUint64(address,true),BigInt(otherAt));env.memory.view.setBigUint64(address,BigInt(at),true);assert.equal(ref.value,mon,'foreign alias updates canonical reference');
const before=env.memory.live.size,head=links.private('test.native.private.head','struct monst');head.value=other;assert.equal(head.value,other);assert.equal(env.memory.live.size,before,'private JS head has no C allocation');
const p=head.address;assert.equal(head.address,p);assert.equal(env.memory.view.getBigUint64(p,true),BigInt(otherAt));head.value=mon;assert.equal(env.memory.view.getBigUint64(p,true),BigInt(at));env.memory.view.setBigUint64(p,0n,true);assert.equal(head.value,0);
env.memory.grow(env.memory.buffer.byteLength+65536);head.value=other;assert.equal(head.value,other);assert.equal(ref.value,mon,'record links survive growth');
const ownHead=b.links.private('test.native.private.head','struct monst');assert.equal(ownHead.value,0,'other game has a separate private head');assert.equal(b.links.owns(head),false);
assert.throws(()=>links.record(mon,'mhp'),/pointer field/);
console.log(JSON.stringify({passed:true,canonicalIdentity:true,sharedMutation:true,foreignAlias:true,noPrematureAllocation:true,privateWriteback:true,heapGrowth:true,perGameIsolation:true}));
