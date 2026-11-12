// EmC is the first-pass reference for this parallel port; native remains an
// explicitly selectable follow-up using the same cases, without normalization.
import { readFileSync } from 'node:fs';
import assert from './native-test-assert.mjs';
import { referenceBackend, assertStackRestored, memoryCheckpoint, assertMemoryGrowth } from './native-test-backend.mjs';
import referenceEmc from '../.cache/tu-probes/earlyarg-reference.mjs';
import hybridFactory from '../.cache/tu-probes/earlyarg-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import * as core from '../js/ported/earlyarg.js';
import { C,R,T } from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.earlyarg,native=process.env.TELEPORT_NATIVE_TESTS==='1';
const runtime=createPortedRuntime(layouts);
const modules=[await (native?referenceBackend('earlyarg',referenceEmc):referenceEmc)(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0,count=0;
function text(m,p){p=Number(p);if(!p)return null;let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
function put(m,s){const b=Buffer.isBuffer(s)?s:Buffer.from(s,'latin1'),p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;return p;}
function scope(){assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));}
function snapshot(m){return{state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),result:text(m,m._probe_result()),alias:m._probe_result_alias(),order:Array.from({length:count},(_,i)=>m._probe_arg_origin(i))};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));scope();comparisons++;}
function call(name,...args){const results=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(results[1],results[0],`${name}(${args})`);check();return results[0];}
function strings(name,args,...before){modules.forEach(m=>{const pointers=args.map(s=>put(m,s));try{m['_probe_'+name](...before,...pointers.map(BigInt));}finally{pointers.forEach(p=>m._free(p));}});check();}
function reset(args=['nethack']){count=args.length;call('reset',count);args.forEach((s,i)=>strings('arg',[s],i));}
function action(op,arg=0,shift=0){return call('action',op,arg,shift);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function state(){return text(modules[0],modules[0]._probe_snapshot());}
// Every compiled constant and field offset is observed before parsing.
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const key=text(m,m._probe_layout_name(i));assert.equal(Number(BigInt.asIntN(64,BigInt(m._probe_layout_value(i)))),L[key],key);}
const catalogueNames=['monsdump','objdump','defsym_cmap_dump','defsym_mon_syms_dump','defsym_mon_defchars_dump','objclass_defchars_dump','objclass_classes_dump','objclass_syms_dump','arti_enum_dump','mcastu_enum_dump'];
for(const [table,name]of catalogueNames.entries()){
 const rows=core[name].map(row=>({nm:row.nm,val:typeof row.val==='string'?L[row.val]:row.val}));
 assert.equal(modules[0]._probe_table_count(table),rows.length);
 for(const [i,row]of rows.entries()){
  assert.equal(text(modules[0],modules[0]._probe_table_name(table,i)),row.nm);
  assert.equal(modules[0]._probe_table_value(table,i),row.val);
  if(table<2){assert.equal(text(modules[1],modules[1]._probe_table_name(table,i)),row.nm);assert.equal(modules[1]._probe_table_value(table,i),row.val);}
 }
}
// Original nonconst C tables remain live after JS-owned initialization.
for(const table of [0,1]){
 reset();const originalValue=modules[0]._probe_table_value(table,0);
 const originalNames=modules.map(m=>m._probe_table_name(table,0));
 modules.forEach(m=>{m._probe_table_set_value(table,0,-12345);m._probe_table_set_name(table,0,BigInt(m._probe_table_name(table,1)));});
 action(10);assert.match(trace(),/-12345,/);
 modules.forEach((m,i)=>{m._probe_table_set_value(table,0,originalValue);m._probe_table_set_name(table,0,BigInt(originalNames[i]));});
 assert.equal(modules[0]._probe_table_value(table,0),originalValue);
 assert.equal(text(modules[1],modules[1]._probe_table_name(table,0)),text(modules[0],originalNames[0]));
 reset();action(10);
}
// getopt-like private helper: matching, abbreviation, separators, next-token
// consumption, dash rejection, NULL return, optional/disallowed/no-value cases.
for(const flags of [0,1,2,4,5,6,8,9,10,12,13,14])
 for(const option of ['-windowtype','-w'])
  for(const arg of ['-w','-wi','-windowtype','-windowtype=tty','-windowtype:tty','-windowtype=','-wtty','-w=tty','-x','-windowtypeX','--windowtype'])
   for(const next of [null,'tty','-dash','']){
    reset(next===null?[arg]:[arg,next,'tail']);strings('option_name',[option]);action(3,flags);
   }
// Same stable writable no-value array; its returned identity is preserved.
reset(['-windowtype']);strings('option_name',['-windowtype']);action(3,1);assert.equal(modules[0]._probe_result_alias(),-2);
const novalue=modules.map(m=>m._probe_pointer(0));call('mutate',0,1,88);action(3,1);assert.equal(snapshot(modules[0]).result,'[Xothing]');call('mutate',0,1,110);
modules.forEach((m,i)=>assert.equal(m._probe_pointer(0),novalue[i]));
// Rotation retains every original pointer, including the hidden final tokens.
for(const argc of [2,3,5,12])for(let index=1;index<argc;index++){
 reset(Array.from({length:argc},(_,i)=>'arg'+i));action(4,index);
 if(index+1<argc){reset(Array.from({length:argc},(_,i)=>'arg'+i));action(5,index);}
}
const argvCases=[['nethack'],['nethack','ordinary','tail'],['nethack','-debug:test'],['nethack','--debug:notest,ttystatus,fuzzer'],['nethack','-nethackrc=custom.rc','tail'],['nethack','-nethackrc','file.rc','tail'],['nethack','-no-nethackrc'],['nethack','-windowtype=tty'],['nethack','--windowtype','curses','tail'],['nethack','-wtty','-w','curses'],['nethack','-d/path','ordinary'],['nethack','-directory','/path','ordinary'],['nethack','-decgraphics'],['nethack','-d'],['nethack','-nethackrc'],['nethack','-windowtype='],['nethack','-help'],['nethack','?'],['nethack','--usage'],['nethack','-?'],['nethack','--version'],['nethack','--version:copy'],['nethack','--version:paste'],['nethack','--version:dump'],['nethack','--version:show'],['nethack','--version:invalid'],['nethack','--showpaths'],['nethack','-s'],['nethack','--scores','Zelda'],['nethack','--s'],['nethack','--bidshow'],['nethack','--dumpmongen'],['nethack','--dumpweights'],['nethack','--dumpglyphids'],['nethack','--dumpenums']];
for(const args of argvCases){reset(args);call('preset',1);action(0);}
reset(['nethack','-nethackrc','x.rc','-debug:test','tail']);action(0);assert.match(state(),/argc:2;/);assert.deepEqual(snapshot(modules[0]).order,[0,4,3,1,2]);
reset(['nethack','-d']);assert.equal(action(0),-2);assert.match(trace(),/error:Flag -d must be followed/);
reset(['nethack','--version:copy']);assert.equal(action(0),-1);assert.match(trace(),/version:1;/);assert.match(state(),/state:0:/);
reset(['nethack','--showpaths']);assert.equal(action(0),0);assert.match(state(),/state:7:1:/);
// argcheck must scan argv, respect every minimum length and extended value rule.
for(const row of core.earlyopts)for(const token of ['-'+row.name,'--'+row.name,'-'+row.name.slice(0,row.minlength-1),'-'+row.name.toUpperCase(),'-'+row.name+':show','-'+row.name+'=bad','ordinary']){
 reset(['nethack','unrelated',token]);action(1,L[row.e]);
}
for(const selector of [-1,999]){reset(['nethack','--version']);assert.equal(action(1,selector),0);}
reset([]);assert.equal(action(1,L.ARG_DEBUG),0);
// debug parser mutates delimiters/whitespace in its caller-owned bytes;
// recursive order and negation are observable through final flags.
for(const value of ['', 'test','notest','!test','!!test','nonotest',' test \t','ttystatus','nottystatus','fuzzer','nofuzzer','test,notest','notest,test','test,ttystatus,fuzzer',' , ,','x'.repeat(L.BUFSZ),'\xfftest']){reset([value]);action(2,0);}
for(const op of [6,7,8,9,10,11]){reset(['nethack','/fixture','-s','Zelda']);call('directory',1);action(op);}
reset(['nethack','-s','Zelda']);action(8);assert.match(trace(),/scores:3;score-arg:nethack;score-arg:-s;score-arg:Zelda;/);assert.match(state(),/fixture-nethack/);
// Actual native dependencies can reenter parser imports or grow memory while
// argument arrays/output scratch are live; scopes and pointer cells stay fresh.
for(const stage of [1,2,3,4,5,6,7,8,9,10]){
 const args=stage===3?['nethack','-nethackrc']:stage===8?['nethack','--version']:stage===9?['nethack','--dumpglyphids']:['nethack','/fixture','-s','Zelda'];
 reset(args);call('directory',1);const grow=[1,10].includes(stage);call('callback',stage,grow?stage:0);const before=modules.map(m=>memoryCheckpoint(m));
 action(stage===4||stage===5?6:stage===6||stage===7?8:stage===10?10:0);
 assert.match(trace(),new RegExp('nested:0;'));if(grow){assert.match(trace(),new RegExp('grew:'+stage+';'));
 modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));}
}
reset(['nethack','-windowtype=tty']);action(0);const kept=snapshot(modules[1]);
const independent=await hybridFactory({nethackPorted:runtime});independent._probe_reset(0);independent._probe_action(9,0,0);assert.deepEqual(snapshot(modules[1]),kept);scope();
console.log(`EARLYARG: ${comparisons} ${native?'native-C':'Emscripten-C'}/hybrid parsing, catalogue, argv mutation, termination, callbacks and growth comparisons checked.`);
