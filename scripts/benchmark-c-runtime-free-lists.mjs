import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
const BASE='28ec0f3a921fe472b505242e1bc005aeba44b700';
const source=execFileSync('git',['show',BASE+':js/c-runtime/heap.js']);
const {CMemory:Baseline}=await import('data:text/javascript;base64,'+source.toString('base64'));
import {CMemory as Candidate} from '../js/c-runtime/heap.js';
const iterations=12000,samples=5;
function prepared(C,count){const m=new C(),addresses=[];for(let i=0;i<count*2+1;i++)addresses.push(m.malloc(16));for(let i=0;i<count*2;i+=2)m.free(addresses[i]);return m;}
function loop(m,n){let checksum=0;for(let i=0;i<n;i++){const p=m.malloc(16);checksum+=p;m.free(p);}return checksum;}
const results={};
for(const count of[1,2,8,64,512]){
    const rows={baseline:[],candidate:[]};
    for(let sample=0;sample<samples;sample++){
        for(const label of sample%2?['candidate','baseline']:['baseline','candidate']){
            const m=prepared(label==='baseline'?Baseline:Candidate,count);loop(m,1000);
            const cpu=process.cpuUsage(),wall=performance.now(),checksum=loop(m,iterations),used=process.cpuUsage(cpu);
            rows[label].push({cpuMs:(used.user+used.system)/1000,wallMs:performance.now()-wall,checksum});
        }
        assert.equal(rows.baseline.at(-1).checksum,rows.candidate.at(-1).checksum);
    }
    const median=a=>[...a].sort((a,b)=>a-b)[Math.floor(a.length/2)];
    const before=median(rows.baseline.map(r=>r.cpuMs)),after=median(rows.candidate.map(r=>r.cpuMs));
    results[count]={baselineMedianCpuMs:before,candidateMedianCpuMs:after,cpuRatio:after/before,samples:rows};
}
const report={node:process.version,iterations,samples,results,scope:'Synthetic fragmented allocation/free loops. Not native or whole-game performance acceptance.'};
fs.writeFileSync('.cache/free-list-benchmark.json',JSON.stringify(report,null,2)+'\n');console.log(JSON.stringify(report,null,2));
