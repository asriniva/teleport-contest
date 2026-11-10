#!/usr/bin/env node
// Source-token projection, independent of native table-byte differential tests.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
import * as role from '../js/ported/role.js';
const root=resolve(fileURLToPath(new URL('..',import.meta.url))),src=readFileSync(resolve(root,'.cache/wasm64-build/tree/src/role.c'),'utf8'),header=readFileSync(resolve(root,'.cache/wasm64-build/tree/include/hack.h'),'utf8');
const sdk=resolve(process.env.EMSDK??resolve(root,'.cache/emsdk'));
const {parse}=await import(pathToFileURL(resolve(sdk,'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
function clean(s){return s.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*/g,'');}
function macro(name){const lines=header.split('\n');let i=lines.findIndex(s=>s.startsWith('#define '+name+' ')),s=lines[i++].replace('#define '+name,'');while(s.trimEnd().endsWith('\\'))s=s.trimEnd().slice(0,-1)+'\n'+lines[i++];return s;}
function expected(name){let c=src.slice(0,src.indexOf('staticfn int randrole_filtered'));c=c.replace(/#if 0[^\n]*[\s\S]*?#endif[^\n]*/g,'');for(const n of ['UNDEFINED_ROLE','UNDEFINED_RACE'])c=c.replaceAll(n,macro(n));c=clean(c);const a=c.indexOf('{',c.indexOf(' '+name+'['));let i=a;
 function array(){assert.equal(c[i++],'{');const values=[];while(true){while(/\s|,/.test(c[i]))i++;if(c[i]==='}'){i++;return values;}if(c[i]==='{'){values.push(array());continue;}let start=i,depth=0,quote=null;while(i<c.length){const ch=c[i];if(quote){if(ch==='\\'){i+=2;continue;}if(ch===quote)quote=null;i++;continue;}if(ch==='"'||ch==="'"){quote=ch;i++;continue;}if(ch==='(')depth++;if(ch===')')depth--;if(!depth&&(ch===','||ch==='}'))break;i++;}const token=c.slice(start,i).trim();if(token==='NULL')values.push(0);else if(/^-?\d+$/.test(token))values.push(Number(token));else if(token.startsWith('"'))values.push(JSON.parse(token));else if(token.startsWith("'")){const v=token.slice(1,-1);values.push(v==='\\0'?0:v.charCodeAt(0));}else values.push({c:token.replace(/\s+/g,' ')});}}
 return array();}
const canonical=v=>Array.isArray(v)?v.map(canonical):v&&typeof v==='object'?{c:v.c.replace(/\s+/g,'')}:v;
for(const[name,count]of [['roles',14],['races',6],['genders',4],['aligns',4]]){assert.equal(role[name].length,count);assert.deepEqual(canonical(role[name]),canonical(expected(name)),name);}
const core=readFileSync(resolve(root,'js/ported/role.js'),'utf8'),ast=parse(core,{ecmaVersion:'latest',sourceType:'module'});
// No executable catalogue initializers can replace readable source records.
for(const node of ast.body)if(node.type==='ExportNamedDeclaration'&&node.declaration?.type==='VariableDeclaration')for(const d of node.declaration.declarations)if(['roles','races','genders','aligns'].includes(d.id.name)){function data(n){assert.ok(['ArrayExpression','Literal','ObjectExpression','Property','Identifier','UnaryExpression'].includes(n.type),n.type);if(n.type==='Identifier')assert.equal(n.name,'c');for(const v of Object.values(n))if(Array.isArray(v))v.forEach(x=>x?.type&&data(x));else if(v?.type)data(v);}data(d.init);}
// Numeric/source expression/header correspondences retain exact symbols and order.
const runtime=readFileSync(resolve(root,'js/ported/role-runtime.js'),'utf8'),expr=JSON.parse(runtime.match(/const expressions=(\[[^\n]+\]);/)[1]),layout=readFileSync(resolve(root,'scripts/tu-role-layout.h'),'utf8');for(let i=0;i<expr.length;i++)assert.ok(layout.includes('ROLE_META(expr_'+i+','+expr[i]+'),'),expr[i]);
let owner;const expectedRng=[];src.split('\n').forEach((line,i)=>{const m=line.match(/^(\w+)\(/);if(m)owner=m[1];for(const call of line.matchAll(/\brn2\s*\(/g))expectedRng.push([owner,i+1]);});const actualRng=[...core.matchAll(/C\.rn2\([^;\n]*?, (\d+), "(\w+)"\)/g)].map(m=>[m[2],Number(m[1])]);assert.deepEqual(actualRng,expectedRng);assert.equal(expectedRng.length,14);assert.equal((core.match(/C\.rn2_on_display_rng\(/g)||[]).length,1);
const native=readFileSync(resolve(root,'nethack-c/wasm/tu-role-support.inc'),'utf8');assert.equal((core.match(/C\.assert\(/g)||[]).length,5);assert.equal((core.match(/C\.Strlen\(/g)||[]).length,6);const ownerAt=at=>[...src.slice(0,at).matchAll(/^(\w+)\(/gm)].at(-1)[1];
const assertExpected=[...src.matchAll(/\bassert\(/g)].map(m=>{let i=m.index+m[0].length,d=1;const start=i;while(d){d+=(src[i]==='(')-(src[i]===')');i++;}return [src.slice(start,i-1).replace(/\s+/g,' '),src.slice(0,i).split('\n').length,ownerAt(m.index)];});
const assertActual=[...native.matchAll(/__assert_fail\(("(?:\\.|[^"\\])*"),"role\.c",(\d+),"(\w+)"\)/g)].map(m=>[JSON.parse(m[1]),Number(m[2]),m[3]]);assert.deepEqual(assertActual,assertExpected);
const strlenExpected=[...src.matchAll(/\bStrlen\(/g)].map(m=>[ownerAt(m.index),src.slice(0,m.index).split('\n').length]);
const strlenActual=[...native.matchAll(/return Strlen_\(s,"(\w+)",(\d+)\)/g)].map(m=>[m[1],Number(m[2])]);assert.deepEqual(strlenActual,strlenExpected);

for(const mutation of [()=>{const x=structuredClone(role.roles);[x[0],x[1]]=[x[1],x[0]];return x;},()=>{const x=structuredClone(role.roles);x[0][0][0]='Changed';return x;},()=>{const x=structuredClone(role.roles);x[0][8].c='NON_PM';return x;}])assert.throws(()=>assert.deepEqual(canonical(mutation()),canonical(expected('roles'))));
console.log('ROLE four original catalogues, symbolic compiler expressions, 15 RNG calls, five assertions/six Strlen contexts passed (three rejected data mutations).');
