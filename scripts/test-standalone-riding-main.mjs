// Natural Knight startup and literal MAIN inputs only. Observers never write game state.
import fs from 'node:fs';
import path from 'node:path';
import assert from 'node:assert/strict';
import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';

const reference=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const output='.cache/riding-main';fs.mkdirSync(output,{recursive:true});
const number=hex=>Number(Buffer.from(hex,'hex').reduce((n,b,i)=>n|(BigInt(b)<<BigInt(i*8)),0n));
const sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
function sourceHashes(){
 const files=[];function walk(dir){for(const entry of fs.readdirSync(dir,{withFileTypes:true})){const p=dir+'/'+entry.name;if(entry.isDirectory())walk(p);else if(/\.(?:m?js|json)$/.test(p))files.push(p);}}walk('js');
 files.push('scripts/test-standalone-riding-main.mjs','scripts/fixtures/standalone-riding-main.json','scripts/run-standalone-program.mjs','scripts/full-original-c-run.mjs','scripts/restoration-world-graph.mjs');
 return Object.fromEntries(files.sort().map(p=>[p,sha(fs.readFileSync(p))]));
}
const before=sourceHashes();
const profile={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',argv:['-u','Ada-male-lawful','-p','Knight','-r','human']};
let checks=0;const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
async function run(kind,keys,name,files={}){
 let runtime;const input={...profile,keys,files,observeRuntime:value=>runtime=value};
 const result=kind==='c'?await runFullOriginalC(reference,input):runStandaloneProgram(reference+'/assets',input);
 fs.writeFileSync(`${output}/${name}-${kind}-result.json`,JSON.stringify(result));
 assert.notEqual(result.status.kind,'failed',kind+' '+name+' must execute');
 const graph=result.status.kind==='input-exhausted'?worldGraph(runtime):null;
 if(graph)fs.writeFileSync(`${output}/${name}-${kind}-world.json`,JSON.stringify(graph));
 return {result,graph};
}
const normalize=(r,kind)=>({status:r.status,consumed:r.consumed,snapshots:r.snapshots,state:r.state,rngLog:r.rngLog,displayRngLog:r.displayRngLog,stdout:r.stdout,stderr:r.stderr,frames:kind==='c'?r.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})):r.frames});
const native=await run('c','  n','natural-startup');
eq(native.result.status,{kind:'input-exhausted'},'genuine Knight reaches first command');
const hero=native.graph.roots.u,position=[number(hero.ux),number(hero.uy)];
const pets=Object.entries(native.graph.nodes).filter(([id,n])=>/^mon:\d+$/.test(id)&&number(n.mtame)>0).map(([id,n])=>({id,position:[number(n.mx),number(n.my)],tameness:number(n.mtame),inventory:n.minvent}));
if(process.argv.includes('--discover')){console.log(JSON.stringify({profile,position,pets}));process.exit(0);}
const fixture=JSON.parse(fs.readFileSync('scripts/fixtures/standalone-riding-main.json'));
eq(profile,fixture.profile,'fixed original-C scenario profile');eq(position,fixture.position,'natural hero position');eq(pets,fixture.pets,'natural saddled pet identity and position');
const evidence={version:1,complete:false,fullGameAccepted:false,scope:'Natural Knight riding through literal MAIN commands and four fresh cross-fed mounted save consumers; no wishes, setup policy calls, raw game writes or input-state cleanup. This bounded interaction is not natural full-game victory.',sourceSha256:before,fixtureSha256:sha(fs.readFileSync('scripts/fixtures/standalone-riding-main.json')),referenceReceiptSha256:sha(fs.readFileSync(reference+'/receipt.json')),cases:[]};
for(const scenario of fixture.cases){
 const c=await run('c',scenario.keys,scenario.name),j=await run('js',scenario.keys,scenario.name);
 eq(c.result.status,{kind:'input-exhausted'},scenario.name+' native command boundary');eq(c.result.consumed,scenario.keys.length,scenario.name+' exact literal inputs');
 eq(normalize(j.result,'js'),normalize(c.result,'c'),scenario.name+' complete recording, input snapshots, both RNG states and logs, raw terminal');eq(j.graph,c.graph,scenario.name+' complete world identity graph');
 eq(c.graph.roots.u.usteed,scenario.mounted?{$ref:fixture.pets[0].id}:null,scenario.name+' actual source riding state');
 if(scenario.position)eq([c.result.state.x,c.result.state.y],scenario.position,scenario.name+' actual mounted movement');
 for(const message of scenario.messages){assert.ok(Buffer.from(c.result.stdout,'base64').toString().includes(message),scenario.name+' source message '+message);checks++;}
 evidence.cases.push({name:scenario.name,keys:scenario.keys,mounted:scenario.mounted,moves:c.result.state.moves,frames:c.result.frames.length,inputBoundaries:c.result.snapshots.length,worldCoverage:c.graph.coverage,recordingSha256:sha(JSON.stringify(normalize(c.result,'c'))),worldSha256:sha(JSON.stringify(c.graph))});
 fs.writeFileSync(output+'/evidence.json',JSON.stringify({...evidence,checks},null,2));
}
const saved={};const filename='/nethack/save/0Ada.Z';
for(const kind of ['c','js']){
 saved[kind]=await run(kind,fixture.saveKeys,'mounted-save');
 eq(saved[kind].result.status,{kind:'exited',code:0},kind+' mounted save exits');eq(saved[kind].result.consumed,fixture.saveKeys.length,kind+' literal save input');assert.ok(saved[kind].result.files[filename],kind+' source-generated compressed save');checks++;
}
eq(normalize(saved.js.result,'js'),normalize(saved.c.result,'c'),'mounted save complete recordings and RNG states');
evidence.cases.push({name:'mounted-save',keys:fixture.saveKeys,sourceStreams:Object.fromEntries(['c','js'].map(k=>[k,sha(Buffer.from(saved[k].result.files[filename].bytes,'base64'))]))});
let resumed;
for(const source of ['c','js'])for(const consumer of ['c','js']){
 const name='restore-'+source+'-in-'+consumer,value=await run(consumer,fixture.restoreKeys,name,{[filename]:saved[source].result.files[filename]});
 eq(value.result.status,{kind:'input-exhausted'},name+' fresh actual command boundary');eq(value.result.consumed,fixture.restoreKeys.length,name+' exact literal restore/dismount inputs');
 eq(value.graph.roots.u.usteed,null,name+' actual post-restore dismount');assert.ok(Buffer.from(value.result.stdout,'base64').toString().includes("You've been through the dungeon on a pony with no name."),name+' source dismount confirms restored riding state');checks++;
 const actual={recording:normalize(value.result,consumer),world:value.graph};if(!resumed)resumed=actual;else eq(actual,resumed,name+' complete recording/world against fresh original-C consumer');
 evidence.cases.push({name,keys:fixture.restoreKeys,moves:value.result.state.moves,frames:value.result.frames.length,worldCoverage:value.graph.coverage,recordingSha256:sha(JSON.stringify(actual.recording)),worldSha256:sha(JSON.stringify(actual.world))});
 fs.writeFileSync(output+'/evidence.json',JSON.stringify({...evidence,checks},null,2));
}
eq(sourceHashes(),before,'all production/test inputs unchanged during run');
evidence.complete=true;fs.writeFileSync(output+'/evidence.json',JSON.stringify({...evidence,checks},null,2));console.log('PASS '+JSON.stringify({...evidence,checks}));
