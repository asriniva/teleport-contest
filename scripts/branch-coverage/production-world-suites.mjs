import fs from 'node:fs';import path from 'node:path';
import {parse} from '../../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
const forbidden=/sessions\/|\.session\.json|session-graph|['"]recordings['"]|recordings[\\/]|literalNativeReplayAccepted|run-standalone-recorder|run-recorder|full-recorder|test-standalone-public-recorder|author-original-c/;
export const expandProductionWorldSuites=suites=>suites.flatMap(name=>name==='test-standalone-obscure-interactions.mjs'?['riding','menus','music','rogue'].map(variant=>({name,variant,args:[variant]})):name==='test-standalone-quest-completion.mjs'?[{name,variant:'controlled-safety-sweep',args:[],environment:{STANDALONE_QUEST_COMPLETION_SAFETY_SWEEP:'1'}}]:[{name,variant:null,args:[]}]);
export function discoverProductionWorldSuites(root,{read=file=>fs.readFileSync(path.join(root,file),'utf8'),names=fs.readdirSync(path.join(root,'scripts'))}={}){
 const memo=new Map();
 function audit(file,seen=new Set()){
  if(seen.has(file))return null;seen.add(file);if(memo.has(file))return memo.get(file);
  const source=read(file);if(forbidden.test(source)){memo.set(file,file);return file;}
  const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),imports=[];
  function visit(node){if(!node||typeof node!=='object')return;
   if(['ImportDeclaration','ExportNamedDeclaration','ExportAllDeclaration','ImportExpression'].includes(node.type)&&typeof node.source?.value==='string')imports.push(node.source.value);
   for(const value of Object.values(node))if(Array.isArray(value))value.forEach(visit);else if(value&&typeof value==='object')visit(value);
  }visit(ast);
  for(const specifier of imports)if(specifier.startsWith('.')){
   const dependency=path.posix.normalize(path.posix.join(path.posix.dirname(file),specifier));
   if(dependency.startsWith('scripts/')&&/\.m?js$/.test(dependency)){const reason=audit(dependency,seen);if(reason){memo.set(file,reason);return reason;}}
  }
  // Positive results are local to this traversal: caching through cycles can
  // otherwise hide a forbidden dependency discovered later in the cycle.
  return null;
 }
 const suites=[],excluded=[];
 for(const name of [...names].sort()){
  if(!/^test-standalone-.*\.mjs$/.test(name)||/recorder|replay/.test(name))continue;
  const file='scripts/'+name,source=read(file);
  if(!/createStandaloneProgram|runStandaloneProgram/.test(source)||!/full-original-c(?:-[\w-]+)?|runFullOriginalC/.test(source))continue;
  const reason=audit(file);if(reason)excluded.push({name,reason});else suites.push(name);
 }
 return{suites,excluded};
}
