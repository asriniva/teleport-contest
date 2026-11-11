import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {callHack,createHackEnvironment} from '../js/ported/hack-runtime.js';
import {C,withCEnvironment} from '../js/ported/c-runtime.js';

const layouts=JSON.parse(await readFile(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const layout=Object.freeze({...layouts.hack}),moduleKey={};
let heap=new Uint8Array(65536),constructions=0,stack=128;
const services={moduleKey,heap:()=>heap,inRoomsBuffer(){constructions++;return 32;},
    stackSave:()=>stack,stackRestore:s=>{stack=s;},stackAlloc:n=>{const at=stack;stack+=n;return at;}};
for(let i=0;i<20;i++)assert.equal(callHack(services,layout,'rounddiv',7n,2),4);
assert.equal(constructions,1,'one validated environment for sequential calls');

const failure=new Error('outer panic'),outer={marker:true};
let innerCalls=0;
const overridden={...services,panic_p(){
    const environment=C;
    assert.equal(callHack({...services},layout,'rounddiv',-7n,2),-4);
    innerCalls++;
    assert.equal(C,environment,'nested call restores the outer lexical environment');
    throw failure;
}};
withCEnvironment(outer,()=>{
    assert.throws(()=>callHack(overridden,layout,'rounddiv',1n,0),e=>e===failure);
    assert.equal(C,outer);
});
assert.equal(innerCalls,1);assert.equal(constructions,2,'nested call owns a second frame');
assert.equal(C,undefined);assert.equal(stack,128);
const otherFailure=new Error('replacement service');
assert.throws(()=>callHack({...services,panic_p(){throw otherFailure;}},layout,'rounddiv',1n,0),e=>e===otherFailure);
assert.equal(constructions,2,'exception releases the cached frame');
assert.equal(callHack(services,layout,'rounddiv',3n,2),2);
assert.equal(callHack({...services,moduleKey:{}},layout,'rounddiv',3n,2),2);
assert.equal(constructions,3,'modules never share environments');

const env=createHackEnvironment(services,layout);
for(const type of ['char','unsigned char','short','unsigned short','int','unsigned int']){
    const values=env.localArray(type,[2,4]),descriptor=values[0].descriptor.e;
    const bits=Number(descriptor.t.slice(1)),signed=descriptor.t[0]==='i';
    for(const input of [-2147483649,-32769,-129,-1,0,127,255,32768,4294967295]){
        values[1][2]=input;
        assert.equal(values[1][2],Number((signed?BigInt.asIntN:BigInt.asUintN)(bits,BigInt(input))));
    }
    const replacement=new Uint8Array(heap.length*2);replacement.set(heap);heap=replacement;
    values[1][2]=42;assert.equal(values[1][2],42,'existing array refreshes after heap replacement');
    assert.equal(new DataView(heap.buffer).getUint8(values[1].address+2*bits/8),42);
}
const mutable={...layout};
callHack(services,mutable,'rounddiv',3n,2);
mutable.pointerSize=4;
assert.throws(()=>callHack(services,mutable,'rounddiv',3n,2),/changed HACK ABI/);
assert.throws(()=>callHack(services,Object.freeze({...layout,width_obj_otyp:4}),'rounddiv',3n,2),/field width/);
assert.equal(stack,128+2*4*(1+1+2+2+4+4));
console.log('HACK runtime reuse: module/frame isolation, service replacement, exception cleanup, mutable-layout validation, signed arrays and heap replacement PASS');
