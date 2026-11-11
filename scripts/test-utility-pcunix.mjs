import assert from 'node:assert/strict';
import {writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import path from 'node:path';
import {callRegularize} from '../js/ported-utilities/pcunix-runtime.js';
import {C} from '../js/ported-utilities/pcunix-scope.js';
const arg=process.argv.indexOf('--out');if(arg<0)throw Error('--out required');const out=path.resolve(process.argv[arg+1]);
const reference=(await import(pathToFileURL(out+'/reference.mjs'))).default,hybrid=(await import(pathToFileURL(out+'/hybrid.mjs'))).default;
const modules=[];let checks=0,cases=0;
for(const factory of[reference,hybrid]){
 const m=await factory({print(){},printErr(){}});m.pcunixRegularize=p=>callRegularize(m,p);modules.push(m);
 assert.equal(m._probe_char_signed(),1);checks++;
 for(let i=0;i<3;i++){assert.equal(m._probe_profile(i),0);checks++;}
}
function one(bytes,offset=0){
 const rows=[];
 for(const m of modules){
  const p=BigInt(m._malloc(BigInt(bytes.length+8)));const at=Number(p);m.HEAPU8.fill(0xa5,at,at+bytes.length+8);m.HEAPU8.set(bytes,at+4);
  assert.equal(m._probe_call(p+4n+BigInt(offset)),p+4n+BigInt(offset));checks++;
  assert.equal(C,undefined);checks++;
  const row=[...m.HEAPU8.slice(at,at+bytes.length+8)];assert.deepEqual(row.slice(0,4),[165,165,165,165]);assert.deepEqual(row.slice(-4),[165,165,165,165]);checks+=2;
  assert.equal(m._probe_call(p+4n+BigInt(offset)),p+4n+BigInt(offset));assert.deepEqual([...m.HEAPU8.slice(at,at+bytes.length+8)],row);checks+=2;
  rows.push(row);m._free(p);
 }
 assert.deepEqual(rows[1],rows[0]);checks++;cases++;return rows[0].slice(4,-4);
}
const enc=s=>[...Buffer.from(s),0];
assert.deepEqual(one(enc('a b.c/d:e?f[g]h\\i|j+k,l*m"n')),enc('a_b_c_d_e_f_g_h_i_j_k_l_m_n'));checks++;
assert.deepEqual(one(enc("A&()!#$%'09-_{}~")),enc("A&()!#$%'09-_{}~"));checks++;
assert.deepEqual(one([0,32,47,255]),[0,32,47,255]);checks++;
assert.deepEqual(one([65,0,32,47,255]),[65,0,32,47,255]);checks++;
assert.deepEqual(one([47,65,32,66,0,47],1),[47,65,95,66,0,47]);checks++;
for(let b=1;b<256;b++)one([b,0,44]);
one([...Array.from({length:255},(_,i)=>i+1),0,47]);
one([...Array.from({length:4096},(_,i)=>1+(i*73)%255),0,47]);
const other=await hybrid({print(){},printErr(){}});other.pcunixRegularize=p=>callRegularize(other,p);const q=BigInt(other._malloc(8n));other.HEAPU8.set([65,43,66,0],Number(q));
const before=modules[1].HEAPU8.buffer.byteLength,grown=modules[1]._malloc(40n*1024n*1024n);assert.ok(modules[1].HEAPU8.buffer.byteLength>before);checks++;
one(enc('fresh+after,growth'));assert.deepEqual([...other.HEAPU8.slice(Number(q),Number(q)+4)],[65,43,66,0]);checks++;
assert.equal(other._probe_call(q),q);assert.deepEqual([...other.HEAPU8.slice(Number(q),Number(q)+4)],[65,95,66,0]);checks+=2;
other._free(q);modules[1]._free(grown);assert.equal(C,undefined);checks++;
const result={status:'PASS',checks,cases,configuredOwnedFunctions:1,actualGrowth:true,actualSecondModule:true};writeFileSync(path.join(out,'test-results.json'),JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(result));
