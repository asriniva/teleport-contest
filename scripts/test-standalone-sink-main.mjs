// Replay frozen, original-C-authored natural sink journeys. No adaptive JS inputs.
import fs from 'node:fs';
import path from 'node:path';
import assert from 'node:assert/strict';
import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const reference=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const output='.cache/sink-main';fs.mkdirSync(output,{recursive:true});
const fixturePath='scripts/fixtures/standalone-sink-main.json',fixture=JSON.parse(fs.readFileSync(fixturePath));
const sha=b=>crypto.createHash('sha256').update(b).digest('hex');
function provenance(){
 const files=[];function walk(dir){for(const e of fs.readdirSync(dir,{withFileTypes:true})){const p=dir+'/'+e.name;if(e.isDirectory())walk(p);else if(/\.(?:m?js|json)$/.test(p))files.push(p);}}walk('js');walk('frozen');
 files.push(fixturePath,'scripts/test-standalone-sink-main.mjs','scripts/author-standalone-sink-main.mjs','scripts/full-original-c-run.mjs','scripts/run-standalone-program.mjs','scripts/restoration-world-graph.mjs');
 return Object.fromEntries(files.sort().map(p=>[p,sha(fs.readFileSync(p))]));
}
const before=provenance();
const num=hex=>Number(Buffer.from(hex,'hex').reduce((n,b,i)=>n|(BigInt(b)<<BigInt(8*i)),0n));
let checks=0;const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const normalize=(r,kind)=>({input:r.input,status:r.status,consumed:r.consumed,snapshots:r.snapshots,state:r.state,rngLog:r.rngLog,displayRngLog:r.displayRngLog,stdout:r.stdout,stderr:r.stderr,frames:kind==='c'?r.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})):r.frames});
const evidence={version:1,complete:false,fullGameAccepted:false,sourceSha256:before,referenceReceiptSha256:sha(fs.readFileSync(reference+'/receipt.json')),scope:'Two fixed natural newgame-to-sink journeys reach toxic-waste POLYSELF through actual MAIN, followed by monster-form save and four fresh cross-fed consumers. Original-C author reads the map/input state for route planning; literal replay makes no setup calls or game-state/RNG/input-depth writes. No natural full-game victory claim.',cases:[]};
eq(evidence.referenceReceiptSha256,fixture.referenceReceiptSha256,'exact complete original-C reference');
for(const [p,h]of Object.entries(fixture.authorSourceSha256))eq(before[p],h,'exact original-C author input '+p);
for(const scenario of fixture.cases){
 const runs={};for(const kind of ['c','js']){
  let runtime;const input={...scenario.input,observeRuntime:r=>runtime=r};
  const result=kind==='c'?await runFullOriginalC(reference,input):runStandaloneProgram(reference+'/assets',input);
  fs.writeFileSync(`${output}/${scenario.name}-${kind}-result.json`,JSON.stringify(result));
  eq(result.status,{kind:'input-exhausted'},scenario.name+' '+kind+' live command boundary');eq(result.consumed,scenario.input.keys.length,scenario.name+' '+kind+' consumes only fixed keys');
  const graph=worldGraph(runtime);fs.writeFileSync(`${output}/${scenario.name}-${kind}-world.json`,JSON.stringify(graph));runs[kind]={result,graph};
 }
 const c=runs.c,j=runs.js,text=Buffer.from(c.result.stdout,'base64').toString();
 eq(sha(JSON.stringify(normalize(c.result,'c'))),scenario.originalRecordingSha256,scenario.name+' literal native replay reproduces original adaptive author recording');
 eq(normalize(j.result,'js'),normalize(c.result,'c'),scenario.name+' complete literal inputs, screens/cursors/animations, raw tty, input snapshots and both RNG states/logs');eq(j.graph,c.graph,scenario.name+' complete world identities and scalar fields');
 assert.ok(/rn2\(20\) = 10 @ drinksink\(fountain.c:604\)/.test(c.result.rngLog),scenario.name+' actual toxic-waste RNG branch');checks++;
 assert.ok(c.result.rngLog.includes('@ polyself(polyself.c:'),scenario.name+' actual POLYSELF owner reached');checks++;
 assert.ok(text.includes('freakish metamorphosis'),scenario.name+' source transformation message');checks++;
 const form=num(c.graph.roots.u.umonnum),human=num(c.graph.roots.u.umonster);eq(form,scenario.form,scenario.name+' exact source-selected resulting form');
 if(scenario.name==='newman'){eq(form,human,'actual source newman returns human');assert.ok(c.result.rngLog.includes('@ newman(polyself.c:'),'actual newman policy executed');checks++;}
 else{assert.notEqual(form,human,'actual monster form');assert.ok(num(c.graph.roots.u.mh)>0,'actual monster hitpoints');checks+=2;}
 const rm=num(c.graph.roots.svl.level.locations[scenario.sink[0]*21+scenario.sink[1]].typ);eq(rm,30,scenario.name+' naturally generated sink remains a sink');
 evidence.cases.push({name:scenario.name,input:scenario.input,form,human,sink:scenario.sink,moves:c.result.state.moves,frames:c.result.frames.length,inputBoundaries:c.result.snapshots.length,worldCoverage:c.graph.coverage,recordingSha256:sha(JSON.stringify(normalize(c.result,'c'))),worldSha256:sha(JSON.stringify(c.graph))});
 fs.writeFileSync(output+'/evidence.json',JSON.stringify({...evidence,checks},null,2));
}
const monster=fixture.cases.find(c=>c.name==='monster'),saved={},filename='/nethack/save/0Ada.Z';
for(const kind of ['c','js']){
 const input={...monster.input,keys:monster.input.keys+fixture.monsterSaveSuffix};
 saved[kind]=kind==='c'?await runFullOriginalC(reference,input):runStandaloneProgram(reference+'/assets',input);
 fs.writeFileSync(`${output}/monster-save-${kind}-result.json`,JSON.stringify(saved[kind]));
 eq(saved[kind].status,{kind:'exited',code:0},kind+' actual monster-form save exits');eq(saved[kind].consumed,input.keys.length,kind+' exact save inputs');assert.ok(saved[kind].files[filename],kind+' real compressed save');checks++;
}
eq(normalize(saved.js,'js'),normalize(saved.c,'c'),'actual monster-form save complete recordings and RNG states');
evidence.cases.push({name:'monster-save',keys:monster.input.keys+fixture.monsterSaveSuffix,sourceStreams:Object.fromEntries(['c','js'].map(k=>[k,sha(Buffer.from(saved[k].files[filename].bytes,'base64'))]))});
let resumed;
for(const source of ['c','js'])for(const consumer of ['c','js']){
 let runtime;const name='restore-'+source+'-in-'+consumer,input={...monster.input,keys:fixture.monsterRestoreKeys,files:{[filename]:saved[source].files[filename]},observeRuntime:r=>runtime=r};
 const result=consumer==='c'?await runFullOriginalC(reference,input):runStandaloneProgram(reference+'/assets',input);
 fs.writeFileSync(`${output}/${name}-result.json`,JSON.stringify(result));eq(result.status,{kind:'input-exhausted'},name+' real fresh command boundary');eq(result.consumed,input.keys.length,name+' exact resumed inputs');
 const graph=worldGraph(runtime);fs.writeFileSync(`${output}/${name}-world.json`,JSON.stringify(graph));eq(num(graph.roots.u.umonnum),monster.form,name+' actual restored monster form');eq(result.state.moves,String(Number(evidence.cases.find(c=>c.name==='monster').moves)+1),name+' actual resumed full monster turn');
 const actual={recording:normalize(result,consumer),world:graph};if(!resumed)resumed=actual;else eq(actual,resumed,name+' complete restored recording/world against original-C consumer');
 evidence.cases.push({name,keys:input.keys,form:num(graph.roots.u.umonnum),moves:result.state.moves,frames:result.frames.length,worldCoverage:graph.coverage,recordingSha256:sha(JSON.stringify(actual.recording)),worldSha256:sha(JSON.stringify(graph))});
 fs.writeFileSync(output+'/evidence.json',JSON.stringify({...evidence,checks},null,2));
}
eq(provenance(),before,'production, frozen infrastructure, fixtures and helpers unchanged throughout run');
evidence.complete=true;fs.writeFileSync(output+'/evidence.json',JSON.stringify({...evidence,checks},null,2));console.log('PASS '+JSON.stringify({complete:true,checks,cases:evidence.cases.map(c=>c.name)}));
