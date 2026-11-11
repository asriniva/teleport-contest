// Development gate. C oracles are test-only; the production entry is pure JS.
import fs from 'node:fs';
import crypto from 'node:crypto';
import {spawnSync} from 'node:child_process';
const tests=['check-standalone-scope','test-js-runtime',...['environment','libc','data','io-lua','address-ports','serialization','track','object-state','terminal','isolation'].map(name=>'test-standalone-'+name)];
if(!process.env.STANDALONE_REFERENCE_ROOT)throw new Error('Set STANDALONE_REFERENCE_ROOT to the prepared reference checkout');
fs.mkdirSync('.cache/standalone-validation',{recursive:true});
const results=[];
for(const name of tests){
    const script='scripts/'+name+'.mjs';
    const result=spawnSync(process.execPath,[script],{env:process.env,encoding:'utf8',maxBuffer:16*1024*1024});
    const log=(result.stdout||'')+(result.stderr||'')+(result.error?String(result.error):'');
    fs.writeFileSync('.cache/standalone-validation/'+name+'.log',log);
    results.push({name,status:result.status,scriptSha256:crypto.createHash('sha256').update(fs.readFileSync(script)).digest('hex')});
    console.log(name+': '+(result.status===0?'PASS':'FAIL'));
    if(result.status!==0){console.error(log);break;}
}
fs.writeFileSync('.cache/standalone-validation/gate.json',JSON.stringify({results,complete:results.length===tests.length&&results.every(r=>r.status===0)},null,2)+'\n');
if(results.length!==tests.length||results.some(r=>r.status!==0))process.exitCode=1;
