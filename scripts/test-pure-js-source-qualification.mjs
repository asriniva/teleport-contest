// Reject source/patch/declaration drift without modifying the live workspace.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {qualifiedHistorical} from './pure-js-fixtures/qualification.mjs';
const declarationPath='docs/runtime-environment/pure-js-source-changes.json';
const declaration=JSON.parse(fs.readFileSync(declarationPath));
const target='js/c-runtime/stdio.js',row=declaration.files[target];
assert.ok(qualifiedHistorical(target).byteLength>0);
const original=fs.readFileSync;
function reject(file,mutate,pattern){fs.readFileSync=function(p,...args){const bytes=original.call(this,p,...args);return path.resolve(String(p))===path.resolve(file)?mutate(bytes):bytes;};try{assert.throws(()=>qualifiedHistorical(target),pattern);}finally{fs.readFileSync=original;}}
reject(target,b=>Buffer.concat([b,Buffer.from('\n')]),/Migration source changed/);
reject(row.patch,b=>Buffer.concat([b,Buffer.from('\n')]),/Migration patch changed/);
reject(declarationPath,b=>{const d=JSON.parse(b);d.baselineCommit='0'.repeat(40);return Buffer.from(JSON.stringify(d));},/Unreviewed migration qualification cohort/);
reject(declarationPath,b=>{const d=JSON.parse(b);d.files['js/unreviewed.js']={};return Buffer.from(JSON.stringify(d));},/Unreviewed migration qualification cohort/);
assert.throws(()=>qualifiedHistorical(target,'0'.repeat(64)),/Historical migration source differs/);
console.log('PASS: exact source qualification rejects source drift, patch drift, baseline replacement, unreviewed files and mismatched historical pins.');
