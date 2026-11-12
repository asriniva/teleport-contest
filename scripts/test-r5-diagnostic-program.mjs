// Actual original main on both complete environments, with identical finite input.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const cases=[{name:'ready',keys:'  n'},{name:'first-wait-turn',keys:'  nm.'},{name:'initial-state-save',keys:'  nSy',status:{kind:'exited',code:0}}];
const evidence={complete:true,fullGameAccepted:false,cases:[],limitation:'Genuine main through the specified finite input boundaries only; later turns, quit, death, saved-stream semantic equivalence, fresh restore and bones remain separate acceptance requirements.'};
let savePair;
for(const scenario of cases){
 const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:scenario.keys};
 const reference=await runFullOriginalC(directory,input),actual=runStandaloneProgram(directory+'/assets',input);
 fs.mkdirSync('.cache/r5-diagnostic-program',{recursive:true});
 for(const[label,value]of [['c',reference],['js',actual]])fs.writeFileSync(`.cache/r5-diagnostic-program/${scenario.name}-${label}.json`,JSON.stringify(value,null,2)+'\n');
 assert.deepEqual(actual.status,scenario.status??{kind:'input-exhausted'},scenario.name+' reaches genuine process boundary');
 assert.deepEqual(actual.status,reference.status,scenario.name+' process status');
 assert.equal(actual.consumed,reference.consumed,scenario.name+' source input consumption');
 assert.deepEqual(actual.snapshots,reference.snapshots,scenario.name+' all input-boundary scalars and both entire ISAAC byte images');
 assert.deepEqual(actual.state,reference.state,scenario.name+' final scalar and RNG state');
 assert.equal(actual.rngLog,reference.rngLog,scenario.name+' complete core RNG log');
 assert.equal(actual.displayRngLog,reference.displayRngLog,scenario.name+' complete display RNG log');
 const frames=reference.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation}));
 assert.deepEqual(actual.frames,frames,scenario.name+' all frozen-encoded recorder frames/cursors/animation');
 assert.equal(actual.stdout,reference.stdout,scenario.name+' exact raw terminal output');
 assert.equal(actual.stderr,reference.stderr,scenario.name+' exact raw terminal error output');
 let savedStream;
 if(scenario.name==='initial-state-save'){
  savePair={c:reference,js:actual};
  assert.deepEqual(Object.keys(actual.files).sort(),Object.keys(reference.files).sort(),'All post-save files and lock removal');
  const filename='/nethack/save/0Ada.Z';assert.ok(actual.files[filename]);assert.ok(reference.files[filename]);
  for(const file of Object.keys(reference.files))if(file!==filename)assert.equal(actual.files[file].bytes,reference.files[file].bytes,'Post-save file bytes '+file);
  savedStream={path:filename,cBytes:Buffer.from(reference.files[filename].bytes,'base64').length,jsBytes:Buffer.from(actual.files[filename].bytes,'base64').length,byteIdentical:actual.files[filename].bytes===reference.files[filename].bytes,semanticEquivalenceAccepted:false};
 }
 evidence.cases.push({savedStream,name:scenario.name,inputBoundaries:actual.snapshots.length,frames:actual.frames.length,rawTerminalBytes:Buffer.from(actual.stdout,'base64').length,moves:actual.state.moves});
}
const restored=[];
for(const source of ['c','js'])for(const consumer of ['c','js']){
 const name=`restore-${source}-save-in-${consumer}`,filename='/nethack/save/0Ada.Z';
 const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'',files:{[filename]:savePair[source].files[filename]}};
 const result=consumer==='c'?await runFullOriginalC(directory,input):runStandaloneProgram(directory+'/assets',input);
 fs.writeFileSync(`.cache/r5-diagnostic-program/${name}.json`,JSON.stringify(result,null,2)+'\n');
 const normalized={status:result.status,consumed:result.consumed,snapshots:result.snapshots,state:result.state,rngLog:result.rngLog,displayRngLog:result.displayRngLog,stdout:result.stdout,stderr:result.stderr,frames:consumer==='c'?result.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})):result.frames};
 assert.deepEqual(result.status,{kind:'input-exhausted'},name+' reaches first restored input boundary');
 if(restored.length)assert.deepEqual(normalized,restored[0].observations,name+' matches original C fresh restore observations');
 restored.push({name,observations:normalized});
 evidence.cases.push({name,inputBoundaries:result.snapshots.length,frames:result.frames.length,rawTerminalBytes:Buffer.from(result.stdout,'base64').length,moves:result.state.moves});
}
evidence.limitation='Actual startup, first wait turn, initial save exit, and four independent C/JS saved-stream producer/consumer combinations through the first restored input prompt. Full restored graph equality, resumed gameplay, later turns, quit/death and bones remain separate acceptance requirements.';
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
evidence.scriptSha256=Object.fromEntries(['scripts/test-r5-diagnostic-program.mjs','scripts/run-standalone-program.mjs','scripts/full-original-c-run.mjs','js/nethack/program.js'].map(file=>[file,sha(file)]));
fs.writeFileSync('.cache/r5-diagnostic-program/evidence.json',JSON.stringify(evidence,null,2)+'\n');
console.log('PASS '+JSON.stringify(evidence));
