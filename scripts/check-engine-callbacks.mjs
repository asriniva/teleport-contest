// Typed callback-field checks independent of reaching a runtime branch.
import fs from 'node:fs';import path from 'node:path';import assert from 'node:assert/strict';
import {parse} from '../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
import {isEngine} from './branch-coverage/loader.mjs';
const metadata=JSON.parse(fs.readFileSync(new URL('../js/nethack/records.json',import.meta.url))),records=metadata.records;
const recordFor=value=>value==='struct window_procs'||value==='window_procs'?records.window_procs:value==='struct sound_procs'||value==='sound_procs'?records.sound_procs:undefined;
const literal=node=>node?.type==='Literal'?node.value:node?.type==='TemplateLiteral'&&!node.expressions.length?node.quasis[0].value.cooked:undefined;
function walk(node,fn,parent){if(!node||typeof node!=='object')return;if(Array.isArray(node)){for(const n of node)walk(n,fn,parent);return;}if(!node.type)return;fn(node,parent);for(const[k,v]of Object.entries(node))if(!['loc','start','end','type'].includes(k))walk(v,fn,node);}
function lookup(node){
 if(node.type==='MemberExpression'){
  const field=node.computed?node.property:{type:'Literal',value:node.property.name},object=node.object;
  // ctypes.record('struct window_procs').fields[name]
  if(object.type==='MemberExpression'&&object.property.name==='fields'&&object.object.type==='CallExpression'&&object.object.callee.type==='MemberExpression'&&object.object.callee.property.name==='record'){
   const record=recordFor(literal(object.object.arguments[0]));if(record)return{record,field};
  }
  // ABI records['struct window_procs'][name]
  if(object.type==='MemberExpression'&&object.computed&&object.object.type==='MemberExpression'&&object.object.property.name==='records'){
   const record=recordFor(literal(object.property));if(record)return{record,field};
  }
 }
 if(node.type!=='CallExpression'||node.callee.type!=='MemberExpression')return;
 const method=node.callee.property.name;if(['locate','getField','setField'].includes(method)){const record=recordFor(literal(node.arguments[0]));if(record)return{record,field:node.arguments[2]};}
 if(method==='field'){const record=recordFor(literal(node.arguments[1]));if(record)return{record,field:node.arguments[2]};}
}
function callbackSignature(ctype){
 const match=/^(.*?)\s*\(\s*\*\s*\)\s*\((.*)\)/.exec(ctype);if(!match)return undefined;
 const scalar=raw=>{let type=raw.replace(/\b(?:const|volatile|restrict)\b/g,'').replace(/\s+/g,' ').trim();if(type.includes('*')||type.includes('['))return'p';const seen=new Set();while(metadata.aliases[type]&&!seen.has(type)){seen.add(type);type=metadata.aliases[type];}if(type==='void')return'v';if(type==='float')return'f';if(type==='double')return'd';if(/\blong\b/.test(type))return'j';return'i';};
 const args=match[2].trim();return scalar(match[1])+(args==='void'||!args?'':args.split(',').map(scalar).join(''));
}
export function checkCallbackSource(source,file){
 const ast=parse(source,{ecmaVersion:'latest',sourceType:'module',locations:true}),helpers=new Map(),sites=[],dynamic=[],typedFields=[],unresolvedTypes=[];
 walk(ast,(node,parent)=>{if(!['ArrowFunctionExpression','FunctionExpression','FunctionDeclaration'].includes(node.type))return;const name=node.id?.name??(parent?.type==='VariableDeclarator'?parent.id.name:undefined);if(!name)return;
  walk(node.body,child=>{const info=lookup(child);if(!info||info.field?.type!=='Identifier')return;const index=node.params.findIndex(p=>p.type==='Identifier'&&p.name===info.field.name);if(index>=0)helpers.set(name,{record:info.record,index,signatureIndex:undefined});});
 });
 walk(ast,(node,parent)=>{if(!['ArrowFunctionExpression','FunctionExpression','FunctionDeclaration'].includes(node.type))return;const name=node.id?.name??(parent?.type==='VariableDeclarator'?parent.id.name:undefined);if(!helpers.has(name))return;walk(node.body,child=>{if(child.type==='CallExpression'&&child.callee.type==='MemberExpression'&&child.callee.property.name==='indirect'&&child.arguments[1]?.type==='Identifier'){const i=node.params.findIndex(p=>p.type==='Identifier'&&p.name===child.arguments[1].name);if(i>=0)helpers.get(name).signatureIndex=i;}});});
 let changed=true;while(changed){changed=false;walk(ast,node=>{if(node.type==='VariableDeclarator'&&node.id.type==='Identifier'&&node.init?.type==='Identifier'&&helpers.has(node.init.name)&&!helpers.has(node.id.name)){helpers.set(node.id.name,helpers.get(node.init.name));changed=true;}});}
 function check(record,field,node){const value=literal(field);if(value===undefined){dynamic.push({file,line:node.loc.start.line});return;}
  assert.ok(typeof value==='string'&&Object.hasOwn(record.fields,value),file+':'+node.loc.start.line+': unknown measured callback field '+value);sites.push({file,line:node.loc.start.line,field:value});
 }
 walk(ast,node=>{
  if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'){
   const method=node.callee.property.name,typeIndex=['locate','getField','setField'].includes(method)?0:method==='field'?1:undefined;
   if(typeIndex!==undefined){const sourceType=literal(node.arguments[typeIndex]),field=literal(node.arguments[2]);if(typeof sourceType==='string'&&typeof field==='string'){
    let type=sourceType;const seen=new Set();while(metadata.aliases[type]&&!seen.has(type)){seen.add(type);type=metadata.aliases[type];}type=type.replace(/^(?:struct|union) /,'');
    const record=records[type];if(record&&Object.keys(record.fields??{}).length){assert.ok(Object.hasOwn(record.fields,field),file+':'+node.loc.start.line+': unknown measured record field '+sourceType+'.'+field);typedFields.push({file,line:node.loc.start.line,type:sourceType,field});}else unresolvedTypes.push({file,line:node.loc.start.line,type:sourceType,field});
   }}
  }
  const direct=lookup(node);if(direct)check(direct.record,direct.field,node);
  if(node.type==='CallExpression'&&node.callee.type==='Identifier'&&helpers.has(node.callee.name)){const h=helpers.get(node.callee.name);check(h.record,node.arguments[h.index],node);const field=literal(node.arguments[h.index]),signature=literal(node.arguments[h.signatureIndex]);if(field!==undefined&&typeof signature==='string'&&/^[vifdjp]+$/.test(signature)){const expected=callbackSignature(h.record.fields[field].ctype);assert.equal(signature,expected,file+':'+node.loc.start.line+': callback signature '+field);}}
 });return{sites,dynamic,typedFields,unresolvedTypes};
}
export function checkEngineCallbacks(){const sites=[],dynamic=[],typedFields=[],unresolvedTypes=[];let modules=0;function visit(dir){for(const row of fs.readdirSync(dir,{withFileTypes:true})){const p=path.posix.join(dir,row.name);if(row.isDirectory())visit(p);else if(isEngine(p)){modules++;const result=checkCallbackSource(fs.readFileSync(p,'utf8'),p);sites.push(...result.sites);dynamic.push(...result.dynamic);typedFields.push(...result.typedFields);unresolvedTypes.push(...result.unresolvedTypes);}}}visit('js');return{modules,sites,dynamic,typedFields,unresolvedTypes};}
if(process.argv[1]===new URL(import.meta.url).pathname){const result=checkEngineCallbacks();assert.ok(result.sites.length>=81);
 for(const expression of ["'win_nh_delay_output'",'`win_nh_delay_output`',"'win_\\u006eh_delay_output'"]){assert.throws(()=>checkCallbackSource("const differentlyNamed=field=>ctypes.locate('struct window_procs',0,field);differentlyNamed("+expression+");",'injected-typo.js'),/unknown measured callback/);}
 assert.throws(()=>checkCallbackSource("const other=(field,sig)=>functions.indirect(ctypes.locate('struct window_procs',0,field).at,sig);other('win_delay_output','vi');",'injected-signature.js'),/callback signature/);
 assert.throws(()=>checkCallbackSource("const other=name=>ctypes.record('struct window_procs').fields[name];other('win_nh_delay_output');",'injected-record-metadata.js'),/unknown measured callback/);
 assert.throws(()=>checkCallbackSource("const other=name=>abi.records['struct window_procs'][name];other('win_nh_delay_output');",'injected-abi-metadata.js'),/unknown measured callback/);
 assert.throws(()=>checkCallbackSource("ctypes.getField('struct obj',0,'definitely_not_an_object_field');",'injected-record-field.js'),/unknown measured record field/);
 const uhitm=fs.readFileSync('js/nethack/uhitm.js','utf8');
 assert.ok(uhitm.includes("window('win_delay_output','v')"),'real UHITM dispatch site');
 assert.throws(()=>checkCallbackSource(uhitm.replace("window('win_delay_output','v')","window('win_nh_delay_output','v')"),'original-engulf-typo.js'),/unknown measured callback/);
 console.log('PASS: '+result.typedFields.length+' measured record fields and '+result.sites.length+' literal window/sound field lookups across '+result.modules+' engine modules; helper aliases/templates/escaped typos and incompatible literal signatures rejected. '+result.dynamic.length+' dynamic lookups remain runtime coverage obligations.');
}
