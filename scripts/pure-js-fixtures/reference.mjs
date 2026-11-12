// Original C executes in a separate process. This process exposes only reference
// observations; the JS implementation cannot load its binary or call its helpers.
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {spawn,execFileSync} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import {channel} from './reference-channel.mjs';
const registry=JSON.parse(fs.readFileSync(new URL('../../nethack-c/wasm/tu-ports.json',import.meta.url)));
const registered=new Set(registry.map(p=>p.name)),typedOwners=new Set();
for(const port of registry)for(const file of port.adapterSources??[])if(/\.(?:c|inc)$/.test(file)){
 const source=fs.readFileSync(new URL('../../'+file,import.meta.url),'utf8');
 for(const match of source.matchAll(/\buint64_t\s+teleport_(\w+)_read\s*\(\s*int\s+\w+\s*,\s*(?:const\s+)?void\s*\*\s*\w+\s*,\s*int\s+\w+\s*\)\s*\{/g))if(registered.has(match[1]))typedOwners.add(match[1]);
}
export function isReferenceGetter(name,key){const m=key.match(/^_teleport_(.+)_(address|global|read|layout|literal_storage|literal_capacity)$/);return Boolean(m&&typedOwners.has(m[1]))||name==='mkobj'&&/^_probe_(?:pool|block|block_count|block_size|block_live|string|string_count|string_capacity)$/.test(key);}
const resources=new Set();
function dispose(resource){if(!resources.delete(resource))return;resource.child.ref();try{resource.rpc.send({op:'shutdown'});}catch{resource.child.kill('SIGTERM');}for(const fd of [resource.input,resource.output])try{fs.closeSync(fd);}catch{}fs.rmSync(resource.directory,{recursive:true,force:true});}
const retired=new FinalizationRegistry(dispose);
process.once('beforeExit',()=>{for(const resource of resources)dispose(resource);});
process.once('exit',()=>{for(const resource of resources)dispose(resource);});
const numeric=k=>typeof k==='string'&&/^\d+$/.test(k)?Number(k):null;
export default async function referenceFactory(name,url=new URL(`../../.cache/tu-probes/${name}-reference.mjs`,import.meta.url),options={}){
 await new Promise(resolve=>setImmediate(resolve));
 const directory=fs.mkdtempSync(path.join(os.tmpdir(),'nethack-c-reference-'));
 execFileSync('mkfifo',[directory+'/requests',directory+'/responses']);
 const flags=fs.constants.O_RDWR|fs.constants.O_NONBLOCK;
 const input=fs.openSync(directory+'/responses',flags),output=fs.openSync(directory+'/requests',flags),rpc=channel(input,output);
 const child=spawn(process.execPath,[fileURLToPath(new URL('./reference-worker.mjs',import.meta.url)),directory,String(url)],{stdio:['ignore','ignore','ignore']});child.unref();
 const resource={child,input,output,directory,rpc};resources.add(resource);const lifetime={calls:0};
 const deliver=events=>{for(const[key,value]of events??[])options[key]?.(value);};
 const callbacks=new Map();let callbackSequence=0;
 const pack=value=>{if(typeof value==='function'){const id=++callbackSequence;callbacks.set(id,value);return {referenceCallback:id};}if(Array.isArray(value))return value.map(pack);return value;};
 const initial={},operations=[];for(const fn of options.preRun??[])fn({ENV:initial,FS:new Proxy({},{get:(_,key)=>(...args)=>operations.push({key,args})})});rpc.send({initial,operations,thisProgram:options.thisProgram,stdio:{stdin:pack(options.stdin),stdout:pack(options.stdout)}});
 let ready=rpc.receive();while(ready.callback){try{rpc.send({value:callbacks.get(ready.callback)(...ready.args)});}catch(error){rpc.send({error:error.message});}ready=rpc.receive();}deliver(ready.events);if(Object.hasOwn(ready,'error'))throw Error(ready.error??'Original C reference initialization failed');
 globalThis.__isolatedCReferenceInstances=(globalThis.__isolatedCReferenceInstances??0)+1;
 class ErrnoError extends Error{constructor(errno){super('FS error '+errno);this.errno=errno;}}
 let size=ready.bytes,buffer,pages=new Map();const pendingWrites=new Map(),observations=new Map();
 // Registered typed ABI getters only compute addresses/read scalar fields.
 const readOnly=key=>isReferenceGetter(name,key);
 function flushWrites(){if(!pendingWrites.size)return;const positions=[...pendingWrites.keys()].sort((a,b)=>a-b),writes=[];let at=positions[0],bytes=[],previous=at-1;for(const position of positions){if(position!==previous+1){writes.push({at,bytes:Uint8Array.from(bytes)});at=position;bytes=[];}bytes.push(pendingWrites.get(position));previous=position;}writes.push({at,bytes:Uint8Array.from(bytes)});pendingWrites.clear();request({op:'writeBatch',writes});}
 const api={_read(at,n){at=Number(at);n=Number(n);flushWrites();if(!Number.isSafeInteger(at)||!Number.isSafeInteger(n)||at<0||n<0||at+n>size)return request({op:'read',at,n});const out=new Uint8Array(n);for(let done=0;done<n;){const page=Math.floor((at+done)/4096)*4096;if(!pages.has(page))pages.set(page,request({op:'read',at:page,n:Math.min(4096,size-page)}));const bytes=pages.get(page),offset=at+done-page,count=Math.min(n-done,bytes.length-offset);out.set(bytes.subarray(offset,offset+count),done);done+=count;}return out;},_write:(at,bytes)=>{request({op:'write',at:Number(at),bytes:Buffer.from(bytes)});pages.clear();observations.clear();}};
 function update(bytes){if(bytes!==size||!buffer){size=bytes;buffer=Object.assign(new ArrayBuffer(size),{nativeAPI:api});pages.clear();}}
 function request(packet){if(packet.op!=='writeBatch')flushWrites();lifetime.calls++;rpc.send(packet);let reply=rpc.receive();while(reply.callback){pages.clear();observations.clear();try{rpc.send({value:callbacks.get(reply.callback)(...reply.args)});}catch(error){rpc.send({error:error.message,name:error.name,errno:error.errno});}reply=rpc.receive();}deliver(reply.events);if(reply.bytes)update(reply.bytes);if(Object.hasOwn(reply,'error')){const error=new Error(reply.error??'Original C reference exception');error.name=reply.name??'Error';if(reply.errno!==undefined)error.errno=reply.errno;if(reply.code!==undefined)error.code=reply.code;if(reply.status!==undefined)error.status=reply.status;throw error;}return reply.value;}
 update(size);
 const heap={get buffer(){flushWrites();return buffer;},get byteLength(){return size;},get length(){return size;},slice:(a,b)=>api._read(a,b-a),subarray:(a,b)=>api._read(a,b-a),set:(v,at=0)=>api._write(at,v),fill(v,a=0,b=size){api._write(a,Buffer.alloc(b-a,v));return proxy;},copyWithin(a,b,c){api._write(a,api._read(b,c-b));return proxy;}};
 const proxy=new Proxy(heap,{get(target,k){const at=numeric(k);if(at===null)return target[k];if(at>=size)return undefined;if(pendingWrites.has(at))return pendingWrites.get(at);const page=Math.floor(at/4096)*4096;if(!pages.has(page))pages.set(page,api._read(page,Math.min(4096,size-page)));return pages.get(page)[at-page];},set(target,k,v){const at=numeric(k);if(at===null)target[k]=v;else if(at<size){observations.clear();pendingWrites.set(at,Number(v)&255);const page=Math.floor(at/4096)*4096;if(pages.has(page))pages.get(page)[at-page]=Number(v)&255;}return true;}});
 const module={...options,ENV:new Proxy({},{set:(o,key,value)=>{request({op:'env',key,value});o[key]=value;return true;}}),isolatedCReference:true,HEAPU8:proxy,FS:new Proxy({},{get:(_,key)=>key==='ErrnoError'?ErrnoError:(...args)=>{pages.clear();observations.clear();return request({op:'fs',key,args:pack(args)});}})};
 for(const key of ready.keys)module[key]=(...args)=>{flushWrites();if(readOnly(key)){const token=key+':'+args.map(String).join(',');if(!observations.has(token))observations.set(token,request({key,args}));return observations.get(token);}pages.clear();observations.clear();try{return request({key,args});}finally{pages.clear();observations.clear();}};
 module.observe=(source,context)=>{pages.clear();observations.clear();return request({op:'observe',source,context});};
 module.referenceStatistics=()=>({calls:lifetime.calls});
 retired.register(lifetime,resource);

 return new Proxy(module,{set(target,key,value){target[key]=value;if(typeof value==='function'&&!String(key).startsWith('_'))request({op:'setModule',key,value:pack(value)});return true;}});
}
