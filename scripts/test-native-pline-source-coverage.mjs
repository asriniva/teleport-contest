// Observe original-C differential execution of every bound message body.
// This loader is test-only; production and frozen sources stay unchanged.
import {registerHooks} from 'node:module';
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {parse} from 'acorn';
const called=new Set();let expected=[];
globalThis.__nativePlineSourceBodies=called;
const hook=registerHooks({load(url,context,next){
 const result=next(url,context);if(!url.endsWith('/js/nethack/native/pline.js'))return result;
 let source=typeof result.source==='string'?result.source:Buffer.from(result.source).toString();
 const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),functions=ast.body[0].declaration.body.body.filter(n=>n.type==='FunctionDeclaration');
 expected=functions.map(n=>n.id.name);
 for(const n of functions.sort((a,b)=>b.body.start-a.body.start))source=source.slice(0,n.body.start+1)+'globalThis.__nativePlineSourceBodies.add('+JSON.stringify(n.id.name)+');'+source.slice(n.body.start+1);
 return{...result,source};
}});
try{
 process.env.NATIVE_PLINE_FIXTURE='1';await import('./test-tu-pline.mjs');
 assert.equal(expected.length,31);const missing=expected.filter(name=>!called.has(name));assert.deepEqual(missing,[],'every native message body executes in the C differential');
 const evidence={expected,called:[...called].sort(),missing};
 fs.mkdirSync('.cache',{recursive:true});fs.writeFileSync('.cache/native-pline-body-coverage.json',JSON.stringify(evidence,null,2)+'\n');
 console.log(JSON.stringify({passed:true,bodies:called.size,missing}));
}finally{hook.deregister();delete globalThis.__nativePlineSourceBodies;}
