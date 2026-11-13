import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
const {parse}=await import(pathToFileURL(process.argv[2]??'.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
let functions=0,locals=0;
function clean(node){
 if(Array.isArray(node))return node.map(clean);if(!node||typeof node!=='object')return node;
 if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'&&node.callee.property.name==='callLocal'){locals++;node={...node,callee:node.arguments[0],arguments:node.arguments.slice(1)};}
 return Object.fromEntries(Object.entries(node).filter(([key])=>!['start','end','raw'].includes(key)).map(([key,value])=>[key,clean(value)]));
}
for(const name of ['rnd']){
 const old=parse(fs.readFileSync('js/ported/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const next=parse(fs.readFileSync('js/nethack/native/rng.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const expected=old.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
 const body=next.body.find(n=>n.type==='ExportNamedDeclaration').declaration.body.body;assert.equal(body.at(-1).type,'ReturnStatement');
 assert.deepEqual(clean(body.slice(0,-1)),clean(expected),name+' policy/RNG AST');functions+=expected.filter(n=>n.type==='FunctionDeclaration').length;
}
console.log(JSON.stringify({passed:true,modules:1,functions,localCallConversions:locals,sourcePolicyAstEqual:true}));
