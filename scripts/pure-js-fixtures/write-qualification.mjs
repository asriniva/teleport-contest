// Record exact reviewed diffs without modifying historical source pins.
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
import {migrationFiles} from './qualification.mjs';
const baselineCommit='cc8ef80b7ac93c01feac7e40677aec0d3d63c03a',sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
const directory='docs/runtime-environment/pure-js-source-changes';fs.mkdirSync(directory,{recursive:true});const files={};
for(const file of [...migrationFiles].sort()){
 let before;try{before=execFileSync('git',['show',baselineCommit+':'+file],{stdio:['ignore','pipe','ignore']});}catch{before=Buffer.alloc(0);}
 const after=fs.readFileSync(file);if(before.equals(after))continue;
 const patch=(()=>{const directory=fs.mkdtempSync(path.join(os.tmpdir(),'migration-source-')),input=path.join(directory,'input.json');try{fs.writeFileSync(input,JSON.stringify({file,before:before.toString(),after:after.toString()}));return execFileSync('python3',['-c',"import sys,json,difflib;d=json.load(open(sys.argv[1]));sys.stdout.write(''.join(difflib.unified_diff(d['before'].splitlines(keepends=True),d['after'].splitlines(keepends=True),fromfile='a/'+d['file'],tofile='b/'+d['file'])))",input],{maxBuffer:16*1024*1024});}finally{fs.rmSync(directory,{recursive:true,force:true});}})();
 const name=directory+'/'+file.replaceAll('/','__')+'.patch';fs.writeFileSync(name,patch);
 files[file]={beforeSha256:before.length?sha(before):null,afterSha256:sha(after),patch:name,patchSha256:sha(patch)};
}
fs.writeFileSync('docs/runtime-environment/pure-js-source-changes.json',JSON.stringify({baselineCommit,scope:'Exact source changes for pure-JS subsystem test migration; separate completed execution receipt is required.',validation:'docs/runtime-environment/pure-js-test-validation.json',files},null,2)+'\n');
console.log('Recorded '+Object.keys(files).length+' exact migration source changes; execution qualification remains separate.');
