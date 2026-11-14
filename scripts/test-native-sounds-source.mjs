import assert from 'node:assert/strict';
import fs from 'node:fs';
import {parse} from 'acorn';
let locals=0;
function clean(node){
 if(Array.isArray(node))return node.map(clean);if(!node||typeof node!=='object')return node;
 if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'&&node.callee.property.name==='callLocal'){locals++;node={...node,callee:node.arguments[0],arguments:node.arguments.slice(1)};}
 return Object.fromEntries(Object.entries(node).filter(([key])=>!['start','end','raw'].includes(key)).map(([key,value])=>[key,clean(value)]));
}
const before=parse(fs.readFileSync('js/ported/sounds.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),after=parse(fs.readFileSync('js/nethack/native/sounds.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),factory=after.body[0].declaration;
assert.equal(factory.id.name,'createNativeSounds','native factory export remains connected');
const expected=before.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n),actual=factory.body.body.slice(0,-1);
assert.deepEqual(clean(actual),clean(expected),'complete original sound policy AST, with direct local calls');
const functions=expected.filter(n=>n.type==='FunctionDeclaration').length;const returned=factory.body.body.at(-1);assert.equal(returned.type,"ReturnStatement");assert.deepEqual(returned.argument.properties.map(p=>p.key.name),expected.flatMap(n=>n.id?[n.id.name]:n.declarations?.map(d=>d.id.name)??[]),"all original exports remain connected");console.log(JSON.stringify({passed:true,functions,localCallConversions:locals,sourcePolicyAstEqual:true}));
