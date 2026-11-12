import{qualifiedHistorical,migrationFiles}from'./pure-js-fixtures/qualification.mjs';
// Verify current sources independently of the historical audit inverse.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {execFileSync} from 'node:child_process';
import {parse} from '../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
const layout=JSON.parse(fs.readFileSync('docs/runtime-environment/services-layout-map.json'));
execFileSync('python3',['scripts/relocate-runtime-layout.py','--historical'],{stdio:'inherit'});
execFileSync(process.execPath,['scripts/extract-binding-infrastructure.mjs'],{stdio:'inherit'});
const original=p=>execFileSync('git',['show',layout.baselineCommit+':'+p],{maxBuffer:32*1024*1024}).toString();
const list=execFileSync('git',['ls-tree','-r','--name-only',layout.baselineCommit],{encoding:'utf8'}).trim().split('\n');
let policies=0,modules=0,imports=0,unbuiltMixedArtifact=0;
for(const file of list.filter(p=>p.startsWith('js/ported/')&&p.endsWith('.js')&&!layout.moves[p])){
 const before=original(file),after=(migrationFiles.has(file)?qualifiedHistorical(file):fs.readFileSync(file)).toString();
 const ast=s=>parse(s,{ecmaVersion:'latest',sourceType:'module'});
 const literals=s=>ast(s).body.filter(n=>n.type==='ImportDeclaration'||n.type.startsWith('Export')&&n.source).map(n=>n.source);
 const a=literals(before),b=literals(after);assert.equal(a.length,b.length,file);
 let normalized=after;
 for(let i=a.length-1;i>=0;i--)normalized=normalized.slice(0,b[i].start)+before.slice(a[i].start,a[i].end)+normalized.slice(b[i].end);
 assert.equal(normalized,before,'Policy body changed beyond import literals: '+file);policies++;
}
function walk(dir){return fs.readdirSync(dir,{withFileTypes:true}).flatMap(d=>d.isDirectory()?walk(dir+'/'+d.name):[dir+'/'+d.name]);}
for(const file of walk('js').filter(p=>p.endsWith('.js')&&!p.startsWith('js/wasm/'))){
 const ast=parse(fs.readFileSync(file,'utf8'),{ecmaVersion:'latest',sourceType:'module'});modules++;
 function visit(n){if(!n||typeof n!=='object')return;
  if(['ImportDeclaration','ExportNamedDeclaration','ExportAllDeclaration','ImportExpression'].includes(n.type)&&n.source?.value?.startsWith('.')){
   const spec=n.source.value,target=path.normalize(path.join(path.dirname(file),spec));
   assert.ok(!target.startsWith('js/services/')&&!/js\/ported\/[^/]+-runtime\.js$/.test(target),'Old live layout: '+file+':'+spec);
   if(file==='js/wasm-adapter.js'&&target==='js/wasm/nethack.mjs'&&!fs.existsSync(target)){assert.ok(original(file).includes(spec));unbuiltMixedArtifact++;}
   else assert.ok(fs.existsSync(target),'Missing production import: '+file+':'+spec);imports++;
  }
  for(const v of Object.values(n))if(Array.isArray(v))v.forEach(visit);else if(v&&typeof v==='object')visit(v);
 }
 visit(ast);
}
assert.ok(!fs.existsSync('js/services'));
const ports=JSON.parse(fs.readFileSync('nethack-c/wasm/tu-ports.json'));
const old=JSON.parse(original('nethack-c/wasm/tu-ports.json'));
assert.deepEqual(ports.map(p=>[p.name,p.source]),old.map(p=>[p.name,p.source]));
for(const port of ports){const sources=new Set(port.adapterSources??[]);for(const file of sources){
 if(!file.endsWith('.js'))continue;
 const ast=parse(fs.readFileSync(file,'utf8'),{ecmaVersion:'latest',sourceType:'module'});
 for(const n of ast.body.filter(n=>n.type==='ImportDeclaration')){
  const target=path.normalize(path.join(path.dirname(file),n.source.value));
  if(target.startsWith('js/c-runtime/')||target==='js/nethack/header-aliases.js')assert.ok(sources.has(target),'Untracked adapter dependency: '+port.name+':'+target);
 }
}}
console.log(`PASS: ${policies} source-shaped policies unchanged beyond imports; ${modules} modules, ${imports} existing imports; adapter dependency closure and C selection retained; ${unbuiltMixedArtifact} unchanged mixed-backend generated artifact imports require a separate build.`);

// Evaluate only the source-list assignment, without executing the build.
const luaAssignment="import ast,json;from pathlib import Path;ROOT=Path.cwd();tree=ast.parse(Path('nethack-c/wasm/build.py').read_text());node=next(n for n in tree.body if isinstance(n,ast.Assign)and any(isinstance(t,ast.Name)and t.id=='lua_sources'for t in n.targets));scope={'ROOT':ROOT};exec(compile(ast.Module(body=[node],type_ignores=[]),'lua-inputs','exec'),scope);print(json.dumps(scope['lua_sources']))";
const actualLua=JSON.parse(execFileSync('python3',['-c',luaAssignment],{encoding:'utf8'}));
const oldLua=list.filter(p=>p.startsWith('js/services/')&&p.endsWith('.js')&&(path.dirname(p).endsWith('/lua')||path.basename(p).startsWith('lua-')||path.basename(p).startsWith('wasm-lua-')||['c-float-format.js','timezone-info.js','native-timezone-data.js'].includes(path.basename(p))));
const expectedLua=[...oldLua.map(p=>layout.moves[p]),'nethack-c/wasm/lua-bridge.c','nethack-c/wasm/lua-library.js','js/lua/io-library.js'].sort();
qualifiedHistorical('js/lua/io-library.js');
assert.deepEqual(actualLua,expectedLua,'Lua build source selection differs from relocation plus qualified IO addition');
console.log('PASS: exact Lua build source selection retained across owner separation.');
