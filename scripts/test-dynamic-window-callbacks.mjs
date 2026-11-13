// Execute every finite window dispatcher with a checked function table. This is
// boundary validation, not execution of the game policies which call it.
// Source expressions run against inert memory/function-table services and JSON
// tables. Unknown expressions may be ignored only outside dispatch contracts:
// every dispatcher caller, helper reference and inventoried lookup must resolve.
// Both branches are traversed; finite for-of tables are expanded exhaustively.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import path from 'node:path';
import {parse} from 'acorn';
import {checkEngineCallbacks,checkCallbackSource} from './check-engine-callbacks.mjs';
import {enableRestoreLifecycle} from '../js/nethack/restore-lifecycle.js';
import {enableSaveLifecycle} from '../js/nethack/save-lifecycle.js';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
const runtime=createStandaloneEnvironment(),fields=runtime.ctypes.record('struct window_procs').fields;
const unknown=Symbol('unresolved'),inventory=checkEngineCallbacks().dynamic,results=[],dispatches=[];
function signature(type){const m=type.match(/^(.*?)\s*\(\s*\*\s*\)\s*\((.*)\)/);assert.ok(m,'callback prototype '+type);const code=t=>{t=runtime.ctypes.canonical(t.trim());return t.includes('*')?'p':t==='void'?'v':t==='float'?'f':t==='double'?'d':runtime.ctypes.size(t)===8?'j':'i';};return code(m[1])+(m[2].trim()==='void'||!m[2].trim()?'':m[2].split(',').map(code).join(''));}
const byId=new Map(Object.entries(fields).map(([name,f])=>[BigInt(f.offset+1),name]));
const record=()=>({fields}),locate=(type,at,name)=>{assert.ok(fields[name],'unknown window field '+name);return{at:fields[name].offset,field:fields[name]};};
const ctypes={...runtime.ctypes,record,locate,getField:(t,p,k)=>{locate(t,p,k);return BigInt(fields[k].offset+1);},load:(t,at)=>BigInt(at+1)};
const indirect=(id,sig,...args)=>{const name=byId.get(BigInt(id));assert.ok(name,'callback address '+id);assert.equal(sig,signature(fields[name].ctype),'signature '+name);dispatches.push({name,signature:sig});return 0;};
const memory={view:{getBigUint64:at=>BigInt(at+1)}},functions={indirect};
const environment={ctypes,memory,functions,requireGlobal:()=>0,address:v=>v};
const transport=new Proxy({},{get:()=>v=>v}),services={literal:()=>0};
Object.assign(environment,{transport,services});
const boundary=(...args)=>args.length===1?args[0]:args.at(-1);
function children(n){return Object.entries(n).filter(([k])=>!['loc','start','end','type'].includes(k)).flatMap(([,v])=>Array.isArray(v)?v:v&&typeof v==='object'?[v]:[]).filter(v=>v?.type);}
function pattern(p,v,scope){if(p.type==='Identifier'){if(v!==unknown||!['ctypes','memory','functions','environment','transport','services','boundary','text','address','cptr','size'].includes(p.name))scope[p.name]=v;}else if(p.type==='ArrayPattern')p.elements.forEach((e,i)=>e&&pattern(e,v===unknown?unknown:v?.[i],scope));else if(p.type==='ObjectPattern')p.properties.forEach(e=>pattern(e.value,v===unknown?unknown:v?.[e.key.name],scope));}
export function auditDynamicFile(file,source,sites=checkCallbackSource(source,file).dynamic){
 const ast=parse(source,{ecmaVersion:'latest',sourceType:'module',locations:true});
 const scope={ctypes,memory,functions,environment,transport,services,boundary,text:()=>0,address:v=>v,cptr:()=>0,size:runtime.ctypes.size};
 const covered=new Map(),definitions=new Map(),helperNames=new Map(),helpers=new Set(),calls=[],unresolved=[];
 function hasLookup(n){if(n.type==='MemberExpression'&&n.object.type==='MemberExpression'&&n.object.property.name==='fields'&&n.object.object.type==='CallExpression'&&n.object.object.callee.property?.name==='record'&&n.object.object.arguments[0]?.value==='struct window_procs')return true;if(n.type==='CallExpression'&&n.callee.type==='MemberExpression'&&['locate','getField'].includes(n.callee.property.name)&&n.arguments[0]?.value==='struct window_procs'&&(n.arguments[2]?.type!=='Literal'||/\(\s*\*/.test(fields[n.arguments[2].value]?.ctype??'')))return true;return children(n).some(c=>!['ArrowFunctionExpression','FunctionExpression','FunctionDeclaration'].includes(c.type)&&hasLookup(c));}
 function discover(n){if(n.type==='VariableDeclarator'&&['ArrowFunctionExpression','FunctionExpression'].includes(n.init?.type)&&hasLookup(n.init.body))helpers.add(n.id.name);if(n.type==='FunctionDeclaration'&&hasLookup(n.body))helpers.add(n.id.name);children(n).forEach(discover);}discover(ast);
 function checkEscapes(n,parent){if(n.type==='Identifier'&&helpers.has(n.name))assert.ok((parent.type==='VariableDeclarator'&&parent.id===n)||(parent.type==='FunctionDeclaration'&&parent.id===n)||(parent.type==='CallExpression'&&parent.callee===n),file+':'+n.loc.start.line+' untraced dispatcher escape '+n.name);children(n).forEach(c=>checkEscapes(c,n));}checkEscapes(ast,{});
 function evaluate(n,s){if(!n)return unknown;try{const entries=Object.entries(s).filter(([,v])=>v!==unknown);return Function(...entries.map(([k])=>k),'return ('+source.slice(n.start,n.end)+')')(...entries.map(([,v])=>v));}catch{return unknown;}}
 function mark(n,names){const line=n.loc.start.line;if(!covered.has(line))covered.set(line,new Set());for(const x of names)covered.get(line).add(x);}
 function finiteFields(n,s){const out=[];function visit(x){let key;if(x.type==='MemberExpression'&&x.object.property?.name==='fields')key=evaluate(x.property,s);if(x.type==='CallExpression'&&['locate','getField'].includes(x.callee.property?.name)&&x.arguments[0]?.value==='struct window_procs')key=evaluate(x.arguments[2],s);if(typeof key==='string'&&fields[key])out.push(key);children(x).forEach(visit);}visit(n);return out;}
 function literalFields(n){const out=[];function visit(x){if(x.type==='Literal'&&typeof x.value==='string'&&fields[x.value])out.push(x.value);children(x).forEach(visit);}visit(n);return out;}
 function probe(fn,args,n,s){const before=dispatches.length;const key=[args[0],typeof args[0]==='string'?'win_'+args[0]:undefined,s.row?.field,s.field,s.key,s.name,...literalFields(n),...finiteFields(n,s)].find(k=>typeof k==='string'&&fields[k]);assert.ok(key,file+':'+n.loc.start.line+' finite callback name');const count=fn.length+signature(fields[key].ctype).length-1;try{fn(...args,...Array(Math.max(0,count-args.length)).fill(0));}catch(e){throw new Error(file+':'+n.loc.start.line+': '+e.message,{cause:e});}assert.ok(dispatches.length>before,file+':'+n.loc.start.line+' must dispatch');const names=dispatches.slice(before).map(x=>x.name);mark(n,names);calls.push({line:n.loc.start.line,names});if(n.callee?.type==='Identifier'&&helpers.has(n.callee.name)){if(!helperNames.has(n.callee.name))helperNames.set(n.callee.name,new Set());for(const name of names)helperNames.get(n.callee.name).add(name);}}
 function visit(n,s,owner){if(!n)return;
  if(n.type==='ImportDeclaration'){if(n.source.value.endsWith('.json')){const value=JSON.parse(fs.readFileSync(path.resolve(path.dirname(file),n.source.value)));for(const spec of n.specifiers)s[spec.local.name]=value;}return;}
  if(n.type==='Program'||n.type==='BlockStatement'){const local={...s};for(const x of n.body)visit(x,local,owner);return;}
  if(n.type==='VariableDeclaration'){for(const d of n.declarations){const value=evaluate(d.init,s);pattern(d.id,value,s);if(d.init&&['ArrowFunctionExpression','FunctionExpression'].includes(d.init.type))visit(d.init,s,d.id.name);else if(d.init)visit(d.init,s,owner);}return;}
  if(n.type==='FunctionDeclaration'){s[n.id.name]=evaluate({...n,type:'FunctionExpression'},s);const local={...s};n.params.forEach(p=>pattern(p,unknown,local));visit(n.body,local,n.id.name);return;}
  if(n.type==='ArrowFunctionExpression'||n.type==='FunctionExpression'){const local={...s};n.params.forEach(p=>pattern(p,unknown,local));
   // Finite generated dispatch closure: its captured table row is already bound.
   if(hasLookup(n.body)&&!helpers.has(owner)){const fn=evaluate(n,s);if(fn!==unknown){probe(fn,[],n,s);return;}}
   visit(n.body,local,owner);return;}
  if(n.type==='ForOfStatement'){const rows=evaluate(n.right,s);if(rows!==unknown&&rows&&Symbol.iterator in Object(rows)){for(const row of rows){const local={...s},p=n.left.type==='VariableDeclaration'?n.left.declarations[0].id:n.left;pattern(p,row,local);visit(n.body,local,owner);}return;}}
  if(n.type==='CallExpression'&&n.callee.type==='Identifier'&&helpers.has(n.callee.name)){
   const args=n.arguments.filter(x=>x.type!=='SpreadElement').map(x=>evaluate(x,s));
   if(args[0]!==unknown&&typeof s[n.callee.name]==='function'){probe(s[n.callee.name],args.map(v=>v===unknown?0:v),n,s);return;}unresolved.push({line:n.loc.start.line,owner,expression:source.slice(n.start,n.end)});
  }
  // Definitions are covered by exhaustive probes of all their call sites below.
  if(hasLookup(n)&&['CallExpression','MemberExpression'].includes(n.type)&&owner&&helpers.has(owner)){mark(n,[]);definitions.set(n.loc.start.line,owner);}
  children(n).forEach(c=>visit(c,s,owner));
 }
 visit(ast,scope);
 assert.deepEqual(unresolved,[],file+': all dispatcher callers must resolve');
 const coverage=sites.map(site=>{const names=covered.get(site.line),helper=definitions.get(site.line),validated=names?.size?names:helperNames.get(helper);assert.ok(validated?.size,file+':'+site.line+' unresolved dynamic lookup');return{...site,helper,names:[...validated].sort()};});
 return{file,helpers:[...helpers],calls,coverage};
}
for(const file of [...new Set(inventory.map(x=>x.file))])results.push(auditDynamicFile(file,fs.readFileSync(file,'utf8'),inventory.filter(x=>x.file===file)));
const validatedDispatches=dispatches.slice();
assert.deepEqual([...new Set(validatedDispatches.map(x=>x.name))].sort(),Object.keys(fields).filter(k=>/\(\s*\*/.test(fields[k].ctype)).sort(),'every measured window callback has a validated dispatch');
const apply=fs.readFileSync('js/nethack/apply.js','utf8');
assert.throws(()=>auditDynamicFile('js/nethack/apply.js',apply.replace("window('win_create_nhwindow','ii'","window('win_create_nhwindow','vi'")),/signature win_create_nhwindow/);
assert.throws(()=>auditDynamicFile('js/nethack/apply.js',apply.replace("window('win_create_nhwindow'","window('win_typo'")),/finite callback name|unknown window field|unknown measured callback field/);
assert.throws(()=>auditDynamicFile('js/nethack/apply.js',apply+'\nwindow(runtimeUnknown,\'v\');'),/all dispatcher callers must resolve/);
const restore=fs.readFileSync('js/nethack/restore-lifecycle.js','utf8');
assert.throws(()=>auditDynamicFile('js/nethack/restore-lifecycle.js',restore.replace("ctypes.record('struct window_procs').fields[name]","abi.schemas.window_procs.fields.find(f=>f.name===name)")),/Unknown RESTORE window callback win_select_menu/);
assert.equal(results.reduce((n,r)=>n+r.coverage.length,0),inventory.length);

// Also exercise the actual installed lifecycle owners and real callback table,
// rather than relying exclusively on extracted dispatcher bodies.
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const live=createStandaloneEnvironment();live.enableDecl(layouts.decl);live.enableMonst(layouts.monst);
const table=live.allocateGlobal('windowprocs',live.ctypes.size('struct window_procs'));
let liveCalls=0;
for(const [kind,enable]of [['restore',enableRestoreLifecycle],['save',enableSaveLifecycle]]){
 const owner=enable(live,layouts),audit=results.find(r=>r.file===`js/nethack/${kind}-lifecycle.js`);
 for(const name of new Set(audit.calls.flatMap(c=>c.names))){
  const field=live.ctypes.record('struct window_procs').fields[name],sig=signature(field.ctype),args=Array(sig.length-1).fill(0);
  for(const value of [7,9]){
   const expected=sig[0]==='v'?undefined:value;
   const callback=live.functions.functionPointer((...actual)=>{assert.deepEqual(actual,args);liveCalls++;return expected;},sig);
   live.memory.view.setBigUint64(table+field.offset,callback,true);
   assert.equal(owner.services[name.slice(4)](...args),expected,kind+' live '+name);
  }
 }
}
assert.equal(liveCalls,34,'all twelve restore and five save callbacks, including live replacement');
fs.mkdirSync('.cache/dynamic-callbacks',{recursive:true});fs.writeFileSync('.cache/dynamic-callbacks/discovery.json',JSON.stringify({inventory,results,dispatches:validatedDispatches,liveCalls},null,2)+'\n');
console.log(JSON.stringify({files:results.length,dispatches:validatedDispatches.length,liveCalls,dynamicSites:inventory.length,validatedSites:results.reduce((n,r)=>n+r.coverage.length,0),unresolved:0},null,2));
