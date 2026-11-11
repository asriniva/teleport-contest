import{resolve}from'node:path';import{pathToFileURL}from'node:url';const i=process.argv.indexOf('--out');if(i<0||!process.argv[i+1])throw Error('--out is required');const out=pathToFileURL(resolve(process.argv[i+1])+'/');
// Logging-only observer: executes every original assertion unchanged, then records values.
import assert from 'node:assert/strict';
import {writeFileSync,readFileSync} from 'node:fs';
import {createHash} from 'node:crypto';
const before=createHash('sha256').update(readFileSync(new URL('./test-utility-xpm2iff-host.mjs',import.meta.url))).digest('hex');
const compare=assert.deepEqual,rows=[];
assert.deepEqual=function(actual,expected,message){const value=compare(actual,expected,message);rows.push({message,actual,expected});return value;};
try{await import('./test-utility-xpm2iff-host.mjs');}finally{assert.deepEqual=compare;}
const after=createHash('sha256').update(readFileSync(new URL('./test-utility-xpm2iff-host.mjs',import.meta.url))).digest('hex');
if(before!==after)throw Error('test source drift');
writeFileSync(new URL('./paired-transcripts.json',out),JSON.stringify({testSha256:before,unchangedBeforeAfter:true,comparison:'original deepEqual executed before logging each unchanged argument; no value normalization in comparison',rows},(_,v)=>typeof v==='bigint'?{$bigint:String(v)}:v,2)+'\n');
