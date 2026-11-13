// Separate-process alternating baseline/candidate samples; setup excluded.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {performance} from 'node:perf_hooks';
import {spawnSync} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import {resolve} from 'node:path';
import {setupMonsterData} from './monster-data-view-harness.mjs';
const [mode,loader]=process.argv.slice(2),count=Number(process.env.BENCH_ITERATIONS??40000);
if(mode==='sample'){
 const x=setupMonsterData(),{env,entry,mon,species}=x,pm=species[0],L=entry.environment;
 let sink=0;
 function run(n){for(let i=0;i<n;i++){let value;switch(i%4){case 0:value=env.services.set_mon_data(mon,pm);break;case 1:value=env.services.mon_learns_traps(mon,L.PIT);break;case 2:value=env.services.attacktype(pm,L.AT_BITE);break;default:value=env.services.attacktype_fordmg(pm,L.AT_BITE,L.AD_ANY);}sink=(sink+Number(value?.address??value??0))|0;}}
 run(20000);const start=performance.now();run(count);const ms=performance.now()-start;
 console.log(JSON.stringify({count,ms,sink}));
}else{
 if(mode!=='compare'||!loader)throw Error('Usage: benchmark-monster-mixed.mjs compare <before-loader>');
 const results={before:[],after:[]},rounds=9;
 for(let i=0;i<rounds;i++)for(const name of i%2?['after','before']:['before','after']){
  const child=spawnSync(process.execPath,[...(name==='before'?['--import',resolve(loader)]:[]),fileURLToPath(import.meta.url),'sample'],{encoding:'utf8'});
  assert.equal(child.status,0,child.stderr);results[name].push(JSON.parse(child.stdout));
 }
 for(let i=0;i<rounds;i++)assert.equal(results.before[i].sink,results.after[i].sink,'observed return checksum');
 const median=a=>[...a].sort((a,b)=>a-b)[Math.floor(a.length/2)],beforeMs=median(results.before.map(r=>r.ms)),afterMs=median(results.after.map(r=>r.ms));
 console.log(JSON.stringify({node:process.version,platform:process.platform,arch:process.arch,rounds,callsPerSample:count,warmupCalls:20000,beforeMs,afterMs,speedup:beforeMs/afterMs,reductionPercent:100*(1-afterMs/beforeMs),pairedSpeedups:results.before.map((r,i)=>r.ms/results.after[i].ms),results},null,2));
}
