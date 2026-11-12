// Development-only exact inverse for the preceding cleanup's historical audits.
// Actual source hashes and the reproducible relocation are checked separately.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{execFileSync}from'node:child_process';
const recipe=()=>JSON.parse(fs.readFileSync('docs/runtime-environment/services-layout.json'));
const hash=b=>crypto.createHash('sha256').update(b).digest('hex');
export function currentSourcePath(file){const d=recipe(),p=path.relative(process.cwd(),path.resolve(file));return d.moves[p]??file;}
export function readBeforeLayout(file,encoding){
 const d=recipe(),p=path.relative(process.cwd(),path.resolve(file)),row=d.files.find(r=>r.file===p||r.destination===p);
 let bytes;
 if(row){const actual=fs.readFileSync(row.destination);if(hash(actual)!==row.afterSha256)throw Error('Relocated source changed: '+row.destination);bytes=execFileSync('git',['show',d.baselineCommit+':'+row.file],{maxBuffer:32*1024*1024});if(hash(bytes)!==row.beforeSha256)throw Error('Historical source inverse differs: '+row.file);}
 else bytes=fs.readFileSync(file);
 return encoding?bytes.toString(encoding):bytes;
}
export function existsBeforeLayout(file){return fs.existsSync(currentSourcePath(file));}
export function writeBeforeLayout(file,bytes){const d=recipe(),p=path.relative(process.cwd(),path.resolve(file)),row=d.files.find(r=>r.file===p||r.destination===p);if(row){if(hash(Buffer.from(bytes))!==row.beforeSha256)throw Error('Historical output changed; review relocation first: '+p);readBeforeLayout(file);return;}fs.writeFileSync(file,bytes);}
