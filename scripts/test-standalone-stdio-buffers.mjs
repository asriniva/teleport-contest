import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
const directory=path.resolve(process.env.STANDALONE_WINDOW_STARTUP_ORACLE||'.cache/standalone-window-startup-v8');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const ref=await factory();let checks=0;
for(const mode of [0,1,2])for(const size of [0,1,7,8,9,16,1024])for(const useSetbuf of size===1024?[0,1]:[0]){
 const env=createStandaloneEnvironment(),io=env.enableStdio(),{memory,filesystem}=env;
 const file=io.fopen('/stdio-buffer','w+'),bytes=memory.malloc(size+32);memory.memset(bytes,0xa5,size+32);
 const cBytes=Number(ref._probe_buffer_open(mode,BigInt(size),useSetbuf));
 if(useSetbuf)io.setbuf(file,bytes+16);else assert.equal(io.setvbuf(file,bytes+16,mode,size),0);
 const label=`mode=${mode} size=${size} setbuf=${useSetbuf}`;
 function compare(phase){
  assert.deepEqual(memory.readBytes(bytes,size+32),ref.HEAPU8.slice(cBytes,cBytes+size+32),label+' caller buffer '+phase);checks++;
  assert.deepEqual(filesystem.readFile('/stdio-buffer'),new Uint8Array(ref.FS.readFile('/stdio-buffer')),label+' visible file '+phase);checks++;
  assert.equal(io.__fbufsize(file),Number(ref._probe_buffer_capacity()),label+' buffer capacity '+phase);checks++;
  assert.equal(io.__fpending(file),Number(ref._probe_buffer_pending()),label+' pending '+phase);checks++;
 }
 compare('fresh');
 const capacity=Number(ref._probe_buffer_capacity());
 for(let i=0;i<capacity+2;i++)assert.equal(io.fputc(65+i%26,file),ref._probe_buffer_put(65+i%26),label+' put '+i);
 compare('full and overflow');
 for(const text of ['before\nmid\nend','x'.repeat(capacity+1),'\n','tail']){
  const data=Buffer.from(text),p=memory.malloc(data.length),cp=ref._malloc(BigInt(data.length));memory.HEAPU8.set(data,p);ref.HEAPU8.set(data,Number(cp));
  assert.equal(io.fwrite(p,1,data.length,file),Number(ref._probe_buffer_write(BigInt(cp),BigInt(data.length))),label+' fwrite');checks++;
  compare('write '+data.length);memory.free(p);ref._free(BigInt(cp));
 }
 assert.equal(io.fflush(file),ref._probe_buffer_flush());compare('flushed');
 assert.equal(io.fclose(file),0);ref._probe_buffer_close();memory.free(bytes);
}
console.log(`PASS: ${checks} original-C caller-buffer, capacity, pending, full-buffer/overflow, newline and flush comparisons.`);
