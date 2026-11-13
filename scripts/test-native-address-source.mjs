// Invert the lowering at AST level and compare every source policy node.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
const {parse}=await import(process.argv[2]?pathToFileURL(process.argv[2]):'acorn');
const ports=JSON.parse(fs.readFileSync('js/nethack/address-ports.json')).ports;
ports.cmd={schema:JSON.parse(fs.readFileSync('js/nethack/command-abi.json')).schema};
const identifier=name=>({type:'Identifier',name});
const literal=value=>({type:'Literal',value});
const member=(object,property)=>({type:'MemberExpression',object,property:identifier(property),computed:false,optional:false});
const call=(callee,args)=>({type:'CallExpression',callee,arguments:args,optional:false});
function clean(v){if(Array.isArray(v))return v.map(clean);if(!v||typeof v!=='object')return v;return Object.fromEntries(Object.entries(v).filter(([k])=>!['start','end','raw'].includes(k)).map(([k,x])=>[k,clean(x)]));}
let functions=0,operations=0;
for(const[name,{schema}]of Object.entries(ports)){
 const old=parse(fs.readFileSync('js/ported/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const next=parse(fs.readFileSync('js/nethack/native/address/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const fields=Object.entries(schema.schema).flatMap(([kind,row])=>row.fields.map(f=>({kind,field:f.name})));
 function lvalue(id,at,property='value'){
  const f=fields[id];assert.ok(f);operations++;
  return member(call(member(identifier('C'),'field'),[at,literal(f.kind),literal(f.field)]),property);
 }
 function invert(node){
  if(Array.isArray(node))return node.map(invert);if(!node||typeof node!=='object')return node;
  node=Object.fromEntries(Object.entries(node).map(([k,v])=>[k,invert(v)]));
  if(node.type==='CallExpression'&&node.callee.type==='Identifier'){
   const m=node.callee.name.match(/^([RWA])(\d+)$/);
   if(m){const id=Number(m[2]);if(m[1]==='W')return {type:'AssignmentExpression',operator:'=',left:lvalue(id,node.arguments[0]),right:node.arguments[1]};return lvalue(id,node.arguments[0],m[1]==='A'?'address':'value');}
  }
  return node;
 }
 const factory=next.body[0].declaration;assert.equal(factory.id.name,'createNativeAddressNamespace');
 const actual=factory.body.body.filter((n,i,all)=>{
  if(i===all.length-1){assert.equal(n.type,'ReturnStatement');return false;}
  if(n.type==='VariableDeclaration'&&n.declarations.every(d=>d.id.name==='NF'||/^[RWA]\d+$/.test(d.id.name)))return false;
  return true;
 });
 const expected=old.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
 assert.deepEqual(clean(invert(actual)),clean(expected),name+' source policy/RNG AST after inverse lowering');
 functions+=expected.filter(n=>n.type==='FunctionDeclaration').length;
}
console.log(JSON.stringify({passed:true,ports:Object.keys(ports).length,functions,invertedFieldOperations:operations,sourcePolicyAstEqual:true}));
