// Immutable compiled pins plus exact, independently reproducible source-layout inverses.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
import {currentSourcePath,readBeforeLayout} from './services-layout-audit.mjs';
let checked=false;const dependencies=new Map();
const digest=b=>crypto.createHash('sha256').update(b).digest('hex');
export const compiledInputDependencies=()=>[...dependencies];
export function assertCompiledInput(file,expected,label='compiled input'){
 const current=currentSourcePath(file),actual=digest(fs.readFileSync(current));
 if(actual===expected)return actual;
 const before=readBeforeLayout(file),historical=digest(before);
 if(historical!==expected){
  const receipt=JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-helper-extraction.json'));
  const relative=path.relative(process.cwd(),path.resolve(file));
  const entry=receipt.files.find(r=>r.file===relative);
  assert.ok(entry&&entry.beforeSha256===expected&&entry.afterSha256===historical,'stale '+label+':'+file);
  assert.equal(digest(execFileSync('git',['show',receipt.baselineCommit+':'+relative],{maxBuffer:32*1024*1024})),expected);
  assert.equal(digest(readBeforeLayout(receipt.helperFile)),receipt.helperSha256);
 }
 if(!checked){
  execFileSync(process.execPath,['scripts/check-services-layout.mjs'],{stdio:'pipe'});
  execFileSync(process.execPath,['scripts/extract-c-runtime-helpers.mjs'],{env:{...process.env,STANDALONE_REFERENCE_ROOT:process.env.STANDALONE_REFERENCE_ROOT??process.cwd()},stdio:'pipe'});
  const layout=JSON.parse(fs.readFileSync('docs/runtime-environment/services-layout.json'));
  for(const p of ['docs/runtime-environment/services-layout.json','docs/runtime-environment/binding-infrastructure.json','docs/runtime-environment/c-runtime-helper-extraction.json',...Object.keys(layout.supportSourceSha256),...Object.keys(JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-manifest.json')).sha256)])dependencies.set(currentSourcePath(p),digest(fs.readFileSync(currentSourcePath(p))));
  checked=true;
 }
 console.log('Reviewed source-layout input inverse: '+file+'; original compiled pin retained');return actual;
}
