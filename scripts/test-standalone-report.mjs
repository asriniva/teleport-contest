// Connected original early_init, REPORT fallback and NHMD4 storage acceptance.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL,fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {enableReport} from '../js/standalone/report.js';
import {C,R,T} from '../js/c-runtime/context.js';

if(!process.argv.includes('--worker')){
 const zones=process.env.STANDALONE_REPORT_ZONES?.split(',').filter(Boolean)||['UTC','America/New_York','America/Los_Angeles','Asia/Kolkata','Europe/Berlin'];assert.ok(zones.length);const results=[];
 for(const zone of zones){const worker=spawnSync(process.execPath,[fileURLToPath(import.meta.url),'--worker'],{env:{...process.env,TZ:zone},encoding:'utf8',timeout:60000,maxBuffer:8*1024*1024});assert.equal(worker.status,0,zone+': '+(worker.error||worker.stderr||worker.stdout));process.stdout.write(worker.stdout);const line=worker.stdout.split('\n').find(s=>s.startsWith('REPORT_RESULT '));assert.ok(line);results.push(JSON.parse(line.slice('REPORT_RESULT '.length)));}
 const sum=key=>results.reduce((n,row)=>n+row[key],0);console.log(`PASS: ${sum('comparisons')} original-C connected early_init/REPORT/NHMD4 comparisons, ${sum('contracts')} JS contracts, ${sum('cases')} bootstrap cases in${zones.length} runtime timezones; executable symlink hashing and process launch remain separate.`);
}else{
const directory=path.resolve(process.env.STANDALONE_REPORT_ORACLE||'.cache/standalone-report-v1');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
let hashes=0,comparisons=0,contracts=0;
for(const [p,hash]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),hash,'Changed C reference input '+p);hashes++;}
for(const [p,hash]of Object.entries(receipt.artifactSha256)){assert.equal(sha(path.join(directory,p)),hash,'Changed C reference artifact '+p);hashes++;}
assert.deepEqual(receipt.buildEnvironment,{SOURCE_DATE_EPOCH:'1777723200',TZ:'UTC'});
const records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),abi=JSON.parse(fs.readFileSync('js/standalone/runtime-info-abi.json'));
const declText=fs.readFileSync('js/nethack/bindings/decl.js','utf8'),globals=JSON.parse(declText.match(/^const globals=(.*);$/m)[1]),schemas=JSON.parse(declText.match(/^const schemas=(.*);$/m)[1]);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);comparisons++;};
function js(fn){
 const keys=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));let accesses=0;
 const forbidden=()=>{accesses++;throw new Error('Forbidden Wasm/network in standalone REPORT/bootstrap');};
 keys.forEach(k=>Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy(Object.create(null),{get:forbidden}):forbidden}));
 try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.equal(accesses,0);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);contracts+=2;}
}
function string(heap,p){p=Number(p);if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');}
const width=d=>d.p!==undefined?8:d.t?Number(d.t.slice(1))/8:d.s?schemas[d.s].size:d.a.reduce((a,b)=>a*b,1)*width(d.e);
function normalized(heap,p,d,bytes){
 p=Number(p);const data=Buffer.from(heap.slice(p,p+bytes)),strings={};
 function walk(d,offset,key){
  if(d.p!==undefined){const value=data.readBigUInt64LE(offset);strings[key]=d.p==='char'?string(heap,value):Boolean(value);data.writeBigUInt64LE(value?1n:0n,offset);}
  else if(d.s){for(const f of schemas[d.s].fields)walk(f.d,offset+f.offset,key+'.'+f.name);}
  else if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};for(let i=0;i<d.a[0];i++)walk(child,offset+i*width(child),key+'['+i+']');}
 }
 walk(d,0,'root');return{data,strings};
}
function normalizeRecord(heap,p,type,count=1){const fields=records[type],data=Buffer.from(heap.slice(Number(p),Number(p)+fields.size*count)),payloads=[];
 for(let i=0;i<count;i++)for(const f of Object.values(fields.fields))if(f.ctype.includes('*'))for(let k=0;k<Number(f.ctype.match(/\[(\d+)\]/)?.[1]||1);k++){const offset=i*fields.size+f.offset+k*8,value=data.readBigUInt64LE(offset);payloads.push(/char\s*\*/.test(f.ctype)?string(heap,value):Boolean(value));data.writeBigUInt64LE(value?1n:0n,offset);}return{data,payloads};}
function cput(ref,s){const bytes=Buffer.from(s+'\0'),p=BigInt(ref._malloc(BigInt(bytes.length)));ref.HEAPU8.set(bytes,Number(p));return p;}
function cset(ref,key,value){const k=cput(ref,key),v=value===null?0n:cput(ref,value);assert.equal(value===null?ref._unsetenv(k):ref._setenv(k,v,1),0);ref._free(k);if(v)ref._free(v);}
for(const real of [null,'','1']){
 const ref=await factory({print:()=>{},printErr:()=>{}});cset(ref,'TZ',process.env.TZ||'UTC');cset(ref,'NETHACK_REAL_BUILD_DATE',real);
 let env,group,report;
 js(()=>{const environment={TZ:process.env.TZ||'UTC'};if(real!==null)environment.NETHACK_REAL_BUILD_DATE=real;
  env=createStandaloneEnvironment({environment});env.enableStdio();env.enableDecl(layouts.decl);env.enableObjects(layouts.objects);env.enableMonst(layouts.monst);env.enableSys(layouts.sys);env.enableVersionInfo(layouts);group=env.enableRuntimeInfo(layouts);report=enableReport(env,layouts);
 });
 const cglobal=i=>Number(ref._probe_decl_global(i));
 function compare(phase){
  globals.forEach((row,i)=>equal(js(()=>normalized(env.memory.HEAPU8,env.requireGlobal(row.name),row.d,row.bytes)),normalized(ref.HEAPU8,cglobal(i),row.d,row.bytes),phase+' complete DECL '+row.name));
  for(const [name,type,count,which]of [['objects','objclass',layouts.objects.sizeof_objects/layouts.objects.objectSize,7],['mons','permonst',layouts.monst.sizeof_mons/layouts.monst.monsterSize,6]]){
   equal(js(()=>normalizeRecord(env.memory.HEAPU8,env.requireGlobal(name),type,count)),normalizeRecord(ref.HEAPU8,ref._probe_startup_global(which),type,count),phase+' full initialized '+name);
  }
  const csys=Number(ref._probe_startup_global(18));equal(js(()=>normalizeRecord(env.memory.HEAPU8,env.requireGlobal('sysopt'),'sysopt_s')),normalizeRecord(ref.HEAPU8,csys,'sysopt_s'),phase+' complete SYS state');
  const cp=Number(ref._probe_runtime_info_nomakedefs());for(const [name,f]of Object.entries(abi.date.fields)){
   const j=js(()=>env.memory.view.getBigUint64(group.nomakedefs+f.offset,true)),c=new DataView(ref.HEAPU8.buffer).getBigUint64(cp+f.offset,true);
   equal(f.kind==='pointer'?js(()=>string(env.memory.HEAPU8,j)):j,f.kind==='pointer'?string(ref.HEAPU8,c):c,phase+' DATE '+name);
  }
  group.storage.forEach((p,i)=>equal(js(()=>Buffer.from(env.memory.readBytes(p,abi.storageBytes[i]))),Buffer.from(ref.HEAPU8.slice(Number(ref._probe_runtime_info_storage(i)),Number(ref._probe_runtime_info_storage(i))+abi.storageBytes[i])),phase+' MDLIB bytes '+i));
  group.state.opttext.forEach((p,i)=>equal(js(()=>string(env.memory.HEAPU8,p)),string(ref.HEAPU8,ref._probe_runtime_info_option(i)),phase+' option '+i));
  report.storage.forEach((p,i)=>equal(js(()=>Buffer.from(env.memory.readBytes(p,i?8192:40))),Buffer.from(ref.HEAPU8.slice(Number(ref._probe_report_storage(i)),Number(ref._probe_report_storage(i))+Number(ref._probe_report_storage_size(i)))),phase+' complete REPORT buffer '+i));
  for(let i=0;i<6;i++)equal(js(()=>string(env.memory.HEAPU8,env.resolve('copyright_banner_line')(i))),string(ref.HEAPU8,ref._copyright_banner_line(i)),phase+' actual banner line '+i);
 }
 js(()=>env.resolve('early_init')(0,0));ref._early_init(0,0n);compare('first connected early_init '+JSON.stringify(real));
 assert.equal(js(()=>string(env.memory.HEAPU8,report.storage[0])),'unknown');assert.equal(report.state.once,1);contracts+=2;
 const pointers=js(()=>[...group.state.opttext,...group.storage]),cPointers=Array.from({length:abi.mdlib.MAXOPT},(_,i)=>ref._probe_runtime_info_option(i));
 js(()=>env.resolve('early_init')(0,0));ref._early_init(0,0n);compare('second connected early_init '+JSON.stringify(real));
 equal(js(()=>[...group.state.opttext,...group.storage]),pointers,'Once guard retains JS MDLIB pointers');equal(Array.from({length:abi.mdlib.MAXOPT},(_,i)=>ref._probe_runtime_info_option(i)),cPointers,'Once guard retains C MDLIB pointers');assert.equal(report.state.once,2);contracts++;
 // Exercise the actual limited filesystem's readlink errors against libc.
 for(const [p,kind,n]of [['/not-present','missing',64],['/regular','file',64],['/directory','directory',64],['/regular','file',0]]){
  if(kind==='file'){js(()=>env.filesystem.writeFile(p,new Uint8Array([1,2])));ref.FS.writeFile(p,new Uint8Array([1,2]));}
  if(kind==='directory'){js(()=>env.filesystem.mkdir(p));ref.FS.mkdir(p);}
  const jp=js(()=>env.memory.malloc(64)),cp=BigInt(ref._malloc(64n)),path=cput(ref,p);
  const j=js(()=>report.services.readlink(p,jp,n)),c=Number(ref._readlink(path,cp,BigInt(n)));equal(j,c,'readlink result '+p+'/'+n);equal(env.libc.errno,ref._probe_tty_errno(),'readlink errno '+p+'/'+n);js(()=>env.memory.free(jp));ref._free(cp);ref._free(path);
 }
 if(real===null)for(const n of [0,1,63,64,65,4095,4096,4097,9000]){
  const jc=js(()=>env.memory.malloc(layouts.nhmd4.size)),cc=BigInt(ref._malloc(BigInt(layouts.nhmd4.size))),ji=js(()=>env.memory.malloc(n+1)),ci=BigInt(ref._malloc(BigInt(n+1))),jo=js(()=>env.memory.malloc(16)),co=BigInt(ref._malloc(16n)),input=Uint8Array.from({length:n},(_,i)=>(i*73+19)&255);
  js(()=>{env.memory.HEAPU8.fill(0xa5,jc,jc+layouts.nhmd4.size);env.memory.HEAPU8.set(input,ji+1);});ref.HEAPU8.fill(0xa5,Number(cc),Number(cc)+layouts.nhmd4.size);ref.HEAPU8.set(input,Number(ci)+1);
  const state=phase=>equal(js(()=>Buffer.from(env.memory.readBytes(jc,layouts.nhmd4.size))),Buffer.from(ref.HEAPU8.slice(Number(cc),Number(cc)+layouts.nhmd4.size)),'C NHMD4 full context '+phase+'/'+n);
  js(()=>env.resolve('nhmd4_init')(jc));ref._nhmd4_init(cc);state('init');
  js(()=>env.resolve('nhmd4_update')(jc,ji+1,n));ref._nhmd4_update(cc,ci+1n,BigInt(n));state('unaligned update');
  js(()=>env.resolve('nhmd4_final')(jc,jo));ref._nhmd4_final(cc,co);state('final clear');equal(js(()=>Buffer.from(env.memory.readBytes(jo,16))),Buffer.from(ref.HEAPU8.slice(Number(co),Number(co)+16)),'C NHMD4 digest '+n);
  js(()=>[jc,ji,jo].forEach(p=>env.memory.free(p)));[cc,ci,co].forEach(p=>ref._free(p));
 }
}
console.log(`PASS: ${comparisons} original-C connected early_init/REPORT/NHMD4 comparisons, ${contracts} JS isolation/ownership checks, ${hashes} source/artifact hashes; three raw build-date settings. Success hashing through executable symlinks and process launch remain unaccepted.`);

console.log("REPORT_RESULT "+JSON.stringify({comparisons,contracts,hashes,cases:3}));
}
