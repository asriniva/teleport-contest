// Invert only the three row setters, then compare every original policy AST.
import fs from 'node:fs';import assert from 'node:assert/strict';import {parse} from 'acorn';
const options={ecmaVersion:'latest',sourceType:'module'},source=parse(fs.readFileSync('js/ported/vision.js','utf8'),options),native=parse(fs.readFileSync('js/nethack/native/vision.js','utf8'),options);
const body=native.body[0].declaration.body.body.slice(0,-1);let setters=0;
function clean(n){if(Array.isArray(n))return n.map(clean);if(!n||typeof n!=='object')return n;
 if(n.type==='CallExpression'&&n.callee?.object?.name==='C'&&n.callee.property?.name==='nativeVisionRow'){
  setters++;assert.equal(n.arguments.length,3);assert.ok(['cs_rows0','cs_rows1','viz_clear_rows'].includes(n.arguments[0].property.name));
  return clean({type:'AssignmentExpression',operator:'=',left:{type:'MemberExpression',computed:true,optional:false,object:n.arguments[0],property:n.arguments[1]},right:n.arguments[2]});
 }
 return Object.fromEntries(Object.entries(n).filter(([k])=>!['start','end','loc','raw'].includes(k)).map(([k,v])=>[k,clean(v)]));
}
const expected=source.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
assert.deepEqual(clean(body),clean(expected),'all vision source decisions and ordered RNG statements after inverse row lowering');assert.equal(setters,3);
console.log('PASS complete native vision source AST; exactly three native row setters');
