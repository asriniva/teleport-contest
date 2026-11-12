// Original C remains the oracle; implementation and its stdio are JS-only.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import {createProbe,createReference} from './pure-js-fixtures/load.mjs';
const modules=[await createReference('nhlobj'),await createProbe('nhlobj')];
const text=(m,p)=>{let end=Number(p);while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(Number(p),end)).toString();};
const cases=[
 "return io.type(io.stdin)..':'..io.type(io.stdout)..':'..io.type(io.stderr)",
 "return tostring(io.type({}))",
 "local f=assert(io.tmpfile());assert(f:write('first\\nsecond\\n'));assert(f:seek('set',0));local a,b,c=f:read('l','L','l');f:close();return a..':'..b..':'..tostring(c)..':'..io.type(f)",
 "local f=assert(io.tmpfile());f:write('abcdef');f:seek('set',1);local a=f:read(3);local p=f:seek();f:close();return a..':'..p",
 "local f=assert(io.tmpfile());local a=f:read(0);f:write('a');f:seek('set',0);local b=f:read(0);f:close();return tostring(a)..':'..b",
 "local f=assert(io.tmpfile());f:write('a\\nb\\n');f:seek('set',0);local t={};for line in f:lines() do t[#t+1]=line end f:close();return table.concat(t,':')",
 "local f=assert(io.tmpfile());f:write('contents');f:seek('set',0);local s=f:read('a');f:close();return s",
 "local f=assert(io.tmpfile());return tostring(f:setvbuf('no'))..':'..tostring(f:flush())..':'..tostring(f:close())",
 "return tostring(io.close(io.stdout))",
 "local f,e,n=io.open('/missing-fixture','r');return tostring(f)..':'..e..':'..n",
];
for(const script of cases){const states=modules.map(m=>{m._probe_reset();const bytes=Buffer.from(script+'\0'),at=m._malloc(BigInt(bytes.length));try{m.HEAPU8.set(bytes,Number(at));return {status:m._probe_eval(BigInt(at)),output:text(m,m._probe_output())};}finally{m._free(BigInt(at));}});assert.deepEqual(states[1],states[0],script);}
console.log(`Lua IO: ${cases.length} original-C/pure-JS stream, bytes, positions, EOF, errors and ownership comparisons passed.`);
