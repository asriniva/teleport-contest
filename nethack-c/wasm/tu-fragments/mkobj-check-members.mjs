// Actual generated JS access paths, not only a native AST inventory.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
const root=resolve(new URL('../../../',import.meta.url).pathname),sdk=resolve(process.env.EMSDK??root+'/.cache/emsdk');
const {parse}=await import(pathToFileURL(sdk+'/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const schema=JSON.parse(await readFile(root+'/nethack-c/wasm/tu-fragments/mkobj-schema.json','utf8'));
const tree=parse(await readFile(root+'/js/ported/mkobj.js','utf8'),{sourceType:'module',ecmaVersion:'latest'});
const allowed=new Set(['ptr','i8','u8','i16','u16','i32','u32','i64','u64','sizes','literal','field','cell','global','stackAlloc','stackSave','stackRestore','copyRecord','variadic','callProc','functionPointer','staticArray','staticData',...Object.keys(schema.data),...schema.globals.map(g=>g.name),...schema.enums,...Object.keys(schema.dependencies)]);
let count=0;const paths=new Set();
function walk(n){if(!n||typeof n!=='object')return;if(n.type==='MemberExpression'&&n.object?.type==='Identifier'&&n.object.name==='C'){assert.equal(n.computed,false,'No unchecked dynamic C member lookup');assert.ok(allowed.has(n.property.name),'Untyped C member '+n.property.name);}if(n.type==='CallExpression'&&n.callee?.object?.name==='C'&&n.callee?.property?.name==='field'){const [at,kind,field]=n.arguments;assert.equal(kind.type,'Literal');assert.equal(field.type,'Literal');assert.ok(schema.schema[kind.value]?.fields.some(f=>f.name===field.value),'Missing native field '+kind.value+'.'+field.value);paths.add(kind.value+'.'+field.value);count++;}for(const v of Object.values(n))if(Array.isArray(v))v.forEach(walk);else if(v&&typeof v==='object')walk(v);}
walk(tree);assert.ok(paths.has('vptrs.v_nexthere')&&paths.has('any.a_obj')&&paths.has('icp.iprob')&&paths.has('icp.iclass'));
const support=await readFile(root+'/nethack-c/wasm/tu-fragments/mkobj-support.c','utf8');
for(const action of ['read','write','address']){const body=support.split('teleport_mkobj_'+action+'(')[1].split('default:abort();}}\n')[0];assert.ok(body,'Native helper exists '+action);}
console.log('MKOBJ actual JS paths guarded: '+count+' field accesses, '+paths.size+' unique typed fields; obj.v.v_nexthere/anything.a_obj/icp paths present; no raw C aliases');
