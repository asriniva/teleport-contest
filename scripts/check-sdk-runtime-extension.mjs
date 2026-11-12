import {runHistoricalCli as runPriorLayoutAudit} from './nethack-layout.mjs';
if(runPriorLayoutAudit(import.meta.url))process.exit(0);
// Development-only proof of the exact native-tested SDK additions after cleanup.
// The immutable relocation baseline and translated-policy guards remain separate.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {readBeforeLayout} from './services-layout-audit.mjs';
import os from 'node:os';
import path from 'node:path';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
const declaration='docs/runtime-environment/c-runtime-sdk-extension.json';
const sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
export function sdkRuntimeExtensionBaseline(){
 if(!fs.existsSync(declaration))return null;
 const row=JSON.parse(readBeforeLayout(declaration));
 assert.equal(row.baselineCommit,'460d483','SDK extension starts after the published game-public checkpoint');
 assert.deepEqual(Object.keys(row.files).sort(),['js/c-runtime/stdio.js','js/services/c-vfs.js','js/nethack/unix-platform-syscalls.js'],'Only the reviewed stdio/CVFS feature delta');
 for(const[file,hashes]of Object.entries(row.files)){
  const before=execFileSync('git',['show',row.baselineCommit+':'+file]);
  assert.equal(sha(before),hashes.beforeSha256,'Preserved SDK extension baseline '+file);
  assert.equal(sha(readBeforeLayout(file)),hashes.afterSha256,'Exact reviewed SDK extension '+file);
 }
 // Compare the verified files themselves, including in an immutable source copy.
 // A parent checkout may contain unrelated in-progress changes.
 const scratch=fs.mkdtempSync(path.join(os.tmpdir(),'sdk-extension-'));
 let patch;
 try{
  const chunks=[];
  for(const file of Object.keys(row.files).sort()){
   for(const side of ['a','b']){const target=path.join(scratch,side,file);fs.mkdirSync(path.dirname(target),{recursive:true});fs.writeFileSync(target,side==='a'?execFileSync('git',['show',row.baselineCommit+':'+file]):readBeforeLayout(file));fs.chmodSync(target,0o644);}
   let output;try{output=execFileSync('git',['diff','--no-index','--no-ext-diff','--no-color','--full-index','--no-renames','--diff-algorithm=myers','--no-indent-heuristic','--unified=3','--','a/'+file,'b/'+file],{cwd:scratch});}catch(error){if(error.status!==1)throw error;output=error.stdout;}
   chunks.push(output.toString().replace(/^diff --git a\/a\/(.*?) b\/b\/(.*?)$/gm,'diff --git a/$1 b/$2').replace(/^--- a\/a\//gm,'--- a/').replace(/^\+\+\+ b\/b\//gm,'+++ b/'));
  }
  patch=Buffer.from(chunks.join(''));
 }finally{fs.rmSync(scratch,{recursive:true,force:true});}
 assert.equal(sha(patch),row.patchSha256,'Reviewed SDK feature patch');
 assert.deepEqual(readBeforeLayout(row.patch),patch,'SDK feature patch matches the actual files');
 const evidenceBytes=readBeforeLayout(row.evidence),evidence=JSON.parse(evidenceBytes);
 assert.equal(sha(evidenceBytes),row.evidenceSha256,'Bound original-SDK comparison evidence');
 assert.equal(evidence.complete,true,'Completed SDK comparison');
 assert.equal(evidence.originalSdkCompared,true,'Original SDK is the reference');
 assert.ok(evidence.checks>0,'Executed native comparisons');
 for(const[file,hash]of Object.entries(evidence.sourceSha256))assert.equal(sha(readBeforeLayout(file)),hash,'SDK evidence input '+file);
 return execFileSync('git',['show',row.baselineCommit+':js/c-runtime/stdio.js'],{encoding:'utf8'});
}
if(process.argv[1]?.endsWith('/check-sdk-runtime-extension.mjs')){
 assert.ok(sdkRuntimeExtensionBaseline(),'SDK extension declaration is required');
 console.log('PASS: exact stdio/CVFS SDK additions and original-SDK comparison evidence; original cleanup baseline retained.');
}
