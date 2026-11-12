// Current-source relocation, imports, capability isolation and negative controls.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {execFileSync} from 'node:child_process';
import {parse} from '../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
import {layoutSourceSha} from './nethack-layout.mjs';
execFileSync('python3',['scripts/consolidate-nethack-layout.py'],{stdio:'inherit'});
let modules=0,imports=0,unbuiltLegacy=0;
function visit(directory){for(const row of fs.readdirSync(directory,{withFileTypes:true})){
 const file=path.join(directory,row.name);if(row.isDirectory()){visit(file);continue;}
 if(!/\.(?:js|mjs)$/.test(file)||file==='js/wasm/nethack.mjs')continue;
 const source=fs.readFileSync(file,'utf8');let ast;try{ast=parse(source,{ecmaVersion:'latest',sourceType:'module'});}catch(error){error.message=file+': '+error.message;throw error;}modules++;
 for(const node of ast.body)if(node.type==='ImportDeclaration'||node.type.startsWith('Export')&&node.source){
  const name=node.source.value;if(!name.startsWith('.'))continue;imports++;
  const target=path.resolve(path.dirname(file),name);
  if(!fs.existsSync(target)&&file==='scripts/test-version-bridge.mjs'&&name==='../js/wasm/nethack.mjs'){unbuiltLegacy++;continue;}
  assert.ok(fs.existsSync(target),file+': '+name);
 }
 if(file.startsWith('js/'))assert.ok(!source.includes('../standalone/'),'Old production import: '+file);
 if(/^scripts\/test-(?:tu-|standalone-)/.test(file))assert.ok(!source.includes('runPriorLayoutAudit'),'Runtime tests must execute current modules: '+file);
}}
visit('js');visit('scripts');
const receipt=JSON.parse(fs.readFileSync('docs/runtime-environment/nethack-layout.json'));
const file='js/nethack/light.js',row=receipt.files['js/standalone/light.js'];
assert.equal(layoutSourceSha(file,row.beforeSha256),row.beforeSha256,'original source pin retained');
const read=fs.readFileSync;
fs.readFileSync=function(p,...args){const bytes=read.call(this,p,...args);return path.resolve(String(p))===path.resolve(file)?Buffer.concat([Buffer.from(bytes),Buffer.from('\n')]):bytes;};
try{assert.throws(()=>layoutSourceSha(file,row.beforeSha256),/changed beyond NetHack path relocation/,'source drift rejected');}finally{fs.readFileSync=read;}
await import('./pure-js-probes/deny-wasm.mjs');
const {createStandaloneEnvironment}=await import('../js/nethack/environment.js');
const env=createStandaloneEnvironment();assert.ok(env.memory&&env.services);
assert.equal(fs.existsSync('js/standalone'),false);
console.log('PASS: '+modules+' current modules parse; '+imports+' relative imports resolve; '+unbuiltLegacy+' unchanged legacy generated imports await their own build.');
console.log('PASS: consolidated environment initializes with Wasm denied; original source pins accepted and altered source rejected.');
