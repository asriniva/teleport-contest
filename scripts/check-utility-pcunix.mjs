import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import path from 'node:path';
const arg=process.argv.indexOf('--source-root');if(arg<0)throw Error('--source-root required');const root=path.resolve(process.argv[arg+1]);
const acorn=await import(pathToFileURL(root+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const original=readFileSync(root+'/nethack-c/upstream/sys/share/pcunix.c','utf8'),source=readFileSync(new URL('../js/ported-utilities/pcunix.js',import.meta.url),'utf8');
const inventory=JSON.parse(readFileSync(new URL('../nethack-c/wasm/utilities/pcunix/inventory.json',import.meta.url),'utf8'));assert.deepEqual(inventory.functions,[{name:'regularize',parameters:['s']}]);
function check(text){const t=acorn.parse(text,{sourceType:'module',ecmaVersion:'latest'}),f=t.body.filter(n=>n.type==='ExportNamedDeclaration').map(n=>n.declaration);assert.equal(f.length,1);assert.equal(f[0].id.name,'regularize');assert.deepEqual(f[0].params.map(n=>n.name),['s']);let loops=0,ifs=0;function walk(n){if(!n||typeof n!=='object')return;if(n.type==='ForStatement')loops++;if(n.type==='IfStatement')ifs++;for(const v of Object.values(n))if(Array.isArray(v))v.forEach(walk);else if(v&&typeof v==='object')walk(v);}walk(f[0]);assert.equal(loops,1);assert.equal(ifs,1);const comment=original.slice(original.indexOf('/*\n * normalize file'),original.indexOf('*/',original.indexOf('/*\n * normalize file'))+2);assert.ok(text.includes(comment));assert.ok(text.startsWith(original.slice(0,original.indexOf('#include'))));}
check(source);assert.throws(()=>check(source.replace('regularize(s)','regularize(pointer)')));console.log('PASS1function/1formal/1for/1if/original active comments; wrongformal negative');
