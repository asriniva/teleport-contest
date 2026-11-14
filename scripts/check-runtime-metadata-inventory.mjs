// One explicit inventory for runtime metadata, support data and inline tables.
// Unknown JSON sources require classification rather than silently escaping gates.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import assert from 'node:assert/strict';import {parse} from 'acorn';
const groups={
 shared_declarations:['js/nethack/records.json','js/nethack/supplemental-record-layouts.json'],
 public_functions:['js/nethack/public-functions.json'],
 layouts_and_plans:['js/wasm/tu-layouts.json','js/nethack/display-direct-fields.json','js/nethack/do-name-native-layout.json','js/nethack/weapon-native-layout.json'],
 runtime_recipes_profiles:['js/nethack/decl-storage.json','js/nethack/lua-api.json','js/nethack/terminal-metadata.json','js/c-runtime/libc-profile.json'],
 supporting_data_manifests:['js/nethack/game-assets.json','js/nethack/game-assets-manifest.json','js/c-runtime/errno-messages.json','js/wasm/build.json','js/wasm/drawing-constants.json','js/ported-utilities/tilemap-generator-constants.json','js/ported-utilities/tilemap-generator-formats.json','js/ported-utilities/random-data.json'],
};
const metadataNames=new Set(['schema','schemas','globals','nativeReturns','nativeTypes','typeAliases','fieldAliases','signatures','callbackTypes','fieldTypes','scalarTypes','primitive','scalars','recordTypes','types','aliases','sizes','fields']);
const isMetadataName=name=>metadataNames.has(name)||/(?:Schema|Schemas|Metadata|TypeAliases|FieldAliases|CallbackTypes|FieldTypes|ScalarTypes|FunctionTypes)$/.test(name);
const literal=node=>['ObjectExpression','ArrayExpression'].includes(node?.type)||node?.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='Object'&&node.callee.property.name==='freeze'&&literal(node.arguments[0]);
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
function files(dir){return fs.readdirSync(dir,{withFileTypes:true}).flatMap(row=>row.isDirectory()?files(path.posix.join(dir,row.name)):[path.posix.join(dir,row.name)]).sort();}
export function runtimeMetadataInventory(){
 const all=files('js'),sources=[],inlineTables=[];
 for(const file of all.filter(file=>file.endsWith('.json'))){
  let group=Object.entries(groups).find(([,values])=>values.includes(file))?.[0];
  if(/^js\/nethack\/[^/]+-abi\.json$/.test(file)||file==='js/nethack/address-ports.json'||file==='js/platform/darwin/terminal-abi.json')group='component_abis';
  assert.ok(group,'Unclassified runtime metadata/data source '+file);sources.push({file,group,sha256:sha(file)});
 }
 for(const file of Object.values(groups).flat())assert.ok(sources.some(row=>row.file===file),'Missing catalog '+file);
 for(const file of all.filter(file=>file.endsWith('.js')&&!file.startsWith('js/wasm/'))){
  const ast=parse(fs.readFileSync(file,'utf8'),{ecmaVersion:'latest',sourceType:'module',locations:true});
  function walk(node){if(!node||typeof node!=='object')return;if(Array.isArray(node)){node.forEach(walk);return;}
   if(node.type==='VariableDeclarator'&&node.id.type==='Identifier'&&isMetadataName(node.id.name)&&literal(node.init))inlineTables.push({file,line:node.loc.start.line,name:node.id.name});
   for(const [key,value]of Object.entries(node))if(!['loc','start','end'].includes(key))walk(value);
  }walk(ast);
 }
 const adapters=all.filter(file=>/^js\/nethack\/bindings\/[^/]+\.js$/.test(file)).map(file=>({file,sha256:sha(file)}));
 const counts=Object.fromEntries([...new Set(sources.map(row=>row.group))].sort().map(group=>[group,sources.filter(row=>row.group===group).length]));
 return{scope:'Every JSON file under js; named literal metadata declarations across non-Wasm JS; all adapter files listed separately. Inline table detection is a source census, not proof of execution coverage. Registration code and computed/unnamed tables require wiring/source checks.',counts,jsonSources:sources.length,coreJsonSources:sources.filter(row=>row.group!=='supporting_data_manifests').length,inlineTableDeclarations:inlineTables.length,inlineTableFiles:new Set(inlineTables.map(row=>row.file)).size,adapterFiles:adapters.length,sharedAliasSource:{file:'js/nethack/declarations.js',sha256:sha('js/nethack/declarations.js')},sources,inlineTables,adapters};
}
if(process.argv[1]===new URL(import.meta.url).pathname){
 const result=runtimeMetadataInventory(),file='docs/runtime-environment/runtime-metadata-inventory.json';
 if(process.argv.includes('--write'))fs.writeFileSync(file,JSON.stringify(result,null,2)+'\n');
 else assert.deepEqual(result,JSON.parse(fs.readFileSync(file,'utf8')),'Runtime metadata inventory changed; update the ledger deliberately');
 console.log(JSON.stringify({passed:true,jsonSources:result.jsonSources,coreJsonSources:result.coreJsonSources,groups:result.counts,inlineTableDeclarations:result.inlineTableDeclarations,inlineTableFiles:result.inlineTableFiles,adapterFiles:result.adapterFiles}));
}
