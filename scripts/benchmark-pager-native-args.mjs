import fs from 'node:fs';import assert from 'node:assert/strict';import {execFileSync} from 'node:child_process';import {performance} from 'node:perf_hooks';
import {setupMonsterData} from './monster-data-view-harness.mjs';
const x=setupMonsterData(),{env,views,mon}=x,file='js/nethack/pager-lookup.js';
const extract=s=>{const m=s.match(/const nativeArg=([\s\S]*?);\n const locate=/);assert.ok(m);return Function('ctypes','transport','views','address','return '+m[1])(env.ctypes,env.transport,views,env.address);};
const a=extract(execFileSync('git',['show','3b6db96:'+file],{encoding:'utf8'})),b=extract(fs.readFileSync(file,'utf8'));
// Repeated types reflect the observed farlook scalar mix; include real record
// and opaque pointer inputs too. These are converter timings, not gameplay.
const values=[...Array(159).fill(['char',65]),...Array(70).fill(['int',256]),...Array(28).fill(['short',12]),...Array(18).fill(['unsigned long',123n]),['signed char',-1],['unsigned int',1],['unsigned int',2],['struct monst *',mon],['char *',mon.address]];
const n=40000,before=[],after=[];let sink=0;
function run(fn){let sum=0;const t=performance.now();for(let i=0;i<n;i++){const[type,value]=values[i%values.length],v=fn(type,value);sum=(sum+Number(v?.address??v))|0;}const ms=performance.now()-t;sink^=sum;return{ms,sum};}
for(let i=0;i<3;i++){run(a);run(b);}
for(let i=0;i<9;i++){let aa,bb;if(i%2){bb=run(b);aa=run(a);}else{aa=run(a);bb=run(b);}assert.equal(aa.sum,bb.sum);before.push(aa.ms);after.push(bb.ms);}
const median=a=>[...a].sort((a,b)=>a-b)[4],beforeMs=median(before),afterMs=median(after);
console.log(JSON.stringify({node:process.version,callsPerSample:n,rounds:9,beforeMs,afterMs,speedup:beforeMs/afterMs,reductionPercent:100*(1-afterMs/beforeMs),pairedSpeedups:before.map((v,i)=>v/after[i]),before,after,sink,scope:'actual private argument converters; observed scalar mix plus record/opaque pointers; excludes setup'},null,2));
