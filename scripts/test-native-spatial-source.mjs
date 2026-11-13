// Compare every generated policy body to its retained source AST.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {parse} from 'acorn';
const ast=s=>parse(s,{ecmaVersion:'latest',sourceType:'module'}),clean=n=>JSON.parse(JSON.stringify(n,(k,v)=>['start','end','loc'].includes(k)?undefined:typeof v==='bigint'?String(v)+'n':v));
const original=new Map();for(const name of ['hacklib','cmd','dbridge','engrave','region'])for(const n of ast(fs.readFileSync('js/ported/'+name+'.js','utf8')).body)if(n.type==='ExportNamedDeclaration'&&n.declaration?.type==='FunctionDeclaration')original.set(n.declaration.id.name,n.declaration);
let functions=0;for(const n of ast(fs.readFileSync('js/nethack/native/spatial-policy.js','utf8')).body){assert.equal(n.type,'ExportNamedDeclaration');const factory=n.declaration;assert.equal(factory.params[0].name,'C');for(const node of factory.body.body){if(node.type==='ReturnStatement')continue;assert.equal(node.type,'FunctionDeclaration');assert.deepEqual(clean(node),clean(original.get(node.id.name)),node.id.name+' original policy');functions++;}}
assert.equal(functions,19);console.log(JSON.stringify({passed:true,functions,sourcePolicyAstEqual:true}));
