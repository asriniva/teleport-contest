// Exercise a browser which supports resizable heaps but rejects such buffers
// at TextDecoder's Web-IDL boundary. Native Node decoding supplies expected text.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {registerHooks} from 'node:module';
const NativeDecoder=globalThis.TextDecoder,originalProcess=globalThis.process;
let decoderCalls=0;
class FixedBufferDecoder extends NativeDecoder{
 decode(bytes,...args){decoderCalls++;if(bytes?.buffer?.resizable)throw new TypeError('TextDecoder input cannot use a resizable ArrayBuffer');return super.decode(bytes,...args);}
}
// Demonstrate the actual input which the old readSdkUtf8 sent to this API.
const rab=new ArrayBuffer(128,{maxByteLength:1024}),view=new Uint8Array(rab);view.set(new TextEncoder().encode('/long/configuration/path/.nethackrc'));
assert.throws(()=>new FixedBufferDecoder().decode(view.subarray(0,35)),/resizable/);
const session=JSON.parse(fs.readFileSync('sessions/seed0013-friday13-save-then-fullmoon-restore.session.json'));
const hook=registerHooks({resolve(specifier,context,next){assert.ok(!specifier.startsWith('node:'),'Browser path imported '+specifier);return next(specifier,context);}});
let checks=1;
try{
 globalThis.TextDecoder=FixedBufferDecoder;delete globalThis.process;
 const {readSdkUtf8}=await import('../js/c-runtime/stdio.js'),{CMemory}=await import('../js/c-runtime/heap.js');
 const expected=new NativeDecoder();
 for(const resizable of [false,true]){
  const memory=new CMemory({initialBytes:128,maximumBytes:16384,resizable}),p=memory.malloc(64);
  assert.equal(Boolean(memory.buffer.resizable),resizable);checks++;
  const payloads=[new TextEncoder().encode('/long/configuration/path/.nethackrc'),new TextEncoder().encode('/長い名前/équipement/🦄.nethackrc'),Uint8Array.from([0xef,0xbb,0xbf,...new TextEncoder().encode('long-bom-configuration-path')]),Uint8Array.from([...new TextEncoder().encode('long-invalid-utf8-path-'),0xf0,0x80,0xff])];
  for(const bytes of payloads){memory.HEAPU8.fill(0,p,p+64);memory.HEAPU8.set(bytes,p);assert.equal(readSdkUtf8(memory,p),expected.decode(bytes));checks++;memory.malloc(256);assert.equal(readSdkUtf8(memory,BigInt(p)),expected.decode(bytes));checks++;}
  assert.equal(readSdkUtf8(memory,0),'');checks++;
  assert.equal(readSdkUtf8(memory,'native text'),'native text');checks++;
  memory.HEAPU8.fill(0,p,p+64);memory.HEAPU8.set(new TextEncoder().encode('short'),p);const before=decoderCalls;assert.equal(readSdkUtf8(memory,p),'short');assert.equal(decoderCalls,before,'SDK small-string path retained');checks+=2;
 }
 const {runSegment}=await import('../js/standalone-recorder-adapter.js');
 const rows=new Map(),storage={getItem:k=>rows.get(k)??null,setItem:(k,v)=>rows.set(k,String(v)),removeItem:k=>rows.delete(k),get length(){return rows.size;},key:i=>[...rows.keys()][i]??null};
 for(const segment of session.segments){
  const result=await runSegment({...segment,storage});
  assert.deepEqual(result.getScreens(),segment.steps.map(step=>step.screen));checks++;
  assert.deepEqual(result.getCursors(),segment.steps.map(step=>step.cursor));checks++;
  assert.deepEqual(result.getRngLog(),segment.steps.flatMap(step=>step.rng??[]));checks++;
 }
 assert.ok(rows.has('vfs:/teleport-standalone-state.json'));checks++;
}finally{hook.deregister();globalThis.TextDecoder=NativeDecoder;globalThis.process=originalProcess;}
console.log(JSON.stringify({passed:true,checks,segments:session.segments.length,resizableDecoderInputsAllowed:false,nodeImportsAllowed:false,processAvailable:false,decoderCalls}));
