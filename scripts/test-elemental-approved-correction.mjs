// Guard regression: reviewed import relocation passes; every extra source edit fails.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {elementalApprovedCorrection} from './elemental-approved-correction.mjs';
const root=process.cwd(),reference=path.resolve('.cache/full-original-c-v1');
const directory=fs.mkdtempSync(path.join(root,'.cache/elemental-guard-test-'));
const source=fs.readFileSync('js/ported/vision.js','utf8');
const correction=JSON.parse(fs.readFileSync('docs/runtime-environment/authorized-port-corrections.json')).corrections[0];
try {
 for(const file of ['js/ported/vision.js','docs/runtime-environment/authorized-port-corrections.json','docs/runtime-environment/scope-baseline.json','docs/runtime-environment/services-layout.json']) {
  const target=path.join(directory,file);fs.mkdirSync(path.dirname(target),{recursive:true});fs.copyFileSync(file,target);
 }
 process.chdir(directory);
 assert.equal(elementalApprovedCorrection(reference).correctedSha256,correction.correctedSha256);
 const cases=[['extra policy',source+'\nexport function unapprovedPolicy() { return 1; }\n'],['reverted correction',source.replace(correction.change.after,correction.change.before)],['unreviewed import',source.replace('../c-runtime/context.js','../c-runtime/unreviewed-context.js')]];
 for(const [name,changed]of cases){assert.notEqual(changed,source,name+' changes fixture');fs.writeFileSync('js/ported/vision.js',changed);assert.throws(()=>elementalApprovedCorrection(reference),/Relocated source changed|Approved corrected VISION hash/,name+' rejected');}
 console.log('PASS: reviewed import relocation and3 rejected extra/reverted/import edits; production sources untouched');
} finally {process.chdir(root);fs.rmSync(directory,{recursive:true,force:true});}
