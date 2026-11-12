// Genuine compressed saves, fresh cross-fed consumers, identity-checked world snapshots.
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import assert from 'node:assert/strict';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1'),output=process.env.RESTORED_OUTPUT??((process.env.RESTORED_KEYS!==undefined||process.env.RESTORED_STAIRS==='1'||process.env.RESTORED_TRAVEL!==undefined)?'.cache/restored-world-diagnostic':'.cache/restored-world');fs.mkdirSync(output,{recursive:true});
const stairKeys='lk khhokkkkklklkkkkhhhhhhhhhhjhhhhhhhhhhjjjjjjjjjhhhjjhhhhkk>';
const travel=process.env.RESTORED_TRAVEL??(process.env.RESTORED_STAIRS==='1'?'down':undefined);
if(travel&&!['down','up','roundtrip'].includes(travel))throw new Error('Unknown restored travel case '+travel);
const selectedKeys=travel?stairKeys+({down:'',up:' < ',roundtrip:' < > '}[travel]):process.env.RESTORED_KEYS;
const filename='/nethack/save/0Ada.Z',profile={seed:1,timezone:'UTC',options:'OPTIONS=!news\n'};
const producers={};for(const source of ['c','js'])producers[source]=JSON.parse(fs.readFileSync(`.cache/standalone-program/initial-state-save-${source}.json`));
const observations=result=>({status:result.status,consumed:result.consumed,snapshots:result.snapshots,state:result.state,rngLog:result.rngLog,displayRngLog:result.displayRngLog,stdout:result.stdout,stderr:result.stderr,frames:result.frames.map(f=>typeof f.screen==='string'&&Array.isArray(f.cursor)&&f.cursor.length===2?{screen:encodeRecorderScreen(f.screen),cursor:[...f.cursor,1],animation:f.animation}:f)});
const sha=value=>crypto.createHash('sha256').update(value).digest('hex');
const evidence={cases:[],complete:false,fullGameAccepted:false,provenance:{referenceReceipt:sha(fs.readFileSync(directory+'/receipt.json')),schema:sha(fs.readFileSync('js/nethack/records.json')),scripts:Object.fromEntries(['scripts/test-standalone-restored-world.mjs','scripts/restoration-world-graph.mjs','scripts/run-standalone-program.mjs','scripts/full-original-c-run.mjs'].map(p=>[p,sha(fs.readFileSync(p))])),savedStreams:Object.fromEntries(['c','js'].map(s=>[s,sha(Buffer.from(producers[s].files[filename].bytes,'base64'))]))},limitations:['Initial-state save fixture only; nonempty light/timer coverage is reported, never inferred.','Only explicitly enumerated world roots are accepted; serialized maps of other levels and Lua state require separate comparison.']};
for(const keys of (selectedKeys!==undefined?[selectedKeys]:['','m.'])){
 let expected,expectedGraph;
 for(const source of ['c','js'])for(const consumer of ['c','js']){
  let retained;const input={...profile,keys,files:{[filename]:producers[source].files[filename]},observeRuntime:runtime=>{retained=runtime;}};
  const result=consumer==='c'?await runFullOriginalC(directory,input):runStandaloneProgram(directory+'/assets',input),name=`${source}-in-${consumer}-${Buffer.from(keys).toString('hex')||'prompt'}`;
  fs.writeFileSync(output+'/'+name+'-result.json',JSON.stringify(result,null,2));
  let graph;try{graph=worldGraph(retained);}catch(error){fs.writeFileSync(output+'/'+name+'-graph-error.txt',error.stack);throw error;}
  fs.writeFileSync(output+'/'+name+'-world.json',JSON.stringify(graph,null,2));
  assert.deepEqual(result.status,{kind:'input-exhausted'},name+' reaches real input boundary');assert.equal(result.consumed,keys.length,name+' consumes exact literal inputs');
  if(travel){assert.equal(graph.roots.u.uz.dnum,'0000',name+' main dungeon');assert.equal(graph.roots.u.uz.dlevel,travel==='up'?'0100':'0200',name+' genuine '+travel+' level transition');if(travel!=='down'){const tty=Buffer.from(result.stdout,'base64').toString();assert.ok(tty.includes('You climb up the stairs.'),name+' actual ascent message');assert.equal(result.state.moves,travel==='up'?'61':'62',name+' real roundtrip turn progression');}}
  if(travel&&travel!=='up'){assert.ok(graph.coverage.counts.eshk>0,name+' nonempty shopkeeper');assert.ok(graph.coverage.counts.fe>0,name+' nonempty timer');assert.ok(graph.coverage.counts.engr>0,name+' nonempty engraving');assert.ok(graph.coverage.counts.trap>0,name+' nonempty traps');}
  const observation=observations(result);if(!expected){expected=observation;expectedGraph=graph;}else{assert.deepEqual(observation,expected,name+' genuine resumed observations');assert.deepEqual(graph,expectedGraph,name+' complete selected world records and identity edges');}
  evidence.cases.push({name,keys,status:result.status,consumed:result.consumed,moves:result.state.moves,coverage:graph.coverage});
  fs.writeFileSync(output+'/evidence.json',JSON.stringify(evidence,null,2));
 }
}
evidence.complete=true;fs.writeFileSync(output+'/evidence.json',JSON.stringify(evidence,null,2));console.log('PASS '+JSON.stringify(evidence));
