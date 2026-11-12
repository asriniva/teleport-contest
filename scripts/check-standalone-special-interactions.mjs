import {runHistoricalCli as runPriorLayoutAudit} from './nethack-layout.mjs';
if(runPriorLayoutAudit(import.meta.url))process.exit(0);
// Targeted guard; the complete standalone provenance gate remains separate.
import assert from 'node:assert/strict';
import {readBeforeLayout} from './services-layout-audit.mjs';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
const reference=process.env.STANDALONE_REFERENCE_ROOT;if(!reference)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const {parse}=await import(pathToFileURL(reference+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const read=p=>JSON.parse(fs.readFileSync(p)),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
const baseline=read('docs/runtime-environment/scope-baseline.json');
const corrections=read('docs/runtime-environment/authorized-port-corrections.json').corrections;
assert.deepEqual(corrections.map(row=>row.file),['js/ported/vision.js'],'Only main\'s explicitly approved correction is allowed');
for(const row of corrections){assert.equal(baseline.sha256[row.file],row.baselineSha256);assert.notEqual(row.correctedSha256,row.baselineSha256);}
const corrected=new Map(corrections.map(row=>[row.file,row.correctedSha256]));
for(const[p,h]of Object.entries(baseline.sha256))assert.equal(crypto.createHash('sha256').update(readBeforeLayout(p)).digest('hex'),corrected.get(p)??h,p);
for(const name of ['isaac64','terminal','storage'])assert.deepEqual(fs.readFileSync('js/'+name+'.js'),fs.readFileSync('frozen/'+name+'.js'));
const abi=read('js/nethack/special-interactions-abi.json');for(const[p,h]of Object.entries(abi.sourceSha256))assert.equal(sha(p),h,p);for(const[p,h]of Object.entries(abi.referenceHeaderSha256))assert.equal(sha(path.resolve(reference,p)),h,p);
const seen=new Set();function collect(file){file=path.resolve(file);assert.ok(file.startsWith(process.cwd()+path.sep));if(seen.has(file))return;seen.add(file);if(file.endsWith('.json'))return;
 const ast=parse(fs.readFileSync(file,'utf8'),{ecmaVersion:'latest',sourceType:'module'});
 function visit(node){if(!node||typeof node!=='object')return;
  if(['ImportDeclaration','ExportAllDeclaration','ExportNamedDeclaration','ImportExpression'].includes(node.type)&&node.source){const src=node.source.value;assert.equal(typeof src,'string');assert.ok(src.startsWith('.')&&!src.endsWith('.wasm'),file+': '+src);collect(path.resolve(path.dirname(file),src));}
  assert.ok(!(node.type==='Identifier'&&node.name==='WebAssembly'),'Wasm '+file);
  if(['CallExpression','NewExpression'].includes(node.type)&&node.callee.type==='Identifier')assert.ok(!['eval','Function','fetch','Worker','WebSocket','XMLHttpRequest'].includes(node.callee.name),'Forbidden host capability '+file);
  for(const[k,v]of Object.entries(node))if(!['start','end','loc'].includes(k)){if(Array.isArray(v))v.forEach(visit);else if(v&&typeof v==='object')visit(v);}
 }visit(ast);
}
collect('js/nethack/program.js');collect('js/nethack/environment.js');
console.log('PASS '+JSON.stringify({policyFiles:baseline.policyCount,unchangedPolicyFiles:baseline.policyCount-corrections.length,approvedCorrections:corrections.map(row=>row.file),frozenFiles:3,productionFiles:seen.size,optionalSourceHashes:Object.keys(abi.sourceSha256).length,measuredHeaders:Object.keys(abi.referenceHeaderSha256).length,limitation:'Targeted new-owner provenance and complete static import closure; does not replace the complete standalone provenance gate or full-game acceptance.'}));
