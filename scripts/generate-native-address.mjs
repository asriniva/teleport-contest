// Generate game-bound kernels and eliminate ordinary C.field lvalue carriers.
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
const {parse}=await import(process.argv[2]?pathToFileURL(process.argv[2]):'acorn');
const metadata=JSON.parse(fs.readFileSync('js/nethack/address-ports.json')).ports;
metadata.cmd={schema:JSON.parse(fs.readFileSync('js/nethack/command-abi.json')).schema};
const chosen=process.argv.slice(3).filter(x=>x!=='--check'),names=chosen.length?chosen:Object.keys(metadata);
const report={};
for(const name of names){
 const source=fs.readFileSync('js/ported/'+name+'.js','utf8'),ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),schema=metadata[name].schema;
 const fields=new Map();let flat=0;
 for(const[kind,row]of Object.entries(schema.schema))for(const field of row.fields)fields.set(kind+'.'+field.name,{id:flat++,field});
 function hygiene(node){if(!node||typeof node!=='object')return;const bound=node.type==='VariableDeclarator'?[node.id]:/Function/.test(node.type)?[node.id,...(node.params??[])]:[];for(const id of bound)if(id?.type==='Identifier'&&(id.name==='NF'||/^(?:[RWA]|NWC)\d+$/.test(id.name)))throw Error('Native binding collision '+name+':'+id.name);for(const value of Object.values(node))if(Array.isArray(value))value.forEach(hygiene);else if(value&&typeof value==='object')hygiene(value);}
 hygiene(ast);
 const windowCalls=new Map();
 const exports=[],used=new Set(),counts={reads:0,writes:0,addresses:0,compound:0,updates:0};
 function match(node){
  if(node?.type!=='MemberExpression'||node.computed||!['value','address'].includes(node.property.name))return;
  const call=node.object;
  if(call.type!=='CallExpression'||call.callee.type!=='MemberExpression'||call.callee.object.name!=='C'||call.callee.property.name!=='field'||call.arguments.length!==3)return;
  const[at,kind,field]=call.arguments;if(kind.type!=='Literal'||field.type!=='Literal')return;
  const entry=fields.get(kind.value+'.'+field.value);if(!entry)throw Error('Unknown native field '+name+':'+kind.value+'.'+field.value);
  used.add(entry.id);return {...entry,at,op:node.property.name};
 }
 function render(node,shadow=false){
  if(!node||typeof node!=='object'||node.start===undefined)return '';
  if(node.type==='ImportDeclaration'){if(node.source.value!=='../c-runtime/context.js')throw Error('Review native import '+node.source.value);return '';}
  if(node.type==='ExportNamedDeclaration'){
   const d=node.declaration;if(!d)throw Error('Unsupported native re-export');
   if(d.id)exports.push(d.id.name);else for(const row of d.declarations)exports.push(row.id.name);
   return render(d,shadow);
  }
  if(/Function|ArrowFunctionExpression/.test(node.type)&&node.params?.some(p=>p.name==='C'))shadow=true;
  if(!shadow){
   if(name==='cmd'&&node.type==='CallExpression'&&node.callee.object?.name==='C'&&node.callee.property?.name==='callProc'){
    const value=node.arguments[0],access=value?.object;
    if(value?.type==='MemberExpression'&&value.property.name==='value'&&access?.type==='CallExpression'&&access.callee.object?.name==='C'&&access.callee.property?.name==='field'&&access.arguments[0].object?.name==='C'&&access.arguments[0].property?.name==='windowprocs'&&access.arguments[1].value==='window_procs'){
     const field=access.arguments[2].value,prototype=node.arguments[1].value;
     if(typeof field!=='string'||typeof prototype!=='string')throw Error('Review native command window call');
     const key=field+'|'+prototype;if(!windowCalls.has(key))windowCalls.set(key,{id:windowCalls.size,field,prototype});
     return 'NWC'+windowCalls.get(key).id+'('+[node.arguments[0],...node.arguments.slice(2)].map(n=>render(n,shadow)).join(',')+')';
    }
   }
   if(node.type==='AssignmentExpression'){
    const field=match(node.left);
    if(field?.op==='value'){
     counts.writes++;const at=render(field.at,shadow),rhs=render(node.right,shadow);
     if(node.operator==='=')return `W${field.id}(${at},${rhs})`;
     counts.compound++;return `NF.compound(R${field.id},W${field.id},${at},${JSON.stringify(node.operator)},()=>(${rhs}))`;
    }
   }
   if(node.type==='UpdateExpression'){
    const field=match(node.argument);if(field?.op==='value'){counts.updates++;return `NF.update(R${field.id},W${field.id},${render(field.at,shadow)},${JSON.stringify(node.operator)},${node.prefix})`;}
   }
   const field=match(node);if(field){counts[field.op==='address'?'addresses':'reads']++;return `${field.op==='address'?'A':'R'}${field.id}(${render(field.at,shadow)})`;}
  }
  const children=[];
  for(const[k,v]of Object.entries(node))if(!['start','end'].includes(k)){
   if(Array.isArray(v)){for(const child of v)if(child?.start!==undefined)children.push(child);}
   else if(v?.start!==undefined)children.push(v);
  }
  children.sort((a,b)=>a.start-b.start);let cursor=node.start,out='';
  for(const child of children){if(child.start<cursor)continue;out+=source.slice(cursor,child.start)+render(child,shadow);cursor=child.end;}
  return out+source.slice(cursor,node.end);
 }
 const body=render(ast),bindings=[...used].sort((a,b)=>a-b).map(i=>`const R${i}=NF.readers[${i}],W${i}=NF.writers[${i}],A${i}=NF.addresses[${i}];`).join('\n');
 const windowBindings=[...windowCalls.values()].map(({id,field,prototype})=>`const NWC${id}=C.nativeWindowCall(${JSON.stringify(field)},${JSON.stringify(prototype)});`).join('\n');
 const result=`// Generated by scripts/generate-native-address.mjs; original policy and RNG order retained.\nexport function createNativeAddressNamespace(C) {\nconst NF=C.nativeFields;\n${bindings}${windowBindings?'\n'+windowBindings:''}\n${body}\nreturn Object.freeze({${exports.join(',')}});\n}\n`;
 parse(result,{ecmaVersion:'latest',sourceType:'module'});
 const path='js/nethack/native/address/'+name+'.js';
 if(process.argv.includes('--check')){if(fs.readFileSync(path,'utf8')!==result)throw Error('Native address generator drift '+name);}else fs.writeFileSync(path,result);
 report[name]={...counts,fields:used.size,exports:exports.length,nativeWindowBindings:windowCalls.size};
}
console.log(JSON.stringify(report));
