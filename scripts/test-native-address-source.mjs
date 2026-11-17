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
let functions=0,operations=0,nativeValueAllocations=0,nativeRngCallers=0;
for(const[name,{schema}]of Object.entries(ports)){
 const old=parse(fs.readFileSync('js/ported/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const next=parse(fs.readFileSync('js/nethack/native/address/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const windowBindings=new Map();
 for(const n of next.body[0].declaration.body.body)if(n.type==='VariableDeclaration')for(const d of n.declarations)if(/^NWC\d+$/.test(d.id.name)){
  assert.equal(name,'cmd');assert.equal(d.init.callee.object.name,'C');assert.equal(d.init.callee.property.name,'nativeWindowCall');
  assert.ok(d.init.arguments.every(a=>a.type==='Literal'&&typeof a.value==='string'));windowBindings.set(d.id.name,d.init.arguments);
 }
 const fields=Object.entries(schema.schema).flatMap(([kind,row])=>row.fields.map(f=>({kind,field:f.name})));
 function lvalue(id,at,property='value'){
  const f=fields[id];assert.ok(f);operations++;
  return member(call(member(identifier('C'),'field'),[at,literal(f.kind),literal(f.field)]),property);
 }
 function invert(node){
  if(Array.isArray(node))return node.map(invert);if(!node||typeof node!=='object')return node;
  node=Object.fromEntries(Object.entries(node).map(([k,v])=>[k,invert(v)]));
  if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'&&node.callee.property.name==='nativeRngCaller'){
   assert.equal(node.arguments.length,3);for(const arg of [node.arguments[0],node.arguments[2]])assert.ok(arg.type==='Literal'&&typeof arg.value==='string');nativeRngCallers++;
   return call(member(identifier('C'),'rng_log_set_caller'),node.arguments.map((arg,i)=>i===1?arg:call(member(identifier('C'),'literal'),[arg])));
  }
  if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'&&node.callee.property.name==='nativeLocalRecord'){
   assert.ok(name==='display'&&node.arguments.length===1&&node.arguments[0].type==='Literal'&&node.arguments[0].value==='struct glyphinfo','Unexpected native display value allocation');
   nativeValueAllocations++;
   const size={type:'MemberExpression',object:member(identifier('C'),'sizes'),property:literal('struct glyphinfo'),computed:true,optional:false};
   return call(member(identifier('C'),'stackAlloc'),[size]);
  }
  if(node.type==='CallExpression'&&node.callee.type==='Identifier'){
   if(windowBindings.has(node.callee.name)){const [field,prototype]=windowBindings.get(node.callee.name),value=node.arguments[0];assert.equal(value.object.arguments[1].value,'window_procs');assert.equal(value.object.arguments[2].value,field.value);return call(member(identifier('C'),'callProc'),[value,prototype,...node.arguments.slice(1)]);}
   const m=node.callee.name.match(/^([RWA])(\d+)$/);
   if(m){const id=Number(m[2]);if(m[1]==='W')return {type:'AssignmentExpression',operator:'=',left:lvalue(id,node.arguments[0]),right:node.arguments[1]};return lvalue(id,node.arguments[0],m[1]==='A'?'address':'value');}
  }
  return node;
 }
 if(name==='display'){assert.throws(()=>invert(call(member(identifier('C'),'nativeLocalRecord'),[literal('struct monst')])),/Unexpected native display value allocation/);assert.throws(()=>invert(call(member(identifier('C'),'nativeLocalRecord'),[literal('struct glyphinfo'),literal(1)])),/Unexpected native display value allocation/);}
 const factory=next.body[0].declaration;assert.equal(factory.id.name,'createNativeAddressNamespace');
 const actual=factory.body.body.filter((n,i,all)=>{
  if(i===all.length-1){assert.equal(n.type,'ReturnStatement');assert.equal(n.argument.callee.object.name,'C');assert.equal(n.argument.callee.property.name,'nativeAddressNamespaceReady');assert.equal(n.argument.arguments.length,2);assert.equal(n.argument.arguments[1].name,'C');assert.equal(n.argument.arguments[0].callee.object.name,'Object');assert.equal(n.argument.arguments[0].callee.property.name,'freeze');assert.equal(n.argument.arguments[0].arguments.length,1);const exported=n.argument.arguments[0].arguments[0];assert.equal(exported.type,'ObjectExpression');const names=old.body.filter(x=>x.type==='ExportNamedDeclaration').flatMap(x=>x.declaration.id?[x.declaration.id.name]:x.declaration.declarations.map(d=>d.id.name));assert.deepEqual(exported.properties.map(p=>{assert.equal(p.type,'Property');assert.equal(p.shorthand,true);assert.equal(p.computed,false);assert.equal(p.key.name,p.value.name);return p.key.name;}),names,'every original namespace export stays connected');return false;}
  if(n.type==='VariableDeclaration'&&n.declarations.every(d=>d.id.name==='NF'||/^(?:[RWA]|NWC)\d+$/.test(d.id.name)))return false;
  return true;
 });
 const expected=old.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
 assert.deepEqual(clean(invert(actual)),clean(expected),name+' source policy/RNG AST after inverse lowering');
 functions+=expected.filter(n=>n.type==='FunctionDeclaration').length;
}
assert.equal(nativeValueAllocations,3,'remaining native DISPLAY glyph values invert to their original allocations');
assert.equal(nativeRngCallers,526);
console.log(JSON.stringify({passed:true,nativeRngCallers,nativeValueAllocations,ports:Object.keys(ports).length,functions,invertedFieldOperations:operations,sourcePolicyAstEqual:true}));
