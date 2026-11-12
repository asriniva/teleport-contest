// Isolated function benchmarks, not a whole-game performance acceptance gate.
import assert from 'node:assert/strict';
import {execFileSync} from 'node:child_process';
import {CMemory,createBitfields,createCTypes} from '../js/c-runtime/index.js';
import {createAddressBindings} from '../js/c-runtime/address-bindings.js';
const base='a2adb495bee21ccbc2ceb9ead95a8083be342df0';
const oldTypes=execFileSync('git',['show',base+':js/c-runtime/types.js'],{encoding:'utf8'})
    .replace("'./memory.js'",JSON.stringify(new URL('../js/c-runtime/memory.js',import.meta.url).href));
const oldBindings=execFileSync('git',['show',base+':js/c-runtime/address-bindings.js'],{encoding:'utf8'});
const moduleFrom=source=>import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
const previous=[(await moduleFrom(oldTypes)).createCTypes,(await moduleFrom(oldBindings)).createAddressBindings];
function fixture([typesFactory,bindingsFactory]) {
    const memory=new CMemory(),metadata={records:{point:{size:8,fields:{x:{offset:0,ctype:'int'},y:{offset:4,ctype:'int'}}}}};
    const types=typesFactory(memory,metadata,createBitfields(memory,metadata)),at=memory.calloc(1,8);
    types.setField('struct point',at,'x','int',42);
    const schema={globals:[],schema:{point:{ctype:'struct point',fields:[{name:'x',canonical:'int'}]}}};
    const bindings=bindingsFactory({environment:{ctypes:types,memory,services:{},transport:{}},name:'bench',schema,layout:[],namespace:{},backings:[],publicFunctions:{functions:{}}}).services;
    return {types,at,bindings};
}
const cases={
    description:f=>f.types.record('struct point').size,
    fieldRead:f=>f.types.getField('struct point',f.at,'x','int'),
    bindingRead:f=>f.bindings.read(0,f.at,0),
    bindingAddress:f=>f.bindings.address(0,f.at,0),
    fieldWrite:f=>{f.types.setField('struct point',f.at,'x','int',42);return 42;},
};
const iterations=250000,samples=5,results={};
function measure(fn,f,count) {
    let checksum=0;const cpu=process.cpuUsage(),start=performance.now();
    for(let i=0;i<count;i++)checksum+=fn(f);
    const used=process.cpuUsage(cpu);
    return {wallMs:performance.now()-start,cpuMs:(used.user+used.system)/1000,checksum};
}
const median=values=>[...values].sort((a,b)=>a-b)[Math.floor(values.length/2)];
for(const[name,fn]of Object.entries(cases)) {
    const rows={baseline:[],candidate:[]};
    for(let sample=0;sample<samples;sample++) {
        const order=sample%2?['candidate','baseline']:['baseline','candidate'];
        for(const label of order) {
            const f=fixture(label==='baseline'?previous:[createCTypes,createAddressBindings]);
            measure(fn,f,20000);rows[label].push(measure(fn,f,iterations));
        }
        assert.equal(rows.baseline.at(-1).checksum,rows.candidate.at(-1).checksum);
    }
    const before=median(rows.baseline.map(r=>r.cpuMs)),after=median(rows.candidate.map(r=>r.cpuMs));
    results[name]={medianBaselineCpuMs:before,medianCandidateCpuMs:after,cpuRatio:after/before,samples:rows};
}
console.log(JSON.stringify({base,node:process.version,iterations,sampleCount:samples,results,scope:'Alternating isolated function measurements. No whole-game speed or deadline acceptance.'},null,2));
