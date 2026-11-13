// Fresh bounded inputs, generated here; no sessions, recorder or replay receipt.
import './branch-coverage/reference-setup.mjs';
import fs from 'node:fs';import assert from 'node:assert/strict';import {gzipSync} from 'node:zlib';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory='.cache/full-original-c-v1',out='.cache/keyboard-branches';fs.mkdirSync(out,{recursive:true});let checks=0,cases=0;
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
for(const seed of [1,2,3,4])for(const [role,alignment]of [['Archeologist','lawful'],['Tourist','neutral']]){
 const name=role+'-'+seed,keys='  n'+['h','j','k','l','y','u','b','n','.','m.','i ','I* '].join('').repeat(2),input={seed,timezone:'UTC',options:'OPTIONS=!news\n',argv:['-u','Ada-male-'+alignment,'-p',role,'-r','human'],keys,maxInputBoundaries:512};let native,actual;
 const c=await runFullOriginalC(directory,{...input,observeRuntime:r=>native=r}),j=runStandaloneProgram(directory+'/assets',{...input,observeRuntime:r=>actual=r});
 assert.ok(c.status.kind==='input-exhausted'||(c.status.kind==='exited'&&c.status.code===0),name+' reference completed without failure');checks++;
 for(const key of ['status','consumed','snapshots','state','stdout','stderr','rngLog','displayRngLog'])equal(j[key],c[key],name+' complete '+key);
 equal(actual.program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),name+' every terminal boundary');
 let world=null;
 if(c.status.kind==='input-exhausted'&&c.state.hp>0){world=worldGraph(native);equal(worldGraph(actual),world,name+' complete live world/identity graph');}
 fs.writeFileSync(out+'/'+name+'.json.gz',gzipSync(JSON.stringify({input,c,j,world,recorderRun:false})));
 cases++;console.log('PASS '+name+' '+c.consumed+' keys, '+c.frames.length+' frames, '+c.status.kind);
}
assert.equal(cases,8);fs.writeFileSync(out+'/evidence.json',JSON.stringify({cases,checks,recorderRun:false,scope:'Eight fresh generated finite keyboard inputs; complete C/JS boundary/state/RNG/TTY equivalence, plus complete live world at alive input exhaustion. Post-death cleanup graphs and arbitrary key sequences are not claimed.'},null,2)+'\n');
console.log('PASS:'+cases+' original-C / pure-JS generated keyboard scenarios; '+checks+' comparisons; no recorded input.');
