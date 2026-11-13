import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
const {parse}=await import(pathToFileURL(process.argv[2]??'.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const old=parse(fs.readFileSync('js/ported/allmain.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
const next=parse(fs.readFileSync('js/nethack/native/turn-loop.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
let scopes=0,locals=0;
function clean(node){
 if(Array.isArray(node))return node.map(clean);
 if(!node||typeof node!=='object')return node;
 if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'){
  if(node.callee.property.name==='nativeTurn'){assert.equal(node.arguments[0].name,'moveloop_core');scopes++;node={...node,callee:node.arguments[0],arguments:[]};}
  else if(node.callee.property.name==='callLocal'){locals++;node={...node,callee:node.arguments[0],arguments:node.arguments.slice(1)};}
 }
 return Object.fromEntries(Object.entries(node).filter(([key])=>!['start','end','raw'].includes(key)).map(([key,value])=>[key,clean(value)]));
}
const expected=old.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
const factory=next.body[0].declaration;assert.equal(factory.id.name,'createNativeTurnLoop');
const actual=factory.body.body.slice(0,-1);assert.equal(factory.body.body.at(-1).type,'ReturnStatement');
assert.deepEqual(clean(actual),clean(expected));assert.equal(scopes,1);assert.equal(locals,1);
console.log(JSON.stringify({passed:true,functions:expected.filter(n=>n.type==='FunctionDeclaration').length,localCallConversions:locals,perTurnScopes:scopes,sourcePolicyAstEqual:true}));
