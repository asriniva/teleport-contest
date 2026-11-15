import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {createCfgfilesEnvironment} from '../js/nethack/bindings/cfgfiles.js';
import * as cfgfiles from '../js/ported/cfgfiles.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const {environment:e}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const services=e.start('cfgfiles').environment;
const pointer=createCfgfilesEnvironment(services,layouts.cfgfiles,cfgfiles);
assert.equal(pointer.va_start([123n]),123,'compiled C fixtures retain their pointer ABI');
assert.throws(()=>pointer.va_start([1,2]),/native va_list/);
const values=createCfgfilesEnvironment(services,layouts.cfgfiles,cfgfiles,{varargs:'values'});
for(const packet of [[],[17],[123n,-17,9007199254741001n]])assert.equal(values.va_start(packet),packet,'native packets retain identity and order');
const original=e.services.vsnprintf,observations=[];
e.services.vsnprintf=(out,size,format,packet)=>{assert.ok(Array.isArray(packet));const result=original(out,size,format,packet);observations.push({format:e.memory.readString(Number(format)),packet:[...packet],text:e.memory.readString(Number(out)),result});return result;};
const literal=text=>e.services.literal(text),call=(name,...args)=>e.resolve(name)(...args);
for(const [root,type,key]of [['program_state','struct sinfo','config_error_ready'],['iflags','struct instance_flags','in_lua']]){const field=e.ctypes.record(type).fields[key],scalar=e.ctypes.canonical(field.ctype.replace(new RegExp('\\s+'+key+'$'),''));e.ctypes.setField(type,e.requireGlobal(root),key,scalar,1);}
call('config_error_init',0,literal('varargs fixture'),0);
const label=literal('value');
for(const [format,packet,expected] of [['no arguments',[],'no arguments'],['one:%d',[17],'one:17'],['mixed:%s:%d:%lld:%zu:%.2f',[label,-17,9007199254741001n,9007199254741003n,1.25],'mixed:value:-17:9007199254741001:9007199254741003:1.25']]){
 call('config_error_add',literal(format),...packet);const actual=observations.pop();assert.equal(actual.format,format);assert.deepEqual(actual.packet,packet);assert.equal(actual.text,expected);assert.equal(actual.result,expected.length);
}
console.log(JSON.stringify({passed:true,pointerAbi:true,nativePackets:true,productionConfiguration:true,emptyAndSinglePackets:true,mixedWidthsAndFloats:true}));

const reference=process.argv.find(arg=>arg.startsWith('--original-c='))?.slice('--original-c='.length);
if(reference){
 const {runFullOriginalC}=await import('./full-original-c-run.mjs'),{runStandaloneProgram}=await import('./run-standalone-program.mjs'),{encodeRecorderScreen}=await import('../js/wasm-replay-support.js');
 for(const options of ['OPTIONS=!news,menu_style:full\n','OPTIONS=!news,inv_order:bad-order\n']){
  const input={seed:1,timezone:'UTC',options,keys:'  ni \x1bi \x1b'},expected=await runFullOriginalC(reference,input),actual=runStandaloneProgram(reference+'/assets',input);
  for(const key of ['status','consumed','state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(actual[key],expected[key],key);
  assert.deepEqual(actual.frames,expected.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})), 'original-C warning frames');
  console.log(JSON.stringify({passed:true,options,frames:actual.frames.length,status:actual.status,orderedRng:true}));
 }
}
