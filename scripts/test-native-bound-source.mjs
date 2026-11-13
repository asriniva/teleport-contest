import fs from 'node:fs';
import assert from 'node:assert/strict';
import {parse} from 'acorn';
function clean(v){if(Array.isArray(v))return v.map(clean);if(!v||typeof v!=='object')return v;return Object.fromEntries(Object.entries(v).filter(([k])=>!['start','end','raw'].includes(k)).map(([k,x])=>[k,clean(x)]));}
for(const [name,factory]of [['mondata','createNativeMondata'],['stairs','createNativeStairs']]){
 const before=parse(fs.readFileSync('js/ported/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),after=parse(fs.readFileSync('js/nethack/native/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const fn=after.body[0].declaration;assert.equal(fn.id.name,factory);assert.deepEqual(fn.params.map(x=>x.name),['C']);
 const expected=before.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
 assert.deepEqual(clean(fn.body.body.slice(0,-1)),clean(expected),'complete source policy '+name);
 const names=before.body.filter(n=>n.type==='ExportNamedDeclaration').flatMap(n=>n.declaration.id?[n.declaration.id.name]:n.declaration.declarations.map(d=>d.id.name));
 assert.deepEqual(fn.body.body.at(-1).argument.properties.map(p=>p.key.name),names,'all source exports stay connected');
 console.log(JSON.stringify({passed:true,module:name,functions:expected.filter(n=>n.type==='FunctionDeclaration').length,sourcePolicyAstEqual:true}));
}
