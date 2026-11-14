// Complete original-C MAIN, literal inputs, real filtering and history recall.
import assert from 'node:assert/strict';import fs from 'node:fs';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
let checks=0,frames=0;const cases=[];
for(const [name,setting,keys]of [['default','','  nl.Fyy \x10\x10 '],['hide','MSGTYPE=hide ".*"\n','  nl.Fyy \x10\x10 '],['norep','MSGTYPE=norep ".*"\n','  nl.Fyy \x10\x10 '],['stop','MSGTYPE=stop ".*"\n','  nl.Fyy \x10\x10 '],['long-wait','', '  n'+'.'.repeat(160)+'\x10\x10 ']]){
 const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n'+setting,keys};let runtime;
 const expected=await runFullOriginalC('.cache/full-original-c-v1',input),actual=runStandaloneProgram('.cache/full-original-c-v1/assets',{...input,observeRuntime:r=>{runtime=r;}});
 assert.notEqual(actual.status.kind,'failed',actual.status.message);assert.notEqual(expected.status.kind,'failed',expected.status.message);
 for(const key of ['status','state','stdout','stderr','rngLog','displayRngLog']){assert.deepEqual(actual[key],expected[key],name+' '+key);checks++;}
 assert.deepEqual(actual.frames,expected.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),name+' every screen/cursor/animation');checks++;frames+=actual.frames.length;
 const owner=nativeStateFor(runtime.environment),gp=owner.nativeRecords.record('struct instance_globals_p',runtime.environment.requireGlobal('gp'));
 if(setting)assert.ok(gp.plinemsg_types,'source parsed actual MSGTYPE list '+name);
 cases.push({name,keys:keys.length,consumed:actual.consumed,frames:actual.frames.length,status:actual.status.kind,filterConfigured:Boolean(gp.plinemsg_types)});
}
const evidence={passed:true,checks,frames,cases,scope:'Actual original-C MAIN and production native-message game with literal walk/wait/attack and history recall, configured hide/norep/stop regex lists, and a long wait sequence. Complete ordered RNG, terminal output and recorder frames match. This does not exercise every hidden recording or handler process.'};
fs.mkdirSync('.cache/native-message-history',{recursive:true});fs.writeFileSync('.cache/native-message-history/gameplay.json',JSON.stringify(evidence,null,2)+'\n');console.log(JSON.stringify(evidence));
