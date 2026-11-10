#!/usr/bin/env node
// Independent original-source projection for Lua registration identity/order.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL,fileURLToPath} from 'node:url';
import * as core from '../js/ported/nhlobj.js';
const root=resolve(fileURLToPath(new URL('..',import.meta.url))),source=readFileSync(resolve(root,'.cache/wasm64-build/tree/src/nhlobj.c'),'utf8'),js=readFileSync(resolve(root,'js/ported/nhlobj.js'),'utf8');
const {parse}=await import(pathToFileURL(resolve(process.env.EMSDK??resolve(root,'.cache/emsdk'),'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const ast=parse(js,{sourceType:'module',ecmaVersion:'latest'}),functions=ast.body.filter(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.type==='FunctionDeclaration').map(n=>n.declaration);
const expected=[...source.matchAll(/^([a-zA-Z_]\w*)\(([^\n]*)\)\n\{/gm)].map(m=>({name:m[1],params:m[2].split(',').map(p=>p.trim().match(/(\w+)$/)[1])}));
assert.equal(expected.length,21);assert.deepEqual(functions.map(n=>({name:n.id.name,params:n.params.map(p=>p.name)})),expected);
for(const comment of source.match(/\/\*[\s\S]*?\*\//g)||[])assert.ok(js.includes(comment),'Missing original comment '+comment);
for(const name of ['l_obj_methods','l_obj_meta']){const match=source.match(new RegExp('\\b'+name+'\\[\\]\\s*=\\s*\\{([\\s\\S]*?)\\n\\};'));assert.ok(match);const pairs=[...match[1].matchAll(/\{\s*("[^"]*"|NULL),\s*(\w+)\s*\}/g)].map(m=>[m[1]==='NULL'?0:JSON.parse(m[1]),m[2]==='NULL'?0:m[2]]);assert.deepEqual(core[name].map(row=>[row.name,row.func?Object.entries(core).find(([k,v])=>v===row.func)[0]:0]),pairs);const declaration=ast.body.find(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.declarations?.some(d=>d.id.name===name));assert.equal(declaration.declaration.declarations[0].init.type,'ArrayExpression');const mutation=pairs.map(row=>row.slice());mutation[0][0]='wrong';assert.throws(()=>assert.deepEqual(core[name].map(r=>[r.name,r.func?Object.entries(core).find(([k,v])=>v===r.func)[0]:0]),mutation));}
assert.ok(source.includes('#define lobj_is_ok(lo) ((lo) && (lo)->obj && (lo)->obj->where != OBJ_LUAFREE)'));
assert.equal((js.match(/lo && lo\.obj && lo\.obj\.where != C\.OBJ_LUAFREE/g)||[]).length,5);assert.equal((js.match(/lobox && lobox\.obj && lobox\.obj\.where != C\.OBJ_LUAFREE/g)||[]).length,1);
assert.ok(js.includes('let class_ = C.short(C.get_table_objclass(L));'));assert.ok(!functions.some(f=>f.params.some(p=>p.name==='class_')));
console.log('NHLOBJ 21 original boundaries/parameters/comments and both registration tables passed (two rejected data mutations).');
