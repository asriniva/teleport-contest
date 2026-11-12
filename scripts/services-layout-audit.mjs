// Development-only exact inverse for the preceding cleanup's historical audits.
// Actual source hashes and the reproducible relocation are checked separately.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import{execFileSync}from'node:child_process';
const recipe=()=>JSON.parse(fs.readFileSync('docs/runtime-environment/services-layout.json'));
const hash=b=>crypto.createHash('sha256').update(b).digest('hex');
const successors=new Set(['js/standalone/level-startup.js','scripts/export-standalone-pager-target-abi.py','js/standalone/pager-target-header-functions.js','js/standalone/pager-target-abi.json','js/standalone/dbridge-abi.json','js/standalone/region-services-abi.json']);
const postDefault=new Set(['js/c-runtime/stdio.js','js/platform/darwin/terminal.js','js/standalone/display-startup.js','js/standalone/environment.js','js/standalone/monster-creation.js','js/standalone/monster-selection.js','js/standalone/program.js','js/standalone/sdk-boundary.js','js/standalone/signals.js','js/standalone/unix-platform.js','js/standalone/unix-terminal.js','js/standalone/version-info.js','js/standalone/makemon-private-abi.json','js/standalone/makemon-public-abi.json','js/standalone/persistence-transport-abi.json','js/standalone/scanf-abi.json','js/standalone/sdk-boundary-abi.json','js/standalone/unix-platform-abi.json','js/standalone/signal-delivery-abi.json']);
const beforeFeature=(file,exists=false)=>execFileSync('python3',['scripts/post_default_successors.py','--file',file,...(exists?['--exists']:[])],{maxBuffer:32*1024*1024});
const monmove=new Set(['js/standalone/monster-movement.js','js/standalone/monmove-abi.json']);
const beforeMonmove=(file,exists=false)=>execFileSync('python3',['scripts/monmove_source_successors.py','--file',file,...(exists?['--exists']:[])],{maxBuffer:32*1024*1024});
const windowHeaders=new Set(['js/standalone/window-system.js','js/standalone/window-abi.json','js/standalone/turn-loop-abi.json']);
const beforeWindowHeaders=(file,exists=false)=>execFileSync('python3',['scripts/window_headers_source_successors.py','--file',file,...(exists?['--exists']:[])],{maxBuffer:32*1024*1024});
const beforeFeatureBytes=file=>windowHeaders.has(file)?beforeWindowHeaders(file):monmove.has(file)?beforeMonmove(file):postDefault.has(file)?beforeFeature(file):fs.readFileSync(file);
const historicalAfter=(file,after)=>execFileSync('python3',['scripts/services_layout_successors.py','--file',file,...(after?['--layout-after',after]:[])],{maxBuffer:32*1024*1024});
export function currentSourcePath(file){const d=recipe(),p=path.relative(process.cwd(),path.resolve(file));return d.moves[p]??file;}
export function readBeforeLayout(file,encoding){
 const d=recipe(),p=path.relative(process.cwd(),path.resolve(file)),row=d.files.find(r=>r.file===p||r.destination===p);
 let bytes;
 if(row){const actual=beforeFeatureBytes(row.destination);if(hash(actual)!==row.afterSha256){if(!successors.has(row.destination))throw Error('Relocated source changed: '+row.destination);historicalAfter(row.destination,row.afterSha256);}bytes=execFileSync('git',['show',d.baselineCommit+':'+row.file],{maxBuffer:32*1024*1024});if(hash(bytes)!==row.beforeSha256)throw Error('Historical source inverse differs: '+row.file);}
 else bytes=successors.has(p)?historicalAfter(p):beforeFeatureBytes(p);
 return encoding?bytes.toString(encoding):bytes;
}
export function existsBeforeLayout(file){const p=path.relative(process.cwd(),path.resolve(currentSourcePath(file)));return windowHeaders.has(p)?beforeWindowHeaders(p,true).toString()==='1':monmove.has(p)?beforeMonmove(p,true).toString()==='1':postDefault.has(p)?beforeFeature(p,true).toString()==='1':fs.existsSync(currentSourcePath(file));}
export function writeBeforeLayout(file,bytes){const d=recipe(),p=path.relative(process.cwd(),path.resolve(file)),row=d.files.find(r=>r.file===p||r.destination===p);if(row){if(hash(Buffer.from(bytes))!==row.beforeSha256)throw Error('Historical output changed; review relocation first: '+p);readBeforeLayout(file);return;}if(successors.has(p)||postDefault.has(p)||monmove.has(p)||windowHeaders.has(p)){const historical=readBeforeLayout(file);if(hash(Buffer.from(bytes))!==hash(historical))throw Error('Historical output changed; review successor first: '+p);if(!fs.readFileSync(file).equals(Buffer.from(bytes)))throw Error('Refusing to overwrite qualified '+(windowHeaders.has(p)?'window-header':monmove.has(p)?'MONMOVE':postDefault.has(p)?'post-default':'post-cleanup')+' feature: '+p);return;}fs.writeFileSync(file,bytes);}
