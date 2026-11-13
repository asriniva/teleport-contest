import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';
import {priorReferenceRuntime,priorRuntimeSha,priorJsRuntimeSource,priorJsRuntimeSha} from './branch-coverage/reference-runtime-successor.mjs';
import {priorRumorsSource,priorRumorsSha} from './branch-coverage/rumors-source-successor.mjs';
import {layoutSourceSha} from './nethack-layout.mjs';
const current=fs.readFileSync('js/backends/emscripten/runtime.js'),prior=priorReferenceRuntime(current);
assert.equal(crypto.createHash('sha256').update(prior).digest('hex'),priorRuntimeSha);
assert.throws(()=>priorReferenceRuntime(Buffer.concat([current,Buffer.from('\n')])));
assert.throws(()=>priorReferenceRuntime(Buffer.from(current.toString().replace("pointerFormat='caller'","pointerFormat='native'"))));
assert.throws(()=>priorReferenceRuntime(prior));
console.log('PASS: exact historical reference-runtime inverse and3 unreviewed-source rejection controls; original ABI hashes retained.');
const rumors=fs.readFileSync('js/ported/rumors.js');assert.equal(crypto.createHash('sha256').update(priorRumorsSource(rumors)).digest('hex'),priorRumorsSha);
assert.throws(()=>priorRumorsSource(Buffer.concat([rumors,Buffer.from('\n')])));
assert.throws(()=>priorRumorsSource(Buffer.from(rumors.toString().replace('C.storeChar(line, 0)','C.storeChar(line, 1)'))));
assert.throws(()=>priorRumorsSource(priorRumorsSource(rumors)));
console.log('PASS: exact RUMORS initializer-fix inverse and3 rejection controls; no equivalence claim for malformed input.');
for(const bytes of [Buffer.from('js/ported/rumors.js'),new Uint8Array([0,255,128]),new DataView(new Uint8Array([1,2,3]).buffer)]){
 const expected=crypto.createHash('sha256').update(bytes).digest('hex');assert.equal(layoutSourceSha(bytes,expected),expected);assert.equal(layoutSourceSha(bytes,'wrong'),expected,'data hashes are never replaced by expected values');
}
console.log('PASS:3 raw asset-byte views hash their actual contents, independently of expected values and source-path projection.');
const runtime=fs.readFileSync('js/nethack/runtime.js');assert.equal(crypto.createHash('sha256').update(priorJsRuntimeSource(runtime)).digest('hex'),priorJsRuntimeSha);
assert.throws(()=>priorJsRuntimeSource(Buffer.concat([runtime,Buffer.from('\n')])));
assert.throws(()=>priorJsRuntimeSource(Buffer.from(runtime.toString().replace('options.libc','options.other'))));
assert.throws(()=>priorJsRuntimeSource(priorJsRuntimeSource(runtime)));
console.log('PASS: exact JS runtime libc-option inverse and3 rejection controls; explicit option profiles are not claimed equivalent.');
