// Test-only body-entry coverage of existing independent C differential suites.
import {registerHooks} from 'node:module';
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {parse} from 'acorn';
const moduleName=process.argv[2],targets={objnam:{flag:'NATIVE_OBJNAM_FIXTURE',count:87},do_wear:{flag:'NATIVE_DO_WEAR_FIXTURE',count:79},weapon:{flag:'NATIVE_WEAPON_FIXTURE',count:40},do:{flag:'NATIVE_DO_FIXTURE',count:44},pline:{flag:'NATIVE_PLINE_FIXTURE',count:31}};
const target=targets[moduleName];if(!target)throw Error('Expected objnam, weapon, do_wear, do or pline');
const called=new Set();let expected=[];globalThis.__nativeBoundBodyEntries=called;
const hook=registerHooks({load(url,context,next){
 const result=next(url,context);if(!url.endsWith('/js/nethack/native/'+moduleName+'.js'))return result;
 let source=typeof result.source==='string'?result.source:Buffer.from(result.source).toString();
 const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),functions=ast.body[0].declaration.body.body.filter(n=>n.type==='FunctionDeclaration');expected=functions.map(n=>n.id.name);
 for(const n of functions.sort((a,b)=>b.body.start-a.body.start))source=source.slice(0,n.body.start+1)+'globalThis.__nativeBoundBodyEntries.add('+JSON.stringify(n.id.name)+');'+source.slice(n.body.start+1);
 return{...result,source};
}});
try{
 process.env[target.flag]='1';await import('./test-tu-'+moduleName+'.mjs');
 assert.equal(expected.length,target.count);const missing=expected.filter(name=>!called.has(name));assert.deepEqual(missing,[],'every native '+moduleName+' body executes in the C differential');
 fs.mkdirSync('.cache',{recursive:true});fs.writeFileSync('.cache/native-'+moduleName+'-body-coverage.json',JSON.stringify({expected,called:[...called].sort(),missing},null,2)+'\n');
 console.log(JSON.stringify({passed:true,module:moduleName,bodies:called.size,missing}));
}finally{hook.deregister();delete globalThis.__nativeBoundBodyEntries;}
