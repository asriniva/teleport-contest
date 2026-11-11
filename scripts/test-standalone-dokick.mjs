// Genuine ordinary main locked-door kick; no direct source policy calls/state writes.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const fixture='.cache/native-deeper-bones-sam3',accepted=JSON.parse(fs.readFileSync(fixture+'/replay-evidence.json'));
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
assert.ok(accepted.nativeProducerFixtureAccepted&&accepted.literalReplayAccepted);
assert.equal(sha(fixture+'/input.json'),accepted.fixtureSha256);
const abi=JSON.parse(fs.readFileSync('js/standalone/dokick-abi.json'));let hashes=0,checks=0;
for(const[file,hash]of Object.entries(abi.sourceSha256)){assert.equal(sha(file),hash,file);hashes++;}
for(const[file,hash]of Object.entries(abi.referenceHeaderSha256)){assert.equal(sha(file),hash,file);hashes++;}
const source=JSON.parse(fs.readFileSync(fixture+'/input.json')),input={...source,keys:source.keys.slice(0,81)};
assert.equal(input.keys[77],String.fromCharCode(4),'ordinary actual kick command is included');
let cr,jr;
const c=await runFullOriginalC(directory,{...input,observeRuntime:r=>{cr=r;}}),j=runStandaloneProgram(directory+'/assets',{...input,observeRuntime:r=>{jr=r;}});
fs.mkdirSync('.cache/standalone-dokick',{recursive:true});
for(const[name,result]of [['c',c],['js',j]])fs.writeFileSync('.cache/standalone-dokick/'+name+'-result.json',JSON.stringify(result,null,2)+'\n');
const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
eq(j.status,{kind:'input-exhausted'},'actual source main completes kicking and reaches next real input');
assert.match(c.rngLog,/@ kick_door\(dokick\.c:/,'actual original locked-door kick executes its RNG');checks++;
const observations=(r,native)=>({status:r.status,consumed:r.consumed,snapshots:r.snapshots,state:r.state,rngLog:r.rngLog,displayRngLog:r.displayRngLog,stdout:r.stdout,stderr:r.stderr,frames:native?r.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})):r.frames});
eq(observations(j,false),observations(c,true),'complete genuine main recording including source kick output and all scalar/dualRNG state');
const cw=worldGraph(cr),jw=worldGraph(jr);
for(const[name,world]of [['c',cw],['js',jw]])fs.writeFileSync('.cache/standalone-dokick/'+name+'-world.json',JSON.stringify(world,null,2)+'\n');
eq(jw,cw,'actual source door/terrain, hero, object and monster named fields/pointer graph');
for(const name of ['obj_delivery','ship_object','down_gate']){assert.equal(jr.environment.hasFunction(name),true,'preserved delivery public '+name);checks++;}
const result={checks,hashes,profile:'Male lawful human Samurai seed3 ordinary full-main locked-door kick and input boundary',moves:j.state.moves,consumed:j.consumed,frames:j.frames.length,worldCoverage:jw.coverage,completeDokickAccepted:false,providerSha256:sha('js/standalone/dokick.js'),testSha256:sha('scripts/test-standalone-dokick.mjs'),limitation:'Only this genuine ordinary door-kick path and exact connected recording/world are accepted. Object/monster kicks, watchman effects, traps, special terrain and other source branches remain unaccepted.'};
fs.writeFileSync('.cache/standalone-dokick/evidence.json',JSON.stringify(result,null,2)+'\n');console.log('PASS '+JSON.stringify(result));
