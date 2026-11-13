// Development-only source-layout inverse. Runtime execution never imports this.
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {execFileSync,spawnSync} from 'node:child_process';
import v8 from 'node:v8';
import crypto from 'node:crypto';
import {priorReferenceRuntime,priorRuntimeSha,priorJsRuntimeSource,priorJsRuntimeSha} from './branch-coverage/reference-runtime-successor.mjs';
import {priorRumorsSource,priorRumorsSha} from './branch-coverage/rumors-source-successor.mjs';
const root=fileURLToPath(new URL('../',import.meta.url));
const base='e61e34c926bed5a098cf3142ba50fa6cf56d2b46';
let checked=false,prior;
export function currentLayoutPath(file){return file.replace(/^js\/standalone(?=\/|$)/,'js/nethack');}
function verify(){if(!checked){execFileSync('python3',[path.join(root,'scripts/consolidate-nethack-layout.py')],{cwd:root,stdio:'pipe'});checked=true;}}
function previous(){
 verify();if(prior)return prior;
 const dir=path.join(root,'.cache/nethack-layout'),view=path.join(dir,'prior'),ready=path.join(dir,'ready');
 fs.mkdirSync(dir,{recursive:true});
 if(fs.existsSync(ready)&&fs.readFileSync(ready,'utf8').trim()!==base)fs.unlinkSync(ready);
 if(!fs.existsSync(ready)){
  const lock=path.join(dir,'lock');let owned=false;
  for(let i=0;i<1200;i++){
   if(fs.existsSync(ready))break;
   try{fs.mkdirSync(lock);owned=true;break;}catch(error){if(error.code!=='EEXIST')throw error;Atomics.wait(new Int32Array(new SharedArrayBuffer(4)),0,0,100);}
  }
  if(owned)try{
   fs.rmSync(view,{recursive:true,force:true});fs.mkdirSync(view,{recursive:true});
   const archive=path.join(dir,'prior.tar');execFileSync('git',['archive','--format=tar','-o',archive,base],{cwd:root});
   execFileSync('tar',['-xf',archive,'-C',view]);fs.unlinkSync(archive);
   const upstream=path.join(view,'nethack-c/upstream');fs.rmSync(upstream,{recursive:true,force:true});fs.symlinkSync(path.join(root,'nethack-c/upstream'),upstream,'dir');
   fs.symlinkSync(path.join(root,'.cache'),path.join(view,'.cache'),'dir');
   const git=execFileSync('git',['rev-parse','--absolute-git-dir'],{cwd:root,encoding:'utf8'}).trim();
   fs.writeFileSync(path.join(view,'.git'),'gitdir: '+git+'\n');
   fs.writeFileSync(ready,execFileSync('git',['rev-parse',base],{cwd:root}));
  }finally{fs.rmSync(lock,{recursive:true,force:true});}
  if(!fs.existsSync(ready))throw Error('Timed out preparing immutable prior-layout audit view');
 }
 prior=view;return view;
}
const featurePaths=new Set(["js/c-runtime/heap.js", "js/c-runtime/adapter-factories.js", "js/nethack/movement.js", "js/nethack/serialization.js", "js/standalone-recorder-adapter.js", "scripts/pure-js-probes/deny-wasm.mjs", "js/nethack/uhitm.js"]);
function beforeFeature(file){
 if(['js/nethack/bindings/termcap.js'].includes(file))return execFileSync('python3',[path.join(root,'scripts/full_replay_source_successor.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024});
 if(["js/c-runtime/records.js", "js/c-runtime/record-views.js", "js/nethack/monster-creation.js", "js/ported-utilities/sfctool-helpers.js", "js/ported-utilities/sfctool-runtime.js", "js/ported-utilities/tile2bmp/runtime.mjs"].includes(file))return execFileSync('python3',[path.join(root,'scripts/monster_view_source_successor.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024});
 if(['js/nethack/bindings/hack.js','js/nethack/bindings/mon.js','js/nethack/bindings/wintty.js'].includes(file)&&fs.existsSync(path.join(root,'scripts/pointer_limit_source_successor.py')))return execFileSync('python3',[path.join(root,'scripts/pointer_limit_source_successor.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024});
 if(['js/nethack/object-state.js','js/nethack/shknam.js','js/nethack/teleport.js'].includes(file))return execFileSync('python3',[path.join(root,'scripts/engine_service_source_successors.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024});
 if(['scripts/test-standalone-game-assets.mjs','scripts/test-standalone-mon-assert.mjs','scripts/test-tu-display.mjs','scripts/test-tu-shk.mjs'].includes(file))return execFileSync('python3',[path.join(root,'scripts/engine_test_source_successors.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024});
 if(['js/nethack/bindings/display.js','js/nethack/bindings/invent.js'].includes(file)&&fs.existsSync(path.join(root,'scripts/immutable_selectors_source_successor.py')))return execFileSync('python3',[path.join(root,'scripts/immutable_selectors_source_successor.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024});
 if(['js/c-runtime/types.js','js/c-runtime/address-bindings.js'].includes(file)&&fs.existsSync(path.join(root,'scripts/type_metadata_source_successor.py')))return execFileSync('python3',[path.join(root,'scripts/type_metadata_source_successor.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024});
 return featurePaths.has(file)&&fs.existsSync(path.join(root,'docs/runtime-environment/transport-allocation-source-successors.json'))?execFileSync('python3',[path.join(root,'scripts/transport_allocation_source_successors.py'),'--file',file],{cwd:root,maxBuffer:32*1024*1024}):fs.readFileSync(path.join(root,file));
}
// Accept either the exact current bytes or their verified path-only predecessor.
export function layoutSourceSha(file,expected){
 // Raw asset data always hashes its real bytes, independently of expected values.
 if(ArrayBuffer.isView(file))return crypto.createHash('sha256').update(file).digest('hex');
 const absolute=path.isAbsolute(file)?file:path.join(root,file),logical=path.relative(root,absolute),actualFile=path.join(root,currentLayoutPath(logical));
 const sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
 const actual=sha(fs.readFileSync(actualFile));if(actual===expected)return actual;
 if(logical==='js/backends/emscripten/runtime.js'&&expected===priorRuntimeSha)return sha(priorReferenceRuntime(fs.readFileSync(actualFile)));
 if(logical==='js/nethack/runtime.js'&&expected===priorJsRuntimeSha)return sha(priorJsRuntimeSource(fs.readFileSync(actualFile)));
 if(logical==='js/ported/rumors.js'&&expected===priorRumorsSha)return sha(priorRumorsSource(fs.readFileSync(actualFile)));
 if(sha(beforeFeature(path.relative(root,actualFile)))===expected)return expected;
 const before=relative(logical),receipt=JSON.parse(fs.readFileSync(path.join(root,'docs/runtime-environment/nethack-layout.json'))),row=receipt.files[before];
 if(!row)return actual;
 const owner=row.destination===null?receipt.files['js/nethack/address-ports.js']:row;
 if(sha(beforeFeature(path.relative(root,actualFile)))!==owner.afterSha256)throw Error('Source changed beyond NetHack path relocation: '+logical);
 verify();
 const bytes=execFileSync('git',['show',base+':'+before],{cwd:root,maxBuffer:32*1024*1024});
 return sha(bytes)===expected?expected:actual;
}
function childEnvironment(view){return {...process.env,GIT_WORK_TREE:view,GIT_DIR:execFileSync('git',['rev-parse','--absolute-git-dir'],{cwd:root,encoding:'utf8'}).trim()};}
function relative(file){const p=path.isAbsolute(file)?path.relative(root,file):file;const receipt=JSON.parse(fs.readFileSync(path.join(root,'docs/runtime-environment/nethack-layout.json')));if(Object.hasOwn(receipt.files,p))return p;return Object.entries(receipt.files).find(([,row])=>row.destination===p)?.[0]??p;}
export function historicalCall(module,name,args){
 const view=previous(),directory=fs.mkdtempSync(path.join(os.tmpdir(),'nethack-prior-call-'));
 try{
  const input=path.join(directory,'input.json'),output=path.join(directory,'output.bin');
  args=[relative(String(args[0])),...args.slice(1)];fs.writeFileSync(input,JSON.stringify(args));
  const code="import fs from 'node:fs';import v8 from 'node:v8';const args=JSON.parse(fs.readFileSync(process.argv[1]),(_,v)=>v?.type==='Buffer'?Buffer.from(v.data):v);const m=await import(process.argv[3]);fs.writeFileSync(process.argv[2],v8.serialize(await m[process.argv[4]](...args)));";
  execFileSync(process.execPath,['--input-type=module','-e',code,input,output,pathToFileURL(path.join(view,module)).href,name],{cwd:view,env:childEnvironment(view),stdio:'pipe'});
  return v8.deserialize(fs.readFileSync(output));
 }finally{fs.rmSync(directory,{recursive:true,force:true});}
}
export function runHistoricalCli(url){
 if(!process.argv[1]||path.resolve(process.argv[1])!==fileURLToPath(url))return false;
 runPrior(relative(fileURLToPath(url)),process.argv.slice(2));return true;
}
function runPrior(file,args){
 if(args.includes('--write')||(file==='scripts/write-c-runtime-manifest.mjs'&&!args.includes('--check')))throw Error('Historical audit projection is read-only; update current sources through the consolidation recipe.');
 args=args.map(value=>value.startsWith('js/')?relative(value):value);
 const view=previous(),binary=file.endsWith('.py')?'python3':process.execPath;
 const result=spawnSync(binary,[path.join(view,file),...args],{cwd:view,env:childEnvironment(view),stdio:'inherit'});
 if(result.error)throw result.error;if(result.status!==0)process.exit(result.status??1);
}
if(process.argv[2]==='--historical')runPrior(process.argv[3],process.argv.slice(4));
