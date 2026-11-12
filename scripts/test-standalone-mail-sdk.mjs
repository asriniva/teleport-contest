import {layoutSourceSha} from './nethack-layout.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{pathToFileURL}from'node:url';
import{createStandaloneEnvironment}from'../js/nethack/environment.js';
import{connectMailSdk}from'../js/nethack/mail.js';
const directory=path.resolve(process.env.STANDALONE_MAIL_SDK_ORACLE||'.cache/standalone-mail-sdk-v1'),receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const[p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed SDK source '+p);
for(const[p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed SDK oracle '+p);
const{default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs'))),ref=await factory({print:()=>{},printErr:()=>{}}),env=createStandaloneEnvironment(),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
connectMailSdk(env);let checks=0;
function jsCall(name,...args){const names=['WebAssembly','fetch','XMLHttpRequest'],saved=names.map(n=>[n,Object.getOwnPropertyDescriptor(globalThis,n)]),forbidden=()=>{throw Error('Wasm/network forbidden in SDK replacement');};Object.defineProperty(globalThis,'WebAssembly',{configurable:true,value:new Proxy({},{get:forbidden})});for(const n of names.slice(1))Object.defineProperty(globalThis,n,{configurable:true,value:forbidden});try{return env.services[name](...args);}finally{for(const[n,d]of saved)if(d)Object.defineProperty(globalThis,n,d);else delete globalThis[n];}}
assert.equal(Number(ref._probe_passwd_layout(1)),layouts.mail.passwd_pw_name);assert.equal(Number(ref._probe_passwd_layout(0)),48);assert.equal(layouts.mail.pointerSize,8);checks+=3;
for(const contents of [null,'root:x:0:0:Root:/root:/bin/sh\nada:x:1000:100:Player:/home/ada:/bin/false\n']){
 if(contents!==null){ref.FS.mkdirTree('/etc');ref.FS.writeFile('/etc/passwd',contents);env.filesystem.mkdirTree('/etc');env.filesystem.writeFile('/etc/passwd',Buffer.from(contents));}
 for(const uid of [0,1000,999,4294967295n,4294967296n]){
  env.libc.errno=73;ref._probe_errno(73);const actual=jsCall('getpwuid',uid),expected=ref._probe_getpwuid(env.transport.uint(uid));assert.equal(BigInt(actual),BigInt(expected),'Actual linked SDK passwd lookup');assert.equal(env.libc.errno,ref._probe_errno(73),'Actual SDK passwd errno');assert.equal(actual,0,'SDK has no virtual passwd account');checks+=3;
 }
}
for(const errno of [0,44,73]){env.libc.errno=errno;ref._probe_errno(errno);assert.equal(jsCall('fork'),ref._probe_fork(),'Actual SDK fork failure');assert.equal(env.libc.errno,ref._probe_errno(errno),'Actual SDK fork errno');checks+=2;}
for(const value of ['/missing','/bin/mail','',null]){
 const jp=value===null?0:env.services.literal(value),cp=value===null?0n:BigInt(ref._malloc(BigInt(Buffer.byteLength(value)+1)));if(cp)ref.HEAPU8.set(Buffer.from(value+'\0'),Number(cp));env.libc.errno=73;ref._probe_errno(73);assert.equal(jsCall('execl',jp,jp,0),ref._probe_execl(cp),'Actual SDK exec failure');assert.equal(env.libc.errno,ref._probe_errno(73),'Actual SDK exec errno');if(cp)ref._free(cp);checks+=2;
}
console.log('PASS: '+checks+' pinned original-SDK passwd/fork/exec comparisons; MAIL delivery/gameplay acceptance remains separate.');
