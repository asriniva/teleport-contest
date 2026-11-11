// Finite ordinary main recordings plus actual world graphs, before and after the
// first hostile item-search movement. Scalar/RNG agreement alone is insufficient.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const reference=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const source=JSON.parse(fs.readFileSync(path.join(reference,'scenarios/death.json')));
const checkpoints=(process.env.STANDALONE_MOVEMENT_CHECKPOINTS??'256,290,716').split(',').map(Number);
assert.ok(checkpoints.length&&checkpoints.every(n=>Number.isInteger(n)&&n>0&&n<=source.keys.length));
const output=path.resolve('.cache/standalone-monster-movement-program');fs.mkdirSync(output,{recursive:true});
const observations=(r,c)=>({status:r.status,consumed:r.consumed,snapshots:r.snapshots,state:r.state,rngLog:r.rngLog,displayRngLog:r.displayRngLog,stdout:r.stdout,stderr:r.stderr,frames:c?r.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})):r.frames});
let checks=0;const cases=[];
for(const count of checkpoints){
 let cr,jr;
 // The hooks retain source runtimes before main. Observe world state only after
 // each finite run; constructor-time snapshots cannot prove gameplay equality.
 const input={...source,keys:source.keys.slice(0,count)};
 const c=await runFullOriginalC(reference,{...input,observeRuntime:r=>{cr=r;}});
 const j=runStandaloneProgram(path.join(reference,'assets'),{...input,observeRuntime:r=>{jr=r;}});
 const cg=worldGraph(cr),jg=worldGraph(jr);
 for(const [name,value]of [['c',c],['js',j],['c-world',cg],['js-world',jg]])fs.writeFileSync(path.join(output,`${count}-${name}.json`),JSON.stringify(value)+'\n');
 assert.deepEqual(j.status,{kind:'input-exhausted'},count+' reaches the finite input boundary');checks++;
 assert.deepEqual(observations(j,false),observations(c,true),count+' complete recording, state and both RNG histories');checks++;
 assert.deepEqual(jg,cg,count+' actual normalized world records and pointer graph');checks++;
 cases.push({keys:count,moves:j.state.moves,frames:j.frames.length,worldRecords:jg.coverage.counts});
 console.log('PASS movement boundary '+JSON.stringify(cases.at(-1)));
}
const files=['scripts/test-standalone-monster-movement-program.mjs','scripts/restoration-world-graph.mjs','scripts/run-standalone-program.mjs','scripts/full-original-c-run.mjs','js/standalone/monster-movement.js','js/standalone/monster-lifecycle.js','js/ported/monmove-runtime.js','js/ported/monmove.js','js/ported/mon-runtime.js','js/ported/mon.js'];
const evidence={profile:'Strict original full-C main against pure JS finite ordinary movement; source death fixture input prefix',checks,cases,completeGameAccepted:false,sourceSha256:Object.fromEntries(files.map(file=>[file,crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex')])),limitation:'Only these finite recordings and normalized world graphs are accepted; later death, victory, other seeds and unreached movement branches remain separate requirements.'};
fs.writeFileSync(path.join(output,'evidence.json'),JSON.stringify(evidence,null,2)+'\n');console.log('PASS '+JSON.stringify(evidence));
