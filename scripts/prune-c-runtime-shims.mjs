// Remove proven-unused forwarding modules and migrate the remaining old provider
// imports. This tool never rewrites historical oracle receipts or game decisions.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
const extraction=JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-helper-extraction.json'));
const baseline=extraction.baselineCommit,sha=text=>crypto.createHash('sha256').update(text).digest('hex');
const old=file=>execFileSync('git',['show',baseline+':'+file],{encoding:'utf8'});
const removals=['js/standalone/bitfields.js','js/standalone/environment-inputs.js','js/standalone/qsort.js','js/standalone/scanf.js','js/standalone/stdio.js','js/ported/js-runtime.js'];
const rules=[
 ['js/standalone/object-state.js',"../ported/js-runtime.js","../nethack/runtime.js"],
 ...['test-js-game-files','test-js-runtime-regex','test-js-time','test-js-runtime'].map(name=>['scripts/'+name+'.mjs','../js/ported/js-runtime.js','../js/nethack/runtime.js']),
 ['scripts/export-standalone-were-abi.py',"'js/ported/js-runtime.js',",''],
 ['scripts/export-standalone-scanf-abi.py',"'js/standalone/scanf.js',",''],
 ['scripts/export-standalone-scanf-abi.py',"'js/standalone/stdio.js',",''],
 ['scripts/test-standalone-scanf.mjs','js/standalone/scanf.js','js/c-runtime/scanf.js'],
 ['scripts/test-standalone-scanf.mjs','js/standalone/stdio.js','js/c-runtime/stdio.js'],
];
const outputs=new Map(),edits=[];
for(const[file,before,after]of rules){const source=outputs.get(file)??old(file);assert.equal(source.split(before).length-1,1,'Changed consumer boundary '+file);outputs.set(file,source.replace(before,after));edits.push({file,before,after});}
const receipt={baselineCommit:baseline,removed:removals.map(file=>({file,beforeSha256:sha(old(file))})),consumers:[...outputs].map(([file,source])=>({file,beforeSha256:sha(old(file)),afterSha256:sha(source),edits:edits.filter(row=>row.file===file)}))};
for(const[file,expected]of outputs){const actual=fs.readFileSync(file,'utf8');if(process.argv.includes('--write')){assert.ok(actual===old(file)||actual===expected,'Refusing unknown consumer edit '+file);}else assert.equal(actual,expected,'Consumer migration differs '+file);}
// Scan every tracked code file's literal imports, including import expressions.
for(const file of execFileSync('git',['ls-files','js','scripts'],{encoding:'utf8'}).trim().split('\n')){
 if(!/\.m?js$/.test(file)||!fs.existsSync(file)||removals.includes(file))continue;
 const source=outputs.get(file)??fs.readFileSync(file,'utf8');
 for(const match of source.matchAll(/(?:from\s*|import\s*\(\s*)['"]([^'"]+)['"]/g)){
  if(!match[1].startsWith('.'))continue;const target=path.relative(process.cwd(),path.resolve(path.dirname(file),match[1]));assert.ok(!removals.includes(target),'Active consumer of deleted shim '+file+' -> '+target);
 }
}
for(const file of removals){if(process.argv.includes('--write')){if(fs.existsSync(file)){assert.equal(sha(fs.readFileSync(file)),sha(old(file)),'Refusing edited shim '+file);}}else assert.ok(!fs.existsSync(file),'Obsolete shim remains '+file);}
if(process.argv.includes('--write')){for(const[file,source]of outputs)fs.writeFileSync(file,source);for(const file of removals)if(fs.existsSync(file))fs.unlinkSync(file);}
const target='docs/runtime-environment/c-runtime-shim-pruning.json',expected=JSON.stringify(receipt,null,2)+'\n';if(process.argv.includes('--write'))fs.writeFileSync(target,expected);else assert.equal(fs.readFileSync(target,'utf8'),expected);
console.log('PASS: '+removals.length+' unused shims removed; '+outputs.size+' consumer/tool files changed only at exact declared boundaries; no tracked literal import remains.');
