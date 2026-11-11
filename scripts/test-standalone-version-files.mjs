// Original VERSION -> SFBASE -> historical SFSTRUCT -> real file acceptance.
import assert from 'node:assert/strict';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';
import {spawnSync} from 'node:child_process';import {fileURLToPath,pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/ported/c-runtime.js';

if(!process.argv.includes('--worker')){
 const result=spawnSync(process.execPath,[fileURLToPath(import.meta.url),'--worker'],{env:{...process.env,TZ:'UTC'},encoding:'utf8',timeout:60000,maxBuffer:8*1024*1024});process.stdout.write(result.stdout||'');assert.equal(result.status,0,result.error||result.stderr||result.stdout);
}else{
 const directory=path.resolve(process.env.STANDALONE_VERSION_FILES_ORACLE||'.cache/standalone-unix-platform-v6'),referenceRoot=path.resolve(process.env.STANDALONE_REFERENCE_ROOT||'../teleport-contest');
 const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),persistence=JSON.parse(fs.readFileSync('js/standalone/persistence-transport-abi.json')),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
 let hashes=0,comparisons=0,contracts=0,cases=0;
 for(const [file,hash]of Object.entries(receipt.sourceSha256)){assert.equal(sha(file),hash,'Changed C reference source '+file);hashes++;}
 for(const [file,hash]of Object.entries(receipt.artifactSha256)){assert.equal(sha(path.join(directory,file)),hash,'Changed C reference artifact '+file);hashes++;}
 for(const [file,hash]of Object.entries(persistence.sourceSha256)){assert.equal(sha(file),hash,'Changed persistence transport '+file);hashes++;}
 for(const [file,hash]of Object.entries(persistence.referenceHeaderSha256)){assert.equal(sha(path.join(referenceRoot,file)),hash,'Changed configured transport input '+file);hashes++;}
 const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),V=layouts.version,S=layouts.sfbase,metadata=JSON.parse(fs.readFileSync('js/standalone/records.json')).records,date=JSON.parse(fs.readFileSync('js/standalone/runtime-info-abi.json')).date;
 const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
 const equal=(a,b,label)=>{assert.deepEqual(a,b,label);comparisons++;};
 function pure(fn){const keys=['WebAssembly','fetch','WebSocket','XMLHttpRequest','Worker'],saved=keys.map(k=>Object.getOwnPropertyDescriptor(globalThis,k));let accesses=0;const deny=()=>{accesses++;throw new Error('Forbidden Wasm/network during VERSION file execution');};keys.forEach(k=>Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy(Object.create(null),{get:deny}):deny}));try{return fn();}finally{keys.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);assert.equal(accesses,0);assert.deepEqual([C,R,T],[undefined,undefined,undefined]);contracts+=2;}}
 const string=(heap,p)=>{p=Number(p);if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');};
 for(const populated of [false,true]){
  const errors=[],ref=await factory({print:()=>{},printErr:s=>errors.push(s)});ref._probe_level_init(1n);
  let env,group;
  pure(()=>{env=createStandaloneEnvironment({environment:{TZ:'UTC'}});env.enableStdio();env.enableDecl(layouts.decl);env.services.program_state_init();env.services.decl_globals_init();env.enableObjects(layouts.objects);env.services.objects_globals_init();env.enableMonst(layouts.monst);env.services.monst_globals_init();env.enableSerialization(layouts);env.enableHacklib(layouts.hacklib);group=env.enableVersionInfo(layouts);if(populated){env.enableRuntimeInfo(layouts);env.services.runtime_info_init();}});
  if(populated)ref._runtime_info_init();
  const {memory,services,ctypes}=env,cnom=Number(ref._probe_version_storage(3));
  for(const [name,f]of Object.entries(date.fields)){const j=pure(()=>memory.view.getBigUint64(group.nomakedefs+f.offset,true)),c=new DataView(ref.HEAPU8.buffer).getBigUint64(cnom+f.offset,true);equal(f.kind==='pointer'?pure(()=>string(memory.HEAPU8,j)):j,f.kind==='pointer'?string(ref.HEAPU8,c):c,'Original DATE initializer/population '+populated+':'+name);}
  const field=(name)=>metadata.nh_file.fields[name].offset,read=(heap,p,name)=>new DataView(heap.buffer).getBigInt64(Number(p)+field(name),true);
  const sides=[{heap:()=>memory.HEAPU8,alloc:n=>pure(()=>memory.calloc(1,n)),free:p=>pure(()=>memory.free(p)),open:(name,writing)=>pure(()=>services.open(name,writing?578:0,0o600)),seek:(fd,n)=>pure(()=>services.lseek(fd,n,0)),bytes:name=>pure(()=>Buffer.from(env.filesystem.readFile(name))),write:(name,bytes)=>pure(()=>env.filesystem.writeFile(name,bytes)),call:(name,...args)=>pure(()=>services[name](...args))},
   {heap:()=>ref.HEAPU8,alloc:n=>{const p=Number(ref._malloc(BigInt(n)));ref.HEAPU8.fill(0,p,p+n);return p;},free:p=>ref._free(BigInt(p)),open:(name,writing)=>ref.FS.open(name,writing?'w+':'r',0o600).fd,seek:(fd,n)=>ref.FS.llseek(ref.FS.getStream(fd),n,0),bytes:name=>Buffer.from(ref.FS.readFile(name)),write:(name,bytes)=>ref.FS.writeFile(name,bytes),call:(name,...args)=>ref['_'+name](...args.map((v,i)=>['store_version','store_critical_bytes','uptodate','compare_critical_bytes'].includes(name)?(i===0||i===1?BigInt(v):BigInt(v)):v))}];
  function frame(side,name,mode){const p=side.alloc(S.nhfileSize),fd=side.open(name,mode!==0),view=new DataView(side.heap().buffer);view.setInt32(p+field('fd'),fd,true);view.setInt32(p+field('mode'),mode,true);view.setInt32(p+field('fnidx'),S.historical,true);view.setInt8(p+field('structlevel'),1);return{p,fd,name};}
  function finish(side,f){side.call('bclose',f.fd);side.free(f.p);}
  function snapshot(){const cp=Number(ref._probe_version_storage(1));equal(pure(()=>Buffer.from(memory.readBytes(group.storage[1],V.criticalCount))),Buffer.from(ref.HEAPU8.slice(cp,cp+V.criticalCount)),'Complete source cscbuf');}
  const critical=Array.from({length:V.criticalCount},(_,i)=>{const jp=group.storage[0]+i*V.criticalSize,cp=Number(ref._probe_version_storage(0))+i*V.criticalSize;equal(pure(()=>memory.view.getUint8(jp+V.critical_ucsize)),ref.HEAPU8[cp+V.critical_ucsize],'Original critical size '+i);return ref.HEAPU8[cp+V.critical_ucsize];});
  let header;
  for(const name of ['store_version','store_critical_bytes'])for(const mode of [S.WRITING,S.COUNTING,S.WRITING|S.COUNTING]){
   const files=sides.map(side=>frame(side,'/version-'+name+'-'+mode,mode));sides.forEach((side,i)=>{side.call(name,files[i].p);side.call('bflush',files[i].fd);});
   const bytes=sides.map((side,i)=>side.bytes(files[i].name));equal(bytes[0],bytes[1],'Exact real historical file '+populated+':'+name+':'+mode);
   for(const key of ['wcount','rcount'])equal(pure(()=>read(memory.HEAPU8,files[0].p,key)),read(ref.HEAPU8,files[1].p,key),'NHFILE '+name+':'+mode+':'+key);
   if(mode&S.WRITING){equal(bytes[0].subarray(0,V.criticalCount+2),Buffer.from([104,V.criticalCount,...critical]),'Pointer-free original critical header');if(name==='store_version'){equal(bytes[0].length,V.criticalCount+2+V.versionSize,'Exact full header extent');const actual=new DataView(bytes[0].buffer,bytes[0].byteOffset+V.criticalCount+2,V.versionSize);for(const [name,key]of [['incarnation','version_number'],['feature_set','version_features'],['entity_count','version_sanity1']])equal(actual.getBigUint64(V['version_'+name],true),memory.view.getBigUint64(group.nomakedefs+date.fields[key].offset,true),'Header payload from actual DATE '+key);header=bytes[0];}}
   sides.forEach((side,i)=>finish(side,files[i]));cases++;
  }
  const mutate=(offset,value)=>{const data=Buffer.from(header);data[offset]=value;return data;},vstart=V.criticalCount+2,changed64=(field,mask)=>{const data=Buffer.from(header),at=vstart+V['version_'+field];data.writeBigUInt64LE(data.readBigUInt64LE(at)^mask,at);return data;};
  let featureBit=1n,ignored=memory.view.getBigUint64(group.nomakedefs+date.fields.ignored_features.offset,true);while(featureBit&(ignored|BigInt(V.SFCTOOL_BIT)))featureBit<<=1n;assert.ok(featureBit<(1n<<64n));
  const inputs=[['valid',Buffer.from(header)],['ignored indicator',mutate(0,63)],['larger critical count',mutate(1,V.criticalCount+1)],['zero critical count',mutate(1,0)],['negative critical count',mutate(1,255)],['wrong short size',mutate(3,3)],['wrong record size',mutate(2+10,header[2+10]^1)],['wrong version',changed64('incarnation',1n)],['wrong features',changed64('feature_set',featureBit)],['wrong entity count',changed64('entity_count',1n)],['converted marker',changed64('feature_set',BigInt(V.SFCTOOL_BIT))]];
  for(const [label,bytes]of inputs)for(const skip of [0,V.UTD_SKIP_SANITY1]){
   const flags=BigInt(V.UTD_QUIETLY|skip),name='/version-input';sides.forEach(side=>side.write(name,bytes));const files=sides.map(side=>frame(side,name,0));
   const values=sides.map((side,i)=>side.call('uptodate',files[i].p,0,flags));equal(values[0],values[1],'Original uptodate result '+populated+':'+label+':'+skip);snapshot();
   equal(pure(()=>ctypes.getField('struct instance_globals_c',env.requireGlobal('gc'),'converted_savefile_loaded','signed char')),ref.HEAPU8[Number(ref._probe_decl_global(JSON.parse(fs.readFileSync('js/standalone/decl-storage.json')).globals.findIndex(r=>r.name==='gc')))+metadata.instance_globals_c.fields.converted_savefile_loaded.offset],'Original converted-save marker');
   sides.forEach((side,i)=>finish(side,files[i]));cases++;
   sides.forEach(side=>side.write(name,bytes.subarray(1)));const criticalFiles=sides.map(side=>frame(side,name,0)),indices=sides.map(side=>{const p=side.alloc(4);new DataView(side.heap().buffer).setInt32(p,-99,true);return p;});
   const results=sides.map((side,i)=>side.call('compare_critical_bytes',criticalFiles[i].p,indices[i],flags));equal(results[0],results[1],'Original critical compatibility status '+label+':'+skip);equal(new DataView(memory.buffer).getInt32(indices[0],true),new DataView(ref.HEAPU8.buffer).getInt32(indices[1],true),'Actual int* first-mismatch copyback '+label+':'+skip);snapshot();
   sides.forEach((side,i)=>{finish(side,criticalFiles[i]);side.free(indices[i]);});cases++;
  }
  assert.deepEqual(errors,[],'Quiet fully sized compatibility cases reach no external diagnostic boundary');contracts++;
 }
 console.log(`PASS: ${comparisons} original-C VERSION/historical file/header/compatibility comparisons over${cases} cases, ${contracts} pure-JS scope checks, ${hashes} source/artifact hashes. Initial and source-populated DATE covered; truncated fatal UI and full SAVE remain separate.`);
}
