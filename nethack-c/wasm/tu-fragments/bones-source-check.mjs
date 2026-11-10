// Development-only guard for the configured translation's original RNG sites,
// literal capacity and compiler-known field schema. No runtime C lookup table.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {resolve,join} from 'node:path';
const root=fileURLToPath(new URL('../../../',import.meta.url));
const sdk=resolve(process.env.EMSDK??join(root,'.cache/emsdk'));
const {parse}=await import(pathToFileURL(join(sdk,'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const source=readFileSync(join(root,'.cache/wasm64-build/tree/src/bones.c'),'utf8');
const core=readFileSync(join(root,'js/ported/bones.js'),'utf8');
const binding=readFileSync(join(root,'nethack-c/wasm/tu-libraries/bones.js'),'utf8');
const support=readFileSync(join(root,'nethack-c/wasm/tu-fragments/bones-support.c'),'utf8');
const header=readFileSync(join(root,'nethack-c/wasm/tu-fragments/bones-source-data.h'),'utf8');
const sites=[[247,'rn2(nmon)','give_to_nearby_mon'],[290,'rn2(5)','drop_upon_death'],[296,'rn2(8)','drop_upon_death'],[377,'rn2(1 + (depth(&u.uz) >> 2))','can_make_bones'],[645,'rn2(3)','getbones']];
function checkSites(text){const lines=text.split('\n');for(const [line,expression]of sites)assert.ok(lines[line-1]?.includes(expression),'Review original BONES RNG site '+line);}
checkSites(source);assert.throws(()=>checkSites('\n'+source),/Review original BONES RNG site/);
assert.ok(support.includes('lines[]={'+sites.map(([line])=>line).join(',')+'}'));
assert.ok(support.includes('callers[]={'+sites.map(([, ,name])=>JSON.stringify(name)).join(',')+'}'));
const ast=parse(core,{ecmaVersion:'latest',sourceType:'module'}),strings=new Set(['%s']);
function visit(node,parent,key){if(node.type==='Literal'&&typeof node.value==='string'&&parent?.type!=='ImportDeclaration'&&!(parent?.type==='CallExpression'&&parent.callee?.property?.name==='reference'&&key===0))strings.add(node.value);for(const [field,value]of Object.entries(node)){if(value&&typeof value==='object'){if(Array.isArray(value))value.forEach((child,index)=>{if(child?.type)visit(child,node,index);});else if(value.type)visit(value,node,field);}}}
visit(ast);const capacity=Array.from(strings).reduce((sum,text)=>sum+Buffer.byteLength(text)+1,0);
assert.equal(Number(header.match(/TELEPORT_BONES_LITERAL_CAPACITY (\d+)/)?.[1]),capacity,'Derived BONES ABI literal capacity');
assert.ok(binding.includes("text('%s')"),'One additional macro format must remain in the corpus');
assert.ok(support.includes('teleport_bones_literals[TELEPORT_BONES_LITERAL_CAPACITY]'));
console.log(`BONES source data: all five original RNG sites/callers and ${capacity} literal bytes checked; shifted-line mutation rejected`);
