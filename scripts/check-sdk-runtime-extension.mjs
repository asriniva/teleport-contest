// Development-only proof of the exact native-tested SDK additions after cleanup.
// The immutable relocation baseline and translated-policy guards remain separate.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
const declaration='docs/runtime-environment/c-runtime-sdk-extension.json';
const sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
export function sdkRuntimeExtensionBaseline(){
 if(!fs.existsSync(declaration))return null;
 const row=JSON.parse(fs.readFileSync(declaration));
 assert.equal(row.baselineCommit,'460d483','SDK extension starts after the published game-public checkpoint');
 assert.deepEqual(Object.keys(row.files).sort(),['js/c-runtime/stdio.js','js/services/c-vfs.js','js/standalone/unix-platform-syscalls.js'],'Only the reviewed stdio/CVFS feature delta');
 for(const[file,hashes]of Object.entries(row.files)){
  const before=execFileSync('git',['show',row.baselineCommit+':'+file]);
  assert.equal(sha(before),hashes.beforeSha256,'Preserved SDK extension baseline '+file);
  assert.equal(sha(fs.readFileSync(file)),hashes.afterSha256,'Exact reviewed SDK extension '+file);
 }
 const patch=execFileSync('git',['diff','--no-ext-diff','--no-color','--full-index','--no-renames','--diff-algorithm=myers','--no-indent-heuristic','--unified=3',row.baselineCommit,'--',...Object.keys(row.files).sort().map(file=>':(top)'+file)]);
 assert.equal(sha(patch),row.patchSha256,'Reviewed SDK feature patch');
 assert.deepEqual(fs.readFileSync(row.patch),patch,'SDK feature patch matches the actual files');
 const evidenceBytes=fs.readFileSync(row.evidence),evidence=JSON.parse(evidenceBytes);
 assert.equal(sha(evidenceBytes),row.evidenceSha256,'Bound original-SDK comparison evidence');
 assert.equal(evidence.complete,true,'Completed SDK comparison');
 assert.equal(evidence.originalSdkCompared,true,'Original SDK is the reference');
 assert.ok(evidence.checks>0,'Executed native comparisons');
 for(const[file,hash]of Object.entries(evidence.sourceSha256))assert.equal(sha(fs.readFileSync(file)),hash,'SDK evidence input '+file);
 return execFileSync('git',['show',row.baselineCommit+':js/c-runtime/stdio.js'],{encoding:'utf8'});
}
if(process.argv[1]?.endsWith('/check-sdk-runtime-extension.mjs')){
 assert.ok(sdkRuntimeExtensionBaseline(),'SDK extension declaration is required');
 console.log('PASS: exact stdio/CVFS SDK additions and original-SDK comparison evidence; original cleanup baseline retained.');
}
