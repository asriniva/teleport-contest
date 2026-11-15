// Reproduce the leaderboard's doquiver_core("fire") -> INVENT.prinv edge.
// Only authored keys/options enter either engine; no recorded answers are used.
import assert from 'node:assert/strict';
import {runSegment} from '../js/standalone-recorder-adapter.js';
import {InMemoryStorage} from '../js/storage.js';
const options='OPTIONS=name:Archer,role:Ranger,race:human,gender:male,align:neutral\nOPTIONS=!autopickup,!autoquiver,!legacy,!tutorial,!splash_screen,pettype:none\n';
const cases=[
 {name:'manual fire refill',keys:'Q- f c\x1b',feedback:'You ready:'},
 {name:'manual fire refill through inventory menu',keys:'Q- f ?c\x1b',feedback:'You ready:'},
 {name:'counted manual refill and split stack',keys:'Q- f 2c\x1b',feedback:'You ready:'},
 {name:'cancel manual refill',keys:'Q- f \x1b',feedback:'Never mind'},
 {name:'ordinary quiver feedback',keys:'Q- Qc\x1b',feedback:'in quiver'},
];
let checks=0;
for(const scenario of cases){
 const actual=await runSegment({seed:101,datetime:'20000110090000',nethackrc:options,moves:scenario.keys,storage:new InMemoryStorage()});
 assert.ok(actual.getScreens().some(screen=>screen.includes(scenario.feedback)),scenario.name+' reaches the intended feedback');checks++;
 assert.equal(actual.getScreens().length,actual.getCursors().length);checks++;
 console.log(JSON.stringify({passed:true,scenario:scenario.name,screens:actual.getScreens().length,wasmForbidden:actual.getDependencyDiagnostics().wasmForbidden}));
}
const reference=process.argv.find(arg=>arg.startsWith('--original-c='))?.slice('--original-c='.length);
if(reference){
 const {runFullOriginalC}=await import('./full-original-c-run.mjs'),{runStandaloneProgram}=await import('./run-standalone-program.mjs'),{encodeRecorderScreen}=await import('../js/wasm-replay-support.js');
 for(const scenario of cases){
  const input={seed:101,timezone:'America/New_York',datetime:'20000110090000',argv:['-u','Archer'],options,keys:scenario.keys};
  const expected=await runFullOriginalC(reference,input),actual=runStandaloneProgram(reference+'/assets',input);
  assert.equal(actual.status.kind,'input-exhausted',scenario.name);checks++;
  for(const key of ['status','consumed','state','stdout','stderr','rngLog','displayRngLog']){assert.deepEqual(actual[key],expected[key],scenario.name+' '+key);checks++;}
  assert.deepEqual(actual.frames,expected.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),scenario.name+' exact C frames');checks++;
  console.log(JSON.stringify({passed:true,scenario:scenario.name,originalC:true,orderedCoreAndDisplayRng:true,screens:actual.frames.length}));
 }
}
console.log(JSON.stringify({passed:true,checks,scenarios:cases.length,originalC:Boolean(reference)}));
