// Development-only exact inverse for the preceding cleanup's historical audits.
// Actual source hashes and the reproducible relocation are checked separately.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{execFileSync}from'node:child_process';
const recipe=()=>JSON.parse(fs.readFileSync('docs/runtime-environment/services-layout.json'));
const hash=b=>crypto.createHash('sha256').update(b).digest('hex');
const successors=new Set(['js/standalone/level-startup.js','scripts/export-standalone-pager-target-abi.py','js/standalone/pager-target-header-functions.js','js/standalone/pager-target-abi.json','js/standalone/dbridge-abi.json','js/standalone/region-services-abi.json']);
const historicalAfter=(file,after)=>execFileSync('python3',['scripts/services_layout_successors.py','--file',file,...(after?['--layout-after',after]:[])],{maxBuffer:32*1024*1024});
export function currentSourcePath(file){const d=recipe(),p=path.relative(process.cwd(),path.resolve(file));return d.moves[p]??file;}
export function readBeforeLayout(file,encoding){
 const d=recipe(),p=path.relative(process.cwd(),path.resolve(file)),row=d.files.find(r=>r.file===p||r.destination===p);
 let bytes;
 if(row){const actual=fs.readFileSync(row.destination);if(hash(actual)!==row.afterSha256){if(!successors.has(row.destination))throw Error('Relocated source changed: '+row.destination);historicalAfter(row.destination,row.afterSha256);}bytes=execFileSync('git',['show',d.baselineCommit+':'+row.file],{maxBuffer:32*1024*1024});if(hash(bytes)!==row.beforeSha256)throw Error('Historical source inverse differs: '+row.file);}
 else bytes=successors.has(p)?historicalAfter(p):fs.readFileSync(file);
 return encoding?bytes.toString(encoding):bytes;
}
export function existsBeforeLayout(file){return fs.existsSync(currentSourcePath(file));}
export function writeBeforeLayout(file,bytes){const d=recipe(),p=path.relative(process.cwd(),path.resolve(file)),row=d.files.find(r=>r.file===p||r.destination===p);if(row){if(hash(Buffer.from(bytes))!==row.beforeSha256)throw Error('Historical output changed; review relocation first: '+p);readBeforeLayout(file);return;}if(successors.has(p)){const historical=readBeforeLayout(file);if(hash(Buffer.from(bytes))!==hash(historical))throw Error('Historical output changed; review successor first: '+p);if(!fs.readFileSync(file).equals(Buffer.from(bytes)))throw Error('Refusing to overwrite qualified post-cleanup feature: '+p);return;}fs.writeFileSync(file,bytes);}
