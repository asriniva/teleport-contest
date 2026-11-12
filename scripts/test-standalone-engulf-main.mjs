// Connected original-C/JS engulf through literal MAIN input, with no policy calls
// or game-memory writes from the fixture. Wizard form/target setup is explicit.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import crypto from 'node:crypto';
import {gzipSync} from 'node:zlib';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {elementalSourceSnapshot} from './elemental-source-provenance.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';

const fixture='scripts/fixtures/standalone-engulf-main.json';
const reference='.cache/full-original-c-v1',out='.cache/engulf-main';
const input=JSON.parse(fs.readFileSync(fixture));
assert.ok(input.argv.includes('-D'),'Explicit original wizard setup');
assert.equal(input.files,undefined,'No injected world/save files');
const snapshot=()=>elementalSourceSnapshot(reference,[
    'scripts/test-standalone-engulf-main.mjs','scripts/author-standalone-engulf.mjs',
],[fixture]);
const before=snapshot();
let native,standalone,checks=0;
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
fs.mkdirSync(out,{recursive:true});
const c=await runFullOriginalC(reference,{...input,observeRuntime:r=>native=r});
const j=runStandaloneProgram(reference+'/assets',{...input,observeRuntime:r=>standalone=r});
for(const [name,result]of [['c',c],['js',j]])
    fs.writeFileSync(out+'/'+name+'-result.json.gz',gzipSync(JSON.stringify(result)));
equal(c.status,{kind:'input-exhausted'},'Native MAIN reaches final live input');
equal(c.consumed,input.keys.length,'All literal native keys consumed');
const normalize=(r,kind)=>({
    status:r.status,consumed:r.consumed,snapshots:r.snapshots,state:r.state,
    rngLog:r.rngLog,displayRngLog:r.displayRngLog,stdout:r.stdout,stderr:r.stderr,
    frames:kind==='c'?r.frames.map(({screen,cursor,animation})=>({
        screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation,
    })):r.frames,
});
const expected=normalize(c,'c'),actual=normalize(j,'js');
for(const name of Object.keys(expected))equal(actual[name],expected[name],'Complete '+name);
const text=Buffer.from(c.stdout,'base64').toString().replace(/\x1b\[[0-?]*[ -/]*[@-~]/g,'');
assert.match(text,/swallow[^\n]*troll/i,'Original attack reaches start_engulf message');checks++;
const engulfAnimations=c.frames.filter(f=>f.animation&&/swallow[^\n]*troll/i.test(f.screen));
assert.ok(engulfAnimations.length>=2,'Both original start_engulf animation boundaries');checks++;
equal(worldGraph(standalone),worldGraph(native),'Complete live world after original engulf');
equal(snapshot(),before,'Production/fixture/reference sources unchanged across comparison');
const sha=value=>crypto.createHash('sha256').update(value).digest('hex');
fs.writeFileSync(out+'/evidence.json',JSON.stringify({
    version:1,complete:true,originalNativeCompared:true,fullGameAccepted:false,
    sourcePolicyCallsFromFixture:0,rawGameWrites:0,debugSetup:true,checks,
    input,consumed:c.consumed,moves:c.state.moves,frames:c.frames.length,
    engulfAnimationBoundaries:engulfAnimations.length,
    recordingSha256:sha(JSON.stringify(expected)),sourceProvenance:before,
    scope:'Literal original MAIN controlled-polymorph/monster-creation commands followed by an actual hero engulf. Complete recordings, RNG, state, snapshots and live world match. No ordinary full-game journey claim.',
},null,2)+'\n');
console.log('PASS '+JSON.stringify({checks,consumed:c.consumed,engulfAnimationBoundaries:engulfAnimations.length}));
