// Three real implementations, with native macOS C as the required result.
// Emscripten C is a diagnostic witness, never an alternative expected JS value.
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
process.env.TELEPORT_NATIVE_TESTS='1';
process.env.TZ='UTC';
const {referenceBackend}=await import('./native-test-backend.mjs');
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const observations=[];
function string(module,pointer){let at=Number(pointer),end=at;while(module.HEAPU8[end])end++;
    return Buffer.from(module.HEAPU8.slice(at,end)).toString('latin1');}
function input(module,text,callback){const bytes=Buffer.from(text+'\0'),pointer=module._malloc(BigInt(bytes.length));
    module.HEAPU8.set(bytes,Number(pointer));try{return callback(BigInt(pointer));}finally{module._free(BigInt(pointer));}}
async function modules(name){
    const original=(await import(`../.cache/tu-probes/${name}-reference.mjs`)).default;
    const hybrid=(await import(`../.cache/tu-probes/${name}-hybrid.mjs`)).default;
    const result=[await referenceBackend(name)(),await original(),await hybrid({nethackPorted:createPortedRuntime(layouts)})];
    assert.equal(result[0].nativeC,true,'First reference really executes native C');
    return result;
}
function compare(name,values,differs=true){
    const [native,emscripten,javascript]=values;
    assert.deepEqual(javascript,native,`${name}: JS must match native C`);
    if(differs)assert.notDeepEqual(emscripten,native,`${name}: retain the actual libc difference`);
    else assert.deepEqual(emscripten,native,`${name}: ordinary shared behavior remains equal`);
    observations.push({name,native,emscripten,javascript,differs});
}
const allocation=await modules('alloc');
for(const pointer of [0n,1n,0x20000000000001n])
    compare(`pointer ${pointer}`,allocation.map(m=>string(m,m._probe_format(pointer))),pointer===0n);
const minion=await modules('minion');
for(const text of ['12 trailing','9223372036854775808','-9223372036854775809','9'.repeat(200)]){
    compare(`bribe scan ${text}`,minion.map(m=>{
        m._probe_reset(1);m._probe_cash(9223372036854775807n);
        input(m,text,p=>m._probe_input(p));
        return {offer:m._probe_bribe(),cash:m._probe_cash_value(),trace:string(m,m._probe_trace())};
    }),text!=='12 trailing');
}
const regex=await modules('posixregex');
for(const pattern of ['','[','a{256}','\\bword\\b','^a+$']){
    compare(`regex ${JSON.stringify(pattern)}`,regex.map(m=>{
        const expression=BigInt(m._probe_init()),buffer=BigInt(m._malloc(1024n));
        try{
            const compiled=input(m,pattern,p=>m._probe_compile(p,expression));
            const status=m._probe_err(expression);
            m._probe_error(expression,buffer);
            const error=string(m,buffer);
            const matched=compiled?input(m,'word',p=>m._probe_match(p,expression)):null;
            return {compiled,status,error,matched};
        }finally{m._probe_free(expression);m._free(buffer);}
    }),pattern!=='^a+$');
}
const calendar=await modules('calendar');
for(const date of ['01000101000000','20000110090000'])
    compare(`calendar ${date}`,calendar.map(m=>input(m,date,p=>m._probe_parse(p))),date[0]==='0');
writeFileSync(new URL('../.cache/native-library-differences.json',import.meta.url),
    JSON.stringify(observations,(_,v)=>typeof v==='bigint'?v.toString():v,2)+'\n');
console.log(`Native library differences: ${observations.length} three-way cases passed; JS equals native C, with Emscripten differences retained explicitly.`);
