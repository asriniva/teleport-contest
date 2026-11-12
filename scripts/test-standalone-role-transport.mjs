import {layoutSourceSha} from './nethack-layout.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_ROLE_TRANSPORT_ORACLE||'.cache/standalone-unix-platform-v6');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed C source '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.makemon,M=layouts.mkobj;
const metadata=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;

let comparisons=0;
function snapshot(heap,at,type,count=1){
 at=Number(at);const record=metadata[type],bytes=Buffer.from(heap.slice(at,at+record.size*count)),strings={};
 function walk(type,offset,label){for(const [name,f]of Object.entries(metadata[type].fields)){
  const arr=f.ctype.match(/\[(\d+)\]/),n=arr?Number(arr[1]):1,child=f.record||f.ctype.match(/struct (\w+)/)?.[1];
  if(f.ctype.includes('*'))for(let i=0;i<n;i++){
   const pos=offset+f.offset+i*8,p=Number(bytes.readBigUInt64LE(pos));
   if(/char\s*\*/.test(f.ctype)){let end=p;if(p){while(heap[end])end++;strings[label+'.'+name+'['+i+']']=Buffer.from(heap.slice(p,end)).toString('latin1');}else strings[label+'.'+name+'['+i+']']=null;}
   else assert.equal(p,0,'Unmodeled non-string pointer '+label+'.'+name);
   bytes.writeBigUInt64LE(p?1n:0n,pos);
  }else if(child&&metadata[child])for(let i=0;i<n;i++)walk(child,offset+f.offset+i*metadata[child].size,label+'.'+name+'['+i+']');
 }}
 for(let i=0;i<count;i++)walk(type,i*record.size,type+'['+i+']');return {bytes,strings};
}

const seed=1n;
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}});
 env.enableStdio();env.enableDecl(layouts.decl);env.call('decl','program_state_init');env.call('decl','decl_globals_init');env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);const group=env.enableMonsterSelection(layouts);const decl=JSON.parse(fs.readFileSync('js/nethack/decl-storage.json')).globals,before=decl.map(r=>env.memory.readBytes(env.requireGlobal(r.name),r.bytes));const creation=env.enableMonsterCreation(layouts);decl.forEach((r,i)=>assert.deepEqual(env.memory.readBytes(env.requireGlobal(r.name),r.bytes),before[i],'enabling creation preserves '+r.name));

 const startup=env.enableGameStartup(layouts);env.call('sys','sys_early_init');
 const errors=[];const ref=await factory({printErr:s=>errors.push(s)});ref._probe_startup_init(seed);

const text=(heap,p)=>{p=Number(p);let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');};
const cLiteral=s=>{const p=BigInt(ref._malloc(BigInt(Buffer.byteLength(s)+1)));ref.HEAPU8.set(Buffer.from(s+'\0'),Number(p));return p;};
for(const [name,values]of [['str2role',['','Archeologist','arc','Wizard','Priestess','@','random','invalid']],['str2race',['','human','elf','orc','random','invalid']],['str2gend',['','male','female','neuter','random','invalid']],['str2align',['','lawful','neutral','chaotic','random','invalid']]])for(const value of values){const p=cLiteral(value);assert.equal(env.services[name](env.services.literal(value)),ref['_'+name](p),'Original checked ROLE string lookup '+name+' '+value);ref._free(p);comparisons++;}
const size=layouts.role.QBUFSZ,jbuf=env.memory.calloc(1,size),cbuf=BigInt(ref._malloc(BigInt(size)));
for(const name of ['root_plselection_prompt','build_plselection_prompt'])for(const config of [...Array.from({length:13},(_,r)=>[r,0,0,0]),[-1,-1,-1,-1],[-2,-2,-2,-2],[0,0,-1,-1],[12,0,1,-1]])for(const length of [1,20,size]){
 env.memory.HEAPU8.fill(0,jbuf,jbuf+size);ref.HEAPU8.fill(0,Number(cbuf),Number(cbuf)+size);
 const result=env.services[name](jbuf,length,...config),expected=ref['_'+name](cbuf,length,...config);
 assert.equal(typeof result==='string'?result:text(env.memory.HEAPU8,result),text(ref.HEAPU8,expected),'Original ROLE prompt '+name+' '+config+' length'+length);comparisons++;
 assert.deepEqual(Buffer.from(env.memory.readBytes(jbuf,size)),Buffer.from(ref.HEAPU8.slice(Number(cbuf),Number(cbuf)+size)),'Original supplied prompt buffer');comparisons++;
}
env.memory.free(jbuf);ref._free(cbuf);
assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
console.log('PASS: '+comparisons+' original-C ROLE checked-string and prompt transport comparisons; full interactive selection/menu recordings remain pending.');
