// Generated inputs; original compiled C supplies every expected result.
import assert from 'node:assert/strict';
import {readFileSync, mkdirSync, writeFileSync} from 'node:fs';
import {fileURLToPath, pathToFileURL} from 'node:url';
import path from 'node:path';
import {createPortedRuntime} from '../js/ported/wasm-runtime.js';
import {C} from '../js/ported/c-runtime.js';

const root=fileURLToPath(new URL('../',import.meta.url));
const directory=path.resolve(process.env.TELEPORT_NHLSEL_PROBE_DIR||path.join(root,'.cache/tu-probes'));
const layouts=JSON.parse(readFileSync(path.join(root,'js/wasm/tu-layouts.json')));
const referenceFactory=(await import(pathToFileURL(path.join(directory,'nhlsel-reference.mjs')))).default;
const hybridFactory=(await import(pathToFileURL(path.join(directory,'nhlsel-hybrid.mjs')))).default;
const reference=await referenceFactory();
const hybrid=await hybridFactory({nethackPorted:createPortedRuntime(layouts)});
const text=(m,p)=>{const heap=m.HEAPU8;let at=Number(p),end=at;while(heap[end])end++;return Buffer.from(heap.subarray(at,end)).toString();};
const results=[];
function scenario(seed,label,program) {
    const states=[reference,hybrid].map(m=>{
        m._probe_reset(seed);
        const stack=m._probe_stack();
        const input=Buffer.from(program+'\0');
        assert(input.length<32768);
        m.HEAPU8.set(input,Number(m._probe_input()));
        const code=m._probe_run();
        assert.equal(m._probe_stack(),stack,'caller stack: '+label);
        assert.equal(C,undefined,'restored JS environment: '+label);
        return {code,trace:text(m,m._probe_trace()),snapshot:text(m,m._probe_snapshot())};
    });
    assert.deepEqual(states[1],states[0],`seed ${seed}: ${label}`);
    results.push({seed,label,code:states[0].code});
}
for(let i=0;i<32;i++) {
    const seed=(Math.imul(i+1,2654435761)>>>0);
    const x=2+i%9,y=1+i%7,dx=1+i%4,dy=1+i%3;
    const points=Array.from({length:12},(_,n)=>`s:set(${1+(i*7+n*11)%78},${(i*3+n*5)%21},${n%3?1:0})`).join(';');
    scenario(seed,'point mutation and deep clones',`local s=selection.new();${points};local c=s:clone();c:set(${x},${y});return s,c,s:numpoints(),c:numpoints(),s:bounds(),c:bounds()`);
    for(const operator of ['&','|','~','-','+'])
        scenario(seed,'binary '+operator,`local a=selection.fillrect(${x},${y},${x+dx},${y+dy});local b=selection.rect(${x+1},${y},${x+dx+2},${y+dy+1});local c=a ${operator} b;return a,b,c,c:numpoints(),c:bounds()`);
    for(const fn of ['line','rect','fillrect'])
        scenario(seed,fn+' with existing selection',`local s=selection.new();local out=selection.${fn}(s,${x},${y},${x+dx},${y+dy});return s,out,out:describe_size()`);
    for(const percent of [0,25,100])
        scenario(seed,'percentage '+percent,`local s=selection.fillrect(${x},${y},${x+dx+2},${y+dy+2}):percentage(${percent});local x,y=s:rndcoord(1);return s,x,y,s:numpoints()`);
    for(const direction of ['north','west','east','south','all','random'])
        scenario(seed,'grow '+direction,`local s=selection.set(${x},${y});return s:grow('${direction}'),s:numpoints()`);
    scenario(seed,'nested callback reentry',`local s=selection.fillrect(${x},${y},${x+dx},${y+dy});local out=selection.new();s:iterate(function(x,y) local t=selection.set(x,y):clone();if t:get(x,y)~=0 then out:set(x,y) end end);return s,out,out:numpoints()`);
    scenario(seed,'defined negate method',`local s=selection.fillrect(${x},${y},${x+dx},${y+dy});local n=s:negate();return s,n,s:numpoints(),n:numpoints()`);
}
// Unary ~s/-s are deliberately kept in the separately reported upstream-UAF
// witness. They are not represented as passing or repaired by this corpus.
const output=path.join(root,'.cache/nhlsel-current-run');mkdirSync(output,{recursive:true});
writeFileSync(path.join(output,'generated-results.json'),JSON.stringify({status:'PASS',cases:results.length,reference:'original Emscripten C',dispatcher:'production createPortedRuntime',upstreamUnaryAliasUaf:'preserved; separate known-failure witness',results},null,2)+'\n');
console.log(`NHLSEL generated: ${results.length} original-C/shared-JS scenarios passed across 32 seeds; complete state/trace/return/stack comparisons.`);
