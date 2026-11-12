// Negative tests: denied capability access must fail even if a fixture catches it.
import assert from 'node:assert/strict';
import {withoutWasm,environment,probeModule} from './pure-js-probes/common.mjs';
for(const name of ['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest']){
 const before=Object.getOwnPropertyDescriptor(globalThis,name);
 assert.throws(()=>withoutWasm(()=>globalThis[name]),/forbidden capability/i);
 assert.throws(()=>withoutWasm(()=>{try{void globalThis[name];}catch{}}),/attempted a forbidden capability/);
 await assert.rejects(withoutWasm(async()=>{try{void globalThis[name];}catch{}}),/attempted a forbidden capability/);
 assert.deepEqual(Object.getOwnPropertyDescriptor(globalThis,name),before);
}
await assert.rejects(withoutWasm(()=>import('data:text/javascript,export default WebAssembly;')),/forbidden capability/i);
const env=await environment(),module=probeModule(env,{_probe_bad(){try{void WebAssembly;}catch{}}});
assert.throws(()=>module._probe_bad(),/attempted a forbidden capability/);
const stack=module._probe_stack(),mark=env.transport.stackSave();
env.transport.stackAlloc(16);assert.equal(module._probe_stack(),stack+1);
env.transport.stackRestore(mark);assert.equal(module._probe_stack(),stack);
console.log('Pure-JS probe isolation: denied imports/calls, swallowed attempts, restoration and real stack-depth observation checked.');
