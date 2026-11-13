import assert from 'node:assert/strict';
import {performance} from 'node:perf_hooks';
import {setupMonsterData} from './monster-data-view-harness.mjs';
const x=setupMonsterData(),{env,entry,mon,species}=x,pm=species[0],L=entry.environment;
const count=Number(process.env.BENCH_ITERATIONS??20000),rounds=11;
let sink=0;
const checksum=value=>{sink=(sink+Number(value?.address??value??0))|0;};
const cases={
 'set_mon_data/views':()=>env.services.set_mon_data(mon,pm),
 'mon_learns_traps/views':()=>env.services.mon_learns_traps(mon,L.PIT),
 'attacktype/views':()=>env.services.attacktype(pm,L.AT_BITE),
 'attacktype_fordmg/views':()=>env.services.attacktype_fordmg(pm,L.AT_BITE,L.AD_ANY),
 'mixed/views':i=>{switch(i%4){case 0:return env.services.set_mon_data(mon,pm);case 1:return env.services.mon_learns_traps(mon,L.PIT);case 2:return env.services.attacktype(pm,L.AT_BITE);default:return env.services.attacktype_fordmg(pm,L.AT_BITE,L.AD_ANY);}},
 'mixed/pointers':i=>{switch(i%4){case 0:return env.services.set_mon_data(mon.address,pm.address);case 1:return env.services.mon_learns_traps(mon.address,L.PIT);case 2:return env.services.attacktype(pm.address,L.AT_BITE);default:return env.services.attacktype_fordmg(pm.address,L.AT_BITE,L.AD_ANY);}},
};
function run(body,prepare){entry.prepareArgs=prepare;mon.data=pm;mon.movement=12;let value=0;const start=performance.now();for(let i=0;i<count;i++){const result=body(i);value=(value+Number(result?.address??result??0))|0;}const ms=performance.now()-start;checksum(value);return ms;}
const median=xs=>[...xs].sort((a,b)=>a-b)[Math.floor(xs.length/2)],results=[];
for(const [name,body]of Object.entries(cases)){
 for(let i=0;i<4;i++){run(body,x.baseline);run(body,x.optimized);}
 const before=[],after=[];
 for(let i=0;i<rounds;i++){
  if(i%2){after.push(run(body,x.optimized));before.push(run(body,x.baseline));}
  else{before.push(run(body,x.baseline));after.push(run(body,x.optimized));}
 }
 const baselineMs=median(before),optimizedMs=median(after);
 results.push({name,callsPerSample:count,rounds,baselineMs,optimizedMs,speedup:baselineMs/optimizedMs,reductionPercent:(1-optimizedMs/baselineMs)*100,pairedSpeedupRange:[Math.min(...before.map((v,i)=>v/after[i])),Math.max(...before.map((v,i)=>v/after[i]))],baselineSamplesMs:before,optimizedSamplesMs:after});
 console.error(JSON.stringify({completed:name,speedup:baselineMs/optimizedMs}));
}
entry.prepareArgs=x.optimized;assert.ok(Number.isInteger(sink));
console.log(JSON.stringify({node:process.version,platform:process.platform,arch:process.arch,comparison:'full registered JS calls, original argument conversion versus store-owned view reuse; setup excluded; alternating order after warmup',results,sink},null,2));
