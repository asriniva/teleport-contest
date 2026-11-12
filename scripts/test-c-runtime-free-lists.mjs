// Differential allocator contracts against an immutable preceding implementation.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
const BASE='28ec0f3a921fe472b505242e1bc005aeba44b700';
const source=execFileSync('git',['show',BASE+':js/c-runtime/heap.js']);
const {CMemory:Baseline}=await import('data:text/javascript;base64,'+source.toString('base64'));
import {CMemory as Candidate} from '../js/c-runtime/heap.js';
const results={checks:0,steps:0,scope:'Synthetic differential allocator experiment; not native or recorder acceptance.'};
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);results.checks++;};
function pair(){return[Baseline,Candidate].map(C=>new C({initialBytes:128,maximumBytes:131072}));}
function state(a,b,aliases,step){
    equal([a.end,a.generation,a.buffer.byteLength],[b.end,b.generation,b.buffer.byteLength],'extent '+step);
    equal([...a.live],[...b.live],'live '+step);equal(a.available,b.available,'free '+step);
    for(const[x,y]of aliases)equal(x,y,'historical free-list alias '+step);
    if(step%101===0){equal(a.HEAPU8,b.HEAPU8,'all bytes '+step);for(const[x,y]of aliases)equal(x.map(p=>a.available.includes(p)),y.map(p=>b.available.includes(p)),'retained block identities '+step);}
}
function call(a,b,op,args,aliases,step){
    const old=[a.available,b.available];
    const run=m=>{try{return{value:m[op](...args)};}catch(e){return{error:{name:e.name,message:e.message}};}};
    const x=run(a),y=run(b);equal(x,y,op+' result '+step);
    equal(a.available===old[0],b.available===old[1],op+' current-array identity '+step);
    aliases.push(old);if(aliases.length>8)aliases.shift();state(a,b,aliases,step);results.steps++;return x.value;
}
{
    const[a,b]=pair(),aliases=[],addresses=[];let step=0;
    for(let i=0;i<5;i++)addresses.push(call(a,b,'malloc',[16],aliases,step++));
    for(const i of[1,3,2,0,4])call(a,b,'free',[addresses[i]],aliases,step++);
    const p=call(a,b,'malloc',[32],aliases,step++);call(a,b,'realloc',[p,96],aliases,step++);
}
for(const seed of[1,2,0x12345678,0xfedcba98]){
    const[a,b]=pair(),aliases=[];let random=seed>>>0;
    const next=()=>{random^=random<<13;random^=random>>>17;random^=random<<5;return random>>>0;};
    for(let step=0;step<20000;step++){
        const live=[...a.live.keys()],choice=next()%100;
        if(live.length>128||choice<30&&live.length){
            const p=live[next()%live.length];call(a,b,'free',[p],aliases,step);
        }else if(choice<45&&live.length){
            const p=live[next()%live.length],size=next()%768;call(a,b,'realloc',[p,size],aliases,step);
        }else if(choice<90){
            const size=next()%512,p=call(a,b,'malloc',[size],aliases,step);
            if(p){const byte=next()&255;a.HEAPU8.fill(byte,p,p+size);b.HEAPU8.fill(byte,p,p+size);}
        }else{
            const count=next()%32,size=next()%16;call(a,b,'calloc',[count,size],aliases,step);
        }
        if(step%137===0)for(const p of[0,-1,1,NaN,Infinity,0n,'16'])call(a,b,'free',[p],aliases,step);
        if(step%257===0)for(const size of[-1,0,1.5,NaN,Infinity,1n,2**30])call(a,b,'malloc',[size],aliases,step);
    }
    equal(a.HEAPU8,b.HEAPU8,'final bytes seed '+seed);
}
fs.writeFileSync('.cache/free-list-differential.json',JSON.stringify(results,null,2)+'\n');
console.log('PASS '+JSON.stringify(results));
