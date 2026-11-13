import assert from 'node:assert/strict';
import fs from 'node:fs';
import {parse} from 'acorn';
let locals=0;
function clean(node){
 if(Array.isArray(node))return node.map(clean);if(!node||typeof node!=='object')return node;
 if(node.type==='MemberExpression'&&node.property.name==='a'&&node.object.type==='MemberExpression'&&node.object.object.type==='MemberExpression'&&node.object.object.object.name==='C'&&node.object.object.property.name==='u'){const alias={abon:'ABON',atemp:'ATEMP',acurr:'ABASE'}[node.object.property.name];if(alias)node={type:'MemberExpression',object:{type:'Identifier',name:'C'},property:{type:'Identifier',name:alias},computed:false,optional:false};}
 if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'&&node.callee.property.name==='callLocal'){locals++;node={...node,callee:node.arguments[0],arguments:node.arguments.slice(1)};}
 return Object.fromEntries(Object.entries(node).filter(([key])=>!['start','end','raw'].includes(key)).map(([key,value])=>[key,clean(value)]));
}
const before=parse(fs.readFileSync('js/ported/attrib.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),after=parse(fs.readFileSync('js/nethack/native/attrib.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),factory=after.body[0].declaration;
assert.equal(factory.id.name,'createNativeAttrib','native factory export remains connected');
const expected=before.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n),actual=factory.body.body.slice(0,-1);
assert.deepEqual(clean(actual),clean(expected),'complete original attribute policy AST, with direct local calls');
const functions=expected.filter(n=>n.type==='FunctionDeclaration').length;assert.equal(functions,34);console.log(JSON.stringify({passed:true,functions,localCallConversions:locals,sourcePolicyAstEqual:true}));
