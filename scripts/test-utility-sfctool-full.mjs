import assert from 'node:assert/strict';
import {writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import path from 'node:path';
const arg=process.argv.indexOf('--out');if(arg<0)throw Error('--out required');const out=path.resolve(process.argv[arg+1]);
const reference=(await import(pathToFileURL(out+'/reference-full.mjs'))).default;
const hybrid=(await import(pathToFileURL(out+'/hybrid-full.mjs'))).default;
import {createSfctool} from '../js/ported-utilities/sfctool-runtime.js';
let checks=0,cases=0,dispatch=0;const results=[];
async function setup(factory){const m=await factory({print(){},printErr(){}});const h=createSfctool(m);m.utilityInvoke=(name,args)=>{dispatch++;return h.invoke(name,args);};m.utilityVararg=(...a)=>h.helper.vararg(...a);m.FS.mkdirTree('/usr/games/lib/nethackdir/save');m.FS.writeFile('/usr/games/lib/nethackdir/sysconf','');m._utility_streams();return{m,h};}
function str(m,s){const n=m.lengthBytesUTF8(s)+1,p=Number(m._malloc(BigInt(n)));m.stringToUTF8(s,p,n);return p;}
function argv(m,args){const p=Number(m._malloc(BigInt((args.length+1)*8)));for(const[i,s]of args.entries())new DataView(m.HEAPU8.buffer).setBigUint64(p+i*8,BigInt(str(m,s)),true);new DataView(m.HEAPU8.buffer).setBigUint64(p+args.length*8,0n,true);return p;}
function snapshot(m){m._utility_flush();const files={};function visit(dir){for(const f of m.FS.readdir(dir))if(!['.','..'].includes(f)){const path=dir+'/'+f;if(m.FS.isDir(m.FS.stat(path).mode))visit(path);else files[path]=Array.from(m.FS.readFile(path));}}visit('/usr/games/lib/nethackdir');const address=k=>Number(m._utility_global(k)),bytes=(k,n)=>Array.from(m.HEAPU8.slice(address(k),address(k)+n)),v=()=>new DataView(m.HEAPU8.buffer),string=k=>{const p=Number(v().getBigUint64(address(k),true));return p?m.UTF8ToString(p):null;};const globals={unconverted:string(0),converted:string(1),thisdatamodel:string(8),renidx:v().getInt32(address(4),true),convertstyle:v().getUint32(address(5),true),chosen:v().getInt8(address(6)),explicit:v().getInt8(address(7)),srclog:bytes(9,Number(m._utility_layout(11))),dstlog:bytes(10,Number(m._utility_layout(11))),version:bytes(3,Number(m._utility_full_layout(48))),plname:bytes(2,Number(m._utility_full_layout(49))),cscbuf:bytes(14,Number(m._utility_full_layout(50)))};return{stdout:m.FS.readFile('/stdout',{encoding:'utf8'}),stderr:m.FS.readFile('/stderr',{encoding:'utf8'}),cwd:m.FS.cwd(),globals,files};}
async function run(args){const rows=[];for(const factory of [reference,hybrid]){const{m,h}=await setup(factory);let status=null,ret;try{ret=m._utility_full_call(0,BigInt(argv(m,args)),0n,args.length,0,0);}catch(e){if(e?.name==='ExitStatus')status=e.status;else throw e;}rows.push({status,ret,...snapshot(m)});}assert.deepEqual(rows[1],rows[0],JSON.stringify(args));checks++;cases++;results.push({args,status:rows[0].status,return:rows[0].ret,stdout:rows[0].stdout,stderr:rows[0].stderr});return rows[0];}
for(const args of [['sfctool'],['sfctool','-h'],['sfctool','-d'],['sfctool','bad','file'],['sfctool','-c'],['sfctool','-u'],['sfctool','-c','missing'],['sfctool','-u','missing']]){const a=await run(args);if(args[1]==='-d'){assert.equal(a.status,0);assert.ok(a.stdout.includes('historical savefile datamodel'));checks+=2;}}

for(const fieldlevel of[0,1]){
 const rows=[];
 for(const factory of [reference,hybrid]){const{m,h}=await setup(factory);const path='/usr/games/lib/nethackdir/save/header'+(fieldlevel?'.exportascii':'');m._utility_make_header(BigInt(str(m,path)),fieldlevel);let status=null,ret;try{ret=m._utility_full_call(0,BigInt(argv(m,['sfctool',fieldlevel?'-u':'-c','header'])),0n,3,0,0);}catch(e){if(e?.name==='ExitStatus')status=e.status;else throw e;}rows.push({status,ret,...snapshot(m)});}
 assert.deepEqual(rows[1],rows[0],'complete native-writer invalid-version header '+fieldlevel);checks++;cases++;
 assert.ok(rows[0].stderr.includes('savefile is outdated'));checks++;results.push({nativeHeaderFixture:fieldlevel?'exportascii':'historical',status:rows[0].status,stderr:rows[0].stderr});
}
for(const fieldlevel of[0,1])for(const exists of[false,true])for(const chosen of[0,1])for(const renidx of[-2,-1,0,6]){
 const rows=[];
 for(const factory of[reference,hybrid]){
  const{m,h}=await setup(factory);h.C.chosen_unconvert=chosen;h.C.renidx=renidx;h.C.thisdatamodel=Number(m._utility_datamodel(0));
  const path='/usr/games/lib/nethackdir/save/output';if(exists)m.FS.writeFile(path,'original-content');
  const suffix=renidx>=0?h.C.rensuffixes[renidx]:(renidx===-2?'':'not_')+m.UTF8ToString(Number(m._utility_datamodel(0)));
  if(exists&&chosen)m.FS.writeFile(path+'.'+suffix,'old-backup');
  let p=m._utility_file_call(1,BigInt(str(m,path)),fieldlevel?h.C.exportascii:h.C.historical);
  assert.ok(p);checks++;
  const f=h.file(p),raw=Array.from(m.HEAPU8.slice(Number(p),Number(p)+h.L[0]));
  for(const k of[19,21])for(let i=0;i<h.L[k+1];i++)raw[h.L[k]+i]=0;
  const fields={mode:f.mode,ftype:f.ftype,fnidx:f.fnidx,structlevel:f.structlevel,fieldlevel:f.fieldlevel,addinfo:f.addinfo,rcount:String(f.rcount)};
  m._utility_close_nhfile(p);rows.push({fields,raw,...snapshot(m)});
 }
 assert.deepEqual(rows[1],rows[0],'create/rename '+[fieldlevel,exists,chosen,renidx]);checks++;cases++;
}
for(const fieldlevel of[0,1])for(const exists of[false,true]){
 const rows=[];
 for(const factory of[reference,hybrid]){const{m,h}=await setup(factory);const path='/usr/games/lib/nethackdir/save/input';if(exists)m.FS.writeFile(path,'bytes');const p=m._utility_file_call(0,BigInt(str(m,path)),fieldlevel?h.C.exportascii:h.C.historical);let fields=null;if(p){const f=h.file(p);fields={mode:f.mode,ftype:f.ftype,fnidx:f.fnidx,structlevel:f.structlevel,fieldlevel:f.fieldlevel,addinfo:f.addinfo,rcount:String(f.rcount)};m._utility_close_nhfile(p);}rows.push({nonnull:Boolean(p),fields,...snapshot(m)});}
 assert.deepEqual(rows[1],rows[0],'open '+fieldlevel+'/'+exists);assert.equal(rows[0].nonnull,exists);checks+=2;cases++;
}
for(const factory of[reference,hybrid]){const{m,h}=await setup(factory);m._utility_full_call(2,0n,0n,0,0,0);for(const[table,idx,source,size]of[[15,h.C.invalid,19,h.L[27]],[16,h.C.invalid,20,h.L[27]],[15,h.C.historical,21,h.L[27]],[16,h.C.historical,22,h.L[27]],[17,h.C.exportascii,23,h.L[28]],[18,h.C.exportascii,24,h.L[28]]]){const base=Number(m._utility_global(table))+idx*size,from=Number(m._utility_global(source));assert.deepEqual(Array.from(m.HEAPU8.slice(base,base+size)),Array.from(m.HEAPU8.slice(from,from+size)));checks++;}}
const r=await setup(reference),b=await setup(hybrid);for(let i=0;i<7;i++){assert.equal(r.m.UTF8ToString(Number(r.m._utility_suffix(i))),b.h.C.rensuffixes[i]);checks++;}
writeFileSync(path.join(out,'full-test-results.json'),JSON.stringify({status:'PASS',checks,cases,dispatch,results},null,2)+'\n');console.log(JSON.stringify({status:'PASS',checks,cases,dispatch}));process.exitCode=0;
