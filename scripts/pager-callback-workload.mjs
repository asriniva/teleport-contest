import fs from 'node:fs';
import assert from 'node:assert/strict';
import {performance} from 'node:perf_hooks';
import {spawnSync} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import {resolve} from 'node:path';
import {runStandaloneProgram} from './run-standalone-program.mjs';
const [mode,assets,out,loader]=process.argv.slice(2);
const cases=[['local-look','  n:'],['farlook','  n;  l. '],['cancel','  n;  \x1b'],['symbol','  n/?.\n'],['help','  n?b'+' '.repeat(10)],['repeat-farlook','  n'+';  l. '.repeat(12)]];
if(mode==='capture'){
 const results=[];for(const seed of[1,305419896])for(const[name,keys]of cases){const result=runStandaloneProgram(assets,{seed,timezone:'UTC',options:'OPTIONS=!news\n',keys});assert.deepEqual(result.status,{kind:'input-exhausted'},name);assert.equal(result.consumed,keys.length);results.push({name,result});}fs.writeFileSync(out,JSON.stringify(results));
}else if(mode==='sample'){
 // Whole real input-driven runs, including initialization; no timing instrumentation
 // or argument converter replacement is installed in production execution.
 const scenarios=cases.filter(([n])=>['repeat-farlook','symbol','help'].includes(n));let checksum=0;
 for(const[name,keys]of scenarios){const r=runStandaloneProgram(assets,{seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys});assert.deepEqual(r.status,{kind:'input-exhausted'},name);}
 const start=performance.now();for(const[name,keys]of scenarios){const r=runStandaloneProgram(assets,{seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys});assert.deepEqual(r.status,{kind:'input-exhausted'},name);checksum+=r.frames.length+r.consumed+r.stdout.length;}
 console.log(JSON.stringify({ms:performance.now()-start,checksum}));
}else if(mode==='compare'){
 fs.mkdirSync(out,{recursive:true});for(const name of['before','after']){const r=spawnSync(process.execPath,[...(name==='before'?['--import',resolve(loader)]:[]),fileURLToPath(import.meta.url),'capture',assets,out+'/'+name+'.json'],{encoding:'utf8'});assert.equal(r.status,0,r.stderr);}
 const a=JSON.parse(fs.readFileSync(out+'/before.json')),b=JSON.parse(fs.readFileSync(out+'/after.json'));assert.deepEqual(b,a,'every raw replay result');console.log(JSON.stringify({status:'PASS',cases:b.length,frames:b.reduce((n,r)=>n+r.result.frames.length,0),inputBoundaries:b.reduce((n,r)=>n+r.result.snapshots.length,0),comparison:'complete results including status, raw output, recordings, RNG state/logs, globals and files'}));
}else if(mode==='benchmark'){
 const rounds=Number(process.env.PAGER_BENCH_ROUNDS??9);assert.ok(Number.isSafeInteger(rounds)&&rounds>=3&&rounds%2===1);
 const before=[],after=[];for(let i=0;i<rounds;i++)for(const name of i%2?['after','before']:['before','after']){const r=spawnSync(process.execPath,[...(name==='before'?['--import',resolve(loader)]:[]),fileURLToPath(import.meta.url),'sample',assets],{encoding:'utf8'});assert.equal(r.status,0,r.stderr);(name==='before'?before:after).push(JSON.parse(r.stdout));}
 for(let i=0;i<rounds;i++)assert.equal(before[i].checksum,after[i].checksum);
 const median=a=>[...a].sort((a,b)=>a-b)[Math.floor(a.length/2)],beforeMs=median(before.map(r=>r.ms)),afterMs=median(after.map(r=>r.ms));console.log(JSON.stringify({node:process.version,rounds,beforeMs,afterMs,reductionPercent:100*(1-afterMs/beforeMs),speedup:beforeMs/afterMs,pairedSpeedups:before.map((r,i)=>r.ms/after[i].ms),before,after,scope:'whole real runs: 12 farlooks, symbol lookup and help; includes initialization; one untimed warmup per process'},null,2));
}else throw Error('Usage: pager-callback-workload.mjs <compare|benchmark> <assets> <output-directory> <baseline-loader>');
