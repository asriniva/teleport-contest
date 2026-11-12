import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import assert from './native-test-assert.mjs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {readFile,writeFile,mkdir} from 'node:fs/promises';
import {spawnSync} from 'node:child_process';
import {initializeDecl,callDecl,createDeclEnvironment} from '../js/nethack/bindings/decl.js';
import {checkDeclSource} from '../nethack-c/wasm/tu-fragments/decl-source-check.mjs';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
const guard=checkDeclSource();
const schema=JSON.parse(await readFile('nethack-c/wasm/tu-fragments/decl-schema.json','utf8'));
const globals=schema.globals,records=schema.schema,dir=resolve(process.env.DECL_PROBE_DIR??'.cache/decl-author');
await mkdir(dir,{recursive:true});
const exports=['teleport_decl_storage','teleport_decl_public_address','teleport_decl_layout_count','teleport_decl_layout_name','teleport_decl_layout_value','probe_stack','probe_trace','probe_action','probe_dirty_reset','probe_retained','probe_dirty_program','probe_grow','probe_links','probe_ctor_ran','probe_foreign'];
if(process.argv.includes('--build')){
 const defines=JSON.parse(await readFile('nethack-c/wasm/compile-defines.json','utf8'));
 const compile=['-O2','-fno-lto','-sMEMORY64=1',...defines.map(x=>'-D'+x),'-I'+resolve('.cache/wasm64-build/tree/include'),'-I'+resolve('.cache/ncurses-wasm64-build/include'),'-I'+resolve('scripts'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-fmacro-prefix-map='+resolve('scripts/../.cache/wasm64-build/tree/src')+'/='];
 for(const mode of ['reference','hybrid']){
  const files=['scripts/tu-decl-probe.c','scripts/tu-decl-probe-consumer.c','nethack-c/wasm/tu-fragments/decl-support.c',...(mode==='hybrid'?['nethack-c/wasm/tu-fragments/decl-storage.c']:[])],objects=[];
  for(const [i,file]of files.entries()){
   const output=resolve(dir,mode+'-'+i+'.o'),args=[...compile,...(mode==='hybrid'?['-DHYBRID_DECL=1']:[]),'-c',resolve(file),'-o',output];
   const result=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{encoding:'utf8',maxBuffer:16*1024*1024});
   await writeFile(resolve(dir,'build-'+mode+'-'+i+'-'+Date.now()+'.log'),result.stdout+result.stderr);assert.equal(result.status,0,'DECL separately compiled '+file+': '+result.stderr);objects.push(output);
  }
  const args=['-O2','-fno-lto','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAPU8','-sEXPORTED_FUNCTIONS='+JSON.stringify(exports.map(n=>'_'+n)),...objects,...(mode==='hybrid'?['--js-library',resolve('nethack-c/wasm/tu-libraries/decl.js')]:[]),'-o',resolve(dir,'decl-'+mode+'.mjs')];
  const result=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{encoding:'utf8',maxBuffer:16*1024*1024});await writeFile(resolve(dir,'link-'+mode+'-'+Date.now()+'.log'),result.stdout+result.stderr);assert.equal(result.status,0,'DECL '+mode+' link: '+result.stderr);
 }
}
const text=(m,p)=>{p=Number(p);if(!p)return null;let end=p;while(end<m.HEAPU8.length&&m.HEAPU8[end])end++;assert.ok(end<m.HEAPU8.length,'terminated native string');return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');};
const rf=(await loadFixture("decl",pathToFileURL(resolve(dir,'decl-reference.mjs')))).default,hf=(await loadFixture("decl",pathToFileURL(resolve(dir,'decl-hybrid.mjs')))).default;
const reference=await rf();const L={};for(let i=0;i<reference._teleport_decl_layout_count();i++)L[text(reference,reference._teleport_decl_layout_name(i))]=reference._teleport_decl_layout_value(i);
const serviceObjects=new WeakMap(),environments=new WeakMap();
const runtime={initializeDecl(s){serviceObjects.set(s.moduleKey,s);const env=initializeDecl(s,L);environments.set(s.moduleKey,env);},decl(s,n,...a){serviceObjects.set(s.moduleKey,s);return callDecl(s,L,n,...a);}};
const hybrid=await hf({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());let comparisons=0,cases=0;
const width=d=>d.p!==undefined?8:d.t?Number(d.t.slice(1))/8:d.s?records[d.s].size:d.a.reduce((a,b)=>a*b,1)*width(d.e);
function pointerSlots(d,at=0,out=new Map()){
 if(d.p!==undefined)out.set(at,d.p);
 else if(d.s){for(const f of records[d.s].fields)if(f.bits===null)pointerSlots(f.d,at+f.offset,out);}
 else if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};for(let i=0;i<d.a[0];i++)pointerSlots(child,at+i*width(child),out);}
 return out;
}
const slots=globals.map(g=>pointerSlots(g.d));
function snapshot(m){
 const regions=globals.map((g,i)=>({start:Number(m._teleport_decl_storage(i)),end:Number(m._teleport_decl_storage(i))+g.bytes,name:g.name}));
 const textAliases=new Map();return globals.map((g,i)=>{
  const at=regions[i].start,bytes=Buffer.from(m.HEAPU8.slice(at,at+g.bytes)),pointers=[];
  for(const [offset,kind]of slots[i]){
   const raw=bytes.readBigUInt64LE(offset);bytes.writeBigUInt64LE(0n,offset);let value='null';
   if(raw){const p=Number(raw),target=regions.find(r=>p>=r.start&&p<r.end);if(kind==='char'&&!target&&!textAliases.has(p))textAliases.set(p,textAliases.size);value=target?[target.name,p-target.start]:kind==='char'?['text',text(m,p),textAliases.get(p)]:['raw',raw.toString()];}
   pointers.push([offset,kind,value]);
  }
  return {name:g.name,bytes,pointers};
 });
}
function compare(label){const a=snapshot(reference),b=snapshot(hybrid);for(let i=0;i<globals.length;i++){assert.deepEqual(b[i],a[i],label+': '+globals[i].name);comparisons++;}assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);for(let i=0;i<modules.length;i++)assert.equal(modules[i]._probe_stack(),stacks[i],'C stack restored');assert.equal(text(reference,reference._probe_trace()),text(hybrid,hybrid._probe_trace()));for(let i=0;i<64;i++){assert.equal(hybrid._probe_foreign(1,i),reference._probe_foreign(1,i),label+': public foreign read '+i);comparisons++;}comparisons+=6;cases++;}
assert.equal(reference._probe_ctor_ran(),1);assert.equal(hybrid._probe_ctor_ran(),1);
for(let i=0;i<64;i++){assert.equal(hybrid._probe_foreign(0,i),reference._probe_foreign(0,i),'foreign C constructor before DECL call slot '+i);comparisons++;}
compare('startup before any DECL function');
for(let i=0;i<globals.length;i++){assert.equal(hybrid._teleport_decl_public_address(i),hybrid._teleport_decl_storage(i),'typed public alias address '+globals[i].name);comparisons++;}
function action(n,label='action '+n){for(const m of modules)m._probe_action(n);compare(label);}
action(0);action(1);for(let i=0;i<7;i++){for(const m of modules)assert.equal(m._probe_links(i),1,'native repaired pointer/stride witness '+i);comparisons+=2;}action(2);action(3);
for(const byte of [0,1,0x55,0x7f,0x80,0xff]){for(const m of modules)m._probe_dirty_reset(byte);action(1,'all original reset targets dirty byte '+byte);}
for(const n of [1,2,31,255]){for(const m of modules)m._probe_retained(n);compare('explicit retained mutations '+n);action(1,'reset preserves omitted globals '+n);action(0,'program_state independent reset '+n);}
for(const n of [0,1,0x7f,0xff]){for(const m of modules)m._probe_dirty_program(n);action(0,'program state byte '+n);}
const retainedEnvironment=environments.get(hybrid),retainedCounts=retainedEnvironment.nhcb_counts,retainedRole=retainedEnvironment.gu.urole;
const oldBuffers=modules.map(m=>m.HEAPU8.buffer);for(const m of modules)m._probe_grow();for(let i=0;i<modules.length;i++)assert.notEqual(modules[i].HEAPU8.buffer,oldBuffers[i],'actual Wasm memory growth');compare('live views after growth');for(const m of modules)m._probe_retained(23);assert.equal(retainedCounts[0],23,'pre-growth array view reads current memory');assert.equal(retainedEnvironment.nhcb_counts[3],-23,'pre-growth environment keeps signed live fields');assert.equal(retainedRole.mnum,environments.get(hybrid).gu.urole.mnum,'pre-growth nested record view reads current memory');comparisons+=3;compare('retained pre-growth views after foreign C writes');action(1);
const services=serviceObjects.get(hybrid),env=environments.get(hybrid);
for(const attempt of [()=>{env.xdir[0]=5;},()=>{env.cg.zeroobj.otyp=10;},()=>{env.nhcb_name[0]=0;},()=>{env.urole_init_data.mnum=0;}]){const before=snapshot(hybrid);assert.throws(attempt,/readonly/);assert.deepEqual(snapshot(hybrid),before);comparisons+=2;}
for(const key of ['pointerSize','size_gg','offset_you_uhp']){assert.throws(()=>createDeclEnvironment(services,{...L,[key]:BigInt(L[key])+1n}),/ABI/);comparisons++;}
assert.throws(()=>{env.cg.nonexistent_field=1;},TypeError);comparisons++;
const other=await hf({nethackPorted:runtime});other._probe_action(1);const before=snapshot(hybrid);other._probe_retained(17);other._probe_action(1);assert.deepEqual(snapshot(hybrid),before,'Module state is independent');assert.notDeepEqual(snapshot(other),snapshot(hybrid));comparisons+=2;
let reentered=false;const nested={...services,heap(){if(C&&!reentered){reentered=true;const outer=C;callDecl(services,L,'sa_victual',0n);assert.equal(C,outer,'nested transport restores active outer bindings');}return services.heap();}};for(const m of [reference])m._probe_action(1);withCEnvironment({sentinel:1},()=>{const outer=C;callDecl(nested,L,'decl_globals_init');assert.equal(C,outer,'original caller binding restored');});assert.ok(reentered);comparisons+=3;compare('same-Module transport reentry');
const negative=await hf({nethackPorted:{initializeDecl(){},decl(){throw Error('negative startup must not call DECL');}}});assert.equal(negative._probe_ctor_ran(),1);assert.notEqual(negative._probe_foreign(0,0),reference._probe_foreign(0,0),'omitting initializer fails real pre-source C constructor witness');comparisons+=2;
console.log('DECL '+cases+' state cases / '+comparisons+' comparisons passed (configured original Emscripten C vs JavaScript; separate no-LTO foreign constructor and public readers). Native-host / whole-game pending.');
await writeFile(resolve(dir,'latest-result.json'),JSON.stringify({cases,comparisons,scope:'configured original Emscripten C vs JavaScript',nativeHost:'pending',wholeGame:'pending',storageObjects:globals.length,storageBytes:globals.reduce((s,g)=>s+g.bytes,0),separateNoLtoForeignConstructor:true,startupProof:{beforeAnyDeclSourceCall:true,foreignConstructorRuns:1,foreignConstructorComparedSlots:64,initialComparedObjects:152,noStartupNegative:{foreignConstructorRuns:negative._probe_ctor_ran(),slot0:negative._probe_foreign(0,0).toString(),originalSlot0:reference._probe_foreign(0,0).toString(),mismatchRequired:true}},retainedPreGrowthViews:true,sourceGuard:guard},null,2)+'\n');
