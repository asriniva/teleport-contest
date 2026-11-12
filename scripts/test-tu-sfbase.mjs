import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("sfbase");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {referenceBackend,assertStackRestored,memoryCheckpoint,assertMemoryGrowth,DataView} from './native-test-backend.mjs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {withCEnvironment,C} from '../js/c-runtime/context.js';
import {createSfbaseEnvironment} from '../js/nethack/bindings/sfbase.js';
import * as core from '../js/ported/sfbase.js';
const directory=resolve(process.env.SFBASE_PROBE_DIR??'.cache/tu-probes');
const load=async mode=>(await loadFixture("sfbase",pathToFileURL(resolve(directory,'sfbase-'+mode+'.mjs')).href)).default;
const referenceFactory=await load('reference'),hybridFactory=await load('hybrid');
const reference=await referenceBackend('sfbase',referenceFactory)();
function text(m,at){at=Number(at);let end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(at,end)).toString('latin1');}
function metadata(m){const d={};for(let i=0;i<m._probe_layout_count();i++)d[text(m,m._probe_layout_name(i))]=Number(m._probe_layout_value(i));return d;}
const L=metadata(reference),environments=new WeakMap();
const runtime={sfbase(services,name,...args){let env=environments.get(services.moduleKey);if(!env){env=createSfbaseEnvironment(services,L);environments.set(services.moduleKey,env);}const saved=services.stackSave();try{const rawSize=name==='sf_log'?args[2]:null;args=args.map(v=>typeof v==='bigint'?Number(v):v);if(name.startsWith('sfo_')||name.startsWith('sfi_')||name==='sf_log')args[0]=env.nhfile(args[0]);if(name==='sfo_version_info'||name==='sfi_version_info')args[1]=env.version(args[1]);if(name==='sf_log')args[2]=BigInt.asUintN(64,rawSize);return withCEnvironment(env,core[name],...args);}finally{services.stackRestore(saved);}}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());assert.deepEqual(metadata(hybrid),L);let comparisons=0;
const names=kind=>Array.from({length:reference['_probe_'+kind+'_count']()},(_,i)=>text(reference,reference['_probe_'+kind+'_name'](i)));
const serializers=names('serial'),values=names('values'),norms=names('norms');
const both=(fn,...args)=>modules.map(m=>m['_probe_'+fn](...args));
function compare(){const snapshots=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),logs:[0,1,2].map(i=>text(m,m._probe_logs(i))),bytes:Array.from(m.HEAPU8.slice(Number(m._probe_pointer(0,0)),Number(m._probe_pointer(0,0))+32768))}));assert.deepEqual(snapshots[1],snapshots[0]);comparisons+=4;modules.forEach((m,i)=>{assertStackRestored(m,stacks[i]);comparisons++;});assert.equal(C,undefined);}
function reset(){both('reset');compare();}
function field(index,key,value){both('file',index,key,BigInt.asIntN(64,BigInt(value)));}
function fill(seed=0){for(const m of modules){const at=Number(m._probe_pointer(0,0));for(let i=0;i<30000;i++)m.HEAPU8[at+i]=(i*19+seed*31)&255;m.HEAPU8.set(Buffer.from('field-name\0payload\0'),at+30000);}}
function action(index,file=0,count=3){modules.forEach(m=>m._probe_action(index,file,0,m._probe_pointer(0,30000),count));compare();}
// Every source-expanded serializer runs against actual C function pointers, in
// both structlevel and fieldlevel modes, including conversion output recursion.
for(const [index,name]of serializers.entries())for(const structure of [0,1])for(const convert of [0,L.CONVERTING]){
    reset();fill(index+structure);const input=name.startsWith('sfi_');field(0,0,(input?0:L.WRITING)|convert);field(0,1,structure);field(0,4,convert?1:-1);
    if(input)both('input',0,20000);action(index);
}
// Short dependency I/O, EOF, logging suppression and mutations made during calls.
for(const name of ['sfo_int64','sfi_int64','sfo_bitfield','sfi_bitfield','sfo_char','sfi_char','sfi_version_info'])for(const structure of [0,1])for(const scenario of [0,1,2,3,4,5]){
    reset();fill(scenario);const input=name.startsWith('sfi_');field(0,0,(input?0:L.WRITING)|L.CONVERTING|L.UNCONVERTING);field(0,1,structure);field(0,4,1);
    if(scenario===0)both('option',0,1);if(scenario===1)both('option',1,1);if(scenario===2)field(0,3,0);if(scenario===3)both('option',2,127);if(scenario===4)both('option',3,1);if(scenario===5)both('option',4,1);
    if(input)both('input',0,scenario===1?0:20000);action(serializers.indexOf(name),0,5);
}
// Typed scalar rendering reads actual signed widths and preserves original
// 20-byte static-buffer truncation, including the full64bit printf argument.
for(const [index,name]of values.entries()){
    const cases=name==='sfvalue_char'?[0,1,17,119]:[0n,1n,-1n,2147483648n,9007199254740997n,0xffffffffffffffffn];
    for(const value of cases){reset();fill(4);for(const m of modules){const at=Number(m._probe_pointer(0,0));for(let j=0;j<8;j++)m.HEAPU8[at+j]=Number(BigInt.asUintN(64,BigInt(value))>>BigInt(j*8)&255n);}
        const out=modules.map(m=>m._probe_value(index,0,name==='sfvalue_char'?Number(value):1));assert.equal(text(hybrid,out[1]),text(reference,out[0]));comparisons++;const bufferSize=L['buffer_'+name];assert.deepEqual(Array.from(hybrid.HEAPU8.slice(Number(out[1]),Number(out[1])+bufferSize)),Array.from(reference.HEAPU8.slice(Number(out[0]),Number(out[0])+bufferSize)));comparisons++;
        const again=modules.map(m=>m._probe_value(index,0,name==='sfvalue_char'?Number(value):1));assert.equal(again[0],out[0]);assert.equal(again[1],out[1]);comparisons+=2;compare();
        if(name==='sfvalue_uint64'&&value===0xffffffffffffffffn)assert.equal(text(hybrid,out[1]),'1844674407370955161');
    }
}
for(const name of ['sfvalue_genericptr','sfvalue_size_t','sfvalue_time_t']){reset();const result=both('value',values.indexOf(name),-1,0);assert.equal(text(hybrid,result[1]),text(reference,result[0]));comparisons++;compare();}
// All73 original norm_ptrs functions are no-ops. Compare the entire raw buffer.
reset();fill(7);for(let index=0;index<norms.length;index++){both('norm',index);compare();}
// Logger size_t/long arguments remain exact beyond32 and53 bits.
for(const count of [-2147483649n,9007199254740997n,9223372036854775807n])for(const size of [1n,4294967297n,18446744073709551615n]){reset();fill(0);field(0,5,count);field(0,0,0);modules.forEach(m=>m._probe_log(0,size,-7,m._probe_pointer(0,30000),m._probe_pointer(0,30011)));compare();}
for(const mode of [0,L.WRITING,L.TURN_OFF_LOGGING,L.WRITING|L.TURN_OFF_LOGGING]){reset();fill(1);field(0,0,mode);field(0,5,9007199254740997n);field(0,6,-9007199254740997n);modules.forEach(m=>m._probe_log(0,1n,1,m._probe_pointer(0,30000),m._probe_pointer(0,30011)));compare();}
// A real descriptor failure sets the FILE error state; SFBASE still follows its
// original ignored fprintf/fflush return behavior.
reset();fill(1);both('close_log',0);action(serializers.indexOf('sfo_int64'));
// C callbacks can grow memory and reenter JS while NHFILE views stay live.
for(const name of ['sfo_int64','sfi_int64','sfi_version_info','sfo_char']){reset();fill(9);field(0,1,0);field(0,0,name.startsWith('sfi_')?L.CONVERTING:L.WRITING);field(0,4,1);both('option',5,1);both('option',4,1);if(name.startsWith('sfi_'))both('input',0,20000);const before=modules.map(memoryCheckpoint);action(serializers.indexOf(name));modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));comparisons+=2;}
// Live table copies/setters, including alternate callback identities and ext.
for(const op of [0,1,2,3]){reset();fill(1);both('table',op,op===3?L.exportascii:L.historical);if(op===3)field(0,1,0);action(serializers.indexOf('sfo_int64'));action(serializers.indexOf('sfi_int64'));}
// Original zero templates are mutable extern data. An external native writer
// changes a callback before sf_init copies it into the invalid table slot.
for(const input of [0,1]){reset();fill(2);for(const m of modules){const memory=new FixtureDataView(m.HEAPU8.buffer);const zero=Number(m._teleport_sfbase_global(input?5:4)),historical=Number(m._teleport_sfbase_global(input?9:8));const offset=L.structlevel_fn+L.proc_int64;memory.setBigUint64(zero+offset,memory.getBigUint64(historical+offset,true),true);}both('table',0,0);field(0,7,L.invalid);if(input)both('input',0,20000);action(serializers.indexOf(input?'sfi_int64':'sfo_int64'));}
// Separate Module instances share the dispatcher but retain independent tables,
// static value buffers, callback identities and NHFILE storage.
reset();fill(11);action(serializers.indexOf('sfo_int64'));const retained=modules.map(m=>text(m,m._probe_snapshot()));const privateBuffer=hybrid._probe_value(values.indexOf('sfvalue_genericptr'),0,0);const retainedBuffer=text(hybrid,privateBuffer);const other=await hybridFactory({nethackPorted:runtime});other._probe_reset();other._probe_value(values.indexOf('sfvalue_genericptr'),-1,0);assert.notEqual(environments.get(other),environments.get(hybrid));assert.equal(text(hybrid,hybrid._probe_snapshot()),retained[1]);assert.equal(text(hybrid,privateBuffer),retainedBuffer);comparisons+=3;
console.log(`sfbase: ${comparisons} ${fixtureReferenceLabel}/JS raw byte, callback, log, field, value, identity, stack and Module comparisons; all239 original functions invoked`);
