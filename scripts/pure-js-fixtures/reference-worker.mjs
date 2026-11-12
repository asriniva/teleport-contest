// This is the ORIGINAL-C reference process. It is never imported by the JS IUT.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {createMkobjEnvironment} from '../../js/nethack/bindings/mkobj.js';
import * as mkobjCore from '../../js/ported/mkobj.js';
import {createCmdEnvironment} from '../../js/nethack/bindings/cmd.js';
import * as cmdCore from '../../js/ported/cmd.js';
import {channel} from './reference-channel.mjs';
import {createPortedRuntime} from '../../js/backends/emscripten/runtime.js';
const [directory,url]=process.argv.slice(2),rpc=channel(fs.openSync(directory+'/requests','r+'),fs.openSync(directory+'/responses','r+'));
let module;const events=[],configuration=rpc.receive();
const revive=value=>{if(value?.referenceCallback)return (...args)=>{rpc.send({callback:value.referenceCallback,args});let reply=rpc.receive();while(reply.op||reply.key){respond(reply);reply=rpc.receive();}if(Object.hasOwn(reply,'error')){if(reply.errno!==undefined)throw new module.FS.ErrnoError(reply.errno);throw Error(reply.error);}return reply.value;};if(Array.isArray(value))return value.map(revive);return value;};
try{
 const layouts=JSON.parse(fs.readFileSync(new URL('../../js/wasm/tu-layouts.json',import.meta.url)));
 module=await (await import(url)).default({...Object.fromEntries(Object.entries(configuration.stdio??{}).filter(([,v])=>v).map(([k,v])=>[k,revive(v)])),thisProgram:configuration.thisProgram,preRun:[m=>{if(Object.keys(configuration.initial).length)Object.assign(m.ENV,configuration.initial);for(const {key,args}of configuration.operations)m.FS[key](...args);}],nethackPorted:createPortedRuntime(layouts),onExit:value=>events.push(['onExit',value]),print:value=>events.push(['print',value]),printErr:value=>events.push(['printErr',value])});
 rpc.send({keys:Object.keys(module).filter(k=>typeof module[k]==='function'),bytes:module.HEAPU8.byteLength,events:events.splice(0)});
}catch(error){rpc.send({error:error.stack});process.exit(1);}
function respond(request){
 if(request.op==='shutdown')process.exit(0);
 try{
  let value;
  if(request.op==='observe')value=new Function('m','context','createMkobjEnvironment','core','Buffer','DataView','assert','createCmdEnvironment','cmdCore',request.source)(module,request.context,createMkobjEnvironment,mkobjCore,Buffer,DataView,assert,createCmdEnvironment,cmdCore);
  else if(request.op==='env')module.ENV[request.key]=request.value;
  else if(request.op==='setModule')module[request.key]=revive(request.value);
  else if(request.op==='writeBatch'){for(const {at,bytes}of request.writes)module.HEAPU8.set(bytes,at);}
  else if(request.op==='read')value=module.HEAPU8.slice(request.at,request.at+request.n);
  else if(request.op==='write')module.HEAPU8.set(request.bytes,request.at);
  else if(request.op==='fs'){value=module.FS[request.key](...revive(request.args));if(request.key==='createDevice')value=undefined;if(request.key==='analyzePath'){const {exists,error,path,name}=value;value={exists,error,path,name};}}
  else value=module[request.key](...request.args);
  rpc.send({value,bytes:module.HEAPU8.byteLength,events:events.splice(0)});
 }catch(error){rpc.send({error:error.message,name:error.name,errno:error.errno,code:error.code,status:error.status,bytes:module.HEAPU8.byteLength,events:events.splice(0)});}
}
while(true)respond(rpc.receive());
