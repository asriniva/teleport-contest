import assert from 'node:assert/strict';
import {CMemory} from '../js/services/c-memory.js';
import {address,createMemoryServices} from '../js/c-runtime/memory.js';
import {createMemoryServices as createStandaloneMemoryServices} from '../js/standalone/memory-services.js';

const memory=new CMemory({initialBytes:128,maximumBytes:1024*1024});
const C=createMemoryServices(memory);
assert.equal(C.coordxy,undefined);assert.equal(C.boolean,undefined);
const compatibility=createStandaloneMemoryServices(memory);
assert.equal(compatibility.coordxy,compatibility.short);
assert.equal(compatibility.boolean,compatibility.char);
C.defineRecord('point',{size:4,fields:{x:{offset:0,type:'Int16'},y:{offset:2,type:'Int16'}}});
const point=C.recordType('point'),at=memory.malloc(8),items=point.array(at,2);
items[0].x=65535;items[0].y=7;
assert.equal(items[0].x,-1);
assert.equal(point.view(at),items[0]);
items[1]=items[0];items[0].y=9;
assert.equal(items[1].y,7); // Struct assignment copies rather than aliases.
assert.equal(compatibility.read('Int16',at),-1);
assert.equal(address(items[0]),at);
assert.throws(()=>items[2],/bounds/);
const live=memory.live.size;
C.scoped(()=>{
    const local=point.local(items[0]);
    local.y=22;assert.equal(items[0].y,9);
    const before=memory.buffer;
    memory.malloc(4096);assert.notEqual(memory.buffer,before);
    assert.equal(local.y,22);assert.equal(items[0].x,-1);
    const innerMark=C.stackSave();
    const inner=point.local({x:32768,y:65536});
    assert.equal(inner.x,-32768);assert.equal(inner.y,0);
    C.stackRestore(innerMark);
    assert.ok(!memory.live.has(inner.address));
    assert.ok(memory.live.has(local.address));
});
assert.equal(memory.live.size,live+1); // Only the explicit growth allocation remains.
assert.throws(()=>C.scoped(()=>{point.local();throw new Error('unwind');}),/unwind/);
assert.equal(memory.live.size,live+1);
// An uninitialized local must reserve bytes without adding zero stores.
C.scoped(()=>{
    const mark=C.stackSave(),seeded=point.local({x:123,y:-456}),saved=seeded.address;
    C.stackRestore(mark);
    const uninitialized=point.local();
    assert.equal(uninitialized.address,saved);
    assert.deepEqual([uninitialized.x,uninitialized.y],[123,-456]);
});
const second=createMemoryServices(new CMemory());
assert.throws(()=>second.recordType('point'),/Missing measured/);
assert.throws(()=>C.recordType('missing'),/Missing measured/);
console.log('PASS: shared C record copying/aliasing, narrowing, growth, scoped lifetimes, uninitialized reservation, instance isolation and compatibility aliases.');
