// Focused source/data/attribution guard; not an equivalence or control-flow proof.
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import { kick_passes_thru } from '../js/ported/dokick.js';
const source=readFileSync(new URL('../nethack-c/upstream/src/dokick.c',import.meta.url),'utf8');
const prepared=readFileSync(new URL('../.cache/wasm64-build/tree/src/dokick.c',import.meta.url),'utf8');
const js=readFileSync(new URL('../js/ported/dokick.js',import.meta.url),'utf8');
assert.equal(prepared,source,'This TU has no inherited source adaptation');
const sdk=resolve(process.env.EMSDK??'.cache/emsdk');
const {parse}=await import(pathToFileURL(resolve(sdk,'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const ast=parse(js,{ecmaVersion:'latest',sourceType:'module'});
const names=['kickdmg','maybe_kick_monster','kick_monster','ghitm','container_impact_dmg','kick_object','really_kick_object','kickstr','watchman_thief_arrest','watchman_door_damage','kick_dumb','kick_ouch','kick_door','kick_nondoor','dokick','drop_to','impact_drop','ship_object','obj_delivery','deliver_obj_to_mon','otransit_msg','down_gate'];
const functions=ast.body.filter(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.type==='FunctionDeclaration').map(n=>n.declaration);
assert.deepEqual(functions.map(n=>n.id.name),names);
for(const comment of source.match(/\/\*[\s\S]*?\*\//g)??[])assert.ok(js.includes(comment),'Original block comment changed');
assert.equal(kick_passes_thru,JSON.parse(/kick_passes_thru\[\] =\s*("[^"\n]*")/.exec(source)[1]));
const strip=s=>s.replace(/\/\*[\s\S]*?\*\//g,m=>m.replace(/[^\n]/g,' ')).replace(/\/\/[^\n]*/g,'');
const quoted=s=>[...strip(s).matchAll(/"(?:\\.|[^"\\])*"/g)].map(m=>JSON.parse(m[0]));
assert.deepEqual(quoted(/flyingcoinmsg\[\] = \{([\s\S]*?)\};/.exec(source)[1]),quoted(/const flyingcoinmsg = \[([\s\S]*?)\];/.exec(js)[1]));
assert.match(js,/doit: \{/);assert.match(js,/break doit;/);
const clean=strip(source), definitions=[...clean.matchAll(/\n(\w+)\([^;{}]*\)\s*\{/g)].filter(m=>names.includes(m[1]));
const expected=[];
for(const m of clean.matchAll(/\b(rn2|rnd|rnl|rn1|ROLL_FROM)\s*\(/g)){
 let p=m.index+m[0].length,depth=1,quote='';
 for(;depth;p++){
  const c=clean[p];assert.ok(c!==undefined,'Unclosed source call');
  if(quote){if(c==='\\')p++;else if(c===quote)quote='';}
  else if(c==='"'||c==="'")quote=c;else if(c==='(')depth++;else if(c===')')depth--;
 }
 const owner=definitions.filter(d=>d.index<m.index).at(-1)?.[1];assert.ok(owner,'Source RNG owner');
 expected.push([m[1]==='ROLL_FROM'?'rn2':m[1],clean.slice(0,p).split('\n').length,owner]);
}
const actual=[];
function visit(node,owner){
 if(!node||typeof node!=='object')return;
 if(node.type==='FunctionDeclaration')owner=node.id.name;
 if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'&&['rn2','rnd','rnl','rn1'].includes(node.callee.property.name)){
  const args=node.arguments;actual.push([node.callee.property.name,args.at(-2).value,args.at(-1).value]);assert.equal(args.at(-1).value,owner);
 }
 for(const [k,v]of Object.entries(node))if(k!=='start'&&k!=='end')if(Array.isArray(v))v.forEach(n=>visit(n,owner));else if(v&&typeof v==='object')visit(v,owner);
}
visit(ast);assert.deepEqual(actual,expected,'Every original RNG expression retains type, physical closing line and caller');
const support=readFileSync(new URL('../nethack-c/wasm/tu-dokick-support.inc',import.meta.url),'utf8');
for(const [bridge,original] of [['watch_thief','watchman_thief_arrest'],['watch_door','watchman_door_damage']]){
 const body=new RegExp('static boolean teleport_dokick_'+bridge+'[^]*?\\}').exec(support)?.[0];
 assert.ok(body,'Native production callback '+bridge);
 assert.ok(body.includes('teleport_dokick_callback_'+original+'('));
 assert.ok(!body.includes('teleport_dokick_test_'),'Production callback cannot depend on test alias');
}
assert.match(support,/TELEPORT_DOKICK_LITERAL_CAPACITY/);
console.log(`DOKICK guard passed: 22 functions, all block comments, both JS data projections, goto join and ${actual.length} exact source RNG sites; pristine/prepared identical.`);
